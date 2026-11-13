/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef __SAMSUNG_DRM_H__
#define __SAMSUNG_DRM_H__

#if defined(__linux__)
#include <linux/types.h>
#endif

#if defined(__cplusplus)
extern "C" {
#endif

#define DRM_SAMSUNG_HDR_EOTF_LUT_LEN	129

/**
 * struct hdr_eotf_lut - HDR EOTF look up table to set by user-space
 *
 * @posx: x coordinate of the boundaries between segments in EOTF
 * @posy: y coordinate of the boundaries between segments in EOTF
 *
 * A hdr_eotf_lut represents a look up table of EOTF(Electro-Optical Transfer
 * Function). It is used for eotf_lut blob property of a plane object if
 * a plane supports HDR10 feature.
 */
struct hdr_eotf_lut {
	__u16 posx[DRM_SAMSUNG_HDR_EOTF_LUT_LEN];
	__u32 posy[DRM_SAMSUNG_HDR_EOTF_LUT_LEN];
};

#define DRM_SAMSUNG_HDR_OETF_LUT_LEN	33

/**
 * struct hdr_oetf_lut - HDR OETF look up table to set by user-space
 *
 * @posx: x coordinate of the boundaries between segments in OETF
 * @posy: y coordinate of the boundaries between segments in OETF
 *
 * A hdr_oetf_lut represents a look up table of OETF(Optical-Electro Transfer
 * Function). It is used for oetf_lut blob property of a plane object if
 * a plane supports HDR10 feature.
 */
struct hdr_oetf_lut {
	__u16 posx[DRM_SAMSUNG_HDR_OETF_LUT_LEN];
	__u16 posy[DRM_SAMSUNG_HDR_OETF_LUT_LEN];
};

#define DRM_SAMSUNG_HDR_GM_DIMENS	3

/**
 * struct hdr_gm_data - HDR gammut matrix data to set by user-space
 *
 * @coeffs: coefficients of a gammut matrix
 * @offsets: offsets of a gammut matrix
 *
 * A hdr_gm_data represents coefficients and offsets of a gammut matrix.
 * It is used to set a plane property for calculating a gammut matrix
 * if a plane supports HDR10 feature.
 */
struct hdr_gm_data {
	__u32 coeffs[DRM_SAMSUNG_HDR_GM_DIMENS * DRM_SAMSUNG_HDR_GM_DIMENS];
	__u32 offsets[DRM_SAMSUNG_HDR_GM_DIMENS];
};

#define DRM_SAMSUNG_HDR_TM_LUT_LEN		33

/**
 * struct hdr_tm_data - HDR tone mapping data and look up table to set
 *                      by user-space.
 *
 * @coeff_r: coefficient to be multiplied with R to convert RGB to Y
 * @coeff_g: coefficient to be multiplied with G to convert RGB to Y
 * @coeff_b: coefficient to be multiplied with B to convert RGB to Y
 * @rng_x_min: left boundary of the decreasing range of the ratio function
 *             for adaptive mixing
 * @rng_x_max: right boundary of the decreasing range of the ratio function
 *             for adaptive mixing
 * @rng_y_min: minimum ratio for adaptive mixing.
 * @rng_y_max: maximum ratio for adaptive mixing.
 * @posx: x coordinate of the boundaries between segments in tone mapping
 *        gain function.
 * @posy: y coordinate of the boundaries between segments in tone mapping
 *        gain function.
 *
 * A hdr_tm_data represents tone mapping data. It is used to set a plane
 * property for calculating tone mapping if a plane supports HDR10+ feature.
 */
struct hdr_tm_data {
	__u16 coeff_r;
	__u16 coeff_g;
	__u16 coeff_b;
	__u16 rng_x_min;
	__u16 rng_x_max;
	__u16 rng_y_min;
	__u16 rng_y_max;
	__u16 posx[DRM_SAMSUNG_HDR_TM_LUT_LEN];
	__u32 posy[DRM_SAMSUNG_HDR_TM_LUT_LEN];
};

typedef struct dpp_u32_range {
	__u32 min;
	__u32 max;
	__u32 align;
}__u32_range;

typedef struct dpu_str_u32 {
	__s8 str[32];
	__u32 val;
} __str_u32;
#define DPP_SIZE_ARG(s) s.min, s.max, s.align
struct dpp_restriction {
	__s32 id;
	__u32 port;
	__u32 dpuf_id;
	__u64 attr;

	__u32_range src_f_w;
	__u32_range src_f_h;
	__u32_range src_w;
	__u32_range src_h;
	__u32 src_x_align;
	__u32 src_y_align;

	__u32_range dst_f_w;
	__u32_range dst_f_h;
	__u32_range dst_w;
	__u32_range dst_h;
	__u32 dst_x_align;
	__u32 dst_y_align;

	__u32_range blk_w;
	__u32_range blk_h;
	__u32 blk_x_align;
	__u32 blk_y_align;

	__u32 src_w_rot_max;
	__u32 src_h_rot_max;

	__u32 scale_down;
	__u32 scale_up;

	__u32 comp_transform_support;
	__u32_range src_rgb_comp_f_w;
	__u32_range src_rgb_comp_f_h;
	__u32_range src_rgb_comp_w;
	__u32_range src_rgb_comp_h;
};

struct decon_restrict {
	__u32 id;
	__u32 disp_max_clock;
	__u32 disp_margin_pct;
	__u32 disp_factor_pct;
	__u32 ppc;
};

enum dpu_res_key {
	DPU_RES_ID,
	DPU_RES_PORT,
	DPU_RES_DPUF_ID,
	DPU_RES_ATTR,

	DPU_RES_SRC_F_W,
	DPU_RES_SRC_F_H,
	DPU_RES_SRC_W,
	DPU_RES_SRC_H,
	DPU_RES_SRC_X_ALIGN,
	DPU_RES_SRC_Y_ALIGN,
	DPU_RES_SRC_W_ROT_MAX,
	DPU_RES_SRC_H_ROT_MAX,

	DPU_RES_SRC_RGB_COMP_F_W,
	DPU_RES_SRC_RGB_COMP_W,
	DPU_RES_SRC_RGB_COMP_F_H,
	DPU_RES_SRC_RGB_COMP_H,

	DPU_RES_SRC_YUV_COMP_F_W,
	DPU_RES_SRC_YUV_COMP_W,
	DPU_RES_SRC_YUV_COMP_F_H,
	DPU_RES_SRC_YUV_COMP_H,

	DPU_RES_DST_F_W,
	DPU_RES_DST_F_H,
	DPU_RES_DST_W,
	DPU_RES_DST_H,
	DPU_RES_DST_X_ALIGN,
	DPU_RES_DST_Y_ALIGN,

	DPU_RES_BLK_W,
	DPU_RES_BLK_H,
	DPU_RES_BLK_X_ALIGN,
	DPU_RES_BLK_Y_ALIGN,

	DPU_RES_SCALE_DOWN,
	DPU_RES_SCALE_UP,

	DPU_RES_DISP_CLK_MAX,
	DPU_RES_DISP_CLK_MARGIN_PCT,
	DPU_RES_DISP_CLK_FACTOR_PCT,
	DPU_RES_DISP_CLK_PPC,

	DPU_RES_MODE_PLANE_CNT,
	DPU_RES_COMP_TRASFORM,

	DPU_RES_MIN_FRAME_INTERVAL_NS,
	DPU_RES_VRR_TIMEOUT_NS,
	DPU_RES_ESYN_PERIOD_NS,
};

enum dpu_res_type {
	DPU_RES_TYPE_S32,
	DPU_RES_TYPE_U32,
	DPU_RES_TYPE_S64,
	DPU_RES_TYPE_U64,
	DPU_RES_TYPE_U32_RANGE,
	DPU_RES_TYPE_U64_BITMASK,
	DPU_RES_TYPE_STR_U32,
};

#define DEFINE_DPU_RESTRICT(t, T)						\
struct dpu_res_##t {								\
	enum dpu_res_type	type;						\
	enum dpu_res_key	key;						\
	__##t			val;						\
};										\
static inline void dpu_res_add_##t(char **data, size_t *size,			\
				     enum dpu_res_key key, const void *val)	\
{										\
	struct dpu_res_##t *ptr = (struct dpu_res_##t *)(*data);		\
										\
	WARN(sizeof(*ptr) > *size, "failed to add restriction to blob data");	\
										\
	ptr->type = DPU_RES_TYPE_##T;						\
	ptr->key = (key);							\
	ptr->val = *(__##t *)(val);						\
	*data += sizeof(*ptr);							\
	*size -= sizeof(*ptr);							\
}
DEFINE_DPU_RESTRICT(u32, U32)
DEFINE_DPU_RESTRICT(u64, U64)
DEFINE_DPU_RESTRICT(u32_range, U32_RANGE)
DEFINE_DPU_RESTRICT(str_u32, STR_U32)


struct dpp_ch_restriction {
	__s32 id;
	__u64 attr;
	struct dpp_restriction restriction;
};

#if defined(__cplusplus)
}
#endif

#endif /* __SAMSUNG_DRM_H__ */
