// SPDX-License-Identifier: GPL-2.0
/*
 * DMABUF HPA heap exporter for Samsung
 *
 * Copyright (C) 2021 Samsung Electronics Co., Ltd.
 * Author: <hyesoo.yu@samsung.com> for Samsung
 *         <drain.lee@samsung.com> for Samsung
 */
#define pr_fmt(fmt) "hpa-heap: " fmt

#include <linux/anon_inodes.h>
#include <linux/cma.h>
#include <linux/debugfs.h>
#include <linux/device.h>
#include <linux/dma-buf.h>
#include <linux/dma-direct.h>
#include <linux/dma-heap.h>
#include <linux/err.h>
#include <linux/fdtable.h>
#include <linux/genalloc.h>
#include <linux/gfp.h>
#include <linux/highmem.h>
#include <linux/iommu.h>
#include <linux/kmemleak.h>
#include <linux/ktime.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_reserved_mem.h>
#include <linux/platform_device.h>
#include <linux/scatterlist.h>
#include <linux/seq_file.h>
#include <linux/slab.h>
#include <linux/list_sort.h>
#include <trace/hooks/mm.h>

#include "trace/samsung_trace.h"
#include "utils/folio-list.h"
#include "utils/prepare-folio.h"
#include "utils/generic-folio-pool.h"
#include "secure_buffer.h"
#include "secure/ppmp-mapping.h"
#include "hpa_trace.h"
#include "hpa_debug.h"

struct hpa_dma_heap {
	const char *name;
	struct dma_heap *dma_heap;
	struct gen_folio_pool *pool;
	struct secure_ctx *sec_ctx;
	unsigned int protection_id;

	/* stats */
	atomic_long_t total_bytes;
	atomic_long_t hpa_alloc_fail_count;
	atomic_long_t sec_map_fail_count;
	atomic_long_t sec_unmap_fail_count;
};

struct hpa_dma_buffer {
	struct hpa_dma_heap *heap;
	struct sg_table sg_table;
	unsigned long ino;
	void *priv;
};

static struct secure_ctx hpa_global_secure_ctx;

#define TRACE_HPA_STAT_POOL_SIZE(__gen_pool) do {\
	char __track_name[64] = {}; \
	snprintf(__track_name, sizeof(__track_name) - 1, "%.50s/size", (__gen_pool)->name); \
	TRACE_HEAP_STAT(__track_name, gen_folio_pool_size(__gen_pool)); \
} while (0)

#define TRACE_HPA_STAT_HEAP_SIZE(__hpa_heap) do {\
	char __track_name[64] = {}; \
	snprintf(__track_name, sizeof(__track_name) - 1, "%.50s/size", (__hpa_heap)->name); \
	TRACE_HEAP_STAT(__track_name, atomic_long_read(&(__hpa_heap)->total_bytes)); \
} while (0)

#define TRACE_HPA_STAT_FAIL_COUNT(__hpa_heap, __field_name) do {\
	char __track_name[64] = {}; \
	snprintf(__track_name, sizeof(__track_name) - 1, "%.50s/"#__field_name, (__hpa_heap)->name); \
	TRACE_HEAP_STAT(__track_name, atomic_long_inc_return(&(__hpa_heap)->__field_name)); \
} while (0)

static struct gen_folio_pool hpa_global_pool;

static void hpa_global_pool_evict(struct gen_folio_pool *gen_pool, struct list_head *folio_list)
{
	struct folio *folio = NULL, *tmp;

	list_for_each_entry_safe(folio, tmp, folio_list, lru) {
		list_del(&folio->lru);
		folio_put(folio);
	}

	TRACE_HPA_STAT_POOL_SIZE(gen_pool);
}

const struct heap_pool_ops hpa_global_pool_ops = {
	.evict = hpa_global_pool_evict,
};

static struct hpa_dma_heap hpa_heaps[] = {
	{
		.name = "vframe-secure",
		.protection_id = 5,
	},
	{
		.name = "system-secure-vframe-secure",
		.protection_id = 5,
	},
	{
		.name = "vscaler-secure",
		.protection_id = 6,
	},
	{
		.name = "system-secure-gpu_buffer-secure",
		.protection_id = 9,
	},
};

