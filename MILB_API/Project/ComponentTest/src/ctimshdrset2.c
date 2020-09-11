/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-03
*@author : maoguangkun
*@brief : CtImShdrSet2
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
#include "ctimshdrset2.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImShdrSet2, ct_im_shdr_set2)
#define CT_IM_SHDR_SET2_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImShdrSet2Private, CT_TYPE_IM_SHDR_SET2))


struct _CtImShdrSet2Private
{

};


/********
 * IMPL
 */
static void ct_im_shdr_set2_constructor(CtImShdrSet2 *self)
{
//	CtImShdrSet2Private *priv = CT_IM_SHDR_SET2_GET_PRIVATE(self);
}

static void ct_im_shdr_set2_destructor(CtImShdrSet2 *self)
{
//	CtImShdrSet2Private *priv = CT_IM_SHDR_SET2_GET_PRIVATE(self);
}


/**********
 * PUBLIC
 */
VOID ct_im_shdr_set2_get_ctrl(CtImShdrSet2* self)
{
	INT32			ret;
	T_IM_SHDR_CTRL	shdr_ctrl;

	ret = Im_SHDR_Get_Ctrl_Common( &shdr_ctrl );

	Ddim_Print(("ct_im_shdr_set2_get_ctrl[ret=0x%08x]\n", ret));
	Ddim_Print(("shdr_ctrl.image_set.in_bit_depth = 0x%08x\n",		shdr_ctrl.image_set.in_bit_depth	));
	Ddim_Print(("shdr_ctrl.image_set.in_c_fmt     = 0x%08x\n",		shdr_ctrl.image_set.in_c_fmt		));
	Ddim_Print(("shdr_ctrl.image_set.in_edge_cpy  = 0x%08x\n",		shdr_ctrl.image_set.in_edge_cpy		));
	Ddim_Print(("shdr_ctrl.image_set.in_edge_cut  = 0x%08x\n",		shdr_ctrl.image_set.in_edge_cut		));
	Ddim_Print(("shdr_ctrl.image_set.out_ctrl     = 0x%08x\n",		shdr_ctrl.image_set.out_ctrl 		));
	Ddim_Print(("shdr_ctrl.image_set.out_sel      = 0x%08x\n",		shdr_ctrl.image_set.out_sel			));
	Ddim_Print(("shdr_ctrl.image_set.out_sel_en   = 0x%08x\n",		shdr_ctrl.image_set.out_sel_en		));
	Ddim_Print(("shdr_ctrl.sdram.r_addr.a_y = 0x%08lx\n",			shdr_ctrl.sdram.r_addr.a_y			));
	Ddim_Print(("shdr_ctrl.sdram.r_addr.a_c = 0x%08lx\n",			shdr_ctrl.sdram.r_addr.a_c			));
	Ddim_Print(("shdr_ctrl.sdram.r_addr.b_y = 0x%08lx\n",			shdr_ctrl.sdram.r_addr.b_y			));
	Ddim_Print(("shdr_ctrl.sdram.r_addr.b_c = 0x%08lx\n",			shdr_ctrl.sdram.r_addr.b_c			));
	Ddim_Print(("shdr_ctrl.sdram.r_addr.c_y = 0x%08lx\n",			shdr_ctrl.sdram.r_addr.c_y			));
	Ddim_Print(("shdr_ctrl.sdram.r_addr.c_c = 0x%08lx\n",			shdr_ctrl.sdram.r_addr.c_c			));
	Ddim_Print(("shdr_ctrl.sdram.r_addr.d_y = 0x%08lx\n",			shdr_ctrl.sdram.r_addr.d_y			));
	Ddim_Print(("shdr_ctrl.sdram.r_addr.d_c = 0x%08lx\n",			shdr_ctrl.sdram.r_addr.d_c			));
	Ddim_Print(("shdr_ctrl.sdram.r_addr.e_y = 0x%08lx\n",			shdr_ctrl.sdram.r_addr.e_y			));
	Ddim_Print(("shdr_ctrl.sdram.r_addr.e_c = 0x%08lx\n",			shdr_ctrl.sdram.r_addr.e_c			));
	Ddim_Print(("shdr_ctrl.sdram.r_addr.f   = 0x%08lx\n",			shdr_ctrl.sdram.r_addr.f			));
	Ddim_Print(("shdr_ctrl.sdram.r_ghsize.a_y = 0x%08x\n",			shdr_ctrl.sdram.r_ghsize.a_y		));
	Ddim_Print(("shdr_ctrl.sdram.r_ghsize.a_c = 0x%08x\n",			shdr_ctrl.sdram.r_ghsize.a_c		));
	Ddim_Print(("shdr_ctrl.sdram.r_ghsize.b_y = 0x%08x\n",			shdr_ctrl.sdram.r_ghsize.b_y		));
	Ddim_Print(("shdr_ctrl.sdram.r_ghsize.b_c = 0x%08x\n",			shdr_ctrl.sdram.r_ghsize.b_c		));
	Ddim_Print(("shdr_ctrl.sdram.r_ghsize.c_y = 0x%08x\n",			shdr_ctrl.sdram.r_ghsize.c_y		));
	Ddim_Print(("shdr_ctrl.sdram.r_ghsize.c_c = 0x%08x\n",			shdr_ctrl.sdram.r_ghsize.c_c		));
	Ddim_Print(("shdr_ctrl.sdram.r_ghsize.d_y = 0x%08x\n",			shdr_ctrl.sdram.r_ghsize.d_y		));
	Ddim_Print(("shdr_ctrl.sdram.r_ghsize.d_c = 0x%08x\n",			shdr_ctrl.sdram.r_ghsize.d_c		));
	Ddim_Print(("shdr_ctrl.sdram.r_ghsize.e_y = 0x%08x\n",			shdr_ctrl.sdram.r_ghsize.e_y		));
	Ddim_Print(("shdr_ctrl.sdram.r_ghsize.e_c = 0x%08x\n",			shdr_ctrl.sdram.r_ghsize.e_c		));
	Ddim_Print(("shdr_ctrl.sdram.r_ghsize.f   = 0x%08x\n",			shdr_ctrl.sdram.r_ghsize.f			));
	Ddim_Print(("shdr_ctrl.sdram.r_vfm.a = 0x%08x\n",				shdr_ctrl.sdram.r_vfm.a				));
	Ddim_Print(("shdr_ctrl.sdram.r_hsize.a = 0x%08x\n",				shdr_ctrl.sdram.r_hsize.a			));
	Ddim_Print(("shdr_ctrl.sdram.r_hsize.b = 0x%08x\n",				shdr_ctrl.sdram.r_hsize.b			));
	Ddim_Print(("shdr_ctrl.sdram.r_hsize.c = 0x%08x\n",				shdr_ctrl.sdram.r_hsize.c			));
	Ddim_Print(("shdr_ctrl.sdram.r_hsize.d = 0x%08x\n",				shdr_ctrl.sdram.r_hsize.d			));
	Ddim_Print(("shdr_ctrl.sdram.r_hsize.e = 0x%08x\n",				shdr_ctrl.sdram.r_hsize.e			));
	Ddim_Print(("shdr_ctrl.sdram.r_vsize.a = 0x%08x\n",				shdr_ctrl.sdram.r_vsize.a			));
	Ddim_Print(("shdr_ctrl.sdram.r_vsize.b = 0x%08x\n",				shdr_ctrl.sdram.r_vsize.b			));
	Ddim_Print(("shdr_ctrl.sdram.r_vsize.c = 0x%08x\n",				shdr_ctrl.sdram.r_vsize.c			));
	Ddim_Print(("shdr_ctrl.sdram.r_vsize.d = 0x%08x\n",				shdr_ctrl.sdram.r_vsize.d			));
	Ddim_Print(("shdr_ctrl.sdram.r_vsize.e = 0x%08x\n",				shdr_ctrl.sdram.r_vsize.e			));
	Ddim_Print(("shdr_ctrl.sdram.w_addr.b_y   = 0x%08lx\n",			shdr_ctrl.sdram.w_addr.b_y			));
	Ddim_Print(("shdr_ctrl.sdram.w_addr.b_c   = 0x%08lx\n",			shdr_ctrl.sdram.w_addr.b_c			));
	Ddim_Print(("shdr_ctrl.sdram.w_addr.e_y   = 0x%08lx\n",			shdr_ctrl.sdram.w_addr.e_y			));
	Ddim_Print(("shdr_ctrl.sdram.w_addr.e_c   = 0x%08lx\n",			shdr_ctrl.sdram.w_addr.e_c			));
	Ddim_Print(("shdr_ctrl.sdram.w_addr.f_y   = 0x%08lx\n",			shdr_ctrl.sdram.w_addr.f_y			));
	Ddim_Print(("shdr_ctrl.sdram.w_addr.f_c   = 0x%08lx\n",			shdr_ctrl.sdram.w_addr.f_c			));
	Ddim_Print(("shdr_ctrl.sdram.w_addr.g_r_y = 0x%08lx\n",			shdr_ctrl.sdram.w_addr.g_r_y		));
	Ddim_Print(("shdr_ctrl.sdram.w_addr.g_g_c = 0x%08lx\n",			shdr_ctrl.sdram.w_addr.g_g_c		));
	Ddim_Print(("shdr_ctrl.sdram.w_addr.g_b   = 0x%08lx\n",			shdr_ctrl.sdram.w_addr.g_b			));
	Ddim_Print(("shdr_ctrl.sdram.w_addr.h_x   = 0x%08lx\n",			shdr_ctrl.sdram.w_addr.h_x			));
	Ddim_Print(("shdr_ctrl.sdram.w_addr.h_y   = 0x%08lx\n",			shdr_ctrl.sdram.w_addr.h_y			));
	Ddim_Print(("shdr_ctrl.sdram.w_addr.i     = 0x%08lx\n",			shdr_ctrl.sdram.w_addr.i			));
	Ddim_Print(("shdr_ctrl.sdram.w_ghsize.b_y   = 0x%08x\n",		shdr_ctrl.sdram.w_ghsize.b_y		));
	Ddim_Print(("shdr_ctrl.sdram.w_ghsize.b_c   = 0x%08x\n",		shdr_ctrl.sdram.w_ghsize.b_c		));
	Ddim_Print(("shdr_ctrl.sdram.w_ghsize.e_y   = 0x%08x\n",		shdr_ctrl.sdram.w_ghsize.e_y		));
	Ddim_Print(("shdr_ctrl.sdram.w_ghsize.e_c   = 0x%08x\n",		shdr_ctrl.sdram.w_ghsize.e_c		));
	Ddim_Print(("shdr_ctrl.sdram.w_ghsize.f_y   = 0x%08x\n",		shdr_ctrl.sdram.w_ghsize.f_y		));
	Ddim_Print(("shdr_ctrl.sdram.w_ghsize.f_c   = 0x%08x\n",		shdr_ctrl.sdram.w_ghsize.f_c		));
	Ddim_Print(("shdr_ctrl.sdram.w_ghsize.g_r_y = 0x%08x\n",		shdr_ctrl.sdram.w_ghsize.g_r_y		));
	Ddim_Print(("shdr_ctrl.sdram.w_ghsize.g_g_c = 0x%08x\n",		shdr_ctrl.sdram.w_ghsize.g_g_c		));
	Ddim_Print(("shdr_ctrl.sdram.w_ghsize.g_b   = 0x%08x\n",		shdr_ctrl.sdram.w_ghsize.g_b		));
	Ddim_Print(("shdr_ctrl.sdram.w_ghsize.h_x   = 0x%08x\n",		shdr_ctrl.sdram.w_ghsize.h_x		));
	Ddim_Print(("shdr_ctrl.sdram.w_ghsize.h_y   = 0x%08x\n",		shdr_ctrl.sdram.w_ghsize.h_y		));
	Ddim_Print(("shdr_ctrl.sdram.w_ghsize.i     = 0x%08x\n",		shdr_ctrl.sdram.w_ghsize.i			));
	Ddim_Print(("shdr_ctrl.sdram.w_vfm.a = 0x%08x\n",				shdr_ctrl.sdram.w_vfm.a				));
	Ddim_Print(("shdr_ctrl.sdram.w_vfm.b = 0x%08x\n",				shdr_ctrl.sdram.w_vfm.b				));
	Ddim_Print(("shdr_ctrl.sdram.w_baddr.a_y = 0x%08lx\n",			shdr_ctrl.sdram.w_baddr.a_y			));
	Ddim_Print(("shdr_ctrl.sdram.w_baddr.a_c = 0x%08lx\n",			shdr_ctrl.sdram.w_baddr.a_c			));
	Ddim_Print(("shdr_ctrl.sdram.w_baddr.c_y = 0x%08lx\n",			shdr_ctrl.sdram.w_baddr.c_y			));
	Ddim_Print(("shdr_ctrl.sdram.w_baddr.c_c = 0x%08lx\n",			shdr_ctrl.sdram.w_baddr.c_c			));
	Ddim_Print(("shdr_ctrl.sdram.w_baddr.d_y = 0x%08lx\n",			shdr_ctrl.sdram.w_baddr.d_y			));
	Ddim_Print(("shdr_ctrl.sdram.w_baddr.d_c = 0x%08lx\n",			shdr_ctrl.sdram.w_baddr.d_c			));
	Ddim_Print(("shdr_ctrl.sdram.w_hsize.a = 0x%08x\n",				shdr_ctrl.sdram.w_hsize.a			));
	Ddim_Print(("shdr_ctrl.sdram.w_hsize.c = 0x%08x\n",				shdr_ctrl.sdram.w_hsize.c			));
	Ddim_Print(("shdr_ctrl.sdram.w_hsize.d = 0x%08x\n",				shdr_ctrl.sdram.w_hsize.d			));
	Ddim_Print(("shdr_ctrl.compip.mode = 0x%08x\n",					shdr_ctrl.compip.mode				));
	Ddim_Print(("shdr_ctrl.compip.mc_mode = 0x%08x\n",				shdr_ctrl.compip.mc_mode			));
	Ddim_Print(("shdr_ctrl.compip.comp_incfmt = 0x%08x\n",			shdr_ctrl.compip.comp_incfmt		));
	Ddim_Print(("shdr_ctrl.compip.r_bypass_mode = 0x%08x\n",		shdr_ctrl.compip.r_bypass_mode		));
	Ddim_Print(("shdr_ctrl.compip.w_bypass_mode = 0x%08x\n",		shdr_ctrl.compip.w_bypass_mode		));
	Ddim_Print(("shdr_ctrl.compip.r_img_axi_size = 0x%08x\n",		shdr_ctrl.compip.r_img_axi_size		));
	Ddim_Print(("shdr_ctrl.compip.r_comp_axi_size = 0x%08x\n",		shdr_ctrl.compip.r_comp_axi_size	));
	Ddim_Print(("shdr_ctrl.compip.w_img_axi_size = 0x%08x\n",		shdr_ctrl.compip.w_img_axi_size		));
	Ddim_Print(("shdr_ctrl.compip.lint_no = 0x%08x\n",				shdr_ctrl.compip.lint_no			));
	Ddim_Print(("shdr_ctrl.compip.lint_mask = 0x%08x\n",			shdr_ctrl.compip.lint_mask			));
	Ddim_Print(("shdr_ctrl.compip.lint_sts = 0x%08x\n",				shdr_ctrl.compip.lint_sts			));
	Ddim_Print(("shdr_ctrl.compip.w_addr_y = 0x%08lx\n",			shdr_ctrl.compip.w_addr_y			));
	Ddim_Print(("shdr_ctrl.compip.w_addr_c = 0x%08lx\n",			shdr_ctrl.compip.w_addr_c			));
	Ddim_Print(("shdr_ctrl.compip.r_addr_y = 0x%08lx\n",			shdr_ctrl.compip.r_addr_y			));
	Ddim_Print(("shdr_ctrl.compip.r_addr_c = 0x%08lx\n",			shdr_ctrl.compip.r_addr_c			));
	Ddim_Print(("shdr_ctrl.image_mode.exp_mag = 0x%08x\n",			shdr_ctrl.image_mode.exp_mag		));
	Ddim_Print(("shdr_ctrl.image_mode.rexp_mag = 0x%08lx\n",		shdr_ctrl.image_mode.rexp_mag		));
	Ddim_Print(("shdr_ctrl.image_mode.rexp_mag_shift = 0x%08x\n",	shdr_ctrl.image_mode.rexp_mag_shift	));
	Ddim_Print(("shdr_ctrl.image_mode.shift_x = 0x%08x\n",			shdr_ctrl.image_mode.shift_x		));
	Ddim_Print(("shdr_ctrl.image_mode.shift_y = 0x%08x\n",			shdr_ctrl.image_mode.shift_y		));
	Ddim_Print(("shdr_ctrl.image_mode.fil_margin = 0x%08x\n",		shdr_ctrl.image_mode.fil_margin		));
	Ddim_Print(("shdr_ctrl.image_mode.fmd_en = 0x%08x\n",			shdr_ctrl.image_mode.fmd_en			));
	Ddim_Print(("shdr_ctrl.image_mode.bypass_en = 0x%08x\n",		shdr_ctrl.image_mode.bypass_en		));
	Ddim_Print(("shdr_ctrl.image_mode.smc_in = 0x%08x\n",			shdr_ctrl.image_mode.smc_in			));
	Ddim_Print(("shdr_ctrl.image_mode.shdr_in = 0x%08x\n",			shdr_ctrl.image_mode.shdr_in		));
	Ddim_Print(("shdr_ctrl.image_mode.tile_size = 0x%08x\n",		shdr_ctrl.image_mode.tile_size		));
}

