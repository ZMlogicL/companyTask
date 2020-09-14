/*
*@Copyright (C) 2010-2015 上海网用软件有限公司
*@date                :2020-04-20
*@author              :
*@brief               :snsnet
*@rely                :klib
*@function
*SNSFS文件系统，采用ETK-C语言编写
*设计的主要功能:
*@version
*1.0.0 2020年04月开始开发
*/
#include <string.h>

#include "ct_im_fpt.h"
#include "im_fpt.h"
#include "dd_gic.h"
#include "dd_top.h"
#include "driver_common.h"
#include "palladium_test.h"

#include "palladiumtestfpt.h"

K_TYPE_DEFINE_WITH_PRIVATE(PalladiumTestFpt, palladium_test_fpt)
#define PALLADIUM_TEST_FPT_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), PalladiumTestFptPrivate,PALLADIUM_TYPE_TEST_FPT))

#define PalladiumTestFpt_D_IM_FPT0_CLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP4())
#define PalladiumTestFpt_D_IM_FPT0_ICLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP4())
#define PalladiumTestFpt_D_IM_FPT0_HCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP4())
#define PalladiumTestFpt_D_IM_FPT0_PCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP4())

#define PalladiumTestFpt_D_IM_FPT0_CLK_REG_BIT	D_DD_TOP_FPT0CK_BIT	// bit8~9
#define PalladiumTestFpt_D_IM_FPT0_ICLK_REG_BIT	D_DD_TOP_FPT0AX_BIT	// bit10~11
#define PalladiumTestFpt_D_IM_FPT0_HCLK_REG_BIT	D_DD_TOP_FPT0AH_BIT	// bit12~13
#define PalladiumTestFpt_D_IM_FPT0_PCLK_REG_BIT	D_DD_TOP_FPT0AP_BIT	// bit14~15

#define	PalladiumTestFpt_ D_IM_FPT1_CLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP4())
#define PalladiumTestFpt_D_IM_FPT1_ICLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP4())
#define PalladiumTestFpt_D_IM_FPT1_HCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP4())
#define PalladiumTestFpt_D_IM_FPT1_PCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP4())

#define PalladiumTestFpt_D_IM_FPT1_CLK_REG_BIT	D_DD_TOP_FPT1CK_BIT	// bit16~17
#define PalladiumTestFpt_D_IM_FPT1_ICLK_REG_BIT	D_DD_TOP_FPT1AX_BIT	// bit18~19
#define PalladiumTestFpt_D_IM_FPT1_HCLK_REG_BIT	D_DD_TOP_FPT1AH_BIT	// bit20~21
#define PalladiumTestFpt_D_IM_FPT1_PCLK_REG_BIT	D_DD_TOP_FPT1AP_BIT	// bit22~23


#define PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_ADDR_TOP						(0x60000000)
#define PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_Y_ADDR_TOP					(0x60000000)
#define PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_TARGET_Y_ADDR_TOP				(0x64000000)
#define PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_ADDR_TOP	(0x68000000)
#define PalladiumTestFpt_D_IM_FPT_IMG_MEM_OUT_MAP_ADDR_TOP					(0x68000000)
#define PalladiumTestFpt_D_IM_FPT_IMG_MEM_OUT_HIST_ADDR_TOP					(0x70000000)
#define PalladiumTestFpt_D_IM_FPT_IMG_MEM_OUT_FEATURE_AMOUNT_ADDR_TOP		(0x70000000)
#define PalladiumTestFpt_D_IM_FPT_IMG_MEM_OUT_VECTOR_ADDR_TOP				(0x70000000)

#define PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_BYTES							(0x10680)		// 224 * 150 * 2
#define PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_Y_BYTES					(0x10680)		// 224 * 150 * 2
#define PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_TARGET_Y_BYTES					(0x10680)		// 224 * 150 * 2
#define PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_BYTES		(0x200)
#define PalladiumTestFpt_D_IM_FPT_IMG_MEM_OUT_MAP_BYTES						(0x10680)		// 224 * 150 * 2
#define PalladiumTestFpt_D_IM_FPT_IMG_MEM_OUT_HIST_BYTES						(0x200)
#define PalladiumTestFpt_D_IM_FPT_IMG_MEM_OUT_FEATURE_AMOUNT_BYTES			(0x200)
#define PalladiumTestFpt_D_IM_FPT_IMG_MEM_OUT_VECTOR_BYTES					(0x200)

