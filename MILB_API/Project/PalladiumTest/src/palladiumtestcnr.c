/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-08-04
*@author              :郭江龙
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年06月开始开发
*/
#include <string.h>
#include "ddimusercustom.h"
#include "palladium_test.h"
#include "palladium_test_common.h"
#include "palladiumtestinterrupta.h"
#include "palladiumtestinterruptb.h"
#include "palladiumtestinterruptc.h"
//#include "_timer.h"
#include "ddgic.h"
#include "ddtop.h"
#include "imcnr.h"
#include "imrdma.h"
#include "jdscnr.h"
#include "palladiumtestcnr.h"
#include "palladiumtestcnr1.h"
#include "palladiumtestcnr2.h"
#include "kjdscnr1a.h"
#include "_jdscnr_ofl_reg_rw.h"


K_TYPE_DEFINE_WITH_PRIVATE(PalladiumTestCnr, palladium_test_cnr);
#define PALLADIUM_TEST_CNR_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), PalladiumTestCnrPrivate, PALLADIUM_TYPE_TEST_CNR))

// Src address(YCC422 Planar format)
#define PalladiumTestCnr_D_IM_IMG_SRC_Y_ADDR	    (PalladiumTestCnr_D_IM_IMG_SRC_ADDR)
#define PalladiumTestCnr_D_IM_IMG_SRC_CB_ADDR	(PalladiumTestCnr_D_IM_IMG_SRC_ADDR + PalladiumTestCnr_D_IM_CNR_TEST_H_PIXS * PalladiumTestCnr_D_IM_CNR_TEST_V_PIXS)				// 0x4804B000
#define PalladiumTestCnr_D_IM_IMG_SRC_CR_ADDR	(PalladiumTestCnr_D_IM_IMG_SRC_CB_ADDR + ((PalladiumTestCnr_D_IM_CNR_TEST_H_PIXS * PalladiumTestCnr_D_IM_CNR_TEST_V_PIXS) / 2))	// 0x48070800
#define PalladiumTestCnr_D_IM_IMG_SRC_BYTES		    (PalladiumTestCnr_D_IM_CNR_TEST_H_PIXS * PalladiumTestCnr_D_IM_CNR_TEST_V_PIXS * 2)										// 0x96000
// Dst address(YCC422 Planar format)
#define PalladiumTestCnr_D_IM_IMG_DST_ADDR		     (PalladiumTestCnr_D_IM_IMG_SRC_ADDR + PalladiumTestCnr_D_IM_IMG_SRC_BYTES)								// 0x48096000
#define PalladiumTestCnr_D_IM_IMG_DST_Y_ADDR	     (PalladiumTestCnr_D_IM_IMG_DST_ADDR)
#define PalladiumTestCnr_D_IM_IMG_DST_CB_ADDR	 (PalladiumTestCnr_D_IM_IMG_DST_ADDR + PalladiumTestCnr_D_IM_CNR_TEST_H_PIXS * PalladiumTestCnr_D_IM_CNR_TEST_V_PIXS)				// 0x480E1000
#define PalladiumTestCnr_D_IM_IMG_DST_CR_ADDR	 (PalladiumTestCnr_D_IM_IMG_DST_CB_ADDR + PalladiumTestCnr_D_IM_CNR_TEST_H_PIXS * PalladiumTestCnr_D_IM_CNR_TEST_V_PIXS /2)		// 0x48106800
#define PalladiumTestCnr_D_IM_IMG_DST_BYTES		     (PalladiumTestCnr_D_IM_CNR_TEST_H_PIXS * PalladiumTestCnr_D_IM_CNR_TEST_V_PIXS * 2)										// 0x96000
// Temporary address(for CNR macro use)
#define PalladiumTestCnr_D_IM_IMG_TMP_ADDR		     (PalladiumTestCnr_D_IM_IMG_DST_ADDR + PalladiumTestCnr_D_IM_IMG_DST_BYTES)								// 0x4812C000
//#define PalladiumTestCnr_D_IM_IMG_TMP_ADDR		(0x30000000UL)																			// 0x30000000
#define PalladiumTestCnr_D_IM_IMG_TMP_BYTES		 (PalladiumTestCnr_D_IM_CNR_TEST_V_PIXS * 576)															// 0x43800
#define	PalladiumTestCnr_IO_CNR(ch)		                         ((D_IM_CNR_CH_0 == ((ch))) ? &ioCnr1 : (D_IM_CNR_CH_1 == ((ch))) ? &ioCnr2 : &ioCnr3)
#define PalladiumTestCnr_D_IM_IMG_SRC_ADDR	         (0x48000000UL)
#define PalladiumTestCnr_D_IM_CNR_TEST_H_PIXS     	 (640)
#define PalladiumTestCnr_D_IM_CNR_TEST_V_PIXS	     (480)
#undef  PalladiumTestCnr_D_IM_CNR_TEST_NO
#define PalladiumTestCnr_D_IM_CNR_TEST_NO "1_1"
#define PalladiumTestCnr_D_IM_CNR_TEST_NO "1_2"
#define PalladiumTestCnr_D_IM_CNR_TEST_NO "1_3"

static kuchar S_GIM_CNR_CLK_CTRL_CNT1;
static kuchar S_GIM_CNR_CLK_CTRL_CNT2;
static kuchar S_GIM_CNR_ICLK_CTRL_CNT1;
static kuchar S_GIM_CNR_ICLK_CTRL_CNT2;

static void                   ptImCnrOflRegRwPrint( kuchar ch );
static void                   ptImCnrOtfRegRwPrint( kuchar ch );
static void                   ptImCnrOflCsprRegPrint( kuchar ch );
static void                   ptImCnrOtfCsprRegPrint( kuchar ch );
static void                   ptImCnrOflYsprRegPrint( kuchar ch );
static void                   ptImCnrOflYsprTblRegPrint( kuchar ch );
static void                   ptImCnrOflCsprMidYRegPrint( kuchar ch );
static void                   ptImCnrOtfCsprMidYRegPrint( kuchar ch );
static void                   ptImCnrOflCsprMidCcYRegPrint( kuchar ch );
static void                   ptImCnrOtfCsprMidCcYRegPrint( kuchar ch );
static void                   ptImCnrOflCsprMidCcCRegPrint( kuchar ch );
static void                   ptImCnrOtfCsprMidCcCRegPrint( kuchar ch );
static void                   ptImCnrOflCsprLowYRegPrint( kuchar ch );
static void                   ptImCnrOtfCsprLowYRegPrint( kuchar ch );
static void                   ptImCnrOflCsprLowCcYRegPrint( kuchar ch );
static void                   ptImCnrOtfCsprLowCcYRegPrint( kuchar ch );
static void                   ptImCnrOflCsprLowCcCCRegPrint( kuchar ch );
static void                   ptImCnrOtfCsprLowCcCRegPrint( kuchar ch );
static void                   ptImCnrOflCsprEdgeRegPrint( kuchar ch );
static void                   ptImCnrOtfCsprEdgeRegPrint( kuchar ch );
static void                   ptImCnrOflCsprHueRegPrint( kuchar ch );
static void                   ptImCnrOtfCsprHueRegPrint( kuchar ch );
static void                   ptImCnrOflCsprSprsRegPrint( kuchar ch );
static void                   ptImCnrOtfCsprSprsRegPrint( kuchar ch );
static void                   ptImCnrOtfCsprSprdRegPrint( kuchar ch );
static void                   ptImCnrOfl11( kuchar ch );
static void                   ptImCnrOtf11( kuchar ch );
static void                   ptImCnrOfl12( kuchar ch );
static void                   ptImCnrOtf12( kuchar ch );
static void                   ptImCnrOfl13( kuchar ch );
static void                   ptImCnrOtf13( kuchar ch );

struct _PalladiumTestCnrPrivate
{
	kint a;
};

