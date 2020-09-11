/*
*
*@Copyright (C) 2010-2020 贵阳高新网用软件有限公司
*@date : 2020-09-08
*@author : aorongxing
*@brief : PalladiumTestTmr64
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 
*
*/

/**
 * @file		palladium_test_tmr64.c
 * @brief		palladium_test_tmr64 process api
 * @note		None
 * @attention	None
 *
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */
#include "palladium_test.h"

#include "dd_gic.h"
#include "dd_top.h"
#include "palladiumtesttmr64.h"


K_TYPE_DEFINE_WITH_PRIVATE(PalladiumTestTmr64, palladium_test_tmr64)
#define PALLADIUM_TEST_TMR64_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), \
											PalladiumTestTmr64Private, PALLADIUM_TYPE_TEST_TMR64))

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
#define PalladiumTestTmr64_CMD_PRM_LEN (16)
#define PalladiumTestTmr64_TFR_PTEST_CMD_TOKEN_NUM (10)

struct _PalladiumTestTmr64Private
{

};

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
static char* S_G_ARGV[PalladiumTestTmr64_TFR_PTEST_CMD_TOKEN_NUM];

/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/
extern VOID Ct_Dd_TMR64_Main( int argc, char** argv );


/*
 * DECLS
 */
static void 	ptDdTmr64ExecuteCmd(int cmdArgc, char* cmdArgv);
static VOID 	ptDdTmr64StartClock( VOID );
static VOID 	ptDdTmr64EnableGic( VOID );

/*
 * IMPL
 */
static void palladium_test_tmr64_constructor(PalladiumTestTmr64 *self)
{
//	PalladiumTestTmr64Private *priv = PALLADIUM_TEST_TMR64_GET_PRIVATE(self);
}

static void palladium_test_tmr64_destructor(PalladiumTestTmr64 *self)
{
//	PalladiumTestTmr64Private *priv = PALLADIUM_TEST_TMR64_GET_PRIVATE(self);
}


static void ptDdTmr64ExecuteCmd(int cmdArgc, char* cmdArgv)
{
    int   j;
    int   cmdPos = 0;

    for (j = 0; j < cmdArgc; j++) {
        S_G_ARGV[j] = (cmdArgv + (cmdPos * PalladiumTestTmr64_CMD_PRM_LEN));
        cmdPos++;
    }
    Ct_Dd_TMR64_Main(cmdArgc, S_G_ARGV);
}

static VOID ptDdTmr64StartClock( VOID )
{
	UCHAR imTmr64RclkCounter = 0;
	UCHAR imTmr64ApbclkCounter = 0;

	Dd_Top_Start_Clock(&imTmr64RclkCounter, &Dd_Top_Get_CLKSTOP2(), ~D_DD_TOP_RCK_BIT);
	Dd_Top_Start_Clock(&imTmr64ApbclkCounter, &Dd_Top_Get_CLKSTOP14(), ~D_DD_TOP_PERIAP_BIT);
}

static VOID ptDdTmr64EnableGic( VOID )
{
//	Dd_GIC_Init();
//	Dd_GIC_Ctrl( E_DD_GIC_INTID_NULL132,  1, D_DD_GIC_PRI30, 1 );		// intid=INT_TMR64_CH, enable, pri=30, cpu=1
}

/*
 * PUBLIC
 */
