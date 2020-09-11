/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-03
*@author : maoguangkun
*@brief : CtImShdrSet
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include <string.h>
#include <stdlib.h>

#include "ct_im_shdr.h"
#include "jdsshdr.h"
#include "im_shdr.h"

#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
#endif //CO_ACT_CLOCK | CO_ACT_HCLOCK | CO_ACT_PCLOCK

#include "ddim_user_custom.h"
#include "ctimshdr.h"
#include "ctimshdrset.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImShdrSet, ct_im_shdr_set)
#define CT_IM_SHDR_SET_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImShdrSetPrivate, CT_TYPE_IM_SHDR_SET))


struct _CtImShdrSetPrivate
{

};


/********
 * IMPL
 */
static void ct_im_shdr_set_constructor(CtImShdrSet *self)
{
//	CtImShdrSetPrivate *priv = CT_IM_SHDR_SET_GET_PRIVATE(self);
}

static void ct_im_shdr_set_destructor(CtImShdrSet *self)
{
//	CtImShdrSetPrivate *priv = CT_IM_SHDR_SET_GET_PRIVATE(self);
}


/**********
 * PUBLIC
 */
VOID ct_im_shdr_set_ctrl(CtImShdrSet* self)
{
	UINT32			loopcnt;
	INT32			ret;
	T_IM_SHDR_CTRL	ctrl[] = {
		[ 0 ] = {	// Max.
			.image_set.in_bit_depth		= D_IM_SHDR_INBITDEPTH_16,
			.image_set.in_c_fmt			= D_IM_SHDR_INCFMT_422SP,
			.image_set.in_edge_cpy		= D_IM_SHDR_ON,
			.image_set.in_edge_cut		= D_IM_SHDR_ON,
			.image_set.out_ctrl			= D_IM_SHDR_OUTCTRL_RGB,
			.image_set.out_sel			= D_IM_SHDR_OUTSEL_RGB_16,
			.image_set.out_sel_en		= D_IM_SHDR_ENABLE,
			.image_mode.exp_mag			= 16383,
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
			.image_mode.fil_margin		= D_IM_SHDR_FLITER_MARGIN_96,
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
			.image_mode.fil_margin		= D_IM_SHDR_FLITER_MARGIN_32,
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif	// CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
			.image_mode.rexp_mag_shift	= 5,
			.image_mode.rexp_mag		= 65536,
			.image_mode.shift_x			= 4094,
			.image_mode.shift_y			= 4094,
			.image_mode.fmd_en			= D_IM_SHDR_ENABLE,
			.image_mode.bypass_en		= D_IM_SHDR_ENABLE,
			.image_mode.smc_in			= D_IM_SHDR_SMCIN_EXT_REF,
			.image_mode.shdr_in			= D_IM_SHDR_SHDRIN_SMCOUT_REF,
			.image_mode.tile_size		= D_IM_SHDR_TILESIZE_1024x512,
			.sdram.r_addr.a_y			= 0xFFFFFFFF,
			.sdram.r_addr.a_c			= 0xFFFFFFFF,
			.sdram.r_addr.b_y			= 0xFFFFFFFF,
			.sdram.r_addr.b_c			= 0xFFFFFFFF,
			.sdram.r_addr.c_y			= 0xFFFFFFFF,
			.sdram.r_addr.c_c			= 0xFFFFFFFF,
			.sdram.r_addr.d_y			= 0xFFFFFFFF,
			.sdram.r_addr.d_c			= 0xFFFFFFFF,
			.sdram.r_addr.e_y			= 0xFFFFFFFF,
			.sdram.r_addr.e_c			= 0xFFFFFFFF,
			.sdram.r_addr.f				= 0xFFFFFFFF,
			.sdram.r_ghsize.a_y			= 0xFFF8,
			.sdram.r_ghsize.a_c			= 0xFFF8,
			.sdram.r_ghsize.b_y			= 0xFFF8,
			.sdram.r_ghsize.b_c			= 0xFFF8,
			.sdram.r_ghsize.c_y			= 0xFFF8,
			.sdram.r_ghsize.c_c			= 0xFFF8,
			.sdram.r_ghsize.d_y			= 0xFFF8,
			.sdram.r_ghsize.d_c			= 0xFFF8,
			.sdram.r_ghsize.e_y			= 0xFFF8,
			.sdram.r_ghsize.e_c			= 0xFFF8,
			.sdram.r_ghsize.f			= 0xFFF8,
			.sdram.r_hsize.a			= 11992,
			.sdram.r_hsize.b			= 11992,
			.sdram.r_hsize.c			= 11992,
			.sdram.r_hsize.d			= 11992,
			.sdram.r_hsize.e			= 11992,
			.sdram.r_vsize.a			= 8992,
			.sdram.r_vsize.b			= 8992,
			.sdram.r_vsize.c			= 8992,
			.sdram.r_vsize.d			= 8992,
			.sdram.r_vsize.e			= 8992,
			.sdram.r_vfm.a				= D_IM_SHDR_VFMT_VIDEO,
			.sdram.w_addr.b_y			= 0xFFFFFFF8,
			.sdram.w_addr.b_c			= 0xFFFFFFF8,
			.sdram.w_addr.e_y			= 0xFFFFFFF8,
			.sdram.w_addr.e_c			= 0xFFFFFFF8,
			.sdram.w_addr.f_y			= 0xFFFFFFF8,
			.sdram.w_addr.f_c			= 0xFFFFFFF8,
			.sdram.w_addr.g_r_y			= 0xFFFFFFF8,
			.sdram.w_addr.g_g_c			= 0xFFFFFFF8,
			.sdram.w_addr.g_b			= 0xFFFFFFF8,
			.sdram.w_addr.h_x			= 0xFFFFFFF8,
			.sdram.w_addr.h_y			= 0xFFFFFFF8,
			.sdram.w_addr.i				= 0xFFFFFFF8,
			.sdram.w_ghsize.b_y			= 0xFFF8,
			.sdram.w_ghsize.b_c			= 0xFFF8,
			.sdram.w_ghsize.e_y			= 0xFFF8,
			.sdram.w_ghsize.e_c			= 0xFFF8,
			.sdram.w_ghsize.f_y			= 0xFFF8,
			.sdram.w_ghsize.f_c			= 0xFFF8,
			.sdram.w_ghsize.g_r_y		= 0xFFF8,
			.sdram.w_ghsize.g_g_c		= 0xFFF8,
			.sdram.w_ghsize.g_b			= 0xFFF8,
			.sdram.w_ghsize.h_x			= 0xFFF8,
			.sdram.w_ghsize.h_y			= 0xFFF8,
			.sdram.w_ghsize.i			= 0xFFF8,
			.sdram.w_vfm.a				= D_IM_SHDR_VFMT_COMPIP_VIDEO,
			.sdram.w_vfm.b				= D_IM_SHDR_VFMT_VIDEO,
			.sdram.w_baddr.a_y			= 0xFFFFC000,
			.sdram.w_baddr.a_c			= 0xFFFFC000,
			.sdram.w_baddr.c_y			= 0xFFFFC000,
			.sdram.w_baddr.c_c			= 0xFFFFC000,
			.sdram.w_baddr.d_y			= 0xFFFFC000,
			.sdram.w_baddr.d_c			= 0xFFFFC000,
			.sdram.w_hsize.a			= 0xFF00,
			.sdram.w_hsize.c			= 0xFF00,
			.sdram.w_hsize.d			= 0xFF00,
			.compip.mode				= D_IM_SHDR_COMP_MODE_LOSSY,
			.compip.mc_mode				= D_IM_SHDR_COMP_MC_UNUSED,
			.compip.comp_incfmt			= D_IM_SHDR_COMP_INCFMT_YUV420,
			.compip.r_bypass_mode		= D_IM_SHDR_ENABLE,
			.compip.w_bypass_mode		= D_IM_SHDR_ENABLE,
			.compip.r_img_axi_size		= D_IM_SHDR_COMP_AXI_512,
			.compip.r_comp_axi_size		= D_IM_SHDR_COMP_AXI_512,
			.compip.w_img_axi_size		= D_IM_SHDR_COMP_AXI_512,
			.compip.lint_no				= 0,
			.compip.lint_mask			= D_IM_SHDR_ENABLE,
			.compip.lint_sts			= D_IM_SHDR_DISABLE,
			.compip.w_addr_y			= 0,
			.compip.w_addr_c			= 0,
			.compip.r_addr_y			= 0,
			.compip.r_addr_c			= 0,
			.pCallBack					= (T_IM_SHDR_CALLBACK)ct_im_shdr_tset2_3_callback,
			.pLineInt_CallBack			= (T_IM_SHDR_LINEINT_CALLBACK)ct_im_shdr_tset2_3_lineint_callback,
		},
#if 0
		[ 1 ] = {	// Min.
			.image_set.in_bit_depth		= D_IM_SHDR_INBITDEPTH_8,
			.image_set.in_c_fmt			= D_IM_SHDR_INCFMT_420SP,
			.image_set.in_edge_cpy		= D_IM_SHDR_OFF,
			.image_set.in_edge_cut		= D_IM_SHDR_OFF,
			.image_set.out_ctrl			= D_IM_SHDR_OUTCTRL_YCC,
			.image_set.out_sel			= D_IM_SHDR_OUTSEL_YCC_16,
			.image_set.out_sel_en		= D_IM_SHDR_DISABLE,
			.image_mode.exp_mag			= 1,
			.image_mode.fil_margin		= D_IM_SHDR_FLITER_MARGIN_16,
			.image_mode.rexp_mag_shift	= -8,
			.image_mode.rexp_mag		= 0,
			.image_mode.shift_x			= -4096,
			.image_mode.shift_y			= -4096,
			.image_mode.fmd_en			= D_IM_SHDR_DISABLE,
			.image_mode.bypass_en		= D_IM_SHDR_DISABLE,
			.image_mode.smc_in			= D_IM_SHDR_SMCIN_STN_REF,
			.image_mode.shdr_in			= D_IM_SHDR_SHDRIN_STN_REF,
			.image_mode.tile_size		= D_IM_SHDR_TILESIZE_1024x1024,
			.sdram.r_addr.a_y			= 0x00000000,
			.sdram.r_addr.a_c			= 0x00000000,
			.sdram.r_addr.b_y			= 0x00000000,
			.sdram.r_addr.b_c			= 0x00000000,
			.sdram.r_addr.c_y			= 0x00000000,
			.sdram.r_addr.c_c			= 0x00000000,
			.sdram.r_addr.d_y			= 0x00000000,
			.sdram.r_addr.d_c			= 0x00000000,
			.sdram.r_addr.e_y			= 0x00000000,
			.sdram.r_addr.e_c			= 0x00000000,
			.sdram.r_addr.f				= 0x00000000,
			.sdram.r_ghsize.a_y			= 0x0008,
			.sdram.r_ghsize.a_c			= 0x0008,
			.sdram.r_ghsize.b_y			= 0x0008,
			.sdram.r_ghsize.b_c			= 0x0008,
			.sdram.r_ghsize.c_y			= 0x0008,
			.sdram.r_ghsize.c_c			= 0x0008,
			.sdram.r_ghsize.d_y			= 0x0008,
			.sdram.r_ghsize.d_c			= 0x0008,
			.sdram.r_ghsize.e_y			= 0x0008,
			.sdram.r_ghsize.e_c			= 0x0008,
			.sdram.r_ghsize.f			= 0x0008,
			.sdram.r_hsize.a			= 4,
			.sdram.r_hsize.b			= 4,
			.sdram.r_hsize.c			= 4,
			.sdram.r_hsize.d			= 4,
			.sdram.r_hsize.e			= 4,
			.sdram.r_vsize.a			= 4,
			.sdram.r_vsize.b			= 4,
			.sdram.r_vsize.c			= 4,
			.sdram.r_vsize.d			= 4,
			.sdram.r_vsize.e			= 4,
			.sdram.r_vfm.a				= D_IM_SHDR_VFMT_RASTER,
			.sdram.w_addr.b_y			= 0x00000000,
			.sdram.w_addr.b_c			= 0x00000000,
			.sdram.w_addr.e_y			= 0x00000000,
			.sdram.w_addr.e_c			= 0x00000000,
			.sdram.w_addr.f_y			= 0x00000000,
			.sdram.w_addr.f_c			= 0x00000000,
			.sdram.w_addr.g_r_y			= 0x00000000,
			.sdram.w_addr.g_g_c			= 0x00000000,
			.sdram.w_addr.g_b			= 0x00000000,
			.sdram.w_addr.h_x			= 0x00000000,
			.sdram.w_addr.h_y			= 0x00000000,
			.sdram.w_addr.i				= 0x00000000,
			.sdram.w_ghsize.b_y			= 0x0001,
			.sdram.w_ghsize.b_c			= 0x0001,
			.sdram.w_ghsize.e_y			= 0x0001,
			.sdram.w_ghsize.e_c			= 0x0001,
			.sdram.w_ghsize.f_y			= 0x0001,
			.sdram.w_ghsize.f_c			= 0x0001,
			.sdram.w_ghsize.g_r_y		= 0x0001,
			.sdram.w_ghsize.g_g_c		= 0x0001,
			.sdram.w_ghsize.g_b			= 0x0001,
			.sdram.w_ghsize.h_x			= 0x0001,
			.sdram.w_ghsize.h_y			= 0x0001,
			.sdram.w_ghsize.i			= 0x0001,
			.sdram.w_vfm.a				= D_IM_SHDR_VFMT_COMPIP_VIDEO,
			.sdram.w_vfm.b				= D_IM_SHDR_VFMT_RASTER,
			.sdram.w_baddr.a_y			= 0x00000000,
			.sdram.w_baddr.a_c			= 0x00000000,
			.sdram.w_baddr.c_y			= 0x00000000,
			.sdram.w_baddr.c_c			= 0x00000000,
			.sdram.w_baddr.d_y			= 0x00000000,
			.sdram.w_baddr.d_c			= 0x00000000,
			.sdram.w_hsize.a			= 0,
			.sdram.w_hsize.c			= 0,
			.sdram.w_hsize.d			= 0,
			.pCallBack					= (T_IM_SHDR_CALLBACK)ct_im_shdr_tset2_3_callback,
			.pLineInt_CallBack			= (T_IM_SHDR_LINEINT_CALLBACK)ct_im_shdr_tset2_3_lineint_callback,
		},
#endif
	};

	for( loopcnt = 0; loopcnt < (sizeof(ctrl) / sizeof(ctrl[0])); loopcnt++ ) {
		ret = Im_SHDR_Ctrl_Common( &ctrl[ loopcnt ] );
		Ddim_Print(("ct_im_shdr_set_ctrl(%d)[ret=0x%08x]\n", loopcnt, ret));
	}
}

