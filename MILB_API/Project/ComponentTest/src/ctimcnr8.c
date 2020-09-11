/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :王印斌
*@brief               :CtImCnr8类
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
#include "driver_common.h"
#include "ddim_user_custom.h"
#include "im_rdma.h"
#include "jdscnr.h"
#include "ctimcnr.h"
#include "ctimcnr8.h"

#include <string.h>
#include <stdlib.h>

G_DEFINE_TYPE(CtImCnr8, ct_im_cnr8, G_TYPE_OBJECT); 
#define CT_IM_CNR8_GET_PRIVATE(o) (G_OBJECT_GET_PRIVATE ((o), CT_TYPE_IM_CNR8, CtImCnr8Private))

struct _CtImCnr8Private
{
};

static void ctImCnrOtfPrintDebugCMidCcYTbl(UCHAR ch);
static void ctImCnrOtfPrintDebugCMidCcCTbl(UCHAR ch);
static void ctImCnrOtfPrintDebugCLowYTbl(UCHAR ch);
static void ctImCnrOtfPrintDebugCLowCcYTbl(UCHAR ch);

static void ct_im_cnr8_constructor(CtImCnr8 *self) 
{
//	CtImCnr8Private *priv = CT_IM_CNR8_GET_PRIVATE(self);
}

static void ct_im_cnr8_destructor(CtImCnr8 *self) 
{
//	CtImCnr8Private *priv = CT_IM_CNR8_GET_PRIVATE(self);
}

