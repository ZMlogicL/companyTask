/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 梁正明
*@brief : CtImR2y3series
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimr2ytool.h"
#include "imr2ystat.h"
#include "ctimr2y3series.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImR2y3series, ct_im_r2y_3series)
#define CT_IM_R2Y_3SERIES_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), \
		CtImR2y3seriesPrivate, CT_TYPE_IM_R2Y_3SERIES))


struct _CtImR2y3seriesPrivate
{

};


/*
 * IMPL
 */
static void ct_im_r2y_3series_constructor(CtImR2y3series *self)
{
	//CtImR2y3seriesPrivate *priv = CT_IM_R2Y_3SERIES_GET_PRIVATE(self);
}

static void ct_im_r2y_3series_destructor(CtImR2y3series *self)
{
	//CtImR2y3seriesPrivate *priv = CT_IM_R2Y_3SERIES_GET_PRIVATE(self);
}


/*
 * PUBLIC
 */
#undef 	CtImR2y3series_FUNC_NAME
#define 	CtImR2y3series_FUNC_NAME "ct_im_r2y_3series_1: "
kint32 ct_im_r2y_3series_1(CtImR2y3series *self, kuchar pipeNo)
{
	TImR2yCtrl r2yCtrl = gctImR2yCtrlBase;
	TImR2yCtrlSdramInput r2yCtrlSdramIn = gctImR2yCtrlSdramInRgb16bit;
	TImR2yResizeRect r2yResizeRectParam = gctImR2yResizeRectParamOutYcc422;
	TImR2yInaddrInfo r2yInAddr = gctImR2yInAddrRgb16bit;
	TImR2yOutbankInfo r2yAddr0;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(("%s\n", CtImR2y3series_FUNC_NAME));
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_0] = ImR2y_ENABLE_ON;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_1] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_2] = ImR2y_ENABLE_OFF;
	memset(&r2yAddr0, '\x00', sizeof(r2yAddr0));
	r2yAddr0 = gctImR2yOutAddrYcc422;
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Ctrl_ModeSDRAMInput(pipeNo, &r2yCtrlSdramIn);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_InAddr_Info(pipeNo, &r2yInAddr);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	Im_R2Y_Ctrl_ModeSDRAMInput(pipeNo, &r2yCtrlSdramIn);
	Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	Im_R2Y_Set_InAddr_Info(pipeNo, &r2yInAddr);
	Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
#endif
	ct_im_r2y_set_wb_gain_rgb(pipeNo);
	ct_im_r2y_set_gamma_on(pipeNo);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", 0));
#ifdef IM_R2Y_STATUS_PRINT
	Ddim_Print((CtImR2y3series_FUNC_NAME "R2Y Start Status\n"));
	Im_R2Y_Print_Status();
	Im_R2Y_Print_ClockStatus();
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif
#ifdef D_IM_R2Y_DEBUG_ON_PC
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		gimR2yMacroFakeFinish[0] = 1;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		gimR2yMacroFakeFinish[1] = 1;
	}
#endif
	Ddim_Print((CtImR2y3series_FUNC_NAME "R2Y Start\n"));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Start(pipeNo);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_Start(pipeNo);
#endif
#ifdef D_IM_R2Y_DEBUG_ON_PC
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		gimR2yMacroFakeFinish[0] = 0;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		gimR2yMacroFakeFinish[1] = 0;
	}
#endif
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		flgptn |= D_IM_R2Y1_INT_FLG_YYW0_END;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		flgptn |= D_IM_R2Y2_INT_FLG_YYW0_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_WaitEnd(NULL, flgptn, 60 * 10);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Stop(pipeNo);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_WaitEnd(NULL, flgptn, 60 * 10);
	Im_R2Y_Stop(pipeNo);
