/*
*@Copyright (c1) 2010-2020 上海网用软件有限公司
*@date:		 2020-8-5 (发布日期)
*@author:	 余林瑞
*@brief:
*@function:参照ETK代码规范，写一个模板类。
*设计的主要功能:
*1、命名规范
*2、类中各模块的布局规范
*3、常量枚举函数等声明及定义顺序
*@version: 1.0.0 实现一个模板类
*
*/


#include "imcnr.h"
#include "driver_common.h"
// #if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
// #endif
#include "dd_arm.h"
#include "ddim_user_custom.h"
#include "jdscnr.h"
// for memset
#include <string.h>
#include "imcnrone.h"
#include "imcnrtwo.h"


G_DEFINE_TYPE(ImCnrtwo, im_cnrtwo, G_TYPE_OBJECT);
#define IM_CNRTWO_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IM_TYPE_CNRTWO, ImCnrtwoPrivate));


struct _ImCnrtwoPrivate{

};


/*DECLS*/
static void 					dispose_od(GObject *object);
static void 					finalize_od(GObject *object);


/*IMPL*/
static void im_cnrtwo_class_init(ImCnrtwoClass *klass)
{
	g_type_class_add_private(klass, sizeof(ImCnrtwoPrivate));
}

static void im_cnrtwo_init(ImCnrtwo *self)
{
	ImCnrtwoPrivate *priv = IM_CNRTWO_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
	ImCnrtwoPrivate *self = IM_CNRTWO_GET_PRIVATE(object);
}

static void finalize_od(GObject *object)
{
	ImCnrtwoPrivate *self = IM_CNRTWO_GET_PRIVATE(object);
}

/*
Set SPR Y table for Middle frequency CbCr
*/
INT32 im_cnrtwo_otf_set_cspr_mid_y_table(ImCnrtwo *self, UCHAR ch,
		const ImCnrTable* const sprCsprMidY )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrtwo_otf_set_cspr_mid_y_table() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( sprCsprMidY == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrtwo_otf_set_cspr_mid_y_table() Parameter is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	ImCnr_DSB();

	IO_CNR(ch)->OTF_CSPR_REG.MCYSCLBD.MCYSCLBD1.bit.MCYSCLBD_1	= sprCsprMidY->bd1;
	IO_CNR(ch)->OTF_CSPR_REG.MCYSCLBD.MCYSCLBD1.bit.MCYSCLBD_2	= sprCsprMidY->bd2;
	IO_CNR(ch)->OTF_CSPR_REG.MCYSCLBD.MCYSCLBD1.bit.MCYSCLBD_3	= sprCsprMidY->bd3;
	IO_CNR(ch)->OTF_CSPR_REG.MCYSCLBD.MCYSCLBD1.bit.MCYSCLBD_4	= sprCsprMidY->bd4;
	IO_CNR(ch)->OTF_CSPR_REG.MCYSCLBD.MCYSCLBD2.bit.MCYSCLBD_5	= sprCsprMidY->bd5;
	IO_CNR(ch)->OTF_CSPR_REG.MCYSCLOF.MCYSCLOF1.bit.MCYSCLOF_0	= sprCsprMidY->of0;
	IO_CNR(ch)->OTF_CSPR_REG.MCYSCLOF.MCYSCLOF1.bit.MCYSCLOF_1	= sprCsprMidY->of1;
	IO_CNR(ch)->OTF_CSPR_REG.MCYSCLOF.MCYSCLOF1.bit.MCYSCLOF_2	= sprCsprMidY->of2;
	IO_CNR(ch)->OTF_CSPR_REG.MCYSCLOF.MCYSCLOF1.bit.MCYSCLOF_3	= sprCsprMidY->of3;
	IO_CNR(ch)->OTF_CSPR_REG.MCYSCLOF.MCYSCLOF2.bit.MCYSCLOF_4	= sprCsprMidY->of4;
	IO_CNR(ch)->OTF_CSPR_REG.MCYSCLOF.MCYSCLOF2.bit.MCYSCLOF_5	= sprCsprMidY->of5;

	// write signed data
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.MCYSCLGA.MCYSCLGA1,
			union io_cnr_cspr_reg_mcysclga_1, MCYSCLGA_0, sprCsprMidY->gain0 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.MCYSCLGA.MCYSCLGA1,
			union io_cnr_cspr_reg_mcysclga_1, MCYSCLGA_1, sprCsprMidY->gain1 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.MCYSCLGA.MCYSCLGA1,
			union io_cnr_cspr_reg_mcysclga_1, MCYSCLGA_2, sprCsprMidY->gain2 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.MCYSCLGA.MCYSCLGA1,
			union io_cnr_cspr_reg_mcysclga_1, MCYSCLGA_3, sprCsprMidY->gain3 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.MCYSCLGA.MCYSCLGA2,
			union io_cnr_cspr_reg_mcysclga_2, MCYSCLGA_4, sprCsprMidY->gain4 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.MCYSCLGA.MCYSCLGA2,
			union io_cnr_cspr_reg_mcysclga_2, MCYSCLGA_5, sprCsprMidY->gain5 );

	im_cnrone_off_pclk(ch);
	ImCnr_DSB();
	return D_DDIM_OK;
}