VOID ct_im_shdr_set_pre(CtImShdrSet* self)
{
	UINT32			loopcnt;
	INT32			ret;
	T_IM_SHDR_PRE	pre[] = {
		[ 0 ] = {	// Max.
			.pre_mode.cus_mode			= D_IM_SHDR_CUS_YCC420_PADDING,
			.pre_mode.degamma_mode		= D_IM_SHDR_DEGAMMA_BITEXP,
			.y2r_coef[ 0 ]				= 0x3FFF,
			.y2r_coef[ 1 ]				= 0x3FFF,
			.y2r_coef[ 2 ]				= 0x3FFF,
			.y2r_coef[ 3 ]				= 0x3FFF,
			.y2r_coef[ 4 ]				= 0x3FFF,
			.y2r_coef[ 5 ]				= 0x3FFF,
			.y2r_coef[ 6 ]				= 0x3FFF,
			.y2r_coef[ 7 ]				= 0x3FFF,
			.y2r_coef[ 8 ]				= 0x3FFF,
			.y2r_clp.upper_long0[ 0 ]	= 0xFFFF,
			.y2r_clp.upper_long0[ 1 ]	= 0xFFFF,
			.y2r_clp.upper_long0[ 2 ]	= 0xFFFF,
			.y2r_clp.lower_long0[ 0 ]	= 0xFFFF,
			.y2r_clp.lower_long0[ 1 ]	= 0xFFFF,
			.y2r_clp.lower_long0[ 2 ]	= 0xFFFF,
			.y2r_clp.upper_short[ 0 ]	= 0xFF,
			.y2r_clp.upper_short[ 1 ]	= 0xFF,
			.y2r_clp.upper_short[ 2 ]	= 0xFF,
			.y2r_clp.lower_short[ 0 ]	= 0xFF,
			.y2r_clp.lower_short[ 1 ]	= 0xFF,
			.y2r_clp.lower_short[ 2 ]	= 0xFF,
			.r2y_coef[ 0 ]				= 0x3FFF,
			.r2y_coef[ 1 ]				= 0x3FFF,
			.r2y_coef[ 2 ]				= 0x3FFF,
			.r2y_coef[ 3 ]				= 0x3FFF,
			.r2y_coef[ 4 ]				= 0x3FFF,
			.r2y_coef[ 5 ]				= 0x3FFF,
			.r2y_coef[ 6 ]				= 0x3FFF,
			.r2y_coef[ 7 ]				= 0x3FFF,
			.r2y_coef[ 8 ]				= 0x3FFF,
			.r2y_clp.upper_long_y		= 0xFFFF,
			.r2y_clp.upper_long_c[ 0 ]	= 0x7FFF,
			.r2y_clp.upper_long_c[ 1 ]	= 0x7FFF,
			.r2y_clp.lower_long_y		= 0xFFFF,
			.r2y_clp.lower_long_c[ 0 ]	= 0x7FFF,
			.r2y_clp.lower_long_c[ 1 ]	= 0x7FFF,
			.r2y_clp.upper_short_y		= 0xFFF,
			.r2y_clp.upper_short_c[ 0 ]	= 0x7FF,
			.r2y_clp.upper_short_c[ 1 ]	= 0x7FF,
			.r2y_clp.lower_short_y		= 0xFFF,
			.r2y_clp.lower_short_c[ 0 ]	= 0x7FF,
			.r2y_clp.lower_short_c[ 1 ]	= 0x7FF,
			.short_knee.offset[ 0 ]		= 0xFF,
			.short_knee.offset[ 1 ]		= 0xFF,
			.short_knee.offset[ 2 ]		= 0xFF,
			.short_knee.slope[ 0 ]		= 0xFF,
			.short_knee.slope[ 1 ]		= 0xFF,
			.short_knee.slope[ 2 ]		= 0xFF,
			.short_knee.boundary[ 0 ]	= 0x3FF,
			.short_knee.boundary[ 1 ]	= 0x3FF,
			.long_knee.offset[ 0 ]		= 0xFF,
			.long_knee.offset[ 1 ]		= 0xFF,
			.long_knee.offset[ 2 ]		= 0xFF,
			.long_knee.slope[ 0 ]		= 0xFF,
			.long_knee.slope[ 1 ]		= 0xFF,
			.long_knee.slope[ 2 ]		= 0xFF,
			.long_knee.boundary[ 0 ]	= 0x3FF,
			.long_knee.boundary[ 1 ]	= 0x3FF,
		},
#if 0
		[ 1 ] = {	// Min.
			.pre_mode.cus_mode			= D_IM_SHDR_CUS_YCC422_BILINEAR_A,
			.pre_mode.degamma_mode		= D_IM_SHDR_DEGAMMA_LUT,
			.y2r_coef[ 0 ]				= -0x4000,
			.y2r_coef[ 1 ]				= -0x4000,
			.y2r_coef[ 2 ]				= -0x4000,
			.y2r_coef[ 3 ]				= -0x4000,
			.y2r_coef[ 4 ]				= -0x4000,
			.y2r_coef[ 5 ]				= -0x4000,
			.y2r_coef[ 6 ]				= -0x4000,
			.y2r_coef[ 7 ]				= -0x4000,
			.y2r_coef[ 8 ]				= -0x4000,
			.y2r_clp.upper_long0[ 0 ]	= 0x0000,
			.y2r_clp.upper_long0[ 1 ]	= 0x0000,
			.y2r_clp.upper_long0[ 2 ]	= 0x0000,
			.y2r_clp.lower_long0[ 0 ]	= 0x0000,
			.y2r_clp.lower_long0[ 1 ]	= 0x0000,
			.y2r_clp.lower_long0[ 2 ]	= 0x0000,
			.y2r_clp.upper_short[ 0 ]	= 0x00,
			.y2r_clp.upper_short[ 1 ]	= 0x00,
			.y2r_clp.upper_short[ 2 ]	= 0x00,
			.y2r_clp.lower_short[ 0 ]	= 0x00,
			.y2r_clp.lower_short[ 1 ]	= 0x00,
			.y2r_clp.lower_short[ 2 ]	= 0x00,
			.r2y_coef[ 0 ]				= -0x4000,
			.r2y_coef[ 1 ]				= -0x4000,
			.r2y_coef[ 2 ]				= -0x4000,
			.r2y_coef[ 3 ]				= -0x4000,
			.r2y_coef[ 4 ]				= -0x4000,
			.r2y_coef[ 5 ]				= -0x4000,
			.r2y_coef[ 6 ]				= -0x4000,
			.r2y_coef[ 7 ]				= -0x4000,
			.r2y_coef[ 8 ]				= -0x4000,
			.r2y_clp.upper_long_y		= 0x0000,
			.r2y_clp.upper_long_c[ 0 ]	= -0x8000,
			.r2y_clp.upper_long_c[ 1 ]	= -0x8000,
			.r2y_clp.lower_long_y		= 0x0000,
			.r2y_clp.lower_long_c[ 0 ]	= -0x8000,
			.r2y_clp.lower_long_c[ 1 ]	= -0x8000,
			.r2y_clp.upper_short_y		= 0x000,
			.r2y_clp.upper_short_c[ 0 ]	= -0x800,
			.r2y_clp.upper_short_c[ 1 ]	= -0x800,
			.r2y_clp.lower_short_y		= 0x000,
			.r2y_clp.lower_short_c[ 0 ]	= -0x800,
			.r2y_clp.lower_short_c[ 1 ]	= -0x800,
			.short_knee.offset[ 0 ]		= 0x00,
			.short_knee.offset[ 1 ]		= 0x00,
			.short_knee.offset[ 2 ]		= 0x00,
			.short_knee.slope[ 0 ]		= 0x00,
			.short_knee.slope[ 1 ]		= 0x00,
			.short_knee.slope[ 2 ]		= 0x00,
			.short_knee.boundary[ 0 ]	= 0x000,
			.short_knee.boundary[ 1 ]	= 0x000,
			.long_knee.offset[ 0 ]		= 0x00,
			.long_knee.offset[ 1 ]		= 0x00,
			.long_knee.offset[ 2 ]		= 0x00,
			.long_knee.slope[ 0 ]		= 0x00,
			.long_knee.slope[ 1 ]		= 0x00,
			.long_knee.slope[ 2 ]		= 0x00,
			.long_knee.boundary[ 0 ]	= 0x000,
			.long_knee.boundary[ 1 ]	= 0x000,
		},
#endif
	};

	for( loopcnt = 0; loopcnt < (sizeof(pre) / sizeof(pre[0])); loopcnt++ ) {
		ret = Im_SHDR_Set_Pre( &pre[ loopcnt ] );
		Ddim_Print(("ct_im_shdr_set_pre(%d)[ret=0x%08x]\n", loopcnt, ret));
	}
}

