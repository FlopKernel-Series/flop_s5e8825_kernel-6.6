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
		unsigned PSTATE : 2;
		unsigned LPD : 1;
		unsigned WIDTH : 2;
		unsigned RATE : 3;
		unsigned MPLLB_SEL : 1;
		unsigned MPLL_EN : 1;
		unsigned OVRD_EN : 1;
		unsigned MSTR_MPLLA_STATE : 1;
		unsigned MSTR_MPLLB_STATE : 1;
		unsigned MSTR_MPLL_OVRD_EN : 1;
		unsigned TX_ASYNC_EN_OVR_VAL : 1;
		unsigned TX_ASYNC_EN_OVR_EN : 1;
	} b;
} CR_RAWLANE1_DIG_PCS_XF_TX_OVRD_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RESET_OVRD_VAL : 1;
		unsigned RESET_OVRD_EN : 1;
		unsigned REQ_OVRD_VAL : 1;
		unsigned REQ_OVRD_EN : 1;
		unsigned DETRX_REQ_OVRD_VAL : 1;
		unsigned DETRX_REQ_OVRD_EN : 1;
		unsigned VBOOST_EN_OVRD_VAL : 1;
		unsigned VBOOST_EN_OVRD_EN : 1;
		unsigned IBOOST_LVL_OVRD_VAL : 4;
		unsigned IBOOST_LVL_OVRD_EN : 1;
		unsigned TX_BEACON_EN_OVR_VAL : 1;
		unsigned TX_BEACON_EN_OVR_EN : 1;
		unsigned RESERVED_15_15 : 1;
	} b;
} CR_RAWLANE1_DIG_PCS_XF_TX_OVRD_IN_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RESET : 1;
		unsigned REQ : 1;
		unsigned PSTATE : 2;
		unsigned LPD : 1;
		unsigned WIDTH : 2;
		unsigned RATE : 3;
		unsigned MPLLB_SEL : 1;
		unsigned MPLL_EN : 1;
		unsigned MSTR_MPLLA_STATE : 1;
		unsigned MSTR_MPLLB_STATE : 1;
		unsigned DETRX_REQ : 1;
		unsigned RESERVED_15_15 : 1;
	} b;
} CR_RAWLANE1_DIG_PCS_XF_TX_PCS_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned ACK : 1;
		unsigned DETRX_RESULT : 1;
		unsigned EN_CTL : 1;
		unsigned RESERVED_15_3 : 13;
	} b;
} CR_RAWLANE1_DIG_PCS_XF_TX_OVRD_OUT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned ACK : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_PCS_XF_TX_PCS_OUT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RATE : 2;
		unsigned WIDTH : 2;
		unsigned PSTATE : 2;
		unsigned LPD : 1;
		unsigned OVRD_EN : 1;
		unsigned ADAPT_AFE_EN : 1;
		unsigned ADAPT_DFE_EN : 1;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_RAWLANE1_DIG_PCS_XF_RX_OVRD_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RESET_OVRD_VAL : 1;
		unsigned RESET_OVRD_EN : 1;
		unsigned REQ_OVRD_VAL : 1;
		unsigned REQ_OVRD_EN : 1;
		unsigned RX_LOS_THRSHLD_OVRD_VAL : 3;
		unsigned RX_LOS_THRSHLD_OVRD_EN : 1;
		unsigned ADAPT_REQ : 1;
		unsigned ADAPT_REQ_OVRD_EN : 1;
		unsigned ADAPT_CONT : 1;
		unsigned OFFCAN_CONT : 1;
		unsigned CONT_OVRD_EN : 1;
		unsigned RESERVED_15_13 : 3;
	} b;
} CR_RAWLANE1_DIG_PCS_XF_RX_OVRD_IN_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned VCO_LD_VAL_OVRD : 13;
		unsigned VCO_LD_VAL_OVRD_EN : 1;
		unsigned VCO_LOWFREQ_VAL_OVRD : 1;
		unsigned VCO_LOWFREQ_VAL_OVRD_EN : 1;
	} b;
} CR_RAWLANE1_DIG_PCS_XF_RX_OVRD_IN_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned REF_LD_VAL_OVRD : 7;
		unsigned REF_LD_VAL_OVRD_EN : 1;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_RAWLANE1_DIG_PCS_XF_RX_OVRD_IN_3;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned REQ : 1;
		unsigned RATE : 2;
		unsigned WIDTH : 2;
		unsigned PSTATE : 2;
		unsigned LPD : 1;
		unsigned CDR_VCO_LOWFREQ : 1;
		unsigned ADAPT_AFE_EN : 1;
		unsigned ADAPT_DFE_EN : 1;
		unsigned ADAPT_REQ : 1;
		unsigned ADAPT_CONT : 1;
		unsigned OFFCAN_CONT : 1;
		unsigned RESET : 1;
		unsigned RESERVED_15_15 : 1;
	} b;
} CR_RAWLANE1_DIG_PCS_XF_RX_PCS_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned REF_LD_VAL : 7;
		unsigned RESERVED_15_7 : 9;
	} b;
} CR_RAWLANE1_DIG_PCS_XF_RX_PCS_IN_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned VCO_LD_VAL : 13;
		unsigned RESERVED_15_13 : 3;
	} b;
} CR_RAWLANE1_DIG_PCS_XF_RX_PCS_IN_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned EQ_ATT_LVL : 3;
		unsigned EQ_VGA1_GAIN : 4;
		unsigned EQ_VGA2_GAIN : 4;
		unsigned EQ_CTLE_BOOST : 5;
	} b;
} CR_RAWLANE1_DIG_PCS_XF_RX_PCS_IN_3;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned EQ_CTLE_POLE : 3;
		unsigned EQ_DFE_TAP1 : 8;
		unsigned RESERVED_15_11 : 5;
	} b;
} CR_RAWLANE1_DIG_PCS_XF_RX_PCS_IN_4;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned ACK : 1;
		unsigned EN_CTL : 1;
		unsigned RESERVED_15_2 : 14;
	} b;
} CR_RAWLANE1_DIG_PCS_XF_RX_OVRD_OUT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned ACK : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_PCS_XF_RX_PCS_OUT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_ADAPT_ACK : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_PCS_XF_RX_ADAPT_ACK;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_ADAPT_FOM : 8;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_RAWLANE1_DIG_PCS_XF_RX_ADAPT_FOM;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_TXPRE_DIR : 2;
		unsigned RESERVED_15_2 : 14;
	} b;
} CR_RAWLANE1_DIG_PCS_XF_RX_TXPRE_DIR;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_TXMAIN_DIR : 2;
		unsigned RESERVED_15_2 : 14;
	} b;
} CR_RAWLANE1_DIG_PCS_XF_RX_TXMAIN_DIR;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_TXPOST_DIR : 2;
		unsigned RESERVED_15_2 : 14;
	} b;
} CR_RAWLANE1_DIG_PCS_XF_RX_TXPOST_DIR;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned LANE_NUMBER : 4;
		unsigned RESERVED_15_4 : 12;
	} b;
} CR_RAWLANE1_DIG_PCS_XF_LANE_NUMBER;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned LANE_XCVR_MODE_OVRD_VAL : 2;
		unsigned LANE_XCVR_MODE_OVRD_EN : 1;
		unsigned RESERVED_15_3 : 13;
	} b;
} CR_RAWLANE1_DIG_PCS_XF_LANE_XCVR_MODE_OVRD_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned LANE_XCVR_MODE : 2;
		unsigned RESERVED_15_2 : 14;
	} b;
} CR_RAWLANE1_DIG_PCS_XF_LANE_XCVR_MODE_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_RESET_ATE_OVRD_VAL : 1;
		unsigned RX_RESET_ATE_OVRD_EN : 1;
		unsigned TX_RESET_ATE_OVRD_VAL : 1;
		unsigned TX_RESET_ATE_OVRD_EN : 1;
		unsigned RX_REQ_ATE_OVRD_VAL : 1;
		unsigned RX_REQ_ATE_OVRD_EN : 1;
		unsigned TX_REQ_ATE_OVRD_VAL : 1;
		unsigned TX_REQ_ATE_OVRD_EN : 1;
		unsigned RX_ADAPT_AFE_EN_OVRD_VAL : 1;
		unsigned RX_ADAPT_AFE_EN_OVRD_EN : 1;
		unsigned RX_ADAPT_DFE_EN_OVRD_VAL : 1;
		unsigned RX_ADAPT_DFE_EN_OVRD_EN : 1;
		unsigned RESERVED_15_12 : 4;
	} b;
} CR_RAWLANE1_DIG_PCS_XF_ATE_OVRD_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_EQ_DELTA_IQ_OVRD_VAL : 4;
		unsigned RX_EQ_DELTA_IQ_OVRD_EN : 1;
		unsigned RESERVED_15_5 : 11;
	} b;
} CR_RAWLANE1_DIG_PCS_XF_RX_EQ_DELTA_IQ_OVRD_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_TERM_CTRL_OVRD_VAL : 3;
		unsigned RX_TERM_CTRL_OVRD_EN : 1;
		unsigned TX_TERM_CTRL_OVRD_VAL : 3;
		unsigned TX_TERM_CTRL_OVRD_EN : 1;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_RAWLANE1_DIG_PCS_XF_TXRX_TERM_CTRL_OVRD_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_TERM_CTRL : 3;
		unsigned TX_TERM_CTRL : 3;
		unsigned RESERVED_15_6 : 10;
	} b;
} CR_RAWLANE1_DIG_PCS_XF_TXRX_TERM_CTRL_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_CLK_EN : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_PCS_XF_RX_OVRD_OUT_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_EQ_AFE_GAIN_OVRD_VAL : 4;
		unsigned RX_EQ_ATT_LVL_OVRD_VAL : 3;
		unsigned RX_EQ_OVRD_EN : 1;
		unsigned RESERVED_15_8 : 8;
	} b;
} CR_RAWLANE1_DIG_PCS_XF_RX_EQ_OVRD_IN_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_EQ_DFE_TAP1_OVRD_VAL : 8;
		unsigned RX_EQ_CTLE_BOOST_OVRD_VAL : 5;
		unsigned RESERVED_15_13 : 3;
	} b;
} CR_RAWLANE1_DIG_PCS_XF_RX_EQ_OVRD_IN_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned PH2_CAL_ACK_VAL : 1;
		unsigned PH2_CAL_REQ_VAL : 1;
		unsigned PH2_CAL_REQ_OVRD_VAL : 1;
		unsigned RESERVED_15_3 : 13;
	} b;
} CR_RAWLANE1_DIG_PCS_XF_RX_PH2_CAL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned FSM_JMP_ADDR : 12;
		unsigned FSM_JMP_EN : 1;
		unsigned FSM_CMD_START : 1;
		unsigned FSM_OVRD_EN : 1;
		unsigned RESERVED_15_15 : 1;
	} b;
} CR_RAWLANE1_DIG_FSM_FSM_OVRD_CTL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MEM_ADDR : 16;
	} b;
} CR_RAWLANE1_DIG_FSM_MEM_ADDR_MON;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned STATE : 5;
		unsigned CMD_RDY : 1;
		unsigned ALU_OVFLW : 1;
		unsigned ALU_RES_EQ0 : 1;
		unsigned WAIT_CNT_EQ0 : 1;
		unsigned WRMSK_DISABLED : 1;
		unsigned RDMSK_DISABLED : 1;
		unsigned RESERVED_15_11 : 5;
	} b;
} CR_RAWLANE1_DIG_FSM_STATUS_MON;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned FAST_RX_STARTUP_CAL : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_FSM_FAST_RX_STARTUP_CAL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned FAST_RX_ADAPT : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_FSM_FAST_RX_ADAPT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned FAST_RX_AFE_CAL : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_FSM_FAST_RX_AFE_CAL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned FAST_RX_DFE_CAL : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_FSM_FAST_RX_DFE_CAL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned FAST_RX_BYPASS_CAL : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_FSM_FAST_RX_BYPASS_CAL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned FAST_RX_REFLVL_CAL : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_FSM_FAST_RX_REFLVL_CAL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned FAST_RX_IQ_CAL : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_FSM_FAST_RX_IQ_CAL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned FAST_RX_AFE_ADAPT : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_FSM_FAST_RX_AFE_ADAPT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned FAST_RX_DFE_ADAPT : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_FSM_FAST_RX_DFE_ADAPT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned FAST_SUP : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_FSM_FAST_SUP;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned FAST_TX_CMN_MODE : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_FSM_FAST_TX_CMN_MODE;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned FAST_TX_RXDET : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_FSM_FAST_TX_RXDET;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned FAST_RX_PWRUP : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_FSM_FAST_RX_PWRUP;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned FAST_RX_VCO_WAIT : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_FSM_FAST_RX_VCO_WAIT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned FAST_RX_VCO_CAL : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_FSM_FAST_RX_VCO_CAL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned CMNCAL_MPLL_INIT : 1;
		unsigned CMNCAL_MPLL_DONE : 1;
		unsigned RESERVED_15_2 : 14;
	} b;
} CR_RAWLANE1_DIG_FSM_CMNCAL_MPLL_STATUS;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned FAST_RX_CONT_CAL_ADAPT : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_FSM_FAST_RX_CONT_CAL_ADAPT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned FAST_RX_CONT_ADAPT : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_FSM_FAST_RX_CONT_ADAPT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned FAST_RX_CONT_DATA_CAL : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_FSM_FAST_RX_CONT_DATA_CAL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned FAST_RX_CONT_PHASE_CAL : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_FSM_FAST_RX_CONT_PHASE_CAL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned FAST_RX_CONT_AFE_CAL : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_FSM_FAST_RX_CONT_AFE_CAL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned TX_FAST_DCC_CAL : 1;
		unsigned RX_FAST_DCC_CAL : 1;
		unsigned RX_FAST_VPHUD_CAL : 1;
		unsigned RX_FAST_VREF_CAL : 1;
		unsigned RX_FAST_SIGDET_CAL : 1;
		unsigned RESERVED_2 : 3;
		unsigned TX_FAST_CONT_DCC_CAL : 1;
		unsigned RX_FAST_CONT_DCC_CAL : 1;
		unsigned RX_FAST_CONT_VPHUD_CAL : 1;
		unsigned RX_FAST_CONT_VREF_CAL : 1;
		unsigned RESERVED_1 : 3;
		unsigned TX_SKIP_SUP_CAL : 1;
	} b;
} CR_RAWLANE1_DIG_FSM_FAST_FLAGS;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned CR_REG_LOCK : 1;
		unsigned CR_MEM_LOCK : 1;
		unsigned RESERVED_15_2 : 14;
	} b;
} CR_RAWLANE1_DIG_FSM_CR_LOCK;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RATE : 1;
		unsigned DIV : 1;
		unsigned MPLL : 1;
		unsigned RESERVED_15_3 : 13;
	} b;
} CR_RAWLANE1_DIG_FSM_TX_DCC_FLAGS;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned FLAG : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_FSM_TX_DCC_STATUS;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RESERVED : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_FSM_RESERVED;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned TX_EQ_UPDATE_FLAG : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_FSM_TX_EQ_UPDATE_FLAG;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned CMNCAL_RCAL_INIT : 1;
		unsigned CMNCAL_RCAL_DONE : 1;
		unsigned RESERVED_15_2 : 14;
	} b;
} CR_RAWLANE1_DIG_FSM_CMNCAL_RCAL_STATUS;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_IQ_PHASE_OFFSET : 4;
		unsigned RESERVED_15_4 : 12;
	} b;
} CR_RAWLANE1_DIG_FSM_RX_IQ_PHASE_OFFSET;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RESET_RTN_REQ : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_IRQ_CTL_RESET_RTN_REQ;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_RESET : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_IRQ_CTL_RX_RESET_IRQ;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_REQ : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_IRQ_CTL_RX_REQ_IRQ;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_RATE_IRQ : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_IRQ_CTL_RX_RATE_IRQ;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_PSTATE_IRQ : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_IRQ_CTL_RX_PSTATE_IRQ;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_ADAPT_REQ_IRQ : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_IRQ_CTL_RX_ADAPT_REQ_IRQ;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_ADAPT_DIS_IRQ : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_IRQ_CTL_RX_ADAPT_DIS_IRQ;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_RESET_IRQ_CLR : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_IRQ_CTL_RX_RESET_IRQ_CLR;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_REQ_IRQ_CLR : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_IRQ_CTL_RX_REQ_IRQ_CLR;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_RATE_IRQ_CLR : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_IRQ_CTL_RX_RATE_IRQ_CLR;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_PSTATE_IRQ_CLR : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_IRQ_CTL_RX_PSTATE_IRQ_CLR;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_ADAPT_REQ_IRQ_CLR : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_IRQ_CTL_RX_ADAPT_REQ_IRQ_CLR;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_ADAPT_DIS_IRQ_CLR : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_IRQ_CTL_RX_ADAPT_DIS_IRQ_CLR;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_REQ_IRQ_MSK : 1;
		unsigned RX_RATE_IRQ_MSK : 1;
		unsigned RX_PSTATE_IRQ_MSK : 1;
		unsigned RX_ADAPT_REQ_IRQ_MSK : 1;
		unsigned RX_ADAPT_DIS_IRQ_MSK : 1;
		unsigned RX_RESET_IRQ_MSK : 1;
		unsigned LANE_XCVR_MODE_IRQ_MSK : 1;
		unsigned RX_PH2_CAL_REQ_IRQ_MSK : 1;
		unsigned RX_PH2_CAL_DIS_IRQ_MSK : 1;
		unsigned LANE_RX2TX_SER_LB_EN_IRQ_MSK : 1;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_RAWLANE1_DIG_IRQ_CTL_IRQ_MASK;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned LANE_XCVR_MODE_IRQ : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_IRQ_CTL_LANE_XCVR_MODE_IRQ;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned LANE_XCVR_MODE_IRQ_CLR : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_IRQ_CTL_LANE_XCVR_MODE_IRQ_CLR;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_PH2_CAL_REQ_IRQ : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_IRQ_CTL_RX_PH2_CAL_REQ_IRQ;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_PH2_CAL_DIS_IRQ : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_IRQ_CTL_RX_PH2_CAL_DIS_IRQ;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_PH2_CAL_REQ_IRQ_CLR : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_IRQ_CTL_RX_PH2_CAL_REQ_IRQ_CLR;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_PH2_CAL_DIS_IRQ_CLR : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_IRQ_CTL_RX_PH2_CAL_DIS_IRQ_CLR;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned LANE_RX2TX_SER_LB_EN_IRQ : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_IRQ_CTL_LANE_RX2TX_SER_LB_EN_IRQ;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned LANE_RX2TX_SER_LB_EN_IRQ_CLR : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_IRQ_CTL_LANE_RX2TX_SER_LB_EN_IRQ_CLR;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned LANE_ON_DEMAND_DCC_CAL_R : 1;
		unsigned LANE_ON_DEMAND_DCC_CAL_CLR_R : 1;
		unsigned RESERVED_15_2 : 14;
	} b;
} CR_RAWLANE1_DIG_IRQ_CTL_LANE_ON_DEMAND_DCC_CAL_CTL_IRQ;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned LANE_MPLLA_EN_IN : 1;
		unsigned LANE_MPLLB_EN_IN : 1;
		unsigned LANE_OVRD_EN : 1;
		unsigned RESERVED_15_3 : 13;
	} b;
} CR_RAWLANE1_DIG_PMA_XF_LANE_OVRD_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned LANE_MPLLA_EN_OUT : 1;
		unsigned LANE_MPLLB_EN_OUT : 1;
		unsigned LANE_OVRD_EN : 1;
		unsigned RESERVED_15_3 : 13;
	} b;
} CR_RAWLANE1_DIG_PMA_XF_LANE_OVRD_OUT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLA_STATE : 1;
		unsigned MPLLB_STATE : 1;
		unsigned SUP_STATE_OVRD_EN : 1;
		unsigned RESERVED_15_3 : 13;
	} b;
} CR_RAWLANE1_DIG_PMA_XF_SUP_OVRD_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLA_STATE : 1;
		unsigned MPLLB_STATE : 1;
		unsigned RESERVED_15_2 : 14;
	} b;
} CR_RAWLANE1_DIG_PMA_XF_SUP_PMA_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned TX_REQ_OVRD_VAL : 1;
		unsigned TX_REQ_OVRD_EN : 1;
		unsigned TX_RESET_OVRD_VAL : 1;
		unsigned TX_RESET_OVRD_EN : 1;
		unsigned TX_BEACON_EN_OVRD_VAL : 1;
		unsigned TX_BEACON_EN_OVRD_EN : 1;
		unsigned TX_ASYNC_DRV_EN_OVRD_VAL : 1;
		unsigned TX_ASYNC_DRV_EN_OVRD_EN : 1;
		unsigned TX_ASYNC_EN_OVRD_VAL : 1;
		unsigned TX_ASYNC_EN_OVRD_EN : 1;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_RAWLANE1_DIG_PMA_XF_TX_OVRD_OUT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned ACK : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_PMA_XF_TX_PMA_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_REQ_OVRD_VAL : 1;
		unsigned RX_REQ_OVRD_EN : 1;
		unsigned RX_RESET_OVRD_VAL : 1;
		unsigned RX_RESET_OVRD_EN : 1;
		unsigned RESERVED_15_4 : 12;
	} b;
} CR_RAWLANE1_DIG_PMA_XF_RX_OVRD_OUT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned ACK : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_PMA_XF_RX_PMA_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned LANE_RTUNE_REQ : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_PMA_XF_LANE_RTUNE_CTL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RTUNE_ACK : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_PMA_XF_SUP_PMA_IN_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_PMA_PWM_WORD_CLK_R : 1;
		unsigned RX_PMA_PWM_WORD_CLK_OVRD_EN : 1;
		unsigned RX_PMA_PWM_DATA_R : 1;
		unsigned RX_PMA_PWM_DATA_OVRD_EN : 1;
		unsigned RX_PMA_PWM_CLK_R : 1;
		unsigned RX_PMA_PWM_CLK_OVRD_EN : 1;
		unsigned RESERVED_15_6 : 10;
	} b;
} CR_RAWLANE1_DIG_PMA_XF_MPHY_OVRD_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_PMA_PWM_EN : 1;
		unsigned RX_PMA_PWM_EN_OVRD_EN : 1;
		unsigned RX_PMA_PWM_CLK_SEL : 2;
		unsigned RX_PMA_PWM_CLK_SEL_OVRD_EN : 1;
		unsigned RX_PMA_ASYNC_EN : 1;
		unsigned RX_PMA_ASYNC_EN_OVRD_EN : 1;
		unsigned RESERVED_15_7 : 9;
	} b;
} CR_RAWLANE1_DIG_PMA_XF_MPHY_OVRD_OUT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned TX_WAIT_MPLL_OFF_TIME : 7;
		unsigned TX_P2_ALLOW_RXDET : 1;
		unsigned TX_P1_ALLOW_RXDET : 1;
		unsigned TX_P0S_ALLOW_RXDET : 1;
		unsigned TX_P0_ALLOW_RXDET : 1;
		unsigned RESERVED_15_11 : 5;
	} b;
} CR_RAWLANE1_DIG_TX_CTL_TX_FSM_CTL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned TX_CLK_EN : 1;
		unsigned TX_CLK_SEL : 4;
		unsigned ASYNC_BEACON_WAIT_TIME : 6;
		unsigned RESERVED_15_11 : 5;
	} b;
} CR_RAWLANE1_DIG_TX_CTL_TX_CLK_CTL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned ENABLE : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_TX_CTL_TX_DCC_CONT_STATUS;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned EN_RX_CTL_FSM : 1;
		unsigned RATE_CHG_IN_P1 : 1;
		unsigned RESERVED_15_2 : 14;
	} b;
} CR_RAWLANE1_DIG_RX_CTL_RX_FSM_CTL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_LOS_MASK_CNT : 9;
		unsigned RESERVED_15_9 : 7;
	} b;
} CR_RAWLANE1_DIG_RX_CTL_RX_LOS_MASK_CTL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RX_DATA_EN_OVRD_CNT : 5;
		unsigned INT_REF_TRCK_CNT : 11;
	} b;
} CR_RAWLANE1_DIG_RX_CTL_RX_DATA_EN_OVRD_CTL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned ENABLE : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_RX_CTL_OFFCAN_CONT_STATUS;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned ENABLE : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWLANE1_DIG_RX_CTL_ADAPT_CONT_STATUS;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RATE_OVRD_VAL : 2;
		unsigned RATE_OVRD_EN : 1;
		unsigned WIDTH_OVRD_VAL : 2;
		unsigned WIDTH_OVRD_EN : 1;
		unsigned PSTATE_OVRD_VAL : 2;
		unsigned PSTATE_OVRD_EN : 1;
		unsigned LPD_OVRD_VAL : 1;
		unsigned LPD_OVRD_EN : 1;
		unsigned RESERVED_15_11 : 5;
	} b;
} CR_RAWLANE1_DIG_PCS_XF_ATE_RX_OVRD_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned PSTATE : 2;
		unsigned LPD : 1;
		unsigned WIDTH : 2;
		unsigned RATE : 3;
		unsigned MPLLB_SEL : 1;
		unsigned MPLL_EN : 1;
		unsigned OVRD_EN : 1;
		unsigned MSTR_MPLLA_STATE : 1;
		unsigned MSTR_MPLLB_STATE : 1;
		unsigned MSTR_MPLL_OVRD_EN : 1;
		unsigned TX_ASYNC_EN_OVR_VAL : 1;
		unsigned TX_ASYNC_EN_OVR_EN : 1;
	} b;
} CR_RAWLANE1_DIG_PCS_XF_ATE_TX_OVRD_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DETRX_REQ_OVRD_VAL : 1;
		unsigned DETRX_REQ_OVRD_EN : 1;
		unsigned VBOOST_EN_OVRD_VAL : 1;
		unsigned VBOOST_EN_OVRD_EN : 1;
		unsigned IBOOST_LVL_OVRD_VAL : 4;
		unsigned IBOOST_LVL_OVRD_EN : 1;
		unsigned TX_BEACON_EN_OVR_VAL : 1;
		unsigned TX_BEACON_EN_OVR_EN : 1;
		unsigned RESERVED_15_11 : 5;
	} b;
} CR_RAWLANE1_DIG_PCS_XF_ATE_TX_OVRD_IN_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLB_LOOP_EN : 1;
		unsigned MPLLA_LOOP_EN : 1;
		unsigned RESERVED_15_2 : 14;
	} b;
} CR_RAWLANE1_DIG_PCS_XF_MASTER_MPLL_LOOP;
