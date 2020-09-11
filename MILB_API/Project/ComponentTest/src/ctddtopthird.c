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

#include "ctddtopthird.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdTopThird, ct_dd_top_third);
#define CT_DD_TOP_THIRD_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdTopThirdPrivate,CT_TYPE_DD_TOP_THIRD))

struct _CtDdTopThirdPrivate
{
	kint32 seqNo;
};
/****************
* DECLS
*/
static void 			ct_dd_top_third_constructor(CtDdTopThird *self);
static void 			ct_dd_top_third_destructor(CtDdTopThird *self);
/****************
* IMPL
*/
static void ct_dd_top_third_constructor(CtDdTopThird *self) 
{
	CtDdTopThirdPrivate *priv = CT_DD_TOP_THIRD_GET_PRIVATE(self);
    priv->seqNo = 0;
}

static void ct_dd_top_third_destructor(CtDdTopThird *self) 
{
//	CtDdTopThirdPrivate *priv = CT_DD_TOP_THIRD_GET_PRIVATE(self);
}
/****************
* PUBLIC
*/
void ct_dd_top_third_set_seq_no(CtDdTopThird *self,kint32 seqNo)
{
    CtDdTopThirdPrivate *priv = CT_DD_TOP_THIRD_GET_PRIVATE(self);
    priv->seqNo = seqNo;
}

kint32 ct_dd_top_third_get_seq_no(CtDdTopThird *self)
{
    CtDdTopThirdPrivate *priv = CT_DD_TOP_THIRD_GET_PRIVATE(self);
    return priv->seqNo;
}

