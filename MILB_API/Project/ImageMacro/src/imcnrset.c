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

#include "imcnrset.h"
#include "imcnr.h"
#include "imcnrget.h"
#include "imcnrinit.h"
#include "imcnrcspr.h"
#include "imcnraxi.h"
#include "driver_common.h"
// #if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
// #endif
#include "dd_arm.h"
#include "ddim_user_custom.h"
#include "jdscnr.h"
// for memset
#include <string.h>

K_TYPE_DEFINE_WITH_PRIVATE(ImCnrSet, im_cnr_set);
#define IM_CNR_SET_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImCnrSetPrivate, IM_TYPE_CNR_SET))

struct _ImCnrSetPrivate
{
	int a;
};

/*----------------------------------------------------------------------*/
/* Local Method Definition												*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
static VOID imCnrConvertRdmaValueCtrlC( const T_IM_CNR_CTRL_C* spr_ctrl_c, T_IM_CNR_RDMA_DATA_CTRL_C* rdma_ctrl_c );
static VOID imCnrConvertRdmaCsprMidYTable( const T_IM_CNR_TABLE* spr_cspr_mid_y, T_IM_CNR_RDMA_DATA_CSPR_MID_Y_TBL* rdma_cspr_mid_y_table );
static VOID imCnrConvertRdmaCsprMidCcYTable( const T_IM_CNR_TABLE* cspr_mid_cc_y, T_IM_CNR_RDMA_DATA_CSPR_MID_CC_Y_TBL* rdma_mid_cc_y_table );
static VOID imCnrConvertRdmaCsprMidCcCTable( const T_IM_CNR_TABLE* cspr_mid_cc_c, T_IM_CNR_RDMA_DATA_CSPR_MID_CC_C_TBL* rdma_mid_cc_c_table );
static VOID imCnrConvertRdmaCsprLowYTable( const T_IM_CNR_TABLE* spr_cspr_low_y, T_IM_CNR_RDMA_DATA_CSPR_LOW_Y_TBL* rdma_cspr_low_y_table );
static VOID imCnrConvertRdmaCsprLowCcYTable( const T_IM_CNR_TABLE* cspr_low_cc_y, T_IM_CNR_RDMA_DATA_CSPR_LOW_CC_Y_TBL* rdma_low_cc_y_table );
static VOID imCnrConvertRdmaCsprLowCcCTable( const T_IM_CNR_TABLE* cspr_low_cc_c, T_IM_CNR_RDMA_DATA_CSPR_LOW_CC_C_TBL* rdma_low_cc_c_table );
static VOID imCnrConvertRdmaCsprEdgeTable( const T_IM_CNR_TABLE* cspr_edge, T_IM_CNR_RDMA_DATA_CSPR_EDGE_TBL* rdma_edge_table );
static VOID imCnrConvertRdmaCsprHueTable( const T_IM_CNR_HUE_SPEC_TABLE* cspr_hue, T_IM_CNR_RDMA_DATA_CSPR_HUE_TBL* rdma_hue_table );
static VOID imCnrConvertRdmaCsprSprsCc( const T_IM_CNR_CTRL_CC_SRC_DST* sprs_ctrl, T_IM_CNR_RDMA_DATA_SPRS_CC_TBL* rdma_sprs_ctrl );
static VOID imCnrConvertRdmaCsprSprdCc( const T_IM_CNR_CTRL_CC_SRC_DST* sprd_ctrl, T_IM_CNR_RDMA_DATA_SPRD_CC_TBL* rdma_sprd_ctrl );
// Nothing Special
//---------------------------- colabo section ----------------------------
// Nothing Special
#endif

static void im_cnr_set_constructor(ImCnrSet *self)
{
}

static void im_cnr_set_destructor(ImCnrSet *self)
{
}

/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/
#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
// Nothing Special
//---------------------------- colabo section ----------------------------
/*
Convert T_IM_CNR_CTRL_C to T_IM_CNR_RDMA_DATA_CTRL_C
*/
static VOID imCnrConvertRdmaValueCtrlC( const T_IM_CNR_CTRL_C* spr_ctrl_c, T_IM_CNR_RDMA_DATA_CTRL_C* rdma_ctrl_c )
{
	rdma_ctrl_c->CSPREN.bit.CSPREN	= spr_ctrl_c->enable;
	rdma_ctrl_c->CGDKEN.bit.CGDKEN	= spr_ctrl_c->gradation_keep_en;
	rdma_ctrl_c->MCEN.bit.MCEN		= spr_ctrl_c->mid_freq_nr.enable;

	rdma_ctrl_c->MCYTHH.bit.MCYTHH_0	= spr_ctrl_c->mid_freq_nr.h_y_threshold[0];
	rdma_ctrl_c->MCYTHH.bit.MCYTHH_1	= spr_ctrl_c->mid_freq_nr.h_y_threshold[1];
	rdma_ctrl_c->MCYTHH.bit.MCYTHH_2	= spr_ctrl_c->mid_freq_nr.h_y_threshold[2];
	rdma_ctrl_c->MCYTHH.bit.MCYTHH_3	= spr_ctrl_c->mid_freq_nr.h_y_threshold[3];
	rdma_ctrl_c->MCYTHV.bit.MCYTHV_0	= spr_ctrl_c->mid_freq_nr.v_y_threshold[0];
	rdma_ctrl_c->MCYTHV.bit.MCYTHV_1	= spr_ctrl_c->mid_freq_nr.v_y_threshold[1];
	rdma_ctrl_c->MCYTHV.bit.MCYTHV_2	= spr_ctrl_c->mid_freq_nr.v_y_threshold[2];
	rdma_ctrl_c->MCYTHV.bit.MCYTHV_3	= spr_ctrl_c->mid_freq_nr.v_y_threshold[3];
	rdma_ctrl_c->MCCTHH.bit.MCCTHH_0	= spr_ctrl_c->mid_freq_nr.h_c_threshold[0];
	rdma_ctrl_c->MCCTHH.bit.MCCTHH_1	= spr_ctrl_c->mid_freq_nr.h_c_threshold[1];
	rdma_ctrl_c->MCCTHH.bit.MCCTHH_2	= spr_ctrl_c->mid_freq_nr.h_c_threshold[2];
	rdma_ctrl_c->MCCTHH.bit.MCCTHH_3	= spr_ctrl_c->mid_freq_nr.h_c_threshold[3];
	rdma_ctrl_c->MCCTHV.bit.MCCTHV_0	= spr_ctrl_c->mid_freq_nr.v_c_threshold[0];
	rdma_ctrl_c->MCCTHV.bit.MCCTHV_1	= spr_ctrl_c->mid_freq_nr.v_c_threshold[1];
	rdma_ctrl_c->MCCTHV.bit.MCCTHV_2	= spr_ctrl_c->mid_freq_nr.v_c_threshold[2];
	rdma_ctrl_c->MCCTHV.bit.MCCTHV_3	= spr_ctrl_c->mid_freq_nr.v_c_threshold[3];
	rdma_ctrl_c->MCYDYMDT.bit.MCYDYMYCR	= spr_ctrl_c->mid_freq_nr.y_threshold_cor;
	rdma_ctrl_c->MCYDYMDT.bit.MCYDYMYG	= spr_ctrl_c->mid_freq_nr.y_threshold_gain;
	rdma_ctrl_c->MCYDYM.bit.MCYDYM		= spr_ctrl_c->mid_freq_nr.y_threshold_dym_en;
	rdma_ctrl_c->MCYSCL.bit.MCYSCL		= spr_ctrl_c->mid_freq_nr.y_threshold_scl_en;
	rdma_ctrl_c->MCSSCL.bit.MCSSCL		= spr_ctrl_c->mid_freq_nr.c_y_threshold_scl_en;
	rdma_ctrl_c->MCCSCL.bit.MCCSCL		= spr_ctrl_c->mid_freq_nr.c_threshold_scl_en;
	rdma_ctrl_c->LCEN.bit.LCEN			= spr_ctrl_c->low_freq_nr.enable;
	rdma_ctrl_c->LCYTHH.bit.LCYTHH_0	= spr_ctrl_c->low_freq_nr.h_y_threshold[0];
	rdma_ctrl_c->LCYTHH.bit.LCYTHH_1	= spr_ctrl_c->low_freq_nr.h_y_threshold[1];
	rdma_ctrl_c->LCYTHH.bit.LCYTHH_2	= spr_ctrl_c->low_freq_nr.h_y_threshold[2];
	rdma_ctrl_c->LCYTHH.bit.LCYTHH_3	= spr_ctrl_c->low_freq_nr.h_y_threshold[3];
	rdma_ctrl_c->LCYTHV.bit.LCYTHV_0	= spr_ctrl_c->low_freq_nr.v_y_threshold[0];
	rdma_ctrl_c->LCYTHV.bit.LCYTHV_1	= spr_ctrl_c->low_freq_nr.v_y_threshold[1];
	rdma_ctrl_c->LCYTHV.bit.LCYTHV_2	= spr_ctrl_c->low_freq_nr.v_y_threshold[2];
	rdma_ctrl_c->LCYTHV.bit.LCYTHV_3	= spr_ctrl_c->low_freq_nr.v_y_threshold[3];
	rdma_ctrl_c->LCCTHH.bit.LCCTHH_0	= spr_ctrl_c->low_freq_nr.h_c_threshold[0];
	rdma_ctrl_c->LCCTHH.bit.LCCTHH_1	= spr_ctrl_c->low_freq_nr.h_c_threshold[1];
	rdma_ctrl_c->LCCTHH.bit.LCCTHH_2	= spr_ctrl_c->low_freq_nr.h_c_threshold[2];
	rdma_ctrl_c->LCCTHH.bit.LCCTHH_3	= spr_ctrl_c->low_freq_nr.h_c_threshold[3];
	rdma_ctrl_c->LCCTHV.bit.LCCTHV_0	= spr_ctrl_c->low_freq_nr.v_c_threshold[0];
	rdma_ctrl_c->LCCTHV.bit.LCCTHV_1	= spr_ctrl_c->low_freq_nr.v_c_threshold[1];
	rdma_ctrl_c->LCCTHV.bit.LCCTHV_2	= spr_ctrl_c->low_freq_nr.v_c_threshold[2];
	rdma_ctrl_c->LCCTHV.bit.LCCTHV_3	= spr_ctrl_c->low_freq_nr.v_c_threshold[3];
	rdma_ctrl_c->LCYDYMDT.bit.LCYDYMYCR	= spr_ctrl_c->low_freq_nr.y_threshold_cor;
	rdma_ctrl_c->LCYDYMDT.bit.LCYDYMYG	= spr_ctrl_c->low_freq_nr.y_threshold_gain;
	rdma_ctrl_c->LCYDYM.bit.LCYDYM	= spr_ctrl_c->low_freq_nr.y_threshold_dym_en;
	rdma_ctrl_c->LCYSCL.bit.LCYSCL	= spr_ctrl_c->low_freq_nr.y_threshold_scl_en;
	rdma_ctrl_c->LCSSCL.bit.LCSSCL	= spr_ctrl_c->low_freq_nr.c_y_threshold_scl_en;
	rdma_ctrl_c->LCCSCL.bit.LCCSCL	= spr_ctrl_c->low_freq_nr.c_threshold_scl_en;
	rdma_ctrl_c->WHTMD.bit.WHTEN	= spr_ctrl_c->whitening_enable;
	rdma_ctrl_c->WHTMD.bit.WHTVAL	= spr_ctrl_c->whitening_value;
	rdma_ctrl_c->WHTMD.bit.WHTBASE	= spr_ctrl_c->whitening_base;
	rdma_ctrl_c->BLEND.bit.BLENDMD		= spr_ctrl_c->c_blend_md;
	rdma_ctrl_c->BLEND.bit.CSPRALPBD	= spr_ctrl_c->c_alpha_blend;
	rdma_ctrl_c->BLEND.bit.CSRGEN		= spr_ctrl_c->c_range;
	rdma_ctrl_c->BLEND.bit.CSRGMD		= spr_ctrl_c->c_range_mode;
}