VOID ct_im_shdr_set_fmd(CtImShdrSet* self)
{
	UINT32			loopcnt;
	INT32			ret;
	T_IM_SHDR_FMD	fmd[] = {
		[ 0 ] = {	// Max.
			.ep_boundary[ 0 ]			= 0xFF,
			.ep_boundary[ 1 ]			= 0xFF,
			.ep_boundary[ 2 ]			= 0xFF,
			.ep_boundary[ 3 ]			= 0xFF,
			.ep_offset[ 0 ]				= 0xFF,
			.ep_offset[ 1 ]				= 0xFF,
			.ep_offset[ 2 ]				= 0xFF,
			.ep_offset[ 3 ]				= 0xFF,
			.ep_blend					= 0x7,
			.fd_weight					= 0x1F,
			.mvcnt.bounds				= 0xFF,
			.mvcnt.threshold			= 0xFF,
			.mvcnt.gr					= 0xFFF,
			.bldr_offset[ 0 ]			= 0xFF,
			.bldr_offset[ 1 ]			= 0xFF,
			.bldr_offset[ 2 ]			= 0xFF,
			.bldr_offset[ 3 ]			= 0xFF,
			.bldr_offset[ 4 ]			= 0xFF,
			.bldr_slope[ 0 ]			= 0xFFF,
			.bldr_slope[ 1 ]			= 0xFFF,
			.bldr_slope[ 2 ]			= 0xFFF,
			.bldr_slope[ 3 ]			= 0xFFF,
			.bldr_slope[ 4 ]			= 0xFFF,
			.bldr_boundary[ 0 ]			= 0xFF,
			.bldr_boundary[ 1 ]			= 0xFF,
			.bldr_boundary[ 2 ]			= 0xFF,
			.bldr_boundary[ 3 ]			= 0xFF,
			.bldr_boundary[ 4 ]			= 0xFF,
			.weight_r2y_coef[ 0 ]		= 0x3FFF,
			.weight_r2y_coef[ 1 ]		= 0x3FFF,
			.weight_r2y_coef[ 2 ]		= 0x3FFF,
			.weight_r2y_clp.upper		= 0xFF,
			.weight_r2y_clp.lower		= 0xFF,
			.weight_base				= D_IM_SHDR_WGHTBASE_RGB,
			.weight_offset[ 0 ][ 0 ]	= 0xFFF,
			.weight_offset[ 0 ][ 1 ]	= 0xFFF,
			.weight_offset[ 0 ][ 2 ]	= 0xFFF,
			.weight_offset[ 0 ][ 3 ]	= 0xFFF,
			.weight_offset[ 0 ][ 4 ]	= 0xFFF,
			.weight_offset[ 1 ][ 0 ]	= 0xFFF,
			.weight_offset[ 1 ][ 1 ]	= 0xFFF,
			.weight_offset[ 1 ][ 2 ]	= 0xFFF,
			.weight_offset[ 1 ][ 3 ]	= 0xFFF,
			.weight_offset[ 1 ][ 4 ]	= 0xFFF,
			.weight_offset[ 2 ][ 0 ]	= 0xFFF,
			.weight_offset[ 2 ][ 1 ]	= 0xFFF,
			.weight_offset[ 2 ][ 2 ]	= 0xFFF,
			.weight_offset[ 2 ][ 3 ]	= 0xFFF,
			.weight_offset[ 2 ][ 4 ]	= 0xFFF,
			.weight_slope[ 0 ][ 0 ]		= 0xFFF,
			.weight_slope[ 0 ][ 1 ]		= 0xFFF,
			.weight_slope[ 0 ][ 2 ]		= 0xFFF,
			.weight_slope[ 0 ][ 3 ]		= 0xFFF,
			.weight_slope[ 0 ][ 4 ]		= 0xFFF,
			.weight_slope[ 1 ][ 0 ]		= 0xFFF,
			.weight_slope[ 1 ][ 1 ]		= 0xFFF,
			.weight_slope[ 1 ][ 2 ]		= 0xFFF,
			.weight_slope[ 1 ][ 3 ]		= 0xFFF,
			.weight_slope[ 1 ][ 4 ]		= 0xFFF,
			.weight_slope[ 2 ][ 0 ]		= 0xFFF,
			.weight_slope[ 2 ][ 1 ]		= 0xFFF,
			.weight_slope[ 2 ][ 2 ]		= 0xFFF,
			.weight_slope[ 2 ][ 3 ]		= 0xFFF,
			.weight_slope[ 2 ][ 4 ]		= 0xFFF,
//			.weight_boundary[ 0 ][ 0 ]	= 0xFF,
			.weight_boundary[ 0 ][ 1 ]	= 0xFF,
			.weight_boundary[ 0 ][ 2 ]	= 0xFF,
			.weight_boundary[ 0 ][ 3 ]	= 0xFF,
			.weight_boundary[ 0 ][ 4 ]	= 0xFF,
//			.weight_boundary[ 1 ][ 0 ]	= 0xFF,
			.weight_boundary[ 1 ][ 1 ]	= 0xFF,
			.weight_boundary[ 1 ][ 2 ]	= 0xFF,
			.weight_boundary[ 1 ][ 3 ]	= 0xFF,
			.weight_boundary[ 1 ][ 4 ]	= 0xFF,
//			.weight_boundary[ 2 ][ 0 ]	= 0xFF,
			.weight_boundary[ 2 ][ 1 ]	= 0xFF,
			.weight_boundary[ 2 ][ 2 ]	= 0xFF,
			.weight_boundary[ 2 ][ 3 ]	= 0xFF,
			.weight_boundary[ 2 ][ 4 ]	= 0xFF,
			.iso_threshold				= 0x1FF,
			.iso_coef[ 0 ]				= 0x3,
			.iso_coef[ 1 ]				= 0x3,
			.iso_coef[ 2 ]				= 0x3,
			.iso_coef[ 3 ]				= 0x1F,
			.iso_coef[ 4 ]				= 0x1F,
			.iso_coef[ 5 ]				= 0xFF,
			.sat_threshold				= 0xFF,
			.exp77_mode					= D_IM_SHDR_EXP77MD_PERIMAXVAL,
			.fmd_sel					= D_IM_SHDR_FMDSEL_REDUCTION,
		},
#if 0
		[ 1 ] = {	// Min.
			.ep_boundary[ 0 ]			= 0x00,
			.ep_boundary[ 1 ]			= 0x00,
			.ep_boundary[ 2 ]			= 0x00,
			.ep_boundary[ 3 ]			= 0x00,
			.ep_offset[ 0 ]				= 0x00,
			.ep_offset[ 1 ]				= 0x00,
			.ep_offset[ 2 ]				= 0x00,
			.ep_offset[ 3 ]				= 0x00,
			.ep_blend					= 0x0,
			.fd_weight					= 0x00,
			.mvcnt.bounds				= 0x00,
			.mvcnt.threshold			= 0x00,
			.mvcnt.gr					= -0x1000,
			.bldr_offset[ 0 ]			= 0x00,
			.bldr_offset[ 1 ]			= 0x00,
			.bldr_offset[ 2 ]			= 0x00,
			.bldr_offset[ 3 ]			= 0x00,
			.bldr_offset[ 4 ]			= 0x00,
			.bldr_slope[ 0 ]			= 0x000,
			.bldr_slope[ 1 ]			= 0x000,
			.bldr_slope[ 2 ]			= 0x000,
			.bldr_slope[ 3 ]			= 0x000,
			.bldr_slope[ 4 ]			= 0x000,
			.bldr_boundary[ 0 ]			= 0x00,
			.bldr_boundary[ 1 ]			= 0x00,
			.bldr_boundary[ 2 ]			= 0x00,
			.bldr_boundary[ 3 ]			= 0x00,
			.bldr_boundary[ 4 ]			= 0x00,
			.weight_r2y_coef[ 0 ]		= -0x4000,
			.weight_r2y_coef[ 1 ]		= -0x4000,
			.weight_r2y_coef[ 2 ]		= -0x4000,
			.weight_r2y_clp.upper		= 0x00,
			.weight_r2y_clp.lower		= 0x00,
			.weight_base				= D_IM_SHDR_WGHTBASE_Y,
			.weight_offset[ 0 ][ 0 ]	= 0x000,
			.weight_offset[ 0 ][ 1 ]	= 0x000,
			.weight_offset[ 0 ][ 2 ]	= 0x000,
			.weight_offset[ 0 ][ 3 ]	= 0x000,
			.weight_offset[ 0 ][ 4 ]	= 0x000,
			.weight_offset[ 1 ][ 0 ]	= 0x000,
			.weight_offset[ 1 ][ 1 ]	= 0x000,
			.weight_offset[ 1 ][ 2 ]	= 0x000,
			.weight_offset[ 1 ][ 3 ]	= 0x000,
			.weight_offset[ 1 ][ 4 ]	= 0x000,
			.weight_offset[ 2 ][ 0 ]	= 0x000,
			.weight_offset[ 2 ][ 1 ]	= 0x000,
			.weight_offset[ 2 ][ 2 ]	= 0x000,
			.weight_offset[ 2 ][ 3 ]	= 0x000,
			.weight_offset[ 2 ][ 4 ]	= 0x000,
			.weight_slope[ 0 ][ 0 ]		= 0x000,
			.weight_slope[ 0 ][ 1 ]		= 0x000,
			.weight_slope[ 0 ][ 2 ]		= 0x000,
			.weight_slope[ 0 ][ 3 ]		= 0x000,
			.weight_slope[ 0 ][ 4 ]		= 0x000,
			.weight_slope[ 1 ][ 0 ]		= 0x000,
			.weight_slope[ 1 ][ 1 ]		= 0x000,
			.weight_slope[ 1 ][ 2 ]		= 0x000,
			.weight_slope[ 1 ][ 3 ]		= 0x000,
			.weight_slope[ 1 ][ 4 ]		= 0x000,
			.weight_slope[ 2 ][ 0 ]		= 0x000,
			.weight_slope[ 2 ][ 1 ]		= 0x000,
			.weight_slope[ 2 ][ 2 ]		= 0x000,
			.weight_slope[ 2 ][ 3 ]		= 0x000,
			.weight_slope[ 2 ][ 4 ]		= 0x000,
//			.weight_boundary[ 0 ][ 0 ]	= 0x00,
			.weight_boundary[ 0 ][ 1 ]	= 0x00,
			.weight_boundary[ 0 ][ 2 ]	= 0x00,
			.weight_boundary[ 0 ][ 3 ]	= 0x00,
			.weight_boundary[ 0 ][ 4 ]	= 0x00,
//			.weight_boundary[ 1 ][ 0 ]	= 0x00,
			.weight_boundary[ 1 ][ 1 ]	= 0x00,
			.weight_boundary[ 1 ][ 2 ]	= 0x00,
			.weight_boundary[ 1 ][ 3 ]	= 0x00,
			.weight_boundary[ 1 ][ 4 ]	= 0x00,
//			.weight_boundary[ 2 ][ 0 ]	= 0x00,
			.weight_boundary[ 2 ][ 1 ]	= 0x00,
			.weight_boundary[ 2 ][ 2 ]	= 0x00,
			.weight_boundary[ 2 ][ 3 ]	= 0x00,
			.weight_boundary[ 2 ][ 4 ]	= 0x00,
			.iso_threshold				= 0x000,
			.iso_coef[ 0 ]				= 0x0,
			.iso_coef[ 1 ]				= 0x0,
			.iso_coef[ 2 ]				= 0x0,
			.iso_coef[ 3 ]				= 0x00,
			.iso_coef[ 4 ]				= 0x00,
			.iso_coef[ 5 ]				= 0x00,
			.sat_threshold				= 0x00,
			.exp77_mode					= D_IM_SHDR_EXP77MD_COEFSUMDIV,
			.fmd_sel					= D_IM_SHDR_FMDSEL_EXPANSION,
		},
#endif
	};

	for( loopcnt = 0; loopcnt < (sizeof(fmd) / sizeof(fmd[0])); loopcnt++ ) {
		ret = Im_SHDR_Set_Fmd( &fmd[ loopcnt ] );
		Ddim_Print(("ct_im_shdr_set_fmd(%d)[ret=0x%08x]\n", loopcnt, ret));
	}
}

