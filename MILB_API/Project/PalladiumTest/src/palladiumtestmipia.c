/*
*@Copyright (C) 2010-2015 上海网用软件有限公司
*@date                :2020-06-13
*@author              :
*@brief               :snsos
*@rely                :klib
*@function
*采用ETK-C语言抄写代码
*设计的主要功能:
*@version
*1.0.0 2020年06月开始开发
*/

#include "ddim_user_custom.h"
#include "palladium_test_common.h"
#include "palladium_test.h"
#include "dd_gic.h"
#include "dd_top.h"
#include "ct_im_mipi.h"
#include "im_mipi.h"
#include "im_disp.h"
#include "jdsdisp3a.h"
#include "palladiumtestmipia.h"

K_TYPE_DEFINE_WITH_PRIVATE(PalladiumTestMipiA, palladium_test_mipi_a);
#define PALLADIUM_TEST_MIPI_A_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), PalladiumTestMipiAPrivate,PALLADIUM_TYPE_TEST_MIPI_A))

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
#define PalladiumTestMipiA_D_PT_MIPI_CMD_LEN				(10)
#define PalladiumTestMipiA_D_PT_MIPI_CLKSTOP_REG_ADDR		(&Dd_Top_Get_CLKSTOP3())
#define PalladiumTestMipiA_D_PT_MIPI_PCLK_ON				(0x00008000)	// bit[15:14]=10.
#define PalladiumTestMipiA_D_PT_MIPI_HCLK_ON				(0x00020000)	// bit[17:16]=10.
#define PalladiumTestMipiA_D_PT_MIPI_ICLK_ON				(0x00080000)	// bit[19:18]=10.

struct _PalladiumTestMipiAPrivate
{
	int a;
};

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
static char* S_GCMD_ARGV[ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ];

static VOID 				ptImMipiEnableGic( VOID );
static VOID 				ptImMipiStartClock( VOID );
static void 				ptImMipiExecuteCmd( int cmd_argc, char* cmd_argv ) ;

static void palladium_test_mipi_a_constructor(PalladiumTestMipiA *self)
{
	PalladiumTestMipiAPrivate *priv = PALLADIUM_TEST_MIPI_A_GET_PRIVATE(self);
}

static void palladium_test_mipi_a_destructor(PalladiumTestMipiA *self)
{
	PalladiumTestMipiAPrivate *priv = PALLADIUM_TEST_MIPI_A_GET_PRIVATE(self);
}


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
static VOID ptImMipiEnableGic( VOID )
{
	Dd_GIC_Ctrl( E_DD_GIC_INTID_MIPI_DSI_Tx_INT, 1, D_DD_GIC_PRI30, 1);		// int enable
}

static VOID ptImMipiStartClock( VOID )
{
	UCHAR im_mipi_iclk_ctrl_cnt = 0;
	UCHAR im_mipi_pclk_ctrl_cnt = 0;
	UCHAR im_mipi_hclk_ctrl_cnt = 0;

	Dd_Top_Start_Clock( &im_mipi_iclk_ctrl_cnt, PalladiumTestMipiA_D_PT_MIPI_CLKSTOP_REG_ADDR, PalladiumTestMipiA_D_PT_MIPI_ICLK_ON );
	Dd_Top_Start_Clock( &im_mipi_pclk_ctrl_cnt, PalladiumTestMipiA_D_PT_MIPI_CLKSTOP_REG_ADDR, PalladiumTestMipiA_D_PT_MIPI_PCLK_ON );
	Dd_Top_Start_Clock( &im_mipi_hclk_ctrl_cnt, PalladiumTestMipiA_D_PT_MIPI_CLKSTOP_REG_ADDR, PalladiumTestMipiA_D_PT_MIPI_HCLK_ON );
}

static void ptImMipiExecuteCmd( int cmd_argc, char* cmd_argv )
{
	INT32 j;
	INT32 cmd_pos = 0;

	for( j = 0; j < cmd_argc; j++ ) {
		S_GCMD_ARGV[ j ] = ( cmd_argv + ( cmd_pos * PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ) );
		cmd_pos++;
	}

	Ct_Im_Mipi_Main( cmd_argc, S_GCMD_ARGV );
}


/*----------------------------------------------------------------------*/
/* Global Function														*/
/*----------------------------------------------------------------------*/
/**
 * @brief		Test code
 * @param		void
 * @return		void
 * @note		None
 * @attention	None
 */