VOID ct_im_shdr_set2_get_pre(CtImShdrSet2* self)
{
	INT32			ret;
	T_IM_SHDR_PRE	pre;

	ret = Im_SHDR_Get_Pre( &pre );

	Ddim_Print(("ct_im_shdr_get_pre[ret=0x%08x]\n", ret));
	Ddim_Print(("pre_mode.cus_mode = 0x%08x\n",				pre.pre_mode.cus_mode			));
	Ddim_Print(("pre_mode.degamma_mode = 0x%08x\n",			pre.pre_mode.degamma_mode		));
	Ddim_Print(("y2r_coef[ 0 ] = 0x%08x\n",					pre.y2r_coef[ 0 ]				));
	Ddim_Print(("y2r_coef[ 1 ] = 0x%08x\n",					pre.y2r_coef[ 1 ]				));
	Ddim_Print(("y2r_coef[ 2 ] = 0x%08x\n",					pre.y2r_coef[ 2 ]				));
	Ddim_Print(("y2r_coef[ 3 ] = 0x%08x\n",					pre.y2r_coef[ 3 ]				));
	Ddim_Print(("y2r_coef[ 4 ] = 0x%08x\n",					pre.y2r_coef[ 4 ]				));
	Ddim_Print(("y2r_coef[ 5 ] = 0x%08x\n",					pre.y2r_coef[ 5 ]				));
	Ddim_Print(("y2r_coef[ 6 ] = 0x%08x\n",					pre.y2r_coef[ 6 ]				));
	Ddim_Print(("y2r_coef[ 7 ] = 0x%08x\n",					pre.y2r_coef[ 7 ]				));
	Ddim_Print(("y2r_coef[ 8 ] = 0x%08x\n",					pre.y2r_coef[ 8 ]				));
	Ddim_Print(("y2r_clp.upper_long0[ 0 ] = 0x%08x\n",		pre.y2r_clp.upper_long0[ 0 ]	));
	Ddim_Print(("y2r_clp.upper_long0[ 1 ] = 0x%08x\n",		pre.y2r_clp.upper_long0[ 1 ]	));
	Ddim_Print(("y2r_clp.upper_long0[ 2 ] = 0x%08x\n",		pre.y2r_clp.upper_long0[ 2 ]	));
	Ddim_Print(("y2r_clp.lower_long0[ 0 ] = 0x%08x\n",		pre.y2r_clp.lower_long0[ 0 ]	));
	Ddim_Print(("y2r_clp.lower_long0[ 1 ] = 0x%08x\n",		pre.y2r_clp.lower_long0[ 1 ]	));
	Ddim_Print(("y2r_clp.lower_long0[ 2 ] = 0x%08x\n",		pre.y2r_clp.lower_long0[ 2 ]	));
	Ddim_Print(("y2r_clp.upper_short[ 0 ] = 0x%08x\n",		pre.y2r_clp.upper_short[ 0 ]	));
	Ddim_Print(("y2r_clp.upper_short[ 1 ] = 0x%08x\n",		pre.y2r_clp.upper_short[ 1 ]	));
	Ddim_Print(("y2r_clp.upper_short[ 2 ] = 0x%08x\n",		pre.y2r_clp.upper_short[ 2 ]	));
	Ddim_Print(("y2r_clp.lower_short[ 0 ] = 0x%08x\n",		pre.y2r_clp.lower_short[ 0 ]	));
	Ddim_Print(("y2r_clp.lower_short[ 1 ] = 0x%08x\n",		pre.y2r_clp.lower_short[ 1 ]	));
	Ddim_Print(("y2r_clp.lower_short[ 2 ] = 0x%08x\n",		pre.y2r_clp.lower_short[ 2 ]	));
	Ddim_Print(("r2y_coef[ 0 ] = 0x%08x\n",					pre.r2y_coef[ 0 ]				));
	Ddim_Print(("r2y_coef[ 1 ] = 0x%08x\n",					pre.r2y_coef[ 1 ]				));
	Ddim_Print(("r2y_coef[ 2 ] = 0x%08x\n",					pre.r2y_coef[ 2 ]				));
	Ddim_Print(("r2y_coef[ 3 ] = 0x%08x\n",					pre.r2y_coef[ 3 ]				));
	Ddim_Print(("r2y_coef[ 4 ] = 0x%08x\n",					pre.r2y_coef[ 4 ]				));
	Ddim_Print(("r2y_coef[ 5 ] = 0x%08x\n",					pre.r2y_coef[ 5 ]				));
	Ddim_Print(("r2y_coef[ 6 ] = 0x%08x\n",					pre.r2y_coef[ 6 ]				));
	Ddim_Print(("r2y_coef[ 7 ] = 0x%08x\n",					pre.r2y_coef[ 7 ]				));
	Ddim_Print(("r2y_coef[ 8 ] = 0x%08x\n",					pre.r2y_coef[ 8 ]				));
	Ddim_Print(("r2y_clp.upper_long_y  = 0x%08x\n",			pre.r2y_clp.upper_long_y		));
	Ddim_Print(("r2y_clp.upper_long_c[ 0 ] = 0x%08x\n",		pre.r2y_clp.upper_long_c[ 0 ]	));
	Ddim_Print(("r2y_clp.upper_long_c[ 1 ] = 0x%08x\n",		pre.r2y_clp.upper_long_c[ 1 ]	));
	Ddim_Print(("r2y_clp.lower_long_y = 0x%08x\n",			pre.r2y_clp.lower_long_y		));
	Ddim_Print(("r2y_clp.lower_long_c[ 0 ] = 0x%08x\n",		pre.r2y_clp.lower_long_c[ 0 ]	));
	Ddim_Print(("r2y_clp.lower_long_c[ 1 ] = 0x%08x\n",		pre.r2y_clp.lower_long_c[ 1 ]	));
	Ddim_Print(("r2y_clp.upper_short_y = 0x%08x\n",			pre.r2y_clp.upper_short_y		));
	Ddim_Print(("r2y_clp.upper_short_c[ 0 ] = 0x%08x\n",	pre.r2y_clp.upper_short_c[ 0 ]	));
	Ddim_Print(("r2y_clp.upper_short_c[ 1 ] = 0x%08x\n",	pre.r2y_clp.upper_short_c[ 1 ]	));
	Ddim_Print(("r2y_clp.lower_short_y = 0x%08x\n",			pre.r2y_clp.lower_short_y		));
	Ddim_Print(("r2y_clp.lower_short_c[ 0 ] = 0x%08x\n",	pre.r2y_clp.lower_short_c[ 0 ]	));
	Ddim_Print(("r2y_clp.lower_short_c[ 1 ] = 0x%08x\n",	pre.r2y_clp.lower_short_c[ 1 ]	));
	Ddim_Print(("short_knee.offset[ 0 ] = 0x%08x\n",		pre.short_knee.offset[ 0 ]		));
	Ddim_Print(("short_knee.offset[ 1 ] = 0x%08x\n",		pre.short_knee.offset[ 1 ]		));
	Ddim_Print(("short_knee.offset[ 2 ] = 0x%08x\n",		pre.short_knee.offset[ 2 ]		));
	Ddim_Print(("short_knee.slope[ 0 ] = 0x%08x\n",			pre.short_knee.slope[ 0 ]		));
	Ddim_Print(("short_knee.slope[ 1 ] = 0x%08x\n",			pre.short_knee.slope[ 1 ]		));
	Ddim_Print(("short_knee.slope[ 2 ] = 0x%08x\n",			pre.short_knee.slope[ 2 ]		));
	Ddim_Print(("short_knee.boundary[ 0 ] = 0x%08x\n",		pre.short_knee.boundary[ 0 ]	));
	Ddim_Print(("short_knee.boundary[ 1 ] = 0x%08x\n",		pre.short_knee.boundary[ 1 ]	));
	Ddim_Print(("long_knee.offset[ 0 ] = 0x%08x\n",			pre.long_knee.offset[ 0 ]		));
	Ddim_Print(("long_knee.offset[ 1 ] = 0x%08x\n",			pre.long_knee.offset[ 1 ]		));
	Ddim_Print(("long_knee.offset[ 2 ] = 0x%08x\n",			pre.long_knee.offset[ 2 ]		));
	Ddim_Print(("long_knee.slope[ 0 ] = 0x%08x\n",			pre.long_knee.slope[ 0 ]		));
	Ddim_Print(("long_knee.slope[ 1 ] = 0x%08x\n",			pre.long_knee.slope[ 1 ]		));
	Ddim_Print(("long_knee.slope[ 2 ] = 0x%08x\n",			pre.long_knee.slope[ 2 ]		));
	Ddim_Print(("long_knee.boundary[ 0 ] = 0x%08x\n",		pre.long_knee.boundary[ 0 ]		));
	Ddim_Print(("long_knee.boundary[ 1 ] = 0x%08x\n",		pre.long_knee.boundary[ 1 ]		));
}

