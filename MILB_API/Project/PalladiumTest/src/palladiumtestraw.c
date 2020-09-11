/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-10
*@author : 周云飞
*@brief : PalladiumTestRaw
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/

#include "ct_im_raw.h"
#include "im_raw.h"
#include "dd_gic.h"
#include "dd_top.h"
//#include "dd_mmu.h"
#include "driver_common.h"
#include "palladium_test.h"
#include <string.h>

#include "palladiumtestraw.h"


K_TYPE_DEFINE_WITH_PRIVATE(PalladiumTestRaw, palladium_test_raw)
#define PALLADIUM_TEST_RAW_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), PalladiumTestRawPrivate, PALLADIUM_TYPE_TEST_RAW))

#define PalladiumTestRaw_D_PT_RAW_CMD_LEN		(11)
// Input: 12bit packed raw ch0
#undef PalladiumTestRaw_D_IM_RAW_TEST_NO
#define PalladiumTestRaw_D_IM_RAW_TEST_NO "2_0"
// Input: 12bit packed raw ch1
#undef PalladiumTestRaw_D_IM_RAW_TEST_NO
#define PalladiumTestRaw_D_IM_RAW_TEST_NO "2_1"
#undef PalladiumTestRaw_D_IM_RAW_TEST_NO
#define PalladiumTestRaw_D_IM_RAW_TEST_NO "2_2"
#undef PalladiumTestRaw_D_IM_RAW_TEST_NO
#define PalladiumTestRaw_D_IM_RAW_TEST_NO "2_3"
#undef PalladiumTestRaw_D_IM_RAW_TEST_NO
#define PalladiumTestRaw_D_IM_RAW_TEST_NO "2_4"
#undef PalladiumTestRaw_D_IM_RAW_TEST_NO
#define PalladiumTestRaw_D_IM_RAW_TEST_NO "2_5"
#undef PalladiumTestRaw_D_IM_RAW_TEST_NO
#define PalladiumTestRaw_D_IM_RAW_TEST_NO "2_6"
#undef PalladiumTestRaw_D_IM_RAW_TEST_NO
#define PalladiumTestRaw_D_IM_RAW_TEST_NO "2_7"
#undef PalladiumTestRaw_D_IM_RAW_TEST_NO
#define PalladiumTestRaw_D_IM_RAW_TEST_NO "2_8"
#undef PalladiumTestRaw_D_IM_RAW_TEST_NO
#define PalladiumTestRaw_D_IM_RAW_TEST_NO "2_9"
#undef PalladiumTestRaw_D_IM_RAW_TEST_NO
#define PalladiumTestRaw_D_IM_RAW_TEST_NO "2_10"
#undef PalladiumTestRaw_D_IM_RAW_TEST_NO
#define PalladiumTestRaw_D_IM_RAW_TEST_NO "2_11"
#undef PalladiumTestRaw_D_IM_RAW_TEST_NO
#define PalladiumTestRaw_D_IM_RAW_TEST_NO "2_13"
#undef PalladiumTestRaw_D_IM_RAW_TEST_NO
#define PalladiumTestRaw_D_IM_RAW_TEST_NO "2_14"

struct _PalladiumTestRawPrivate
{

};

static char* S_GCMD_ARGV[PalladiumTestRaw_D_PT_RAW_CMD_LEN];

/*
 * DECLS
 */

static VOID 			ptImRawEnableGic( VOID );
static VOID 			ptImRawStartClock( VOID );
static void 			ptImRawExecuteCmd(int cmd_argc, char* cmd_argv);
static VOID	 		ptImRawDoTest20( VOID );
static VOID 			ptImRawDoTest21( VOID );
static VOID 			ptImRawDoTest22( VOID );
static VOID 			ptImRawDoTest23( VOID );
static VOID 			ptImRawDoTest24( VOID );
static VOID 			ptImRawDoTest25( VOID );
static VOID 			ptImRawDoTest26( VOID );
static VOID 			ptImRawDoTest27( VOID );
static VOID 			ptImRawDoTest28( VOID );
static VOID 			ptImRawDoTest29( VOID );
static VOID 			ptImRawDoTest210( VOID );
static VOID 			ptImRawDoTest211( VOID );
static VOID 			ptImRawDoTest213( VOID );
static VOID 			ptImRawDoTest214( VOID );

