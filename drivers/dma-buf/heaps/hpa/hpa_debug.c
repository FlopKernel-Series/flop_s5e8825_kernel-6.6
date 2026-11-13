// SPDX-License-Identifier: GPL-2.0
/*
 * DMABUF HPA heap debug for Samsung
 *
 * Copyright (C) 2021 Samsung Electronics Co., Ltd.
 * Author: <hyesoo.yu@samsung.com> for Samsung
 */

#include <linux/types.h>
#include <linux/ktime.h>
#include <linux/seq_file.h>
#include <linux/debugfs.h>
#include <linux/dma-buf.h>

#include "hpa_debug.h"

#define HPA_EVENT_LOG	256
#define HPA_EVENT_CLAMP_ID(id) ((id) & (HPA_EVENT_LOG - 1))

static atomic_t hpa_eventid;

static char * const hpa_event_name[] = {
	"alloc",
	"free",
	"map_dma_buf",
	"unmap_dma_buf",
};

static struct hpa_event {
	ktime_t begin;
	ktime_t done;
	unsigned char heapname[16];
	unsigned long ino;
	size_t size;
	enum hpa_event_type type;
} hpa_events[HPA_EVENT_LOG];

void hpa_event_record(enum hpa_event_type type, struct dma_buf *dmabuf,
	ktime_t begin, unsigned long ino)
{
	int idx = HPA_EVENT_CLAMP_ID(atomic_inc_return(&hpa_eventid));
	struct hpa_event *event = &hpa_events[idx];

	event->begin = begin;
	event->done = ktime_get();
	strlcpy(event->heapname, dmabuf->exp_name, sizeof(event->heapname));
	event->ino = ino;
	event->size = dmabuf->size;
	event->type = type;
}

#if IS_ENABLED(CONFIG_DEBUG_FS)
static int hpa_event_show(struct seq_file *s, void *unused)
{
	int index = HPA_EVENT_CLAMP_ID(atomic_read(&hpa_eventid) + 1);
	int i = index;

	seq_printf(s, "%14s %18s %16s %16s %10s %10s\n",
		   "timestamp", "event", "name", "size(kb)", "ino",  "elapsed(us)");

	do {
		struct hpa_event *event = &hpa_events[HPA_EVENT_CLAMP_ID(i)];
		long elapsed = ktime_us_delta(event->done, event->begin);
		struct timespec64 ts = ktime_to_timespec64(event->begin);

		if (elapsed == 0)
			continue;

		seq_printf(s, "[%06lld.%06ld]", ts.tv_sec, ts.tv_nsec / NSEC_PER_USEC);
		seq_printf(s, "%18s %16s %16zd %10lu %10ld", hpa_event_name[event->type],
			   event->heapname, event->size >> 10, event->ino, elapsed);

		if (elapsed > 100 * USEC_PER_MSEC)
			seq_puts(s, " *");

		seq_puts(s, "\n");
	} while (HPA_EVENT_CLAMP_ID(++i) != index);

	return 0;
}

static int hpa_event_open(struct inode *inode, struct file *file)
{
	return single_open(file, hpa_event_show, inode->i_private);
}

static const struct file_operations hpa_event_fops = {
	.open = hpa_event_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

void hpa_debug_init(void)
{
	struct dentry *root = debugfs_create_dir("hpa", NULL);

	if (IS_ERR(root)) {
		pr_err("Failed to create debug directory for dma_heap");
		return;
	}

	if (IS_ERR(debugfs_create_file("event", 0444, root, NULL, &hpa_event_fops)))
		pr_err("Failed to create event file for dma_heap\n");
}
#endif