void ct_dd_top_third_pc_test_main(CtDdTopThird *self)
{
    CtDdTopThirdPrivate *priv = CT_DD_TOP_THIRD_GET_PRIVATE(self);

	Ddim_Print(("*** [CT] 01-04-%03d : CRRSM/CRRRS)\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop reset get");

	Ddim_Print(("*** [CT] 01-04-%03d : DdToptwo_CLEAR_CRRSM_PORST()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop reset set CRRSM_PORST");

	Ddim_Print(("*** [CT] 01-04-%03d : DdToptwo_CLEAR_CRRSM_SRST()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop reset set CRRSM_SRST");

	Ddim_Print(("*** [CT] 01-04-%03d : DdToptwo_CLEAR_CRRSM_SWRST()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop reset set CRRSM_SWRST");

	Ddim_Print(("*** [CT] 01-04-%03d : DdToptwo_CLEAR_CRRSM_WDRST()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop reset set CRRSM_WDRST");

	Ddim_Print(("*** [CT] 01-04-%03d : DdToptwo_CLEAR_CRRRS_CPU0_SR_CLR()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop reset set CRRRS_CPU0_SR_CLR");

	Ddim_Print(("*** [CT] 01-04-%03d : DdToptwo_CLEAR_CRRRS_CPU0_SR_RES()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop reset set CRRRS_CPU0_SR_RES");

	Ddim_Print(("*** [CT] 01-04-%03d : DdToptwo_CLEAR_CRRRS_CPU1_SR_CLR()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop reset set CRRRS_CPU1_SR_CLR");

	Ddim_Print(("*** [CT] 01-04-%03d : DdToptwo_CLEAR_CRRRS_CPU1_SR_RES()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop reset set CRRRS_CPU1_SR_RES");

	Ddim_Print(("*** [CT] 01-04-%03d : DdToptwo_CLEAR_CRRRS_CPU2_SR_CLR()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop reset set CRRRS_CPU2_SR_CLR");

	Ddim_Print(("*** [CT] 01-04-%03d : DdToptwo_CLEAR_CRRRS_CPU2_SR_RES()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop reset set CRRRS_CPU2_SR_RES");

	Ddim_Print(("*** [CT] 01-04-%03d : DdToptwo_CLEAR_CRRRS_CPU3_SR_CLR()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop reset set CRRRS_CPU3_SR_CLR");

	Ddim_Print(("*** [CT] 01-04-%03d : DdToptwo_CLEAR_CRRRS_CPU3_SR_RES()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop reset set CRRRS_CPU3_SR_RES");

	Ddim_Print(("*** [CT] 01-04-%03d : DdToptwo_CLEAR_CRRRS_RIBSR_CLR()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop reset set CRRRS_RIBSR_CLR");

	Ddim_Print(("*** [CT] 01-04-%03d : DdToptwo_CLEAR_CRRRS_RIBSR_RES()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop reset set CRRRS_RIBSR_RES");

	Ddim_Print(("*** [CT] 01-04-%03d : DdToptwo_CLEAR_CRRRS_HEIPPASYNCSR_CLR()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop reset set CRRRS_HEIPPASYNCSR_CLR");

	Ddim_Print(("*** [CT] 01-04-%03d : DdToptwo_CLEAR_CRRRS_HEIPPASYNCSR_RES()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop reset set CRRRS_HEIPPASYNCSR_RES");

	Ddim_Print(("*** [CT] 01-04-%03d : DdToptwo_CLEAR_CRRRS_HEIPPSYNCSR_CLR()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop reset set CRRRS_HEIPPSYNCSR_CLR");

	Ddim_Print(("*** [CT] 01-04-%03d : DdToptwo_CLEAR_CRRRS_HEIPPSYNCSR_CLR()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop reset set CRRRS_HEIPPSYNCSR_CLR");

	Ddim_Print(("*** [CT] 01-04-%03d : DdToptwo_CLEAR_CRRRS_HEVDFSR_CLR()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop reset set CRRRS_HEVDFSR_CLR");

	Ddim_Print(("*** [CT] 01-04-%03d : DdToptwo_CLEAR_CRRRS_HEVDFSR_RES()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop reset set CRRRS_HEVDFSR_RES");

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	Ddim_Print(("*** [CT] 01-04-%03d : DdToptwo_CLEAR_CRRRS_HEPXFSR_CLR()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop reset set CRRRS_HEPXFSR_CLR");

	Ddim_Print(("*** [CT] 01-04-%03d : DdToptwo_CLEAR_CRRRS_HEPXFSR_RES()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop reset set CRRRS_HEPXFSR_RES");
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	Ddim_Print(("*** [CT] 01-04-%03d : DdToptwo_CLEAR_CRRRS_HEVENCSR_CLR()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop reset set CRRRS_HEVENCSR_CLR");

	Ddim_Print(("*** [CT] 01-04-%03d : DdToptwo_CLEAR_CRRRS_HEVENCSR_RES()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop reset set CRRRS_HEVENCSR_RES");
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

	Ddim_Print(("*** [CT] 01-04-%03d : DdToptwo_CLEAR_CRRRS_DSPSR_CLR()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop reset set CRRRS_DSPSR_CLR");

	Ddim_Print(("*** [CT] 01-04-%03d : DdToptwo_CLEAR_CRRRS_DSPSR_RES()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop reset set CRRRS_DSPSR_RES");

	priv->seqNo = 0;
	Ddim_Print(("*** [CT] 01-05-%03d : dd_topthree_start_clock()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock start clkstop1 0 0x30");
	
	Ddim_Print(("*** [CT] 01-05-%03d : dd_topthree_start_clock()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock start clkstop2 0 0x10");

	Ddim_Print(("*** [CT] 01-05-%03d : dd_topthree_start_clock()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock start clkstop3 0 0xF0");

	Ddim_Print(("*** [CT] 01-05-%03d : dd_topthree_start_clock()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock start clkstop4 0 0xF00");

	Ddim_Print(("*** [CT] 01-05-%03d : dd_topthree_start_clock()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock start clkstop5 0 0x10000");

	Ddim_Print(("*** [CT] 01-05-%03d : dd_topthree_start_clock()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock start clkstop6 0 0xD00");

	Ddim_Print(("*** [CT] 01-05-%03d : dd_topthree_start_clock()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock start clkstop7 0 0xD00");

	Ddim_Print(("*** [CT] 01-05-%03d : dd_topthree_start_clock()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock start clkstop8 0 0x30");

	Ddim_Print(("*** [CT] 01-05-%03d : dd_topthree_start_clock()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock start clkstop9 0 0x10");

	Ddim_Print(("*** [CT] 01-05-%03d : dd_topthree_start_clock()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock start clkstop10 0 0xF0");

	Ddim_Print(("*** [CT] 01-05-%03d : dd_topthree_start_clock()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock start clkstop11 0 0xF00");

	Ddim_Print(("*** [CT] 01-05-%03d : dd_topthree_start_clock()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock start clkstop12 0 0x10000");

	Ddim_Print(("*** [CT] 01-05-%03d : dd_topthree_start_clock()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock start clkstop13 0 0xD00");

	Ddim_Print(("*** [CT] 01-05-%03d : dd_topthree_start_clock()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock start clkstop14 0 0xD00");

	Ddim_Print(("*** [CT] 01-05-%03d : dd_topthree_stop_clock()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock stop clkstop1 1 0x30");

	Ddim_Print(("*** [CT] 01-05-%03d : dd_topthree_stop_clock()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock stop clkstop2 1 0x10");

	Ddim_Print(("*** [CT] 01-05-%03d : dd_topthree_stop_clock()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock stop clkstop3 1 0xF0");

	Ddim_Print(("*** [CT] 01-05-%03d : dd_topthree_stop_clock()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock stop clkstop4 1 0xF00");

	Ddim_Print(("*** [CT] 01-05-%03d : dd_topthree_stop_clock()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock stop clkstop5 1 0x10000");

	Ddim_Print(("*** [CT] 01-05-%03d : dd_topthree_stop_clock()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock stop clkstop6 1 0xD00");

	Ddim_Print(("*** [CT] 01-05-%03d : dd_topthree_stop_clock()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock stop clkstop7 1 0xD00");

	Ddim_Print(("*** [CT] 01-05-%03d : dd_topthree_stop_clock()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock stop clkstop8 1 0x30");

	Ddim_Print(("*** [CT] 01-05-%03d : dd_topthree_stop_clock()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock stop clkstop9 1 0x10");

	Ddim_Print(("*** [CT] 01-05-%03d : dd_topthree_stop_clock()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock stop clkstop10 1 0xF0");

	Ddim_Print(("*** [CT] 01-05-%03d : dd_topthree_stop_clock()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock stop clkstop11 1 0xF00");

	Ddim_Print(("*** [CT] 01-05-%03d : dd_topthree_stop_clock()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock stop clkstop12 1 0x10000");

	Ddim_Print(("*** [CT] 01-05-%03d : dd_topthree_stop_clock()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock stop clkstop13 1 0xD00");

	Ddim_Print(("*** [CT] 01-05-%03d : dd_topthree_stop_clock()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock stop clkstop14 1 0xD00");

	Ddim_Print(("*** [CT] 01-05-%03d : dd_topthree_start_clock()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock start clkstop14 1 0xD00");

	Ddim_Print(("*** [CT] 01-05-%03d : dd_topthree_stop_clock()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock stop clkstop14 2 0xD00");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_GET_CLKSEL1()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_reg clksel1");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_GET_CLKSEL2()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_reg clksel2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_GET_CLKSEL3()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_reg clksel3");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_GET_CLKSEL4()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_reg clksel4");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_GET_CLKSEL5()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_reg clksel5");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_GET_CLKSEL6()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_reg clksel6");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_GET_CLKSEL7()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_reg clksel7");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_GET_CLKSEL8()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_reg clksel8");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_GET_CLKSEL9()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_reg clksel9");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_GET_CLKSEL10()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_reg clksel10");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_GET_CLKSEL11()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_reg clksel11");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_GET_CLKSEL12()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_reg clksel12");

	Ddim_Print(("*** [CT] 01-05-%03d : Dd_Top_Get_PLLCNT1_xxxxx()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_reg pllcnt1");

	Ddim_Print(("*** [CT] 01-05-%03d : Dd_Top_Get_PLLCNT2_xxxxx()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_reg pllcnt2");

	Ddim_Print(("*** [CT] 01-05-%03d : Dd_Top_Get_PLLCNT3_xxxxx()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_reg pllcnt3");

	Ddim_Print(("*** [CT] 01-05-%03d : Dd_Top_Get_PLLCNT4_xxxxx()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_reg pllcnt4");

	Ddim_Print(("*** [CT] 01-05-%03d : Dd_Top_Get_PLLCNT5_xxxxx()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_reg pllcnt5");

	Ddim_Print(("*** [CT] 01-05-%03d : Dd_Top_Get_PLLCNT6_xxxxx()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_reg pllcnt6");

	Ddim_Print(("*** [CT] 01-05-%03d : Dd_Top_Get_PLLCNT7_xxxxx()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_reg pllcnt7");

	Ddim_Print(("*** [CT] 01-05-%03d : Dd_Top_Get_PLLCNT8_xxxxx()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_reg pllcnt8");

	Ddim_Print(("*** [CT] 01-05-%03d : Dd_Top_Get_PLLCNT9_xxxxx()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_reg pllcnt9");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_GET_CLKSTOP1_xxxxx()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_reg clkstop1");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_GET_CLKSTOP2_xxxxx()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_reg clkstop2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_GET_CLKSTOP3_xxxxx()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_reg clkstop3");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_GET_CLKSTOP4_xxxxx()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_reg clkstop4");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_GET_CLKSTOP5_xxxxx()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_reg clkstop5");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_GET_CLKSTOP6_xxxxx()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_reg clkstop6");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_GET_CLKSTOP7_xxxxx()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_reg clkstop7");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_GET_CLKSTOP8_xxxxx()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_reg clkstop8");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_GET_CLKSTOP9_xxxxx()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_reg clkstop9");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_GET_CLKSTOP10_xxxxx()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_reg clkstop10");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_GET_CLKSTOP11_xxxxx()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_reg clkstop11");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_GET_CLKSTOP12_xxxxx()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_reg clkstop12");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_GET_CLKSTOP13_xxxxx()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_reg clkstop13");

	Ddim_Print(("*** [CT] 01-05-%03d : DdToptwo_GET_CLKSTOP14_xxxxx()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_reg clkstop14");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL1_RCLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel1 RCLK 7");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel1 RCLK 4");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL1_UHS1CLK0()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel1 UHS1CLK0 31");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel1 UHS1CLK0 16");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL1_UHS1CLK1()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel1 UHS1CLK1 31");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel1 UHS1CLK1 16");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL1_UHS1CLK2()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel1 UHS1CLK2 31");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel1 UHS1CLK2 16");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL1_UHS2CLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel1 UHS2CLK 15");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel1 UHS2CLK 8");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL1_NFCLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel1 NFCLK 63");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel1 NFCLK 32");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL1_EMMCCLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel1 EMMCCLK 7");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel1 EMMCCLK 4");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL2_ELACLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel2 ELACLK 15");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel2 ELACLK 8");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL2_JPGCLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel2 ELACLK 15");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel2 ELACLK 8");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL2_GPUCLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel2 GPUCLK 15");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel2 GPUCLK 8");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL2_IPUTMECLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel2 IPUTMECLK 15");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel2 IPUTMECLK 8");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL2_IPUCLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel2 IPUCLK 15");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel2 IPUCLK 8");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL2_MIFCLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel2 MIFCLK 15");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel2 MIFCLK 8");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL2_HIFCLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel2 HIFCLK 15");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel2 HIFCLK 8");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL2_RAWCLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel2 RAWCLK 7");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel2 RAWCLK 4");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL3_VDFCLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel3 VDFCLK 15");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel3 VDFCLK 8");

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL3_PXFCLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel3 PXFCLK 15");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel3 PXFCLK 8");
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL3_HEVENCCLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel3 HEVENCCLK 15");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel3 HEVENCCLK 8");
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL3_IPPCLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel3 IPPCLK 31");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel3 IPPCLK 16");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL3_PASCLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel3 PASCLK 15");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel3 PASCLK 8");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL3_IIPCLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel3 IIPCLK 15");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel3 IIPCLK 8");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL3_SENMSKCLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel3 SENMSKCLK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel3 SENMSKCLK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL3_SENCLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel3 SENCLK 15");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel3 SENCLK 8");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL3_PIPESEL()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel3 PIPESEL 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel3 PIPESEL 2");

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL3_HEVENCSEL()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel3 HEVENCSEL 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel3 HEVENCSEL 2");
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL4_CNR1CLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel4 CNR1CLK 127");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel4 CNR1CLK 64");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL4_B2R1CLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel4 B2R1CLK 127");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel4 B2R1CLK 64");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL4_LTM1CLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel4 LTM1CLK 127");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel4 LTM1CLK 64");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL4_R2Y1CLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel4 R2Y1CLK 127");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel4 R2Y1CLK 64");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL4_SRO1CLK_2()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel4 SRO1CLK_2 15");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel4 SRO1CLK_2 8");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL5_LTMRBK1CLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel5 LTMRBK1CLK 63");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel5 LTMRBK1CLK 32");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL5_B2B1CLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel5 B2B1CLK 63");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel5 B2B1CLK 32");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL5_SRO1CLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel5 SRO1CLK 31");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel5 SRO1CLK 16");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL6_CNR2CLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel6 CNR2CLK 127");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel6 CNR2CLK 64");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL6_B2R2CLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel6 B2R2CLK 127");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel6 B2R2CLK 64");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL6_LTM2CLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel6 LTM2CLK 127");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel6 LTM2CLK 64");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL6_R2Y2CLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel6 R2Y2CLK 127");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel6 R2Y2CLK 64");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL6_SRO2CLK_2()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel6 SRO2CLK_2 15");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel6 SRO2CLK_2 8");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL7_LTMRBK2CLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel7 LTMRBK2CLK 63");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel7 LTMRBK2CLK 32");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL7_B2B2CLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel7 B2B2CLK 63");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel7 B2B2CLK 32");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL7_SRO2CLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel7 SRO2CLK 31");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel7 SRO2CLK 16");

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL7_MIPISEL()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel7 MIPISEL 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel7 MIPISEL 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL7_PDM0SEL()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel7 PDM0SEL 7");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel7 PDM0SEL 4");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL7_PDM1SEL()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel7 PDM1SEL 7");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel7 PDM1SEL 4");
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL8_DSPCLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel8 DSPCLK 7");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel8 DSPCLK 4");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL8_SPICLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel8 SPICLK 7");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel8 SPICLK 4");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL8_AUCLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel8 AUCLK 7");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel8 AUCLK 4");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL8_AU0SEL()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel8 AU0SEL 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel8 AU0SEL 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL8_AU2SEL()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel8 AU2SEL 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel8 AU2SEL 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL8_AU3SEL()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel8 AU3SEL 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel8 AU3SEL 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL8_NETAUSEL()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel8 NETAUSEL 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel8 NETAUSEL 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL8_APCLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel8 APCLK 63");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel8 APCLK 32");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL8_AP0SEL()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel8 AP0SEL 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel8 AP0SEL 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL8_AP1SEL()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel8 AP1SEL 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel8 AP1SEL 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL8_AP2SEL()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel8 AP2SEL 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel8 AP2SEL 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL8_AP3SEL()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel8 AP3SEL 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel8 AP3SEL 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL9_PCLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel9 PCLK 127");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel9 PCLK 64");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL9_HCLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel9 HCLK 31");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel9 HCLK 16");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL9_HCLKBMH()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel9 HCLKBMH 15");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel9 HCLKBMH 8");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL9_ACLKEXS()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel9 ACLKEXS 15");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel9 ACLKEXS 8");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL9_ACLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel9 ACLK 15");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel9 ACLK 8");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL10_ACLK400()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel10 ACLK400 7");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel10 ACLK400 4");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL10_MCLK200()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel10 MCLK200 15");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel10 MCLK200 8");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL10_MCLK400()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel10 MCLK400 7");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel10 MCLK400 4");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL11_DCHREQ()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel11 DCHREQ 1");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL12_ACLK300()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel12 ACLK300 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel12 ACLK300 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL12_GYROCLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel12 GYROCLK 7");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel12 GYROCLK 4");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL12_SHDRCLK()\n", priv->seqNo++));
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel12 SHDRCLK 15");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel12 SHDRCLK 8");
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel12 SHDRCLK 31");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel12 SHDRCLK 16");
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL12_FPT0CLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel12 FPT0CLK 15");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel12 FPT0CLK 8");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL12_FPT1CLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel12 FPT1CLK 15");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel12 FPT1CLK 8");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL12_MECLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel12 MECLK 7");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel12 MECLK 4");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL12_NFBCHCLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel12 NFBCHCLK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel12 NFBCHCLK 2");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_CLKSEL12_RIBCLK()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel12 RIBCLK 31");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg clksel12 RIBCLK 16");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT1_PL00ST()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt1 PL00ST 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt1 PL00ST 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT1_PL01ST()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt1 PL01ST 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt1 PL01ST 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT1_PL02ST()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt1 PL02ST 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt1 PL02ST 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT1_PL03ST()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt1 PL03ST 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt1 PL03ST 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT1_PL04ST()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt1 PL04ST 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt1 PL04ST 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT1_PL05ST()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt1 PL05ST 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt1 PL05ST 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT1_PL05AST()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt1 PL05AST 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt1 PL05AST 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT1_PL06ST()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt1 PL06ST 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt1 PL06ST 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT1_PL07ST()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt1 PL07ST 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt1 PL07ST 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT1_PL08ST()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt1 PL08ST 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt1 PL08ST 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT1_PL10ST()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt1 PL10ST 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt1 PL10ST 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT1_PL10AST()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt1 PL10AST 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt1 PL10AST 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT1_PL11ST()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt1 PL11ST 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt1 PL11ST 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT1_DPL00ST()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt1 DPL00ST 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt1 DPL00ST 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT1_DPL01ST()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt1 DPL01ST 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt1 DPL01ST 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT1_DPL02ST()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt1 DPL02ST 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt1 DPL02ST 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT1_DPL10ST()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt1 DPL10ST 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt1 DPL10ST 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT1_DPL11ST()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt1 DPL11ST 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt1 DPL11ST 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT1_DPL12ST()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt1 DPL12ST 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt1 DPL12ST 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT2_PL00SEL()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt2 PL00SEL 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt2 PL00SEL 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT2_PL01SEL()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt2 PL01SEL 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt2 PL01SEL 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT2_PL02SEL()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt2 PL02SEL 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt2 PL02SEL 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT2_PL03SEL()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt2 PL03SEL 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt2 PL03SEL 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT2_PL04SEL()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt2 PL04SEL 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt2 PL04SEL 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT2_PL05SEL()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt2 PL05SEL 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt2 PL05SEL 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT2_PL05ASEL()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt2 PL05ASEL 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt2 PL05ASEL 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT2_PL06SEL()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt2 PL06SEL 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt2 PL06SEL 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT2_PL07SEL()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt2 PL07SEL 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt2 PL07SEL 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT2_PL08SEL()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt2 PL08SEL 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt2 PL08SEL 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT2_PL10SEL()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt2 PL10SEL 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt2 PL10SEL 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT2_PL10ASEL()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt2 PL10ASEL 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt2 PL10ASEL 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT2_PL11SEL()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt2 PL11SEL 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt2 PL11SEL 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT2_PL01SSEN()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt2 PL01SSEN 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt2 PL01SSEN 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT2_PL02SSEN()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt2 PL02SSEN 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt2 PL02SSEN 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT3_P00POSTDIV()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt3 P00POSTDIV 255");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt3 P00POSTDIV 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT3_P00PREDIV()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt3 P00PREDIV 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt3 P00PREDIV 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT3_P00PLLDIV()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt3 P00PLLDIV 255");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt3 P00PLLDIV 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT3_P00PLLDIV()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt3 P00PLLDIV 255");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt3 P00PLLDIV 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT4_P00FNUM()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt4 P00FNUM -1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt4 P00FNUM 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT5_P00FDEN()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt5 P00FDEN -1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt5 P00FDEN 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT6_P01RATE()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt6 P01RATE 164");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt6 P01RATE 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT6_P01FREQ()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt6 P01FREQ 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt6 P01FREQ 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT6_P01MODE()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt6 P01MODE 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt6 P01MODE 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT6_P02RATE()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt6 P02RATE 164");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt6 P02RATE 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT6_P02FREQ()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt6 P02FREQ 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt6 P02FREQ 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT6_P02MODE()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt6 P02MODE 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt6 P02MODE 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT7_P03POSTDIV0()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt7 P03POSTDIV0 8");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt7 P03POSTDIV0 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT7_P03POSTDIV1()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt7 P03POSTDIV1 8");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt7 P03POSTDIV1 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT7_P03PREDIV()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt7 P03PREDIV 5");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt7 P03PREDIV 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT7_P03PLLDIV()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt7 P03PLLDIV 149");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt7 P03PLLDIV 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT7_P03OC0()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt7 P03OC0 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt7 P03OC0 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT7_P03OC1()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt7 P03OC1 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt7 P03OC1 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT7_D0XOC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt7 D0XOC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt7 D0XOC 0");

	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT7_D1XOC()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt7 D1XOC 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt7 D1XOC 0");

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	Ddim_Print(("*** [CT] 01-05-%03d : DdTopone_SET_PLLCNT7_DPLX8()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt7 DPLX8 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock set_reg pllcnt7 DPLX8 0");

// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
}

CtDdTopThird* ct_dd_top_third_new(void) 
{
    CtDdTopThird *self = k_object_new_with_private(CT_TYPE_DD_TOP_THIRD, sizeof(CtDdTopThirdPrivate));
    return self;
}