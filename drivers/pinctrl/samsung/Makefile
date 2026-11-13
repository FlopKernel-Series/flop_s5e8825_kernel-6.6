# SPDX-License-Identifier: GPL-2.0
# Samsung pin control drivers

obj-$(CONFIG_PINCTRL_SAMSUNG)	+= pinctrl-samsung.o
obj-$(CONFIG_PINCTRL_EXYNOS)	+= pinctrl-exynos.o
obj-$(CONFIG_PINCTRL_EXYNOS_ARM)	+= pinctrl-exynos-arm.o
obj-$(CONFIG_PINCTRL_EXYNOS_ARM64)	+= pinctrl-exynos-arm64.o
obj-$(CONFIG_PINCTRL_S3C64XX)	+= pinctrl-s3c64xx.o

# SPDX-License-Identifier: GPL-2.0
# Samsung pin control drivers

obj-$(CONFIG_PINCTRL_SAMSUNG_EXT)	+= pinctrl-samsung-ext.o
pinctrl-samsung-ext-$(CONFIG_PINCTRL_SAMSUNG_EXT)	+= pinctrl-samsung.o
pinctrl-samsung-ext-$(CONFIG_PINCTRL_EXYNOS_EXT)	+= pinctrl-exynos.o
pinctrl-samsung-ext-$(CONFIG_PINCTRL_EXYNOS_EXT_ARM64)	+= pinctrl-exynos-arm64.o
obj-$(CONFIG_PINCTRL_SEC_GPIO_DVS)	+= secgpio_dvs.o

subdir-ccflags-y += -I${ROOT_DIR}/${KERNEL_DIR}/drivers/pinctrl
