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
#include "ctclockclkstop.h"
#include "ctclockclkstopmid.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtClockClkstop, ct_clock_clkstop);
#define CT_CLOCK_CLKSTOP_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtClockClkstopPrivate,CT_TYPE_CLOCK_CLKSTOP))

struct _CtClockClkstopPrivate
{
	CtClockClkstopMid* ctClockClkstopMid;
};
/****************
* DECLS
*/
static void 			ct_clock_clkstop_constructor(CtClockClkstop *self);
static void 			ct_clock_clkstop_destructor(CtClockClkstop *self);
static void 			ctGetClockClkstop1(void);
static void 			ctGetClockClkstop2(void);
static void 			ctGetClockClkstop3(void);
static void 			ctGetClockClkstop4(void);
static void 			ctGetClockClkstop5(void);
static void 			ctGetClockClkstop6(void);
static void 			ctSetClockClkstop1(kint argc, kchar** argv);
static void 			ctSetClockClkstop2(kint argc, kchar** argv);
static void 			ctSetClockClkstop3(kint argc, kchar** argv);
static void 			ctSetClockClkstop4(kint argc, kchar** argv);
static void 			ctSetClockClkstop5(kint argc, kchar** argv);
static void 			ctSetClockClkstop6(kint argc, kchar** argv);
/****************
* IMPL
*/
static void ct_clock_clkstop_constructor(CtClockClkstop *self) 
{
	CtClockClkstopPrivate *priv = CT_CLOCK_CLKSTOP_GET_PRIVATE(self);
	priv->ctClockClkstopMid = ct_clock_clkstop_mid_new();
}

static void ct_clock_clkstop_destructor(CtClockClkstop *self) 
{
	CtClockClkstopPrivate *priv = CT_CLOCK_CLKSTOP_GET_PRIVATE(self);
	k_object_unref(priv->ctClockClkstopMid);
}

static void ctGetClockClkstop1(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.CLKSTOP1.bit.DSPCK		= 1;
	IO_CHIPTOP.CLKSTOP1.bit.DSPAX		= 1;
	IO_CHIPTOP.CLKSTOP1.bit.SENCK		= 1;
	IO_CHIPTOP.CLKSTOP1.bit.SENAX		= 1;
	IO_CHIPTOP.CLKSTOP1.bit.SENAH		= 1;
	IO_CHIPTOP.CLKSTOP1.bit.SENAP		= 1;
	IO_CHIPTOP.CLKSTOP1.bit.GPIOAP		= 1;
	IO_CHIPTOP.CLKSTOP1.bit.AU0CK		= 1;
	IO_CHIPTOP.CLKSTOP1.bit.AU2CK		= 1;
	IO_CHIPTOP.CLKSTOP1.bit.AU3CK		= 1;
	IO_CHIPTOP.CLKSTOP1.bit.AU4CK		= 1;
	IO_CHIPTOP.CLKSTOP1.bit.AU5CK		= 1;
	IO_CHIPTOP.CLKSTOP1.bit.NETAUCK		= 1;
	IO_CHIPTOP.CLKSTOP1.bit.TEMPCK		= 1;
#endif

	Ddim_Print(("CLKSTOP1_DSPCK		= %d\n", DdToptwo_GET_CLKSTOP1_DSPCK()));
	Ddim_Print(("CLKSTOP1_DSPAX		= %d\n", DdToptwo_GET_CLKSTOP1_DSPAX()));
	Ddim_Print(("CLKSTOP1_SENCK		= %d\n", DdToptwo_GET_CLKSTOP1_SENCK()));
	Ddim_Print(("CLKSTOP1_SENAX		= %d\n", DdToptwo_GET_CLKSTOP1_SENAX()));
	Ddim_Print(("CLKSTOP1_SENAH		= %d\n", DdToptwo_GET_CLKSTOP1_SENAH()));
	Ddim_Print(("CLKSTOP1_SENAP		= %d\n", DdToptwo_GET_CLKSTOP1_SENAP()));
	Ddim_Print(("CLKSTOP1_GPIOAP		= %d\n", DdToptwo_GET_CLKSTOP1_GPIOAP()));
	Ddim_Print(("CLKSTOP1_AU0CK		= %d\n", DdToptwo_GET_CLKSTOP1_AU0CK()));
	Ddim_Print(("CLKSTOP1_AU2CK		= %d\n", DdToptwo_GET_CLKSTOP1_AU2CK()));
	Ddim_Print(("CLKSTOP1_AU3CK		= %d\n", DdToptwo_GET_CLKSTOP1_AU3CK()));
	Ddim_Print(("CLKSTOP1_AU4CK		= %d\n", DdToptwo_GET_CLKSTOP1_AU4CK()));
	Ddim_Print(("CLKSTOP1_AU5CK		= %d\n", DdToptwo_GET_CLKSTOP1_AU5CK()));
	Ddim_Print(("CLKSTOP1_NETAUCK		= %d\n", DdToptwo_GET_CLKSTOP1_NETAUCK()));
	Ddim_Print(("CLKSTOP1_TEMPCK		= %d\n", DdToptwo_GET_CLKSTOP1_TEMPCK()));
	Ddim_Print(("CLKSTOP1 = %08lX\n", DdToptwo_GET_CLKSTOP1()));
}

