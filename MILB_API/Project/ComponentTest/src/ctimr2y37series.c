/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 梁正明
*@brief : CtImR2y37series
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimr2ytool.h"
#include "imr2ystat.h"
#include "ctimr2y37series.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImR2y37series, ct_im_r2y_37series)
#define CT_IM_R2Y_37SERIES_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), \
		CtImR2y37seriesPrivate, CT_TYPE_IM_R2Y_37SERIES))


struct _CtImR2y37seriesPrivate
{

};


/*
 * IMPL
 */
static void ct_im_r2y_37series_constructor(CtImR2y37series *self)
{
	CtImR2y37seriesPrivate *priv = CT_IM_R2Y_37SERIES_GET_PRIVATE(self);
	self->ctImR2y = ct_im_r2y_new();
	self->ctImR2yClassa = ct_im_r2y_classa_new();
	self->ctImR2yClassb = ct_im_r2y_classb_new();
	self->imR2y = im_r2y_new();
	self->imR2y2 = im_r2y2_new();
	self->imR2y3 = im_r2y3_new();
	self->imR2yCtrl2 = im_r2y_ctrl2_new();
	self->imR2yCtrl3 = im_r2y_ctrl3_new();
	self->imR2yProc = im_r2y_proc_new();
	self->imR2yStat = im_r2y_stat_new();
}

static void ct_im_r2y_37series_destructor(CtImR2y37series *self)
{
	//CtImR2y37seriesPrivate *priv = CT_IM_R2Y_37SERIES_GET_PRIVATE(self);
}


/*
 * PUBLIC
 */
#undef 	CtImR2y37series_FUNC_NAME
#define 	CtImR2y37series_FUNC_NAME "ct_im_r2y_37series_0: "
kint32 ct_im_r2y_37series_0(CtImR2y37series *self, kuchar pipeNo)
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

	Ddim_Print(("%s\n", CtImR2y37series_FUNC_NAME));
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_0] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_1] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_2] = ImR2y_ENABLE_ON;
	memset(&r2yAddr0, '\x00', sizeof(r2yAddr0));
	r2yAddr0 = gctImR2yOutAddrYcc422;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_2].yywWidth = D_IM_R2Y_DST_IMG_PIXS_WIDTH;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_2].yywLines = D_IM_R2Y_DST_IMG_PIXS_LINES;
	// 180 degree rotation.
	r2yCtrl.yywHorizontalFlip = ImR2y_ENABLE_ON;
	r2yAddr0.outputAddr[ImR2y_YYW_BANK_0].ycc.addrY
		= (VOID*)(((ULONG)r2yAddr0.outputAddr[ImR2y_YYW_BANK_0].ycc.addrY)
		+ (r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_2].outputGlobalW[ImR2y_PORT_Y]
		* (r2yResizeRectParam.inputSize.imgLines -1)));
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_2].outputGlobalW[ImR2y_PORT_Y]
		= -r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_2].outputGlobalW[ImR2y_PORT_Y];
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_ctrl_mode_sdram_input(self->imR2y, pipeNo, &r2yCtrlSdramIn);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_set_inaddr_info(self->imR2y, pipeNo, &r2yInAddr);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_2, &r2yAddr0);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl);
	im_r2y_ctrl_mode_sdram_input(self->imR2y, pipeNo, &r2yCtrlSdramIn);
	im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam);
	im_r2y_set_inaddr_info(self->imR2y, pipeNo, &r2yInAddr);
	im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_2, &r2yAddr0);
#endif
	ct_im_r2y_classa_set_wb_gain_rgb(self->ctImR2yClassa, pipeNo);
	ct_im_r2y_set_gamma_on(self->ctImR2y, pipeNo);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", 0));
#ifdef IM_R2Y_STATUS_PRINT
	Ddim_Print((CtImR2y37series_FUNC_NAME "Status\n"));
	im_r2y_stat_print_status(self->imR2yStat);
#endif
#ifdef D_IM_R2Y_DEBUG_ON_PC
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)){
		gimR2yMacroFakeFinish[0] = 1;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)){
		gimR2yMacroFakeFinish[1] = 1;
	}
