/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 梁正明
*@brief : CtImR2y2series
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimr2ytool.h"
#include "ctimr2y2series.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImR2y2series, ct_im_r2y_2series)
#define CT_IM_R2Y_2SERIES_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), \
		CtImR2y2seriesPrivate, CT_TYPE_IM_R2Y_2SERIES))


struct _CtImR2y2seriesPrivate
{

};


/*
 * IMPL
 */
static void ct_im_r2y_2series_constructor(CtImR2y2series *self)
{
	CtImR2y2seriesPrivate *priv = CT_IM_R2Y_2SERIES_GET_PRIVATE(self);
	self->ctImR2y2series = ct_im_r2y_2series_new();
	self->imR2y = im_r2y_new();
	self->imR2y2 = im_r2y2_new();
	self->imR2y3 = im_r2y3_new();
	self->imR2yProc = im_r2y_proc_new();
	self->imR2yStat = im_r2y_stat_new();
}

static void ct_im_r2y_2series_destructor(CtImR2y2series *self)
{
	CtImR2y2seriesPrivate *priv = CT_IM_R2Y_2SERIES_GET_PRIVATE(self);
			if(self->imR2yStat){
				k_object_unref(self->imR2yStat);
				self->imR2yStat=NULL;
			}

			if(self->ctImR2y2series){
				k_object_unref(self->ctImR2y2series);
				self->ctImR2y2series=NULL;
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


/*
 * PUBLIC
 */
#undef 	CtImR2y2series_FUNC_NAME
#define 	CtImR2y2series_FUNC_NAME "ct_im_r2y_2series_1: "
kint32 ct_im_r2y_2series_1(CtImR2y2series *self, kuchar pipeNo)
{
	TImR2yCtrl r2yCtrl = gctImR2yCtrlBase;
	TImR2yResizeRect r2yResizeRectParam;
	TImR2yInaddrInfo r2yInAddr;
	TImR2yOutbankInfo r2yAddr0;
	kuint32 loopcnt;
	kuchar bankIndex;
	DdimUserFlgptn flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

#ifdef CO_DEBUG_ON_PC
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		ioR2yP1.yyr.yyrtrg.bit.yyrtrg = 2;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		IO_R2Y_P2.yyr.yyrtrg.bit.yyrtrg = 2;
	}
#endif	//CO_DEBUG_ON_PC
	r2yCtrl.yywEnable[ImR2y_YYW_CH_1] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[ImR2y_YYW_CH_2] = ImR2y_ENABLE_OFF;
	r2yResizeRectParam.inputSize.imgTop = 0;
	r2yResizeRectParam.inputSize.imgLeft = 0;
	r2yResizeRectParam.inputSize.imgWidth = D_IM_R2Y_SRC_IMG_PIXS_WIDTH;
	r2yResizeRectParam.inputSize.imgLines = D_IM_R2Y_SRC_IMG_PIXS_LINES;
	r2yResizeRectParam.outputSize[ImR2y_YYW_CH_0].yywWidth = D_IM_R2Y_DST_IMG_PIXS_WIDTH;
	r2yResizeRectParam.outputSize[ImR2y_YYW_CH_0].yywLines = D_IM_R2Y_DST_IMG_PIXS_LINES;
	r2yResizeRectParam.outputSize[ImR2y_YYW_CH_0].outputGlobalW[ImR2y_PORT_Y] =
			D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC422_Y;
	r2yResizeRectParam.outputSize[ImR2y_YYW_CH_0].outputGlobalW[ImR2y_PORT_CB] =
			D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC422_C;
	r2yInAddr.rgb.addrR = (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_U16_R_ADDR_TOP;
	r2yInAddr.rgb.addrG = (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_U16_G_ADDR_TOP;
	r2yInAddr.rgb.addrB = (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_U16_B_ADDR_TOP;
	memset(&r2yAddr0, '\x0', sizeof(r2yAddr0));
	r2yAddr0.bankInitialPosition = ImR2y_YYW_BANK_3;
	r2yAddr0.useBankNum = ImR2y_YYW_BANK_3;
	r2yAddr0.outputAddr[ImR2y_YYW_BANK_0].ycc.addrY = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_Y_ADDR_TOP;
	r2yAddr0.outputAddr[ImR2y_YYW_BANK_0].ycc.addrCb = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_CB_ADDR_TOP;
	r2yAddr0.outputAddr[ImR2y_YYW_BANK_0].ycc.addrCr = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_CR_ADDR_TOP;
	r2yAddr0.outputAddr[ImR2y_YYW_BANK_1].ycc.addrY = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_Y_ADDR_TOP;
	r2yAddr0.outputAddr[ImR2y_YYW_BANK_1].ycc.addrCb = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_CB_ADDR_TOP;
	r2yAddr0.outputAddr[ImR2y_YYW_BANK_1].ycc.addrCr = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_CR_ADDR_TOP;
	r2yAddr0.outputAddr[ImR2y_YYW_BANK_2].ycc.addrY = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_Y_ADDR_TOP;
	r2yAddr0.outputAddr[ImR2y_YYW_BANK_2].ycc.addrCb = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_CB_ADDR_TOP;
	r2yAddr0.outputAddr[ImR2y_YYW_BANK_2].ycc.addrCr = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_CR_ADDR_TOP;
	r2yAddr0.outputAddr[ImR2y_YYW_BANK_3].ycc.addrY = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_Y_ADDR_TOP;
	r2yAddr0.outputAddr[ImR2y_YYW_BANK_3].ycc.addrCb = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_CB_ADDR_TOP;
	r2yAddr0.outputAddr[ImR2y_YYW_BANK_3].ycc.addrCr = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_CR_ADDR_TOP;
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl);
	DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_ctrl_mode_sdram_input(self->imR2y, pipeNo, &gctImR2yCtrlSdramInBase);
	DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam);
	DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_set_inaddr_info(self->imR2y, pipeNo, &r2yInAddr);
	DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_set_out_bank_info(self->imR2y, pipeNo, ImR2y_YYW_CH_0, &r2yAddr0);
	DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl);
	im_r2y_ctrl_mode_sdram_input(self->imR2y, pipeNo, &gctImR2yCtrlSdramInBase);
	im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam);
	im_r2y_set_inaddr_info(self->imR2y, pipeNo, &r2yInAddr);
	im_r2y_set_out_bank_info(self->imR2y, pipeNo, ImR2y_YYW_CH_0, &r2yAddr0);
#endif
	DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "0x%x\n", 0));