#endif
	ct_im_r2y_print_r2y_common_reg();
	ct_im_r2y_print_r2y_yyr_reg();
	ct_im_r2y_print_r2y_yyw_reg();
	ct_im_r2y_print_r2y_ctrl_reg();
	ct_im_r2y_print_r2y_ctrl_modesdraminput_reg();
	ct_im_r2y_print_r2y_ctrl_modedirect_reg();
	ct_im_r2y_print_resize_rect_reg();
	ct_im_r2y_print_trimming_reg();
	ct_im_r2y_print_color_extract_reg();
	ct_im_r2y_print_hist_reg();
	ct_im_r2y_print_post_resize_edge0_reg();
	ct_im_r2y_print_post_resize_edge1_reg();
	ct_im_r2y_print_other_reg();
	ct_im_r2y_print_fr2y_ctrl_reg();
	ct_im_r2y_print_axi_reg();
#ifdef IM_R2Y_STATUS_PRINT
	Ddim_Print((CtImR2y3series_FUNC_NAME "R2Y End Status\n"));
	Im_R2Y_Print_Status();
	Im_R2Y_Print_ClockStatus();
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y3series_FUNC_NAME
#define 	CtImR2y3series_FUNC_NAME "ct_im_r2y_3series_2: "
kint32 ct_im_r2y_3series_2(CtImR2y3series *self, kuchar pipeNo)
{
	TImR2yCtrl r2yCtrl = gctImR2yCtrlBase;
	TImR2yCtrlDirect r2y_ctrl_direct = gct_im_r2y_ctrl_direct;
	TImR2yResizeRect r2yResizeRectParam = gctImR2yResizeRectParamOutYcc422;
	TImR2yOutbankInfo r2yAddr0;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(("%s\n", CtImR2y3series_FUNC_NAME));
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_0] = ImR2y_ENABLE_ON;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_1] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_2] = ImR2y_ENABLE_OFF;
	memset(&r2yAddr0, '\x00', sizeof(r2yAddr0));
	r2yAddr0 = gctImR2yOutAddrYcc422;
	ct_im_r2y_set_b2r(pipeNo);
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Ctrl_ModeDirect(pipeNo, &r2y_ctrl_direct);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	Im_R2Y_Ctrl_ModeDirect(pipeNo, &r2y_ctrl_direct);
	Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
#endif
	ct_im_r2y_set_wb_gain_rgb(pipeNo);
	ct_im_r2y_set_gamma_on(pipeNo);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", 0));
#ifdef IM_R2Y_STATUS_PRINT
	Ddim_Print((CtImR2y3series_FUNC_NAME "R2Y Start Status\n"));
	Im_R2Y_Print_Status();
	Im_R2Y_Print_ClockStatus();
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif
#ifdef D_IM_R2Y_DEBUG_ON_PC
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		gimR2yMacroFakeFinish[0] = 1;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		gimR2yMacroFakeFinish[1] = 1;
	}
#endif
	Ddim_Print((CtImR2y3series_FUNC_NAME "R2Y Start\n"));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Start(pipeNo);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_Start(pipeNo);
#endif
#ifdef D_IM_R2Y_DEBUG_ON_PC
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		gimR2yMacroFakeFinish[0] = 0;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		gimR2yMacroFakeFinish[1] = 0;
	}
#endif
	ct_im_r2y_start_b2r(pipeNo);
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		flgptn |= D_IM_R2Y1_INT_FLG_YYW0_END;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		flgptn |= D_IM_R2Y2_INT_FLG_YYW0_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_WaitEnd(NULL, flgptn, 30);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Stop(pipeNo);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_WaitEnd(NULL, flgptn, 30);
	Im_R2Y_Stop(pipeNo);
#endif
	ct_im_r2y_waitend_stop_b2r(pipeNo);
	ct_im_r2y_print_r2y_common_reg();
	ct_im_r2y_print_r2y_yyr_reg();
	ct_im_r2y_print_r2y_yyw_reg();
	ct_im_r2y_print_r2y_ctrl_reg();
	ct_im_r2y_print_r2y_ctrl_modesdraminput_reg();
	ct_im_r2y_print_r2y_ctrl_modedirect_reg();
	ct_im_r2y_print_resize_rect_reg();
	ct_im_r2y_print_trimming_reg();
	ct_im_r2y_print_color_extract_reg();
	ct_im_r2y_print_chroma_scale_reg();
	ct_im_r2y_print_hue_scale_reg();
	ct_im_r2y_print_hist_reg();
	ct_im_r2y_print_post_resize_edge0_reg();
	ct_im_r2y_print_post_resize_edge1_reg();
	ct_im_r2y_print_other_reg();
	ct_im_r2y_print_fr2y_ctrl_reg();
	ct_im_r2y_print_axi_reg();
