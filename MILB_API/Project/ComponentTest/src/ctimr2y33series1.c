/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 梁正明
*@brief : CtImR2y33series1
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimr2ytool.h"
#include "ctimr2y33series1.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImR2y33series1, ct_im_r2y_33series1)
#define CT_IM_R2Y_33SERIES1_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), \
		CtImR2y33series1Private, CT_TYPE_IM_R2Y_33SERIES1))


struct _CtImR2y33series1Private
{

};


static void ct_im_r2y_33series1_constructor(CtImR2y33series1 *self)
{
	CtImR2y33series1Private *priv = CT_IM_R2Y_33SERIES1_GET_PRIVATE(self);
	self->ctImR2y = ct_im_t2y_new();
	self->ctImR2yClassa = ct_im_r2y_classa_new();
	self->ctImR2yClassb = ct_im_r2y_classb_new();
	self->imR2y = im_r2y_new();
	self->imR2y2 = im_r2y2_new();
	self->imR2y3 = im_r2y3_new();
	self->imR2yProc = im_r2y3_proc_new();
	self->imR2yStat = im_r2y_stat_new();
}

static void ct_im_r2y_33series1_destructor(CtImR2y33series1 *self)
{
	CtImR2y33series1Private *priv = CT_IM_R2Y_33SERIES1_GET_PRIVATE(self);
				if(self->ctImR2y){
										k_object_unref(self->ctImR2y);
										self->ctImR2y=NULL;
									}

				if(self->ctImR2yClassa){
					k_object_unref(self->ctImR2yClassa);
					self->ctImR2yClassa=NULL;
				}

				if(self->ctImR2yClassb){
						k_object_unref(self->ctImR2yClassb);
						self->ctImR2yClassb=NULL;
					}
				if(self->imR2y){
										k_object_unref(self->imR2y);
										self->imR2y=NULL;
									}

				if(self->imR2y2){
					k_object_unref(self->imR2y2);
					self->imR2y2=NULL;
				}

				if(self->imR2y3){
						k_object_unref(self->imR2y3);
						self->imR2y3=NULL;
					}

				if(self->imR2yProc){
									k_object_unref(self->imR2yProc);
									self->imR2yProc=NULL;
								}
}

#undef 	CtImR2y33series1_FUNC_NAME
#define 	CtImR2y33series1_FUNC_NAME "ct_im_r2y_33series1_5: "
kint32 ct_im_r2y_33series1_5(CtImR2y33series1 *self, kuchar pipeNo)
{
	TImR2yCtrl r2yCtrl = gctImR2yCtrlBase;
	TImR2yResizeRect r2yResizeRectParam = gctImR2yResizeRectParamOutYcc422;
	TImR2yCtrlDirect r2yCtrlDirect;
	TImR2yOutbankInfo r2yAddr0;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(("%s\n", CtImR2y33series1_FUNC_NAME));
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_0] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_1] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_2] = ImR2y_ENABLE_ON;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_2].yywWidth = D_IM_R2Y_SRC_IMG_PIXS_WIDTH / 2;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_2].yywLines = D_IM_R2Y_SRC_IMG_PIXS_LINES / 2;
	r2yCtrlDirect.frameStop = 1;
	memset(&r2yAddr0, '\x00', sizeof(r2yAddr0));
	r2yAddr0 = gctImR2yOutAddrYcc422;
	ct_im_r2y_classa_set_b2r(self->ctImR2yClassa, pipeNo);
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y3_ctrl_mode_direct(self->imR2y3,  pipeNo, &r2yCtrlDirect);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_2, &r2yAddr0);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl);
	ercd = im_r2y3_ctrl_mode_direct(self->imR2y3,  pipeNo, &r2yCtrlDirect);
	im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam);
	im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_2, &r2yAddr0);
#endif
	ct_im_r2y_classa_set_wb_gain_rgb(self->ctImR2yClassa, pipeNo);
	ct_im_r2y_set_gamma_on(self->ctImR2y, pipeNo);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", 0));
#ifdef IM_R2Y_STATUS_PRINT
	Ddim_Print((CtImR2y33series1_FUNC_NAME "Status\n"));
	im_r2y_stat_print_status(self->imR2yStat);