#undef 	PalladiumTestFpt_NO
#define	PalladiumTestFpt_NO "1_1"
#undef	PalladiumTestFpt_NO
#define	PalladiumTestFpt_NO "1_7"
#undef	PalladiumTestFpt_NO
#define	PalladiumTestFpt_NO "2_1"
#undef 	PalladiumTestFpt_NO
#define	PalladiumTestFpt_NO "2_7"
#undef	PalladiumTestFpt_NO
#define	PalladiumTestFpt_NO "3_1"
#undef	PalladiumTestFpt_NO
#define 	PalladiumTestFpt_NO "3_11"
#undef	PalladiumTestFpt_NO
#define	PalladiumTestFpt_NO "3_21"
#undef	PalladiumTestFpt_NO
#define	PalladiumTestFpt_NO "4_1"
#undef 	PalladiumTestFpt_NO
#define	PalladiumTestFpt_NO "4_4"
#undef	PalladiumTestFpt_NO
#define	PalladiumTestFpt_NO "4_5"
#undef	PalladiumTestFpt_NO
#define	PalladiumTestFpt_NO "4_6"
#undef	PalladiumTestFpt_NO
#define	PalladiumTestFpt_NO "4_7"
#undef	PalladiumTestFpt_NO
#define	PalladiumTestFpt_NO "4_8"
#undef	PalladiumTestFpt_NO
#define	PalladiumTestFpt_NO "4_9"
#undef	PalladiumTestFpt_NO
#define	PalladiumTestFpt_NO "4_10"
#undef	PalladiumTestFpt_NO
#define	PalladiumTestFpt_NO "4_11"
#undef	PalladiumTestFpt_NO
#define	PalladiumTestFpt_NO "4_12"
#undef	PalladiumTestFpt_NO
#define	PalladiumTestFpt_NO "4_13"
#undef	PalladiumTestFpt_NO
#define	PalladiumTestFpt_NO "4_14"

struct _PalladiumTestFptPrivate
{
	kint a;
};

