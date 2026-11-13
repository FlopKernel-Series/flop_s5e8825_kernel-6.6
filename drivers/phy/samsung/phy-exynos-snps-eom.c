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

#include <linux/string.h>
#include <linux/types.h>
#include <linux/delay.h>
#include <linux/slab.h>

#include "phy-samsung-usb-cal.h"
#include "phy-exynos-snps-usbdp.h"
#include "cr.h"

#define EOF (-1)
#define PMIX_MAP_SZ 84
#define MAX_POLL_TIMEOUT 1000000

#define agr(_x, _pos) ((CR_##_x *) __cr_read(info, _x + lane, &reg))->b._pos
#define asr(_x, _pos, _value)    do { \
    ((CR_##_x *) __cr_read(info, _x + lane, &reg))->b._pos = _value; \
    phy_exynos_snps_usbdp_cr_write(info, _x + lane, reg); } while(0)

#define PHY_INFO(_X...)     printk("[dwc3_dptx] "_X)

#define WAIT_DONE						\
do {								\
	int __done = 0;						\
	int __timeout = 0;					\
	while (__done == 0 && __timeout < MAX_POLL_TIMEOUT) {\
		__done = agr(LANE1_DIG_RX_STAT_SMPL_CNT1,\
			     SMPL_CNT1_DONE);			\
		__timeout++;					\
	}							\
	if (__done == 0)					\
		PHY_INFO("%d, timeout %d\n", __LINE__, __timeout);\
} while (0)


struct scope_params {
	s64 data_rate;
	int dfe;
	int phase_step;
	int vdac_step;
	int scope_sel;
	int scope_dac_range;
	int val_plot;
	int dfe_tap1_range;
	int dfe_tap2_range;
	int dfe_vdac_range;
	int offset_correction;
	int debug;

	int *fig_composite;
	int *fig_pattern_1x;
	int *fig_pattern_0x;
	int *deb_map_table;
	int *dob_map_table;

	int stat_len;
};

struct array_3d {
	s64 *tmp;

	int x_max;
	int y_max;
	int z_max;
};

struct snps_phy_info {
	int lane;
	int scope_pmix_mapping[PMIX_MAP_SZ];

	int pmix_steps_per_ui;
	int bits_per_word;
	int xcentre;
	s64 dac_range;

	struct scope_params params;

	struct array_3d *xd_eye_vals_dfe;
	struct array_3d *d_eye_vals_dfe;

	unsigned fsm_ovrd_ctl:1;
};

static struct snps_phy_info *self;

static inline u16 *__cr_read(struct exynos_usbphy_info *info, u16 addr, u16 * data)
{
	*data = phy_exynos_snps_usbdp_cr_read(info, addr);
	return data;
}

/*************************************************************************
 * This function creates
 * pid			Part ID
 * lane 		Desired lane
 * start		initial point for dac sweep
 * dac_step 	Step size for dac steps
 * stop 		final point for dac sweep
 * first_time	reserved
 * stat_counter which stat counter used to see the data
 * scount		reserved
 * data_rate	reserved
 * bits_per_word reserved
 *************************************************************************/
static void stat_block_dac_sweep(struct exynos_usbphy_info *info, int start, int vdac_step,
				 int stop, int first_time, int stat_counter, int scount,
				 int data_rate, int bits_per_word, int *correlation, int *samples)
{
	int cnt = 0;
	u16 lane;
	u16 reg;

	lane = (info->used_phy_port == 0) ? 0x0000 : 0x0100;
	// step through the voltage settings of the VDAC (make vertical slice of the eye)
	for (int dac_code = start; dac_code <= stop; dac_code += vdac_step, cnt++) {
		// write dac_code into the DAC to set the voltage offset of the scope slicer
		// pulse enable to write in the value
		asr(LANE1_DIG_ANA_RX_DAC_CTRL_OVRD, RX_CAL_DAC_CTRL_OVRD, 0);
		asr(LANE1_DIG_ANA_RX_DAC_CTRL, RX_ANA_CAL_DAC_CTRL, dac_code);
		// pulse enable to write in the value
		asr(LANE1_DIG_ANA_RX_DAC_CTRL_OVRD, RX_CAL_DAC_CTRL_OVRD, 1);
		asr(LANE1_DIG_ANA_RX_ANA_CAL_DAC_CTRL_EN, RX_ANA_CAL_DAC_CTRL_EN, 1);

		// run stats block for N events
		// write self-clearing bit to start count
		asr(LANE1_DIG_RX_STAT_LD_VAL_1, SC1_START, 1);
		WAIT_DONE;

		samples[cnt] = agr(LANE1_DIG_RX_STAT_SMPL_CNT1, SMPL_CNT1);
		if (stat_counter == 0)
			correlation[cnt] = agr(LANE1_DIG_RX_STAT_STAT_CNT_0, STAT_CNT_0);
		else if (stat_counter == 1)
			correlation[cnt] = agr(LANE1_DIG_RX_STAT_STAT_CNT_1, STAT_CNT_1);
		else if (stat_counter == 2)
			correlation[cnt] = agr(LANE1_DIG_RX_STAT_STAT_CNT_2, STAT_CNT_2);
		else if (stat_counter == 3)
			correlation[cnt] = agr(LANE1_DIG_RX_STAT_STAT_CNT_3, STAT_CNT_3);
		else if (stat_counter == 4)
			correlation[cnt] = agr(LANE1_DIG_RX_STAT_STAT_CNT_4, STAT_CNT_4);
		else if (stat_counter == 5)
			correlation[cnt] = agr(LANE1_DIG_RX_STAT_STAT_CNT_5, STAT_CNT_5);
		else
			correlation[cnt] = agr(LANE1_DIG_RX_STAT_STAT_CNT_6, STAT_CNT_6);
	}
}

static void get_pattern_value_from_mask(int mask_value, int *mask_4_0, int *mask_19_5)
{
	*mask_4_0 = 0;
	*mask_19_5 = 0;
	*mask_4_0 = mask_value & 0x1F;
	*mask_19_5 = (mask_value & 0x0FFFE0) >> 5;
}

static struct array_3d *alloc_3d_double_array(int x, int y, int z)
{
	struct array_3d *ret;

	ret = kmalloc(sizeof(struct array_3d), GFP_KERNEL);
	ret->tmp = kcalloc(sizeof(s64), x * y * z, GFP_KERNEL);
	ret->x_max = x;
	ret->y_max = y;
	ret->z_max = z;
	return ret;
}

static void set_val_3d(struct array_3d *ptr, int x, int y, int z, s64 value)
{
	*(ptr->tmp + (x * ptr->y_max * ptr->z_max) + (y * ptr->z_max) + z) = value;
}

static s64 get_val_3d(struct array_3d *ptr, int x, int y, int z)
{
	return *(ptr->tmp + (x * ptr->y_max * ptr->z_max) + (y * ptr->z_max) + z);
}

static s64 *get_ptr_z_array(struct array_3d *ptr, int x, int y)
{
	return (ptr->tmp + (x * ptr->y_max * ptr->z_max) + (y * ptr->z_max));
}

static s64 *get_ptr_y_array(struct array_3d *ptr, int x)
{
	return (ptr->tmp + (x * ptr->y_max * ptr->z_max));
}

static void free_3d_array(struct array_3d *ptr)
{
	kfree(ptr->tmp);
	kfree(ptr);
}

static int corr[2][256] = {
	0,
};

static int samples[2][256] = {
	0,
};

int eom_run(struct exynos_usbphy_info *info)
{
	u16 reg;
	u16 lane;

	lane = (info->used_phy_port == 0) ? 0x0000 : 0x0100;	// 1, 0x0100
	int stat_len = self->params.stat_len;	// 2540
	int offset_correction = self->params.offset_correction;	// 0
	int vdac_step = self->params.vdac_step;	// 4
	int data_rate = (int)self->params.data_rate;	// 5e9
	int phase_step = self->params.phase_step;	// 4
	int dfe = self->params.dfe;	// 0

	int dfe_tap2_range = self->params.dfe_tap2_range;	// 44
	int dfe_tap1_range = self->params.dfe_tap1_range;	// 160

	int bits_per_word = self->bits_per_word;	// 19
	int pmix_steps_per_ui = self->pmix_steps_per_ui;	// 84
	int *scope_pmix_mapping = self->scope_pmix_mapping;	//int a[84];
	int xcentre = self->xcentre;	// -3
	s64 dac_range = self->dac_range;	// 550

	int debug = self->params.debug;

	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// MAKE THE SCOPE PLOT
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// [14:0] number samples per stats block run
	asr(LANE1_DIG_RX_STAT_LD_VAL_1, SC1_LD_VAL, stat_len);

	PHY_INFO("enter eom_run: offset_correction = %d, pmix_steps_per_ui = %d\n",
		offset_correction, pmix_steps_per_ui);	// 0, 84

	int offcode = 0;
	if (offset_correction == 1) {	//false
		// the pattern and pattern mask should be input as vectors
		int stat_counter = 3;
		int first_time = 1;
		int scount = 100000;

		// the pattern and pattern mask should be input as vectors
		int dec_pattern_mask_cr1a_4_0 = 7;
		int dec_pattern_mask_cr1a_19_5 = 0;
		//  [4:0]   Value of pattern A mask
		asr(LANE1_DIG_RX_STAT_MATCH_CTL0, PTTRN_MSK_CR1A_4_0, dec_pattern_mask_cr1a_4_0);
		//  *[14:0] Value of pattern A mask
		asr(LANE1_DIG_RX_STAT_MATCH_CTL3, PTTRN_MSK_CR1A_19_5, dec_pattern_mask_cr1a_19_5);

		// --------------------------------------------------
		//  find results when the current bit = 1, finds the mean of the top fuzz
		//  the pattern and pattern mask should be input as vectors
		int dec_pattern_cr1a_4_0 = 2;
		int dec_pattern_cr1a_19_5 = 0;
		// [4:0] Value of pattern A mask
		asr(LANE1_DIG_RX_STAT_MATCH_CTL0, PTTRN_CR1A_4_0, dec_pattern_cr1a_4_0);
		// [14:0]   Value of pattern A mask
		asr(LANE1_DIG_RX_STAT_MATCH_CTL2, PTTRN_CR1A_19_5, dec_pattern_cr1a_19_5);

		// run script to get a vertical strip quickly
		stat_block_dac_sweep(info, 0, vdac_step, 255, first_time, stat_counter, scount,
				     data_rate, bits_per_word, corr[1], samples[1]);
		// --------------------------------------------------
		// find results when the current bit = 0, finds the mean of the bottom fuzz
		first_time = 0;
		dec_pattern_cr1a_4_0 = 5;
		dec_pattern_cr1a_19_5 = 0;
		//   [4:0] Value of pattern A mask
		asr(LANE1_DIG_RX_STAT_MATCH_CTL0, PTTRN_CR1A_4_0, dec_pattern_cr1a_4_0);
		//   [14:0] Value of pattern A mask
		asr(LANE1_DIG_RX_STAT_MATCH_CTL2, PTTRN_CR1A_19_5, dec_pattern_cr1a_19_5);

		// run script to get a vertical strip quickly
		stat_block_dac_sweep(info, 0, vdac_step, 255, first_time, stat_counter, scount,
				     data_rate, bits_per_word, corr[0], samples[0]);

		s64 offcode_top, offcode_bot;
		int top0975 = -1, bot0975 = -1;
		int top0025 = -1, bot0025 = -1;

		for (int cnt = 0; cnt < (256 / vdac_step); cnt++) {
			s64 dac_results0, dac_results1;
			dac_results1 = (s64) corr[1][cnt] * 1000 / (s64) samples[1][cnt];
			if (dac_results1 > 25)
				top0025 = cnt;
			if (top0975 == -1 && dac_results1 < 975)
				top0975 = cnt;

			dac_results0 = (s64) corr[0][cnt] * 1000 / (s64) samples[0][cnt];
			if (bot0025 == -1 && dac_results0 > 25)
				bot0025 = cnt;
			if (dac_results0 < 975)
				bot0975 = cnt;
		}
		if (debug >= 1) {
			PHY_INFO("\nTop  First %d\n", top0975);
			PHY_INFO("\nTop  Last %d\n", top0025);
			PHY_INFO("\nBot First %d\n", bot0025);
			PHY_INFO("\nBot Last %d\n", bot0975);
		}
		offcode_top = 1000 * top0975 + 1000 * (top0025 - top0975) / 2;

		offcode_bot = 1000 * bot0025 + 1000 * (bot0975 - bot0025) / 2;
		if (debug >= 1)
			PHY_INFO("\n\nOffcode bot:%lld, top:%lld\n", offcode_bot, offcode_top);

		// matlab scripts have numerator = 256 because index starts in 1
		offcode = ((offcode_top + offcode_bot) / 2 - 1000 * 255 / vdac_step / 2) / 1000;

		if (debug >= 1)
			PHY_INFO("Offcode bot:%lld, top:%lld, avr:%d\n\n", offcode_bot, offcode_top, offcode);
	} else
		offcode = 0;
	PHY_INFO("Off code:%d\n", offcode);	// 0

	// setup the patterns based on the 'dfe' variable setting
	int pattern_mask = 0xE;
	int pattern_array[4] = { 0xC, 0x4, 0x8, 0x0 };
	int num_pattern_array = 4;
	int scount = 200000;
	int dec_pattern_mask_cr1a_4_0, dec_pattern_mask_cr1a_19_5;
	if (dfe == 0) {		// true
		// run the scope for each DFE data pattern (11X, 10X, 01X, 00X)
		pattern_mask = 0x2;
		memset(pattern_array, 0x00, sizeof(int) * 4);
		num_pattern_array = 1;
		scount = 20000;
	}
	get_pattern_value_from_mask(pattern_mask, &dec_pattern_mask_cr1a_4_0, &dec_pattern_mask_cr1a_19_5);

	dec_pattern_mask_cr1a_4_0 = 2;
	dec_pattern_mask_cr1a_19_5 = 0;
	// [4:0]    Value of pattern A mask
	asr(LANE1_DIG_RX_STAT_MATCH_CTL0, PTTRN_MSK_CR1A_4_0, dec_pattern_mask_cr1a_4_0);
	// [14:0]   Value of pattern A mask
	asr(LANE1_DIG_RX_STAT_MATCH_CTL3, PTTRN_MSK_CR1A_19_5, dec_pattern_mask_cr1a_19_5);

	// create the scope eye for each pattern (they will be combined later in the DFE eye
	int stat_counter = 3;
	int first_time = 1;
	int num_ui_in_eye = 2;
	int num_dac_steps = (256 / vdac_step) - 1;	// 63
	int num_pmix_steps = pmix_steps_per_ui * num_ui_in_eye / phase_step;	// 84*2/4 = 42
	PHY_INFO("vdac_step:%d, num_dac_steps:%d, pmix_steps_per_ui:%d, num_ui_in_eye:%d, phase_step:%d, num_pmix_steps:%d\n",
		vdac_step, num_dac_steps, pmix_steps_per_ui, num_ui_in_eye, phase_step, num_pmix_steps);	// 4, 63, 84, 2, 4, 42

	int *correlation6;
	struct array_3d *m_eye_vals;
	struct array_3d *d_eye_vals;
	struct array_3d *xd_eye_vals;
	int corr6_cnt, pmix_cnt;

	// correlation6 = np.zeros(len(range(0, 255+1, vdac_step)))
	corr6_cnt = 256 / vdac_step;	// 64
	pmix_cnt = (pmix_steps_per_ui * 2 / phase_step) + 1;	// 84*2/4 + 1 = 43

	correlation6 = (int *)kcalloc(sizeof(int), corr6_cnt, GFP_KERNEL);	// 64 integers
	m_eye_vals = alloc_3d_double_array(num_pattern_array, corr6_cnt, pmix_cnt);
	d_eye_vals = alloc_3d_double_array(num_pattern_array, corr6_cnt, pmix_cnt);
	xd_eye_vals = alloc_3d_double_array(num_pattern_array, corr6_cnt, pmix_cnt);

	PHY_INFO("num_pattern_array:%d, corr6_cnt:%d, pmix_cnt:%d\n", num_pattern_array, corr6_cnt, pmix_cnt);	// 1, 64, 43
	PHY_INFO("Total size of array:%lu\n", sizeof(s64) * num_pattern_array * corr6_cnt * pmix_cnt);	// 22016 = 8 * 1 * 64 * 43

	num_dac_steps = 256 / vdac_step - 1;	// 63
	dac_range = self->params.dfe_vdac_range * 1050;	// 550 * 1050 = 577500

	for (int pattern_cnt = 0; pattern_cnt < num_pattern_array; pattern_cnt++) {	// 0
		int phase_ctr = 0;
		int pattern;
		int phase;

		pattern = pattern_array[pattern_cnt];
		// spin the PMIX back one UI to enable pattern matching
		for (phase = xcentre; phase > xcentre - pmix_steps_per_ui - phase_step; phase -= phase_step) {
			int code, mod_phase;

			mod_phase = (phase % 84 + 84) % 84;

			code = scope_pmix_mapping[mod_phase];
			// disable the scope clocks
			asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_CLK_EN, 0);
			// set initial scope phase
			asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_PHASE, code);
			// toggle clock to write pmix phase (self-clearing)
			asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_PH_CLK, 1);
			// enable the scope clocks
			asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_CLK_EN, 1);
		}
		int idx = 0;

		for (phase = xcentre - pmix_steps_per_ui; phase < xcentre + pmix_steps_per_ui + phase_step; phase += phase_step) {
		// phase = -3 - 84 = -87, phase < -3 + 84 + 4 = 85, phase_step is 4, so idx changes from 0 to 41, there are 42 loops in all.
			phase_ctr = phase_ctr + 1;

			// write phase into the PMIX
			int code, mod_phase;

			mod_phase = (phase % 84 + 84) % 84;

			code = scope_pmix_mapping[mod_phase];
			// disable the scope clocks
			asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_CLK_EN, 0);
			// set initial scope phase
			asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_PHASE, code);
			// toggle clock to write pmix phase (self-clearing)
			asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_PH_CLK, 1);
			// enable the scope clocks
			asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_CLK_EN, 1);

			// --------------------------------------------------
			// data agnostic scope
			// --------------------------------------------------
			// find results when the current bit = 1
			pattern |= (1 << 1);
			int dec_pattern_cr1a_4_0 = 2, dec_pattern_cr1a_19_5 = 0;
			get_pattern_value_from_mask(pattern, &dec_pattern_cr1a_4_0, &dec_pattern_cr1a_19_5);

			// [4:0]    Value of pattern A mask
			asr(LANE1_DIG_RX_STAT_MATCH_CTL0, PTTRN_CR1A_4_0, dec_pattern_cr1a_4_0);
			// [14:0]   Value of pattern A mask
			asr(LANE1_DIG_RX_STAT_MATCH_CTL2, PTTRN_CR1A_19_5, dec_pattern_cr1a_19_5);
			// run script to get a vertical quickly

			stat_block_dac_sweep(info, 0, vdac_step, 255, first_time, stat_counter,
					     scount, data_rate, bits_per_word, corr[1], samples[1]);
			// find results when the current bit = 0
			pattern &= ~(1 << 1);
			first_time = 0;
			dec_pattern_cr1a_4_0 = 0, dec_pattern_cr1a_19_5 = 0;
			get_pattern_value_from_mask(pattern, &dec_pattern_cr1a_4_0, &dec_pattern_cr1a_19_5);
			//dec_pattern_cr1a_4_0 = 0;
			//dec_pattern_cr1a_19_5 = 0;
			// [4:0]    Value of pattern A mask
			asr(LANE1_DIG_RX_STAT_MATCH_CTL0, PTTRN_CR1A_4_0, dec_pattern_cr1a_4_0);
			// [14:0]   Value of pattern A mask
			asr(LANE1_DIG_RX_STAT_MATCH_CTL2, PTTRN_CR1A_19_5, dec_pattern_cr1a_19_5);

			stat_block_dac_sweep(info, 0, vdac_step, 255, first_time, stat_counter,
					     scount, data_rate, bits_per_word, corr[0], samples[0]);
			if (debug >= 2)
				PHY_INFO("[Pattern_cnt %3d][Phase %3d][idx %3d]\n", pattern_cnt, phase, idx);	// [0,1,1], [-87,85,4], [0,42,1]
			//[Pattern_cnt   0][Phase -87][idx   0]
			//[Pattern_cnt   0][Phase -79][idx   2]
			//[Pattern_cnt   0][Phase  81][idx  42]
			for (int cnt = 0; cnt < (256 / vdac_step); cnt++) {	// 0, 1, 2, ... , 63
				s64 dac_results1 = (s64) corr[1][cnt] * 1000 / (s64) samples[1][cnt];
				s64 dac_results0 = (s64) corr[0][cnt] * 1000 / (s64) samples[0][cnt];
				s64 dac_results = 1000 - (1000 + dac_results0 - dac_results1) / 2;

				if (debug >= 2)
					PHY_INFO("dac_results1:%lld, dac_results0:%lld, dac_results:%lld\n",
					dac_results1, dac_results0, dac_results);	// 988, 154, 917
				//dac_results1:965, dac_results0:186, dac_results:890

				// --------------------------------------------------
				// store the correlations and generate the diff (i.e. derivative)
				// used for the eye diagram
				set_val_3d(m_eye_vals, pattern_cnt, cnt, idx, dac_results);

				if (cnt == 0)
					continue;

				set_val_3d(d_eye_vals, pattern_cnt, cnt - 1, idx, ((dac_results - offcode) - get_val_3d(m_eye_vals, pattern_cnt, cnt - 1, idx)) * -1);

				if (debug >= 2)
					PHY_INFO("get_val_3d(m_eye_vals, pattern_cnt, cnt - 1, idx): %lld, dac_results:%lld, d_eye_vals %lld\n",
						get_val_3d(m_eye_vals, pattern_cnt, cnt - 1, idx), dac_results, (dac_results - get_val_3d(m_eye_vals, pattern_cnt, cnt - 1, idx)) * -1);
						//get_val_3d(m_eye_vals, pattern_cnt, cnt - 1, idx): 890, dac_results:833, d_eye_vals 57
			}
			idx = idx + 1;
		}

		// apply the offset
		// len_array = len(correlation6)-1
		// memset(xd_eye_vals[pattern_cnt], 0x00, sizeof(s64) * num_pmix_steps * corr6_cnt);

		s64 *dest, *source;
		if (offcode > 0) {
			for (int code_offset = 0; code_offset < corr6_cnt - offcode; code_offset++) {
				for (int col = 0; col <= num_pmix_steps; col++)	//SNPS
				{	//SNPS
					PHY_INFO("code_offset< %d Col %d\n", code_offset, col);	//SNPS
					set_val_3d(xd_eye_vals, pattern_cnt, code_offset + offcode, col, get_val_3d(d_eye_vals, pattern_cnt, code_offset, col));	//SNPS
				}	//SNPS
			}
		} else if (offcode < 0) {
			for (int code_offset = -1 * offcode; code_offset < corr6_cnt; code_offset++) {
				for (int col = 0; col <= num_pmix_steps; col++)	//SNPS
				{	//SNPS
					PHY_INFO("code_offset< %d Col %d\n", code_offset, col);	//SNPS
					set_val_3d(xd_eye_vals, pattern_cnt, code_offset + offcode, col, get_val_3d(d_eye_vals, pattern_cnt, code_offset, col));	//SNPS
				}	//SNPS

			}
		} else {	// true
			dest = get_ptr_y_array(xd_eye_vals, pattern_cnt);
			source = get_ptr_y_array(d_eye_vals, pattern_cnt);
			memcpy(dest, source, sizeof(s64) * num_pmix_steps * corr6_cnt);
		}

		// spin the PMIX back to the initial location, xcentre
		for (phase = pmix_steps_per_ui + xcentre; phase > xcentre - phase_step; phase -= phase_step) {	// [80,-12,-8]
			int code, mod_phase;

			mod_phase = (phase % 84 + 84) % 84;
			code = scope_pmix_mapping[mod_phase];

			// disable the scope clocks
			asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_CLK_EN, 0);
			// set initial scope phase
			asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_PHASE, code);
			// toggle clock to write pmix phase (self-clearing)
			asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_PH_CLK, 1);
			// enable the scope clocks
			asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_CLK_EN, 1);
		}
	}