/*
Convert T_IM_CNR_TABLE to T_IM_CNR_RDMA_DATA_CSPR_MID_Y_TBL
*/
static VOID imCnrConvertRdmaCsprMidYTable( const T_IM_CNR_TABLE* spr_cspr_mid_y, T_IM_CNR_RDMA_DATA_CSPR_MID_Y_TBL* rdma_cspr_mid_y_table )
{
	rdma_cspr_mid_y_table->MCYSCLBD.MCYSCLBD1.bit.MCYSCLBD_1	= spr_cspr_mid_y->bd1;
	rdma_cspr_mid_y_table->MCYSCLBD.MCYSCLBD1.bit.MCYSCLBD_2	= spr_cspr_mid_y->bd2;
	rdma_cspr_mid_y_table->MCYSCLBD.MCYSCLBD1.bit.MCYSCLBD_3	= spr_cspr_mid_y->bd3;
	rdma_cspr_mid_y_table->MCYSCLBD.MCYSCLBD1.bit.MCYSCLBD_4	= spr_cspr_mid_y->bd4;
	rdma_cspr_mid_y_table->MCYSCLBD.MCYSCLBD2.bit.MCYSCLBD_5	= spr_cspr_mid_y->bd5;
	rdma_cspr_mid_y_table->MCYSCLOF.MCYSCLOF1.bit.MCYSCLOF_0	= spr_cspr_mid_y->of0;
	rdma_cspr_mid_y_table->MCYSCLOF.MCYSCLOF1.bit.MCYSCLOF_1	= spr_cspr_mid_y->of1;
	rdma_cspr_mid_y_table->MCYSCLOF.MCYSCLOF1.bit.MCYSCLOF_2	= spr_cspr_mid_y->of2;
	rdma_cspr_mid_y_table->MCYSCLOF.MCYSCLOF1.bit.MCYSCLOF_3	= spr_cspr_mid_y->of3;
	rdma_cspr_mid_y_table->MCYSCLOF.MCYSCLOF2.bit.MCYSCLOF_4	= spr_cspr_mid_y->of4;
	rdma_cspr_mid_y_table->MCYSCLOF.MCYSCLOF2.bit.MCYSCLOF_5	= spr_cspr_mid_y->of5;
	// write signed data
	im_cnr_set_reg_signed( rdma_cspr_mid_y_table->MCYSCLGA.MCYSCLGA1, union io_cnr_cspr_reg_mcysclga_1, MCYSCLGA_0, spr_cspr_mid_y->gain0 );
	im_cnr_set_reg_signed( rdma_cspr_mid_y_table->MCYSCLGA.MCYSCLGA1, union io_cnr_cspr_reg_mcysclga_1, MCYSCLGA_1, spr_cspr_mid_y->gain1 );
	im_cnr_set_reg_signed( rdma_cspr_mid_y_table->MCYSCLGA.MCYSCLGA1, union io_cnr_cspr_reg_mcysclga_1, MCYSCLGA_2, spr_cspr_mid_y->gain2 );
	im_cnr_set_reg_signed( rdma_cspr_mid_y_table->MCYSCLGA.MCYSCLGA1, union io_cnr_cspr_reg_mcysclga_1, MCYSCLGA_3, spr_cspr_mid_y->gain3 );
	im_cnr_set_reg_signed( rdma_cspr_mid_y_table->MCYSCLGA.MCYSCLGA2, union io_cnr_cspr_reg_mcysclga_2, MCYSCLGA_4, spr_cspr_mid_y->gain4 );
	im_cnr_set_reg_signed( rdma_cspr_mid_y_table->MCYSCLGA.MCYSCLGA2, union io_cnr_cspr_reg_mcysclga_2, MCYSCLGA_5, spr_cspr_mid_y->gain5 );
}

/*
Convert T_IM_CNR_TABLE to T_IM_CNR_RDMA_ADDR_CSPR_MID_CC_Y_TBL
*/
static VOID imCnrConvertRdmaCsprMidCcYTable( const T_IM_CNR_TABLE* cspr_mid_cc_y, T_IM_CNR_RDMA_DATA_CSPR_MID_CC_Y_TBL* rdma_mid_cc_y_table )
{
	rdma_mid_cc_y_table->MCCSCLBD.MCCSCLBD1.bit.MCCSCLBD_1	= cspr_mid_cc_y->bd1;
	rdma_mid_cc_y_table->MCCSCLBD.MCCSCLBD1.bit.MCCSCLBD_2	= cspr_mid_cc_y->bd2;
	rdma_mid_cc_y_table->MCCSCLBD.MCCSCLBD1.bit.MCCSCLBD_3	= cspr_mid_cc_y->bd3;
	rdma_mid_cc_y_table->MCCSCLBD.MCCSCLBD1.bit.MCCSCLBD_4	= cspr_mid_cc_y->bd4;
	rdma_mid_cc_y_table->MCCSCLBD.MCCSCLBD2.bit.MCCSCLBD_5	= cspr_mid_cc_y->bd5;
	rdma_mid_cc_y_table->MCCSCLOF.MCCSCLOF1.bit.MCCSCLOF_0	= cspr_mid_cc_y->of0;
	rdma_mid_cc_y_table->MCCSCLOF.MCCSCLOF1.bit.MCCSCLOF_1	= cspr_mid_cc_y->of1;
	rdma_mid_cc_y_table->MCCSCLOF.MCCSCLOF1.bit.MCCSCLOF_2	= cspr_mid_cc_y->of2;
	rdma_mid_cc_y_table->MCCSCLOF.MCCSCLOF1.bit.MCCSCLOF_3	= cspr_mid_cc_y->of3;
	rdma_mid_cc_y_table->MCCSCLOF.MCCSCLOF2.bit.MCCSCLOF_4	= cspr_mid_cc_y->of4;
	rdma_mid_cc_y_table->MCCSCLOF.MCCSCLOF2.bit.MCCSCLOF_5	= cspr_mid_cc_y->of5;
	// write signed data
	im_cnr_set_reg_signed( rdma_mid_cc_y_table->MCCSCLGA.MCCSCLGA1, union io_cnr_cspr_reg_mccsclga_1, MCCSCLGA_0, cspr_mid_cc_y->gain0 );
	im_cnr_set_reg_signed( rdma_mid_cc_y_table->MCCSCLGA.MCCSCLGA1, union io_cnr_cspr_reg_mccsclga_1, MCCSCLGA_1, cspr_mid_cc_y->gain1 );
	im_cnr_set_reg_signed( rdma_mid_cc_y_table->MCCSCLGA.MCCSCLGA1, union io_cnr_cspr_reg_mccsclga_1, MCCSCLGA_2, cspr_mid_cc_y->gain2 );
	im_cnr_set_reg_signed( rdma_mid_cc_y_table->MCCSCLGA.MCCSCLGA1, union io_cnr_cspr_reg_mccsclga_1, MCCSCLGA_3, cspr_mid_cc_y->gain3 );
	im_cnr_set_reg_signed( rdma_mid_cc_y_table->MCCSCLGA.MCCSCLGA2, union io_cnr_cspr_reg_mccsclga_2, MCCSCLGA_4, cspr_mid_cc_y->gain4 );
	im_cnr_set_reg_signed( rdma_mid_cc_y_table->MCCSCLGA.MCCSCLGA2, union io_cnr_cspr_reg_mccsclga_2, MCCSCLGA_5, cspr_mid_cc_y->gain5 );
}

/*
Convert T_IM_CNR_TABLE to T_IM_CNR_RDMA_ADDR_CSPR_MID_CC_C_TBL
*/
static VOID imCnrConvertRdmaCsprMidCcCTable( const T_IM_CNR_TABLE* cspr_mid_cc_c, T_IM_CNR_RDMA_DATA_CSPR_MID_CC_C_TBL* rdma_mid_cc_c_table )
{
	rdma_mid_cc_c_table->MCSSCLBD.MCSSCLBD1.bit.MCSSCLBD_1	= cspr_mid_cc_c->bd1;
	rdma_mid_cc_c_table->MCSSCLBD.MCSSCLBD1.bit.MCSSCLBD_2	= cspr_mid_cc_c->bd2;
	rdma_mid_cc_c_table->MCSSCLBD.MCSSCLBD1.bit.MCSSCLBD_3	= cspr_mid_cc_c->bd3;
	rdma_mid_cc_c_table->MCSSCLBD.MCSSCLBD1.bit.MCSSCLBD_4	= cspr_mid_cc_c->bd4;
	rdma_mid_cc_c_table->MCSSCLBD.MCSSCLBD2.bit.MCSSCLBD_5	= cspr_mid_cc_c->bd5;
	rdma_mid_cc_c_table->MCSSCLOF.MCSSCLOF1.bit.MCSSCLOF_0	= cspr_mid_cc_c->of0;
	rdma_mid_cc_c_table->MCSSCLOF.MCSSCLOF1.bit.MCSSCLOF_1	= cspr_mid_cc_c->of1;
	rdma_mid_cc_c_table->MCSSCLOF.MCSSCLOF1.bit.MCSSCLOF_2	= cspr_mid_cc_c->of2;
	rdma_mid_cc_c_table->MCSSCLOF.MCSSCLOF1.bit.MCSSCLOF_3	= cspr_mid_cc_c->of3;
	rdma_mid_cc_c_table->MCSSCLOF.MCSSCLOF2.bit.MCSSCLOF_4	= cspr_mid_cc_c->of4;
	rdma_mid_cc_c_table->MCSSCLOF.MCSSCLOF2.bit.MCSSCLOF_5	= cspr_mid_cc_c->of5;
	// write signed data
	im_cnr_set_reg_signed( rdma_mid_cc_c_table->MCSSCLGA.MCSSCLGA1, union io_cnr_cspr_reg_mcssclga_1, MCSSCLGA_0, cspr_mid_cc_c->gain0 );
	im_cnr_set_reg_signed( rdma_mid_cc_c_table->MCSSCLGA.MCSSCLGA1, union io_cnr_cspr_reg_mcssclga_1, MCSSCLGA_1, cspr_mid_cc_c->gain1 );
	im_cnr_set_reg_signed( rdma_mid_cc_c_table->MCSSCLGA.MCSSCLGA1, union io_cnr_cspr_reg_mcssclga_1, MCSSCLGA_2, cspr_mid_cc_c->gain2 );
	im_cnr_set_reg_signed( rdma_mid_cc_c_table->MCSSCLGA.MCSSCLGA1, union io_cnr_cspr_reg_mcssclga_1, MCSSCLGA_3, cspr_mid_cc_c->gain3 );
	im_cnr_set_reg_signed( rdma_mid_cc_c_table->MCSSCLGA.MCSSCLGA2, union io_cnr_cspr_reg_mcssclga_2, MCSSCLGA_4, cspr_mid_cc_c->gain4 );
	im_cnr_set_reg_signed( rdma_mid_cc_c_table->MCSSCLGA.MCSSCLGA2, union io_cnr_cspr_reg_mcssclga_2, MCSSCLGA_5, cspr_mid_cc_c->gain5 );
}

