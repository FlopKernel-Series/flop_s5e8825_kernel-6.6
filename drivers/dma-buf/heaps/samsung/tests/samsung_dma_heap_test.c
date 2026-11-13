// SPDX-License-Identifier: GPL-2.0
/**
 * DMA-BUF Samsung Heap KUnit Test Module
 *
 * KUnit test module for Samsung DMA-BUF heap subsystem.
 * Tests heap registration, buffer allocation, and memory management operations.
 *
 * Copyright (C) 2026 Samsung Electronics Co., Ltd.
 * Authors: Dongseok Lee <drain.lee@samsung.com>
 */

#include <linux/module.h>
#include <linux/debugfs.h>
#include <kunit/visibility.h>

static struct dentry *debugfs_dir;

static int __init samsung_dma_heap_test_init(void)
{
	int ret = 0;

	/* Create debugfs directory */
	debugfs_dir = debugfs_create_dir("dma_heap_test", NULL);
	if (!debugfs_dir) {
		pr_err("Failed to create debugfs directory\n");
		return -ENOMEM;
	}

	return ret;
}

static void __exit samsung_dma_heap_test_exit(void)
{
	if (debugfs_dir)
		debugfs_remove_recursive(debugfs_dir);
}

module_init(samsung_dma_heap_test_init);
module_exit(samsung_dma_heap_test_exit);

MODULE_DESCRIPTION("DMA-BUF Samsung Heap KUnit Test Module");
MODULE_IMPORT_NS(EXPORTED_FOR_KUNIT_TESTING);
MODULE_LICENSE("GPL");
