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
#include "ctpll.h"
#include "ctsetpll.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtPll, ct_pll);
#define CT_PLL_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtPllPrivate,CT_TYPE_PLL))

struct _CtPllPrivate
{
	CtSetPll *ctSetPll;
};
/****************
* DECLS
*/
static kint32 			ctStartPll00(void);
static kint32 			ctStopPll00(void);
static kint32 			ctStartPll01(void);
static kint32 			ctStopPll01(void);
static kint32 			ctStartPll02(void);
static kint32 			ctStopPll02(void);
static kint32 			ctStartPll03(void);
static kint32 			ctStopPll03(void);
static kint32 			ctStartPll04(void);
static kint32 			ctStopPll04(void);
static kint32 			ctStartPll05(void);
static kint32 			ctStopPll05(void);
static kint32 			ctStartPll05A(void);
static kint32 			ctStopPll05A(void);
static kint32 			ctStartPll06(void);
static kint32 			ctStopPll06(void);
static kint32 			ctStartPll07(void);
static kint32 			ctStopPll07(void);
static kint32 			ctStartPll08(void);
static kint32 			ctStopPll08(void);
static kint32 			ctStartPll10(void);
static kint32 			ctStopPll10(void);
static kint32 			ctStartPll10A(void);
static kint32 			ctStopPll10A(void);
static kint32 			ctStartPll11(void);
static kint32 			ctStopPll11(void);
static kint32 			ctStartDdrPll00(void);
static kint32 			ctStopDdr_Pll00(void);
static kint32 			ctStartDdrPll01(void);
static kint32 			ctStopDdr_Pll01(void);
static kint32 			ctStartDdrPll02(void);
static kint32 			ctStopDdr_Pll02(void);
static kint32 			ctStartDdrPll10(void);
static kint32 			ctStopDdr_Pll10(void);
static kint32 			ctStartDdrPll11(void);
static kint32 			ctStopDdr_Pll11(void);
static kint32 			ctStartDdrPll12(void);
static kint32 			ctStopDdr_Pll12(void);
/****************
* IMPL
*/
static void ct_pll_constructor(CtPll *self)
{
	CtPllPrivate *priv = CT_PLL_GET_PRIVATE(self);  
	priv->ctSetPll = ct_set_pll_new();
}

static void ct_pll_destructor(CtPll *self)
{
	CtPllPrivate *priv = CT_PLL_GET_PRIVATE(self);
	k_object_unref(priv->ctSetPll);
}

static kint32 ctStartPll00(void)
{
	kint32 ret;

#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.PL00ST = 0;
	IO_CHIPTOP.PLLCNT2.bit.PL00SEL = 0;
#endif
	ret = dd_topthree_start_pll00();
	if( ret == D_DDIM_OK ){
		Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL00ST = %d\n", IO_CHIPTOP.PLLCNT1.bit.PL00ST));
		Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL00SEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL00SEL));
	}
	return(ret);
}

static kint32 ctStopPll00(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT2.bit.PL00SEL = 1;
	IO_CHIPTOP.PLLCNT1.bit.PL00ST = 1;
#endif
	dd_topthree_stop_pll00();
	Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL00ST = %d\n", IO_CHIPTOP.PLLCNT1.bit.PL00ST));
	Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL00SEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL00SEL));
	return(D_DDIM_OK);
}

static kint32 ctStartPll01(void)
{
	kint32 ret;

#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.PL01ST = 0;
	IO_CHIPTOP.PLLCNT2.bit.PL01SEL = 0;
#endif
	ret = dd_topthree_start_pll01();
	if( ret == D_DDIM_OK ){
		Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL01ST = %d\n", IO_CHIPTOP.PLLCNT1.bit.PL01ST));
		Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL01SEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL01SEL));
	}
	return(ret);
}

static kint32 ctStopPll01(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT2.bit.PL01SEL = 1;
	IO_CHIPTOP.PLLCNT1.bit.PL01ST = 1;
#endif
	dd_topthree_stop_pll01();
	Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL01SEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL01SEL));
	Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL01ST = %d\n", IO_CHIPTOP.PLLCNT1.bit.PL01ST));
	return(D_DDIM_OK);
}

