#
# Makefile for the stui Module
#

ccflags-y += -I$(srctree)/$(src)
ccflags-y += -I$(srctree)/$(src)/../tzdev/include/tzdev
ccflags-y += -DUSE_TEE_CLIENT_API

tuihw-inf-objs := stui_inf.o stui_log.o

tuihw-objs := main.o
tuihw-objs += stui_core.o
tuihw-objs += stui_log.o

ccflags-y += -I$(srctree)/$(src)/platforms
ccflags-y += -I$(srctree)/drivers
tuihw-objs += platforms/stui_hal_display.o
tuihw-objs += platforms/stui_hal_touch.o

ifeq ($(CONFIG_SOC_S5E9925),y)
ccflags-y += -DCONFIG_SOC_S5E9925
endif

ifeq ($(CONFIG_SOC_S5E8825),y)
ccflags-y += -DCONFIG_SOC_S5E8825
endif

ifdef CONFIG_EXYNOS_DPU_USE_DUAL_DRV
ccflags-y += -DCONFIG_EXYNOS_DPU_USE_DUAL_DRV
endif

ifdef CONFIG_SAMSUNG_TUI_LOWLEVEL
tuihw-objs += iwd_agent.o

ccflags-y += -I$(srctree)/$(src)/../tzdev
ccflags-y += -DCONFIG_SAMSUNG_TUI_LOWLEVEL
endif

ifneq ($(TARGET_BUILD_VARIANT),user)
ccflags-y += -DDEBUG_LOG_ALLOWED
endif

obj-$(CONFIG_SAMSUNG_TUI) += tuihw.o tuihw-inf.o
