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
#include "ctsetpll.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtSetPll, ct_set_pll);
#define CT_SET_PLL_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtSetPllPrivate,CT_TYPE_SET_PLL))

struct _CtSetPllPrivate
{
	kint a;
};
/****************
* DECLS
*/
static void 			ct_set_pll_constructor(CtSetPll *self);
static void 			ct_set_pll_destructor(CtSetPll *self);
static void 			ctSetPllcnt2Pl00sel(kint argc, kchar **argv);
static void 			ctSetPllcnt2Pl01sel(kint argc, kchar **argv);
static void 			ctSetPllcnt2Pl02sel(kint argc, kchar **argv);
static void 			ctSetPllcnt2Pl03sel(kint argc, kchar **argv);
static void 			ctSetPllcnt2Pl04sel(kint argc, kchar **argv);
static void 			ctSetPllcnt2Pl05sel(kint argc, kchar **argv);
static void 			ctSetPllcnt2Pl05asel(kint argc, kchar **argv);
static void 			ctSetPllcnt2Pl06sel(kint argc, kchar **argv);
static void 			ctSetPllcnt2Pl07sel(kint argc, kchar **argv);
static void 			ctSetPllcnt2Pl08sel(kint argc, kchar **argv);
static void 			ctSetPllcnt2Pl10sel(kint argc, kchar **argv);
static void 			ctSetPllcnt2Pl10asel(kint argc, kchar **argv);
static void 			ctSetPllcnt2Pl11sel(kint argc, kchar **argv);
static void 			ctSetPllcnt2Pl01ssen(kint argc, kchar **argv);
static void 			ctSetPllcnt2Pl02ssen(kint argc, kchar **argv);
static void 			ctSetPllcnt3P00postdiv(kint argc, kchar **argv);
static void 			ctSetPllcnt3P00prediv(kint argc, kchar **argv);
static void 			ctSetPllcnt3P00plldiv(kint argc, kchar **argv);
static void 			ctSetPllcnt4P00fnum(kint argc, kchar **argv);
static void 			ctSetPllcnt5P00fden(kint argc, kchar **argv);
static void 			ctSetPllcnt7P03postdiv0(kint argc, kchar **argv);
static void 			ctSetPllcnt7P03postdiv1(kint argc, kchar **argv);
static void 			ctSetPllcnt7P03prediv(kint argc, kchar **argv);
static void			 	ctSetPllcnt7P03plldiv(kint argc, kchar **argv);
static void 			ctSetPllcnt7P03oc0(kint argc, kchar **argv);
static void 			ctSetPllcnt7P03oc1(kint argc, kchar **argv);
static void 			ctSetPllcnt7D0xoc(kint argc, kchar **argv);
static void 			ctSetPllcnt7D1xoc(kint argc, kchar **argv);
#ifdef CO_ES1_HARDWARE
static void 			ctSetPllcnt7Dplx8(kint argc, kchar **argv);
#endif // CO_ES1_HARDWARE
static void 			ctSetPllcnt7Dsel(kint argc, kchar **argv);
static void 			ctSetPllcnt8P04postdiv(kint argc, kchar **argv);
static void 			ctSetPllcnt8P04prediv(kint argc, kchar **argv);
static void 			ctSetPllcnt8P04plldiv(kint argc, kchar **argv);
static void 			ctSetPllcnt9P10aplldiv(kint argc, kchar **argv);
static void 			ctSetPllcnt9P08plldiv(kint argc, kchar **argv);
static void 			ctSetPllcnt9P05chg(kint argc, kchar **argv);
static void  			ctSetPllfreq1Plldiv(kint argc, kchar **argv);
static void  			ctSetOdivch0Odivch0num(kint argc, kchar **argv);
static void  			ctSetCmdenCmden(kint argc, kchar **argv);
static void  			ctPllErr();
/****************
* IMPL
*/
static void ct_set_pll_constructor(CtSetPll *self) 
{
	// CtSetPllPrivate *priv = CT_SET_PLL_GET_PRIVATE(self);
}

static void ct_set_pll_destructor(CtSetPll *self) 
{
	// CtSetPllPrivate *priv = CT_SET_PLL_GET_PRIVATE(self);
}

