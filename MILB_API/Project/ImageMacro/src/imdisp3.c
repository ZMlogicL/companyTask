/*
 * imdisp3.c
 *
 *  Created on: 2020年8月8日
 *      Author: sns
 */
#include "imdisp.h"
#include "imdisp3.h"

#include "jdsdisp3a.h"

#include "dd_arm.h"
#include "ddim_user_custom.h"
#include <stddef.h>
#include <string.h>

K_TYPE_DEFINE_WITH_PRIVATE(ImDisp3, im_disp3)
#define IM_DISP3_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), ImDisp3Private,IM_TYPE_DISP3))


struct _ImDisp3Private
{
	int a;
};

static void im_disp3_constructor(ImDisp3 *self)
{
//	ImDisp3Private *priv = IM_DISP3_GET_PRIVATE(self);
}

static void im_disp3_destructor(ImDisp3 *self)
{
//	ImDisp3Private *priv = IM_DISP3_GET_PRIVATE(self);
}

/**
Check input data zebra warning parameter.
@param[in]	zebra			Setting of zebra warning.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
static INT32 imDispParamCheckZebra(T_IM_DISP_ZEBRA const *const zebra)
{
	INT32 ret = D_DDIM_OK;

	if (zebra->lzbwid.bit.ZBHH < 2) {
		Im_DISP_Check_Point(("CP:imDispParamCheckZebra() 1\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (zebra->lzbwid.bit.ZBHL < 2) {
		Im_DISP_Check_Point(("CP:imDispParamCheckZebra() 2\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}

	return ret;
}

/**
wait usec.
@param[in]	usec				micro second.<br>
*/
static VOID imDispWaitUsec(UINT32 usec)
{
	Im_DISP_Dsb();
	Dd_ARM_Wait_ns(usec * 1000);
}