#ifdef IM_R2Y_STATUS_PRINT
	DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "Status\n"));
	im_r2y_stat_print_status(self->imR2yStat);
#endif
	for(loopcnt = 0; loopcnt < ImR2y_YYW_BANK_MAX; loopcnt++) {
#ifdef D_IM_R2Y_DEBUG_ON_PC
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
			gimR2yMacroFakeFinish[0] = 1;
		}
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
			gimR2yMacroFakeFinish[1] = 1;
		}
#endif
		DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "R2Y Start\n"));
#ifdef CO_MSG_PRINT_ON
		DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "loopcnt = %u\n", loopcnt));
		ercd = im_r2y_proc_start(self->imR2yProc, pipeNo);
		DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "0x%x\n", ercd));
#ifdef CO_DEBUG_ON_PC
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
			ioR2yP1.yyr.yyrtrg.bit.yyrtrg = 3;
		}
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
			IO_R2Y_P2.yyr.yyrtrg.bit.yyrtrg = 3;
		}
#endif	//CO_DEBUG_ON_PC
		ercd = im_r2y_ctrl_mode_sdram_input(self->imR2y, pipeNo, &gctImR2yCtrlSdramInBase);
		DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "0x%x\n", ercd));
#else
		im_r2y_proc_start(self->imR2yProc, pipeNo);
#ifdef CO_DEBUG_ON_PC
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
			ioR2yP1.yyr.yyrtrg.bit.yyrtrg = 3;
		}
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
			IO_R2Y_P2.yyr.yyrtrg.bit.yyrtrg = 3;
		}