static kint32 ctStartPll02(void)
{
	kint32 ret;

#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.PL02ST = 0;
	IO_CHIPTOP.PLLCNT2.bit.PL02SEL = 0;
#endif
	ret = dd_topthree_start_pll02();
	if( ret == D_DDIM_OK ){
		Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL02ST = %d\n", IO_CHIPTOP.PLLCNT1.bit.PL02ST));
		Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL02SEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL02SEL));
	}
	return(ret);
}

static kint32 ctStopPll02(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT2.bit.PL02SEL = 1;
	IO_CHIPTOP.PLLCNT1.bit.PL02ST = 1;
#endif
	dd_topthree_stop_pll02();
	Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL02SEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL02SEL));
	Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL02ST = %d\n", IO_CHIPTOP.PLLCNT1.bit.PL02ST));
	return(D_DDIM_OK);
}

static kint32 ctStartPll03(void)
{
	kint32 ret;

#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.PL03ST = 0;
	IO_CHIPTOP.PLLCNT2.bit.PL03SEL = 0;
#endif
	ret = dd_topthree_start_pll03();
	if( ret == D_DDIM_OK ){
		Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL03ST = %d\n", IO_CHIPTOP.PLLCNT1.bit.PL03ST));
		Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL03SEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL03SEL));
	}
	return(ret);
}

static kint32 ctStopPll03(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT2.bit.PL03SEL = 1;
	IO_CHIPTOP.PLLCNT1.bit.PL03ST = 1;
#endif
	dd_topthree_stop_pll03();
	Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL03SEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL03SEL));
	Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL03ST = %d\n", IO_CHIPTOP.PLLCNT1.bit.PL03ST));
	return(D_DDIM_OK);
}

static kint32 ctStartPll04(void)
{
	kint32 ret;

#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.PL04ST = 0;
	IO_CHIPTOP.PLLCNT2.bit.PL04SEL = 0;
#endif
	ret = dd_topthree_start_pll04();
	if( ret == D_DDIM_OK ){
		Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL04ST = %d\n", IO_CHIPTOP.PLLCNT1.bit.PL04ST));
		Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL04SEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL04SEL));
	}
	return(ret);
}

static kint32 ctStopPll04(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT2.bit.PL04SEL = 1;
	IO_CHIPTOP.PLLCNT1.bit.PL04ST = 1;
#endif
	dd_topthree_stop_pll04();
	Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL04SEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL04SEL));
	Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL04ST = %d\n", IO_CHIPTOP.PLLCNT1.bit.PL04ST));
	return(D_DDIM_OK);
}

static kint32 ctStartPll05(void)
{
	kint32 ret;

#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.PL05ST = 0;
	IO_CHIPTOP.PLLCNT2.bit.PL05SEL = 0;
#endif
	ret = dd_topthree_start_pll05();
	if( ret == D_DDIM_OK ){
		Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL05ST = %d\n", IO_CHIPTOP.PLLCNT1.bit.PL05ST));
		Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL05SEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL05SEL));
	}
	return(ret);
}

static kint32 ctStopPll05(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT2.bit.PL05SEL = 1;
	IO_CHIPTOP.PLLCNT1.bit.PL05ST = 1;
#endif
	dd_topthree_stop_pll05();
	Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL05SEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL05SEL));
	Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL05ST = %d\n", IO_CHIPTOP.PLLCNT1.bit.PL05ST));
	return(D_DDIM_OK);
}

static kint32 ctStartPll05A(void)
{
	kint32 ret;

#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.PL05AST = 0;
	IO_CHIPTOP.PLLCNT2.bit.PL05ASEL = 0;
#endif
	ret = dd_topthree_start_pll05A();
	if( ret == D_DDIM_OK ){
		Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL05AST = %d\n", IO_CHIPTOP.PLLCNT1.bit.PL05AST));
		Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL05ASEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL05ASEL));
	}
	return(ret);
}

static kint32 ctStopPll05A(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT2.bit.PL05SEL = 1;
	IO_CHIPTOP.PLLCNT1.bit.PL05ST = 1;
#endif
	dd_topthree_stop_pll05A();
	Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL05ASEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL05SEL));
	Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL05AST = %d\n", IO_CHIPTOP.PLLCNT1.bit.PL05ST));
	return(D_DDIM_OK);
}

