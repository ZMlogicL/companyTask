/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :王印斌
*@brief               :CtImCnr13类
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
#include "ctimcnr13.h"

#include <string.h>
#include <stdlib.h>

G_DEFINE_TYPE(CtImCnr13, ct_im_cnr13, G_TYPE_OBJECT); 
#define CT_IM_CNR13_GET_PRIVATE(o) (G_OBJECT_GET_PRIVATE ((o), CT_TYPE_IM_CNR13, CtImCnr13Private))

struct _CtImCnr13Private
{
};

static void ctImCnrOflPrintDebugCtrlReg(UCHAR ch);
static void ctImCnrOflPrintDebugCtrlAxi(UCHAR ch);
static void ctImCnrOflPrintDebugStatAxi(const T_IM_CNR_OFL_AXI_STATUS* const axiStat);
static void ctImCnrOflPrintDebugCtrlC(UCHAR ch);

static void ct_im_cnr13_constructor(CtImCnr13 *self) 
{
}

static void ct_im_cnr13_destructor(CtImCnr13 *self) 
{
}

static void ctImCnrOflPrintDebugCtrlReg(UCHAR ch)
{
	UCHAR loop, loopSta, loopEnd;

	Im_CNR_On_Pclk(ch);

	ct_im_cnr_get_loop_cnt(ch, &loopSta, &loopEnd);

	for(loop = loopSta; loop <= loopEnd; loop++){
		Ddim_Print(("ch[%d]\n",           loop));
		Ddim_Print(("YUV_DFMT = %u\n",    io_cnr(loop)->OFL_REG_RW.SPRMOD.bit.YUV_MODE));
		Ddim_Print(("HSIZE    = 0x%x\n",  io_cnr(loop)->OFL_REG_RW.HSIZE.bit.HSIZE));
		Ddim_Print(("VSIZE    = 0x%x\n",  io_cnr(loop)->OFL_REG_RW.VSIZE.bit.VSIZE));

		Ddim_Print(("RYDEF    = 0x%x\n",  io_cnr(loop)->OFL_REG_RW.RYDEF.bit.RYDEF));
		Ddim_Print(("RYTA     = 0x%lx\n", io_cnr(loop)->OFL_REG_RW.RYTA.bit.RYTA));

		Ddim_Print(("RCDEF    = 0x%x\n",  io_cnr(loop)->OFL_REG_RW.RCDEF.bit.RCDEF));
		Ddim_Print(("RCBTA    = 0x%lx\n", io_cnr(loop)->OFL_REG_RW.RCBTA.bit.RCBTA));
		Ddim_Print(("RCRTA    = 0x%lx\n", io_cnr(loop)->OFL_REG_RW.RCRTA.bit.RCRTA));

		Ddim_Print(("WYDEF    = 0x%x\n",  io_cnr(loop)->OFL_REG_RW.WYDEF.bit.WYDEF));
		Ddim_Print(("WYTA     = 0x%lx\n", io_cnr(loop)->OFL_REG_RW.WYTA.bit.WYTA));

		Ddim_Print(("WCDEF    = 0x%x\n",  io_cnr(loop)->OFL_REG_RW.WCDEF.bit.WCDEF));
		Ddim_Print(("WCBTA    = 0x%lx\n", io_cnr(loop)->OFL_REG_RW.WCBTA.bit.WCBTA));
		Ddim_Print(("WCRTA    = 0x%lx\n", io_cnr(loop)->OFL_REG_RW.WCRTA.bit.WCRTA));

		Ddim_Print(("TMPTA    = 0x%lx\n", io_cnr(loop)->OFL_REG_RW.TMPTA.bit.TMPTA));

		Ddim_Print(("VDIVT    = %u\n",    io_cnr(loop)->OFL_REG_RW.VDIV.bit.VDIVT));
		Ddim_Print(("VDIVB    = %u\n",    io_cnr(loop)->OFL_REG_RW.VDIV.bit.VDIVB));
	}

	Im_CNR_Off_Pclk(ch);
}

