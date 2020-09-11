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
#include "ctgetctrl.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtGetCtrl, ct_get_ctrl);
#define CT_GET_CTRL_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtGetCtrlPrivate,CT_TYPE_GET_CTRL))

struct _CtGetCtrlPrivate
{
	kchar* vaule;
};
/****************
* DECLS
*/
static void 			ct_get_ctrl_constructor(CtGetCtrl *self);
static void 			ct_get_ctrl_destructor(CtGetCtrl *self);
static void 			ctGetCtrlPersel1(void);
static void 			ctGetCtrlPersel2(void);
static void 			ctGetCtrlPersel3(void);
static void 			ctGetCtrlPersel4(void);
static void 			ctGetCtrlMsel(void);
static void 			ctGetCtrlDbcnt1(void);
static void 			ctGetCtrlDbcnt2(void);
static void 			ctGetCtrlDbcnt3(void);
static void 			ctGetCtrlDbcnt5(void);
static void 			ctGetCtrlPudcnt(void);
/****************
* IMPL
*/
static void ct_get_ctrl_constructor(CtGetCtrl *self) 
{
	CtGetCtrlPrivate *priv = CT_GET_CTRL_GET_PRIVATE(self);
    priv->vaule = NULL;
}

static void ct_get_ctrl_destructor(CtGetCtrl *self) 
{
	CtGetCtrlPrivate *priv = CT_GET_CTRL_GET_PRIVATE(self);
	if(priv->vaule != NULL)
	{
		k_free(priv->vaule);
		priv->vaule = NULL;
	}
}

static void ctGetCtrlPersel1(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PERSEL1.bit.I2C0CNT	=	2;
	IO_CHIPTOP.PERSEL1.bit.SDANC0	=	1;
	IO_CHIPTOP.PERSEL1.bit.SCLNC0	=	1;
	IO_CHIPTOP.PERSEL1.bit.I2C1CNT	=	2;
	IO_CHIPTOP.PERSEL1.bit.SDANC1	=	1;
	IO_CHIPTOP.PERSEL1.bit.SCLNC1	=	1;
	IO_CHIPTOP.PERSEL1.bit.I2C2CNT	=	2;
	IO_CHIPTOP.PERSEL1.bit.SDANC2	=	1;
	IO_CHIPTOP.PERSEL1.bit.SCLNC2	=	1;
	IO_CHIPTOP.PERSEL1.bit.DVWT2	=	1;
	IO_CHIPTOP.PERSEL1.bit.DHWT3	=	1;
	IO_CHIPTOP.PERSEL1.bit.AU0DO0C	=	1;
	IO_CHIPTOP.PERSEL1.bit.AU0DO1C	=	1;
	IO_CHIPTOP.PERSEL1.bit.AU1DOC	=	1;
	IO_CHIPTOP.PERSEL1.bit.AU0MCC	=	1;
	IO_CHIPTOP.PERSEL1.bit.AU1MCC	=	1;
	IO_CHIPTOP.PERSEL1.bit.RLSEL3	=	1;
	IO_CHIPTOP.PERSEL1.bit.RLSEL4	=	1;
	IO_CHIPTOP.PERSEL1.bit.RLSEL5	=	1;
	IO_CHIPTOP.PERSEL1.bit.INTVDSEL	=	1;
#endif

	Ddim_Print(("PERSEL1_I2C0CNT	= %d\n", DdTopthree_GET_PERSEL1_I2C0CNT()));
	Ddim_Print(("PERSEL1_SDANC0	    = %d\n", DdTopthree_GET_PERSEL1_SDANC0()));
	Ddim_Print(("PERSEL1_SCLNC0	    = %d\n", DdTopthree_GET_PERSEL1_SCLNC0()));
	Ddim_Print(("PERSEL1_I2C1CNT	= %d\n", DdTopthree_GET_PERSEL1_I2C1CNT()));
	Ddim_Print(("PERSEL1_SDANC1	    = %d\n", DdTopthree_GET_PERSEL1_SDANC1()));
	Ddim_Print(("PERSEL1_SCLNC1	    = %d\n", DdTopthree_GET_PERSEL1_SCLNC1()));
	Ddim_Print(("PERSEL1_I2C2CNT	= %d\n", DdTopthree_GET_PERSEL1_I2C2CNT()));
	Ddim_Print(("PERSEL1_SDANC2	    = %d\n", DdTopthree_GET_PERSEL1_SDANC2()));
	Ddim_Print(("PERSEL1_SCLNC2	    = %d\n", DdTopthree_GET_PERSEL1_SCLNC2()));
	Ddim_Print(("PERSEL1_DVWT2	    = %d\n", DdTopthree_GET_PERSEL1_DVWT2()));
	Ddim_Print(("PERSEL1_DHWT3	    = %d\n", DdTopthree_GET_PERSEL1_DHWT3()));
	Ddim_Print(("PERSEL1_AU0DO0C	= %d\n", DdTopthree_GET_PERSEL1_AU0DO0C()));
	Ddim_Print(("PERSEL1_AU0DO1C	= %d\n", DdTopthree_GET_PERSEL1_AU0DO1C()));
	Ddim_Print(("PERSEL1_AU1DOC	    = %d\n", DdTopthree_GET_PERSEL1_AU1DOC()));
	Ddim_Print(("PERSEL1_AU0MCC	    = %d\n", DdTopthree_GET_PERSEL1_AU0MCC()));
	Ddim_Print(("PERSEL1_AU1MCC	    = %d\n", DdTopthree_GET_PERSEL1_AU1MCC()));
	Ddim_Print(("PERSEL1_RLSEL3	    = %d\n", DdTopothree_GET_PERSEL1_RLSEL3()));
	Ddim_Print(("PERSEL1_RLSEL4	    = %d\n", DdTopothree_GET_PERSEL1_RLSEL4()));
	Ddim_Print(("PERSEL1_RLSEL5	    = %d\n", DdTopothree_GET_PERSEL1_RLSEL5()));
	Ddim_Print(("PERSEL1_INTVDSEL	= %d\n", DdTopothree_GET_PERSEL1_INTVDSEL()));
}

