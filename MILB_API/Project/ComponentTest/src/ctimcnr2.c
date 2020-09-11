/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :王印斌
*@brief               :CtImCnr2类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/
#include "im_cnr.h"
#include "dd_top.h"
#include "jdscnr.h"
#include "im_rdma.h"
#include "ctimcnr.h"
#include "ctimcnr2.h"
#include "driver_common.h"
#include "ddim_user_custom.h"

#include <string.h>
#include <stdlib.h>

G_DEFINE_TYPE(CtImCnr2, ct_im_cnr2, G_TYPE_OBJECT); 
#define CT_IM_CNR2_GET_PRIVATE(o) (G_OBJECT_GET_PRIVATE ((o), CT_TYPE_IM_CNR2, CtImCnr2Private))

struct _CtImCnr2Private
{
};

static void ctImCnrOflPrintDebugCtrlY(UCHAR ch);
static void ctImCnrOflPrintDebugCMidYTbl(UCHAR ch);
static void ctImCnrOflPrintDebugCLowYTbl(UCHAR ch);
static void ctImCnrOflPrintDebugCMidCcYTbl(UCHAR ch);

static void ct_im_cnr2_constructor(CtImCnr2 *self) 
{
}

static void ct_im_cnr2_destructor(CtImCnr2 *self) 
{
}

static void ctImCnrOflPrintDebugCtrlY(UCHAR ch)
{
	UCHAR loop, loopSta, loopEnd;

	Im_CNR_On_Pclk(ch);

	ct_im_cnr_get_loop_cnt(ch, &loopSta, &loopEnd);

	for(loop = loopSta; loop <= loopEnd; loop++){
		Ddim_Print(("ch[%d]\n",           loop));
		Ddim_Print(("YSPREN    = %u\n",   io_cnr(loop)->OFL_REG_YSPR.YSPREN.bit.YSPREN));
		Ddim_Print(("YSPRMD    = %u\n",   io_cnr(loop)->OFL_REG_YSPR.YSPRMODE.bit.YSPRMD));
		Ddim_Print(("YSPRFE    = %u\n",   io_cnr(loop)->OFL_REG_YSPR.YSPRMODE.bit.YSPRFE));
		Ddim_Print(("YSPRFXEYH = 0x%x\n", io_cnr(loop)->OFL_REG_YSPR.YSPRFXEY.bit.YSPRFXEYH));
		Ddim_Print(("YSPRFXEYV = 0x%x\n", io_cnr(loop)->OFL_REG_YSPR.YSPRFXEY.bit.YSPRFXEYV));
		Ddim_Print(("YSPRFXECH = 0x%x\n", io_cnr(loop)->OFL_REG_YSPR.YSPRFXEC.bit.YSPRFXECH));
		Ddim_Print(("YSPRFXECV = 0x%x\n", io_cnr(loop)->OFL_REG_YSPR.YSPRFXEC.bit.YSPRFXECV));
		Ddim_Print(("YSPRALPBD = 0x%x\n", io_cnr(loop)->OFL_REG_YSPR.YSPRALPBD.bit.YSPRALPBD));
	}

	Im_CNR_Off_Pclk(ch);
}

