/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :董如利
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/
#include <stdlib.h>
#include <string.h>
#include<ct_dd_top.h>
#include "../../DeviceDriver/LSITop/src/ddtop.h"
#include "../../DeviceDriver/LSITop/src/ddtopfour.h"
#include "../../DeviceDriver/LSITop/src/ddtopone.h"
#include "../../DeviceDriver/LSITop/src/ddtopthree.h"
#include "../../DeviceDriver/LSITop/src/ddtoptwo.h"

#include "ctddtopsecond.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdTopSecond, ct_dd_top_second);
#define CT_DD_TOP_SECOND_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdTopSecondPrivate,CT_TYPE_DD_TOP_SECOND))

struct _CtDdTopSecondPrivate
{
	kint32 seqNo;
};
/****************
* DECLS
*/
static void 			ct_dd_top_second_constructor(CtDdTopSecond *self);
static void 			ct_dd_top_second_destructor(CtDdTopSecond *self);
/****************
* IMPL
*/
static void ct_dd_top_second_constructor(CtDdTopSecond *self) 
{
	CtDdTopSecondPrivate *priv = CT_DD_TOP_SECOND_GET_PRIVATE(self);
    priv->seqNo = 0;
}

static void ct_dd_top_second_destructor(CtDdTopSecond *self) 
{
//	CtDdTopSecondPrivate *priv = CT_DD_TOP_SECOND_GET_PRIVATE(self);
}
/****************
* PUBLIC
*/
void ct_dd_top_second_pc_test_main(CtDdTopSecond *self)
{
    CtDdTopSecondPrivate *priv = CT_DD_TOP_SECOND_GET_PRIVATE(self);

	Ddim_Print(("*** [CT] 01-03-%03d : Dd_Top_Get_PERSEL1_xxxxx()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi get_ctrl persel1");

	Ddim_Print(("*** [CT] 01-03-%03d : Dd_Top_Get_PERSEL2_xxxxx()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi get_ctrl persel2");

	Ddim_Print(("*** [CT] 01-03-%03d : Dd_Top_Get_PERSEL3_xxxxx()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi get_ctrl persel3");

	Ddim_Print(("*** [CT] 01-03-%03d : Dd_Top_Get_PERSEL4_xxxxx()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi get_ctrl persel4");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_GET_MSELC_MSEL()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi get_ctrl msel");

	Ddim_Print(("*** [CT] 01-03-%03d : Dd_Top_Get_DBCNT1_xxxxx()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi get_ctrl dbcnt1");

	Ddim_Print(("*** [CT] 01-03-%03d : Dd_Top_Get_DBCNT2_xxxxx()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi get_ctrl dbcnt2");

	Ddim_Print(("*** [CT] 01-03-%03d : Dd_Top_Get_DBCNT3_xxxxx()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi get_ctrl dbcnt3");

	Ddim_Print(("*** [CT] 01-03-%03d : Dd_Top_Get_DBCNT4_xxxxx()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi get_ctrl dbcnt4");

	Ddim_Print(("*** [CT] 01-03-%03d : Dd_Top_Get_DBCNT5_xxxxx()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi get_ctrl dbcnt5");

	Ddim_Print(("*** [CT] 01-03-%03d : Dd_Top_Get_PUDCNT_xxxxx()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi get_ctrl pudcnt");

	Ddim_Print(("*** [CT] 01-03-%03d : Dd_Top_Get_PUDCNT_xxxxx()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi get_ctrl pudcnt");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PERSEL1_I2C0CNT()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 I2C0CNT 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 I2C0CNT 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 I2C0CNT 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 I2C0CNT 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PERSEL1_SDANC0()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 SDANC0 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 SDANC0 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PERSEL1_SCLNC0()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 SCLNC0 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 SCLNC0 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PERSEL1_I2C1CNT()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 I2C1CNT 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 I2C1CNT 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 I2C1CNT 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 I2C1CNT 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PERSEL1_SDANC1()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 SDANC1 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 SDANC1 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PERSEL1_SCLNC1)\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 SCLNC1 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 SCLNC1 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PERSEL1_I2C2CNT()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 I2C2CNT 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 I2C2CNT 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 I2C2CNT 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 I2C2CNT 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PERSEL1_SDANC2()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 SDANC2 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 SDANC2 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PERSEL1_SCLNC2()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 SCLNC2 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 SCLNC2 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PERSEL1_DVWT2()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 DVWT2 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 DVWT2 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PERSEL1_DHWT3()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 DHWT3 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 DHWT3 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PERSEL1_AU0DO0C()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 AU0DO0C 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 AU0DO0C 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PERSEL1_AU0DO1C()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 AU0DO1C 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 AU0DO1C 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PERSEL1_AU1DOC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 AU1DOC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 AU1DOC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PERSEL1_AU0MCC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 AU0MCC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 AU0MCC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PERSEL1_AU1MCC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 AU1MCC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 AU1MCC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopothree_SET_PERSEL1_RLSEL3()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 RLSEL3 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 RLSEL3 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopothree_SET_PERSEL1_RLSEL4()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 RLSEL4 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 RLSEL4 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopothree_SET_PERSEL1_RLSEL5()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 RLSEL5 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 RLSEL5 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopothree_SET_PERSEL1_INTVDSEL()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 INTVDSEL 7");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 INTVDSEL 6");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 INTVDSEL 5");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 INTVDSEL 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 INTVDSEL 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 INTVDSEL 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 INTVDSEL 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel1 INTVDSEL 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopothree_SET_PERSEL2_UDCTRG()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel2 UDCTRG 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel2 UDCTRG 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopothree_SET_PERSEL2_UDC0AM()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel2 UDC0AM 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel2 UDC0AM 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopothree_SET_PERSEL2_UDC0BM()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel2 UDC0BM 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel2 UDC0BM 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopothree_SET_PERSEL2_UDC1AM()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel2 UDC1AM 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel2 UDC1AM 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopothree_SET_PERSEL2_UDC1BM()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel2 UDC1BM 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel2 UDC1BM 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopothree_SET_PERSEL2_UDC2AM()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel2 UDC2AM 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel2 UDC2AM 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopothree_SET_PERSEL2_UDC2BM()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel2 UDC2BM 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel2 UDC2BM 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopothree_SET_PERSEL2_UDC3AM()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel2 UDC3AM 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel2 UDC3AM 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopothree_SET_PERSEL2_UDC3BM()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel2 UDC3BM 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel2 UDC3BM 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopothree_SET_PERSEL2_UDC4AM()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel2 UDC4AM 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel2 UDC4AM 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopothree_SET_PERSEL2_UDC4BM()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel2 UDC4BM 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel2 UDC4BM 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopothree_SET_PERSEL2_UDC5AM()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel2 UDC5AM 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel2 UDC5AM 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopothree_SET_PERSEL2_UDC5BM()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel2 UDC5BM 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel2 UDC5BM 0");

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	Ddim_Print(("*** [CT] 01-03-%03d : DdTopothree_SET_PERSEL2_SPIMSEN0()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel2 SPIMSEN0 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel2 SPIMSEN0 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopothree_SET_PERSEL2_SPIMSEN1()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel2 SPIMSEN1 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel2 SPIMSEN1 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopothree_SET_PERSEL2_SPIMSEN2()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel2 SPIMSEN2 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel2 SPIMSEN2 0");
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopothree_SET_PERSEL3_AU1WPPS()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 AU1WPPS 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 AU1WPPS 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopothree_SET_PERSEL3_AU0WP11()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 AU0WP11 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 AU0WP11 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopothree_SET_PERSEL3_SNH2WP04()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 SNH2WP04 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 SNH2WP04 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopothree_SET_PERSEL3_SNV2WP05()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 SNV2WP05 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 SNV2WP05 0");

	Ddim_Print(("*** [CT] 01-03-%03d : Dd_Top_Set_PERSEL3_SNV2WP06()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 SNV2WP06 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 SNV2WP06 0");

	Ddim_Print(("*** [CT] 01-03-%03d : Dd_Top_Set_PERSEL3_SNV2WP07()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 SNV2WP07 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 SNV2WP07 0");

	Ddim_Print(("*** [CT] 01-03-%03d : Dd_Top_Set_PERSEL3_SNV2WP08()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 SNV2WP08 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 SNV2WP08 0");

	Ddim_Print(("*** [CT] 01-03-%03d : Dd_Top_Set_PERSEL3_SNV2WP09()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 SNV2WP09 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 SNV2WP09 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopothree_SET_PERSEL3_U1VBSOU5()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 U1VBSOU5 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 U1VBSOU5 0");

	Ddim_Print(("*** [CT] 01-03-%03d : Dd_Top_Set_PERSEL3_U1VBSOU7()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 U1VBSOU7 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 U1VBSOU7 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopothree_SET_PERSEL3_U2IDWP14()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 U2IDWP14 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 U2IDWP14 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopothree_SET_PERSEL3_PRT1SOU3()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 PRT1SOU3 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 PRT1SOU3 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopothree_SET_PERSEL3_PXW0WP12()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 PXW0WP12 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 PXW0WP12 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopothree_SET_PERSEL3_PXW1SOU7()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 PXW1SOU7 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 PXW1SOU7 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopothree_SET_PERSEL3_PXC0SCK7()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 PXC0SCK7 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 PXC0SCK7 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopone_Set_PERSEL3_PXC1WP15()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 PXC1WP15 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 PXC1WP15 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopothree_SET_PERSEL3_SCK4WP13()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 SCK4WP13 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 SCK4WP13 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopothree_SET_PERSEL3_S3LSOU5WP14()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 S3LSOU5WP14 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 S3LSOU5WP14 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopothree_SET_PERSEL3_S3SWP15()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 S3SWP15 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 S3SWP15 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PERSEL3_RTS1SCK2()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 RTS1SCK2 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 RTS1SCK2 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PERSEL3_U1IDWP13()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 U1IDWP13 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 U1IDWP13 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PERSEL3_PRT0SCK3()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 PRT0SCK3 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel3 PRT0SCK3 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PERSEL4_EI22UD0A()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel4 EI22UD0A 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel4 EI22UD0A 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PERSEL4_EI23UD0B()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel4 EI23UD0B 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel4 EI23UD0B 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PERSEL4_EI24UD1A()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel4 EI24UD1A 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel4 EI24UD1A 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PERSEL4_EI25UD1B()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel4 EI25UD1B 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel4 EI25UD1B 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PERSEL4_EI26UD2A()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel4 EI26UD2A 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel4 EI26UD2A 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PERSEL4_EI27UD2B()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel4 EI27UD2B 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel4 EI27UD2B 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PERSEL4_EI28UD3A()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel4 EI28UD3A 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel4 EI28UD3A 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PERSEL4_EI29UD3B()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel4 EI29UD3B 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel4 EI29UD3B 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PERSEL4_EI30UD4A()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel4 EI30UD4A 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel4 EI30UD4A 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PERSEL4_EI31UD4B()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel4 EI31UD4B 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel4 EI31UD4B 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PERSEL4_SD3CDXS()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel4 SD3CDXS 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel4 SD3CDXS 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PERSEL4_SD3WPS()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel4 SD3WPS 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel4 SD3WPS 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PERSEL4_U1OCDXS)\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel4 U1OCDXS 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel4 U1OCDXS 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PERSEL4_U1IDDIGS()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel4 U1IDDIGS 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel4 U1IDDIGS 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PERSEL4_U2OCDXS()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel4 U2OCDXS 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel4 U2OCDXS 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PERSEL4_U2IDDIGS()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel4 U2IDDIGS 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl persel4 U2IDDIGS 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_MSELC_MSEL()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl mselc MSEL 15");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl mselc MSEL 14");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl mselc MSEL 13");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl mselc MSEL 12");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl mselc MSEL 11");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl mselc MSEL 10");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl mselc MSEL 9");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl mselc MSEL 8");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl mselc MSEL 7");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl mselc MSEL 6");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl mselc MSEL 5");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl mselc MSEL 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl mselc MSEL 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl mselc MSEL 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl mselc MSEL 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl mselc MSEL 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT1_T07DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt1 T07DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt1 T07DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt1 T07DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt1 T07DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT1_T08DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt1 T08DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt1 T08DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt1 T08DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt1 T08DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT1_T09DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt1 T09DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt1 T09DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt1 T09DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt1 T09DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT1_T10DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt1 T10DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt1 T10DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt1 T10DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt1 T10DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT1_T11DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt1 T11DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt1 T11DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt1 T11DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt1 T11DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT1_T12DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt1 T12DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt1 T12DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt1 T12DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt1 T12DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT1_T13DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt1 T13DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt1 T13DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt1 T13DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt1 T13DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT1_T14DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt1 T14DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt1 T14DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt1 T14DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt1 T14DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT1_T15DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt1 T15DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt1 T15DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt1 T15DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt1 T15DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT2_T16DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T16DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T16DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T16DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T16DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT2_T17DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T17DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T17DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T17DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T17DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT2_T18DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T18DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T18DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T18DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T18DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT2_T19DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T19DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T19DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T19DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T19DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT2_T20DC)\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T20DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T20DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T20DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T20DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT2_T21DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T21DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T21DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T21DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T21DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT2_T22DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T22DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T22DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T22DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T22DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT2_T23DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T23DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T23DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T23DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T23DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT2_T24DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T24DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T24DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T24DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T24DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT2_T25DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T25DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T25DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T25DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T25DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT2_T26DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T26DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T26DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T26DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T26DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT2_T27DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T27DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T27DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T27DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T27DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT2_T28DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T28DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T28DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T28DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T28DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT2_T29DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T29DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T29DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T29DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T29DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT2_T30DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T30DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T30DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T30DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T30DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT2_T31DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T31DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T31DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T31DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt2 T31DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT3_T32DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T32DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T32DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T32DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T32DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT3_T33DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T33DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T33DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T33DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T33DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT3_T34DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T34DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T34DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T34DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T34DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT3_T35DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T35DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T35DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T35DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T35DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT3_T36DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T36DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T36DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T36DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T36DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT3_T37DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T37DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T37DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T37DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T37DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT3_T38DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T38DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T38DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T38DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T38DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT3_T39DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T39DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T39DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T39DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T39DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT3_T40DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T40DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T40DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T40DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T40DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT3_T41DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T41DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T41DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T41DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T41DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT3_T42DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T42DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T42DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T42DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T42DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT3_T43DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T43DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T43DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T43DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T43DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT3_T44DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T44DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T44DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T44DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T44DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT3_T45DCC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T45DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T45DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T45DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T45DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT3_T46DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T46DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T46DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T46DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T46DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT3_T47DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T47DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T47DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T47DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt3 T47DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT4_T48DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T48DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T48DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T48DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T48DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT4_T49DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T49DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T49DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T48DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T49DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT4_T50DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T50DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T50DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T50DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T50DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT4_T51DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T51DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T51DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T51DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T51DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT4_T52DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T52DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T52DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T52DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T52DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT4_T53DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T53DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T53DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T53DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T53DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT4_T54DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T54DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T54DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T54DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T54DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT4_T55DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T55DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T54DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T54DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T54DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT4_T56DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T56DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T56DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T56DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T56DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT4_T57DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T57DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T57DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T57DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T57DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT4_T58DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T58DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T58DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T58DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T58DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT4_T59DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T59DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T59DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T59DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T59DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT4_T60DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T60DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T60DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T60DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T60DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT4_T61DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T61DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T61DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T61DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T61DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT4_T62DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T62DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T62DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T62DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T62DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT4_T63DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T63DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T63DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T63DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt4 T63DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT5_T64DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt5 T64DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt5 T64DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt5 T64DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt5 T64DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT5_T65DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt5 T65DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt5 T65DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt5 T65DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt5 T65DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_DBCNT5_T66DC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt5 T66DC 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt5 T66DC 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt5 T66DC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl dbcnt5 T66DC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PUDCNT_EMMCNICS()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl pudcnt EMMCNICS 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl pudcnt EMMCNICS 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl pudcnt EMMCNICS 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl pudcnt EMMCNICS 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PUDCNT_EMDATPUE()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl pudcnt EMDATPUE 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl pudcnt EMDATPUE 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PUDCNT_EMCMDPUE()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl pudcnt EMCMDPUE 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl pudcnt EMCMDPUE 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PUDCNT_EMDSPDE()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl pudcnt EMDSPDE 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl pudcnt EMDSPDE 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PUDCNT_NFDATPUE()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl pudcnt NFDATPUE 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl pudcnt NFDATPUE 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PUDCNT_NFRBXPUE()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl pudcnt NFRBXPUE 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl pudcnt NFRBXPUE 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PUDCNT_NFDQSPUE()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl pudcnt NFDQSPUE 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl pudcnt NFDQSPUE 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PUDCNT_SP1MISOPE()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl pudcnt SP1MISOPE 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl pudcnt SP1MISOPE 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PUDCNT_SP1MOSIPE()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl pudcnt SP1MOSIPE 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl pudcnt SP1MOSIPE 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PUDCNT_SP1SCKPE)\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl pudcnt SP1SCKPE 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl pudcnt SP1SCKPE 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PUDCNT_SP1CS0PE()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl pudcnt SP1CS0PE 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl pudcnt SP1CS0PE 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PUDCNT_SP1MISOUDC)\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl pudcnt SP1MISOUDC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl pudcnt SP1MISOUDC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PUDCNT_SP1MOSIUDC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl pudcnt SP1MOSIUDC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl pudcnt SP1MOSIUDC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PUDCNT_SP1SCKUDC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl pudcnt SP1SCKUDC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl pudcnt SP1SCKUDC 0");

	Ddim_Print(("*** [CT] 01-03-%03d : DdTopthree_SET_PUDCNT_SP1CS0UDC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl pudcnt SP1CS0UDC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop lsi set_ctrl pudcnt SP1CS0UDC 0");

}

CtDdTopSecond* ct_dd_top_second_new(void) 
{
    CtDdTopSecond *self = k_object_new_with_private(CT_TYPE_DD_TOP_SECOND, sizeof(CtDdTopSecondPrivate));
    return self;
}