#endif	//CO_DEBUG_ON_PC
		im_r2y_ctrl_mode_sdram_input(self->imR2y, pipeNo, &gctImR2yCtrlSdramInBase);
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
		DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "0x%x\n", ercd));
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
			ercd = im_r2y_get_out_bank_index(self->imR2y,  0, ImR2y_YYW_CH_0, &bankIndex);
			DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "%d bank_idx=%u\n", ercd, bankIndex));
			ercd = im_r2y_get_out_bank_index(self->imR2y,  0, ImR2y_YYW_CH_1, &bankIndex);
			DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "%d bank_idx=%u\n", ercd, bankIndex));
			ercd = im_r2y_get_out_bank_index(self->imR2y,  0, ImR2y_YYW_CH_2, &bankIndex);
			DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "%d bank_idx=%u\n", ercd, bankIndex));
			ercd = im_r2y_get_out_bank_index(self->imR2y,  0, D_IM_R2Y_YYW_CH_0A, &bankIndex);
			DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "%d bank_idx=%u\n", ercd, bankIndex));
		}
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
			ercd = im_r2y_get_out_bank_index(self->imR2y,  1, ImR2y_YYW_CH_0, &bankIndex);
			DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "%d bank_idx=%u\n", ercd, bankIndex));
			ercd = im_r2y_get_out_bank_index(self->imR2y,  1, ImR2y_YYW_CH_1, &bankIndex);
			DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "%d bank_idx=%u\n", ercd, bankIndex));
			ercd = im_r2y_get_out_bank_index(self->imR2y,  1, ImR2y_YYW_CH_2, &bankIndex);
			DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "%d bank_idx=%u\n", ercd, bankIndex));
			ercd = im_r2y_get_out_bank_index(self->imR2y,  1, D_IM_R2Y_YYW_CH_0A, &bankIndex);
			DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "%d bank_idx=%u\n", ercd, bankIndex));
		}
		ercd = im_r2y_proc_stop(self->imR2yProc, pipeNo);
		DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "0x%x\n", ercd));
#ifdef CO_DEBUG_ON_PC
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
			ioR2yP1.yyr.yyrtrg.bit.yyrtrg = 2;
		}
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
			IO_R2Y_P2.yyr.yyrtrg.bit.yyrtrg = 2;
		}
#endif	//CO_DEBUG_ON_PC
#else
		im_r2y_proc_waitend(self->imR2yProc, NULL, flgptn, 60);
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
			im_r2y_get_out_bank_index(self->imR2y,  0, ImR2y_YYW_CH_0, &bankIndex);
			im_r2y_get_out_bank_index(self->imR2y,  0, ImR2y_YYW_CH_1, &bankIndex);
			im_r2y_get_out_bank_index(self->imR2y,  0, ImR2y_YYW_CH_2, &bankIndex);
			im_r2y_get_out_bank_index(self->imR2y,  0, D_IM_R2Y_YYW_CH_0A, &bankIndex);
		}
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
			im_r2y_get_out_bank_index(self->imR2y,  1, ImR2y_YYW_CH_0, &bankIndex);
			im_r2y_get_out_bank_index(self->imR2y,  1, ImR2y_YYW_CH_1, &bankIndex);
			im_r2y_get_out_bank_index(self->imR2y,  1, ImR2y_YYW_CH_2, &bankIndex);
			im_r2y_get_out_bank_index(self->imR2y,  1, D_IM_R2Y_YYW_CH_0A, &bankIndex);
		}
		im_r2y_proc_stop(self->imR2yProc, pipeNo);
#ifdef CO_DEBUG_ON_PC
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
			ioR2yP1.yyr.yyrtrg.bit.yyrtrg = 2;
		}
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
			IO_R2Y_P2.yyr.yyrtrg.bit.yyrtrg = 2;
		}
#endif	//CO_DEBUG_ON_PC
#endif
#ifdef IM_R2Y_STATUS_PRINT
		im_r2y_stat_print_status(self->imR2yStat);
