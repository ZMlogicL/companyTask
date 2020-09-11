/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :王印斌
*@brief               :CtImCnr7类
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
#include "ctimcnr7.h"

#include <string.h>
#include <stdlib.h>

G_DEFINE_TYPE(CtImCnr7, ct_im_cnr7, G_TYPE_OBJECT); 
#define CT_IM_CNR7_GET_PRIVATE(o) (G_OBJECT_GET_PRIVATE ((o), CT_TYPE_IM_CNR7, CtImCnr7Private))

struct _CtImCnr7Private
{
};

static void ctImCnrOtfPrintDebugCtrlReg(UCHAR ch);
static void ctImCnrOtfPrintDebugCtrlAxi(UCHAR ch);
static void ctImCnrOtfPrintDebugStatAxi(const T_IM_CNR_OTF_AXI_STATUS* const axiStat);
static void ctImCnrOtfPrintDebugCtrlC(UCHAR ch);
static void ctImCnrOtfPrintDebugCMidYTbl(UCHAR ch);
	
static void ct_im_cnr7_constructor(CtImCnr7 *self) 
{
//	CtImCnr7Private *priv = CT_IM_CNR7_GET_PRIVATE(self);
}

static void ct_im_cnr7_destructor(CtImCnr7 *self) 
{
//	CtImCnr7Private *priv = CT_IM_CNR7_GET_PRIVATE(self);
}

static void ctImCnrOtfPrintDebugCtrlReg(UCHAR ch)
{
	UCHAR loop, loopSta, loopEnd;

	Im_CNR_On_Pclk(ch);

	ct_im_cnr_get_loop_cnt(ch, &loopSta, &loopEnd);

	for(loop = loopSta; loop <= loopEnd; loop++){
		Ddim_Print(("ch[%d]\n",           loop));
		Ddim_Print(("YUV_DFMT = %u\n",    io_cnr(loop)->OTF_REG_RW.SPRMOD.bit.YUV_MODE));
		Ddim_Print(("EXMODE   = %u\n",    io_cnr(loop)->OTF_REG_RW.SPRMOD.bit.EXMODE));
		Ddim_Print(("CNRVFM   = %u\n",    io_cnr(loop)->OTF_REG_RW.SPRMOD.bit.CNRVFM));

		Ddim_Print(("HSIZE    = 0x%x\n",  io_cnr(loop)->OTF_REG_RW.HSIZE.bit.HSIZE));
		Ddim_Print(("VSIZE    = 0x%x\n",  io_cnr(loop)->OTF_REG_RW.VSIZE.bit.VSIZE));

		Ddim_Print(("WCDEF    = 0x%x\n",  io_cnr(loop)->OTF_REG_RW.WCDEF.bit.WCDEF));
		Ddim_Print(("WCTA     = 0x%lx\n", io_cnr(loop)->OTF_REG_RW.WCTA.bit.WCTA));

		Ddim_Print(("CNRWOFSX = %u\n",    io_cnr(loop)->OTF_REG_RW.CNRWOFSX.bit.CNRWOFSX));

		Ddim_Print(("CNRCSE   = %u\n",    io_cnr(loop)->OTF_REG_RW.SPRTRG.bit.CNRCSE));

		Ddim_Print(("HDIVL    = %u\n",    io_cnr(loop)->OTF_REG_RW.HDIV.bit.HDIVL));
		Ddim_Print(("HDIVR    = %u\n",    io_cnr(loop)->OTF_REG_RW.HDIV.bit.HDIVR));
	}

	Im_CNR_Off_Pclk(ch);
}

static void ctImCnrOtfPrintDebugCtrlAxi(UCHAR ch)
{
	UCHAR loop, loopSta, loopEnd;

	Im_CNR_On_Pclk(ch);

	ct_im_cnr_get_loop_cnt(ch, &loopSta, &loopEnd);

	for(loop = loopSta; loop <= loopEnd; loop++){
		Ddim_Print(("ch[%d]\n",           loop));
		Ddim_Print(("AWCACHE = 0x%x\n", io_cnr(loop)->OTF_REG_RW.SPRAXISET.bit.AWCACHE));
		Ddim_Print(("AWPROT  = 0x%x\n",   io_cnr(loop)->OTF_REG_RW.SPRAXISET.bit.AWPROT));
	}

	Im_CNR_Off_Pclk(ch);
}