static kint32 ctStartPll06(void)
{
	kint32 ret;

#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.PL06ST = 0;
	IO_CHIPTOP.PLLCNT2.bit.PL06SEL = 0;
#endif
	ret = dd_topthree_start_pll06();
	if( ret == D_DDIM_OK ){
		Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL06ST = %d\n", IO_CHIPTOP.PLLCNT1.bit.PL06ST));
		Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL06SEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL06SEL));
	}
	return(ret);
}

static kint32 ctStopPll06(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT2.bit.PL06SEL = 1;
	IO_CHIPTOP.PLLCNT1.bit.PL06ST = 1;
#endif
	dd_topthree_stop_pll06();
	Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL06SEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL06SEL));
	Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL06ST = %d\n", IO_CHIPTOP.PLLCNT1.bit.PL06ST));
	return(D_DDIM_OK);
}

static kint32 ctStartPll07(void)
{
	kint32 ret;

#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.PL07ST = 0;
	IO_CHIPTOP.PLLCNT2.bit.PL07SEL = 0;
#endif
	ret = dd_topthree_start_pll07();
	if( ret == D_DDIM_OK ){
		Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL07ST = %d\n", IO_CHIPTOP.PLLCNT1.bit.PL07ST));
		Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL07SEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL07SEL));
	}
	return(ret);
}

static kint32 ctStopPll07(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT2.bit.PL07SEL = 1;
	IO_CHIPTOP.PLLCNT1.bit.PL07ST = 1;
#endif
	dd_topthree_stop_pll07();
	Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL07SEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL07SEL));
	Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL07ST = %d\n", IO_CHIPTOP.PLLCNT1.bit.PL07ST));
	return(D_DDIM_OK);
}

static kint32 ctStartPll08(void)
{
	kint32 ret;

#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.PL08ST = 0;
	IO_CHIPTOP.PLLCNT2.bit.PL08SEL = 0;
#endif
	ret = dd_topthree_start_pll08();
	if( ret == D_DDIM_OK ){
		Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL08ST = %d\n", IO_CHIPTOP.PLLCNT1.bit.PL08ST));
		Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL08SEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL08SEL));
	}
	return(ret);
}

static kint32 ctStopPll08(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT2.bit.PL08SEL = 1;
	IO_CHIPTOP.PLLCNT1.bit.PL08ST = 1;
#endif
	dd_topthree_stop_pll08();
	Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL08SEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL08SEL));
	Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL08ST = %d\n", IO_CHIPTOP.PLLCNT1.bit.PL08ST));
	return(D_DDIM_OK);
}

static kint32 ctStartPll10(void)
{
	kint32 ret;

#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.PL10ST = 0;
	IO_CHIPTOP.PLLCNT2.bit.PL10SEL = 0;
#endif
	ret = dd_topthree_start_pll10();
	if( ret == D_DDIM_OK ){
		Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL10ST = %d\n", IO_CHIPTOP.PLLCNT1.bit.PL10ST));
		Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL10SEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL10SEL));
	}
	return(ret);
}

static kint32 ctStopPll10(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT2.bit.PL10SEL = 1;
	IO_CHIPTOP.PLLCNT1.bit.PL10ST = 1;
#endif
	dd_topthree_stop_pll10();
	Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL10SEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL10SEL));
	Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL10ST = %d\n", IO_CHIPTOP.PLLCNT1.bit.PL10ST));
	return(D_DDIM_OK);
}

static kint32 ctStartPll10A(void)
{
	kint32 ret;

#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.PL10AST = 0;
	IO_CHIPTOP.PLLCNT2.bit.PL10ASEL = 0;
#endif
	ret = dd_topthree_start_pll10A();
	if( ret == D_DDIM_OK ){
		Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL10AST = %d\n", IO_CHIPTOP.PLLCNT1.bit.PL10AST));
		Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL10ASEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL10ASEL));
	}
	return(ret);
}

static kint32 ctStopPll10A(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT2.bit.PL10ASEL = 1;
	IO_CHIPTOP.PLLCNT1.bit.PL10AST = 1;
#endif
	dd_topthree_stop_pll10A();
	Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL10ASEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL10ASEL));
	Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL10AST = %d\n", IO_CHIPTOP.PLLCNT1.bit.PL10AST));
	return(D_DDIM_OK);
}

static kint32 ctStartPll11(void)
{
	kint32 ret;

#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.PL11ST = 0;
	IO_CHIPTOP.PLLCNT2.bit.PL11SEL = 0;
#endif
	ret = dd_topthree_start_pll11();
	if( ret == D_DDIM_OK ){
		Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL11ST = %d\n", IO_CHIPTOP.PLLCNT1.bit.PL11ST));
		Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL11SEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL11SEL));
	}
	return(ret);
}