static void ctSetPllcnt2Pl00sel(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_PLLCNT2_PL00SEL(pll_select);
		Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL00SEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL00SEL));
	}
}

static void ctSetPllcnt2Pl01sel(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_PLLCNT2_PL01SEL(pll_select);
		Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL01SEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL01SEL));
	}
}

static void ctSetPllcnt2Pl02sel(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_PLLCNT2_PL02SEL(pll_select);
		Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL02SEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL02SEL));
	}
}

static void ctSetPllcnt2Pl03sel(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_PLLCNT2_PL03SEL(pll_select);
		Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL03SEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL03SEL));
	}
}

static void ctSetPllcnt2Pl04sel(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_PLLCNT2_PL04SEL(pll_select);
		Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL04SEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL04SEL));
	}
}

static void ctSetPllcnt2Pl05sel(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_PLLCNT2_PL05SEL(pll_select);
		Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL05SEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL05SEL));
	}
}

static void ctSetPllcnt2Pl05asel(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_PLLCNT2_PL05ASEL(pll_select);
		Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL05ASEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL05ASEL));
	}
}

static void ctSetPllcnt2Pl06sel(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_PLLCNT2_PL06SEL(pll_select);
		Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL06SEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL06SEL));
	}
}

static void ctSetPllcnt2Pl07sel(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_PLLCNT2_PL07SEL(pll_select);
		Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL07SEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL07SEL));
	}
}

static void ctSetPllcnt2Pl08sel(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_PLLCNT2_PL08SEL(pll_select);
		Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL08SEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL08SEL));
	}
}

static void ctSetPllcnt2Pl10sel(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_PLLCNT2_PL10SEL(pll_select);
		Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL10SEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL10SEL));
	}
}

static void ctSetPllcnt2Pl10asel(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_PLLCNT2_PL10ASEL(pll_select);
		Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL10ASEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL10ASEL));
	}
}

static void ctSetPllcnt2Pl11sel(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_PLLCNT2_PL11SEL(pll_select);
		Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL11SEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL11SEL));
	}
}

static void ctSetPllcnt2Pl01ssen(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_PLLCNT2_PL01SSEN(pll_select);
		Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL01SSEN = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL01SSEN));
	}
}

static void ctSetPllcnt2Pl02ssen(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_PLLCNT2_PL02SSEN(pll_select);
		Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL02SSEN = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL02SSEN));
	}
}

static void ctSetPllcnt3P00postdiv(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_PLLCNT3_P00POSTDIV(pll_select);
		Ddim_Print(("IO_CHIPTOP.PLLCNT3.bit.P00POSTDIV = %d\n", IO_CHIPTOP.PLLCNT3.bit.P00POSTDIV));
	}
}

static void ctSetPllcnt3P00prediv(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_PLLCNT3_P00PREDIV(pll_select);
		Ddim_Print(("IO_CHIPTOP.PLLCNT3.bit.P00PREDIV = %d\n", IO_CHIPTOP.PLLCNT3.bit.P00PREDIV));
	}
}

static void ctSetPllcnt3P00plldiv(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_PLLCNT3_P00PLLDIV(pll_select);
		Ddim_Print(("IO_CHIPTOP.PLLCNT3.bit.P00PLLDIV = %d\n", IO_CHIPTOP.PLLCNT3.bit.P00PLLDIV));
	}
}

static void ctSetPllcnt4P00fnum(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_PLLCNT4_P00FNUM(pll_select);
		Ddim_Print(("IO_CHIPTOP.PLLCNT4.bit.P00FNUM = %lu\n", IO_CHIPTOP.PLLCNT4.bit.P00FNUM));
	}
}

static void ctSetPllcnt5P00fden(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_PLLCNT5_P00FDEN(pll_select);
		Ddim_Print(("IO_CHIPTOP.PLLCNT5.bit.P00FDEN = %lu\n", IO_CHIPTOP.PLLCNT5.bit.P00FDEN));
	}
}

