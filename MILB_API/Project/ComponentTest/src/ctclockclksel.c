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

#include "ctclockclksel.h"
#include"ctclockpllcnt.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtClockClksel, ct_clock_clksel);
#define CT_CLOCK_CLKSEL_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtClockClkselPrivate,CT_TYPE_CLOCK_CLKSEL))

struct _CtClockClkselPrivate
{
	CtClockPllcnt *ctClockPllcnt;
};
/****************
* DECLS
*/
static void 			ct_clock_clksel_constructor(CtClockClksel *self);
static void 			ct_clock_clksel_destructor(CtClockClksel *self);
static void 			ctGetClockClksel1(void);
static void 			ctGetClockClksel2(void);
static void 			ctGetClockClksel3(void);
static void 			ctGetClockClksel4(void);
static void 			ctGetClockClksel5(void);
static void 			ctGetClockClksel6(void);
static void 			ctGetClockClksel7(void);
static void 			ctGetClockClksel8(void);
static void 			ctGetClockClksel9(void);
static void 			ctGetClockClksel10(void);
static void 			ctGetClockClksel11(void);
static void 			ctGetClockClksel12(void);
static void 			ctSetClockClksel1(kint argc, kchar** argv);
static void 			ctSetClockClksel2(kint argc, kchar** argv);
static void 			ctSetClockClksel3(kint argc, kchar** argv);
static void 			ctSetClockClksel4(kint argc, kchar** argv);
static void 			ctSetClockClksel5(kint argc, kchar** argv);
static void 			ctSetClockClksel6(kint argc, kchar** argv);
static void 			ctSetClockClksel7(kint argc, kchar** argv);
static void 			ctSetClockClksel8(kint argc, kchar** argv);
static void 			ctSetClockClksel9(kint argc, kchar** argv);
static void 			ctSetClockClksel10(kint argc, kchar** argv);
static void 			ctSetClockClksel11(kint argc, kchar** argv);
static void 			ctSetClockClksel12(kint argc, kchar** argv);
/****************
* IMPL
*/
static void ct_clock_clksel_constructor(CtClockClksel *self) 
{
	CtClockClkselPrivate *priv = CT_CLOCK_CLKSEL_GET_PRIVATE(self);
	priv->ctClockPllcnt = ct_clock_pllcnt_new();
}

static void ct_clock_clksel_destructor(CtClockClksel *self) 
{
	CtClockClkselPrivate *priv = CT_CLOCK_CLKSEL_GET_PRIVATE(self);
	k_object_unref(priv->ctClockPllcnt);
}

static void ctGetClockClksel1(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.CLKSEL1.bit.RCLK     = 1;
	IO_CHIPTOP.CLKSEL1.bit.UHS1CLK0 = 1;
	IO_CHIPTOP.CLKSEL1.bit.UHS1CLK1 = 1;
	IO_CHIPTOP.CLKSEL1.bit.UHS1CLK2 = 1;
	IO_CHIPTOP.CLKSEL1.bit.UHS2CLK  = 1;
	IO_CHIPTOP.CLKSEL1.bit.NFCLK    = 1;
	IO_CHIPTOP.CLKSEL1.bit.EMMCCLK  = 1;
#endif
	Ddim_Print(("CLKSEL1_RCLK     = %d\n", DdTopone_GET_CLKSEL1_RCLK()));
	Ddim_Print(("CLKSEL1_UHS1CLK0 = %d\n", DdTopone_GET_CLKSEL1_UHS1CLK0()));
	Ddim_Print(("CLKSEL1_UHS1CLK1 = %d\n", DdTopone_GET_CLKSEL1_UHS1CLK1()));
	Ddim_Print(("CLKSEL1_UHS1CLK2 = %d\n", DdTopone_GET_CLKSEL1_UHS1CLK2()));
	Ddim_Print(("CLKSEL1_UHS2CLK  = %d\n", DdTopone_GET_CLKSEL1_UHS2CLK()));
	Ddim_Print(("CLKSEL1_NFCLK    = %d\n", DdTopone_GET_CLKSEL1_NFCLK()));
	Ddim_Print(("CLKSEL1_EMMCCLK  = %d\n", DdTopone_GET_CLKSEL1_EMMCCLK()));

	Ddim_Print(("CLKSEL1 = %08lX\n", DdTopone_GET_CLKSEL1()));
}

static void ctGetClockClksel2(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.CLKSEL2.bit.ELACLK		= 1;
	IO_CHIPTOP.CLKSEL2.bit.JPGCLK		= 1;
	IO_CHIPTOP.CLKSEL2.bit.GPUCLK		= 1;
	IO_CHIPTOP.CLKSEL2.bit.IPUTMECLK	= 1;
	IO_CHIPTOP.CLKSEL2.bit.IPUCLK		= 1;
	IO_CHIPTOP.CLKSEL2.bit.MIFCLK		= 1;
	IO_CHIPTOP.CLKSEL2.bit.HIFCLK		= 1;
	IO_CHIPTOP.CLKSEL2.bit.RAWCLK		= 1;
#endif
	Ddim_Print(("CLKSEL2_ELACLK    = %d\n", DdTopone_GET_CLKSEL2_ELACLK()));
	Ddim_Print(("CLKSEL2_JPGCLK    = %d\n", DdTopone_GET_CLKSEL2_JPGCLK()));
	Ddim_Print(("CLKSEL2_GPUCLK    = %d\n", DdTopone_GET_CLKSEL2_GPUCLK()));
	Ddim_Print(("CLKSEL2_IPUTMECLK = %d\n", DdTopone_GET_CLKSEL2_IPUTMECLK()));
	Ddim_Print(("CLKSEL2_IPUCLK	   = %d\n", DdTopone_GET_CLKSEL2_IPUCLK()));
	Ddim_Print(("CLKSEL2_MIFCLK    = %d\n", DdTopone_GET_CLKSEL2_MIFCLK()));
	Ddim_Print(("CLKSEL2_HIFCLK    = %d\n", DdTopone_GET_CLKSEL2_HIFCLK()));
	Ddim_Print(("CLKSEL2_RAWCLK    = %d\n", DdTopone_GET_CLKSEL2_RAWCLK()));

	Ddim_Print(("CLKSEL2 = %08lX\n", DdTopone_GET_CLKSEL2()));
}

