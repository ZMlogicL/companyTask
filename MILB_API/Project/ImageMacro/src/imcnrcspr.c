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

#include "imcnrcspr.h"
#include "imcnr.h"
#include "imcnrset.h"
#include "imcnrget.h"
#include "imcnrinit.h"
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

K_TYPE_DEFINE_WITH_PRIVATE(ImCnrCspr, im_cnr_cspr);
#define IM_CNR_CSPR_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImCnrCsprPrivate, IM_TYPE_CNR_CSPR))

struct _ImCnrCsprPrivate
{
	int a;
};

/*----------------------------------------------------------------------*/
/* Local Method Definition												*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
static void im_cnr_cspr_constructor(ImCnrCspr *self)
{
}

static void im_cnr_cspr_destructor(ImCnrCspr *self)
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
Set SPR table for Y
*/
INT32 im_cnr_cspr_ofl_set_yspr_table(ImCnrCspr*self, UCHAR ch, const TImCnrTable* const spr_yspr )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_cspr_ofl_set_yspr_table() error. input channel error : %d\n", ch));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_yspr == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_cspr_ofl_set_yspr_table() Parameter is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnr_on_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	ImCnr_IO_CNR(ch)->OFL_REG_YSPR.ysprDyeybd.YSPRDYEYBD1.bit.ysprDyeybd1	= spr_yspr->bd1;
	ImCnr_IO_CNR(ch)->OFL_REG_YSPR.ysprDyeybd.YSPRDYEYBD1.bit.ysprDyeybd2	= spr_yspr->bd2;
	ImCnr_IO_CNR(ch)->OFL_REG_YSPR.ysprDyeybd.YSPRDYEYBD1.bit.YSPRDYEYBD_3	= spr_yspr->bd3;
	ImCnr_IO_CNR(ch)->OFL_REG_YSPR.ysprDyeybd.YSPRDYEYBD1.bit.YSPRDYEYBD_4	= spr_yspr->bd4;
	ImCnr_IO_CNR(ch)->OFL_REG_YSPR.ysprDyeybd.YSPRDYEYBD2.bit.YSPRDYEYBD_5	= spr_yspr->bd5;
	ImCnr_IO_CNR(ch)->OFL_REG_YSPR.ysprDyeyof.YSPRDYEYOF1.bit.YSPRDYEYOF_0	= spr_yspr->of0;
	ImCnr_IO_CNR(ch)->OFL_REG_YSPR.ysprDyeyof.YSPRDYEYOF1.bit.ysprDyeyof1	= spr_yspr->of1;
	ImCnr_IO_CNR(ch)->OFL_REG_YSPR.ysprDyeyof.YSPRDYEYOF1.bit.ysprDyeyof2	= spr_yspr->of2;
	ImCnr_IO_CNR(ch)->OFL_REG_YSPR.ysprDyeyof.YSPRDYEYOF1.bit.YSPRDYEYOF_3	= spr_yspr->of3;
	ImCnr_IO_CNR(ch)->OFL_REG_YSPR.ysprDyeyof.YSPRDYEYOF2.bit.YSPRDYEYOF_4	= spr_yspr->of4;
	ImCnr_IO_CNR(ch)->OFL_REG_YSPR.ysprDyeyof.YSPRDYEYOF2.bit.YSPRDYEYOF_5	= spr_yspr->of5;

	// write signed data
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_REG_YSPR.ysprDyeyga.YSPRDYEYGA1, union io_cnr_ofl_reg_yspr_ysprdyeyga_1, YSPRDYEYGA_0, spr_yspr->gain0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_REG_YSPR.ysprDyeyga.YSPRDYEYGA1, union io_cnr_ofl_reg_yspr_ysprdyeyga_1, ysprDyeyga1, spr_yspr->gain1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_REG_YSPR.ysprDyeyga.YSPRDYEYGA1, union io_cnr_ofl_reg_yspr_ysprdyeyga_1, ysprDyeyga2, spr_yspr->gain2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_REG_YSPR.ysprDyeyga.YSPRDYEYGA1, union io_cnr_ofl_reg_yspr_ysprdyeyga_1, YSPRDYEYGA_3, spr_yspr->gain3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_REG_YSPR.ysprDyeyga.YSPRDYEYGA2, union io_cnr_ofl_reg_yspr_ysprdyeyga_2, YSPRDYEYGA_4, spr_yspr->gain4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_REG_YSPR.ysprDyeyga.YSPRDYEYGA2, union io_cnr_ofl_reg_yspr_ysprdyeyga_2, YSPRDYEYGA_5, spr_yspr->gain5 );

	im_cnr_off_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	return D_DDIM_OK;
}

/*
Set SPR Y table for Middle frequency CbCr
*/
INT32 im_cnr_cspr_ofl_set_cspr_mid_y_table(ImCnrCspr*self, UCHAR ch, const TImCnrTable* const spr_cspr_mid_y )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_cspr_ofl_set_cspr_mid_y_table() error. input channel error : %d\n", ch));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_cspr_mid_y == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_cspr_ofl_set_cspr_mid_y_table() Parameter is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnr_on_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcysClbd.MCYSCLBD1.bit.mcysClbd1	= spr_cspr_mid_y->bd1;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcysClbd.MCYSCLBD1.bit.mcysClbd2	= spr_cspr_mid_y->bd2;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcysClbd.MCYSCLBD1.bit.MCYSCLBD_3	= spr_cspr_mid_y->bd3;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcysClbd.MCYSCLBD1.bit.MCYSCLBD_4	= spr_cspr_mid_y->bd4;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcysClbd.MCYSCLBD2.bit.MCYSCLBD_5	= spr_cspr_mid_y->bd5;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcysClof.MCYSCLOF1.bit.MCYSCLOF_0	= spr_cspr_mid_y->of0;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcysClof.MCYSCLOF1.bit.mcysClof1	= spr_cspr_mid_y->of1;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcysClof.MCYSCLOF1.bit.mcysClof2	= spr_cspr_mid_y->of2;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcysClof.MCYSCLOF1.bit.MCYSCLOF_3	= spr_cspr_mid_y->of3;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcysClof.MCYSCLOF2.bit.MCYSCLOF_4	= spr_cspr_mid_y->of4;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcysClof.MCYSCLOF2.bit.MCYSCLOF_5	= spr_cspr_mid_y->of5;

	// write signed data
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcysClga.MCYSCLGA1, union io_cnr_cspr_reg_mcysclga_1, MCYSCLGA_0, spr_cspr_mid_y->gain0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcysClga.MCYSCLGA1, union io_cnr_cspr_reg_mcysclga_1, mcysClga1, spr_cspr_mid_y->gain1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcysClga.MCYSCLGA1, union io_cnr_cspr_reg_mcysclga_1, mcysClga2, spr_cspr_mid_y->gain2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcysClga.MCYSCLGA1, union io_cnr_cspr_reg_mcysclga_1, MCYSCLGA_3, spr_cspr_mid_y->gain3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcysClga.MCYSCLGA2, union io_cnr_cspr_reg_mcysclga_2, MCYSCLGA_4, spr_cspr_mid_y->gain4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcysClga.MCYSCLGA2, union io_cnr_cspr_reg_mcysclga_2, MCYSCLGA_5, spr_cspr_mid_y->gain5 );

	im_cnr_off_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	return D_DDIM_OK;
}

