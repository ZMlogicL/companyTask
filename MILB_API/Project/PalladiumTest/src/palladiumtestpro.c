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

#include "palladium_test.h"
#include "ct_im_pro.h"

#include "im_pro.h"
#include "im_pro_common.h"

#include "dd_top.h"
#include "dd_gic.h"

#include "palladiumtestpro.h"



typedef struct _PalladiumTestProPrivate		PalladiumTestProPrivate;
struct _PalladiumTestProPrivate
{
	int a;
};

K_TYPE_DEFINE_WITH_PRIVATE(PalladiumTestPro, palladium_test_pro)
#define PALLADIUM_TEST_PRO_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), PalladiumTestProPrivate,PALLADIUM_TYPE_TEST_PRO))
#define PalladiumTestPro_TEST_NO "1_1"

static VOID ptImProPrintClockStatus( UCHAR* idx );
static VOID ptImProEnableGic( VOID );
static VOID ptImProStartClock( VOID );
static VOID ptImProRun1( const UINT32 type1 );

static void palladium_test_pro_constructor(PalladiumTestPro *self)
{
	PalladiumTestProPrivate *priv = PALLADIUM_TEST_PRO_GET_PRIVATE(self);
	priv -> a = 0;
}

static void palladium_test_pro_destructor(PalladiumTestPro *self)
{
	PalladiumTestProPrivate *priv = PALLADIUM_TEST_PRO_GET_PRIVATE(self);
	priv -> a = 0;
}

