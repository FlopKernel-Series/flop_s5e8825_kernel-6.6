// SPDX-License-Identifier: GPL-2.0+
//
// Exynos ARMv8 specific support for Samsung pinctrl/gpiolib driver
// with eint support.
//
// Copyright (c) 2012 Samsung Electronics Co., Ltd.
//		http://www.samsung.com
// Copyright (c) 2012 Linaro Ltd
//		http://www.linaro.org
// Copyright (c) 2017 Krzysztof Kozlowski <krzk@kernel.org>
//
// This file contains the Samsung Exynos specific information required by the
// the Samsung pinctrl/gpiolib driver. It also includes the implementation of
// external gpio and wakeup interrupt support.

#include <linux/slab.h>
#include <linux/module.h>
#include <linux/soc/samsung/exynos-regs-pmu.h>

#include "pinctrl-samsung.h"
#include "pinctrl-exynos.h"

static const struct samsung_pin_bank_type bank_type_off = {
	.fld_width = { 4, 1, 2, 2, 2, 2, },
	.reg_offset = { 0x00, 0x04, 0x08, 0x0c, 0x10, 0x14, },
};

static const struct samsung_pin_bank_type bank_type_alive = {
	.fld_width = { 4, 1, 2, 2, },
	.reg_offset = { 0x00, 0x04, 0x08, 0x0c, },
};

/* Exynos5433 has the 4bit widths for PINCFG_TYPE_DRV bitfields. */
static const struct samsung_pin_bank_type exynos5433_bank_type_off = {
	.fld_width = { 4, 1, 2, 4, 2, 2, },
	.reg_offset = { 0x00, 0x04, 0x08, 0x0c, 0x10, 0x14, },
};

static const struct samsung_pin_bank_type exynos5433_bank_type_alive = {
	.fld_width = { 4, 1, 2, 4, },
	.reg_offset = { 0x00, 0x04, 0x08, 0x0c, },
};

/* bank type for non-alive type
 * (CON bit field: 4, DAT bit field: 1, PUD bit field: 4, DRV bit field: 4)
 * (CONPDN bit field: 2, PUDPDN bit field: 4)
 */
static struct samsung_pin_bank_type exynos9810_bank_type_off  = {
	.fld_width = { 4, 1, 4, 4, 2, 4, },
	.reg_offset = { 0x00, 0x04, 0x08, 0x0c, 0x10, 0x14, },
};

/* bank type for alive type
 * (CON bit field: 4, DAT bit field: 1, PUD bit field: 4, DRV bit field: 4)
 */
static struct samsung_pin_bank_type exynos9810_bank_type_alive = {
	.fld_width = { 4, 1, 4, 4, },
	.reg_offset = { 0x00, 0x04, 0x08, 0x0c, },
};

/*
 * pinctrl define for S5E9925
 */

/* pin banks of s5e9925 pin-controller (GPIO_ALIVE=0x15850000) */
static struct samsung_pin_bank_data s5e9925_pin_alive[] = {
	EXYNOS9_PIN_BANK_EINTW(exynos9810_bank_type_alive, 8, 0x0,  "gpa0", 0x00, 0x00),
	EXYNOS9_PIN_BANK_EINTW(exynos9810_bank_type_alive, 8, 0x20, "gpa1", 0x04, 0x08),
	EXYNOS9_PIN_BANK_EINTW(exynos9810_bank_type_alive, 8, 0x40, "gpa2", 0x08, 0x10),
	EXYNOS9_PIN_BANK_EINTW(exynos9810_bank_type_alive, 8, 0x60, "gpa3", 0x0c, 0x18),
	EXYNOS9_PIN_BANK_EINTW(exynos9810_bank_type_alive, 2, 0x80, "gpa4", 0x10, 0x20),
	EXYNOS9_PIN_BANK_EINTN(exynos9810_bank_type_alive, 4, 0xa0, "gpq0"),
	EXYNOS9_PIN_BANK_EINTN(exynos9810_bank_type_alive, 2, 0xc0, "gpq1"),
	EXYNOS9_PIN_BANK_EINTN(exynos9810_bank_type_alive, 2, 0xe0, "gpq2"),
};

