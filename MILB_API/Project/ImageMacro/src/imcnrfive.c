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
#include "imcnrfive.h"


G_DEFINE_TYPE(ImCnrfive, im_cnrfive, G_TYPE_OBJECT);
#define IM_CNRFIVE_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IM_TYPE_CNRFIVE, ImCnrfivePrivate));


struct _ImCnrfivePrivate{

};


/*DECLS*/
static void 					dispose_od(GObject *object);
static void 					finalize_od(GObject *object);
#ifdef CO_DDIM_UTILITY_USE
static VOID imCnrConvertRdmaCsprLowCcYTable(const ImCnrTable* csprLowCcY,
		ImCnroneRdmaDataCsprLowCcYTbl* rdmaLowCcYTable);
static VOID imCnrConvertRdmaCsprLowCcCTable(const ImCnrTable* csprLowCcC,
		ImCnroneRdmaDataCsprLowCcCTbl* rdmaLowCcCTable);
static VOID imCnrConvertRdmaCsprEdgeTable(const ImCnrTable* csprEdge,
		ImCnroneRdmaDataCsprEdgeTbl* rdmaEdgeTable);
static VOID imCnrConvertRdmaCsprHueTable(const ImCnrHueSpecTable* csprHue,
		ImCnroneRdmaDataCsprHueTbl* rdmaHueTable);
static VOID imCnrConvertRdmaCsprSprsCc(const ImCnrCtrlCcSrcDst* sprsCtrl,
		ImCnrRdmaDataSprsCcTbl* rdmaSprsCtrl);
static VOID imCnrConvertRdmaCsprSprdCc(const ImCnrCtrlCcSrcDst* sprdCtrl,
		ImCnroneRdmaDataSprdCcTbl* rdmaSprdCtrl);
static VOID imCnrConvertRdmaCsprLowYTable(const ImCnrTable* sprCsprLowY,
		ImCnrRdmaDataCsprLowYTbl* rdmaCsprLowYTable);
#endif


/*IMPL*/
static void im_cnrfive_class_init(ImCnrfiveClass *klass)
{
	g_type_class_add_private(klass, sizeof(ImCnrfivePrivate));
}

static void im_cnrfive_init(ImCnrfive *self)
{
	ImCnrfivePrivate *priv = IM_CNRFIVE_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
	ImCnrfivePrivate *self = IM_CNRFIVE_GET_PRIVATE(object);
}

static void finalize_od(GObject *object)
{
	ImCnrfivePrivate *self = IM_CNRFIVE_GET_PRIVATE(object);
}

#ifdef CO_DDIM_UTILITY_USE
/*
Convert ImCnrTable to ImCnrRdmaAddrCsprLowCcYTbl
*/
static VOID imCnrConvertRdmaCsprLowCcYTable( const ImCnrTable* csprLowCcY,
		ImCnroneRdmaDataCsprLowCcYTbl* rdmaLowCcYTable )
{
	rdmaLowCcYTable->LCCSCLBD.LCCSCLBD1.bit.LCCSCLBD_1	= csprLowCcY->bd1;
	rdmaLowCcYTable->LCCSCLBD.LCCSCLBD1.bit.LCCSCLBD_2	= csprLowCcY->bd2;
	rdmaLowCcYTable->LCCSCLBD.LCCSCLBD1.bit.LCCSCLBD_3	= csprLowCcY->bd3;
	rdmaLowCcYTable->LCCSCLBD.LCCSCLBD1.bit.LCCSCLBD_4	= csprLowCcY->bd4;
	rdmaLowCcYTable->LCCSCLBD.LCCSCLBD2.bit.LCCSCLBD_5	= csprLowCcY->bd5;
	rdmaLowCcYTable->LCCSCLOF.LCCSCLOF1.bit.LCCSCLOF_0	= csprLowCcY->of0;
	rdmaLowCcYTable->LCCSCLOF.LCCSCLOF1.bit.LCCSCLOF_1	= csprLowCcY->of1;
	rdmaLowCcYTable->LCCSCLOF.LCCSCLOF1.bit.LCCSCLOF_2	= csprLowCcY->of2;
	rdmaLowCcYTable->LCCSCLOF.LCCSCLOF1.bit.LCCSCLOF_3	= csprLowCcY->of3;
	rdmaLowCcYTable->LCCSCLOF.LCCSCLOF2.bit.LCCSCLOF_4	= csprLowCcY->of4;
	rdmaLowCcYTable->LCCSCLOF.LCCSCLOF2.bit.LCCSCLOF_5	= csprLowCcY->of5;
	// write signed data
	im_cnr_set_reg_signed( rdmaLowCcYTable->LCCSCLGA.LCCSCLGA1,
			union io_cnr_cspr_reg_lccsclga_1, LCCSCLGA_0, csprLowCcY->gain0 );
	im_cnr_set_reg_signed( rdmaLowCcYTable->LCCSCLGA.LCCSCLGA1,
			union io_cnr_cspr_reg_lccsclga_1, LCCSCLGA_1, csprLowCcY->gain1 );
	im_cnr_set_reg_signed( rdmaLowCcYTable->LCCSCLGA.LCCSCLGA1,
			union io_cnr_cspr_reg_lccsclga_1, LCCSCLGA_2, csprLowCcY->gain2 );
	im_cnr_set_reg_signed( rdmaLowCcYTable->LCCSCLGA.LCCSCLGA1,
			union io_cnr_cspr_reg_lccsclga_1, LCCSCLGA_3, csprLowCcY->gain3 );
	im_cnr_set_reg_signed( rdmaLowCcYTable->LCCSCLGA.LCCSCLGA2,
			union io_cnr_cspr_reg_lccsclga_2, LCCSCLGA_4, csprLowCcY->gain4 );
	im_cnr_set_reg_signed( rdmaLowCcYTable->LCCSCLGA.LCCSCLGA2,
			union io_cnr_cspr_reg_lccsclga_2, LCCSCLGA_5, csprLowCcY->gain5 );
}
/*
Convert ImCnrTable to ImCnroneRdmaAddrCsprLowCcCTbl
*/
static VOID imCnrConvertRdmaCsprLowCcCTable( const ImCnrTable* csprLowCcC,
		ImCnroneRdmaDataCsprLowCcCTbl* rdmaLowCcCTable )
{
	rdmaLowCcCTable->LCSSCLBD.LCSSCLBD1.bit.LCSSCLBD_1	= csprLowCcC->bd1;
	rdmaLowCcCTable->LCSSCLBD.LCSSCLBD1.bit.LCSSCLBD_2	= csprLowCcC->bd2;
	rdmaLowCcCTable->LCSSCLBD.LCSSCLBD1.bit.LCSSCLBD_3	= csprLowCcC->bd3;
	rdmaLowCcCTable->LCSSCLBD.LCSSCLBD1.bit.LCSSCLBD_4	= csprLowCcC->bd4;
	rdmaLowCcCTable->LCSSCLBD.LCSSCLBD2.bit.LCSSCLBD_5	= csprLowCcC->bd5;
	rdmaLowCcCTable->LCSSCLOF.LCSSCLOF1.bit.LCSSCLOF_0	= csprLowCcC->of0;
	rdmaLowCcCTable->LCSSCLOF.LCSSCLOF1.bit.LCSSCLOF_1	= csprLowCcC->of1;
	rdmaLowCcCTable->LCSSCLOF.LCSSCLOF1.bit.LCSSCLOF_2	= csprLowCcC->of2;
	rdmaLowCcCTable->LCSSCLOF.LCSSCLOF1.bit.LCSSCLOF_3	= csprLowCcC->of3;
	rdmaLowCcCTable->LCSSCLOF.LCSSCLOF2.bit.LCSSCLOF_4	= csprLowCcC->of4;
	rdmaLowCcCTable->LCSSCLOF.LCSSCLOF2.bit.LCSSCLOF_5	= csprLowCcC->of5;
	// write signed data
	im_cnr_set_reg_signed( rdmaLowCcCTable->LCSSCLGA.LCSSCLGA1,
			union io_cnr_cspr_reg_lcssclga_1, LCSSCLGA_0, csprLowCcC->gain0 );
	im_cnr_set_reg_signed( rdmaLowCcCTable->LCSSCLGA.LCSSCLGA1,
			union io_cnr_cspr_reg_lcssclga_1, LCSSCLGA_1, csprLowCcC->gain1 );
	im_cnr_set_reg_signed( rdmaLowCcCTable->LCSSCLGA.LCSSCLGA1,
			union io_cnr_cspr_reg_lcssclga_1, LCSSCLGA_2, csprLowCcC->gain2 );
	im_cnr_set_reg_signed( rdmaLowCcCTable->LCSSCLGA.LCSSCLGA1,
			union io_cnr_cspr_reg_lcssclga_1, LCSSCLGA_3, csprLowCcC->gain3 );
	im_cnr_set_reg_signed( rdmaLowCcCTable->LCSSCLGA.LCSSCLGA2,
			union io_cnr_cspr_reg_lcssclga_2, LCSSCLGA_4, csprLowCcC->gain4 );
	im_cnr_set_reg_signed( rdmaLowCcCTable->LCSSCLGA.LCSSCLGA2,
			union io_cnr_cspr_reg_lcssclga_2, LCSSCLGA_5, csprLowCcC->gain5 );
}

