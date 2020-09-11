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
#include "palladium_test_common.h"
#include "palladium_test.h"
#include "palladium_test_interrupt.h"
#include "dd_gic.h"
#include "dd_top.h"
#include "ct_dd_tmr32.h"

#include "palladiumtesttmr32.h"

K_TYPE_DEFINE_WITH_PRIVATE(PalladiumTestTmr32, palladium_test_tmr32)
#define PALLADIUM_TEST_TMR32_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), PalladiumTestTmr32Private,PALLADIUM_TYPE_TEST_TMR32))

#define PalladiumTestTmr32_CMD_PRM_LEN (16)
#define PalladiumTestTmr32_TFR_PTEST_CMD_TOKEN_NUM (10)

struct _PalladiumTestTmr32Private
{
	kint a;
};

extern VOID Ct_Dd_TMR32_Main( kint argc, char** argv );
#if 0
static char* S_GARGV[TFR_PTEST_CMD_TOKEN_NUM];
#endif

/*
 * DECLS
 */

#if 0
static void ptDdTmr32ExecuteCmd(kint cmdArgc, char* cmdArgv);
#else
static void ptDdTmr32ExecuteCmd(char* cmdArgv[]);
#endif
static VOID ptDdTmr32StartClock( VOID );
static VOID pt_dd_tmr32_enable_gic( VOID );

static void palladium_test_tmr32_constructor(PalladiumTestTmr32 *self)
{
	PalladiumTestTmr32Private *priv = PALLADIUM_TEST_TMR32_GET_PRIVATE(self);
	priv -> a = 0;
}

static void palladium_test_tmr32_destructor(PalladiumTestTmr32 *self)
{
	PalladiumTestTmr32Private *priv = PALLADIUM_TEST_TMR32_GET_PRIVATE(self);
	priv -> a = 0;
}

/*
 * DECLS
 */

#if 0
static void ptDdTmr32ExecuteCmd(kint cmdArgc, char* cmdArgv)
{
    kint   j;
    kint   cmdPos = 0;

    for (j = 0; j < cmdArgc; j++) {
        S_GARGV[j] = (cmdArgv + (cmdPos * PalladiumTestTmr32_CMD_PRM_LEN));
        cmdPos++;
    }
    Ct_Dd_TMR32_Main(cmdArgc, S_GARGV);
}
#else
static void ptDdTmr32ExecuteCmd(char* cmdArgv[])
{
    kint   j;
    kint   cmdPos = 0;

    for (j = 0; cmdArgv[j] != NULL; j++) {
        cmdPos++;
    }
    Ct_Dd_TMR32_Main(cmdPos, cmdArgv);
}
#endif

static VOID ptDdTmr32StartClock( VOID )
{
	UCHAR imTmr32RclkCounter = 0;
	UCHAR imTmr32ApbclkCounter = 0;

	Dd_Top_Start_Clock(&imTmr32RclkCounter, &Dd_Top_Get_CLKSTOP2(), ~D_DD_TOP_RCK_BIT);
	Dd_Top_Start_Clock(&imTmr32ApbclkCounter, &Dd_Top_Get_CLKSTOP14(), ~D_DD_TOP_PERIAP_BIT);
}