static void palladium_test_raw_constructor(PalladiumTestRaw *self)
{
//	PalladiumTestRawPrivate *priv = PALLADIUM_TEST_RAW_GET_PRIVATE(self);
}

static void palladium_test_raw_destructor(PalladiumTestRaw *self)
{
//	PalladiumTestRawPrivate *priv = PALLADIUM_TEST_RAW_GET_PRIVATE(self);
}

/*
 * IMPL
 */

static VOID ptImRawEnableGic( VOID )
{
//	Dd_GIC_Init();
	Dd_GIC_Ctrl( E_DD_GIC_INTID_TIMER_CH0_INT, 1, D_DD_GIC_PRI30, 1 );		// cpu=0, intid=118, enable, pri=30
	Dd_GIC_Ctrl( E_DD_GIC_INTID_RAW_INT,       1, D_DD_GIC_PRI30, 1 );		// int enable
}

static VOID ptImRawStartClock( VOID )
{
	kuchar im_raw_pclk_ctrl_cnt = 0;
	kuchar im_raw_clk_ctrl_cnt = 0;
	kuchar im_raw_iclk_ctrl_cnt = 0;

	Dd_Top_Start_Clock( (kuchar*)&im_raw_pclk_ctrl_cnt, &Dd_Top_Get_CLKSTOP7(), ~D_DD_TOP_RAWAP_BIT );

	Dd_Top_Start_Clock( (kuchar*)&im_raw_iclk_ctrl_cnt, &Dd_Top_Get_CLKSTOP7(), ~D_DD_TOP_RAWAX_BIT );

	Dd_Top_Start_Clock( (kuchar*)&im_raw_clk_ctrl_cnt, &Dd_Top_Get_CLKSTOP7(), ~D_DD_TOP_RAWCK_BIT );
}

static void ptImRawExecuteCmd(int cmd_argc, char* cmd_argv)
{
	kint32 j;
	kint32 cmd_pos = 0;

	for (j = 0; j < cmd_argc; j++) {
		S_GCMD_ARGV[j] = (cmd_argv + (cmd_pos * PalladiumTestRaw_D_PT_RAW_CMD_LEN));
		cmd_pos++;
	}

	Ct_Im_RAW_Main(cmd_argc, S_GCMD_ARGV);
}

static VOID ptImRawDoTest20( VOID )
{
	char test_argv[][PalladiumTestRaw_D_PT_RAW_CMD_LEN] = {"imraw", "2", "0"};

	Ddim_Print(( "*** RAW test " PalladiumTestRaw_D_IM_RAW_TEST_NO " begin\n" ));

	// 入力データ(不要：エラールートチェックの為)
//	Palladium_Set_In_Localstack( D_CT_IM_RAW_ORG_ADDR, D_CT_IM_RAW_INPUT_BAYER_0_SIZ );

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* RAW begin CT_Im_Raw_" PalladiumTestRaw_D_IM_RAW_TEST_NO "\n" ));
	ptImRawExecuteCmd( (sizeof(test_argv) / PalladiumTestRaw_D_PT_RAW_CMD_LEN), (char*)test_argv );
	Ddim_Print(( "* RAW end CT_Im_Raw_" PalladiumTestRaw_D_IM_RAW_TEST_NO "\n" ));

	// タイマー停止
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ(不要：エラールートチェックの為)
//	palladium_test_set_out_localstack( D_CT_IM_RAW_ENC_ADDR, D_CT_IM_RAW_INPUT_BAYER_0_SIZ );

	Ddim_Print(( "*** RAW test " PalladiumTestRaw_D_IM_RAW_TEST_NO " end\n" ));
}

