/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 梁正明
*@brief : CtImR2y36series
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimr2ytool.h"
#include "ctimr2y36series.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImR2y36series, ct_im_r2y_36series)
#define CT_IM_R2Y_36SERIES_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), \
		CtImR2y36seriesPrivate, CT_TYPE_IM_R2Y_36SERIES))


struct _CtImR2y36seriesPrivate
{

};


static void ct_im_r2y_36series_constructor(CtImR2y36series *self)
{
	//CtImR2y36seriesPrivate *priv = CT_IM_R2Y_36SERIES_GET_PRIVATE(self);
}

static void ct_im_r2y_36series_destructor(CtImR2y36series *self)
{
	//CtImR2y36seriesPrivate *priv = CT_IM_R2Y_36SERIES_GET_PRIVATE(self);
}


/*
 * PUBLIC
 */
#undef 	CtImR2y36series_FUNC_NAME
#define 	CtImR2y36series_FUNC_NAME "ct_im_r2y_36series_0: "
kint32 ct_im_r2y_36series_0(CtImR2y36series *self, kuchar pipeNo)
{
	Ddim_Print(("%s\n", CtImR2y36series_FUNC_NAME));

	return ct_im_r2y_31series_6(NULL, pipeNo);
}

#undef 	CtImR2y36series_FUNC_NAME
#define 	CtImR2y36series_FUNC_NAME "ct_im_r2y_36series_1: "
kint32 ct_im_r2y_36series_1(CtImR2y36series *self, kuchar pipeNo)
{
	Ddim_Print(("%s\n", CtImR2y36series_FUNC_NAME));

	return ct_im_r2y_31series_7(NULL, pipeNo);
}

#undef 	CtImR2y36series_FUNC_NAME
#define 	CtImR2y36series_FUNC_NAME "ct_im_r2y_36series_2: "
kint32 ct_im_r2y_36series_2(CtImR2y36series *self, kuchar pipeNo)
{
	TImR2yCtrl r2yCtrl = gctImR2yCtrlBase;
	TImR2yCtrlSdramInput r2yCtrlSdramIn = gctImR2yCtrlSdramInRgb16bit;
	TImR2yResizeRect r2yResizeRectParam = gctImR2yResizeRectParamOutYcc422;
	TImR2yInaddrInfo r2yInAddr = gctImR2yInAddrRgb16bit;
	TImR2yOutbankInfo r2yAddr0;
	TImR2yCtrlHistogram r2yHistCtrl;
	static kushort S_HIST_R2Y_Y[D_IM_R2Y_TABLE_MAX_HISTOGRAM];
	TImR2yHistogramAddr histAddr;
	TImR2yHistogramStat status;
	kuint32 loopcnt;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(("%s\n", CtImR2y36series_FUNC_NAME));
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_0] = ImR2y_ENABLE_ON;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_1] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_2] = ImR2y_ENABLE_OFF;
	memset(&r2yAddr0, '\x00', sizeof(r2yAddr0));
	r2yAddr0 = gctImR2yOutAddrYcc422;
	r2yHistCtrl.enable = ImR2y_ENABLE_ON;
	r2yHistCtrl.yywNo = D_IM_R2Y_YYW_CH_0;
	r2yHistCtrl.samplingPitch = D_IM_R2Y_HIST_PIT_2X2;
	r2yHistCtrl.histogramArea.imgTop = 0;
	r2yHistCtrl.histogramArea.imgLeft = 0;
	r2yHistCtrl.histogramArea.imgWidth = 640;
	r2yHistCtrl.histogramArea.imgLines = 480;
	histAddr.yBuf = S_HIST_R2Y_Y;
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Ctrl_ModeSDRAMInput(pipeNo, &r2yCtrlSdramIn);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_InAddr_Info(pipeNo, &r2yInAddr);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_HistogramAccessEnable(pipeNo, ImR2y_ENABLE_ON, ImR2y_ENABLE_ON);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Ctrl_Histogram(pipeNo, &r2yHistCtrl);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	Im_R2Y_Ctrl_ModeSDRAMInput(pipeNo, &r2yCtrlSdramIn);
	Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	Im_R2Y_Set_InAddr_Info(pipeNo, &r2yInAddr);
	Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
	Im_R2Y_Set_HistogramAccessEnable(pipeNo, ImR2y_ENABLE_ON, ImR2y_ENABLE_ON);
	Im_R2Y_Ctrl_Histogram(pipeNo, &r2yHistCtrl);
