/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 梁正明
*@brief : CtImR2y19series
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimr2ytool.h"
#include "ctimr2y19series.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImR2y19series, ct_im_r2y_19series)
#define CT_IM_R2Y_19SERIES_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), \
		CtImR2y19seriesPrivate, CT_TYPE_IM_R2Y_19SERIES))


struct _CtImR2y19seriesPrivate
{

};


/*
 * IMPL
 */
static void ct_im_r2y_19series_constructor(CtImR2y19series *self)
{
	CtImR2y19seriesPrivate *priv = CT_IM_R2Y_19SERIES_GET_PRIVATE(self);
	self->imR2yClk = im_r2y_clk_new();
	self->imR2yCtrl = im_r2y_ctrl_new();
	self->imR2yCtrl2 = im_r2y_ctrl2_new();
	self->imR2yCtrl3 = im_r2y_ctrl3_new();
	self->imR2yEdge = im_r2y_edge_new();
	self->imR2ySet = im_r2y_set_new();
}

static void ct_im_r2y_19series_destructor(CtImR2y19series *self)
{
		CtImR2y19seriesPrivate *priv = CT_IM_R2Y_19SERIES_GET_PRIVATE(self);
		if(self->imR2yCtrl3){
			k_object_unref(self->imR2yCtrl3);
			self->imR2yCtrl3=NULL;
		}

		if(self->imR2yCtrl2){
					k_object_unref(self->imR2yCtrl2);
					self->imR2yCtrl2=NULL;
				}

		if(self->imR2yCtrl){
			k_object_unref(self->imR2yCtrl);
			self->imR2yCtrl3=NULL;
		}

		if(self->imR2yClk){
				k_object_unref(self->imR2yClk);
				self->imR2yClk=NULL;
		}
		if(self->imR2yEdge){
					k_object_unref(self->imR2yEdge);
					self->imR2yEdge=NULL;
				}

		if(self->imR2ySet){
				k_object_unref(self->imR2ySet);
				self->imR2ySet=NULL;
		}
}


/*
 * PUBLIC
 */
#undef 	CtImR2y19series_FUNC_NAME
#define 	CtImR2y19series_FUNC_NAME "ct_im_r2y_19series_0: "
kint32 ct_im_r2y_19series_0(CtImR2y19series *self, kuchar pipeNo)
{
#ifdef CO_DEBUG_ON_PC
	struct TCtImR2y190
	{
		kushort srcTbl[ImR2y_TABLE_MAX_TONE];
		kushort dstTbl[ImR2y_TABLE_MAX_TONE];
	};
	struct TCtImR2y190 tblBody;
	struct TCtImR2y190	*tbl = &tblBody;
#else //!CO_DEBUG_ON_PC
	struct TCtImR2y190
	{
		kushort srcTbl[ImR2y_TABLE_MAX_TONE];
		kushort dstTbl[ImR2y_TABLE_MAX_TONE];
	}* tbl = (struct TCtImR2y190*)D_IM_R2Y_IMG_MEM_IN_ADDR_TOP;
#endif //!CO_DEBUG_ON_PC
	kuint32 loopcnt;
	kuint32 loopcnt2;
	union UCtImR2y190
	{
		kulong	word;
		struct
		{
			kulong	tc0	:15;
			kulong		:1;
			kulong	tc1	:15;
			kulong		:1;
		}bit;
	} wordConv =
			{
				.bit.tc0 = 0,
				.bit.tc1 = 0,
			};
	kulong regVal;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y19series_FUNC_NAME));
	for(loopcnt = 0; loopcnt < ImR2y_TABLE_MAX_TONE; loopcnt++) {
		tbl->srcTbl[loopcnt] = ImR2y_TABLE_MAX_TONE - loopcnt;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_ctrl3_set_tone_control_table(self->imR2yCtrl3, pipeNo, tbl->srcTbl, 0, ImR2y_TABLE_MAX_TONE);
	DriverCommon_DDIM_PRINT((CtImR2y19series_FUNC_NAME "0x%x\n", ercd));
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		ercd = im_r2y_ctrl3_get_tone_control_table(self->imR2yCtrl3, 0, tbl->dstTbl, 0, ImR2y_TABLE_MAX_TONE);
		DriverCommon_DDIM_PRINT((CtImR2y19series_FUNC_NAME "0x%x\n", ercd));
		im_r2y_clk_on_hclk(self->imR2yClk, 0);
		im_r2y_set_tone_control_tbl_access_enable(self->imR2yCtrl, 0, ImR2y_ENABLE_ON, ImR2y_WAIT_ON);
		for(loopcnt = 0; loopcnt < ImR2y_TABLE_MAX_TONE; loopcnt += 2) {
			// Force word read access
			wordConv.word = *(kulong*)&ioR2yTblP1.tc.hword[loopcnt];
			for(loopcnt2 = loopcnt; loopcnt2 < (loopcnt + 2); loopcnt2++) {
				if(loopcnt2 == loopcnt) {
					regVal = wordConv.bit.tc0;
				} else {
					regVal = wordConv.bit.tc1;
				}
				//	DriverCommon_DDIM_PRINT(("[%u] = %u, %u\n", loopcnt2, tbl->dstTbl[loopcnt2], regVal));
				if(regVal != tbl->dstTbl[loopcnt2]) {
					DriverCommon_DDIM_PRINT(("[%u] unmatch\n", loopcnt2));
				}
			}
		}
		im_r2y_set_tone_control_tbl_access_enable(self->imR2yCtrl, 0, ImR2y_ENABLE_OFF, ImR2y_WAIT_OFF);
		im_r2y_clk_off_hclk(self->imR2yClk, 0);
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		ercd = im_r2y_ctrl3_get_tone_control_table(self->imR2yCtrl3, 1, tbl->dstTbl, 0, ImR2y_TABLE_MAX_TONE);
		DriverCommon_DDIM_PRINT((CtImR2y19series_FUNC_NAME "0x%x\n", ercd));
		im_r2y_clk_on_hclk(self->imR2yClk, 1);
		im_r2y_set_tone_control_tbl_access_enable(self->imR2yCtrl, 1, ImR2y_ENABLE_ON, ImR2y_WAIT_ON);
		for(loopcnt = 0; loopcnt < ImR2y_TABLE_MAX_TONE; loopcnt += 2) {
			// Force word read access
			wordConv.word = *(kulong*)&ioR2yTblP2.tc.hword[loopcnt];
			for(loopcnt2 = loopcnt; loopcnt2 < (loopcnt + 2); loopcnt2++) {
				if(loopcnt2 == loopcnt) {
					regVal = wordConv.bit.tc0;
				} else {
					regVal = wordConv.bit.tc1;
				}
				//DriverCommon_DDIM_PRINT(("[%u] = %u, %u\n", loopcnt2, tbl->dstTbl[loopcnt2], regVal));
				if(regVal != tbl->dstTbl[loopcnt2]) {
					DriverCommon_DDIM_PRINT(("[%u] unmatch\n", loopcnt2));
				}
			}
		}
		im_r2y_set_tone_control_tbl_access_enable(self->imR2yCtrl, 1, ImR2y_ENABLE_OFF, ImR2y_WAIT_OFF);
		im_r2y_clk_off_hclk(self->imR2yClk, 1);
	}
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y19series_FUNC_NAME
#define 	CtImR2y19series_FUNC_NAME "ct_im_r2y_19series_1: "
kint32 ct_im_r2y_19series_1(CtImR2y19series *self, kuchar pipeNo)
{
#ifdef CO_DEBUG_ON_PC
	struct TCtImR2y191
	{
		kuint32 dstTbl[ImR2y_TABLE_MAX_TCT];
	};
	struct TCtImR2y191 tblBody;
	struct TCtImR2y191* tbl = &tblBody;
	kuint32 loopcnt;
#else //!CO_DEBUG_ON_PC
	struct TCtImR2y191
	{
		kuint32 dstTbl[ImR2y_TABLE_MAX_TCT];
	}* tbl = (struct TCtImR2y191*)D_IM_R2Y_IMG_MEM_IN_ADDR_TOP;
#endif //!CO_DEBUG_ON_PC
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y19series_FUNC_NAME));
#ifdef CO_DEBUG_ON_PC
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		for(loopcnt = 0; loopcnt < ImR2y_TABLE_MAX_TCT; loopcnt++) {
			ioR2yTblP1.tctdata.word[loopcnt] = ImR2y_TABLE_MAX_TCT - loopcnt;
		}
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		for(loopcnt = 0; loopcnt < ImR2y_TABLE_MAX_TCT; loopcnt++) {
			ioR2yTblP2.tctdata.word[loopcnt] = ImR2y_TABLE_MAX_TCT - loopcnt;
		}
	}
