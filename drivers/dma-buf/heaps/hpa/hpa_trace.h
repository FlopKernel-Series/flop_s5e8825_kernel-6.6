// SPDX-License-Identifier: GPL-2.0
/*
 * DMABUF HPA heap trace for Samsung
 *
 * Copyright (C) 2021 Samsung Electronics Co., Ltd.
 * Author: <hyesoo.yu@samsung.com> for Samsung
 */
#ifndef __HPA_TRACE_H__
#define __HPA_TRACE_H__

#include <linux/fdtable.h>
#include <linux/dma-buf.h>

void hpa_trace_map(struct dma_buf *dmabuf, struct device *dev);
void hpa_trace_unmap(struct dma_buf *dmabuf, struct device *dev);
void hpa_trace_add_task(void);
void show_hpa_trace_handler(void *data, unsigned int filter, nodemask_t *nodemask);

#endif/*__HPA_TRACE_H__*/