VOID ct_im_shdr_set_pmsk(CtImShdrSet* self)
{
	UINT32			loopcnt;
	INT32			ret;
	T_IM_SHDR_PMSK	pmsk[] = {
		[ 0 ] = {	// Max.
			.tlut[ 0 ]	= 0xFF,
			.tlut[ 1 ]	= 0xFF,
			.tlut[ 2 ]	= 0xFF,
			.tlut[ 3 ]	= 0xFF,
			.tlut[ 4 ]	= 0xFF,
			.tlut[ 5 ]	= 0xFF,
			.tlut[ 6 ]	= 0xFF,
			.tlut[ 7 ]	= 0xFF,
			.tlut[ 8 ]	= 0xFF,
			.tlut[ 9 ]	= 0xFF,
			.tlut[ 10 ]	= 0xFF,
			.tlut[ 11 ]	= 0xFF,
			.tlut[ 12 ]	= 0xFF,
			.tlut[ 13 ]	= 0xFF,
			.tlut[ 14 ]	= 0xFF,
			.tlut[ 15 ]	= 0xFF,
			.tlut[ 16 ]	= 0xFF,
			.pmsk_mode	= D_IM_SHDR_PMSKMD_AVE,
		},
#if 0
		[ 1 ] = {	// Min.
			.tlut[ 0 ]	= 0x00,
			.tlut[ 1 ]	= 0x00,
			.tlut[ 2 ]	= 0x00,
			.tlut[ 3 ]	= 0x00,
			.tlut[ 4 ]	= 0x00,
			.tlut[ 5 ]	= 0x00,
			.tlut[ 6 ]	= 0x00,
			.tlut[ 7 ]	= 0x00,
			.tlut[ 8 ]	= 0x00,
			.tlut[ 9 ]	= 0x00,
			.tlut[ 10 ]	= 0x00,
			.tlut[ 11 ]	= 0x00,
			.tlut[ 12 ]	= 0x00,
			.tlut[ 13 ]	= 0x00,
			.tlut[ 14 ]	= 0x00,
			.tlut[ 15 ]	= 0x00,
			.tlut[ 16 ]	= 0x00,
			.pmsk_mode	= D_IM_SHDR_PMSKMD_MAX,
		},
#endif
	};

	for( loopcnt = 0; loopcnt < (sizeof(pmsk) / sizeof(pmsk[0])); loopcnt++ ) {
		ret = Im_SHDR_Set_PreMask( &pmsk[ loopcnt ] );
		Ddim_Print(("ct_im_shdr_set_pmsk(%d)[ret=0x%08x]\n", loopcnt, ret));
	}
}