#define XD_EYE_VAL_11_POS   0
#define XD_EYE_VAL_01_POS   1
#define XD_EYE_VAL_10_POS   2
#define XD_EYE_VAL_00_POS   3
	// -----------------------------------------------------------
	// all necessary data is gathered, apply the DFE taps and create the
	// composite DFE eye diagram
	// -----------------------------------------------------------
	struct array_3d *xd_eye_vals_xx = alloc_3d_double_array(4, num_dac_steps, num_pmix_steps);
	struct array_3d *xd_eye_vals_dfe;
	struct array_3d *d_eye_vals_dfe;

	if (dfe == 1) {		// false
		int dfe_tap1_full_code = agr(LANE1_DIG_RX_ADPTCTL_DFE_TAP1_STATUS, DFE_TAP1_ADPT_CODE);
		int dfe_tap2_full_code = agr(LANE1_DIG_RX_ADPTCTL_DFE_TAP2_STATUS, DFE_TAP2_ADPT_CODE);
		int dfe_tap1_code = dfe_tap1_full_code / 64 - 64;
		int dfe_tap2_code = dfe_tap2_full_code / 32 - 64;

		if (debug >= 1)
			PHY_INFO("dfe_tap1_full_code:%d, dfe_tap2_full_code:%d, dfe_tap1_code:%d, dfe_tap2_code:%d\n",
			     dfe_tap1_full_code, dfe_tap2_full_code, dfe_tap1_code, dfe_tap2_code);
		//dfe_tap1_full_code:3847, dfe_tap2_full_code:1367, dfe_tap1_code:-4, dfe_tap2_code:-22

		s64 *dest, *source;

		// setup variables for the DFE tap values
		int mv_per_dac_step = dac_range / num_dac_steps;	// 550 / 63 = 8
		s64 dfe_tap1_mv = 1000 * dfe_tap1_code * dfe_tap1_range / 128;	// DFE tap1 range = +/-8mV    // x1 * 160 /128
		s64 dfe_tap2_mv = 1000 * dfe_tap2_code * dfe_tap2_range / 128;	// DFE tap2 range = +/-25mV   // x2 * 44 /128
		s64 tmp;
		int tap11;
		int tap01;
		if (debug >= 1)
			PHY_INFO("dfe_tap1_mv:%lld, dfe_tap2_mv:%lld, mv_per_dac_step:%d\n", dfe_tap1_mv, dfe_tap2_mv, mv_per_dac_step);
		// dfe_tap1_mv:-5000, dfe_tap2_mv:-7562, mv_per_dac_step:8

		tmp = (dfe_tap1_mv + dfe_tap2_mv) * 1000 / mv_per_dac_step;
		tap11 = tmp - tmp % 1000;
		tap11 = (tmp % 1000 > 500) ? tap11 + 1000
		    : (tmp % 1000 == 500) ? ((tap11 / 1000 % 2) ? tap11 + 1000 : tap11)
		    : tap11;
		tap11 /= 1000;
		if (debug >= 1)
			PHY_INFO("tmp:%lld, tap11:%d\n", tmp, tap11);
		// tmp:-1570, tap11:-1

		tmp = (dfe_tap1_mv - dfe_tap2_mv) * 1000 / mv_per_dac_step;
		tap01 = tmp - tmp % 1000;
		tap01 = (tmp % 1000 > 500) ? tap01 + 1000
		    : (tmp % 1000 == 500) ? ((tap01 / 1000 % 2) ? tap01 + 1000 : tap01)
		    : tap01;
		tap01 /= 1000;
		if (debug >= 1)
			PHY_INFO("tmp:%lld, tap01:%d\n", tmp, tap01);
		// tmp:320, tap01:0

		// go through each of the four patterns, apply the effective DFE action based
		// on the particular data pattern
		for (int pattern_iter = 0; pattern_iter < num_dac_steps; pattern_iter++) {	// [0, 63, 1]
			int dac_cnt, deye_cnt;
			if (pattern_iter == 0) {
				if (tap11 >= 0) {
					for (dac_cnt = 0; dac_cnt < num_dac_steps - tap11; dac_cnt++) {
						dest = get_ptr_z_array(xd_eye_vals_xx, XD_EYE_VAL_11_POS, dac_cnt);
						source = get_ptr_z_array(d_eye_vals, XD_EYE_VAL_11_POS, tap11 + dac_cnt);
						memcpy(dest, source, sizeof(s64) * num_pmix_steps);
					}
				} else {
					for (dac_cnt = -tap11, deye_cnt = 0; dac_cnt < num_dac_steps; dac_cnt++, deye_cnt++) {
						dest = get_ptr_z_array(xd_eye_vals_xx, XD_EYE_VAL_11_POS, dac_cnt);
						source = get_ptr_z_array(d_eye_vals, XD_EYE_VAL_11_POS, deye_cnt);
						memcpy(dest, source, sizeof(s64) * num_pmix_steps);
					}
				}
			} else if (pattern_iter == 1) {
				if (tap01 >= 0) {
					for (dac_cnt = 0; dac_cnt < num_dac_steps - tap01; dac_cnt++) {
						dest = get_ptr_z_array(xd_eye_vals_xx, XD_EYE_VAL_01_POS, dac_cnt);
						source = get_ptr_z_array(d_eye_vals, XD_EYE_VAL_01_POS, tap01 + dac_cnt);
						memcpy(dest, source, sizeof(s64) * num_pmix_steps);
					}
				} else {
					for (dac_cnt = -tap01, deye_cnt = 0; dac_cnt < num_dac_steps; dac_cnt++, deye_cnt++) {
						dest = get_ptr_z_array(xd_eye_vals_xx, XD_EYE_VAL_01_POS, dac_cnt);
						source = get_ptr_z_array(d_eye_vals, XD_EYE_VAL_01_POS, deye_cnt);
						memcpy(dest, source, sizeof(s64) * num_pmix_steps);
					}
				}
			} else if (pattern_iter == 2) {
				if (tap01 >= 0) {
					for (dac_cnt = tap01, deye_cnt = 0; dac_cnt < num_dac_steps; dac_cnt++, deye_cnt++) {
						dest = get_ptr_z_array(xd_eye_vals_xx, XD_EYE_VAL_10_POS, dac_cnt);
						source = get_ptr_z_array(d_eye_vals, XD_EYE_VAL_10_POS, deye_cnt);
						memcpy(dest, source, sizeof(s64) * num_pmix_steps);
					}
				} else {
					for (dac_cnt = -tap01, deye_cnt = 0;
					     dac_cnt < num_dac_steps; dac_cnt++, deye_cnt++) {
						dest = get_ptr_z_array(xd_eye_vals_xx, XD_EYE_VAL_10_POS, dac_cnt);
						source = get_ptr_z_array(d_eye_vals, XD_EYE_VAL_10_POS, deye_cnt);
						memcpy(dest, source, sizeof(s64) * num_pmix_steps);
					}
				}
			} else if (pattern_iter == 3) {
				if (tap11 >= 0) {
					for (dac_cnt = tap11, deye_cnt = 0; dac_cnt < num_dac_steps; dac_cnt++, deye_cnt++) {
						dest = get_ptr_z_array(xd_eye_vals_xx, XD_EYE_VAL_00_POS, dac_cnt);
						source = get_ptr_z_array(d_eye_vals, XD_EYE_VAL_00_POS, deye_cnt);
						memcpy(dest, source, sizeof(s64) * num_pmix_steps);
					}
				} else {
					for (dac_cnt = -tap11, deye_cnt = 0; dac_cnt < num_dac_steps; dac_cnt++, deye_cnt++) {
						dest = get_ptr_z_array(xd_eye_vals_xx, XD_EYE_VAL_00_POS, dac_cnt);
						source = get_ptr_z_array(d_eye_vals, XD_EYE_VAL_00_POS, deye_cnt);
						memcpy(dest, source, sizeof(s64) * num_pmix_steps);
					}
				}
			}
		}
		xd_eye_vals_dfe = alloc_3d_double_array(num_pattern_array, corr6_cnt, pmix_cnt);

		for (int cnt = 0; cnt < 4; cnt++) {
			dest = get_ptr_y_array(xd_eye_vals_dfe, cnt);
			source = get_ptr_y_array(xd_eye_vals_xx, cnt);
			memcpy(dest, source, sizeof(s64) * corr6_cnt * pmix_cnt);
		}

		d_eye_vals_dfe = alloc_3d_double_array(1, corr6_cnt, pmix_cnt);
		for (int tmp_corr6_cnt = 0; tmp_corr6_cnt < corr6_cnt; tmp_corr6_cnt++) {
			for (int tmp_pmix_cnt = 0; tmp_pmix_cnt < pmix_cnt; tmp_pmix_cnt++) {
				s64 tmp_d_eye_vals_dfe = 0;
				for (int cnt = 0; cnt < 4; cnt++) {
					tmp_d_eye_vals_dfe += get_val_3d(xd_eye_vals_xx, cnt, tmp_corr6_cnt, tmp_pmix_cnt);
				}
				tmp_d_eye_vals_dfe *= 1000;
				tmp_d_eye_vals_dfe /= 4;
				set_val_3d(d_eye_vals_dfe, 0, tmp_corr6_cnt, tmp_pmix_cnt, tmp_d_eye_vals_dfe);
			}
		}
	} else {		// true
		s64 *dest, *source;

		xd_eye_vals_dfe = alloc_3d_double_array(1, corr6_cnt, pmix_cnt);
		d_eye_vals_dfe = alloc_3d_double_array(1, corr6_cnt, pmix_cnt);

		dest = get_ptr_y_array(xd_eye_vals_dfe, 0);
		source = get_ptr_y_array(xd_eye_vals, 0);
		memcpy(dest, source, sizeof(s64) * corr6_cnt * pmix_cnt);

		dest = get_ptr_y_array(d_eye_vals_dfe, 0);
		source = get_ptr_y_array(xd_eye_vals, 0);
		memcpy(dest, source, sizeof(s64) * corr6_cnt * pmix_cnt);
	}

	for (int pattern_iter = 0; pattern_iter < num_pattern_array; pattern_iter++) {
		s64 max_val = 0;

		for (int k = 0; k < corr6_cnt; k++) {
			for (int i = 0; i < pmix_cnt; i++) {
				if (get_val_3d(xd_eye_vals_dfe, pattern_iter, k, i) < 0)
					set_val_3d(xd_eye_vals_dfe, pattern_iter, k, i, 0);
				if (max_val > get_val_3d(xd_eye_vals_dfe, pattern_iter, k, i))
					continue;
				max_val = get_val_3d(xd_eye_vals_dfe, pattern_iter, k, i);
			}
		}
		for (int k = 0; k < corr6_cnt; k++) {
			for (int i = 0; i < pmix_cnt; i++) {
				s64 tmp;

				tmp = get_val_3d(xd_eye_vals_dfe, pattern_iter, k, i);
				tmp *= (256 * 1000);
				tmp /= max_val;
				set_val_3d(xd_eye_vals_dfe, pattern_iter, k, i, tmp);
			}
		}
	}

	s64 max_val = 0;
	for (int k = 0; k < corr6_cnt; k++) {
		for (int i = 0; i < pmix_cnt; i++) {
			if (get_val_3d(d_eye_vals_dfe, 0, k, i) < 0)
				set_val_3d(d_eye_vals_dfe, 0, k, i, 0);
			if (max_val > get_val_3d(d_eye_vals_dfe, 0, k, i))
				continue;
			max_val = get_val_3d(d_eye_vals_dfe, 0, k, i);
		}
	}

	for (int i = 0; i < pmix_cnt; i++) {
		for (int k = 0; k < corr6_cnt; k++) {
			s64 tmp;

			tmp = get_val_3d(d_eye_vals_dfe, 0, k, i);
			tmp *= (256 * 1000);
			tmp /= max_val;
			set_val_3d(d_eye_vals_dfe, 0, k, i, tmp);

			PHY_INFO("dEyeValsDfe %lld\n", tmp);
		}
		PHY_INFO("dEyeValsDfe END_OF_LINE\n");
		// PHY_INFO("\n");
	}
	PHY_INFO("\n");
	PHY_INFO("-----END_OF_EOM-----\n");

	kfree(correlation6);
	free_3d_array(m_eye_vals);
	free_3d_array(d_eye_vals);
	free_3d_array(xd_eye_vals);
	free_3d_array(d_eye_vals_dfe);
	free_3d_array(xd_eye_vals_dfe);
	free_3d_array(xd_eye_vals_xx);

	kfree(self);
	self = NULL;
	return 0;
}

