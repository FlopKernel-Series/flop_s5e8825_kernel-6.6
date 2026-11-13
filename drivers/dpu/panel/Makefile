
# Makefile for MCD Panel Samsung Driver

# Include paths for DPU headers
DPU_INCLUDE_PATH := $(srctree)/drivers/dpu

ccflags-y := -I$(DPU_INCLUDE_PATH) \
             -I$(DPU_INCLUDE_PATH)/include \
             -I$(DPU_INCLUDE_PATH)/cal_common \
             -I$(DPU_INCLUDE_PATH)/cal_pm \
             -I$(DPU_INCLUDE_PATH)/mcd_cal \
             -I$(DPU_INCLUDE_PATH)/exynos_p2 \
             -I$(DPU_INCLUDE_PATH)/exynos_p2/cal_py \
             -I$(srctree)/drivers/gpu/drm/samsung/panel \
             -I$(srctree)/include

subdir-ccflags-y := $(ccflags-y)

obj-$(CONFIG_DRM_PANEL_MCD_COMMON) += mcd-panel-samsung-drv.o mcd-panel-samsung-helper.o
obj-$(CONFIG_SEC_KUNIT) += kunit_test/
