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
#include "ctclockclkstopmid.h"
#include "ctclockclkstopend.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtClockClkstopMid, ct_clock_clkstop_mid);
#define CT_CLOCK_CLKSTOP_MID_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtClockClkstopMidPrivate,CT_TYPE_CLOCK_CLKSTOP_MID))

struct _CtClockClkstopMidPrivate
{
	CtClockClkstopEnd* ctClockClkstopEnd;
};
/****************
* DECLS
*/
static void 			ct_clock_clkstop_mid_constructor(CtClockClkstopMid *self);
static void 			ct_clock_clkstop_mid_destructor(CtClockClkstopMid *self);
static void 			ctGetClockClkstop7(void);
static void 			ctGetClockClkstop8(void);
static void 			ctGetClockClkstop9(void);
static void 			ctGetClockClkstop10(void);
static void 			ctSetClockClkstop7(kint argc, kchar** argv);
static void 			ctSetClockClkstop8(kint argc, kchar** argv);
static void 			ctSetClockClkstop9(kint argc, kchar** argv);
static void 			ctSetClockClkstop10(kint argc, kchar** argv);
/****************
* IMPL
*/
static void ct_clock_clkstop_mid_constructor(CtClockClkstopMid *self) 
{
	CtClockClkstopMidPrivate *priv = CT_CLOCK_CLKSTOP_MID_GET_PRIVATE(self);
	priv->ctClockClkstopEnd = ct_clock_clkstop_end_new();
}

static void ct_clock_clkstop_mid_destructor(CtClockClkstopMid *self) 
{
	CtClockClkstopMidPrivate *priv = CT_CLOCK_CLKSTOP_MID_GET_PRIVATE(self);
	k_object_unref(priv->ctClockClkstopEnd);
}

static void ctGetClockClkstop7(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.CLKSTOP7.bit.IPUFDCK		= 1;
	IO_CHIPTOP.CLKSTOP7.bit.IPUVISCK	= 1;
	IO_CHIPTOP.CLKSTOP7.bit.IPUAX		= 1;
	IO_CHIPTOP.CLKSTOP7.bit.IPUAH		= 1;
	IO_CHIPTOP.CLKSTOP7.bit.RAWCK		= 1;
	IO_CHIPTOP.CLKSTOP7.bit.RAWAX		= 1;
	IO_CHIPTOP.CLKSTOP7.bit.RAWAP		= 1;
	IO_CHIPTOP.CLKSTOP7.bit.SHDRCK		= 1;
	IO_CHIPTOP.CLKSTOP7.bit.SHDRAX		= 1;
	IO_CHIPTOP.CLKSTOP7.bit.SHDRAH		= 1;
	IO_CHIPTOP.CLKSTOP7.bit.SHDRAP		= 1;
	IO_CHIPTOP.CLKSTOP7.bit.M0CK		= 1;
	IO_CHIPTOP.CLKSTOP7.bit.MECK		= 1;
	IO_CHIPTOP.CLKSTOP7.bit.MEAX		= 1;
	IO_CHIPTOP.CLKSTOP7.bit.MEAP		= 1;
#endif

	Ddim_Print(("CLKSTOP7_IPUFDCK	= %d\n", DdToptwo_GET_CLKSTOP7_IPUFDCK()));
	Ddim_Print(("CLKSTOP7_IPUVISCK	= %d\n", DdToptwo_GET_CLKSTOP7_IPUVISCK()));
	Ddim_Print(("CLKSTOP7_IPUAX		= %d\n", DdToptwo_GET_CLKSTOP7_IPUAX()));
	Ddim_Print(("CLKSTOP7_IPUAH		= %d\n", DdToptwo_GET_CLKSTOP7_IPUAH()));
	Ddim_Print(("CLKSTOP7_RAWCK		= %d\n", DdToptwo_GET_CLKSTOP7_RAWCK()));
	Ddim_Print(("CLKSTOP7_RAWAX		= %d\n", DdToptwo_GET_CLKSTOP7_RAWAX()));
	Ddim_Print(("CLKSTOP7_RAWAP		= %d\n", DdToptwo_GET_CLKSTOP7_RAWAP()));
	Ddim_Print(("CLKSTOP7_SHDRCK	= %d\n", DdToptwo_GET_CLKSTOP7_SHDRCK()));
	Ddim_Print(("CLKSTOP7_SHDRAX	= %d\n", DdToptwo_GET_CLKSTOP7_SHDRAX()));
	Ddim_Print(("CLKSTOP7_SHDRAH	= %d\n", DdToptwo_GET_CLKSTOP7_SHDRAH()));
	Ddim_Print(("CLKSTOP7_SHDRAP	= %d\n", DdToptwo_GET_CLKSTOP7_SHDRAP()));
	Ddim_Print(("CLKSTOP7_M0CK		= %d\n", DdToptwo_GET_CLKSTOP7_M0CK()));
	Ddim_Print(("CLKSTOP7_MECK		= %d\n", DdToptwo_GET_CLKSTOP7_MECK()));
	Ddim_Print(("CLKSTOP7_MEAX		= %d\n", DdToptwo_GET_CLKSTOP7_MEAX()));
	Ddim_Print(("CLKSTOP7_MEAP		= %d\n", DdToptwo_GET_CLKSTOP7_MEAP()));
	Ddim_Print(("CLKSTOP7 = %08lX\n", DdToptwo_GET_CLKSTOP7()));
}