static void ctImCnrOflPrintDebugCtrlAxi(UCHAR ch)
{
	UCHAR loop, loopSta, loopEnd;

	Im_CNR_On_Pclk(ch);

	ct_im_cnr_get_loop_cnt(ch, &loopSta, &loopEnd);

	for(loop = loopSta; loop <= loopEnd; loop++){
		Ddim_Print(("ch[%d]\n",           loop));
		Ddim_Print(("ARCACHE = 0x%x\n", io_cnr(loop)->OFL_REG_RW.SPRAXISET.bit.ARCACHE));
		Ddim_Print(("ARPROT  = 0x%x\n", io_cnr(loop)->OFL_REG_RW.SPRAXISET.bit.ARPROT));
		Ddim_Print(("AWCACHE = 0x%x\n", io_cnr(loop)->OFL_REG_RW.SPRAXISET.bit.AWCACHE));
		Ddim_Print(("AWPROT  = 0x%x\n", io_cnr(loop)->OFL_REG_RW.SPRAXISET.bit.AWPROT));
	}

	Im_CNR_Off_Pclk(ch);
}

static void ctImCnrOflPrintDebugStatAxi(const T_IM_CNR_OFL_AXI_STATUS* const axiStat)
{
	Ddim_Print(("read_channel_response  = 0x%x\n", axiStat->read_channel_response));
	Ddim_Print(("write_channel_response = 0x%x\n", axiStat->write_channel_response));
}

