// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2020 Samsung Electronics Co., Ltd.
 *      http://www.samsung.com
 */

#include <linux/cpumask.h>
#include <linux/tick.h>
#include <linux/cpu.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <trace/events/power.h>
#include <uapi/linux/sched/types.h>
#include <linux/sched.h>
#include <linux/sched/prio.h>
#include <linux/suspend.h>
#include <linux/kthread.h>
#include <linux/cpufreq.h>
#include <linux/pm_qos.h>

#undef pr_fmt
#define pr_fmt(fmt) "[wcpu_alloc] " fmt

#define INVALID_SAVED_PRIO	(-1)
#define PM_TASK_RT_PRIO		(1)
#define PMS_TASK_RT

static struct cpumask fast_cpu_mask;
static struct cpumask backup_cpu_mask;
static int start_cpu, end_cpu;
static struct task_struct *pms_task;
#if defined(PMS_TASK_RT)
static int saved_prio = INVALID_SAVED_PRIO;
static int prev_policy;
static unsigned int rt_on = 1;
#endif

static int sec_wcpu_alloc_pm_notifier(struct notifier_block *notifier,
				      unsigned long pm_event, void *dummy);

static int __start_boosting(void);
static void __restore_boosting(void);

/*
 * dpm_complete resume boosting
 *
 * Raise the minimum frequency of a target CPU cluster during the tail of system
 * resume.  The boost is applied at the beginning of the dpm_complete() section
 * (hooked via the suspend_resume tracepoint that emits TPS("dpm_complete"), so
 * dpm_complete() itself is left untouched) and released at PM_POST_SUSPEND,
 * which marks the end of the resume window we care about.
 *
 * The frequency floor is applied through the cpufreq policy's FREQ_QOS_MIN
 * constraint (the same freq_qos framework exynos-acme uses), which is what
 * actually drives the CPU cluster frequency.  freq_qos has no timeout variant,
 * hence the explicit release at PM_POST_SUSPEND.
 *
 * Configuration (device tree):
 *   boost_enable   - 0/1, master switch for the feature
 *   boost_cluster  - target cluster index (0: little, 1: big, ...)
 *   boost_freq_khz - minimum frequency to guarantee, in kHz
 */
static bool boost_enabled;
static u32 boost_cluster;
static u32 boost_freq_khz;
static int boost_cpu = -1;		/* representative cpu of boost_cluster */
static bool boost_req_added;		/* freq_qos request has been added */
static bool boost_active;		/* floor currently raised (needs release) */
static struct freq_qos_request boost_freq_req;
static struct kthread_worker *boost_kworker;
static struct kthread_work boost_kwork;

/*
 * Map a cluster index to a representative cpu.  cpufreq exposes one policy per
 * cluster whose related_cpus lists all cpus of that cluster, and clusters are
 * laid out in ascending cpu-id order, so the Nth policy leader is cluster N.
 */
static int sec_wcpu_cluster_first_cpu(u32 cluster)
{
	struct cpufreq_policy *policy;
	int cpu, first;
	u32 idx = 0;

	for_each_possible_cpu(cpu) {
		policy = cpufreq_cpu_get(cpu);
		if (!policy)
			continue;
		first = cpumask_first(policy->related_cpus);
		cpufreq_cpu_put(policy);

		if (first != cpu)
			continue;	/* not the leader of its cluster */
		if (idx == cluster)
			return cpu;
		idx++;
	}

	return -1;
}

