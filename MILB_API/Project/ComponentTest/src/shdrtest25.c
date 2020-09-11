/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : maoguangkun
*@brief : ShdrTest25
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
#include "shdrtest21.h"
#include "ctimshdrtools.h"
#include "shdrtest25.h"


K_TYPE_DEFINE_WITH_PRIVATE(ShdrTest25, shdr_test2_5)
#define SHDR_TEST2_5_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), ShdrTest25Private, SHDR_TYPE_TEST2_5))


struct _ShdrTest25Private
{

};


/********
 * IMPL
 */
static void shdr_test2_5_constructor(ShdrTest25 *self)
{
//	ShdrTest25Private *priv = SHDR_TEST2_5_GET_PRIVATE(self);
}

static void shdr_test2_5_destructor(ShdrTest25 *self)
{
//	ShdrTest25Private *priv = SHDR_TEST2_5_GET_PRIVATE(self);
}


/**********
 * PUBLIC
 */
VOID ct_im_shdr_test2_5(ShdrTest25* self)
{
	TImShdrParam	shdr_param = {
		.ctrl = {
			.image_set.in_bit_depth		= D_IM_SHDR_INBITDEPTH_8,
			.image_set.in_c_fmt			= D_IM_SHDR_INCFMT_420SP,		// 420sp in.
			.image_set.in_edge_cpy		= D_IM_SHDR_OFF,
			.image_set.in_edge_cut		= D_IM_SHDR_OFF,
			.image_set.out_ctrl			= D_IM_SHDR_OUTCTRL_YCC,
			.image_set.out_sel			= D_IM_SHDR_OUTSEL_YCC_16,
			.image_set.out_sel_en		= D_IM_SHDR_DISABLE,
			.image_mode.exp_mag			= 0x0100,
			.image_mode.fil_margin		= D_IM_SHDR_FLITER_MARGIN_32,	// 32pixel.
			.image_mode.rexp_mag_shift	= 0,
			.image_mode.rexp_mag		= 0x00000,
			.image_mode.shift_x			= 0x0000,
			.image_mode.shift_y			= 0x0000,
			.image_mode.fmd_en			= D_IM_SHDR_DISABLE,
			.image_mode.bypass_en		= D_IM_SHDR_ENABLE,
			.image_mode.smc_in			= D_IM_SHDR_SMCIN_STN_REF,
			.image_mode.shdr_in			= D_IM_SHDR_SHDRIN_STN_REF,
			.image_mode.tile_size		= D_IM_SHDR_TILESIZE_1024x1024,
			.sdram.r_addr.a_y			= 0x00000000,
			.sdram.r_addr.a_c			= 0x00000000,
			.sdram.r_addr.b_y			= CtImShdr_D_IM_SHDR_IMG_MEM_IN_YCC_REF_ADDR_Y,
			.sdram.r_addr.b_c			= CtImShdr_D_IM_SHDR_IMG_MEM_IN_YCC_REF_ADDR_C,
			.sdram.r_addr.c_y			= 0x00000000,
			.sdram.r_addr.c_c			= 0x00000000,
			.sdram.r_addr.d_y			= 0x00000000,
			.sdram.r_addr.d_c			= 0x00000000,
			.sdram.r_addr.e_y			= 0x00000000,
			.sdram.r_addr.e_c			= 0x00000000,
			.sdram.r_addr.f				= 0x00000000,
			.sdram.r_ghsize.a_y			= 0x0000,
			.sdram.r_ghsize.a_c			= 0x0000,
			.sdram.r_ghsize.b_y			= CtImShdr_D_IM_SHDR_SRC_IMG_PIXS_WIDTH_YCC_4K2K_REF,
			.sdram.r_ghsize.b_c			= CtImShdr_D_IM_SHDR_SRC_IMG_PIXS_WIDTH_YCC_4K2K_REF,
			.sdram.r_ghsize.c_y			= 0x0000,
			.sdram.r_ghsize.c_c			= 0x0000,
			.sdram.r_ghsize.d_y			= 0x0000,
			.sdram.r_ghsize.d_c			= 0x0000,
			.sdram.r_ghsize.e_y			= 0x0000,
			.sdram.r_ghsize.e_c			= 0x0000,
			.sdram.r_ghsize.f			= 0x0000,
			.sdram.r_hsize.a			= 0x0000,
			.sdram.r_hsize.b			= CtImShdr_D_IM_SHDR_SRC_IMG_PIXS_WIDTH_YCC_4K2K_REF,
			.sdram.r_hsize.c			= 0x0000,
			.sdram.r_hsize.d			= 0x0000,
			.sdram.r_hsize.e			= 0x0000,
			.sdram.r_vsize.a			= 0x0000,
			.sdram.r_vsize.b			= CtImShdr_D_IM_SHDR_SRC_IMG_PIXS_LINES_YCC_4K2K_REF,
			.sdram.r_vsize.c			= 0x0000,
			.sdram.r_vsize.d			= 0x0000,
			.sdram.r_vsize.e			= 0x0000,
			.sdram.r_vfm.a				= D_IM_SHDR_VFMT_RASTER,
			.sdram.w_addr.b_y			= CtImShdr_D_IM_SHDR_IMG_MEM_OUT_MEIN_ADDR_Y,
			.sdram.w_addr.b_c			= CtImShdr_D_IM_SHDR_IMG_MEM_OUT_MEIN_ADDR_C,
			.sdram.w_addr.e_y			= CtImShdr_D_IM_SHDR_IMG_MEM_OUT_DISP_HDMI_ADDR_Y,
			.sdram.w_addr.e_c			= CtImShdr_D_IM_SHDR_IMG_MEM_OUT_DISP_HDMI_ADDR_C,
			.sdram.w_addr.f_y			= CtImShdr_D_IM_SHDR_IMG_MEM_OUT_DISP_LCD_ADDR_Y,
			.sdram.w_addr.f_c			= CtImShdr_D_IM_SHDR_IMG_MEM_OUT_DISP_LCD_ADDR_C,
			.sdram.w_addr.g_r_y			= 0x00000000,
			.sdram.w_addr.g_g_c			= 0x00000000,
			.sdram.w_addr.g_b			= 0x00000000,
			.sdram.w_addr.h_x			= 0x00000000,
			.sdram.w_addr.h_y			= 0x00000000,
			.sdram.w_addr.i				= 0x00000000,
			.sdram.w_ghsize.b_y			= CtImShdr_D_IM_SHDR_DST_IMG_PIXS_WIDTH_MEIN,
			.sdram.w_ghsize.b_c			= CtImShdr_D_IM_SHDR_DST_IMG_PIXS_WIDTH_MEIN,
			.sdram.w_ghsize.e_y			= CtImShdr_D_IM_SHDR_DST_IMG_PIXS_WIDTH_DISP_HDMI,
			.sdram.w_ghsize.e_c			= CtImShdr_D_IM_SHDR_DST_IMG_PIXS_WIDTH_DISP_HDMI,
			.sdram.w_ghsize.f_y			= CtImShdr_D_IM_SHDR_DST_IMG_PIXS_WIDTH_DISP_LCD,
			.sdram.w_ghsize.f_c			= CtImShdr_D_IM_SHDR_DST_IMG_PIXS_WIDTH_DISP_LCD,
			.sdram.w_ghsize.g_r_y		= 0x0000,
			.sdram.w_ghsize.g_g_c		= 0x0000,
			.sdram.w_ghsize.g_b			= 0x0000,
			.sdram.w_ghsize.h_x			= 0x0000,
			.sdram.w_ghsize.h_y			= 0x0000,
			.sdram.w_ghsize.i			= 0x0000,
			.sdram.w_vfm.a				= D_IM_SHDR_VFMT_COMPIP_VIDEO,
			.sdram.w_vfm.b				= D_IM_SHDR_VFMT_RASTER,
			.sdram.w_baddr.a_y			= CtImShdr_D_IM_SHDR_IMG_MEM_OUT_HEVC_ADDR_Y,
			.sdram.w_baddr.a_c			= CtImShdr_D_IM_SHDR_IMG_MEM_OUT_HEVC_ADDR_C,
			.sdram.w_baddr.c_y			= CtImShdr_D_IM_SHDR_IMG_MEM_OUT_RIB_FHD_ADDR_Y,
			.sdram.w_baddr.c_c			= CtImShdr_D_IM_SHDR_IMG_MEM_OUT_RIB_FHD_ADDR_C,
			.sdram.w_baddr.d_y			= CtImShdr_D_IM_SHDR_IMG_MEM_OUT_RIB_HD_ADDR_Y,
			.sdram.w_baddr.d_c			= CtImShdr_D_IM_SHDR_IMG_MEM_OUT_RIB_HD_ADDR_C,
			.sdram.w_hsize.a			= CtImShdr_D_IM_SHDR_IMG_MEM_HEVC_U8_Y_GLOBAL_WIDTH,
			.sdram.w_hsize.c			= CtImShdr_D_IM_SHDR_IMG_MEM_RIB_FHD_U8_Y_GLOBAL_WIDTH,
			.sdram.w_hsize.d			= CtImShdr_D_IM_SHDR_IMG_MEM_RIB_HD_U8_Y_GLOBAL_WIDTH,
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
		.pre = {
			.pre_mode.cus_mode			= D_IM_SHDR_CUS_YCC420_PADDING,
			.pre_mode.degamma_mode		= D_IM_SHDR_DEGAMMA_LUT,
			.y2r_coef[ 0 ] 				= 0x0000,
			.y2r_coef[ 1 ] 				= 0x0000,
			.y2r_coef[ 2 ] 				= 0x0000,
			.y2r_coef[ 3 ] 				= 0x0000,
			.y2r_coef[ 4 ] 				= 0x0000,
			.y2r_coef[ 5 ] 				= 0x0000,
			.y2r_coef[ 6 ] 				= 0x0000,
			.y2r_coef[ 7 ] 				= 0x0000,
			.y2r_coef[ 8 ] 				= 0x0000,
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
			.r2y_coef[ 0 ] 				= 0x0000,
			.r2y_coef[ 1 ] 				= 0x0000,
			.r2y_coef[ 2 ] 				= 0x0000,
			.r2y_coef[ 3 ] 				= 0x0000,
			.r2y_coef[ 4 ] 				= 0x0000,
			.r2y_coef[ 5 ] 				= 0x0000,
			.r2y_coef[ 6 ] 				= 0x0000,
			.r2y_coef[ 7 ] 				= 0x0000,
			.r2y_coef[ 8 ] 				= 0x0000,
			.r2y_clp.upper_long_y		= 0x0000,
			.r2y_clp.upper_long_c[ 0 ]	= 0x0000,
			.r2y_clp.upper_long_c[ 1 ]	= 0x0000,
			.r2y_clp.lower_long_y		= 0x0000,
			.r2y_clp.lower_long_c[ 0 ]	= 0x0000,
			.r2y_clp.lower_long_c[ 1 ]	= 0x0000,
			.r2y_clp.upper_short_y		= 0x000,
			.r2y_clp.upper_short_c[ 0 ]	= 0x000,
			.r2y_clp.upper_short_c[ 1 ]	= 0x000,
			.r2y_clp.lower_short_y		= 0x000,
			.r2y_clp.lower_short_c[ 0 ]	= 0x000,
			.r2y_clp.lower_short_c[ 1 ]	= 0x000,
			.short_knee.offset[ 0 ]		= 0x00,
			.short_knee.offset[ 1 ]		= 0x00,
			.short_knee.offset[ 2 ]		= 0x00,
			.short_knee.slope[ 0 ]		= 0x00,
			.short_knee.slope[ 1 ]		= 0x00,
			.short_knee.slope[ 2 ]		= 0x00,
			.short_knee.boundary[ 0 ]	= 0x000,
			.short_knee.boundary[ 0 ]	= 0x000,
			.long_knee.offset[ 0 ]		= 0x00,
			.long_knee.offset[ 1 ]		= 0x00,
			.long_knee.offset[ 2 ]		= 0x00,
			.long_knee.slope[ 0 ]		= 0x00,
			.long_knee.slope[ 1 ]		= 0x00,
			.long_knee.slope[ 2 ]		= 0x00,
			.long_knee.boundary[ 0 ]	= 0x000,
			.long_knee.boundary[ 0 ]	= 0x000,
		},
		.fmd = {
			.ep_boundary[ 0 ]			= 0x00,		// D.C.
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
			.mvcnt.gr					= 0x0000,
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
			.bldr_boundary[ 0 ]			= 0x00,		// D.C.
			.bldr_boundary[ 1 ]			= 0x00,
			.bldr_boundary[ 2 ]			= 0x00,
			.bldr_boundary[ 3 ]			= 0x00,
			.bldr_boundary[ 4 ]			= 0x00,
			.weight_r2y_coef[ 0 ]		= 0x0000,
			.weight_r2y_coef[ 1 ]		= 0x0000,
			.weight_r2y_coef[ 2 ]		= 0x0000,
			.weight_r2y_clp.upper		= 0x00,
			.weight_r2y_clp.lower		= 0x00,
			.weight_base				= 0x0,
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
			.weight_boundary[ 0 ][ 0 ]	= 0x00,		// D.C.
			.weight_boundary[ 0 ][ 1 ]	= 0x00,
			.weight_boundary[ 0 ][ 2 ]	= 0x00,
			.weight_boundary[ 0 ][ 3 ]	= 0x00,
			.weight_boundary[ 0 ][ 4 ]	= 0x00,
			.weight_boundary[ 1 ][ 0 ]	= 0x00,		// D.C.
			.weight_boundary[ 1 ][ 1 ]	= 0x00,
			.weight_boundary[ 1 ][ 2 ]	= 0x00,
			.weight_boundary[ 1 ][ 3 ]	= 0x00,
			.weight_boundary[ 1 ][ 4 ]	= 0x00,
			.weight_boundary[ 2 ][ 0 ]	= 0x00,		// D.C.
			.weight_boundary[ 2 ][ 1 ]	= 0x00,
			.weight_boundary[ 2 ][ 2 ]	= 0x00,
			.weight_boundary[ 2 ][ 3 ]	= 0x00,
			.weight_boundary[ 2 ][ 4 ]	= 0x00,
			.iso_threshold				= 0x000,
			.iso_coef[ 0 ]				= 0x1,
			.iso_coef[ 1 ]				= 0x1,
			.iso_coef[ 2 ]				= 0x1,
			.iso_coef[ 3 ]				= 0x01,
			.iso_coef[ 4 ]				= 0x01,
			.iso_coef[ 5 ]				= 0x01,
			.sat_threshold				= 0x00,
			.exp77_mode					= D_IM_SHDR_EXP77MD_COEFSUMDIV,
			.fmd_sel					= D_IM_SHDR_FMDSEL_EXPANSION,
		},
		.pmsk = {
			.tlut[ 0 ]					= 0x00,
			.tlut[ 1 ]					= 0x00,
			.tlut[ 2 ]					= 0x00,
			.tlut[ 3 ]					= 0x00,
			.tlut[ 4 ]					= 0x00,
			.tlut[ 5 ]					= 0x00,
			.tlut[ 6 ]					= 0x00,
			.tlut[ 7 ]					= 0x00,
			.tlut[ 8 ]					= 0x00,
			.tlut[ 9 ]					= 0x00,
			.tlut[ 10 ]					= 0x00,
			.tlut[ 11 ]					= 0x00,
			.tlut[ 12 ]					= 0x00,
			.tlut[ 13 ]					= 0x00,
			.tlut[ 14 ]					= 0x00,
			.tlut[ 15 ]					= 0x00,
			.tlut[ 16 ]					= 0x00,
			.pmsk_mode					= D_IM_SHDR_PMSKMD_MAX,
		},
		.spnr = {
			.spnr_en					= D_IM_SHDR_DISABLE,
			.spe_blend					= 0x0,
			.spe_boundary[ 0 ]			= 0x000,		// D.C.
			.spe_boundary[ 1 ]			= 0x000,
			.spe_boundary[ 2 ]			= 0x000,
			.spe_boundary[ 3 ]			= 0x000,
			.spe_offset[ 0 ]			= 0x000,
			.spe_offset[ 1 ]			= 0x000,
			.spe_offset[ 2 ]			= 0x000,
			.spe_offset[ 3 ]			= 0x000,
		},
		.msk = {
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
			.alpha						= 0x20,
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
			.blend_boundary[ 0 ]		= 0x000,		// D.C.
			.blend_boundary[ 1 ]		= 0x400,
			.blend_boundary[ 2 ]		= 0x700,
			.blend_boundary[ 3 ]		= 0x7C0,
			.blend_boundary[ 4 ]		= 0x940,
			.blend_boundary[ 5 ]		= 0xA00,
			.blend_boundary[ 6 ]		= 0xC00,
			.norm_gain[ 0 ]				= 0x00,
			.norm_gain[ 1 ]				= 0x00,
			.norm_gain[ 2 ]				= 0x00,
			.norm_offset[ 0 ]			= 0x00,
			.norm_offset[ 1 ]			= 0x00,
			.norm_offset[ 2 ]			= 0x00,
			.msk_mode					= D_IM_SHDR_MSKMD_SHORT,
		},
		.bld = {
			.blend_sel					= D_IM_SHDR_BLDSEL_SHORT_LONG,
			.alpha_sel					= D_IM_SHDR_ALPHASEL_MERGEMASK,
			.alpha_val[ 0 ]				= 0x00,
			.alpha_val[ 1 ]				= 0x00,
			.alpha_val[ 2 ]				= 0x00,
		},
		.post = {
			.sft1rnd.sft1rnd_en			= D_IM_SHDR_DISABLE,
			.y2r_coef[ 0 ]				= 0x0000,
			.y2r_coef[ 1 ]				= 0x0000,
			.y2r_coef[ 2 ]				= 0x0000,
			.y2r_coef[ 3 ]				= 0x0000,
			.y2r_coef[ 4 ]				= 0x0000,
			.y2r_coef[ 5 ]				= 0x0000,
			.y2r_coef[ 6 ]				= 0x0000,
			.y2r_coef[ 7 ]				= 0x0000,
			.y2r_coef[ 8 ]				= 0x0000,
			.y2r_clp_th_upper[ 0 ]		= 0x0000,
			.y2r_clp_th_upper[ 1 ]		= 0x0000,
			.y2r_clp_th_upper[ 2 ]		= 0x0000,
			.y2r_clp_th_lower[ 0 ]		= 0x0000,
			.y2r_clp_th_lower[ 1 ]		= 0x0000,
			.y2r_clp_th_lower[ 2 ]		= 0x0000,
			.ev_sel						= D_IM_SHDR_POSTSEL1_Y,
			.mulqpos					= D_IM_SHDR_POSTMULQPOS_Q5,
			.ev_kn_boundary[ 0 ]		= 0x000,		// D.C.
			.ev_kn_boundary[ 1 ]		= 0x000,
			.ev_kn_boundary[ 2 ]		= 0x000,
			.ev_kn_boundary[ 3 ]		= 0x000,
			.ev_kn_boundary[ 4 ]		= 0x000,
			.ev_kn_boundary[ 5 ]		= 0x000,
			.ev_kn_boundary[ 6 ]		= 0x000,
			.ev_kn_boundary[ 7 ]		= 0x000,
			.ev_kn_boundary[ 8 ]		= 0x000,
			.ev_kn_boundary[ 9 ]		= 0x000,
			.ev_kn_offset[ 0 ]			= 0x000,
			.ev_kn_offset[ 1 ]			= 0x0000,
			.ev_kn_offset[ 2 ]			= 0x0000,
			.ev_kn_offset[ 3 ]			= 0x0000,
			.ev_kn_offset[ 4 ]			= 0x0000,
			.ev_kn_offset[ 5 ]			= 0x0000,
			.ev_kn_offset[ 6 ]			= 0x0000,
			.ev_kn_offset[ 7 ]			= 0x0000,
			.ev_kn_offset[ 8 ]			= 0x0000,
			.ev_kn_offset[ 9 ]			= 0x0200,
			.ev_kn_slope[ 0 ]			= 0x0000,
			.ev_kn_slope[ 1 ]			= 0x0000,
			.ev_kn_slope[ 2 ]			= 0x0000,
			.ev_kn_slope[ 3 ]			= 0x0000,
			.ev_kn_slope[ 4 ]			= 0x0000,
			.ev_kn_slope[ 5 ]			= 0x0000,
			.ev_kn_slope[ 6 ]			= 0x0000,
			.ev_kn_slope[ 7 ]			= 0x0000,
			.ev_kn_slope[ 8 ]			= 0x0000,
			.ev_kn_slope[ 9 ]			= 0x0000,
			.css_sel					= D_IM_SHDR_POSTSEL0_BYPASS_YCC8,	// Bypass.
			.hdrcss_mode				= D_IM_SHDR_HDRCSSMD_YCC422_ODD,
		},
		.resize = {
			.chmode.a_w_en				= D_IM_SHDR_ENABLE,
			.chmode.a_drc_en			= D_IM_SHDR_DISABLE,
			.chmode.a_css_md			= D_IM_SHDR_CSSMD_YCC420_ODD,
			.chmode.b_w_en				= D_IM_SHDR_DISABLE,
			.chmode.b_rdc_md			= D_IM_RDCMD1_1_4,
			.chmode.b_css_md			= D_IM_SHDR_CSSMD_YCC420_ODD,
			.chmode.c_w_en				= D_IM_SHDR_ENABLE,
			.chmode.c_rsz_md			= D_IM_RSZMD_ODD1,
			.chmode.c_rdc_en			= D_IM_SHDR_DISABLE,
			.chmode.c_rdc_md			= D_IM_RDCMD_1_2,
			.chmode.c_trm_en			= D_IM_SHDR_DISABLE,
			.chmode.c_drc_en			= D_IM_SHDR_DISABLE,
			.chmode.c_css_md			= D_IM_SHDR_CSSMD_YCC420_ODD,
			.chmode.d_w_en				= D_IM_SHDR_ENABLE,
			.chmode.d_rsz_md			= D_IM_RSZMD_ODD1,
			.chmode.d_rdc_en			= D_IM_SHDR_ENABLE,
			.chmode.d_rdc_md			= D_IM_RDCMD_1_2,
			.chmode.d_trm_en			= D_IM_SHDR_DISABLE,
			.chmode.d_drc_en			= D_IM_SHDR_DISABLE,
			.chmode.d_css_md			= D_IM_SHDR_CSSMD_YCC420_ODD,
			.chmode.e_w_en				= D_IM_SHDR_ENABLE,
			.chmode.e_rsz_md			= D_IM_RSZMD_ODD1,
			.chmode.e_rdc_en			= D_IM_SHDR_ENABLE,
			.chmode.e_rdc_md			= D_IM_RDCMD_1_2,
			.chmode.e_trm_en			= D_IM_SHDR_DISABLE,
			.chmode.e_css_md			= D_IM_SHDR_CSSMD_YCC420_ODD,
			.chmode.f_w_en				= D_IM_SHDR_ENABLE,
			.chmode.f_rsz_md			= D_IM_RDCMD_1_4,
			.chmode.f_rdc_en			= D_IM_SHDR_ENABLE,
			.chmode.f_rdc_md			= D_IM_RDCMD_1_4,
			.chmode.f_trm_en			= D_IM_SHDR_DISABLE,
			.chmode.f_css_md			= D_IM_SHDR_CSSMD_YCC420_ODD,
			.woutsz.a_hsize				= CtImShdr_D_IM_SHDR_DST_IMG_PIXS_WIDTH_HEVC,		// 3840
			.woutsz.a_vsize				= CtImShdr_D_IM_SHDR_DST_IMG_PIXS_LINES_HEVC,		// 2160
			.woutsz.b_hsize				= CtImShdr_D_IM_SHDR_DST_IMG_PIXS_WIDTH_MEIN,		// 960
			.woutsz.b_vsize				= CtImShdr_D_IM_SHDR_DST_IMG_PIXS_LINES_MEIN,		// 540
			.woutsz.c_hsize				= CtImShdr_D_IM_SHDR_DST_IMG_PIXS_WIDTH_RIB_FHD,		// 1920
			.woutsz.c_vsize				= CtImShdr_D_IM_SHDR_DST_IMG_PIXS_LINES_RIB_FHD,		// 1080
			.woutsz.d_hsize				= CtImShdr_D_IM_SHDR_DST_IMG_PIXS_WIDTH_RIB_HD,		// 1280
			.woutsz.d_vsize				= CtImShdr_D_IM_SHDR_DST_IMG_PIXS_LINES_RIB_HD,		// 720
			.woutsz.e_hsize				= CtImShdr_D_IM_SHDR_DST_IMG_PIXS_WIDTH_DISP_HDMI,	// 1280
			.woutsz.e_vsize				= CtImShdr_D_IM_SHDR_DST_IMG_PIXS_LINES_DISP_HDMI,	// 720
			.woutsz.f_hsize				= CtImShdr_D_IM_SHDR_DST_IMG_PIXS_WIDTH_DISP_LCD,	// 640
			.woutsz.f_vsize				= CtImShdr_D_IM_SHDR_DST_IMG_PIXS_LINES_DISP_LCD,	// 360
			.rszhcnt.c_hsta				= 0x0000,
			.rszhcnt.c_hpit				= 0x7FFF,	// 50%
			.rszhcnt.d_hsta				= 0x0000,
			.rszhcnt.d_hpit				= 0x5FFF,	// 66.7%
			.rszhcnt.e_hsta				= 0x0000,
			.rszhcnt.e_hpit				= 0x5FFF,	// 66.7%
			.rszhcnt.f_hsta				= 0x0000,
			.rszhcnt.f_hpit				= 0x5FFF,	// 66.7%
			.rszvcnt.c_vsta				= 0x0000,
			.rszvcnt.c_vpit				= 0x7FFF,	// 50%
			.rszvcnt.d_vsta				= 0x0000,
			.rszvcnt.d_vpit				= 0x5FFF,	// 66.7%
			.rszvcnt.e_vsta				= 0x0000,
			.rszvcnt.e_vpit				= 0x5FFF,	// 66.7%
			.rszvcnt.f_vsta				= 0x0000,
			.rszvcnt.f_vpit				= 0x5FFF,	// 66.7%
			.trmsta.c_hsta				= 0x0000,
			.trmsta.c_vsta				= 0x0000,
			.trmsta.d_hsta				= 0x0000,
			.trmsta.d_vsta				= 0x0000,
			.trmsta.e_hsta				= 0x0000,
			.trmsta.e_vsta				= 0x0000,
			.trmsta.f_hsta				= 0x0000,
			.trmsta.f_vsta				= 0x0000,
			.drcofst.a_y				= 0x00,
			.drcofst.a_cb				= 0x00,
			.drcofst.a_cr				= 0x00,
			.drcofst.c_y				= 0x00,
			.drcofst.c_cb				= 0x00,
			.drcofst.c_cr				= 0x00,
			.drcofst.d_y				= 0x00,
			.drcofst.d_cb				= 0x00,
			.drcofst.d_cr				= 0x00,
			.drcgain.a_y				= 0x100,
			.drcgain.a_cb				= 0x80,
			.drcgain.a_cr				= 0x80,
			.drcgain.c_y				= 0x100,
			.drcgain.c_cb				= 0x80,
			.drcgain.c_cr				= 0x80,
			.drcgain.d_y				= 0x100,
			.drcgain.d_cb				= 0x80,
			.drcgain.d_cr				= 0x80,
			.drcclph.a_y				= 0xFF,
			.drcclph.a_cb				= 0x7F,
			.drcclph.a_cr				= 0x7F,
			.drcclph.c_y				= 0xFF,
			.drcclph.c_cb				= 0x7F,
			.drcclph.c_cr				= 0x7F,
			.drcclph.d_y				= 0xFF,
			.drcclph.d_cb				= 0x7F,
			.drcclph.d_cr				= 0x7F,
			.drcclpl.a_y				= 0x00,
			.drcclpl.a_cb				= 0x80,
			.drcclpl.a_cr				= 0x80,
			.drcclpl.c_y				= 0x00,
			.drcclpl.c_cb				= 0x80,
			.drcclpl.c_cr				= 0x80,
			.drcclpl.d_y				= 0x00,
			.drcclpl.d_cb				= 0x80,
			.drcclpl.d_cr				= 0x80,
		},
		.smc = {
			.mcarmd.mca_mode			= D_IM_MCAMD_MAX,
			.mcarmd.mcr_mode			= D_IM_MCRMD_STANDARD,
			.mcmpmd.mcmp_mode			= D_IM_SHDR_OFF,
			.mcmpmd.mvw_en				= D_IM_SHDR_DISABLE,
			.mmvval.mmv_x				= 0x00,
			.mmvval.mmv_y				= 0x00,
			.mmvrcnt.mmvro_x			= 0x00,
			.mmvrcnt.mmvro_y			= 0x00,
			.mmvrcnt.mmvrk_x			= 0x0,
			.mmvrcnt.mmvrk_y			= 0x0,
			.mdbcnt.mdb_x				= 0x0,
			.mdbcnt.mdb_y				= 0x0,
			.mdbrocnt.mdbro_x			= 0x00,
			.mdbrocnt.mdbro_y			= 0x00,
			.mdbrocnt.mdbrk_x			= 0x0,
			.mdbrocnt.mdbrk_y			= 0x0,
			.molrcnt.molr_sm			= 0x0,
			.molrcnt.molr_ss			= 0x0,
			.molrcnt.molr_o				= 0x0,
			.molrcnt.molr_k				= 0x0,
			.mcpcnt.mcpx_s				= 0x00,
			.mcpcnt.mcpx_o				= 0x00,
			.mcpcnt.mcpx_k				= 0x0,
			.mmcrcnt.mmcr_s				= 0x000,
			.mmcrcnt.mmcr_k				= 0x0,
			.molecnt.mole_s				= 0x000,
			.molecnt.mole_o				= 0x00,
			.molecnt.mole_k				= 0x0,
			.mmvecnt.mmve_s				= 0x000,
			.mmvecnt.mmve_o				= 0x00,
			.mmvecnt.mmve_k				= 0x0,
			.mcpxecnt.mcpxe_s			= 0x000,
			.mcpxecnt.mcpxe_o			= 0x00,
			.mcpxecnt.mcpxe_k			= 0x0,
			.mvlcnt.mvl_en				= D_IM_SHDR_DISABLE,
			.mvlcnt.mvl_threshold		= 0x00,
			.mvlcnt.mvl_count_threshold	= 0x00,
		},
		.axi = {
			.ax_mode.r_burst			= D_IM_SHDR_BURSTLEN_512,
			.ax_mode.w_burst			= D_IM_SHDR_BURSTLEN_512,
			.ax_mode.w_w_mask			= D_IM_SHDR_WWMASK_ON,
			.r_ctl.a_cahche[ 0 ]		= 0x0,
			.r_ctl.a_cahche[ 1 ]		= 0x0,
			.r_ctl.a_protect[ 0 ]		= 0x2,
			.r_ctl.a_protect[ 1 ]		= 0x2,
			.r_ctl.b_cahche[ 0 ]		= 0x0,
			.r_ctl.b_cahche[ 1 ]		= 0x0,
			.r_ctl.b_protect[ 0 ]		= 0x2,
			.r_ctl.b_protect[ 1 ]		= 0x2,
			.r_ctl.c_cahche[ 0 ]		= 0x0,
			.r_ctl.c_cahche[ 1 ]		= 0x0,
			.r_ctl.c_cahche[ 2 ]		= 0x0,
			.r_ctl.c_cahche[ 3 ]		= 0x0,
			.r_ctl.c_protect[ 0 ]		= 0x2,
			.r_ctl.c_protect[ 1 ]		= 0x2,
			.r_ctl.c_protect[ 2 ]		= 0x2,
			.r_ctl.c_protect[ 3 ]		= 0x2,
			.r_ctl.d_cahche[ 0 ]		= 0x0,
			.r_ctl.d_cahche[ 1 ]		= 0x0,
			.r_ctl.d_protect[ 0 ]		= 0x2,
			.r_ctl.d_protect[ 1 ]		= 0x2,
			.w_ctl.a_cahche[ 0 ]		= 0x0,
			.w_ctl.a_cahche[ 1 ]		= 0x0,
			.w_ctl.a_cahche[ 2 ]		= 0x0,
			.w_ctl.a_cahche[ 3 ]		= 0x0,
			.w_ctl.a_protect[ 0 ]		= 0x2,
			.w_ctl.a_protect[ 1 ]		= 0x2,
			.w_ctl.a_protect[ 2 ]		= 0x2,
			.w_ctl.a_protect[ 3 ]		= 0x2,
			.w_ctl.b_cahche[ 0 ]		= 0x0,
			.w_ctl.b_cahche[ 1 ]		= 0x0,
			.w_ctl.b_cahche[ 2 ]		= 0x0,
			.w_ctl.b_cahche[ 3 ]		= 0x0,
			.w_ctl.b_cahche[ 4 ]		= 0x0,
			.w_ctl.b_cahche[ 5 ]		= 0x0,
			.w_ctl.b_protect[ 0 ]		= 0x2,
			.w_ctl.b_protect[ 1 ]		= 0x2,
			.w_ctl.b_protect[ 2 ]		= 0x2,
			.w_ctl.b_protect[ 3 ]		= 0x2,
			.w_ctl.b_protect[ 4 ]		= 0x2,
			.w_ctl.b_protect[ 5 ]		= 0x2,
			.w_ctl.c_cahche[ 0 ]		= 0x0,
			.w_ctl.c_cahche[ 1 ]		= 0x0,
			.w_ctl.c_cahche[ 2 ]		= 0x0,
			.w_ctl.c_cahche[ 3 ]		= 0x0,
			.w_ctl.c_cahche[ 4 ]		= 0x0,
			.w_ctl.c_cahche[ 5 ]		= 0x0,
			.w_ctl.c_cahche[ 6 ]		= 0x0,
			.w_ctl.c_protect[ 0 ]		= 0x2,
			.w_ctl.c_protect[ 1 ]		= 0x2,
			.w_ctl.c_protect[ 2 ]		= 0x2,
			.w_ctl.c_protect[ 3 ]		= 0x2,
			.w_ctl.c_protect[ 4 ]		= 0x2,
			.w_ctl.c_protect[ 5 ]		= 0x2,
			.w_ctl.c_protect[ 6 ]		= 0x2,
		},
	};

	ct_im_shdr_test2_5_test(NULL, &shdr_param);
}

VOID ct_im_shdr_test2_5_test(ShdrTest25* self, TImShdrParam* shdr_param )
{
	INT32	ret;
	UINT32	wait_factor;

	Ddim_Print(("porocess 1\n"));
	ret = Im_SHDR_Open( 0 );
	if ( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_SHDR_Open[ret=0x%08x]\n", ret));
	}

	Ddim_Print(("porocess 2\n"));
	ret = Im_SHDR_Init( FALSE );
	if ( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_SHDR_Init[ret=0x%08x]\n", ret));
	}

	Ddim_Print(("porocess 3\n"));
	ret = Im_SHDR_Ctrl_Common( &shdr_param->ctrl );
	if ( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_SHDR_Ctrl_Common[ret=0x%08x]\n", ret));
	}

	Ddim_Print(("porocess 4\n"));
	ret = Im_SHDR_Set_Pre( &shdr_param->pre );
	if ( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_SHDR_Set_Pre[ret=0x%08x]\n", ret));
	}

	Ddim_Print(("porocess 5\n"));
	ret = Im_SHDR_Set_Fmd( &shdr_param->fmd );
	if ( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_SHDR_Set_Fmd[ret=0x%08x]\n", ret));
	}

	Ddim_Print(("porocess 6\n"));
	ret = Im_SHDR_Set_PreMask( &shdr_param->pmsk );
	if ( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_SHDR_Set_PreMask[ret=0x%08x]\n", ret));
	}

	Ddim_Print(("porocess 7\n"));
	ret = Im_SHDR_Set_Spnr( &shdr_param->spnr );
	if ( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_SHDR_Set_Spnr[ret=0x%08x]\n", ret));
	}

	Ddim_Print(("porocess 8\n"));
	ret = Im_SHDR_Set_Mask( &shdr_param->msk );
	if ( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_SHDR_Set_Mask[ret=0x%08x]\n", ret));
	}

	Ddim_Print(("porocess 9\n"));
	ret = Im_SHDR_Set_Blend( &shdr_param->bld );
	if ( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_SHDR_Set_Blend[ret=0x%08x]\n", ret));
	}

	Ddim_Print(("porocess 10\n"));
	ret = Im_SHDR_Set_Post( &shdr_param->post );
	if ( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_SHDR_Set_Post[ret=0x%08x]\n", ret));
	}

	Ddim_Print(("porocess 11\n"));
	ret = Im_SHDR_Set_Resize( &shdr_param->resize );
	if ( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_SHDR_Set_Resize[ret=0x%08x]\n", ret));
	}

	Ddim_Print(("porocess 12\n"));
	ret = Im_SHDR_Set_Smc( &shdr_param->smc );
	if ( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_SHDR_Set_Smc[ret=0x%08x]\n", ret));
	}

	Ddim_Print(("porocess 13\n"));
	ret = Im_SHDR_Set_Axi( &shdr_param->axi );
	if ( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_SHDR_Set_Axi[ret=0x%08x]\n", ret));
	}

	Ddim_Print(("porocess 14\n"));
	ret = Im_SHDR_Start();
	if ( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_SHDR_Start[ret=0x%08x]\n", ret));
	}

	Ddim_Print(("porocess 15\n"));
	ret = Im_SHDR_Wait_End( &wait_factor, 1000 );
	if ( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_SHDR_Wait_End[ret=0x%08x]\n", ret));
	}

	Ddim_Print(("porocess 16\n"));
	ret = Im_SHDR_Close();
	if ( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_SHDR_Close[ret=0x%08x]\n", ret));
	}
}

ShdrTest25* shdr_test2_5_get(void)
{
	static ShdrTest25* self = NULL;

	if (!self) {
		self = k_object_new_with_private(SHDR_TYPE_TEST2_5, sizeof(ShdrTest25Private));
	}

	return self;
}