#endif
	}

	return D_DDIM_OK;
}

#undef 	CtImR2y2series_FUNC_NAME
#define 	CtImR2y2series_FUNC_NAME "ct_im_r2y_2series_2: "
kint32 ct_im_r2y_2series_2(CtImR2y2series *self, kuchar pipeNo)
{
	TImR2yCtrl r2yCtrl = gctImR2yCtrlBase;
	TImR2yResizeRect r2yResizeRectParam;
	TImR2yInaddrInfo r2yInAddr;
	TImR2yOutbankInfo r2yAddr0;
	kuint32 loopcnt;
	kuchar bankIndex;
	TImR2yCtrlDirect r2yCtrlDirect[] =
	{
		[0] =
			{
				.frameStop = 1,
			},
	};
	DdimUserFlgptn flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

#ifdef CO_DEBUG_ON_PC
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		ioR2yP1.yyr.yyrtrg.bit.yyrtrg = 2;
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		IO_R2Y_P2.yyr.yyrtrg.bit.yyrtrg = 2;
	}
#endif	//CO_DEBUG_ON_PC
	r2yCtrl.yywEnable[ImR2y_YYW_CH_1] = ImR2y_ENABLE_OFF;
	r2yCtrl.yywEnable[ImR2y_YYW_CH_2] = ImR2y_ENABLE_OFF;
	r2yResizeRectParam.inputSize.imgTop = 0;
	r2yResizeRectParam.inputSize.imgLeft = 0;
	r2yResizeRectParam.inputSize.imgWidth = D_IM_R2Y_SRC_IMG_PIXS_WIDTH;
	r2yResizeRectParam.inputSize.imgLines = D_IM_R2Y_SRC_IMG_PIXS_LINES;
	r2yResizeRectParam.outputSize[ImR2y_YYW_CH_0].yywWidth = D_IM_R2Y_DST_IMG_PIXS_WIDTH;
	r2yResizeRectParam.outputSize[ImR2y_YYW_CH_0].yywLines = D_IM_R2Y_DST_IMG_PIXS_LINES;
	r2yResizeRectParam.outputSize[ImR2y_YYW_CH_0].outputGlobalW[ImR2y_PORT_Y] =
			D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC422_Y;
	r2yResizeRectParam.outputSize[ImR2y_YYW_CH_0].outputGlobalW[ImR2y_PORT_CB] =
			D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC422_C;
	r2yInAddr.rgb.addrR = (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_U16_R_ADDR_TOP;
	r2yInAddr.rgb.addrG = (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_U16_G_ADDR_TOP;
	r2yInAddr.rgb.addrB = (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_U16_B_ADDR_TOP;
	memset(&r2yAddr0, '\x0', sizeof(r2yAddr0));
	r2yAddr0.bankInitialPosition = ImR2y_YYW_BANK_3;
	r2yAddr0.useBankNum = ImR2y_YYW_BANK_3;
	r2yAddr0.outputAddr[ImR2y_YYW_BANK_0].ycc.addrY = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_Y_ADDR_TOP;
	r2yAddr0.outputAddr[ImR2y_YYW_BANK_0].ycc.addrCb = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_CB_ADDR_TOP;
	r2yAddr0.outputAddr[ImR2y_YYW_BANK_0].ycc.addrCr = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_CR_ADDR_TOP;
	r2yAddr0.outputAddr[ImR2y_YYW_BANK_1].ycc.addrY = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_Y_ADDR_TOP;
	r2yAddr0.outputAddr[ImR2y_YYW_BANK_1].ycc.addrCb = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_CB_ADDR_TOP;
	r2yAddr0.outputAddr[ImR2y_YYW_BANK_1].ycc.addrCr = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_CR_ADDR_TOP;
	r2yAddr0.outputAddr[ImR2y_YYW_BANK_2].ycc.addrY = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_Y_ADDR_TOP;
	r2yAddr0.outputAddr[ImR2y_YYW_BANK_2].ycc.addrCb = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_CB_ADDR_TOP;
	r2yAddr0.outputAddr[ImR2y_YYW_BANK_2].ycc.addrCr = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_CR_ADDR_TOP;
	r2yAddr0.outputAddr[ImR2y_YYW_BANK_3].ycc.addrY = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_Y_ADDR_TOP;
	r2yAddr0.outputAddr[ImR2y_YYW_BANK_3].ycc.addrCb = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_CB_ADDR_TOP;
	r2yAddr0.outputAddr[ImR2y_YYW_BANK_3].ycc.addrCr = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_CR_ADDR_TOP;
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl);
	DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_ctrl_mode_sdram_input(self->imR2y, pipeNo, &gctImR2yCtrlSdramInBase);
	DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam);
	DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_set_inaddr_info(self->imR2y, pipeNo, &r2yInAddr);
	DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "0x%x\n", ercd));
	ercd = im_r2y_set_out_bank_info(self->imR2y, pipeNo, ImR2y_YYW_CH_0, &r2yAddr0);
	DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "0x%x\n", ercd));
