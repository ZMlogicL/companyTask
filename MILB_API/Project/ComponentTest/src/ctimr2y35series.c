/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 梁正明
*@brief : CtImR2y35series
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimr2ytool.h"
#include "ctimr2y3series.h"
#include "ctimr2y31series.h"
#include "ctimr2y35series.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImR2y35series, ct_im_r2y_35series)
#define CT_IM_R2Y_35SERIES_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), \
		CtImR2y35seriesPrivate, CT_TYPE_IM_R2Y_35SERIES))


struct _CtImR2y35seriesPrivate
{

};


static void ct_im_r2y_35series_constructor(CtImR2y35series *self)
{
	CtImR2y35seriesPrivate *priv = CT_IM_R2Y_35SERIES_GET_PRIVATE(self);
	ImR2y *imR2y;

}

static void ct_im_r2y_35series_destructor(CtImR2y35series *self)
{
	//CtImR2y35seriesPrivate *priv = CT_IM_R2Y_35SERIES_GET_PRIVATE(self);
}


/*
 * PUBLIC
 */
#undef 	CtImR2y35series_FUNC_NAME
#define 	CtImR2y35series_FUNC_NAME "ct_im_r2y_35series_0: "
kint32 ct_im_r2y_35series_0(CtImR2y35series *self, kuchar pipeNo)
{
	TImR2yCtrl r2yCtrl = gctImR2yCtrlBase;
	TImR2yCtrlSdramInput r2yCtrlSdramIn = gctImR2yCtrlSdramInRgb16bit;
	TImR2yResizeRect r2yResizeRectParam = gctImR2yResizeRectParamOutYcc444;
	TImR2yInaddrInfo r2yInAddr = gctImR2yInAddrRgb16bit;
	TImR2yOutbankInfo r2yAddr0;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(("%s\n", CtImR2y35series_FUNC_NAME));
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_0] = ImR2y_ENABLE_ON;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_1] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_2] = ImR2y_ENABLE_OFF;
	r2yCtrl.yyw[D_IM_R2Y_YYW_CH_0].yccCcThinSelect = D_IM_R2Y_THIN_OUT_YCC444;
	r2yCtrl.yyw[D_IM_R2Y_YYW_CH_0].planarInterleavedMode = D_IM_R2Y_PORT_PLANAR;
	memset(&r2yAddr0, '\x00', sizeof(r2yAddr0));
	r2yAddr0 = gct_im_r2y_out_addr_ycc444;
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_ctrl_mode_sdram_input(self->imR2y, pipeNo, &r2yCtrlSdramIn);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_set_inaddr_info(self->imR2y, pipeNo, &r2yInAddr);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl);
	im_r2y_ctrl_mode_sdram_input(self->imR2y, pipeNo, &r2yCtrlSdramIn);
	im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam);
	im_r2y_set_inaddr_info(self->imR2y, pipeNo, &r2yInAddr);
	im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
#endif
	ct_im_r2y_classa_set_wb_gain_rgb(self->ctImR2yClassa, pipeNo);
	ct_im_r2y_set_gamma_on(self->ctImR2y, pipeNo);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", 0));
#ifdef IM_R2Y_STATUS_PRINT
	Ddim_Print((CtImR2y35series_FUNC_NAME "Status\n"));
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
	Ddim_Print((CtImR2y35series_FUNC_NAME "R2Y Start\n"));
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_proc_start(self->imR2yProc, pipeNo);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
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
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		flgptn |= D_IM_R2Y1_INT_FLG_YYW0_END;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		flgptn |= D_IM_R2Y2_INT_FLG_YYW0_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_proc_waitend(self->imR2yProc, NULL, flgptn, 60);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_proc_stop(self->imR2yProc, pipeNo);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_proc_waitend(self->imR2yProc, NULL, flgptn, 60);
	im_r2y_proc_stop(self->imR2yProc, pipeNo);