#endif
#ifdef D_IM_R2Y_DEBUG_ON_PC
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		gimR2yMacroFakeFinish[0] = 1;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		gimR2yMacroFakeFinish[1] = 1;
	}
#endif
	Ddim_Print((CtImR2y33series1_FUNC_NAME "R2Y Start\n"));
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_proc_start(self->imR2yProc, pipeNo);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_proc_start(self->imR2yProc, pipeNo);
#endif
#ifdef D_IM_R2Y_DEBUG_ON_PC
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		gimR2yMacroFakeFinish[0] = 0;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		gimR2yMacroFakeFinish[1] = 0;
	}
#endif
	ct_im_r2y_classa_start_b2r(self->ctImR2yClassa, pipeNo);
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		flgptn |= D_IM_R2Y1_INT_FLG_YYW2_END;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		flgptn |= D_IM_R2Y2_INT_FLG_YYW2_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_proc_waitend(self->imR2yProc, NULL, flgptn, 60);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_proc_stop(self->imR2yProc, pipeNo);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_proc_waitend(self->imR2yProc, NULL, flgptn, 60);
	im_r2y_proc_stop(self->imR2yProc, pipeNo);
#endif
	ct_im_r2y_waitend_stop_b2r(pipeNo);
	ct_im_r2y_classa_print_r2y_ctrl_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_r2y_ctrl_modedirect_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_resize_rect_reg(self->ctImR2yClassa);
	ct_im_classb_r2y_print_other_reg(self->ctImR2yClassb);
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y33series1_FUNC_NAME
#define 	CtImR2y33series1_FUNC_NAME "ct_im_r2y_33series1_6: "
kint32 ct_im_r2y_33series1_6(CtImR2y33series1 *self, kuchar pipeNo)
{
	TImR2yCtrl r2yCtrl = gctImR2yCtrlBase;
	TImR2yResizeRect r2yResizeRectParam = gctImR2yResizeRectParamOutYcc422;
	TImR2yCtrlDirect r2yCtrlDirect;
	TImR2yCtrlTrimming r2yCtrlTrimming;
	TImR2yOutbankInfo r2yAddr0;
	TImR2yOutbankInfo r2yAddr0a;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(("%s\n", CtImR2y33series1_FUNC_NAME));
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_0] = ImR2y_ENABLE_ON;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_1] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_2] = ImR2y_ENABLE_OFF;
	r2yCtrl.outputMode0a = D_IM_R2Y_YYW0A_OUTPUT_MODE_DIV_32_SP;
	r2yResizeRectParam.inputSize.imgWidth = 1280;
	r2yResizeRectParam.inputSize.imgLines = 960;
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
	r2yCtrlDirect.frameStop = 1;
	memset(&r2yAddr0, '\x00', sizeof(r2yAddr0));
	r2yAddr0 = gctImR2yOutAddrYcc422;
	memset(&r2yAddr0a, '\x00', sizeof(r2yAddr0a));
	r2yAddr0a.outputAddr[ImR2y_YYW_BANK_0].ycc.addrY = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_Y_ADDR_TOP_1;
	r2yAddr0a.outputAddr[ImR2y_YYW_BANK_0].ycc.addrCb = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_CB_ADDR_TOP_1;
	r2yAddr0a.outputAddr[ImR2y_YYW_BANK_0].ycc.addrCr = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_CR_ADDR_TOP_1;
	ct_im_r2y_classa_set_b2r(self->ctImR2yClassa, pipeNo);
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y3_ctrl_mode_direct(self->imR2y3,  pipeNo, &r2yCtrlDirect);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y3_ctrl_trimming(self->imR2y3, pipeNo, D_IM_R2Y_YYW_CH_0, &r2yCtrlTrimming);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0A, &r2yAddr0a);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl);
	ercd = im_r2y3_ctrl_mode_direct(self->imR2y3,  pipeNo, &r2yCtrlDirect);
	im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam);
	im_r2y3_ctrl_trimming(self->imR2y3, pipeNo, D_IM_R2Y_YYW_CH_0, &r2yCtrlTrimming);
	im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
	im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0A, &r2yAddr0a);
#endif
	ct_im_r2y_classa_set_wb_gain_rgb(self->ctImR2yClassa, pipeNo);
	ct_im_r2y_set_gamma_on(self->ctImR2y, pipeNo);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", 0));
