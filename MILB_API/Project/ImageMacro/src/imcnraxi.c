/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-07
*@author              :李昕
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年06月开始开发
*/

#include "imcnraxi.h"
#include "imcnr.h"
#include "imcnrset.h"
#include "imcnrget.h"
#include "imcnrinit.h"
#include "imcnrcspr.h"
#include "driver_common.h"
// #if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
// #endif
#include "dd_arm.h"
#include "ddim_user_custom.h"
#include "jdscnr.h"
// for memset
#include <string.h>

K_TYPE_DEFINE_WITH_PRIVATE(ImCnrAxi, im_cnr_axi);
#define IM_CNR_AXI_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImCnrAxiPrivate, IM_TYPE_CNR_AXI))

struct _ImCnrAxiPrivate
{
	int a;
};

/*----------------------------------------------------------------------*/
/* Local Method Definition												*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
static void im_cnr_axi_constructor(ImCnrAxi *self)
{
}

static void im_cnr_axi_destructor(ImCnrAxi *self)
{
}

/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/

/*----------------------------------------------------------------------*/
/* Global Function														*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
/*
CNR(OFL) Control set AXI bus I/F Control
*/
INT32 im_cnr_axi_ofl_ctrl_axi(ImCnrAxi*self, UCHAR ch, const TImCnrOflAxi* const axi_ctrl )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_axi_ofl_ctrl_axi( ) error. input channel error : %d\n", ch));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( axi_ctrl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_axi_ofl_ctrl_axi( ) Parameter is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnr_on_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	ImCnr_IO_CNR(ch)->OFL_REG_RW.SPRAXISET.bit.AWPROT		= axi_ctrl->writeProtectionType;
	ImCnr_IO_CNR(ch)->OFL_REG_RW.SPRAXISET.bit.ARPROT		= axi_ctrl->readProtectionType;
	ImCnr_IO_CNR(ch)->OFL_REG_RW.SPRAXISET.bit.AWCACHE	= axi_ctrl->writeCacheType;
	ImCnr_IO_CNR(ch)->OFL_REG_RW.SPRAXISET.bit.ARCACHE	= axi_ctrl->readCacheType;

	im_cnr_off_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	return D_DDIM_OK;
}

/*
CNR(OTF) Control set AXI bus I/F Control
*/
INT32 im_cnr_axi_otf_ctrl_axi(ImCnrAxi*self, UCHAR ch, const TImCnrOtfAxi* const axi_ctrl )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_axi_otf_ctrl_axi( ) error. input channel error : %d\n", ch));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( axi_ctrl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_axi_otf_ctrl_axi( ) Parameter is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnr_on_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	ImCnr_IO_CNR(ch)->OTF_REG_RW.SPRAXISET.bit.AWPROT		= axi_ctrl->writeProtectionType;
	ImCnr_IO_CNR(ch)->OTF_REG_RW.SPRAXISET.bit.AWCACHE	= axi_ctrl->writeCacheType;

	im_cnr_off_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	return D_DDIM_OK;
}