static void palladium_test_cnr_constructor(PalladiumTestCnr* self)
{
	PalladiumTestCnrPrivate* priv = PALLADIUM_TEST_CNR_GET_PRIVATE(self);
priv->a = 0;
}

static void palladium_test_cnr_destructor(PalladiumTestCnr* self)
{
	PalladiumTestCnrPrivate* priv = PALLADIUM_TEST_CNR_GET_PRIVATE(self);
priv->a = 0;
}

static void ptImCnrOflRegRwPrint( kuchar ch )
{
	Ddim_Print(("oflRegRw ch%d print -----------\n", ch ));
	Im_CNR_On_Pclk( ch );
	Ddim_Print(("PalladiumTestCnr_IO_CNR(%d)->oflRegRw.SPRSR.word     = 0x%lx\n", ch, PalladiumTestCnr_IO_CNR(ch)->oflRegRw.SPRSR.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(%d)->oflRegRw.ACESEN.word    = 0x%lx\n", ch, PalladiumTestCnr_IO_CNR(ch)->oflRegRw.ACESEN.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(%d)->oflRegRw.SPRTRG.word    = 0x%lx\n", ch, PalladiumTestCnr_IO_CNR(ch)->oflRegRw.SPRTRG.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(%d)->oflRegRw.SPRICE.word    = 0x%lx\n", ch, PalladiumTestCnr_IO_CNR(ch)->oflRegRw.SPRICE.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(%d)->oflRegRw.SPRICF.word    = 0x%lx\n", ch, PalladiumTestCnr_IO_CNR(ch)->oflRegRw.SPRICF.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(%d)->oflRegRw.VDIV.word      = 0x%lx\n", ch, PalladiumTestCnr_IO_CNR(ch)->oflRegRw.VDIV.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(%d)->oflRegRw.SPRAXISET.word = 0x%lx\n", ch, PalladiumTestCnr_IO_CNR(ch)->oflRegRw.SPRAXISET.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(%d)->oflRegRw.SPRMOD.word    = 0x%lx\n", ch, PalladiumTestCnr_IO_CNR(ch)->oflRegRw.SPRMOD.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(%d)->oflRegRw.HSIZE.word     = 0x%lx\n", ch, PalladiumTestCnr_IO_CNR(ch)->oflRegRw.HSIZE.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(%d)->oflRegRw.VSIZE.word     = 0x%lx\n", ch, PalladiumTestCnr_IO_CNR(ch)->oflRegRw.VSIZE.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(%d)->oflRegRw.RYTA.word      = 0x%lx\n", ch, PalladiumTestCnr_IO_CNR(ch)->oflRegRw.RYTA.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(%d)->oflRegRw.RYDEF.word     = 0x%lx\n", ch, PalladiumTestCnr_IO_CNR(ch)->oflRegRw.RYDEF.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(%d)->oflRegRw.RCBTA.word     = 0x%lx\n", ch, PalladiumTestCnr_IO_CNR(ch)->oflRegRw.RCBTA.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(%d)->oflRegRw.RCRTA.word     = 0x%lx\n", ch, PalladiumTestCnr_IO_CNR(ch)->oflRegRw.RCRTA.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(%d)->oflRegRw.RCDEF.word     = 0x%lx\n", ch, PalladiumTestCnr_IO_CNR(ch)->oflRegRw.RCDEF.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(%d)->oflRegRw.WYTA.word      = 0x%lx\n", ch, PalladiumTestCnr_IO_CNR(ch)->oflRegRw.WYTA.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(%d)->oflRegRw.WYDEF.word     = 0x%lx\n", ch, PalladiumTestCnr_IO_CNR(ch)->oflRegRw.WYDEF.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(%d)->oflRegRw.WCBTA.word     = 0x%lx\n", ch, PalladiumTestCnr_IO_CNR(ch)->oflRegRw.WCBTA.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(%d)->oflRegRw.WCRTA.word     = 0x%lx\n", ch, PalladiumTestCnr_IO_CNR(ch)->oflRegRw.WCRTA.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(%d)->oflRegRw.WCDEF.word     = 0x%lx\n", ch, PalladiumTestCnr_IO_CNR(ch)->oflRegRw.WCDEF.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(%d)->oflRegRw.TMPTA.word     = 0x%lx\n", ch, PalladiumTestCnr_IO_CNR(ch)->oflRegRw.TMPTA.word ));
	Im_CNR_Off_Pclk( ch );
}

static void ptImCnrOtfRegRwPrint( kuchar ch )
{
	Ddim_Print(("otfRegRw ch%d print -----------\n", ch ));
	Im_CNR_On_Pclk( ch );
	Ddim_Print(("PalladiumTestCnr_IO_CNR(%d)->otfRegRw.SPRSR.word     = 0x%lx\n", ch, PalladiumTestCnr_IO_CNR(ch)->otfRegRw.SPRSR.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(%d)->otfRegRw.ACESEN.word    = 0x%lx\n", ch, PalladiumTestCnr_IO_CNR(ch)->otfRegRw.ACESEN.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(%d)->otfRegRw.SPRTRG.word    = 0x%lx\n", ch, PalladiumTestCnr_IO_CNR(ch)->otfRegRw.SPRTRG.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(%d)->otfRegRw.SPRICE.word    = 0x%lx\n", ch, PalladiumTestCnr_IO_CNR(ch)->otfRegRw.SPRICE.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(%d)->otfRegRw.SPRICF.word    = 0x%lx\n", ch, PalladiumTestCnr_IO_CNR(ch)->otfRegRw.SPRICF.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(%d)->otfRegRw.HDIV.word      = 0x%lx\n", ch, PalladiumTestCnr_IO_CNR(ch)->otfRegRw.HDIV.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(%d)->otfRegRw.SPRAXISET.word = 0x%lx\n", ch, PalladiumTestCnr_IO_CNR(ch)->otfRegRw.SPRAXISET.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(%d)->otfRegRw.SPRMOD.word    = 0x%lx\n", ch, PalladiumTestCnr_IO_CNR(ch)->otfRegRw.SPRMOD.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(%d)->otfRegRw.HSIZE.word     = 0x%lx\n", ch, PalladiumTestCnr_IO_CNR(ch)->otfRegRw.HSIZE.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(%d)->otfRegRw.VSIZE.word     = 0x%lx\n", ch, PalladiumTestCnr_IO_CNR(ch)->otfRegRw.VSIZE.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(%d)->otfRegRw.WCTA.word      = 0x%lx\n", ch, PalladiumTestCnr_IO_CNR(ch)->otfRegRw.WCTA.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(%d)->otfRegRw.WCDEF.word     = 0x%lx\n", ch, PalladiumTestCnr_IO_CNR(ch)->otfRegRw.WCDEF.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(%d)->otfRegRw.CNRWOFSX.word  = 0x%lx\n", ch, PalladiumTestCnr_IO_CNR(ch)->otfRegRw.CNRWOFSX.word ));
	Im_CNR_Off_Pclk( ch );
}

static void ptImCnrOflCsprRegPrint( kuchar ch )
{
	Ddim_Print(("oflCsprReg ch%d print -----------\n", ch ));
	Im_CNR_On_Pclk( ch );
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.CSPREN.word   = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.CSPREN.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.CGDKEN.word   = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.CGDKEN.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCEN.word     = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCEN.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCYTHH.word   = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCYTHH.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCYTHV.word   = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCYTHV.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCCTHH.word   = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCCTHH.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCCTHV.word   = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCCTHV.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCYDYM.word   = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCYDYM.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCYDYMDT.word = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCYDYMDT.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCYSCL.word   = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCYSCL.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCSSCL.word   = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCSSCL.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCCSCL.word   = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCCSCL.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCEN.word     = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCEN.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCYTHH.word   = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCYTHH.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCYTHV.word   = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCYTHV.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCCTHH.word   = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCCTHH.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCCTHV.word   = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCCTHV.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCYDYM.word   = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCYDYM.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCYDYMDT.word = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCYDYMDT.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCYSCL.word   = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCYSCL.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCSSCL.word   = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCSSCL.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCCSCL.word   = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCCSCL.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.WHTMD.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.WHTMD.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.BLEND.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.BLEND.word ));
	Im_CNR_Off_Pclk( ch );
}

