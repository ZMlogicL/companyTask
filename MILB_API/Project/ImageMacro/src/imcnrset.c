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
static VOID imCnrConvertRdmaValueCtrlC( const TImCnrCtrlC* spr_ctrl_c, TImCnrRdmaDataCtrlC* rdma_ctrl_c );
static VOID imCnrConvertRdmaCsprMidYTable( const TImCnrTable* spr_cspr_mid_y, TImCnrRdmaDataCsprMidYTbl* rdma_cspr_mid_y_table );
static VOID imCnrConvertRdmaCsprMidCcYTable( const TImCnrTable* cspr_mid_cc_y, TImCnrRdmaDataCsprMidCcYTbl* rdma_mid_cc_y_table );
static VOID imCnrConvertRdmaCsprMidCcCTable( const TImCnrTable* cspr_mid_cc_c, TImCnrRdmaDataCsprMidCcCTbl* rdma_mid_cc_c_table );
static VOID imCnrConvertRdmaCsprLowYTable( const TImCnrTable* spr_cspr_low_y, TImCnrRdmaDataCsprLowYTbl* rdma_cspr_low_y_table );
static VOID imCnrConvertRdmaCsprLowCcYTable( const TImCnrTable* cspr_low_cc_y, TImCnrRdmaDataCsprLowCcYTbl* rdma_low_cc_y_table );
static VOID imCnrConvertRdmaCsprLowCcCTable( const TImCnrTable* cspr_low_cc_c, TImCnrRdmaDataCsprLowCcCTbl* rdma_low_cc_c_table );
static VOID imCnrConvertRdmaCsprEdgeTable( const TImCnrTable* cspr_edge, TImCnrRdmaDataCsprEdgeTbl* rdma_edge_table );
static VOID imCnrConvertRdmaCsprHueTable( const TImCnrHueSpecTable* cspr_hue, TImCnrRdmaDataCsprHueTbl* rdma_hue_table );
static VOID imCnrConvertRdmaCsprSprsCc( const TImCnrCtrlCcSrcDst* sprs_ctrl, TImCnrRdmaDataSprsCcTbl* rdma_sprs_ctrl );
static VOID imCnrConvertRdmaCsprSprdCc( const TImCnrCtrlCcSrcDst* sprd_ctrl, TImCnrRdmaDataSprdCcTbl* rdma_sprd_ctrl );
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
Convert TImCnrCtrlC to TImCnrRdmaDataCtrlC
*/
static VOID imCnrConvertRdmaValueCtrlC( const TImCnrCtrlC* spr_ctrl_c, TImCnrRdmaDataCtrlC* rdma_ctrl_c )
{
	rdma_ctrl_c->csprEn.bit.csprEn	= spr_ctrl_c->enable;
	rdma_ctrl_c->cgdkEn.bit.cgdkEn	= spr_ctrl_c->gradationKeepEn;
	rdma_ctrl_c->mcEn.bit.mcEn		= spr_ctrl_c->midFreqNr.enable;

	rdma_ctrl_c->mcYthh.bit.MCYTHH_0	= spr_ctrl_c->midFreqNr.hYThreshold[0];
	rdma_ctrl_c->mcYthh.bit.MCYTHH_1	= spr_ctrl_c->midFreqNr.hYThreshold[1];
	rdma_ctrl_c->mcYthh.bit.MCYTHH_2	= spr_ctrl_c->midFreqNr.hYThreshold[2];
	rdma_ctrl_c->mcYthh.bit.MCYTHH_3	= spr_ctrl_c->midFreqNr.hYThreshold[3];
	rdma_ctrl_c->mcYthv.bit.MCYTHV_0	= spr_ctrl_c->midFreqNr.vYThreshold[0];
	rdma_ctrl_c->mcYthv.bit.MCYTHV_1	= spr_ctrl_c->midFreqNr.vYThreshold[1];
	rdma_ctrl_c->mcYthv.bit.MCYTHV_2	= spr_ctrl_c->midFreqNr.vYThreshold[2];
	rdma_ctrl_c->mcYthv.bit.MCYTHV_3	= spr_ctrl_c->midFreqNr.vYThreshold[3];
	rdma_ctrl_c->mcCthh.bit.MCCTHH_0	= spr_ctrl_c->midFreqNr.hCThreshold[0];
	rdma_ctrl_c->mcCthh.bit.MCCTHH_1	= spr_ctrl_c->midFreqNr.hCThreshold[1];
	rdma_ctrl_c->mcCthh.bit.MCCTHH_2	= spr_ctrl_c->midFreqNr.hCThreshold[2];
	rdma_ctrl_c->mcCthh.bit.MCCTHH_3	= spr_ctrl_c->midFreqNr.hCThreshold[3];
	rdma_ctrl_c->mcCthv.bit.MCCTHV_0	= spr_ctrl_c->midFreqNr.vCThreshold[0];
	rdma_ctrl_c->mcCthv.bit.MCCTHV_1	= spr_ctrl_c->midFreqNr.vCThreshold[1];
	rdma_ctrl_c->mcCthv.bit.MCCTHV_2	= spr_ctrl_c->midFreqNr.vCThreshold[2];
	rdma_ctrl_c->mcCthv.bit.MCCTHV_3	= spr_ctrl_c->midFreqNr.vCThreshold[3];
	rdma_ctrl_c->mcYdymDt.bit.MCYDYMYCR	= spr_ctrl_c->midFreqNr.yThresholdCor;
	rdma_ctrl_c->mcYdymDt.bit.MCYDYMYG	= spr_ctrl_c->midFreqNr.yThresholdGain;
	rdma_ctrl_c->mcYdym.bit.mcYdym		= spr_ctrl_c->midFreqNr.yThresholdDymEn;
	rdma_ctrl_c->mcYscl.bit.mcYscl		= spr_ctrl_c->midFreqNr.yThresholdSclEn;
	rdma_ctrl_c->mcSscl.bit.mcSscl		= spr_ctrl_c->midFreqNr.cYThresholdSclEn;
	rdma_ctrl_c->mcCscl.bit.mcCscl		= spr_ctrl_c->midFreqNr.cThresholdSclEn;
	rdma_ctrl_c->lcEn.bit.lcEn			= spr_ctrl_c->lowFreqNr.enable;
	rdma_ctrl_c->lcYthh.bit.LCYTHH_0	= spr_ctrl_c->lowFreqNr.hYThreshold[0];
	rdma_ctrl_c->lcYthh.bit.LCYTHH_1	= spr_ctrl_c->lowFreqNr.hYThreshold[1];
	rdma_ctrl_c->lcYthh.bit.LCYTHH_2	= spr_ctrl_c->lowFreqNr.hYThreshold[2];
	rdma_ctrl_c->lcYthh.bit.LCYTHH_3	= spr_ctrl_c->lowFreqNr.hYThreshold[3];
	rdma_ctrl_c->lcYthv.bit.LCYTHV_0	= spr_ctrl_c->lowFreqNr.vYThreshold[0];
	rdma_ctrl_c->lcYthv.bit.LCYTHV_1	= spr_ctrl_c->lowFreqNr.vYThreshold[1];
	rdma_ctrl_c->lcYthv.bit.LCYTHV_2	= spr_ctrl_c->lowFreqNr.vYThreshold[2];
	rdma_ctrl_c->lcYthv.bit.LCYTHV_3	= spr_ctrl_c->lowFreqNr.vYThreshold[3];
	rdma_ctrl_c->lcCthh.bit.LCCTHH_0	= spr_ctrl_c->lowFreqNr.hCThreshold[0];
	rdma_ctrl_c->lcCthh.bit.LCCTHH_1	= spr_ctrl_c->lowFreqNr.hCThreshold[1];
	rdma_ctrl_c->lcCthh.bit.LCCTHH_2	= spr_ctrl_c->lowFreqNr.hCThreshold[2];
	rdma_ctrl_c->lcCthh.bit.LCCTHH_3	= spr_ctrl_c->lowFreqNr.hCThreshold[3];
	rdma_ctrl_c->lcCthv.bit.LCCTHV_0	= spr_ctrl_c->lowFreqNr.vCThreshold[0];
	rdma_ctrl_c->lcCthv.bit.LCCTHV_1	= spr_ctrl_c->lowFreqNr.vCThreshold[1];
	rdma_ctrl_c->lcCthv.bit.LCCTHV_2	= spr_ctrl_c->lowFreqNr.vCThreshold[2];
	rdma_ctrl_c->lcCthv.bit.LCCTHV_3	= spr_ctrl_c->lowFreqNr.vCThreshold[3];
	rdma_ctrl_c->lcYdymDt.bit.LCYDYMYCR	= spr_ctrl_c->lowFreqNr.yThresholdCor;
	rdma_ctrl_c->lcYdymDt.bit.LCYDYMYG	= spr_ctrl_c->lowFreqNr.yThresholdGain;
	rdma_ctrl_c->lcYdym.bit.lcYdym	= spr_ctrl_c->lowFreqNr.yThresholdDymEn;
	rdma_ctrl_c->lcYscl.bit.lcYscl	= spr_ctrl_c->lowFreqNr.yThresholdSclEn;
	rdma_ctrl_c->lcSscl.bit.lcSscl	= spr_ctrl_c->lowFreqNr.cYThresholdSclEn;
	rdma_ctrl_c->lcCscl.bit.lcCscl	= spr_ctrl_c->lowFreqNr.cThresholdSclEn;
	rdma_ctrl_c->whTmd.bit.WHTEN	= spr_ctrl_c->whiteningEnable;
	rdma_ctrl_c->whTmd.bit.WHTVAL	= spr_ctrl_c->whiteningValue;
	rdma_ctrl_c->whTmd.bit.WHTBASE	= spr_ctrl_c->whiteningBase;
	rdma_ctrl_c->blEnd.bit.BLENDMD		= spr_ctrl_c->cBlendMd;
	rdma_ctrl_c->blEnd.bit.CSPRALPBD	= spr_ctrl_c->cAlphaBlend;
	rdma_ctrl_c->blEnd.bit.CSRGEN		= spr_ctrl_c->cRange;
	rdma_ctrl_c->blEnd.bit.CSRGMD		= spr_ctrl_c->cRangeMode;
}

