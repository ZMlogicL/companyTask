/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :王印斌
*@brief               :CtImCnr3类
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
#include "im_rdma.h"
#include "jdscnr.h"
#include "ctimcnr.h"
#include "ctimcnr3.h"
#include "driver_common.h"
#include "ddim_user_custom.h"

#include <string.h>
#include <stdlib.h>


G_DEFINE_TYPE(CtImCnr3, ct_im_cnr3, G_TYPE_OBJECT); 
#define CT_IM_CNR3_GET_PRIVATE(o) (G_OBJECT_GET_PRIVATE ((o), CT_TYPE_IM_CNR3, CtImCnr3Private))

struct _CtImCnr3Private
{

};

static void ctImCnrOflPrintDebugCMidCcCTbl(UCHAR ch);
static void ctImCnrOflPrintDebugCLowCcYTbl(UCHAR ch);
static void ctImCnrOflPrintDebugCLowCcCTbl(UCHAR ch);

static void ct_im_cnr3_constructor(CtImCnr3 *self) 
{
//	CtImCnr3Private *priv = CT_IM_CNR3_GET_PRIVATE(self);
}

static void ct_im_cnr3_destructor(CtImCnr3 *self) 
{
//	CtImCnr3Private *priv = CT_IM_CNR3_GET_PRIVATE(self);
}