static void ctGetClockClksel3(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.CLKSEL3.bit.VDFCLK		= 1;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	IO_CHIPTOP.CLKSEL3.bit.PXFCLK		= 1;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	IO_CHIPTOP.CLKSEL3.bit.HEVENCCLK	= 1;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	IO_CHIPTOP.CLKSEL3.bit.IPPCLK		= 1;
	IO_CHIPTOP.CLKSEL3.bit.PASCLK		= 1;
	IO_CHIPTOP.CLKSEL3.bit.IIPCLK		= 1;
	IO_CHIPTOP.CLKSEL3.bit.SENMSKCLK	= 1;
	IO_CHIPTOP.CLKSEL3.bit.SENCLK		= 1;
	IO_CHIPTOP.CLKSEL3.bit.PIPESEL		= 1;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	IO_CHIPTOP.CLKSEL3.bit.HEVENCSEL	= 1;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
#endif
	Ddim_Print(("CLKSEL3_VDFCLK		= %d\n", DdTopone_GET_CLKSEL3_VDFCLK()));
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	Ddim_Print(("CLKSEL3_PXFCLK		= %d\n", DdTopone_GET_CLKSEL3_PXFCLK()));
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	Ddim_Print(("CLKSEL3_HEVENCCLK	= %d\n", DdTopone_GET_CLKSEL3_HEVENCCLK()));
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	Ddim_Print(("CLKSEL3_IPPCLK		= %d\n", DdTopone_GET_CLKSEL3_IPPCLK()));
	Ddim_Print(("CLKSEL3_PASCLK		= %d\n", DdTopone_GET_CLKSEL3_PASCLK()));
	Ddim_Print(("CLKSEL3_IIPCLK		= %d\n", DdTopone_GET_CLKSEL3_IIPCLK()));
	Ddim_Print(("CLKSEL3_SENMSKCLK	= %d\n", DdTopone_GET_CLKSEL3_SENMSKCLK()));
	Ddim_Print(("CLKSEL3_SENCLK		= %d\n", DdTopone_GET_CLKSEL3_SENCLK()));
	Ddim_Print(("CLKSEL3_PIPESEL	= %d\n", DdTopone_GET_CLKSEL3_PIPESEL()));
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	Ddim_Print(("CLKSEL3_HEVENCSEL	= %d\n", DdTopone_GET_CLKSEL3_HEVENCSEL()));
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

	Ddim_Print(("CLKSEL3 = %08lX\n", DdTopone_GET_CLKSEL3()));
}

static void ctGetClockClksel4(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.CLKSEL4.bit.CNR1CLK		= 1;
	IO_CHIPTOP.CLKSEL4.bit.B2R1CLK		= 1;
	IO_CHIPTOP.CLKSEL4.bit.LTM1CLK		= 1;
	IO_CHIPTOP.CLKSEL4.bit.R2Y1CLK		= 1;
	IO_CHIPTOP.CLKSEL4.bit.SRO1CLK_2	= 1;
#endif
	Ddim_Print(("CLKSEL4_CNR1CLK	= %d\n", DdTopone_GET_CLKSEL4_CNR1CLK()));
	Ddim_Print(("CLKSEL4_B2R1CLK	= %d\n", DdTopone_GET_CLKSEL4_B2R1CLK()));
	Ddim_Print(("CLKSEL4_LTM1CLK	= %d\n", DdTopone_GET_CLKSEL4_LTM1CLK()));
	Ddim_Print(("CLKSEL4_R2Y1CLK	= %d\n", DdTopone_GET_CLKSEL4_R2Y1CLK()));
	Ddim_Print(("CLKSEL4_SRO1CLK_2	= %d\n", DdTopone_GET_CLKSEL4_SRO1CLK_2()));

	Ddim_Print(("CLKSEL4 = %08lX\n", DdTopone_GET_CLKSEL4()));
}

static void ctGetClockClksel5(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.CLKSEL5.bit.LTMRBK1CLK	= 1;
	IO_CHIPTOP.CLKSEL5.bit.B2B1CLK		= 1;
	IO_CHIPTOP.CLKSEL5.bit.SRO1CLK		= 1;
#endif
	Ddim_Print(("CLKSEL5_LTMRBK1CLK	= %d\n", DdTopone_GET_CLKSEL5_LTMRBK1CLK()));
	Ddim_Print(("CLKSEL5_B2B1CLK	= %d\n", DdTopone_GET_CLKSEL5_B2B1CLK()));
	Ddim_Print(("CLKSEL5_SRO1CLK	= %d\n", DdTopone_GET_CLKSEL5_SRO1CLK()));

	Ddim_Print(("CLKSEL5 = %08lX\n", DdTopone_GET_CLKSEL5()));
}

static void ctGetClockClksel6(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.CLKSEL6.bit.CNR2CLK		= 1;
	IO_CHIPTOP.CLKSEL6.bit.B2R2CLK		= 1;
	IO_CHIPTOP.CLKSEL6.bit.LTM2CLK		= 1;
	IO_CHIPTOP.CLKSEL6.bit.R2Y2CLK		= 1;
	IO_CHIPTOP.CLKSEL6.bit.SRO2CLK_2	= 1;
#endif
	Ddim_Print(("CLKSEL6_CNR2CLK	= %d\n", DdTopone_GET_CLKSEL6_CNR2CLK()));
	Ddim_Print(("CLKSEL6_B2R2CLK	= %d\n", DdTopone_GET_CLKSEL6_B2R2CLK()));
	Ddim_Print(("CLKSEL6_LTM2CLK	= %d\n", DdTopone_GET_CLKSEL6_LTM2CLK()));
	Ddim_Print(("CLKSEL6_R2Y2CLK	= %d\n", DdTopone_GET_CLKSEL6_R2Y2CLK()));
	Ddim_Print(("CLKSEL6_SRO2CLK_2	= %d\n", DdTopone_GET_CLKSEL6_SRO2CLK_2()));

	Ddim_Print(("CLKSEL6 = %08lX\n", DdTopone_GET_CLKSEL6()));
}