static void ctGetCtrlPersel2(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PERSEL2.bit.UDCTRG	=	1;
	IO_CHIPTOP.PERSEL2.bit.UDC0AM	=	1;
	IO_CHIPTOP.PERSEL2.bit.UDC0BM	=	1;
	IO_CHIPTOP.PERSEL2.bit.UDC1AM	=	1;
	IO_CHIPTOP.PERSEL2.bit.UDC1BM	=	1;
	IO_CHIPTOP.PERSEL2.bit.UDC2AM	=	1;
	IO_CHIPTOP.PERSEL2.bit.UDC2BM	=	1;
	IO_CHIPTOP.PERSEL2.bit.UDC3AM	=	1;
	IO_CHIPTOP.PERSEL2.bit.UDC3BM	=	1;
	IO_CHIPTOP.PERSEL2.bit.UDC4AM	=	1;
	IO_CHIPTOP.PERSEL2.bit.UDC4BM	=	1;
	IO_CHIPTOP.PERSEL2.bit.UDC5AM	=	1;
	IO_CHIPTOP.PERSEL2.bit.UDC5BM	=	1;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	IO_CHIPTOP.PERSEL2.bit.SPIMSEN0	=	1;
	IO_CHIPTOP.PERSEL2.bit.SPIMSEN1	=	1;
	IO_CHIPTOP.PERSEL2.bit.SPIMSEN2	=	1;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
#endif

	Ddim_Print(("PERSEL2_UDCTRG		= %d\n", DdTopothree_GET_PERSEL2_UDCTRG()));
	Ddim_Print(("PERSEL2_UDC0AM	    = %d\n", DdTopothree_GET_PERSEL2_UDC0AM()));
	Ddim_Print(("PERSEL2_UDC0BM	    = %d\n", DdTopothree_GET_PERSEL2_UDC0BM()));
	Ddim_Print(("PERSEL2_UDC1AM		= %d\n", DdTopothree_GET_PERSEL2_UDC1AM()));
	Ddim_Print(("PERSEL2_UDC1BM	    = %d\n", DdTopothree_GET_PERSEL2_UDC1BM()));
	Ddim_Print(("PERSEL2_UDC2AM	    = %d\n", DdTopothree_GET_PERSEL2_UDC2AM()));
	Ddim_Print(("PERSEL2_UDC2BM		= %d\n", DdTopothree_GET_PERSEL2_UDC2BM()));
	Ddim_Print(("PERSEL2_UDC3AM	    = %d\n", DdTopothree_GET_PERSEL2_UDC3AM()));
	Ddim_Print(("PERSEL2_UDC3BM	    = %d\n", DdTopothree_GET_PERSEL2_UDC3BM()));
	Ddim_Print(("PERSEL2_UDC4AM	    = %d\n", DdTopothree_GET_PERSEL2_UDC4AM()));
	Ddim_Print(("PERSEL2_UDC4BM	    = %d\n", DdTopothree_GET_PERSEL2_UDC4BM()));
	Ddim_Print(("PERSEL2_UDC5AM		= %d\n", DdTopothree_GET_PERSEL2_UDC5AM()));
	Ddim_Print(("PERSEL2_UDC5BM		= %d\n", DdTopothree_GET_PERSEL2_UDC5BM()));
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	Ddim_Print(("PERSEL2_SPIMSEN0		= %d\n", DdTopothree_GET_PERSEL2_SPIMSEN0()));
	Ddim_Print(("PERSEL2_SPIMSEN1		= %d\n", DdTopothree_GET_PERSEL2_SPIMSEN1()));
	Ddim_Print(("PERSEL2_SPIMSEN2		= %d\n", DdTopothree_GET_PERSEL2_SPIMSEN2()));
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
}

