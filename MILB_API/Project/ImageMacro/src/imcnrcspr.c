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
INT32 im_cnr_cspr_ofl_set_yspr_table(ImCnrCspr*self, UCHAR ch, const T_IM_CNR_TABLE* const spr_yspr )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_cspr_ofl_set_yspr_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_yspr == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_cspr_ofl_set_yspr_table() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	Im_CNR_On_Pclk(ch);
	Im_CNR_Dsb();

	IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYBD.YSPRDYEYBD1.bit.YSPRDYEYBD_1	= spr_yspr->bd1;
	IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYBD.YSPRDYEYBD1.bit.YSPRDYEYBD_2	= spr_yspr->bd2;
	IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYBD.YSPRDYEYBD1.bit.YSPRDYEYBD_3	= spr_yspr->bd3;
	IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYBD.YSPRDYEYBD1.bit.YSPRDYEYBD_4	= spr_yspr->bd4;
	IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYBD.YSPRDYEYBD2.bit.YSPRDYEYBD_5	= spr_yspr->bd5;
	IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYOF.YSPRDYEYOF1.bit.YSPRDYEYOF_0	= spr_yspr->of0;
	IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYOF.YSPRDYEYOF1.bit.YSPRDYEYOF_1	= spr_yspr->of1;
	IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYOF.YSPRDYEYOF1.bit.YSPRDYEYOF_2	= spr_yspr->of2;
	IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYOF.YSPRDYEYOF1.bit.YSPRDYEYOF_3	= spr_yspr->of3;
	IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYOF.YSPRDYEYOF2.bit.YSPRDYEYOF_4	= spr_yspr->of4;
	IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYOF.YSPRDYEYOF2.bit.YSPRDYEYOF_5	= spr_yspr->of5;

	// write signed data
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYGA.YSPRDYEYGA1, union io_cnr_ofl_reg_yspr_ysprdyeyga_1, YSPRDYEYGA_0, spr_yspr->gain0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYGA.YSPRDYEYGA1, union io_cnr_ofl_reg_yspr_ysprdyeyga_1, YSPRDYEYGA_1, spr_yspr->gain1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYGA.YSPRDYEYGA1, union io_cnr_ofl_reg_yspr_ysprdyeyga_1, YSPRDYEYGA_2, spr_yspr->gain2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYGA.YSPRDYEYGA1, union io_cnr_ofl_reg_yspr_ysprdyeyga_1, YSPRDYEYGA_3, spr_yspr->gain3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYGA.YSPRDYEYGA2, union io_cnr_ofl_reg_yspr_ysprdyeyga_2, YSPRDYEYGA_4, spr_yspr->gain4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYGA.YSPRDYEYGA2, union io_cnr_ofl_reg_yspr_ysprdyeyga_2, YSPRDYEYGA_5, spr_yspr->gain5 );

	Im_CNR_Off_Pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
Set SPR Y table for Middle frequency CbCr
*/
INT32 im_cnr_cspr_ofl_set_cspr_mid_y_table(ImCnrCspr*self, UCHAR ch, const T_IM_CNR_TABLE* const spr_cspr_mid_y )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_cspr_ofl_set_cspr_mid_y_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_cspr_mid_y == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_cspr_ofl_set_cspr_mid_y_table() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	Im_CNR_On_Pclk(ch);
	Im_CNR_Dsb();

	IO_CNR(ch)->OFL_CSPR_REG.MCYSCLBD.MCYSCLBD1.bit.MCYSCLBD_1	= spr_cspr_mid_y->bd1;
	IO_CNR(ch)->OFL_CSPR_REG.MCYSCLBD.MCYSCLBD1.bit.MCYSCLBD_2	= spr_cspr_mid_y->bd2;
	IO_CNR(ch)->OFL_CSPR_REG.MCYSCLBD.MCYSCLBD1.bit.MCYSCLBD_3	= spr_cspr_mid_y->bd3;
	IO_CNR(ch)->OFL_CSPR_REG.MCYSCLBD.MCYSCLBD1.bit.MCYSCLBD_4	= spr_cspr_mid_y->bd4;
	IO_CNR(ch)->OFL_CSPR_REG.MCYSCLBD.MCYSCLBD2.bit.MCYSCLBD_5	= spr_cspr_mid_y->bd5;
	IO_CNR(ch)->OFL_CSPR_REG.MCYSCLOF.MCYSCLOF1.bit.MCYSCLOF_0	= spr_cspr_mid_y->of0;
	IO_CNR(ch)->OFL_CSPR_REG.MCYSCLOF.MCYSCLOF1.bit.MCYSCLOF_1	= spr_cspr_mid_y->of1;
	IO_CNR(ch)->OFL_CSPR_REG.MCYSCLOF.MCYSCLOF1.bit.MCYSCLOF_2	= spr_cspr_mid_y->of2;
	IO_CNR(ch)->OFL_CSPR_REG.MCYSCLOF.MCYSCLOF1.bit.MCYSCLOF_3	= spr_cspr_mid_y->of3;
	IO_CNR(ch)->OFL_CSPR_REG.MCYSCLOF.MCYSCLOF2.bit.MCYSCLOF_4	= spr_cspr_mid_y->of4;
	IO_CNR(ch)->OFL_CSPR_REG.MCYSCLOF.MCYSCLOF2.bit.MCYSCLOF_5	= spr_cspr_mid_y->of5;

	// write signed data
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.MCYSCLGA.MCYSCLGA1, union io_cnr_cspr_reg_mcysclga_1, MCYSCLGA_0, spr_cspr_mid_y->gain0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.MCYSCLGA.MCYSCLGA1, union io_cnr_cspr_reg_mcysclga_1, MCYSCLGA_1, spr_cspr_mid_y->gain1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.MCYSCLGA.MCYSCLGA1, union io_cnr_cspr_reg_mcysclga_1, MCYSCLGA_2, spr_cspr_mid_y->gain2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.MCYSCLGA.MCYSCLGA1, union io_cnr_cspr_reg_mcysclga_1, MCYSCLGA_3, spr_cspr_mid_y->gain3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.MCYSCLGA.MCYSCLGA2, union io_cnr_cspr_reg_mcysclga_2, MCYSCLGA_4, spr_cspr_mid_y->gain4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.MCYSCLGA.MCYSCLGA2, union io_cnr_cspr_reg_mcysclga_2, MCYSCLGA_5, spr_cspr_mid_y->gain5 );

	Im_CNR_Off_Pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