static void ctSetPllcnt7P03postdiv0(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_PLLCNT7_P03POSTDIV0(pll_select);
		Ddim_Print(("IO_CHIPTOP.PLLCNT7.bit.P03POSTDIV0 = %d\n", IO_CHIPTOP.PLLCNT7.bit.P03POSTDIV0));
	}
}

static void ctSetPllcnt7P03postdiv1(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_PLLCNT7_P03POSTDIV1(pll_select);
		Ddim_Print(("IO_CHIPTOP.PLLCNT7.bit.P03POSTDIV1 = %d\n", IO_CHIPTOP.PLLCNT7.bit.P03POSTDIV1));
	}
}

static void ctSetPllcnt7P03prediv(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_PLLCNT7_P03PREDIV(pll_select);
		Ddim_Print(("IO_CHIPTOP.PLLCNT7.bit.P03PREDIV = %d\n", IO_CHIPTOP.PLLCNT7.bit.P03PREDIV));
	}
}

static void ctSetPllcnt7P03plldiv(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_PLLCNT7_P03PLLDIV(pll_select);
		Ddim_Print(("IO_CHIPTOP.PLLCNT7.bit.P03PLLDIV = %d\n", IO_CHIPTOP.PLLCNT7.bit.P03PLLDIV));
	}
}

static void ctSetPllcnt7P03oc0(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_PLLCNT7_P03OC0(pll_select);
		Ddim_Print(("IO_CHIPTOP.PLLCNT7.bit.P03OC0 = %d\n", IO_CHIPTOP.PLLCNT7.bit.P03OC0));
	}
}

static void ctSetPllcnt7P03oc1(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_PLLCNT7_P03OC1(pll_select);
		Ddim_Print(("IO_CHIPTOP.PLLCNT7.bit.P03OC1 = %d\n", IO_CHIPTOP.PLLCNT7.bit.P03OC1));
	}
}

static void ctSetPllcnt7D0xoc(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_PLLCNT7_D0XOC(pll_select);
		Ddim_Print(("IO_CHIPTOP.PLLCNT7.bit.D0XOC = %d\n", IO_CHIPTOP.PLLCNT7.bit.D0XOC));
	}
}

static void ctSetPllcnt7D1xoc(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_PLLCNT7_D1XOC(pll_select);
		Ddim_Print(("IO_CHIPTOP.PLLCNT7.bit.D1XOC = %d\n", IO_CHIPTOP.PLLCNT7.bit.D1XOC));
	}
}

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
static void ctSetPllcnt7Dplx8(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_PLLCNT7_DPLX8(pll_select);
		Ddim_Print(("IO_CHIPTOP.PLLCNT7.bit.DPLX8 = %d\n", IO_CHIPTOP.PLLCNT7.bit.DPLX8));
	}
}

// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
static void ctSetPllcnt7Dsel(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_PLLCNT7_DSEL(pll_select);
		Ddim_Print(("IO_CHIPTOP.PLLCNT7.bit.DSEL = %d\n", IO_CHIPTOP.PLLCNT7.bit.DSEL));
	}
}

static void ctSetPllcnt8P04postdiv(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_PLLCNT8_P04POSTDIV(pll_select);
		Ddim_Print(("IO_CHIPTOP.PLLCNT8.bit.P04POSTDIV = %d\n", IO_CHIPTOP.PLLCNT8.bit.P04POSTDIV));
	}
}

static void ctSetPllcnt8P04prediv(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_PLLCNT8_P04PREDIV(pll_select);
		Ddim_Print(("IO_CHIPTOP.PLLCNT8.bit.P04PREDIV = %d\n", IO_CHIPTOP.PLLCNT8.bit.P04PREDIV));
	}
}

static void ctSetPllcnt8P04plldiv(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_PLLCNT8_P04PLLDIV(pll_select);
		Ddim_Print(("IO_CHIPTOP.PLLCNT8.bit.P04PLLDIV = %d\n", IO_CHIPTOP.PLLCNT8.bit.P04PLLDIV));
	}
}

static void ctSetPllcnt9P10aplldiv(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_PLLCNT9_P10APLLDIV(pll_select);
		Ddim_Print(("IO_CHIPTOP.PLLCNT9.bit.P10APLLDIV = %d\n", IO_CHIPTOP.PLLCNT9.bit.P10APLLDIV));
	}
}