/*
Get AXI bus I/F Status
*/
INT32 im_cnr_axi_ofl_get_axi_status(ImCnrAxi*self, UCHAR ch, TImCnrOflAxiStatus* const sts )
{
#ifdef CO_PARAM_CHECK
	if (ch >= (ImCnr_D_IM_CNR_CH_NUM_MAX-1)) {
		Ddim_Assertion(("im_cnr_axi_ofl_get_axi_status( ) error. input channel error : %d\n", ch));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( sts == NULL ) {
		// sts setting error
		Ddim_Assertion(("I:im_cnr_axi_ofl_get_axi_status( ) Parameter is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnr_on_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	sts->readChannelResponse = ImCnr_IO_CNR(ch)->OFL_REG_RW.SPRAXISET.bit.RRESP;
	sts->writeChannelResponse = ImCnr_IO_CNR(ch)->OFL_REG_RW.SPRAXISET.bit.WRESP;

	im_cnr_off_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	return D_DDIM_OK;
}

/*
Get AXI bus I/F Status
*/
INT32 im_cnr_axi_otf_get_axi_status(ImCnrAxi*self, UCHAR ch, TImCnrOtfAxiStatus* const sts )
{
#ifdef CO_PARAM_CHECK
	if (ch >= (ImCnr_D_IM_CNR_CH_NUM_MAX-1)) {
		Ddim_Assertion(("im_cnr_axi_otf_get_axi_status( ) error. input channel error : %d\n", ch));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( sts == NULL ) {
		// sts setting error
		Ddim_Assertion(("I:im_cnr_axi_otf_get_axi_status( ) Parameter is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnr_on_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	sts->writeChannelResponse = ImCnr_IO_CNR(ch)->OTF_REG_RW.SPRAXISET.bit.WRESP;

	im_cnr_off_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	return D_DDIM_OK;
}

/*
Set SPR setting for CbCr
*/
INT32 im_cnr_axi_ofl_ctrl_c(ImCnrAxi*self, UCHAR ch, const TImCnrCtrlC* const spr_ctrl_c )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_axi_ofl_ctrl_c() error. input channel error : %d\n", ch));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_ctrl_c == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_axi_ofl_ctrl_c() Parameter is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnr_on_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.csprEn.bit.csprEn = spr_ctrl_c->enable;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cgdkEn.bit.cgdkEn = spr_ctrl_c->gradationKeepEn;

	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcEn.bit.mcEn = spr_ctrl_c->midFreqNr.enable;

	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcYthh.bit.MCYTHH_0 = spr_ctrl_c->midFreqNr.hYThreshold[0];
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcYthh.bit.MCYTHH_1 = spr_ctrl_c->midFreqNr.hYThreshold[1];
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcYthh.bit.MCYTHH_2 = spr_ctrl_c->midFreqNr.hYThreshold[2];
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcYthh.bit.MCYTHH_3 = spr_ctrl_c->midFreqNr.hYThreshold[3];

	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcYthv.bit.MCYTHV_0 = spr_ctrl_c->midFreqNr.vYThreshold[0];
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcYthv.bit.MCYTHV_1 = spr_ctrl_c->midFreqNr.vYThreshold[1];
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcYthv.bit.MCYTHV_2 = spr_ctrl_c->midFreqNr.vYThreshold[2];
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcYthv.bit.MCYTHV_3 = spr_ctrl_c->midFreqNr.vYThreshold[3];

	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcCthh.bit.MCCTHH_0 = spr_ctrl_c->midFreqNr.hCThreshold[0];
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcCthh.bit.MCCTHH_1 = spr_ctrl_c->midFreqNr.hCThreshold[1];
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcCthh.bit.MCCTHH_2 = spr_ctrl_c->midFreqNr.hCThreshold[2];
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcCthh.bit.MCCTHH_3 = spr_ctrl_c->midFreqNr.hCThreshold[3];

	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcCthv.bit.MCCTHV_0 = spr_ctrl_c->midFreqNr.vCThreshold[0];
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcCthv.bit.MCCTHV_1 = spr_ctrl_c->midFreqNr.vCThreshold[1];
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcCthv.bit.MCCTHV_2 = spr_ctrl_c->midFreqNr.vCThreshold[2];
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcCthv.bit.MCCTHV_3 = spr_ctrl_c->midFreqNr.vCThreshold[3];

	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcYdymDt.bit.MCYDYMYCR = spr_ctrl_c->midFreqNr.yThresholdCor;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcYdymDt.bit.MCYDYMYG = spr_ctrl_c->midFreqNr.yThresholdGain;

	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcYdym.bit.mcYdym = spr_ctrl_c->midFreqNr.yThresholdDymEn;

	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcYscl.bit.mcYscl = spr_ctrl_c->midFreqNr.yThresholdSclEn;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcSscl.bit.mcSscl = spr_ctrl_c->midFreqNr.cYThresholdSclEn;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcCscl.bit.mcCscl = spr_ctrl_c->midFreqNr.cThresholdSclEn;

	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcEn.bit.lcEn = spr_ctrl_c->lowFreqNr.enable;

	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcYthh.bit.LCYTHH_0 = spr_ctrl_c->lowFreqNr.hYThreshold[0];
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcYthh.bit.LCYTHH_1 = spr_ctrl_c->lowFreqNr.hYThreshold[1];
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcYthh.bit.LCYTHH_2 = spr_ctrl_c->lowFreqNr.hYThreshold[2];
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcYthh.bit.LCYTHH_3 = spr_ctrl_c->lowFreqNr.hYThreshold[3];

	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcYthv.bit.LCYTHV_0 = spr_ctrl_c->lowFreqNr.vYThreshold[0];
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcYthv.bit.LCYTHV_1 = spr_ctrl_c->lowFreqNr.vYThreshold[1];
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcYthv.bit.LCYTHV_2 = spr_ctrl_c->lowFreqNr.vYThreshold[2];
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcYthv.bit.LCYTHV_3 = spr_ctrl_c->lowFreqNr.vYThreshold[3];

	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcCthh.bit.LCCTHH_0 = spr_ctrl_c->lowFreqNr.hCThreshold[0];
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcCthh.bit.LCCTHH_1 = spr_ctrl_c->lowFreqNr.hCThreshold[1];
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcCthh.bit.LCCTHH_2 = spr_ctrl_c->lowFreqNr.hCThreshold[2];
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcCthh.bit.LCCTHH_3 = spr_ctrl_c->lowFreqNr.hCThreshold[3];

	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcCthv.bit.LCCTHV_0 = spr_ctrl_c->lowFreqNr.vCThreshold[0];
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcCthv.bit.LCCTHV_1 = spr_ctrl_c->lowFreqNr.vCThreshold[1];
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcCthv.bit.LCCTHV_2 = spr_ctrl_c->lowFreqNr.vCThreshold[2];
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcCthv.bit.LCCTHV_3 = spr_ctrl_c->lowFreqNr.vCThreshold[3];

	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcYdymDt.bit.LCYDYMYCR = spr_ctrl_c->lowFreqNr.yThresholdCor;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcYdymDt.bit.LCYDYMYG = spr_ctrl_c->lowFreqNr.yThresholdGain;

	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcYdym.bit.lcYdym = spr_ctrl_c->lowFreqNr.yThresholdDymEn;

	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcYscl.bit.lcYscl = spr_ctrl_c->lowFreqNr.yThresholdSclEn;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcSscl.bit.lcSscl = spr_ctrl_c->lowFreqNr.cYThresholdSclEn;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcCscl.bit.lcCscl = spr_ctrl_c->lowFreqNr.cThresholdSclEn;

	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.whTmd.bit.WHTEN = spr_ctrl_c->whiteningEnable;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.whTmd.bit.WHTVAL = spr_ctrl_c->whiteningValue;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.whTmd.bit.WHTBASE = spr_ctrl_c->whiteningBase;

	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.blEnd.bit.BLENDMD = spr_ctrl_c->cBlendMd;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.blEnd.bit.CSPRALPBD = spr_ctrl_c->cAlphaBlend;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.blEnd.bit.CSRGEN = spr_ctrl_c->cRange;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.blEnd.bit.CSRGMD = spr_ctrl_c->cRangeMode;

	im_cnr_off_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	return D_DDIM_OK;
}

/*
Set SPR setting for CbCr
*/
INT32 im_cnr_axi_otf_ctrl_c(ImCnrAxi*self, UCHAR ch, const TImCnrCtrlC* const spr_ctrl_c )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_axi_otf_ctrl_c() error. input channel error : %d\n", ch));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_ctrl_c == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_axi_otf_ctrl_c() Parameter is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnr_on_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.csprEn.bit.csprEn = spr_ctrl_c->enable;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cgdkEn.bit.cgdkEn = spr_ctrl_c->gradationKeepEn;

	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcEn.bit.mcEn = spr_ctrl_c->midFreqNr.enable;

	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcYthh.bit.MCYTHH_0 = spr_ctrl_c->midFreqNr.hYThreshold[0];
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcYthh.bit.MCYTHH_1 = spr_ctrl_c->midFreqNr.hYThreshold[1];
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcYthh.bit.MCYTHH_2 = spr_ctrl_c->midFreqNr.hYThreshold[2];
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcYthh.bit.MCYTHH_3 = spr_ctrl_c->midFreqNr.hYThreshold[3];

	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcYthv.bit.MCYTHV_0 = spr_ctrl_c->midFreqNr.vYThreshold[0];
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcYthv.bit.MCYTHV_1 = spr_ctrl_c->midFreqNr.vYThreshold[1];
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcYthv.bit.MCYTHV_2 = spr_ctrl_c->midFreqNr.vYThreshold[2];
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcYthv.bit.MCYTHV_3 = spr_ctrl_c->midFreqNr.vYThreshold[3];

	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcCthh.bit.MCCTHH_0 = spr_ctrl_c->midFreqNr.hCThreshold[0];
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcCthh.bit.MCCTHH_1 = spr_ctrl_c->midFreqNr.hCThreshold[1];
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcCthh.bit.MCCTHH_2 = spr_ctrl_c->midFreqNr.hCThreshold[2];
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcCthh.bit.MCCTHH_3 = spr_ctrl_c->midFreqNr.hCThreshold[3];

	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcCthv.bit.MCCTHV_0 = spr_ctrl_c->midFreqNr.vCThreshold[0];
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcCthv.bit.MCCTHV_1 = spr_ctrl_c->midFreqNr.vCThreshold[1];
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcCthv.bit.MCCTHV_2 = spr_ctrl_c->midFreqNr.vCThreshold[2];
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcCthv.bit.MCCTHV_3 = spr_ctrl_c->midFreqNr.vCThreshold[3];

	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcYdymDt.bit.MCYDYMYCR = spr_ctrl_c->midFreqNr.yThresholdCor;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcYdymDt.bit.MCYDYMYG = spr_ctrl_c->midFreqNr.yThresholdGain;

	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcYdym.bit.mcYdym = spr_ctrl_c->midFreqNr.yThresholdDymEn;

	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcYscl.bit.mcYscl = spr_ctrl_c->midFreqNr.yThresholdSclEn;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcSscl.bit.mcSscl = spr_ctrl_c->midFreqNr.cYThresholdSclEn;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcCscl.bit.mcCscl = spr_ctrl_c->midFreqNr.cThresholdSclEn;

	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcEn.bit.lcEn = spr_ctrl_c->lowFreqNr.enable;

	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcYthh.bit.LCYTHH_0 = spr_ctrl_c->lowFreqNr.hYThreshold[0];
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcYthh.bit.LCYTHH_1 = spr_ctrl_c->lowFreqNr.hYThreshold[1];
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcYthh.bit.LCYTHH_2 = spr_ctrl_c->lowFreqNr.hYThreshold[2];
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcYthh.bit.LCYTHH_3 = spr_ctrl_c->lowFreqNr.hYThreshold[3];

	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcYthv.bit.LCYTHV_0 = spr_ctrl_c->lowFreqNr.vYThreshold[0];
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcYthv.bit.LCYTHV_1 = spr_ctrl_c->lowFreqNr.vYThreshold[1];
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcYthv.bit.LCYTHV_2 = spr_ctrl_c->lowFreqNr.vYThreshold[2];
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcYthv.bit.LCYTHV_3 = spr_ctrl_c->lowFreqNr.vYThreshold[3];

	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcCthh.bit.LCCTHH_0 = spr_ctrl_c->lowFreqNr.hCThreshold[0];
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcCthh.bit.LCCTHH_1 = spr_ctrl_c->lowFreqNr.hCThreshold[1];
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcCthh.bit.LCCTHH_2 = spr_ctrl_c->lowFreqNr.hCThreshold[2];
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcCthh.bit.LCCTHH_3 = spr_ctrl_c->lowFreqNr.hCThreshold[3];

	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcCthv.bit.LCCTHV_0 = spr_ctrl_c->lowFreqNr.vCThreshold[0];
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcCthv.bit.LCCTHV_1 = spr_ctrl_c->lowFreqNr.vCThreshold[1];
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcCthv.bit.LCCTHV_2 = spr_ctrl_c->lowFreqNr.vCThreshold[2];
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcCthv.bit.LCCTHV_3 = spr_ctrl_c->lowFreqNr.vCThreshold[3];

	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcYdymDt.bit.LCYDYMYCR = spr_ctrl_c->lowFreqNr.yThresholdCor;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcYdymDt.bit.LCYDYMYG = spr_ctrl_c->lowFreqNr.yThresholdGain;

	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcYdym.bit.lcYdym = spr_ctrl_c->lowFreqNr.yThresholdDymEn;

	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcYscl.bit.lcYscl = spr_ctrl_c->lowFreqNr.yThresholdSclEn;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcCscl.bit.lcCscl = spr_ctrl_c->lowFreqNr.cThresholdSclEn;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcCscl.bit.lcCscl = spr_ctrl_c->lowFreqNr.cThresholdSclEn;

	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.whTmd.bit.WHTEN = spr_ctrl_c->whiteningEnable;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.whTmd.bit.WHTVAL = spr_ctrl_c->whiteningValue;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.whTmd.bit.WHTBASE = spr_ctrl_c->whiteningBase;

	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.blEnd.bit.BLENDMD = spr_ctrl_c->cBlendMd;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.blEnd.bit.CSPRALPBD = spr_ctrl_c->cAlphaBlend;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.blEnd.bit.CSRGEN = spr_ctrl_c->cRange;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.blEnd.bit.CSRGMD = spr_ctrl_c->cRangeMode;

	im_cnr_off_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	return D_DDIM_OK;
}

/*
Set SPR setting for Y for Off Line
*/
INT32 im_cnr_axi_ofl_ctrl_y(ImCnrAxi*self, UCHAR ch, const TImCnrOflCtrlY* const spr_ctrl_y )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_axi_ofl_ctrl_y() error. input channel error : %d\n", ch));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_ctrl_y == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_axi_ofl_ctrl_y() Parameter is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnr_on_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	ImCnr_IO_CNR(ch)->OFL_REG_YSPR.ysprEn.bit.ysprEn = spr_ctrl_y->enable;
	ImCnr_IO_CNR(ch)->OFL_REG_YSPR.ysprMode.bit.YSPRMD = spr_ctrl_y->thresholdType;
	ImCnr_IO_CNR(ch)->OFL_REG_YSPR.ysprMode.bit.YSPRFE = spr_ctrl_y->level;

	ImCnr_IO_CNR(ch)->OFL_REG_YSPR.ysprFxey.bit.YSPRFXEYV = spr_ctrl_y->vYThreshold;
	ImCnr_IO_CNR(ch)->OFL_REG_YSPR.ysprFxey.bit.YSPRFXEYH = spr_ctrl_y->hYThreshold;
	ImCnr_IO_CNR(ch)->OFL_REG_YSPR.ysprFxec.bit.YSPRFXECV = spr_ctrl_y->vCThreshold;
	ImCnr_IO_CNR(ch)->OFL_REG_YSPR.ysprFxec.bit.YSPRFXECH = spr_ctrl_y->hCThreshold;
	ImCnr_IO_CNR(ch)->OFL_REG_YSPR.ysprAlpbd.bit.ysprAlpbd = spr_ctrl_y->alphaBlendRatio;

	im_cnr_off_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	return D_DDIM_OK;
}

/*
Set CbCr setting of source
*/
INT32 im_cnr_axi_ofl_ctrl_sprs_cc(ImCnrAxi*self, UCHAR ch, const TImCnrCtrlCcSrcDst* const sprs_ctrl )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_axi_ofl_ctrl_sprs_cc() error. input channel error : %d\n", ch));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( sprs_ctrl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_axi_ofl_ctrl_sprs_cc() Parameter is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnr_on_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprs.bit.sprs = sprs_ctrl->enable;

	// write signed data
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprsCbbd.SPRSCBBD1, union io_cnr_cspr_reg_sprscbbd_1, sprsCbbd1, sprs_ctrl->cbTable.bd1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprsCbbd.SPRSCBBD1, union io_cnr_cspr_reg_sprscbbd_1, sprsCbbd2, sprs_ctrl->cbTable.bd2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprsCbbd.SPRSCBBD1, union io_cnr_cspr_reg_sprscbbd_1, SPRSCBBD_3, sprs_ctrl->cbTable.bd3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprsCbbd.SPRSCBBD1, union io_cnr_cspr_reg_sprscbbd_1, SPRSCBBD_4, sprs_ctrl->cbTable.bd4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprsCbbd.SPRSCBBD2, union io_cnr_cspr_reg_sprscbbd_2, SPRSCBBD_5, sprs_ctrl->cbTable.bd5 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprsCbof.SPRSCBOF1, union io_cnr_cspr_reg_sprscbof_1, SPRSCBOF_0, sprs_ctrl->cbTable.of0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprsCbof.SPRSCBOF1, union io_cnr_cspr_reg_sprscbof_1, sprsCbof1, sprs_ctrl->cbTable.of1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprsCbof.SPRSCBOF1, union io_cnr_cspr_reg_sprscbof_1, sprsCbof2, sprs_ctrl->cbTable.of2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprsCbof.SPRSCBOF1, union io_cnr_cspr_reg_sprscbof_1, SPRSCBOF_3, sprs_ctrl->cbTable.of3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprsCbof.SPRSCBOF2, union io_cnr_cspr_reg_sprscbof_2, SPRSCBOF_4, sprs_ctrl->cbTable.of4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprsCbof.SPRSCBOF2, union io_cnr_cspr_reg_sprscbof_2, SPRSCBOF_5, sprs_ctrl->cbTable.of5 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprsCbga.SPRSCBGA1, union io_cnr_cspr_reg_sprscbga_1, SPRSCBGA_0, sprs_ctrl->cbTable.gain0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprsCbga.SPRSCBGA1, union io_cnr_cspr_reg_sprscbga_1, sprsCbga1, sprs_ctrl->cbTable.gain1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprsCbga.SPRSCBGA2, union io_cnr_cspr_reg_sprscbga_2, sprsCbga2, sprs_ctrl->cbTable.gain2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprsCbga.SPRSCBGA2, union io_cnr_cspr_reg_sprscbga_2, sprsCbga3, sprs_ctrl->cbTable.gain3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprsCbga.SPRSCBGA3, union io_cnr_cspr_reg_sprscbga_3, SPRSCBGA_4, sprs_ctrl->cbTable.gain4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprsCbga.SPRSCBGA3, union io_cnr_cspr_reg_sprscbga_3, SPRSCBGA_5, sprs_ctrl->cbTable.gain5 );

	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprsCrbd.SPRSCRBD1, union io_cnr_cspr_reg_sprscrbd_1, sprsCrbd1, sprs_ctrl->crTable.bd1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprsCrbd.SPRSCRBD1, union io_cnr_cspr_reg_sprscrbd_1, sprsCrbd2, sprs_ctrl->crTable.bd2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprsCrbd.SPRSCRBD1, union io_cnr_cspr_reg_sprscrbd_1, SPRSCRBD_3, sprs_ctrl->crTable.bd3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprsCrbd.SPRSCRBD1, union io_cnr_cspr_reg_sprscrbd_1, SPRSCRBD_4, sprs_ctrl->crTable.bd4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprsCrbd.SPRSCRBD2, union io_cnr_cspr_reg_sprscrbd_2, SPRSCRBD_5, sprs_ctrl->crTable.bd5 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprsCrof.SPRSCROF1, union io_cnr_cspr_reg_sprscrof_1, SPRSCROF_0, sprs_ctrl->crTable.of0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprsCrof.SPRSCROF1, union io_cnr_cspr_reg_sprscrof_1, sprsCrof1, sprs_ctrl->crTable.of1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprsCrof.SPRSCROF1, union io_cnr_cspr_reg_sprscrof_1, sprsCrof2, sprs_ctrl->crTable.of2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprsCrof.SPRSCROF1, union io_cnr_cspr_reg_sprscrof_1, SPRSCROF_3, sprs_ctrl->crTable.of3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprsCrof.SPRSCROF2, union io_cnr_cspr_reg_sprscrof_2, SPRSCROF_4, sprs_ctrl->crTable.of4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprsCrof.SPRSCROF2, union io_cnr_cspr_reg_sprscrof_2, SPRSCROF_5, sprs_ctrl->crTable.of5 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprsCrga.SPRSCRGA1, union io_cnr_cspr_reg_sprscrga_1, SPRSCRGA_0, sprs_ctrl->crTable.gain0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprsCrga.SPRSCRGA1, union io_cnr_cspr_reg_sprscrga_1, sprsCrga1, sprs_ctrl->crTable.gain1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprsCrga.SPRSCRGA2, union io_cnr_cspr_reg_sprscrga_2, sprsCrga2, sprs_ctrl->crTable.gain2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprsCrga.SPRSCRGA2, union io_cnr_cspr_reg_sprscrga_2, sprsCrga3, sprs_ctrl->crTable.gain3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprsCrga.SPRSCRGA3, union io_cnr_cspr_reg_sprscrga_3, SPRSCRGA_4, sprs_ctrl->crTable.gain4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprsCrga.SPRSCRGA3, union io_cnr_cspr_reg_sprscrga_3, SPRSCRGA_5, sprs_ctrl->crTable.gain5 );

	im_cnr_off_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	return D_DDIM_OK;
}

/*
Set CbCr setting of source
*/
INT32 im_cnr_axi_otf_ctrl_sprs_cc(ImCnrAxi*self, UCHAR ch, const TImCnrCtrlCcSrcDst* const sprs_ctrl )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_axi_otf_ctrl_sprs_cc() error. input channel error : %d\n", ch));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( sprs_ctrl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_axi_otf_ctrl_sprs_cc() Parameter is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnr_on_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprs.bit.sprs = sprs_ctrl->enable;

	// write signed data
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprsCbbd.SPRSCBBD1, union io_cnr_cspr_reg_sprscbbd_1, sprsCbbd1, sprs_ctrl->cbTable.bd1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprsCbbd.SPRSCBBD1, union io_cnr_cspr_reg_sprscbbd_1, sprsCbbd2, sprs_ctrl->cbTable.bd2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprsCbbd.SPRSCBBD1, union io_cnr_cspr_reg_sprscbbd_1, SPRSCBBD_3, sprs_ctrl->cbTable.bd3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprsCbbd.SPRSCBBD1, union io_cnr_cspr_reg_sprscbbd_1, SPRSCBBD_4, sprs_ctrl->cbTable.bd4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprsCbbd.SPRSCBBD2, union io_cnr_cspr_reg_sprscbbd_2, SPRSCBBD_5, sprs_ctrl->cbTable.bd5 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprsCbof.SPRSCBOF1, union io_cnr_cspr_reg_sprscbof_1, SPRSCBOF_0, sprs_ctrl->cbTable.of0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprsCbof.SPRSCBOF1, union io_cnr_cspr_reg_sprscbof_1, sprsCbof1, sprs_ctrl->cbTable.of1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprsCbof.SPRSCBOF1, union io_cnr_cspr_reg_sprscbof_1, sprsCbof2, sprs_ctrl->cbTable.of2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprsCbof.SPRSCBOF1, union io_cnr_cspr_reg_sprscbof_1, SPRSCBOF_3, sprs_ctrl->cbTable.of3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprsCbof.SPRSCBOF2, union io_cnr_cspr_reg_sprscbof_2, SPRSCBOF_4, sprs_ctrl->cbTable.of4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprsCbof.SPRSCBOF2, union io_cnr_cspr_reg_sprscbof_2, SPRSCBOF_5, sprs_ctrl->cbTable.of5 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprsCbga.SPRSCBGA1, union io_cnr_cspr_reg_sprscbga_1, SPRSCBGA_0, sprs_ctrl->cbTable.gain0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprsCbga.SPRSCBGA1, union io_cnr_cspr_reg_sprscbga_1, sprsCbga1, sprs_ctrl->cbTable.gain1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprsCbga.SPRSCBGA2, union io_cnr_cspr_reg_sprscbga_2, sprsCbga2, sprs_ctrl->cbTable.gain2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprsCbga.SPRSCBGA2, union io_cnr_cspr_reg_sprscbga_2, sprsCbga3, sprs_ctrl->cbTable.gain3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprsCbga.SPRSCBGA3, union io_cnr_cspr_reg_sprscbga_3, SPRSCBGA_4, sprs_ctrl->cbTable.gain4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprsCbga.SPRSCBGA3, union io_cnr_cspr_reg_sprscbga_3, SPRSCBGA_5, sprs_ctrl->cbTable.gain5 );

	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprsCrbd.SPRSCRBD1, union io_cnr_cspr_reg_sprscrbd_1, sprsCrbd1, sprs_ctrl->crTable.bd1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprsCrbd.SPRSCRBD1, union io_cnr_cspr_reg_sprscrbd_1, sprsCrbd2, sprs_ctrl->crTable.bd2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprsCrbd.SPRSCRBD1, union io_cnr_cspr_reg_sprscrbd_1, SPRSCRBD_3, sprs_ctrl->crTable.bd3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprsCrbd.SPRSCRBD1, union io_cnr_cspr_reg_sprscrbd_1, SPRSCRBD_4, sprs_ctrl->crTable.bd4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprsCrbd.SPRSCRBD2, union io_cnr_cspr_reg_sprscrbd_2, SPRSCRBD_5, sprs_ctrl->crTable.bd5 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprsCrof.SPRSCROF1, union io_cnr_cspr_reg_sprscrof_1, SPRSCROF_0, sprs_ctrl->crTable.of0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprsCrof.SPRSCROF1, union io_cnr_cspr_reg_sprscrof_1, sprsCrof1, sprs_ctrl->crTable.of1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprsCrof.SPRSCROF1, union io_cnr_cspr_reg_sprscrof_1, sprsCrof2, sprs_ctrl->crTable.of2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprsCrof.SPRSCROF1, union io_cnr_cspr_reg_sprscrof_1, SPRSCROF_3, sprs_ctrl->crTable.of3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprsCrof.SPRSCROF2, union io_cnr_cspr_reg_sprscrof_2, SPRSCROF_4, sprs_ctrl->crTable.of4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprsCrof.SPRSCROF2, union io_cnr_cspr_reg_sprscrof_2, SPRSCROF_5, sprs_ctrl->crTable.of5 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprsCrga.SPRSCRGA1, union io_cnr_cspr_reg_sprscrga_1, SPRSCRGA_0, sprs_ctrl->crTable.gain0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprsCrga.SPRSCRGA1, union io_cnr_cspr_reg_sprscrga_1, sprsCrga1, sprs_ctrl->crTable.gain1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprsCrga.SPRSCRGA2, union io_cnr_cspr_reg_sprscrga_2, sprsCrga2, sprs_ctrl->crTable.gain2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprsCrga.SPRSCRGA2, union io_cnr_cspr_reg_sprscrga_2, sprsCrga3, sprs_ctrl->crTable.gain3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprsCrga.SPRSCRGA3, union io_cnr_cspr_reg_sprscrga_3, SPRSCRGA_4, sprs_ctrl->crTable.gain4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprsCrga.SPRSCRGA3, union io_cnr_cspr_reg_sprscrga_3, SPRSCRGA_5, sprs_ctrl->crTable.gain5 );

	im_cnr_off_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	return D_DDIM_OK;
}