/* pin banks of s5e9925 pin-controller (GPIO_CMGP=0x14E30000) */
static struct samsung_pin_bank_data s5e9925_pin_cmgp[] = {
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 2, 0x0,   "gpm0",  0x00, 0x00, 0x288, 0),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 2, 0x20,  "gpm1",  0x04, 0x04, 0x288, 2),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 2, 0x40,  "gpm2",  0x08, 0x08, 0x288, 4),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 2, 0x60,  "gpm3",  0x0c, 0x0c, 0x288, 6),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 2, 0x80,  "gpm4",  0x10, 0x10, 0x288, 10),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 2, 0xa0,  "gpm5",  0x14, 0x14, 0x288, 12),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 2, 0xc0,  "gpm6",  0x18, 0x18, 0x288, 14),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 2, 0xe0,  "gpm7",  0x1c, 0x1c, 0x288, 16),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 2, 0x100, "gpm8",  0x20, 0x20, 0x288, 18),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 2, 0x120, "gpm9",  0x24, 0x24, 0x288, 20),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 2, 0x140, "gpm10", 0x28, 0x28, 0x288, 22),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 2, 0x160, "gpm11", 0x2c, 0x2c, 0x288, 24),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 2, 0x180, "gpm12", 0x30, 0x30, 0x288, 26),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 2, 0x1a0, "gpm13", 0x34, 0x34, 0x288, 28),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x1c0, "gpm14", 0x38, 0x38, 0x288, 30),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x1e0, "gpm15", 0x3c, 0x3c, 0x288, 31),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x200, "gpm16", 0x40, 0x40, 0x2B8, 0),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x220, "gpm17", 0x44, 0x44, 0x2B8, 1),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x240, "gpm20", 0x48, 0x48, 0x2B8, 2),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x260, "gpm21", 0x4c, 0x4c, 0x2B8, 3),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x280, "gpm22", 0x50, 0x50, 0x2B8, 4),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x2a0, "gpm23", 0x54, 0x54, 0x2B8, 5),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x2c0, "gpm24", 0x58, 0x58, 0x2B8, 6),
};

/* pin banks of s5e9925 pin-controller (GPIO_HSI1=0x11240000) */
static struct samsung_pin_bank_data s5e9925_pin_hsi1[] = {
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 4, 0x0, "gpf0", 0x00, 0x00),
};

/* pin banks of s5e9925 pin-controller (GPIO_UFS=0x11040000) */
static struct samsung_pin_bank_data s5e9925_pin_ufs[] = {
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 7, 0x0, "gpf1", 0x00, 0x00),
};

/* pin banks of s5e9925 pin-controller (GPIO_HSI1UFS=0x11060000) */
static struct samsung_pin_bank_data s5e9925_pin_hsi1ufs[] = {
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 2, 0x0, "gpf2", 0x00, 0x00),
};

/* pin banks of s5e9925 pin-controller (GPIO_PERIC0=0x10430000) */
static struct samsung_pin_bank_data s5e9925_pin_peric0[] = {
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 4, 0x0,   "gpb0",  0x00, 0x00),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 4, 0x20,  "gpb1",  0x04, 0x04),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 4, 0x40,  "gpb2",  0x08, 0x08),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 4, 0x60,  "gpb3",  0x0c, 0x0c),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 4, 0x80,  "gpp4",  0x10, 0x10),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 2, 0xa0,  "gpc0",  0x14, 0x14),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 2, 0xc0,  "gpc1",  0x18, 0x18),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 2, 0xe0,  "gpc2",  0x1c, 0x1c),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 7, 0x100, "gpg1",  0x20, 0x20),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 2, 0x120, "gpg2",  0x24, 0x24),
};

/* pin banks of s5e9925 pin-controller (GPIO_PERIC1=0x10730000) */
static struct samsung_pin_bank_data s5e9925_pin_peric1[] = {
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 4, 0x0,  "gpp7",  0x00, 0x00),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 4, 0x20, "gpp8",  0x04, 0x04),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 4, 0x40, "gpp9",  0x08, 0x08),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 4, 0x60, "gpp10", 0x0c, 0x0c),
};