/*
Convert TImCnrTable to TImCnrRdmaDataCsprMidYTbl
*/
static VOID imCnrConvertRdmaCsprMidYTable( const TImCnrTable* spr_cspr_mid_y, TImCnrRdmaDataCsprMidYTbl* rdma_cspr_mid_y_table )
{
	rdma_cspr_mid_y_table->mcysClbd.MCYSCLBD1.bit.mcysClbd1	= spr_cspr_mid_y->bd1;
	rdma_cspr_mid_y_table->mcysClbd.MCYSCLBD1.bit.mcysClbd2	= spr_cspr_mid_y->bd2;
	rdma_cspr_mid_y_table->mcysClbd.MCYSCLBD1.bit.MCYSCLBD_3	= spr_cspr_mid_y->bd3;
	rdma_cspr_mid_y_table->mcysClbd.MCYSCLBD1.bit.MCYSCLBD_4	= spr_cspr_mid_y->bd4;
	rdma_cspr_mid_y_table->mcysClbd.MCYSCLBD2.bit.MCYSCLBD_5	= spr_cspr_mid_y->bd5;
	rdma_cspr_mid_y_table->mcysClof.MCYSCLOF1.bit.MCYSCLOF_0	= spr_cspr_mid_y->of0;
	rdma_cspr_mid_y_table->mcysClof.MCYSCLOF1.bit.mcysClof1	= spr_cspr_mid_y->of1;
	rdma_cspr_mid_y_table->mcysClof.MCYSCLOF1.bit.mcysClof2	= spr_cspr_mid_y->of2;
	rdma_cspr_mid_y_table->mcysClof.MCYSCLOF1.bit.MCYSCLOF_3	= spr_cspr_mid_y->of3;
	rdma_cspr_mid_y_table->mcysClof.MCYSCLOF2.bit.MCYSCLOF_4	= spr_cspr_mid_y->of4;
	rdma_cspr_mid_y_table->mcysClof.MCYSCLOF2.bit.MCYSCLOF_5	= spr_cspr_mid_y->of5;
	// write signed data
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_cspr_mid_y_table->mcysClga.MCYSCLGA1, union io_cnr_cspr_reg_mcysclga_1, MCYSCLGA_0, spr_cspr_mid_y->gain0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_cspr_mid_y_table->mcysClga.MCYSCLGA1, union io_cnr_cspr_reg_mcysclga_1, mcysClga1, spr_cspr_mid_y->gain1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_cspr_mid_y_table->mcysClga.MCYSCLGA1, union io_cnr_cspr_reg_mcysclga_1, mcysClga2, spr_cspr_mid_y->gain2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_cspr_mid_y_table->mcysClga.MCYSCLGA1, union io_cnr_cspr_reg_mcysclga_1, MCYSCLGA_3, spr_cspr_mid_y->gain3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_cspr_mid_y_table->mcysClga.MCYSCLGA2, union io_cnr_cspr_reg_mcysclga_2, MCYSCLGA_4, spr_cspr_mid_y->gain4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_cspr_mid_y_table->mcysClga.MCYSCLGA2, union io_cnr_cspr_reg_mcysclga_2, MCYSCLGA_5, spr_cspr_mid_y->gain5 );
}

/*
Convert TImCnrTable to TImCnrRdmaAddrCsprMidCcYTbl
*/
static VOID imCnrConvertRdmaCsprMidCcYTable( const TImCnrTable* cspr_mid_cc_y, TImCnrRdmaDataCsprMidCcYTbl* rdma_mid_cc_y_table )
{
	rdma_mid_cc_y_table->mccsClbd.MCCSCLBD1.bit.mccsClbd1	= cspr_mid_cc_y->bd1;
	rdma_mid_cc_y_table->mccsClbd.MCCSCLBD1.bit.mccsClbd2	= cspr_mid_cc_y->bd2;
	rdma_mid_cc_y_table->mccsClbd.MCCSCLBD1.bit.MCCSCLBD_3	= cspr_mid_cc_y->bd3;
	rdma_mid_cc_y_table->mccsClbd.MCCSCLBD1.bit.MCCSCLBD_4	= cspr_mid_cc_y->bd4;
	rdma_mid_cc_y_table->mccsClbd.MCCSCLBD2.bit.MCCSCLBD_5	= cspr_mid_cc_y->bd5;
	rdma_mid_cc_y_table->mccsClof.MCCSCLOF1.bit.MCCSCLOF_0	= cspr_mid_cc_y->of0;
	rdma_mid_cc_y_table->mccsClof.MCCSCLOF1.bit.mccsClof1	= cspr_mid_cc_y->of1;
	rdma_mid_cc_y_table->mccsClof.MCCSCLOF1.bit.mccsClof2	= cspr_mid_cc_y->of2;
	rdma_mid_cc_y_table->mccsClof.MCCSCLOF1.bit.MCCSCLOF_3	= cspr_mid_cc_y->of3;
	rdma_mid_cc_y_table->mccsClof.MCCSCLOF2.bit.MCCSCLOF_4	= cspr_mid_cc_y->of4;
	rdma_mid_cc_y_table->mccsClof.MCCSCLOF2.bit.MCCSCLOF_5	= cspr_mid_cc_y->of5;
	// write signed data
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_mid_cc_y_table->mccsClga.MCCSCLGA1, union io_cnr_cspr_reg_mccsclga_1, MCCSCLGA_0, cspr_mid_cc_y->gain0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_mid_cc_y_table->mccsClga.MCCSCLGA1, union io_cnr_cspr_reg_mccsclga_1, mccsClga1, cspr_mid_cc_y->gain1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_mid_cc_y_table->mccsClga.MCCSCLGA1, union io_cnr_cspr_reg_mccsclga_1, mccsClga2, cspr_mid_cc_y->gain2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_mid_cc_y_table->mccsClga.MCCSCLGA1, union io_cnr_cspr_reg_mccsclga_1, MCCSCLGA_3, cspr_mid_cc_y->gain3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_mid_cc_y_table->mccsClga.MCCSCLGA2, union io_cnr_cspr_reg_mccsclga_2, MCCSCLGA_4, cspr_mid_cc_y->gain4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_mid_cc_y_table->mccsClga.MCCSCLGA2, union io_cnr_cspr_reg_mccsclga_2, MCCSCLGA_5, cspr_mid_cc_y->gain5 );
}

/*
Convert TImCnrTable to TImCnrRdmaAddrCsprMidCcCTbl
*/
static VOID imCnrConvertRdmaCsprMidCcCTable( const TImCnrTable* cspr_mid_cc_c, TImCnrRdmaDataCsprMidCcCTbl* rdma_mid_cc_c_table )
{
	rdma_mid_cc_c_table->mcssClbd.MCSSCLBD1.bit.mcssClbd1	= cspr_mid_cc_c->bd1;
	rdma_mid_cc_c_table->mcssClbd.MCSSCLBD1.bit.mcssClbd2	= cspr_mid_cc_c->bd2;
	rdma_mid_cc_c_table->mcssClbd.MCSSCLBD1.bit.MCSSCLBD_3	= cspr_mid_cc_c->bd3;
	rdma_mid_cc_c_table->mcssClbd.MCSSCLBD1.bit.MCSSCLBD_4	= cspr_mid_cc_c->bd4;
	rdma_mid_cc_c_table->mcssClbd.MCSSCLBD2.bit.MCSSCLBD_5	= cspr_mid_cc_c->bd5;
	rdma_mid_cc_c_table->mcssClof.MCSSCLOF1.bit.MCSSCLOF_0	= cspr_mid_cc_c->of0;
	rdma_mid_cc_c_table->mcssClof.MCSSCLOF1.bit.mcssClof1	= cspr_mid_cc_c->of1;
	rdma_mid_cc_c_table->mcssClof.MCSSCLOF1.bit.mcssClof2	= cspr_mid_cc_c->of2;
	rdma_mid_cc_c_table->mcssClof.MCSSCLOF1.bit.MCSSCLOF_3	= cspr_mid_cc_c->of3;
	rdma_mid_cc_c_table->mcssClof.MCSSCLOF2.bit.MCSSCLOF_4	= cspr_mid_cc_c->of4;
	rdma_mid_cc_c_table->mcssClof.MCSSCLOF2.bit.MCSSCLOF_5	= cspr_mid_cc_c->of5;
	// write signed data
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_mid_cc_c_table->mcssClga.MCSSCLGA1, union io_cnr_cspr_reg_mcssclga_1, MCSSCLGA_0, cspr_mid_cc_c->gain0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_mid_cc_c_table->mcssClga.MCSSCLGA1, union io_cnr_cspr_reg_mcssclga_1, mcssClga1, cspr_mid_cc_c->gain1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_mid_cc_c_table->mcssClga.MCSSCLGA1, union io_cnr_cspr_reg_mcssclga_1, mcssClga2, cspr_mid_cc_c->gain2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_mid_cc_c_table->mcssClga.MCSSCLGA1, union io_cnr_cspr_reg_mcssclga_1, MCSSCLGA_3, cspr_mid_cc_c->gain3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_mid_cc_c_table->mcssClga.MCSSCLGA2, union io_cnr_cspr_reg_mcssclga_2, MCSSCLGA_4, cspr_mid_cc_c->gain4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_mid_cc_c_table->mcssClga.MCSSCLGA2, union io_cnr_cspr_reg_mcssclga_2, MCSSCLGA_5, cspr_mid_cc_c->gain5 );
}