/*
Set CbCr setting of destination
*/
INT32 im_cnr_axi_ofl_ctrl_sprd_cc(ImCnrAxi*self, UCHAR ch, const TImCnrCtrlCcSrcDst* const sprd_ctrl )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_axi_ofl_ctrl_sprd_cc() error. input channel error : %d\n", ch));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( sprd_ctrl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_axi_ofl_ctrl_sprd_cc() Parameter is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnr_on_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprd.bit.sprd = sprd_ctrl->enable;

	// write signed data
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprdCbbd.SPRDCBBD1, union io_cnr_cspr_reg_sprdcbbd_1, sprdCbbd1, sprd_ctrl->cbTable.bd1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprdCbbd.SPRDCBBD1, union io_cnr_cspr_reg_sprdcbbd_1, sprdCbbd2, sprd_ctrl->cbTable.bd2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprdCbbd.SPRDCBBD1, union io_cnr_cspr_reg_sprdcbbd_1, SPRDCBBD_3, sprd_ctrl->cbTable.bd3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprdCbbd.SPRDCBBD1, union io_cnr_cspr_reg_sprdcbbd_1, SPRDCBBD_4, sprd_ctrl->cbTable.bd4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprdCbbd.SPRDCBBD2, union io_cnr_cspr_reg_sprdcbbd_2, SPRDCBBD_5, sprd_ctrl->cbTable.bd5 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprdCbof.SPRDCBOF1, union io_cnr_cspr_reg_sprdcbof_1, SPRDCBOF_0, sprd_ctrl->cbTable.of0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprdCbof.SPRDCBOF1, union io_cnr_cspr_reg_sprdcbof_1, sprdCbof1, sprd_ctrl->cbTable.of1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprdCbof.SPRDCBOF1, union io_cnr_cspr_reg_sprdcbof_1, sprdCbof2, sprd_ctrl->cbTable.of2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprdCbof.SPRDCBOF1, union io_cnr_cspr_reg_sprdcbof_1, SPRDCBOF_3, sprd_ctrl->cbTable.of3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprdCbof.SPRDCBOF2, union io_cnr_cspr_reg_sprdcbof_2, SPRDCBOF_4, sprd_ctrl->cbTable.of4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprdCbof.SPRDCBOF2, union io_cnr_cspr_reg_sprdcbof_2, SPRDCBOF_5, sprd_ctrl->cbTable.of5 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprdCbga.SPRDCBGA1, union io_cnr_cspr_reg_sprdcbga_1, SPRDCBGA_0, sprd_ctrl->cbTable.gain0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprdCbga.SPRDCBGA1, union io_cnr_cspr_reg_sprdcbga_1, sprdCbga1, sprd_ctrl->cbTable.gain1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprdCbga.SPRDCBGA2, union io_cnr_cspr_reg_sprdcbga_2, sprdCbga2, sprd_ctrl->cbTable.gain2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprdCbga.SPRDCBGA2, union io_cnr_cspr_reg_sprdcbga_2, sprdCbga3, sprd_ctrl->cbTable.gain3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprdCbga.SPRDCBGA3, union io_cnr_cspr_reg_sprdcbga_3, SPRDCBGA_4, sprd_ctrl->cbTable.gain4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprdCbga.SPRDCBGA3, union io_cnr_cspr_reg_sprdcbga_3, SPRDCBGA_5, sprd_ctrl->cbTable.gain5 );

	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprdCrbd.SPRDCRBD1, union io_cnr_cspr_reg_sprdcrbd_1, sprdCrbd1, sprd_ctrl->crTable.bd1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprdCrbd.SPRDCRBD1, union io_cnr_cspr_reg_sprdcrbd_1, sprdCrbd2, sprd_ctrl->crTable.bd2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprdCrbd.SPRDCRBD1, union io_cnr_cspr_reg_sprdcrbd_1, SPRDCRBD_3, sprd_ctrl->crTable.bd3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprdCrbd.SPRDCRBD1, union io_cnr_cspr_reg_sprdcrbd_1, SPRDCRBD_4, sprd_ctrl->crTable.bd4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprdCrbd.SPRDCRBD2, union io_cnr_cspr_reg_sprdcrbd_2, SPRDCRBD_5, sprd_ctrl->crTable.bd5 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprdCrof.SPRDCROF1, union io_cnr_cspr_reg_sprdcrof_1, SPRDCROF_0, sprd_ctrl->crTable.of0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprdCrof.SPRDCROF1, union io_cnr_cspr_reg_sprdcrof_1, sprdCrof1, sprd_ctrl->crTable.of1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprdCrof.SPRDCROF1, union io_cnr_cspr_reg_sprdcrof_1, sprdCrof2, sprd_ctrl->crTable.of2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprdCrof.SPRDCROF1, union io_cnr_cspr_reg_sprdcrof_1, SPRDCROF_3, sprd_ctrl->crTable.of3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprdCrof.SPRDCROF2, union io_cnr_cspr_reg_sprdcrof_2, SPRDCROF_4, sprd_ctrl->crTable.of4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprdCrof.SPRDCROF2, union io_cnr_cspr_reg_sprdcrof_2, SPRDCROF_5, sprd_ctrl->crTable.of5 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprdCrga.SPRDCRGA1, union io_cnr_cspr_reg_sprdcrga_1, SPRDCRGA_0, sprd_ctrl->crTable.gain0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprdCrga.SPRDCRGA1, union io_cnr_cspr_reg_sprdcrga_1, sprdCrga1, sprd_ctrl->crTable.gain1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprdCrga.SPRDCRGA2, union io_cnr_cspr_reg_sprdcrga_2, sprdCrga2, sprd_ctrl->crTable.gain2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprdCrga.SPRDCRGA2, union io_cnr_cspr_reg_sprdcrga_2, sprdCrga3, sprd_ctrl->crTable.gain3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprdCrga.SPRDCRGA3, union io_cnr_cspr_reg_sprdcrga_3, SPRDCRGA_4, sprd_ctrl->crTable.gain4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.sprdCrga.SPRDCRGA3, union io_cnr_cspr_reg_sprdcrga_3, SPRDCRGA_5, sprd_ctrl->crTable.gain5 );

	im_cnr_off_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	return D_DDIM_OK;
}