static void ptImCnrOtfCsprRegPrint( kuchar ch )
{
	Ddim_Print(("otfCsprReg ch%d print -----------\n", ch ));
	Im_CNR_On_Pclk( ch );
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.CSPREN.word   = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.CSPREN.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.CGDKEN.word   = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.CGDKEN.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCEN.word     = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCEN.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCYTHH.word   = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCYTHH.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCYTHV.word   = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCYTHV.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCCTHH.word   = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCCTHH.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCCTHV.word   = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCCTHV.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCYDYM.word   = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCYDYM.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCYDYMDT.word = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCYDYMDT.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCYSCL.word   = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCYSCL.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCSSCL.word   = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCSSCL.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCCSCL.word   = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCCSCL.word ));

	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCEN.word     = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCEN.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCYTHH.word   = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCYTHH.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCYTHV.word   = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCYTHV.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCCTHH.word   = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCCTHH.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCCTHV.word   = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCCTHV.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCYDYM.word   = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCYDYM.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCYDYMDT.word = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCYDYMDT.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCYSCL.word   = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCYSCL.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCSSCL.word   = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCSSCL.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCCSCL.word   = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCCSCL.word ));

	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.WHTMD.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.WHTMD.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.BLEND.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.BLEND.word ));
	Im_CNR_Off_Pclk( ch );
}

static void ptImCnrOflYsprRegPrint( kuchar ch )
{
	Ddim_Print(("OFL_YSPR_REG ch%d print -----------\n", ch ));
	Im_CNR_On_Pclk( ch );
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->OFL_REG_YSPR.YSPREN.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->OFL_REG_YSPR.YSPREN.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->OFL_REG_YSPR.YSPRMODE.word  = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->OFL_REG_YSPR.YSPRMODE.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->OFL_REG_YSPR.YSPRFXEY.word  = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->OFL_REG_YSPR.YSPRFXEY.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->OFL_REG_YSPR.YSPRFXEC.word  = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->OFL_REG_YSPR.YSPRFXEC.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->OFL_REG_YSPR.YSPRALPBD.word = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->OFL_REG_YSPR.YSPRALPBD.word ));
	Im_CNR_Off_Pclk( ch );
}

static void ptImCnrOflYsprTblRegPrint( kuchar ch )
{
	Ddim_Print(("OFL_YSPR_TABLE REG ch%d print -----------\n", ch ));
	Im_CNR_On_Pclk( ch );
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYBD.YSPRDYEYBD1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYBD.YSPRDYEYBD1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYBD.YSPRDYEYBD2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYBD.YSPRDYEYBD2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYOF.YSPRDYEYOF1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYOF.YSPRDYEYOF1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYOF.YSPRDYEYOF2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYOF.YSPRDYEYOF2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYGA.YSPRDYEYGA1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYGA.YSPRDYEYGA1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYGA.YSPRDYEYGA2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYGA.YSPRDYEYGA2.word ));
	Im_CNR_Off_Pclk( ch );
}

static void ptImCnrOflCsprMidYRegPrint( kuchar ch )
{
	Ddim_Print(("OFL_CSPR_MID_Y_TABLE REG ch%d print -----------\n", ch ));
	Im_CNR_On_Pclk( ch );
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCYSCLBD.MCYSCLBD1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCYSCLBD.MCYSCLBD1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCYSCLBD.MCYSCLBD2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCYSCLBD.MCYSCLBD2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCYSCLOF.MCYSCLOF1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCYSCLOF.MCYSCLOF1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCYSCLOF.MCYSCLOF2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCYSCLOF.MCYSCLOF2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCYSCLGA.MCYSCLGA1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCYSCLGA.MCYSCLGA1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCYSCLGA.MCYSCLGA2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCYSCLGA.MCYSCLGA2.word ));
	Im_CNR_Off_Pclk( ch );
}

static void ptImCnrOtfCsprMidYRegPrint( kuchar ch )
{
	Ddim_Print(("OTF_CSPR_MID_Y_TABLE REG ch%d print -----------\n", ch ));
	Im_CNR_On_Pclk( ch );
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCYSCLBD.MCYSCLBD1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCYSCLBD.MCYSCLBD1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCYSCLBD.MCYSCLBD2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCYSCLBD.MCYSCLBD2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCYSCLOF.MCYSCLOF1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCYSCLOF.MCYSCLOF1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCYSCLOF.MCYSCLOF2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCYSCLOF.MCYSCLOF2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCYSCLGA.MCYSCLGA1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCYSCLGA.MCYSCLGA1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCYSCLGA.MCYSCLGA2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCYSCLGA.MCYSCLGA2.word ));
	Im_CNR_Off_Pclk( ch );
}

static void ptImCnrOflCsprMidCcYRegPrint( kuchar ch )
{
	Ddim_Print(("OFL_CSPR_MID_CC_Y_TABLE REG ch%d print -----------\n", ch ));
	Im_CNR_On_Pclk( ch );
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCCSCLBD.MCCSCLBD1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCCSCLBD.MCCSCLBD1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCCSCLBD.MCCSCLBD2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCCSCLBD.MCCSCLBD2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCCSCLOF.MCCSCLOF1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCCSCLOF.MCCSCLOF1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCCSCLOF.MCCSCLOF2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCCSCLOF.MCCSCLOF2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCCSCLGA.MCCSCLGA1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCCSCLGA.MCCSCLGA1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCCSCLGA.MCCSCLGA2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCCSCLGA.MCCSCLGA2.word ));
	Im_CNR_Off_Pclk( ch );
}

static void ptImCnrOtfCsprMidCcYRegPrint( kuchar ch )
{
	Ddim_Print(("OTF_CSPR_MID_CC_Y_TABLE REG ch%d print -----------\n", ch ));
	Im_CNR_On_Pclk( ch );
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCCSCLBD.MCCSCLBD1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCCSCLBD.MCCSCLBD1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCCSCLBD.MCCSCLBD2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCCSCLBD.MCCSCLBD2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCCSCLOF.MCCSCLOF1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCCSCLOF.MCCSCLOF1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCCSCLOF.MCCSCLOF2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCCSCLOF.MCCSCLOF2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCCSCLGA.MCCSCLGA1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCCSCLGA.MCCSCLGA1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCCSCLGA.MCCSCLGA2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCCSCLGA.MCCSCLGA2.word ));
	Im_CNR_Off_Pclk( ch );
}

static void ptImCnrOflCsprMidCcCRegPrint( kuchar ch )
{
	Ddim_Print(("OFL_CSPR_MID_CC_C_TABLE REG ch%d print -----------\n", ch ));
	Im_CNR_On_Pclk( ch );
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCSSCLBD.MCSSCLBD1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCSSCLBD.MCSSCLBD1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCSSCLBD.MCSSCLBD2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCSSCLBD.MCSSCLBD2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCSSCLOF.MCSSCLOF1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCSSCLOF.MCSSCLOF1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCSSCLOF.MCSSCLOF2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCSSCLOF.MCSSCLOF2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCSSCLGA.MCSSCLGA1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCSSCLGA.MCSSCLGA1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCSSCLGA.MCSSCLGA2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.MCSSCLGA.MCSSCLGA2.word ));
	Im_CNR_Off_Pclk( ch );
}