/*
Convert T_IM_CNR_TABLE to T_IM_CNR_RDMA_DATA_CSPR_LOW_Y_TBL
*/
static VOID imCnrConvertRdmaCsprLowYTable( const T_IM_CNR_TABLE* spr_cspr_low_y, T_IM_CNR_RDMA_DATA_CSPR_LOW_Y_TBL* rdma_cspr_low_y_table )
{
	rdma_cspr_low_y_table->LCYSCLBD.LCYSCLBD1.bit.LCYSCLBD_1	= spr_cspr_low_y->bd1;
	rdma_cspr_low_y_table->LCYSCLBD.LCYSCLBD1.bit.LCYSCLBD_2	= spr_cspr_low_y->bd2;
	rdma_cspr_low_y_table->LCYSCLBD.LCYSCLBD1.bit.LCYSCLBD_3	= spr_cspr_low_y->bd3;
	rdma_cspr_low_y_table->LCYSCLBD.LCYSCLBD1.bit.LCYSCLBD_4	= spr_cspr_low_y->bd4;
	rdma_cspr_low_y_table->LCYSCLBD.LCYSCLBD2.bit.LCYSCLBD_5	= spr_cspr_low_y->bd5;
	rdma_cspr_low_y_table->LCYSCLOF.LCYSCLOF1.bit.LCYSCLOF_0	= spr_cspr_low_y->of0;
	rdma_cspr_low_y_table->LCYSCLOF.LCYSCLOF1.bit.LCYSCLOF_1	= spr_cspr_low_y->of1;
	rdma_cspr_low_y_table->LCYSCLOF.LCYSCLOF1.bit.LCYSCLOF_2	= spr_cspr_low_y->of2;
	rdma_cspr_low_y_table->LCYSCLOF.LCYSCLOF1.bit.LCYSCLOF_3	= spr_cspr_low_y->of3;
	rdma_cspr_low_y_table->LCYSCLOF.LCYSCLOF2.bit.LCYSCLOF_4	= spr_cspr_low_y->of4;
	rdma_cspr_low_y_table->LCYSCLOF.LCYSCLOF2.bit.LCYSCLOF_5	= spr_cspr_low_y->of5;
	// write signed data
	im_cnr_set_reg_signed( rdma_cspr_low_y_table->LCYSCLGA.LCYSCLGA1, union io_cnr_cspr_reg_lcysclga_1, LCYSCLGA_0, spr_cspr_low_y->gain0 );
	im_cnr_set_reg_signed( rdma_cspr_low_y_table->LCYSCLGA.LCYSCLGA1, union io_cnr_cspr_reg_lcysclga_1, LCYSCLGA_1, spr_cspr_low_y->gain1 );
	im_cnr_set_reg_signed( rdma_cspr_low_y_table->LCYSCLGA.LCYSCLGA1, union io_cnr_cspr_reg_lcysclga_1, LCYSCLGA_2, spr_cspr_low_y->gain2 );
	im_cnr_set_reg_signed( rdma_cspr_low_y_table->LCYSCLGA.LCYSCLGA1, union io_cnr_cspr_reg_lcysclga_1, LCYSCLGA_3, spr_cspr_low_y->gain3 );
	im_cnr_set_reg_signed( rdma_cspr_low_y_table->LCYSCLGA.LCYSCLGA2, union io_cnr_cspr_reg_lcysclga_2, LCYSCLGA_4, spr_cspr_low_y->gain4 );
	im_cnr_set_reg_signed( rdma_cspr_low_y_table->LCYSCLGA.LCYSCLGA2, union io_cnr_cspr_reg_lcysclga_2, LCYSCLGA_5, spr_cspr_low_y->gain5 );
}

/*
Convert T_IM_CNR_TABLE to T_IM_CNR_RDMA_ADDR_CSPR_LOW_CC_Y_TBL
*/
static VOID imCnrConvertRdmaCsprLowCcYTable( const T_IM_CNR_TABLE* cspr_low_cc_y, T_IM_CNR_RDMA_DATA_CSPR_LOW_CC_Y_TBL* rdma_low_cc_y_table )
{
	rdma_low_cc_y_table->LCCSCLBD.LCCSCLBD1.bit.LCCSCLBD_1	= cspr_low_cc_y->bd1;
	rdma_low_cc_y_table->LCCSCLBD.LCCSCLBD1.bit.LCCSCLBD_2	= cspr_low_cc_y->bd2;
	rdma_low_cc_y_table->LCCSCLBD.LCCSCLBD1.bit.LCCSCLBD_3	= cspr_low_cc_y->bd3;
	rdma_low_cc_y_table->LCCSCLBD.LCCSCLBD1.bit.LCCSCLBD_4	= cspr_low_cc_y->bd4;
	rdma_low_cc_y_table->LCCSCLBD.LCCSCLBD2.bit.LCCSCLBD_5	= cspr_low_cc_y->bd5;
	rdma_low_cc_y_table->LCCSCLOF.LCCSCLOF1.bit.LCCSCLOF_0	= cspr_low_cc_y->of0;
	rdma_low_cc_y_table->LCCSCLOF.LCCSCLOF1.bit.LCCSCLOF_1	= cspr_low_cc_y->of1;
	rdma_low_cc_y_table->LCCSCLOF.LCCSCLOF1.bit.LCCSCLOF_2	= cspr_low_cc_y->of2;
	rdma_low_cc_y_table->LCCSCLOF.LCCSCLOF1.bit.LCCSCLOF_3	= cspr_low_cc_y->of3;
	rdma_low_cc_y_table->LCCSCLOF.LCCSCLOF2.bit.LCCSCLOF_4	= cspr_low_cc_y->of4;
	rdma_low_cc_y_table->LCCSCLOF.LCCSCLOF2.bit.LCCSCLOF_5	= cspr_low_cc_y->of5;
	// write signed data
	im_cnr_set_reg_signed( rdma_low_cc_y_table->LCCSCLGA.LCCSCLGA1, union io_cnr_cspr_reg_lccsclga_1, LCCSCLGA_0, cspr_low_cc_y->gain0 );
	im_cnr_set_reg_signed( rdma_low_cc_y_table->LCCSCLGA.LCCSCLGA1, union io_cnr_cspr_reg_lccsclga_1, LCCSCLGA_1, cspr_low_cc_y->gain1 );
	im_cnr_set_reg_signed( rdma_low_cc_y_table->LCCSCLGA.LCCSCLGA1, union io_cnr_cspr_reg_lccsclga_1, LCCSCLGA_2, cspr_low_cc_y->gain2 );
	im_cnr_set_reg_signed( rdma_low_cc_y_table->LCCSCLGA.LCCSCLGA1, union io_cnr_cspr_reg_lccsclga_1, LCCSCLGA_3, cspr_low_cc_y->gain3 );
	im_cnr_set_reg_signed( rdma_low_cc_y_table->LCCSCLGA.LCCSCLGA2, union io_cnr_cspr_reg_lccsclga_2, LCCSCLGA_4, cspr_low_cc_y->gain4 );
	im_cnr_set_reg_signed( rdma_low_cc_y_table->LCCSCLGA.LCCSCLGA2, union io_cnr_cspr_reg_lccsclga_2, LCCSCLGA_5, cspr_low_cc_y->gain5 );
}

/*
Convert T_IM_CNR_TABLE to T_IM_CNR_RDMA_ADDR_CSPR_LOW_CC_C_TBL
*/
static VOID imCnrConvertRdmaCsprLowCcCTable( const T_IM_CNR_TABLE* cspr_low_cc_c, T_IM_CNR_RDMA_DATA_CSPR_LOW_CC_C_TBL* rdma_low_cc_c_table )
{
	rdma_low_cc_c_table->LCSSCLBD.LCSSCLBD1.bit.LCSSCLBD_1	= cspr_low_cc_c->bd1;
	rdma_low_cc_c_table->LCSSCLBD.LCSSCLBD1.bit.LCSSCLBD_2	= cspr_low_cc_c->bd2;
	rdma_low_cc_c_table->LCSSCLBD.LCSSCLBD1.bit.LCSSCLBD_3	= cspr_low_cc_c->bd3;
	rdma_low_cc_c_table->LCSSCLBD.LCSSCLBD1.bit.LCSSCLBD_4	= cspr_low_cc_c->bd4;
	rdma_low_cc_c_table->LCSSCLBD.LCSSCLBD2.bit.LCSSCLBD_5	= cspr_low_cc_c->bd5;
	rdma_low_cc_c_table->LCSSCLOF.LCSSCLOF1.bit.LCSSCLOF_0	= cspr_low_cc_c->of0;
	rdma_low_cc_c_table->LCSSCLOF.LCSSCLOF1.bit.LCSSCLOF_1	= cspr_low_cc_c->of1;
	rdma_low_cc_c_table->LCSSCLOF.LCSSCLOF1.bit.LCSSCLOF_2	= cspr_low_cc_c->of2;
	rdma_low_cc_c_table->LCSSCLOF.LCSSCLOF1.bit.LCSSCLOF_3	= cspr_low_cc_c->of3;
	rdma_low_cc_c_table->LCSSCLOF.LCSSCLOF2.bit.LCSSCLOF_4	= cspr_low_cc_c->of4;
	rdma_low_cc_c_table->LCSSCLOF.LCSSCLOF2.bit.LCSSCLOF_5	= cspr_low_cc_c->of5;
	// write signed data
	im_cnr_set_reg_signed( rdma_low_cc_c_table->LCSSCLGA.LCSSCLGA1, union io_cnr_cspr_reg_lcssclga_1, LCSSCLGA_0, cspr_low_cc_c->gain0 );
	im_cnr_set_reg_signed( rdma_low_cc_c_table->LCSSCLGA.LCSSCLGA1, union io_cnr_cspr_reg_lcssclga_1, LCSSCLGA_1, cspr_low_cc_c->gain1 );
	im_cnr_set_reg_signed( rdma_low_cc_c_table->LCSSCLGA.LCSSCLGA1, union io_cnr_cspr_reg_lcssclga_1, LCSSCLGA_2, cspr_low_cc_c->gain2 );
	im_cnr_set_reg_signed( rdma_low_cc_c_table->LCSSCLGA.LCSSCLGA1, union io_cnr_cspr_reg_lcssclga_1, LCSSCLGA_3, cspr_low_cc_c->gain3 );
	im_cnr_set_reg_signed( rdma_low_cc_c_table->LCSSCLGA.LCSSCLGA2, union io_cnr_cspr_reg_lcssclga_2, LCSSCLGA_4, cspr_low_cc_c->gain4 );
	im_cnr_set_reg_signed( rdma_low_cc_c_table->LCSSCLGA.LCSSCLGA2, union io_cnr_cspr_reg_lcssclga_2, LCSSCLGA_5, cspr_low_cc_c->gain5 );
}