/*
Set SPR Y table for Middle frequency CbCr
*/
INT32 im_cnr_cspr_otf_set_cspr_mid_y_table(ImCnrCspr*self, UCHAR ch, const TImCnrTable* const spr_cspr_mid_y )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_cspr_otf_set_cspr_mid_y_table() error. input channel error : %d\n", ch));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_cspr_mid_y == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_cspr_otf_set_cspr_mid_y_table() Parameter is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnr_on_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcysClbd.MCYSCLBD1.bit.mcysClbd1	= spr_cspr_mid_y->bd1;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcysClbd.MCYSCLBD1.bit.mcysClbd2	= spr_cspr_mid_y->bd2;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcysClbd.MCYSCLBD1.bit.MCYSCLBD_3	= spr_cspr_mid_y->bd3;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcysClbd.MCYSCLBD1.bit.MCYSCLBD_4	= spr_cspr_mid_y->bd4;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcysClbd.MCYSCLBD2.bit.MCYSCLBD_5	= spr_cspr_mid_y->bd5;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcysClof.MCYSCLOF1.bit.MCYSCLOF_0	= spr_cspr_mid_y->of0;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcysClof.MCYSCLOF1.bit.mcysClof1	= spr_cspr_mid_y->of1;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcysClof.MCYSCLOF1.bit.mcysClof2	= spr_cspr_mid_y->of2;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcysClof.MCYSCLOF1.bit.MCYSCLOF_3	= spr_cspr_mid_y->of3;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcysClof.MCYSCLOF2.bit.MCYSCLOF_4	= spr_cspr_mid_y->of4;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcysClof.MCYSCLOF2.bit.MCYSCLOF_5	= spr_cspr_mid_y->of5;

	// write signed data
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcysClga.MCYSCLGA1, union io_cnr_cspr_reg_mcysclga_1, MCYSCLGA_0, spr_cspr_mid_y->gain0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcysClga.MCYSCLGA1, union io_cnr_cspr_reg_mcysclga_1, mcysClga1, spr_cspr_mid_y->gain1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcysClga.MCYSCLGA1, union io_cnr_cspr_reg_mcysclga_1, mcysClga2, spr_cspr_mid_y->gain2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcysClga.MCYSCLGA1, union io_cnr_cspr_reg_mcysclga_1, MCYSCLGA_3, spr_cspr_mid_y->gain3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcysClga.MCYSCLGA2, union io_cnr_cspr_reg_mcysclga_2, MCYSCLGA_4, spr_cspr_mid_y->gain4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcysClga.MCYSCLGA2, union io_cnr_cspr_reg_mcysclga_2, MCYSCLGA_5, spr_cspr_mid_y->gain5 );

	im_cnr_off_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	return D_DDIM_OK;
}

/*
Set SPR CbCr table for Middle frequency CbCr
*/
INT32 im_cnr_cspr_ofl_set_cspr_mid_cc_y_table(ImCnrCspr*self, UCHAR ch, const TImCnrTable* const spr_cspr_mid_c )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_cspr_ofl_set_cspr_mid_cc_y_table() error. input channel error : %d\n", ch));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_cspr_mid_c == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_cspr_ofl_set_cspr_mid_cc_y_table() Parameter is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnr_on_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mccsClbd.MCCSCLBD1.bit.mccsClbd1	= spr_cspr_mid_c->bd1;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mccsClbd.MCCSCLBD1.bit.mccsClbd2	= spr_cspr_mid_c->bd2;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mccsClbd.MCCSCLBD1.bit.MCCSCLBD_3	= spr_cspr_mid_c->bd3;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mccsClbd.MCCSCLBD1.bit.MCCSCLBD_4	= spr_cspr_mid_c->bd4;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mccsClbd.MCCSCLBD2.bit.MCCSCLBD_5	= spr_cspr_mid_c->bd5;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mccsClof.MCCSCLOF1.bit.MCCSCLOF_0	= spr_cspr_mid_c->of0;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mccsClof.MCCSCLOF1.bit.mccsClof1	= spr_cspr_mid_c->of1;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mccsClof.MCCSCLOF1.bit.mccsClof2	= spr_cspr_mid_c->of2;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mccsClof.MCCSCLOF1.bit.MCCSCLOF_3	= spr_cspr_mid_c->of3;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mccsClof.MCCSCLOF2.bit.MCCSCLOF_4	= spr_cspr_mid_c->of4;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mccsClof.MCCSCLOF2.bit.MCCSCLOF_5	= spr_cspr_mid_c->of5;

	// write signed data
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mccsClga.MCCSCLGA1, union io_cnr_cspr_reg_mccsclga_1, MCCSCLGA_0, spr_cspr_mid_c->gain0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mccsClga.MCCSCLGA1, union io_cnr_cspr_reg_mccsclga_1, mccsClga1, spr_cspr_mid_c->gain1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mccsClga.MCCSCLGA1, union io_cnr_cspr_reg_mccsclga_1, mccsClga2, spr_cspr_mid_c->gain2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mccsClga.MCCSCLGA1, union io_cnr_cspr_reg_mccsclga_1, MCCSCLGA_3, spr_cspr_mid_c->gain3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mccsClga.MCCSCLGA2, union io_cnr_cspr_reg_mccsclga_2, MCCSCLGA_4, spr_cspr_mid_c->gain4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mccsClga.MCCSCLGA2, union io_cnr_cspr_reg_mccsclga_2, MCCSCLGA_5, spr_cspr_mid_c->gain5 );

	im_cnr_off_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	return D_DDIM_OK;
}