VOID ct_im_shdr_set_spnr(CtImShdrSet* self)
{
	UINT32			loopcnt;
	INT32			ret;
	T_IM_SHDR_SPNR	spnr[] = {
		[ 0 ] = {	// Max.
			.spnr_en			= D_IM_SHDR_ENABLE,
			.spe_blend			= 0x7,
//			.spe_boundary[ 0 ]	= 0xFFF,
			.spe_boundary[ 1 ]	= 0xFFF,
			.spe_boundary[ 2 ]	= 0xFFF,
			.spe_boundary[ 3 ]	= 0xFFF,
			.spe_offset[ 0 ]	= 0xFFF,
			.spe_offset[ 1 ]	= 0xFFF,
			.spe_offset[ 2 ]	= 0xFFF,
			.spe_offset[ 3 ]	= 0xFFF,
		},
#if 0
		[ 1 ] = {	// Min.
			.spnr_en			= D_IM_SHDR_DISABLE,
			.spe_blend			= 0x0,
//			.spe_boundary[ 0 ]	= 0x000,
			.spe_boundary[ 1 ]	= 0x000,
			.spe_boundary[ 2 ]	= 0x000,
			.spe_boundary[ 3 ]	= 0x000,
			.spe_offset[ 0 ]	= 0x000,
			.spe_offset[ 1 ]	= 0x000,
			.spe_offset[ 2 ]	= 0x000,
			.spe_offset[ 3 ]	= 0x000,
		},
#endif
	};

	for( loopcnt = 0; loopcnt < (sizeof(spnr) / sizeof(spnr[0])); loopcnt++ ) {
		ret = Im_SHDR_Set_Spnr( &spnr[ loopcnt ] );
		Ddim_Print(("ct_im_shdr_set_spnr(%d)[ret=0x%08x]\n", loopcnt, ret));
	}
}

