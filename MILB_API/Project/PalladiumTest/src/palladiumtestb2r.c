/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-10
*@author : 刘嫚鶄
*@brief : PalladiumTestB2r
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/

#include "ct_im_b2r.h"
#include "im_b2r.h"
#include "dd_gic.h"
#include "dd_top.h"
#include "driver_common.h"
#include "palladium_test.h"
#include <string.h>

#include "palladiumtestb2r.h"

K_TYPE_DEFINE_WITH_PRIVATE(PalladiumTestB2r, palladium_test_b2r)
#define PALLADIUM_TEST_B2R_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), PalladiumTestB2rPrivate, PALLADIUM_TYPE_TEST_B2R))

struct _PalladiumTestB2rPrivate
{

};

/*
 * DECLS
 */

static VOID 			ptImB2rEnableGic( VOID );
static VOID 			ptImB2rStartClock( VOID );
static VOID 			ptImB2rDoTest11( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd );
static VOID 			ptImB2rDoTest122( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd );
static VOID 			ptImB2rDoTest132( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd );
static VOID 			ptImB2rDoTest138( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd );
static VOID 			ptImB2rDoTest146( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd );
static VOID 			ptImB2rRun1( const kuint32 type1 );
static VOID 			ptImB2rDoTest21( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd );
static VOID 			ptImB2rRun2( const kuint32 type1 );
static VOID 			ptImB2rDoTest31( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd );
static VOID 			ptImB2rDoTest32( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd );
static VOID 			ptImB2rDoTest33( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd );
static VOID 			ptImB2rDoTest34( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd );
static VOID 			ptImB2rDoTest35( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd );
static VOID 			ptImB2rDoTest36( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd );
static VOID 			ptImB2rDoTest37( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd );
static VOID 			ptImB2rDoTest38( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd );
static VOID 			ptImB2rDoTest39( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd );
static VOID 			ptImB2rDoTest310( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd );
static VOID 			ptImB2rDoTest311( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd );
static VOID 			ptImB2rDoTest317( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd );
static VOID 			ptImB2rDoTest318( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd );
static VOID 			ptImB2rDoTest319( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd );
static VOID 			ptImB2rDoTest320( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd );
static VOID 			ptImB2rDoTest321( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd );
static VOID 			ptImB2rDoTest322( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd );
static VOID 			ptImB2rDoTest323( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd );
static VOID 			ptImB2rDoTest324( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd );
static VOID 			ptImB2rDoTest325( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd );
static VOID 			ptImB2rDoTest326( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd );
static VOID 			ptImB2rDoTest327( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd );
static VOID 			ptImB2rDoTest328( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd );
static VOID 			ptImB2rDoTest329( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd );
static VOID 			ptImB2rDoTest330( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd );
static VOID 			ptImB2rDoTest331( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd );
static VOID 			ptImB2rDoTest332( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd );
static VOID 			ptImB2rDoTest333( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd );
static VOID 			ptImB2rDoTest334( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd );
static VOID 			ptImB2rDoTest335( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd );
static VOID 			ptImB2rRun3( const kuint32 type1 );
static VOID 			ptImB2rRun9( const kuint32 type1 );

static void palladium_test_b2r_constructor(PalladiumTestB2r *self)
{
//	PalladiumTestB2rPrivate *priv = PALLADIUM_TEST_B2R_GET_PRIVATE(self);
}

static void palladium_test_b2r_destructor(PalladiumTestB2r *self)
{
//	PalladiumTestB2rPrivate *priv = PALLADIUM_TEST_B2R_GET_PRIVATE(self);
}

/*
 * IMPL
 */

