// SPDX-License-Identifier: GPL-2.0
/**
 * Perfetto-compatible trace events for Samsung DMA heap allocator layer
 *
 * Copyright (C) 2026 Samsung Electronics Co., Ltd.
 * Authors: Dongseok Lee <drain.lee@samsung.com>
 *
 * Defines tracepoints for heap allocation operations using Perfetto kernel
 * track event conventions. Events include slice tracks for operation timing
 * (B/E/I) and counter tracks for statistics/fallback metrics.
 *
 * TRACE_SYSTEM: samsung_dma_heap
 * tracefs: /sys/kernel/tracing/events/samsung_dma_heap/
 *
 * Event types:
 *   - samsung_dma_heap_op: allocation/deallocation/failure operations
 *   - samsung_dma_heap_shrinker: reclaim operations
 *   - samsung_dma_heap_stat: counter metrics (e.g., size, count)
 *   - samsung_dma_heap_fallback: fallback frequency tracking
 */

#undef TRACE_SYSTEM
#define TRACE_SYSTEM samsung_dma_heap

#if !defined(_TRACE_SAMSUNG_DMA_HEAP_H) || defined(TRACE_HEADER_MULTI_READ)
#define _TRACE_SAMSUNG_DMA_HEAP_H

#include <linux/tracepoint.h>

#include <linux/version.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0)
#define __assign_str(src, dst) __assign_str(dst)
#endif

TRACE_EVENT(samsung_dma_heap_op,

	TP_PROTO(char type, const char *slice, const char *track,
		 size_t size, unsigned long ino, int err,
		 unsigned int flags, const char *note, ktime_t begin_elapsed),

	TP_ARGS(type, slice, track, size, ino, err, flags, note, begin_elapsed),

	TP_STRUCT__entry(
		__field(char,		track_event_type)
		__string(slice_name,	slice)
		__string(track_name,	track)
		__field(ktime_t,	begin_elapsed)
		__field(size_t,		size)
		__field(unsigned long,	ino)
		__field(int,		err)
		__field(unsigned int,	flags)
		__string(note,		note)
	),

	TP_fast_assign(
		__entry->track_event_type = type;
		__assign_str(slice_name, slice);
		__assign_str(track_name, track);
		__entry->begin_elapsed = begin_elapsed;
		__entry->size = size;
		__entry->ino = ino;
		__entry->err = err;
		__entry->flags = flags;
		__assign_str(note, note);
	),

	TP_printk("type=%c slice=%s track=%s size=%zu ino=%lu err=%d flags=%#x note=%s %s=%lldus",
		  __entry->track_event_type,
		  __get_str(slice_name),
		  __get_str(track_name),
		  __entry->size,
		  __entry->ino,
		  __entry->err,
		  __entry->flags,
		  __get_str(note),
		  __entry->track_event_type == 'E' ? "elapsed" : "begin",
		  ktime_to_us(__entry->begin_elapsed))
);

TRACE_EVENT(samsung_dma_heap_shrinker,

	TP_PROTO(char type, const char *slice, const char *track,
		 unsigned long nr_to_scan, unsigned long freed),

	TP_ARGS(type, slice, track, nr_to_scan, freed),

	TP_STRUCT__entry(
		__field(char,		track_event_type)
		__string(slice_name,	slice)
		__string(track_name,	track)
		__field(unsigned long,	nr_to_scan)
		__field(unsigned long,	freed)
	),

	TP_fast_assign(
		__entry->track_event_type = type;
		__assign_str(slice_name, slice);
		__assign_str(track_name, track);
		__entry->nr_to_scan = nr_to_scan;
		__entry->freed = freed;
	),

	TP_printk("type=%c slice=%s track=%s nr_to_scan=%lu freed=%lu",
		  __entry->track_event_type,
		  __get_str(slice_name),
		  __get_str(track_name),
		  __entry->nr_to_scan,
		  __entry->freed)
);

TRACE_EVENT(samsung_dma_heap_stat,

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

TRACE_EVENT(samsung_dma_heap_fallback,

	TP_PROTO(s64 count, const char *track),

	TP_ARGS(count, track),

	TP_STRUCT__entry(
		__field(s64,		counter_value)
		__string(track_name,	track)
	),

	TP_fast_assign(
		__entry->counter_value = count;
		__assign_str(track_name, track);
	),

	TP_printk("count=%lld track=%s",
		  __entry->counter_value,
		  __get_str(track_name))
);

#endif /* _TRACE_SAMSUNG_DMA_HEAP_H */

/* This part must be outside protection */
#include <trace/define_trace.h>
