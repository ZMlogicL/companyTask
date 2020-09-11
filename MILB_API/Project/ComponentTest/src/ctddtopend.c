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

#include "ctddtopend.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdTopEnd, ct_dd_top_end);
#define CT_DD_TOP_END_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdTopEndPrivate,CT_TYPE_DD_TOP_END))

struct _CtDdTopEndPrivate
{
	kint32 seqNo;
};
/****************
* DECLS
*/
static void 			ct_dd_top_end_constructor(CtDdTopEnd *self);
static void 			ct_dd_top_end_destructor(CtDdTopEnd *self) ;
/****************
* IMPL
*/
static void ct_dd_top_end_constructor(CtDdTopEnd *self) 
{
	// CtDdTopEndPrivate *priv = CT_DD_TOP_END_GET_PRIVATE(self);
}

static void ct_dd_top_end_destructor(CtDdTopEnd *self) 
{
//	CtDdTopEndPrivate *priv = CT_DD_TOP_END_GET_PRIVATE(self);
}
/****************
* PUBLIC
*/
void ct_dd_top_end_set_seq_no(CtDdTopEnd *self,kint32 seqNo)
{
    CtDdTopEndPrivate *priv = CT_DD_TOP_END_GET_PRIVATE(self);
    priv->seqNo = seqNo;
}

kint32 ct_dd_top_end_get_seq_no(CtDdTopEnd *self)
{
    CtDdTopEndPrivate *priv = CT_DD_TOP_END_GET_PRIVATE(self);
    return priv->seqNo;
}