/*
Convert ImCnrTable to ImCnroneRdmaAddrCsprEdgeTbl
*/
static VOID imCnrConvertRdmaCsprEdgeTable( const ImCnrTable* csprEdge,
		ImCnroneRdmaDataCsprEdgeTbl* rdmaEdgeTable )
{
	rdmaEdgeTable->CESCLBD.CESCLBD1.bit.CESCLBD_1	= csprEdge->bd1;
	rdmaEdgeTable->CESCLBD.CESCLBD1.bit.CESCLBD_2	= csprEdge->bd2;
	rdmaEdgeTable->CESCLBD.CESCLBD1.bit.CESCLBD_3	= csprEdge->bd3;
	rdmaEdgeTable->CESCLBD.CESCLBD1.bit.CESCLBD_4	= csprEdge->bd4;
	rdmaEdgeTable->CESCLBD.CESCLBD2.bit.CESCLBD_5	= csprEdge->bd5;
	rdmaEdgeTable->CESCLOF.CESCLOF1.bit.CESCLOF_0	= csprEdge->of0;
	rdmaEdgeTable->CESCLOF.CESCLOF1.bit.CESCLOF_1	= csprEdge->of1;
	rdmaEdgeTable->CESCLOF.CESCLOF1.bit.CESCLOF_2	= csprEdge->of2;
	rdmaEdgeTable->CESCLOF.CESCLOF1.bit.CESCLOF_3	= csprEdge->of3;
	rdmaEdgeTable->CESCLOF.CESCLOF2.bit.CESCLOF_4	= csprEdge->of4;
	rdmaEdgeTable->CESCLOF.CESCLOF2.bit.CESCLOF_5	= csprEdge->of5;
	// write signed data
	im_cnr_set_reg_signed( rdmaEdgeTable->CESCLGA.CESCLGA1,
			union io_cnr_cspr_reg_cesclga_1, CESCLGA_0, csprEdge->gain0 );
	im_cnr_set_reg_signed( rdmaEdgeTable->CESCLGA.CESCLGA1,
			union io_cnr_cspr_reg_cesclga_1, CESCLGA_1, csprEdge->gain1 );
	im_cnr_set_reg_signed( rdmaEdgeTable->CESCLGA.CESCLGA1,
			union io_cnr_cspr_reg_cesclga_1, CESCLGA_2, csprEdge->gain2 );
	im_cnr_set_reg_signed( rdmaEdgeTable->CESCLGA.CESCLGA1,
			union io_cnr_cspr_reg_cesclga_1, CESCLGA_3, csprEdge->gain3 );
	im_cnr_set_reg_signed( rdmaEdgeTable->CESCLGA.CESCLGA2,
			union io_cnr_cspr_reg_cesclga_2, CESCLGA_4, csprEdge->gain4 );
	im_cnr_set_reg_signed( rdmaEdgeTable->CESCLGA.CESCLGA2,
			union io_cnr_cspr_reg_cesclga_2, CESCLGA_5, csprEdge->gain5 );
}

/*
Convert ImCnrHueSpecTable to ImCnroneRdmaAddrCsprHueTbl
*/
static VOID imCnrConvertRdmaCsprHueTable( const ImCnrHueSpecTable* csprHue,
		ImCnroneRdmaDataCsprHueTbl* rdmaHueTable )
{
	// write signed data
	im_cnr_set_reg_signed( rdmaHueTable->CPHPT, union io_cnr_cspr_reg_cphpt, CDCB, csprHue->cd_cb );
	im_cnr_set_reg_signed( rdmaHueTable->CPHPT, union io_cnr_cspr_reg_cphpt, CDCR, csprHue->cd_cr );

	rdmaHueTable->CPHPTK.bit.KCB	= csprHue->k_cb;
	rdmaHueTable->CPHPTK.bit.KCR	= csprHue->k_cr;

	rdmaHueTable->CDSCLBD.CDSCLBD1.bit.CDSCLBD_1	= csprHue->bd1;
	rdmaHueTable->CDSCLBD.CDSCLBD1.bit.CDSCLBD_2	= csprHue->bd2;
	rdmaHueTable->CDSCLBD.CDSCLBD2.bit.CDSCLBD_3	= csprHue->bd3;
	rdmaHueTable->CDSCLBD.CDSCLBD2.bit.CDSCLBD_4	= csprHue->bd4;
	rdmaHueTable->CDSCLBD.CDSCLBD3.bit.CDSCLBD_5	= csprHue->bd5;
	rdmaHueTable->CDSCLOF.CDSCLOF1.bit.CDSCLOF_0	= csprHue->of0;
	rdmaHueTable->CDSCLOF.CDSCLOF1.bit.CDSCLOF_1	= csprHue->of1;
	rdmaHueTable->CDSCLOF.CDSCLOF2.bit.CDSCLOF_2	= csprHue->of2;
	rdmaHueTable->CDSCLOF.CDSCLOF2.bit.CDSCLOF_3	= csprHue->of3;
	rdmaHueTable->CDSCLOF.CDSCLOF3.bit.CDSCLOF_4	= csprHue->of4;
	rdmaHueTable->CDSCLOF.CDSCLOF3.bit.CDSCLOF_5	= csprHue->of5;
	// write signed data
	im_cnr_set_reg_signed( rdmaHueTable->CDSCLGA.CDSCLGA1,
			union io_cnr_cspr_reg_cdsclga_1, CDSCLGA_0, csprHue->gain0 );
	im_cnr_set_reg_signed( rdmaHueTable->CDSCLGA.CDSCLGA1,
			union io_cnr_cspr_reg_cdsclga_1, CDSCLGA_1, csprHue->gain1 );
	im_cnr_set_reg_signed( rdmaHueTable->CDSCLGA.CDSCLGA2,
			union io_cnr_cspr_reg_cdsclga_2, CDSCLGA_2, csprHue->gain2 );
	im_cnr_set_reg_signed( rdmaHueTable->CDSCLGA.CDSCLGA2,
			union io_cnr_cspr_reg_cdsclga_2, CDSCLGA_3, csprHue->gain3 );
	im_cnr_set_reg_signed( rdmaHueTable->CDSCLGA.CDSCLGA3,
			union io_cnr_cspr_reg_cdsclga_3, CDSCLGA_4, csprHue->gain4 );
	im_cnr_set_reg_signed( rdmaHueTable->CDSCLGA.CDSCLGA3,
			union io_cnr_cspr_reg_cdsclga_3, CDSCLGA_5, csprHue->gain5 );
}