VOID palladium_test_mipi_a_pt_Im_mipi_main(PalladiumTestMipiA* self)
{
	UINT32	testno;

	// 開始...
	Ddim_Print(( "****** MIPI begin Pt_Im_Mipi_Main\n" ));

	// タイマー初期化
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_INIT );

	// テストパラメータ取得
	testno	= gDDIM_Info.com._6a;

	Ddim_Print(( "****** Palladium Test %d begin\n", testno ));

	ptImMipiEnableGic();
	ptImMipiStartClock();

	while( 1 ) {

		// Im_MIPI_Init.
		if ( testno == 0 ) {
			// タイマー起動
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

			char test_argv1[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "init", "0" };

			// test 1-1-1.
			ptImMipiExecuteCmd((sizeof(test_argv1) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv1);

			// タイマー停止
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
		}
		// Im_MIPI_Power_Ctrl.
		else if ( testno == 1 ) {
			// タイマー起動
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

			char test_argv1[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "pc", "1" };

			// test 1-1-2.
			ptImMipiExecuteCmd((sizeof(test_argv1) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv1);

			// タイマー停止
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
		}
		// Im_MIPI_Enter_Ulps, Im_MIPI_Exit_Ulps.
		else if ( testno == 2 ) {
			// タイマー起動
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

			char test_argv1[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "init", "0" };
			char test_argv2[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "ulps", "enter", "0", "0" };
			char test_argv3[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "ulps", "enter", "1" };
			char test_argv4[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "ulps", "enter", "2" };
			char test_argv5[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "ulps", "exit", "0", "0" };
			char test_argv6[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "ulps", "exit", "1" };

			// Im_MIPI_Init
			ptImMipiExecuteCmd((sizeof(test_argv1) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv1);

			// test 1-1-3.
			ptImMipiExecuteCmd((sizeof(test_argv2) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv2);
			// test 1-1-4.
			ptImMipiExecuteCmd((sizeof(test_argv3) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv3);
			ptImMipiExecuteCmd((sizeof(test_argv4) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv4);
			// test 1-1-5.
			ptImMipiExecuteCmd((sizeof(test_argv5) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv5);
			// test 1-1-6.
			ptImMipiExecuteCmd((sizeof(test_argv6) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv6);

			// タイマー停止
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
		}
		// Im_MIPI_Set_Lane_Info, Im_MIPI_Get_Lane_Info.
		else if ( testno == 3 ) {
			// タイマー起動
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

			char test_argv1[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "init", "0" };
			char test_argv2[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "lane", "set", "0", "0" };
			char test_argv3[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "lane", "set", "1" };
			char test_argv4[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "lane", "get", "0", "0" };
			char test_argv5[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "lane", "get", "1" };

			// Im_MIPI_Init
			ptImMipiExecuteCmd((sizeof(test_argv1) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv1);

			// test 1-1-7.
			ptImMipiExecuteCmd((sizeof(test_argv2) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv2);
			// test 1-1-8.
			ptImMipiExecuteCmd((sizeof(test_argv3) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv3);
			// test 1-1-9.
			ptImMipiExecuteCmd((sizeof(test_argv4) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv4);
			// test 1-1-10.
			ptImMipiExecuteCmd((sizeof(test_argv5) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv5);

			// タイマー停止
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
		}
		// Im_MIPI_Set_DPI_Resolution, Im_MIPI_Get_DPI_Resolution / Im_MIPI_Update_Dpi.
		else if ( testno == 4 ) {
			// タイマー起動
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

			char test_argv1[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "init", "0" };
			char test_argv2[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "dpi", "set", "0", "0" };
			char test_argv3[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "dpi", "set", "1" };
			char test_argv4[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "dpi", "get", "0", "0" };
			char test_argv5[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "dpi", "get", "1" };
			char test_argv6[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "dpi", "update", "0" };
			char test_argv7[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "dpi", "update", "1" };
			char test_argv8[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "dpi", "update", "2" };

			// Im_MIPI_Init
			ptImMipiExecuteCmd((sizeof(test_argv1) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv1);

			// test 1-1-11.
			ptImMipiExecuteCmd((sizeof(test_argv2) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv2);
			// test 1-1-12.
			ptImMipiExecuteCmd((sizeof(test_argv3) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv3);
			// test 1-1-13.
			ptImMipiExecuteCmd((sizeof(test_argv4) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv4);
			// test 1-1-14.
			ptImMipiExecuteCmd((sizeof(test_argv5) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv5);
			// test 1-1-15.
			ptImMipiExecuteCmd((sizeof(test_argv6) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv6);
			// test 1-1-16.
			ptImMipiExecuteCmd((sizeof(test_argv7) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv7);
			ptImMipiExecuteCmd((sizeof(test_argv8) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv8);

			// タイマー停止
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
		}
		// Im_MIPI_Set_Transmission_Configuration, Im_MIPI_Get_Transmission_Configuration.
		else if ( testno == 5 ) {
			// タイマー起動
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

			char test_argv1[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "init", "0" };
			char test_argv2[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "tc", "set", "0", "0" };
			char test_argv3[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "tc", "set", "1" };
			char test_argv4[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "tc", "get", "0", "0" };
			char test_argv5[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "tc", "get", "1" };

			// Im_MIPI_Init
			ptImMipiExecuteCmd((sizeof(test_argv1) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv1);

			// test 1-1-17.
			ptImMipiExecuteCmd((sizeof(test_argv2) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv2);
			// test 1-1-18.
			ptImMipiExecuteCmd((sizeof(test_argv3) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv3);
			// test 1-1-19.
			ptImMipiExecuteCmd((sizeof(test_argv4) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv4);
			// test 1-1-20.
			ptImMipiExecuteCmd((sizeof(test_argv5) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv5);

			// タイマー停止
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
		}
		// Im_MIPI_Packet_Transmission, Im_MIPI_Packet_Transmission.
		else if ( testno == 6 ) {
			// タイマー起動
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

			char test_argv1[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "init", "0" };
			char test_argv2[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "pt", "0", "4" };
			char test_argv3[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "pt", "1" };

			// Im_MIPI_Init
			ptImMipiExecuteCmd((sizeof(test_argv1) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv1);

			// test 1-1-21.
			ptImMipiExecuteCmd((sizeof(test_argv2) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv2);
			// test 1-1-22.
			ptImMipiExecuteCmd((sizeof(test_argv3) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv3);

			// タイマー停止
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
		}
		// Im_MIPI_Set_Timer_Count.
		else if ( testno == 7 ) {
			// タイマー起動
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

			char test_argv1[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "init", "0" };
			char test_argv2[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "timer", "set", "0" };

			// Im_MIPI_Init
			ptImMipiExecuteCmd((sizeof(test_argv1) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv1);

			// test 1-1-23.
			ptImMipiExecuteCmd((sizeof(test_argv2) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv2);

			// タイマー停止
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
		}
		// Im_MIPI_Set_Int_Mask, Im_MIPI_Get_Int_Mask.
		else if ( testno == 8 ) {
			// タイマー起動
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

			char test_argv1[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "init", "0" };
			char test_argv2[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "mask", "set", "0" };
			char test_argv3[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "mask", "get", "0" };
			char test_argv4[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "mask", "get", "1" };

			// Im_MIPI_Init
			ptImMipiExecuteCmd((sizeof(test_argv1) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv1);

			// test 1-1-24.
			ptImMipiExecuteCmd((sizeof(test_argv2) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv2);
			// test 1-1-25.
			ptImMipiExecuteCmd((sizeof(test_argv3) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv3);
			// test 1-1-26.
			ptImMipiExecuteCmd((sizeof(test_argv4) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv4);

			// タイマー停止
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
		}
		// Im_MIPI_Set_Int_Callback.
		else if ( testno == 9 ) {
			// タイマー起動
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

			char test_argv1[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "init", "0" };
			char test_argv2[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "cb", "set", "0", "1" };
			char test_argv3[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "cb", "set", "5", "0" };

			// Im_MIPI_Init
			ptImMipiExecuteCmd((sizeof(test_argv1) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv1);

			// test 1-1-27.
			ptImMipiExecuteCmd((sizeof(test_argv2) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv2);
			// test 1-1-28.
			ptImMipiExecuteCmd((sizeof(test_argv3) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv3);

			// タイマー停止
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
		}
		// Im_MIPI_Int_Handler.
		else if ( testno == 10 ) {
			// タイマー起動
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

			char test_argv1[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "init", "0" };
			char test_argv2[][ PalladiumTestMipiA_D_PT_MIPI_CMD_LEN ] = { "immipi", "int", "0" };

			// Im_MIPI_Init
			ptImMipiExecuteCmd((sizeof(test_argv1) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv1);

			// test 1-1-29.
			ptImMipiExecuteCmd((sizeof(test_argv2) / PalladiumTestMipiA_D_PT_MIPI_CMD_LEN), (char*)test_argv2);

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

	Ddim_Print(( "****** Palladium MIPI Test end\n" ));

	// Force stop
	Palladium_Force_Stop();
}

ddd
PalladiumTestMipiA* palladium_test_mipi_a_new(void)
{
	PalladiumTestMipiA *self = k_object_new(PALLADIUM_TYPE_TEST_MIPI_A);
	return self;
}