/* Add our FREQ_QOS_MIN request to the target cluster's cpufreq policy (once). */
static int sec_wcpu_boost_add_freq_qos(void)
{
	struct cpufreq_policy *policy;
	int cpu, ret;

	cpu = sec_wcpu_cluster_first_cpu(boost_cluster);
	if (cpu < 0) {
		pr_err("%s: no cpufreq policy for cluster%u\n", __func__,
		       boost_cluster);
		return -ENODEV;
	}

	policy = cpufreq_cpu_get(cpu);
	if (!policy)
		return -ENODEV;

	ret = freq_qos_add_request(&policy->constraints, &boost_freq_req,
				   FREQ_QOS_MIN, FREQ_QOS_MIN_DEFAULT_VALUE);
	/*
	 * boost_freq_req stays linked in policy->constraints after we drop this
	 * reference, but that is safe here: the cluster's cpufreq policy lives for
	 * the system lifetime (the cpufreq driver is never unbound at runtime on
	 * this SoC), so &policy->constraints remains valid until we remove the
	 * request in sec_wcpu_boost_exit().
	 */
	cpufreq_cpu_put(policy);
	if (ret < 0) {
		pr_err("%s: freq_qos_add_request failed (%d)\n", __func__, ret);
		return ret;
	}

	boost_cpu = cpu;
	return 0;
}

/*
 * Runs in the dedicated RT kthread (schedulable context).  freq_qos_*_request()
 * may sleep (mutex + blocking notifier that applies the frequency), so it cannot
 * run directly from the tracepoint probe, which executes with preemption
 * disabled.
 */
static void sec_wcpu_boost_work_fn(struct kthread_work *work)
{
	int ret;

	/* cpufreq is guaranteed up by the time dpm_complete runs; add lazily. */
	if (!boost_req_added) {
		if (sec_wcpu_boost_add_freq_qos() < 0)
			return;
		boost_req_added = true;
	}

	ret = freq_qos_update_request(&boost_freq_req, boost_freq_khz);
	boost_active = true;

	/*
	 * cpufreq_quick_get() returns policy->cur, i.e. the frequency the cpufreq
	 * driver last programmed, so it is a physical-level confirmation that the
	 * floor took effect (unlike a pure QoS-target read-back).
	 */
	pr_info("boost cluster%u(cpu%d) min=%u kHz applied, cpufreq_cur=%u kHz (ret=%d)\n",
		boost_cluster, boost_cpu, boost_freq_khz,
		cpufreq_quick_get(boost_cpu), ret);
}

/* Release the frequency floor.  Called from the PM_POST_SUSPEND notifier. */
static void sec_wcpu_boost_release(void)
{
	if (!boost_enabled)
		return;

	/*
	 * Make sure the (asynchronous, RT-kthread) apply has finished before we
	 * decide whether to release, otherwise a delayed apply could land after
	 * this point and leave the floor stuck high.
	 */
	kthread_flush_work(&boost_kwork);

	if (boost_req_added && boost_active) {
		freq_qos_update_request(&boost_freq_req, FREQ_QOS_MIN_DEFAULT_VALUE);
		boost_active = false;
		pr_info("boost cluster%u released, cpufreq_cur=%u kHz\n",
			boost_cluster, cpufreq_quick_get(boost_cpu));
	}
}

/*
 * suspend_resume tracepoint probe.  dpm_complete() is only entered on the
 * resume path, so matching action == "dpm_complete" with start == true catches
 * the start of the dpm_complete section during resume.  This runs in atomic
 * context, so it only kicks the RT kthread and returns.
 */
static void sec_wcpu_dpm_complete_probe(void *data, const char *action,
					int val, bool start)
{
	if (!boost_enabled || !start)
		return;

	if (strcmp(action, "dpm_complete"))
		return;

	kthread_queue_work(boost_kworker, &boost_kwork);
}

static void sec_wcpu_boost_parse_dt(struct device *dev)
{
	u32 enable = 0;

	boost_enabled = false;

	if (of_property_read_u32(dev->of_node, "boost_enable", &enable) < 0 ||
	    enable == 0) {
		pr_info("%s: dpm_complete boosting disabled\n", __func__);
		return;
	}

	if (of_property_read_u32(dev->of_node, "boost_cluster", &boost_cluster) < 0) {
		pr_info("%s: boost_cluster not found\n", __func__);
		return;
	}

	if (of_property_read_u32(dev->of_node, "boost_freq_khz", &boost_freq_khz) < 0) {
		pr_info("%s: boost_freq_khz not found\n", __func__);
		return;
	}

	boost_enabled = true;
	pr_info("%s: boost cluster%u to %u kHz from dpm_complete to post_suspend\n",
		__func__, boost_cluster, boost_freq_khz);
}

