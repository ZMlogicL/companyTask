/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-03
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
#include "../../DeviceDriver/LSITop/src/ddtop.h"
#include "../../DeviceDriver/LSITop/src/ddtopfour.h"
#include "../../DeviceDriver/LSITop/src/ddtopone.h"
#include "../../DeviceDriver/LSITop/src/ddtopthree.h"
#include "../../DeviceDriver/LSITop/src/ddtoptwo.h"
#include "ctclockpllcnt.h"
#include"ctclockclkstop.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtClockPllcnt, ct_clock_pllcnt);
#define CT_CLOCK_PLLCNT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtClockPllcntPrivate,CT_TYPE_CLOCK_PLLCNT))

struct _CtClockPllcntPrivate
{
	CtClockClkstop *ctClockClkstop;
};
/****************
* DECLS
*/
static void 			ct_clock_pllcnt_constructor(CtClockPllcnt *self);
static void 			ct_clock_pllcnt_destructor(CtClockPllcnt *self);
static void 			ctGetClockPllcnt1(void);
static void 			ctGetClockPllcnt2(void);
static void 			ctGetClockPllcnt3(void);
static void 			ctGetClockPllcnt4(void);
static void 			ctGetClockPllcnt5(void);
static void 			ctGetClockPllcnt6(void);
static void 			ctGetClockPllcnt7(void);
static void 			ctGetClockPllcnt8(void);
static void 			ctGetClockPllcnt9(void);
static void 			ctSetClockPllcnt1(kint argc, kchar** argv);
static void 			ctSetClockPllcnt2(kint argc, kchar** argv);
static void 			ctSetClockPllcnt3(kint argc, kchar** argv);
static void 			ctSetClockPllcnt4(kint argc, kchar** argv);
static void 			ctSetClockPllcnt5(kint argc, kchar** argv);
static void 			ctSetClockPllcnt6(kint argc, kchar** argv);
static void 			ctSetClockPllcnt7(kint argc, kchar** argv);
static void 			ctSetClockPllcnt8(kint argc, kchar** argv);
static void 			ctSetClockPllcnt9(kint argc, kchar** argv);
/****************
* IMPL
*/
static void ct_clock_pllcnt_constructor(CtClockPllcnt *self) 
{
	CtClockPllcntPrivate *priv = CT_CLOCK_PLLCNT_GET_PRIVATE(self);
	priv->ctClockClkstop = ct_clock_clkstop_new();
}

static void ct_clock_pllcnt_destructor(CtClockPllcnt *self) 
{
	CtClockPllcntPrivate *priv = CT_CLOCK_PLLCNT_GET_PRIVATE(self);
	k_object_unref(priv->ctClockClkstop);
}

static void ctGetClockPllcnt1(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.PL00ST		= 1;
	IO_CHIPTOP.PLLCNT1.bit.PL01ST		= 1;
	IO_CHIPTOP.PLLCNT1.bit.PL02ST		= 1;
	IO_CHIPTOP.PLLCNT1.bit.PL03ST		= 1;
	IO_CHIPTOP.PLLCNT1.bit.PL04ST		= 1;
	IO_CHIPTOP.PLLCNT1.bit.PL05ST		= 1;
	IO_CHIPTOP.PLLCNT1.bit.PL05AST		= 1;
	IO_CHIPTOP.PLLCNT1.bit.PL06ST		= 1;
	IO_CHIPTOP.PLLCNT1.bit.PL07ST		= 1;
	IO_CHIPTOP.PLLCNT1.bit.PL08ST		= 1;
	IO_CHIPTOP.PLLCNT1.bit.PL10ST		= 1;
	IO_CHIPTOP.PLLCNT1.bit.PL10AST		= 1;
	IO_CHIPTOP.PLLCNT1.bit.PL11ST		= 1;
	IO_CHIPTOP.PLLCNT1.bit.DPL00ST		= 1;
	IO_CHIPTOP.PLLCNT1.bit.DPL01ST		= 1;
	IO_CHIPTOP.PLLCNT1.bit.DPL02ST		= 1;
	IO_CHIPTOP.PLLCNT1.bit.DPL10ST		= 1;
	IO_CHIPTOP.PLLCNT1.bit.DPL11ST		= 1;
	IO_CHIPTOP.PLLCNT1.bit.DPL12ST		= 1;
#endif

	Ddim_Print(("PLLCNT1_PL00ST	= %d\n", DdTopone_GET_PLLCNT1_PL00ST()));
	Ddim_Print(("PLLCNT1_PL01ST	= %d\n", DdTopone_GET_PLLCNT1_PL01ST()));
	Ddim_Print(("PLLCNT1_PL02ST	= %d\n", DdTopone_GET_PLLCNT1_PL02ST()));
	Ddim_Print(("PLLCNT1_PL03ST	= %d\n", DdTopone_GET_PLLCNT1_PL03ST()));
	Ddim_Print(("PLLCNT1_PL04ST	= %d\n", DdTopone_GET_PLLCNT1_PL04ST()));
	Ddim_Print(("PLLCNT1_PL05ST	= %d\n", DdTopone_GET_PLLCNT1_PL05ST()));
	Ddim_Print(("PLLCNT1_PL05AST	= %d\n", DdTopone_GET_PLLCNT1_PL05AST()));
	Ddim_Print(("PLLCNT1_PL06ST	= %d\n", DdTopone_GET_PLLCNT1_PL06ST()));
	Ddim_Print(("PLLCNT1_PL07ST	= %d\n", DdTopone_GET_PLLCNT1_PL07ST()));
	Ddim_Print(("PLLCNT1_PL08ST	= %d\n", DdTopone_GET_PLLCNT1_PL08ST()));
	Ddim_Print(("PLLCNT1_PL10ST	= %d\n", DdTopone_GET_PLLCNT1_PL10ST()));
	Ddim_Print(("PLLCNT1_PL10AST	= %d\n", DdTopone_GET_PLLCNT1_PL10AST()));
	Ddim_Print(("PLLCNT1_PL11ST	= %d\n", DdTopone_GET_PLLCNT1_PL11ST()));
	Ddim_Print(("PLLCNT1_DPL00ST	= %d\n", DdTopone_GET_PLLCNT1_DPL00ST()));
	Ddim_Print(("PLLCNT1_DPL01ST	= %d\n", DdTopone_GET_PLLCNT1_DPL01ST()));
	Ddim_Print(("PLLCNT1_DPL02ST	= %d\n", DdTopone_GET_PLLCNT1_DPL02ST()));
	Ddim_Print(("PLLCNT1_DPL10ST	= %d\n", DdTopone_GET_PLLCNT1_DPL10ST()));
	Ddim_Print(("PLLCNT1_DPL11ST	= %d\n", DdTopone_GET_PLLCNT1_DPL11ST()));
	Ddim_Print(("PLLCNT1_DPL12ST	= %d\n", DdTopone_GET_PLLCNT1_DPL12ST()));
}

