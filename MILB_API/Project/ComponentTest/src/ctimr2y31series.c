/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 梁正明
*@brief : CtImR2y31series
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimr2ytool.h"
#include "ctimr2y31series.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImR2y31series, ct_im_r2y_31series)
#define CT_IM_R2Y_31SERIES_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), \
		CtImR2y31seriesPrivate, CT_TYPE_IM_R2Y_31SERIES))


struct _CtImR2y31seriesPrivate
{

};


/*
 * IMPL
 */
static void ct_im_r2y_31series_constructor(CtImR2y31series *self)
{
	//CtImR2y31seriesPrivate *priv = CT_IM_R2Y_31SERIES_GET_PRIVATE(self);
}

static void ct_im_r2y_31series_destructor(CtImR2y31series *self)
{
	//CtImR2y31seriesPrivate *priv = CT_IM_R2Y_31SERIES_GET_PRIVATE(self);
}


/*
 * PUBLIC
 */
#undef 	CtImR2y31series_FUNC_NAME
#define 	CtImR2y31series_FUNC_NAME "ct_im_r2y_31series_2: "
kint32 ct_im_r2y_31series_2(CtImR2y31series *self, kuchar pipeNo)
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

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y31series_FUNC_NAME));
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_0] = ImR2y_ENABLE_ON;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_1] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_2] = ImR2y_ENABLE_OFF;
	r2yResizeRectParam.inputSize.imgTop = D_IM_R2Y_SRC_IMG_PIXS_LINES / 4;
	r2yResizeRectParam.inputSize.imgLeft = D_IM_R2Y_SRC_IMG_PIXS_WIDTH / 4;
	r2yResizeRectParam.inputSize.imgWidth = D_IM_R2Y_SRC_IMG_PIXS_WIDTH / 2;
	r2yResizeRectParam.inputSize.imgLines = D_IM_R2Y_SRC_IMG_PIXS_LINES / 2;
	memset(&r2yAddr0, '\x00', sizeof(r2yAddr0));
	r2yAddr0 = gctImR2yOutAddrYcc422;
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Ctrl_ModeSDRAMInput(pipeNo, &r2yCtrlSdramIn);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_InAddr_Info(pipeNo, &r2yInAddr);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	Im_R2Y_Ctrl_ModeSDRAMInput(pipeNo, &r2yCtrlSdramIn);
	Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	Im_R2Y_Set_InAddr_Info(pipeNo, &r2yInAddr);
	Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
#endif
	ct_im_r2y_set_wb_gain_rgb(pipeNo);
	ct_im_r2y_set_gamma_on(pipeNo);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", 0));
#ifdef IM_R2Y_STATUS_PRINT
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "Status\n"));
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
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "R2Y Start\n"));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Start(pipeNo);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
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
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Stop(pipeNo);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
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

#undef 	CtImR2y31series_FUNC_NAME
#define 	CtImR2y31series_FUNC_NAME "ct_im_r2y_31series_3: "
kint32 ct_im_r2y_31series_3(CtImR2y31series *self, kuchar pipeNo)
{
	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y31series_FUNC_NAME));

	return ct_im_r2y_31series_2(NULL, pipeNo);
}

#undef 	CtImR2y31series_FUNC_NAME
#define 	CtImR2y31series_FUNC_NAME "ct_im_r2y_31series_4: "
kint32 ct_im_r2y_31series_4(CtImR2y31series *self, kuchar pipeNo)
{
	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y31series_FUNC_NAME));

	return ct_im_r2y_31series_2(NULL, pipeNo);
}