#endif
	ct_im_r2y_classa_print_r2y_ctrl_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_r2y_ctrl_modesdraminput_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_resize_rect_reg(self->ctImR2yClassa);
	ct_im_classb_r2y_print_other_reg(self->ctImR2yClassb);
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y35series_FUNC_NAME
#define 	CtImR2y35series_FUNC_NAME "ct_im_r2y_35series_1: "
kint32 ct_im_r2y_35series_1(CtImR2y35series *self, kuchar pipeNo)
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

	Ddim_Print(("%s\n", CtImR2y35series_FUNC_NAME));
	r2yCtrl.yyw[D_IM_R2Y_YYW_CH_0].yccCcThinSelect = D_IM_R2Y_THIN_OUT_YCC422_ODD;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_0] = ImR2y_ENABLE_ON;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_1] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_2] = ImR2y_ENABLE_OFF;
	memset(&r2yAddr0, '\x00', sizeof(r2yAddr0));
	r2yAddr0 = gctImR2yOutAddrYcc422;
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_ctrl_mode_sdram_input(self->imR2y, pipeNo, &r2yCtrlSdramIn);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_set_inaddr_info(self->imR2y, pipeNo, &r2yInAddr);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl);
	im_r2y_ctrl_mode_sdram_input(self->imR2y, pipeNo, &r2yCtrlSdramIn);
	im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam);
	im_r2y_set_inaddr_info(self->imR2y, pipeNo, &r2yInAddr);
	im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
#endif
	ct_im_r2y_classa_set_wb_gain_rgb(self->ctImR2yClassa, pipeNo);
	ct_im_r2y_set_gamma_on(self->ctImR2y, pipeNo);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", 0));
#ifdef IM_R2Y_STATUS_PRINT
	Ddim_Print((CtImR2y35series_FUNC_NAME "Status\n"));
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
	Ddim_Print((CtImR2y35series_FUNC_NAME "R2Y Start\n"));
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_proc_start(self->imR2yProc, pipeNo);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
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
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		flgptn |= D_IM_R2Y1_INT_FLG_YYW0_END;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		flgptn |= D_IM_R2Y2_INT_FLG_YYW0_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_proc_waitend(self->imR2yProc, NULL, flgptn, 60);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_proc_stop(self->imR2yProc, pipeNo);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_proc_waitend(self->imR2yProc, NULL, flgptn, 60);
	im_r2y_proc_stop(self->imR2yProc, pipeNo);
#endif
	ct_im_r2y_classa_print_r2y_ctrl_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_r2y_ctrl_modesdraminput_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_resize_rect_reg(self->ctImR2yClassa);
	ct_im_classb_r2y_print_other_reg(self->ctImR2yClassb);
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y35series_FUNC_NAME
#define 	CtImR2y35series_FUNC_NAME "ct_im_r2y_35series_2: "
kint32 ct_im_r2y_35series_2(CtImR2y35series *self, kuchar pipeNo)
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

	Ddim_Print(("%s\n", CtImR2y35series_FUNC_NAME));
	r2yCtrl.yyw[D_IM_R2Y_YYW_CH_0].yccCcThinSelect = D_IM_R2Y_THIN_OUT_YCC422_CENTER;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_0] = ImR2y_ENABLE_ON;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_1] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_2] = ImR2y_ENABLE_OFF;
	memset(&r2yAddr0, '\x00', sizeof(r2yAddr0));
	r2yAddr0 = gctImR2yOutAddrYcc422;
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_ctrl_mode_sdram_input(self->imR2y, pipeNo, &r2yCtrlSdramIn);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_set_inaddr_info(self->imR2y, pipeNo, &r2yInAddr);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl);
	im_r2y_ctrl_mode_sdram_input(self->imR2y, pipeNo, &r2yCtrlSdramIn);
	im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam);
	im_r2y_set_inaddr_info(self->imR2y, pipeNo, &r2yInAddr);
	im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
#endif
	ct_im_r2y_classa_set_wb_gain_rgb(self->ctImR2yClassa, pipeNo);
	ct_im_r2y_set_gamma_on(self->ctImR2y, pipeNo);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", 0));