static void ctImCnrOtfPrintDebugCMidCcYTbl(UCHAR ch)
{
	UCHAR loop, loopSta, loopEnd;

	Im_CNR_On_Pclk(ch);

	ct_im_cnr_get_loop_cnt(ch, &loopSta, &loopEnd);

	for(loop = loopSta; loop <= loopEnd; loop++){
		Ddim_Print(("ch[%d]\n",           loop));
		Ddim_Print(("MCCSCLBD_1 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCCSCLBD.MCCSCLBD1.bit.MCCSCLBD_1));
		Ddim_Print(("MCCSCLBD_2 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCCSCLBD.MCCSCLBD1.bit.MCCSCLBD_2));
		Ddim_Print(("MCCSCLBD_3 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCCSCLBD.MCCSCLBD1.bit.MCCSCLBD_3));
		Ddim_Print(("MCCSCLBD_4 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCCSCLBD.MCCSCLBD1.bit.MCCSCLBD_4));
		Ddim_Print(("MCCSCLBD_5 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCCSCLBD.MCCSCLBD2.bit.MCCSCLBD_5));

		Ddim_Print(("MCCSCLOF_0 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCCSCLOF.MCCSCLOF1.bit.MCCSCLOF_0));
		Ddim_Print(("MCCSCLOF_1 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCCSCLOF.MCCSCLOF1.bit.MCCSCLOF_1));
		Ddim_Print(("MCCSCLOF_2 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCCSCLOF.MCCSCLOF1.bit.MCCSCLOF_2));
		Ddim_Print(("MCCSCLOF_3 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCCSCLOF.MCCSCLOF1.bit.MCCSCLOF_3));
		Ddim_Print(("MCCSCLOF_4 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCCSCLOF.MCCSCLOF2.bit.MCCSCLOF_4));
		Ddim_Print(("MCCSCLOF_5 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCCSCLOF.MCCSCLOF2.bit.MCCSCLOF_5));

		Ddim_Print(("MCCSCLGA_0 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCCSCLGA.MCCSCLGA1.bit.MCCSCLGA_0));
		Ddim_Print(("MCCSCLGA_1 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCCSCLGA.MCCSCLGA1.bit.MCCSCLGA_1));
		Ddim_Print(("MCCSCLGA_2 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCCSCLGA.MCCSCLGA1.bit.MCCSCLGA_2));
		Ddim_Print(("MCCSCLGA_3 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCCSCLGA.MCCSCLGA1.bit.MCCSCLGA_3));
		Ddim_Print(("MCCSCLGA_4 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCCSCLGA.MCCSCLGA2.bit.MCCSCLGA_4));
		Ddim_Print(("MCCSCLGA_5 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCCSCLGA.MCCSCLGA2.bit.MCCSCLGA_5));
	}

	Im_CNR_Off_Pclk(ch);
}

static void ctImCnrOtfPrintDebugCMidCcCTbl(UCHAR ch)
{
	UCHAR loop, loopSta, loopEnd;

	Im_CNR_On_Pclk(ch);

	ct_im_cnr_get_loop_cnt(ch, &loopSta, &loopEnd);

	for(loop = loopSta; loop <= loopEnd; loop++){
		Ddim_Print(("ch[%d]\n",           loop));
		Ddim_Print(("MCSSCLBD_1 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCSSCLBD.MCSSCLBD1.bit.MCSSCLBD_1));
		Ddim_Print(("MCSSCLBD_2 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCSSCLBD.MCSSCLBD1.bit.MCSSCLBD_2));
		Ddim_Print(("MCSSCLBD_3 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCSSCLBD.MCSSCLBD1.bit.MCSSCLBD_3));
		Ddim_Print(("MCSSCLBD_4 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCSSCLBD.MCSSCLBD1.bit.MCSSCLBD_4));
		Ddim_Print(("MCSSCLBD_5 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCSSCLBD.MCSSCLBD2.bit.MCSSCLBD_5));

		Ddim_Print(("MCSSCLOF_0 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCSSCLOF.MCSSCLOF1.bit.MCSSCLOF_0));
		Ddim_Print(("MCSSCLOF_1 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCSSCLOF.MCSSCLOF1.bit.MCSSCLOF_1));
		Ddim_Print(("MCSSCLOF_2 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCSSCLOF.MCSSCLOF1.bit.MCSSCLOF_2));
		Ddim_Print(("MCSSCLOF_3 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCSSCLOF.MCSSCLOF1.bit.MCSSCLOF_3));
		Ddim_Print(("MCSSCLOF_4 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCSSCLOF.MCSSCLOF2.bit.MCSSCLOF_4));
		Ddim_Print(("MCSSCLOF_5 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCSSCLOF.MCSSCLOF2.bit.MCSSCLOF_5));

		Ddim_Print(("MCSSCLGA_0 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCSSCLGA.MCSSCLGA1.bit.MCSSCLGA_0));
		Ddim_Print(("MCSSCLGA_1 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCSSCLGA.MCSSCLGA1.bit.MCSSCLGA_1));
		Ddim_Print(("MCSSCLGA_2 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCSSCLGA.MCSSCLGA1.bit.MCSSCLGA_2));
		Ddim_Print(("MCSSCLGA_3 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCSSCLGA.MCSSCLGA1.bit.MCSSCLGA_3));
		Ddim_Print(("MCSSCLGA_4 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCSSCLGA.MCSSCLGA2.bit.MCSSCLGA_4));
		Ddim_Print(("MCSSCLGA_5 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCSSCLGA.MCSSCLGA2.bit.MCSSCLGA_5));
	}

	Im_CNR_Off_Pclk(ch);
}

static void ctImCnrOtfPrintDebugCLowYTbl(UCHAR ch)
{
	UCHAR loop, loopSta, loopEnd;

	Im_CNR_On_Pclk(ch);

	ct_im_cnr_get_loop_cnt(ch, &loopSta, &loopEnd);

	for(loop = loopSta; loop <= loopEnd; loop++){
		Ddim_Print(("ch[%d]\n",           loop));
		Ddim_Print(("LCYSCLBD_1 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCYSCLBD.LCYSCLBD1.bit.LCYSCLBD_1));
		Ddim_Print(("LCYSCLBD_2 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCYSCLBD.LCYSCLBD1.bit.LCYSCLBD_2));
		Ddim_Print(("LCYSCLBD_3 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCYSCLBD.LCYSCLBD1.bit.LCYSCLBD_3));
		Ddim_Print(("LCYSCLBD_4 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCYSCLBD.LCYSCLBD1.bit.LCYSCLBD_4));
		Ddim_Print(("LCYSCLBD_5 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCYSCLBD.LCYSCLBD2.bit.LCYSCLBD_5));

		Ddim_Print(("LCYSCLOF_0 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCYSCLOF.LCYSCLOF1.bit.LCYSCLOF_0));
		Ddim_Print(("LCYSCLOF_1 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCYSCLOF.LCYSCLOF1.bit.LCYSCLOF_1));
		Ddim_Print(("LCYSCLOF_2 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCYSCLOF.LCYSCLOF1.bit.LCYSCLOF_2));
		Ddim_Print(("LCYSCLOF_3 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCYSCLOF.LCYSCLOF1.bit.LCYSCLOF_3));
		Ddim_Print(("LCYSCLOF_4 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCYSCLOF.LCYSCLOF2.bit.LCYSCLOF_4));
		Ddim_Print(("LCYSCLOF_5 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCYSCLOF.LCYSCLOF2.bit.LCYSCLOF_5));

		Ddim_Print(("LCYSCLGA_0 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCYSCLGA.LCYSCLGA1.bit.LCYSCLGA_0));
		Ddim_Print(("LCYSCLGA_1 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCYSCLGA.LCYSCLGA1.bit.LCYSCLGA_1));
		Ddim_Print(("LCYSCLGA_2 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCYSCLGA.LCYSCLGA1.bit.LCYSCLGA_2));
		Ddim_Print(("LCYSCLGA_3 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCYSCLGA.LCYSCLGA1.bit.LCYSCLGA_3));
		Ddim_Print(("LCYSCLGA_4 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCYSCLGA.LCYSCLGA2.bit.LCYSCLGA_4));
		Ddim_Print(("LCYSCLGA_5 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCYSCLGA.LCYSCLGA2.bit.LCYSCLGA_5));
	}

	Im_CNR_Off_Pclk(ch);
}

static void ctImCnrOtfPrintDebugCLowCcYTbl(UCHAR ch)
{
	UCHAR loop, loopSta, loopEnd;

	Im_CNR_On_Pclk(ch);

	ct_im_cnr_get_loop_cnt(ch, &loopSta, &loopEnd);

	for(loop = loopSta; loop <= loopEnd; loop++){
		Ddim_Print(("ch[%d]\n",           loop));
		Ddim_Print(("LCCSCLBD_1 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCCSCLBD.LCCSCLBD1.bit.LCCSCLBD_1));
		Ddim_Print(("LCCSCLBD_2 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCCSCLBD.LCCSCLBD1.bit.LCCSCLBD_2));
		Ddim_Print(("LCCSCLBD_3 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCCSCLBD.LCCSCLBD1.bit.LCCSCLBD_3));
		Ddim_Print(("LCCSCLBD_4 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCCSCLBD.LCCSCLBD1.bit.LCCSCLBD_4));
		Ddim_Print(("LCCSCLBD_5 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCCSCLBD.LCCSCLBD2.bit.LCCSCLBD_5));

		Ddim_Print(("LCCSCLOF_0 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCCSCLOF.LCCSCLOF1.bit.LCCSCLOF_0));
		Ddim_Print(("LCCSCLOF_1 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCCSCLOF.LCCSCLOF1.bit.LCCSCLOF_1));
		Ddim_Print(("LCCSCLOF_2 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCCSCLOF.LCCSCLOF1.bit.LCCSCLOF_2));
		Ddim_Print(("LCCSCLOF_3 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCCSCLOF.LCCSCLOF1.bit.LCCSCLOF_3));
		Ddim_Print(("LCCSCLOF_4 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCCSCLOF.LCCSCLOF2.bit.LCCSCLOF_4));
		Ddim_Print(("LCCSCLOF_5 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCCSCLOF.LCCSCLOF2.bit.LCCSCLOF_5));

		Ddim_Print(("LCCSCLGA_0 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCCSCLGA.LCCSCLGA1.bit.LCCSCLGA_0));
		Ddim_Print(("LCCSCLGA_1 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCCSCLGA.LCCSCLGA1.bit.LCCSCLGA_1));
		Ddim_Print(("LCCSCLGA_2 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCCSCLGA.LCCSCLGA1.bit.LCCSCLGA_2));
		Ddim_Print(("LCCSCLGA_3 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCCSCLGA.LCCSCLGA1.bit.LCCSCLGA_3));
		Ddim_Print(("LCCSCLGA_4 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCCSCLGA.LCCSCLGA2.bit.LCCSCLGA_4));
		Ddim_Print(("LCCSCLGA_5 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCCSCLGA.LCCSCLGA2.bit.LCCSCLGA_5));
	}

	Im_CNR_Off_Pclk(ch);
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_3_14: "
INT32 ct_im_cnr_otf_3_14(CtImCnr8 *self)
{
	UCHAR ch = self->ch8;
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

	imErcd = Im_CNR_OTF_Open(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Open error = 0x%x\n", imErcd));
		return imErcd;
	}

	for(loopcnt = 0; loopcnt < (sizeof(sprTbl) / sizeof(sprTbl[0])); loopcnt++) {
		Ddim_Print(("** %u\n", loopcnt));
		imErcd = Im_CNR_OTF_Set_CSPR_Mid_CC_Y_Table(ch, &sprTbl[loopcnt]);
		if(imErcd != D_DDIM_OK) {
			Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl error = 0x%x\n", imErcd));
			return imErcd;
		}
		ctImCnrOtfPrintDebugCMidCcYTbl(ch);
	}

	imErcd = Im_CNR_OTF_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_3_15: "
INT32 ct_im_cnr_otf_3_15(CtImCnr8 *self)
{
	UCHAR ch = self->ch8;
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

	imErcd = Im_CNR_OTF_Open(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Open error = 0x%x\n", imErcd));
		return imErcd;
	}

	for(loopcnt = 0; loopcnt < (sizeof(sprTbl) / sizeof(sprTbl[0])); loopcnt++) {
		Ddim_Print(("** %u\n", loopcnt));
		imErcd = Im_CNR_OTF_Set_CSPR_Mid_CC_C_Table(ch, &sprTbl[loopcnt]);
		if(imErcd != D_DDIM_OK) {
			Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl error = 0x%x\n", imErcd));
			return imErcd;
		}
		ctImCnrOtfPrintDebugCMidCcCTbl(ch);
	}

	imErcd = Im_CNR_OTF_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_3_16: "
INT32 ct_im_cnr_otf_3_16(CtImCnr8 *self)
{
	UCHAR ch = self->ch8;
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

	imErcd = Im_CNR_OTF_Open(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Open error = 0x%x\n", imErcd));
		return imErcd;
	}

	for(loopcnt = 0; loopcnt < (sizeof(sprTbl) / sizeof(sprTbl[0])); loopcnt++) {
		Ddim_Print(("** %u\n", loopcnt));
		imErcd = Im_CNR_OTF_Set_CSPR_Low_Y_Table(ch, &sprTbl[loopcnt]);
		if(imErcd != D_DDIM_OK) {
			Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl error = 0x%x\n", imErcd));
			return imErcd;
		}
		ctImCnrOtfPrintDebugCLowYTbl(ch);
	}

	imErcd = Im_CNR_OTF_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_3_17: "
INT32 ct_im_cnr_otf_3_17(CtImCnr8 *self)
{
	UCHAR ch = self->ch8;
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

	imErcd = Im_CNR_OTF_Open(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Open error = 0x%x\n", imErcd));
		return imErcd;
	}

	for(loopcnt = 0; loopcnt < (sizeof(sprTbl) / sizeof(sprTbl[0])); loopcnt++) {
		Ddim_Print(("** %u\n", loopcnt));
		imErcd = Im_CNR_OTF_Set_CSPR_Low_CC_Y_Table(ch, &sprTbl[loopcnt]);
		if(imErcd != D_DDIM_OK) {
			Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl error = 0x%x\n", imErcd));
			return imErcd;
		}
		ctImCnrOtfPrintDebugCLowCcYTbl(ch);
	}

	imErcd = Im_CNR_OTF_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_3_21: "
INT32 ct_im_cnr_otf_3_21(CtImCnr8 *self)
{
	UCHAR ch = self->ch8;
	INT32 imErcd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	Im_CNR_OTF_Open(ch, 100);
	imErcd = Im_CNR_OTF_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_3_22: "
INT32 ct_im_cnr_otf_3_22(CtImCnr8 *self)
{
	UCHAR ch = self->ch8;
	INT32 imErcd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_OTF_Reset(ch);

	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Reset error = 0x%x\n", imErcd));
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_6_16: "
INT32 ct_im_cnr_6_16(CtImCnr8 *self)
{
	UCHAR ch = self->ch8;
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

	ret = Im_CNR_Get_RdmaAddr_OTF_CSPR_Mid_CC_Y_Table(ch, &C_MID_CC_Y_TBL_ADDR, &size);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OTF_CSPR_Mid_Y_Table error = 0x%x\n", ret));
		return ret;
	}

	ret = Im_CNR_Set_RdmaValue_OTF_CSPR_Mid_CC_Y_Table(&cnrTable, &rdmaMidCcYTbl);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OTF_CSPR_Mid_Y_Table error = 0x%x\n", ret));
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
		ctImCnrOtfPrintDebugCMidCcYTbl(0);
		ctImCnrOtfPrintDebugCMidCcYTbl(1);
	}
	else{
		ctImCnrOtfPrintDebugCMidCcYTbl(ch);
	}

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_6_17: "
INT32 ct_im_cnr_6_17(CtImCnr8 *self)
{
	UCHAR ch = self->ch8;
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
	const  T_IM_CNR_RDMA_ADDR_CSPR_MID_CC_C_TBL*	C_MID_CC_TBL_ADDR;
	ULONG	size;

	ret = Im_CNR_Get_RdmaAddr_OTF_CSPR_Mid_CC_C_Table(ch, &C_MID_CC_TBL_ADDR, &size);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OTF_CSPR_Mid_CC_C_Table error = 0x%x\n", ret));
		return ret;
	}

	ret = Im_CNR_Set_RdmaValue_OTF_CSPR_Mid_CC_C_Table(&cnrTable, &rdmaMidCcCTbl);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OTF_CSPR_Mid_CC_C_Table error = 0x%x\n", ret));
		return ret;
	}

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)C_MID_CC_TBL_ADDR;
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
		ctImCnrOtfPrintDebugCMidCcCTbl(0);
		ctImCnrOtfPrintDebugCMidCcCTbl(1);
	}
	else{
		ctImCnrOtfPrintDebugCMidCcCTbl(ch);
	}

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_6_18: "
INT32 ct_im_cnr_6_18(CtImCnr8 *self)
{
	UCHAR ch = self->ch8;
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
	const  T_IM_CNR_RDMA_ADDR_CSPR_LOW_Y_TBL*	C_LOW_TY_TBL_ADDR;
	ULONG	size;

	ret = Im_CNR_Get_RdmaAddr_OTF_CSPR_Low_Y_Table(ch, &C_LOW_TY_TBL_ADDR, &size);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OTF_CSPR_Low_Y_Table error = 0x%x\n", ret));
		return ret;
	}

	ret = Im_CNR_Set_RdmaValue_OTF_CSPR_Low_Y_Table(&cnrTable, &rdmaLowYTbl);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OTF_CSPR_Low_Y_Table error = 0x%x\n", ret));
		return ret;
	}

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)C_LOW_TY_TBL_ADDR;
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
		ctImCnrOtfPrintDebugCLowYTbl(0);
		ctImCnrOtfPrintDebugCLowYTbl(1);
	}
	else{
		ctImCnrOtfPrintDebugCLowYTbl(ch);
	}

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_6_19: "
INT32 ct_im_cnr_6_19(CtImCnr8 *self)
{
	UCHAR ch = self->ch8;
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

	ret = Im_CNR_Get_RdmaAddr_OTF_CSPR_Low_CC_Y_Table(ch, &C_LOW_CC_Y_TBL_ADDR, &size);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OTF_CSPR_Low_CC_Y_Table error = 0x%x\n", ret));
		return ret;
	}

	ret = Im_CNR_Set_RdmaValue_OTF_CSPR_Low_CC_Y_Table(&cnrTable, &rdmaLowCcYTbl);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OTF_CSPR_Low_CC_Y_Table error = 0x%x\n", ret));
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
		ctImCnrOtfPrintDebugCLowCcYTbl(0);
		ctImCnrOtfPrintDebugCLowCcYTbl(1);
	}
	else{
		ctImCnrOtfPrintDebugCLowCcYTbl(ch);
	}

	return D_DDIM_OK;
}

CtImCnr8* ct_im_cnr8_new(void) 
{
    CtImCnr8 *self = g_object_new(CT_TYPE_IM_CNR8, NULL);
    return self;
}