static void ptImCnrOtfCsprMidCcCRegPrint( kuchar ch )
{
	Ddim_Print(("OTF_CSPR_MID_CC_C_TABLE REG ch%d print -----------\n", ch ));
	Im_CNR_On_Pclk( ch );
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCSSCLBD.MCSSCLBD1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCSSCLBD.MCSSCLBD1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCSSCLBD.MCSSCLBD2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCSSCLBD.MCSSCLBD2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCSSCLOF.MCSSCLOF1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCSSCLOF.MCSSCLOF1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCSSCLOF.MCSSCLOF2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCSSCLOF.MCSSCLOF2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCSSCLGA.MCSSCLGA1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCSSCLGA.MCSSCLGA1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCSSCLGA.MCSSCLGA2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.MCSSCLGA.MCSSCLGA2.word ));
	Im_CNR_Off_Pclk( ch );
}

static void ptImCnrOflCsprLowYRegPrint( kuchar ch )
{
	Ddim_Print(("OFL_CSPR_LOW_Y_TABLE REG ch%d print -----------\n", ch ));
	Im_CNR_On_Pclk( ch );
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCYSCLBD.LCYSCLBD1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCYSCLBD.LCYSCLBD1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCYSCLBD.LCYSCLBD2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCYSCLBD.LCYSCLBD2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCYSCLOF.LCYSCLOF1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCYSCLOF.LCYSCLOF1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCYSCLOF.LCYSCLOF2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCYSCLOF.LCYSCLOF2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCYSCLGA.LCYSCLGA1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCYSCLGA.LCYSCLGA1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCYSCLGA.LCYSCLGA2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCYSCLGA.LCYSCLGA2.word ));
	Im_CNR_Off_Pclk( ch );
}

static void ptImCnrOtfCsprLowYRegPrint( kuchar ch )
{
	Ddim_Print(("OTF_CSPR_LOW_Y_TABLE REG ch%d print -----------\n", ch ));
	Im_CNR_On_Pclk( ch );
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCYSCLBD.LCYSCLBD1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCYSCLBD.LCYSCLBD1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCYSCLBD.LCYSCLBD2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCYSCLBD.LCYSCLBD2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCYSCLOF.LCYSCLOF1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCYSCLOF.LCYSCLOF1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCYSCLOF.LCYSCLOF2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCYSCLOF.LCYSCLOF2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCYSCLGA.LCYSCLGA1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCYSCLGA.LCYSCLGA1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCYSCLGA.LCYSCLGA2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCYSCLGA.LCYSCLGA2.word ));
	Im_CNR_Off_Pclk( ch );
}

static void ptImCnrOflCsprLowCcYRegPrint( kuchar ch )
{
	Ddim_Print(("OFL_CSPR_LOW_CC_Y_TABLE REG ch%d print -----------\n", ch ));
	Im_CNR_On_Pclk( ch );
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCCSCLBD.LCCSCLBD1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCCSCLBD.LCCSCLBD1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCCSCLBD.LCCSCLBD2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCCSCLBD.LCCSCLBD2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCCSCLOF.LCCSCLOF1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCCSCLOF.LCCSCLOF1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCCSCLOF.LCCSCLOF2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCCSCLOF.LCCSCLOF2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCCSCLGA.LCCSCLGA1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCCSCLGA.LCCSCLGA1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCCSCLGA.LCCSCLGA2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCCSCLGA.LCCSCLGA2.word ));
	Im_CNR_Off_Pclk( ch );
}

static void ptImCnrOtfCsprLowCcYRegPrint( kuchar ch )
{
	Ddim_Print(("OTF_CSPR_LOW_CC_Y_TABLE REG ch%d print -----------\n", ch ));
	Im_CNR_On_Pclk( ch );
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCCSCLBD.LCCSCLBD1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCCSCLBD.LCCSCLBD1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCCSCLBD.LCCSCLBD2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCCSCLBD.LCCSCLBD2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCCSCLOF.LCCSCLOF1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCCSCLOF.LCCSCLOF1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCCSCLOF.LCCSCLOF2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCCSCLOF.LCCSCLOF2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCCSCLGA.LCCSCLGA1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCCSCLGA.LCCSCLGA1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCCSCLGA.LCCSCLGA2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCCSCLGA.LCCSCLGA2.word ));
	Im_CNR_Off_Pclk( ch );
}

static void ptImCnrOflCsprLowCcCCRegPrint( kuchar ch )
{
	Ddim_Print(("OFL_CSPR_LOW_CC_C_TABLE REG ch%d print -----------\n", ch ));
	Im_CNR_On_Pclk( ch );
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCSSCLBD.LCSSCLBD1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCSSCLBD.LCSSCLBD1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCSSCLBD.LCSSCLBD2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCSSCLBD.LCSSCLBD2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCSSCLOF.LCSSCLOF1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCSSCLOF.LCSSCLOF1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCSSCLOF.LCSSCLOF2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCSSCLOF.LCSSCLOF2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCSSCLGA.LCSSCLGA1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCSSCLGA.LCSSCLGA1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCSSCLGA.LCSSCLGA2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.LCSSCLGA.LCSSCLGA2.word ));
	Im_CNR_Off_Pclk( ch );
}

static void ptImCnrOtfCsprLowCcCRegPrint( kuchar ch )
{
	Ddim_Print(("OTF_CSPR_LOW_CC_C_TABLE REG ch%d print -----------\n", ch ));
	Im_CNR_On_Pclk( ch );
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCSSCLBD.LCSSCLBD1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCSSCLBD.LCSSCLBD1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCSSCLBD.LCSSCLBD2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCSSCLBD.LCSSCLBD2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCSSCLOF.LCSSCLOF1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCSSCLOF.LCSSCLOF1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCSSCLOF.LCSSCLOF2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCSSCLOF.LCSSCLOF2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCSSCLGA.LCSSCLGA1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCSSCLGA.LCSSCLGA1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCSSCLGA.LCSSCLGA2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.LCSSCLGA.LCSSCLGA2.word ));
	Im_CNR_Off_Pclk( ch );
}

static void ptImCnrOflCsprEdgeRegPrint( kuchar ch )
{
	Ddim_Print(("OFL_CSPR_EDGE_TABLE REG ch%d print -----------\n", ch ));
	Im_CNR_On_Pclk( ch );
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.CESCLBD.CESCLBD1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.CESCLBD.CESCLBD1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.CESCLBD.CESCLBD2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.CESCLBD.CESCLBD2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.CESCLOF.CESCLOF1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.CESCLOF.CESCLOF1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.CESCLOF.CESCLOF2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.CESCLOF.CESCLOF2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.CESCLGA.CESCLGA1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.CESCLGA.CESCLGA1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.CESCLGA.CESCLGA2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.CESCLGA.CESCLGA2.word ));
	Im_CNR_Off_Pclk( ch );
}

static void ptImCnrOtfCsprEdgeRegPrint( kuchar ch )
{
	Ddim_Print(("OTF_CSPR_EDGE_TABLE REG ch%d print -----------\n", ch ));
	Im_CNR_On_Pclk( ch );
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.CESCLBD.CESCLBD1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.CESCLBD.CESCLBD1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.CESCLBD.CESCLBD2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.CESCLBD.CESCLBD2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.CESCLOF.CESCLOF1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.CESCLOF.CESCLOF1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.CESCLOF.CESCLOF2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.CESCLOF.CESCLOF2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.CESCLGA.CESCLGA1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.CESCLGA.CESCLGA1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.CESCLGA.CESCLGA2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.CESCLGA.CESCLGA2.word ));
	Im_CNR_Off_Pclk( ch );
}