static void ctGetCtrlPersel3(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PERSEL3.bit.AU1WPPS	   = 1;
	IO_CHIPTOP.PERSEL3.bit.AU0WP11 	   = 1;
	IO_CHIPTOP.PERSEL3.bit.SNH2WP04    = 1;
	IO_CHIPTOP.PERSEL3.bit.SNV2WP05    = 1;
	IO_CHIPTOP.PERSEL3.bit.SNA2WP06    = 1;
	IO_CHIPTOP.PERSEL3.bit.SNH3WP07    = 1;
	IO_CHIPTOP.PERSEL3.bit.SNV3WP08    = 1;
	IO_CHIPTOP.PERSEL3.bit.SNA3WP09    = 1;
	IO_CHIPTOP.PERSEL3.bit.U1VBSOU5    = 1;
	IO_CHIPTOP.PERSEL3.bit.U2VBSOU6    = 1;
	IO_CHIPTOP.PERSEL3.bit.U2IDWP14    = 1;
	IO_CHIPTOP.PERSEL3.bit.PRT1SOU3    = 1;
	IO_CHIPTOP.PERSEL3.bit.PXW0WP12    = 1;
	IO_CHIPTOP.PERSEL3.bit.PXW1SOU7    = 1;
	IO_CHIPTOP.PERSEL3.bit.PXC0SCK7    = 1;
	IO_CHIPTOP.PERSEL3.bit.PXC1WP15    = 1;
	IO_CHIPTOP.PERSEL3.bit.SCK4WP13    = 1;
	IO_CHIPTOP.PERSEL3.bit.S3LSOU5WP14 = 1;
	IO_CHIPTOP.PERSEL3.bit.S3SWP15     = 1;
	IO_CHIPTOP.PERSEL3.bit.RTS1SCK2    = 1;
	IO_CHIPTOP.PERSEL3.bit.U1IDWP13    = 1;
	IO_CHIPTOP.PERSEL3.bit.PRT0SCK3    = 1;
#endif

	Ddim_Print(("PERSEL3_AU1WPPS     = %d\n", DdTopothree_GET_PERSEL3_AU1WPPS()));
	Ddim_Print(("PERSEL3_AU0WP11     = %d\n", DdTopothree_GET_PERSEL3_AU0WP11()));
	Ddim_Print(("PERSEL3_SNH2WP04    = %d\n", DdTopothree_GET_PERSEL3_SNH2WP04()));
	Ddim_Print(("PERSEL3_SNV2WP05    = %d\n", DdTopothree_GET_PERSEL3_SNV2WP05()));
	Ddim_Print(("PERSEL3_SNA2WP06    = %d\n", DdTopothree_GET_PERSEL3_SNA2WP06()));
	Ddim_Print(("PERSEL3_SNH3WP07    = %d\n", DdTopothree_GET_PERSEL3_SNH3WP07()));
	Ddim_Print(("PERSEL3_SNV3WP08    = %d\n", DdTopothree_GET_PERSEL3_SNV3WP08()));
	Ddim_Print(("PERSEL3_SNA3WP09    = %d\n", DdTopothree_GET_PERSEL3_SNA3WP09()));
	Ddim_Print(("PERSEL3_U1VBSOU5    = %d\n", DdTopothree_GET_PERSEL3_U1VBSOU5()));
	Ddim_Print(("PERSEL3_U2VBSOU6    = %d\n", DdTopothree_GET_PERSEL3_U2VBSOU6()));
	Ddim_Print(("PERSEL3_U2IDWP14    = %d\n", DdTopothree_GET_PERSEL3_U2IDWP14()));
	Ddim_Print(("PERSEL3_PRT1SOU3    = %d\n", DdTopothree_GET_PERSEL3_PRT1SOU3()));
	Ddim_Print(("PERSEL3_PXW0WP12    = %d\n", DdTopothree_GET_PERSEL3_PXW0WP12()));
	Ddim_Print(("PERSEL3_PXW1SOU7    = %d\n", DdTopothree_GET_PERSEL3_PXW1SOU7()));
	Ddim_Print(("PERSEL3_PXC0SCK7    = %d\n", DdTopothree_GET_PERSEL3_PXC0SCK7()));
	Ddim_Print(("PERSEL3_PXC1WP15    = %d\n", DdTopone_Get_PERSEL3_PXC1WP15()));
	Ddim_Print(("PERSEL3_SCK4WP13    = %d\n", DdTopothree_GET_PERSEL3_SCK4WP13()));
	Ddim_Print(("PERSEL3_S3LSOU5WP14 = %d\n", DdTopothree_GET_PERSEL3_S3LSOU5WP14()));
	Ddim_Print(("PERSEL3_S3SWP15     = %d\n", DdTopothree_GET_PERSEL3_S3SWP15()));
	Ddim_Print(("PERSEL3_RTS1SCK2    = %d\n", DdTopothree_GET_PERSEL3_RTS1SCK2()));
	Ddim_Print(("PERSEL3_U1IDWP13    = %d\n", DdTopthree_GET_PERSEL3_U1IDWP13()));
	Ddim_Print(("PERSEL3_PRT0SCK3    = %d\n", DdTopthree_GET_PERSEL3_PRT0SCK3()));
}

