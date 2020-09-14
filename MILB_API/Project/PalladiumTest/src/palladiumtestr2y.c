/*
*
*@Copyright (C) 2010-2020 贵阳高新网用软件有限公司
*@date : 2020-09-08
*@author : aorongxing
*@brief : PalladiumTestR2y
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 
*
*/

/**
 * @file		palladium_test_r2y.c
 * @brief		palladium test r2y code
 * @note		None
 * @attention	None
 *
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */

#include "ct_im_r2y.h"
#include "imr2y.h"
#include "ddgic.h"
#include "ddtop.h"

#include "driver_common.h"
#include "palladium_test.h"

#include <string.h>
#include "palladiumtestr2y.h"
#include "palladiumtestr2ycom.h"
#include "palladiumtestr2ycom2.h"


K_TYPE_DEFINE_WITH_PRIVATE(PalladiumTestR2y, palladium_test_r2y)
#define PALLADIUM_TEST_R2Y_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), PalladiumTestR2yPrivate, PALLADIUM_TYPE_TEST_R2Y))


#define PalladiumTestR2y_D_IM_R2Y1_CLK_REG_ADDR	(&DdToptwo_GET_CLKSTOP11())
#define PalladiumTestR2y_D_IM_R2Y1_ICLK_REG_ADDR	(&DdToptwo_GET_CLKSTOP11())
#define PalladiumTestR2y_D_IM_R2Y1_HCLK_REG_ADDR	(&DdToptwo_GET_CLKSTOP11())
#define PalladiumTestR2y_D_IM_R2Y1_PCLK_REG_ADDR	(&DdToptwo_GET_CLKSTOP11())

#define PalladiumTestR2y_D_IM_R2Y1_CLK_REG_BIT	DdTopone_R2Y1CK_BIT	// bit8~9
#define PalladiumTestR2y_D_IM_R2Y1_ICLK_REG_BIT	DdTopone_R2Y1AX_BIT	// bit10~11
#define PalladiumTestR2y_D_IM_R2Y1_HCLK_REG_BIT	DdTopone_R2Y1AH_BIT	// bit12~13
#define PalladiumTestR2y_D_IM_R2Y1_PCLK_REG_BIT	DdTopone_R2Y1AP_BIT	// bit14~15

#define PalladiumTestR2y_D_IM_R2Y2_CLK_REG_ADDR	(&DdToptwo_GET_CLKSTOP13())
#define PalladiumTestR2y_D_IM_R2Y2_ICLK_REG_ADDR	(&DdToptwo_GET_CLKSTOP13())
#define PalladiumTestR2y_D_IM_R2Y2_HCLK_REG_ADDR	(&DdToptwo_GET_CLKSTOP13())
#define PalladiumTestR2y_D_IM_R2Y2_PCLK_REG_ADDR	(&DdToptwo_GET_CLKSTOP13())

#define PalladiumTestR2y_D_IM_R2Y2_CLK_REG_BIT	DdTopone_R2Y2CK_BIT	// bit8~9
#define PalladiumTestR2y_D_IM_R2Y2_ICLK_REG_BIT	DdTopone_R2Y2AX_BIT	// bit10~11
#define PalladiumTestR2y_D_IM_R2Y2_HCLK_REG_BIT	DdTopone_R2Y2AH_BIT	// bit12~13
#define PalladiumTestR2y_D_IM_R2Y2_PCLK_REG_BIT	DdTopone_R2Y2AP_BIT	// bit14~15


struct _PalladiumTestR2yPrivate
{
	int a;
	DdTopthree* ddTopthree;
	PalladiumTestR2yCom* palladiumTestR2yCom;
	PalladiumTestR2yCom2* palladiumTestR2yCom2;
};

/*
 * DECLS
 */