#undef 	CtImR2y31series_FUNC_NAME
#define 	CtImR2y31series_FUNC_NAME "ct_im_r2y_31series_5: "
kint32 ct_im_r2y_31series_5(CtImR2y31series *self, kuchar pipeNo)
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

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y31series_FUNC_NAME));
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_0] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_1] = ImR2y_ENABLE_ON;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_2] = ImR2y_ENABLE_OFF;
	r2yResizeRectParam.inputSize.imgTop = D_IM_R2Y_SRC_IMG_PIXS_LINES / 4;
	r2yResizeRectParam.inputSize.imgLeft = D_IM_R2Y_SRC_IMG_PIXS_WIDTH / 4;
	r2yResizeRectParam.inputSize.imgWidth = D_IM_R2Y_SRC_IMG_PIXS_WIDTH / 2;
	r2yResizeRectParam.inputSize.imgLines = D_IM_R2Y_SRC_IMG_PIXS_LINES / 2;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_1].yywWidth = D_IM_R2Y_DST_IMG_PIXS_WIDTH / 2;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_1].yywLines = D_IM_R2Y_DST_IMG_PIXS_LINES / 2;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_1].outputGlobalW[D_IM_R2Y_PORT_Y] =
			D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC422_Y;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_1].outputGlobalW[D_IM_R2Y_PORT_CB] =
			D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC422_C;
	memset(&r2yAddr0, '\x00', sizeof(r2yAddr0));
	r2yAddr0 = gctImR2yOutAddrYcc422;
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Ctrl_ModeSDRAMInput(pipeNo, &r2yCtrlSdramIn);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_InAddr_Info(pipeNo, &r2yInAddr);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_1, &r2yAddr0);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	Im_R2Y_Ctrl_ModeSDRAMInput(pipeNo, &r2yCtrlSdramIn);
	Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	Im_R2Y_Set_InAddr_Info(pipeNo, &r2yInAddr);
	Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_1, &r2yAddr0);
#endif
	ct_im_r2y_set_wb_gain_rgb(pipeNo);
	ct_im_r2y_set_gamma_on(pipeNo);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", 0));
#ifdef IM_R2Y_STATUS_PRINT
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "Status\n"));
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
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "R2Y Start\n"));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Start(pipeNo);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
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
		flgptn |= D_IM_R2Y1_INT_FLG_YYW1_END;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		flgptn |= D_IM_R2Y2_INT_FLG_YYW1_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_WaitEnd(NULL, flgptn, 60);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Stop(pipeNo);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
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

#undef 	CtImR2y31series_FUNC_NAME
#define 	CtImR2y31series_FUNC_NAME "ct_im_r2y_31series_6: "
kint32 ct_im_r2y_31series_6(CtImR2y31series *self, kuchar pipeNo)
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

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y31series_FUNC_NAME));
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_0] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_1] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_2] = ImR2y_ENABLE_ON;
	r2yResizeRectParam.inputSize.imgTop = D_IM_R2Y_SRC_IMG_PIXS_LINES / 4;
	r2yResizeRectParam.inputSize.imgLeft = D_IM_R2Y_SRC_IMG_PIXS_WIDTH / 4;
	r2yResizeRectParam.inputSize.imgWidth = D_IM_R2Y_SRC_IMG_PIXS_WIDTH / 2;
	r2yResizeRectParam.inputSize.imgLines = D_IM_R2Y_SRC_IMG_PIXS_LINES / 2;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_2].yywWidth
		= D_IM_R2Y_DST_IMG_PIXS_WIDTH / 4;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_2].yywLines = D_IM_R2Y_DST_IMG_PIXS_LINES / 4;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_2].outputGlobalW[D_IM_R2Y_PORT_Y]
	    = D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC422_Y;
	memset(&r2yAddr0, '\x00', sizeof(r2yAddr0));
	r2yAddr0 = gctImR2yOutAddrYcc422;
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Ctrl_ModeSDRAMInput(pipeNo, &r2yCtrlSdramIn);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_InAddr_Info(pipeNo, &r2yInAddr);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_2, &r2yAddr0);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	Im_R2Y_Ctrl_ModeSDRAMInput(pipeNo, &r2yCtrlSdramIn);
	Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	Im_R2Y_Set_InAddr_Info(pipeNo, &r2yInAddr);
	Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_2, &r2yAddr0);
#endif
	ct_im_r2y_set_wb_gain_rgb(pipeNo);
	ct_im_r2y_set_gamma_on(pipeNo);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", 0));
#ifdef IM_R2Y_STATUS_PRINT
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "Status\n"));
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
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "R2Y Start\n"));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Start(pipeNo);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
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
		flgptn |= D_IM_R2Y1_INT_FLG_YYW2_END;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		flgptn |= D_IM_R2Y2_INT_FLG_YYW2_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_WaitEnd(NULL, flgptn, 60);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_R2Y_Stop(pipeNo);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
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