#endif
	Ddim_Print((CtImR2y37series_FUNC_NAME "R2Y Start\n"));
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_proc_start(self->imR2yProc, pipeNo);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_proc_start(self->imR2yProc, pipeNo);
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
	ercd = im_r2y_proc_waitend(self->imR2yProc, NULL, flgptn, 60);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_proc_stop(self->imR2yProc, pipeNo);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_proc_waitend(self->imR2yProc, NULL, flgptn, 60);
	im_r2y_proc_stop(self->imR2yProc, pipeNo);
#endif
	ct_im_r2y_classa_print_r2y_common_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_r2y_yyr_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_r2y_yyw_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_r2y_ctrl_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_r2y_ctrl_modesdraminput_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_resize_rect_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_color_extract_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_chroma_scale_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_chroma_scale_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_post_resize_edge0_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_post_resize_edge1_reg(self->ctImR2yClassa);
	ct_im_r2y_classb_print_fr2y_ctrl_reg(self->ctImR2yClassb);
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y37series_FUNC_NAME
#define 	CtImR2y37series_FUNC_NAME "ct_im_r2y_37series_1: "
kint32 ct_im_r2y_37series_1(CtImR2y37series *self, kuchar pipeNo)
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

	Ddim_Print(("%s\n", CtImR2y37series_FUNC_NAME));
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_0]  = ImR2y_ENABLE_ON;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_1]  = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_2]  = ImR2y_ENABLE_OFF;
	r2yCtrl.outputMode0a = D_IM_R2Y_YYW0A_OUTPUT_MODE_DIV_32_SP;
	r2yCtrlSdramIn.inputGlobal = 1280 * 2;
	r2yResizeRectParam.inputSize.imgWidth = 1280;
	r2yResizeRectParam.inputSize.imgLines = 960;
	r2yInAddr.rgb.addrR = (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_U16_R_ADDR_TOP;
	r2yInAddr.rgb.addrG = (VOID*)(r2yInAddr.rgb.addrR
			+ (r2yResizeRectParam.inputSize.imgWidth * r2yResizeRectParam.inputSize.imgLines * 2));
	r2yInAddr.rgb.addrB = (VOID*)(r2yInAddr.rgb.addrG
			+ (r2yResizeRectParam.inputSize.imgWidth * r2yResizeRectParam.inputSize.imgLines * 2));
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].yywWidth = 1280;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].yywLines = 960;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].outputGlobalW[ImR2y_PORT_Y]     = 1280;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].outputGlobalW[D_IM_R2Y_PORT_CBCR]  = 1280;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0A].outputGlobalW[ImR2y_PORT_Y]    = 1280 / 32;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0A].outputGlobalW[D_IM_R2Y_PORT_CBCR] = 1280 / 32;
	r2yCtrlTrimming.trimmingEnable       = ImR2y_ENABLE_ON;
	r2yCtrlTrimming.trimWindow.imgLeft  = 0;
	r2yCtrlTrimming.trimWindow.imgTop   = 0;
	r2yCtrlTrimming.trimWindow.imgWidth = r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].yywWidth;
	r2yCtrlTrimming.trimWindow.imgLines = r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].yywLines;
	memset(&r2yAddr0, '\x00', sizeof(r2yAddr0));
	r2yAddr0 = gctImR2yOutAddrYcc422;
	// 180 degree rotation.
	r2yCtrl.yywHorizontalFlip = ImR2y_ENABLE_ON;
	r2yAddr0.outputAddr[ImR2y_YYW_BANK_0].ycc.addrY  = (VOID*)(r2yInAddr.rgb.addrB
			+ (r2yResizeRectParam.inputSize.imgWidth * r2yResizeRectParam.inputSize.imgLines * 2));
	r2yAddr0.outputAddr[ImR2y_YYW_BANK_0].ycc.addrCb
			= (VOID*)(((ULONG)r2yAddr0.outputAddr[ImR2y_YYW_BANK_0].ycc.addrY)
			+ (r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].outputGlobalW[ImR2y_PORT_Y]
			* (r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].yywLines)));
	r2yAddr0a.outputAddr[ImR2y_YYW_BANK_0].ycc.addrY
			= (VOID*)(((ULONG)r2yAddr0.outputAddr[ImR2y_YYW_BANK_0].ycc.addrCb)
			 + (r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].outputGlobalW[D_IM_R2Y_PORT_CBCR]
			 * (r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].yywLines)));
	r2yAddr0a.outputAddr[ImR2y_YYW_BANK_0].ycc.addrCb
			= (VOID*)(((ULONG)r2yAddr0a.outputAddr[ImR2y_YYW_BANK_0].ycc.addrY)
			+ (r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0A].outputGlobalW[ImR2y_PORT_Y]
			* (r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].yywLines / 32)));
	r2yAddr0.outputAddr[ImR2y_YYW_BANK_0].ycc.addrY
			= (VOID*)(((ULONG)r2yAddr0.outputAddr[ImR2y_YYW_BANK_0].ycc.addrY)
			+ (r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].outputGlobalW[ImR2y_PORT_Y]
			* (r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].yywLines -1)));
	r2yAddr0.outputAddr[ImR2y_YYW_BANK_0].ycc.addrCb
			= (VOID*)(((ULONG)r2yAddr0.outputAddr[ImR2y_YYW_BANK_0].ycc.addrCb)
			+ (r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].outputGlobalW[D_IM_R2Y_PORT_CBCR]
			* (r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].yywLines -1)));
	r2yAddr0a.outputAddr[ImR2y_YYW_BANK_0].ycc.addrY
			= (VOID*)(((ULONG)r2yAddr0a.outputAddr[ImR2y_YYW_BANK_0].ycc.addrY)
			+ (r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0A].outputGlobalW[ImR2y_PORT_Y]
			* (r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].yywLines / 32 -1)));
	r2yAddr0a.outputAddr[ImR2y_YYW_BANK_0].ycc.addrCb
			= (VOID*)(((ULONG)r2yAddr0a.outputAddr[ImR2y_YYW_BANK_0].ycc.addrCb)
			+ (r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0A].outputGlobalW[D_IM_R2Y_PORT_CBCR]
			* (r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].yywLines / 32 -1)));
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].outputGlobalW[ImR2y_PORT_Y]
	        = -r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].outputGlobalW[ImR2y_PORT_Y];
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].outputGlobalW[D_IM_R2Y_PORT_CBCR]
		    = -r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].outputGlobalW[D_IM_R2Y_PORT_CBCR];
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0A].outputGlobalW[ImR2y_PORT_Y]
		   = -r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0A].outputGlobalW[ImR2y_PORT_Y];
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0A].outputGlobalW[D_IM_R2Y_PORT_CBCR]
		  = -r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0A].outputGlobalW[D_IM_R2Y_PORT_CBCR];
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_ctrl_mode_sdram_input(self->imR2y, pipeNo, &r2yCtrlSdramIn);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y3_ctrl_trimming(self->imR2y3, pipeNo, D_IM_R2Y_YYW_CH_0, &r2yCtrlTrimming);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_set_inaddr_info(self->imR2y, pipeNo, &r2yInAddr);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0A, &r2yAddr0a);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl);
	im_r2y_ctrl_mode_sdram_input(self->imR2y, pipeNo, &r2yCtrlSdramIn);
	im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam);
	im_r2y3_ctrl_trimming(self->imR2y3, pipeNo, D_IM_R2Y_YYW_CH_0, &r2yCtrlTrimming);
	im_r2y_set_inaddr_info(self->imR2y, pipeNo, &r2yInAddr);
	im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
	im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0A, &r2yAddr0a);
