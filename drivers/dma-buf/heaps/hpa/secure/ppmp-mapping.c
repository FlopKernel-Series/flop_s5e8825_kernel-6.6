// SPDX-License-Identifier: GPL-2.0
/*
 * Secure PPMP Mapping for Samsung
 *
 * Copyright (C) 2021 Samsung Electronics Co., Ltd.
 * Author: <hyesoo.yu@samsung.com> for Samsung
 *         <drain.lee@samsung.com> for Samsung
 */
#define pr_fmt(fmt) "ppmp-mapping: " fmt

#include <linux/dma-direct.h>
#include <linux/dma-mapping.h>
#include <linux/kmemleak.h>
#include <linux/genalloc.h>
#include <linux/of.h>

#include "../secure_buffer.h"
#include "secure-ops.h"
#include "ppmp-mapping.h"

#define SMC_DRM_PPMP_PROT SMC_DRM_MEMORY_PROT
#define SMC_DRM_PPMP_UNPROT SMC_DRM_MEMORY_UNPROT

/* SMC DRM PPMP Error lists for Secure Buffer */
#define E_DRMDRV_LIST(X)                    \
	X(DUPLICATED_BUFFER, 0x7001)            \
	X(BUFFER_LIST_FULL, 0x7002)             \
	X(NOT_EXIST_IN_SEC_BUFFER_LIST, 0x7003) \
	X(OVERLAP_RESERVED_ASP_REGION, 0x7004)  \
	X(INVALID_BUFFER_TYPE, 0x7005)          \
	X(INVALID_CHUNK_COUNT, 0x7006)          \
	X(INVALID_MEMORY_CORVERAGE, 0x7007)     \
	X(BUFFER_PROTECT_FAILED, 0x7008)        \
	X(BUFFER_UNPROTECT_FAILED, 0x7009)

#define ENUM_GEN(name, value) E_DRMDRV_##name = value,
enum e_drmdrv_type {
	E_DRMDRV_LIST(ENUM_GEN)
};

#define STRING_GEN(name, value) case E_DRMDRV_##name: return #name;
static const char *e_drmdrv_str(int code)
{
	switch (code) {
	E_DRMDRV_LIST(STRING_GEN)
	default:
		return "Unknown";
	}
};

#define HPA_SECURE_DMA_BASE	0x80000000
#define HPA_SECURE_DMA_SIZE	0x80000000

/*
 * Alignment to a secure address larger than 16MiB is not beneficial because
 * the protection alignment just needs 64KiB by the buffer protection H/W and
 * the largest granule of H/W security firewall (the secure context of SysMMU)
 * is 16MiB.
 */
#define MAX_SECURE_VA_ALIGN	(SZ_16M)

static struct gen_pool *hpa_iova_pool;

int secure_ppmp_init(struct secure_ctx *ctx, const char *name, void *priv)
{
	struct device_node *np;
	phys_addr_t base = HPA_SECURE_DMA_BASE, size = HPA_SECURE_DMA_SIZE;
	int ret;

	if (hpa_iova_pool)
		return 0;

	if (!ctx)
		return -EINVAL;

	hpa_iova_pool = gen_pool_create(PAGE_SHIFT, -1);
	if (!hpa_iova_pool) {
		pr_err("failed to create HPA IOVA pool\n");
		return -ENOMEM;
	}

	for_each_node_by_name(np, "secure-iova-domain") {
		phys_addr_t domain_end;
		int naddr = of_n_addr_cells(np);
		int nsize = of_n_size_cells(np);
		const __be32 *prop;
		int len;

		prop = of_get_property(np, "#address-cells", NULL);
		if (prop)
			naddr = be32_to_cpup(prop);

		prop = of_get_property(np, "#size-cells", NULL);
		if (prop)
			nsize = be32_to_cpup(prop);

		prop = of_get_property(np, "domain-ranges", &len);
		if (prop && len > 0) {
			domain_end = (phys_addr_t)of_read_number(prop, naddr);
			prop += naddr;
			domain_end += (phys_addr_t)of_read_number(prop, nsize);
		} else {
			pr_err("%s: failed to get domain-ranges attributes\n", __func__);
			break;
		}

		prop = of_get_property(np, "hpa,reserved", &len);
		if (prop && len > 0) {
			size = (phys_addr_t)of_read_number(prop, nsize);
			base = domain_end - size;
		} else {
			pr_err("%s: failed to get hpa,reserved attributes\n", __func__);
			break;
		}
	}

	ret = gen_pool_add(hpa_iova_pool, base, size, -1);
	if (ret) {
		pr_err("failed to set address range of HPA IOVA pool\n");
		gen_pool_destroy(hpa_iova_pool);
		return ret;
	}
	pr_info("Add hpa iova ranges %pa-%pa\n", &base, &size);

	ctx->name = name ? : "";
	ctx->ops = &secure_ppmp_ops;
	ctx->priv = priv;

	return 0;
}