static void ctSetPllcnt9P08plldiv(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_PLLCNT9_P08PLLDIV(pll_select);
		Ddim_Print(("IO_CHIPTOP.PLLCNT9.bit.P08PLLDIV = %d\n", IO_CHIPTOP.PLLCNT9.bit.P08PLLDIV));
	}
}

static void ctSetPllcnt9P05chg(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_PLLCNT9_P05CHG(pll_select);
		Ddim_Print(("IO_CHIPTOP.PLLCNT9.bit.P05CHG = %d\n", IO_CHIPTOP.PLLCNT9.bit.P05CHG));
	}
}

static void  ctSetPllfreq1Plldiv(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_PLLFREQ1_PLLIDIV(pll_select);
		Ddim_Print(("IO_CHIPTOP.PLLFREQ1.bit.PLLIDIV = %d\n", IO_CHIPTOP.PLLFREQ1.bit.PLLIDIV));
	}
}

static void  ctSetOdivch0Odivch0num(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_ODIVCH0_ODIVCH0NUM(pll_select);
		Ddim_Print(("IO_CHIPTOP.ODIVCH0.bit.ODIVCH0NUM = %d\n", IO_CHIPTOP.ODIVCH0.bit.ODIVCH0NUM));
	}
}

static void  ctSetCmdenCmden(kint argc, kchar **argv)
{
	kuchar pll_select;

	if (argc == 4) {
		pll_select = atoi(argv[3]);
		DdTopone_SET_CMDEN_CMDEN(pll_select);
		Ddim_Print(("IO_CHIPTOP.CMDEN.bit.CMDEN = %d\n", IO_CHIPTOP.CMDEN.bit.CMDEN));
	}
}