#ifdef IM_R2Y_STATUS_PRINT
	Ddim_Print((CtImR2y3series_FUNC_NAME "R2Y End Status\n"));
	Im_R2Y_Print_Status();
	Im_R2Y_Print_ClockStatus();
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef CtImR2y3series_FUNC_NAME
#define CtImR2y3series_FUNC_NAME "ct_im_r2y_3series_3: "
kint32 ct_im_r2y_3series_3(CtImR2y3series *self, kuchar pipeNo)
{
	TImR2yCtrl r2yCtrl = gctImR2yCtrlBase;
	TImR2yCtrlDirect r2y_ctrl_direct = gct_im_r2y_ctrl_direct;
	TImR2yResizeRect r2yResizeRectParam = gctImR2yResizeRectParamOutYcc422;
	TImR2yOutbankInfo r2yAddr0;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(("%s\n", CtImR2y3series_FUNC_NAME));
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_0] = ImR2y_ENABLE_ON;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_1] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_2] = ImR2y_ENABLE_OFF;
	memset(&r2yAddr0, '\x00', sizeof(r2yAddr0));
	r2yAddr0 = gctImR2yOutAddrYcc422;
	ct_im_r2y_set_ltm(pipeNo);
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Ctrl_ModeDirect(pipeNo, &r2y_ctrl_direct);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	Im_R2Y_Ctrl_ModeDirect(pipeNo, &r2y_ctrl_direct);
	Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
#endif
	ct_im_r2y_set_wb_gain_rgb(pipeNo);
	ct_im_r2y_set_gamma_on(pipeNo);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", 0));
#ifdef IM_R2Y_STATUS_PRINT
	Ddim_Print((CtImR2y3series_FUNC_NAME "R2Y Start Status\n"));
	Im_R2Y_Print_Status();
	Im_R2Y_Print_ClockStatus();
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif
#ifdef D_IM_R2Y_DEBUG_ON_PC
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		gimR2yMacroFakeFinish[0] = 1;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		gimR2yMacroFakeFinish[1] = 1;
	}
#endif
	Ddim_Print((CtImR2y3series_FUNC_NAME "R2Y Start\n"));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Start(pipeNo);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_Start(pipeNo);
#endif
#ifdef D_IM_R2Y_DEBUG_ON_PC
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		gimR2yMacroFakeFinish[0] = 0;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		gimR2yMacroFakeFinish[1] = 0;
	}
#endif
	ct_im_r2y_start_ltm(pipeNo);
	ct_im_r2y_waitend_stop_ltm(pipeNo);
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		flgptn |= D_IM_R2Y1_INT_FLG_YYW0_END;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		flgptn |= D_IM_R2Y2_INT_FLG_YYW0_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_WaitEnd(NULL, flgptn, 30);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Stop(pipeNo);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_WaitEnd(NULL, flgptn, 30);
	Im_R2Y_Stop(pipeNo);
#endif
	ct_im_r2y_print_r2y_common_reg();
	ct_im_r2y_print_r2y_yyr_reg();
	ct_im_r2y_print_r2y_yyw_reg();
	ct_im_r2y_print_r2y_ctrl_reg();
	ct_im_r2y_print_r2y_ctrl_modesdraminput_reg();
	ct_im_r2y_print_r2y_ctrl_modedirect_reg();
	ct_im_r2y_print_resize_rect_reg();
	ct_im_r2y_print_trimming_reg();
	ct_im_r2y_print_color_extract_reg();
	ct_im_r2y_print_chroma_scale_reg();
	ct_im_r2y_print_hue_scale_reg();
	ct_im_r2y_print_hist_reg();
	ct_im_r2y_print_post_resize_edge0_reg();
	ct_im_r2y_print_post_resize_edge1_reg();
	ct_im_r2y_print_other_reg();
	ct_im_r2y_print_fr2y_ctrl_reg();
	ct_im_r2y_print_axi_reg();