static VOID ptImB2rEnableGic( VOID )
{
//	Dd_GIC_Init();
	Dd_GIC_Ctrl( E_DD_GIC_INTID_TIMER_CH0_INT,    1, D_DD_GIC_PRI30, 1 );		//cpu=0, intid=118, enable, pri=30
	Dd_GIC_Ctrl( E_DD_GIC_INTID_B2R_UNIT1_INT,    1, D_DD_GIC_PRI30, 1 );		// int enable
	Dd_GIC_Ctrl( E_DD_GIC_INTID_B2R_UNIT2_INT,    1, D_DD_GIC_PRI30, 1 );		// int enable
	Dd_GIC_Ctrl( E_DD_GIC_INTID_B2B_UNIT1_INT,	  1, D_DD_GIC_PRI30, 1 );		//cpu=0, intid=223, enable, pri=30 B2B_UNIT1_INT
	Dd_GIC_Ctrl( E_DD_GIC_INTID_B2B_UNIT1_VD_INT, 1, D_DD_GIC_PRI30, 1 );		//cpu=0, intid=224, enable, pri=30 B2B_UNIT1_VD_INT
	Dd_GIC_Ctrl( E_DD_GIC_INTID_B2B_UNIT1_HD_INT, 1, D_DD_GIC_PRI30, 1 );		//cpu=0, intid=225, enable, pri=30 B2B_UNIT1_HD_INT
	Dd_GIC_Ctrl( E_DD_GIC_INTID_B2B_UNIT2_INT,	  1, D_DD_GIC_PRI30, 1 );		//cpu=0, intid=226, enable, pri=30 B2B_UNIT2_INT
	Dd_GIC_Ctrl( E_DD_GIC_INTID_B2B_UNIT2_VD_INT, 1, D_DD_GIC_PRI30, 1 );		//cpu=0, intid=227, enable, pri=30 B2B_UNIT2_VD_INT
	Dd_GIC_Ctrl( E_DD_GIC_INTID_B2B_UNIT2_HD_INT, 1, D_DD_GIC_PRI30, 1 );		//cpu=0, intid=228, enable, pri=30 B2B_UNIT2_HD_INT
}

static VOID ptImB2rStartClock( VOID )
{
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_PCLOCK) || defined(CO_ACT_HCLOCK)
#else
	kuchar im_b2r1_clk_ctrl_cnt = 0;
	kuchar im_b2r1_hclk_ctrl_cnt = 0;
	kuchar im_b2r1_pclk_ctrl_cnt = 0;
	kuchar im_b2r1_iclk_ctrl_cnt = 0;
	kuchar im_b2r2_clk_ctrl_cnt = 0;
	kuchar im_b2r2_hclk_ctrl_cnt = 0;
	kuchar im_b2r2_pclk_ctrl_cnt = 0;
	kuchar im_b2r2_iclk_ctrl_cnt = 0;

	Dd_Top_Start_Clock( &im_b2r1_pclk_ctrl_cnt, PalladiumTestB2r_D_IM_B2R1_PCLK_REG_ADDR, ~PalladiumTestB2r_D_IM_B2R1_PCLK_REG_BIT );
	Dd_Top_Start_Clock( &im_b2r1_hclk_ctrl_cnt, PalladiumTestB2r_D_IM_B2R1_HCLK_REG_ADDR, ~PalladiumTestB2r_D_IM_B2R1_HCLK_REG_BIT );
	Dd_Top_Start_Clock( &im_b2r1_iclk_ctrl_cnt, PalladiumTestB2r_D_IM_B2R1_ICLK_REG_ADDR, ~PalladiumTestB2r_D_IM_B2R1_ICLK_REG_BIT );
	Dd_Top_Start_Clock( &im_b2r1_clk_ctrl_cnt,  PalladiumTestB2r_PalladiumTestB2r_D_IM_B2R1_CLK_REG_ADDR,  ~PalladiumTestB2r_PalladiumTestB2r_D_IM_B2R1_CLK_REG_BIT );

	Dd_Top_Start_Clock( &im_b2r2_pclk_ctrl_cnt, PalladiumTestB2r_D_IM_B2R2_PCLK_REG_ADDR, ~PalladiumTestB2r_D_IM_B2R2_PCLK_REG_BIT );
	Dd_Top_Start_Clock( &im_b2r2_hclk_ctrl_cnt, PalladiumTestB2r_D_IM_B2R2_HCLK_REG_ADDR, ~PalladiumTestB2r_D_IM_B2R2_HCLK_REG_BIT );
	Dd_Top_Start_Clock( &im_b2r2_iclk_ctrl_cnt, PalladiumTestB2r_D_IM_B2R2_ICLK_REG_ADDR, ~PalladiumTestB2r_D_IM_B2R2_ICLK_REG_BIT );
	Dd_Top_Start_Clock( &im_b2r2_clk_ctrl_cnt,  PalladiumTestB2r_D_IM_B2R2_CLK_REG_ADDR,  ~PalladiumTestB2r_D_IM_B2R2_CLK_REG_BIT );
#endif
}

static VOID ptImB2rDoTest11( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd )
{
	static const kuchar	no_2nd_tbl[] = {
		1, 14, 17, 18, 19, 20, 21,
	};
	kuint32				loopcnt;

	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " begin\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	for( loopcnt = 0; loopcnt < (sizeof(no_2nd_tbl) / sizeof(no_2nd_tbl[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* B2R begin CT_Im_B2r_%u_%u\n", ct_idx_1st, no_2nd_tbl[loopcnt] ));
		CT_Im_B2R_Run( ct_idx_1st, no_2nd_tbl[loopcnt], 0 );
		Ddim_Print(( "* B2R end CT_Im_B2r_%u_%u\n", ct_idx_1st, no_2nd_tbl[loopcnt] ));
	}
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " end\n" ));
}