#undef 	CtImR2y31series_FUNC_NAME
#define 	CtImR2y31series_FUNC_NAME "ct_im_r2y_31series_7: "
kint32 ct_im_r2y_31series_7(CtImR2y31series *self, kuchar pipeNo)
{
	TImR2yCtrl r2yCtrl = gctImR2yCtrlBase;
	TImR2yCtrlSdramInput r2yCtrlSdramIn = gctImR2yCtrlSdramInRgb16bit;
	TImR2yResizeRect r2yResizeRectParam = gctImR2yResizeRectParamOutYcc422;
	TImR2yInaddrInfo r2yInAddr = gctImR2yInAddrRgb16bit;
	//TImR2yCtrlTrimming TImR2yCtrlTrimming
	TImR2yCtrlTrimming r2yCtrlTrimming;
	TImR2yOutbankInfo r2yAddr0;
	TImR2yOutbankInfo r2yAddr0a;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y31series_FUNC_NAME));
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_0] = ImR2y_ENABLE_ON;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_1] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_2] = ImR2y_ENABLE_OFF;
	r2yCtrl.outputMode0a = D_IM_R2Y_YYW0A_OUTPUT_MODE_DIV_32_SP; //outputMode0a outputMode0a
	r2yCtrlSdramIn.inputGlobal = 1280 * 2; //inputGlobal  inputGlobal
	r2yResizeRectParam.inputSize.imgWidth = 1280;
	r2yResizeRectParam.inputSize.imgLines = 960;
	r2yInAddr.rgb.addrR = (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_U16_R_ADDR_TOP;
	r2yInAddr.rgb.addrG = (VOID*)(r2yInAddr.rgb.addrR + (r2yResizeRectParam.inputSize.imgWidth //addrG addrG
			* r2yResizeRectParam.inputSize.imgLines * 2));
	r2yInAddr.rgb.addrB = (VOID*)(r2yInAddr.rgb.addrG + (r2yResizeRectParam.inputSize.imgWidth //addrB addrB
			* r2yResizeRectParam.inputSize.imgLines * 2));
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].yywWidth = 1280;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].yywLines = 960;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].outputGlobalW[D_IM_R2Y_PORT_Y] = 1280;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].outputGlobalW[D_IM_R2Y_PORT_CBCR] = 1280;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0A].outputGlobalW[D_IM_R2Y_PORT_Y] = 1280 / 32;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0A].outputGlobalW[D_IM_R2Y_PORT_CBCR] = 1280 / 32;
	r2yCtrlTrimming.trimmingEnable = ImR2y_ENABLE_ON; //trimmingEnable trimmingEnable
	r2yCtrlTrimming.trimWindow.imgLeft = 0;
	r2yCtrlTrimming.trimWindow.imgTop = 0;
	r2yCtrlTrimming.trimWindow.imgWidth = r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].yywWidth;
	r2yCtrlTrimming.trimWindow.imgLines = r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].yywLines;
	memset(&r2yAddr0, '\x00', sizeof(r2yAddr0));
	memset(&r2yAddr0a, '\x00', sizeof(r2yAddr0));
	r2yAddr0 = r2yAddr0a = gctImR2yOutAddrYcc422;
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_0].ycc.addrY = (VOID*)(r2yInAddr.rgb.addrB  //outputAddr outputAddr addrY addrY addrB addrB
		+ (r2yResizeRectParam.inputSize.imgWidth * r2yResizeRectParam.inputSize.imgLines * 2));
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_0].ycc.addrCb  //addrCb addrCb
		= (VOID*)(((ULONG)r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_0].ycc.addrY)
		+ (r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].outputGlobalW[D_IM_R2Y_PORT_Y]
		* (r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].yywLines)));
	r2yAddr0a.outputAddr[D_IM_R2Y_YYW_BANK_0].ycc.addrY
		= (VOID*)(((ULONG)r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_0].ycc.addrCb)
		+ (r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].outputGlobalW[D_IM_R2Y_PORT_CBCR]
		* (r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].yywLines)));
	r2yAddr0a.outputAddr[D_IM_R2Y_YYW_BANK_0].ycc.addrCb
		= (VOID*)(((ULONG)r2yAddr0a.outputAddr[D_IM_R2Y_YYW_BANK_0].ycc.addrY)
		+ (r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0A].outputGlobalW[D_IM_R2Y_PORT_Y]
		* (r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].yywLines / 32)));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Ctrl_ModeSDRAMInput(pipeNo, &r2yCtrlSdramIn);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Ctrl_Trimming(pipeNo, D_IM_R2Y_YYW_CH_0, &r2yCtrlTrimming);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_InAddr_Info(pipeNo, &r2yInAddr);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_0A, &r2yAddr0a);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	Im_R2Y_Ctrl_ModeSDRAMInput(pipeNo, &r2yCtrlSdramIn);
	Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	Im_R2Y_Ctrl_Trimming(pipeNo, D_IM_R2Y_YYW_CH_0, &r2yCtrlTrimming);
	Im_R2Y_Set_InAddr_Info(pipeNo, &r2yInAddr);
	Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
	Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_0A, &r2yAddr0a);