#ifdef IM_R2Y_STATUS_PRINT
	Ddim_Print((CtImR2y3series_FUNC_NAME "R2Y End Status\n"));
	Im_R2Y_Print_Status();
	Im_R2Y_Print_ClockStatus();
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y3series_FUNC_NAME
#define 	CtImR2y3series_FUNC_NAME "ct_im_r2y_3series_4: "
kint32 ct_im_r2y_3series_4(CtImR2y3series *self, kuchar pipeNo)
{
	TImR2yCtrl r2yCtrl = gctImR2yCtrlBase;
	TImR2yCtrlSdramInput r2yCtrlSdramIn = gctImR2yCtrlSdramInRgb16bit;
	TImR2yResizeRect r2yResizeRectParam = gctImR2yResizeRectParamOutYcc422;
	TImR2yInaddrInfo r2yInAddr = gctImR2yInAddrRgb16bit;
	TImR2yOutbankInfo r2yAddr0;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(("%s\n", CtImR2y3series_FUNC_NAME));
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_0] = ImR2y_ENABLE_ON;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_1] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_2] = ImR2y_ENABLE_OFF;
	r2yCtrl.line_intr[D_IM_R2Y_LINE_INT_0].level = D_IM_R2Y_DST_IMG_PIXS_LINES / 2;
	r2yCtrl.line_intr[D_IM_R2Y_LINE_INT_0].yyw_select = D_IM_R2Y_YYW_CH_0,
	r2yCtrl.line_intr[D_IM_R2Y_LINE_INT_1].level = 0;
	r2yCtrl.line_intr[D_IM_R2Y_LINE_INT_1].yyw_select = D_IM_R2Y_YYW_CH_0;
	r2yCtrl.line_intr[D_IM_R2Y_LINE_INT_2].level = 0;
	r2yCtrl.line_intr[D_IM_R2Y_LINE_INT_2].yyw_select = D_IM_R2Y_YYW_CH_0;
	r2yCtrl.r2y_user_handler = ct_im_r2y_handler;
	memset(&r2yAddr0, '\x00', sizeof(r2yAddr0));
	r2yAddr0 = gctImR2yOutAddrYcc422;
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Ctrl_ModeSDRAMInput(pipeNo, &r2yCtrlSdramIn);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_InAddr_Info(pipeNo, &r2yInAddr);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	Im_R2Y_Ctrl_ModeSDRAMInput(pipeNo, &r2yCtrlSdramIn);
	Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	Im_R2Y_Set_InAddr_Info(pipeNo, &r2yInAddr);
	Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
#endif
	ct_im_r2y_set_wb_gain_rgb(pipeNo);
	ct_im_r2y_set_gamma_on(pipeNo);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", 0));
#ifdef IM_R2Y_STATUS_PRINT
	Ddim_Print((CtImR2y3series_FUNC_NAME "Status\n"));
	Im_R2Y_Print_Status();
#endif
#ifdef D_IM_R2Y_DEBUG_ON_PC
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		gimR2yMacroFakeFinish[0] = 1;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		gimR2yMacroFakeFinish[1] = 1;
	}
#endif
	Ddim_Print((CtImR2y3series_FUNC_NAME "R2Y Start\n"));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Start(pipeNo);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_Start(pipeNo);
#endif
#ifdef D_IM_R2Y_DEBUG_ON_PC
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		gimR2yMacroFakeFinish[0] = 0;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		gimR2yMacroFakeFinish[1] = 0;
	}
#endif
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		flgptn |= D_IM_R2Y1_INT_FLG_YYW0_END;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		flgptn |= D_IM_R2Y2_INT_FLG_YYW0_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_WaitEnd(NULL, flgptn, 60);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Stop(pipeNo);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_WaitEnd(NULL, flgptn, 60);
	Im_R2Y_Stop(pipeNo);
#endif
	ct_im_r2y_print_r2y_ctrl_reg();
	ct_im_r2y_print_r2y_ctrl_modesdraminput_reg();
	ct_im_r2y_print_resize_rect_reg();
	ct_im_r2y_print_other_reg();