static void ctGetClockClkstop2(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.CLKSTOP2.bit.RCK		    = 1;
	IO_CHIPTOP.CLKSTOP2.bit.UHS1CK0		= 1;
	IO_CHIPTOP.CLKSTOP2.bit.UHS1CK1		= 1;
	IO_CHIPTOP.CLKSTOP2.bit.UHS1CK2		= 1;
	IO_CHIPTOP.CLKSTOP2.bit.UHS2CK		= 1;
	IO_CHIPTOP.CLKSTOP2.bit.NFCK		= 1;
	IO_CHIPTOP.CLKSTOP2.bit.EMMCCK		= 1;
	IO_CHIPTOP.CLKSTOP2.bit.NETSECCK	= 1;
	IO_CHIPTOP.CLKSTOP2.bit.NETRCK		= 1;
	IO_CHIPTOP.CLKSTOP2.bit.EXSAX		= 1;
	IO_CHIPTOP.CLKSTOP2.bit.SPICK		= 1;
	IO_CHIPTOP.CLKSTOP2.bit.SLIMB00CK	= 1;
	IO_CHIPTOP.CLKSTOP2.bit.SLIMB01CK	= 1;
	IO_CHIPTOP.CLKSTOP2.bit.SLIMB10CK	= 1;
	IO_CHIPTOP.CLKSTOP2.bit.SLIMB11CK	= 1;
	IO_CHIPTOP.CLKSTOP2.bit.PCISUPPCK	= 1;
#endif

	Ddim_Print(("CLKSTOP2_RCK			= %d\n", DdToptwo_GET_CLKSTOP2_RCK()));
	Ddim_Print(("CLKSTOP2_UHS1CK0		= %d\n", DdToptwo_GET_CLKSTOP2_UHS1CK0()));
	Ddim_Print(("CLKSTOP2_UHS1CK1		= %d\n", DdToptwo_GET_CLKSTOP2_UHS1CK1()));
	Ddim_Print(("CLKSTOP2_UHS1CK2		= %d\n", DdToptwo_GET_CLKSTOP2_UHS1CK2()));
	Ddim_Print(("CLKSTOP2_UHS2CK		= %d\n", DdToptwo_GET_CLKSTOP2_UHS2CK()));
	Ddim_Print(("CLKSTOP2_NFCK			= %d\n", DdToptwo_GET_CLKSTOP2_NFCK()));
	Ddim_Print(("CLKSTOP2_EMMCCK		= %d\n", DdToptwo_GET_CLKSTOP2_EMMCCK()));
	Ddim_Print(("CLKSTOP2_NETSECCK		= %d\n", DdToptwo_GET_CLKSTOP2_NETSECCK()));
	Ddim_Print(("CLKSTOP2_NETRCK		= %d\n", DdToptwo_GET_CLKSTOP2_NETRCK()));
	Ddim_Print(("CLKSTOP2_EXSAX			= %d\n", DdToptwo_GET_CLKSTOP2_EXSAX()));
	Ddim_Print(("CLKSTOP2_SPICK			= %d\n", DdToptwo_GET_CLKSTOP2_SPICK()));
	Ddim_Print(("CLKSTOP2_SLIMB00CK		= %d\n", DdToptwo_GET_CLKSTOP2_SLIMB00CK()));
	Ddim_Print(("CLKSTOP2_SLIMB01CK		= %d\n", DdToptwo_GET_CLKSTOP2_SLIMB01CK()));
	Ddim_Print(("CLKSTOP2_SLIMB10CK		= %d\n", DdToptwo_GET_CLKSTOP2_SLIMB10CK()));
	Ddim_Print(("CLKSTOP2_SLIMB11CK		= %d\n", DdToptwo_GET_CLKSTOP2_SLIMB11CK()));
	Ddim_Print(("CLKSTOP2_PCISUPPCK		= %d\n", DdToptwo_GET_CLKSTOP2_PCISUPPCK()));
	Ddim_Print(("CLKSTOP2 = %08lX\n", DdToptwo_GET_CLKSTOP2()));
}

static void ctGetClockClkstop3(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.CLKSTOP3.bit.IIPCK		= 1;
	IO_CHIPTOP.CLKSTOP3.bit.IIPAP		= 1;
	IO_CHIPTOP.CLKSTOP3.bit.IIPAH		= 1;
	IO_CHIPTOP.CLKSTOP3.bit.IIPAX		= 1;
	IO_CHIPTOP.CLKSTOP3.bit.LCDCK		= 1;
	IO_CHIPTOP.CLKSTOP3.bit.HIFCK		= 1;
	IO_CHIPTOP.CLKSTOP3.bit.MIFCK		= 1;
	IO_CHIPTOP.CLKSTOP3.bit.DISPAP		= 1;
	IO_CHIPTOP.CLKSTOP3.bit.DISPAH		= 1;
	IO_CHIPTOP.CLKSTOP3.bit.DISPAX		= 1;
	IO_CHIPTOP.CLKSTOP3.bit.JPGCK		= 1;
	IO_CHIPTOP.CLKSTOP3.bit.JPGAX		= 1;
	IO_CHIPTOP.CLKSTOP3.bit.JPGAH		= 1;
	IO_CHIPTOP.CLKSTOP3.bit.JPGAP		= 1;
	IO_CHIPTOP.CLKSTOP3.bit.PDM0CK		= 1;
	IO_CHIPTOP.CLKSTOP3.bit.PDM1CK		= 1;
#endif

	Ddim_Print(("CLKSTOP3_IIPCK		= %d\n", DdToptwo_GET_CLKSTOP3_IIPCK()));
	Ddim_Print(("CLKSTOP3_IIPAP		= %d\n", DdToptwo_GET_CLKSTOP3_IIPAP()));
	Ddim_Print(("CLKSTOP3_IIPAH		= %d\n", DdToptwo_GET_CLKSTOP3_IIPAH()));
	Ddim_Print(("CLKSTOP3_IIPAX		= %d\n", DdToptwo_GET_CLKSTOP3_IIPAX()));
	Ddim_Print(("CLKSTOP3_LCDCK		= %d\n", DdToptwo_GET_CLKSTOP3_LCDCK()));
	Ddim_Print(("CLKSTOP3_HIFCK		= %d\n", DdToptwo_GET_CLKSTOP3_HIFCK()));
	Ddim_Print(("CLKSTOP3_MIFCK		= %d\n", DdToptwo_GET_CLKSTOP3_MIFCK()));
	Ddim_Print(("CLKSTOP3_DISPAP	= %d\n", DdToptwo_GET_CLKSTOP3_DISPAP()));
	Ddim_Print(("CLKSTOP3_DISPAH	= %d\n", DdToptwo_GET_CLKSTOP3_DISPAH()));
	Ddim_Print(("CLKSTOP3_DISPAX	= %d\n", DdToptwo_GET_CLKSTOP3_DISPAX()));
	Ddim_Print(("CLKSTOP3_JPGAX		= %d\n", DdToptwo_GET_CLKSTOP3_JPGAX()));
	Ddim_Print(("CLKSTOP3_JPGCK		= %d\n", DdToptwo_GET_CLKSTOP3_JPGCK()));
	Ddim_Print(("CLKSTOP3_JPGAH		= %d\n", DdToptwo_GET_CLKSTOP3_JPGAH()));
	Ddim_Print(("CLKSTOP3_JPGAP		= %d\n", DdToptwo_GET_CLKSTOP3_JPGAP()));
	Ddim_Print(("CLKSTOP3_PDM0CK	= %d\n", DdToptwo_GET_CLKSTOP3_PDM0CK()));
	Ddim_Print(("CLKSTOP3_PDM1CK	= %d\n", DdToptwo_GET_CLKSTOP3_PDM1CK()));
	Ddim_Print(("CLKSTOP3 = %08lX\n", DdToptwo_GET_CLKSTOP3()));
}

