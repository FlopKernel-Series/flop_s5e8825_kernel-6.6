# SPDX-License-Identifier: GPL-2.0
#
# Makefile for nfc devices
#

obj-$(CONFIG_NFC_FDP)		+= fdp/
obj-$(CONFIG_NFC_PN544)		+= pn544/
obj-$(CONFIG_NFC_MICROREAD)	+= microread/
obj-$(CONFIG_NFC_PN533)		+= pn533/
obj-$(CONFIG_NFC_MEI_PHY)	+= mei_phy.o
obj-$(CONFIG_NFC_SIM)		+= nfcsim.o
obj-$(CONFIG_NFC_PORT100)	+= port100.o
obj-$(CONFIG_NFC_MRVL)		+= nfcmrvl/
obj-$(CONFIG_NFC_TRF7970A)	+= trf7970a.o
obj-$(CONFIG_NFC_ST21NFCA)  	+= st21nfca/
obj-$(CONFIG_NFC_ST_NCI)	+= st-nci/
obj-$(CONFIG_NFC_NXP_NCI)	+= nxp-nci/
obj-$(CONFIG_NFC_S3FWRN5)	+= s3fwrn5/
obj-$(CONFIG_NFC_ST95HF)	+= st95hf/
obj-$(CONFIG_NFC_VIRTUAL_NCI)	+= virtual_ncidev.o

# SPDX-License-Identifier: GPL-2.0
#
# Makefile for nfc devices
#
ifneq ($(SEC_BUILD_CONF_USE_ESE_TZ), false)
	ccflags-y += -DENABLE_ESE_SPI_SECURED
endif

ifeq ($(CONFIG_SAMSUNG_NFC),m)
obj-$(CONFIG_SAMSUNG_NFC)		+= nfc_stm_sec.o
nfc_stm_sec-$(CONFIG_NFC_ST21NFC)		+= st21nfc.o
nfc_stm_sec-$(CONFIG_NFC_ST54SPI_ESE_SUPPORT)	+= st54spi.o
nfc_stm_sec-$(CONFIG_SEC_NFC_LOGGER)		+= nfc_logger/nfc_logger.o
else
obj-$(CONFIG_NFC_ST21NFC)		+= st21nfc.o
obj-$(CONFIG_NFC_ST54SPI_ESE_SUPPORT)	+= st54spi.o
obj-$(CONFIG_SEC_NFC_LOGGER)		+= nfc_logger/nfc_logger.o
endif

ccflags-y 			+= -DRECOVERY_ENABLE -UDEBUG