/*
Convert TImCnrTable to TImCnrRdmaDataCsprLowYTbl
*/
static VOID imCnrConvertRdmaCsprLowYTable( const TImCnrTable* spr_cspr_low_y, TImCnrRdmaDataCsprLowYTbl* rdma_cspr_low_y_table )
{
	rdma_cspr_low_y_table->lcysClbd.LCYSCLBD1.bit.lcysClbd1	= spr_cspr_low_y->bd1;
	rdma_cspr_low_y_table->lcysClbd.LCYSCLBD1.bit.lcysClbd2	= spr_cspr_low_y->bd2;
	rdma_cspr_low_y_table->lcysClbd.LCYSCLBD1.bit.LCYSCLBD_3	= spr_cspr_low_y->bd3;
	rdma_cspr_low_y_table->lcysClbd.LCYSCLBD1.bit.LCYSCLBD_4	= spr_cspr_low_y->bd4;
	rdma_cspr_low_y_table->lcysClbd.LCYSCLBD2.bit.LCYSCLBD_5	= spr_cspr_low_y->bd5;
	rdma_cspr_low_y_table->lcysClof.LCYSCLOF1.bit.LCYSCLOF_0	= spr_cspr_low_y->of0;
	rdma_cspr_low_y_table->lcysClof.LCYSCLOF1.bit.lcysClof1	= spr_cspr_low_y->of1;
	rdma_cspr_low_y_table->lcysClof.LCYSCLOF1.bit.lcysClof2	= spr_cspr_low_y->of2;
	rdma_cspr_low_y_table->lcysClof.LCYSCLOF1.bit.LCYSCLOF_3	= spr_cspr_low_y->of3;
	rdma_cspr_low_y_table->lcysClof.LCYSCLOF2.bit.LCYSCLOF_4	= spr_cspr_low_y->of4;
	rdma_cspr_low_y_table->lcysClof.LCYSCLOF2.bit.LCYSCLOF_5	= spr_cspr_low_y->of5;
	// write signed data
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_cspr_low_y_table->lcysClga.LCYSCLGA1, union io_cnr_cspr_reg_lcysclga_1, LCYSCLGA_0, spr_cspr_low_y->gain0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_cspr_low_y_table->lcysClga.LCYSCLGA1, union io_cnr_cspr_reg_lcysclga_1, lcysClga1, spr_cspr_low_y->gain1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_cspr_low_y_table->lcysClga.LCYSCLGA1, union io_cnr_cspr_reg_lcysclga_1, lcysClga2, spr_cspr_low_y->gain2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_cspr_low_y_table->lcysClga.LCYSCLGA1, union io_cnr_cspr_reg_lcysclga_1, LCYSCLGA_3, spr_cspr_low_y->gain3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_cspr_low_y_table->lcysClga.LCYSCLGA2, union io_cnr_cspr_reg_lcysclga_2, LCYSCLGA_4, spr_cspr_low_y->gain4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_cspr_low_y_table->lcysClga.LCYSCLGA2, union io_cnr_cspr_reg_lcysclga_2, LCYSCLGA_5, spr_cspr_low_y->gain5 );
}

/*
Convert TImCnrTable to TImCnrRdmaAddrCsprLowCcYTbl
*/
static VOID imCnrConvertRdmaCsprLowCcYTable( const TImCnrTable* cspr_low_cc_y, TImCnrRdmaDataCsprLowCcYTbl* rdma_low_cc_y_table )
{
	rdma_low_cc_y_table->lccsClbd.LCCSCLBD1.bit.lccsClbd1	= cspr_low_cc_y->bd1;
	rdma_low_cc_y_table->lccsClbd.LCCSCLBD1.bit.lccsClbd2	= cspr_low_cc_y->bd2;
	rdma_low_cc_y_table->lccsClbd.LCCSCLBD1.bit.LCCSCLBD_3	= cspr_low_cc_y->bd3;
	rdma_low_cc_y_table->lccsClbd.LCCSCLBD1.bit.LCCSCLBD_4	= cspr_low_cc_y->bd4;
	rdma_low_cc_y_table->lccsClbd.LCCSCLBD2.bit.LCCSCLBD_5	= cspr_low_cc_y->bd5;
	rdma_low_cc_y_table->lccsClof.LCCSCLOF1.bit.LCCSCLOF_0	= cspr_low_cc_y->of0;
	rdma_low_cc_y_table->lccsClof.LCCSCLOF1.bit.lccsClof1	= cspr_low_cc_y->of1;
	rdma_low_cc_y_table->lccsClof.LCCSCLOF1.bit.lccsClof2	= cspr_low_cc_y->of2;
	rdma_low_cc_y_table->lccsClof.LCCSCLOF1.bit.LCCSCLOF_3	= cspr_low_cc_y->of3;
	rdma_low_cc_y_table->lccsClof.LCCSCLOF2.bit.LCCSCLOF_4	= cspr_low_cc_y->of4;
	rdma_low_cc_y_table->lccsClof.LCCSCLOF2.bit.LCCSCLOF_5	= cspr_low_cc_y->of5;
	// write signed data
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_low_cc_y_table->lccsClga.LCCSCLGA1, union io_cnr_cspr_reg_lccsclga_1, LCCSCLGA_0, cspr_low_cc_y->gain0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_low_cc_y_table->lccsClga.LCCSCLGA1, union io_cnr_cspr_reg_lccsclga_1, lccsClga1, cspr_low_cc_y->gain1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_low_cc_y_table->lccsClga.LCCSCLGA1, union io_cnr_cspr_reg_lccsclga_1, lccsClga2, cspr_low_cc_y->gain2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_low_cc_y_table->lccsClga.LCCSCLGA1, union io_cnr_cspr_reg_lccsclga_1, LCCSCLGA_3, cspr_low_cc_y->gain3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_low_cc_y_table->lccsClga.LCCSCLGA2, union io_cnr_cspr_reg_lccsclga_2, LCCSCLGA_4, cspr_low_cc_y->gain4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_low_cc_y_table->lccsClga.LCCSCLGA2, union io_cnr_cspr_reg_lccsclga_2, LCCSCLGA_5, cspr_low_cc_y->gain5 );
}

/*
Convert TImCnrTable to TImCnrRdmaAddrCsprLowCcCTbl
*/
static VOID imCnrConvertRdmaCsprLowCcCTable( const TImCnrTable* cspr_low_cc_c, TImCnrRdmaDataCsprLowCcCTbl* rdma_low_cc_c_table )
{
	rdma_low_cc_c_table->lcssClbd.LCSSCLBD1.bit.lcssClbd1	= cspr_low_cc_c->bd1;
	rdma_low_cc_c_table->lcssClbd.LCSSCLBD1.bit.lcssClbd2	= cspr_low_cc_c->bd2;
	rdma_low_cc_c_table->lcssClbd.LCSSCLBD1.bit.LCSSCLBD_3	= cspr_low_cc_c->bd3;
	rdma_low_cc_c_table->lcssClbd.LCSSCLBD1.bit.LCSSCLBD_4	= cspr_low_cc_c->bd4;
	rdma_low_cc_c_table->lcssClbd.LCSSCLBD2.bit.LCSSCLBD_5	= cspr_low_cc_c->bd5;
	rdma_low_cc_c_table->lcssClof.LCSSCLOF1.bit.LCSSCLOF_0	= cspr_low_cc_c->of0;
	rdma_low_cc_c_table->lcssClof.LCSSCLOF1.bit.lcssClof1	= cspr_low_cc_c->of1;
	rdma_low_cc_c_table->lcssClof.LCSSCLOF1.bit.lcssClof2	= cspr_low_cc_c->of2;
	rdma_low_cc_c_table->lcssClof.LCSSCLOF1.bit.LCSSCLOF_3	= cspr_low_cc_c->of3;
	rdma_low_cc_c_table->lcssClof.LCSSCLOF2.bit.LCSSCLOF_4	= cspr_low_cc_c->of4;
	rdma_low_cc_c_table->lcssClof.LCSSCLOF2.bit.LCSSCLOF_5	= cspr_low_cc_c->of5;
	// write signed data
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_low_cc_c_table->lcssClga.LCSSCLGA1, union io_cnr_cspr_reg_lcssclga_1, LCSSCLGA_0, cspr_low_cc_c->gain0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_low_cc_c_table->lcssClga.LCSSCLGA1, union io_cnr_cspr_reg_lcssclga_1, lcssClga1, cspr_low_cc_c->gain1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_low_cc_c_table->lcssClga.LCSSCLGA1, union io_cnr_cspr_reg_lcssclga_1, lcssClga2, cspr_low_cc_c->gain2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_low_cc_c_table->lcssClga.LCSSCLGA1, union io_cnr_cspr_reg_lcssclga_1, LCSSCLGA_3, cspr_low_cc_c->gain3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_low_cc_c_table->lcssClga.LCSSCLGA2, union io_cnr_cspr_reg_lcssclga_2, LCSSCLGA_4, cspr_low_cc_c->gain4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_low_cc_c_table->lcssClga.LCSSCLGA2, union io_cnr_cspr_reg_lcssclga_2, LCSSCLGA_5, cspr_low_cc_c->gain5 );
}

