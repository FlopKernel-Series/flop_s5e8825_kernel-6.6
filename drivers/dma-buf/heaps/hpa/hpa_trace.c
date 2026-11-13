// SPDX-License-Identifier: GPL-2.0
/*
 * DMABUF HPA heap trace for Samsung
 *
 * Copyright (C) 2021 Samsung Electronics Co., Ltd.
 * Author: <hyesoo.yu@samsung.com> for Samsung
 */

#include <linux/mutex.h>
#include <linux/dma-buf.h>
#include <linux/anon_inodes.h>
#include <linux/fdtable.h>

static DEFINE_MUTEX(hpa_trace_lock);

struct hpa_trace_task {
	struct list_head node;
	struct task_struct *task;
	struct file *file;
};
static struct list_head hpa_task_list = LIST_HEAD_INIT(hpa_task_list);

#define MAX_HPA_MAP_DEVICE 64
static struct hpa_map_device {
	struct device *dev;
	size_t size;
	unsigned long mapcnt;
} hpa_map_lists[MAX_HPA_MAP_DEVICE];
static unsigned int hpa_map_devices;

static struct hpa_map_device *hpa_trace_get_device(struct device *dev)
{
	unsigned int i;

	for (i = 0; i < hpa_map_devices; i++) {
		if (hpa_map_lists[i].dev == dev)
			return &hpa_map_lists[i];
	}

	BUG_ON(hpa_map_devices == MAX_HPA_MAP_DEVICE);
	hpa_map_lists[hpa_map_devices].dev = dev;

	return &hpa_map_lists[hpa_map_devices++];
}

void hpa_trace_map(struct dma_buf *dmabuf, struct device *dev)
{
	struct hpa_map_device *trace_device;

	mutex_lock(&hpa_trace_lock);
	trace_device = hpa_trace_get_device(dev);

	trace_device->size += dmabuf->size;
	trace_device->mapcnt++;

	mutex_unlock(&hpa_trace_lock);
}

void hpa_trace_unmap(struct dma_buf *dmabuf, struct device *dev)
{
	struct hpa_map_device *trace_device;

	mutex_lock(&hpa_trace_lock);
	trace_device = hpa_trace_get_device(dev);

	trace_device->size -= dmabuf->size;
	trace_device->mapcnt--;

	mutex_unlock(&hpa_trace_lock);
}

static int hpa_trace_task_release(struct inode *inode, struct file *file)
{
	struct hpa_trace_task *task = file->private_data;

	if (!(task->task->flags & PF_EXITING)) {
		pr_err("%s: Invalid to close '%d' on process '%s'(%x, %x)\n",
			   __func__, task->task->pid, task->task->comm,
			   task->task->flags, task->task->__state);
		dump_stack();
	}
	put_task_struct(task->task);

	mutex_lock(&hpa_trace_lock);
	list_del(&task->node);
	mutex_unlock(&hpa_trace_lock);

	kfree(task);

	return 0;
}

static const struct file_operations hpa_trace_task_fops = {
	.release = hpa_trace_task_release,
};

void hpa_trace_add_task(void)
{
	struct hpa_trace_task *task;
	unsigned char name[10];
	int fd;

	if (!current->mm && (current->flags & PF_KTHREAD))
		return;

	if (current->group_leader->pid == 1)
		return;

	mutex_lock(&hpa_trace_lock);

	list_for_each_entry(task, &hpa_task_list, node) {
		if (task->task == current->group_leader) {
			mutex_unlock(&hpa_trace_lock);
			return;
		}
	}

	task = kzalloc(sizeof(*task), GFP_KERNEL);
	if (!task)
		goto err;

	get_task_struct(current->group_leader);
	task->task = current->group_leader;

	fd = get_unused_fd_flags(O_RDONLY | O_CLOEXEC);
	if (fd < 0)
		goto err_fd;

	scnprintf(name, 10, "%d", current->group_leader->pid);
	task->file = anon_inode_getfile(name, &hpa_trace_task_fops, task, O_RDWR);
	if (IS_ERR(task->file))
		goto err_inode;

	fd_install(fd, task->file);
	list_add_tail(&task->node, &hpa_task_list);

	mutex_unlock(&hpa_trace_lock);

	return;

err_inode:
	put_unused_fd(fd);
err_fd:
	put_task_struct(current->group_leader);
	kfree(task);
err:
	mutex_unlock(&hpa_trace_lock);
}

struct hpa_fd_iterdata {
	int fd_ref_size;
	int fd_ref_cnt;
};

static int hpa_traverse_filetable(const void *t, struct file *file, unsigned fd)
{
	struct hpa_fd_iterdata *iterdata = (struct hpa_fd_iterdata*)t;
	struct dma_buf *dmabuf;

	if (!is_dma_buf_file(file))
		return 0;

	dmabuf = file->private_data;

	iterdata->fd_ref_cnt++;
	iterdata->fd_ref_size += dmabuf->size >> 10;

	return 0;
}

/*
 * The HPA buffers are referenced by attached device, and file descriptor of process.
 * These buffers don't need to consider mmap count because secure buffer can not be mmaped.
 * The file descriptor might be tracked on dma-buf-trace because that interates dma-buf
 * file descriptor when show_mem() calls, so we only show devices to attach the hpa buffers.
 */
void show_hpa_trace_handler(void *data, unsigned int filter, nodemask_t *nodemask)
{
	static DEFINE_RATELIMIT_STATE(hpa_map_ratelimit, HZ * 10, 1);
	struct hpa_trace_task *task;
	int i;
	bool show_header = false;

	if (!__ratelimit(&hpa_map_ratelimit))
		return;

	if (in_interrupt()) {
		pr_info("log is skipped in interrupt context\n");
		return;
	}

	if (!mutex_trylock(&hpa_trace_lock))
		return;

	if (!list_empty(&hpa_task_list))
		pr_info("%20s %5s %10s %10s (HPA allocation tasks)\n",
			"comm", "pid", "fdrefcnt", "fdsize(kb)");

	list_for_each_entry(task, &hpa_task_list, node) {
		struct hpa_fd_iterdata iterdata;
		bool locked;

		iterdata.fd_ref_cnt = iterdata.fd_ref_size = 0;

		locked = spin_trylock(&task->task->alloc_lock);
		if (locked) {
			iterate_fd(task->task->files, 0, hpa_traverse_filetable, &iterdata);
			spin_unlock(&task->task->alloc_lock);
		}

		pr_info("%20s %5d %10d %10d %s\n", task->task->comm, task->task->pid,
			iterdata.fd_ref_cnt, iterdata.fd_ref_size,
			locked ? "" : "-> skip by lock contention");
	}

	for (i = 0; i < hpa_map_devices; i++) {
		if (!hpa_map_lists[i].size && !hpa_map_lists[i].mapcnt)
			continue;

		if (!show_header) {
			pr_info("HPA attached device list:\n");
			pr_info("%20s %20s %10s\n", "attached device", "size(kb)", "mapcount");

			show_header = true;
		}

		pr_info("%20s %20zu %10lu\n", dev_name(hpa_map_lists[i].dev),
			hpa_map_lists[i].size, hpa_map_lists[i].mapcnt);
	}
	mutex_unlock(&hpa_trace_lock);
}