static void ctImCnrOflPrintDebugCMidYTbl(UCHAR ch)
{
	UCHAR loop, loopSta, loopEnd;

	Im_CNR_On_Pclk(ch);

	ct_im_cnr_get_loop_cnt(ch, &loopSta, &loopEnd);

	for(loop = loopSta; loop <= loopEnd; loop++){
		Ddim_Print(("ch[%d]\n",           loop));
		Ddim_Print(("MCYSCLBD_1 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCYSCLBD.MCYSCLBD1.bit.MCYSCLBD_1));
		Ddim_Print(("MCYSCLBD_2 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCYSCLBD.MCYSCLBD1.bit.MCYSCLBD_2));
		Ddim_Print(("MCYSCLBD_3 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCYSCLBD.MCYSCLBD1.bit.MCYSCLBD_3));
		Ddim_Print(("MCYSCLBD_4 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCYSCLBD.MCYSCLBD1.bit.MCYSCLBD_4));
		Ddim_Print(("MCYSCLBD_5 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCYSCLBD.MCYSCLBD2.bit.MCYSCLBD_5));

		Ddim_Print(("MCYSCLOF_0 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCYSCLOF.MCYSCLOF1.bit.MCYSCLOF_0));
		Ddim_Print(("MCYSCLOF_1 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCYSCLOF.MCYSCLOF1.bit.MCYSCLOF_1));
		Ddim_Print(("MCYSCLOF_2 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCYSCLOF.MCYSCLOF1.bit.MCYSCLOF_2));
		Ddim_Print(("MCYSCLOF_3 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCYSCLOF.MCYSCLOF1.bit.MCYSCLOF_3));
		Ddim_Print(("MCYSCLOF_4 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCYSCLOF.MCYSCLOF2.bit.MCYSCLOF_4));
		Ddim_Print(("MCYSCLOF_5 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCYSCLOF.MCYSCLOF2.bit.MCYSCLOF_5));

		Ddim_Print(("MCYSCLGA_0 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCYSCLGA.MCYSCLGA1.bit.MCYSCLGA_0));
		Ddim_Print(("MCYSCLGA_1 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCYSCLGA.MCYSCLGA1.bit.MCYSCLGA_1));
		Ddim_Print(("MCYSCLGA_2 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCYSCLGA.MCYSCLGA1.bit.MCYSCLGA_2));
		Ddim_Print(("MCYSCLGA_3 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCYSCLGA.MCYSCLGA1.bit.MCYSCLGA_3));
		Ddim_Print(("MCYSCLGA_4 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCYSCLGA.MCYSCLGA2.bit.MCYSCLGA_4));
		Ddim_Print(("MCYSCLGA_5 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCYSCLGA.MCYSCLGA2.bit.MCYSCLGA_5));
	}

	Im_CNR_Off_Pclk(ch);
}

static void ctImCnrOflPrintDebugCLowYTbl(UCHAR ch)
{
	UCHAR loop, loopSta, loopEnd;

	Im_CNR_On_Pclk(ch);

	ct_im_cnr_get_loop_cnt(ch, &loopSta, &loopEnd);

	for(loop = loopSta; loop <= loopEnd; loop++){
		Ddim_Print(("ch[%d]\n",           loop));
		Ddim_Print(("LCYSCLBD_1 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCYSCLBD.LCYSCLBD1.bit.LCYSCLBD_1));
		Ddim_Print(("LCYSCLBD_2 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCYSCLBD.LCYSCLBD1.bit.LCYSCLBD_2));
		Ddim_Print(("LCYSCLBD_3 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCYSCLBD.LCYSCLBD1.bit.LCYSCLBD_3));
		Ddim_Print(("LCYSCLBD_4 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCYSCLBD.LCYSCLBD1.bit.LCYSCLBD_4));
		Ddim_Print(("LCYSCLBD_5 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCYSCLBD.LCYSCLBD2.bit.LCYSCLBD_5));

		Ddim_Print(("LCYSCLOF_0 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCYSCLOF.LCYSCLOF1.bit.LCYSCLOF_0));
		Ddim_Print(("LCYSCLOF_1 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCYSCLOF.LCYSCLOF1.bit.LCYSCLOF_1));
		Ddim_Print(("LCYSCLOF_2 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCYSCLOF.LCYSCLOF1.bit.LCYSCLOF_2));
		Ddim_Print(("LCYSCLOF_3 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCYSCLOF.LCYSCLOF1.bit.LCYSCLOF_3));
		Ddim_Print(("LCYSCLOF_4 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCYSCLOF.LCYSCLOF2.bit.LCYSCLOF_4));
		Ddim_Print(("LCYSCLOF_5 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCYSCLOF.LCYSCLOF2.bit.LCYSCLOF_5));

		Ddim_Print(("LCYSCLGA_0 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCYSCLGA.LCYSCLGA1.bit.LCYSCLGA_0));
		Ddim_Print(("LCYSCLGA_1 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCYSCLGA.LCYSCLGA1.bit.LCYSCLGA_1));
		Ddim_Print(("LCYSCLGA_2 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCYSCLGA.LCYSCLGA1.bit.LCYSCLGA_2));
		Ddim_Print(("LCYSCLGA_3 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCYSCLGA.LCYSCLGA1.bit.LCYSCLGA_3));
		Ddim_Print(("LCYSCLGA_4 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCYSCLGA.LCYSCLGA2.bit.LCYSCLGA_4));
		Ddim_Print(("LCYSCLGA_5 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCYSCLGA.LCYSCLGA2.bit.LCYSCLGA_5));
	}

	Im_CNR_Off_Pclk(ch);
}

static void ctImCnrOflPrintDebugCMidCcYTbl(UCHAR ch)
{
	UCHAR loop, loopSta, loopEnd;

	Im_CNR_On_Pclk(ch);

	ct_im_cnr_get_loop_cnt(ch, &loopSta, &loopEnd);

	for(loop = loopSta; loop <= loopEnd; loop++){
		Ddim_Print(("ch[%d]\n",           loop));
		Ddim_Print(("MCCSCLBD_1 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCCSCLBD.MCCSCLBD1.bit.MCCSCLBD_1));
		Ddim_Print(("MCCSCLBD_2 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCCSCLBD.MCCSCLBD1.bit.MCCSCLBD_2));
		Ddim_Print(("MCCSCLBD_3 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCCSCLBD.MCCSCLBD1.bit.MCCSCLBD_3));
		Ddim_Print(("MCCSCLBD_4 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCCSCLBD.MCCSCLBD1.bit.MCCSCLBD_4));
		Ddim_Print(("MCCSCLBD_5 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCCSCLBD.MCCSCLBD2.bit.MCCSCLBD_5));

		Ddim_Print(("MCCSCLOF_0 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCCSCLOF.MCCSCLOF1.bit.MCCSCLOF_0));
		Ddim_Print(("MCCSCLOF_1 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCCSCLOF.MCCSCLOF1.bit.MCCSCLOF_1));
		Ddim_Print(("MCCSCLOF_2 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCCSCLOF.MCCSCLOF1.bit.MCCSCLOF_2));
		Ddim_Print(("MCCSCLOF_3 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCCSCLOF.MCCSCLOF1.bit.MCCSCLOF_3));
		Ddim_Print(("MCCSCLOF_4 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCCSCLOF.MCCSCLOF2.bit.MCCSCLOF_4));
		Ddim_Print(("MCCSCLOF_5 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCCSCLOF.MCCSCLOF2.bit.MCCSCLOF_5));

		Ddim_Print(("MCCSCLGA_0 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCCSCLGA.MCCSCLGA1.bit.MCCSCLGA_0));
		Ddim_Print(("MCCSCLGA_1 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCCSCLGA.MCCSCLGA1.bit.MCCSCLGA_1));
		Ddim_Print(("MCCSCLGA_2 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCCSCLGA.MCCSCLGA1.bit.MCCSCLGA_2));
		Ddim_Print(("MCCSCLGA_3 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCCSCLGA.MCCSCLGA1.bit.MCCSCLGA_3));
		Ddim_Print(("MCCSCLGA_4 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCCSCLGA.MCCSCLGA2.bit.MCCSCLGA_4));
		Ddim_Print(("MCCSCLGA_5 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCCSCLGA.MCCSCLGA2.bit.MCCSCLGA_5));
	}

	Im_CNR_Off_Pclk(ch);
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_13: "
INT32 ct_im_cnr_ofl_1_13(CtImCnr2 *self)
{
	UCHAR ch = self->ch2;
	INT32 imErcd;
	UINT32 loopcnt;
	T_IM_CNR_OFL_CTRL_Y sprCtrl[2] = {
		[0] = {	// max
			.enable = (E_IM_CNR_ONOFF)1,
			.threshold_type = (E_IM_CNR_THRESHOLD)1,
			.level = (E_IM_CNR_LEVEL)3,
			.h_y_threshold = 0xFF,
			.v_y_threshold = 0xFF,
			.h_c_threshold = 0xFF,
			.v_c_threshold = 0xFF,
			.alpha_blend_ratio = 0x1F,
		},
		[1] = {	// min
			.enable = (E_IM_CNR_ONOFF)0,
			.threshold_type = (E_IM_CNR_THRESHOLD)0,
			.level = (E_IM_CNR_LEVEL)0,
			.h_y_threshold = 0,
			.v_y_threshold = 0,
			.h_c_threshold = 0,
			.v_c_threshold = 0,
			.alpha_blend_ratio = 0,
		},
	};

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_OFL_Open(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Open error = 0x%x\n", imErcd));
		return imErcd;
	}

	for(loopcnt = 0; loopcnt < (sizeof(sprCtrl) / sizeof(sprCtrl[0])); loopcnt++) {
		Ddim_Print(("** %u\n", loopcnt));
		imErcd = Im_CNR_OFL_Ctrl_Y(ch, &sprCtrl[loopcnt]);
		if(imErcd != D_DDIM_OK) {
			Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl error = 0x%x\n", imErcd));
			return imErcd;
		}
		ctImCnrOflPrintDebugCtrlY(ch);
	}

	imErcd = Im_CNR_OFL_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_14: "
INT32 ct_im_cnr_ofl_1_14(CtImCnr2 *self)
{
	UCHAR ch = self->ch2;
	INT32 imErcd;
	UINT32 loopcnt;
	T_IM_CNR_TABLE sprTbl[3] = {
		[0] = {	// max
			.bd1 = 0xFF,
			.bd2 = 0xFF,
			.bd3 = 0xFF,
			.bd4 = 0xFF,
			.bd5 = 0xFF,
			.of0 = 0xFF,
			.of1 = 0xFF,
			.of2 = 0xFF,
			.of3 = 0xFF,
			.of4 = 0xFF,
			.of5 = 0xFF,
			.gain0 = 0x7F,
			.gain1 = 0x7F,
			.gain2 = 0x7F,
			.gain3 = 0x7F,
			.gain4 = 0x7F,
			.gain5 = 0x7F,
		},
		[1] = {	// min
			.bd1 = 0,
			.bd2 = 0,
			.bd3 = 0,
			.bd4 = 0,
			.bd5 = 0,
			.of0 = 0,
			.of1 = 0,
			.of2 = 0,
			.of3 = 0,
			.of4 = 0,
			.of5 = 0,
			.gain0 = -0x80,
			.gain1 = -0x80,
			.gain2 = -0x80,
			.gain3 = -0x80,
			.gain4 = -0x80,
			.gain5 = -0x80,
		},
		[2] = {	// countup
			.bd1 = 1,
			.bd2 = 2,
			.bd3 = 3,
			.bd4 = 4,
			.bd5 = 5,
			.of0 = 6,
			.of1 = 7,
			.of2 = 8,
			.of3 = 9,
			.of4 = 0xA,
			.of5 = 0xB,
			.gain0 = 0xC,
			.gain1 = 0xD,
			.gain2 = 0xE,
			.gain3 = 0xF,
			.gain4 = 0x10,
			.gain5 = 0x11,
		},
	};

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_OFL_Open(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Open error = 0x%x\n", imErcd));
		return imErcd;
	}

	for(loopcnt = 0; loopcnt < (sizeof(sprTbl) / sizeof(sprTbl[0])); loopcnt++) {
		Ddim_Print(("** %u\n", loopcnt));
		imErcd = Im_CNR_OFL_Set_CSPR_Mid_Y_Table(ch, &sprTbl[loopcnt]);
		if(imErcd != D_DDIM_OK) {
			Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl error = 0x%x\n", imErcd));
			return imErcd;
		}
		ctImCnrOflPrintDebugCMidYTbl(ch);
	}

	imErcd = Im_CNR_OFL_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_15: "
INT32 ct_im_cnr_ofl_1_15(CtImCnr2 *self)
{
	UCHAR ch = self->ch2;
	INT32 imErcd;
	UINT32 loopcnt;
	T_IM_CNR_TABLE sprTbl[3] = {
		[0] = {	// max
			.bd1 = 0xFF,
			.bd2 = 0xFF,
			.bd3 = 0xFF,
			.bd4 = 0xFF,
			.bd5 = 0xFF,
			.of0 = 0xFF,
			.of1 = 0xFF,
			.of2 = 0xFF,
			.of3 = 0xFF,
			.of4 = 0xFF,
			.of5 = 0xFF,
			.gain0 = 0x7F,
			.gain1 = 0x7F,
			.gain2 = 0x7F,
			.gain3 = 0x7F,
			.gain4 = 0x7F,
			.gain5 = 0x7F,
		},
		[1] = {	// min
			.bd1 = 0,
			.bd2 = 0,
			.bd3 = 0,
			.bd4 = 0,
			.bd5 = 0,
			.of0 = 0,
			.of1 = 0,
			.of2 = 0,
			.of3 = 0,
			.of4 = 0,
			.of5 = 0,
			.gain0 = -0x80,
			.gain1 = -0x80,
			.gain2 = -0x80,
			.gain3 = -0x80,
			.gain4 = -0x80,
			.gain5 = -0x80,
		},
		[2] = {	// countup
			.bd1 = 1,
			.bd2 = 2,
			.bd3 = 3,
			.bd4 = 4,
			.bd5 = 5,
			.of0 = 6,
			.of1 = 7,
			.of2 = 8,
			.of3 = 9,
			.of4 = 0xA,
			.of5 = 0xB,
			.gain0 = 0xC,
			.gain1 = 0xD,
			.gain2 = 0xE,
			.gain3 = 0xF,
			.gain4 = 0x10,
			.gain5 = 0x11,
		},
	};

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_OFL_Open(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Open error = 0x%x\n", imErcd));
		return imErcd;
	}

	for(loopcnt = 0; loopcnt < (sizeof(sprTbl) / sizeof(sprTbl[0])); loopcnt++) {
		Ddim_Print(("** %u\n", loopcnt));
		imErcd = Im_CNR_OFL_Set_CSPR_Mid_CC_Y_Table(ch, &sprTbl[loopcnt]);
		if(imErcd != D_DDIM_OK) {
			Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl error = 0x%x\n", imErcd));
			return imErcd;
		}
		ctImCnrOflPrintDebugCMidCcYTbl(ch);
	}

	imErcd = Im_CNR_OFL_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_17: "
INT32 ct_im_cnr_ofl_1_17(CtImCnr2 *self)
{
	UCHAR ch = self->ch2;
	INT32 imErcd;
	UINT32 loopcnt;
	T_IM_CNR_TABLE sprTbl[3] = {
		[0] = {	// max
			.bd1 = 0xFF,
			.bd2 = 0xFF,
			.bd3 = 0xFF,
			.bd4 = 0xFF,
			.bd5 = 0xFF,
			.of0 = 0xFF,
			.of1 = 0xFF,
			.of2 = 0xFF,
			.of3 = 0xFF,
			.of4 = 0xFF,
			.of5 = 0xFF,
			.gain0 = 0x7F,
			.gain1 = 0x7F,
			.gain2 = 0x7F,
			.gain3 = 0x7F,
			.gain4 = 0x7F,
			.gain5 = 0x7F,
		},
		[1] = {	// min
			.bd1 = 0,
			.bd2 = 0,
			.bd3 = 0,
			.bd4 = 0,
			.bd5 = 0,
			.of0 = 0,
			.of1 = 0,
			.of2 = 0,
			.of3 = 0,
			.of4 = 0,
			.of5 = 0,
			.gain0 = -0x80,
			.gain1 = -0x80,
			.gain2 = -0x80,
			.gain3 = -0x80,
			.gain4 = -0x80,
			.gain5 = -0x80,
		},
		[2] = {	// countup
			.bd1 = 1,
			.bd2 = 2,
			.bd3 = 3,
			.bd4 = 4,
			.bd5 = 5,
			.of0 = 6,
			.of1 = 7,
			.of2 = 8,
			.of3 = 9,
			.of4 = 0xA,
			.of5 = 0xB,
			.gain0 = 0xC,
			.gain1 = 0xD,
			.gain2 = 0xE,
			.gain3 = 0xF,
			.gain4 = 0x10,
			.gain5 = 0x11,
		},
	};

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_OFL_Open(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Open error = 0x%x\n", imErcd));
		return imErcd;
	}

	for(loopcnt = 0; loopcnt < (sizeof(sprTbl) / sizeof(sprTbl[0])); loopcnt++) {
		Ddim_Print(("** %u\n", loopcnt));
		imErcd = Im_CNR_OFL_Set_CSPR_Low_Y_Table(ch, &sprTbl[loopcnt]);
		if(imErcd != D_DDIM_OK) {
			Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl error = 0x%x\n", imErcd));
			return imErcd;
		}
		ctImCnrOflPrintDebugCLowYTbl(ch);
	}

	imErcd = Im_CNR_OFL_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_23: "
INT32 ct_im_cnr_ofl_1_23(CtImCnr2 *self)
{
	UCHAR ch = self->ch2;
	INT32 imErcd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	Im_CNR_OFL_Open(ch, 100);
	imErcd = Im_CNR_OFL_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_24: "
INT32 ct_im_cnr_ofl_1_24(CtImCnr2 *self)
{
	UCHAR ch = self->ch2;
	INT32 imErcd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_OFL_Reset(ch);

	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Reset error = 0x%x\n", imErcd));
	}

	return imErcd;
}

// test RDMA
#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_30: "
INT32 ct_im_cnr_ofl_1_30(CtImCnr2 *self)
{
	UCHAR ch = self->ch2;
	INT32 imErcd;
	const T_IM_CNR_RDMA_ADDR_CTRL_C* C_CNR_CTRL_C;
	ULONG size;
	ULONG* ptAddr;
	UINT32 loopcnt;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_Get_RdmaAddr_OFL_Ctrl_C(ch, &C_CNR_CTRL_C, &size);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Im_CNR_Get_RdmaAddr_OFL_Ctrl_C() error = 0x%x\n", imErcd));
		return imErcd;
	}

	// Check parameter
	Ddim_Print(("size = 0x%lx\n", size));
	ptAddr = (ULONG*)C_CNR_CTRL_C;
	for(loopcnt = 0; loopcnt < size; loopcnt+=4) {
		Ddim_Print(("address = 0x%lx\n", *ptAddr));
		ptAddr++;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_32: "
INT32 ct_im_cnr_ofl_1_32(CtImCnr2 *self)
{
	UCHAR ch = self->ch2;
	INT32 imErcd;
	const T_IM_CNR_RDMA_ADDR_OFL_CTRL_Y* C_CNR_CTRL_Y;
	ULONG size;
	ULONG* ptAddr;
	UINT32 loopcnt;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_Get_RdmaAddr_OFL_Ctrl_Y(ch, &C_CNR_CTRL_Y, &size);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Im_CNR_Get_RdmaAddr_OFL_Ctrl_Y() error = 0x%x\n", imErcd));
		return imErcd;
	}

	// Check parameter
	Ddim_Print(("size = 0x%lx\n", size));
	ptAddr = (ULONG*)C_CNR_CTRL_Y;
	for(loopcnt = 0; loopcnt < size; loopcnt+=4) {
		Ddim_Print(("address = 0x%lx\n", *ptAddr));
		ptAddr++;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_54: "
INT32 ct_im_cnr_ofl_1_54(CtImCnr2 *self)
{
	UCHAR ch = self->ch2;
	INT32 imErcd;
	const T_IM_CNR_RDMA_ADDR_SPRD_CC_TBL* C_CSPR_SPRD_CC_TBL;
	ULONG size;
	ULONG* ptAddr;
	UINT32 loopcnt;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_Get_RdmaAddr_OFL_CSPR_SPRD_CC_Table(ch, &C_CSPR_SPRD_CC_TBL, &size);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Im_CNR_Get_RdmaAddr_OFL_CSPR_SPRD_CC_Table() error = 0x%x\n", imErcd));
		return imErcd;
	}

	// Check parameter
	Ddim_Print(("size = 0x%lx\n", size));
	ptAddr = (ULONG*)C_CSPR_SPRD_CC_TBL;
	for(loopcnt = 0; loopcnt < size; loopcnt+=4) {
		Ddim_Print(("address = 0x%lx\n", *ptAddr));
		ptAddr++;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_6_2: "
INT32 ct_im_cnr_6_2(CtImCnr2 *self)
{
	UCHAR ch = self->ch2;
	INT32 ret;
	T_IM_RDMA_CTRL rdmaCtrl;
	T_IM_CNR_OFL_CTRL_Y			sprCtrlY = {
		.enable = E_IM_CNR_ONOFF_DISABLE,
		.threshold_type = E_IM_CNR_THRES_REGISTER,
		.level = E_IM_CNR_LEVEL_HIGH,
		.h_y_threshold = 0xFF,
		.v_y_threshold = 0xFF,
		.h_c_threshold = 0xFF,
		.v_c_threshold = 0xFF,
		.alpha_blend_ratio = 0x1F,
	};
	T_IM_CNR_RDMA_DATA_OFL_CTRL_Y	rdmaCtrlY;
	const  T_IM_CNR_RDMA_ADDR_OFL_CTRL_Y*	C_CNR_CTRL_ADDR;
	ULONG	size;

	ret = Im_CNR_Get_RdmaAddr_OFL_Ctrl_Y(ch, &C_CNR_CTRL_ADDR, &size);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OFL_Ctrl_Y error = 0x%x\n", ret));
		return ret;
	}

	ret = Im_CNR_Set_RdmaValue_OFL_Ctrl_Y(&sprCtrlY, &rdmaCtrlY);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OFL_Ctrl_Y error = 0x%x\n", ret));
		return ret;
	}

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)C_CNR_CTRL_ADDR;
	rdmaCtrl.reg_data_top_addr	= (ULONG)&rdmaCtrlY;
	rdmaCtrl.req_threshold		= E_IM_RDMA_PRCH_CNT_NOLIMIT;
	rdmaCtrl.int_mode			= E_IM_RDMA_INT_MODE_AND_ERR;
	rdmaCtrl.pCallBack			= NULL;
	ret = Im_RDMA_Ctrl_Quick_Start_Sync(D_DDIM_WAIT_END_TIME, &rdmaCtrl);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Ctrl error = 0x%x\n", ret));
		return ret;
	}

	if(ch == D_IM_CNR_CH_2){
		ctImCnrOflPrintDebugCtrlY(0);
		ctImCnrOflPrintDebugCtrlY(1);
	}
	else{
		ctImCnrOflPrintDebugCtrlY(ch);
	}

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_6_4: "
INT32 ct_im_cnr_6_4(CtImCnr2 *self)
{
	UCHAR ch = self->ch2;
	INT32 ret;
	T_IM_RDMA_CTRL rdmaCtrl;
	T_IM_CNR_TABLE	cnrTable = {
		.bd1 = 0xFF,
		.bd2 = 0xFF,
		.bd3 = 0xFF,
		.bd4 = 0xFF,
		.bd5 = 0xFF,
		.of0 = 0xFF,
		.of1 = 0xFF,
		.of2 = 0xFF,
		.of3 = 0xFF,
		.of4 = 0xFF,
		.of5 = 0xFF,
		.gain0 = 0x7F,
		.gain1 = 0x7F,
		.gain2 = 0x7F,
		.gain3 = 0x7F,
		.gain4 = 0x7F,
		.gain5 = 0x7F,
	};
	T_IM_CNR_RDMA_DATA_CSPR_MID_Y_TBL	rdmaMidYTbl;
	const  T_IM_CNR_RDMA_ADDR_CSPR_MID_Y_TBL*	C_MID_Y_TBL_ADDR;
	ULONG	size;

	ret = Im_CNR_Get_RdmaAddr_OFL_CSPR_Mid_Y_Table(ch, &C_MID_Y_TBL_ADDR, &size);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OFL_CSPR_Mid_Y_Table error = 0x%x\n", ret));
		return ret;
	}

	ret = Im_CNR_Set_RdmaValue_OFL_CSPR_Mid_Y_Table(&cnrTable, &rdmaMidYTbl);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OFL_CSPR_Mid_Y_Table error = 0x%x\n", ret));
		return ret;
	}

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)C_MID_Y_TBL_ADDR;
	rdmaCtrl.reg_data_top_addr	= (ULONG)&rdmaMidYTbl;
	rdmaCtrl.req_threshold		= E_IM_RDMA_PRCH_CNT_NOLIMIT;
	rdmaCtrl.int_mode			= E_IM_RDMA_INT_MODE_AND_ERR;
	rdmaCtrl.pCallBack			= NULL;
	ret = Im_RDMA_Ctrl_Quick_Start_Sync(D_DDIM_WAIT_END_TIME, &rdmaCtrl);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Ctrl error = 0x%x\n", ret));
		return ret;
	}

	if(ch == D_IM_CNR_CH_2){
		ctImCnrOflPrintDebugCMidYTbl(0);
		ctImCnrOflPrintDebugCMidYTbl(1);
	}
	else{
		ctImCnrOflPrintDebugCMidYTbl(ch);
	}

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_6_5: "
INT32 ct_im_cnr_6_5(CtImCnr2 *self)
{
	UCHAR ch = self->ch2;
	INT32 ret;
	T_IM_RDMA_CTRL rdmaCtrl;
	T_IM_CNR_TABLE	cnrTable = {
		.bd1 = 0xFF,
		.bd2 = 0xFF,
		.bd3 = 0xFF,
		.bd4 = 0xFF,
		.bd5 = 0xFF,
		.of0 = 0xFF,
		.of1 = 0xFF,
		.of2 = 0xFF,
		.of3 = 0xFF,
		.of4 = 0xFF,
		.of5 = 0xFF,
		.gain0 = 0x7F,
		.gain1 = 0x7F,
		.gain2 = 0x7F,
		.gain3 = 0x7F,
		.gain4 = 0x7F,
		.gain5 = 0x7F,
	};
	T_IM_CNR_RDMA_DATA_CSPR_MID_CC_Y_TBL	rdmaMidCcYTbl;
	const  T_IM_CNR_RDMA_ADDR_CSPR_MID_CC_Y_TBL*	C_MID_CC_Y_TBL_ADDR;
	ULONG	size;

	ret = Im_CNR_Get_RdmaAddr_OFL_CSPR_Mid_CC_Y_Table(ch, &C_MID_CC_Y_TBL_ADDR, &size);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OFL_CSPR_Mid_Y_Table error = 0x%x\n", ret));
		return ret;
	}

	ret = Im_CNR_Set_RdmaValue_OFL_CSPR_Mid_CC_Y_Table(&cnrTable, &rdmaMidCcYTbl);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OFL_CSPR_Mid_Y_Table error = 0x%x\n", ret));
		return ret;
	}

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)C_MID_CC_Y_TBL_ADDR;
	rdmaCtrl.reg_data_top_addr	= (ULONG)&rdmaMidCcYTbl;
	rdmaCtrl.req_threshold		= E_IM_RDMA_PRCH_CNT_NOLIMIT;
	rdmaCtrl.int_mode			= E_IM_RDMA_INT_MODE_AND_ERR;
	rdmaCtrl.pCallBack			= NULL;
	ret = Im_RDMA_Ctrl_Quick_Start_Sync(D_DDIM_WAIT_END_TIME, &rdmaCtrl);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Ctrl error = 0x%x\n", ret));
		return ret;
	}

	if(ch == D_IM_CNR_CH_2){
		ctImCnrOflPrintDebugCMidCcYTbl(0);
		ctImCnrOflPrintDebugCMidCcYTbl(1);
	}
	else{
		ctImCnrOflPrintDebugCMidCcYTbl(ch);
	}

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_6_7: "
INT32 ct_im_cnr_6_7(CtImCnr2 *self)
{
	UCHAR ch = self->ch2;
	INT32 ret;
	T_IM_RDMA_CTRL rdmaCtrl;
	T_IM_CNR_TABLE	cnrTable = {
		.bd1 = 0xFF,
		.bd2 = 0xFF,
		.bd3 = 0xFF,
		.bd4 = 0xFF,
		.bd5 = 0xFF,
		.of0 = 0xFF,
		.of1 = 0xFF,
		.of2 = 0xFF,
		.of3 = 0xFF,
		.of4 = 0xFF,
		.of5 = 0xFF,
		.gain0 = 0x7F,
		.gain1 = 0x7F,
		.gain2 = 0x7F,
		.gain3 = 0x7F,
		.gain4 = 0x7F,
		.gain5 = 0x7F,
	};
	T_IM_CNR_RDMA_DATA_CSPR_LOW_Y_TBL	rdmaLowYTbl;
	const  T_IM_CNR_RDMA_ADDR_CSPR_LOW_Y_TBL*	C_LOW_Y_TBL_ADDR;
	ULONG	size;

	ret = Im_CNR_Get_RdmaAddr_OFL_CSPR_Low_Y_Table(ch, &C_LOW_Y_TBL_ADDR, &size);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OFL_CSPR_Low_Y_Table error = 0x%x\n", ret));
		return ret;
	}

	ret = Im_CNR_Set_RdmaValue_OFL_CSPR_Low_Y_Table(&cnrTable, &rdmaLowYTbl);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OFL_CSPR_Low_Y_Table error = 0x%x\n", ret));
		return ret;
	}

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)C_LOW_Y_TBL_ADDR;
	rdmaCtrl.reg_data_top_addr	= (ULONG)&rdmaLowYTbl;
	rdmaCtrl.req_threshold		= E_IM_RDMA_PRCH_CNT_NOLIMIT;
	rdmaCtrl.int_mode			= E_IM_RDMA_INT_MODE_AND_ERR;
	rdmaCtrl.pCallBack			= NULL;
	ret = Im_RDMA_Ctrl_Quick_Start_Sync(D_DDIM_WAIT_END_TIME, &rdmaCtrl);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Ctrl error = 0x%x\n", ret));
		return ret;
	}

	if(ch == D_IM_CNR_CH_2){
		ctImCnrOflPrintDebugCLowYTbl(0);
		ctImCnrOflPrintDebugCLowYTbl(1);
	}
	else{
		ctImCnrOflPrintDebugCLowYTbl(ch);
	}

	return D_DDIM_OK;
}

CtImCnr2* ct_im_cnr2_new(void) 
{
    CtImCnr2 *self = g_object_new(CT_TYPE_IM_CNR2, NULL);
    return self;
}
