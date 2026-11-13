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

#include <gpex_ifpo.h>

int gpex_ifpo_init(void)
{
	return 0;
}

void gpex_ifpo_term(void)
{
	return;
}

int gpex_ifpo_power_up(bool check_status)
{
        CSTD_UNUSED(check_status);
	return 0;
}

int gpex_ifpo_power_down(bool check_status)
{
        CSTD_UNUSED(check_status);
	return 0;
}

ifpo_status gpex_ifpo_get_status(void)
{
	return IFPO_POWER_UP;
}

ifpo_mode gpex_ifpo_get_mode(void)
{
	return IFPO_DISABLED;
}


#ifdef CONFIG_MALI_DYNAMIC_IFPO
int gpex_ifpo_get_gpu_ifpo_cnt(void)
{
       return 0;
}

void gpex_ifpo_set_gpu_ifpo_cnt(int count)
{
       CSTD_UNUSED(count);
}

void gpex_ifpo_set_gpu_ifpo_get_flag(int flag)
{
       CSTD_UNUSED(flag);
}

int gpex_ifpo_get_gpu_dynamic_ifpo_util(void)
{
       return 0;
}

void gpex_ifpo_set_gpu_dynamic_ifpo_util(int util)
{
       CSTD_UNUSED(util);
}

int gpex_ifpo_get_gpu_dynamic_ifpo_freq(void)
{
       return 0;
}

void gpex_ifpo_set_gpu_dynamic_ifpo_freq(int freq)
{
       CSTD_UNUSED(freq);
}

int gpex_ifpo_get_gpu_dynamic_ifpo_disable(void)
{
       return 0;
}

void gpex_ifpo_set_gpu_dynamic_ifpo_disable(int disable)
{
       CSTD_UNUSED(disable);
}

int gpex_check_ifpo_status(void)
{
       return 0;
}
#endif

#ifdef CONFIG_MALI_DELAYED_IFPO_ON_RESUME
void gpex_decrease_ifpo_delay_count(void)
{
       return;
}

void gpex_reset_ifpo_delay_value(void)
{
       return;
}
#endif