/* pin banks of s5e9925 pin-controller (GPIO_PERIC2=0x11C30000) */
static struct samsung_pin_bank_data s5e9925_pin_peric2[] = {
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 4, 0x0,   "gpp0",  0x00, 0x00),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 4, 0x20,  "gpp1",  0x04, 0x04),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 4, 0x40,  "gpp2",  0x08, 0x08),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 4, 0x60,  "gpp3",  0x0c, 0x0c),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 4, 0x80,  "gpp5",  0x10, 0x10),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 4, 0xa0,  "gpp6",  0x14, 0x14),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 4, 0xc0,  "gpp11", 0x18, 0x18),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 2, 0xe0,  "gpc3",  0x1c, 0x1c),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 2, 0x100, "gpc4",  0x20, 0x20),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 2, 0x120, "gpc5",  0x24, 0x24),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 2, 0x140, "gpc6",  0x28, 0x28),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 2, 0x160, "gpc7",  0x2c, 0x2c),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 2, 0x180, "gpc8",  0x30, 0x30),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 2, 0x1a0, "gpc9",  0x34, 0x34),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 5, 0x1c0, "gpg0",  0x38, 0x38),
};

/* pin banks of s5e9925 pin-controller (GPIO_VTS=0x15320000) */
static struct samsung_pin_bank_data s5e9925_pin_vts[] = {
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 7, 0x0, "gpv0", 0x00, 0x00),
};

static struct samsung_pin_ctrl s5e9925_pin_ctrl[] = {
	{
		/* pin-controller instance 0 ALIVE data */
		.pin_banks	= s5e9925_pin_alive,
		.nr_banks	= ARRAY_SIZE(s5e9925_pin_alive),
		.eint_gpio_init = exynos_eint_gpio_init,
		.eint_wkup_init = exynos_eint_wkup_init,
		.suspend	= exynos_pinctrl_suspend,
		.resume		= exynos_pinctrl_resume,
	}, {
		/* pin-controller instance 1 CMGP data */
		.pin_banks	= s5e9925_pin_cmgp,
		.nr_banks	= ARRAY_SIZE(s5e9925_pin_cmgp),
		.eint_gpio_init = exynos_eint_gpio_init,
		.eint_wkup_init = exynos_eint_wkup_init,
		.suspend	= exynos_pinctrl_suspend,
		.resume		= exynos_pinctrl_resume,
	}, {
		/* pin-controller instance 2 HSI1 data */
		.pin_banks	= s5e9925_pin_hsi1,
		.nr_banks	= ARRAY_SIZE(s5e9925_pin_hsi1),
	}, {
		/* pin-controller instance 3 UFS data */
		.pin_banks	= s5e9925_pin_ufs,
		.nr_banks	= ARRAY_SIZE(s5e9925_pin_ufs),
		.eint_gpio_init = exynos_eint_gpio_init,
		.suspend	= exynos_pinctrl_suspend,
		.resume		= exynos_pinctrl_resume,
	}, {
		/* pin-controller instance 4 HSI1UFS data */
		.pin_banks	= s5e9925_pin_hsi1ufs,
		.nr_banks	= ARRAY_SIZE(s5e9925_pin_hsi1ufs),
		.eint_gpio_init = exynos_eint_gpio_init,
		.suspend	= exynos_pinctrl_suspend,
		.resume		= exynos_pinctrl_resume,
	}, {
		/* pin-controller instance 5 PERIC0 data */
		.pin_banks	= s5e9925_pin_peric0,
		.nr_banks	= ARRAY_SIZE(s5e9925_pin_peric0),
		.eint_gpio_init = exynos_eint_gpio_init,
		.suspend	= exynos_pinctrl_suspend,
		.resume		= exynos_pinctrl_resume,
	}, {
		/* pin-controller instance 6 PERIC1 data */
		.pin_banks	= s5e9925_pin_peric1,
		.nr_banks	= ARRAY_SIZE(s5e9925_pin_peric1),
		.eint_gpio_init = exynos_eint_gpio_init,
		.suspend	= exynos_pinctrl_suspend,
		.resume		= exynos_pinctrl_resume,
	}, {
		/* pin-controller instance 7 PERIC2 data */
		.pin_banks	= s5e9925_pin_peric2,
		.nr_banks	= ARRAY_SIZE(s5e9925_pin_peric2),
		.eint_gpio_init = exynos_eint_gpio_init,
		.suspend	= exynos_pinctrl_suspend,
		.resume		= exynos_pinctrl_resume,
	}, {
		/* For this block, pinctrl will not care for interrupt and S2R */
		/* pin-controller instance 8 VTS data */
		.pin_banks	= s5e9925_pin_vts,
		.nr_banks	= ARRAY_SIZE(s5e9925_pin_vts),
	},
};