static VOID pt_dd_tmr32_enable_gic( VOID )
{
//	Dd_GIC_Init();
	Dd_GIC_Ctrl( E_DD_GIC_INTID_TIMER_CH0_INT,  1, D_DD_GIC_PRI30, 1 );		// intid=INT_TMR32_CH0, enable, pri=30, cpu=1
	Dd_GIC_Ctrl( E_DD_GIC_INTID_TIMER_CH1_INT,  1, D_DD_GIC_PRI30, 1 );		// intid=INT_TMR32_CH1, enable, pri=30, cpu=1
	Dd_GIC_Ctrl( E_DD_GIC_INTID_TIMER_CH2_INT,  1, D_DD_GIC_PRI30, 1 );		// intid=INT_TMR32_CH2, enable, pri=30, cpu=1
	Dd_GIC_Ctrl( E_DD_GIC_INTID_TIMER_CH3_INT,  1, D_DD_GIC_PRI30, 1 );		// intid=INT_TMR32_CH3, enable, pri=30, cpu=1
	Dd_GIC_Ctrl( E_DD_GIC_INTID_TIMER_CH4_INT,  1, D_DD_GIC_PRI30, 1 );		// intid=INT_TMR32_CH4, enable, pri=30, cpu=1
	Dd_GIC_Ctrl( E_DD_GIC_INTID_TIMER_CH5_INT,  1, D_DD_GIC_PRI30, 1 );		// intid=INT_TMR32_CH5, enable, pri=30, cpu=1
	Dd_GIC_Ctrl( E_DD_GIC_INTID_TIMER_CH6_INT,  1, D_DD_GIC_PRI30, 1 );		// intid=INT_TMR32_CH6, enable, pri=30, cpu=1
	Dd_GIC_Ctrl( E_DD_GIC_INTID_TIMER_CH7_INT,  1, D_DD_GIC_PRI30, 1 );		// intid=INT_TMR32_CH7, enable, pri=30, cpu=1
	Dd_GIC_Ctrl( E_DD_GIC_INTID_TIMER_CH8_INT,  1, D_DD_GIC_PRI30, 1 );		// intid=INT_TMR32_CH8, enable, pri=30, cpu=1
	Dd_GIC_Ctrl( E_DD_GIC_INTID_TIMER_CH9_INT,  1, D_DD_GIC_PRI30, 1 );		// intid=INT_TMR32_CH9, enable, pri=30, cpu=1
	Dd_GIC_Ctrl( E_DD_GIC_INTID_TIMER_CH10_INT, 1, D_DD_GIC_PRI30, 1 );		// intid=INT_TMR32_CH10, enable, pri=30, cpu=1
	Dd_GIC_Ctrl( E_DD_GIC_INTID_TIMER_CH11_INT, 1, D_DD_GIC_PRI30, 1 );		// intid=INT_TMR32_CH11, enable, pri=30, cpu=1
	Dd_GIC_Ctrl( E_DD_GIC_INTID_TIMER_CH12_INT, 1, D_DD_GIC_PRI30, 1 );		// intid=INT_TMR32_CH12, enable, pri=30, cpu=1
	Dd_GIC_Ctrl( E_DD_GIC_INTID_TIMER_CH13_INT, 1, D_DD_GIC_PRI30, 1 );		// intid=INT_TMR32_CH13, enable, pri=30, cpu=1
}

/*
 * PUBLIC
 */