/*
Set SPR CbCr table for Middle frequency CbCr
*/
INT32 im_cnr_cspr_otf_set_cspr_mid_cc_y_table(ImCnrCspr*self, UCHAR ch, const TImCnrTable* const spr_cspr_mid_c )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_cspr_otf_set_cspr_mid_cc_y_table() error. input channel error : %d\n", ch));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_cspr_mid_c == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_cspr_otf_set_cspr_mid_cc_y_table() Parameter is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnr_on_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mccsClbd.MCCSCLBD1.bit.mccsClbd1	= spr_cspr_mid_c->bd1;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mccsClbd.MCCSCLBD1.bit.mccsClbd2	= spr_cspr_mid_c->bd2;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mccsClbd.MCCSCLBD1.bit.MCCSCLBD_3	= spr_cspr_mid_c->bd3;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mccsClbd.MCCSCLBD1.bit.MCCSCLBD_4	= spr_cspr_mid_c->bd4;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mccsClbd.MCCSCLBD2.bit.MCCSCLBD_5	= spr_cspr_mid_c->bd5;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mccsClof.MCCSCLOF1.bit.MCCSCLOF_0	= spr_cspr_mid_c->of0;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mccsClof.MCCSCLOF1.bit.mccsClof1	= spr_cspr_mid_c->of1;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mccsClof.MCCSCLOF1.bit.mccsClof2	= spr_cspr_mid_c->of2;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mccsClof.MCCSCLOF1.bit.MCCSCLOF_3	= spr_cspr_mid_c->of3;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mccsClof.MCCSCLOF2.bit.MCCSCLOF_4	= spr_cspr_mid_c->of4;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mccsClof.MCCSCLOF2.bit.MCCSCLOF_5	= spr_cspr_mid_c->of5;

	// write signed data
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mccsClga.MCCSCLGA1, union io_cnr_cspr_reg_mccsclga_1, MCCSCLGA_0, spr_cspr_mid_c->gain0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mccsClga.MCCSCLGA1, union io_cnr_cspr_reg_mccsclga_1, mccsClga1, spr_cspr_mid_c->gain1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mccsClga.MCCSCLGA1, union io_cnr_cspr_reg_mccsclga_1, mccsClga2, spr_cspr_mid_c->gain2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mccsClga.MCCSCLGA1, union io_cnr_cspr_reg_mccsclga_1, MCCSCLGA_3, spr_cspr_mid_c->gain3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mccsClga.MCCSCLGA2, union io_cnr_cspr_reg_mccsclga_2, MCCSCLGA_4, spr_cspr_mid_c->gain4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mccsClga.MCCSCLGA2, union io_cnr_cspr_reg_mccsclga_2, MCCSCLGA_5, spr_cspr_mid_c->gain5 );

	im_cnr_off_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	return D_DDIM_OK;
}

/*
Set SPR CbCr table for Middle frequency CbCr
*/
INT32 im_cnr_cspr_ofl_set_cspr_mid_cc_c_table(ImCnrCspr*self, UCHAR ch, const TImCnrTable* const spr_cspr_mid_c )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_cspr_ofl_set_cspr_mid_cc_c_table() error. input channel error : %d\n", ch));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_cspr_mid_c == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_cspr_ofl_set_cspr_mid_cc_c_table() Parameter is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnr_on_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcssClbd.MCSSCLBD1.bit.mcssClbd1	= spr_cspr_mid_c->bd1;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcssClbd.MCSSCLBD1.bit.mcssClbd2	= spr_cspr_mid_c->bd2;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcssClbd.MCSSCLBD1.bit.MCSSCLBD_3	= spr_cspr_mid_c->bd3;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcssClbd.MCSSCLBD1.bit.MCSSCLBD_4	= spr_cspr_mid_c->bd4;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcssClbd.MCSSCLBD2.bit.MCSSCLBD_5	= spr_cspr_mid_c->bd5;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcssClof.MCSSCLOF1.bit.MCSSCLOF_0	= spr_cspr_mid_c->of0;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcssClof.MCSSCLOF1.bit.mcssClof1	= spr_cspr_mid_c->of1;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcssClof.MCSSCLOF1.bit.mcssClof2	= spr_cspr_mid_c->of2;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcssClof.MCSSCLOF1.bit.MCSSCLOF_3	= spr_cspr_mid_c->of3;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcssClof.MCSSCLOF2.bit.MCSSCLOF_4	= spr_cspr_mid_c->of4;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcssClof.MCSSCLOF2.bit.MCSSCLOF_5	= spr_cspr_mid_c->of5;

	// write signed data
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcssClga.MCSSCLGA1, union io_cnr_cspr_reg_mcssclga_1, MCSSCLGA_0, spr_cspr_mid_c->gain0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcssClga.MCSSCLGA1, union io_cnr_cspr_reg_mcssclga_1, mcssClga1, spr_cspr_mid_c->gain1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcssClga.MCSSCLGA1, union io_cnr_cspr_reg_mcssclga_1, mcssClga2, spr_cspr_mid_c->gain2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcssClga.MCSSCLGA1, union io_cnr_cspr_reg_mcssclga_1, MCSSCLGA_3, spr_cspr_mid_c->gain3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcssClga.MCSSCLGA2, union io_cnr_cspr_reg_mcssclga_2, MCSSCLGA_4, spr_cspr_mid_c->gain4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.mcssClga.MCSSCLGA2, union io_cnr_cspr_reg_mcssclga_2, MCSSCLGA_5, spr_cspr_mid_c->gain5 );

	im_cnr_off_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	return D_DDIM_OK;
}

