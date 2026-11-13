// SPDX-License-Identifier: GPL-2.0
/**
 * Generic folio pool for memory management
 *
 * Copyright (C) 2026 Samsung Electronics Co., Ltd.
 * Authors: Dongseok Lee <drain.lee@samsung.com>
 *
 * Provides a pool of pre-allocated folios for efficient memory allocation.
 * Supports shrinker-based reclamation under memory pressure.
 */

#ifndef __GENERIC_FOLIO_POOL_H__
#define  __GENERIC_FOLIO_POOL_H__

#include <linux/mm.h>
#include <linux/spinlock.h>
#include <linux/atomic.h>
#include <linux/shrinker.h>

struct gen_folio_pool;

/**
 * struct heap_pool_ops - Callback operations for per-heap folio pool
 * @pre_evict: Called before evicting a list of folios (optional)
 *             This callback allows the pool owner to perform pre-eviction
 *             validation or state management before folios are actually evicted.
 *
 *             Parameters:
 *               @gen_pool: The generic folio pool
 *               @folio_list: List of folios to process (using lru field).
 *                          Each folio in this list is a candidate for eviction.
 *               @failed_list: Pre-initialized list head provided by caller.
 *                             Implementation MUST move (transfer) failed folios
 *                             from @folio_list to @failed_list. Folios must be
 *                             transferred, not copied or removed.
 *
 *             Return semantics:
 *               - >=0: Number of folios that succeeded (remain in folio_list).
 *                       If all input folios succeeded, this equals the input count.
 *                       Empty input list returns 0.
 *               - <0: Some folios failed (-errno).
 *                   Caller processes remaining successful folios in folio_list and
 *                   handles failed folios in failed_list.
 *
 *             Behavior patterns:
 *               1. Nothing succeeds: Move all folios to @failed_list,
 *                  leave @folio_list empty, return -EINVAL
 *               2. All succeed: Keep all folios in @folio_list, return input_count
 *               3. Partial succeed: Move only failed ones to @failed_list,
 *                  keep successful ones in @folio_list, return success_count (or <0 to
 *                  signal partial failure while allowing following evict to proceed
 *                  with successful ones)
 *
 *             Implementation requirements:
 *               - MUST transfer (move) folios between lists, not remove with list_del()
 *               - MUST NOT modify folio contents, only move between lists
 *               - Caller will EVICT folios from folio_list and PUT BACK
 *                 failed folios from failed_list (if any)
 *               - Callback is called without spinlocks held (lock-free context)
 *
 *             Example implementation (simple validation that rejects some folios):
 *               static int my_pool_pre_evict(struct gen_folio_pool *gen_pool,
 *                                            struct list_head *folio_list,
 *                                            struct list_head *failed_list)
 *               {
 *                   struct folio *folio, *tmp;
 *                   int succeeded = 0;
 *
 *                   list_for_each_entry_safe(folio, tmp, folio_list, lru) {
 *                       if (some_validation_fails(folio)) {
 *                           list_move(&folio->lru, failed_list);
 *                       } else {
 *                           succeeded++;
 *                       }
 *                   }
 *
 *                   // Return success count, or error if any failed
 *                   return (list_empty(failed_list)) ? succeeded : -EAGAIN;
 *               }
 *
 * @evict: Called to finalize eviction of a list of folios (mandatory)
 *         This callback is called for folios that passed pre_evict validation.
 *         Implementation MUST:
 *           - Remove each folio from the list (already removed by caller)
 *           - Release any pool-owned references (e.g., folio_put())
 *
 *         Note: Caller has already removed folios from bucket lists and
 *               subtracted from bucket statistics before calling this callback.
 *               Only deallocation/cleanup is needed.
 */
struct heap_pool_ops {
	int (*pre_evict)(struct gen_folio_pool *gen_pool, struct list_head *folio_list,
			 struct list_head *failed_list);
	void (*evict)(struct gen_folio_pool *gen_pool, struct list_head *folio_list);
};

/**
 * struct order_bucket - Per-order bucket for folio management
 * @lock:		Spinlock protecting this bucket
 * @folio_list:		List head for folios of this order
 * @count:		Number of folios in this bucket
 * @size:		Total bytes of folios in this bucket
 */
struct order_bucket {
	spinlock_t lock;
	struct list_head folio_list;
	atomic_long_t count;
	atomic_long_t size;
};

/**
 * struct gen_folio_pool - Generic folio pool for memory management
 * @name:		Name identifier for the pool
 * @pool_ops:		Callback operations for eviction handling
 * @shrinker:		Shrinker for memory reclamation
 * @orders_bitmap:	Bitmap of supported orders (bit N set = order N supported)
 * @buckets:		Static array of order buckets indexed by order value
 * @priv:		Private data for pool-specific context (e.g., secure ops, heap ref)
 *
 * A pool of pre-allocated folios for efficient memory allocation.
 * Supports multiple orders and shrinker-based reclamation under memory pressure.
 * Buckets are indexed directly by order value (0 to MAX_ORDER-1).
 */
struct gen_folio_pool {
	const char *name;
	const struct heap_pool_ops *pool_ops;
	struct shrinker shrinker;

	unsigned long orders_bitmap;
	struct order_bucket buckets[MAX_ORDER];

	void *priv;
};

/* Multi-order API */
struct folio *gen_folio_pool_get_order(struct gen_folio_pool *gen_pool,
				       unsigned int order);
unsigned int gen_folio_pool_get_order_list(struct gen_folio_pool *gen_pool,
					    unsigned int order,
					    struct list_head *folio_list,
					    unsigned int nr_folios);
void gen_folio_pool_put(struct gen_folio_pool *gen_pool, struct folio *folio);
unsigned long gen_folio_pool_size(struct gen_folio_pool *gen_pool);

/* Initialization API */
int gen_folio_pool_init_ext(struct gen_folio_pool *gen_pool,
	const char *name, const struct heap_pool_ops *pool_ops,
	unsigned long orders_bitmap, long batch, int seeks);

#endif/*__GENERIC_FOLIO_POOL_H__*/