/*
Convert TImCnrTable to TImCnrRdmaAddrCsprEdgeTbl
*/
static VOID imCnrConvertRdmaCsprEdgeTable( const TImCnrTable* cspr_edge, TImCnrRdmaDataCsprEdgeTbl* rdma_edge_table )
{
	rdma_edge_table->cesClbd.CESCLBD1.bit.cesClbd1	= cspr_edge->bd1;
	rdma_edge_table->cesClbd.CESCLBD1.bit.cesClbd2	= cspr_edge->bd2;
	rdma_edge_table->cesClbd.CESCLBD1.bit.CESCLBD_3	= cspr_edge->bd3;
	rdma_edge_table->cesClbd.CESCLBD1.bit.CESCLBD_4	= cspr_edge->bd4;
	rdma_edge_table->cesClbd.CESCLBD2.bit.CESCLBD_5	= cspr_edge->bd5;
	rdma_edge_table->cesClof.CESCLOF1.bit.CESCLOF_0	= cspr_edge->of0;
	rdma_edge_table->cesClof.CESCLOF1.bit.cesClof1	= cspr_edge->of1;
	rdma_edge_table->cesClof.CESCLOF1.bit.cesClof2	= cspr_edge->of2;
	rdma_edge_table->cesClof.CESCLOF1.bit.CESCLOF_3	= cspr_edge->of3;
	rdma_edge_table->cesClof.CESCLOF2.bit.CESCLOF_4	= cspr_edge->of4;
	rdma_edge_table->cesClof.CESCLOF2.bit.CESCLOF_5	= cspr_edge->of5;
	// write signed data
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_edge_table->cesClga.CESCLGA1, union io_cnr_cspr_reg_cesclga_1, CESCLGA_0, cspr_edge->gain0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_edge_table->cesClga.CESCLGA1, union io_cnr_cspr_reg_cesclga_1, cesClga1, cspr_edge->gain1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_edge_table->cesClga.CESCLGA1, union io_cnr_cspr_reg_cesclga_1, cesClga2, cspr_edge->gain2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_edge_table->cesClga.CESCLGA1, union io_cnr_cspr_reg_cesclga_1, CESCLGA_3, cspr_edge->gain3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_edge_table->cesClga.CESCLGA2, union io_cnr_cspr_reg_cesclga_2, CESCLGA_4, cspr_edge->gain4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_edge_table->cesClga.CESCLGA2, union io_cnr_cspr_reg_cesclga_2, CESCLGA_5, cspr_edge->gain5 );
}

/*
Convert TImCnrHueSpecTable to TImCnrRdmaAddrCsprHueTbl
*/
static VOID imCnrConvertRdmaCsprHueTable( const TImCnrHueSpecTable* cspr_hue, TImCnrRdmaDataCsprHueTbl* rdma_hue_table )
{
	// write signed data
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_hue_table->cphpt, union io_cnr_cspr_reg_cphpt, CDCB, cspr_hue->cdCb );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_hue_table->cphpt, union io_cnr_cspr_reg_cphpt, CDCR, cspr_hue->cdCr );
	rdma_hue_table->cphptk.bit.KCB	= cspr_hue->kCb;
	rdma_hue_table->cphptk.bit.KCR	= cspr_hue->kCr;
	rdma_hue_table->cdsClbd.CDSCLBD1.bit.cdsClbd1	= cspr_hue->bd1;
	rdma_hue_table->cdsClbd.CDSCLBD1.bit.cdsClbd2	= cspr_hue->bd2;
	rdma_hue_table->cdsClbd.CDSCLBD2.bit.cdsClbd3	= cspr_hue->bd3;
	rdma_hue_table->cdsClbd.CDSCLBD2.bit.CDSCLBD_4	= cspr_hue->bd4;
	rdma_hue_table->cdsClbd.CDSCLBD3.bit.CDSCLBD_5	= cspr_hue->bd5;
	rdma_hue_table->cdsClof.CDSCLOF1.bit.CDSCLOF_0	= cspr_hue->of0;
	rdma_hue_table->cdsClof.CDSCLOF1.bit.cdsClof1	= cspr_hue->of1;
	rdma_hue_table->cdsClof.CDSCLOF2.bit.cdsClof2	= cspr_hue->of2;
	rdma_hue_table->cdsClof.CDSCLOF2.bit.cdsClof3	= cspr_hue->of3;
	rdma_hue_table->cdsClof.CDSCLOF3.bit.CDSCLOF_4	= cspr_hue->of4;
	rdma_hue_table->cdsClof.CDSCLOF3.bit.CDSCLOF_5	= cspr_hue->of5;
	// write signed data
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_hue_table->cdsClga.CDSCLGA1, union io_cnr_cspr_reg_cdsclga_1, CDSCLGA_0, cspr_hue->gain0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_hue_table->cdsClga.CDSCLGA1, union io_cnr_cspr_reg_cdsclga_1, cdsClga1, cspr_hue->gain1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_hue_table->cdsClga.CDSCLGA2, union io_cnr_cspr_reg_cdsclga_2, cdsClga2, cspr_hue->gain2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_hue_table->cdsClga.CDSCLGA2, union io_cnr_cspr_reg_cdsclga_2, cdsClga3, cspr_hue->gain3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_hue_table->cdsClga.CDSCLGA3, union io_cnr_cspr_reg_cdsclga_3, CDSCLGA_4, cspr_hue->gain4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_hue_table->cdsClga.CDSCLGA3, union io_cnr_cspr_reg_cdsclga_3, CDSCLGA_5, cspr_hue->gain5 );
}