static void ptImCnrOflCsprHueRegPrint( kuchar ch )
{
	Ddim_Print(("OFL_CSPR_HUE_TABLE REG ch%d print -----------\n", ch ));
	Im_CNR_On_Pclk( ch );
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.CPHPT.word  = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.CPHPT.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.CPHPTK.word = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.CPHPTK.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.CDSCLBD.CDSCLBD1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.CDSCLBD.CDSCLBD1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.CDSCLBD.CDSCLBD2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.CDSCLBD.CDSCLBD2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.CDSCLBD.CDSCLBD3.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.CDSCLBD.CDSCLBD3.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.CDSCLOF.CDSCLOF1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.CDSCLOF.CDSCLOF1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.CDSCLOF.CDSCLOF2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.CDSCLOF.CDSCLOF2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.CDSCLOF.CDSCLOF3.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.CDSCLOF.CDSCLOF3.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.CDSCLGA.CDSCLGA1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.CDSCLGA.CDSCLGA1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.CDSCLGA.CDSCLGA2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.CDSCLGA.CDSCLGA2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.CDSCLGA.CDSCLGA3.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.CDSCLGA.CDSCLGA3.word ));
	Im_CNR_Off_Pclk( ch );
}

static void ptImCnrOtfCsprHueRegPrint( kuchar ch )
{
	Ddim_Print(("OTF_CSPR_HUE_TABLE REG ch%d print -----------\n", ch ));
	Im_CNR_On_Pclk( ch );
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.CPHPT.word  = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.CPHPT.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.CPHPTK.word = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.CPHPTK.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.CDSCLBD.CDSCLBD1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.CDSCLBD.CDSCLBD1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.CDSCLBD.CDSCLBD2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.CDSCLBD.CDSCLBD2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.CDSCLBD.CDSCLBD3.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.CDSCLBD.CDSCLBD3.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.CDSCLOF.CDSCLOF1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.CDSCLOF.CDSCLOF1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.CDSCLOF.CDSCLOF2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.CDSCLOF.CDSCLOF2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.CDSCLOF.CDSCLOF3.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.CDSCLOF.CDSCLOF3.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.CDSCLGA.CDSCLGA1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.CDSCLGA.CDSCLGA1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.CDSCLGA.CDSCLGA2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.CDSCLGA.CDSCLGA2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.CDSCLGA.CDSCLGA3.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.CDSCLGA.CDSCLGA3.word ));
	Im_CNR_Off_Pclk( ch );
}

static void ptImCnrOflCsprSprsRegPrint( kuchar ch )
{
	Ddim_Print(("OFL_CSPR_SPRS_TABLE REG ch%d print -----------\n", ch ));
	Im_CNR_On_Pclk( ch );
	// Cb
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRSCBBD.SPRSCBBD1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRSCBBD.SPRSCBBD1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRSCBBD.SPRSCBBD2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRSCBBD.SPRSCBBD2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRSCBOF.SPRSCBOF1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRSCBOF.SPRSCBOF1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRSCBOF.SPRSCBOF2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRSCBOF.SPRSCBOF2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRSCBGA.SPRSCBGA1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRSCBGA.SPRSCBGA1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRSCBGA.SPRSCBGA2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRSCBGA.SPRSCBGA2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRSCBGA.SPRSCBGA3.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRSCBGA.SPRSCBGA3.word ));
	// Cr
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRSCRBD.SPRSCRBD1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRSCRBD.SPRSCRBD1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRSCRBD.SPRSCRBD2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRSCRBD.SPRSCRBD2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRSCROF.SPRSCROF1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRSCROF.SPRSCROF1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRSCROF.SPRSCROF2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRSCROF.SPRSCROF2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRSCRGA.SPRSCRGA1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRSCRGA.SPRSCRGA1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRSCRGA.SPRSCRGA2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRSCRGA.SPRSCRGA2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRSCRGA.SPRSCRGA3.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRSCRGA.SPRSCRGA3.word ));
	Im_CNR_Off_Pclk( ch );
}

static void ptImCnrOtfCsprSprsRegPrint( kuchar ch )
{
	Ddim_Print(("OTF_CSPR_SPRS_TABLE REG ch%d print -----------\n", ch ));
	Im_CNR_On_Pclk( ch );
	// Cb
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRSCBBD.SPRSCBBD1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRSCBBD.SPRSCBBD1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRSCBBD.SPRSCBBD2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRSCBBD.SPRSCBBD2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRSCBOF.SPRSCBOF1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRSCBOF.SPRSCBOF1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRSCBOF.SPRSCBOF2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRSCBOF.SPRSCBOF2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRSCBGA.SPRSCBGA1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRSCBGA.SPRSCBGA1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRSCBGA.SPRSCBGA2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRSCBGA.SPRSCBGA2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRSCBGA.SPRSCBGA3.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRSCBGA.SPRSCBGA3.word ));
	// Cr
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRSCRBD.SPRSCRBD1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRSCRBD.SPRSCRBD1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRSCRBD.SPRSCRBD2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRSCRBD.SPRSCRBD2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRSCROF.SPRSCROF1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRSCROF.SPRSCROF1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRSCROF.SPRSCROF2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRSCROF.SPRSCROF2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRSCRGA.SPRSCRGA1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRSCRGA.SPRSCRGA1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRSCRGA.SPRSCRGA2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRSCRGA.SPRSCRGA2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRSCRGA.SPRSCRGA3.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRSCRGA.SPRSCRGA3.word ));
	Im_CNR_Off_Pclk( ch );
}

static void pt_im_cnr_ofl_cspr_sprd_reg_print( kuchar ch )
{
	Ddim_Print(("OFL_CSPR_SPRD_TABLE REG ch%d print -----------\n", ch ));
	Im_CNR_On_Pclk( ch );
	// Cb
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRDCBBD.SPRDCBBD1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRDCBBD.SPRDCBBD1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRDCBBD.SPRDCBBD2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRDCBBD.SPRDCBBD2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRDCBOF.SPRDCBOF1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRDCBOF.SPRDCBOF1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRDCBOF.SPRDCBOF2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRDCBOF.SPRDCBOF2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRDCBGA.SPRDCBGA1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRDCBGA.SPRDCBGA1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRDCBGA.SPRDCBGA2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRDCBGA.SPRDCBGA2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRDCBGA.SPRDCBGA3.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRDCBGA.SPRDCBGA3.word ));
	// Cr
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRDCRBD.SPRDCRBD1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRDCRBD.SPRDCRBD1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRDCRBD.SPRDCRBD2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRDCRBD.SPRDCRBD2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRDCROF.SPRDCROF1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRDCROF.SPRDCROF1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRDCROF.SPRDCROF2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRDCROF.SPRDCROF2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRDCRGA.SPRDCRGA1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRDCRGA.SPRDCRGA1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRDCRGA.SPRDCRGA2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRDCRGA.SPRDCRGA2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRDCRGA.SPRDCRGA3.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->oflCsprReg.SPRDCRGA.SPRDCRGA3.word ));
	Im_CNR_Off_Pclk( ch );
}

static void ptImCnrOtfCsprSprdRegPrint( kuchar ch )
{
	Ddim_Print(("OTF_CSPR_SPRD_TABLE REG ch%d print -----------\n", ch ));
	Im_CNR_On_Pclk( ch );
	// Cb
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRDCBBD.SPRDCBBD1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRDCBBD.SPRDCBBD1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRDCBBD.SPRDCBBD2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRDCBBD.SPRDCBBD2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRDCBOF.SPRDCBOF1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRDCBOF.SPRDCBOF1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRDCBOF.SPRDCBOF2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRDCBOF.SPRDCBOF2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRDCBGA.SPRDCBGA1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRDCBGA.SPRDCBGA1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRDCBGA.SPRDCBGA2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRDCBGA.SPRDCBGA2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRDCBGA.SPRDCBGA3.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRDCBGA.SPRDCBGA3.word ));
	// Cr
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRDCRBD.SPRDCRBD1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRDCRBD.SPRDCRBD1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRDCRBD.SPRDCRBD2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRDCRBD.SPRDCRBD2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRDCROF.SPRDCROF1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRDCROF.SPRDCROF1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRDCROF.SPRDCROF2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRDCROF.SPRDCROF2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRDCRGA.SPRDCRGA1.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRDCRGA.SPRDCRGA1.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRDCRGA.SPRDCRGA2.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRDCRGA.SPRDCRGA2.word ));
	Ddim_Print(("PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRDCRGA.SPRDCRGA3.word    = 0x%lx\n", PalladiumTestCnr_IO_CNR(ch)->otfCsprReg.SPRDCRGA.SPRDCRGA3.word ));
	Im_CNR_Off_Pclk( ch );
}