#endif
	ct_im_r2y_set_wb_gain_rgb(pipeNo);
	ct_im_r2y_set_gamma_on(pipeNo);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", 0));
#ifdef IM_R2Y_STATUS_PRINT
	Ddim_Print((CtImR2y36series_FUNC_NAME "Status\n"));
	Im_R2Y_Print_Status();
#endif
	ct_im_r2y_print_hist_reg();
#ifdef D_IM_R2Y_DEBUG_ON_PC
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)){
		gimR2yMacroFakeFinish[0] = 1;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)){
		gimR2yMacroFakeFinish[1] = 1;
	}
#endif
	Ddim_Print((CtImR2y36series_FUNC_NAME "R2Y Start\n"));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Start(pipeNo);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_Start(pipeNo);
#endif
#ifdef D_IM_R2Y_DEBUG_ON_PC
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)){
		gimR2yMacroFakeFinish[0] = 0;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)){
		gimR2yMacroFakeFinish[1] = 0;
	}
#endif
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)){
		flgptn |= D_IM_R2Y1_INT_FLG_YYW0_END;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)){
		flgptn |= D_IM_R2Y2_INT_FLG_YYW0_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_WaitEnd(NULL, flgptn, 60);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Stop(pipeNo);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)){
		ercd = Im_R2Y_Get_Histogram(0, &status, &histAddr);
		Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
		Ddim_Print(("yOverflow = %u\n", status.yOverflow));
		Ddim_Print(("runningStatus = %u\n", status.runningStatus));
		for(loopcnt = 0; loopcnt < D_IM_R2Y_TABLE_MAX_HISTOGRAM; loopcnt++) {
			Ddim_Print(("S_HIST_R2Y_Y[%u] = %u\n", loopcnt, S_HIST_R2Y_Y[loopcnt]));
		}
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)){
		ercd = Im_R2Y_Get_Histogram(1, &status, &histAddr);
		Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
		Ddim_Print(("yOverflow = %u\n", status.yOverflow));
		Ddim_Print(("runningStatus = %u\n", status.runningStatus));
		for(loopcnt = 0; loopcnt < D_IM_R2Y_TABLE_MAX_HISTOGRAM; loopcnt++) {
			Ddim_Print(("S_HIST_R2Y_Y[%u] = %u\n", loopcnt, S_HIST_R2Y_Y[loopcnt]));
		}
	}
#else
	Im_R2Y_WaitEnd(NULL, flgptn, 60);
	Im_R2Y_Stop(pipeNo);
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)){
		Im_R2Y_Get_Histogram(0, &status, &histAddr);
		Ddim_Print(("yOverflow = %u\n", status.yOverflow));
		Ddim_Print(("runningStatus = %u\n", status.runningStatus));
		for(loopcnt = 0; loopcnt < D_IM_R2Y_TABLE_MAX_HISTOGRAM; loopcnt++) {
			Ddim_Print(("S_HIST_R2Y_Y[%u] = %u\n", loopcnt, S_HIST_R2Y_Y[loopcnt]));
		}
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)){
		Im_R2Y_Get_Histogram(1, &status, &histAddr);
		Ddim_Print(("yOverflow = %u\n", status.yOverflow));
		Ddim_Print(("runningStatus = %u\n", status.runningStatus));
		for(loopcnt = 0; loopcnt < D_IM_R2Y_TABLE_MAX_HISTOGRAM; loopcnt++) {
			Ddim_Print(("S_HIST_R2Y_Y[%u] = %u\n", loopcnt, S_HIST_R2Y_Y[loopcnt]));
		}
	}
#endif
	ercd = Im_R2Y_Set_HistogramAccessEnable(pipeNo, ImR2y_ENABLE_OFF, ImR2y_ENABLE_OFF);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
	ct_im_r2y_print_r2y_ctrl_reg();
	ct_im_r2y_print_r2y_ctrl_modesdraminput_reg();
	ct_im_r2y_print_resize_rect_reg();
	ct_im_r2y_print_other_reg();
	ct_im_r2y_print_hist_reg();
