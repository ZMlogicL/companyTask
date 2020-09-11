/*
*@Copyright (C) 2020-2020 上海网用软件有限公司
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
#include "ctclockclkstopend.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtClockClkstopEnd, ct_clock_clkstop_end);
#define CT_CLOCK_CLKSTOP_END_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtClockClkstopEndPrivate,CT_TYPE_CLOCK_CLKSTOP_END))

struct _CtClockClkstopEndPrivate
{
	kint a;
};
/****************
* DECLS
*/
static void 			ct_clock_clkstop_end_constructor(CtClockClkstopEnd *self);
static void 			ct_clock_clkstop_end_destructor(CtClockClkstopEnd *self);
static void 			ctGetClockClkstop11(void);
static void 			ctGetClockClkstop12(void);
static void 			ctGetClockClkstop13(void);
static void 			ctGetClockClkstop14(void);
static void 			ctSetClockClkstop11(kint argc, kchar** argv);
static void 			ctSetClockClkstop12(kint argc, kchar** argv);
static void 			ctSetClockClkstop13(kint argc, kchar** argv);
static void 			ctSetClockClkstop14(kint argc, kchar** argv);
/****************
* IMPL
*/
static void ct_clock_clkstop_end_constructor(CtClockClkstopEnd *self) 
{
	// CtClockClkstopEndPrivate *priv = CT_CLOCK_CLKSTOP_END_GET_PRIVATE(self);
}

static void ct_clock_clkstop_end_destructor(CtClockClkstopEnd *self) 
{
	// CtClockClkstopEndPrivate *priv = CT_CLOCK_CLKSTOP_END_GET_PRIVATE(self);
}

static void ctGetClockClkstop11(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.CLKSTOP11.bit.LTM1CK		= 1;
	IO_CHIPTOP.CLKSTOP11.bit.LTM1AX		= 1;
	IO_CHIPTOP.CLKSTOP11.bit.LTM1AH		= 1;
	IO_CHIPTOP.CLKSTOP11.bit.LTM1AP		= 1;
	IO_CHIPTOP.CLKSTOP11.bit.R2Y1CK		= 1;
	IO_CHIPTOP.CLKSTOP11.bit.R2Y1AX		= 1;
	IO_CHIPTOP.CLKSTOP11.bit.R2Y1AH		= 1;
	IO_CHIPTOP.CLKSTOP11.bit.R2Y1AP		= 1;
	IO_CHIPTOP.CLKSTOP11.bit.CNR1CK		= 1;
	IO_CHIPTOP.CLKSTOP11.bit.CNR1AX		= 1;
	IO_CHIPTOP.CLKSTOP11.bit.CNR1AP		= 1;
	IO_CHIPTOP.CLKSTOP11.bit.APAH		= 1;
	IO_CHIPTOP.CLKSTOP11.bit.DBGAP		= 1;
	IO_CHIPTOP.CLKSTOP11.bit.NFBCHCK	= 1;
#endif

	Ddim_Print(("CLKSTOP11_LTM1CK		= %d\n", DdToptwo_GET_CLKSTOP11_LTM1CK()));
	Ddim_Print(("CLKSTOP11_LTM1AX		= %d\n", DdToptwo_GET_CLKSTOP11_LTM1AX()));
	Ddim_Print(("CLKSTOP11_LTM1AH		= %d\n", DdToptwo_GET_CLKSTOP11_LTM1AH()));
	Ddim_Print(("CLKSTOP11_LTM1AP		= %d\n", DdToptwo_GET_CLKSTOP11_LTM1AP()));
	Ddim_Print(("CLKSTOP11_R2Y1CK		= %d\n", DdToptwo_GET_CLKSTOP11_R2Y1CK()));
	Ddim_Print(("CLKSTOP11_R2Y1AX		= %d\n", DdToptwo_GET_CLKSTOP11_R2Y1AX()));
	Ddim_Print(("CLKSTOP11_R2Y1AH		= %d\n", DdToptwo_GET_CLKSTOP11_R2Y1AH()));
	Ddim_Print(("CLKSTOP11_R2Y1AP		= %d\n", DdToptwo_GET_CLKSTOP11_R2Y1AP()));
	Ddim_Print(("CLKSTOP11_CNR1CK		= %d\n", DdToptwo_GET_CLKSTOP11_CNR1CK()));
	Ddim_Print(("CLKSTOP11_CNR1AX		= %d\n", DdToptwo_GET_CLKSTOP11_CNR1AX()));
	Ddim_Print(("CLKSTOP11_CNR1AP		= %d\n", DdToptwo_GET_CLKSTOP11_CNR1AP()));
	Ddim_Print(("CLKSTOP11_APAH			= %d\n", DdToptwo_GET_CLKSTOP11_APAH()));
	Ddim_Print(("CLKSTOP11_DBGAP		= %d\n", DdToptwo_GET_CLKSTOP11_DBGAP()));
	Ddim_Print(("CLKSTOP11_NFBCHCK		= %d\n", DdToptwo_GET_CLKSTOP11_NFBCHCK()));
	Ddim_Print(("CLKSTOP11 = %08lX\n", DdToptwo_GET_CLKSTOP11()));
}