#ifdef IM_R2Y_STATUS_PRINT
	Im_R2Y_Print_Status();
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y3series_FUNC_NAME
#define 	CtImR2y3series_FUNC_NAME "ct_im_r2y_3series_5: "
kint32 ct_im_r2y_3series_5(CtImR2y3series *self, kuchar pipeNo)
{
	TImR2yCtrl r2yCtrl = gctImR2yCtrlBase;
	TImR2yCtrlSdramInput r2yCtrlSdramIn = gctImR2yCtrlSdramInRgb16bit;
	TImR2yResizeRect r2yResizeRectParam = gctImR2yResizeRectParamOutYcc422;
	TImR2yInaddrInfo r2yInAddr = gctImR2yInAddrRgb16bit;
	TImR2yOutbankInfo r2yAddr0;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(("%s\n", CtImR2y3series_FUNC_NAME));
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_0] = ImR2y_ENABLE_ON;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_1] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_2] = ImR2y_ENABLE_OFF;
	r2yCtrl.line_intr[D_IM_R2Y_LINE_INT_0].level = 0;
	r2yCtrl.line_intr[D_IM_R2Y_LINE_INT_0].yyw_select = D_IM_R2Y_YYW_CH_0,
	r2yCtrl.line_intr[D_IM_R2Y_LINE_INT_1].level = D_IM_R2Y_DST_IMG_PIXS_LINES / 2;
	r2yCtrl.line_intr[D_IM_R2Y_LINE_INT_1].yyw_select = D_IM_R2Y_YYW_CH_0;
	r2yCtrl.line_intr[D_IM_R2Y_LINE_INT_2].level = 0;
	r2yCtrl.line_intr[D_IM_R2Y_LINE_INT_2].yyw_select = D_IM_R2Y_YYW_CH_0;
	r2yCtrl.r2y_user_handler = ct_im_r2y_handler;
	memset(&r2yAddr0, '\x00', sizeof(r2yAddr0));
	r2yAddr0 = gctImR2yOutAddrYcc422;
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Ctrl_ModeSDRAMInput(pipeNo, &r2yCtrlSdramIn);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_InAddr_Info(pipeNo, &r2yInAddr);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	Im_R2Y_Ctrl_ModeSDRAMInput(pipeNo, &r2yCtrlSdramIn);
	Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	Im_R2Y_Set_InAddr_Info(pipeNo, &r2yInAddr);
	Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
#endif
	ct_im_r2y_set_wb_gain_rgb(pipeNo);
	ct_im_r2y_set_gamma_on(pipeNo);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", 0));
#ifdef IM_R2Y_STATUS_PRINT
	Ddim_Print((CtImR2y3series_FUNC_NAME "Status\n"));
	Im_R2Y_Print_Status();
#endif
#ifdef D_IM_R2Y_DEBUG_ON_PC
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		gimR2yMacroFakeFinish[0] = 1;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		gimR2yMacroFakeFinish[1] = 1;
	}
#endif
	Ddim_Print((CtImR2y3series_FUNC_NAME "R2Y Start\n"));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Start(pipeNo);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_Start(pipeNo);
#endif
#ifdef D_IM_R2Y_DEBUG_ON_PC
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		gimR2yMacroFakeFinish[0] = 0;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		gimR2yMacroFakeFinish[1] = 0;
	}
#endif
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		flgptn |= D_IM_R2Y1_INT_FLG_YYW0_END;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		flgptn |= D_IM_R2Y2_INT_FLG_YYW0_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_WaitEnd(NULL, flgptn, 60);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Stop(pipeNo);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_WaitEnd(NULL, flgptn, 60);
	Im_R2Y_Stop(pipeNo);
#endif
	ct_im_r2y_print_r2y_ctrl_reg();
	ct_im_r2y_print_r2y_ctrl_modesdraminput_reg();
	ct_im_r2y_print_resize_rect_reg();
	ct_im_r2y_print_other_reg();