/*
Set SPR CbCr table for Middle frequency CbCr
*/
INT32 im_cnrtwo_ofl_set_cspr_mid_cc_y_table(ImCnrtwo *self, UCHAR ch, const ImCnrTable* const sprCsprMidC )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrtwo_ofl_set_cspr_mid_cc_y_table() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( sprCsprMidC == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrtwo_ofl_set_cspr_mid_cc_y_table() Parameter is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	ImCnr_DSB();

	IO_CNR(ch)->OFL_CSPR_REG.MCCSCLBD.MCCSCLBD1.bit.MCCSCLBD_1	= sprCsprMidC->bd1;
	IO_CNR(ch)->OFL_CSPR_REG.MCCSCLBD.MCCSCLBD1.bit.MCCSCLBD_2	= sprCsprMidC->bd2;
	IO_CNR(ch)->OFL_CSPR_REG.MCCSCLBD.MCCSCLBD1.bit.MCCSCLBD_3	= sprCsprMidC->bd3;
	IO_CNR(ch)->OFL_CSPR_REG.MCCSCLBD.MCCSCLBD1.bit.MCCSCLBD_4	= sprCsprMidC->bd4;
	IO_CNR(ch)->OFL_CSPR_REG.MCCSCLBD.MCCSCLBD2.bit.MCCSCLBD_5	= sprCsprMidC->bd5;
	IO_CNR(ch)->OFL_CSPR_REG.MCCSCLOF.MCCSCLOF1.bit.MCCSCLOF_0	= sprCsprMidC->of0;
	IO_CNR(ch)->OFL_CSPR_REG.MCCSCLOF.MCCSCLOF1.bit.MCCSCLOF_1	= sprCsprMidC->of1;
	IO_CNR(ch)->OFL_CSPR_REG.MCCSCLOF.MCCSCLOF1.bit.MCCSCLOF_2	= sprCsprMidC->of2;
	IO_CNR(ch)->OFL_CSPR_REG.MCCSCLOF.MCCSCLOF1.bit.MCCSCLOF_3	= sprCsprMidC->of3;
	IO_CNR(ch)->OFL_CSPR_REG.MCCSCLOF.MCCSCLOF2.bit.MCCSCLOF_4	= sprCsprMidC->of4;
	IO_CNR(ch)->OFL_CSPR_REG.MCCSCLOF.MCCSCLOF2.bit.MCCSCLOF_5	= sprCsprMidC->of5;

	// write signed data
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.MCCSCLGA.MCCSCLGA1,
			union io_cnr_cspr_reg_mccsclga_1, MCCSCLGA_0, sprCsprMidC->gain0 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.MCCSCLGA.MCCSCLGA1,
			union io_cnr_cspr_reg_mccsclga_1, MCCSCLGA_1, sprCsprMidC->gain1 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.MCCSCLGA.MCCSCLGA1,
			union io_cnr_cspr_reg_mccsclga_1, MCCSCLGA_2, sprCsprMidC->gain2 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.MCCSCLGA.MCCSCLGA1,
			union io_cnr_cspr_reg_mccsclga_1, MCCSCLGA_3, sprCsprMidC->gain3 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.MCCSCLGA.MCCSCLGA2,
			union io_cnr_cspr_reg_mccsclga_2, MCCSCLGA_4, sprCsprMidC->gain4 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.MCCSCLGA.MCCSCLGA2,
			union io_cnr_cspr_reg_mccsclga_2, MCCSCLGA_5, sprCsprMidC->gain5 );

	im_cnrone_off_pclk(ch);
	ImCnr_DSB();
	return D_DDIM_OK;
}

/*
Set SPR CbCr table for Middle frequency CbCr
*/
INT32 im_cnrtwo_otf_set_cspr_mid_cc_y_table(ImCnrtwo *self, UCHAR ch, const ImCnrTable* const sprCsprMidC )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrtwo_otf_set_cspr_mid_cc_y_table() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( sprCsprMidC == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrtwo_otf_set_cspr_mid_cc_y_table() Parameter is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	ImCnr_DSB();

	IO_CNR(ch)->OTF_CSPR_REG.MCCSCLBD.MCCSCLBD1.bit.MCCSCLBD_1	= sprCsprMidC->bd1;
	IO_CNR(ch)->OTF_CSPR_REG.MCCSCLBD.MCCSCLBD1.bit.MCCSCLBD_2	= sprCsprMidC->bd2;
	IO_CNR(ch)->OTF_CSPR_REG.MCCSCLBD.MCCSCLBD1.bit.MCCSCLBD_3	= sprCsprMidC->bd3;
	IO_CNR(ch)->OTF_CSPR_REG.MCCSCLBD.MCCSCLBD1.bit.MCCSCLBD_4	= sprCsprMidC->bd4;
	IO_CNR(ch)->OTF_CSPR_REG.MCCSCLBD.MCCSCLBD2.bit.MCCSCLBD_5	= sprCsprMidC->bd5;
	IO_CNR(ch)->OTF_CSPR_REG.MCCSCLOF.MCCSCLOF1.bit.MCCSCLOF_0	= sprCsprMidC->of0;
	IO_CNR(ch)->OTF_CSPR_REG.MCCSCLOF.MCCSCLOF1.bit.MCCSCLOF_1	= sprCsprMidC->of1;
	IO_CNR(ch)->OTF_CSPR_REG.MCCSCLOF.MCCSCLOF1.bit.MCCSCLOF_2	= sprCsprMidC->of2;
	IO_CNR(ch)->OTF_CSPR_REG.MCCSCLOF.MCCSCLOF1.bit.MCCSCLOF_3	= sprCsprMidC->of3;
	IO_CNR(ch)->OTF_CSPR_REG.MCCSCLOF.MCCSCLOF2.bit.MCCSCLOF_4	= sprCsprMidC->of4;
	IO_CNR(ch)->OTF_CSPR_REG.MCCSCLOF.MCCSCLOF2.bit.MCCSCLOF_5	= sprCsprMidC->of5;

	// write signed data
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.MCCSCLGA.MCCSCLGA1,
			union io_cnr_cspr_reg_mccsclga_1, MCCSCLGA_0, sprCsprMidC->gain0 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.MCCSCLGA.MCCSCLGA1,
			union io_cnr_cspr_reg_mccsclga_1, MCCSCLGA_1, sprCsprMidC->gain1 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.MCCSCLGA.MCCSCLGA1,
			union io_cnr_cspr_reg_mccsclga_1, MCCSCLGA_2, sprCsprMidC->gain2 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.MCCSCLGA.MCCSCLGA1,
			union io_cnr_cspr_reg_mccsclga_1, MCCSCLGA_3, sprCsprMidC->gain3 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.MCCSCLGA.MCCSCLGA2,
			union io_cnr_cspr_reg_mccsclga_2, MCCSCLGA_4, sprCsprMidC->gain4 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.MCCSCLGA.MCCSCLGA2,
			union io_cnr_cspr_reg_mccsclga_2, MCCSCLGA_5, sprCsprMidC->gain5 );

	im_cnrone_off_pclk(ch);
	ImCnr_DSB();
	return D_DDIM_OK;
}