#ifdef IM_R2Y_STATUS_PRINT
	Ddim_Print((CtImR2y33series1_FUNC_NAME "Status\n"));
	im_r2y_stat_print_status(self->imR2yStat);
#endif
#ifdef D_IM_R2Y_DEBUG_ON_PC
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		gimR2yMacroFakeFinish[0] = 1;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		gimR2yMacroFakeFinish[1] = 1;
	}
#endif
	Ddim_Print((CtImR2y33series1_FUNC_NAME "R2Y Start\n"));
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_proc_start(self->imR2yProc, pipeNo);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_proc_start(self->imR2yProc, pipeNo);
#endif
#ifdef D_IM_R2Y_DEBUG_ON_PC
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		gimR2yMacroFakeFinish[0] = 0;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		gimR2yMacroFakeFinish[1] = 0;
	}
#endif
	ct_im_r2y_classa_start_b2r(self->ctImR2yClassa, pipeNo);
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		flgptn |= D_IM_R2Y1_INT_FLG_YYW0_END;
		flgptn |= D_IM_R2Y1_INT_FLG_YYW0A_END;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		flgptn |= D_IM_R2Y2_INT_FLG_YYW0_END;
		flgptn |= D_IM_R2Y2_INT_FLG_YYW0A_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_proc_waitend(self->imR2yProc, NULL, flgptn, 60);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", ercd));

	ercd = im_r2y_proc_stop(self->imR2yProc, pipeNo);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_proc_waitend(self->imR2yProc, NULL, flgptn, 60);
	im_r2y_proc_stop(self->imR2yProc, pipeNo);
#endif
	ct_im_r2y_waitend_stop_b2r(pipeNo);
	ct_im_r2y_classa_print_r2y_ctrl_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_r2y_ctrl_modedirect_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_resize_rect_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_trimming_reg(self->ctImR2yClassa);
	ct_im_classb_r2y_print_other_reg(self->ctImR2yClassb);
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y33series1_FUNC_NAME
#define 	CtImR2y33series1_FUNC_NAME "ct_im_r2y_33series1_7: "
kint32 ct_im_r2y_33series1_7(CtImR2y33series1 *self, kuchar pipeNo)
{
	TImR2yCtrl r2yCtrl = gctImR2yCtrlBase;
	TImR2yResizeRect r2yResizeRectParam = gctImR2yResizeRectParamOutYcc422;
	TImR2yCtrlDirect r2yCtrlDirect;
	TImR2yOutbankInfo r2yAddr0;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(("%s\n", CtImR2y33series1_FUNC_NAME));
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_0] = ImR2y_ENABLE_ON;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_1] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_2] = ImR2y_ENABLE_OFF;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].yywWidth = D_IM_R2Y_SRC_IMG_PIXS_WIDTH / 2;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].yywLines = D_IM_R2Y_SRC_IMG_PIXS_LINES / 2;
	r2yCtrlDirect.frameStop = 1;
	memset(&r2yAddr0, '\x00', sizeof(r2yAddr0));
	r2yAddr0 = gctImR2yOutAddrYcc422;
	ct_im_r2y_classa_set_ltm(self->ctImR2yClassa, pipeNo);
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y3_ctrl_mode_direct(self->imR2y3,  pipeNo, &r2yCtrlDirect);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl);
	ercd = im_r2y3_ctrl_mode_direct(self->imR2y3,  pipeNo, &r2yCtrlDirect);
	im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam);
	im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
#endif
	ct_im_r2y_classa_set_wb_gain_rgb(self->ctImR2yClassa, pipeNo);
	ct_im_r2y_set_gamma_on(self->ctImR2y, pipeNo);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", 0));
#ifdef IM_R2Y_STATUS_PRINT
	Ddim_Print((CtImR2y33series1_FUNC_NAME "Status\n"));
	im_r2y_stat_print_status(self->imR2yStat);
#endif
#ifdef D_IM_R2Y_DEBUG_ON_PC
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		gimR2yMacroFakeFinish[0] = 1;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		gimR2yMacroFakeFinish[1] = 1;
	}