/*
Convert T_IM_CNR_TABLE to T_IM_CNR_RDMA_ADDR_CSPR_EDGE_TBL
*/
static VOID imCnrConvertRdmaCsprEdgeTable( const T_IM_CNR_TABLE* cspr_edge, T_IM_CNR_RDMA_DATA_CSPR_EDGE_TBL* rdma_edge_table )
{
	rdma_edge_table->CESCLBD.CESCLBD1.bit.CESCLBD_1	= cspr_edge->bd1;
	rdma_edge_table->CESCLBD.CESCLBD1.bit.CESCLBD_2	= cspr_edge->bd2;
	rdma_edge_table->CESCLBD.CESCLBD1.bit.CESCLBD_3	= cspr_edge->bd3;
	rdma_edge_table->CESCLBD.CESCLBD1.bit.CESCLBD_4	= cspr_edge->bd4;
	rdma_edge_table->CESCLBD.CESCLBD2.bit.CESCLBD_5	= cspr_edge->bd5;
	rdma_edge_table->CESCLOF.CESCLOF1.bit.CESCLOF_0	= cspr_edge->of0;
	rdma_edge_table->CESCLOF.CESCLOF1.bit.CESCLOF_1	= cspr_edge->of1;
	rdma_edge_table->CESCLOF.CESCLOF1.bit.CESCLOF_2	= cspr_edge->of2;
	rdma_edge_table->CESCLOF.CESCLOF1.bit.CESCLOF_3	= cspr_edge->of3;
	rdma_edge_table->CESCLOF.CESCLOF2.bit.CESCLOF_4	= cspr_edge->of4;
	rdma_edge_table->CESCLOF.CESCLOF2.bit.CESCLOF_5	= cspr_edge->of5;
	// write signed data
	im_cnr_set_reg_signed( rdma_edge_table->CESCLGA.CESCLGA1, union io_cnr_cspr_reg_cesclga_1, CESCLGA_0, cspr_edge->gain0 );
	im_cnr_set_reg_signed( rdma_edge_table->CESCLGA.CESCLGA1, union io_cnr_cspr_reg_cesclga_1, CESCLGA_1, cspr_edge->gain1 );
	im_cnr_set_reg_signed( rdma_edge_table->CESCLGA.CESCLGA1, union io_cnr_cspr_reg_cesclga_1, CESCLGA_2, cspr_edge->gain2 );
	im_cnr_set_reg_signed( rdma_edge_table->CESCLGA.CESCLGA1, union io_cnr_cspr_reg_cesclga_1, CESCLGA_3, cspr_edge->gain3 );
	im_cnr_set_reg_signed( rdma_edge_table->CESCLGA.CESCLGA2, union io_cnr_cspr_reg_cesclga_2, CESCLGA_4, cspr_edge->gain4 );
	im_cnr_set_reg_signed( rdma_edge_table->CESCLGA.CESCLGA2, union io_cnr_cspr_reg_cesclga_2, CESCLGA_5, cspr_edge->gain5 );
}

/*
Convert T_IM_CNR_HUE_SPEC_TABLE to T_IM_CNR_RDMA_ADDR_CSPR_HUE_TBL
*/
static VOID imCnrConvertRdmaCsprHueTable( const T_IM_CNR_HUE_SPEC_TABLE* cspr_hue, T_IM_CNR_RDMA_DATA_CSPR_HUE_TBL* rdma_hue_table )
{
	// write signed data
	im_cnr_set_reg_signed( rdma_hue_table->CPHPT, union io_cnr_cspr_reg_cphpt, CDCB, cspr_hue->cd_cb );
	im_cnr_set_reg_signed( rdma_hue_table->CPHPT, union io_cnr_cspr_reg_cphpt, CDCR, cspr_hue->cd_cr );
	rdma_hue_table->CPHPTK.bit.KCB	= cspr_hue->k_cb;
	rdma_hue_table->CPHPTK.bit.KCR	= cspr_hue->k_cr;
	rdma_hue_table->CDSCLBD.CDSCLBD1.bit.CDSCLBD_1	= cspr_hue->bd1;
	rdma_hue_table->CDSCLBD.CDSCLBD1.bit.CDSCLBD_2	= cspr_hue->bd2;
	rdma_hue_table->CDSCLBD.CDSCLBD2.bit.CDSCLBD_3	= cspr_hue->bd3;
	rdma_hue_table->CDSCLBD.CDSCLBD2.bit.CDSCLBD_4	= cspr_hue->bd4;
	rdma_hue_table->CDSCLBD.CDSCLBD3.bit.CDSCLBD_5	= cspr_hue->bd5;
	rdma_hue_table->CDSCLOF.CDSCLOF1.bit.CDSCLOF_0	= cspr_hue->of0;
	rdma_hue_table->CDSCLOF.CDSCLOF1.bit.CDSCLOF_1	= cspr_hue->of1;
	rdma_hue_table->CDSCLOF.CDSCLOF2.bit.CDSCLOF_2	= cspr_hue->of2;
	rdma_hue_table->CDSCLOF.CDSCLOF2.bit.CDSCLOF_3	= cspr_hue->of3;
	rdma_hue_table->CDSCLOF.CDSCLOF3.bit.CDSCLOF_4	= cspr_hue->of4;
	rdma_hue_table->CDSCLOF.CDSCLOF3.bit.CDSCLOF_5	= cspr_hue->of5;
	// write signed data
	im_cnr_set_reg_signed( rdma_hue_table->CDSCLGA.CDSCLGA1, union io_cnr_cspr_reg_cdsclga_1, CDSCLGA_0, cspr_hue->gain0 );
	im_cnr_set_reg_signed( rdma_hue_table->CDSCLGA.CDSCLGA1, union io_cnr_cspr_reg_cdsclga_1, CDSCLGA_1, cspr_hue->gain1 );
	im_cnr_set_reg_signed( rdma_hue_table->CDSCLGA.CDSCLGA2, union io_cnr_cspr_reg_cdsclga_2, CDSCLGA_2, cspr_hue->gain2 );
	im_cnr_set_reg_signed( rdma_hue_table->CDSCLGA.CDSCLGA2, union io_cnr_cspr_reg_cdsclga_2, CDSCLGA_3, cspr_hue->gain3 );
	im_cnr_set_reg_signed( rdma_hue_table->CDSCLGA.CDSCLGA3, union io_cnr_cspr_reg_cdsclga_3, CDSCLGA_4, cspr_hue->gain4 );
	im_cnr_set_reg_signed( rdma_hue_table->CDSCLGA.CDSCLGA3, union io_cnr_cspr_reg_cdsclga_3, CDSCLGA_5, cspr_hue->gain5 );
}