static void ctGetClockPllcnt2(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT2.bit.PL00SEL		= 1;
	IO_CHIPTOP.PLLCNT2.bit.PL01SEL		= 1;
	IO_CHIPTOP.PLLCNT2.bit.PL02SEL		= 1;
	IO_CHIPTOP.PLLCNT2.bit.PL03SEL		= 1;
	IO_CHIPTOP.PLLCNT2.bit.PL04SEL		= 1;
	IO_CHIPTOP.PLLCNT2.bit.PL05SEL		= 1;
	IO_CHIPTOP.PLLCNT2.bit.PL05ASEL		= 1;
	IO_CHIPTOP.PLLCNT2.bit.PL06SEL		= 1;
	IO_CHIPTOP.PLLCNT2.bit.PL07SEL		= 1;
	IO_CHIPTOP.PLLCNT2.bit.PL08SEL		= 1;
	IO_CHIPTOP.PLLCNT2.bit.PL10SEL		= 1;
	IO_CHIPTOP.PLLCNT2.bit.PL10ASEL		= 1;
	IO_CHIPTOP.PLLCNT2.bit.PL11SEL		= 1;
	IO_CHIPTOP.PLLCNT2.bit.PL01SSEN		= 1;
	IO_CHIPTOP.PLLCNT2.bit.PL02SSEN		= 1;
#endif

	Ddim_Print(("PLLCNT2_PL00SEL	= %d\n", DdTopone_GET_PLLCNT2_PL00SEL()));
	Ddim_Print(("PLLCNT2_PL01SEL	= %d\n", DdTopone_GET_PLLCNT2_PL01SEL()));
	Ddim_Print(("PLLCNT2_PL02SEL	= %d\n", DdTopone_GET_PLLCNT2_PL02SEL()));
	Ddim_Print(("PLLCNT2_PL03SEL	= %d\n", DdTopone_GET_PLLCNT2_PL03SEL()));
	Ddim_Print(("PLLCNT2_PL04SEL	= %d\n", DdTopone_GET_PLLCNT2_PL04SEL()));
	Ddim_Print(("PLLCNT2_PL05SEL	= %d\n", DdTopone_GET_PLLCNT2_PL05SEL()));
	Ddim_Print(("PLLCNT2_PL05ASEL	= %d\n", DdTopone_GET_PLLCNT2_PL05ASEL()));
	Ddim_Print(("PLLCNT2_PL06SEL	= %d\n", DdTopone_GET_PLLCNT2_PL06SEL()));
	Ddim_Print(("PLLCNT2_PL07SEL	= %d\n", DdTopone_GET_PLLCNT2_PL07SEL()));
	Ddim_Print(("PLLCNT2_PL08SEL	= %d\n", DdTopone_GET_PLLCNT2_PL08SEL()));
	Ddim_Print(("PLLCNT2_PL10SEL	= %d\n", DdTopone_GET_PLLCNT2_PL10SEL()));
	Ddim_Print(("PLLCNT2_PL10ASEL	= %d\n", DdTopone_GET_PLLCNT2_PL10ASEL()));
	Ddim_Print(("PLLCNT2_PL11SEL	= %d\n", DdTopone_GET_PLLCNT2_PL11SEL()));
	Ddim_Print(("PLLCNT2_PL01SSEN	= %d\n", DdTopone_GET_PLLCNT2_PL01SSEN()));
	Ddim_Print(("PLLCNT2_PL02SSEN	= %d\n", DdTopone_GET_PLLCNT2_PL02SSEN()));
}                                       