#endif
	ct_im_r2y_classa_set_wb_gain_rgb(self->ctImR2yClassa, pipeNo);
	ct_im_r2y_set_gamma_on(self->ctImR2y, pipeNo);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", 0));
#ifdef IM_R2Y_STATUS_PRINT
	Ddim_Print((CtImR2y37series_FUNC_NAME "Status\n"));
	im_r2y_stat_print_status(self->imR2yStat);
#endif
#ifdef D_IM_R2Y_DEBUG_ON_PC
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)){
		gimR2yMacroFakeFinish[0] = 1;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)){
		gimR2yMacroFakeFinish[1] = 1;
	}
#endif
	Ddim_Print((CtImR2y37series_FUNC_NAME "R2Y Start\n"));
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_proc_start(self->imR2yProc, pipeNo);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_proc_start(self->imR2yProc, pipeNo);
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
		flgptn |= D_IM_R2Y1_INT_FLG_YYW0A_END;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)){
		flgptn |= D_IM_R2Y1_INT_FLG_YYW0_END;
		flgptn |= D_IM_R2Y1_INT_FLG_YYW0A_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_proc_waitend(self->imR2yProc, NULL, flgptn, 60);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_proc_stop(self->imR2yProc, pipeNo);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_proc_waitend(self->imR2yProc, NULL, flgptn, 60);
	im_r2y_proc_stop(self->imR2yProc, pipeNo);
#endif
	ct_im_r2y_classa_print_r2y_common_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_r2y_yyr_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_r2y_yyw_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_r2y_ctrl_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_r2y_ctrl_modesdraminput_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_resize_rect_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_trimming_reg(self->ctImR2yClassa);
	ct_im_classb_r2y_print_other_reg(self->ctImR2yClassb);
	ct_im_r2y_classa_print_color_extract_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_chroma_scale_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_chroma_scale_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_post_resize_edge0_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_post_resize_edge1_reg(self->ctImR2yClassa);
	ct_im_r2y_classb_print_fr2y_ctrl_reg(self->ctImR2yClassb);
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y37series_FUNC_NAME
#define 	CtImR2y37series_FUNC_NAME "ct_im_r2y_37series_2: "
kint32 ct_im_r2y_37series_2(CtImR2y37series *self, kuchar pipeNo)
{
	TImR2yCtrl r2yCtrl = gctImR2yCtrlBase;
	TImR2yCtrlSdramInput r2yCtrlSdramIn = gctImR2yCtrlSdramInRgb16bit;
	TImR2yResizeRect r2yResizeRectParam = gctImR2yResizeRectParamOutYcc422;
	TImR2yInaddrInfo r2yInAddr = gctImR2yInAddrRgb16bit;
	TImR2yOutbankInfo r2yAddr0;
	TImR2yTct r2yCtrlBtcTct;
	kuint32* tct_addr = (kuint32*)D_IM_R2Y_TBL_MEM_OUT_ADDR_TOP_TCTDATA;
	DDIM_USER_FLGPTN flgptn = 0;
	kuint32 loopcnt;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(("%s\n", CtImR2y37series_FUNC_NAME));
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_0] = ImR2y_ENABLE_ON;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_1] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_2] = ImR2y_ENABLE_OFF;
	r2yCtrlBtcTct.tct_enable = 1;
	r2yCtrlBtcTct.start_x = 0;
	r2yCtrlBtcTct.start_y = 0;
	r2yCtrlBtcTct.block_hsiz = 16;
	r2yCtrlBtcTct.block_vsiz = 16;
	r2yCtrlBtcTct.blockHnum = 40;
	r2yCtrlBtcTct.blockVnum = 30;
	memset(&r2yAddr0, '\x00', sizeof(r2yAddr0));
	r2yAddr0 = gctImR2yOutAddrYcc422;
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_ctrl_mode_sdram_input(self->imR2y, pipeNo, &r2yCtrlSdramIn);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_set_inaddr_info(self->imR2y, pipeNo, &r2yInAddr);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_ctrl2_before_tone_tct(self->imR2yCtrl2, pipeNo, &r2yCtrlBtcTct);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl);
	im_r2y_ctrl_mode_sdram_input(self->imR2y, pipeNo, &r2yCtrlSdramIn);
	im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam);
	im_r2y_set_inaddr_info(self->imR2y, pipeNo, &r2yInAddr);
	im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
	im_r2y_ctrl2_before_tone_tct(self->imR2yCtrl2, pipeNo, &r2yCtrlBtcTct);