static void ptImR2yEnableGic( void );
static void ptImR2yStartClock(PalladiumTestR2y* self);
static void ptImR2yDoTest11( const kuint32 ctIdx1st, const kuint32 ctIdx2nd );
static void ptImR2yDoTest128( const kuint32 ctIdx1st, const kuint32 ctIdx2nd );
static void ptImR2yDoTest142( const kuint32 ctIdx1st, const kuint32 ctIdx2nd );
static void ptImR2yDoTest146( const kuint32 ctIdx1st, const kuint32 ctIdx2nd );
static void ptImR2yDoTest153( const kuint32 ctIdx1st, const kuint32 ctIdx2nd );
static void ptImR2yDoTest154( const kuint32 ctIdx1st, const kuint32 ctIdx2nd );
static void ptImR2yDoTest166( const kuint32 ctIdx1st, const kuint32 ctIdx2nd );
static void ptImR2yDoTest177( const kuint32 ctIdx1st, const kuint32 ctIdx2nd );
static void ptImR2yDoTest189( const kuint32 ctIdx1st, const kuint32 ctIdx2nd );
static void ptImR2yRun1( const kuint32 type1 );
static void ptImR2yDoTest21( const kuint32 ctIdx1st, const kuint32 ctIdx2nd );
static void ptImR2yRun2( const kuint32 type1 );
static void ptImR2yDoTest367( const kuint32 ctIdx1st, const kuint32 ctIdx2nd, const kuint32 ctIdx3rd );
static void ptImR2yDoTest368( const kuint32 ctIdx1st, const kuint32 ctIdx2nd, const kuint32 ctIdx3rd );
static void ptImR2yDoTest369( const kuint32 ctIdx1st, const kuint32 ctIdx2nd, const kuint32 ctIdx3rd );
static void ptImR2yDoTest370( const kuint32 ctIdx1st, const kuint32 ctIdx2nd, const kuint32 ctIdx3rd );
static void ptImR2yDoTest371( const kuint32 ctIdx1st, const kuint32 ctIdx2nd, const kuint32 ctIdx3rd );
static void ptImR2yDoTest372( const kuint32 ctIdx1st, const kuint32 ctIdx2nd, const kuint32 ctIdx3rd );
static void ptImR2yDoTest373( const kuint32 ctIdx1st, const kuint32 ctIdx2nd, const kuint32 ctIdx3rd );
static void ptImR2yRun3( const kuint32 type1 );
static void ptImR2yRun9( const kuint32 type1 );

/*
 * IMPL
 */
static void palladium_test_r2y_constructor(PalladiumTestR2y *self)
{
	PalladiumTestR2yPrivate *priv = PALLADIUM_TEST_R2Y_GET_PRIVATE(self);
	priv->a = 0;
	priv->ddTopthree = dd_topthree_new();
	priv->palladiumTestR2yCom = palladium_test_r2y_com_new();
	priv->palladiumTestR2yCom2 = palladium_test_r2y_com2_new();
}

static void palladium_test_r2y_destructor(PalladiumTestR2y *self)
{
	PalladiumTestR2yPrivate *priv = PALLADIUM_TEST_R2Y_GET_PRIVATE(self);
	priv->a = 0;
	if(priv->ddTopthree)
	{
		k_object_unref(priv->ddTopthree);
		priv->ddTopthree = NULL;
	}
	if(priv->palladiumTestR2yCom)
		{
			k_object_unref(priv->palladiumTestR2yCom);
			priv->palladiumTestR2yCom = NULL;
		}
	if(priv->palladiumTestR2yCom2)
			{
				k_object_unref(priv->palladiumTestR2yCom2);
				priv->palladiumTestR2yCom2 = NULL;
			}
}


static void ptImR2yEnableGic( void )
{
//	Dd_GIC_Init();
	Dd_GIC_Ctrl( DdGic_INTID_TIMER_CH0_INT, 1, C_PRI30, 1 );		// cpu=0, intid=118, enable, pri=30
	Dd_GIC_Ctrl( DdGic_INTID_R2Y_UNIT1_INT, 1, C_PRI30, 1 );		// int enable
	Dd_GIC_Ctrl( DdGic_INTID_R2Y_UNIT2_INT, 1, C_PRI30, 1 );		// int enable

	Dd_GIC_Ctrl( DdGic_INTID_B2R_UNIT1_INT, 1, C_PRI30, 1 );		// cpu=0, intid=233, enable, pri=30 B2R_UNIT1_INT
	Dd_GIC_Ctrl( DdGic_INTID_B2R_UNIT2_INT, 1, C_PRI30, 1 );		// cpu=0, intid=234, enable, pri=30 B2R_UNIT2_INT
	Dd_GIC_Ctrl( DdGic_INTID_LTM_UNIT1_INT, 1, C_PRI30, 1 );		// cpu=0, intid=235, enable, pri=30 LTM_UNIT1_INT
	Dd_GIC_Ctrl( DdGic_INTID_LTM_UNIT2_INT, 1, C_PRI30, 1 );		// cpu=0, intid=236, enable, pri=30 LTM_UNIT2_INT
}

