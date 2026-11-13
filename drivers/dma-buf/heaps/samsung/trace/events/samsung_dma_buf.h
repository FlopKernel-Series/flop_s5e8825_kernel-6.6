// SPDX-License-Identifier: GPL-2.0
/**
 * Perfetto-compatible trace events for Samsung DMA-BUF lifecycle layer
 *
 * Copyright (C) 2026 Samsung Electronics Co., Ltd.
 * Authors: Dongseok Lee <drain.lee@samsung.com>
 *
 * Defines tracepoints for buffer lifecycle operations after creation.
 * Tracks attach/detach, map/unmap, cpu_access, mmap, vmap, and release
 * operations. Separate from the allocator layer (samsung_dma_heap) for
 * selective enable and different event frequency.
 *
 * TRACE_SYSTEM: samsung_dma_buf
 * tracefs: /sys/kernel/tracing/events/samsung_dma_buf/
 *
 * Event types:
 *   - samsung_dma_buf_op: buffer usage operations (attach, map, etc.)
 *   - samsung_dma_buf_lifecycle: buffer lifecycle counters
 */

#undef TRACE_SYSTEM
#define TRACE_SYSTEM samsung_dma_buf

#if !defined(_TRACE_SAMSUNG_DMA_BUF_H) || defined(TRACE_HEADER_MULTI_READ)
#define _TRACE_SAMSUNG_DMA_BUF_H

#include <linux/tracepoint.h>

#include <linux/version.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0)
#define __assign_str(src, dst) __assign_str(dst)
#endif

TRACE_EVENT(samsung_dma_buf_op,

	TP_PROTO(char type, const char *slice, const char *track,
		 unsigned long ino, size_t size, int err,
		 int direction, const char *device, ktime_t begin_elapsed),

	TP_ARGS(type, slice, track, ino, size, err, direction, device, begin_elapsed),

	TP_STRUCT__entry(
		__field(char,		track_event_type)
		__string(slice_name,	slice)
		__string(track_name,	track)
		__field(ktime_t,	begin_elapsed)
		__field(unsigned long,	ino)
		__field(size_t,		size)
		__field(int,		err)
		__field(int,		direction)
		__string(device,	device)
	),

	TP_fast_assign(
		__entry->track_event_type = type;
		__assign_str(slice_name, slice);
		__assign_str(track_name, track);
		__entry->begin_elapsed = begin_elapsed;
		__entry->ino = ino;
		__entry->size = size;
		__entry->err = err;
		__entry->direction = direction;
		__assign_str(device, device);
	),

	TP_printk("type=%c slice=%s track=%s ino=%lu size=%zu err=%d dir=%d dev=%s %s=%lldus",
		  __entry->track_event_type,
		  __get_str(slice_name),
		  __get_str(track_name),
		  __entry->ino,
		  __entry->size,
		  __entry->err,
		  __entry->direction,
		  __get_str(device),
		  __entry->track_event_type == 'E' ? "elapsed" : "begin",
		  ktime_to_us(__entry->begin_elapsed))
);

TRACE_EVENT(samsung_dma_buf_lifecycle,

	TP_PROTO(s64 value, const char *track),

	TP_ARGS(value, track),

	TP_STRUCT__entry(
		__field(s64,		counter_value)
		__string(track_name,	track)
		__field(s8,		scope_id)
	),

	TP_fast_assign(
		__entry->counter_value = value;
		__assign_str(track_name, track);
		__entry->scope_id = 0;
	),

	TP_printk("value=%lld track=%s",
		  __entry->counter_value,
		  __get_str(track_name))
);

#endif /* _TRACE_SAMSUNG_DMA_BUF_H */

/* This part must be outside protection */
#include <trace/define_trace.h>
