// SPDX-License-Identifier: GPL-2.0
/**
 * Folio list utility functions for DMA buffer heaps
 *
 * Copyright (C) 2026 Samsung Electronics Co., Ltd.
 * Authors: Dongseok Lee <drain.lee@samsung.com>
 *
 * Utility functions for converting between folio arrays and folio lists
 * commonly used in DMA buffer heap implementations.
 *
 * Provides conversion between folio arrays (for physical address operations)
 * and folio lists (for HVC calls, protection operations, and bulk operations).
 */

#ifndef _FOLIO_LIST_H
#define _FOLIO_LIST_H

#include <linux/mm.h>
#include <linux/list.h>
#include <linux/scatterlist.h>
#include <linux/errno.h>

/* =============================================================
   Array <-> List Conversion
   ============================================================= */

/**
 * folio_list_unlink_all_unsafe - Remove all entries from a folio list without cleanup
 * @folio_list: List head to clear
 *
 * Removes all entries from the folio list but does not free them.
 * Caller is responsible for proper folio cleanup.
 *
 * Return: Number of entries removed, or -EINVAL if @folio_list is NULL
 */
static inline int folio_list_unlink_all_unsafe(struct list_head *folio_list)
{
	struct list_head *pos, *n;
	int idx = 0;

	if (!folio_list)
		return -EINVAL;

	list_for_each_safe(pos, n, folio_list) {
		list_del(pos);
		idx++;
	}

	return idx;
}

/**
 * folio_list_from_folio_array - Convert folio array to folio list
 * @nr_folios: Number of folios in the array
 * @folio_array: Array of folio pointers
 * @folio_list: List head to populate (will be reinitialized)
 *
 * Converts an array of folio pointers into a linked list using the lru field.
 * The @folio_list is reinitialized before adding entries.
 *
 * Return: Number of folios converted, or -EINVAL on invalid arguments
 */
static inline int folio_list_from_folio_array(unsigned long nr_folios,
					    struct folio **folio_array,
					    struct list_head *folio_list)
{
	int idx;

	if (!nr_folios || !folio_array || !folio_list)
		return -EINVAL;

	INIT_LIST_HEAD(folio_list);

	for (idx = 0; idx < nr_folios; idx++) {
		INIT_LIST_HEAD(&folio_array[idx]->lru);
		list_add_tail(&folio_array[idx]->lru, folio_list);
	}

	return idx;
}

/**
 * folio_list_to_sg_table - Convert folio list to scatter-gather table
 * @folio_list: List head containing folios
 * @sgt: Scatter-gather table to populate (must have allocated sgl with sgt->nents > 0)
 *
 * Extracts folios from a list into a scatter-gather table.
 * Each folio is set as a single sg entry using sg_set_folio().
 * After the conversion, sg_table->nents is updated to the actual
 * number of folios converted. Entries remain in the original list.
 *
 * If the folio list contains more entries than sgt->nents, the function
 * returns the number of folios actually converted (up to sgt->nents).
 * In this case, sg_table->nents is not updated and retains its original
 * value (only the first idx entries are set).
 *
 * Return: Number of folios converted (0 to sgt->nents), or -EINVAL on
 *         invalid arguments (NULL @folio_list, NULL @sgt, NULL @sgt->sgl,
 *         or sgt->nents == 0)
 */
static inline int folio_list_to_sg_table(struct list_head *folio_list,
					    struct sg_table *sgt)
{
	struct folio *folio;
	struct scatterlist *sg;
	int idx = 0;

	if (!folio_list || !sgt || !sgt->sgl || !sgt->nents)
		return -EINVAL;

	sg = sgt->sgl;
	list_for_each_entry(folio, folio_list, lru) {
		if (idx >= sgt->nents)
			return sgt->nents;

		sg_set_folio(sg, folio, folio_size(folio), 0);
		sg = sg_next(sg);

		idx++;
	}

	sgt->nents = idx;

	return idx;
}

/* =============================================================
   List Operations
   ============================================================= */

/**
 * folio_list_count - Count entries in a folio list
 * @folio_list: List head to count
 *
 * Return: Number of entries in the list, 0 if @folio_list is NULL or empty
 */
static inline unsigned int folio_list_count(struct list_head *folio_list)
{
	struct folio *folio;
	unsigned int count = 0;

	if (!folio_list)
		return 0;

	list_for_each_entry(folio, folio_list, lru)
		count++;

	return count;
}

/* =============================================================
   Helper Functions for Sorting and Searching
   ============================================================= */

/**
 * folio_list_total_bytes - Calculate total memory size in bytes
 * @folio_list: List head
 *
 * Accounts for both normal folios and large folios.
 *
 * Return: Total size in bytes, or 0 if @folio_list is NULL
 */
static inline unsigned long folio_list_total_bytes(struct list_head *folio_list)
{
	struct folio *folio;
	unsigned long size = 0;

	if (!folio_list)
		return 0;

	list_for_each_entry(folio, folio_list, lru)
		size += folio_size(folio);

	return size;
}

#endif /* _FOLIO_LIST_H */