static void ctGetClockClkstop12(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.CLKSTOP12.bit.SRO2CK		= 1;
	IO_CHIPTOP.CLKSTOP12.bit.SRO2CK_2	= 1;
	IO_CHIPTOP.CLKSTOP12.bit.SRO2AX		= 1;
	IO_CHIPTOP.CLKSTOP12.bit.SRO2AH		= 1;
	IO_CHIPTOP.CLKSTOP12.bit.SRO2AP		= 1;
	IO_CHIPTOP.CLKSTOP12.bit.B2B2CK		= 1;
	IO_CHIPTOP.CLKSTOP12.bit.B2B2AX		= 1;
	IO_CHIPTOP.CLKSTOP12.bit.B2B2AH		= 1;
	IO_CHIPTOP.CLKSTOP12.bit.B2B2AP		= 1;
	IO_CHIPTOP.CLKSTOP12.bit.LTMRBK2CK	= 1;
	IO_CHIPTOP.CLKSTOP12.bit.B2R2CK		= 1;
	IO_CHIPTOP.CLKSTOP12.bit.B2R2AX		= 1;
	IO_CHIPTOP.CLKSTOP12.bit.B2R2AH		= 1;
	IO_CHIPTOP.CLKSTOP12.bit.B2R2AP		= 1;
#endif

	Ddim_Print(("CLKSTOP12_SRO2CK		= %d\n", DdToptwo_GET_CLKSTOP12_SRO2CK()));
	Ddim_Print(("CLKSTOP12_SRO2CK_2		= %d\n", DdToptwo_GET_CLKSTOP12_SRO2CK_2()));
	Ddim_Print(("CLKSTOP12_SRO2AX		= %d\n", DdToptwo_GET_CLKSTOP12_SRO2AX()));
	Ddim_Print(("CLKSTOP12_SRO2AH		= %d\n", DdToptwo_GET_CLKSTOP12_SRO2AH()));
	Ddim_Print(("CLKSTOP12_SRO2AP		= %d\n", DdToptwo_GET_CLKSTOP12_SRO2AP()));
	Ddim_Print(("CLKSTOP12_B2B2CK		= %d\n", DdToptwo_GET_CLKSTOP12_B2B2CK()));
	Ddim_Print(("CLKSTOP12_B2B2AX		= %d\n", DdToptwo_GET_CLKSTOP12_B2B2AX()));
	Ddim_Print(("CLKSTOP12_B2B2AH		= %d\n", DdToptwo_GET_CLKSTOP12_B2B2AH()));
	Ddim_Print(("CLKSTOP12_B2B2AP		= %d\n", DdToptwo_GET_CLKSTOP12_B2B2AP()));
	Ddim_Print(("CLKSTOP12_LTMRBK2CK	= %d\n", DdToptwo_GET_CLKSTOP12_LTMRBK2CK()));
	Ddim_Print(("CLKSTOP12_B2R2CK		= %d\n", DdToptwo_GET_CLKSTOP12_B2R2CK()));
	Ddim_Print(("CLKSTOP12_B2R2AX		= %d\n", DdToptwo_GET_CLKSTOP12_B2R2AX()));
	Ddim_Print(("CLKSTOP12_B2R2AH		= %d\n", DdToptwo_GET_CLKSTOP12_B2R2AH()));
	Ddim_Print(("CLKSTOP12_B2R2AP		= %d\n", DdToptwo_GET_CLKSTOP12_B2R2AP()));
	Ddim_Print(("CLKSTOP12 = %08lX\n", DdToptwo_GET_CLKSTOP12()));
}