const struct samsung_pinctrl_of_match_data s5e9925_of_data __initconst = {
	.ctrl		= s5e9925_pin_ctrl,
	.num_ctrl	= ARRAY_SIZE(s5e9925_pin_ctrl),
};

/*
 * pinctrl define for S5E9925 EVT0
 */

/* pin banks of s5e9925_evt0 pin-controller (GPIO_ALIVE=0x15850000) */
static struct samsung_pin_bank_data s5e9925_evt0_pin_alive[] = {
	EXYNOS9_PIN_BANK_EINTW(exynos9810_bank_type_alive, 8, 0x0,  "gpa0", 0x00, 0x00),
	EXYNOS9_PIN_BANK_EINTW(exynos9810_bank_type_alive, 8, 0x20, "gpa1", 0x04, 0x08),
	EXYNOS9_PIN_BANK_EINTW(exynos9810_bank_type_alive, 8, 0x40, "gpa2", 0x08, 0x10),
	EXYNOS9_PIN_BANK_EINTW(exynos9810_bank_type_alive, 8, 0x60, "gpa3", 0x0c, 0x18),
	EXYNOS9_PIN_BANK_EINTW(exynos9810_bank_type_alive, 2, 0x80, "gpa4", 0x10, 0x20),
	EXYNOS9_PIN_BANK_EINTN(exynos9810_bank_type_alive, 4, 0xa0, "gpq0"),
	EXYNOS9_PIN_BANK_EINTN(exynos9810_bank_type_alive, 2, 0xc0, "gpq1"),
	EXYNOS9_PIN_BANK_EINTN(exynos9810_bank_type_alive, 2, 0xe0, "gpq2"),
};

/* pin banks of s5e9925_evt0 pin-controller (GPIO_CMGP=0x14E30000) */
static struct samsung_pin_bank_data s5e9925_evt0_pin_cmgp[] = {
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 2, 0x0,   "gpm0",  0x00, 0x00, 0x288, 0),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 2, 0x20,  "gpm1",  0x04, 0x04, 0x288, 2),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 2, 0x40,  "gpm2",  0x08, 0x08, 0x288, 4),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 2, 0x60,  "gpm3",  0x0c, 0x0c, 0x288, 6),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 2, 0x80,  "gpm4",  0x10, 0x10, 0x288, 10),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 2, 0xa0,  "gpm5",  0x14, 0x14, 0x288, 12),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 2, 0xc0,  "gpm6",  0x18, 0x18, 0x288, 14),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 2, 0xe0,  "gpm7",  0x1c, 0x1c, 0x288, 16),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 2, 0x100, "gpm8",  0x20, 0x20, 0x288, 18),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 2, 0x120, "gpm9",  0x24, 0x24, 0x288, 20),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 2, 0x140, "gpm10", 0x28, 0x28, 0x288, 22),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 2, 0x160, "gpm11", 0x2c, 0x2c, 0x288, 24),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 2, 0x180, "gpm12", 0x30, 0x30, 0x288, 26),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 2, 0x1a0, "gpm13", 0x34, 0x34, 0x288, 28),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x1c0, "gpm14", 0x38, 0x38, 0x288, 30),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x1e0, "gpm15", 0x3c, 0x3c, 0x288, 31),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x200, "gpm16", 0x40, 0x40, 0x2B8, 0),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x220, "gpm17", 0x44, 0x44, 0x2B8, 1),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x240, "gpm18", 0x48, 0x48, 0x2B8, 2),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x260, "gpm19", 0x4c, 0x4c, 0x2B8, 3),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x280, "gpm20", 0x50, 0x50, 0x2B8, 4),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x2a0, "gpm21", 0x54, 0x54, 0x2B8, 5),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x2c0, "gpm22", 0x58, 0x58, 0x2B8, 6),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x2e0, "gpm23", 0x5c, 0x5c, 0x2B8, 7),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x300, "gpm24", 0x60, 0x60, 0x2B8, 8),
};