/*
Convert ImCnrCtrlCcSrcDst to ImCnrRdmaDataSprsCcTbl
*/
static VOID imCnrConvertRdmaCsprSprsCc( const ImCnrCtrlCcSrcDst* sprsCtrl,
		ImCnrRdmaDataSprsCcTbl* rdmaSprsCtrl )
{
	rdmaSprsCtrl->SPRS.bit.SPRS = sprsCtrl->enable;
	// write signed data
	im_cnr_set_reg_signed( rdmaSprsCtrl->SPRSCBBD.SPRSCBBD1,
			union io_cnr_cspr_reg_sprscbbd_1, SPRSCBBD_1, sprsCtrl->cb_table.bd1 );
	im_cnr_set_reg_signed( rdmaSprsCtrl->SPRSCBBD.SPRSCBBD1,
			union io_cnr_cspr_reg_sprscbbd_1, SPRSCBBD_2, sprsCtrl->cb_table.bd2 );
	im_cnr_set_reg_signed( rdmaSprsCtrl->SPRSCBBD.SPRSCBBD1,
			union io_cnr_cspr_reg_sprscbbd_1, SPRSCBBD_3, sprsCtrl->cb_table.bd3 );
	im_cnr_set_reg_signed( rdmaSprsCtrl->SPRSCBBD.SPRSCBBD1,
			union io_cnr_cspr_reg_sprscbbd_1, SPRSCBBD_4, sprsCtrl->cb_table.bd4 );
	im_cnr_set_reg_signed( rdmaSprsCtrl->SPRSCBBD.SPRSCBBD2,
			union io_cnr_cspr_reg_sprscbbd_2, SPRSCBBD_5, sprsCtrl->cb_table.bd5 );
	im_cnr_set_reg_signed( rdmaSprsCtrl->SPRSCBOF.SPRSCBOF1,
			union io_cnr_cspr_reg_sprscbof_1, SPRSCBOF_0, sprsCtrl->cb_table.of0 );
	im_cnr_set_reg_signed( rdmaSprsCtrl->SPRSCBOF.SPRSCBOF1,
			union io_cnr_cspr_reg_sprscbof_1, SPRSCBOF_1, sprsCtrl->cb_table.of1 );
	im_cnr_set_reg_signed( rdmaSprsCtrl->SPRSCBOF.SPRSCBOF1,
			union io_cnr_cspr_reg_sprscbof_1, SPRSCBOF_2, sprsCtrl->cb_table.of2 );
	im_cnr_set_reg_signed( rdmaSprsCtrl->SPRSCBOF.SPRSCBOF1,
			union io_cnr_cspr_reg_sprscbof_1, SPRSCBOF_3, sprsCtrl->cb_table.of3 );
	im_cnr_set_reg_signed( rdmaSprsCtrl->SPRSCBOF.SPRSCBOF2,
			union io_cnr_cspr_reg_sprscbof_2, SPRSCBOF_4, sprsCtrl->cb_table.of4 );
	im_cnr_set_reg_signed( rdmaSprsCtrl->SPRSCBOF.SPRSCBOF2,
			union io_cnr_cspr_reg_sprscbof_2, SPRSCBOF_5, sprsCtrl->cb_table.of5 );
	im_cnr_set_reg_signed( rdmaSprsCtrl->SPRSCBGA.SPRSCBGA1,
			union io_cnr_cspr_reg_sprscbga_1, SPRSCBGA_0, sprsCtrl->cb_table.gain0 );
	im_cnr_set_reg_signed( rdmaSprsCtrl->SPRSCBGA.SPRSCBGA1,
			union io_cnr_cspr_reg_sprscbga_1, SPRSCBGA_1, sprsCtrl->cb_table.gain1 );
	im_cnr_set_reg_signed( rdmaSprsCtrl->SPRSCBGA.SPRSCBGA2,
			union io_cnr_cspr_reg_sprscbga_2, SPRSCBGA_2, sprsCtrl->cb_table.gain2 );
	im_cnr_set_reg_signed( rdmaSprsCtrl->SPRSCBGA.SPRSCBGA2,
			union io_cnr_cspr_reg_sprscbga_2, SPRSCBGA_3, sprsCtrl->cb_table.gain3 );
	im_cnr_set_reg_signed( rdmaSprsCtrl->SPRSCBGA.SPRSCBGA3,
			union io_cnr_cspr_reg_sprscbga_3, SPRSCBGA_4, sprsCtrl->cb_table.gain4 );
	im_cnr_set_reg_signed( rdmaSprsCtrl->SPRSCBGA.SPRSCBGA3,
			union io_cnr_cspr_reg_sprscbga_3, SPRSCBGA_5, sprsCtrl->cb_table.gain5 );

	im_cnr_set_reg_signed( rdmaSprsCtrl->SPRSCRBD.SPRSCRBD1,
			union io_cnr_cspr_reg_sprscrbd_1, SPRSCRBD_1, sprsCtrl->cr_table.bd1 );
	im_cnr_set_reg_signed( rdmaSprsCtrl->SPRSCRBD.SPRSCRBD1,
			union io_cnr_cspr_reg_sprscrbd_1, SPRSCRBD_2, sprsCtrl->cr_table.bd2 );
	im_cnr_set_reg_signed( rdmaSprsCtrl->SPRSCRBD.SPRSCRBD1,
			union io_cnr_cspr_reg_sprscrbd_1, SPRSCRBD_3, sprsCtrl->cr_table.bd3 );
	im_cnr_set_reg_signed( rdmaSprsCtrl->SPRSCRBD.SPRSCRBD1,
			union io_cnr_cspr_reg_sprscrbd_1, SPRSCRBD_4, sprsCtrl->cr_table.bd4 );
	im_cnr_set_reg_signed( rdmaSprsCtrl->SPRSCRBD.SPRSCRBD2,
			union io_cnr_cspr_reg_sprscrbd_2, SPRSCRBD_5, sprsCtrl->cr_table.bd5 );
	im_cnr_set_reg_signed( rdmaSprsCtrl->SPRSCROF.SPRSCROF1,
			union io_cnr_cspr_reg_sprscrof_1, SPRSCROF_0, sprsCtrl->cr_table.of0 );
	im_cnr_set_reg_signed( rdmaSprsCtrl->SPRSCROF.SPRSCROF1,
			union io_cnr_cspr_reg_sprscrof_1, SPRSCROF_1, sprsCtrl->cr_table.of1 );
	im_cnr_set_reg_signed( rdmaSprsCtrl->SPRSCROF.SPRSCROF1,
			union io_cnr_cspr_reg_sprscrof_1, SPRSCROF_2, sprsCtrl->cr_table.of2 );
	im_cnr_set_reg_signed( rdmaSprsCtrl->SPRSCROF.SPRSCROF1,
			union io_cnr_cspr_reg_sprscrof_1, SPRSCROF_3, sprsCtrl->cr_table.of3 );
	im_cnr_set_reg_signed( rdmaSprsCtrl->SPRSCROF.SPRSCROF2,
			union io_cnr_cspr_reg_sprscrof_2, SPRSCROF_4, sprsCtrl->cr_table.of4 );
	im_cnr_set_reg_signed( rdmaSprsCtrl->SPRSCROF.SPRSCROF2,
			union io_cnr_cspr_reg_sprscrof_2, SPRSCROF_5, sprsCtrl->cr_table.of5 );
	im_cnr_set_reg_signed( rdmaSprsCtrl->SPRSCRGA.SPRSCRGA1,
			union io_cnr_cspr_reg_sprscrga_1, SPRSCRGA_0, sprsCtrl->cr_table.gain0 );
	im_cnr_set_reg_signed( rdmaSprsCtrl->SPRSCRGA.SPRSCRGA1,
			union io_cnr_cspr_reg_sprscrga_1, SPRSCRGA_1, sprsCtrl->cr_table.gain1 );
	im_cnr_set_reg_signed( rdmaSprsCtrl->SPRSCRGA.SPRSCRGA2,
			union io_cnr_cspr_reg_sprscrga_2, SPRSCRGA_2, sprsCtrl->cr_table.gain2 );
	im_cnr_set_reg_signed( rdmaSprsCtrl->SPRSCRGA.SPRSCRGA2,
			union io_cnr_cspr_reg_sprscrga_2, SPRSCRGA_3, sprsCtrl->cr_table.gain3 );
	im_cnr_set_reg_signed( rdmaSprsCtrl->SPRSCRGA.SPRSCRGA3,
			union io_cnr_cspr_reg_sprscrga_3, SPRSCRGA_4, sprsCtrl->cr_table.gain4 );
	im_cnr_set_reg_signed( rdmaSprsCtrl->SPRSCRGA.SPRSCRGA3,
			union io_cnr_cspr_reg_sprscrga_3, SPRSCRGA_5, sprsCtrl->cr_table.gain5 );
}