void ct_dd_top_end_pc_test_main(CtDdTopEnd *self)
{
    CtDdTopEndPrivate *priv = CT_DD_TOP_END_GET_PRIVATE(self);
    
	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT7_DSEL()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt7 DSEL 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt7 DSEL 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT8_P04POSTDIV()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt8 P04POSTDIV 254");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt8 P04POSTDIV 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT8_P04PREDIV()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt8 P04PREDIV 5");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt8 P04PREDIV 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT8_P04PLLDIV()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt8 P04PLLDIV 149");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt8 P04PLLDIV 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT9_P10APLLDIV()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt9 P10APLLDIV 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt9 P10APLLDIV 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT9_P08PLLDIV()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt9 P08PLLDIV 74");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt9 P08PLLDIV 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT9_P05CHG()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt9 P05CHG 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt9 P05CHG 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP1_DSPCK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP1 DSPCK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP1 DSPCK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP1_DSPAX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP1 DSPAX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP1 DSPAX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP1_SENCK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP1 SENCK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP1 SENCK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP1_SENAX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP1 SENAX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP1 SENAX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP1_SENAH()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP1 SENAH 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP1 SENAH 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP1_SENAP()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP1 SENAP 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP1 SENAP 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP1_GPIOAP()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP1 GPIOAP 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP1 GPIOAP 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP1_AU0CK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP1 AU0CK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP1 AU0CK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP1_AU2CK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP1 AU2CK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP1 AU2CK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP1_AU3CK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP1 AU3CK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP1 AU3CK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP1_AU4CK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP1 AU4CK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP1 AU4CK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP1_AU5CK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP1 AU5CK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP1 AU5CK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP1_NETAUCK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP1 NETAUCK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP1 NETAUCK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP1_TEMPCK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP1 TEMPCK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP1 TEMPCK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP2_RCK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP2 RCK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP2 RCK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP2_UHS1CK0()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP2 UHS1CK0 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP2 UHS1CK0 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP2_UHS1CK1()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP2 UHS1CK1 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP2 UHS1CK1 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP2_UHS1CK2()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP2 UHS1CK2 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP2 UHS1CK2 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP2_UHS2CK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP2 UHS2CK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP2 UHS2CK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP2_NFCK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP2 NFCK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP2 NFCK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP2_EMMCCK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP2 EMMCCK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP2 EMMCCK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP2_NETSECCK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP2 NETSECCK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP2 NETSECCK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP2_NETRCK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP2 NETRCK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP2 NETRCK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP2_EXSAX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP2 EXSAX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP2 EXSAX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP2_SPICK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP2 SPICK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP2 SPICK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP2_SLIMB00CK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP2 SLIMB00CK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP2 SLIMB00CK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP2_SLIMB01CK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP2 SLIMB01CK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP2 SLIMB01CK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP2_SLIMB10CK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP2 SLIMB10CK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP2 SLIMB10CK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP2_SLIMB11CK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP2 SLIMB11CK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP2 SLIMB11CK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP2_PCISUPPCK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP2 PCISUPPCK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP2 PCISUPPCK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP3_IIPCK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP3 IIPCK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP3 IIPCK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP3_IIPAP()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP3 IIPAP 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP3 IIPAP 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP3_IIPAH()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP3 IIPAH 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP3 IIPAH 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP3_IIPAX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP3 IIPAX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP3 IIPAX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP3_LCDCK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP3 LCDCK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP3 LCDCK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP3_HIFCK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP3 HIFCK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP3 HIFCK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP3_MIFCK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP3 MIFCK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP3 MIFCK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP3_DISPAP()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP3 DISPAP 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP3 DISPAP 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP3_DISPAH()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP3 DISPAH 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP3 DISPAH 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP3_DISPAX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP3 DISPAX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP3 DISPAX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP3_JPGCK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP3 JPGCK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP3 JPGCK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP3_JPGAP()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP3 JPGAP 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP3 JPGAP 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP3_JPGAH()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP3 JPGAH 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP3 JPGAH 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP3_JPGAX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP3 JPGAX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP3 JPGAX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP3_PDM0CK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP3 PDM0CK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP3 PDM0CK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP3_PDM1CK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP3 PDM1CK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP3 PDM1CK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP4_GPUCK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP4 GPUCK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP4 GPUCK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP4_GPUAP()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP4 GPUAP 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP4 GPUAP 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP4_GPUCK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP4 GPUAH 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP4 GPUAH 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP4_GPUCK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP4 GPUAX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP4 GPUAX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP4_FPT0CK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP4 FPT0CK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP4 FPT0CK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP4_FPT0AP()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP4 FPT0AP 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP4 FPT0AP 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP4_FPT0AH()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP4 FPT0AH 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP4 FPT0AH 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP4_FPT0AX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP4 FPT0AX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP4 FPT0AX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP4_FPT1CK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP4 FPT1CK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP4 FPT1CK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP4_FPT1AP()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP4 FPT1AP 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP4 FPT1AP 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP4_FPT1AH()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP4 FPT1AH 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP4 FPT1AH 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP4_FPT1AX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP4 FPT1AX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP4 FPT1AX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP4_APCK0()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP4 APCK0 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP4 APCK0 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP4_APCK1()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP4 APCK1 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP4 APCK1 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP4_APCK2()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP4 APCK2 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP4 APCK2 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP4_APCK3()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP4 APCK3 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP4 APCK3 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP5_MICAX0()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP5 MICAX0 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP5 MICAX0 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP5_MICAX1()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP5 MICAX1 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP5 MICAX1 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP5_MICAX2()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP5 MICAX2 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP5 MICAX2 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP5_MICAX3()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP5 MICAX3 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP5 MICAX3 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP5_MICAX4()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP5 MICAX4 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP5 MICAX4 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP5_MICAX5()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP5 MICAX5 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP5 MICAX5 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP5_MICAX6()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP5 MICAX6 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP5 MICAX6 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP5_MICAP0()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP5 MICAP0 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP5 MICAP0 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP5_MICAP1()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP5 MICAP1 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP5 MICAP1 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP5_MICAP2()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP5 MICAP2 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP5 MICAP2 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP5_MICAP3()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP5 MICAP3 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP5 MICAP3 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP5_MICAP4()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP5 MICAP4 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP5 MICAP4 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP5_MICAP5()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP5 MICAP5 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP5 MICAP5 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP5_MICAP6()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP5 MICAP6 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP5 MICAP6 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP6_MICAH1()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP6 MICAH1 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP6 MICAH1 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP6_MICAH2()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP6 MICAH2 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP6 MICAH2 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP6_MICAH3()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP6 MICAH3 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP6 MICAH3 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP6_IMGAX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP6 IMGAX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP6 IMGAX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP6_IMGAH0()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP6 IMGAH0 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP6 IMGAH0 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP6_IMGAH1()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP6 IMGAH1 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP6 IMGAH1 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP6_IMGAH3()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP6 IMGAH3 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP6 IMGAH3 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP6_IMGAP3()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP6 IMGAP3 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP6 IMGAP3 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP6_REGAP()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP6 REGAP 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP6 REGAP 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP6_XCHAX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP6 XCHAX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP6 XCHAX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP6_XCHAP()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP6 XCHAP 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP6 XCHAP 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP6_ELACK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP6 ELACK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP6 ELACK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP6_ELAAX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP6 ELAAX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP6 ELAAX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP6_ELAAP()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP6 ELAAP 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP6 ELAAP 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP7_IPUFDCK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP7 IPUFDCK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP7 IPUFDCK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP7_IPUVISCK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP7 IPUVISCK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP7 IPUVISCK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP7_IPUAX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP7 IPUAX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP7 IPUAX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP7_IPUAH()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP7 IPUAH 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP7 IPUAH 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP7_RAWCK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP7 RAWCK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP7 RAWCK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP7_RAWAX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP7 RAWAX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP7 RAWAX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP7_RAWAP()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP7 RAWAP 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP7 RAWAP 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP7_SHDRCK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP7 SHDRCK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP7 SHDRCK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP7_SHDRAX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP7 SHDRAX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP7 SHDRAX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP7_SHDRAH()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP7 SHDRAH 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP7 SHDRAH 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP7_SHDRAP()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP7 SHDRAP 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP7 SHDRAP 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP7_M0CK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP7 M0CK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP7 M0CK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP7_MECK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP7 MECK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP7 MECK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP7_MEAX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP7 MEAX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP7 MEAX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP7_MEAP()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP7 MEAP 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP7 MEAP 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP8_RIBCK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP8 RIBCK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP8 RIBCK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP8_RIBAH()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP8 RIBAH 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP8 RIBAH 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP8_HEVDFCK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP8 HEVDFCK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP8 HEVDFCK 2");

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP8_HEPXFCK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP8 HEPXFCK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP8 HEPXFCK 2");
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP8_HEVENCCK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP8 HEVENCCK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP8 HEVENCCK 2");
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP8_HEIPPCK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP8 HEIPPCK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP8 HEIPPCK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP8_UMC0HEVCMX2()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP8 UMC0HEVCMX2 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP8 UMC0HEVCMX2 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP8_UMC0HEVCMX4()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP8 UMC0HEVCMX4 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP8 UMC0HEVCMX4 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP8_UMC0RBRMX4()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP8 UMC0RBRMX4 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP8 UMC0RBRMX4 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP8_UMC1HEVCMX2()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP8 UMC1HEVCMX2 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP8 UMC1HEVCMX2 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP8_UMC1HEVCMX4()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP8 UMC1HEVCMX4 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP8 UMC1HEVCMX4 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP8_UMC1RBRMX4()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP8 UMC1RBRMX4 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP8 UMC1RBRMX4 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP8_UMC0CMNAX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP8 UMC0CMNAX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP8 UMC0CMNAX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP8_UMC0MX1AX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP8 UMC0MX1AX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP8 UMC0MX1AX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP8_UMC0MX2AX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP8 UMC0MX2AX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP8 UMC0MX2AX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP8_UMC0MX3AX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP8 UMC0MX3AX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP8 UMC0MX3AX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP8_UMC0MX4AX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP8 UMC0MX4AX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP8 UMC0MX4AX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP9_UMC0MX5AX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP9 UMC0MX5AX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP9 UMC0MX5AX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP9_UMC1CMNAX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP9 UMC1CMNAX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP9 UMC1CMNAX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP9_UMC1MX1AX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP9 UMC1MX1AX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP9 UMC1MX1AX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP9_UMC1MX2AX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP9 UMC1MX2AX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP9 UMC1MX2AX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP9_UMC1MX3AX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP9 UMC1MX3AX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP9 UMC1MX3AX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP9_UMC1MX4AX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP9 UMC1MX4AX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP9 UMC1MX4AX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP9_UMC1MX5AX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP9 UMC1MX5AX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP9 UMC1MX5AX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP9_UMC0MX0AX3()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP9 UMC0MX0AX3 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP9 UMC0MX0AX3 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP9_UMC0MX6AX4()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP9 UMC0MX6AX4 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP9 UMC0MX6AX4 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP9_UMC0HEVCAX4()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP9 UMC0HEVCAX4 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP9 UMC0HEVCAX4 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP9_UMC1MX0AX3()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP9 UMC1MX0AX3 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP9 UMC1MX0AX3 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP9_UMC1MX6AX4()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP9 UMC1MX6AX4 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP9 UMC1MX6AX4 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP9_UMC1HEVCAX4()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP9 UMC1HEVCAX4 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP9 UMC1HEVCAX4 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP9_UMC0AP()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP9 UMC0AP 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP9 UMC0AP 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP9_UMC1AP()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP9 UMC1AP 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP9 UMC1AP 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP10_SRO1CK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP10 SRO1CK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP10 SRO1CK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP10_SRO1CK_2()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP10 SRO1CK_2 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP10 SRO1CK_2 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP10_SRO1AX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP10 SRO1AX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP10 SRO1AX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP10_SRO1AH()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP10 SRO1AH 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP10 SRO1AH 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP10_SRO1AP()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP10 SRO1AP 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP10 SRO1AP 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP10_B2B1CK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP10 B2B1CK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP10 B2B1CK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP10_B2B1AX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP10 B2B1AX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP10 B2B1AX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP10_B2B1AH()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP10 B2B1AH 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP10 B2B1AH 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP10_B2B1AP()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP10 B2B1AP 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP10 B2B1AP 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP10_LTMRBK1CK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP10 LTMRBK1CK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP10 LTMRBK1CK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP10_B2R1CK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP10 B2R1CK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP10 B2R1CK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP10_B2R1AX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP10 B2R1AX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP10 B2R1AX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP10_B2R1AH()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP10 B2R1AH 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP10 B2R1AH 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP10_B2R1AP()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP10 B2R1AP 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP10 B2R1AP 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP11_LTM1CK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP11 LTM1CK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP11 LTM1CK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP11_LTM1AX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP11 LTM1AX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP11 LTM1AX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP11_LTM1AH()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP11 LTM1AH 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP11 LTM1AH 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP11_LTM1AP()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP11 LTM1AP 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP11 LTM1AP 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP11_R2Y1CK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP11 R2Y1CK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP11 R2Y1CK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP11_R2Y1AX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP11 R2Y1AX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP11 R2Y1AX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP11_R2Y1AH()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP11 R2Y1AH 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP11 R2Y1AH 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP11_R2Y1AP()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP11 R2Y1AP 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP11 R2Y1AP 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP11_CNR1CK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP11 CNR1CK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP11 CNR1CK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP11_CNR1AX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP11 CNR1AX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP11 CNR1AX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP11_CNR1AP()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP11 CNR1AP 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP11 CNR1AP 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP11_APAH()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP11 APAH 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP11 APAH 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP11_DBGAP()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP11 DBGAP 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP11 DBGAP 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP11_NFBCHCK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP11 NFBCHCK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP11 NFBCHCK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP12_SRO2CK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP12 SRO2CK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP12 SRO2CK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP12_SRO2CK_2()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP12 SRO2CK_2 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP12 SRO2CK_2 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP12_SRO2AX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP12 SRO2AX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP12 SRO2AX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP12_SRO2AH()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP12 SRO2AH 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP12 SRO2AH 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP12_SRO2AP()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP12 SRO2AP 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP12 SRO2AP 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP12_B2B2CK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP12 B2B2CK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP12 B2B2CK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP12_B2B2AX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP12 B2B2AX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP12 B2B2AX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP12_B2B2AH()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP12 B2B2AH 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP12 B2B2AH 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP12_B2B2AP()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP12 B2B2AP 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP12 B2B2AP 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP12_LTMRBK2CK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP12 LTMRBK2CK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP12 LTMRBK2CK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP12_B2R2CK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP12 B2R2CK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP12 B2R2CK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP12_B2R2AX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP12 B2R2AX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP12 B2R2AX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP12_B2R2AH()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP12 B2R2AH 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP12 B2R2AH 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP12_B2R2AP()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP12 B2R2AP 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP12 B2R2AP 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP13_LTM2CK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP13 LTM2CK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP13 LTM2CK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP13_LTM2AX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP13 LTM2AX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP13 LTM2AX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP13_LTM2AH()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP13 LTM2AH 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP13 LTM2AH 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP13_LTM2AP()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP13 LTM2AP 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP13 LTM2AP 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP13_R2Y2CK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP13 R2Y2CK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP13 R2Y2CK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP13_R2Y2AX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP13 R2Y2AX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP13 R2Y2AX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP13_R2Y2AH()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP13 R2Y2AH 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP13 R2Y2AH 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP13_R2Y2AP()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP13 R2Y2AP 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP13 R2Y2AP 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP13_CNR2CK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP13 CNR2CK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP13 CNR2CK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP13_CNR2AX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP13 CNR2AX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP13 CNR2AX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP13_CNR2AP()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP13 CNR2AP 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP13 CNR2AP 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP13_UMCVDFMX4()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP13 UMCVDFMX4 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP13 UMCVDFMX4 2");

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP13_UMCPXFMX4()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP13 UMCPXFMX4 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP13 UMCPXFMX4 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP13_UMCVDFMX2()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP13 UMCVDFMX2 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP13 UMCVDFMX2 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP13_UMCPXFMX2()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP13 UMCPXFMX2 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP13 UMCPXFMX2 2");
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP13_UMCHEVENCAX4()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP13 UMCHEVENCAX4 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP13 UMCHEVENCAX4 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP13_UMCVDFMX2()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP13 UMCVDFMX2 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP13 UMCVDFMX2 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP13_HEVENCAP()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP13 HEVENCAP 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP13 HEVENCAP 2");
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP13_BMH1CK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP13 BMH1CK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP13 BMH1CK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP14_STATAX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP14 STATAX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP14 STATAX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP14_STATAH()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP14 STATAH 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP14 STATAH 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP14_STATAP()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP14 STATAP 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP14 STATAP 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP14_PERIAH()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP14 PERIAH 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP14 PERIAH 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP14_PERIAP()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP14 PERIAP 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP14 PERIAP 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP14_SENMSKCK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP14 SENMSKCK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP14 SENMSKCK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP14_GYROCK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP14 GYROCK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP14 GYROCK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP14_EXSAH()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP14 EXSAH 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP14 EXSAH 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP14_EXSAP()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP14 EXSAP 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP14 EXSAP 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP14_PASCK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP14 PASCK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP14 PASCK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP14_BMH0CK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP14 BMH0CK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP14 BMH0CK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP14_BMH0AX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP14 BMH0AX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP14 BMH0AX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP14_RDMAAX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP14 RDMAAX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP14 RDMAAX 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP14_RDMAAP()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP14 RDMAAP 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP14 RDMAAP 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_SET_CLKSTOP14_BMH1AX()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP14 BMH1AX 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg CLKSTOP14 BMH1AX 2");

	Ddim_Print(("*** [CT] 01-06-001 - 005\n"));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop gpio test");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop gpio err");
}

CtDdTopEnd* ct_dd_top_end_new(void) 
{
    CtDdTopEnd *self = k_object_new_with_private(CT_TYPE_DD_TOP_END, sizeof(CtDdTopEndPrivate));
    return self;
}