static VOID ptImProPrintClockStatus( UCHAR* idx )
{
	Ddim_Print(( "--------ptImProPrintClockStatus(%u)--------\n", *idx ));
	*idx += 1;
	Ddim_Print(( "(CLKSEL-3)\n" ));
	Ddim_Print(( "SENCLK   = %d\n", Dd_Top_Get_CLKSEL3_SENCLK() ));
	Ddim_Print(( "PASCLK   = %d\n", Dd_Top_Get_CLKSEL3_PASCLK() ));
	Ddim_Print(( "(CLKSEL-4)\n" ));
	Ddim_Print(( "SRO1CLK_2= %d\n", Dd_Top_Get_CLKSEL4_SRO1CLK_2() ));
	Ddim_Print(( "(CLKSEL-5)\n" ));
	Ddim_Print(( "SRO1CLK  = %d\n", Dd_Top_Get_CLKSEL5_SRO1CLK() ));
	Ddim_Print(( "B2B1CLK  = %d\n", Dd_Top_Get_CLKSEL5_B2B1CLK() ));
	Ddim_Print(( "(CLKSEL-6)\n" ));
	Ddim_Print(( "SRO2CLK_2= %d\n", Dd_Top_Get_CLKSEL4_SRO1CLK_2() ));
	Ddim_Print(( "(CLKSEL-7)\n" ));
	Ddim_Print(( "SRO2CLK  = %d\n", Dd_Top_Get_CLKSEL5_SRO1CLK() ));
	Ddim_Print(( "B2B2CLK  = %d\n", Dd_Top_Get_CLKSEL7_B2B2CLK() ));
	Ddim_Print(( "(CLKSEL-8)\n" ));
	Ddim_Print(( "APCLK    = %d\n", Dd_Top_Get_CLKSEL8_APCLK() ));
	Ddim_Print(( "AP0SEL   = %d\n", Dd_Top_Get_CLKSEL8_AP0SEL() ));
	Ddim_Print(( "AP1SEL   = %d\n", Dd_Top_Get_CLKSEL8_AP1SEL() ));
	Ddim_Print(( "AP2SEL   = %d\n", Dd_Top_Get_CLKSEL8_AP2SEL() ));
	Ddim_Print(( "AP3SEL   = %d\n", Dd_Top_Get_CLKSEL8_AP3SEL() ));
	Ddim_Print(( "(CLKSTOP-1)\n" ));
	Ddim_Print(( "SENCK    = %d\n", Dd_Top_Get_CLKSTOP1_SENCK() ));
	Ddim_Print(( "SENAX    = %d\n", Dd_Top_Get_CLKSTOP1_SENAX() ));
	Ddim_Print(( "SENAH    = %d\n", Dd_Top_Get_CLKSTOP1_SENAH() ));
	Ddim_Print(( "SENAP    = %d\n", Dd_Top_Get_CLKSTOP1_SENAP() ));
	Ddim_Print(( "(CLKSTOP-4)\n" ));
	Ddim_Print(( "APCK0    = %d\n", Dd_Top_Get_CLKSTOP4_APCK0() ));
	Ddim_Print(( "APCK1    = %d\n", Dd_Top_Get_CLKSTOP4_APCK1() ));
	Ddim_Print(( "APCK2    = %d\n", Dd_Top_Get_CLKSTOP4_APCK2() ));
	Ddim_Print(( "APCK3    = %d\n", Dd_Top_Get_CLKSTOP4_APCK3() ));
	Ddim_Print(( "(CLKSTOP-10)\n" ));
	Ddim_Print(( "SRO1CK   = %d\n", Dd_Top_Get_CLKSTOP10_SRO1CK() ));
	Ddim_Print(( "SRO1CK_2 = %d\n", Dd_Top_Get_CLKSTOP10_SRO1CK_2() ));
	Ddim_Print(( "SRO1AX   = %d\n", Dd_Top_Get_CLKSTOP10_SRO1AX() ));
	Ddim_Print(( "SRO1AH   = %d\n", Dd_Top_Get_CLKSTOP10_SRO1AH() ));
	Ddim_Print(( "SRO1AP   = %d\n", Dd_Top_Get_CLKSTOP10_SRO1AP() ));
	Ddim_Print(( "B2B1CK   = %d\n", Dd_Top_Get_CLKSTOP10_B2B1CK() ));
	Ddim_Print(( "B2B1AX   = %d\n", Dd_Top_Get_CLKSTOP10_B2B1AX() ));
	Ddim_Print(( "B2B1AH   = %d\n", Dd_Top_Get_CLKSTOP10_B2B1AH() ));
	Ddim_Print(( "B2B1AP   = %d\n", Dd_Top_Get_CLKSTOP10_B2B1AP() ));
	Ddim_Print(( "(CLKSTOP-12)\n" ));
	Ddim_Print(( "SRO2CK   = %d\n", Dd_Top_Get_CLKSTOP12_SRO2CK() ));
	Ddim_Print(( "SRO2CK_2 = %d\n", Dd_Top_Get_CLKSTOP12_SRO2CK_2() ));
	Ddim_Print(( "SRO2AX   = %d\n", Dd_Top_Get_CLKSTOP12_SRO2AX() ));
	Ddim_Print(( "SRO2AH   = %d\n", Dd_Top_Get_CLKSTOP12_SRO2AH() ));
	Ddim_Print(( "SRO2AP   = %d\n", Dd_Top_Get_CLKSTOP12_SRO2AP() ));
	Ddim_Print(( "B2B2CK   = %d\n", Dd_Top_Get_CLKSTOP12_B2B2CK() ));
	Ddim_Print(( "B2B2AX   = %d\n", Dd_Top_Get_CLKSTOP12_B2B2AX() ));
	Ddim_Print(( "B2B2AH   = %d\n", Dd_Top_Get_CLKSTOP12_B2B2AH() ));
	Ddim_Print(( "B2B2AP   = %d\n", Dd_Top_Get_CLKSTOP12_B2B2AP() ));
	Ddim_Print(( "(CLKSTOP-14)\n" ));
	Ddim_Print(( "STATAX   = %d\n", Dd_Top_Get_CLKSTOP14_STATAX() ));
	Ddim_Print(( "STATAH   = %d\n", Dd_Top_Get_CLKSTOP14_STATAH() ));
	Ddim_Print(( "STATAP   = %d\n", Dd_Top_Get_CLKSTOP14_STATAP() ));
	Ddim_Print(( "PASCK    = %d\n", Dd_Top_Get_CLKSTOP14_PASCK() ));
	Ddim_Print(( "------------------------------------------------\n" ));
}