static void ptImCnrOfl11( kuchar ch )
{
	kint32 ret;

	Ddim_Print(( "*** CNR OFL test " PalladiumTestCnr_D_IM_CNR_TEST_NO " begin\n" ));

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	ret = Im_CNR_OFL_Init(ch);

	// タイマー停止
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "Im_CNR_Init = %d\n", ret));

	Ddim_Print(( "*** CNR OFL test " PalladiumTestCnr_D_IM_CNR_TEST_NO " end\n" ));
}

static void ptImCnrOtf11( kuchar ch )
{
	kint32 ret;

	Ddim_Print(( "*** CNR OTF test " PalladiumTestCnr_D_IM_CNR_TEST_NO " begin\n" ));

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	ret = Im_CNR_OTF_Init(ch);

	// タイマー停止
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "Im_CNR_Init = %d\n", ret));

	Ddim_Print(( "*** CNR OTF test " PalladiumTestCnr_D_IM_CNR_TEST_NO " end\n" ));
}

static void ptImCnrOfl12( kuchar ch )
{
	kint32 imErcd;
	T_IM_CNR_OFL_CTRL spr_ctrl = {
		.mode = E_IM_CNR_OFL_YCC_MODE_YCC422_SIMPLE,

		.width = PalladiumTestCnr_D_IM_CNR_TEST_H_PIXS,
		.lines = PalladiumTestCnr_D_IM_CNR_TEST_V_PIXS,

		.r_y_width = PalladiumTestCnr_D_IM_CNR_TEST_H_PIXS,
		.r_y_addr = D_IM_CNR_TEST_IMG_SRC_Y_ADDR,

		.r_c_width = PalladiumTestCnr_D_IM_CNR_TEST_H_PIXS,
		.r_cb_addr = D_IM_CNR_TEST_IMG_SRC_CB_ADDR,
		.r_cr_addr = D_IM_CNR_TEST_IMG_SRC_CR_ADDR,

		.w_y_width = PalladiumTestCnr_D_IM_CNR_TEST_H_PIXS,
		.w_y_addr = D_IM_CNR_TEST_IMG_DST_Y_ADDR,

		.w_c_width = PalladiumTestCnr_D_IM_CNR_TEST_H_PIXS,
		.w_cb_addr = D_IM_CNR_TEST_IMG_DST_CB_ADDR,
		.w_cr_addr = D_IM_CNR_TEST_IMG_DST_CR_ADDR,

		.work_addr = D_IM_CNR_TEST_IMG_TMP_ADDR,

		.divide_top = E_IM_CNR_VPROCESS_NORM,
		.divide_bot = E_IM_CNR_VPROCESS_NORM,

		.pCallBack = NULL,
	};
	T_IM_CNR_CTRL_C spr_ctrl_c = {
		.enable = E_IM_CNR_ONOFF_ENABLE,
		.mid_freq_nr = {
			.enable = E_IM_CNR_ONOFF_ENABLE,
			.h_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.h_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.y_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
			.c_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
		},
		.low_freq_nr = {
			.enable = E_IM_CNR_ONOFF_ENABLE,
			.h_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.h_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.y_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
			.c_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
		},
	};
	T_IM_CNR_OFL_CTRL_Y spr_ctrl_y = {
		.enable = E_IM_CNR_ONOFF_DISABLE,
		.threshold_type = E_IM_CNR_THRES_REGISTER,
		.level = E_IM_CNR_LEVEL_HIGH,
		.h_y_threshold = 0xFF,
		.v_y_threshold = 0xFF,
		.h_c_threshold = 0xFF,
		.v_c_threshold = 0xFF,
		.alpha_blend_ratio = 0x1F,
	};

	// 入力データ
	Palladium_Set_In_Localstack( D_IM_CNR_TEST_IMG_SRC_ADDR, D_IM_CNR_TEST_IMG_SRC_BYTES );

	Ddim_Print(( "*** CNR OFL test " PalladiumTestCnr_D_IM_CNR_TEST_NO " begin\n" ));


	imErcd = Im_CNR_OFL_Open( ch, 100 );
	if( imErcd != D_DDIM_OK ) {
		Ddim_Print(("Open error = 0x%x\n", imErcd ));
		return ;
	}

	imErcd = Im_CNR_OFL_Ctrl( ch, &spr_ctrl );
	if( imErcd != D_DDIM_OK ) {
		Ddim_Print(("Ctrl error = 0x%x\n", imErcd ));
		return ;
	}

	imErcd = Im_CNR_OFL_Ctrl_C( ch, &spr_ctrl_c );
	if( imErcd != D_DDIM_OK ) {
		Ddim_Print(("Ctrl_C error = 0x%x\n", imErcd ));
		return ;
	}

	imErcd = Im_CNR_OFL_Ctrl_Y( ch, &spr_ctrl_y );
	if( imErcd != D_DDIM_OK ) {
		Ddim_Print(("Ctrl_Y error = 0x%x\n", imErcd ));
		return ;
	}

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	imErcd = Im_CNR_OFL_Start_Sync( ch, 100 );
	if( imErcd != D_DDIM_OK ) {
		Ddim_Print(("Start error = 0x%x\n", imErcd ));
	}

	// タイマー停止
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	imErcd = Im_CNR_OFL_Stop(ch);
	if( imErcd != D_DDIM_OK ) {
		Ddim_Print(("Stop error = 0x%x\n", imErcd ));
	}


	imErcd = Im_CNR_OFL_Close(ch);
	if( imErcd != D_DDIM_OK ) {
		Ddim_Print(("Close error = 0x%x\n", imErcd ));
	}

	// 出力ダンプ
	Palladium_Set_Out_Localstack( D_IM_CNR_TEST_IMG_DST_ADDR, D_IM_CNR_TEST_IMG_DST_BYTES );

	ptImCnrOflRegRwPrint( ch );

	Ddim_Print(( "*** CNR OFL test " PalladiumTestCnr_D_IM_CNR_TEST_NO " end\n" ));
}