Set SPR Y table for Middle frequency CbCr
*/
INT32 im_cnr_cspr_otf_set_cspr_mid_y_table(ImCnrCspr*self, UCHAR ch, const T_IM_CNR_TABLE* const spr_cspr_mid_y )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_cspr_otf_set_cspr_mid_y_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_cspr_mid_y == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_cspr_otf_set_cspr_mid_y_table() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	Im_CNR_On_Pclk(ch);
	Im_CNR_Dsb();

	IO_CNR(ch)->OTF_CSPR_REG.MCYSCLBD.MCYSCLBD1.bit.MCYSCLBD_1	= spr_cspr_mid_y->bd1;
	IO_CNR(ch)->OTF_CSPR_REG.MCYSCLBD.MCYSCLBD1.bit.MCYSCLBD_2	= spr_cspr_mid_y->bd2;
	IO_CNR(ch)->OTF_CSPR_REG.MCYSCLBD.MCYSCLBD1.bit.MCYSCLBD_3	= spr_cspr_mid_y->bd3;
	IO_CNR(ch)->OTF_CSPR_REG.MCYSCLBD.MCYSCLBD1.bit.MCYSCLBD_4	= spr_cspr_mid_y->bd4;
	IO_CNR(ch)->OTF_CSPR_REG.MCYSCLBD.MCYSCLBD2.bit.MCYSCLBD_5	= spr_cspr_mid_y->bd5;
	IO_CNR(ch)->OTF_CSPR_REG.MCYSCLOF.MCYSCLOF1.bit.MCYSCLOF_0	= spr_cspr_mid_y->of0;
	IO_CNR(ch)->OTF_CSPR_REG.MCYSCLOF.MCYSCLOF1.bit.MCYSCLOF_1	= spr_cspr_mid_y->of1;
	IO_CNR(ch)->OTF_CSPR_REG.MCYSCLOF.MCYSCLOF1.bit.MCYSCLOF_2	= spr_cspr_mid_y->of2;
	IO_CNR(ch)->OTF_CSPR_REG.MCYSCLOF.MCYSCLOF1.bit.MCYSCLOF_3	= spr_cspr_mid_y->of3;
	IO_CNR(ch)->OTF_CSPR_REG.MCYSCLOF.MCYSCLOF2.bit.MCYSCLOF_4	= spr_cspr_mid_y->of4;
	IO_CNR(ch)->OTF_CSPR_REG.MCYSCLOF.MCYSCLOF2.bit.MCYSCLOF_5	= spr_cspr_mid_y->of5;

	// write signed data
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.MCYSCLGA.MCYSCLGA1, union io_cnr_cspr_reg_mcysclga_1, MCYSCLGA_0, spr_cspr_mid_y->gain0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.MCYSCLGA.MCYSCLGA1, union io_cnr_cspr_reg_mcysclga_1, MCYSCLGA_1, spr_cspr_mid_y->gain1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.MCYSCLGA.MCYSCLGA1, union io_cnr_cspr_reg_mcysclga_1, MCYSCLGA_2, spr_cspr_mid_y->gain2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.MCYSCLGA.MCYSCLGA1, union io_cnr_cspr_reg_mcysclga_1, MCYSCLGA_3, spr_cspr_mid_y->gain3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.MCYSCLGA.MCYSCLGA2, union io_cnr_cspr_reg_mcysclga_2, MCYSCLGA_4, spr_cspr_mid_y->gain4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.MCYSCLGA.MCYSCLGA2, union io_cnr_cspr_reg_mcysclga_2, MCYSCLGA_5, spr_cspr_mid_y->gain5 );

	Im_CNR_Off_Pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
Set SPR CbCr table for Middle frequency CbCr
*/
INT32 im_cnr_cspr_ofl_set_cspr_mid_cc_y_table(ImCnrCspr*self, UCHAR ch, const T_IM_CNR_TABLE* const spr_cspr_mid_c )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_cspr_ofl_set_cspr_mid_cc_y_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_cspr_mid_c == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_cspr_ofl_set_cspr_mid_cc_y_table() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	Im_CNR_On_Pclk(ch);
	Im_CNR_Dsb();

	IO_CNR(ch)->OFL_CSPR_REG.MCCSCLBD.MCCSCLBD1.bit.MCCSCLBD_1	= spr_cspr_mid_c->bd1;
	IO_CNR(ch)->OFL_CSPR_REG.MCCSCLBD.MCCSCLBD1.bit.MCCSCLBD_2	= spr_cspr_mid_c->bd2;
	IO_CNR(ch)->OFL_CSPR_REG.MCCSCLBD.MCCSCLBD1.bit.MCCSCLBD_3	= spr_cspr_mid_c->bd3;
	IO_CNR(ch)->OFL_CSPR_REG.MCCSCLBD.MCCSCLBD1.bit.MCCSCLBD_4	= spr_cspr_mid_c->bd4;
	IO_CNR(ch)->OFL_CSPR_REG.MCCSCLBD.MCCSCLBD2.bit.MCCSCLBD_5	= spr_cspr_mid_c->bd5;
	IO_CNR(ch)->OFL_CSPR_REG.MCCSCLOF.MCCSCLOF1.bit.MCCSCLOF_0	= spr_cspr_mid_c->of0;
	IO_CNR(ch)->OFL_CSPR_REG.MCCSCLOF.MCCSCLOF1.bit.MCCSCLOF_1	= spr_cspr_mid_c->of1;
	IO_CNR(ch)->OFL_CSPR_REG.MCCSCLOF.MCCSCLOF1.bit.MCCSCLOF_2	= spr_cspr_mid_c->of2;
	IO_CNR(ch)->OFL_CSPR_REG.MCCSCLOF.MCCSCLOF1.bit.MCCSCLOF_3	= spr_cspr_mid_c->of3;
	IO_CNR(ch)->OFL_CSPR_REG.MCCSCLOF.MCCSCLOF2.bit.MCCSCLOF_4	= spr_cspr_mid_c->of4;
	IO_CNR(ch)->OFL_CSPR_REG.MCCSCLOF.MCCSCLOF2.bit.MCCSCLOF_5	= spr_cspr_mid_c->of5;

	// write signed data
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.MCCSCLGA.MCCSCLGA1, union io_cnr_cspr_reg_mccsclga_1, MCCSCLGA_0, spr_cspr_mid_c->gain0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.MCCSCLGA.MCCSCLGA1, union io_cnr_cspr_reg_mccsclga_1, MCCSCLGA_1, spr_cspr_mid_c->gain1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.MCCSCLGA.MCCSCLGA1, union io_cnr_cspr_reg_mccsclga_1, MCCSCLGA_2, spr_cspr_mid_c->gain2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.MCCSCLGA.MCCSCLGA1, union io_cnr_cspr_reg_mccsclga_1, MCCSCLGA_3, spr_cspr_mid_c->gain3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.MCCSCLGA.MCCSCLGA2, union io_cnr_cspr_reg_mccsclga_2, MCCSCLGA_4, spr_cspr_mid_c->gain4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.MCCSCLGA.MCCSCLGA2, union io_cnr_cspr_reg_mccsclga_2, MCCSCLGA_5, spr_cspr_mid_c->gain5 );

	Im_CNR_Off_Pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