#define CORR_ALIGN_VAL 750

int eom_init(struct exynos_usbphy_info *info, char *speed)
{
	u16 lane;
	u16 reg;

	lane = (info->used_phy_port == 0) ? 0x0000 : 0x0100;
	PHY_INFO("info->used_phy_port = %d, lane = 0x%04x\n", info->used_phy_port, lane);	// 1, 0x0100 or 0, 0x0000

	if (!self) {		// true
		int cnt1, cnt2;

		self = kmalloc(sizeof(struct snps_phy_info), GFP_KERNEL);
		/* Set-up scope data */
		for (cnt1 = 0; cnt1 < 6; cnt1++) {
			for (cnt2 = 0; cnt2 < 14; cnt2++) {
				self->scope_pmix_mapping[cnt1 * 14 + cnt2] = (cnt2 < 7) ? cnt2 : 14 - cnt2;
			}
		}
		for (cnt1 = 0; cnt1 < 84; cnt1++) {
			self->scope_pmix_mapping[cnt1] = 16 * (int)(cnt1 / 7) + 2 * (self->scope_pmix_mapping[cnt1]);
		}

		if (!strcmp(speed, "g2") || !strcmp(speed, "gen2")) {	// usb gen2 10Gbps test
			self->params.data_rate = 10e9;
		} else {
			self->params.data_rate = 5e9;	// usb gen1 5Gbps test
		}

		self->params.dfe = 0;	// not support
		self->params.phase_step = 2;	// number of PMIX steps per iteration (horizontal step size)
		self->params.vdac_step = 4;	// number of VDAC steps per iteration (vertical step size)
		self->params.scope_sel = 1;	// scope_sel - 0 for scope at ATT output, 1 for scope at CTLE output
		// ■ 00 - AFE scope selected
		// ■ 01 - DFE even scope selected
		// ■ 10 - DFE odd scope selected
		// ■ 11 - DFE bypass/AFE buffer scope selected
		self->params.scope_dac_range = 2;	// scope_dac_range - 1=+/-130mV, 2=+/-260mV, 3=+/-300mV
		self->params.val_plot = 1;	// val_plot: 0=no plotting, 1=composite DFE eye only, 2=all DFE eyes

		self->params.dfe_tap1_range = 160;
		self->params.dfe_tap2_range = 44;
		self->params.dfe_vdac_range = 550;
		self->params.offset_correction = 0;	// default:0 , 1: tuning (not support)
		self->params.stat_len = 16000;
		self->params.debug = 0;	// PHY_INFO print level. 0: disable; 1:debug; 2:verbose
	} else {
		if (self->xd_eye_vals_dfe)
			free_3d_array(self->xd_eye_vals_dfe);
		if (self->d_eye_vals_dfe)
			free_3d_array(self->d_eye_vals_dfe);
	}
	self->xd_eye_vals_dfe = NULL;
	self->d_eye_vals_dfe = NULL;

	int stat_len = self->params.stat_len;
	int debug = self->params.debug;
	int *scope_pmix_mapping = self->scope_pmix_mapping;

	/* Disable FIRMWARE */
	self->fsm_ovrd_ctl = agr(RAWLANE1_DIG_FSM_FSM_OVRD_CTL, FSM_OVRD_EN);
	asr(RAWLANE1_DIG_FSM_FSM_OVRD_CTL, FSM_OVRD_EN, 1);

	asr(LANE1_ANA_RX_ATB_REGREF, BOOST_REGREF_IQC, 0x3);

	/* determine the number of PMIX steps per UI based on the rx_rate setting
	   -if the VCO clock is divided in ckdrv then the scope PMIX will have to
	   take more steps to traverse a single UI
	 */
	int rate_rx = 0;
	int pmix_steps_per_ui = 0;

	if (agr(LANE1_DIG_ASIC_RX_OVRD_IN_0, RATE_OVRD_EN) == 1) {	// agr value is 0
		// PHY_INFO("ovrd_rate_rx = %d\n", agr(LANE1_DIG_ASIC_RX_OVRD_IN_0, RATE_OVRD_EN));
		rate_rx = agr(LANE1_DIG_ASIC_RX_OVRD_IN_0, RATE);
	} else {
		rate_rx = agr(LANE1_DIG_ASIC_RX_ASIC_IN_0, RATE);	// true
	}
	if (debug >= 1)
		PHY_INFO("rate_rx = %d\n", rate_rx);	// 1

	if (rate_rx == 0) {
		pmix_steps_per_ui = 42;
	} else if (rate_rx == 1) {	// true
		pmix_steps_per_ui = 42 * 2;	// 84
		self->params.phase_step = 2 * self->params.phase_step;	// 4
	} else {
		pmix_steps_per_ui = 42 * 4;
		self->params.phase_step = 4 * self->params.phase_step;
	}

	// select proper correction dac
	int scope_dac_range = self->params.scope_dac_range;	// 2
	s64 dac_range = 0;
	// TODO: Check Proper value, python script fix vlaue(24), but original matlab value is choosed by dac_range
	int correction_dac = 0;

	// enable the DAC override, need to de-assert this at the end
	asr(LANE1_DIG_ANA_RX_DAC_CTRL_OVRD, RX_CAL_DAC_CTRL_OVRD, 1);
	correction_dac = 24;

	if (scope_dac_range == 1) {
		// +/-140mV, dac for extra-large range
		dac_range = (self->params.dfe_vdac_range * 1075) / 2;
	} else if (scope_dac_range == 2) {	// true
		dac_range = (self->params.dfe_vdac_range) * 1050;	// 550 * 1050 = 577500
	} else {
		// +/-300mV, dac for extra-large range
		dac_range = self->params.dfe_vdac_range * 1075;
	}
	if (debug >= 1) {
		PHY_INFO("scope_dac_range = %d, self->params.dfe_vdac_range = %d, dac_range = %lld\n",
			scope_dac_range, self->params.dfe_vdac_range, dac_range);	// 2, 550, 577500
	}
	asr(LANE1_DIG_ANA_RX_DAC_CTRL_SEL, RX_ANA_CAL_DAC_CTRL_SEL, 23);
	asr(LANE1_DIG_ANA_RX_DAC_CTRL, RX_ANA_CAL_DAC_CTRL, scope_dac_range);
	// pulse enable to write in the value
	asr(LANE1_DIG_ANA_RX_ANA_CAL_DAC_CTRL_EN, RX_ANA_CAL_DAC_CTRL_EN, 1);

	// if ATT is selected force dfe=0
	if (self->params.scope_sel == 0) {
		// scope slicer after ATT - can't do the DFE eye at the ATT output
		self->params.dfe = 0;
	} else if (self->params.scope_sel == 1) {	// true
		// scope slicer after CTLE
	} else {
		PHY_INFO("scope_sel must be 0:att or 1:ctle");
		return -1;
	}

	// set to scope DAC to mid-code, 0V_diff
	asr(LANE1_DIG_ANA_RX_DAC_CTRL_SEL, RX_ANA_CAL_DAC_CTRL_SEL, correction_dac);
	asr(LANE1_DIG_ANA_RX_DAC_CTRL, RX_ANA_CAL_DAC_CTRL, 128);
	// pulse enable to write in the value
	asr(LANE1_DIG_ANA_RX_ANA_CAL_DAC_CTRL_EN, RX_ANA_CAL_DAC_CTRL_EN, 1);
	// turn on the scope clocks and select the right scope slicer
	// 2'b00 - AFE, 2'b01 DFE even, 2'b10 reserved, 2'b11 reserved
	asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_SEL, self->params.scope_sel);
	asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_CLK_EN, 1);	// enable the scope clocks
	asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_EN, 1);	// turn on scope slicer

	/////////////////////////////////////////////////
	//  SETUP THE STATS BLOCK FOR THE SCOPE
	//  setup_stats_block_gen_gen2.m file
	/////////////////////////////////////////////////
	int sc1_ld_val = stat_len;	// the max ld_val is 32767=(2^15)-1
	// all bits = 1048575, calibration comparator=1 (only one bit);
	// int pattern_cr1a[5] = { 0, }; // no masking
	// int pattern_mask_cr1a[5] = { 0, }; // no masking
	// int pattern_cr1b[5] = { 0, };
	// int pattern_mask_cr1b[5] = { 0, };
	int pattern_cr1b_en = 0;
	int pattern_cr1a_adapt_en = 0;	// disable ORing of adapation pattern with pattern CR1A
	// (only using stats_block)
	int skip_en = 0;
	int sc_timer_mode = 0;	// 0=samples, 1=timer
	int stat_rxclk_sel = 1;	// clk_sel: Select stat clock (0=ref_range_clk,1=rx_dig_clk) (0 for CAL_COMP, 1 for using SLICERS)
	int stat_src_sel = 4;	// stat_src_sel: stat source input (0=cal,  1=sc, 2=ph,  3=err,  4=data,  5=phdir,  6=F)
	int stat_shft_sel = 0;	// shift: Select stat source shift value (0=N-1,1=N+1,2=N+5,3=N+11,), USAGE: 0 for
	// calibration comparator, 1 for everything else (not sure about scope)
	int corr_mode_en = 1;	// corr_en: correlation enable, 0 if just counting
	int corr_src_sel = 2;	// corr_src_sel: Select correlation input source (0=err,  1=ph,  2=sc,  3=no corr);
	int corr_shft_sel = 0;
	int corr_shft_sel_vga = 0;
	int vld_ctl = 0;
	int vld_loss_clr = 1;
	int stat_clk_en = 1;
	int sc_pause = 0;
	int stat_cnt_6_en = 1;
	int stat_cnt_5_en = 1;
	int stat_cnt_4_en = 1;
	int stat_cnt_3_en = 1;
	int stat_cnt_2_en = 1;
	int stat_cnt_1_en = 1;
	int stat_cnt_0_en = 1;
	int ref_div_cnt = 3;	// test 7
	int precharge_cnt = 1;	// test 3

	// the data mask control spans two registers, have to split it up
	// bit 0: 20'h00001->20'd1, bit 6: 20'h00040->20'd64, bit 12: 20'h01000->20'd4096,
	// bit 18: 20'h40000->20'd262144
	// all even bits: 699050,  all odd bits: 349525
	int data_mask15_0 = 0x1;
	int data_mask19_16 = 0x0;

	// the pattern and pattern mask should be input as vectors
	int dec_pattern_mask_cr1a_4_0 = 0;
	int dec_pattern_mask_cr1a_19_5 = 0;
	int dec_pattern_cr1a_4_0 = 0;
	int dec_pattern_cr1a_19_5 = 0;
	int dec_pattern_mask_cr1b_4_0 = 0;
	int dec_pattern_mask_cr1b_19_5 = 0;
	int dec_pattern_cr1b_4_0 = 0;
	int dec_pattern_cr1b_19_5 = 0;

	// the data_delay[2:0] is divided up into [2] and [1:0]
	int data_dly_sel_2 = 0;
	int data_dly_sel_1_0 = 0;

	// the scope_dly[2:0] is divided up into [2] and [1:0]
	int scope_dly_2 = 0;
	int scope_dly_1_0 = 0;

	// [15] Start sample counter #1
	asr(LANE1_DIG_RX_STAT_LD_VAL_1, SC1_START, 0);
	// [14:0]  number samples per stats block run
	asr(LANE1_DIG_RX_STAT_LD_VAL_1, SC1_LD_VAL, sc1_ld_val);
	// [15:0]   Value of data_msk_r[15:0]
	asr(LANE1_DIG_RX_STAT_DATA_MSK, DATA_MSK_15_0, data_mask15_0);
	// [13:10]  Value of data_msk_r[19:16]
	asr(LANE1_DIG_RX_STAT_MATCH_CTL0, DATA_MSK_19_16, data_mask19_16);
	// [15:14] // of clock cycle delays on scope_data_rx_clk
	asr(LANE1_DIG_RX_STAT_MATCH_CTL0, SCOPE_DLY, scope_dly_1_0);
	// [9:5]    Value of pattern A
	asr(LANE1_DIG_RX_STAT_MATCH_CTL0, PTTRN_CR1A_4_0, dec_pattern_cr1a_4_0);
	// *[14:0]  Value of pattern A
	asr(LANE1_DIG_RX_STAT_MATCH_CTL2, PTTRN_CR1A_19_5, dec_pattern_cr1a_19_5);
	// [4:0]    Value of pattern A mask
	asr(LANE1_DIG_RX_STAT_MATCH_CTL0, PTTRN_MSK_CR1A_4_0, dec_pattern_mask_cr1a_4_0);
	// *[14:0]  Value of pattern A mask
	asr(LANE1_DIG_RX_STAT_MATCH_CTL3, PTTRN_MSK_CR1A_19_5, dec_pattern_mask_cr1a_19_5);
	// *[14:0]  Value of pattern B
	asr(LANE1_DIG_RX_STAT_MATCH_CTL4, PTTRN_CR1B_19_5, dec_pattern_cr1b_19_5);
	// [10:6]   Value of pattern B
	asr(LANE1_DIG_RX_STAT_MATCH_CTL1, PTTRN_CR1B_4_0, dec_pattern_cr1b_4_0);
	// [11] Enable ORign of adaptation pattern with pattern CR1A
	asr(LANE1_DIG_RX_STAT_MATCH_CTL1, PTTRN_CR1A_ADPT_EN, pattern_cr1a_adapt_en);
	// [14:0] Value of pattern B mask
	asr(LANE1_DIG_RX_STAT_MATCH_CTL5, PTTRN_MSK_CR1B_19_5, dec_pattern_mask_cr1b_19_5);
	// [5:1]    Value of pattern B mask
	asr(LANE1_DIG_RX_STAT_MATCH_CTL1, PTTRN_MSK_CR1B_4_0, dec_pattern_mask_cr1b_4_0);
	// [0] Enable pattern B matching
	asr(LANE1_DIG_RX_STAT_MATCH_CTL1, PTTRN_CR1B_EN, pattern_cr1b_en);
	// [15] run the adaptation running every other cycle
	asr(LANE1_DIG_RX_STAT_STAT_CTL0, SKIP_EN, skip_en);
	// [14] Sample counter operation mode (0=samples, 1=timer);
	asr(LANE1_DIG_RX_STAT_STAT_CTL0, SC_TIMER_MODE, sc_timer_mode);
	// [13] Select stat clock (0=ref_range_clk,1=rx_dig_clk);
	asr(LANE1_DIG_RX_STAT_STAT_CTL0, STAT_RXCLK_SEL, stat_rxclk_sel);
	// [12:10]  stat source input (0=cal,1=sc,2=ph,3=err,4=data,5=phdir,6=F);
	asr(LANE1_DIG_RX_STAT_STAT_CTL0, STAT_SRC_SEL, stat_src_sel);
	// [9:6]    Select stat source shift value (0=N-1,1=N+1,2=N+5,3=N+11,…);
	asr(LANE1_DIG_RX_STAT_STAT_CTL0, STAT_SHFT_SEL, stat_shft_sel);
	// [5] is deselected correlators just count the stat source (no correlation);
	asr(LANE1_DIG_RX_STAT_STAT_CTL0, CORR_MODE_EN, corr_mode_en);
	// [4:3]    Select correlation input source (0=err,1=ph,2=sc,3=no corr);
	asr(LANE1_DIG_RX_STAT_STAT_CTL0, CORR_SRC_SEL, corr_src_sel);
	// [2] Select shift for phase,  0:none, 1:>>1
	asr(LANE1_DIG_RX_STAT_STAT_CTL0, CORR_SHFT_SEL, corr_shft_sel);
	// [1]  Select shift for vga correlator,  0:none, 1:>>1
	asr(LANE1_DIG_RX_STAT_STAT_CTL0, CORR_SHFT_SEL_VGA, corr_shft_sel_vga);
	// [15:14] Gating configuration of stats collection (cdr_valid & rx_valid);
	asr(LANE1_DIG_RX_STAT_STAT_CTL1, VLD_CTL, vld_ctl);
	// [13] Clearing of stats collection upon loss of valid (0=hold, 1=clear);
	asr(LANE1_DIG_RX_STAT_STAT_CTL1, VLD_LOSS_CLR, vld_loss_clr);
	// [12:11]  // of clock cycle delays on rx_data[19:0]
	asr(LANE1_DIG_RX_STAT_STAT_CTL1, DATA_DLY_SEL, data_dly_sel_1_0);
	// [10] Clock gate enable for stat clock, turns off block, saves power
	asr(LANE1_DIG_RX_STAT_STAT_CTL1, STAT_CLK_EN, stat_clk_en);
	// [9]      Pause the sample counter and stat counters
	asr(LANE1_DIG_RX_STAT_STAT_CTL1, SC_PAUSE, sc_pause);
	// Enable stat counters
	asr(LANE1_DIG_RX_STAT_STAT_CTL1, STAT_CNT_6_EN, stat_cnt_6_en);
	asr(LANE1_DIG_RX_STAT_STAT_CTL1, STAT_CNT_5_EN, stat_cnt_5_en);
	asr(LANE1_DIG_RX_STAT_STAT_CTL1, STAT_CNT_4_EN, stat_cnt_4_en);
	asr(LANE1_DIG_RX_STAT_STAT_CTL1, STAT_CNT_3_EN, stat_cnt_3_en);
	asr(LANE1_DIG_RX_STAT_STAT_CTL1, STAT_CNT_2_EN, stat_cnt_2_en);
	asr(LANE1_DIG_RX_STAT_STAT_CTL1, STAT_CNT_1_EN, stat_cnt_1_en);
	asr(LANE1_DIG_RX_STAT_STAT_CTL1, STAT_CNT_0_EN, stat_cnt_0_en);
	// [1]      // of clock cycle delays on scope_data_rx_clk, bit [2] in [2:0] bus
	asr(LANE1_DIG_RX_STAT_STAT_CTL2, SCOPE_DLY_2, scope_dly_2);
	// [0]      // of clock cycle delays on rx_data[19:0], bit [2] in [2:0] bus
	asr(LANE1_DIG_RX_STAT_STAT_CTL2, DATA_DLY_SEL_2, data_dly_sel_2);
	// [5:3]    Ref range clock count (e.g. 5'd3 = 4 ref_range cycles);
	asr(LANE1_DIG_RX_STAT_CAL_COMP_CLK_CTL, REF_DIV_CNT, ref_div_cnt);
	// [2:0]    Precharge Count (e.g. 5'd1 = 2 ref_range cycles);
	asr(LANE1_DIG_RX_STAT_CAL_COMP_CLK_CTL, PRECHRGE_CNT, precharge_cnt);

	// determine whether the PHY is in 16/20 bit mode and setup the number
	// of bits to look at accordingly

	int ovrd_width_rx = agr(LANE1_DIG_ASIC_RX_OVRD_IN_0, WIDTH_OVRD_EN);

	int width_rx, bits_per_word;
	if (ovrd_width_rx == 1) {
		width_rx = agr(LANE1_DIG_ASIC_RX_OVRD_IN_0, WIDTH);
	} else {
		width_rx = agr(LANE1_DIG_ASIC_RX_ASIC_IN_0, WIDTH);
	}

	if (width_rx == 2)
		// bits_per_word = 16;
		bits_per_word = 15;
	else if (width_rx == 3)	// true
		bits_per_word = 19;
	else if (width_rx == 1)
		bits_per_word = 10;
	else
		bits_per_word = 8;

	if (debug >= 1)
		PHY_INFO("width_rx = %d bits_per_word=%d\n", width_rx, bits_per_word);	// 3, 19

	//-------------------------------------------------------------
	// search the data_delay, data_mask and phase until the scope correlations are good
	s64 max_corr = 0;
	int flag = 0;
	int xstart = 0;
	int xstep = 4;
	int xstop = 2 * pmix_steps_per_ui;	// 168
	int phase, data_delay, xdata_mask;
	s64 corr = 0;

	if (debug >= 1) {
		PHY_INFO("xstart = %d, xstop = %d, xstep = %d\n", xstart, xstop, xstep);	//0, 168, 4
		/*
		   PHY_INFO("scope_pmix_mapping[84]: ");
		   for(int i=0; i<84; i++) {
		   PHY_INFO("%d   ", scope_pmix_mapping[i]);
		   if (i%10==0 && i>0)
		   PHY_INFO("\n");
		   }
		   PHY_INFO("\n");
		 */
		// 00 02 04 06 08 10 12 30 28 26 24
		//    22 20 18 32 34 36 38 40 42 44
		//    62 60 58 56 54 52 50 64 66 68
		//    70 72 74 76 94 92 90 88 86 84
		//    82  96  98  100 102 104 106 108 126 124
		//    122 120 118 116 114 128 130 132 134 136
		//    138 140 158 156 154 152 150 148 146 160
		//    162 164 166 168 170 172 190 188 186 184
		//    182 180 178
	}

	for (phase = xstart; phase <= xstop; phase += xstep) {

		int code = scope_pmix_mapping[(phase % 84 + 84) % 84];

		asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_CLK_EN, 0);
		// set initial scope phase
		asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_PHASE, code);
		// toggle clock to write pmix phase (self-clearing);
		asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_PH_CLK, 1);
		// enable the scope clocks
		asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_CLK_EN, 1);

		for (data_delay = 0; data_delay < 8; data_delay++) {
			// SET DATA DELAY -------------------------------------------------
			// Set the number of word clock cycle delays on rx_data[19:0].
			// ----------------------------------------------------------------
			asr(LANE1_DIG_RX_STAT_STAT_CTL1, DATA_DLY_SEL, data_delay % 4);
			asr(LANE1_DIG_RX_STAT_STAT_CTL2, DATA_DLY_SEL_2, (int)(data_delay / 4));
			// ----------------------------------------------------------------

			// DATA MASK SWEEP %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
			for (xdata_mask = 0; xdata_mask <= bits_per_word; xdata_mask++) {
				if (xdata_mask <= 15) {
					// mask data bits to only look at one bit
					asr(LANE1_DIG_RX_STAT_DATA_MSK, DATA_MSK_15_0, 1 << xdata_mask);
					// mask data bits to only look at one bit
					asr(LANE1_DIG_RX_STAT_MATCH_CTL0, DATA_MSK_19_16, 0);
				} else {
					// mask data bits to only look at one bit
					asr(LANE1_DIG_RX_STAT_DATA_MSK, DATA_MSK_15_0, 0);
					// mask data bits to only look at one bit
					asr(LANE1_DIG_RX_STAT_MATCH_CTL0, DATA_MSK_19_16, 1 << (xdata_mask - 16));
				}

				// RUN STATS BLOCK ============================================
				// Run the stats block and wait for SMPL_CNT1_DONE == 1.
				asr(LANE1_DIG_RX_STAT_LD_VAL_1, SC1_START, 1);
				// write self-clearing bit to start count
				WAIT_DONE;

				// read number of samples
				int samples = agr(LANE1_DIG_RX_STAT_SMPL_CNT1, SMPL_CNT1);
				// read current bit correlation
				int corr3 = agr(LANE1_DIG_RX_STAT_STAT_CNT_3, STAT_CNT_3);
				if (samples == 0)
					continue;
				// calculate the correlation
				corr = (s64) corr3 *1000 / (s64) samples;

				// display the progress, debug
				if (debug >= 2) {
					PHY_INFO("stage1: phase = %d\t"
						 "data_delay = %d\t"
						 "data_mask = %d\t"
						 "samples = %d, corr3 = %d\t"
						 "corr = %lld\n",
						 phase, data_delay, xdata_mask, samples, corr3, corr);
				}
/*
[  198.695481] [5:            cat: 6043] [dwc3_dptx] stage1: phase = 0	data_delay = 5	data_mask = 5	samples = 16000, corr3 = 7642	corr = 477
[  198.695772] [5:            cat: 6043] [dwc3_dptx] stage1: phase = 0	data_delay = 5	data_mask = 6	samples = 16000, corr3 = 7580	corr = 473
[  198.696062] [5:            cat: 6043] [dwc3_dptx] stage1: phase = 0	data_delay = 5	data_mask = 7	samples = 16000, corr3 = 16000	corr = 1000
[  198.696066] [5:            cat: 6043] [dwc3_dptx] correlation found, starting scope: phase = 0,data_delay = 5,data_mask = 7,corr = 1000
*/

				if (corr > max_corr) {
					max_corr = corr;
				}
				// if eye is closed we will still make some errors
				if (corr > CORR_ALIGN_VAL) {
					flag = 1;
					break;
				}
			}
			if (flag == 1) {
				break;
			}
		}
		if (flag == 1) {
			break;
		}
	}
