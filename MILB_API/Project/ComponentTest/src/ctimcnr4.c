/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :王印斌
*@brief               :CtImCnr4类
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
#include "ctimcnr4.h"

#include <string.h>
#include <stdlib.h>

G_DEFINE_TYPE(CtImCnr4, ct_im_cnr4, G_TYPE_OBJECT); 
#define CT_IM_CNR4_GET_PRIVATE(o) (G_OBJECT_GET_PRIVATE ((o), CT_TYPE_IM_CNR4, CtImCnr4Private))

struct _CtImCnr4Private
{

};

static void ctImCnrOflPrintDebugYTbl(UCHAR ch);
static void ctImCnrOflPrintDebugCtrlSrcCc(UCHAR ch);
static void ctImCnrOflPrintDebugCtrlDstCc(UCHAR ch);

static void ct_im_cnr4_constructor(CtImCnr4 *self) 
{
//	CtImCnr4Private *priv = CT_IM_CNR4_GET_PRIVATE(self);
}

static void ct_im_cnr4_destructor(CtImCnr4 *self) 
{
//	CtImCnr4Private *priv = CT_IM_CNR4_GET_PRIVATE(self);
}

static void ctImCnrOflPrintDebugYTbl(UCHAR ch)
{
	UCHAR loop, loopSta, loopEnd;

	Im_CNR_On_Pclk(ch);

	ct_im_cnr_get_loop_cnt(ch, &loopSta, &loopEnd);

	for(loop = loopSta; loop <= loopEnd; loop++){
		Ddim_Print(("ch[%d]\n",           loop));
		Ddim_Print(("YSPRDYEYBD_1 = 0x%x\n", io_cnr(loop)->OFL_REG_YSPR.YSPRDYEYBD.YSPRDYEYBD1.bit.YSPRDYEYBD_1));
		Ddim_Print(("YSPRDYEYBD_2 = 0x%x\n", io_cnr(loop)->OFL_REG_YSPR.YSPRDYEYBD.YSPRDYEYBD1.bit.YSPRDYEYBD_2));
		Ddim_Print(("YSPRDYEYBD_3 = 0x%x\n", io_cnr(loop)->OFL_REG_YSPR.YSPRDYEYBD.YSPRDYEYBD1.bit.YSPRDYEYBD_3));
		Ddim_Print(("YSPRDYEYBD_4 = 0x%x\n", io_cnr(loop)->OFL_REG_YSPR.YSPRDYEYBD.YSPRDYEYBD1.bit.YSPRDYEYBD_4));
		Ddim_Print(("YSPRDYEYBD_5 = 0x%x\n", io_cnr(loop)->OFL_REG_YSPR.YSPRDYEYBD.YSPRDYEYBD2.bit.YSPRDYEYBD_5));

		Ddim_Print(("YSPRDYEYOF_0 = 0x%x\n", io_cnr(loop)->OFL_REG_YSPR.YSPRDYEYOF.YSPRDYEYOF1.bit.YSPRDYEYOF_0));
		Ddim_Print(("YSPRDYEYOF_1 = 0x%x\n", io_cnr(loop)->OFL_REG_YSPR.YSPRDYEYOF.YSPRDYEYOF1.bit.YSPRDYEYOF_1));
		Ddim_Print(("YSPRDYEYOF_2 = 0x%x\n", io_cnr(loop)->OFL_REG_YSPR.YSPRDYEYOF.YSPRDYEYOF1.bit.YSPRDYEYOF_2));
		Ddim_Print(("YSPRDYEYOF_3 = 0x%x\n", io_cnr(loop)->OFL_REG_YSPR.YSPRDYEYOF.YSPRDYEYOF1.bit.YSPRDYEYOF_3));
		Ddim_Print(("YSPRDYEYOF_4 = 0x%x\n", io_cnr(loop)->OFL_REG_YSPR.YSPRDYEYOF.YSPRDYEYOF2.bit.YSPRDYEYOF_4));
		Ddim_Print(("YSPRDYEYOF_5 = 0x%x\n", io_cnr(loop)->OFL_REG_YSPR.YSPRDYEYOF.YSPRDYEYOF2.bit.YSPRDYEYOF_5));

		Ddim_Print(("YSPRDYEYGA_0 = 0x%x\n", io_cnr(loop)->OFL_REG_YSPR.YSPRDYEYGA.YSPRDYEYGA1.bit.YSPRDYEYGA_0));
		Ddim_Print(("YSPRDYEYGA_1 = 0x%x\n", io_cnr(loop)->OFL_REG_YSPR.YSPRDYEYGA.YSPRDYEYGA1.bit.YSPRDYEYGA_1));
		Ddim_Print(("YSPRDYEYGA_2 = 0x%x\n", io_cnr(loop)->OFL_REG_YSPR.YSPRDYEYGA.YSPRDYEYGA1.bit.YSPRDYEYGA_2));
		Ddim_Print(("YSPRDYEYGA_3 = 0x%x\n", io_cnr(loop)->OFL_REG_YSPR.YSPRDYEYGA.YSPRDYEYGA1.bit.YSPRDYEYGA_3));
		Ddim_Print(("YSPRDYEYGA_4 = 0x%x\n", io_cnr(loop)->OFL_REG_YSPR.YSPRDYEYGA.YSPRDYEYGA2.bit.YSPRDYEYGA_4));
		Ddim_Print(("YSPRDYEYGA_5 = 0x%x\n", io_cnr(loop)->OFL_REG_YSPR.YSPRDYEYGA.YSPRDYEYGA2.bit.YSPRDYEYGA_5));
	}

	Im_CNR_Off_Pclk(ch);
}