#ifdef IM_R2Y_STATUS_PRINT
	Im_R2Y_Print_Status();
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y36series_FUNC_NAME
#define 	CtImR2y36series_FUNC_NAME "ct_im_r2y_36series_3: "
kint32 ct_im_r2y_36series_3(CtImR2y36series *self, kuchar pipeNo)
{
	TImR2yCtrl r2yCtrl = gctImR2yCtrlBase;
	TImR2yCtrlSdramInput r2yCtrlSdramIn = gctImR2yCtrlSdramInRgb16bit;
	TImR2yResizeRect r2yResizeRectParam = gctImR2yResizeRectParamOutYcc422;
	TImR2yInaddrInfo r2yInAddr = gctImR2yInAddrRgb16bit;
	TImR2yOutbankInfo r2yAddr0;
	TImR2yCtrlHistogram r2yHistCtrl;
	static kushort S_HIST_R2Y_Y[D_IM_R2Y_TABLE_MAX_HISTOGRAM];
	TImR2yHistogramAddr	histAddr;
	TImR2yHistogramStat status;
	kuint32 loopcnt;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(("%s\n", CtImR2y36series_FUNC_NAME));
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_0] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_1] = ImR2y_ENABLE_ON;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_2] = ImR2y_ENABLE_OFF;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_1].yywWidth = D_IM_R2Y_DST_IMG_PIXS_WIDTH;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_1].yywLines = D_IM_R2Y_DST_IMG_PIXS_LINES;
	memset(&r2yAddr0, '\x00', sizeof(r2yAddr0));
	r2yAddr0 = gctImR2yOutAddrYcc422;
	r2yHistCtrl.enable = ImR2y_ENABLE_ON;
	r2yHistCtrl.yywNo = D_IM_R2Y_YYW_CH_1;
	r2yHistCtrl.samplingPitch = D_IM_R2Y_HIST_PIT_4X4;
	r2yHistCtrl.histogramArea.imgTop = 0;
	r2yHistCtrl.histogramArea.imgLeft = 0;
	r2yHistCtrl.histogramArea.imgWidth = 640;
	r2yHistCtrl.histogramArea.imgLines = 480;
	histAddr.yBuf = S_HIST_R2Y_Y;
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Ctrl_ModeSDRAMInput(pipeNo, &r2yCtrlSdramIn);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_InAddr_Info(pipeNo, &r2yInAddr);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_1, &r2yAddr0);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_HistogramAccessEnable(pipeNo, ImR2y_ENABLE_ON, ImR2y_ENABLE_ON);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Ctrl_Histogram(pipeNo, &r2yHistCtrl);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	Im_R2Y_Ctrl_ModeSDRAMInput(pipeNo, &r2yCtrlSdramIn);
	Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	Im_R2Y_Set_InAddr_Info(pipeNo, &r2yInAddr);
	Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_1, &r2yAddr0);
	Im_R2Y_Set_HistogramAccessEnable(pipeNo, ImR2y_ENABLE_ON, ImR2y_ENABLE_OFF);
	Im_R2Y_Ctrl_Histogram(pipeNo, &r2yHistCtrl);
#endif
	ct_im_r2y_set_wb_gain_rgb(pipeNo);
	ct_im_r2y_set_gamma_on(pipeNo);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", 0));
#ifdef IM_R2Y_STATUS_PRINT
	Ddim_Print((CtImR2y36series_FUNC_NAME "Status\n"));
	Im_R2Y_Print_Status();
#endif
	ct_im_r2y_print_hist_reg();
#ifdef D_IM_R2Y_DEBUG_ON_PC
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)){
		gimR2yMacroFakeFinish[0] = 1;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)){
		gimR2yMacroFakeFinish[1] = 1;
	}
#endif
	Ddim_Print((CtImR2y36series_FUNC_NAME "R2Y Start\n"));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Start(pipeNo);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_Start(pipeNo);
#endif
#ifdef D_IM_R2Y_DEBUG_ON_PC
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)){
		gimR2yMacroFakeFinish[0] = 0;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)){
		gimR2yMacroFakeFinish[1] = 0;
	}
