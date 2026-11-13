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
		unsigned PHY_FUNC_RST : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWCMN_DIG_CMN_CTL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLA_WORD_DIV2_EN_OVRD_VAL : 1;
		unsigned MPLLA_WORD_DIV2_EN_OVRD_EN : 1;
		unsigned MPLLA_TX_CLK_DIV_OVRD_VAL : 3;
		unsigned MPLLA_TX_CLK_DIV_OVRD_EN : 1;
		unsigned MPLLA_DIV10_CLK_EN_OVRD_VAL : 1;
		unsigned MPLLA_DIV10_CLK_EN_OVRD_EN : 1;
		unsigned MPLLA_DIV8_CLK_EN_OVRD_VAL : 1;
		unsigned MPLLA_DIV8_CLK_EN_OVRD_EN : 1;
		unsigned MPLLA_BW_OVRD_EN : 1;
		unsigned RESERVED_15_11 : 5;
	} b;
} CR_RAWCMN_DIG_MPLLA_OVRD_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLA_BW_OVRD_VAL : 16;
	} b;
} CR_RAWCMN_DIG_MPLLA_BW_OVRD_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLA_SSC_RANGE_OVRD_VAL : 3;
		unsigned MPLLA_SSC_RANGE_OVRD_EN : 1;
		unsigned MPLLA_SSC_CLK_SEL_OVRD_VAL : 3;
		unsigned MPLLA_SSC_CLK_SEL_OVRD_EN : 1;
		unsigned MPLLA_SSC_EN_OVRD_VAL : 1;
		unsigned MPLLA_SSC_EN_OVRD_EN : 1;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_RAWCMN_DIG_MPLLA_SSC_CTL_OVRD_IN_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLB_WORD_DIV2_EN_OVRD_VAL : 1;
		unsigned MPLLB_WORD_DIV2_EN_OVRD_EN : 1;
		unsigned MPLLB_TX_CLK_DIV_OVRD_VAL : 3;
		unsigned MPLLB_TX_CLK_DIV_OVRD_EN : 1;
		unsigned MPLLB_DIV10_CLK_EN_OVRD_VAL : 1;
		unsigned MPLLB_DIV10_CLK_EN_OVRD_EN : 1;
		unsigned MPLLB_DIV8_CLK_EN_OVRD_VAL : 1;
		unsigned MPLLB_DIV8_CLK_EN_OVRD_EN : 1;
		unsigned MPLLB_BW_OVRD_EN : 1;
		unsigned RESERVED_15_11 : 5;
	} b;
} CR_RAWCMN_DIG_MPLLB_OVRD_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLB_BW_OVRD_VAL : 16;
	} b;
} CR_RAWCMN_DIG_MPLLB_BW_OVRD_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLB_SSC_RANGE_OVRD_VAL : 3;
		unsigned MPLLB_SSC_RANGE_OVRD_EN : 1;
		unsigned MPLLB_SSC_CLK_SEL_OVRD_VAL : 3;
		unsigned MPLLB_SSC_CLK_SEL_OVRD_EN : 1;
		unsigned MPLLB_SSC_EN_OVRD_VAL : 1;
		unsigned MPLLB_SSC_EN_OVRD_EN : 1;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_RAWCMN_DIG_MPLLB_SSC_CTL_OVRD_IN_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DATA : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWCMN_DIG_LANE_FSM_OP_XTND;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLA_FRACN_CTRL_OVRD_VAL : 11;
		unsigned MPLLA_FRACN_CTRL_OVRD_EN : 1;
		unsigned RESERVED_15_12 : 4;
	} b;
} CR_RAWCMN_DIG_MPLLA_SSC_CTL_OVRD_IN_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLB_FRACN_CTRL_OVRD_VAL : 11;
		unsigned MPLLB_FRACN_CTRL_OVRD_EN : 1;
		unsigned RESERVED_15_12 : 4;
	} b;
} CR_RAWCMN_DIG_MPLLB_SSC_CTL_OVRD_IN_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLA_INIT_CAL_DISABLE_OVRD_VAL : 1;
		unsigned MPLLA_INIT_CAL_DISABLE_OVRD_EN : 1;
		unsigned MPLLB_INIT_CAL_DISABLE_OVRD_VAL : 1;
		unsigned MPLLB_INIT_CAL_DISABLE_OVRD_EN : 1;
		unsigned RTUNE_REQ_OVRD_VAL : 1;
		unsigned RTUNE_REQ_OVRD_EN : 1;
		unsigned RESERVED_15_6 : 10;
	} b;
} CR_RAWCMN_DIG_CMN_CTL_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLL_OFF_TIME : 6;
		unsigned MPLLA_STATE : 1;
		unsigned MPLLB_STATE : 1;
		unsigned MPLL_STATE_OVRD_OUT_EN : 1;
		unsigned RESERVED_15_9 : 7;
	} b;
} CR_RAWCMN_DIG_MPLL_STATE_CTL;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DATA : 4;
		unsigned RESERVED_15_4 : 12;
	} b;
} CR_RAWCMN_DIG_TX_CAL_CODE;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned DATA : 1;
		unsigned RESERVED_15_1 : 15;
	} b;
} CR_RAWCMN_DIG_SRAM_INIT_DONE;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RTUNE_RX_VAL_0 : 6;
		unsigned RESERVED_15_6 : 10;
	} b;
} CR_RAWCMN_DIG_AON_CMN_RTUNE_RX_VAL_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RTUNE_TXDN_VAL_0 : 10;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_RAWCMN_DIG_AON_CMN_RTUNE_TXDN_VAL_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RTUNE_TXUP_VAL_0 : 10;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_RAWCMN_DIG_AON_CMN_RTUNE_TXUP_VAL_0;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RTUNE_RX_VAL_1 : 6;
		unsigned RESERVED_15_6 : 10;
	} b;
} CR_RAWCMN_DIG_AON_CMN_RTUNE_RX_VAL_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RTUNE_TXDN_VAL_1 : 10;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_RAWCMN_DIG_AON_CMN_RTUNE_TXDN_VAL_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RTUNE_TXUP_VAL_1 : 10;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_RAWCMN_DIG_AON_CMN_RTUNE_TXUP_VAL_1;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RTUNE_RX_VAL_2 : 6;
		unsigned RESERVED_15_6 : 10;
	} b;
} CR_RAWCMN_DIG_AON_CMN_RTUNE_RX_VAL_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RTUNE_TXDN_VAL_2 : 10;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_RAWCMN_DIG_AON_CMN_RTUNE_TXDN_VAL_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RTUNE_TXUP_VAL_2 : 10;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_RAWCMN_DIG_AON_CMN_RTUNE_TXUP_VAL_2;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RTUNE_RX_VAL_3 : 6;
		unsigned RESERVED_15_6 : 10;
	} b;
} CR_RAWCMN_DIG_AON_CMN_RTUNE_RX_VAL_3;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RTUNE_TXDN_VAL_3 : 10;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_RAWCMN_DIG_AON_CMN_RTUNE_TXDN_VAL_3;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RTUNE_TXUP_VAL_3 : 10;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_RAWCMN_DIG_AON_CMN_RTUNE_TXUP_VAL_3;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RTUNE_RX_VAL_4 : 6;
		unsigned RESERVED_15_6 : 10;
	} b;
} CR_RAWCMN_DIG_AON_CMN_RTUNE_RX_VAL_4;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RTUNE_TXDN_VAL_4 : 10;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_RAWCMN_DIG_AON_CMN_RTUNE_TXDN_VAL_4;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RTUNE_TXUP_VAL_4 : 10;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_RAWCMN_DIG_AON_CMN_RTUNE_TXUP_VAL_4;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RTUNE_RX_VAL_5 : 6;
		unsigned RESERVED_15_6 : 10;
	} b;
} CR_RAWCMN_DIG_AON_CMN_RTUNE_RX_VAL_5;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RTUNE_TXDN_VAL_5 : 10;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_RAWCMN_DIG_AON_CMN_RTUNE_TXDN_VAL_5;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RTUNE_TXUP_VAL_5 : 10;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_RAWCMN_DIG_AON_CMN_RTUNE_TXUP_VAL_5;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RTUNE_RX_VAL_6 : 6;
		unsigned RESERVED_15_6 : 10;
	} b;
} CR_RAWCMN_DIG_AON_CMN_RTUNE_RX_VAL_6;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RTUNE_TXDN_VAL_6 : 10;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_RAWCMN_DIG_AON_CMN_RTUNE_TXDN_VAL_6;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RTUNE_TXUP_VAL_6 : 10;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_RAWCMN_DIG_AON_CMN_RTUNE_TXUP_VAL_6;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RTUNE_RX_VAL_7 : 6;
		unsigned RESERVED_15_6 : 10;
	} b;
} CR_RAWCMN_DIG_AON_CMN_RTUNE_RX_VAL_7;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RTUNE_TXDN_VAL_7 : 10;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_RAWCMN_DIG_AON_CMN_RTUNE_TXDN_VAL_7;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RTUNE_TXUP_VAL_7 : 10;
		unsigned RESERVED_15_10 : 6;
	} b;
} CR_RAWCMN_DIG_AON_CMN_RTUNE_TXUP_VAL_7;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned SRAM_PGATE_BL_EN : 1;
		unsigned SRAM_BL_ROM : 1;
		unsigned SRAM_BL_BYPASS : 1;
		unsigned SRAM_BL_START : 1;
		unsigned RESERVED_15_4 : 12;
	} b;
} CR_RAWCMN_DIG_AON_CMN_SRAM_BL_CFG;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned PMA_PWR_STABLE_OVRD : 1;
		unsigned PCS_PWR_STABLE_OVRD : 1;
		unsigned PG_RESET_OVRD_VAL : 1;
		unsigned PG_RESET_OVRD_EN : 1;
		unsigned PG_MODE_EN_OVRD_VAL : 1;
		unsigned PG_MODE_EN_OVRD_EN : 1;
		unsigned RESERVED_15_6 : 10;
	} b;
} CR_RAWCMN_DIG_AON_CMN_PG_OVRD_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned PMA_PWR_EN_OVRD : 1;
		unsigned PCS_PWR_EN_OVRD : 1;
		unsigned RESERVED_15_2 : 14;
	} b;
} CR_RAWCMN_DIG_AON_CMN_PG_OVRD_OUT;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned MPLLA_FORCE_EN_OVRD_VAL : 1;
		unsigned MPLLA_FORCE_EN_OVRD_EN : 1;
		unsigned MPLLB_FORCE_EN_OVRD_VAL : 1;
		unsigned MPLLB_FORCE_EN_OVRD_EN : 1;
		unsigned REF_CLK_EN_OVRD_VAL : 1;
		unsigned REF_CLK_EN_OVRD_EN : 1;
		unsigned RESERVED_15_6 : 10;
	} b;
} CR_RAWCMN_DIG_AON_CMN_SUP_OVRD_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned SUP_ANA_VPHUD_SELVPH : 1;
		unsigned VREF_CAL_DONE : 1;
		unsigned RESERVED_15_2 : 14;
	} b;
} CR_RAWCMN_DIG_AON_CMN_VREF_STATS;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RES_REQ_IN : 1;
		unsigned RES_ACK_IN : 1;
		unsigned RES_OVRD_EN : 1;
		unsigned RES_REQ_OUT : 1;
		unsigned RES_REQ_OUT_OVRD_EN : 1;
		unsigned RES_ACK_OUT : 1;
		unsigned RES_ACK_OUT_OVRD_EN : 1;
		unsigned RESERVED_15_7 : 9;
	} b;
} CR_RAWCMN_DIG_AON_CMN_RES_OVRD_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned RES_REQ_IN : 1;
		unsigned RES_REQ_OUT : 1;
		unsigned RES_ACK_IN : 1;
		unsigned RES_ACK_OUT : 1;
		unsigned RESERVED_15_4 : 12;
	} b;
} CR_RAWCMN_DIG_AON_CMN_RES_ASIC_IN;
typedef union {
	struct {
		u16 reg;
	} data;
	struct {
		unsigned OVRD_VAL : 5;
		unsigned OVRD_EN : 1;
		unsigned RESERVED_15_6 : 10;
	} b;
} CR_RAWCMN_DIG_AON_CMN_REF_RANGE_OVRD;