static VOID ptImRawDoTest21( VOID )
{
	char test_argv[][PalladiumTestRaw_D_PT_RAW_CMD_LEN] = {"imraw", "2", "1"};

	Ddim_Print(( "*** RAW test " PalladiumTestRaw_D_IM_RAW_TEST_NO " begin\n" ));

	// 入力データ(不要：初期化処理チェックの為)
//	Palladium_Set_In_Localstack( D_CT_IM_RAW_ORG_ADDR, D_CT_IM_RAW_INPUT_BAYER_0_SIZ );

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* RAW begin CT_Im_Raw_" PalladiumTestRaw_D_IM_RAW_TEST_NO "\n" ));
	ptImRawExecuteCmd( (sizeof(test_argv) / PalladiumTestRaw_D_PT_RAW_CMD_LEN), (char*)test_argv );
	Ddim_Print(( "* RAW end CT_Im_Raw_" PalladiumTestRaw_D_IM_RAW_TEST_NO "\n" ));

	// タイマー停止
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ(不要：初期化処理チェックの為)
//	palladium_test_set_out_localstack( D_CT_IM_RAW_ENC_ADDR, D_CT_IM_RAW_INPUT_BAYER_0_SIZ );
	Ddim_Print(( "*** RAW test " PalladiumTestRaw_D_IM_RAW_TEST_NO " end\n" ));
}