#ifdef IM_R2Y_STATUS_PRINT
	Ddim_Print((CtImR2y35series_FUNC_NAME "Status\n"));
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
	Ddim_Print((CtImR2y35series_FUNC_NAME "R2Y Start\n"));
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_proc_start(self->imR2yProc, pipeNo);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
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
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		flgptn |= D_IM_R2Y1_INT_FLG_YYW0_END;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		flgptn |= D_IM_R2Y2_INT_FLG_YYW0_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_proc_waitend(self->imR2yProc, NULL, flgptn, 60);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_proc_stop(self->imR2yProc, pipeNo);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_proc_waitend(self->imR2yProc, NULL, flgptn, 60);
	im_r2y_proc_stop(self->imR2yProc, pipeNo);
#endif
	ct_im_r2y_classa_print_r2y_ctrl_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_r2y_ctrl_modesdraminput_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_resize_rect_reg(self->ctImR2yClassa);
	ct_im_classb_r2y_print_other_reg(self->ctImR2yClassb);
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y35series_FUNC_NAME
#define 	CtImR2y35series_FUNC_NAME "ct_im_r2y_35series_3: "
kint32 ct_im_r2y_35series_3(CtImR2y35series *self, kuchar pipeNo)
{
	TImR2yCtrl r2yCtrl = gctImR2yCtrlBase;
	TImR2yCtrlSdramInput r2yCtrlSdramIn = gctImR2yCtrlSdramInRgb16bit;
	TImR2yResizeRect r2yResizeRectParam = gctImR2yResizeRectParamOutYcc420;
	TImR2yInaddrInfo r2yInAddr = gctImR2yInAddrRgb16bit;
	TImR2yOutbankInfo r2yAddr0;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(("%s\n", CtImR2y35series_FUNC_NAME));
	r2yCtrl.yyw[D_IM_R2Y_YYW_CH_0].yccCcThinSelect = D_IM_R2Y_THIN_OUT_YCC420_ODD;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_0] = ImR2y_ENABLE_ON;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_1] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_2] = ImR2y_ENABLE_OFF;
	memset(&r2yAddr0, '\x00', sizeof(r2yAddr0));
	r2yAddr0 = gctImR2yOutAddrYcc420;
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_ctrl_mode_sdram_input(self->imR2y, pipeNo, &r2yCtrlSdramIn);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_set_inaddr_info(self->imR2y, pipeNo, &r2yInAddr);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl);
	im_r2y_ctrl_mode_sdram_input(self->imR2y, pipeNo, &r2yCtrlSdramIn);
	im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam);
	im_r2y_set_inaddr_info(self->imR2y, pipeNo, &r2yInAddr);
	im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
#endif
	ct_im_r2y_classa_set_wb_gain_rgb(self->ctImR2yClassa, pipeNo);
	ct_im_r2y_set_gamma_on(self->ctImR2y, pipeNo);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", 0));
#ifdef IM_R2Y_STATUS_PRINT
	Ddim_Print((CtImR2y35series_FUNC_NAME "Status\n"));
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
	Ddim_Print((CtImR2y35series_FUNC_NAME "R2Y Start\n"));
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_proc_start(self->imR2yProc, pipeNo);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
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
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		flgptn |= D_IM_R2Y1_INT_FLG_YYW0_END;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		flgptn |= D_IM_R2Y2_INT_FLG_YYW0_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_proc_waitend(self->imR2yProc, NULL, flgptn, 60);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_proc_stop(self->imR2yProc, pipeNo);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_proc_waitend(self->imR2yProc, NULL, flgptn, 60);
	im_r2y_proc_stop(self->imR2yProc, pipeNo);