#endif
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)){
		flgptn |= D_IM_R2Y1_INT_FLG_YYW1_END;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)){
		flgptn |= D_IM_R2Y2_INT_FLG_YYW1_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_WaitEnd(NULL, flgptn, 60);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Stop(pipeNo);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)){
		ercd = Im_R2Y_Get_Histogram(0, &status, &histAddr);
		Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
		Ddim_Print(("yOverflow = %u\n", status.yOverflow));
		Ddim_Print(("runningStatus = %u\n", status.runningStatus));
		for(loopcnt = 0; loopcnt < D_IM_R2Y_TABLE_MAX_HISTOGRAM; loopcnt++) {
			Ddim_Print(("S_HIST_R2Y_Y[%u] = %u\n", loopcnt, S_HIST_R2Y_Y[loopcnt]));
		}
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)){
		ercd = Im_R2Y_Get_Histogram(1, &status, &histAddr);
		Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
		Ddim_Print(("yOverflow = %u\n", status.yOverflow));
		Ddim_Print(("runningStatus = %u\n", status.runningStatus));
		for(loopcnt = 0; loopcnt < D_IM_R2Y_TABLE_MAX_HISTOGRAM; loopcnt++) {
			Ddim_Print(("S_HIST_R2Y_Y[%u] = %u\n", loopcnt, S_HIST_R2Y_Y[loopcnt]));
		}
	}
#else
	Im_R2Y_WaitEnd(NULL, flgptn, 60);
	Im_R2Y_Stop(pipeNo);
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)){
		Im_R2Y_Get_Histogram(0, &status, &histAddr);
		Ddim_Print(("yOverflow = %u\n", status.yOverflow));
		Ddim_Print(("runningStatus = %u\n", status.runningStatus));
		for(loopcnt = 0; loopcnt < D_IM_R2Y_TABLE_MAX_HISTOGRAM; loopcnt++) {
			Ddim_Print(("S_HIST_R2Y_Y[%u] = %u\n", loopcnt, S_HIST_R2Y_Y[loopcnt]));
		}
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)){
		Im_R2Y_Get_Histogram(1, &status, &histAddr);
		Ddim_Print(("yOverflow = %u\n", status.yOverflow));
		Ddim_Print(("runningStatus = %u\n", status.runningStatus));
		for(loopcnt = 0; loopcnt < D_IM_R2Y_TABLE_MAX_HISTOGRAM; loopcnt++) {
			Ddim_Print(("S_HIST_R2Y_Y[%u] = %u\n", loopcnt, S_HIST_R2Y_Y[loopcnt]));
		}
	}
#endif
	ercd = Im_R2Y_Set_HistogramAccessEnable(pipeNo, ImR2y_ENABLE_OFF, ImR2y_ENABLE_OFF);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
	ct_im_r2y_print_r2y_ctrl_reg();
	ct_im_r2y_print_r2y_ctrl_modesdraminput_reg();
	ct_im_r2y_print_resize_rect_reg();
	ct_im_r2y_print_other_reg();
	ct_im_r2y_print_hist_reg();
#ifdef IM_R2Y_STATUS_PRINT
	Im_R2Y_Print_Status();
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y36series_FUNC_NAME
#define 	CtImR2y36series_FUNC_NAME "ct_im_r2y_36series_4: "
kint32 ct_im_r2y_36series_4(CtImR2y36series *self, kuchar pipeNo)
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

	Ddim_Print(("%s\n", CtImR2y36series_FUNC_NAME));
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_0] = ImR2y_ENABLE_ON;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_1] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_2] = ImR2y_ENABLE_OFF;
	r2yCtrl.yyw[D_IM_R2Y_YYW_CH_0].pixelAvgReductionEnable = ImR2y_ENABLE_ON;
	r2yCtrl.yyw[D_IM_R2Y_YYW_CH_0].pixelAvgReductionMode = D_IM_R2Y_RDC_MODE_DIV_2;
	memset(&r2yAddr0, '\x00', sizeof(r2yAddr0));
	r2yAddr0 = gctImR2yOutAddrYcc422;
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Ctrl_ModeSDRAMInput(pipeNo, &r2yCtrlSdramIn);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_InAddr_Info(pipeNo, &r2yInAddr);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	Im_R2Y_Ctrl_ModeSDRAMInput(pipeNo, &r2yCtrlSdramIn);
	Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	Im_R2Y_Set_InAddr_Info(pipeNo, &r2yInAddr);
	Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
#endif
	ct_im_r2y_set_wb_gain_rgb(pipeNo);
	ct_im_r2y_set_gamma_on(pipeNo);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", 0));
#ifdef IM_R2Y_STATUS_PRINT
	Ddim_Print((CtImR2y36series_FUNC_NAME "Status\n"));
	Im_R2Y_Print_Status();
#endif
#ifdef D_IM_R2Y_DEBUG_ON_PC
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)){
		gimR2yMacroFakeFinish[0] = 1;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)){
		gimR2yMacroFakeFinish[1] = 1;
	}