static VOID ptImRawDoTest22( VOID )
{
	char test_argv[][PalladiumTestRaw_D_PT_RAW_CMD_LEN] = {"imraw", "2", "2"};

	Ddim_Print(( "*** RAW test " PalladiumTestRaw_D_IM_RAW_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_IM_RAW_ORG_ADDR, D_CT_IM_RAW_INPUT_BAYER_1_SIZ );
	// 入力データダンプ
//	palladium_test_set_out_localstack( D_CT_IM_RAW_ORG_ADDR, D_CT_IM_RAW_INPUT_BAYER_1_SIZ );

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* RAW begin CT_Im_Raw_" PalladiumTestRaw_D_IM_RAW_TEST_NO "\n" ));
	ptImRawExecuteCmd( (sizeof(test_argv) / PalladiumTestRaw_D_PT_RAW_CMD_LEN), (char*)test_argv );
	Ddim_Print(( "* RAW end CT_Im_Raw_" PalladiumTestRaw_D_IM_RAW_TEST_NO "\n" ));

	// タイマー停止
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_test_set_out_localstack( D_CT_IM_RAW_ENC_ADDR, D_CT_IM_RAW_INPUT_BAYER_1_SIZ );
	palladium_test_set_out_localstack( D_CT_IM_RAW_DEC_ADDR, D_CT_IM_RAW_INPUT_BAYER_1_SIZ );

	Ddim_Print(( "*** RAW test " PalladiumTestRaw_D_IM_RAW_TEST_NO " end\n" ));
}

static VOID ptImRawDoTest23( VOID )
{
	char test_argv[][PalladiumTestRaw_D_PT_RAW_CMD_LEN] = {"imraw", "2", "3"};

	Ddim_Print(( "*** RAW test " PalladiumTestRaw_D_IM_RAW_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_IM_RAW_ORG_ADDR, D_CT_IM_RAW_INPUT_BAYER_1_SIZ );
	// 入力データダンプ
//	palladium_test_set_out_localstack( D_CT_IM_RAW_ORG_ADDR, D_CT_IM_RAW_INPUT_BAYER_1_SIZ );

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* RAW begin CT_Im_Raw_" PalladiumTestRaw_D_IM_RAW_TEST_NO "\n" ));
	ptImRawExecuteCmd( (sizeof(test_argv) / PalladiumTestRaw_D_PT_RAW_CMD_LEN), (char*)test_argv );
	Ddim_Print(( "* RAW end CT_Im_Raw_" PalladiumTestRaw_D_IM_RAW_TEST_NO "\n" ));

	// タイマー停止
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_test_set_out_localstack( D_CT_IM_RAW_ENC_ADDR, D_CT_IM_RAW_INPUT_BAYER_1_SIZ );
	palladium_test_set_out_localstack( D_CT_IM_RAW_DEC_ADDR, D_CT_IM_RAW_INPUT_BAYER_1_SIZ );

	Ddim_Print(( "*** RAW test " PalladiumTestRaw_D_IM_RAW_TEST_NO " end\n" ));
}

static VOID ptImRawDoTest24( VOID )
{
	char test_argv[][PalladiumTestRaw_D_PT_RAW_CMD_LEN] = {"imraw", "2", "4"};

	Ddim_Print(( "*** RAW test " PalladiumTestRaw_D_IM_RAW_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_IM_RAW_ORG_ADDR, D_CT_IM_RAW_INPUT_Y_0_SIZ );
	// 入力データダンプ
//	palladium_test_set_out_localstack( D_CT_IM_RAW_ORG_ADDR, D_CT_IM_RAW_INPUT_Y_0_SIZ );

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* RAW begin CT_Im_Raw_" PalladiumTestRaw_D_IM_RAW_TEST_NO "\n" ));
	ptImRawExecuteCmd( (sizeof(test_argv) / PalladiumTestRaw_D_PT_RAW_CMD_LEN), (char*)test_argv );
	Ddim_Print(( "* RAW end CT_Im_Raw_" PalladiumTestRaw_D_IM_RAW_TEST_NO "\n" ));

	// タイマー停止
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_test_set_out_localstack( D_CT_IM_RAW_ENC_ADDR, D_CT_IM_RAW_INPUT_Y_0_SIZ );
	palladium_test_set_out_localstack( D_CT_IM_RAW_DEC_ADDR, D_CT_IM_RAW_INPUT_Y_0_SIZ );

	Ddim_Print(( "*** RAW test " PalladiumTestRaw_D_IM_RAW_TEST_NO " end\n" ));
}

static VOID ptImRawDoTest25( VOID )
{
	char test_argv[][PalladiumTestRaw_D_PT_RAW_CMD_LEN] = {"imraw", "2", "5"};

	Ddim_Print(( "*** RAW test " PalladiumTestRaw_D_IM_RAW_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_IM_RAW_ORG_ADDR, D_CT_IM_RAW_INPUT_Y_0_SIZ );
	// 入力データダンプ
//	palladium_test_set_out_localstack( D_CT_IM_RAW_ORG_ADDR, D_CT_IM_RAW_INPUT_Y_0_SIZ );

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* RAW begin CT_Im_Raw_" PalladiumTestRaw_D_IM_RAW_TEST_NO "\n" ));
	ptImRawExecuteCmd( (sizeof(test_argv) / PalladiumTestRaw_D_PT_RAW_CMD_LEN), (char*)test_argv );
	Ddim_Print(( "* RAW end CT_Im_Raw_" PalladiumTestRaw_D_IM_RAW_TEST_NO "\n" ));

	// タイマー停止
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_test_set_out_localstack( D_CT_IM_RAW_ENC_ADDR, D_CT_IM_RAW_INPUT_Y_0_SIZ );
	palladium_test_set_out_localstack( D_CT_IM_RAW_DEC_ADDR, D_CT_IM_RAW_INPUT_Y_0_SIZ );

	Ddim_Print(( "*** RAW test " PalladiumTestRaw_D_IM_RAW_TEST_NO " end\n" ));
}

static VOID ptImRawDoTest26( VOID )
{
	char test_argv[][PalladiumTestRaw_D_PT_RAW_CMD_LEN] = {"imraw", "2", "6"};

	Ddim_Print(( "*** RAW test " PalladiumTestRaw_D_IM_RAW_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_IM_RAW_ORG_ADDR, D_CT_IM_RAW_INPUT_BAYER_1_SIZ );
	// 入力データダンプ
//	palladium_test_set_out_localstack( D_CT_IM_RAW_ORG_ADDR, D_CT_IM_RAW_INPUT_BAYER_1_SIZ );

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* RAW begin CT_Im_Raw_" PalladiumTestRaw_D_IM_RAW_TEST_NO "\n" ));
	ptImRawExecuteCmd( (sizeof(test_argv) / PalladiumTestRaw_D_PT_RAW_CMD_LEN), (char*)test_argv );
	Ddim_Print(( "* RAW end CT_Im_Raw_" PalladiumTestRaw_D_IM_RAW_TEST_NO "\n" ));

	// タイマー停止
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_test_set_out_localstack( D_CT_IM_RAW_ENC_ADDR, D_CT_IM_RAW_INPUT_BAYER_1_SIZ );
	palladium_test_set_out_localstack( D_CT_IM_RAW_DEC_ADDR, D_CT_IM_RAW_INPUT_BAYER_1_SIZ );

	Ddim_Print(( "*** RAW test " PalladiumTestRaw_D_IM_RAW_TEST_NO " end\n" ));
}

static VOID ptImRawDoTest27( VOID )
{
	char test_argv[][PalladiumTestRaw_D_PT_RAW_CMD_LEN] = {"imraw", "2", "7"};

	Ddim_Print(( "*** RAW test " PalladiumTestRaw_D_IM_RAW_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_IM_RAW_ORG_ADDR, D_CT_IM_RAW_INPUT_BAYER_1_SIZ );
	// 入力データダンプ
//	palladium_test_set_out_localstack( D_CT_IM_RAW_ORG_ADDR, D_CT_IM_RAW_INPUT_BAYER_1_SIZ );

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* RAW begin CT_Im_Raw_" PalladiumTestRaw_D_IM_RAW_TEST_NO "\n" ));
	ptImRawExecuteCmd( (sizeof(test_argv) / PalladiumTestRaw_D_PT_RAW_CMD_LEN), (char*)test_argv );
	Ddim_Print(( "* RAW end CT_Im_Raw_" PalladiumTestRaw_D_IM_RAW_TEST_NO "\n" ));

	// タイマー停止
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_test_set_out_localstack( D_CT_IM_RAW_ENC_ADDR, D_CT_IM_RAW_INPUT_BAYER_1_SIZ );

	Ddim_Print(( "*** RAW test " PalladiumTestRaw_D_IM_RAW_TEST_NO " end\n" ));
}

static VOID ptImRawDoTest28( VOID )
{
	char test_argv[][PalladiumTestRaw_D_PT_RAW_CMD_LEN] = {"imraw", "2", "8"};

	Ddim_Print(( "*** RAW test " PalladiumTestRaw_D_IM_RAW_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_IM_RAW_ORG_ADDR, D_CT_IM_RAW_INPUT_BAYER_1_SIZ );
	// 入力データダンプ
//	palladium_test_set_out_localstack( D_CT_IM_RAW_ORG_ADDR, D_CT_IM_RAW_INPUT_BAYER_1_SIZ );

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* RAW begin CT_Im_Raw_" PalladiumTestRaw_D_IM_RAW_TEST_NO "\n" ));
	ptImRawExecuteCmd( (sizeof(test_argv) / PalladiumTestRaw_D_PT_RAW_CMD_LEN), (char*)test_argv );
	Ddim_Print(( "* RAW end CT_Im_Raw_" PalladiumTestRaw_D_IM_RAW_TEST_NO "\n" ));

	// タイマー停止
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_test_set_out_localstack( D_CT_IM_RAW_ENC_ADDR, D_CT_IM_RAW_INPUT_BAYER_1_SIZ );
	palladium_test_set_out_localstack( D_CT_IM_RAW_DEC_ADDR, D_CT_IM_RAW_INPUT_BAYER_1_SIZ );

	Ddim_Print(( "*** RAW test " PalladiumTestRaw_D_IM_RAW_TEST_NO " end\n" ));
}

static VOID ptImRawDoTest29( VOID )
{
	char test_argv[][PalladiumTestRaw_D_PT_RAW_CMD_LEN] = {"imraw", "2", "9"};

	Ddim_Print(( "*** RAW test " PalladiumTestRaw_D_IM_RAW_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_IM_RAW_ORG_ADDR, D_CT_IM_RAW_INPUT_BAYER_1_SIZ );
	// 入力データダンプ
//	palladium_test_set_out_localstack( D_CT_IM_RAW_ORG_ADDR, D_CT_IM_RAW_INPUT_BAYER_1_SIZ );

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* RAW begin CT_Im_Raw_" PalladiumTestRaw_D_IM_RAW_TEST_NO "\n" ));
	ptImRawExecuteCmd( (sizeof(test_argv) / PalladiumTestRaw_D_PT_RAW_CMD_LEN), (char*)test_argv );
	Ddim_Print(( "* RAW end CT_Im_Raw_" PalladiumTestRaw_D_IM_RAW_TEST_NO "\n" ));

	// タイマー停止
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_test_set_out_localstack( D_CT_IM_RAW_ENC_ADDR, D_CT_IM_RAW_INPUT_BAYER_1_SIZ );
	palladium_test_set_out_localstack( D_CT_IM_RAW_DEC_ADDR, D_CT_IM_RAW_INPUT_BAYER_1_SIZ );

	Ddim_Print(( "*** RAW test " PalladiumTestRaw_D_IM_RAW_TEST_NO " end\n" ));
}

static VOID ptImRawDoTest210( VOID )
{
	char test_argv[][PalladiumTestRaw_D_PT_RAW_CMD_LEN] = {"imraw", "2", "10"};

	Ddim_Print(( "*** RAW test " PalladiumTestRaw_D_IM_RAW_TEST_NO " begin\n" ));

	// 入力データ(不要：セマフォ動作確認処理の為)
//	Palladium_Set_In_Localstack( D_CT_IM_RAW_ORG_ADDR, D_CT_IM_RAW_SIZ_4K2K );
	// 入力データダンプ
//	palladium_test_set_out_localstack( D_CT_IM_RAW_ORG_ADDR, D_CT_IM_RAW_SIZ_4K2K );

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* RAW begin CT_Im_Raw_" PalladiumTestRaw_D_IM_RAW_TEST_NO "\n" ));
	ptImRawExecuteCmd( (sizeof(test_argv) / PalladiumTestRaw_D_PT_RAW_CMD_LEN), (char*)test_argv );
	Ddim_Print(( "* RAW end CT_Im_Raw_" PalladiumTestRaw_D_IM_RAW_TEST_NO "\n" ));

	// タイマー停止
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ(不要：セマフォ動作確認処理の為)
//	palladium_test_set_out_localstack( D_CT_IM_RAW_ENC_ADDR, D_CT_IM_RAW_SIZ_4K2K );

	Ddim_Print(( "*** RAW test " PalladiumTestRaw_D_IM_RAW_TEST_NO " end\n" ));
}

static VOID ptImRawDoTest211( VOID )
{
	char test_argv[][PalladiumTestRaw_D_PT_RAW_CMD_LEN] = {"imraw", "2", "11"};

	Ddim_Print(( "*** RAW test " PalladiumTestRaw_D_IM_RAW_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_IM_RAW_ORG_ADDR, D_CT_IM_RAW_INPUT_BAYER_0_SIZ );
	// 入力データダンプ
//	palladium_test_set_out_localstack( D_CT_IM_RAW_ORG_ADDR, D_CT_IM_RAW_INPUT_BAYER_0_SIZ );

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* RAW begin CT_Im_Raw_" PalladiumTestRaw_D_IM_RAW_TEST_NO "\n" ));
	ptImRawExecuteCmd( (sizeof(test_argv) / PalladiumTestRaw_D_PT_RAW_CMD_LEN), (char*)test_argv );
	Ddim_Print(( "* RAW end CT_Im_Raw_" PalladiumTestRaw_D_IM_RAW_TEST_NO "\n" ));

	// タイマー停止
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_test_set_out_localstack( D_CT_IM_RAW_ENC_ADDR, D_CT_IM_RAW_INPUT_BAYER_0_SIZ );
	palladium_test_set_out_localstack( D_CT_IM_RAW_DEC_ADDR, D_CT_IM_RAW_INPUT_BAYER_0_SIZ );

	Ddim_Print(( "*** RAW test " PalladiumTestRaw_D_IM_RAW_TEST_NO " end\n" ));
}

static VOID ptImRawDoTest213( VOID )
{
	char test_argv[][PalladiumTestRaw_D_PT_RAW_CMD_LEN] = {"imraw", "2", "13"};

	Ddim_Print(( "*** RAW test " PalladiumTestRaw_D_IM_RAW_TEST_NO " begin\n" ));

	// 入力データ(不要：AXI Errorチェックの為)
//	Palladium_Set_In_Localstack( D_CT_IM_RAW_ORG_ADDR, D_CT_IM_RAW_INPUT_BAYER_0_SIZ );
	// 入力データダンプ
//	palladium_test_set_out_localstack( D_CT_IM_RAW_ORG_ADDR, D_CT_IM_RAW_INPUT_BAYER_0_SIZ );

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* RAW begin CT_Im_Raw_" PalladiumTestRaw_D_IM_RAW_TEST_NO "\n" ));
	ptImRawExecuteCmd( (sizeof(test_argv) / PalladiumTestRaw_D_PT_RAW_CMD_LEN), (char*)test_argv );
	Ddim_Print(( "* RAW end CT_Im_Raw_" PalladiumTestRaw_D_IM_RAW_TEST_NO "\n" ));

	// タイマー停止
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ(不要：AXI Errorチェックの為)
//	palladium_test_set_out_localstack( D_CT_IM_RAW_ENC_ADDR, D_CT_IM_RAW_INPUT_BAYER_0_SIZ );

	Ddim_Print(( "*** RAW test " PalladiumTestRaw_D_IM_RAW_TEST_NO " end\n" ));
}

static VOID ptImRawDoTest214( VOID )
{
	char test_argv_1[][PalladiumTestRaw_D_PT_RAW_CMD_LEN] = {"imraw", "2", "14", "1", "1", "4704", "3500", "0", "0", "0", "0" };
	char test_argv_2[][PalladiumTestRaw_D_PT_RAW_CMD_LEN] = {"imraw", "2", "14", "1", "1", "4704", "3500", "0", "0", "0", "1" };

	Ddim_Print(( "*** RAW test " PalladiumTestRaw_D_IM_RAW_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_IM_RAW_ORG_ADDR, D_CT_IM_RAW_INPUT_BAYER_0_SIZ );
	// 入力データダンプ
//	palladium_test_set_out_localstack( D_CT_IM_RAW_ORG_ADDR, D_CT_IM_RAW_INPUT_BAYER_0_SIZ );

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* RAW begin CT_Im_Raw_" PalladiumTestRaw_D_IM_RAW_TEST_NO "\n" ));
	ptImRawExecuteCmd( (sizeof(test_argv_1) / PalladiumTestRaw_D_PT_RAW_CMD_LEN), (char*)test_argv_1 );

	ptImRawExecuteCmd( (sizeof(test_argv_2) / PalladiumTestRaw_D_PT_RAW_CMD_LEN), (char*)test_argv_2 );
	Ddim_Print(( "* RAW end CT_Im_Raw_" PalladiumTestRaw_D_IM_RAW_TEST_NO "\n" ));

	// タイマー停止
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_test_set_out_localstack( D_CT_IM_RAW_ENC_ADDR, D_CT_IM_RAW_INPUT_BAYER_0_SIZ );
	palladium_test_set_out_localstack( D_CT_IM_RAW_DEC_ADDR, D_CT_IM_RAW_INPUT_BAYER_0_SIZ );

	Ddim_Print(( "*** RAW test " PalladiumTestRaw_D_IM_RAW_TEST_NO " end\n" ));
}

VOID pt_im_raw_main( VOID )
{
	kuchar			type1;
	kint32	retval;

	// 開始...
	Ddim_Print(( "****** RAW begin Pt_Im_RAW_Main\n" ));

	// タイマー初期化
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_INIT );

	// テストパラメータ取得
	type1	= gDDIM_Info.com._6a;

	Ddim_Print(( "*** RAW begin Im_RAW_Init\n" ));

	Ddim_Print(("*** RAW RTRG 0x288A0004 = 0x%08lx\n", *(volatile ULONG*)0x288A0004));

	retval = Im_RAW_Init();
	if( retval != D_IM_RAW_RETVAL_OK ){

		Ddim_Print(("****** RAW begin Im_RAW_Init() Error !!!!!,  retval = 0x%x\n", retval));

		Ddim_Print(("*** RAW RTRG 0x288A0004 = 0x%08lx\n", *(volatile ULONG*)0x288A0004));

		// テスト強制終了処理
		Palladium_Force_Stop();
		return;
	}

	Ddim_Print(("*** RAW RTRG 0x288A0004 = 0x%08lx\n", *(volatile ULONG*)0x288A0004));

	Ddim_Print(( "*** RAW end Im_RAW_Init\n" ));

	ptImRawEnableGic();
	ptImRawStartClock();

	switch( type1 ) {
		case 0:
			ptImRawDoTest20();
			Ddim_Print(( "\n" ));
			break;
		case 1:
			ptImRawDoTest21();
			Ddim_Print(( "\n" ));
			break;
		case 2:
			ptImRawDoTest22();
			Ddim_Print(( "\n" ));
			break;
		case 3:
			ptImRawDoTest23();
			Ddim_Print(( "\n" ));
			break;
		case 4:
			ptImRawDoTest24();
			// RAWレジスタダンプ
			Ddim_Print(( "\n" ));
			break;
		case 5:
			ptImRawDoTest25();
			Ddim_Print(( "\n" ));
			break;
		case 6:
			ptImRawDoTest26();
			Ddim_Print(( "\n" ));
			break;
		case 7:
			ptImRawDoTest27();
			Ddim_Print(( "\n" ));
			break;
		case 8:
			ptImRawDoTest28();
			Ddim_Print(( "\n" ));
			break;
		case 9:
			ptImRawDoTest29();
			Ddim_Print(( "\n" ));
			break;
		case 10:
			ptImRawDoTest210();
			Ddim_Print(( "\n" ));
			break;
		case 11:
			ptImRawDoTest211();
			Ddim_Print(( "\n" ));
			break;
		case 13:
			ptImRawDoTest213();
			Ddim_Print(( "\n" ));
			break;
		case 14:
			ptImRawDoTest214();
			Ddim_Print(( "\n" ));
			break;
		default:
			Ddim_Print(("*** RAW test skip\n" ));
			break;
	}

	// タイマーログ出力
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_PRINT );

#if 0
	Ddim_Print(( "\n" ));
	Ddim_Print(( "(CLKSEL-B)\n" ));
	Ddim_Print(( "RAWCLK[0] = %d\n", Dd_Top_Get_CLKSEL_RAW0CLK() ));
	Ddim_Print(( "RAWCLK[1] = %d\n", Dd_Top_Get_CLKSEL_RAW1CLK() ));
	Ddim_Print(( "(CLKSTOP-F)\n" ));
	Ddim_Print(( "RAWCK[0] = %d\n", Dd_Top_Get_CLKSTOP_RAW0CK() ));
	Ddim_Print(( "RAWCK[1] = %d\n", Dd_Top_Get_CLKSTOP_RAW1CK() ));
	Ddim_Print(( "RAWAP[0] = %d\n", Dd_Top_Get_CLKSTOP_RAW0AP() ));
	Ddim_Print(( "RAWAP[1] = %d\n", Dd_Top_Get_CLKSTOP_RAW1AP() ));
	Ddim_Print(( "RAWAX[0] = %d\n", Dd_Top_Get_CLKSTOP_RAW0AX() ));
	Ddim_Print(( "RAWAX[1] = %d\n", Dd_Top_Get_CLKSTOP_RAW1AX() ));
	Ddim_Print(( "****** RAW end Pt_Im_RAW_Main\n" ));
#endif
	// テスト強制終了処理
	Palladium_Force_Stop();
}

PalladiumTestRaw* palladium_test_raw_new(void)
{
	PalladiumTestRaw* self = k_object_new_with_private(PALLADIUM_TYPE_TEST_RAW, sizeof(PalladiumTestRawPrivate));

	return self;
}