static void ctGetCtrlPersel4(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PERSEL4.bit.EI22UD0A	   = 1;
	IO_CHIPTOP.PERSEL4.bit.EI23UD0B    = 1;
	IO_CHIPTOP.PERSEL4.bit.EI24UD1A    = 1;
	IO_CHIPTOP.PERSEL4.bit.EI25UD1B    = 1;
	IO_CHIPTOP.PERSEL4.bit.EI26UD2A    = 1;
	IO_CHIPTOP.PERSEL4.bit.EI27UD2B    = 1;
	IO_CHIPTOP.PERSEL4.bit.EI28UD3A    = 1;
	IO_CHIPTOP.PERSEL4.bit.EI29UD3B    = 1;
	IO_CHIPTOP.PERSEL4.bit.EI30UD4A    = 1;
	IO_CHIPTOP.PERSEL4.bit.EI31UD4B    = 1;
	IO_CHIPTOP.PERSEL4.bit.SD3CDXS     = 1;
	IO_CHIPTOP.PERSEL4.bit.SD3WPS      = 1;
	IO_CHIPTOP.PERSEL4.bit.U1OCDXS     = 1;
	IO_CHIPTOP.PERSEL4.bit.U1IDDIGS    = 1;
	IO_CHIPTOP.PERSEL4.bit.U2OCDXS     = 1;
	IO_CHIPTOP.PERSEL4.bit.U2IDDIGS    = 1;
#endif

	Ddim_Print(("PERSEL4_EI22UD0A    = %d\n", DdTopthree_GET_PERSEL4_EI22UD0A()));
	Ddim_Print(("PERSEL4_EI23UD0B    = %d\n", DdTopthree_GET_PERSEL4_EI23UD0B()));
	Ddim_Print(("PERSEL4_EI24UD1A    = %d\n", DdTopthree_GET_PERSEL4_EI24UD1A()));
	Ddim_Print(("PERSEL4_EI25UD1B    = %d\n", DdTopthree_GET_PERSEL4_EI25UD1B()));
	Ddim_Print(("PERSEL4_EI26UD2A    = %d\n", DdTopthree_GET_PERSEL4_EI26UD2A()));
	Ddim_Print(("PERSEL4_EI27UD2B    = %d\n", DdTopthree_GET_PERSEL4_EI27UD2B()));
	Ddim_Print(("PERSEL4_EI28UD3A    = %d\n", DdTopthree_GET_PERSEL4_EI28UD3A()));
	Ddim_Print(("PERSEL4_EI29UD3B    = %d\n", DdTopthree_GET_PERSEL4_EI29UD3B()));
	Ddim_Print(("PERSEL4_EI30UD4A    = %d\n", DdTopthree_GET_PERSEL4_EI30UD4A()));
	Ddim_Print(("PERSEL4_EI31UD4B    = %d\n", DdTopthree_GET_PERSEL4_EI31UD4B()));
	Ddim_Print(("PERSEL4_SD3CDXS     = %d\n", DdTopthree_GET_PERSEL4_SD3CDXS()));
	Ddim_Print(("PERSEL4_SD3WPS      = %d\n", DdTopthree_GET_PERSEL4_SD3WPS()));
	Ddim_Print(("PERSEL4_U1OCDXS     = %d\n", DdTopthree_GET_PERSEL4_U1OCDXS()));
	Ddim_Print(("PERSEL4_U1IDDIGS    = %d\n", DdTopthree_GET_PERSEL4_U1IDDIGS()));
	Ddim_Print(("PERSEL4_U2OCDXS     = %d\n", DdTopthree_GET_PERSEL4_U2OCDXS()));
	Ddim_Print(("PERSEL4_U2IDDIGS    = %d\n", DdTopthree_GET_PERSEL4_U2IDDIGS()));
}

