/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-03
*@author              :董如利
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
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
#include "ctsetctrl.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtSetCtrl, ct_set_ctrl);
#define CT_SET_CTRL_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtSetCtrlPrivate,CT_TYPE_SET_CTRL))

struct _CtSetCtrlPrivate
{
    kint a;
};
/****************
* DECLS
*/
static void 			ct_set_ctrl_constructor(CtSetCtrl *self);
static void   			ct_set_ctrl_destructor(CtSetCtrl *self);
static void  			ctSetCtrlPersel1(kint argc, kchar** argv);
static void  			ctSetCtrlPersel2(kint argc, kchar** argv);
static void  			ctSetCtrlPersel3(kint argc, kchar** argv);
static void  			ctSetCtrlPersel4(kint argc, kchar** argv);
static void  			ctSetCtrlMsel(kint argc, kchar** argv);
static void  			ctSetCtrlDbcnt1(kint argc, kchar** argv);
static void  			ctSetCtrlDbcnt2(kint argc, kchar** argv);
static void  			ctSetCtrlDbcnt3(kint argc, kchar** argv);
static void  			ctSetCtrlDbcnt4(kint argc, kchar** argv);
static void  			ctSetCtrlDbcnt5(kint argc, kchar** argv);
static void  			ctSetCtrlPudcnt(kint argc, kchar** argv);
/****************
* IMPL
*/
static void ct_set_ctrl_constructor(CtSetCtrl *self) 
{
	// CtSetCtrlPrivate *priv = CT_SET_CTRL_GET_PRIVATE(self);
}

static void   ct_set_ctrl_destructor(CtSetCtrl *self) 
{
	// CtSetCtrlPrivate *priv = CT_SET_CTRL_GET_PRIVATE(self);
}