static VOID ptImB2rDoTest122( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd )
{
	static const kuchar	no_2nd_tbl[] = {
		22, 23, 25, 27, 28, 30,
	};
	kuint32				loopcnt;

	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " begin\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	for( loopcnt = 0; loopcnt < (sizeof(no_2nd_tbl) / sizeof(no_2nd_tbl[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* B2R begin CT_Im_B2r_%u_%u\n", ct_idx_1st, no_2nd_tbl[loopcnt] ));
		CT_Im_B2R_Run( ct_idx_1st, no_2nd_tbl[loopcnt], 0 );
		Ddim_Print(( "* B2R end CT_Im_B2r_%u_%u\n", ct_idx_1st, no_2nd_tbl[loopcnt] ));
	}
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " end\n" ));
}

static VOID ptImB2rDoTest132( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd )
{
	static const kuchar	no_2nd_tbl[] = {
		32, 33, 34, 35, 36, 37,
	};
	kuint32				loopcnt;

	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " begin\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	for( loopcnt = 0; loopcnt < (sizeof(no_2nd_tbl) / sizeof(no_2nd_tbl[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* B2R begin CT_Im_B2r_%u_%u\n", ct_idx_1st, no_2nd_tbl[loopcnt] ));
		CT_Im_B2R_Run( ct_idx_1st, no_2nd_tbl[loopcnt], 0 );
		Ddim_Print(( "* B2R end CT_Im_B2r_%u_%u\n", ct_idx_1st, no_2nd_tbl[loopcnt] ));
	}
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " end\n" ));
}

static VOID ptImB2rDoTest138( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd )
{
	static const kuchar	no_2nd_tbl[] = {
		38, 39, 40, 41, 42, 43, 44, 45
	};
	kuint32				loopcnt;

	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " begin\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	for( loopcnt = 0; loopcnt < (sizeof(no_2nd_tbl) / sizeof(no_2nd_tbl[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* B2R begin CT_Im_B2r_%u_%u\n", ct_idx_1st, no_2nd_tbl[loopcnt] ));
		CT_Im_B2R_Run( ct_idx_1st, no_2nd_tbl[loopcnt], 0 );
		Ddim_Print(( "* B2R end CT_Im_B2r_%u_%u\n", ct_idx_1st, no_2nd_tbl[loopcnt] ));
	}
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " end\n" ));
}

static VOID ptImB2rDoTest146( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd )
{
	static const kuchar	no_2nd_tbl[] = {
		46, 47, 48, 49, 50, 51, 52, 53, 54
	};
	kuint32				loopcnt;

	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " begin\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	for( loopcnt = 0; loopcnt < (sizeof(no_2nd_tbl) / sizeof(no_2nd_tbl[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* B2R begin CT_Im_B2r_%u_%u\n", ct_idx_1st, no_2nd_tbl[loopcnt] ));
		CT_Im_B2R_Run( ct_idx_1st, no_2nd_tbl[loopcnt], 0 );
		Ddim_Print(( "* B2R end CT_Im_B2r_%u_%u\n", ct_idx_1st, no_2nd_tbl[loopcnt] ));
	}
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " end\n" ));
}

static VOID ptImB2rRun1( const kuint32 type1 )
{
	kuchar			type2;

	type2	= gDDIM_Info.com._6b;

	switch( type2 ) {
		case 1:
			ptImB2rDoTest11( type1, type2 );
			break;
		case 22:
			ptImB2rDoTest122( type1, type2 );
			break;
		case 32:
			ptImB2rDoTest132( type1, type2 );
			break;
		case 38:
			ptImB2rDoTest138( type1, type2 );
			break;
		case 46:
			ptImB2rDoTest146( type1, type2 );
			break;
		default:
			Ddim_Print(("*** B2R test skip\n" ));
			break;
	}
}