/*
Convert T_IM_CNR_CTRL_CC_SRC_DST to T_IM_CNR_RDMA_DATA_SPRS_CC_TBL
*/
static VOID imCnrConvertRdmaCsprSprsCc( const T_IM_CNR_CTRL_CC_SRC_DST* sprs_ctrl, T_IM_CNR_RDMA_DATA_SPRS_CC_TBL* rdma_sprs_ctrl )
{
	rdma_sprs_ctrl->SPRS.bit.SPRS = sprs_ctrl->enable;
	// write signed data
	im_cnr_set_reg_signed( rdma_sprs_ctrl->SPRSCBBD.SPRSCBBD1, union io_cnr_cspr_reg_sprscbbd_1, SPRSCBBD_1, sprs_ctrl->cb_table.bd1 );
	im_cnr_set_reg_signed( rdma_sprs_ctrl->SPRSCBBD.SPRSCBBD1, union io_cnr_cspr_reg_sprscbbd_1, SPRSCBBD_2, sprs_ctrl->cb_table.bd2 );
	im_cnr_set_reg_signed( rdma_sprs_ctrl->SPRSCBBD.SPRSCBBD1, union io_cnr_cspr_reg_sprscbbd_1, SPRSCBBD_3, sprs_ctrl->cb_table.bd3 );
	im_cnr_set_reg_signed( rdma_sprs_ctrl->SPRSCBBD.SPRSCBBD1, union io_cnr_cspr_reg_sprscbbd_1, SPRSCBBD_4, sprs_ctrl->cb_table.bd4 );
	im_cnr_set_reg_signed( rdma_sprs_ctrl->SPRSCBBD.SPRSCBBD2, union io_cnr_cspr_reg_sprscbbd_2, SPRSCBBD_5, sprs_ctrl->cb_table.bd5 );
	im_cnr_set_reg_signed( rdma_sprs_ctrl->SPRSCBOF.SPRSCBOF1, union io_cnr_cspr_reg_sprscbof_1, SPRSCBOF_0, sprs_ctrl->cb_table.of0 );
	im_cnr_set_reg_signed( rdma_sprs_ctrl->SPRSCBOF.SPRSCBOF1, union io_cnr_cspr_reg_sprscbof_1, SPRSCBOF_1, sprs_ctrl->cb_table.of1 );
	im_cnr_set_reg_signed( rdma_sprs_ctrl->SPRSCBOF.SPRSCBOF1, union io_cnr_cspr_reg_sprscbof_1, SPRSCBOF_2, sprs_ctrl->cb_table.of2 );
	im_cnr_set_reg_signed( rdma_sprs_ctrl->SPRSCBOF.SPRSCBOF1, union io_cnr_cspr_reg_sprscbof_1, SPRSCBOF_3, sprs_ctrl->cb_table.of3 );
	im_cnr_set_reg_signed( rdma_sprs_ctrl->SPRSCBOF.SPRSCBOF2, union io_cnr_cspr_reg_sprscbof_2, SPRSCBOF_4, sprs_ctrl->cb_table.of4 );
	im_cnr_set_reg_signed( rdma_sprs_ctrl->SPRSCBOF.SPRSCBOF2, union io_cnr_cspr_reg_sprscbof_2, SPRSCBOF_5, sprs_ctrl->cb_table.of5 );
	im_cnr_set_reg_signed( rdma_sprs_ctrl->SPRSCBGA.SPRSCBGA1, union io_cnr_cspr_reg_sprscbga_1, SPRSCBGA_0, sprs_ctrl->cb_table.gain0 );
	im_cnr_set_reg_signed( rdma_sprs_ctrl->SPRSCBGA.SPRSCBGA1, union io_cnr_cspr_reg_sprscbga_1, SPRSCBGA_1, sprs_ctrl->cb_table.gain1 );
	im_cnr_set_reg_signed( rdma_sprs_ctrl->SPRSCBGA.SPRSCBGA2, union io_cnr_cspr_reg_sprscbga_2, SPRSCBGA_2, sprs_ctrl->cb_table.gain2 );
	im_cnr_set_reg_signed( rdma_sprs_ctrl->SPRSCBGA.SPRSCBGA2, union io_cnr_cspr_reg_sprscbga_2, SPRSCBGA_3, sprs_ctrl->cb_table.gain3 );
	im_cnr_set_reg_signed( rdma_sprs_ctrl->SPRSCBGA.SPRSCBGA3, union io_cnr_cspr_reg_sprscbga_3, SPRSCBGA_4, sprs_ctrl->cb_table.gain4 );
	im_cnr_set_reg_signed( rdma_sprs_ctrl->SPRSCBGA.SPRSCBGA3, union io_cnr_cspr_reg_sprscbga_3, SPRSCBGA_5, sprs_ctrl->cb_table.gain5 );

	im_cnr_set_reg_signed( rdma_sprs_ctrl->SPRSCRBD.SPRSCRBD1, union io_cnr_cspr_reg_sprscrbd_1, SPRSCRBD_1, sprs_ctrl->cr_table.bd1 );
	im_cnr_set_reg_signed( rdma_sprs_ctrl->SPRSCRBD.SPRSCRBD1, union io_cnr_cspr_reg_sprscrbd_1, SPRSCRBD_2, sprs_ctrl->cr_table.bd2 );
	im_cnr_set_reg_signed( rdma_sprs_ctrl->SPRSCRBD.SPRSCRBD1, union io_cnr_cspr_reg_sprscrbd_1, SPRSCRBD_3, sprs_ctrl->cr_table.bd3 );
	im_cnr_set_reg_signed( rdma_sprs_ctrl->SPRSCRBD.SPRSCRBD1, union io_cnr_cspr_reg_sprscrbd_1, SPRSCRBD_4, sprs_ctrl->cr_table.bd4 );
	im_cnr_set_reg_signed( rdma_sprs_ctrl->SPRSCRBD.SPRSCRBD2, union io_cnr_cspr_reg_sprscrbd_2, SPRSCRBD_5, sprs_ctrl->cr_table.bd5 );
	im_cnr_set_reg_signed( rdma_sprs_ctrl->SPRSCROF.SPRSCROF1, union io_cnr_cspr_reg_sprscrof_1, SPRSCROF_0, sprs_ctrl->cr_table.of0 );
	im_cnr_set_reg_signed( rdma_sprs_ctrl->SPRSCROF.SPRSCROF1, union io_cnr_cspr_reg_sprscrof_1, SPRSCROF_1, sprs_ctrl->cr_table.of1 );
	im_cnr_set_reg_signed( rdma_sprs_ctrl->SPRSCROF.SPRSCROF1, union io_cnr_cspr_reg_sprscrof_1, SPRSCROF_2, sprs_ctrl->cr_table.of2 );
	im_cnr_set_reg_signed( rdma_sprs_ctrl->SPRSCROF.SPRSCROF1, union io_cnr_cspr_reg_sprscrof_1, SPRSCROF_3, sprs_ctrl->cr_table.of3 );
	im_cnr_set_reg_signed( rdma_sprs_ctrl->SPRSCROF.SPRSCROF2, union io_cnr_cspr_reg_sprscrof_2, SPRSCROF_4, sprs_ctrl->cr_table.of4 );
	im_cnr_set_reg_signed( rdma_sprs_ctrl->SPRSCROF.SPRSCROF2, union io_cnr_cspr_reg_sprscrof_2, SPRSCROF_5, sprs_ctrl->cr_table.of5 );
	im_cnr_set_reg_signed( rdma_sprs_ctrl->SPRSCRGA.SPRSCRGA1, union io_cnr_cspr_reg_sprscrga_1, SPRSCRGA_0, sprs_ctrl->cr_table.gain0 );
	im_cnr_set_reg_signed( rdma_sprs_ctrl->SPRSCRGA.SPRSCRGA1, union io_cnr_cspr_reg_sprscrga_1, SPRSCRGA_1, sprs_ctrl->cr_table.gain1 );
	im_cnr_set_reg_signed( rdma_sprs_ctrl->SPRSCRGA.SPRSCRGA2, union io_cnr_cspr_reg_sprscrga_2, SPRSCRGA_2, sprs_ctrl->cr_table.gain2 );
	im_cnr_set_reg_signed( rdma_sprs_ctrl->SPRSCRGA.SPRSCRGA2, union io_cnr_cspr_reg_sprscrga_2, SPRSCRGA_3, sprs_ctrl->cr_table.gain3 );
	im_cnr_set_reg_signed( rdma_sprs_ctrl->SPRSCRGA.SPRSCRGA3, union io_cnr_cspr_reg_sprscrga_3, SPRSCRGA_4, sprs_ctrl->cr_table.gain4 );
	im_cnr_set_reg_signed( rdma_sprs_ctrl->SPRSCRGA.SPRSCRGA3, union io_cnr_cspr_reg_sprscrga_3, SPRSCRGA_5, sprs_ctrl->cr_table.gain5 );
}