#else
	im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl);
	im_r2y_ctrl_mode_sdram_input(self->imR2y, pipeNo, &gctImR2yCtrlSdramInBase);
	im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam);
	im_r2y_set_inaddr_info(self->imR2y, pipeNo, &r2yInAddr);
	im_r2y_set_out_bank_info(self->imR2y, pipeNo, ImR2y_YYW_CH_0, &r2yAddr0);
#endif
	DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "0x%x\n", 0));
#ifdef IM_R2Y_STATUS_PRINT
	DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "Status\n"));
	im_r2y_stat_print_status(self->imR2yStat);
#endif
	for(loopcnt = 0; loopcnt < ImR2y_YYW_BANK_MAX; loopcnt++) {
#ifdef D_IM_R2Y_DEBUG_ON_PC
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
			gimR2yMacroFakeFinish[0] = 1;
		}
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
			gimR2yMacroFakeFinish[1] = 1;
		}
#endif
		DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "R2Y Start\n"));
#ifdef CO_MSG_PRINT_ON
		DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "loopcnt = %u\n", loopcnt));
		ercd = im_r2y_proc_start(self->imR2yProc, pipeNo);
		DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "0x%x\n", ercd));
#ifdef CO_DEBUG_ON_PC
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
			ioR2yP1.yyr.yyrtrg.bit.yyrtrg = 3;
		}
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
			IO_R2Y_P2.yyr.yyrtrg.bit.yyrtrg = 3;
		}
#endif	//CO_DEBUG_ON_PC
		ercd = im_r2y3_ctrl_mode_direct(self->imR2y3,  pipeNo, &r2yCtrlDirect[0]);
		DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "0x%x\n", ercd));
#else
		im_r2y_proc_start(self->imR2yProc, pipeNo);
#ifdef CO_DEBUG_ON_PC
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
			ioR2yP1.yyr.yyrtrg.bit.yyrtrg = 3;
		}
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
			IO_R2Y_P2.yyr.yyrtrg.bit.yyrtrg = 3;
		}
