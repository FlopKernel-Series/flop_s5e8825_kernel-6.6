// SPDX-License-Identifier: GPL-2.0
/**
 * Generic folio pool for memory management
 *
 * Copyright (C) 2026 Samsung Electronics Co., Ltd.
 * Authors: Dongseok Lee <drain.lee@samsung.com>
 *
 * Provides a pool of pre-allocated folios for efficient memory allocation.
 * Supports multiple orders and shrinker-based reclamation under memory pressure.
 */

#define pr_fmt(fmt) "dma-heap gen-pool: " fmt

#include <linux/errno.h>
#include <linux/printk.h>
#include <linux/cleanup.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/sort.h>
#include <linux/vmstat.h>
#include <linux/spinlock.h>
#include <linux/shrinker.h>
#include <linux/atomic.h>
#include <linux/bitops.h>
#include <kunit/test-bug.h>

#include "generic-folio-pool.h"
#include "folio-list.h"

/* ============================== Internal Helpers ============================== */

/**
 * get_folio_smallest_order - Get the smallest order folio that fits in max_count
 * @pool: The generic folio pool
 * @max_count: Maximum pages that can be reclaimed
 *
 * Search buckets in forward order (smallest first) to find the first folio that is
 * smaller than or equal to max_count. Returns NULL if all available folios are
 * larger than max_count (no smaller orders available).
 *
 * Return: Smallest available folio, or NULL
 */
static struct folio *get_folio_smallest_order(struct gen_folio_pool *pool,
					      unsigned long max_count)
{
	struct folio *folio;
	unsigned int i;

	for (i = 0; i < MAX_ORDER; i++) {
		if (!(pool->orders_bitmap & BIT(i)))
			continue;

		/* No smaller orders available */
		if (BIT(i) > max_count) {
			if (i == 0)  /* Smallest possible order */
				return NULL;
			continue;
		}

		folio = gen_folio_pool_get_order(pool, i);
		if (folio)
			return folio;
	}

	return NULL;
}

/* ============================== Shrinker ============================== */

static unsigned long pool_shrink_count(struct shrinker *shrinker,
				       struct shrink_control *sc)
{
	struct gen_folio_pool *gen_pool = container_of(shrinker, struct gen_folio_pool, shrinker);
	unsigned long total_pages = 0;
	unsigned int i;

	/* Sum up pages across all buckets */
	for (i = 0; i < MAX_ORDER; i++) {
		if (gen_pool->orders_bitmap & BIT(i)) {
			total_pages += max(0, atomic_long_read(&gen_pool->buckets[i].size)) >>
				       PAGE_SHIFT;
		}
	}

	/*
	 * An approximate count is sufficient for the shrinker.
	 */
	return total_pages;
}

static unsigned long pool_shrink_scan(struct shrinker *shrinker,
				      struct shrink_control *sc)
{
	struct gen_folio_pool *gen_pool = container_of(shrinker, struct gen_folio_pool, shrinker);
	unsigned long nr_freed = 0;
	LIST_HEAD(candidate_list);
	LIST_HEAD(failed_list);
	struct folio *folio;

	/*
	 * nr_to_scan is in pages. We reclaim folios until we reach the target.
	 * Start from smallest order buckets first to make room for larger allocations.
	 */
	/* Phase 1: Collect candidate folios from pool */
	while (nr_freed < sc->nr_to_scan) {
		folio = get_folio_smallest_order(gen_pool,
						 sc->nr_to_scan - nr_freed);

		if (!folio)
			break;

		INIT_LIST_HEAD(&folio->lru);
		list_add_tail(&folio->lru, &candidate_list);
		nr_freed += (1UL << folio_order(folio));
	}

	if (list_empty(&candidate_list))
		return 0;

	/* Phase 2: Pre-evict callback (partial failure support) */
	if (gen_pool->pool_ops->pre_evict) {
		int err = gen_pool->pool_ops->pre_evict(gen_pool, &candidate_list,
							&failed_list);

		if (err < 0) {
			nr_freed = folio_list_total_bytes(&candidate_list) >> PAGE_SHIFT;

			pr_warn("%s: pre_evict partial fail (%d), proceeding with %d/%d folios\n",
				gen_pool->name, err, folio_list_count(&candidate_list),
				folio_list_count(&candidate_list) + folio_list_count(&failed_list));
		}
	}
	/* else: No pre_evict - all succeed by default (remain in candidate_list) */

	/* Phase 3: Evict successful folios (remain in candidate_list) */
	if (!list_empty(&candidate_list)) {
		gen_pool->pool_ops->evict(gen_pool, &candidate_list);
	}

	/* Phase 4: Put back failed folios */
	while (!list_empty(&failed_list)) {
		folio = list_first_entry(&failed_list, struct folio, lru);
		list_del(&folio->lru);
		gen_folio_pool_put(gen_pool, folio);
	}

	return nr_freed;
}

/* ============================== Multi-Order Public API ============================== */

/**
 * gen_folio_pool_get_order - Retrieve a folio of specific order from the pool
 * @gen_pool: The generic folio pool to retrieve from
 * @order: The folio order to retrieve
 *
 * Removes and returns a folio of the specified order from the pool.
 * The caller takes ownership of the folio and is responsible for releasing
 * it back via gen_folio_pool_put().
 *
 * Return: A pointer to the folio, or NULL if no folio of this order exists
 */