static unsigned long hpa_iova_alloc(unsigned long size, unsigned int align)
{
	unsigned long out_addr;
	struct genpool_data_align alignment = {
		.align = roundup_pow_of_two(clamp(align, PAGE_SIZE, MAX_SECURE_VA_ALIGN)),
	};

	if (WARN_ON_ONCE(!hpa_iova_pool))
		return 0;

	out_addr = gen_pool_alloc_algo(hpa_iova_pool, size, gen_pool_first_fit_align, &alignment);
	if (out_addr == 0)
		pr_err("failed alloc secure iova. %zu/%zu bytes used\n",
		       gen_pool_avail(hpa_iova_pool),
		       gen_pool_size(hpa_iova_pool));

	return out_addr;
}

static void hpa_iova_free(unsigned long addr, unsigned long size)
{
	gen_pool_free(hpa_iova_pool, addr, size);
}

static int ppmp_map(struct buffer_prot_info *protdesc, size_t desc_size, struct device *dev)
{
	unsigned long ret;
	dma_addr_t dma_addr = DMA_MAPPING_ERROR;

	dma_addr = dma_map_single(dev, protdesc, desc_size, DMA_TO_DEVICE);
	ret = ppmp_smc(SMC_DRM_PPMP_PROT, virt_to_phys(protdesc), 0, 0);
	dma_unmap_single(dev, dma_addr, desc_size, DMA_TO_DEVICE);

	if (ret) {
		pr_err("Map %s(%#lx), cmd %#x, dva=%#x, size=%#x x%u, flg=%u, phy=%#lx\n",
		       e_drmdrv_str(ret), ret, SMC_DRM_PPMP_PROT, protdesc->dma_addr,
		       protdesc->chunk_size, protdesc->chunk_count,
		       protdesc->flags, protdesc->bus_address);

		if (ret == E_DRMDRV_BUFFER_LIST_FULL)
			return -ENOSPC;
		else
			return -EACCES;
	}

	return 0;
}

static int ppmp_unmap(struct buffer_prot_info *protdesc, size_t desc_size, struct device *dev)
{
	unsigned long ret;
	dma_addr_t dma_addr = DMA_MAPPING_ERROR;

	dma_addr = dma_map_single(dev, protdesc, desc_size, DMA_TO_DEVICE);
	ret = ppmp_smc(SMC_DRM_PPMP_UNPROT, virt_to_phys(protdesc), 0, 0);
	dma_unmap_single(dev, dma_addr, desc_size, DMA_TO_DEVICE);

	if (ret) {
		pr_err("Unmap %s(%#lx), cmd %#x, dva=%#x, size=%#x x%u, flg=%u, phy=%#lx\n",
		       e_drmdrv_str(ret), ret, SMC_DRM_PPMP_UNPROT, protdesc->dma_addr,
		       protdesc->chunk_size, protdesc->chunk_count,
		       protdesc->flags, protdesc->bus_address);
		return -EACCES;
	}

	return 0;
}

static void *secure_ppmp_map(struct secure_ctx *ctx, struct device *dev,
	struct sg_table *sgt, unsigned int protection_id)
{
	struct ppmp_map_handle *handle = NULL;
	size_t chunk_size = 0;
	dma_addr_t dma_addr = 0;
	unsigned long size;
	int ret;

	if (sgt->nents == 0)
		return ERR_PTR(-EINVAL);

	chunk_size = folio_size(page_folio(sg_page(sgt->sgl)));
	size = chunk_size * sgt->nents;
	dma_addr = hpa_iova_alloc(size, max_t(unsigned int, chunk_size, PAGE_SIZE));
	if (!dma_addr)
		return ERR_PTR(-ENOMEM);

	handle = ppmp_map_handle_alloc(dev, sgt->nents);
	if (!handle) {
		ret = -ENOMEM;
		goto err_free_iova;
	}

	ret = ppmp_prot_payload_build(&handle->payload, sgt, protection_id, dma_addr);
	if (ret)
		goto err_free_handle;

	ret = ppmp_map(&handle->payload.protdesc, handle->payload_size, dev);
	if (ret)
		goto err_free_handle;

	/* returns a struct buffer_prot_info* for compatibility. */
	return &handle->payload.protdesc;

err_free_handle:
	ppmp_map_handle_free(handle);
err_free_iova:
	hpa_iova_free(dma_addr, size);
	return ERR_PTR(ret);
}

static int secure_ppmp_unmap(struct secure_ctx *ctx, void *handle)
{
	struct buffer_prot_info *protdesc = handle;
	struct ppmp_prot_payload* payload =
		container_of(protdesc, struct ppmp_prot_payload, protdesc);
	struct ppmp_map_handle *info =
		container_of(payload, struct ppmp_map_handle, payload);
	unsigned long size;
	int ret = 0;

	if (!handle)
		return -EINVAL;

	size = protdesc->chunk_count * protdesc->chunk_size;

	ret = ppmp_unmap(protdesc, info->payload_size, info->dev);
	if (!ret) {
		/*
		 * retain the secure device address if unprotection to its area fails.
		 * It might be unusable forever since we do not know the state of the
		 * secure world before returning error from ppmp_smc() above.
		 */
		hpa_iova_free(protdesc->dma_addr, size);
	}

	ppmp_map_handle_free(info);

	return ret;
}

const struct secure_ops secure_ppmp_ops = {
	.map = secure_ppmp_map,
	.unmap = secure_ppmp_unmap,
};