static void ctGetClockClkstop13(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.CLKSTOP13.bit.LTM2CK		= 1;
	IO_CHIPTOP.CLKSTOP13.bit.LTM2AX		= 1;
	IO_CHIPTOP.CLKSTOP13.bit.LTM2AH		= 1;
	IO_CHIPTOP.CLKSTOP13.bit.LTM2AP		= 1;
	IO_CHIPTOP.CLKSTOP13.bit.R2Y2CK		= 1;
	IO_CHIPTOP.CLKSTOP13.bit.R2Y2AX		= 1;
	IO_CHIPTOP.CLKSTOP13.bit.R2Y2AH		= 1;
	IO_CHIPTOP.CLKSTOP13.bit.R2Y2AP		= 1;
	IO_CHIPTOP.CLKSTOP13.bit.CNR2CK		= 1;
	IO_CHIPTOP.CLKSTOP13.bit.CNR2AX		= 1;
	IO_CHIPTOP.CLKSTOP13.bit.CNR2AP		= 1;
	IO_CHIPTOP.CLKSTOP13.bit.UMCVDFMX4	= 1;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	IO_CHIPTOP.CLKSTOP13.bit.UMCPXFMX4	= 1;
	IO_CHIPTOP.CLKSTOP13.bit.UMCVDFMX2	= 1;
	IO_CHIPTOP.CLKSTOP13.bit.UMCPXFMX2	= 1;// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	IO_CHIPTOP.CLKSTOP13.bit.UMCHEVENCAX4	= 1;
	IO_CHIPTOP.CLKSTOP13.bit.UMCVDFMX2	= 1;
	IO_CHIPTOP.CLKSTOP13.bit.HEVENCAP	= 1;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	IO_CHIPTOP.CLKSTOP13.bit.BMH1CK		= 1;
#endif

	Ddim_Print(("CLKSTOP13_LTM2CK		= %d\n", DdToptwo_GET_CLKSTOP13_LTM2CK()));
	Ddim_Print(("CLKSTOP13_LTM2AX		= %d\n", DdToptwo_GET_CLKSTOP13_LTM2AX()));
	Ddim_Print(("CLKSTOP13_LTM2AH		= %d\n", DdToptwo_GET_CLKSTOP13_LTM2AH()));
	Ddim_Print(("CLKSTOP13_LTM2AP		= %d\n", DdToptwo_GET_CLKSTOP13_LTM2AP()));
	Ddim_Print(("CLKSTOP13_R2Y2CK		= %d\n", DdToptwo_GET_CLKSTOP13_R2Y2CK()));
	Ddim_Print(("CLKSTOP13_R2Y2AX		= %d\n", DdToptwo_GET_CLKSTOP13_R2Y2AX()));
	Ddim_Print(("CLKSTOP13_R2Y2AH		= %d\n", DdToptwo_GET_CLKSTOP13_R2Y2AH()));
	Ddim_Print(("CLKSTOP13_R2Y2AP		= %d\n", DdToptwo_GET_CLKSTOP13_R2Y2AP()));
	Ddim_Print(("CLKSTOP13_CNR2CK		= %d\n", DdToptwo_GET_CLKSTOP13_CNR2CK()));
	Ddim_Print(("CLKSTOP13_CNR2AX		= %d\n", DdToptwo_GET_CLKSTOP13_CNR2AX()));
	Ddim_Print(("CLKSTOP13_CNR2AP		= %d\n", DdToptwo_GET_CLKSTOP13_CNR2AP()));
	Ddim_Print(("CLKSTOP13_UMCVDFMX4	= %d\n", DdToptwo_GET_CLKSTOP13_UMCVDFMX4()));
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	Ddim_Print(("CLKSTOP13_UMCPXFMX4	= %d\n", DdToptwo_GET_CLKSTOP13_UMCPXFMX4()));
	Ddim_Print(("CLKSTOP13_UMCVDFMX2	= %d\n", DdToptwo_GET_CLKSTOP13_UMCVDFMX2()));
	Ddim_Print(("CLKSTOP13_UMCPXFMX2	= %d\n", DdToptwo_GET_CLKSTOP13_UMCPXFMX2()));
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	Ddim_Print(("CLKSTOP13_UMCHEVENCAX4	= %d\n", DdToptwo_GET_CLKSTOP13_UMCHEVENCAX4()));
	Ddim_Print(("CLKSTOP13_UMCVDFMX2	= %d\n", DdToptwo_GET_CLKSTOP13_UMCVDFMX2()));
	Ddim_Print(("CLKSTOP13_HEVENCAP		= %d\n", DdToptwo_GET_CLKSTOP13_HEVENCAP()));
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	Ddim_Print(("CLKSTOP13_BMH1CK		= %d\n", DdToptwo_GET_CLKSTOP13_BMH1CK()));
	Ddim_Print(("CLKSTOP13 = %08lX\n", DdToptwo_GET_CLKSTOP13()));
}