static VOID ptImB2rDoTest21( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd )
{
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " begin\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* B2R begin CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	CT_Im_B2R_Run( ct_idx_1st, ct_idx_2nd, 0 );
	Ddim_Print(( "* B2R end CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " end\n" ));
}

static VOID ptImB2rRun2( const kuint32 type1 )
{
	kuchar			type2;

	type2	= gDDIM_Info.com._6b;

	switch( type2 ) {
		case 1:
			ptImB2rDoTest21( type1, type2 );
			break;
		default:
			Ddim_Print(("*** B2R test skip\n" ));
			break;
	}
}

static VOID ptImB2rDoTest31( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd )
{
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " begin\n" ));

	memset( (VOID*)D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Palladium_Set_In_Localstack( D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_B2R_IMG_MEM_IN_BAY_BYTES_16BIT );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "* B2R begin CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	CT_Im_B2R_Run( ct_idx_1st, ct_idx_2nd, ct_idx_3rd );
	Ddim_Print(( "* B2R end CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );

	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " end\n" ));
}

static VOID ptImB2rDoTest32( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd )
{
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " begin\n" ));
	memset( (VOID*)D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_IN_BAY_BYTES_16BIT );
	memset( (VOID*)D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_OUT_RGB_P12_BYTES );
	Palladium_Set_In_Localstack( D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_B2R_IMG_MEM_IN_BAY_BYTES_16BIT );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* B2R begin CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	CT_Im_B2R_Run( ct_idx_1st, ct_idx_2nd, ct_idx_3rd );
	Ddim_Print(( "* B2R end CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_B2R_IMG_MEM_OUT_RGB_P12_BYTES );
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " end\n" ));
}

static VOID ptImB2rDoTest33( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd )
{
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " begin\n" ));

	memset( (VOID*)D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_IN_BAY_BYTES_12BIT );
	memset( (VOID*)D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Palladium_Set_In_Localstack( D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_B2R_IMG_MEM_IN_BAY_BYTES_12BIT );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* B2R begin CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	CT_Im_B2R_Run( ct_idx_1st, ct_idx_2nd, ct_idx_3rd );
	Ddim_Print(( "* B2R end CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " end\n" ));
}

static VOID ptImB2rDoTest34( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd )
{
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " begin\n" ));
	memset( (VOID*)D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_IN_BAY_BYTES_12BIT );
	memset( (VOID*)D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_OUT_RGB_P12_BYTES );
	Palladium_Set_In_Localstack( D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_B2R_IMG_MEM_IN_BAY_BYTES_12BIT );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* B2R begin CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	CT_Im_B2R_Run( ct_idx_1st, ct_idx_2nd, ct_idx_3rd );
	Ddim_Print(( "* B2R end CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_B2R_IMG_MEM_OUT_RGB_P12_BYTES );
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " end\n" ));
}

static VOID ptImB2rDoTest35( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd )
{
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " begin\n" ));
	memset( (VOID*)D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_IN_BAY_BYTES_10BIT );
	memset( (VOID*)D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Palladium_Set_In_Localstack( D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_B2R_IMG_MEM_IN_BAY_BYTES_10BIT );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* B2R begin CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	CT_Im_B2R_Run( ct_idx_1st, ct_idx_2nd, ct_idx_3rd );
	Ddim_Print(( "* B2R end CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " end\n" ));
}

static VOID ptImB2rDoTest36( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd )
{
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " begin\n" ));
	memset( (VOID*)D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_IN_BAY_BYTES_10BIT );
	memset( (VOID*)D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_OUT_RGB_P12_BYTES );
	Palladium_Set_In_Localstack( D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_B2R_IMG_MEM_IN_BAY_BYTES_10BIT );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* B2R begin CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	CT_Im_B2R_Run( ct_idx_1st, ct_idx_2nd, ct_idx_3rd );
	Ddim_Print(( "* B2R end CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_B2R_IMG_MEM_OUT_RGB_P12_BYTES );
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " end\n" ));
}

static VOID ptImB2rDoTest37( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd )
{
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " begin\n" ));
	memset( (VOID*)D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_IN_BAY_BYTES_8BIT );
	memset( (VOID*)D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Palladium_Set_In_Localstack( D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_B2R_IMG_MEM_IN_BAY_BYTES_8BIT );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* B2R begin CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	CT_Im_B2R_Run( ct_idx_1st, ct_idx_2nd, ct_idx_3rd );
	Ddim_Print(( "* B2R end CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " end\n" ));
}

static VOID ptImB2rDoTest38( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd )
{
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " begin\n" ));
	memset( (VOID*)D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_IN_BAY_BYTES_8BIT );
	memset( (VOID*)D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_OUT_RGB_P12_BYTES );
	Palladium_Set_In_Localstack( D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_B2R_IMG_MEM_IN_BAY_BYTES_8BIT );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* B2R begin CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	CT_Im_B2R_Run( ct_idx_1st, ct_idx_2nd, ct_idx_3rd );
	Ddim_Print(( "* B2R end CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_B2R_IMG_MEM_OUT_RGB_P12_BYTES );
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " end\n" ));
}