#endif
	ct_im_r2y_classa_set_wb_gain_rgb(self->ctImR2yClassa, pipeNo);
	ct_im_r2y_set_gamma_on(self->ctImR2y, pipeNo);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", 0));
#ifdef IM_R2Y_STATUS_PRINT
	Ddim_Print((CtImR2y37series_FUNC_NAME "R2Y Start Status\n"));
	im_r2y_stat_print_status(self->imR2yStat);
	im_r2y_stat_print_clock_status(self->ctImR2yStat);
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif
#ifdef D_IM_R2Y_DEBUG_ON_PC
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)){
		gimR2yMacroFakeFinish[0] = 1;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)){
		gimR2yMacroFakeFinish[1] = 1;
	}
#endif
	Ddim_Print((CtImR2y37series_FUNC_NAME "R2Y Start\n"));
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_proc_start(self->imR2yProc, pipeNo);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_proc_start(self->imR2yProc, pipeNo);
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
	ercd = im_r2y_proc_waitend(self->imR2yProc, NULL, flgptn, 60 * 10);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_proc_stop(self->imR2yProc, pipeNo);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_ctrl3_get_luminance_evaluation_before_tone(self->imR2yCtrl3, pipeNo, tct_addr,
			r2yCtrlBtcTct.blockHnum * r2yCtrlBtcTct.blockVnum);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_proc_waitend(self->imR2yProc, NULL, flgptn, 60 * 10);
	im_r2y_proc_stop(self->imR2yProc, pipeNo);
	im_r2y_ctrl3_get_luminance_evaluation_before_tone(self->imR2yCtrl3, pipeNo, tct_addr,
			r2yCtrlBtcTct.blockHnum * r2yCtrlBtcTct.blockVnum);
