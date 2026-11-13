// SPDX-License-Identifier: GPL-2.0
/*
 * DMABUF HPA heap debug for Samsung
 *
 * Copyright (C) 2021 Samsung Electronics Co., Ltd.
 * Author: <hyesoo.yu@samsung.com> for Samsung
 */
#ifndef __HPA_DEBUG_H__
#define __HPA_DEBUG_H__

#include <linux/ktime.h>
#include <linux/dma-buf.h>

enum hpa_event_type {
	HPA_EVENT_ALLOC = 0,
	HPA_EVENT_FREE,
	HPA_EVENT_DMA_MAP,
	HPA_EVENT_DMA_UNMAP,
};

#if IS_ENABLED(CONFIG_DEBUG_FS)
void hpa_debug_init(void);
#else
static inline void hpa_debug_init(void) {}
#endif

void hpa_event_record(enum hpa_event_type type, struct dma_buf *dmabuf,
	ktime_t begin, unsigned long ino);

#endif/*__HPA_DEBUG_H__*/