static VOID ptImB2rDoTest39( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd )
{
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " begin\n" ));
	memset( (VOID*)D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_IN_BAY_BYTES_12BIT );
	memset( (VOID*)D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Palladium_Set_In_Localstack( D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_B2R_IMG_MEM_IN_BAY_BYTES_12BIT );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* B2R begin CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	CT_Im_B2R_Run( ct_idx_1st, ct_idx_2nd, ct_idx_3rd );
	Ddim_Print(( "* B2R end CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " end\n" ));
}

static VOID ptImB2rDoTest310( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd )
{
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " begin\n" ));
	memset( (VOID*)D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_IN_BAY_BYTES_12BIT );
	memset( (VOID*)D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_OUT_RGB_P12_BYTES );
	Palladium_Set_In_Localstack( D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_B2R_IMG_MEM_IN_BAY_BYTES_12BIT );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* B2R begin CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	CT_Im_B2R_Run( ct_idx_1st, ct_idx_2nd, ct_idx_3rd );
	Ddim_Print(( "* B2R end CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_B2R_IMG_MEM_OUT_RGB_P12_BYTES );
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " end\n" ));
}

static VOID ptImB2rDoTest311( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd )
{
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " begin\n" ));
	memset( (VOID*)D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_IN_BAY_BYTES_16BIT );
	memset( (VOID*)D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Palladium_Set_In_Localstack( D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_B2R_IMG_MEM_IN_BAY_BYTES_16BIT );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* B2R begin CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	CT_Im_B2R_Run( ct_idx_1st, ct_idx_2nd, ct_idx_3rd );
	Ddim_Print(( "* B2R end CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " end\n" ));
}

static VOID ptImB2rDoTest317( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd )
{
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " begin\n" ));
	memset( (VOID*)D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_IN_BAY_BYTES_16BIT );
	memset( (VOID*)D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Palladium_Set_In_Localstack( D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_B2R_IMG_MEM_IN_BAY_BYTES_16BIT );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* B2R begin CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	CT_Im_B2R_Run( ct_idx_1st, ct_idx_2nd, ct_idx_3rd );
	Ddim_Print(( "* B2R end CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	Palladium_Set_Out_Localstack( D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );

	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " end\n" ));
}

static VOID ptImB2rDoTest318( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd )
{
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " begin\n" ));
	memset( (VOID*)D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_IN_BAY_BYTES_16BIT );
	memset( (VOID*)D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Palladium_Set_In_Localstack( D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_B2R_IMG_MEM_IN_BAY_BYTES_16BIT );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* B2R begin CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	CT_Im_B2R_Run( ct_idx_1st, ct_idx_2nd, ct_idx_3rd );
	Ddim_Print(( "* B2R end CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );

	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " end\n" ));
}