Set SPR CbCr table for Middle frequency CbCr
*/
INT32 im_cnr_cspr_otf_set_cspr_mid_cc_y_table(ImCnrCspr*self, UCHAR ch, const T_IM_CNR_TABLE* const spr_cspr_mid_c )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_cspr_otf_set_cspr_mid_cc_y_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_cspr_mid_c == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_cspr_otf_set_cspr_mid_cc_y_table() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	Im_CNR_On_Pclk(ch);
	Im_CNR_Dsb();

	IO_CNR(ch)->OTF_CSPR_REG.MCCSCLBD.MCCSCLBD1.bit.MCCSCLBD_1	= spr_cspr_mid_c->bd1;
	IO_CNR(ch)->OTF_CSPR_REG.MCCSCLBD.MCCSCLBD1.bit.MCCSCLBD_2	= spr_cspr_mid_c->bd2;
	IO_CNR(ch)->OTF_CSPR_REG.MCCSCLBD.MCCSCLBD1.bit.MCCSCLBD_3	= spr_cspr_mid_c->bd3;
	IO_CNR(ch)->OTF_CSPR_REG.MCCSCLBD.MCCSCLBD1.bit.MCCSCLBD_4	= spr_cspr_mid_c->bd4;
	IO_CNR(ch)->OTF_CSPR_REG.MCCSCLBD.MCCSCLBD2.bit.MCCSCLBD_5	= spr_cspr_mid_c->bd5;
	IO_CNR(ch)->OTF_CSPR_REG.MCCSCLOF.MCCSCLOF1.bit.MCCSCLOF_0	= spr_cspr_mid_c->of0;
	IO_CNR(ch)->OTF_CSPR_REG.MCCSCLOF.MCCSCLOF1.bit.MCCSCLOF_1	= spr_cspr_mid_c->of1;
	IO_CNR(ch)->OTF_CSPR_REG.MCCSCLOF.MCCSCLOF1.bit.MCCSCLOF_2	= spr_cspr_mid_c->of2;
	IO_CNR(ch)->OTF_CSPR_REG.MCCSCLOF.MCCSCLOF1.bit.MCCSCLOF_3	= spr_cspr_mid_c->of3;
	IO_CNR(ch)->OTF_CSPR_REG.MCCSCLOF.MCCSCLOF2.bit.MCCSCLOF_4	= spr_cspr_mid_c->of4;
	IO_CNR(ch)->OTF_CSPR_REG.MCCSCLOF.MCCSCLOF2.bit.MCCSCLOF_5	= spr_cspr_mid_c->of5;

	// write signed data
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.MCCSCLGA.MCCSCLGA1, union io_cnr_cspr_reg_mccsclga_1, MCCSCLGA_0, spr_cspr_mid_c->gain0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.MCCSCLGA.MCCSCLGA1, union io_cnr_cspr_reg_mccsclga_1, MCCSCLGA_1, spr_cspr_mid_c->gain1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.MCCSCLGA.MCCSCLGA1, union io_cnr_cspr_reg_mccsclga_1, MCCSCLGA_2, spr_cspr_mid_c->gain2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.MCCSCLGA.MCCSCLGA1, union io_cnr_cspr_reg_mccsclga_1, MCCSCLGA_3, spr_cspr_mid_c->gain3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.MCCSCLGA.MCCSCLGA2, union io_cnr_cspr_reg_mccsclga_2, MCCSCLGA_4, spr_cspr_mid_c->gain4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.MCCSCLGA.MCCSCLGA2, union io_cnr_cspr_reg_mccsclga_2, MCCSCLGA_5, spr_cspr_mid_c->gain5 );

	Im_CNR_Off_Pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
Set SPR CbCr table for Middle frequency CbCr
*/
INT32 im_cnr_cspr_ofl_set_cspr_mid_cc_c_table(ImCnrCspr*self, UCHAR ch, const T_IM_CNR_TABLE* const spr_cspr_mid_c )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_cspr_ofl_set_cspr_mid_cc_c_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_cspr_mid_c == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_cspr_ofl_set_cspr_mid_cc_c_table() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	Im_CNR_On_Pclk(ch);
	Im_CNR_Dsb();

	IO_CNR(ch)->OFL_CSPR_REG.MCSSCLBD.MCSSCLBD1.bit.MCSSCLBD_1	= spr_cspr_mid_c->bd1;
	IO_CNR(ch)->OFL_CSPR_REG.MCSSCLBD.MCSSCLBD1.bit.MCSSCLBD_2	= spr_cspr_mid_c->bd2;
	IO_CNR(ch)->OFL_CSPR_REG.MCSSCLBD.MCSSCLBD1.bit.MCSSCLBD_3	= spr_cspr_mid_c->bd3;
	IO_CNR(ch)->OFL_CSPR_REG.MCSSCLBD.MCSSCLBD1.bit.MCSSCLBD_4	= spr_cspr_mid_c->bd4;
	IO_CNR(ch)->OFL_CSPR_REG.MCSSCLBD.MCSSCLBD2.bit.MCSSCLBD_5	= spr_cspr_mid_c->bd5;
	IO_CNR(ch)->OFL_CSPR_REG.MCSSCLOF.MCSSCLOF1.bit.MCSSCLOF_0	= spr_cspr_mid_c->of0;
	IO_CNR(ch)->OFL_CSPR_REG.MCSSCLOF.MCSSCLOF1.bit.MCSSCLOF_1	= spr_cspr_mid_c->of1;
	IO_CNR(ch)->OFL_CSPR_REG.MCSSCLOF.MCSSCLOF1.bit.MCSSCLOF_2	= spr_cspr_mid_c->of2;
	IO_CNR(ch)->OFL_CSPR_REG.MCSSCLOF.MCSSCLOF1.bit.MCSSCLOF_3	= spr_cspr_mid_c->of3;
	IO_CNR(ch)->OFL_CSPR_REG.MCSSCLOF.MCSSCLOF2.bit.MCSSCLOF_4	= spr_cspr_mid_c->of4;
	IO_CNR(ch)->OFL_CSPR_REG.MCSSCLOF.MCSSCLOF2.bit.MCSSCLOF_5	= spr_cspr_mid_c->of5;

	// write signed data
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.MCSSCLGA.MCSSCLGA1, union io_cnr_cspr_reg_mcssclga_1, MCSSCLGA_0, spr_cspr_mid_c->gain0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.MCSSCLGA.MCSSCLGA1, union io_cnr_cspr_reg_mcssclga_1, MCSSCLGA_1, spr_cspr_mid_c->gain1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.MCSSCLGA.MCSSCLGA1, union io_cnr_cspr_reg_mcssclga_1, MCSSCLGA_2, spr_cspr_mid_c->gain2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.MCSSCLGA.MCSSCLGA1, union io_cnr_cspr_reg_mcssclga_1, MCSSCLGA_3, spr_cspr_mid_c->gain3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.MCSSCLGA.MCSSCLGA2, union io_cnr_cspr_reg_mcssclga_2, MCSSCLGA_4, spr_cspr_mid_c->gain4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.MCSSCLGA.MCSSCLGA2, union io_cnr_cspr_reg_mcssclga_2, MCSSCLGA_5, spr_cspr_mid_c->gain5 );

	Im_CNR_Off_Pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