VOID ct_im_shdr_set2_get_fmd(CtImShdrSet2* self)
{
	INT32			ret;
	T_IM_SHDR_FMD	fmd;

	ret = Im_SHDR_Get_Fmd( &fmd );

	Ddim_Print(("ct_im_shdr_get_fmd[ret=0x%08x]\n", ret));
	Ddim_Print(("ep_boundary[ 0 ]			= 0x%08x\n",	fmd.ep_boundary[ 0 ]			));
	Ddim_Print(("ep_boundary[ 1 ]			= 0x%08x\n",	fmd.ep_boundary[ 1 ]			));
	Ddim_Print(("ep_boundary[ 2 ]			= 0x%08x\n",	fmd.ep_boundary[ 2 ]			));
	Ddim_Print(("ep_boundary[ 3 ]			= 0x%08x\n",	fmd.ep_boundary[ 3 ]			));
	Ddim_Print(("ep_offset[ 0 ]				= 0x%08x\n",	fmd.ep_offset[ 0 ]				));
	Ddim_Print(("ep_offset[ 1 ]				= 0x%08x\n",	fmd.ep_offset[ 1 ]				));
	Ddim_Print(("ep_offset[ 2 ]				= 0x%08x\n",	fmd.ep_offset[ 2 ]				));
	Ddim_Print(("ep_offset[ 3 ]				= 0x%08x\n",	fmd.ep_offset[ 3 ]				));
	Ddim_Print(("ep_blend					= 0x%08x\n",	fmd.ep_blend					));
	Ddim_Print(("fd_weight					= 0x%08x\n",	fmd.fd_weight					));
	Ddim_Print(("mvcnt.bounds				= 0x%08x\n",	fmd.mvcnt.bounds				));
	Ddim_Print(("mvcnt.threshold			= 0x%08x\n",	fmd.mvcnt.threshold				));
	Ddim_Print(("mvcnt.gr					= 0x%08x\n",	fmd.mvcnt.gr					));
	Ddim_Print(("bldr_offset[ 0 ]			= 0x%08x\n",	fmd.bldr_offset[ 0 ]			));
	Ddim_Print(("bldr_offset[ 1 ]			= 0x%08x\n",	fmd.bldr_offset[ 1 ]			));
	Ddim_Print(("bldr_offset[ 2 ]			= 0x%08x\n",	fmd.bldr_offset[ 2 ]			));
	Ddim_Print(("bldr_offset[ 3 ]			= 0x%08x\n",	fmd.bldr_offset[ 3 ]			));
	Ddim_Print(("bldr_offset[ 4 ]			= 0x%08x\n",	fmd.bldr_offset[ 4 ]			));
	Ddim_Print(("bldr_slope[ 0 ]			= 0x%08x\n",	fmd.bldr_slope[ 0 ]				));
	Ddim_Print(("bldr_slope[ 1 ]			= 0x%08x\n",	fmd.bldr_slope[ 1 ]				));
	Ddim_Print(("bldr_slope[ 2 ]			= 0x%08x\n",	fmd.bldr_slope[ 2 ]				));
	Ddim_Print(("bldr_slope[ 3 ]			= 0x%08x\n",	fmd.bldr_slope[ 3 ]				));
	Ddim_Print(("bldr_slope[ 4 ]			= 0x%08x\n",	fmd.bldr_slope[ 4 ]				));
	Ddim_Print(("bldr_boundary[ 0 ]			= 0x%08x\n",	fmd.bldr_boundary[ 0 ]			));
	Ddim_Print(("bldr_boundary[ 1 ]			= 0x%08x\n",	fmd.bldr_boundary[ 1 ]			));
	Ddim_Print(("bldr_boundary[ 2 ]			= 0x%08x\n",	fmd.bldr_boundary[ 2 ]			));
	Ddim_Print(("bldr_boundary[ 3 ]			= 0x%08x\n",	fmd.bldr_boundary[ 3 ]			));
	Ddim_Print(("bldr_boundary[ 4 ]			= 0x%08x\n",	fmd.bldr_boundary[ 4 ]			));
	Ddim_Print(("weight_r2y_coef[ 0 ]		= 0x%08x\n",	fmd.weight_r2y_coef[ 0 ]		));
	Ddim_Print(("weight_r2y_coef[ 1 ]		= 0x%08x\n",	fmd.weight_r2y_coef[ 1 ]		));
	Ddim_Print(("weight_r2y_coef[ 2 ]		= 0x%08x\n",	fmd.weight_r2y_coef[ 2 ]		));
	Ddim_Print(("weight_r2y_clp.upper		= 0x%08x\n",	fmd.weight_r2y_clp.upper		));
	Ddim_Print(("weight_r2y_clp.lower		= 0x%08x\n",	fmd.weight_r2y_clp.lower		));
	Ddim_Print(("weight_base				= 0x%08x\n",	fmd.weight_base					));
	Ddim_Print(("weight_offset[ 0 ][ 0 ]	= 0x%08x\n",	fmd.weight_offset[ 0 ][ 0 ]		));
	Ddim_Print(("weight_offset[ 0 ][ 1 ]	= 0x%08x\n",	fmd.weight_offset[ 0 ][ 1 ]		));
	Ddim_Print(("weight_offset[ 0 ][ 2 ]	= 0x%08x\n",	fmd.weight_offset[ 0 ][ 2 ]		));
	Ddim_Print(("weight_offset[ 0 ][ 3 ]	= 0x%08x\n",	fmd.weight_offset[ 0 ][ 3 ]		));
	Ddim_Print(("weight_offset[ 0 ][ 4 ]	= 0x%08x\n",	fmd.weight_offset[ 0 ][ 4 ]		));
	Ddim_Print(("weight_offset[ 1 ][ 0 ]	= 0x%08x\n",	fmd.weight_offset[ 1 ][ 0 ]		));
	Ddim_Print(("weight_offset[ 1 ][ 1 ]	= 0x%08x\n",	fmd.weight_offset[ 1 ][ 1 ]		));
	Ddim_Print(("weight_offset[ 1 ][ 2 ]	= 0x%08x\n",	fmd.weight_offset[ 1 ][ 2 ]		));
	Ddim_Print(("weight_offset[ 1 ][ 3 ]	= 0x%08x\n",	fmd.weight_offset[ 1 ][ 3 ]		));
	Ddim_Print(("weight_offset[ 1 ][ 4 ]	= 0x%08x\n",	fmd.weight_offset[ 1 ][ 4 ]		));
	Ddim_Print(("weight_offset[ 2 ][ 0 ]	= 0x%08x\n",	fmd.weight_offset[ 2 ][ 0 ]		));
	Ddim_Print(("weight_offset[ 2 ][ 1 ]	= 0x%08x\n",	fmd.weight_offset[ 2 ][ 1 ]		));
	Ddim_Print(("weight_offset[ 2 ][ 2 ]	= 0x%08x\n",	fmd.weight_offset[ 2 ][ 2 ]		));
	Ddim_Print(("weight_offset[ 2 ][ 3 ]	= 0x%08x\n",	fmd.weight_offset[ 2 ][ 3 ]		));
	Ddim_Print(("weight_offset[ 2 ][ 4 ]	= 0x%08x\n",	fmd.weight_offset[ 2 ][ 4 ]		));
	Ddim_Print(("weight_slope[ 0 ][ 0 ]		= 0x%08x\n",	fmd.weight_slope[ 0 ][ 0 ]		));
	Ddim_Print(("weight_slope[ 0 ][ 1 ]		= 0x%08x\n",	fmd.weight_slope[ 0 ][ 1 ]		));
	Ddim_Print(("weight_slope[ 0 ][ 2 ]		= 0x%08x\n",	fmd.weight_slope[ 0 ][ 2 ]		));
	Ddim_Print(("weight_slope[ 0 ][ 3 ]		= 0x%08x\n",	fmd.weight_slope[ 0 ][ 3 ]		));
	Ddim_Print(("weight_slope[ 0 ][ 4 ]		= 0x%08x\n",	fmd.weight_slope[ 0 ][ 4 ]		));
	Ddim_Print(("weight_slope[ 1 ][ 0 ]		= 0x%08x\n",	fmd.weight_slope[ 1 ][ 0 ]		));
	Ddim_Print(("weight_slope[ 1 ][ 1 ]		= 0x%08x\n",	fmd.weight_slope[ 1 ][ 1 ]		));
	Ddim_Print(("weight_slope[ 1 ][ 2 ]		= 0x%08x\n",	fmd.weight_slope[ 1 ][ 2 ]		));
	Ddim_Print(("weight_slope[ 1 ][ 3 ]		= 0x%08x\n",	fmd.weight_slope[ 1 ][ 3 ]		));
	Ddim_Print(("weight_slope[ 1 ][ 4 ]		= 0x%08x\n",	fmd.weight_slope[ 1 ][ 4 ]		));
	Ddim_Print(("weight_slope[ 2 ][ 0 ]		= 0x%08x\n",	fmd.weight_slope[ 2 ][ 0 ]		));
	Ddim_Print(("weight_slope[ 2 ][ 1 ]		= 0x%08x\n",	fmd.weight_slope[ 2 ][ 1 ]		));
	Ddim_Print(("weight_slope[ 2 ][ 2 ]		= 0x%08x\n",	fmd.weight_slope[ 2 ][ 2 ]		));
	Ddim_Print(("weight_slope[ 2 ][ 3 ]		= 0x%08x\n",	fmd.weight_slope[ 2 ][ 3 ]		));
	Ddim_Print(("weight_slope[ 2 ][ 4 ]		= 0x%08x\n",	fmd.weight_slope[ 2 ][ 4 ]		));
//	Ddim_Print(("weight_boundary[ 0 ][ 0 ]	= 0x%08x\n",	fmd.weight_boundary[ 0 ][ 0 ]	));
	Ddim_Print(("weight_boundary[ 0 ][ 1 ]	= 0x%08x\n",	fmd.weight_boundary[ 0 ][ 1 ]	));
	Ddim_Print(("weight_boundary[ 0 ][ 2 ]	= 0x%08x\n",	fmd.weight_boundary[ 0 ][ 2 ]	));
	Ddim_Print(("weight_boundary[ 0 ][ 3 ]	= 0x%08x\n",	fmd.weight_boundary[ 0 ][ 3 ]	));
	Ddim_Print(("weight_boundary[ 0 ][ 4 ]	= 0x%08x\n",	fmd.weight_boundary[ 0 ][ 4 ]	));
//	Ddim_Print(("weight_boundary[ 1 ][ 0 ]	= 0x%08x\n",	fmd.weight_boundary[ 1 ][ 0 ]	));
	Ddim_Print(("weight_boundary[ 1 ][ 1 ]	= 0x%08x\n",	fmd.weight_boundary[ 1 ][ 1 ]	));
	Ddim_Print(("weight_boundary[ 1 ][ 2 ]	= 0x%08x\n",	fmd.weight_boundary[ 1 ][ 2 ]	));
	Ddim_Print(("weight_boundary[ 1 ][ 3 ]	= 0x%08x\n",	fmd.weight_boundary[ 1 ][ 3 ]	));
	Ddim_Print(("weight_boundary[ 1 ][ 4 ]	= 0x%08x\n",	fmd.weight_boundary[ 1 ][ 4 ]	));
//	Ddim_Print(("weight_boundary[ 2 ][ 0 ]	= 0x%08x\n",	fmd.weight_boundary[ 2 ][ 0 ]	));
	Ddim_Print(("weight_boundary[ 2 ][ 1 ]	= 0x%08x\n",	fmd.weight_boundary[ 2 ][ 1 ]	));
	Ddim_Print(("weight_boundary[ 2 ][ 2 ]	= 0x%08x\n",	fmd.weight_boundary[ 2 ][ 2 ]	));
	Ddim_Print(("weight_boundary[ 2 ][ 3 ]	= 0x%08x\n",	fmd.weight_boundary[ 2 ][ 3 ]	));
	Ddim_Print(("weight_boundary[ 2 ][ 4 ]	= 0x%08x\n",	fmd.weight_boundary[ 2 ][ 4 ]	));
	Ddim_Print(("iso_threshold				= 0x%08x\n",	fmd.iso_threshold				));
	Ddim_Print(("iso_coef[ 0 ]				= 0x%08x\n",	fmd.iso_coef[ 0 ]				));
	Ddim_Print(("iso_coef[ 1 ]				= 0x%08x\n",	fmd.iso_coef[ 1 ]				));
	Ddim_Print(("iso_coef[ 2 ]				= 0x%08x\n",	fmd.iso_coef[ 2 ]				));
	Ddim_Print(("iso_coef[ 3 ]				= 0x%08x\n",	fmd.iso_coef[ 3 ]				));
	Ddim_Print(("iso_coef[ 4 ]				= 0x%08x\n",	fmd.iso_coef[ 4 ]				));
	Ddim_Print(("iso_coef[ 5 ]				= 0x%08x\n",	fmd.iso_coef[ 5 ]				));
	Ddim_Print(("sat_threshold				= 0x%08x\n",	fmd.sat_threshold				));
	Ddim_Print(("exp77_mode					= 0x%08x\n",	fmd.exp77_mode					));
	Ddim_Print(("fmd_sel					= 0x%08x\n",	fmd.fmd_sel						));
}