static void ctGetCtrlMsel(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.MSELC.bit.MSEL = 7;
#endif

	Ddim_Print(("MSELC_MSEL  = %d\n", DdTopthree_GET_MSELC_MSEL()));
}

static void ctGetCtrlDbcnt1(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.DBCNT1.bit.T07DC	= 1;
	IO_CHIPTOP.DBCNT1.bit.T08DC	= 1;
	IO_CHIPTOP.DBCNT1.bit.T09DC	= 1;
	IO_CHIPTOP.DBCNT1.bit.T10DC	= 1;
	IO_CHIPTOP.DBCNT1.bit.T11DC	= 1;
	IO_CHIPTOP.DBCNT1.bit.T12DC	= 1;
	IO_CHIPTOP.DBCNT1.bit.T13DC	= 1;
	IO_CHIPTOP.DBCNT1.bit.T14DC	= 1;
	IO_CHIPTOP.DBCNT1.bit.T15DC	= 1;
#endif

	Ddim_Print(("DBCNT1_T07DC	= %d\n", DdTopthree_GET_DBCNT1_T07DC()));
	Ddim_Print(("DBCNT1_T08DC	= %d\n", DdTopthree_GET_DBCNT1_T08DC()));
	Ddim_Print(("DBCNT1_T09DC	= %d\n", DdTopthree_GET_DBCNT1_T09DC()));
	Ddim_Print(("DBCNT1_T10DC	= %d\n", DdTopthree_GET_DBCNT1_T10DC()));
	Ddim_Print(("DBCNT1_T11DC	= %d\n", DdTopthree_GET_DBCNT1_T11DC()));
	Ddim_Print(("DBCNT1_T12DC	= %d\n", DdTopthree_GET_DBCNT1_T12DC()));
	Ddim_Print(("DBCNT1_T13DC	= %d\n", DdTopthree_GET_DBCNT1_T13DC()));
	Ddim_Print(("DBCNT1_T14DC	= %d\n", DdTopthree_GET_DBCNT1_T14DC()));
	Ddim_Print(("DBCNT1_T15DC	= %d\n", DdTopthree_GET_DBCNT1_T15DC()));
}

static void ctGetCtrlDbcnt2(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.DBCNT2.bit.T16DC	= 1;
	IO_CHIPTOP.DBCNT2.bit.T17DC	= 1;
	IO_CHIPTOP.DBCNT2.bit.T18DC	= 1;
	IO_CHIPTOP.DBCNT2.bit.T19DC	= 1;
	IO_CHIPTOP.DBCNT2.bit.T20DC	= 1;
	IO_CHIPTOP.DBCNT2.bit.T21DC	= 1;
	IO_CHIPTOP.DBCNT2.bit.T22DC	= 1;
	IO_CHIPTOP.DBCNT2.bit.T23DC	= 1;
	IO_CHIPTOP.DBCNT2.bit.T24DC	= 1;
	IO_CHIPTOP.DBCNT2.bit.T25DC	= 1;
	IO_CHIPTOP.DBCNT2.bit.T26DC	= 1;
	IO_CHIPTOP.DBCNT2.bit.T27DC	= 1;
	IO_CHIPTOP.DBCNT2.bit.T28DC	= 1;
	IO_CHIPTOP.DBCNT2.bit.T29DC	= 1;
	IO_CHIPTOP.DBCNT2.bit.T30DC	= 1;
	IO_CHIPTOP.DBCNT2.bit.T31DC	= 1;
#endif

	Ddim_Print(("DBCNT2_T16DC	= %d\n", DdTopthree_GET_DBCNT2_T16DC()));
	Ddim_Print(("DBCNT2_T17DC	= %d\n", DdTopthree_GET_DBCNT2_T17DC()));
	Ddim_Print(("DBCNT2_T18DC	= %d\n", DdTopthree_GET_DBCNT2_T18DC()));
	Ddim_Print(("DBCNT2_T19DC	= %d\n", DdTopthree_GET_DBCNT2_T19DC()));
	Ddim_Print(("DBCNT2_T20DC	= %d\n", DdTopthree_GET_DBCNT2_T20DC()));
	Ddim_Print(("DBCNT2_T21DC	= %d\n", DdTopthree_GET_DBCNT2_T21DC()));
	Ddim_Print(("DBCNT2_T22DC	= %d\n", DdTopthree_GET_DBCNT2_T22DC()));
	Ddim_Print(("DBCNT2_T23DC	= %d\n", DdTopthree_GET_DBCNT2_T23DC()));
	Ddim_Print(("DBCNT2_T24DC	= %d\n", DdTopthree_GET_DBCNT2_T24DC()));
	Ddim_Print(("DBCNT2_T25DC	= %d\n", DdTopthree_GET_DBCNT2_T25DC()));
	Ddim_Print(("DBCNT2_T26DC	= %d\n", DdTopthree_GET_DBCNT2_T26DC()));
	Ddim_Print(("DBCNT2_T27DC	= %d\n", DdTopthree_GET_DBCNT2_T27DC()));
	Ddim_Print(("DBCNT2_T28DC	= %d\n", DdTopthree_GET_DBCNT2_T28DC()));
	Ddim_Print(("DBCNT2_T29DC	= %d\n", DdTopthree_GET_DBCNT2_T29DC()));
	Ddim_Print(("DBCNT2_T30DC	= %d\n", DdTopthree_GET_DBCNT2_T30DC()));
	Ddim_Print(("DBCNT2_T31DC	= %d\n", DdTopthree_GET_DBCNT2_T31DC()));
}