#define MAX_EXCEPTION_AREAS 4
static phys_addr_t hpa_exception_areas[MAX_EXCEPTION_AREAS][2];
static int nr_hpa_exception;

#define HPA_DEFAULT_ORDER 4
#define HPA_CHUNK_SIZE  (PAGE_SIZE << HPA_DEFAULT_ORDER)
#define HPA_PAGE_COUNT(len) (ALIGN(len, HPA_CHUNK_SIZE) / HPA_CHUNK_SIZE)
#define HPA_MAX_CHUNK_COUNT ((PAGE_SIZE * 2) / sizeof(struct page *))

static int hpa_compare_folio_list(void *priv, const struct list_head *lru1,
	const struct list_head *lru2)
{
	if (*((unsigned long *)lru1) > (*((unsigned long *)lru2)))
		return 1;
	else if (*((unsigned long *)lru1) < (*((unsigned long *)lru2)))
		return -1;
	return 0;
}

static struct hpa_dma_buffer* hpa_dma_buffer_alloc(struct hpa_dma_heap *hpa_heap,
						   size_t size, unsigned long nents)
{
	struct hpa_dma_buffer *buffer;

	buffer = kzalloc(sizeof(*buffer), GFP_KERNEL);
	if (!buffer)
		return ERR_PTR(-ENOMEM);

	if (sg_alloc_table(&buffer->sg_table, nents, GFP_KERNEL)) {
		pr_err("failed to allocate sgtable with %lu entry\n", nents);
		kfree(buffer);
		return ERR_PTR(-ENOMEM);
	}

	buffer->heap = hpa_heap;

	return buffer;
}

void hpa_dma_buffer_free(struct hpa_dma_buffer *buffer)
{
	sg_free_table(&buffer->sg_table);
	kfree(buffer);
}

static struct sg_table *hpa_dup_sg_table(struct sg_table *table)
{
	struct sg_table *new_table;
	int ret, i;
	struct scatterlist *sg, *new_sg;

	new_table = kzalloc(sizeof(*new_table), GFP_KERNEL);
	if (!new_table)
		return ERR_PTR(-ENOMEM);

	ret = sg_alloc_table(new_table, table->orig_nents, GFP_KERNEL);
	if (ret) {
		kfree(new_table);
		return ERR_PTR(-ENOMEM);
	}

	new_sg = new_table->sgl;
	for_each_sgtable_sg(table, sg, i) {
		sg_set_page(new_sg, sg_page(sg), sg->length, sg->offset);
		new_sg = sg_next(new_sg);
	}

	return new_table;
}

static struct sg_table *hpa_heap_map_dma_buf(struct dma_buf_attachment *a,
					     enum dma_data_direction direction)
{
	struct hpa_dma_buffer *buffer = a->dmabuf->priv;
	struct sg_table *table;

	TRACE_BUF_OP(op, a->dmabuf->exp_name, "map", a->dmabuf, dev_name(a->dev));

	table = hpa_dup_sg_table(&buffer->sg_table);
	if (IS_ERR(table))
		TRACE_RETURN_ERR_PTR(op, PTR_ERR(table));

	if (dev_iommu_fwspec_get(a->dev)) {
		struct buffer_prot_info *info = buffer->priv;

		sg_dma_address(table->sgl) = info->dma_addr;
		sg_dma_len(table->sgl) = info->chunk_count * info->chunk_size;
		table->nents = 1;
	} else {
		TRACE_BUF_STAGE(op, stage, "map/dma-map-sg", a->dmabuf, dev_name(a->dev)) {
			stage.err = dma_map_sgtable(a->dev, table, direction, a->dma_map_attrs);
			if (stage.err) {
				sg_free_table(table);
				kfree(table);

				TRACE_RETURN_ERR_PTR(op, stage.err);
			}
		}
	}

	hpa_trace_map(a->dmabuf, a->dev);

	hpa_event_record(HPA_EVENT_DMA_MAP, a->dmabuf, op.begin, op.ino);

	return table;
}

static void hpa_heap_unmap_dma_buf(struct dma_buf_attachment *a,
				   struct sg_table *table,
				   enum dma_data_direction direction)
{
	TRACE_BUF_OP(op, a->dmabuf->exp_name, "unmap", a->dmabuf, dev_name(a->dev));