/*
Set SPR CbCr table for Middle frequency CbCr
*/
INT32 im_cnrtwo_ofl_set_cspr_mid_cc_c_table(ImCnrtwo *self, UCHAR ch, const ImCnrTable* const sprCsprMidC )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrtwo_ofl_set_cspr_mid_cc_c_table() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( sprCsprMidC == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrtwo_ofl_set_cspr_mid_cc_c_table() Parameter is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	ImCnr_DSB();

	IO_CNR(ch)->OFL_CSPR_REG.MCSSCLBD.MCSSCLBD1.bit.MCSSCLBD_1	= sprCsprMidC->bd1;
	IO_CNR(ch)->OFL_CSPR_REG.MCSSCLBD.MCSSCLBD1.bit.MCSSCLBD_2	= sprCsprMidC->bd2;
	IO_CNR(ch)->OFL_CSPR_REG.MCSSCLBD.MCSSCLBD1.bit.MCSSCLBD_3	= sprCsprMidC->bd3;
	IO_CNR(ch)->OFL_CSPR_REG.MCSSCLBD.MCSSCLBD1.bit.MCSSCLBD_4	= sprCsprMidC->bd4;
	IO_CNR(ch)->OFL_CSPR_REG.MCSSCLBD.MCSSCLBD2.bit.MCSSCLBD_5	= sprCsprMidC->bd5;
	IO_CNR(ch)->OFL_CSPR_REG.MCSSCLOF.MCSSCLOF1.bit.MCSSCLOF_0	= sprCsprMidC->of0;
	IO_CNR(ch)->OFL_CSPR_REG.MCSSCLOF.MCSSCLOF1.bit.MCSSCLOF_1	= sprCsprMidC->of1;
	IO_CNR(ch)->OFL_CSPR_REG.MCSSCLOF.MCSSCLOF1.bit.MCSSCLOF_2	= sprCsprMidC->of2;
	IO_CNR(ch)->OFL_CSPR_REG.MCSSCLOF.MCSSCLOF1.bit.MCSSCLOF_3	= sprCsprMidC->of3;
	IO_CNR(ch)->OFL_CSPR_REG.MCSSCLOF.MCSSCLOF2.bit.MCSSCLOF_4	= sprCsprMidC->of4;
	IO_CNR(ch)->OFL_CSPR_REG.MCSSCLOF.MCSSCLOF2.bit.MCSSCLOF_5	= sprCsprMidC->of5;

	// write signed data
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.MCSSCLGA.MCSSCLGA1,
			union io_cnr_cspr_reg_mcssclga_1, MCSSCLGA_0, sprCsprMidC->gain0 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.MCSSCLGA.MCSSCLGA1,
			union io_cnr_cspr_reg_mcssclga_1, MCSSCLGA_1, sprCsprMidC->gain1 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.MCSSCLGA.MCSSCLGA1,
			union io_cnr_cspr_reg_mcssclga_1, MCSSCLGA_2, sprCsprMidC->gain2 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.MCSSCLGA.MCSSCLGA1,
			union io_cnr_cspr_reg_mcssclga_1, MCSSCLGA_3, sprCsprMidC->gain3 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.MCSSCLGA.MCSSCLGA2,
			union io_cnr_cspr_reg_mcssclga_2, MCSSCLGA_4, sprCsprMidC->gain4 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.MCSSCLGA.MCSSCLGA2,
			union io_cnr_cspr_reg_mcssclga_2, MCSSCLGA_5, sprCsprMidC->gain5 );

	im_cnrone_off_pclk(ch);
	ImCnr_DSB();

	return D_DDIM_OK;
}

/*
Set SPR CbCr table for Middle frequency CbCr
*/
INT32 im_cnrtwo_otf_set_cspr_mid_cc_c_table(ImCnrtwo *self, UCHAR ch, const ImCnrTable* const sprCsprMidC )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrtwo_otf_set_cspr_mid_cc_c_table() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( sprCsprMidC == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrtwo_otf_set_cspr_mid_cc_c_table() Parameter is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	ImCnr_DSB();

	IO_CNR(ch)->OTF_CSPR_REG.MCSSCLBD.MCSSCLBD1.bit.MCSSCLBD_1	= sprCsprMidC->bd1;
	IO_CNR(ch)->OTF_CSPR_REG.MCSSCLBD.MCSSCLBD1.bit.MCSSCLBD_2	= sprCsprMidC->bd2;
	IO_CNR(ch)->OTF_CSPR_REG.MCSSCLBD.MCSSCLBD1.bit.MCSSCLBD_3	= sprCsprMidC->bd3;
	IO_CNR(ch)->OTF_CSPR_REG.MCSSCLBD.MCSSCLBD1.bit.MCSSCLBD_4	= sprCsprMidC->bd4;
	IO_CNR(ch)->OTF_CSPR_REG.MCSSCLBD.MCSSCLBD2.bit.MCSSCLBD_5	= sprCsprMidC->bd5;
	IO_CNR(ch)->OTF_CSPR_REG.MCSSCLOF.MCSSCLOF1.bit.MCSSCLOF_0	= sprCsprMidC->of0;
	IO_CNR(ch)->OTF_CSPR_REG.MCSSCLOF.MCSSCLOF1.bit.MCSSCLOF_1	= sprCsprMidC->of1;
	IO_CNR(ch)->OTF_CSPR_REG.MCSSCLOF.MCSSCLOF1.bit.MCSSCLOF_2	= sprCsprMidC->of2;
	IO_CNR(ch)->OTF_CSPR_REG.MCSSCLOF.MCSSCLOF1.bit.MCSSCLOF_3	= sprCsprMidC->of3;
	IO_CNR(ch)->OTF_CSPR_REG.MCSSCLOF.MCSSCLOF2.bit.MCSSCLOF_4	= sprCsprMidC->of4;
	IO_CNR(ch)->OTF_CSPR_REG.MCSSCLOF.MCSSCLOF2.bit.MCSSCLOF_5	= sprCsprMidC->of5;

	// write signed data
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.MCSSCLGA.MCSSCLGA1,
			union io_cnr_cspr_reg_mcssclga_1, MCSSCLGA_0, sprCsprMidC->gain0 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.MCSSCLGA.MCSSCLGA1,
			union io_cnr_cspr_reg_mcssclga_1, MCSSCLGA_1, sprCsprMidC->gain1 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.MCSSCLGA.MCSSCLGA1,
			union io_cnr_cspr_reg_mcssclga_1, MCSSCLGA_2, sprCsprMidC->gain2 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.MCSSCLGA.MCSSCLGA1,
			union io_cnr_cspr_reg_mcssclga_1, MCSSCLGA_3, sprCsprMidC->gain3 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.MCSSCLGA.MCSSCLGA2,
			union io_cnr_cspr_reg_mcssclga_2, MCSSCLGA_4, sprCsprMidC->gain4 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.MCSSCLGA.MCSSCLGA2,
			union io_cnr_cspr_reg_mcssclga_2, MCSSCLGA_5, sprCsprMidC->gain5 );

	im_cnrone_off_pclk(ch);
	ImCnr_DSB();

	return D_DDIM_OK;
}