static void ctGetClockPllcnt3(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT3.bit.P00POSTDIV	= 1;
	IO_CHIPTOP.PLLCNT3.bit.P00PREDIV	= 1;
	IO_CHIPTOP.PLLCNT3.bit.P00PLLDIV	= 1;
#endif

	Ddim_Print(("PLLCNT3_P00POSTDIV	= %d\n", DdTopone_GET_PLLCNT3_P00POSTDIV()));
	Ddim_Print(("PLLCNT3_P00PREDIV	= %d\n", DdTopone_GET_PLLCNT3_P00PREDIV()));
	Ddim_Print(("PLLCNT3_P00PLLDIV	= %d\n", DdTopone_GET_PLLCNT3_P00PLLDIV()));
}

static void ctGetClockPllcnt4(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT4.bit.P00FNUM		= 1;
#endif

	Ddim_Print(("PLLCNT4_P00FNUM	= %lu\n", DdTopone_GET_PLLCNT4_P00FNUM()));
}

static void ctGetClockPllcnt5(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT5.bit.P00FDEN		= 1;
#endif

	Ddim_Print(("PLLCNT5_P00FDEN	= %lu\n", DdTopone_GET_PLLCNT5_P00FDEN()));
}

static void ctGetClockPllcnt6(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT6.bit.P01RATE		= 1;
	IO_CHIPTOP.PLLCNT6.bit.P01FREQ		= 1;
	IO_CHIPTOP.PLLCNT6.bit.P01MODE		= 1;
	IO_CHIPTOP.PLLCNT6.bit.P02RATE		= 1;
	IO_CHIPTOP.PLLCNT6.bit.P02FREQ		= 1;
	IO_CHIPTOP.PLLCNT6.bit.P02MODE		= 1;
#endif

	Ddim_Print(("PLLCNT6_P01RATE	= %d\n", DdTopone_GET_PLLCNT6_P01RATE()));
	Ddim_Print(("PLLCNT6_P01FREQ	= %d\n", DdTopone_GET_PLLCNT6_P01FREQ()));
	Ddim_Print(("PLLCNT6_P01MODE	= %d\n", DdTopone_GET_PLLCNT6_P01MODE()));
	Ddim_Print(("PLLCNT6_P02RATE	= %d\n", DdTopone_GET_PLLCNT6_P02RATE()));
	Ddim_Print(("PLLCNT6_P02FREQ	= %d\n", DdTopone_GET_PLLCNT6_P02FREQ()));
	Ddim_Print(("PLLCNT6_P02MODE	= %d\n", DdTopone_GET_PLLCNT6_P02MODE()));
}

static void ctGetClockPllcnt7(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT7.bit.P03POSTDIV0	= 1;
	IO_CHIPTOP.PLLCNT7.bit.P03POSTDIV1	= 1;
	IO_CHIPTOP.PLLCNT7.bit.P03PREDIV	= 1;
	IO_CHIPTOP.PLLCNT7.bit.P03PLLDIV	= 1;
	IO_CHIPTOP.PLLCNT7.bit.P03OC0		= 1;
	IO_CHIPTOP.PLLCNT7.bit.P03OC1		= 1;
	IO_CHIPTOP.PLLCNT7.bit.D0XOC		= 1;
	IO_CHIPTOP.PLLCNT7.bit.D1XOC		= 1;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	IO_CHIPTOP.PLLCNT7.bit.DPLX8		= 1;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	IO_CHIPTOP.PLLCNT7.bit.DSEL			= 1;
#endif

	Ddim_Print(("PLLCNT7_P03POSTDIV0	= %d\n", DdTopone_GET_PLLCNT7_P03POSTDIV0()));
	Ddim_Print(("PLLCNT7_P03POSTDIV1	= %d\n", DdTopone_GET_PLLCNT7_P03POSTDIV1()));
	Ddim_Print(("PLLCNT7_P03PREDIV	= %d\n", DdTopone_GET_PLLCNT7_P03PREDIV()));
	Ddim_Print(("PLLCNT7_P03PLLDIV	= %d\n", DdTopone_GET_PLLCNT7_P03PLLDIV()));
	Ddim_Print(("PLLCNT7_P03OC0		= %d\n", DdTopone_GET_PLLCNT7_P03OC0()));
	Ddim_Print(("PLLCNT7_P03OC1		= %d\n", DdTopone_GET_PLLCNT7_P03OC1()));
	Ddim_Print(("PLLCNT7_D0XOC		= %d\n", DdTopone_GET_PLLCNT7_D0XOC()));
	Ddim_Print(("PLLCNT7_D1XOC		= %d\n", DdTopone_GET_PLLCNT7_D1XOC()));
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	Ddim_Print(("PLLCNT7_DPLX8		= %d\n", DdTopone_GET_PLLCNT7_DPLX8()));
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	Ddim_Print(("PLLCNT7_DSEL		= %d\n", DdTopone_GET_PLLCNT7_DSEL()));
}

