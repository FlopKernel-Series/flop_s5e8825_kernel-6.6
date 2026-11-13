# SPDX-License-Identifier: GPL-2.0
ccflags-y := -I$(srctree)/drivers/dma-buf/heaps
ccflags-y += -I$(srctree)/$(src)

obj-$(CONFIG_DMABUF_HEAPS_HPA) += hpa_heap.o hpa_trace.o hpa_debug.o
obj-$(CONFIG_DMABUF_HEAPS_HPA) += trace/samsung_trace.o
obj-$(CONFIG_DMABUF_HEAPS_HPA) += utils/generic-folio-pool.o
obj-$(CONFIG_DMABUF_HEAPS_HPA) += secure/ppmp-mapping.o
