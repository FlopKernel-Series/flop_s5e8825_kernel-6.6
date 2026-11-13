# SPDX-License-Identifier: GPL-2.0

obj-$(CONFIG_SCSI_UFS_DWC_TC_PCI) += tc-dwc-g210-pci.o ufshcd-dwc.o tc-dwc-g210.o
obj-$(CONFIG_SCSI_UFS_DWC_TC_PLATFORM) += tc-dwc-g210-pltfrm.o ufshcd-dwc.o tc-dwc-g210.o
obj-$(CONFIG_SCSI_UFS_CDNS_PLATFORM) += cdns-pltfrm.o
obj-$(CONFIG_SCSI_UFS_QCOM) += ufs-qcom.o
obj-$(CONFIG_SCSI_UFS_EXYNOS) += ufs-exynos.o
obj-$(CONFIG_SCSI_UFSHCD_PCI) += ufshcd-pci.o
obj-$(CONFIG_SCSI_UFSHCD_PLATFORM) += ufshcd-pltfrm.o
obj-$(CONFIG_SCSI_UFS_HISI) += ufs-hisi.o
obj-$(CONFIG_SCSI_UFS_MEDIATEK) += ufs-mediatek.o
obj-$(CONFIG_SCSI_UFS_RENESAS) += ufs-renesas.o
obj-$(CONFIG_SCSI_UFS_SPRD) += ufs-sprd.o
obj-$(CONFIG_SCSI_UFS_TI_J721E) += ti-j721e-ufs.o

# SPDX-License-Identifier: GPL-2.0-only
ifdef CONFIG_SCSI_UFS_SAMSUNG
subdir-ccflags-y += $(UFS_DEFS) \
		    -I$(srctree)/drivers/ufs/core \
		    -I$(srctree)/drivers/ufs/host \
		    -I$(srctree)/drivers/ufs/host/s5e8825
endif

obj-$(CONFIG_SCSI_UFS_SAMSUNG)	+= ufs-exynos-core.o
ufs-exynos-core-$(CONFIG_SCSI_UFS_SAMSUNG) += ufs-exynos.o \
			s5e8825/ufs-cal-if.o
ufs-exynos-core-$(CONFIG_SCSI_UFS_PERF) += ufs-exynos-perf.o ufs-exynos-perf-v1.o
ufs-exynos-core-$(CONFIG_SCSI_UFS_DBG) += ufs-exynos-dbg.o
ufs-exynos-core-$(CONFIG_SCSI_UFS_EXYNOS_SRPMB) += ufs-exynos-srpmb.o
ufs-exynos-core-$(CONFIG_SCSI_UFS_EXYNOS_FMP) += ufs-exynos-fmp.o
ufs-exynos-core-$(CONFIG_SEC_UFS_FEATURE) += ufs-sec-feature.o ufs-sec-sysfs.o

# SPDX-License-Identifier: GPL-2.0
# UFSHCD makefile
ifdef CONFIG_SCSI_UFS_SAMSUNG
subdir-ccflags-y += $(UFS_DEFS) \
		    -I$(srctree)/drivers/ufs/core \
	            -I$(srctree)/drivers/ufs/host \
	            -I$(srctree)/drivers/ufs/host/s5e8825
endif

obj-$(CONFIG_SCSI_UFS_SAMSUNG) += ufs-exynos-core.o
ufs-exynos-core-$(CONFIG_SCSI_UFS_SAMSUNG) += ufs-exynos.o \
					s5e8825/ufs-cal-if.o
ufs-exynos-core-$(CONFIG_SCSI_UFS_PERF) += ufs-exynos-perf.o ufs-exynos-perf-v1.o ufs-exynos-gear.o
ufs-exynos-core-$(CONFIG_SCSI_UFS_DBG) += ufs-exynos-dbg.o
ufs-exynos-core-$(CONFIG_SCSI_UFS_EXYNOS_SRPMB) += ufs-exynos-srpmb.o
ufs-exynos-core-$(CONFIG_SCSI_UFS_EXYNOS_FMP) += ufs-exynos-fmp.o

obj-$(CONFIG_EXYNOS_UFS_KUNIT_TEST) += test/

# drivers/ufs/host/Makefile
obj-$(CONFIG_SEC_UFS_FEATURE) += ufs-sec-driver.o
ufs-sec-driver-$(CONFIG_SEC_UFS_FEATURE) += ufs-sec-misc.o

subdir-ccflags-y += $(UFS_DEFS) \
                    -I$(srctree)/drivers/ufs/core \
                    -I$(srctree)/drivers/ufs/host \
                    -I$(srctree)/drivers/ufs/host/s5e8825 