static void ctGetClockPllcnt8(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT8.bit.P04POSTDIV	= 1;
	IO_CHIPTOP.PLLCNT8.bit.P04PREDIV	= 1;
	IO_CHIPTOP.PLLCNT8.bit.P04PLLDIV	= 1;
#endif
	Ddim_Print(("PLLCNT8_P04POSTDIV	= %d\n", DdTopone_GET_PLLCNT8_P04POSTDIV()));
	Ddim_Print(("PLLCNT8_P04PREDIV	= %d\n", DdTopone_GET_PLLCNT8_P04PREDIV()));
	Ddim_Print(("PLLCNT8_P04PLLDIV	= %d\n", DdTopone_GET_PLLCNT8_P04PLLDIV()));
}

static void ctGetClockPllcnt9(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT9.bit.P10APLLDIV	= 1;
	IO_CHIPTOP.PLLCNT9.bit.P08PLLDIV	= 1;
	IO_CHIPTOP.PLLCNT9.bit.P05CHG	= 1;
#endif
	Ddim_Print(("PLLCNT9_P10APLLDIV	= %d\n", DdTopone_GET_PLLCNT9_P10APLLDIV()));
	Ddim_Print(("PLLCNT9_P08PLLDIV	= %d\n", DdTopone_GET_PLLCNT9_P08PLLDIV()));
	Ddim_Print(("PLLCNT9_P05CHG	    = %d\n", DdTopone_GET_PLLCNT9_P05CHG()));
}