VOID ct_im_shdr_set2_get_pmsk(CtImShdrSet2* self)
{
	INT32			ret;
	T_IM_SHDR_PMSK	pmsk;

	ret = Im_SHDR_Get_PreMask( &pmsk );

	Ddim_Print(("ct_im_shdr_get_pmsk[ret=0x%08x]\n", ret));
	Ddim_Print(("tlut[ 0 ]	= 0x%08x\n",	pmsk.tlut[ 0 ]	));
	Ddim_Print(("tlut[ 1 ]	= 0x%08x\n",	pmsk.tlut[ 1 ]	));
	Ddim_Print(("tlut[ 2 ]	= 0x%08x\n",	pmsk.tlut[ 2 ]	));
	Ddim_Print(("tlut[ 3 ]	= 0x%08x\n",	pmsk.tlut[ 3 ]	));
	Ddim_Print(("tlut[ 4 ]	= 0x%08x\n",	pmsk.tlut[ 4 ]	));
	Ddim_Print(("tlut[ 5 ]	= 0x%08x\n",	pmsk.tlut[ 5 ]	));
	Ddim_Print(("tlut[ 6 ]	= 0x%08x\n",	pmsk.tlut[ 6 ]	));
	Ddim_Print(("tlut[ 7 ]	= 0x%08x\n",	pmsk.tlut[ 7 ]	));
	Ddim_Print(("tlut[ 8 ]	= 0x%08x\n",	pmsk.tlut[ 8 ]	));
	Ddim_Print(("tlut[ 9 ]	= 0x%08x\n",	pmsk.tlut[ 9 ]	));
	Ddim_Print(("tlut[ 10 ]	= 0x%08x\n",	pmsk.tlut[ 10 ]	));
	Ddim_Print(("tlut[ 11 ]	= 0x%08x\n",	pmsk.tlut[ 11 ]	));
	Ddim_Print(("tlut[ 12 ]	= 0x%08x\n",	pmsk.tlut[ 12 ]	));
	Ddim_Print(("tlut[ 13 ]	= 0x%08x\n",	pmsk.tlut[ 13 ]	));
	Ddim_Print(("tlut[ 14 ]	= 0x%08x\n",	pmsk.tlut[ 14 ]	));
	Ddim_Print(("tlut[ 15 ]	= 0x%08x\n",	pmsk.tlut[ 15 ]	));
	Ddim_Print(("tlut[ 16 ]	= 0x%08x\n",	pmsk.tlut[ 16 ]	));
	Ddim_Print(("pmsk_mode	= 0x%08x\n",	pmsk.pmsk_mode	));
}