static VOID ptImB2rDoTest319( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd )
{
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " begin\n" ));
	memset( (VOID*)D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_IN_BAY_BYTES_16BIT );
	memset( (VOID*)D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Palladium_Set_In_Localstack( D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_B2R_IMG_MEM_IN_BAY_BYTES_16BIT );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* B2R begin CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	CT_Im_B2R_Run( ct_idx_1st, ct_idx_2nd, ct_idx_3rd );
	Ddim_Print(( "* B2R end CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " end\n" ));
}

static VOID ptImB2rDoTest320( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd )
{
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " begin\n" ));
	memset( (VOID*)D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_IN_BAY_BYTES_16BIT );
	memset( (VOID*)D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Palladium_Set_In_Localstack( D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_B2R_IMG_MEM_IN_BAY_BYTES_16BIT );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* B2R begin CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	CT_Im_B2R_Run( ct_idx_1st, ct_idx_2nd, ct_idx_3rd );
	Ddim_Print(( "* B2R end CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " end\n" ));
}

static VOID ptImB2rDoTest321( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd )
{
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " begin\n" ));
	memset( (VOID*)D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_IN_BAY_BYTES_12BIT );
	memset( (VOID*)D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Palladium_Set_In_Localstack( D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_B2R_IMG_MEM_IN_BAY_BYTES_12BIT );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* B2R begin CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	CT_Im_B2R_Run( ct_idx_1st, ct_idx_2nd, ct_idx_3rd );
	Ddim_Print(( "* B2R end CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " end\n" ));
}

static VOID ptImB2rDoTest322( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd )
{
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " begin\n" ));
	memset( (VOID*)D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_IN_BAY_BYTES_12BIT );
	memset( (VOID*)D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Palladium_Set_In_Localstack( D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_B2R_IMG_MEM_IN_BAY_BYTES_12BIT );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* B2R begin CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	CT_Im_B2R_Run( ct_idx_1st, ct_idx_2nd, ct_idx_3rd );
	Ddim_Print(( "* B2R end CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );

	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " end\n" ));
}

static VOID ptImB2rDoTest323( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd )
{
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " begin\n" ));
	memset( (VOID*)D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_IN_BAY_BYTES_10BIT );
	memset( (VOID*)D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Palladium_Set_In_Localstack( D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_B2R_IMG_MEM_IN_BAY_BYTES_10BIT );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* B2R begin CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	CT_Im_B2R_Run( ct_idx_1st, ct_idx_2nd, ct_idx_3rd );
	Ddim_Print(( "* B2R end CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " end\n" ));
}

static VOID ptImB2rDoTest324( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd )
{
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " begin\n" ));
	memset( (VOID*)D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_IN_BAY_BYTES_10BIT );
	memset( (VOID*)D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Palladium_Set_In_Localstack( D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_B2R_IMG_MEM_IN_BAY_BYTES_10BIT );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* B2R begin CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	CT_Im_B2R_Run( ct_idx_1st, ct_idx_2nd, ct_idx_3rd );
	Ddim_Print(( "* B2R end CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );

	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " end\n" ));
}

static VOID ptImB2rDoTest325( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd )
{
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " begin\n" ));
	memset( (VOID*)D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_IN_BAY_BYTES_8BIT );
	memset( (VOID*)D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Palladium_Set_In_Localstack( D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_B2R_IMG_MEM_IN_BAY_BYTES_8BIT );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* B2R begin CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	CT_Im_B2R_Run( ct_idx_1st, ct_idx_2nd, ct_idx_3rd );
	Ddim_Print(( "* B2R end CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );

	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " end\n" ));
}

static VOID ptImB2rDoTest326( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd )
{
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " begin\n" ));

	memset( (VOID*)D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_IN_BAY_BYTES_8BIT );
	memset( (VOID*)D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Palladium_Set_In_Localstack( D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_B2R_IMG_MEM_IN_BAY_BYTES_8BIT );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* B2R begin CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	CT_Im_B2R_Run( ct_idx_1st, ct_idx_2nd, ct_idx_3rd );
	Ddim_Print(( "* B2R end CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " end\n" ));
}

static VOID ptImB2rDoTest327( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd )
{
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " begin\n" ));
	memset( (VOID*)D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_IN_BAY_BYTES_12BIT );
	memset( (VOID*)D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Palladium_Set_In_Localstack( D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_B2R_IMG_MEM_IN_BAY_BYTES_12BIT );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* B2R begin CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	CT_Im_B2R_Run( ct_idx_1st, ct_idx_2nd, ct_idx_3rd );
	Ddim_Print(( "* B2R end CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Palladium_Set_Out_Localstack( D_IM_B2R_IMG_MEM_OUT2_ADDR_TOP, D_IM_B2R_IMG_MEM_IN_BAY_BYTES_12BIT );
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " end\n" ));
}

static VOID ptImB2rDoTest328( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd )
{
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " begin\n" ));
	memset( (VOID*)D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_IN_BAY_BYTES_8BIT );
	memset( (VOID*)D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_OUT_RGB_P12_BYTES );
	Palladium_Set_In_Localstack( D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_B2R_IMG_MEM_IN_BAY_BYTES_8BIT );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* B2R begin CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	CT_Im_B2R_Run( ct_idx_1st, ct_idx_2nd, ct_idx_3rd );
	Ddim_Print(( "* B2R end CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_B2R_IMG_MEM_OUT_RGB_P12_BYTES );
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " end\n" ));
}

