// SPDX-License-Identifier: GPL-2.0
#ifndef __LINUX_USB_EXYNOS_AUDIO_POLICY_H
#define __LINUX_USB_EXYNOS_AUDIO_POLICY_H

#include <linux/kconfig.h>
#include <linux/types.h>

static inline bool exynos_usb_audio_use_legacy(void)
{
	return IS_ENABLED(CONFIG_SND_EXYNOS_USB_AUDIO_LEGACY);
}

#endif
