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

#include <errno.h>

#include <gpex_ifpo.h>
#include <gpex_clock.h>
#include <gpexbe_devicetree.h>
#include <gpexbe_pm.h>
#include <gpex_dvfs.h>
#include "gpex_ifpo_sysfs.h"

struct ifpo_info {
	ifpo_mode mode;
	ifpo_status status;
#ifdef CONFIG_MALI_DYNAMIC_IFPO
       int gpu_dynamic_ifpo_util;
       int gpu_dynamic_ifpo_freq;
       int gpu_dynamic_ifpo_disable;
       int gpu_ifpo_cnt;
       int gpu_ifpo_get_flag;
#endif

#ifdef CONFIG_MALI_DELAYED_IFPO_ON_RESUME
       u32 ifpo_delay;
#endif
};

static struct ifpo_info ifpo;

#ifdef CONFIG_MALI_DYNAMIC_IFPO
int gpex_ifpo_get_gpu_ifpo_cnt(void)
{
       return ifpo.gpu_ifpo_cnt;
}

void gpex_ifpo_set_gpu_ifpo_cnt(int count)
{
       ifpo.gpu_ifpo_cnt = count;
}

void gpex_ifpo_set_gpu_ifpo_get_flag(int flag)
{
       ifpo.gpu_ifpo_get_flag = flag;
}

int gpex_ifpo_get_gpu_dynamic_ifpo_util(void)
{
       return ifpo.gpu_dynamic_ifpo_util;
}

void gpex_ifpo_set_gpu_dynamic_ifpo_util(int util)
{
       ifpo.gpu_dynamic_ifpo_util = util;
}

int gpex_ifpo_get_gpu_dynamic_ifpo_freq(void)
{
       return ifpo.gpu_dynamic_ifpo_freq;
}

void gpex_ifpo_set_gpu_dynamic_ifpo_freq(int freq)
{
       ifpo.gpu_dynamic_ifpo_freq = freq;
}

int gpex_ifpo_get_gpu_dynamic_ifpo_disable(void)
{
       return ifpo.gpu_dynamic_ifpo_disable;
}

void gpex_ifpo_set_gpu_dynamic_ifpo_disable(int disable)
{
       ifpo.gpu_dynamic_ifpo_disable = disable;
}

int gpex_check_ifpo_status(void) {
       int ret = 1;
       if((gpex_dvfs_get_utilization() >= ifpo.gpu_dynamic_ifpo_util
          && gpex_clock_get_cur_clock() >= ifpo.gpu_dynamic_ifpo_freq)
          || ifpo.gpu_dynamic_ifpo_disable)
           ret = 0;
#ifdef CONFIG_MALI_DELAYED_IFPO_ON_RESUME
        else if (ifpo.ifpo_delay >0)
               ret = 0;
#endif
       return ret;
}
#endif

#ifdef CONFIG_MALI_DELAYED_IFPO_ON_RESUME
void gpex_decrease_ifpo_delay_count(void){
       if(ifpo.ifpo_delay > 0)
               ifpo.ifpo_delay --;
}

#define IFPO_DELAY_DEFAULT 30
void gpex_reset_ifpo_delay_value(void){
       ifpo.ifpo_delay = IFPO_DELAY_DEFAULT;
}
#endif

int gpex_ifpo_power_down(bool check_status)
{
	int ret = 0;

	if (!ifpo.mode)
		return 0;
#ifdef CONFIG_MALI_DYNAMIC_IFPO
       if(check_status && !gpex_check_ifpo_status())
               return 0;
#endif

	gpex_clock_mutex_lock();

	/* inter frame power off */
	ret = gpexbe_pm_pd_control_down();

	if (!ret)
		ifpo.status = IFPO_POWER_DOWN;

	gpex_clock_mutex_unlock();
#ifdef CONFIG_MALI_DYNAMIC_IFPO
       if(ifpo.gpu_ifpo_get_flag)
               ifpo.gpu_ifpo_cnt++;
#endif

	return ret;
}

int gpex_ifpo_power_up(bool check_status)
{
	int ret = 0;

	if (!ifpo.mode)
		return 0;
#ifdef CONFIG_MALI_DYNAMIC_IFPO
       if(check_status && !gpex_check_ifpo_status())
               return 0;
#endif
	gpex_clock_mutex_lock();

	/* inter frame power on */
	ret = gpexbe_pm_pd_control_up();

	if (!ret)
		ifpo.status = IFPO_POWER_UP;

	gpex_clock_mutex_unlock();

	return ret;
}

/* return non-zero value when power off for now */
ifpo_status gpex_ifpo_get_status(void)
{
	return ifpo.status;
}

ifpo_mode gpex_ifpo_get_mode(void)
{
	return ifpo.mode;
}

int gpex_ifpo_init(void)
{
	ifpo.mode = (ifpo_mode)gpexbe_devicetree_get_int(gpu_inter_frame_pm);
#ifdef CONFIG_MALI_DYNAMIC_IFPO
       gpex_ifpo_sysfs_init();

       ifpo.gpu_dynamic_ifpo_util = gpexbe_devicetree_get_int(gpu_inter_frame_dynamic_util);
       ifpo.gpu_dynamic_ifpo_freq = gpexbe_devicetree_get_int(gpu_inter_frame_dynamic_freq);
       ifpo.gpu_dynamic_ifpo_disable = 0;
#endif

#ifdef CONFIG_MALI_DELAYED_IFPO_ON_RESUME
       ifpo.ifpo_delay = 0;
#endif
	/* TODO: delete this line! This is to force enable IFPO regardless of the DT value */
	/* TODO: Or maybe remove inter_frame_pm from DT and let kconfig decide IFPO enable/disable? */
	ifpo.mode = IFPO_ENABLED;
	ifpo.status = IFPO_POWER_UP;

	return 0;
}

void gpex_ifpo_term(void)
{
	ifpo.mode = IFPO_DISABLED;

	/* TODO: power up if in power down state? */
	if (ifpo.status == IFPO_POWER_DOWN)
		gpex_ifpo_power_up(false);

	return;
}