VOID ct_im_shdr_set2_get_spnr(CtImShdrSet2* self)
{
	INT32			ret;
	T_IM_SHDR_SPNR	spnr;

	ret = Im_SHDR_Get_Spnr( &spnr );

	Ddim_Print(("ct_im_shdr_get_spnr[ret=0x%08x]\n", ret));
	Ddim_Print(("spnr_en			= 0x%08x\n",	spnr.spnr_en			));
	Ddim_Print(("spe_blend			= 0x%08x\n",	spnr.spe_blend			));
//	Ddim_Print(("spe_boundary[ 0 ]	= 0x%08x\n",	spnr.spe_boundary[ 0 ]	));
	Ddim_Print(("spe_boundary[ 1 ]	= 0x%08x\n",	spnr.spe_boundary[ 1 ]	));
	Ddim_Print(("spe_boundary[ 2 ]	= 0x%08x\n",	spnr.spe_boundary[ 2 ]	));
	Ddim_Print(("spe_boundary[ 3 ]	= 0x%08x\n",	spnr.spe_boundary[ 3 ]	));
	Ddim_Print(("spe_offset[ 0 ]	= 0x%08x\n",	spnr.spe_offset[ 0 ]	));
	Ddim_Print(("spe_offset[ 1 ]	= 0x%08x\n",	spnr.spe_offset[ 1 ]	));
	Ddim_Print(("spe_offset[ 2 ]	= 0x%08x\n",	spnr.spe_offset[ 2 ]	));
	Ddim_Print(("spe_offset[ 3 ]	= 0x%08x\n",	spnr.spe_offset[ 3 ]	));
}

VOID ct_im_shdr_set2_get_mask(CtImShdrSet2* self)
{
	INT32			ret;
	T_IM_SHDR_MSK	msk;

	ret = Im_SHDR_Get_Mask( &msk );

	Ddim_Print(("ct_im_shdr_get_msk[ret=0x%08x]\n", ret));
	Ddim_Print(("y2r_clp_upper_long[ 0 ]	= 0x%08x\n",	msk.y2r_clp_upper_long[ 0 ]	));
	Ddim_Print(("y2r_clp_upper_long[ 1 ]	= 0x%08x\n",	msk.y2r_clp_upper_long[ 1 ]	));
	Ddim_Print(("y2r_clp_upper_long[ 2 ]	= 0x%08x\n",	msk.y2r_clp_upper_long[ 2 ]	));
	Ddim_Print(("y2r_clp_lower_long[ 0 ]	= 0x%08x\n",	msk.y2r_clp_lower_long[ 0 ]	));
	Ddim_Print(("y2r_clp_lower_long[ 1 ]	= 0x%08x\n",	msk.y2r_clp_lower_long[ 1 ]	));
	Ddim_Print(("y2r_clp_lower_long[ 2 ]	= 0x%08x\n",	msk.y2r_clp_lower_long[ 2 ]	));
	Ddim_Print(("y2r_clp_upper_short[ 0 ]	= 0x%08x\n",	msk.y2r_clp_upper_short[ 0 ]));
	Ddim_Print(("y2r_clp_upper_short[ 1 ]	= 0x%08x\n",	msk.y2r_clp_upper_short[ 1 ]));
	Ddim_Print(("y2r_clp_upper_short[ 2 ]	= 0x%08x\n",	msk.y2r_clp_upper_short[ 2 ]));
	Ddim_Print(("y2r_clp_lower_short[ 0 ]	= 0x%08x\n",	msk.y2r_clp_lower_short[ 0 ]));
	Ddim_Print(("y2r_clp_lower_short[ 1 ]	= 0x%08x\n",	msk.y2r_clp_lower_short[ 1 ]));
	Ddim_Print(("y2r_clp_lower_short[ 2 ]	= 0x%08x\n",	msk.y2r_clp_lower_short[ 2 ]));
	Ddim_Print(("alpha						= 0x%08x\n",	msk.alpha					));
	Ddim_Print(("lpfc[ 0 ][ 0 ]				= 0x%08x\n",	msk.lpfc[ 0 ][ 0 ]			));
	Ddim_Print(("lpfc[ 0 ][ 1 ]				= 0x%08x\n",	msk.lpfc[ 0 ][ 1 ]			));
	Ddim_Print(("lpfc[ 0 ][ 2 ]				= 0x%08x\n",	msk.lpfc[ 0 ][ 2 ]			));
	Ddim_Print(("lpfc[ 1 ][ 0 ]				= 0x%08x\n",	msk.lpfc[ 1 ][ 0 ]			));
	Ddim_Print(("lpfc[ 1 ][ 1 ]				= 0x%08x\n",	msk.lpfc[ 1 ][ 1 ]			));
	Ddim_Print(("lpfc[ 1 ][ 2 ]				= 0x%08x\n",	msk.lpfc[ 1 ][ 2 ]			));
	Ddim_Print(("lpfc[ 2 ][ 0 ]				= 0x%08x\n",	msk.lpfc[ 2 ][ 0 ]			));
	Ddim_Print(("lpfc[ 2 ][ 1 ]				= 0x%08x\n",	msk.lpfc[ 2 ][ 1 ]			));
	Ddim_Print(("lpfc[ 2 ][ 2 ]				= 0x%08x\n",	msk.lpfc[ 2 ][ 2 ]			));
	Ddim_Print(("blend_offset[ 0 ]			= 0x%08x\n",	msk.blend_offset[ 0 ]		));
	Ddim_Print(("blend_offset[ 1 ]			= 0x%08x\n",	msk.blend_offset[ 1 ]		));
	Ddim_Print(("blend_offset[ 2 ]			= 0x%08x\n",	msk.blend_offset[ 2 ]		));
	Ddim_Print(("blend_offset[ 3 ]			= 0x%08x\n",	msk.blend_offset[ 3 ]		));
	Ddim_Print(("blend_offset[ 4 ]			= 0x%08x\n",	msk.blend_offset[ 4 ]		));
	Ddim_Print(("blend_offset[ 5 ]			= 0x%08x\n",	msk.blend_offset[ 5 ]		));
	Ddim_Print(("blend_offset[ 6 ]			= 0x%08x\n",	msk.blend_offset[ 6 ]		));
	Ddim_Print(("blend_slope[ 0 ]			= 0x%08x\n",	msk.blend_slope[ 0 ]		));
	Ddim_Print(("blend_slope[ 1 ]			= 0x%08x\n",	msk.blend_slope[ 1 ]		));
	Ddim_Print(("blend_slope[ 2 ]			= 0x%08x\n",	msk.blend_slope[ 2 ]		));
	Ddim_Print(("blend_slope[ 3 ]			= 0x%08x\n",	msk.blend_slope[ 3 ]		));
	Ddim_Print(("blend_slope[ 4 ]			= 0x%08x\n",	msk.blend_slope[ 4 ]		));
	Ddim_Print(("blend_slope[ 5 ]			= 0x%08x\n",	msk.blend_slope[ 5 ]		));
	Ddim_Print(("blend_slope[ 6 ]			= 0x%08x\n",	msk.blend_slope[ 6 ]		));
//	Ddim_Print(("blend_boundary[ 0 ]		= 0x%08x\n",	msk.blend_boundary[ 0 ]		));
	Ddim_Print(("blend_boundary[ 1 ]		= 0x%08x\n",	msk.blend_boundary[ 1 ]		));
	Ddim_Print(("blend_boundary[ 2 ]		= 0x%08x\n",	msk.blend_boundary[ 2 ]		));
	Ddim_Print(("blend_boundary[ 3 ]		= 0x%08x\n",	msk.blend_boundary[ 3 ]		));
	Ddim_Print(("blend_boundary[ 4 ]		= 0x%08x\n",	msk.blend_boundary[ 4 ]		));
	Ddim_Print(("blend_boundary[ 5 ]		= 0x%08x\n",	msk.blend_boundary[ 5 ]		));
	Ddim_Print(("blend_boundary[ 6 ]		= 0x%08x\n",	msk.blend_boundary[ 6 ]		));
	Ddim_Print(("norm_gain[ 0 ]				= 0x%08x\n",	msk.norm_gain[ 0 ]			));
	Ddim_Print(("norm_gain[ 1 ]				= 0x%08x\n",	msk.norm_gain[ 1 ]			));
	Ddim_Print(("norm_gain[ 2 ]				= 0x%08x\n",	msk.norm_gain[ 2 ]			));
	Ddim_Print(("norm_offset[ 0 ]			= 0x%08x\n",	msk.norm_offset[ 0 ]		));
	Ddim_Print(("norm_offset[ 1 ]			= 0x%08x\n",	msk.norm_offset[ 1 ]		));
	Ddim_Print(("norm_offset[ 2 ]			= 0x%08x\n",	msk.norm_offset[ 2 ]		));
	Ddim_Print(("msk_mode					= 0x%08x\n",	msk.msk_mode				));
}

VOID ct_im_shdr_set2_get_bld(CtImShdrSet2* self)
{
	INT32			ret;
	T_IM_SHDR_BLD	bld;

	ret = Im_SHDR_Get_Blend( &bld );

	Ddim_Print(("ct_im_shdr_get_bld[ret=0x%08x]\n", ret));
	Ddim_Print(("blend_sel		= 0x%08x\n",	bld.blend_sel		));
	Ddim_Print(("alpha_sel		= 0x%08x\n",	bld.alpha_sel		));
	Ddim_Print(("alpha_val[ 0 ]	= 0x%08x\n",	bld.alpha_val[ 0 ]	));
	Ddim_Print(("alpha_val[ 1 ]	= 0x%08x\n",	bld.alpha_val[ 1 ]	));
	Ddim_Print(("alpha_val[ 2 ]	= 0x%08x\n",	bld.alpha_val[ 2 ]	));
}

