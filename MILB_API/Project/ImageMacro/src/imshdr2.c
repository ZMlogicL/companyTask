/*
 * imshdr2.c
 *
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :卢樊
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、interrupt setting process api
*2、
*@version:        1.0.0
*/

#include "jdsshdr.h"
#include "dd_top.h"
#include "ddim_user_custom.h"
#include "imshdr.h"

#include "imshdr2.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImShdr2, im_shdr2);
#define IM_SHDR2_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImShdr2Private, IM_TYPE_SHDR2))

struct _ImShdr2Private
{
	int a;
};


static void im_shdr2_constructor(ImShdr2 *self)
{
//	ImShdr2Private *priv = IM_SHDR2_GET_PRIVATE(self);
}

static void im_shdr2_destructor(ImShdr2 *self)
{
//	ImShdr2Private *priv = IM_SHDR2_GET_PRIVATE(self);
}

static ImShdr2 imShdr2;
static char isImShdr2 = 0;

static volatile ULONG				S_G_IM_SHDR_AXI_ERR		= D_IM_SHDR_NORMAL_END;
static volatile T_IM_SHDR_CALLBACK			S_G_IM_SHDR_CALLBACK_FUNC			= NULL;
static volatile T_IM_SHDR_LINEINT_CALLBACK	S_G_IM_SHDR_LINEINT_CALLBACK_FUNC	= NULL;

/*
PUBLIC
 */

