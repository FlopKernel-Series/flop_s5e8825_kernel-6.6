// SPDX-License-Identifier: GPL-2.0
/**
 * Folio preparation operations for DMA buffer heaps
 *
 * Copyright (C) 2026 Samsung Electronics Co., Ltd.
 * Authors: Dongseok Lee <drain.lee@samsung.com>
 *
 * Clean, flush, and clear operations for folio lists, arrays,
 * and scatterlist tables.
 */

#ifndef _PREPARE_FOLIO_H_
#define _PREPARE_FOLIO_H_

#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/highmem.h>
#include <linux/dma-mapping.h>
#include <linux/list.h>
#include <linux/scatterlist.h>

/* =============================================================
   Internal Helpers
   ============================================================= */

/**
 * __prep_flush_folio - Flush folio (DMA_BIDIRECTIONAL)
 * @dev: Device for DMA operations
 * @folio: Folio to flush
 *
 * Maps and unmaps with DMA_BIDIRECTIONAL to clean+invalidate cache.
 */
static inline void __prep_flush_folio(struct device *dev, struct folio *folio)
{
	const dma_addr_t handle =
		dma_map_page(dev, folio_page(folio, 0), 0, folio_size(folio), DMA_BIDIRECTIONAL);
	if (handle != DMA_MAPPING_ERROR)
		dma_unmap_page(dev, handle, folio_size(folio), DMA_BIDIRECTIONAL);
}

/**
 * __prep_clear_folio - Clear folio content
 * @folio: Folio to clear
 *
 * Zeroes all pages in the folio.
 */
static inline void __prep_clear_folio(struct folio *folio)
{
	const unsigned long nr_pages = folio_nr_pages(folio);

	for (unsigned long idx = 0; idx < nr_pages; idx++)
		clear_highpage(folio_page(folio, idx));
}

/**
 * prep_clear_and_flush_sgtable - Clear and flush scatterlist table
 * @dev: Device for DMA operations
 * @sgt: Scatterlist table to clear and flush
 *
 * Zeroes content and flushes cache for all scatterlist entries.
 *
 * Return: 0 on success
 */
static inline int prep_clear_and_flush_sgtable(struct device *dev, struct sg_table *sgt)
{
	struct scatterlist *sg;
	int i;

	if (!sgt)
		return -EINVAL;

	for_each_sgtable_sg(sgt, sg, i) {
		struct folio *folio = page_folio(sg_page(sg));

		__prep_clear_folio(folio);
		__prep_flush_folio(dev, folio);
	}

	return 0;
}

#endif /* _PREPARE_FOLIO_H_ */