struct folio *gen_folio_pool_get_order(struct gen_folio_pool *gen_pool,
				       unsigned int order)
{
	struct order_bucket *bucket;
	struct folio *folio = NULL;

	if (order >= MAX_ORDER || !(gen_pool->orders_bitmap & BIT(order)))
		return NULL;

	bucket = &gen_pool->buckets[order];

	scoped_guard(spinlock, &bucket->lock) {
		folio = list_first_entry_or_null(&bucket->folio_list,
						 struct folio, lru);
		if (!folio)
			return NULL;

		list_del(&folio->lru);
	}

	atomic_long_dec(&bucket->count);
	atomic_long_sub(folio_size(folio), &bucket->size);

	node_stat_sub_folio(folio, NR_KERNEL_MISC_RECLAIMABLE);

	return folio;
}

/**
 * gen_folio_pool_get_order_list - Retrieve multiple folios of specific order from the pool
 * @gen_pool: The generic folio pool to retrieve from
 * @order: The folio order to retrieve
 * @folio_list: List to store retrieved folios
 * @nr_folios: Number of folios requested
 *
 * Return: Number of folios actually retrieved (0 to @nr_folios)
 */
unsigned int gen_folio_pool_get_order_list(struct gen_folio_pool *gen_pool,
					    unsigned int order,
					    struct list_head *folio_list,
					    unsigned int nr_folios)
{
	unsigned int alloced;

	for (alloced = 0; alloced < nr_folios; alloced++) {
		struct folio *folio = gen_folio_pool_get_order(gen_pool, order);
		if (!folio)
			break;

		list_add_tail(&folio->lru, folio_list);
	}

	return alloced;
}

/**
 * gen_folio_pool_put - Return a folio to the pool
 * @gen_pool: The generic folio pool to return to
 * @folio: The folio to return
 *
 * Adds the folio back to the appropriate bucket based on its order.
 * Unsupported folios will be evicted immediately via pool_ops->evict().
 */
void gen_folio_pool_put(struct gen_folio_pool *gen_pool, struct folio *folio)
{
	struct order_bucket *bucket;
	unsigned int order;

	order = folio_order(folio);

	/* Check if order is valid and supported */
	if (order >= MAX_ORDER || !(gen_pool->orders_bitmap & BIT(order))) {
		LIST_HEAD(folio_list);

		pr_warn("%s: unexpected order %u folio, evicting immediately\n",
			gen_pool->name, order);

		INIT_LIST_HEAD(&folio->lru);
		list_add(&folio->lru, &folio_list);
		gen_pool->pool_ops->evict(gen_pool, &folio_list);

		return;
	}

	bucket = &gen_pool->buckets[order];

	atomic_long_inc(&bucket->count);
	atomic_long_add(folio_size(folio), &bucket->size);

	node_stat_add_folio(folio, NR_KERNEL_MISC_RECLAIMABLE);

	scoped_guard(spinlock, &bucket->lock)
		list_add_tail(&folio->lru, &bucket->folio_list);
}

/* ============================== Size Query API ============================== */

/**
 * gen_folio_pool_size - Get the total size of folios in the pool
 * @gen_pool: The generic folio pool to query
 *
 * Return: Total size of all folios across all buckets in bytes
 */
unsigned long gen_folio_pool_size(struct gen_folio_pool *gen_pool)
{
	unsigned long total_size = 0;
	unsigned int i;

	for (i = 0; i < MAX_ORDER; i++) {
		if (gen_pool->orders_bitmap & BIT(i))
			total_size += max(0, atomic_long_read(&gen_pool->buckets[i].size));
	}

	return total_size;
}

/* ============================== Initialization/Exit API ============================== */

/**
 * gen_folio_pool_init_ext - Initialize a generic folio pool with specific params
 * @gen_pool: The generic folio pool to initialize
 * @name: Name identifier for the pool
 * @pool_ops: Per-Heap pool operations
 * @orders_bitmap: Bitmap of supported orders (bit N set = order N supported)
 * @batch: Batch count for the shrinker
 * @seeks: Seeks priority for the shrinker
 *
 * Initializes the pool with support for orders specified via bitmap.
 * Each set bit position corresponds to a supported order.
 * Registers a shrinker for memory reclamation.
 *
 * Return: 0 on success, negative error code on failure
 */
int gen_folio_pool_init_ext(struct gen_folio_pool *gen_pool,
			    const char *name, const struct heap_pool_ops *pool_ops,
			    unsigned long orders_bitmap, long batch, int seeks)
{
	unsigned int i;

	if (!gen_pool || !pool_ops || !pool_ops->evict)
		return -EINVAL;

	/* Validate orders_bitmap and count orders */
	if ((orders_bitmap == 0) || ((orders_bitmap >> MAX_ORDER) != 0))
		return -EINVAL;

	memset(gen_pool, 0, sizeof(*gen_pool));

	/* Register shrinker */
	gen_pool->shrinker.count_objects = pool_shrink_count;
	gen_pool->shrinker.scan_objects = pool_shrink_scan;
	gen_pool->shrinker.seeks = seeks;
	gen_pool->shrinker.batch = batch;

	if (register_shrinker(&gen_pool->shrinker, "gen-pool:%s", name) < 0)
		return -ENODEV;

	/* Initialize pool fields */
	gen_pool->orders_bitmap = orders_bitmap;
	gen_pool->name = name;
	gen_pool->pool_ops = pool_ops;

	/* Initialize all bucket spinlocks and lists */
	for (i = 0; i < MAX_ORDER; i++) {
		spin_lock_init(&gen_pool->buckets[i].lock);
		INIT_LIST_HEAD(&gen_pool->buckets[i].folio_list);
		atomic_long_set(&gen_pool->buckets[i].count, 0);
		atomic_long_set(&gen_pool->buckets[i].size, 0);
	}

	if (!kunit_get_current_test())
		pr_info("\"%s\" pool init with %lu orders\n", name, hweight_long(gen_pool->orders_bitmap));

	return 0;
}