/*
Set CbCr setting of destination
*/
INT32 im_cnr_axi_otf_ctrl_sprd_cc(ImCnrAxi*self, UCHAR ch, const TImCnrCtrlCcSrcDst* const sprd_ctrl )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_axi_otf_ctrl_sprd_cc() error. input channel error : %d\n", ch));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( sprd_ctrl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_axi_otf_ctrl_sprd_cc() Parameter is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnr_on_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprd.bit.sprd = sprd_ctrl->enable;

	// write signed data
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprdCbbd.SPRDCBBD1, union io_cnr_cspr_reg_sprdcbbd_1, sprdCbbd1, sprd_ctrl->cbTable.bd1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprdCbbd.SPRDCBBD1, union io_cnr_cspr_reg_sprdcbbd_1, sprdCbbd2, sprd_ctrl->cbTable.bd2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprdCbbd.SPRDCBBD1, union io_cnr_cspr_reg_sprdcbbd_1, SPRDCBBD_3, sprd_ctrl->cbTable.bd3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprdCbbd.SPRDCBBD1, union io_cnr_cspr_reg_sprdcbbd_1, SPRDCBBD_4, sprd_ctrl->cbTable.bd4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprdCbbd.SPRDCBBD2, union io_cnr_cspr_reg_sprdcbbd_2, SPRDCBBD_5, sprd_ctrl->cbTable.bd5 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprdCbof.SPRDCBOF1, union io_cnr_cspr_reg_sprdcbof_1, SPRDCBOF_0, sprd_ctrl->cbTable.of0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprdCbof.SPRDCBOF1, union io_cnr_cspr_reg_sprdcbof_1, sprdCbof1, sprd_ctrl->cbTable.of1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprdCbof.SPRDCBOF1, union io_cnr_cspr_reg_sprdcbof_1, sprdCbof2, sprd_ctrl->cbTable.of2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprdCbof.SPRDCBOF1, union io_cnr_cspr_reg_sprdcbof_1, SPRDCBOF_3, sprd_ctrl->cbTable.of3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprdCbof.SPRDCBOF2, union io_cnr_cspr_reg_sprdcbof_2, SPRDCBOF_4, sprd_ctrl->cbTable.of4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprdCbof.SPRDCBOF2, union io_cnr_cspr_reg_sprdcbof_2, SPRDCBOF_5, sprd_ctrl->cbTable.of5 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprdCbga.SPRDCBGA1, union io_cnr_cspr_reg_sprdcbga_1, SPRDCBGA_0, sprd_ctrl->cbTable.gain0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprdCbga.SPRDCBGA1, union io_cnr_cspr_reg_sprdcbga_1, sprdCbga1, sprd_ctrl->cbTable.gain1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprdCbga.SPRDCBGA2, union io_cnr_cspr_reg_sprdcbga_2, sprdCbga2, sprd_ctrl->cbTable.gain2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprdCbga.SPRDCBGA2, union io_cnr_cspr_reg_sprdcbga_2, sprdCbga3, sprd_ctrl->cbTable.gain3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprdCbga.SPRDCBGA3, union io_cnr_cspr_reg_sprdcbga_3, SPRDCBGA_4, sprd_ctrl->cbTable.gain4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprdCbga.SPRDCBGA3, union io_cnr_cspr_reg_sprdcbga_3, SPRDCBGA_5, sprd_ctrl->cbTable.gain5 );

	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprdCrbd.SPRDCRBD1, union io_cnr_cspr_reg_sprdcrbd_1, sprdCrbd1, sprd_ctrl->crTable.bd1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprdCrbd.SPRDCRBD1, union io_cnr_cspr_reg_sprdcrbd_1, sprdCrbd2, sprd_ctrl->crTable.bd2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprdCrbd.SPRDCRBD1, union io_cnr_cspr_reg_sprdcrbd_1, SPRDCRBD_3, sprd_ctrl->crTable.bd3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprdCrbd.SPRDCRBD1, union io_cnr_cspr_reg_sprdcrbd_1, SPRDCRBD_4, sprd_ctrl->crTable.bd4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprdCrbd.SPRDCRBD2, union io_cnr_cspr_reg_sprdcrbd_2, SPRDCRBD_5, sprd_ctrl->crTable.bd5 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprdCrof.SPRDCROF1, union io_cnr_cspr_reg_sprdcrof_1, SPRDCROF_0, sprd_ctrl->crTable.of0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprdCrof.SPRDCROF1, union io_cnr_cspr_reg_sprdcrof_1, sprdCrof1, sprd_ctrl->crTable.of1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprdCrof.SPRDCROF1, union io_cnr_cspr_reg_sprdcrof_1, sprdCrof2, sprd_ctrl->crTable.of2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprdCrof.SPRDCROF1, union io_cnr_cspr_reg_sprdcrof_1, SPRDCROF_3, sprd_ctrl->crTable.of3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprdCrof.SPRDCROF2, union io_cnr_cspr_reg_sprdcrof_2, SPRDCROF_4, sprd_ctrl->crTable.of4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprdCrof.SPRDCROF2, union io_cnr_cspr_reg_sprdcrof_2, SPRDCROF_5, sprd_ctrl->crTable.of5 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprdCrga.SPRDCRGA1, union io_cnr_cspr_reg_sprdcrga_1, SPRDCRGA_0, sprd_ctrl->crTable.gain0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprdCrga.SPRDCRGA1, union io_cnr_cspr_reg_sprdcrga_1, sprdCrga1, sprd_ctrl->crTable.gain1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprdCrga.SPRDCRGA2, union io_cnr_cspr_reg_sprdcrga_2, sprdCrga2, sprd_ctrl->crTable.gain2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprdCrga.SPRDCRGA2, union io_cnr_cspr_reg_sprdcrga_2, sprdCrga3, sprd_ctrl->crTable.gain3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprdCrga.SPRDCRGA3, union io_cnr_cspr_reg_sprdcrga_3, SPRDCRGA_4, sprd_ctrl->crTable.gain4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.sprdCrga.SPRDCRGA3, union io_cnr_cspr_reg_sprdcrga_3, SPRDCRGA_5, sprd_ctrl->crTable.gain5 );

	im_cnr_off_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	return D_DDIM_OK;
}

ImCnrAxi *im_cnr_axi_new(void)
{
	ImCnrAxi* self = k_object_new_with_private(IM_TYPE_CNR_AXI,sizeof(ImCnrAxiPrivate));
	return self;
}