#endif //!CO_DEBUG_ON_PC
#ifdef CO_MSG_PRINT_ON
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		ercd = im_r2y_ctrl3_get_luminance_evaluation_before_tone(self->imR2yCtrl3, 0, tbl->dstTbl, ImR2y_TABLE_MAX_TCT);
		DriverCommon_DDIM_PRINT((CtImR2y19series_FUNC_NAME "0x%x\n", ercd));
#ifdef CO_DEBUG_ON_PC
		im_r2y_clk_on_hclk(self->imR2yClk, 0);
		im_r2y_ctrl2_set_luminance_evaluation_tbl_access_enable(self->imR2yCtrl2, 0, ImR2y_ENABLE_ON, ImR2y_WAIT_ON);
		for(loopcnt = 0; loopcnt < ImR2y_TABLE_MAX_TCT; loopcnt++) {
			//DriverCommon_DDIM_PRINT(("[%u] = %u, %u\n", loopcnt,
			//tbl->dstTbl[loopcnt], ioR2yTblP1.tctdata.word[loopcnt]));
			if(ioR2yTblP1.tctdata.word[loopcnt] != ImR2y_TABLE_MAX_TCT - loopcnt) {
				DriverCommon_DDIM_PRINT(("[%u] unmatch\n", loopcnt));
			}
		}
		im_r2y_ctrl2_set_luminance_evaluation_tbl_access_enable(self->imR2yCtrl2, 0, ImR2y_ENABLE_OFF, ImR2y_WAIT_OFF);
		im_r2y_clk_off_hclk(self->imR2yClk, 0);
#endif //!CO_DEBUG_ON_PC
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		ercd = im_r2y_ctrl3_get_luminance_evaluation_before_tone(self->imR2yCtrl3, 1, tbl->dstTbl, ImR2y_TABLE_MAX_TCT);
		DriverCommon_DDIM_PRINT((CtImR2y19series_FUNC_NAME "0x%x\n", ercd));
#ifdef CO_DEBUG_ON_PC
		im_r2y_clk_on_hclk(self->imR2yClk, 0);
		im_r2y_ctrl2_set_luminance_evaluation_tbl_access_enable(self->imR2yCtrl2, 1, ImR2y_ENABLE_ON, ImR2y_WAIT_ON);
		for(loopcnt = 0; loopcnt < ImR2y_TABLE_MAX_TCT; loopcnt++) {
			//	DriverCommon_DDIM_PRINT(("[%u] = %u, %u\n", loopcnt,
			//tbl->dstTbl[loopcnt], ioR2yTblP2.tctdata.word[loopcnt]));
			if(ioR2yTblP2.tctdata.word[loopcnt] != ImR2y_TABLE_MAX_TCT - loopcnt) {
				DriverCommon_DDIM_PRINT(("[%u] unmatch\n", loopcnt));
			}
		}
		im_r2y_ctrl2_set_luminance_evaluation_tbl_access_enable(self->imR2yCtrl2, 1, ImR2y_ENABLE_OFF, ImR2y_WAIT_OFF);
		im_r2y_clk_off_hclk(self->imR2yClk, 0);
#endif //!CO_DEBUG_ON_PC
	}
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y19series_FUNC_NAME
#define 	CtImR2y19series_FUNC_NAME "ct_im_r2y_19series_2: "
kint32 ct_im_r2y_19series_2(CtImR2y19series *self, kuchar pipeNo)
{
#ifdef CO_DEBUG_ON_PC
	struct TCtImR2y192
	{
		kushort dstTblY[ImR2y_TABLE_MAX_BTC_HISTOGRAM_Y];
		kushort dstTblRgb[ImR2y_TABLE_MAX_BTC_HISTOGRAM_RGB];
	};
	struct TCtImR2y192 tblBody;
	struct TCtImR2y192 *tbl = &tblBody;
	kuint32 loopcnt;
#else //!CO_DEBUG_ON_PC
	struct TCtImR2y192
	{
		kushort dstTblY[ImR2y_TABLE_MAX_BTC_HISTOGRAM_Y];
		kushort dstTblRgb[ImR2y_TABLE_MAX_BTC_HISTOGRAM_RGB];
	}* tbl = (struct TCtImR2y192*)D_IM_R2Y_IMG_MEM_IN_ADDR_TOP;
#endif //!CO_DEBUG_ON_PC
	union UCtImR2y192
	{
		kulong	word;
		struct
		{
			kulong	tchSxData0	:16;
			kulong	tchSxData1	:16;
		}bit;
	};
	TImR2yTchsFlg overflowFlg;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y19series_FUNC_NAME));