#endif	//CO_DEBUG_ON_PC
		im_r2y3_ctrl_mode_direct(self->imR2y3,  pipeNo, &r2yCtrlDirect[0]);
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
		DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "0x%x\n", ercd));
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
			ercd = im_r2y_get_out_bank_index(self->imR2y,  0, ImR2y_YYW_CH_0, &bankIndex);
			DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "%d bank_idx=%u\n", ercd, bankIndex));
			ercd = im_r2y_get_out_bank_index(self->imR2y,  0, ImR2y_YYW_CH_1, &bankIndex);
			DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "%d bank_idx=%u\n", ercd, bankIndex));
			ercd = im_r2y_get_out_bank_index(self->imR2y,  0, ImR2y_YYW_CH_2, &bankIndex);
			DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "%d bank_idx=%u\n", ercd, bankIndex));
			ercd = im_r2y_get_out_bank_index(self->imR2y,  0, D_IM_R2Y_YYW_CH_0A, &bankIndex);
			DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "%d bank_idx=%u\n", ercd, bankIndex));
		}
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
			ercd = im_r2y_get_out_bank_index(self->imR2y,  1, ImR2y_YYW_CH_0, &bankIndex);
			DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "%d bank_idx=%u\n", ercd, bankIndex));
			ercd = im_r2y_get_out_bank_index(self->imR2y,  1, ImR2y_YYW_CH_1, &bankIndex);
			DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "%d bank_idx=%u\n", ercd, bankIndex));
			ercd = im_r2y_get_out_bank_index(self->imR2y,  1, ImR2y_YYW_CH_2, &bankIndex);
			DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "%d bank_idx=%u\n", ercd, bankIndex));
			ercd = im_r2y_get_out_bank_index(self->imR2y,  1, D_IM_R2Y_YYW_CH_0A, &bankIndex);
			DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "%d bank_idx=%u\n", ercd, bankIndex));
		}
		ercd = im_r2y_proc_stop(self->imR2yProc, pipeNo);
		DriverCommon_DDIM_PRINT((CtImR2y2series_FUNC_NAME "0x%x\n", ercd));
#ifdef CO_DEBUG_ON_PC
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
			ioR2yP1.yyr.yyrtrg.bit.yyrtrg = 2;
		}
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
			IO_R2Y_P2.yyr.yyrtrg.bit.yyrtrg = 2;
		}
#endif	//CO_DEBUG_ON_PC
#else
		im_r2y_proc_waitend(self->imR2yProc, NULL, flgptn, 60);
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
			im_r2y_get_out_bank_index(self->imR2y,  0, ImR2y_YYW_CH_0, &bankIndex);
			im_r2y_get_out_bank_index(self->imR2y,  0, ImR2y_YYW_CH_1, &bankIndex);
			im_r2y_get_out_bank_index(self->imR2y,  0, ImR2y_YYW_CH_2, &bankIndex);
			im_r2y_get_out_bank_index(self->imR2y,  0, D_IM_R2Y_YYW_CH_0A, &bankIndex);
		}
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
			im_r2y_get_out_bank_index(self->imR2y,  1, ImR2y_YYW_CH_0, &bankIndex);
			im_r2y_get_out_bank_index(self->imR2y,  1, ImR2y_YYW_CH_1, &bankIndex);
			im_r2y_get_out_bank_index(self->imR2y,  1, ImR2y_YYW_CH_2, &bankIndex);
			im_r2y_get_out_bank_index(self->imR2y,  1, D_IM_R2Y_YYW_CH_0A, &bankIndex);
		}
		im_r2y_proc_stop(self->imR2yProc, pipeNo);
#ifdef CO_DEBUG_ON_PC
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
			ioR2yP1.yyr.yyrtrg.bit.yyrtrg = 2;
		}
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
			IO_R2Y_P2.yyr.yyrtrg.bit.yyrtrg = 2;
		}
#endif	//CO_DEBUG_ON_PC
#endif
#ifdef IM_R2Y_STATUS_PRINT
		im_r2y_stat_print_status(self->imR2yStat);
#endif
	}
	return D_DDIM_OK;
}

kint32 ct_im_r2y_2series_run_2(CtImR2y2series *self, kuchar pipeNo, const kuint32 ctNo3rd)
{
	switch(ctNo3rd) {
		// Test-1-2-1
		case 1:
			return ct_im_r2y_2series_1(self->ctImR2y2series, pipeNo);
		case 2:
			return ct_im_r2y_2series_2(self->ctImR2y2series, pipeNo);
		default:
			DriverCommon_DDIM_PRINT(("Error: Unknown command.\n"));
			break;
	}

	return D_DDIM_INPUT_PARAM_ERROR;
}

CtImR2y2series* ct_im_r2y_2series_new(void)
{
	CtImR2y2series* self = k_object_new_with_private(CT_TYPE_IM_R2Y_2SERIES, sizeof(CtImR2y2seriesPrivate));

	return self;
}