/*
Convert T_IM_CNR_CTRL_CC_SRC_DST to T_IM_CNR_RDMA_DATA_SPRD_CC_TBL
*/
static VOID imCnrConvertRdmaCsprSprdCc( const T_IM_CNR_CTRL_CC_SRC_DST* sprd_ctrl, T_IM_CNR_RDMA_DATA_SPRD_CC_TBL* rdma_sprd_ctrl )
{
	rdma_sprd_ctrl->SPRD.bit.SPRD = sprd_ctrl->enable;
	// write signed data
	im_cnr_set_reg_signed( rdma_sprd_ctrl->SPRDCBBD.SPRDCBBD1, union io_cnr_cspr_reg_sprdcbbd_1, SPRDCBBD_1, sprd_ctrl->cb_table.bd1 );
	im_cnr_set_reg_signed( rdma_sprd_ctrl->SPRDCBBD.SPRDCBBD1, union io_cnr_cspr_reg_sprdcbbd_1, SPRDCBBD_2, sprd_ctrl->cb_table.bd2 );
	im_cnr_set_reg_signed( rdma_sprd_ctrl->SPRDCBBD.SPRDCBBD1, union io_cnr_cspr_reg_sprdcbbd_1, SPRDCBBD_3, sprd_ctrl->cb_table.bd3 );
	im_cnr_set_reg_signed( rdma_sprd_ctrl->SPRDCBBD.SPRDCBBD1, union io_cnr_cspr_reg_sprdcbbd_1, SPRDCBBD_4, sprd_ctrl->cb_table.bd4 );
	im_cnr_set_reg_signed( rdma_sprd_ctrl->SPRDCBBD.SPRDCBBD2, union io_cnr_cspr_reg_sprdcbbd_2, SPRDCBBD_5, sprd_ctrl->cb_table.bd5 );
	im_cnr_set_reg_signed( rdma_sprd_ctrl->SPRDCBOF.SPRDCBOF1, union io_cnr_cspr_reg_sprdcbof_1, SPRDCBOF_0, sprd_ctrl->cb_table.of0 );
	im_cnr_set_reg_signed( rdma_sprd_ctrl->SPRDCBOF.SPRDCBOF1, union io_cnr_cspr_reg_sprdcbof_1, SPRDCBOF_1, sprd_ctrl->cb_table.of1 );
	im_cnr_set_reg_signed( rdma_sprd_ctrl->SPRDCBOF.SPRDCBOF1, union io_cnr_cspr_reg_sprdcbof_1, SPRDCBOF_2, sprd_ctrl->cb_table.of2 );
	im_cnr_set_reg_signed( rdma_sprd_ctrl->SPRDCBOF.SPRDCBOF1, union io_cnr_cspr_reg_sprdcbof_1, SPRDCBOF_3, sprd_ctrl->cb_table.of3 );
	im_cnr_set_reg_signed( rdma_sprd_ctrl->SPRDCBOF.SPRDCBOF2, union io_cnr_cspr_reg_sprdcbof_2, SPRDCBOF_4, sprd_ctrl->cb_table.of4 );
	im_cnr_set_reg_signed( rdma_sprd_ctrl->SPRDCBOF.SPRDCBOF2, union io_cnr_cspr_reg_sprdcbof_2, SPRDCBOF_5, sprd_ctrl->cb_table.of5 );
	im_cnr_set_reg_signed( rdma_sprd_ctrl->SPRDCBGA.SPRDCBGA1, union io_cnr_cspr_reg_sprdcbga_1, SPRDCBGA_0, sprd_ctrl->cb_table.gain0 );
	im_cnr_set_reg_signed( rdma_sprd_ctrl->SPRDCBGA.SPRDCBGA1, union io_cnr_cspr_reg_sprdcbga_1, SPRDCBGA_1, sprd_ctrl->cb_table.gain1 );
	im_cnr_set_reg_signed( rdma_sprd_ctrl->SPRDCBGA.SPRDCBGA2, union io_cnr_cspr_reg_sprdcbga_2, SPRDCBGA_2, sprd_ctrl->cb_table.gain2 );
	im_cnr_set_reg_signed( rdma_sprd_ctrl->SPRDCBGA.SPRDCBGA2, union io_cnr_cspr_reg_sprdcbga_2, SPRDCBGA_3, sprd_ctrl->cb_table.gain3 );
	im_cnr_set_reg_signed( rdma_sprd_ctrl->SPRDCBGA.SPRDCBGA3, union io_cnr_cspr_reg_sprdcbga_3, SPRDCBGA_4, sprd_ctrl->cb_table.gain4 );
	im_cnr_set_reg_signed( rdma_sprd_ctrl->SPRDCBGA.SPRDCBGA3, union io_cnr_cspr_reg_sprdcbga_3, SPRDCBGA_5, sprd_ctrl->cb_table.gain5 );

	im_cnr_set_reg_signed( rdma_sprd_ctrl->SPRDCRBD.SPRDCRBD1, union io_cnr_cspr_reg_sprdcrbd_1, SPRDCRBD_1, sprd_ctrl->cr_table.bd1 );
	im_cnr_set_reg_signed( rdma_sprd_ctrl->SPRDCRBD.SPRDCRBD1, union io_cnr_cspr_reg_sprdcrbd_1, SPRDCRBD_2, sprd_ctrl->cr_table.bd2 );
	im_cnr_set_reg_signed( rdma_sprd_ctrl->SPRDCRBD.SPRDCRBD1, union io_cnr_cspr_reg_sprdcrbd_1, SPRDCRBD_3, sprd_ctrl->cr_table.bd3 );
	im_cnr_set_reg_signed( rdma_sprd_ctrl->SPRDCRBD.SPRDCRBD1, union io_cnr_cspr_reg_sprdcrbd_1, SPRDCRBD_4, sprd_ctrl->cr_table.bd4 );
	im_cnr_set_reg_signed( rdma_sprd_ctrl->SPRDCRBD.SPRDCRBD2, union io_cnr_cspr_reg_sprdcrbd_2, SPRDCRBD_5, sprd_ctrl->cr_table.bd5 );
	im_cnr_set_reg_signed( rdma_sprd_ctrl->SPRDCROF.SPRDCROF1, union io_cnr_cspr_reg_sprdcrof_1, SPRDCROF_0, sprd_ctrl->cr_table.of0 );
	im_cnr_set_reg_signed( rdma_sprd_ctrl->SPRDCROF.SPRDCROF1, union io_cnr_cspr_reg_sprdcrof_1, SPRDCROF_1, sprd_ctrl->cr_table.of1 );
	im_cnr_set_reg_signed( rdma_sprd_ctrl->SPRDCROF.SPRDCROF1, union io_cnr_cspr_reg_sprdcrof_1, SPRDCROF_2, sprd_ctrl->cr_table.of2 );
	im_cnr_set_reg_signed( rdma_sprd_ctrl->SPRDCROF.SPRDCROF1, union io_cnr_cspr_reg_sprdcrof_1, SPRDCROF_3, sprd_ctrl->cr_table.of3 );
	im_cnr_set_reg_signed( rdma_sprd_ctrl->SPRDCROF.SPRDCROF2, union io_cnr_cspr_reg_sprdcrof_2, SPRDCROF_4, sprd_ctrl->cr_table.of4 );
	im_cnr_set_reg_signed( rdma_sprd_ctrl->SPRDCROF.SPRDCROF2, union io_cnr_cspr_reg_sprdcrof_2, SPRDCROF_5, sprd_ctrl->cr_table.of5 );
	im_cnr_set_reg_signed( rdma_sprd_ctrl->SPRDCRGA.SPRDCRGA1, union io_cnr_cspr_reg_sprdcrga_1, SPRDCRGA_0, sprd_ctrl->cr_table.gain0 );
	im_cnr_set_reg_signed( rdma_sprd_ctrl->SPRDCRGA.SPRDCRGA1, union io_cnr_cspr_reg_sprdcrga_1, SPRDCRGA_1, sprd_ctrl->cr_table.gain1 );
	im_cnr_set_reg_signed( rdma_sprd_ctrl->SPRDCRGA.SPRDCRGA2, union io_cnr_cspr_reg_sprdcrga_2, SPRDCRGA_2, sprd_ctrl->cr_table.gain2 );
	im_cnr_set_reg_signed( rdma_sprd_ctrl->SPRDCRGA.SPRDCRGA2, union io_cnr_cspr_reg_sprdcrga_2, SPRDCRGA_3, sprd_ctrl->cr_table.gain3 );
	im_cnr_set_reg_signed( rdma_sprd_ctrl->SPRDCRGA.SPRDCRGA3, union io_cnr_cspr_reg_sprdcrga_3, SPRDCRGA_4, sprd_ctrl->cr_table.gain4 );
	im_cnr_set_reg_signed( rdma_sprd_ctrl->SPRDCRGA.SPRDCRGA3, union io_cnr_cspr_reg_sprdcrga_3, SPRDCRGA_5, sprd_ctrl->cr_table.gain5 );
}
#endif

/*----------------------------------------------------------------------*/
/* Global Function														*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
// Nothing Special
//---------------------------- colabo section ----------------------------
/*
CNR(OFL) Set SPR CTRL-C setting parameter information
*/
INT32 Im_CNR_Set_RdmaValue_OFL_Ctrl_C( const T_IM_CNR_CTRL_C* const spr_ctrl_c, T_IM_CNR_RDMA_DATA_CTRL_C* const rdma_ctrl_c )
{
#ifdef CO_PARAM_CHECK
	if( spr_ctrl_c == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OFL_Ctrl_C() Parameter(spr_ctrl_c) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_ctrl_c == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OFL_Ctrl_C() Parameter(rdma_ctrl_c) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_ctrl_c, 0, sizeof(T_IM_CNR_RDMA_DATA_CTRL_C) );
	imCnrConvertRdmaValueCtrlC( spr_ctrl_c, rdma_ctrl_c );
	return D_DDIM_OK;
}

/*
CNR(OTF) Set SPR CTRL-C setting parameter information
*/
INT32 Im_CNR_Set_RdmaValue_OTF_Ctrl_C( const T_IM_CNR_CTRL_C* const spr_ctrl_c, T_IM_CNR_RDMA_DATA_CTRL_C* const rdma_ctrl_c )
{
#ifdef CO_PARAM_CHECK
	if( spr_ctrl_c == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OTF_Ctrl_C() Parameter(spr_ctrl_c) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_ctrl_c == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OTF_Ctrl_C() Parameter(rdma_ctrl_c) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_ctrl_c, 0, sizeof(T_IM_CNR_RDMA_DATA_CTRL_C) );
	imCnrConvertRdmaValueCtrlC( spr_ctrl_c, rdma_ctrl_c );
	return D_DDIM_OK;
}

/*
CNR(OFL) Set CSPR Mid_Y Table setting parameter information
*/
INT32 Im_CNR_Set_RdmaValue_OFL_CSPR_Mid_Y_Table( const T_IM_CNR_TABLE* const spr_cspr_mid_y, T_IM_CNR_RDMA_DATA_CSPR_MID_Y_TBL* const rdma_cspr_mid_y_table )
{
#ifdef CO_PARAM_CHECK
	if( spr_cspr_mid_y == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OFL_CSPR_Mid_Y_Table() Parameter(spr_cspr_mid_y) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_mid_y_table == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OFL_CSPR_Mid_Y_Table() Parameter(rdma_cspr_mid_y_table) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_mid_y_table, 0, sizeof(T_IM_CNR_RDMA_DATA_CSPR_MID_Y_TBL) );
	imCnrConvertRdmaCsprMidYTable( spr_cspr_mid_y, rdma_cspr_mid_y_table );
	return D_DDIM_OK;
}

/*
CNR(OTF) Set CSPR Mid_Y Table setting parameter information
*/
INT32 Im_CNR_Set_RdmaValue_OTF_CSPR_Mid_Y_Table( const T_IM_CNR_TABLE* const spr_cspr_mid_y, T_IM_CNR_RDMA_DATA_CSPR_MID_Y_TBL* const rdma_cspr_mid_y_table )
{
#ifdef CO_PARAM_CHECK
	if( spr_cspr_mid_y == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OTF_CSPR_Mid_Y_Table() Parameter(spr_cspr_mid_y) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_mid_y_table == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OTF_CSPR_Mid_Y_Table() Parameter(rdma_cspr_mid_y_table) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_mid_y_table, 0, sizeof(T_IM_CNR_RDMA_DATA_CSPR_MID_Y_TBL) );
	imCnrConvertRdmaCsprMidYTable( spr_cspr_mid_y, rdma_cspr_mid_y_table );
	return D_DDIM_OK;
}

/*
CNR(OFL) Set CSPR Mid_CC_Y Table setting parameter information
*/
INT32 Im_CNR_Set_RdmaValue_OFL_CSPR_Mid_CC_Y_Table( const T_IM_CNR_TABLE* const spr_cspr_mid_cc_y, T_IM_CNR_RDMA_DATA_CSPR_MID_CC_Y_TBL* const rdma_cspr_mid_cc_y_table )
{
#ifdef CO_PARAM_CHECK
	if( spr_cspr_mid_cc_y == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OFL_CSPR_Mid_CC_Y_Table() Parameter(spr_cspr_mid_cc_y) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_mid_cc_y_table == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OFL_CSPR_Mid_CC_Y_Table() Parameter(rdma_cspr_mid_cc_y_table) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_mid_cc_y_table, 0, sizeof(T_IM_CNR_RDMA_DATA_CSPR_MID_CC_Y_TBL) );
	imCnrConvertRdmaCsprMidCcYTable( spr_cspr_mid_cc_y, rdma_cspr_mid_cc_y_table );
	return D_DDIM_OK;
}

/*
CNR(OTF) Set CSPR Mid_CC_Y Table setting parameter information
*/
INT32 Im_CNR_Set_RdmaValue_OTF_CSPR_Mid_CC_Y_Table( const T_IM_CNR_TABLE* const spr_cspr_mid_cc_y, T_IM_CNR_RDMA_DATA_CSPR_MID_CC_Y_TBL* const rdma_cspr_mid_cc_y_table )
{
#ifdef CO_PARAM_CHECK
	if( spr_cspr_mid_cc_y == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OTF_CSPR_Mid_CC_Y_Table() Parameter(spr_cspr_mid_cc_y) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_mid_cc_y_table == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OTF_CSPR_Mid_CC_Y_Table() Parameter(rdma_cspr_mid_cc_y_table) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_mid_cc_y_table, 0, sizeof(T_IM_CNR_RDMA_DATA_CSPR_MID_CC_Y_TBL) );
	imCnrConvertRdmaCsprMidCcYTable( spr_cspr_mid_cc_y, rdma_cspr_mid_cc_y_table );
	return D_DDIM_OK;
}

