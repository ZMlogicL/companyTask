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
#include "im_r2y.h"
#include "dd_gic.h"
#include "dd_top.h"

#include "driver_common.h"
#include "palladium_test.h"

#include <string.h>
#include "palladiumtestr2y.h"
#include "palladiumtestr2ycom.h"
#include "palladiumtestr2ycom2.h"


K_TYPE_DEFINE_WITH_PRIVATE(PalladiumTestR2y, palladium_test_r2y)
#define PALLADIUM_TEST_R2Y_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), PalladiumTestR2yPrivate, PALLADIUM_TYPE_TEST_R2Y))


#define PalladiumTestR2y_D_IM_R2Y1_CLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP11())
#define PalladiumTestR2y_D_IM_R2Y1_ICLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP11())
#define PalladiumTestR2y_D_IM_R2Y1_HCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP11())
#define PalladiumTestR2y_D_IM_R2Y1_PCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP11())

#define PalladiumTestR2y_D_IM_R2Y1_CLK_REG_BIT	D_DD_TOP_R2Y1CK_BIT	// bit8~9
#define PalladiumTestR2y_D_IM_R2Y1_ICLK_REG_BIT	D_DD_TOP_R2Y1AX_BIT	// bit10~11
#define PalladiumTestR2y_D_IM_R2Y1_HCLK_REG_BIT	D_DD_TOP_R2Y1AH_BIT	// bit12~13
#define PalladiumTestR2y_D_IM_R2Y1_PCLK_REG_BIT	D_DD_TOP_R2Y1AP_BIT	// bit14~15

#define PalladiumTestR2y_D_IM_R2Y2_CLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP13())
#define PalladiumTestR2y_D_IM_R2Y2_ICLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP13())
#define PalladiumTestR2y_D_IM_R2Y2_HCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP13())
#define PalladiumTestR2y_D_IM_R2Y2_PCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP13())

#define PalladiumTestR2y_D_IM_R2Y2_CLK_REG_BIT	D_DD_TOP_R2Y2CK_BIT	// bit8~9
#define PalladiumTestR2y_D_IM_R2Y2_ICLK_REG_BIT	D_DD_TOP_R2Y2AX_BIT	// bit10~11
#define PalladiumTestR2y_D_IM_R2Y2_HCLK_REG_BIT	D_DD_TOP_R2Y2AH_BIT	// bit12~13
#define PalladiumTestR2y_D_IM_R2Y2_PCLK_REG_BIT	D_DD_TOP_R2Y2AP_BIT	// bit14~15


struct _PalladiumTestR2yPrivate
{

};

/*
 * DECLS
 */