Set SPR CbCr table for Middle frequency CbCr
*/
INT32 im_cnr_cspr_otf_set_cspr_mid_cc_c_table(ImCnrCspr*self, UCHAR ch, const T_IM_CNR_TABLE* const spr_cspr_mid_c )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_cspr_otf_set_cspr_mid_cc_c_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_cspr_mid_c == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_cspr_otf_set_cspr_mid_cc_c_table() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	Im_CNR_On_Pclk(ch);
	Im_CNR_Dsb();

	IO_CNR(ch)->OTF_CSPR_REG.MCSSCLBD.MCSSCLBD1.bit.MCSSCLBD_1	= spr_cspr_mid_c->bd1;
	IO_CNR(ch)->OTF_CSPR_REG.MCSSCLBD.MCSSCLBD1.bit.MCSSCLBD_2	= spr_cspr_mid_c->bd2;
	IO_CNR(ch)->OTF_CSPR_REG.MCSSCLBD.MCSSCLBD1.bit.MCSSCLBD_3	= spr_cspr_mid_c->bd3;
	IO_CNR(ch)->OTF_CSPR_REG.MCSSCLBD.MCSSCLBD1.bit.MCSSCLBD_4	= spr_cspr_mid_c->bd4;
	IO_CNR(ch)->OTF_CSPR_REG.MCSSCLBD.MCSSCLBD2.bit.MCSSCLBD_5	= spr_cspr_mid_c->bd5;
	IO_CNR(ch)->OTF_CSPR_REG.MCSSCLOF.MCSSCLOF1.bit.MCSSCLOF_0	= spr_cspr_mid_c->of0;
	IO_CNR(ch)->OTF_CSPR_REG.MCSSCLOF.MCSSCLOF1.bit.MCSSCLOF_1	= spr_cspr_mid_c->of1;
	IO_CNR(ch)->OTF_CSPR_REG.MCSSCLOF.MCSSCLOF1.bit.MCSSCLOF_2	= spr_cspr_mid_c->of2;
	IO_CNR(ch)->OTF_CSPR_REG.MCSSCLOF.MCSSCLOF1.bit.MCSSCLOF_3	= spr_cspr_mid_c->of3;
	IO_CNR(ch)->OTF_CSPR_REG.MCSSCLOF.MCSSCLOF2.bit.MCSSCLOF_4	= spr_cspr_mid_c->of4;
	IO_CNR(ch)->OTF_CSPR_REG.MCSSCLOF.MCSSCLOF2.bit.MCSSCLOF_5	= spr_cspr_mid_c->of5;

	// write signed data
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.MCSSCLGA.MCSSCLGA1, union io_cnr_cspr_reg_mcssclga_1, MCSSCLGA_0, spr_cspr_mid_c->gain0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.MCSSCLGA.MCSSCLGA1, union io_cnr_cspr_reg_mcssclga_1, MCSSCLGA_1, spr_cspr_mid_c->gain1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.MCSSCLGA.MCSSCLGA1, union io_cnr_cspr_reg_mcssclga_1, MCSSCLGA_2, spr_cspr_mid_c->gain2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.MCSSCLGA.MCSSCLGA1, union io_cnr_cspr_reg_mcssclga_1, MCSSCLGA_3, spr_cspr_mid_c->gain3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.MCSSCLGA.MCSSCLGA2, union io_cnr_cspr_reg_mcssclga_2, MCSSCLGA_4, spr_cspr_mid_c->gain4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.MCSSCLGA.MCSSCLGA2, union io_cnr_cspr_reg_mcssclga_2, MCSSCLGA_5, spr_cspr_mid_c->gain5 );

	Im_CNR_Off_Pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
Set SPR Y table for Low frequency CbCr
*/
INT32 im_cnr_cspr_ofl_set_cspr_low_y_table(ImCnrCspr*self, UCHAR ch, const T_IM_CNR_TABLE* const spr_cspr_low_y )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_cspr_ofl_set_cspr_low_y_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_cspr_low_y == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_cspr_ofl_set_cspr_low_y_table() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	Im_CNR_On_Pclk(ch);
	Im_CNR_Dsb();

	IO_CNR(ch)->OFL_CSPR_REG.LCYSCLBD.LCYSCLBD1.bit.LCYSCLBD_1	= spr_cspr_low_y->bd1;
	IO_CNR(ch)->OFL_CSPR_REG.LCYSCLBD.LCYSCLBD1.bit.LCYSCLBD_2	= spr_cspr_low_y->bd2;
	IO_CNR(ch)->OFL_CSPR_REG.LCYSCLBD.LCYSCLBD1.bit.LCYSCLBD_3	= spr_cspr_low_y->bd3;
	IO_CNR(ch)->OFL_CSPR_REG.LCYSCLBD.LCYSCLBD1.bit.LCYSCLBD_4	= spr_cspr_low_y->bd4;
	IO_CNR(ch)->OFL_CSPR_REG.LCYSCLBD.LCYSCLBD2.bit.LCYSCLBD_5	= spr_cspr_low_y->bd5;
	IO_CNR(ch)->OFL_CSPR_REG.LCYSCLOF.LCYSCLOF1.bit.LCYSCLOF_0	= spr_cspr_low_y->of0;
	IO_CNR(ch)->OFL_CSPR_REG.LCYSCLOF.LCYSCLOF1.bit.LCYSCLOF_1	= spr_cspr_low_y->of1;
	IO_CNR(ch)->OFL_CSPR_REG.LCYSCLOF.LCYSCLOF1.bit.LCYSCLOF_2	= spr_cspr_low_y->of2;
	IO_CNR(ch)->OFL_CSPR_REG.LCYSCLOF.LCYSCLOF1.bit.LCYSCLOF_3	= spr_cspr_low_y->of3;
	IO_CNR(ch)->OFL_CSPR_REG.LCYSCLOF.LCYSCLOF2.bit.LCYSCLOF_4	= spr_cspr_low_y->of4;
	IO_CNR(ch)->OFL_CSPR_REG.LCYSCLOF.LCYSCLOF2.bit.LCYSCLOF_5	= spr_cspr_low_y->of5;

	// write signed data
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.LCYSCLGA.LCYSCLGA1, union io_cnr_cspr_reg_lcysclga_1, LCYSCLGA_0, spr_cspr_low_y->gain0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.LCYSCLGA.LCYSCLGA1, union io_cnr_cspr_reg_lcysclga_1, LCYSCLGA_1, spr_cspr_low_y->gain1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.LCYSCLGA.LCYSCLGA1, union io_cnr_cspr_reg_lcysclga_1, LCYSCLGA_2, spr_cspr_low_y->gain2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.LCYSCLGA.LCYSCLGA1, union io_cnr_cspr_reg_lcysclga_1, LCYSCLGA_3, spr_cspr_low_y->gain3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.LCYSCLGA.LCYSCLGA2, union io_cnr_cspr_reg_lcysclga_2, LCYSCLGA_4, spr_cspr_low_y->gain4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.LCYSCLGA.LCYSCLGA2, union io_cnr_cspr_reg_lcysclga_2, LCYSCLGA_5, spr_cspr_low_y->gain5 );

	Im_CNR_Off_Pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
Set SPR Y table for Low frequency CbCr
*/
INT32 im_cnr_cspr_otf_set_cspr_low_y_table(ImCnrCspr*self, UCHAR ch, const T_IM_CNR_TABLE* const spr_cspr_low_y )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_cspr_otf_set_cspr_low_y_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_cspr_low_y == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_cspr_otf_set_cspr_low_y_table() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	Im_CNR_On_Pclk(ch);
	Im_CNR_Dsb();

	IO_CNR(ch)->OTF_CSPR_REG.LCYSCLBD.LCYSCLBD1.bit.LCYSCLBD_1	= spr_cspr_low_y->bd1;
	IO_CNR(ch)->OTF_CSPR_REG.LCYSCLBD.LCYSCLBD1.bit.LCYSCLBD_2	= spr_cspr_low_y->bd2;
	IO_CNR(ch)->OTF_CSPR_REG.LCYSCLBD.LCYSCLBD1.bit.LCYSCLBD_3	= spr_cspr_low_y->bd3;
	IO_CNR(ch)->OTF_CSPR_REG.LCYSCLBD.LCYSCLBD1.bit.LCYSCLBD_4	= spr_cspr_low_y->bd4;
	IO_CNR(ch)->OTF_CSPR_REG.LCYSCLBD.LCYSCLBD2.bit.LCYSCLBD_5	= spr_cspr_low_y->bd5;
	IO_CNR(ch)->OTF_CSPR_REG.LCYSCLOF.LCYSCLOF1.bit.LCYSCLOF_0	= spr_cspr_low_y->of0;
	IO_CNR(ch)->OTF_CSPR_REG.LCYSCLOF.LCYSCLOF1.bit.LCYSCLOF_1	= spr_cspr_low_y->of1;
	IO_CNR(ch)->OTF_CSPR_REG.LCYSCLOF.LCYSCLOF1.bit.LCYSCLOF_2	= spr_cspr_low_y->of2;
	IO_CNR(ch)->OTF_CSPR_REG.LCYSCLOF.LCYSCLOF1.bit.LCYSCLOF_3	= spr_cspr_low_y->of3;
	IO_CNR(ch)->OTF_CSPR_REG.LCYSCLOF.LCYSCLOF2.bit.LCYSCLOF_4	= spr_cspr_low_y->of4;
	IO_CNR(ch)->OTF_CSPR_REG.LCYSCLOF.LCYSCLOF2.bit.LCYSCLOF_5	= spr_cspr_low_y->of5;

	// write signed data
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.LCYSCLGA.LCYSCLGA1, union io_cnr_cspr_reg_lcysclga_1, LCYSCLGA_0, spr_cspr_low_y->gain0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.LCYSCLGA.LCYSCLGA1, union io_cnr_cspr_reg_lcysclga_1, LCYSCLGA_1, spr_cspr_low_y->gain1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.LCYSCLGA.LCYSCLGA1, union io_cnr_cspr_reg_lcysclga_1, LCYSCLGA_2, spr_cspr_low_y->gain2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.LCYSCLGA.LCYSCLGA1, union io_cnr_cspr_reg_lcysclga_1, LCYSCLGA_3, spr_cspr_low_y->gain3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.LCYSCLGA.LCYSCLGA2, union io_cnr_cspr_reg_lcysclga_2, LCYSCLGA_4, spr_cspr_low_y->gain4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.LCYSCLGA.LCYSCLGA2, union io_cnr_cspr_reg_lcysclga_2, LCYSCLGA_5, spr_cspr_low_y->gain5 );

	Im_CNR_Off_Pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
