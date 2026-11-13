// SPDX-License-Identifier: GPL-2.0
/**
 * Cleanup-based trace helpers for Samsung DMA heaps
 *
 * Copyright (C) 2026 Samsung Electronics Co., Ltd.
 * Authors: Dongseok Lee <drain.lee@samsung.com>
 *
 * Provides RAII-style trace scope management using cleanup.h DEFINE_CLASS.
 * Automatic 'B' (begin) event emission on entry and 'E' (end) event emission
 * on scope exit, ensuring proper event pairing on all code paths.
 *
 * Includes helper macros for heap operations (TRACE_HEAP_OP) and buffer
 * operations (TRACE_BUF_OP) with error tracking and stat counters.
 */

#ifndef __SAMSUNG_TRACE_H__
#define __SAMSUNG_TRACE_H__

#include <linux/cleanup.h>
#include <linux/dma-heap.h>
#include <linux/ktime.h>

/* Pull in tracepoint declarations (not CREATE_TRACE_POINTS) */
#include "./events/samsung_dma_heap.h"
#include "./events/samsung_dma_buf.h"

/* ====================================================================
 * Scope context structs
 * ==================================================================== */

struct heap_trace_scope {
	const char	*__track_name;
	const char	*__slice_name;
	size_t		size;
	unsigned long	ino;
	int		err;
	unsigned int	flags;
	const char	*note;
	ktime_t begin;
};

struct buf_trace_scope {
	const char	*__track_name;
	const char	*__slice_name;
	unsigned long	ino;
	size_t		size;
	int		err;
	int		direction;
	const char	*device;
	ktime_t begin;
};

/* ====================================================================
 * DEFINE_CLASS for automatic 'B'/'E' pairing
 * ==================================================================== */

DEFINE_CLASS(heap_op_trace, struct heap_trace_scope,
	/* destructor: emit 'E' with current err/ino/note */
	({
		const ktime_t elapsed = ktime_sub(ktime_get(), _T.begin);
		trace_samsung_dma_heap_op('E', _T.__slice_name, _T.__track_name,
					_T.size, _T.ino, _T.err, 0,
					_T.note ? _T.note : "", elapsed);
	}),
	/* constructor: emit 'B', return initialized struct */
	({
		const ktime_t begin = ktime_get();
		trace_samsung_dma_heap_op('B', __slice, __track,
					  __size, __ino, 0, __flags, "", begin);
		(struct heap_trace_scope){
			.__track_name = __track,
			.__slice_name = __slice,
			.size       = __size,
			.ino       = __ino,
			.flags      = __flags,
			.note       = "",
			.begin      = begin,
		};
	}),
	const char *__track, const char *__slice,
	size_t __size, unsigned int __flags, unsigned long __ino)

DEFINE_CLASS(buf_op_trace, struct buf_trace_scope,
	({
		const ktime_t elapsed = ktime_sub(ktime_get(), _T.begin);
		trace_samsung_dma_buf_op('E', _T.__slice_name, _T.__track_name,
					_T.ino, _T.size, _T.err,
					_T.direction, _T.device ? _T.device : "", elapsed);
	}),
	({
		const ktime_t begin = ktime_get();
		trace_samsung_dma_buf_op('B', __slice, __track,
					__ino, __size, 0, -1, __dev, begin);
		(struct buf_trace_scope){
			.__track_name = __track,
			.__slice_name = __slice,
			.ino        = __ino,
			.size       = __size,
			.direction  = -1,
			.device     = __dev,
			.begin      = begin,
		};
	}),
	const char *__track, const char *__slice,
	unsigned long __ino, size_t __size, const char *__dev)

/* ====================================================================
 * Trace common helper macros
 * ==================================================================== */

#define TRACE_RETURN_ERR_WITH_NOTE(var, __err, __note)		\
	return ({ (var).note = (__note); ((var).err = (__err)); })

#define TRACE_RETURN_ERR(var, __err)		\
	return ((var).err = (__err))

#define TRACE_RETURN_ERR_PTR(var, __err)		\
	return ({ (var).err = (__err); ERR_PTR(__err); })

/* ====================================================================
 * Layer 1: samsung_dma_heap helper macros
 * ==================================================================== */

#define TRACE_HEAP_OP(var, heap, slice, size, flags, ino)		\
	CLASS(heap_op_trace, var)((heap)->name,	\
				  slice, size, flags, ino)

#define TRACE_HEAP_OP_RAW(var, heap_name, slice, size, flags, ino)	\
	CLASS(heap_op_trace, var)(heap_name, slice, size, flags, ino)

#define TRACE_HEAP_STAGE(parent_var, var, slice, size)			\
	for (CLASS(heap_op_trace, var)((parent_var).__track_name, slice, size, 0, (parent_var).ino),	\
		 *__done_##var = NULL; !__done_##var;		\
		 __done_##var = (void *)1)

#define TRACE_HEAP_INSTANT(heap, slice, size, err, note)	\
	trace_samsung_dma_heap_op('I', slice,			\
		(heap)->name, size, 0, err, 0, note, ktime_get())

#define TRACE_HEAP_INSTANT_RAW(heap_name, slice, size, err, note)	\
	trace_samsung_dma_heap_op('I', slice,			\
		heap_name, size, 0, err, 0, note, ktime_get())

#define TRACE_HEAP_STAT(track_name, value)			\
	trace_samsung_dma_heap_stat((s64)(value), track_name)

#define TRACE_HEAP_FALLBACK(track_name, count)			\
	trace_samsung_dma_heap_fallback((s64)(count), track_name)

/* ====================================================================
 * Layer 2: samsung_dma_buf helper macros
 * ==================================================================== */

#define TRACE_BUF_OP(var, heap_name, slice, dmabuf, dev_name)	\
	CLASS(buf_op_trace, var)(heap_name, slice,		\
		file_inode((dmabuf)->file)->i_ino,		\
		(dmabuf)->size, dev_name)

#define TRACE_BUF_STAGE(parent_var, var, slice, dmabuf, dev_name) \
	for (CLASS(buf_op_trace, var)((parent_var).__track_name, slice,		\
		file_inode((dmabuf)->file)->i_ino,		\
		(dmabuf)->size, dev_name),			\
		 *__done_##var = NULL; !__done_##var;		\
		 __done_##var = (void *)1)

#define TRACE_BUF_INSTANT(heap_name, slice, dmabuf, dev_name)	\
	trace_samsung_dma_buf_op('I', slice, heap_name,		\
		file_inode((dmabuf)->file)->i_ino,		\
		(dmabuf)->size, 0, -1, dev_name, ktime_get())

#define TRACE_BUF_STAT(track_name, value)			\
	trace_samsung_dma_buf_lifecycle((s64)(value), track_name)

#endif /* __SAMSUNG_TRACE_H__ */