static void ctImCnrOflPrintDebugCMidCcCTbl(UCHAR ch)
{
	UCHAR loop, loopSta, loopEnd;

	Im_CNR_On_Pclk(ch);

	ct_im_cnr_get_loop_cnt(ch, &loopSta, &loopEnd);

	for(loop = loopSta; loop <= loopEnd; loop++){
		Ddim_Print(("ch[%d]\n",           loop));
		Ddim_Print(("MCSSCLBD_1 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCSSCLBD.MCSSCLBD1.bit.MCSSCLBD_1));
		Ddim_Print(("MCSSCLBD_2 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCSSCLBD.MCSSCLBD1.bit.MCSSCLBD_2));
		Ddim_Print(("MCSSCLBD_3 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCSSCLBD.MCSSCLBD1.bit.MCSSCLBD_3));
		Ddim_Print(("MCSSCLBD_4 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCSSCLBD.MCSSCLBD1.bit.MCSSCLBD_4));
		Ddim_Print(("MCSSCLBD_5 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCSSCLBD.MCSSCLBD2.bit.MCSSCLBD_5));

		Ddim_Print(("MCSSCLOF_0 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCSSCLOF.MCSSCLOF1.bit.MCSSCLOF_0));
		Ddim_Print(("MCSSCLOF_1 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCSSCLOF.MCSSCLOF1.bit.MCSSCLOF_1));
		Ddim_Print(("MCSSCLOF_2 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCSSCLOF.MCSSCLOF1.bit.MCSSCLOF_2));
		Ddim_Print(("MCSSCLOF_3 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCSSCLOF.MCSSCLOF1.bit.MCSSCLOF_3));
		Ddim_Print(("MCSSCLOF_4 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCSSCLOF.MCSSCLOF2.bit.MCSSCLOF_4));
		Ddim_Print(("MCSSCLOF_5 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCSSCLOF.MCSSCLOF2.bit.MCSSCLOF_5));

		Ddim_Print(("MCSSCLGA_0 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCSSCLGA.MCSSCLGA1.bit.MCSSCLGA_0));
		Ddim_Print(("MCSSCLGA_1 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCSSCLGA.MCSSCLGA1.bit.MCSSCLGA_1));
		Ddim_Print(("MCSSCLGA_2 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCSSCLGA.MCSSCLGA1.bit.MCSSCLGA_2));
		Ddim_Print(("MCSSCLGA_3 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCSSCLGA.MCSSCLGA1.bit.MCSSCLGA_3));
		Ddim_Print(("MCSSCLGA_4 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCSSCLGA.MCSSCLGA2.bit.MCSSCLGA_4));
		Ddim_Print(("MCSSCLGA_5 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCSSCLGA.MCSSCLGA2.bit.MCSSCLGA_5));
	}

	Im_CNR_Off_Pclk(ch);
}

static void ctImCnrOflPrintDebugCLowCcYTbl(UCHAR ch)
{
	UCHAR loop, loopSta, loopEnd;

	Im_CNR_On_Pclk(ch);

	ct_im_cnr_get_loop_cnt(ch, &loopSta, &loopEnd);

	for(loop = loopSta; loop <= loopEnd; loop++){
		Ddim_Print(("ch[%d]\n",           loop));
		Ddim_Print(("LCCSCLBD_1 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCCSCLBD.LCCSCLBD1.bit.LCCSCLBD_1));
		Ddim_Print(("LCCSCLBD_2 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCCSCLBD.LCCSCLBD1.bit.LCCSCLBD_2));
		Ddim_Print(("LCCSCLBD_3 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCCSCLBD.LCCSCLBD1.bit.LCCSCLBD_3));
		Ddim_Print(("LCCSCLBD_4 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCCSCLBD.LCCSCLBD1.bit.LCCSCLBD_4));
		Ddim_Print(("LCCSCLBD_5 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCCSCLBD.LCCSCLBD2.bit.LCCSCLBD_5));

		Ddim_Print(("LCCSCLOF_0 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCCSCLOF.LCCSCLOF1.bit.LCCSCLOF_0));
		Ddim_Print(("LCCSCLOF_1 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCCSCLOF.LCCSCLOF1.bit.LCCSCLOF_1));
		Ddim_Print(("LCCSCLOF_2 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCCSCLOF.LCCSCLOF1.bit.LCCSCLOF_2));
		Ddim_Print(("LCCSCLOF_3 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCCSCLOF.LCCSCLOF1.bit.LCCSCLOF_3));
		Ddim_Print(("LCCSCLOF_4 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCCSCLOF.LCCSCLOF2.bit.LCCSCLOF_4));
		Ddim_Print(("LCCSCLOF_5 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCCSCLOF.LCCSCLOF2.bit.LCCSCLOF_5));

		Ddim_Print(("LCCSCLGA_0 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCCSCLGA.LCCSCLGA1.bit.LCCSCLGA_0));
		Ddim_Print(("LCCSCLGA_1 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCCSCLGA.LCCSCLGA1.bit.LCCSCLGA_1));
		Ddim_Print(("LCCSCLGA_2 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCCSCLGA.LCCSCLGA1.bit.LCCSCLGA_2));
		Ddim_Print(("LCCSCLGA_3 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCCSCLGA.LCCSCLGA1.bit.LCCSCLGA_3));
		Ddim_Print(("LCCSCLGA_4 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCCSCLGA.LCCSCLGA2.bit.LCCSCLGA_4));
		Ddim_Print(("LCCSCLGA_5 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCCSCLGA.LCCSCLGA2.bit.LCCSCLGA_5));
	}

	Im_CNR_Off_Pclk(ch);
}

static void ctImCnrOflPrintDebugCLowCcCTbl(UCHAR ch)
{
	UCHAR loop, loopSta, loopEnd;

	Im_CNR_On_Pclk(ch);

	ct_im_cnr_get_loop_cnt(ch, &loopSta, &loopEnd);

	for(loop = loopSta; loop <= loopEnd; loop++){
		Ddim_Print(("ch[%d]\n",           loop));
		Ddim_Print(("LCSSCLBD_1 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCSSCLBD.LCSSCLBD1.bit.LCSSCLBD_1));
		Ddim_Print(("LCSSCLBD_2 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCSSCLBD.LCSSCLBD1.bit.LCSSCLBD_2));
		Ddim_Print(("LCSSCLBD_3 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCSSCLBD.LCSSCLBD1.bit.LCSSCLBD_3));
		Ddim_Print(("LCSSCLBD_4 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCSSCLBD.LCSSCLBD1.bit.LCSSCLBD_4));
		Ddim_Print(("LCSSCLBD_5 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCSSCLBD.LCSSCLBD2.bit.LCSSCLBD_5));

		Ddim_Print(("LCSSCLOF_0 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCSSCLOF.LCSSCLOF1.bit.LCSSCLOF_0));
		Ddim_Print(("LCSSCLOF_1 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCSSCLOF.LCSSCLOF1.bit.LCSSCLOF_1));
		Ddim_Print(("LCSSCLOF_2 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCSSCLOF.LCSSCLOF1.bit.LCSSCLOF_2));
		Ddim_Print(("LCSSCLOF_3 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCSSCLOF.LCSSCLOF1.bit.LCSSCLOF_3));
		Ddim_Print(("LCSSCLOF_4 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCSSCLOF.LCSSCLOF2.bit.LCSSCLOF_4));
		Ddim_Print(("LCSSCLOF_5 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCSSCLOF.LCSSCLOF2.bit.LCSSCLOF_5));

		Ddim_Print(("LCSSCLGA_0 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCSSCLGA.LCSSCLGA1.bit.LCSSCLGA_0));
		Ddim_Print(("LCSSCLGA_1 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCSSCLGA.LCSSCLGA1.bit.LCSSCLGA_1));
		Ddim_Print(("LCSSCLGA_2 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCSSCLGA.LCSSCLGA1.bit.LCSSCLGA_2));
		Ddim_Print(("LCSSCLGA_3 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCSSCLGA.LCSSCLGA1.bit.LCSSCLGA_3));
		Ddim_Print(("LCSSCLGA_4 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCSSCLGA.LCSSCLGA2.bit.LCSSCLGA_4));
		Ddim_Print(("LCSSCLGA_5 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCSSCLGA.LCSSCLGA2.bit.LCSSCLGA_5));
	}

	Im_CNR_Off_Pclk(ch);
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_16: "
INT32 ct_im_cnr_ofl_1_16(CtImCnr3 *self)
{
	UCHAR ch = self->ch3;
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
		imErcd = Im_CNR_OFL_Set_CSPR_Mid_CC_C_Table(ch, &sprTbl[loopcnt]);
		if(imErcd != D_DDIM_OK) {
			Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl error = 0x%x\n", imErcd));
			return imErcd;
		}
		ctImCnrOflPrintDebugCMidCcCTbl(ch);
	}

	imErcd = Im_CNR_OFL_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_18: "
INT32 ct_im_cnr_ofl_1_18(CtImCnr3 *self)
{
	UCHAR ch = self->ch3;
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
		imErcd = Im_CNR_OFL_Set_CSPR_Low_CC_Y_Table(ch, &sprTbl[loopcnt]);
		if(imErcd != D_DDIM_OK) {
			Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl error = 0x%x\n", imErcd));
			return imErcd;
		}
		ctImCnrOflPrintDebugCLowCcYTbl(ch);
	}

	imErcd = Im_CNR_OFL_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_19: "
INT32 ct_im_cnr_ofl_1_19(CtImCnr3 *self)
{
	UCHAR ch = self->ch3;
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
		imErcd = Im_CNR_OFL_Set_CSPR_Low_CC_C_Table(ch, &sprTbl[loopcnt]);
		if(imErcd != D_DDIM_OK) {
			Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl error = 0x%x\n", imErcd));
			return imErcd;
		}
		ctImCnrOflPrintDebugCLowCcCTbl(ch);
	}

	imErcd = Im_CNR_OFL_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_21: "
INT32 ct_im_cnr_ofl_1_21(CtImCnr3 *self)
{
	UCHAR ch = self->ch3;
	INT32 imErcd;
	T_IM_CNR_OFL_CTRL sprCtrl = {
		.mode = E_IM_CNR_OFL_YCC_MODE_YCC422_SIMPLE,

		.width = CtImCnr_D_IM_CNR_TEST_H_PIXS,
		.lines = CtImCnr_D_IM_CNR_TEST_V_PIXS,

		.r_y_width = CtImCnr_D_IM_CNR_TEST_H_PIXS,
		.r_y_addr = CtImCnr_D_IM_CNR_TEST_IMG_SRC_Y_ADDR,

		.r_c_width = CtImCnr_D_IM_CNR_TEST_H_PIXS,
		.r_cb_addr = CtImCnr_D_IM_CNR_TEST_IMG_SRC_CB_ADDR,
		.r_cr_addr = CtImCnr_D_IM_CNR_TEST_IMG_SRC_CR_ADDR,

		.w_y_width = CtImCnr_D_IM_CNR_TEST_H_PIXS,
		.w_y_addr = CtImCnr_D_IM_CNR_TEST_IMG_DST_Y_ADDR,

		.w_c_width = CtImCnr_D_IM_CNR_TEST_H_PIXS,
		.w_cb_addr = CtImCnr_D_IM_CNR_TEST_IMG_DST_CB_ADDR,
		.w_cr_addr = CtImCnr_D_IM_CNR_TEST_IMG_DST_CR_ADDR,

		.work_addr = CtImCnr_D_IM_CNR_TEST_IMG_TMP_ADDR,

		.divide_top = E_IM_CNR_VPROCESS_NORM,
		.divide_bot = E_IM_CNR_VPROCESS_NORM,

		.pCallBack = NULL,
		.user_param = 0,
	};
	T_IM_CNR_CTRL_C sprCtrlC = {
		.enable = E_IM_CNR_ONOFF_ENABLE,
		.mid_freq_nr = {
			.enable = E_IM_CNR_ONOFF_ENABLE,
			.h_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.h_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.y_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
			.c_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
		},
		.low_freq_nr = {
			.enable = E_IM_CNR_ONOFF_ENABLE,
			.h_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.h_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.y_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
			.c_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
		},
	};
	T_IM_CNR_OFL_CTRL_Y sprCtrlY = {
		.enable = E_IM_CNR_ONOFF_DISABLE,
		.threshold_type = E_IM_CNR_THRES_REGISTER,
		.level = E_IM_CNR_LEVEL_HIGH,
		.h_y_threshold = 0xFF,
		.v_y_threshold = 0xFF,
		.h_c_threshold = 0xFF,
		.v_c_threshold = 0xFF,
		.alpha_blend_ratio = 0x1F,
	};

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_OFL_Open(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Open error = 0x%x\n", imErcd));
		return imErcd;
	}

	Im_CNR_OFL_Init(ch);

	imErcd = Im_CNR_OFL_Ctrl(ch, &sprCtrl);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OFL_Ctrl_C(ch, &sprCtrlC);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl_C error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OFL_Ctrl_Y(ch, &sprCtrlY);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl_Y error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OFL_Start_Sync(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Start Sync error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OFL_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_22: "
INT32 ct_im_cnr_ofl_1_22(CtImCnr3 *self)
{
	UCHAR ch = self->ch3;
	INT32 imErcd;
	const char C_DUMPMSG[] = "ch%d SPRTRG = %u\n";

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_OFL_Open(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Open error = 0x%x\n", imErcd));
		return imErcd;
	}

#ifdef CO_DEBUG_ON_PC
	io_cnr(ch)->OFL_REG_RW.SPRTRG.bit.SPRTRG = 3;
#endif //CO_DEBUG_ON_PC

	imErcd = Im_CNR_OFL_Stop(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Stop error = 0x%x\n", imErcd));
		return imErcd;
	}
	Im_CNR_On_Pclk(ch);
	Ddim_Print((C_DUMPMSG, D_IM_CNR_CH_0, io_cnr(D_IM_CNR_CH_0)->OFL_REG_RW.SPRTRG.bit.SPRTRG));
	Ddim_Print((C_DUMPMSG, D_IM_CNR_CH_1, io_cnr(D_IM_CNR_CH_1)->OFL_REG_RW.SPRTRG.bit.SPRTRG));
	Im_CNR_Off_Pclk(ch);

#ifdef CO_DEBUG_ON_PC
	io_cnr(ch)->OFL_REG_RW.SPRTRG.bit.SPRTRG = 2;
#endif //CO_DEBUG_ON_PC

	imErcd = Im_CNR_OFL_Stop(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Stop error = 0x%x\n", imErcd));
		return imErcd;
	}
	Im_CNR_On_Pclk(ch);
	Ddim_Print((C_DUMPMSG, D_IM_CNR_CH_0, io_cnr(D_IM_CNR_CH_0)->OFL_REG_RW.SPRTRG.bit.SPRTRG));
	Ddim_Print((C_DUMPMSG, D_IM_CNR_CH_1, io_cnr(D_IM_CNR_CH_1)->OFL_REG_RW.SPRTRG.bit.SPRTRG));
	Im_CNR_Off_Pclk(ch);

	imErcd = Im_CNR_OFL_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_33: "
INT32 ct_im_cnr_ofl_1_33(CtImCnr3 *self)
{
	INT32 imErcd;
	T_IM_CNR_OFL_CTRL_Y sprCtrlY = {
		.enable = E_IM_CNR_ONOFF_DISABLE,
		.threshold_type = E_IM_CNR_THRES_REGISTER,
		.level = E_IM_CNR_LEVEL_HIGH,
		.h_y_threshold = 0xFF,
		.v_y_threshold = 0xFF,
		.h_c_threshold = 0xFF,
		.v_c_threshold = 0xFF,
		.alpha_blend_ratio = 0x1F,
	};
	T_IM_CNR_RDMA_DATA_OFL_CTRL_Y rdma_ctrl_y;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_Set_RdmaValue_OFL_Ctrl_Y(&sprCtrlY, &rdma_ctrl_y);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Im_CNR_Set_RdmaValue_OFL_Ctrl_Y() error = 0x%x\n", imErcd));
		return imErcd;
	}

	// Check parameter
	Ddim_Print(("rdma_ctrl_y.YSPREN    = 0x%lx\n", rdma_ctrl_y.YSPREN.word));
	Ddim_Print(("rdma_ctrl_y.YSPRMODE  = 0x%lx\n", rdma_ctrl_y.YSPRMODE.word));
	Ddim_Print(("rdma_ctrl_y.YSPRFXEY  = 0x%lx\n", rdma_ctrl_y.YSPRFXEY.word));
	Ddim_Print(("rdma_ctrl_y.YSPRFXEC  = 0x%lx\n", rdma_ctrl_y.YSPRFXEC.word));
	Ddim_Print(("rdma_ctrl_y.YSPRALPBD = 0x%lx\n", rdma_ctrl_y.YSPRALPBD.word));

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_34: "
INT32 ct_im_cnr_ofl_1_34(CtImCnr3 *self)
{
	UCHAR ch = self->ch3;
	INT32 imErcd;
	const T_IM_CNR_RDMA_ADDR_OFL_YSPR_TBL* C_CNR_YSPR_TBL;
	ULONG size;
	ULONG* ptAddr;
	UINT32 loopcnt;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_Get_RdmaAddr_OFL_YSPR_Table(ch, &C_CNR_YSPR_TBL, &size);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Im_CNR_Get_RdmaAddr_OFL_YSPR_Table() error = 0x%x\n", imErcd));
		return imErcd;
	}

	// Check parameter
	Ddim_Print(("size = 0x%lx\n", size));
	ptAddr = (ULONG*)C_CNR_YSPR_TBL;
	for(loopcnt = 0; loopcnt < size; loopcnt+=4) {
		Ddim_Print(("address = 0x%lx\n", *ptAddr));
		ptAddr++;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_6_6: "
INT32 ct_im_cnr_6_6(CtImCnr3 *self)
{
	UCHAR ch = self->ch3;
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
	T_IM_CNR_RDMA_DATA_CSPR_MID_CC_C_TBL	rdmaMidCcCTbl;
	const  T_IM_CNR_RDMA_ADDR_CSPR_MID_CC_C_TBL*	C_MID_CC_C_TBL_ADDR;
	ULONG	size;

	ret = Im_CNR_Get_RdmaAddr_OFL_CSPR_Mid_CC_C_Table(ch, &C_MID_CC_C_TBL_ADDR, &size);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OFL_CSPR_Mid_CC_C_Table error = 0x%x\n", ret));
		return ret;
	}

	ret = Im_CNR_Set_RdmaValue_OFL_CSPR_Mid_CC_C_Table(&cnrTable, &rdmaMidCcCTbl);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OFL_CSPR_Mid_CC_C_Table error = 0x%x\n", ret));
		return ret;
	}

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)C_MID_CC_C_TBL_ADDR;
	rdmaCtrl.reg_data_top_addr	= (ULONG)&rdmaMidCcCTbl;
	rdmaCtrl.req_threshold		= E_IM_RDMA_PRCH_CNT_NOLIMIT;
	rdmaCtrl.int_mode			= E_IM_RDMA_INT_MODE_AND_ERR;
	rdmaCtrl.pCallBack			= NULL;
	ret = Im_RDMA_Ctrl_Quick_Start_Sync(D_DDIM_WAIT_END_TIME, &rdmaCtrl);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Ctrl error = 0x%x\n", ret));
		return ret;
	}

	if(ch == D_IM_CNR_CH_2){
		ctImCnrOflPrintDebugCMidCcCTbl(0);
		ctImCnrOflPrintDebugCMidCcCTbl(1);
	}
	else{
		ctImCnrOflPrintDebugCMidCcCTbl(ch);
	}

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_6_8: "
INT32 ct_im_cnr_6_8(CtImCnr3 *self)
{
	UCHAR ch = self->ch3;
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
	T_IM_CNR_RDMA_DATA_CSPR_LOW_CC_Y_TBL	rdmaLowCcYTbl;
	const  T_IM_CNR_RDMA_ADDR_CSPR_LOW_CC_Y_TBL*	C_LOW_CC_Y_TBL_ADDR;
	ULONG	size;

	ret = Im_CNR_Get_RdmaAddr_OFL_CSPR_Low_CC_Y_Table(ch, &C_LOW_CC_Y_TBL_ADDR, &size);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OFL_CSPR_Low_CC_Y_Table error = 0x%x\n", ret));
		return ret;
	}

	ret = Im_CNR_Set_RdmaValue_OFL_CSPR_Low_CC_Y_Table(&cnrTable, &rdmaLowCcYTbl);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OFL_CSPR_Low_CC_Y_Table error = 0x%x\n", ret));
		return ret;
	}

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)C_LOW_CC_Y_TBL_ADDR;
	rdmaCtrl.reg_data_top_addr	= (ULONG)&rdmaLowCcYTbl;
	rdmaCtrl.req_threshold		= E_IM_RDMA_PRCH_CNT_NOLIMIT;
	rdmaCtrl.int_mode			= E_IM_RDMA_INT_MODE_AND_ERR;
	rdmaCtrl.pCallBack			= NULL;
	ret = Im_RDMA_Ctrl_Quick_Start_Sync(D_DDIM_WAIT_END_TIME, &rdmaCtrl);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Ctrl error = 0x%x\n", ret));
		return ret;
	}

	if(ch == D_IM_CNR_CH_2){
		ctImCnrOflPrintDebugCLowCcYTbl(0);
		ctImCnrOflPrintDebugCLowCcYTbl(1);
	}
	else{
		ctImCnrOflPrintDebugCLowCcYTbl(ch);
	}

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_6_9: "
INT32 ct_im_cnr_6_9(CtImCnr3 *self)
{
	UCHAR ch = self->ch3;
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
	T_IM_CNR_RDMA_DATA_CSPR_LOW_CC_C_TBL	rdmaLowCcCTbl;
	const  T_IM_CNR_RDMA_ADDR_CSPR_LOW_CC_C_TBL*	C_LOW_CC_C_TBL_ADDR;
	ULONG	size;

	ret = Im_CNR_Get_RdmaAddr_OFL_CSPR_Low_CC_C_Table(ch, &C_LOW_CC_C_TBL_ADDR, &size);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OFL_CSPR_Low_CC_C_Table error = 0x%x\n", ret));
		return ret;
	}

	ret = Im_CNR_Set_RdmaValue_OFL_CSPR_Low_CC_C_Table(&cnrTable, &rdmaLowCcCTbl);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OFL_CSPR_Low_CC_C_Table error = 0x%x\n", ret));
		return ret;
	}

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)C_LOW_CC_C_TBL_ADDR;
	rdmaCtrl.reg_data_top_addr	= (ULONG)&rdmaLowCcCTbl;
	rdmaCtrl.req_threshold		= E_IM_RDMA_PRCH_CNT_NOLIMIT;
	rdmaCtrl.int_mode			= E_IM_RDMA_INT_MODE_AND_ERR;
	rdmaCtrl.pCallBack			= NULL;
	ret = Im_RDMA_Ctrl_Quick_Start_Sync(D_DDIM_WAIT_END_TIME, &rdmaCtrl);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Ctrl error = 0x%x\n", ret));
		return ret;
	}

	if(ch == D_IM_CNR_CH_2){
		ctImCnrOflPrintDebugCLowCcCTbl(0);
		ctImCnrOflPrintDebugCLowCcCTbl(1);
	}
	else{
		ctImCnrOflPrintDebugCLowCcCTbl(ch);
	}

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_55: "
INT32 ct_im_cnr_ofl_1_55(CtImCnr3 *self)
{
	INT32 imErcd;
	T_IM_CNR_CTRL_CC_SRC_DST cspr_sprd_cc = {
		.enable = (E_IM_CNR_ONOFF)1,
		.cb_table = {
			.bd1 = 0x7F,
			.bd2 = 0x7F,
			.bd3 = 0x7F,
			.bd4 = 0x7F,
			.bd5 = 0x7F,
			.of0 = 0x7F,
			.of1 = 0x7F,
			.of2 = 0x7F,
			.of3 = 0x7F,
			.of4 = 0x7F,
			.of5 = 0x7F,
			.gain0 = 0x07FF,
			.gain1 = 0x07FF,
			.gain2 = 0x07FF,
			.gain3 = 0x07FF,
			.gain4 = 0x07FF,
			.gain5 = 0x07FF
		},
		.cr_table = {
			.bd1 = 0x7F,
			.bd2 = 0x7F,
			.bd3 = 0x7F,
			.bd4 = 0x7F,
			.bd5 = 0x7F,
			.of0 = 0x7F,
			.of1 = 0x7F,
			.of2 = 0x7F,
			.of3 = 0x7F,
			.of4 = 0x7F,
			.of5 = 0x7F,
			.gain0 = 0x07FF,
			.gain1 = 0x07FF,
			.gain2 = 0x07FF,
			.gain3 = 0x07FF,
			.gain4 = 0x07FF,
			.gain5 = 0x07FF
		}
	};
	T_IM_CNR_RDMA_DATA_SPRD_CC_TBL rdma_cspr_sprd_cc;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_Set_RdmaValue_OFL_CSPR_SPRD_CC_Table(&cspr_sprd_cc, &rdma_cspr_sprd_cc);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Im_CNR_Set_RdmaValue_OFL_CSPR_SPRD_CC_Table() error = 0x%x\n", imErcd));
		return imErcd;
	}

	// Check parameter
	Ddim_Print(("rdma_cspr_sprd_cc.SPRD               = 0x%lx\n", rdma_cspr_sprd_cc.SPRD.word));

	Ddim_Print(("rdma_cspr_sprd_cc.SPRDCBOF.SPRDCBOF1 = 0x%lx\n", rdma_cspr_sprd_cc.SPRDCBOF.SPRDCBOF1.word));
	Ddim_Print(("rdma_cspr_sprd_cc.SPRDCBOF.SPRDCBOF2 = 0x%lx\n", rdma_cspr_sprd_cc.SPRDCBOF.SPRDCBOF2.word));
	Ddim_Print(("rdma_cspr_sprd_cc.SPRDCBGA.SPRDCBGA1 = 0x%lx\n", rdma_cspr_sprd_cc.SPRDCBGA.SPRDCBGA1.word));
	Ddim_Print(("rdma_cspr_sprd_cc.SPRDCBGA.SPRDCBGA2 = 0x%lx\n", rdma_cspr_sprd_cc.SPRDCBGA.SPRDCBGA2.word));
	Ddim_Print(("rdma_cspr_sprd_cc.SPRDCBGA.SPRDCBGA3 = 0x%lx\n", rdma_cspr_sprd_cc.SPRDCBGA.SPRDCBGA3.word));
	Ddim_Print(("rdma_cspr_sprd_cc.SPRDCBBD.SPRDCBBD1 = 0x%lx\n", rdma_cspr_sprd_cc.SPRDCBBD.SPRDCBBD1.word));
	Ddim_Print(("rdma_cspr_sprd_cc.SPRDCBBD.SPRDCBBD2 = 0x%lx\n", rdma_cspr_sprd_cc.SPRDCBBD.SPRDCBBD2.word));

	Ddim_Print(("rdma_cspr_sprd_cc.SPRDCROF.SPRDCROF1 = 0x%lx\n", rdma_cspr_sprd_cc.SPRDCROF.SPRDCROF1.word));
	Ddim_Print(("rdma_cspr_sprd_cc.SPRDCROF.SPRDCROF2 = 0x%lx\n", rdma_cspr_sprd_cc.SPRDCROF.SPRDCROF2.word));
	Ddim_Print(("rdma_cspr_sprd_cc.SPRDCRGA.SPRDCRGA1 = 0x%lx\n", rdma_cspr_sprd_cc.SPRDCRGA.SPRDCRGA1.word));
	Ddim_Print(("rdma_cspr_sprd_cc.SPRDCRGA.SPRDCRGA2 = 0x%lx\n", rdma_cspr_sprd_cc.SPRDCRGA.SPRDCRGA2.word));
	Ddim_Print(("rdma_cspr_sprd_cc.SPRDCRGA.SPRDCRGA3 = 0x%lx\n", rdma_cspr_sprd_cc.SPRDCRGA.SPRDCRGA3.word));
	Ddim_Print(("rdma_cspr_sprd_cc.SPRDCRBD.SPRDCRBD1 = 0x%lx\n", rdma_cspr_sprd_cc.SPRDCRBD.SPRDCRBD1.word));
	Ddim_Print(("rdma_cspr_sprd_cc.SPRDCRBD.SPRDCRBD2 = 0x%lx\n", rdma_cspr_sprd_cc.SPRDCRBD.SPRDCRBD2.word));

	return imErcd;
}

CtImCnr3* ct_im_cnr3_new(void) 
{
    CtImCnr3 *self = g_object_new(CT_TYPE_IM_CNR3, NULL);
    return self;
}