Set SPR CbCr table for Low frequency CbCr
*/
INT32 im_cnr_cspr_ofl_set_cspr_low_cc_y_table(ImCnrCspr*self, UCHAR ch, const T_IM_CNR_TABLE* const spr_cspr_low_c )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_cspr_ofl_set_cspr_low_cc_y_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_cspr_low_c == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_cspr_ofl_set_cspr_low_cc_y_table() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	Im_CNR_On_Pclk(ch);
	Im_CNR_Dsb();

	IO_CNR(ch)->OFL_CSPR_REG.LCCSCLBD.LCCSCLBD1.bit.LCCSCLBD_1	= spr_cspr_low_c->bd1;
	IO_CNR(ch)->OFL_CSPR_REG.LCCSCLBD.LCCSCLBD1.bit.LCCSCLBD_2	= spr_cspr_low_c->bd2;
	IO_CNR(ch)->OFL_CSPR_REG.LCCSCLBD.LCCSCLBD1.bit.LCCSCLBD_3	= spr_cspr_low_c->bd3;
	IO_CNR(ch)->OFL_CSPR_REG.LCCSCLBD.LCCSCLBD1.bit.LCCSCLBD_4	= spr_cspr_low_c->bd4;
	IO_CNR(ch)->OFL_CSPR_REG.LCCSCLBD.LCCSCLBD2.bit.LCCSCLBD_5	= spr_cspr_low_c->bd5;
	IO_CNR(ch)->OFL_CSPR_REG.LCCSCLOF.LCCSCLOF1.bit.LCCSCLOF_0	= spr_cspr_low_c->of0;
	IO_CNR(ch)->OFL_CSPR_REG.LCCSCLOF.LCCSCLOF1.bit.LCCSCLOF_1	= spr_cspr_low_c->of1;
	IO_CNR(ch)->OFL_CSPR_REG.LCCSCLOF.LCCSCLOF1.bit.LCCSCLOF_2	= spr_cspr_low_c->of2;
	IO_CNR(ch)->OFL_CSPR_REG.LCCSCLOF.LCCSCLOF1.bit.LCCSCLOF_3	= spr_cspr_low_c->of3;
	IO_CNR(ch)->OFL_CSPR_REG.LCCSCLOF.LCCSCLOF2.bit.LCCSCLOF_4	= spr_cspr_low_c->of4;
	IO_CNR(ch)->OFL_CSPR_REG.LCCSCLOF.LCCSCLOF2.bit.LCCSCLOF_5	= spr_cspr_low_c->of5;

	// write signed data
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.LCCSCLGA.LCCSCLGA1, union io_cnr_cspr_reg_lccsclga_1, LCCSCLGA_0, spr_cspr_low_c->gain0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.LCCSCLGA.LCCSCLGA1, union io_cnr_cspr_reg_lccsclga_1, LCCSCLGA_1, spr_cspr_low_c->gain1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.LCCSCLGA.LCCSCLGA1, union io_cnr_cspr_reg_lccsclga_1, LCCSCLGA_2, spr_cspr_low_c->gain2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.LCCSCLGA.LCCSCLGA1, union io_cnr_cspr_reg_lccsclga_1, LCCSCLGA_3, spr_cspr_low_c->gain3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.LCCSCLGA.LCCSCLGA2, union io_cnr_cspr_reg_lccsclga_2, LCCSCLGA_4, spr_cspr_low_c->gain4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.LCCSCLGA.LCCSCLGA2, union io_cnr_cspr_reg_lccsclga_2, LCCSCLGA_5, spr_cspr_low_c->gain5 );

	Im_CNR_Off_Pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
Set SPR CbCr table for Low frequency CbCr
*/
INT32 im_cnr_cspr_otf_set_cspr_low_cc_y_table(ImCnrCspr*self, UCHAR ch, const T_IM_CNR_TABLE* const spr_cspr_low_c )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_cspr_otf_set_cspr_low_cc_y_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_cspr_low_c == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_cspr_otf_set_cspr_low_cc_y_table() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	Im_CNR_On_Pclk(ch);
	Im_CNR_Dsb();

	IO_CNR(ch)->OTF_CSPR_REG.LCCSCLBD.LCCSCLBD1.bit.LCCSCLBD_1	= spr_cspr_low_c->bd1;
	IO_CNR(ch)->OTF_CSPR_REG.LCCSCLBD.LCCSCLBD1.bit.LCCSCLBD_2	= spr_cspr_low_c->bd2;
	IO_CNR(ch)->OTF_CSPR_REG.LCCSCLBD.LCCSCLBD1.bit.LCCSCLBD_3	= spr_cspr_low_c->bd3;
	IO_CNR(ch)->OTF_CSPR_REG.LCCSCLBD.LCCSCLBD1.bit.LCCSCLBD_4	= spr_cspr_low_c->bd4;
	IO_CNR(ch)->OTF_CSPR_REG.LCCSCLBD.LCCSCLBD2.bit.LCCSCLBD_5	= spr_cspr_low_c->bd5;
	IO_CNR(ch)->OTF_CSPR_REG.LCCSCLOF.LCCSCLOF1.bit.LCCSCLOF_0	= spr_cspr_low_c->of0;
	IO_CNR(ch)->OTF_CSPR_REG.LCCSCLOF.LCCSCLOF1.bit.LCCSCLOF_1	= spr_cspr_low_c->of1;
	IO_CNR(ch)->OTF_CSPR_REG.LCCSCLOF.LCCSCLOF1.bit.LCCSCLOF_2	= spr_cspr_low_c->of2;
	IO_CNR(ch)->OTF_CSPR_REG.LCCSCLOF.LCCSCLOF1.bit.LCCSCLOF_3	= spr_cspr_low_c->of3;
	IO_CNR(ch)->OTF_CSPR_REG.LCCSCLOF.LCCSCLOF2.bit.LCCSCLOF_4	= spr_cspr_low_c->of4;
	IO_CNR(ch)->OTF_CSPR_REG.LCCSCLOF.LCCSCLOF2.bit.LCCSCLOF_5	= spr_cspr_low_c->of5;

	// write signed data
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.LCCSCLGA.LCCSCLGA1, union io_cnr_cspr_reg_lccsclga_1, LCCSCLGA_0, spr_cspr_low_c->gain0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.LCCSCLGA.LCCSCLGA1, union io_cnr_cspr_reg_lccsclga_1, LCCSCLGA_1, spr_cspr_low_c->gain1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.LCCSCLGA.LCCSCLGA1, union io_cnr_cspr_reg_lccsclga_1, LCCSCLGA_2, spr_cspr_low_c->gain2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.LCCSCLGA.LCCSCLGA1, union io_cnr_cspr_reg_lccsclga_1, LCCSCLGA_3, spr_cspr_low_c->gain3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.LCCSCLGA.LCCSCLGA2, union io_cnr_cspr_reg_lccsclga_2, LCCSCLGA_4, spr_cspr_low_c->gain4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.LCCSCLGA.LCCSCLGA2, union io_cnr_cspr_reg_lccsclga_2, LCCSCLGA_5, spr_cspr_low_c->gain5 );

	Im_CNR_Off_Pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
