/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 梁正明
*@brief : CtImR2y36series1
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimr2ytool.h"
#include "ctimr2y36series1.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImR2y36series1, ct_im_r2y_36series1)
#define CT_IM_R2Y_36SERIES1_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), \
		CtImR2y36series1Private, CT_TYPE_IM_R2Y_36SERIES1))


struct _CtImR2y36series1Private
{

};


/*
 * IMPL
 */
static void ct_im_r2y_36series1_constructor(CtImR2y36series1 *self)
{
	//CtImR2y36series1Private *priv = CT_IM_R2Y_36SERIES1_GET_PRIVATE(self);
}

static void ct_im_r2y_36series1_destructor(CtImR2y36series1 *self)
{
	//CtImR2y36series1Private *priv = CT_IM_R2Y_36SERIES1_GET_PRIVATE(self);
}


/*
 * PUBLIC
 */
#undef 	CtImR2y36series1_FUNC_NAME
#define 	CtImR2y36series1_FUNC_NAME "ct_im_r2y_36series1_6: "
kint32 ct_im_r2y_36series1_6(CtImR2y36series1 *self, kuchar pipeNo)
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

	Ddim_Print(("%s\n", CtImR2y36series1_FUNC_NAME));
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_0] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_1] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_2] = ImR2y_ENABLE_ON;
	r2yCtrl.yyw[D_IM_R2Y_YYW_CH_2].pixelAvgReductionEnable = ImR2y_ENABLE_ON;
	r2yCtrl.yyw[D_IM_R2Y_YYW_CH_2].pixelAvgReductionMode = D_IM_R2Y_RDC_MODE_DIV_2;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_2].yywWidth = D_IM_R2Y_DST_IMG_PIXS_WIDTH;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_2].yywLines = D_IM_R2Y_DST_IMG_PIXS_LINES;
	memset(&r2yAddr0, '\x00', sizeof(r2yAddr0));
	r2yAddr0 = gctImR2yOutAddrYcc422;
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Ctrl_ModeSDRAMInput(pipeNo, &r2yCtrlSdramIn);
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_InAddr_Info(pipeNo, &r2yInAddr);
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_2, &r2yAddr0);
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	Im_R2Y_Ctrl_ModeSDRAMInput(pipeNo, &r2yCtrlSdramIn);
	Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	Im_R2Y_Set_InAddr_Info(pipeNo, &r2yInAddr);
	Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_2, &r2yAddr0);
#endif
	ct_im_r2y_set_wb_gain_rgb(pipeNo);
	ct_im_r2y_set_gamma_on(pipeNo);
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", 0));
#ifdef IM_R2Y_STATUS_PRINT
	Ddim_Print((CtImR2y36series1_FUNC_NAME "Status\n"));
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
	Ddim_Print((CtImR2y36series1_FUNC_NAME "R2Y Start\n"));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Start(pipeNo);
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", ercd));
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
		flgptn |= D_IM_R2Y1_INT_FLG_YYW2_END;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)){
		flgptn |= D_IM_R2Y2_INT_FLG_YYW2_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_WaitEnd(NULL, flgptn, 60);
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Stop(pipeNo);
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", ercd));
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

#undef 	CtImR2y36series1_FUNC_NAME
#define 	CtImR2y36series1_FUNC_NAME "ct_im_r2y_36series1_7: "
kint32 ct_im_r2y_36series1_7(CtImR2y36series1 *self, kuchar pipeNo)
{
	TImR2yCtrl r2yCtrl = gctImR2yCtrlBase;
	TImR2yCtrlSdramInput r2yCtrlSdramIn = gctImR2yCtrlSdramInRgb16bit;
	TImR2yResizeRect r2yResizeRectParam = gctImR2yResizeRectParamOutYcc422;
	TImR2yInaddrInfo r2yInAddr = gctImR2yInAddrRgb16bit;
	TImR2yOutbankInfo r2yAddr0;
	DDIM_USER_FLGPTN flgptn = 0;
// Choice orange patch of Macbeth color chart
#if 1
	TImR2yColorExtract r2yColorExtract =
		{
			.extractEnable = 1,
			.refAxisX = -104,
			.refAxisY = 72,
		};

	TImR2yChromaScale r2yChromaScale =
		{
			.chromaOffset = 28,
			.chromaGain = (kushort)(15.984375 * 0x40),
		};

	TImR2yHueScale r2yHueScale =
		{
			.hueOffset = 0,
			.hueGain = (kushort)(15.984375 * 0x40),
		};
#endif
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(("%s\n", CtImR2y36series1_FUNC_NAME));
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_0] = ImR2y_ENABLE_ON;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_1] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_2] = ImR2y_ENABLE_OFF;
	memset(&r2yAddr0, '\x00', sizeof(r2yAddr0));
	r2yAddr0 = gctImR2yOutAddrYcc422;
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Ctrl_ModeSDRAMInput(pipeNo, &r2yCtrlSdramIn);
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_Color_Extract(pipeNo, &r2yColorExtract);
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_Chroma(pipeNo, &r2yChromaScale);
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_Hue(pipeNo, &r2yHueScale);
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_InAddr_Info(pipeNo, &r2yInAddr);
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	Im_R2Y_Ctrl_ModeSDRAMInput(pipeNo, &r2yCtrlSdramIn);
	Im_R2Y_Set_Color_Extract(pipeNo, &r2yColorExtract);
	Im_R2Y_Set_Chroma(pipeNo, &r2yChromaScale);
	Im_R2Y_Set_Hue(pipeNo, &r2yHueScale);
	Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	Im_R2Y_Set_InAddr_Info(pipeNo, &r2yInAddr);
	Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