static void ctGetClockClksel7(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.CLKSEL7.bit.LTMRBK2CLK	= 1;
	IO_CHIPTOP.CLKSEL7.bit.B2B2CLK		= 1;
	IO_CHIPTOP.CLKSEL7.bit.SRO2CLK		= 1;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	IO_CHIPTOP.CLKSEL7.bit.MIPISEL		= 1;
	IO_CHIPTOP.CLKSEL7.bit.PDM0SEL		= 1;
	IO_CHIPTOP.CLKSEL7.bit.PDM1SEL		= 1;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
#endif
	Ddim_Print(("CLKSEL7_LTMRBK2CLK	= %d\n", DdTopone_GET_CLKSEL7_LTMRBK2CLK()));
	Ddim_Print(("CLKSEL7_B2B2CLK	= %d\n", DdTopone_GET_CLKSEL7_B2B2CLK()));
	Ddim_Print(("CLKSEL7_SRO2CLK	= %d\n", DdTopone_GET_CLKSEL7_SRO2CLK()));
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	Ddim_Print(("CLKSEL7_MIPISEL	= %d\n", DdTopone_GET_CLKSEL7_MIPISEL()));
	Ddim_Print(("CLKSEL7_PDM0SEL	= %d\n", DdTopone_GET_CLKSEL7_PDM0SEL()));
	Ddim_Print(("CLKSEL7_PDM1SEL	= %d\n", DdTopone_GET_CLKSEL7_PDM1SEL()));
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

	Ddim_Print(("CLKSEL7 = %08lX\n", DdTopone_GET_CLKSEL7()));
}

static void ctGetClockClksel8(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.CLKSEL8.bit.DSPCLK	= 1;
	IO_CHIPTOP.CLKSEL8.bit.SPICLK	= 1;
	IO_CHIPTOP.CLKSEL8.bit.AUCLK	= 1;
	IO_CHIPTOP.CLKSEL8.bit.AU0SEL	= 1;
	IO_CHIPTOP.CLKSEL8.bit.AU2SEL	= 1;
	IO_CHIPTOP.CLKSEL8.bit.AU3SEL	= 1;
	IO_CHIPTOP.CLKSEL8.bit.NETAUSEL	= 1;
	IO_CHIPTOP.CLKSEL8.bit.APCLK	= 1;
	IO_CHIPTOP.CLKSEL8.bit.AP0SEL	= 1;
	IO_CHIPTOP.CLKSEL8.bit.AP1SEL	= 1;
	IO_CHIPTOP.CLKSEL8.bit.AP2SEL	= 1;
	IO_CHIPTOP.CLKSEL8.bit.AP3SEL	= 1;
#endif
	Ddim_Print(("CLKSEL8_DSPCLK		= %d\n", DdTopone_GET_CLKSEL8_DSPCLK()));
	Ddim_Print(("CLKSEL8_SPICLK		= %d\n", DdTopone_GET_CLKSEL8_SPICLK()));
	Ddim_Print(("CLKSEL8_AUCLK		= %d\n", DdTopone_GET_CLKSEL8_AUCLK()));
	Ddim_Print(("CLKSEL8_AU0SEL		= %d\n", DdTopone_GET_CLKSEL8_AU0SEL()));
	Ddim_Print(("CLKSEL8_AU2SEL		= %d\n", DdTopone_GET_CLKSEL8_AU2SEL()));
	Ddim_Print(("CLKSEL8_AU3SEL		= %d\n", DdTopone_GET_CLKSEL8_AU3SEL()));
	Ddim_Print(("CLKSEL8_NETAUSEL	= %d\n", DdTopone_GET_CLKSEL8_NETAUSEL()));
	Ddim_Print(("CLKSEL8_APCLK		= %d\n", DdTopone_GET_CLKSEL8_APCLK()));
	Ddim_Print(("CLKSEL8_AP0SEL		= %d\n", DdTopone_GET_CLKSEL8_AP0SEL()));
	Ddim_Print(("CLKSEL8_AP1SEL		= %d\n", DdTopone_GET_CLKSEL8_AP1SEL()));
	Ddim_Print(("CLKSEL8_AP2SEL		= %d\n", DdTopone_GET_CLKSEL8_AP2SEL()));
	Ddim_Print(("CLKSEL8_AP3SEL		= %d\n", DdTopone_GET_CLKSEL8_AP3SEL()));
	Ddim_Print(("CLKSEL8 = %08lX\n", DdTopone_GET_CLKSEL8()));
}

static void ctGetClockClksel9(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.CLKSEL9.bit.PCLK		= 1;
	IO_CHIPTOP.CLKSEL9.bit.HCLK		= 1;
	IO_CHIPTOP.CLKSEL9.bit.HCLKBMH	= 1;
	IO_CHIPTOP.CLKSEL9.bit.ACLKEXS	= 1;
	IO_CHIPTOP.CLKSEL9.bit.ACLK		= 1;
#endif
	Ddim_Print(("CLKSEL9_PCLK		= %d\n", DdTopone_GET_CLKSEL9_PCLK()));
	Ddim_Print(("CLKSEL9_HCLK		= %d\n", DdTopone_GET_CLKSEL9_HCLK()));
	Ddim_Print(("CLKSEL9_HCLKBMH	= %d\n", DdTopone_GET_CLKSEL9_HCLKBMH()));
	Ddim_Print(("CLKSEL9_ACLKEXS	= %d\n", DdTopone_GET_CLKSEL9_ACLKEXS()));
	Ddim_Print(("CLKSEL9_ACLK		= %d\n", DdTopone_GET_CLKSEL9_ACLK()));
	Ddim_Print(("CLKSEL9 = %08lX\n", DdTopone_GET_CLKSEL9()));
}

static void ctGetClockClksel10(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.CLKSEL10.bit.ACLK400 = 1;
	IO_CHIPTOP.CLKSEL10.bit.MCLK200 = 1;
	IO_CHIPTOP.CLKSEL10.bit.MCLK400 = 1;
#endif
	Ddim_Print(("CLKSEL10_ACLK400	= %d\n", DdTopone_GET_CLKSEL10_ACLK400()));
	Ddim_Print(("CLKSEL10_MCLK200	= %d\n", DdTopone_GET_CLKSEL10_MCLK200()));
	Ddim_Print(("CLKSEL10_MCLK400	= %d\n", DdTopone_GET_CLKSEL10_MCLK400()));
	Ddim_Print(("CLKSEL10 = %08lX\n", DdTopone_GET_CLKSEL10()));
}

static void ctGetClockClksel11(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.CLKSEL11.bit.DCHREQ = 1;
#endif

	Ddim_Print(("CLKSEL11_DCHREQ = %d\n", DdTopone_GET_CLKSEL11_DCHREQ()));
	Ddim_Print(("CLKSEL11 = %08lX\n", DdTopone_GET_CLKSEL11()));
}