/*
Set SPR Y table for Low frequency CbCr
*/
INT32 im_cnrtwo_ofl_set_cspr_low_y_table(ImCnrtwo *self, UCHAR ch, const ImCnrTable* const sprCsprLowY )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrtwo_ofl_set_cspr_low_y_table() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( sprCsprLowY == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrtwo_ofl_set_cspr_low_y_table() Parameter is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	ImCnr_DSB();

	IO_CNR(ch)->OFL_CSPR_REG.LCYSCLBD.LCYSCLBD1.bit.LCYSCLBD_1	= sprCsprLowY->bd1;
	IO_CNR(ch)->OFL_CSPR_REG.LCYSCLBD.LCYSCLBD1.bit.LCYSCLBD_2	= sprCsprLowY->bd2;
	IO_CNR(ch)->OFL_CSPR_REG.LCYSCLBD.LCYSCLBD1.bit.LCYSCLBD_3	= sprCsprLowY->bd3;
	IO_CNR(ch)->OFL_CSPR_REG.LCYSCLBD.LCYSCLBD1.bit.LCYSCLBD_4	= sprCsprLowY->bd4;
	IO_CNR(ch)->OFL_CSPR_REG.LCYSCLBD.LCYSCLBD2.bit.LCYSCLBD_5	= sprCsprLowY->bd5;
	IO_CNR(ch)->OFL_CSPR_REG.LCYSCLOF.LCYSCLOF1.bit.LCYSCLOF_0	= sprCsprLowY->of0;
	IO_CNR(ch)->OFL_CSPR_REG.LCYSCLOF.LCYSCLOF1.bit.LCYSCLOF_1	= sprCsprLowY->of1;
	IO_CNR(ch)->OFL_CSPR_REG.LCYSCLOF.LCYSCLOF1.bit.LCYSCLOF_2	= sprCsprLowY->of2;
	IO_CNR(ch)->OFL_CSPR_REG.LCYSCLOF.LCYSCLOF1.bit.LCYSCLOF_3	= sprCsprLowY->of3;
	IO_CNR(ch)->OFL_CSPR_REG.LCYSCLOF.LCYSCLOF2.bit.LCYSCLOF_4	= sprCsprLowY->of4;
	IO_CNR(ch)->OFL_CSPR_REG.LCYSCLOF.LCYSCLOF2.bit.LCYSCLOF_5	= sprCsprLowY->of5;

	// write signed data
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.LCYSCLGA.LCYSCLGA1,
			union io_cnr_cspr_reg_lcysclga_1, LCYSCLGA_0, sprCsprLowY->gain0 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.LCYSCLGA.LCYSCLGA1,
			union io_cnr_cspr_reg_lcysclga_1, LCYSCLGA_1, sprCsprLowY->gain1 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.LCYSCLGA.LCYSCLGA1,
			union io_cnr_cspr_reg_lcysclga_1, LCYSCLGA_2, sprCsprLowY->gain2 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.LCYSCLGA.LCYSCLGA1,
			union io_cnr_cspr_reg_lcysclga_1, LCYSCLGA_3, sprCsprLowY->gain3 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.LCYSCLGA.LCYSCLGA2,
			union io_cnr_cspr_reg_lcysclga_2, LCYSCLGA_4, sprCsprLowY->gain4 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.LCYSCLGA.LCYSCLGA2,
			union io_cnr_cspr_reg_lcysclga_2, LCYSCLGA_5, sprCsprLowY->gain5 );

	im_cnrone_off_pclk(ch);
	ImCnr_DSB();
	return D_DDIM_OK;
}

/*
Set SPR Y table for Low frequency CbCr
*/
INT32 im_cnrtwo_otf_set_cspr_low_y_table(ImCnrtwo *self, UCHAR ch, const ImCnrTable* const sprCsprLowY )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrtwo_otf_set_cspr_low_y_table() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( sprCsprLowY == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrtwo_otf_set_cspr_low_y_table() Parameter is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	ImCnr_DSB();

	IO_CNR(ch)->OTF_CSPR_REG.LCYSCLBD.LCYSCLBD1.bit.LCYSCLBD_1	= sprCsprLowY->bd1;
	IO_CNR(ch)->OTF_CSPR_REG.LCYSCLBD.LCYSCLBD1.bit.LCYSCLBD_2	= sprCsprLowY->bd2;
	IO_CNR(ch)->OTF_CSPR_REG.LCYSCLBD.LCYSCLBD1.bit.LCYSCLBD_3	= sprCsprLowY->bd3;
	IO_CNR(ch)->OTF_CSPR_REG.LCYSCLBD.LCYSCLBD1.bit.LCYSCLBD_4	= sprCsprLowY->bd4;
	IO_CNR(ch)->OTF_CSPR_REG.LCYSCLBD.LCYSCLBD2.bit.LCYSCLBD_5	= sprCsprLowY->bd5;
	IO_CNR(ch)->OTF_CSPR_REG.LCYSCLOF.LCYSCLOF1.bit.LCYSCLOF_0	= sprCsprLowY->of0;
	IO_CNR(ch)->OTF_CSPR_REG.LCYSCLOF.LCYSCLOF1.bit.LCYSCLOF_1	= sprCsprLowY->of1;
	IO_CNR(ch)->OTF_CSPR_REG.LCYSCLOF.LCYSCLOF1.bit.LCYSCLOF_2	= sprCsprLowY->of2;
	IO_CNR(ch)->OTF_CSPR_REG.LCYSCLOF.LCYSCLOF1.bit.LCYSCLOF_3	= sprCsprLowY->of3;
	IO_CNR(ch)->OTF_CSPR_REG.LCYSCLOF.LCYSCLOF2.bit.LCYSCLOF_4	= sprCsprLowY->of4;
	IO_CNR(ch)->OTF_CSPR_REG.LCYSCLOF.LCYSCLOF2.bit.LCYSCLOF_5	= sprCsprLowY->of5;

	// write signed data
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.LCYSCLGA.LCYSCLGA1,
			union io_cnr_cspr_reg_lcysclga_1, LCYSCLGA_0, sprCsprLowY->gain0 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.LCYSCLGA.LCYSCLGA1,
			union io_cnr_cspr_reg_lcysclga_1, LCYSCLGA_1, sprCsprLowY->gain1 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.LCYSCLGA.LCYSCLGA1,
			union io_cnr_cspr_reg_lcysclga_1, LCYSCLGA_2, sprCsprLowY->gain2 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.LCYSCLGA.LCYSCLGA1,
			union io_cnr_cspr_reg_lcysclga_1, LCYSCLGA_3, sprCsprLowY->gain3 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.LCYSCLGA.LCYSCLGA2,
			union io_cnr_cspr_reg_lcysclga_2, LCYSCLGA_4, sprCsprLowY->gain4 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.LCYSCLGA.LCYSCLGA2,
			union io_cnr_cspr_reg_lcysclga_2, LCYSCLGA_5, sprCsprLowY->gain5 );

	im_cnrone_off_pclk(ch);
	ImCnr_DSB();

	return D_DDIM_OK;
}