static void ctGetClockClkstop4(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.CLKSTOP4.bit.GPUCK		= 1;
	IO_CHIPTOP.CLKSTOP4.bit.GPUAP		= 1;
	IO_CHIPTOP.CLKSTOP4.bit.GPUAH		= 1;
	IO_CHIPTOP.CLKSTOP4.bit.GPUAX		= 1;
	IO_CHIPTOP.CLKSTOP4.bit.FPT0CK		= 1;
	IO_CHIPTOP.CLKSTOP4.bit.FPT0AP		= 1;
	IO_CHIPTOP.CLKSTOP4.bit.FPT0AH		= 1;
	IO_CHIPTOP.CLKSTOP4.bit.FPT0AX		= 1;
	IO_CHIPTOP.CLKSTOP4.bit.FPT1CK		= 1;
	IO_CHIPTOP.CLKSTOP4.bit.FPT1AP		= 1;
	IO_CHIPTOP.CLKSTOP4.bit.FPT1AH		= 1;
	IO_CHIPTOP.CLKSTOP4.bit.FPT1AX		= 1;
	IO_CHIPTOP.CLKSTOP4.bit.APCK0		= 1;
	IO_CHIPTOP.CLKSTOP4.bit.APCK1		= 1;
	IO_CHIPTOP.CLKSTOP4.bit.APCK2		= 1;
	IO_CHIPTOP.CLKSTOP4.bit.APCK3		= 1;
#endif

	Ddim_Print(("CLKSTOP4_GPUCK		= %d\n", DdToptwo_GET_CLKSTOP4_GPUCK()));
	Ddim_Print(("CLKSTOP4_GPUAP		= %d\n", DdToptwo_GET_CLKSTOP4_GPUAP()));
	Ddim_Print(("CLKSTOP4_GPUAH		= %d\n", DdToptwo_GET_CLKSTOP4_GPUAH()));
	Ddim_Print(("CLKSTOP4_GPUAX		= %d\n", DdToptwo_GET_CLKSTOP4_GPUAX()));
	Ddim_Print(("CLKSTOP4_FPT0CK	= %d\n", DdToptwo_GET_CLKSTOP4_FPT0CK()));
	Ddim_Print(("CLKSTOP4_FPT0AP	= %d\n", DdToptwo_GET_CLKSTOP4_FPT0AP()));
	Ddim_Print(("CLKSTOP4_FPT0AH	= %d\n", DdToptwo_GET_CLKSTOP4_FPT0AH()));
	Ddim_Print(("CLKSTOP4_FPT0AX	= %d\n", DdToptwo_GET_CLKSTOP4_FPT0AX()));
	Ddim_Print(("CLKSTOP4_FPT1CK	= %d\n", DdToptwo_GET_CLKSTOP4_FPT1CK()));
	Ddim_Print(("CLKSTOP4_FPT1AP	= %d\n", DdToptwo_GET_CLKSTOP4_FPT1AP()));
	Ddim_Print(("CLKSTOP4_FPT1AH	= %d\n", DdToptwo_GET_CLKSTOP4_FPT1AH()));
	Ddim_Print(("CLKSTOP4_FPT1AX	= %d\n", DdToptwo_GET_CLKSTOP4_FPT1AX()));
	Ddim_Print(("CLKSTOP4_APCK0		= %d\n", DdToptwo_GET_CLKSTOP4_APCK0()));
	Ddim_Print(("CLKSTOP4_APCK1		= %d\n", DdToptwo_GET_CLKSTOP4_APCK1()));
	Ddim_Print(("CLKSTOP4_APCK2		= %d\n", DdToptwo_GET_CLKSTOP4_APCK2()));
	Ddim_Print(("CLKSTOP4_APCK3		= %d\n", DdToptwo_GET_CLKSTOP4_APCK3()));
	Ddim_Print(("CLKSTOP4 = %08lX\n", DdToptwo_GET_CLKSTOP4()));
}

static void ctGetClockClkstop5(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.CLKSTOP5.bit.MICAX0		= 1;
	IO_CHIPTOP.CLKSTOP5.bit.MICAX1		= 1;
	IO_CHIPTOP.CLKSTOP5.bit.MICAX2		= 1;
	IO_CHIPTOP.CLKSTOP5.bit.MICAX3		= 1;
	IO_CHIPTOP.CLKSTOP5.bit.MICAX4		= 1;
	IO_CHIPTOP.CLKSTOP5.bit.MICAX5		= 1;
	IO_CHIPTOP.CLKSTOP5.bit.MICAX6		= 1;
	IO_CHIPTOP.CLKSTOP5.bit.MICAP0		= 1;
	IO_CHIPTOP.CLKSTOP5.bit.MICAP1		= 1;
	IO_CHIPTOP.CLKSTOP5.bit.MICAP2		= 1;
	IO_CHIPTOP.CLKSTOP5.bit.MICAP3		= 1;
	IO_CHIPTOP.CLKSTOP5.bit.MICAP4		= 1;
	IO_CHIPTOP.CLKSTOP5.bit.MICAP5		= 1;
	IO_CHIPTOP.CLKSTOP5.bit.MICAP6		= 1;
#endif

	Ddim_Print(("CLKSTOP5_MICAX0		= %d\n", DdToptwo_GET_CLKSTOP5_MICAX0()));
	Ddim_Print(("CLKSTOP5_MICAX1		= %d\n", DdToptwo_GET_CLKSTOP5_MICAX1()));
	Ddim_Print(("CLKSTOP5_MICAX2		= %d\n", DdToptwo_GET_CLKSTOP5_MICAX2()));
	Ddim_Print(("CLKSTOP5_MICAX3		= %d\n", DdToptwo_GET_CLKSTOP5_MICAX3()));
	Ddim_Print(("CLKSTOP5_MICAX4		= %d\n", DdToptwo_GET_CLKSTOP5_MICAX4()));
	Ddim_Print(("CLKSTOP5_MICAX5		= %d\n", DdToptwo_GET_CLKSTOP5_MICAX5()));
	Ddim_Print(("CLKSTOP5_MICAX6		= %d\n", DdToptwo_GET_CLKSTOP5_MICAX6()));
	Ddim_Print(("CLKSTOP5_MICAP0		= %d\n", DdToptwo_GET_CLKSTOP5_MICAP0()));
	Ddim_Print(("CLKSTOP5_MICAP1		= %d\n", DdToptwo_GET_CLKSTOP5_MICAP1()));
	Ddim_Print(("CLKSTOP5_MICAP2		= %d\n", DdToptwo_GET_CLKSTOP5_MICAP2()));
	Ddim_Print(("CLKSTOP5_MICAP3		= %d\n", DdToptwo_GET_CLKSTOP5_MICAP3()));
	Ddim_Print(("CLKSTOP5_MICAP4		= %d\n", DdToptwo_GET_CLKSTOP5_MICAP4()));
	Ddim_Print(("CLKSTOP5_MICAP5		= %d\n", DdToptwo_GET_CLKSTOP5_MICAP5()));
	Ddim_Print(("CLKSTOP5_MICAP6		= %d\n", DdToptwo_GET_CLKSTOP5_MICAP6()));
	Ddim_Print(("CLKSTOP5 = %08lX\n", DdToptwo_GET_CLKSTOP5()));
}