/* Set parameter reflect timing.
*/
INT32 Im_DISP_Set_Parameter_Reflect_Timing(E_IM_DISP_SEL block, E_IM_DISP_RPGTMG timing)
{
	INT32 ret = D_DDIM_OK;

	im_disp_pclk_on(im_disp_new());
	if (IO_DISP.MAIN[block].LCH.LTRG.word == E_IM_DISP_TRG_READ_NO_ACT) {
		// Set LRPGCTL
		IO_DISP.MAIN[block].LCH.LRPGCTL.bit.RPGTMG = timing;
	}
	else {
		Ddim_Print(("E:Im_DISP_Set_Parameter_Reflect_Timing: Main layer busy\n"));
		ret = D_IM_DISP_MACRO_BUSY_NG;
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get parameter reflect timing.
*/
INT32 Im_DISP_Get_Parameter_Reflect_Timing(E_IM_DISP_SEL block, E_IM_DISP_RPGTMG *timing)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (timing == NULL) {
		Ddim_Print(("E:Im_DISP_Get_Parameter_Reflect_Timing: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get LRPGCTL
	*timing = (E_IM_DISP_RPGTMG)IO_DISP.MAIN[block].LCH.LRPGCTL.bit.RPGTMG;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set input data transfer.
*/
INT32 Im_DISP_Set_Input_Data_Transfer(E_IM_DISP_SEL block, U_IM_DISP_LIDT lidt)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (im_disp_param_check_lidt(block, lidt) != D_DDIM_OK) {
		Ddim_Print(("E:Im_DISP_Set_Input_Data_Transfer: LIDT parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Set LIDT0/LIDT1
	IO_DISP.MAIN[block].LCH.LIDT0.word = lidt.word[0];
	IO_DISP.MAIN[block].LCH.LIDT1.word = lidt.word[1];
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get input data transfer.
*/
INT32 Im_DISP_Get_Input_Data_Transfer(E_IM_DISP_SEL block, U_IM_DISP_LIDT *lidt)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (lidt == NULL) {
		Ddim_Print(("E:Im_DISP_Get_Input_Data_Transfer: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get LIDT0/LIDT1
	lidt->word[0] = IO_DISP.MAIN[block].LCH.LIDT0.word;
	lidt->word[1] = IO_DISP.MAIN[block].LCH.LIDT1.word;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set input data size of MAIN.
*/
INT32 Im_DISP_Set_Input_Size(E_IM_DISP_SEL block, U_IM_DISP_SIZE input_size)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (im_disp_param_check_lisize(input_size) != D_DDIM_OK) {
		Ddim_Print(("E:Im_DISP_Set_Input_Size: LISIZE parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Set LISIZE
	IO_DISP.MAIN[block].LCH.LISIZE.word = input_size.word;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get input data size of MAIN.
*/
INT32 Im_DISP_Get_Input_Size(E_IM_DISP_SEL block, U_IM_DISP_SIZE *input_size)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (input_size == NULL) {
		Ddim_Print(("E:Im_DISP_Get_Input_Size: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get LISIZE
	input_size->word = IO_DISP.MAIN[block].LCH.LISIZE.word;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Connect MAIN input data address with the bank index.
*/
INT32 Im_DISP_Set_Addr(E_IM_DISP_SEL block, E_IM_DISP_BANK bank_no, T_IM_DISP_IMAGE_ADDR const *const address)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (address == NULL) {
		Ddim_Print(("E:Im_DISP_Set_Addr: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Set LYSA0~3/LCSA0~3
	IO_DISP.MAIN[block].LCH.LYSA[bank_no].word = address->y_addr;
	IO_DISP.MAIN[block].LCH.LCSA[bank_no].word = address->c_addr;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get MAIN input data address of the bank index specified.
*/
INT32 Im_DISP_Get_Addr(E_IM_DISP_SEL block, E_IM_DISP_BANK bank_no, T_IM_DISP_IMAGE_ADDR *const address)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (address == NULL) {
		Ddim_Print(("E:Im_DISP_Get_Addr: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get LYSA0~3/LCSA0~3
	address->y_addr = IO_DISP.MAIN[block].LCH.LYSA[bank_no].word;
	address->c_addr = IO_DISP.MAIN[block].LCH.LCSA[bank_no].word;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set the global size.
*/
INT32 Im_DISP_Set_Lfd(E_IM_DISP_SEL block, ULONG y_hga, ULONG c_hga)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (im_disp_param_check_lfd(y_hga, c_hga) != D_DDIM_OK){
		Ddim_Print(("E:Im_DISP_Set_Lfd: LYHGA/LCHGA parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Set LYHGA/LCHGA
	IO_DISP.MAIN[block].LCH.LYHGA.word = y_hga;
	IO_DISP.MAIN[block].LCH.LCHGA.word = c_hga;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get the global size.
*/
INT32 Im_DISP_Get_Lfd(E_IM_DISP_SEL block, ULONG* y_hga, ULONG* c_hga)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ((y_hga == NULL) || (c_hga == NULL)) {
		Ddim_Print(("E:Im_DISP_Get_Lfd: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get LYHGA/LCHGA
	*y_hga = IO_DISP.MAIN[block].LCH.LYHGA.word;
	*c_hga = IO_DISP.MAIN[block].LCH.LCHGA.word;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set main bank No. to show.
*/
VOID Im_DISP_Set_Main_Bank(E_IM_DISP_SEL block, E_IM_DISP_BANK bank_no)
{
	im_disp_pclk_on(im_disp_new());
	// Set LIBCTL.IBSET
	IO_DISP.MAIN[block].LCH.LIBCTL.bit.IBSET = bank_no;
	im_disp_pclk_off(im_disp_new());
}

/* Get main bank No. to show or showing.
*/
INT32 Im_DISP_Get_Main_Bank(E_IM_DISP_SEL block, E_IM_DISP_BANK *bank_no)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (bank_no == NULL) {
		Ddim_Print(("E:Im_DISP_Get_Main_Bank: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get LIBCTL.IBSET
	*bank_no = (E_IM_DISP_BANK)IO_DISP.MAIN[block].LCH.LIBCTL.bit.IBSET;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get main bank No. to showing.
*/
INT32 Im_DISP_Get_Main_Bank_Monitor(E_IM_DISP_SEL block, E_IM_DISP_BANK *bank_no)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (bank_no == NULL) {
		Ddim_Print(("E:Im_DISP_Get_Main_Bank_Monitor: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get LIBCTL.IBMNT
	*bank_no = (E_IM_DISP_BANK)IO_DISP.MAIN[block].LCH.LIBCTL.bit.IBMNT;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set resize value.
*/
INT32 Im_DISP_Set_Resize(E_IM_DISP_SEL block, T_IM_DISP_RESIZE const *const resize)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (resize == NULL) {
		Ddim_Print(("E:Im_DISP_Set_Resize: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (im_disp_param_check_resize(resize->rsz0, resize->rsz1, resize->rsz2, resize->rsz3) != D_DDIM_OK){
		Ddim_Print(("E:Im_DISP_Set_Resize: LHRSZ0/LHRSZ1/LVRSZ parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Set LRSZ0/LRSZ1/LRSZ2/LRSZ3
	IO_DISP.MAIN[block].LCH.LRSZ0.word = resize->rsz0;
	IO_DISP.MAIN[block].LCH.LRSZ1.word = resize->rsz1.word;
	IO_DISP.MAIN[block].LCH.LRSZ2.word = resize->rsz2.word;
	IO_DISP.MAIN[block].LCH.LRSZ3.word = resize->rsz3.word;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get resize value.
*/
INT32 Im_DISP_Get_Resize(E_IM_DISP_SEL block, T_IM_DISP_RESIZE *const resize)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (resize == NULL) {
		Ddim_Print(("E:Im_DISP_Get_Resize: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get LRSZ0/LRSZ1/LRSZ2/LRSZ3
	resize->rsz0 = IO_DISP.MAIN[block].LCH.LRSZ0.word;
	resize->rsz1.word = IO_DISP.MAIN[block].LCH.LRSZ1.word;
	resize->rsz2.word = IO_DISP.MAIN[block].LCH.LRSZ2.word;
	resize->rsz3.word = IO_DISP.MAIN[block].LCH.LRSZ3.word;

	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set YHLP data.
*/
INT32 Im_DISP_Set_Yhlp(E_IM_DISP_SEL block, T_IM_DISP_YHLP const *const yhlp)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (yhlp == NULL) {
		Ddim_Print(("E:Im_DISP_Set_Yhlp: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Set LYHLPCTL/LYHLPK0/LYHLPK1/LYHLPOL/LYHLPCLR
	IO_DISP.MAIN[block].LCH.LYHLPCTL.word = yhlp->lyhlpcl.word;
	IO_DISP.MAIN[block].LCH.LYHLPK0.word = yhlp->lyhlpk.word[0];
	IO_DISP.MAIN[block].LCH.LYHLPK1.word = yhlp->lyhlpk.word[1];
	IO_DISP.MAIN[block].LCH.LYHLPOL.word = yhlp->lyhlpol.word;
	IO_DISP.MAIN[block].LCH.LYHLPCLR.dword = yhlp->lyhlpclr.dword;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get YHLP data.
*/
INT32 Im_DISP_Get_Yhlp(E_IM_DISP_SEL block, T_IM_DISP_YHLP *const yhlp)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (yhlp == NULL) {
		Ddim_Print(("E:Im_DISP_Get_Yhlp: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get LYHLPCTL/LYHLPK0/LYHLPK1/LYHLPOL/LYHLPCLR
	yhlp->lyhlpcl.word = IO_DISP.MAIN[block].LCH.LYHLPCTL.word;
	yhlp->lyhlpk.word[0] = IO_DISP.MAIN[block].LCH.LYHLPK0.word;
	yhlp->lyhlpk.word[1] = IO_DISP.MAIN[block].LCH.LYHLPK1.word;
	yhlp->lyhlpol.word = IO_DISP.MAIN[block].LCH.LYHLPOL.word;
	yhlp->lyhlpclr.dword = IO_DISP.MAIN[block].LCH.LYHLPCLR.dword;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set warning processing data.
*/
INT32 Im_DISP_Set_Warning(E_IM_DISP_SEL block, T_IM_DISP_WARNING const *const warning)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (warning == NULL) {
		Ddim_Print(("E:Im_DISP_Set_Warning: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (im_disp_param_check_warning(warning) != D_DDIM_OK) {
		Ddim_Print(("E:Im_DISP_Set_Warning: LYWTH parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Set LYWCTL/LYW0TH/LYW1TH/LYW0ST/LYW0CA/LYW0CB/LYW1ST/LYW1CA/LYW1CB/LBOST
	IO_DISP.MAIN[block].LCH.LYWCTL.word = warning->lywctl.word;
	IO_DISP.MAIN[block].LCH.LYW0TH.word = warning->lyw0th.word;
	IO_DISP.MAIN[block].LCH.LYW1TH.word = warning->lyw1th.word;
	IO_DISP.MAIN[block].LCH.LYW0ST.word = warning->lyw0st;
	IO_DISP.MAIN[block].LCH.LYW0CA.dword = warning->lyw0ca.dword;
	IO_DISP.MAIN[block].LCH.LYW0CB.dword = warning->lyw0cb.dword;
	IO_DISP.MAIN[block].LCH.LYW1ST.word = warning->lyw1st;
	IO_DISP.MAIN[block].LCH.LYW1CA.dword = warning->lyw1ca.dword;
	IO_DISP.MAIN[block].LCH.LYW1CB.dword = warning->lyw1cb.dword;
	IO_DISP.MAIN[block].LCH.LBOST.word = warning->lbost;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get warning.
*/
INT32 Im_DISP_Get_Warning(E_IM_DISP_SEL block, T_IM_DISP_WARNING *const warning)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (warning == NULL) {
		Ddim_Print(("E:Im_DISP_Get_Warning: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get LYWCTL/LYW0TH/LYW1TH/LYW0ST/LYW0CA/LYW0CB/LYW1ST/LYW1CA/LYW1CB/LBOST
	warning->lywctl.word = IO_DISP.MAIN[block].LCH.LYWCTL.word;
	warning->lyw0th.word = IO_DISP.MAIN[block].LCH.LYW0TH.word;
	warning->lyw1th.word = IO_DISP.MAIN[block].LCH.LYW1TH.word;
	warning->lyw0st = (E_IM_DISP_YWMD)IO_DISP.MAIN[block].LCH.LYW0ST.word;
	warning->lyw0ca.dword = IO_DISP.MAIN[block].LCH.LYW0CA.dword;
	warning->lyw0cb.dword = IO_DISP.MAIN[block].LCH.LYW0CB.dword;
	warning->lyw1st = (E_IM_DISP_YWMD)IO_DISP.MAIN[block].LCH.LYW1ST.word;
	warning->lyw1ca.dword = IO_DISP.MAIN[block].LCH.LYW1CA.dword;
	warning->lyw1cb.dword = IO_DISP.MAIN[block].LCH.LYW1CB.dword;
	warning->lbost = IO_DISP.MAIN[block].LCH.LBOST.word;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set blink timer control data.
*/
VOID Im_DISP_Set_Blink_Timer(E_IM_DISP_SEL block, U_IM_DISP_LBLTMR lbltmr)
{
	im_disp_pclk_on(im_disp_new());
	// Set LBLTMR
	IO_DISP.MAIN[block].LCH.LBLTMR.word = lbltmr.word;
	im_disp_pclk_off(im_disp_new());
}

/* Get blink timer control data.
*/
INT32 Im_DISP_Get_Blink_Timer(E_IM_DISP_SEL block, U_IM_DISP_LBLTMR *lbltmr)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if(lbltmr == NULL) {
		Ddim_Print(("E:Im_DISP_Get_Blink_Timer: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get LBLTMR
	lbltmr->word = IO_DISP.MAIN[block].LCH.LBLTMR.word;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set zebra warning data.
*/
INT32 Im_DISP_Set_Zebra(E_IM_DISP_SEL block, T_IM_DISP_ZEBRA const *const zebra)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (zebra == NULL) {
		Ddim_Print(("E:Im_DISP_Set_Zebra: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (imDispParamCheckZebra(zebra) != D_DDIM_OK) {
		Ddim_Print(("E:Im_DISP_Set_Zebra: LYWTH parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Set LZBWID/LZBV/LZBPT
	IO_DISP.MAIN[block].LCH.LZBWID.word = zebra->lzbwid.word;
	IO_DISP.MAIN[block].LCH.LZBV.word = zebra->lzbv.word;
	IO_DISP.MAIN[block].LCH.LZBPT.word = zebra->lzbpt.word;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get zebra warning data.
*/
INT32 Im_DISP_Get_Zebra(E_IM_DISP_SEL block, T_IM_DISP_ZEBRA *const zebra)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (zebra == NULL) {
		Ddim_Print(("E:Im_DISP_Get_Zebra: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get LZBWID/LZBV/LZBPT
	zebra->lzbwid.word = IO_DISP.MAIN[block].LCH.LZBWID.word;
	zebra->lzbv.word = IO_DISP.MAIN[block].LCH.LZBV.word;
	zebra->lzbpt.word = IO_DISP.MAIN[block].LCH.LZBPT.word;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set YCbCr->RGB matrix.
*/
INT32 Im_DISP_Set_Matrix(E_IM_DISP_SEL block, const U_IM_DISP_YR_MATRIX_COEFFICIENT matrix[D_IM_DISP_MATRIX_SIZE])
{
	INT32 loop;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (matrix == NULL) {
		Ddim_Print(("E:Im_DISP_Set_Matrix: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// YCbCr-> RGB's matrix
	for (loop = D_IM_DISP_MATRIX_SIZE - 1; loop >= 0; loop--) {
		// Set LY2R0~2
		IO_DISP.MAIN[block].LCH.LY2R[loop].dword = matrix[loop].dword;
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get YCbCr->RGB matrix.
*/
INT32 Im_DISP_Get_Matrix(E_IM_DISP_SEL block, U_IM_DISP_YR_MATRIX_COEFFICIENT matrix[D_IM_DISP_MATRIX_SIZE])
{
	INT32 loop;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (matrix == NULL) {
		Ddim_Print(("E:Im_DISP_Get_Matrix: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// YCbCr-> RGB's matrix
	for (loop = D_IM_DISP_MATRIX_SIZE - 1; loop >= 0; loop--) {
		// Set LY2R0~2
		matrix[loop].dword = IO_DISP.MAIN[block].LCH.LY2R[loop].dword;
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set gamma correct enable.
*/
INT32 Im_DISP_Set_Gamma_Enable(E_IM_DISP_SEL block, E_IM_DISP_CORRECT_SELECT set_item, T_IM_DISP_TBL_ACCESS_SET const *const correct)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (correct == NULL) {
		// Error when argument is NULL.
		Ddim_Print(("E:Im_DISP_Set_Gamma_Enable: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());

	switch (set_item) {
		// Main data input block RAM table access (LTBLASET).
		case E_IM_DISP_CORRECT_SELECT_ANTI_GAMMA:			// Anti-gamma.
			// check status.
			if ((IO_DISP.MAIN[block].LCH.LTRG.bit.TRG == E_IM_DISP_TRG_READ_NO_ACT) ||
				(correct->access == E_IM_DISP_TABLE_ACCESS_ENABLE)) {
				// Set LTBLASET.IGTAEN.
				IO_DISP.MAIN[block].LCH.LTBLASET.bit.IGTAEN = correct->access;
				imDispWaitUsec(1);		// Wait 1 usec
			}
			else {
				// not setting table access disable.
				Ddim_Print(("E:Im_DISP_Set_Gamma_Enable: not setting anti-gamma access disable\n"));
			}

			// Set LTBLASET.IGEN
			if (correct->proc) {
				// check anti-gamma table access enable.
				if (IO_DISP.MAIN[block].LCH.LTBLASET.bit.IGTAEN == E_IM_DISP_TABLE_ACCESS_ENABLE) {
					// setting enable.
					IO_DISP.MAIN[block].LCH.LTBLASET.bit.IGEN = E_IM_DISP_CORRECT_PROC_ENABLE;
				}
				else {
					// not setting enable.
					Ddim_Print(("W:Im_DISP_Set_Gamma_Enable: not setting anti-gamma correction enable\n"));
				}
			}
			else {
				// settign disable.
				IO_DISP.MAIN[block].LCH.LTBLASET.bit.IGEN = E_IM_DISP_CORRECT_PROC_DISABLE;
			}

			// Set LTBLASET.IGTSL
			IO_DISP.MAIN[block].LCH.LTBLASET.bit.IGTSL = correct->surface;
			break;
		case E_IM_DISP_CORRECT_SELECT_GAMMA_IN:				// Gamma(Main data input block).
			// check status.
			if ((IO_DISP.MAIN[block].LCH.LTRG.bit.TRG == E_IM_DISP_TRG_READ_NO_ACT) ||
				(correct->access == E_IM_DISP_TABLE_ACCESS_ENABLE)) {
				// Set LTBLASET.GTAEN.
				IO_DISP.MAIN[block].LCH.LTBLASET.bit.GTAEN = correct->access;
				imDispWaitUsec(1);		// Wait 1 usec
			}
			else {
				// not setting table access disable.
				Ddim_Print(("E:Im_DISP_Set_Gamma_Enable: not setting gamma(main data input block) access disable\n"));
			}

			// Set LTBLASET.GMEN
			if (correct->proc) {
				// check gamma table access enable.
				if (IO_DISP.MAIN[block].LCH.LTBLASET.bit.GTAEN == E_IM_DISP_TABLE_ACCESS_ENABLE) {
					// setting enable.
					IO_DISP.MAIN[block].LCH.LTBLASET.bit.GMEN = E_IM_DISP_CORRECT_PROC_ENABLE;
				}
				else {
					// not setting enable.
					Ddim_Print(("W:Im_DISP_Set_Gamma_Enable: not setting Gamma(Main data input block) correction enable\n"));
				}
			}
			else {
				// settign disable.
				IO_DISP.MAIN[block].LCH.LTBLASET.bit.GMEN = E_IM_DISP_CORRECT_PROC_DISABLE;
			}

			// Set LTBLASET.GMTSL
			IO_DISP.MAIN[block].LCH.LTBLASET.bit.GMTSL = correct->surface;
			break;

		// Data output block RAM table access (TBLASET).
		case E_IM_DISP_CORRECT_SELECT_GAMMA_OUT:			// Gamma(Data output block).
			// check status.
			if ((IO_DISP.MAIN[block].DCORE.TRG.bit.TRG == E_IM_DISP_TRG_READ_NO_ACT) ||
				(correct->access == E_IM_DISP_TABLE_ACCESS_ENABLE)) {
				// Set TBLASET.GMTAEN.
				IO_DISP.MAIN[block].DCORE.TBLASET.bit.GMTAEN = correct->access;
				imDispWaitUsec(1);		// Wait 1 usec
			}
			else {
				// not setting table access disable.
				Ddim_Print(("E:Im_DISP_Set_Gamma_Enable: not setting gamma(data output block) access disable\n"));
			}

			// Set TBLASET.GMEN
			if (correct->proc) {
				// check gamma table access enable.
				if (IO_DISP.MAIN[block].DCORE.TBLASET.bit.GMTAEN == E_IM_DISP_TABLE_ACCESS_ENABLE) {
					// setting enable.
					IO_DISP.MAIN[block].DCORE.TBLASET.bit.GMEN = E_IM_DISP_CORRECT_PROC_ENABLE;
				}
				else {
					// not setting enable.
					Ddim_Print(("W:Im_DISP_Set_Gamma_Enable: not setting Gamma(data output block) correction enable\n"));
				}
			}
			else {
				// settign disable.
				IO_DISP.MAIN[block].DCORE.TBLASET.bit.GMEN = E_IM_DISP_CORRECT_PROC_DISABLE;
			}

			// Set TBLASET.GMTSL
			IO_DISP.MAIN[block].DCORE.TBLASET.bit.GMTSL = correct->surface;
			break;
		default:											// Luminance and chroma.
			// check status.
			if ((IO_DISP.MAIN[block].DCORE.TRG.bit.TRG == E_IM_DISP_TRG_READ_NO_ACT) ||
				(correct->access == E_IM_DISP_TABLE_ACCESS_ENABLE)) {
				// Set TBLASET.YSATTA.
				IO_DISP.MAIN[block].DCORE.TBLASET.bit.YSATTA = correct->access;
				imDispWaitUsec(1);		// Wait 1 usec
			}
			else {
				// not setting table access disable.
				Ddim_Print(("E:Im_DISP_Set_Gamma_Enable: not setting luminance and chroma access disable\n"));
			}

			// Set TBLASET.YSATEN
			if (correct->proc) {
				// check Luminance and chroma table access enable.
				if (IO_DISP.MAIN[block].DCORE.TBLASET.bit.YSATTA == E_IM_DISP_TABLE_ACCESS_ENABLE) {
					// setting enable.
					IO_DISP.MAIN[block].DCORE.TBLASET.bit.YSATEN = E_IM_DISP_CORRECT_PROC_ENABLE;
				}
				else {
					// not setting enable.
					Ddim_Print(("W:Im_DISP_Set_Gamma_Enable: not setting Luminance and chroma correction enable\n"));
				}
			}
			else {
				// settign disable.
				IO_DISP.MAIN[block].DCORE.TBLASET.bit.YSATEN = E_IM_DISP_CORRECT_PROC_DISABLE;
			}

			// Set TBLASET.YSATSL
			IO_DISP.MAIN[block].DCORE.TBLASET.bit.YSATSL = correct->surface;
			break;
	}

	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get gamma correct enable.
*/
INT32 Im_DISP_Get_Gamma_Enable(E_IM_DISP_SEL block, U_IM_DISP_LTBLASET *lch_ltblaset, U_IM_DISP_TBLASET *dcore_tblaset)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ((lch_ltblaset == NULL) || (dcore_tblaset == NULL)) {
		Ddim_Print(("E:Im_DISP_Get_Gamma_Enable: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get LTBLASET.
	lch_ltblaset->word = IO_DISP.MAIN[block].LCH.LTBLASET.word;
	// Get TBLASET.
	dcore_tblaset->word = IO_DISP.MAIN[block].DCORE.TBLASET.word;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set gamma correct mode.
*/
VOID Im_DISP_Set_Gamma_Mode(E_IM_DISP_SEL block, U_IM_DISP_LGMMD lgmmd)
{
	im_disp_pclk_on(im_disp_new());

	// Set LGMMD.
	IO_DISP.MAIN[block].LCH.LGMMD.word = lgmmd.word;

	im_disp_pclk_off(im_disp_new());
}

/* Get gamma correct mode.
*/
INT32 Im_DISP_Get_Gamma_Mode(E_IM_DISP_SEL block, U_IM_DISP_LGMMD* lgmmd)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (lgmmd == NULL) {
		Ddim_Print(("E:Im_DISP_Get_Gamma_Mode: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get LGMMD.
	lgmmd->word = IO_DISP.MAIN[block].LCH.LGMMD.word;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set Alpha value.
*/
VOID Im_DISP_Set_Alpha_Value(E_IM_DISP_SEL block, U_IM_DISP_LALP lalp)
{
	im_disp_pclk_on(im_disp_new());

	// Set LALP.
	IO_DISP.MAIN[block].LCH.LALP.word = lalp.word;

	im_disp_pclk_off(im_disp_new());
}

/* Get Alpha value.
*/
INT32 Im_DISP_Get_Alpha_Value(E_IM_DISP_SEL block, U_IM_DISP_LALP *lalp)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (lalp == NULL) {
		Ddim_Print(("E:Im_DISP_Get_Alpha_Value: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get LALP.
	lalp->word = IO_DISP.MAIN[block].LCH.LALP.word;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set display position.
*/
INT32 Im_DISP_Set_Display_Position(E_IM_DISP_SEL block, U_IM_DISP_DSTA position)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (im_disp_param_check_ldsta(position) != D_DDIM_OK){
		Ddim_Print(("E:Im_DISP_Set_Display_Position: LDSTA parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Set LDSTA.
	IO_DISP.MAIN[block].LCH.LDSTA.word = position.word;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get display position.
*/
INT32 Im_DISP_Get_Display_Position(E_IM_DISP_SEL block, U_IM_DISP_DSTA *position)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if(position == NULL){
		Ddim_Print(("E:Im_DISP_Get_Display_Position: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get LDSTA.
	position->word = IO_DISP.MAIN[block].LCH.LDSTA.word;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set reverse display setting.
*/
VOID Im_DISP_Set_Reverse_Display(E_IM_DISP_SEL block, U_IM_DISP_LREVDISP reverse)
{
	im_disp_pclk_on(im_disp_new());
	// Set LREVDISP.
	IO_DISP.MAIN[block].LCH.LREVDISP.word = reverse.word;
	im_disp_pclk_off(im_disp_new());
}

/* Get reverse display setting.
*/
INT32 Im_DISP_Get_Reverse_Display(E_IM_DISP_SEL block, U_IM_DISP_LREVDISP *reverse)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (reverse == NULL) {
		Ddim_Print(("E:Im_DISP_Get_Reverse_Display: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get LREVDISP.
	reverse->word = IO_DISP.MAIN[block].LCH.LREVDISP.word;
	im_disp_pclk_off(im_disp_new());

	return ret;
}


ImDisp3 *im_disp3_new(void)
{
	ImDisp3* self = k_object_new_with_private(IM_TYPE_DISP3,sizeof(ImDisp3Private));
	return self;
}
