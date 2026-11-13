#include <linux/of.h>
#include <linux/phy/phy.h>
#include <linux/platform_device.h>
#include <soc/samsung/exynos-cpupm.h>
#ifdef CONFIG_OF
#include <linux/of_device.h>
#endif

#include "phy-exynos-usbdrd.h"
#ifdef CONFIG_SND_EXYNOS_USB_AUDIO_GIC
#include <sound/samsung/abox.h>
static struct device *abox_dev;
#endif

int otg_connection;
EXPORT_SYMBOL_GPL(otg_connection);

int is_otg_only;
EXPORT_SYMBOL_GPL(is_otg_only);

#define OTG_NO_CONNECT		0
#define OTG_CONNECT_ONLY	1
#define OTG_DEVICE_CONNECT	2

u32 otg_is_connect(void)
{
	if (!otg_connection)
		return OTG_NO_CONNECT;
	else if (is_otg_only)
		return OTG_CONNECT_ONLY;
	else
		return OTG_DEVICE_CONNECT;
}
EXPORT_SYMBOL_GPL(otg_is_connect);

static int exynos_usb_pm_notifier(struct notifier_block *nb,
		unsigned long action, void *nb_data)
{
	struct exynos_usbdrd_phy *phy_drd
		= container_of(nb, struct exynos_usbdrd_phy, pm_nb);

	switch (action) {
	case PM_SUSPEND_PREPARE:
		pr_info("%s suspend prepare\n", __func__);
		phy_drd->phy_usbdrd_suspended = true;
		reinit_completion(&phy_drd->resume_cmpl);
		break;
	case PM_POST_SUSPEND:
		pr_info("%s post suspend\n", __func__);
		phy_drd->phy_usbdrd_suspended = false;
		complete(&phy_drd->resume_cmpl);
		break;
	default:
		break;
	}
	return NOTIFY_OK;
}

void exynos_usb_pm_noti_init(struct exynos_usbdrd_phy *phy_drd)
{
	init_completion(&phy_drd->resume_cmpl);
	phy_drd->phy_usbdrd_suspended = false;
	phy_drd->pm_nb.notifier_call = exynos_usb_pm_notifier;
	register_pm_notifier(&phy_drd->pm_nb);
}

int exynos_usbdrd_phy_set_common(struct exynos_usbdrd_phy *phy_drd,
				enum phy_mode mode, int submode)
{
	int ret = 0;
	int phymode = mode;

	switch (phymode) {
	case PHY_MODE_BUS_SUSPEND:
		break;
	case PHY_MODE_BUS_RESUME:
		break;
	case PHY_MODE_ABOX_POWER:
#ifdef CONFIG_SND_EXYNOS_USB_AUDIO_GIC
		if (submode == 1) {
			if (phy_drd->phy_usbdrd_suspended) {
				pr_info("%s: wait resume completion\n", __func__);
				wait_for_completion_timeout(&phy_drd->resume_cmpl,
							    msecs_to_jiffies(5000));
			}
			ret = abox_request_power_sync(abox_dev, 0x7007, "TFA9874");
			if (ret < 0)
				dev_err(abox_dev, "failed to abox_request_power_sync\n");

			ret = abox_wait_boot_timeout(abox_dev, nsecs_to_jiffies(100000000UL));
			if (ret < 0)
				dev_err(abox_dev, "failed to abox_wait_boot_timeout\n");
		} else {
			abox_release_power(abox_dev, 0x7007, "TFA9874");
		}
#endif
		break;
	case PHY_MODE_CALL_ENTER:
		break;
	case PHY_MODE_CALL_EXIT:
		break;
	case PHY_MODE_SUSPEND_BYPASS:
		break;
	case PHY_MODE_RESUME_BYPASS:
		break;
	default:
		break;
	}

	return ret;
}
EXPORT_SYMBOL_GPL(exynos_usbdrd_phy_set_common);

#ifdef CONFIG_SND_EXYNOS_USB_AUDIO_GIC
void get_exynos_abox_device(void)
{
	struct device_node *np = NULL;
	struct device_node *np_abox;
	struct platform_device *pdev_abox;

	np = of_find_compatible_node(NULL, NULL, "synopsys,dwc3");
	if (!np) {
		pr_err("%s: failed to get the dwc3 node\n", __func__);
		return;
	}

	np_abox = of_parse_phandle(np, "abox", 0);
	if(!np_abox) {
		pr_err("Failed to get abox device node\n");
		return;
	}

	pdev_abox = of_find_device_by_node(np_abox);
	if (!pdev_abox) {
		pr_err("Failed to get abox platform device\n");
		return;
	}

	abox_dev = &pdev_abox->dev;
}
EXPORT_SYMBOL_GPL(get_exynos_abox_device);
#endif