/*
CNR(OFL) Set CSPR Mid_CC_C Table setting parameter information
*/
INT32 Im_CNR_Set_RdmaValue_OFL_CSPR_Mid_CC_C_Table( const T_IM_CNR_TABLE* const spr_cspr_mid_cc_c, T_IM_CNR_RDMA_DATA_CSPR_MID_CC_C_TBL* const rdma_cspr_mid_cc_c_table )
{
#ifdef CO_PARAM_CHECK
	if( spr_cspr_mid_cc_c == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OFL_CSPR_Mid_CC_C_Table() Parameter(spr_cspr_mid_cc_c) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_mid_cc_c_table == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OFL_CSPR_Mid_CC_C_Table() Parameter(rdma_cspr_mid_cc_c_table) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_mid_cc_c_table, 0, sizeof(T_IM_CNR_RDMA_DATA_CSPR_MID_CC_C_TBL) );
	imCnrConvertRdmaCsprMidCcCTable( spr_cspr_mid_cc_c, rdma_cspr_mid_cc_c_table );
	return D_DDIM_OK;
}

/*
CNR(OTF) Set CSPR Mid_CC_C Table setting parameter information
*/
INT32 Im_CNR_Set_RdmaValue_OTF_CSPR_Mid_CC_C_Table( const T_IM_CNR_TABLE* const spr_cspr_mid_cc_c, T_IM_CNR_RDMA_DATA_CSPR_MID_CC_C_TBL* const rdma_cspr_mid_cc_c_table )
{
#ifdef CO_PARAM_CHECK
	if( spr_cspr_mid_cc_c == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OTF_CSPR_Mid_CC_C_Table() Parameter(spr_cspr_mid_cc_c) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_mid_cc_c_table == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OTF_CSPR_Mid_CC_C_Table() Parameter(rdma_cspr_mid_cc_c_table) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_mid_cc_c_table, 0, sizeof(T_IM_CNR_RDMA_DATA_CSPR_MID_CC_C_TBL) );
	imCnrConvertRdmaCsprMidCcCTable( spr_cspr_mid_cc_c, rdma_cspr_mid_cc_c_table );
	return D_DDIM_OK;
}

/*
CNR(OFL) Set CSPR Low_Y Table setting parameter information
*/
INT32 Im_CNR_Set_RdmaValue_OFL_CSPR_Low_Y_Table( const T_IM_CNR_TABLE* const spr_cspr_low_y, T_IM_CNR_RDMA_DATA_CSPR_LOW_Y_TBL* const rdma_cspr_low_y_table )
{
#ifdef CO_PARAM_CHECK
	if( spr_cspr_low_y == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OFL_CSPR_Low_Y_Table() Parameter(spr_cspr_low_y) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_low_y_table == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OFL_CSPR_Low_Y_Table() Parameter(rdma_cspr_low_y_table) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_low_y_table, 0, sizeof(T_IM_CNR_RDMA_DATA_CSPR_LOW_Y_TBL) );
	imCnrConvertRdmaCsprLowYTable( spr_cspr_low_y, rdma_cspr_low_y_table );
	return D_DDIM_OK;
}

/*
CNR(OTF) Set CSPR Low_Y Table setting parameter information
*/
INT32 Im_CNR_Set_RdmaValue_OTF_CSPR_Low_Y_Table( const T_IM_CNR_TABLE* const spr_cspr_low_y, T_IM_CNR_RDMA_DATA_CSPR_LOW_Y_TBL* const rdma_cspr_low_y_table )
{
#ifdef CO_PARAM_CHECK
	if( spr_cspr_low_y == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OTF_CSPR_Low_Y_Table() Parameter(spr_cspr_low_y) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_low_y_table == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OTF_CSPR_Low_Y_Table() Parameter(rdma_cspr_low_y_table) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_low_y_table, 0, sizeof(T_IM_CNR_RDMA_DATA_CSPR_LOW_Y_TBL) );
	imCnrConvertRdmaCsprLowYTable( spr_cspr_low_y, rdma_cspr_low_y_table );
	return D_DDIM_OK;
}

/*
CNR(OFL) Set CSPR Low_CC_Y Table setting parameter information
*/
INT32 Im_CNR_Set_RdmaValue_OFL_CSPR_Low_CC_Y_Table( const T_IM_CNR_TABLE* const spr_cspr_low_cc_y, T_IM_CNR_RDMA_DATA_CSPR_LOW_CC_Y_TBL* const rdma_cspr_low_cc_y_table )
{
#ifdef CO_PARAM_CHECK
	if( spr_cspr_low_cc_y == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OFL_CSPR_Low_CC_Y_Table() Parameter(spr_cspr_low_cc_y) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_low_cc_y_table == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OFL_CSPR_Low_CC_Y_Table() Parameter(rdma_cspr_low_cc_y_table) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_low_cc_y_table, 0, sizeof(T_IM_CNR_RDMA_DATA_CSPR_LOW_CC_Y_TBL) );
	imCnrConvertRdmaCsprLowCcYTable( spr_cspr_low_cc_y, rdma_cspr_low_cc_y_table );
	return D_DDIM_OK;
}

/*
CNR(OTF) Set CSPR Low_CC_Y Table setting parameter information
*/
INT32 Im_CNR_Set_RdmaValue_OTF_CSPR_Low_CC_Y_Table( const T_IM_CNR_TABLE* const spr_cspr_low_cc_y, T_IM_CNR_RDMA_DATA_CSPR_LOW_CC_Y_TBL* const rdma_cspr_low_cc_y_table )
{
#ifdef CO_PARAM_CHECK
	if( spr_cspr_low_cc_y == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OTF_CSPR_Low_CC_Y_Table() Parameter(spr_cspr_low_cc_y) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_low_cc_y_table == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OTF_CSPR_Low_CC_Y_Table() Parameter(rdma_cspr_low_cc_y_table) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_low_cc_y_table, 0, sizeof(T_IM_CNR_RDMA_DATA_CSPR_LOW_CC_Y_TBL) );
	imCnrConvertRdmaCsprLowCcYTable( spr_cspr_low_cc_y, rdma_cspr_low_cc_y_table );
	return D_DDIM_OK;
}

/*
CNR(OFL) Set CSPR Low_CC_C Table setting parameter information
*/
INT32 Im_CNR_Set_RdmaValue_OFL_CSPR_Low_CC_C_Table( const T_IM_CNR_TABLE* const spr_cspr_low_cc_c, T_IM_CNR_RDMA_DATA_CSPR_LOW_CC_C_TBL* const rdma_cspr_low_cc_c_table )
{
#ifdef CO_PARAM_CHECK
	if( spr_cspr_low_cc_c == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OFL_CSPR_Low_CC_C_Table() Parameter(spr_cspr_low_cc_c) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_low_cc_c_table == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OFL_CSPR_Low_CC_C_Table() Parameter(rdma_cspr_low_cc_c_table) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_low_cc_c_table, 0, sizeof(T_IM_CNR_RDMA_DATA_CSPR_LOW_CC_C_TBL) );
	imCnrConvertRdmaCsprLowCcCTable( spr_cspr_low_cc_c, rdma_cspr_low_cc_c_table );
	return D_DDIM_OK;
}

/*
CNR(OTF) Set CSPR Low_CC_C Table setting parameter information
*/
INT32 Im_CNR_Set_RdmaValue_OTF_CSPR_Low_CC_C_Table( const T_IM_CNR_TABLE* const spr_cspr_low_cc_c, T_IM_CNR_RDMA_DATA_CSPR_LOW_CC_C_TBL* const rdma_cspr_low_cc_c_table )
{
#ifdef CO_PARAM_CHECK
	if( spr_cspr_low_cc_c == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OTF_CSPR_Low_CC_C_Table() Parameter(spr_cspr_low_cc_c) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_low_cc_c_table == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OTF_CSPR_Low_CC_C_Table() Parameter(rdma_cspr_low_cc_c_table) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_low_cc_c_table, 0, sizeof(T_IM_CNR_RDMA_DATA_CSPR_LOW_CC_C_TBL) );
	imCnrConvertRdmaCsprLowCcCTable( spr_cspr_low_cc_c, rdma_cspr_low_cc_c_table );
	return D_DDIM_OK;
}

/*
CNR(OFL) Set CSPR Edge Table setting parameter information
*/
INT32 Im_CNR_Set_RdmaValue_OFL_CSPR_Edge_Table( const T_IM_CNR_TABLE* const spr_cspr_edge, T_IM_CNR_RDMA_DATA_CSPR_EDGE_TBL* const rdma_cspr_edge_table )
{
#ifdef CO_PARAM_CHECK
	if( spr_cspr_edge == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OFL_CSPR_Edge_Table() Parameter(spr_cspr_edge) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_edge_table == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OFL_CSPR_Edge_Table() Parameter(rdma_cspr_edge_table) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_edge_table, 0, sizeof(T_IM_CNR_RDMA_DATA_CSPR_EDGE_TBL) );
	imCnrConvertRdmaCsprEdgeTable( spr_cspr_edge, rdma_cspr_edge_table );
	return D_DDIM_OK;
}

/*
CNR(OTF) Set CSPR Edge Table setting parameter information
*/
INT32 Im_CNR_Set_RdmaValue_OTF_CSPR_Edge_Table( const T_IM_CNR_TABLE* const spr_cspr_edge, T_IM_CNR_RDMA_DATA_CSPR_EDGE_TBL* const rdma_cspr_edge_table )
{
#ifdef CO_PARAM_CHECK
	if( spr_cspr_edge == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OTF_CSPR_Edge_Table() Parameter(spr_cspr_edge) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_edge_table == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OTF_CSPR_Edge_Table() Parameter(rdma_cspr_edge_table) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_edge_table, 0, sizeof(T_IM_CNR_RDMA_DATA_CSPR_EDGE_TBL) );
	imCnrConvertRdmaCsprEdgeTable( spr_cspr_edge, rdma_cspr_edge_table );
	return D_DDIM_OK;
}

/*
CNR(OFL) Set CSPR Hue Specified Table setting parameter information
*/
INT32 Im_CNR_Set_RdmaValue_OFL_CSPR_Hue_Spec_Table( const T_IM_CNR_HUE_SPEC_TABLE* const spr_cspr_hue, T_IM_CNR_RDMA_DATA_CSPR_HUE_TBL* const rdma_cspr_hue_table )
{
#ifdef CO_PARAM_CHECK
	if( spr_cspr_hue == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OFL_CSPR_Hue_Spec_Table() Parameter(spr_cspr_hue) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_hue_table == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OFL_CSPR_Hue_Spec_Table() Parameter(rdma_cspr_hue_table) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_hue_table, 0, sizeof(T_IM_CNR_RDMA_DATA_CSPR_HUE_TBL) );
	imCnrConvertRdmaCsprHueTable( spr_cspr_hue, rdma_cspr_hue_table );
	return D_DDIM_OK;
}