static void ctGetClockClkstop6(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.CLKSTOP6.bit.MICAH1		= 1;
	IO_CHIPTOP.CLKSTOP6.bit.MICAH2		= 1;
	IO_CHIPTOP.CLKSTOP6.bit.MICAH3		= 1;
	IO_CHIPTOP.CLKSTOP6.bit.IMGAX		= 1;
	IO_CHIPTOP.CLKSTOP6.bit.IMGAH0		= 1;
	IO_CHIPTOP.CLKSTOP6.bit.IMGAH1		= 1;
	IO_CHIPTOP.CLKSTOP6.bit.IMGAH3		= 1;
	IO_CHIPTOP.CLKSTOP6.bit.IMGAP3		= 1;
	IO_CHIPTOP.CLKSTOP6.bit.REGAP		= 1;
	IO_CHIPTOP.CLKSTOP6.bit.XCHAX		= 1;
	IO_CHIPTOP.CLKSTOP6.bit.XCHAP		= 1;
	IO_CHIPTOP.CLKSTOP6.bit.ELACK		= 1;
	IO_CHIPTOP.CLKSTOP6.bit.ELAAX		= 1;
	IO_CHIPTOP.CLKSTOP6.bit.ELAAP		= 1;
#endif

	Ddim_Print(("CLKSTOP6_MICAH1		= %d\n", DdToptwo_GET_CLKSTOP6_MICAH1()));
	Ddim_Print(("CLKSTOP6_MICAH2		= %d\n", DdToptwo_GET_CLKSTOP6_MICAH2()));
	Ddim_Print(("CLKSTOP6_MICAH3		= %d\n", DdToptwo_GET_CLKSTOP6_MICAH3()));
	Ddim_Print(("CLKSTOP6_IMGAX		= %d\n", DdToptwo_GET_CLKSTOP6_IMGAX()));
	Ddim_Print(("CLKSTOP6_IMGAH0		= %d\n", DdToptwo_GET_CLKSTOP6_IMGAH0()));
	Ddim_Print(("CLKSTOP6_IMGAH1		= %d\n", DdToptwo_GET_CLKSTOP6_IMGAH1()));
	Ddim_Print(("CLKSTOP6_IMGAH3		= %d\n", DdToptwo_GET_CLKSTOP6_IMGAH3()));
	Ddim_Print(("CLKSTOP6_IMGAP3		= %d\n", DdToptwo_GET_CLKSTOP6_IMGAP3()));
	Ddim_Print(("CLKSTOP6_REGAP		= %d\n", DdToptwo_GET_CLKSTOP6_REGAP()));
	Ddim_Print(("CLKSTOP6_XCHAX		= %d\n", DdToptwo_GET_CLKSTOP6_XCHAX()));
	Ddim_Print(("CLKSTOP6_XCHAP		= %d\n", DdToptwo_GET_CLKSTOP6_XCHAP()));
	Ddim_Print(("CLKSTOP6_ELACK		= %d\n", DdToptwo_GET_CLKSTOP6_ELACK()));
	Ddim_Print(("CLKSTOP6_ELAAX		= %d\n", DdToptwo_GET_CLKSTOP6_ELAAX()));
	Ddim_Print(("CLKSTOP6_ELAAP		= %d\n", DdToptwo_GET_CLKSTOP6_ELAAP()));
	Ddim_Print(("CLKSTOP6 = %08lX\n", DdToptwo_GET_CLKSTOP6()));
}