	hpa_trace_unmap(a->dmabuf, a->dev);

	if (!dev_iommu_fwspec_get(a->dev))
		TRACE_BUF_STAGE(op, stage, "unmap/dma-unmap-sg", a->dmabuf, dev_name(a->dev))
			dma_unmap_sgtable(a->dev, table, direction, a->dma_map_attrs);

	sg_free_table(table);
	kfree(table);

	hpa_event_record(HPA_EVENT_DMA_UNMAP, a->dmabuf, op.begin, op.ino);
}

static int hpa_heap_mmap(struct dma_buf *dmabuf, struct vm_area_struct *vma)
{
	pr_err("mmap() to protected buffer is not allowed\n");
	return -EACCES;
}

static int hpa_heap_vmap(struct dma_buf *dmabuf, struct iosys_map *map)
{
	pr_err("vmap() to protected buffer is not allowed\n");
	return -EACCES;
}

static void hpa_heap_dma_buf_release(struct dma_buf *dmabuf)
{
	struct hpa_dma_buffer *buffer = dmabuf->priv;
	struct sg_table *sgt = &buffer->sg_table;
	struct scatterlist *sg;
	int i;
	int unprot_err;

	TRACE_HEAP_OP(op, buffer->heap, "release", dmabuf->size, 0, buffer->ino);

	TRACE_HEAP_STAGE(op, stage, "release/sec-unmap", dmabuf->size) {
		unprot_err = secure_unmap(buffer->heap->sec_ctx, buffer->priv);
		stage.err = unprot_err;
	}

	if (unprot_err) {
		TRACE_HPA_STAT_FAIL_COUNT(buffer->heap, sec_unmap_fail_count);

		pr_crit("failed(%d, ino %lu) to secure unmap %zu bytes from '%s' heap",
			unprot_err, buffer->ino, dmabuf->size, buffer->heap->name);
	} else {
		for_each_sgtable_sg(sgt, sg, i)
			gen_folio_pool_put(buffer->heap->pool, page_folio(sg_page(sg)));

		TRACE_HPA_STAT_POOL_SIZE(buffer->heap->pool);

		atomic_long_sub(dmabuf->size, &buffer->heap->total_bytes);
		TRACE_HPA_STAT_HEAP_SIZE(buffer->heap);
	}

	hpa_dma_buffer_free(buffer);

	hpa_event_record(HPA_EVENT_FREE, dmabuf, op.begin, op.ino);
}

#define HPA_HEAP_FLAG_PROTECTED BIT(1)

static int hpa_heap_dma_buf_get_flags(struct dma_buf *dmabuf, unsigned long *flags)
{
	*flags = HPA_HEAP_FLAG_PROTECTED;

	return 0;
}

const struct dma_buf_ops hpa_dma_buf_ops = {
	.map_dma_buf = hpa_heap_map_dma_buf,
	.unmap_dma_buf = hpa_heap_unmap_dma_buf,
	.mmap = hpa_heap_mmap,
	.vmap = hpa_heap_vmap,
	.release = hpa_heap_dma_buf_release,
	.get_flags = hpa_heap_dma_buf_get_flags,
};