#endif
	ct_im_r2y_classa_print_r2y_ctrl_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_r2y_ctrl_modesdraminput_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_resize_rect_reg(self->ctImR2yClassa);
	ct_im_classb_r2y_print_other_reg(self->ctImR2yClassb);
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y35series_FUNC_NAME
#define 	CtImR2y35series_FUNC_NAME "ct_im_r2y_35series_4: "
kint32 ct_im_r2y_35series_4(CtImR2y35series *self, kuchar pipeNo)
{
	TImR2yCtrl r2yCtrl = gctImR2yCtrlBase;
	TImR2yCtrlSdramInput r2yCtrlSdramIn = gctImR2yCtrlSdramInRgb16bit;
	TImR2yResizeRect r2yResizeRectParam = gctImR2yResizeRectParamOutYcc420;
	TImR2yInaddrInfo r2yInAddr = gctImR2yInAddrRgb16bit;
	TImR2yOutbankInfo r2yAddr0;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(("%s\n", CtImR2y35series_FUNC_NAME));
	r2yCtrl.yyw[D_IM_R2Y_YYW_CH_0].yccCcThinSelect = D_IM_R2Y_THIN_OUT_YCC420_CENTER_LEFT;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_0] = ImR2y_ENABLE_ON;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_1] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_2] = ImR2y_ENABLE_OFF;
	memset(&r2yAddr0, '\x00', sizeof(r2yAddr0));
	r2yAddr0 = gctImR2yOutAddrYcc420;
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_ctrl_mode_sdram_input(self->imR2y, pipeNo, &r2yCtrlSdramIn);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_set_inaddr_info(self->imR2y, pipeNo, &r2yInAddr);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl);
	im_r2y_ctrl_mode_sdram_input(self->imR2y, pipeNo, &r2yCtrlSdramIn);
	im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam);
	im_r2y_set_inaddr_info(self->imR2y, pipeNo, &r2yInAddr);
	im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
#endif
	ct_im_r2y_classa_set_wb_gain_rgb(self->ctImR2yClassa, pipeNo);
	ct_im_r2y_set_gamma_on(self->ctImR2y, pipeNo);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", 0));
#ifdef IM_R2Y_STATUS_PRINT
	Ddim_Print((CtImR2y35series_FUNC_NAME "Status\n"));
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
	Ddim_Print((CtImR2y35series_FUNC_NAME "R2Y Start\n"));
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_proc_start(self->imR2yProc, pipeNo);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
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
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		flgptn |= D_IM_R2Y1_INT_FLG_YYW0_END;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		flgptn |= D_IM_R2Y2_INT_FLG_YYW0_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_proc_waitend(self->imR2yProc, NULL, flgptn, 60);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_proc_stop(self->imR2yProc, pipeNo);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_proc_waitend(self->imR2yProc, NULL, flgptn, 60);
	im_r2y_proc_stop(self->imR2yProc, pipeNo);
#endif
	ct_im_r2y_classa_print_r2y_ctrl_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_r2y_ctrl_modesdraminput_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_resize_rect_reg(self->ctImR2yClassa);
	ct_im_classb_r2y_print_other_reg(self->ctImR2yClassb);
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y35series_FUNC_NAME
#define 	CtImR2y35series_FUNC_NAME "ct_im_r2y_35series_5: "
kint32 ct_im_r2y_35series_5(CtImR2y35series *self, kuchar pipeNo)
{
	TImR2yCtrl r2yCtrl = gctImR2yCtrlBase;
	TImR2yCtrlSdramInput r2yCtrlSdramIn = gctImR2yCtrlSdramInRgb16bit;
	TImR2yResizeRect r2yResizeRectParam = gctImR2yResizeRectParamOutYcc420;
	TImR2yInaddrInfo r2yInAddr = gctImR2yInAddrRgb16bit;
	TImR2yOutbankInfo r2yAddr0;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(("%s\n", CtImR2y35series_FUNC_NAME));
	r2yCtrl.yyw[D_IM_R2Y_YYW_CH_0].yccCcThinSelect = D_IM_R2Y_THIN_OUT_YCC420_CENTER;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_0] = ImR2y_ENABLE_ON;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_1] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[D_IM_R2Y_YYW_CH_2] = ImR2y_ENABLE_OFF;
	memset(&r2yAddr0, '\x00', sizeof(r2yAddr0));
	r2yAddr0 = gctImR2yOutAddrYcc420;
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_ctrl_mode_sdram_input(self->imR2y, pipeNo, &r2yCtrlSdramIn);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_set_inaddr_info(self->imR2y, pipeNo, &r2yInAddr);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl);
	im_r2y_ctrl_mode_sdram_input(self->imR2y, pipeNo, &r2yCtrlSdramIn);
	im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam);
	im_r2y_set_inaddr_info(self->imR2y, pipeNo, &r2yInAddr);
	im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