VOID ct_im_shdr_set2_get_post(CtImShdrSet2* self)
{
	INT32			ret;
	T_IM_SHDR_POST	post;

	ret = Im_SHDR_Get_Post( &post );

	Ddim_Print(("ct_im_shdr_get_post[ret=0x%08x]\n", ret));
	Ddim_Print(("sft1rnd.sft1rnd_en		= 0x%08x\n",	post.sft1rnd.sft1rnd_en		));
	Ddim_Print(("y2r_coef[ 0 ]			= 0x%08x\n",	post.y2r_coef[ 0 ]			));
	Ddim_Print(("y2r_coef[ 1 ]			= 0x%08x\n",	post.y2r_coef[ 1 ]			));
	Ddim_Print(("y2r_coef[ 2 ]			= 0x%08x\n",	post.y2r_coef[ 2 ]			));
	Ddim_Print(("y2r_coef[ 3 ]			= 0x%08x\n",	post.y2r_coef[ 3 ]			));
	Ddim_Print(("y2r_coef[ 4 ]			= 0x%08x\n",	post.y2r_coef[ 4 ]			));
	Ddim_Print(("y2r_coef[ 5 ]			= 0x%08x\n",	post.y2r_coef[ 5 ]			));
	Ddim_Print(("y2r_coef[ 6 ]			= 0x%08x\n",	post.y2r_coef[ 6 ]			));
	Ddim_Print(("y2r_coef[ 7 ]			= 0x%08x\n",	post.y2r_coef[ 7 ]			));
	Ddim_Print(("y2r_coef[ 8 ]			= 0x%08x\n",	post.y2r_coef[ 8 ]			));
	Ddim_Print(("y2r_clp_th_upper[ 0 ]	= 0x%08x\n",	post.y2r_clp_th_upper[ 0 ]	));
	Ddim_Print(("y2r_clp_th_upper[ 1 ]	= 0x%08x\n",	post.y2r_clp_th_upper[ 1 ]	));
	Ddim_Print(("y2r_clp_th_upper[ 2 ]	= 0x%08x\n",	post.y2r_clp_th_upper[ 2 ]	));
	Ddim_Print(("y2r_clp_th_lower[ 0 ]	= 0x%08x\n",	post.y2r_clp_th_lower[ 0 ]	));
	Ddim_Print(("y2r_clp_th_lower[ 1 ]	= 0x%08x\n",	post.y2r_clp_th_lower[ 1 ]	));
	Ddim_Print(("y2r_clp_th_lower[ 2 ]	= 0x%08x\n",	post.y2r_clp_th_lower[ 2 ]	));
	Ddim_Print(("ev_sel					= 0x%08x\n",	post.ev_sel					));
	Ddim_Print(("mulqpos				= 0x%08x\n",	post.mulqpos				));
	Ddim_Print(("ev_kn_boundary[ 0 ]	= 0x%08x\n",	post.ev_kn_boundary[ 0 ]	));
	Ddim_Print(("ev_kn_boundary[ 1 ]	= 0x%08x\n",	post.ev_kn_boundary[ 1 ]	));
	Ddim_Print(("ev_kn_boundary[ 2 ]	= 0x%08x\n",	post.ev_kn_boundary[ 2 ]	));
	Ddim_Print(("ev_kn_boundary[ 3 ]	= 0x%08x\n",	post.ev_kn_boundary[ 3 ]	));
	Ddim_Print(("ev_kn_boundary[ 4 ]	= 0x%08x\n",	post.ev_kn_boundary[ 4 ]	));
	Ddim_Print(("ev_kn_boundary[ 5 ]	= 0x%08x\n",	post.ev_kn_boundary[ 5 ]	));
	Ddim_Print(("ev_kn_boundary[ 6 ]	= 0x%08x\n",	post.ev_kn_boundary[ 6 ]	));
	Ddim_Print(("ev_kn_boundary[ 7 ]	= 0x%08x\n",	post.ev_kn_boundary[ 7 ]	));
	Ddim_Print(("ev_kn_boundary[ 8 ]	= 0x%08x\n",	post.ev_kn_boundary[ 8 ]	));
	Ddim_Print(("ev_kn_boundary[ 9 ]	= 0x%08x\n",	post.ev_kn_boundary[ 9 ]	));
	Ddim_Print(("ev_kn_offset[ 0 ]		= 0x%08x\n",	post.ev_kn_offset[ 0 ]		));
	Ddim_Print(("ev_kn_offset[ 1 ]		= 0x%08x\n",	post.ev_kn_offset[ 1 ]		));
	Ddim_Print(("ev_kn_offset[ 2 ]		= 0x%08x\n",	post.ev_kn_offset[ 2 ]		));
	Ddim_Print(("ev_kn_offset[ 3 ]		= 0x%08x\n",	post.ev_kn_offset[ 3 ]		));
	Ddim_Print(("ev_kn_offset[ 4 ]		= 0x%08x\n",	post.ev_kn_offset[ 4 ]		));
	Ddim_Print(("ev_kn_offset[ 5 ]		= 0x%08x\n",	post.ev_kn_offset[ 5 ]		));
	Ddim_Print(("ev_kn_offset[ 6 ]		= 0x%08x\n",	post.ev_kn_offset[ 6 ]		));
	Ddim_Print(("ev_kn_offset[ 7 ]		= 0x%08x\n",	post.ev_kn_offset[ 7 ]		));
	Ddim_Print(("ev_kn_offset[ 8 ]		= 0x%08x\n",	post.ev_kn_offset[ 8 ]		));
	Ddim_Print(("ev_kn_offset[ 9 ]		= 0x%08x\n",	post.ev_kn_offset[ 9 ]		));
	Ddim_Print(("ev_kn_slope[ 0 ]		= 0x%08x\n",	post.ev_kn_slope[ 0 ]		));
	Ddim_Print(("ev_kn_slope[ 1 ]		= 0x%08x\n",	post.ev_kn_slope[ 1 ]		));
	Ddim_Print(("ev_kn_slope[ 2 ]		= 0x%08x\n",	post.ev_kn_slope[ 2 ]		));
	Ddim_Print(("ev_kn_slope[ 3 ]		= 0x%08x\n",	post.ev_kn_slope[ 3 ]		));
	Ddim_Print(("ev_kn_slope[ 4 ]		= 0x%08x\n",	post.ev_kn_slope[ 4 ]		));
	Ddim_Print(("ev_kn_slope[ 5 ]		= 0x%08x\n",	post.ev_kn_slope[ 5 ]		));
	Ddim_Print(("ev_kn_slope[ 6 ]		= 0x%08x\n",	post.ev_kn_slope[ 6 ]		));
	Ddim_Print(("ev_kn_slope[ 7 ]		= 0x%08x\n",	post.ev_kn_slope[ 7 ]		));
	Ddim_Print(("ev_kn_slope[ 8 ]		= 0x%08x\n",	post.ev_kn_slope[ 8 ]		));
	Ddim_Print(("ev_kn_slope[ 9 ]		= 0x%08x\n",	post.ev_kn_slope[ 9 ]		));
	Ddim_Print(("css_sel				= 0x%08x\n",	post.css_sel				));
	Ddim_Print(("hdrcss_mode			= 0x%08x\n",	post.hdrcss_mode			));
}