Set SPR CbCr table for Low frequency CbCr
*/
INT32 im_cnr_cspr_ofl_set_cspr_low_cc_c_table(ImCnrCspr*self, UCHAR ch, const T_IM_CNR_TABLE* const spr_cspr_low_c )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_cspr_ofl_set_cspr_low_cc_c_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_cspr_low_c == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_cspr_ofl_set_cspr_low_cc_c_table() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	Im_CNR_On_Pclk(ch);
	Im_CNR_Dsb();

	IO_CNR(ch)->OFL_CSPR_REG.LCSSCLBD.LCSSCLBD1.bit.LCSSCLBD_1	= spr_cspr_low_c->bd1;
	IO_CNR(ch)->OFL_CSPR_REG.LCSSCLBD.LCSSCLBD1.bit.LCSSCLBD_2	= spr_cspr_low_c->bd2;
	IO_CNR(ch)->OFL_CSPR_REG.LCSSCLBD.LCSSCLBD1.bit.LCSSCLBD_3	= spr_cspr_low_c->bd3;
	IO_CNR(ch)->OFL_CSPR_REG.LCSSCLBD.LCSSCLBD1.bit.LCSSCLBD_4	= spr_cspr_low_c->bd4;
	IO_CNR(ch)->OFL_CSPR_REG.LCSSCLBD.LCSSCLBD2.bit.LCSSCLBD_5	= spr_cspr_low_c->bd5;
	IO_CNR(ch)->OFL_CSPR_REG.LCSSCLOF.LCSSCLOF1.bit.LCSSCLOF_0	= spr_cspr_low_c->of0;
	IO_CNR(ch)->OFL_CSPR_REG.LCSSCLOF.LCSSCLOF1.bit.LCSSCLOF_1	= spr_cspr_low_c->of1;
	IO_CNR(ch)->OFL_CSPR_REG.LCSSCLOF.LCSSCLOF1.bit.LCSSCLOF_2	= spr_cspr_low_c->of2;
	IO_CNR(ch)->OFL_CSPR_REG.LCSSCLOF.LCSSCLOF1.bit.LCSSCLOF_3	= spr_cspr_low_c->of3;
	IO_CNR(ch)->OFL_CSPR_REG.LCSSCLOF.LCSSCLOF2.bit.LCSSCLOF_4	= spr_cspr_low_c->of4;
	IO_CNR(ch)->OFL_CSPR_REG.LCSSCLOF.LCSSCLOF2.bit.LCSSCLOF_5	= spr_cspr_low_c->of5;

	// write signed data
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.LCSSCLGA.LCSSCLGA1, union io_cnr_cspr_reg_lcssclga_1, LCSSCLGA_0, spr_cspr_low_c->gain0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.LCSSCLGA.LCSSCLGA1, union io_cnr_cspr_reg_lcssclga_1, LCSSCLGA_1, spr_cspr_low_c->gain1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.LCSSCLGA.LCSSCLGA1, union io_cnr_cspr_reg_lcssclga_1, LCSSCLGA_2, spr_cspr_low_c->gain2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.LCSSCLGA.LCSSCLGA1, union io_cnr_cspr_reg_lcssclga_1, LCSSCLGA_3, spr_cspr_low_c->gain3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.LCSSCLGA.LCSSCLGA2, union io_cnr_cspr_reg_lcssclga_2, LCSSCLGA_4, spr_cspr_low_c->gain4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.LCSSCLGA.LCSSCLGA2, union io_cnr_cspr_reg_lcssclga_2, LCSSCLGA_5, spr_cspr_low_c->gain5 );

	Im_CNR_Off_Pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
Set SPR CbCr table for Low frequency CbCr
*/
INT32 im_cnr_cspr_otf_set_cspr_low_cc_c_table(ImCnrCspr*self, UCHAR ch, const T_IM_CNR_TABLE* const spr_cspr_low_c )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_cspr_otf_set_cspr_low_cc_c_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_cspr_low_c == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_cspr_otf_set_cspr_low_cc_c_table() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	Im_CNR_On_Pclk(ch);
	Im_CNR_Dsb();

	IO_CNR(ch)->OTF_CSPR_REG.LCSSCLBD.LCSSCLBD1.bit.LCSSCLBD_1	= spr_cspr_low_c->bd1;
	IO_CNR(ch)->OTF_CSPR_REG.LCSSCLBD.LCSSCLBD1.bit.LCSSCLBD_2	= spr_cspr_low_c->bd2;
	IO_CNR(ch)->OTF_CSPR_REG.LCSSCLBD.LCSSCLBD1.bit.LCSSCLBD_3	= spr_cspr_low_c->bd3;
	IO_CNR(ch)->OTF_CSPR_REG.LCSSCLBD.LCSSCLBD1.bit.LCSSCLBD_4	= spr_cspr_low_c->bd4;
	IO_CNR(ch)->OTF_CSPR_REG.LCSSCLBD.LCSSCLBD2.bit.LCSSCLBD_5	= spr_cspr_low_c->bd5;
	IO_CNR(ch)->OTF_CSPR_REG.LCSSCLOF.LCSSCLOF1.bit.LCSSCLOF_0	= spr_cspr_low_c->of0;
	IO_CNR(ch)->OTF_CSPR_REG.LCSSCLOF.LCSSCLOF1.bit.LCSSCLOF_1	= spr_cspr_low_c->of1;
	IO_CNR(ch)->OTF_CSPR_REG.LCSSCLOF.LCSSCLOF1.bit.LCSSCLOF_2	= spr_cspr_low_c->of2;
	IO_CNR(ch)->OTF_CSPR_REG.LCSSCLOF.LCSSCLOF1.bit.LCSSCLOF_3	= spr_cspr_low_c->of3;
	IO_CNR(ch)->OTF_CSPR_REG.LCSSCLOF.LCSSCLOF2.bit.LCSSCLOF_4	= spr_cspr_low_c->of4;
	IO_CNR(ch)->OTF_CSPR_REG.LCSSCLOF.LCSSCLOF2.bit.LCSSCLOF_5	= spr_cspr_low_c->of5;

	// write signed data
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.LCSSCLGA.LCSSCLGA1, union io_cnr_cspr_reg_lcssclga_1, LCSSCLGA_0, spr_cspr_low_c->gain0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.LCSSCLGA.LCSSCLGA1, union io_cnr_cspr_reg_lcssclga_1, LCSSCLGA_1, spr_cspr_low_c->gain1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.LCSSCLGA.LCSSCLGA1, union io_cnr_cspr_reg_lcssclga_1, LCSSCLGA_2, spr_cspr_low_c->gain2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.LCSSCLGA.LCSSCLGA1, union io_cnr_cspr_reg_lcssclga_1, LCSSCLGA_3, spr_cspr_low_c->gain3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.LCSSCLGA.LCSSCLGA2, union io_cnr_cspr_reg_lcssclga_2, LCSSCLGA_4, spr_cspr_low_c->gain4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.LCSSCLGA.LCSSCLGA2, union io_cnr_cspr_reg_lcssclga_2, LCSSCLGA_5, spr_cspr_low_c->gain5 );

	Im_CNR_Off_Pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
