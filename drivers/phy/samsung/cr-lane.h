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
		unsigned LANE_TX2RX_SER_LB : 1;
		unsigned LANE_RX2TX_PAR_LB : 1;
		unsigned EN : 1;
		unsigned RESERVED_15_3 : 13;
	} b;
} CR_LANE1_DIG_ASIC_LANE_OVRD_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned REQ : 1;
		unsigned REQ_OVRD_EN : 1;
		unsigned PSTATE : 2;
		unsigned PSTATE_OVRD_EN : 1;
		unsigned RATE : 3;
		unsigned RATE_OVRD_EN : 1;
		unsigned WIDTH : 2;
		unsigned WIDTH_OVRD_EN : 1;
		unsigned MPLLB_SEL : 1;
		unsigned MPLLB_SEL_OVRD_EN : 1;
		unsigned DATA_EN : 1;
		unsigned DATA_EN_OVRD_EN : 1;
	} b;
} CR_LANE1_DIG_ASIC_TX_OVRD_IN_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned REQ : 1;
		unsigned REQ_OVRD_EN : 1;
		unsigned PSTATE : 2;
		unsigned PSTATE_OVRD_EN : 1;
		unsigned RATE : 3;
		unsigned RATE_OVRD_EN : 1;
		unsigned WIDTH : 2;
		unsigned WIDTH_OVRD_EN : 1;
		unsigned MPLLB_SEL : 1;
		unsigned MPLLB_SEL_OVRD_EN : 1;
		unsigned DATA_EN : 1;
		unsigned DATA_EN_OVRD_EN : 1;
	} b;
} CR_LANE0_DIG_ASIC_TX_OVRD_IN_0;

typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned NYQUIST_DATA : 1;
		unsigned DISABLE : 1;
		unsigned BEACON_EN : 1;
		unsigned EN : 1;
		unsigned TX_MAIN_CURSOR : 6;
		unsigned MAIN_OVRD_EN : 1;
		unsigned ASYNC_DRV_EN : 1;
		unsigned ASYNC_DRV_OVRD_EN : 1;
		unsigned RESERVED_15_13 : 3;
	} b;
} CR_LANE1_DIG_ASIC_TX_OVRD_IN_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned TX_PRE_CURSOR : 6;
		unsigned PRE_OVRD_EN : 1;
		unsigned TX_POST_CURSOR : 6;
		unsigned POST_OVRD_EN : 1;
		unsigned HDMIMODE_EN : 1;
		unsigned HDMIMODE_ENABLE_OVRD_EN : 1;
	} b;
} CR_LANE1_DIG_ASIC_TX_OVRD_IN_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned CLK_RDY : 1;
		unsigned CLK_RDY_OVRD_EN : 1;
		unsigned DETECT_RX_REQ : 1;
		unsigned DETECT_RX_REQ_OVRD_EN : 1;
		unsigned INVERT : 1;
		unsigned INVERT_OVRD_EN : 1;
		unsigned LPD_OVRD_EN : 1;
		unsigned LPD : 1;
		unsigned TX_DC_COUP_EN : 1;
		unsigned TX_DC_COUP_EN_OVRD_EN : 1;
		unsigned PMA_EXTENDED_FIFO_EN : 1;
		unsigned PMA_EXTENDED_FIFO_EN_OVRD_EN : 1;
		unsigned RESERVED_15_12 : 4;
	} b;
} CR_LANE1_DIG_ASIC_TX_OVRD_IN_3;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RESET : 1;
		unsigned RESET_OVRD_EN : 1;
		unsigned RESERVED_15_2 : 14;
	} b;
} CR_LANE1_DIG_ASIC_TX_OVRD_IN_4;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned TX_ACK : 1;
		unsigned EN_TX_ACK : 1;
		unsigned DETRX_RESULT : 1;
		unsigned EN_DETRX_RESULT : 1;
		unsigned RESERVED_15_4 : 12;
	} b;
} CR_LANE1_DIG_ASIC_TX_OVRD_OUT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned REQ : 1;
		unsigned REQ_OVRD_EN : 1;
		unsigned DATA_EN : 1;
		unsigned DATA_EN_OVRD_EN : 1;
		unsigned PSTATE : 2;
		unsigned PSTATE_OVRD_EN : 1;
		unsigned RATE : 2;
		unsigned RATE_OVRD_EN : 1;
		unsigned WIDTH : 2;
		unsigned WIDTH_OVRD_EN : 1;
		unsigned RESERVED_15_13 : 3;
	} b;
} CR_LANE1_DIG_ASIC_RX_OVRD_IN_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_REF_LD_VAL_5_0 : 6;
		unsigned RX_CDR_VCO_LOWFREQ : 1;
		unsigned EN : 1;
		unsigned RX_REF_LD_VAL_6 : 1;
		unsigned RESERVED_15_9 : 7;
	} b;
} CR_LANE1_DIG_ASIC_RX_OVRD_IN_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_VCO_LD_VAL : 13;
		unsigned EN : 1;
		unsigned RESERVED_15_14 : 2;
	} b;
} CR_LANE1_DIG_ASIC_RX_OVRD_IN_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned CDR_TRACK_EN : 1;
		unsigned CDR_TRACK_EN_OVRD_EN : 1;
		unsigned CDR_SSC_EN : 1;
		unsigned CDR_SSC_EN_OVRD_EN : 1;
		unsigned ALIGN_EN : 1;
		unsigned ALIGN_EN_OVRD_EN : 1;
		unsigned CLK_SHIFT : 1;
		unsigned CLK_SHIFT_OVRD_EN : 1;
		unsigned DISABLE : 1;
		unsigned DISABLE_OVRD_EN : 1;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_LANE1_DIG_ASIC_RX_OVRD_IN_3;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned LPD : 1;
		unsigned LPD_OVRD_EN : 1;
		unsigned INVERT : 1;
		unsigned INVERT_OVRD_EN : 1;
		unsigned ADAPT_AFE_EN : 1;
		unsigned ADAPT_DFE_EN : 1;
		unsigned ADPT_OVRD_EN : 1;
		unsigned TERM_EN : 1;
		unsigned TERM_ACDC : 1;
		unsigned TERM_OVRD_EN : 1;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_LANE1_DIG_ASIC_RX_OVRD_IN_4;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RESET : 1;
		unsigned RESET_OVRD_EN : 1;
		unsigned RESERVED_15_2 : 14;
	} b;
} CR_LANE1_DIG_ASIC_RX_OVRD_IN_5;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned EQ_ATT_LVL : 3;
		unsigned EQ_AFE_GAIN : 4;
		unsigned RESERVED : 4;
		unsigned EQ_CTLE_BOOST : 5;
	} b;
} CR_LANE1_DIG_ASIC_RX_OVRD_EQ_IN_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned EQ_DFE_TAP2 : 7;
		unsigned EQ_DFE_TAP1 : 8;
		unsigned EQ_OVRD_EN : 1;
	} b;
} CR_LANE1_DIG_ASIC_RX_OVRD_EQ_IN_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned ACK : 1;
		unsigned ACK_OVRD_EN : 1;
		unsigned ADAPT_STS : 2;
		unsigned ADAPT_STS_OVRD_EN : 1;
		unsigned RX_ASYNC_DATA : 1;
		unsigned RX_ASYNC_DATA_OVRD_EN : 1;
		unsigned RX_SQ_WEAKKEEP_OUT : 1;
		unsigned RX_SQ_WEAKKEEP_OUT_OVRD_EN : 1;
		unsigned RESERVED_15_9 : 7;
	} b;
} CR_LANE1_DIG_ASIC_RX_OVRD_OUT_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned LANE_TX2RX_SER_LB : 1;
		unsigned LANE_RX2TX_PAR_LB : 1;
		unsigned RESERVED_15_2 : 14;
	} b;
} CR_LANE1_DIG_ASIC_LANE_ASIC_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned CLK_RDY : 1;
		unsigned RESET : 1;
		unsigned INVERT : 1;
		unsigned DATA_EN : 1;
		unsigned REQ : 1;
		unsigned LPD : 1;
		unsigned PSTATE : 2;
		unsigned RATE : 3;
		unsigned WIDTH : 2;
		unsigned MPLLB_SEL : 1;
		unsigned DETECT_RX_REQ : 1;
		unsigned DISABLE : 1;
	} b;
} CR_LANE1_DIG_ASIC_TX_ASIC_IN_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned BEACON_EN : 1;
		unsigned TX_MAIN_CURSOR : 6;
		unsigned TX_ASYNC_EN : 1;
		unsigned TX_ASYNC_DATA : 1;
		unsigned TX_ASYNC_DRV_EN : 1;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_LANE1_DIG_ASIC_TX_ASIC_IN_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned TX_PRE_CURSOR : 6;
		unsigned TX_POST_CURSOR : 6;
		unsigned RESERVED_15_12 : 4;
	} b;
} CR_LANE1_DIG_ASIC_TX_ASIC_IN_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned TX_ACK : 1;
		unsigned DETRX_RESULT : 1;
		unsigned RESERVED_15_2 : 14;
	} b;
} CR_LANE1_DIG_ASIC_TX_ASIC_OUT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RESET : 1;
		unsigned INVERT : 1;
		unsigned DATA_EN : 1;
		unsigned REQ : 1;
		unsigned LPD : 1;
		unsigned PSTATE : 2;
		unsigned RATE : 2;
		unsigned WIDTH : 2;
		unsigned RESERVED : 1;
		unsigned ADAPT_AFE_EN : 1;
		unsigned ADAPT_DFE_EN : 1;
		unsigned CDR_TRACK_EN : 1;
		unsigned RESERVED_15_15 : 1;
	} b;
} CR_LANE1_DIG_ASIC_RX_ASIC_IN_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned CDR_SSC_EN : 1;
		unsigned ALIGN_EN : 1;
		unsigned CLK_SHIFT : 1;
		unsigned DISABLE : 1;
		unsigned RX_TERM_EN : 1;
		unsigned RX_TERM_ACDC : 1;
		unsigned RESERVED_15_6 : 10;
	} b;
} CR_LANE1_DIG_ASIC_RX_ASIC_IN_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned EQ_ATT_LVL : 3;
		unsigned EQ_AFE_GAIN : 4;
		unsigned RESERVED : 4;
		unsigned EQ_CTLE_BOOST : 5;
	} b;
} CR_LANE1_DIG_ASIC_RX_EQ_ASIC_IN_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned EQ_DFE_TAP2 : 7;
		unsigned EQ_DFE_TAP1 : 8;
		unsigned RESERVED_15_15 : 1;
	} b;
} CR_LANE1_DIG_ASIC_RX_EQ_ASIC_IN_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_CDR_VCO_LOWFREQ : 1;
		unsigned RX_REF_LD_VAL : 7;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_LANE1_DIG_ASIC_RX_CDR_VCO_ASIC_IN_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_VCO_LD_VAL : 13;
		unsigned RESERVED_15_13 : 3;
	} b;
} CR_LANE1_DIG_ASIC_RX_CDR_VCO_ASIC_IN_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned ACK : 1;
		unsigned VALID : 1;
		unsigned ADAPT_STS : 2;
		unsigned RESERVED_15_4 : 12;
	} b;
} CR_LANE1_DIG_ASIC_RX_ASIC_OUT_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_PWM_CLK_SEL : 2;
		unsigned RX_TERM_LCC_ON : 1;
		unsigned RX_TERM_LS_ON : 1;
		unsigned RX_TERM_CTL : 2;
		unsigned RX_PWM_EN : 1;
		unsigned RESERVED_15_7 : 9;
	} b;
} CR_LANE1_DIG_ASIC_RX_OVRD_OUT_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RPTR_EN_MASTER_LANE : 1;
		unsigned RPTR_EN_MASTER_LANE_OVRD_EN : 1;
		unsigned DIG_CLK_EN_OTHER_LANE : 1;
		unsigned DIG_CLK_EN_OTHER_LANE_OVRD_EN : 1;
		unsigned DIG_CLK_STATE_MASTER_LANE : 1;
		unsigned DIG_CLK_STATE_MASTER_LANE_OVRD_EN : 1;
		unsigned SHIFT_MASTER_LANE : 1;
		unsigned SHIFT_MASTER_LANE_ORVD_EN : 1;
		unsigned SHIFT_ACK_OTHER_LANE : 1;
		unsigned SHIFT_ACK_OTHER_LANE_OVRD_EN : 1;
		unsigned LANE_MASTER : 1;
		unsigned LANE_MASTER_OVRD_IN_EN : 1;
		unsigned RESERVED_15_12 : 4;
	} b;
} CR_LANE1_DIG_ASIC_TX_OVRD_IN_5;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RPTR_EN_OUT : 1;
		unsigned RPTR_EN_OUT_OVRD_EN : 1;
		unsigned DIG_CLK_EN_OUT : 1;
		unsigned DIG_CLK_EN_OUT_OVRD_EN : 1;
		unsigned DIG_CLK_STATE_OUT : 1;
		unsigned DIG_CLK_STATE_OUT_OVRD_EN : 1;
		unsigned SHIFT_OUT : 1;
		unsigned SHIFT_OUT_OVRD_EN : 1;
		unsigned SHIFT_ACK_OUT : 1;
		unsigned SHIFT_ACK_OUT_OVRD_EN : 1;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_LANE1_DIG_ASIC_TX_OVRD_OUT_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned TX_P0_ANA_REFGEN_EN : 1;
		unsigned TX_P0_ANA_VCM_HOLD : 1;
		unsigned TX_P0_ANA_CLK_EN : 1;
		unsigned TX_P0_ANA_WORD_CLK_EN : 1;
		unsigned TX_P0_ANA_RESET : 1;
		unsigned TX_P0_ANA_SERIAL_EN : 1;
		unsigned TX_P0_DIG_CLK_EN : 1;
		unsigned TX_P0_DATA_EN : 1;
		unsigned TX_P0_ALLOW_RXDET : 1;
		unsigned TX_P0_ANA_DCC_COMP_CAL_EN : 1;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_LANE1_DIG_TX_PWRCTL_TX_PSTATE_P0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned TX_P0S_ANA_REFGEN_EN : 1;
		unsigned TX_P0S_ANA_VCM_HOLD : 1;
		unsigned TX_P0S_ANA_CLK_EN : 1;
		unsigned TX_P0S_ANA_WORD_CLK_EN : 1;
		unsigned TX_P0S_ANA_RESET : 1;
		unsigned TX_P0S_ANA_SERIAL_EN : 1;
		unsigned TX_P0S_DIG_CLK_EN : 1;
		unsigned TX_P0S_DATA_EN : 1;
		unsigned TX_P0S_ALLOW_RXDET : 1;
		unsigned TX_P0S_ANA_DCC_COMP_CAL_EN : 1;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_LANE1_DIG_TX_PWRCTL_TX_PSTATE_P0S;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned TX_P1_ANA_REFGEN_EN : 1;
		unsigned TX_P1_ANA_VCM_HOLD : 1;
		unsigned TX_P1_ANA_CLK_EN : 1;
		unsigned TX_P1_ANA_WORD_CLK_EN : 1;
		unsigned TX_P1_ANA_RESET : 1;
		unsigned TX_P1_ANA_SERIAL_EN : 1;
		unsigned TX_P1_DIG_CLK_EN : 1;
		unsigned TX_P1_DATA_EN : 1;
		unsigned TX_P1_ALLOW_RXDET : 1;
		unsigned TX_P1_ANA_DCC_COMP_CAL_EN : 1;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_LANE1_DIG_TX_PWRCTL_TX_PSTATE_P1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned TX_P2_ANA_REFGEN_EN : 1;
		unsigned TX_P2_ANA_VCM_HOLD : 1;
		unsigned TX_P2_ANA_CLK_EN : 1;
		unsigned TX_P2_ANA_WORD_CLK_EN : 1;
		unsigned TX_P2_ANA_RESET : 1;
		unsigned TX_P2_ANA_SERIAL_EN : 1;
		unsigned TX_P2_DIG_CLK_EN : 1;
		unsigned TX_P2_DATA_EN : 1;
		unsigned TX_P2_ALLOW_RXDET : 1;
		unsigned TX_P2_ALLOW_VBOOST : 1;
		unsigned TX_P2_ANA_DCC_COMP_CAL_EN : 1;
		unsigned RESERVED_15_11 : 5;
	} b;
} CR_LANE1_DIG_TX_PWRCTL_TX_PSTATE_P2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned TX_REFGEN_EN_TIME : 8;
		unsigned TX_CLK_EN : 8;
	} b;
} CR_LANE1_DIG_TX_PWRCTL_TX_PWRUP_TIME_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned TX_VCM_HOLD_TIME_14_0 : 15;
		unsigned SKIP_TX_VCM_HOLD_WAIT : 1;
	} b;
} CR_LANE1_DIG_TX_PWRCTL_TX_PWRUP_TIME_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned TX_VBOOST_DIS_TIME_12_0 : 13;
		unsigned DTB_SEL : 3;
	} b;
} CR_LANE1_DIG_TX_PWRCTL_TX_PWRUP_TIME_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned TX_VCM_HOLD_TIME_17_15 : 3;
		unsigned TX_VBOOST_DIS_TIME_13 : 1;
		unsigned RESERVED_15_4 : 12;
	} b;
} CR_LANE1_DIG_TX_PWRCTL_TX_PWRUP_TIME_3;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned TX_VCM_HOLD_GS_TIME : 15;
		unsigned SKIP_TX_VCM_HOLD_GS_PULSE : 1;
	} b;
} CR_LANE1_DIG_TX_PWRCTL_TX_PWRUP_TIME_4;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned TX_RXDET_TIME : 10;
		unsigned FAST_TX_RXDET : 1;
		unsigned TX_RESET_TIME : 2;
		unsigned TX_SERIAL_EN_TIME : 2;
		unsigned RESERVED_15_15 : 1;
	} b;
} CR_LANE1_DIG_TX_PWRCTL_TX_PWRUP_TIME_5;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned ADDR : 16;
	} b;
} CR_LANE1_DIG_TX_PWRCTL_DCC_CR_BANK_ADDR;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DATA : 16;
	} b;
} CR_LANE1_DIG_TX_PWRCTL_DCC_CR_BANK_DATA;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned CTRL : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_LANE1_DIG_TX_PWRCTL_DCC_DAC_CTRL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned CTRL : 2;
		unsigned RESERVED_15_2 : 14;
	} b;
} CR_LANE1_DIG_TX_PWRCTL_DCC_DAC_RANGE;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned SEL : 3;
		unsigned REQ : 1;
		unsigned CTRL_UPD : 1;
		unsigned RANGE_UPD : 1;
		unsigned BIN_HOT : 1;
		unsigned RESERVED_15_7 : 9;
	} b;
} CR_LANE1_DIG_TX_PWRCTL_DCC_DAC_SEL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned ACK : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_LANE1_DIG_TX_PWRCTL_DCC_DAC_ACK;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned ADDR : 16;
	} b;
} CR_LANE1_DIG_TX_PWRCTL_DCC_DAC_ADDR;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned TX_NUM_2UI_SHIFTS_16B_MODE : 4;
		unsigned TX_NUM_2UI_SHIFTS_20B_MODE : 4;
		unsigned TX_FIFO_BYPASS : 1;
		unsigned RESERVED_15_9 : 7;
	} b;
} CR_LANE1_DIG_TX_CLK_ALIGN_TX_CTL_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MODE : 4;
		unsigned TRIGGER_ERR : 1;
		unsigned PAT0 : 10;
		unsigned RESERVED_15_15 : 1;
	} b;
} CR_LANE1_DIG_TX_LBERT_CTL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_P0_ANA_AFE_EN : 1;
		unsigned RX_P0_ANA_CLK_VREG_EN : 1;
		unsigned RESERVED_1 : 1;
		unsigned RX_P0_ANA_CLK_EN : 1;
		unsigned RESERVED_0 : 1;
		unsigned RX_P0_ANA_DESER_EN : 1;
		unsigned RX_P0_ANA_CDR_EN : 1;
		unsigned RX_P0_VCO_FREQ_RST : 1;
		unsigned RX_P0_VCO_CAL_RST : 1;
		unsigned RX_P0_VCO_CONTCAL_EN : 1;
		unsigned RX_P0_DIG_CLK_EN : 1;
		unsigned RESERVED_15_11 : 5;
	} b;
} CR_LANE1_DIG_RX_PWRCTL_RX_PSTATE_P0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_P0S_ANA_AFE_EN : 1;
		unsigned RX_P0S_ANA_CLK_VREG_EN : 1;
		unsigned RESERVED_2 : 1;
		unsigned RX_P0S_ANA_CLK_EN : 1;
		unsigned RESERVED_4 : 1;
		unsigned RX_P0S_ANA_DESER_EN : 1;
		unsigned RX_P0S_ANA_CDR_EN : 1;
		unsigned RX_P0S_VCO_FREQ_RST : 1;
		unsigned RX_P0S_VCO_CAL_RST : 1;
		unsigned RX_P0S_VCO_CONTCAL_EN : 1;
		unsigned RX_P0S_DIG_CLK_EN : 1;
		unsigned RESERVED_15_11 : 5;
	} b;
} CR_LANE1_DIG_RX_PWRCTL_RX_PSTATE_P0S;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_P1_ANA_AFE_EN : 1;
		unsigned RX_P1_ANA_CLK_VREG_EN : 1;
		unsigned RESERVED_2 : 1;
		unsigned RX_P1_ANA_CLK_EN : 1;
		unsigned RESERVED_4 : 1;
		unsigned RX_P1_ANA_DESER_EN : 1;
		unsigned RX_P1_ANA_CDR_EN : 1;
		unsigned RX_P1_VCO_FREQ_RST : 1;
		unsigned RX_P1_VCO_CAL_RST : 1;
		unsigned RX_P1_VCO_CONTCAL_EN : 1;
		unsigned RX_P1_DIG_CLK_EN : 1;
		unsigned RESERVED_15_11 : 5;
	} b;
} CR_LANE1_DIG_RX_PWRCTL_RX_PSTATE_P1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_P2_ANA_AFE_EN : 1;
		unsigned RX_P2_ANA_CLK_VREG_EN : 1;
		unsigned RESERVED_2 : 1;
		unsigned RX_P2_ANA_CLK_EN : 1;
		unsigned RESERVED_4 : 1;
		unsigned RX_P2_ANA_DESER_EN : 1;
		unsigned RX_P2_ANA_CDR_EN : 1;
		unsigned RX_P2_VCO_FREQ_RST : 1;
		unsigned RX_P2_VCO_CAL_RST : 1;
		unsigned RX_P2_VCO_CONTCAL_EN : 1;
		unsigned RX_P2_DIG_CLK_EN : 1;
		unsigned RESERVED_15_11 : 5;
	} b;
} CR_LANE1_DIG_RX_PWRCTL_RX_PSTATE_P2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_AFE_EN_TIME : 6;
		unsigned FAST_RX_AFE_EN : 1;
		unsigned RX_VREG_EN_TIME : 6;
		unsigned FAST_RX_VREG_EN : 1;
		unsigned RESERVED_15_14 : 2;
	} b;
} CR_LANE1_DIG_RX_PWRCTL_RX_PWRUP_TIME_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_CLK_EN_TIME : 6;
		unsigned FAST_RX_CLK_EN : 1;
		unsigned RX_FAST_START_TIME : 4;
		unsigned RESERVED_15_11 : 5;
	} b;
} CR_LANE1_DIG_RX_PWRCTL_RX_PWRUP_TIME_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_RATE_TIME : 2;
		unsigned RSVD_3_7_2 : 6;
		unsigned RX_CDR_EN_TIME : 4;
		unsigned RX_DESER_EN_TIME : 2;
		unsigned RX_DESER_DIS_TIME : 2;
	} b;
} CR_LANE1_DIG_RX_PWRCTL_RX_PWRUP_TIME_3;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned INT_GAIN_CAL_FIXED_CNT : 5;
		unsigned INT_GAIN_CAL_FIXED_CNT_EN : 1;
		unsigned INT_GAIN_CAL_CNT_SHIFT : 3;
		unsigned INT_GAIN_CAL_BOUNCE_CNT : 3;
		unsigned RESERVED_15_12 : 4;
	} b;
} CR_LANE1_DIG_RX_VCOCAL_RX_VCO_CAL_CTRL_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_VCO_OVRD_SEL : 1;
		unsigned RX_VCO_FREQ_RST : 1;
		unsigned RX_VCO_CAL_RST : 1;
		unsigned RX_VCO_CONTCAL_EN : 1;
		unsigned DISABLE_INT_CAL_MODE : 1;
		unsigned DPLL_CAL_UG : 4;
		unsigned DTB_SEL : 7;
	} b;
} CR_LANE1_DIG_RX_VCOCAL_RX_VCO_CAL_CTRL_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned FREQ_TUNE_START_VAL : 10;
		unsigned FREQ_TUNE_CAL_STEPS : 4;
		unsigned SKIP_RX_VCO_FREQ_TUNE_CAL : 1;
		unsigned SKIP_RX_VCO_CAL : 1;
	} b;
} CR_LANE1_DIG_RX_VCOCAL_RX_VCO_CAL_CTRL_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_VCO_STARTUP_TIME : 7;
		unsigned RX_VCO_UPDATE_TIME : 4;
		unsigned RX_VCO_CNTR_PWRUP_TIME : 4;
		unsigned FAST_RX_VCO_WAIT : 1;
	} b;
} CR_LANE1_DIG_RX_VCOCAL_RX_VCO_CAL_TIME_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_VCO_CNTR_SETTLE_TIME : 3;
		unsigned RESERVED_15_3 : 13;
	} b;
} CR_LANE1_DIG_RX_VCOCAL_RX_VCO_CAL_TIME_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_ANA_CDR_FREQ_TUNE : 10;
		unsigned RX_ANA_VCO_CNTR_PD : 1;
		unsigned RX_ANA_VCO_CNTR_EN : 1;
		unsigned RX_ANA_CDR_STARTUP : 1;
		unsigned RX_ANA_CDR_VCO_EN : 1;
		unsigned RESERVED_15_14 : 2;
	} b;
} CR_LANE1_DIG_RX_VCOCAL_RX_VCO_STAT_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_VCO_FSM_STATE : 4;
		unsigned RX_VCO_FREQ_RST : 1;
		unsigned RX_VCO_CAL_RST : 1;
		unsigned RX_VCO_CONTCAL_EN : 1;
		unsigned RX_VCO_CAL_DONE : 1;
		unsigned DPLL_FREQ_RST : 1;
		unsigned RESERVED_15_9 : 7;
	} b;
} CR_LANE1_DIG_RX_VCOCAL_RX_VCO_STAT_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned VCO_CNTR_FINAL : 13;
		unsigned VCOCLK_TOO_FAST : 1;
		unsigned RX_VCO_CORRECT : 1;
		unsigned RX_VCO_UP : 1;
	} b;
} CR_LANE1_DIG_RX_VCOCAL_RX_VCO_STAT_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned XAUI_COMM_MASK : 10;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_LANE1_DIG_RX_RX_ALIGN_XAUI_COMM_MASK;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MODE : 4;
		unsigned SYNC : 1;
		unsigned RESERVED_15_5 : 11;
	} b;
} CR_LANE1_DIG_RX_LBERT_CTL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned COUNT : 15;
		unsigned OV14 : 1;
	} b;
} CR_LANE1_DIG_RX_LBERT_ERR;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned PHDET_EN : 2;
		unsigned PHDET_EDGE : 2;
		unsigned PHDET_POL : 1;
		unsigned PHDET_EN_PR_MODE : 1;
		unsigned ALWAYS_REALIGN : 1;
		unsigned DTB_SEL : 4;
		unsigned RESERVED_15_11 : 5;
	} b;
} CR_LANE1_DIG_RX_CDR_CDR_CTL_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned SSC_OFF_CNT0 : 10;
		unsigned SSC_OFF_CNT1 : 6;
	} b;
} CR_LANE1_DIG_RX_CDR_CDR_CTL_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned SSC_ON_CNT0 : 9;
		unsigned SSC_ON_CNT1 : 7;
	} b;
} CR_LANE1_DIG_RX_CDR_CDR_CTL_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned SSC_OFF_PHUG0 : 3;
		unsigned SSC_OFF_PHUG1 : 3;
		unsigned SSC_OFF_FRUG0 : 3;
		unsigned OVRD_DPLL_GAIN : 1;
		unsigned PHUG_OVRD_VALUE : 3;
		unsigned FRUG_OVRD_VALUE : 3;
	} b;
} CR_LANE1_DIG_RX_CDR_CDR_CTL_3;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned SSC_OFF_FRUG1 : 3;
		unsigned SSC_ON_FRUG0 : 3;
		unsigned SSC_ON_FRUG1 : 3;
		unsigned SSC_ON_PHUG0 : 3;
		unsigned SSC_ON_PHUG1 : 3;
		unsigned RESERVED_15_15 : 1;
	} b;
} CR_LANE1_DIG_RX_CDR_CDR_CTL_4;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned PHUG_VALUE : 3;
		unsigned FRUG_VALUE : 3;
		unsigned RESERVED_15_6 : 10;
	} b;
} CR_LANE1_DIG_RX_CDR_STAT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned VAL : 14;
		unsigned RESERVED_15_14 : 2;
	} b;
} CR_LANE1_DIG_RX_DPLL_FREQ;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned FREQ_BOUND_EN : 1;
		unsigned UPPER_FREQ_BOUND : 10;
		unsigned RESERVED_15_11 : 5;
	} b;
} CR_LANE1_DIG_RX_DPLL_FREQ_BOUND_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned LOWER_FREQ_BOUND : 10;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_LANE1_DIG_RX_DPLL_FREQ_BOUND_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned N_TOP_ASM1 : 10;
		unsigned N_TGG_ASM1 : 4;
		unsigned START_ASM1 : 1;
		unsigned ADPT_CLK_DIV4_EN : 1;
	} b;
} CR_LANE1_DIG_RX_ADPTCTL_ADPT_CFG_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned N_WAIT_ASM1 : 7;
		unsigned FAST_AFE_DFE_SETTLE : 1;
		unsigned CTLE_POLE_OVRD_VAL : 3;
		unsigned CTLE_POLE_OVRD_EN : 1;
		unsigned RESERVED_15_12 : 4;
	} b;
} CR_LANE1_DIG_RX_ADPTCTL_ADPT_CFG_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned TGG_PTTRN_0 : 5;
		unsigned TGG_PTTRN_1 : 5;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_LANE1_DIG_RX_ADPTCTL_ADPT_CFG_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned CTLE_EN : 5;
		unsigned VGA_EN : 1;
		unsigned ATT_EN : 1;
		unsigned DFE_EN : 5;
		unsigned EYEHE_EN : 1;
		unsigned EYEHO_EN : 1;
		unsigned TGG_EN : 1;
		unsigned ESL_TWICE_DSL : 1;
	} b;
} CR_LANE1_DIG_RX_ADPTCTL_ADPT_CFG_3;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned CTLE_TH : 4;
		unsigned VGA_TH : 4;
		unsigned DFE1_TH : 4;
		unsigned DFE2_TH : 4;
	} b;
} CR_LANE1_DIG_RX_ADPTCTL_ADPT_CFG_4;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DFE3_TH : 4;
		unsigned DFE4_TH : 4;
		unsigned DFE5_TH : 4;
		unsigned TH_OFFSET : 4;
	} b;
} CR_LANE1_DIG_RX_ADPTCTL_ADPT_CFG_5;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned CTLE_MU : 3;
		unsigned VGA_MU : 3;
		unsigned ATT_MU : 3;
		unsigned VGA_SAT_CNT : 3;
		unsigned VGA_SAT_CNT_STICKY : 1;
		unsigned ATT_LOW_TH : 3;
	} b;
} CR_LANE1_DIG_RX_ADPTCTL_ADPT_CFG_6;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned VGA_MIN_SAT : 5;
		unsigned VGA_LEV_HIGH : 5;
		unsigned VGA_LEV_LOW : 5;
		unsigned RESERVED_15_15 : 1;
	} b;
} CR_LANE1_DIG_RX_ADPTCTL_ADPT_CFG_7;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DFE1_MU : 3;
		unsigned DFE2_MU : 3;
		unsigned DFE3_MU : 3;
		unsigned DFE4_MU : 3;
		unsigned DFE5_MU : 3;
		unsigned RESERVED_15_15 : 1;
	} b;
} CR_LANE1_DIG_RX_ADPTCTL_ADPT_CFG_8;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned ERR_SLE_ADPT_INIT : 8;
		unsigned ERR_SLO_ADPT_INIT : 8;
	} b;
} CR_LANE1_DIG_RX_ADPTCTL_ADPT_CFG_9;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RST_ADPT_ATT : 1;
		unsigned RST_ADPT_VGA : 1;
		unsigned RST_ADPT_CTLE_BOOST : 1;
		unsigned RST_ADPT_CTLE_POLE : 1;
		unsigned RST_ADPT_TAP1 : 1;
		unsigned RESERVED_15_5 : 11;
	} b;
} CR_LANE1_DIG_RX_ADPTCTL_RST_ADPT_CFG;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned ATT_ADPT_CODE : 8;
		unsigned ASM1_DON : 1;
		unsigned RESERVED_15_9 : 7;
	} b;
} CR_LANE1_DIG_RX_ADPTCTL_ATT_STATUS;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned VGA_ADPT_CODE : 10;
		unsigned ASM1_DONE : 1;
		unsigned RESERVED_15_11 : 5;
	} b;
} CR_LANE1_DIG_RX_ADPTCTL_VGA_STATUS;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned CTLE_BOOST_ADPT_CODE : 10;
		unsigned CTLE_POLE_ADPT_CODE : 3;
		unsigned ASM1_DONE : 1;
		unsigned RESERVED_15_14 : 2;
	} b;
} CR_LANE1_DIG_RX_ADPTCTL_CTLE_STATUS;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DFE_TAP1_ADPT_CODE : 13;
		unsigned ASM1_DONE : 1;
		unsigned RESERVED_15_14 : 2;
	} b;
} CR_LANE1_DIG_RX_ADPTCTL_DFE_TAP1_STATUS;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DFE_TAP2_ADPT_CODE : 12;
		unsigned ASM1_DONE : 1;
		unsigned RESERVED_15_13 : 3;
	} b;
} CR_LANE1_DIG_RX_ADPTCTL_DFE_TAP2_STATUS;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DFE_TAP3_ADPT_CODE : 12;
		unsigned ASM1_DONE : 1;
		unsigned RESERVED_15_13 : 3;
	} b;
} CR_LANE1_DIG_RX_ADPTCTL_DFE_TAP3_STATUS;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DFE_TAP4_ADPT_CODE : 12;
		unsigned ASM1_DONE : 1;
		unsigned RESERVED_15_13 : 3;
	} b;
} CR_LANE1_DIG_RX_ADPTCTL_DFE_TAP4_STATUS;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DFE_TAP5_ADPT_CODE : 12;
		unsigned ASM1_DONE : 1;
		unsigned RESERVED_15_13 : 3;
	} b;
} CR_LANE1_DIG_RX_ADPTCTL_DFE_TAP5_STATUS;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DFE_DATA_EVEN_VDAC_OFST : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_LANE1_DIG_RX_ADPTCTL_DFE_DATA_EVEN_VDAC_OFST;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DFE_DATA_ODD_VDAC_OFST : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_LANE1_DIG_RX_ADPTCTL_DFE_DATA_ODD_VDAC_OFST;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_ANA_SLICER_CTRL_E : 4;
		unsigned RESERVED_15_4 : 12;
	} b;
} CR_LANE1_DIG_RX_ADPTCTL_RX_SLICER_CTRL_EVEN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_ANA_SLICER_CTRL_O : 4;
		unsigned RESERVED_15_4 : 12;
	} b;
} CR_LANE1_DIG_RX_ADPTCTL_RX_SLICER_CTRL_ODD;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DFE_ERROR_EVEN_VDAC_OFST : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_LANE1_DIG_RX_ADPTCTL_DFE_ERROR_EVEN_VDAC_OFST;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DFE_ERROR_ODD_VDAC_OFST : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_LANE1_DIG_RX_ADPTCTL_DFE_ERROR_ODD_VDAC_OFST;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned E_SLO_LVL : 8;
		unsigned E_SLE_LVL : 8;
	} b;
} CR_LANE1_DIG_RX_ADPTCTL_ERROR_SLICER_LEVEL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RESET_ASM1 : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_LANE1_DIG_RX_ADPTCTL_ADPT_RESET;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DFE_T1_IDAC : 5;
		unsigned DFE_T2_IDAC : 5;
		unsigned DCC_START_IDAC : 5;
		unsigned RESERVED_15_15 : 1;
	} b;
} CR_LANE1_DIG_RX_ADPTCTL_DAC_CTRL_SEL_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DFE_DAT_EVEN_VDAC : 5;
		unsigned DFE_DAT_ODD_VDAC : 5;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_LANE1_DIG_RX_ADPTCTL_DAC_CTRL_SEL_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DFE_ERR_EVEN_VDAC : 5;
		unsigned DFE_ERR_ODD_VDAC : 5;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_LANE1_DIG_RX_ADPTCTL_DAC_CTRL_SEL_3;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned ADDR : 16;
	} b;
} CR_LANE1_DIG_RX_ADPTCTL_CR_BANK_ADDR;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DATA : 16;
	} b;
} CR_LANE1_DIG_RX_ADPTCTL_CR_BANK_DATA;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned SC1_LD_VAL : 15;
		unsigned SC1_START : 1;
	} b;
} CR_LANE1_DIG_RX_STAT_LD_VAL_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DATA_MSK_15_0 : 16;
	} b;
} CR_LANE1_DIG_RX_STAT_DATA_MSK;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned PTTRN_MSK_CR1A_4_0 : 5;
		unsigned PTTRN_CR1A_4_0 : 5;
		unsigned DATA_MSK_19_16 : 4;
		unsigned SCOPE_DLY : 2;
	} b;
} CR_LANE1_DIG_RX_STAT_MATCH_CTL0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned PTTRN_CR1B_EN : 1;
		unsigned PTTRN_MSK_CR1B_4_0 : 5;
		unsigned PTTRN_CR1B_4_0 : 5;
		unsigned PTTRN_CR1A_ADPT_EN : 1;
		unsigned RESERVED_15_12 : 4;
	} b;
} CR_LANE1_DIG_RX_STAT_MATCH_CTL1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RESERVED_0 : 1;
		unsigned CORR_SHFT_SEL_VGA : 1;
		unsigned CORR_SHFT_SEL : 1;
		unsigned CORR_SRC_SEL : 2;
		unsigned CORR_MODE_EN : 1;
		unsigned STAT_SHFT_SEL : 4;
		unsigned STAT_SRC_SEL : 3;
		unsigned STAT_RXCLK_SEL : 1;
		unsigned SC_TIMER_MODE : 1;
		unsigned SKIP_EN : 1;
	} b;
} CR_LANE1_DIG_RX_STAT_STAT_CTL0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned STAT_CNT_0_EN : 1;
		unsigned STAT_CNT_1_EN : 1;
		unsigned STAT_CNT_2_EN : 1;
		unsigned STAT_CNT_3_EN : 1;
		unsigned STAT_CNT_4_EN : 1;
		unsigned STAT_CNT_5_EN : 1;
		unsigned STAT_CNT_6_EN : 1;
		unsigned RESERVED_8_7 : 2;
		unsigned SC_PAUSE : 1;
		unsigned STAT_CLK_EN : 1;
		unsigned DATA_DLY_SEL : 2;
		unsigned VLD_LOSS_CLR : 1;
		unsigned VLD_CTL : 2;
	} b;
} CR_LANE1_DIG_RX_STAT_STAT_CTL1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned SMPL_CNT1 : 15;
		unsigned SMPL_CNT1_DONE : 1;
	} b;
} CR_LANE1_DIG_RX_STAT_SMPL_CNT1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned STAT_CNT_0 : 15;
		unsigned SMPL_CNT1_DONE : 1;
	} b;
} CR_LANE1_DIG_RX_STAT_STAT_CNT_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned STAT_CNT_1 : 15;
		unsigned SMPL_CNT1_DONE : 1;
	} b;
} CR_LANE1_DIG_RX_STAT_STAT_CNT_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned STAT_CNT_2 : 15;
		unsigned SMPL_CNT1_DONE : 1;
	} b;
} CR_LANE1_DIG_RX_STAT_STAT_CNT_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned STAT_CNT_3 : 15;
		unsigned SMPL_CNT1_DONE : 1;
	} b;
} CR_LANE1_DIG_RX_STAT_STAT_CNT_3;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned STAT_CNT_4 : 15;
		unsigned SMPL_CNT1_DONE : 1;
	} b;
} CR_LANE1_DIG_RX_STAT_STAT_CNT_4;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned STAT_CNT_5 : 15;
		unsigned SMPL_CNT1_DONE : 1;
	} b;
} CR_LANE1_DIG_RX_STAT_STAT_CNT_5;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned STAT_CNT_6 : 15;
		unsigned SMPL_CNT1_DONE : 1;
	} b;
} CR_LANE1_DIG_RX_STAT_STAT_CNT_6;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned PRECHRGE_CNT : 3;
		unsigned REF_DIV_CNT : 3;
		unsigned RESERVED_15_6 : 10;
	} b;
} CR_LANE1_DIG_RX_STAT_CAL_COMP_CLK_CTL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned PTTRN_CR1A_19_5 : 15;
		unsigned RESERVED_15_15 : 1;
	} b;
} CR_LANE1_DIG_RX_STAT_MATCH_CTL2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned PTTRN_MSK_CR1A_19_5 : 15;
		unsigned RESERVED_15_15 : 1;
	} b;
} CR_LANE1_DIG_RX_STAT_MATCH_CTL3;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned PTTRN_CR1B_19_5 : 15;
		unsigned RESERVED_15_15 : 1;
	} b;
} CR_LANE1_DIG_RX_STAT_MATCH_CTL4;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned PTTRN_MSK_CR1B_19_5 : 15;
		unsigned RESERVED_15_15 : 1;
	} b;
} CR_LANE1_DIG_RX_STAT_MATCH_CTL5;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DATA_DLY_SEL_2 : 1;
		unsigned SCOPE_DLY_2 : 1;
		unsigned DISABLE_SAMPLE_COUNT : 1;
		unsigned RESERVED_15_3 : 13;
	} b;
} CR_LANE1_DIG_RX_STAT_STAT_CTL2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned SC1_STOP : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_LANE1_DIG_RX_STAT_STAT_STOP;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_PWM_POL : 1;
		unsigned RX_PWM_DATA_POL : 1;
		unsigned RESERVED_15_2 : 14;
	} b;
} CR_LANE1_DIG_MPHY_RX_PWM_CTL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_TERM_LCC_CNT : 3;
		unsigned RESERVED_15_3 : 13;
	} b;
} CR_LANE1_DIG_MPHY_RX_TERM_LS_CTL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned PWM_CLK_STABLE_CNT : 4;
		unsigned RESERVED_15_4 : 12;
	} b;
} CR_LANE1_DIG_MPHY_RX_ANA_PWM_CLK_STABLE_CNT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned TX_ANA_CLK_SHIFT : 1;
		unsigned TX_ANA_DATA_EN : 1;
		unsigned TX_ANA_REFGEN_EN : 1;
		unsigned TX_ANA_VCM_HOLD : 1;
		unsigned TX_ANA_CLK_EN : 1;
		unsigned TX_ANA_WORD_CLK_EN : 1;
		unsigned TX_ANA_MPLLA_CLK_EN : 1;
		unsigned TX_ANA_MPLLB_CLK_EN : 1;
		unsigned TX_ANA_RESET : 1;
		unsigned TX_ANA_SERIAL_EN : 1;
		unsigned TX_ANA_DATA_RATE : 2;
		unsigned RESERVED : 1;
		unsigned TX_DIV4_EN : 1;
		unsigned TX_RXDET_EN : 1;
		unsigned TX_OVRD_EN : 1;
	} b;
} CR_LANE1_DIG_ANA_TX_OVRD_OUT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned TX_TERM_CODE : 10;
		unsigned TX_TERM_OVRD_EN : 1;
		unsigned RESERVED_15_11 : 5;
	} b;
} CR_LANE1_DIG_ANA_TX_TERM_CODE_OVRD_OUT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned TX_TERM_DN_CLK : 1;
		unsigned TX_TERM_CLK_SELF_CLEAR_DISABLE : 1;
		unsigned RESERVED_15_2 : 14;
	} b;
} CR_LANE1_DIG_ANA_TX_TERM_CODE_CLK_OVRD_OUT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned TX_ANA_LOAD_CLK : 1;
		unsigned TX_ANA_CTRL_LEG_PULL_EN_13_0 : 14;
		unsigned TX_EQ_OVRD_EN : 1;
	} b;
} CR_LANE1_DIG_ANA_TX_EQ_OVRD_OUT_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned TX_ANA_CTRL_LEG_PULL_EN_19_14 : 6;
		unsigned RESERVED_15_6 : 10;
	} b;
} CR_LANE1_DIG_ANA_TX_EQ_OVRD_OUT_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RESERVED : 7;
		unsigned TX_ANA_CTRL_PRE : 6;
		unsigned RESERVED_15_13 : 3;
	} b;
} CR_LANE1_DIG_ANA_TX_EQ_OVRD_OUT_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned TX_ANA_CTRL_POST : 9;
		unsigned RESERVED_15_9 : 7;
	} b;
} CR_LANE1_DIG_ANA_TX_EQ_OVRD_OUT_3;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned TX_ANA_CTRL_LEG_PULL_DIR_19_4 : 16;
	} b;
} CR_LANE1_DIG_ANA_TX_EQ_OVRD_OUT_4;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned TX_ANA_CTRL_LEG_PULL_DIR_3_0 : 4;
		unsigned RESERVED_15_4 : 12;
	} b;
} CR_LANE1_DIG_ANA_TX_EQ_OVRD_OUT_5;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RESERVED : 1;
		unsigned RX_ANA_DATA_RATE : 2;
		unsigned RX_ANA_WORD_CLK_EN : 1;
		unsigned RX_ANA_DIV4_EN : 1;
		unsigned RX_ANA_DFE_TAPS_EN : 1;
		unsigned RX_ANA_ADAPTATION_EN : 1;
		unsigned RX_LBK_CLK_EN : 1;
		unsigned RX_CTL_OVRD_EN : 1;
		unsigned RESERVED_15_9 : 7;
	} b;
} CR_LANE1_DIG_ANA_RX_CTL_OVRD_OUT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_ANA_AFE_EN : 1;
		unsigned RX_ANA_CLK_VREG_EN : 1;
		unsigned RX_ANA_CLK_DCC_EN : 1;
		unsigned RX_ANA_CLK_EN : 1;
		unsigned RX_ANA_CDR_EN : 1;
		unsigned RX_ANA_DESERIAL_EN : 1;
		unsigned RX_PWR_OVRD_EN : 1;
		unsigned RX_ANA_FAST_START : 1;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_LANE1_DIG_ANA_RX_PWR_OVRD_OUT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_ANA_CDR_VCO_EN : 1;
		unsigned RX_ANA_CDR_STARTUP : 1;
		unsigned RX_VCO_CDR_OVRD_EN : 1;
		unsigned RX_ANA_CDR_FREQ_TUNE : 10;
		unsigned RX_ANA_VCO_CNTR_EN : 1;
		unsigned RX_ANA_VCO_CNTR_CLK : 1;
		unsigned RX_CDR_FREQ_TUNE_OVRD_EN : 1;
	} b;
} CR_LANE1_DIG_ANA_RX_VCO_OVRD_OUT_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_ANA_CDR_VCO_LOWFREQ : 1;
		unsigned RX_ANA_VCO_CNTR_PD : 1;
		unsigned RESERVED_15_2 : 14;
	} b;
} CR_LANE1_DIG_ANA_RX_VCO_OVRD_OUT_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_ANA_CDR_FREQ_TUNE_CLK : 1;
		unsigned CDR_FREQ_TUNE_CLK_SELF_CLEAR_DISABLE : 1;
		unsigned RESERVED_15_2 : 14;
	} b;
} CR_LANE1_DIG_ANA_RX_VCO_OVRD_OUT_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_ANA_CAL_MUXA_SEL : 5;
		unsigned RX_ANA_CAL_MUXB_SEL : 5;
		unsigned RX_ANA_CAL_LPFBYP_EN : 1;
		unsigned RESERVED : 1;
		unsigned RX_ANA_SLICER_CAL_EN : 1;
		unsigned RX_ANA_CAL_MODE : 2;
		unsigned RX_ANA_CAL_COMP_EN : 1;
	} b;
} CR_LANE1_DIG_ANA_RX_CAL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_ANA_CAL_DAC_CTRL : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_LANE1_DIG_ANA_RX_DAC_CTRL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_CAL_DAC_CTRL_OVRD : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_LANE1_DIG_ANA_RX_DAC_CTRL_OVRD;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_ANA_CAL_DAC_CTRL_SEL : 5;
		unsigned RESERVED_15_5 : 11;
	} b;
} CR_LANE1_DIG_ANA_RX_DAC_CTRL_SEL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_ANA_AFE_ATT_LVL : 3;
		unsigned RX_ANA_AFE_GAIN : 4;
		unsigned RESERVED : 4;
		unsigned RX_AFE_OVRD_EN : 1;
		unsigned RESERVED_15_12 : 4;
	} b;
} CR_LANE1_DIG_ANA_RX_AFE_ATT_VGA;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RESERVED : 3;
		unsigned RX_ANA_AFE_CTLE_BOOST : 5;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_LANE1_DIG_ANA_RX_AFE_CTLE;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_ANA_SCOPE_EN : 1;
		unsigned RX_ANA_SCOPE_SEL : 2;
		unsigned RX_ANA_SCOPE_PH_CLK : 1;
		unsigned RX_ANA_SCOPE_PHASE : 8;
		unsigned RX_ANA_SCOPE_CLK_EN : 1;
		unsigned RX_SCOPE_SELF_CLEAR_DISABLE : 1;
		unsigned RESERVED_15_14 : 2;
	} b;
} CR_LANE1_DIG_ANA_RX_SCOPE;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_ANA_SLICER_CTRL_E : 4;
		unsigned RX_ANA_SLICER_CTRL_O : 4;
		unsigned RX_ANA_SLICER_CTRL_OVRD_EN : 1;
		unsigned RESERVED_15_9 : 7;
	} b;
} CR_LANE1_DIG_ANA_RX_SLICER_CTRL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_ANA_IQ_PHASE_ADJUST : 7;
		unsigned RESERVED_15_7 : 9;
	} b;
} CR_LANE1_DIG_ANA_RX_ANA_IQ_PHASE_ADJUST;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_ANA_IQ_SENSE_EN : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_LANE1_DIG_ANA_RX_ANA_IQ_SENSE_EN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_ANA_CAL_DAC_CTRL_EN : 1;
		unsigned DAC_CTRL_SELF_CLEAR_DISABLE : 1;
		unsigned RESERVED_15_2 : 14;
	} b;
} CR_LANE1_DIG_ANA_RX_ANA_CAL_DAC_CTRL_EN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_ANA_AFE_UPDATE_EN : 1;
		unsigned AFE_UPDATE_SELF_CLEAR_DISABLE : 1;
		unsigned RESERVED_15_2 : 14;
	} b;
} CR_LANE1_DIG_ANA_RX_ANA_SIGNALS_CHANGES_ENABLE;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_ANA_IQ_PHASE_ADJUST_CLK : 1;
		unsigned PHASE_ADJUST_SELF_CLEAR_DISABLE : 1;
		unsigned RESERVED_15_2 : 14;
	} b;
} CR_LANE1_DIG_ANA_RX_ANA_PHASE_ADJUST_CLK;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned TX_ANA_CLK_SHIFT_ACK : 1;
		unsigned TX_ANA_RXDETP_RESULT : 1;
		unsigned TX_ANA_RXDETM_RESULT : 1;
		unsigned TX_ANA_LOOPBACK_EN : 1;
		unsigned TX_ANA_CLK_LB_EN : 1;
		unsigned RX_ANA_CAL_RESULT : 1;
		unsigned RX_ANA_SCOPE_DATA : 1;
		unsigned TX_ANA_DCC_CAL_RESULT : 1;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_LANE1_DIG_ANA_STATUS_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_ANA_VCO_CNTR : 13;
		unsigned RESERVED_15_13 : 3;
	} b;
} CR_LANE1_DIG_ANA_STATUS_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_TERM_CODE : 6;
		unsigned RX_TERM_OVRD_EN : 1;
		unsigned RESERVED_15_7 : 9;
	} b;
} CR_LANE1_DIG_ANA_RX_TERM_CODE_OVRD_OUT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_TERM_CLK : 1;
		unsigned RX_TERM_CLK_SELF_CLEAR_DISABLE : 1;
		unsigned RESERVED_15_2 : 14;
	} b;
} CR_LANE1_DIG_ANA_RX_TERM_CODE_CLK_OVRD_OUT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_ANA_SQ_CTRL_TRESH : 3;
		unsigned RX_ANA_SQ_CTRL_TRESH_OVRD_EN : 1;
		unsigned RX_ANA_SQ_CTRL_RESP : 2;
		unsigned RX_ANA_SQ_CTRL_RESP_OVRD_EN : 1;
		unsigned RX_ANA_PWM_EN : 1;
		unsigned RX_ANA_PWM_EN_OVRD_EN : 1;
		unsigned RX_ANA_PWM_CLK_SEL : 2;
		unsigned RX_ANA_PWM_CLK_SEL_OVRD_EN : 1;
		unsigned RX_ANA_TERM_CTRL : 2;
		unsigned RX_ANA_TERM_CTRL_OVRD_EN : 1;
		unsigned RESERVED_15_15 : 1;
	} b;
} CR_LANE1_DIG_ANA_MPHY_OVRD_OUT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_ANA_SIGDET_HF_THRESH : 3;
		unsigned RX_ANA_SIGDET_HF_THRESH_OVRD_EN : 1;
		unsigned RX_ANA_SIGDET_HF_CAL_TUNE : 6;
		unsigned RX_ANA_SIGDET_CAL_TUNE_OVRD_EN : 1;
		unsigned RX_ANA_SIGDET_CAL_EN : 1;
		unsigned RX_ANA_SIGDET_CAL_EN_OVRD_EN : 1;
		unsigned RESERVED_15_13 : 3;
	} b;
} CR_LANE1_DIG_ANA_SIGDET_OVRD_OUT_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_ANA_SIGDET_LF_THRESH : 3;
		unsigned RX_ANA_SIGDET_LF_THRESH_OVRD_EN : 1;
		unsigned RX_ANA_SIGDET_LF_FILTER_EN : 1;
		unsigned RX_ANA_SIGDET_LF_FILTER_EN_OVRD_EN : 1;
		unsigned RX_ANA_SIGDET_CAL_TUNE : 6;
		unsigned RX_ANA_SIGDET_CAL_TUNE_OVRD_EN : 1;
		unsigned RESERVED_15_13 : 3;
	} b;
} CR_LANE1_DIG_ANA_SIGDET_OVRD_OUT_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned TX_ANA_DCC_CAL_RANGE : 2;
		unsigned TX_ANA_DCC_CAL_RANGE_OVRD_EN : 1;
		unsigned TX_ANA_DCC_CAL_COMP_EN : 1;
		unsigned TX_ANA_DCC_CAL_COMP_EN_OVRD_EN : 1;
		unsigned TX_ANA_DCC_CAL_CTRL : 8;
		unsigned TX_ANA_DCC_CAL_CTRL_OVRD_EN : 1;
		unsigned TX_ANA_DCC_CAL_CTRL_EN : 1;
		unsigned TX_ANA_DCC_CAL_CTRL_EN_OVRD_EN : 1;
	} b;
} CR_LANE1_DIG_ANA_TX_DCC_DAC_OVRD_OUT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned TX_ANA_DCC_CAL_CTRL_SEL : 3;
		unsigned TX_ANA_DCC_CAL_CTRL_SEL_OVRD_EN : 1;
		unsigned TX_ANA_DCC_CLK_COMP : 1;
		unsigned TX_ANA_DCC_CLK_COMP_OVRD_EN : 1;
		unsigned RESERVED_15_6 : 10;
	} b;
} CR_LANE1_DIG_ANA_TX_DCC_DAC_OVRD_OUT_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned TX_ANA_FAST_START : 1;
		unsigned TX_ANA_FAST_START_OVRD_EN : 1;
		unsigned TX_CLK_LB_EN : 1;
		unsigned TX_CLK_LB_EN_OVRD_EN : 1;
		unsigned RESERVED_15_4 : 12;
	} b;
} CR_LANE1_DIG_ANA_TX_OVRD_OUT_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned OVRD_CLK_SHIFT : 1;
		unsigned CLK_SHIFT_REG : 1;
		unsigned MEAS_ATB_CAL_MUX : 1;
		unsigned MEAS_ATB_CAL_COMP : 1;
		unsigned OVRD_VCM_HOLD : 1;
		unsigned VCM_HOLD_REG : 1;
		unsigned PULL_UP_REG : 1;
		unsigned PULL_DN_REG : 1;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_LANE1_ANA_TX_OVRD_MEAS;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned OVRD_TX_LOOPBACK : 1;
		unsigned LOOPBACK_EN_REG : 1;
		unsigned REFGEN_EN_REG : 1;
		unsigned CLK_DIV_EN_REG : 1;
		unsigned DATA_EN_REG_INT : 1;
		unsigned CLK_EN_REG : 1;
		unsigned SERIAL_EN_REG : 1;
		unsigned OVRD_EN : 1;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_LANE1_ANA_TX_PWR_OVRD;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DRV_SOURCE_REG : 2;
		unsigned OVRD_ALT_BUS : 1;
		unsigned ATB_S_ENABLE : 1;
		unsigned TX_ALT_RINGO : 3;
		unsigned JTAG_DATA_REG : 1;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_LANE1_ANA_TX_ALT_BUS;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MEAS_ATB_GD : 1;
		unsigned MEAS_ATB_VDDH : 1;
		unsigned OVERRIDE_RXDETREF : 1;
		unsigned MEAS_ATB_VPTX : 1;
		unsigned OVERRIDE_REGREF : 1;
		unsigned MEAS_ATB_VREG_DRV : 1;
		unsigned MEAS_ATB_VREG : 1;
		unsigned MEAS_ATB_VPH_HALF : 1;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_LANE1_ANA_TX_ATB1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MEAS_ATB_VCM : 1;
		unsigned MEAS_ATB_CAL_VDAC_CM : 1;
		unsigned MEAS_ATB_CAL_VDAC_DIFF : 1;
		unsigned MEAS_ATB_TXM : 1;
		unsigned MEAS_ATB_TXP : 1;
		unsigned MEAS_ATB_RXDETREF : 1;
		unsigned LFPS_HIGH_PRIORITY : 1;
		unsigned OSC_DIV4_EN : 1;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_LANE1_ANA_TX_ATB2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DCC_DAC_REG : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_LANE1_ANA_TX_DCC_DAC;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned NC0 : 1;
		unsigned OVRD_DCC_DAC_CTRL_SEL : 1;
		unsigned DCC_DAC_CTRL_SEL_REG : 3;
		unsigned OVRD_DCC_DAC_CTRL_EN : 1;
		unsigned DCC_DAC_CTRL_EN_REG : 1;
		unsigned OVRD_DCC_DAC_REG : 1;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_LANE1_ANA_TX_DCC_CTRL1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned TERM_CODE_REG_70 : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_LANE1_ANA_TX_TERM_CODE;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned VREG_BOOST_1 : 1;
		unsigned OVRD_UPDATE_TERM : 1;
		unsigned UPDATE_TERM_REG : 1;
		unsigned OVRD_RESET_TERM : 1;
		unsigned RESET_TERM_REG : 1;
		unsigned OVRD_TERM_CODE : 1;
		unsigned TERM_CODE_REG_98 : 2;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_LANE1_ANA_TX_TERM_CODE_CTRL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned VREG_BOOST_0 : 1;
		unsigned CLK_LB_EN_REG : 1;
		unsigned OVRD_LB_EN : 1;
		unsigned MPLLB_CLK_EN_REG : 1;
		unsigned MPLLA_CLK_EN_REG : 1;
		unsigned OVRD_MPLLAB_EN : 1;
		unsigned WORD_CLK_EN_REG : 1;
		unsigned OVRD_WORD_CLK_EN : 1;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_LANE1_ANA_TX_OVRD_CLK;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MEAS_ATB_CAL_CLK_ALIGN : 1;
		unsigned OVRD_DCC_DAC_CTRL_RANGE : 1;
		unsigned DCC_DAC_CTRL_RANGE_REG : 2;
		unsigned OVRD_VREF_SEL : 1;
		unsigned VREF_SEL_REG : 1;
		unsigned FORCE_ATB_TXM : 1;
		unsigned FORCE_ATB_TXP : 1;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_LANE1_ANA_TX_MISC;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned CDR_VCO_STARTUP_CODE : 2;
		unsigned CDR_VCO_TEMP_COMP_EN : 1;
		unsigned CDR_VCO_USE_UNCAL_BIAS : 1;
		unsigned OVERRIDE_CDR_EN : 1;
		unsigned OVRD_CLK_EN : 1;
		unsigned CLK_EN_REG : 1;
		unsigned NC7 : 1;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_LANE1_ANA_RX_CLK_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned IQ_PHASE_ADJUST_REG : 5;
		unsigned OVRD_IQ_PHASE_ADJUST : 1;
		unsigned RX_LOOPBACK_CLK_REG : 1;
		unsigned OVRD_RX_LOOPBACK_CLK : 1;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_LANE1_ANA_RX_CLK_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned OVRD_WORD_CLK_EN : 1;
		unsigned WORD_CLK_EN_REG : 1;
		unsigned PHDET_ODD_REG : 1;
		unsigned PHDET_EVEN_REG : 1;
		unsigned LOS_VREF_EXT_EN : 1;
		unsigned NC7_5 : 3;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_LANE1_ANA_RX_CDR_DES;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_SLICER_CTRL_O_REG : 4;
		unsigned RX_SLICER_CTRL_E_REG : 4;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_LANE1_ANA_RX_SLC_CTRL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned OVRD_ACJT_EN : 1;
		unsigned ACJT_EN_REG : 1;
		unsigned OVRD_LOS_LFPS_EN : 1;
		unsigned LOS_LFPS_EN_REG : 1;
		unsigned OVRD_AFE_EN : 1;
		unsigned AFE_EN_REG : 1;
		unsigned AFE_CM_SEL : 2;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_LANE1_ANA_RX_PWR_CTRL1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned OVRD_DFE_EN : 1;
		unsigned DFE_EN_REG : 1;
		unsigned OVRD_DESERIAL_EN : 1;
		unsigned DESERIAL_EN_REG : 1;
		unsigned OVRD_LOOPBACK_EN : 1;
		unsigned LOOPBACK_EN_REG : 1;
		unsigned OVRD_FAST_START : 1;
		unsigned FAST_START_REG : 1;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_LANE1_ANA_RX_PWR_CTRL2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned SQ_CTRL_RESP_REG : 2;
		unsigned OVRD_SQ_CTRL_RESP : 1;
		unsigned NC4_3 : 2;
		unsigned SQ_CTRL_TRESH_REG : 1;
		unsigned OVRD_SQ_CTRL_TRESH : 1;
		unsigned AFE_LOOPBACK_SEL : 1;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_LANE1_ANA_RX_SQ;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DFE_TAPS_EN_REG : 1;
		unsigned OVRD_DFE_TAPS_EN : 1;
		unsigned CAL_MUXB_SEL_REG : 5;
		unsigned OVRD_CAL_MUXB_SEL : 1;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_LANE1_ANA_RX_CAL1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned AFE_PD_EQ_OFFSET : 1;
		unsigned CAL_IDACS_USE_UNCAL : 1;
		unsigned CAL_MUXA_SEL_REG : 5;
		unsigned OVRD_CAL_MUXA_SEL : 1;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_LANE1_ANA_RX_CAL2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned OVERRIDE_REGREF_VCO : 1;
		unsigned OVERRIDE_REGREF_CLK : 1;
		unsigned OVERRIDE_REGREF_IQC : 1;
		unsigned BOOST_REGREF_IQC : 2;
		unsigned OVRD_RX_SLICER_CTRL : 1;
		unsigned OVRD_RX_TERM_GD_EN : 1;
		unsigned RX_TERM_GD_EN_REG : 1;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_LANE1_ANA_RX_ATB_REGREF;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MASTER_ATB_EN : 1;
		unsigned MEAS_ATB_VP : 1;
		unsigned MEAS_ATB_GD : 1;
		unsigned MEAS_ATB_VREG_VCO : 1;
		unsigned MEAS_ATB_VREG_CLK : 1;
		unsigned MEAS_ATB_VREG_IQC : 1;
		unsigned NC7_6 : 2;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_LANE1_ANA_RX_ATB_MEAS1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MEAS_ATB_RX : 7;
		unsigned NC7_6 : 1;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_LANE1_ANA_RX_ATB_MEAS2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MEAS_ATB_CDR_VCO_GD : 1;
		unsigned MEAS_ATB_CDR_VCO_VIREF_200U : 1;
		unsigned MEAS_ATB_VIBIAS_CDR_VCO : 1;
		unsigned MEAS_ATB_CDR_VCO_VOSC : 1;
		unsigned MEAS_ATB_CAL_MUX : 3;
		unsigned NC7 : 1;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_LANE1_ANA_RX_ATB_MEAS3;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MEAS_ATB_CAL_VREF : 7;
		unsigned NC7 : 1;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_LANE1_ANA_RX_ATB_MEAS4;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned FRC_ATB_CAL_VREF : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_LANE1_ANA_RX_ATB_FRC;