static VOID ptImB2rDoTest329( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd )
{
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " begin\n" ));
	memset( (VOID*)D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_IN_BAY_BYTES_16BIT );
	memset( (VOID*)D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Palladium_Set_In_Localstack( D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_B2R_IMG_MEM_IN_BAY_BYTES_16BIT );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* B2R begin CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	CT_Im_B2R_Run( ct_idx_1st, ct_idx_2nd, ct_idx_3rd );
	Ddim_Print(( "* B2R end CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " end\n" ));
}

static VOID ptImB2rDoTest330( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd )
{
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " begin\n" ));

	memset( (VOID*)D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_IN_BAY_BYTES_16BIT );
	memset( (VOID*)D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Palladium_Set_In_Localstack( D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_B2R_IMG_MEM_IN_BAY_BYTES_16BIT );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* B2R begin CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	CT_Im_B2R_Run( ct_idx_1st, ct_idx_2nd, ct_idx_3rd );
	Ddim_Print(( "* B2R end CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " end\n" ));
}

static VOID ptImB2rDoTest331( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd )
{
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " begin\n" ));
	memset( (VOID*)D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_IN_BAY_BYTES_16BIT );
	memset( (VOID*)D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Palladium_Set_In_Localstack( D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_B2R_IMG_MEM_IN_BAY_BYTES_16BIT );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* B2R begin CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	CT_Im_B2R_Run( ct_idx_1st, ct_idx_2nd, ct_idx_3rd );
	Ddim_Print(( "* B2R end CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " end\n" ));
}

static VOID ptImB2rDoTest332( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd )
{
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " begin\n" ));
	memset( (VOID*)D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_IN_BAY_BYTES_16BIT );
	memset( (VOID*)D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Palladium_Set_In_Localstack( D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_B2R_IMG_MEM_IN_BAY_BYTES_16BIT );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* B2R begin CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	CT_Im_B2R_Run( ct_idx_1st, ct_idx_2nd, ct_idx_3rd );
	Ddim_Print(( "* B2R end CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );

	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " end\n" ));
}

static VOID ptImB2rDoTest333( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd )
{
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " begin\n" ));
	memset( (VOID*)D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_IN_BAY_BYTES_16BIT );
	memset( (VOID*)D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Palladium_Set_In_Localstack( D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_B2R_IMG_MEM_IN_BAY_BYTES_16BIT );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* B2R begin CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	CT_Im_B2R_Run( ct_idx_1st, ct_idx_2nd, ct_idx_3rd );
	Ddim_Print(( "* B2R end CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " end\n" ));
}

static VOID ptImB2rDoTest334( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd )
{
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " begin\n" ));
	memset( (VOID*)D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_IN_BAY_BYTES_16BIT );
	memset( (VOID*)D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Palladium_Set_In_Localstack( D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_B2R_IMG_MEM_IN_BAY_BYTES_16BIT );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* B2R begin CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	CT_Im_B2R_Run( ct_idx_1st, ct_idx_2nd, ct_idx_3rd );
	Ddim_Print(( "* B2R end CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES );
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " end\n" ));
}

static VOID ptImB2rDoTest335( const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd )
{
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " begin\n" ));

#if 0
	memset( (VOID*)D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_IN_BAY_BYTES_16BIT );
	memset( (VOID*)D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_B2R_IMG_MEM_OUT_RGB_U16_BYTES );
#endif
	Palladium_Set_In_Localstack( D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_B2R_IMG_MEM_IN_BAY_BYTES_16BIT );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* B2R begin CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	CT_Im_B2R_Run( ct_idx_1st, ct_idx_2nd, ct_idx_3rd );
	Ddim_Print(( "* B2R end CT_Im_B2r_" D_IM_B2R_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_B2R_IMG_MEM_OUT_RGB_U16_BYTES );

	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO " end\n" ));
}

static VOID ptImB2rRun3( const kuint32 type1 )
{
	kuchar			type2;
	kuchar			type3;

	type2	= gDDIM_Info.com._6b;
	type3	= gDDIM_Info.com._6c;

	switch( type2 ) {
		case 1:
			ptImB2rDoTest31( type1, type2, type3 );
			break;
		case 2:
			ptImB2rDoTest32( type1, type2, type3 );
			break;
		case 3:
			ptImB2rDoTest33( type1, type2, type3 );
			break;
		case 4:
			ptImB2rDoTest34( type1, type2, type3 );
			break;
		case 5:
			ptImB2rDoTest35( type1, type2, type3 );
			break;
		case 6:
			ptImB2rDoTest36( type1, type2, type3 );
			break;
		case 7:
			ptImB2rDoTest37( type1, type2, type3 );
			break;
		case 8:
			ptImB2rDoTest38( type1, type2, type3 );
			break;
		case 9:
			ptImB2rDoTest39( type1, type2, type3 );
			break;
		case 10:
			ptImB2rDoTest310( type1, type2, type3 );
			break;
		case 11:
			ptImB2rDoTest311( type1, type2, type3 );
			break;
		case 17:
			ptImB2rDoTest317( type1, type2, type3 );
			break;
		case 18:
			ptImB2rDoTest318( type1, type2, type3 );
			break;
		case 19:
			ptImB2rDoTest319( type1, type2, type3 );
			break;
		case 20:
			ptImB2rDoTest320( type1, type2, type3 );
			break;
		case 21:
			ptImB2rDoTest321( type1, type2, type3 );
			break;
		case 22:
			ptImB2rDoTest322( type1, type2, type3 );
			break;
		case 23:
			ptImB2rDoTest323( type1, type2, type3 );
			break;
		case 24:
			ptImB2rDoTest324( type1, type2, type3 );
			break;
		case 25:
			ptImB2rDoTest325( type1, type2, type3 );
			break;
		case 26:
			ptImB2rDoTest326( type1, type2, type3 );
			break;
		case 27:
			ptImB2rDoTest327( type1, type2, type3 );
			break;
		case 28:
			ptImB2rDoTest328( type1, type2, type3 );
			break;
		case 29:
			ptImB2rDoTest329( type1, type2, type3 );
			break;
		case 30:
			ptImB2rDoTest330( type1, type2, type3 );
			break;
		case 31:
			ptImB2rDoTest331( type1, type2, type3 );
			break;
		case 32:
			ptImB2rDoTest332( type1, type2, type3 );
			break;
		case 33:
			ptImB2rDoTest333( type1, type2, type3 );
			break;
		case 34:
			ptImB2rDoTest334( type1, type2, type3 );
			break;
		case 35:
			ptImB2rDoTest335( type1, type2, type3 );
			break;
		default:
			Ddim_Print(("*** B2R test skip\n" ));
			break;
	}
}

