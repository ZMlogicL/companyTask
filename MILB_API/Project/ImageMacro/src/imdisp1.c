/*
 * imdisp1.c
 *
 *  Created on: 2020年8月8日
 *      Author: sns
 */
#include "imdisp1.h"
#include "jdsdisp3a.h"

#include "dd_arm.h"
#include "ddim_user_custom.h"
#include <stddef.h>
#include <string.h>

K_TYPE_DEFINE_WITH_PRIVATE(ImDisp1, im_disp1)
#define IM_DISP1_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), ImDisp1Private,IM_TYPE_DISP1))


struct _ImDisp1Private
{
	int a;
};

static void im_disp1_constructor(ImDisp1 *self)
{
	//ImDisp1Private *priv = IM_DISP1_GET_PRIVATE(self);
}

static void im_disp1_destructor(ImDisp1 *self)
{
	//ImDisp1Private *priv = IM_DISP1_GET_PRIVATE(self);
}

/* DISP ICLK change to ON
*/
static VOID imDispIclkOn(VOID)
{
#ifdef CO_ACT_ICLOCK
	Dd_Top_Set_CLKSTOP3_DISPAX(2);	// DISP AXI clock on.
#endif	// CO_ACT_ICLOCK
}

/**
Check control OSD data input parameter.
@param[in]	ctrl			Setting of OSD data input block.<br>
							It is possible to rewrite it while OSD data input block is operating.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
static INT32 imDispParamCheckCtrlOsdLayer(T_IM_DISP_CTRL_OSD_LAYER const *const ctrl)
{
	INT32 loop;
	INT32 ret = D_DDIM_OK;

	if(ctrl != NULL){
		if (im_disp_param_check_gridt(ctrl->gridt) != D_DDIM_OK){
			Ddim_Print(("E:im_disp1_ctrl_osd_layer: GRIDT parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
		if (im_disp_param_check_grtisize(ctrl->grtisize) != D_DDIM_OK){
			Ddim_Print(("E:im_disp1_ctrl_osd_layer: GRTISIZE parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
		if (im_disp_param_check_grtdsta(ctrl->grtdsta) != D_DDIM_OK){
			Ddim_Print(("E:im_disp1_ctrl_osd_layer: GRTDSTA parameter error,DSH=%x,DSV=%x\n",ctrl->grtdsta.bit.DSH,ctrl->grtdsta.bit.DSV));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
		if (im_disp_param_check_gripo(ctrl->gripo) != D_DDIM_OK){
			Ddim_Print(("E:im_disp1_ctrl_osd_layer: GRIPO parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
		if (im_disp_param_check_grisize(ctrl->grisize, ImDisp_D_IM_DISP_OSD_DISPLAY_AREA_COUNT) != D_DDIM_OK) {
			Ddim_Print(("E:im_disp1_ctrl_osd_layer: GRISIZE parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
		for(loop = ImDisp_D_IM_DISP_OSD_DISPLAY_AREA_COUNT - 1; loop >= 0; loop--) {
			if (ctrl->grdsta[loop].bit.DSH + ctrl->grisize[loop].size.width > ctrl->grtisize.size.width) {
				Im_DISP_Check_Point(("CP:imDispParamCheckCtrlOsdLayer() 1\n"));
				Ddim_Print(("E:im_disp1_ctrl_osd_layer: GRISIZE parameter error\n"));
				return D_IM_DISP_INPUT_PARAM_ERROR;
			}
			if (ctrl->grdsta[loop].bit.DSV + ctrl->grisize[loop].size.lines > ctrl->grtisize.size.lines) {
				Im_DISP_Check_Point(("CP:imDispParamCheckCtrlOsdLayer() 2\n"));
				Ddim_Print(("E:im_disp1_ctrl_osd_layer: GRISIZE parameter error\n"));
				return D_IM_DISP_INPUT_PARAM_ERROR;
			}
			if (im_disp_param_check_grhga(ctrl->grhga[loop]) != D_DDIM_OK) {
				Ddim_Print(("E:im_disp1_ctrl_osd_layer: GRHGA parameter error\n"));
				return D_IM_DISP_INPUT_PARAM_ERROR;
			}
			if (im_disp_param_check_grdsta(ctrl->grdsta[loop]) != D_DDIM_OK) {
				Ddim_Print(("E:im_disp1_ctrl_osd_layer: GRDSTA parameter error\n"));
				return D_IM_DISP_INPUT_PARAM_ERROR;
			}
			if ((loop > 0) && (ctrl->grdsta[loop-1].bit.DSH > ctrl->grdsta[loop].bit.DSH)) {
				Im_DISP_Check_Point(("CP:imDispParamCheckCtrlOsdLayer() 3\n"));
				Ddim_Print(("E:im_disp1_ctrl_osd_layer: GRDSTA parameter error\n"));
				return D_IM_DISP_INPUT_PARAM_ERROR;
			}
		}
		for(loop = ImDisp_D_IM_DISP_OSD_ADDR_0_BANK_SIZE - 1; loop >= 0; loop--) {
			if (im_disp_param_check_grsa(ctrl->grsa0[loop]) != D_DDIM_OK){
				Ddim_Print(("E:im_disp1_ctrl_osd_layer: GRSA0 parameter error\n"));
				return D_IM_DISP_INPUT_PARAM_ERROR;
			}
		}
		for(loop = ImDisp_D_IM_DISP_OSD_ADDR_BANK_SIZE - 1; loop >= 0; loop--) {
			if (im_disp_param_check_grsa(ctrl->grsa[loop]) != D_DDIM_OK){
				Ddim_Print(("E:im_disp1_ctrl_osd_layer: GRSA parameter error\n"));
				return D_IM_DISP_INPUT_PARAM_ERROR;
			}
		}
		if (im_disp_param_check_resize(ctrl->grrsz0, ctrl->grrsz1, ctrl->grrsz2, ctrl->grrsz3) != D_DDIM_OK){
			Ddim_Print(("E:im_disp1_ctrl_osd_layer: GRRSZ0/GRRSZ1/GRRSZ2 parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
	}

	return ret;
}

/*----------------------------------------------------------------------*/
/* Global Function														*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
/* Initialize DISP macro to clear soft-reset bit.
*/
VOID im_disp1_init(ImDisp1 * self)
{
	imDispIclkOn();
	im_disp_pclk_on(im_disp_new());
	Im_DISP_Dsb();

	// Clear SR.
	// Common block 0.
	IO_DISP.MAIN[0].LCH.LRST.word			= D_IM_DISP_SR_CANCEL;	// Main data input block.
	IO_DISP.MAIN[0].DCORE.RESET.word		= D_IM_DISP_SR_CANCEL;	// Data output block.
	IO_DISP.MAIN[0].GRCH[0].GRRST.word		= D_IM_DISP_SR_CANCEL;	// OSD_0 data input block.
	IO_DISP.MAIN[0].GRCH[1].GRRST.word		= D_IM_DISP_SR_CANCEL;	// OSD_1 data input block.
	// Common block 1.
	IO_DISP.MAIN[1].LCH.LRST.word			= D_IM_DISP_SR_CANCEL;	// Main data input block.
	IO_DISP.MAIN[1].DCORE.RESET.word		= D_IM_DISP_SR_CANCEL;	// Data output block.
	IO_DISP.MAIN[1].GRCH[0].GRRST.word		= D_IM_DISP_SR_CANCEL;	// OSD_0 data input block.
	IO_DISP.MAIN[1].GRCH[1].GRRST.word		= D_IM_DISP_SR_CANCEL;	// OSD_1 data input block.

	// MIPI-DSI.
	IO_DISP.MDSCTL.MDSSR.word				= D_IM_DISP_SR_CANCEL;

	// HDMI.
	IO_DISP.JDDISP_HDMI_HDMIC.HDMISR.word	= D_IM_DISP_SR_CANCEL;

	Im_DISP_Dsb();

	im_disp_pclk_off(im_disp_new());
	Im_DISP_Dsb();
}