/*
Set SPR CbCr table for Middle frequency CbCr
*/
INT32 im_cnr_cspr_otf_set_cspr_mid_cc_c_table(ImCnrCspr*self, UCHAR ch, const TImCnrTable* const spr_cspr_mid_c )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_cspr_otf_set_cspr_mid_cc_c_table() error. input channel error : %d\n", ch));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_cspr_mid_c == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_cspr_otf_set_cspr_mid_cc_c_table() Parameter is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnr_on_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcssClbd.MCSSCLBD1.bit.mcssClbd1	= spr_cspr_mid_c->bd1;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcssClbd.MCSSCLBD1.bit.mcssClbd2	= spr_cspr_mid_c->bd2;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcssClbd.MCSSCLBD1.bit.MCSSCLBD_3	= spr_cspr_mid_c->bd3;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcssClbd.MCSSCLBD1.bit.MCSSCLBD_4	= spr_cspr_mid_c->bd4;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcssClbd.MCSSCLBD2.bit.MCSSCLBD_5	= spr_cspr_mid_c->bd5;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcssClof.MCSSCLOF1.bit.MCSSCLOF_0	= spr_cspr_mid_c->of0;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcssClof.MCSSCLOF1.bit.mcssClof1	= spr_cspr_mid_c->of1;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcssClof.MCSSCLOF1.bit.mcssClof2	= spr_cspr_mid_c->of2;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcssClof.MCSSCLOF1.bit.MCSSCLOF_3	= spr_cspr_mid_c->of3;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcssClof.MCSSCLOF2.bit.MCSSCLOF_4	= spr_cspr_mid_c->of4;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcssClof.MCSSCLOF2.bit.MCSSCLOF_5	= spr_cspr_mid_c->of5;

	// write signed data
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcssClga.MCSSCLGA1, union io_cnr_cspr_reg_mcssclga_1, MCSSCLGA_0, spr_cspr_mid_c->gain0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcssClga.MCSSCLGA1, union io_cnr_cspr_reg_mcssclga_1, mcssClga1, spr_cspr_mid_c->gain1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcssClga.MCSSCLGA1, union io_cnr_cspr_reg_mcssclga_1, mcssClga2, spr_cspr_mid_c->gain2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcssClga.MCSSCLGA1, union io_cnr_cspr_reg_mcssclga_1, MCSSCLGA_3, spr_cspr_mid_c->gain3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcssClga.MCSSCLGA2, union io_cnr_cspr_reg_mcssclga_2, MCSSCLGA_4, spr_cspr_mid_c->gain4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.mcssClga.MCSSCLGA2, union io_cnr_cspr_reg_mcssclga_2, MCSSCLGA_5, spr_cspr_mid_c->gain5 );

	im_cnr_off_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	return D_DDIM_OK;
}

/*
Set SPR Y table for Low frequency CbCr
*/
INT32 im_cnr_cspr_ofl_set_cspr_low_y_table(ImCnrCspr*self, UCHAR ch, const TImCnrTable* const spr_cspr_low_y )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_cspr_ofl_set_cspr_low_y_table() error. input channel error : %d\n", ch));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_cspr_low_y == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_cspr_ofl_set_cspr_low_y_table() Parameter is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnr_on_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcysClbd.LCYSCLBD1.bit.lcysClbd1	= spr_cspr_low_y->bd1;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcysClbd.LCYSCLBD1.bit.lcysClbd2	= spr_cspr_low_y->bd2;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcysClbd.LCYSCLBD1.bit.LCYSCLBD_3	= spr_cspr_low_y->bd3;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcysClbd.LCYSCLBD1.bit.LCYSCLBD_4	= spr_cspr_low_y->bd4;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcysClbd.LCYSCLBD2.bit.LCYSCLBD_5	= spr_cspr_low_y->bd5;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcysClof.LCYSCLOF1.bit.LCYSCLOF_0	= spr_cspr_low_y->of0;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcysClof.LCYSCLOF1.bit.lcysClof1	= spr_cspr_low_y->of1;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcysClof.LCYSCLOF1.bit.lcysClof2	= spr_cspr_low_y->of2;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcysClof.LCYSCLOF1.bit.LCYSCLOF_3	= spr_cspr_low_y->of3;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcysClof.LCYSCLOF2.bit.LCYSCLOF_4	= spr_cspr_low_y->of4;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcysClof.LCYSCLOF2.bit.LCYSCLOF_5	= spr_cspr_low_y->of5;

	// write signed data
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcysClga.LCYSCLGA1, union io_cnr_cspr_reg_lcysclga_1, LCYSCLGA_0, spr_cspr_low_y->gain0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcysClga.LCYSCLGA1, union io_cnr_cspr_reg_lcysclga_1, lcysClga1, spr_cspr_low_y->gain1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcysClga.LCYSCLGA1, union io_cnr_cspr_reg_lcysclga_1, lcysClga2, spr_cspr_low_y->gain2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcysClga.LCYSCLGA1, union io_cnr_cspr_reg_lcysclga_1, LCYSCLGA_3, spr_cspr_low_y->gain3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcysClga.LCYSCLGA2, union io_cnr_cspr_reg_lcysclga_2, LCYSCLGA_4, spr_cspr_low_y->gain4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcysClga.LCYSCLGA2, union io_cnr_cspr_reg_lcysclga_2, LCYSCLGA_5, spr_cspr_low_y->gain5 );

	im_cnr_off_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	return D_DDIM_OK;
}