static void ctGetClockClkstop8(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.CLKSTOP8.bit.RIBCK		= 1;
	IO_CHIPTOP.CLKSTOP8.bit.RIBAH		= 1;
	IO_CHIPTOP.CLKSTOP8.bit.HEVDFCK		= 1;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	IO_CHIPTOP.CLKSTOP8.bit.HEPXFCK		= 1;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	IO_CHIPTOP.CLKSTOP8.bit.HEVENCCK	= 1;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	IO_CHIPTOP.CLKSTOP8.bit.HEIPPCK		= 1;
	IO_CHIPTOP.CLKSTOP8.bit.UMC0HEVCMX2	= 1;
	IO_CHIPTOP.CLKSTOP8.bit.UMC0HEVCMX4	= 1;
	IO_CHIPTOP.CLKSTOP8.bit.UMC0RBRMX4	= 1;
	IO_CHIPTOP.CLKSTOP8.bit.UMC1HEVCMX2	= 1;
	IO_CHIPTOP.CLKSTOP8.bit.UMC1HEVCMX4	= 1;
	IO_CHIPTOP.CLKSTOP8.bit.UMC1RBRMX4	= 1;
	IO_CHIPTOP.CLKSTOP8.bit.UMC0CMNAX	= 1;
	IO_CHIPTOP.CLKSTOP8.bit.UMC0MX1AX	= 1;
	IO_CHIPTOP.CLKSTOP8.bit.UMC0MX2AX	= 1;
	IO_CHIPTOP.CLKSTOP8.bit.UMC0MX3AX	= 1;
	IO_CHIPTOP.CLKSTOP8.bit.UMC0MX4AX	= 1;
#endif

	Ddim_Print(("CLKSTOP8_RIBCK			= %d\n", DdToptwo_GET_CLKSTOP8_RIBCK()));
	Ddim_Print(("CLKSTOP8_RIBAH			= %d\n", DdToptwo_GET_CLKSTOP8_RIBAH()));
	Ddim_Print(("CLKSTOP8_HEVDFCK		= %d\n", DdToptwo_GET_CLKSTOP8_HEVDFCK()));
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	Ddim_Print(("CLKSTOP8_HEPXFCK		= %d\n", DdToptwo_GET_CLKSTOP8_HEPXFCK()));
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	Ddim_Print(("CLKSTOP8_HEVENCCK		= %d\n", DdToptwo_GET_CLKSTOP8_HEVENCCK()));
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	Ddim_Print(("CLKSTOP8_HEIPPCK		= %d\n", DdToptwo_GET_CLKSTOP8_HEIPPCK()));
	Ddim_Print(("CLKSTOP8_UMC0HEVCMX2	= %d\n", DdToptwo_GET_CLKSTOP8_UMC0HEVCMX2()));
	Ddim_Print(("CLKSTOP8_UMC0HEVCMX4	= %d\n", DdToptwo_GET_CLKSTOP8_UMC0HEVCMX4()));
	Ddim_Print(("CLKSTOP8_UMC0RBRMX4	= %d\n", DdToptwo_GET_CLKSTOP8_UMC0RBRMX4()));
	Ddim_Print(("CLKSTOP8_UMC1HEVCMX2	= %d\n", DdToptwo_GET_CLKSTOP8_UMC1HEVCMX2()));
	Ddim_Print(("CLKSTOP8_UMC1HEVCMX4	= %d\n", DdToptwo_GET_CLKSTOP8_UMC1HEVCMX4()));
	Ddim_Print(("CLKSTOP8_UMC1RBRMX4	= %d\n", DdToptwo_GET_CLKSTOP8_UMC1RBRMX4()));
	Ddim_Print(("CLKSTOP8_UMC0CMNAX		= %d\n", DdToptwo_GET_CLKSTOP8_UMC0CMNAX()));
	Ddim_Print(("CLKSTOP8_UMC0MX1AX		= %d\n", DdToptwo_GET_CLKSTOP8_UMC0MX1AX()));
	Ddim_Print(("CLKSTOP8_UMC0MX2AX		= %d\n", DdToptwo_GET_CLKSTOP8_UMC0MX2AX()));
	Ddim_Print(("CLKSTOP8_UMC0MX3AX		= %d\n", DdToptwo_GET_CLKSTOP8_UMC0MX3AX()));
	Ddim_Print(("CLKSTOP8_UMC0MX4AX		= %d\n", DdToptwo_GET_CLKSTOP8_UMC0MX4AX()));
	Ddim_Print(("CLKSTOP8 = %08lX\n", DdToptwo_GET_CLKSTOP8()));
}