static struct dma_buf *hpa_heap_allocate(struct dma_heap *heap, unsigned long len,
				    u32 fd_flags, u64 heap_flags)
{
	DEFINE_DMA_BUF_EXPORT_INFO(exp_info);
	struct hpa_dma_heap *hpa_heap = dma_heap_get_drvdata(heap);
	struct device *dev = dma_heap_get_dev(heap);
	struct hpa_dma_buffer *buffer;
	struct dma_buf *dmabuf;
	struct folio *folio = NULL, *tmp = NULL;
	unsigned long size, nr_chunks, nr_pool_chunks;
	LIST_HEAD(folio_list);
	int ret;

	TRACE_HEAP_OP(op, hpa_heap, "allocate", len, heap_flags, 0);

	size = ALIGN(len, HPA_CHUNK_SIZE);
	nr_chunks = size / HPA_CHUNK_SIZE;

	if (nr_chunks > HPA_MAX_CHUNK_COUNT) {
		pr_err("Too big size %lu (HPA limited size %lu)\n", len,
		       HPA_MAX_CHUNK_COUNT * HPA_CHUNK_SIZE);
		TRACE_RETURN_ERR_PTR(op, -EINVAL);
	}

	TRACE_HEAP_STAGE(op, stage, "allocate/pool-get", size) {
		nr_pool_chunks = gen_folio_pool_get_order_list(hpa_heap->pool,
			HPA_DEFAULT_ORDER, &folio_list, nr_chunks);

		stage.size = HPA_CHUNK_SIZE * nr_pool_chunks;

		TRACE_HPA_STAT_POOL_SIZE(hpa_heap->pool);
	}

	if (nr_pool_chunks < nr_chunks) {
		const unsigned long nr_pages = nr_chunks - nr_pool_chunks;
		struct page **pages __free(kfree) =
		kmalloc_array(nr_pages, sizeof(*pages), GFP_KERNEL);
		LIST_HEAD(alloc_list);

		if (!pages)
			TRACE_RETURN_ERR_PTR(op, -ENOMEM);

		TRACE_HEAP_STAGE(op, stage, "allocate/alloc", HPA_CHUNK_SIZE * nr_pages) {
			ret = alloc_pages_highorder_except(HPA_DEFAULT_ORDER, pages, nr_pages,
							hpa_exception_areas, nr_hpa_exception);
			stage.err = ret;
			if (ret) {
				TRACE_HPA_STAT_FAIL_COUNT(hpa_heap, hpa_alloc_fail_count);
				goto err_buffer;
			}
		}

		folio_list_from_folio_array(nr_pages, (struct folio **)pages, &alloc_list);
		list_splice_init(&alloc_list, &folio_list);
	}

	buffer = hpa_dma_buffer_alloc(hpa_heap, size, nr_chunks);
	if (IS_ERR(buffer)) {
		ret = PTR_ERR(buffer);
		goto err_buffer;
	}

	list_sort(NULL, &folio_list, hpa_compare_folio_list);

	folio_list_to_sg_table(&folio_list, &buffer->sg_table);
	prep_clear_and_flush_sgtable(dev, &buffer->sg_table);

	TRACE_HEAP_STAGE(op, stage, "allocate/sec-map", HPA_CHUNK_SIZE * nr_chunks) {
		buffer->priv = secure_map(hpa_heap->sec_ctx, dev, &buffer->sg_table,
			hpa_heap->protection_id);
		if (IS_ERR(buffer->priv)) {
			TRACE_HPA_STAT_FAIL_COUNT(hpa_heap, sec_map_fail_count);
			ret = PTR_ERR(buffer->priv);
			stage.err = ret;
			goto err_prot;
		}
	}

	exp_info.ops = &hpa_dma_buf_ops;
	exp_info.exp_name = hpa_heap->name;
	exp_info.size = size;
	exp_info.flags = fd_flags;
	exp_info.priv = buffer;

	dmabuf = dma_buf_export(&exp_info);
	if (IS_ERR(dmabuf)) {
		ret = PTR_ERR(dmabuf);
		goto err_export;
	}

	buffer->ino = op.ino = file_inode(dmabuf->file)->i_ino;

	folio_list_unlink_all_unsafe(&folio_list);

	atomic_long_add(dmabuf->size, &hpa_heap->total_bytes);
	TRACE_HPA_STAT_HEAP_SIZE(hpa_heap);

	hpa_trace_add_task();

	hpa_event_record(HPA_EVENT_ALLOC, dmabuf, op.begin, op.ino);

	return dmabuf;

err_export:
	secure_unmap(hpa_heap->sec_ctx, buffer->priv);
err_prot:
	hpa_dma_buffer_free(buffer);
err_buffer:
	list_for_each_entry_safe(folio, tmp, &folio_list, lru) {
		list_del(&folio->lru);
		gen_folio_pool_put(hpa_heap->pool, folio);
	}

	pr_err("failed(%d) to alloc (len %zu, %#x %#llx) from '%s' heap",
	       ret, len, fd_flags, heap_flags, hpa_heap->name);

	TRACE_RETURN_ERR_PTR(op, ret);
}

static long hpa_heap_get_pool_size(struct dma_heap * heap)
{
	struct hpa_dma_heap *hpa_heap = dma_heap_get_drvdata(heap);

	return atomic_long_read(&hpa_heap->total_bytes);
}