static void ptImR2yStartClock(PalladiumTestR2y* self)
{
	PalladiumTestR2yPrivate *priv = PALLADIUM_TEST_R2Y_GET_PRIVATE(self);

#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_PCLOCK) || defined(CO_ACT_HCLOCK)
#else
	kuchar imR2y1ClkCtrlCnt = 0;
	kuchar imR2y1HclkCtrlCnt = 0;
	kuchar imR2y1PclkCtrlCnt = 0;
	kuchar imR2y1IclkCtrlCnt = 0;
	kuchar imR2y2ClkCtrlCnt = 0;
	kuchar imR2y2HclkCtrlCnt = 0;
	kuchar imR2y2PclkCtrlCnt = 0;
	kuchar imR2y2IclkCtrlCnt = 0;

	dd_topthree_start_clock(priv->ddTopthree, &imR2y1PclkCtrlCnt, PalladiumTestR2y_D_IM_R2Y1_PCLK_REG_ADDR,
			~PalladiumTestR2y_D_IM_R2Y1_PCLK_REG_BIT );
	dd_topthree_start_clock(priv->ddTopthree, &imR2y1HclkCtrlCnt, PalladiumTestR2y_D_IM_R2Y1_HCLK_REG_ADDR,
			~PalladiumTestR2y_D_IM_R2Y1_HCLK_REG_BIT );
	dd_topthree_start_clock(priv->ddTopthree, &imR2y1IclkCtrlCnt, PalladiumTestR2y_D_IM_R2Y1_ICLK_REG_ADDR,
			~PalladiumTestR2y_D_IM_R2Y1_ICLK_REG_BIT );
	dd_topthree_start_clock(priv->ddTopthree, &imR2y1ClkCtrlCnt,  PalladiumTestR2y_D_IM_R2Y1_CLK_REG_ADDR,
			~PalladiumTestR2y_D_IM_R2Y1_CLK_REG_BIT );

	dd_topthree_start_clock(priv->ddTopthree, &imR2y2PclkCtrlCnt, PalladiumTestR2y_D_IM_R2Y2_PCLK_REG_ADDR,
			~PalladiumTestR2y_D_IM_R2Y2_PCLK_REG_BIT );
	dd_topthree_start_clock(priv->ddTopthree, &imR2y2HclkCtrlCnt, PalladiumTestR2y_D_IM_R2Y2_HCLK_REG_ADDR,
			~PalladiumTestR2y_D_IM_R2Y2_HCLK_REG_BIT );
	dd_topthree_start_clock(priv->ddTopthree, &imR2y2IclkCtrlCnt, PalladiumTestR2y_D_IM_R2Y2_ICLK_REG_ADDR,
			~PalladiumTestR2y_D_IM_R2Y2_ICLK_REG_BIT );
	dd_topthree_start_clock(priv->ddTopthree, &imR2y2ClkCtrlCnt,  PalladiumTestR2y_D_IM_R2Y2_CLK_REG_ADDR,
			~PalladiumTestR2y_D_IM_R2Y2_CLK_REG_BIT );
#endif
}