/* pin banks of s5e9925_evt0 pin-controller (GPIO_HSI1=0x11040000) */
static struct samsung_pin_bank_data s5e9925_evt0_pin_hsi1[] = {
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 4, 0x0, "gpf0", 0x00, 0x00),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 7, 0x20, "gpf1", 0x04, 0x04),
};

/* pin banks of s5e9925_evt0 pin-controller (GPIO_HSI1UFS=0x11060000) */
static struct samsung_pin_bank_data s5e9925_evt0_pin_hsi1ufs[] = {
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 2, 0x0, "gpf2", 0x00, 0x00),
};

/* pin banks of s5e9925_evt0 pin-controller (GPIO_PERIC0=0x10430000) */
static struct samsung_pin_bank_data s5e9925_evt0_pin_peric0[] = {
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 4, 0x0,  "gpp4",  0x00, 0x00),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 7, 0x20, "gpg1",  0x04, 0x04),
};

/* pin banks of s5e9925_evt0 pin-controller (GPIO_PERIC1=0x10730000) */
static struct samsung_pin_bank_data s5e9925_evt0_pin_peric1[] = {
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 4, 0x0, "gpb0",  0x00, 0x00),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 4, 0x20, "gpb1",  0x04, 0x04),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 4, 0x40, "gpb2",  0x08, 0x08),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 4, 0x60, "gpb3",  0x0c, 0x0c),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 4, 0x80, "gpp7", 0x10, 0x10),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 4, 0xa0, "gpp8", 0x14, 0x14),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 4, 0xc0,  "gpp9",  0x18, 0x18),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 4, 0xe0,  "gpp10", 0x1c, 0x1c),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 2, 0x100, "gpc0", 0x20, 0x20),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 2, 0x120, "gpc1", 0x24, 0x24),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 2, 0x140, "gpc2", 0x28, 0x28),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 2, 0x160, "gpg2", 0x2c, 0x2c),
};

/* pin banks of s5e9925_evt0 pin-controller (GPIO_PERIC2=0x11C30000) */
static struct samsung_pin_bank_data s5e9925_evt0_pin_peric2[] = {
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 4, 0x0,   "gpp0",  0x00, 0x00),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 4, 0x20,  "gpp1",  0x04, 0x04),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 4, 0x40,  "gpp2",  0x08, 0x08),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 4, 0x60,  "gpp3",  0x0c, 0x0c),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 4, 0x80,  "gpp5",  0x10, 0x10),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 4, 0xa0,  "gpp6",  0x14, 0x14),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 4, 0xc0,  "gpp11", 0x18, 0x18),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 2, 0xe0,  "gpc3", 0x1c, 0x1c),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 2, 0x100, "gpc4", 0x20, 0x20),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 2, 0x120, "gpc5", 0x24, 0x24),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 2, 0x140, "gpc6", 0x28, 0x28),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 2, 0x160, "gpc7", 0x2c, 0x2c),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 2, 0x180, "gpc8", 0x30, 0x30),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 2, 0x1a0, "gpc9", 0x34, 0x34),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 5, 0x1c0, "gpg0", 0x38, 0x38),
};

/* pin banks of s5e9925_evt0 pin-controller (GPIO_VTS=0x15580000) */
static struct samsung_pin_bank_data s5e9925_evt0_pin_vts[] = {
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 7, 0x0, "gpv0", 0x00, 0x00),
};