static kint32 ctStopPll11(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT2.bit.PL11SEL = 1;
	IO_CHIPTOP.PLLCNT1.bit.PL11ST = 1;
#endif
	dd_topthree_stop_pll11();
	Ddim_Print(("IO_CHIPTOP.PLLCNT2.bit.PL11SEL = %d\n", IO_CHIPTOP.PLLCNT2.bit.PL11SEL));
	Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.PL11ST = %d\n", IO_CHIPTOP.PLLCNT1.bit.PL11ST));
	return(D_DDIM_OK);
}

static kint32 ctStartDdrPll00(void)
{
	kint32 ret;

#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.DPL00ST = 0;
#endif
	ret = dd_topthree_start_ddr_pll00();
	if( ret == D_DDIM_OK ){
		Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.DPL00ST = %d\n", IO_CHIPTOP.PLLCNT1.bit.DPL00ST));
	}
	return(ret);
}

static kint32 ctStopDdr_Pll00(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.DPL00ST = 1;
#endif
	dd_topthree_stop_ddr_pll00();
	Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.DPL00ST = %d\n", IO_CHIPTOP.PLLCNT1.bit.DPL00ST));
	return(D_DDIM_OK);
}

static kint32 ctStartDdrPll01(void)
{
	kint32 ret;

#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.DPL01ST = 0;
#endif
	ret = dd_topthree_start_ddr_pll01();
	if( ret == D_DDIM_OK ){
		Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.DPL01ST = %d\n", IO_CHIPTOP.PLLCNT1.bit.DPL01ST));
	}
	return(ret);
}

static kint32 ctStopDdr_Pll01(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.DPL01ST = 1;
#endif
	dd_topthree_stop_ddr_pll01();
	Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.DPL01ST = %d\n", IO_CHIPTOP.PLLCNT1.bit.DPL01ST));
	return(D_DDIM_OK);
}

static kint32 ctStartDdrPll02(void)
{
	kint32 ret;

#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.DPL02ST = 0;
#endif
	ret = dd_topthree_start_ddr_pll02();
	if( ret == D_DDIM_OK ){
		Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.DPL02ST = %d\n", IO_CHIPTOP.PLLCNT1.bit.DPL02ST));
	}
	return(ret);
}

static kint32 ctStopDdr_Pll02(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.DPL02ST = 1;
#endif
	dd_topthree_stop_ddr_pll02();
	Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.DPL02ST = %d\n", IO_CHIPTOP.PLLCNT1.bit.DPL02ST));
	return(D_DDIM_OK);
}

static kint32 ctStartDdrPll10(void)
{
	kint32 ret;

#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.DPL10ST = 0;
#endif
	ret = dd_topthree_start_ddr_pll10();
	if( ret == D_DDIM_OK ){
		Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.DPL10ST = %d\n", IO_CHIPTOP.PLLCNT1.bit.DPL10ST));
	}
	return(ret);
}

static kint32 ctStopDdr_Pll10(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.DPL10ST = 1;
#endif
	dd_topthree_stop_ddr_pll10();
	Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.DPL10ST = %d\n", IO_CHIPTOP.PLLCNT1.bit.DPL10ST));
	return(D_DDIM_OK);
}

static kint32 ctStartDdrPll11(void)
{
	kint32 ret;

#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.DPL11ST = 0;
#endif
	ret = dd_topthree_start_ddr_pll11();
	if( ret == D_DDIM_OK ){
		Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.DPL11ST = %d\n", IO_CHIPTOP.PLLCNT1.bit.DPL11ST));
	}
	return(ret);
}

static kint32 ctStopDdr_Pll11(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.DPL11ST = 1;
#endif
	dd_topthree_stop_ddr_pll11();
	Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.DPL11ST = %d\n", IO_CHIPTOP.PLLCNT1.bit.DPL11ST));
	return(D_DDIM_OK);
}

static kint32 ctStartDdrPll12(void)
{
	kint32 ret;

#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.DPL12ST = 0;
#endif
	ret = dd_topthree_start_ddr_pll12();
	if( ret == D_DDIM_OK ){
		Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.DPL12ST = %d\n", IO_CHIPTOP.PLLCNT1.bit.DPL12ST));
	}
	return(ret);
}