static void ctImCnrOflPrintDebugCtrlSrcCc(UCHAR ch)
{
	UCHAR loop, loopSta, loopEnd;

	Im_CNR_On_Pclk(ch);

	ct_im_cnr_get_loop_cnt(ch, &loopSta, &loopEnd);

	for(loop = loopSta; loop <= loopEnd; loop++){
		Ddim_Print(("ch[%d]\n",           loop));
		Ddim_Print(("SPRS       = %u\n",   io_cnr(loop)->OFL_CSPR_REG.SPRS.bit.SPRS));

		// CB
		Ddim_Print(("SPRSCBBD_1 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRSCBBD.SPRSCBBD1.bit.SPRSCBBD_1));
		Ddim_Print(("SPRSCBBD_2 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRSCBBD.SPRSCBBD1.bit.SPRSCBBD_2));
		Ddim_Print(("SPRSCBBD_3 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRSCBBD.SPRSCBBD1.bit.SPRSCBBD_3));
		Ddim_Print(("SPRSCBBD_4 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRSCBBD.SPRSCBBD1.bit.SPRSCBBD_4));
		Ddim_Print(("SPRSCBBD_5 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRSCBBD.SPRSCBBD2.bit.SPRSCBBD_5));

		Ddim_Print(("SPRSCBOF_0 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRSCBOF.SPRSCBOF1.bit.SPRSCBOF_0));
		Ddim_Print(("SPRSCBOF_1 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRSCBOF.SPRSCBOF1.bit.SPRSCBOF_1));
		Ddim_Print(("SPRSCBOF_2 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRSCBOF.SPRSCBOF1.bit.SPRSCBOF_2));
		Ddim_Print(("SPRSCBOF_3 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRSCBOF.SPRSCBOF1.bit.SPRSCBOF_3));
		Ddim_Print(("SPRSCBOF_4 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRSCBOF.SPRSCBOF2.bit.SPRSCBOF_4));
		Ddim_Print(("SPRSCBOF_5 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRSCBOF.SPRSCBOF2.bit.SPRSCBOF_5));

		Ddim_Print(("SPRSCBGA_0 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRSCBGA.SPRSCBGA1.bit.SPRSCBGA_0));
		Ddim_Print(("SPRSCBGA_1 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRSCBGA.SPRSCBGA1.bit.SPRSCBGA_1));
		Ddim_Print(("SPRSCBGA_2 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRSCBGA.SPRSCBGA2.bit.SPRSCBGA_2));
		Ddim_Print(("SPRSCBGA_3 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRSCBGA.SPRSCBGA2.bit.SPRSCBGA_3));
		Ddim_Print(("SPRSCBGA_4 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRSCBGA.SPRSCBGA3.bit.SPRSCBGA_4));
		Ddim_Print(("SPRSCBGA_5 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRSCBGA.SPRSCBGA3.bit.SPRSCBGA_5));

		// CR
		Ddim_Print(("SPRSCRBD_1 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRSCRBD.SPRSCRBD1.bit.SPRSCRBD_1));
		Ddim_Print(("SPRSCRBD_2 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRSCRBD.SPRSCRBD1.bit.SPRSCRBD_2));
		Ddim_Print(("SPRSCRBD_3 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRSCRBD.SPRSCRBD1.bit.SPRSCRBD_3));
		Ddim_Print(("SPRSCRBD_4 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRSCRBD.SPRSCRBD1.bit.SPRSCRBD_4));
		Ddim_Print(("SPRSCRBD_5 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRSCRBD.SPRSCRBD2.bit.SPRSCRBD_5));

		Ddim_Print(("SPRSCROF_0 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRSCROF.SPRSCROF1.bit.SPRSCROF_0));
		Ddim_Print(("SPRSCROF_1 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRSCROF.SPRSCROF1.bit.SPRSCROF_1));
		Ddim_Print(("SPRSCROF_2 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRSCROF.SPRSCROF1.bit.SPRSCROF_2));
		Ddim_Print(("SPRSCROF_3 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRSCROF.SPRSCROF1.bit.SPRSCROF_3));
		Ddim_Print(("SPRSCROF_4 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRSCROF.SPRSCROF2.bit.SPRSCROF_4));
		Ddim_Print(("SPRSCROF_5 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRSCROF.SPRSCROF2.bit.SPRSCROF_5));

		Ddim_Print(("SPRSCRGA_0 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRSCRGA.SPRSCRGA1.bit.SPRSCRGA_0));
		Ddim_Print(("SPRSCRGA_1 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRSCRGA.SPRSCRGA1.bit.SPRSCRGA_1));
		Ddim_Print(("SPRSCRGA_2 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRSCRGA.SPRSCRGA2.bit.SPRSCRGA_2));
		Ddim_Print(("SPRSCRGA_3 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRSCRGA.SPRSCRGA2.bit.SPRSCRGA_3));
		Ddim_Print(("SPRSCRGA_4 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRSCRGA.SPRSCRGA3.bit.SPRSCRGA_4));
		Ddim_Print(("SPRSCRGA_5 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRSCRGA.SPRSCRGA3.bit.SPRSCRGA_5));
	}

	Im_CNR_Off_Pclk(ch);
}

static void ctImCnrOflPrintDebugCtrlDstCc(UCHAR ch)
{
	UCHAR loop, loopSta, loopEnd;

	Im_CNR_On_Pclk(ch);

	ct_im_cnr_get_loop_cnt(ch, &loopSta, &loopEnd);

	for(loop = loopSta; loop <= loopEnd; loop++){
		Ddim_Print(("ch[%d]\n",           loop));
		Ddim_Print(("SPRD       = %u\n",   io_cnr(loop)->OFL_CSPR_REG.SPRD.bit.SPRD));

		// CB
		Ddim_Print(("SPRSCBBD_1 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRDCBBD.SPRDCBBD1.bit.SPRDCBBD_1));
		Ddim_Print(("SPRSCBBD_2 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRDCBBD.SPRDCBBD1.bit.SPRDCBBD_2));
		Ddim_Print(("SPRSCBBD_3 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRDCBBD.SPRDCBBD1.bit.SPRDCBBD_3));
		Ddim_Print(("SPRSCBBD_4 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRDCBBD.SPRDCBBD1.bit.SPRDCBBD_4));
		Ddim_Print(("SPRSCBBD_5 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRDCBBD.SPRDCBBD2.bit.SPRDCBBD_5));

		Ddim_Print(("SPRSCBOF_0 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRDCBOF.SPRDCBOF1.bit.SPRDCBOF_0));
		Ddim_Print(("SPRSCBOF_1 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRDCBOF.SPRDCBOF1.bit.SPRDCBOF_1));
		Ddim_Print(("SPRSCBOF_2 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRDCBOF.SPRDCBOF1.bit.SPRDCBOF_2));
		Ddim_Print(("SPRSCBOF_3 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRDCBOF.SPRDCBOF1.bit.SPRDCBOF_3));
		Ddim_Print(("SPRSCBOF_4 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRDCBOF.SPRDCBOF2.bit.SPRDCBOF_4));
		Ddim_Print(("SPRSCBOF_5 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRDCBOF.SPRDCBOF2.bit.SPRDCBOF_5));

		Ddim_Print(("SPRSCBGA_0 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRDCBGA.SPRDCBGA1.bit.SPRDCBGA_0));
		Ddim_Print(("SPRSCBGA_1 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRDCBGA.SPRDCBGA1.bit.SPRDCBGA_1));
		Ddim_Print(("SPRSCBGA_2 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRDCBGA.SPRDCBGA2.bit.SPRDCBGA_2));
		Ddim_Print(("SPRSCBGA_3 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRDCBGA.SPRDCBGA2.bit.SPRDCBGA_3));
		Ddim_Print(("SPRSCBGA_4 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRDCBGA.SPRDCBGA3.bit.SPRDCBGA_4));
		Ddim_Print(("SPRSCBGA_5 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRDCBGA.SPRDCBGA3.bit.SPRDCBGA_5));

		// CR
		Ddim_Print(("SPRSCRBD_1 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRDCRBD.SPRDCRBD1.bit.SPRDCRBD_1));
		Ddim_Print(("SPRSCRBD_2 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRDCRBD.SPRDCRBD1.bit.SPRDCRBD_2));
		Ddim_Print(("SPRSCRBD_3 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRDCRBD.SPRDCRBD1.bit.SPRDCRBD_3));
		Ddim_Print(("SPRSCRBD_4 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRDCRBD.SPRDCRBD1.bit.SPRDCRBD_4));
		Ddim_Print(("SPRSCRBD_5 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRDCRBD.SPRDCRBD2.bit.SPRDCRBD_5));

		Ddim_Print(("SPRSCROF_0 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRDCROF.SPRDCROF1.bit.SPRDCROF_0));
		Ddim_Print(("SPRSCROF_1 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRDCROF.SPRDCROF1.bit.SPRDCROF_1));
		Ddim_Print(("SPRSCROF_2 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRDCROF.SPRDCROF1.bit.SPRDCROF_2));
		Ddim_Print(("SPRSCROF_3 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRDCROF.SPRDCROF1.bit.SPRDCROF_3));
		Ddim_Print(("SPRSCROF_4 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRDCROF.SPRDCROF2.bit.SPRDCROF_4));
		Ddim_Print(("SPRSCROF_5 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRDCROF.SPRDCROF2.bit.SPRDCROF_5));

		Ddim_Print(("SPRSCRGA_0 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRDCRGA.SPRDCRGA1.bit.SPRDCRGA_0));
		Ddim_Print(("SPRSCRGA_1 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRDCRGA.SPRDCRGA1.bit.SPRDCRGA_1));
		Ddim_Print(("SPRSCRGA_2 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRDCRGA.SPRDCRGA2.bit.SPRDCRGA_2));
		Ddim_Print(("SPRSCRGA_3 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRDCRGA.SPRDCRGA2.bit.SPRDCRGA_3));
		Ddim_Print(("SPRSCRGA_4 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRDCRGA.SPRDCRGA3.bit.SPRDCRGA_4));
		Ddim_Print(("SPRSCRGA_5 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.SPRDCRGA.SPRDCRGA3.bit.SPRDCRGA_5));
	}

	Im_CNR_Off_Pclk(ch);
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_20: "
INT32 ct_im_cnr_ofl_1_20(CtImCnr4 *self)
{
	UCHAR ch = self->ch4;
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
		imErcd = Im_CNR_OFL_Set_YSPR_Table(ch, &sprTbl[loopcnt]);
		if(imErcd != D_DDIM_OK) {
			Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl error = 0x%x\n", imErcd));
			return imErcd;
		}
		ctImCnrOflPrintDebugYTbl(ch);
	}

	imErcd = Im_CNR_OFL_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_25: "
INT32 ct_im_cnr_ofl_1_25(CtImCnr4 *self)
{
	UCHAR ch = self->ch4;
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

	imErcd = Im_CNR_OFL_Open(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Open error = 0x%x\n", imErcd));
		return imErcd;
	}

	for(loopcnt = 0; loopcnt < (sizeof(sprCtrl) / sizeof(sprCtrl[0])); loopcnt++) {
		Ddim_Print(("** %u\n", loopcnt));
		imErcd = Im_CNR_OFL_Ctrl_SPRS_CC(ch, &sprCtrl[loopcnt]);
		if(imErcd != D_DDIM_OK) {
			Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl error = 0x%x\n", imErcd));
			return imErcd;
		}
		ctImCnrOflPrintDebugCtrlSrcCc(ch);
	}

	imErcd = Im_CNR_OFL_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_26: "
INT32 ct_im_cnr_ofl_1_26(CtImCnr4 *self)
{
	UCHAR ch = self->ch4;
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

	imErcd = Im_CNR_OFL_Open(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Open error = 0x%x\n", imErcd));
		return imErcd;
	}

	for(loopcnt = 0; loopcnt < (sizeof(sprCtrl) / sizeof(sprCtrl[0])); loopcnt++) {
		Ddim_Print(("** %u\n", loopcnt));
		imErcd = Im_CNR_OFL_Ctrl_SPRD_CC(ch, &sprCtrl[loopcnt]);
		if(imErcd != D_DDIM_OK) {
			Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl error = 0x%x\n", imErcd));
			return imErcd;
		}
		ctImCnrOflPrintDebugCtrlDstCc(ch);
	}

	imErcd = Im_CNR_OFL_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_35: "
INT32 ct_im_cnr_ofl_1_35(CtImCnr4 *self)
{
	// UCHAR ch = self->ch4;
	INT32 imErcd;
	T_IM_CNR_TABLE ysprTable = {
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
	T_IM_CNR_RDMA_DATA_OFL_YSPR_TBL rdma_yspr_table;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_Set_RdmaValue_OFL_YSPR_Table(&ysprTable, &rdma_yspr_table);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Im_CNR_Set_RdmaValue_OFL_YSPR_Table() error = 0x%x\n", imErcd));
		return imErcd;
	}

	// Check parameter
	Ddim_Print(("rdma_yspr_table.YSPRDYEYOF.YSPRDYEYOF1 = 0x%lx\n", rdma_yspr_table.YSPRDYEYOF.YSPRDYEYOF1.word));
	Ddim_Print(("rdma_yspr_table.YSPRDYEYOF.YSPRDYEYOF2 = 0x%lx\n", rdma_yspr_table.YSPRDYEYOF.YSPRDYEYOF2.word));
	Ddim_Print(("rdma_yspr_table.YSPRDYEYGA.YSPRDYEYGA1 = 0x%lx\n", rdma_yspr_table.YSPRDYEYGA.YSPRDYEYGA1.word));
	Ddim_Print(("rdma_yspr_table.YSPRDYEYGA.YSPRDYEYGA2 = 0x%lx\n", rdma_yspr_table.YSPRDYEYGA.YSPRDYEYGA2.word));
	Ddim_Print(("rdma_yspr_table.YSPRDYEYBD.YSPRDYEYBD1 = 0x%lx\n", rdma_yspr_table.YSPRDYEYBD.YSPRDYEYBD1.word));
	Ddim_Print(("rdma_yspr_table.YSPRDYEYBD.YSPRDYEYBD2 = 0x%lx\n", rdma_yspr_table.YSPRDYEYBD.YSPRDYEYBD2.word));

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_36: "
INT32 ct_im_cnr_ofl_1_36(CtImCnr4 *self)
{
	UCHAR ch = self->ch4;
	INT32 imErcd;
	const T_IM_CNR_RDMA_ADDR_CSPR_MID_Y_TBL* C_CSPR_MID_Y_TBL;
	ULONG size;
	ULONG* ptAddr;
	UINT32 loopcnt;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_Get_RdmaAddr_OFL_CSPR_Mid_Y_Table(ch, &C_CSPR_MID_Y_TBL, &size);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Im_CNR_Get_RdmaAddr_OFL_CSPR_Mid_Y_Table() error = 0x%x\n", imErcd));
		return imErcd;
	}

	// Check parameter
	Ddim_Print(("size = 0x%lx\n", size));
	ptAddr = (ULONG*)C_CSPR_MID_Y_TBL;
	for(loopcnt = 0; loopcnt < size; loopcnt+=4) {
		Ddim_Print(("address = 0x%lx\n", *ptAddr));
		ptAddr++;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_6_3: "
INT32 ct_im_cnr_6_3(CtImCnr4 *self)
{
	UCHAR ch = self->ch4;
	INT32 ret;
	T_IM_RDMA_CTRL rdmaCtrl;
	T_IM_CNR_TABLE	ysprTable = {
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
	T_IM_CNR_RDMA_DATA_OFL_YSPR_TBL	rdmaYsprTbl;
	const  T_IM_CNR_RDMA_ADDR_OFL_YSPR_TBL*	C_YSPR_TBL_ADDR;
	ULONG	size;

	ret = Im_CNR_Get_RdmaAddr_OFL_YSPR_Table(ch, &C_YSPR_TBL_ADDR, &size);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OFL_YSPR_Table error = 0x%x\n", ret));
		return ret;
	}

	ret = Im_CNR_Set_RdmaValue_OFL_YSPR_Table(&ysprTable, &rdmaYsprTbl);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OFL_YSPR_Table error = 0x%x\n", ret));
		return ret;
	}

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)C_YSPR_TBL_ADDR;
	rdmaCtrl.reg_data_top_addr	= (ULONG)&rdmaYsprTbl;
	rdmaCtrl.req_threshold		= E_IM_RDMA_PRCH_CNT_NOLIMIT;
	rdmaCtrl.int_mode			= E_IM_RDMA_INT_MODE_AND_ERR;
	rdmaCtrl.pCallBack			= NULL;
	ret = Im_RDMA_Ctrl_Quick_Start_Sync(D_DDIM_WAIT_END_TIME, &rdmaCtrl);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Ctrl error = 0x%x\n", ret));
		return ret;
	}

	if(ch == D_IM_CNR_CH_2){
		ctImCnrOflPrintDebugYTbl(0);
		ctImCnrOflPrintDebugYTbl(1);
	}
	else{
		ctImCnrOflPrintDebugYTbl(ch);
	}

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_6_12: "
INT32 ct_im_cnr_6_12(CtImCnr4 *self)
{
	UCHAR ch = self->ch4;
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

	ret = Im_CNR_Get_RdmaAddr_OFL_CSPR_SPRS_CC_Table(ch, &C_SPRS_TBL_ADDR, &size);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OFL_CSPR_SPRS_CC_Table error = 0x%x\n", ret));
		return ret;
	}

	ret = Im_CNR_Set_RdmaValue_OFL_CSPR_SPRS_CC_Table(&csprSprsCc, &rdmaSprsTbl);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OFL_CSPR_SPRS_CC_Table error = 0x%x\n", ret));
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
		ctImCnrOflPrintDebugCtrlSrcCc(0);
		ctImCnrOflPrintDebugCtrlSrcCc(1);
	}
	else{
		ctImCnrOflPrintDebugCtrlSrcCc(ch);
	}

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_6_13: "
INT32 ct_im_cnr_6_13(CtImCnr4 *self)
{
	UCHAR ch = self->ch4;
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

	ret = Im_CNR_Get_RdmaAddr_OFL_CSPR_SPRD_CC_Table(ch, &C_SPRD_TBL_ADDR, &size);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OFL_CSPR_SPRD_CC_Table error = 0x%x\n", ret));
		return ret;
	}

	ret = Im_CNR_Set_RdmaValue_OFL_CSPR_SPRD_CC_Table(&csprSprdCc, &rdmaSprdTbl);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OFL_CSPR_SPRD_CC_Table error = 0x%x\n", ret));
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
		ctImCnrOflPrintDebugCtrlDstCc(0);
		ctImCnrOflPrintDebugCtrlDstCc(1);
	}
	else{
		ctImCnrOflPrintDebugCtrlDstCc(ch);
	}

	return D_DDIM_OK;
}

CtImCnr4* ct_im_cnr4_new(void) 
{
    CtImCnr4 *self = g_object_new(CT_TYPE_IM_CNR4, NULL);
    return self;
}