static void ptImCnrOtf12( kuchar ch )
{
	kint32 imErcd;
	T_IM_CNR_OTF_CTRL spr_ctrl = {
		.mode = E_IM_CNR_OTF_YCC_MODE_YCC422_SIMPLE,

		.width = PalladiumTestCnr_D_IM_CNR_TEST_H_PIXS,
		.lines = PalladiumTestCnr_D_IM_CNR_TEST_V_PIXS,

		.w_c_width = PalladiumTestCnr_D_IM_CNR_TEST_H_PIXS,

		.divide_left = E_IM_CNR_VPROCESS_NORM,
		.divide_right = E_IM_CNR_VPROCESS_NORM,

		.pCallBack = NULL,
	};
	T_IM_CNR_OTF_OUTADDR_INFO addr_info = {
		.use_bank_num= 1,
		.w_c_addr[0] = D_IM_CNR_TEST_IMG_DST_CB_ADDR,
	};
	T_IM_CNR_CTRL_C spr_ctrl_c = {
		.enable = E_IM_CNR_ONOFF_ENABLE,
		.mid_freq_nr = {
			.enable = E_IM_CNR_ONOFF_ENABLE,
			.h_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.h_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.y_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
			.c_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
		},
		.low_freq_nr = {
			.enable = E_IM_CNR_ONOFF_ENABLE,
			.h_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.h_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.y_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
			.c_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
		},
	};

	// 入力データ
	Palladium_Set_In_Localstack( D_IM_CNR_TEST_IMG_SRC_ADDR, D_IM_CNR_TEST_IMG_SRC_BYTES );

	Ddim_Print(( "*** CNR OTF test " PalladiumTestCnr_D_IM_CNR_TEST_NO " begin\n" ));


	imErcd = Im_CNR_OTF_Open( ch, 100 );
	if( imErcd != D_DDIM_OK ) {
		Ddim_Print(("Open error = 0x%x\n", imErcd ));
		return ;
	}

	imErcd = Im_CNR_OTF_Ctrl( ch, &spr_ctrl );
	if( imErcd != D_DDIM_OK ) {
		Ddim_Print(("Ctrl error = 0x%x\n", imErcd ));
		return ;
	}

	imErcd = Im_CNR_OTF_Set_OutAddr_Info( ch, &addr_info );
	if( imErcd != D_DDIM_OK ) {
		Ddim_Print(( "Set OutAddrInfo error = 0x%x\n", imErcd ));
		return ;
	}

	imErcd = Im_CNR_OTF_Ctrl_C( ch, &spr_ctrl_c );
	if( imErcd != D_DDIM_OK ) {
		Ddim_Print(("Ctrl_C error = 0x%x\n", imErcd ));
		return ;
	}

#ifdef D_IM_CNR_R2Y_MACRO_ENABLE
	imErcd = ct_im_cnr_set_im_r2y_set( ch );
	if( imErcd != D_DDIM_OK ) {
		Ddim_Print(("ct_im_cnr_set_im_r2y_set error = 0x%x\n", imErcd ));
		return ;
	}
	imErcd = ct_im_cnr_set_im_r2y_start( ch );
	if( imErcd != D_DDIM_OK ) {
		Ddim_Print(("ct_im_cnr_set_im_r2y_start error = 0x%x\n", imErcd ));
		return ;
	}
#endif	// D_IM_CNR_R2Y_MACRO_ENABLE

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	imErcd = Im_CNR_OTF_Start_Sync( ch, 100 );
	if( imErcd != D_DDIM_OK ) {
		Ddim_Print(("Start error = 0x%x\n", imErcd ));
	}

	// タイマー停止
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	imErcd = Im_CNR_OTF_Stop(ch);
	if( imErcd != D_DDIM_OK ) {
		Ddim_Print(("Stop error = 0x%x\n", imErcd ));
	}

#ifdef D_IM_CNR_R2Y_MACRO_ENABLE
	imErcd = ct_im_cnr_set_im_r2y_stop( ch );
	if( imErcd != D_DDIM_OK ) {
		Ddim_Print(("ct_im_cnr_set_im_r2y_stop error = 0x%x\n", imErcd ));
		return ;
	}
#endif	// D_IM_CNR_R2Y_MACRO_ENABLE

	imErcd = Im_CNR_OTF_Close(ch);
	if( imErcd != D_DDIM_OK ) {
		Ddim_Print(("Close error = 0x%x\n", imErcd ));
	}

	// 出力ダンプ
	Palladium_Set_Out_Localstack( D_IM_CNR_TEST_IMG_DST_ADDR, D_IM_CNR_TEST_IMG_DST_BYTES );

	ptImCnrOtfRegRwPrint( ch );

	Ddim_Print(( "*** CNR OTF test " PalladiumTestCnr_D_IM_CNR_TEST_NO " end\n" ));
}

static void ptImCnrOfl13( kuchar ch )
{
	kint32 imErcd;
	T_IM_CNR_OFL_CTRL spr_ctrl = {
		.mode = E_IM_CNR_OFL_YCC_MODE_YCC422,

		.width = PalladiumTestCnr_D_IM_CNR_TEST_H_PIXS,
		.lines = PalladiumTestCnr_D_IM_CNR_TEST_V_PIXS,

		.r_y_width = PalladiumTestCnr_D_IM_CNR_TEST_H_PIXS,
		.r_y_addr = D_IM_CNR_TEST_IMG_SRC_Y_ADDR,

		.r_c_width = PalladiumTestCnr_D_IM_CNR_TEST_H_PIXS,
		.r_cb_addr = D_IM_CNR_TEST_IMG_SRC_CB_ADDR,
		.r_cr_addr = D_IM_CNR_TEST_IMG_SRC_CR_ADDR,

		.w_y_width = PalladiumTestCnr_D_IM_CNR_TEST_H_PIXS,
		.w_y_addr = D_IM_CNR_TEST_IMG_DST_Y_ADDR,

		.w_c_width = PalladiumTestCnr_D_IM_CNR_TEST_H_PIXS,
		.w_cb_addr = D_IM_CNR_TEST_IMG_DST_CB_ADDR,
		.w_cr_addr = D_IM_CNR_TEST_IMG_DST_CR_ADDR,

		.work_addr = D_IM_CNR_TEST_IMG_TMP_ADDR,

		.divide_top = E_IM_CNR_VPROCESS_NORM,
		.divide_bot = E_IM_CNR_VPROCESS_NORM,

		.pCallBack = NULL,
	};
	T_IM_CNR_CTRL_C spr_ctrl_c = {
		.enable = E_IM_CNR_ONOFF_DISABLE,
		.mid_freq_nr = {
			.enable = E_IM_CNR_ONOFF_DISABLE,
			.h_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.h_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.y_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
			.c_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
		},
		.low_freq_nr = {
			.enable = E_IM_CNR_ONOFF_DISABLE,
			.h_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.h_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.y_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
			.c_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
		},
	};
	T_IM_CNR_OFL_CTRL_Y spr_ctrl_y = {
		.enable = E_IM_CNR_ONOFF_ENABLE,
		.threshold_type = E_IM_CNR_THRES_REGISTER,
		.level = E_IM_CNR_LEVEL_HIGH,
		.h_y_threshold = 0xFF,
		.v_y_threshold = 0xFF,
		.h_c_threshold = 0xFF,
		.v_c_threshold = 0xFF,
		.alpha_blend_ratio = 0,
	};

	// 入力データ
	Palladium_Set_In_Localstack( D_IM_CNR_TEST_IMG_SRC_ADDR, D_IM_CNR_TEST_IMG_SRC_BYTES );

	Ddim_Print(( "*** CNR OFL test " PalladiumTestCnr_D_IM_CNR_TEST_NO " begin\n" ));

	imErcd = Im_CNR_OFL_Open( ch, 100 );
	if( imErcd != D_DDIM_OK ) {
		Ddim_Print(("Open error = 0x%x\n", imErcd ));
		return;
	}

	imErcd = Im_CNR_OFL_Ctrl( ch, &spr_ctrl );
	if( imErcd != D_DDIM_OK ) {
		Ddim_Print(("Ctrl error = 0x%x\n", imErcd ));
		return;
	}

	imErcd = Im_CNR_OFL_Ctrl_C( ch, &spr_ctrl_c );
	if( imErcd != D_DDIM_OK ) {
		Ddim_Print(("Ctrl_C error = 0x%x\n", imErcd ));
		return;
	}

	imErcd = Im_CNR_OFL_Ctrl_Y( ch, &spr_ctrl_y );
	if( imErcd != D_DDIM_OK ) {
		Ddim_Print(("Ctrl_Y error = 0x%x\n", imErcd ));
		return;
	}

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	imErcd = Im_CNR_OFL_Start_Sync( ch, 100 );
	if( imErcd != D_DDIM_OK ) {
		Ddim_Print(("Start error = 0x%x\n", imErcd ));
	}

	// タイマー停止
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	imErcd = Im_CNR_OFL_Stop(ch);
	if( imErcd != D_DDIM_OK ) {
		Ddim_Print(("Stop error = 0x%x\n", imErcd ));
	}

	imErcd = Im_CNR_OFL_Close(ch);
	if( imErcd != D_DDIM_OK ) {
		Ddim_Print(("Close error = 0x%x\n", imErcd ));
	}

	// 出力ダンプ
	Palladium_Set_Out_Localstack( D_IM_CNR_TEST_IMG_DST_ADDR, D_IM_CNR_TEST_IMG_DST_BYTES );

	ptImCnrOflRegRwPrint( ch );

	Ddim_Print(( "*** CNR OFL test " PalladiumTestCnr_D_IM_CNR_TEST_NO " end\n" ));
}