/*
Set SPR CbCr table for Low frequency CbCr
*/
INT32 im_cnrtwo_ofl_set_cspr_low_cc_y_table(ImCnrtwo *self, UCHAR ch, const ImCnrTable* const sprCsprLowC )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrtwo_ofl_set_cspr_low_cc_y_table() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( sprCsprLowC == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrtwo_ofl_set_cspr_low_cc_y_table() Parameter is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	ImCnr_DSB();

	IO_CNR(ch)->OFL_CSPR_REG.LCCSCLBD.LCCSCLBD1.bit.LCCSCLBD_1	= sprCsprLowC->bd1;
	IO_CNR(ch)->OFL_CSPR_REG.LCCSCLBD.LCCSCLBD1.bit.LCCSCLBD_2	= sprCsprLowC->bd2;
	IO_CNR(ch)->OFL_CSPR_REG.LCCSCLBD.LCCSCLBD1.bit.LCCSCLBD_3	= sprCsprLowC->bd3;
	IO_CNR(ch)->OFL_CSPR_REG.LCCSCLBD.LCCSCLBD1.bit.LCCSCLBD_4	= sprCsprLowC->bd4;
	IO_CNR(ch)->OFL_CSPR_REG.LCCSCLBD.LCCSCLBD2.bit.LCCSCLBD_5	= sprCsprLowC->bd5;
	IO_CNR(ch)->OFL_CSPR_REG.LCCSCLOF.LCCSCLOF1.bit.LCCSCLOF_0	= sprCsprLowC->of0;
	IO_CNR(ch)->OFL_CSPR_REG.LCCSCLOF.LCCSCLOF1.bit.LCCSCLOF_1	= sprCsprLowC->of1;
	IO_CNR(ch)->OFL_CSPR_REG.LCCSCLOF.LCCSCLOF1.bit.LCCSCLOF_2	= sprCsprLowC->of2;
	IO_CNR(ch)->OFL_CSPR_REG.LCCSCLOF.LCCSCLOF1.bit.LCCSCLOF_3	= sprCsprLowC->of3;
	IO_CNR(ch)->OFL_CSPR_REG.LCCSCLOF.LCCSCLOF2.bit.LCCSCLOF_4	= sprCsprLowC->of4;
	IO_CNR(ch)->OFL_CSPR_REG.LCCSCLOF.LCCSCLOF2.bit.LCCSCLOF_5	= sprCsprLowC->of5;

	// write signed data
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.LCCSCLGA.LCCSCLGA1,
			union io_cnr_cspr_reg_lccsclga_1, LCCSCLGA_0, sprCsprLowC->gain0 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.LCCSCLGA.LCCSCLGA1,
			union io_cnr_cspr_reg_lccsclga_1, LCCSCLGA_1, sprCsprLowC->gain1 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.LCCSCLGA.LCCSCLGA1,
			union io_cnr_cspr_reg_lccsclga_1, LCCSCLGA_2, sprCsprLowC->gain2 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.LCCSCLGA.LCCSCLGA1,
			union io_cnr_cspr_reg_lccsclga_1, LCCSCLGA_3, sprCsprLowC->gain3 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.LCCSCLGA.LCCSCLGA2,
			union io_cnr_cspr_reg_lccsclga_2, LCCSCLGA_4, sprCsprLowC->gain4 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.LCCSCLGA.LCCSCLGA2,
			union io_cnr_cspr_reg_lccsclga_2, LCCSCLGA_5, sprCsprLowC->gain5 );

	im_cnrone_off_pclk(ch);
	ImCnr_DSB();

	return D_DDIM_OK;
}

/*
Set SPR CbCr table for Low frequency CbCr
*/
INT32 im_cnrtwo_otf_set_cspr_low_cc_y_table(ImCnrtwo *self, UCHAR ch, const ImCnrTable* const sprCsprLowC )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrtwo_otf_set_cspr_low_cc_y_table() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( sprCsprLowC == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrtwo_otf_set_cspr_low_cc_y_table() Parameter is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	ImCnr_DSB();

	IO_CNR(ch)->OTF_CSPR_REG.LCCSCLBD.LCCSCLBD1.bit.LCCSCLBD_1	= sprCsprLowC->bd1;
	IO_CNR(ch)->OTF_CSPR_REG.LCCSCLBD.LCCSCLBD1.bit.LCCSCLBD_2	= sprCsprLowC->bd2;
	IO_CNR(ch)->OTF_CSPR_REG.LCCSCLBD.LCCSCLBD1.bit.LCCSCLBD_3	= sprCsprLowC->bd3;
	IO_CNR(ch)->OTF_CSPR_REG.LCCSCLBD.LCCSCLBD1.bit.LCCSCLBD_4	= sprCsprLowC->bd4;
	IO_CNR(ch)->OTF_CSPR_REG.LCCSCLBD.LCCSCLBD2.bit.LCCSCLBD_5	= sprCsprLowC->bd5;
	IO_CNR(ch)->OTF_CSPR_REG.LCCSCLOF.LCCSCLOF1.bit.LCCSCLOF_0	= sprCsprLowC->of0;
	IO_CNR(ch)->OTF_CSPR_REG.LCCSCLOF.LCCSCLOF1.bit.LCCSCLOF_1	= sprCsprLowC->of1;
	IO_CNR(ch)->OTF_CSPR_REG.LCCSCLOF.LCCSCLOF1.bit.LCCSCLOF_2	= sprCsprLowC->of2;
	IO_CNR(ch)->OTF_CSPR_REG.LCCSCLOF.LCCSCLOF1.bit.LCCSCLOF_3	= sprCsprLowC->of3;
	IO_CNR(ch)->OTF_CSPR_REG.LCCSCLOF.LCCSCLOF2.bit.LCCSCLOF_4	= sprCsprLowC->of4;
	IO_CNR(ch)->OTF_CSPR_REG.LCCSCLOF.LCCSCLOF2.bit.LCCSCLOF_5	= sprCsprLowC->of5;

	// write signed data
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.LCCSCLGA.LCCSCLGA1,
			union io_cnr_cspr_reg_lccsclga_1, LCCSCLGA_0, sprCsprLowC->gain0 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.LCCSCLGA.LCCSCLGA1,
			union io_cnr_cspr_reg_lccsclga_1, LCCSCLGA_1, sprCsprLowC->gain1 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.LCCSCLGA.LCCSCLGA1,
			union io_cnr_cspr_reg_lccsclga_1, LCCSCLGA_2, sprCsprLowC->gain2 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.LCCSCLGA.LCCSCLGA1,
			union io_cnr_cspr_reg_lccsclga_1, LCCSCLGA_3, sprCsprLowC->gain3 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.LCCSCLGA.LCCSCLGA2,
			union io_cnr_cspr_reg_lccsclga_2, LCCSCLGA_4, sprCsprLowC->gain4 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.LCCSCLGA.LCCSCLGA2,
			union io_cnr_cspr_reg_lccsclga_2, LCCSCLGA_5, sprCsprLowC->gain5 );

	im_cnrone_off_pclk(ch);
	ImCnr_DSB();
	return D_DDIM_OK;
}