static const struct dma_heap_ops hpa_heap_ops = {
	.allocate = hpa_heap_allocate,
	.get_pool_size = hpa_heap_get_pool_size,
};

static void hpa_add_exception_area(void)
{
	struct device_node *np;

	for_each_node_by_name(np, "dma_heap_exception_area") {
		int naddr = of_n_addr_cells(np);
		int nsize = of_n_size_cells(np);
		phys_addr_t base, size;
		const __be32 *prop;
		int len;
		int i;

		prop = of_get_property(np, "#address-cells", NULL);
		if (prop)
			naddr = be32_to_cpup(prop);

		prop = of_get_property(np, "#size-cells", NULL);
		if (prop)
			nsize = be32_to_cpup(prop);

		prop = of_get_property(np, "ppmpu-limit", &len);
		if (prop && len > 0) {
			base = (phys_addr_t)of_read_number(prop, naddr);

			hpa_exception_areas[0][0] = base;
			hpa_exception_areas[0][1] = -1;

			nr_hpa_exception++;
		}

		prop = of_get_property(np, "exception-range", &len);
		if (prop && len > 0) {
			int n_area = len / (sizeof(*prop) * (nsize + naddr));

			n_area += nr_hpa_exception;
			n_area = min_t(int, n_area, MAX_EXCEPTION_AREAS);

			for (i = nr_hpa_exception; i < n_area ; i++) {
				base = (phys_addr_t)of_read_number(prop, naddr);
				prop += naddr;
				size = (phys_addr_t)of_read_number(prop, nsize);
				prop += nsize;

				hpa_exception_areas[i][0] = base;
				hpa_exception_areas[i][1] = base + size - 1;
			}

			nr_hpa_exception = n_area;
		}
	}
}

static void show_hpa_heap_handler(void *data, unsigned int filter, nodemask_t *nodemask)
{
	struct hpa_dma_heap *heap = data;
	u64 total_size_kb = div_u64(atomic_long_read(&heap->total_bytes), 1024);

	if (total_size_kb)
		pr_info("%s: %llukb ", heap->name, total_size_kb);
}

static int hpa_dma_heap_probe(struct platform_device *pdev)
{
	struct dma_heap_export_info exp_info;
	struct dma_heap *dma_heap;
	int ret, i = 0;

	ret = secure_ppmp_init(&hpa_global_secure_ctx, "hpa_global_secure_ctx", NULL);
	if (ret)
		return ret;

	gen_folio_pool_init_ext(&hpa_global_pool, "hpa_global_pool",
		&hpa_global_pool_ops, BIT(HPA_DEFAULT_ORDER), 0, DEFAULT_SEEKS);

	for (i = 0; i < ARRAY_SIZE(hpa_heaps); i++) {
		exp_info.name = hpa_heaps[i].name;
		exp_info.priv = &hpa_heaps[i];
		exp_info.ops = &hpa_heap_ops;

		dma_heap = dma_heap_add(&exp_info);
		if (IS_ERR(dma_heap))
			return PTR_ERR(dma_heap);

		hpa_heaps[i].dma_heap = dma_heap;
		hpa_heaps[i].pool = &hpa_global_pool;
		hpa_heaps[i].sec_ctx = &hpa_global_secure_ctx;
		dma_coerce_mask_and_coherent(dma_heap_get_dev(dma_heap), DMA_BIT_MASK(36));
		register_trace_android_vh_show_mem(show_hpa_heap_handler, &hpa_heaps[i]);

		pr_info("Registered %s dma-heap successfully\n", hpa_heaps[i].name);
	}
	register_trace_android_vh_show_mem(show_hpa_trace_handler, NULL);

	hpa_add_exception_area();
	hpa_debug_init();

	return 0;
}

static const struct of_device_id hpa_dma_heap_of_match[] = {
	{ .compatible = "samsung,dma-heap-hpa" },
	{},
};

static struct platform_driver hpa_dma_heap_driver = {
	.probe  = hpa_dma_heap_probe,
	.driver = {
		.name           = "hpa-dma-heap",
		.of_match_table = hpa_dma_heap_of_match,
	},
};
builtin_platform_driver(hpa_dma_heap_driver);