VOID ct_im_shdr_set_mask(CtImShdrSet* self)
{
	UINT32			loopcnt;
	INT32			ret;
	T_IM_SHDR_MSK	msk[] = {
		[ 0 ] = {	// Max.
			.y2r_clp_upper_long[ 0 ]	= 0xFFF,
			.y2r_clp_upper_long[ 1 ]	= 0xFFF,
			.y2r_clp_upper_long[ 2 ]	= 0xFFF,
			.y2r_clp_lower_long[ 0 ]	= 0xFFF,
			.y2r_clp_lower_long[ 1 ]	= 0xFFF,
			.y2r_clp_lower_long[ 2 ]	= 0xFFF,
			.y2r_clp_upper_short[ 0 ]	= 0xFFF,
			.y2r_clp_upper_short[ 1 ]	= 0xFFF,
			.y2r_clp_upper_short[ 2 ]	= 0xFFF,
			.y2r_clp_lower_short[ 0 ]	= 0xFFF,
			.y2r_clp_lower_short[ 1 ]	= 0xFFF,
			.y2r_clp_lower_short[ 2 ]	= 0xFFF,
			.alpha						= 0x3F,
			.lpfc[ 0 ][ 0 ]				= 0xFF,
			.lpfc[ 0 ][ 1 ]				= 0xFF,
			.lpfc[ 0 ][ 2 ]				= 0xFF,
			.lpfc[ 1 ][ 0 ]				= 0xFF,
			.lpfc[ 1 ][ 1 ]				= 0xFF,
			.lpfc[ 1 ][ 2 ]				= 0xFF,
			.lpfc[ 2 ][ 0 ]				= 0xFF,
			.lpfc[ 2 ][ 1 ]				= 0xFF,
			.lpfc[ 2 ][ 2 ]				= 0xFF,
			.blend_offset[ 0 ]			= 0xFF,
			.blend_offset[ 1 ]			= 0xFF,
			.blend_offset[ 2 ]			= 0xFF,
			.blend_offset[ 3 ]			= 0xFF,
			.blend_offset[ 4 ]			= 0xFF,
			.blend_offset[ 5 ]			= 0xFF,
			.blend_offset[ 6 ]			= 0xFF,
			.blend_slope[ 0 ]			= 0xFFFF,
			.blend_slope[ 1 ]			= 0xFFFF,
			.blend_slope[ 2 ]			= 0xFFFF,
			.blend_slope[ 3 ]			= 0xFFFF,
			.blend_slope[ 4 ]			= 0xFFFF,
			.blend_slope[ 5 ]			= 0xFFFF,
			.blend_slope[ 6 ]			= 0xFFFF,
//			.blend_boundary[ 0 ]		= 0xFFF,
			.blend_boundary[ 1 ]		= 0xFFF,
			.blend_boundary[ 2 ]		= 0xFFF,
			.blend_boundary[ 3 ]		= 0xFFF,
			.blend_boundary[ 4 ]		= 0xFFF,
			.blend_boundary[ 5 ]		= 0xFFF,
			.blend_boundary[ 6 ]		= 0xFFF,
			.norm_gain[ 0 ]				= 0xFF,
			.norm_gain[ 1 ]				= 0xFF,
			.norm_gain[ 2 ]				= 0xFF,
			.norm_offset[ 0 ]			= 0xFF,
			.norm_offset[ 1 ]			= 0xFF,
			.norm_offset[ 2 ]			= 0xFF,
			.msk_mode					= D_IM_SHDR_MSKMD_MSKONLY,
		},
#if 0
		[ 1 ] = {	// Min.
			.y2r_clp_upper_long[ 0 ]	= 0x000,
			.y2r_clp_upper_long[ 1 ]	= 0x000,
			.y2r_clp_upper_long[ 2 ]	= 0x000,
			.y2r_clp_lower_long[ 0 ]	= 0x000,
			.y2r_clp_lower_long[ 1 ]	= 0x000,
			.y2r_clp_lower_long[ 2 ]	= 0x000,
			.y2r_clp_upper_short[ 0 ]	= 0x000,
			.y2r_clp_upper_short[ 1 ]	= 0x000,
			.y2r_clp_upper_short[ 2 ]	= 0x000,
			.y2r_clp_lower_short[ 0 ]	= 0x000,
			.y2r_clp_lower_short[ 1 ]	= 0x000,
			.y2r_clp_lower_short[ 2 ]	= 0x000,
			.alpha						= 0x00,
			.lpfc[ 0 ][ 0 ]				= 0x00,
			.lpfc[ 0 ][ 1 ]				= 0x00,
			.lpfc[ 0 ][ 2 ]				= 0x00,
			.lpfc[ 1 ][ 0 ]				= 0x00,
			.lpfc[ 1 ][ 1 ]				= 0x00,
			.lpfc[ 1 ][ 2 ]				= 0x00,
			.lpfc[ 2 ][ 0 ]				= 0x00,
			.lpfc[ 2 ][ 1 ]				= 0x00,
			.lpfc[ 2 ][ 2 ]				= 0x00,
			.blend_offset[ 0 ]			= 0x00,
			.blend_offset[ 1 ]			= 0x00,
			.blend_offset[ 2 ]			= 0x00,
			.blend_offset[ 3 ]			= 0x00,
			.blend_offset[ 4 ]			= 0x00,
			.blend_offset[ 5 ]			= 0x00,
			.blend_offset[ 6 ]			= 0x00,
			.blend_slope[ 0 ]			= 0x0000,
			.blend_slope[ 1 ]			= 0x0000,
			.blend_slope[ 2 ]			= 0x0000,
			.blend_slope[ 3 ]			= 0x0000,
			.blend_slope[ 4 ]			= 0x0000,
			.blend_slope[ 5 ]			= 0x0000,
			.blend_slope[ 6 ]			= 0x0000,
//			.blend_boundary[ 0 ]		= 0x000,
			.blend_boundary[ 1 ]		= 0x000,
			.blend_boundary[ 2 ]		= 0x000,
			.blend_boundary[ 3 ]		= 0x000,
			.blend_boundary[ 4 ]		= 0x000,
			.blend_boundary[ 5 ]		= 0x000,
			.blend_boundary[ 6 ]		= 0x000,
			.norm_gain[ 0 ]				= 0xFF,
			.norm_gain[ 1 ]				= 0xFF,
			.norm_gain[ 2 ]				= 0xFF,
			.norm_offset[ 0 ]			= 0xFF,
			.norm_offset[ 1 ]			= 0xFF,
			.norm_offset[ 2 ]			= 0xFF,
			.msk_mode					= D_IM_SHDR_MSKMD_SHORT,
		},
#endif
	};

	for( loopcnt = 0; loopcnt < (sizeof(msk) / sizeof(msk[0])); loopcnt++ ) {
		ret = Im_SHDR_Set_Mask( &msk[ loopcnt ] );
		Ddim_Print(("ct_im_shdr_set_msk(%d)[ret=0x%08x]\n", loopcnt, ret));
	}
}

