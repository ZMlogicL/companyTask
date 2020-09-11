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
#include "ctddtop.h"
#include "ctreset.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtReset, ct_reset);
#define CT_RESET_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtResetPrivate,CT_TYPE_RESET))

struct _CtResetPrivate
{
	kint a;
};
/****************
* DECLS
*/
static void 			ct_reset_constructor(CtReset *self);
static void 			ct_reset_destructor(CtReset *self);
static void  			ctGetResetCtrl(kint argc, kchar** argv);
static void  			ctSetResetCtrl(kint argc, kchar** argv);
/****************
* IMPL
*/
static void ct_reset_constructor(CtReset *self) 
{
	// CtResetPrivate *priv = CT_RESET_GET_PRIVATE(self);
}

static void ct_reset_destructor(CtReset *self) 
{
	// CtResetPrivate *priv = CT_RESET_GET_PRIVATE(self);
}

static void  ctGetResetCtrl(kint argc, kchar** argv)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.CRRSM.bit.__WDRST		= 1;
	IO_CHIPTOP.CRRSM.bit.__SWRST		= 1;
	IO_CHIPTOP.CRRSM.bit.__SRST			= 1;
	IO_CHIPTOP.CRRSM.bit.__PORST		= 1;
#endif
	Ddim_Print(("### CRRSM Register ###\n"));
	Ddim_Print(("IO_CHIPTOP.CRRSM.bit.__WDRST		= %d, CRRSM_WDRST			= %d\n",
			IO_CHIPTOP.CRRSM.bit.__WDRST, DdToptwo_GET_CRRSM_WDRST()));
	Ddim_Print(("IO_CHIPTOP.CRRSM.bit.__SWRST		= %d, CRRSM_SWRST			= %d\n",
			IO_CHIPTOP.CRRSM.bit.__SWRST, DdToptwo_GET_CRRSM_SWRST()));
	Ddim_Print(("IO_CHIPTOP.CRRSM.bit.__SRST		= %d, CRRSM_SRST			= %d\n",
			IO_CHIPTOP.CRRSM.bit.__SRST, DdToptwo_GET_CRRSM_SRST()));
	Ddim_Print(("IO_CHIPTOP.CRRSM.bit.__PORST		= %d, CRRSM_PORST			= %d\n",
			IO_CHIPTOP.CRRSM.bit.__PORST, DdToptwo_GET_CRRSM_PORST()));
	Ddim_Print(("\n"));
	Ddim_Print(("### CRRRS Register ###\n"));
	Ddim_Print(("IO_CHIPTOP.CRRRS.bit.RIBSR			= %d, CRRRS_RIBSR			= %d\n",
			IO_CHIPTOP.CRRRS.bit.RIBSR, DdToptwo_GET_CRRRS_RIBSR()));
	Ddim_Print(("IO_CHIPTOP.CRRRS.bit.HEIPPASYNCSR	= %d, CRRRS_HEIPPASYNCSR	= %d\n",
			IO_CHIPTOP.CRRRS.bit.HEIPPASYNCSR, DdToptwo_GET_CRRRS_HEIPPASYNCSR()));
	Ddim_Print(("IO_CHIPTOP.CRRRS.bit.HEIPPSYNCSR	= %d, CRRRS_HEIPPSYNCSR		= %d\n",
			IO_CHIPTOP.CRRRS.bit.HEIPPSYNCSR, DdToptwo_GET_CRRRS_HEIPPSYNCSR()));
	Ddim_Print(("IO_CHIPTOP.CRRRS.bit.HEVDFSR		= %d, CRRRS_HEVDFSR			= %d\n",
			IO_CHIPTOP.CRRRS.bit.HEVDFSR, DdToptwo_GET_CRRRS_HEVDFSR()));
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	Ddim_Print(("IO_CHIPTOP.CRRRS.bit.HEPXFSR		= %d, CRRRS_HEPXFSR			= %d\n",
			IO_CHIPTOP.CRRRS.bit.HEPXFSR, DdToptwo_GET_CRRRS_HEPXFSR()));
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	Ddim_Print(("IO_CHIPTOP.CRRRS.bit.HEVENCSR		= %d, CRRRS_HEVENCSR		= %d\n",
			IO_CHIPTOP.CRRRS.bit.HEVENCSR, DdToptwo_GET_CRRRS_HEVENCSR()));
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	Ddim_Print(("IO_CHIPTOP.CRRRS.bit.DSPSR			= %d, CRRRS_DSPSR			= %d\n",
			IO_CHIPTOP.CRRRS.bit.DSPSR, DdToptwo_GET_CRRRS_DSPSR()));
	Ddim_Print(("IO_CHIPTOP.CRRRS.bit.CPU0_SR		= %d, CRRRS_CPU0_SR			= %d\n",
			IO_CHIPTOP.CRRRS.bit.CPU0_SR, DdToptwo_GET_CRRRS_CPU0_SR()));
	Ddim_Print(("IO_CHIPTOP.CRRRS.bit.CPU1_SR		= %d, CRRRS_CPU1_SR			= %d\n",
			IO_CHIPTOP.CRRRS.bit.CPU1_SR, DdToptwo_GET_CRRRS_CPU1_SR()));
	Ddim_Print(("IO_CHIPTOP.CRRRS.bit.CPU2_SR		= %d, CRRRS_CPU2_SR			= %d\n",
			IO_CHIPTOP.CRRRS.bit.CPU2_SR, DdToptwo_GET_CRRRS_CPU2_SR()));
	Ddim_Print(("IO_CHIPTOP.CRRRS.bit.CPU3_SR		= %d, CRRRS_CPU3_SR			= %d\n",
			IO_CHIPTOP.CRRRS.bit.CPU3_SR, DdToptwo_GET_CRRRS_CPU3_SR()));
}