/*
Set SPR CbCr table for Low frequency CbCr
*/
INT32 im_cnrtwo_ofl_set_cspr_low_cc_c_table(ImCnrtwo *self, UCHAR ch, const ImCnrTable* const sprCsprLowC )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrtwo_ofl_set_cspr_low_cc_c_table() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( sprCsprLowC == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrtwo_ofl_set_cspr_low_cc_c_table() Parameter is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	ImCnr_DSB();

	IO_CNR(ch)->OFL_CSPR_REG.LCSSCLBD.LCSSCLBD1.bit.LCSSCLBD_1	= sprCsprLowC->bd1;
	IO_CNR(ch)->OFL_CSPR_REG.LCSSCLBD.LCSSCLBD1.bit.LCSSCLBD_2	= sprCsprLowC->bd2;
	IO_CNR(ch)->OFL_CSPR_REG.LCSSCLBD.LCSSCLBD1.bit.LCSSCLBD_3	= sprCsprLowC->bd3;
	IO_CNR(ch)->OFL_CSPR_REG.LCSSCLBD.LCSSCLBD1.bit.LCSSCLBD_4	= sprCsprLowC->bd4;
	IO_CNR(ch)->OFL_CSPR_REG.LCSSCLBD.LCSSCLBD2.bit.LCSSCLBD_5	= sprCsprLowC->bd5;
	IO_CNR(ch)->OFL_CSPR_REG.LCSSCLOF.LCSSCLOF1.bit.LCSSCLOF_0	= sprCsprLowC->of0;
	IO_CNR(ch)->OFL_CSPR_REG.LCSSCLOF.LCSSCLOF1.bit.LCSSCLOF_1	= sprCsprLowC->of1;
	IO_CNR(ch)->OFL_CSPR_REG.LCSSCLOF.LCSSCLOF1.bit.LCSSCLOF_2	= sprCsprLowC->of2;
	IO_CNR(ch)->OFL_CSPR_REG.LCSSCLOF.LCSSCLOF1.bit.LCSSCLOF_3	= sprCsprLowC->of3;
	IO_CNR(ch)->OFL_CSPR_REG.LCSSCLOF.LCSSCLOF2.bit.LCSSCLOF_4	= sprCsprLowC->of4;
	IO_CNR(ch)->OFL_CSPR_REG.LCSSCLOF.LCSSCLOF2.bit.LCSSCLOF_5	= sprCsprLowC->of5;

	// write signed data
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.LCSSCLGA.LCSSCLGA1,
			union io_cnr_cspr_reg_lcssclga_1, LCSSCLGA_0, sprCsprLowC->gain0 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.LCSSCLGA.LCSSCLGA1,
			union io_cnr_cspr_reg_lcssclga_1, LCSSCLGA_1, sprCsprLowC->gain1 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.LCSSCLGA.LCSSCLGA1,
			union io_cnr_cspr_reg_lcssclga_1, LCSSCLGA_2, sprCsprLowC->gain2 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.LCSSCLGA.LCSSCLGA1,
			union io_cnr_cspr_reg_lcssclga_1, LCSSCLGA_3, sprCsprLowC->gain3 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.LCSSCLGA.LCSSCLGA2,
			union io_cnr_cspr_reg_lcssclga_2, LCSSCLGA_4, sprCsprLowC->gain4 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.LCSSCLGA.LCSSCLGA2,
			union io_cnr_cspr_reg_lcssclga_2, LCSSCLGA_5, sprCsprLowC->gain5 );

	im_cnrone_off_pclk(ch);
	ImCnr_DSB();
	return D_DDIM_OK;
}

/*
Set SPR CbCr table for Low frequency CbCr
*/
INT32 im_cnrtwo_otf_set_cspr_low_cc_c_table(ImCnrtwo *self, UCHAR ch, const ImCnrTable* const sprCsprLowC )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrtwo_otf_set_cspr_low_cc_c_table() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( sprCsprLowC == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrtwo_otf_set_cspr_low_cc_c_table() Parameter is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	ImCnr_DSB();

	IO_CNR(ch)->OTF_CSPR_REG.LCSSCLBD.LCSSCLBD1.bit.LCSSCLBD_1	= sprCsprLowC->bd1;
	IO_CNR(ch)->OTF_CSPR_REG.LCSSCLBD.LCSSCLBD1.bit.LCSSCLBD_2	= sprCsprLowC->bd2;
	IO_CNR(ch)->OTF_CSPR_REG.LCSSCLBD.LCSSCLBD1.bit.LCSSCLBD_3	= sprCsprLowC->bd3;
	IO_CNR(ch)->OTF_CSPR_REG.LCSSCLBD.LCSSCLBD1.bit.LCSSCLBD_4	= sprCsprLowC->bd4;
	IO_CNR(ch)->OTF_CSPR_REG.LCSSCLBD.LCSSCLBD2.bit.LCSSCLBD_5	= sprCsprLowC->bd5;
	IO_CNR(ch)->OTF_CSPR_REG.LCSSCLOF.LCSSCLOF1.bit.LCSSCLOF_0	= sprCsprLowC->of0;
	IO_CNR(ch)->OTF_CSPR_REG.LCSSCLOF.LCSSCLOF1.bit.LCSSCLOF_1	= sprCsprLowC->of1;
	IO_CNR(ch)->OTF_CSPR_REG.LCSSCLOF.LCSSCLOF1.bit.LCSSCLOF_2	= sprCsprLowC->of2;
	IO_CNR(ch)->OTF_CSPR_REG.LCSSCLOF.LCSSCLOF1.bit.LCSSCLOF_3	= sprCsprLowC->of3;
	IO_CNR(ch)->OTF_CSPR_REG.LCSSCLOF.LCSSCLOF2.bit.LCSSCLOF_4	= sprCsprLowC->of4;
	IO_CNR(ch)->OTF_CSPR_REG.LCSSCLOF.LCSSCLOF2.bit.LCSSCLOF_5	= sprCsprLowC->of5;

	// write signed data
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.LCSSCLGA.LCSSCLGA1,
			union io_cnr_cspr_reg_lcssclga_1, LCSSCLGA_0, sprCsprLowC->gain0 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.LCSSCLGA.LCSSCLGA1,
			union io_cnr_cspr_reg_lcssclga_1, LCSSCLGA_1, sprCsprLowC->gain1 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.LCSSCLGA.LCSSCLGA1,
			union io_cnr_cspr_reg_lcssclga_1, LCSSCLGA_2, sprCsprLowC->gain2 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.LCSSCLGA.LCSSCLGA1,
			union io_cnr_cspr_reg_lcssclga_1, LCSSCLGA_3, sprCsprLowC->gain3 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.LCSSCLGA.LCSSCLGA2,
			union io_cnr_cspr_reg_lcssclga_2, LCSSCLGA_4, sprCsprLowC->gain4 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.LCSSCLGA.LCSSCLGA2,
			union io_cnr_cspr_reg_lcssclga_2, LCSSCLGA_5, sprCsprLowC->gain5 );

	im_cnrone_off_pclk(ch);
	ImCnr_DSB();

	return D_DDIM_OK;
}