#ifdef CO_DEBUG_ON_PC
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		for(loopcnt = 0; loopcnt < ImR2y_TABLE_MAX_BTC_HISTOGRAM_Y; loopcnt++) {
			ioR2yTblP1.tchsydata.hword[loopcnt] = ImR2y_TABLE_MAX_BTC_HISTOGRAM_Y - loopcnt;
		}
		for(loopcnt = 0; loopcnt < ImR2y_TABLE_MAX_BTC_HISTOGRAM_RGB; loopcnt++) {
			ioR2yTblP1.tchsrdata.hword[loopcnt] = ImR2y_TABLE_MAX_BTC_HISTOGRAM_RGB - loopcnt;
		}
		for(loopcnt = 0; loopcnt < ImR2y_TABLE_MAX_BTC_HISTOGRAM_RGB; loopcnt++) {
			ioR2yTblP1.tchsgdata.hword[loopcnt] = ImR2y_TABLE_MAX_BTC_HISTOGRAM_RGB - loopcnt;
		}
		for(loopcnt = 0; loopcnt < ImR2y_TABLE_MAX_BTC_HISTOGRAM_RGB; loopcnt++) {
			ioR2yTblP1.tchsbdata.hword[loopcnt] = ImR2y_TABLE_MAX_BTC_HISTOGRAM_RGB - loopcnt;
		}
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		for(loopcnt = 0; loopcnt < ImR2y_TABLE_MAX_BTC_HISTOGRAM_Y; loopcnt++) {
			ioR2yTblP2.tchsydata.hword[loopcnt] = ImR2y_TABLE_MAX_BTC_HISTOGRAM_Y - loopcnt;
		}
		for(loopcnt = 0; loopcnt < ImR2y_TABLE_MAX_BTC_HISTOGRAM_RGB; loopcnt++) {
			ioR2yTblP2.tchsrdata.hword[loopcnt] = ImR2y_TABLE_MAX_BTC_HISTOGRAM_RGB - loopcnt;
		}
		for(loopcnt = 0; loopcnt < ImR2y_TABLE_MAX_BTC_HISTOGRAM_RGB; loopcnt++) {
			ioR2yTblP2.tchsgdata.hword[loopcnt] = ImR2y_TABLE_MAX_BTC_HISTOGRAM_RGB - loopcnt;
		}
		for(loopcnt = 0; loopcnt < ImR2y_TABLE_MAX_BTC_HISTOGRAM_RGB; loopcnt++) {
			ioR2yTblP2.tchsbdata.hword[loopcnt] = ImR2y_TABLE_MAX_BTC_HISTOGRAM_RGB - loopcnt;
		}
	}
#endif //!CO_DEBUG_ON_PC
#ifdef CO_MSG_PRINT_ON
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		ercd = im_r2y_ctrl3_get_histogram_before_tone(self->imR2yCtrl3, 0, E_R2Y_BTC_HIST_RGBTBL_Y, &overflowFlg, tbl->dstTblY);
		DriverCommon_DDIM_PRINT((CtImR2y19series_FUNC_NAME "0x%x\n", ercd));
		DriverCommon_DDIM_PRINT((CtImR2y19series_FUNC_NAME "0x%x, 0x%x, 0x%x, 0x%x\n",
				overflowFlg.y, overflowFlg.r, overflowFlg.g, overflowFlg.b));
#ifdef CO_DEBUG_ON_PC
		im_r2y_clk_on_hclk(self->imR2yClk, 0);
		im_r2y_ctrl2_set_btc_histogram_tbl_access_enable(self->imR2yCtrl2, 0, ImR2y_ENABLE_ON, ImR2y_WAIT_ON);
		for(loopcnt = 0; loopcnt < ImR2y_TABLE_MAX_BTC_HISTOGRAM_Y; loopcnt++) {
			if(ioR2yTblP1.tchsydata.hword[loopcnt] != ImR2y_TABLE_MAX_BTC_HISTOGRAM_Y - loopcnt) {
				DriverCommon_DDIM_PRINT(("[%u] unmatch\n", loopcnt));
			}
		}
		im_r2y_ctrl2_set_btc_histogram_tbl_access_enable(self->imR2yCtrl2, 0, ImR2y_ENABLE_OFF, ImR2y_WAIT_OFF);
		im_r2y_clk_off_hclk(self->imR2yClk, 0);
#endif //!CO_DEBUG_ON_PC
		ercd = im_r2y_ctrl3_get_histogram_before_tone(self->imR2yCtrl3, 0, E_R2Y_BTC_HIST_RGBTBL_R, &overflowFlg, tbl->dstTblRgb);
		DriverCommon_DDIM_PRINT((CtImR2y19series_FUNC_NAME "0x%x\n", ercd));
		DriverCommon_DDIM_PRINT((CtImR2y19series_FUNC_NAME "0x%x, 0x%x, 0x%x, 0x%x\n",
				overflowFlg.y, overflowFlg.r, overflowFlg.g, overflowFlg.b));
#ifdef CO_DEBUG_ON_PC
		im_r2y_clk_on_hclk(self->imR2yClk, 0);
		im_r2y_ctrl2_set_btc_histogram_tbl_access_enable(self->imR2yCtrl2, 0, ImR2y_ENABLE_ON, ImR2y_WAIT_ON);
		for(loopcnt = 0; loopcnt < ImR2y_TABLE_MAX_BTC_HISTOGRAM_RGB; loopcnt++) {
			if(ioR2yTblP1.tchsrdata.hword[loopcnt] != ImR2y_TABLE_MAX_BTC_HISTOGRAM_RGB - loopcnt) {
				DriverCommon_DDIM_PRINT(("[%u] unmatch\n", loopcnt));
			}
		}
		im_r2y_ctrl2_set_btc_histogram_tbl_access_enable(self->imR2yCtrl2, 0, ImR2y_ENABLE_OFF, ImR2y_WAIT_OFF);
		im_r2y_clk_off_hclk(self->imR2yClk, 0);
#endif //!CO_DEBUG_ON_PC
		ercd = im_r2y_ctrl3_get_histogram_before_tone(self->imR2yCtrl3, 0, E_R2Y_BTC_HIST_RGBTBL_G, &overflowFlg, tbl->dstTblRgb);
		DriverCommon_DDIM_PRINT((CtImR2y19series_FUNC_NAME "0x%x\n", ercd));
		DriverCommon_DDIM_PRINT((CtImR2y19series_FUNC_NAME "0x%x, 0x%x, 0x%x, 0x%x\n",
				overflowFlg.y, overflowFlg.r, overflowFlg.g, overflowFlg.b));
#ifdef CO_DEBUG_ON_PC
		im_r2y_clk_on_hclk(self->imR2yClk, 0);
		im_r2y_ctrl2_set_btc_histogram_tbl_access_enable(self->imR2yCtrl2, 0, ImR2y_ENABLE_ON, ImR2y_WAIT_ON);
		for(loopcnt = 0; loopcnt < ImR2y_TABLE_MAX_BTC_HISTOGRAM_RGB; loopcnt++) {
			if(ioR2yTblP1.tchsgdata.hword[loopcnt] != ImR2y_TABLE_MAX_BTC_HISTOGRAM_RGB - loopcnt) {
				DriverCommon_DDIM_PRINT(("[%u] unmatch\n", loopcnt));
			}
		}
		im_r2y_ctrl2_set_btc_histogram_tbl_access_enable(self->imR2yCtrl2, 0, ImR2y_ENABLE_OFF, ImR2y_WAIT_OFF);
		im_r2y_clk_off_hclk(self->imR2yClk, 0);
#endif //!CO_DEBUG_ON_PC
		ercd = im_r2y_ctrl3_get_histogram_before_tone(self->imR2yCtrl3, 0, E_R2Y_BTC_HIST_RGBTBL_B, &overflowFlg, tbl->dstTblRgb);
		DriverCommon_DDIM_PRINT((CtImR2y19series_FUNC_NAME "0x%x\n", ercd));
		DriverCommon_DDIM_PRINT((CtImR2y19series_FUNC_NAME "0x%x, 0x%x, 0x%x, 0x%x\n",
				overflowFlg.y, overflowFlg.r, overflowFlg.g, overflowFlg.b));
