/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * OF helpers for the GPIO API
 *
 * Copyright (c) 2007-2008  MontaVista Software, Inc.
 *
 * Author: Anton Vorontsov <avorontsov@ru.mvista.com>
 */

#ifndef __LINUX_OF_GPIO_H
#define __LINUX_OF_GPIO_H

#include <linux/compiler.h>
#include <linux/gpio/driver.h>
#include <linux/gpio.h>		/* FIXME: Shouldn't be here */
#include <linux/of.h>

struct device_node;

#ifdef CONFIG_OF_GPIO

extern int of_get_named_gpio(const struct device_node *np,
			     const char *list_name, int index);

#else /* CONFIG_OF_GPIO */

#include <linux/errno.h>

/* Drivers may not strictly depend on the GPIO support, so let them link. */
static inline int of_get_named_gpio(const struct device_node *np,
                                   const char *propname, int index)
{
	return -ENOSYS;
}

#endif /* CONFIG_OF_GPIO */

/*
 * Legacy of_gpio_count()/of_get_gpio() helpers removed upstream. Samsung
 * BSP drivers still call them; they are exact restores of the removed
 * semantics.
 */
static inline int of_gpio_count(struct device_node *np)
{
	return of_property_count_u32_elems(np, "gpios");
}

static inline int of_get_gpio(struct device_node *np, int index)
{
	return of_get_named_gpio(np, "gpios", index);
}

#endif /* __LINUX_OF_GPIO_H */