static void ctGetClockClkstop9(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.CLKSTOP9.bit.UMC0MX5AX	= 1;
	IO_CHIPTOP.CLKSTOP9.bit.UMC1CMNAX	= 1;
	IO_CHIPTOP.CLKSTOP9.bit.UMC1MX1AX	= 1;
	IO_CHIPTOP.CLKSTOP9.bit.UMC1MX2AX	= 1;
	IO_CHIPTOP.CLKSTOP9.bit.UMC1MX3AX	= 1;
	IO_CHIPTOP.CLKSTOP9.bit.UMC1MX4AX	= 1;
	IO_CHIPTOP.CLKSTOP9.bit.UMC1MX5AX	= 1;
	IO_CHIPTOP.CLKSTOP9.bit.UMC0MX0AX3	= 1;
	IO_CHIPTOP.CLKSTOP9.bit.UMC0MX6AX4	= 1;
	IO_CHIPTOP.CLKSTOP9.bit.UMC0HEVCAX4	= 1;
	IO_CHIPTOP.CLKSTOP9.bit.UMC1MX0AX3	= 1;
	IO_CHIPTOP.CLKSTOP9.bit.UMC1MX6AX4	= 1;
	IO_CHIPTOP.CLKSTOP9.bit.UMC1HEVCAX4	= 1;
	IO_CHIPTOP.CLKSTOP9.bit.UMC0AP		= 1;
	IO_CHIPTOP.CLKSTOP9.bit.UMC1AP		= 1;
#endif

	Ddim_Print(("CLKSTOP9_UMC0MX5AX		= %d\n", DdToptwo_GET_CLKSTOP9_UMC0MX5AX()));
	Ddim_Print(("CLKSTOP9_UMC1CMNAX		= %d\n", DdToptwo_GET_CLKSTOP9_UMC1CMNAX()));
	Ddim_Print(("CLKSTOP9_UMC1MX1AX		= %d\n", DdToptwo_GET_CLKSTOP9_UMC1MX1AX()));
	Ddim_Print(("CLKSTOP9_UMC1MX2AX		= %d\n", DdToptwo_GET_CLKSTOP9_UMC1MX2AX()));
	Ddim_Print(("CLKSTOP9_UMC1MX3AX		= %d\n", DdToptwo_GET_CLKSTOP9_UMC1MX3AX()));
	Ddim_Print(("CLKSTOP9_UMC1MX4AX		= %d\n", DdToptwo_GET_CLKSTOP9_UMC1MX4AX()));
	Ddim_Print(("CLKSTOP9_UMC1MX5AX		= %d\n", DdToptwo_GET_CLKSTOP9_UMC1MX5AX()));
	Ddim_Print(("CLKSTOP9_UMC0MX0AX3	= %d\n", DdToptwo_GET_CLKSTOP9_UMC0MX0AX3()));
	Ddim_Print(("CLKSTOP9_UMC0MX6AX4	= %d\n", DdToptwo_GET_CLKSTOP9_UMC0MX6AX4()));
	Ddim_Print(("CLKSTOP9_UMC0HEVCAX4	= %d\n", DdToptwo_GET_CLKSTOP9_UMC0HEVCAX4()));
	Ddim_Print(("CLKSTOP9_UMC1MX0AX3	= %d\n", DdToptwo_GET_CLKSTOP9_UMC1MX0AX3()));
	Ddim_Print(("CLKSTOP9_UMC1MX6AX4	= %d\n", DdToptwo_GET_CLKSTOP9_UMC1MX6AX4()));
	Ddim_Print(("CLKSTOP9_UMC1HEVCAX4	= %d\n", DdToptwo_GET_CLKSTOP9_UMC1HEVCAX4()));
	Ddim_Print(("CLKSTOP9_UMC0AP		= %d\n", DdToptwo_GET_CLKSTOP9_UMC0AP()));
	Ddim_Print(("CLKSTOP9_UMC1AP		= %d\n", DdToptwo_GET_CLKSTOP9_UMC1AP()));
	Ddim_Print(("CLKSTOP9 = %08lX\n", DdToptwo_GET_CLKSTOP9()));
}

static void ctGetClockClkstop10(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.CLKSTOP10.bit.SRO1CK		= 1;
	IO_CHIPTOP.CLKSTOP10.bit.SRO1CK_2	= 1;
	IO_CHIPTOP.CLKSTOP10.bit.SRO1AX		= 1;
	IO_CHIPTOP.CLKSTOP10.bit.SRO1AH		= 1;
	IO_CHIPTOP.CLKSTOP10.bit.SRO1AP		= 1;
	IO_CHIPTOP.CLKSTOP10.bit.B2B1CK		= 1;
	IO_CHIPTOP.CLKSTOP10.bit.B2B1AX		= 1;
	IO_CHIPTOP.CLKSTOP10.bit.B2B1AH		= 1;
	IO_CHIPTOP.CLKSTOP10.bit.B2B1AP		= 1;
	IO_CHIPTOP.CLKSTOP10.bit.LTMRBK1CK	= 1;
	IO_CHIPTOP.CLKSTOP10.bit.B2R1CK		= 1;
	IO_CHIPTOP.CLKSTOP10.bit.B2R1AX		= 1;
	IO_CHIPTOP.CLKSTOP10.bit.B2R1AH		= 1;
	IO_CHIPTOP.CLKSTOP10.bit.B2R1AP		= 1;
#endif

	Ddim_Print(("CLKSTOP10_SRO1CK		= %d\n", DdToptwo_GET_CLKSTOP10_SRO1CK()));
	Ddim_Print(("CLKSTOP10_SRO1CK_2		= %d\n", DdToptwo_GET_CLKSTOP10_SRO1CK_2()));
	Ddim_Print(("CLKSTOP10_SRO1AX		= %d\n", DdToptwo_GET_CLKSTOP10_SRO1AX()));
	Ddim_Print(("CLKSTOP10_SRO1AH		= %d\n", DdToptwo_GET_CLKSTOP10_SRO1AH()));
	Ddim_Print(("CLKSTOP10_SRO1AP		= %d\n", DdToptwo_GET_CLKSTOP10_SRO1AP()));
	Ddim_Print(("CLKSTOP10_B2B1CK		= %d\n", DdToptwo_GET_CLKSTOP10_B2B1CK()));
	Ddim_Print(("CLKSTOP10_B2B1AX		= %d\n", DdToptwo_GET_CLKSTOP10_B2B1AX()));
	Ddim_Print(("CLKSTOP10_B2B1AH		= %d\n", DdToptwo_GET_CLKSTOP10_B2B1AH()));
	Ddim_Print(("CLKSTOP10_B2B1AP		= %d\n", DdToptwo_GET_CLKSTOP10_B2B1AP()));
	Ddim_Print(("CLKSTOP10_LTMRBK1CK	= %d\n", DdToptwo_GET_CLKSTOP10_LTMRBK1CK()));
	Ddim_Print(("CLKSTOP10_B2R1CK		= %d\n", DdToptwo_GET_CLKSTOP10_B2R1CK()));
	Ddim_Print(("CLKSTOP10_B2R1AX		= %d\n", DdToptwo_GET_CLKSTOP10_B2R1AX()));
	Ddim_Print(("CLKSTOP10_B2R1AH		= %d\n", DdToptwo_GET_CLKSTOP10_B2R1AH()));
	Ddim_Print(("CLKSTOP10_B2R1AP		= %d\n", DdToptwo_GET_CLKSTOP10_B2R1AP()));
	Ddim_Print(("CLKSTOP10 = %08lX\n", DdToptwo_GET_CLKSTOP10()));
}