VOID ct_im_shdr_set2_get_resize(CtImShdrSet2* self)
{
	INT32				ret;
	T_IM_SHDR_RESIZE	resize;

	ret = Im_SHDR_Get_Resize( &resize );

	Ddim_Print(("ct_im_shdr_get_resize[ret=0x%08x]\n", ret));
	Ddim_Print(("chmode.a_w_en		= 0x%08x\n",	resize.chmode.a_w_en	));
	Ddim_Print(("chmode.a_drc_en	= 0x%08x\n",	resize.chmode.a_drc_en	));
	Ddim_Print(("chmode.a_css_md	= 0x%08x\n",	resize.chmode.a_css_md	));
	Ddim_Print(("chmode.b_w_en		= 0x%08x\n",	resize.chmode.b_w_en	));
	Ddim_Print(("chmode.b_rdc_md	= 0x%08x\n",	resize.chmode.b_rdc_md	));
	Ddim_Print(("chmode.b_css_md	= 0x%08x\n",	resize.chmode.b_css_md	));
	Ddim_Print(("chmode.c_w_en		= 0x%08x\n",	resize.chmode.c_w_en	));
	Ddim_Print(("chmode.c_rsz_md	= 0x%08x\n",	resize.chmode.c_rsz_md	));
	Ddim_Print(("chmode.c_rdc_en	= 0x%08x\n",	resize.chmode.c_rdc_en	));
	Ddim_Print(("chmode.c_rdc_md	= 0x%08x\n",	resize.chmode.c_rdc_md	));
	Ddim_Print(("chmode.c_trm_en	= 0x%08x\n",	resize.chmode.c_trm_en	));
	Ddim_Print(("chmode.c_drc_en	= 0x%08x\n",	resize.chmode.c_drc_en	));
	Ddim_Print(("chmode.c_css_md	= 0x%08x\n",	resize.chmode.c_css_md	));
	Ddim_Print(("chmode.d_w_en		= 0x%08x\n",	resize.chmode.d_w_en	));
	Ddim_Print(("chmode.d_rsz_md	= 0x%08x\n",	resize.chmode.d_rsz_md	));
	Ddim_Print(("chmode.d_rdc_en	= 0x%08x\n",	resize.chmode.d_rdc_en	));
	Ddim_Print(("chmode.d_rdc_md	= 0x%08x\n",	resize.chmode.d_rdc_md	));
	Ddim_Print(("chmode.d_trm_en	= 0x%08x\n",	resize.chmode.d_trm_en	));
	Ddim_Print(("chmode.d_drc_en	= 0x%08x\n",	resize.chmode.d_drc_en	));
	Ddim_Print(("chmode.d_css_md	= 0x%08x\n",	resize.chmode.d_css_md	));
	Ddim_Print(("chmode.e_w_en		= 0x%08x\n",	resize.chmode.e_w_en	));
	Ddim_Print(("chmode.e_rsz_md	= 0x%08x\n",	resize.chmode.e_rsz_md	));
	Ddim_Print(("chmode.e_rdc_en	= 0x%08x\n",	resize.chmode.e_rdc_en	));
	Ddim_Print(("chmode.e_rdc_md	= 0x%08x\n",	resize.chmode.e_rdc_md	));
	Ddim_Print(("chmode.e_trm_en	= 0x%08x\n",	resize.chmode.e_trm_en	));
	Ddim_Print(("chmode.e_css_md	= 0x%08x\n",	resize.chmode.e_css_md	));
	Ddim_Print(("chmode.f_w_en		= 0x%08x\n",	resize.chmode.f_w_en	));
	Ddim_Print(("chmode.f_rsz_md	= 0x%08x\n",	resize.chmode.f_rsz_md	));
	Ddim_Print(("chmode.f_rdc_en	= 0x%08x\n",	resize.chmode.f_rdc_en	));
	Ddim_Print(("chmode.f_rdc_md	= 0x%08x\n",	resize.chmode.f_rdc_md	));
	Ddim_Print(("chmode.f_trm_en	= 0x%08x\n",	resize.chmode.f_trm_en	));
	Ddim_Print(("chmode.f_css_md	= 0x%08x\n",	resize.chmode.f_css_md	));
	Ddim_Print(("woutsz.a_hsize		= 0x%08x\n",	resize.woutsz.a_hsize	));
	Ddim_Print(("woutsz.a_vsize		= 0x%08x\n",	resize.woutsz.a_vsize	));
	Ddim_Print(("woutsz.b_hsize		= 0x%08x\n",	resize.woutsz.b_hsize	));
	Ddim_Print(("woutsz.b_vsize		= 0x%08x\n",	resize.woutsz.b_vsize	));
	Ddim_Print(("woutsz.c_hsize		= 0x%08x\n",	resize.woutsz.c_hsize	));
	Ddim_Print(("woutsz.c_vsize		= 0x%08x\n",	resize.woutsz.c_vsize	));
	Ddim_Print(("woutsz.d_hsize		= 0x%08x\n",	resize.woutsz.d_hsize	));
	Ddim_Print(("woutsz.d_vsize		= 0x%08x\n",	resize.woutsz.d_vsize	));
	Ddim_Print(("woutsz.e_hsize		= 0x%08x\n",	resize.woutsz.e_hsize	));
	Ddim_Print(("woutsz.e_vsize		= 0x%08x\n",	resize.woutsz.e_vsize	));
	Ddim_Print(("woutsz.f_hsize		= 0x%08x\n",	resize.woutsz.f_hsize	));
	Ddim_Print(("woutsz.f_vsize		= 0x%08x\n",	resize.woutsz.f_vsize	));
	Ddim_Print(("rszhcnt.c_hsta		= 0x%08x\n",	resize.rszhcnt.c_hsta	));
	Ddim_Print(("rszhcnt.c_hpit		= 0x%08x\n",	resize.rszhcnt.c_hpit	));
	Ddim_Print(("rszhcnt.d_hsta		= 0x%08x\n",	resize.rszhcnt.d_hsta	));
	Ddim_Print(("rszhcnt.d_hpit		= 0x%08x\n",	resize.rszhcnt.d_hpit	));
	Ddim_Print(("rszhcnt.e_hsta		= 0x%08x\n",	resize.rszhcnt.e_hsta	));
	Ddim_Print(("rszhcnt.e_hpit		= 0x%08x\n",	resize.rszhcnt.e_hpit	));
	Ddim_Print(("rszhcnt.f_hsta		= 0x%08x\n",	resize.rszhcnt.f_hsta	));
	Ddim_Print(("rszhcnt.f_hpit		= 0x%08x\n",	resize.rszhcnt.f_hpit	));
	Ddim_Print(("rszvcnt.c_vsta		= 0x%08x\n",	resize.rszvcnt.c_vsta	));
	Ddim_Print(("rszvcnt.c_vpit		= 0x%08x\n",	resize.rszvcnt.c_vpit	));
	Ddim_Print(("rszvcnt.d_vsta		= 0x%08x\n",	resize.rszvcnt.d_vsta	));
	Ddim_Print(("rszvcnt.d_vpit		= 0x%08x\n",	resize.rszvcnt.d_vpit	));
	Ddim_Print(("rszvcnt.e_vsta		= 0x%08x\n",	resize.rszvcnt.e_vsta	));
	Ddim_Print(("rszvcnt.e_vpit		= 0x%08x\n",	resize.rszvcnt.e_vpit	));
	Ddim_Print(("rszvcnt.f_vsta		= 0x%08x\n",	resize.rszvcnt.f_vsta	));
	Ddim_Print(("rszvcnt.f_vpit		= 0x%08x\n",	resize.rszvcnt.f_vpit	));
	Ddim_Print(("trmsta.c_hsta		= 0x%08x\n",	resize.trmsta.c_hsta	));
	Ddim_Print(("trmsta.c_vsta		= 0x%08x\n",	resize.trmsta.c_vsta	));
	Ddim_Print(("trmsta.d_hsta		= 0x%08x\n",	resize.trmsta.d_hsta	));
	Ddim_Print(("trmsta.d_vsta		= 0x%08x\n",	resize.trmsta.d_vsta	));
	Ddim_Print(("trmsta.e_hsta		= 0x%08x\n",	resize.trmsta.e_hsta	));
	Ddim_Print(("trmsta.e_vsta		= 0x%08x\n",	resize.trmsta.e_vsta	));
	Ddim_Print(("trmsta.f_hsta		= 0x%08x\n",	resize.trmsta.f_hsta	));
	Ddim_Print(("trmsta.f_vsta		= 0x%08x\n",	resize.trmsta.f_vsta	));
	Ddim_Print(("drcofst.a_y		= 0x%08x\n",	resize.drcofst.a_y		));
	Ddim_Print(("drcofst.a_cb		= 0x%08x\n",	resize.drcofst.a_cb		));
	Ddim_Print(("drcofst.a_cr		= 0x%08x\n",	resize.drcofst.a_cr		));
	Ddim_Print(("drcofst.c_y		= 0x%08x\n",	resize.drcofst.c_y		));
	Ddim_Print(("drcofst.c_cb		= 0x%08x\n",	resize.drcofst.c_cb		));
	Ddim_Print(("drcofst.c_cr		= 0x%08x\n",	resize.drcofst.c_cr		));
	Ddim_Print(("drcofst.d_y		= 0x%08x\n",	resize.drcofst.d_y		));
	Ddim_Print(("drcofst.d_cb		= 0x%08x\n",	resize.drcofst.d_cb		));
	Ddim_Print(("drcofst.d_cr		= 0x%08x\n",	resize.drcofst.d_cr		));
	Ddim_Print(("drcgain.a_y		= 0x%08x\n",	resize.drcgain.a_y		));
	Ddim_Print(("drcgain.a_cb		= 0x%08x\n",	resize.drcgain.a_cb		));
	Ddim_Print(("drcgain.a_cr		= 0x%08x\n",	resize.drcgain.a_cr		));
	Ddim_Print(("drcgain.c_y		= 0x%08x\n",	resize.drcgain.c_y		));
	Ddim_Print(("drcgain.c_cb		= 0x%08x\n",	resize.drcgain.c_cb		));
	Ddim_Print(("drcgain.c_cr		= 0x%08x\n",	resize.drcgain.c_cr		));
	Ddim_Print(("drcgain.d_y		= 0x%08x\n",	resize.drcgain.d_y		));
	Ddim_Print(("drcgain.d_cb		= 0x%08x\n",	resize.drcgain.d_cb		));
	Ddim_Print(("drcgain.d_cr		= 0x%08x\n",	resize.drcgain.d_cr		));
	Ddim_Print(("drcclph.a_y		= 0x%08x\n",	resize.drcclph.a_y		));
	Ddim_Print(("drcclph.a_cb		= 0x%08x\n",	resize.drcclph.a_cb		));
	Ddim_Print(("drcclph.a_cr		= 0x%08x\n",	resize.drcclph.a_cr		));
	Ddim_Print(("drcclph.c_y		= 0x%08x\n",	resize.drcclph.c_y		));
	Ddim_Print(("drcclph.c_cb		= 0x%08x\n",	resize.drcclph.c_cb		));
	Ddim_Print(("drcclph.c_cr		= 0x%08x\n",	resize.drcclph.c_cr		));
	Ddim_Print(("drcclph.d_y		= 0x%08x\n",	resize.drcclph.d_y		));
	Ddim_Print(("drcclph.d_cb		= 0x%08x\n",	resize.drcclph.d_cb		));
	Ddim_Print(("drcclph.d_cr		= 0x%08x\n",	resize.drcclph.d_cr		));
	Ddim_Print(("drcclpl.a_y		= 0x%08x\n",	resize.drcclpl.a_y		));
	Ddim_Print(("drcclpl.a_cb		= 0x%08x\n",	resize.drcclpl.a_cb		));
	Ddim_Print(("drcclpl.a_cr		= 0x%08x\n",	resize.drcclpl.a_cr		));
	Ddim_Print(("drcclpl.c_y		= 0x%08x\n",	resize.drcclpl.c_y		));
	Ddim_Print(("drcclpl.c_cb		= 0x%08x\n",	resize.drcclpl.c_cb		));
	Ddim_Print(("drcclpl.c_cr		= 0x%08x\n",	resize.drcclpl.c_cr		));
	Ddim_Print(("drcclpl.d_y		= 0x%08x\n",	resize.drcclpl.d_y		));
	Ddim_Print(("drcclpl.d_cb		= 0x%08x\n",	resize.drcclpl.d_cb		));
	Ddim_Print(("drcclpl.d_cr		= 0x%08x\n",	resize.drcclpl.d_cr		));
}