INT32 Im_SHDR_Ctrl_Common(const  T_IM_SHDR_CTRL*const  shdr_ctrl )
{
	ImShdr2* imShdr2 = im_shdr2_get();
	UCHAR		*gImShdrOutCtrl = im_shdr2_get_gIM_SHDR_Out_Ctrl(imShdr2);

#ifdef CO_PARAM_CHECK
	if ( shdr_ctrl == NULL ) {
		Ddim_Assertion(("Im_SHDR_Ctrl_Common() error. shdr_ctrl = NULL\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_ctrl->image_set.in_bit_depth > D_IM_SHDR_INBITDEPTH_16 ) {
		Ddim_Assertion(("Im_SHDR_Ctrl_Common() error. in_bit_depth is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_ctrl->image_set.in_c_fmt > D_IM_SHDR_INCFMT_422SP ) {
		Ddim_Assertion(("Im_SHDR_Ctrl_Common() error. in_c_fmt is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_ctrl->image_set.in_edge_cpy > D_IM_SHDR_ON ) {
		Ddim_Assertion(("Im_SHDR_Ctrl_Common() error. in_edge_cpy is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_ctrl->image_set.in_edge_cut > D_IM_SHDR_ON ) {
		Ddim_Assertion(("Im_SHDR_Ctrl_Common() error. in_edge_cut is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_ctrl->image_set.out_ctrl > D_IM_SHDR_OUTCTRL_RGB ) {
		Ddim_Assertion(("Im_SHDR_Ctrl_Common() error. out_ctrl is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_ctrl->image_set.out_sel > D_IM_SHDR_OUTSEL_RGB_16 ) {
		Ddim_Assertion(("Im_SHDR_Ctrl_Common() error. out_sel is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_ctrl->image_set.out_sel_en > D_IM_SHDR_ENABLE ) {
		Ddim_Assertion(("Im_SHDR_Ctrl_Common() error. out_sel_en is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	if ( shdr_ctrl->image_mode.fil_margin > D_IM_SHDR_FLITER_MARGIN_96 ) {
		Ddim_Assertion(("Im_SHDR_Ctrl_Common() error. fil_margin is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	if ( shdr_ctrl->image_mode.fil_margin > D_IM_SHDR_FLITER_MARGIN_32 ) {
		Ddim_Assertion(("Im_SHDR_Ctrl_Common() error. fil_margin is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif	// CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	if ( shdr_ctrl->image_mode.fmd_en > D_IM_SHDR_ENABLE ) {
		Ddim_Assertion(("Im_SHDR_Ctrl_Common() error. fmd_en is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_ctrl->image_mode.bypass_en > D_IM_SHDR_ENABLE ) {
		Ddim_Assertion(("Im_SHDR_Ctrl_Common() error. bypass_en is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_ctrl->image_mode.smc_in > D_IM_SHDR_SMCIN_EXT_REF ) {
		Ddim_Assertion(("Im_SHDR_Ctrl_Common() error. smc_in is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_ctrl->image_mode.shdr_in > D_IM_SHDR_SHDRIN_SMCOUT_REF ) {
		Ddim_Assertion(("Im_SHDR_Ctrl_Common() error. shdr_in is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_ctrl->image_mode.tile_size > D_IM_SHDR_TILESIZE_1024x512 ) {
		Ddim_Assertion(("Im_SHDR_Ctrl_Common() error. tile_size is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_ctrl->sdram.r_vfm.a > D_IM_SHDR_VFMT_VIDEO ) {
		Ddim_Assertion(("Im_SHDR_Ctrl_Common() error. r_vfm is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_ctrl->sdram.w_vfm.a > D_IM_SHDR_VFMT_COMPIP_RASTER ) {
		Ddim_Assertion(("Im_SHDR_Ctrl_Common() error. w_vfm.a is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_ctrl->sdram.w_vfm.b > D_IM_SHDR_VFMT_VIDEO ) {
		Ddim_Assertion(("Im_SHDR_Ctrl_Common() error. w_vfm.b is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_ctrl->compip.mode > D_IM_SHDR_COMP_MODE_LOSSLESS ) {
		Ddim_Assertion(("Im_SHDR_Ctrl_Common() error. compip.mode is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_ctrl->compip.mc_mode > D_IM_SHDR_COMP_MC_USED ) {
		Ddim_Assertion(("Im_SHDR_Ctrl_Common() error. compip.mc_mode is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_ctrl->compip.comp_incfmt > D_IM_SHDR_COMP_INCFMT_YUV422 ) {
		Ddim_Assertion(("Im_SHDR_Ctrl_Common() error. compip.comp_incfmt is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_ctrl->compip.r_bypass_mode > D_IM_SHDR_ENABLE ) {
		Ddim_Assertion(("Im_SHDR_Ctrl_Common() error. compip.r_bypass_mode is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_ctrl->compip.w_bypass_mode > D_IM_SHDR_ENABLE ) {
		Ddim_Assertion(("Im_SHDR_Ctrl_Common() error. compip.w_bypass_mode is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_ctrl->compip.r_img_axi_size > D_IM_SHDR_COMP_AXI_256 ) {
		Ddim_Assertion(("Im_SHDR_Ctrl_Common() error. compip.r_img_axi_size is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_ctrl->compip.r_comp_axi_size > D_IM_SHDR_COMP_AXI_256 ) {
		Ddim_Assertion(("Im_SHDR_Ctrl_Common() error. compip.r_comp_axi_size is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_ctrl->compip.w_img_axi_size > D_IM_SHDR_COMP_AXI_256 ) {
		Ddim_Assertion(("Im_SHDR_Ctrl_Common() error. compip.w_img_axi_size is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_ctrl->compip.lint_mask > D_IM_SHDR_ENABLE ) {
		Ddim_Assertion(("Im_SHDR_Ctrl_Common() error. compip.lint_mask is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_ctrl->compip.lint_sts > D_IM_SHDR_ENABLE ) {
		Ddim_Assertion(("Im_SHDR_Ctrl_Common() error. compip.lint_mask is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
#endif

	// limitation check 1.
	if ( ( shdr_ctrl->image_set.in_bit_depth == D_IM_SHDR_INBITDEPTH_16 ) &&
		 ( shdr_ctrl->image_set.in_c_fmt     == D_IM_SHDR_INCFMT_420SP  ) ) {
		Ddim_Print(("Im_SHDR_Ctrl_Common() : limitation check 1 NG\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}

	// limitation check 2.
	if ( ( shdr_ctrl->image_mode.bypass_en  == D_IM_SHDR_DISABLE                ) &&
		 ( shdr_ctrl->image_set.in_edge_cpy != shdr_ctrl->image_set.in_edge_cut ) ) {
		Ddim_Print(("Im_SHDR_Ctrl_Common() : limitation check 2 NG\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}

	// limitation check 3.
	if ( ( shdr_ctrl->image_mode.shdr_in    == D_IM_SHDR_SHDRIN_SMCOUT_REF ) &&
		 ( shdr_ctrl->image_set.in_edge_cut == D_IM_SHDR_ON                ) ) {
		Ddim_Print(("Im_SHDR_Ctrl_Common() : limitation check 3 NG\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}

	// limitation check 4.
	if ( shdr_ctrl->image_set.out_ctrl != shdr_ctrl->image_set.out_sel ) {
		Ddim_Print(("Im_SHDR_Ctrl_Common() : limitation check 4 NG\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}

	// limitation check 5.
	if ( ( shdr_ctrl->image_set.in_edge_cpy == D_IM_SHDR_OFF ) &&
		 ( shdr_ctrl->image_mode.shift_x != 0 ) &&
		 ( shdr_ctrl->image_mode.shift_y != 0 ) ) {
		Ddim_Print(("Im_SHDR_Ctrl_Common() : limitation check 5 NG\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}

	im_shdr_on_pclk();
	im_shdr_dsb();

	// Wait SHDR Stop.
	while ( IO_SHDR.SHDRACTL1.bit.TRG == D_IM_SHDR_TRG_STATUS_START ) {

		DDIM_User_Dly_Tsk( 1 );

		Ddim_Print(("Im_SHDR_Ctrl_Common() : SHDR Processing\n"));
	}

	// User callback function setting.
	S_G_IM_SHDR_AXI_ERR				= D_IM_SHDR_NORMAL_END;
	S_G_IM_SHDR_CALLBACK_FUNC			= shdr_ctrl->pCallBack;
	S_G_IM_SHDR_LINEINT_CALLBACK_FUNC	= shdr_ctrl->pLineInt_CallBack;

	*gImShdrOutCtrl				= shdr_ctrl->image_set.out_ctrl;

	// Image setting.
	// Input.
	IO_SHDR.SHDRIFRM.bit.IBITS0					= shdr_ctrl->image_set.in_bit_depth;
	IO_SHDR.SHDRIFRM.bit.INCFMT					= shdr_ctrl->image_set.in_c_fmt;
	IO_SHDR.SHDRIFRM.bit.EDGECPY				= shdr_ctrl->image_set.in_edge_cpy;
	IO_SHDR.SHDRIFRM.bit.EDGECUT				= shdr_ctrl->image_set.in_edge_cut;

	// Output.
	IO_SHDR.SHDROFRM.bit.OUTCTRL				= shdr_ctrl->image_set.out_ctrl;
	IO_SHDR.SHDROFRM.bit.OUTSEL					= shdr_ctrl->image_set.out_sel;
	IO_SHDR.SHDROFRM.bit.OUTSELEN				= shdr_ctrl->image_set.out_sel_en;

	// Read SDRAM setting.
	// Address.
	IO_SHDR.SDRR_ADDR_A.bit.SDRR_ADDR_A_0		= shdr_ctrl->sdram.r_addr.a_y;
	IO_SHDR.SDRR_ADDR_A.bit.SDRR_ADDR_A_1		= shdr_ctrl->sdram.r_addr.a_c;
	IO_SHDR.SDRR_ADDR_B.bit.SDRR_ADDR_B_0		= shdr_ctrl->sdram.r_addr.b_y;
	IO_SHDR.SDRR_ADDR_B.bit.SDRR_ADDR_B_1		= shdr_ctrl->sdram.r_addr.b_c;
	IO_SHDR.SDRR_ADDR_C.bit.SDRR_ADDR_C_0		= shdr_ctrl->sdram.r_addr.c_y;
	IO_SHDR.SDRR_ADDR_C.bit.SDRR_ADDR_C_1		= shdr_ctrl->sdram.r_addr.c_c;
	IO_SHDR.SDRR_ADDR_D.bit.SDRR_ADDR_D_0		= shdr_ctrl->sdram.r_addr.d_y;
	IO_SHDR.SDRR_ADDR_D.bit.SDRR_ADDR_D_1		= shdr_ctrl->sdram.r_addr.d_c;
	IO_SHDR.SDRR_ADDR_E.bit.SDRR_ADDR_E_0		= shdr_ctrl->sdram.r_addr.e_y;
	IO_SHDR.SDRR_ADDR_E.bit.SDRR_ADDR_E_1		= shdr_ctrl->sdram.r_addr.e_c;
	IO_SHDR.SDRR_ADDR_F.bit.SDRR_ADDR_F_0		= shdr_ctrl->sdram.r_addr.f;

	// Global horizontal size.
	IO_SHDR.SDRR_GHSIZE_A.bit.SDRR_GHSIZE_A_0	= shdr_ctrl->sdram.r_ghsize.a_y;
	IO_SHDR.SDRR_GHSIZE_A.bit.SDRR_GHSIZE_A_1	= shdr_ctrl->sdram.r_ghsize.a_c;
	IO_SHDR.SDRR_GHSIZE_B.bit.SDRR_GHSIZE_B_0	= shdr_ctrl->sdram.r_ghsize.b_y;
	IO_SHDR.SDRR_GHSIZE_B.bit.SDRR_GHSIZE_B_1	= shdr_ctrl->sdram.r_ghsize.b_c;
	IO_SHDR.SDRR_GHSIZE_C.bit.SDRR_GHSIZE_C_0	= shdr_ctrl->sdram.r_ghsize.c_y;
	IO_SHDR.SDRR_GHSIZE_C.bit.SDRR_GHSIZE_C_1	= shdr_ctrl->sdram.r_ghsize.c_c;
	IO_SHDR.SDRR_GHSIZE_D.bit.SDRR_GHSIZE_D_0	= shdr_ctrl->sdram.r_ghsize.d_y;
	IO_SHDR.SDRR_GHSIZE_D.bit.SDRR_GHSIZE_D_1	= shdr_ctrl->sdram.r_ghsize.d_c;
	IO_SHDR.SDRR_GHSIZE_E.bit.SDRR_GHSIZE_E_0	= shdr_ctrl->sdram.r_ghsize.e_y;
	IO_SHDR.SDRR_GHSIZE_E.bit.SDRR_GHSIZE_E_1	= shdr_ctrl->sdram.r_ghsize.e_c;
	IO_SHDR.SDRR_GHSIZE_F.bit.SDRR_GHSIZE_F_0	= shdr_ctrl->sdram.r_ghsize.f;

	// Video format.
	IO_SHDR.SDRR_VFM.bit.SDRR_VFM_A				= shdr_ctrl->sdram.r_vfm.a;

	// Horizontal size.
	IO_SHDR.SDRR_HSIZE_A.bit.SDRR_HSIZE_A		= shdr_ctrl->sdram.r_hsize.a;
	IO_SHDR.SDRR_HSIZE_B.bit.SDRR_HSIZE_B		= shdr_ctrl->sdram.r_hsize.b;
	IO_SHDR.SDRR_HSIZE_C.bit.SDRR_HSIZE_C		= shdr_ctrl->sdram.r_hsize.c;
	IO_SHDR.SDRR_HSIZE_D.bit.SDRR_HSIZE_D		= shdr_ctrl->sdram.r_hsize.d;
	IO_SHDR.SDRR_HSIZE_E.bit.SDRR_HSIZE_E		= shdr_ctrl->sdram.r_hsize.e;

	// Vertical size.
	IO_SHDR.SDRR_VSIZE_A.bit.SDRR_VSIZE_A		= shdr_ctrl->sdram.r_vsize.a;
	IO_SHDR.SDRR_VSIZE_B.bit.SDRR_VSIZE_B		= shdr_ctrl->sdram.r_vsize.b;
	IO_SHDR.SDRR_VSIZE_C.bit.SDRR_VSIZE_C		= shdr_ctrl->sdram.r_vsize.c;
	IO_SHDR.SDRR_VSIZE_D.bit.SDRR_VSIZE_D		= shdr_ctrl->sdram.r_vsize.d;
	IO_SHDR.SDRR_VSIZE_E.bit.SDRR_VSIZE_E		= shdr_ctrl->sdram.r_vsize.e;

	// Write SDRAM setting.
	// Address.
	IO_SHDR.SDRW_ADDR_B.bit.SDRW_ADDR_B_0		= shdr_ctrl->sdram.w_addr.b_y;
	IO_SHDR.SDRW_ADDR_B.bit.SDRW_ADDR_B_1		= shdr_ctrl->sdram.w_addr.b_c;
	IO_SHDR.SDRW_ADDR_E.bit.SDRW_ADDR_E_0		= shdr_ctrl->sdram.w_addr.e_y;
	IO_SHDR.SDRW_ADDR_E.bit.SDRW_ADDR_E_1		= shdr_ctrl->sdram.w_addr.e_c;
	IO_SHDR.SDRW_ADDR_F.bit.SDRW_ADDR_F_0		= shdr_ctrl->sdram.w_addr.f_y;
	IO_SHDR.SDRW_ADDR_F.bit.SDRW_ADDR_F_1		= shdr_ctrl->sdram.w_addr.f_c;
	IO_SHDR.SDRW_ADDR_G.bit.SDRW_ADDR_G_0		= shdr_ctrl->sdram.w_addr.g_r_y;
	IO_SHDR.SDRW_ADDR_G.bit.SDRW_ADDR_G_1		= shdr_ctrl->sdram.w_addr.g_g_c;
	IO_SHDR.SDRW_ADDR_G.bit.SDRW_ADDR_G_2		= shdr_ctrl->sdram.w_addr.g_b;
	IO_SHDR.SDRW_ADDR_H.bit.SDRW_ADDR_H_0		= shdr_ctrl->sdram.w_addr.h_x;
	IO_SHDR.SDRW_ADDR_H.bit.SDRW_ADDR_H_1		= shdr_ctrl->sdram.w_addr.h_y;
	IO_SHDR.SDRW_ADDR_I.bit.SDRW_ADDR_I_0		= shdr_ctrl->sdram.w_addr.i;

	// Grlobal horizontal size.
	IO_SHDR.SDRW_GHSIZE_B.bit.SDRW_GHSIZE_B_0	= shdr_ctrl->sdram.w_ghsize.b_y;
	IO_SHDR.SDRW_GHSIZE_B.bit.SDRW_GHSIZE_B_1	= shdr_ctrl->sdram.w_ghsize.b_c;
	IO_SHDR.SDRW_GHSIZE_E.bit.SDRW_GHSIZE_E_0	= shdr_ctrl->sdram.w_ghsize.e_y;
	IO_SHDR.SDRW_GHSIZE_E.bit.SDRW_GHSIZE_E_1	= shdr_ctrl->sdram.w_ghsize.e_c;
	IO_SHDR.SDRW_GHSIZE_F.bit.SDRW_GHSIZE_F_0	= shdr_ctrl->sdram.w_ghsize.f_y;
	IO_SHDR.SDRW_GHSIZE_F.bit.SDRW_GHSIZE_F_1	= shdr_ctrl->sdram.w_ghsize.f_c;
	IO_SHDR.SDRW_GHSIZE_G.bit.SDRW_GHSIZE_G_0	= shdr_ctrl->sdram.w_ghsize.g_r_y;
	IO_SHDR.SDRW_GHSIZE_G.bit.SDRW_GHSIZE_G_1	= shdr_ctrl->sdram.w_ghsize.g_g_c;
	IO_SHDR.SDRW_GHSIZE_G.bit.SDRW_GHSIZE_G_2	= shdr_ctrl->sdram.w_ghsize.g_b;
	IO_SHDR.SDRW_GHSIZE_H.bit.SDRW_GHSIZE_H_0	= shdr_ctrl->sdram.w_ghsize.h_x;
	IO_SHDR.SDRW_GHSIZE_H.bit.SDRW_GHSIZE_H_1	= shdr_ctrl->sdram.w_ghsize.h_y;
	IO_SHDR.SDRW_GHSIZE_I.bit.SDRW_GHSIZE_I_0	= shdr_ctrl->sdram.w_ghsize.i;

	// Video format.
	IO_SHDR.SDRW_GHSIZE_I.bit.SDRW_VFM_A		= shdr_ctrl->sdram.w_vfm.a;
	IO_SHDR.SDRW_VFM.bit.SDRW_VFM_B				= shdr_ctrl->sdram.w_vfm.b;

	// Base address.
	IO_SHDR.SDRW_BA_A.bit.SDRW_BA_A_0			= shdr_ctrl->sdram.w_baddr.a_y;
	IO_SHDR.SDRW_BA_A.bit.SDRW_BA_A_1			= shdr_ctrl->sdram.w_baddr.a_c;
	IO_SHDR.SDRW_BA_C.bit.SDRW_BA_C_0			= shdr_ctrl->sdram.w_baddr.c_y;
	IO_SHDR.SDRW_BA_C.bit.SDRW_BA_C_1			= shdr_ctrl->sdram.w_baddr.c_c;
	IO_SHDR.SDRW_BA_D.bit.SDRW_BA_D_0			= shdr_ctrl->sdram.w_baddr.d_y;
	IO_SHDR.SDRW_BA_D.bit.SDRW_BA_D_1			= shdr_ctrl->sdram.w_baddr.d_c;

	// Horizontal size.
	IO_SHDR.SDRW_FW_A.bit.SDRW_FW_A				= shdr_ctrl->sdram.w_hsize.a;
	IO_SHDR.SDRW_FW_C.bit.SDRW_FW_C				= shdr_ctrl->sdram.w_hsize.c;
	IO_SHDR.SDRW_FW_D.bit.SDRW_FW_D				= shdr_ctrl->sdram.w_hsize.d;

	// Image mode.
	// Exposure magnification.
	IO_SHDR.EXMAG.bit.EXMAG						= shdr_ctrl->image_mode.exp_mag;

	// Reciprocal of the exposure magnification.
	IO_SHDR.REMVAL.bit.REXMAG					= shdr_ctrl->image_mode.rexp_mag;
	im_shdr_set_reg_signed( IO_SHDR.REMVAL, union io_shdr_remval, REMSFT, shdr_ctrl->image_mode.rexp_mag_shift );

	// Shift.
	im_shdr_set_reg_signed( IO_SHDR.SHIFT, union io_shdr_shift, SHIFTX, shdr_ctrl->image_mode.shift_x );
	im_shdr_set_reg_signed( IO_SHDR.SHIFT, union io_shdr_shift, SHIFTY, shdr_ctrl->image_mode.shift_y );

	// Filter margin.
	IO_SHDR.MRGN.bit.MRGN						= shdr_ctrl->image_mode.fil_margin;

	// FMC/Bypass enable. SMC/SHDR input select.
	IO_SHDR.FLWCNT.bit.FMDEN					= shdr_ctrl->image_mode.fmd_en;
	IO_SHDR.FLWCNT.bit.BPEN						= shdr_ctrl->image_mode.bypass_en;
	IO_SHDR.FLWCNT.bit.SMCIN					= shdr_ctrl->image_mode.smc_in;
	IO_SHDR.FLWCNT.bit.BRSEL					= shdr_ctrl->image_mode.shdr_in;

	// Tile size select.
	IO_SHDR.TMODE.bit.TMODE						= shdr_ctrl->image_mode.tile_size;

	// COMPIP.
	IO_SHDR.MODESEL.bit.MODE					= shdr_ctrl->compip.mode;
	IO_SHDR.MC_MODESEL.bit.MODE					= shdr_ctrl->compip.mc_mode;
	IO_SHDR.COMP_INCFMSEL.bit.MODE				= shdr_ctrl->compip.comp_incfmt;
	IO_SHDR.BYPASSON.bit.RMD					= shdr_ctrl->compip.r_bypass_mode;
	IO_SHDR.BYPASSON.bit.WMD					= shdr_ctrl->compip.w_bypass_mode;
	IO_SHDR.AXISIZE.bit.RYC						= shdr_ctrl->compip.r_img_axi_size;		// RFID=A0/A1.
	IO_SHDR.AXISIZE.bit.RCI						= shdr_ctrl->compip.r_comp_axi_size;	// RFID=A0/A1.
	IO_SHDR.AXISIZE.bit.WR						= shdr_ctrl->compip.w_img_axi_size;		// RFID=A0/A1.
	IO_SHDR.LINT.bit.NO							= shdr_ctrl->compip.lint_no;
	IO_SHDR.LINT.bit.MSK						= shdr_ctrl->compip.lint_mask;
	IO_SHDR.LINT.bit.ST							= shdr_ctrl->compip.lint_sts;
	IO_SHDR.WRSTARTADDR.bit.ADDR_Y				= shdr_ctrl->compip.w_addr_y;
	IO_SHDR.WRSTARTADDR.bit.ADDR_C				= shdr_ctrl->compip.w_addr_c;
	IO_SHDR.RDSTARTADDR.bit.ADDR_Y				= shdr_ctrl->compip.r_addr_y;
	IO_SHDR.RDSTARTADDR.bit.ADDR_C				= shdr_ctrl->compip.r_addr_c;

	im_shdr_off_pclk();
	im_shdr_dsb();

	return D_DDIM_OK;
}


INT32 Im_SHDR_Get_Ctrl_Common( T_IM_SHDR_CTRL* const shdr_ctrl )
{
#ifdef CO_PARAM_CHECK
	if ( shdr_ctrl == NULL ) {
		Ddim_Assertion(("Im_SHDR_Get_Ctrl_Common() error. shdr_ctrl = NULL\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
#endif

	im_shdr_on_pclk();
	im_shdr_dsb();

	// Image setting.
	// Input.
	shdr_ctrl->image_set.in_bit_depth	= IO_SHDR.SHDRIFRM.bit.IBITS0;
	shdr_ctrl->image_set.in_c_fmt		= IO_SHDR.SHDRIFRM.bit.INCFMT;
	shdr_ctrl->image_set.in_edge_cpy	= IO_SHDR.SHDRIFRM.bit.EDGECPY;
	shdr_ctrl->image_set.in_edge_cut	= IO_SHDR.SHDRIFRM.bit.EDGECUT;

	// Output.
	shdr_ctrl->image_set.out_ctrl		= IO_SHDR.SHDROFRM.bit.OUTCTRL;
	shdr_ctrl->image_set.out_sel		= IO_SHDR.SHDROFRM.bit.OUTSEL;
	shdr_ctrl->image_set.out_sel_en		= IO_SHDR.SHDROFRM.bit.OUTSELEN;

	// Read SDRAM setting.
	// Address.
	shdr_ctrl->sdram.r_addr.a_y			= IO_SHDR.SDRR_ADDR_A.bit.SDRR_ADDR_A_0;
	shdr_ctrl->sdram.r_addr.a_c			= IO_SHDR.SDRR_ADDR_A.bit.SDRR_ADDR_A_1;
	shdr_ctrl->sdram.r_addr.b_y			= IO_SHDR.SDRR_ADDR_B.bit.SDRR_ADDR_B_0;
	shdr_ctrl->sdram.r_addr.b_c			= IO_SHDR.SDRR_ADDR_B.bit.SDRR_ADDR_B_1;
	shdr_ctrl->sdram.r_addr.c_y			= IO_SHDR.SDRR_ADDR_C.bit.SDRR_ADDR_C_0;
	shdr_ctrl->sdram.r_addr.c_c			= IO_SHDR.SDRR_ADDR_C.bit.SDRR_ADDR_C_1;
	shdr_ctrl->sdram.r_addr.d_y			= IO_SHDR.SDRR_ADDR_D.bit.SDRR_ADDR_D_0;
	shdr_ctrl->sdram.r_addr.d_c			= IO_SHDR.SDRR_ADDR_D.bit.SDRR_ADDR_D_1;
	shdr_ctrl->sdram.r_addr.e_y			= IO_SHDR.SDRR_ADDR_E.bit.SDRR_ADDR_E_0;
	shdr_ctrl->sdram.r_addr.e_c			= IO_SHDR.SDRR_ADDR_E.bit.SDRR_ADDR_E_1;
	shdr_ctrl->sdram.r_addr.f			= IO_SHDR.SDRR_ADDR_F.bit.SDRR_ADDR_F_0;

	// Global horizontal size.
	shdr_ctrl->sdram.r_ghsize.a_y		= IO_SHDR.SDRR_GHSIZE_A.bit.SDRR_GHSIZE_A_0;
	shdr_ctrl->sdram.r_ghsize.a_c		= IO_SHDR.SDRR_GHSIZE_A.bit.SDRR_GHSIZE_A_1;
	shdr_ctrl->sdram.r_ghsize.b_y		= IO_SHDR.SDRR_GHSIZE_B.bit.SDRR_GHSIZE_B_0;
	shdr_ctrl->sdram.r_ghsize.b_c		= IO_SHDR.SDRR_GHSIZE_B.bit.SDRR_GHSIZE_B_1;
	shdr_ctrl->sdram.r_ghsize.c_y		= IO_SHDR.SDRR_GHSIZE_C.bit.SDRR_GHSIZE_C_0;
	shdr_ctrl->sdram.r_ghsize.c_c		= IO_SHDR.SDRR_GHSIZE_C.bit.SDRR_GHSIZE_C_1;
	shdr_ctrl->sdram.r_ghsize.d_y		= IO_SHDR.SDRR_GHSIZE_D.bit.SDRR_GHSIZE_D_0;
	shdr_ctrl->sdram.r_ghsize.d_c		= IO_SHDR.SDRR_GHSIZE_D.bit.SDRR_GHSIZE_D_1;
	shdr_ctrl->sdram.r_ghsize.e_y		= IO_SHDR.SDRR_GHSIZE_E.bit.SDRR_GHSIZE_E_0;
	shdr_ctrl->sdram.r_ghsize.e_c		= IO_SHDR.SDRR_GHSIZE_E.bit.SDRR_GHSIZE_E_1;
	shdr_ctrl->sdram.r_ghsize.f			= IO_SHDR.SDRR_GHSIZE_F.bit.SDRR_GHSIZE_F_0;

	// Video format.
	shdr_ctrl->sdram.r_vfm.a			= IO_SHDR.SDRR_VFM.bit.SDRR_VFM_A;

	// Horizontal size.
	shdr_ctrl->sdram.r_hsize.a			= IO_SHDR.SDRR_HSIZE_A.bit.SDRR_HSIZE_A;
	shdr_ctrl->sdram.r_hsize.b			= IO_SHDR.SDRR_HSIZE_B.bit.SDRR_HSIZE_B;
	shdr_ctrl->sdram.r_hsize.c			= IO_SHDR.SDRR_HSIZE_C.bit.SDRR_HSIZE_C;
	shdr_ctrl->sdram.r_hsize.d			= IO_SHDR.SDRR_HSIZE_D.bit.SDRR_HSIZE_D;
	shdr_ctrl->sdram.r_hsize.e			= IO_SHDR.SDRR_HSIZE_E.bit.SDRR_HSIZE_E;

	// Vertical size.
	shdr_ctrl->sdram.r_vsize.a			= IO_SHDR.SDRR_VSIZE_A.bit.SDRR_VSIZE_A;
	shdr_ctrl->sdram.r_vsize.b			= IO_SHDR.SDRR_VSIZE_B.bit.SDRR_VSIZE_B;
	shdr_ctrl->sdram.r_vsize.c			= IO_SHDR.SDRR_VSIZE_C.bit.SDRR_VSIZE_C;
	shdr_ctrl->sdram.r_vsize.d			= IO_SHDR.SDRR_VSIZE_D.bit.SDRR_VSIZE_D;
	shdr_ctrl->sdram.r_vsize.e			= IO_SHDR.SDRR_VSIZE_E.bit.SDRR_VSIZE_E;

	// Write SDRAM setting.
	// Address.
	shdr_ctrl->sdram.w_addr.b_y			= IO_SHDR.SDRW_ADDR_B.bit.SDRW_ADDR_B_0;
	shdr_ctrl->sdram.w_addr.b_c			= IO_SHDR.SDRW_ADDR_B.bit.SDRW_ADDR_B_1;
	shdr_ctrl->sdram.w_addr.e_y			= IO_SHDR.SDRW_ADDR_E.bit.SDRW_ADDR_E_0;
	shdr_ctrl->sdram.w_addr.e_c			= IO_SHDR.SDRW_ADDR_E.bit.SDRW_ADDR_E_1;
	shdr_ctrl->sdram.w_addr.f_y			= IO_SHDR.SDRW_ADDR_F.bit.SDRW_ADDR_F_0;
	shdr_ctrl->sdram.w_addr.f_c			= IO_SHDR.SDRW_ADDR_F.bit.SDRW_ADDR_F_1;
	shdr_ctrl->sdram.w_addr.g_r_y		= IO_SHDR.SDRW_ADDR_G.bit.SDRW_ADDR_G_0;
	shdr_ctrl->sdram.w_addr.g_g_c		= IO_SHDR.SDRW_ADDR_G.bit.SDRW_ADDR_G_1;
	shdr_ctrl->sdram.w_addr.g_b			= IO_SHDR.SDRW_ADDR_G.bit.SDRW_ADDR_G_2;
	shdr_ctrl->sdram.w_addr.h_x			= IO_SHDR.SDRW_ADDR_H.bit.SDRW_ADDR_H_0;
	shdr_ctrl->sdram.w_addr.h_y			= IO_SHDR.SDRW_ADDR_H.bit.SDRW_ADDR_H_1;
	shdr_ctrl->sdram.w_addr.i			= IO_SHDR.SDRW_ADDR_I.bit.SDRW_ADDR_I_0;

	// Grlobal horizontal size.
	shdr_ctrl->sdram.w_ghsize.b_y		= IO_SHDR.SDRW_GHSIZE_B.bit.SDRW_GHSIZE_B_0;
	shdr_ctrl->sdram.w_ghsize.b_c		= IO_SHDR.SDRW_GHSIZE_B.bit.SDRW_GHSIZE_B_1;
	shdr_ctrl->sdram.w_ghsize.e_y		= IO_SHDR.SDRW_GHSIZE_E.bit.SDRW_GHSIZE_E_0;
	shdr_ctrl->sdram.w_ghsize.e_c		= IO_SHDR.SDRW_GHSIZE_E.bit.SDRW_GHSIZE_E_1;
	shdr_ctrl->sdram.w_ghsize.f_y		= IO_SHDR.SDRW_GHSIZE_F.bit.SDRW_GHSIZE_F_0;
	shdr_ctrl->sdram.w_ghsize.f_c		= IO_SHDR.SDRW_GHSIZE_F.bit.SDRW_GHSIZE_F_1;
	shdr_ctrl->sdram.w_ghsize.g_r_y		= IO_SHDR.SDRW_GHSIZE_G.bit.SDRW_GHSIZE_G_0;
	shdr_ctrl->sdram.w_ghsize.g_g_c		= IO_SHDR.SDRW_GHSIZE_G.bit.SDRW_GHSIZE_G_1;
	shdr_ctrl->sdram.w_ghsize.g_b		= IO_SHDR.SDRW_GHSIZE_G.bit.SDRW_GHSIZE_G_2;
	shdr_ctrl->sdram.w_ghsize.h_x		= IO_SHDR.SDRW_GHSIZE_H.bit.SDRW_GHSIZE_H_0;
	shdr_ctrl->sdram.w_ghsize.h_y		= IO_SHDR.SDRW_GHSIZE_H.bit.SDRW_GHSIZE_H_1;
	shdr_ctrl->sdram.w_ghsize.i			= IO_SHDR.SDRW_GHSIZE_I.bit.SDRW_GHSIZE_I_0;

	// Video format.
	shdr_ctrl->sdram.w_vfm.a			= IO_SHDR.SDRW_GHSIZE_I.bit.SDRW_VFM_A;
	shdr_ctrl->sdram.w_vfm.b			= IO_SHDR.SDRW_VFM.bit.SDRW_VFM_B;

	// Base address.
	shdr_ctrl->sdram.w_baddr.a_y		= IO_SHDR.SDRW_BA_A.bit.SDRW_BA_A_0;
	shdr_ctrl->sdram.w_baddr.a_c		= IO_SHDR.SDRW_BA_A.bit.SDRW_BA_A_1;
	shdr_ctrl->sdram.w_baddr.c_y		= IO_SHDR.SDRW_BA_C.bit.SDRW_BA_C_0;
	shdr_ctrl->sdram.w_baddr.c_c		= IO_SHDR.SDRW_BA_C.bit.SDRW_BA_C_1;
	shdr_ctrl->sdram.w_baddr.d_y		= IO_SHDR.SDRW_BA_D.bit.SDRW_BA_D_0;
	shdr_ctrl->sdram.w_baddr.d_c		= IO_SHDR.SDRW_BA_D.bit.SDRW_BA_D_1;

	// Horizontal size.
	shdr_ctrl->sdram.w_hsize.a			= IO_SHDR.SDRW_FW_A.bit.SDRW_FW_A;
	shdr_ctrl->sdram.w_hsize.c			= IO_SHDR.SDRW_FW_C.bit.SDRW_FW_C;
	shdr_ctrl->sdram.w_hsize.d			= IO_SHDR.SDRW_FW_D.bit.SDRW_FW_D;

	// Image mode.
	// Exposure magnification.
	shdr_ctrl->image_mode.exp_mag		= IO_SHDR.EXMAG.bit.EXMAG;

	// Reciprocal of the exposure magnification.
	shdr_ctrl->image_mode.rexp_mag		= IO_SHDR.REMVAL.bit.REXMAG;
	im_shdr_get_reg_signed( shdr_ctrl->image_mode.rexp_mag_shift, IO_SHDR.REMVAL, union io_shdr_remval, REMSFT );

	// Shift.
	im_shdr_get_reg_signed( shdr_ctrl->image_mode.shift_x, IO_SHDR.SHIFT, union io_shdr_shift, SHIFTX );
	im_shdr_get_reg_signed( shdr_ctrl->image_mode.shift_y, IO_SHDR.SHIFT, union io_shdr_shift, SHIFTY );

	// Filter margin.
	shdr_ctrl->image_mode.fil_margin	= IO_SHDR.MRGN.bit.MRGN;

	// FMC/Bypass enable. SMC/SHDR input select.
	shdr_ctrl->image_mode.fmd_en		= IO_SHDR.FLWCNT.bit.FMDEN;
	shdr_ctrl->image_mode.bypass_en		= IO_SHDR.FLWCNT.bit.BPEN;
	shdr_ctrl->image_mode.smc_in		= IO_SHDR.FLWCNT.bit.SMCIN;
	shdr_ctrl->image_mode.shdr_in		= IO_SHDR.FLWCNT.bit.BRSEL;

	// Tile size select.
	shdr_ctrl->image_mode.tile_size		= IO_SHDR.TMODE.bit.TMODE;

	// COMPIP.
	shdr_ctrl->compip.mode				= IO_SHDR.MODESEL.bit.MODE;
	shdr_ctrl->compip.mc_mode			= IO_SHDR.MC_MODESEL.bit.MODE;
	shdr_ctrl->compip.comp_incfmt		= IO_SHDR.COMP_INCFMSEL.bit.MODE;
	shdr_ctrl->compip.r_bypass_mode		= IO_SHDR.BYPASSON.bit.RMD;
	shdr_ctrl->compip.w_bypass_mode		= IO_SHDR.BYPASSON.bit.WMD;
	shdr_ctrl->compip.r_img_axi_size	= IO_SHDR.AXISIZE.bit.RYC;
	shdr_ctrl->compip.r_comp_axi_size	= IO_SHDR.AXISIZE.bit.RCI;
	shdr_ctrl->compip.w_img_axi_size	= IO_SHDR.AXISIZE.bit.WR;
	shdr_ctrl->compip.lint_no			= IO_SHDR.LINT.bit.NO;
	shdr_ctrl->compip.lint_mask			= IO_SHDR.LINT.bit.MSK;
	shdr_ctrl->compip.lint_sts			= IO_SHDR.LINT.bit.ST;
	shdr_ctrl->compip.w_addr_y			= IO_SHDR.WRSTARTADDR.bit.ADDR_Y;
	shdr_ctrl->compip.w_addr_c			= IO_SHDR.WRSTARTADDR.bit.ADDR_C;
	shdr_ctrl->compip.r_addr_y			= IO_SHDR.RDSTARTADDR.bit.ADDR_Y;
	shdr_ctrl->compip.r_addr_c			= IO_SHDR.RDSTARTADDR.bit.ADDR_C;

	im_shdr_off_pclk();
	im_shdr_dsb();

	return D_DDIM_OK;
}




INT32 Im_SHDR_Wait_End( UINT32* const p_wait_factor, const INT32 wait_time )
{
	DDIM_USER_FLGPTN	waitptn;
	DDIM_USER_FLGPTN	flgptn;
	DDIM_USER_ER		ercd;
	INT32				ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ( ( p_wait_factor == NULL ) ||
		 ( im_shdr_check_wait_time( wait_time ) == FALSE) ) {
		Ddim_Assertion(("Im_SHDR_Wait_End parameter error\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
#endif

	waitptn = ( D_IM_SHDR_FLG_END | D_IM_SHDR_FLG_STOP );

	// SHDR wait end.
	ercd = DDIM_User_Twai_Flg( FID_IM_SHDR, waitptn, D_DDIM_USER_TWF_ORW, &flgptn, (DDIM_USER_TMO)wait_time );

	if ( ercd == D_DDIM_USER_E_TMOUT ) {

		Ddim_Print(("Im_SHDR_Wait_End() time out. ercd = %d\n", ercd));

		ret = D_IM_SHDR_TIMEOUT;
	}
	else if ( ercd != D_DDIM_USER_E_OK ) {

		Ddim_Print(("Im_SHDR_Wait_End() system error. ercd = %d\n", ercd));

		ret = D_IM_SHDR_NG;
	}
	else {
		flgptn = waitptn & flgptn;
		(VOID)DDIM_User_Clr_Flg( FID_IM_SHDR, ~flgptn );
	}

	*p_wait_factor = (UINT32)flgptn;

	if ( ret == D_DDIM_OK ) {
		// Check AXI error.
		if ( S_G_IM_SHDR_AXI_ERR != D_IM_SHDR_NORMAL_END ) {
			Ddim_Print(("Im_SHDR_Wait_End() AXI error. ercd = %lu\n", S_G_IM_SHDR_AXI_ERR));
			ret = D_IM_SHDR_AXI_ERROR;
		}
	}

	im_shdr_off_clk();
	im_shdr_off_xclk();
	im_shdr_dsb();

	return ret;
}

VOID Im_SHDR_Int_Handler( VOID )
{
	DDIM_USER_ER			ercd;
	union io_shdr_shdrint0	shdrint0;
	union io_shdr_shdrint1	shdrint1;

	S_G_IM_SHDR_AXI_ERR = D_IM_SHDR_NORMAL_END;

	im_shdr_on_pclk();
	im_shdr_dsb();

	shdrint0.word = IO_SHDR.SHDRINT0.word;
	shdrint1.word = IO_SHDR.SHDRINT1.word;

	// AXI write error check.
	if ( ( shdrint0.bit.AXWEEN == 1 ) && ( shdrint1.bit.__AXWEFLG == 1 ) ) {	/* pgr0872 */
#ifdef CO_SHDR_DEBUG_PRINT
		Ddim_Print(("BRESPA[0] = %d\n", IO_SHDR.AXICTLWA.bit.BRESPA_0));
		Ddim_Print(("BRESPA[1] = %d\n", IO_SHDR.AXICTLWA.bit.BRESPA_1));
		Ddim_Print(("BRESPA[2] = %d\n", IO_SHDR.AXICTLWA.bit.BRESPA_2));
		Ddim_Print(("BRESPA[3] = %d\n", IO_SHDR.AXICTLWA.bit.BRESPA_3));
		Ddim_Print(("BRESPB[0] = %d\n", IO_SHDR.AXICTLWB.bit.BRESPB_0));
		Ddim_Print(("BRESPB[1] = %d\n", IO_SHDR.AXICTLWB.bit.BRESPB_1));
		Ddim_Print(("BRESPB[2] = %d\n", IO_SHDR.AXICTLWB.bit.BRESPB_2));
		Ddim_Print(("BRESPB[3] = %d\n", IO_SHDR.AXICTLWB.bit.BRESPB_3));
		Ddim_Print(("BRESPB[4] = %d\n", IO_SHDR.AXICTLWB.bit.BRESPB_4));
		Ddim_Print(("BRESPB[5] = %d\n", IO_SHDR.AXICTLWB.bit.BRESPB_5));
		Ddim_Print(("BRESPC[0] = %d\n", IO_SHDR.AXICTLWC.bit.BRESPC_0));
		Ddim_Print(("BRESPC[1] = %d\n", IO_SHDR.AXICTLWC.bit.BRESPC_1));
		Ddim_Print(("BRESPC[2] = %d\n", IO_SHDR.AXICTLWC.bit.BRESPC_2));
		Ddim_Print(("BRESPC[3] = %d\n", IO_SHDR.AXICTLWC.bit.BRESPC_3));
		Ddim_Print(("BRESPC[4] = %d\n", IO_SHDR.AXICTLWC.bit.BRESPC_4));
		Ddim_Print(("BRESPC[5] = %d\n", IO_SHDR.AXICTLWC.bit.BRESPC_5));
		Ddim_Print(("BRESPC[6] = %d\n", IO_SHDR.AXICTLWC.bit.BRESPC_6));
#endif
		IO_SHDR.SHDRINT1.word = D_IM_SHDR_INTF_AXWEFLG;							// flag clear.
		S_G_IM_SHDR_AXI_ERR |= D_IM_SHDR_AXI_ERR_CH_W;
	}

	// AXI read error check.
	if ( ( shdrint0.bit.AXREEN == 1 ) && ( shdrint1.bit.__AXREFLG == 1 ) ) {	/* pgr0872 */
#ifdef CO_SHDR_DEBUG_PRINT
		Ddim_Print(("RRESPA[0] = %d\n", IO_SHDR.AXICTLRA.bit.RRESPA_0));
		Ddim_Print(("RRESPA[1] = %d\n", IO_SHDR.AXICTLRA.bit.RRESPA_1));
		Ddim_Print(("RRESPB[0] = %d\n", IO_SHDR.AXICTLRB.bit.RRESPB_0));
		Ddim_Print(("RRESPB[1] = %d\n", IO_SHDR.AXICTLRB.bit.RRESPB_1));
		Ddim_Print(("RRESPC[0] = %d\n", IO_SHDR.AXICTLRC.bit.RRESPC_0));
		Ddim_Print(("RRESPC[1] = %d\n", IO_SHDR.AXICTLRC.bit.RRESPC_1));
		Ddim_Print(("RRESPC[2] = %d\n", IO_SHDR.AXICTLRC.bit.RRESPC_2));
		Ddim_Print(("RRESPC[3] = %d\n", IO_SHDR.AXICTLRC.bit.RRESPC_3));
		Ddim_Print(("RRESPD[0] = %d\n", IO_SHDR.AXICTLRD.bit.RRESPD_0));
		Ddim_Print(("RRESPD[1] = %d\n", IO_SHDR.AXICTLRD.bit.RRESPD_1));
#endif
		IO_SHDR.SHDRINT1.word = D_IM_SHDR_INTF_AXREFLG;							// flag clear.
		S_G_IM_SHDR_AXI_ERR |= D_IM_SHDR_AXI_ERR_CH_R;
	}

	// SHDR trans end check.
	if ( ( shdrint0.bit.SHDREN == 1 ) && ( shdrint1.bit.__SHDRFLG == 1 ) ) {	/* pgr0872 */
		IO_SHDR.SHDRINT1.word = D_IM_SHDR_INTF_SHDRFLG;							// flag clear.
	}

	im_shdr_dsb();

#ifdef CO_SHDR_DEBUG_PRINT
	Ddim_Print(( "Im_SHDR_Int_Handler shdrint0=0x%lx shdrint1=0x%lx\n", shdrint0.word, shdrint1.word ));
#endif

	ercd = DDIM_User_Set_Flg( FID_IM_SHDR, D_IM_SHDR_FLG_END );
	if ( ercd != D_DDIM_USER_E_OK ) {
		Ddim_Print(("Im_SHDR_Int_Handler : Error DDIM_User_Set_Flg [%d]\n", ercd));
	}

	im_shdr_off_pclk();
	im_shdr_dsb();

	// User callback function.
	if ( S_G_IM_SHDR_CALLBACK_FUNC != NULL ) {
#ifdef CO_SHDR_DEBUG_PRINT
		Ddim_Print(( "Im_SHDR_Int_Handler begin callback\n" ));
#endif
		S_G_IM_SHDR_CALLBACK_FUNC( S_G_IM_SHDR_AXI_ERR );

#ifdef CO_SHDR_DEBUG_PRINT
		Ddim_Print(( "Im_SHDR_Int_Handler end callback\n" ));
#endif
	}
}

/**
SHDR line interupt handler.<br>
@retval			None.
*/
VOID Im_SHDR_Line_Int_Handler( VOID )
{
	// User callback function.
	if ( S_G_IM_SHDR_LINEINT_CALLBACK_FUNC != NULL ) {
#ifdef CO_SHDR_DEBUG_PRINT
		Ddim_Print(( "Im_SHDR_Line_Int_Handler begin callback\n" ));
#endif
		S_G_IM_SHDR_LINEINT_CALLBACK_FUNC( 0 );

#ifdef CO_SHDR_DEBUG_PRINT
		Ddim_Print(( "Im_SHDR_Line_Int_Handler end callback\n" ));
#endif
	}
}

ImShdr2 *im_shdr2_get(void)
{
	if(!isImShdr2){
		isImShdr2 =1;
		ImShdr2* self = &imShdr2;
		self->gImShdrOutCtrl = D_IM_SHDR_OUTCTRL_YCC;
	}

	return &imShdr2;
}