/*
Set SPR Y table for Low frequency CbCr
*/
INT32 im_cnr_cspr_otf_set_cspr_low_y_table(ImCnrCspr*self, UCHAR ch, const TImCnrTable* const spr_cspr_low_y )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_cspr_otf_set_cspr_low_y_table() error. input channel error : %d\n", ch));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_cspr_low_y == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_cspr_otf_set_cspr_low_y_table() Parameter is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnr_on_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcysClbd.LCYSCLBD1.bit.lcysClbd1	= spr_cspr_low_y->bd1;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcysClbd.LCYSCLBD1.bit.lcysClbd2	= spr_cspr_low_y->bd2;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcysClbd.LCYSCLBD1.bit.LCYSCLBD_3	= spr_cspr_low_y->bd3;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcysClbd.LCYSCLBD1.bit.LCYSCLBD_4	= spr_cspr_low_y->bd4;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcysClbd.LCYSCLBD2.bit.LCYSCLBD_5	= spr_cspr_low_y->bd5;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcysClof.LCYSCLOF1.bit.LCYSCLOF_0	= spr_cspr_low_y->of0;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcysClof.LCYSCLOF1.bit.lcysClof1	= spr_cspr_low_y->of1;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcysClof.LCYSCLOF1.bit.lcysClof2	= spr_cspr_low_y->of2;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcysClof.LCYSCLOF1.bit.LCYSCLOF_3	= spr_cspr_low_y->of3;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcysClof.LCYSCLOF2.bit.LCYSCLOF_4	= spr_cspr_low_y->of4;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcysClof.LCYSCLOF2.bit.LCYSCLOF_5	= spr_cspr_low_y->of5;

	// write signed data
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcysClga.LCYSCLGA1, union io_cnr_cspr_reg_lcysclga_1, LCYSCLGA_0, spr_cspr_low_y->gain0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcysClga.LCYSCLGA1, union io_cnr_cspr_reg_lcysclga_1, lcysClga1, spr_cspr_low_y->gain1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcysClga.LCYSCLGA1, union io_cnr_cspr_reg_lcysclga_1, lcysClga2, spr_cspr_low_y->gain2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcysClga.LCYSCLGA1, union io_cnr_cspr_reg_lcysclga_1, LCYSCLGA_3, spr_cspr_low_y->gain3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcysClga.LCYSCLGA2, union io_cnr_cspr_reg_lcysclga_2, LCYSCLGA_4, spr_cspr_low_y->gain4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcysClga.LCYSCLGA2, union io_cnr_cspr_reg_lcysclga_2, LCYSCLGA_5, spr_cspr_low_y->gain5 );

	im_cnr_off_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	return D_DDIM_OK;
}

/*
Set SPR CbCr table for Low frequency CbCr
*/
INT32 im_cnr_cspr_ofl_set_cspr_low_cc_y_table(ImCnrCspr*self, UCHAR ch, const TImCnrTable* const spr_cspr_low_c )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_cspr_ofl_set_cspr_low_cc_y_table() error. input channel error : %d\n", ch));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_cspr_low_c == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_cspr_ofl_set_cspr_low_cc_y_table() Parameter is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnr_on_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lccsClbd.LCCSCLBD1.bit.lccsClbd1	= spr_cspr_low_c->bd1;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lccsClbd.LCCSCLBD1.bit.lccsClbd2	= spr_cspr_low_c->bd2;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lccsClbd.LCCSCLBD1.bit.LCCSCLBD_3	= spr_cspr_low_c->bd3;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lccsClbd.LCCSCLBD1.bit.LCCSCLBD_4	= spr_cspr_low_c->bd4;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lccsClbd.LCCSCLBD2.bit.LCCSCLBD_5	= spr_cspr_low_c->bd5;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lccsClof.LCCSCLOF1.bit.LCCSCLOF_0	= spr_cspr_low_c->of0;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lccsClof.LCCSCLOF1.bit.lccsClof1	= spr_cspr_low_c->of1;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lccsClof.LCCSCLOF1.bit.lccsClof2	= spr_cspr_low_c->of2;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lccsClof.LCCSCLOF1.bit.LCCSCLOF_3	= spr_cspr_low_c->of3;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lccsClof.LCCSCLOF2.bit.LCCSCLOF_4	= spr_cspr_low_c->of4;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lccsClof.LCCSCLOF2.bit.LCCSCLOF_5	= spr_cspr_low_c->of5;

	// write signed data
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lccsClga.LCCSCLGA1, union io_cnr_cspr_reg_lccsclga_1, LCCSCLGA_0, spr_cspr_low_c->gain0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lccsClga.LCCSCLGA1, union io_cnr_cspr_reg_lccsclga_1, lccsClga1, spr_cspr_low_c->gain1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lccsClga.LCCSCLGA1, union io_cnr_cspr_reg_lccsclga_1, lccsClga2, spr_cspr_low_c->gain2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lccsClga.LCCSCLGA1, union io_cnr_cspr_reg_lccsclga_1, LCCSCLGA_3, spr_cspr_low_c->gain3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lccsClga.LCCSCLGA2, union io_cnr_cspr_reg_lccsclga_2, LCCSCLGA_4, spr_cspr_low_c->gain4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lccsClga.LCCSCLGA2, union io_cnr_cspr_reg_lccsclga_2, LCCSCLGA_5, spr_cspr_low_c->gain5 );

	im_cnr_off_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	return D_DDIM_OK;
}

