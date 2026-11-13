/* SPDX-License-Identifier: GPL-2.0 */
/*
 * (C) Copyright 2025 SAMSUNG Electronics
 * Author: wooseok.oh@samsung.com (Woo-Seok Oh)
 *
 * This software is proprietary of Samsung Electronics.
 * No part of this software, either material or conceptual may be copied or distributed, transmitted
 * transcribed, stored in a retrieval system or translated into any human or computer language in an
 * form by any means,
 * electronic, mechanical, manual or otherwise, or disclosed
 * to third parties without the express written permission of Samsung Electronics.
 *
 */

typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DATA : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_RAWAONLANE1_DIG_AFE_ATT_IDAC_OFST;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DATA : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_RAWAONLANE1_DIG_AFE_CTLE_IDAC_OFST;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DATA : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_RAWAONLANE1_DIG_AFE_VGA1_IDAC_OFST;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DATA : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_RAWAONLANE1_DIG_RX_ADAPT_FOM;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DATA : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_RAWAONLANE1_DIG_DFE_SUMMER_ODD_IDAC_OFST;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DATA : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_RAWAONLANE1_DIG_DFE_PHASE_EVEN_VDAC_OFST;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DATA : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_RAWAONLANE1_DIG_DFE_PHASE_ODD_VDAC_OFST;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DATA : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_RAWAONLANE1_DIG_DFE_EVEN_REF_LVL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DATA : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_RAWAONLANE1_DIG_DFE_ODD_REF_LVL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DATA : 5;
		unsigned RESERVED_15_5 : 11;
	} b;
} CR_RAWAONLANE1_DIG_RX_PHSADJ_LIN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DATA : 5;
		unsigned RESERVED_15_5 : 11;
	} b;
} CR_RAWAONLANE1_DIG_RX_PHSADJ_MAP;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DATA : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_RAWAONLANE1_DIG_DFE_DATA_EVEN_HIGH_VDAC_OFST;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DATA : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_RAWAONLANE1_DIG_DFE_DATA_EVEN_LOW_VDAC_OFST;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DATA : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_RAWAONLANE1_DIG_DFE_DATA_ODD_HIGH_VDAC_OFST;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DATA : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_RAWAONLANE1_DIG_DFE_DATA_ODD_LOW_VDAC_OFST;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DATA : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_RAWAONLANE1_DIG_DFE_BYPASS_EVEN_VDAC_OFST;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DATA : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_RAWAONLANE1_DIG_DFE_BYPASS_ODD_VDAC_OFST;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DATA : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_RAWAONLANE1_DIG_DFE_ERROR_EVEN_VDAC_OFST;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DATA : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_RAWAONLANE1_DIG_DFE_ERROR_ODD_VDAC_OFST;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DATA : 7;
		unsigned RESERVED_15_7 : 9;
	} b;
} CR_RAWAONLANE1_DIG_RX_IQ_PHASE_ADJUST;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DATA : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_RAWAONLANE1_DIG_MPLLA_COARSE_TUNE;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DATA : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_RAWAONLANE1_DIG_MPLLB_COARSE_TUNE;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DATA : 1;
		unsigned PH2_PWRUP_DONE : 1;
		unsigned RESERVED_15_2 : 14;
	} b;
} CR_RAWAONLANE1_DIG_INIT_PWRUP_DONE;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned ATT_ADPT_VAL : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_RAWAONLANE1_DIG_RX_ADPT_ATT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned VGA_ADPT_VAL : 10;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_RAWAONLANE1_DIG_RX_ADPT_VGA;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned CTLE_BOOST_ADPT_VAL : 10;
		unsigned CTLE_POLE_ADPT_VAL : 3;
		unsigned RESERVED_15_13 : 3;
	} b;
} CR_RAWAONLANE1_DIG_RX_ADPT_CTLE;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DFE_TAP1_ADPT_VAL : 13;
		unsigned RESERVED_15_13 : 3;
	} b;
} CR_RAWAONLANE1_DIG_RX_ADPT_DFE_TAP1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DATA : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWAONLANE1_DIG_RX_ADAPT_DONE;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned FAST_RX_STARTUP_CAL : 1;
		unsigned FAST_RX_ADAPT : 1;
		unsigned FAST_RX_AFE_CAL : 1;
		unsigned FAST_RX_DFE_CAL : 1;
		unsigned FAST_RX_BYPASS_CAL : 1;
		unsigned FAST_RX_REFLVL_CAL : 1;
		unsigned FAST_RX_IQ_CAL : 1;
		unsigned FAST_RX_AFE_ADAPT : 1;
		unsigned FAST_RX_DFE_ADAPT : 1;
		unsigned FAST_SUP : 1;
		unsigned FAST_TX_CMN_MODE : 1;
		unsigned FAST_TX_RXDET : 1;
		unsigned FAST_RX_PWRUP : 1;
		unsigned FAST_RX_VCO_WAIT : 1;
		unsigned FAST_RX_VCO_CAL : 1;
		unsigned RESERVED_15_15 : 1;
	} b;
} CR_RAWAONLANE1_DIG_FAST_FLAGS;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DFE_TAP2_ADPT_VAL : 12;
		unsigned RESERVED_15_12 : 4;
	} b;
} CR_RAWAONLANE1_DIG_RX_ADPT_DFE_TAP2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DFE_TAP3_ADPT_VAL : 12;
		unsigned RESERVED_15_12 : 4;
	} b;
} CR_RAWAONLANE1_DIG_RX_ADPT_DFE_TAP3;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DFE_TAP4_ADPT_VAL : 12;
		unsigned RESERVED_15_12 : 4;
	} b;
} CR_RAWAONLANE1_DIG_RX_ADPT_DFE_TAP4;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DFE_TAP5_ADPT_VAL : 12;
		unsigned RESERVED_15_12 : 4;
	} b;
} CR_RAWAONLANE1_DIG_RX_ADPT_DFE_TAP5;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_ANA_SLICER_CTRL_E : 4;
		unsigned RESERVED_15_4 : 12;
	} b;
} CR_RAWAONLANE1_DIG_RX_SLICER_CTRL_EVEN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_ANA_SLICER_CTRL_O : 4;
		unsigned RESERVED_15_4 : 12;
	} b;
} CR_RAWAONLANE1_DIG_RX_SLICER_CTRL_ODD;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned LANE_CMNCAL_MPLL_INIT : 1;
		unsigned LANE_CMNCAL_MPLL_DONE : 1;
		unsigned RESERVED_15_2 : 14;
	} b;
} CR_RAWAONLANE1_DIG_LANE_CMNCAL_MPLL_STATUS;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned VAL : 16;
	} b;
} CR_RAWAONLANE1_DIG_ADPT_CTL_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned VAL : 16;
	} b;
} CR_RAWAONLANE1_DIG_ADPT_CTL_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned VAL : 16;
	} b;
} CR_RAWAONLANE1_DIG_ADPT_CTL_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned VAL : 16;
	} b;
} CR_RAWAONLANE1_DIG_ADPT_CTL_3;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned VAL : 16;
	} b;
} CR_RAWAONLANE1_DIG_ADPT_CTL_4;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned VAL : 16;
	} b;
} CR_RAWAONLANE1_DIG_ADPT_CTL_5;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned VAL : 16;
	} b;
} CR_RAWAONLANE1_DIG_ADPT_CTL_6;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned VAL : 16;
	} b;
} CR_RAWAONLANE1_DIG_ADPT_CTL_7;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned LANE_MPLLA_DISABLE : 1;
		unsigned LANE_MPLLB_DISABLE : 1;
		unsigned RESERVED_15_2 : 14;
	} b;
} CR_RAWAONLANE1_DIG_MPLL_DISABLE;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned FAST_RX_CONT_CAL_ADAPT : 1;
		unsigned FAST_RX_CONT_ADAPT : 1;
		unsigned FAST_RX_CONT_DATA_CAL : 1;
		unsigned FAST_RX_CONT_PHASE_CAL : 1;
		unsigned FAST_RX_CONT_AFE_CAL : 1;
		unsigned FAST_TX_CONT_DCC_CAL : 1;
		unsigned FAST_RX_CONT_DCC_CAL : 1;
		unsigned FAST_RX_CONT_VPHUD_CAL : 1;
		unsigned FAST_RX_CONT_VREF_CAL : 1;
		unsigned FAST_TX_DCC_CAL : 1;
		unsigned FAST_RX_DCC_CAL : 1;
		unsigned FAST_RX_VPHUD_CAL : 1;
		unsigned FAST_RX_VREF_CAL : 1;
		unsigned SKIP_TX_RTUNE_CAL : 1;
		unsigned FAST_RX_SIGDET_CAL : 1;
		unsigned RESERVED_15_15 : 1;
	} b;
} CR_RAWAONLANE1_DIG_FAST_FLAGS_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned LANE_CMNCAL_RCAL_INIT : 1;
		unsigned LANE_CMNCAL_RCAL_DONE : 1;
		unsigned RESERVED_15_2 : 14;
	} b;
} CR_RAWAONLANE1_DIG_LANE_CMNCAL_RCAL_STATUS;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_DISABLE_OVRD_VAL : 1;
		unsigned RX_DISABLE_OVRD_EN : 1;
		unsigned TX_DISABLE_OVRD_VAL : 1;
		unsigned TX_DISABLE_OVRD_EN : 1;
		unsigned RESERVED_15_4 : 12;
	} b;
} CR_RAWAONLANE1_DIG_TXRX_OVRD_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_LOS_MASK_CNT : 9;
		unsigned RESERVED_15_9 : 7;
	} b;
} CR_RAWAONLANE1_DIG_RX_LOS_MASK_CTL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned ISOLATE_SIGDET_HF : 1;
		unsigned MASK_RX_PMA_SIGDET_HF_WITH_LF : 1;
		unsigned RX_SIGDEF_HF_FILT_OVR_DIS : 1;
		unsigned RX_SIGDEF_HF_FILT_OVR : 1;
		unsigned RESERVED_15_4 : 12;
	} b;
} CR_RAWAONLANE1_DIG_RX_SIGDET_FILT_CTRL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_VREFGEN_MASTER : 1;
		unsigned RX_PMA_SQ_OUT : 1;
		unsigned RESERVED_15_2 : 14;
	} b;
} CR_RAWAONLANE1_DIG_STATS;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_PMA_SQ_CTRL_TRESH_OVRD_VAL : 3;
		unsigned RX_PMA_SQ_CTRL_TRESH_OVRD_EN : 1;
		unsigned RX_PMA_SQ_CTRL_RESP_OVRD_VAL : 2;
		unsigned RX_PMA_SQ_CTRL_RESP_OVRD_EN : 1;
		unsigned RX_PMA_SQ_WEAKKEEP_OVRD_VAL : 1;
		unsigned RX_PMA_SQ_WEAKKEEP_OVRD_EN : 1;
		unsigned RX_PMA_SQ_INV_POLARITY_OVRD_VAL : 1;
		unsigned RX_PMA_SQ_INV_POLARITY_OVRD_EN : 1;
		unsigned RX_PMA_SQ_EN_OVRD_VAL : 1;
		unsigned RX_PMA_SQ_EN_OVRD_EN : 1;
		unsigned RESERVED_15_13 : 3;
	} b;
} CR_RAWAONLANE1_DIG_RX_OVRD_OUT_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_PMA_VREFGEN_EN_OVRD_VAL : 1;
		unsigned RX_PMA_VREFGEN_EN_OVRD_EN : 1;
		unsigned RX_SQ_OUT_OVRD_VAL : 1;
		unsigned RX_SQ_OUT_OVRD_EN : 1;
		unsigned RESERVED_15_4 : 12;
	} b;
} CR_RAWAONLANE1_DIG_RX_OVRD_OUT_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_PMA_SIGDET_LF_FILTER_EN_OVRD_VAL : 1;
		unsigned RX_PMA_SIGDET_LF_FILTER_EN_OVRD_EN : 1;
		unsigned RX_PMA_SIGDET_LF_EN_OVRD_VAL : 1;
		unsigned RX_PMA_SIGDET_LF_EN_OVRD_EN : 1;
		unsigned RX_PMA_SIGDET_HF_EN_OVRD_VAL : 1;
		unsigned RX_PMA_SIGDET_HF_EN_OVRD_EN : 1;
		unsigned RESERVED_15_6 : 10;
	} b;
} CR_RAWAONLANE1_DIG_RX_OVRD_OUT_3;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_PMA_SIGDET_LF_THRESHOLD : 3;
		unsigned RX_PMA_SIGDET_HF_THRESHOLD : 3;
		unsigned RX_PMA_SIGDET_CAL_EN : 1;
		unsigned RESERVED_15_7 : 9;
	} b;
} CR_RAWAONLANE1_DIG_RX_SIGDET_CAL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_PMA_SIGDET_HF_CAL_TUNE : 6;
		unsigned RESERVED_15_6 : 10;
	} b;
} CR_RAWAONLANE1_DIG_RX_SIGDET_HF_CODE;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_PMA_SIGDET_LF_CAL_TUNE : 6;
		unsigned RESERVED_15_6 : 10;
	} b;
} CR_RAWAONLANE1_DIG_RX_SIGDET_LF_CODE;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned PULL_UP : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWAONLANE1_DIG_RX_VREFGEN_EN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DATA : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_RAWAONLANE1_DIG_CAL_IOFF_CODE;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DATA : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_RAWAONLANE1_DIG_CAL_ICONST_CODE;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DATA : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_RAWAONLANE1_DIG_CAL_VREFGEN_CODE;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_DCC_CAL_IDF_CODE : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_RAWAONLANE1_DIG_RX_DCC_CAL_IDF_CODE_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_DCC_CAL_ICM_CODE : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_RAWAONLANE1_DIG_RX_DCC_CAL_ICM_CODE_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_DCC_CAL_QDF_CODE : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_RAWAONLANE1_DIG_RX_DCC_CAL_QDF_CODE_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_DCC_CAL_QCM_CODE : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_RAWAONLANE1_DIG_RX_DCC_CAL_QCM_CODE_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_DCC_CAL_IDF_CODE : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_RAWAONLANE1_DIG_RX_DCC_CAL_IDF_CODE_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_DCC_CAL_ICM_CODE : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_RAWAONLANE1_DIG_RX_DCC_CAL_ICM_CODE_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_DCC_CAL_QDF_CODE : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_RAWAONLANE1_DIG_RX_DCC_CAL_QDF_CODE_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_DCC_CAL_QCM_CODE : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_RAWAONLANE1_DIG_RX_DCC_CAL_QCM_CODE_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned ADDR : 16;
	} b;
} CR_RAWAONLANE1_DIG_TX_DCC_BANK_ADDR;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DATA : 16;
	} b;
} CR_RAWAONLANE1_DIG_TX_DCC_BANK_DATA;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned EN : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWAONLANE1_DIG_TX_DCC_CONT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLL_STATE_WAIT : 1;
		unsigned MPLL_STATE_DLY_EN : 1;
		unsigned RESERVED_15_2 : 14;
	} b;
} CR_RAWAONLANE1_DIG_MPLL_BG_CTL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_SIGDET_HF_OUT_OVRD_VAL : 1;
		unsigned RX_SIGDET_HF_OUT_OVRD_EN : 1;
		unsigned RX_SIGDET_LF_OUT_OVRD_VAL : 1;
		unsigned RX_SIGDET_LF_OUT_OVRD_EN : 1;
		unsigned RESERVED_15_4 : 12;
	} b;
} CR_RAWAONLANE1_DIG_SIGDET_OUT_OVRD;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_SIGDET_HF_OUT_OVRD_VAL : 1;
		unsigned RX_SIGDET_LF_OUT_OVRD_VAL : 1;
		unsigned RESERVED_15_2 : 14;
	} b;
} CR_RAWAONLANE1_DIG_SIGDET_OUT_IN;
