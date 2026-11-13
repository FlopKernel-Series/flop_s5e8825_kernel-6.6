// SPDX-License-Identifier: GPL-2.0
/*
 * Secure PPMP Mapping for Samsung
 *
 * Copyright (C) 2021 Samsung Electronics Co., Ltd.
 * Author: <hyesoo.yu@samsung.com> for Samsung
 *         <drain.lee@samsung.com> for Samsung
 */

#ifndef __PPMP_MAPPING_H__
#define __PPMP_MAPPING_H__

#include <linux/device.h>
#include <linux/scatterlist.h>
#include <linux/types.h>

#include "../secure_buffer.h"
#include "secure-ops.h"

/* SMC protection payload with physical bus addresses */
struct ppmp_prot_payload {
	struct buffer_prot_info protdesc;
	unsigned long bus_addresses[];
};

/* PPMP mapping handle for secure memory allocation */
struct ppmp_map_handle {
	struct device *dev;
	unsigned int nents;
	size_t payload_size;

	____cacheline_aligned
	struct ppmp_prot_payload payload;
};

/**
 * ppmp_map_handle_alloc - Allocate and initialize PPMP map handle
 * @dev: device for DMA operations
 * @nents: number of scatterlist entries
 *
 * Return: allocated handle or NULL on failure
 */
static inline struct ppmp_map_handle *
ppmp_map_handle_alloc(struct device *dev, unsigned int nents)
{
	struct ppmp_map_handle *handle;
	const size_t handle_alloc_size = sizeof(struct ppmp_map_handle) +
					(sizeof(unsigned long) * (nents > 1 ? nents : 0));

	handle = kzalloc(handle_alloc_size, GFP_KERNEL);
	if (!handle)
		return NULL;

	handle->dev = dev;
	handle->nents = nents;
	handle->payload_size = handle_alloc_size - offsetof(struct ppmp_map_handle, payload);

	return handle;
}

/**
 * ppmp_map_handle_free - Free PPMP map handle
 * @handle: handle to free
 */
static inline void ppmp_map_handle_free(struct ppmp_map_handle *handle)
{
	kfree(handle);
}

/**
 * ppmp_prot_payload_build - Build PPMP protection payload from scatterlist
 * @payload: payload structure to fill
 * @sgt: scatterlist table with physical pages
 * @protection_id: protection ID for secure world
 * @dma_addr: IOVA address for protected memory
 *
 * Return: 0 on success, negative error on failure
 */
static inline int
ppmp_prot_payload_build(struct ppmp_prot_payload *payload,
			struct sg_table *sgt,
			unsigned int protection_id,
			dma_addr_t dma_addr)
{
	struct buffer_prot_info *protdesc;
	struct scatterlist *sg;
	int i = 0;

	if (sgt->nents == 0)
		return -EINVAL;

	protdesc = &payload->protdesc;
	protdesc->flags = protection_id;
	protdesc->dma_addr = (unsigned int)dma_addr;
	protdesc->chunk_size = folio_size(page_folio(sg_page(sgt->sgl)));

	if (sgt->nents == 1) {
		protdesc->chunk_count = 1;
		protdesc->bus_address = page_to_phys(sg_page(sgt->sgl));
	} else {
		protdesc->chunk_count = 0;

		for_each_sgtable_sg(sgt, sg, i) {
			if (folio_size(page_folio(sg_page(sg))) != protdesc->chunk_size)
				return -EINVAL;

			payload->bus_addresses[protdesc->chunk_count++] =
				virt_to_phys(page_address(sg_page(sg)));
		}

		if (protdesc->chunk_count != sgt->nents)
			return -EINVAL;

		protdesc->bus_address = virt_to_phys(payload->bus_addresses);
	}

	return 0;
}

extern const struct secure_ops secure_ppmp_ops;
int secure_ppmp_init(struct secure_ctx *ctx, const char *name, void *priv);

#endif/*__PPMP_MAPPING_H__*/