/*
Set SPR CbCr table for Low frequency CbCr
*/
INT32 im_cnr_cspr_otf_set_cspr_low_cc_y_table(ImCnrCspr*self, UCHAR ch, const TImCnrTable* const spr_cspr_low_c )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_cspr_otf_set_cspr_low_cc_y_table() error. input channel error : %d\n", ch));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_cspr_low_c == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_cspr_otf_set_cspr_low_cc_y_table() Parameter is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnr_on_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lccsClbd.LCCSCLBD1.bit.lccsClbd1	= spr_cspr_low_c->bd1;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lccsClbd.LCCSCLBD1.bit.lccsClbd2	= spr_cspr_low_c->bd2;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lccsClbd.LCCSCLBD1.bit.LCCSCLBD_3	= spr_cspr_low_c->bd3;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lccsClbd.LCCSCLBD1.bit.LCCSCLBD_4	= spr_cspr_low_c->bd4;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lccsClbd.LCCSCLBD2.bit.LCCSCLBD_5	= spr_cspr_low_c->bd5;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lccsClof.LCCSCLOF1.bit.LCCSCLOF_0	= spr_cspr_low_c->of0;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lccsClof.LCCSCLOF1.bit.lccsClof1	= spr_cspr_low_c->of1;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lccsClof.LCCSCLOF1.bit.lccsClof2	= spr_cspr_low_c->of2;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lccsClof.LCCSCLOF1.bit.LCCSCLOF_3	= spr_cspr_low_c->of3;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lccsClof.LCCSCLOF2.bit.LCCSCLOF_4	= spr_cspr_low_c->of4;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lccsClof.LCCSCLOF2.bit.LCCSCLOF_5	= spr_cspr_low_c->of5;

	// write signed data
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lccsClga.LCCSCLGA1, union io_cnr_cspr_reg_lccsclga_1, LCCSCLGA_0, spr_cspr_low_c->gain0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lccsClga.LCCSCLGA1, union io_cnr_cspr_reg_lccsclga_1, lccsClga1, spr_cspr_low_c->gain1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lccsClga.LCCSCLGA1, union io_cnr_cspr_reg_lccsclga_1, lccsClga2, spr_cspr_low_c->gain2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lccsClga.LCCSCLGA1, union io_cnr_cspr_reg_lccsclga_1, LCCSCLGA_3, spr_cspr_low_c->gain3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lccsClga.LCCSCLGA2, union io_cnr_cspr_reg_lccsclga_2, LCCSCLGA_4, spr_cspr_low_c->gain4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lccsClga.LCCSCLGA2, union io_cnr_cspr_reg_lccsclga_2, LCCSCLGA_5, spr_cspr_low_c->gain5 );

	im_cnr_off_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	return D_DDIM_OK;
}

/*
Set SPR CbCr table for Low frequency CbCr
*/
INT32 im_cnr_cspr_ofl_set_cspr_low_cc_c_table(ImCnrCspr*self, UCHAR ch, const TImCnrTable* const spr_cspr_low_c )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_cspr_ofl_set_cspr_low_cc_c_table() error. input channel error : %d\n", ch));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_cspr_low_c == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_cspr_ofl_set_cspr_low_cc_c_table() Parameter is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnr_on_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcssClbd.LCSSCLBD1.bit.lcssClbd1	= spr_cspr_low_c->bd1;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcssClbd.LCSSCLBD1.bit.lcssClbd2	= spr_cspr_low_c->bd2;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcssClbd.LCSSCLBD1.bit.LCSSCLBD_3	= spr_cspr_low_c->bd3;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcssClbd.LCSSCLBD1.bit.LCSSCLBD_4	= spr_cspr_low_c->bd4;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcssClbd.LCSSCLBD2.bit.LCSSCLBD_5	= spr_cspr_low_c->bd5;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcssClof.LCSSCLOF1.bit.LCSSCLOF_0	= spr_cspr_low_c->of0;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcssClof.LCSSCLOF1.bit.lcssClof1	= spr_cspr_low_c->of1;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcssClof.LCSSCLOF1.bit.lcssClof2	= spr_cspr_low_c->of2;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcssClof.LCSSCLOF1.bit.LCSSCLOF_3	= spr_cspr_low_c->of3;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcssClof.LCSSCLOF2.bit.LCSSCLOF_4	= spr_cspr_low_c->of4;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcssClof.LCSSCLOF2.bit.LCSSCLOF_5	= spr_cspr_low_c->of5;

	// write signed data
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcssClga.LCSSCLGA1, union io_cnr_cspr_reg_lcssclga_1, LCSSCLGA_0, spr_cspr_low_c->gain0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcssClga.LCSSCLGA1, union io_cnr_cspr_reg_lcssclga_1, lcssClga1, spr_cspr_low_c->gain1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcssClga.LCSSCLGA1, union io_cnr_cspr_reg_lcssclga_1, lcssClga2, spr_cspr_low_c->gain2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcssClga.LCSSCLGA1, union io_cnr_cspr_reg_lcssclga_1, LCSSCLGA_3, spr_cspr_low_c->gain3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcssClga.LCSSCLGA2, union io_cnr_cspr_reg_lcssclga_2, LCSSCLGA_4, spr_cspr_low_c->gain4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.lcssClga.LCSSCLGA2, union io_cnr_cspr_reg_lcssclga_2, LCSSCLGA_5, spr_cspr_low_c->gain5 );

	im_cnr_off_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	return D_DDIM_OK;
}

/*
Set SPR CbCr table for Low frequency CbCr
*/
INT32 im_cnr_cspr_otf_set_cspr_low_cc_c_table(ImCnrCspr*self, UCHAR ch, const TImCnrTable* const spr_cspr_low_c )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_cspr_otf_set_cspr_low_cc_c_table() error. input channel error : %d\n", ch));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_cspr_low_c == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_cspr_otf_set_cspr_low_cc_c_table() Parameter is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnr_on_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcssClbd.LCSSCLBD1.bit.lcssClbd1	= spr_cspr_low_c->bd1;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcssClbd.LCSSCLBD1.bit.lcssClbd2	= spr_cspr_low_c->bd2;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcssClbd.LCSSCLBD1.bit.LCSSCLBD_3	= spr_cspr_low_c->bd3;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcssClbd.LCSSCLBD1.bit.LCSSCLBD_4	= spr_cspr_low_c->bd4;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcssClbd.LCSSCLBD2.bit.LCSSCLBD_5	= spr_cspr_low_c->bd5;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcssClof.LCSSCLOF1.bit.LCSSCLOF_0	= spr_cspr_low_c->of0;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcssClof.LCSSCLOF1.bit.lcssClof1	= spr_cspr_low_c->of1;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcssClof.LCSSCLOF1.bit.lcssClof2	= spr_cspr_low_c->of2;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcssClof.LCSSCLOF1.bit.LCSSCLOF_3	= spr_cspr_low_c->of3;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcssClof.LCSSCLOF2.bit.LCSSCLOF_4	= spr_cspr_low_c->of4;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcssClof.LCSSCLOF2.bit.LCSSCLOF_5	= spr_cspr_low_c->of5;

	// write signed data
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcssClga.LCSSCLGA1, union io_cnr_cspr_reg_lcssclga_1, LCSSCLGA_0, spr_cspr_low_c->gain0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcssClga.LCSSCLGA1, union io_cnr_cspr_reg_lcssclga_1, lcssClga1, spr_cspr_low_c->gain1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcssClga.LCSSCLGA1, union io_cnr_cspr_reg_lcssclga_1, lcssClga2, spr_cspr_low_c->gain2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcssClga.LCSSCLGA1, union io_cnr_cspr_reg_lcssclga_1, LCSSCLGA_3, spr_cspr_low_c->gain3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcssClga.LCSSCLGA2, union io_cnr_cspr_reg_lcssclga_2, LCSSCLGA_4, spr_cspr_low_c->gain4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.lcssClga.LCSSCLGA2, union io_cnr_cspr_reg_lcssclga_2, LCSSCLGA_5, spr_cspr_low_c->gain5 );

	im_cnr_off_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	return D_DDIM_OK;
}