static kint32 ctStopDdr_Pll12(void)
{
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.DPL12ST = 1;
#endif
	dd_topthree_stop_ddr_pll12();
	Ddim_Print(("IO_CHIPTOP.PLLCNT1.bit.DPL12ST = %d\n", IO_CHIPTOP.PLLCNT1.bit.DPL12ST));
	return(D_DDIM_OK);
}
/****************
* PUBLIC
*/
void ct_pll_control(CtPll *self)
{
    kint32 result;
	CtPllPrivate *priv = CT_PLL_GET_PRIVATE(self);  

    if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "pll00" ) ) {
			if ( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "start" ) ) {
				result = ctStartPll00();
				Ddim_Print(("PLL00 START = %d\n", result));
			}
			else if ( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "stop" )) {
				result = ctStopPll00();
				Ddim_Print(("PLL00 STOP\n"));
			}
			else {
				Ddim_Print(("please check 3rd parameter!!\n"));
			}
		}
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "pll01" ) ) {
        if ( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "start" ) ) {
            result = ctStartPll01();
            Ddim_Print(("PLL01 START = %d\n", result));
        }
        else if ( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "stop" )) {
            result = ctStopPll01();
            Ddim_Print(("PLL01 STOP\n"));
        }
        else {
            Ddim_Print(("please check 3rd parameter!!\n"));
        }
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "pll02" ) ) {
        if ( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "start" ) ) {
            result = ctStartPll02();
            Ddim_Print(("PLL02 START = %d\n", result));
        }
        else if ( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "stop" )) {
            result = ctStopPll02();
            Ddim_Print(("PLL02 STOP\n"));
        }
        else {
            Ddim_Print(("please check 3rd parameter!!\n"));
        }
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "pll03" ) ) {
        if ( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "start" ) ) {
            result = ctStartPll03();
            Ddim_Print(("PLL03 START = %d\n", result));
        }
        else if ( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "stop" )) {
            result = ctStopPll03();
            Ddim_Print(("PLL03 STOP\n"));
        }
        else {
            Ddim_Print(("please check 3rd parameter!!\n"));
        }
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "pll04" ) ) {
        if ( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "start" ) ) {
            result = ctStartPll04();
            Ddim_Print(("PLL04 START = %d\n", result));
        }
        else if ( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "stop" )) {
            result = ctStopPll04();
            Ddim_Print(("PLL04 STOP\n"));
        }
        else {
            Ddim_Print(("please check 3rd parameter!!\n"));
        }
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "pll05" ) ) {
        if ( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "start" ) ) {
            result = ctStartPll05();
            Ddim_Print(("PLL05 START = %d\n", result));
        }
        else if ( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "stop" )) {
            result = ctStopPll05();
            Ddim_Print(("PLL05 STOP\n"));
        }
        else {
            Ddim_Print(("please check 3rd parameter!!\n"));
        }
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "pll05a" ) ) {
        if ( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "start" ) ) {
            result = ctStartPll05A();
            Ddim_Print(("PLL05A START = %d\n", result));
        }
        else if ( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "stop" )) {
            result = ctStopPll05A();
            Ddim_Print(("PLL05A STOP\n"));
        }
        else {
            Ddim_Print(("please check 3rd parameter!!\n"));
        }
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "pll06" ) ) {
        if ( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "start" ) ) {
            result = ctStartPll06();
            Ddim_Print(("PLL06 START = %d\n", result));
        }
        else if ( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "stop" )) {
            result = ctStopPll06();
            Ddim_Print(("PLL06 STOP\n"));
        }
        else {
            Ddim_Print(("please check 3rd parameter!!\n"));
        }
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "pll07" ) ) {
        if ( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "start" ) ) {
            result = ctStartPll07();
            Ddim_Print(("PLL07 START = %d\n", result));
        }
        else if ( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "stop" )) {
            result = ctStopPll07();
            Ddim_Print(("PLL07 STOP\n"));
        }
        else {
            Ddim_Print(("please check 3rd parameter!!\n"));
        }
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "pll08" ) ) {
        if ( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "start" ) ) {
            result = ctStartPll08();
            Ddim_Print(("PLL08 START = %d\n", result));
        }
        else if ( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "stop" )) {
            result = ctStopPll08();
            Ddim_Print(("PLL08 STOP\n"));
        }
        else {
            Ddim_Print(("please check 3rd parameter!!\n"));
        }
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "pll10" ) ) {
        if ( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "start" ) ) {
            result = ctStartPll10();
            Ddim_Print(("PLL10 START = %d\n", result));
        }
        else if ( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "stop" )) {
            result = ctStopPll10();
            Ddim_Print(("PLL10 STOP\n"));
        }
        else {
            Ddim_Print(("please check 3rd parameter!!\n"));
        }
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "pll10a" ) ) {
        if ( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "start" ) ) {
            result = ctStartPll10A();
            Ddim_Print(("PLL10A START = %d\n", result));
        }
        else if ( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "stop" )) {
            result = ctStopPll10A();
            Ddim_Print(("PLL10A STOP\n"));
        }
        else {
            Ddim_Print(("please check 3rd parameter!!\n"));
        }
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "pll11" ) ) {
        if ( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "start" ) ) {
            result = ctStartPll11();
            Ddim_Print(("PLL11 START = %d\n", result));
        }
        else if ( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "stop" )) {
            result = ctStopPll11();
            Ddim_Print(("PLL11 STOP\n"));
        }
        else {
            Ddim_Print(("please check 3rd parameter!!\n"));
        }
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "ddr00" ) ) {
        if ( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "start" ) ) {
            result = ctStartDdrPll00();
            Ddim_Print(("DDR PLL00 START = %d\n", result));
        }
        else if ( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "stop" )) {
            result = ctStopDdr_Pll00();
            Ddim_Print(("DDR PLL00 STOP\n"));
        }
        else {
            Ddim_Print(("please check 3rd parameter!!\n"));
        }
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "ddr01" ) ) {
        if ( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "start" ) ) {
            result = ctStartDdrPll01();
            Ddim_Print(("DDR PLL01 START = %d\n", result));
        }
        else if ( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "stop" )) {
            result = ctStopDdr_Pll01();
            Ddim_Print(("DDR PLL01 STOP\n"));
        }
        else {
            Ddim_Print(("please check 3rd parameter!!\n"));
        }
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "ddr02" ) ) {
        if ( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "start" ) ) {
            result = ctStartDdrPll02();
            Ddim_Print(("DDR PLL02 START = %d\n", result));
        }
        else if ( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "stop" )) {
            result = ctStopDdr_Pll02();
            Ddim_Print(("DDR PLL02 STOP\n"));
        }
        else {
            Ddim_Print(("please check 3rd parameter!!\n"));
        }
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "ddr10" ) ) {
        if ( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "start" ) ) {
            result = ctStartDdrPll10();
            Ddim_Print(("DDR PLL10 START = %d\n", result));
        }
        else if ( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "stop" )) {
            result = ctStopDdr_Pll10();
            Ddim_Print(("DDR PLL10 STOP\n"));
        }
        else {
            Ddim_Print(("please check 3rd parameter!!\n"));
        }
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "ddr11" ) ) {
        if ( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "start" ) ) {
            result = ctStartDdrPll11();
            Ddim_Print(("DDR PLL11 START = %d\n", result));
        }
        else if ( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "stop" )) {
            result = ctStopDdr_Pll11();
            Ddim_Print(("DDR PLL11 STOP\n"));
        }
        else {
            Ddim_Print(("please check 3rd parameter!!\n"));
        }
    }
    else if( 0 == strcmp( ((CtDdParameter *)self)->argv[2], "ddr12" ) ) {
        if ( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "start" ) ) {
            result = ctStartDdrPll12();
            Ddim_Print(("DDR PLL12 START = %d\n", result));
        }
        else if ( 0 == strcmp( ((CtDdParameter *)self)->argv[3], "stop" )) {
            result = ctStopDdr_Pll12();
            Ddim_Print(("DDR PLL12 STOP\n"));
        }
        else {
            Ddim_Print(("please check 3rd parameter!!\n"));
        }
    }else {
		ct_dd_parameter_set_parameter((CtDdParameter *)priv->ctSetPll,
				((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
		ct_set_pll_control(priv->ctSetPll);
	}
}

CtPll* ct_pll_new(void) 
{
    CtPll *self = k_object_new_with_private(CT_TYPE_PLL, sizeof(CtPllPrivate));
    return self;
}