/*
Set SPR Edge for CbcCr for Off Line
*/
INT32 im_cnrtwo_ofl_set_cspr_edge_table(ImCnrtwo *self, UCHAR ch, const ImCnrTable* const sprCsprEdge )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrtwo_ofl_set_cspr_edge_table() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( sprCsprEdge == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrtwo_ofl_set_cspr_edge_table() Parameter is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	ImCnr_DSB();

	IO_CNR(ch)->OFL_CSPR_REG.CESCLBD.CESCLBD1.bit.CESCLBD_1	= sprCsprEdge->bd1;
	IO_CNR(ch)->OFL_CSPR_REG.CESCLBD.CESCLBD1.bit.CESCLBD_2	= sprCsprEdge->bd2;
	IO_CNR(ch)->OFL_CSPR_REG.CESCLBD.CESCLBD1.bit.CESCLBD_3	= sprCsprEdge->bd3;
	IO_CNR(ch)->OFL_CSPR_REG.CESCLBD.CESCLBD1.bit.CESCLBD_4	= sprCsprEdge->bd4;
	IO_CNR(ch)->OFL_CSPR_REG.CESCLBD.CESCLBD2.bit.CESCLBD_5	= sprCsprEdge->bd5;
	IO_CNR(ch)->OFL_CSPR_REG.CESCLOF.CESCLOF1.bit.CESCLOF_0	= sprCsprEdge->of0;
	IO_CNR(ch)->OFL_CSPR_REG.CESCLOF.CESCLOF1.bit.CESCLOF_1	= sprCsprEdge->of1;
	IO_CNR(ch)->OFL_CSPR_REG.CESCLOF.CESCLOF1.bit.CESCLOF_2	= sprCsprEdge->of2;
	IO_CNR(ch)->OFL_CSPR_REG.CESCLOF.CESCLOF1.bit.CESCLOF_3	= sprCsprEdge->of3;
	IO_CNR(ch)->OFL_CSPR_REG.CESCLOF.CESCLOF2.bit.CESCLOF_4	= sprCsprEdge->of4;
	IO_CNR(ch)->OFL_CSPR_REG.CESCLOF.CESCLOF2.bit.CESCLOF_5	= sprCsprEdge->of5;

	// write signed data
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.CESCLGA.CESCLGA1,
			union io_cnr_cspr_reg_cesclga_1, CESCLGA_0, sprCsprEdge->gain0 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.CESCLGA.CESCLGA1,
			union io_cnr_cspr_reg_cesclga_1, CESCLGA_1, sprCsprEdge->gain1 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.CESCLGA.CESCLGA1,
			union io_cnr_cspr_reg_cesclga_1, CESCLGA_2, sprCsprEdge->gain2 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.CESCLGA.CESCLGA1,
			union io_cnr_cspr_reg_cesclga_1, CESCLGA_3, sprCsprEdge->gain3 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.CESCLGA.CESCLGA2,
			union io_cnr_cspr_reg_cesclga_2, CESCLGA_4, sprCsprEdge->gain4 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.CESCLGA.CESCLGA2,
			union io_cnr_cspr_reg_cesclga_2, CESCLGA_5, sprCsprEdge->gain5 );

	im_cnrone_off_pclk(ch);
	ImCnr_DSB();

	return D_DDIM_OK;
}

/*
Set SPR Edge for CbcCr for Off Line
*/
INT32 im_cnrtwo_otf_set_cspr_edge_table(ImCnrtwo *self, UCHAR ch, const ImCnrTable* const sprCsprEdge )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrtwo_otf_set_cspr_edge_table() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( sprCsprEdge == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrtwo_otf_set_cspr_edge_table() Parameter is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	ImCnr_DSB();

	IO_CNR(ch)->OTF_CSPR_REG.CESCLBD.CESCLBD1.bit.CESCLBD_1	= sprCsprEdge->bd1;
	IO_CNR(ch)->OTF_CSPR_REG.CESCLBD.CESCLBD1.bit.CESCLBD_2	= sprCsprEdge->bd2;
	IO_CNR(ch)->OTF_CSPR_REG.CESCLBD.CESCLBD1.bit.CESCLBD_3	= sprCsprEdge->bd3;
	IO_CNR(ch)->OTF_CSPR_REG.CESCLBD.CESCLBD1.bit.CESCLBD_4	= sprCsprEdge->bd4;
	IO_CNR(ch)->OTF_CSPR_REG.CESCLBD.CESCLBD2.bit.CESCLBD_5	= sprCsprEdge->bd5;
	IO_CNR(ch)->OTF_CSPR_REG.CESCLOF.CESCLOF1.bit.CESCLOF_0	= sprCsprEdge->of0;
	IO_CNR(ch)->OTF_CSPR_REG.CESCLOF.CESCLOF1.bit.CESCLOF_1	= sprCsprEdge->of1;
	IO_CNR(ch)->OTF_CSPR_REG.CESCLOF.CESCLOF1.bit.CESCLOF_2	= sprCsprEdge->of2;
	IO_CNR(ch)->OTF_CSPR_REG.CESCLOF.CESCLOF1.bit.CESCLOF_3	= sprCsprEdge->of3;
	IO_CNR(ch)->OTF_CSPR_REG.CESCLOF.CESCLOF2.bit.CESCLOF_4	= sprCsprEdge->of4;
	IO_CNR(ch)->OTF_CSPR_REG.CESCLOF.CESCLOF2.bit.CESCLOF_5	= sprCsprEdge->of5;

	// write signed data
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.CESCLGA.CESCLGA1,
			union io_cnr_cspr_reg_cesclga_1, CESCLGA_0, sprCsprEdge->gain0 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.CESCLGA.CESCLGA1,
			union io_cnr_cspr_reg_cesclga_1, CESCLGA_1, sprCsprEdge->gain1 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.CESCLGA.CESCLGA1,
			union io_cnr_cspr_reg_cesclga_1, CESCLGA_2, sprCsprEdge->gain2 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.CESCLGA.CESCLGA1,
			union io_cnr_cspr_reg_cesclga_1, CESCLGA_3, sprCsprEdge->gain3 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.CESCLGA.CESCLGA2,
			union io_cnr_cspr_reg_cesclga_2, CESCLGA_4, sprCsprEdge->gain4 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.CESCLGA.CESCLGA2,
			union io_cnr_cspr_reg_cesclga_2, CESCLGA_5, sprCsprEdge->gain5 );

	im_cnrone_off_pclk(ch);
	ImCnr_DSB();

	return D_DDIM_OK;
}