VOID ct_im_shdr_set_bld(CtImShdrSet* self)
{
	UINT32			loopcnt;
	INT32			ret;
	T_IM_SHDR_BLD	bld[] = {
		[ 0 ] = {	// Max.
			.blend_sel		= D_IM_SHDR_BLDSEL_LONG_SHORT,
			.alpha_sel		= D_IM_SHDR_ALPHASEL_FIXED,
			.alpha_val[ 0 ]	= 0xFF,
			.alpha_val[ 1 ]	= 0xFF,
			.alpha_val[ 2 ]	= 0xFF,
		},
#if 0
		[ 1 ] = {	// Min.
			.blend_sel		= D_IM_SHDR_BLDSEL_SHORT_LONG,
			.alpha_sel		= D_IM_SHDR_ALPHASEL_MERGEMASK,
			.alpha_val[ 0 ]	= 0x00,
			.alpha_val[ 1 ]	= 0x00,
			.alpha_val[ 2 ]	= 0x00,
		},
#endif
	};

	for( loopcnt = 0; loopcnt < (sizeof(bld) / sizeof(bld[0])); loopcnt++ ) {
		ret = Im_SHDR_Set_Blend( &bld[ loopcnt ] );
		Ddim_Print(("ct_im_shdr_set_bld(%d)[ret=0x%08x]\n", loopcnt, ret));
	}
}

CtImShdrSet* ct_im_shdr_set_get(void)
{
	static CtImShdrSet* self = NULL;

	if (!self) {
		self = k_object_new_with_private(CT_TYPE_IM_SHDR_SET, sizeof(CtImShdrSetPrivate));
	}

	return self;
}