#endif
	Ddim_Print((CtImR2y36series_FUNC_NAME "R2Y Start\n"));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Start(pipeNo);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_Start(pipeNo);
#endif
#ifdef D_IM_R2Y_DEBUG_ON_PC
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)){
		gimR2yMacroFakeFinish[0] = 0;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)){
		gimR2yMacroFakeFinish[1] = 0;
	}
#endif
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)){
		flgptn |= D_IM_R2Y1_INT_FLG_YYW0_END;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)){
		flgptn |= D_IM_R2Y2_INT_FLG_YYW0_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_WaitEnd(NULL, flgptn, 60);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Stop(pipeNo);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_WaitEnd(NULL, flgptn, 60);
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
	ct_im_r2y_print_other_reg();
	ct_im_r2y_print_fr2y_ctrl_reg();
	ct_im_r2y_print_axi_reg();
#ifdef IM_R2Y_STATUS_PRINT
	Im_R2Y_Print_Status();
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y36series_FUNC_NAME
#define 	CtImR2y36series_FUNC_NAME "ct_im_r2y_36series_5: "
kint32 ct_im_r2y_36series_5(CtImR2y36series *self, kuchar pipeNo)
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
	Ddim_Print(("%s\n", CtImR2y36series_FUNC_NAME));
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_0] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_1] = ImR2y_ENABLE_ON;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_2] = ImR2y_ENABLE_OFF;
	r2yCtrl.yyw[D_IM_R2Y_YYW_CH_1].pixelAvgReductionEnable = ImR2y_ENABLE_ON;
	r2yCtrl.yyw[D_IM_R2Y_YYW_CH_1].pixelAvgReductionMode = D_IM_R2Y_RDC_MODE_DIV_2;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_1].yywWidth = D_IM_R2Y_DST_IMG_PIXS_WIDTH;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_1].yywLines = D_IM_R2Y_DST_IMG_PIXS_LINES;
	memset(&r2yAddr0, '\x00', sizeof(r2yAddr0));
	r2yAddr0 = gctImR2yOutAddrYcc422;
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Ctrl_ModeSDRAMInput(pipeNo, &r2yCtrlSdramIn);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_InAddr_Info(pipeNo, &r2yInAddr);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_1, &r2yAddr0);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	Im_R2Y_Ctrl_ModeSDRAMInput(pipeNo, &r2yCtrlSdramIn);
	Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	Im_R2Y_Set_InAddr_Info(pipeNo, &r2yInAddr);
	Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_1, &r2yAddr0);
#endif
	ct_im_r2y_set_wb_gain_rgb(pipeNo);
	ct_im_r2y_set_gamma_on(pipeNo);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", 0));
#ifdef IM_R2Y_STATUS_PRINT
	Ddim_Print((CtImR2y36series_FUNC_NAME "Status\n"));
	Im_R2Y_Print_Status();
#endif
#ifdef D_IM_R2Y_DEBUG_ON_PC
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)){
		gimR2yMacroFakeFinish[0] = 1;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)){
		gimR2yMacroFakeFinish[1] = 1;
	}
#endif
	Ddim_Print((CtImR2y36series_FUNC_NAME "R2Y Start\n"));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Start(pipeNo);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_Start(pipeNo);
#endif
#ifdef D_IM_R2Y_DEBUG_ON_PC
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)){
		gimR2yMacroFakeFinish[0] = 0;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)){
		gimR2yMacroFakeFinish[1] = 0;
	}
#endif
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)){
		flgptn |= D_IM_R2Y1_INT_FLG_YYW1_END;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)){
		flgptn |= D_IM_R2Y2_INT_FLG_YYW1_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_WaitEnd(NULL, flgptn, 60);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Stop(pipeNo);
	Ddim_Print((CtImR2y36series_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_WaitEnd(NULL, flgptn, 60);
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
	ct_im_r2y_print_other_reg();
	ct_im_r2y_print_fr2y_ctrl_reg();
	ct_im_r2y_print_axi_reg();
#ifdef IM_R2Y_STATUS_PRINT
	Im_R2Y_Print_Status();
#endif

	return D_DDIM_OK;
}

CtImR2y36series* ct_im_r2y_36series_new(void)
{
	CtImR2y36series* self = k_object_new_with_private(CT_TYPE_IM_R2Y_36SERIES, sizeof(CtImR2y36seriesPrivate));

	return self;
}