#ifdef IM_R2Y_STATUS_PRINT
	Im_R2Y_Print_Status();
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y3series_FUNC_NAME
#define 	CtImR2y3series_FUNC_NAME "ct_im_r2y_3series_6: "
kint32 ct_im_r2y_3series_6(CtImR2y3series *self, kuchar pipeNo)
{
	TImR2yCtrl r2yCtrl = gctImR2yCtrlBase;
	TImR2yCtrlSdramInput r2yCtrlSdramIn = gctImR2yCtrlSdramInRgb16bit;
	TImR2yResizeRect r2yResizeRectParam = gctImR2yResizeRectParamOutYcc422;
	TImR2yInaddrInfo r2yInAddr = gctImR2yInAddrRgb16bit;
	TImR2yOutbankInfo r2yAddr0;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(("%s\n", CtImR2y3series_FUNC_NAME));
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_0] = ImR2y_ENABLE_ON;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_1] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_2] = ImR2y_ENABLE_OFF;
	r2yCtrl.line_intr[D_IM_R2Y_LINE_INT_0].level = 0;
	r2yCtrl.line_intr[D_IM_R2Y_LINE_INT_0].yyw_select = D_IM_R2Y_YYW_CH_0,
	r2yCtrl.line_intr[D_IM_R2Y_LINE_INT_1].level = 0;
	r2yCtrl.line_intr[D_IM_R2Y_LINE_INT_1].yyw_select = D_IM_R2Y_YYW_CH_0;
	r2yCtrl.line_intr[D_IM_R2Y_LINE_INT_2].level = D_IM_R2Y_DST_IMG_PIXS_LINES / 2;
	r2yCtrl.line_intr[D_IM_R2Y_LINE_INT_2].yyw_select = D_IM_R2Y_YYW_CH_0;
	r2yCtrl.r2y_user_handler = ct_im_r2y_handler;
	memset(&r2yAddr0, '\x00', sizeof(r2yAddr0));
	r2yAddr0 = gctImR2yOutAddrYcc422;
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Ctrl_ModeSDRAMInput(pipeNo, &r2yCtrlSdramIn);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_InAddr_Info(pipeNo, &r2yInAddr);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	Im_R2Y_Ctrl_ModeSDRAMInput(pipeNo, &r2yCtrlSdramIn);
	Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	Im_R2Y_Set_InAddr_Info(pipeNo, &r2yInAddr);
	Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
#endif
	ct_im_r2y_set_wb_gain_rgb(pipeNo);
	ct_im_r2y_set_gamma_on(pipeNo);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", 0));
#ifdef IM_R2Y_STATUS_PRINT
	Ddim_Print((CtImR2y3series_FUNC_NAME "Status\n"));
	Im_R2Y_Print_Status();
#endif
#ifdef D_IM_R2Y_DEBUG_ON_PC
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		gimR2yMacroFakeFinish[0] = 1;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		gimR2yMacroFakeFinish[1] = 1;
	}
#endif
	Ddim_Print((CtImR2y3series_FUNC_NAME "R2Y Start\n"));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Start(pipeNo);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_Start(pipeNo);
#endif
#ifdef D_IM_R2Y_DEBUG_ON_PC
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		gimR2yMacroFakeFinish[0] = 0;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		gimR2yMacroFakeFinish[1] = 0;
	}
#endif
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		flgptn |= D_IM_R2Y1_INT_FLG_YYW0_END;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		flgptn |= D_IM_R2Y2_INT_FLG_YYW0_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_WaitEnd(NULL, flgptn, 60);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Stop(pipeNo);
	Ddim_Print((CtImR2y3series_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_WaitEnd(NULL, flgptn, 60);
	Im_R2Y_Stop(pipeNo);
#endif
	ct_im_r2y_print_r2y_ctrl_reg();
	ct_im_r2y_print_r2y_ctrl_modesdraminput_reg();
	ct_im_r2y_print_resize_rect_reg();
	ct_im_r2y_print_other_reg();
#ifdef IM_R2Y_STATUS_PRINT
	Im_R2Y_Print_Status();
#endif

	return D_DDIM_OK;
}

CtImR2y3series *ct_im_r2y_3series_new(void)
{
	CtImR2y3series *self = k_object_new_with_private(CT_TYPE_IM_R2Y_3SERIES, sizeof(CtImR2y3seriesPrivate));

	return self;
}