static struct samsung_pin_ctrl s5e9925_evt0_pin_ctrl[] = {
	{
		/* pin-controller instance 0 ALIVE data */
		.pin_banks	= s5e9925_evt0_pin_alive,
		.nr_banks	= ARRAY_SIZE(s5e9925_evt0_pin_alive),
		.eint_gpio_init = exynos_eint_gpio_init,
		.eint_wkup_init = exynos_eint_wkup_init,
		.suspend	= exynos_pinctrl_suspend,
		.resume		= exynos_pinctrl_resume,
	}, {
		/* pin-controller instance 1 CMGP data */
		.pin_banks	= s5e9925_evt0_pin_cmgp,
		.nr_banks	= ARRAY_SIZE(s5e9925_evt0_pin_cmgp),
		.eint_gpio_init = exynos_eint_gpio_init,
		.eint_wkup_init = exynos_eint_wkup_init,
		.suspend	= exynos_pinctrl_suspend,
		.resume		= exynos_pinctrl_resume,
	}, {
		/* pin-controller instance 2 HSI1 data */
		.pin_banks	= s5e9925_evt0_pin_hsi1,
		.nr_banks	= ARRAY_SIZE(s5e9925_evt0_pin_hsi1),
		.eint_gpio_init = exynos_eint_gpio_init,
		.suspend	= exynos_pinctrl_suspend,
		.resume		= exynos_pinctrl_resume,
	}, {
		/* pin-controller instance 3 HSI1UFS data */
		.pin_banks	= s5e9925_evt0_pin_hsi1ufs,
		.nr_banks	= ARRAY_SIZE(s5e9925_evt0_pin_hsi1ufs),
		.eint_gpio_init = exynos_eint_gpio_init,
		.suspend	= exynos_pinctrl_suspend,
		.resume		= exynos_pinctrl_resume,
	}, {
		/* pin-controller instance 4 PERIC0 data */
		.pin_banks	= s5e9925_evt0_pin_peric0,
		.nr_banks	= ARRAY_SIZE(s5e9925_evt0_pin_peric0),
		.eint_gpio_init = exynos_eint_gpio_init,
		.suspend	= exynos_pinctrl_suspend,
		.resume		= exynos_pinctrl_resume,
	}, {
		/* pin-controller instance 5 PERIC1 data */
		.pin_banks	= s5e9925_evt0_pin_peric1,
		.nr_banks	= ARRAY_SIZE(s5e9925_evt0_pin_peric1),
		.eint_gpio_init = exynos_eint_gpio_init,
		.suspend	= exynos_pinctrl_suspend,
		.resume		= exynos_pinctrl_resume,
	}, {
		/* pin-controller instance 6 PERIC2 data */
		.pin_banks	= s5e9925_evt0_pin_peric2,
		.nr_banks	= ARRAY_SIZE(s5e9925_evt0_pin_peric2),
		.eint_gpio_init = exynos_eint_gpio_init,
		.suspend	= exynos_pinctrl_suspend,
		.resume		= exynos_pinctrl_resume,
	}, {
		/* For this block, pinctrl will not care for interrupt and S2R */
		/* pin-controller instance 7 VTS data */
		.pin_banks	= s5e9925_evt0_pin_vts,
		.nr_banks	= ARRAY_SIZE(s5e9925_evt0_pin_vts),
	},
};

const struct samsung_pinctrl_of_match_data s5e9925_evt0_of_data __initconst = {
	.ctrl		= s5e9925_evt0_pin_ctrl,
	.num_ctrl	= ARRAY_SIZE(s5e9925_evt0_pin_ctrl),
};

/*
 * pinctrl define for S5E8825
 */
/* pin banks of s5e8825 pin-controller (GPIO_ALIVE=0x11850000) */
static struct samsung_pin_bank_data s5e8825_pin_alive[] = {
	EXYNOS9_PIN_BANK_EINTW(exynos9810_bank_type_alive, 8, 0x00, "gpa0", 0x00, 0x00),
	EXYNOS9_PIN_BANK_EINTW(exynos9810_bank_type_alive, 4, 0x20, "gpa1", 0x04, 0x08),
	EXYNOS9_PIN_BANK_EINTN(exynos9810_bank_type_alive, 4, 0x40, "gpq0"),
	EXYNOS9_PIN_BANK_EINTN(exynos9810_bank_type_alive, 2, 0x60, "gpq1"),
	EXYNOS9_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x80, "gpc0", 0x08, 0x0c),
	EXYNOS9_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0xa0, "gpc1", 0x0c, 0x10),
	EXYNOS9_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0xc0, "gpc2", 0x10, 0x14),
	EXYNOS9_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0xe0, "gpc3", 0x14, 0x18),
	EXYNOS9_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x100, "gpc4", 0x18, 0x1c),
	EXYNOS9_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x120, "gpc5", 0x1c, 0x20),
	EXYNOS9_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x140, "gpc6", 0x20, 0x24),
	EXYNOS9_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x160, "gpc7", 0x24, 0x28),
	EXYNOS9_PIN_BANK_EINTN(exynos9810_bank_type_alive, 3, 0x180, "gpx0"),
};