/*
Convert TImCnrCtrlCcSrcDst to TImCnrRdmaDataSprsCcTbl
*/
static VOID imCnrConvertRdmaCsprSprsCc( const TImCnrCtrlCcSrcDst* sprs_ctrl, TImCnrRdmaDataSprsCcTbl* rdma_sprs_ctrl )
{
	rdma_sprs_ctrl->sprs.bit.sprs = sprs_ctrl->enable;
	// write signed data
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprs_ctrl->sprsCbbd.SPRSCBBD1, union io_cnr_cspr_reg_sprscbbd_1, sprsCbbd1, sprs_ctrl->cbTable.bd1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprs_ctrl->sprsCbbd.SPRSCBBD1, union io_cnr_cspr_reg_sprscbbd_1, sprsCbbd2, sprs_ctrl->cbTable.bd2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprs_ctrl->sprsCbbd.SPRSCBBD1, union io_cnr_cspr_reg_sprscbbd_1, SPRSCBBD_3, sprs_ctrl->cbTable.bd3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprs_ctrl->sprsCbbd.SPRSCBBD1, union io_cnr_cspr_reg_sprscbbd_1, SPRSCBBD_4, sprs_ctrl->cbTable.bd4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprs_ctrl->sprsCbbd.SPRSCBBD2, union io_cnr_cspr_reg_sprscbbd_2, SPRSCBBD_5, sprs_ctrl->cbTable.bd5 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprs_ctrl->sprsCbof.SPRSCBOF1, union io_cnr_cspr_reg_sprscbof_1, SPRSCBOF_0, sprs_ctrl->cbTable.of0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprs_ctrl->sprsCbof.SPRSCBOF1, union io_cnr_cspr_reg_sprscbof_1, sprsCbof1, sprs_ctrl->cbTable.of1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprs_ctrl->sprsCbof.SPRSCBOF1, union io_cnr_cspr_reg_sprscbof_1, sprsCbof2, sprs_ctrl->cbTable.of2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprs_ctrl->sprsCbof.SPRSCBOF1, union io_cnr_cspr_reg_sprscbof_1, SPRSCBOF_3, sprs_ctrl->cbTable.of3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprs_ctrl->sprsCbof.SPRSCBOF2, union io_cnr_cspr_reg_sprscbof_2, SPRSCBOF_4, sprs_ctrl->cbTable.of4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprs_ctrl->sprsCbof.SPRSCBOF2, union io_cnr_cspr_reg_sprscbof_2, SPRSCBOF_5, sprs_ctrl->cbTable.of5 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprs_ctrl->sprsCbga.SPRSCBGA1, union io_cnr_cspr_reg_sprscbga_1, SPRSCBGA_0, sprs_ctrl->cbTable.gain0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprs_ctrl->sprsCbga.SPRSCBGA1, union io_cnr_cspr_reg_sprscbga_1, sprsCbga1, sprs_ctrl->cbTable.gain1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprs_ctrl->sprsCbga.SPRSCBGA2, union io_cnr_cspr_reg_sprscbga_2, sprsCbga2, sprs_ctrl->cbTable.gain2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprs_ctrl->sprsCbga.SPRSCBGA2, union io_cnr_cspr_reg_sprscbga_2, sprsCbga3, sprs_ctrl->cbTable.gain3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprs_ctrl->sprsCbga.SPRSCBGA3, union io_cnr_cspr_reg_sprscbga_3, SPRSCBGA_4, sprs_ctrl->cbTable.gain4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprs_ctrl->sprsCbga.SPRSCBGA3, union io_cnr_cspr_reg_sprscbga_3, SPRSCBGA_5, sprs_ctrl->cbTable.gain5 );

	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprs_ctrl->sprsCrbd.SPRSCRBD1, union io_cnr_cspr_reg_sprscrbd_1, sprsCrbd1, sprs_ctrl->crTable.bd1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprs_ctrl->sprsCrbd.SPRSCRBD1, union io_cnr_cspr_reg_sprscrbd_1, sprsCrbd2, sprs_ctrl->crTable.bd2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprs_ctrl->sprsCrbd.SPRSCRBD1, union io_cnr_cspr_reg_sprscrbd_1, SPRSCRBD_3, sprs_ctrl->crTable.bd3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprs_ctrl->sprsCrbd.SPRSCRBD1, union io_cnr_cspr_reg_sprscrbd_1, SPRSCRBD_4, sprs_ctrl->crTable.bd4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprs_ctrl->sprsCrbd.SPRSCRBD2, union io_cnr_cspr_reg_sprscrbd_2, SPRSCRBD_5, sprs_ctrl->crTable.bd5 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprs_ctrl->sprsCrof.SPRSCROF1, union io_cnr_cspr_reg_sprscrof_1, SPRSCROF_0, sprs_ctrl->crTable.of0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprs_ctrl->sprsCrof.SPRSCROF1, union io_cnr_cspr_reg_sprscrof_1, sprsCrof1, sprs_ctrl->crTable.of1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprs_ctrl->sprsCrof.SPRSCROF1, union io_cnr_cspr_reg_sprscrof_1, sprsCrof2, sprs_ctrl->crTable.of2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprs_ctrl->sprsCrof.SPRSCROF1, union io_cnr_cspr_reg_sprscrof_1, SPRSCROF_3, sprs_ctrl->crTable.of3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprs_ctrl->sprsCrof.SPRSCROF2, union io_cnr_cspr_reg_sprscrof_2, SPRSCROF_4, sprs_ctrl->crTable.of4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprs_ctrl->sprsCrof.SPRSCROF2, union io_cnr_cspr_reg_sprscrof_2, SPRSCROF_5, sprs_ctrl->crTable.of5 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprs_ctrl->sprsCrga.SPRSCRGA1, union io_cnr_cspr_reg_sprscrga_1, SPRSCRGA_0, sprs_ctrl->crTable.gain0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprs_ctrl->sprsCrga.SPRSCRGA1, union io_cnr_cspr_reg_sprscrga_1, sprsCrga1, sprs_ctrl->crTable.gain1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprs_ctrl->sprsCrga.SPRSCRGA2, union io_cnr_cspr_reg_sprscrga_2, sprsCrga2, sprs_ctrl->crTable.gain2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprs_ctrl->sprsCrga.SPRSCRGA2, union io_cnr_cspr_reg_sprscrga_2, sprsCrga3, sprs_ctrl->crTable.gain3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprs_ctrl->sprsCrga.SPRSCRGA3, union io_cnr_cspr_reg_sprscrga_3, SPRSCRGA_4, sprs_ctrl->crTable.gain4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprs_ctrl->sprsCrga.SPRSCRGA3, union io_cnr_cspr_reg_sprscrga_3, SPRSCRGA_5, sprs_ctrl->crTable.gain5 );
}

/*
Convert TImCnrCtrlCcSrcDst to TImCnrRdmaDataSprdCcTbl
*/
static VOID imCnrConvertRdmaCsprSprdCc( const TImCnrCtrlCcSrcDst* sprd_ctrl, TImCnrRdmaDataSprdCcTbl* rdma_sprd_ctrl )
{
	rdma_sprd_ctrl->sprd.bit.sprd = sprd_ctrl->enable;
	// write signed data
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprd_ctrl->sprdCbbd.SPRDCBBD1, union io_cnr_cspr_reg_sprdcbbd_1, sprdCbbd1, sprd_ctrl->cbTable.bd1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprd_ctrl->sprdCbbd.SPRDCBBD1, union io_cnr_cspr_reg_sprdcbbd_1, sprdCbbd2, sprd_ctrl->cbTable.bd2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprd_ctrl->sprdCbbd.SPRDCBBD1, union io_cnr_cspr_reg_sprdcbbd_1, SPRDCBBD_3, sprd_ctrl->cbTable.bd3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprd_ctrl->sprdCbbd.SPRDCBBD1, union io_cnr_cspr_reg_sprdcbbd_1, SPRDCBBD_4, sprd_ctrl->cbTable.bd4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprd_ctrl->sprdCbbd.SPRDCBBD2, union io_cnr_cspr_reg_sprdcbbd_2, SPRDCBBD_5, sprd_ctrl->cbTable.bd5 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprd_ctrl->sprdCbof.SPRDCBOF1, union io_cnr_cspr_reg_sprdcbof_1, SPRDCBOF_0, sprd_ctrl->cbTable.of0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprd_ctrl->sprdCbof.SPRDCBOF1, union io_cnr_cspr_reg_sprdcbof_1, sprdCbof1, sprd_ctrl->cbTable.of1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprd_ctrl->sprdCbof.SPRDCBOF1, union io_cnr_cspr_reg_sprdcbof_1, sprdCbof2, sprd_ctrl->cbTable.of2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprd_ctrl->sprdCbof.SPRDCBOF1, union io_cnr_cspr_reg_sprdcbof_1, SPRDCBOF_3, sprd_ctrl->cbTable.of3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprd_ctrl->sprdCbof.SPRDCBOF2, union io_cnr_cspr_reg_sprdcbof_2, SPRDCBOF_4, sprd_ctrl->cbTable.of4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprd_ctrl->sprdCbof.SPRDCBOF2, union io_cnr_cspr_reg_sprdcbof_2, SPRDCBOF_5, sprd_ctrl->cbTable.of5 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprd_ctrl->sprdCbga.SPRDCBGA1, union io_cnr_cspr_reg_sprdcbga_1, SPRDCBGA_0, sprd_ctrl->cbTable.gain0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprd_ctrl->sprdCbga.SPRDCBGA1, union io_cnr_cspr_reg_sprdcbga_1, sprdCbga1, sprd_ctrl->cbTable.gain1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprd_ctrl->sprdCbga.SPRDCBGA2, union io_cnr_cspr_reg_sprdcbga_2, sprdCbga2, sprd_ctrl->cbTable.gain2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprd_ctrl->sprdCbga.SPRDCBGA2, union io_cnr_cspr_reg_sprdcbga_2, sprdCbga3, sprd_ctrl->cbTable.gain3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprd_ctrl->sprdCbga.SPRDCBGA3, union io_cnr_cspr_reg_sprdcbga_3, SPRDCBGA_4, sprd_ctrl->cbTable.gain4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprd_ctrl->sprdCbga.SPRDCBGA3, union io_cnr_cspr_reg_sprdcbga_3, SPRDCBGA_5, sprd_ctrl->cbTable.gain5 );

	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprd_ctrl->sprdCrbd.SPRDCRBD1, union io_cnr_cspr_reg_sprdcrbd_1, sprdCrbd1, sprd_ctrl->crTable.bd1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprd_ctrl->sprdCrbd.SPRDCRBD1, union io_cnr_cspr_reg_sprdcrbd_1, sprdCrbd2, sprd_ctrl->crTable.bd2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprd_ctrl->sprdCrbd.SPRDCRBD1, union io_cnr_cspr_reg_sprdcrbd_1, SPRDCRBD_3, sprd_ctrl->crTable.bd3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprd_ctrl->sprdCrbd.SPRDCRBD1, union io_cnr_cspr_reg_sprdcrbd_1, SPRDCRBD_4, sprd_ctrl->crTable.bd4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprd_ctrl->sprdCrbd.SPRDCRBD2, union io_cnr_cspr_reg_sprdcrbd_2, SPRDCRBD_5, sprd_ctrl->crTable.bd5 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprd_ctrl->sprdCrof.SPRDCROF1, union io_cnr_cspr_reg_sprdcrof_1, SPRDCROF_0, sprd_ctrl->crTable.of0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprd_ctrl->sprdCrof.SPRDCROF1, union io_cnr_cspr_reg_sprdcrof_1, sprdCrof1, sprd_ctrl->crTable.of1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprd_ctrl->sprdCrof.SPRDCROF1, union io_cnr_cspr_reg_sprdcrof_1, sprdCrof2, sprd_ctrl->crTable.of2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprd_ctrl->sprdCrof.SPRDCROF1, union io_cnr_cspr_reg_sprdcrof_1, SPRDCROF_3, sprd_ctrl->crTable.of3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprd_ctrl->sprdCrof.SPRDCROF2, union io_cnr_cspr_reg_sprdcrof_2, SPRDCROF_4, sprd_ctrl->crTable.of4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprd_ctrl->sprdCrof.SPRDCROF2, union io_cnr_cspr_reg_sprdcrof_2, SPRDCROF_5, sprd_ctrl->crTable.of5 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprd_ctrl->sprdCrga.SPRDCRGA1, union io_cnr_cspr_reg_sprdcrga_1, SPRDCRGA_0, sprd_ctrl->crTable.gain0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprd_ctrl->sprdCrga.SPRDCRGA1, union io_cnr_cspr_reg_sprdcrga_1, sprdCrga1, sprd_ctrl->crTable.gain1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprd_ctrl->sprdCrga.SPRDCRGA2, union io_cnr_cspr_reg_sprdcrga_2, sprdCrga2, sprd_ctrl->crTable.gain2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprd_ctrl->sprdCrga.SPRDCRGA2, union io_cnr_cspr_reg_sprdcrga_2, sprdCrga3, sprd_ctrl->crTable.gain3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprd_ctrl->sprdCrga.SPRDCRGA3, union io_cnr_cspr_reg_sprdcrga_3, SPRDCRGA_4, sprd_ctrl->crTable.gain4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_sprd_ctrl->sprdCrga.SPRDCRGA3, union io_cnr_cspr_reg_sprdcrga_3, SPRDCRGA_5, sprd_ctrl->crTable.gain5 );
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
INT32 im_cnr_set_rdma_value_ofl_ctrl_c(ImCnrSet*self, const TImCnrCtrlC* const spr_ctrl_c, TImCnrRdmaDataCtrlC* const rdma_ctrl_c )
{
#ifdef CO_PARAM_CHECK
	if( spr_ctrl_c == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_ofl_ctrl_c() Parameter(spr_ctrl_c) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_ctrl_c == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_ofl_ctrl_c() Parameter(rdma_ctrl_c) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_ctrl_c, 0, sizeof(TImCnrRdmaDataCtrlC) );
	imCnrConvertRdmaValueCtrlC( spr_ctrl_c, rdma_ctrl_c );
	return D_DDIM_OK;
}