static void sec_wcpu_boost_init(void)
{
	int ret;

	if (!boost_enabled)
		return;

	/*
	 * Apply the boost from a dedicated real-time kthread.  The suspend_resume
	 * tracepoint probe runs with preemption disabled, so it can only hand the
	 * work off to a schedulable context.  A normal workqueue worker was seen
	 * to start several milliseconds late, which is huge against a short resume
	 * window, so an RT (SCHED_FIFO) kthread is used to keep the wake-up latency
	 * to microseconds.
	 */
	boost_kworker = kthread_create_worker(0, "wcpu_boost");
	if (IS_ERR(boost_kworker)) {
		pr_err("%s: failed to create boost kthread (%ld)\n",
		       __func__, PTR_ERR(boost_kworker));
		boost_kworker = NULL;
		boost_enabled = false;
		return;
	}
	sched_set_fifo_low(boost_kworker->task);
	kthread_init_work(&boost_kwork, sec_wcpu_boost_work_fn);

	ret = register_trace_suspend_resume(sec_wcpu_dpm_complete_probe, NULL);
	if (ret) {
		pr_err("%s: failed to register suspend_resume probe (%d)\n",
		       __func__, ret);
		kthread_destroy_worker(boost_kworker);
		boost_kworker = NULL;
		boost_enabled = false;
		return;
	}

	pr_info("%s: dpm_complete boosting armed (freq_qos, rt kthread)\n", __func__);
}

static void sec_wcpu_boost_exit(void)
{
	if (!boost_enabled)
		return;

	unregister_trace_suspend_resume(sec_wcpu_dpm_complete_probe, NULL);
	/*
	 * Wait for any in-flight probe to finish before tearing down the resources
	 * it touches (the kthread worker).  Otherwise a probe racing with module
	 * exit could queue work onto a destroyed worker or run freed module code.
	 */
	tracepoint_synchronize_unregister();

	kthread_flush_work(&boost_kwork);
	kthread_destroy_worker(boost_kworker);
	boost_kworker = NULL;

	if (boost_req_added) {
		freq_qos_remove_request(&boost_freq_req);
		boost_req_added = false;
	}
}
static void init_pm_cpumask(void)
{
	int i;

	cpumask_clear(&fast_cpu_mask);
	for (i = start_cpu; i <= end_cpu; i++)
		cpumask_set_cpu(i, &fast_cpu_mask);
}

static int sec_wakeup_cpu_allocator_suspend_noirq(struct device *dev)
{
	pr_info("%s\n", __func__);

	return 0;
}

static int __start_boosting(void)
{
#if defined(PMS_TASK_RT)
	struct sched_attr attr;
	int ret;
#endif

	pr_info("%s\n", __func__);
	cpumask_copy(&backup_cpu_mask, current->cpus_ptr);
	set_cpus_allowed_ptr(current, &fast_cpu_mask);
	pms_task = current;

#if defined(PMS_TASK_RT)
	if (rt_on && current->prio >= MAX_RT_PRIO) {
		saved_prio = current->prio;
		prev_policy = current->policy;
		memset(&attr, 0, sizeof(attr));
		attr.size = sizeof(attr);
		attr.sched_policy = SCHED_FIFO;
		attr.sched_priority = PM_TASK_RT_PRIO;
		pr_info("start boosting target prio: (%d, %d) current (%d, %d)\n",
			PM_TASK_RT_PRIO, SCHED_FIFO, saved_prio, prev_policy);
		ret = sched_setattr_nocheck(current, &attr);
		if (ret != 0) {
			pr_err("Failed to set real-time scheduling policy and priority with ret:%d\n", ret);
#if defined(DEBUG_ENABLE)
			BUG();
#endif
		}
	}
#endif

	return 0;
}