static VOID ptImProEnableGic( VOID )
{
	Dd_GIC_Ctrl( E_DD_GIC_INTID_TIMER_CH0_INT,    1, D_DD_GIC_PRI30, 1 );		//cpu=0, intid=118, enable, pri=30

	Dd_GIC_Ctrl( E_DD_GIC_INTID_SEN_INT,				1, D_DD_GIC_PRI30, 1 );		// int enable
	Dd_GIC_Ctrl( E_DD_GIC_INTID_SEN_VD_INT,				1, D_DD_GIC_PRI30, 1 );		// int enable
	Dd_GIC_Ctrl( E_DD_GIC_INTID_SEN_HD_INT,				1, D_DD_GIC_PRI30, 1 );		// int enable
	Dd_GIC_Ctrl( E_DD_GIC_INTID_SENSOR_IF_MACRO0_INT,	1, D_DD_GIC_PRI30, 1 );		// int enable
	Dd_GIC_Ctrl( E_DD_GIC_INTID_SENSOR_IF_MACRO1_INT,	1, D_DD_GIC_PRI30, 1 );		// int enable
	Dd_GIC_Ctrl( E_DD_GIC_INTID_SENSOR_IF_MACRO2_INT,	1, D_DD_GIC_PRI30, 1 );		// int enable
	Dd_GIC_Ctrl( E_DD_GIC_INTID_SENSOR_IF_MACRO3_INT,	1, D_DD_GIC_PRI30, 1 );		// int enable
	Dd_GIC_Ctrl( E_DD_GIC_INTID_SRO_UNIT1_INT,			1, D_DD_GIC_PRI30, 1 );		// int enable
	Dd_GIC_Ctrl( E_DD_GIC_INTID_SRO_UNIT1_VD_INT,		1, D_DD_GIC_PRI30, 1 );		// int enable
	Dd_GIC_Ctrl( E_DD_GIC_INTID_SRO_UNIT1_HD_INT,		1, D_DD_GIC_PRI30, 1 );		// int enable
	Dd_GIC_Ctrl( E_DD_GIC_INTID_SRO_UNIT2_INT,			1, D_DD_GIC_PRI30, 1 );		// int enable
	Dd_GIC_Ctrl( E_DD_GIC_INTID_SRO_UNIT2_VD_INT,		1, D_DD_GIC_PRI30, 1 );		// int enable
	Dd_GIC_Ctrl( E_DD_GIC_INTID_SRO_UNIT2_HD_INT,		1, D_DD_GIC_PRI30, 1 );		// int enable
	Dd_GIC_Ctrl( E_DD_GIC_INTID_B2B_UNIT1_INT,			1, D_DD_GIC_PRI30, 1 );		// int enable
	Dd_GIC_Ctrl( E_DD_GIC_INTID_B2B_UNIT1_VD_INT,		1, D_DD_GIC_PRI30, 1 );		// int enable
	Dd_GIC_Ctrl( E_DD_GIC_INTID_B2B_UNIT1_HD_INT,		1, D_DD_GIC_PRI30, 1 );		// int enable
	Dd_GIC_Ctrl( E_DD_GIC_INTID_B2B_UNIT2_INT,			1, D_DD_GIC_PRI30, 1 );		// int enable
	Dd_GIC_Ctrl( E_DD_GIC_INTID_B2B_UNIT2_VD_INT,		1, D_DD_GIC_PRI30, 1 );		// int enable
	Dd_GIC_Ctrl( E_DD_GIC_INTID_B2B_UNIT2_HD_INT,		1, D_DD_GIC_PRI30, 1 );		// int enable
	Dd_GIC_Ctrl( E_DD_GIC_INTID_START_INT,				1, D_DD_GIC_PRI30, 1 );		// int enable
	Dd_GIC_Ctrl( E_DD_GIC_INTID_PAS_UNIT2_INT,			1, D_DD_GIC_PRI30, 1 );		// int enable
	Dd_GIC_Ctrl( E_DD_GIC_INTID_PAS_UNIT2_VD_INT,		1, D_DD_GIC_PRI30, 1 );		// int enable
	Dd_GIC_Ctrl( E_DD_GIC_INTID_PAS_UNIT2_HD_INT,		1, D_DD_GIC_PRI30, 1 );		// int enable
}