/*
CNR(OTF) Set SPR CTRL-C setting parameter information
*/
INT32 im_cnr_set_rdma_value_otf_ctrl_c(ImCnrSet*self, const TImCnrCtrlC* const spr_ctrl_c, TImCnrRdmaDataCtrlC* const rdma_ctrl_c )
{
#ifdef CO_PARAM_CHECK
	if( spr_ctrl_c == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_otf_ctrl_c() Parameter(spr_ctrl_c) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_ctrl_c == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_otf_ctrl_c() Parameter(rdma_ctrl_c) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_ctrl_c, 0, sizeof(TImCnrRdmaDataCtrlC) );
	imCnrConvertRdmaValueCtrlC( spr_ctrl_c, rdma_ctrl_c );
	return D_DDIM_OK;
}

/*
CNR(OFL) Set CSPR Mid_Y Table setting parameter information
*/
INT32 im_cnr_set_rdma_value_ofl_cspr_mid_y_table(ImCnrSet*self, const TImCnrTable* const spr_cspr_mid_y, TImCnrRdmaDataCsprMidYTbl* const rdma_cspr_mid_y_table )
{
#ifdef CO_PARAM_CHECK
	if( spr_cspr_mid_y == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_ofl_cspr_mid_y_table() Parameter(spr_cspr_mid_y) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_mid_y_table == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_ofl_cspr_mid_y_table() Parameter(rdma_cspr_mid_y_table) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_mid_y_table, 0, sizeof(TImCnrRdmaDataCsprMidYTbl) );
	imCnrConvertRdmaCsprMidYTable( spr_cspr_mid_y, rdma_cspr_mid_y_table );
	return D_DDIM_OK;
}

/*
CNR(OTF) Set CSPR Mid_Y Table setting parameter information
*/
INT32 im_cnr_set_rdma_value_otf_cspr_mid_y_table(ImCnrSet*self, const TImCnrTable* const spr_cspr_mid_y, TImCnrRdmaDataCsprMidYTbl* const rdma_cspr_mid_y_table )
{
#ifdef CO_PARAM_CHECK
	if( spr_cspr_mid_y == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_otf_cspr_mid_y_table() Parameter(spr_cspr_mid_y) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_mid_y_table == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_otf_cspr_mid_y_table() Parameter(rdma_cspr_mid_y_table) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_mid_y_table, 0, sizeof(TImCnrRdmaDataCsprMidYTbl) );
	imCnrConvertRdmaCsprMidYTable( spr_cspr_mid_y, rdma_cspr_mid_y_table );
	return D_DDIM_OK;
}

/*
CNR(OFL) Set CSPR Mid_CC_Y Table setting parameter information
*/
INT32 im_cnr_set_rdma_value_ofl_cspr_mid_cc_y_table(ImCnrSet*self, const TImCnrTable* const spr_cspr_mid_cc_y, TImCnrRdmaDataCsprMidCcYTbl* const rdma_cspr_mid_cc_y_table )
{
#ifdef CO_PARAM_CHECK
	if( spr_cspr_mid_cc_y == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_ofl_cspr_mid_cc_y_table() Parameter(spr_cspr_mid_cc_y) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_mid_cc_y_table == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_ofl_cspr_mid_cc_y_table() Parameter(rdma_cspr_mid_cc_y_table) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_mid_cc_y_table, 0, sizeof(TImCnrRdmaDataCsprMidCcYTbl) );
	imCnrConvertRdmaCsprMidCcYTable( spr_cspr_mid_cc_y, rdma_cspr_mid_cc_y_table );
	return D_DDIM_OK;
}

/*
CNR(OTF) Set CSPR Mid_CC_Y Table setting parameter information
*/
INT32 im_cnr_set_rdma_value_otf_cspr_mid_cc_y_table(ImCnrSet*self, const TImCnrTable* const spr_cspr_mid_cc_y, TImCnrRdmaDataCsprMidCcYTbl* const rdma_cspr_mid_cc_y_table )
{
#ifdef CO_PARAM_CHECK
	if( spr_cspr_mid_cc_y == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_otf_cspr_mid_cc_y_table() Parameter(spr_cspr_mid_cc_y) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_mid_cc_y_table == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_otf_cspr_mid_cc_y_table() Parameter(rdma_cspr_mid_cc_y_table) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_mid_cc_y_table, 0, sizeof(TImCnrRdmaDataCsprMidCcYTbl) );
	imCnrConvertRdmaCsprMidCcYTable( spr_cspr_mid_cc_y, rdma_cspr_mid_cc_y_table );
	return D_DDIM_OK;
}

/*
CNR(OFL) Set CSPR Mid_CC_C Table setting parameter information
*/
INT32 im_cnr_set_rdma_value_ofl_cspr_mid_cc_c_table(ImCnrSet*self, const TImCnrTable* const spr_cspr_mid_cc_c, TImCnrRdmaDataCsprMidCcCTbl* const rdma_cspr_mid_cc_c_table )
{
#ifdef CO_PARAM_CHECK
	if( spr_cspr_mid_cc_c == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_ofl_cspr_mid_cc_c_table() Parameter(spr_cspr_mid_cc_c) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_mid_cc_c_table == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_ofl_cspr_mid_cc_c_table() Parameter(rdma_cspr_mid_cc_c_table) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_mid_cc_c_table, 0, sizeof(TImCnrRdmaDataCsprMidCcCTbl) );
	imCnrConvertRdmaCsprMidCcCTable( spr_cspr_mid_cc_c, rdma_cspr_mid_cc_c_table );
	return D_DDIM_OK;
}

/*
CNR(OTF) Set CSPR Mid_CC_C Table setting parameter information
*/
INT32 im_cnr_set_rdma_value_otf_cspr_mid_cc_c_table(ImCnrSet*self, const TImCnrTable* const spr_cspr_mid_cc_c, TImCnrRdmaDataCsprMidCcCTbl* const rdma_cspr_mid_cc_c_table )
{
#ifdef CO_PARAM_CHECK
	if( spr_cspr_mid_cc_c == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_otf_cspr_mid_cc_c_table() Parameter(spr_cspr_mid_cc_c) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_mid_cc_c_table == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_otf_cspr_mid_cc_c_table() Parameter(rdma_cspr_mid_cc_c_table) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_mid_cc_c_table, 0, sizeof(TImCnrRdmaDataCsprMidCcCTbl) );
	imCnrConvertRdmaCsprMidCcCTable( spr_cspr_mid_cc_c, rdma_cspr_mid_cc_c_table );
	return D_DDIM_OK;
}