#endif
	for(loopcnt = 0; loopcnt < 64; loopcnt++){
		Ddim_Print((CtImR2y37series_FUNC_NAME "TCTDATA[%x] = 0x%x\n", loopcnt, *tct_addr));
		tct_addr++;
	}
	ct_im_r2y_classa_print_r2y_common_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_r2y_yyr_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_r2y_yyw_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_r2y_ctrl_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_r2y_ctrl_modesdraminput_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_r2y_ctrl_modedirect_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_resize_rect_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_trimming_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_color_extract_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_hist_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_post_resize_edge0_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_post_resize_edge1_reg(self->ctImR2yClassa);
	ct_im_classb_r2y_print_other_reg(self->ctImR2yClassb);
	ct_im_r2y_classb_print_fr2y_ctrl_reg(self->ctImR2yClassb);
	ct_im_r2y_classb_print_axi_reg(self->ctImR2yClassb);
#ifdef IM_R2Y_STATUS_PRINT
	Ddim_Print((CtImR2y37series_FUNC_NAME "R2Y End Status\n"));
	im_r2y_stat_print_status(self->imR2yStat);
	im_r2y_stat_print_clock_status(self->ctImR2yStat);
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y37series_FUNC_NAME
#define 	CtImR2y37series_FUNC_NAME "ct_im_r2y_37series_3: "
kint32 ct_im_r2y_37series_3(CtImR2y37series *self,, kuchar pipeNo)
{
	TImR2yCtrl r2yCtrl = gctImR2yCtrlBase;
	TImR2yCtrlSdramInput r2yCtrlSdramIn = gctImR2yCtrlSdramInRgb16bit;
	TImR2yResizeRect r2yResizeRectParam = gctImR2yResizeRectParamOutYcc422;
	TImR2yInaddrInfo r2yInAddr = gctImR2yInAddrRgb16bit;
	TImR2yOutbankInfo r2yAddr0;
	TImR2yTchs r2yCtrlBtcTchs;
	TImR2yTchsFlg tchsFlg;
	kushort* tchsYAddr = (kushort*)D_IM_R2Y_TBL_MEM_OUT_ADDR_TOP_TCHSYDATA;
	kushort* tchsRAddr = (kushort*)D_IM_R2Y_TBL_MEM_OUT_ADDR_TOP_TCHSRDATA;
	kushort* tchsGAddr = (kushort*)D_IM_R2Y_TBL_MEM_OUT_ADDR_TOP_TCHSGDATA;
	kushort* tchsBAddr = (kushort*)D_IM_R2Y_TBL_MEM_OUT_ADDR_TOP_TCHSBDATA;
	DDIM_USER_FLGPTN flgptn = 0;
	kuint32 loopcnt;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(("%s\n", CtImR2y37series_FUNC_NAME));
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_0] = ImR2y_ENABLE_ON;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_1] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_2] = ImR2y_ENABLE_OFF;
	r2yCtrlBtcTchs.hist_enable = 1;
	r2yCtrlBtcTchs.sampling_hcyc = D_IM_R2Y_HIST_HCYC_4;
	r2yCtrlBtcTchs.sampling_vcyc = D_IM_R2Y_HIST_VCYC_4;
	r2yCtrlBtcTchs.histogram_mode = D_IM_R2Y_HIST_BIT_WIDTH_11_4;
	r2yCtrlBtcTchs.hist_minus_mode = ImR2y_ENABLE_ON;
	r2yCtrlBtcTchs.tchs_window.imgLeft = 0;
	r2yCtrlBtcTchs.tchs_window.imgTop = 0;
	r2yCtrlBtcTchs.tchs_window.imgWidth = 640;
	r2yCtrlBtcTchs.tchs_window.imgLines = 480;
	memset(&r2yAddr0, '\x00', sizeof(r2yAddr0));
	r2yAddr0 = gctImR2yOutAddrYcc422;
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_ctrl_mode_sdram_input(self->imR2y, pipeNo, &r2yCtrlSdramIn);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_set_inaddr_info(self->imR2y, pipeNo, &r2yInAddr);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_ctrl2_before_tone_tchs(self->imR2yCtrl2, pipeNo, &r2yCtrlBtcTchs);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl);
	im_r2y_ctrl_mode_sdram_input(self->imR2y, pipeNo, &r2yCtrlSdramIn);
	im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam);
	im_r2y_set_inaddr_info(self->imR2y, pipeNo, &r2yInAddr);
	im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
	im_r2y_ctrl2_before_tone_tchs(self->imR2yCtrl2, pipeNo, &r2yCtrlBtcTchs);