/* pin banks of s5e8825 pin-controller (GPIO_CHUB=0x111d0000) */
static struct samsung_pin_bank_data s5e8825_pin_chub[] = {
	EXYNOS9_PIN_BANK_EINTW(exynos9810_bank_type_alive, 8, 0x00,  "gph0",  0x00, 0x00),
	EXYNOS9_PIN_BANK_EINTW(exynos9810_bank_type_alive, 4, 0x20,  "gph1",  0x04, 0x08),

};

/* pin banks of s5e8825 pin-controller (GPIO_CMGP=0x11430000) */
static struct samsung_pin_bank_data s5e8825_pin_cmgp[] = {
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x00,  "gpm0",  0x00, 0x00, 0x288, 0),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x20,  "gpm1",  0x04, 0x04, 0x288, 1),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x40,  "gpm2",  0x08, 0x08, 0x288, 2),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x60,  "gpm3",  0x0c, 0x0c, 0x288, 3),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x80,  "gpm4",  0x10, 0x10, 0x288, 4),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0xa0,  "gpm5",  0x14, 0x14, 0x288, 5),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0xc0,  "gpm6",  0x18, 0x18, 0x288, 6),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0xe0,  "gpm7",  0x1c, 0x1c, 0x288, 7),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x100, "gpm8",  0x20, 0x20, 0x288, 8),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x120, "gpm9",  0x24, 0x24, 0x288, 9),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x140, "gpm10", 0x28, 0x28, 0x288, 10),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x160, "gpm11", 0x2c, 0x2c, 0x288, 11),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x180, "gpm12", 0x30, 0x30, 0x288, 12),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x1a0, "gpm13", 0x34, 0x34, 0x288, 13),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x1c0, "gpm14", 0x38, 0x38, 0x288, 14),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x1e0, "gpm15", 0x3c, 0x3c, 0x288, 15),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x200, "gpm16", 0x40, 0x40, 0x288, 16),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x220, "gpm17", 0x44, 0x44, 0x288, 17),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x240, "gpm18", 0x48, 0x48, 0x288, 18),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x260, "gpm19", 0x4c, 0x4c, 0x288, 19),
	EXYNOS_CMGP_PIN_BANK_EINTW(exynos9810_bank_type_alive, 1, 0x280, "gpm20", 0x50, 0x50, 0x288, 20),
};

/* pin banks of s5e8825 pin-controller (GPIO_HSI=0x13450000) */
static struct samsung_pin_bank_data s5e8825_pin_hsi[] = {
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 2, 0x0, "gpf0", 0x00, 0x00),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 8, 0x20, "gpf1", 0x04, 0x08),
};

/* pin banks of s5e8825 pin-controller (GPIO_HSIUFS=0x13440000) */
static struct samsung_pin_bank_data s5e8825_pin_hsiufs[] = {
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 2, 0x0, "gpf3", 0x00, 0x00),
};


/* pin banks of s5e8825 pin-controller (GPIO_PERI=0x10040000) */
static struct samsung_pin_bank_data s5e8825_pin_peri[] = {
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 8, 0x0,   "gpp0", 0x00, 0x00),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 8, 0x20,  "gpp1", 0x04, 0x08),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 8, 0x40,  "gpp2", 0x08, 0x10),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 6, 0x60,  "gpp3", 0x0c, 0x18),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 5, 0x80,  "gpg0", 0x10, 0x20),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 3, 0xa0,  "gpg1", 0x14, 0x28),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 2, 0xc0,  "gpg2", 0x18, 0x2c),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 6, 0xe0,  "gpb0", 0x1c, 0x30),
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 4, 0x100, "gpb1", 0x20, 0x38),

};