#ifdef CO_DEBUG_ON_PC
		im_r2y_clk_on_hclk(self->imR2yClk, 0);
		im_r2y_ctrl2_set_btc_histogram_tbl_access_enable(self->imR2yCtrl2, 0, ImR2y_ENABLE_ON, ImR2y_WAIT_ON);
		for(loopcnt = 0; loopcnt < ImR2y_TABLE_MAX_BTC_HISTOGRAM_RGB; loopcnt++) {
			if(ioR2yTblP1.tchsbdata.hword[loopcnt] != ImR2y_TABLE_MAX_BTC_HISTOGRAM_RGB - loopcnt) {
				DriverCommon_DDIM_PRINT(("[%u] unmatch\n", loopcnt));
			}
		}
		im_r2y_ctrl2_set_btc_histogram_tbl_access_enable(self->imR2yCtrl2, 0, ImR2y_ENABLE_OFF, ImR2y_WAIT_OFF);
		im_r2y_clk_off_hclk(self->imR2yClk, 0);
#endif //!CO_DEBUG_ON_PC
	}
	if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		ercd = im_r2y_ctrl3_get_histogram_before_tone(self->imR2yCtrl3, 0, E_R2Y_BTC_HIST_RGBTBL_Y, &overflowFlg, tbl->dstTblY);
		DriverCommon_DDIM_PRINT((CtImR2y19series_FUNC_NAME "0x%x\n", ercd));
		DriverCommon_DDIM_PRINT((CtImR2y19series_FUNC_NAME "0x%x, 0x%x, 0x%x, 0x%x\n",
				overflowFlg.y, overflowFlg.r, overflowFlg.g, overflowFlg.b));
#ifdef CO_DEBUG_ON_PC
		im_r2y_clk_on_hclk(self->imR2yClk, 0);
		im_r2y_ctrl2_set_btc_histogram_tbl_access_enable(self->imR2yCtrl2, 0, ImR2y_ENABLE_ON, ImR2y_WAIT_ON);
		for(loopcnt = 0; loopcnt < ImR2y_TABLE_MAX_BTC_HISTOGRAM_Y; loopcnt++) {
			if(ioR2yTblP2.tchsydata.hword[loopcnt] != ImR2y_TABLE_MAX_BTC_HISTOGRAM_Y - loopcnt) {
				DriverCommon_DDIM_PRINT(("[%u] unmatch\n", loopcnt));
			}
		}
		im_r2y_ctrl2_set_btc_histogram_tbl_access_enable(self->imR2yCtrl2, 0, ImR2y_ENABLE_OFF, ImR2y_WAIT_OFF);
		im_r2y_clk_off_hclk(self->imR2yClk, 0);
#endif //!CO_DEBUG_ON_PC
		ercd = im_r2y_ctrl3_get_histogram_before_tone(self->imR2yCtrl3, 0, E_R2Y_BTC_HIST_RGBTBL_R, &overflowFlg, tbl->dstTblRgb);
		DriverCommon_DDIM_PRINT((CtImR2y19series_FUNC_NAME "0x%x\n", ercd));
		DriverCommon_DDIM_PRINT((CtImR2y19series_FUNC_NAME "0x%x, 0x%x, 0x%x, 0x%x\n",
				overflowFlg.y, overflowFlg.r, overflowFlg.g, overflowFlg.b));
#ifdef CO_DEBUG_ON_PC
		im_r2y_clk_on_hclk(self->imR2yClk, 0);
		im_r2y_ctrl2_set_btc_histogram_tbl_access_enable(self->imR2yCtrl2, 0, ImR2y_ENABLE_ON, ImR2y_WAIT_ON);
		for(loopcnt = 0; loopcnt < ImR2y_TABLE_MAX_BTC_HISTOGRAM_RGB; loopcnt++) {
			if(ioR2yTblP2.tchsrdata.hword[loopcnt] != ImR2y_TABLE_MAX_BTC_HISTOGRAM_RGB - loopcnt) {
				DriverCommon_DDIM_PRINT(("[%u] unmatch\n", loopcnt));
			}
		}
		im_r2y_ctrl2_set_btc_histogram_tbl_access_enable(self->imR2yCtrl2, 0, ImR2y_ENABLE_OFF, ImR2y_WAIT_OFF);
		im_r2y_clk_off_hclk(self->imR2yClk, 0);
#endif //!CO_DEBUG_ON_PC
		ercd = im_r2y_ctrl3_get_histogram_before_tone(self->imR2yCtrl3, 0, E_R2Y_BTC_HIST_RGBTBL_G, &overflowFlg, tbl->dstTblRgb);
		DriverCommon_DDIM_PRINT((CtImR2y19series_FUNC_NAME "0x%x\n", ercd));
		DriverCommon_DDIM_PRINT((CtImR2y19series_FUNC_NAME "0x%x, 0x%x, 0x%x, 0x%x\n",
				overflowFlg.y, overflowFlg.r, overflowFlg.g, overflowFlg.b));
#ifdef CO_DEBUG_ON_PC
		im_r2y_clk_on_hclk(self->imR2yClk, 0);
		im_r2y_ctrl2_set_btc_histogram_tbl_access_enable(self->imR2yCtrl2, 0, ImR2y_ENABLE_ON, ImR2y_WAIT_ON);
		for(loopcnt = 0; loopcnt < ImR2y_TABLE_MAX_BTC_HISTOGRAM_RGB; loopcnt++) {
			if(ioR2yTblP2.tchsgdata.hword[loopcnt] != ImR2y_TABLE_MAX_BTC_HISTOGRAM_RGB - loopcnt) {
				DriverCommon_DDIM_PRINT(("[%u] unmatch\n", loopcnt));
			}
		}
		im_r2y_ctrl2_set_btc_histogram_tbl_access_enable(self->imR2yCtrl2, 0, ImR2y_ENABLE_OFF, ImR2y_WAIT_OFF);
		im_r2y_clk_off_hclk(self->imR2yClk, 0);
#endif //!CO_DEBUG_ON_PC
		ercd = im_r2y_ctrl3_get_histogram_before_tone(self->imR2yCtrl3, 0, E_R2Y_BTC_HIST_RGBTBL_B, &overflowFlg, tbl->dstTblRgb);
		DriverCommon_DDIM_PRINT((CtImR2y19series_FUNC_NAME "0x%x\n", ercd));
		DriverCommon_DDIM_PRINT((CtImR2y19series_FUNC_NAME "0x%x, 0x%x, 0x%x, 0x%x\n",
				overflowFlg.y, overflowFlg.r, overflowFlg.g, overflowFlg.b));
#ifdef CO_DEBUG_ON_PC
		im_r2y_clk_on_hclk(self->imR2yClk, 0);
		im_r2y_ctrl2_set_btc_histogram_tbl_access_enable(self->imR2yCtrl2, 0, ImR2y_ENABLE_ON, ImR2y_WAIT_ON);
		for(loopcnt = 0; loopcnt < ImR2y_TABLE_MAX_BTC_HISTOGRAM_RGB; loopcnt++) {
			if(ioR2yTblP2.tchsbdata.hword[loopcnt] != ImR2y_TABLE_MAX_BTC_HISTOGRAM_RGB - loopcnt) {
				DriverCommon_DDIM_PRINT(("[%u] unmatch\n", loopcnt));
			}
		}
		im_r2y_ctrl2_set_btc_histogram_tbl_access_enable(self->imR2yCtrl2, 0, ImR2y_ENABLE_OFF, ImR2y_WAIT_OFF);
		im_r2y_clk_off_hclk(self->imR2yClk, 0);
