#
# Makefile for BTS device driver
#

obj-$(CONFIG_EXYNOS_BTS)	+= exynos-bts.o

# Chipset Dependent code
ifdef CONFIG_SOC_S5E8825
obj-$(CONFIG_EXYNOS_BTS)	+= exynos-btsops8825.o
endif