VOID ct_im_shdr_set2_get_smc(CtImShdrSet2* self)
{
	INT32			ret;
	T_IM_SHDR_SMC	smc;

	ret = Im_SHDR_Get_Smc( &smc );

	Ddim_Print(("ct_im_shdr_get_smc[ret=0x%08x]\n", ret));
	Ddim_Print(("mcarmd.mca_mode			= 0x%08x\n",	smc.mcarmd.mca_mode				));
	Ddim_Print(("mcarmd.mcr_mode			= 0x%08x\n",	smc.mcarmd.mcr_mode				));
	Ddim_Print(("mcmpmd.mcmp_mode			= 0x%08x\n",	smc.mcmpmd.mcmp_mode			));
	Ddim_Print(("mcmpmd.mvw_en				= 0x%08x\n",	smc.mcmpmd.mvw_en				));
	Ddim_Print(("mmvval.mmv_x				= 0x%08x\n",	smc.mmvval.mmv_x				));
	Ddim_Print(("mmvval.mmv_y				= 0x%08x\n",	smc.mmvval.mmv_y				));
	Ddim_Print(("mmvrcnt.mmvro_x			= 0x%08x\n",	smc.mmvrcnt.mmvro_x				));
	Ddim_Print(("mmvrcnt.mmvro_y			= 0x%08x\n",	smc.mmvrcnt.mmvro_y				));
	Ddim_Print(("mmvrcnt.mmvrk_x			= 0x%08x\n",	smc.mmvrcnt.mmvrk_x				));
	Ddim_Print(("mmvrcnt.mmvrk_y			= 0x%08x\n",	smc.mmvrcnt.mmvrk_y				));
	Ddim_Print(("mdbcnt.mdb_x				= 0x%08x\n",	smc.mdbcnt.mdb_x				));
	Ddim_Print(("mdbcnt.mdb_y				= 0x%08x\n",	smc.mdbcnt.mdb_y				));
	Ddim_Print(("mdbrocnt.mdbro_x			= 0x%08x\n",	smc.mdbrocnt.mdbro_x			));
	Ddim_Print(("mdbrocnt.mdbro_y			= 0x%08x\n",	smc.mdbrocnt.mdbro_y			));
	Ddim_Print(("mdbrocnt.mdbrk_x			= 0x%08x\n",	smc.mdbrocnt.mdbrk_x			));
	Ddim_Print(("mdbrocnt.mdbrk_y			= 0x%08x\n",	smc.mdbrocnt.mdbrk_y			));
	Ddim_Print(("molrcnt.molr_sm			= 0x%08x\n",	smc.molrcnt.molr_sm				));
	Ddim_Print(("molrcnt.molr_ss			= 0x%08x\n",	smc.molrcnt.molr_ss				));
	Ddim_Print(("molrcnt.molr_o				= 0x%08x\n",	smc.molrcnt.molr_o				));
	Ddim_Print(("molrcnt.molr_k				= 0x%08x\n",	smc.molrcnt.molr_k				));
	Ddim_Print(("mcpcnt.mcpx_s				= 0x%08x\n",	smc.mcpcnt.mcpx_s				));
	Ddim_Print(("mcpcnt.mcpx_o				= 0x%08x\n",	smc.mcpcnt.mcpx_o				));
	Ddim_Print(("mcpcnt.mcpx_k				= 0x%08x\n",	smc.mcpcnt.mcpx_k				));
	Ddim_Print(("mmcrcnt.mmcr_s				= 0x%08x\n",	smc.mmcrcnt.mmcr_s				));
	Ddim_Print(("mmcrcnt.mmcr_k				= 0x%08x\n",	smc.mmcrcnt.mmcr_k				));
	Ddim_Print(("molecnt.mole_s				= 0x%08x\n",	smc.molecnt.mole_s				));
	Ddim_Print(("molecnt.mole_o				= 0x%08x\n",	smc.molecnt.mole_o				));
	Ddim_Print(("molecnt.mole_k				= 0x%08x\n",	smc.molecnt.mole_k				));
	Ddim_Print(("mmvecnt.mmve_s				= 0x%08x\n",	smc.mmvecnt.mmve_s				));
	Ddim_Print(("mmvecnt.mmve_o				= 0x%08x\n",	smc.mmvecnt.mmve_o				));
	Ddim_Print(("mmvecnt.mmve_k				= 0x%08x\n",	smc.mmvecnt.mmve_k				));
	Ddim_Print(("mcpxecnt.mcpxe_s			= 0x%08x\n",	smc.mcpxecnt.mcpxe_s			));
	Ddim_Print(("mcpxecnt.mcpxe_o			= 0x%08x\n",	smc.mcpxecnt.mcpxe_o			));
	Ddim_Print(("mcpxecnt.mcpxe_k			= 0x%08x\n",	smc.mcpxecnt.mcpxe_k			));
	Ddim_Print(("mvlcnt.mvl_en				= 0x%08x\n",	smc.mvlcnt.mvl_en				));
	Ddim_Print(("mvlcnt.mvl_threshold		= 0x%08x\n",	smc.mvlcnt.mvl_threshold		));
	Ddim_Print(("mvlcnt.mvl_count_threshold	= 0x%08x\n",	smc.mvlcnt.mvl_count_threshold	));
}

VOID ct_im_shdr_set2_get_dgr(CtImShdrSet2* self)
{
	INT32			ret;
	INT32			i;
	USHORT			dst_tbl[D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE];

	ret = Im_SHDR_Get_Degamma_R( &dst_tbl[0], 0, D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE, D_IM_SHDR_DGTRSEL_PREFL );

	Ddim_Print(("ct_im_shdr_get_dgr[ret=0x%08x]\n", ret));
	for ( i = 0; i < D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE; i++ ) {
		Ddim_Print(("dst_tbl[%d] = 0x%08x\n", i, dst_tbl[i]));
	}
}

VOID ct_im_shdr_set2_get_dgg(CtImShdrSet2* self)
{
	INT32			ret;
	INT32			i;
	USHORT			dst_tbl[D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE];

	ret = Im_SHDR_Get_Degamma_G( &dst_tbl[0], 0, D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE, D_IM_SHDR_DGTRSEL_PREFL );

	Ddim_Print(("ct_im_shdr_get_dgg[ret=0x%08x]\n", ret));
	for ( i = 0; i < D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE; i++ ) {
		Ddim_Print(("dst_tbl[%d] = 0x%08x\n", i, dst_tbl[i]));
	}
}

VOID ct_im_shdr_set2_get_dgb(CtImShdrSet2* self)
{
	INT32			ret;
	INT32			i;
	USHORT			dst_tbl[D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE];

	ret = Im_SHDR_Get_Degamma_B( &dst_tbl[0], 0, D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE, D_IM_SHDR_DGTRSEL_PREFL );

	Ddim_Print(("ct_im_shdr_get_dgb[ret=0x%08x]\n", ret));
	for ( i = 0; i < D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE; i++ ) {
		Ddim_Print(("dst_tbl[%d] = 0x%08x\n", i, dst_tbl[i]));
	}
}

VOID ct_im_shdr_set2_get_dg(CtImShdrSet2* self)
{
	INT32			ret;
	INT32			i, j;
	USHORT			dst_tbl[3][D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE];

	ret = Im_SHDR_Get_Degamma( &dst_tbl[0][0], &dst_tbl[1][0], &dst_tbl[2][0], 0, D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE, D_IM_SHDR_DGTRSEL_PREFL );

	Ddim_Print(("ct_im_shdr_get_dg[ret=0x%08x]\n", ret));
	for ( i = 0; i < 3; i++ ) {
		for ( j = 0; j < D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE; j++ ) {
			Ddim_Print(("dst_tbl[%d][%d] = 0x%08x\n", i, j, dst_tbl[i][j]));
		}
	}
}

VOID ct_im_shdr_set2_get_axires(CtImShdrSet2* self)
{
	INT32				ret;
	T_IM_SHDR_AXI_RESP	axires;

	ret = Im_SHDR_Get_Axi_Response( &axires );

	Ddim_Print(("ct_im_shdr_get_axires[ret=0x%08x]\n", ret));
	Ddim_Print(("r_resp_a[0]= 0x%08x\n", axires.r_resp_a[0]));
	Ddim_Print(("r_resp_a[1]= 0x%08x\n", axires.r_resp_a[1]));
	Ddim_Print(("r_resp_a[2]= 0x%08x\n", axires.r_resp_a[2]));
	Ddim_Print(("r_resp_a[3]= 0x%08x\n", axires.r_resp_a[3]));
	Ddim_Print(("r_resp_b[0]= 0x%08x\n", axires.r_resp_b[0]));
	Ddim_Print(("r_resp_b[1]= 0x%08x\n", axires.r_resp_b[1]));
	Ddim_Print(("r_resp_b[2]= 0x%08x\n", axires.r_resp_b[2]));
	Ddim_Print(("r_resp_b[3]= 0x%08x\n", axires.r_resp_b[3]));
	Ddim_Print(("r_resp_c[0]= 0x%08x\n", axires.r_resp_c[0]));
	Ddim_Print(("r_resp_c[1]= 0x%08x\n", axires.r_resp_c[1]));
	Ddim_Print(("r_resp_c[2]= 0x%08x\n", axires.r_resp_c[2]));
	Ddim_Print(("r_resp_c[3]= 0x%08x\n", axires.r_resp_c[3]));
	Ddim_Print(("r_resp_d[0]= 0x%08x\n", axires.r_resp_d[0]));
	Ddim_Print(("r_resp_d[1]= 0x%08x\n", axires.r_resp_d[1]));
	Ddim_Print(("r_resp_d[2]= 0x%08x\n", axires.r_resp_d[2]));
	Ddim_Print(("r_resp_d[3]= 0x%08x\n", axires.r_resp_d[3]));
	Ddim_Print(("w_resp_a[0]= 0x%08x\n", axires.w_resp_a[0]));
	Ddim_Print(("w_resp_a[1]= 0x%08x\n", axires.w_resp_a[1]));
	Ddim_Print(("w_resp_a[2]= 0x%08x\n", axires.w_resp_a[2]));
	Ddim_Print(("w_resp_a[3]= 0x%08x\n", axires.w_resp_a[3]));
	Ddim_Print(("w_resp_a[4]= 0x%08x\n", axires.w_resp_a[4]));
	Ddim_Print(("w_resp_a[5]= 0x%08x\n", axires.w_resp_a[5]));
	Ddim_Print(("w_resp_a[6]= 0x%08x\n", axires.w_resp_a[6]));
	Ddim_Print(("w_resp_b[0]= 0x%08x\n", axires.w_resp_b[0]));
	Ddim_Print(("w_resp_b[1]= 0x%08x\n", axires.w_resp_b[1]));
	Ddim_Print(("w_resp_b[2]= 0x%08x\n", axires.w_resp_b[2]));
	Ddim_Print(("w_resp_b[3]= 0x%08x\n", axires.w_resp_b[3]));
	Ddim_Print(("w_resp_b[4]= 0x%08x\n", axires.w_resp_b[4]));
	Ddim_Print(("w_resp_b[5]= 0x%08x\n", axires.w_resp_b[5]));
	Ddim_Print(("w_resp_b[6]= 0x%08x\n", axires.w_resp_b[6]));
	Ddim_Print(("w_resp_c[0]= 0x%08x\n", axires.w_resp_c[0]));
	Ddim_Print(("w_resp_c[1]= 0x%08x\n", axires.w_resp_c[1]));
	Ddim_Print(("w_resp_c[2]= 0x%08x\n", axires.w_resp_c[2]));
	Ddim_Print(("w_resp_c[3]= 0x%08x\n", axires.w_resp_c[3]));
	Ddim_Print(("w_resp_c[4]= 0x%08x\n", axires.w_resp_c[4]));
	Ddim_Print(("w_resp_c[5]= 0x%08x\n", axires.w_resp_c[5]));
	Ddim_Print(("w_resp_c[6]= 0x%08x\n", axires.w_resp_c[6]));
}

CtImShdrSet2* ct_im_shdr_set2_get(void)
{
	static CtImShdrSet2* self = NULL;

	if (!self) {
		self = k_object_new_with_private(CT_TYPE_IM_SHDR_SET2, sizeof(CtImShdrSet2Private));
	}

	return self;
}