#endif //!CO_DEBUG_ON_PC
	}
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y19series_FUNC_NAME
#define 	CtImR2y19series_FUNC_NAME "ct_im_r2y_19series_3: "
kint32 ct_im_r2y_19series_3(CtImR2y19series *self, kuchar pipeNo)
{
#ifdef CO_DEBUG_ON_PC
	struct TCtImR2y193
	{
		kushort srcTblFull[ImR2y_TABLE_MAX_GAMMA];
		kulonglong srcTblDiff[ImR2y_TABLE_MAX_GAMMA];
	};
	struct TCtImR2y193 tblBody;
	struct TCtImR2y193	*tbl = &tblBody;
#else //!CO_DEBUG_ON_PC
	struct TCtImR2y193
	{
		kushort srcTblFull[ImR2y_TABLE_MAX_GAMMA];
		kulonglong srcTblDiff[ImR2y_TABLE_MAX_GAMMA];
	}* tbl = (struct TCtImR2y193*)D_IM_R2Y_IMG_MEM_IN_ADDR_TOP;
#endif //!CO_DEBUG_ON_PC
	kuint32 loopcnt;
	kuint32 loopcnt2;
	kuint32 loopcnt3;
	union UCtImR2y193
	{
		kulong	word;
		struct
		{
			kulong	gmxxFl0	:10;
			kulong			 :6;
			kulong	gmxxFl1	:10;
			kulong			 :6;
		}bit;
	} wordConv =
	{
		.bit.gmxxFl0 = 0,
		.bit.gmxxFl1 = 0,
	};
	kulong regVal;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	const char errmsg[] = "%u-%u[%u] unmatch\n";

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y19series_FUNC_NAME));
	for(loopcnt = 0; loopcnt < 3; loopcnt++) {
		DriverCommon_DDIM_PRINT(("** %u\n", loopcnt));
		switch(loopcnt) {
			// max
			default:
				//	case 0:
				for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_GAMMA; loopcnt2++) {
					tbl->srcTblFull[loopcnt2] = 0x3FF;
					tbl->srcTblDiff[loopcnt2] = 0xFFFFFFFFFFFFFFFF;
				}
				break;
			// min
			case 1:
				for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_GAMMA; loopcnt2++) {
					tbl->srcTblFull[loopcnt2] = 0;
					tbl->srcTblDiff[loopcnt2] = 0;
				}
				break;
			// indvisual
			case 2:
				for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_GAMMA; loopcnt2++) {
					tbl->srcTblFull[loopcnt2] = ImR2y_TABLE_MAX_GAMMA - loopcnt2;
					tbl->srcTblDiff[loopcnt2] = loopcnt2;
				}
				break;
		}