static void ctGetCtrlDbcnt3(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.DBCNT3.bit.T32DC	= 1;
	IO_CHIPTOP.DBCNT3.bit.T33DC	= 1;
	IO_CHIPTOP.DBCNT3.bit.T34DC	= 1;
	IO_CHIPTOP.DBCNT3.bit.T35DC	= 1;
	IO_CHIPTOP.DBCNT3.bit.T36DC	= 1;
	IO_CHIPTOP.DBCNT3.bit.T37DC	= 1;
	IO_CHIPTOP.DBCNT3.bit.T38DC	= 1;
	IO_CHIPTOP.DBCNT3.bit.T39DC	= 1;
	IO_CHIPTOP.DBCNT3.bit.T40DC	= 1;
	IO_CHIPTOP.DBCNT3.bit.T41DC	= 1;
	IO_CHIPTOP.DBCNT3.bit.T42DC	= 1;
	IO_CHIPTOP.DBCNT3.bit.T43DC	= 1;
	IO_CHIPTOP.DBCNT3.bit.T44DC	= 1;
	IO_CHIPTOP.DBCNT3.bit.T45DC	= 1;
	IO_CHIPTOP.DBCNT3.bit.T46DC	= 1;
	IO_CHIPTOP.DBCNT3.bit.T47DC	= 1;
#endif

	Ddim_Print(("DBCNT3_T32DC	= %d\n", DdTopthree_GET_DBCNT3_T32DC()));
	Ddim_Print(("DBCNT3_T33DC	= %d\n", DdTopthree_GET_DBCNT3_T33DC()));
	Ddim_Print(("DBCNT3_T34DC	= %d\n", DdTopthree_GET_DBCNT3_T34DC()));
	Ddim_Print(("DBCNT3_T35DC	= %d\n", DdTopthree_GET_DBCNT3_T35DC()));
	Ddim_Print(("DBCNT3_T36DC	= %d\n", DdTopthree_GET_DBCNT3_T36DC()));
	Ddim_Print(("DBCNT3_T37DC	= %d\n", DdTopthree_GET_DBCNT3_T37DC()));
	Ddim_Print(("DBCNT3_T38DC	= %d\n", DdTopthree_GET_DBCNT3_T38DC()));
	Ddim_Print(("DBCNT3_T39DC	= %d\n", DdTopthree_GET_DBCNT3_T39DC()));
	Ddim_Print(("DBCNT3_T40DC	= %d\n", DdTopthree_GET_DBCNT3_T40DC()));
	Ddim_Print(("DBCNT3_T41DC	= %d\n", DdTopthree_GET_DBCNT3_T41DC()));
	Ddim_Print(("DBCNT3_T42DC	= %d\n", DdTopthree_GET_DBCNT3_T42DC()));
	Ddim_Print(("DBCNT3_T43DC	= %d\n", DdTopthree_GET_DBCNT3_T43DC()));
	Ddim_Print(("DBCNT3_T44DC	= %d\n", DdTopthree_GET_DBCNT3_T44DC()));
	Ddim_Print(("DBCNT3_T45DC	= %d\n", DdTopthree_GET_DBCNT3_T45DC()));
	Ddim_Print(("DBCNT3_T46DC	= %d\n", DdTopthree_GET_DBCNT3_T46DC()));
	Ddim_Print(("DBCNT3_T47DC	= %d\n", DdTopthree_GET_DBCNT3_T47DC()));
}