static VOID ptImProStartClock( VOID )
{
	UCHAR clkIdx = 0;

	Dd_Top_Set_CLKSTOP4_APCK0( 1 );
	Dd_Top_Set_CLKSTOP4_APCK1( 1 );
	Dd_Top_Set_CLKSTOP4_APCK2( 1 );
	Dd_Top_Set_CLKSTOP4_APCK3( 1 );

	im_pro_off_drive_clk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN  );
	im_pro_off_drive_clk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SRO  );
	im_pro_off_drive_clk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_B2B  );
	im_pro_off_drive_clk( E_IM_PRO_UNIT_NUM_2, E_IM_PRO_CLK_BLOCK_TYPE_SRO  );
	im_pro_off_drive_clk( E_IM_PRO_UNIT_NUM_2, E_IM_PRO_CLK_BLOCK_TYPE_B2B  );

	Dd_Top_Set_CLKSEL3_SENCLK( 0x0 );
	Dd_Top_Set_CLKSEL5_SRO1CLK( 0x0 );
	Dd_Top_Set_CLKSEL4_SRO1CLK_2( 0x0 );
	Dd_Top_Set_CLKSEL7_SRO2CLK( 0x0 );
	Dd_Top_Set_CLKSEL6_SRO2CLK_2( 0x0 );
	Dd_Top_Set_CLKSEL5_B2B1CLK( 1 << 3 );
	Dd_Top_Set_CLKSEL7_B2B2CLK( 1 << 3 );
	Dd_Top_Set_CLKSEL3_PASCLK( 0x0 );

	Dd_Top_Set_CLKSEL8_APCLK(0x4);
	Dd_Top_Set_CLKSEL8_AP0SEL(1);
	Dd_Top_Set_CLKSEL8_AP1SEL(1);
	Dd_Top_Set_CLKSEL8_AP2SEL(1);
	Dd_Top_Set_CLKSEL8_AP3SEL(1);

	Dd_Top_Set_CLKSTOP4_APCK0( 0 );
	Dd_Top_Set_CLKSTOP4_APCK1( 0 );
	Dd_Top_Set_CLKSTOP4_APCK2( 0 );
	Dd_Top_Set_CLKSTOP4_APCK3( 0 );

	im_pro_on_drive_clk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN  );
	im_pro_on_drive_clk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SRO  );
	im_pro_on_drive_clk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SRO2 );
	im_pro_on_drive_clk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_B2B  );
	im_pro_on_drive_clk( E_IM_PRO_UNIT_NUM_2, E_IM_PRO_CLK_BLOCK_TYPE_SRO  );
	im_pro_on_drive_clk( E_IM_PRO_UNIT_NUM_2, E_IM_PRO_CLK_BLOCK_TYPE_SRO2 );
	im_pro_on_drive_clk( E_IM_PRO_UNIT_NUM_2, E_IM_PRO_CLK_BLOCK_TYPE_B2B  );

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN  );
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SRO  );
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_B2B  );
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_2, E_IM_PRO_CLK_BLOCK_TYPE_SRO  );
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_2, E_IM_PRO_CLK_BLOCK_TYPE_B2B  );
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );

	im_pro_on_hclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN  );
	im_pro_on_hclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SRO  );
	im_pro_on_hclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_B2B  );
	im_pro_on_hclk( E_IM_PRO_UNIT_NUM_2, E_IM_PRO_CLK_BLOCK_TYPE_SRO  );
	im_pro_on_hclk( E_IM_PRO_UNIT_NUM_2, E_IM_PRO_CLK_BLOCK_TYPE_B2B  );
	im_pro_on_hclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );

	im_pro_on_xclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN  );
	im_pro_on_xclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SRO  );
	im_pro_on_xclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_B2B  );
	im_pro_on_xclk( E_IM_PRO_UNIT_NUM_2, E_IM_PRO_CLK_BLOCK_TYPE_SRO  );
	im_pro_on_xclk( E_IM_PRO_UNIT_NUM_2, E_IM_PRO_CLK_BLOCK_TYPE_B2B  );
	im_pro_on_xclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );

	ptImProPrintClockStatus( &clkIdx );
}

static VOID ptImProRun1( const UINT32 type1 )
{
	static const UCHAR	S_NO_2ND_TBL[] = {
		1, 2, 3,
	};
	kuint32				loopcnt;

	Ddim_Print(( "*** PRO test " PalladiumTestPro_TEST_NO " begin\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	for( loopcnt = 0; loopcnt < (sizeof(S_NO_2ND_TBL) / sizeof(S_NO_2ND_TBL[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* PRO begin ct_im_pro_%u_%u\n", 8, S_NO_2ND_TBL[loopcnt] ));
		ct_im_pro_Run( 8, S_NO_2ND_TBL[loopcnt], 0, 0 );
		Ddim_Print(( "* PRO end ct_im_pro_%u_%u\n", 8, S_NO_2ND_TBL[loopcnt] ));
	}

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** PRO test " PalladiumTestPro_TEST_NO " end\n" ));
}

void palladium_test_pro_main( void )
{
	kuchar		clkIdx = 0;
	UCHAR	type1;
	Ddim_Print(( "****** PRO begin palladium_test_pro_main\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_INIT );
	type1	= gDDIM_Info.com._6a;
	ptImProEnableGic();

	ptImProStartClock();

	switch( type1 ) {
		case 1:
			ptImProRun1( type1 );
			break;

		default:
			Ddim_Print(("*** PRO test skip\n" ));
			break;
	}

	ptImProPrintClockStatus( &clkIdx );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_PRINT );
	Palladium_Force_Stop();
	Ddim_Print(( "****** PRO end palladium_test_pro_main\n" ));
}

PalladiumTestPro* palladium_test_pro_new(void)
{
	PalladiumTestPro *self = k_object_new_with_private(PALLADIUM_TYPE_TEST_PRO, sizeof(PalladiumTestProPrivate));
	return self;
}