/* pin banks of s5e8825 pin-controller (GPIO_PERIMMC=0x100f0000) */
static struct samsung_pin_bank_data s5e8825_pin_perimmc[] = {
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 6, 0x0, "gpf2", 0x00, 0x00),
};

/* pin banks of s5e8825 pin-controller (GPIO_VTS=0x11780000) */
static struct samsung_pin_bank_data s5e8825_pin_vts[] = {
	EXYNOS9_PIN_BANK_EINTG(exynos9810_bank_type_off, 4, 0x0, "gpv0", 0x00, 0x00),
};



static struct samsung_pin_ctrl s5e8825_pin_ctrl[] = {
	{
	/* pin-controller instance 0 ALIVE data */
		.pin_banks	= s5e8825_pin_alive,
		.nr_banks	= ARRAY_SIZE(s5e8825_pin_alive),
		.eint_gpio_init = exynos_eint_gpio_init,
		.eint_wkup_init = exynos_eint_wkup_init,
		.suspend	= exynos_pinctrl_suspend,
		.resume		= exynos_pinctrl_resume,
	}, {
	/* pin-controller instance 1 CMGP data */
		.pin_banks      = s5e8825_pin_cmgp,
		.nr_banks       = ARRAY_SIZE(s5e8825_pin_cmgp),
		.eint_gpio_init = exynos_eint_gpio_init,
		.eint_wkup_init = exynos_eint_wkup_init,
		.suspend        = exynos_pinctrl_suspend,
		.resume         = exynos_pinctrl_resume,
        }, {
	/* pin-controller instance 2 GPIO_CHUB data */
		.pin_banks      = s5e8825_pin_chub,
		.nr_banks       = ARRAY_SIZE(s5e8825_pin_chub),
		.eint_gpio_init = exynos_eint_gpio_init,
		.eint_wkup_init = exynos_eint_wkup_init,
		.suspend        = exynos_pinctrl_suspend,
		.resume         = exynos_pinctrl_resume,
	}, {
	/* pin-controller instance 3 HSI data */
		.pin_banks	= s5e8825_pin_hsi,
		.nr_banks	= ARRAY_SIZE(s5e8825_pin_hsi),
		.eint_gpio_init = exynos_eint_gpio_init,
		.suspend	= exynos_pinctrl_suspend,
		.resume		= exynos_pinctrl_resume,
	}, {
	/* pin-controller instance 4 HSIUFS data */
		.pin_banks	= s5e8825_pin_hsiufs,
		.nr_banks	= ARRAY_SIZE(s5e8825_pin_hsiufs),
		.eint_gpio_init = exynos_eint_gpio_init,
		.suspend	= exynos_pinctrl_suspend,
		.resume		= exynos_pinctrl_resume,
	}, {
	/* pin-controller instance 5 PERI data */
		.pin_banks	= s5e8825_pin_peri,
		.nr_banks	= ARRAY_SIZE(s5e8825_pin_peri),
		.eint_gpio_init = exynos_eint_gpio_init,
		.suspend	= exynos_pinctrl_suspend,
		.resume		= exynos_pinctrl_resume,
	}, {
	/* pin-controller instance 6 PERI EMMC data */
		.pin_banks	= s5e8825_pin_perimmc,
		.nr_banks	= ARRAY_SIZE(s5e8825_pin_perimmc),
		.eint_gpio_init = exynos_eint_gpio_init,
		.suspend	= exynos_pinctrl_suspend,
		.resume		= exynos_pinctrl_resume,
	}, {
	/* For this block, pinctrl will not care for interrupt and S2R */
	/* pin-controller instance 7 VTS data */
		.pin_banks	= s5e8825_pin_vts,
		.nr_banks	= ARRAY_SIZE(s5e8825_pin_vts),
	},
};

const struct samsung_pinctrl_of_match_data s5e8825_of_data __initconst = {
	.ctrl		= s5e8825_pin_ctrl,
	.num_ctrl	= ARRAY_SIZE(s5e8825_pin_ctrl),
};
MODULE_LICENSE("GPL");