static void ctGetCtrlDbcnt4(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.DBCNT4.bit.T48DC	= 1;
	IO_CHIPTOP.DBCNT4.bit.T49DC	= 1;
	IO_CHIPTOP.DBCNT4.bit.T50DC	= 1;
	IO_CHIPTOP.DBCNT4.bit.T51DC	= 1;
	IO_CHIPTOP.DBCNT4.bit.T52DC	= 1;
	IO_CHIPTOP.DBCNT4.bit.T53DC	= 1;
	IO_CHIPTOP.DBCNT4.bit.T54DC	= 1;
	IO_CHIPTOP.DBCNT4.bit.T55DC	= 1;
	IO_CHIPTOP.DBCNT4.bit.T56DC	= 1;
	IO_CHIPTOP.DBCNT4.bit.T57DC	= 1;
	IO_CHIPTOP.DBCNT4.bit.T58DC	= 1;
	IO_CHIPTOP.DBCNT4.bit.T59DC	= 1;
	IO_CHIPTOP.DBCNT4.bit.T60DC	= 1;
	IO_CHIPTOP.DBCNT4.bit.T61DC	= 1;
	IO_CHIPTOP.DBCNT4.bit.T62DC	= 1;
	IO_CHIPTOP.DBCNT4.bit.T63DC	= 1;
#endif

	Ddim_Print(("DBCNT4_T48DC	= %d\n", DdTopthree_GET_DBCNT4_T48DC()));
	Ddim_Print(("DBCNT4_T49DC	= %d\n", DdTopthree_GET_DBCNT4_T49DC()));
	Ddim_Print(("DBCNT4_T50DC	= %d\n", DdTopthree_GET_DBCNT4_T50DC()));
	Ddim_Print(("DBCNT4_T51DC	= %d\n", DdTopthree_GET_DBCNT4_T51DC()));
	Ddim_Print(("DBCNT4_T52DC	= %d\n", DdTopthree_GET_DBCNT4_T52DC()));
	Ddim_Print(("DBCNT4_T53DC	= %d\n", DdTopthree_GET_DBCNT4_T53DC()));
	Ddim_Print(("DBCNT4_T54DC	= %d\n", DdTopthree_GET_DBCNT4_T54DC()));
	Ddim_Print(("DBCNT4_T55DC	= %d\n", DdTopthree_GET_DBCNT4_T55DC()));
	Ddim_Print(("DBCNT4_T56DC	= %d\n", DdTopthree_GET_DBCNT4_T56DC()));
	Ddim_Print(("DBCNT4_T57DC	= %d\n", DdTopthree_GET_DBCNT4_T57DC()));
	Ddim_Print(("DBCNT4_T58DC	= %d\n", DdTopthree_GET_DBCNT4_T58DC()));
	Ddim_Print(("DBCNT4_T59DC	= %d\n", DdTopthree_GET_DBCNT4_T59DC()));
	Ddim_Print(("DBCNT4_T60DC	= %d\n", DdTopthree_GET_DBCNT4_T60DC()));
	Ddim_Print(("DBCNT4_T61DC	= %d\n", DdTopthree_GET_DBCNT4_T61DC()));
	Ddim_Print(("DBCNT4_T62DC	= %d\n", DdTopthree_GET_DBCNT4_T62DC()));
	Ddim_Print(("DBCNT4_T63DC	= %d\n", DdTopthree_GET_DBCNT4_T63DC()));
}

static void ctGetCtrlDbcnt5(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.DBCNT5.bit.T64DC	= 1;
	IO_CHIPTOP.DBCNT5.bit.T65DC	= 1;
	IO_CHIPTOP.DBCNT5.bit.T66DC	= 1;
#endif

	Ddim_Print(("DBCNT5_T64DC  = %d\n", DdTopthree_GET_DBCNT5_T64DC()));
	Ddim_Print(("DBCNT5_T65DC  = %d\n", DdTopthree_GET_DBCNT5_T65DC()));
	Ddim_Print(("DBCNT5_T66DC  = %d\n", DdTopthree_GET_DBCNT5_T66DC()));
}