static void ctSetClockClkstop1(kint argc, kchar** argv)
{
	kulong val;

	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "DSPCK" ) ) {
			DdToptwo_SET_CLKSTOP1_DSPCK(val);
			Ddim_Print(("It set CLKSTOP1_DSPCK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP1.bit.DSPCK	= %d\n", IO_CHIPTOP.CLKSTOP1.bit.DSPCK));
		}else if (  0 == strcmp( argv[4], "DSPAX" ) ) {
			DdToptwo_SET_CLKSTOP1_DSPAX(val);
			Ddim_Print(("It set CLKSTOP1_DSPAX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP1.bit.DSPAX	= %d\n", IO_CHIPTOP.CLKSTOP1.bit.DSPAX));
		}else if (  0 == strcmp( argv[4], "SENCK" ) ) {
			DdToptwo_SET_CLKSTOP1_SENCK(val);
			Ddim_Print(("It set CLKSTOP1_SENCK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP1.bit.SENCK	= %d\n", IO_CHIPTOP.CLKSTOP1.bit.SENCK));
		}else if (  0 == strcmp( argv[4], "SENAX" ) ) {
			DdToptwo_SET_CLKSTOP1_SENAX(val);
			Ddim_Print(("It set CLKSTOP1_SENAX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP1.bit.SENAX	= %d\n", IO_CHIPTOP.CLKSTOP1.bit.SENAX));
		}else if (  0 == strcmp( argv[4], "SENAH" ) ) {
			DdToptwo_SET_CLKSTOP1_SENAH(val);
			Ddim_Print(("It set CLKSTOP1_SENAH Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP1.bit.SENAH	= %d\n", IO_CHIPTOP.CLKSTOP1.bit.SENAH));
		}else if (  0 == strcmp( argv[4], "SENAP" ) ) {
			DdToptwo_SET_CLKSTOP1_SENAP(val);
			Ddim_Print(("It set CLKSTOP1_SENAP Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP1.bit.SENAP	= %d\n", IO_CHIPTOP.CLKSTOP1.bit.SENAP));
		}else if (  0 == strcmp( argv[4], "GPIOAP" ) ) {
			DdToptwo_SET_CLKSTOP1_GPIOAP(val);
			Ddim_Print(("It set CLKSTOP1_GPIOAP Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP1.bit.GPIOAP	= %d\n", IO_CHIPTOP.CLKSTOP1.bit.GPIOAP));
		}else if (  0 == strcmp( argv[4], "AU0CK" ) ) {
			DdToptwo_SET_CLKSTOP1_AU0CK(val);
			Ddim_Print(("It set CLKSTOP1_AU0CK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP1.bit.AU0CK	= %d\n", IO_CHIPTOP.CLKSTOP1.bit.AU0CK));
		}else if (  0 == strcmp( argv[4], "AU2CK" ) ) {
			DdToptwo_SET_CLKSTOP1_AU2CK(val);
			Ddim_Print(("It set CLKSTOP1_AU2CK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP1.bit.AU2CK	= %d\n", IO_CHIPTOP.CLKSTOP1.bit.AU2CK));
		}else if (  0 == strcmp( argv[4], "AU3CK" ) ) {
			DdToptwo_SET_CLKSTOP1_AU3CK(val);
			Ddim_Print(("It set CLKSTOP1_AU3CK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP1.bit.AU3CK	= %d\n", IO_CHIPTOP.CLKSTOP1.bit.AU3CK));
		}else if (  0 == strcmp( argv[4], "AU4CK" ) ) {
			DdToptwo_SET_CLKSTOP1_AU4CK(val);
			Ddim_Print(("It set CLKSTOP1_AU4CK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP1.bit.AU4CK	= %d\n", IO_CHIPTOP.CLKSTOP1.bit.AU4CK));
		}else if (  0 == strcmp( argv[4], "AU5CK" ) ) {
			DdToptwo_SET_CLKSTOP1_AU5CK(val);
			Ddim_Print(("It set CLKSTOP1_AU5CK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP1.bit.AU5CK	= %d\n", IO_CHIPTOP.CLKSTOP1.bit.AU5CK));
		}else if (  0 == strcmp( argv[4], "NETAUCK" ) ) {
			DdToptwo_SET_CLKSTOP1_NETAUCK(val);
			Ddim_Print(("It set CLKSTOP1_NETAUCK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP1.bit.NETAUCK	= %d\n", IO_CHIPTOP.CLKSTOP1.bit.NETAUCK));
		}else if (  0 == strcmp( argv[4], "TEMPCK" ) ) {
			DdToptwo_SET_CLKSTOP1_TEMPCK(val);
			Ddim_Print(("It set CLKSTOP1_TEMPCK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP1.bit.TEMPCK	= %d\n", IO_CHIPTOP.CLKSTOP1.bit.TEMPCK));
		}
		else {
			Ddim_Print(("please check 4th parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void ctSetClockClkstop2(kint argc, kchar** argv)
{
	kulong val;

	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "RCK" ) ) {
			DdToptwo_SET_CLKSTOP2_RCK(val);
			Ddim_Print(("It set CLKSTOP2_RCK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP2.bit.RCK	= %d\n", IO_CHIPTOP.CLKSTOP2.bit.RCK));
		}else if (  0 == strcmp( argv[4], "UHS1CK0" ) ) {
			DdToptwo_SET_CLKSTOP2_UHS1CK0(val);
			Ddim_Print(("It set CLKSTOP2_UHS1CK0 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP2.bit.UHS1CK0	= %d\n", IO_CHIPTOP.CLKSTOP2.bit.UHS1CK0));
		}else if (  0 == strcmp( argv[4], "UHS1CK1" ) ) {
			DdToptwo_SET_CLKSTOP2_UHS1CK1(val);
			Ddim_Print(("It set CLKSTOP2_UHS1CK1 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP2.bit.UHS1CK1	= %d\n", IO_CHIPTOP.CLKSTOP2.bit.UHS1CK1));
		}else if (  0 == strcmp( argv[4], "UHS1CK2" ) ) {
			DdToptwo_SET_CLKSTOP2_UHS1CK2(val);
			Ddim_Print(("It set CLKSTOP2_UHS1CK2 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP2.bit.UHS1CK2	= %d\n", IO_CHIPTOP.CLKSTOP2.bit.UHS1CK2));
		}else if (  0 == strcmp( argv[4], "UHS2CK" ) ) {
			DdToptwo_SET_CLKSTOP2_UHS2CK(val);
			Ddim_Print(("It set CLKSTOP2_UHS2CK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP2.bit.UHS2CK	= %d\n", IO_CHIPTOP.CLKSTOP2.bit.UHS2CK));
		}else if (  0 == strcmp( argv[4], "NFCK" ) ) {
			DdToptwo_SET_CLKSTOP2_NFCK(val);
			Ddim_Print(("It set CLKSTOP2_NFCK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP2.bit.NFCK	= %d\n", IO_CHIPTOP.CLKSTOP2.bit.NFCK));
		}else if (  0 == strcmp( argv[4], "EMMCCK" ) ) {
			DdToptwo_SET_CLKSTOP2_EMMCCK(val);
			Ddim_Print(("It set CLKSTOP2_EMMCCK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP2.bit.EMMCCK	= %d\n", IO_CHIPTOP.CLKSTOP2.bit.EMMCCK));
		}else if (  0 == strcmp( argv[4], "NETSECCK" ) ) {
			DdToptwo_SET_CLKSTOP2_NETSECCK(val);
			Ddim_Print(("It set CLKSTOP2_NETSECCK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP2.bit.NETSECCK	= %d\n", IO_CHIPTOP.CLKSTOP2.bit.NETSECCK));
		}else if (  0 == strcmp( argv[4], "NETRCK" ) ) {
			DdToptwo_SET_CLKSTOP2_NETRCK(val);
			Ddim_Print(("It set CLKSTOP2_NETRCK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP2.bit.NETRCK	= %d\n", IO_CHIPTOP.CLKSTOP2.bit.NETRCK));
		}else if (  0 == strcmp( argv[4], "EXSAX" ) ) {
			DdToptwo_SET_CLKSTOP2_EXSAX(val);
			Ddim_Print(("It set CLKSTOP2_EXSAX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP2.bit.EXSAX	= %d\n", IO_CHIPTOP.CLKSTOP2.bit.EXSAX));
		}else if (  0 == strcmp( argv[4], "SPICK" ) ) {
			DdToptwo_SET_CLKSTOP2_SPICK(val);
			Ddim_Print(("It set CLKSTOP2_SPICK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP2.bit.SPICK	= %d\n", IO_CHIPTOP.CLKSTOP2.bit.SPICK));
		}else if (  0 == strcmp( argv[4], "SLIMB00CK" ) ) {
			DdToptwo_SET_CLKSTOP2_SLIMB00CK(val);
			Ddim_Print(("It set CLKSTOP2_SLIMB00CK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP2.bit.SLIMB00CK	= %d\n", IO_CHIPTOP.CLKSTOP2.bit.SLIMB00CK));
		}else if (  0 == strcmp( argv[4], "SLIMB01CK" ) ) {
			DdToptwo_SET_CLKSTOP2_SLIMB01CK(val);
			Ddim_Print(("It set CLKSTOP2_SLIMB01CK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP2.bit.SLIMB01CK	= %d\n", IO_CHIPTOP.CLKSTOP2.bit.SLIMB01CK));
		}else if (  0 == strcmp( argv[4], "SLIMB10CK" ) ) {
			DdToptwo_SET_CLKSTOP2_SLIMB10CK(val);
			Ddim_Print(("It set CLKSTOP2_SLIMB10CK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP2.bit.SLIMB10CK	= %d\n", IO_CHIPTOP.CLKSTOP2.bit.SLIMB10CK));
		}else if (  0 == strcmp( argv[4], "SLIMB11CK" ) ) {
			DdToptwo_SET_CLKSTOP2_SLIMB11CK(val);
			Ddim_Print(("It set CLKSTOP2_SLIMB11CK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP2.bit.SLIMB11CK	= %d\n", IO_CHIPTOP.CLKSTOP2.bit.SLIMB11CK));
		}else if (  0 == strcmp( argv[4], "PCISUPPCK" ) ) {
			DdToptwo_SET_CLKSTOP2_PCISUPPCK(val);
			Ddim_Print(("It set CLKSTOP2_PCISUPPCK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP2.bit.PCISUPPCK	= %d\n", IO_CHIPTOP.CLKSTOP2.bit.PCISUPPCK));
		}
		else {
			Ddim_Print(("please check 4th parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void ctSetClockClkstop3(kint argc, kchar** argv)
{
	kulong val;

	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "IIPCK" ) ) {
			DdToptwo_SET_CLKSTOP3_IIPCK(val);
			Ddim_Print(("It set CLKSTOP3_IIPCK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP3.bit.IIPCK	= %d\n", IO_CHIPTOP.CLKSTOP3.bit.IIPCK));
		}else if (  0 == strcmp( argv[4], "IIPAP" ) ) {
			DdToptwo_SET_CLKSTOP3_IIPAP(val);
			Ddim_Print(("It set CLKSTOP3_IIPAP Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP3.bit.IIPAP	= %d\n", IO_CHIPTOP.CLKSTOP3.bit.IIPAP));
		}else if (  0 == strcmp( argv[4], "IIPAH" ) ) {
			DdToptwo_SET_CLKSTOP3_IIPAH(val);
			Ddim_Print(("It set CLKSTOP3_IIPAH Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP3.bit.IIPAH	= %d\n", IO_CHIPTOP.CLKSTOP3.bit.IIPAH));
		}else if (  0 == strcmp( argv[4], "IIPAX" ) ) {
			DdToptwo_SET_CLKSTOP3_IIPAX(val);
			Ddim_Print(("It set CLKSTOP3_IIPAX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP3.bit.IIPAX	= %d\n", IO_CHIPTOP.CLKSTOP3.bit.IIPAX));
		}else if (  0 == strcmp( argv[4], "LCDCK" ) ) {
			DdToptwo_SET_CLKSTOP3_LCDCK(val);
			Ddim_Print(("It set CLKSTOP3_LCDCK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP3.bit.LCDCK	= %d\n", IO_CHIPTOP.CLKSTOP3.bit.LCDCK));
		}else if (  0 == strcmp( argv[4], "HIFCK" ) ) {
			DdToptwo_SET_CLKSTOP3_HIFCK(val);
			Ddim_Print(("It set CLKSTOP3_HIFCK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP3.bit.HIFCK	= %d\n", IO_CHIPTOP.CLKSTOP3.bit.HIFCK));
		}else if (  0 == strcmp( argv[4], "MIFCK" ) ) {
			DdToptwo_SET_CLKSTOP3_MIFCK(val);
			Ddim_Print(("It set CLKSTOP3_MIFCK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP3.bit.MIFCK	= %d\n", IO_CHIPTOP.CLKSTOP3.bit.MIFCK));
		}else if (  0 == strcmp( argv[4], "DISPAP" ) ) {
			DdToptwo_SET_CLKSTOP3_DISPAP(val);
			Ddim_Print(("It set CLKSTOP3_DISPAP Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP3.bit.DISPAP	= %d\n", IO_CHIPTOP.CLKSTOP3.bit.DISPAP));
		}else if (  0 == strcmp( argv[4], "DISPAH" ) ) {
			DdToptwo_SET_CLKSTOP3_DISPAH(val);
			Ddim_Print(("It set CLKSTOP3_DISPAH Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP3.bit.DISPAH	= %d\n", IO_CHIPTOP.CLKSTOP3.bit.DISPAH));
		}else if (  0 == strcmp( argv[4], "DISPAX" ) ) {
			DdToptwo_SET_CLKSTOP3_DISPAX(val);
			Ddim_Print(("It set CLKSTOP3_DISPAX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP3.bit.DISPAX	= %d\n", IO_CHIPTOP.CLKSTOP3.bit.DISPAX));
		}else if (  0 == strcmp( argv[4], "JPGCK" ) ) {
			DdToptwo_SET_CLKSTOP3_JPGCK(val);
			Ddim_Print(("It set CLKSTOP3_JPGCK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP3.bit.JPGCK	= %d\n", IO_CHIPTOP.CLKSTOP3.bit.JPGCK));
		}else if (  0 == strcmp( argv[4], "JPGAP" ) ) {
			DdToptwo_SET_CLKSTOP3_JPGAP(val);
			Ddim_Print(("It set CLKSTOP3_JPGAP Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP3.bit.JPGAP	= %d\n", IO_CHIPTOP.CLKSTOP3.bit.JPGAP));
		}else if (  0 == strcmp( argv[4], "JPGAH" ) ) {
			DdToptwo_SET_CLKSTOP3_JPGAH(val);
			Ddim_Print(("It set CLKSTOP3_JPGAH Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP3.bit.JPGAH	= %d\n", IO_CHIPTOP.CLKSTOP3.bit.JPGAH));
		}else if (  0 == strcmp( argv[4], "JPGAX" ) ) {
			DdToptwo_SET_CLKSTOP3_JPGAX(val);
			Ddim_Print(("It set CLKSTOP3_JPGAX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP3.bit.JPGAX	= %d\n", IO_CHIPTOP.CLKSTOP3.bit.JPGAX));
		}else if (  0 == strcmp( argv[4], "PDM0CK" ) ) {
			DdToptwo_SET_CLKSTOP3_PDM0CK(val);
			Ddim_Print(("It set CLKSTOP3_PDM0CK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP3.bit.PDM0CK	= %d\n", IO_CHIPTOP.CLKSTOP3.bit.PDM0CK));
		}else if (  0 == strcmp( argv[4], "PDM1CK" ) ) {
			DdToptwo_SET_CLKSTOP3_PDM1CK(val);
			Ddim_Print(("It set CLKSTOP3_PDM1CK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP3.bit.PDM1CK	= %d\n", IO_CHIPTOP.CLKSTOP3.bit.PDM1CK));
		}
		else {
			Ddim_Print(("please check 4th parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void ctSetClockClkstop4(kint argc, kchar** argv)
{
	kulong val;

	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "GPUCK" ) ) {
			DdToptwo_SET_CLKSTOP4_GPUCK(val);
			Ddim_Print(("It set CLKSTOP4_GPUCK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP4.bit.GPUCK	= %d\n", IO_CHIPTOP.CLKSTOP4.bit.GPUCK));
		}else if (  0 == strcmp( argv[4], "GPUAP" ) ) {
			DdToptwo_SET_CLKSTOP4_GPUAP(val);
			Ddim_Print(("It set CLKSTOP4_GPUAP Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP4.bit.GPUAP	= %d\n", IO_CHIPTOP.CLKSTOP4.bit.GPUAP));
		}else if (  0 == strcmp( argv[4], "GPUAH" ) ) {
			DdToptwo_SET_CLKSTOP4_GPUAH(val);
			Ddim_Print(("It set CLKSTOP4_GPUAH Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP4.bit.GPUAH	= %d\n", IO_CHIPTOP.CLKSTOP4.bit.GPUAH));
		}else if (  0 == strcmp( argv[4], "GPUAX" ) ) {
			DdToptwo_SET_CLKSTOP4_GPUAX(val);
			Ddim_Print(("It set CLKSTOP4_GPUAX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP4.bit.GPUAX	= %d\n", IO_CHIPTOP.CLKSTOP4.bit.GPUAX));
		}else if (  0 == strcmp( argv[4], "FPT0CK" ) ) {
			DdToptwo_SET_CLKSTOP4_FPT0CK(val);
			Ddim_Print(("It set CLKSTOP4_FPT0CK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP4.bit.FPT0CK	= %d\n", IO_CHIPTOP.CLKSTOP4.bit.FPT0CK));
		}else if (  0 == strcmp( argv[4], "FPT0AX" ) ) {
			DdToptwo_SET_CLKSTOP4_FPT0AX(val);
			Ddim_Print(("It set CLKSTOP4_FPT0AX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP4.bit.FPT0AX	= %d\n", IO_CHIPTOP.CLKSTOP4.bit.FPT0AX));
		}else if (  0 == strcmp( argv[4], "FPT0AH" ) ) {
			DdToptwo_SET_CLKSTOP4_FPT0AH(val);
			Ddim_Print(("It set CLKSTOP4_FPT0AH Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP4.bit.FPT0AH	= %d\n", IO_CHIPTOP.CLKSTOP4.bit.FPT0AH));
		}else if (  0 == strcmp( argv[4], "FPT0AP" ) ) {
			DdToptwo_SET_CLKSTOP4_FPT0AP(val);
			Ddim_Print(("It set CLKSTOP4_FPT0AP Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP4.bit.FPT0AP	= %d\n", IO_CHIPTOP.CLKSTOP4.bit.FPT0AP));
		}else if (  0 == strcmp( argv[4], "FPT1CK" ) ) {
			DdToptwo_SET_CLKSTOP4_FPT1CK(val);
			Ddim_Print(("It set CLKSTOP4_FPT1CK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP4.bit.FPT1CK	= %d\n", IO_CHIPTOP.CLKSTOP4.bit.FPT1CK));
		}else if (  0 == strcmp( argv[4], "FPT1AP" ) ) {
			DdToptwo_SET_CLKSTOP4_FPT1AP(val);
			Ddim_Print(("It set CLKSTOP4_FPT1AP Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP4.bit.FPT1AP	= %d\n", IO_CHIPTOP.CLKSTOP4.bit.FPT1AP));
		}else if (  0 == strcmp( argv[4], "FPT1AH" ) ) {
			DdToptwo_SET_CLKSTOP4_FPT1AH(val);
			Ddim_Print(("It set CLKSTOP4_FPT1AH Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP4.bit.FPT1AH	= %d\n", IO_CHIPTOP.CLKSTOP4.bit.FPT1AH));
		}else if (  0 == strcmp( argv[4], "FPT1AX" ) ) {
			DdToptwo_SET_CLKSTOP4_FPT1AX(val);
			Ddim_Print(("It set CLKSTOP4_FPT1AX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP4.bit.FPT1AX	= %d\n", IO_CHIPTOP.CLKSTOP4.bit.FPT1AX));
		}else if (  0 == strcmp( argv[4], "APCK0" ) ) {
			DdToptwo_SET_CLKSTOP4_APCK0(val);
			Ddim_Print(("It set CLKSTOP4_APCK0 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP4.bit.APCK0	= %d\n", IO_CHIPTOP.CLKSTOP4.bit.APCK0));
		}else if (  0 == strcmp( argv[4], "APCK1" ) ) {
			DdToptwo_SET_CLKSTOP4_APCK1(val);
			Ddim_Print(("It set CLKSTOP4_APCK1 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP4.bit.APCK1	= %d\n", IO_CHIPTOP.CLKSTOP4.bit.APCK1));
		}else if (  0 == strcmp( argv[4], "APCK2" ) ) {
			DdToptwo_SET_CLKSTOP4_APCK2(val);
			Ddim_Print(("It set CLKSTOP4_APCK2 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP4.bit.APCK2	= %d\n", IO_CHIPTOP.CLKSTOP4.bit.APCK2));
		}else if (  0 == strcmp( argv[4], "APCK3" ) ) {
			DdToptwo_SET_CLKSTOP4_APCK3(val);
			Ddim_Print(("It set CLKSTOP4_APCK3 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP4.bit.APCK3	= %d\n", IO_CHIPTOP.CLKSTOP4.bit.APCK3));
		}
		else {
			Ddim_Print(("please check 4th parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void ctSetClockClkstop5(kint argc, kchar** argv)
{
	kulong val;

	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "MICAX0" ) ) {
			DdToptwo_SET_CLKSTOP5_MICAX0(val);
			Ddim_Print(("It set CLKSTOP5_MICAX0 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP5.bit.MICAX0	= %d\n", IO_CHIPTOP.CLKSTOP5.bit.MICAX0));
		}else if (  0 == strcmp( argv[4], "MICAX1" ) ) {
			DdToptwo_SET_CLKSTOP5_MICAX1(val);
			Ddim_Print(("It set CLKSTOP5_MICAX1 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP5.bit.MICAX1	= %d\n", IO_CHIPTOP.CLKSTOP5.bit.MICAX1));
		}else if (  0 == strcmp( argv[4], "MICAX2" ) ) {
			DdToptwo_SET_CLKSTOP5_MICAX2(val);
			Ddim_Print(("It set CLKSTOP5_MICAX2 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP5.bit.MICAX2	= %d\n", IO_CHIPTOP.CLKSTOP5.bit.MICAX2));
		}else if (  0 == strcmp( argv[4], "MICAX3" ) ) {
			DdToptwo_SET_CLKSTOP5_MICAX3(val);
			Ddim_Print(("It set CLKSTOP5_MICAX3 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP5.bit.MICAX3	= %d\n", IO_CHIPTOP.CLKSTOP5.bit.MICAX3));
		}else if (  0 == strcmp( argv[4], "MICAX4" ) ) {
			DdToptwo_SET_CLKSTOP5_MICAX4(val);
			Ddim_Print(("It set CLKSTOP5_MICAX4 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP5.bit.MICAX4	= %d\n", IO_CHIPTOP.CLKSTOP5.bit.MICAX4));
		}else if (  0 == strcmp( argv[4], "MICAX5" ) ) {
			DdToptwo_SET_CLKSTOP5_MICAX5(val);
			Ddim_Print(("It set CLKSTOP5_MICAX5 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP5.bit.MICAX5	= %d\n", IO_CHIPTOP.CLKSTOP5.bit.MICAX5));
		}else if (  0 == strcmp( argv[4], "MICAX6" ) ) {
			DdToptwo_SET_CLKSTOP5_MICAX6(val);
			Ddim_Print(("It set CLKSTOP5_MICAX6 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP5.bit.MICAX6	= %d\n", IO_CHIPTOP.CLKSTOP5.bit.MICAX6));
		}else if (  0 == strcmp( argv[4], "MICAP0" ) ) {
			DdToptwo_SET_CLKSTOP5_MICAP0(val);
			Ddim_Print(("It set CLKSTOP5_MICAP0 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP5.bit.MICAP0	= %d\n", IO_CHIPTOP.CLKSTOP5.bit.MICAP0));
		}else if (  0 == strcmp( argv[4], "MICAP1" ) ) {
			DdToptwo_SET_CLKSTOP5_MICAP1(val);
			Ddim_Print(("It set CLKSTOP5_MICAP1 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP5.bit.MICAP1	= %d\n", IO_CHIPTOP.CLKSTOP5.bit.MICAP1));
		}else if (  0 == strcmp( argv[4], "MICAP2" ) ) {
			DdToptwo_SET_CLKSTOP5_MICAP2(val);
			Ddim_Print(("It set CLKSTOP5_MICAP2 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP5.bit.MICAP2	= %d\n", IO_CHIPTOP.CLKSTOP5.bit.MICAP2));
		}else if (  0 == strcmp( argv[4], "MICAP3" ) ) {
			DdToptwo_SET_CLKSTOP5_MICAP3(val);
			Ddim_Print(("It set CLKSTOP5_MICAP3 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP5.bit.MICAP3	= %d\n", IO_CHIPTOP.CLKSTOP5.bit.MICAP3));
		}else if (  0 == strcmp( argv[4], "MICAP4" ) ) {
			DdToptwo_SET_CLKSTOP5_MICAP4(val);
			Ddim_Print(("It set CLKSTOP5_MICAP4 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP5.bit.MICAP4	= %d\n", IO_CHIPTOP.CLKSTOP5.bit.MICAP4));
		}else if (  0 == strcmp( argv[4], "MICAP5" ) ) {
			DdToptwo_SET_CLKSTOP5_MICAP5(val);
			Ddim_Print(("It set CLKSTOP5_MICAP5 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP5.bit.MICAP5	= %d\n", IO_CHIPTOP.CLKSTOP5.bit.MICAP5));
		}else if (  0 == strcmp( argv[4], "MICAP6" ) ) {
			DdToptwo_SET_CLKSTOP5_MICAP6(val);
			Ddim_Print(("It set CLKSTOP5_MICAP6 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP5.bit.MICAP6	= %d\n", IO_CHIPTOP.CLKSTOP5.bit.MICAP6));
		}
		else {
			Ddim_Print(("please check 4th parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void ctSetClockClkstop6(kint argc, kchar** argv)
{
	kulong val;

	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "MICAH1" ) ) {
			DdToptwo_SET_CLKSTOP6_MICAH1(val);
			Ddim_Print(("It set CLKSTOP6_MICAH1 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP6.bit.MICAH1	= %d\n", IO_CHIPTOP.CLKSTOP6.bit.MICAH1));
		}else if (  0 == strcmp( argv[4], "MICAH2" ) ) {
			DdToptwo_SET_CLKSTOP6_MICAH2(val);
			Ddim_Print(("It set CLKSTOP6_MICAH2 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP6.bit.MICAH2	= %d\n", IO_CHIPTOP.CLKSTOP6.bit.MICAH2));
		}else if (  0 == strcmp( argv[4], "MICAH3" ) ) {
			DdToptwo_SET_CLKSTOP6_MICAH3(val);
			Ddim_Print(("It set CLKSTOP6_MICAH3 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP6.bit.MICAH3	= %d\n", IO_CHIPTOP.CLKSTOP6.bit.MICAH3));
		}else if (  0 == strcmp( argv[4], "IMGAX" ) ) {
			DdToptwo_SET_CLKSTOP6_IMGAX(val);
			Ddim_Print(("It set CLKSTOP6_IMGAX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP6.bit.IMGAX	= %d\n", IO_CHIPTOP.CLKSTOP6.bit.IMGAX));
		}else if (  0 == strcmp( argv[4], "IMGAH0" ) ) {
			DdToptwo_SET_CLKSTOP6_IMGAH0(val);
			Ddim_Print(("It set CLKSTOP6_IMGAH0 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP6.bit.IMGAH0	= %d\n", IO_CHIPTOP.CLKSTOP6.bit.IMGAH0));
		}else if (  0 == strcmp( argv[4], "IMGAH1" ) ) {
			DdToptwo_SET_CLKSTOP6_IMGAH1(val);
			Ddim_Print(("It set CLKSTOP6_IMGAH1 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP6.bit.IMGAH1	= %d\n", IO_CHIPTOP.CLKSTOP6.bit.IMGAH1));
		}else if (  0 == strcmp( argv[4], "IMGAH3" ) ) {
			DdToptwo_SET_CLKSTOP6_IMGAH3(val);
			Ddim_Print(("It set CLKSTOP6_IMGAH3 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP6.bit.IMGAH3	= %d\n", IO_CHIPTOP.CLKSTOP6.bit.IMGAH3));
		}else if (  0 == strcmp( argv[4], "IMGAP3" ) ) {
			DdToptwo_SET_CLKSTOP6_IMGAP3(val);
			Ddim_Print(("It set CLKSTOP6_IMGAP3 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP6.bit.IMGAP3	= %d\n", IO_CHIPTOP.CLKSTOP6.bit.IMGAP3));
		}else if (  0 == strcmp( argv[4], "REGAP" ) ) {
			DdToptwo_SET_CLKSTOP6_REGAP(val);
			Ddim_Print(("It set CLKSTOP6_REGAP Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP6.bit.REGAP	= %d\n", IO_CHIPTOP.CLKSTOP6.bit.REGAP));
		}else if (  0 == strcmp( argv[4], "XCHAX" ) ) {
			DdToptwo_SET_CLKSTOP6_XCHAX(val);
			Ddim_Print(("It set CLKSTOP6_XCHAX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP6.bit.XCHAX	= %d\n", IO_CHIPTOP.CLKSTOP6.bit.XCHAX));
		}else if (  0 == strcmp( argv[4], "XCHAP" ) ) {
			DdToptwo_SET_CLKSTOP6_XCHAP(val);
			Ddim_Print(("It set CLKSTOP6_XCHAP Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP6.bit.XCHAP	= %d\n", IO_CHIPTOP.CLKSTOP6.bit.XCHAP));
		}else if (  0 == strcmp( argv[4], "ELACK" ) ) {
			DdToptwo_SET_CLKSTOP6_ELACK(val);
			Ddim_Print(("It set CLKSTOP6_ELACK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP6.bit.ELACK	= %d\n", IO_CHIPTOP.CLKSTOP6.bit.ELACK));
		}else if (  0 == strcmp( argv[4], "ELAAX" ) ) {
			DdToptwo_SET_CLKSTOP6_ELAAX(val);
			Ddim_Print(("It set CLKSTOP6_ELAAX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP6.bit.ELAAX	= %d\n", IO_CHIPTOP.CLKSTOP6.bit.ELAAX));
		}else if (  0 == strcmp( argv[4], "ELAAP" ) ) {
			DdToptwo_SET_CLKSTOP6_ELAAP(val);
			Ddim_Print(("It set CLKSTOP6_ELAAP Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP6.bit.ELAAP	= %d\n", IO_CHIPTOP.CLKSTOP6.bit.ELAAP));
		}
		else {
			Ddim_Print(("please check 4th parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}
/****************
* PUBLIC
*/
void ct_clock_clkstop_set(CtClockClkstop *self)
{
	CtClockClkstopPrivate *priv = CT_CLOCK_CLKSTOP_GET_PRIVATE(self);
    
    if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clkstop1" ) ) {
        ctSetClockClkstop1( ((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv );
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clkstop2" ) ) {
        ctSetClockClkstop2( ((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv );
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clkstop3" ) ) {
        ctSetClockClkstop3( ((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv );
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clkstop4" ) ) {
        ctSetClockClkstop4( ((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv );
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clkstop5" ) ) {
        ctSetClockClkstop5( ((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv );
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clkstop6" ) ) {
        ctSetClockClkstop6( ((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv );
    }else {
		ct_dd_parameter_set_parameter((CtDdParameter *)priv->ctClockClkstopMid,
				((CtDdParameter *)self)->argc,((CtDdParameter *)self)->argv);
		ct_clock_clkstop_mid_set(priv->ctClockClkstopMid);
	}
}

void ct_clock_clkstop_get(CtClockClkstop *self)
{
   	CtClockClkstopPrivate *priv = CT_CLOCK_CLKSTOP_GET_PRIVATE(self);

    if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clkstop1" ) ) {
        ctGetClockClkstop1();
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clkstop2" ) ) {
        ctGetClockClkstop2();
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clkstop3" ) ) {
        ctGetClockClkstop3();
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clkstop4" ) ) {
        ctGetClockClkstop4();
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clkstop5" ) ) {
        ctGetClockClkstop5();
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clkstop6" ) ) {
        ctGetClockClkstop6();
    }else {
		ct_dd_parameter_set_parameter((CtDdParameter *)priv->ctClockClkstopMid,
				((CtDdParameter *)self)->argc,((CtDdParameter *)self)->argv);
		ct_clock_clkstop_mid_get(priv->ctClockClkstopMid);
	}
}

CtClockClkstop* ct_clock_clkstop_new(void) 
{
    CtClockClkstop *self = k_object_new_with_private(CT_TYPE_CLOCK_CLKSTOP, sizeof(CtClockClkstopPrivate));
    return self;
}