#endif
	Ddim_Print((CtImR2y33series1_FUNC_NAME "R2Y Start\n"));
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_proc_start(self->imR2yProc, pipeNo);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_proc_start(self->imR2yProc, pipeNo);
#endif
#ifdef D_IM_R2Y_DEBUG_ON_PC
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		gimR2yMacroFakeFinish[0] = 0;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		gimR2yMacroFakeFinish[1] = 0;
	}
#endif
	ct_im_r2y_classa_start_ltm(self->ctImR2yClassa, pipeNo);
	ct_im_r2y_classa_waitend_stop_ltm(self->ctImR2yClassa, pipeNo);
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		flgptn |= D_IM_R2Y1_INT_FLG_YYW0_END;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		flgptn |= D_IM_R2Y2_INT_FLG_YYW0_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_proc_waitend(self->imR2yProc, NULL, flgptn, 60);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_proc_stop(self->imR2yProc, pipeNo);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_proc_waitend(self->imR2yProc, NULL, flgptn, 60);
	im_r2y_proc_stop(self->imR2yProc, pipeNo);
#endif
	ct_im_r2y_classa_print_r2y_ctrl_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_r2y_ctrl_modedirect_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_resize_rect_reg(self->ctImR2yClassa);
	ct_im_classb_r2y_print_other_reg(self->ctImR2yClassb);
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y33series1_FUNC_NAME
#define 	CtImR2y33series1_FUNC_NAME "ct_im_r2y_33series1_8: "
kint32 ct_im_r2y_33series1_8(CtImR2y33series1 *self, kuchar pipeNo)
{
	TImR2yCtrl r2yCtrl = gctImR2yCtrlBase;
	TImR2yResizeRect r2yResizeRectParam = gctImR2yResizeRectParamOutYcc422;
	TImR2yCtrlDirect r2yCtrlDirect;
	TImR2yOutbankInfo r2yAddr0;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	Ddim_Print(("%s\n", CtImR2y33series1_FUNC_NAME));
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_0] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_1] = ImR2y_ENABLE_ON;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_2] = ImR2y_ENABLE_OFF;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_1].yywWidth = D_IM_R2Y_SRC_IMG_PIXS_WIDTH / 2;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_1].yywLines = D_IM_R2Y_SRC_IMG_PIXS_LINES / 2;
	r2yCtrlDirect.frameStop = 1;
	memset(&r2yAddr0, '\x00', sizeof(r2yAddr0));
	r2yAddr0 = gctImR2yOutAddrYcc422;
	ct_im_r2y_classa_set_ltm(self->ctImR2yClassa, pipeNo);
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y3_ctrl_mode_direct(self->imR2y3,  pipeNo, &r2yCtrlDirect);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_1, &r2yAddr0);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl);
	ercd = im_r2y3_ctrl_mode_direct(self->imR2y3,  pipeNo, &r2yCtrlDirect);
	im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam);
	im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_1, &r2yAddr0);
#endif
	ct_im_r2y_classa_set_wb_gain_rgb(self->ctImR2yClassa, pipeNo);
	ct_im_r2y_set_gamma_on(self->ctImR2y, pipeNo);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", 0));
#ifdef IM_R2Y_STATUS_PRINT
	Ddim_Print((CtImR2y33series1_FUNC_NAME "Status\n"));
	im_r2y_stat_print_status(self->imR2yStat);
#endif
#ifdef D_IM_R2Y_DEBUG_ON_PC
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		gimR2yMacroFakeFinish[0] = 1;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		gimR2yMacroFakeFinish[1] = 1;
	}
#endif
	Ddim_Print((CtImR2y33series1_FUNC_NAME "R2Y Start\n"));
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_proc_start(self->imR2yProc, pipeNo);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_proc_start(self->imR2yProc, pipeNo);
#endif
#ifdef D_IM_R2Y_DEBUG_ON_PC
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		gimR2yMacroFakeFinish[0] = 0;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		gimR2yMacroFakeFinish[1] = 0;
	}
#endif
	ct_im_r2y_classa_start_ltm(self->ctImR2yClassa, pipeNo);
	ct_im_r2y_classa_waitend_stop_ltm(self->ctImR2yClassa, pipeNo);
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		flgptn |= D_IM_R2Y1_INT_FLG_YYW1_END;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		flgptn |= D_IM_R2Y2_INT_FLG_YYW1_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_proc_waitend(self->imR2yProc, NULL, flgptn, 60);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_proc_stop(self->imR2yProc, pipeNo);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_proc_waitend(self->imR2yProc, NULL, flgptn, 60);
	im_r2y_proc_stop(self->imR2yProc, pipeNo);