#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "1_1"
static void ptImR2yDoTest11( const kuint32 ctIdx1st, const kuint32 ctIdx2nd )
{
	static const kuchar	no2ndTbl[] = {
		1, 14, 17, 18, 19, 20, 21, 22, 23, 25, 27,
	};
	kuint32				loopcnt;

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	for( loopcnt = 0; loopcnt < (sizeof(no2ndTbl) / sizeof(no2ndTbl[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* R2Y begin CT_Im_R2y_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
		CT_Im_R2Y_Run( ctIdx1st, no2ndTbl[loopcnt], 0 );
		Ddim_Print(( "* R2Y end CT_Im_R2y_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
	}

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "1_28"
static void ptImR2yDoTest128( const kuint32 ctIdx1st, const kuint32 ctIdx2nd )
{
	static const kuchar	no2ndTbl[] = {
		28, 29, 30, 32, 33, 34, 36, 37, 38, 39, 41,
	};
	kuint32				loopcnt;

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	for( loopcnt = 0; loopcnt < (sizeof(no2ndTbl) / sizeof(no2ndTbl[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* R2Y begin CT_Im_R2y_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
		CT_Im_R2Y_Run( ctIdx1st, no2ndTbl[loopcnt], 0 );
		Ddim_Print(( "* R2Y end CT_Im_R2y_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
	}

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "1_42"
static void ptImR2yDoTest142( const kuint32 ctIdx1st, const kuint32 ctIdx2nd )
{
	static const kuchar	no2ndTbl[] = {
		42, 43, 44, 45,
	};
	kuint32				loopcnt;

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	for( loopcnt = 0; loopcnt < (sizeof(no2ndTbl) / sizeof(no2ndTbl[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* R2Y begin CT_Im_R2y_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
		CT_Im_R2Y_Run( ctIdx1st, no2ndTbl[loopcnt], 0 );
		Ddim_Print(( "* R2Y end CT_Im_R2y_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
	}

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}


#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "1_46"
static void ptImR2yDoTest146( const kuint32 ctIdx1st, const kuint32 ctIdx2nd )
{
	static const kuchar	no2ndTbl[] = {
		46, 47, 48, 49, 50, 51, 52,
	};
	kuint32				loopcnt;

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	for( loopcnt = 0; loopcnt < (sizeof(no2ndTbl) / sizeof(no2ndTbl[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* R2Y begin CT_Im_R2y_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
		CT_Im_R2Y_Run( ctIdx1st, no2ndTbl[loopcnt], 0 );
		Ddim_Print(( "* R2Y end CT_Im_R2y_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
	}

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}


#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "1_53"
static void ptImR2yDoTest153( const kuint32 ctIdx1st, const kuint32 ctIdx2nd )
{
	static const kuchar	no2ndTbl[] = {
		53, 55, 56, 57, 58, 59, 61, 62, 63, 65,
	};
	kuint32				loopcnt;

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	for( loopcnt = 0; loopcnt < (sizeof(no2ndTbl) / sizeof(no2ndTbl[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* R2Y begin CT_Im_R2y_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
		CT_Im_R2Y_Run( ctIdx1st, no2ndTbl[loopcnt], 0 );
		Ddim_Print(( "* R2Y end CT_Im_R2y_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
	}
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}


#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "1_54"
static void ptImR2yDoTest154( const kuint32 ctIdx1st, const kuint32 ctIdx2nd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "=-=-=-=-\n" ));
	Ddim_Print(( "* R2Y begin CT_Im_R2y_%u_%u\n", ctIdx1st, 54 ));
	CT_Im_R2Y_Run( ctIdx1st, 54, 0 );
	Ddim_Print(( "* R2Y end CT_Im_R2y_%u_%u\n", ctIdx1st, 54 ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}


#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "1_66"
static void ptImR2yDoTest166( const kuint32 ctIdx1st, const kuint32 ctIdx2nd )
{
	static const kuchar	no2ndTbl[] = {
		66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76,
	};
	kuint32				loopcnt;

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	for( loopcnt = 0; loopcnt < (sizeof(no2ndTbl) / sizeof(no2ndTbl[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* R2Y begin CT_Im_R2y_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
		CT_Im_R2Y_Run( ctIdx1st, no2ndTbl[loopcnt], 0 );
		Ddim_Print(( "* R2Y end CT_Im_R2y_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
	}
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}


#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "1_77"
static void ptImR2yDoTest177( const kuint32 ctIdx1st, const kuint32 ctIdx2nd )
{
	static const kuchar	no2ndTbl[] = {
		77, 78, 80, 81, 82, 83, 84, 85, 86, 87, 88,
	};
	kuint32				loopcnt;

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	for( loopcnt = 0; loopcnt < (sizeof(no2ndTbl) / sizeof(no2ndTbl[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* R2Y begin CT_Im_R2y_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
		CT_Im_R2Y_Run( ctIdx1st, no2ndTbl[loopcnt], 0 );
		Ddim_Print(( "* R2Y end CT_Im_R2y_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
	}

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}


#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "1_89"
static void ptImR2yDoTest189( const kuint32 ctIdx1st, const kuint32 ctIdx2nd )
{
	static const kuchar	no2ndTbl[] = {
		89, 90, 93, 94, 95, 96, 97, 98, 99, 100, 133,
	};
	kuint32				loopcnt;

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	for( loopcnt = 0; loopcnt < (sizeof(no2ndTbl) / sizeof(no2ndTbl[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* R2Y begin CT_Im_R2y_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
		CT_Im_R2Y_Run( ctIdx1st, no2ndTbl[loopcnt], 0 );
		Ddim_Print(( "* R2Y end CT_Im_R2y_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
	}

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}


static void ptImR2yRun1( const kuint32 type1 )
{
	kuchar			type2;

	type2	= gDDIM_Info.com._6b;

	switch( type2 ) {
		case 1:
			ptImR2yDoTest11( type1, type2 );
			break;
		case 28:
			ptImR2yDoTest128( type1, type2 );
			break;
		case 42:
			ptImR2yDoTest142( type1, type2 );
			break;
		case 46:
			ptImR2yDoTest146( type1, type2 );
			break;
		case 53:
			ptImR2yDoTest153( type1, type2 );
			break;
		case 54:
			ptImR2yDoTest154( type1, type2 );
			break;
		case 66:
			ptImR2yDoTest166( type1, type2 );
			break;
		case 77:
			ptImR2yDoTest177( type1, type2 );
			break;
		case 89:
			ptImR2yDoTest189( type1, type2 );
			break;
		default:
			Ddim_Print(("*** R2Y test skip\n" ));
			break;
	}
}

#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "2_1"
static void ptImR2yDoTest21( const kuint32 ctIdx1st, const kuint32 ctIdx2nd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, 0 );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

static void ptImR2yRun2( const kuint32 type1 )
{
	kuchar			type2;

	type2	= gDDIM_Info.com._6b;

	switch( type2 ) {
		case 1:
			ptImR2yDoTest21( type1, type2 );
			break;
		default:
			Ddim_Print(("*** R2Y test skip\n" ));
			break;
	}
}

// Input: RGB U16,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_67"
static void ptImR2yDoTest367( const kuint32 ctIdx1st, const kuint32 ctIdx2nd, const kuint32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (void*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	memset( (void*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB U16,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_68"
static void ptImR2yDoTest368( const kuint32 ctIdx1st, const kuint32 ctIdx2nd, const kuint32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (void*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	memset( (void*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB U16,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_69"
static void ptImR2yDoTest369( const kuint32 ctIdx1st, const kuint32 ctIdx2nd, const kuint32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (void*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	memset( (void*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB U16,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_70"
static void ptImR2yDoTest370( const kuint32 ctIdx1st, const kuint32 ctIdx2nd, const kuint32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (void*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	memset( (void*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB U16,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_71"
static void ptImR2yDoTest371( const kuint32 ctIdx1st, const kuint32 ctIdx2nd, const kuint32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (void*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', (1280 * 960 * 2 * 3) );
	memset( (void*)(D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP + (1280 * 960 * 2 * 3)), '\xee', (1280 * 960 * 2) + ( D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES / 256 ));
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, (1280 * 960 * 2 * 3) );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack(( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP + (1280 * 960 * 2 * 3)), D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES * 4 );
	Palladium_Set_Out_Localstack(( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP + (1280 * 960 * 2 * 3) + (1280 * 960 * 2)), D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES / 256 );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB U16,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_72"
static void ptImR2yDoTest372( const kuint32 ctIdx1st, const kuint32 ctIdx2nd, const kuint32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (void*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	memset( (void*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
//	Palladium_Set_Out_Localstack( D_IM_R2Y_TBL_MEM_OUT_ADDR_TOP_TCTDATA, D_IM_R2Y_TBL_MEM_OUT_TCTDATA );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB U16,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_73"
static void ptImR2yDoTest373( const kuint32 ctIdx1st, const kuint32 ctIdx2nd, const kuint32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (void*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	memset( (void*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
//	Palladium_Set_Out_Localstack( D_IM_R2Y_TBL_MEM_OUT_ADDR_TOP_TCHSYDATA, D_IM_R2Y_TBL_MEM_OUT_TCHSYDATA );
//	Palladium_Set_Out_Localstack( D_IM_R2Y_TBL_MEM_OUT_ADDR_TOP_TCHSRDATA, D_IM_R2Y_TBL_MEM_OUT_TCHSRGBDATA );
//	Palladium_Set_Out_Localstack( D_IM_R2Y_TBL_MEM_OUT_ADDR_TOP_TCHSGDATA, D_IM_R2Y_TBL_MEM_OUT_TCHSRGBDATA );
//	Palladium_Set_Out_Localstack( D_IM_R2Y_TBL_MEM_OUT_ADDR_TOP_TCHSBDATA, D_IM_R2Y_TBL_MEM_OUT_TCHSRGBDATA );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

static void ptImR2yRun3(PalladiumTestR2y* self, const kuint32 type1 )
{
	PalladiumTestR2yPrivate *priv = PALLADIUM_TEST_R2Y_GET_PRIVATE(self);
	kuchar			type2;
	kuchar			type3;

	type2	= gDDIM_Info.com._6b;
	type3	= gDDIM_Info.com._6c;

	switch( type2 ) {
		case 1:
			 palladium_test_r2y_com_do_test_3_1(priv->palladiumTestR2yCom, type1, type2, type3 );
			break;
		case 2:
			 palladium_test_r2y_com_do_test_3_2(priv->palladiumTestR2yCom, type1, type2, type3 );
			break;
		case 3:
			 palladium_test_r2y_com_do_test_3_3(priv->palladiumTestR2yCom, type1, type2, type3 );
			break;
		case 4:
			 palladium_test_r2y_com_do_test_3_4(priv->palladiumTestR2yCom, type1, type2, type3 );
			break;
		case 5:
			 palladium_test_r2y_com_do_test_3_5(priv->palladiumTestR2yCom, type1, type2, type3 );
			break;
		case 6:
			 palladium_test_r2y_com_do_test_3_6(priv->palladiumTestR2yCom, type1, type2, type3 );
			break;
		case 12:
			 palladium_test_r2y_com_do_test_3_12(priv->palladiumTestR2yCom, type1, type2, type3 );
			break;
		case 13:
			 palladium_test_r2y_com_do_test_3_13(priv->palladiumTestR2yCom, type1, type2, type3 );
			break;
		case 14:
			 palladium_test_r2y_com_do_test_3_14(priv->palladiumTestR2yCom, type1, type2, type3 );
			break;
		case 15:
			 palladium_test_r2y_com_do_test_3_15(priv->palladiumTestR2yCom, type1, type2, type3 );
			break;
		case 16:
			 palladium_test_r2y_com_do_test_3_16(priv->palladiumTestR2yCom, type1, type2, type3 );
			break;
		case 17:
			 palladium_test_r2y_com_do_test_3_17(priv->palladiumTestR2yCom, type1, type2, type3 );
			break;
		case 18:
			 palladium_test_r2y_com_do_test_3_18(priv->palladiumTestR2yCom, type1, type2, type3 );
			break;
		case 19:
			 palladium_test_r2y_com_do_test_3_19(priv->palladiumTestR2yCom, type1, type2, type3 );
			break;
		case 20:
			 palladium_test_r2y_com_do_test_3_20(priv->palladiumTestR2yCom, type1, type2, type3 );
			break;
		case 21:
			 palladium_test_r2y_com_do_test_3_21(priv->palladiumTestR2yCom, type1, type2, type3 );
			break;
		case 22:
			 palladium_test_r2y_com_do_test_3_22(priv->palladiumTestR2yCom, type1, type2, type3 );
			break;
		case 23:
			 palladium_test_r2y_com_do_test_3_23(priv->palladiumTestR2yCom, type1, type2, type3 );
			break;
		case 24:
			 palladium_test_r2y_com_do_test_3_24(priv->palladiumTestR2yCom, type1, type2, type3 );
			break;
		case 25:
			 palladium_test_r2y_com_do_test_3_25(priv->palladiumTestR2yCom, type1, type2, type3 );
			break;
		case 26:
			 palladium_test_r2y_com_do_test_3_26(priv->palladiumTestR2yCom, type1, type2, type3 );
			break;
		case 27:
			 palladium_test_r2y_com_do_test_3_27(priv->palladiumTestR2yCom, type1, type2, type3 );
			break;
		case 28:
			 palladium_test_r2y_com_do_test_3_28(priv->palladiumTestR2yCom, type1, type2, type3 );
			break;
		case 29:
			 palladium_test_r2y_com_do_test_3_29(priv->palladiumTestR2yCom, type1, type2, type3 );
			break;
		case 30:
			 palladium_test_r2y_com_do_test_3_30(priv->palladiumTestR2yCom, type1, type2, type3 );
			break;
		case 31:
			 palladium_test_r2y_com_do_test_3_31(priv->palladiumTestR2yCom, type1, type2, type3 );
			break;
		case 32:
			 palladium_test_r2y_com_do_test_3_32(priv->palladiumTestR2yCom, type1, type2, type3 );
			break;
		case 33:
			palladium_test_r2y_com2_do_test_3_33(priv->palladiumTestR2yCom2, type1, type2, type3 );
			break;
		case 34:
			palladium_test_r2y_com2_do_test_3_34(priv->palladiumTestR2yCom2, type1, type2, type3 );
			break;
		case 35:
			palladium_test_r2y_com2_do_test_3_35(priv->palladiumTestR2yCom2, type1, type2, type3 );
			break;
		case 36:
			palladium_test_r2y_com2_do_test_3_36(priv->palladiumTestR2yCom2, type1, type2, type3 );
			break;
//		case 37:
//			palladium_test_r2y_com2_do_test_3_37(priv->palladiumTestR2yCom2, type1, type2, type3 );
//			break;
//		case 38:
//			palladium_test_r2y_com2_do_test_3_38(priv->palladiumTestR2yCom2, type1, type2, type3 );
//			break;
//		case 39:
//			palladium_test_r2y_com2_do_test_3_39(priv->palladiumTestR2yCom2, type1, type2, type3 );
//			break;
//		case 40:
//			palladium_test_r2y_com2_do_test_3_40(priv->palladiumTestR2yCom2, type1, type2, type3 );
//			break;
		case 41:
			palladium_test_r2y_com2_do_test_3_41(priv->palladiumTestR2yCom2, type1, type2, type3 );
			break;
		case 42:
			palladium_test_r2y_com2_do_test_3_42(priv->palladiumTestR2yCom2, type1, type2, type3 );
			break;
		case 43:
			palladium_test_r2y_com2_do_test_3_43(priv->palladiumTestR2yCom2, type1, type2, type3 );
			break;
		case 44:
			palladium_test_r2y_com2_do_test_3_44(priv->palladiumTestR2yCom2, type1, type2, type3 );
			break;
		case 45:
			palladium_test_r2y_com2_do_test_3_45(priv->palladiumTestR2yCom2, type1, type2, type3 );
			break;
		case 46:
			palladium_test_r2y_com2_do_test_3_46(priv->palladiumTestR2yCom2, type1, type2, type3 );
			break;
		case 47:
			palladium_test_r2y_com2_do_test_3_47(priv->palladiumTestR2yCom2, type1, type2, type3 );
			break;
		case 48:
			palladium_test_r2y_com2_do_test_3_48(priv->palladiumTestR2yCom2, type1, type2, type3 );
			break;
		case 49:
			palladium_test_r2y_com2_do_test_3_49(priv->palladiumTestR2yCom2, type1, type2, type3 );
			break;
		case 50:
			palladium_test_r2y_com2_do_test_3_50(priv->palladiumTestR2yCom2, type1, type2, type3 );
			break;
		case 51:
			palladium_test_r2y_com2_do_test_3_51(priv->palladiumTestR2yCom2, type1, type2, type3 );
			break;
		case 52:
			palladium_test_r2y_com2_do_test_3_52(priv->palladiumTestR2yCom2, type1, type2, type3 );
			break;
		case 53:
			palladium_test_r2y_com2_do_test_3_53(priv->palladiumTestR2yCom2, type1, type2, type3 );
			break;
		case 54:
			palladium_test_r2y_com2_do_test_3_54(priv->palladiumTestR2yCom2, type1, type2, type3 );
			break;
		case 55:
			palladium_test_r2y_com2_do_test_3_55(priv->palladiumTestR2yCom2, type1, type2, type3 );
			break;
		case 56:
			palladium_test_r2y_com2_do_test_3_56(priv->palladiumTestR2yCom2, type1, type2, type3 );
			break;
		case 57:
			palladium_test_r2y_com2_do_test_3_57(priv->palladiumTestR2yCom2, type1, type2, type3 );
			break;
		case 58:
			palladium_test_r2y_com2_do_test_3_58(priv->palladiumTestR2yCom2, type1, type2, type3 );
			break;
		case 59:
			palladium_test_r2y_com2_do_test_3_59(priv->palladiumTestR2yCom2, type1, type2, type3 );
			break;
		case 60:
			palladium_test_r2y_com2_do_test_3_60(priv->palladiumTestR2yCom2, type1, type2, type3 );
			break;
		case 61:
			palladium_test_r2y_com2_do_test_3_61(priv->palladiumTestR2yCom2, type1, type2, type3 );
			break;
		case 62:
			palladium_test_r2y_com2_do_test_3_62(priv->palladiumTestR2yCom2, type1, type2, type3 );
			break;
		case 63:
			palladium_test_r2y_com2_do_test_3_63(priv->palladiumTestR2yCom2, type1, type2, type3 );
			break;
		case 64:
			palladium_test_r2y_com2_do_test_3_64(priv->palladiumTestR2yCom2, type1, type2, type3 );
			break;
		case 65:
			palladium_test_r2y_com2_do_test_3_65(priv->palladiumTestR2yCom2, type1, type2, type3 );
			break;
		case 66:
			palladium_test_r2y_com2_do_test_3_66(priv->palladiumTestR2yCom2, type1, type2, type3 );
			break;
		case 67:
			ptImR2yDoTest367( type1, type2, type3 );
			break;
		case 68:
			ptImR2yDoTest368( type1, type2, type3 );
			break;
		case 69:
			ptImR2yDoTest369( type1, type2, type3 );
			break;
		case 70:
			ptImR2yDoTest370( type1, type2, type3 );
			break;
		case 71:
			ptImR2yDoTest371( type1, type2, type3 );
			break;
		case 72:
			ptImR2yDoTest372( type1, type2, type3 );
			break;
		case 73:
			ptImR2yDoTest373( type1, type2, type3 );
			break;
		default:
			Ddim_Print(("*** R2Y test skip\n" ));
			break;
	}
}


#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "1_"
static void ptImR2yRun9( const kuint32 type1 )
{
	kuchar			type2;

	type2	= gDDIM_Info.com._6b;

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO "%u begin\n", type2 ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "=-=-=-=-\n" ));
	Ddim_Print(( "* R2Y begin CT_Im_R2y_1_%u\n", type2 ));
	CT_Im_R2Y_Run( 1, type2, 0 );
	Ddim_Print(( "* R2Y end CT_Im_R2y_1_%u\n", type2 ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO "%u end\n", type2 ));
}


void palladium_test_r2y_main(PalladiumTestR2y* self)
{
	kuchar			type1;

	Ddim_Print(( "****** R2Y begin palladium_test_r2y_main\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_INIT );

	type1	= gDDIM_Info.com._6a;

	Dd_Top_Set_CLKSTOP11_R2Y1CK( 1 );
	Dd_Top_Set_CLKSEL4_R2Y1CLK( 0 );	// 300MHz
	Dd_Top_Set_CLKSTOP11_R2Y1CK( 0 );
	Dd_Top_Set_CLKSTOP13_R2Y2CK( 1 );
	Dd_Top_Set_CLKSEL6_R2Y2CLK( 0 );	// 300MHz
	Dd_Top_Set_CLKSTOP13_R2Y2CK( 0 );


	Ddim_Print(( "*** R2Y begin Im_R2Y_Init\n" ));
	Im_R2Y_Init( D_IM_R2Y_PIPE12 );
	Ddim_Print(( "*** R2Y end Im_R2Y_Init\n" ));

	ptImR2yEnableGic();
	ptImR2yStartClock(NULL);

	switch( type1 ) {
		case 1:
			ptImR2yRun1( type1 );
			break;
		case 2:
			ptImR2yRun2( type1 );
			break;
		case 3:
			ptImR2yRun3(NULL, type1 );
			break;
		case 9:
			ptImR2yRun9( type1 );
			break;
		default:
			Ddim_Print(("*** R2Y test skip\n" ));
			break;
	}

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_PRINT );


	Ddim_Print(( "(CLKSEL-4)\n" ));
	Ddim_Print(( "R2Y1CLK = %d\n", Dd_Top_Get_CLKSEL4_R2Y1CLK() ));
	Ddim_Print(( "(CLKSTOP-11)\n" ));
	Ddim_Print(( "R2Y1CK = %d\n", Dd_Top_Get_CLKSTOP11_R2Y1CK() ));
	Ddim_Print(( "R2Y1AP = %d\n", Dd_Top_Get_CLKSTOP11_R2Y1AP() ));
	Ddim_Print(( "R2Y1AH = %d\n", Dd_Top_Get_CLKSTOP11_R2Y1AH() ));
	Ddim_Print(( "R2Y1AX = %d\n", Dd_Top_Get_CLKSTOP11_R2Y1AX() ));
	Ddim_Print(( "(CLKSEL-6)\n" ));
	Ddim_Print(( "R2Y2CLK = %d\n", Dd_Top_Get_CLKSEL6_R2Y2CLK() ));
	Ddim_Print(( "(CLKSTOP-13)\n" ));
	Ddim_Print(( "R2Y2CK = %d\n", Dd_Top_Get_CLKSTOP13_R2Y2CK() ));
	Ddim_Print(( "R2Y2AP = %d\n", Dd_Top_Get_CLKSTOP13_R2Y2AP() ));
	Ddim_Print(( "R2Y2AH = %d\n", Dd_Top_Get_CLKSTOP13_R2Y2AH() ));
	Ddim_Print(( "R2Y2AX = %d\n", Dd_Top_Get_CLKSTOP13_R2Y2AX() ));
	Ddim_Print(( "****** R2Y end palladium_test_r2y_main\n" ));

	Palladium_Force_Stop();
}


PalladiumTestR2y* palladium_test_r2y_new(void)
{
	PalladiumTestR2y* self = k_object_new_with_private(PALLADIUM_TYPE_TEST_R2Y, sizeof(PalladiumTestR2yPrivate));

	return self;
}