void palladium_test_tmr64_pt_dd_main(void)
{
	ULONG	time = 50; // 10ms wait (PTで妥当な時間設定か？)      50 msになっていたが試験ではTime = 10 ms???	10 msでOK????

	// GIC interrupt enable
	ptDdTmr64EnableGic();

	// Clock start
	ptDdTmr64StartClock();

	/*	32 div = 10ms Timer
		 8 div = 10ms Timer
		 2 div = 10ms Timer */

	// テストパラメータ取得(RSファイルに紐付く)
	UCHAR testno = gDDIM_Info.com._6a;

	/******************************************************************/
	if ( testno == 1 ) {	// 1-1

		char tmrArgv01[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "open", "0"};
		char tmrArgv02[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "ctrl", "2", "1", "1"};  //"1", "1"?????????
		char tmrArgv03[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "get_table"};
		char tmrArgv04[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "start"};
		char tmrArgv05[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "get_counter"};
		char tmrArgv06[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "stop"};
		char tmrArgv07[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "close"};

		Ddim_Print(("TMR64 1-1 S\n"));
		Ddim_Print(("TMR64 1-1 Open S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv01) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv01);
		Ddim_Print(("TMR64 1-1 Open E\n"));
		Ddim_Print(("TMR64 1-1 Ctrl S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv02) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv02);
		Ddim_Print(("TMR64 1-1 Ctrl E\n"));
		Ddim_Print(("TMR64 1-1 Get_table S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv03) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv03);
		Ddim_Print(("TMR64 1-1 Get_table E\n"));
		Ddim_Print(("TMR64 1-1 Start S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv04) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv04);
		Ddim_Print(("TMR64 1-1 Start E\n"));
		DDIM_User_Dly_Tsk(time);
		Ddim_Print( ("Time wait = %lu (ms) \n", time) );
		Ddim_Print(("TMR64 1-1 Get_counter S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv05) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv05);
		Ddim_Print(("TMR64 1-1 Get_counter E\n"));
		Ddim_Print(("TMR64 1-1 Stop S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv06) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv06);
		Ddim_Print(("TMR64 1-1 Stop E\n"));
		Ddim_Print(("TMR64 1-1 Close S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv07) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv07);
		Ddim_Print(("TMR64 1-1 Close E\n"));
		Ddim_Print(("TMR64 1-1 E\n"));

	/******************************************************************/
	} else if ( testno == 2 ) {		// 1-2

		char tmrArgv01[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "open", "-1"};
		char tmrArgv02[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "ctrl", "8", "1", "1"};  //"1", "1"?????????
		char tmrArgv03[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "get_table"};
		char tmrArgv04[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "start"};
		char tmrArgv05[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "get_counter"};
		char tmrArgv06[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "stop"};
		char tmrArgv07[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "close"};

		Ddim_Print(("TMR64 1-2 S\n"));
		Ddim_Print(("TMR64 1-2 Open S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv01) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv01);
		Ddim_Print(("TMR64 1-2 Open E\n"));
		Ddim_Print(("TMR64 1-2 Ctrl S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv02) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv02);
		Ddim_Print(("TMR64 1-2 Ctrl E\n"));
		Ddim_Print(("TMR64 1-2 Get_table S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv03) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv03);
		Ddim_Print(("TMR64 1-2 Get_table E\n"));
		Ddim_Print(("TMR64 1-2 Start S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv04) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv04);
		Ddim_Print(("TMR64 1-2 Start E\n"));
		DDIM_User_Dly_Tsk(time);
		Ddim_Print( ("Time wait = %lu (ms) \n", time) );
		Ddim_Print(("TMR64 1-2 Get_counter S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv05) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv05);
		Ddim_Print(("TMR64 1-2 Get_counter E\n"));
		Ddim_Print(("TMR64 1-2 Stop S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv06) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv06);
		Ddim_Print(("TMR64 1-2 Stop E\n"));
		Ddim_Print(("TMR64 1-2 Close S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv07) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv07);
		Ddim_Print(("TMR64 1-2 Close E\n"));
		Ddim_Print(("TMR64 1-2 E\n"));

	/******************************************************************/
	} else if ( testno == 3 ) {		// 1-3

		char tmrArgv01[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "open", "5000"};
		char tmrArgv02[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "ctrl", "32", "1", "1"}; //"1", "1"?????????
		char tmrArgv03[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "get_table"};
		char tmrArgv04[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "start"};
		char tmrArgv05[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "get_counter"};
		char tmrArgv06[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "stop"};
		char tmrArgv07[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "close"};

		Ddim_Print(("TMR64 1-3 S\n"));
		Ddim_Print(("TMR64 1-3 Open S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv01) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv01);
		Ddim_Print(("TMR64 1-3 Open E\n"));
		Ddim_Print(("TMR64 1-3 Ctrl S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv02) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv02);
		Ddim_Print(("TMR64 1-3 Ctrl E\n"));
		Ddim_Print(("TMR64 1-3 Get_table S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv03) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv03);
		Ddim_Print(("TMR64 1-3 Get_table E\n"));
		Ddim_Print(("TMR64 1-3 Start S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv04) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv04);
		Ddim_Print(("TMR64 1-3 End S\n"));
		DDIM_User_Dly_Tsk(time);
		Ddim_Print( ("Time wait = %lu (ms) \n", time) );
		Ddim_Print(("TMR64 1-3 Get_counter S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv05) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv05);
		Ddim_Print(("TMR64 1-3 Get_counter E\n"));
		Ddim_Print(("TMR64 1-3 Stop S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv06) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv06);
		Ddim_Print(("TMR64 1-3 Stop E\n"));
		Ddim_Print(("TMR64 1-3 Close S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv07) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv07);
		Ddim_Print(("TMR64 1-3 Close E\n"));
		Ddim_Print(("TMR64 1-3 E\n"));

	/******************************************************************/
	} else if ( testno == 4 ) {		// 1-4

		char tmrArgv01[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "open", "0"};
		char tmrArgv02[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "ctrl", "32", "1", "1"};  //"x", "x"????????? カウンタ値を入力必要！！！！！！
		char tmrArgv03[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "start"};
		char tmrArgv04[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "get_counter"};
		char tmrArgv05[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "pause"};
		char tmrArgv06[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "get_counter"};
		char tmrArgv07[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "start"};
		char tmr_argv_08[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "get_counter"};
		char tmr_argv_09[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "stop"};
		char tmr_argv_10[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "close"};

		Ddim_Print(("TMR64 1-4 S\n"));
		Ddim_Print(("TMR64 1-4 Open S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv01) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv01);
		Ddim_Print(("TMR64 1-4 Open E\n"));
		Ddim_Print(("TMR64 1-4 Ctrl S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv02) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv02);
		Ddim_Print(("TMR64 1-4 Ctrl E\n"));
		Ddim_Print(("TMR64 1-4 Start S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv03) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv03);
		Ddim_Print(("TMR64 1-4 Start E\n"));
		DDIM_User_Dly_Tsk(time);
		Ddim_Print( ("Time wait = %lu (ms) \n", time) );
		Ddim_Print(("TMR64 1-4 Get_counter S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv04) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv04);
		Ddim_Print(("TMR64 1-4 Get_counter E\n"));
		Ddim_Print(("TMR64 1-4 Pause S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv05) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv05);
		Ddim_Print(("TMR64 1-4 Pause E\n"));
		Ddim_Print(("TMR64 1-4 Get_counter S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv06) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv06);
		Ddim_Print(("TMR64 1-4 Get_counter E\n"));
		Ddim_Print(("TMR64 1-4 Start S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv07) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv07);
		Ddim_Print(("TMR64 1-4 Start E\n"));
		DDIM_User_Dly_Tsk(time);
		Ddim_Print( ("Time wait = %lu (ms) \n", time) );
		Ddim_Print(("TMR64 1-4 Get_counter S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmr_argv_08) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmr_argv_08);
		Ddim_Print(("TMR64 1-4 Get_counter E\n"));
		Ddim_Print(("TMR64 1-4 Stop S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmr_argv_09) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmr_argv_09);
		Ddim_Print(("TMR64 1-4 Stop E\n"));
		Ddim_Print(("TMR64 1-4 Close S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmr_argv_10) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmr_argv_10);
		Ddim_Print(("TMR64 1-4 Close E\n"));
		Ddim_Print(("TMR64 1-4 E\n"));



	/******************************************************************/
	} else if ( testno == 5 ) {		// 1-5

		char tmrArgv01[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "open", "0"};
		char tmrArgv02[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "ctrl", "32", "1", "1"};  //"x", "x"????????? カウンタ値を入力必要！！！！！！
		char tmrArgv03[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "start"};
		char tmrArgv04[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "get_gyro"};
		char tmrArgv05[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "pause"};
		char tmrArgv06[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "get_gyro"};
		char tmrArgv07[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "start"};
		char tmr_argv_08[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "get_gyro"};
		char tmr_argv_09[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "stop"};
		char tmr_argv_10[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "close"};

		Ddim_Print(("TMR64 1-5 S\n"));
		Ddim_Print(("TMR64 1-5 Open S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv01) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv01);
		Ddim_Print(("TMR64 1-5 Open E\n"));
		Ddim_Print(("TMR64 1-5 Ctrl S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv02) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv02);
		Ddim_Print(("TMR64 1-5 Ctrl E\n"));
		Ddim_Print(("TMR64 1-5 Start S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv03) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv03);
		Ddim_Print(("TMR64 1-5 Start E\n"));
		DDIM_User_Dly_Tsk(time);
		Ddim_Print( ("Time wait = %lu (ms) \n", time) );
		Ddim_Print(("TMR64 1-5 Get_gyro S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv04) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv04);
		Ddim_Print(("TMR64 1-5 Get_gyro E\n"));
		Ddim_Print(("TMR64 1-5 Pause S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv05) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv05);
		Ddim_Print(("TMR64 1-5 Pause E\n"));
		Ddim_Print(("TMR64 1-5 Get_gyro S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv06) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv06);
		Ddim_Print(("TMR64 1-5 Get_gyro E\n"));
		Ddim_Print(("TMR64 1-5 Start S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv07) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv07);
		Ddim_Print(("TMR64 1-5 Start E\n"));
		DDIM_User_Dly_Tsk(time);
		Ddim_Print( ("Time wait = %lu (ms) \n", time) );
		Ddim_Print(("TMR64 1-5 Get_gyro S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmr_argv_08) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmr_argv_08);
		Ddim_Print(("TMR64 1-5 Get_gyro E\n"));
		Ddim_Print(("TMR64 1-5 Stop S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmr_argv_09) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmr_argv_09);
		Ddim_Print(("TMR64 1-5 Stop E\n"));
		Ddim_Print(("TMR64 1-5 Close S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmr_argv_10) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmr_argv_10);
		Ddim_Print(("TMR64 1-5 Close E\n"));
		Ddim_Print(("TMR64 1-5 E\n"));

	/******************************************************************/
	} else if ( testno == 6 ) {		// 1-6

		char tmrArgv01[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "open", "0"};
		char tmrArgv02[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "ctrl", "32", "1", "1"};  //"x", "x"????????? カウンタ値を入力必要！！！！！！
		char tmrArgv03[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "start"};

		char tmrArgv04[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "get_start"};
		char tmrArgv05[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "pause"};
		char tmrArgv06[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "get_start"};
		char tmrArgv07[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "start"};

		char tmr_argv_08[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "get_start"};
		char tmr_argv_09[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "pause"};
		char tmr_argv_10[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "get_start"};
		char tmr_argv_11[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "start"};

		char tmr_argv_12[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "get_start"};
		char tmr_argv_13[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "pause"};
		char tmr_argv_14[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "get_start"};
		char tmr_argv_15[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "start"};

		char tmr_argv_16[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "get_start"};
		char tmr_argv_17[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "stop"};
		char tmr_argv_18[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "close"};

		Ddim_Print(("TMR64 1-6 S\n"));
		Ddim_Print(("TMR64 1-6 Open S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv01) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv01);
		Ddim_Print(("TMR64 1-6 Open E\n"));
		Ddim_Print(("TMR64 1-6 Ctrl S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv02) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv02);
		Ddim_Print(("TMR64 1-6 Ctrl E\n"));
		Ddim_Print(("TMR64 1-6 Start S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv03) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv03);
		Ddim_Print(("TMR64 1-6 Start E\n"));
		DDIM_User_Dly_Tsk(time);
		Ddim_Print( ("Time wait = %lu (ms) \n", time) );
		Ddim_Print(("TMR64 1-6 Get_start S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv04) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv04);
		Ddim_Print(("TMR64 1-6 Get_start E\n"));
		Ddim_Print(("TMR64 1-6 Pause S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv05) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv05);
		Ddim_Print(("TMR64 1-6 Pause E\n"));
		Ddim_Print(("TMR64 1-6 Get_start S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv06) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv06);
		Ddim_Print(("TMR64 1-6 Get_start E\n"));
		Ddim_Print(("TMR64 1-6 Start S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv07) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv07);
		Ddim_Print(("TMR64 1-6 Start E\n"));
		DDIM_User_Dly_Tsk(time);
		Ddim_Print( ("Time wait = %lu (ms) \n", time) );
		Ddim_Print(("TMR64 1-6 Get_start S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmr_argv_08) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmr_argv_08);
		Ddim_Print(("TMR64 1-6 Get_start E\n"));
		Ddim_Print(("TMR64 1-6 Pause S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmr_argv_09) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmr_argv_09);
		Ddim_Print(("TMR64 1-6 Pause E\n"));
		Ddim_Print(("TMR64 1-6 Get_start S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmr_argv_10) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmr_argv_10);
		Ddim_Print(("TMR64 1-6 Get_start S\n"));
		Ddim_Print(("TMR64 1-6 Start S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmr_argv_11) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmr_argv_11);
		Ddim_Print(("TMR64 1-6 Start E\n"));
		DDIM_User_Dly_Tsk(time);
		Ddim_Print( ("Time wait = %lu (ms) \n", time) );
		Ddim_Print(("TMR64 1-6 Get_start S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmr_argv_12) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmr_argv_12);
		Ddim_Print(("TMR64 1-6 Get_start E\n"));
		Ddim_Print(("TMR64 1-6 Pause S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmr_argv_13) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmr_argv_13);
		Ddim_Print(("TMR64 1-6 Pause E\n"));
		Ddim_Print(("TMR64 1-6 Get_start S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmr_argv_14) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmr_argv_14);
		Ddim_Print(("TMR64 1-6 Get_start S\n"));
		Ddim_Print(("TMR64 1-6 Start S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmr_argv_15) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmr_argv_15);
		Ddim_Print(("TMR64 1-6 Start E\n"));
		DDIM_User_Dly_Tsk(time);
		Ddim_Print( ("Time wait = %lu (ms) \n", time) );
		Ddim_Print(("TMR64 1-6 Get_start S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmr_argv_16) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmr_argv_16);
		Ddim_Print(("TMR64 1-6 Get_start E\n"));
		Ddim_Print(("TMR64 1-6 Stop S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmr_argv_17) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmr_argv_17);
		Ddim_Print(("TMR64 1-6 Stop E\n"));
		Ddim_Print(("TMR64 1-6 Close S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmr_argv_18) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmr_argv_18);
		Ddim_Print(("TMR64 1-6 Close E\n"));
		Ddim_Print(("TMR64 1-6 E\n"));


	/******************************************************************/
	} else if ( testno == 7 ) {		// 1-7

		char tmrArgv01[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "open", "0"};
		char tmrArgv02[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "ctrl", "32", "1", "1"};  //"x", "x"????????? カウンタ値を入力必要！！！！！！
		char tmrArgv03[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "start"};

		char tmrArgv04[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "get_end"};
		char tmrArgv05[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "pause"};
		char tmrArgv06[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "get_end"};
		char tmrArgv07[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "start"};

		char tmr_argv_08[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "get_end"};
		char tmr_argv_09[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "pause"};
		char tmr_argv_10[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "get_end"};
		char tmr_argv_11[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "start"};

		char tmr_argv_12[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "get_end"};
		char tmr_argv_13[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "pause"};
		char tmr_argv_14[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "get_end"};
		char tmr_argv_15[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "start"};

		char tmr_argv_16[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "get_end"};
		char tmr_argv_17[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "stop"};
		char tmr_argv_18[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "close"};

		Ddim_Print(("TMR64 1-7 S\n"));
		Ddim_Print(("TMR64 1-7 Open S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv01) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv01);
		Ddim_Print(("TMR64 1-7 Open E\n"));
		Ddim_Print(("TMR64 1-7 Ctrl S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv02) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv02);
		Ddim_Print(("TMR64 1-7 Ctrl E\n"));
		Ddim_Print(("TMR64 1-7 Start S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv03) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv03);
		Ddim_Print(("TMR64 1-7 Start E\n"));
		DDIM_User_Dly_Tsk(time);
		Ddim_Print( ("Time wait = %lu (ms) \n", time) );
		Ddim_Print(("TMR64 1-7 Get_end S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv04) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv04);
		Ddim_Print(("TMR64 1-7 Get_end E\n"));
		Ddim_Print(("TMR64 1-7 Pause S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv05) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv05);
		Ddim_Print(("TMR64 1-7 Pause E\n"));
		Ddim_Print(("TMR64 1-7 Get_end S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv06) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv06);
		Ddim_Print(("TMR64 1-7 Get_end E\n"));
		Ddim_Print(("TMR64 1-7 Start S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv07) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv07);
		Ddim_Print(("TMR64 1-7 Start E\n"));
		DDIM_User_Dly_Tsk(time);
		Ddim_Print( ("Time wait = %lu (ms) \n", time) );
		Ddim_Print(("TMR64 1-7 Get_end S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmr_argv_08) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmr_argv_08);
		Ddim_Print(("TMR64 1-7 Get_end E\n"));
		Ddim_Print(("TMR64 1-7 Pause S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmr_argv_09) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmr_argv_09);
		Ddim_Print(("TMR64 1-7 Pause E\n"));
		Ddim_Print(("TMR64 1-7 Get_end S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmr_argv_10) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmr_argv_10);
		Ddim_Print(("TMR64 1-7 Get_end S\n"));
		Ddim_Print(("TMR64 1-7 Start S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmr_argv_11) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmr_argv_11);
		Ddim_Print(("TMR64 1-7 Start E\n"));
		DDIM_User_Dly_Tsk(time);
		Ddim_Print( ("Time wait = %lu (ms) \n", time) );
		Ddim_Print(("TMR64 1-7 Get_end S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmr_argv_12) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmr_argv_12);
		Ddim_Print(("TMR64 1-7 Get_end E\n"));
		Ddim_Print(("TMR64 1-7 Pause S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmr_argv_13) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmr_argv_13);
		Ddim_Print(("TMR64 1-7 Pause E\n"));
		Ddim_Print(("TMR64 1-7 Get_end S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmr_argv_14) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmr_argv_14);
		Ddim_Print(("TMR64 1-7 Get_end S\n"));
		Ddim_Print(("TMR64 1-7 Start S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmr_argv_15) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmr_argv_15);
		Ddim_Print(("TMR64 1-7 Start E\n"));
		DDIM_User_Dly_Tsk(time);
		Ddim_Print( ("Time wait = %lu (ms) \n", time) );
		Ddim_Print(("TMR64 1-7 Get_end S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmr_argv_16) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmr_argv_16);
		Ddim_Print(("TMR64 1-7 Get_end E\n"));
		Ddim_Print(("TMR64 1-7 Stop S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmr_argv_17) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmr_argv_17);
		Ddim_Print(("TMR64 1-7 Stop E\n"));
		Ddim_Print(("TMR64 1-7 Close S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmr_argv_18) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmr_argv_18);
		Ddim_Print(("TMR64 1-7 Close E\n"));
		Ddim_Print(("TMR64 1-7 E\n"));



	/******************************************************************/
	} else if ( testno == 8 ) {		// 1-8

		char tmrArgv01[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "get_counter"};
		Ddim_Print(("TMR64 1-8 S\n"));
		Ddim_Print(("TMR64 1-8 Get_counter S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv01) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv01);
		Ddim_Print(("TMR64 1-8 Get_counter E\n"));
		Ddim_Print(("TMR64 1-8 E\n"));

	/******************************************************************/
	} else if ( testno == 9 ) {		// 1-9

		char tmrArgv01[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "load_timestamp"};
		Ddim_Print(("TMR64 1-9 S\n"));
		Ddim_Print(("TMR64 1-9 Load_timestamp S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv01) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv01);
		Ddim_Print(("TMR64 1-9 Load_timestamp E\n"));
		Ddim_Print(("TMR64 1-9 E\n"));

	/******************************************************************/
	} else if ( testno == 10 ) {	// 1-10

		char tmrArgv01[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "load_counter"};
		Ddim_Print(("TMR64 1-10 S\n"));
		Ddim_Print(("TMR64 1-10 Load_counter S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv01) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv01);
		Ddim_Print(("TMR64 1-10 Load_counter E\n"));
		Ddim_Print(("TMR64 1-10 E\n"));

	/******************************************************************/
	} else if ( testno == 11 ) {	// 1-11

		char tmrArgv01[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "open", "0"};
		char tmrArgv02[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "get_table"};
		char tmrArgv03[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "u_start_one"};
		char tmrArgv04[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "stop"};
		char tmrArgv05[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "close"};

		Ddim_Print(("TMR64 1-11 S\n"));
		Ddim_Print(("TMR64 1-11 Open S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv01) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv01);
		Ddim_Print(("TMR64 1-11 Open E\n"));
		Ddim_Print(("TMR64 1-11 Get_table S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv02) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv02);
		Ddim_Print(("TMR64 1-11 Get_table E\n"));
		Ddim_Print(("TMR64 1-11 U_start_one S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv03) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv03);
		Ddim_Print(("TMR64 1-11 U_start_one E\n"));
		Ddim_Print(("TMR64 1-11 Stop S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv04) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv04);
		Ddim_Print(("TMR64 1-11 Stop E\n"));
		Ddim_Print(("TMR64 1-11 Close S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv05) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv05);
		Ddim_Print(("TMR64 1-11 Close E\n"));
		Ddim_Print(("TMR64 1-11 E\n"));



	// test 3-1, test 3-2, test 3-3 ?????



	/******************************************************************/
	} else if ( testno == 21 ) {		// 2-1

		char tmrArgv01[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "test_2_1"};

		Ddim_Print(("TMR64 2-1 S\n"));
		Ddim_Print(("Test 2-1 S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv01) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv01);
		Ddim_Print(("Test 2-1 E\n"));
		Ddim_Print(("TMR64 2-1 E\n"));

	/******************************************************************/
	} else if ( testno == 22 ) {		// 2-2

		char tmrArgv01[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "test_2_2"};

		Ddim_Print(("TMR64 2-2 S\n"));
		Ddim_Print(("Test 2-2 S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv01) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv01);
		Ddim_Print(("Test 2-2 E\n"));
		Ddim_Print(("TMR64 2-2 E\n"));

	/******************************************************************/
	} else if ( testno == 23 ) {		// 2-3

		char tmrArgv01[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "test_2_3"};

		Ddim_Print(("TMR64 2-3 S\n"));
		Ddim_Print(("Test 2-3 S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv01) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv01);
		Ddim_Print(("Test 2-3 E\n"));
		Ddim_Print(("TMR64 2-3 E\n"));

	/******************************************************************/
	} else if ( testno == 24 ) {		// 2-4

		char tmrArgv01[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "test_2_4"};

		Ddim_Print(("TMR64 2-4 S\n"));
		Ddim_Print(("Test 2-4 S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv01) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv01);
		Ddim_Print(("Test 2-4 E\n"));
		Ddim_Print(("TMR64 2-4 E\n"));

	/******************************************************************/
	} else if ( testno == 25 ) {		// 2-5

		char tmrArgv01[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "test_2_5"};

		Ddim_Print(("TMR64 2-5 S\n"));
		Ddim_Print(("Test 2-5 S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv01) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv01);
		Ddim_Print(("Test 2-5 E\n"));
		Ddim_Print(("TMR64 2-5 E\n"));

	/******************************************************************/
	} else if ( testno == 26 ) {		// 2-6

		char tmrArgv01[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "test_2_6"};

		Ddim_Print(("TMR64 2-6 S\n"));
		Ddim_Print(("Test 2-6 S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv01) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv01);
		Ddim_Print(("Test 2-6 E\n"));
		Ddim_Print(("TMR64 2-6 E\n"));

	/******************************************************************/
	} else if ( testno == 27 ) {		// 2-7

		char tmrArgv01[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "test_2_7"};

		Ddim_Print(("TMR64 2-7 S\n"));
		Ddim_Print(("Test 2-7 S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv01) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv01);
		Ddim_Print(("Test 2-7 E\n"));
		Ddim_Print(("TMR64 2-7 E\n"));

	/******************************************************************/
	} else if ( testno == 28 ) {		// 2-8

		char tmrArgv01[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "test_2_8"};

		Ddim_Print(("TMR64 2-8 S\n"));
		Ddim_Print(("Test 2-8 S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv01) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv01);
		Ddim_Print(("Test 2-8 E\n"));
		Ddim_Print(("TMR64 2-8 E\n"));

	/******************************************************************/
	} else if ( testno == 29 ) {		// 2-9

		char tmrArgv01[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "test_2_9"};

		Ddim_Print(("TMR64 2-9 S\n"));
		Ddim_Print(("Test 2-9 S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv01) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv01);
		Ddim_Print(("Test 2-9 E\n"));
		Ddim_Print(("TMR64 2-9 E\n"));

	/******************************************************************/
	} else if ( testno == 30 ) {		// 2-10

		char tmrArgv01[][PalladiumTestTmr64_CMD_PRM_LEN] = {"tmr64", "test_2_10"};

		Ddim_Print(("TMR64 2-10 S\n"));
		Ddim_Print(("Test 2-10 S\n"));
		ptDdTmr64ExecuteCmd((sizeof(tmrArgv01) / PalladiumTestTmr64_CMD_PRM_LEN), (char*)tmrArgv01);
		Ddim_Print(("Test 2-10 E\n"));
		Ddim_Print(("TMR64 2-10 E\n"));

	/******************************************************************/
	}

	Palladium_Force_Stop();

}


PalladiumTestTmr64* palladium_test_tmr64_new(void)
{
	PalladiumTestTmr64* self = k_object_new_with_private(PALLADIUM_TYPE_TEST_TMR64, sizeof(PalladiumTestTmr64Private));

	return self;
}

PalladiumTestTmr64* palladium_test_tmr64_get(void)
{
	static PalladiumTestTmr64* self = NULL;

	if (!self) {
		self = k_object_new_with_private(PALLADIUM_TYPE_TEST_TMR64, sizeof(PalladiumTestTmr64Private));
	}

	return self;
}