static void ctGetClockClkstop14(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.CLKSTOP14.bit.STATAX		= 1;
	IO_CHIPTOP.CLKSTOP14.bit.STATAH		= 1;
	IO_CHIPTOP.CLKSTOP14.bit.STATAP		= 1;
	IO_CHIPTOP.CLKSTOP14.bit.PERIAH		= 1;
	IO_CHIPTOP.CLKSTOP14.bit.PERIAP		= 1;
	IO_CHIPTOP.CLKSTOP14.bit.SENMSKCK	= 1;
	IO_CHIPTOP.CLKSTOP14.bit.GYROCK		= 1;
	IO_CHIPTOP.CLKSTOP14.bit.EXSAH		= 1;
	IO_CHIPTOP.CLKSTOP14.bit.EXSAP		= 1;
	IO_CHIPTOP.CLKSTOP14.bit.PASCK		= 1;
	IO_CHIPTOP.CLKSTOP14.bit.BMH0CK		= 1;
	IO_CHIPTOP.CLKSTOP14.bit.BMH0AX		= 1;
	IO_CHIPTOP.CLKSTOP14.bit.RDMAAX		= 1;
	IO_CHIPTOP.CLKSTOP14.bit.RDMAAP		= 1;
	IO_CHIPTOP.CLKSTOP14.bit.BMH1AX		= 1;
#endif

	Ddim_Print(("CLKSTOP14_STATAX		= %d\n", DdToptwo_GET_CLKSTOP14_STATAX()));
	Ddim_Print(("CLKSTOP14_STATAH		= %d\n", DdToptwo_GET_CLKSTOP14_STATAH()));
	Ddim_Print(("CLKSTOP14_STATAP		= %d\n", DdToptwo_GET_CLKSTOP14_STATAP()));
	Ddim_Print(("CLKSTOP14_PERIAH		= %d\n", DdToptwo_GET_CLKSTOP14_PERIAH()));
	Ddim_Print(("CLKSTOP14_PERIAP		= %d\n", DdToptwo_GET_CLKSTOP14_PERIAP()));
	Ddim_Print(("CLKSTOP14_SENMSKCK		= %d\n", DdToptwo_GET_CLKSTOP14_SENMSKCK()));
	Ddim_Print(("CLKSTOP14_GYROCK		= %d\n", DdToptwo_GET_CLKSTOP14_GYROCK()));
	Ddim_Print(("CLKSTOP14_EXSAH		= %d\n", DdToptwo_GET_CLKSTOP14_EXSAH()));
	Ddim_Print(("CLKSTOP14_EXSAP		= %d\n", DdToptwo_GET_CLKSTOP14_EXSAP()));
	Ddim_Print(("CLKSTOP14_PASCK		= %d\n", DdToptwo_GET_CLKSTOP14_PASCK()));
	Ddim_Print(("CLKSTOP14_BMH0CK		= %d\n", DdToptwo_GET_CLKSTOP14_BMH0CK()));
	Ddim_Print(("CLKSTOP14_BMH0AX		= %d\n", DdToptwo_GET_CLKSTOP14_BMH0AX()));
	Ddim_Print(("CLKSTOP14_RDMAAX		= %d\n", DdToptwo_GET_CLKSTOP14_RDMAAX()));
	Ddim_Print(("CLKSTOP14_RDMAAP		= %d\n", DdToptwo_GET_CLKSTOP14_RDMAAP()));
	Ddim_Print(("CLKSTOP14_BMH1AX		= %d\n", DdToptwo_GET_CLKSTOP14_BMH1AX()));
	Ddim_Print(("CLKSTOP14 = %08lX\n", DdToptwo_GET_CLKSTOP14()));
}

