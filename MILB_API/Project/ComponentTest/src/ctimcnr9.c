/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :王印斌
*@brief               :CtImCnr9类
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
#include "ctimcnr9.h"

#include <string.h>
#include <stdlib.h>

G_DEFINE_TYPE(CtImCnr9, ct_im_cnr9, G_TYPE_OBJECT); 
#define CT_IM_CNR9_GET_PRIVATE(o) (G_OBJECT_GET_PRIVATE ((o), CT_TYPE_IM_CNR9, CtImCnr9Private))

struct _CtImCnr9Private
{
};

static void ctImCnrOtfPrintDebugCLowCcCTbl(UCHAR ch);
static void ctImCnrOtfPrintDebugCtrlSrcCc(UCHAR ch);
static void ctImCnrOtfPrintDebugCtrlDstCc(UCHAR ch);

static void ct_im_cnr9_constructor(CtImCnr9 *self) 
{
}

static void ct_im_cnr9_destructor(CtImCnr9 *self) 
{
}

static void ctImCnrOtfPrintDebugCLowCcCTbl(UCHAR ch)
{
	UCHAR loop, loopSta, loopEnd;

	Im_CNR_On_Pclk(ch);

	ct_im_cnr_get_loop_cnt(ch, &loopSta, &loopEnd);

	for(loop = loopSta; loop <= loopEnd; loop++){
		Ddim_Print(("ch[%d]\n",           loop));
		Ddim_Print(("LCSSCLBD_1 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCSSCLBD.LCSSCLBD1.bit.LCSSCLBD_1));
		Ddim_Print(("LCSSCLBD_2 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCSSCLBD.LCSSCLBD1.bit.LCSSCLBD_2));
		Ddim_Print(("LCSSCLBD_3 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCSSCLBD.LCSSCLBD1.bit.LCSSCLBD_3));
		Ddim_Print(("LCSSCLBD_4 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCSSCLBD.LCSSCLBD1.bit.LCSSCLBD_4));
		Ddim_Print(("LCSSCLBD_5 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCSSCLBD.LCSSCLBD2.bit.LCSSCLBD_5));

		Ddim_Print(("LCSSCLOF_0 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCSSCLOF.LCSSCLOF1.bit.LCSSCLOF_0));
		Ddim_Print(("LCSSCLOF_1 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCSSCLOF.LCSSCLOF1.bit.LCSSCLOF_1));
		Ddim_Print(("LCSSCLOF_2 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCSSCLOF.LCSSCLOF1.bit.LCSSCLOF_2));
		Ddim_Print(("LCSSCLOF_3 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCSSCLOF.LCSSCLOF1.bit.LCSSCLOF_3));
		Ddim_Print(("LCSSCLOF_4 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCSSCLOF.LCSSCLOF2.bit.LCSSCLOF_4));
		Ddim_Print(("LCSSCLOF_5 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCSSCLOF.LCSSCLOF2.bit.LCSSCLOF_5));

		Ddim_Print(("LCSSCLGA_0 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCSSCLGA.LCSSCLGA1.bit.LCSSCLGA_0));
		Ddim_Print(("LCSSCLGA_1 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCSSCLGA.LCSSCLGA1.bit.LCSSCLGA_1));
		Ddim_Print(("LCSSCLGA_2 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCSSCLGA.LCSSCLGA1.bit.LCSSCLGA_2));
		Ddim_Print(("LCSSCLGA_3 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCSSCLGA.LCSSCLGA1.bit.LCSSCLGA_3));
		Ddim_Print(("LCSSCLGA_4 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCSSCLGA.LCSSCLGA2.bit.LCSSCLGA_4));
		Ddim_Print(("LCSSCLGA_5 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCSSCLGA.LCSSCLGA2.bit.LCSSCLGA_5));
	}

	Im_CNR_Off_Pclk(ch);
}

static void ctImCnrOtfPrintDebugCtrlSrcCc(UCHAR ch)
{
	UCHAR loop, loopSta, loopEnd;

	Im_CNR_On_Pclk(ch);

	ct_im_cnr_get_loop_cnt(ch, &loopSta, &loopEnd);

	for(loop = loopSta; loop <= loopEnd; loop++){
		Ddim_Print(("ch[%d]\n",           loop));
		Ddim_Print(("SPRS       = %u\n",   io_cnr(loop)->OTF_CSPR_REG.SPRS.bit.SPRS));

		// CB
		Ddim_Print(("SPRSCBBD_1 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRSCBBD.SPRSCBBD1.bit.SPRSCBBD_1));
		Ddim_Print(("SPRSCBBD_2 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRSCBBD.SPRSCBBD1.bit.SPRSCBBD_2));
		Ddim_Print(("SPRSCBBD_3 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRSCBBD.SPRSCBBD1.bit.SPRSCBBD_3));
		Ddim_Print(("SPRSCBBD_4 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRSCBBD.SPRSCBBD1.bit.SPRSCBBD_4));
		Ddim_Print(("SPRSCBBD_5 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRSCBBD.SPRSCBBD2.bit.SPRSCBBD_5));

		Ddim_Print(("SPRSCBOF_0 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRSCBOF.SPRSCBOF1.bit.SPRSCBOF_0));
		Ddim_Print(("SPRSCBOF_1 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRSCBOF.SPRSCBOF1.bit.SPRSCBOF_1));
		Ddim_Print(("SPRSCBOF_2 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRSCBOF.SPRSCBOF1.bit.SPRSCBOF_2));
		Ddim_Print(("SPRSCBOF_3 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRSCBOF.SPRSCBOF1.bit.SPRSCBOF_3));
		Ddim_Print(("SPRSCBOF_4 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRSCBOF.SPRSCBOF2.bit.SPRSCBOF_4));
		Ddim_Print(("SPRSCBOF_5 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRSCBOF.SPRSCBOF2.bit.SPRSCBOF_5));

		Ddim_Print(("SPRSCBGA_0 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRSCBGA.SPRSCBGA1.bit.SPRSCBGA_0));
		Ddim_Print(("SPRSCBGA_1 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRSCBGA.SPRSCBGA1.bit.SPRSCBGA_1));
		Ddim_Print(("SPRSCBGA_2 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRSCBGA.SPRSCBGA2.bit.SPRSCBGA_2));
		Ddim_Print(("SPRSCBGA_3 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRSCBGA.SPRSCBGA2.bit.SPRSCBGA_3));
		Ddim_Print(("SPRSCBGA_4 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRSCBGA.SPRSCBGA3.bit.SPRSCBGA_4));
		Ddim_Print(("SPRSCBGA_5 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRSCBGA.SPRSCBGA3.bit.SPRSCBGA_5));

		// CR
		Ddim_Print(("SPRSCRBD_1 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRSCRBD.SPRSCRBD1.bit.SPRSCRBD_1));
		Ddim_Print(("SPRSCRBD_2 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRSCRBD.SPRSCRBD1.bit.SPRSCRBD_2));
		Ddim_Print(("SPRSCRBD_3 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRSCRBD.SPRSCRBD1.bit.SPRSCRBD_3));
		Ddim_Print(("SPRSCRBD_4 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRSCRBD.SPRSCRBD1.bit.SPRSCRBD_4));
		Ddim_Print(("SPRSCRBD_5 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRSCRBD.SPRSCRBD2.bit.SPRSCRBD_5));

		Ddim_Print(("SPRSCROF_0 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRSCROF.SPRSCROF1.bit.SPRSCROF_0));
		Ddim_Print(("SPRSCROF_1 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRSCROF.SPRSCROF1.bit.SPRSCROF_1));
		Ddim_Print(("SPRSCROF_2 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRSCROF.SPRSCROF1.bit.SPRSCROF_2));
		Ddim_Print(("SPRSCROF_3 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRSCROF.SPRSCROF1.bit.SPRSCROF_3));
		Ddim_Print(("SPRSCROF_4 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRSCROF.SPRSCROF2.bit.SPRSCROF_4));
		Ddim_Print(("SPRSCROF_5 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRSCROF.SPRSCROF2.bit.SPRSCROF_5));

		Ddim_Print(("SPRSCRGA_0 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRSCRGA.SPRSCRGA1.bit.SPRSCRGA_0));
		Ddim_Print(("SPRSCRGA_1 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRSCRGA.SPRSCRGA1.bit.SPRSCRGA_1));
		Ddim_Print(("SPRSCRGA_2 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRSCRGA.SPRSCRGA2.bit.SPRSCRGA_2));
		Ddim_Print(("SPRSCRGA_3 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRSCRGA.SPRSCRGA2.bit.SPRSCRGA_3));
		Ddim_Print(("SPRSCRGA_4 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRSCRGA.SPRSCRGA3.bit.SPRSCRGA_4));
		Ddim_Print(("SPRSCRGA_5 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRSCRGA.SPRSCRGA3.bit.SPRSCRGA_5));
	}

	Im_CNR_Off_Pclk(ch);
}

static void ctImCnrOtfPrintDebugCtrlDstCc(UCHAR ch)
{
	UCHAR loop, loopSta, loopEnd;

	Im_CNR_On_Pclk(ch);

	ct_im_cnr_get_loop_cnt(ch, &loopSta, &loopEnd);

	for(loop = loopSta; loop <= loopEnd; loop++){
		Ddim_Print(("ch[%d]\n",           loop));
		Ddim_Print(("SPRD       = %u\n",   io_cnr(loop)->OTF_CSPR_REG.SPRD.bit.SPRD));

		// CB
		Ddim_Print(("SPRSCBBD_1 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRDCBBD.SPRDCBBD1.bit.SPRDCBBD_1));
		Ddim_Print(("SPRSCBBD_2 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRDCBBD.SPRDCBBD1.bit.SPRDCBBD_2));
		Ddim_Print(("SPRSCBBD_3 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRDCBBD.SPRDCBBD1.bit.SPRDCBBD_3));
		Ddim_Print(("SPRSCBBD_4 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRDCBBD.SPRDCBBD1.bit.SPRDCBBD_4));
		Ddim_Print(("SPRSCBBD_5 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRDCBBD.SPRDCBBD2.bit.SPRDCBBD_5));

		Ddim_Print(("SPRSCBOF_0 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRDCBOF.SPRDCBOF1.bit.SPRDCBOF_0));
		Ddim_Print(("SPRSCBOF_1 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRDCBOF.SPRDCBOF1.bit.SPRDCBOF_1));
		Ddim_Print(("SPRSCBOF_2 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRDCBOF.SPRDCBOF1.bit.SPRDCBOF_2));
		Ddim_Print(("SPRSCBOF_3 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRDCBOF.SPRDCBOF1.bit.SPRDCBOF_3));
		Ddim_Print(("SPRSCBOF_4 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRDCBOF.SPRDCBOF2.bit.SPRDCBOF_4));
		Ddim_Print(("SPRSCBOF_5 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRDCBOF.SPRDCBOF2.bit.SPRDCBOF_5));

		Ddim_Print(("SPRSCBGA_0 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRDCBGA.SPRDCBGA1.bit.SPRDCBGA_0));
		Ddim_Print(("SPRSCBGA_1 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRDCBGA.SPRDCBGA1.bit.SPRDCBGA_1));
		Ddim_Print(("SPRSCBGA_2 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRDCBGA.SPRDCBGA2.bit.SPRDCBGA_2));
		Ddim_Print(("SPRSCBGA_3 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRDCBGA.SPRDCBGA2.bit.SPRDCBGA_3));
		Ddim_Print(("SPRSCBGA_4 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRDCBGA.SPRDCBGA3.bit.SPRDCBGA_4));
		Ddim_Print(("SPRSCBGA_5 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRDCBGA.SPRDCBGA3.bit.SPRDCBGA_5));

		// CR
		Ddim_Print(("SPRSCRBD_1 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRDCRBD.SPRDCRBD1.bit.SPRDCRBD_1));
		Ddim_Print(("SPRSCRBD_2 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRDCRBD.SPRDCRBD1.bit.SPRDCRBD_2));
		Ddim_Print(("SPRSCRBD_3 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRDCRBD.SPRDCRBD1.bit.SPRDCRBD_3));
		Ddim_Print(("SPRSCRBD_4 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRDCRBD.SPRDCRBD1.bit.SPRDCRBD_4));
		Ddim_Print(("SPRSCRBD_5 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRDCRBD.SPRDCRBD2.bit.SPRDCRBD_5));

		Ddim_Print(("SPRSCROF_0 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRDCROF.SPRDCROF1.bit.SPRDCROF_0));
		Ddim_Print(("SPRSCROF_1 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRDCROF.SPRDCROF1.bit.SPRDCROF_1));
		Ddim_Print(("SPRSCROF_2 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRDCROF.SPRDCROF1.bit.SPRDCROF_2));
		Ddim_Print(("SPRSCROF_3 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRDCROF.SPRDCROF1.bit.SPRDCROF_3));
		Ddim_Print(("SPRSCROF_4 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRDCROF.SPRDCROF2.bit.SPRDCROF_4));
		Ddim_Print(("SPRSCROF_5 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRDCROF.SPRDCROF2.bit.SPRDCROF_5));

		Ddim_Print(("SPRSCRGA_0 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRDCRGA.SPRDCRGA1.bit.SPRDCRGA_0));
		Ddim_Print(("SPRSCRGA_1 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRDCRGA.SPRDCRGA1.bit.SPRDCRGA_1));
		Ddim_Print(("SPRSCRGA_2 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRDCRGA.SPRDCRGA2.bit.SPRDCRGA_2));
		Ddim_Print(("SPRSCRGA_3 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRDCRGA.SPRDCRGA2.bit.SPRDCRGA_3));
		Ddim_Print(("SPRSCRGA_4 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRDCRGA.SPRDCRGA3.bit.SPRDCRGA_4));
		Ddim_Print(("SPRSCRGA_5 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.SPRDCRGA.SPRDCRGA3.bit.SPRDCRGA_5));
	}

	Im_CNR_Off_Pclk(ch);
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_3_18: "
INT32 ct_im_cnr_otf_3_18(CtImCnr9 *self)
{
	UCHAR ch = self->ch9;
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
		imErcd = Im_CNR_OTF_Set_CSPR_Low_CC_C_Table(ch, &sprTbl[loopcnt]);
		if(imErcd != D_DDIM_OK) {
			Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl error = 0x%x\n", imErcd));
			return imErcd;
		}
		ctImCnrOtfPrintDebugCLowCcCTbl(ch);
	}

	imErcd = Im_CNR_OTF_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_3_19: "
INT32 ct_im_cnr_otf_3_19(CtImCnr9 *self)
{
	UCHAR ch = self->ch9;
	INT32 imErcd;
	T_IM_CNR_OTF_CTRL sprCtrl = {
		.mode = E_IM_CNR_OTF_YCC_MODE_YCC422_SIMPLE,

		.width = CtImCnr_D_IM_CNR_TEST_H_PIXS,
		.lines = CtImCnr_D_IM_CNR_TEST_V_PIXS,

		.w_c_width = CtImCnr_D_IM_CNR_TEST_H_PIXS,

		.divide_left = E_IM_CNR_VPROCESS_NORM,
		.divide_right = E_IM_CNR_VPROCESS_NORM,

		.w_offset_x = 1000,

		.continuous = E_IM_CNR_ONOFF_ENABLE,

		.pCallBack = NULL,
		.user_param = 0,
	};
	T_IM_CNR_OTF_OUTADDR_INFO addrInfo = {
		.use_bank_num = 1,
		.w_c_addr[0] = CtImCnr_D_IM_CNR_TEST_IMG_DST_CB_ADDR,
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


	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_OTF_Open(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Open error = 0x%x\n", imErcd));
		return imErcd;
	}

	Im_CNR_OTF_Init(ch);

	imErcd = Im_CNR_OTF_Ctrl(ch, &sprCtrl);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OTF_Set_OutAddr_Info(ch, &addrInfo);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Set OutAddrInfo error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OTF_Ctrl_C(ch, &sprCtrlC);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl_C error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OTF_Start_Sync(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Start Sync error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OTF_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_3_23: "
INT32 ct_im_cnr_otf_3_23(CtImCnr9 *self)
{
	UCHAR ch = self->ch9;
	INT32 imErcd;
	UINT32 loopcnt;
	T_IM_CNR_CTRL_CC_SRC_DST sprCtrl[3] = {
		[0] = {	//max
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
		},
		[1] = {	//min
			.enable = (E_IM_CNR_ONOFF)0,
			.cb_table = {
				.bd1 = -0x80,
				.bd2 = -0x80,
				.bd3 = -0x80,
				.bd4 = -0x80,
				.bd5 = -0x80,
				.of0 = -0x80,
				.of1 = -0x80,
				.of2 = -0x80,
				.of3 = -0x80,
				.of4 = -0x80,
				.of5 = -0x80,
				.gain0 = -0x0800,
				.gain1 = -0x0800,
				.gain2 = -0x0800,
				.gain3 = -0x0800,
				.gain4 = -0x0800,
				.gain5 = -0x0800
			},
			.cr_table = {
				.bd1 = -0x80,
				.bd2 = -0x80,
				.bd3 = -0x80,
				.bd4 = -0x80,
				.bd5 = -0x80,
				.of0 = -0x80,
				.of1 = -0x80,
				.of2 = -0x80,
				.of3 = -0x80,
				.of4 = -0x80,
				.of5 = -0x80,
				.gain0 = -0x0800,
				.gain1 = -0x0800,
				.gain2 = -0x0800,
				.gain3 = -0x0800,
				.gain4 = -0x0800,
				.gain5 = -0x0800
			}
		},
		[2] = {	//countup
			.enable = (E_IM_CNR_ONOFF)1,
			.cb_table = {
				.bd1 = 0x01,
				.bd2 = 0x02,
				.bd3 = 0x03,
				.bd4 = 0x04,
				.bd5 = 0x05,
				.of0 = 0x06,
				.of1 = 0x07,
				.of2 = 0x08,
				.of3 = 0x09,
				.of4 = 0x0A,
				.of5 = 0x0B,
				.gain0 = 0x000C,
				.gain1 = 0x000D,
				.gain2 = 0x000E,
				.gain3 = 0x000F,
				.gain4 = 0x0010,
				.gain5 = 0x0011
			},
			.cr_table = {
				.bd1 = 0x01,
				.bd2 = 0x02,
				.bd3 = 0x03,
				.bd4 = 0x04,
				.bd5 = 0x05,
				.of0 = 0x06,
				.of1 = 0x07,
				.of2 = 0x08,
				.of3 = 0x09,
				.of4 = 0x0A,
				.of5 = 0x0B,
				.gain0 = 0x000C,
				.gain1 = 0x000D,
				.gain2 = 0x000E,
				.gain3 = 0x000F,
				.gain4 = 0x0010,
				.gain5 = 0x0011
			}
		},
	};

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_OTF_Open(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Open error = 0x%x\n", imErcd));
		return imErcd;
	}

	for(loopcnt = 0; loopcnt < (sizeof(sprCtrl) / sizeof(sprCtrl[0])); loopcnt++) {
		Ddim_Print(("** %u\n", loopcnt));
		imErcd = Im_CNR_OTF_Ctrl_SPRS_CC(ch, &sprCtrl[loopcnt]);
		if(imErcd != D_DDIM_OK) {
			Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl error = 0x%x\n", imErcd));
			return imErcd;
		}
		ctImCnrOtfPrintDebugCtrlSrcCc(ch);
	}

	imErcd = Im_CNR_OTF_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_3_24: "
INT32 ct_im_cnr_otf_3_24(CtImCnr9 *self)
{
	UCHAR ch = self->ch9;
	INT32 imErcd;
	UINT32 loopcnt;
	T_IM_CNR_CTRL_CC_SRC_DST sprCtrl[3] = {
		[0] = {	//max
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
		},
		[1] = {	//min
			.enable = (E_IM_CNR_ONOFF)0,
			.cb_table = {
				.bd1 = -0x80,
				.bd2 = -0x80,
				.bd3 = -0x80,
				.bd4 = -0x80,
				.bd5 = -0x80,
				.of0 = -0x80,
				.of1 = -0x80,
				.of2 = -0x80,
				.of3 = -0x80,
				.of4 = -0x80,
				.of5 = -0x80,
				.gain0 = -0x0800,
				.gain1 = -0x0800,
				.gain2 = -0x0800,
				.gain3 = -0x0800,
				.gain4 = -0x0800,
				.gain5 = -0x0800
			},
			.cr_table = {
				.bd1 = -0x80,
				.bd2 = -0x80,
				.bd3 = -0x80,
				.bd4 = -0x80,
				.bd5 = -0x80,
				.of0 = -0x80,
				.of1 = -0x80,
				.of2 = -0x80,
				.of3 = -0x80,
				.of4 = -0x80,
				.of5 = -0x80,
				.gain0 = -0x0800,
				.gain1 = -0x0800,
				.gain2 = -0x0800,
				.gain3 = -0x0800,
				.gain4 = -0x0800,
				.gain5 = -0x0800
			}
		},
		[2] = {	//countup
			.enable = (E_IM_CNR_ONOFF)1,
			.cb_table = {
				.bd1 = 0x01,
				.bd2 = 0x02,
				.bd3 = 0x03,
				.bd4 = 0x04,
				.bd5 = 0x05,
				.of0 = 0x06,
				.of1 = 0x07,
				.of2 = 0x08,
				.of3 = 0x09,
				.of4 = 0x0A,
				.of5 = 0x0B,
				.gain0 = 0x000C,
				.gain1 = 0x000D,
				.gain2 = 0x000E,
				.gain3 = 0x000F,
				.gain4 = 0x0010,
				.gain5 = 0x0011
			},
			.cr_table = {
				.bd1 = 0x01,
				.bd2 = 0x02,
				.bd3 = 0x03,
				.bd4 = 0x04,
				.bd5 = 0x05,
				.of0 = 0x06,
				.of1 = 0x07,
				.of2 = 0x08,
				.of3 = 0x09,
				.of4 = 0x0A,
				.of5 = 0x0B,
				.gain0 = 0x000C,
				.gain1 = 0x000D,
				.gain2 = 0x000E,
				.gain3 = 0x000F,
				.gain4 = 0x0010,
				.gain5 = 0x0011
			}
		},
	};

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_OTF_Open(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Open error = 0x%x\n", imErcd));
		return imErcd;
	}

	for(loopcnt = 0; loopcnt < (sizeof(sprCtrl) / sizeof(sprCtrl[0])); loopcnt++) {
		Ddim_Print(("** %u\n", loopcnt));
		imErcd = Im_CNR_OTF_Ctrl_SPRD_CC(ch, &sprCtrl[loopcnt]);
		if(imErcd != D_DDIM_OK) {
			Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl error = 0x%x\n", imErcd));
			return imErcd;
		}
		ctImCnrOtfPrintDebugCtrlDstCc(ch);
	}

	imErcd = Im_CNR_OTF_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_6_20: "
INT32 ct_im_cnr_6_20(CtImCnr9 *self)
{
	UCHAR ch = self->ch9;
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
	const  T_IM_CNR_RDMA_ADDR_CSPR_LOW_CC_C_TBL*	C_LOW_CC_TBL_ADDR;
	ULONG	size;

	ret = Im_CNR_Get_RdmaAddr_OTF_CSPR_Low_CC_C_Table(ch, &C_LOW_CC_TBL_ADDR, &size);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OTF_CSPR_Low_CC_C_Table error = 0x%x\n", ret));
		return ret;
	}

	ret = Im_CNR_Set_RdmaValue_OTF_CSPR_Low_CC_C_Table(&cnrTable, &rdmaLowCcCTbl);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OTF_CSPR_Low_CC_C_Table error = 0x%x\n", ret));
		return ret;
	}

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)C_LOW_CC_TBL_ADDR;
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
		ctImCnrOtfPrintDebugCLowCcCTbl(0);
		ctImCnrOtfPrintDebugCLowCcCTbl(1);
	}
	else{
		ctImCnrOtfPrintDebugCLowCcCTbl(ch);
	}

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_6_23: "
INT32 ct_im_cnr_6_23(CtImCnr9 *self)
{
	UCHAR ch = self->ch9;
	INT32 ret;
	T_IM_RDMA_CTRL rdmaCtrl;
	T_IM_CNR_CTRL_CC_SRC_DST	csprSprsCc = {
		.enable = (E_IM_CNR_ONOFF)1,
		.cb_table = {
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
			.gain0 = 0x07FF,
			.gain1 = 0x07FF,
			.gain2 = 0x07FF,
			.gain3 = 0x07FF,
			.gain4 = 0x07FF,
			.gain5 = 0x07FF
		},
		.cr_table = {
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
			.gain0 = 0x07FF,
			.gain1 = 0x07FF,
			.gain2 = 0x07FF,
			.gain3 = 0x07FF,
			.gain4 = 0x07FF,
			.gain5 = 0x07FF
		}
	};
	T_IM_CNR_RDMA_DATA_SPRS_CC_TBL	rdmaSprsTbl;
	const  T_IM_CNR_RDMA_ADDR_SPRS_CC_TBL*	C_SPRS_TBL_ADDR;
	ULONG	size;

	ret = Im_CNR_Get_RdmaAddr_OTF_CSPR_SPRS_CC_Table(ch, &C_SPRS_TBL_ADDR, &size);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OTF_CSPR_SPRS_CC_Table error = 0x%x\n", ret));
		return ret;
	}

	ret = Im_CNR_Set_RdmaValue_OTF_CSPR_SPRS_CC_Table(&csprSprsCc, &rdmaSprsTbl);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OTF_CSPR_SPRS_CC_Table error = 0x%x\n", ret));
		return ret;
	}

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)C_SPRS_TBL_ADDR;
	rdmaCtrl.reg_data_top_addr	= (ULONG)&rdmaSprsTbl;
	rdmaCtrl.req_threshold		= E_IM_RDMA_PRCH_CNT_NOLIMIT;
	rdmaCtrl.int_mode			= E_IM_RDMA_INT_MODE_AND_ERR;
	rdmaCtrl.pCallBack			= NULL;
	ret = Im_RDMA_Ctrl_Quick_Start_Sync(D_DDIM_WAIT_END_TIME, &rdmaCtrl);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Ctrl error = 0x%x\n", ret));
		return ret;
	}

	if(ch == D_IM_CNR_CH_2){
		ctImCnrOtfPrintDebugCtrlSrcCc(0);
		ctImCnrOtfPrintDebugCtrlSrcCc(1);
	}
	else{
		ctImCnrOtfPrintDebugCtrlSrcCc(ch);
	}

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_6_24: "
INT32 ct_im_cnr_6_24(CtImCnr9 *self)
{
	UCHAR ch = self->ch9;
	INT32 ret;
	T_IM_RDMA_CTRL rdmaCtrl;
	T_IM_CNR_CTRL_CC_SRC_DST	csprSprdCc = {
		.enable = (E_IM_CNR_ONOFF)1,
		.cb_table = {
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
			.gain0 = 0x07FF,
			.gain1 = 0x07FF,
			.gain2 = 0x07FF,
			.gain3 = 0x07FF,
			.gain4 = 0x07FF,
			.gain5 = 0x07FF
		},
		.cr_table = {
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
			.gain0 = 0x07FF,
			.gain1 = 0x07FF,
			.gain2 = 0x07FF,
			.gain3 = 0x07FF,
			.gain4 = 0x07FF,
			.gain5 = 0x07FF
		}
	};
	T_IM_CNR_RDMA_DATA_SPRD_CC_TBL	rdmaSprdTbl;
	const  T_IM_CNR_RDMA_ADDR_SPRD_CC_TBL*	C_SPRD_TBL_ADDR;
	ULONG	size;

	ret = Im_CNR_Get_RdmaAddr_OTF_CSPR_SPRD_CC_Table(ch, &C_SPRD_TBL_ADDR, &size);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OTF_CSPR_SPRD_CC_Table error = 0x%x\n", ret));
		return ret;
	}

	ret = Im_CNR_Set_RdmaValue_OTF_CSPR_SPRD_CC_Table(&csprSprdCc, &rdmaSprdTbl);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OTF_CSPR_SPRD_CC_Table error = 0x%x\n", ret));
		return ret;
	}

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)C_SPRD_TBL_ADDR;
	rdmaCtrl.reg_data_top_addr	= (ULONG)&rdmaSprdTbl;
	rdmaCtrl.req_threshold		= E_IM_RDMA_PRCH_CNT_NOLIMIT;
	rdmaCtrl.int_mode			= E_IM_RDMA_INT_MODE_AND_ERR;
	rdmaCtrl.pCallBack			= NULL;
	ret = Im_RDMA_Ctrl_Quick_Start_Sync(D_DDIM_WAIT_END_TIME, &rdmaCtrl);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Ctrl error = 0x%x\n", ret));
		return ret;
	}

	if(ch == D_IM_CNR_CH_2){
		ctImCnrOtfPrintDebugCtrlDstCc(0);
		ctImCnrOtfPrintDebugCtrlDstCc(1);
	}
	else{
		ctImCnrOtfPrintDebugCtrlDstCc(ch);
	}

	return D_DDIM_OK;
}

CtImCnr9* ct_im_cnr9_new(void) 
{
    CtImCnr9 *self = g_object_new(CT_TYPE_IM_CNR9, NULL);
    return self;
}