static VOID ptImFptEnableGic( VOID );
static VOID ptImFptStartClock( VOID );
static VOID ptImFptDoTest11( const UINT32 ctIdx1st, const UINT32 ctIdx2nd );
static VOID ptImFptDoTest17( const UINT32 ctIdx1st, const UINT32 ctIdx2nd );
static VOID ptImFptRun1( const UINT32 type1 );
static VOID ptImFptDoTest21( const UINT32 ctIdx1st, const UINT32 ctIdx2nd );
static VOID ptImFptDoTest27( const UINT32 ctIdx1st, const UINT32 ctIdx2nd );
static VOID ptImFptRun2( const UINT32 type1 );
static VOID ptImFptDoTest31( const UINT32 ctIdx1st, const UINT32 ctIdx2nd );
static VOID ptImFptDoTest311( const UINT32 ctIdx1st, const UINT32 ctIdx2nd );
static VOID ptImFptDoTest321( const UINT32 ctIdx1st, const UINT32 ctIdx2nd );
static VOID ptImFptRun3( const UINT32 type1 );
static VOID ptImFptDoTest41( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID ptImFptDoTest44( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID ptImFptDoTest45( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID ptImFptDoTest46( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID ptImFptDoTest47( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID ptImFptDoTest48( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID ptImFptDoTest49( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID ptImFptDoTest410( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID ptImFptDoTest411( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID ptImFptDoTest412( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID ptImFptDoTest413( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID ptImFptDoTest414( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID ptImFptRun4( const UINT32 type1 );

static void palladium_test_fpt_constructor(PalladiumTestFpt *self)
{
	PalladiumTestFptPrivate *priv = PALLADIUM_TEST_FPT_GET_PRIVATE(self);
	priv -> a = 0;
}

static void palladium_test_fpt_destructor(PalladiumTestFpt *self)
{
	PalladiumTestFptPrivate *priv = PALLADIUM_TEST_FPT_GET_PRIVATE(self);
	priv -> a = 0;
}

static VOID ptImFptEnableGic( VOID )
{
//	Dd_GIC_Init();
	Dd_GIC_Ctrl( E_DD_GIC_INTID_TIMER_CH0_INT,    1, D_DD_GIC_PRI30, 1 );		//cpu=0, intid=118, enable, pri=30
	Dd_GIC_Ctrl( E_DD_GIC_INTID_FPT_UNIT0_INT,    1, D_DD_GIC_PRI30, 1 );		// int enable
	Dd_GIC_Ctrl( E_DD_GIC_INTID_FPT_UNIT1_INT,    1, D_DD_GIC_PRI30, 1 );		// int enable
}

static VOID ptImFptStartClock( VOID )
{
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_PCLOCK) || defined(CO_ACT_HCLOCK)
#else
	kuchar im_fpt0_clk_ctrl_cnt = 0;
	kuchar im_fpt0_hclk_ctrl_cnt = 0;
	kuchar im_fpt0_pclk_ctrl_cnt = 0;
	kuchar im_fpt0_iclk_ctrl_cnt = 0;
	kuchar im_fpt1_clk_ctrl_cnt = 0;
	kuchar im_fpt1_hclk_ctrl_cnt = 0;
	kuchar im_fpt1_pclk_ctrl_cnt = 0;
	kuchar im_fpt1_iclk_ctrl_cnt = 0;

	Dd_Top_Start_Clock( &im_fpt0_pclk_ctrl_cnt, D_IM_FPT0_PCLK_REG_ADDR, ~D_IM_FPT0_PCLK_REG_BIT );
	Dd_Top_Start_Clock( &im_fpt0_hclk_ctrl_cnt, D_IM_FPT0_HCLK_REG_ADDR, ~D_IM_FPT0_HCLK_REG_BIT );
	Dd_Top_Start_Clock( &im_fpt0_iclk_ctrl_cnt, D_IM_FPT0_ICLK_REG_ADDR, ~D_IM_FPT0_ICLK_REG_BIT );
	Dd_Top_Start_Clock( &im_fpt0_clk_ctrl_cnt,  D_IM_FPT0_CLK_REG_ADDR,  ~D_IM_FPT0_CLK_REG_BIT );

	Dd_Top_Start_Clock( &im_fpt1_pclk_ctrl_cnt, D_IM_FPT1_PCLK_REG_ADDR, ~D_IM_FPT1_PCLK_REG_BIT );
	Dd_Top_Start_Clock( &im_fpt1_hclk_ctrl_cnt, D_IM_FPT1_HCLK_REG_ADDR, ~D_IM_FPT1_HCLK_REG_BIT );
	Dd_Top_Start_Clock( &im_fpt1_iclk_ctrl_cnt, D_IM_FPT1_ICLK_REG_ADDR, ~D_IM_FPT1_ICLK_REG_BIT );
	Dd_Top_Start_Clock( &im_fpt1_clk_ctrl_cnt,  D_IM_FPT1_CLK_REG_ADDR,  ~D_IM_FPT1_CLK_REG_BIT );
#endif
}

static VOID ptImFptDoTest11( const UINT32 ctIdx1st, const UINT32 ctIdx2nd )
{
	static const UCHAR	no_2nd_tbl[] = {
		1, 2, 3, 4, 5, 6,
	};
	kuint32				loopcnt;

	Ddim_Print(( "*** FPT test " PalladiumTestFpt_NO " begin\n" ));


	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	for( loopcnt = 0; loopcnt < (sizeof(no_2nd_tbl) / sizeof(no_2nd_tbl[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* FPT begin CT_Im_Fpt_%u_%u\n", ctIdx1st, no_2nd_tbl[loopcnt] ));
		CT_Im_FPT_Run( ctIdx1st, no_2nd_tbl[loopcnt], 0 );
		Ddim_Print(( "* FPT end CT_Im_Fpt_%u_%u\n", ctIdx1st, no_2nd_tbl[loopcnt] ));
	}

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** FPT test " PalladiumTestFpt_NO " end\n" ));
}

static VOID ptImFptDoTest17( const UINT32 ctIdx1st, const UINT32 ctIdx2nd )
{
	static const UCHAR	no_2nd_tbl[] = {
		7, 8, 9, 10, 11,
	};
	kuint32				loopcnt;

	Ddim_Print(( "*** FPT test " PalladiumTestFpt_NO " begin\n" ));


	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	for( loopcnt = 0; loopcnt < (sizeof(no_2nd_tbl) / sizeof(no_2nd_tbl[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* FPT begin CT_Im_Fpt_%u_%u\n", ctIdx1st, no_2nd_tbl[loopcnt] ));
		CT_Im_FPT_Run( ctIdx1st, no_2nd_tbl[loopcnt], 0 );
		Ddim_Print(( "* FPT end CT_Im_Fpt_%u_%u\n", ctIdx1st, no_2nd_tbl[loopcnt] ));
	}

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** FPT test " PalladiumTestFpt_NO " end\n" ));
}

static VOID ptImFptRun1( const UINT32 type1 )
{
	kuchar			type2;

	type2	= gDDIM_Info.com._6b;

	switch( type2 ) {
		case 1:
			ptImFptDoTest11( type1, type2 );
			break;
		case 7:
			ptImFptDoTest17( type1, type2 );
			break;
		default:
			Ddim_Print(("*** FPT test skip\n" ));
			break;
	}
}

static VOID ptImFptDoTest21( const UINT32 ctIdx1st, const UINT32 ctIdx2nd )
{
	static const UCHAR	no_2nd_tbl[] = {
		1, 2, 3, 4, 5, 6,
	};
	kuint32				loopcnt;

	Ddim_Print(( "*** FPT test " PalladiumTestFpt_NO " begin\n" ));


	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	for( loopcnt = 0; loopcnt < (sizeof(no_2nd_tbl) / sizeof(no_2nd_tbl[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* FPT begin CT_Im_Fpt_%u_%u\n", ctIdx1st, no_2nd_tbl[loopcnt] ));
		CT_Im_FPT_Run( ctIdx1st, no_2nd_tbl[loopcnt], 0 );
		Ddim_Print(( "* FPT end CT_Im_Fpt_%u_%u\n", ctIdx1st, no_2nd_tbl[loopcnt] ));
	}

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** FPT test " PalladiumTestFpt_NO " end\n" ));
}

static VOID ptImFptDoTest27( const UINT32 ctIdx1st, const UINT32 ctIdx2nd )
{
	static const UCHAR	no_2nd_tbl[] = {
		7, 8, 9, 10, 11, 12,
	};
	kuint32				loopcnt;

	Ddim_Print(( "*** FPT test " PalladiumTestFpt_NO " begin\n" ));


	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	for( loopcnt = 0; loopcnt < (sizeof(no_2nd_tbl) / sizeof(no_2nd_tbl[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* FPT begin CT_Im_Fpt_%u_%u\n", ctIdx1st, no_2nd_tbl[loopcnt] ));
		CT_Im_FPT_Run( ctIdx1st, no_2nd_tbl[loopcnt], 0 );
		Ddim_Print(( "* FPT end CT_Im_Fpt_%u_%u\n", ctIdx1st, no_2nd_tbl[loopcnt] ));
	}

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** FPT test " PalladiumTestFpt_NO " end\n" ));
}

static VOID ptImFptRun2( const UINT32 type1 )
{
	kuchar			type2;

	type2	= gDDIM_Info.com._6b;

	switch( type2 ) {
		case 1:
			ptImFptDoTest21( type1, type2 );
			break;
		case 7:
			ptImFptDoTest27( type1, type2 );
			break;
		default:
			Ddim_Print(("*** FPT test skip\n" ));
			break;
	}
}

static VOID ptImFptDoTest31( const UINT32 ctIdx1st, const UINT32 ctIdx2nd )
{
	static const UCHAR	no_2nd_tbl[] = {
		1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
	};
	kuint32				loopcnt;

	Ddim_Print(( "*** FPT test " PalladiumTestFpt_NO " begin\n" ));


	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	for( loopcnt = 0; loopcnt < (sizeof(no_2nd_tbl) / sizeof(no_2nd_tbl[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* FPT begin CT_Im_Fpt_%u_%u\n", ctIdx1st, no_2nd_tbl[loopcnt] ));
		CT_Im_FPT_Run( ctIdx1st, no_2nd_tbl[loopcnt], 0 );
		Ddim_Print(( "* FPT end CT_Im_Fpt_%u_%u\n", ctIdx1st, no_2nd_tbl[loopcnt] ));
	}

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** FPT test " PalladiumTestFpt_NO " end\n" ));
}

static VOID ptImFptDoTest311( const UINT32 ctIdx1st, const UINT32 ctIdx2nd )
{
	static const UCHAR	no_2nd_tbl[] = {
		11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
	};
	kuint32				loopcnt;

	Ddim_Print(( "*** FPT test " PalladiumTestFpt_NO " begin\n" ));


	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	for( loopcnt = 0; loopcnt < (sizeof(no_2nd_tbl) / sizeof(no_2nd_tbl[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* FPT begin CT_Im_Fpt_%u_%u\n", ctIdx1st, no_2nd_tbl[loopcnt] ));
		CT_Im_FPT_Run( ctIdx1st, no_2nd_tbl[loopcnt], 0 );
		Ddim_Print(( "* FPT end CT_Im_Fpt_%u_%u\n", ctIdx1st, no_2nd_tbl[loopcnt] ));
	}

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** FPT test " PalladiumTestFpt_NO " end\n" ));
}

static VOID ptImFptDoTest321( const UINT32 ctIdx1st, const UINT32 ctIdx2nd )
{
	static const UCHAR	no_2nd_tbl[] = {
		21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
	};
	kuint32				loopcnt;

	Ddim_Print(( "*** FPT test " PalladiumTestFpt_NO " begin\n" ));


	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	for( loopcnt = 0; loopcnt < (sizeof(no_2nd_tbl) / sizeof(no_2nd_tbl[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* FPT begin CT_Im_Fpt_%u_%u\n", ctIdx1st, no_2nd_tbl[loopcnt] ));
		CT_Im_FPT_Run( ctIdx1st, no_2nd_tbl[loopcnt], 0 );
		Ddim_Print(( "* FPT end CT_Im_Fpt_%u_%u\n", ctIdx1st, no_2nd_tbl[loopcnt] ));
	}

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** FPT test " PalladiumTestFpt_NO " end\n" ));
}

static VOID ptImFptRun3( const UINT32 type1 )
{
	kuchar			type2;

	type2	= gDDIM_Info.com._6b;

	switch( type2 ) {
		case 1:
			ptImFptDoTest31( type1, type2 );
			break;
		case 11:
			ptImFptDoTest311( type1, type2 );
			break;
		case 21:
			ptImFptDoTest321( type1, type2 );
			break;
		default:
			Ddim_Print(("*** FPT test skip\n" ));
			break;
	}
}

static VOID ptImFptDoTest41( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	static const UCHAR	no_2nd_tbl[] = {
		1, 2, 3,
	};
	UINT32				loopcnt;

	Ddim_Print(( "*** FPT test " PalladiumTestFpt_NO " begin\n" ));


	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	for( loopcnt = 0; loopcnt < (sizeof(no_2nd_tbl) / sizeof(no_2nd_tbl[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* FPT begin CT_Im_Fpt_%u_%u\n", ctIdx1st, no_2nd_tbl[loopcnt] ));
		CT_Im_FPT_Run( ctIdx1st, no_2nd_tbl[loopcnt], ctIdx3rd );
		Ddim_Print(( "* FPT end CT_Im_Fpt_%u_%u\n", ctIdx1st, no_2nd_tbl[loopcnt] ));
	}

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** FPT test " PalladiumTestFpt_NO " end\n" ));
}

static VOID ptImFptDoTest44( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** FPT test " PalladiumTestFpt_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_ADDR_TOP, '\xee', PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_BYTES );
	memset( (VOID*)PalladiumTestFpt_D_IM_FPT_IMG_MEM_OUT_MAP_ADDR_TOP, '\xee', PalladiumTestFpt_D_IM_FPT_IMG_MEM_OUT_MAP_BYTES );
	memset( (VOID*)PalladiumTestFpt_D_IM_FPT_IMG_MEM_OUT_HIST_ADDR_TOP, '\xee', PalladiumTestFpt_D_IM_FPT_IMG_MEM_OUT_HIST_BYTES );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_ADDR_TOP, PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_BYTES );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* FPT begin CT_Im_Fpt_" PalladiumTestFpt_NO "\n" ));
	CT_Im_FPT_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* FPT end CT_Im_Fpt_" PalladiumTestFpt_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( PalladiumTestFpt_D_IM_FPT_IMG_MEM_OUT_MAP_ADDR_TOP, PalladiumTestFpt_D_IM_FPT_IMG_MEM_OUT_MAP_BYTES );
	Palladium_Set_Out_Localstack( PalladiumTestFpt_D_IM_FPT_IMG_MEM_OUT_HIST_ADDR_TOP, PalladiumTestFpt_D_IM_FPT_IMG_MEM_OUT_HIST_BYTES );

	Ddim_Print(( "*** FPT test " PalladiumTestFpt_NO " end\n" ));
}

static VOID ptImFptDoTest45( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** FPT test " PalladiumTestFpt_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_ADDR_TOP, '\xee', PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_BYTES );
	memset( (VOID*)PalladiumTestFpt_D_IM_FPT_IMG_MEM_OUT_MAP_ADDR_TOP, '\xee', PalladiumTestFpt_D_IM_FPT_IMG_MEM_OUT_MAP_BYTES );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_ADDR_TOP, PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_BYTES );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* FPT begin CT_Im_Fpt_" PalladiumTestFpt_NO "\n" ));
	CT_Im_FPT_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* FPT end CT_Im_Fpt_" PalladiumTestFpt_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( PalladiumTestFpt_D_IM_FPT_IMG_MEM_OUT_MAP_ADDR_TOP, PalladiumTestFpt_D_IM_FPT_IMG_MEM_OUT_MAP_BYTES );

	Ddim_Print(( "*** FPT test " PalladiumTestFpt_NO " end\n" ));
}

static VOID ptImFptDoTest46( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** FPT test " PalladiumTestFpt_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_ADDR_TOP, '\xee', PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_BYTES );
	memset( (VOID*)PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_ADDR_TOP, '\xee', PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_BYTES );
	memset( (VOID*)PalladiumTestFpt_D_IM_FPT_IMG_MEM_OUT_FEATURE_AMOUNT_ADDR_TOP, '\xee', PalladiumTestFpt_D_IM_FPT_IMG_MEM_OUT_FEATURE_AMOUNT_BYTES );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_ADDR_TOP, PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_BYTES );
	Palladium_Set_In_Localstack( PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_ADDR_TOP, PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_BYTES );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* FPT begin CT_Im_Fpt_" PalladiumTestFpt_NO "\n" ));
	CT_Im_FPT_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* FPT end CT_Im_Fpt_" PalladiumTestFpt_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( PalladiumTestFpt_D_IM_FPT_IMG_MEM_OUT_FEATURE_AMOUNT_ADDR_TOP, PalladiumTestFpt_D_IM_FPT_IMG_MEM_OUT_FEATURE_AMOUNT_BYTES );

	Ddim_Print(( "*** FPT test " PalladiumTestFpt_NO " end\n" ));
}

static VOID ptImFptDoTest47( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** FPT test " PalladiumTestFpt_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_ADDR_TOP, '\xee', PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_BYTES );
	memset( (VOID*)PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_ADDR_TOP, '\xee', PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_BYTES );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_ADDR_TOP, PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_BYTES );
	Palladium_Set_In_Localstack( PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_ADDR_TOP, PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_BYTES );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* FPT begin CT_Im_Fpt_" PalladiumTestFpt_NO "\n" ));
	CT_Im_FPT_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* FPT end CT_Im_Fpt_" PalladiumTestFpt_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** FPT test " PalladiumTestFpt_NO " end\n" ));
}

static VOID ptImFptDoTest48( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** FPT test " PalladiumTestFpt_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_Y_ADDR_TOP, '\xee', PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_Y_BYTES );
	memset( (VOID*)PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_TARGET_Y_ADDR_TOP, '\xee', PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_ADDR_TOP );
	memset( (VOID*)PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_ADDR_TOP, '\xee', PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_BYTES );
	memset( (VOID*)PalladiumTestFpt_D_IM_FPT_IMG_MEM_OUT_VECTOR_ADDR_TOP, '\xee', PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_BYTES );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_Y_ADDR_TOP, PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_Y_BYTES );
	Palladium_Set_In_Localstack( PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_TARGET_Y_ADDR_TOP, PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_ADDR_TOP );
	Palladium_Set_In_Localstack( PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_ADDR_TOP, PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_BYTES );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* FPT begin CT_Im_Fpt_" PalladiumTestFpt_NO "\n" ));
	CT_Im_FPT_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* FPT end CT_Im_Fpt_" PalladiumTestFpt_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( PalladiumTestFpt_D_IM_FPT_IMG_MEM_OUT_VECTOR_ADDR_TOP, PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_BYTES );

	Ddim_Print(( "*** FPT test " PalladiumTestFpt_NO " end\n" ));
}

static VOID ptImFptDoTest49( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** FPT test " PalladiumTestFpt_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_TARGET_Y_ADDR_TOP, '\xee', PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_ADDR_TOP );
	memset( (VOID*)PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_ADDR_TOP, '\xee', PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_BYTES );
	memset( (VOID*)PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_ADDR_TOP, '\xee', PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_BYTES );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_TARGET_Y_ADDR_TOP, PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_ADDR_TOP );
	Palladium_Set_In_Localstack( PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_ADDR_TOP, PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_BYTES );
	Palladium_Set_In_Localstack( PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_ADDR_TOP, PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_BYTES );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* FPT begin CT_Im_Fpt_" PalladiumTestFpt_NO "\n" ));
	CT_Im_FPT_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* FPT end CT_Im_Fpt_" PalladiumTestFpt_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** FPT test " PalladiumTestFpt_NO " end\n" ));
}

static VOID ptImFptDoTest410( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** FPT test " PalladiumTestFpt_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_Y_ADDR_TOP, '\xee', PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_Y_BYTES );
	memset( (VOID*)PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_TARGET_Y_ADDR_TOP, '\xee', PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_ADDR_TOP );
	memset( (VOID*)PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_ADDR_TOP, '\xee', PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_BYTES );
	memset( (VOID*)PalladiumTestFpt_D_IM_FPT_IMG_MEM_OUT_VECTOR_ADDR_TOP, '\xee', PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_BYTES );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_Y_ADDR_TOP, PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_Y_BYTES );
	Palladium_Set_In_Localstack( PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_TARGET_Y_ADDR_TOP, PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_ADDR_TOP );
	Palladium_Set_In_Localstack( PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_ADDR_TOP, PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_BYTES );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* FPT begin CT_Im_Fpt_" PalladiumTestFpt_NO "\n" ));
	CT_Im_FPT_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* FPT end CT_Im_Fpt_" PalladiumTestFpt_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( PalladiumTestFpt_D_IM_FPT_IMG_MEM_OUT_VECTOR_ADDR_TOP, PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_BYTES );

	Ddim_Print(( "*** FPT test " PalladiumTestFpt_NO " end\n" ));
}

static VOID ptImFptDoTest411( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** FPT test " PalladiumTestFpt_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_TARGET_Y_ADDR_TOP, '\xee', PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_ADDR_TOP );
	memset( (VOID*)PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_ADDR_TOP, '\xee', PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_BYTES );
	memset( (VOID*)PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_ADDR_TOP, '\xee', PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_BYTES );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_TARGET_Y_ADDR_TOP, PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_ADDR_TOP );
	Palladium_Set_In_Localstack( PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_ADDR_TOP, PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_BYTES );
	Palladium_Set_In_Localstack( PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_ADDR_TOP, PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_BYTES );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* FPT begin CT_Im_Fpt_" PalladiumTestFpt_NO "\n" ));
	CT_Im_FPT_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* FPT end CT_Im_Fpt_" PalladiumTestFpt_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** FPT test " PalladiumTestFpt_NO " end\n" ));
}

static VOID ptImFptDoTest412( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** FPT test " PalladiumTestFpt_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_Y_ADDR_TOP, '\xee', PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_Y_BYTES );
	memset( (VOID*)PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_TARGET_Y_ADDR_TOP, '\xee', PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_ADDR_TOP );
	memset( (VOID*)PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_ADDR_TOP, '\xee', PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_BYTES );
	memset( (VOID*)PalladiumTestFpt_D_IM_FPT_IMG_MEM_OUT_VECTOR_ADDR_TOP, '\xee', PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_BYTES );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_Y_ADDR_TOP, PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_Y_BYTES );
	Palladium_Set_In_Localstack( PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_TARGET_Y_ADDR_TOP, PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_ADDR_TOP );
	Palladium_Set_In_Localstack( PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_ADDR_TOP, PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_BYTES );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* FPT begin CT_Im_Fpt_" PalladiumTestFpt_NO "\n" ));
	CT_Im_FPT_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* FPT end CT_Im_Fpt_" PalladiumTestFpt_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( PalladiumTestFpt_D_IM_FPT_IMG_MEM_OUT_VECTOR_ADDR_TOP, PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_BYTES );

	Ddim_Print(( "*** FPT test " PalladiumTestFpt_NO " end\n" ));
}

static VOID ptImFptDoTest413( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** FPT test " PalladiumTestFpt_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_Y_ADDR_TOP, '\xee', PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_Y_BYTES );
	memset( (VOID*)PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_TARGET_Y_ADDR_TOP, '\xee', PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_ADDR_TOP );
	memset( (VOID*)PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_ADDR_TOP, '\xee', PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_BYTES );
	memset( (VOID*)PalladiumTestFpt_D_IM_FPT_IMG_MEM_OUT_FEATURE_AMOUNT_ADDR_TOP, '\xee', PalladiumTestFpt_D_IM_FPT_IMG_MEM_OUT_FEATURE_AMOUNT_BYTES );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_Y_ADDR_TOP, PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_Y_BYTES );
	Palladium_Set_In_Localstack( PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_TARGET_Y_ADDR_TOP, PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_ADDR_TOP );
	Palladium_Set_In_Localstack( PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_ADDR_TOP, PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_BYTES );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* FPT begin CT_Im_Fpt_" PalladiumTestFpt_NO "\n" ));
	CT_Im_FPT_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* FPT end CT_Im_Fpt_" PalladiumTestFpt_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( PalladiumTestFpt_D_IM_FPT_IMG_MEM_OUT_FEATURE_AMOUNT_ADDR_TOP, PalladiumTestFpt_D_IM_FPT_IMG_MEM_OUT_FEATURE_AMOUNT_BYTES );

	Ddim_Print(( "*** FPT test " PalladiumTestFpt_NO " end\n" ));
}

static VOID ptImFptDoTest414( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** FPT test " PalladiumTestFpt_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_Y_ADDR_TOP, '\xee', PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_Y_BYTES );
	memset( (VOID*)PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_TARGET_Y_ADDR_TOP, '\xee', PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_ADDR_TOP );
	memset( (VOID*)PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_ADDR_TOP, '\xee', PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_BYTES );
	memset( (VOID*)PalladiumTestFpt_D_IM_FPT_IMG_MEM_OUT_VECTOR_ADDR_TOP, '\xee', PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_BYTES );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_Y_ADDR_TOP, PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_Y_BYTES );
	Palladium_Set_In_Localstack( PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_TARGET_Y_ADDR_TOP, PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_Y_ADDR_TOP );
	Palladium_Set_In_Localstack( PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_ADDR_TOP, PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_BYTES );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* FPT begin CT_Im_Fpt_" PalladiumTestFpt_NO "\n" ));
	CT_Im_FPT_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* FPT end CT_Im_Fpt_" PalladiumTestFpt_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( PalladiumTestFpt_D_IM_FPT_IMG_MEM_OUT_VECTOR_ADDR_TOP, PalladiumTestFpt_D_IM_FPT_IMG_MEM_IN_BASE_FEATURE_AMOUNT_BYTES );

	Ddim_Print(( "*** FPT test " PalladiumTestFpt_NO " end\n" ));
}

static VOID ptImFptRun4( const UINT32 type1 )
{
	kuchar			type2;
	kuchar			type3;

	type2	= gDDIM_Info.com._6b;
	type3	= gDDIM_Info.com._6c;

	switch( type2 ) {
		case 1:
			ptImFptDoTest41( type1, type2, type3 );
			break;
		case 4:
			ptImFptDoTest44( type1, type2, type3 );
			break;
		case 5:
			ptImFptDoTest45( type1, type2, type3 );
			break;
		case 6:
			ptImFptDoTest46( type1, type2, type3 );
			break;
		case 7:
			ptImFptDoTest47( type1, type2, type3 );
			break;
		case 8:
			ptImFptDoTest48( type1, type2, type3 );
			break;
		case 9:
			ptImFptDoTest49( type1, type2, type3 );
			break;
		case 10:
			ptImFptDoTest410( type1, type2, type3 );
			break;
		case 11:
			ptImFptDoTest411( type1, type2, type3 );
			break;
		case 12:
			ptImFptDoTest412( type1, type2, type3 );
			break;
		case 13:
			ptImFptDoTest413( type1, type2, type3 );
			break;
		case 14:
			ptImFptDoTest414( type1, type2, type3 );
			break;
		default:
			Ddim_Print(("*** FPT test skip\n" ));
			break;
	}
}


VOID palladium_test_fpt_pt_im_fpt_main( VOID )
{
	kuchar			type1;

	// �J�n...
	Ddim_Print(( "****** FPT begin palladium_test_fpt_pt_im_fpt_main\n" ));

	// �^�C�}�[����
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_INIT );

	// �e�X�g�p�����[�^�擾
	type1	= gDDIM_Info.com._6a;

	Dd_Top_Set_CLKSTOP4_FPT0CK( 1 );
	Dd_Top_Set_CLKSEL12_FPT0CLK( 0 );	// 300MHz
	Dd_Top_Set_CLKSTOP4_FPT0CK( 0 );
	Dd_Top_Set_CLKSTOP4_FPT1CK( 1 );
	Dd_Top_Set_CLKSEL12_FPT1CLK( 0 );	// 300MHz
	Dd_Top_Set_CLKSTOP4_FPT1CK( 0 );

	ptImFptEnableGic();
	ptImFptStartClock();

	switch( type1 ) {
		case 1:
			ptImFptRun1( type1 );
			break;
		case 2:
			ptImFptRun2( type1 );
			break;
		case 3:
			ptImFptRun3( type1 );
			break;
		case 4:
			ptImFptRun4( type1 );
			break;
		default:
			Ddim_Print(("*** FPT test skip\n" ));
			break;
	}

	// �^�C�}�[���O�o��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_PRINT );


	Ddim_Print(( "(CLKSEL-12)\n" ));
	Ddim_Print(( "FPT0CLK = %d\n", Dd_Top_Get_CLKSEL12_FPT0CLK() ));
	Ddim_Print(( "(CLKSTOP-4)\n" ));
	Ddim_Print(( "FPT0CK = %d\n", Dd_Top_Get_CLKSTOP4_FPT0CK() ));
	Ddim_Print(( "FPT0AP = %d\n", Dd_Top_Get_CLKSTOP4_FPT0AP() ));
	Ddim_Print(( "FPT0AH = %d\n", Dd_Top_Get_CLKSTOP4_FPT0AH() ));
	Ddim_Print(( "FPT0AX = %d\n", Dd_Top_Get_CLKSTOP4_FPT0AX() ));
	Ddim_Print(( "(CLKSEL-12)\n" ));
	Ddim_Print(( "FPT1CLK = %d\n", Dd_Top_Get_CLKSEL12_FPT1CLK() ));
	Ddim_Print(( "(CLKSTOP-4)\n" ));
	Ddim_Print(( "FPT1CK = %d\n", Dd_Top_Get_CLKSTOP4_FPT1CK() ));
	Ddim_Print(( "FPT1AP = %d\n", Dd_Top_Get_CLKSTOP4_FPT1AP() ));
	Ddim_Print(( "FPT1AH = %d\n", Dd_Top_Get_CLKSTOP4_FPT1AH() ));
	Ddim_Print(( "FPT1AX = %d\n", Dd_Top_Get_CLKSTOP4_FPT1AX() ));
	Ddim_Print(( "****** FPT end palladium_test_fpt_pt_im_fpt_main\n" ));

	// �e�X�g�����I������
	Palladium_Force_Stop();
}

PalladiumTestFpt* palladium_test_fpt_new(void)
{
	PalladiumTestFpt *self = k_object_new_with_private(PALLADIUM_TYPE_TEST_FPT, sizeof(PalladiumTestFptPrivate));
	return self;
}