/*
CNR(OFL) Set CSPR Low_Y Table setting parameter information
*/
INT32 im_cnr_set_rdma_value_ofl_cspr_low_y_table(ImCnrSet*self, const TImCnrTable* const spr_cspr_low_y, TImCnrRdmaDataCsprLowYTbl* const rdma_cspr_low_y_table )
{
#ifdef CO_PARAM_CHECK
	if( spr_cspr_low_y == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_ofl_cspr_low_y_table() Parameter(spr_cspr_low_y) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_low_y_table == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_ofl_cspr_low_y_table() Parameter(rdma_cspr_low_y_table) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_low_y_table, 0, sizeof(TImCnrRdmaDataCsprLowYTbl) );
	imCnrConvertRdmaCsprLowYTable( spr_cspr_low_y, rdma_cspr_low_y_table );
	return D_DDIM_OK;
}

/*
CNR(OTF) Set CSPR Low_Y Table setting parameter information
*/
INT32 im_cnr_set_rdma_value_otf_cspr_low_y_table(ImCnrSet*self, const TImCnrTable* const spr_cspr_low_y, TImCnrRdmaDataCsprLowYTbl* const rdma_cspr_low_y_table )
{
#ifdef CO_PARAM_CHECK
	if( spr_cspr_low_y == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_otf_cspr_low_y_table() Parameter(spr_cspr_low_y) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_low_y_table == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_otf_cspr_low_y_table() Parameter(rdma_cspr_low_y_table) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_low_y_table, 0, sizeof(TImCnrRdmaDataCsprLowYTbl) );
	imCnrConvertRdmaCsprLowYTable( spr_cspr_low_y, rdma_cspr_low_y_table );
	return D_DDIM_OK;
}

/*
CNR(OFL) Set CSPR Low_CC_Y Table setting parameter information
*/
INT32 im_cnr_set_rdma_value_ofl_cspr_low_cc_y_table(ImCnrSet*self, const TImCnrTable* const spr_cspr_low_cc_y, TImCnrRdmaDataCsprLowCcYTbl* const rdma_cspr_low_cc_y_table )
{
#ifdef CO_PARAM_CHECK
	if( spr_cspr_low_cc_y == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_ofl_cspr_low_cc_y_table() Parameter(spr_cspr_low_cc_y) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_low_cc_y_table == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_ofl_cspr_low_cc_y_table() Parameter(rdma_cspr_low_cc_y_table) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_low_cc_y_table, 0, sizeof(TImCnrRdmaDataCsprLowCcYTbl) );
	imCnrConvertRdmaCsprLowCcYTable( spr_cspr_low_cc_y, rdma_cspr_low_cc_y_table );
	return D_DDIM_OK;
}

/*
CNR(OTF) Set CSPR Low_CC_Y Table setting parameter information
*/
INT32 im_cnr_set_rdma_value_otf_cspr_low_cc_y_table(ImCnrSet*self, const TImCnrTable* const spr_cspr_low_cc_y, TImCnrRdmaDataCsprLowCcYTbl* const rdma_cspr_low_cc_y_table )
{
#ifdef CO_PARAM_CHECK
	if( spr_cspr_low_cc_y == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_otf_cspr_low_cc_y_table() Parameter(spr_cspr_low_cc_y) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_low_cc_y_table == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_otf_cspr_low_cc_y_table() Parameter(rdma_cspr_low_cc_y_table) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_low_cc_y_table, 0, sizeof(TImCnrRdmaDataCsprLowCcYTbl) );
	imCnrConvertRdmaCsprLowCcYTable( spr_cspr_low_cc_y, rdma_cspr_low_cc_y_table );
	return D_DDIM_OK;
}

/*
CNR(OFL) Set CSPR Low_CC_C Table setting parameter information
*/
INT32 im_cnr_set_rdma_value_ofl_cspr_low_cc_c_table(ImCnrSet*self, const TImCnrTable* const spr_cspr_low_cc_c, TImCnrRdmaDataCsprLowCcCTbl* const rdma_cspr_low_cc_c_table )
{
#ifdef CO_PARAM_CHECK
	if( spr_cspr_low_cc_c == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_ofl_cspr_low_cc_c_table() Parameter(spr_cspr_low_cc_c) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_low_cc_c_table == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_ofl_cspr_low_cc_c_table() Parameter(rdma_cspr_low_cc_c_table) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_low_cc_c_table, 0, sizeof(TImCnrRdmaDataCsprLowCcCTbl) );
	imCnrConvertRdmaCsprLowCcCTable( spr_cspr_low_cc_c, rdma_cspr_low_cc_c_table );
	return D_DDIM_OK;
}

/*
CNR(OTF) Set CSPR Low_CC_C Table setting parameter information
*/
INT32 im_cnr_set_rdma_value_otf_cspr_low_cc_c_table(ImCnrSet*self, const TImCnrTable* const spr_cspr_low_cc_c, TImCnrRdmaDataCsprLowCcCTbl* const rdma_cspr_low_cc_c_table )
{
#ifdef CO_PARAM_CHECK
	if( spr_cspr_low_cc_c == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_otf_cspr_low_cc_c_table() Parameter(spr_cspr_low_cc_c) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_low_cc_c_table == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_otf_cspr_low_cc_c_table() Parameter(rdma_cspr_low_cc_c_table) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_low_cc_c_table, 0, sizeof(TImCnrRdmaDataCsprLowCcCTbl) );
	imCnrConvertRdmaCsprLowCcCTable( spr_cspr_low_cc_c, rdma_cspr_low_cc_c_table );
	return D_DDIM_OK;
}

/*
CNR(OFL) Set CSPR Edge Table setting parameter information
*/
INT32 im_cnr_set_rdma_value_ofl_cspr_edge_table(ImCnrSet*self, const TImCnrTable* const spr_cspr_edge, TImCnrRdmaDataCsprEdgeTbl* const rdma_cspr_edge_table )
{
#ifdef CO_PARAM_CHECK
	if( spr_cspr_edge == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_ofl_cspr_edge_table() Parameter(spr_cspr_edge) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_edge_table == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_ofl_cspr_edge_table() Parameter(rdma_cspr_edge_table) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_edge_table, 0, sizeof(TImCnrRdmaDataCsprEdgeTbl) );
	imCnrConvertRdmaCsprEdgeTable( spr_cspr_edge, rdma_cspr_edge_table );
	return D_DDIM_OK;
}

/*
CNR(OTF) Set CSPR Edge Table setting parameter information
*/
INT32 im_cnr_set_rdma_value_otf_cspr_edge_table(ImCnrSet*self, const TImCnrTable* const spr_cspr_edge, TImCnrRdmaDataCsprEdgeTbl* const rdma_cspr_edge_table )
{
#ifdef CO_PARAM_CHECK
	if( spr_cspr_edge == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_otf_cspr_edge_table() Parameter(spr_cspr_edge) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_edge_table == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_otf_cspr_edge_table() Parameter(rdma_cspr_edge_table) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_edge_table, 0, sizeof(TImCnrRdmaDataCsprEdgeTbl) );
	imCnrConvertRdmaCsprEdgeTable( spr_cspr_edge, rdma_cspr_edge_table );
	return D_DDIM_OK;
}

/*
CNR(OFL) Set CSPR Hue Specified Table setting parameter information
*/
INT32 im_cnr_set_rdma_value_ofl_cspr_hue_spec_table(ImCnrSet*self, const TImCnrHueSpecTable* const spr_cspr_hue, TImCnrRdmaDataCsprHueTbl* const rdma_cspr_hue_table )
{
#ifdef CO_PARAM_CHECK
	if( spr_cspr_hue == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_ofl_cspr_hue_spec_table() Parameter(spr_cspr_hue) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_hue_table == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_ofl_cspr_hue_spec_table() Parameter(rdma_cspr_hue_table) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_hue_table, 0, sizeof(TImCnrRdmaDataCsprHueTbl) );
	imCnrConvertRdmaCsprHueTable( spr_cspr_hue, rdma_cspr_hue_table );
	return D_DDIM_OK;
}

/*
CNR(OTF) Set CSPR Hue Specified Table setting parameter information
*/
INT32 im_cnr_set_rdma_value_otf_cspr_hue_spec_table(ImCnrSet*self, const TImCnrHueSpecTable* const spr_cspr_hue, TImCnrRdmaDataCsprHueTbl* const rdma_cspr_hue_table )
{
#ifdef CO_PARAM_CHECK
	if( spr_cspr_hue == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_otf_cspr_hue_spec_table() Parameter(spr_cspr_hue) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_hue_table == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_otf_cspr_hue_spec_table() Parameter(rdma_cspr_hue_table) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_hue_table, 0, sizeof(TImCnrRdmaDataCsprHueTbl) );
	imCnrConvertRdmaCsprHueTable( spr_cspr_hue, rdma_cspr_hue_table );
	return D_DDIM_OK;
}

