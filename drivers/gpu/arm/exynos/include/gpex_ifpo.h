/* SPDX-License-Identifier: GPL-2.0 */

/*
 * (C) COPYRIGHT 2021 Samsung Electronics Inc. All rights reserved.
 *
 * This program is free software and is provided to you under the terms of the
 * GNU General Public License version 2 as published by the Free Software
 * Foundation, and any use by you of this program is subject to the terms
 * of such GNU licence.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you can access it online at
 * http://www.gnu.org/licenses/gpl-2.0.html.
 */

#ifndef _MALI_EXYNOS_IFPO_H_
#define _MALI_EXYNOS_IFPO_H_

#include <mali_kbase.h>
#include <linux/device.h>

typedef enum ifpo_mode {
	IFPO_DISABLED = 0,
	IFPO_ENABLED,
} ifpo_mode;

typedef enum ifpo_state {
	IFPO_POWER_DOWN = 0,
	IFPO_POWER_UP,
} ifpo_status;


#ifdef CONFIG_MALI_DYNAMIC_IFPO

/**
 * gpex_ifpo_get_gpu_ifpo_cnt() - Return gpu_ifpo_cnt
 */
int gpex_ifpo_get_gpu_ifpo_cnt(void);

/**
 * gpex_ifpo_set_gpu_ifpo_cnt() - Set gpu_ifpo_cnt
 */
void gpex_ifpo_set_gpu_ifpo_cnt(int count);

/**
 * gpex_ifpo_get_gpu_get_flag() - Return gpu_get_flag
 */
void gpex_ifpo_set_gpu_ifpo_get_flag(int flag);

/**
 * gpex_ifpo_get_gpu_dynamic_ifpo_util() - Get gpu_dynamic_ifpo_util
 */
int gpex_ifpo_get_gpu_dynamic_ifpo_util(void);

/**
 * gpex_ifpo_set_gpu_dynamic_ifpo_util() - Set gpu_dynamic_ifpo_util
 */
void gpex_ifpo_set_gpu_dynamic_ifpo_util(int util);

/**
 * gpex_ifpo_get_gpu_dynamic_ifpo_freq() - Get gpu_dynamic_ifpo_freq
 */
int gpex_ifpo_get_gpu_dynamic_ifpo_freq(void);

/**
 * gpex_ifpo_set_gpu_dynamic_ifpo_freq() - Set gpu_dynamic_ifpo_freq
 */
void gpex_ifpo_set_gpu_dynamic_ifpo_freq(int freq);

/**
 * gpex_ifpo_get_gpu_dynamic_ifpo_disable() - Get gpu_dynamic_ifpo_disable
 */
int gpex_ifpo_get_gpu_dynamic_ifpo_disable(void);

/**
 * gpex_ifpo_get_gpu_dynamic_ifpo_disable() - Set gpu_dynamic_ifpo_disable
 */
void gpex_ifpo_set_gpu_dynamic_ifpo_disable(int disable);

int gpex_check_ifpo_status(void);

#endif

#ifdef CONFIG_MALI_DELAYED_IFPO_ON_RESUME
void gpex_decrease_ifpo_delay_count(void);

void gpex_reset_ifpo_delay_value(void);
#endif


/**
 * gpex_ifpo_init() - Initialize IFPO module
 *
 * Initializes to enabled and powered-on state
 *
 * Return: 0 on success
 */
int gpex_ifpo_init(void);

/**
 * gpex_ifpo_init() - Terminate IFPO module
 */
void gpex_ifpo_term(void);

/**
 * gpex_ifpo_power_up() - power on the gpu from ifpo power down state
 *
 * Context: takes gpex_clock_lock (if clock module enabled)
 *
 * Return: 0 on success
 */
int gpex_ifpo_power_up(bool check_status);

/**
 * gpex_ifpo_power_down() - power off the gpu from ifpo power up state
 *
 * Context: takes gpex_clock_lock (if clock module enabled)
 *
 * Return: 0 on success
 */
int gpex_ifpo_power_down(bool check_status);

/**
 * gpex_ifpo_get_status() - get current GPU power state as controlled by IFPO
 *
 * Return: IFPO power state of enum type ifpo_status (gpu powered up or down)
 */
ifpo_status gpex_ifpo_get_status(void);

/**
 * gpex_ifpo_get_mode() - get current IFPO mode (enabled or disabled)
 *
 * Return: IFPO mode (enabled or disabled)
 */
ifpo_mode gpex_ifpo_get_mode(void);

#endif /* _MALI_EXYNOS_IFPO_H_ */