static void ctSetClockPllcnt1(kint argc, kchar** argv)
{
	kulong val;
	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "PL00ST" ) ) {
			DdTopone_SET_PLLCNT1_PL00ST(val);
			Ddim_Print(("It set PLLCNT1_PL00ST PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL00ST	= %d\n", IO_CHIPTOP.PLLCNT1.bit.PL00ST));
		}else if (  0 == strcmp( argv[4], "PL01ST" ) ) {
			DdTopone_SET_PLLCNT1_PL01ST(val);
			Ddim_Print(("It set PLLCNT1_PL01ST PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL01ST	= %d\n", IO_CHIPTOP.PLLCNT1.bit.PL01ST));
		}else if (  0 == strcmp( argv[4], "PL02ST" ) ) {
			DdTopone_SET_PLLCNT1_PL02ST(val);
			Ddim_Print(("It set PLLCNT1_PL02ST PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL02ST	= %d\n", IO_CHIPTOP.PLLCNT1.bit.PL02ST));
		}else if (  0 == strcmp( argv[4], "PL03ST" ) ) {
			DdTopone_SET_PLLCNT1_PL03ST(val);
			Ddim_Print(("It set PLLCNT1_PL03ST PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL03ST	= %d\n", IO_CHIPTOP.PLLCNT1.bit.PL03ST));
		}else if (  0 == strcmp( argv[4], "PL04ST" ) ) {
			DdTopone_SET_PLLCNT1_PL04ST(val);
			Ddim_Print(("It set PLLCNT1_PL04ST PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL04ST	= %d\n", IO_CHIPTOP.PLLCNT1.bit.PL04ST));
		}else if (  0 == strcmp( argv[4], "PL05ST" ) ) {
			DdTopone_SET_PLLCNT1_PL05ST(val);
			Ddim_Print(("It set PLLCNT1_PL05ST PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL05ST	= %d\n", IO_CHIPTOP.PLLCNT1.bit.PL05ST));
		}else if (  0 == strcmp( argv[4], "PL05AST" ) ) {
			DdTopone_SET_PLLCNT1_PL05AST(val);
			Ddim_Print(("It set PLLCNT1_PL05AST PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL05AST	= %d\n", IO_CHIPTOP.PLLCNT1.bit.PL05AST));
		}else if (  0 == strcmp( argv[4], "PL06ST" ) ) {
			DdTopone_SET_PLLCNT1_PL06ST(val);
			Ddim_Print(("It set PLLCNT1_PL06ST PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL06ST	= %d\n", IO_CHIPTOP.PLLCNT1.bit.PL06ST));
		}else if (  0 == strcmp( argv[4], "PL07ST" ) ) {
			DdTopone_SET_PLLCNT1_PL07ST(val);
			Ddim_Print(("It set PLLCNT1_PL07ST PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL07ST	= %d\n", IO_CHIPTOP.PLLCNT1.bit.PL07ST));
		}else if (  0 == strcmp( argv[4], "PL08ST" ) ) {
			DdTopone_SET_PLLCNT1_PL08ST(val);
			Ddim_Print(("It set PLLCNT1_PL08ST PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL08ST	= %d\n", IO_CHIPTOP.PLLCNT1.bit.PL08ST));
		}else if (  0 == strcmp( argv[4], "PL10ST" ) ) {
			DdTopone_SET_PLLCNT1_PL10ST(val);
			Ddim_Print(("It set PLLCNT1_PL10ST PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL10ST	= %d\n", IO_CHIPTOP.PLLCNT1.bit.PL10ST));
		}else if (  0 == strcmp( argv[4], "PL10AST" ) ) {
			DdTopone_SET_PLLCNT1_PL10AST(val);
			Ddim_Print(("It set PLLCNT1_PL10AST PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL10AST	= %d\n", IO_CHIPTOP.PLLCNT1.bit.PL10AST));
		}else if (  0 == strcmp( argv[4], "PL11ST" ) ) {
			DdTopone_SET_PLLCNT1_PL11ST(val);
			Ddim_Print(("It set PLLCNT1_PL11ST PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL11ST	= %d\n", IO_CHIPTOP.PLLCNT1.bit.PL11ST));
		}else if (  0 == strcmp( argv[4], "DPL00ST" ) ) {
			DdTopone_SET_PLLCNT1_DPL00ST(val);
			Ddim_Print(("It set PLLCNT1_DPL00ST PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.DPL00ST	= %d\n", IO_CHIPTOP.PLLCNT1.bit.DPL00ST));
		}else if (  0 == strcmp( argv[4], "DPL01ST" ) ) {
			DdTopone_SET_PLLCNT1_DPL01ST(val);
			Ddim_Print(("It set PLLCNT1_DPL01ST PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.DPL01ST	= %d\n", IO_CHIPTOP.PLLCNT1.bit.DPL01ST));
		}else if (  0 == strcmp( argv[4], "DPL02ST" ) ) {
			DdTopone_SET_PLLCNT1_DPL02ST(val);
			Ddim_Print(("It set PLLCNT1_DPL02ST PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.DPL02ST	= %d\n", IO_CHIPTOP.PLLCNT1.bit.DPL02ST));
		}else if (  0 == strcmp( argv[4], "DPL10ST" ) ) {
			DdTopone_SET_PLLCNT1_DPL10ST(val);
			Ddim_Print(("It set PLLCNT1_DPL10ST PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.DPL10ST	= %d\n", IO_CHIPTOP.PLLCNT1.bit.DPL10ST));
		}else if (  0 == strcmp( argv[4], "DPL11ST" ) ) {
			DdTopone_SET_PLLCNT1_DPL11ST(val);
			Ddim_Print(("It set PLLCNT1_DPL11ST PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.DPL11ST	= %d\n", IO_CHIPTOP.PLLCNT1.bit.DPL11ST));
		}else if (  0 == strcmp( argv[4], "DPL12ST" ) ) {
			DdTopone_SET_PLLCNT1_DPL12ST(val);
			Ddim_Print(("It set PLLCNT1_DPL12ST PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.DPL12ST	= %d\n", IO_CHIPTOP.PLLCNT1.bit.DPL12ST));
		}
		else {
			Ddim_Print(("please check 3rd parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void ctSetClockPllcnt2(kint argc, kchar** argv)
{
	kulong val;
	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "PL00SEL" ) ) {
			DdTopone_SET_PLLCNT2_PL00SEL(val);
			Ddim_Print(("It set PLLCNT2_PL00SEL PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL00SEL	= %d\n", IO_CHIPTOP.PLLCNT2.bit.PL00SEL));
		}else if (  0 == strcmp( argv[4], "PL01SEL" ) ) {
			DdTopone_SET_PLLCNT2_PL01SEL(val);
			Ddim_Print(("It set PLLCNT2_PL01SEL PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL01SEL	= %d\n", IO_CHIPTOP.PLLCNT2.bit.PL01SEL));
		}else if (  0 == strcmp( argv[4], "PL02SEL" ) ) {
			DdTopone_SET_PLLCNT2_PL02SEL(val);
			Ddim_Print(("It set PLLCNT2_PL02SEL PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL02SEL	= %d\n", IO_CHIPTOP.PLLCNT2.bit.PL02SEL));
		}else if (  0 == strcmp( argv[4], "PL03SEL" ) ) {
			DdTopone_SET_PLLCNT2_PL03SEL(val);
			Ddim_Print(("It set PLLCNT2_PL03SEL PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL03SEL	= %d\n", IO_CHIPTOP.PLLCNT2.bit.PL03SEL));
		}else if (  0 == strcmp( argv[4], "PL04SEL" ) ) {
			DdTopone_SET_PLLCNT2_PL04SEL(val);
			Ddim_Print(("It set PLLCNT2_PL04SEL PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL04SEL	= %d\n", IO_CHIPTOP.PLLCNT2.bit.PL04SEL));
		}else if (  0 == strcmp( argv[4], "PL05SEL" ) ) {
			DdTopone_SET_PLLCNT2_PL05SEL(val);
			Ddim_Print(("It set PLLCNT2_PL05SEL PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL05SEL	= %d\n", IO_CHIPTOP.PLLCNT2.bit.PL05SEL));
		}else if (  0 == strcmp( argv[4], "PL05ASEL" ) ) {
			DdTopone_SET_PLLCNT2_PL05ASEL(val);
			Ddim_Print(("It set PLLCNT2_PL05ASEL PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL05ASEL	= %d\n", IO_CHIPTOP.PLLCNT2.bit.PL05ASEL));
		}else if (  0 == strcmp( argv[4], "PL06SEL" ) ) {
			DdTopone_SET_PLLCNT2_PL06SEL(val);
			Ddim_Print(("It set PLLCNT2_PL06SEL PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL06SEL	= %d\n", IO_CHIPTOP.PLLCNT2.bit.PL06SEL));
		}else if (  0 == strcmp( argv[4], "PL07SEL" ) ) {
			DdTopone_SET_PLLCNT2_PL07SEL(val);
			Ddim_Print(("It set PLLCNT2_PL07SEL PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL07SEL	= %d\n", IO_CHIPTOP.PLLCNT2.bit.PL07SEL));
		}else if (  0 == strcmp( argv[4], "PL08SEL" ) ) {
			DdTopone_SET_PLLCNT2_PL08SEL(val);
			Ddim_Print(("It set PLLCNT2_PL08SEL PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL08SEL	= %d\n", IO_CHIPTOP.PLLCNT2.bit.PL08SEL));
		}else if (  0 == strcmp( argv[4], "PL10SEL" ) ) {
			DdTopone_SET_PLLCNT2_PL10SEL(val);
			Ddim_Print(("It set PLLCNT2_PL10SEL PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL10SEL	= %d\n", IO_CHIPTOP.PLLCNT2.bit.PL10SEL));
		}else if (  0 == strcmp( argv[4], "PL10ASEL" ) ) {
			DdTopone_SET_PLLCNT2_PL10ASEL(val);
			Ddim_Print(("It set PLLCNT2_PL10ASEL PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL10ASEL	= %d\n", IO_CHIPTOP.PLLCNT2.bit.PL10ASEL));
		}else if (  0 == strcmp( argv[4], "PL11SEL" ) ) {
			DdTopone_SET_PLLCNT2_PL11SEL(val);
			Ddim_Print(("It set PLLCNT2_PL11SEL PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL11SEL	= %d\n", IO_CHIPTOP.PLLCNT2.bit.PL11SEL));
		}else if (  0 == strcmp( argv[4], "PL01SSEN" ) ) {
			DdTopone_SET_PLLCNT2_PL01SSEN(val);
			Ddim_Print(("It set PLLCNT2_PL01SSEN PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL01SSEN	= %d\n", IO_CHIPTOP.PLLCNT2.bit.PL01SSEN));
		}else if (  0 == strcmp( argv[4], "PL02SSEN" ) ) {
			DdTopone_SET_PLLCNT2_PL02SSEN(val);
			Ddim_Print(("It set PLLCNT2_PL02SSEN PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL02SSEN	= %d\n", IO_CHIPTOP.PLLCNT2.bit.PL02SSEN));
		}
		else {
			Ddim_Print(("please check 3rd parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void ctSetClockPllcnt3(kint argc, kchar** argv)
{
	kulong val;
	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "P00POSTDIV" ) ) {
			DdTopone_SET_PLLCNT3_P00POSTDIV(val);
			Ddim_Print(("It set PLLCNT3_P00POSTDIV PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT3.bit.P00POSTDIV	= %d\n", IO_CHIPTOP.PLLCNT3.bit.P00POSTDIV));
		}else if (  0 == strcmp( argv[4], "P00PREDIV" ) ) {
			DdTopone_SET_PLLCNT3_P00PREDIV(val);
			Ddim_Print(("It set PLLCNT3_P00PREDIV PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT3.bit.P00PREDIV	= %d\n", IO_CHIPTOP.PLLCNT3.bit.P00PREDIV));
		}else if (  0 == strcmp( argv[4], "P00PLLDIV" ) ) {
			DdTopone_SET_PLLCNT3_P00PLLDIV(val);
			Ddim_Print(("It set PLLCNT3_P00PLLDIV PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT3.bit.P00PLLDIV	= %d\n", IO_CHIPTOP.PLLCNT3.bit.P00PLLDIV));
		}
		else {
			Ddim_Print(("please check 3rd parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void ctSetClockPllcnt4(kint argc, kchar** argv)
{
	kulong val;
	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "P00FNUM" ) ) {
			DdTopone_SET_PLLCNT4_P00FNUM(val);
			Ddim_Print(("It set PLLCNT4_P00FNUM PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT4.bit.P00FNUM	= %lu\n", IO_CHIPTOP.PLLCNT4.bit.P00FNUM));
		}
		else {
			Ddim_Print(("please check 3rd parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void ctSetClockPllcnt5(kint argc, kchar** argv)
{
	kulong val;
	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "P00FDEN" ) ) {
			DdTopone_SET_PLLCNT5_P00FDEN(val);
			Ddim_Print(("It set PLLCNT5_P00FDEN PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT5.bit.P00FDEN	= %lu\n", IO_CHIPTOP.PLLCNT5.bit.P00FDEN));
		}
		else {
			Ddim_Print(("please check 3rd parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void ctSetClockPllcnt6(kint argc, kchar** argv)
{
	kulong val;
	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "P01RATE" ) ) {
			DdTopone_SET_PLLCNT6_P01RATE(val);
			Ddim_Print(("It set PLLCNT6_P01RATE PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT6.bit.P01RATE	= %d\n", IO_CHIPTOP.PLLCNT6.bit.P01RATE));
		}else if (  0 == strcmp( argv[4], "P01FREQ" ) ) {
			DdTopone_SET_PLLCNT6_P01FREQ(val);
			Ddim_Print(("It set PLLCNT6_P01FREQ PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT6.bit.P01FREQ	= %d\n", IO_CHIPTOP.PLLCNT6.bit.P01FREQ));
		}else if (  0 == strcmp( argv[4], "P01MODE" ) ) {
			DdTopone_SET_PLLCNT6_P01MODE(val);
			Ddim_Print(("It set PLLCNT6_P01MODE PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT6.bit.P01MODE	= %d\n", IO_CHIPTOP.PLLCNT6.bit.P01MODE));
		}else if (  0 == strcmp( argv[4], "P02RATE" ) ) {
			DdTopone_SET_PLLCNT6_P02RATE(val);
			Ddim_Print(("It set PLLCNT6_P02RATE PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT6.bit.P02RATE	= %d\n", IO_CHIPTOP.PLLCNT6.bit.P02RATE));
		}else if (  0 == strcmp( argv[4], "P02FREQ" ) ) {
			DdTopone_SET_PLLCNT6_P02FREQ(val);
			Ddim_Print(("It set PLLCNT6_P02FREQ PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT6.bit.P02FREQ	= %d\n", IO_CHIPTOP.PLLCNT6.bit.P02FREQ));
		}else if (  0 == strcmp( argv[4], "P02MODE" ) ) {
			DdTopone_SET_PLLCNT6_P02MODE(val);
			Ddim_Print(("It set PLLCNT6_P02MODE PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT6.bit.P02MODE	= %d\n", IO_CHIPTOP.PLLCNT6.bit.P02MODE));
		}
		else {
			Ddim_Print(("please check 3rd parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void ctSetClockPllcnt7(kint argc, kchar** argv)
{
	kulong val;
	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "P03POSTDIV0" ) ) {
			DdTopone_SET_PLLCNT7_P03POSTDIV0(val);
			Ddim_Print(("It set PLLCNT7_P03POSTDIV0 PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT7.bit.P03POSTDIV0	= %d\n", IO_CHIPTOP.PLLCNT7.bit.P03POSTDIV0));
		}else if (  0 == strcmp( argv[4], "P03POSTDIV1" ) ) {
			DdTopone_SET_PLLCNT7_P03POSTDIV1(val);
			Ddim_Print(("It set PLLCNT7_P03POSTDIV1 PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT7.bit.P03POSTDIV1	= %d\n", IO_CHIPTOP.PLLCNT7.bit.P03POSTDIV1));
		}else if (  0 == strcmp( argv[4], "P03PREDIV" ) ) {
			DdTopone_SET_PLLCNT7_P03PREDIV(val);
			Ddim_Print(("It set PLLCNT7_P03PREDIV PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT7.bit.P03PREDIV	= %d\n", IO_CHIPTOP.PLLCNT7.bit.P03PREDIV));
		}else if (  0 == strcmp( argv[4], "P03PLLDIV" ) ) {
			DdTopone_SET_PLLCNT7_P03PLLDIV(val);
			Ddim_Print(("It set PLLCNT7_P03PLLDIV PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT7.bit.P03PLLDIV	= %d\n", IO_CHIPTOP.PLLCNT7.bit.P03PLLDIV));
		}else if (  0 == strcmp( argv[4], "P03OC0" ) ) {
			DdTopone_SET_PLLCNT7_P03OC0(val);
			Ddim_Print(("It set PLLCNT8_P03OC0 PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT7.bit.P03OC0	= %d\n", IO_CHIPTOP.PLLCNT7.bit.P03OC0));
		}else if (  0 == strcmp( argv[4], "P03OC1" ) ) {
			DdTopone_SET_PLLCNT7_P03OC1(val);
			Ddim_Print(("It set PLLCNT8_P03OC1 PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT7.bit.P03OC1	= %d\n", IO_CHIPTOP.PLLCNT7.bit.P03OC1));
		}else if (  0 == strcmp( argv[4], "D0XOC" ) ) {
			DdTopone_SET_PLLCNT7_D0XOC(val);
			Ddim_Print(("It set PLLCNT8_D0XOC PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT7.bit.D0XOC	= %d\n", IO_CHIPTOP.PLLCNT7.bit.D0XOC));
		}else if (  0 == strcmp( argv[4], "D1XOC" ) ) {
			DdTopone_SET_PLLCNT7_D1XOC(val);
			Ddim_Print(("It set PLLCNT8_D1XOC PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT7.bit.D1XOC	= %d\n", IO_CHIPTOP.PLLCNT7.bit.D1XOC));
		}
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
		else if ( 0 == strcmp( argv[4], "DPLX8" ) ) {
			DdTopone_SET_PLLCNT7_DPLX8(val);
			Ddim_Print(("It set PLLCNT8_DPLX8 PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT7.bit.DPLX8	= %d\n", IO_CHIPTOP.PLLCNT7.bit.DPLX8));
		}
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
		else if ( 0 == strcmp( argv[4], "DSEL" ) ) {
			DdTopone_SET_PLLCNT7_DSEL(val);
			Ddim_Print(("It set PLLCNT8_DSEL PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT7.bit.DSEL	= %d\n", IO_CHIPTOP.PLLCNT7.bit.DSEL));
		}
		else {
			Ddim_Print(("please check 3rd parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void ctSetClockPllcnt8(kint argc, kchar** argv)
{
	kulong val;
	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "P04POSTDIV" ) ) {
			DdTopone_SET_PLLCNT8_P04POSTDIV(val);
			Ddim_Print(("It set PLLCNT8_P04POSTDIV PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT8.bit.P04POSTDIV	= %d\n", IO_CHIPTOP.PLLCNT8.bit.P04POSTDIV));
		}else if (  0 == strcmp( argv[4], "P04PREDIV" ) ) {
			DdTopone_SET_PLLCNT8_P04PREDIV(val);
			Ddim_Print(("It set PLLCNT8_P04PREDIV PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT8.bit.P04PREDIV	= %d\n", IO_CHIPTOP.PLLCNT8.bit.P04PREDIV));
		}else if (  0 == strcmp( argv[4], "P04PLLDIV" ) ) {
			DdTopone_SET_PLLCNT8_P04PLLDIV(val);
			Ddim_Print(("It set PLLCNT8_P04PLLDIV PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT8.bit.P04PLLDIV	= %d\n", IO_CHIPTOP.PLLCNT8.bit.P04PLLDIV));
		}
		else {
			Ddim_Print(("please check 3rd parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void ctSetClockPllcnt9(kint argc, kchar** argv)
{
	kulong val;
	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "P10APLLDIV" ) ) {
			DdTopone_SET_PLLCNT9_P10APLLDIV(val);
			Ddim_Print(("It set PLLCNT9_P10APLLDIV PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT9.bit.P10APLLDIV	= %d\n", IO_CHIPTOP.PLLCNT9.bit.P10APLLDIV));
		}else if (  0 == strcmp( argv[4], "P08PLLDIV" ) ) {
			DdTopone_SET_PLLCNT9_P08PLLDIV(val);
			Ddim_Print(("It set PLLCNT9_P08PLLDIV PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT9.bit.P08PLLDIV	= %d\n", IO_CHIPTOP.PLLCNT9.bit.P08PLLDIV));
		}else if (  0 == strcmp( argv[4], "P05CHG" ) ) {
			DdTopone_SET_PLLCNT9_P05CHG(val);
			Ddim_Print(("It set PLLCNT9_P05CHG PLL State.\n"));
			Ddim_Print(("IO_CHIPTOP.PLLCNT9.bit.P05CHG	= %d\n", IO_CHIPTOP.PLLCNT9.bit.P05CHG));
		}
		else {
			Ddim_Print(("please check 3rd parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}
/****************
* PUBLIC
*/
void ct_clock_pllcnt_set(CtClockPllcnt *self)
{
	CtClockPllcntPrivate *priv = CT_CLOCK_PLLCNT_GET_PRIVATE(self);

    if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "pllcnt1" ) ) {
        ctSetClockPllcnt1( ((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv );
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "pllcnt2" ) ) {
        ctSetClockPllcnt2( ((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv );
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "pllcnt3" ) ) {
        ctSetClockPllcnt3( ((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv );
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "pllcnt4" ) ) {
        ctSetClockPllcnt4( ((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv );
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "pllcnt5" ) ) {
        ctSetClockPllcnt5( ((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv );
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "pllcnt6" ) ) {
        ctSetClockPllcnt6( ((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv );
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "pllcnt7" ) ) {
        ctSetClockPllcnt7( ((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv );
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "pllcnt8" ) ) {
        ctSetClockPllcnt8( ((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv );
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "pllcnt9" ) ) {
        ctSetClockPllcnt9( ((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv );
    }else {
		ct_dd_parameter_set_parameter((CtDdParameter *)priv->ctClockClkstop,
				((CtDdParameter *)self)->argc,((CtDdParameter *)self)->argv);
		ct_clock_clkstop_set(priv->ctClockClkstop);
	}
}

void ct_clock_pllcnt_get(CtClockPllcnt *self)
{
	CtClockPllcntPrivate *priv = CT_CLOCK_PLLCNT_GET_PRIVATE(self);

    if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "pllcnt1" ) ) {
        ctGetClockPllcnt1();
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "pllcnt2" ) ) {
        ctGetClockPllcnt2();
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "pllcnt3" ) ) {
        ctGetClockPllcnt3();
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "pllcnt4" ) ) {
        ctGetClockPllcnt4();
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "pllcnt5" ) ) {
        ctGetClockPllcnt5();
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "pllcnt6" ) ) {
        ctGetClockPllcnt6();
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "pllcnt7" ) ) {
        ctGetClockPllcnt7();
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "pllcnt8" ) ) {
        ctGetClockPllcnt8();
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "pllcnt9" ) ) {
        ctGetClockPllcnt9();
    }else {
		ct_dd_parameter_set_parameter((CtDdParameter *)priv->ctClockClkstop,
				((CtDdParameter *)self)->argc,((CtDdParameter *)self)->argv);
		ct_clock_clkstop_get(priv->ctClockClkstop);
	}
	
}

CtClockPllcnt* ct_clock_pllcnt_new(void) 
{
    CtClockPllcnt *self = k_object_new_with_private(CT_TYPE_CLOCK_PLLCNT, sizeof(CtClockPllcntPrivate));
    return self;
}