static void  ctPllErr(void)
{
	kint32 ret;

	ret = dd_topthree_start_pll00();
	Ddim_Print(("dd_topthree_start_pll00(): status error. ret=%d\n", ret));

	ret = dd_topthree_start_pll01();
	Ddim_Print(("dd_topthree_start_pll01(): status error. ret=%d\n", ret));

	ret = dd_topthree_start_pll02();
	Ddim_Print(("dd_topthree_start_pll02(): status error. ret=%d\n", ret));

	ret = dd_topthree_start_pll03();
	Ddim_Print(("dd_topthree_start_pll03(): status error. ret=%d\n", ret));

	ret = dd_topthree_start_pll04();
	Ddim_Print(("dd_topthree_start_pll04(): status error. ret=%d\n", ret));

	ret = dd_topthree_start_pll05();
	Ddim_Print(("dd_topthree_start_pll05(): status error. ret=%d\n", ret));

	ret = dd_topthree_start_pll05A();
	Ddim_Print(("dd_topthree_start_pll05A(): status error. ret=%d\n", ret));

	ret = dd_topthree_start_pll06();
	Ddim_Print(("dd_topthree_start_pll06(): status error. ret=%d\n", ret));

	ret = dd_topthree_start_pll07();
	Ddim_Print(("dd_topthree_start_pll07(): status error. ret=%d\n", ret));

	ret = dd_topthree_start_pll08();
	Ddim_Print(("dd_topthree_start_pll08(): status error. ret=%d\n", ret));

	ret = dd_topthree_start_pll10();
	Ddim_Print(("dd_topthree_start_pll10(): status error. ret=%d\n", ret));

	ret = dd_topthree_start_pll10A();
	Ddim_Print(("dd_topthree_start_pll10A(): status error. ret=%d\n", ret));

	ret = dd_topthree_start_pll11();
	Ddim_Print(("dd_topthree_start_pll11(): status error. ret=%d\n", ret));

	ret = dd_topthree_start_ddr_pll00();
	Ddim_Print(("dd_topthree_start_ddr_pll00(): status error. ret=%d\n", ret));

	ret = dd_topthree_start_ddr_pll01();
	Ddim_Print(("dd_topthree_start_ddr_pll01(): status error. ret=%d\n", ret));

	ret = dd_topthree_start_ddr_pll02();
	Ddim_Print(("dd_topthree_start_ddr_pll02(): status error. ret=%d\n", ret));

	ret = dd_topthree_start_ddr_pll10();
	Ddim_Print(("dd_topthree_start_ddr_pll10(): status error. ret=%d\n", ret));

	ret = dd_topthree_start_ddr_pll11();
	Ddim_Print(("dd_topthree_start_ddr_pll11(): status error. ret=%d\n", ret));

	ret = dd_topthree_start_ddr_pll12();
	Ddim_Print(("dd_topthree_start_ddr_pll12(): status error. ret=%d\n", ret));
}
/****************
* PUBLIC
*/
void ct_set_pll_control(CtSetPll *self)
{    
	if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "pl00sel" ) ) {
        ctSetPllcnt2Pl00sel(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "pl01sel" ) ) {
        ctSetPllcnt2Pl01sel(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "pl02sel" ) ) {
        ctSetPllcnt2Pl02sel(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "pl03sel" ) ) {
        ctSetPllcnt2Pl03sel(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "pl04sel" ) ) {
        ctSetPllcnt2Pl04sel(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "pl05sel" ) ) {
        ctSetPllcnt2Pl05sel(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "pl05asel" ) ) {
        ctSetPllcnt2Pl05asel(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "pl06sel" ) ) {
        ctSetPllcnt2Pl06sel(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "pl07sel" ) ) {
        ctSetPllcnt2Pl07sel(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "pl08sel" ) ) {
        ctSetPllcnt2Pl08sel(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "pl10sel" ) ) {
        ctSetPllcnt2Pl10sel(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "pl10asel" ) ) {
        ctSetPllcnt2Pl10asel(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "pl11sel" ) ) {
        ctSetPllcnt2Pl11sel(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "pl01ssen" ) ) {
        ctSetPllcnt2Pl01ssen(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "pl02ssen" ) ) {
        ctSetPllcnt2Pl02ssen(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "p00postdiv" ) ) {
        ctSetPllcnt3P00postdiv(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "p00prediv" ) ) {
        ctSetPllcnt3P00prediv(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "p00plldiv" ) ) {
        ctSetPllcnt3P00plldiv(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "p00fnum" ) ) {
        ctSetPllcnt4P00fnum(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "p00fden" ) ) {
        ctSetPllcnt5P00fden(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "p03postdiv0" ) ) {
        ctSetPllcnt7P03postdiv0(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "p03postdiv1" ) ) {
        ctSetPllcnt7P03postdiv1(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "p03prediv" ) ) {
        ctSetPllcnt7P03prediv(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "p03plldiv" ) ) {
        ctSetPllcnt7P03plldiv(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "p03oc0" ) ) {
        ctSetPllcnt7P03oc0(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "p03oc1" ) ) {
        ctSetPllcnt7P03oc1(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "d0xoc" ) ) {
        ctSetPllcnt7D0xoc(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "d1xoc" ) ) {
        ctSetPllcnt7D1xoc(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "dplx8" ) ) {
        ctSetPllcnt7Dplx8(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "dsel" ) ) {
        ctSetPllcnt7Dsel(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "p04postdiv" ) ) {
        ctSetPllcnt8P04postdiv(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "p04prediv" ) ) {
        ctSetPllcnt8P04prediv(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "p04plldiv" ) ) {
        ctSetPllcnt8P04plldiv(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "p10aplldiv" ) ) {
        ctSetPllcnt9P10aplldiv(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "p08plldiv" ) ) {
        ctSetPllcnt9P08plldiv(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "p05chg" ) ) {
        ctSetPllcnt9P05chg(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "plldiv" ) ) {
         ctSetPllfreq1Plldiv(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "odivch0num" ) ) {
         ctSetOdivch0Odivch0num(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "cmden" ) ) {
         ctSetCmdenCmden(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "err" ) ) {
         ctPllErr();
    }else {
		Ddim_Print(("please check 2nd parameter!!\n"));
	}
	
}

CtSetPll* ct_set_pll_new(void) 
{
    CtSetPll *self = k_object_new_with_private(CT_TYPE_SET_PLL, sizeof(CtSetPllPrivate));
    return self;
}