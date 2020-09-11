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


/**
 * @file		palladium_test_sdramc.c
 * @brief		SDRAMC test code on palladium
 * @note		None
 * @attention	None
 *
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */

#include "im_sdramc.h"
#include "ct_im_sdramc.h"
#include "dd_gic.h"
#include "dd_top.h"
#include "driver_common.h"
#include "palladium_test.h"

#include "palladiumtestsdramc.h"


K_TYPE_DEFINE_WITH_PRIVATE(PalladiumTestSdramc, palladium_test_sdramc);
#define PALLADIUM_TEST_SDRAMC_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), PalladiumTestSdramcPrivate,PALLADIUM_TYPE_TEST_SDRAMC))

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
#define PalladiumTestSdramc_PT_SDRAMC_CMD_LEN			(20)


struct _PalladiumTestSdramcPrivate
{
	int a;
};

//私有函数声明
static VOID 					ptImSdramcEnableGic( VOID );
static VOID 					ptImSdramcStartClock( VOID );

#if 0
static void 					ptImSdramcExecuteCmd( int cmdArgc, char* cmdArgv );
#endif

//构造函数
static void 					palladium_test_sdramc_constructor(PalladiumTestSdramc *self)
{
	PalladiumTestSdramcPrivate *priv = PALLADIUM_TEST_SDRAMC_GET_PRIVATE(self);
	priv->a = 0;
}

//析构函数
static void palladium_test_sdramc_destructor(PalladiumTestSdramc *self)
{
}

/*
 * DECLS
 */

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
//static char* gCmd_Argv[ PalladiumTestSdramc_PT_SDRAMC_CMD_LEN ];

/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Local Method Definition												*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/
static VOID ptImSdramcEnableGic( VOID )
{
	Dd_GIC_Ctrl( E_DD_GIC_INTID_TIMER_CH0_INT,  1, D_DD_GIC_PRI30, 1 );		// cpu=0, intid=118, enable, pri=30
	Dd_GIC_Ctrl( E_DD_GIC_INTID_SDRAMC_CH0_INT, 1, D_DD_GIC_PRI30, 1 );		// int enable
	Dd_GIC_Ctrl( E_DD_GIC_INTID_SDRAMC_CH1_INT, 1, D_DD_GIC_PRI30, 1 );		// int enable
}


static VOID ptImSdramcStartClock( VOID )
{
	UCHAR imSdramcPclkCtrlCnt[ 2 ] = { 0, 0 };

	Dd_Top_Start_Clock( (UCHAR*)&imSdramcPclkCtrlCnt[ 0 ], &Dd_Top_Get_CLKSTOP9(), ~D_DD_TOP_UMC0AP_BIT );
	Dd_Top_Start_Clock( (UCHAR*)&imSdramcPclkCtrlCnt[ 1 ], &Dd_Top_Get_CLKSTOP9(), ~D_DD_TOP_UMC1AP_BIT );
}

#if 0
static void ptImSdramcExecuteCmd( int cmdArgc, char* cmdArgv )
{
	INT32 j;
	INT32 cmdPos = 0;

	for( j = 0; j < cmdArgc; j++ ) {
		gCmd_Argv[ j ] = ( cmdArgv + ( cmdPos * PalladiumTestSdramc_PT_SDRAMC_CMD_LEN ) );
		cmdPos++;
	}

	Ct_Im_SDRAMC_Main( cmdArgc, gCmd_Argv );
}
#endif

/*
 * PUBLIC
 */

/*----------------------------------------------------------------------*/
/* Global Function														*/
/*----------------------------------------------------------------------*/
/**
 * @brief		SDRAMC main code
 * @param		void
 * @return		void
 * @note		None
 * @attention	None
 */
void palladium_test_sdramc_im_sdramc_main( void )
{
	UINT32	testno;

	// 開始...
	Ddim_Print(( "****** SDRAMC begin palladium_test_sdramc_im_sdramc_main\n" ));

	// タイマー初期化
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_INIT );

	// テストパラメータ取得
	testno	= gDDIM_Info.com._6a;

	Ddim_Print(( "****** Palladium Test %d begin\n", testno ));

	ptImSdramcEnableGic();
	ptImSdramcStartClock();

	while( 1 ) {

		if ( testno == 0 ) {
			// タイマー起動
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

			CT_Im_SDRAMC_1_01( 0 );

			CT_Im_SDRAMC_1_01( 1 );

			// タイマー停止
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
		}
		else if ( testno == 1 ) {
			// タイマー起動
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

			CT_Im_SDRAMC_1_02( 0 );

			CT_Im_SDRAMC_1_02( 1 );

			// タイマー停止
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
		}
		else if ( testno == 2 ) {
			// タイマー起動
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

			CT_Im_SDRAMC_1_03( 0 );

			CT_Im_SDRAMC_1_03( 1 );

			// タイマー停止
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
		}
		else if ( testno == 3 ) {
			// タイマー起動
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

			CT_Im_SDRAMC_1_04( 0 );

			CT_Im_SDRAMC_1_04( 1 );

			// タイマー停止
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
		}
		else if ( testno == 4 ) {
			// タイマー起動
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

			CT_Im_SDRAMC_1_05( 0 );

			CT_Im_SDRAMC_1_05( 1 );

			// タイマー停止
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
		}
		// Self refresh mode start/stop.
		else if ( testno == 5 ) {
			// タイマー起動
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

			CT_Im_SDRAMC_1_06( 0 );

			CT_Im_SDRAMC_1_06( 1 );

			// タイマー停止
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
		}
		// Access detection start/stop/get.
		else if ( testno == 6 ) {
			// タイマー起動
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

			CT_Im_SDRAMC_1_07( 0 );

			CT_Im_SDRAMC_1_07( 1 );

			// タイマー停止
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
		}
		else if ( testno == 7 ) {
			// タイマー起動
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

			CT_Im_SDRAMC_1_08( 0 );

			CT_Im_SDRAMC_1_08( 1 );

			// タイマー停止
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
		}
		else if ( testno == 8 ) {
			// タイマー起動
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

			CT_Im_SDRAMC_1_09( 0 );

			CT_Im_SDRAMC_1_09( 1 );

			// タイマー停止
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
		}
		else if ( testno == 9 ) {
			// タイマー起動
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

			CT_Im_SDRAMC_1_10( 0 );

			CT_Im_SDRAMC_1_10( 1 );

			// タイマー停止
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
		}
		else if ( testno == 10 ) {
			// タイマー起動
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

			CT_Im_SDRAMC_1_11( 0 );

			CT_Im_SDRAMC_1_11( 1 );

			// タイマー停止
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
		}
		else if ( testno == 11 ) {
			// タイマー起動
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

			CT_Im_SDRAMC_1_12( 0 );

			CT_Im_SDRAMC_1_12( 1 );

			// タイマー停止
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
		}
		else {
			Ddim_Print(("*** RS Parameter Error\n" ));
		}

		break;
	}

	// タイマーログ出力
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_PRINT );

	Ddim_Print(( "****** Palladium Test %d end\n", testno ));

	// Force stop
	Palladium_Force_Stop();
}




PalladiumTestSdramc* palladium_test_sdramc_new(void)
{
	PalladiumTestSdramc *self = k_object_new_with_private(PALLADIUM_TYPE_TEST_SDRAMC,sizeof(PalladiumTestSdramcPrivate));
	return self;
}