#endif
	ct_im_r2y_classa_set_wb_gain_rgb(self->ctImR2yClassa, pipeNo);
	ct_im_r2y_set_gamma_on(self->ctImR2y, pipeNo);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", 0));
#ifdef IM_R2Y_STATUS_PRINT
	Ddim_Print((CtImR2y37series_FUNC_NAME "R2Y Start Status\n"));
	im_r2y_stat_print_status(self->imR2yStat);
	im_r2y_stat_print_clock_status(self->ctImR2yStat);
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif
#ifdef D_IM_R2Y_DEBUG_ON_PC
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)){
		gimR2yMacroFakeFinish[0] = 1;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)){
		gimR2yMacroFakeFinish[1] = 1;
	}
#endif
	Ddim_Print((CtImR2y37series_FUNC_NAME "R2Y Start\n"));
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_proc_start(self->imR2yProc, pipeNo);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_proc_start(self->imR2yProc, pipeNo);
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
	ercd = im_r2y_proc_waitend(self->imR2yProc, NULL, flgptn, 60 * 10);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_proc_stop(self->imR2yProc, pipeNo);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_ctrl3_get_histogram_before_tone(self->imR2yCtrl3, pipeNo, E_R2Y_BTC_HIST_RGBTBL_Y, &tchsFlg, tchsYAddr);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
	if(tchsFlg.Y != 0){
		Ddim_Print((CtImR2y37series_FUNC_NAME "TCHS Y overflow\n"));
	}
	for(loopcnt = 0; loopcnt < 64; loopcnt++){
		Ddim_Print((CtImR2y37series_FUNC_NAME "TCHSYDATA[%x] = 0x%x\n", loopcnt, *tchsYAddr));
		tchsYAddr++;
	}
	ercd = im_r2y_ctrl3_get_histogram_before_tone(self->imR2yCtrl3, pipeNo, E_R2Y_BTC_HIST_RGBTBL_R, &tchsFlg, tchsRAddr);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
	if(tchsFlg.R != 0){
		Ddim_Print((CtImR2y37series_FUNC_NAME "TCHS R overflow\n"));
	}
	for(loopcnt = 0; loopcnt < 64; loopcnt++){
		Ddim_Print((CtImR2y37series_FUNC_NAME "TCHSRDATA[%x] = 0x%x\n", loopcnt, *tchsRAddr));
		tchsRAddr++;
	}
	ercd = im_r2y_ctrl3_get_histogram_before_tone(self->imR2yCtrl3, pipeNo, E_R2Y_BTC_HIST_RGBTBL_G, &tchsFlg, tchsGAddr);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
	if(tchsFlg.G != 0){
		Ddim_Print((CtImR2y37series_FUNC_NAME "TCHS G overflow\n"));
	}
	for(loopcnt = 0; loopcnt < 64; loopcnt++){
		Ddim_Print((CtImR2y37series_FUNC_NAME "TCHSGDATA[%x] = 0x%x\n", loopcnt, *tchsGAddr));
		tchsGAddr++;
	}
	ercd = im_r2y_ctrl3_get_histogram_before_tone(self->imR2yCtrl3, pipeNo, E_R2Y_BTC_HIST_RGBTBL_B, &tchsFlg, tchsBAddr);
	Ddim_Print((CtImR2y37series_FUNC_NAME "0x%x\n", ercd));
	if(tchsFlg.B != 0){
		Ddim_Print((CtImR2y37series_FUNC_NAME "TCHS B overflow\n"));
	}
	for(loopcnt = 0; loopcnt < 64; loopcnt++){
		Ddim_Print((CtImR2y37series_FUNC_NAME "TCHSBDATA[%x] = 0x%x\n", loopcnt, *tchsBAddr));
		tchsBAddr++;
	}