/*
CNR(OFL) Set CSPR SPRS_CC Table setting parameter information
*/
INT32 im_cnr_set_rdma_value_ofl_cspr_sprs_cc_table(ImCnrSet*self, const TImCnrCtrlCcSrcDst* const cspr_sprs_cc, TImCnrRdmaDataSprsCcTbl* const rdma_cspr_sprs_cc )
{
#ifdef CO_PARAM_CHECK
	if( cspr_sprs_cc == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_ofl_cspr_sprs_cc_table() Parameter(cspr_sprs_cc) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_sprs_cc == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_ofl_cspr_sprs_cc_table() Parameter(rdma_cspr_sprs_cc) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_sprs_cc, 0, sizeof(TImCnrRdmaDataSprsCcTbl) );
	imCnrConvertRdmaCsprSprsCc( cspr_sprs_cc, rdma_cspr_sprs_cc );
	return D_DDIM_OK;
}

/*
CNR(OTF) Set CSPR SPRS_CC Table setting parameter information
*/
INT32 im_cnr_set_rdma_value_otf_cspr_sprs_cc_table(ImCnrSet*self, const TImCnrCtrlCcSrcDst* const cspr_sprs_cc, TImCnrRdmaDataSprsCcTbl* const rdma_cspr_sprs_cc )
{
#ifdef CO_PARAM_CHECK
	if( cspr_sprs_cc == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_otf_cspr_sprs_cc_table() Parameter(cspr_sprs_cc) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_sprs_cc == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_otf_cspr_sprs_cc_table() Parameter(rdma_cspr_sprs_cc) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_sprs_cc, 0, sizeof(TImCnrRdmaDataSprsCcTbl) );
	imCnrConvertRdmaCsprSprsCc( cspr_sprs_cc, rdma_cspr_sprs_cc );
	return D_DDIM_OK;
}

/*
CNR(OFL) Set CSPR SPRD_CC Table setting parameter information
*/
INT32 im_cnr_set_rdma_value_ofl_cspr_sprd_cc_table(ImCnrSet*self, const TImCnrCtrlCcSrcDst* const cspr_sprd_cc, TImCnrRdmaDataSprdCcTbl* const rdma_cspr_sprd_cc )
{
#ifdef CO_PARAM_CHECK
	if( cspr_sprd_cc == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_ofl_cspr_sprd_cc_table() Parameter(cspr_sprd_cc) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_sprd_cc == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_ofl_cspr_sprd_cc_table() Parameter(rdma_cspr_sprd_cc) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_sprd_cc, 0, sizeof(TImCnrRdmaDataSprdCcTbl) );
	imCnrConvertRdmaCsprSprdCc( cspr_sprd_cc, rdma_cspr_sprd_cc );
	return D_DDIM_OK;
}

/*
CNR(OTF) Set CSPR SPRD_CC Table setting parameter information
*/
INT32 im_cnr_set_rdma_value_otf_cspr_sprd_cc_table(ImCnrSet*self, const TImCnrCtrlCcSrcDst* const cspr_sprd_cc, TImCnrRdmaDataSprdCcTbl* const rdma_cspr_sprd_cc )
{
#ifdef CO_PARAM_CHECK
	if( cspr_sprd_cc == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_otf_cspr_sprd_cc_table() Parameter(cspr_sprd_cc) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_cspr_sprd_cc == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_otf_cspr_sprd_cc_table() Parameter(rdma_cspr_sprd_cc) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_cspr_sprd_cc, 0, sizeof(TImCnrRdmaDataSprdCcTbl) );
	imCnrConvertRdmaCsprSprdCc( cspr_sprd_cc, rdma_cspr_sprd_cc );
	return D_DDIM_OK;
}

/*
CNR(OFL) Set YSPR Table setting parameter information
*/
INT32 im_cnr_set_rdma_value_ofl_yspr_table(ImCnrSet*self, const TImCnrTable* const yspr_table, TImCnrRdmaDataOflYsprTbl* const rdma_yspr_table )
{
#ifdef CO_PARAM_CHECK
	if( yspr_table == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_ofl_yspr_table() Parameter(yspr_table) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_yspr_table == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_ofl_yspr_table() Parameter(rdma_yspr_table) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_yspr_table, 0, sizeof(TImCnrRdmaDataOflYsprTbl) );
	rdma_yspr_table->ysprDyeybd.YSPRDYEYBD1.bit.ysprDyeybd1	= yspr_table->bd1;
	rdma_yspr_table->ysprDyeybd.YSPRDYEYBD1.bit.ysprDyeybd2	= yspr_table->bd2;
	rdma_yspr_table->ysprDyeybd.YSPRDYEYBD1.bit.YSPRDYEYBD_3	= yspr_table->bd3;
	rdma_yspr_table->ysprDyeybd.YSPRDYEYBD1.bit.YSPRDYEYBD_4	= yspr_table->bd4;
	rdma_yspr_table->ysprDyeybd.YSPRDYEYBD2.bit.YSPRDYEYBD_5	= yspr_table->bd5;
	rdma_yspr_table->ysprDyeyof.YSPRDYEYOF1.bit.YSPRDYEYOF_0	= yspr_table->of0;
	rdma_yspr_table->ysprDyeyof.YSPRDYEYOF1.bit.ysprDyeyof1	= yspr_table->of1;
	rdma_yspr_table->ysprDyeyof.YSPRDYEYOF1.bit.ysprDyeyof2	= yspr_table->of2;
	rdma_yspr_table->ysprDyeyof.YSPRDYEYOF1.bit.YSPRDYEYOF_3	= yspr_table->of3;
	rdma_yspr_table->ysprDyeyof.YSPRDYEYOF2.bit.YSPRDYEYOF_4	= yspr_table->of4;
	rdma_yspr_table->ysprDyeyof.YSPRDYEYOF2.bit.YSPRDYEYOF_5	= yspr_table->of5;
	// write signed data
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_yspr_table->ysprDyeyga.YSPRDYEYGA1, union io_cnr_ofl_reg_yspr_ysprdyeyga_1, YSPRDYEYGA_0, yspr_table->gain0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_yspr_table->ysprDyeyga.YSPRDYEYGA1, union io_cnr_ofl_reg_yspr_ysprdyeyga_1, ysprDyeyga1, yspr_table->gain1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_yspr_table->ysprDyeyga.YSPRDYEYGA1, union io_cnr_ofl_reg_yspr_ysprdyeyga_1, ysprDyeyga2, yspr_table->gain2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_yspr_table->ysprDyeyga.YSPRDYEYGA1, union io_cnr_ofl_reg_yspr_ysprdyeyga_1, YSPRDYEYGA_3, yspr_table->gain3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_yspr_table->ysprDyeyga.YSPRDYEYGA2, union io_cnr_ofl_reg_yspr_ysprdyeyga_2, YSPRDYEYGA_4, yspr_table->gain4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( rdma_yspr_table->ysprDyeyga.YSPRDYEYGA2, union io_cnr_ofl_reg_yspr_ysprdyeyga_2, YSPRDYEYGA_5, yspr_table->gain5 );
	return D_DDIM_OK;
}

/*
CNR(OFL) Set SPR CTRL-Y setting parameter information
*/
INT32 im_cnr_set_rdma_value_ofl_ctrl_y(ImCnrSet*self, const TImCnrOflCtrlY* const spr_ctrl_y, TImCnrRdmaDataOflCtrlY* const rdma_ctrl_y )
{
#ifdef CO_PARAM_CHECK
	if( spr_ctrl_y == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_ofl_ctrl_y() Parameter(spr_ctrl_y) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdma_ctrl_y == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_set_rdma_value_ofl_ctrl_y() Parameter(rdma_ctrl_y) is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	memset( rdma_ctrl_y, 0, sizeof(TImCnrRdmaDataOflCtrlY) );
	rdma_ctrl_y->ysprEn.bit.ysprEn			= spr_ctrl_y->enable;
	rdma_ctrl_y->ysprMode.bit.YSPRMD		= spr_ctrl_y->thresholdType;
	rdma_ctrl_y->ysprMode.bit.YSPRFE		= spr_ctrl_y->level;
	rdma_ctrl_y->ysprFxey.bit.YSPRFXEYV		= spr_ctrl_y->vYThreshold;
	rdma_ctrl_y->ysprFxey.bit.YSPRFXEYH		= spr_ctrl_y->hYThreshold;
	rdma_ctrl_y->ysprFxec.bit.YSPRFXECV		= spr_ctrl_y->vCThreshold;
	rdma_ctrl_y->ysprFxec.bit.YSPRFXECH		= spr_ctrl_y->hCThreshold;
	rdma_ctrl_y->ysprAlpbd.bit.ysprAlpbd	= spr_ctrl_y->alphaBlendRatio;
	return D_DDIM_OK;
}

#endif

ImCnrSet *im_cnr_set_new(void)
{
	ImCnrSet* self = k_object_new_with_private(IM_TYPE_CNR_SET,sizeof(ImCnrSetPrivate));
	return self;
}