#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y_set_gamma_table(self->imR2ySet, pipeNo, 0, tbl->srcTblFull, tbl->srcTblDiff);
		DriverCommon_DDIM_PRINT((CtImR2y19series_FUNC_NAME "0x%x\n", ercd));
		im_r2y_clk_on_hclk(self->imR2yClk, pipeNo);
		im_r2y_ctrl2_set_gamma_tbl_access_enable(self->imR2yCtrl2, pipeNo, ImR2y_ENABLE_ON, ImR2y_WAIT_ON);
		im_r2y_ctrl2_set_gamma_yb_tbl_access_enable(self->imR2yCtrl2, pipeNo, ImR2y_ENABLE_ON, ImR2y_WAIT_ON);
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
			for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_GAMMA; loopcnt2 += 2) {
				wordConv.word = *(kulong*)&ioR2yTblP1.gmrgbfl.hword[loopcnt2];
				for(loopcnt3 = loopcnt2; loopcnt3 < (loopcnt2 + 2); loopcnt3++) {
					if(loopcnt3 == loopcnt2) {
						regVal = wordConv.bit.gmxxFl0;
					} else {
						regVal = wordConv.bit.gmxxFl1;
					}
					//DriverCommon_DDIM_PRINT(("%u-%u[%u] %lx, %x\n", 0, 0,
					//loopcnt3, regVal, tbl->srcTblFull[loopcnt3]));
					if(regVal != tbl->srcTblFull[loopcnt3]) {
						DriverCommon_DDIM_PRINT((errmsg, 0, 0, loopcnt3));
					}
					//DriverCommon_DDIM_PRINT(("%u-%u[%u] %llx, %llx\n", 0, 1, loopcnt3,
					//	ioR2yTblP1.gmrgbdf.dword[loopcnt3], tbl->srcTblDiff[loopcnt3]));
#ifdef CO_DEBUG_ON_PC
					if(ioR2yTblP1.gmrgbdf.dword[loopcnt3] != tbl->srcTblDiff[loopcnt3]) {
						DriverCommon_DDIM_PRINT((errmsg, 0, 1, loopcnt3));
					}
#endif	// CO_DEBUG_ON_PC
				}
			}
		}
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
			for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_GAMMA; loopcnt2 += 2) {
				wordConv.word = *(kulong*)&ioR2yTblP2.gmrgbfl.hword[loopcnt2];
				for(loopcnt3 = loopcnt2; loopcnt3 < (loopcnt2 + 2); loopcnt3++) {
					if(loopcnt3 == loopcnt2) {
						regVal = wordConv.bit.gmxxFl0;
					} else {
						regVal = wordConv.bit.gmxxFl1;
					}
					//	DriverCommon_DDIM_PRINT(("%u-%u[%u] %lx, %x\n", 0, 0,
					//loopcnt3, regVal, tbl->srcTblFull[loopcnt3]));
					if(regVal != tbl->srcTblFull[loopcnt3]) {
						DriverCommon_DDIM_PRINT((errmsg, 0, 0, loopcnt3));
					}
					//DriverCommon_DDIM_PRINT(("%u-%u[%u] %llx, %llx\n", 0, 1, loopcnt3,
					//	ioR2yTblP2.gmrgbdf.dword[loopcnt3], tbl->srcTblDiff[loopcnt3]));
#ifdef CO_DEBUG_ON_PC
					if(ioR2yTblP2.gmrgbdf.dword[loopcnt3] != tbl->srcTblDiff[loopcnt3]) {
						DriverCommon_DDIM_PRINT((errmsg, 0, 1, loopcnt3));
					}
#endif	// CO_DEBUG_ON_PC
				}
			}
		}
		im_r2y_ctrl2_set_gamma_tbl_access_enable(self->imR2yCtrl2, pipeNo, ImR2y_ENABLE_OFF, ImR2y_WAIT_OFF);
		im_r2y_ctrl2_set_gamma_yb_tbl_access_enable(self->imR2yCtrl2, pipeNo, ImR2y_ENABLE_OFF, ImR2y_WAIT_OFF);
		im_r2y_clk_off_hclk(self->imR2yClk, pipeNo);
		ercd = im_r2y_set_gamma_table(self->imR2ySet, pipeNo, 1, tbl->srcTblFull, tbl->srcTblDiff);
		DriverCommon_DDIM_PRINT((CtImR2y19series_FUNC_NAME "0x%x\n", ercd));
		im_r2y_clk_on_hclk(self->imR2yClk, pipeNo);
		im_r2y_ctrl2_set_gamma_tbl_access_enable(self->imR2yCtrl2, pipeNo, ImR2y_ENABLE_ON, ImR2y_WAIT_ON);
		im_r2y_ctrl2_set_gamma_yb_tbl_access_enable(self->imR2yCtrl2, pipeNo, ImR2y_ENABLE_ON, ImR2y_WAIT_ON);
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
			for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_GAMMA; loopcnt2 += 2) {
				wordConv.word = *(kulong*)&ioR2yTblP1.gmrfl.hword[loopcnt2];
				for(loopcnt3 = loopcnt2; loopcnt3 < (loopcnt2 + 2); loopcnt3++) {
					if(loopcnt3 == loopcnt2) {
						regVal = wordConv.bit.gmxxFl0;
					} else {
						regVal = wordConv.bit.gmxxFl1;
					}
					//	DriverCommon_DDIM_PRINT(("%u-%u[%u] %lx, %x\n", 1,
					//0, loopcnt3, regVal, tbl->srcTblFull[loopcnt3]));
					if(regVal != tbl->srcTblFull[loopcnt3]) {
						DriverCommon_DDIM_PRINT((errmsg, 1, 0, loopcnt3));
					}
					//	DriverCommon_DDIM_PRINT(("%u-%u[%u] %llx, %llx\n", 1, 1,
					//loopcnt3, ioR2yTblP1.gmrdf.dword[loopcnt3], tbl->srcTblDiff[loopcnt3]));
#ifdef CO_DEBUG_ON_PC
					if(ioR2yTblP1.gmrdf.dword[loopcnt3] != tbl->srcTblDiff[loopcnt3]) {
						DriverCommon_DDIM_PRINT((errmsg, 1, 1, loopcnt3));
					}
#endif	// CO_DEBUG_ON_PC
				}
			}
		}
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
			for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_GAMMA; loopcnt2 += 2) {
				wordConv.word = *(kulong*)&ioR2yTblP2.gmrfl.hword[loopcnt2];
				for(loopcnt3 = loopcnt2; loopcnt3 < (loopcnt2 + 2); loopcnt3++) {
					if(loopcnt3 == loopcnt2) {
						regVal = wordConv.bit.gmxxFl0;
					} else {
						regVal = wordConv.bit.gmxxFl1;
					}
					//	DriverCommon_DDIM_PRINT(("%u-%u[%u] %lx, %x\n", 1, 0,
					//loopcnt3, regVal, tbl->srcTblFull[loopcnt3]));
					if(regVal != tbl->srcTblFull[loopcnt3]) {
						DriverCommon_DDIM_PRINT((errmsg, 1, 0, loopcnt3));
					}
					//DriverCommon_DDIM_PRINT(("%u-%u[%u] %llx, %llx\n", 1, 1, loopcnt3,
					//ioR2yTblP2.gmrdf.dword[loopcnt3], tbl->srcTblDiff[loopcnt3]));
#ifdef CO_DEBUG_ON_PC
					if(ioR2yTblP2.gmrdf.dword[loopcnt3] != tbl->srcTblDiff[loopcnt3]) {
						DriverCommon_DDIM_PRINT((errmsg, 1, 1, loopcnt3));
					}
#endif	// CO_DEBUG_ON_PC
				}
			}
		}
		im_r2y_ctrl2_set_gamma_tbl_access_enable(self->imR2yCtrl2, pipeNo, ImR2y_ENABLE_OFF, ImR2y_WAIT_OFF);
		im_r2y_ctrl2_set_gamma_yb_tbl_access_enable(self->imR2yCtrl2, pipeNo, ImR2y_ENABLE_OFF, ImR2y_WAIT_OFF);
		im_r2y_clk_off_hclk(self->imR2yClk, pipeNo);
		ercd = im_r2y_set_gamma_table(self->imR2ySet, pipeNo, 2, tbl->srcTblFull, tbl->srcTblDiff);
		DriverCommon_DDIM_PRINT((CtImR2y19series_FUNC_NAME "0x%x\n", ercd));
		im_r2y_clk_on_hclk(self->imR2yClk, pipeNo);
		im_r2y_ctrl2_set_gamma_tbl_access_enable(self->imR2yCtrl2, pipeNo, ImR2y_ENABLE_ON, ImR2y_WAIT_ON);
		im_r2y_ctrl2_set_gamma_yb_tbl_access_enable(self->imR2yCtrl2, pipeNo, ImR2y_ENABLE_ON, ImR2y_WAIT_ON);
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
			for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_GAMMA; loopcnt2 += 2) {
				wordConv.word = *(kulong*)&ioR2yTblP1.gmgfl.hword[loopcnt2];
				for(loopcnt3 = loopcnt2; loopcnt3 < (loopcnt2 + 2); loopcnt3++) {
					if(loopcnt3 == loopcnt2) {
						regVal = wordConv.bit.gmxxFl0;
					} else {
						regVal = wordConv.bit.gmxxFl1;
					}
					//DriverCommon_DDIM_PRINT(("%u-%u[%u] %lx, %x\n", 2, 0,
					//loopcnt3, regVal, tbl->srcTblFull[loopcnt3]));
					if(regVal != tbl->srcTblFull[loopcnt3]) {
						DriverCommon_DDIM_PRINT((errmsg, 2, 0, loopcnt3));
					}
					//	DriverCommon_DDIM_PRINT(("%u-%u[%u] %llx, %llx\n", 2, 1, loopcnt3,
					//ioR2yTblP1.gmgdf.dword[loopcnt3], tbl->srcTblDiff[loopcnt3]));
#ifdef CO_DEBUG_ON_PC
					if(ioR2yTblP1.gmgdf.dword[loopcnt3] != tbl->srcTblDiff[loopcnt3]) {
						DriverCommon_DDIM_PRINT((errmsg, 2, 1, loopcnt3));
					}
#endif	// CO_DEBUG_ON_PC
				}
			}
		}
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
			for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_GAMMA; loopcnt2 += 2) {
				wordConv.word = *(kulong*)&ioR2yTblP2.gmgfl.hword[loopcnt2];
				for(loopcnt3 = loopcnt2; loopcnt3 < (loopcnt2 + 2); loopcnt3++) {
					if(loopcnt3 == loopcnt2) {
						regVal = wordConv.bit.gmxxFl0;
					} else {
						regVal = wordConv.bit.gmxxFl1;
					}
					//	DriverCommon_DDIM_PRINT(("%u-%u[%u] %lx, %x\n", 2, 0,
					//loopcnt3, regVal, tbl->srcTblFull[loopcnt3]));
					if(regVal != tbl->srcTblFull[loopcnt3]) {
						DriverCommon_DDIM_PRINT((errmsg, 2, 0, loopcnt3));
					}
					//	DriverCommon_DDIM_PRINT(("%u-%u[%u] %llx, %llx\n", 2, 1,
					//loopcnt3, ioR2yTblP2.gmgdf.dword[loopcnt3], tbl->srcTblDiff[loopcnt3]));
#ifdef CO_DEBUG_ON_PC
					if(ioR2yTblP2.gmgdf.dword[loopcnt3] != tbl->srcTblDiff[loopcnt3]) {
						DriverCommon_DDIM_PRINT((errmsg, 2, 1, loopcnt3));
					}
#endif	// CO_DEBUG_ON_PC
				}
			}
		}
		im_r2y_ctrl2_set_gamma_tbl_access_enable(self->imR2yCtrl2, pipeNo, ImR2y_ENABLE_OFF, ImR2y_WAIT_OFF);
		im_r2y_ctrl2_set_gamma_yb_tbl_access_enable(self->imR2yCtrl2, pipeNo, ImR2y_ENABLE_OFF, ImR2y_WAIT_OFF);
		im_r2y_clk_off_hclk(self->imR2yClk, pipeNo);
		ercd = im_r2y_set_gamma_table(self->imR2ySet, pipeNo, 3, tbl->srcTblFull, tbl->srcTblDiff);
		DriverCommon_DDIM_PRINT((CtImR2y19series_FUNC_NAME "0x%x\n", ercd));
		im_r2y_clk_on_hclk(self->imR2yClk, pipeNo);
		im_r2y_ctrl2_set_gamma_tbl_access_enable(self->imR2yCtrl2, pipeNo, ImR2y_ENABLE_ON, ImR2y_WAIT_ON);
		im_r2y_ctrl2_set_gamma_yb_tbl_access_enable(self->imR2yCtrl2, pipeNo, ImR2y_ENABLE_ON, ImR2y_WAIT_ON);
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
			for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_GAMMA; loopcnt2 += 2) {
				wordConv.word = *(kulong*)&ioR2yTblP1.gmbfl.hword[loopcnt2];
				for(loopcnt3 = loopcnt2; loopcnt3 < (loopcnt2 + 2); loopcnt3++) {
					if(loopcnt3 == loopcnt2) {
						regVal = wordConv.bit.gmxxFl0;
					} else {
						regVal = wordConv.bit.gmxxFl1;
					}
					//	DriverCommon_DDIM_PRINT(("%u-%u[%u] %lx, %x\n", 3, 0,
					//loopcnt3, regVal, tbl->srcTblFull[loopcnt3]));
					if(regVal != tbl->srcTblFull[loopcnt3]) {
						DriverCommon_DDIM_PRINT((errmsg, 3, 0, loopcnt3));
					}
					//DriverCommon_DDIM_PRINT(("%u-%u[%u] %llx, %llx\n", 3, 1, loopcnt3,
					//ioR2yTblP1.gmbdf.dword[loopcnt3], tbl->srcTblDiff[loopcnt3]));
#ifdef CO_DEBUG_ON_PC
					if(ioR2yTblP1.gmbdf.dword[loopcnt3] != tbl->srcTblDiff[loopcnt3]) {
						DriverCommon_DDIM_PRINT((errmsg, 3, 1, loopcnt3));
					}
#endif	// CO_DEBUG_ON_PC
				}
			}
		}
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
			for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_GAMMA; loopcnt2 += 2) {
				wordConv.word = *(kulong*)&ioR2yTblP2.gmbfl.hword[loopcnt2];
				for(loopcnt3 = loopcnt2; loopcnt3 < (loopcnt2 + 2); loopcnt3++) {
					if(loopcnt3 == loopcnt2) {
						regVal = wordConv.bit.gmxxFl0;
					} else {
						regVal = wordConv.bit.gmxxFl1;
					}
					//	DriverCommon_DDIM_PRINT(("%u-%u[%u] %lx, %x\n", 3, 0,
					//loopcnt3, regVal, tbl->srcTblFull[loopcnt3]));
					if(regVal != tbl->srcTblFull[loopcnt3]) {
						DriverCommon_DDIM_PRINT((errmsg, 3, 0, loopcnt3));
					}
					//	DriverCommon_DDIM_PRINT(("%u-%u[%u] %llx, %llx\n", 3, 1,
					//loopcnt3, ioR2yTblP2.gmbdf.dword[loopcnt3], tbl->srcTblDiff[loopcnt3]));
#ifdef CO_DEBUG_ON_PC
					if(ioR2yTblP2.gmbdf.dword[loopcnt3] != tbl->srcTblDiff[loopcnt3]) {
						DriverCommon_DDIM_PRINT((errmsg, 3, 1, loopcnt3));
					}
#endif	// CO_DEBUG_ON_PC
				}
			}
		}
		im_r2y_ctrl2_set_gamma_tbl_access_enable(self->imR2yCtrl2, pipeNo, ImR2y_ENABLE_OFF, ImR2y_WAIT_OFF);
		im_r2y_ctrl2_set_gamma_yb_tbl_access_enable(self->imR2yCtrl2, pipeNo, ImR2y_ENABLE_OFF, ImR2y_WAIT_OFF);
		im_r2y_clk_off_hclk(self->imR2yClk, pipeNo);
		ercd = im_r2y_set_gamma_table(self->imR2ySet, pipeNo, 4, tbl->srcTblFull, tbl->srcTblDiff);
		DriverCommon_DDIM_PRINT((CtImR2y19series_FUNC_NAME "0x%x\n", ercd));
		im_r2y_clk_on_hclk(self->imR2yClk, pipeNo);
		im_r2y_ctrl2_set_gamma_tbl_access_enable(self->imR2yCtrl2, pipeNo, ImR2y_ENABLE_ON, ImR2y_WAIT_ON);
		im_r2y_ctrl2_set_gamma_yb_tbl_access_enable(self->imR2yCtrl2, pipeNo, ImR2y_ENABLE_ON, ImR2y_WAIT_ON);
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
			for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_GAMMA; loopcnt2 += 2) {
				wordConv.word = *(kulong*)&ioR2yTblP1.gmybfl.hword[loopcnt2];
				for(loopcnt3 = loopcnt2; loopcnt3 < (loopcnt2 + 2); loopcnt3++) {
					if(loopcnt3 == loopcnt2) {
						regVal = wordConv.bit.gmxxFl0;
					} else {
						regVal = wordConv.bit.gmxxFl1;
					}
					//	DriverCommon_DDIM_PRINT(("%u-%u[%u] %lx, %x\n", 4, 0,
					//loopcnt3, regVal, tbl->srcTblFull[loopcnt3]));
					if(regVal != tbl->srcTblFull[loopcnt3]) {
						DriverCommon_DDIM_PRINT((errmsg, 4, 0, loopcnt3));
					}
					//	DriverCommon_DDIM_PRINT(("%u-%u[%u] %llx, %llx\n", 4, 1, loopcnt3,
					//ioR2yTblP1.gmybdf.dword[loopcnt3], tbl->srcTblDiff[loopcnt3]));
#ifdef CO_DEBUG_ON_PC
					if(ioR2yTblP1.gmybdf.dword[loopcnt3] != tbl->srcTblDiff[loopcnt3]) {
						DriverCommon_DDIM_PRINT((errmsg, 4, 1, loopcnt3));
					}
#endif	// CO_DEBUG_ON_PC
				}
			}
		}
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
			for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_GAMMA; loopcnt2 += 2) {
				wordConv.word = *(kulong*)&ioR2yTblP2.gmybfl.hword[loopcnt2];
				for(loopcnt3 = loopcnt2; loopcnt3 < (loopcnt2 + 2); loopcnt3++) {
					if(loopcnt3 == loopcnt2) {
						regVal = wordConv.bit.gmxxFl0;
					} else {
						regVal = wordConv.bit.gmxxFl1;
					}
					//DriverCommon_DDIM_PRINT(("%u-%u[%u] %lx, %x\n", 4, 0,
					//loopcnt3, regVal, tbl->srcTblFull[loopcnt3]));
					if(regVal != tbl->srcTblFull[loopcnt3]) {
						DriverCommon_DDIM_PRINT((errmsg, 4, 0, loopcnt3));
					}
					//	DriverCommon_DDIM_PRINT(("%u-%u[%u] %llx, %llx\n", 4, 1, loopcnt3,
					//ioR2yTblP2.gmybdf.dword[loopcnt3], tbl->srcTblDiff[loopcnt3]));
#ifdef CO_DEBUG_ON_PC
					if(ioR2yTblP2.gmybdf.dword[loopcnt3] != tbl->srcTblDiff[loopcnt3]) {
						DriverCommon_DDIM_PRINT((errmsg, 4, 1, loopcnt3));
					}
#endif	// CO_DEBUG_ON_PC
				}
			}
		}
		im_r2y_ctrl2_set_gamma_tbl_access_enable(self->imR2yCtrl2, pipeNo, ImR2y_ENABLE_OFF, ImR2y_WAIT_OFF);
		im_r2y_ctrl2_set_gamma_yb_tbl_access_enable(self->imR2yCtrl2, pipeNo, ImR2y_ENABLE_OFF, ImR2y_WAIT_OFF);
		im_r2y_clk_off_hclk(self->imR2yClk, pipeNo);