static void ctGetClockClksel12(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.CLKSEL12.bit.ACLK300	= 1;
	IO_CHIPTOP.CLKSEL12.bit.GYROCLK	= 1;
	IO_CHIPTOP.CLKSEL12.bit.FPT0CLK	= 1;
	IO_CHIPTOP.CLKSEL12.bit.FPT1CLK	= 1;
	IO_CHIPTOP.CLKSEL12.bit.MECLK	= 1;
	IO_CHIPTOP.CLKSEL12.bit.NFBCHCLK = 1;
	IO_CHIPTOP.CLKSEL12.bit.RIBCLK	= 1;
	IO_CHIPTOP.CLKSEL12.bit.SHDRCLK	= 1;
#endif
	Ddim_Print(("CLKSEL12_ACLK300	= %d\n", DdTopone_GET_CLKSEL12_ACLK300()));
	Ddim_Print(("CLKSEL12_GYROCLK	= %d\n", DdTopone_GET_CLKSEL12_GYROCLK()));
	Ddim_Print(("CLKSEL12_FPT0CLK	= %d\n", DdTopone_GET_CLKSEL12_FPT0CLK()));
	Ddim_Print(("CLKSEL12_FPT1CLK	= %d\n", DdTopone_GET_CLKSEL12_FPT1CLK()));
	Ddim_Print(("CLKSEL12_MECLK		= %d\n", DdTopone_GET_CLKSEL12_MECLK()));
	Ddim_Print(("CLKSEL12_NFBCHCLK	= %d\n", DdTopone_GET_CLKSEL12_NFBCHCLK()));
	Ddim_Print(("CLKSEL12_RIBCLK	= %d\n", DdTopone_GET_CLKSEL12_RIBCLK()));
	Ddim_Print(("CLKSEL12_SHDRCLK	= %d\n", DdTopone_GET_CLKSEL12_SHDRCLK()));
	Ddim_Print(("CLKSEL12 = %08lX\n", DdTopone_GET_CLKSEL12()));
}