/*
[  356.110824] [9:            cat: 7483] [dwc3_dptx] samples = 2540, corr3 = 0
[  356.110825] [9:            cat: 7483] [dwc3_dptx] stage1: phase = 164	data_delay = 7	data_mask = 17	corr = 0
[  356.111053] [9:            cat: 7483] [dwc3_dptx] samples = 2540, corr3 = 0
[  356.111054] [9:            cat: 7483] [dwc3_dptx] stage1: phase = 164	data_delay = 7	data_mask = 18	corr = 0
[  356.111055] [9:            cat: 7483] [dwc3_dptx] No corr found; max corr 0
*/
	// -------------------------------------------------------------
	// deal with outcome whether or not a correlation was found
	if (flag == 0) {
		PHY_INFO("No corr found; max corr %lld\n", max_corr);
		/* TODO: Disable DAC Override */
		return -1;
	} else {
		PHY_INFO("correlation found, starting scope: phase = %d, data_delay = %d, data_mask = %d, corr = %lld\n",
			phase, data_delay, xdata_mask, corr);	// 0, 0, 1, 924
	}	// 0, 0, 0, 902

	// -------------------------------------------------------------
	// find the centre of the eye
	// -------------------------------------------------------------
	int xcentre = 0;
	int limit_low = 0, limit_high = 0;
	for (int centre_iter = 2; centre_iter < 3; centre_iter++) {
		// walk down and find the edge of correlations
		int phase_init = phase;

		while (corr > CORR_ALIGN_VAL) {
			int code, mod_phase;

			phase = phase - 1;

			// mod_phase = ((phase < 0) ? (phase * -1) : phase) % 84;
			mod_phase = (phase % 84 + 84) % 84;	// (2^64 - 1) % 84 = 15

			code = scope_pmix_mapping[mod_phase];

			asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_CLK_EN, 0);
			// set initial scope phase
			asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_PHASE, code);
			// toggle clock to write pmix phase (self-clearing);
			asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_PH_CLK, 1);
			// enable the scope clocks
			asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_CLK_EN, 1);

			// Run the stats block and wait for SMPL_CNT1_DONE == 1.
			// write self-clearing bit to start count
			asr(LANE1_DIG_RX_STAT_LD_VAL_1, SC1_START, 1);
			WAIT_DONE;

			// read number of samples
			int samples = agr(LANE1_DIG_RX_STAT_SMPL_CNT1, SMPL_CNT1);
			// read current bit correlation
			int corr3 = agr(LANE1_DIG_RX_STAT_STAT_CNT_3, STAT_CNT_3);
			corr = (s64) corr3 *1000 / (s64) samples;	// calculate the correlation

			// below is debug, read the correlations and display
			if (debug >= 2) {
				// display the correlations to make sure we end up in a good place
				PHY_INFO("stage1(%d): code:%d phase=%03d(%03d)\t correlation=%lld (corr3 %04d / samples %04d)\n",
				     centre_iter, code, phase, mod_phase, corr, corr3, samples);
			}