static VOID ptImR2yEnableGic( VOID );
static VOID ptImR2yStartClock( VOID );
static VOID ptImR2yDoTest11( const UINT32 ctIdx1st, const UINT32 ctIdx2nd );
static VOID ptImR2yDoTest128( const UINT32 ctIdx1st, const UINT32 ctIdx2nd );
static VOID ptImR2yDoTest142( const UINT32 ctIdx1st, const UINT32 ctIdx2nd );
static VOID ptImR2yDoTest146( const UINT32 ctIdx1st, const UINT32 ctIdx2nd );
static VOID ptImR2yDoTest153( const UINT32 ctIdx1st, const UINT32 ctIdx2nd );
static VOID ptImR2yDoTest154( const UINT32 ctIdx1st, const UINT32 ctIdx2nd );
static VOID ptImR2yDoTest166( const UINT32 ctIdx1st, const UINT32 ctIdx2nd );
static VOID ptImR2yDoTest177( const UINT32 ctIdx1st, const UINT32 ctIdx2nd );
static VOID ptImR2yDoTest189( const UINT32 ctIdx1st, const UINT32 ctIdx2nd );
static VOID ptImR2yRun1( const UINT32 type1 );
static VOID ptImR2yDoTest21( const UINT32 ctIdx1st, const UINT32 ctIdx2nd );
static VOID ptImR2yRun2( const UINT32 type1 );
static VOID ptImR2yDoTest367( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID ptImR2yDoTest368( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID ptImR2yDoTest369( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID ptImR2yDoTest370( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID ptImR2yDoTest371( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID ptImR2yDoTest372( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID ptImR2yDoTest373( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID ptImR2yRun3( const UINT32 type1 );
static VOID ptImR2yRun9( const UINT32 type1 );

/*
 * IMPL
 */
static void palladium_test_r2y_constructor(PalladiumTestR2y *self)
{
	PalladiumTestR2yPrivate *priv = PALLADIUM_TEST_R2Y_GET_PRIVATE(self);
}

static void palladium_test_r2y_destructor(PalladiumTestR2y *self)
{
	PalladiumTestR2yPrivate *priv = PALLADIUM_TEST_R2Y_GET_PRIVATE(self);
}


static VOID ptImR2yEnableGic( VOID )
{
//	Dd_GIC_Init();
	Dd_GIC_Ctrl( E_DD_GIC_INTID_TIMER_CH0_INT, 1, D_DD_GIC_PRI30, 1 );		// cpu=0, intid=118, enable, pri=30
	Dd_GIC_Ctrl( E_DD_GIC_INTID_R2Y_UNIT1_INT, 1, D_DD_GIC_PRI30, 1 );		// int enable
	Dd_GIC_Ctrl( E_DD_GIC_INTID_R2Y_UNIT2_INT, 1, D_DD_GIC_PRI30, 1 );		// int enable

	Dd_GIC_Ctrl( E_DD_GIC_INTID_B2R_UNIT1_INT, 1, D_DD_GIC_PRI30, 1 );		// cpu=0, intid=233, enable, pri=30 B2R_UNIT1_INT
	Dd_GIC_Ctrl( E_DD_GIC_INTID_B2R_UNIT2_INT, 1, D_DD_GIC_PRI30, 1 );		// cpu=0, intid=234, enable, pri=30 B2R_UNIT2_INT
	Dd_GIC_Ctrl( E_DD_GIC_INTID_LTM_UNIT1_INT, 1, D_DD_GIC_PRI30, 1 );		// cpu=0, intid=235, enable, pri=30 LTM_UNIT1_INT
	Dd_GIC_Ctrl( E_DD_GIC_INTID_LTM_UNIT2_INT, 1, D_DD_GIC_PRI30, 1 );		// cpu=0, intid=236, enable, pri=30 LTM_UNIT2_INT
}

static VOID ptImR2yStartClock( VOID )
{
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_PCLOCK) || defined(CO_ACT_HCLOCK)
#else
	UCHAR imR2y1ClkCtrlCnt = 0;
	UCHAR imR2y1HclkCtrlCnt = 0;
	UCHAR imR2y1PclkCtrlCnt = 0;
	UCHAR imR2y1IclkCtrlCnt = 0;
	UCHAR imR2y2ClkCtrlCnt = 0;
	UCHAR imR2y2HclkCtrlCnt = 0;
	UCHAR imR2y2PclkCtrlCnt = 0;
	UCHAR imR2y2IclkCtrlCnt = 0;

	Dd_Top_Start_Clock( &imR2y1PclkCtrlCnt, PalladiumTestR2y_D_IM_R2Y1_PCLK_REG_ADDR,
			~PalladiumTestR2y_D_IM_R2Y1_PCLK_REG_BIT );
	Dd_Top_Start_Clock( &imR2y1HclkCtrlCnt, PalladiumTestR2y_D_IM_R2Y1_HCLK_REG_ADDR,
			~PalladiumTestR2y_D_IM_R2Y1_HCLK_REG_BIT );
	Dd_Top_Start_Clock( &imR2y1IclkCtrlCnt, PalladiumTestR2y_D_IM_R2Y1_ICLK_REG_ADDR,
			~PalladiumTestR2y_D_IM_R2Y1_ICLK_REG_BIT );
	Dd_Top_Start_Clock( &imR2y1ClkCtrlCnt,  PalladiumTestR2y_D_IM_R2Y1_CLK_REG_ADDR,
			~PalladiumTestR2y_D_IM_R2Y1_CLK_REG_BIT );

	Dd_Top_Start_Clock( &imR2y2PclkCtrlCnt, PalladiumTestR2y_D_IM_R2Y2_PCLK_REG_ADDR,
			~PalladiumTestR2y_D_IM_R2Y2_PCLK_REG_BIT );
	Dd_Top_Start_Clock( &imR2y2HclkCtrlCnt, PalladiumTestR2y_D_IM_R2Y2_HCLK_REG_ADDR,
			~PalladiumTestR2y_D_IM_R2Y2_HCLK_REG_BIT );
	Dd_Top_Start_Clock( &imR2y2IclkCtrlCnt, PalladiumTestR2y_D_IM_R2Y2_ICLK_REG_ADDR,
			~PalladiumTestR2y_D_IM_R2Y2_ICLK_REG_BIT );
	Dd_Top_Start_Clock( &imR2y2ClkCtrlCnt,  PalladiumTestR2y_D_IM_R2Y2_CLK_REG_ADDR,
			~PalladiumTestR2y_D_IM_R2Y2_CLK_REG_BIT );
#endif
}

#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "1_1"
static VOID ptImR2yDoTest11( const UINT32 ctIdx1st, const UINT32 ctIdx2nd )
{
	static const UCHAR	no2ndTbl[] = {
		1, 14, 17, 18, 19, 20, 21, 22, 23, 25, 27,
	};
	UINT32				loopcnt;

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
static VOID ptImR2yDoTest128( const UINT32 ctIdx1st, const UINT32 ctIdx2nd )
{
	static const UCHAR	no2ndTbl[] = {
		28, 29, 30, 32, 33, 34, 36, 37, 38, 39, 41,
	};
	UINT32				loopcnt;

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
static VOID ptImR2yDoTest142( const UINT32 ctIdx1st, const UINT32 ctIdx2nd )
{
	static const UCHAR	no2ndTbl[] = {
		42, 43, 44, 45,
	};
	UINT32				loopcnt;

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
static VOID ptImR2yDoTest146( const UINT32 ctIdx1st, const UINT32 ctIdx2nd )
{
	static const UCHAR	no2ndTbl[] = {
		46, 47, 48, 49, 50, 51, 52,
	};
	UINT32				loopcnt;

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
static VOID ptImR2yDoTest153( const UINT32 ctIdx1st, const UINT32 ctIdx2nd )
{
	static const UCHAR	no2ndTbl[] = {
		53, 55, 56, 57, 58, 59, 61, 62, 63, 65,
	};
	UINT32				loopcnt;

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
static VOID ptImR2yDoTest154( const UINT32 ctIdx1st, const UINT32 ctIdx2nd )
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
static VOID ptImR2yDoTest166( const UINT32 ctIdx1st, const UINT32 ctIdx2nd )
{
	static const UCHAR	no2ndTbl[] = {
		66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76,
	};
	UINT32				loopcnt;

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
static VOID ptImR2yDoTest177( const UINT32 ctIdx1st, const UINT32 ctIdx2nd )
{
	static const UCHAR	no2ndTbl[] = {
		77, 78, 80, 81, 82, 83, 84, 85, 86, 87, 88,
	};
	UINT32				loopcnt;

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
static VOID ptImR2yDoTest189( const UINT32 ctIdx1st, const UINT32 ctIdx2nd )
{
	static const UCHAR	no2ndTbl[] = {
		89, 90, 93, 94, 95, 96, 97, 98, 99, 100, 133,
	};
	UINT32				loopcnt;

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


static VOID ptImR2yRun1( const UINT32 type1 )
{
	UCHAR			type2;

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
static VOID ptImR2yDoTest21( const UINT32 ctIdx1st, const UINT32 ctIdx2nd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, 0 );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

static VOID ptImR2yRun2( const UINT32 type1 )
{
	UCHAR			type2;

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
static VOID ptImR2yDoTest367( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
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
static VOID ptImR2yDoTest368( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
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
static VOID ptImR2yDoTest369( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
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
static VOID ptImR2yDoTest370( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
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
static VOID ptImR2yDoTest371( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', (1280 * 960 * 2 * 3) );
	memset( (VOID*)(D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP + (1280 * 960 * 2 * 3)), '\xee', (1280 * 960 * 2) + ( D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES / 256 ));
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
static VOID ptImR2yDoTest372( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
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
static VOID ptImR2yDoTest373( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
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

static VOID ptImR2yRun3( const UINT32 type1 )
{
	UCHAR			type2;
	UCHAR			type3;

	type2	= gDDIM_Info.com._6b;
	type3	= gDDIM_Info.com._6c;

	switch( type2 ) {
		case 1:
			pt_im_r2y_do_test_3_1( type1, type2, type3 );
			break;
		case 2:
			pt_im_r2y_do_test_3_2( type1, type2, type3 );
			break;
		case 3:
			pt_im_r2y_do_test_3_3( type1, type2, type3 );
			break;
		case 4:
			pt_im_r2y_do_test_3_4( type1, type2, type3 );
			break;
		case 5:
			pt_im_r2y_do_test_3_5( type1, type2, type3 );
			break;
		case 6:
			pt_im_r2y_do_test_3_6( type1, type2, type3 );
			break;
		case 12:
			pt_im_r2y_do_test_3_12( type1, type2, type3 );
			break;
		case 13:
			pt_im_r2y_do_test_3_13( type1, type2, type3 );
			break;
		case 14:
			pt_im_r2y_do_test_3_14( type1, type2, type3 );
			break;
		case 15:
			pt_im_r2y_do_test_3_15( type1, type2, type3 );
			break;
		case 16:
			pt_im_r2y_do_test_3_16( type1, type2, type3 );
			break;
		case 17:
			pt_im_r2y_do_test_3_17( type1, type2, type3 );
			break;
		case 18:
			pt_im_r2y_do_test_3_18( type1, type2, type3 );
			break;
		case 19:
			pt_im_r2y_do_test_3_19( type1, type2, type3 );
			break;
		case 20:
			pt_im_r2y_do_test_3_20( type1, type2, type3 );
			break;
		case 21:
			pt_im_r2y_do_test_3_21( type1, type2, type3 );
			break;
		case 22:
			pt_im_r2y_do_test_3_22( type1, type2, type3 );
			break;
		case 23:
			pt_im_r2y_do_test_3_23( type1, type2, type3 );
			break;
		case 24:
			pt_im_r2y_do_test_3_24( type1, type2, type3 );
			break;
		case 25:
			pt_im_r2y_do_test_3_25( type1, type2, type3 );
			break;
		case 26:
			pt_im_r2y_do_test_3_26( type1, type2, type3 );
			break;
		case 27:
			pt_im_r2y_do_test_3_27( type1, type2, type3 );
			break;
		case 28:
			pt_im_r2y_do_test_3_28( type1, type2, type3 );
			break;
		case 29:
			pt_im_r2y_do_test_3_29( type1, type2, type3 );
			break;
		case 30:
			pt_im_r2y_do_test_3_30( type1, type2, type3 );
			break;
		case 31:
			pt_im_r2y_do_test_3_31( type1, type2, type3 );
			break;
		case 32:
			pt_im_r2y_do_test_3_32( type1, type2, type3 );
			break;
		case 33:
			pt_im_r2y_do_test_3_33( type1, type2, type3 );
			break;
		case 34:
			pt_im_r2y_do_test_3_34( type1, type2, type3 );
			break;
		case 35:
			pt_im_r2y_do_test_3_35( type1, type2, type3 );
			break;
		case 36:
			pt_im_r2y_do_test_3_36( type1, type2, type3 );
			break;
//		case 37:
//			pt_im_r2y_do_test_3_37( type1, type2, type3 );
//			break;
//		case 38:
//			pt_im_r2y_do_test_3_38( type1, type2, type3 );
//			break;
//		case 39:
//			pt_im_r2y_do_test_3_39( type1, type2, type3 );
//			break;
//		case 40:
//			pt_im_r2y_do_test_3_40( type1, type2, type3 );
//			break;
		case 41:
			pt_im_r2y_do_test_3_41( type1, type2, type3 );
			break;
		case 42:
			pt_im_r2y_do_test_3_42( type1, type2, type3 );
			break;
		case 43:
			pt_im_r2y_do_test_3_43( type1, type2, type3 );
			break;
		case 44:
			pt_im_r2y_do_test_3_44( type1, type2, type3 );
			break;
		case 45:
			pt_im_r2y_do_test_3_45( type1, type2, type3 );
			break;
		case 46:
			pt_im_r2y_do_test_3_46( type1, type2, type3 );
			break;
		case 47:
			pt_im_r2y_do_test_3_47( type1, type2, type3 );
			break;
		case 48:
			pt_im_r2y_do_test_3_48( type1, type2, type3 );
			break;
		case 49:
			pt_im_r2y_do_test_3_49( type1, type2, type3 );
			break;
		case 50:
			pt_im_r2y_do_test_3_50( type1, type2, type3 );
			break;
		case 51:
			pt_im_r2y_do_test_3_51( type1, type2, type3 );
			break;
		case 52:
			pt_im_r2y_do_test_3_52( type1, type2, type3 );
			break;
		case 53:
			pt_im_r2y_do_test_3_53( type1, type2, type3 );
			break;
		case 54:
			pt_im_r2y_do_test_3_54( type1, type2, type3 );
			break;
		case 55:
			pt_im_r2y_do_test_3_55( type1, type2, type3 );
			break;
		case 56:
			pt_im_r2y_do_test_3_56( type1, type2, type3 );
			break;
		case 57:
			pt_im_r2y_do_test_3_57( type1, type2, type3 );
			break;
		case 58:
			pt_im_r2y_do_test_3_58( type1, type2, type3 );
			break;
		case 59:
			pt_im_r2y_do_test_3_59( type1, type2, type3 );
			break;
		case 60:
			pt_im_r2y_do_test_3_60( type1, type2, type3 );
			break;
		case 61:
			pt_im_r2y_do_test_3_61( type1, type2, type3 );
			break;
		case 62:
			pt_im_r2y_do_test_3_62( type1, type2, type3 );
			break;
		case 63:
			pt_im_r2y_do_test_3_63( type1, type2, type3 );
			break;
		case 64:
			pt_im_r2y_do_test_3_64( type1, type2, type3 );
			break;
		case 65:
			pt_im_r2y_do_test_3_65( type1, type2, type3 );
			break;
		case 66:
			pt_im_r2y_do_test_3_66( type1, type2, type3 );
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
static VOID ptImR2yRun9( const UINT32 type1 )
{
	UCHAR			type2;

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


VOID Pt_Im_R2Y_Main( VOID )
{
	UCHAR			type1;

	Ddim_Print(( "****** R2Y begin Pt_Im_R2Y_Main\n" ));

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
	ptImR2yStartClock();

	switch( type1 ) {
		case 1:
			ptImR2yRun1( type1 );
			break;
		case 2:
			ptImR2yRun2( type1 );
			break;
		case 3:
			ptImR2yRun3( type1 );
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
	Ddim_Print(( "****** R2Y end Pt_Im_R2Y_Main\n" ));

	Palladium_Force_Stop();
}


PalladiumTestR2y* palladium_test_r2y_new(void)
{
	PalladiumTestR2y* self = k_object_new_with_private(PALLADIUM_TYPE_TEST_R2Y, sizeof(PalladiumTestR2yPrivate));

	return self;
}

PalladiumTestR2y* palladium_test_r2y_get(void)
{
	static PalladiumTestR2y* self = NULL;

	if (!self) {
		self = k_object_new_with_private(PALLADIUM_TYPE_TEST_R2Y, sizeof(PalladiumTestR2yPrivate));
	}

	return self;
}