static void ctGetCtrlPudcnt(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PUDCNT.bit.EMMCNICS	 = 1;
	IO_CHIPTOP.PUDCNT.bit.EMDATPUE	 = 1;
	IO_CHIPTOP.PUDCNT.bit.EMCMDPUE	 = 1;
	IO_CHIPTOP.PUDCNT.bit.EMDSPDE	 = 1;
	IO_CHIPTOP.PUDCNT.bit.NFDATPUE	 = 1;
	IO_CHIPTOP.PUDCNT.bit.NFRBXPUE	 = 1;
	IO_CHIPTOP.PUDCNT.bit.NFDQSPUE	 = 1;
	IO_CHIPTOP.PUDCNT.bit.SP1MISOPE	 = 1;
	IO_CHIPTOP.PUDCNT.bit.SP1MOSIPE	 = 1;
	IO_CHIPTOP.PUDCNT.bit.SP1SCKPE	 = 1;
	IO_CHIPTOP.PUDCNT.bit.SP1CS0PE	 = 1;
	IO_CHIPTOP.PUDCNT.bit.SP1MISOUDC = 1;
	IO_CHIPTOP.PUDCNT.bit.SP1MOSIUDC = 1;
	IO_CHIPTOP.PUDCNT.bit.SP1SCKUDC	 = 1;
	IO_CHIPTOP.PUDCNT.bit.SP1CS0UDC	 = 1;
#endif

	Ddim_Print(("PUDCNT_EMMCNICS   = %d\n", DdTopthree_GET_PUDCNT_EMMCNICS()));
	Ddim_Print(("PUDCNT_EMDATPUE   = %d\n", DdTopthree_GET_PUDCNT_EMDATPUE()));
	Ddim_Print(("PUDCNT_EMCMDPUE   = %d\n", DdTopthree_GET_PUDCNT_EMCMDPUE()));
	Ddim_Print(("PUDCNT_EMDSPDE    = %d\n", DdTopthree_GET_PUDCNT_EMDSPDE()));
	Ddim_Print(("PUDCNT_NFDATPUE   = %d\n", DdTopthree_GET_PUDCNT_NFDATPUE()));
	Ddim_Print(("PUDCNT_NFRBXPUE   = %d\n", DdTopthree_GET_PUDCNT_NFRBXPUE()));
	Ddim_Print(("PUDCNT_NFDQSPUE   = %d\n", DdTopthree_GET_PUDCNT_NFDQSPUE()));
	Ddim_Print(("PUDCNT_SP1MISOPE  = %d\n", DdTopthree_GET_PUDCNT_SP1MISOPE()));
	Ddim_Print(("PUDCNT_SP1MOSIPE  = %d\n", DdTopthree_GET_PUDCNT_SP1MOSIPE()));
	Ddim_Print(("PUDCNT_SP1SCKPE   = %d\n", DdTopthree_GET_PUDCNT_SP1SCKPE()));
	Ddim_Print(("PUDCNT_SP1CS0PE   = %d\n", DdTopthree_GET_PUDCNT_SP1CS0PE()));
	Ddim_Print(("PUDCNT_SP1MISOUDC = %d\n", DdTopthree_GET_PUDCNT_SP1MISOUDC()));
	Ddim_Print(("PUDCNT_SP1MOSIUDC = %d\n", DdTopthree_GET_PUDCNT_SP1MOSIUDC()));
	Ddim_Print(("PUDCNT_SP1SCKUDC  = %d\n", DdTopthree_GET_PUDCNT_SP1SCKUDC()));
	Ddim_Print(("PUDCNT_SP1CS0UDC  = %d\n", DdTopthree_GET_PUDCNT_SP1CS0UDC()));
}
/****************
* PUBLIC
*/
void ct_get_ctrl_set_vaule(CtGetCtrl *self,kchar* vaule)
{
    CtGetCtrlPrivate *priv = CT_GET_CTRL_GET_PRIVATE(self);
    priv->vaule = vaule;
}

void ct_get_ctrl(CtGetCtrl *self)
{
    CtGetCtrlPrivate *priv = CT_GET_CTRL_GET_PRIVATE(self);
    if( 0 == strcmp( priv->vaule, "persel1" ) ) {
        ctGetCtrlPersel1();
    }
    else if( 0 == strcmp( priv->vaule, "persel2" ) ) {
        ctGetCtrlPersel2();
    }
    else if( 0 == strcmp( priv->vaule, "persel3" ) ) {
        ctGetCtrlPersel3();
    }
    else if( 0 == strcmp( priv->vaule, "persel4" ) ) {
        ctGetCtrlPersel4();
    }
    else if( 0 == strcmp( priv->vaule, "msel" ) ) {
        ctGetCtrlMsel();
    }
    else if( 0 == strcmp( priv->vaule, "dbcnt1" ) ) {
        ctGetCtrlDbcnt1();
    }
    else if( 0 == strcmp( priv->vaule, "dbcnt2" ) ) {
        ctGetCtrlDbcnt2();
    }
    else if( 0 == strcmp( priv->vaule, "dbcnt3" ) ) {
        ctGetCtrlDbcnt3();
    }
    else if( 0 == strcmp( priv->vaule, "dbcnt4" ) ) {
        ctGetCtrlDbcnt4();
    }
    else if( 0 == strcmp( priv->vaule, "dbcnt5" ) ) {
        ctGetCtrlDbcnt5();
    }
    else if( 0 == strcmp( priv->vaule, "pudcnt" ) ) {
        ctGetCtrlPudcnt();
    }
		
}

CtGetCtrl* ct_get_ctrl_new(void) 
{
    CtGetCtrl *self = k_object_new_with_private(CT_TYPE_GET_CTRL, sizeof(CtGetCtrlPrivate));
    return self;
}