/*
[   28.244761] [dwc3_dptx] stage1(2): code:34 phase=-01(015)     correlation=902 (corr3 16402 / samples 18184)
[   28.245035] [dwc3_dptx] stage1(2): code:32 phase=-02(014)     correlation=902 (corr3 16402 / samples 18184)
[   28.245303] [dwc3_dptx] stage1(2): code:18 phase=-03(013)     correlation=902 (corr3 16402 / samples 18184)
.........
[   28.284940] [dwc3_dptx] stage1(2): code:94 phase=-149(035)    correlation=902 (corr3 16402 / samples 18184)
[   28.285209] [dwc3_dptx] stage1(2): code:76 phase=-150(034)    correlation=902 (corr3 16402 / samples 18184)
[   28.285479] [dwc3_dptx] stage1(2): code:74 phase=-151(033)    correlation=902 (corr3 16402 / samples 18184)
[   28.285482] [dwc3_dptx] Error during centering. Check lane and try again
*/
			if (phase < -150) {
				PHY_INFO("Error during centering. Check lane and try again\n");
				return -1;
			}
		}
		limit_low = phase;	// -3
		// -------------------------------------------------------------

		// -------------------------------------------------------------
		// walk back to original correlation point
		if (debug >= 1) {
			PHY_INFO("stage2(%d), limit_low:%d, phase_init:%d\n", centre_iter, limit_low, phase_init);	// 2, -3, 0
		}
		for (phase = limit_low; phase < phase_init; phase++) {	// -3, -2, -1
			int code, mod_phase;

			// mod_phase = ((phase < 0) ? (phase * -1) : phase) % 84;
			mod_phase = (phase % 84 + 84) % 84;
			code = scope_pmix_mapping[mod_phase];

			asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_CLK_EN, 0);
			// set initial scope phase
			asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_PHASE, code);
			// toggle clock to write pmix phase (self-clearing);
			asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_PH_CLK, 1);
			// enable the scope clocks
			asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_CLK_EN, 1);

			// Run the stats block and wait for SMPL_CNT1_DONE == 1,
			// write self-clearing bit to start count
			// read sample counter status, wait for DONE==1
			asr(LANE1_DIG_RX_STAT_LD_VAL_1, SC1_START, 1);
			WAIT_DONE;

			// read number of samples
			int samples = agr(LANE1_DIG_RX_STAT_SMPL_CNT1, SMPL_CNT1);
			// read current bit correlation
			int corr3 = agr(LANE1_DIG_RX_STAT_STAT_CNT_3, STAT_CNT_3);

			// calculate the correlation
			corr = (s64) corr3 *1000 / (s64) samples;

			// below is debug, read the correlations and display
			if (debug >= 1) {
				// display the correlations to make sure we end up in a good place
				PHY_INFO("stage2(%d): code:%d phase=%03d(%03d)\t correlation=%lld(%04d/%04d)\n",
				     centre_iter, code, phase, mod_phase, corr, corr3, samples);
			}
		}

		//  walk up and find the edge of correlations

		while (corr > CORR_ALIGN_VAL) {
			phase = phase + 1;

			int code, mod_phase;

			mod_phase = (phase % 84 + 84) % 84;

			code = scope_pmix_mapping[mod_phase];

			asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_CLK_EN, 0);
			// set initial scope phase
			asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_PHASE, code);
			// toggle clock to write pmix phase (self-clearing);
			asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_PH_CLK, 1);
			// enable the scope clocks
			asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_CLK_EN, 1);

			// Run the stats block and wait for SMPL_CNT1_DONE == 1,
			// write self-clearing bit to start count
			asr(LANE1_DIG_RX_STAT_LD_VAL_1, SC1_START, 1);
			// read sample counter status, wait for DONE==1
			WAIT_DONE;
			// read number of samples
			int samples = agr(LANE1_DIG_RX_STAT_SMPL_CNT1, SMPL_CNT1);
			// read current bit correlation
			int corr3 = agr(LANE1_DIG_RX_STAT_STAT_CNT_3, STAT_CNT_3);

			s64 corr_old = corr;
			// calculate the correlation
			corr = (s64) corr3 *1000 / (s64) samples;
			// below is debug, read the correlations and display
			if (debug >= 2) {
				// display the correlations to make sure we end up in a good place
				PHY_INFO("stage3(%d): code:%d phase=%03d(%03d)\tcorrelation=%lld(%d/%d)\n",
				     centre_iter, code, phase, mod_phase, corr, corr3, samples);
			}
			if ((corr_old > 900) && (corr < 600)) {
				mdelay(1000);
			}
		}

		limit_high = phase;	// 0

		// -------------------------------------------------------------
		//
		// -------------------------------------------------------------
		// find the middle and walk to it
		int phase_centre = (int)((limit_low + limit_high) / 2);
		if (debug >= 1)
			PHY_INFO("stage4, limit_high:%d, phase_centre:%d\n", limit_high, phase_centre);	// 0, -1
		for (phase = limit_high; phase > phase_centre; phase--) {
			int code, mod_phase;

			mod_phase = (phase % 84 + 84) % 84;

			code = scope_pmix_mapping[mod_phase];

			asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_CLK_EN, 0);
			// set initial scope phase
			asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_PHASE, code);
			// toggle clock to write pmix phase (self-clearing);
			asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_PH_CLK, 1);
			// enable the scope clocks
			asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_CLK_EN, 1);

			// Run the stats block and wait for SMPL_CNT1_DONE == 1.
			// write self-clearing bit to start count
			asr(LANE1_DIG_RX_STAT_LD_VAL_1, SC1_START, 1);
			// read sample counter status, wait for DONE==1
			WAIT_DONE;
			// read number of samples
			int samples = agr(LANE1_DIG_RX_STAT_SMPL_CNT1, SMPL_CNT1);
			// read current bit correlation
			int corr3 = agr(LANE1_DIG_RX_STAT_STAT_CNT_3, STAT_CNT_3);
			// calculate the correlation
			corr = (s64) corr3 *1000 / (s64) samples;

			//  below is debug, read the correlations and display
			if (debug >= 2) {
				// display the correlations to make sure we end up in a good place
				PHY_INFO("stage4(%d): phase=%03d(%03d)\tcorrelation=%lld\n", centre_iter, phase, mod_phase, corr);	// 2, 0(84), 914
			}
		}

		// phase_centre = (int)mod(phase_centre, 84.0);
		phase_centre = (phase_centre % 84 + 84) % 84;

		xcentre = phase_centre;

		// -------------------------------------------------------------
		if (centre_iter == 1) {
			// -------------------------------------------------------------
			//  move data_mask away from any place where you lose correlation
			// -------------------------------------------------------------
			int align_bit, mask_incdec, phase_incdec;
			//-------------------------------------------------------------
			// walk to xdata_mask=align_bit; centres the eye in the word, makes pattern masking easier
			// determine whether to increment or decrement the data_mask and the phase mixer (they move opposite)
			if (xdata_mask < 5) {
				align_bit = 5;
				mask_incdec = +1;
				phase_incdec = -1;
			} else if (xdata_mask < 9) {
				align_bit = 5;
				mask_incdec = -1;
				phase_incdec = +1;
			} else if (xdata_mask < 12) {
				// e.g. if data_mask = 10 and we want to move to 4 we must increment the phase
				align_bit = 12;
				mask_incdec = +1;
				phase_incdec = -1;
			} else {
				// e.g. if data_mask = 10 and we want to move to 4 we must increment the phase
				align_bit = 12;
				mask_incdec = -1;
				phase_incdec = +1;
			}
			// keep walking the phase one UI at a time until the data_mask reaches the align bit
			phase = phase_centre;
			while (xdata_mask != align_bit) {
				xdata_mask = xdata_mask + mask_incdec;
				if (xdata_mask <= 15) {
					// mask data bits to only look at one bit
					asr(LANE1_DIG_RX_STAT_DATA_MSK, DATA_MSK_15_0, 1 << (xdata_mask));
					// mask data bits to only look at one bit
					asr(LANE1_DIG_RX_STAT_MATCH_CTL0, DATA_MSK_19_16, 0);
				} else {
					// mask data bits to only look at one bit
					asr(LANE1_DIG_RX_STAT_DATA_MSK, DATA_MSK_15_0, 0);
					//  mask data bits to only look at one bit
					asr(LANE1_DIG_RX_STAT_MATCH_CTL0, DATA_MSK_19_16, 1 << (xdata_mask - 16));
				}
				for (int xiter = 1; xiter <= pmix_steps_per_ui; xiter++) {
					int code, mod_phase;

					phase = phase + phase_incdec;
					mod_phase = (phase % 84 + 84) % 84;

					code = scope_pmix_mapping[mod_phase];

					asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_CLK_EN, 0);
					// set initial scope phase
					asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_PHASE, code);
					// toggle clock to write pmix phase (self-clearing);
					asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_PH_CLK, 1);
					// enable the scope clocks
					asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_CLK_EN, 1);

					// Run the stats block and wait for SMPL_CNT1_DONE == 1.
					// write self-clearing bit to start count
					asr(LANE1_DIG_RX_STAT_LD_VAL_1, SC1_START, 1);
					// read sample counter status, wait for DONE==1
					WAIT_DONE;

					// read number of samples
					int samples = agr(LANE1_DIG_RX_STAT_SMPL_CNT1, SMPL_CNT1);
					// read current bit correlation
					int corr3 = agr(LANE1_DIG_RX_STAT_STAT_CNT_3, STAT_CNT_3);
					// calculate the correlation
					corr = (s64) (corr3) * 1000 / (s64) samples;

					//  below is debug, read the correlations and display
					if (debug >= 1) {
						// display the correlations to make sure we end in a good place
						PHY_INFO("stage5(%d): data_mask=%d\tphase=%03d(%03d)\t correlation=%lld\n",
						     centre_iter, xdata_mask, phase, mod_phase, corr);
					}
				}
			}
			// phase_centre = (int)mod(phase,84.0);
			phase_centre = (phase % 84 + 84) % 84;
			//-------------------------------------------------------------

			// -------------------------------------------------------------
			// if the centre point is in the second half of the PMIX space (i.e. > 42/83 codes);
			// move back one UI (and increment the data_mask accordingly);
			phase = phase_centre;
			if (phase_centre < pmix_steps_per_ui) {
				xdata_mask = xdata_mask - 1;

				// mask data bits to only look at only lsb
				asr(LANE1_DIG_RX_STAT_DATA_MSK, DATA_MSK_15_0, 1 << (xdata_mask));
				asr(LANE1_DIG_RX_STAT_MATCH_CTL0, DATA_MSK_19_16, 0);
				for (int xiter = 1; xiter <= pmix_steps_per_ui; xiter++) {
					phase = phase + 1;

					int code, mod_phase;

					mod_phase = (phase % 84 + 84) % 84;

					code = scope_pmix_mapping[mod_phase];

					asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_CLK_EN, 0);
					// set initial scope phase
					asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_PHASE, code);
					// toggle clock to write pmix phase (self-clearing);
					asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_PH_CLK, 1);
					// enable the scope clocks
					asr(LANE1_DIG_ANA_RX_SCOPE, RX_ANA_SCOPE_CLK_EN, 1);

					// Run the stats block and wait for SMPL_CNT1_DONE == 1
					// write self-clearing bit to start count
					asr(LANE1_DIG_RX_STAT_LD_VAL_1, SC1_START, 1);
					// read sample counter status, wait for DONE==1
					WAIT_DONE;

					// read number of samples
					int samples = agr(LANE1_DIG_RX_STAT_SMPL_CNT1, SMPL_CNT1);
					// read current bit correlation

					int corr3 = agr(LANE1_DIG_RX_STAT_STAT_CNT_3, STAT_CNT_3);

					corr = (s64) corr3 *1000 / (s64) samples;	// calculate the correlation

					// below is debug, read the correlations and display
					if (debug >= 1) {
						// display the correlations to make sure we end up in a good place
						PHY_INFO("stage6(%d): data_mask=%d\tphase=%03d(%03d)\tcorrelation=%lld\n",
						     centre_iter, xdata_mask, phase, mod_phase, corr);
					}
				}
			}
			xcentre = phase;
		}
	}

	// if correlation was lost, bail out
	if (debug >= 1) {
		if (corr < CORR_ALIGN_VAL) {
			PHY_INFO("Correlation lost(%lld < 750). Re-try scope.\n", corr);
			/* TODO: Check why correlation lost */
			return -1;
		}
	}

	xcentre = phase;

	PHY_INFO("entre phase found:\t phase = %d\tdata_delay = %d\tdata_mask = %d\tcorr = %lld\n",
		xcentre, data_delay, xdata_mask, corr);	// -1, 0, 1, 914  // -4, 0, 3, 999  // -3, 5, 7, 1000

	// check which variables are needed to run scope
	self->bits_per_word = bits_per_word;
	self->pmix_steps_per_ui = pmix_steps_per_ui;
	self->xcentre = xcentre;
	self->dac_range = dac_range;
	PHY_INFO("eom_init finishes. bits_per_word=%d, pmix_steps_per_ui=%d, xcentre=%d, dac_range=%lld\n",
		bits_per_word, pmix_steps_per_ui, xcentre, dac_range);	// 19, 84, -3, 577500
	// TODO Return sucess flag and details about the initialization

	// TODO implement mechanisms to handle failure

	return 0;
}