static void ctSetClockClksel1(kint argc, kchar** argv)
{
	kulong val;

	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "RCLK" ) ) {
			DdTopone_SET_CLKSEL1_RCLK(val);
			Ddim_Print(("It set CLKSEL_RCLK	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL1.bit.RCLK	 = %d\n", IO_CHIPTOP.CLKSEL1.bit.RCLK));
		}else if (  0 == strcmp( argv[4], "UHS1CLK0" ) ) {
			DdTopone_SET_CLKSEL1_UHS1CLK0(val);
			Ddim_Print(("It set CLKSEL_UHS1CLK0	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL1.bit.UHS1CLK0	 = %d\n", IO_CHIPTOP.CLKSEL1.bit.UHS1CLK0));
		}else if (  0 == strcmp( argv[4], "UHS1CLK1" ) ) {
			DdTopone_SET_CLKSEL1_UHS1CLK1(val);
			Ddim_Print(("It set CLKSEL_UHS1CLK1	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL1.bit.UHS1CLK1	 = %d\n", IO_CHIPTOP.CLKSEL1.bit.UHS1CLK1));
		}else if (  0 == strcmp( argv[4], "UHS1CLK2" ) ) {
			DdTopone_SET_CLKSEL1_UHS1CLK2(val);
			Ddim_Print(("It set CLKSEL_UHS1CLK2	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL1.bit.UHS1CLK2	 = %d\n", IO_CHIPTOP.CLKSEL1.bit.UHS1CLK2));
		}else if (  0 == strcmp( argv[4], "UHS2CLK" ) ) {
			DdTopone_SET_CLKSEL1_UHS2CLK(val);
			Ddim_Print(("It set CLKSEL_UHS2CLK		 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL1.bit.UHS2CLK	 = %d\n", IO_CHIPTOP.CLKSEL1.bit.UHS2CLK));
		}else if (  0 == strcmp( argv[4], "NFCLK" ) ) {
			DdTopone_SET_CLKSEL1_NFCLK(val);
			Ddim_Print(("It set CLKSEL_NFCLK		 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL1.bit.NFCLK	 = %d\n", IO_CHIPTOP.CLKSEL1.bit.NFCLK));
		}else if (  0 == strcmp( argv[4], "EMMCCLK" ) ) {
			DdTopone_SET_CLKSEL1_EMMCCLK(val);
			Ddim_Print(("It set CLKSEL_EMMCCLK		 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL1.bit.EMMCCLK	 = %d\n", IO_CHIPTOP.CLKSEL1.bit.EMMCCLK));
		}
		else {
			Ddim_Print(("please check 4th parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void ctSetClockClksel2(kint argc, kchar** argv)
{
	kulong val;

	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "ELACLK" ) ) {
			DdTopone_SET_CLKSEL2_ELACLK(val);
			Ddim_Print(("It set CLKSEL_ELACLK	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL2.bit.ELACLK	 = %d\n", IO_CHIPTOP.CLKSEL2.bit.ELACLK));
		}else if (  0 == strcmp( argv[4], "JPGCLK" ) ) {
			DdTopone_SET_CLKSEL2_JPGCLK(val);
			Ddim_Print(("It set CLKSEL_JPGCLK		 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL2.bit.JPGCLK	 = %d\n", IO_CHIPTOP.CLKSEL2.bit.JPGCLK));
		}else if (  0 == strcmp( argv[4], "GPUCLK" ) ) {
			DdTopone_SET_CLKSEL2_GPUCLK(val);
			Ddim_Print(("It set CLKSEL_GPUCLK		 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL2.bit.GPUCLK	 = %d\n", IO_CHIPTOP.CLKSEL2.bit.GPUCLK));
		}else if (  0 == strcmp( argv[4], "IPUTMECLK" ) ) {
			DdTopone_SET_CLKSEL2_IPUTMECLK(val);
			Ddim_Print(("It set CLKSEL_IPUTMECLK	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL2.bit.IPUTMECLK	 = %d\n", IO_CHIPTOP.CLKSEL2.bit.IPUTMECLK));
		}else if (  0 == strcmp( argv[4], "IPUCLK" ) ) {
			DdTopone_SET_CLKSEL2_IPUCLK(val);
			Ddim_Print(("It set CLKSEL_IPUCLK	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL2.bit.IPUCLK	 = %d\n", IO_CHIPTOP.CLKSEL2.bit.IPUCLK));
		}else if (  0 == strcmp( argv[4], "MIFCLK" ) ) {
			DdTopone_SET_CLKSEL2_MIFCLK(val);
			Ddim_Print(("It set CLKSEL_MIFCLK		 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL2.bit.MIFCLK	 = %d\n", IO_CHIPTOP.CLKSEL2.bit.MIFCLK));
		}else if (  0 == strcmp( argv[4], "HIFCLK" ) ) {
			DdTopone_SET_CLKSEL2_HIFCLK(val);
			Ddim_Print(("It set CLKSEL_HIFCLK		 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL2.bit.HIFCLK	 = %d\n", IO_CHIPTOP.CLKSEL2.bit.HIFCLK));
		}else if (  0 == strcmp( argv[4], "RAWCLK" ) ) {
			DdTopone_SET_CLKSEL2_RAWCLK(val);
			Ddim_Print(("It set CLKSEL_RAWCLK	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL2.bit.RAWCLK	 = %d\n", IO_CHIPTOP.CLKSEL2.bit.RAWCLK));
		}
		else {
			Ddim_Print(("please check 4th parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void ctSetClockClksel3(kint argc, kchar** argv)
{
	kulong val;

	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "VDFCLK" ) ) {
			DdTopone_SET_CLKSEL3_VDFCLK(val);
			Ddim_Print(("It set CLKSEL_VDFCLK	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL3.bit.VDFCLK	 = %d\n", IO_CHIPTOP.CLKSEL3.bit.VDFCLK));
		}
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
		else if ( 0 == strcmp( argv[4], "PXFCLK" ) ) {
			DdTopone_SET_CLKSEL3_PXFCLK(val);
			Ddim_Print(("It set CLKSEL_PXFCLK	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL3.bit.PXFCLK	 = %d\n", IO_CHIPTOP.CLKSEL3.bit.PXFCLK));
		}
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
		else if ( 0 == strcmp( argv[4], "HEVENCCLK" ) ) {
			DdTopone_SET_CLKSEL3_HEVENCCLK(val);
			Ddim_Print(("It set CLKSEL_HEVENCCLK	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL3.bit.HEVENCCLK	 = %d\n", IO_CHIPTOP.CLKSEL3.bit.HEVENCCLK));
		}
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
		else if ( 0 == strcmp( argv[4], "IPPCLK" ) ) {
			DdTopone_SET_CLKSEL3_IPPCLK(val);
			Ddim_Print(("It set CLKSEL_IPPCLK		 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL3.bit.IPPCLK	 = %d\n", IO_CHIPTOP.CLKSEL3.bit.IPPCLK));
		}else if (  0 == strcmp( argv[4], "PASCLK" ) ) {
			DdTopone_SET_CLKSEL3_PASCLK(val);
			Ddim_Print(("It set CLKSEL_PASCLK		 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL3.bit.PASCLK	 = %d\n", IO_CHIPTOP.CLKSEL3.bit.PASCLK));
		}else if (  0 == strcmp( argv[4], "IIPCLK" ) ) {
			DdTopone_SET_CLKSEL3_IIPCLK(val);
			Ddim_Print(("It set CLKSEL_IIPCLK	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL3.bit.IIPCLK	 = %d\n", IO_CHIPTOP.CLKSEL3.bit.IIPCLK));
		}else if (  0 == strcmp( argv[4], "SENMSKCLK" ) ) {
			DdTopone_SET_CLKSEL3_SENMSKCLK(val);
			Ddim_Print(("It set CLKSEL_SENMSKCLK	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL3.bit.SENMSKCLK	 = %d\n", IO_CHIPTOP.CLKSEL3.bit.SENMSKCLK));
		}else if (  0 == strcmp( argv[4], "SENCLK" ) ) {
			DdTopone_SET_CLKSEL3_SENCLK(val);
			Ddim_Print(("It set CLKSEL_SENCLK		 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL3.bit.SENCLK	 = %d\n", IO_CHIPTOP.CLKSEL3.bit.SENCLK));
		}else if (  0 == strcmp( argv[4], "PIPESEL" ) ) {
			DdTopone_SET_CLKSEL3_PIPESEL(val);
			Ddim_Print(("It set CLKSEL_PIPESEL		 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL3.bit.PIPESEL	 = %d\n", IO_CHIPTOP.CLKSEL3.bit.PIPESEL));
		}
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
		else if ( 0 == strcmp( argv[4], "HEVENCSEL" ) ) {
			DdTopone_SET_CLKSEL3_HEVENCSEL(val);
			Ddim_Print(("It set CLKSEL_HEVENCSEL		 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL3.bit.HEVENCSEL	 = %d\n", IO_CHIPTOP.CLKSEL3.bit.HEVENCSEL));
		}
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
		else {
			Ddim_Print(("please check 4th parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void ctSetClockClksel4(kint argc, kchar** argv)
{
	kulong val;

	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "CNR1CLK" ) ) {
			DdTopone_SET_CLKSEL4_CNR1CLK(val);
			Ddim_Print(("It set CLKSEL_CNR1CLK		 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL4.bit.CNR1CLK	 = %d\n", IO_CHIPTOP.CLKSEL4.bit.CNR1CLK));
		}else if (  0 == strcmp( argv[4], "B2R1CLK" ) ) {
			DdTopone_SET_CLKSEL4_B2R1CLK(val);
			Ddim_Print(("It set CLKSEL_B2R1CLK		 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL4.bit.B2R1CLK	 = %d\n", IO_CHIPTOP.CLKSEL4.bit.B2R1CLK));
		}else if (  0 == strcmp( argv[4], "LTM1CLK" ) ) {
			DdTopone_SET_CLKSEL4_LTM1CLK(val);
			Ddim_Print(("It set CLKSEL_LTM1CLK		 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL4.bit.LTM1CLK	 = %d\n", IO_CHIPTOP.CLKSEL4.bit.LTM1CLK));
		}else if (  0 == strcmp( argv[4], "R2Y1CLK" ) ) {
			DdTopone_SET_CLKSEL4_R2Y1CLK(val);
			Ddim_Print(("It set CLKSEL_R2Y1CLK		 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL4.bit.R2Y1CLK	 = %d\n", IO_CHIPTOP.CLKSEL4.bit.R2Y1CLK));
		}else if (  0 == strcmp( argv[4], "SRO1CLK_2" ) ) {
			DdTopone_SET_CLKSEL4_SRO1CLK_2(val);
			Ddim_Print(("It set CLKSEL_SRO1CLK_2	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL4.bit.SRO1CLK_2	 = %d\n", IO_CHIPTOP.CLKSEL4.bit.SRO1CLK_2));
		}
		else {
			Ddim_Print(("please check 4th parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void ctSetClockClksel5(kint argc, kchar** argv)
{
	kulong val;

	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "LTMRBK1CLK" ) ) {
			DdTopone_SET_CLKSEL5_LTMRBK1CLK(val);
			Ddim_Print(("It set CLKSEL_LTMRBK1CLK	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL5.bit.LTMRBK1CLK	 = %d\n", IO_CHIPTOP.CLKSEL5.bit.LTMRBK1CLK));
		}else if (  0 == strcmp( argv[4], "B2B1CLK" ) ) {
			DdTopone_SET_CLKSEL5_B2B1CLK(val);
			Ddim_Print(("It set CLKSEL_B2B1CLK		 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL5.bit.B2B1CLK	 = %d\n", IO_CHIPTOP.CLKSEL5.bit.B2B1CLK));
		}else if (  0 == strcmp( argv[4], "SRO1CLK" ) ) {
			DdTopone_SET_CLKSEL5_SRO1CLK(val);
			Ddim_Print(("It set CLKSEL_SRO1CLK	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL5.bit.SRO1CLK	 = %d\n", IO_CHIPTOP.CLKSEL5.bit.SRO1CLK));
		}
		else {
			Ddim_Print(("please check 4th parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void ctSetClockClksel6(kint argc, kchar** argv)
{
	kulong val;

	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "CNR2CLK" ) ) {
			DdTopone_SET_CLKSEL6_CNR2CLK(val);
			Ddim_Print(("It set CLKSEL_CNR2CLK		 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL6.bit.CNR2CLK	 = %d\n", IO_CHIPTOP.CLKSEL6.bit.CNR2CLK));
		}else if (  0 == strcmp( argv[4], "B2R2CLK" ) ) {
			DdTopone_SET_CLKSEL6_B2R2CLK(val);
			Ddim_Print(("It set CLKSEL_B2R2CLK		 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL6.bit.B2R2CLK	 = %d\n", IO_CHIPTOP.CLKSEL6.bit.B2R2CLK));
		}else if (  0 == strcmp( argv[4], "LTM2CLK" ) ) {
			DdTopone_SET_CLKSEL6_LTM2CLK(val);
			Ddim_Print(("It set CLKSEL_LTM2CLK		 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL6.bit.LTM2CLK	 = %d\n", IO_CHIPTOP.CLKSEL6.bit.LTM2CLK));
		}else if (  0 == strcmp( argv[4], "R2Y2CLK" ) ) {
			DdTopone_SET_CLKSEL6_R2Y2CLK(val);
			Ddim_Print(("It set CLKSEL_R2Y2CLK		 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL6.bit.R2Y2CLK	 = %d\n", IO_CHIPTOP.CLKSEL6.bit.R2Y2CLK));
		}else if (  0 == strcmp( argv[4], "SRO2CLK_2" ) ) {
			DdTopone_SET_CLKSEL6_SRO2CLK_2(val);
			Ddim_Print(("It set CLKSEL_SRO2CLK_2	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL6.bit.SRO2CLK_2	 = %d\n", IO_CHIPTOP.CLKSEL6.bit.SRO2CLK_2));
		}
		else {
			Ddim_Print(("please check 4th parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void ctSetClockClksel7(kint argc, kchar** argv)
{
	kulong val;

	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "LTMRBK2CLK" ) ) {
			DdTopone_SET_CLKSEL7_LTMRBK2CLK(val);
			Ddim_Print(("It set CLKSEL_LTMRBK2CLK	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL7.bit.LTMRBK2CLK	 = %d\n", IO_CHIPTOP.CLKSEL7.bit.LTMRBK2CLK));
		}else if (  0 == strcmp( argv[4], "B2B2CLK" ) ) {
			DdTopone_SET_CLKSEL7_B2B2CLK(val);
			Ddim_Print(("It set CLKSEL_B2B2CLK		 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL7.bit.B2B2CLK	 = %d\n", IO_CHIPTOP.CLKSEL7.bit.B2B2CLK));
		}else if (  0 == strcmp( argv[4], "SRO2CLK" ) ) {
			DdTopone_SET_CLKSEL7_SRO2CLK(val);
			Ddim_Print(("It set CLKSEL_SRO2CLK	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL7.bit.SRO2CLK	 = %d\n", IO_CHIPTOP.CLKSEL7.bit.SRO2CLK));
		}
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
		else if ( 0 == strcmp( argv[4], "MIPISEL" ) ) {
			DdTopone_SET_CLKSEL7_MIPISEL(val);
			Ddim_Print(("It set CLKSEL_MIPISEL	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL7.bit.MIPISEL	 = %d\n", IO_CHIPTOP.CLKSEL7.bit.MIPISEL));
		}else if (  0 == strcmp( argv[4], "PDM0SEL" ) ) {
			DdTopone_SET_CLKSEL7_PDM0SEL(val);
			Ddim_Print(("It set CLKSEL_PDM0SEL	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL7.bit.PDM0SEL	 = %d\n", IO_CHIPTOP.CLKSEL7.bit.PDM0SEL));
		}else if (  0 == strcmp( argv[4], "PDM1SEL" ) ) {
			DdTopone_SET_CLKSEL7_PDM1SEL(val);
			Ddim_Print(("It set CLKSEL_PDM1SEL	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL7.bit.PDM1SEL	 = %d\n", IO_CHIPTOP.CLKSEL7.bit.PDM1SEL));
		}
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
		else {
			Ddim_Print(("please check 4th parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void ctSetClockClksel8(kint argc, kchar** argv)
{
	kulong val;

	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "DSPCLK" ) ) {
			DdTopone_SET_CLKSEL8_DSPCLK(val);
			Ddim_Print(("It set CLKSEL_DSPCLK	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL8.bit.DSPCLK	 = %d\n", IO_CHIPTOP.CLKSEL8.bit.DSPCLK));
		}else if (  0 == strcmp( argv[4], "SPICLK" ) ) {
			DdTopone_SET_CLKSEL8_SPICLK(val);
			Ddim_Print(("It set CLKSEL_SPICLK	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL8.bit.SPICLK	 = %d\n", IO_CHIPTOP.CLKSEL8.bit.SPICLK));
		}else if (  0 == strcmp( argv[4], "AUCLK" ) ) {
			DdTopone_SET_CLKSEL8_AUCLK(val);
			Ddim_Print(("It set CLKSEL_AUCLK	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL8.bit.AUCLK	 = %d\n", IO_CHIPTOP.CLKSEL8.bit.AUCLK));
		}else if (  0 == strcmp( argv[4], "AU0SEL" ) ) {
			DdTopone_SET_CLKSEL8_AU0SEL(val);
			Ddim_Print(("It set CLKSEL_AU0SEL		 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL8.bit.AU0SEL	 = %d\n", IO_CHIPTOP.CLKSEL8.bit.AU0SEL));
		}else if (  0 == strcmp( argv[4], "AU2SEL" ) ) {
			DdTopone_SET_CLKSEL8_AU2SEL(val);
			Ddim_Print(("It set CLKSEL_AU2SEL		 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL8.bit.AU2SEL	 = %d\n", IO_CHIPTOP.CLKSEL8.bit.AU2SEL));
		}else if (  0 == strcmp( argv[4], "AU3SEL" ) ) {
			DdTopone_SET_CLKSEL8_AU3SEL(val);
			Ddim_Print(("It set CLKSEL_AU3SEL		 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL8.bit.AU3SEL	 = %d\n", IO_CHIPTOP.CLKSEL8.bit.AU3SEL));
		}else if (  0 == strcmp( argv[4], "NETAUSEL" ) ) {
			DdTopone_SET_CLKSEL8_NETAUSEL(val);
			Ddim_Print(("It set CLKSEL_NETAUSEL	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL8.bit.NETAUSEL	 = %d\n", IO_CHIPTOP.CLKSEL8.bit.NETAUSEL));
		}else if (  0 == strcmp( argv[4], "APCLK" ) ) {
			DdTopone_SET_CLKSEL8_APCLK(val);
			Ddim_Print(("It set CLKSEL_APCLK		 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL8.bit.APCLK	 = %d\n", IO_CHIPTOP.CLKSEL8.bit.APCLK));
		}else if (  0 == strcmp( argv[4], "AP0SEL" ) ) {
			DdTopone_SET_CLKSEL8_AP0SEL(val);
			Ddim_Print(("It set CLKSEL_AP0SEL		 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL8.bit.AP0SEL	 = %d\n", IO_CHIPTOP.CLKSEL8.bit.AP0SEL));
		}else if (  0 == strcmp( argv[4], "AP1SEL" ) ) {
			DdTopone_SET_CLKSEL8_AP1SEL(val);
			Ddim_Print(("It set CLKSEL_AP1SEL		 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL8.bit.AP1SEL	 = %d\n", IO_CHIPTOP.CLKSEL8.bit.AP1SEL));
		}else if (  0 == strcmp( argv[4], "AP2SEL" ) ) {
			DdTopone_SET_CLKSEL8_AP2SEL(val);
			Ddim_Print(("It set CLKSEL_AP2SEL		 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL8.bit.AP2SEL	 = %d\n", IO_CHIPTOP.CLKSEL8.bit.AP2SEL));
		}else if (  0 == strcmp( argv[4], "AP3SEL" ) ) {
			DdTopone_SET_CLKSEL8_AP3SEL(val);
			Ddim_Print(("It set CLKSEL_AP3SEL		 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL8.bit.AP3SEL	 = %d\n", IO_CHIPTOP.CLKSEL8.bit.AP3SEL));
		}
		else {
			Ddim_Print(("please check 4th parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void ctSetClockClksel9(kint argc, kchar** argv)
{
	kulong val;

	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "PCLK" ) ) {
			DdTopone_SET_CLKSEL9_PCLK(val);
			Ddim_Print(("It set CLKSEL_PCLK		 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL9.bit.PCLK	 = %d\n", IO_CHIPTOP.CLKSEL9.bit.PCLK));
		}else if (  0 == strcmp( argv[4], "HCLK" ) ) {
			DdTopone_SET_CLKSEL9_HCLK(val);
			Ddim_Print(("It set CLKSEL_HCLK		 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL9.bit.HCLK	 = %d\n", IO_CHIPTOP.CLKSEL9.bit.HCLK));
		}else if (  0 == strcmp( argv[4], "HCLKBMH" ) ) {
			DdTopone_SET_CLKSEL9_HCLKBMH(val);
			Ddim_Print(("It set CLKSEL_HCLKBMH	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL9.bit.HCLKBMH	 = %d\n", IO_CHIPTOP.CLKSEL9.bit.HCLKBMH));
		}else if (  0 == strcmp( argv[4], "ACLKEXS" ) ) {
			DdTopone_SET_CLKSEL9_ACLKEXS(val);
			Ddim_Print(("It set CLKSEL_ACLKEXS	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL9.bit.ACLKEXS	 = %d\n", IO_CHIPTOP.CLKSEL9.bit.ACLKEXS));
		}else if (  0 == strcmp( argv[4], "ACLK" ) ) {
			DdTopone_SET_CLKSEL9_ACLK(val);
			Ddim_Print(("It set CLKSEL_ACLK	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL9.bit.ACLK	 = %d\n", IO_CHIPTOP.CLKSEL9.bit.ACLK));
		}
		else {
			Ddim_Print(("please check 4th parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void ctSetClockClksel10(kint argc, kchar** argv)
{
	kulong val;

	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "ACLK400" ) ) {
			DdTopone_SET_CLKSEL10_ACLK400(val);
			Ddim_Print(("It set CLKSEL_ACLK400		 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL10.bit.ACLK400	 = %d\n", IO_CHIPTOP.CLKSEL10.bit.ACLK400));
		}else if (  0 == strcmp( argv[4], "MCLK200" ) ) {
			DdTopone_SET_CLKSEL10_MCLK200(val);
			Ddim_Print(("It set CLKSEL_MCLK200	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL10.bit.MCLK200	 = %d\n", IO_CHIPTOP.CLKSEL10.bit.MCLK200));
		}else if (  0 == strcmp( argv[4], "MCLK400" ) ) {
			DdTopone_SET_CLKSEL10_MCLK400(val);
			Ddim_Print(("It set CLKSEL_MCLK400		 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL10.bit.MCLK400	 = %d\n", IO_CHIPTOP.CLKSEL10.bit.MCLK400));
		}
		else {
			Ddim_Print(("please check 4th parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void ctSetClockClksel11(kint argc, kchar** argv)
{
	kulong val;

	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "DCHREQ" ) ) {
			DdTopone_SET_CLKSEL11_DCHREQ(val);
			Ddim_Print(("It set CLKSEL_DCHREQ	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL11.bit.DCHREQ	 = %d\n", IO_CHIPTOP.CLKSEL11.bit.DCHREQ));
		}
		else {
			Ddim_Print(("please check 4th parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void ctSetClockClksel12(kint argc, kchar** argv)
{
	kulong val;

	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "ACLK300" ) ) {
			DdTopone_SET_CLKSEL12_ACLK300(val);
			Ddim_Print(("It set CLKSEL_ACLK300	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL12.bit.ACLK300	 = %d\n", IO_CHIPTOP.CLKSEL12.bit.ACLK300));
		}else if (  0 == strcmp( argv[4], "GYROCLK" ) ) {
			DdTopone_SET_CLKSEL12_GYROCLK(val);
			Ddim_Print(("It set CLKSEL_GYROCLK	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL12.bit.GYROCLK	 = %d\n", IO_CHIPTOP.CLKSEL12.bit.GYROCLK));
		}else if (  0 == strcmp( argv[4], "FPT0CLK" ) ) {
			DdTopone_SET_CLKSEL12_FPT0CLK(val);
			Ddim_Print(("It set CLKSEL_FPT0CLK	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL12.bit.FPT0CLK	 = %d\n", IO_CHIPTOP.CLKSEL12.bit.FPT0CLK));
		}else if (  0 == strcmp( argv[4], "FPT1CLK" ) ) {
			DdTopone_SET_CLKSEL12_FPT1CLK(val);
			Ddim_Print(("It set CLKSEL_FPT1CLK	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL12.bit.FPT1CLK	 = %d\n", IO_CHIPTOP.CLKSEL12.bit.FPT1CLK));
		}else if (  0 == strcmp( argv[4], "MECLK" ) ) {
			DdTopone_SET_CLKSEL12_MECLK(val);
			Ddim_Print(("It set CLKSEL_MECLK	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL12.bit.MECLK	 = %d\n", IO_CHIPTOP.CLKSEL12.bit.MECLK));
		}else if (  0 == strcmp( argv[4], "NFBCHCLK" ) ) {
			DdTopone_SET_CLKSEL12_NFBCHCLK(val);
			Ddim_Print(("It set CLKSEL_NFBCHCLK	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL12.bit.NFBCHCLK	 = %d\n", IO_CHIPTOP.CLKSEL12.bit.NFBCHCLK));
		}else if (  0 == strcmp( argv[4], "RIBCLK" ) ) {
			DdTopone_SET_CLKSEL12_RIBCLK(val);
			Ddim_Print(("It set CLKSEL_RIBCLK	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL12.bit.RIBCLK	 = %d\n", IO_CHIPTOP.CLKSEL12.bit.RIBCLK));
		}else if (  0 == strcmp( argv[4], "SHDRCLK" ) ) {
			DdTopone_SET_CLKSEL12_SHDRCLK(val);
			Ddim_Print(("It set CLKSEL_SHDRCLK	 Clock select.\n"));
			Ddim_Print(("IO_CHIPTOP.CLKSEL12.bit.SHDRCLK	 = %d\n", IO_CHIPTOP.CLKSEL12.bit.SHDRCLK));
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
void ct_clock_clksel_set(CtClockClksel *self)
{
    CtClockClkselPrivate *priv = CT_CLOCK_CLKSEL_GET_PRIVATE(self);

    if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clksel1" ) ) {
        ctSetClockClksel1( ((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv );
    }else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clksel2" ) ) {
        ctSetClockClksel2( ((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv );
    }else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clksel3" ) ) {
        ctSetClockClksel3( ((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv );
    }else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clksel4" ) ) {
        ctSetClockClksel4( ((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv );
    }else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clksel5" ) ) {
        ctSetClockClksel5( ((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv );
    }else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clksel6" ) ) {
        ctSetClockClksel6( ((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv );
    }else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clksel7" ) ) {
        ctSetClockClksel7( ((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv );
    }else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clksel8" ) ) {
        ctSetClockClksel8( ((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv );
    }else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clksel9" ) ) {
        ctSetClockClksel9( ((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv );
    }else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clksel10" ) ) {
        ctSetClockClksel10( ((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv );
    }else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clksel11" ) ) {
        ctSetClockClksel11( ((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv );
    }else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clksel12" ) ) {
        ctSetClockClksel12( ((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv );
    }else {
		ct_dd_parameter_set_parameter((CtDdParameter *)priv->ctClockPllcnt,
				((CtDdParameter *)self)->argc,((CtDdParameter *)self)->argv);
		ct_clock_pllcnt_set(priv->ctClockPllcnt);
	}
}

void ct_clock_clksel_get(CtClockClksel *self)
{
    CtClockClkselPrivate *priv = CT_CLOCK_CLKSEL_GET_PRIVATE(self);

    if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clksel1" ) ) {
        ctGetClockClksel1();
    }else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clksel2" ) ) {
        ctGetClockClksel2();
    }else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clksel3" ) ) {
        ctGetClockClksel3();
    }else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clksel4" ) ) {
        ctGetClockClksel4();
    }else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clksel5" ) ) {
        ctGetClockClksel5();
    }else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clksel6" ) ) {
        ctGetClockClksel6();
    }else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clksel7" ) ) {
        ctGetClockClksel7();
    }else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clksel8" ) ) {
        ctGetClockClksel8();
    }else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clksel9" ) ) {
        ctGetClockClksel9();
    }else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clksel10" ) ) {
        ctGetClockClksel10();
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clksel11" ) ) {
        ctGetClockClksel11();
    }else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "clksel12" ) ) {
        ctGetClockClksel12();
    }else {
		ct_dd_parameter_set_parameter((CtDdParameter *)priv->ctClockPllcnt,
				((CtDdParameter *)self)->argc,((CtDdParameter *)self)->argv);
		ct_clock_pllcnt_get(priv->ctClockPllcnt);
	}
}

CtClockClksel* ct_clock_clksel_new(void) 
{
    CtClockClksel *self = k_object_new_with_private(CT_TYPE_CLOCK_CLKSEL, sizeof(CtClockClkselPrivate));
    return self;
}
