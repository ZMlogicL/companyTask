/*
 * imdisp4.c
 *
 *  Created on: 2020年8月8日
 *      Author: sns
 */
#include "imdisp.h"
#include "imdisp4.h"

#include "jdsdisp3a.h"

#include "dd_arm.h"
#include "ddim_user_custom.h"
#include <stddef.h>
#include <string.h>

K_TYPE_DEFINE_WITH_PRIVATE(ImDisp4, im_disp4)
#define IM_DISP4_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), ImDisp4Private,IM_TYPE_DISP4))


struct _ImDisp4Private
{
	int a;
};

static void im_disp4_constructor(ImDisp4 *self)
{
//	ImDisp4Private *priv = IM_DISP4_GET_PRIVATE(self);
}

static void im_disp4_destructor(ImDisp4 *self)
{
//	ImDisp4Private *priv = IM_DISP4_GET_PRIVATE(self);
}

/**
Check clip parameter.
@param[in]	clip_cal		clip/gain/offset data.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
static INT32 imDispParamCheckClip(T_IM_DISP_CLIP_CAL const *const clip_cal)
{
	INT32 ret = D_DDIM_OK;

	if (clip_cal->y_cal.yofs > 8191){
		Im_DISP_Check_Point(("CP:imDispParamCheckClip() 1\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}

	if ((clip_cal->cb_cal.cofs < -8192) || (clip_cal->cb_cal.cofs > 8191)){
		Im_DISP_Check_Point(("CP:imDispParamCheckClip() 2\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}

	if ((clip_cal->cr_cal.cofs < -8192) || (clip_cal->cr_cal.cofs > 8191)){
		Im_DISP_Check_Point(("CP:imDispParamCheckClip() 3\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}

	return ret;
}

/* Set display interface selection.
*/
INT32 Im_DISP_Set_Display_Interface(E_IM_DISP_SEL block, BYTE ifs)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ((ifs != D_IM_DISP_IFS_NONE) &&
		(ifs != D_IM_DISP_IFS_LCD) &&
		(ifs != D_IM_DISP_IFS_HDMI) &&
		(ifs != D_IM_DISP_IFS_MIPI)) {
		Ddim_Print(("E:Im_DISP_Set_Display_Interface: ifs parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((block == E_IM_DISP_HDMI) &&
		((ifs == D_IM_DISP_IFS_LCD) || (ifs == D_IM_DISP_IFS_MIPI))) {
		Ddim_Print(("E:Im_DISP_Set_Display_Interface: ifs parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((block == E_IM_DISP_LCD_MIPI) && (ifs == D_IM_DISP_IFS_HDMI)) {
		Ddim_Print(("E:Im_DISP_Set_Display_Interface: ifs parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	if(IO_DISP.MAIN[block].DCORE.RESET.bit.SR == D_IM_DISP_SR_RESET){
		// Set IFS.IFS
		IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = ifs;
	}
	else {
		Ddim_Print(("E:Im_DISP_Set_Display_Interface: SR was not set to 1\n"));
		ret = D_IM_DISP_STATUS_ABNORMAL;
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get display interface selection.
*/
INT32 Im_DISP_Get_Display_Interface(E_IM_DISP_SEL block, BYTE *ifs)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if(ifs == NULL) {
		Ddim_Print(("E:Im_DISP_Get_Display_Interface: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get IFS.IFS
	*ifs = IO_DISP.MAIN[block].DCORE.IFS.bit.IFS;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set external start-up mode.
*/
INT32 Im_DISP_Set_External_Startup_Mode(E_IM_DISP_SEL block, E_IM_DISP_TGKMD tgkmd)
{
	INT32 ret = D_DDIM_OK;

	im_disp_pclk_on(im_disp_new());
	if(IO_DISP.MAIN[block].DCORE.TRG.bit.TRG == E_IM_DISP_TRG_READ_NO_ACT){
		// Set TRG.TGKMD
		IO_DISP.MAIN[block].DCORE.TRG.bit.TGKMD = tgkmd;
	}
	else {
		Ddim_Print(("E:Im_DISP_Set_External_Startup_Mode: output block busy\n\n"));
		ret = D_IM_DISP_STATUS_ABNORMAL;
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get external start-up mode.
*/
INT32 Im_DISP_Get_External_Startup_Mode(E_IM_DISP_SEL block, E_IM_DISP_TGKMD* tgkmd)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if(tgkmd == NULL) {
		Ddim_Print(("E:Im_DISP_Get_External_Startup_Mode: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get TRG.TGKMD
	*tgkmd = IO_DISP.MAIN[block].DCORE.TRG.bit.TGKMD;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set external start-up operation start timing.
*/
INT32 Im_DISP_Set_External_Startup_Timing(E_IM_DISP_SEL block, ULONG tgkst)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (tgkst > 0x0FFF) {
		Ddim_Print(("E:Im_DISP_Set_External_Startup_Timing: parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	if(IO_DISP.MAIN[block].DCORE.TRG.bit.TRG == E_IM_DISP_TRG_READ_NO_ACT){
		// Set TGKST
		IO_DISP.MAIN[block].DCORE.TGKST.word = tgkst;
	}
	else {
		Ddim_Print(("E:Im_DISP_Set_External_Startup_Timing: output block busy\n\n"));
		ret = D_IM_DISP_STATUS_ABNORMAL;
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get display interface selection.
*/
INT32 Im_DISP_Get_External_Startup_Timing(E_IM_DISP_SEL block, ULONG* tgkst)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if(tgkst == NULL) {
		Ddim_Print(("E:Im_DISP_Get_External_Startup_Mode: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get TGKST
	*tgkst = IO_DISP.MAIN[block].DCORE.TGKST.bit.TGKDL;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set a flag generation timing of vertical synchronization signal.
*/
VOID Im_DISP_Set_Vsync_Int_Timing(E_IM_DISP_SEL block, E_IM_DISP_VSYNC_FLAG timing)
{
	im_disp_pclk_on(im_disp_new());
	// Set INTC
	IO_DISP.MAIN[block].DCORE.INTC.word = timing;
	im_disp_pclk_off(im_disp_new());
}

/* Get a flag generation timing of vertical synchronization signal.
*/
INT32 Im_DISP_Get_Vsync_Int_Timing(E_IM_DISP_SEL block, E_IM_DISP_VSYNC_FLAG *timing)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if(timing == NULL) {
		Ddim_Print(("E:Im_DISP_Get_Vsync_Int_Timing: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get INTC
	*timing = (E_IM_DISP_VSYNC_FLAG)IO_DISP.MAIN[block].DCORE.INTC.bit.VFTMG;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set interruption demand permission setting.
*/
INT32 Im_DISP_Set_Int(E_IM_DISP_SEL block, UINT32 interruption_select, E_IM_DISP_INTERRUPTION_STATE interruption_state)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ((interruption_select & E_IM_DISP_CORRECT_SELECT_ALL) == 0) {
		Ddim_Print(("E:Im_DISP_Set_Int: interruption_select parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Set INTE
	im_disp_set_word_bit(IO_DISP.MAIN[block].DCORE.INTE.word, interruption_select, interruption_state);
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get interruption demand permission setting.
*/
INT32 Im_DISP_Get_Int(E_IM_DISP_SEL block, UINT32* interruption_state)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if(interruption_state == NULL) {
		Ddim_Print(("E:Im_DISP_Get_Int: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get INTE
	*interruption_state = IO_DISP.MAIN[block].DCORE.INTE.word;
	im_disp_pclk_off(im_disp_new());

	return ret;
}



/* Get AXI state.
*/
INT32 Im_DISP_Get_AXI_Status(E_IM_DISP_SEL block, U_IM_DISP_AXISTS *axi_state)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (axi_state == NULL) {
		Ddim_Print(("E:Im_DISP_Get_AXI_Status: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get AXISTS
	axi_state->word = IO_DISP.MAIN[block].DCORE.AXISTS.word;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set parameter reflect timing.
*/
INT32 Im_DISP_Set_Output_Parameter_Reflect_Timing(E_IM_DISP_SEL block, E_IM_DISP_RPGTMG timing)
{
	INT32 ret = D_DDIM_OK;

	im_disp_pclk_on(im_disp_new());
	if (IO_DISP.MAIN[block].DCORE.TRG.bit.TRG == E_IM_DISP_TRG_READ_NO_ACT) {
		// Set RPGCTL
		IO_DISP.MAIN[block].DCORE.RPGCTL.bit.RPGTMG = timing;
	}
	else {
		Ddim_Print(("E:Im_DISP_Set_Output_Parameter_Reflect_Timing: Output layer busy\n"));
		ret = D_IM_DISP_MACRO_BUSY_NG;
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get parameter reflect timing.
*/
INT32 Im_DISP_Get_Output_Parameter_Reflect_Timing(E_IM_DISP_SEL block, E_IM_DISP_RPGTMG *timing)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (timing == NULL) {
		Ddim_Print(("E:Im_DISP_Get_Output_Parameter_Reflect_Timing: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get RPGCTL
	*timing = (E_IM_DISP_RPGTMG)IO_DISP.MAIN[block].DCORE.RPGCTL.bit.RPGTMG;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set parameter reflect enable.
*/
INT32 Im_DISP_Set_Output_Parameter_Reflect_Enable(E_IM_DISP_SEL block, UINT32 enable)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ((enable != D_IM_DISP_ENABLE_OFF) && (enable != D_IM_DISP_ENABLE_ON)) {
		Ddim_Print(("E:Im_DISP_Set_Output_Parameter_Reflect_Enable: enable parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Set RPGEN
	IO_DISP.MAIN[block].DCORE.RPGEN.bit.RPGEN = enable;
	Im_DISP_Dsb();
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get parameter reflect enable.
*/
INT32 Im_DISP_Get_Output_Parameter_Reflect_Enable(E_IM_DISP_SEL block, UINT32 *enable)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (enable == NULL) {
		Ddim_Print(("E:Im_DISP_Get_Output_Parameter_Reflect_Enable: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get RPGEN
	*enable = IO_DISP.MAIN[block].DCORE.RPGEN.bit.RPGEN;
	Im_DISP_Dsb();
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set transmission mode.
*/
INT32 Im_DISP_Set_TSL(E_IM_DISP_SEL block, BYTE tsl)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ((tsl != D_IM_DISP_TSL_PROGRESSIVE) && (tsl != D_IM_DISP_TSL_INTERLACE)) {
		Ddim_Print(("E:Im_DISP_Set_TSL: tsl parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	if (IO_DISP.MAIN[block].DCORE.TRG.bit.TRG == E_IM_DISP_TRG_READ_NO_ACT) {
		// Set TSL
		IO_DISP.MAIN[block].DCORE.TSL.word = tsl;
	}
	else {
		Ddim_Print(("E:Im_DISP_Set_TSL: Output layer busy\n"));
		ret = D_IM_DISP_MACRO_BUSY_NG;
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get transmission mode.
*/
INT32 Im_DISP_Get_TSL(E_IM_DISP_SEL block, BYTE *tsl)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (tsl == NULL) {
		Ddim_Print(("E:Im_DISP_Get_TSL: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get TSL
	*tsl = IO_DISP.MAIN[block].DCORE.TSL.bit.TSL;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get output size.
*/
INT32 Im_DISP_Get_Output_Size(E_IM_DISP_SEL block, ULONG *ovsize, ULONG *ohsize)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ((ovsize == NULL) || (ohsize == NULL)){
		Ddim_Print(("E:Im_DISP_Get_Output_Size: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get OVSIZE/OHSIZE
	*ovsize = IO_DISP.MAIN[block].DCORE.OVSIZE.word;
	*ohsize = IO_DISP.MAIN[block].DCORE.OHSIZE.word;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Switch force data out.
*/
VOID Im_DISP_Set_Force_Out_Data_Enable(E_IM_DISP_SEL block, E_IM_DISP_FDOEN is_enable)
{
	im_disp_pclk_on(im_disp_new());
	// Set FDOEN
	IO_DISP.MAIN[block].DCORE.FDOEN.word = is_enable;
	im_disp_pclk_off(im_disp_new());
}

/* Get force data out state.
*/
INT32  Im_DISP_Get_Force_Out_Data_Enable(E_IM_DISP_SEL block, E_IM_DISP_FDOEN *is_enable)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if(is_enable == NULL){
		Ddim_Print(("E:Im_DISP_Get_Force_Out_Data_Enable: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get FDOEN
	*is_enable = (E_IM_DISP_FDOEN)IO_DISP.MAIN[block].DCORE.FDOEN.bit.FDEN;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set force output data.
*/
VOID Im_DISP_Set_Force_Out_Data(E_IM_DISP_SEL block, U_IM_DISP_IMAGE_COLOR color_data)
{
	im_disp_pclk_on(im_disp_new());
	// Set FODATA
	IO_DISP.MAIN[block].DCORE.FODATA.word = color_data.word;
	im_disp_pclk_off(im_disp_new());
}

/* Get force output data.
*/
INT32 Im_DISP_Get_Force_Out_Data(E_IM_DISP_SEL block, U_IM_DISP_IMAGE_COLOR *color_data)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if(color_data == NULL) {
		Ddim_Print(("E:Im_DISP_Get_Force_Out_Data: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get FODATA
	color_data->word = IO_DISP.MAIN[block].DCORE.FODATA.word;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set color bar's width.
*/
INT32 Im_DISP_Set_Color_Bar_Size(E_IM_DISP_SEL block, ULONG clbhsize)
{
	INT32 ret = D_DDIM_OK;

	im_disp_pclk_on(im_disp_new());
#ifdef CO_PARAM_CHECK
	if(clbhsize * 16 < IO_DISP.MAIN[block].DCORE.OHSIZE.word) {
		Ddim_Print(("E:Im_DISP_Set_Color_Bar_Size: CLBHSIZE parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK
	// Set CLBHSIZE
	IO_DISP.MAIN[block].DCORE.CLBHSIZE.word = clbhsize;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get color bar's width.
*/
INT32 Im_DISP_Get_Color_Bar_Size(E_IM_DISP_SEL block, ULONG *clbhsize)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if(clbhsize == NULL) {
		Ddim_Print(("E:Im_DISP_Get_Color_Bar_Size: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get CLBHSIZE
	*clbhsize = IO_DISP.MAIN[block].DCORE.CLBHSIZE.word;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set color bar's color.
*/
INT32 Im_DISP_Set_Color_Bar(E_IM_DISP_SEL block, U_IM_DISP_IMAGE_COLOR const *const clbdt, UINT32 clbdt_size)
{
	INT32 ret = D_DDIM_OK;
	UINT32 loop;

#ifdef CO_PARAM_CHECK
	if (clbdt == NULL) {
		Ddim_Print(("E:Im_DISP_Set_Color_Bar: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (clbdt_size > D_IM_DISP_COLOR_BAR_COUNT) {
		Ddim_Print(("E:Im_DISP_Set_Color_Bar: clbdt_size parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	for(loop = 0; loop < clbdt_size; loop++) {
		// Set CLBDT
		IO_DISP.MAIN[block].DCORE.CLBDT[loop].word = clbdt[loop].word;
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get color bar's color.
*/
INT32 Im_DISP_Get_Color_Bar(E_IM_DISP_SEL block, U_IM_DISP_IMAGE_COLOR clbdt[D_IM_DISP_COLOR_BAR_COUNT])
{
	INT32 loop;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (clbdt == NULL) {
		Ddim_Print(("E:Im_DISP_Get_Color_Bar: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	for(loop = 0; loop < D_IM_DISP_COLOR_BAR_COUNT; loop++) {
		// Get CLBDT
		clbdt[loop].word = IO_DISP.MAIN[block].DCORE.CLBDT[loop].word;
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set blend order.
*/
INT32 Im_DISP_Set_Blend(E_IM_DISP_SEL block, U_IM_DISP_BLDCTL blend)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if(im_disp_param_check_blend(blend) != D_DDIM_OK) {
		Ddim_Print(("E:Im_DISP_Set_Blend: BLDCTL parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Set BLDCTL
	IO_DISP.MAIN[block].DCORE.BLDCTL.word = blend.word;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get blend order.
*/
INT32 Im_DISP_Get_Blend(E_IM_DISP_SEL block, U_IM_DISP_BLDCTL *blend)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (blend == NULL) {
		Ddim_Print(("E:Im_DISP_Get_Blend: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get BLDCTL
	blend->word = IO_DISP.MAIN[block].DCORE.BLDCTL.word;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set RGB->YCbCr or YCbCr->RGB matrix data.
*/
INT32 Im_DISP_Set_Output_Matrix(E_IM_DISP_SEL block, E_IM_DISP_MATRIX_KIND kind, const U_IM_DISP_YR_MATRIX_COEFFICIENT matrix[D_IM_DISP_MATRIX_SIZE])
{
	INT32 loop;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (matrix == NULL) {
		Ddim_Print(("E:Im_DISP_Set_Output_Matrix: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (kind == E_IM_DISP_MATRIX_KIND_CC) {
		Ddim_Print(("E:Im_DISP_Set_Output_Matrix: kind parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());

	if (kind == E_IM_DISP_MATRIX_KIND_R2Y) {
		for (loop = D_IM_DISP_MATRIX_SIZE - 1; loop >= 0; loop--) {
			// Set R2Y0~2
			IO_DISP.MAIN[block].DCORE.R2Y[loop].dword = matrix[loop].dword;
		}
	}
	else if (kind == E_IM_DISP_MATRIX_KIND_Y2R) {
		for (loop = D_IM_DISP_MATRIX_SIZE - 1; loop >= 0; loop--) {
			// Set Y2R0~2
			IO_DISP.MAIN[block].DCORE.Y2R[loop].dword = matrix[loop].dword;
		}
	}
	else {
		// no processing.
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get RGB to RGB matrix data.
*/
INT32 Im_DISP_Get_Output_Matrix(E_IM_DISP_SEL block, E_IM_DISP_MATRIX_KIND kind, U_IM_DISP_YR_MATRIX_COEFFICIENT matrix[D_IM_DISP_MATRIX_SIZE])
{
	INT32 ret = D_DDIM_OK;
	INT32 loop;

#ifdef CO_PARAM_CHECK
	if (matrix == NULL) {
		Ddim_Print(("E:Im_DISP_Get_Output_Matrix: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (kind == E_IM_DISP_MATRIX_KIND_CC) {
		Ddim_Print(("E:Im_DISP_Get_Output_Matrix: kind parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());

	if (kind == E_IM_DISP_MATRIX_KIND_R2Y) {
		for (loop = D_IM_DISP_MATRIX_SIZE - 1; loop >= 0; loop--) {
			// Get R2Y0~2
			matrix[loop].dword = IO_DISP.MAIN[block].DCORE.R2Y[loop].dword;
		}
	}
	else if (kind == E_IM_DISP_MATRIX_KIND_Y2R) {
		for (loop = D_IM_DISP_MATRIX_SIZE - 1; loop >= 0; loop--) {
			// Get R2Y0~2
			matrix[loop].dword = IO_DISP.MAIN[block].DCORE.Y2R[loop].dword;
		}
	}
	else {
		// no processing.
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set clip/gain/offset.
*/
INT32 Im_DISP_Set_Clip(E_IM_DISP_SEL block, T_IM_DISP_CLIP_CAL const *const clip_cal)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (clip_cal == NULL) {
		Ddim_Print(("E:Im_DISP_Set_Clip: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (imDispParamCheckClip(clip_cal) != D_DDIM_OK) {
		Ddim_Print(("E:Im_DISP_Set_Clip: YCAL/YCLIP/CBCAL/CBCLIP/CRCAL/CRCLIP parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Set YCAL/YCLIP/CBCAL/CBCLIP/CRCAL/CRCLIP
	IO_DISP.MAIN[block].DCORE.YCAL.bit.YGAIN = clip_cal->y_cal.ygain;
	IO_DISP.MAIN[block].DCORE.YCAL.bit.YOFS = clip_cal->y_cal.yofs;
	IO_DISP.MAIN[block].DCORE.YCLIP.bit.YCPH = clip_cal->y_clip.cph;
	IO_DISP.MAIN[block].DCORE.YCLIP.bit.YCPL = clip_cal->y_clip.cpl;

	IO_DISP.MAIN[block].DCORE.CBCAL.bit.CBGAIN = clip_cal->cb_cal.cgain;
	im_disp_set_reg_signed(IO_DISP.MAIN[block].DCORE.CBCAL, union io_jdsdcore_reg_cbcal, CBOFS, clip_cal->cb_cal.cofs);
	IO_DISP.MAIN[block].DCORE.CBCLIP.bit.CBCPH = clip_cal->cb_clip.cph;
	IO_DISP.MAIN[block].DCORE.CBCLIP.bit.CBCPL = clip_cal->cb_clip.cpl;

	IO_DISP.MAIN[block].DCORE.CRCAL.bit.CRGAIN = clip_cal->cr_cal.cgain;
	im_disp_set_reg_signed(IO_DISP.MAIN[block].DCORE.CRCAL, union io_jdsdcore_reg_crcal, CROFS, clip_cal->cr_cal.cofs);
	IO_DISP.MAIN[block].DCORE.CRCLIP.bit.CRCPH = clip_cal->cr_clip.cph;
	IO_DISP.MAIN[block].DCORE.CRCLIP.bit.CRCPL = clip_cal->cr_clip.cpl;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get clip/gain/offset.
*/
INT32 Im_DISP_Get_Clip(E_IM_DISP_SEL block, T_IM_DISP_CLIP_CAL *const clip_cal)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (clip_cal == NULL) {
		Ddim_Print(("E:Im_DISP_Get_Clip: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get YCAL/YCLIP/CBCAL/CBCLIP/CRCAL/CRCLIP
	clip_cal->y_cal.ygain = IO_DISP.MAIN[block].DCORE.YCAL.bit.YGAIN;
	clip_cal->y_cal.yofs = IO_DISP.MAIN[block].DCORE.YCAL.bit.YOFS;
	clip_cal->y_clip.cph = IO_DISP.MAIN[block].DCORE.YCLIP.bit.YCPH;
	clip_cal->y_clip.cpl = IO_DISP.MAIN[block].DCORE.YCLIP.bit.YCPL;

	clip_cal->cb_cal.cgain = IO_DISP.MAIN[block].DCORE.CBCAL.bit.CBGAIN;
	im_disp_get_reg_signed(clip_cal->cb_cal.cofs, IO_DISP.MAIN[block].DCORE.CBCAL, union io_jdsdcore_reg_cbcal, CBOFS);
	clip_cal->cb_clip.cph = IO_DISP.MAIN[block].DCORE.CBCLIP.bit.CBCPH;
	clip_cal->cb_clip.cpl = IO_DISP.MAIN[block].DCORE.CBCLIP.bit.CBCPL;

	clip_cal->cr_cal.cgain = IO_DISP.MAIN[block].DCORE.CRCAL.bit.CRGAIN;
	im_disp_get_reg_signed(clip_cal->cr_cal.cofs, IO_DISP.MAIN[block].DCORE.CRCAL, union io_jdsdcore_reg_crcal, CROFS);
	clip_cal->cr_clip.cph = IO_DISP.MAIN[block].DCORE.CRCLIP.bit.CRCPH;
	clip_cal->cr_clip.cpl = IO_DISP.MAIN[block].DCORE.CRCLIP.bit.CRCPL;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set RGB/YCbCr's output order.
*/
VOID Im_DISP_Set_Output_Order(E_IM_DISP_SEL block, U_IM_DISP_DOCTL0 doctl0)
{
	im_disp_pclk_on(im_disp_new());
	// Set DOCTL0
	IO_DISP.MAIN[block].DCORE.DOCTL0.word = doctl0.word;
	im_disp_pclk_off(im_disp_new());
}

/* Get RGB/YCbCr's output order.
*/
INT32 Im_DISP_Get_Output_Order(E_IM_DISP_SEL block, U_IM_DISP_DOCTL0 *doctl0)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (doctl0 == NULL) {
		Ddim_Print(("E:Im_DISP_Get_Output_Order: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get DOCTL0
	doctl0->word = IO_DISP.MAIN[block].DCORE.DOCTL0.word;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set grid data.
*/
INT32 Im_DISP_Set_Grid(E_IM_DISP_SEL block, T_IM_DISP_GRID const *const grid)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (grid == NULL) {
		Ddim_Print(("E:Im_DISP_Set_Grid: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if(im_disp_param_check_grid(grid) != D_DDIM_OK){
		Ddim_Print(("E:Im_DISP_Set_Grid: GHDSTA/GVDSTA/GLENGTH/GWIDTH/GITVL parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Set GHDSTA/GVDSTA/GLENGTH/GWIDTH/GITVL/GNUM/GDCTL
	IO_DISP.MAIN[block].DCORE.GHDSTA.word = grid->ghdsta.word;
	IO_DISP.MAIN[block].DCORE.GVDSTA.word = grid->gvdsta.word;
	IO_DISP.MAIN[block].DCORE.GLENGTH.word = grid->glength.word;
	IO_DISP.MAIN[block].DCORE.GWIDTH.word = grid->gwidth.word;
	IO_DISP.MAIN[block].DCORE.GITVL.word = grid->gitvl.word;
	IO_DISP.MAIN[block].DCORE.GNUM.word = grid->gnum.word;
	IO_DISP.MAIN[block].DCORE.GDCTL.word = grid->gdctl.word;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get grid data.
*/
INT32 Im_DISP_Get_Grid(E_IM_DISP_SEL block, T_IM_DISP_GRID *const grid)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (grid == NULL) {
		Ddim_Print(("E:Im_DISP_Get_Grid: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get GHDSTA/GVDSTA/GLENGTH/GWIDTH/GITVL/GNUM/GDCTL
	grid->ghdsta.word = IO_DISP.MAIN[block].DCORE.GHDSTA.word;
	grid->gvdsta.word = IO_DISP.MAIN[block].DCORE.GVDSTA.word;
	grid->glength.word = IO_DISP.MAIN[block].DCORE.GLENGTH.word;
	grid->gwidth.word = IO_DISP.MAIN[block].DCORE.GWIDTH.word;
	grid->gitvl.word = IO_DISP.MAIN[block].DCORE.GITVL.word;
	grid->gnum.word = IO_DISP.MAIN[block].DCORE.GNUM.word;
	grid->gdctl.word = IO_DISP.MAIN[block].DCORE.GDCTL.word;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set grid line display enable.
*/
VOID Im_DISP_Set_Grid_Enable(E_IM_DISP_SEL block, E_IM_DISP_GDISPEN gdispen)
{
	im_disp_pclk_on(im_disp_new());
	// Set GDISPEN
	IO_DISP.MAIN[block].DCORE.GDISPEN.word = gdispen;
	im_disp_pclk_off(im_disp_new());
}

/* Get grid line display enable.
*/
INT32 Im_DISP_Get_Grid_Enable(E_IM_DISP_SEL block, E_IM_DISP_GDISPEN *gdispen)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (gdispen == NULL) {
		Ddim_Print(("E:Im_DISP_Get_Grid_Enable: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get GDISPEN
	*gdispen = (E_IM_DISP_GDISPEN)IO_DISP.MAIN[block].DCORE.GDISPEN.bit.GDEN;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

ImDisp4 *im_disp4_new(void)
{
	ImDisp4* self = k_object_new_with_private(IM_TYPE_DISP4,sizeof(ImDisp4Private));
	return self;
}
