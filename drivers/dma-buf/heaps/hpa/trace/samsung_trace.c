// SPDX-License-Identifier: GPL-2.0
/**
 * Tracepoint creation and event registration for Samsung DMA heaps
 *
 * Copyright (C) 2026 Samsung Electronics Co., Ltd.
 * Authors: Dongseok Lee <drain.lee@samsung.com>
 *
 * Defines CREATE_TRACE_POINTS to instantiate tracepoint definitions
 * from event headers. This is the single compilation unit that creates
 * the actual tracepoint structures, shared across the subsystem.
 *
 * Includes event headers for heap allocator operations (samsung_dma_heap)
 * and buffer lifecycle operations (samsung_dma_buf).
 */

#include <linux/export.h>

/* CREATE_TRACE_POINTS must be defined in exactly ONE .c file */
#define CREATE_TRACE_POINTS
#include "events/samsung_dma_heap.h"
#include "events/samsung_dma_buf.h"