#endif
	}

	return D_DDIM_OK;
}

#undef 	CtImR2y19series_FUNC_NAME
#define 	CtImR2y19series_FUNC_NAME "ct_im_r2y_19series_4: "
kint32 ct_im_r2y_19series_4(CtImR2y19series *self, kuchar pipeNo)
{
#ifdef CO_DEBUG_ON_PC
	struct TCtImR2y194
	{
		kuchar srcTbl[ImR2y_TABLE_MAX_EDGE_SCALE_HI];
	};
	struct TCtImR2y194 tblBody;
	struct TCtImR2y194	*tbl = &tblBody;
#else //!CO_DEBUG_ON_PC
	struct TCtImR2y194
	{
		kuchar srcTbl[ImR2y_TABLE_MAX_EDGE_SCALE_HI];
	}* tbl = (struct TCtImR2y194*)D_IM_R2Y_IMG_MEM_IN_ADDR_TOP;
#endif //!CO_DEBUG_ON_PC
	kuint32 loopcnt;
	kuint32 loopcnt2;
	kuint32 loopcnt3;
	union UCtImR2y194
	{
		kulong	word;
		struct
		{
			kulong	eghwscl0	:8;
			kulong	eghwscl1	:8;
			kulong	eghwscl2	:8;
			kulong	eghwscl3	:8;
		}bit;
	} wordConv =
		{
		.bit.eghwscl0 = 0,
		.bit.eghwscl1 = 0,
		.bit.eghwscl2 = 0,
		.bit.eghwscl3 = 0,
		};
	kulong regVal;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	const char errmsg[] = "%u[%u] unmatch\n";

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y19series_FUNC_NAME));
	for(loopcnt = 0; loopcnt < 3; loopcnt++) {
		DriverCommon_DDIM_PRINT(("** %u\n", loopcnt));
		switch(loopcnt) {
			// max
			default:
				//	case 0:
				for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_EDGE_SCALE_HI; loopcnt2++) {
					tbl->srcTbl[loopcnt2] = 0xFF;
				}
				break;
			// min
			case 1:
				for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_EDGE_SCALE_HI; loopcnt2++) {
					tbl->srcTbl[loopcnt2] = 0;
				}
				break;
			// indvisual
			case 2:
				for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_EDGE_SCALE_HI; loopcnt2++) {
					if(loopcnt2 >= 256) {
						tbl->srcTbl[loopcnt2] = 0xFF - (loopcnt2 - 256);
					} else {
						tbl->srcTbl[loopcnt2] = 0xFF - loopcnt2;
					}
				}
				break;
		}