/*
Convert ImCnrCtrlCcSrcDst to ImCnroneRdmaDataSprdCcTbl
*/
static VOID imCnrConvertRdmaCsprSprdCc( const ImCnrCtrlCcSrcDst* sprdCtrl,
		ImCnroneRdmaDataSprdCcTbl* rdmaSprdCtrl )
{
	rdmaSprdCtrl->SPRD.bit.SPRD = sprdCtrl->enable;
	// write signed data
	im_cnr_set_reg_signed( rdmaSprdCtrl->SPRDCBBD.SPRDCBBD1,
			union io_cnr_cspr_reg_sprdcbbd_1, SPRDCBBD_1, sprdCtrl->cb_table.bd1 );
	im_cnr_set_reg_signed( rdmaSprdCtrl->SPRDCBBD.SPRDCBBD1,
			union io_cnr_cspr_reg_sprdcbbd_1, SPRDCBBD_2, sprdCtrl->cb_table.bd2 );
	im_cnr_set_reg_signed( rdmaSprdCtrl->SPRDCBBD.SPRDCBBD1,
			union io_cnr_cspr_reg_sprdcbbd_1, SPRDCBBD_3, sprdCtrl->cb_table.bd3 );
	im_cnr_set_reg_signed( rdmaSprdCtrl->SPRDCBBD.SPRDCBBD1,
			union io_cnr_cspr_reg_sprdcbbd_1, SPRDCBBD_4, sprdCtrl->cb_table.bd4 );
	im_cnr_set_reg_signed( rdmaSprdCtrl->SPRDCBBD.SPRDCBBD2,
			union io_cnr_cspr_reg_sprdcbbd_2, SPRDCBBD_5, sprdCtrl->cb_table.bd5 );
	im_cnr_set_reg_signed( rdmaSprdCtrl->SPRDCBOF.SPRDCBOF1,
			union io_cnr_cspr_reg_sprdcbof_1, SPRDCBOF_0, sprdCtrl->cb_table.of0 );
	im_cnr_set_reg_signed( rdmaSprdCtrl->SPRDCBOF.SPRDCBOF1,
			union io_cnr_cspr_reg_sprdcbof_1, SPRDCBOF_1, sprdCtrl->cb_table.of1 );
	im_cnr_set_reg_signed( rdmaSprdCtrl->SPRDCBOF.SPRDCBOF1,
			union io_cnr_cspr_reg_sprdcbof_1, SPRDCBOF_2, sprdCtrl->cb_table.of2 );
	im_cnr_set_reg_signed( rdmaSprdCtrl->SPRDCBOF.SPRDCBOF1,
			union io_cnr_cspr_reg_sprdcbof_1, SPRDCBOF_3, sprdCtrl->cb_table.of3 );
	im_cnr_set_reg_signed( rdmaSprdCtrl->SPRDCBOF.SPRDCBOF2,
			union io_cnr_cspr_reg_sprdcbof_2, SPRDCBOF_4, sprdCtrl->cb_table.of4 );
	im_cnr_set_reg_signed( rdmaSprdCtrl->SPRDCBOF.SPRDCBOF2,
			union io_cnr_cspr_reg_sprdcbof_2, SPRDCBOF_5, sprdCtrl->cb_table.of5 );
	im_cnr_set_reg_signed( rdmaSprdCtrl->SPRDCBGA.SPRDCBGA1,
			union io_cnr_cspr_reg_sprdcbga_1, SPRDCBGA_0, sprdCtrl->cb_table.gain0 );
	im_cnr_set_reg_signed( rdmaSprdCtrl->SPRDCBGA.SPRDCBGA1,
			union io_cnr_cspr_reg_sprdcbga_1, SPRDCBGA_1, sprdCtrl->cb_table.gain1 );
	im_cnr_set_reg_signed( rdmaSprdCtrl->SPRDCBGA.SPRDCBGA2,
			union io_cnr_cspr_reg_sprdcbga_2, SPRDCBGA_2, sprdCtrl->cb_table.gain2 );
	im_cnr_set_reg_signed( rdmaSprdCtrl->SPRDCBGA.SPRDCBGA2,
			union io_cnr_cspr_reg_sprdcbga_2, SPRDCBGA_3, sprdCtrl->cb_table.gain3 );
	im_cnr_set_reg_signed( rdmaSprdCtrl->SPRDCBGA.SPRDCBGA3,
			union io_cnr_cspr_reg_sprdcbga_3, SPRDCBGA_4, sprdCtrl->cb_table.gain4 );
	im_cnr_set_reg_signed( rdmaSprdCtrl->SPRDCBGA.SPRDCBGA3,
			union io_cnr_cspr_reg_sprdcbga_3, SPRDCBGA_5, sprdCtrl->cb_table.gain5 );

	im_cnr_set_reg_signed( rdmaSprdCtrl->SPRDCRBD.SPRDCRBD1,
			union io_cnr_cspr_reg_sprdcrbd_1, SPRDCRBD_1, sprdCtrl->cr_table.bd1 );
	im_cnr_set_reg_signed( rdmaSprdCtrl->SPRDCRBD.SPRDCRBD1,
			union io_cnr_cspr_reg_sprdcrbd_1, SPRDCRBD_2, sprdCtrl->cr_table.bd2 );
	im_cnr_set_reg_signed( rdmaSprdCtrl->SPRDCRBD.SPRDCRBD1,
			union io_cnr_cspr_reg_sprdcrbd_1, SPRDCRBD_3, sprdCtrl->cr_table.bd3 );
	im_cnr_set_reg_signed( rdmaSprdCtrl->SPRDCRBD.SPRDCRBD1,
			union io_cnr_cspr_reg_sprdcrbd_1, SPRDCRBD_4, sprdCtrl->cr_table.bd4 );
	im_cnr_set_reg_signed( rdmaSprdCtrl->SPRDCRBD.SPRDCRBD2,
			union io_cnr_cspr_reg_sprdcrbd_2, SPRDCRBD_5, sprdCtrl->cr_table.bd5 );
	im_cnr_set_reg_signed( rdmaSprdCtrl->SPRDCROF.SPRDCROF1,
			union io_cnr_cspr_reg_sprdcrof_1, SPRDCROF_0, sprdCtrl->cr_table.of0 );
	im_cnr_set_reg_signed( rdmaSprdCtrl->SPRDCROF.SPRDCROF1,
			union io_cnr_cspr_reg_sprdcrof_1, SPRDCROF_1, sprdCtrl->cr_table.of1 );
	im_cnr_set_reg_signed( rdmaSprdCtrl->SPRDCROF.SPRDCROF1,
			union io_cnr_cspr_reg_sprdcrof_1, SPRDCROF_2, sprdCtrl->cr_table.of2 );
	im_cnr_set_reg_signed( rdmaSprdCtrl->SPRDCROF.SPRDCROF1,
			union io_cnr_cspr_reg_sprdcrof_1, SPRDCROF_3, sprdCtrl->cr_table.of3 );
	im_cnr_set_reg_signed( rdmaSprdCtrl->SPRDCROF.SPRDCROF2,
			union io_cnr_cspr_reg_sprdcrof_2, SPRDCROF_4, sprdCtrl->cr_table.of4 );
	im_cnr_set_reg_signed( rdmaSprdCtrl->SPRDCROF.SPRDCROF2,
			union io_cnr_cspr_reg_sprdcrof_2, SPRDCROF_5, sprdCtrl->cr_table.of5 );
	im_cnr_set_reg_signed( rdmaSprdCtrl->SPRDCRGA.SPRDCRGA1,
			union io_cnr_cspr_reg_sprdcrga_1, SPRDCRGA_0, sprdCtrl->cr_table.gain0 );
	im_cnr_set_reg_signed( rdmaSprdCtrl->SPRDCRGA.SPRDCRGA1,
			union io_cnr_cspr_reg_sprdcrga_1, SPRDCRGA_1, sprdCtrl->cr_table.gain1 );
	im_cnr_set_reg_signed( rdmaSprdCtrl->SPRDCRGA.SPRDCRGA2,
			union io_cnr_cspr_reg_sprdcrga_2, SPRDCRGA_2, sprdCtrl->cr_table.gain2 );
	im_cnr_set_reg_signed( rdmaSprdCtrl->SPRDCRGA.SPRDCRGA2,
			union io_cnr_cspr_reg_sprdcrga_2, SPRDCRGA_3, sprdCtrl->cr_table.gain3 );
	im_cnr_set_reg_signed( rdmaSprdCtrl->SPRDCRGA.SPRDCRGA3,
			union io_cnr_cspr_reg_sprdcrga_3, SPRDCRGA_4, sprdCtrl->cr_table.gain4 );
	im_cnr_set_reg_signed( rdmaSprdCtrl->SPRDCRGA.SPRDCRGA3,
			union io_cnr_cspr_reg_sprdcrga_3, SPRDCRGA_5, sprdCtrl->cr_table.gain5 );
}