#endif
	ct_im_r2y_set_wb_gain_rgb(pipeNo);
	ct_im_r2y_set_gamma_on(pipeNo);
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", 0));
#ifdef IM_R2Y_STATUS_PRINT
	Ddim_Print((CtImR2y36series1_FUNC_NAME "Status\n"));
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
	Ddim_Print((CtImR2y36series1_FUNC_NAME "R2Y Start\n"));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Start(pipeNo);
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", ercd));
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
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Stop(pipeNo);
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_WaitEnd(NULL, flgptn, 60);
	Im_R2Y_Stop(pipeNo);
#endif
	ct_im_r2y_print_r2y_common_reg();
	ct_im_r2y_print_r2y_yyr_reg();
	ct_im_r2y_print_r2y_yyw_reg();
	ct_im_r2y_print_r2y_ctrl_reg();
	ct_im_r2y_print_r2y_ctrl_modesdraminput_reg();
	ct_im_r2y_print_resize_rect_reg();
	ct_im_r2y_print_color_extract_reg();
	ct_im_r2y_print_chroma_scale_reg();
	ct_im_r2y_print_hue_scale_reg();
	ct_im_r2y_print_post_resize_edge0_reg();
	ct_im_r2y_print_post_resize_edge1_reg();
	ct_im_r2y_print_fr2y_ctrl_reg();
#ifdef IM_R2Y_STATUS_PRINT
	Im_R2Y_Print_Status();
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y36series1_FUNC_NAME
#define 	CtImR2y36series1_FUNC_NAME "ct_im_r2y_36series1_8: "
kint32 ct_im_r2y_36series1_8(CtImR2y36series1 *self, kuchar pipeNo)
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

	Ddim_Print(("%s\n", CtImR2y36series1_FUNC_NAME));
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_0] = ImR2y_ENABLE_ON;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_1] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_2] = ImR2y_ENABLE_OFF;
	memset(&r2yAddr0, '\x00', sizeof(r2yAddr0));
	r2yAddr0 = gctImR2yOutAddrYcc422;
	// 180 degree rotation.
	r2yCtrl.yywHorizontalFlip = ImR2y_ENABLE_ON;
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_0].ycc.addrY
		= (VOID*)(((ULONG)r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_0].ycc.addrY)
		+ (r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].outputGlobalW[D_IM_R2Y_PORT_Y]
		* (r2yResizeRectParam.inputSize.imgLines -1)));
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_0].ycc.addrCb
		= (VOID*)(((ULONG)r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_0].ycc.addrCb)
		+ (r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].outputGlobalW[D_IM_R2Y_PORT_CBCR]
		* (r2yResizeRectParam.inputSize.imgLines -1)));
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].outputGlobalW[D_IM_R2Y_PORT_Y]
		= -r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].outputGlobalW[D_IM_R2Y_PORT_Y];
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].outputGlobalW[D_IM_R2Y_PORT_CBCR]
		= -r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].outputGlobalW[D_IM_R2Y_PORT_CBCR];
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Ctrl_ModeSDRAMInput(pipeNo, &r2yCtrlSdramIn);
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_InAddr_Info(pipeNo, &r2yInAddr);
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	Im_R2Y_Ctrl_ModeSDRAMInput(pipeNo, &r2yCtrlSdramIn);
	Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	Im_R2Y_Set_InAddr_Info(pipeNo, &r2yInAddr);
	Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
#endif
	ct_im_r2y_set_wb_gain_rgb(pipeNo);
	ct_im_r2y_set_gamma_on(pipeNo);
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", 0));
#ifdef IM_R2Y_STATUS_PRINT
	Ddim_Print((CtImR2y36series1_FUNC_NAME "Status\n"));
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
	Ddim_Print((CtImR2y36series1_FUNC_NAME "R2Y Start\n"));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Start(pipeNo);
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", ercd));
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
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Stop(pipeNo);
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_WaitEnd(NULL, flgptn, 60);
	Im_R2Y_Stop(pipeNo);
#endif
	ct_im_r2y_print_r2y_common_reg();
	ct_im_r2y_print_r2y_yyr_reg();
	ct_im_r2y_print_r2y_yyw_reg();
	ct_im_r2y_print_r2y_ctrl_reg();
	ct_im_r2y_print_r2y_ctrl_modesdraminput_reg();
	ct_im_r2y_print_resize_rect_reg();
	ct_im_r2y_print_color_extract_reg();
	ct_im_r2y_print_chroma_scale_reg();
	ct_im_r2y_print_hue_scale_reg();
	ct_im_r2y_print_post_resize_edge0_reg();
	ct_im_r2y_print_post_resize_edge1_reg();
	ct_im_r2y_print_fr2y_ctrl_reg();