static void  ctSetResetCtrl(kint argc, kchar** argv)
{
	if (argc == 4) {
		if ( 0 == strcmp( argv[3], "CRRSM_WDRST" ) ) {
			DdToptwo_CLEAR_CRRSM_WDRST();
			Ddim_Print(("It set CRRSM_WDRST select.\n"));
			Ddim_Print(("IO_CHIPTOP.CRRSM.bit.__WDRST=%d\n", IO_CHIPTOP.CRRSM.bit.__WDRST));
		}else if (  0 == strcmp( argv[3], "CRRSM_SWRST" ) ) {
			DdToptwo_CLEAR_CRRSM_SWRST();
			Ddim_Print(("It set CRRSM_SWRST select.\n"));
			Ddim_Print(("IO_CHIPTOP.CRRSM.bit.__SWRST=%d\n", IO_CHIPTOP.CRRSM.bit.__SWRST));
		}else if (  0 == strcmp( argv[3], "CRRSM_SRST" ) ) {
			DdToptwo_CLEAR_CRRSM_SRST();
			Ddim_Print(("It set CRRSM_SRST select.\n"));
			Ddim_Print(("IO_CHIPTOP.CRRSM.bit.__SRST=%d\n", IO_CHIPTOP.CRRSM.bit.__SRST));
		}else if (  0 == strcmp( argv[3], "CRRSM_PORST" ) ) {
			DdToptwo_CLEAR_CRRSM_PORST();
			Ddim_Print(("It set CRRSM_PORST select.\n"));
			Ddim_Print(("IO_CHIPTOP.CRRSM.bit.__PORST=%d\n", IO_CHIPTOP.CRRSM.bit.__PORST));
		}else if (  0 == strcmp( argv[3], "CRRRS_CPU0_SR_CLR" ) ) {
			DdToptwo_CLEAR_CRRRS_CPU0_SR();
			Ddim_Print(("It set CRRRS_CPU0_SR_CLR select.\n"));
			Ddim_Print(("IO_CHIPTOP.CRRRS.bit.CPU0_SR=%d\n", IO_CHIPTOP.CRRRS.bit.CPU0_SR));
		}else if (  0 == strcmp( argv[3], "CRRRS_CPU0_SR_RES" ) ) {
			DdToptwo_RESET_CRRRS_CPU0_SR();
			Ddim_Print(("It set CRRRS_CPU0_SR_RES select.\n"));
			Ddim_Print(("IO_CHIPTOP.CRRRS.bit.CPU0_SR=%d\n", IO_CHIPTOP.CRRRS.bit.CPU0_SR));
		}else if (  0 == strcmp( argv[3], "CRRRS_CPU1_SR_CLR" ) ) {
			DdToptwo_CLEAR_CRRRS_CPU1_SR();
			Ddim_Print(("It set CRRRS_CPU1_SR_CLR select.\n"));
			Ddim_Print(("IO_CHIPTOP.CRRRS.bit.CPU1_SR=%d\n", IO_CHIPTOP.CRRRS.bit.CPU1_SR));
		}else if (  0 == strcmp( argv[3], "CRRRS_CPU1_SR_RES" ) ) {
			DdToptwo_RESET_CRRRS_CPU1_SR();
			Ddim_Print(("It set CRRRS_CPU1_SR_RES select.\n"));
			Ddim_Print(("IO_CHIPTOP.CRRRS.bit.CPU1_SR=%d\n", IO_CHIPTOP.CRRRS.bit.CPU1_SR));
		}else if (  0 == strcmp( argv[3], "CRRRS_CPU2_SR_CLR" ) ) {
			DdToptwo_CLEAR_CRRRS_CPU2_SR();
			Ddim_Print(("It set CRRRS_CPU2_SR_CLR select.\n"));
			Ddim_Print(("IO_CHIPTOP.CRRRS.bit.CPU2_SR=%d\n", IO_CHIPTOP.CRRRS.bit.CPU2_SR));
		}else if (  0 == strcmp( argv[3], "CRRRS_CPU2_SR_RES" ) ) {
			DdToptwo_RESET_CRRRS_CPU2_SR();
			Ddim_Print(("It set CRRRS_CPU2_SR_RES select.\n"));
			Ddim_Print(("IO_CHIPTOP.CRRRS.bit.CPU2_SR=%d\n", IO_CHIPTOP.CRRRS.bit.CPU2_SR));
		}else if (  0 == strcmp( argv[3], "CRRRS_CPU3_SR_CLR" ) ) {
			DdToptwo_CLEAR_CRRRS_CPU3_SR();
			Ddim_Print(("It set CRRRS_CPU3_SR_CLR select.\n"));
			Ddim_Print(("IO_CHIPTOP.CRRRS.bit.CPU3_SR=%d\n", IO_CHIPTOP.CRRRS.bit.CPU3_SR));
		}else if (  0 == strcmp( argv[3], "CRRRS_CPU3_SR_RES" ) ) {
			DdToptwo_RESET_CRRRS_CPU3_SR();
			Ddim_Print(("It set CRRRS_CPU3_SR_RES select.\n"));
			Ddim_Print(("IO_CHIPTOP.CRRRS.bit.CPU3_SR=%d\n", IO_CHIPTOP.CRRRS.bit.CPU3_SR));
		}else if (  0 == strcmp( argv[3], "CRRRS_RIBSR_CLR" ) ) {
			DdToptwo_CLEAR_CRRRS_RIBSR();
			Ddim_Print(("It set CRRRS_RIBSR_CLR select.\n"));
			Ddim_Print(("IO_CHIPTOP.CRRRS.bit.RIBSR=%d\n", IO_CHIPTOP.CRRRS.bit.RIBSR));
		}else if (  0 == strcmp( argv[3], "CRRRS_RIBSR_RES" ) ) {
			DdToptwo_RESET_CRRRS_RIBSR();
			Ddim_Print(("It set CRRRS_RIBSR_RES select.\n"));
			Ddim_Print(("IO_CHIPTOP.CRRRS.bit.RIBSR=%d\n", IO_CHIPTOP.CRRRS.bit.RIBSR));
		}else if (  0 == strcmp( argv[3], "CRRRS_HEIPPASYNCSR_CLR" ) ) {
			DdToptwo_CLEAR_CRRRS_HEIPPASYNCSR();
			Ddim_Print(("It set CRRRS_HEIPPASYNCSR_CLR select.\n"));
			Ddim_Print(("IO_CHIPTOP.CRRRS.bit.HEIPPASYNCSR=%d\n", IO_CHIPTOP.CRRRS.bit.HEIPPASYNCSR));
		}else if (  0 == strcmp( argv[3], "CRRRS_HEIPPASYNCSR_RES" ) ) {
			DdToptwo_RESET_CRRRS_HEIPPASYNCSR();
			Ddim_Print(("It set CRRRS_HEIPPASYNCSR_RES select.\n"));
			Ddim_Print(("IO_CHIPTOP.CRRRS.bit.HEIPPASYNCSR=%d\n", IO_CHIPTOP.CRRRS.bit.HEIPPASYNCSR));
		}else if (  0 == strcmp( argv[3], "CRRRS_HEIPPSYNCSR_CLR" ) ) {
			DdToptwo_CLEAR_CRRRS_HEIPPSYNCSR();
			Ddim_Print(("It set CRRRS_HEIPPSYNCSR_CLR select.\n"));
			Ddim_Print(("IO_CHIPTOP.CRRRS.bit.HEIPPSYNCSR=%d\n", IO_CHIPTOP.CRRRS.bit.HEIPPSYNCSR));
		}else if (  0 == strcmp( argv[3], "CRRRS_HEIPPSYNCSR_RES" ) ) {
			DdToptwo_RESET_CRRRS_HEIPPSYNCSR();
			Ddim_Print(("It set CRRRS_HEIPPSYNCSR_RES select.\n"));
			Ddim_Print(("IO_CHIPTOP.CRRRS.bit.HEIPPSYNCSR=%d\n", IO_CHIPTOP.CRRRS.bit.HEIPPSYNCSR));
		}else if (  0 == strcmp( argv[3], "CRRRS_HEVDFSR_CLR" ) ) {
			DdToptwo_CLEAR_CRRRS_HEVDFSR();
			Ddim_Print(("It set CRRRS_HEVDFSR_CLR select.\n"));
			Ddim_Print(("IO_CHIPTOP.CRRRS.bit.HEVDFSR=%d\n", IO_CHIPTOP.CRRRS.bit.HEVDFSR));
		}else if (  0 == strcmp( argv[3], "CRRRS_HEVDFSR_RES" ) ) {
			DdToptwo_RESET_CRRRS_HEVDFSR();
			Ddim_Print(("It set CRRRS_HEVDFSR_RES select.\n"));
			Ddim_Print(("IO_CHIPTOP.CRRRS.bit.HEVDFSR=%d\n", IO_CHIPTOP.CRRRS.bit.HEVDFSR));
		}
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
		else if ( 0 == strcmp( argv[3], "CRRRS_HEPXFSR_CLR" ) ) {
			DdToptwo_CLEAR_CRRRS_HEPXFSR();
			Ddim_Print(("It set CRRRS_HEPXFSR_CLR select.\n"));
			Ddim_Print(("IO_CHIPTOP.CRRRS.bit.HEPXFSR=%d\n", IO_CHIPTOP.CRRRS.bit.HEPXFSR));
		}else if (  0 == strcmp( argv[3], "CRRRS_HEPXFSR_RES" ) ) {
			DdToptwo_RESET_CRRRS_HEPXFSR();
			Ddim_Print(("It set CRRRS_HEPXFSR_RES select.\n"));
			Ddim_Print(("IO_CHIPTOP.CRRRS.bit.HEPXFSR=%d\n", IO_CHIPTOP.CRRRS.bit.HEPXFSR));
		}
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
		else if ( 0 == strcmp( argv[3], "CRRRS_HEVENCSR_CLR" ) ) {
			DdToptwo_CLEAR_CRRRS_HEVENCSR();
			Ddim_Print(("It set CRRRS_HEVENCSR_CLR select.\n"));
			Ddim_Print(("IO_CHIPTOP.CRRRS.bit.HEVENCSR=%d\n", IO_CHIPTOP.CRRRS.bit.HEVENCSR));
		}else if (  0 == strcmp( argv[3], "CRRRS_HEVENCSR_RES" ) ) {
			DdToptwo_RESET_CRRRS_HEVENCSR();
			Ddim_Print(("It set CRRRS_HEVENCSR_RES select.\n"));
			Ddim_Print(("IO_CHIPTOP.CRRRS.bit.HEVENCSR=%d\n", IO_CHIPTOP.CRRRS.bit.HEVENCSR));
		}
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
		else if ( 0 == strcmp( argv[3], "CRRRS_DSPSR_CLR" ) ) {
			DdToptwo_CLEAR_CRRRS_DSPSR();
			Ddim_Print(("It set CRRRS_DSPSR_CLR select.\n"));
			Ddim_Print(("IO_CHIPTOP.CRRRS.bit.DSPSR=%d\n", IO_CHIPTOP.CRRRS.bit.DSPSR));
		}else if (  0 == strcmp( argv[3], "CRRRS_DSPSR_RES" ) ) {
			DdToptwo_RESET_CRRRS_DSPSR();
			Ddim_Print(("It set CRRRS_DSPSR_RES select.\n"));
			Ddim_Print(("IO_CHIPTOP.CRRRS.bit.DSPSR=%d\n", IO_CHIPTOP.CRRRS.bit.DSPSR));
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
void ct_reset_control(CtReset *self)
{
    if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "get" ) ) {
         ctGetResetCtrl(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "set" ) ) {
         ctSetResetCtrl(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else {
        Ddim_Print(("please check 2nd parameter!!\n"));
    }
}

CtReset* ct_reset_new(void) 
{
    CtReset *self = k_object_new_with_private(CT_TYPE_RESET, sizeof(CtResetPrivate));
    return self;
}