Set SPR Edge for CbcCr for Off Line
*/
INT32 im_cnr_cspr_ofl_set_cspr_edge_table(ImCnrCspr*self, UCHAR ch, const T_IM_CNR_TABLE* const spr_cspr_edge )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_cspr_ofl_set_cspr_edge_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_cspr_edge == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_cspr_ofl_set_cspr_edge_table() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	Im_CNR_On_Pclk(ch);
	Im_CNR_Dsb();

	IO_CNR(ch)->OFL_CSPR_REG.CESCLBD.CESCLBD1.bit.CESCLBD_1	= spr_cspr_edge->bd1;
	IO_CNR(ch)->OFL_CSPR_REG.CESCLBD.CESCLBD1.bit.CESCLBD_2	= spr_cspr_edge->bd2;
	IO_CNR(ch)->OFL_CSPR_REG.CESCLBD.CESCLBD1.bit.CESCLBD_3	= spr_cspr_edge->bd3;
	IO_CNR(ch)->OFL_CSPR_REG.CESCLBD.CESCLBD1.bit.CESCLBD_4	= spr_cspr_edge->bd4;
	IO_CNR(ch)->OFL_CSPR_REG.CESCLBD.CESCLBD2.bit.CESCLBD_5	= spr_cspr_edge->bd5;
	IO_CNR(ch)->OFL_CSPR_REG.CESCLOF.CESCLOF1.bit.CESCLOF_0	= spr_cspr_edge->of0;
	IO_CNR(ch)->OFL_CSPR_REG.CESCLOF.CESCLOF1.bit.CESCLOF_1	= spr_cspr_edge->of1;
	IO_CNR(ch)->OFL_CSPR_REG.CESCLOF.CESCLOF1.bit.CESCLOF_2	= spr_cspr_edge->of2;
	IO_CNR(ch)->OFL_CSPR_REG.CESCLOF.CESCLOF1.bit.CESCLOF_3	= spr_cspr_edge->of3;
	IO_CNR(ch)->OFL_CSPR_REG.CESCLOF.CESCLOF2.bit.CESCLOF_4	= spr_cspr_edge->of4;
	IO_CNR(ch)->OFL_CSPR_REG.CESCLOF.CESCLOF2.bit.CESCLOF_5	= spr_cspr_edge->of5;

	// write signed data
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.CESCLGA.CESCLGA1, union io_cnr_cspr_reg_cesclga_1, CESCLGA_0, spr_cspr_edge->gain0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.CESCLGA.CESCLGA1, union io_cnr_cspr_reg_cesclga_1, CESCLGA_1, spr_cspr_edge->gain1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.CESCLGA.CESCLGA1, union io_cnr_cspr_reg_cesclga_1, CESCLGA_2, spr_cspr_edge->gain2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.CESCLGA.CESCLGA1, union io_cnr_cspr_reg_cesclga_1, CESCLGA_3, spr_cspr_edge->gain3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.CESCLGA.CESCLGA2, union io_cnr_cspr_reg_cesclga_2, CESCLGA_4, spr_cspr_edge->gain4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.CESCLGA.CESCLGA2, union io_cnr_cspr_reg_cesclga_2, CESCLGA_5, spr_cspr_edge->gain5 );

	Im_CNR_Off_Pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
Set SPR Edge for CbcCr for Off Line
*/
INT32 im_cnr_cspr_otf_set_cspr_edge_table(ImCnrCspr*self, UCHAR ch, const T_IM_CNR_TABLE* const spr_cspr_edge )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_cspr_otf_set_cspr_edge_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_cspr_edge == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_cspr_otf_set_cspr_edge_table() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	Im_CNR_On_Pclk(ch);
	Im_CNR_Dsb();

	IO_CNR(ch)->OTF_CSPR_REG.CESCLBD.CESCLBD1.bit.CESCLBD_1	= spr_cspr_edge->bd1;
	IO_CNR(ch)->OTF_CSPR_REG.CESCLBD.CESCLBD1.bit.CESCLBD_2	= spr_cspr_edge->bd2;
	IO_CNR(ch)->OTF_CSPR_REG.CESCLBD.CESCLBD1.bit.CESCLBD_3	= spr_cspr_edge->bd3;
	IO_CNR(ch)->OTF_CSPR_REG.CESCLBD.CESCLBD1.bit.CESCLBD_4	= spr_cspr_edge->bd4;
	IO_CNR(ch)->OTF_CSPR_REG.CESCLBD.CESCLBD2.bit.CESCLBD_5	= spr_cspr_edge->bd5;
	IO_CNR(ch)->OTF_CSPR_REG.CESCLOF.CESCLOF1.bit.CESCLOF_0	= spr_cspr_edge->of0;
	IO_CNR(ch)->OTF_CSPR_REG.CESCLOF.CESCLOF1.bit.CESCLOF_1	= spr_cspr_edge->of1;
	IO_CNR(ch)->OTF_CSPR_REG.CESCLOF.CESCLOF1.bit.CESCLOF_2	= spr_cspr_edge->of2;
	IO_CNR(ch)->OTF_CSPR_REG.CESCLOF.CESCLOF1.bit.CESCLOF_3	= spr_cspr_edge->of3;
	IO_CNR(ch)->OTF_CSPR_REG.CESCLOF.CESCLOF2.bit.CESCLOF_4	= spr_cspr_edge->of4;
	IO_CNR(ch)->OTF_CSPR_REG.CESCLOF.CESCLOF2.bit.CESCLOF_5	= spr_cspr_edge->of5;

	// write signed data
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.CESCLGA.CESCLGA1, union io_cnr_cspr_reg_cesclga_1, CESCLGA_0, spr_cspr_edge->gain0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.CESCLGA.CESCLGA1, union io_cnr_cspr_reg_cesclga_1, CESCLGA_1, spr_cspr_edge->gain1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.CESCLGA.CESCLGA1, union io_cnr_cspr_reg_cesclga_1, CESCLGA_2, spr_cspr_edge->gain2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.CESCLGA.CESCLGA1, union io_cnr_cspr_reg_cesclga_1, CESCLGA_3, spr_cspr_edge->gain3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.CESCLGA.CESCLGA2, union io_cnr_cspr_reg_cesclga_2, CESCLGA_4, spr_cspr_edge->gain4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.CESCLGA.CESCLGA2, union io_cnr_cspr_reg_cesclga_2, CESCLGA_5, spr_cspr_edge->gain5 );

	Im_CNR_Off_Pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
