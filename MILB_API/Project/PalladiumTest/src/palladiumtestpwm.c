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
 * @file		palladium_test_pwm.c
 * @brief		palladium test code for pwm.
 * @note		None
 * @attention	None
 *
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */

#include "ddim_user_custom.h"
#include "palladium_test_common.h"
#include "palladium_test.h"
#include "dd_gic.h"
#include "dd_top.h"
#include "ct_dd_pwm.h"
#include "palladiumtestpwm.h"


K_TYPE_DEFINE_WITH_PRIVATE(PalladiumTestPwm, palladium_test_pwm);
#define PALLADIUM_TEST_PWM_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), PalladiumTestPwmPrivate,PALLADIUM_TYPE_TEST_PWM))

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
#define PalladiumTestPwm_PT_DD_PWM_CMD_LEN			(20)


struct _PalladiumTestPwmPrivate
{
	int a;
};


//静态变量
static char* 	 		gDdPwmCmdArgv[20];

//私有函数声明
static void 			ptDdPwmExecuteCmd(int cmdArgc, char* cmdArgv);

//构造函数
static void palladium_test_pwm_constructor(PalladiumTestPwm *self)
{
	PalladiumTestPwmPrivate *priv = PALLADIUM_TEST_PWM_GET_PRIVATE(self);
	priv->a = 0;
}

//析构函数
static void palladium_test_pwm_destructor(PalladiumTestPwm *self)
{
}

/*
 * DECLS
 */

static void ptDdPwmExecuteCmd(int cmdArgc, char* cmdArgv)
{
	INT32 j;
	INT32 cmdPos = 0;

	for (j = 0; j < cmdArgc; j++) {
		gDdPwmCmdArgv[j] = (cmdArgv + (cmdPos * PalladiumTestPwm_PT_DD_PWM_CMD_LEN));
		cmdPos++;
	}

	Ct_Dd_PWM_Main(cmdArgc, gDdPwmCmdArgv);
}

/*
 * PUBLIC
 */

/*----------------------------------------------------------------------*/
/* Global Function														*/
/*----------------------------------------------------------------------*/
/**
 * @brief		sample code
 * @param		void
 * @return		void
 * @note		None
 * @attention	None
 */