/*
Set SPR Edge for CbcCr for Off Line
*/
INT32 im_cnr_cspr_ofl_set_cspr_edge_table(ImCnrCspr*self, UCHAR ch, const TImCnrTable* const spr_cspr_edge )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_cspr_ofl_set_cspr_edge_table() error. input channel error : %d\n", ch));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_cspr_edge == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_cspr_ofl_set_cspr_edge_table() Parameter is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnr_on_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cesClbd.CESCLBD1.bit.cesClbd1	= spr_cspr_edge->bd1;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cesClbd.CESCLBD1.bit.cesClbd2	= spr_cspr_edge->bd2;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cesClbd.CESCLBD1.bit.CESCLBD_3	= spr_cspr_edge->bd3;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cesClbd.CESCLBD1.bit.CESCLBD_4	= spr_cspr_edge->bd4;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cesClbd.CESCLBD2.bit.CESCLBD_5	= spr_cspr_edge->bd5;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cesClof.CESCLOF1.bit.CESCLOF_0	= spr_cspr_edge->of0;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cesClof.CESCLOF1.bit.cesClof1	= spr_cspr_edge->of1;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cesClof.CESCLOF1.bit.cesClof2	= spr_cspr_edge->of2;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cesClof.CESCLOF1.bit.CESCLOF_3	= spr_cspr_edge->of3;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cesClof.CESCLOF2.bit.CESCLOF_4	= spr_cspr_edge->of4;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cesClof.CESCLOF2.bit.CESCLOF_5	= spr_cspr_edge->of5;

	// write signed data
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cesClga.CESCLGA1, union io_cnr_cspr_reg_cesclga_1, CESCLGA_0, spr_cspr_edge->gain0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cesClga.CESCLGA1, union io_cnr_cspr_reg_cesclga_1, cesClga1, spr_cspr_edge->gain1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cesClga.CESCLGA1, union io_cnr_cspr_reg_cesclga_1, cesClga2, spr_cspr_edge->gain2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cesClga.CESCLGA1, union io_cnr_cspr_reg_cesclga_1, CESCLGA_3, spr_cspr_edge->gain3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cesClga.CESCLGA2, union io_cnr_cspr_reg_cesclga_2, CESCLGA_4, spr_cspr_edge->gain4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cesClga.CESCLGA2, union io_cnr_cspr_reg_cesclga_2, CESCLGA_5, spr_cspr_edge->gain5 );

	im_cnr_off_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	return D_DDIM_OK;
}

/*
Set SPR Edge for CbcCr for Off Line
*/
INT32 im_cnr_cspr_otf_set_cspr_edge_table(ImCnrCspr*self, UCHAR ch, const TImCnrTable* const spr_cspr_edge )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_cspr_otf_set_cspr_edge_table() error. input channel error : %d\n", ch));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_cspr_edge == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_cspr_otf_set_cspr_edge_table() Parameter is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnr_on_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cesClbd.CESCLBD1.bit.cesClbd1	= spr_cspr_edge->bd1;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cesClbd.CESCLBD1.bit.cesClbd2	= spr_cspr_edge->bd2;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cesClbd.CESCLBD1.bit.CESCLBD_3	= spr_cspr_edge->bd3;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cesClbd.CESCLBD1.bit.CESCLBD_4	= spr_cspr_edge->bd4;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cesClbd.CESCLBD2.bit.CESCLBD_5	= spr_cspr_edge->bd5;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cesClof.CESCLOF1.bit.CESCLOF_0	= spr_cspr_edge->of0;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cesClof.CESCLOF1.bit.cesClof1	= spr_cspr_edge->of1;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cesClof.CESCLOF1.bit.cesClof2	= spr_cspr_edge->of2;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cesClof.CESCLOF1.bit.CESCLOF_3	= spr_cspr_edge->of3;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cesClof.CESCLOF2.bit.CESCLOF_4	= spr_cspr_edge->of4;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cesClof.CESCLOF2.bit.CESCLOF_5	= spr_cspr_edge->of5;

	// write signed data
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cesClga.CESCLGA1, union io_cnr_cspr_reg_cesclga_1, CESCLGA_0, spr_cspr_edge->gain0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cesClga.CESCLGA1, union io_cnr_cspr_reg_cesclga_1, cesClga1, spr_cspr_edge->gain1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cesClga.CESCLGA1, union io_cnr_cspr_reg_cesclga_1, cesClga2, spr_cspr_edge->gain2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cesClga.CESCLGA1, union io_cnr_cspr_reg_cesclga_1, CESCLGA_3, spr_cspr_edge->gain3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cesClga.CESCLGA2, union io_cnr_cspr_reg_cesclga_2, CESCLGA_4, spr_cspr_edge->gain4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cesClga.CESCLGA2, union io_cnr_cspr_reg_cesclga_2, CESCLGA_5, spr_cspr_edge->gain5 );

	im_cnr_off_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	return D_DDIM_OK;
}