static void ctSetClockClkstop11(kint argc, kchar** argv)
{
	kulong val;

	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "LTM1CK" ) ) {
			DdToptwo_SET_CLKSTOP11_LTM1CK(val);
			Ddim_Print(("It set CLKSTOP_11LTM1CK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP11.bit.LTM1CK	= %d\n", IO_CHIPTOP.CLKSTOP11.bit.LTM1CK));
		}else if (  0 == strcmp( argv[4], "LTM1AX" ) ) {
			DdToptwo_SET_CLKSTOP11_LTM1AX(val);
			Ddim_Print(("It set CLKSTOP_11LTM1AX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP11.bit.LTM1AX	= %d\n", IO_CHIPTOP.CLKSTOP11.bit.LTM1AX));
		}else if (  0 == strcmp( argv[4], "LTM1AH" ) ) {
			DdToptwo_SET_CLKSTOP11_LTM1AH(val);
			Ddim_Print(("It set CLKSTOP_11LTM1AH Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP11.bit.LTM1AH	= %d\n", IO_CHIPTOP.CLKSTOP11.bit.LTM1AH));
		}else if (  0 == strcmp( argv[4], "LTM1AP" ) ) {
			DdToptwo_SET_CLKSTOP11_LTM1AP(val);
			Ddim_Print(("It set CLKSTOP_11LTM1AP Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP11.bit.LTM1AP	= %d\n", IO_CHIPTOP.CLKSTOP11.bit.LTM1AP));
		}else if (  0 == strcmp( argv[4], "R2Y1CK" ) ) {
			DdToptwo_SET_CLKSTOP11_R2Y1CK(val);
			Ddim_Print(("It set CLKSTOP_11R2Y1CK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP11.bit.R2Y1CK	= %d\n", IO_CHIPTOP.CLKSTOP11.bit.R2Y1CK));
		}else if (  0 == strcmp( argv[4], "R2Y1AX" ) ) {
			DdToptwo_SET_CLKSTOP11_R2Y1AX(val);
			Ddim_Print(("It set CLKSTOP_11R2Y1AX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP11.bit.R2Y1AX	= %d\n", IO_CHIPTOP.CLKSTOP11.bit.R2Y1AX));
		}else if (  0 == strcmp( argv[4], "R2Y1AH" ) ) {
			DdToptwo_SET_CLKSTOP11_R2Y1AH(val);
			Ddim_Print(("It set CLKSTOP_11R2Y1AH Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP11.bit.R2Y1AH	= %d\n", IO_CHIPTOP.CLKSTOP11.bit.R2Y1AH));
		}else if (  0 == strcmp( argv[4], "R2Y1AP" ) ) {
			DdToptwo_SET_CLKSTOP11_R2Y1AP(val);
			Ddim_Print(("It set CLKSTOP_11R2Y1AP Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP11.bit.R2Y1AP	= %d\n", IO_CHIPTOP.CLKSTOP11.bit.R2Y1AP));
		}else if (  0 == strcmp( argv[4], "CNR1CK" ) ) {
			DdToptwo_SET_CLKSTOP11_CNR1CK(val);
			Ddim_Print(("It set CLKSTOP_11CNR1CK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP11.bit.CNR1CK	= %d\n", IO_CHIPTOP.CLKSTOP11.bit.CNR1CK));
		}else if (  0 == strcmp( argv[4], "CNR1AX" ) ) {
			DdToptwo_SET_CLKSTOP11_CNR1AX(val);
			Ddim_Print(("It set CLKSTOP_11CNR1AX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP11.bit.CNR1AX	= %d\n", IO_CHIPTOP.CLKSTOP11.bit.CNR1AX));
		}else if (  0 == strcmp( argv[4], "CNR1AP" ) ) {
			DdToptwo_SET_CLKSTOP11_CNR1AP(val);
			Ddim_Print(("It set CLKSTOP_11CNR1AP Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP11.bit.CNR1AP	= %d\n", IO_CHIPTOP.CLKSTOP11.bit.CNR1AP));
		}else if (  0 == strcmp( argv[4], "APAH" ) ) {
			DdToptwo_SET_CLKSTOP11_APAH(val);
			Ddim_Print(("It set CLKSTOP_APAH Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP11.bit.APAH	= %d\n", IO_CHIPTOP.CLKSTOP11.bit.APAH));
		}else if (  0 == strcmp( argv[4], "DBGAP" ) ) {
			DdToptwo_SET_CLKSTOP11_DBGAP(val);
			Ddim_Print(("It set CLKSTOP_DBGAP Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP11.bit.DBGAP	= %d\n", IO_CHIPTOP.CLKSTOP11.bit.DBGAP));
		}else if (  0 == strcmp( argv[4], "NFBCHCK" ) ) {
			DdToptwo_SET_CLKSTOP11_NFBCHCK(val);
			Ddim_Print(("It set CLKSTOP_NFBCHCK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP11.bit.NFBCHCK	= %d\n", IO_CHIPTOP.CLKSTOP11.bit.NFBCHCK));
		}
		else {
			Ddim_Print(("please check 4th parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void ctSetClockClkstop12(kint argc, kchar** argv)
{
	kulong val;

	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "SRO2CK" ) ) {
			DdToptwo_SET_CLKSTOP12_SRO2CK(val);
			Ddim_Print(("It set CLKSTOP_12SRO2CK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP12.bit.SRO2CK	= %d\n", IO_CHIPTOP.CLKSTOP12.bit.SRO2CK));
		}else if (  0 == strcmp( argv[4], "SRO2CK_2" ) ) {
			DdToptwo_SET_CLKSTOP12_SRO2CK_2(val);
			Ddim_Print(("It set CLKSTOP_12SRO2CK_2 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP12.bit.SRO2CK_2	= %d\n", IO_CHIPTOP.CLKSTOP12.bit.SRO2CK_2));
		}else if (  0 == strcmp( argv[4], "SRO2AX" ) ) {
			DdToptwo_SET_CLKSTOP12_SRO2AX(val);
			Ddim_Print(("It set CLKSTOP_12SRO2AX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP12.bit.SRO2AX	= %d\n", IO_CHIPTOP.CLKSTOP12.bit.SRO2AX));
		}else if (  0 == strcmp( argv[4], "SRO2AH" ) ) {
			DdToptwo_SET_CLKSTOP12_SRO2AH(val);
			Ddim_Print(("It set CLKSTOP_12SRO2AH Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP12.bit.SRO2AH	= %d\n", IO_CHIPTOP.CLKSTOP12.bit.SRO2AH));
		}else if (  0 == strcmp( argv[4], "SRO2AP" ) ) {
			DdToptwo_SET_CLKSTOP12_SRO2AP(val);
			Ddim_Print(("It set CLKSTOP_12SRO2AP Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP12.bit.SRO2AP	= %d\n", IO_CHIPTOP.CLKSTOP12.bit.SRO2AP));
		}else if (  0 == strcmp( argv[4], "B2B2CK" ) ) {
			DdToptwo_SET_CLKSTOP12_B2B2CK(val);
			Ddim_Print(("It set CLKSTOP_12B2B2CK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP12.bit.B2B2CK	= %d\n", IO_CHIPTOP.CLKSTOP12.bit.B2B2CK));
		}else if (  0 == strcmp( argv[4], "B2B2AX" ) ) {
			DdToptwo_SET_CLKSTOP12_B2B2AX(val);
			Ddim_Print(("It set CLKSTOP_12B2B2AX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP12.bit.B2B2AX	= %d\n", IO_CHIPTOP.CLKSTOP12.bit.B2B2AX));
		}else if (  0 == strcmp( argv[4], "B2B2AH" ) ) {
			DdToptwo_SET_CLKSTOP12_B2B2AH(val);
			Ddim_Print(("It set CLKSTOP_12B2B2AH Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP12.bit.B2B2AH	= %d\n", IO_CHIPTOP.CLKSTOP12.bit.B2B2AH));
		}else if (  0 == strcmp( argv[4], "B2B2AP" ) ) {
			DdToptwo_SET_CLKSTOP12_B2B2AP(val);
			Ddim_Print(("It set CLKSTOP_12B2B2AP Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP12.bit.B2B2AP	= %d\n", IO_CHIPTOP.CLKSTOP12.bit.B2B2AP));
		}else if (  0 == strcmp( argv[4], "LTMRBK2CK" ) ) {
			DdToptwo_SET_CLKSTOP12_LTMRBK2CK(val);
			Ddim_Print(("It set CLKSTOP_12LTMRBK2CK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP12.bit.LTMRBK2CK	= %d\n", IO_CHIPTOP.CLKSTOP12.bit.LTMRBK2CK));
		}else if (  0 == strcmp( argv[4], "B2R2CK" ) ) {
			DdToptwo_SET_CLKSTOP12_B2R2CK(val);
			Ddim_Print(("It set CLKSTOP_12B2R2CK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP12.bit.B2R2CK	= %d\n", IO_CHIPTOP.CLKSTOP12.bit.B2R2CK));
		}else if (  0 == strcmp( argv[4], "B2R2AX" ) ) {
			DdToptwo_SET_CLKSTOP12_B2R2AX(val);
			Ddim_Print(("It set CLKSTOP_12B2R2AX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP12.bit.B2R2AX	= %d\n", IO_CHIPTOP.CLKSTOP12.bit.B2R2AX));
		}else if (  0 == strcmp( argv[4], "B2R2AH" ) ) {
			DdToptwo_SET_CLKSTOP12_B2R2AH(val);
			Ddim_Print(("It set CLKSTOP_12B2R2AH Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP12.bit.B2R2AH	= %d\n", IO_CHIPTOP.CLKSTOP12.bit.B2R2AH));
		}else if (  0 == strcmp( argv[4], "B2R2AP" ) ) {
			DdToptwo_SET_CLKSTOP12_B2R2AP(val);
			Ddim_Print(("It set CLKSTOP_12B2R2AP Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP12.bit.B2R2AP	= %d\n", IO_CHIPTOP.CLKSTOP12.bit.B2R2AP));
		}
		else {
			Ddim_Print(("please check 4th parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void ctSetClockClkstop13(kint argc, kchar** argv)
{
	kulong val;

	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "LTM2CK" ) ) {
			DdToptwo_SET_CLKSTOP13_LTM2CK(val);
			Ddim_Print(("It set CLKSTOP_13LTM2CK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP13.bit.LTM2CK	= %d\n", IO_CHIPTOP.CLKSTOP13.bit.LTM2CK));
		}else if (  0 == strcmp( argv[4], "LTM2AX" ) ) {
			DdToptwo_SET_CLKSTOP13_LTM2AX(val);
			Ddim_Print(("It set CLKSTOP_13LTM2AX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP13.bit.LTM2AX	= %d\n", IO_CHIPTOP.CLKSTOP13.bit.LTM2AX));
		}else if (  0 == strcmp( argv[4], "LTM2AH" ) ) {
			DdToptwo_SET_CLKSTOP13_LTM2AH(val);
			Ddim_Print(("It set CLKSTOP_13LTM2AH Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP13.bit.LTM2AH	= %d\n", IO_CHIPTOP.CLKSTOP13.bit.LTM2AH));
		}else if (  0 == strcmp( argv[4], "LTM2AP" ) ) {
			DdToptwo_SET_CLKSTOP13_LTM2AP(val);
			Ddim_Print(("It set CLKSTOP_13LTM2AP Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP13.bit.LTM2AP	= %d\n", IO_CHIPTOP.CLKSTOP13.bit.LTM2AP));
		}else if (  0 == strcmp( argv[4], "R2Y2CK" ) ) {
			DdToptwo_SET_CLKSTOP13_R2Y2CK(val);
			Ddim_Print(("It set CLKSTOP_13R2Y2CK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP13.bit.R2Y2CK	= %d\n", IO_CHIPTOP.CLKSTOP13.bit.R2Y2CK));
		}else if (  0 == strcmp( argv[4], "R2Y2AX" ) ) {
			DdToptwo_SET_CLKSTOP13_R2Y2AX(val);
			Ddim_Print(("It set CLKSTOP_13R2Y2AX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP13.bit.R2Y2AX	= %d\n", IO_CHIPTOP.CLKSTOP13.bit.R2Y2AX));
		}else if (  0 == strcmp( argv[4], "R2Y2AH" ) ) {
			DdToptwo_SET_CLKSTOP13_R2Y2AH(val);
			Ddim_Print(("It set CLKSTOP_13R2Y2AH Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP13.bit.R2Y2AH	= %d\n", IO_CHIPTOP.CLKSTOP13.bit.R2Y2AH));
		}else if (  0 == strcmp( argv[4], "R2Y2AP" ) ) {
			DdToptwo_SET_CLKSTOP13_R2Y2AP(val);
			Ddim_Print(("It set CLKSTOP_13R2Y2AP Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP13.bit.R2Y2AP	= %d\n", IO_CHIPTOP.CLKSTOP13.bit.R2Y2AP));
		}else if (  0 == strcmp( argv[4], "CNR2CK" ) ) {
			DdToptwo_SET_CLKSTOP13_CNR2CK(val);
			Ddim_Print(("It set CLKSTOP_13CNR2CK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP13.bit.CNR2CK	= %d\n", IO_CHIPTOP.CLKSTOP13.bit.CNR2CK));
		}else if (  0 == strcmp( argv[4], "CNR2AX" ) ) {
			DdToptwo_SET_CLKSTOP13_CNR2AX(val);
			Ddim_Print(("It set CLKSTOP_13CNR2AX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP13.bit.CNR2AX	= %d\n", IO_CHIPTOP.CLKSTOP13.bit.CNR2AX));
		}else if (  0 == strcmp( argv[4], "CNR2AP" ) ) {
			DdToptwo_SET_CLKSTOP13_CNR2AP(val);
			Ddim_Print(("It set CLKSTOP_13CNR2AP Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP13.bit.CNR2AP	= %d\n", IO_CHIPTOP.CLKSTOP13.bit.CNR2AP));
		}else if (  0 == strcmp( argv[4], "UMCVDFMX4" ) ) {
			DdToptwo_SET_CLKSTOP13_UMCVDFMX4(val);
			Ddim_Print(("It set CLKSTOP_UMCVDFMX4 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP13.bit.UMCVDFMX4	= %d\n", IO_CHIPTOP.CLKSTOP13.bit.UMCVDFMX4));
		}
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
		else if ( 0 == strcmp( argv[4], "UMCPXFMX4" ) ) {
			DdToptwo_SET_CLKSTOP13_UMCPXFMX4(val);
			Ddim_Print(("It set CLKSTOP_UMCPXFMX4 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP13.bit.UMCPXFMX4	= %d\n", IO_CHIPTOP.CLKSTOP13.bit.UMCPXFMX4));
		}
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
		else if ( 0 == strcmp( argv[4], "UMCHEVENCAX4" ) ) {
			DdToptwo_SET_CLKSTOP13_UMCHEVENCAX4(val);
			Ddim_Print(("It set CLKSTOP_UMCHEVENCAX4 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP13.bit.UMCHEVENCAX4	= %d\n", IO_CHIPTOP.CLKSTOP13.bit.UMCHEVENCAX4));
		}
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
		else if ( 0 == strcmp( argv[4], "UMCVDFMX2" ) ) {
			DdToptwo_SET_CLKSTOP13_UMCVDFMX2(val);
			Ddim_Print(("It set CLKSTOP_UMCVDFMX2 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP13.bit.UMCVDFMX2	= %d\n", IO_CHIPTOP.CLKSTOP13.bit.UMCVDFMX2));
		}
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
		else if ( 0 == strcmp( argv[4], "UMCPXFMX2" ) ) {
			DdToptwo_SET_CLKSTOP13_UMCPXFMX2(val);
			Ddim_Print(("It set CLKSTOP_UMCPXFMX2 Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP13.bit.UMCPXFMX2	= %d\n", IO_CHIPTOP.CLKSTOP13.bit.UMCPXFMX2));
		}
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
		else if ( 0 == strcmp( argv[4], "HEVENCAP" ) ) {
			DdToptwo_SET_CLKSTOP13_HEVENCAP(val);
			Ddim_Print(("It set CLKSTOP_HEVENCAP Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP13.bit.HEVENCAP	= %d\n", IO_CHIPTOP.CLKSTOP13.bit.HEVENCAP));
		}
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
		else if ( 0 == strcmp( argv[4], "BMH1CK" ) ) {
			DdToptwo_SET_CLKSTOP13_BMH1CK(val);
			Ddim_Print(("It set CLKSTOP_BMH1CK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP13.bit.BMH1CK	= %d\n", IO_CHIPTOP.CLKSTOP13.bit.BMH1CK));
		}
		else {
			Ddim_Print(("please check 4th parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void ctSetClockClkstop14(kint argc, kchar** argv)
{
	kulong val;

	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "STATAX" ) ) {
			DdToptwo_SET_CLKSTOP14_STATAX(val);
			Ddim_Print(("It set CLKSTOP_14STATAX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP14.bit.STATAX	= %d\n", IO_CHIPTOP.CLKSTOP14.bit.STATAX));
		}else if (  0 == strcmp( argv[4], "STATAH" ) ) {
			DdToptwo_SET_CLKSTOP14_STATAH(val);
			Ddim_Print(("It set CLKSTOP_14STATAH Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP14.bit.STATAH	= %d\n", IO_CHIPTOP.CLKSTOP14.bit.STATAH));
		}else if (  0 == strcmp( argv[4], "STATAP" ) ) {
			DdToptwo_SET_CLKSTOP14_STATAP(val);
			Ddim_Print(("It set CLKSTOP_14STATAP Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP14.bit.STATAP	= %d\n", IO_CHIPTOP.CLKSTOP14.bit.STATAP));
		}else if (  0 == strcmp( argv[4], "PERIAH" ) ) {
			DdToptwo_SET_CLKSTOP14_PERIAH(val);
			Ddim_Print(("It set CLKSTOP_14PERIAH Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP14.bit.PERIAH	= %d\n", IO_CHIPTOP.CLKSTOP14.bit.PERIAH));
		}else if (  0 == strcmp( argv[4], "PERIAP" ) ) {
			DdToptwo_SET_CLKSTOP14_PERIAP(val);
			Ddim_Print(("It set CLKSTOP_14PERIAP Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP14.bit.PERIAP	= %d\n", IO_CHIPTOP.CLKSTOP14.bit.PERIAP));
		}else if (  0 == strcmp( argv[4], "SENMSKCK" ) ) {
			DdToptwo_SET_CLKSTOP14_SENMSKCK(val);
			Ddim_Print(("It set CLKSTOP_14SENMSKCK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP14.bit.SENMSKCK	= %d\n", IO_CHIPTOP.CLKSTOP14.bit.SENMSKCK));
		}else if (  0 == strcmp( argv[4], "GYROCK" ) ) {
			DdToptwo_SET_CLKSTOP14_GYROCK(val);
			Ddim_Print(("It set CLKSTOP_14GYROCK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP14.bit.GYROCK	= %d\n", IO_CHIPTOP.CLKSTOP14.bit.GYROCK));
		}else if (  0 == strcmp( argv[4], "EXSAH" ) ) {
			DdToptwo_SET_CLKSTOP14_EXSAH(val);
			Ddim_Print(("It set CLKSTOP_EXSAH Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP14.bit.EXSAH	= %d\n", IO_CHIPTOP.CLKSTOP14.bit.EXSAH));
		}else if (  0 == strcmp( argv[4], "EXSAP" ) ) {
			DdToptwo_SET_CLKSTOP14_EXSAP(val);
			Ddim_Print(("It set CLKSTOP_EXSAP Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP14.bit.EXSAP	= %d\n", IO_CHIPTOP.CLKSTOP14.bit.EXSAP));
		}else if (  0 == strcmp( argv[4], "PASCK" ) ) {
			DdToptwo_SET_CLKSTOP14_PASCK(val);
			Ddim_Print(("It set CLKSTOP_PASCK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP14.bit.PASCK	= %d\n", IO_CHIPTOP.CLKSTOP14.bit.PASCK));
		}else if (  0 == strcmp( argv[4], "BMH0CK" ) ) {
			DdToptwo_SET_CLKSTOP14_BMH0CK(val);
			Ddim_Print(("It set CLKSTOP_BMH0CK Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP14.bit.BMH0CK	= %d\n", IO_CHIPTOP.CLKSTOP14.bit.BMH0CK));
		}else if (  0 == strcmp( argv[4], "BMH0AX" ) ) {
			DdToptwo_SET_CLKSTOP14_BMH0AX(val);
			Ddim_Print(("It set CLKSTOP_BMH0AX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP14.bit.BMH0AX	= %d\n", IO_CHIPTOP.CLKSTOP14.bit.BMH0AX));
		}else if (  0 == strcmp( argv[4], "RDMAAX" ) ) {
			DdToptwo_SET_CLKSTOP14_RDMAAX(val);
			Ddim_Print(("It set CLKSTOP_RDMAAX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP14.bit.RDMAAX	= %d\n", IO_CHIPTOP.CLKSTOP14.bit.RDMAAX));
		}else if (  0 == strcmp( argv[4], "RDMAAP" ) ) {
			DdToptwo_SET_CLKSTOP14_RDMAAP(val);
			Ddim_Print(("It set CLKSTOP_RDMAAP Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP14.bit.RDMAAP	= %d\n", IO_CHIPTOP.CLKSTOP14.bit.RDMAAP));
		}else if (  0 == strcmp( argv[4], "BMH1AX" ) ) {
			DdToptwo_SET_CLKSTOP14_BMH1AX(val);
			Ddim_Print(("It set CLKSTOP_BMH1AX Clock State.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP14.bit.BMH1AX	= %d\n", IO_CHIPTOP.CLKSTOP14.bit.BMH1AX));
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
void ct_clock_clkstop_end_set(CtClockClkstopEnd *self)
{
    if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clkstop11" ) ) {
        ctSetClockClkstop11( ((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv );
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clkstop12" ) ) {
        ctSetClockClkstop12( ((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv );
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clkstop13" ) ) {
        ctSetClockClkstop13( ((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv );
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clkstop14" ) ) {
        ctSetClockClkstop14( ((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv );
    }else {
		Ddim_Print(("please check 3rd parameter!!\n"));
	}
}

void ct_clock_clkstop_end_get(CtClockClkstopEnd *self)
{    	
    if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clkstop11" ) ) {
        ctGetClockClkstop11();
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clkstop12" ) ) {
        ctGetClockClkstop12();
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clkstop13" ) ) {
        ctGetClockClkstop13();
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clkstop14" ) ) {
        ctGetClockClkstop14();
    }else {
		Ddim_Print(("please check 3rd parameter!!\n"));
	}
	
}

CtClockClkstopEnd* ct_clock_clkstop_end_new(void) 
{
    CtClockClkstopEnd *self = k_object_new_with_private(CT_TYPE_CLOCK_CLKSTOP_END, sizeof(CtClockClkstopEndPrivate));
    return self;
}