#else
	im_r2y_proc_waitend(self->imR2yProc, NULL, flgptn, 60 * 10);
	im_r2y_proc_stop(self->imR2yProc, pipeNo);
	im_r2y_ctrl3_get_histogram_before_tone(self->imR2yCtrl3, pipeNo, E_R2Y_BTC_HIST_RGBTBL_Y, &tchsFlg, tchsYAddr);
	im_r2y_ctrl3_get_histogram_before_tone(self->imR2yCtrl3, pipeNo, E_R2Y_BTC_HIST_RGBTBL_R, &tchsFlg, tchsRAddr);
	im_r2y_ctrl3_get_histogram_before_tone(self->imR2yCtrl3, pipeNo, E_R2Y_BTC_HIST_RGBTBL_G, &tchsFlg, tchsGAddr);
	im_r2y_ctrl3_get_histogram_before_tone(self->imR2yCtrl3, pipeNo, E_R2Y_BTC_HIST_RGBTBL_B, &tchsFlg, tchsBAddr);
#endif
	ct_im_r2y_classa_print_r2y_common_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_r2y_yyr_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_r2y_yyw_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_r2y_ctrl_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_r2y_ctrl_modesdraminput_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_r2y_ctrl_modedirect_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_resize_rect_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_trimming_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_color_extract_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_hist_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_post_resize_edge0_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_post_resize_edge1_reg(self->ctImR2yClassa);
	ct_im_classb_r2y_print_other_reg(self->ctImR2yClassb);
	ct_im_r2y_classb_print_fr2y_ctrl_reg(self->ctImR2yClassb);
	ct_im_r2y_classb_print_axi_reg(self->ctImR2yClassb);
#ifdef IM_R2Y_STATUS_PRINT
	Ddim_Print((CtImR2y37series_FUNC_NAME "R2Y End Status\n"));
	im_r2y_stat_print_status(self->imR2yStat);
	im_r2y_stat_print_clock_status(self->ctImR2yStat);
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

CtImR2y37series* ct_im_r2y_37series_new(void)
{
	CtImR2y37series* self = k_object_new_with_private(CT_TYPE_IM_R2Y_37SERIES, sizeof(CtImR2y37seriesPrivate));

	return self;
}