#endif
	ct_im_r2y_classa_print_r2y_ctrl_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_r2y_ctrl_modedirect_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_resize_rect_reg(self->ctImR2yClassa);
	ct_im_classb_r2y_print_other_reg(self->ctImR2yClassb);
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y33series1_FUNC_NAME
#define 	CtImR2y33series1_FUNC_NAME "ct_im_r2y_33series1_9: "
kint32 ct_im_r2y_33series1_9(CtImR2y33series1 *self, kuchar pipeNo)
{
	TImR2yCtrl r2yCtrl = gctImR2yCtrlBase;
	TImR2yResizeRect r2yResizeRectParam = gctImR2yResizeRectParamOutYcc422;
	TImR2yCtrlDirect r2yCtrlDirect;
	TImR2yOutbankInfo r2yAddr0;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(("%s\n", CtImR2y33series1_FUNC_NAME));
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_0] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_1] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_2] = ImR2y_ENABLE_ON;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_2].yywWidth = D_IM_R2Y_SRC_IMG_PIXS_WIDTH / 2;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_2].yywLines = D_IM_R2Y_SRC_IMG_PIXS_LINES / 2;
	r2yCtrlDirect.frameStop = 1;
	memset(&r2yAddr0, '\x00', sizeof(r2yAddr0));
	r2yAddr0 = gctImR2yOutAddrYcc422;
	ct_im_r2y_classa_set_ltm(self->ctImR2yClassa, pipeNo);
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y3_ctrl_mode_direct(self->imR2y3,  pipeNo, &r2yCtrlDirect);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_2, &r2yAddr0);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl);
	ercd = im_r2y3_ctrl_mode_direct(self->imR2y3,  pipeNo, &r2yCtrlDirect);
	im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam);
	im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_2, &r2yAddr0);
#endif
	ct_im_r2y_classa_set_wb_gain_rgb(self->ctImR2yClassa, pipeNo);
	ct_im_r2y_set_gamma_on(self->ctImR2y, pipeNo);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", 0));
#ifdef IM_R2Y_STATUS_PRINT
	Ddim_Print((CtImR2y33series1_FUNC_NAME "Status\n"));
	im_r2y_stat_print_status(self->imR2yStat);
#endif
#ifdef D_IM_R2Y_DEBUG_ON_PC
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		gimR2yMacroFakeFinish[0] = 1;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		gimR2yMacroFakeFinish[1] = 1;
	}
#endif
	Ddim_Print((CtImR2y33series1_FUNC_NAME "R2Y Start\n"));
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_proc_start(self->imR2yProc, pipeNo);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_proc_start(self->imR2yProc, pipeNo);
#endif
#ifdef D_IM_R2Y_DEBUG_ON_PC
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		gimR2yMacroFakeFinish[0] = 0;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		gimR2yMacroFakeFinish[1] = 0;
	}
#endif
	ct_im_r2y_classa_start_ltm(self->ctImR2yClassa, pipeNo);
	ct_im_r2y_classa_waitend_stop_ltm(self->ctImR2yClassa, pipeNo);
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		flgptn |= D_IM_R2Y1_INT_FLG_YYW2_END;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		flgptn |= D_IM_R2Y2_INT_FLG_YYW2_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_proc_waitend(self->imR2yProc, NULL, flgptn, 60);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_proc_stop(self->imR2yProc, pipeNo);
	Ddim_Print((CtImR2y33series1_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_proc_waitend(self->imR2yProc, NULL, flgptn, 60);
	im_r2y_proc_stop(self->imR2yProc, pipeNo);
#endif
	ct_im_r2y_classa_print_r2y_ctrl_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_r2y_ctrl_modedirect_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_resize_rect_reg(self->ctImR2yClassa);
	ct_im_classb_r2y_print_other_reg(self->ctImR2yClassb);
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

CtImR2y33series1* ct_im_r2y_33series1_new(void)
{
	CtImR2y33series1* self = k_object_new_with_private(CT_TYPE_IM_R2Y_33SERIES1, sizeof(CtImR2y33series1Private));

	return self;
}