/*
Convert ImCnrTable to ImCnrRdmaDataCsprLowYTbl
*/
static VOID imCnrConvertRdmaCsprLowYTable( const ImCnrTable* sprCsprLowY,
		ImCnrRdmaDataCsprLowYTbl* rdmaCsprLowYTable )
{
	rdmaCsprLowYTable->LCYSCLBD.LCYSCLBD1.bit.LCYSCLBD_1	= sprCsprLowY->bd1;
	rdmaCsprLowYTable->LCYSCLBD.LCYSCLBD1.bit.LCYSCLBD_2	= sprCsprLowY->bd2;
	rdmaCsprLowYTable->LCYSCLBD.LCYSCLBD1.bit.LCYSCLBD_3	= sprCsprLowY->bd3;
	rdmaCsprLowYTable->LCYSCLBD.LCYSCLBD1.bit.LCYSCLBD_4	= sprCsprLowY->bd4;
	rdmaCsprLowYTable->LCYSCLBD.LCYSCLBD2.bit.LCYSCLBD_5	= sprCsprLowY->bd5;
	rdmaCsprLowYTable->LCYSCLOF.LCYSCLOF1.bit.LCYSCLOF_0	= sprCsprLowY->of0;
	rdmaCsprLowYTable->LCYSCLOF.LCYSCLOF1.bit.LCYSCLOF_1	= sprCsprLowY->of1;
	rdmaCsprLowYTable->LCYSCLOF.LCYSCLOF1.bit.LCYSCLOF_2	= sprCsprLowY->of2;
	rdmaCsprLowYTable->LCYSCLOF.LCYSCLOF1.bit.LCYSCLOF_3	= sprCsprLowY->of3;
	rdmaCsprLowYTable->LCYSCLOF.LCYSCLOF2.bit.LCYSCLOF_4	= sprCsprLowY->of4;
	rdmaCsprLowYTable->LCYSCLOF.LCYSCLOF2.bit.LCYSCLOF_5	= sprCsprLowY->of5;
	// write signed data
	im_cnr_set_reg_signed( rdmaCsprLowYTable->LCYSCLGA.LCYSCLGA1,
			union io_cnr_cspr_reg_lcysclga_1, LCYSCLGA_0, sprCsprLowY->gain0 );
	im_cnr_set_reg_signed( rdmaCsprLowYTable->LCYSCLGA.LCYSCLGA1,
			union io_cnr_cspr_reg_lcysclga_1, LCYSCLGA_1, sprCsprLowY->gain1 );
	im_cnr_set_reg_signed( rdmaCsprLowYTable->LCYSCLGA.LCYSCLGA1,
			union io_cnr_cspr_reg_lcysclga_1, LCYSCLGA_2, sprCsprLowY->gain2 );
	im_cnr_set_reg_signed( rdmaCsprLowYTable->LCYSCLGA.LCYSCLGA1,
			union io_cnr_cspr_reg_lcysclga_1, LCYSCLGA_3, sprCsprLowY->gain3 );
	im_cnr_set_reg_signed( rdmaCsprLowYTable->LCYSCLGA.LCYSCLGA2,
			union io_cnr_cspr_reg_lcysclga_2, LCYSCLGA_4, sprCsprLowY->gain4 );
	im_cnr_set_reg_signed( rdmaCsprLowYTable->LCYSCLGA.LCYSCLGA2,
			union io_cnr_cspr_reg_lcysclga_2, LCYSCLGA_5, sprCsprLowY->gain5 );
}

#endif