static void __restore_boosting(void)
{
#if defined(PMS_TASK_RT)
	int ret;
	struct sched_attr attr;
#endif
	pr_info("%s\n", __func__);

	if (!cpumask_empty(&backup_cpu_mask)) {
		set_cpus_allowed_ptr(pms_task, &backup_cpu_mask);
		cpumask_clear(&backup_cpu_mask);
#if defined(PMS_TASK_RT)
		if (rt_on && saved_prio != INVALID_SAVED_PRIO) {
			pr_info("restored to (%d, %d) from prev prio (%d, %d)\n",
				saved_prio, prev_policy, current->prio, current->policy);

			memset(&attr, 0, sizeof(attr));
			attr.size = sizeof(attr);
			attr.sched_policy = prev_policy; // SCHED_NORMAL
			attr.sched_priority = 0; // Must be 0 for SCHED_NORMAL
			attr.sched_nice = PRIO_TO_NICE(saved_prio); // Restore nice value
			ret = sched_setattr(pms_task, &attr);
			if (ret != 0) {
				pr_crit("Failed to retore to saved_prio with error: %d\n", ret);
#if defined(DEBUG_ENABLE)
				BUG();
#endif
			}
			saved_prio = INVALID_SAVED_PRIO;
		}
#endif
	}
}

static int sec_wakeup_cpu_allocator_resume_noirq(struct device *dev)
{
	return __start_boosting();
}

static void sec_wakeup_cpu_allocator_complete(struct device *dev)
{
	pr_info("%s\n", __func__);

	/*
	 *	if (!cpumask_empty(&backup_cpu_mask)) {
	 *	set_cpus_allowed_ptr(current, &backup_cpu_mask);
	 *	cpumask_clear(&backup_cpu_mask);
	 *}
	 */
}

static const struct dev_pm_ops wakeupcpu_pm_ops = {
	.suspend_noirq = sec_wakeup_cpu_allocator_suspend_noirq,
	.resume_noirq = sec_wakeup_cpu_allocator_resume_noirq,
	.complete = sec_wakeup_cpu_allocator_complete,
};

static struct notifier_block sec_wcpu_alloc_pm_notifier_block = {
	.notifier_call = sec_wcpu_alloc_pm_notifier,
};

static int sec_wcpu_alloc_pm_notifier(struct notifier_block *notifier,
	unsigned long pm_event, void *dummy)
{
	switch (pm_event) {
	case PM_POST_SUSPEND:
		__restore_boosting();
		/* End of the resume window: drop the cpufreq floor we raised. */
		sec_wcpu_boost_release();
		break;
	}

	return NOTIFY_OK;
}

static int sec_wakeup_cpu_allocator_setup(struct device *dev)
{
	int ret = 0;

	pr_info("%s\n", __func__);

	if (of_property_read_u32(dev->of_node, "start_cpu_num", &start_cpu) < 0) {
		pr_info("%s: start_cpu_num not found\n", __func__);
		ret = -ENODEV;
	}

	if (of_property_read_u32(dev->of_node, "end_cpu_num", &end_cpu) < 0) {
		pr_info("%s: end_cpu_num not found\n", __func__);
		ret = -ENODEV;
	}

	pr_info("%s: alloc cpu %d - %d\n", __func__, start_cpu, end_cpu);

	return ret;
}

/*
 * Sysfs impl
 */

#if defined(DEBUG_ENABLE)
static ssize_t wcpus_store(struct device *dev,
	struct device_attribute *attr,
	const char *buf, size_t count)
{
	int ret;
	unsigned int start, end;

	ret = sscanf(buf, "%u %u", &start, &end);
	if (ret != 2)
		return -EINVAL;

	start_cpu = start;
	end_cpu = end;
	init_pm_cpumask();
	pr_info("wakeup cpus: %d ~ %d\n", start, end);
	return count;
}

