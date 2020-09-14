/*
 * imdisp2.c
 *
 *  Created on: 2020年8月8日
 *      Author: sns
 */
#include "imdisp.h"
#include "imdisp2.h"
#include "jdsdisp3a.h"

#include "dd_arm.h"
#include "ddim_user_custom.h"
#include <stddef.h>
#include <string.h>

K_TYPE_DEFINE_WITH_PRIVATE(ImDisp2, im_disp2)
#define IM_DISP2_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), ImDisp2Private,IM_TYPE_DISP2))


struct _ImDisp2Private
{
	int a;
};

static void im_disp2_constructor(ImDisp2 *self)
{
//	ImDisp2Private *priv = IM_DISP2_GET_PRIVATE(self);
}

static void im_disp2_destructor(ImDisp2 *self)
{
//	ImDisp2Private *priv = IM_DISP2_GET_PRIVATE(self);
}

/* Set Gamma table (Main data input block).
*/
INT32 im_disp2_ctrl_main_tbl(ImDisp2 * self, ImDispEImDispSel block, T_IM_DISP_CTRL_MAIN_TBL const *const ctrl_tbl)
{
	INT32 ret = D_DDIM_OK;
	ULONG rpgen;

#ifdef CO_PARAM_CHECK
	if (ctrl_tbl == NULL) {
		Ddim_Print(("E:im_disp2_ctrl_main_tbl: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((ctrl_tbl->anti_a.r_anti == NULL) ||
		(ctrl_tbl->anti_a.g_anti == NULL) ||
		(ctrl_tbl->anti_a.b_anti == NULL) ||
		(ctrl_tbl->anti_b.r_anti == NULL) ||
		(ctrl_tbl->anti_b.g_anti == NULL) ||
		(ctrl_tbl->anti_b.b_anti == NULL) ||
		(ctrl_tbl->gamma_a.r_data == NULL) ||
		(ctrl_tbl->gamma_a.g_data == NULL) ||
		(ctrl_tbl->gamma_a.b_data == NULL) ||
		(ctrl_tbl->gamma_b.r_data == NULL) ||
		(ctrl_tbl->gamma_b.g_data == NULL) ||
		(ctrl_tbl->gamma_b.b_data == NULL)) {
		Ddim_Print(("E:im_disp2_ctrl_main_tbl: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Set RPGEN off
	rpgen = IO_DISP.MAIN[block].DCORE.RPGEN.word;
	IO_DISP.MAIN[block].DCORE.RPGEN.word = D_IM_DISP_ENABLE_OFF;
	Im_DISP_Dsb();

	// Anti gamma table.
	if ((IO_DISP.MAIN[block].LCH.LTBLASET.bit.igtaen == ImDisp_E_IM_DISP_TABLE_ACCESS_ENABLE) &&
		((IO_DISP.MAIN[block].LCH.LTRG.bit.TRG == ImDisp_E_IM_DISP_TRG_READ_NO_ACT) ||
		 (IO_DISP.MAIN[block].LCH.LTBLASET.bit.igtsl == D_IM_DISP_TABLE_SURFACE_B))) {
		// Table access enable, and main data input block is stopped or Anti gamma table is using surface B.

		DDIM_User_AhbReg_SpinLock();
		im_disp_hclk_on(im_disp_new());
		// Set Anti gamma table (surface A)
		im_disp_access_gamma_table(im_disp_new(), (BYTE*)(&(ctrl_tbl->anti_a)), (BYTE*)(&(IO_DISP_TBL.MAIN[block].LCH.IGTBLA)),
									ImDisp_E_IM_DISP_CORRECT_SELECT_ANTI_GAMMA, ImDisp_E_IM_DISP_ACCESS_GAMMA_SET);
		im_disp_hclk_off(im_disp_new());
		DDIM_User_AhbReg_SpinUnLock();
	}
	if ((IO_DISP.MAIN[block].LCH.LTBLASET.bit.igtaen == ImDisp_E_IM_DISP_TABLE_ACCESS_ENABLE) &&
		((IO_DISP.MAIN[block].LCH.LTRG.bit.TRG == ImDisp_E_IM_DISP_TRG_READ_NO_ACT) ||
		 (IO_DISP.MAIN[block].LCH.LTBLASET.bit.igtsl == D_IM_DISP_TABLE_SURFACE_A))) {
		// Table access enable, and main data input block is stopped or Anti gamma table is using surface A.

		DDIM_User_AhbReg_SpinLock();
		im_disp_hclk_on(im_disp_new());
		// Set Anti gamma table (surface B)
		im_disp_access_gamma_table(im_disp_new(),(BYTE*)(&(ctrl_tbl->anti_b)), (BYTE*)(&(IO_DISP_TBL.MAIN[block].LCH.IGTBLB)),
									ImDisp_E_IM_DISP_CORRECT_SELECT_ANTI_GAMMA, ImDisp_E_IM_DISP_ACCESS_GAMMA_SET);
		im_disp_hclk_off(im_disp_new());
		DDIM_User_AhbReg_SpinUnLock();
	}

	// Gamma table is enable.
	if ((IO_DISP.MAIN[block].LCH.LTBLASET.bit.gtaen == ImDisp_E_IM_DISP_TABLE_ACCESS_ENABLE) &&
		((IO_DISP.MAIN[block].LCH.LTRG.bit.TRG == ImDisp_E_IM_DISP_TRG_READ_NO_ACT) ||
		 (IO_DISP.MAIN[block].LCH.LTBLASET.bit.gmtsl == D_IM_DISP_TABLE_SURFACE_B))) {
		// Table access enable, and main data input block is stopped or Gamma table is using surface B.

		DDIM_User_AhbReg_SpinLock();
		im_disp_hclk_on(im_disp_new());
		// Set Gamma table (surface A)
		im_disp_access_gamma_table(im_disp_new(),(BYTE*)(&(ctrl_tbl->gamma_a)), (BYTE*)(&(IO_DISP_TBL.MAIN[block].LCH.GTBLA)),
									ImDisp_E_IM_DISP_CORRECT_SELECT_GAMMA_IN, ImDisp_E_IM_DISP_ACCESS_GAMMA_SET);
		im_disp_hclk_off(im_disp_new());
		DDIM_User_AhbReg_SpinUnLock();
	}
	if ((IO_DISP.MAIN[block].LCH.LTBLASET.bit.gtaen == ImDisp_E_IM_DISP_TABLE_ACCESS_ENABLE) &&
		((IO_DISP.MAIN[block].LCH.LTRG.bit.TRG == ImDisp_E_IM_DISP_TRG_READ_NO_ACT) ||
		 (IO_DISP.MAIN[block].LCH.LTBLASET.bit.gmtsl == D_IM_DISP_TABLE_SURFACE_A))) {
		// Table access enable, and main data input block is stopped or Gamma table is using surface A.

		DDIM_User_AhbReg_SpinLock();
		im_disp_hclk_on(im_disp_new());
		// Set Gamma table (surface B)
		im_disp_access_gamma_table(im_disp_new(),(BYTE*)(&(ctrl_tbl->gamma_b)), (BYTE*)(&(IO_DISP_TBL.MAIN[block].LCH.GTBLB)),
									ImDisp_E_IM_DISP_CORRECT_SELECT_GAMMA_IN, ImDisp_E_IM_DISP_ACCESS_GAMMA_SET);
		im_disp_hclk_off(im_disp_new());
		DDIM_User_AhbReg_SpinUnLock();
	}

	// Recover RPGEN
	IO_DISP.MAIN[block].DCORE.RPGEN.word = rpgen;
	im_disp_pclk_off(im_disp_new());
	Im_DISP_Dsb();

	return  ret;
}

/* Get Gamma table (Main data input block).
*/
INT32 im_disp2_get_ctrl_main_tbl(ImDisp2 * self, ImDispEImDispSel block, T_IM_DISP_CTRL_MAIN_TBL *const ctrl_tbl)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (ctrl_tbl == NULL) {
		Ddim_Print(("E:im_disp2_get_ctrl_main_tbl: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((ctrl_tbl->anti_a.r_anti == NULL) ||
		(ctrl_tbl->anti_a.g_anti == NULL) ||
		(ctrl_tbl->anti_a.b_anti == NULL) ||
		(ctrl_tbl->anti_b.r_anti == NULL) ||
		(ctrl_tbl->anti_b.g_anti == NULL) ||
		(ctrl_tbl->anti_b.b_anti == NULL) ||
		(ctrl_tbl->gamma_a.r_data == NULL) ||
		(ctrl_tbl->gamma_a.g_data == NULL) ||
		(ctrl_tbl->gamma_a.b_data == NULL) ||
		(ctrl_tbl->gamma_b.r_data == NULL) ||
		(ctrl_tbl->gamma_b.g_data == NULL) ||
		(ctrl_tbl->gamma_b.b_data == NULL)) {
		Ddim_Print(("E:im_disp2_get_ctrl_main_tbl: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());

	// Anti gamma table.
	if ((IO_DISP.MAIN[block].LCH.LTBLASET.bit.igtaen == ImDisp_E_IM_DISP_TABLE_ACCESS_ENABLE) &&
		((IO_DISP.MAIN[block].LCH.LTRG.bit.TRG == ImDisp_E_IM_DISP_TRG_READ_NO_ACT) ||
		 (IO_DISP.MAIN[block].LCH.LTBLASET.bit.igtsl == D_IM_DISP_TABLE_SURFACE_B))) {
		// Table access enable, and main data input block is stopped or Anti gamma table is using surface B.

		DDIM_User_AhbReg_SpinLock();
		im_disp_hclk_on(im_disp_new());
		// Get Anti gamma table (surface A)
		im_disp_access_gamma_table(im_disp_new(),(BYTE*)(&(ctrl_tbl->anti_a)), (BYTE*)(&(IO_DISP_TBL.MAIN[block].LCH.IGTBLA)),
									ImDisp_E_IM_DISP_CORRECT_SELECT_ANTI_GAMMA, ImDisp_E_IM_DISP_ACCESS_GAMMA_GET);
		im_disp_hclk_off(im_disp_new());
		DDIM_User_AhbReg_SpinUnLock();
	}
	if ((IO_DISP.MAIN[block].LCH.LTBLASET.bit.igtaen == ImDisp_E_IM_DISP_TABLE_ACCESS_ENABLE) &&
		((IO_DISP.MAIN[block].LCH.LTRG.bit.TRG == ImDisp_E_IM_DISP_TRG_READ_NO_ACT) ||
		 (IO_DISP.MAIN[block].LCH.LTBLASET.bit.igtsl == D_IM_DISP_TABLE_SURFACE_A))) {
		// Table access enable, and main data input block is stopped or Anti gamma table is using surface A.

		DDIM_User_AhbReg_SpinLock();
		im_disp_hclk_on(im_disp_new());
		// Get Anti gamma table (surface B)
		im_disp_access_gamma_table(im_disp_new(),(BYTE*)(&(ctrl_tbl->anti_b)), (BYTE*)(&(IO_DISP_TBL.MAIN[block].LCH.IGTBLB)),
									ImDisp_E_IM_DISP_CORRECT_SELECT_ANTI_GAMMA, ImDisp_E_IM_DISP_ACCESS_GAMMA_GET);
		im_disp_hclk_off(im_disp_new());
		DDIM_User_AhbReg_SpinUnLock();
	}

	// Gamma table.
	if ((IO_DISP.MAIN[block].LCH.LTBLASET.bit.gtaen == ImDisp_E_IM_DISP_TABLE_ACCESS_ENABLE) &&
		((IO_DISP.MAIN[block].LCH.LTRG.bit.TRG == ImDisp_E_IM_DISP_TRG_READ_NO_ACT) ||
		 (IO_DISP.MAIN[block].LCH.LTBLASET.bit.gmtsl == D_IM_DISP_TABLE_SURFACE_B))) {
		// Table access enable, and main data input block is stopped or Gamma table is using surface B.

		DDIM_User_AhbReg_SpinLock();
		im_disp_hclk_on(im_disp_new());
		// Get Gamma table (surface A)
		im_disp_access_gamma_table(im_disp_new(),(BYTE*)(&(ctrl_tbl->gamma_a)), (BYTE*)(&(IO_DISP_TBL.MAIN[block].LCH.GTBLA)),
									ImDisp_E_IM_DISP_CORRECT_SELECT_GAMMA_IN, ImDisp_E_IM_DISP_ACCESS_GAMMA_GET);
		im_disp_hclk_off(im_disp_new());
		DDIM_User_AhbReg_SpinUnLock();
	}
	if ((IO_DISP.MAIN[block].LCH.LTBLASET.bit.gtaen == ImDisp_E_IM_DISP_TABLE_ACCESS_ENABLE) &&
		((IO_DISP.MAIN[block].LCH.LTRG.bit.TRG == ImDisp_E_IM_DISP_TRG_READ_NO_ACT) ||
		 (IO_DISP.MAIN[block].LCH.LTBLASET.bit.gmtsl == D_IM_DISP_TABLE_SURFACE_A))) {
		// Table access enable, and main data input block is stopped or Gamma table is using surface A.

		DDIM_User_AhbReg_SpinLock();
		im_disp_hclk_on(im_disp_new());
		// Get Gamma table (surface B)
		im_disp_access_gamma_table(im_disp_new(),(BYTE*)(&(ctrl_tbl->gamma_b)), (BYTE*)(&(IO_DISP_TBL.MAIN[block].LCH.GTBLB)),
									ImDisp_E_IM_DISP_CORRECT_SELECT_GAMMA_IN, ImDisp_E_IM_DISP_ACCESS_GAMMA_GET);
		im_disp_hclk_off(im_disp_new());
		DDIM_User_AhbReg_SpinUnLock();
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set Gamma table (Data output block).
*/
INT32 im_disp2_ctrl_output_tbl(ImDisp2 * self, ImDispEImDispSel block, T_IM_DISP_CTRL_OUTPUT_TBL const *const ctrl_tbl)
{
	INT32 ret = D_DDIM_OK;
	ULONG rpgen;

#ifdef CO_PARAM_CHECK
	if (ctrl_tbl == NULL) {
		Ddim_Print(("E:im_disp2_ctrl_output_tbl: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((ctrl_tbl->gamma_a.r_data == NULL) ||
		(ctrl_tbl->gamma_a.g_data == NULL) ||
		(ctrl_tbl->gamma_a.b_data == NULL) ||
		(ctrl_tbl->gamma_b.r_data == NULL) ||
		(ctrl_tbl->gamma_b.g_data == NULL) ||
		(ctrl_tbl->gamma_b.b_data == NULL) ||
		(ctrl_tbl->luminance_a == NULL) ||
		(ctrl_tbl->chroma_a == NULL) ||
		(ctrl_tbl->luminance_b == NULL) ||
		(ctrl_tbl->chroma_b == NULL)) {
		Ddim_Print(("E:im_disp2_ctrl_output_tbl: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Set RPGEN off
	rpgen = IO_DISP.MAIN[block].DCORE.RPGEN.word;
	IO_DISP.MAIN[block].DCORE.RPGEN.word = D_IM_DISP_ENABLE_OFF;
	Im_DISP_Dsb();

	// Gamma table.
	if ((IO_DISP.MAIN[block].DCORE.TBLASET.bit.GMTAEN == ImDisp_E_IM_DISP_TABLE_ACCESS_ENABLE) &&
		((IO_DISP.MAIN[block].DCORE.TRG.bit.TRG == ImDisp_E_IM_DISP_TRG_READ_NO_ACT) ||
		 (IO_DISP.MAIN[block].DCORE.TBLASET.bit.gmtsl == D_IM_DISP_TABLE_SURFACE_B))) {
		// Table access enable, and data output block is stopped or Gamma table is using surface B.

		DDIM_User_AhbReg_SpinLock();
		im_disp_hclk_on(im_disp_new());
		// Set Gamma table (surface A)
		im_disp_access_gamma_table(im_disp_new(),(BYTE*)(&(ctrl_tbl->gamma_a)), (BYTE*)(&(IO_DISP_TBL.MAIN[block].DCORE.GTBLA)),
									ImDisp_E_IM_DISP_CORRECT_SELECT_GAMMA_OUT, ImDisp_E_IM_DISP_ACCESS_GAMMA_SET);
		im_disp_hclk_off(im_disp_new());
		DDIM_User_AhbReg_SpinUnLock();
	}
	if ((IO_DISP.MAIN[block].DCORE.TBLASET.bit.GMTAEN == ImDisp_E_IM_DISP_TABLE_ACCESS_ENABLE) &&
		((IO_DISP.MAIN[block].DCORE.TRG.bit.TRG == ImDisp_E_IM_DISP_TRG_READ_NO_ACT) ||
		 (IO_DISP.MAIN[block].DCORE.TBLASET.bit.gmtsl == D_IM_DISP_TABLE_SURFACE_A))) {
		// Table access enable, and data output block is stopped or Gamma table is using surface A.

		DDIM_User_AhbReg_SpinLock();
		im_disp_hclk_on(im_disp_new());
		// Set Gamma table (surface B)
		im_disp_access_gamma_table(im_disp_new(),(BYTE*)(&(ctrl_tbl->gamma_b)), (BYTE*)(&(IO_DISP_TBL.MAIN[block].DCORE.GTBLB)),
									ImDisp_E_IM_DISP_CORRECT_SELECT_GAMMA_OUT, ImDisp_E_IM_DISP_ACCESS_GAMMA_SET);
		im_disp_hclk_off(im_disp_new());
		DDIM_User_AhbReg_SpinUnLock();
	}

	// Luminance and Chroma table.
	if ((IO_DISP.MAIN[block].DCORE.TBLASET.bit.YSATTA == ImDisp_E_IM_DISP_TABLE_ACCESS_ENABLE) &&
		((IO_DISP.MAIN[block].DCORE.TRG.bit.TRG == ImDisp_E_IM_DISP_TRG_READ_NO_ACT) ||
		 (IO_DISP.MAIN[block].DCORE.TBLASET.bit.YSATSL == D_IM_DISP_TABLE_SURFACE_B))) {
		// Table access enable, and data output block is stopped or Luminance and Chroma table is using surface B.

		DDIM_User_AhbReg_SpinLock();
		im_disp_hclk_on(im_disp_new());
		// Set Luminance table (surface A)
		im_disp_access_gamma_table(im_disp_new(),(BYTE*)(&(ctrl_tbl->luminance_a)), (BYTE*)(&(IO_DISP_TBL.MAIN[block].DCORE.YSTBLAYT)),
									ImDisp_E_IM_DISP_CORRECT_SELECT_LUMINANCE, ImDisp_E_IM_DISP_ACCESS_GAMMA_SET);
		// Set Chroma table (surface A)
		im_disp_access_gamma_table(im_disp_new(),(BYTE*)(&(ctrl_tbl->chroma_a)), (BYTE*)(&(IO_DISP_TBL.MAIN[block].DCORE.YSTBLACG)),
									ImDisp_E_IM_DISP_CORRECT_SELECT_CHROMA, ImDisp_E_IM_DISP_ACCESS_GAMMA_SET);
		im_disp_hclk_off(im_disp_new());
		DDIM_User_AhbReg_SpinUnLock();
	}
	if ((IO_DISP.MAIN[block].DCORE.TBLASET.bit.YSATTA == ImDisp_E_IM_DISP_TABLE_ACCESS_ENABLE) &&
		((IO_DISP.MAIN[block].DCORE.TRG.bit.TRG == ImDisp_E_IM_DISP_TRG_READ_NO_ACT) ||
		 (IO_DISP.MAIN[block].DCORE.TBLASET.bit.YSATSL == D_IM_DISP_TABLE_SURFACE_A))) {
		// Table access enable, and data output block is stopped or Luminance and Chroma table is using surface A.

		DDIM_User_AhbReg_SpinLock();
		im_disp_hclk_on(im_disp_new());
		// Set Luminance table (surface B)
		im_disp_access_gamma_table(im_disp_new(),(BYTE*)(&(ctrl_tbl->luminance_b)), (BYTE*)(&(IO_DISP_TBL.MAIN[block].DCORE.YSTBLBYT)),
									ImDisp_E_IM_DISP_CORRECT_SELECT_LUMINANCE, ImDisp_E_IM_DISP_ACCESS_GAMMA_SET);
		// Set Chroma table (surface B)
		im_disp_access_gamma_table(im_disp_new(),(BYTE*)(&(ctrl_tbl->chroma_b)), (BYTE*)(&(IO_DISP_TBL.MAIN[block].DCORE.YSTBLBCG)),
									ImDisp_E_IM_DISP_CORRECT_SELECT_CHROMA, ImDisp_E_IM_DISP_ACCESS_GAMMA_SET);
		im_disp_hclk_off(im_disp_new());
		DDIM_User_AhbReg_SpinUnLock();
	}

	// Recover RPGEN
	IO_DISP.MAIN[block].DCORE.RPGEN.word = rpgen;
	im_disp_pclk_off(im_disp_new());
	Im_DISP_Dsb();

	return  ret;
}

/* Get Gamma table (Data output block).
*/
INT32 im_disp2_get_ctrl_output_tbl(ImDisp2 * self, ImDispEImDispSel block, T_IM_DISP_CTRL_OUTPUT_TBL *const ctrl_tbl)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (ctrl_tbl == NULL) {
		Ddim_Print(("E:im_disp2_get_ctrl_output_tbl: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((ctrl_tbl->gamma_a.r_data == NULL) ||
		(ctrl_tbl->gamma_a.g_data == NULL) ||
		(ctrl_tbl->gamma_a.b_data == NULL) ||
		(ctrl_tbl->gamma_b.r_data == NULL) ||
		(ctrl_tbl->gamma_b.g_data == NULL) ||
		(ctrl_tbl->gamma_b.b_data == NULL) ||
		(ctrl_tbl->luminance_a == NULL) ||
		(ctrl_tbl->chroma_a == NULL) ||
		(ctrl_tbl->luminance_b == NULL) ||
		(ctrl_tbl->chroma_b == NULL)) {
		Ddim_Print(("E:im_disp2_get_ctrl_output_tbl: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());

	// Gamma table.
	if ((IO_DISP.MAIN[block].DCORE.TBLASET.bit.GMTAEN == ImDisp_E_IM_DISP_TABLE_ACCESS_ENABLE) &&
		((IO_DISP.MAIN[block].DCORE.TRG.bit.TRG == ImDisp_E_IM_DISP_TRG_READ_NO_ACT) ||
		 (IO_DISP.MAIN[block].DCORE.TBLASET.bit.gmtsl == D_IM_DISP_TABLE_SURFACE_B))) {
		// Table access enable, and data output block is stopped or Gamma table is using surface B.

		DDIM_User_AhbReg_SpinLock();
		im_disp_hclk_on(im_disp_new());
		// Get Gamma table (surface A)
		im_disp_access_gamma_table(im_disp_new(),(BYTE*)(&(ctrl_tbl->gamma_a)), (BYTE*)(&(IO_DISP_TBL.MAIN[block].DCORE.GTBLA)),
									ImDisp_E_IM_DISP_CORRECT_SELECT_GAMMA_OUT, ImDisp_E_IM_DISP_ACCESS_GAMMA_GET);
		im_disp_hclk_off(im_disp_new());
		DDIM_User_AhbReg_SpinUnLock();
	}
	if ((IO_DISP.MAIN[block].DCORE.TBLASET.bit.GMTAEN == ImDisp_E_IM_DISP_TABLE_ACCESS_ENABLE) &&
		((IO_DISP.MAIN[block].DCORE.TRG.bit.TRG == ImDisp_E_IM_DISP_TRG_READ_NO_ACT) ||
		 (IO_DISP.MAIN[block].DCORE.TBLASET.bit.gmtsl == D_IM_DISP_TABLE_SURFACE_A))) {
		// Table access enable, and data output block is stopped or Gamma table is using surface A.

		DDIM_User_AhbReg_SpinLock();
		im_disp_hclk_on(im_disp_new());
		// Get Gamma table (surface B)
		im_disp_access_gamma_table(im_disp_new(),(BYTE*)(&(ctrl_tbl->gamma_b)), (BYTE*)(&(IO_DISP_TBL.MAIN[block].DCORE.GTBLB)),
									ImDisp_E_IM_DISP_CORRECT_SELECT_GAMMA_OUT, ImDisp_E_IM_DISP_ACCESS_GAMMA_GET);
		im_disp_hclk_off(im_disp_new());
		DDIM_User_AhbReg_SpinUnLock();
	}

	// Luminance and Chroma table.
	if ((IO_DISP.MAIN[block].DCORE.TBLASET.bit.YSATTA == ImDisp_E_IM_DISP_TABLE_ACCESS_ENABLE) &&
		((IO_DISP.MAIN[block].DCORE.TRG.bit.TRG == ImDisp_E_IM_DISP_TRG_READ_NO_ACT) ||
		 (IO_DISP.MAIN[block].DCORE.TBLASET.bit.YSATSL == D_IM_DISP_TABLE_SURFACE_B))) {
		// Table access enable, and data output block is stopped or Luminance and Chroma table is using surface B.

		DDIM_User_AhbReg_SpinLock();
		im_disp_hclk_on(im_disp_new());
		// Get Luminance table (surface A)
		im_disp_access_gamma_table(im_disp_new(),(BYTE*)(&(ctrl_tbl->luminance_a)), (BYTE*)(&(IO_DISP_TBL.MAIN[block].DCORE.YSTBLAYT)),
									ImDisp_E_IM_DISP_CORRECT_SELECT_LUMINANCE, ImDisp_E_IM_DISP_ACCESS_GAMMA_GET);
		// Get Chroma table (surface A)
		im_disp_access_gamma_table(im_disp_new(),(BYTE*)(&(ctrl_tbl->chroma_a)), (BYTE*)(&(IO_DISP_TBL.MAIN[block].DCORE.YSTBLACG)),
									ImDisp_E_IM_DISP_CORRECT_SELECT_CHROMA, ImDisp_E_IM_DISP_ACCESS_GAMMA_GET);
		im_disp_hclk_off(im_disp_new());
		DDIM_User_AhbReg_SpinUnLock();
	}
	if ((IO_DISP.MAIN[block].DCORE.TBLASET.bit.YSATTA == ImDisp_E_IM_DISP_TABLE_ACCESS_ENABLE) &&
		((IO_DISP.MAIN[block].DCORE.TRG.bit.TRG == ImDisp_E_IM_DISP_TRG_READ_NO_ACT) ||
		 (IO_DISP.MAIN[block].DCORE.TBLASET.bit.YSATSL == D_IM_DISP_TABLE_SURFACE_A))) {
		// Table access enable, and data output block is stopped or Luminance and Chroma table is using surface A.

		DDIM_User_AhbReg_SpinLock();
		im_disp_hclk_on(im_disp_new());
		// Get Luminance table (surface B)
		im_disp_access_gamma_table(im_disp_new(),(BYTE*)(&(ctrl_tbl->luminance_b)), (BYTE*)(&(IO_DISP_TBL.MAIN[block].DCORE.YSTBLBYT)),
									ImDisp_E_IM_DISP_CORRECT_SELECT_LUMINANCE, ImDisp_E_IM_DISP_ACCESS_GAMMA_GET);
		// Get Chroma table (surface B)
		im_disp_access_gamma_table(im_disp_new(),(BYTE*)(&(ctrl_tbl->chroma_b)), (BYTE*)(&(IO_DISP_TBL.MAIN[block].DCORE.YSTBLBCG)),
									ImDisp_E_IM_DISP_CORRECT_SELECT_CHROMA, ImDisp_E_IM_DISP_ACCESS_GAMMA_GET);
		im_disp_hclk_off(im_disp_new());
		DDIM_User_AhbReg_SpinUnLock();
	}

	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* The block is started.
*/
INT32 im_disp2_start(ImDisp2 * self, UINT32 hdmi_layer, UINT32 lcd_mipi_layer, BYTE write_channel)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (((hdmi_layer & E_IM_DISP_SEL_LAYER_ALL) == E_IM_DISP_SEL_LAYER_NONE) &&
		((lcd_mipi_layer & E_IM_DISP_SEL_LAYER_ALL) == E_IM_DISP_SEL_LAYER_NONE) &&
		(write_channel == 0 )){
		Ddim_Print(("E:im_disp2_start: layer parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());

	// HDMI(Common block 0)
	if((hdmi_layer & E_IM_DISP_SEL_LAYER_ALL) != E_IM_DISP_SEL_LAYER_NONE) {
		ret = im_disp_set_trg(im_disp_new(), ImDisp_E_IM_DISP_HDMI, hdmi_layer, write_channel, ImDisp_E_IM_DISP_TRG_WRITE_ACT);
	}

	// LCD or MIPI-DSI(Common block 1)
	if((lcd_mipi_layer & E_IM_DISP_SEL_LAYER_ALL) != E_IM_DISP_SEL_LAYER_NONE) {
		ret = im_disp_set_trg(im_disp_new(), ImDisp_E_IM_DISP_LCD_MIPI, lcd_mipi_layer, write_channel, ImDisp_E_IM_DISP_TRG_WRITE_ACT);
	}

	im_disp_pclk_off(im_disp_new());
	Im_DISP_Dsb();

	return ret;
}

/* The block is stopped.
*/
INT32 im_disp2_stop(ImDisp2 * self, UINT32 hdmi_layer, UINT32 lcd_mipi_layer, BYTE write_channel, E_IM_DISP_STOP_TYPE stop_type)
{
	ImDispEImDispTrg set_type;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (((hdmi_layer & E_IM_DISP_SEL_LAYER_ALL) == E_IM_DISP_SEL_LAYER_NONE) &&
		((lcd_mipi_layer & E_IM_DISP_SEL_LAYER_ALL) == E_IM_DISP_SEL_LAYER_NONE) &&
		(write_channel == 0)){
		Ddim_Print(("E:im_disp2_stop: layer parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// HDMI(Common block 0)
	if( hdmi_layer & (~E_IM_DISP_SEL_LAYER_NONE)) {
		if ((stop_type == E_IM_DISP_STOP_TYPE_WITHOUT_WAIT) ||
			(IO_DISP.MAIN[ImDisp_E_IM_DISP_HDMI].DCORE.TRG.bit.TRG == ImDisp_E_IM_DISP_TRG_READ_NO_ACT)) {
			//force stop
			set_type = ImDisp_E_IM_DISP_TRG_WRITE_NO_ACT;
		}
		else {
			//frame stop
			set_type = ImDisp_E_IM_DISP_TRG_READ_NO_ACT;
		}
		ret = im_disp_set_trg(im_disp_new(), ImDisp_E_IM_DISP_HDMI, hdmi_layer, write_channel, set_type);
	}
	else if ((lcd_mipi_layer == E_IM_DISP_SEL_LAYER_NONE) && (write_channel != 0)) {
		if (IO_DISP.MAIN[ImDisp_E_IM_DISP_HDMI].DCORE.TRG.bit.TRG == ImDisp_E_IM_DISP_TRG_READ_NO_ACT) {
			//force stop
			set_type = ImDisp_E_IM_DISP_TRG_WRITE_NO_ACT;
		}
		else {
			//frame stop
			set_type = ImDisp_E_IM_DISP_TRG_READ_NO_ACT;
		}
		ret = im_disp_set_trg(im_disp_new(), ImDisp_E_IM_DISP_HDMI, hdmi_layer, write_channel, set_type);
	}

	// LCD or MIPI-DSI(Common block 1)
	if( lcd_mipi_layer & (~E_IM_DISP_SEL_LAYER_NONE)) {
		if ((stop_type == E_IM_DISP_STOP_TYPE_WITHOUT_WAIT) ||
			(IO_DISP.MAIN[ImDisp_E_IM_DISP_LCD_MIPI].DCORE.TRG.bit.TRG == ImDisp_E_IM_DISP_TRG_READ_NO_ACT)) {
			//force stop
			set_type = ImDisp_E_IM_DISP_TRG_WRITE_NO_ACT;
		}
		else {
			//frame stop
			set_type = ImDisp_E_IM_DISP_TRG_READ_NO_ACT;
		}
		ret = im_disp_set_trg(im_disp_new(), ImDisp_E_IM_DISP_LCD_MIPI, lcd_mipi_layer, write_channel, set_type);
	}

	im_disp_pclk_off(im_disp_new());
	Im_DISP_Dsb();

	return ret;
}

/* Get startup status of all blocks.
*/
INT32 im_disp2_get_status(ImDisp2 * self, UINT32* hdmi_layer, UINT32* lcd_mipi_layer)
{
	UINT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ((hdmi_layer == NULL) && (lcd_mipi_layer == NULL)){
		Ddim_Print(("E:im_disp2_get_status: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	if (hdmi_layer != NULL){
		*hdmi_layer = E_IM_DISP_SEL_LAYER_NONE;

		//Check common block 0
		if(IO_DISP.MAIN[ImDisp_E_IM_DISP_HDMI].LCH.LTRG.word == ImDisp_E_IM_DISP_TRG_READ_ACT) {
			*hdmi_layer |= E_IM_DISP_SEL_LAYER_MAIN;
		}
		if(IO_DISP.MAIN[ImDisp_E_IM_DISP_HDMI].DCORE.TRG.bit.TRG == ImDisp_E_IM_DISP_TRG_READ_ACT) {
			*hdmi_layer |= E_IM_DISP_SEL_LAYER_DCORE;
		}
		if(IO_DISP.MAIN[ImDisp_E_IM_DISP_HDMI].GRCH[0].GRTRG.word == ImDisp_E_IM_DISP_TRG_READ_ACT) {
			*hdmi_layer |= E_IM_DISP_SEL_LAYER_OSD_0;
		}
		if(IO_DISP.MAIN[ImDisp_E_IM_DISP_HDMI].GRCH[1].GRTRG.word == ImDisp_E_IM_DISP_TRG_READ_ACT) {
			*hdmi_layer |= E_IM_DISP_SEL_LAYER_OSD_1;
		}
	}

	if (lcd_mipi_layer != NULL){
		*lcd_mipi_layer = E_IM_DISP_SEL_LAYER_NONE;

		//Check common block 0
		if(IO_DISP.MAIN[ImDisp_E_IM_DISP_LCD_MIPI].LCH.LTRG.word == ImDisp_E_IM_DISP_TRG_READ_ACT) {
			*lcd_mipi_layer |= E_IM_DISP_SEL_LAYER_MAIN;
		}
		if(IO_DISP.MAIN[ImDisp_E_IM_DISP_LCD_MIPI].DCORE.TRG.bit.TRG == ImDisp_E_IM_DISP_TRG_READ_ACT) {
			*lcd_mipi_layer |= E_IM_DISP_SEL_LAYER_DCORE;
		}
		if(IO_DISP.MAIN[ImDisp_E_IM_DISP_LCD_MIPI].GRCH[0].GRTRG.word == ImDisp_E_IM_DISP_TRG_READ_ACT) {
			*lcd_mipi_layer |= E_IM_DISP_SEL_LAYER_OSD_0;
		}
		if(IO_DISP.MAIN[ImDisp_E_IM_DISP_LCD_MIPI].GRCH[1].GRTRG.word == ImDisp_E_IM_DISP_TRG_READ_ACT) {
			*lcd_mipi_layer |= E_IM_DISP_SEL_LAYER_OSD_1;
		}
	}

	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Wait VSYNC interruption.
*/
INT32 im_disp2_wait_vsync(ImDisp2 * self, ImDispEImDispSel block, ImDispEImDispInterruptionSelect interruption_select, E_IM_DISP_WAIT wait_time)
{
	DDIM_USER_ER ercd;
	INT32 loop;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ((interruption_select != ImDisp_E_IM_DISP_INTERRUPTION_SELECT_VE2) &&
		(interruption_select != ImDisp_E_IM_DISP_INTERRUPTION_SELECT_VE) &&
		(interruption_select != ImDisp_E_IM_DISP_CORRECT_SELECT_ALL_VE)) {
		Ddim_Print(("E:im_disp2_wait_vsync: interruption_select parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	if(IO_DISP.MAIN[block].DCORE.TRG.bit.TRG == ImDisp_E_IM_DISP_TRG_READ_ACT) {
		//Channel's triger On
		if(IO_DISP.MAIN[block].DCORE.INTC.word != E_IM_DISP_VFTMG_NONE_FLAG) {
			// Because it is a setting that generate the flag.
			if((IO_DISP.MAIN[block].DCORE.INTE.word & interruption_select) != 0) {
				// Because it is a setting that generate the interrupt.
				DDIM_USER_FLGPTN flg_ptn;
				UINT32 disp_flg = im_disp_get_event_flag(im_disp_new(), interruption_select);
				for (loop = wait_time; loop > 0; loop--) {
					ercd = DDIM_User_Clr_Flg(FID_IM_DISP, ~disp_flg);
					if (ercd != D_DDIM_USER_E_OK) {
						// DDIM_User_Twai_Flg error
						Ddim_Print(("E:im_disp2_wait_vsync: DDIM_User_Clr_Flg error. ercd = %d\n", ercd));
						ret = D_IM_DISP_STATUS_ABNORMAL;
					}
#ifdef CO_DEBUG_ON_PC
					IO_DISP.MAIN[block].DCORE.INTF.word = interruption_select;
					im_disp2_int_handler();
#endif // CO_DEBUG_ON_PC
#ifdef CO_DEBUG_DISP
					Ddim_Print(("I:im_disp2_wait_vsync: DDIM_User_Twai_Flg(%08X)\n", disp_flg));
#endif // CO_DEBUG_DISP
					ercd = DDIM_User_Twai_Flg(FID_IM_DISP, disp_flg, D_DDIM_USER_TWF_ORW, &flg_ptn, D_IM_DISP_VSYNC_TIME * 2);
					if (ercd != D_DDIM_USER_E_OK) {
						// DDIM_User_Twai_Flg error
						Ddim_Print(("E:im_disp2_wait_vsync: DDIM_User_Twai_Flg error. ercd = %d\n", ercd));
						ret = D_IM_DISP_STATUS_ABNORMAL;
					}
				}
			}
			else{
				Ddim_Print(("E:im_disp2_wait_vsync: INTE was not set to 1\n"));
				ret = D_IM_DISP_STATUS_ABNORMAL;
			}
		}
		else{
			Ddim_Print(("E:im_disp2_wait_vsync: INTC was 0\n"));
			ret = D_IM_DISP_STATUS_ABNORMAL;
		}
	}
	else{
		Ddim_Print(("E:im_disp2_wait_vsync: Output layer free\n"));
		ret = D_IM_DISP_STATUS_ABNORMAL;
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Wait the block stopping after the @ref im_disp2_stop was called if it was necessary.
*/
INT32 im_disp2_wait_stop(ImDisp2 * self, UINT32 hdmi_layer, UINT32 lcd_mipi_layer)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (((hdmi_layer & E_IM_DISP_SEL_LAYER_ALL) == E_IM_DISP_SEL_LAYER_NONE) &&
		((lcd_mipi_layer & E_IM_DISP_SEL_LAYER_ALL) == E_IM_DISP_SEL_LAYER_NONE)){
		Ddim_Print(("E:im_disp2_wait_stop: layer parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	// Wait stop
	// common block 0
	if ((hdmi_layer & E_IM_DISP_SEL_LAYER_ALL) != E_IM_DISP_SEL_LAYER_NONE) {
		ret = im_disp_wait_trg_stop_start(im_disp_new(), ImDisp_E_IM_DISP_HDMI, hdmi_layer, ImDisp_E_IM_DISP_TRG_READ_NO_ACT);
		if (ret != D_DDIM_OK){
			Ddim_Print(("E:im_disp2_wait_stop: Time-out occur when waiting the block stop\n"));
		}
	}

	// common block 1
	if ((lcd_mipi_layer & E_IM_DISP_SEL_LAYER_ALL) != E_IM_DISP_SEL_LAYER_NONE) {
		ret = im_disp_wait_trg_stop_start(im_disp_new(), ImDisp_E_IM_DISP_LCD_MIPI, lcd_mipi_layer, ImDisp_E_IM_DISP_TRG_READ_NO_ACT);
		if (ret != D_DDIM_OK){
			Ddim_Print(("E:im_disp2_wait_stop: Time-out occur when waiting the block stop\n"));
		}
	}

	return ret;
}

/* DISP interrupt handler.
*/
VOID im_disp2_int_handler(void)
{


	ImDisp0 * imDisp0 = im_disp0_get();



				im_disp0_gim_Disp_Interrupt_Callback1(imDisp0); //此处原有函数改为调用的公有函数



#ifdef CO_DEBUG_DISP
	Ddim_Print(("I:im_disp2_int_handler: after IO_DISP.MAIN[0].DCORE.INTF = %08X\n", (UINT32)IO_DISP.MAIN[0].DCORE.INTF.word));
	Ddim_Print(("I:im_disp2_int_handler: after IO_DISP.MAIN[1].DCORE.INTF = %08X\n", (UINT32)IO_DISP.MAIN[1].DCORE.INTF.word));
#endif // CO_DEBUG_DISP
	im_disp_pclk_off(im_disp_new());
}

/* Set SR.
*/
INT32 im_disp2_set_sr(ImDisp2 * self, UINT32 hdmi_layer, UINT32 lcd_mipi_layer, BYTE sr)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (((hdmi_layer & E_IM_DISP_SEL_LAYER_ALL) == E_IM_DISP_SEL_LAYER_NONE) &&
		((lcd_mipi_layer & E_IM_DISP_SEL_LAYER_ALL) == E_IM_DISP_SEL_LAYER_NONE)){
		Ddim_Print(("E:im_disp2_set_sr: layer parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((sr != D_IM_DISP_SR_CANCEL) && (sr != D_IM_DISP_SR_RESET)) {
		Ddim_Print(("E:im_disp2_set_sr: sr parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());

	// common block 0 (HDMI)
	if (((hdmi_layer & E_IM_DISP_SEL_LAYER_MAIN) == E_IM_DISP_SEL_LAYER_MAIN) &&
		(IO_DISP.MAIN[ImDisp_E_IM_DISP_HDMI].LCH.LTRG.word == ImDisp_E_IM_DISP_TRG_READ_NO_ACT)) {
		IO_DISP.MAIN[ImDisp_E_IM_DISP_HDMI].LCH.LRST.bit.SR = sr;		// Main data input block
	}
	if (((hdmi_layer & E_IM_DISP_SEL_LAYER_DCORE) == E_IM_DISP_SEL_LAYER_DCORE) &&
		(IO_DISP.MAIN[ImDisp_E_IM_DISP_HDMI].DCORE.TRG.bit.TRG == ImDisp_E_IM_DISP_TRG_READ_NO_ACT)) {
		IO_DISP.MAIN[ImDisp_E_IM_DISP_HDMI].DCORE.RESET.bit.SR = sr;	// Output data block
	}
	if (((hdmi_layer & E_IM_DISP_SEL_LAYER_OSD_0) == E_IM_DISP_SEL_LAYER_OSD_0) &&
		(IO_DISP.MAIN[ImDisp_E_IM_DISP_HDMI].GRCH[0].GRTRG.word == ImDisp_E_IM_DISP_TRG_READ_NO_ACT)) {
		IO_DISP.MAIN[ImDisp_E_IM_DISP_HDMI].GRCH[0].GRRST.bit.SR = sr;	// OSD_0 data input block
	}
	if (((hdmi_layer & E_IM_DISP_SEL_LAYER_OSD_1) == E_IM_DISP_SEL_LAYER_OSD_1) &&
		(IO_DISP.MAIN[ImDisp_E_IM_DISP_HDMI].GRCH[1].GRTRG.word == ImDisp_E_IM_DISP_TRG_READ_NO_ACT)) {
		IO_DISP.MAIN[ImDisp_E_IM_DISP_HDMI].GRCH[1].GRRST.bit.SR = sr;	// OSD_1 data input block
	}

	// common block 1 (LCD or MIPI)
	if (((lcd_mipi_layer & E_IM_DISP_SEL_LAYER_MAIN) == E_IM_DISP_SEL_LAYER_MAIN) &&
		(IO_DISP.MAIN[ImDisp_E_IM_DISP_LCD_MIPI].LCH.LTRG.word == ImDisp_E_IM_DISP_TRG_READ_NO_ACT)) {
		IO_DISP.MAIN[ImDisp_E_IM_DISP_LCD_MIPI].LCH.LRST.bit.SR = sr;		// Main data input block
	}
	if (((lcd_mipi_layer & E_IM_DISP_SEL_LAYER_DCORE) == E_IM_DISP_SEL_LAYER_DCORE) &&
		(IO_DISP.MAIN[ImDisp_E_IM_DISP_LCD_MIPI].DCORE.TRG.bit.TRG == ImDisp_E_IM_DISP_TRG_READ_NO_ACT)) {
		IO_DISP.MAIN[ImDisp_E_IM_DISP_LCD_MIPI].DCORE.RESET.bit.SR = sr;	// Output data block
	}
	if (((lcd_mipi_layer & E_IM_DISP_SEL_LAYER_OSD_0) == E_IM_DISP_SEL_LAYER_OSD_0) &&
		(IO_DISP.MAIN[ImDisp_E_IM_DISP_LCD_MIPI].GRCH[0].GRTRG.word == ImDisp_E_IM_DISP_TRG_READ_NO_ACT)) {
		IO_DISP.MAIN[ImDisp_E_IM_DISP_LCD_MIPI].GRCH[0].GRRST.bit.SR = sr;	// OSD_0 data input block
	}
	if (((lcd_mipi_layer & E_IM_DISP_SEL_LAYER_OSD_1) == E_IM_DISP_SEL_LAYER_OSD_1) &&
		(IO_DISP.MAIN[ImDisp_E_IM_DISP_LCD_MIPI].GRCH[1].GRTRG.word == ImDisp_E_IM_DISP_TRG_READ_NO_ACT)) {
		IO_DISP.MAIN[ImDisp_E_IM_DISP_LCD_MIPI].GRCH[1].GRRST.bit.SR = sr;	// OSD_1 data input block
	}

	im_disp_pclk_off(im_disp_new());
	Im_DISP_Dsb();

	return ret;
}

/* Get SR.
*/
INT32 im_disp2_get_sr(ImDisp2 * self, UINT32* hdmi_layer, UINT32* lcd_mipi_layer)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ((hdmi_layer == NULL) || (lcd_mipi_layer == NULL)) {
		Ddim_Print(("E:im_disp2_get_sr: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	*hdmi_layer = E_IM_DISP_SEL_LAYER_NONE;
	*lcd_mipi_layer = E_IM_DISP_SEL_LAYER_NONE;

	// common block 0 (HDMI)
	if (IO_DISP.MAIN[ImDisp_E_IM_DISP_HDMI].LCH.LRST.bit.SR == D_IM_DISP_SR_RESET) {
		*hdmi_layer |= E_IM_DISP_SEL_LAYER_MAIN;
	}
	if (IO_DISP.MAIN[ImDisp_E_IM_DISP_HDMI].DCORE.RESET.bit.SR == D_IM_DISP_SR_RESET) {
		*hdmi_layer |= E_IM_DISP_SEL_LAYER_DCORE;
	}
	if (IO_DISP.MAIN[ImDisp_E_IM_DISP_HDMI].GRCH[0].GRRST.bit.SR == D_IM_DISP_SR_RESET) {
		*hdmi_layer |= E_IM_DISP_SEL_LAYER_OSD_0;
	}
	if (IO_DISP.MAIN[ImDisp_E_IM_DISP_HDMI].GRCH[1].GRRST.bit.SR == D_IM_DISP_SR_RESET) {
		*hdmi_layer |= E_IM_DISP_SEL_LAYER_OSD_1;
	}

	// common block 1 (LCD or MIPI)
	if (IO_DISP.MAIN[ImDisp_E_IM_DISP_LCD_MIPI].LCH.LRST.bit.SR == D_IM_DISP_SR_RESET) {
		*lcd_mipi_layer |= E_IM_DISP_SEL_LAYER_MAIN;
	}
	if (IO_DISP.MAIN[ImDisp_E_IM_DISP_LCD_MIPI].DCORE.RESET.bit.SR == D_IM_DISP_SR_RESET) {
		*lcd_mipi_layer |= E_IM_DISP_SEL_LAYER_DCORE;
	}
	if (IO_DISP.MAIN[ImDisp_E_IM_DISP_LCD_MIPI].GRCH[0].GRRST.bit.SR == D_IM_DISP_SR_RESET) {
		*lcd_mipi_layer |= E_IM_DISP_SEL_LAYER_OSD_0;
	}
	if (IO_DISP.MAIN[ImDisp_E_IM_DISP_LCD_MIPI].GRCH[1].GRRST.bit.SR == D_IM_DISP_SR_RESET) {
		*lcd_mipi_layer |= E_IM_DISP_SEL_LAYER_OSD_1;
	}

	im_disp_pclk_off(im_disp_new());

	return ret;
}


ImDisp2 *im_disp2_new(void)
{
	ImDisp2* self = k_object_new_with_private(IM_TYPE_DISP2,sizeof(ImDisp2Private));
	return self;
}