/*
CNR(OTF) Set CSPR Hue Specified Table setting parameter information
*/
INT32 Im_CNR_Set_RdmaValue_OTF_CSPR_Hue_Spec_Table( const T_IM_CNR_HUE_SPEC_TABLE* const spr_cspr_hue, T_IM_CNR_RDMA_DATA_CSPR_HUE_TBL* const rdma_cspr_hue_table )
{
#ifdef CO_PARAM_CHECK
	if( spr_cspr_hue == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OTF_CSPR_Hue_Spec_Table() Parameter(spr_cspr_hue) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_hue_table == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OTF_CSPR_Hue_Spec_Table() Parameter(rdma_cspr_hue_table) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_hue_table, 0, sizeof(T_IM_CNR_RDMA_DATA_CSPR_HUE_TBL) );
	imCnrConvertRdmaCsprHueTable( spr_cspr_hue, rdma_cspr_hue_table );
	return D_DDIM_OK;
}

/*
CNR(OFL) Set CSPR SPRS_CC Table setting parameter information
*/
INT32 Im_CNR_Set_RdmaValue_OFL_CSPR_SPRS_CC_Table( const T_IM_CNR_CTRL_CC_SRC_DST* const cspr_sprs_cc, T_IM_CNR_RDMA_DATA_SPRS_CC_TBL* const rdma_cspr_sprs_cc )
{
#ifdef CO_PARAM_CHECK
	if( cspr_sprs_cc == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OFL_CSPR_SPRS_CC_Table() Parameter(cspr_sprs_cc) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_sprs_cc == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OFL_CSPR_SPRS_CC_Table() Parameter(rdma_cspr_sprs_cc) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_sprs_cc, 0, sizeof(T_IM_CNR_RDMA_DATA_SPRS_CC_TBL) );
	imCnrConvertRdmaCsprSprsCc( cspr_sprs_cc, rdma_cspr_sprs_cc );
	return D_DDIM_OK;
}

/*
CNR(OTF) Set CSPR SPRS_CC Table setting parameter information
*/
INT32 Im_CNR_Set_RdmaValue_OTF_CSPR_SPRS_CC_Table( const T_IM_CNR_CTRL_CC_SRC_DST* const cspr_sprs_cc, T_IM_CNR_RDMA_DATA_SPRS_CC_TBL* const rdma_cspr_sprs_cc )
{
#ifdef CO_PARAM_CHECK
	if( cspr_sprs_cc == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OTF_CSPR_SPRS_CC_Table() Parameter(cspr_sprs_cc) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_sprs_cc == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OTF_CSPR_SPRS_CC_Table() Parameter(rdma_cspr_sprs_cc) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_sprs_cc, 0, sizeof(T_IM_CNR_RDMA_DATA_SPRS_CC_TBL) );
	imCnrConvertRdmaCsprSprsCc( cspr_sprs_cc, rdma_cspr_sprs_cc );
	return D_DDIM_OK;
}

/*
CNR(OFL) Set CSPR SPRD_CC Table setting parameter information
*/
INT32 Im_CNR_Set_RdmaValue_OFL_CSPR_SPRD_CC_Table( const T_IM_CNR_CTRL_CC_SRC_DST* const cspr_sprd_cc, T_IM_CNR_RDMA_DATA_SPRD_CC_TBL* const rdma_cspr_sprd_cc )
{
#ifdef CO_PARAM_CHECK
	if( cspr_sprd_cc == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OFL_CSPR_SPRD_CC_Table() Parameter(cspr_sprd_cc) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_sprd_cc == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OFL_CSPR_SPRD_CC_Table() Parameter(rdma_cspr_sprd_cc) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_sprd_cc, 0, sizeof(T_IM_CNR_RDMA_DATA_SPRD_CC_TBL) );
	imCnrConvertRdmaCsprSprdCc( cspr_sprd_cc, rdma_cspr_sprd_cc );
	return D_DDIM_OK;
}

/*
CNR(OTF) Set CSPR SPRD_CC Table setting parameter information
*/
INT32 Im_CNR_Set_RdmaValue_OTF_CSPR_SPRD_CC_Table( const T_IM_CNR_CTRL_CC_SRC_DST* const cspr_sprd_cc, T_IM_CNR_RDMA_DATA_SPRD_CC_TBL* const rdma_cspr_sprd_cc )
{
#ifdef CO_PARAM_CHECK
	if( cspr_sprd_cc == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OTF_CSPR_SPRD_CC_Table() Parameter(cspr_sprd_cc) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_sprd_cc == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OTF_CSPR_SPRD_CC_Table() Parameter(rdma_cspr_sprd_cc) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_sprd_cc, 0, sizeof(T_IM_CNR_RDMA_DATA_SPRD_CC_TBL) );
	imCnrConvertRdmaCsprSprdCc( cspr_sprd_cc, rdma_cspr_sprd_cc );
	return D_DDIM_OK;
}

/*
CNR(OFL) Set YSPR Table setting parameter information
*/
INT32 Im_CNR_Set_RdmaValue_OFL_YSPR_Table( const T_IM_CNR_TABLE* const yspr_table, T_IM_CNR_RDMA_DATA_OFL_YSPR_TBL* const rdma_yspr_table )
{
#ifdef CO_PARAM_CHECK
	if( yspr_table == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OFL_YSPR_Table() Parameter(yspr_table) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_yspr_table == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OFL_YSPR_Table() Parameter(rdma_yspr_table) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_yspr_table, 0, sizeof(T_IM_CNR_RDMA_DATA_OFL_YSPR_TBL) );
	rdma_yspr_table->YSPRDYEYBD.YSPRDYEYBD1.bit.YSPRDYEYBD_1	= yspr_table->bd1;
	rdma_yspr_table->YSPRDYEYBD.YSPRDYEYBD1.bit.YSPRDYEYBD_2	= yspr_table->bd2;
	rdma_yspr_table->YSPRDYEYBD.YSPRDYEYBD1.bit.YSPRDYEYBD_3	= yspr_table->bd3;
	rdma_yspr_table->YSPRDYEYBD.YSPRDYEYBD1.bit.YSPRDYEYBD_4	= yspr_table->bd4;
	rdma_yspr_table->YSPRDYEYBD.YSPRDYEYBD2.bit.YSPRDYEYBD_5	= yspr_table->bd5;
	rdma_yspr_table->YSPRDYEYOF.YSPRDYEYOF1.bit.YSPRDYEYOF_0	= yspr_table->of0;
	rdma_yspr_table->YSPRDYEYOF.YSPRDYEYOF1.bit.YSPRDYEYOF_1	= yspr_table->of1;
	rdma_yspr_table->YSPRDYEYOF.YSPRDYEYOF1.bit.YSPRDYEYOF_2	= yspr_table->of2;
	rdma_yspr_table->YSPRDYEYOF.YSPRDYEYOF1.bit.YSPRDYEYOF_3	= yspr_table->of3;
	rdma_yspr_table->YSPRDYEYOF.YSPRDYEYOF2.bit.YSPRDYEYOF_4	= yspr_table->of4;
	rdma_yspr_table->YSPRDYEYOF.YSPRDYEYOF2.bit.YSPRDYEYOF_5	= yspr_table->of5;
	// write signed data
	im_cnr_set_reg_signed( rdma_yspr_table->YSPRDYEYGA.YSPRDYEYGA1, union io_cnr_ofl_reg_yspr_ysprdyeyga_1, YSPRDYEYGA_0, yspr_table->gain0 );
	im_cnr_set_reg_signed( rdma_yspr_table->YSPRDYEYGA.YSPRDYEYGA1, union io_cnr_ofl_reg_yspr_ysprdyeyga_1, YSPRDYEYGA_1, yspr_table->gain1 );
	im_cnr_set_reg_signed( rdma_yspr_table->YSPRDYEYGA.YSPRDYEYGA1, union io_cnr_ofl_reg_yspr_ysprdyeyga_1, YSPRDYEYGA_2, yspr_table->gain2 );
	im_cnr_set_reg_signed( rdma_yspr_table->YSPRDYEYGA.YSPRDYEYGA1, union io_cnr_ofl_reg_yspr_ysprdyeyga_1, YSPRDYEYGA_3, yspr_table->gain3 );
	im_cnr_set_reg_signed( rdma_yspr_table->YSPRDYEYGA.YSPRDYEYGA2, union io_cnr_ofl_reg_yspr_ysprdyeyga_2, YSPRDYEYGA_4, yspr_table->gain4 );
	im_cnr_set_reg_signed( rdma_yspr_table->YSPRDYEYGA.YSPRDYEYGA2, union io_cnr_ofl_reg_yspr_ysprdyeyga_2, YSPRDYEYGA_5, yspr_table->gain5 );
	return D_DDIM_OK;
}

/*
CNR(OFL) Set SPR CTRL-Y setting parameter information
*/
INT32 Im_CNR_Set_RdmaValue_OFL_Ctrl_Y( const T_IM_CNR_OFL_CTRL_Y* const spr_ctrl_y, T_IM_CNR_RDMA_DATA_OFL_CTRL_Y* const rdma_ctrl_y )
{
#ifdef CO_PARAM_CHECK
	if( spr_ctrl_y == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OFL_Ctrl_Y() Parameter(spr_ctrl_y) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_ctrl_y == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Set_RdmaValue_OFL_Ctrl_Y() Parameter(rdma_ctrl_y) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_ctrl_y, 0, sizeof(T_IM_CNR_RDMA_DATA_OFL_CTRL_Y) );
	rdma_ctrl_y->YSPREN.bit.YSPREN			= spr_ctrl_y->enable;
	rdma_ctrl_y->YSPRMODE.bit.YSPRMD		= spr_ctrl_y->threshold_type;
	rdma_ctrl_y->YSPRMODE.bit.YSPRFE		= spr_ctrl_y->level;
	rdma_ctrl_y->YSPRFXEY.bit.YSPRFXEYV		= spr_ctrl_y->v_y_threshold;
	rdma_ctrl_y->YSPRFXEY.bit.YSPRFXEYH		= spr_ctrl_y->h_y_threshold;
	rdma_ctrl_y->YSPRFXEC.bit.YSPRFXECV		= spr_ctrl_y->v_c_threshold;
	rdma_ctrl_y->YSPRFXEC.bit.YSPRFXECH		= spr_ctrl_y->h_c_threshold;
	rdma_ctrl_y->YSPRALPBD.bit.YSPRALPBD	= spr_ctrl_y->alpha_blend_ratio;
	return D_DDIM_OK;
}

#endif

ImCnrSet *im_cnr_set_new(void)
{
	ImCnrSet* self = k_object_new_with_private(IM_TYPE_CNR_SET,sizeof(ImCnrSetPrivate));
	return self;
}