static VOID ptImB2rRun9( const kuint32 type1 )
{
	kuchar			type2;
	type2	= gDDIM_Info.com._6b;
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO "%u begin\n", type2 ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "=-=-=-=-\n" ));
	Ddim_Print(( "* B2R begin CT_Im_B2r_1_%u\n", type2 ));
	CT_Im_B2R_Run( 1, type2, 0 );
	Ddim_Print(( "* B2R end CT_Im_B2r_1_%u\n", type2 ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Ddim_Print(( "*** B2R test " D_IM_B2R_TEST_NO "%u end\n", type2 ));
}

VOID pt_im_b2r_main( VOID )
{
	kuchar			type1;
	Ddim_Print(( "****** B2R begin Pt_Im_B2R_Main\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_INIT );
	type1	= gDDIM_Info.com._6a;
	Dd_Top_Set_CLKSTOP10_B2R1CK( 1 );
	Dd_Top_Set_CLKSEL4_B2R1CLK( 0 );	// 300MHz
	Dd_Top_Set_CLKSTOP10_B2R1CK( 0 );
	Dd_Top_Set_CLKSTOP12_B2R2CK( 1 );
	Dd_Top_Set_CLKSEL6_B2R2CLK( 0 );	// 300MHz
	Dd_Top_Set_CLKSTOP12_B2R2CK( 0 );
	Ddim_Print(( "*** B2R begin Im_B2R_Init\n" ));
	Im_B2R_Init(D_IM_B2R_PIPE12);
	Ddim_Print(( "*** B2R end Im_B2R_Init\n" ));
	ptImB2rEnableGic();
	ptImB2rStartClock();
	switch( type1 ) {
		case 1:
			ptImB2rRun1( type1 );
			break;
		case 2:
			ptImB2rRun2( type1 );
			break;
		case 3:
			ptImB2rRun3( type1 );
			break;
		case 9:
			ptImB2rRun9( type1 );
			break;
		default:
			Ddim_Print(("*** B2R test skip\n" ));
			break;
	}
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_PRINT );
	Ddim_Print(( "(CLKSEL-4)\n" ));
	Ddim_Print(( "B2R1CLK = %d\n", Dd_Top_Get_CLKSEL4_B2R1CLK() ));
	Ddim_Print(( "(CLKSTOP-10)\n" ));
	Ddim_Print(( "B2R1CK = %d\n", Dd_Top_Get_CLKSTOP10_B2R1CK() ));
	Ddim_Print(( "B2R1AP = %d\n", Dd_Top_Get_CLKSTOP10_B2R1AP() ));
	Ddim_Print(( "B2R1AH = %d\n", Dd_Top_Get_CLKSTOP10_B2R1AH() ));
	Ddim_Print(( "B2R1AX = %d\n", Dd_Top_Get_CLKSTOP10_B2R1AX() ));
	Ddim_Print(( "(CLKSEL-6)\n" ));
	Ddim_Print(( "B2R2CLK = %d\n", Dd_Top_Get_CLKSEL6_B2R2CLK() ));
	Ddim_Print(( "(CLKSTOP-12)\n" ));
	Ddim_Print(( "B2R2CK = %d\n", Dd_Top_Get_CLKSTOP12_B2R2CK() ));
	Ddim_Print(( "B2R2AP = %d\n", Dd_Top_Get_CLKSTOP12_B2R2AP() ));
	Ddim_Print(( "B2R2AH = %d\n", Dd_Top_Get_CLKSTOP12_B2R2AH() ));
	Ddim_Print(( "B2R2AX = %d\n", Dd_Top_Get_CLKSTOP12_B2R2AX() ));
	Ddim_Print(( "****** B2R end Pt_Im_B2R_Main\n" ));
	Palladium_Force_Stop();
}

PalladiumTestB2r* palladium_test_b2r_new(void)
{
	PalladiumTestB2r* self = k_object_new_with_private(PALLADIUM_TYPE_TEST_B2R, sizeof(PalladiumTestB2rPrivate));

	return self;
}