static void  ctSetCtrlPersel1(kint argc, kchar** argv)
{
	kulong val;

	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "I2C0CNT" ) ) {
			DdTopthree_SET_PERSEL1_I2C0CNT(val);
			Ddim_Print(("It set PERSEL1_I2C0CNT select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL1.bit.I2C0CNT	=%d\n", IO_CHIPTOP.PERSEL1.bit.I2C0CNT));
		}else if (  0 == strcmp( argv[4], "SDANC0" ) ) {
			DdTopthree_SET_PERSEL1_SDANC0(val);
			Ddim_Print(("It set PERSEL1_SDANC0 select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL1.bit.SDANC0	=%d\n", IO_CHIPTOP.PERSEL1.bit.SDANC0));
		}else if (  0 == strcmp( argv[4], "SCLNC0" ) ) {
			DdTopthree_SET_PERSEL1_SCLNC0(val);
			Ddim_Print(("It set PERSEL1_SCLNC0 select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL1.bit.SCLNC0	=%d\n", IO_CHIPTOP.PERSEL1.bit.SCLNC0));
		}else if (  0 == strcmp( argv[4], "I2C1CNT" ) ) {
			DdTopthree_SET_PERSEL1_I2C1CNT(val);
			Ddim_Print(("It set PERSEL1_I2C1CNT select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL1.bit.I2C1CNT	=%d\n", IO_CHIPTOP.PERSEL1.bit.I2C1CNT));
		}else if (  0 == strcmp( argv[4], "SDANC1" ) ) {
			DdTopthree_SET_PERSEL1_SDANC1(val);
			Ddim_Print(("It set PERSEL1_SDANC1 select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL1.bit.SDANC1	=%d\n", IO_CHIPTOP.PERSEL1.bit.SDANC1));
		}else if (  0 == strcmp( argv[4], "SCLNC1" ) ) {
			DdTopthree_SET_PERSEL1_SCLNC1(val);
			Ddim_Print(("It set PERSEL1_SCLNC1 select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL1.bit.SCLNC1	=%d\n", IO_CHIPTOP.PERSEL1.bit.SCLNC1));
		}else if (  0 == strcmp( argv[4], "I2C2CNT" ) ) {
			DdTopthree_SET_PERSEL1_I2C2CNT(val);
			Ddim_Print(("It set PERSEL1_I2C2CNT select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL1.bit.I2C2CNT	=%d\n", IO_CHIPTOP.PERSEL1.bit.I2C2CNT));
		}else if (  0 == strcmp( argv[4], "SDANC2" ) ) {
			DdTopthree_SET_PERSEL1_SDANC2(val);
			Ddim_Print(("It set PERSEL1_SDANC2 select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL1.bit.SDANC2	=%d\n", IO_CHIPTOP.PERSEL1.bit.SDANC2));
		}else if (  0 == strcmp( argv[4], "SCLNC2" ) ) {
			DdTopthree_SET_PERSEL1_SCLNC2(val);
			Ddim_Print(("It set PERSEL1_SCLNC2 select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL1.bit.SCLNC2	=%d\n", IO_CHIPTOP.PERSEL1.bit.SCLNC2));
		}else if (  0 == strcmp( argv[4], "DVWT2" ) ) {
			DdTopthree_SET_PERSEL1_DVWT2(val);
			Ddim_Print(("It set PERSEL1_DVWT2 select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL1.bit.DVWT2	=%d\n", IO_CHIPTOP.PERSEL1.bit.DVWT2));
		}else if (  0 == strcmp( argv[4], "DHWT3" ) ) {
			DdTopthree_SET_PERSEL1_DHWT3(val);
			Ddim_Print(("It set PERSEL1_DHWT3 select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL1.bit.DHWT3	=%d\n", IO_CHIPTOP.PERSEL1.bit.DHWT3));
		}else if (  0 == strcmp( argv[4], "AU0DO0C" ) ) {
			DdTopthree_SET_PERSEL1_AU0DO0C(val);
			Ddim_Print(("It set PERSEL1_AU0DO0C select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL1.bit.AU0DO0C	=%d\n", IO_CHIPTOP.PERSEL1.bit.AU0DO0C));
		}else if (  0 == strcmp( argv[4], "AU0DO1C" ) ) {
			DdTopthree_SET_PERSEL1_AU0DO1C(val);
			Ddim_Print(("It set PERSEL1_AU0DO1C select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL1.bit.AU0DO1C	=%d\n", IO_CHIPTOP.PERSEL1.bit.AU0DO1C));
		}else if (  0 == strcmp( argv[4], "AU1DOC" ) ) {
			DdTopthree_SET_PERSEL1_AU1DOC(val);
			Ddim_Print(("It set PERSEL1_AU1DOC select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL1.bit.AU1DOC	=%d\n", IO_CHIPTOP.PERSEL1.bit.AU1DOC));
		}else if (  0 == strcmp( argv[4], "AU0MCC" ) ) {
			DdTopthree_SET_PERSEL1_AU0MCC(val);	
			Ddim_Print(("It set PERSEL1_AU0MCC select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL1.bit.AU0MCC	=%d\n", IO_CHIPTOP.PERSEL1.bit.AU0MCC));
		}else if (  0 == strcmp( argv[4], "AU1MCC" ) ) {
			DdTopthree_SET_PERSEL1_AU1MCC(val);
			Ddim_Print(("It set PERSEL1_AU1MCC select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL1.bit.AU1MCC	=%d\n", IO_CHIPTOP.PERSEL1.bit.AU1MCC));
		}else if (  0 == strcmp( argv[4], "RLSEL3" ) ) {
			DdTopothree_SET_PERSEL1_RLSEL3(val);
			Ddim_Print(("It set PERSEL1_RLSEL3 select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL1.bit.RLSEL3	=%d\n", IO_CHIPTOP.PERSEL1.bit.RLSEL3));
		}else if (  0 == strcmp( argv[4], "RLSEL4" ) ) {
			DdTopothree_SET_PERSEL1_RLSEL4(val);
			Ddim_Print(("It set PERSEL1_RLSEL4 select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL1.bit.RLSEL4	=%d\n", IO_CHIPTOP.PERSEL1.bit.RLSEL4));
		}else if (  0 == strcmp( argv[4], "RLSEL5" ) ) {
			DdTopothree_SET_PERSEL1_RLSEL5(val);
			Ddim_Print(("It set PERSEL1_RLSEL5 select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL1.bit.RLSEL5	=%d\n", IO_CHIPTOP.PERSEL1.bit.RLSEL5));
		}else if (  0 == strcmp( argv[4], "INTVDSEL" ) ) {
			DdTopothree_SET_PERSEL1_INTVDSEL(val);
			Ddim_Print(("It set PERSEL1_INTVDSEL select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL1.bit.INTVDSEL	=%d\n", IO_CHIPTOP.PERSEL1.bit.INTVDSEL));
		}
		else {
			Ddim_Print(("please check 3rd parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void  ctSetCtrlPersel2(kint argc, kchar** argv)
{
	kulong val;

	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "UDCTRG" ) ) {
			DdTopothree_SET_PERSEL2_UDCTRG(val);
			Ddim_Print(("It set PERSEL2_UDCTRG select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL2.bit.UDCTRG	=%d\n", IO_CHIPTOP.PERSEL2.bit.UDCTRG));
		}else if (  0 == strcmp( argv[4], "UDC0AM" ) ) {
			DdTopothree_SET_PERSEL2_UDC0AM(val);
			Ddim_Print(("It set PERSEL2_UDC0AM select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL2.bit.UDC0AM	=%d\n", IO_CHIPTOP.PERSEL2.bit.UDC0AM));
		}else if (  0 == strcmp( argv[4], "UDC0BM" ) ) {
			DdTopothree_SET_PERSEL2_UDC0BM(val);
			Ddim_Print(("It set PERSEL2_UDC0BM select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL2.bit.UDC0BM	=%d\n", IO_CHIPTOP.PERSEL2.bit.UDC0BM));
		}else if (  0 == strcmp( argv[4], "UDC1AM" ) ) {
			DdTopothree_SET_PERSEL2_UDC1AM(val);
			Ddim_Print(("It set PERSEL2_UDC1AM select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL2.bit.UDC1AM	=%d\n", IO_CHIPTOP.PERSEL2.bit.UDC1AM));
		}else if (  0 == strcmp( argv[4], "UDC1BM" ) ) {
			DdTopothree_SET_PERSEL2_UDC1BM(val);
			Ddim_Print(("It set PERSEL2_UDC1BM select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL2.bit.UDC1BM	=%d\n", IO_CHIPTOP.PERSEL2.bit.UDC1BM));
		}else if (  0 == strcmp( argv[4], "UDC2AM" ) ) {
			DdTopothree_SET_PERSEL2_UDC2AM(val);
			Ddim_Print(("It set PERSEL2_UDC2AM select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL2.bit.UDC2AM	=%d\n", IO_CHIPTOP.PERSEL2.bit.UDC2AM));
		}else if (  0 == strcmp( argv[4], "UDC2BM" ) ) {
			DdTopothree_SET_PERSEL2_UDC2BM(val);
			Ddim_Print(("It set PERSEL2_UDC2BM select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL2.bit.UDC2BM	=%d\n", IO_CHIPTOP.PERSEL2.bit.UDC2BM));
		}else if (  0 == strcmp( argv[4], "UDC3AM" ) ) {
			DdTopothree_SET_PERSEL2_UDC3AM(val);
			Ddim_Print(("It set PERSEL2_UDC3AM select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL2.bit.UDC3AM	=%d\n", IO_CHIPTOP.PERSEL2.bit.UDC3AM));
		}else if (  0 == strcmp( argv[4], "UDC3BM" ) ) {
			DdTopothree_SET_PERSEL2_UDC3BM(val);
			Ddim_Print(("It set PERSEL2_UDC3BM select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL2.bit.UDC3BM	=%d\n", IO_CHIPTOP.PERSEL2.bit.UDC3BM));
		}else if (  0 == strcmp( argv[4], "UDC4AM" ) ) {
			DdTopothree_SET_PERSEL2_UDC4AM(val);
			Ddim_Print(("It set PERSEL2_UDC4AM select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL2.bit.UDC4AM	=%d\n", IO_CHIPTOP.PERSEL2.bit.UDC4AM));
		}else if (  0 == strcmp( argv[4], "UDC4BM" ) ) {
			DdTopothree_SET_PERSEL2_UDC4BM(val);
			Ddim_Print(("It set PERSEL2_UDC4BM select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL2.bit.UDC4BM	=%d\n", IO_CHIPTOP.PERSEL2.bit.UDC4BM));
		}else if (  0 == strcmp( argv[4], "UDC5AM" ) ) {
			DdTopothree_SET_PERSEL2_UDC5AM(val);
			Ddim_Print(("It set PERSEL2_UDC5AM select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL2.bit.UDC5AM	=%d\n", IO_CHIPTOP.PERSEL2.bit.UDC5AM));
		}else if (  0 == strcmp( argv[4], "UDC5BM" ) ) {
			DdTopothree_SET_PERSEL2_UDC5BM(val);
			Ddim_Print(("It set PERSEL2_UDC5BM select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL2.bit.UDC5BM	=%d\n", IO_CHIPTOP.PERSEL2.bit.UDC5BM));
		}
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
		else if ( 0 == strcmp( argv[4], "SPIMSEN0" ) ) {
			DdTopothree_SET_PERSEL2_SPIMSEN0(val);
			Ddim_Print(("It set PERSEL2_SPIMSEN0 select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL2.bit.SPIMSEN0	=%d\n", IO_CHIPTOP.PERSEL2.bit.SPIMSEN0));
		}else if (  0 == strcmp( argv[4], "SPIMSEN1" ) ) {
			DdTopothree_SET_PERSEL2_SPIMSEN1(val);
			Ddim_Print(("It set PERSEL2_SPIMSEN1 select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL2.bit.SPIMSEN1	=%d\n", IO_CHIPTOP.PERSEL2.bit.SPIMSEN1));
		}else if (  0 == strcmp( argv[4], "SPIMSEN2" ) ) {
			DdTopothree_SET_PERSEL2_SPIMSEN2(val);
			Ddim_Print(("It set PERSEL2_SPIMSEN2 select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL2.bit.SPIMSEN2	=%d\n", IO_CHIPTOP.PERSEL2.bit.SPIMSEN2));
		}
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
		else {
			Ddim_Print(("please check 3rd parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void  ctSetCtrlPersel3(kint argc, kchar** argv)
{
	kulong val;

	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "AU1WPPS" ) ) {
			DdTopothree_SET_PERSEL3_AU1WPPS(val);
			Ddim_Print(("It set PERSEL3_AU1WPPS select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL3.bit.AU1WPPS	=%d\n", IO_CHIPTOP.PERSEL3.bit.AU1WPPS));
		}else if (  0 == strcmp( argv[4], "AU0WP11" ) ) {
			DdTopothree_SET_PERSEL3_AU0WP11(val);
			Ddim_Print(("It set PERSEL3_AU0WP11 select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL3.bit.AU0WP11	=%d\n", IO_CHIPTOP.PERSEL3.bit.AU0WP11));
		}else if (  0 == strcmp( argv[4], "SNH2WP04" ) ) {
			DdTopothree_SET_PERSEL3_SNH2WP04(val);
			Ddim_Print(("It set PERSEL3_SNH2WP04 select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL3.bit.SNH2WP04	=%d\n", IO_CHIPTOP.PERSEL3.bit.SNH2WP04));
		}else if (  0 == strcmp( argv[4], "SNV2WP05" ) ) {
			DdTopothree_SET_PERSEL3_SNV2WP05(val);
			Ddim_Print(("It set PERSEL3_SNV2WP05 select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL3.bit.SNV2WP05	=%d\n", IO_CHIPTOP.PERSEL3.bit.SNV2WP05));
		}else if (  0 == strcmp( argv[4], "SNA2WP06" ) ) {
			DdTopothree_SET_PERSEL3_SNA2WP06(val);
			Ddim_Print(("It set PERSEL3_SNA2WP06 select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL3.bit.SNA2WP06	=%d\n", IO_CHIPTOP.PERSEL3.bit.SNA2WP06));
		}else if (  0 == strcmp( argv[4], "SNH3WP07" ) ) {
			DdTopothree_SET_PERSEL3_SNH3WP07(val);
			Ddim_Print(("It set PERSEL3_SNH3WP07 select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL3.bit.SNH3WP07	=%d\n", IO_CHIPTOP.PERSEL3.bit.SNH3WP07));
		}else if (  0 == strcmp( argv[4], "SNV3WP08" ) ) {
			DdTopothree_SET_PERSEL3_SNV3WP08(val);
			Ddim_Print(("It set PERSEL3_SNV3WP08 select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL3.bit.SNV3WP08	=%d\n", IO_CHIPTOP.PERSEL3.bit.SNV3WP08));
		}else if (  0 == strcmp( argv[4], "SNA3WP09" ) ) {
			DdTopothree_SET_PERSEL3_SNA3WP09(val);
			Ddim_Print(("It set PERSEL3_SNA3WP09 select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL3.bit.SNA3WP09	=%d\n", IO_CHIPTOP.PERSEL3.bit.SNA3WP09));
		}else if (  0 == strcmp( argv[4], "U1VBSOU5" ) ) {
			DdTopothree_SET_PERSEL3_U1VBSOU5(val);
			Ddim_Print(("It set PERSEL3_U1VBSOU5 select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL3.bit.U1VBSOU5	=%d\n", IO_CHIPTOP.PERSEL3.bit.U1VBSOU5));
		}else if (  0 == strcmp( argv[4], "U2VBSOU6" ) ) {
			DdTopothree_SET_PERSEL3_U2VBSOU6(val);
			Ddim_Print(("It set PERSEL3_U2VBSOU6 select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL3.bit.U2VBSOU6	=%d\n", IO_CHIPTOP.PERSEL3.bit.U2VBSOU6));
		}else if (  0 == strcmp( argv[4], "U2IDWP14" ) ) {
			DdTopothree_SET_PERSEL3_U2IDWP14(val);
			Ddim_Print(("It set PERSEL3_U2IDWP14 select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL3.bit.U2IDWP14	=%d\n", IO_CHIPTOP.PERSEL3.bit.U2IDWP14));
		}else if (  0 == strcmp( argv[4], "PRT1SOU3" ) ) {
			DdTopothree_SET_PERSEL3_PRT1SOU3(val);
			Ddim_Print(("It set PERSEL3_PRT1SOU3 select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL3.bit.PRT1SOU3	=%d\n", IO_CHIPTOP.PERSEL3.bit.PRT1SOU3));
		}else if (  0 == strcmp( argv[4], "PXW0WP12" ) ) {
			DdTopothree_SET_PERSEL3_PXW0WP12(val);
			Ddim_Print(("It set PERSEL3_PXW0WP12 select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL3.bit.PXW0WP12	=%d\n", IO_CHIPTOP.PERSEL3.bit.PXW0WP12));
		}else if (  0 == strcmp( argv[4], "PXW1SOU7" ) ) {
			DdTopothree_SET_PERSEL3_PXW1SOU7(val);
			Ddim_Print(("It set PERSEL3_PXW1SOU7 select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL3.bit.PXW1SOU7	=%d\n", IO_CHIPTOP.PERSEL3.bit.PXW1SOU7));
		}else if (  0 == strcmp( argv[4], "PXC0SCK7" ) ) {
			DdTopothree_SET_PERSEL3_PXC0SCK7(val);
			Ddim_Print(("It set PERSEL3_PXC0SCK7 select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL3.bit.PXC0SCK7	=%d\n", IO_CHIPTOP.PERSEL3.bit.PXC0SCK7));
		}else if (  0 == strcmp( argv[4], "PXC1WP15" ) ) {
			DdTopone_Set_PERSEL3_PXC1WP15(val);
			Ddim_Print(("It set PERSEL3_PXC1WP15 select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL3.bit.PXC1WP15	=%d\n", IO_CHIPTOP.PERSEL3.bit.PXC1WP15));
		}else if (  0 == strcmp( argv[4], "SCK4WP13" ) ) {
			DdTopone_Set_PERSEL3_PXC1WP15(val);
			Ddim_Print(("It set PERSEL3_SCK4WP13 select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL3.bit.SCK4WP13	=%d\n", IO_CHIPTOP.PERSEL3.bit.SCK4WP13));
		}else if (  0 == strcmp( argv[4], "S3LSOU5WP14" ) ) {
			DdTopothree_SET_PERSEL3_S3LSOU5WP14(val);
			Ddim_Print(("It set PERSEL3_S3LSOU5WP14 select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL3.bit.S3LSOU5WP14	=%d\n", IO_CHIPTOP.PERSEL3.bit.S3LSOU5WP14));
		}else if (  0 == strcmp( argv[4], "S3SWP15" ) ) {
			DdTopothree_SET_PERSEL3_S3SWP15(val);
			Ddim_Print(("It set PERSEL3_S3SWP15 select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL3.bit.S3SWP15	=%d\n", IO_CHIPTOP.PERSEL3.bit.S3SWP15));
		}else if (  0 == strcmp( argv[4], "RTS1SCK2" ) ) {
			DdTopthree_SET_PERSEL3_RTS1SCK2(val);
			Ddim_Print(("It set PERSEL3_RTS1SCK2 select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL3.bit.RTS1SCK2	=%d\n", IO_CHIPTOP.PERSEL3.bit.RTS1SCK2));
		}else if (  0 == strcmp( argv[4], "U1IDWP13" ) ) {
			DdTopthree_SET_PERSEL3_U1IDWP13(val);
			Ddim_Print(("It set PERSEL3_U1IDWP13 select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL3.bit.U1IDWP13	=%d\n", IO_CHIPTOP.PERSEL3.bit.U1IDWP13));
		}else if (  0 == strcmp( argv[4], "PRT0SCK3" ) ) {
			DdTopthree_SET_PERSEL3_PRT0SCK3(val);
			Ddim_Print(("It set PERSEL3_PRT0SCK3 select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL3.bit.PRT0SCK3	=%d\n", IO_CHIPTOP.PERSEL3.bit.PRT0SCK3));
		}
		else {
			Ddim_Print(("please check 3rd parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void  ctSetCtrlPersel4(kint argc, kchar** argv)
{
	kulong val;

	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "EI22UD0A" ) ) {
			DdTopthree_SET_PERSEL4_EI22UD0A(val);
			Ddim_Print(("It set PERSEL4_EI22UD0A select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL4.bit.EI22UD0A	=%d\n", IO_CHIPTOP.PERSEL4.bit.EI22UD0A));
		}else if (  0 == strcmp( argv[4], "EI23UD0B" ) ) {
			DdTopthree_SET_PERSEL4_EI23UD0B(val);
			Ddim_Print(("It set PERSEL4_EI23UD0B select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL4.bit.EI23UD0B	=%d\n", IO_CHIPTOP.PERSEL4.bit.EI23UD0B));
		}else if (  0 == strcmp( argv[4], "EI24UD1A" ) ) {
			DdTopthree_SET_PERSEL4_EI24UD1A(val);
			Ddim_Print(("It set PERSEL4_EI24UD1A select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL4.bit.EI24UD1A	=%d\n", IO_CHIPTOP.PERSEL4.bit.EI24UD1A));
		}else if (  0 == strcmp( argv[4], "EI25UD1B" ) ) {
			DdTopthree_SET_PERSEL4_EI25UD1B(val);
			Ddim_Print(("It set PERSEL4_EI25UD1B select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL4.bit.EI25UD1B	=%d\n", IO_CHIPTOP.PERSEL4.bit.EI25UD1B));
		}else if (  0 == strcmp( argv[4], "EI26UD2A" ) ) {
			DdTopthree_SET_PERSEL4_EI26UD2A(val);
			Ddim_Print(("It set PERSEL4_EI26UD2A select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL4.bit.EI26UD2A	=%d\n", IO_CHIPTOP.PERSEL4.bit.EI26UD2A));
		}else if (  0 == strcmp( argv[4], "EI27UD2B" ) ) {
			DdTopthree_SET_PERSEL4_EI27UD2B(val);
			Ddim_Print(("It set PERSEL4_EI27UD2B select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL4.bit.EI27UD2B	=%d\n", IO_CHIPTOP.PERSEL4.bit.EI27UD2B));
		}else if (  0 == strcmp( argv[4], "EI28UD3A" ) ) {
			DdTopthree_SET_PERSEL4_EI28UD3A(val);
			Ddim_Print(("It set PERSEL4_EI28UD3A select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL4.bit.EI28UD3A	=%d\n", IO_CHIPTOP.PERSEL4.bit.EI28UD3A));
		}else if (  0 == strcmp( argv[4], "EI29UD3B" ) ) {
			DdTopthree_SET_PERSEL4_EI29UD3B(val);
			Ddim_Print(("It set PERSEL4_EI29UD3B select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL4.bit.EI29UD3B	=%d\n", IO_CHIPTOP.PERSEL4.bit.EI29UD3B));
		}else if (  0 == strcmp( argv[4], "EI30UD4A" ) ) {
			DdTopthree_SET_PERSEL4_EI30UD4A(val);
			Ddim_Print(("It set PERSEL4_EI30UD4A select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL4.bit.EI30UD4A	=%d\n", IO_CHIPTOP.PERSEL4.bit.EI30UD4A));
		}else if (  0 == strcmp( argv[4], "EI31UD4B" ) ) {
			DdTopthree_SET_PERSEL4_EI31UD4B(val);
			Ddim_Print(("It set PERSEL4_EI31UD4B select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL4.bit.EI31UD4B	=%d\n", IO_CHIPTOP.PERSEL4.bit.EI31UD4B));
		}else if (  0 == strcmp( argv[4], "SD3CDXS" ) ) {
			DdTopthree_SET_PERSEL4_SD3CDXS(val);
			Ddim_Print(("It set PERSEL4_SD3CDXS select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL4.bit.SD3CDXS	=%d\n", IO_CHIPTOP.PERSEL4.bit.SD3CDXS));
		}else if (  0 == strcmp( argv[4], "SD3WPS" ) ) {
			DdTopthree_SET_PERSEL4_SD3WPS(val);
			Ddim_Print(("It set PERSEL4_SD3WPS select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL4.bit.SD3WPS	=%d\n", IO_CHIPTOP.PERSEL4.bit.SD3WPS));
		}else if (  0 == strcmp( argv[4], "U1OCDXS" ) ) {
			DdTopthree_SET_PERSEL4_U1OCDXS(val);
			Ddim_Print(("It set PERSEL4_U1OCDXS select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL4.bit.U1OCDXS	=%d\n", IO_CHIPTOP.PERSEL4.bit.U1OCDXS));
		}else if (  0 == strcmp( argv[4], "U1IDDIGS" ) ) {
			DdTopthree_SET_PERSEL4_U1IDDIGS(val);
			Ddim_Print(("It set PERSEL4_U1IDDIGS select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL4.bit.U1IDDIGS =%d\n", IO_CHIPTOP.PERSEL4.bit.U1IDDIGS));
		}else if (  0 == strcmp( argv[4], "U2OCDXS" ) ) {
			DdTopthree_SET_PERSEL4_U2OCDXS(val);
			Ddim_Print(("It set PERSEL4_U2OCDXS select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL4.bit.U2OCDXS =%d\n", IO_CHIPTOP.PERSEL4.bit.U2OCDXS));
		}else if (  0 == strcmp( argv[4], "U2IDDIGS" ) ) {
			DdTopthree_SET_PERSEL4_U2IDDIGS(val);
			Ddim_Print(("It set PERSEL4_U2IDDIGS select.\n"));
			Ddim_Print(("IO_CHIPTOP.PERSEL4.bit.U2IDDIGS =%d\n", IO_CHIPTOP.PERSEL4.bit.U2IDDIGS));
		}
		else {
			Ddim_Print(("please check 3rd parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void  ctSetCtrlMsel(kint argc, kchar** argv)
{
	kulong val;

	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "MSEL" ) ) {
			DdTopthree_SET_MSELC_MSEL(val);
			Ddim_Print(("It set MSEL_MSEL select.\n"));
			Ddim_Print(("IO_CHIPTOP.MSEL.bit.MSEL = %d\n", IO_CHIPTOP.MSELC.bit.MSEL));
		}
		else {
			Ddim_Print(("please check 3rd parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void  ctSetCtrlDbcnt1(kint argc, kchar** argv)
{
	kulong val;

	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "T07DC" ) ) {
			DdTopthree_SET_DBCNT1_T07DC(val);
			Ddim_Print(("It set DBCNT1_T07DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT1.bit.T07DC = %d\n", IO_CHIPTOP.DBCNT1.bit.T07DC));
		}else if (  0 == strcmp( argv[4], "T08DC" ) ) {
			DdTopthree_SET_DBCNT1_T08DC(val);
			Ddim_Print(("It set DBCNT1_T08DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT1.bit.T08DC = %d\n", IO_CHIPTOP.DBCNT1.bit.T08DC));
		}else if (  0 == strcmp( argv[4], "T09DC" ) ) {
			DdTopthree_SET_DBCNT1_T09DC(val);
			Ddim_Print(("It set DBCNT1_T09DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT1.bit.T09DC = %d\n", IO_CHIPTOP.DBCNT1.bit.T09DC));
		}else if (  0 == strcmp( argv[4], "T10DC" ) ) {
			DdTopthree_SET_DBCNT1_T10DC(val);
			Ddim_Print(("It set DBCNT1_T10DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT1.bit.T10DC = %d\n", IO_CHIPTOP.DBCNT1.bit.T10DC));
		}else if (  0 == strcmp( argv[4], "T11DC" ) ) {
			DdTopthree_SET_DBCNT1_T11DC(val);
			Ddim_Print(("It set DBCNT1_T11DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT1.bit.T11DC = %d\n", IO_CHIPTOP.DBCNT1.bit.T11DC));
		}else if (  0 == strcmp( argv[4], "T12DC" ) ) {
			DdTopthree_SET_DBCNT1_T12DC(val);
			Ddim_Print(("It set DBCNT1_T12DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT1.bit.T12DC = %d\n", IO_CHIPTOP.DBCNT1.bit.T12DC));
		}else if (  0 == strcmp( argv[4], "T13DC" ) ) {
			DdTopthree_SET_DBCNT1_T13DC(val);
			Ddim_Print(("It set DBCNT1_T13DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT1.bit.T13DC = %d\n", IO_CHIPTOP.DBCNT1.bit.T13DC));
		}else if (  0 == strcmp( argv[4], "T14DC" ) ) {
			DdTopthree_SET_DBCNT1_T14DC(val);
			Ddim_Print(("It set DBCNT1_T14DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT1.bit.T14DC = %d\n", IO_CHIPTOP.DBCNT1.bit.T14DC));
		}else if (  0 == strcmp( argv[4], "T15DC" ) ) {
			DdTopthree_SET_DBCNT1_T15DC(val);
			Ddim_Print(("It set DBCNT1_T15DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT1.bit.T15DC = %d\n", IO_CHIPTOP.DBCNT1.bit.T15DC));
		}
		else {
			Ddim_Print(("please check 3rd parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void  ctSetCtrlDbcnt2(kint argc, kchar** argv)
{
	kulong val;

	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "T16DC" ) ) {
			DdTopthree_SET_DBCNT2_T16DC(val);
			Ddim_Print(("It set DBCNT2_T16DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT2.bit.T16DC = %d\n", IO_CHIPTOP.DBCNT2.bit.T16DC));
		}else if (  0 == strcmp( argv[4], "T17DC" ) ) {
			DdTopthree_SET_DBCNT2_T17DC(val);
			Ddim_Print(("It set DBCNT2_T17DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT2.bit.T17DC = %d\n", IO_CHIPTOP.DBCNT2.bit.T17DC));
		}else if (  0 == strcmp( argv[4], "T18DC" ) ) {
			DdTopthree_SET_DBCNT2_T18DC(val);
			Ddim_Print(("It set DBCNT2_T18DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT2.bit.T18DC = %d\n", IO_CHIPTOP.DBCNT2.bit.T18DC));
		}else if (  0 == strcmp( argv[4], "T19DC" ) ) {
			DdTopthree_SET_DBCNT2_T19DC(val);
			Ddim_Print(("It set DBCNT2_T19DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT2.bit.T19DC = %d\n", IO_CHIPTOP.DBCNT2.bit.T19DC));
		}else if (  0 == strcmp( argv[4], "T20DC" ) ) {
			DdTopthree_SET_DBCNT2_T20DC(val);
			Ddim_Print(("It set DBCNT2_T20DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT2.bit.T20DC = %d\n", IO_CHIPTOP.DBCNT2.bit.T20DC));
		}else if (  0 == strcmp( argv[4], "T21DC" ) ) {
			DdTopthree_SET_DBCNT2_T21DC(val);
			Ddim_Print(("It set DBCNT2_T21DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT2.bit.T21DC = %d\n", IO_CHIPTOP.DBCNT2.bit.T21DC));
		}else if (  0 == strcmp( argv[4], "T22DC" ) ) {
			DdTopthree_SET_DBCNT2_T22DC(val);
			Ddim_Print(("It set DBCNT2_T22DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT2.bit.T22DC = %d\n", IO_CHIPTOP.DBCNT2.bit.T22DC));
		}else if (  0 == strcmp( argv[4], "T23DC" ) ) {
			DdTopthree_SET_DBCNT2_T23DC(val);
			Ddim_Print(("It set DBCNT2_T23DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT2.bit.T23DC = %d\n", IO_CHIPTOP.DBCNT2.bit.T23DC));
		}else if (  0 == strcmp( argv[4], "T24DC" ) ) {
			DdTopthree_SET_DBCNT2_T24DC(val);
			Ddim_Print(("It set DBCNT2_T24DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT2.bit.T24DC = %d\n", IO_CHIPTOP.DBCNT2.bit.T24DC));
		}else if (  0 == strcmp( argv[4], "T25DC" ) ) {
			DdTopthree_SET_DBCNT2_T25DC(val);
			Ddim_Print(("It set DBCNT2_T25DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT2.bit.T25DC = %d\n", IO_CHIPTOP.DBCNT2.bit.T25DC));
		}else if (  0 == strcmp( argv[4], "T26DC" ) ) {
			DdTopthree_SET_DBCNT2_T26DC(val);
			Ddim_Print(("It set DBCNT2_T26DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT2.bit.T26DC = %d\n", IO_CHIPTOP.DBCNT2.bit.T26DC));
		}else if (  0 == strcmp( argv[4], "T27DC" ) ) {
			DdTopthree_SET_DBCNT2_T27DC(val);
			Ddim_Print(("It set DBCNT2_T27DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT2.bit.T27DC = %d\n", IO_CHIPTOP.DBCNT2.bit.T27DC));
		}else if (  0 == strcmp( argv[4], "T28DC" ) ) {
			DdTopthree_SET_DBCNT2_T28DC(val);
			Ddim_Print(("It set DBCNT2_T28DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT2.bit.T28DC = %d\n", IO_CHIPTOP.DBCNT2.bit.T28DC));
		}else if (  0 == strcmp( argv[4], "T29DC" ) ) {
			DdTopthree_SET_DBCNT2_T29DC(val);
			Ddim_Print(("It set DBCNT2_T29DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT2.bit.T29DC = %d\n", IO_CHIPTOP.DBCNT2.bit.T29DC));
		}else if (  0 == strcmp( argv[4], "T30DC" ) ) {
			DdTopthree_SET_DBCNT2_T30DC(val);
			Ddim_Print(("It set DBCNT2_T30DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT2.bit.T30DC = %d\n", IO_CHIPTOP.DBCNT2.bit.T30DC));
		}else if (  0 == strcmp( argv[4], "T31DC" ) ) {
			DdTopthree_SET_DBCNT2_T31DC(val);
			Ddim_Print(("It set DBCNT2_T31DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT2.bit.T31DC = %d\n", IO_CHIPTOP.DBCNT2.bit.T31DC));
		}
		else {
			Ddim_Print(("please check 3rd parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void  ctSetCtrlDbcnt3(kint argc, kchar** argv)
{
	kulong val;

	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "T32DC" ) ) {
			DdTopthree_SET_DBCNT3_T32DC(val);
			Ddim_Print(("It set DBCNT3_T32DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.IO_CHIPTOP.DBCNT3.bit.T32DC = %d\n", IO_CHIPTOP.DBCNT3.bit.T32DC));
		}else if (  0 == strcmp( argv[4], "T33DC" ) ) {
			DdTopthree_SET_DBCNT3_T33DC(val);
			Ddim_Print(("It set DBCNT3_T33DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.IO_CHIPTOP.DBCNT3.bit.T33DC = %d\n", IO_CHIPTOP.DBCNT3.bit.T33DC));
		}else if (  0 == strcmp( argv[4], "T34DC" ) ) {
			DdTopthree_SET_DBCNT3_T34DC(val);
			Ddim_Print(("It set DBCNT3_T34DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.IO_CHIPTOP.DBCNT3.bit.T34DC = %d\n", IO_CHIPTOP.DBCNT3.bit.T34DC));
		}else if (  0 == strcmp( argv[4], "T35DC" ) ) {
			DdTopthree_SET_DBCNT3_T35DC(val);
			Ddim_Print(("It set DBCNT3_T35DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.IO_CHIPTOP.DBCNT3.bit.T35DC = %d\n", IO_CHIPTOP.DBCNT3.bit.T35DC));
		}else if (  0 == strcmp( argv[4], "T36DC" ) ) {
			DdTopthree_SET_DBCNT3_T36DC(val);
			Ddim_Print(("It set DBCNT3_T36DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.IO_CHIPTOP.DBCNT3.bit.T36DC = %d\n", IO_CHIPTOP.DBCNT3.bit.T36DC));
		}else if (  0 == strcmp( argv[4], "T37DC" ) ) {
			DdTopthree_SET_DBCNT3_T37DC(val);
			Ddim_Print(("It set DBCNT3_T37DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.IO_CHIPTOP.DBCNT3.bit.T37DC = %d\n", IO_CHIPTOP.DBCNT3.bit.T37DC));
		}else if (  0 == strcmp( argv[4], "T38DC" ) ) {
			DdTopthree_SET_DBCNT3_T38DC(val);
			Ddim_Print(("It set DBCNT3_T38DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.IO_CHIPTOP.DBCNT3.bit.T38DC = %d\n", IO_CHIPTOP.DBCNT3.bit.T38DC));
		}else if (  0 == strcmp( argv[4], "T39DC" ) ) {
			DdTopthree_SET_DBCNT3_T39DC(val);
			Ddim_Print(("It set DBCNT3_T39DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.IO_CHIPTOP.DBCNT3.bit.T39DC = %d\n", IO_CHIPTOP.DBCNT3.bit.T39DC));
		}else if (  0 == strcmp( argv[4], "T40DC" ) ) {
			DdTopthree_SET_DBCNT3_T40DC(val);
			Ddim_Print(("It set DBCNT3_T40DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.IO_CHIPTOP.DBCNT3.bit.T40DC = %d\n", IO_CHIPTOP.DBCNT3.bit.T40DC));
		}else if (  0 == strcmp( argv[4], "T41DC" ) ) {
			DdTopthree_SET_DBCNT3_T41DC(val);
			Ddim_Print(("It set DBCNT3_T41DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.IO_CHIPTOP.DBCNT3.bit.T41DC = %d\n", IO_CHIPTOP.DBCNT3.bit.T41DC));
		}else if (  0 == strcmp( argv[4], "T42DC" ) ) {
			DdTopthree_SET_DBCNT3_T42DC(val);
			Ddim_Print(("It set DBCNT3_T42DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.IO_CHIPTOP.DBCNT3.bit.T42DC = %d\n", IO_CHIPTOP.DBCNT3.bit.T42DC));
		}else if (  0 == strcmp( argv[4], "T43DC" ) ) {
			DdTopthree_SET_DBCNT3_T43DC(val);
			Ddim_Print(("It set DBCNT3_T43DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.IO_CHIPTOP.DBCNT3.bit.T43DC = %d\n", IO_CHIPTOP.DBCNT3.bit.T43DC));
		}else if (  0 == strcmp( argv[4], "T44DC" ) ) {
			DdTopthree_SET_DBCNT3_T44DC(val);
			Ddim_Print(("It set DBCNT3_T44DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.IO_CHIPTOP.DBCNT3.bit.T44DC = %d\n", IO_CHIPTOP.DBCNT3.bit.T44DC));
		}else if (  0 == strcmp( argv[4], "T45DC" ) ) {
			DdTopthree_SET_DBCNT3_T45DC(val);
			Ddim_Print(("It set DBCNT3_T45DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.IO_CHIPTOP.DBCNT3.bit.T45DC = %d\n", IO_CHIPTOP.DBCNT3.bit.T45DC));
		}else if (  0 == strcmp( argv[4], "T46DC" ) ) {
			DdTopthree_SET_DBCNT3_T46DC(val);
			Ddim_Print(("It set DBCNT3_T46DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.IO_CHIPTOP.DBCNT3.bit.T46DC = %d\n", IO_CHIPTOP.DBCNT3.bit.T46DC));
		}else if (  0 == strcmp( argv[4], "T47DC" ) ) {
			DdTopthree_SET_DBCNT3_T47DC(val);
			Ddim_Print(("It set DBCNT3_T47DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.IO_CHIPTOP.DBCNT3.bit.T47DC = %d\n", IO_CHIPTOP.DBCNT3.bit.T47DC));
		}
		else {
			Ddim_Print(("please check 3rd parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void  ctSetCtrlDbcnt4(kint argc, kchar** argv)
{
	kulong val;

	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "T48DC" ) ) {
			DdTopthree_SET_DBCNT4_T48DC(val);
			Ddim_Print(("It set DBCNT4_T48DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT4.bit.T48DC = %d\n", IO_CHIPTOP.DBCNT4.bit.T48DC));
		}else if (  0 == strcmp( argv[4], "T49DC" ) ) {
			DdTopthree_SET_DBCNT4_T49DC(val);
			Ddim_Print(("It set DBCNT4_T49DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT4.bit.T49DC = %d\n", IO_CHIPTOP.DBCNT4.bit.T49DC));
		}else if (  0 == strcmp( argv[4], "T50DC" ) ) {
			DdTopthree_SET_DBCNT4_T50DC(val);
			Ddim_Print(("It set DBCNT4_T50DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT4.bit.T50DC = %d\n", IO_CHIPTOP.DBCNT4.bit.T50DC));
		}else if (  0 == strcmp( argv[4], "T51DC" ) ) {
			DdTopthree_SET_DBCNT4_T51DC(val);
			Ddim_Print(("It set DBCNT4_T51DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT4.bit.T51DC = %d\n", IO_CHIPTOP.DBCNT4.bit.T51DC));
		}else if (  0 == strcmp( argv[4], "T52DC" ) ) {
			DdTopthree_SET_DBCNT4_T52DC(val);
			Ddim_Print(("It set DBCNT4_T52DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT4.bit.T52DC = %d\n", IO_CHIPTOP.DBCNT4.bit.T52DC));
		}else if (  0 == strcmp( argv[4], "T53DC" ) ) {
			DdTopthree_SET_DBCNT4_T53DC(val);
			Ddim_Print(("It set DBCNT4_T53DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT4.bit.T53DC = %d\n", IO_CHIPTOP.DBCNT4.bit.T53DC));
		}else if (  0 == strcmp( argv[4], "T54DC" ) ) {
			DdTopthree_SET_DBCNT4_T54DC(val);
			Ddim_Print(("It set DBCNT4_T54DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT4.bit.T54DC = %d\n", IO_CHIPTOP.DBCNT4.bit.T54DC));
		}else if (  0 == strcmp( argv[4], "T55DC" ) ) {
			DdTopthree_SET_DBCNT4_T55DC(val);
			Ddim_Print(("It set DBCNT4_T55DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT4.bit.T55DC = %d\n", IO_CHIPTOP.DBCNT4.bit.T55DC));
		}else if (  0 == strcmp( argv[4], "T56DC" ) ) {
			DdTopthree_SET_DBCNT4_T56DC(val);
			Ddim_Print(("It set DBCNT4_T56DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT4.bit.T56DC = %d\n", IO_CHIPTOP.DBCNT4.bit.T56DC));
		}else if (  0 == strcmp( argv[4], "T57DC" ) ) {
			DdTopthree_SET_DBCNT4_T57DC(val);
			Ddim_Print(("It set DBCNT4_T57DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT4.bit.T57DC = %d\n", IO_CHIPTOP.DBCNT4.bit.T57DC));
		}else if (  0 == strcmp( argv[4], "T58DC" ) ) {
			DdTopthree_SET_DBCNT4_T58DC(val);
			Ddim_Print(("It set DBCNT4_T58DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT4.bit.T58DC = %d\n", IO_CHIPTOP.DBCNT4.bit.T58DC));
		}else if (  0 == strcmp( argv[4], "T59DC" ) ) {
			DdTopthree_SET_DBCNT4_T59DC(val);
			Ddim_Print(("It set DBCNT4_T59DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT4.bit.T59DC = %d\n", IO_CHIPTOP.DBCNT4.bit.T59DC));
		}else if (  0 == strcmp( argv[4], "T60DC" ) ) {
			DdTopthree_SET_DBCNT4_T60DC(val);
			Ddim_Print(("It set DBCNT4_T60DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT4.bit.T60DC = %d\n", IO_CHIPTOP.DBCNT4.bit.T60DC));
		}else if (  0 == strcmp( argv[4], "T61DC" ) ) {
			DdTopthree_SET_DBCNT4_T61DC(val);
			Ddim_Print(("It set DBCNT4_T61DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT4.bit.T61DC = %d\n", IO_CHIPTOP.DBCNT4.bit.T61DC));
		}else if (  0 == strcmp( argv[4], "T62DC" ) ) {
			DdTopthree_SET_DBCNT4_T62DC(val);
			Ddim_Print(("It set DBCNT4_T62DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT4.bit.T62DC = %d\n", IO_CHIPTOP.DBCNT4.bit.T62DC));
		}else if (  0 == strcmp( argv[4], "T63DC" ) ) {
			DdTopthree_SET_DBCNT4_T63DC(val);
			Ddim_Print(("It set DBCNT4_T63DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT4.bit.T63DC = %d\n", IO_CHIPTOP.DBCNT4.bit.T63DC));
		}
		else {
			Ddim_Print(("please check 3rd parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void  ctSetCtrlDbcnt5(kint argc, kchar** argv)
{
	kulong val;

	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "T64DC" ) ) {
			DdTopthree_SET_DBCNT5_T64DC(val);
			Ddim_Print(("It set DBCNT5_T64DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT5.bit.T64DC = %d\n", IO_CHIPTOP.DBCNT5.bit.T64DC));
		}else if (  0 == strcmp( argv[4], "T65DC" ) ) {
			DdTopthree_SET_DBCNT5_T65DC(val);
			Ddim_Print(("It set DBCNT5_T65DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT5.bit.T65DC = %d\n", IO_CHIPTOP.DBCNT5.bit.T65DC));
		}else if (  0 == strcmp( argv[4], "T66DC" ) ) {
			DdTopthree_SET_DBCNT5_T66DC(val);
			Ddim_Print(("It set DBCNT5_T66DC select.\n"));
			Ddim_Print(("IO_CHIPTOP.DBCNT5.bit.T66DC = %d\n", IO_CHIPTOP.DBCNT5.bit.T66DC));
		}
		else {
			Ddim_Print(("please check 3rd parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void  ctSetCtrlPudcnt(kint argc, kchar** argv)
{
	kulong val;

	if (argc == 6) {
		val = atoi(argv[5]);
		if ( 0 == strcmp( argv[4], "EMMCNICS" ) ) {
			DdTopthree_SET_PUDCNT_EMMCNICS(val);
			Ddim_Print(("It set PUDCNT_EMMCNICS select.\n"));
			Ddim_Print(("IO_CHIPTOP.PUDCNT.bit.EMMCNICS = %d\n", IO_CHIPTOP.PUDCNT.bit.EMMCNICS));
		}else if (  0 == strcmp( argv[4], "EMDATPUE" ) ) {
			DdTopthree_SET_PUDCNT_EMDATPUE(val);
			Ddim_Print(("It set PUDCNT_EMDATPUE select.\n"));
			Ddim_Print(("IO_CHIPTOP.PUDCNT.bit.EMDATPUE = %d\n", IO_CHIPTOP.PUDCNT.bit.EMDATPUE));
		}else if (  0 == strcmp( argv[4], "EMCMDPUE" ) ) {
			DdTopthree_SET_PUDCNT_EMCMDPUE(val);
			Ddim_Print(("It set PUDCNT_EMCMDPUE select.\n"));
			Ddim_Print(("IO_CHIPTOP.PUDCNT.bit.EMCMDPUE = %d\n", IO_CHIPTOP.PUDCNT.bit.EMCMDPUE));
		}else if (  0 == strcmp( argv[4], "EMDSPDE" ) ) {
			DdTopthree_SET_PUDCNT_EMDSPDE(val);
			Ddim_Print(("It set PUDCNT_EMDSPDE select.\n"));
			Ddim_Print(("IO_CHIPTOP.PUDCNT.bit.EMDSPDE = %d\n", IO_CHIPTOP.PUDCNT.bit.EMDSPDE));
		}else if (  0 == strcmp( argv[4], "NFDATPUE" ) ) {
			DdTopthree_SET_PUDCNT_NFDATPUE(val);
			Ddim_Print(("It set PUDCNT_NFDATPUE select.\n"));
			Ddim_Print(("IO_CHIPTOP.PUDCNT.bit.NFDATPUE = %d\n", IO_CHIPTOP.PUDCNT.bit.NFDATPUE));
		}else if (  0 == strcmp( argv[4], "NFRBXPUE" ) ) {
			DdTopthree_SET_PUDCNT_NFRBXPUE(val);
			Ddim_Print(("It set PUDCNT_NFRBXPUE select.\n"));
			Ddim_Print(("IO_CHIPTOP.PUDCNT.bit.NFRBXPUE = %d\n", IO_CHIPTOP.PUDCNT.bit.NFRBXPUE));
		}else if (  0 == strcmp( argv[4], "NFDQSPUE" ) ) {
			DdTopthree_SET_PUDCNT_NFDQSPUE(val);
			Ddim_Print(("It set PUDCNT_NFDQSPUE select.\n"));
			Ddim_Print(("IO_CHIPTOP.PUDCNT.bit.NFDQSPUE = %d\n", IO_CHIPTOP.PUDCNT.bit.NFDQSPUE));
		}else if (  0 == strcmp( argv[4], "SP1MISOPE" ) ) {
			DdTopthree_SET_PUDCNT_SP1MISOPE(val);
			Ddim_Print(("It set PUDCNT_SP1MISOPE select.\n"));
			Ddim_Print(("IO_CHIPTOP.PUDCNT.bit.SP1MISOPE = %d\n", IO_CHIPTOP.PUDCNT.bit.SP1MISOPE));
		}else if (  0 == strcmp( argv[4], "SP1MOSIPE" ) ) {
			DdTopthree_SET_PUDCNT_SP1MOSIPE(val);
			Ddim_Print(("It set PUDCNT_SP1MOSIPE select.\n"));
			Ddim_Print(("IO_CHIPTOP.PUDCNT.bit.SP1MOSIPE = %d\n", IO_CHIPTOP.PUDCNT.bit.SP1MOSIPE));
		}else if (  0 == strcmp( argv[4], "SP1SCKPE" ) ) {
			DdTopthree_SET_PUDCNT_SP1SCKPE(val);
			Ddim_Print(("It set PUDCNT_SP1SCKPE select.\n"));
			Ddim_Print(("IO_CHIPTOP.PUDCNT.bit.SP1SCKPE = %d\n", IO_CHIPTOP.PUDCNT.bit.SP1SCKPE));
		}else if (  0 == strcmp( argv[4], "SP1CS0PE" ) ) {
			DdTopthree_SET_PUDCNT_SP1CS0PE(val);
			Ddim_Print(("It set PUDCNT_SP1CS0PE select.\n"));
			Ddim_Print(("IO_CHIPTOP.PUDCNT.bit.SP1CS0PE = %d\n", IO_CHIPTOP.PUDCNT.bit.SP1CS0PE));
		}else if (  0 == strcmp( argv[4], "SP1MISOUDC" ) ) {
			DdTopthree_SET_PUDCNT_SP1MISOUDC(val);
			Ddim_Print(("It set PUDCNT_SP1MISOUDC select.\n"));
			Ddim_Print(("IO_CHIPTOP.PUDCNT.bit.SP1MISOUDC = %d\n", IO_CHIPTOP.PUDCNT.bit.SP1MISOUDC));
		}else if (  0 == strcmp( argv[4], "SP1MOSIUDC" ) ) {
			DdTopthree_SET_PUDCNT_SP1MOSIUDC(val);
			Ddim_Print(("It set PUDCNT_SP1MOSIUDC select.\n"));
			Ddim_Print(("IO_CHIPTOP.PUDCNT.bit.SP1MOSIUDC = %d\n", IO_CHIPTOP.PUDCNT.bit.SP1MOSIUDC));
		}else if (  0 == strcmp( argv[4], "SP1SCKUDC" ) ) {
			DdTopthree_SET_PUDCNT_SP1SCKUDC(val);
			Ddim_Print(("It set PUDCNT_SP1SCKUDC select.\n"));
			Ddim_Print(("IO_CHIPTOP.PUDCNT.bit.SP1SCKUDC = %d\n", IO_CHIPTOP.PUDCNT.bit.SP1SCKUDC));
		}else if (  0 == strcmp( argv[4], "SP1CS0UDC" ) ) {
			DdTopthree_SET_PUDCNT_SP1CS0UDC(val);
			Ddim_Print(("It set PUDCNT_SP1CS0UDC select.\n"));
			Ddim_Print(("IO_CHIPTOP.PUDCNT.bit.SP1CS0UDC = %d\n", IO_CHIPTOP.PUDCNT.bit.SP1CS0UDC));
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
void ct_set_ctrl(CtSetCtrl *self)
{
    if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "persel1" ) ) {
         ctSetCtrlPersel1(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "persel2" ) ) {
         ctSetCtrlPersel2(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "persel3" ) ) {
         ctSetCtrlPersel3(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "persel4" ) ) {
         ctSetCtrlPersel4(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "msel" ) ) {
         ctSetCtrlMsel(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "dbcnt1" ) ) {
         ctSetCtrlDbcnt1(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "dbcnt2" ) ) {
         ctSetCtrlDbcnt2(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    } else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "dbcnt3" ) ) {
         ctSetCtrlDbcnt3(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "dbcnt4" ) ) {
         ctSetCtrlDbcnt4(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "dbcnt5" ) ) {
         ctSetCtrlDbcnt5(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }else if( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "pudcnt" ) ) {
         ctSetCtrlPudcnt(((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
}

CtSetCtrl* ct_set_ctrl_new(void) 
{
    CtSetCtrl *self = k_object_new_with_private(CT_TYPE_SET_CTRL, sizeof(CtSetCtrlPrivate));
    return self;
}
