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

#include <gpex_pm.h>
#include <gpex_dvfs.h>
#include <gpex_clock.h>
#include <gpex_utils.h>
#include <gpex_ifpo.h>
#include "gpex_ifpo_sysfs.h"

static ssize_t show_ifpo_count(char *buf)
{
       ssize_t ret = 0;


       int ifpo_count = gpex_ifpo_get_gpu_ifpo_cnt();

       ret += snprintf(buf+ret, PAGE_SIZE-ret, "%d", ifpo_count);

       if (ret < PAGE_SIZE - 1) {
               ret += snprintf(buf+ret, PAGE_SIZE-ret, "\n");
       } else {
               buf[PAGE_SIZE-2] = '\n';
               buf[PAGE_SIZE-1] = '\0';
               ret = PAGE_SIZE-1;
       }

       gpex_ifpo_set_gpu_ifpo_cnt(0);

       return ret;
}
CREATE_SYSFS_DEVICE_READ_FUNCTION(show_ifpo_count);

static ssize_t set_ifpo_count(const char *buf, size_t count)
{

       if (sysfs_streq("0", buf))
               gpex_ifpo_set_gpu_ifpo_get_flag(0);
       else if (sysfs_streq("1", buf))
               gpex_ifpo_set_gpu_ifpo_get_flag(1);

       return count;
}
CREATE_SYSFS_DEVICE_WRITE_FUNCTION(set_ifpo_count);

static ssize_t show_dynamic_ifpo_util(char *buf)
{
       ssize_t ret = 0;

       int gpu_dynamic_ifpo_util = gpex_ifpo_get_gpu_dynamic_ifpo_util();
       ret += snprintf(buf+ret, PAGE_SIZE-ret, "%d", gpu_dynamic_ifpo_util);

       if (ret < PAGE_SIZE - 1) {
               ret += snprintf(buf+ret, PAGE_SIZE-ret, "\n");
       } else {
               buf[PAGE_SIZE-2] = '\n';
               buf[PAGE_SIZE-1] = '\0';
               ret = PAGE_SIZE-1;
       }

       return ret;

}
CREATE_SYSFS_DEVICE_READ_FUNCTION(show_dynamic_ifpo_util);

static ssize_t set_dynamic_ifpo_util(const char *buf, size_t count)
{
       int ret;
    int gpu_dynamic_ifpo_util;
       ret = kstrtoint(buf, 0, &gpu_dynamic_ifpo_util);
       if (ret) {
               GPU_LOG(MALI_EXYNOS_WARNING, "%s: invalid value\n", __func__);
               return -ENOENT;
       }

       gpex_ifpo_set_gpu_dynamic_ifpo_util(gpu_dynamic_ifpo_util);
       GPU_LOG(MALI_EXYNOS_WARNING, "%s: gpu_dynamic_ifpo_util %d\n", __func__, gpu_dynamic_ifpo_util);

       return count;
}
CREATE_SYSFS_DEVICE_WRITE_FUNCTION(set_dynamic_ifpo_util);

static ssize_t show_dynamic_ifpo_freq(char *buf)
{
        ssize_t ret = 0;
               int gpu_dynamic_ifpo_freq = gpex_ifpo_get_gpu_dynamic_ifpo_freq();
        ret += snprintf(buf+ret, PAGE_SIZE-ret, "%d", gpu_dynamic_ifpo_freq);

        if (ret < PAGE_SIZE - 1) {
                ret += snprintf(buf+ret, PAGE_SIZE-ret, "\n");
        } else {
                buf[PAGE_SIZE-2] = '\n';
                buf[PAGE_SIZE-1] = '\0';
                ret = PAGE_SIZE-1;
        }

        return ret;

}
CREATE_SYSFS_DEVICE_READ_FUNCTION(show_dynamic_ifpo_freq);

static ssize_t set_dynamic_ifpo_freq(const char *buf, size_t count)
{
       int ret;
       int gpu_dynamic_ifpo_freq;
       ret = kstrtoint(buf, 0, &gpu_dynamic_ifpo_freq);
       if (ret) {
               GPU_LOG(MALI_EXYNOS_WARNING, "%s: invalid value\n", __func__);
               return -ENOENT;
       }

       gpex_ifpo_set_gpu_dynamic_ifpo_freq(gpu_dynamic_ifpo_freq);
       GPU_LOG(MALI_EXYNOS_WARNING, "%s: gpu_dynamic_ifpo_util %d\n", __func__, gpu_dynamic_ifpo_freq);

       return count;
}
CREATE_SYSFS_DEVICE_WRITE_FUNCTION(set_dynamic_ifpo_freq);

static ssize_t show_dynamic_ifpo_disable(char *buf)
{
       ssize_t ret = 0;
       bool gpu_dynamic_ifpo_disable = gpex_ifpo_get_gpu_dynamic_ifpo_disable();
       ret += snprintf(buf+ret, PAGE_SIZE-ret, "%d", gpu_dynamic_ifpo_disable);

       if (ret < PAGE_SIZE - 1) {
               ret += snprintf(buf+ret, PAGE_SIZE-ret, "\n");
       } else {
               buf[PAGE_SIZE-2] = '\n';
               buf[PAGE_SIZE-1] = '\0';
               ret = PAGE_SIZE-1;
       }

       return ret;

}
CREATE_SYSFS_DEVICE_READ_FUNCTION(show_dynamic_ifpo_disable);

static ssize_t set_dynamic_ifpo_disable(const char *buf, size_t count)
{
       int ret;
    int gpu_dynamic_ifpo_disable;
       ret = kstrtoint(buf, 0, &gpu_dynamic_ifpo_disable);
       if (ret) {
               GPU_LOG(MALI_EXYNOS_WARNING, "%s: invalid value\n", __func__);
               return -ENOENT;
       }

       gpex_ifpo_set_gpu_dynamic_ifpo_disable(gpu_dynamic_ifpo_disable);
       GPU_LOG(MALI_EXYNOS_WARNING, "%s: gpu_dynamic_ifpo_disable %d\n", __func__, gpu_dynamic_ifpo_disable);

       return count;
}
CREATE_SYSFS_DEVICE_WRITE_FUNCTION(set_dynamic_ifpo_disable);

int gpex_ifpo_sysfs_init(void)
{

       GPEX_UTILS_SYSFS_DEVICE_FILE_ADD(ifpo_count, show_ifpo_count, set_ifpo_count);
       GPEX_UTILS_SYSFS_DEVICE_FILE_ADD(dynamic_ifpo_util, show_dynamic_ifpo_util, set_dynamic_ifpo_util);
       GPEX_UTILS_SYSFS_DEVICE_FILE_ADD(dynamic_ifpo_freq, show_dynamic_ifpo_freq, set_dynamic_ifpo_freq);
       GPEX_UTILS_SYSFS_DEVICE_FILE_ADD(dynamic_ifpo_disable, show_dynamic_ifpo_disable,
                                                                       set_dynamic_ifpo_disable);

       return 0;
}