#if defined(PMS_TASK_RT)
static ssize_t rt_task_store(struct device *dev,
	struct device_attribute *attr,
	const char *buf, size_t count)
{
	unsigned int val;
	int ret;

	ret = kstrtouint(buf, 10, &val);
	if (ret < 0)
		return ret;

	if (val > 1)
		return -EINVAL;

	rt_on = val;
	pr_info("pms run by rt: %d\n", rt_on);
	return count;
}
#endif

static DEVICE_ATTR(wcpus, 0220, NULL, wcpus_store);
#if defined(PMS_TASK_RT)
static DEVICE_ATTR(rt_task, 0220, NULL, rt_task_store);
#endif
static struct attribute *sec_wakeup_attrs[] = {
	&dev_attr_wcpus.attr,
#if defined(PMS_TASK_RT)
	&dev_attr_rt_task.attr,
#endif
	NULL,
};

static const struct attribute_group sec_wakeup_attr_group = {
	.attrs = sec_wakeup_attrs,
};
#endif

static int sec_wakeup_cpu_allocator_probe(struct platform_device *pdev)
{
#if defined(DEBUG_ENABLE)
	int ret;
	struct device *dev = &pdev->dev;
#endif
	pr_info("%s\n", __func__);
	if (sec_wakeup_cpu_allocator_setup(&pdev->dev) < 0) {
		pr_crit("%s: failed\n", __func__);
		return -ENODEV;
	}

#if defined(DEBUG_ENABLE)
	ret = sysfs_create_group(&dev->kobj, &sec_wakeup_attr_group);
	if (ret) {
		dev_err(dev, "Failed to create sysfs group\n");
		return ret;
	}
#endif
	init_pm_cpumask();

	register_pm_notifier(&sec_wcpu_alloc_pm_notifier_block);

	sec_wcpu_boost_parse_dt(&pdev->dev);
	sec_wcpu_boost_init();

	return 0;
}

static const struct of_device_id of_sec_wakeup_cpu_allocator_match[] = {
	{ .compatible = "samsung,sec_wakeup_cpu_allocator", },
	{ },
};
MODULE_DEVICE_TABLE(of, of_sec_wakeup_cpu_allocator_match);

static struct platform_driver sec_wakeup_cpu_allocator_driver = {
	.probe = sec_wakeup_cpu_allocator_probe,
	.driver = {
		.name = "sec_wakeup_cpu_allocator",
		.of_match_table = of_match_ptr(of_sec_wakeup_cpu_allocator_match),
#if IS_ENABLED(CONFIG_PM)
		.pm = &wakeupcpu_pm_ops,
#endif
	},

};

static int __init sec_wakeup_cpu_allocator_driver_init(void)
{
	pr_info("%s\n", __func__);
	return platform_driver_register(&sec_wakeup_cpu_allocator_driver);
}
core_initcall(sec_wakeup_cpu_allocator_driver_init);

static void __exit sec_wakeup_cpu_allocator_driver_exit(void)
{
	pr_info("%s\n", __func__);
	/*
	 * Stop the PM notifier before tearing down the boost: sec_wcpu_boost_release()
	 * runs from the PM_POST_SUSPEND notifier and touches boost resources, so it
	 * must not fire once sec_wcpu_boost_exit() has freed them.
	 */
	unregister_pm_notifier(&sec_wcpu_alloc_pm_notifier_block);
	sec_wcpu_boost_exit();
	platform_driver_unregister(&sec_wakeup_cpu_allocator_driver);
}
module_exit(sec_wakeup_cpu_allocator_driver_exit);

MODULE_DESCRIPTION("SEC WAKEUP CPU ALLOCATOR driver");
MODULE_LICENSE("GPL");
