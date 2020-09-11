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
INT32 im_cnr_axi_ofl_ctrl_axi(ImCnrAxi*self, UCHAR ch, const T_IM_CNR_OFL_AXI* const axi_ctrl )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_axi_ofl_ctrl_axi( ) error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( axi_ctrl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_axi_ofl_ctrl_axi( ) Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	Im_CNR_On_Pclk(ch);
	Im_CNR_Dsb();

	IO_CNR(ch)->OFL_REG_RW.SPRAXISET.bit.AWPROT		= axi_ctrl->write_protection_type;
	IO_CNR(ch)->OFL_REG_RW.SPRAXISET.bit.ARPROT		= axi_ctrl->read_protection_type;
	IO_CNR(ch)->OFL_REG_RW.SPRAXISET.bit.AWCACHE	= axi_ctrl->write_cache_type;
	IO_CNR(ch)->OFL_REG_RW.SPRAXISET.bit.ARCACHE	= axi_ctrl->read_cache_type;

	Im_CNR_Off_Pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
CNR(OTF) Control set AXI bus I/F Control
*/
INT32 im_cnr_axi_otf_ctrl_axi(ImCnrAxi*self, UCHAR ch, const T_IM_CNR_OTF_AXI* const axi_ctrl )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_axi_otf_ctrl_axi( ) error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( axi_ctrl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_axi_otf_ctrl_axi( ) Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	Im_CNR_On_Pclk(ch);
	Im_CNR_Dsb();

	IO_CNR(ch)->OTF_REG_RW.SPRAXISET.bit.AWPROT		= axi_ctrl->write_protection_type;
	IO_CNR(ch)->OTF_REG_RW.SPRAXISET.bit.AWCACHE	= axi_ctrl->write_cache_type;

	Im_CNR_Off_Pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
Get AXI bus I/F Status
*/
INT32 im_cnr_axi_ofl_get_axi_status(ImCnrAxi*self, UCHAR ch, T_IM_CNR_OFL_AXI_STATUS* const sts )
{
#ifdef CO_PARAM_CHECK
	if (ch >= (D_IM_CNR_CH_NUM_MAX-1)) {
		Ddim_Assertion(("im_cnr_axi_ofl_get_axi_status( ) error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( sts == NULL ) {
		// sts setting error
		Ddim_Assertion(("I:im_cnr_axi_ofl_get_axi_status( ) Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	Im_CNR_On_Pclk(ch);
	Im_CNR_Dsb();

	sts->read_channel_response = IO_CNR(ch)->OFL_REG_RW.SPRAXISET.bit.RRESP;
	sts->write_channel_response = IO_CNR(ch)->OFL_REG_RW.SPRAXISET.bit.WRESP;

	Im_CNR_Off_Pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
Get AXI bus I/F Status
*/
INT32 im_cnr_axi_otf_get_axi_status(ImCnrAxi*self, UCHAR ch, T_IM_CNR_OTF_AXI_STATUS* const sts )
{
#ifdef CO_PARAM_CHECK
	if (ch >= (D_IM_CNR_CH_NUM_MAX-1)) {
		Ddim_Assertion(("im_cnr_axi_otf_get_axi_status( ) error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( sts == NULL ) {
		// sts setting error
		Ddim_Assertion(("I:im_cnr_axi_otf_get_axi_status( ) Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	Im_CNR_On_Pclk(ch);
	Im_CNR_Dsb();

	sts->write_channel_response = IO_CNR(ch)->OTF_REG_RW.SPRAXISET.bit.WRESP;

	Im_CNR_Off_Pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
Set SPR setting for CbCr
*/
INT32 im_cnr_axi_ofl_ctrl_c(ImCnrAxi*self, UCHAR ch, const T_IM_CNR_CTRL_C* const spr_ctrl_c )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_axi_ofl_ctrl_c() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_ctrl_c == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_axi_ofl_ctrl_c() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	Im_CNR_On_Pclk(ch);
	Im_CNR_Dsb();

	IO_CNR(ch)->OFL_CSPR_REG.CSPREN.bit.CSPREN = spr_ctrl_c->enable;
	IO_CNR(ch)->OFL_CSPR_REG.CGDKEN.bit.CGDKEN = spr_ctrl_c->gradation_keep_en;

	IO_CNR(ch)->OFL_CSPR_REG.MCEN.bit.MCEN = spr_ctrl_c->mid_freq_nr.enable;

	IO_CNR(ch)->OFL_CSPR_REG.MCYTHH.bit.MCYTHH_0 = spr_ctrl_c->mid_freq_nr.h_y_threshold[0];
	IO_CNR(ch)->OFL_CSPR_REG.MCYTHH.bit.MCYTHH_1 = spr_ctrl_c->mid_freq_nr.h_y_threshold[1];
	IO_CNR(ch)->OFL_CSPR_REG.MCYTHH.bit.MCYTHH_2 = spr_ctrl_c->mid_freq_nr.h_y_threshold[2];
	IO_CNR(ch)->OFL_CSPR_REG.MCYTHH.bit.MCYTHH_3 = spr_ctrl_c->mid_freq_nr.h_y_threshold[3];

	IO_CNR(ch)->OFL_CSPR_REG.MCYTHV.bit.MCYTHV_0 = spr_ctrl_c->mid_freq_nr.v_y_threshold[0];
	IO_CNR(ch)->OFL_CSPR_REG.MCYTHV.bit.MCYTHV_1 = spr_ctrl_c->mid_freq_nr.v_y_threshold[1];
	IO_CNR(ch)->OFL_CSPR_REG.MCYTHV.bit.MCYTHV_2 = spr_ctrl_c->mid_freq_nr.v_y_threshold[2];
	IO_CNR(ch)->OFL_CSPR_REG.MCYTHV.bit.MCYTHV_3 = spr_ctrl_c->mid_freq_nr.v_y_threshold[3];

	IO_CNR(ch)->OFL_CSPR_REG.MCCTHH.bit.MCCTHH_0 = spr_ctrl_c->mid_freq_nr.h_c_threshold[0];
	IO_CNR(ch)->OFL_CSPR_REG.MCCTHH.bit.MCCTHH_1 = spr_ctrl_c->mid_freq_nr.h_c_threshold[1];
	IO_CNR(ch)->OFL_CSPR_REG.MCCTHH.bit.MCCTHH_2 = spr_ctrl_c->mid_freq_nr.h_c_threshold[2];
	IO_CNR(ch)->OFL_CSPR_REG.MCCTHH.bit.MCCTHH_3 = spr_ctrl_c->mid_freq_nr.h_c_threshold[3];

	IO_CNR(ch)->OFL_CSPR_REG.MCCTHV.bit.MCCTHV_0 = spr_ctrl_c->mid_freq_nr.v_c_threshold[0];
	IO_CNR(ch)->OFL_CSPR_REG.MCCTHV.bit.MCCTHV_1 = spr_ctrl_c->mid_freq_nr.v_c_threshold[1];
	IO_CNR(ch)->OFL_CSPR_REG.MCCTHV.bit.MCCTHV_2 = spr_ctrl_c->mid_freq_nr.v_c_threshold[2];
	IO_CNR(ch)->OFL_CSPR_REG.MCCTHV.bit.MCCTHV_3 = spr_ctrl_c->mid_freq_nr.v_c_threshold[3];

	IO_CNR(ch)->OFL_CSPR_REG.MCYDYMDT.bit.MCYDYMYCR = spr_ctrl_c->mid_freq_nr.y_threshold_cor;
	IO_CNR(ch)->OFL_CSPR_REG.MCYDYMDT.bit.MCYDYMYG = spr_ctrl_c->mid_freq_nr.y_threshold_gain;

	IO_CNR(ch)->OFL_CSPR_REG.MCYDYM.bit.MCYDYM = spr_ctrl_c->mid_freq_nr.y_threshold_dym_en;

	IO_CNR(ch)->OFL_CSPR_REG.MCYSCL.bit.MCYSCL = spr_ctrl_c->mid_freq_nr.y_threshold_scl_en;
	IO_CNR(ch)->OFL_CSPR_REG.MCSSCL.bit.MCSSCL = spr_ctrl_c->mid_freq_nr.c_y_threshold_scl_en;
	IO_CNR(ch)->OFL_CSPR_REG.MCCSCL.bit.MCCSCL = spr_ctrl_c->mid_freq_nr.c_threshold_scl_en;

	IO_CNR(ch)->OFL_CSPR_REG.LCEN.bit.LCEN = spr_ctrl_c->low_freq_nr.enable;

	IO_CNR(ch)->OFL_CSPR_REG.LCYTHH.bit.LCYTHH_0 = spr_ctrl_c->low_freq_nr.h_y_threshold[0];
	IO_CNR(ch)->OFL_CSPR_REG.LCYTHH.bit.LCYTHH_1 = spr_ctrl_c->low_freq_nr.h_y_threshold[1];
	IO_CNR(ch)->OFL_CSPR_REG.LCYTHH.bit.LCYTHH_2 = spr_ctrl_c->low_freq_nr.h_y_threshold[2];
	IO_CNR(ch)->OFL_CSPR_REG.LCYTHH.bit.LCYTHH_3 = spr_ctrl_c->low_freq_nr.h_y_threshold[3];

	IO_CNR(ch)->OFL_CSPR_REG.LCYTHV.bit.LCYTHV_0 = spr_ctrl_c->low_freq_nr.v_y_threshold[0];
	IO_CNR(ch)->OFL_CSPR_REG.LCYTHV.bit.LCYTHV_1 = spr_ctrl_c->low_freq_nr.v_y_threshold[1];
	IO_CNR(ch)->OFL_CSPR_REG.LCYTHV.bit.LCYTHV_2 = spr_ctrl_c->low_freq_nr.v_y_threshold[2];
	IO_CNR(ch)->OFL_CSPR_REG.LCYTHV.bit.LCYTHV_3 = spr_ctrl_c->low_freq_nr.v_y_threshold[3];

	IO_CNR(ch)->OFL_CSPR_REG.LCCTHH.bit.LCCTHH_0 = spr_ctrl_c->low_freq_nr.h_c_threshold[0];
	IO_CNR(ch)->OFL_CSPR_REG.LCCTHH.bit.LCCTHH_1 = spr_ctrl_c->low_freq_nr.h_c_threshold[1];
	IO_CNR(ch)->OFL_CSPR_REG.LCCTHH.bit.LCCTHH_2 = spr_ctrl_c->low_freq_nr.h_c_threshold[2];
	IO_CNR(ch)->OFL_CSPR_REG.LCCTHH.bit.LCCTHH_3 = spr_ctrl_c->low_freq_nr.h_c_threshold[3];

	IO_CNR(ch)->OFL_CSPR_REG.LCCTHV.bit.LCCTHV_0 = spr_ctrl_c->low_freq_nr.v_c_threshold[0];
	IO_CNR(ch)->OFL_CSPR_REG.LCCTHV.bit.LCCTHV_1 = spr_ctrl_c->low_freq_nr.v_c_threshold[1];
	IO_CNR(ch)->OFL_CSPR_REG.LCCTHV.bit.LCCTHV_2 = spr_ctrl_c->low_freq_nr.v_c_threshold[2];
	IO_CNR(ch)->OFL_CSPR_REG.LCCTHV.bit.LCCTHV_3 = spr_ctrl_c->low_freq_nr.v_c_threshold[3];

	IO_CNR(ch)->OFL_CSPR_REG.LCYDYMDT.bit.LCYDYMYCR = spr_ctrl_c->low_freq_nr.y_threshold_cor;
	IO_CNR(ch)->OFL_CSPR_REG.LCYDYMDT.bit.LCYDYMYG = spr_ctrl_c->low_freq_nr.y_threshold_gain;

	IO_CNR(ch)->OFL_CSPR_REG.LCYDYM.bit.LCYDYM = spr_ctrl_c->low_freq_nr.y_threshold_dym_en;

	IO_CNR(ch)->OFL_CSPR_REG.LCYSCL.bit.LCYSCL = spr_ctrl_c->low_freq_nr.y_threshold_scl_en;
	IO_CNR(ch)->OFL_CSPR_REG.LCSSCL.bit.LCSSCL = spr_ctrl_c->low_freq_nr.c_y_threshold_scl_en;
	IO_CNR(ch)->OFL_CSPR_REG.LCCSCL.bit.LCCSCL = spr_ctrl_c->low_freq_nr.c_threshold_scl_en;

	IO_CNR(ch)->OFL_CSPR_REG.WHTMD.bit.WHTEN = spr_ctrl_c->whitening_enable;
	IO_CNR(ch)->OFL_CSPR_REG.WHTMD.bit.WHTVAL = spr_ctrl_c->whitening_value;
	IO_CNR(ch)->OFL_CSPR_REG.WHTMD.bit.WHTBASE = spr_ctrl_c->whitening_base;

	IO_CNR(ch)->OFL_CSPR_REG.BLEND.bit.BLENDMD = spr_ctrl_c->c_blend_md;
	IO_CNR(ch)->OFL_CSPR_REG.BLEND.bit.CSPRALPBD = spr_ctrl_c->c_alpha_blend;
	IO_CNR(ch)->OFL_CSPR_REG.BLEND.bit.CSRGEN = spr_ctrl_c->c_range;
	IO_CNR(ch)->OFL_CSPR_REG.BLEND.bit.CSRGMD = spr_ctrl_c->c_range_mode;

	Im_CNR_Off_Pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
Set SPR setting for CbCr
*/
INT32 im_cnr_axi_otf_ctrl_c(ImCnrAxi*self, UCHAR ch, const T_IM_CNR_CTRL_C* const spr_ctrl_c )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_axi_otf_ctrl_c() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_ctrl_c == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_axi_otf_ctrl_c() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	Im_CNR_On_Pclk(ch);
	Im_CNR_Dsb();

	IO_CNR(ch)->OTF_CSPR_REG.CSPREN.bit.CSPREN = spr_ctrl_c->enable;
	IO_CNR(ch)->OTF_CSPR_REG.CGDKEN.bit.CGDKEN = spr_ctrl_c->gradation_keep_en;

	IO_CNR(ch)->OTF_CSPR_REG.MCEN.bit.MCEN = spr_ctrl_c->mid_freq_nr.enable;

	IO_CNR(ch)->OTF_CSPR_REG.MCYTHH.bit.MCYTHH_0 = spr_ctrl_c->mid_freq_nr.h_y_threshold[0];
	IO_CNR(ch)->OTF_CSPR_REG.MCYTHH.bit.MCYTHH_1 = spr_ctrl_c->mid_freq_nr.h_y_threshold[1];
	IO_CNR(ch)->OTF_CSPR_REG.MCYTHH.bit.MCYTHH_2 = spr_ctrl_c->mid_freq_nr.h_y_threshold[2];
	IO_CNR(ch)->OTF_CSPR_REG.MCYTHH.bit.MCYTHH_3 = spr_ctrl_c->mid_freq_nr.h_y_threshold[3];

	IO_CNR(ch)->OTF_CSPR_REG.MCYTHV.bit.MCYTHV_0 = spr_ctrl_c->mid_freq_nr.v_y_threshold[0];
	IO_CNR(ch)->OTF_CSPR_REG.MCYTHV.bit.MCYTHV_1 = spr_ctrl_c->mid_freq_nr.v_y_threshold[1];
	IO_CNR(ch)->OTF_CSPR_REG.MCYTHV.bit.MCYTHV_2 = spr_ctrl_c->mid_freq_nr.v_y_threshold[2];
	IO_CNR(ch)->OTF_CSPR_REG.MCYTHV.bit.MCYTHV_3 = spr_ctrl_c->mid_freq_nr.v_y_threshold[3];

	IO_CNR(ch)->OTF_CSPR_REG.MCCTHH.bit.MCCTHH_0 = spr_ctrl_c->mid_freq_nr.h_c_threshold[0];
	IO_CNR(ch)->OTF_CSPR_REG.MCCTHH.bit.MCCTHH_1 = spr_ctrl_c->mid_freq_nr.h_c_threshold[1];
	IO_CNR(ch)->OTF_CSPR_REG.MCCTHH.bit.MCCTHH_2 = spr_ctrl_c->mid_freq_nr.h_c_threshold[2];
	IO_CNR(ch)->OTF_CSPR_REG.MCCTHH.bit.MCCTHH_3 = spr_ctrl_c->mid_freq_nr.h_c_threshold[3];

	IO_CNR(ch)->OTF_CSPR_REG.MCCTHV.bit.MCCTHV_0 = spr_ctrl_c->mid_freq_nr.v_c_threshold[0];
	IO_CNR(ch)->OTF_CSPR_REG.MCCTHV.bit.MCCTHV_1 = spr_ctrl_c->mid_freq_nr.v_c_threshold[1];
	IO_CNR(ch)->OTF_CSPR_REG.MCCTHV.bit.MCCTHV_2 = spr_ctrl_c->mid_freq_nr.v_c_threshold[2];
	IO_CNR(ch)->OTF_CSPR_REG.MCCTHV.bit.MCCTHV_3 = spr_ctrl_c->mid_freq_nr.v_c_threshold[3];

	IO_CNR(ch)->OTF_CSPR_REG.MCYDYMDT.bit.MCYDYMYCR = spr_ctrl_c->mid_freq_nr.y_threshold_cor;
	IO_CNR(ch)->OTF_CSPR_REG.MCYDYMDT.bit.MCYDYMYG = spr_ctrl_c->mid_freq_nr.y_threshold_gain;

	IO_CNR(ch)->OTF_CSPR_REG.MCYDYM.bit.MCYDYM = spr_ctrl_c->mid_freq_nr.y_threshold_dym_en;

	IO_CNR(ch)->OTF_CSPR_REG.MCYSCL.bit.MCYSCL = spr_ctrl_c->mid_freq_nr.y_threshold_scl_en;
	IO_CNR(ch)->OTF_CSPR_REG.MCSSCL.bit.MCSSCL = spr_ctrl_c->mid_freq_nr.c_y_threshold_scl_en;
	IO_CNR(ch)->OTF_CSPR_REG.MCCSCL.bit.MCCSCL = spr_ctrl_c->mid_freq_nr.c_threshold_scl_en;

	IO_CNR(ch)->OTF_CSPR_REG.LCEN.bit.LCEN = spr_ctrl_c->low_freq_nr.enable;

	IO_CNR(ch)->OTF_CSPR_REG.LCYTHH.bit.LCYTHH_0 = spr_ctrl_c->low_freq_nr.h_y_threshold[0];
	IO_CNR(ch)->OTF_CSPR_REG.LCYTHH.bit.LCYTHH_1 = spr_ctrl_c->low_freq_nr.h_y_threshold[1];
	IO_CNR(ch)->OTF_CSPR_REG.LCYTHH.bit.LCYTHH_2 = spr_ctrl_c->low_freq_nr.h_y_threshold[2];
	IO_CNR(ch)->OTF_CSPR_REG.LCYTHH.bit.LCYTHH_3 = spr_ctrl_c->low_freq_nr.h_y_threshold[3];

	IO_CNR(ch)->OTF_CSPR_REG.LCYTHV.bit.LCYTHV_0 = spr_ctrl_c->low_freq_nr.v_y_threshold[0];
	IO_CNR(ch)->OTF_CSPR_REG.LCYTHV.bit.LCYTHV_1 = spr_ctrl_c->low_freq_nr.v_y_threshold[1];
	IO_CNR(ch)->OTF_CSPR_REG.LCYTHV.bit.LCYTHV_2 = spr_ctrl_c->low_freq_nr.v_y_threshold[2];
	IO_CNR(ch)->OTF_CSPR_REG.LCYTHV.bit.LCYTHV_3 = spr_ctrl_c->low_freq_nr.v_y_threshold[3];

	IO_CNR(ch)->OTF_CSPR_REG.LCCTHH.bit.LCCTHH_0 = spr_ctrl_c->low_freq_nr.h_c_threshold[0];
	IO_CNR(ch)->OTF_CSPR_REG.LCCTHH.bit.LCCTHH_1 = spr_ctrl_c->low_freq_nr.h_c_threshold[1];
	IO_CNR(ch)->OTF_CSPR_REG.LCCTHH.bit.LCCTHH_2 = spr_ctrl_c->low_freq_nr.h_c_threshold[2];
	IO_CNR(ch)->OTF_CSPR_REG.LCCTHH.bit.LCCTHH_3 = spr_ctrl_c->low_freq_nr.h_c_threshold[3];

	IO_CNR(ch)->OTF_CSPR_REG.LCCTHV.bit.LCCTHV_0 = spr_ctrl_c->low_freq_nr.v_c_threshold[0];
	IO_CNR(ch)->OTF_CSPR_REG.LCCTHV.bit.LCCTHV_1 = spr_ctrl_c->low_freq_nr.v_c_threshold[1];
	IO_CNR(ch)->OTF_CSPR_REG.LCCTHV.bit.LCCTHV_2 = spr_ctrl_c->low_freq_nr.v_c_threshold[2];
	IO_CNR(ch)->OTF_CSPR_REG.LCCTHV.bit.LCCTHV_3 = spr_ctrl_c->low_freq_nr.v_c_threshold[3];

	IO_CNR(ch)->OTF_CSPR_REG.LCYDYMDT.bit.LCYDYMYCR = spr_ctrl_c->low_freq_nr.y_threshold_cor;
	IO_CNR(ch)->OTF_CSPR_REG.LCYDYMDT.bit.LCYDYMYG = spr_ctrl_c->low_freq_nr.y_threshold_gain;

	IO_CNR(ch)->OTF_CSPR_REG.LCYDYM.bit.LCYDYM = spr_ctrl_c->low_freq_nr.y_threshold_dym_en;

	IO_CNR(ch)->OTF_CSPR_REG.LCYSCL.bit.LCYSCL = spr_ctrl_c->low_freq_nr.y_threshold_scl_en;
	IO_CNR(ch)->OTF_CSPR_REG.LCCSCL.bit.LCCSCL = spr_ctrl_c->low_freq_nr.c_threshold_scl_en;
	IO_CNR(ch)->OTF_CSPR_REG.LCCSCL.bit.LCCSCL = spr_ctrl_c->low_freq_nr.c_threshold_scl_en;

	IO_CNR(ch)->OTF_CSPR_REG.WHTMD.bit.WHTEN = spr_ctrl_c->whitening_enable;
	IO_CNR(ch)->OTF_CSPR_REG.WHTMD.bit.WHTVAL = spr_ctrl_c->whitening_value;
	IO_CNR(ch)->OTF_CSPR_REG.WHTMD.bit.WHTBASE = spr_ctrl_c->whitening_base;

	IO_CNR(ch)->OTF_CSPR_REG.BLEND.bit.BLENDMD = spr_ctrl_c->c_blend_md;
	IO_CNR(ch)->OTF_CSPR_REG.BLEND.bit.CSPRALPBD = spr_ctrl_c->c_alpha_blend;
	IO_CNR(ch)->OTF_CSPR_REG.BLEND.bit.CSRGEN = spr_ctrl_c->c_range;
	IO_CNR(ch)->OTF_CSPR_REG.BLEND.bit.CSRGMD = spr_ctrl_c->c_range_mode;

	Im_CNR_Off_Pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
Set SPR setting for Y for Off Line
*/
INT32 im_cnr_axi_ofl_ctrl_y(ImCnrAxi*self, UCHAR ch, const T_IM_CNR_OFL_CTRL_Y* const spr_ctrl_y )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_axi_ofl_ctrl_y() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_ctrl_y == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_axi_ofl_ctrl_y() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	Im_CNR_On_Pclk(ch);
	Im_CNR_Dsb();

	IO_CNR(ch)->OFL_REG_YSPR.YSPREN.bit.YSPREN = spr_ctrl_y->enable;
	IO_CNR(ch)->OFL_REG_YSPR.YSPRMODE.bit.YSPRMD = spr_ctrl_y->threshold_type;
	IO_CNR(ch)->OFL_REG_YSPR.YSPRMODE.bit.YSPRFE = spr_ctrl_y->level;

	IO_CNR(ch)->OFL_REG_YSPR.YSPRFXEY.bit.YSPRFXEYV = spr_ctrl_y->v_y_threshold;
	IO_CNR(ch)->OFL_REG_YSPR.YSPRFXEY.bit.YSPRFXEYH = spr_ctrl_y->h_y_threshold;
	IO_CNR(ch)->OFL_REG_YSPR.YSPRFXEC.bit.YSPRFXECV = spr_ctrl_y->v_c_threshold;
	IO_CNR(ch)->OFL_REG_YSPR.YSPRFXEC.bit.YSPRFXECH = spr_ctrl_y->h_c_threshold;
	IO_CNR(ch)->OFL_REG_YSPR.YSPRALPBD.bit.YSPRALPBD = spr_ctrl_y->alpha_blend_ratio;

	Im_CNR_Off_Pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
Set CbCr setting of source
*/
INT32 im_cnr_axi_ofl_ctrl_sprs_cc(ImCnrAxi*self, UCHAR ch, const T_IM_CNR_CTRL_CC_SRC_DST* const sprs_ctrl )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_axi_ofl_ctrl_sprs_cc() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( sprs_ctrl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_axi_ofl_ctrl_sprs_cc() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	Im_CNR_On_Pclk(ch);
	Im_CNR_Dsb();

	IO_CNR(ch)->OFL_CSPR_REG.SPRS.bit.SPRS = sprs_ctrl->enable;

	// write signed data
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRSCBBD.SPRSCBBD1, union io_cnr_cspr_reg_sprscbbd_1, SPRSCBBD_1, sprs_ctrl->cb_table.bd1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRSCBBD.SPRSCBBD1, union io_cnr_cspr_reg_sprscbbd_1, SPRSCBBD_2, sprs_ctrl->cb_table.bd2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRSCBBD.SPRSCBBD1, union io_cnr_cspr_reg_sprscbbd_1, SPRSCBBD_3, sprs_ctrl->cb_table.bd3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRSCBBD.SPRSCBBD1, union io_cnr_cspr_reg_sprscbbd_1, SPRSCBBD_4, sprs_ctrl->cb_table.bd4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRSCBBD.SPRSCBBD2, union io_cnr_cspr_reg_sprscbbd_2, SPRSCBBD_5, sprs_ctrl->cb_table.bd5 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRSCBOF.SPRSCBOF1, union io_cnr_cspr_reg_sprscbof_1, SPRSCBOF_0, sprs_ctrl->cb_table.of0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRSCBOF.SPRSCBOF1, union io_cnr_cspr_reg_sprscbof_1, SPRSCBOF_1, sprs_ctrl->cb_table.of1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRSCBOF.SPRSCBOF1, union io_cnr_cspr_reg_sprscbof_1, SPRSCBOF_2, sprs_ctrl->cb_table.of2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRSCBOF.SPRSCBOF1, union io_cnr_cspr_reg_sprscbof_1, SPRSCBOF_3, sprs_ctrl->cb_table.of3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRSCBOF.SPRSCBOF2, union io_cnr_cspr_reg_sprscbof_2, SPRSCBOF_4, sprs_ctrl->cb_table.of4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRSCBOF.SPRSCBOF2, union io_cnr_cspr_reg_sprscbof_2, SPRSCBOF_5, sprs_ctrl->cb_table.of5 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRSCBGA.SPRSCBGA1, union io_cnr_cspr_reg_sprscbga_1, SPRSCBGA_0, sprs_ctrl->cb_table.gain0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRSCBGA.SPRSCBGA1, union io_cnr_cspr_reg_sprscbga_1, SPRSCBGA_1, sprs_ctrl->cb_table.gain1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRSCBGA.SPRSCBGA2, union io_cnr_cspr_reg_sprscbga_2, SPRSCBGA_2, sprs_ctrl->cb_table.gain2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRSCBGA.SPRSCBGA2, union io_cnr_cspr_reg_sprscbga_2, SPRSCBGA_3, sprs_ctrl->cb_table.gain3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRSCBGA.SPRSCBGA3, union io_cnr_cspr_reg_sprscbga_3, SPRSCBGA_4, sprs_ctrl->cb_table.gain4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRSCBGA.SPRSCBGA3, union io_cnr_cspr_reg_sprscbga_3, SPRSCBGA_5, sprs_ctrl->cb_table.gain5 );

	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRSCRBD.SPRSCRBD1, union io_cnr_cspr_reg_sprscrbd_1, SPRSCRBD_1, sprs_ctrl->cr_table.bd1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRSCRBD.SPRSCRBD1, union io_cnr_cspr_reg_sprscrbd_1, SPRSCRBD_2, sprs_ctrl->cr_table.bd2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRSCRBD.SPRSCRBD1, union io_cnr_cspr_reg_sprscrbd_1, SPRSCRBD_3, sprs_ctrl->cr_table.bd3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRSCRBD.SPRSCRBD1, union io_cnr_cspr_reg_sprscrbd_1, SPRSCRBD_4, sprs_ctrl->cr_table.bd4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRSCRBD.SPRSCRBD2, union io_cnr_cspr_reg_sprscrbd_2, SPRSCRBD_5, sprs_ctrl->cr_table.bd5 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRSCROF.SPRSCROF1, union io_cnr_cspr_reg_sprscrof_1, SPRSCROF_0, sprs_ctrl->cr_table.of0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRSCROF.SPRSCROF1, union io_cnr_cspr_reg_sprscrof_1, SPRSCROF_1, sprs_ctrl->cr_table.of1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRSCROF.SPRSCROF1, union io_cnr_cspr_reg_sprscrof_1, SPRSCROF_2, sprs_ctrl->cr_table.of2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRSCROF.SPRSCROF1, union io_cnr_cspr_reg_sprscrof_1, SPRSCROF_3, sprs_ctrl->cr_table.of3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRSCROF.SPRSCROF2, union io_cnr_cspr_reg_sprscrof_2, SPRSCROF_4, sprs_ctrl->cr_table.of4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRSCROF.SPRSCROF2, union io_cnr_cspr_reg_sprscrof_2, SPRSCROF_5, sprs_ctrl->cr_table.of5 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRSCRGA.SPRSCRGA1, union io_cnr_cspr_reg_sprscrga_1, SPRSCRGA_0, sprs_ctrl->cr_table.gain0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRSCRGA.SPRSCRGA1, union io_cnr_cspr_reg_sprscrga_1, SPRSCRGA_1, sprs_ctrl->cr_table.gain1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRSCRGA.SPRSCRGA2, union io_cnr_cspr_reg_sprscrga_2, SPRSCRGA_2, sprs_ctrl->cr_table.gain2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRSCRGA.SPRSCRGA2, union io_cnr_cspr_reg_sprscrga_2, SPRSCRGA_3, sprs_ctrl->cr_table.gain3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRSCRGA.SPRSCRGA3, union io_cnr_cspr_reg_sprscrga_3, SPRSCRGA_4, sprs_ctrl->cr_table.gain4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRSCRGA.SPRSCRGA3, union io_cnr_cspr_reg_sprscrga_3, SPRSCRGA_5, sprs_ctrl->cr_table.gain5 );

	Im_CNR_Off_Pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
Set CbCr setting of source
*/
INT32 im_cnr_axi_otf_ctrl_sprs_cc(ImCnrAxi*self, UCHAR ch, const T_IM_CNR_CTRL_CC_SRC_DST* const sprs_ctrl )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_axi_otf_ctrl_sprs_cc() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( sprs_ctrl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_axi_otf_ctrl_sprs_cc() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	Im_CNR_On_Pclk(ch);
	Im_CNR_Dsb();

	IO_CNR(ch)->OTF_CSPR_REG.SPRS.bit.SPRS = sprs_ctrl->enable;

	// write signed data
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRSCBBD.SPRSCBBD1, union io_cnr_cspr_reg_sprscbbd_1, SPRSCBBD_1, sprs_ctrl->cb_table.bd1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRSCBBD.SPRSCBBD1, union io_cnr_cspr_reg_sprscbbd_1, SPRSCBBD_2, sprs_ctrl->cb_table.bd2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRSCBBD.SPRSCBBD1, union io_cnr_cspr_reg_sprscbbd_1, SPRSCBBD_3, sprs_ctrl->cb_table.bd3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRSCBBD.SPRSCBBD1, union io_cnr_cspr_reg_sprscbbd_1, SPRSCBBD_4, sprs_ctrl->cb_table.bd4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRSCBBD.SPRSCBBD2, union io_cnr_cspr_reg_sprscbbd_2, SPRSCBBD_5, sprs_ctrl->cb_table.bd5 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRSCBOF.SPRSCBOF1, union io_cnr_cspr_reg_sprscbof_1, SPRSCBOF_0, sprs_ctrl->cb_table.of0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRSCBOF.SPRSCBOF1, union io_cnr_cspr_reg_sprscbof_1, SPRSCBOF_1, sprs_ctrl->cb_table.of1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRSCBOF.SPRSCBOF1, union io_cnr_cspr_reg_sprscbof_1, SPRSCBOF_2, sprs_ctrl->cb_table.of2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRSCBOF.SPRSCBOF1, union io_cnr_cspr_reg_sprscbof_1, SPRSCBOF_3, sprs_ctrl->cb_table.of3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRSCBOF.SPRSCBOF2, union io_cnr_cspr_reg_sprscbof_2, SPRSCBOF_4, sprs_ctrl->cb_table.of4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRSCBOF.SPRSCBOF2, union io_cnr_cspr_reg_sprscbof_2, SPRSCBOF_5, sprs_ctrl->cb_table.of5 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRSCBGA.SPRSCBGA1, union io_cnr_cspr_reg_sprscbga_1, SPRSCBGA_0, sprs_ctrl->cb_table.gain0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRSCBGA.SPRSCBGA1, union io_cnr_cspr_reg_sprscbga_1, SPRSCBGA_1, sprs_ctrl->cb_table.gain1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRSCBGA.SPRSCBGA2, union io_cnr_cspr_reg_sprscbga_2, SPRSCBGA_2, sprs_ctrl->cb_table.gain2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRSCBGA.SPRSCBGA2, union io_cnr_cspr_reg_sprscbga_2, SPRSCBGA_3, sprs_ctrl->cb_table.gain3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRSCBGA.SPRSCBGA3, union io_cnr_cspr_reg_sprscbga_3, SPRSCBGA_4, sprs_ctrl->cb_table.gain4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRSCBGA.SPRSCBGA3, union io_cnr_cspr_reg_sprscbga_3, SPRSCBGA_5, sprs_ctrl->cb_table.gain5 );

	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRSCRBD.SPRSCRBD1, union io_cnr_cspr_reg_sprscrbd_1, SPRSCRBD_1, sprs_ctrl->cr_table.bd1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRSCRBD.SPRSCRBD1, union io_cnr_cspr_reg_sprscrbd_1, SPRSCRBD_2, sprs_ctrl->cr_table.bd2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRSCRBD.SPRSCRBD1, union io_cnr_cspr_reg_sprscrbd_1, SPRSCRBD_3, sprs_ctrl->cr_table.bd3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRSCRBD.SPRSCRBD1, union io_cnr_cspr_reg_sprscrbd_1, SPRSCRBD_4, sprs_ctrl->cr_table.bd4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRSCRBD.SPRSCRBD2, union io_cnr_cspr_reg_sprscrbd_2, SPRSCRBD_5, sprs_ctrl->cr_table.bd5 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRSCROF.SPRSCROF1, union io_cnr_cspr_reg_sprscrof_1, SPRSCROF_0, sprs_ctrl->cr_table.of0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRSCROF.SPRSCROF1, union io_cnr_cspr_reg_sprscrof_1, SPRSCROF_1, sprs_ctrl->cr_table.of1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRSCROF.SPRSCROF1, union io_cnr_cspr_reg_sprscrof_1, SPRSCROF_2, sprs_ctrl->cr_table.of2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRSCROF.SPRSCROF1, union io_cnr_cspr_reg_sprscrof_1, SPRSCROF_3, sprs_ctrl->cr_table.of3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRSCROF.SPRSCROF2, union io_cnr_cspr_reg_sprscrof_2, SPRSCROF_4, sprs_ctrl->cr_table.of4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRSCROF.SPRSCROF2, union io_cnr_cspr_reg_sprscrof_2, SPRSCROF_5, sprs_ctrl->cr_table.of5 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRSCRGA.SPRSCRGA1, union io_cnr_cspr_reg_sprscrga_1, SPRSCRGA_0, sprs_ctrl->cr_table.gain0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRSCRGA.SPRSCRGA1, union io_cnr_cspr_reg_sprscrga_1, SPRSCRGA_1, sprs_ctrl->cr_table.gain1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRSCRGA.SPRSCRGA2, union io_cnr_cspr_reg_sprscrga_2, SPRSCRGA_2, sprs_ctrl->cr_table.gain2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRSCRGA.SPRSCRGA2, union io_cnr_cspr_reg_sprscrga_2, SPRSCRGA_3, sprs_ctrl->cr_table.gain3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRSCRGA.SPRSCRGA3, union io_cnr_cspr_reg_sprscrga_3, SPRSCRGA_4, sprs_ctrl->cr_table.gain4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRSCRGA.SPRSCRGA3, union io_cnr_cspr_reg_sprscrga_3, SPRSCRGA_5, sprs_ctrl->cr_table.gain5 );

	Im_CNR_Off_Pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
Set CbCr setting of destination
*/
INT32 im_cnr_axi_ofl_ctrl_sprd_cc(ImCnrAxi*self, UCHAR ch, const T_IM_CNR_CTRL_CC_SRC_DST* const sprd_ctrl )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_axi_ofl_ctrl_sprd_cc() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( sprd_ctrl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_axi_ofl_ctrl_sprd_cc() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	Im_CNR_On_Pclk(ch);
	Im_CNR_Dsb();

	IO_CNR(ch)->OFL_CSPR_REG.SPRD.bit.SPRD = sprd_ctrl->enable;

	// write signed data
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCBBD.SPRDCBBD1, union io_cnr_cspr_reg_sprdcbbd_1, SPRDCBBD_1, sprd_ctrl->cb_table.bd1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCBBD.SPRDCBBD1, union io_cnr_cspr_reg_sprdcbbd_1, SPRDCBBD_2, sprd_ctrl->cb_table.bd2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCBBD.SPRDCBBD1, union io_cnr_cspr_reg_sprdcbbd_1, SPRDCBBD_3, sprd_ctrl->cb_table.bd3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCBBD.SPRDCBBD1, union io_cnr_cspr_reg_sprdcbbd_1, SPRDCBBD_4, sprd_ctrl->cb_table.bd4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCBBD.SPRDCBBD2, union io_cnr_cspr_reg_sprdcbbd_2, SPRDCBBD_5, sprd_ctrl->cb_table.bd5 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCBOF.SPRDCBOF1, union io_cnr_cspr_reg_sprdcbof_1, SPRDCBOF_0, sprd_ctrl->cb_table.of0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCBOF.SPRDCBOF1, union io_cnr_cspr_reg_sprdcbof_1, SPRDCBOF_1, sprd_ctrl->cb_table.of1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCBOF.SPRDCBOF1, union io_cnr_cspr_reg_sprdcbof_1, SPRDCBOF_2, sprd_ctrl->cb_table.of2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCBOF.SPRDCBOF1, union io_cnr_cspr_reg_sprdcbof_1, SPRDCBOF_3, sprd_ctrl->cb_table.of3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCBOF.SPRDCBOF2, union io_cnr_cspr_reg_sprdcbof_2, SPRDCBOF_4, sprd_ctrl->cb_table.of4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCBOF.SPRDCBOF2, union io_cnr_cspr_reg_sprdcbof_2, SPRDCBOF_5, sprd_ctrl->cb_table.of5 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCBGA.SPRDCBGA1, union io_cnr_cspr_reg_sprdcbga_1, SPRDCBGA_0, sprd_ctrl->cb_table.gain0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCBGA.SPRDCBGA1, union io_cnr_cspr_reg_sprdcbga_1, SPRDCBGA_1, sprd_ctrl->cb_table.gain1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCBGA.SPRDCBGA2, union io_cnr_cspr_reg_sprdcbga_2, SPRDCBGA_2, sprd_ctrl->cb_table.gain2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCBGA.SPRDCBGA2, union io_cnr_cspr_reg_sprdcbga_2, SPRDCBGA_3, sprd_ctrl->cb_table.gain3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCBGA.SPRDCBGA3, union io_cnr_cspr_reg_sprdcbga_3, SPRDCBGA_4, sprd_ctrl->cb_table.gain4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCBGA.SPRDCBGA3, union io_cnr_cspr_reg_sprdcbga_3, SPRDCBGA_5, sprd_ctrl->cb_table.gain5 );

	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCRBD.SPRDCRBD1, union io_cnr_cspr_reg_sprdcrbd_1, SPRDCRBD_1, sprd_ctrl->cr_table.bd1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCRBD.SPRDCRBD1, union io_cnr_cspr_reg_sprdcrbd_1, SPRDCRBD_2, sprd_ctrl->cr_table.bd2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCRBD.SPRDCRBD1, union io_cnr_cspr_reg_sprdcrbd_1, SPRDCRBD_3, sprd_ctrl->cr_table.bd3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCRBD.SPRDCRBD1, union io_cnr_cspr_reg_sprdcrbd_1, SPRDCRBD_4, sprd_ctrl->cr_table.bd4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCRBD.SPRDCRBD2, union io_cnr_cspr_reg_sprdcrbd_2, SPRDCRBD_5, sprd_ctrl->cr_table.bd5 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCROF.SPRDCROF1, union io_cnr_cspr_reg_sprdcrof_1, SPRDCROF_0, sprd_ctrl->cr_table.of0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCROF.SPRDCROF1, union io_cnr_cspr_reg_sprdcrof_1, SPRDCROF_1, sprd_ctrl->cr_table.of1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCROF.SPRDCROF1, union io_cnr_cspr_reg_sprdcrof_1, SPRDCROF_2, sprd_ctrl->cr_table.of2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCROF.SPRDCROF1, union io_cnr_cspr_reg_sprdcrof_1, SPRDCROF_3, sprd_ctrl->cr_table.of3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCROF.SPRDCROF2, union io_cnr_cspr_reg_sprdcrof_2, SPRDCROF_4, sprd_ctrl->cr_table.of4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCROF.SPRDCROF2, union io_cnr_cspr_reg_sprdcrof_2, SPRDCROF_5, sprd_ctrl->cr_table.of5 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCRGA.SPRDCRGA1, union io_cnr_cspr_reg_sprdcrga_1, SPRDCRGA_0, sprd_ctrl->cr_table.gain0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCRGA.SPRDCRGA1, union io_cnr_cspr_reg_sprdcrga_1, SPRDCRGA_1, sprd_ctrl->cr_table.gain1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCRGA.SPRDCRGA2, union io_cnr_cspr_reg_sprdcrga_2, SPRDCRGA_2, sprd_ctrl->cr_table.gain2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCRGA.SPRDCRGA2, union io_cnr_cspr_reg_sprdcrga_2, SPRDCRGA_3, sprd_ctrl->cr_table.gain3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCRGA.SPRDCRGA3, union io_cnr_cspr_reg_sprdcrga_3, SPRDCRGA_4, sprd_ctrl->cr_table.gain4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCRGA.SPRDCRGA3, union io_cnr_cspr_reg_sprdcrga_3, SPRDCRGA_5, sprd_ctrl->cr_table.gain5 );

	Im_CNR_Off_Pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
Set CbCr setting of destination
*/
INT32 im_cnr_axi_otf_ctrl_sprd_cc(ImCnrAxi*self, UCHAR ch, const T_IM_CNR_CTRL_CC_SRC_DST* const sprd_ctrl )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_axi_otf_ctrl_sprd_cc() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( sprd_ctrl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_axi_otf_ctrl_sprd_cc() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	Im_CNR_On_Pclk(ch);
	Im_CNR_Dsb();

	IO_CNR(ch)->OTF_CSPR_REG.SPRD.bit.SPRD = sprd_ctrl->enable;

	// write signed data
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCBBD.SPRDCBBD1, union io_cnr_cspr_reg_sprdcbbd_1, SPRDCBBD_1, sprd_ctrl->cb_table.bd1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCBBD.SPRDCBBD1, union io_cnr_cspr_reg_sprdcbbd_1, SPRDCBBD_2, sprd_ctrl->cb_table.bd2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCBBD.SPRDCBBD1, union io_cnr_cspr_reg_sprdcbbd_1, SPRDCBBD_3, sprd_ctrl->cb_table.bd3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCBBD.SPRDCBBD1, union io_cnr_cspr_reg_sprdcbbd_1, SPRDCBBD_4, sprd_ctrl->cb_table.bd4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCBBD.SPRDCBBD2, union io_cnr_cspr_reg_sprdcbbd_2, SPRDCBBD_5, sprd_ctrl->cb_table.bd5 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCBOF.SPRDCBOF1, union io_cnr_cspr_reg_sprdcbof_1, SPRDCBOF_0, sprd_ctrl->cb_table.of0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCBOF.SPRDCBOF1, union io_cnr_cspr_reg_sprdcbof_1, SPRDCBOF_1, sprd_ctrl->cb_table.of1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCBOF.SPRDCBOF1, union io_cnr_cspr_reg_sprdcbof_1, SPRDCBOF_2, sprd_ctrl->cb_table.of2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCBOF.SPRDCBOF1, union io_cnr_cspr_reg_sprdcbof_1, SPRDCBOF_3, sprd_ctrl->cb_table.of3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCBOF.SPRDCBOF2, union io_cnr_cspr_reg_sprdcbof_2, SPRDCBOF_4, sprd_ctrl->cb_table.of4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCBOF.SPRDCBOF2, union io_cnr_cspr_reg_sprdcbof_2, SPRDCBOF_5, sprd_ctrl->cb_table.of5 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCBGA.SPRDCBGA1, union io_cnr_cspr_reg_sprdcbga_1, SPRDCBGA_0, sprd_ctrl->cb_table.gain0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCBGA.SPRDCBGA1, union io_cnr_cspr_reg_sprdcbga_1, SPRDCBGA_1, sprd_ctrl->cb_table.gain1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCBGA.SPRDCBGA2, union io_cnr_cspr_reg_sprdcbga_2, SPRDCBGA_2, sprd_ctrl->cb_table.gain2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCBGA.SPRDCBGA2, union io_cnr_cspr_reg_sprdcbga_2, SPRDCBGA_3, sprd_ctrl->cb_table.gain3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCBGA.SPRDCBGA3, union io_cnr_cspr_reg_sprdcbga_3, SPRDCBGA_4, sprd_ctrl->cb_table.gain4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCBGA.SPRDCBGA3, union io_cnr_cspr_reg_sprdcbga_3, SPRDCBGA_5, sprd_ctrl->cb_table.gain5 );

	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCRBD.SPRDCRBD1, union io_cnr_cspr_reg_sprdcrbd_1, SPRDCRBD_1, sprd_ctrl->cr_table.bd1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCRBD.SPRDCRBD1, union io_cnr_cspr_reg_sprdcrbd_1, SPRDCRBD_2, sprd_ctrl->cr_table.bd2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCRBD.SPRDCRBD1, union io_cnr_cspr_reg_sprdcrbd_1, SPRDCRBD_3, sprd_ctrl->cr_table.bd3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCRBD.SPRDCRBD1, union io_cnr_cspr_reg_sprdcrbd_1, SPRDCRBD_4, sprd_ctrl->cr_table.bd4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCRBD.SPRDCRBD2, union io_cnr_cspr_reg_sprdcrbd_2, SPRDCRBD_5, sprd_ctrl->cr_table.bd5 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCROF.SPRDCROF1, union io_cnr_cspr_reg_sprdcrof_1, SPRDCROF_0, sprd_ctrl->cr_table.of0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCROF.SPRDCROF1, union io_cnr_cspr_reg_sprdcrof_1, SPRDCROF_1, sprd_ctrl->cr_table.of1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCROF.SPRDCROF1, union io_cnr_cspr_reg_sprdcrof_1, SPRDCROF_2, sprd_ctrl->cr_table.of2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCROF.SPRDCROF1, union io_cnr_cspr_reg_sprdcrof_1, SPRDCROF_3, sprd_ctrl->cr_table.of3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCROF.SPRDCROF2, union io_cnr_cspr_reg_sprdcrof_2, SPRDCROF_4, sprd_ctrl->cr_table.of4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCROF.SPRDCROF2, union io_cnr_cspr_reg_sprdcrof_2, SPRDCROF_5, sprd_ctrl->cr_table.of5 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCRGA.SPRDCRGA1, union io_cnr_cspr_reg_sprdcrga_1, SPRDCRGA_0, sprd_ctrl->cr_table.gain0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCRGA.SPRDCRGA1, union io_cnr_cspr_reg_sprdcrga_1, SPRDCRGA_1, sprd_ctrl->cr_table.gain1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCRGA.SPRDCRGA2, union io_cnr_cspr_reg_sprdcrga_2, SPRDCRGA_2, sprd_ctrl->cr_table.gain2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCRGA.SPRDCRGA2, union io_cnr_cspr_reg_sprdcrga_2, SPRDCRGA_3, sprd_ctrl->cr_table.gain3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCRGA.SPRDCRGA3, union io_cnr_cspr_reg_sprdcrga_3, SPRDCRGA_4, sprd_ctrl->cr_table.gain4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCRGA.SPRDCRGA3, union io_cnr_cspr_reg_sprdcrga_3, SPRDCRGA_5, sprd_ctrl->cr_table.gain5 );

	Im_CNR_Off_Pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

ImCnrAxi *im_cnr_axi_new(void)
{
	ImCnrAxi* self = k_object_new_with_private(IM_TYPE_CNR_AXI,sizeof(ImCnrAxiPrivate));
	return self;
}