VOID palladium_test_pwm_dd_pwm_main( VOID )
{
	UCHAR	testno;

	// 開始ログ
	Ddim_Print(( "PWM Palladium test Start\n" ));

	// タイマー初期化(処理時間計測用)
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_INIT );

	// テストパラメータ取得(RSファイルに紐付く)
	testno	= gDDIM_Info.com._6a;

	Ddim_Print(( "PWM Palladium test No %d Start\n", testno ));

	// レジスタ取得＆設定(#define PC_DEBUG を定義すること)
	/******************************************************************/
	if ( testno == 1 ) {	// 1-1-1

		char testArgv01[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "init"};
		char testArgv02[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "open", "0"};
		char testArgv03[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "set_test", "0", "0"};
		char testArgv04[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "start", "0"};
		char testArgv05[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "stop", "0"};
		char testArgv06[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "close", "0"};

		ptDdPwmExecuteCmd((sizeof(testArgv01) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv01);
		ptDdPwmExecuteCmd((sizeof(testArgv02) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv02);
		ptDdPwmExecuteCmd((sizeof(testArgv03) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv03);
		ptDdPwmExecuteCmd((sizeof(testArgv04) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv04);
		ptDdPwmExecuteCmd((sizeof(testArgv05) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv05);
		ptDdPwmExecuteCmd((sizeof(testArgv06) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv06);

	/******************************************************************/
	} else if ( testno == 2 ) {		// 1-1-2

		char testArgv01[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "init"};
		char testArgv02[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "open", "0"};
		char testArgv03[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "set_test", "0", "1"};
		char testArgv04[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "start", "0"};
		char testArgv05[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "stop", "0"};
		char testArgv06[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "close", "0"};

		ptDdPwmExecuteCmd((sizeof(testArgv01) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv01);
		ptDdPwmExecuteCmd((sizeof(testArgv02) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv02);
		ptDdPwmExecuteCmd((sizeof(testArgv03) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv03);
		ptDdPwmExecuteCmd((sizeof(testArgv04) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv04);
		ptDdPwmExecuteCmd((sizeof(testArgv05) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv05);
		ptDdPwmExecuteCmd((sizeof(testArgv06) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv06);

	/******************************************************************/
	} else if ( testno == 3 ) {		// 1-1-3

		char testArgv01[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddtmr32", "stop", "1"};
		char testArgv02[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddtmr32", "close", "1"};
		char testArgv03[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "init"};
		char testArgv04[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "open", "0"};
		char testArgv05[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "set_test", "0", "2"};
		char testArgv06[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "start", "0"};
		char testArgv07[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddtmr32", "open", "1"};
		char testArgv08[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddtmr32", "ctrl", "1", "2", "reload", "2700000", "2700000", "1"};
		char testArgv09[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddtmr32", "start", "1"};

		ptDdPwmExecuteCmd((sizeof(testArgv01) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv01);
		ptDdPwmExecuteCmd((sizeof(testArgv02) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv02);
		ptDdPwmExecuteCmd((sizeof(testArgv03) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv03);
		ptDdPwmExecuteCmd((sizeof(testArgv04) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv04);
		ptDdPwmExecuteCmd((sizeof(testArgv05) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv05);
		ptDdPwmExecuteCmd((sizeof(testArgv06) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv06);
		ptDdPwmExecuteCmd((sizeof(testArgv07) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv07);
		ptDdPwmExecuteCmd((sizeof(testArgv08) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv08);
		ptDdPwmExecuteCmd((sizeof(testArgv09) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv09);

	/******************************************************************/
	} else if ( testno == 4 ) {		// 1-1-4

		char testArgv01[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "stop", "0"};
		char testArgv02[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "close", "0"};

		ptDdPwmExecuteCmd((sizeof(testArgv01) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv01);
		ptDdPwmExecuteCmd((sizeof(testArgv02) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv02);

	/******************************************************************/
	} else if ( testno == 5 ) {		// 1-1-5

		char testArgv01[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "init"};
		char testArgv02[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "open", "0"};
		char testArgv03[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "set_test", "1"};
		char testArgv04[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "chg_wave", "0", "r", "60000", "40"};
		char testArgv05[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "start", "0"};
		char testArgv06[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "stop", "0"};
		char testArgv07[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "close", "0"};

		ptDdPwmExecuteCmd((sizeof(testArgv01) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv01);
		ptDdPwmExecuteCmd((sizeof(testArgv02) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv02);
		ptDdPwmExecuteCmd((sizeof(testArgv03) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv03);
		ptDdPwmExecuteCmd((sizeof(testArgv04) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv04);
		ptDdPwmExecuteCmd((sizeof(testArgv05) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv05);
		ptDdPwmExecuteCmd((sizeof(testArgv06) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv06);
		ptDdPwmExecuteCmd((sizeof(testArgv07) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv07);

	/******************************************************************/
	} else if ( testno == 6 ) {		// 1-1-6

		char testArgv01[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddtmr32", "stop", "1"};
		char testArgv02[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddtmr32", "close", "1"};
		char testArgv03[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "init"};
		char testArgv04[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "open", "0"};
		char testArgv05[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "set_test", "0", "2"};
		char testArgv06[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "chg_wave", "0", "r", "60000", "40"};
		char testArgv07[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "chg_wave", "0", "q", "60000", "25"};
		char testArgv08[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "w_fact", "0", "2"};
		char testArgv09[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "start", "0"};
		char testArgv10[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddtmr32", "open", "1", "0"};
		char testArgv11[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddtmr32", "ctrl", "1", "2", "reload", "2700000", "2700000", "1"};
		char testArgv12[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddtmr32", "start", "1"};
		char testArgv13[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "stop", "0"};
		char testArgv14[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "close", "0"};

		ptDdPwmExecuteCmd((sizeof(testArgv01) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv01);
		ptDdPwmExecuteCmd((sizeof(testArgv02) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv02);
		ptDdPwmExecuteCmd((sizeof(testArgv03) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv03);
		ptDdPwmExecuteCmd((sizeof(testArgv04) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv04);
		ptDdPwmExecuteCmd((sizeof(testArgv05) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv05);
		ptDdPwmExecuteCmd((sizeof(testArgv06) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv06);
		ptDdPwmExecuteCmd((sizeof(testArgv07) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv07);
		ptDdPwmExecuteCmd((sizeof(testArgv08) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv08);
		ptDdPwmExecuteCmd((sizeof(testArgv09) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv09);
		ptDdPwmExecuteCmd((sizeof(testArgv10) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv10);
		ptDdPwmExecuteCmd((sizeof(testArgv11) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv11);
		ptDdPwmExecuteCmd((sizeof(testArgv12) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv12);
		ptDdPwmExecuteCmd((sizeof(testArgv13) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv13);
		ptDdPwmExecuteCmd((sizeof(testArgv14) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv14);

	/******************************************************************/
	} else if ( testno == 7 ) {		// 1-1-7

		char testArgv01[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "init"};
		char testArgv02[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "open", "0"};
		char testArgv03[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "set_test", "0", "1"};
		char testArgv04[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "start", "0"};
		char testArgv05[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "chg_wave", "0", "2"};
		char testArgv06[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "chg_wave", "1", "n", "60000", "40"};
		char testArgv07[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "stop", "0"};
		char testArgv08[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "close", "0"};

		ptDdPwmExecuteCmd((sizeof(testArgv01) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv01);
		ptDdPwmExecuteCmd((sizeof(testArgv02) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv02);
		ptDdPwmExecuteCmd((sizeof(testArgv03) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv03);
		ptDdPwmExecuteCmd((sizeof(testArgv04) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv04);
		ptDdPwmExecuteCmd((sizeof(testArgv05) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv05);
		ptDdPwmExecuteCmd((sizeof(testArgv06) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv06);
		ptDdPwmExecuteCmd((sizeof(testArgv07) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv07);
		ptDdPwmExecuteCmd((sizeof(testArgv08) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv08);

	/******************************************************************/
	} else if ( testno == 8 ) {		// 1-1-8

		char testArgv01[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "init"};
		char testArgv02[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "open_e", "8"};
		char testArgv03[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "set_test_e", "8", "0", "1"};
		char testArgv04[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "start_e", "0"};

		ptDdPwmExecuteCmd((sizeof(testArgv01) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv01);
		ptDdPwmExecuteCmd((sizeof(testArgv02) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv02);
		ptDdPwmExecuteCmd((sizeof(testArgv03) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv03);
		ptDdPwmExecuteCmd((sizeof(testArgv04) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv04);

	/******************************************************************/
	} else if ( testno == 9 ) {		// 1-1-9

		char testArgv01[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "init"};
		char testArgv02[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "open_e", "8"};
		char testArgv03[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "set_test_e", "8", "0", "2"};
		char testArgv04[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "start_e", "8"};

		ptDdPwmExecuteCmd((sizeof(testArgv01) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv01);
		ptDdPwmExecuteCmd((sizeof(testArgv02) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv02);
		ptDdPwmExecuteCmd((sizeof(testArgv03) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv03);
		ptDdPwmExecuteCmd((sizeof(testArgv04) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv04);

	/******************************************************************/
	} else if ( testno == 10 ) {		// 1-1-10

		char testArgv01[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "init"};
		char testArgv02[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "open_e", "8"};
		char testArgv03[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "set_test_e", "8", "0", "3", "16"};
		char testArgv04[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "start", "8"};

		ptDdPwmExecuteCmd((sizeof(testArgv01) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv01);
		ptDdPwmExecuteCmd((sizeof(testArgv02) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv02);
		ptDdPwmExecuteCmd((sizeof(testArgv03) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv03);
		ptDdPwmExecuteCmd((sizeof(testArgv04) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv04);

	/******************************************************************/
	} else if ( testno == 11 ) {		// 1-1-11

		char testArgv01[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "init"};
		char testArgv02[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "open_e", "8"};
		char testArgv03[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "set_test_e", "8", "0", "3", "15"};
		char testArgv04[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "start_e", "8"};

		ptDdPwmExecuteCmd((sizeof(testArgv01) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv01);
		ptDdPwmExecuteCmd((sizeof(testArgv02) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv02);
		ptDdPwmExecuteCmd((sizeof(testArgv03) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv03);
		ptDdPwmExecuteCmd((sizeof(testArgv04) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv04);

	/******************************************************************/
	} else if ( testno == 12 ) {		// 1-1-12

		char testArgv01[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "init"};
		char testArgv02[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "open_e", "8"};
		char testArgv03[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "set_test_e", "8", "0", "3", "4"};
		char testArgv04[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "start_e", "8"};

		ptDdPwmExecuteCmd((sizeof(testArgv01) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv01);
		ptDdPwmExecuteCmd((sizeof(testArgv02) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv02);
		ptDdPwmExecuteCmd((sizeof(testArgv03) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv03);
		ptDdPwmExecuteCmd((sizeof(testArgv04) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv04);

	/******************************************************************/
	} else if ( testno == 13 ) {		// 1-1-13

		char testArgv01[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "init"};
		char testArgv02[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "open", "0"};
		char testArgv03[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "set_test", "0", "1"};
		char testArgv04[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "start", "0"};
		char testArgv05[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "get_pls", "0"};

		ptDdPwmExecuteCmd((sizeof(testArgv01) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv01);
		ptDdPwmExecuteCmd((sizeof(testArgv02) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv02);
		ptDdPwmExecuteCmd((sizeof(testArgv03) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv03);
		ptDdPwmExecuteCmd((sizeof(testArgv04) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv04);
		ptDdPwmExecuteCmd((sizeof(testArgv05) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv05);

	/******************************************************************/
	} else if ( testno == 14 ) {		// 1-1-14

		char testArgv01[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "init"};
		char testArgv02[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "open_e", "0", "0"};
		char testArgv03[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "set_test_e", "0", "0", "3", "16"};
		char testArgv04[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "start", "0"};
		char testArgv05[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "get_pls", "0"};

		ptDdPwmExecuteCmd((sizeof(testArgv01) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv01);
		ptDdPwmExecuteCmd((sizeof(testArgv02) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv02);
		ptDdPwmExecuteCmd((sizeof(testArgv03) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv03);
		ptDdPwmExecuteCmd((sizeof(testArgv04) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv04);
		ptDdPwmExecuteCmd((sizeof(testArgv05) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv05);

	/******************************************************************/
	} else if ( testno == 15 ) {		// 1-1-15

		char testArgv01[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "init"};
		char testArgv02[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "open_e", "0", "0"};
		char testArgv03[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "set_test_e", "0", "0", "3", "16"};
		char testArgv04[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "start", "0"};
		char testArgv05[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "get_int", "0"};
		char testArgv06[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "set_int", "0"};
		char testArgv07[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "get_int", "0"};

		ptDdPwmExecuteCmd((sizeof(testArgv01) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv01);
		ptDdPwmExecuteCmd((sizeof(testArgv02) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv02);
		ptDdPwmExecuteCmd((sizeof(testArgv03) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv03);
		ptDdPwmExecuteCmd((sizeof(testArgv04) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv04);
		ptDdPwmExecuteCmd((sizeof(testArgv05) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv05);
		ptDdPwmExecuteCmd((sizeof(testArgv06) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv06);
		ptDdPwmExecuteCmd((sizeof(testArgv07) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv07);

	/******************************************************************/
	} else if ( testno == 16 ) {		// 1-1-16

		char testArgv01[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "init"};
		char testArgv02[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "open", "0"};
		char testArgv03[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "cal_cycc", "20000", "0"};

		ptDdPwmExecuteCmd((sizeof(testArgv01) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv01);
		ptDdPwmExecuteCmd((sizeof(testArgv02) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv02);
		ptDdPwmExecuteCmd((sizeof(testArgv03) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv03);

	/******************************************************************/
	} else if ( testno == 17 ) {		// 1-1-17

		char testArgv01[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "init"};
		char testArgv02[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "open", "0"};
		char testArgv03[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "cal_cycc", "20000", "3"};

		ptDdPwmExecuteCmd((sizeof(testArgv01) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv01);
		ptDdPwmExecuteCmd((sizeof(testArgv02) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv02);
		ptDdPwmExecuteCmd((sizeof(testArgv03) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv03);

	/******************************************************************/
	} else if ( testno == 18 ) {		// 1-1-18

		char testArgv01[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "set_trg", "3", "3"};
		char testArgv02[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "set_trg", "4", "0"};
		char testArgv03[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "set_trg", "9", "4"};
		char testArgv04[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "set_trg", "10", "10"};

		ptDdPwmExecuteCmd((sizeof(testArgv01) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv01);
		ptDdPwmExecuteCmd((sizeof(testArgv02) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv02);
		ptDdPwmExecuteCmd((sizeof(testArgv03) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv03);
		ptDdPwmExecuteCmd((sizeof(testArgv04) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv04);

	/******************************************************************/
	} else if ( testno == 19 ) {		// 1-1-19

		char testArgv01[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "set_trg", "0", "12"};
		char testArgv02[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "set_trg", "5", "72"};
		char testArgv03[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "set_trg", "10", "132"};
		char testArgv04[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "set_trg", "11", "192"};

		ptDdPwmExecuteCmd((sizeof(testArgv01) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv01);
		ptDdPwmExecuteCmd((sizeof(testArgv02) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv02);
		ptDdPwmExecuteCmd((sizeof(testArgv03) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv03);
		ptDdPwmExecuteCmd((sizeof(testArgv04) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv04);

	/******************************************************************/
	} else if ( testno == 20 ) {		// 1-1-20

		char testArgv01[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "init"};
		char testArgv02[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "open", "0"};
		char testArgv03[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "set_one", "0", "60000", "30000"};
		char testArgv04[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "start", "0"};

		ptDdPwmExecuteCmd((sizeof(testArgv01) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv01);
		ptDdPwmExecuteCmd((sizeof(testArgv02) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv02);
		ptDdPwmExecuteCmd((sizeof(testArgv03) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv03);
		ptDdPwmExecuteCmd((sizeof(testArgv04) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv04);

	/******************************************************************/
	} else if ( testno == 21 ) {		// 1-1-21

		char testArgv01[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "stop_e", "0"};
		char testArgv02[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "close_e", "0"};

		ptDdPwmExecuteCmd((sizeof(testArgv01) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv01);
		ptDdPwmExecuteCmd((sizeof(testArgv02) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv02);

	/******************************************************************/
	} else if ( testno == 22 ) {		// 1-1-22

		char testArgv01[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "init"};
		char testArgv02[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "open", "0"};
		char testArgv03[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "set_test", "0", "1"};
		char testArgv04[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "start", "0"};
		char testArgv05[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "get_intstat", "0"};

		ptDdPwmExecuteCmd((sizeof(testArgv01) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv01);
		ptDdPwmExecuteCmd((sizeof(testArgv02) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv02);
		ptDdPwmExecuteCmd((sizeof(testArgv03) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv03);
		ptDdPwmExecuteCmd((sizeof(testArgv04) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv04);
		ptDdPwmExecuteCmd((sizeof(testArgv05) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv05);

	/******************************************************************/
	} else if ( testno == 23 ) {		// 1-1-23

		char testArgv01[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "init"};
		char testArgv02[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "open", "0"};
		char testArgv03[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "set_test", "0", "0"};
		char testArgv04[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "get_cmn", "0"};

		ptDdPwmExecuteCmd((sizeof(testArgv01) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv01);
		ptDdPwmExecuteCmd((sizeof(testArgv02) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv02);
		ptDdPwmExecuteCmd((sizeof(testArgv03) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv03);
		ptDdPwmExecuteCmd((sizeof(testArgv04) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv04);

	/******************************************************************/
	} else if ( testno == 24 ) {		// 1-2-1

		char testArgv01[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "0"};
		char testArgv02[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "1"};
		char testArgv03[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "2"};
		char testArgv04[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "3"};
		char testArgv05[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "4"};
		char testArgv06[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "5"};
		char testArgv07[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "6"};
		char testArgv08[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "7"};
		char testArgv09[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "8"};
		char testArgv10[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "9"};
		char testArgv11[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "10"};
		char testArgv12[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "11"};
		char testArgv13[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "12"};
		char testArgv14[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "13"};
		char testArgv15[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "14"};
		char testArgv16[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "15"};
		char testArgv17[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "16"};
		char testArgv18[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "17"};
		char testArgv19[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "18"};
		char testArgv20[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "19"};
		char testArgv21[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "20"};
		char testArgv22[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "21"};
		char testArgv23[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "22"};
		char testArgv24[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "23"};
		char testArgv25[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "24"};
		char testArgv26[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "25"};
		char testArgv27[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "26"};
		char testArgv28[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "27"};
		char testArgv29[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "28"};
		char testArgv30[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "29"};
		char testArgv31[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "30"};
		char testArgv32[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "31"};
		char testArgv33[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "32"};
		char testArgv34[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "33"};
		char testArgv35[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "34"};
		char testArgv36[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "35"};
		char testArgv37[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "36"};
		char testArgv38[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "37"};
		char testArgv39[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "38"};
		char testArgv40[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "39"};
		char testArgv41[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "40"};
		char testArgv42[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "41"};
		char testArgv43[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "42"};
		char testArgv44[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "43"};
		char testArgv45[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "44"};
		char testArgv46[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "45"};
		char testArgv47[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "46"};
		char testArgv48[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "47"};
		char testArgv49[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "48"};
		char testArgv50[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "49"};
		char testArgv51[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "50"};
		char testArgv52[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "51"};
		char testArgv53[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "52"};
		char testArgv54[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "53"};
		char testArgv55[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "54"};
		char testArgv56[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "55"};
		char testArgv57[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "err", "56"};

		ptDdPwmExecuteCmd((sizeof(testArgv01) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv01);
		ptDdPwmExecuteCmd((sizeof(testArgv02) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv02);
		ptDdPwmExecuteCmd((sizeof(testArgv03) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv03);
		ptDdPwmExecuteCmd((sizeof(testArgv04) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv04);
		ptDdPwmExecuteCmd((sizeof(testArgv05) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv05);
		ptDdPwmExecuteCmd((sizeof(testArgv06) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv06);
		ptDdPwmExecuteCmd((sizeof(testArgv07) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv07);
		ptDdPwmExecuteCmd((sizeof(testArgv08) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv08);
		ptDdPwmExecuteCmd((sizeof(testArgv09) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv09);
		ptDdPwmExecuteCmd((sizeof(testArgv10) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv10);
		ptDdPwmExecuteCmd((sizeof(testArgv11) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv11);
		ptDdPwmExecuteCmd((sizeof(testArgv12) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv12);
		ptDdPwmExecuteCmd((sizeof(testArgv13) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv13);
		ptDdPwmExecuteCmd((sizeof(testArgv14) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv14);
		ptDdPwmExecuteCmd((sizeof(testArgv15) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv15);
		ptDdPwmExecuteCmd((sizeof(testArgv16) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv16);
		ptDdPwmExecuteCmd((sizeof(testArgv17) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv17);
		ptDdPwmExecuteCmd((sizeof(testArgv18) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv18);
		ptDdPwmExecuteCmd((sizeof(testArgv19) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv19);
		ptDdPwmExecuteCmd((sizeof(testArgv20) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv20);
		ptDdPwmExecuteCmd((sizeof(testArgv21) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv21);
		ptDdPwmExecuteCmd((sizeof(testArgv22) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv22);
		ptDdPwmExecuteCmd((sizeof(testArgv23) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv23);
		ptDdPwmExecuteCmd((sizeof(testArgv24) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv24);
		ptDdPwmExecuteCmd((sizeof(testArgv25) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv25);
		ptDdPwmExecuteCmd((sizeof(testArgv26) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv26);
		ptDdPwmExecuteCmd((sizeof(testArgv27) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv27);
		ptDdPwmExecuteCmd((sizeof(testArgv28) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv28);
		ptDdPwmExecuteCmd((sizeof(testArgv29) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv29);
		ptDdPwmExecuteCmd((sizeof(testArgv30) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv30);
		ptDdPwmExecuteCmd((sizeof(testArgv31) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv31);
		ptDdPwmExecuteCmd((sizeof(testArgv32) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv32);
		ptDdPwmExecuteCmd((sizeof(testArgv33) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv33);
		ptDdPwmExecuteCmd((sizeof(testArgv34) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv34);
		ptDdPwmExecuteCmd((sizeof(testArgv35) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv35);
		ptDdPwmExecuteCmd((sizeof(testArgv36) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv36);
		ptDdPwmExecuteCmd((sizeof(testArgv37) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv37);
		ptDdPwmExecuteCmd((sizeof(testArgv38) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv38);
		ptDdPwmExecuteCmd((sizeof(testArgv39) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv39);
		ptDdPwmExecuteCmd((sizeof(testArgv40) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv40);
		ptDdPwmExecuteCmd((sizeof(testArgv41) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv41);
		ptDdPwmExecuteCmd((sizeof(testArgv42) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv42);
		ptDdPwmExecuteCmd((sizeof(testArgv43) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv43);
		ptDdPwmExecuteCmd((sizeof(testArgv44) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv44);
		ptDdPwmExecuteCmd((sizeof(testArgv45) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv45);
		ptDdPwmExecuteCmd((sizeof(testArgv46) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv46);
		ptDdPwmExecuteCmd((sizeof(testArgv47) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv47);
		ptDdPwmExecuteCmd((sizeof(testArgv48) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv48);
		ptDdPwmExecuteCmd((sizeof(testArgv49) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv49);
		ptDdPwmExecuteCmd((sizeof(testArgv50) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv50);
		ptDdPwmExecuteCmd((sizeof(testArgv51) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv51);
		ptDdPwmExecuteCmd((sizeof(testArgv52) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv52);
		ptDdPwmExecuteCmd((sizeof(testArgv53) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv53);
		ptDdPwmExecuteCmd((sizeof(testArgv54) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv54);
		ptDdPwmExecuteCmd((sizeof(testArgv55) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv55);
		ptDdPwmExecuteCmd((sizeof(testArgv56) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv56);
		ptDdPwmExecuteCmd((sizeof(testArgv57) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv07);

	/******************************************************************/
	} else if ( testno == 25 ) {		// 1-2-2

		char testArgv01[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "init"};
		char testArgv02[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "open", "0"};
		char testArgv03[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "open", "0", "0"};

		ptDdPwmExecuteCmd((sizeof(testArgv01) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv01);
		ptDdPwmExecuteCmd((sizeof(testArgv02) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv02);
		ptDdPwmExecuteCmd((sizeof(testArgv03) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv03);

	/******************************************************************/
	} else if ( testno == 26 ) {		// 1-2-3

		char testArgv01[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "init"};
		char testArgv02[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "open", "0"};
		char testArgv03[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "open", "0", "-1"};

		ptDdPwmExecuteCmd((sizeof(testArgv01) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv01);
		ptDdPwmExecuteCmd((sizeof(testArgv02) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv02);
		ptDdPwmExecuteCmd((sizeof(testArgv03) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv03);

	/******************************************************************/
	} else if ( testno == 27 ) {		// 1-2-4

		char testArgv01[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "init"};
		char testArgv02[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "open", "0"};
		char testArgv03[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "open", "0", "10000"};

		ptDdPwmExecuteCmd((sizeof(testArgv01) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv01);
		ptDdPwmExecuteCmd((sizeof(testArgv02) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv02);
		ptDdPwmExecuteCmd((sizeof(testArgv03) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv03);

	/******************************************************************/
	} else if ( testno == 28 ) {		// 1-2-5

		char testArgv01[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "init"};
		char testArgv02[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "open_e", "0"};
		char testArgv03[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "open_e", "0", "0"};

		ptDdPwmExecuteCmd((sizeof(testArgv01) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv01);
		ptDdPwmExecuteCmd((sizeof(testArgv02) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv02);
		ptDdPwmExecuteCmd((sizeof(testArgv03) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv03);

	/******************************************************************/
	} else if ( testno == 29 ) {		// 1-2-6

		char testArgv01[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "init"};
		char testArgv02[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "open_e", "0"};
		char testArgv03[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "open_e", "0", "-1"};

		ptDdPwmExecuteCmd((sizeof(testArgv01) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv01);
		ptDdPwmExecuteCmd((sizeof(testArgv02) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv02);
		ptDdPwmExecuteCmd((sizeof(testArgv03) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv03);

	/******************************************************************/
	} else if ( testno == 30 ) {		// 1-2-7

		char testArgv01[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "init"};
		char testArgv02[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "open_e", "0"};
		char testArgv03[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "open_e", "0", "10000"};

		ptDdPwmExecuteCmd((sizeof(testArgv01) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv01);
		ptDdPwmExecuteCmd((sizeof(testArgv02) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv02);
		ptDdPwmExecuteCmd((sizeof(testArgv03) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv03);

	/******************************************************************/
	} else if ( testno == 31 ) {		// 1-2-8  1-2-10  1-2-12

		char testArgv01[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "init"};
		char testArgv02[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "open", "0"};
		char testArgv03[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "start", "0"};
		char testArgv04[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "stop", "0"};
		char testArgv05[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "set_stp_mask", "0", "1"};	//	1-2-8
		char testArgv06[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "stop", "0"};
		char testArgv07[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "set_stp_mask", "0", "1"};	//	1-2-10
		char testArgv08[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "stop", "0"};
		char testArgv09[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "get_stp_out", "0"};			//	1-2-12

		ptDdPwmExecuteCmd((sizeof(testArgv01) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv01);
		ptDdPwmExecuteCmd((sizeof(testArgv02) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv02);
		ptDdPwmExecuteCmd((sizeof(testArgv03) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv03);
		ptDdPwmExecuteCmd((sizeof(testArgv04) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv04);
		ptDdPwmExecuteCmd((sizeof(testArgv05) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv05);
		ptDdPwmExecuteCmd((sizeof(testArgv06) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv06);
		ptDdPwmExecuteCmd((sizeof(testArgv07) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv07);
		ptDdPwmExecuteCmd((sizeof(testArgv08) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv08);
		ptDdPwmExecuteCmd((sizeof(testArgv09) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv09);

	/******************************************************************/
	} else if ( testno == 31 ) {		// 1-2-9  1-2-11  1-2-13

		char testArgv01[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "init"};
		char testArgv02[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "open", "0"};
		char testArgv03[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "start", "0"};
		char testArgv04[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "stop", "0"};
		char testArgv05[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "set_stp_mask", "0", "0"};	//	1-2-9
		char testArgv06[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "stop", "0"};
		char testArgv07[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "set_stp_mask", "0", "0"};	//	1-2-11
		char testArgv08[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "stop", "0"};
		char testArgv09[][PalladiumTestPwm_PT_DD_PWM_CMD_LEN]  = {"ddpwm", "get_stp_out", "0"};			//	1-2-13

		ptDdPwmExecuteCmd((sizeof(testArgv01) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv01);
		ptDdPwmExecuteCmd((sizeof(testArgv02) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv02);
		ptDdPwmExecuteCmd((sizeof(testArgv03) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv03);
		ptDdPwmExecuteCmd((sizeof(testArgv04) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv04);
		ptDdPwmExecuteCmd((sizeof(testArgv05) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv05);
		ptDdPwmExecuteCmd((sizeof(testArgv06) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv06);
		ptDdPwmExecuteCmd((sizeof(testArgv07) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv07);
		ptDdPwmExecuteCmd((sizeof(testArgv08) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv08);
		ptDdPwmExecuteCmd((sizeof(testArgv09) / PalladiumTestPwm_PT_DD_PWM_CMD_LEN), (char*)testArgv09);

	/******************************************************************/
	} else {
		// 例外パラメータ指定
		Ddim_Print(( "Parameters of the excluded\n" ));
	}
	// タイマーログ出力(処理時間出力)
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_PRINT );

	Ddim_Print(( "RELC Palladium test No %d End\n", testno ));

	// Force stop
	Palladium_Force_Stop();
}


PalladiumTestPwm* palladium_test_pwm_new(void)
{
	PalladiumTestPwm *self = k_object_new_with_private(PALLADIUM_TYPE_TEST_PWM,sizeof(PalladiumTestPwmPrivate));
	return self;
}