#endif
	ct_im_r2y_set_wb_gain_rgb(pipeNo);
	ct_im_r2y_set_gamma_on(pipeNo);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", 0));
#ifdef IM_R2Y_STATUS_PRINT
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "Status\n"));
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
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "R2Y Start\n"));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Start(pipeNo);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
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
		flgptn |= D_IM_R2Y1_INT_FLG_YYW0A_END;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		flgptn |= D_IM_R2Y2_INT_FLG_YYW0_END;
		flgptn |= D_IM_R2Y2_INT_FLG_YYW0A_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_WaitEnd(NULL, flgptn, 60);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Stop(pipeNo);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_WaitEnd(NULL, flgptn, 60);
	Im_R2Y_Stop(pipeNo);
#endif
	ct_im_r2y_print_r2y_ctrl_reg();
	ct_im_r2y_print_r2y_ctrl_modesdraminput_reg();
	ct_im_r2y_print_resize_rect_reg();
	ct_im_r2y_print_trimming_reg();
	ct_im_r2y_print_other_reg();

#ifdef IM_R2Y_STATUS_PRINT
	Im_R2Y_Print_Status();
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y31series_FUNC_NAME
#define 	CtImR2y31series_FUNC_NAME "ct_im_r2y_31series_8: "
kint32 ct_im_r2y_31series_8(CtImR2y31series *self, kuchar pipeNo)
{
	TImR2yCtrl r2yCtrl = gctImR2yCtrlBase;
	TImR2yCtrlSdramInput r2yCtrlSdramIn = gctImR2yCtrlSdramInRgb16bit;
	TImR2yResizeRect r2yResizeRectParam = gctImR2yResizeRectParamOutYcc422;
	TImR2yInaddrInfo r2yInAddr = gctImR2yInAddrRgb16bit;
	TImR2yCtrlTrimming r2yCtrlTrimming;
	TImR2yOutbankInfo r2yAddr0;
	TImR2yOutbankInfo r2yAddr0a;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y31series_FUNC_NAME));
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_0] = ImR2y_ENABLE_ON;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_1] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_2] = ImR2y_ENABLE_OFF;
	r2yCtrl.outputMode0a = D_IM_R2Y_YYW0A_OUTPUT_MODE_DIV_8_Y;
	r2yCtrlTrimming.trimmingEnable = ImR2y_ENABLE_ON;
	r2yCtrlTrimming.trimWindow.imgLeft = 0;
	r2yCtrlTrimming.trimWindow.imgTop = 0;
	r2yCtrlTrimming.trimWindow.imgWidth = r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].yywWidth;
	r2yCtrlTrimming.trimWindow.imgLines = r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].yywLines;
	memset(&r2yAddr0, '\x00', sizeof(r2yAddr0));
	memset(&r2yAddr0a, '\x00', sizeof(r2yAddr0));
	r2yAddr0 = r2yAddr0a = gctImR2yOutAddrYcc422;
	r2yAddr0a.outputAddr[D_IM_R2Y_YYW_BANK_0].ycc.addrY
		= (VOID*)(((ULONG)r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_0].ycc.addrCb)
	    + (r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].outputGlobalW[D_IM_R2Y_PORT_CBCR]
		* (r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].yywLines)));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Ctrl_ModeSDRAMInput(pipeNo, &r2yCtrlSdramIn);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Ctrl_Trimming(pipeNo, D_IM_R2Y_YYW_CH_0, &r2yCtrlTrimming);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_InAddr_Info(pipeNo, &r2yInAddr);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_0A, &r2yAddr0a);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	Im_R2Y_Ctrl_ModeSDRAMInput(pipeNo, &r2yCtrlSdramIn);
	Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	Im_R2Y_Ctrl_Trimming(pipeNo, D_IM_R2Y_YYW_CH_0, &r2yCtrlTrimming);
	Im_R2Y_Set_InAddr_Info(pipeNo, &r2yInAddr);
	Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
	Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_0A, &r2yAddr0a);
