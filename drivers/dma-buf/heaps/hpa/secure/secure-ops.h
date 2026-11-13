// SPDX-License-Identifier: GPL-2.0
/**
 * Secure Ops
 *
 * Copyright (C) 2026 Samsung Electronics Co., Ltd.
 * Authors: Dongseok Lee <drain.lee@samsung.com>
 */

#ifndef __SECURE_OPS_H__
#define __SECURE_OPS_H__

#include <linux/device.h>
#include <linux/scatterlist.h>

struct secure_ctx;

struct secure_ops {
	void *(*map)(struct secure_ctx *ctx, struct device *dev, struct sg_table *sgt,
		unsigned int protection_id);
	int (*unmap)(struct secure_ctx *ctx, void *map_handle);
};

struct secure_ctx {
	const char *name;
	const struct secure_ops *ops;
	void *priv;
};

static inline void *secure_map(struct secure_ctx *ctx, struct device *dev,
	struct sg_table *sgt, unsigned int protection_id)
{
	if (!ctx || !ctx->ops || !ctx->ops->map)
		return ERR_PTR(-EINVAL);

	return ctx->ops->map(ctx, dev, sgt, protection_id);
}

static inline int secure_unmap(struct secure_ctx *ctx, void *map_handle)
{
	if (!ctx || !ctx->ops || !ctx->ops->unmap)
		return -EINVAL;

	return ctx->ops->unmap(ctx, map_handle);
}

#endif/*__SECURE_OPS_H__*/