static void ctImCnrOflPrintDebugCtrlC(UCHAR ch)
{
	UCHAR loop, loopSta, loopEnd;

	Im_CNR_On_Pclk(ch);

	ct_im_cnr_get_loop_cnt(ch, &loopSta, &loopEnd);

	for(loop = loopSta; loop <= loopEnd; loop++){
		Ddim_Print(("ch[%d]\n",           loop));
		Ddim_Print(("CSPREN    = %u\n",   io_cnr(loop)->OFL_CSPR_REG.CSPREN.bit.CSPREN));
		Ddim_Print(("CGDKEN    = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CGDKEN.bit.CGDKEN));
		Ddim_Print(("MCEN      = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCEN.bit.MCEN));
		Ddim_Print(("MCYTHH_0  = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCYTHH.bit.MCYTHH_0));
		Ddim_Print(("MCYTHH_1  = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCYTHH.bit.MCYTHH_1));
		Ddim_Print(("MCYTHH_2  = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCYTHH.bit.MCYTHH_2));
		Ddim_Print(("MCYTHH_3  = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCYTHH.bit.MCYTHH_3));
		Ddim_Print(("MCYTHV_0  = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCYTHV.bit.MCYTHV_0));
		Ddim_Print(("MCYTHV_1  = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCYTHV.bit.MCYTHV_1));
		Ddim_Print(("MCYTHV_2  = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCYTHV.bit.MCYTHV_2));
		Ddim_Print(("MCYTHV_3  = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCYTHV.bit.MCYTHV_3));
		Ddim_Print(("MCCTHH_0  = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCCTHH.bit.MCCTHH_0));
		Ddim_Print(("MCCTHH_1  = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCCTHH.bit.MCCTHH_1));
		Ddim_Print(("MCCTHH_2  = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCCTHH.bit.MCCTHH_2));
		Ddim_Print(("MCCTHH_3  = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCCTHH.bit.MCCTHH_3));
		Ddim_Print(("MCCTHV_0  = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCCTHV.bit.MCCTHV_0));
		Ddim_Print(("MCCTHV_1  = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCCTHV.bit.MCCTHV_1));
		Ddim_Print(("MCCTHV_2  = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCCTHV.bit.MCCTHV_2));
		Ddim_Print(("MCCTHV_3  = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCCTHV.bit.MCCTHV_3));

		Ddim_Print(("MCYDYMYCR = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCYDYMDT.bit.MCYDYMYCR));
		Ddim_Print(("MCYDYMYG  = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCYDYMDT.bit.MCYDYMYG));
		Ddim_Print(("MCYDYM    = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.MCYDYM.bit.MCYDYM));

		Ddim_Print(("MCYSCL    = %u\n",   io_cnr(loop)->OFL_CSPR_REG.MCYSCL.bit.MCYSCL));
		Ddim_Print(("MCSSCL    = %u\n",   io_cnr(loop)->OFL_CSPR_REG.MCSSCL.bit.MCSSCL));
		Ddim_Print(("MCCSCL    = %u\n",   io_cnr(loop)->OFL_CSPR_REG.MCCSCL.bit.MCCSCL));

		Ddim_Print(("LCEN      = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCEN.bit.LCEN));
		Ddim_Print(("LCYTHH_0  = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCYTHH.bit.LCYTHH_0));
		Ddim_Print(("LCYTHH_1  = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCYTHH.bit.LCYTHH_1));
		Ddim_Print(("LCYTHH_2  = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCYTHH.bit.LCYTHH_2));
		Ddim_Print(("LCYTHH_3  = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCYTHH.bit.LCYTHH_3));
		Ddim_Print(("LCYTHV_0  = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCYTHV.bit.LCYTHV_0));
		Ddim_Print(("LCYTHV_1  = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCYTHV.bit.LCYTHV_1));
		Ddim_Print(("LCYTHV_2  = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCYTHV.bit.LCYTHV_2));
		Ddim_Print(("LCYTHV_3  = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCYTHV.bit.LCYTHV_3));
		Ddim_Print(("LCCTHH_0  = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCCTHH.bit.LCCTHH_0));
		Ddim_Print(("LCCTHH_1  = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCCTHH.bit.LCCTHH_1));
		Ddim_Print(("LCCTHH_2  = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCCTHH.bit.LCCTHH_2));
		Ddim_Print(("LCCTHH_3  = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCCTHH.bit.LCCTHH_3));
		Ddim_Print(("LCCTHV_0  = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCCTHV.bit.LCCTHV_0));
		Ddim_Print(("LCCTHV_1  = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCCTHV.bit.LCCTHV_1));
		Ddim_Print(("LCCTHV_2  = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCCTHV.bit.LCCTHV_2));
		Ddim_Print(("LCCTHV_3  = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCCTHV.bit.LCCTHV_3));

		Ddim_Print(("LCYDYMYCR = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCYDYMDT.bit.LCYDYMYCR));
		Ddim_Print(("LCYDYMYG  = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCYDYMDT.bit.LCYDYMYG));
		Ddim_Print(("LCYDYM    = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.LCYDYM.bit.LCYDYM));

		Ddim_Print(("LCYSCL    = %u\n",   io_cnr(loop)->OFL_CSPR_REG.LCYSCL.bit.LCYSCL));
		Ddim_Print(("LCSSCL    = %u\n",   io_cnr(loop)->OFL_CSPR_REG.LCSSCL.bit.LCSSCL));
		Ddim_Print(("LCCSCL    = %u\n",   io_cnr(loop)->OFL_CSPR_REG.LCCSCL.bit.LCCSCL));

		Ddim_Print(("WHTEN     = %u\n",   io_cnr(loop)->OFL_CSPR_REG.WHTMD.bit.WHTEN));
		Ddim_Print(("WHTVAL    = %u\n",   io_cnr(loop)->OFL_CSPR_REG.WHTMD.bit.WHTVAL));
		Ddim_Print(("WHTBASE   = %u\n",   io_cnr(loop)->OFL_CSPR_REG.WHTMD.bit.WHTBASE));
		Ddim_Print(("BLENDMD   = %u\n",   io_cnr(loop)->OFL_CSPR_REG.BLEND.bit.BLENDMD));
		Ddim_Print(("CSPRALPBD = %u\n",   io_cnr(loop)->OFL_CSPR_REG.BLEND.bit.CSPRALPBD));
		Ddim_Print(("CSRGEN    = %u\n",   io_cnr(loop)->OFL_CSPR_REG.BLEND.bit.CSRGEN));
		Ddim_Print(("CSRGMD    = %u\n",   io_cnr(loop)->OFL_CSPR_REG.BLEND.bit.CSRGMD));
	}

	Im_CNR_Off_Pclk(ch);
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_5: "
INT32 ct_im_cnr_ofl_1_5(CtImCnr13 *self)
{
	
	INT32 imErcd;
#ifdef CO_DEBUG_ON_PC
	UINT32 waitFactor;
#endif //CO_DEBUG_ON_PC

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

#ifdef CO_DEBUG_ON_PC
	UCHAR ch = self->ch13;
	imErcd = Im_CNR_OFL_Open(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Open error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OFL_Start_Async(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Start Async error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OFL_Wait_End(ch, &waitFactor, 10);
	if(imErcd != D_IM_CNR_SEM_TIMEOUT_ERR) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Wait End error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OFL_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}
#else //!CO_DEBUG_ON_PC
	Ddim_Print(("%s: Only debug on PC\n", D_IM_CNR_FUNC_NAME));
	imErcd = D_DDIM_SYSTEM_ERROR;
#endif //!CO_DEBUG_ON_PC

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_6: "
INT32 ct_im_cnr_ofl_1_6(CtImCnr13 *self)
{
	UCHAR ch = self->ch13;
	INT32 imErcd;
	UINT32 waitFactor;
	DDIM_USER_ID fidBack;
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

	imErcd = Im_CNR_OFL_Start_Async(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Start Async error = 0x%x\n", imErcd));
		return imErcd;
	}

	fidBack = FID_IM_CNR;
	FID_IM_CNR = 0xfff;
	imErcd = Im_CNR_OFL_Wait_End(ch, &waitFactor, 10);
	if(imErcd != D_IM_CNR_SEM_NG) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Wait End error = 0x%x\n", imErcd));
		return imErcd;
	}

	FID_IM_CNR = fidBack;

	imErcd = Im_CNR_OFL_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_7: "
INT32 ct_im_cnr_ofl_1_7(CtImCnr13 *self)
{
	UCHAR ch = self->ch13;
	INT32 imErcd;
	DDIM_USER_ID sidBack;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	sidBack = SID_IM_CNR_OFL(ch);
	SID_IM_CNR_OFL(ch) = 0xfff;

	imErcd = Im_CNR_OFL_Close(ch);
	if(imErcd != D_IM_CNR_SEM_NG) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	SID_IM_CNR_OFL(ch) = sidBack;

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_8: "
INT32 ct_im_cnr_ofl_1_8(CtImCnr13 *self)
{
	UCHAR ch = self->ch13;
	INT32 imErcd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_OFL_Open(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Open error = 0x%x\n", imErcd));
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
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_9: "
INT32 ct_im_cnr_ofl_1_9(CtImCnr13 *self)
{
	UCHAR ch = self->ch13;
	INT32 imErcd;
	UINT32 loopcnt;
	T_IM_CNR_OFL_CTRL sprCtrl[2] = {
		[0] = {	// max
			.mode = (E_IM_CNR_OFL_YCC_MODE)7,

			.width = 0x7FFF,
			.lines = 0x7FFF,

			.r_y_width = 0x3FFFF,
			.r_y_addr = 0xFFFFFFFF,

			.r_c_width = 0x3FFFF,
			.r_cb_addr = 0xFFFFFFFF,
			.r_cr_addr = 0xFFFFFFFF,

			.w_y_width = 0x3FFFF,
			.w_y_addr = 0xFFFFFFFF,

			.w_c_width = 0x3FFFF,
			.w_cb_addr = 0xFFFFFFFF,
			.w_cr_addr = 0xFFFFFFFF,

			.work_addr = 0xFFFFFFFF,

			.divide_top = (E_IM_CNR_VPROCESS)1,
			.divide_bot = (E_IM_CNR_VPROCESS)1,

			.pCallBack = (T_IM_CNR_CALLBACK)0xFFFFFFFF,
			.user_param = 0xFFFFFFFF,
		},
		[1] = {	// min
			.mode = (E_IM_CNR_OFL_YCC_MODE)0,

			.width = 0,
			.lines = 0,

			.r_y_width = 0,
			.r_y_addr = 0,

			.r_c_width = 0,
			.r_cb_addr = 0,
			.r_cr_addr = 0,

			.w_y_width = 0,
			.w_y_addr = 0,

			.w_c_width = 0,
			.w_cb_addr = 0,
			.w_cr_addr = 0,

			.work_addr = 0,

			.divide_top = (E_IM_CNR_VPROCESS)0,
			.divide_bot = (E_IM_CNR_VPROCESS)0,

			.pCallBack = (T_IM_CNR_CALLBACK)0,
			.user_param = 0,
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
		imErcd = Im_CNR_OFL_Ctrl(ch, &sprCtrl[loopcnt]);
		if(imErcd != D_DDIM_OK) {
			Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl error = 0x%x\n", imErcd));
			return imErcd;
		}
		ctImCnrOflPrintDebugCtrlReg(ch);
	}

	imErcd = Im_CNR_OFL_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_10: "
INT32 ct_im_cnr_ofl_1_10(CtImCnr13 *self)
{
	UCHAR ch = self->ch13;
	INT32 imErcd;
	UINT32 loopcnt;
	T_IM_CNR_OFL_AXI axiCtrl[2] = {
		[0] = {	// max
			.read_cache_type = 0xF,
			.read_protection_type = 7,
			.write_cache_type = 0xF,
			.write_protection_type = 7,
		},
		[1] = {	// min
			.read_cache_type = 0,
			.read_protection_type = 0,
			.write_cache_type = 0,
			.write_protection_type = 0,
		},
	};

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_OFL_Open(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Open error = 0x%x\n", imErcd));
		return imErcd;
	}

	for(loopcnt = 0; loopcnt < (sizeof(axiCtrl) / sizeof(axiCtrl[0])); loopcnt++) {
		Ddim_Print(("** %u\n", loopcnt));
		imErcd = Im_CNR_OFL_Ctrl_Axi(ch, &axiCtrl[loopcnt]);
		if(imErcd != D_DDIM_OK) {
			Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl error = 0x%x\n", imErcd));
			return imErcd;
		}
		ctImCnrOflPrintDebugCtrlAxi(ch);
	}

	imErcd = Im_CNR_OFL_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_11: "
INT32 ct_im_cnr_ofl_1_11(CtImCnr13 *self)
{
	UCHAR ch = self->ch13;
	INT32 imErcd;
	T_IM_CNR_OFL_AXI_STATUS axiStat;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_OFL_Open(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Open error = 0x%x\n", imErcd));
		return imErcd;
	}

#ifdef CO_DEBUG_ON_PC
	io_cnr(ch)->OFL_REG_RW.SPRAXISET.bit.RRESP = 3;
	io_cnr(ch)->OFL_REG_RW.SPRAXISET.bit.WRESP = 3;
#endif //CO_DEBUG_ON_PC

	imErcd = Im_CNR_OFL_Get_AXI_Status(ch, &axiStat);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Get error = 0x%x\n", imErcd));
		return imErcd;
	}
	ctImCnrOflPrintDebugStatAxi(&axiStat);

#ifdef CO_DEBUG_ON_PC
	io_cnr(ch)->OFL_REG_RW.SPRAXISET.bit.RRESP = 0;
	io_cnr(ch)->OFL_REG_RW.SPRAXISET.bit.WRESP = 0;
#endif //CO_DEBUG_ON_PC

	imErcd = Im_CNR_OFL_Get_AXI_Status(ch, &axiStat);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Get error = 0x%x\n", imErcd));
		return imErcd;
	}
	ctImCnrOflPrintDebugStatAxi(&axiStat);

	imErcd = Im_CNR_OFL_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_12: "
INT32 ct_im_cnr_ofl_1_12(CtImCnr13 *self)
{
	UCHAR ch = self->ch13;
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
				.c_y_threshold_scl_en = (E_IM_CNR_ONOFF)1,
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
				.c_y_threshold_scl_en = (E_IM_CNR_ONOFF)1,
				.c_threshold_scl_en = (E_IM_CNR_ONOFF)1,
			},
			.whitening_enable = (E_IM_CNR_ONOFF)1,
			.whitening_value = 0xF,
			.whitening_base = (E_IM_CNR_WHITEN_BASE)3,
			.c_blend_md = E_IM_CNR_C_BLEND_MD_HUE_SPEC,
			.c_alpha_blend = 0xF,
			.c_range = (E_IM_CNR_ONOFF)1,
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
				.c_y_threshold_scl_en = (E_IM_CNR_ONOFF)0,
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
				.c_y_threshold_scl_en = (E_IM_CNR_ONOFF)0,
				.c_threshold_scl_en = (E_IM_CNR_ONOFF)0,
			},
			.whitening_enable = (E_IM_CNR_ONOFF)0,
			.whitening_value = 0,
			.whitening_base = (E_IM_CNR_WHITEN_BASE)0,
			.c_blend_md = E_IM_CNR_C_BLEND_MD_FIX,
			.c_alpha_blend = 0,
			.c_range = (E_IM_CNR_ONOFF)0,
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
				.c_y_threshold_scl_en = (E_IM_CNR_ONOFF)1,
				.c_threshold_scl_en = (E_IM_CNR_ONOFF)0,
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
				.c_y_threshold_scl_en = (E_IM_CNR_ONOFF)0,
				.c_threshold_scl_en = (E_IM_CNR_ONOFF)0,
			},
			.whitening_enable = (E_IM_CNR_ONOFF)1,
			.whitening_value = 7,
			.whitening_base = (E_IM_CNR_WHITEN_BASE)2,
			.c_blend_md = E_IM_CNR_C_BLEND_MD_COL_DIFF_EDGE,
			.c_alpha_blend = 8,
			.c_range = (E_IM_CNR_ONOFF)1,
			.c_range_mode = E_IM_CNR_C_RANGE_MODE_0_8,
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
		imErcd = Im_CNR_OFL_Ctrl_C(ch, &sprCtrl[loopcnt]);
		if(imErcd != D_DDIM_OK) {
			Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl error = 0x%x\n", imErcd));
			return imErcd;
		}
		ctImCnrOflPrintDebugCtrlC(ch);
	}

	imErcd = Im_CNR_OFL_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_6_1: "
INT32 ct_im_cnr_6_1(CtImCnr13 *self)
{
	UCHAR ch = self->ch13;
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

	ret = Im_CNR_Get_RdmaAddr_OFL_Ctrl_C(ch, &C_CNR_CTRL_ADDR, &size);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OFL_Ctrl_C error = 0x%x\n", ret));
		return ret;
	}

	ret = Im_CNR_Set_RdmaValue_OFL_Ctrl_C(&sprCtrlC, &rdmaCtrlC);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OFL_Ctrl_C error = 0x%x\n", ret));
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
		ctImCnrOflPrintDebugCtrlC(0);
		ctImCnrOflPrintDebugCtrlC(1);
	}
	else{
		ctImCnrOflPrintDebugCtrlC(ch);
	}

	return D_DDIM_OK;
}

CtImCnr13* ct_im_cnr13_new(void) 
{
    CtImCnr13 *self = g_object_new(CT_TYPE_IM_CNR13, NULL);
    return self;
}