#endif
	ct_im_r2y_set_wb_gain_rgb(pipeNo);
	ct_im_r2y_set_gamma_on(pipeNo);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", 0));
#ifdef IM_R2Y_STATUS_PRINT
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "Status\n"));
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
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "R2Y Start\n"));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Start(pipeNo);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
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
		flgptn |= D_IM_R2Y1_INT_FLG_YYW0A_END;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		flgptn |= D_IM_R2Y2_INT_FLG_YYW0_END;
		flgptn |= D_IM_R2Y2_INT_FLG_YYW0A_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_WaitEnd(NULL, flgptn, 60);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Stop(pipeNo);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_WaitEnd(NULL, flgptn, 60);
	Im_R2Y_Stop(pipeNo);
#endif
	ct_im_r2y_print_r2y_ctrl_reg();
	ct_im_r2y_print_r2y_ctrl_modesdraminput_reg();
	ct_im_r2y_print_resize_rect_reg();
	ct_im_r2y_print_trimming_reg();
	ct_im_r2y_print_other_reg();
#ifdef IM_R2Y_STATUS_PRINT
	Im_R2Y_Print_Status();
#endif

	return D_DDIM_OK;
}

#undef CtImR2y31series_FUNC_NAME
#define CtImR2y31series_FUNC_NAME "ct_im_r2y_31series_9: "
kint32 ct_im_r2y_31series_9(CtImR2y31series *self, kuchar pipeNo)
{
	TImR2yCtrl r2yCtrl = gctImR2yCtrlBase;
	TImR2yCtrlSdramInput r2yCtrlSdramIn = gctImR2yCtrlSdramInRgb8bit;
	TImR2yResizeRect r2yResizeRectParam = gctImR2yResizeRectParamOutYcc422;
	TImR2yInaddrInfo r2yInAddr = gctImR2yInAddrRgb8bit;
	TImR2yOutbankInfo r2yAddr0;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y31series_FUNC_NAME));
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_0] = ImR2y_ENABLE_ON;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_1] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_2] = ImR2y_ENABLE_OFF;
	r2yResizeRectParam.inputSize.imgTop = D_IM_R2Y_SRC_IMG_PIXS_LINES / 4;
	r2yResizeRectParam.inputSize.imgLeft = D_IM_R2Y_SRC_IMG_PIXS_WIDTH / 4;
	r2yResizeRectParam.inputSize.imgWidth = D_IM_R2Y_SRC_IMG_PIXS_WIDTH / 2;
	r2yResizeRectParam.inputSize.imgLines = D_IM_R2Y_SRC_IMG_PIXS_LINES / 2;
	r2yCtrlSdramIn.rgbLeftShift = D_IM_R2Y_STL_RGB_LEFT_SHIFT_4BIT;
	r2yCtrlSdramIn.rgbDekneeEnable = ImR2y_ENABLE_OFF;
	memset(&r2yAddr0, '\x00', sizeof(r2yAddr0));
	r2yAddr0 = gctImR2yOutAddrYcc422;
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Ctrl_ModeSDRAMInput(pipeNo, &r2yCtrlSdramIn);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_InAddr_Info(pipeNo, &r2yInAddr);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	Im_R2Y_Ctrl_ModeSDRAMInput(pipeNo, &r2yCtrlSdramIn);
	Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	Im_R2Y_Set_InAddr_Info(pipeNo, &r2yInAddr);
	Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
#endif
	ct_im_r2y_set_wb_gain_rgb(pipeNo);
	ct_im_r2y_set_gamma_on(pipeNo);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", 0));
#ifdef IM_R2Y_STATUS_PRINT
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "Status\n"));
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
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "R2Y Start\n"));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Start(pipeNo);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
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
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Stop(pipeNo);
	DriverCommon_DDIM_PRINT((CtImR2y31series_FUNC_NAME "0x%x\n", ercd));
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

CtImR2y31series* ct_im_r2y_31series_new(void)
{
	CtImR2y31series* self = k_object_new_with_private(CT_TYPE_IM_R2Y_31SERIES, sizeof(CtImR2y31seriesPrivate));

	return self;
}