#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y_set_high_edge_scale_table(self->imR2ySet, pipeNo, tbl->srcTbl, 0, ImR2y_TABLE_MAX_EDGE_SCALE_HI);
		DriverCommon_DDIM_PRINT((CtImR2y19series_FUNC_NAME "0x%x\n", ercd));
		im_r2y_clk_on_hclk(self->imR2yClk, pipeNo);
		im_r2y_edge_set_high_edge_scl_tbl_access_enable(self->imR2yEdge, pipeNo, ImR2y_ENABLE_ON, ImR2y_WAIT_ON);
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
			for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_EDGE_SCALE_HI; loopcnt2 += 4) {
				// Force word read access
				wordConv.word = *(kulong*)&ioR2yTblP1.eghwscl.byte[loopcnt2];
				for(loopcnt3 = loopcnt2; loopcnt3 < (loopcnt2 + 4); loopcnt3++) {
					if(loopcnt3 == loopcnt2) {
						regVal = wordConv.bit.eghwscl0;
					} else if(loopcnt3 == (loopcnt2 +1)) {
						regVal = wordConv.bit.eghwscl1;
					} else if(loopcnt3 == (loopcnt2 +2)) {
						regVal = wordConv.bit.eghwscl2;
					} else {
						regVal = wordConv.bit.eghwscl3;
					}
					//DriverCommon_DDIM_PRINT(("[%u], 0x%lx, 0x%x, 0x%lx\n", loopcnt3,
					//regVal, tbl->srcTbl[loopcnt3], wordConv.word));
					if(regVal != tbl->srcTbl[loopcnt3]) {
						DriverCommon_DDIM_PRINT((errmsg, 0, loopcnt3));
					}
				}
			}
		}
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
			for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_EDGE_SCALE_HI; loopcnt2 += 4) {
				// Force word read access
				wordConv.word = *(kulong*)&ioR2yTblP2.eghwscl.byte[loopcnt2];
				for(loopcnt3 = loopcnt2; loopcnt3 < (loopcnt2 + 4); loopcnt3++) {
					if(loopcnt3 == loopcnt2) {
						regVal = wordConv.bit.eghwscl0;
					} else if(loopcnt3 == (loopcnt2 +1)) {
						regVal = wordConv.bit.eghwscl1;
					} else if(loopcnt3 == (loopcnt2 +2)) {
						regVal = wordConv.bit.eghwscl2;
					} else {
						regVal = wordConv.bit.eghwscl3;
					}
					//	DriverCommon_DDIM_PRINT(("[%u], 0x%lx, 0x%x, 0x%lx\n", loopcnt3, regVal,
					//tbl->srcTbl[loopcnt3], wordConv.word));
					if(regVal != tbl->srcTbl[loopcnt3]) {
						DriverCommon_DDIM_PRINT((errmsg, 0, loopcnt3));
					}
				}
			}
		}
		im_r2y_edge_set_high_edge_scl_tbl_access_enable(self->imR2yEdge, pipeNo, ImR2y_ENABLE_OFF, ImR2y_WAIT_OFF);
		im_r2y_clk_off_hclk(self->imR2yClk, pipeNo);
#endif
	}

	return D_DDIM_OK;
}

CtImR2y19series* ct_im_r2y_19series_new(void)
{
	CtImR2y19series* self = k_object_new_with_private(CT_TYPE_IM_R2Y_19SERIES, sizeof(CtImR2y19seriesPrivate));

	return self;
}