Set SPR Hue specified for CbcCr for Off Line
*/
INT32 im_cnr_cspr_ofl_set_cspr_hue_specified_table(ImCnrCspr*self, UCHAR ch, const T_IM_CNR_HUE_SPEC_TABLE* const spr_cspr_hue )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_cspr_ofl_set_cspr_hue_specified_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_cspr_hue == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_cspr_ofl_set_cspr_hue_specified_table() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	Im_CNR_On_Pclk(ch);
	Im_CNR_Dsb();

	// write signed data
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.CPHPT, union io_cnr_cspr_reg_cphpt, CDCB, spr_cspr_hue->cd_cb );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.CPHPT, union io_cnr_cspr_reg_cphpt, CDCR, spr_cspr_hue->cd_cr );

	IO_CNR(ch)->OFL_CSPR_REG.CPHPTK.bit.KCB	= spr_cspr_hue->k_cb;
	IO_CNR(ch)->OFL_CSPR_REG.CPHPTK.bit.KCR	= spr_cspr_hue->k_cr;

	IO_CNR(ch)->OFL_CSPR_REG.CDSCLBD.CDSCLBD1.bit.CDSCLBD_1	= spr_cspr_hue->bd1;
	IO_CNR(ch)->OFL_CSPR_REG.CDSCLBD.CDSCLBD1.bit.CDSCLBD_2	= spr_cspr_hue->bd2;
	IO_CNR(ch)->OFL_CSPR_REG.CDSCLBD.CDSCLBD2.bit.CDSCLBD_3	= spr_cspr_hue->bd3;
	IO_CNR(ch)->OFL_CSPR_REG.CDSCLBD.CDSCLBD2.bit.CDSCLBD_4	= spr_cspr_hue->bd4;
	IO_CNR(ch)->OFL_CSPR_REG.CDSCLBD.CDSCLBD3.bit.CDSCLBD_5	= spr_cspr_hue->bd5;
	IO_CNR(ch)->OFL_CSPR_REG.CDSCLOF.CDSCLOF1.bit.CDSCLOF_0	= spr_cspr_hue->of0;
	IO_CNR(ch)->OFL_CSPR_REG.CDSCLOF.CDSCLOF1.bit.CDSCLOF_1	= spr_cspr_hue->of1;
	IO_CNR(ch)->OFL_CSPR_REG.CDSCLOF.CDSCLOF2.bit.CDSCLOF_2	= spr_cspr_hue->of2;
	IO_CNR(ch)->OFL_CSPR_REG.CDSCLOF.CDSCLOF2.bit.CDSCLOF_3	= spr_cspr_hue->of3;
	IO_CNR(ch)->OFL_CSPR_REG.CDSCLOF.CDSCLOF3.bit.CDSCLOF_4	= spr_cspr_hue->of4;
	IO_CNR(ch)->OFL_CSPR_REG.CDSCLOF.CDSCLOF3.bit.CDSCLOF_5	= spr_cspr_hue->of5;

	// write signed data
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.CDSCLGA.CDSCLGA1, union io_cnr_cspr_reg_cdsclga_1, CDSCLGA_0, spr_cspr_hue->gain0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.CDSCLGA.CDSCLGA1, union io_cnr_cspr_reg_cdsclga_1, CDSCLGA_1, spr_cspr_hue->gain1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.CDSCLGA.CDSCLGA2, union io_cnr_cspr_reg_cdsclga_2, CDSCLGA_2, spr_cspr_hue->gain2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.CDSCLGA.CDSCLGA2, union io_cnr_cspr_reg_cdsclga_2, CDSCLGA_3, spr_cspr_hue->gain3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.CDSCLGA.CDSCLGA3, union io_cnr_cspr_reg_cdsclga_3, CDSCLGA_4, spr_cspr_hue->gain4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.CDSCLGA.CDSCLGA3, union io_cnr_cspr_reg_cdsclga_3, CDSCLGA_5, spr_cspr_hue->gain5 );

	Im_CNR_Off_Pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
Set SPR Hue specified for CbcCr for Off Line
*/
INT32 im_cnr_cspr_otf_set_cspr_hue_specified_table(ImCnrCspr*self, UCHAR ch, const T_IM_CNR_HUE_SPEC_TABLE* const spr_cspr_hue )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_cspr_otf_set_cspr_hue_specified_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_cspr_hue == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_cspr_otf_set_cspr_hue_specified_table() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	Im_CNR_On_Pclk(ch);
	Im_CNR_Dsb();

	// write signed data
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.CPHPT, union io_cnr_cspr_reg_cphpt, CDCB, spr_cspr_hue->cd_cb );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.CPHPT, union io_cnr_cspr_reg_cphpt, CDCR, spr_cspr_hue->cd_cr );

	IO_CNR(ch)->OTF_CSPR_REG.CPHPTK.bit.KCB	= spr_cspr_hue->k_cb;
	IO_CNR(ch)->OTF_CSPR_REG.CPHPTK.bit.KCR	= spr_cspr_hue->k_cr;

	IO_CNR(ch)->OTF_CSPR_REG.CDSCLBD.CDSCLBD1.bit.CDSCLBD_1	= spr_cspr_hue->bd1;
	IO_CNR(ch)->OTF_CSPR_REG.CDSCLBD.CDSCLBD1.bit.CDSCLBD_2	= spr_cspr_hue->bd2;
	IO_CNR(ch)->OTF_CSPR_REG.CDSCLBD.CDSCLBD2.bit.CDSCLBD_3	= spr_cspr_hue->bd3;
	IO_CNR(ch)->OTF_CSPR_REG.CDSCLBD.CDSCLBD2.bit.CDSCLBD_4	= spr_cspr_hue->bd4;
	IO_CNR(ch)->OTF_CSPR_REG.CDSCLBD.CDSCLBD3.bit.CDSCLBD_5	= spr_cspr_hue->bd5;
	IO_CNR(ch)->OTF_CSPR_REG.CDSCLOF.CDSCLOF1.bit.CDSCLOF_0	= spr_cspr_hue->of0;
	IO_CNR(ch)->OTF_CSPR_REG.CDSCLOF.CDSCLOF1.bit.CDSCLOF_1	= spr_cspr_hue->of1;
	IO_CNR(ch)->OTF_CSPR_REG.CDSCLOF.CDSCLOF2.bit.CDSCLOF_2	= spr_cspr_hue->of2;
	IO_CNR(ch)->OTF_CSPR_REG.CDSCLOF.CDSCLOF2.bit.CDSCLOF_3	= spr_cspr_hue->of3;
	IO_CNR(ch)->OTF_CSPR_REG.CDSCLOF.CDSCLOF3.bit.CDSCLOF_4	= spr_cspr_hue->of4;
	IO_CNR(ch)->OTF_CSPR_REG.CDSCLOF.CDSCLOF3.bit.CDSCLOF_5	= spr_cspr_hue->of5;

	// write signed data
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.CDSCLGA.CDSCLGA1, union io_cnr_cspr_reg_cdsclga_1, CDSCLGA_0, spr_cspr_hue->gain0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.CDSCLGA.CDSCLGA1, union io_cnr_cspr_reg_cdsclga_1, CDSCLGA_1, spr_cspr_hue->gain1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.CDSCLGA.CDSCLGA2, union io_cnr_cspr_reg_cdsclga_2, CDSCLGA_2, spr_cspr_hue->gain2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.CDSCLGA.CDSCLGA2, union io_cnr_cspr_reg_cdsclga_2, CDSCLGA_3, spr_cspr_hue->gain3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.CDSCLGA.CDSCLGA3, union io_cnr_cspr_reg_cdsclga_3, CDSCLGA_4, spr_cspr_hue->gain4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.CDSCLGA.CDSCLGA3, union io_cnr_cspr_reg_cdsclga_3, CDSCLGA_5, spr_cspr_hue->gain5 );

	Im_CNR_Off_Pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

ImCnrCspr *im_cnr_cspr_new(void)
{
	ImCnrCspr* self = k_object_new_with_private(IM_TYPE_CNR_CSPR,sizeof(ImCnrCsprPrivate));
	return self;
}