/*
Set CbCr setting of destination
*/
INT32 im_cnrfive_ofl_ctrl_sprd_cc(ImCnrfive *self, UCHAR ch, const ImCnrCtrlCcSrcDst* const sprdCtrl )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrfive_ofl_ctrl_sprd_cc() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( sprdCtrl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrfive_ofl_ctrl_sprd_cc() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	Im_CNR_Dsb();

	IO_CNR(ch)->OFL_CSPR_REG.SPRD.bit.SPRD = sprdCtrl->enable;

	// write signed data
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCBBD.SPRDCBBD1,
			union io_cnr_cspr_reg_sprdcbbd_1, SPRDCBBD_1, sprdCtrl->cb_table.bd1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCBBD.SPRDCBBD1,
			union io_cnr_cspr_reg_sprdcbbd_1, SPRDCBBD_2, sprdCtrl->cb_table.bd2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCBBD.SPRDCBBD1,
			union io_cnr_cspr_reg_sprdcbbd_1, SPRDCBBD_3, sprdCtrl->cb_table.bd3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCBBD.SPRDCBBD1,
			union io_cnr_cspr_reg_sprdcbbd_1, SPRDCBBD_4, sprdCtrl->cb_table.bd4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCBBD.SPRDCBBD2,
			union io_cnr_cspr_reg_sprdcbbd_2, SPRDCBBD_5, sprdCtrl->cb_table.bd5 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCBOF.SPRDCBOF1,
			union io_cnr_cspr_reg_sprdcbof_1, SPRDCBOF_0, sprdCtrl->cb_table.of0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCBOF.SPRDCBOF1,
			union io_cnr_cspr_reg_sprdcbof_1, SPRDCBOF_1, sprdCtrl->cb_table.of1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCBOF.SPRDCBOF1,
			union io_cnr_cspr_reg_sprdcbof_1, SPRDCBOF_2, sprdCtrl->cb_table.of2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCBOF.SPRDCBOF1,
			union io_cnr_cspr_reg_sprdcbof_1, SPRDCBOF_3, sprdCtrl->cb_table.of3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCBOF.SPRDCBOF2,
			union io_cnr_cspr_reg_sprdcbof_2, SPRDCBOF_4, sprdCtrl->cb_table.of4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCBOF.SPRDCBOF2,
			union io_cnr_cspr_reg_sprdcbof_2, SPRDCBOF_5, sprdCtrl->cb_table.of5 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCBGA.SPRDCBGA1,
			union io_cnr_cspr_reg_sprdcbga_1, SPRDCBGA_0, sprdCtrl->cb_table.gain0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCBGA.SPRDCBGA1,
			union io_cnr_cspr_reg_sprdcbga_1, SPRDCBGA_1, sprdCtrl->cb_table.gain1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCBGA.SPRDCBGA2,
			union io_cnr_cspr_reg_sprdcbga_2, SPRDCBGA_2, sprdCtrl->cb_table.gain2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCBGA.SPRDCBGA2,
			union io_cnr_cspr_reg_sprdcbga_2, SPRDCBGA_3, sprdCtrl->cb_table.gain3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCBGA.SPRDCBGA3,
			union io_cnr_cspr_reg_sprdcbga_3, SPRDCBGA_4, sprdCtrl->cb_table.gain4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCBGA.SPRDCBGA3,
			union io_cnr_cspr_reg_sprdcbga_3, SPRDCBGA_5, sprdCtrl->cb_table.gain5 );

	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCRBD.SPRDCRBD1,
			union io_cnr_cspr_reg_sprdcrbd_1, SPRDCRBD_1, sprdCtrl->cr_table.bd1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCRBD.SPRDCRBD1,
			union io_cnr_cspr_reg_sprdcrbd_1, SPRDCRBD_2, sprdCtrl->cr_table.bd2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCRBD.SPRDCRBD1,
			union io_cnr_cspr_reg_sprdcrbd_1, SPRDCRBD_3, sprdCtrl->cr_table.bd3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCRBD.SPRDCRBD1,
			union io_cnr_cspr_reg_sprdcrbd_1, SPRDCRBD_4, sprdCtrl->cr_table.bd4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCRBD.SPRDCRBD2,
			union io_cnr_cspr_reg_sprdcrbd_2, SPRDCRBD_5, sprdCtrl->cr_table.bd5 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCROF.SPRDCROF1,
			union io_cnr_cspr_reg_sprdcrof_1, SPRDCROF_0, sprdCtrl->cr_table.of0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCROF.SPRDCROF1,
			union io_cnr_cspr_reg_sprdcrof_1, SPRDCROF_1, sprdCtrl->cr_table.of1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCROF.SPRDCROF1,
			union io_cnr_cspr_reg_sprdcrof_1, SPRDCROF_2, sprdCtrl->cr_table.of2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCROF.SPRDCROF1,
			union io_cnr_cspr_reg_sprdcrof_1, SPRDCROF_3, sprdCtrl->cr_table.of3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCROF.SPRDCROF2,
			union io_cnr_cspr_reg_sprdcrof_2, SPRDCROF_4, sprdCtrl->cr_table.of4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCROF.SPRDCROF2,
			union io_cnr_cspr_reg_sprdcrof_2, SPRDCROF_5, sprdCtrl->cr_table.of5 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCRGA.SPRDCRGA1,
			union io_cnr_cspr_reg_sprdcrga_1, SPRDCRGA_0, sprdCtrl->cr_table.gain0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCRGA.SPRDCRGA1,
			union io_cnr_cspr_reg_sprdcrga_1, SPRDCRGA_1, sprdCtrl->cr_table.gain1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCRGA.SPRDCRGA2,
			union io_cnr_cspr_reg_sprdcrga_2, SPRDCRGA_2, sprdCtrl->cr_table.gain2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCRGA.SPRDCRGA2,
			union io_cnr_cspr_reg_sprdcrga_2, SPRDCRGA_3, sprdCtrl->cr_table.gain3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCRGA.SPRDCRGA3,
			union io_cnr_cspr_reg_sprdcrga_3, SPRDCRGA_4, sprdCtrl->cr_table.gain4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.SPRDCRGA.SPRDCRGA3,
			union io_cnr_cspr_reg_sprdcrga_3, SPRDCRGA_5, sprdCtrl->cr_table.gain5 );

	im_cnrone_off_pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
Set CbCr setting of destination
*/
INT32 im_cnrfive_otf_ctrl_sprd_cc(ImCnrfive *self, UCHAR ch, const ImCnrCtrlCcSrcDst* const sprdCtrl )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrfive_otf_ctrl_sprd_cc() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( sprdCtrl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrfive_otf_ctrl_sprd_cc() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	Im_CNR_Dsb();

	IO_CNR(ch)->OTF_CSPR_REG.SPRD.bit.SPRD = sprdCtrl->enable;

	// write signed data
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCBBD.SPRDCBBD1,
			union io_cnr_cspr_reg_sprdcbbd_1, SPRDCBBD_1, sprdCtrl->cb_table.bd1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCBBD.SPRDCBBD1,
			union io_cnr_cspr_reg_sprdcbbd_1, SPRDCBBD_2, sprdCtrl->cb_table.bd2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCBBD.SPRDCBBD1,
			union io_cnr_cspr_reg_sprdcbbd_1, SPRDCBBD_3, sprdCtrl->cb_table.bd3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCBBD.SPRDCBBD1,
			union io_cnr_cspr_reg_sprdcbbd_1, SPRDCBBD_4, sprdCtrl->cb_table.bd4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCBBD.SPRDCBBD2,
			union io_cnr_cspr_reg_sprdcbbd_2, SPRDCBBD_5, sprdCtrl->cb_table.bd5 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCBOF.SPRDCBOF1,
			union io_cnr_cspr_reg_sprdcbof_1, SPRDCBOF_0, sprdCtrl->cb_table.of0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCBOF.SPRDCBOF1,
			union io_cnr_cspr_reg_sprdcbof_1, SPRDCBOF_1, sprdCtrl->cb_table.of1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCBOF.SPRDCBOF1,
			union io_cnr_cspr_reg_sprdcbof_1, SPRDCBOF_2, sprdCtrl->cb_table.of2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCBOF.SPRDCBOF1,
			union io_cnr_cspr_reg_sprdcbof_1, SPRDCBOF_3, sprdCtrl->cb_table.of3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCBOF.SPRDCBOF2,
			union io_cnr_cspr_reg_sprdcbof_2, SPRDCBOF_4, sprdCtrl->cb_table.of4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCBOF.SPRDCBOF2,
			union io_cnr_cspr_reg_sprdcbof_2, SPRDCBOF_5, sprdCtrl->cb_table.of5 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCBGA.SPRDCBGA1,
			union io_cnr_cspr_reg_sprdcbga_1, SPRDCBGA_0, sprdCtrl->cb_table.gain0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCBGA.SPRDCBGA1,
			union io_cnr_cspr_reg_sprdcbga_1, SPRDCBGA_1, sprdCtrl->cb_table.gain1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCBGA.SPRDCBGA2,
			union io_cnr_cspr_reg_sprdcbga_2, SPRDCBGA_2, sprdCtrl->cb_table.gain2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCBGA.SPRDCBGA2,
			union io_cnr_cspr_reg_sprdcbga_2, SPRDCBGA_3, sprdCtrl->cb_table.gain3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCBGA.SPRDCBGA3,
			union io_cnr_cspr_reg_sprdcbga_3, SPRDCBGA_4, sprdCtrl->cb_table.gain4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCBGA.SPRDCBGA3,
			union io_cnr_cspr_reg_sprdcbga_3, SPRDCBGA_5, sprdCtrl->cb_table.gain5 );

	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCRBD.SPRDCRBD1,
			union io_cnr_cspr_reg_sprdcrbd_1, SPRDCRBD_1, sprdCtrl->cr_table.bd1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCRBD.SPRDCRBD1,
			union io_cnr_cspr_reg_sprdcrbd_1, SPRDCRBD_2, sprdCtrl->cr_table.bd2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCRBD.SPRDCRBD1,
			union io_cnr_cspr_reg_sprdcrbd_1, SPRDCRBD_3, sprdCtrl->cr_table.bd3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCRBD.SPRDCRBD1,
			union io_cnr_cspr_reg_sprdcrbd_1, SPRDCRBD_4, sprdCtrl->cr_table.bd4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCRBD.SPRDCRBD2,
			union io_cnr_cspr_reg_sprdcrbd_2, SPRDCRBD_5, sprdCtrl->cr_table.bd5 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCROF.SPRDCROF1,
			union io_cnr_cspr_reg_sprdcrof_1, SPRDCROF_0, sprdCtrl->cr_table.of0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCROF.SPRDCROF1,
			union io_cnr_cspr_reg_sprdcrof_1, SPRDCROF_1, sprdCtrl->cr_table.of1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCROF.SPRDCROF1,
			union io_cnr_cspr_reg_sprdcrof_1, SPRDCROF_2, sprdCtrl->cr_table.of2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCROF.SPRDCROF1,
			union io_cnr_cspr_reg_sprdcrof_1, SPRDCROF_3, sprdCtrl->cr_table.of3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCROF.SPRDCROF2,
			union io_cnr_cspr_reg_sprdcrof_2, SPRDCROF_4, sprdCtrl->cr_table.of4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCROF.SPRDCROF2,
			union io_cnr_cspr_reg_sprdcrof_2, SPRDCROF_5, sprdCtrl->cr_table.of5 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCRGA.SPRDCRGA1,
			union io_cnr_cspr_reg_sprdcrga_1, SPRDCRGA_0, sprdCtrl->cr_table.gain0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCRGA.SPRDCRGA1,
			union io_cnr_cspr_reg_sprdcrga_1, SPRDCRGA_1, sprdCtrl->cr_table.gain1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCRGA.SPRDCRGA2,
			union io_cnr_cspr_reg_sprdcrga_2, SPRDCRGA_2, sprdCtrl->cr_table.gain2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCRGA.SPRDCRGA2,
			union io_cnr_cspr_reg_sprdcrga_2, SPRDCRGA_3, sprdCtrl->cr_table.gain3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCRGA.SPRDCRGA3,
			union io_cnr_cspr_reg_sprdcrga_3, SPRDCRGA_4, sprdCtrl->cr_table.gain4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OTF_CSPR_REG.SPRDCRGA.SPRDCRGA3,
			union io_cnr_cspr_reg_sprdcrga_3, SPRDCRGA_5, sprdCtrl->cr_table.gain5 );

	im_cnrone_off_pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

