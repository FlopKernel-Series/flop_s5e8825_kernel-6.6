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
		unsigned DATA : 16;
	} b;
} CR_SUP_DIG_IDCODE_LO;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DATA : 16;
	} b;
} CR_SUP_DIG_IDCODE_HI;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned REF_CLK_EN : 1;
		unsigned REF_CLK_EN_OVRD_EN : 1;
		unsigned REF_USE_PAD : 1;
		unsigned REF_USE_PAD_OVRD_EN : 1;
		unsigned REF_CLK_RANGE : 5;
		unsigned REF_CLK_RANGE_OVRD_EN : 1;
		unsigned BG_EN : 1;
		unsigned BG_EN_OVRD_EN : 1;
		unsigned HDMIMODE_EN : 1;
		unsigned HDMIMODE_ENABLE_OVRD_EN : 1;
		unsigned RESERVED_15_14 : 2;
	} b;
} CR_SUP_DIG_REFCLK_OVRD_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLA_DIV_CLK_EN : 1;
		unsigned MPLLA_DIV_MULTIPLIER : 8;
		unsigned MPLLA_DIV_OVRD_EN : 1;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_SUP_DIG_MPLLA_DIV_CLK_OVRD_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLA_HDMI_PIXEL_CLK_DIV : 2;
		unsigned MPLLA_HDMI_DIV : 3;
		unsigned MPLLA_HDMI_OVRD_EN : 1;
		unsigned RESERVED_15_6 : 10;
	} b;
} CR_SUP_DIG_MPLLA_HDMI_CLK_OVRD_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLB_DIV_CLK_EN : 1;
		unsigned MPLLB_DIV_MULTIPLIER : 8;
		unsigned MPLLB_DIV_OVRD_EN : 1;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_SUP_DIG_MPLLB_DIV_CLK_OVRD_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLB_HDMI_PIXEL_CLK_DIV : 2;
		unsigned MPLLB_HDMI_DIV : 3;
		unsigned MPLLB_HDMI_OVRD_EN : 1;
		unsigned RESERVED_15_6 : 10;
	} b;
} CR_SUP_DIG_MPLLB_HDMI_CLK_OVRD_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLA_EN : 1;
		unsigned MPLLA_DIV5_CLK_EN : 1;
		unsigned MPLLA_TX_CLK_DIV : 3;
		unsigned OVRD_EN : 1;
		unsigned MPLLA_V2I : 2;
		unsigned MPLLA_STANDBY : 1;
		unsigned MPLLA_FREQ_VCO : 2;
		unsigned MPLLA_CAL_FORCE : 1;
		unsigned MPLL_FRACN_EN : 1;
		unsigned RESERVED_15_13 : 3;
	} b;
} CR_SUP_DIG_MPLLA_OVRD_IN_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLA_MULTIPLIER : 12;
		unsigned RESERVED_15_12 : 4;
	} b;
} CR_SUP_DIG_MPLLA_OVRD_IN_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLA_SSC_EN : 1;
		unsigned MPLLA_SSC_OVRD_EN : 1;
		unsigned MPLLA_SSC_UP_SPREAD : 1;
		unsigned MPLLA_PMIX_EN : 1;
		unsigned MPLLA_WORD_DIV2_EN : 1;
		unsigned MPLLA_FRACN_CFG_UPDATE_EN : 1;
		unsigned RESERVED_15_6 : 10;
	} b;
} CR_SUP_DIG_MPLLA_OVRD_IN_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLA_SSC_PEAK_15_0 : 16;
	} b;
} CR_SUP_DIG_MPLLA_SSC_PEAK_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLA_SSC_PEAK_19_16 : 4;
		unsigned RESERVED_15_4 : 12;
	} b;
} CR_SUP_DIG_MPLLA_SSC_PEAK_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLA_SSC_STEPSIZE_15_0 : 16;
	} b;
} CR_SUP_DIG_MPLLA_SSC_STEPSIZE_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLA_SSC_STEPSIZE_20_16 : 5;
		unsigned RESERVED_15_5 : 11;
	} b;
} CR_SUP_DIG_MPLLA_SSC_STEPSIZE_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLA_FRACN_QUOT : 16;
	} b;
} CR_SUP_DIG_MPLLA_OVRD_IN_3;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLA_FRACN_REM : 16;
	} b;
} CR_SUP_DIG_MPLLA_OVRD_IN_4;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLA_FRACN_DEN : 16;
	} b;
} CR_SUP_DIG_MPLLA_OVRD_IN_5;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLA_CP_PROP : 7;
		unsigned MPLLA_CP_INT : 7;
		unsigned RESERVED_15_14 : 2;
	} b;
} CR_SUP_DIG_MPLLA_CP_OVRD_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLB_EN : 1;
		unsigned MPLLB_DIV5_CLK_EN : 1;
		unsigned MPLLB_TX_CLK_DIV : 3;
		unsigned OVRD_EN : 1;
		unsigned MPLLB_V2I : 2;
		unsigned MPLLB_STANDBY : 1;
		unsigned MPLLB_FREQ_VCO : 2;
		unsigned MPLLB_CAL_FORCE : 1;
		unsigned MPLL_FRACN_EN : 1;
		unsigned RESERVED_15_13 : 3;
	} b;
} CR_SUP_DIG_MPLLB_OVRD_IN_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLB_MULTIPLIER : 12;
		unsigned RESERVED_15_12 : 4;
	} b;
} CR_SUP_DIG_MPLLB_OVRD_IN_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLB_SSC_EN : 1;
		unsigned MPLLB_SSC_OVRD_EN : 1;
		unsigned MPLLB_SSC_UP_SPREAD : 1;
		unsigned MPLLB_PMIX_EN : 1;
		unsigned MPLLB_WORD_DIV2_EN : 1;
		unsigned MPLLB_FRACN_CFG_UPDATE_EN : 1;
		unsigned RESERVED_15_6 : 10;
	} b;
} CR_SUP_DIG_MPLLB_OVRD_IN_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLB_SSC_PEAK_15_0 : 16;
	} b;
} CR_SUP_DIG_MPLLB_SSC_PEAK_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLB_SSC_PEAK_19_16 : 4;
		unsigned RESERVED_15_4 : 12;
	} b;
} CR_SUP_DIG_MPLLB_SSC_PEAK_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLB_SSC_STEPSIZE_15_0 : 16;
	} b;
} CR_SUP_DIG_MPLLB_SSC_STEPSIZE_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLB_SSC_STEPSIZE_20_16 : 5;
		unsigned RESERVED_15_5 : 11;
	} b;
} CR_SUP_DIG_MPLLB_SSC_STEPSIZE_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLB_FRACN_QUOT : 16;
	} b;
} CR_SUP_DIG_MPLLB_OVRD_IN_3;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLB_FRACN_REM : 16;
	} b;
} CR_SUP_DIG_MPLLB_OVRD_IN_4;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLB_FRACN_DEN : 16;
	} b;
} CR_SUP_DIG_MPLLB_OVRD_IN_5;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLB_CP_PROP : 7;
		unsigned MPLLB_CP_INT : 7;
		unsigned RESERVED_15_14 : 2;
	} b;
} CR_SUP_DIG_MPLLB_CP_OVRD_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned PRESCALER_OVRD_EN : 1;
		unsigned RTUNE_REQ : 1;
		unsigned RTUNE_OVRD_EN : 1;
		unsigned TX_CAL_CODE : 4;
		unsigned TX_CAL_CODE_EN : 1;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_SUP_DIG_SUP_OVRD_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DCO_RANGE : 2;
		unsigned DCO_FINETUNE : 6;
		unsigned REF_CLK_MPLLB_DIV : 3;
		unsigned REF_CLK_MPLLA_DIV : 3;
		unsigned REF_CLKDET_RESULT : 1;
		unsigned REF_CLKDET_EN : 1;
	} b;
} CR_SUP_DIG_PRESCALER_OVRD_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RTUNE_ACK : 1;
		unsigned RTUNE_ACK_OVRD_EN : 1;
		unsigned MPLLA_STATE : 1;
		unsigned MPLLA_STATE_OVRD_EN : 1;
		unsigned MPLLB_STATE : 1;
		unsigned MPLLB_STATE_OVRD_EN : 1;
		unsigned BG_LANE_STATE : 1;
		unsigned BG_LANE_STATE_OVRD_EN : 1;
		unsigned BG_SUP_STATE : 1;
		unsigned BG_SUP_STATE_OVRD_EN : 1;
		unsigned REF_CLK_ACK : 1;
		unsigned RESERVED_15_11 : 5;
	} b;
} CR_SUP_DIG_SUP_OVRD_OUT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_VREF_CTRL : 3;
		unsigned RX_VREF_CTRL_EN : 1;
		unsigned TX_VBOOST_LVL : 3;
		unsigned TX_VBOOST_LVL_EN : 1;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_SUP_DIG_LVL_OVRD_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DTB_SEL : 3;
		unsigned RESERVED_15_3 : 13;
	} b;
} CR_SUP_DIG_DEBUG;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLA_EN : 1;
		unsigned MPLLA_DIV5_CLK_EN : 1;
		unsigned MPLLA_TX_CLK_DIV : 3;
		unsigned MPLLA_V2I : 2;
		unsigned MPLLA_STANDBY : 1;
		unsigned MPLLA_FREQ_VCO : 2;
		unsigned MPLLA_CAL_FORCE : 1;
		unsigned MPLLA_FRACN_EN : 1;
		unsigned RESERVED_15_12 : 4;
	} b;
} CR_SUP_DIG_MPLLA_ASIC_IN_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLA_MULTIPLIER : 12;
		unsigned RESERVED_15_12 : 4;
	} b;
} CR_SUP_DIG_MPLLA_ASIC_IN_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLA_SSC_EN : 1;
		unsigned MPLLA_SSC_UP_SPREAD : 1;
		unsigned MPLLA_PMIX_EN : 1;
		unsigned MPLLA_WORD_DIV2_EN : 1;
		unsigned MPLLA_FRACN_CFG_UPDATE_EN : 1;
		unsigned RESERVED_15_5 : 11;
	} b;
} CR_SUP_DIG_MPLLA_ASIC_IN_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLA_SSC_PEAK_15_0 : 16;
	} b;
} CR_SUP_DIG_MPLLA_ASIC_IN_3;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLA_SSC_PEAK_19_16 : 4;
		unsigned RESERVED_15_4 : 12;
	} b;
} CR_SUP_DIG_MPLLA_ASIC_IN_4;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLA_SSC_STEPSIZE_15_0 : 16;
	} b;
} CR_SUP_DIG_MPLLA_ASIC_IN_5;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLA_SSC_STEPSIZE_20_16 : 4;
		unsigned RESERVED_15_4 : 12;
	} b;
} CR_SUP_DIG_MPLLA_ASIC_IN_6;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLB_EN : 1;
		unsigned MPLLB_DIV5_CLK_EN : 1;
		unsigned MPLLB_TX_CLK_DIV : 3;
		unsigned MPLLB_V2I : 2;
		unsigned MPLLB_STANDBY : 1;
		unsigned MPLLB_FREQ_VCO : 2;
		unsigned MPLLB_CAL_FORCE : 1;
		unsigned MPLLB_FRACN_EN : 1;
		unsigned RESERVED_15_12 : 4;
	} b;
} CR_SUP_DIG_MPLLB_ASIC_IN_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLB_MULTIPLIER : 12;
		unsigned RESERVED_15_12 : 4;
	} b;
} CR_SUP_DIG_MPLLB_ASIC_IN_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLB_SSC_EN : 1;
		unsigned MPLLB_SSC_UP_SPREAD : 1;
		unsigned MPLLB_PMIX_EN : 1;
		unsigned MPLLB_WORD_DIV2_EN : 1;
		unsigned MPLLB_FRACN_CFG_UPDATE_EN : 1;
		unsigned RESERVED_15_5 : 11;
	} b;
} CR_SUP_DIG_MPLLB_ASIC_IN_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLB_SSC_PEAK_15_0 : 16;
	} b;
} CR_SUP_DIG_MPLLB_ASIC_IN_3;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLB_SSC_PEAK_19_16 : 4;
		unsigned RESERVED_15_4 : 12;
	} b;
} CR_SUP_DIG_MPLLB_ASIC_IN_4;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLB_SSC_STEPSIZE_15_0 : 16;
	} b;
} CR_SUP_DIG_MPLLB_ASIC_IN_5;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLB_SSC_STEPSIZE_20_16 : 4;
		unsigned RESERVED_15_4 : 12;
	} b;
} CR_SUP_DIG_MPLLB_ASIC_IN_6;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLA_DIV_CLK_EN : 1;
		unsigned MPLLA_DIV_MULTIPLIER : 8;
		unsigned RESERVED_15_9 : 7;
	} b;
} CR_SUP_DIG_MPLLA_DIV_CLK_ASIC_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLA_HDMI_PIXEL_CLK_DIV : 2;
		unsigned MPLLA_HDMI_DIV : 3;
		unsigned RESERVED_15_5 : 11;
	} b;
} CR_SUP_DIG_MPLLA_HDMI_CLK_ASIC_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLB_DIV_CLK_EN : 1;
		unsigned MPLLB_DIV_MULTIPLIER : 8;
		unsigned RESERVED_15_9 : 7;
	} b;
} CR_SUP_DIG_MPLLB_DIV_CLK_ASIC_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLB_HDMI_PIXEL_CLK_DIV : 2;
		unsigned MPLLB_HDMI_DIV : 3;
		unsigned RESERVED_15_5 : 11;
	} b;
} CR_SUP_DIG_MPLLB_HDMI_CLK_ASIC_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned PHY_RESET : 1;
		unsigned REF_CLK_EN : 1;
		unsigned REF_USE_PAD : 1;
		unsigned TEST_BURNIN : 1;
		unsigned TEST_POWERDOWN : 1;
		unsigned RTUNE_REQ : 1;
		unsigned RTUNE_ACK : 1;
		unsigned MPLLA_STATE : 1;
		unsigned MPLLB_STATE : 1;
		unsigned TEST_TX_REF_CLK_EN : 1;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_SUP_DIG_ASIC_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_VREF_CTRL : 3;
		unsigned TX_VBOOST_LVL : 3;
		unsigned RESERVED_15_6 : 10;
	} b;
} CR_SUP_DIG_LVL_ASIC_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned BG_EN : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_SUP_DIG_BANDGAP_ASIC_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLA_CP_PROP : 7;
		unsigned MPLLA_CP_INT : 7;
		unsigned RESERVED_15_14 : 2;
	} b;
} CR_SUP_DIG_MPLLA_CP_ASIC_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLB_CP_PROP : 7;
		unsigned MPLLB_CP_INT : 7;
		unsigned RESERVED_15_14 : 2;
	} b;
} CR_SUP_DIG_MPLLB_CP_ASIC_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned LANE_MASTER0 : 1;
		unsigned LANE_MASTER1 : 1;
		unsigned LANE_MASTER2 : 1;
		unsigned LANE_MASTER3 : 1;
		unsigned LANE_MASTER4 : 1;
		unsigned LANE_MASTER5 : 1;
		unsigned LANE_MASTER6 : 1;
		unsigned LANE_MASTER7 : 1;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_SUP_DIG_MASTER_LANE;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned PSCALER_ATB_SELECT : 1;
		unsigned PSCALER_MEAS_VREG : 1;
		unsigned PSCALER_OVRD_FAST_START : 1;
		unsigned PSCALER_FAST_START_REG : 1;
		unsigned PSCALER_VREG_BOOST : 2;
		unsigned PSCALER_HYST_REF : 2;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_SUP_ANA_PRESCALER_CTRL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RT_ATB : 1;
		unsigned RT_SEL_ATBF : 1;
		unsigned RT_SEL_ATBP : 1;
		unsigned RT_VP4O8_EN : 1;
		unsigned RT_DAC_CHOP : 1;
		unsigned RT_DAC_MODE : 1;
		unsigned RT_EN_FRCON : 1;
		unsigned PSCALER_VREG_FB_DIV_CTRL : 1;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_SUP_ANA_RTUNE_CTRL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned SUP_SEL_VBG_VREF : 2;
		unsigned SUP_SEL_RX_VCO_VREF : 3;
		unsigned SUP_SEL_VPLL_REF : 2;
		unsigned RT_VREF_SEL : 1;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_SUP_ANA_BG1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned SUP_BYPASS_BG : 1;
		unsigned SUP_CHOP_EN : 1;
		unsigned SUP_TEMP_MEAS : 1;
		unsigned VPHUD_SELREF : 1;
		unsigned ATB_EXT_MEAS_EN : 1;
		unsigned REXT_ATB_EN : 1;
		unsigned SUP_DISABLE_SUFFLER : 1;
		unsigned SUP_DISABLE_CHOP : 1;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_SUP_ANA_BG2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned SUP_ATB_SW : 7;
		unsigned SUP_TIE : 1;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_SUP_ANA_SWITCH_PWR_MEAS;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned NC1_0 : 2;
		unsigned TEST_VREG_DIV : 2;
		unsigned VBG_EN : 1;
		unsigned COUNT_SEL_LOCK : 1;
		unsigned PHASE_SEL_LOCK : 2;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_SUP_ANA_MPLLA_MISC1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned OVRD_PR_BYPASS : 1;
		unsigned PR_BYPASS : 1;
		unsigned OVRD_GEARSHIFT : 1;
		unsigned GEARSHIFT_REG : 1;
		unsigned TEST_LOCK_GEAR : 1;
		unsigned EN_CAL_SPO : 1;
		unsigned TEST_BOOST : 2;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_SUP_ANA_MPLLA_MISC2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned OVRD_ENABLE : 1;
		unsigned ENABLE_REG : 1;
		unsigned OVRD_CAL : 1;
		unsigned CAL_REG : 1;
		unsigned OVRD_FB_CLK_EN : 1;
		unsigned FB_CLK_EN_REG : 1;
		unsigned OVRD_RESET : 1;
		unsigned RESET_REG : 1;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_SUP_ANA_MPLLA_OVRD;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MEAS_IV_WRAP : 7;
		unsigned ATB_SELECT : 1;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_SUP_ANA_MPLLA_ATB1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MEAS_IV_PLL : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_SUP_ANA_MPLLA_ATB2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MEAS_IV_BIAS : 3;
		unsigned NC7_3 : 5;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_SUP_ANA_MPLLA_ATB3;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned CTR_CP_PLL : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_SUP_ANA_MPLLA_CTR1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned CTR_REGS_PLL : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_SUP_ANA_MPLLA_CTR2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned CTR_REGS_CP_PLL : 2;
		unsigned CTR_SPO_PLL : 5;
		unsigned NC7 : 1;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_SUP_ANA_MPLLA_CTR3;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned CTR_CP_8X : 1;
		unsigned CTR_FIL_REG : 1;
		unsigned CTR_CP_PROP_REF : 1;
		unsigned CTR_DOUBLER_GAIN : 1;
		unsigned NC7_4 : 4;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_SUP_ANA_MPLLA_CTR4;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned NC1_0 : 2;
		unsigned TEST_VREG_DIV : 2;
		unsigned VBG_EN : 1;
		unsigned COUNT_SEL_LOCK : 1;
		unsigned PHASE_SEL_LOCK : 2;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_SUP_ANA_MPLLB_MISC1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned OVRD_PR_BYPASS : 1;
		unsigned PR_BYPASS : 1;
		unsigned OVRD_GEARSHIFT : 1;
		unsigned GEARSHIFT_REG : 1;
		unsigned TEST_LOCK_GEAR : 1;
		unsigned EN_CAL_SPO : 1;
		unsigned TEST_BOOST : 2;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_SUP_ANA_MPLLB_MISC2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned OVRD_ENABLE : 1;
		unsigned ENABLE_REG : 1;
		unsigned OVRD_CAL : 1;
		unsigned CAL_REG : 1;
		unsigned OVRD_FB_CLK_EN : 1;
		unsigned FB_CLK_EN_REG : 1;
		unsigned OVRD_RESET : 1;
		unsigned RESET_REG : 1;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_SUP_ANA_MPLLB_OVRD;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MEAS_IV_WRAP : 7;
		unsigned ATB_SELECT : 1;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_SUP_ANA_MPLLB_ATB1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MEAS_IV_PLL : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_SUP_ANA_MPLLB_ATB2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MEAS_IV_BIAS : 3;
		unsigned NC7_3 : 5;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_SUP_ANA_MPLLB_ATB3;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned CTR_CP_PLL : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_SUP_ANA_MPLLB_CTR1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned CTR_REGS_PLL : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_SUP_ANA_MPLLB_CTR2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned CTR_REGS_CP_PLL : 2;
		unsigned CTR_SPO_PLL : 5;
		unsigned NC7 : 1;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_SUP_ANA_MPLLB_CTR3;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned CTR_CP_8X : 1;
		unsigned CTR_FIL_REG : 1;
		unsigned CTR_CP_PROP_REF : 1;
		unsigned CTR_DOUBLER_GAIN : 1;
		unsigned NC7_4 : 4;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_SUP_ANA_MPLLB_CTR4;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned OVRD_SEL : 1;
		unsigned MPLL_FBDIGCLK_EN : 1;
		unsigned MPLL_PCLK_EN : 1;
		unsigned FAST_MPLL_PWRUP : 1;
		unsigned FAST_MPLL_LOCK : 1;
		unsigned DTB_SEL : 5;
		unsigned DIV10_EN : 1;
		unsigned RESERVED : 5;
	} b;
} CR_SUP_DIG_MPLLA_MPLL_PWR_CTL_MPLL_OVRD;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned FSM_STATE : 4;
		unsigned MPLL_R_LANES : 1;
		unsigned MPLL_L_LANES : 1;
		unsigned MPLL_PCLK_EN : 1;
		unsigned MPLL_OUTPUT_EN : 1;
		unsigned MPLL_FBCLK_EN : 1;
		unsigned MPLL_CAL : 1;
		unsigned MPLL_RST : 1;
		unsigned MPLL_ANA_EN : 1;
		unsigned MPLL_LOCK : 1;
		unsigned RESERVED_15_13 : 3;
	} b;
} CR_SUP_DIG_MPLLA_MPLL_PWR_CTL_STAT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned CP_INT_GS : 7;
		unsigned CP_PROP_GS : 7;
		unsigned RESERVED_15_14 : 2;
	} b;
} CR_SUP_DIG_MPLLA_MPLL_PWR_CTL_MPLL_CP;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MAX_RANGE : 5;
		unsigned DAC_IN : 5;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_SUP_DIG_MPLLA_MPLL_PWR_CTL_MPLL_DAC_MAXRANGE;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned LOCK_TIME : 8;
		unsigned STABLE_TIME : 6;
		unsigned RESERVED_15_14 : 2;
	} b;
} CR_SUP_DIG_MPLLA_MPLL_PWR_CTL_MPLL_TIMERS_LOCK;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned GEARSHIFT_TIME : 8;
		unsigned PRESET_TIME : 8;
	} b;
} CR_SUP_DIG_MPLLA_MPLL_PWR_CTL_MPLL_TIMERS;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned PWRDN_WAIT_TIME : 6;
		unsigned PCLK_EN_TIME : 6;
		unsigned RESERVED_15_12 : 4;
	} b;
} CR_SUP_DIG_MPLLA_MPLL_PWR_CTL_MPLL_TIMERS_PCLK_STABLE;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned PCLK_DIS_TIME : 6;
		unsigned PWRDN_TIME : 6;
		unsigned RESERVED_15_12 : 4;
	} b;
} CR_SUP_DIG_MPLLA_MPLL_PWR_CTL_MPLL_TIMERS_PCLK_STABLE_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLL_CAL : 1;
		unsigned MPLL_CAL_OVRD_EN : 1;
		unsigned MPLL_SYNC : 1;
		unsigned RESERVED_15_3 : 13;
	} b;
} CR_SUP_DIG_MPLLA_MPLL_PWR_CTL_MPLL_SYN_CAL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLL_ANA_DAC_OUT : 5;
		unsigned RESERVED_15_5 : 11;
	} b;
} CR_SUP_DIG_MPLLA_MPLL_PWR_CTL_MPLL_ANA_DAC_OUT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned SPREAD_TYPE : 2;
		unsigned OVR_EN : 1;
		unsigned RESERVED_15_3 : 13;
	} b;
} CR_SUP_DIG_MPLLA_SSC_GEN_SPREAD_TYPE;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned OVRD_SEL : 1;
		unsigned MPLL_FBDIGCLK_EN : 1;
		unsigned MPLL_PCLK_EN : 1;
		unsigned FAST_MPLL_PWRUP : 1;
		unsigned FAST_MPLL_LOCK : 1;
		unsigned DTB_SEL : 5;
		unsigned DIV10_EN : 1;
		unsigned RESERVED : 5;
	} b;
} CR_SUP_DIG_MPLLB_MPLL_PWR_CTL_MPLL_OVRD;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned FSM_STATE : 4;
		unsigned MPLL_R_LANES : 1;
		unsigned MPLL_L_LANES : 1;
		unsigned MPLL_PCLK_EN : 1;
		unsigned MPLL_OUTPUT_EN : 1;
		unsigned MPLL_FBCLK_EN : 1;
		unsigned MPLL_CAL : 1;
		unsigned MPLL_RST : 1;
		unsigned MPLL_ANA_EN : 1;
		unsigned MPLL_LOCK : 1;
		unsigned RESERVED_15_13 : 3;
	} b;
} CR_SUP_DIG_MPLLB_MPLL_PWR_CTL_STAT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned CP_INT_GS : 7;
		unsigned CP_PROP_GS : 7;
		unsigned RESERVED_15_14 : 2;
	} b;
} CR_SUP_DIG_MPLLB_MPLL_PWR_CTL_MPLL_CP;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MAX_RANGE : 5;
		unsigned DAC_IN : 5;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_SUP_DIG_MPLLB_MPLL_PWR_CTL_MPLL_DAC_MAXRANGE;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned LOCK_TIME : 8;
		unsigned STABLE_TIME : 6;
		unsigned RESERVED_15_14 : 2;
	} b;
} CR_SUP_DIG_MPLLB_MPLL_PWR_CTL_MPLL_TIMERS_LOCK;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned GEARSHIFT_TIME : 8;
		unsigned PRESET_TIME : 8;
	} b;
} CR_SUP_DIG_MPLLB_MPLL_PWR_CTL_MPLL_TIMERS;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned PWRDN_WAIT_TIME : 6;
		unsigned PCLK_EN_TIME : 6;
		unsigned RESERVED_15_12 : 4;
	} b;
} CR_SUP_DIG_MPLLB_MPLL_PWR_CTL_MPLL_TIMERS_PCLK_STABLE;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned PCLK_DIS_TIME : 6;
		unsigned PWRDN_TIME : 6;
		unsigned RESERVED_15_12 : 4;
	} b;
} CR_SUP_DIG_MPLLB_MPLL_PWR_CTL_MPLL_TIMERS_PCLK_STABLE_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLL_CAL : 1;
		unsigned MPLL_CAL_OVRD_EN : 1;
		unsigned MPLL_SYNC : 1;
		unsigned RESERVED_15_3 : 13;
	} b;
} CR_SUP_DIG_MPLLB_MPLL_PWR_CTL_MPLL_SYN_CAL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLL_ANA_DAC_OUT : 5;
		unsigned RESERVED_15_5 : 11;
	} b;
} CR_SUP_DIG_MPLLB_MPLL_PWR_CTL_MPLL_ANA_DAC_OUT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned SPREAD_TYPE : 2;
		unsigned OVR_EN : 1;
		unsigned RESERVED_15_3 : 13;
	} b;
} CR_SUP_DIG_MPLLB_SSC_GEN_SPREAD_TYPE;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned BG_SUP_EN_TIME : 9;
		unsigned FAST_BG_WAIT : 1;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_SUP_DIG_CLK_RST_BG_PWRUP_TIME_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned BG_LANE_EN_TIME : 9;
		unsigned RESERVED_15_9 : 7;
	} b;
} CR_SUP_DIG_CLK_RST_BG_PWRUP_TIME_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned BG_KICK_START_EN_TIME : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_SUP_DIG_CLK_RST_BG_PWRUP_TIME_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned REF_VREG_FAST_START_TIME : 5;
		unsigned FAST_REF_WAIT : 1;
		unsigned RESERVED_15_6 : 10;
	} b;
} CR_SUP_DIG_CLK_RST_REF_PWRUP_TIME_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned SUP_ANA_VPHUD_SELVPH_I : 1;
		unsigned SUP_ANA_VPHUD_EN_I : 1;
		unsigned RESERVED_15_2 : 14;
	} b;
} CR_SUP_DIG_CLK_RST_REF_VPHUD;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned FLIP_COMP : 1;
		unsigned MAN_TUNE : 1;
		unsigned SET_VAL : 1;
		unsigned TYPE : 2;
		unsigned VALUE : 10;
		unsigned TXUP_GO : 1;
	} b;
} CR_SUP_DIG_RTUNE_DEBUG;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_CAL_EN : 1;
		unsigned FAST_RTUNE : 1;
		unsigned TX_CAL_EN : 1;
		unsigned SUP_ANA_TERM_CTRL : 3;
		unsigned RESERVED_15_6 : 10;
	} b;
} CR_SUP_DIG_RTUNE_CONFIG;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned STAT : 10;
		unsigned DTB_RTUNE : 2;
		unsigned RESERVED_15_12 : 4;
	} b;
} CR_SUP_DIG_RTUNE_STAT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_SET_VAL : 6;
		unsigned RESERVED_15_6 : 10;
	} b;
} CR_SUP_DIG_RTUNE_RX_SET_VAL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned TXDN_SET_VAL : 10;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_SUP_DIG_RTUNE_TXDN_SET_VAL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned TXUP_SET_VAL : 10;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_SUP_DIG_RTUNE_TXUP_SET_VAL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_STAT : 6;
		unsigned RESERVED_15_6 : 10;
	} b;
} CR_SUP_DIG_RTUNE_RX_STAT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned TXDN_STAT : 10;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_SUP_DIG_RTUNE_TXDN_STAT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned TXUP_STAT : 10;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_SUP_DIG_RTUNE_TXUP_STAT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RT_RESULT_TIME : 4;
		unsigned RT_EVAL_TIME : 4;
		unsigned RT_RST_TIME : 4;
		unsigned RT_ACK_TIME : 4;
	} b;
} CR_SUP_DIG_RTUNE_CONFIG_CNT0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RT_TXDN_SETTLE_TIME : 4;
		unsigned RT_PWRUP_TIME : 5;
		unsigned RESERVED_15_9 : 7;
	} b;
} CR_SUP_DIG_RTUNE_CONFIG_CNT1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned VALUE : 4;
		unsigned RESERVED_15_4 : 12;
	} b;
} CR_SUP_DIG_RTUNE_TX_CAL_CODE;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLA_WORD_CLK_EN : 1;
		unsigned MPLLA_HDMI_CLK_EN : 1;
		unsigned MPLLA_DIV_CLK_EN : 1;
		unsigned MPLLA_OUTPUT_EN : 1;
		unsigned MPLLA_CLK_EN_OVRD_EN : 1;
		unsigned MPLLA_OUTPUT_L_EN : 1;
		unsigned MPLLA_OUTPUT_R_EN : 1;
		unsigned MPLLA_ANA_EN : 1;
		unsigned MPLLA_RST : 1;
		unsigned MPLLA_CAL : 1;
		unsigned MPLLA_DIV5_CLK_EN : 1;
		unsigned MPLLA_DIV10_CLK_EN : 1;
		unsigned MPLLA_FBCLK_EN : 1;
		unsigned MPLLA_GEARSHIFT_EN : 1;
		unsigned MPLLA_STANDBY : 1;
		unsigned OVRD_SEL : 1;
	} b;
} CR_SUP_DIG_ANA_MPLLA_OVRD_OUT_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLA_ANA_INT : 10;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_SUP_DIG_ANA_MPLLA_OVRD_OUT_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLA_CP_PROP : 7;
		unsigned MPLLA_CP_INT : 7;
		unsigned RESERVED_15_14 : 2;
	} b;
} CR_SUP_DIG_ANA_MPLLA_OVRD_OUT_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLB_WORD_CLK_EN : 1;
		unsigned MPLLB_HDMI_CLK_EN : 1;
		unsigned MPLLB_DIV_CLK_EN : 1;
		unsigned MPLLB_OUTPUT_EN : 1;
		unsigned MPLLB_CLK_EN_OVRD_EN : 1;
		unsigned MPLLB_OUTPUT_L_EN : 1;
		unsigned MPLLB_OUTPUT_R_EN : 1;
		unsigned MPLLB_ANA_EN : 1;
		unsigned MPLLB_RST : 1;
		unsigned MPLLB_CAL : 1;
		unsigned MPLLB_DIV5_CLK_EN : 1;
		unsigned MPLLB_DIV10_CLK_EN : 1;
		unsigned MPLLB_FBCLK_EN : 1;
		unsigned MPLLB_GEARSHIFT_EN : 1;
		unsigned MPLLB_STANDBY : 1;
		unsigned OVRD_SEL : 1;
	} b;
} CR_SUP_DIG_ANA_MPLLB_OVRD_OUT_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLB_ANA_INT : 10;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_SUP_DIG_ANA_MPLLB_OVRD_OUT_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLB_CP_PROP : 7;
		unsigned MPLLB_CP_INT : 7;
		unsigned RESERVED_15_14 : 2;
	} b;
} CR_SUP_DIG_ANA_MPLLB_OVRD_OUT_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RTUNE_COMP_RST : 1;
		unsigned RTUNE_MODE : 2;
		unsigned RTUNE_EN : 1;
		unsigned RTUNE_VALUE : 10;
		unsigned RTUNE_OVRD_EN : 1;
		unsigned RESERVED_15_15 : 1;
	} b;
} CR_SUP_DIG_ANA_RTUNE_OVRD_OUT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RT_ANA_COMP_RESULT : 1;
		unsigned REF_ANA_CLKDET_RESULT : 1;
		unsigned RESERVED_15_2 : 14;
	} b;
} CR_SUP_DIG_ANA_STAT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned BG_EN : 1;
		unsigned BG_FAST_START : 1;
		unsigned BG_KICK_START : 1;
		unsigned BG_OVRD_EN : 1;
		unsigned ANA_ASYNC_RST : 1;
		unsigned ANA_ASYNC_RST_OVRD_EN : 1;
		unsigned REF_VREG_FAST_START : 1;
		unsigned REF_VREG_FAST_START_OVRD_EN : 1;
		unsigned REF_VREG_REF_SEL : 2;
		unsigned REF_VREG_REF_SEL_OVRD_EN : 1;
		unsigned RESERVED_15_11 : 5;
	} b;
} CR_SUP_DIG_ANA_BG_OVRD_OUT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLA_PMIX_SEL : 6;
		unsigned MPLLA_PMIX_EN : 1;
		unsigned MPLLA_PMIX_SEL_OVRD_EN : 1;
		unsigned MPLLA_PMIX_EN_OVRD_EN : 1;
		unsigned RESERVED_15_9 : 7;
	} b;
} CR_SUP_DIG_ANA_MPLLA_PMIX_OVRD_OUT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLB_PMIX_SEL : 6;
		unsigned MPLLB_PMIX_EN : 1;
		unsigned MPLLB_PMIX_SEL_OVRD_EN : 1;
		unsigned MPLLB_PMIX_EN_OVRD_EN : 1;
		unsigned RESERVED_15_9 : 7;
	} b;
} CR_SUP_DIG_ANA_MPLLB_PMIX_OVRD_OUT;