/*
Set SPR Hue specified for CbcCr for Off Line
*/
INT32 im_cnr_cspr_ofl_set_cspr_hue_specified_table(ImCnrCspr*self, UCHAR ch, const TImCnrHueSpecTable* const spr_cspr_hue )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_cspr_ofl_set_cspr_hue_specified_table() error. input channel error : %d\n", ch));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_cspr_hue == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_cspr_ofl_set_cspr_hue_specified_table() Parameter is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnr_on_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	// write signed data
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cphpt, union io_cnr_cspr_reg_cphpt, CDCB, spr_cspr_hue->cdCb );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cphpt, union io_cnr_cspr_reg_cphpt, CDCR, spr_cspr_hue->cdCr );

	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cphptk.bit.KCB	= spr_cspr_hue->kCb;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cphptk.bit.KCR	= spr_cspr_hue->kCr;

	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cdsClbd.CDSCLBD1.bit.cdsClbd1	= spr_cspr_hue->bd1;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cdsClbd.CDSCLBD1.bit.cdsClbd2	= spr_cspr_hue->bd2;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cdsClbd.CDSCLBD2.bit.cdsClbd3	= spr_cspr_hue->bd3;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cdsClbd.CDSCLBD2.bit.CDSCLBD_4	= spr_cspr_hue->bd4;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cdsClbd.CDSCLBD3.bit.CDSCLBD_5	= spr_cspr_hue->bd5;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cdsClof.CDSCLOF1.bit.CDSCLOF_0	= spr_cspr_hue->of0;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cdsClof.CDSCLOF1.bit.cdsClof1	= spr_cspr_hue->of1;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cdsClof.CDSCLOF2.bit.cdsClof2	= spr_cspr_hue->of2;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cdsClof.CDSCLOF2.bit.cdsClof3	= spr_cspr_hue->of3;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cdsClof.CDSCLOF3.bit.CDSCLOF_4	= spr_cspr_hue->of4;
	ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cdsClof.CDSCLOF3.bit.CDSCLOF_5	= spr_cspr_hue->of5;

	// write signed data
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cdsClga.CDSCLGA1, union io_cnr_cspr_reg_cdsclga_1, CDSCLGA_0, spr_cspr_hue->gain0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cdsClga.CDSCLGA1, union io_cnr_cspr_reg_cdsclga_1, cdsClga1, spr_cspr_hue->gain1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cdsClga.CDSCLGA2, union io_cnr_cspr_reg_cdsclga_2, cdsClga2, spr_cspr_hue->gain2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cdsClga.CDSCLGA2, union io_cnr_cspr_reg_cdsclga_2, cdsClga3, spr_cspr_hue->gain3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cdsClga.CDSCLGA3, union io_cnr_cspr_reg_cdsclga_3, CDSCLGA_4, spr_cspr_hue->gain4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OFL_CSPR_REG.cdsClga.CDSCLGA3, union io_cnr_cspr_reg_cdsclga_3, CDSCLGA_5, spr_cspr_hue->gain5 );

	im_cnr_off_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	return D_DDIM_OK;
}

/*
Set SPR Hue specified for CbcCr for Off Line
*/
INT32 im_cnr_cspr_otf_set_cspr_hue_specified_table(ImCnrCspr*self, UCHAR ch, const TImCnrHueSpecTable* const spr_cspr_hue )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_cspr_otf_set_cspr_hue_specified_table() error. input channel error : %d\n", ch));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_cspr_hue == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_cspr_otf_set_cspr_hue_specified_table() Parameter is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnr_on_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	// write signed data
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cphpt, union io_cnr_cspr_reg_cphpt, CDCB, spr_cspr_hue->cdCb );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cphpt, union io_cnr_cspr_reg_cphpt, CDCR, spr_cspr_hue->cdCr );

	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cphptk.bit.KCB	= spr_cspr_hue->kCb;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cphptk.bit.KCR	= spr_cspr_hue->kCr;

	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cdsClbd.CDSCLBD1.bit.cdsClbd1	= spr_cspr_hue->bd1;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cdsClbd.CDSCLBD1.bit.cdsClbd2	= spr_cspr_hue->bd2;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cdsClbd.CDSCLBD2.bit.cdsClbd3	= spr_cspr_hue->bd3;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cdsClbd.CDSCLBD2.bit.CDSCLBD_4	= spr_cspr_hue->bd4;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cdsClbd.CDSCLBD3.bit.CDSCLBD_5	= spr_cspr_hue->bd5;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cdsClof.CDSCLOF1.bit.CDSCLOF_0	= spr_cspr_hue->of0;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cdsClof.CDSCLOF1.bit.cdsClof1	= spr_cspr_hue->of1;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cdsClof.CDSCLOF2.bit.cdsClof2	= spr_cspr_hue->of2;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cdsClof.CDSCLOF2.bit.cdsClof3	= spr_cspr_hue->of3;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cdsClof.CDSCLOF3.bit.CDSCLOF_4	= spr_cspr_hue->of4;
	ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cdsClof.CDSCLOF3.bit.CDSCLOF_5	= spr_cspr_hue->of5;

	// write signed data
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cdsClga.CDSCLGA1, union io_cnr_cspr_reg_cdsclga_1, CDSCLGA_0, spr_cspr_hue->gain0 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cdsClga.CDSCLGA1, union io_cnr_cspr_reg_cdsclga_1, cdsClga1, spr_cspr_hue->gain1 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cdsClga.CDSCLGA2, union io_cnr_cspr_reg_cdsclga_2, cdsClga2, spr_cspr_hue->gain2 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cdsClga.CDSCLGA2, union io_cnr_cspr_reg_cdsclga_2, cdsClga3, spr_cspr_hue->gain3 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cdsClga.CDSCLGA3, union io_cnr_cspr_reg_cdsclga_3, CDSCLGA_4, spr_cspr_hue->gain4 );
	ImCnr_IM_CNR_SET_REG_SIGNED( ImCnr_IO_CNR(ch)->OTF_CSPR_REG.cdsClga.CDSCLGA3, union io_cnr_cspr_reg_cdsclga_3, CDSCLGA_5, spr_cspr_hue->gain5 );

	im_cnr_off_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	return D_DDIM_OK;
}

ImCnrCspr *im_cnr_cspr_new(void)
{
	ImCnrCspr* self = k_object_new_with_private(IM_TYPE_CNR_CSPR,sizeof(ImCnrCsprPrivate));
	return self;
}