static void ptImCnrOtf13( kuchar ch )
{
	kint32 imErcd;
	T_IM_CNR_OTF_CTRL spr_ctrl = {
		.mode = E_IM_CNR_OTF_YCC_MODE_YCC422_SIMPLE,

		.width = PalladiumTestCnr_D_IM_CNR_TEST_H_PIXS,
		.lines = PalladiumTestCnr_D_IM_CNR_TEST_V_PIXS,

		.w_c_width = PalladiumTestCnr_D_IM_CNR_TEST_H_PIXS,

		.divide_left = E_IM_CNR_VPROCESS_NORM,
		.divide_right = E_IM_CNR_VPROCESS_NORM,

		.pCallBack = NULL,
	};
	T_IM_CNR_OTF_OUTADDR_INFO addr_info = {
		.use_bank_num= 1,
		.w_c_addr[0] = D_IM_CNR_TEST_IMG_DST_CB_ADDR,
	};
	T_IM_CNR_CTRL_C spr_ctrl_c = {
		.enable = E_IM_CNR_ONOFF_DISABLE,
		.mid_freq_nr = {
			.enable = E_IM_CNR_ONOFF_DISABLE,
			.h_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.h_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.y_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
			.c_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
		},
		.low_freq_nr = {
			.enable = E_IM_CNR_ONOFF_DISABLE,
			.h_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.h_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.y_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
			.c_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
		},
	};

	// 入力データ
	Palladium_Set_In_Localstack( D_IM_CNR_TEST_IMG_SRC_ADDR, D_IM_CNR_TEST_IMG_SRC_BYTES );

	Ddim_Print(( "*** CNR OTF test " PalladiumTestCnr_D_IM_CNR_TEST_NO " begin\n" ));

	imErcd = Im_CNR_OTF_Open( ch, 100 );
	if( imErcd != D_DDIM_OK ) {
		Ddim_Print(("Open error = 0x%x\n", imErcd ));
		return;
	}

	imErcd = Im_CNR_OTF_Ctrl( ch, &spr_ctrl );
	if( imErcd != D_DDIM_OK ) {
		Ddim_Print(("Ctrl error = 0x%x\n", imErcd ));
		return;
	}

	imErcd = Im_CNR_OTF_Set_OutAddr_Info( ch, &addr_info );
	if( imErcd != D_DDIM_OK ) {
		Ddim_Print(( "Set OutAddrInfo error = 0x%x\n", imErcd ));
		return ;
	}

	imErcd = Im_CNR_OTF_Ctrl_C( ch, &spr_ctrl_c );
	if( imErcd != D_DDIM_OK ) {
		Ddim_Print(("Ctrl_C error = 0x%x\n", imErcd ));
		return;
	}

#ifdef D_IM_CNR_R2Y_MACRO_ENABLE
	imErcd = ct_im_cnr_set_im_r2y_set( ch );
	if( imErcd != D_DDIM_OK ) {
		Ddim_Print(("ct_im_cnr_set_im_r2y_set error = 0x%x\n", imErcd ));
		return ;
	}
	imErcd = ct_im_cnr_set_im_r2y_start( ch );
	if( imErcd != D_DDIM_OK ) {
		Ddim_Print(("ct_im_cnr_set_im_r2y_start error = 0x%x\n", imErcd ));
		return ;
	}
#endif	// D_IM_CNR_R2Y_MACRO_ENABLE

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	imErcd = Im_CNR_OTF_Start_Sync( ch, 100 );
	if( imErcd != D_DDIM_OK ) {
		Ddim_Print(("Start error = 0x%x\n", imErcd ));
	}

	// タイマー停止
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	imErcd = Im_CNR_OTF_Stop(ch);
	if( imErcd != D_DDIM_OK ) {
		Ddim_Print(("Stop error = 0x%x\n", imErcd ));
	}

#ifdef D_IM_CNR_R2Y_MACRO_ENABLE
	imErcd = ct_im_cnr_set_im_r2y_stop( ch );
	if( imErcd != D_DDIM_OK ) {
		Ddim_Print(("ct_im_cnr_set_im_r2y_stop error = 0x%x\n", imErcd ));
		return ;
	}
#endif	// D_IM_CNR_R2Y_MACRO_ENABLE

	imErcd = Im_CNR_OTF_Close(ch);
	if( imErcd != D_DDIM_OK ) {
		Ddim_Print(("Close error = 0x%x\n", imErcd ));
	}

	// 出力ダンプ
	Palladium_Set_Out_Localstack( D_IM_CNR_TEST_IMG_DST_ADDR, D_IM_CNR_TEST_IMG_DST_BYTES );

	ptImCnrOtfRegRwPrint( ch );

	Ddim_Print(( "*** CNR OTF test " PalladiumTestCnr_D_IM_CNR_TEST_NO " end\n" ));
}

void palladium_test_cnr_im_main(void)
{
	kuchar	type1;

//	Dd_GIC_Init();
	Dd_GIC_Ctrl( E_DD_GIC_INTID_TIMER_CH0_INT, 1, D_DD_GIC_PRI30, 1 );		//cpu=0, intid=118, enable, pri=30
	Dd_GIC_Ctrl( E_DD_GIC_INTID_CNR_UNIT1_INT, 1, D_DD_GIC_PRI30, 1 );		// int enable
	Dd_GIC_Ctrl( E_DD_GIC_INTID_CNR_UNIT2_INT, 1, D_DD_GIC_PRI30, 1 );		// int enable

	Dd_Top_Start_Clock( (kuchar*)&S_GIM_CNR_CLK_CTRL_CNT1, &Dd_Top_Get_CLKSTOP11(), ~D_DD_TOP_CNR1CK_BIT );
	Dd_Top_Start_Clock( (kuchar*)&S_GIM_CNR_CLK_CTRL_CNT2, &Dd_Top_Get_CLKSTOP13(), ~D_DD_TOP_CNR2CK_BIT );
	Dd_Top_Start_Clock( (kuchar*)&S_GIM_CNR_ICLK_CTRL_CNT1, &Dd_Top_Get_CLKSTOP11(), ~D_DD_TOP_CNR1AX_BIT );
	Dd_Top_Start_Clock( (kuchar*)&S_GIM_CNR_ICLK_CTRL_CNT2, &Dd_Top_Get_CLKSTOP13(), ~D_DD_TOP_CNR2AX_BIT );


	Ddim_Print(("CNR START\n"));

	// タイマー初期化
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_INIT );

	// テストパラメータ取得
	type1	= gDDIM_Info.com._6a;

	switch (type1){
		case 5:
			pt_im_cnr_run_5(type1);
			break;

		case 6:
			pt_im_cnr_run_6(type1);
			break;

		default:
			break;
	}

	// タイマーログ出力
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_PRINT );

	Ddim_Print(("CNR END\n"));

	// テスト強制終了処理
	Palladium_Force_Stop();
}

PalladiumTestCnr* palladium_test_cnr_new(void)
{
	PalladiumTestCnr* self = k_object_new_with_private(PALLADIUM_TYPE_TEST_CNR,sizeof(PalladiumTestCnrPrivate));
	return self;
}