static void ctSetClockClkstop7(kint argc, kchar** argv)
{
	kulong val;

	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "IPUFDCK" ) ) {
			DdToptwo_SET_CLKSTOP7_IPUFDCK(val);
			Ddim_Print(("It set CLKSTOP7_IPUFDCK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP7.bit.IPUFDCK	= %d\n", IO_CHIPTOP.CLKSTOP7.bit.IPUFDCK));
		}else if (  0 == strcmp( argv[4], "IPUVISCK" ) ) {
			DdToptwo_SET_CLKSTOP7_IPUVISCK(val);
			Ddim_Print(("It set CLKSTOP7_IPUVISCK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP7.bit.IPUVISCK	= %d\n", IO_CHIPTOP.CLKSTOP7.bit.IPUVISCK));
		}else if (  0 == strcmp( argv[4], "IPUAX" ) ) {
			DdToptwo_SET_CLKSTOP7_IPUAX(val);
			Ddim_Print(("It set CLKSTOP7_IPUAX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP7.bit.IPUAX	= %d\n", IO_CHIPTOP.CLKSTOP7.bit.IPUAX));
		}else if (  0 == strcmp( argv[4], "IPUAH" ) ) {
			DdToptwo_SET_CLKSTOP7_IPUAH(val);
			Ddim_Print(("It set CLKSTOP7_IPUAH Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP7.bit.IPUAH	= %d\n", IO_CHIPTOP.CLKSTOP7.bit.IPUAH));
		}else if (  0 == strcmp( argv[4], "RAWCK" ) ) {
			DdToptwo_SET_CLKSTOP7_RAWCK(val);
			Ddim_Print(("It set CLKSTOP7_RAWCK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP7.bit.RAWCK	= %d\n", IO_CHIPTOP.CLKSTOP7.bit.RAWCK));
		}else if (  0 == strcmp( argv[4], "RAWAX" ) ) {
			DdToptwo_SET_CLKSTOP7_RAWAX(val);
			Ddim_Print(("It set CLKSTOP7_RAWAX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP7.bit.RAWAX	= %d\n", IO_CHIPTOP.CLKSTOP7.bit.RAWAX));
		}else if (  0 == strcmp( argv[4], "RAWAP" ) ) {
			DdToptwo_SET_CLKSTOP7_RAWAP(val);
			Ddim_Print(("It set CLKSTOP7_RAWAP Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP7.bit.RAWAP	= %d\n", IO_CHIPTOP.CLKSTOP7.bit.RAWAP));
		}else if (  0 == strcmp( argv[4], "SHDRCK" ) ) {
			DdToptwo_SET_CLKSTOP7_SHDRCK(val);
			Ddim_Print(("It set CLKSTOP7_SHDRCK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP7.bit.SHDRCK	= %d\n", IO_CHIPTOP.CLKSTOP7.bit.SHDRCK));
		}else if (  0 == strcmp( argv[4], "SHDRAX" ) ) {
			DdToptwo_SET_CLKSTOP7_SHDRAX(val);
			Ddim_Print(("It set CLKSTOP7_SHDRAX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP7.bit.SHDRAX	= %d\n", IO_CHIPTOP.CLKSTOP7.bit.SHDRAX));
		}else if (  0 == strcmp( argv[4], "SHDRAH" ) ) {
			DdToptwo_SET_CLKSTOP7_SHDRAH(val);
			Ddim_Print(("It set CLKSTOP7_SHDRAH Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP7.bit.SHDRAH	= %d\n", IO_CHIPTOP.CLKSTOP7.bit.SHDRAH));
		}else if (  0 == strcmp( argv[4], "SHDRAP" ) ) {
			DdToptwo_SET_CLKSTOP7_SHDRAP(val);
			Ddim_Print(("It set CLKSTOP7_SHDRAP Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP7.bit.SHDRAP	= %d\n", IO_CHIPTOP.CLKSTOP7.bit.SHDRAP));
		}else if (  0 == strcmp( argv[4], "M0CK" ) ) {
			DdToptwo_SET_CLKSTOP7_M0CK(val);
			Ddim_Print(("It set CLKSTOP7_M0CK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP7.bit.M0CK	= %d\n", IO_CHIPTOP.CLKSTOP7.bit.M0CK));
		}else if (  0 == strcmp( argv[4], "MECK" ) ) {
			DdToptwo_SET_CLKSTOP7_MECK(val);
			Ddim_Print(("It set CLKSTOP7_MECK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP7.bit.MECK	= %d\n", IO_CHIPTOP.CLKSTOP7.bit.MECK));
		}else if (  0 == strcmp( argv[4], "MEAX" ) ) {
			DdToptwo_SET_CLKSTOP7_MEAX(val);
			Ddim_Print(("It set CLKSTOP7_MEAX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP7.bit.MEAX	= %d\n", IO_CHIPTOP.CLKSTOP7.bit.MEAX));
		}else if (  0 == strcmp( argv[4], "MEAP" ) ) {
			DdToptwo_SET_CLKSTOP7_MEAP(val);
			Ddim_Print(("It set CLKSTOP7_MEAP Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP7.bit.MEAP	= %d\n", IO_CHIPTOP.CLKSTOP7.bit.MEAP));
		}
		else {
			Ddim_Print(("please check 4th parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void ctSetClockClkstop8(kint argc, kchar** argv)
{
	kulong val;

	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "RIBCK" ) ) {
			DdToptwo_SET_CLKSTOP8_RIBCK(val);
			Ddim_Print(("It set CLKSTOP8_RIBCK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP8.bit.RIBCK	= %d\n", IO_CHIPTOP.CLKSTOP8.bit.RIBCK));
		}else if (  0 == strcmp( argv[4], "RIBAH" ) ) {
			DdToptwo_SET_CLKSTOP8_RIBAH(val);
			Ddim_Print(("It set CLKSTOP8_RIBAH Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP8.bit.RIBAH	= %d\n", IO_CHIPTOP.CLKSTOP8.bit.RIBAH));
		}else if (  0 == strcmp( argv[4], "HEVDFCK" ) ) {
			DdToptwo_SET_CLKSTOP8_HEVDFCK(val);
			Ddim_Print(("It set CLKSTOP8_HEVDFCK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP8.bit.HEVDFCK	= %d\n", IO_CHIPTOP.CLKSTOP8.bit.HEVDFCK));
		}
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
		else if ( 0 == strcmp( argv[4], "HEPXFCK" ) ) {
			DdToptwo_SET_CLKSTOP8_HEPXFCK(val);
			Ddim_Print(("It set CLKSTOP8_HEPXFCK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP8.bit.HEPXFCK	= %d\n", IO_CHIPTOP.CLKSTOP8.bit.HEPXFCK));
		}
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
		else if ( 0 == strcmp( argv[4], "HEVENCCK" ) ) {
			DdToptwo_SET_CLKSTOP8_HEVENCCK(val);
			Ddim_Print(("It set CLKSTOP8_HEVENCCK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP8.bit.HEVENCCK	= %d\n", IO_CHIPTOP.CLKSTOP8.bit.HEVENCCK));
		}
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
		else if ( 0 == strcmp( argv[4], "HEIPPCK" ) ) {
			DdToptwo_SET_CLKSTOP8_HEIPPCK(val);
			Ddim_Print(("It set CLKSTOP8_HEIPPCK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP8.bit.HEIPPCK	= %d\n", IO_CHIPTOP.CLKSTOP8.bit.HEIPPCK));
		}else if (  0 == strcmp( argv[4], "UMC0HEVCMX2" ) ) {
			DdToptwo_SET_CLKSTOP8_UMC0HEVCMX2(val);
			Ddim_Print(("It set CLKSTOP8_UMC0HEVCMX2 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP8.bit.UMC0HEVCMX2	= %d\n", IO_CHIPTOP.CLKSTOP8.bit.UMC0HEVCMX2));
		}else if (  0 == strcmp( argv[4], "UMC0HEVCMX4" ) ) {
			DdToptwo_SET_CLKSTOP8_UMC0HEVCMX4(val);
			Ddim_Print(("It set CLKSTOP8_UMC0HEVCMX4 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP8.bit.UMC0HEVCMX4	= %d\n", IO_CHIPTOP.CLKSTOP8.bit.UMC0HEVCMX4));
		}else if (  0 == strcmp( argv[4], "UMC0RBRMX4" ) ) {
			DdToptwo_SET_CLKSTOP8_UMC0RBRMX4(val);
			Ddim_Print(("It set CLKSTOP8_UMC0RBRMX4 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP8.bit.UMC0RBRMX4	= %d\n", IO_CHIPTOP.CLKSTOP8.bit.UMC0RBRMX4));
		}else if (  0 == strcmp( argv[4], "UMC1HEVCMX2" ) ) {
			DdToptwo_SET_CLKSTOP8_UMC1HEVCMX2(val);
			Ddim_Print(("It set CLKSTOP8_UMC1HEVCMX2 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP8.bit.UMC1HEVCMX2	= %d\n", IO_CHIPTOP.CLKSTOP8.bit.UMC1HEVCMX2));
		}else if (  0 == strcmp( argv[4], "UMC1HEVCMX4" ) ) {
			DdToptwo_SET_CLKSTOP8_UMC1HEVCMX4(val);
			Ddim_Print(("It set CLKSTOP8_UMC1HEVCMX4 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP8.bit.UMC1HEVCMX4	= %d\n", IO_CHIPTOP.CLKSTOP8.bit.UMC1HEVCMX4));
		}else if (  0 == strcmp( argv[4], "UMC1RBRMX4" ) ) {
			DdToptwo_SET_CLKSTOP8_UMC1RBRMX4(val);
			Ddim_Print(("It set CLKSTOP8_UMC1RBRMX4 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP8.bit.UMC1RBRMX4	= %d\n", IO_CHIPTOP.CLKSTOP8.bit.UMC1RBRMX4));
		}else if (  0 == strcmp( argv[4], "UMC0CMNAX" ) ) {
			DdToptwo_SET_CLKSTOP8_UMC0CMNAX(val);
			Ddim_Print(("It set CLKSTOP8_UMC0CMNAX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP8.bit.UMC0CMNAX	= %d\n", IO_CHIPTOP.CLKSTOP8.bit.UMC0CMNAX));
		}else if (  0 == strcmp( argv[4], "UMC0MX1AX" ) ) {
			DdToptwo_SET_CLKSTOP8_UMC0MX1AX(val);
			Ddim_Print(("It set CLKSTOP8_UMC0MX1AX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP8.bit.UMC0MX1AX	= %d\n", IO_CHIPTOP.CLKSTOP8.bit.UMC0MX1AX));
		}else if (  0 == strcmp( argv[4], "UMC0MX2AX" ) ) {
			DdToptwo_SET_CLKSTOP8_UMC0MX2AX(val);
			Ddim_Print(("It set CLKSTOP8_UMC0MX2AX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP8.bit.UMC0MX2AX	= %d\n", IO_CHIPTOP.CLKSTOP8.bit.UMC0MX2AX));
		}else if (  0 == strcmp( argv[4], "UMC0MX3AX" ) ) {
			DdToptwo_SET_CLKSTOP8_UMC0MX3AX(val);
			Ddim_Print(("It set CLKSTOP8_UMC0MX3AX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP8.bit.UMC0MX3AX	= %d\n", IO_CHIPTOP.CLKSTOP8.bit.UMC0MX3AX));
		}else if (  0 == strcmp( argv[4], "UMC0MX4AX" ) ) {
			DdToptwo_SET_CLKSTOP8_UMC0MX4AX(val);
			Ddim_Print(("It set CLKSTOP8_UMC0MX4AX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP8.bit.UMC0MX4AX	= %d\n", IO_CHIPTOP.CLKSTOP8.bit.UMC0MX4AX));
		}else {
			Ddim_Print(("please check 4th parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void ctSetClockClkstop9(kint argc, kchar** argv)
{
	kulong val;

	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "UMC0MX5AX" ) ) {
			DdToptwo_SET_CLKSTOP9_UMC0MX5AX(val);
			Ddim_Print(("It set CLKSTOP9_UMC0MX5AX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP9.bit.UMC0MX5AX	= %d\n", IO_CHIPTOP.CLKSTOP9.bit.UMC0MX5AX));
		}else if (  0 == strcmp( argv[4], "UMC1CMNAX" ) ) {
			DdToptwo_SET_CLKSTOP9_UMC1CMNAX(val);
			Ddim_Print(("It set CLKSTOP9_UMC1CMNAX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP9.bit.UMC1CMNAX	= %d\n", IO_CHIPTOP.CLKSTOP9.bit.UMC1CMNAX));
		}else if (  0 == strcmp( argv[4], "UMC1MX1AX" ) ) {
			DdToptwo_SET_CLKSTOP9_UMC1MX1AX(val);
			Ddim_Print(("It set CLKSTOP9_UMC1MX1AX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP9.bit.UMC1MX1AX	= %d\n", IO_CHIPTOP.CLKSTOP9.bit.UMC1MX1AX));
		}else if (  0 == strcmp( argv[4], "UMC1MX2AX" ) ) {
			DdToptwo_SET_CLKSTOP9_UMC1MX2AX(val);
			Ddim_Print(("It set CLKSTOP9_UMC1MX2AX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP9.bit.UMC1MX2AX	= %d\n", IO_CHIPTOP.CLKSTOP9.bit.UMC1MX2AX));
		}else if (  0 == strcmp( argv[4], "UMC1MX3AX" ) ) {
			DdToptwo_SET_CLKSTOP9_UMC1MX3AX(val);
			Ddim_Print(("It set CLKSTOP9_UMC1MX3AX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP9.bit.UMC1MX3AX	= %d\n", IO_CHIPTOP.CLKSTOP9.bit.UMC1MX3AX));
		}else if (  0 == strcmp( argv[4], "UMC1MX4AX" ) ) {
			DdToptwo_SET_CLKSTOP9_UMC1MX4AX(val);
			Ddim_Print(("It set CLKSTOP9_UMC1MX4AX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP9.bit.UMC1MX4AX	= %d\n", IO_CHIPTOP.CLKSTOP9.bit.UMC1MX4AX));
		}else if (  0 == strcmp( argv[4], "UMC1MX5AX" ) ) {
			DdToptwo_SET_CLKSTOP9_UMC1MX5AX(val);
			Ddim_Print(("It set CLKSTOP9_UMC1MX5AX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP9.bit.UMC1MX5AX	= %d\n", IO_CHIPTOP.CLKSTOP9.bit.UMC1MX5AX));
		}else if (  0 == strcmp( argv[4], "UMC0MX0AX3" ) ) {
			DdToptwo_SET_CLKSTOP9_UMC0MX0AX3(val);
			Ddim_Print(("It set CLKSTOP9_UMC0MX0AX3 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP9.bit.UMC0MX0AX3	= %d\n", IO_CHIPTOP.CLKSTOP9.bit.UMC0MX0AX3));
		}else if (  0 == strcmp( argv[4], "UMC0MX6AX4" ) ) {
			DdToptwo_SET_CLKSTOP9_UMC0MX6AX4(val);
			Ddim_Print(("It set CLKSTOP9_UMC0MX6AX4 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP9.bit.UMC0MX6AX4	= %d\n", IO_CHIPTOP.CLKSTOP9.bit.UMC0MX6AX4));
		}else if (  0 == strcmp( argv[4], "UMC0HEVCAX4" ) ) {
			DdToptwo_SET_CLKSTOP9_UMC0HEVCAX4(val);
			Ddim_Print(("It set CLKSTOP9_UMC0HEVCAX4 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP9.bit.UMC0HEVCAX4	= %d\n", IO_CHIPTOP.CLKSTOP9.bit.UMC0HEVCAX4));
		}else if (  0 == strcmp( argv[4], "UMC1MX0AX3" ) ) {
			DdToptwo_SET_CLKSTOP9_UMC1MX0AX3(val);
			Ddim_Print(("It set CLKSTOP9_UMC1MX0AX3 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP9.bit.UMC1MX0AX3	= %d\n", IO_CHIPTOP.CLKSTOP9.bit.UMC1MX0AX3));
		}else if (  0 == strcmp( argv[4], "UMC1MX6AX4" ) ) {
			DdToptwo_SET_CLKSTOP9_UMC1MX6AX4(val);
			Ddim_Print(("It set CLKSTOP9_UMC1MX6AX4 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP9.bit.UMC1MX6AX4	= %d\n", IO_CHIPTOP.CLKSTOP9.bit.UMC1MX6AX4));
		}else if (  0 == strcmp( argv[4], "UMC1HEVCAX4" ) ) {
			DdToptwo_SET_CLKSTOP9_UMC1HEVCAX4(val);
			Ddim_Print(("It set CLKSTOP9_UMC1HEVCAX4 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP9.bit.UMC1HEVCAX4	= %d\n", IO_CHIPTOP.CLKSTOP9.bit.UMC1HEVCAX4));
		}else if (  0 == strcmp( argv[4], "UMC0AP" ) ) {
			DdToptwo_SET_CLKSTOP9_UMC0AP(val);
			Ddim_Print(("It set CLKSTOP9_UMC0AP Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP9.bit.UMC0AP	= %d\n", IO_CHIPTOP.CLKSTOP9.bit.UMC0AP));
		}else if (  0 == strcmp( argv[4], "UMC1AP" ) ) {
			DdToptwo_SET_CLKSTOP9_UMC1AP(val);
			Ddim_Print(("It set CLKSTOP9_UMC1AP Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP9.bit.UMC1AP	= %d\n", IO_CHIPTOP.CLKSTOP9.bit.UMC1AP));
		}
		else {
			Ddim_Print(("please check 4th parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void ctSetClockClkstop10(kint argc, kchar** argv)
{
	kulong val;

	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "SRO1CK" ) ) {
			DdToptwo_SET_CLKSTOP10_SRO1CK(val);
			Ddim_Print(("It set CLKSTOP_10SRO1CK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP10.bit.SRO1CK	= %d\n", IO_CHIPTOP.CLKSTOP10.bit.SRO1CK));
		}else if (  0 == strcmp( argv[4], "SRO1CK_2" ) ) {
			DdToptwo_SET_CLKSTOP10_SRO1CK_2(val);
			Ddim_Print(("It set CLKSTOP_10SRO1CK_2 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP10.bit.SRO1CK_2	= %d\n", IO_CHIPTOP.CLKSTOP10.bit.SRO1CK_2));
		}else if (  0 == strcmp( argv[4], "SRO1AX" ) ) {
			DdToptwo_SET_CLKSTOP10_SRO1AX(val);
			Ddim_Print(("It set CLKSTOP_10SRO1AX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP10.bit.SRO1AX	= %d\n", IO_CHIPTOP.CLKSTOP10.bit.SRO1AX));
		}else if (  0 == strcmp( argv[4], "SRO1AH" ) ) {
			DdToptwo_SET_CLKSTOP10_SRO1AH(val);
			Ddim_Print(("It set CLKSTOP_10SRO1AH Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP10.bit.SRO1AH	= %d\n", IO_CHIPTOP.CLKSTOP10.bit.SRO1AH));
		}else if (  0 == strcmp( argv[4], "SRO1AP" ) ) {
			DdToptwo_SET_CLKSTOP10_SRO1AP(val);
			Ddim_Print(("It set CLKSTOP_10SRO1AP Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP10.bit.SRO1AP	= %d\n", IO_CHIPTOP.CLKSTOP10.bit.SRO1AP));
		}else if (  0 == strcmp( argv[4], "B2B1CK" ) ) {
			DdToptwo_SET_CLKSTOP10_B2B1CK(val);
			Ddim_Print(("It set CLKSTOP_10B2B1CK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP10.bit.B2B1CK	= %d\n", IO_CHIPTOP.CLKSTOP10.bit.B2B1CK));
		}else if (  0 == strcmp( argv[4], "B2B1AX" ) ) {
			DdToptwo_SET_CLKSTOP10_B2B1AX(val);
			Ddim_Print(("It set CLKSTOP_10B2B1AX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP10.bit.B2B1AX	= %d\n", IO_CHIPTOP.CLKSTOP10.bit.B2B1AX));
		}else if (  0 == strcmp( argv[4], "B2B1AH" ) ) {
			DdToptwo_SET_CLKSTOP10_B2B1AH(val);
			Ddim_Print(("It set CLKSTOP_10B2B1AH Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP10.bit.B2B1AH	= %d\n", IO_CHIPTOP.CLKSTOP10.bit.B2B1AH));
		}else if (  0 == strcmp( argv[4], "B2B1AP" ) ) {
			DdToptwo_SET_CLKSTOP10_B2B1AP(val);
			Ddim_Print(("It set CLKSTOP_10B2B1AP Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP10.bit.B2B1AP	= %d\n", IO_CHIPTOP.CLKSTOP10.bit.B2B1AP));
		}else if (  0 == strcmp( argv[4], "LTMRBK1CK" ) ) {
			DdToptwo_SET_CLKSTOP10_LTMRBK1CK(val);
			Ddim_Print(("It set CLKSTOP_10LTMRBK1CK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP10.bit.LTMRBK1CK	= %d\n", IO_CHIPTOP.CLKSTOP10.bit.LTMRBK1CK));
		}else if (  0 == strcmp( argv[4], "B2R1CK" ) ) {
			DdToptwo_SET_CLKSTOP10_B2R1CK(val);
			Ddim_Print(("It set CLKSTOP_10B2R1CK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP10.bit.B2R1CK	= %d\n", IO_CHIPTOP.CLKSTOP10.bit.B2R1CK));
		}else if (  0 == strcmp( argv[4], "B2R1AX" ) ) {
			DdToptwo_SET_CLKSTOP10_B2R1AX(val);
			Ddim_Print(("It set CLKSTOP_10B2R1AX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP10.bit.B2R1AX	= %d\n", IO_CHIPTOP.CLKSTOP10.bit.B2R1AX));
		}else if (  0 == strcmp( argv[4], "B2R1AH" ) ) {
			DdToptwo_SET_CLKSTOP10_B2R1AH(val);
			Ddim_Print(("It set CLKSTOP_10B2R1AH Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP10.bit.B2R1AH	= %d\n", IO_CHIPTOP.CLKSTOP10.bit.B2R1AH));
		}else if (  0 == strcmp( argv[4], "B2R1AP" ) ) {
			DdToptwo_SET_CLKSTOP10_B2R1AP(val);
			Ddim_Print(("It set CLKSTOP_10B2R1AP Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP10.bit.B2R1AP	= %d\n", IO_CHIPTOP.CLKSTOP10.bit.B2R1AP));
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
void ct_clock_clkstop_mid_set(CtClockClkstopMid *self)
{
	CtClockClkstopMidPrivate *priv = CT_CLOCK_CLKSTOP_MID_GET_PRIVATE(self);
    if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clkstop7" ) ) {
        ctSetClockClkstop7( ((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv );
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clkstop8" ) ) {
        ctSetClockClkstop8( ((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv );
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clkstop9" ) ) {
        ctSetClockClkstop9( ((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv );
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clkstop10" ) ) {
        ctSetClockClkstop10( ((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv );
    }else {
		ct_dd_parameter_set_parameter((CtDdParameter *)priv->ctClockClkstopEnd,
				((CtDdParameter *)self)->argc,((CtDdParameter *)self)->argv);
		ct_clock_clkstop_end_set(priv->ctClockClkstopEnd);
	}
}

void ct_clock_clkstop_mid_get(CtClockClkstopMid *self)
{
   	CtClockClkstopMidPrivate *priv = CT_CLOCK_CLKSTOP_MID_GET_PRIVATE(self);
     if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clkstop7" ) ) {
        ctGetClockClkstop7();
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clkstop8" ) ) {
        ctGetClockClkstop8();
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clkstop9" ) ) {
        ctGetClockClkstop9();
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clkstop10" ) ) {
        ctGetClockClkstop10();
    }else {
		ct_dd_parameter_set_parameter((CtDdParameter *)priv->ctClockClkstopEnd,
				((CtDdParameter *)self)->argc,((CtDdParameter *)self)->argv);
		ct_clock_clkstop_end_get(priv->ctClockClkstopEnd);
	}
}

CtClockClkstopMid* ct_clock_clkstop_mid_new(void) 
{
    CtClockClkstopMid *self = k_object_new_with_private(CT_TYPE_CLOCK_CLKSTOP_MID, sizeof(CtClockClkstopMidPrivate));
    return self;
}