#endif
	ct_im_r2y_classa_set_wb_gain_rgb(self->ctImR2yClassa, pipeNo);
	ct_im_r2y_set_gamma_on(self->ctImR2y, pipeNo);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", 0));
#ifdef IM_R2Y_STATUS_PRINT
	Ddim_Print((CtImR2y35series_FUNC_NAME "Status\n"));
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
	Ddim_Print((CtImR2y35series_FUNC_NAME "R2Y Start\n"));
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_proc_start(self->imR2yProc, pipeNo);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
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
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		flgptn |= D_IM_R2Y1_INT_FLG_YYW0_END;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		flgptn |= D_IM_R2Y2_INT_FLG_YYW0_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_proc_waitend(self->imR2yProc, NULL, flgptn, 60);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_proc_stop(self->imR2yProc, pipeNo);
	Ddim_Print((CtImR2y35series_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_proc_waitend(self->imR2yProc, NULL, flgptn, 60);
	im_r2y_proc_stop(self->imR2yProc, pipeNo);
#endif
	ct_im_r2y_classa_print_r2y_ctrl_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_r2y_ctrl_modesdraminput_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_resize_rect_reg(self->ctImR2yClassa);
	ct_im_classb_r2y_print_other_reg(self->ctImR2yClassb);
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y35series_FUNC_NAME
#define 	CtImR2y35series_FUNC_NAME "ct_im_r2y_35series_6: "
kint32 ct_im_r2y_35series_6(CtImR2y35series *self, kuchar pipeNo)
{
	Ddim_Print(("%s\n", CtImR2y35series_FUNC_NAME));

	return ct_im_r2y_35series_0(self->ctImR2y35series, pipeNo);
}

#undef 	CtImR2y35series_FUNC_NAME
#define 	CtImR2y35series_FUNC_NAME "ct_im_r2y_35series_7: "
kint32 ct_im_r2y_35series_7(CtImR2y35series *self, kuchar pipeNo)
{
	Ddim_Print(("%s\n", CtImR2y35series_FUNC_NAME));

	return ct_im_r2y_3series_1(self->ctImR2y3series, pipeNo);
}

#undef 	CtImR2y35series_FUNC_NAME
#define 	CtImR2y35series_FUNC_NAME "ct_im_r2y_35series_8: "
kint32 ct_im_r2y_35series_8(CtImR2y35series *self, kuchar pipeNo)
{
	Ddim_Print(("%s\n", CtImR2y35series_FUNC_NAME));

	return ct_im_r2y_31series_4(self->ctImR2y31series, pipeNo);
}

#undef 	CtImR2y35series_FUNC_NAME
#define 	CtImR2y35series_FUNC_NAME "ct_im_r2y_35series_9: "
kint32 ct_im_r2y_35series_9(CtImR2y35series *self, kuchar pipeNo)
{
	Ddim_Print(("%s\n", CtImR2y35series_FUNC_NAME));

	return ct_im_r2y_31series_5(self->ctImR2y31series, pipeNo);
}


CtImR2y35series* ct_im_r2y_35series_new(void)
{
	CtImR2y35series* self = k_object_new_with_private(CT_TYPE_IM_R2Y_35SERIES, sizeof(CtImR2y35seriesPrivate));

	return self;
}