static void  ctImCnrOtfPrintDebugStatAxi(const T_IM_CNR_OTF_AXI_STATUS* const axiStat)
{
	Ddim_Print(("write_channel_response = 0x%x\n", axiStat->write_channel_response));
}

static void ctImCnrOtfPrintDebugCtrlC(UCHAR ch)
{
	UCHAR loop, loopSta, loopEnd;

	Im_CNR_On_Pclk(ch);

	ct_im_cnr_get_loop_cnt(ch, &loopSta, &loopEnd);

	for(loop = loopSta; loop <= loopEnd; loop++){
		Ddim_Print(("ch[%d]\n",           loop));
		Ddim_Print(("CSPREN    = %u\n",   io_cnr(loop)->OTF_CSPR_REG.CSPREN.bit.CSPREN));
		Ddim_Print(("CGDKEN    = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.CGDKEN.bit.CGDKEN));
		Ddim_Print(("MCEN      = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCEN.bit.MCEN));
		Ddim_Print(("MCYTHH_0  = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCYTHH.bit.MCYTHH_0));
		Ddim_Print(("MCYTHH_1  = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCYTHH.bit.MCYTHH_1));
		Ddim_Print(("MCYTHH_2  = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCYTHH.bit.MCYTHH_2));
		Ddim_Print(("MCYTHH_3  = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCYTHH.bit.MCYTHH_3));
		Ddim_Print(("MCYTHV_0  = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCYTHV.bit.MCYTHV_0));
		Ddim_Print(("MCYTHV_1  = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCYTHV.bit.MCYTHV_1));
		Ddim_Print(("MCYTHV_2  = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCYTHV.bit.MCYTHV_2));
		Ddim_Print(("MCYTHV_3  = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCYTHV.bit.MCYTHV_3));
		Ddim_Print(("MCCTHH_0  = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCCTHH.bit.MCCTHH_0));
		Ddim_Print(("MCCTHH_1  = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCCTHH.bit.MCCTHH_1));
		Ddim_Print(("MCCTHH_2  = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCCTHH.bit.MCCTHH_2));
		Ddim_Print(("MCCTHH_3  = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCCTHH.bit.MCCTHH_3));
		Ddim_Print(("MCCTHV_0  = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCCTHV.bit.MCCTHV_0));
		Ddim_Print(("MCCTHV_1  = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCCTHV.bit.MCCTHV_1));
		Ddim_Print(("MCCTHV_2  = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCCTHV.bit.MCCTHV_2));
		Ddim_Print(("MCCTHV_3  = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCCTHV.bit.MCCTHV_3));

		Ddim_Print(("MCYDYMYCR = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCYDYMDT.bit.MCYDYMYCR));
		Ddim_Print(("MCYDYMYG  = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCYDYMDT.bit.MCYDYMYG));
		Ddim_Print(("MCYDYM    = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCYDYM.bit.MCYDYM));

		Ddim_Print(("MCYSCL    = %u\n",   io_cnr(loop)->OTF_CSPR_REG.MCYSCL.bit.MCYSCL));
		Ddim_Print(("MCCSCL    = %u\n",   io_cnr(loop)->OTF_CSPR_REG.MCCSCL.bit.MCCSCL));

		Ddim_Print(("LCEN      = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCEN.bit.LCEN));
		Ddim_Print(("LCYTHH_0  = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCYTHH.bit.LCYTHH_0));
		Ddim_Print(("LCYTHH_1  = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCYTHH.bit.LCYTHH_1));
		Ddim_Print(("LCYTHH_2  = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCYTHH.bit.LCYTHH_2));
		Ddim_Print(("LCYTHH_3  = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCYTHH.bit.LCYTHH_3));
		Ddim_Print(("LCYTHV_0  = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCYTHV.bit.LCYTHV_0));
		Ddim_Print(("LCYTHV_1  = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCYTHV.bit.LCYTHV_1));
		Ddim_Print(("LCYTHV_2  = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCYTHV.bit.LCYTHV_2));
		Ddim_Print(("LCYTHV_3  = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCYTHV.bit.LCYTHV_3));
		Ddim_Print(("LCCTHH_0  = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCCTHH.bit.LCCTHH_0));
		Ddim_Print(("LCCTHH_1  = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCCTHH.bit.LCCTHH_1));
		Ddim_Print(("LCCTHH_2  = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCCTHH.bit.LCCTHH_2));
		Ddim_Print(("LCCTHH_3  = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCCTHH.bit.LCCTHH_3));
		Ddim_Print(("LCCTHV_0  = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCCTHV.bit.LCCTHV_0));
		Ddim_Print(("LCCTHV_1  = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCCTHV.bit.LCCTHV_1));
		Ddim_Print(("LCCTHV_2  = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCCTHV.bit.LCCTHV_2));
		Ddim_Print(("LCCTHV_3  = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCCTHV.bit.LCCTHV_3));

		Ddim_Print(("LCYDYMYCR = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCYDYMDT.bit.LCYDYMYCR));
		Ddim_Print(("LCYDYMYG  = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCYDYMDT.bit.LCYDYMYG));
		Ddim_Print(("LCYDYM    = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.LCYDYM.bit.LCYDYM));

		Ddim_Print(("LCYSCL    = %u\n",   io_cnr(loop)->OTF_CSPR_REG.LCYSCL.bit.LCYSCL));
		Ddim_Print(("LCCSCL    = %u\n",   io_cnr(loop)->OTF_CSPR_REG.LCCSCL.bit.LCCSCL));

		Ddim_Print(("WHTVAL    = %u\n",   io_cnr(loop)->OTF_CSPR_REG.WHTMD.bit.WHTVAL));
		Ddim_Print(("BLENDMD   = %u\n",   io_cnr(loop)->OTF_CSPR_REG.BLEND.bit.BLENDMD));
		Ddim_Print(("CSPRALPBD = %u\n",   io_cnr(loop)->OTF_CSPR_REG.BLEND.bit.CSPRALPBD));
		Ddim_Print(("CSRGMD    = %u\n",   io_cnr(loop)->OTF_CSPR_REG.BLEND.bit.CSRGMD));
	}

	Im_CNR_Off_Pclk(ch);
}

static void ctImCnrOtfPrintDebugCMidYTbl(UCHAR ch)
{
	UCHAR loop, loopSta, loopEnd;

	Im_CNR_On_Pclk(ch);

	ct_im_cnr_get_loop_cnt(ch, &loopSta, &loopEnd);

	for(loop = loopSta; loop <= loopEnd; loop++){
		Ddim_Print(("ch[%d]\n",           loop));
		Ddim_Print(("MCYSCLBD_1 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCYSCLBD.MCYSCLBD1.bit.MCYSCLBD_1));
		Ddim_Print(("MCYSCLBD_2 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCYSCLBD.MCYSCLBD1.bit.MCYSCLBD_2));
		Ddim_Print(("MCYSCLBD_3 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCYSCLBD.MCYSCLBD1.bit.MCYSCLBD_3));
		Ddim_Print(("MCYSCLBD_4 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCYSCLBD.MCYSCLBD1.bit.MCYSCLBD_4));
		Ddim_Print(("MCYSCLBD_5 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCYSCLBD.MCYSCLBD2.bit.MCYSCLBD_5));

		Ddim_Print(("MCYSCLOF_0 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCYSCLOF.MCYSCLOF1.bit.MCYSCLOF_0));
		Ddim_Print(("MCYSCLOF_1 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCYSCLOF.MCYSCLOF1.bit.MCYSCLOF_1));
		Ddim_Print(("MCYSCLOF_2 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCYSCLOF.MCYSCLOF1.bit.MCYSCLOF_2));
		Ddim_Print(("MCYSCLOF_3 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCYSCLOF.MCYSCLOF1.bit.MCYSCLOF_3));
		Ddim_Print(("MCYSCLOF_4 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCYSCLOF.MCYSCLOF2.bit.MCYSCLOF_4));
		Ddim_Print(("MCYSCLOF_5 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCYSCLOF.MCYSCLOF2.bit.MCYSCLOF_5));

		Ddim_Print(("MCYSCLGA_0 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCYSCLGA.MCYSCLGA1.bit.MCYSCLGA_0));
		Ddim_Print(("MCYSCLGA_1 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCYSCLGA.MCYSCLGA1.bit.MCYSCLGA_1));
		Ddim_Print(("MCYSCLGA_2 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCYSCLGA.MCYSCLGA1.bit.MCYSCLGA_2));
		Ddim_Print(("MCYSCLGA_3 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCYSCLGA.MCYSCLGA1.bit.MCYSCLGA_3));
		Ddim_Print(("MCYSCLGA_4 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCYSCLGA.MCYSCLGA2.bit.MCYSCLGA_4));
		Ddim_Print(("MCYSCLGA_5 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.MCYSCLGA.MCYSCLGA2.bit.MCYSCLGA_5));
	}

	Im_CNR_Off_Pclk(ch);
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_3_9: "
INT32 ct_im_cnr_otf_3_9(CtImCnr7 *self)
{
	UCHAR ch = self->ch7;
	INT32 imErcd;
	UINT32 loopcnt;
	T_IM_CNR_OTF_CTRL sprCtrl[2] = {
		[0] = {	// max
			.mode = (E_IM_CNR_OTF_YCC_MODE)7,

			.width = 2360,
			.lines = 4096,

			.w_c_width = 0x3FFF8,

			.divide_left = (E_IM_CNR_VPROCESS)1,
			.divide_right = (E_IM_CNR_VPROCESS)1,

			.w_offset_x = 2360,

			.continuous = E_IM_CNR_ONOFF_ENABLE,

			.pCallBack = (T_IM_CNR_CALLBACK)0xFFFFFFFF,
			.user_param = 0xFFFFFFFF,
		},
		[1] = {	// min
			.mode = (E_IM_CNR_OTF_YCC_MODE)0,

			.width = 96,
			.lines = 72,

			.w_c_width = 0,

			.divide_left = (E_IM_CNR_VPROCESS)0,
			.divide_right = (E_IM_CNR_VPROCESS)0,

			.w_offset_x = 0,

			.continuous = E_IM_CNR_ONOFF_DISABLE,

			.pCallBack = (T_IM_CNR_CALLBACK)0,
			.user_param = 0,
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
		imErcd = Im_CNR_OTF_Ctrl(ch, &sprCtrl[loopcnt]);
		if(imErcd != D_DDIM_OK) {
			Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl error = 0x%x\n", imErcd));
			return imErcd;
		}
		ctImCnrOtfPrintDebugCtrlReg(ch);
	}

	imErcd = Im_CNR_OTF_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_3_10: "
INT32 ct_im_cnr_otf_3_10(CtImCnr7 *self)
{
	UCHAR ch = self->ch7;
	INT32 imErcd;
	UINT32 loopcnt;
	T_IM_CNR_OTF_AXI axiCtrl[2] = {
		[0] = {	// max
			.write_cache_type = 0xF,
			.write_protection_type = 7,
		},
		[1] = {	// min
			.write_cache_type = 0,
			.write_protection_type = 0,
		},
	};

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_OTF_Open(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Open error = 0x%x\n", imErcd));
		return imErcd;
	}

	for(loopcnt = 0; loopcnt < (sizeof(axiCtrl) / sizeof(axiCtrl[0])); loopcnt++) {
		Ddim_Print(("** %u\n", loopcnt));
		imErcd = Im_CNR_OTF_Ctrl_Axi(ch, &axiCtrl[loopcnt]);
		if(imErcd != D_DDIM_OK) {
			Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl error = 0x%x\n", imErcd));
			return imErcd;
		}
		ctImCnrOtfPrintDebugCtrlAxi(ch);
	}

	imErcd = Im_CNR_OTF_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_3_11: "
INT32 ct_im_cnr_otf_3_11(CtImCnr7 *self)
{
	UCHAR ch = self->ch7;
	INT32 imErcd;
	T_IM_CNR_OTF_AXI_STATUS axiStat;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_OTF_Open(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Open error = 0x%x\n", imErcd));
		return imErcd;
	}

#ifdef CO_DEBUG_ON_PC
//OTF	io_cnr(ch)->OTF_REG_RW.SPRAXISET.bit.RRESP = 3;
	io_cnr(ch)->OTF_REG_RW.SPRAXISET.bit.WRESP = 3;
#endif //CO_DEBUG_ON_PC

	imErcd = Im_CNR_OTF_Get_AXI_Status(ch, &axiStat);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Get error = 0x%x\n", imErcd));
		return imErcd;
	}
	ctImCnrOtfPrintDebugStatAxi(&axiStat);

#ifdef CO_DEBUG_ON_PC
//OTF	io_cnr(ch)->OTF_REG_RW.SPRAXISET.bit.RRESP = 0;
	io_cnr(ch)->OTF_REG_RW.SPRAXISET.bit.WRESP = 0;
#endif //CO_DEBUG_ON_PC

	imErcd = Im_CNR_OTF_Get_AXI_Status(ch, &axiStat);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Get error = 0x%x\n", imErcd));
		return imErcd;
	}
	ctImCnrOtfPrintDebugStatAxi(&axiStat);

	imErcd = Im_CNR_OTF_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_3_12: "
INT32 ct_im_cnr_otf_3_12(CtImCnr7 *self)
{
	UCHAR ch = self->ch7;
	INT32 imErcd;
	UINT32 loopcnt;
	T_IM_CNR_CTRL_C sprCtrl[3] = {
		[0] = {	// max
			.enable = (E_IM_CNR_ONOFF)1,
			.gradation_keep_en = (E_IM_CNR_ONOFF)1,
			.mid_freq_nr = {
				.enable = (E_IM_CNR_ONOFF)1,
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
				.y_threshold_cor = 0xFF,
				.y_threshold_gain = 0x01FF,
				.y_threshold_dym_en = (E_IM_CNR_ONOFF)1,
				.y_threshold_scl_en = (E_IM_CNR_ONOFF)1,
				.c_threshold_scl_en = (E_IM_CNR_ONOFF)1,
			},
			.low_freq_nr = {
				.enable = (E_IM_CNR_ONOFF)1,
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
				.y_threshold_cor = 0xFF,
				.y_threshold_gain = 0x01FF,
				.y_threshold_dym_en = (E_IM_CNR_ONOFF)1,
				.y_threshold_scl_en = (E_IM_CNR_ONOFF)1,
				.c_threshold_scl_en = (E_IM_CNR_ONOFF)1,
			},
			.whitening_value = 0xF,
			.c_blend_md = E_IM_CNR_C_BLEND_MD_HUE_SPEC,
			.c_alpha_blend = 0xF,
			.c_range_mode = E_IM_CNR_C_RANGE_MODE_0_64,
		},
		[1] = {	// min
			.enable = (E_IM_CNR_ONOFF)0,
			.gradation_keep_en = (E_IM_CNR_ONOFF)0,
			.mid_freq_nr = {
				.enable = (E_IM_CNR_ONOFF)0,
				.h_y_threshold = {
					0, 0, 0, 0,
				},
				.v_y_threshold = {
					0, 0, 0, 0,
				},
				.h_c_threshold = {
					0, 0, 0, 0,
				},
				.v_c_threshold = {
					0, 0, 0, 0,
				},
				.y_threshold_cor = 0x00,
				.y_threshold_gain = 0x0000,
				.y_threshold_dym_en = (E_IM_CNR_ONOFF)0,
				.y_threshold_scl_en = (E_IM_CNR_ONOFF)0,
				.c_threshold_scl_en = (E_IM_CNR_ONOFF)0,
			},
			.low_freq_nr = {
				.enable = (E_IM_CNR_ONOFF)0,
				.h_y_threshold = {
					0, 0, 0, 0,
				},
				.v_y_threshold = {
					0, 0, 0, 0,
				},
				.h_c_threshold = {
					0, 0, 0, 0,
				},
				.v_c_threshold = {
					0, 0, 0, 0,
				},
				.y_threshold_cor = 0x00,
				.y_threshold_gain = 0x0000,
				.y_threshold_dym_en = (E_IM_CNR_ONOFF)0,
				.y_threshold_scl_en = (E_IM_CNR_ONOFF)0,
				.c_threshold_scl_en = (E_IM_CNR_ONOFF)0,
			},
			.whitening_value = 0,
			.c_blend_md = E_IM_CNR_C_BLEND_MD_FIX,
			.c_alpha_blend = 0,
			.c_range_mode = E_IM_CNR_C_RANGE_MODE_0_1,
		},
		[2] = {	// countup
			.enable = (E_IM_CNR_ONOFF)0,
			.gradation_keep_en = (E_IM_CNR_ONOFF)1,
			.mid_freq_nr = {
				.enable = (E_IM_CNR_ONOFF)1,
				.h_y_threshold = {
					0x1, 0x2, 0x3, 0x4,
				},
				.v_y_threshold = {
					0x5, 0x6, 0x7, 0x8,
				},
				.h_c_threshold = {
					0x9, 0xA, 0xB, 0xC,
				},
				.v_c_threshold = {
					0xD, 0xE, 0xF, 0x10,
				},
				.y_threshold_cor = 0x11,
				.y_threshold_gain = 0x0012,
				.y_threshold_dym_en = (E_IM_CNR_ONOFF)1,
				.y_threshold_scl_en = (E_IM_CNR_ONOFF)0,
				.c_threshold_scl_en = (E_IM_CNR_ONOFF)1,
			},
			.low_freq_nr = {
				.enable = (E_IM_CNR_ONOFF)0,
				.h_y_threshold = {
					0x21, 0x22, 0x23, 0x24,
				},
				.v_y_threshold = {
					0x25, 0x26, 0x27, 0x28,
				},
				.h_c_threshold = {
					0x29, 0x2A, 0x2B, 0x2C,
				},
				.v_c_threshold = {
					0x2D, 0x2E, 0x2F, 0x30,
				},
				.y_threshold_cor = 0x31,
				.y_threshold_gain = 0x0032,
				.y_threshold_dym_en = (E_IM_CNR_ONOFF)1,
				.y_threshold_scl_en = (E_IM_CNR_ONOFF)1,
				.c_threshold_scl_en = (E_IM_CNR_ONOFF)0,
			},
			.whitening_value = 7,
			.c_blend_md = E_IM_CNR_C_BLEND_MD_COL_DIFF_EDGE,
			.c_alpha_blend = 8,
			.c_range_mode = E_IM_CNR_C_RANGE_MODE_0_8,
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
		imErcd = Im_CNR_OTF_Ctrl_C(ch, &sprCtrl[loopcnt]);
		if(imErcd != D_DDIM_OK) {
			Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl error = 0x%x\n", imErcd));
			return imErcd;
		}
		ctImCnrOtfPrintDebugCtrlC(ch);
	}

	imErcd = Im_CNR_OTF_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_3_13: "
INT32 ct_im_cnr_otf_3_13(CtImCnr7 *self)
{
	UCHAR ch = self->ch7;
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
		imErcd = Im_CNR_OTF_Set_CSPR_Mid_Y_Table(ch, &sprTbl[loopcnt]);
		if(imErcd != D_DDIM_OK) {
			Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl error = 0x%x\n", imErcd));
			return imErcd;
		}
		ctImCnrOtfPrintDebugCMidYTbl(ch);
	}

	imErcd = Im_CNR_OTF_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_3_20: "
INT32 ct_im_cnr_otf_3_20(CtImCnr7 *self)
{
	UCHAR ch = self->ch7;
	INT32 imErcd;
	const char C_DUMPMSG[] = "ch%d SPRTRG = %u\n";

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_OTF_Open(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Open error = 0x%x\n", imErcd));
		return imErcd;
	}

#ifdef CO_DEBUG_ON_PC
	io_cnr(ch)->OTF_REG_RW.SPRTRG.bit.SPRTRG = 3;
#endif //CO_DEBUG_ON_PC
	Im_CNR_On_Pclk(ch);
	Ddim_Print((C_DUMPMSG, D_IM_CNR_CH_0, io_cnr(D_IM_CNR_CH_0)->OTF_REG_RW.SPRTRG.bit.SPRTRG));
	Ddim_Print((C_DUMPMSG, D_IM_CNR_CH_1, io_cnr(D_IM_CNR_CH_1)->OTF_REG_RW.SPRTRG.bit.SPRTRG));

	Im_CNR_Off_Pclk(ch);

	imErcd = Im_CNR_OTF_Stop(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Stop error = 0x%x\n", imErcd));
		return imErcd;
	}
	Im_CNR_On_Pclk(ch);
	Ddim_Print((C_DUMPMSG, D_IM_CNR_CH_0, io_cnr(D_IM_CNR_CH_0)->OTF_REG_RW.SPRTRG.bit.SPRTRG));
	Ddim_Print((C_DUMPMSG, D_IM_CNR_CH_1, io_cnr(D_IM_CNR_CH_1)->OTF_REG_RW.SPRTRG.bit.SPRTRG));
	Im_CNR_Off_Pclk(ch);

#ifdef CO_DEBUG_ON_PC
	io_cnr(ch)->OTF_REG_RW.SPRTRG.bit.SPRTRG = 2;
#endif //CO_DEBUG_ON_PC

	imErcd = Im_CNR_OTF_Stop(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Stop error = 0x%x\n", imErcd));
		return imErcd;
	}
	Im_CNR_On_Pclk(ch);
	Ddim_Print((C_DUMPMSG, D_IM_CNR_CH_0, io_cnr(D_IM_CNR_CH_0)->OTF_REG_RW.SPRTRG.bit.SPRTRG));
	Ddim_Print((C_DUMPMSG, D_IM_CNR_CH_1, io_cnr(D_IM_CNR_CH_1)->OTF_REG_RW.SPRTRG.bit.SPRTRG));
	Im_CNR_Off_Pclk(ch);

	imErcd = Im_CNR_OTF_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_3_26: "
INT32 ct_im_cnr_otf_3_26(CtImCnr7 *self)
{
	UCHAR ch = self->ch7;
	INT32 imErcd;
	UINT32 loopcnt;
	T_IM_CNR_OTF_OUTADDR_INFO addrInfo[2] = {
		[0] = {	// max
			.use_bank_num = 1,
			.w_c_addr[0] = 0xFFFFFFFF,
		},
		[1] = {	// min
			.use_bank_num = 1,
			.w_c_addr[0] = 0,
		},
	};

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_OTF_Open(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Open error = 0x%x\n", imErcd));
		return imErcd;
	}

	for(loopcnt = 0; loopcnt < (sizeof(addrInfo) / sizeof(addrInfo[0])); loopcnt++) {
		Ddim_Print(("** %u\n", loopcnt));
		imErcd = Im_CNR_OTF_Set_OutAddr_Info(ch, &addrInfo[loopcnt]);
		if(imErcd != D_DDIM_OK) {
			Ddim_Print((D_IM_CNR_FUNC_NAME "Set OutAddrInfo error = 0x%x\n", imErcd));
			return imErcd;
		}
		ctImCnrOtfPrintDebugCtrlReg(ch);
	}

	imErcd = Im_CNR_OTF_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_6_14: "
INT32 ct_im_cnr_6_14(CtImCnr7 *self)
{
	UCHAR ch = self->ch7;
	INT32 ret;
	T_IM_RDMA_CTRL rdmaCtrl;
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
	T_IM_CNR_RDMA_DATA_CTRL_C	rdmaCtrlC;
	const  T_IM_CNR_RDMA_ADDR_CTRL_C*	C_CNR_CTRL_ADDR;
	ULONG	size;

	ret = Im_CNR_Get_RdmaAddr_OTF_Ctrl_C(ch, &C_CNR_CTRL_ADDR, &size);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OTF_Ctrl_C error = 0x%x\n", ret));
		return ret;
	}

	ret = Im_CNR_Set_RdmaValue_OTF_Ctrl_C(&sprCtrlC, &rdmaCtrlC);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OTF_Ctrl_C error = 0x%x\n", ret));
		return ret;
	}

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)C_CNR_CTRL_ADDR;
	rdmaCtrl.reg_data_top_addr	= (ULONG)&rdmaCtrlC;
	rdmaCtrl.req_threshold		= E_IM_RDMA_PRCH_CNT_NOLIMIT;
	rdmaCtrl.int_mode			= E_IM_RDMA_INT_MODE_AND_ERR;
	rdmaCtrl.pCallBack			= NULL;
	ret = Im_RDMA_Ctrl_Quick_Start_Sync(D_DDIM_WAIT_END_TIME, &rdmaCtrl);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Ctrl error = 0x%x\n", ret));
		return ret;
	}

	if(ch == D_IM_CNR_CH_2){
		ctImCnrOtfPrintDebugCMidYTbl(0);
		ctImCnrOtfPrintDebugCMidYTbl(1);
	}
	else{
		ctImCnrOtfPrintDebugCMidYTbl(ch);
	}

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_6_15: "
INT32 ct_im_cnr_6_15(CtImCnr7 *self)
{
	UCHAR ch = self->ch7;
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

	ret = Im_CNR_Get_RdmaAddr_OTF_CSPR_Mid_Y_Table(ch, &C_MID_Y_TBL_ADDR, &size);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OTF_CSPR_Mid_Y_Table error = 0x%x\n", ret));
		return ret;
	}

	ret = Im_CNR_Set_RdmaValue_OTF_CSPR_Mid_Y_Table(&cnrTable, &rdmaMidYTbl);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OTF_CSPR_Mid_Y_Table error = 0x%x\n", ret));
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
		ctImCnrOtfPrintDebugCMidYTbl(0);
		ctImCnrOtfPrintDebugCMidYTbl(1);
	}
	else{
		ctImCnrOtfPrintDebugCMidYTbl(ch);
	}

	return D_DDIM_OK;
}

CtImCnr7* ct_im_cnr7_new(void) 
{
    CtImCnr7 *self = g_object_new(CT_TYPE_IM_CNR7, NULL);
    return self;
}