#ifdef CO_DDIM_UTILITY_USE
/*
CNR(OFL) Set CSPR Low_CC_Y Table setting parameter information
*/
INT32 im_cnrfive_set_rdmavalue_ofl_cspr_low_cc_y_table(ImCnrfive *self, const ImCnrTable* const sprCsprLowCcY,
		ImCnroneRdmaDataCsprLowCcYTbl* const rdmaCsprLowCcYTable )
{
#ifdef CO_PARAM_CHECK
	if( sprCsprLowCcY == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfive_set_rdmavalue_ofl_cspr_low_cc_y_table() Parameter(sprCsprLowCcY) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdmaCsprLowCcYTable == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfive_set_rdmavalue_ofl_cspr_low_cc_y_table() Parameter(rdmaCsprLowCcYTable) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	memset( rdmaCsprLowCcYTable, 0, sizeof(ImCnroneRdmaDataCsprLowCcYTbl) );
	imCnrConvertRdmaCsprLowCcYTable( sprCsprLowCcY, rdmaCsprLowCcYTable );

	return D_DDIM_OK;
}

/*
CNR(OTF) Set CSPR Low_CC_Y Table setting parameter information
*/
INT32 im_cnrfive_set_rdmavalue_otf_cspr_low_cc_y_table(ImCnrfive *self, const ImCnrTable* const sprCsprLowCcY,
		ImCnroneRdmaDataCsprLowCcYTbl* const rdmaCsprLowCcYTable )
{
#ifdef CO_PARAM_CHECK
	if( sprCsprLowCcY == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfive_set_rdmavalue_otf_cspr_low_cc_y_table() Parameter(sprCsprLowCcY) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdmaCsprLowCcYTable == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfive_set_rdmavalue_otf_cspr_low_cc_y_table() Parameter(rdmaCsprLowCcYTable) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	memset( rdmaCsprLowCcYTable, 0, sizeof(ImCnroneRdmaDataCsprLowCcYTbl) );
	imCnrConvertRdmaCsprLowCcYTable( sprCsprLowCcY, rdmaCsprLowCcYTable );

	return D_DDIM_OK;
}

/*
CNR(OFL) Set CSPR Low_CC_C Table setting parameter information
*/
INT32 im_cnrfive_set_rdmavalue_ofl_cspr_low_cc_c_table(ImCnrfive *self, const ImCnrTable* const sprCsprLowCcC,
		ImCnroneRdmaDataCsprLowCcCTbl* const rdmaCsprLowCcCTable )
{
#ifdef CO_PARAM_CHECK
	if( sprCsprLowCcC == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfive_set_rdmavalue_ofl_cspr_low_cc_c_table() Parameter(sprCsprLowCcC) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdmaCsprLowCcCTable == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfive_set_rdmavalue_ofl_cspr_low_cc_c_table() Parameter(rdmaCsprLowCcCTable) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	memset( rdmaCsprLowCcCTable, 0, sizeof(ImCnroneRdmaDataCsprLowCcCTbl) );
	imCnrConvertRdmaCsprLowCcCTable( sprCsprLowCcC, rdmaCsprLowCcCTable );

	return D_DDIM_OK;
}

/*
CNR(OTF) Set CSPR Low_CC_C Table setting parameter information
*/
INT32 im_cnrfive_set_rdmavalue_otf_cspr_low_cc_c_table(ImCnrfive *self, const ImCnrTable* const sprCsprLowCcC,
		ImCnroneRdmaDataCsprLowCcCTbl* const rdmaCsprLowCcCTable )
{
#ifdef CO_PARAM_CHECK
	if( sprCsprLowCcC == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfive_set_rdmavalue_otf_cspr_low_cc_c_table() Parameter(sprCsprLowCcC) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdmaCsprLowCcCTable == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfive_set_rdmavalue_otf_cspr_low_cc_c_table() Parameter(rdmaCsprLowCcCTable) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	memset( rdmaCsprLowCcCTable, 0, sizeof(ImCnroneRdmaDataCsprLowCcCTbl) );
	imCnrConvertRdmaCsprLowCcCTable( sprCsprLowCcC, rdmaCsprLowCcCTable );

	return D_DDIM_OK;
}

/*
CNR(OFL) Set CSPR Edge Table setting parameter information
*/
INT32 im_cnrfive_set_rdmavalue_ofl_cspr_edge_table(ImCnrfive *self, const ImCnrTable* const sprCsprEdge,
		ImCnroneRdmaDataCsprEdgeTbl* const rdmaCsprEdgeTable )
{
#ifdef CO_PARAM_CHECK
	if( sprCsprEdge == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfive_set_rdmavalue_ofl_cspr_edge_table() Parameter(sprCsprEdge) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdmaCsprEdgeTable == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfive_set_rdmavalue_ofl_cspr_edge_table() Parameter(rdmaCsprEdgeTable) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	memset( rdmaCsprEdgeTable, 0, sizeof(ImCnroneRdmaDataCsprEdgeTbl) );
	imCnrConvertRdmaCsprEdgeTable( sprCsprEdge, rdmaCsprEdgeTable );

	return D_DDIM_OK;
}

/*
CNR(OTF) Set CSPR Edge Table setting parameter information
*/
INT32 im_cnrfive_set_rdmavalue_otf_cspr_edge_table(ImCnrfive *self, const ImCnrTable* const sprCsprEdge,
		ImCnroneRdmaDataCsprEdgeTbl* const rdmaCsprEdgeTable )
{
#ifdef CO_PARAM_CHECK
	if( sprCsprEdge == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfive_set_rdmavalue_otf_cspr_edge_table() Parameter(sprCsprEdge) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdmaCsprEdgeTable == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfive_set_rdmavalue_otf_cspr_edge_table() Parameter(rdmaCsprEdgeTable) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	memset( rdmaCsprEdgeTable, 0, sizeof(ImCnroneRdmaDataCsprEdgeTbl) );
	imCnrConvertRdmaCsprEdgeTable( sprCsprEdge, rdmaCsprEdgeTable );

	return D_DDIM_OK;
}

/*
CNR(OFL) Set CSPR Hue Specified Table setting parameter information
*/
INT32 im_cnrfive_set_rdmavalue_ofl_cspr_hue_spec_table(ImCnrfive *self, const ImCnrHueSpecTable* const sprCsprHue,
		ImCnroneRdmaDataCsprHueTbl* const rdmaCsprHueTable )
{
#ifdef CO_PARAM_CHECK
	if( sprCsprHue == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfive_set_rdmavalue_ofl_cspr_hue_spec_table() Parameter(sprCsprHue) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdmaCsprHueTable == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfive_set_rdmavalue_ofl_cspr_hue_spec_table() Parameter(rdmaCsprHueTable) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	memset( rdmaCsprHueTable, 0, sizeof(ImCnroneRdmaDataCsprHueTbl) );
	imCnrConvertRdmaCsprHueTable( sprCsprHue, rdmaCsprHueTable );

	return D_DDIM_OK;
}

/*
CNR(OTF) Set CSPR Hue Specified Table setting parameter information
*/
INT32 im_cnrfive_set_rdmavalue_otf_cspr_hue_spec_table(ImCnrfive *self, const ImCnrHueSpecTable* const sprCsprHue,
		ImCnroneRdmaDataCsprHueTbl* const rdmaCsprHueTable )
{
#ifdef CO_PARAM_CHECK
	if( sprCsprHue == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfive_set_rdmavalue_otf_cspr_hue_spec_table() Parameter(sprCsprHue) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdmaCsprHueTable == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfive_set_rdmavalue_otf_cspr_hue_spec_table() Parameter(rdmaCsprHueTable) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	memset( rdmaCsprHueTable, 0, sizeof(ImCnroneRdmaDataCsprHueTbl) );
	imCnrConvertRdmaCsprHueTable( sprCsprHue, rdmaCsprHueTable );

	return D_DDIM_OK;
}

/*
CNR(OFL) Set CSPR SPRS_CC Table setting parameter information
*/
INT32 im_cnrfive_set_rdmavalue_ofl_cspr_sprs_cc_table(ImCnrfive *self, const ImCnrCtrlCcSrcDst* const csprSprsCc,
		ImCnrRdmaDataSprsCcTbl* const rdmaCsprSprsCc )
{
#ifdef CO_PARAM_CHECK
	if( csprSprsCc == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfive_set_rdmavalue_ofl_cspr_sprs_cc_table() Parameter(csprSprsCc) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdmaCsprSprsCc == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfive_set_rdmavalue_ofl_cspr_sprs_cc_table() Parameter(rdmaCsprSprsCc) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	memset( rdmaCsprSprsCc, 0, sizeof(ImCnrRdmaDataSprsCcTbl) );
	imCnrConvertRdmaCsprSprsCc( csprSprsCc, rdmaCsprSprsCc );

	return D_DDIM_OK;
}

/*
CNR(OTF) Set CSPR SPRS_CC Table setting parameter information
*/
INT32 im_cnrfive_set_rdmavalue_otf_cspr_sprs_cc_table(ImCnrfive *self, const ImCnrCtrlCcSrcDst* const csprSprsCc,
		ImCnrRdmaDataSprsCcTbl* const rdmaCsprSprsCc )
{
#ifdef CO_PARAM_CHECK
	if( csprSprsCc == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfive_set_rdmavalue_otf_cspr_sprs_cc_table() Parameter(csprSprsCc) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdmaCsprSprsCc == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfive_set_rdmavalue_otf_cspr_sprs_cc_table() Parameter(rdmaCsprSprsCc) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	memset( rdmaCsprSprsCc, 0, sizeof(ImCnrRdmaDataSprsCcTbl) );
	imCnrConvertRdmaCsprSprsCc( csprSprsCc, rdmaCsprSprsCc );

	return D_DDIM_OK;
}

/*
CNR(OFL) Set CSPR SPRD_CC Table setting parameter information
*/
INT32 im_cnrfive_set_rdmavalue_ofl_cspr_sprd_cc_table(ImCnrfive *self, const ImCnrCtrlCcSrcDst* const csprSprdCc,
		ImCnroneRdmaDataSprdCcTbl* const rdmaCsprSprdCc )
{
#ifdef CO_PARAM_CHECK
	if( csprSprdCc == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfive_set_rdmavalue_ofl_cspr_sprd_cc_table() Parameter(csprSprdCc) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdmaCsprSprdCc == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfive_set_rdmavalue_ofl_cspr_sprd_cc_table() Parameter(rdmaCsprSprdCc) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	memset( rdmaCsprSprdCc, 0, sizeof(ImCnroneRdmaDataSprdCcTbl) );
	imCnrConvertRdmaCsprSprdCc( csprSprdCc, rdmaCsprSprdCc );

	return D_DDIM_OK;
}

/*
CNR(OTF) Set CSPR SPRD_CC Table setting parameter information
*/
INT32 im_cnrfive_set_rdmavalue_otf_cspr_sprd_cc_table(ImCnrfive *self, const ImCnrCtrlCcSrcDst* const csprSprdCc,
		ImCnroneRdmaDataSprdCcTbl* const rdmaCsprSprdCc )
{
#ifdef CO_PARAM_CHECK
	if( csprSprdCc == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfive_set_rdmavalue_otf_cspr_sprd_cc_table() Parameter(csprSprdCc) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdmaCsprSprdCc == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfive_set_rdmavalue_otf_cspr_sprd_cc_table() Parameter(rdmaCsprSprdCc) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	memset( rdmaCsprSprdCc, 0, sizeof(ImCnroneRdmaDataSprdCcTbl) );
	imCnrConvertRdmaCsprSprdCc( csprSprdCc, rdmaCsprSprdCc );

	return D_DDIM_OK;
}

/*
CNR(OFL) Set CSPR Low_Y Table setting parameter information
*/
INT32 im_cnrfive_set_rdmavalue_ofl_cspr_low_y_table(ImCnrfive *self, const ImCnrTable* const sprCsprLowY,
		ImCnrRdmaDataCsprLowYTbl* const rdmaCsprLowYTable )
{
#ifdef CO_PARAM_CHECK
	if( sprCsprLowY == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfive_set_rdmavalue_ofl_cspr_low_y_table() Parameter(sprCsprLowY) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdmaCsprLowYTable == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfive_set_rdmavalue_ofl_cspr_low_y_table() Parameter(rdmaCsprLowYTable) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	memset( rdmaCsprLowYTable, 0, sizeof(ImCnrRdmaDataCsprLowYTbl) );
	imCnrConvertRdmaCsprLowYTable( sprCsprLowY, rdmaCsprLowYTable );

	return D_DDIM_OK;
}

/*
CNR(OTF) Set CSPR Low_Y Table setting parameter information
*/
INT32 im_cnrfive_set_rdmavalue_otf_cspr_low_y_table(ImCnrfive *self, const ImCnrTable* const sprCsprLowY,
		ImCnrRdmaDataCsprLowYTbl* const rdmaCsprLowYTable )
{
#ifdef CO_PARAM_CHECK
	if( sprCsprLowY == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfive_set_rdmavalue_otf_cspr_low_y_table() Parameter(sprCsprLowY) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( rdmaCsprLowYTable == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfive_set_rdmavalue_otf_cspr_low_y_table() Parameter(rdmaCsprLowYTable) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	memset( rdmaCsprLowYTable, 0, sizeof(ImCnrRdmaDataCsprLowYTbl) );
	imCnrConvertRdmaCsprLowYTable( sprCsprLowY, rdmaCsprLowYTable );

	return D_DDIM_OK;
}

#endif

/*PUBLIC*/
ImCnrfive* im_cnrfive_new(void)
{
	ImCnrfive *self = g_object_new(IM_TYPE_CNRFIVE, NULL);
	return self;
}