void palladium_test_tmr32_pt_dd_tmr32_main(void)
{
	ULONG	time = 10; // 10ms wait				ULONG	time = 50; // 50ms wait        //50 ms or 10 ms ???????

	// GIC interrupt enable
	pt_dd_tmr32_enable_gic();

	// Clock start
	ptDdTmr32StartClock();

	/*	32 div = 10ms Timer
		 8 div = 10ms Timer
		 2 div = 10ms Timer */


	// タイマー初期化
    Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_INIT);
	// タイマー起動
    Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_START);


	// テストパラメータ取得(RSファイルに紐付く)
	UCHAR testno = gDDIM_Info.com._6a;




	// chの選択ができるように変更 (ch数が増加の為、増加したchのテストの為に変更 (新たなch = 10-13)
	kint num;
	char *ch_num[]={"5", "10", "13", NULL}; // without ch1 and ch4 for PT
	for (num = 0; ch_num[num] != NULL; num++) {
        Ddim_Print(("ch_num( %d ) = %s\n", num, ch_num[num]));
    }
	Ddim_Print(("dd_tmr32 Test Start.. \n"));




	// main
	for(num = 0; ch_num[num] != NULL; num++){								// 複数のchを設定できるように変更
		Ddim_Print(("ch_num( %d ) = %s\n", num, ch_num[num]));

		if ( testno == 1 ) {	// 1-1
			Ddim_Print(("TMR32 1-1 S\n"));
			Ddim_Print(("TMR32 1-1 Open S\n"));
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "open", ch_num[num], "0", NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			Ddim_Print(("TMR32 1-1 Open E\n"));
			Ddim_Print(("TMR32 1-1 Ctrl S\n"));
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "ctrl", ch_num[num], "2", "reload", "270000", "270000", "1", "u", NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			Ddim_Print(("TMR32 1-1 Ctrl E\n"));
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "get_table", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			Ddim_Print(("TMR32 1-1 Start S\n"));
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "start", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			DDIM_User_Dly_Tsk(time);
			Ddim_Print(("TMR32 1-1 Start E\n"));
			Ddim_Print(("TMR32 1-1 Stop S\n"));
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "stop", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			Ddim_Print(("TMR32 1-1 Stop E\n"));
			Ddim_Print(("TMR32 1-1 Close S\n"));
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "close", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			Ddim_Print(("TMR32 1-1 Close E\n"));
			Ddim_Print(("TMR32 1-1 E\n"));

		////////////////////////////////////////////////////////////////////
		} else if ( testno == 2 ) {		// 1-2
			Ddim_Print(("TMR32 1-2 S\n"));
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "open", ch_num[num], "-1", NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "ctrl", ch_num[num], "8", "one", "67500", "67500", "1", "u", NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "get_table", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "start", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			DDIM_User_Dly_Tsk(time);
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "stop", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "close", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			Ddim_Print(("TMR32 1-2 E\n"));

		////////////////////////////////////////////////////////////////////
		} else if ( testno == 3 ) {		// 1-3
			Ddim_Print(("TMR32 1-3 S\n"));
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "open", ch_num[num], "5000", NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "ctrl", ch_num[num], "32", "reload", "16875", "16875", "1", "d", NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "get_table", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "start", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			DDIM_User_Dly_Tsk(time);
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "stop", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "close", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			Ddim_Print(("TMR32 1-3 E\n"));

		////////////////////////////////////////////////////////////////////
		} else if ( testno == 4 ) {		// 1-4
			Ddim_Print(("TMR32 1-4 S\n"));
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "open", ch_num[num], "0", NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "ctrl", ch_num[num], "32", "reload", "16875", "16875", "2", "b", NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "get_table", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "start", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			DDIM_User_Dly_Tsk(time);
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "stop", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "close", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			Ddim_Print(("TMR32 1-4 E\n"));

		////////////////////////////////////////////////////////////////////
		} else if ( testno == 5 ) {		// 1-5
			Ddim_Print(("TMR32 1-5 S\n"));
			Ddim_Print(("TMR32 1-5 Open S\n"));
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "open", ch_num[num], "-1", NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			Ddim_Print(("TMR32 1-5 Open E\n"));
			Ddim_Print(("TMR32 1-5 Ctrl S\n"));
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "ctrl", ch_num[num], "2", "reload", "270000", "270000", "2", "d", NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			Ddim_Print(("TMR32 1-5 Ctrl E\n"));
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "get_table", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "get_reload", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "set_reload", ch_num[num], "0", NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "get_reload", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			Ddim_Print(("TMR32 1-5 Start S\n"));
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "start", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			DDIM_User_Dly_Tsk(time);
			Ddim_Print(("TMR32 1-5 Start E\n"));
			Ddim_Print(("TMR32 1-5 Stop S\n"));
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "stop", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			Ddim_Print(("TMR32 1-5 Stop E\n"));
			Ddim_Print(("TMR32 1-5 Close S\n"));
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "close", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			Ddim_Print(("TMR32 1-5 Close E\n"));
			Ddim_Print(("TMR32 1-5 E\n"));

		////////////////////////////////////////////////////////////////////
		} else if ( testno == 6 ) {		// 1-6
			Ddim_Print(("TMR32 1-6 S\n"));
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "open", ch_num[num], "4000", NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "ctrl", ch_num[num], "8", "reload", "67500", "67500", "2", "d", NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "get_table", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "start", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			DDIM_User_Dly_Tsk(time);
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "stop", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "close", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			Ddim_Print(("TMR32 1-6 E\n"));

		////////////////////////////////////////////////////////////////////
		} else if ( testno == 7 ) {		// 1-7
			Ddim_Print(("TMR32 1-7 S\n"));
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "open", ch_num[num], "0", NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "ctrl", ch_num[num], "32", "reload", "16875", "16875", "1", "d", NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "get_table", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "start", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			DDIM_User_Dly_Tsk(time);
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "pause", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			Ddim_Print(("Timer Pause. Start\n"));

			DDIM_User_Dly_Tsk(time);

			Ddim_Print(("Timer Pause. End\n"));
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "get_counter", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "get_table", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "start", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			DDIM_User_Dly_Tsk(time);
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "stop", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "close", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			Ddim_Print(("TMR32 1-7 E\n"));

		////////////////////////////////////////////////////////////////////
		} else if ( testno == 8 ) {		// 1-8
			Ddim_Print(("TMR32 1-8 S\n"));
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "set_softcounter", ch_num[num], "100", NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "get_softcounter", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			Ddim_Print(("TMR32 1-8 E\n"));

		////////////////////////////////////////////////////////////////////
		} else if ( testno == 9 ) {		// 1-9
			Ddim_Print(("TMR32 1-9 S\n"));
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "set_reload", ch_num[num], "255", NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "set_reload", ch_num[num], "1", NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "get_reload", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			Ddim_Print(("TMR32 1-9 E\n"));

		////////////////////////////////////////////////////////////////////
		} else if ( testno == 10 ) {		// 1-10
			Ddim_Print(("TMR32 1-10 S\n"));
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "open", ch_num[num], "0", NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "u_set", ch_num[num], "10000", NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "get_table", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "u_start_reload", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			DDIM_User_Dly_Tsk(time);
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "stop", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "close", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			Ddim_Print(("TMR32 1-10 E\n"));

		////////////////////////////////////////////////////////////////////
		} else if ( testno == 11 ) {		// 1-11
			Ddim_Print(("TMR32 1-11 S\n"));
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "open", ch_num[num], "0", NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "u_set", ch_num[num], "10000", NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "get_table", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "u_start_one", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			DDIM_User_Dly_Tsk(time);
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "stop", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "close", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			Ddim_Print(("TMR32 1-11 E\n"));

		////////////////////////////////////////////////////////////////////
		} else if ( testno == 21 ) {		// 2-1
			Ddim_Print(("TMR32 2-1 S\n"));
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "open", ch_num[num], "0", NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "open", ch_num[num], "0", NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "close", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			Ddim_Print(("TMR32 2-1 E\n"));

		////////////////////////////////////////////////////////////////////
#if 0
		} else if ( testno == 22 ) {		// 2-2	(PT対象外)
			Ddim_Print(("TMR32 2-2 S\n"));
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "open", ch_num[num], "0", NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "close", ch_num[num], "0", NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "ctrl", ch_num[num], "32", "one", "16875", "16875", "1", "d", NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "start", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "stop", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "get_counter", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "get_table", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "set_softcounter", ch_num[num], "1", NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "get_softcounter", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "set_reload", ch_num[num], "1", NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "get_reload", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "u_set", ch_num[num], "1000", NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "u_start_reload", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "u_start_one", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			Ddim_Print(("TMR32 2-2 E\n"));
#endif

		////////////////////////////////////////////////////////////////////
#if 0
		} else if ( testno == 23 ) {		// 2-3	(PT対象外)
			Ddim_Print(("TMR32 2-3 S\n"));
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "open", ch_num[num], "-2", NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			{
				char *tmr_argv[PalladiumTestTmr32_CMD_PRM_LEN] = { "tmr32", "close", ch_num[num], NULL };
				ptDdTmr32ExecuteCmd(tmr_argv);
			}
			Ddim_Print(("TMR32 2-3 E\n"));
#endif

#if 0
			// 3-1	(PT対象外)
			Ddim_Print(("TMR32 3-1 E\n"));	// There is no code for Test 3-3. ????????
#endif
		}
	}


	Ddim_Print( ("dd_tmr32 Test End \n") );

    // タイマー停止
    Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_END);

    // タイマーログ出力
    Palladium_Timer( P_TIMER_ID_COMMON0 , P_TIMER_PRINT );



	// meaning???
	Palladium_Force_Stop();






}

PalladiumTestTmr32* palladium_test_tmr32_new(void)
{
	PalladiumTestTmr32 *self = k_object_new_with_private(PALLADIUM_TYPE_TEST_TMR32, sizeof(PalladiumTestTmr32Private));
	return self;
}