/* Set control data of main data input block.
*/
INT32 im_disp1_ctrl_main_layer(ImDisp1 * self, ImDispEImDispSel block, T_IM_DISP_CTRL_MAIN_LAYER_TRG_LIMIT const *const ctrl_trg_limit, T_IM_DISP_CTRL_MAIN_LAYER const *const ctrl)
{
	INT32 loop;
	INT32 ret = D_DDIM_OK;
	ULONG rpgen;

#ifdef CO_PARAM_CHECK
	if ((ctrl_trg_limit == NULL) && (ctrl == NULL)) {
		// Error when all arguments are NULL.
		Ddim_Print(("E:im_disp1_ctrl_main_layer: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (im_disp_param_check_ctrl_main_layer(block, ctrl) != D_DDIM_OK) {
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Set RPGEN off
	rpgen = IO_DISP.MAIN[block].DCORE.RPGEN.word;
	IO_DISP.MAIN[block].DCORE.RPGEN.word = D_IM_DISP_ENABLE_OFF;
	Im_DISP_Dsb();

	// Set data to this layer
	if (ctrl_trg_limit != NULL) {
		// Set core part
		if(IO_DISP.MAIN[block].LCH.LTRG.word == ImDisp_E_IM_DISP_TRG_READ_NO_ACT ){
			// Must stop LCH's Trigger
			// Set LRPGCTL
			IO_DISP.MAIN[block].LCH.LRPGCTL.word = ctrl_trg_limit->lrpgctl;

			// Set LTBLASET.igtaen/LTBLASET.gtaen
			IO_DISP.MAIN[block].LCH.LTBLASET.bit.igtaen = ctrl_trg_limit->ltblaset_igtaen;
			IO_DISP.MAIN[block].LCH.LTBLASET.bit.gtaen = ctrl_trg_limit->ltblaset_gtaen;
		}
		else{
			// TRG is on, enable setting possible.
			if (ctrl_trg_limit->ltblaset_igtaen == ImDisp_E_IM_DISP_TABLE_ACCESS_ENABLE) {
				// Set LTBLASET.igtaen
				IO_DISP.MAIN[block].LCH.LTBLASET.bit.igtaen = ctrl_trg_limit->ltblaset_igtaen;
			}
			if (ctrl_trg_limit->ltblaset_gtaen == ImDisp_E_IM_DISP_TABLE_ACCESS_ENABLE) {
				// Set LTBLASET.gtaen
				IO_DISP.MAIN[block].LCH.LTBLASET.bit.gtaen = ctrl_trg_limit->ltblaset_gtaen;
			}
		}
	}

	if(ctrl != NULL) {
		// Set LIDT0/LIDT1/LISIZE
		IO_DISP.MAIN[block].LCH.LIDT0.word = ctrl->lidt.word[0];
		IO_DISP.MAIN[block].LCH.LIDT1.word = ctrl->lidt.word[1];
		IO_DISP.MAIN[block].LCH.LISIZE.word = ctrl->lisize.word;
		// Set LYSA/LCSA
		for(loop = D_IM_DISP_MAIN_ADDR_BANK_SIZE - 1; loop >= 0; loop--) {
			IO_DISP.MAIN[block].LCH.LYSA[loop].word = ctrl->laddr[loop].y_addr;
			IO_DISP.MAIN[block].LCH.LCSA[loop].word = ctrl->laddr[loop].c_addr;
		}
		// Set LYHGA/LCHGA
		IO_DISP.MAIN[block].LCH.LYHGA.word = ctrl->y_hga;
		IO_DISP.MAIN[block].LCH.LCHGA.word = ctrl->c_hga;
		// Set LIBCTL.IBEN/LIBCTL.IBSET
		IO_DISP.MAIN[block].LCH.LIBCTL.bit.IBEN = 0;
		IO_DISP.MAIN[block].LCH.LIBCTL.bit.IBSET = ctrl->libctl_ibset;

		// Set LRSZ0/LRSZ1/LRSZ2/LRSZ3
		IO_DISP.MAIN[block].LCH.LRSZ0.word = ctrl->lrsz0;
		IO_DISP.MAIN[block].LCH.LRSZ1.word = ctrl->lrsz1.word;
		IO_DISP.MAIN[block].LCH.LRSZ2.word = ctrl->lrsz2.word;
		IO_DISP.MAIN[block].LCH.LRSZ3.word = ctrl->lrsz3.word;

		// Set LCEPMD
		// 3DA register unmatch, chekc V1.0
		// IO_DISP.MAIN[block].LCH.LCEPMD.word = ctrl->lcepmd;

		// Set LYHLPCTL/LYHLPK0/LYHLPK1/LYHLPOL/LYHLPCLR
		IO_DISP.MAIN[block].LCH.LYHLPCTL.word = ctrl->yhlp.lyhlpcl.word;
		IO_DISP.MAIN[block].LCH.LYHLPK0.word = ctrl->yhlp.lyhlpk.word[0];
		IO_DISP.MAIN[block].LCH.LYHLPK1.word = ctrl->yhlp.lyhlpk.word[1];
		IO_DISP.MAIN[block].LCH.LYHLPOL.word = ctrl->yhlp.lyhlpol.word;
		IO_DISP.MAIN[block].LCH.LYHLPCLR.dword = ctrl->yhlp.lyhlpclr.dword;

		// Set LYWCTL/LYW0TH/LYW1TH/LYW0ST/LYW0CA/LYW0CB/LYW1ST/LYW1CA/LYW1CB/LBOST
		IO_DISP.MAIN[block].LCH.LYWCTL.word = ctrl->warning.lywctl.word;
		IO_DISP.MAIN[block].LCH.LYW0TH.word = ctrl->warning.lyw0th.word;
		IO_DISP.MAIN[block].LCH.LYW1TH.word = ctrl->warning.lyw1th.word;
		IO_DISP.MAIN[block].LCH.LYW0ST.word = ctrl->warning.lyw0st;
		IO_DISP.MAIN[block].LCH.LYW0CA.dword = ctrl->warning.lyw0ca.dword;
		IO_DISP.MAIN[block].LCH.LYW0CB.dword = ctrl->warning.lyw0cb.dword;
		IO_DISP.MAIN[block].LCH.LYW1ST.word = ctrl->warning.lyw1st;
		IO_DISP.MAIN[block].LCH.LYW1CA.dword = ctrl->warning.lyw1ca.dword;
		IO_DISP.MAIN[block].LCH.LYW1CB.dword = ctrl->warning.lyw1cb.dword;
		IO_DISP.MAIN[block].LCH.LBOST.word = ctrl->warning.lbost;
		// Set LBLTMR
		IO_DISP.MAIN[block].LCH.LBLTMR.word = ctrl->lbltmr.word;

		// Set LZBWID/LZBV/LZBPT
		IO_DISP.MAIN[block].LCH.LZBWID.word = ctrl->zebra.lzbwid.word;
		IO_DISP.MAIN[block].LCH.LZBV.word = ctrl->zebra.lzbv.word;
		IO_DISP.MAIN[block].LCH.LZBPT.word = ctrl->zebra.lzbpt.word;

		// Set LY2R0/LY2R1/LY2R2/LCC0/LCC1/LCC2
		for(loop = D_IM_DISP_MATRIX_SIZE - 1; loop >= 0; loop--) {
			IO_DISP.MAIN[block].LCH.LY2R[loop].dword = ctrl->ly2r[loop].dword;
			IO_DISP.MAIN[block].LCH.LCC[loop].dword = ctrl->lcc[loop].dword;
		}

		// Set LTBLASET.igen
		if (ctrl->ltblaset_igen) {
			// check anti-gamma table access enable.
			if (IO_DISP.MAIN[block].LCH.LTBLASET.bit.igtaen == ImDisp_E_IM_DISP_TABLE_ACCESS_ENABLE) {
				// setting enable.
				IO_DISP.MAIN[block].LCH.LTBLASET.bit.igen = E_IM_DISP_CORRECT_PROC_ENABLE;
			}
			else {
				// not setting enable.
				Ddim_Print(("W:im_disp1_ctrl_main_layer: not setting anti-gamma correction enable\n"));
			}
		}
		else {
			// settign disable.
			IO_DISP.MAIN[block].LCH.LTBLASET.bit.igen = E_IM_DISP_CORRECT_PROC_DISABLE;
		}
		// Set LTBLASET.gmen
		if (ctrl->ltblaset_gmen) {
			// check gamma table access enable.
			if (IO_DISP.MAIN[block].LCH.LTBLASET.bit.gtaen == ImDisp_E_IM_DISP_TABLE_ACCESS_ENABLE) {
				// setting enable.
				IO_DISP.MAIN[block].LCH.LTBLASET.bit.gmen = E_IM_DISP_CORRECT_PROC_ENABLE;
			}
			else {
				// not setting enable.
				Ddim_Print(("W:im_disp1_ctrl_main_layer: not setting gamma correction enable\n"));
			}
		}
		else {
			// setting disable.
			IO_DISP.MAIN[block].LCH.LTBLASET.bit.gmen = E_IM_DISP_CORRECT_PROC_DISABLE;
		}
		// Set LTBLASET.igtsl/LTBLASET.gmtsl
		IO_DISP.MAIN[block].LCH.LTBLASET.bit.igtsl = ctrl->ltblaset_igtsl;
		IO_DISP.MAIN[block].LCH.LTBLASET.bit.gmtsl = ctrl->ltblaset_gmtsl;

		// Set LGMMD/LALP
		IO_DISP.MAIN[block].LCH.LGMMD.word = ctrl->lgmmd.word;
		IO_DISP.MAIN[block].LCH.LALP.word = ctrl->lalp.word;

		// Set LDSTA/LREVDISP
		IO_DISP.MAIN[block].LCH.LDSTA.word = ctrl->ldsta.word;
		IO_DISP.MAIN[block].LCH.LREVDISP.word = ctrl->lrevdisp.word;
	}

	// Recover RPGEN
	IO_DISP.MAIN[block].DCORE.RPGEN.word = rpgen;
	im_disp_pclk_off(im_disp_new());
	Im_DISP_Dsb();

	return ret;
}

/* Get control data of main data input block.
*/
INT32 im_disp1_get_ctrl_main_layer(ImDisp1 * self, ImDispEImDispSel block, T_IM_DISP_CTRL_MAIN_LAYER_TRG_LIMIT *const ctrl_trg_limit, T_IM_DISP_CTRL_MAIN_LAYER *const ctrl)
{
	INT32 loop;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ((ctrl_trg_limit == NULL) && (ctrl == NULL)) {
		// Error when all arguments are NULL.
		Ddim_Print(("E:im_disp1_get_ctrl_main_layer: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	if(ctrl_trg_limit != NULL) {
		// Get core part
		// Get LRPGCTL
		ctrl_trg_limit->lrpgctl = (ImDispEImDispRpgtmg)IO_DISP.MAIN[block].LCH.LRPGCTL.word;
		// Get LTBLASET.igtaen/LTBLASET.gtaen
		ctrl_trg_limit->ltblaset_igtaen = (ImDispEImDispTableAccess)IO_DISP.MAIN[block].LCH.LTBLASET.bit.igtaen;
		ctrl_trg_limit->ltblaset_gtaen = (ImDispEImDispTableAccess)IO_DISP.MAIN[block].LCH.LTBLASET.bit.gtaen;
	}

	if(ctrl != NULL) {
		// Get main part
		ctrl->lidt.word[0] = IO_DISP.MAIN[block].LCH.LIDT0.word;
		ctrl->lidt.word[1] = IO_DISP.MAIN[block].LCH.LIDT1.word;
		ctrl->lisize.word = IO_DISP.MAIN[block].LCH.LISIZE.word;
		// Get LYSA/LCSA
		for(loop = D_IM_DISP_MAIN_ADDR_BANK_SIZE - 1; loop >= 0; loop--) {
			ctrl->laddr[loop].y_addr = IO_DISP.MAIN[block].LCH.LYSA[loop].word;
			ctrl->laddr[loop].c_addr = IO_DISP.MAIN[block].LCH.LCSA[loop].word;
		}
		// Get LYHGA/LCHGA
		ctrl->y_hga = IO_DISP.MAIN[block].LCH.LYHGA.word;
		ctrl->c_hga = IO_DISP.MAIN[block].LCH.LCHGA.word;
		// Get LIBCTL.IBSET
		ctrl->libctl_ibset = (E_IM_DISP_BANK)IO_DISP.MAIN[block].LCH.LIBCTL.bit.IBSET;

		// Get LRSZ0/LRSZ1/LRSZ2/LRSZ3
		ctrl->lrsz0 = (ImDispEImDispRszsl)IO_DISP.MAIN[block].LCH.LRSZ0.bit.RSZSL;
		ctrl->lrsz1.word = IO_DISP.MAIN[block].LCH.LRSZ1.word;
		ctrl->lrsz2.word = IO_DISP.MAIN[block].LCH.LRSZ2.word;
		ctrl->lrsz3.word = IO_DISP.MAIN[block].LCH.LRSZ3.word;
		// Get LYHLPCTL/LYHLPK0/LYHLPK1/LYHLPOL/LYHLPCLR
		ctrl->yhlp.lyhlpcl.word = IO_DISP.MAIN[block].LCH.LYHLPCTL.word;
		ctrl->yhlp.lyhlpk.word[0] = IO_DISP.MAIN[block].LCH.LYHLPK0.word;
		ctrl->yhlp.lyhlpk.word[1] = IO_DISP.MAIN[block].LCH.LYHLPK1.word;
		ctrl->yhlp.lyhlpol.word = IO_DISP.MAIN[block].LCH.LYHLPOL.word;
		ctrl->yhlp.lyhlpclr.dword = IO_DISP.MAIN[block].LCH.LYHLPCLR.dword;

		// Get LYWCTL/LYW0TH/LYW1TH/LYW0ST/LYW0CA/LYW0CB/LYW1ST/LYW1CA/LYW1CB/LBLTMR/LBOST
		ctrl->warning.lywctl.word = IO_DISP.MAIN[block].LCH.LYWCTL.word;
		ctrl->warning.lyw0th.word = IO_DISP.MAIN[block].LCH.LYW0TH.word;
		ctrl->warning.lyw1th.word = IO_DISP.MAIN[block].LCH.LYW1TH.word;
		ctrl->warning.lyw0st = IO_DISP.MAIN[block].LCH.LYW0ST.word;
		ctrl->warning.lyw0ca.dword = IO_DISP.MAIN[block].LCH.LYW0CA.dword;
		ctrl->warning.lyw0cb.dword = IO_DISP.MAIN[block].LCH.LYW0CB.dword;
		ctrl->warning.lyw1st = IO_DISP.MAIN[block].LCH.LYW1ST.word;
		ctrl->warning.lyw1ca.dword = IO_DISP.MAIN[block].LCH.LYW1CA.dword;
		ctrl->warning.lyw1cb.dword = IO_DISP.MAIN[block].LCH.LYW1CB.dword;
		ctrl->warning.lbost = IO_DISP.MAIN[block].LCH.LBOST.word;
		ctrl->lbltmr.word = IO_DISP.MAIN[block].LCH.LBLTMR.word;

		// Get LZBWID/LZBV/LZBPT
		ctrl->zebra.lzbwid.word = IO_DISP.MAIN[block].LCH.LZBWID.word;
		ctrl->zebra.lzbv.word = IO_DISP.MAIN[block].LCH.LZBV.word;
		ctrl->zebra.lzbpt.word = IO_DISP.MAIN[block].LCH.LZBPT.word;

		// Get LY2R0/LY2R1/LY2R2/LCC0/LCC1/LCC2
		for(loop = D_IM_DISP_MATRIX_SIZE - 1; loop >= 0; loop--) {
			ctrl->ly2r[loop].dword = IO_DISP.MAIN[block].LCH.LY2R[loop].dword;
			ctrl->lcc[loop].dword = IO_DISP.MAIN[block].LCH.LCC[loop].dword;
		}
		// Get LTBLASET.igen/LTBLASET.igtsl/LTBLASET.gmen/LTBLASET.gmtsl
		ctrl->ltblaset_igen = (E_IM_DISP_CORRECT_PROC)IO_DISP.MAIN[block].LCH.LTBLASET.bit.igen;
		ctrl->ltblaset_igtsl = IO_DISP.MAIN[block].LCH.LTBLASET.bit.igtsl;
		ctrl->ltblaset_gmen = (E_IM_DISP_CORRECT_PROC)IO_DISP.MAIN[block].LCH.LTBLASET.bit.gmen;
		ctrl->ltblaset_gmtsl = IO_DISP.MAIN[block].LCH.LTBLASET.bit.gmtsl;
		// Get LGMMD/LALP
		ctrl->lgmmd.word = IO_DISP.MAIN[block].LCH.LGMMD.word;
		ctrl->lalp.word = IO_DISP.MAIN[block].LCH.LALP.word;

		// Get LDSTA/LREVDISP
		ctrl->ldsta.word = IO_DISP.MAIN[block].LCH.LDSTA.word;
		ctrl->lrevdisp.word = IO_DISP.MAIN[block].LCH.LREVDISP.word;
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set control data of data output block.
*/
INT32 im_disp1_ctrl_output(ImDisp1 * self, ImDispEImDispSel block, T_IM_DISP_CTRL_OUTPUT_TRG_LIMIT const *const ctrl_trg_limit, T_IM_DISP_CTRL_OUTPUT const *const ctrl)
{
	INT32 loop;
	ULONG rpgen;
	INT32 ret = D_DDIM_OK;

	//ImDisp0 * imDisp0 = im_disp0_get();

#ifdef CO_PARAM_CHECK
	if ((ctrl_trg_limit == NULL) && (ctrl == NULL)) {
		// Error when all arguments are NULL.
		Ddim_Print(("E:im_disp1_ctrl_output: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (im_disp_param_check_ctrl_output(block, ctrl_trg_limit, ctrl) != D_DDIM_OK){
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Set RPGEN off
	rpgen = IO_DISP.MAIN[block].DCORE.RPGEN.word;
	IO_DISP.MAIN[block].DCORE.RPGEN.word = D_IM_DISP_ENABLE_OFF;
	Im_DISP_Dsb();

	if(ctrl_trg_limit != NULL) {
		// Set core part
		if(IO_DISP.MAIN[block].DCORE.TRG.bit.TRG == ImDisp_E_IM_DISP_TRG_READ_NO_ACT ){
			// Must stop DCORE's TRiger
			// Set TRG.TGKMD/TGKST/TOCTL
			IO_DISP.MAIN[block].DCORE.TRG.bit.TGKMD = ctrl_trg_limit->tgkmd;
			IO_DISP.MAIN[block].DCORE.TGKST.word = ctrl_trg_limit->tgkst;
			IO_DISP.MAIN[block].DCORE.TOCTL.word = ctrl_trg_limit->toctl.word;
			// Set RPGCTL/POLSEL/TSL
			IO_DISP.MAIN[block].DCORE.RPGCTL.bit.RPGTMG = ctrl_trg_limit->rpgctl;
			IO_DISP.MAIN[block].DCORE.POLSEL.word = ctrl_trg_limit->polsel.word;
			IO_DISP.MAIN[block].DCORE.TSL.bit.TSL = ctrl_trg_limit->tsl;
			// Set VCYC/HCYC/VPW/HPW/VBLK/HBLK/VDLY/HDLY/OVSIZE/OHSIZE
			IO_DISP.MAIN[block].DCORE.VCYC.word = ctrl_trg_limit->vcyc.word;
			IO_DISP.MAIN[block].DCORE.HCYC.word = ctrl_trg_limit->hcyc;
			IO_DISP.MAIN[block].DCORE.OVPW.word = ctrl_trg_limit->ovpw.word;
			IO_DISP.MAIN[block].DCORE.HPW.word = ctrl_trg_limit->hpw;
			IO_DISP.MAIN[block].DCORE.VBLK.word = ctrl_trg_limit->vblk.word;
			IO_DISP.MAIN[block].DCORE.HBLK.word = ctrl_trg_limit->hblk;
			IO_DISP.MAIN[block].DCORE.VDLY.word = ctrl_trg_limit->vdly;
			IO_DISP.MAIN[block].DCORE.HDLY.word = ctrl_trg_limit->hdly;
			IO_DISP.MAIN[block].DCORE.OVSIZE.word = ctrl_trg_limit->ovsize;
			IO_DISP.MAIN[block].DCORE.OHSIZE.word = ctrl_trg_limit->ohsize;
			// Set VRFCTL/HRFCTL
			IO_DISP.MAIN[block].DCORE.VRFCTL.bit.VENS = ctrl_trg_limit->vrfctl;
			IO_DISP.MAIN[block].DCORE.HRFCTL.bit.HENS = ctrl_trg_limit->hrfctl;

			// Set DOMD
			IO_DISP.MAIN[block].DCORE.DOMD.word = ctrl_trg_limit->domd.word;
			// Set TBLASET.GMTAEN/TBLASET.YSATTA
			IO_DISP.MAIN[block].DCORE.TBLASET.bit.GMTAEN = ctrl_trg_limit->tblaset_gmtaen;
			IO_DISP.MAIN[block].DCORE.TBLASET.bit.YSATTA = ctrl_trg_limit->tblaset_ysatta;
		}
		else{
			// TRG is on, enable setting possible.
			if (ctrl_trg_limit->tblaset_gmtaen == ImDisp_E_IM_DISP_TABLE_ACCESS_ENABLE) {
				// Set TBLASET.GMTAEN
				IO_DISP.MAIN[block].DCORE.TBLASET.bit.GMTAEN = ctrl_trg_limit->tblaset_gmtaen;
			}
			if (ctrl_trg_limit->tblaset_ysatta == ImDisp_E_IM_DISP_TABLE_ACCESS_ENABLE) {
				// Set TBLASET.YSATTA
				IO_DISP.MAIN[block].DCORE.TBLASET.bit.YSATTA = ctrl_trg_limit->tblaset_ysatta;
			}
		}
	}

	if(ctrl != NULL) {
		// Set main part
		// Set INTC/INTE
		IO_DISP.MAIN[block].DCORE.INTC.word = ctrl->intc;
		IO_DISP.MAIN[block].DCORE.INTE.word = ctrl->inte.word;

		// Set HABLK
		IO_DISP.MAIN[block].DCORE.HABLK.bit.HABLK = ctrl->hablk;

		// Set FDOEN/FODATA/BLANKDT/CLBHSIZE
		IO_DISP.MAIN[block].DCORE.FDOEN.bit.FDEN = ctrl->fdoen;
		IO_DISP.MAIN[block].DCORE.FODATA.word = ctrl->fodata.word;
		IO_DISP.MAIN[block].DCORE.BLANKDT.BLANKDT1.word = ctrl->blankdt.word[0];
		IO_DISP.MAIN[block].DCORE.BLANKDT.BLANKDT2.word = ctrl->blankdt.word[1];
		IO_DISP.MAIN[block].DCORE.CLBHSIZE.word = ctrl->clbhsize;
		// Set CLBDT
		for(loop = D_IM_DISP_COLOR_BAR_COUNT - 1; loop >= 0; loop--) {
			IO_DISP.MAIN[block].DCORE.CLBDT[loop].word = ctrl->clbdt[loop].word;
		}
		// Set BLDCTL
		IO_DISP.MAIN[block].DCORE.BLDCTL.word = ctrl->bldctl.word;
		// Set R2Y0/1/2
		for(loop = D_IM_DISP_MATRIX_SIZE - 1; loop >= 0 ; loop--) {
			IO_DISP.MAIN[block].DCORE.R2Y[loop].dword = ctrl->r2y[loop].dword;
		}
		// Set YCAL/YCLIP/CBCAL/CBCLIP/CRCAL/CRCLIP
		IO_DISP.MAIN[block].DCORE.YCAL.bit.YGAIN = ctrl->clip_cal.y_cal.ygain;
		IO_DISP.MAIN[block].DCORE.YCAL.bit.YOFS = ctrl->clip_cal.y_cal.yofs;
		IO_DISP.MAIN[block].DCORE.YCLIP.bit.YCPH = ctrl->clip_cal.y_clip.cph;
		IO_DISP.MAIN[block].DCORE.YCLIP.bit.YCPL = ctrl->clip_cal.y_clip.cpl;
		IO_DISP.MAIN[block].DCORE.CBCAL.bit.CBGAIN = ctrl->clip_cal.cb_cal.cgain;
		im_disp_set_reg_signed(IO_DISP.MAIN[block].DCORE.CBCAL, union io_jdsdcore_reg_cbcal, CBOFS, ctrl->clip_cal.cb_cal.cofs);
		IO_DISP.MAIN[block].DCORE.CBCLIP.bit.CBCPH = ctrl->clip_cal.cb_clip.cph;
		IO_DISP.MAIN[block].DCORE.CBCLIP.bit.CBCPL = ctrl->clip_cal.cb_clip.cpl;
		IO_DISP.MAIN[block].DCORE.CRCAL.bit.CRGAIN = ctrl->clip_cal.cr_cal.cgain;
		im_disp_set_reg_signed(IO_DISP.MAIN[block].DCORE.CRCAL, union io_jdsdcore_reg_crcal, CROFS, ctrl->clip_cal.cr_cal.cofs);
		IO_DISP.MAIN[block].DCORE.CRCLIP.bit.CRCPH = ctrl->clip_cal.cr_clip.cph;
		IO_DISP.MAIN[block].DCORE.CRCLIP.bit.CRCPL = ctrl->clip_cal.cr_clip.cpl;
		// Set DOCTL0~DOCTL2
		IO_DISP.MAIN[block].DCORE.DOCTL0.word = ctrl->doctl0.word;
		IO_DISP.MAIN[block].DCORE.DOCTL1.word = ctrl->doctl1.word;
		IO_DISP.MAIN[block].DCORE.DOCTL2.word = ctrl->doctl2.word;
		// Set TRSCODE0/TRSCODE1
		IO_DISP.MAIN[block].DCORE.TRSCODE0.word = ctrl->trscode[0].word;
		IO_DISP.MAIN[block].DCORE.TRSCODE1.word = ctrl->trscode[1].word;
		// Set Y2R0/1/2
		for(loop = D_IM_DISP_MATRIX_SIZE - 1; loop >= 0 ; loop--) {
			IO_DISP.MAIN[block].DCORE.Y2R[loop].dword = ctrl->y2r[loop].dword;
		}
		// Set TBLASET.gmen
		if (ctrl->tblaset_gmen) {
			// check gamma table access enable.
			if (IO_DISP.MAIN[block].DCORE.TBLASET.bit.GMTAEN == ImDisp_E_IM_DISP_TABLE_ACCESS_ENABLE) {
				// setting enable.
				IO_DISP.MAIN[block].DCORE.TBLASET.bit.gmen = E_IM_DISP_CORRECT_PROC_ENABLE;
			}
			else {
				// not setting enable.
				Ddim_Print(("W:im_disp1_ctrl_output: not setting gamma correction enable\n"));
			}
		}
		else {
			// settign disable.
			IO_DISP.MAIN[block].DCORE.TBLASET.bit.gmen = E_IM_DISP_CORRECT_PROC_DISABLE;
		}
		// Set TBLASET.YSATEN
		if (ctrl->tblaset_ysaten) {
			// check luminance and chroma table access enable.
			if (IO_DISP.MAIN[block].DCORE.TBLASET.bit.YSATTA == ImDisp_E_IM_DISP_TABLE_ACCESS_ENABLE) {
				// setting enable.
				IO_DISP.MAIN[block].DCORE.TBLASET.bit.YSATEN = E_IM_DISP_CORRECT_PROC_ENABLE;
			}
			else {
				// not setting enable.
				Ddim_Print(("W:im_disp1_ctrl_output: not setting luminance and chroma correction enable\n"));
			}
		}
		else {
			// setting disable.
			IO_DISP.MAIN[block].DCORE.TBLASET.bit.YSATEN = E_IM_DISP_CORRECT_PROC_DISABLE;
		}
		// Set TBLASET.gmtsl/TBLASET.YSATSL
		IO_DISP.MAIN[block].DCORE.TBLASET.bit.gmtsl = ctrl->tblaset_gmtsl;
		IO_DISP.MAIN[block].DCORE.TBLASET.bit.YSATSL = ctrl->tblaset_ysatsl;

		// Set FFDSTA/FFSIZE/FFWIDTH/FFCLR
		for(loop = D_IM_DISP_FACE_FRAME_COUNT - 1; loop >= 0 ; loop--) {
			IO_DISP.MAIN[block].DCORE.FFDSTA[loop].word = ctrl->face.param[loop].ffdsta.word;
			IO_DISP.MAIN[block].DCORE.FFSIZE[loop].word = ctrl->face.param[loop].ffsize.word;
			IO_DISP.MAIN[block].DCORE.FFWIDTH[loop].word = ctrl->face.param[loop].ffwidth.word;
			IO_DISP.MAIN[block].DCORE.FFCLR[loop].word = ctrl->face.param[loop].ffclr.word;
		}
		// Set FFDISPEN
		IO_DISP.MAIN[block].DCORE.FFDISPEN.bit.FFDEN = ctrl->face.ffden;
		// Set FFDO
		IO_DISP.MAIN[block].DCORE.FFDO.bit.MSFF = ctrl->face.msff;

		// Set Call back function at interrupt
		im_disp0_memcpy(self->imDisp0, block,  ctrl);
	}

	// Recover RPGEN
	IO_DISP.MAIN[block].DCORE.RPGEN.word = rpgen;
	im_disp_pclk_off(im_disp_new());
	Im_DISP_Dsb();

	return ret;
}


/* Get control data of data output block.
*/
INT32 im_disp1_get_ctrl_output(ImDisp1 * self, ImDispEImDispSel block, T_IM_DISP_CTRL_OUTPUT_TRG_LIMIT *const ctrl_trg_limit, T_IM_DISP_CTRL_OUTPUT *const ctrl)
{
	INT32 loop;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ((ctrl_trg_limit == NULL) && (ctrl == NULL)) {
		// Error when all arguments are NULL.
		Ddim_Print(("E:im_disp1_get_ctrl_output: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	if(ctrl_trg_limit != NULL) {
		// Get core part
		// Get TRG.TGKMD/TGKST/TOCTL
		ctrl_trg_limit->tgkmd = (ImDispEImDispTgkmd)IO_DISP.MAIN[block].DCORE.TRG.bit.TGKMD;
		ctrl_trg_limit->tgkst = IO_DISP.MAIN[block].DCORE.TGKST.word;
		ctrl_trg_limit->toctl.word = IO_DISP.MAIN[block].DCORE.TOCTL.word;
		// Get RPGCTL/POLSEL/TSL
		ctrl_trg_limit->rpgctl = (ImDispEImDispRpgtmg)IO_DISP.MAIN[block].DCORE.RPGCTL.bit.RPGTMG;
		ctrl_trg_limit->polsel.word = IO_DISP.MAIN[block].DCORE.POLSEL.word;
		ctrl_trg_limit->tsl = IO_DISP.MAIN[block].DCORE.TSL.bit.TSL;
		// Get VCYC/HCYC/VPW/HPW/VBLK/HBLK/VDLY/HDLY/OVSIZE/OHSIZE
		ctrl_trg_limit->vcyc.word = IO_DISP.MAIN[block].DCORE.VCYC.word;
		ctrl_trg_limit->hcyc = IO_DISP.MAIN[block].DCORE.HCYC.word;
		ctrl_trg_limit->ovpw.word = IO_DISP.MAIN[block].DCORE.OVPW.word;
		ctrl_trg_limit->hpw = IO_DISP.MAIN[block].DCORE.HPW.word;
		ctrl_trg_limit->vblk.word = IO_DISP.MAIN[block].DCORE.VBLK.word;
		ctrl_trg_limit->hblk = IO_DISP.MAIN[block].DCORE.HBLK.word;
		ctrl_trg_limit->vdly = IO_DISP.MAIN[block].DCORE.VDLY.word;
		ctrl_trg_limit->hdly = IO_DISP.MAIN[block].DCORE.HDLY.word;
		ctrl_trg_limit->ovsize = IO_DISP.MAIN[block].DCORE.OVSIZE.word;
		ctrl_trg_limit->ohsize = IO_DISP.MAIN[block].DCORE.OHSIZE.word;
		// Get VRFCTL/HRFCTL
		ctrl_trg_limit->vrfctl = IO_DISP.MAIN[block].DCORE.VRFCTL.bit.VENS;
		ctrl_trg_limit->hrfctl = IO_DISP.MAIN[block].DCORE.HRFCTL.bit.HENS;
		// Get DOMD
		ctrl_trg_limit->domd.word = IO_DISP.MAIN[block].DCORE.DOMD.word;
		// Get TBLASET.GMTAEN/TBLASET.YSATTA
		ctrl_trg_limit->tblaset_gmtaen = IO_DISP.MAIN[block].DCORE.TBLASET.bit.GMTAEN;
		ctrl_trg_limit->tblaset_ysatta = IO_DISP.MAIN[block].DCORE.TBLASET.bit.YSATTA;
	}

	if(ctrl != NULL) {
		// Get main part
		// Get INTC/INTE
		ctrl->intc = IO_DISP.MAIN[block].DCORE.INTC.word;
		ctrl->inte.word = IO_DISP.MAIN[block].DCORE.INTE.word;

		// Get HABLK
		ctrl->hablk = IO_DISP.MAIN[block].DCORE.HABLK.bit.HABLK;

		// Get FDOEN/FODATA/BLANKDT/CLBHSIZE
		ctrl->fdoen = IO_DISP.MAIN[block].DCORE.FDOEN.bit.FDEN;
		ctrl->fodata.word = IO_DISP.MAIN[block].DCORE.FODATA.word;
		ctrl->blankdt.word[0] = IO_DISP.MAIN[block].DCORE.BLANKDT.BLANKDT1.word;
		ctrl->blankdt.word[1] = IO_DISP.MAIN[block].DCORE.BLANKDT.BLANKDT2.word;
		ctrl->clbhsize = IO_DISP.MAIN[block].DCORE.CLBHSIZE.word;
		// Get CLBDT
		for(loop = D_IM_DISP_COLOR_BAR_COUNT - 1; loop >= 0; loop--) {
			ctrl->clbdt[loop].word = IO_DISP.MAIN[block].DCORE.CLBDT[loop].word;
		}
		// Get BLDCTL
		ctrl->bldctl.word = IO_DISP.MAIN[block].DCORE.BLDCTL.word;
		// Get R2Y0/1/2
		for(loop = D_IM_DISP_MATRIX_SIZE - 1; loop >= 0 ; loop--) {
			ctrl->r2y[loop].dword = IO_DISP.MAIN[block].DCORE.R2Y[loop].dword;
		}
		// Get YCAL/YCLIP/CBCAL/CBCLIP/CRCAL/CRCLIP
		ctrl->clip_cal.y_cal.ygain = IO_DISP.MAIN[block].DCORE.YCAL.bit.YGAIN;
		ctrl->clip_cal.y_cal.yofs = IO_DISP.MAIN[block].DCORE.YCAL.bit.YOFS;
		ctrl->clip_cal.y_clip.cph = IO_DISP.MAIN[block].DCORE.YCLIP.bit.YCPH;
		ctrl->clip_cal.y_clip.cpl = IO_DISP.MAIN[block].DCORE.YCLIP.bit.YCPL;
		ctrl->clip_cal.cb_cal.cgain = IO_DISP.MAIN[block].DCORE.CBCAL.bit.CBGAIN;
		im_disp_get_reg_signed(ctrl->clip_cal.cb_cal.cofs, IO_DISP.MAIN[block].DCORE.CBCAL, union io_jdsdcore_reg_cbcal, CBOFS);
		ctrl->clip_cal.cb_clip.cph = IO_DISP.MAIN[block].DCORE.CBCLIP.bit.CBCPH;
		ctrl->clip_cal.cb_clip.cpl = IO_DISP.MAIN[block].DCORE.CBCLIP.bit.CBCPL;
		ctrl->clip_cal.cr_cal.cgain = IO_DISP.MAIN[block].DCORE.CRCAL.bit.CRGAIN;
		im_disp_get_reg_signed(ctrl->clip_cal.cr_cal.cofs, IO_DISP.MAIN[block].DCORE.CRCAL, union io_jdsdcore_reg_crcal, CROFS);
		ctrl->clip_cal.cr_clip.cph = IO_DISP.MAIN[block].DCORE.CRCLIP.bit.CRCPH;
		ctrl->clip_cal.cr_clip.cpl = IO_DISP.MAIN[block].DCORE.CRCLIP.bit.CRCPL;
		// Get DOCTL0~DOCTL2
		ctrl->doctl0.word = IO_DISP.MAIN[block].DCORE.DOCTL0.word;
		ctrl->doctl1.word = IO_DISP.MAIN[block].DCORE.DOCTL1.word;
		ctrl->doctl2.word = IO_DISP.MAIN[block].DCORE.DOCTL2.word;
		// Get TRSCODE0/TRSCODE1
		ctrl->trscode[0].word = IO_DISP.MAIN[block].DCORE.TRSCODE0.word;
		ctrl->trscode[1].word = IO_DISP.MAIN[block].DCORE.TRSCODE1.word;
		// Get Y2R0/1/2
		for(loop = D_IM_DISP_MATRIX_SIZE - 1; loop >= 0 ; loop--) {
			ctrl->y2r[loop].dword = IO_DISP.MAIN[block].DCORE.Y2R[loop].dword;
		}
		// Get TBLASET.gmen/TBLASET.gmtsl/TBLASET.YSATEN/TBLASET.YSATSL
		ctrl->tblaset_gmen = IO_DISP.MAIN[block].DCORE.TBLASET.bit.gmen;
		ctrl->tblaset_gmtsl = IO_DISP.MAIN[block].DCORE.TBLASET.bit.gmtsl;
		ctrl->tblaset_ysaten = IO_DISP.MAIN[block].DCORE.TBLASET.bit.YSATEN;
		ctrl->tblaset_ysatsl = IO_DISP.MAIN[block].DCORE.TBLASET.bit.YSATSL;

		// Get FFDSTA/FFSIZE/FFWIDTH/FFCLR
		for(loop = D_IM_DISP_FACE_FRAME_COUNT - 1; loop >= 0 ; loop--) {
			ctrl->face.param[loop].ffdsta.word = IO_DISP.MAIN[block].DCORE.FFDSTA[loop].word;
			ctrl->face.param[loop].ffsize.word = IO_DISP.MAIN[block].DCORE.FFSIZE[loop].word;
			ctrl->face.param[loop].ffwidth.word = IO_DISP.MAIN[block].DCORE.FFWIDTH[loop].word;
			ctrl->face.param[loop].ffclr.word = IO_DISP.MAIN[block].DCORE.FFCLR[loop].word;
		}
		// Get FFDISPEN
		ctrl->face.ffden = IO_DISP.MAIN[block].DCORE.FFDISPEN.bit.FFDEN;
		// Get FFDO
		ctrl->face.msff = IO_DISP.MAIN[block].DCORE.FFDO.bit.MSFF;

		// Get Call back function at interrupt
		im_disp0_memcpy1(self->imDisp0,block,ctrl);
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set control data of Grid in common block.
*/
INT32 im_disp1_ctrl_grid_layer(ImDisp1 * self, ImDispEImDispSel block, T_IM_DISP_CTRL_GRID_LAYER const *const ctrl)
{
	INT32 ret = D_DDIM_OK;
	ULONG rpgen;

#ifdef CO_PARAM_CHECK
	if (ctrl == NULL) {
		Ddim_Print(("E:im_disp1_ctrl_grid_layer: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if(im_disp_param_check_grid(&(ctrl->grid)) != D_DDIM_OK){
		Ddim_Print(("E:im_disp1_ctrl_grid_layer: GHDSTA/GVDSTA/GLENGTH/GWIDTH/GITVL parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Set RPGEN off
	rpgen = IO_DISP.MAIN[block].DCORE.RPGEN.word;
	IO_DISP.MAIN[block].DCORE.RPGEN.word = D_IM_DISP_ENABLE_OFF;
	Im_DISP_Dsb();

	// Set GHDSTA/GVDSTA/GLENGTH/GWIDTH/GITVL/GNUM/GDCTL
	IO_DISP.MAIN[block].DCORE.GHDSTA.word = ctrl->grid.ghdsta.word;
	IO_DISP.MAIN[block].DCORE.GVDSTA.word = ctrl->grid.gvdsta.word;
	IO_DISP.MAIN[block].DCORE.GLENGTH.word = ctrl->grid.glength.word;
	IO_DISP.MAIN[block].DCORE.GWIDTH.word = ctrl->grid.gwidth.word;
	IO_DISP.MAIN[block].DCORE.GITVL.word = ctrl->grid.gitvl.word;
	IO_DISP.MAIN[block].DCORE.GNUM.word = ctrl->grid.gnum.word;
	IO_DISP.MAIN[block].DCORE.GDCTL.word = ctrl->grid.gdctl.word;

	// Set GDISPEN
	IO_DISP.MAIN[block].DCORE.GDISPEN.word = ctrl->gdispen;

	// Recover RPGEN
	IO_DISP.MAIN[block].DCORE.RPGEN.word = rpgen;
	im_disp_pclk_off(im_disp_new());
	Im_DISP_Dsb();

	return ret;
}

/* Get control data of Grid in common block.
*/
INT32 im_disp1_get_ctrl_grid_layer(ImDisp1 * self, ImDispEImDispSel block, T_IM_DISP_CTRL_GRID_LAYER *const ctrl)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (ctrl == NULL) {
		Ddim_Print(("E:im_disp1_ctrl_grid_layer: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get GHDSTA/GVDSTA/GLENGTH/GWIDTH/GITVL/GNUM/GDCTL
	ctrl->grid.ghdsta.word = IO_DISP.MAIN[block].DCORE.GHDSTA.word;
	ctrl->grid.gvdsta.word = IO_DISP.MAIN[block].DCORE.GVDSTA.word;
	ctrl->grid.glength.word = IO_DISP.MAIN[block].DCORE.GLENGTH.word;
	ctrl->grid.gwidth.word = IO_DISP.MAIN[block].DCORE.GWIDTH.word;
	ctrl->grid.gitvl.word = IO_DISP.MAIN[block].DCORE.GITVL.word;
	ctrl->grid.gnum.word = IO_DISP.MAIN[block].DCORE.GNUM.word;
	ctrl->grid.gdctl.word = IO_DISP.MAIN[block].DCORE.GDCTL.word;

	// Get GDISPEN
	ctrl->gdispen = (ImDispEImDispGdispen)IO_DISP.MAIN[block].DCORE.GDISPEN.bit.GDEN;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set control data of OSD data input block.
*/
INT32 im_disp1_ctrl_osd_layer(ImDisp1 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, ImDispEImDispRpgtmg* grrpgctl, T_IM_DISP_CTRL_OSD_LAYER const *const ctrl)
{
	INT32 layer_index;
	INT32 loop;
	INT32 ret = D_DDIM_OK;
	ULONG rpgen;

#ifdef CO_PARAM_CHECK
	if ((grrpgctl == NULL) && (ctrl == NULL)) {
		// Error when all arguments are NULL.
		Ddim_Print(("E:im_disp1_ctrl_osd_layer: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((layer != E_IM_DISP_SEL_LAYER_OSD_0) && (layer != E_IM_DISP_SEL_LAYER_OSD_1)) {
		Ddim_Print(("E:im_disp1_ctrl_osd_layer: layer parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (imDispParamCheckCtrlOsdLayer(ctrl) != D_DDIM_OK){
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Set RPGEN off
	rpgen = IO_DISP.MAIN[block].DCORE.RPGEN.word;
	IO_DISP.MAIN[block].DCORE.RPGEN.word = D_IM_DISP_ENABLE_OFF;
	Im_DISP_Dsb();

	// Set layer index
	if (layer == E_IM_DISP_SEL_LAYER_OSD_0) {
		layer_index = 0;
	}
	else {
		layer_index = 1;
	}

	if(grrpgctl != NULL){
		if(IO_DISP.MAIN[block].GRCH[layer_index].GRTRG.word == ImDisp_E_IM_DISP_TRG_READ_NO_ACT){
			// Must stop GRCH's TRiger
			// Set GRRPGCTL
			IO_DISP.MAIN[block].GRCH[layer_index].GRRPGCTL.word = *grrpgctl;
		}
		else{
			Ddim_Print(("E:im_disp1_ctrl_osd_layer: OSD-%d layer busy\n", layer_index));
			ret = D_IM_DISP_MACRO_BUSY_NG;
		}
	}

	if(ctrl != NULL){
		// Set GRIDT/GRTISIZE/GRTDSTA/GRIPO/GRSCCTL
		IO_DISP.MAIN[block].GRCH[layer_index].GRIDT.word = ctrl->gridt.word;
		IO_DISP.MAIN[block].GRCH[layer_index].GRTISIZE.word = ctrl->grtisize.word;
		IO_DISP.MAIN[block].GRCH[layer_index].GRTDSTA.word = ctrl->grtdsta.word;
		IO_DISP.MAIN[block].GRCH[layer_index].GRIPO.word = ctrl->gripo.word;
		IO_DISP.MAIN[block].GRCH[layer_index].GRSCCTL.bit.SCEN = 0;
		IO_DISP.MAIN[block].GRCH[layer_index].GRSCCTL.bit.IDSET = ctrl->grscctl_idset;

		// Set GRISIZE/GRASA/GRHGA/GRAHGA/GRDSTA
		for(loop = ImDisp_D_IM_DISP_OSD_DISPLAY_AREA_COUNT - 1; loop >= 0; loop--) {
			IO_DISP.MAIN[block].GRCH[layer_index].GRISIZE[loop].word = ctrl->grisize[loop].word;
			IO_DISP.MAIN[block].GRCH[layer_index].GRASA[loop].word = ctrl->grasa[loop];
			IO_DISP.MAIN[block].GRCH[layer_index].GRHGA[loop].word = ctrl->grhga[loop];
			IO_DISP.MAIN[block].GRCH[layer_index].GRAHGA[loop].word = ctrl->grahga[loop];
			IO_DISP.MAIN[block].GRCH[layer_index].GRDSTA[loop].word = ctrl->grdsta[loop].word;
		}
		// Set GRSA0
		for(loop = ImDisp_D_IM_DISP_OSD_ADDR_0_BANK_SIZE - 1; loop >= 0; loop--) {
			IO_DISP.MAIN[block].GRCH[layer_index].GRSA0[loop].word = ctrl->grsa0[loop];
		}
		// Set GRSA
		for(loop = ImDisp_D_IM_DISP_OSD_ADDR_BANK_SIZE - 1; loop >= 0; loop--) {
			IO_DISP.MAIN[block].GRCH[layer_index].GRSA[loop].word = ctrl->grsa[loop];
		}
		// Set GRAREN/GRBSL
		IO_DISP.MAIN[block].GRCH[layer_index].GRAREN.word = ctrl->graren;
		IO_DISP.MAIN[block].GRCH[layer_index].GRBSL.word = ctrl->grbsl;

		// Set GRBLINK
		for(loop = D_IM_DISP_GRBLINK_SIZE - 1; loop >= 0; loop--) {
			IO_DISP.MAIN[block].GRCH[layer_index].GRBLINK.word[loop] = ctrl->grblink.word[loop];
		}
		// Set GRBLINK/GRBITRG
		IO_DISP.MAIN[block].GRCH[layer_index].GRBINIT.word = ctrl->grbinit;
		IO_DISP.MAIN[block].GRCH[layer_index].GRBITRG.word = ctrl->grbitrg;
		// Set GRRSZ0/GRRSZ1/GRRSZ2/GRRSZ3
		IO_DISP.MAIN[block].GRCH[layer_index].GRRSZ0.word = ctrl->grrsz0;
		IO_DISP.MAIN[block].GRCH[layer_index].GRRSZ1.word = ctrl->grrsz1.word;
		IO_DISP.MAIN[block].GRCH[layer_index].GRRSZ2.word = ctrl->grrsz2.word;
		IO_DISP.MAIN[block].GRCH[layer_index].GRRSZ3.word = ctrl->grrsz3.word;

		// Set GRR2Y0~2/GRY2R0~2/GRCC0~2
		for(loop = D_IM_DISP_MATRIX_SIZE - 1; loop >= 0; loop--) {
			IO_DISP.MAIN[block].GRCH[layer_index].GRY2R[loop].word = ctrl->gry2r[loop].word;
		}
		// Set GRALP
		IO_DISP.MAIN[block].GRCH[layer_index].GRALP.word = ctrl->gralp;
	}

	// Recover RPGEN
	IO_DISP.MAIN[block].DCORE.RPGEN.word = rpgen;
	im_disp_pclk_off(im_disp_new());
	Im_DISP_Dsb();

	return ret;
}

/* Get control data of OSD layer in common block.
*/
INT32 im_disp1_get_ctrl_osd_layer(ImDisp1 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, ImDispEImDispRpgtmg* grrpgctl, T_IM_DISP_CTRL_OSD_LAYER *const ctrl)
{
	INT32 layer_index;
	INT32 loop;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ((grrpgctl == NULL) && (ctrl == NULL)) {
		// Error when all arguments are NULL.
		Ddim_Print(("E:im_disp1_get_ctrl_osd_layer: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((layer != E_IM_DISP_SEL_LAYER_OSD_0) && (layer != E_IM_DISP_SEL_LAYER_OSD_1)) {
		Ddim_Print(("E:im_disp1_get_ctrl_osd_layer: layer parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Set layer index
	if (layer == E_IM_DISP_SEL_LAYER_OSD_0) {
		layer_index = 0;
	}
	else {
		layer_index = 1;
	}

	if(grrpgctl != NULL){
		// Get GRRPGCTL
		*grrpgctl = (ImDispEImDispRpgtmg)IO_DISP.MAIN[block].GRCH[layer_index].GRRPGCTL.word;
	}

	if(ctrl != NULL){
		// Get GRIDT/GRTISIZE/GRTDSTA/GRIPO/GRSCCTL
		ctrl->gridt.word = IO_DISP.MAIN[block].GRCH[layer_index].GRIDT.word;
		ctrl->grtisize.word = IO_DISP.MAIN[block].GRCH[layer_index].GRTISIZE.word;
		ctrl->grtdsta.word = IO_DISP.MAIN[block].GRCH[layer_index].GRTDSTA.word;
		ctrl->gripo.word = IO_DISP.MAIN[block].GRCH[layer_index].GRIPO.word;
		ctrl->grscctl_idset = (ImDispEImDispInputDataArea)IO_DISP.MAIN[block].GRCH[layer_index].GRSCCTL.bit.IDSET;

		// Get GRISIZE/GRASA/GRHGA/GRAHGA/GRDSTA
		for(loop = ImDisp_D_IM_DISP_OSD_DISPLAY_AREA_COUNT - 1; loop >= 0; loop--) {
			ctrl->grisize[loop].word = IO_DISP.MAIN[block].GRCH[layer_index].GRISIZE[loop].word;
			ctrl->grasa[loop] = IO_DISP.MAIN[block].GRCH[layer_index].GRASA[loop].word;
			ctrl->grhga[loop] = IO_DISP.MAIN[block].GRCH[layer_index].GRHGA[loop].word;
			ctrl->grahga[loop] = IO_DISP.MAIN[block].GRCH[layer_index].GRAHGA[loop].word;
			ctrl->grdsta[loop].word = IO_DISP.MAIN[block].GRCH[layer_index].GRDSTA[loop].word;
		}
		// Get GRSA0
		for(loop = ImDisp_D_IM_DISP_OSD_ADDR_0_BANK_SIZE - 1; loop >= 0; loop--) {
			ctrl->grsa0[loop] = IO_DISP.MAIN[block].GRCH[layer_index].GRSA0[loop].word;
		}
		// Get GRSA
		for(loop = ImDisp_D_IM_DISP_OSD_ADDR_BANK_SIZE - 1; loop >= 0; loop--) {
			ctrl->grsa[loop] = IO_DISP.MAIN[block].GRCH[layer_index].GRSA[loop].word;
		}
		// Get GRAREN/GRBSL
		ctrl->graren = IO_DISP.MAIN[block].GRCH[layer_index].GRAREN.word;
		ctrl->grbsl = IO_DISP.MAIN[block].GRCH[layer_index].GRBSL.word;

		// Get GRBLINK
		for(loop = D_IM_DISP_GRBLINK_SIZE - 1; loop >= 0; loop--) {
			ctrl->grblink.word[loop] = IO_DISP.MAIN[block].GRCH[layer_index].GRBLINK.word[loop];
		}
		// Get GRBLINK/GRBITRG
		ctrl->grbinit = IO_DISP.MAIN[block].GRCH[layer_index].GRBINIT.word;
		ctrl->grbitrg = IO_DISP.MAIN[block].GRCH[layer_index].GRBITRG.word;
		// Get GRRSZ0/GRRSZ1/GRRSZ2/GRRSZ3
		ctrl->grrsz0 = (ImDispEImDispRszsl)IO_DISP.MAIN[block].GRCH[layer_index].GRRSZ0.bit.RSZSL;
		ctrl->grrsz1.word = IO_DISP.MAIN[block].GRCH[layer_index].GRRSZ1.word;
		ctrl->grrsz2.word = IO_DISP.MAIN[block].GRCH[layer_index].GRRSZ2.word;
		ctrl->grrsz3.word = IO_DISP.MAIN[block].GRCH[layer_index].GRRSZ3.word;

		// Get GRR2Y0~2/GRY2R0~2/GRCC0~2
		for(loop = D_IM_DISP_MATRIX_SIZE - 1; loop >= 0; loop--) {
			ctrl->gry2r[loop].word = IO_DISP.MAIN[block].GRCH[layer_index].GRY2R[loop].word;
		}

		// Get GRALP
		ctrl->gralp = IO_DISP.MAIN[block].GRCH[layer_index].GRALP.word;
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

ImDisp1 *im_disp1_new(void)
{
	ImDisp1* self = k_object_new_with_private(IM_TYPE_DISP1,sizeof(ImDisp1Private));
	return self;
}