/*
Set SPR Hue specified for CbcCr for Off Line
*/
INT32 im_cnrtwo_ofl_set_cspr_hue_specified_table(ImCnrtwo *self, UCHAR ch,
		const ImCnrHueSpecTable* const sprCsprHue )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrtwo_ofl_set_cspr_hue_specified_table() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( sprCsprHue == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrtwo_ofl_set_cspr_hue_specified_table() Parameter is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	ImCnr_DSB();

	// write signed data
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.CPHPT,
			union io_cnr_cspr_reg_cphpt, CDCB, sprCsprHue->cdCb );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.CPHPT,
			union io_cnr_cspr_reg_cphpt, CDCR, sprCsprHue->cdCr );

	IO_CNR(ch)->OFL_CSPR_REG.CPHPTK.bit.KCB	= sprCsprHue->kCb;
	IO_CNR(ch)->OFL_CSPR_REG.CPHPTK.bit.KCR	= sprCsprHue->kCr;

	IO_CNR(ch)->OFL_CSPR_REG.CDSCLBD.CDSCLBD1.bit.CDSCLBD_1	= sprCsprHue->bd1;
	IO_CNR(ch)->OFL_CSPR_REG.CDSCLBD.CDSCLBD1.bit.CDSCLBD_2	= sprCsprHue->bd2;
	IO_CNR(ch)->OFL_CSPR_REG.CDSCLBD.CDSCLBD2.bit.CDSCLBD_3	= sprCsprHue->bd3;
	IO_CNR(ch)->OFL_CSPR_REG.CDSCLBD.CDSCLBD2.bit.CDSCLBD_4	= sprCsprHue->bd4;
	IO_CNR(ch)->OFL_CSPR_REG.CDSCLBD.CDSCLBD3.bit.CDSCLBD_5	= sprCsprHue->bd5;
	IO_CNR(ch)->OFL_CSPR_REG.CDSCLOF.CDSCLOF1.bit.CDSCLOF_0	= sprCsprHue->of0;
	IO_CNR(ch)->OFL_CSPR_REG.CDSCLOF.CDSCLOF1.bit.CDSCLOF_1	= sprCsprHue->of1;
	IO_CNR(ch)->OFL_CSPR_REG.CDSCLOF.CDSCLOF2.bit.CDSCLOF_2	= sprCsprHue->of2;
	IO_CNR(ch)->OFL_CSPR_REG.CDSCLOF.CDSCLOF2.bit.CDSCLOF_3	= sprCsprHue->of3;
	IO_CNR(ch)->OFL_CSPR_REG.CDSCLOF.CDSCLOF3.bit.CDSCLOF_4	= sprCsprHue->of4;
	IO_CNR(ch)->OFL_CSPR_REG.CDSCLOF.CDSCLOF3.bit.CDSCLOF_5	= sprCsprHue->of5;

	// write signed data
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.CDSCLGA.CDSCLGA1,
			union io_cnr_cspr_reg_cdsclga_1, CDSCLGA_0, sprCsprHue->gain0 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.CDSCLGA.CDSCLGA1,
			union io_cnr_cspr_reg_cdsclga_1, CDSCLGA_1, sprCsprHue->gain1 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.CDSCLGA.CDSCLGA2,
			union io_cnr_cspr_reg_cdsclga_2, CDSCLGA_2, sprCsprHue->gain2 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.CDSCLGA.CDSCLGA2,
			union io_cnr_cspr_reg_cdsclga_2, CDSCLGA_3, sprCsprHue->gain3 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.CDSCLGA.CDSCLGA3,
			union io_cnr_cspr_reg_cdsclga_3, CDSCLGA_4, sprCsprHue->gain4 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.CDSCLGA.CDSCLGA3,
			union io_cnr_cspr_reg_cdsclga_3, CDSCLGA_5, sprCsprHue->gain5 );

	im_cnrone_off_pclk(ch);
	ImCnr_DSB();

	return D_DDIM_OK;
}

/*
Set SPR Hue specified for CbcCr for Off Line
*/
INT32 im_cnrtwo_otf_set_cspr_hue_specified_table(ImCnrtwo *self, UCHAR ch,
		const ImCnrHueSpecTable* const sprCsprHue )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrtwo_otf_set_cspr_hue_specified_table() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( sprCsprHue == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrtwo_otf_set_cspr_hue_specified_table() Parameter is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	ImCnr_DSB();

	// write signed data
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.CPHPT,
			union io_cnr_cspr_reg_cphpt, CDCB, sprCsprHue->cdCb );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.CPHPT,
			union io_cnr_cspr_reg_cphpt, CDCR, sprCsprHue->cdCr );

	IO_CNR(ch)->OTF_CSPR_REG.CPHPTK.bit.KCB	= sprCsprHue->kCb;
	IO_CNR(ch)->OTF_CSPR_REG.CPHPTK.bit.KCR	= sprCsprHue->kCr;

	IO_CNR(ch)->OTF_CSPR_REG.CDSCLBD.CDSCLBD1.bit.CDSCLBD_1	= sprCsprHue->bd1;
	IO_CNR(ch)->OTF_CSPR_REG.CDSCLBD.CDSCLBD1.bit.CDSCLBD_2	= sprCsprHue->bd2;
	IO_CNR(ch)->OTF_CSPR_REG.CDSCLBD.CDSCLBD2.bit.CDSCLBD_3	= sprCsprHue->bd3;
	IO_CNR(ch)->OTF_CSPR_REG.CDSCLBD.CDSCLBD2.bit.CDSCLBD_4	= sprCsprHue->bd4;
	IO_CNR(ch)->OTF_CSPR_REG.CDSCLBD.CDSCLBD3.bit.CDSCLBD_5	= sprCsprHue->bd5;
	IO_CNR(ch)->OTF_CSPR_REG.CDSCLOF.CDSCLOF1.bit.CDSCLOF_0	= sprCsprHue->of0;
	IO_CNR(ch)->OTF_CSPR_REG.CDSCLOF.CDSCLOF1.bit.CDSCLOF_1	= sprCsprHue->of1;
	IO_CNR(ch)->OTF_CSPR_REG.CDSCLOF.CDSCLOF2.bit.CDSCLOF_2	= sprCsprHue->of2;
	IO_CNR(ch)->OTF_CSPR_REG.CDSCLOF.CDSCLOF2.bit.CDSCLOF_3	= sprCsprHue->of3;
	IO_CNR(ch)->OTF_CSPR_REG.CDSCLOF.CDSCLOF3.bit.CDSCLOF_4	= sprCsprHue->of4;
	IO_CNR(ch)->OTF_CSPR_REG.CDSCLOF.CDSCLOF3.bit.CDSCLOF_5	= sprCsprHue->of5;

	// write signed data
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.CDSCLGA.CDSCLGA1,
			union io_cnr_cspr_reg_cdsclga_1, CDSCLGA_0, sprCsprHue->gain0 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.CDSCLGA.CDSCLGA1,
			union io_cnr_cspr_reg_cdsclga_1, CDSCLGA_1, sprCsprHue->gain1 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.CDSCLGA.CDSCLGA2,
			union io_cnr_cspr_reg_cdsclga_2, CDSCLGA_2, sprCsprHue->gain2 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.CDSCLGA.CDSCLGA2,
			union io_cnr_cspr_reg_cdsclga_2, CDSCLGA_3, sprCsprHue->gain3 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.CDSCLGA.CDSCLGA3,
			union io_cnr_cspr_reg_cdsclga_3, CDSCLGA_4, sprCsprHue->gain4 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.CDSCLGA.CDSCLGA3,
			union io_cnr_cspr_reg_cdsclga_3, CDSCLGA_5, sprCsprHue->gain5 );

	im_cnrone_off_pclk(ch);
	ImCnr_DSB();

	return D_DDIM_OK;
}




/*PUBLIC*/
ImCnrtwo* im_cnrtwo_new(void)
{
	ImCnrtwo *self = g_object_new(IM_TYPE_CNRTWO, NULL);
	return self;
}