#ifdef IM_R2Y_STATUS_PRINT
	Im_R2Y_Print_Status();
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y36series1_FUNC_NAME
#define 	CtImR2y36series1_FUNC_NAME "ct_im_r2y_36series1_9: "
kint32 ct_im_r2y_36series1_9(CtImR2y36series1 *self, kuchar pipeNo)
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

	Ddim_Print(("%s\n", CtImR2y36series1_FUNC_NAME));
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_0] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_1] = ImR2y_ENABLE_ON;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_2] = ImR2y_ENABLE_OFF;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_1].yywWidth = D_IM_R2Y_DST_IMG_PIXS_WIDTH;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_1].yywLines = D_IM_R2Y_DST_IMG_PIXS_LINES;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_1].outputGlobalW[D_IM_R2Y_PORT_Y]
	        = D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC422_Y;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_1].outputGlobalW[D_IM_R2Y_PORT_CBCR]
	        = D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC422_C;
	memset(&r2yAddr0, '\x00', sizeof(r2yAddr0));
	r2yAddr0 = gctImR2yOutAddrYcc422;
	// 180 degree rotation.
	r2yCtrl.yywHorizontalFlip = ImR2y_ENABLE_ON;
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_0].ycc.addrY
		= (VOID*)(((ULONG)r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_0].ycc.addrY)
		+ (r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_1].outputGlobalW[D_IM_R2Y_PORT_Y]
		* (r2yResizeRectParam.inputSize.imgLines -1)));
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_0].ycc.addrCb
		= (VOID*)(((ULONG)r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_0].ycc.addrCb)
		+ (r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_1].outputGlobalW[D_IM_R2Y_PORT_CBCR]
		* (r2yResizeRectParam.inputSize.imgLines -1)));
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_1].outputGlobalW[D_IM_R2Y_PORT_Y]
		= -r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_1].outputGlobalW[D_IM_R2Y_PORT_Y];
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_1].outputGlobalW[D_IM_R2Y_PORT_CBCR]
		= -r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_1].outputGlobalW[D_IM_R2Y_PORT_CBCR];
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Ctrl_ModeSDRAMInput(pipeNo, &r2yCtrlSdramIn);
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_InAddr_Info(pipeNo, &r2yInAddr);
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_1, &r2yAddr0);
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_Ctrl(pipeNo, &r2yCtrl);
	Im_R2Y_Ctrl_ModeSDRAMInput(pipeNo, &r2yCtrlSdramIn);
	Im_R2Y_Set_Resize_Rect(pipeNo, &r2yResizeRectParam);
	Im_R2Y_Set_InAddr_Info(pipeNo, &r2yInAddr);
	Im_R2Y_Set_OutBankInfo(pipeNo, D_IM_R2Y_YYW_CH_1, &r2yAddr0);
#endif
	ct_im_r2y_set_wb_gain_rgb(pipeNo);
	ct_im_r2y_set_gamma_on(pipeNo);
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", 0));
#ifdef IM_R2Y_STATUS_PRINT
	Ddim_Print((CtImR2y36series1_FUNC_NAME "Status\n"));
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
	Ddim_Print((CtImR2y36series1_FUNC_NAME "R2Y Start\n"));

#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Start(pipeNo);
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", ercd));
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
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_R2Y_Stop(pipeNo);
	Ddim_Print((CtImR2y36series1_FUNC_NAME "0x%x\n", ercd));
#else
	Im_R2Y_WaitEnd(NULL, flgptn, 60);
	Im_R2Y_Stop(pipeNo);
#endif
	ct_im_r2y_print_r2y_common_reg();
	ct_im_r2y_print_r2y_yyr_reg();
	ct_im_r2y_print_r2y_yyw_reg();
	ct_im_r2y_print_r2y_ctrl_reg();
	ct_im_r2y_print_r2y_ctrl_modesdraminput_reg();
	ct_im_r2y_print_resize_rect_reg();
	ct_im_r2y_print_color_extract_reg();
	ct_im_r2y_print_chroma_scale_reg();
	ct_im_r2y_print_hue_scale_reg();
	ct_im_r2y_print_post_resize_edge0_reg();
	ct_im_r2y_print_post_resize_edge1_reg();
	ct_im_r2y_print_fr2y_ctrl_reg();
#ifdef IM_R2Y_STATUS_PRINT
	Im_R2Y_Print_Status();
#endif

	return D_DDIM_OK;
}

CtImR2y36series1 *ct_im_r2y_36series1_new(void)
{
	CtImR2y36series1 *self = k_object_new_with_private(CT_TYPE_IM_R2Y_36SERIES1, sizeof(CtImR2y36series1Private));

	return self;
}
