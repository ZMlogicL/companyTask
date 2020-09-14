/*
 * imdisp7.c
 *
 *  Created on: 2020年8月8日
 *      Author: sns
 */
#include "imdisp.h"
#include "imdisp3.h"
#include "imdisp4.h"
#include "imdisp6.h"
#include "imdisp7.h"
#include "jdsdisp3a.h"

#include "dd_arm.h"
#include "ddim_user_custom.h"
#include <stddef.h>
#include <string.h>

K_TYPE_DEFINE_WITH_PRIVATE(ImDisp7, im_disp7)
#define IM_DISP7_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), ImDisp7Private,IM_TYPE_DISP7))


struct _ImDisp7Private
{
	int a;
};

static void im_disp7_constructor(ImDisp7 *self)
{
//	ImDisp7Private *priv = IM_DISP7_GET_PRIVATE(self);
}

static void im_disp7_destructor(ImDisp7 *self)
{
//	ImDisp7Private *priv = IM_DISP7_GET_PRIVATE(self);
}


/* Set Luminance correct table.
*/
INT32 im_disp7_set_luminance_table(ImDisp7 * self, ImDispEImDispSel block, BYTE surface, USHORT* tbl)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (tbl == NULL) {
		Ddim_Print(("E:im_disp7_set_luminance_table: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}

	if ((surface != D_IM_DISP_TABLE_SURFACE_A) &&
		(surface != D_IM_DISP_TABLE_SURFACE_B)) {
		Ddim_Print(("E:im_disp7_set_luminance_table: Paramter check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());

	// check trigger.
	if ((IO_DISP.MAIN[block].DCORE.TRG.bit.TRG == ImDisp_E_IM_DISP_TRG_READ_NO_ACT) ||
		(IO_DISP.MAIN[block].DCORE.TBLASET.bit.YSATSL != surface)) {
		// Data output block is stopped, or or specified surface is unused.

		DDIM_User_AhbReg_SpinLock();
		im_disp_hclk_on(im_disp_new());

		// check table surface.
		if (surface == D_IM_DISP_TABLE_SURFACE_A) {
			// Set Luminance table (surface A)
			im_disp_access_gamma_table(im_disp_new(),(BYTE*)(tbl), (BYTE*)(&(IO_DISP_TBL.MAIN[block].DCORE.YSTBLAYT)),
										ImDisp_E_IM_DISP_CORRECT_SELECT_LUMINANCE, ImDisp_E_IM_DISP_ACCESS_GAMMA_SET);
		}
		else {
			// Set Luminance table (surface B)
			im_disp_access_gamma_table(im_disp_new(),(BYTE*)(tbl), (BYTE*)(&(IO_DISP_TBL.MAIN[block].DCORE.YSTBLBYT)),
										ImDisp_E_IM_DISP_CORRECT_SELECT_LUMINANCE, ImDisp_E_IM_DISP_ACCESS_GAMMA_SET);
		}

		im_disp_hclk_off(im_disp_new());
		DDIM_User_AhbReg_SpinUnLock();
	}
	else {
		Ddim_Print(("E:im_disp7_set_luminance_table: Output layer busy and specified surface is being used\n"));
		ret = D_IM_DISP_MACRO_BUSY_NG;
	}

	im_disp_pclk_off(im_disp_new());

	return  ret;
}

/* Get Luminance correct table.
*/
INT32 im_disp7_get_luminance_table(ImDisp7 * self, ImDispEImDispSel block, BYTE surface, USHORT* tbl)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (tbl == NULL) {
		Ddim_Print(("E:im_disp7_get_luminance_table: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}

	if ((surface != D_IM_DISP_TABLE_SURFACE_A) &&
		(surface != D_IM_DISP_TABLE_SURFACE_B)) {
		Ddim_Print(("E:im_disp7_get_luminance_table: Parameter check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());

	// check trigger.
	if ((IO_DISP.MAIN[block].DCORE.TRG.bit.TRG == ImDisp_E_IM_DISP_TRG_READ_NO_ACT) ||
		(IO_DISP.MAIN[block].DCORE.TBLASET.bit.YSATSL != surface)) {
		// Data output block is stopped, or or specified surface is unused.

		DDIM_User_AhbReg_SpinLock();
		im_disp_hclk_on(im_disp_new());

		// check table surface.
		if (surface == D_IM_DISP_TABLE_SURFACE_A) {
			// Get Luminance table (surface A)
			im_disp_access_gamma_table(im_disp_new(),(BYTE*)(tbl), (BYTE*)(&(IO_DISP_TBL.MAIN[block].DCORE.YSTBLAYT)),
										ImDisp_E_IM_DISP_CORRECT_SELECT_LUMINANCE, ImDisp_E_IM_DISP_ACCESS_GAMMA_GET);
		}
		else {
			// Get Luminance table (surface B)
			im_disp_access_gamma_table(im_disp_new(),(BYTE*)(tbl), (BYTE*)(&(IO_DISP_TBL.MAIN[block].DCORE.YSTBLBYT)),
										ImDisp_E_IM_DISP_CORRECT_SELECT_LUMINANCE, ImDisp_E_IM_DISP_ACCESS_GAMMA_GET);
		}

		im_disp_hclk_off(im_disp_new());
		DDIM_User_AhbReg_SpinUnLock();
	}
	else {
		Ddim_Print(("E:im_disp7_set_luminance_table: Output layer busy and specified surface is being used\n"));
		ret = D_IM_DISP_MACRO_BUSY_NG;
	}

	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set Chroma correct gain table.
*/
INT32 im_disp7_set_chroma_gain_table(ImDisp7 * self, ImDispEImDispSel block, BYTE surface, USHORT* tbl)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (tbl == NULL) {
		Ddim_Print(("E:im_disp7_set_chroma_gain_table: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}

	if ((surface != D_IM_DISP_TABLE_SURFACE_A) &&
		(surface != D_IM_DISP_TABLE_SURFACE_B)) {
		Ddim_Print(("E:im_disp7_set_chroma_gain_table: Paramter check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());

	// check trigger.
	if ((IO_DISP.MAIN[block].DCORE.TRG.bit.TRG == ImDisp_E_IM_DISP_TRG_READ_NO_ACT) ||
		(IO_DISP.MAIN[block].DCORE.TBLASET.bit.YSATSL != surface)) {
		// Data output block is stopped, or or specified surface is unused.

		DDIM_User_AhbReg_SpinLock();
		im_disp_hclk_on(im_disp_new());

		// check table surface.
		if (surface == D_IM_DISP_TABLE_SURFACE_A) {
			// Set Chroma gain table (surface A)
			im_disp_access_gamma_table(im_disp_new(),(BYTE*)(tbl), (BYTE*)(&(IO_DISP_TBL.MAIN[block].DCORE.YSTBLACG)),
										ImDisp_E_IM_DISP_CORRECT_SELECT_CHROMA, ImDisp_E_IM_DISP_ACCESS_GAMMA_SET);
		}
		else {
			// Set Chroma gain table (surface B)
			im_disp_access_gamma_table(im_disp_new(),(BYTE*)(tbl), (BYTE*)(&(IO_DISP_TBL.MAIN[block].DCORE.YSTBLBCG)),
										ImDisp_E_IM_DISP_CORRECT_SELECT_CHROMA, ImDisp_E_IM_DISP_ACCESS_GAMMA_SET);
		}

		im_disp_hclk_off(im_disp_new());
		DDIM_User_AhbReg_SpinUnLock();
	}
	else {
		Ddim_Print(("E:im_disp7_set_chroma_gain_table: Output layer busy and specified surface is being used\n"));
		ret = D_IM_DISP_MACRO_BUSY_NG;
	}

	im_disp_pclk_off(im_disp_new());

	return  ret;
}

/* Get Chroma correct gain table.
*/
INT32 im_disp7_get_chroma_gain_table(ImDisp7 * self, ImDispEImDispSel block, BYTE surface, USHORT* tbl)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (tbl == NULL) {
		Ddim_Print(("E:im_disp7_get_chroma_gain_table: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}

	if ((surface != D_IM_DISP_TABLE_SURFACE_A) &&
		(surface != D_IM_DISP_TABLE_SURFACE_B)) {
		Ddim_Print(("E:im_disp7_get_chroma_gain_table: Paramter check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());

	// check trigger.
	if ((IO_DISP.MAIN[block].DCORE.TRG.bit.TRG == ImDisp_E_IM_DISP_TRG_READ_NO_ACT) ||
		(IO_DISP.MAIN[block].DCORE.TBLASET.bit.YSATSL != surface)) {
		// Data output block is stopped, or or specified surface is unused.

		DDIM_User_AhbReg_SpinLock();
		im_disp_hclk_on(im_disp_new());

		// check table surface.
		if (surface == D_IM_DISP_TABLE_SURFACE_A) {
			// Get Chroma gain table (surface A)
			im_disp_access_gamma_table(im_disp_new(),(BYTE*)(tbl), (BYTE*)(&(IO_DISP_TBL.MAIN[block].DCORE.YSTBLACG)),
										ImDisp_E_IM_DISP_CORRECT_SELECT_CHROMA, ImDisp_E_IM_DISP_ACCESS_GAMMA_GET);
		}
		else {
			// Get Chroma gain table (surface B)
			im_disp_access_gamma_table(im_disp_new(),(BYTE*)(tbl), (BYTE*)(&(IO_DISP_TBL.MAIN[block].DCORE.YSTBLBCG)),
										ImDisp_E_IM_DISP_CORRECT_SELECT_CHROMA, ImDisp_E_IM_DISP_ACCESS_GAMMA_GET);
		}

		im_disp_hclk_off(im_disp_new());
		DDIM_User_AhbReg_SpinUnLock();
	}
	else {
		Ddim_Print(("E:im_disp7_get_chroma_gain_table: Output layer busy and specified surface is being used\n"));
		ret = D_IM_DISP_MACRO_BUSY_NG;
	}

	im_disp_pclk_off(im_disp_new());

	return  ret;
}

/* Set MIPI-DSI IP input pin control 0.
*/
INT32 im_disp7_set_mipi_dsi_ctrl0(ImDisp7 * self, BYTE shudown, BYTE color_mode)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ((shudown != D_IM_DISP_ENABLE_OFF) && (shudown != D_IM_DISP_ENABLE_ON)) {
		Ddim_Print(("E:im_disp7_set_mipi_dsi_ctrl0: parameter error - shudown\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}

	if ((color_mode != D_IM_DISP_ENABLE_OFF) && (color_mode != D_IM_DISP_ENABLE_ON)) {
		Ddim_Print(("E:im_disp7_set_mipi_dsi_ctrl0: parameter error - color_mode\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());

	// Check trigger of common block that was selected MIPI.

	// Set MDSIC0
	IO_DISP.MDSCTL.MDSIC0.bit.MDSSD = shudown;
	IO_DISP.MDSCTL.MDSIC0.bit.MDSCM = color_mode;

	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get MIPI-DSI IP input pin control 0.
*/
INT32 im_disp7_get_mipi_dsi_ctrl0(ImDisp7 * self, BYTE* shudown, BYTE* color_mode)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ((shudown == NULL) || (color_mode == NULL)) {
		Ddim_Print(("E:im_disp7_get_mipi_dsi_ctrl0: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());

	// Get MDSIC0
	*shudown = IO_DISP.MDSCTL.MDSIC0.bit.MDSSD;
	*color_mode= IO_DISP.MDSCTL.MDSIC0.bit.MDSCM;

	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set MIPI-DSI IP input pin control 1.
*/
INT32 im_disp7_set_mipi_dsi_ctrl1(ImDisp7 * self)
{
	INT32 ret = D_DDIM_OK;

	im_disp_pclk_on(im_disp_new());

	// not DPI configuration update wait.
	if (IO_DISP.MDSCTL.MDSIC1.bit.MDSUDC != D_IM_DISP_MDSUDC_READ_UPDATE_WAIT) {
		// Set MDSIC1
		IO_DISP.MDSCTL.MDSIC1.bit.MDSUDC = D_IM_DISP_MDSUDC_WRITE_1SHOT;
	}
	else {
		// status NG.
		Ddim_Print(("E:im_disp7_set_mipi_dsi_ctrl1: Status NG - 1 shot signal input in update waiting.\n"));
		ret = D_IM_DISP_STATUS_ABNORMAL;
	}

	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get MIPI-DSI IP input pin control 1.
*/
INT32 im_disp7_get_mipi_dsi_ctrl1(ImDisp7 * self, BYTE* update_config)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (update_config == NULL) {
		Ddim_Print(("E:im_disp7_get_mipi_dsi_ctrl1: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());

	*update_config = IO_DISP.MDSCTL.MDSIC1.bit.MDSUDC;

	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set SR of IP (HDMI, MIPI).
*/
INT32 im_disp7_set_sr_ip(ImDisp7 * self, BYTE ip, BYTE sr)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (((ip & D_IM_DISP_IP_HDMI) != D_IM_DISP_IP_HDMI) &&
		((ip & D_IM_DISP_IP_MIPI) != D_IM_DISP_IP_MIPI)) {
		Ddim_Print(("E:im_disp7_set_sr_ip: ip parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((sr != D_IM_DISP_SR_CANCEL) && (sr != D_IM_DISP_SR_RESET)) {
		Ddim_Print(("E:im_disp7_set_sr_ip: sr parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());

	// HDMI IP Reset.
	if (((ip & D_IM_DISP_IP_HDMI) == D_IM_DISP_IP_HDMI) &&
		(IO_DISP.MAIN[ImDisp_E_IM_DISP_HDMI].DCORE.TRG.bit.TRG == ImDisp_E_IM_DISP_TRG_READ_NO_ACT)) {
		IO_DISP.JDDISP_HDMI_HDMIC.HDMISR.bit.SR = sr;	// software reset.
	}

	// MIPI-DSI IP Reset.
	if (((ip & D_IM_DISP_IP_MIPI) == D_IM_DISP_IP_MIPI) &&
		(IO_DISP.MAIN[ImDisp_E_IM_DISP_LCD_MIPI].DCORE.TRG.bit.TRG == ImDisp_E_IM_DISP_TRG_READ_NO_ACT)) {
		IO_DISP.MDSCTL.MDSSR.bit.SR = sr;				// software reset.
	}

	im_disp_pclk_off(im_disp_new());
	Im_DISP_Dsb();

	return ret;
}

/* Get SR of IP (HDMI, MIPI).
*/
INT32 im_disp7_get_sr_ip(ImDisp7 * self, BYTE *sr)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (sr == NULL) {
		Ddim_Print(("E:im_disp7_get_sr_ip: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());

	*sr = 0;

	// check SR bit of HDMI IP and MIPI IP.
	if (IO_DISP.JDDISP_HDMI_HDMIC.HDMISR.bit.SR == D_IM_DISP_SR_RESET) {
		*sr |= D_IM_DISP_IP_HDMI;
	}
	if (IO_DISP.MDSCTL.MDSSR.bit.SR == D_IM_DISP_SR_RESET) {
		*sr |= D_IM_DISP_IP_MIPI;
	}

	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set Write Channel control.
*/
INT32 im_disp7_set_write_channel_ctrl(ImDisp7 * self, E_IM_DISP_WC_NUM number, T_IM_DISP_CTRL_P2M const *const p2m, T_IM_DISP_CTRL_PWCH const *const pwch)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ((p2m == NULL) || (pwch == NULL)) {
		Ddim_Print(("E:im_disp7_set_write_channel_ctrl: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());

	// P2M Macro.

	// check status.
	if ((p2m->p2mpaen == D_IM_DISP_ENABLE_ON) ||
		(IO_DISP.P2M[number].P2MTRG.bit.P2MTRG == E_IM_DISP_P2M_PWCH_TRG_READ_NO_ACT)) {
		// Set P2MPAEN.
		IO_DISP.P2M[number].P2MPAEN.word	= p2m->p2mpaen;
	}

	// Set P2M2PMD (fix:1).
	IO_DISP.P2M[number].P2M2PMD.word		= 1;
	// Set P2MCTL.
	IO_DISP.P2M[number].P2MCTL.bit.PKNEMD	= 0;					// fix:0.
	IO_DISP.P2M[number].P2MCTL.bit.PLPF		= p2m->p2mctl_plpf;
	IO_DISP.P2M[number].P2MCTL.bit.P2MTYP	= p2m->p2mctl_p2mtyp;
	// Set P2MOFS/PBSFT/PCLPH.
	IO_DISP.P2M[number].P2MOFS.word			= p2m->p2mofs;
	IO_DISP.P2M[number].PBSFT.word			= p2m->pbsft;
	IO_DISP.P2M[number].PCLPH.word			= p2m->pclph;
	// Set PTRMV/PTRMH.
	IO_DISP.P2M[number].PTRMV.word			= p2m->ptrmv;
	IO_DISP.P2M[number].PTRMH.word			= p2m->ptrmh;
	// Set PTRMVW/PTRMHW.
	IO_DISP.P2M[number].PTRMVW.word			= p2m->ptrmvw;
	IO_DISP.P2M[number].PTRMHW.word			= p2m->ptrmhw;
	// Set PTRMXVCYC/PTRMXHCYC.
	IO_DISP.P2M[number].PTRMXVCYC.word		= p2m->ptrmxvcyc;
	IO_DISP.P2M[number].PTRMXHCYC.word		= p2m->ptrmxhcyc;
	// Set PTRMXVEN/PTRMXHEN.
	IO_DISP.P2M[number].PTRMXVEN.dword		= p2m->ptrmxven;
	IO_DISP.P2M[number].PTRMXHEN.dword		= p2m->ptrmxhen;
	// Set P2MMIR.
	IO_DISP.P2M[number].P2MMIR.word			= p2m->p2mmir;

	// PWCH Macro.
	// check trigger.
	if (IO_DISP.PWCH[number].PWCHTRG.bit.PWCHTRG == E_IM_DISP_P2M_PWCH_TRG_READ_NO_ACT) {
		// Set PWAXCTL.
		IO_DISP.PWCH[number].PWAXCTL.word	= pwch->pwaxctl.word;
	}

	// Set PWS (fix:0).
	IO_DISP.PWCH[number].PWS.word			= 0;

	// Set PWCHCTL.
	IO_DISP.PWCH[number].PWCHCTL.word		= 0x0002;		// PWLV[6:4]=000b, PWBMD[1:0]=01b.
	IO_DISP.PWCH[number].PWCHCTL.bit.PWMW	= pwch->pwmw;	// PWMW[8].
	// Set PWCHINTENB.
	IO_DISP.PWCH[number].PWCHINTENB.word	= pwch->pwchintenb.word;
	// Set PWSA/PWLSIZE.
	IO_DISP.PWCH[number].PWSA.word			= pwch->pwsa;
	IO_DISP.PWCH[number].PWLSIZE.word		= pwch->pwlsize;
	// Set PWVFM.
	IO_DISP.PWCH[number].PWVFM.word			= pwch->pwvfm;
	// Set PWDW.
	if (pwch->pwvfm == D_IM_DISP_FORMAT_VIDEO) {
		IO_DISP.PWCH[number].PWDW.word		= 0x0003;		// PWDW[1:0]=11b : 128byte aligned.
	}
	else {
		IO_DISP.PWCH[number].PWDW.word		= 0x0001;		// PWDW[1:0]=01b : 32byte aligned.
	}

	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get Write Channel control.
*/
INT32 im_disp7_get_write_channel_ctrl(ImDisp7 * self, E_IM_DISP_WC_NUM number, T_IM_DISP_CTRL_P2M  *const p2m, T_IM_DISP_CTRL_PWCH *const pwch)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ((p2m == NULL) || (pwch == NULL)) {
		Ddim_Print(("E:im_disp7_get_write_channel_ctrl: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());

	// P2M Macro.
	// Get P2MPAEN.
	p2m->p2mpaen		= IO_DISP.P2M[number].P2MPAEN.word;
	// Get P2MCTL.PLPF/P2MCTL.P2MTYP.
	p2m->p2mctl_plpf	= IO_DISP.P2M[number].P2MCTL.bit.PLPF;
	p2m->p2mctl_p2mtyp	= IO_DISP.P2M[number].P2MCTL.bit.P2MTYP;
	// Get P2MOFS/PBSFT/PCLPH.
	p2m->p2mofs			= IO_DISP.P2M[number].P2MOFS.word;
	p2m->pbsft			= IO_DISP.P2M[number].PBSFT.word;
	p2m->pclph			= IO_DISP.P2M[number].PCLPH.word;
	// Get PTRMV/PTRMH.
	p2m->ptrmv			= IO_DISP.P2M[number].PTRMV.word;
	p2m->ptrmh			= IO_DISP.P2M[number].PTRMH.word;
	// Get PTRMVW/PTRMHW.
	p2m->ptrmvw			= IO_DISP.P2M[number].PTRMVW.word;
	p2m->ptrmhw			= IO_DISP.P2M[number].PTRMHW.word;
	// Get PTRMXVCYC/PTRMXHCYC.
	p2m->ptrmxvcyc		= IO_DISP.P2M[number].PTRMXVCYC.word;
	p2m->ptrmxhcyc		= IO_DISP.P2M[number].PTRMXHCYC.word;
	// Get PTRMXVEN/PTRMXHEN.
	p2m->ptrmxven		= IO_DISP.P2M[number].PTRMXVEN.dword;
	p2m->ptrmxhen		= IO_DISP.P2M[number].PTRMXHEN.dword;
	// Get P2MMIR/P2M2PMD.
	p2m->p2mmir			= IO_DISP.P2M[number].P2MMIR.word;
	p2m->p2m2pmd		= IO_DISP.P2M[number].P2M2PMD.word;

	// PWCH Macro.
	// Get PWAXCTL.
	pwch->pwaxctl.word		= IO_DISP.PWCH[number].PWAXCTL.word;
	// Get PWCHCTL.PWMW.
	pwch->pwmw				= IO_DISP.PWCH[number].PWCHCTL.bit.PWMW;
	// Get PWCHINTENB.
	pwch->pwchintenb.word	= IO_DISP.PWCH[number].PWCHINTENB.word;
	// Get PWSA/PWLSIZE.
	pwch->pwsa				= IO_DISP.PWCH[number].PWSA.word;
	pwch->pwlsize			= IO_DISP.PWCH[number].PWLSIZE.word;
	// Get PWVFM.
	pwch->pwvfm				= IO_DISP.PWCH[number].PWVFM.word;

	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get write channel response.
*/
INT32 im_disp7_get_write_channel_response(ImDisp7 * self, E_IM_DISP_WC_NUM number, ULONG *response)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (response == NULL) {
		Ddim_Print(("E:im_disp7_get_write_channel_response: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());

	// Get PWCHBRESP.
	*response = IO_DISP.PWCH[number].PWCHBRESP.word;

	im_disp_pclk_off(im_disp_new());

	return ret;
}


#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
/* Set CSC matrix to covert from BT.601 to BT.709's RGB or no any convert.
*/
INT32 im_disp7_change_csc_matrix(ImDisp7 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, E_IM_DISP_CC_MATRIX convert)
{
	INT32 i;
	INT32 ret = D_DDIM_OK;
	U_IM_DISP_YR_MATRIX_COEFFICIENT matrix_to_709[D_IM_DISP_MATRIX_SIZE] = {
		{ 0x0000006500000040 },	// 0x40,0x00,0x65 (1.0,  0.0,      1.5748)
		{ 0x000000E200F40040 },	// 0x40,0xF4,0xE2 (1.0, -0.1873,  -0.4681)
		{ 0x0000000000770040 }	// 0x40,0x77,0x00 (1.0,  1.85565,  0.0)
	};
	U_IM_DISP_YR_MATRIX_COEFFICIENT matrix_to_through[D_IM_DISP_MATRIX_SIZE] = {
		// Default
		{ 0x0000005A00000040 },	// 0x40,0x00,0x5A (1.0,  0.0,       1.40625)
		{ 0x000000D300EA0040 },	// 0x40,0xEA,0xD3 (1.0, -0.34375,  -0.703125)
		{ 0x000000FF00710040 }	// 0x40,0x71,0xFF (1.0,  1.765625,  0.015625)
	};	// No any convert

	U_IM_DISP_GRY2R matrix_to_709_osd[D_IM_DISP_MATRIX_SIZE] = {
		{ 0x00650040 },	// 0x40,0x00,0x65 (1.0,  0.0,      1.5748)
		{ 0x00E2F440 },	// 0x40,0xF4,0xE2 (1.0, -0.1873,  -0.4681)
		{ 0x00007740 }	// 0x40,0x77,0x00 (1.0,  1.85565,  0.0)
	};
	U_IM_DISP_GRY2R matrix_to_through_osd[D_IM_DISP_MATRIX_SIZE] = {
		{ 0x005A0040 },	// 0x40,0x00,0x5A (1.0,  0.0,       1.40625)
		{ 0x00D3EA40 },	// 0x40,0xEA,0xD3 (1.0, -0.34375,  -0.703125)
		{ 0x00FF7140 }	// 0x40,0x71,0xFF (1.0,  1.765625,  0.015625)
	};

	E_IM_DISP_SEL_LAYER osd_layer[2] = {
		E_IM_DISP_SEL_LAYER_OSD_0, E_IM_DISP_SEL_LAYER_OSD_1
	};

	U_IM_DISP_YR_MATRIX_COEFFICIENT* ycc2rgb;
	U_IM_DISP_GRY2R* ycc2rgb_osd;

#ifdef CO_PARAM_CHECK
	if ((layer & E_IM_DISP_SEL_LAYER_ALL) == E_IM_DISP_SEL_LAYER_NONE) {
		Ddim_Print(("E:im_disp7_change_csc_matrix: layer parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	if(convert == E_IM_DISP_CC_MATRIX_709) {
		ycc2rgb		= matrix_to_709;
		ycc2rgb_osd	= matrix_to_709_osd;
	}
	else {
		ycc2rgb		= matrix_to_through;
		ycc2rgb_osd	= matrix_to_through_osd;
	}

	// Main
	if((layer & E_IM_DISP_SEL_LAYER_MAIN) == E_IM_DISP_SEL_LAYER_MAIN) {
		ret = im_disp3_set_matrix(im_disp3_new(),block, ycc2rgb);
	}
	// OSD
	for(i = 0; i < 2; i++) {
		if((layer & osd_layer[i]) == osd_layer[i]) {
			ret = im_disp6_set_osd_matrix(im_disp6_new(),block, layer, ycc2rgb_osd);
		}
	}
	// Output
	if((layer & E_IM_DISP_SEL_LAYER_DCORE) == E_IM_DISP_SEL_LAYER_DCORE) {
		ret = im_disp4_set_output_matrix(im_disp4_new(),block, E_IM_DISP_MATRIX_KIND_Y2R, ycc2rgb);
	}

	return ret;
}

/* Change color bar's color which was used as black back.
*/
VOID im_disp7_change_bb_color(ImDisp7 * self, ImDispEImDispSel block, U_IM_DISP_IMAGE_COLOR black_back_color)
{
	im_disp_pclk_on(im_disp_new());
	// Set CLBHSIZE/CLBDT0
	IO_DISP.MAIN[block].DCORE.CLBHSIZE.word = IO_DISP.MAIN[block].DCORE.OHSIZE.word;
	IO_DISP.MAIN[block].DCORE.CLBDT[0].word = black_back_color.word;
	im_disp_pclk_off(im_disp_new());
}

/* Get the color bar's color which was used as black back.
*/
INT32 im_disp7_check_bb_color(ImDisp7 * self, ImDispEImDispSel block, U_IM_DISP_IMAGE_COLOR* black_back_color)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (black_back_color == NULL) {
		Ddim_Print(("E:im_disp7_check_bb_color: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get CLBDT0
	black_back_color->word = IO_DISP.MAIN[block].DCORE.CLBDT[0].word;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Change grid.
*/
INT32 im_disp7_change_grid(ImDisp7 * self, ImDispEImDispSel block, UINT32 ghnum, UINT32 gvnum)
{
	ULONG ohsize;
	ULONG ovsize;
	ULONG ghitv;
	ULONG gvitv;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ((ghnum >= D_IM_DISP_GRID_NUM) || (gvnum >= D_IM_DISP_GRID_NUM)) {
		Ddim_Print(("E:im_disp7_change_grid: ghnum/gvnum parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	ohsize = IO_DISP.MAIN[block].DCORE.OHSIZE.word;
	ovsize = IO_DISP.MAIN[block].DCORE.OVSIZE.word;

	ghitv = ohsize / (ghnum + 2);
	gvitv = ovsize / (gvnum + 2);

	IO_DISP.MAIN[block].DCORE.GHDSTA.bit.GHDSV = ghitv - (IO_DISP.MAIN[block].DCORE.GWIDTH.bit.GHWID) / 2;
	IO_DISP.MAIN[block].DCORE.GVDSTA.bit.GVDSH = gvitv - (IO_DISP.MAIN[block].DCORE.GWIDTH.bit.GVWID) / 2;

	IO_DISP.MAIN[block].DCORE.GITVL.bit.GHITV = ghitv;
	IO_DISP.MAIN[block].DCORE.GITVL.bit.GVITV = gvitv;

	IO_DISP.MAIN[block].DCORE.GNUM.bit.GHNUM = ghnum;
	IO_DISP.MAIN[block].DCORE.GNUM.bit.GVNUM = gvnum;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Draw single face frame.
*/
INT32 im_disp7_draw_face_frame_single(ImDisp7 * self, ImDispEImDispSel block, INT32 index, INT32 enable, T_IM_DISP_FACE_FRAME_PARAM const *const face)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (face == NULL){
		Ddim_Print(("E:im_disp7_draw_face_frame_single: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (index >= D_IM_DISP_FACE_FRAME_COUNT){
		Ddim_Print(("E:im_disp7_draw_face_frame_single: index parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((enable != D_IM_DISP_ENABLE_OFF) && (enable != D_IM_DISP_ENABLE_ON)){
		Ddim_Print(("E:im_disp7_draw_face_frame_single: enable parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (im_disp_param_check_face_frame(face) != D_DDIM_OK){
		Ddim_Print(("E:im_disp7_draw_face_frame_single: FFDSTA/FFSIZE/FFWIDTH parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Set FFDSTA/FFSIZE/FFWIDTH/FFCLR
	IO_DISP.MAIN[block].DCORE.FFDSTA[index].word = face->ffdsta.word;
	IO_DISP.MAIN[block].DCORE.FFSIZE[index].word = face->ffsize.word;
	IO_DISP.MAIN[block].DCORE.FFWIDTH[index].word = face->ffwidth.word;
	IO_DISP.MAIN[block].DCORE.FFCLR[index].word = face->ffclr.word;

	// Set FFDISPEN
	if (enable == D_IM_DISP_ENABLE_ON) {
		// Display enable
		IO_DISP.MAIN[block].DCORE.FFDISPEN.bit.FFDEN |= ((ULLONG)D_IM_DISP_ENABLE_ON << index);
	}
	else {
		// Display disable
		IO_DISP.MAIN[block].DCORE.FFDISPEN.bit.FFDEN &= ~((ULLONG)D_IM_DISP_ENABLE_ON << index);
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}
#endif



ImDisp7 *im_disp7_new(void)
{
	ImDisp7* self = k_object_new_with_private(IM_TYPE_DISP7,sizeof(ImDisp7Private));
	return self;
}
