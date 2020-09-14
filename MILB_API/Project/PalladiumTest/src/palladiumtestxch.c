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


#include "palladiumtestxch.h"
#include "ct_im_xch.h"
#include "im_xch.h"
#include "dd_gic.h"
#include "dd_top.h"
#include "driver_common.h"
#include "palladium_test.h"
#include <string.h>

K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(PalladiumTestXch, palladium_test_xch,K_TYPE_OBJECT)
#define PALLADIUM_TEST_XCH_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), PalladiumTestXchPrivate,PALLADIUM_TYPE_TEST_XCH))

#define PalladiumTestXch_D_PT_XCH_CMD_LEN		(11)

struct _PalladiumTestXchPrivate
{
	char* gCmdArgv[PalladiumTestXch_D_PT_XCH_CMD_LEN];
	char testArgv1[2][PalladiumTestXch_D_PT_XCH_CMD_LEN];
};

/*
 * DECLS
 */

static void ptImXchEnableGic( void );
static void ptImXchStartGic( void );
static void ptImXchExecuteCmd(PalladiumTestXch *self, int cmd_argc, char* cmd_argv);
static void ptImXchDoTest21( void );
static void ptImXchDoTest22( void );
static void ptImXchDoTest23( void );
static void ptImXchDoTest24( void );
static void ptImXchDoTest25( PalladiumTestXch *self );
static void ptImXchDoTest26( PalladiumTestXch *self );
static void ptImXchDoTest27( PalladiumTestXch *self);
static void ptImXchDoTest28( PalladiumTestXch *self );
static void ptImXchDoTest29( PalladiumTestXch *self );
static void ptImXchDoTest210( PalladiumTestXch *self );
static void ptImXchDoTest211( PalladiumTestXch *self );
static void ptImXchDoTest212( PalladiumTestXch *self );
static void ptImXchDoTest213( PalladiumTestXch *self  );
static void ptImXchDoTest214( PalladiumTestXch *self );
static void ptImXchDoTest215( PalladiumTestXch *self );
static void ptImXchDoTest216( PalladiumTestXch *self  );
static void ptImXchDoTest217( PalladiumTestXch *self  );
static void ptImXchDoTest218( PalladiumTestXch *self );
static void ptImXchDoTest219( PalladiumTestXch *self  );
static void ptImXchDoTest220( PalladiumTestXch *self  );
static void ptImXchDoTest221( PalladiumTestXch *self  );
static void ptImXchDoTest222( PalladiumTestXch *self  );
static void ptImXchDoTest223( PalladiumTestXch *self );
static void ptImXchDoTest224( PalladiumTestXch *self  );
static void ptImXchDoTest225( PalladiumTestXch *self  );
static void ptImXchDoTest226( PalladiumTestXch *self  );
static void ptImXchDoTest227( PalladiumTestXch *self  );
static void ptImXchDoTest228( PalladiumTestXch *self  );
static void ptImXchDoTest229( PalladiumTestXch *self );
static void ptImXchDoTest230( PalladiumTestXch *self  );
static void ptImXchDoTest231( PalladiumTestXch *self  );
static void ptImXchDoTest232( PalladiumTestXch *self );
static void ptImXchDoTest233( PalladiumTestXch *self  );
static void ptImXchDoTest234( PalladiumTestXch *self  );
static void ptImXchDoTest235( PalladiumTestXch *self  );
static void ptImXchDoTest236( PalladiumTestXch *self  );
static void ptImXchDoTest237( PalladiumTestXch *self  );
static void ptImXchDoTest238( PalladiumTestXch *self  );

/*
 * IMPL
 */
static void palladium_test_xch_constructor(PalladiumTestXch *self)
{
	PalladiumTestXchPrivate *priv = PALLADIUM_TEST_XCH_GET_PRIVATE(self);
	memset(priv ->gCmdArgv, 0,11*(sizeof(char*)));
	memset(priv ->testArgv1,0,3*11*(sizeof(char)));
	strcpy(priv ->testArgv1[0],"imxch");
	strcpy(priv ->testArgv1[1],"1");
}

static void palladium_test_xch_destructor(PalladiumTestXch *self)
{
	PalladiumTestXchPrivate *priv = PALLADIUM_TEST_XCH_GET_PRIVATE(self);
	if(priv ->gCmdArgv != NULL){
		k_free(priv ->gCmdArgv);
		priv ->gCmdArgv = NULL;
	}

	if(priv ->testArgv1 != NULL){
		k_free(priv ->testArgv1);
		priv ->testArgv1 = NULL;
	}
}

static void ptImXchEnableGic( void )
{
	dd_gic_ctrl( EDdGicIntid_TIMER_CH0_INT, 1, D_DD_GIC_PRI30, 1 );		//cpu=0, intid=118, enable, pri=30
	dd_gic_ctrl( EDdGicIntid_XCH_INT,       1, D_DD_GIC_PRI30, 1 );		// int enable
}

static void ptImXchStartGic( void )
{
	kuchar imXchPclkCtrlCnt = 0;
	kuchar imXchIclkCtrlCnt = 0;

	dd_top_start_clock( (kuchar*)&imXchPclkCtrlCnt, &Dd_Top_Get_CLKSTOP6(), ~D_DD_TOP_XCHAP_BIT );

	dd_top_start_clock( (kuchar*)&imXchIclkCtrlCnt, &Dd_Top_Get_CLKSTOP6(), ~D_DD_TOP_XCHAX_BIT );
}

static void ptImXchExecuteCmd(PalladiumTestXch *self,int cmd_argc, char* cmd_argv)
{
	PalladiumTestXchPrivate *priv = PALLADIUM_TEST_XCH_GET_PRIVATE(self);
	kint32 j;
	kint32 cmdPos = 0;

	for (j = 0; j < cmd_argc; j++) {
		priv ->gCmdArgv[j] = (cmd_argv + (cmdPos * PalladiumTestXch_D_PT_XCH_CMD_LEN));
		cmdPos++;
	}

	ct_im_xch_main(cmd_argc, priv ->gCmdArgv);
}

// high speed subsumpling 1/4 8bit
#undef D_IM_XCH_TEST_NO
#define D_IM_XCH_TEST_NO "2_1"
static void ptImXchDoTest21( PalladiumTestXch *self )
{
	PalladiumTestXchPrivate *priv = PALLADIUM_TEST_XCH_GET_PRIVATE(self);
	//	char testArgv1[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "1", "0"};
	strcpy(priv->testArgv1[2], "0");
	char testArgv2[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "3", "0", "0", "816", "816", "612", "0"};
	char testArgv3[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "4", "0", "0", "0", "0x44444444", "3264"};
	char testArgv4[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "9", "0", "0"};
	char testArgv5[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "2", "0"};

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_XCH_SRC_TOP_ADDR, 3264*2448 );

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* XCH begin CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));
	ptImXchExecuteCmd(self, (sizeof(priv ->testArgv1) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)priv ->testArgv1 );
	ptImXchExecuteCmd(self, (sizeof(testArgv2) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv2 );
	ptImXchExecuteCmd(self, (sizeof(testArgv3) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv3 );
	ptImXchExecuteCmd(self, (sizeof(testArgv4) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv4 );
	ptImXchExecuteCmd(self, (sizeof(testArgv5) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv5 );
	Ddim_Print(( "* XCH end CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_set_out_localstack( D_CT_XCH_DST_TOP_ADDR, 816*612 );
	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " end\n" ));
}

// high speed subsumpling 1/4 16bit
#undef D_IM_XCH_TEST_NO
#define D_IM_XCH_TEST_NO "2_2"
static void ptImXchDoTest22( PalladiumTestXch *self  )
{
	PalladiumTestXchPrivate *priv = PALLADIUM_TEST_XCH_GET_PRIVATE(self);
	//	char testArgv1[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "1", "0"};
	strcpy(priv->testArgv1[2], "0");
	char testArgv2[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "3", "0", "0", "816", "816", "612", "1"};
	char testArgv3[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "4", "0", "1", "0", "0x44444444", "3264"};
	char testArgv4[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "9", "0", "2"};
	char testArgv5[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "2", "0"};

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_XCH_SRC_TOP_ADDR, 3264*2448*2 );

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* XCH begin CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));
	ptImXchExecuteCmd(self, (sizeof(priv ->testArgv1) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)priv ->testArgv1 );
	ptImXchExecuteCmd(self, (sizeof(testArgv2) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv2 );
	ptImXchExecuteCmd(self, (sizeof(testArgv3) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv3 );
	ptImXchExecuteCmd(self, (sizeof(testArgv4) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv4 );
	ptImXchExecuteCmd(self, (sizeof(testArgv5) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv5 );
	Ddim_Print(( "* XCH end CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_set_out_localstack( D_CT_XCH_DST_TOP_ADDR, 816*612*2 );

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " end\n" ));
}

// high speed subsumpling 3/4 16bit
#undef D_IM_XCH_TEST_NO
#define D_IM_XCH_TEST_NO "2_3"
static void ptImXchDoTest23( PalladiumTestXch *self  )
{
	PalladiumTestXchPrivate *priv = PALLADIUM_TEST_XCH_GET_PRIVATE(self);
	//	char testArgv1[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "1", "1"};
	strcpy(priv->testArgv1[2], "1");
	char testArgv2[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "3", "1", "0", "2448", "2448", "1836", "1"};
	char testArgv3[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "4", "1", "1", "0", "0xBBBBBBBB", "3264"};
	char testArgv4[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "9", "1", "2"};
	char testArgv5[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "2", "1"};

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_XCH_SRC_TOP_ADDR, 3264*2448*2 );

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* XCH begin CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));
	ptImXchExecuteCmd(self, (sizeof(priv ->testArgv1) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)priv ->testArgv1 );
	ptImXchExecuteCmd(self, (sizeof(testArgv2) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv2 );
	ptImXchExecuteCmd(self, (sizeof(testArgv3) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv3 );
	ptImXchExecuteCmd(self, (sizeof(testArgv4) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv4 );
	ptImXchExecuteCmd(self, (sizeof(testArgv5) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv5 );
	Ddim_Print(( "* XCH end CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_set_out_localstack( D_CT_XCH_DST_TOP_ADDR, 2448*1836*2 );

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " end\n" ));
}

// subsumpling 1/4 8bit
#undef D_IM_XCH_TEST_NO
#define D_IM_XCH_TEST_NO "2_4"
static void ptImXchDoTest24(PalladiumTestXch *self)
{
	PalladiumTestXchPrivate *priv = PALLADIUM_TEST_XCH_GET_PRIVATE(self);
	//	char testArgv1[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "1", "0"};
	strcpy(priv->testArgv1[2], "0");
	char testArgv2[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "3", "0", "1", "816", "816", "612", "0"};
	char testArgv3[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "4", "0", "0", "0", "0x44444444", "3264"};
	char testArgv4[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "9", "0", "0"};
	char testArgv5[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "2", "0"};

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_XCH_SRC_TOP_ADDR, 3264*2448 );

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* XCH begin CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));
	ptImXchExecuteCmd(self, (sizeof(priv ->testArgv1) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)priv ->testArgv1 );
	ptImXchExecuteCmd(self, (sizeof(testArgv2) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv2 );
	ptImXchExecuteCmd(self, (sizeof(testArgv3) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv3 );
	ptImXchExecuteCmd(self, (sizeof(testArgv4) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv4 );
	ptImXchExecuteCmd(self, (sizeof(testArgv5) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv5 );
	Ddim_Print(( "* XCH end CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_set_out_localstack( D_CT_XCH_DST_TOP_ADDR, 816*612 );

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " end\n" ));
}

// subsumpling 1/4 16bit
#undef D_IM_XCH_TEST_NO
#define D_IM_XCH_TEST_NO "2_5"
static void ptImXchDoTest25( PalladiumTestXch *self)
{
	PalladiumTestXchPrivate *priv = PALLADIUM_TEST_XCH_GET_PRIVATE(self);
	strcpy(priv->testArgv1[2], "0");
	char testArgv2[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "3", "0", "1", "816", "816", "612", "1"};
	char testArgv3[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "4", "0", "1", "0", "0x44444444", "3264"};
	char testArgv4[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "9", "0", "2"};
	char testArgv5[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "2", "0"};

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_XCH_SRC_TOP_ADDR, 3264*2448*2 );

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* XCH begin CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));
	ptImXchExecuteCmd(self, (sizeof(priv ->testArgv1) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)priv ->testArgv1 );
	ptImXchExecuteCmd(self,  (sizeof(testArgv2) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv2 );
	ptImXchExecuteCmd(self,  (sizeof(testArgv3) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv3 );
	ptImXchExecuteCmd(self,  (sizeof(testArgv4) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv4 );
	ptImXchExecuteCmd(self,  (sizeof(testArgv5) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv5 );
	Ddim_Print(( "* XCH end CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_set_out_localstack( D_CT_XCH_DST_TOP_ADDR, 816*612*2 );

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " end\n" ));
}

// subsumpling 3/4 16bit
#undef D_IM_XCH_TEST_NO
#define D_IM_XCH_TEST_NO "2_6"
static void ptImXchDoTest26( PalladiumTestXch *self )
{
	PalladiumTestXchPrivate *priv = PALLADIUM_TEST_XCH_GET_PRIVATE(self);
	//	char priv ->testArgv1[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "1", "1"};
	strcpy(priv->testArgv1[2], "1");
	char testArgv2[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "3", "1", "1", "2448", "2448", "1836", "1"};
	char testArgv3[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "4", "1", "1", "0", "0xBBBBBBBB", "3264"};
	char testArgv4[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "9", "1", "2"};
	char testArgv5[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "2", "1"};

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_XCH_SRC_TOP_ADDR, 3264*2448*2 );

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* XCH begin CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));
	ptImXchExecuteCmd(self,  (sizeof(priv ->testArgv1) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)priv ->testArgv1 );
	ptImXchExecuteCmd(self,  (sizeof(testArgv2) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv2 );
	ptImXchExecuteCmd(self,  (sizeof(testArgv3) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv3 );
	ptImXchExecuteCmd(self,  (sizeof(testArgv4) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv4 );
	ptImXchExecuteCmd(self,  (sizeof(testArgv5) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv5 );
	Ddim_Print(( "* XCH end CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_set_out_localstack( D_CT_XCH_DST_TOP_ADDR, 2448*1836*2 );

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " end\n" ));
}

// histogram subsumpling 1/4 8bit
#undef D_IM_XCH_TEST_NO
#define D_IM_XCH_TEST_NO "2_7"
static void ptImXchDoTest27( PalladiumTestXch *self)
{
	PalladiumTestXchPrivate *priv = PALLADIUM_TEST_XCH_GET_PRIVATE(self);
	//	char testArgv1[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "1", "0"};
	strcpy(priv->testArgv1[2], "0");
	char testArgv2[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "3", "0", "2", "816", "816", "612", "0"};
	char testArgv3[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "5", "0", "0", "0", "0x44444444", "3264", "0"};
	char testArgv4[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "9", "0", "0"};
	char testArgv5[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "10"};
	char testArgv6[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "11"};
	char testArgv7[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "2", "0"};

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_XCH_SRC_TOP_ADDR, 3264*2448 );

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* XCH begin CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));
	ptImXchExecuteCmd(self, (sizeof(priv ->testArgv1) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)priv ->testArgv1 );
	ptImXchExecuteCmd(self, (sizeof(testArgv2) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv2 );
	ptImXchExecuteCmd(self, (sizeof(testArgv3) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv3 );
	ptImXchExecuteCmd(self, (sizeof(testArgv4) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv4 );
	ptImXchExecuteCmd(self, (sizeof(testArgv5) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv5 );
	ptImXchExecuteCmd(self, (sizeof(testArgv6) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv6 );
	ptImXchExecuteCmd(self, (sizeof(testArgv7) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv7 );
	Ddim_Print(( "* XCH end CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_set_out_localstack( D_CT_XCH_DST_TOP_ADDR, 816*612 );

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " end\n" ));
}

// histogram subsumpling 1/4 16bit
#undef D_IM_XCH_TEST_NO
#define D_IM_XCH_TEST_NO "2_8"
static void ptImXchDoTest28( PalladiumTestXch *self )
{
	PalladiumTestXchPrivate *priv = PALLADIUM_TEST_XCH_GET_PRIVATE(self);
	//	char testArgv1[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "1", "0"};
	strcpy(priv->testArgv1[2], "0");
	char testArgv2[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "3", "0", "2", "1632", "1632", "612", "0"};
	char testArgv3[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "5", "0", "1", "0", "0x44444444", "6628", "0"};
	char testArgv4[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "9", "0", "2"};
	char testArgv5[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "10"};
	char testArgv6[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "11"};
	char testArgv7[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "2", "0"};

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_XCH_SRC_TOP_ADDR, 3264*2448*2 );

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* XCH begin CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));
	ptImXchExecuteCmd(self, (sizeof(priv ->testArgv1) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)priv ->testArgv1 );
	ptImXchExecuteCmd(self, (sizeof(testArgv2) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv2 );
	ptImXchExecuteCmd(self, (sizeof(testArgv3) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv3 );
	ptImXchExecuteCmd(self, (sizeof(testArgv4) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv4 );
	ptImXchExecuteCmd(self, (sizeof(testArgv5) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv5 );
	ptImXchExecuteCmd(self, (sizeof(testArgv6) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv6 );
	ptImXchExecuteCmd(self, (sizeof(testArgv7) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv7 );
	Ddim_Print(( "* XCH end CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_set_out_localstack( D_CT_XCH_DST_TOP_ADDR, 816*612*2 );

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " end\n" ));
}

// histogram subsumpling 1/4 8bit
#undef D_IM_XCH_TEST_NO
#define D_IM_XCH_TEST_NO "2_9"
static void ptImXchDoTest29( PalladiumTestXch *self )
{
	PalladiumTestXchPrivate *priv = PALLADIUM_TEST_XCH_GET_PRIVATE(self);
	//	char testArgv1[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "1", "0"};
	strcpy(priv->testArgv1[2], "0");
	char testArgv2[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "3", "0", "2", "816", "816", "612", "0"};
	char testArgv3[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "5", "0", "0", "0", "0x44444444", "3264", "0"};
	char testArgv4[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "9", "0", "0"};
	char testArgv5[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "10"};
	char testArgv6[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "11"};
	char testArgv7[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "3", "0", "2", "816", "816", "612", "0"};
	char testArgv8[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "5", "0", "0", "0", "0x44444444", "3264", "1"};
	char testArgv9[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "9", "0", "0"};
	char testArgv10[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "10"};
	char testArgv11[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "11"};
	char testArgv12[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "2", "0"};

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_XCH_SRC_TOP_ADDR, 3264*2448 );

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* XCH begin CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));
	ptImXchExecuteCmd(self, (sizeof(priv ->testArgv1) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)priv ->testArgv1 );
	ptImXchExecuteCmd(self, (sizeof(testArgv2) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv2 );
	ptImXchExecuteCmd(self, (sizeof(testArgv3) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv3 );
	ptImXchExecuteCmd(self, (sizeof(testArgv4) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv4 );
	ptImXchExecuteCmd(self, (sizeof(testArgv5) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv5 );
	ptImXchExecuteCmd(self, (sizeof(testArgv6) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv6 );
	ptImXchExecuteCmd(self, (sizeof(testArgv7) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv7 );
	ptImXchExecuteCmd(self, (sizeof(testArgv8) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv8 );
	ptImXchExecuteCmd(self, (sizeof(testArgv9) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv9 );
	ptImXchExecuteCmd(self, (sizeof(testArgv10) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv10 );
	ptImXchExecuteCmd(self, (sizeof(testArgv11) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv11 );
	ptImXchExecuteCmd(self, (sizeof(testArgv12) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv12 );
	Ddim_Print(( "* XCH end CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_set_out_localstack( D_CT_XCH_DST_TOP_ADDR, 816*612 );

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " end\n" ));
}

// histogram subsumpling 1/4 8bit
#undef D_IM_XCH_TEST_NO
#define D_IM_XCH_TEST_NO "2_10"
static void ptImXchDoTest210( PalladiumTestXch *self )
{
	PalladiumTestXchPrivate *priv = PALLADIUM_TEST_XCH_GET_PRIVATE(self);
	//	char testArgv1[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "1", "0"};
	strcpy(priv->testArgv1[2], "0");
	char testArgv2[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "3", "0", "3", "816", "816", "612", "0"};
	char testArgv3[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "5", "0", "0", "0", "0x44444444", "3264", "0"};
	char testArgv4[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "9", "0", "0"};
	char testArgv5[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "10"};
	char testArgv6[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "11"};
	char testArgv7[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "2", "0"};

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_XCH_SRC_TOP_ADDR, 3264*2448 );

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* XCH begin CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));
	ptImXchExecuteCmd(self, (sizeof(priv ->testArgv1) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)priv ->testArgv1 );
	ptImXchExecuteCmd(self, (sizeof(testArgv2) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv2 );
	ptImXchExecuteCmd(self, (sizeof(testArgv3) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv3 );
	ptImXchExecuteCmd(self, (sizeof(testArgv4) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv4 );
	ptImXchExecuteCmd(self, (sizeof(testArgv5) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv5 );
	ptImXchExecuteCmd(self, (sizeof(testArgv6) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv6 );
	ptImXchExecuteCmd(self, (sizeof(testArgv7) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv7 );
	Ddim_Print(( "* XCH end CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_set_out_localstack( D_CT_XCH_DST_TOP_ADDR, 816*612 );

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " end\n" ));
}

// histogram subsumpling 1/4 16bit
#undef D_IM_XCH_TEST_NO
#define D_IM_XCH_TEST_NO "2_11"
static void ptImXchDoTest211( PalladiumTestXch *self )
{
	PalladiumTestXchPrivate *priv = PALLADIUM_TEST_XCH_GET_PRIVATE(self);
	//	char testArgv1[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "1", "0"};
	strcpy(priv->testArgv1[2], "0");
	char testArgv2[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "3", "0", "3", "816", "816", "612", "0"};
	char testArgv3[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "5", "0", "1", "0", "0x44444444", "3264", "0"};
	char testArgv4[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "9", "0", "2"};
	char testArgv5[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "10"};
	char testArgv6[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "11"};
	char testArgv7[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "2", "0"};

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_XCH_SRC_TOP_ADDR, 3264*2448*2 );

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* XCH begin CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));
	ptImXchExecuteCmd(self, (sizeof(priv ->testArgv1) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)priv ->testArgv1 );
	ptImXchExecuteCmd(self, (sizeof(testArgv2) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv2 );
	ptImXchExecuteCmd(self, (sizeof(testArgv3) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv3 );
	ptImXchExecuteCmd(self, (sizeof(testArgv4) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv4 );
	ptImXchExecuteCmd(self, (sizeof(testArgv5) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv5 );
	ptImXchExecuteCmd(self, (sizeof(testArgv6) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv6 );
	ptImXchExecuteCmd(self, (sizeof(testArgv7) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv7 );
	Ddim_Print(( "* XCH end CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_set_out_localstack( D_CT_XCH_DST_TOP_ADDR, 816*612*2 );

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " end\n" ));
}

// histogram subsumpling 1/4 8bit
#undef D_IM_XCH_TEST_NO
#define D_IM_XCH_TEST_NO "2_12"
static void ptImXchDoTest212( PalladiumTestXch *self )
{
	PalladiumTestXchPrivate *priv = PALLADIUM_TEST_XCH_GET_PRIVATE(self);
	//	char testArgv1[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "1", "0"};
	strcpy(priv->testArgv1[2], "0");
	char testArgv2[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "3", "0", "3", "816", "816", "612", "0"};
	char testArgv3[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "5", "0", "0", "0", "0x44444444", "3264", "0"};
	char testArgv4[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "9", "0", "0"};
	char testArgv5[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "10"};
	char testArgv6[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "11"};
	char testArgv7[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "3", "0", "3", "816", "816", "612", "0"};
	char testArgv8[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "5", "0", "0", "0", "0x44444444", "3264", "1"};
	char testArgv9[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "9", "0", "0"};
	char testArgv10[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "10"};
	char testArgv11[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "11"};
	char testArgv12[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "2", "0"};

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_XCH_SRC_TOP_ADDR, 3264*2448 );

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* XCH begin CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));
	ptImXchExecuteCmd(self, (sizeof(priv ->testArgv1) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)priv ->testArgv1 );
	ptImXchExecuteCmd(self, (sizeof(testArgv2) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv2 );
	ptImXchExecuteCmd(self, (sizeof(testArgv3) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv3 );
	ptImXchExecuteCmd(self, (sizeof(testArgv4) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv4 );
	ptImXchExecuteCmd(self, (sizeof(testArgv5) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv5 );
	ptImXchExecuteCmd(self, (sizeof(testArgv6) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv6 );
	ptImXchExecuteCmd(self, (sizeof(testArgv7) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv7 );
	ptImXchExecuteCmd(self, (sizeof(testArgv8) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv8 );
	ptImXchExecuteCmd(self, (sizeof(testArgv9) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv9 );
	ptImXchExecuteCmd(self, (sizeof(testArgv10) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv10 );
	ptImXchExecuteCmd(self, (sizeof(testArgv11) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv11 );
	ptImXchExecuteCmd(self, (sizeof(testArgv12) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv12 );
	Ddim_Print(( "* XCH end CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_set_out_localstack( D_CT_XCH_DST_TOP_ADDR, 816*612 );

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " end\n" ));
}

// 1/2 subsumpling even (sync)
#undef D_IM_XCH_TEST_NO
#define D_IM_XCH_TEST_NO "2_13"
static void ptImXchDoTest213(PalladiumTestXch *self )
{
	PalladiumTestXchPrivate *priv = PALLADIUM_TEST_XCH_GET_PRIVATE(self);
	//	char testArgv1[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "1", "0"};
	strcpy(priv->testArgv1[2], "0");
	char testArgv2[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "3", "0", "4", "1632", "1632", "2448", "0"};
	char testArgv3[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "6", "0", "0", "0xFFFFFFFF", "3264"};
	char testArgv4[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "9", "0", "0"};
	char testArgv5[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "2", "0"};

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_XCH_SRC_TOP_ADDR, 3264*2448 );

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* XCH begin CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));
	ptImXchExecuteCmd(self, (sizeof(priv ->testArgv1) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)priv ->testArgv1 );
	ptImXchExecuteCmd(self, (sizeof(testArgv2) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv2 );
	ptImXchExecuteCmd(self, (sizeof(testArgv3) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv3 );
	ptImXchExecuteCmd(self, (sizeof(testArgv4) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv4 );
	ptImXchExecuteCmd(self, (sizeof(testArgv5) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv5 );
	Ddim_Print(( "* XCH end CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_set_out_localstack( D_CT_XCH_DST_TOP_ADDR, (3264/2)*2448 );

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " end\n" ));
}

// 1/2 subsumpling even (async)
#undef D_IM_XCH_TEST_NO
#define D_IM_XCH_TEST_NO "2_14"
static void ptImXchDoTest214( PalladiumTestXch *self)
{
	PalladiumTestXchPrivate *priv = PALLADIUM_TEST_XCH_GET_PRIVATE(self);
	//	char testArgv1[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "1", "0"};
	strcpy(priv->testArgv1[2], "0");
	char testArgv2[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "3", "1", "4", "1632", "1632", "1224", "0"};
	char testArgv3[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "6", "1", "0", "0xAAAAAAAA", "3264"};
	char testArgv4[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "9", "1", "1"};
	char testArgv5[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "2", "1"};

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_XCH_SRC_TOP_ADDR, 3264*2448 );

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* XCH begin CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));
	ptImXchExecuteCmd(self, (sizeof(priv ->testArgv1) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)priv ->testArgv1 );
	ptImXchExecuteCmd(self, (sizeof(testArgv2) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv2 );
	ptImXchExecuteCmd(self, (sizeof(testArgv3) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv3 );
	ptImXchExecuteCmd(self, (sizeof(testArgv4) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv4 );
	ptImXchExecuteCmd(self, (sizeof(testArgv5) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv5 );
	Ddim_Print(( "* XCH end CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_set_out_localstack( D_CT_XCH_DST_TOP_ADDR, 3264*(2448/2) );

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " end\n" ));
}

// 1/2 subsumpling odd (sync)
#undef D_IM_XCH_TEST_NO
#define D_IM_XCH_TEST_NO "2_15"
static void ptImXchDoTest215(PalladiumTestXch *self )
{
	PalladiumTestXchPrivate *priv = PALLADIUM_TEST_XCH_GET_PRIVATE(self);
	//	char testArgv1[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "1", "0"};
	strcpy(priv->testArgv1[2], "0");
	char testArgv2[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "3", "0", "5", "1632", "1632", "2448", "0"};
	char testArgv3[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "6", "0", "0", "0xFFFFFFFF", "3264"};
	char testArgv4[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "9", "0", "0"};
	char testArgv5[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "2", "0"};

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_XCH_SRC_TOP_ADDR, 3264*2448 );

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* XCH begin CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));
	ptImXchExecuteCmd(self, (sizeof(priv ->testArgv1) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)priv ->testArgv1 );
	ptImXchExecuteCmd(self, (sizeof(testArgv2) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv2 );
	ptImXchExecuteCmd(self, (sizeof(testArgv3) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv3 );
	ptImXchExecuteCmd(self, (sizeof(testArgv4) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv4 );
	ptImXchExecuteCmd(self, (sizeof(testArgv5) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv5 );
	Ddim_Print(( "* XCH end CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_set_out_localstack( D_CT_XCH_DST_TOP_ADDR, (3264/2)*2448 );

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " end\n" ));
}

// 1/2 subsumpling odd (async)
#undef D_IM_XCH_TEST_NO
#define D_IM_XCH_TEST_NO "2_16"
static void ptImXchDoTest216(PalladiumTestXch *self)
{
	PalladiumTestXchPrivate *priv = PALLADIUM_TEST_XCH_GET_PRIVATE(self);
	//	char testArgv1[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "1", "1"};
	strcpy(priv->testArgv1[2], "1");
	char testArgv2[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "3", "1", "5", "1632", "1632", "1224", "0"};
	char testArgv3[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "6", "1", "0", "0xAAAAAAAA", "3264"};
	char testArgv4[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "9", "1", "1"};
	char testArgv5[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "2", "1"};

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_XCH_SRC_TOP_ADDR, 3264*2448 );

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* XCH begin CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));
	ptImXchExecuteCmd(self, (sizeof(priv ->testArgv1) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)priv ->testArgv1 );
	ptImXchExecuteCmd(self, (sizeof(testArgv2) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv2 );
	ptImXchExecuteCmd(self, (sizeof(testArgv3) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv3 );
	ptImXchExecuteCmd(self, (sizeof(testArgv4) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv4 );
	ptImXchExecuteCmd(self, (sizeof(testArgv5) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv5 );
	Ddim_Print(( "* XCH end CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_set_out_localstack( D_CT_XCH_DST_TOP_ADDR, 3264*(2448/2) );

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " end\n" ));
}

// copy (sync)
#undef D_IM_XCH_TEST_NO
#define D_IM_XCH_TEST_NO "2_17"
static void ptImXchDoTest217(PalladiumTestXch *self)
{
	PalladiumTestXchPrivate *priv = PALLADIUM_TEST_XCH_GET_PRIVATE(self);
	//	char testArgv1[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "1", "0"};
	strcpy(priv->testArgv1[2], "0");
	char testArgv2[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "3", "0", "6", "3264", "3264", "2448", "0"};
	char testArgv3[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "6", "0", "0", "0xFFFFFFFF", "3264"};
	char testArgv4[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "9", "0", "0"};
	char testArgv5[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "2", "0"};

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_XCH_SRC_TOP_ADDR, 3264*2448 );

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* XCH begin CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));
	ptImXchExecuteCmd(self, (sizeof(priv ->testArgv1) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)priv ->testArgv1 );
	ptImXchExecuteCmd(self, (sizeof(testArgv2) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv2 );
	ptImXchExecuteCmd(self, (sizeof(testArgv3) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv3 );
	ptImXchExecuteCmd(self, (sizeof(testArgv4) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv4 );
	ptImXchExecuteCmd(self, (sizeof(testArgv5) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv5 );
	Ddim_Print(( "* XCH end CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_set_out_localstack( D_CT_XCH_DST_TOP_ADDR, 3264*2448 );

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " end\n" ));
}

// copy (async)
#undef D_IM_XCH_TEST_NO
#define D_IM_XCH_TEST_NO "2_18"
static void ptImXchDoTest218(PalladiumTestXch *self )
{
	PalladiumTestXchPrivate *priv = PALLADIUM_TEST_XCH_GET_PRIVATE(self);
	//	char testArgv1[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "1", "1"};
	strcpy(priv->testArgv1[2], "1");
	char testArgv2[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "3", "1", "6", "3264", "3264", "2448", "1"};
	char testArgv3[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "6", "1", "0", "0xFFFFFFFF", "3264"};
	char testArgv4[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "9", "1", "2"};
	char testArgv5[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "2", "1"};

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_XCH_SRC_TOP_ADDR, 3264*2448 );

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* XCH begin CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));
	ptImXchExecuteCmd(self, (sizeof(priv ->testArgv1) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)priv ->testArgv1 );
	ptImXchExecuteCmd(self, (sizeof(testArgv2) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv2 );
	ptImXchExecuteCmd(self, (sizeof(testArgv3) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv3 );
	ptImXchExecuteCmd(self, (sizeof(testArgv4) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv4 );
	ptImXchExecuteCmd(self, (sizeof(testArgv5) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv5 );
	Ddim_Print(( "* XCH end CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_set_out_localstack( D_CT_XCH_DST_TOP_ADDR, 3264*2448 );

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " end\n" ));
}

// fill (sync)
#undef D_IM_XCH_TEST_NO
#define D_IM_XCH_TEST_NO "2_19"
static void ptImXchDoTest219(PalladiumTestXch *self )
{
	PalladiumTestXchPrivate *priv = PALLADIUM_TEST_XCH_GET_PRIVATE(self);
	//	char testArgv1[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "1", "1"};
	strcpy(priv->testArgv1[2], "1");
	char testArgv2[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "3", "0", "7", "3264", "640", "480", "0"};
	char testArgv3[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "8", "0", "128"};
	char testArgv4[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "9", "0", "0"};
	char testArgv5[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "2", "0"};

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_XCH_SRC_TOP_ADDR, 3264*2448 );

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* XCH begin CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));
	ptImXchExecuteCmd(self, (sizeof(priv ->testArgv1) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)priv ->testArgv1 );
	ptImXchExecuteCmd(self, (sizeof(testArgv2) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv2 );
	ptImXchExecuteCmd(self, (sizeof(testArgv3) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv3 );
	ptImXchExecuteCmd(self, (sizeof(testArgv4) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv4 );
	ptImXchExecuteCmd(self, (sizeof(testArgv5) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv5 );
	Ddim_Print(( "* XCH end CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_set_out_localstack( D_CT_XCH_DST_TOP_ADDR, 3264*2448 );

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " end\n" ));
}

// fill (async)
#undef D_IM_XCH_TEST_NO
#define D_IM_XCH_TEST_NO "2_20"
static void ptImXchDoTest220(PalladiumTestXch *self)
{
	PalladiumTestXchPrivate *priv = PALLADIUM_TEST_XCH_GET_PRIVATE(self);
	//	char testArgv1[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "1", "1"};
	strcpy(priv->testArgv1[2], "1");
	char testArgv2[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "3", "1", "7", "3264", "640", "480", "0"};
	char testArgv3[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "8", "1", "0"};
	char testArgv4[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "9", "1", "1"};
	char testArgv5[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "2", "1"};

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_XCH_SRC_TOP_ADDR, 3264*2448 );

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* XCH begin CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));
	ptImXchExecuteCmd(self, (sizeof(priv ->testArgv1) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)priv ->testArgv1 );
	ptImXchExecuteCmd(self, (sizeof(testArgv2) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv2 );
	ptImXchExecuteCmd(self, (sizeof(testArgv3) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv3 );
	ptImXchExecuteCmd(self, (sizeof(testArgv4) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv4 );
	ptImXchExecuteCmd(self, (sizeof(testArgv5) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv5 );
	Ddim_Print(( "* XCH end CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_set_out_localstack( D_CT_XCH_DST_TOP_ADDR, 3264*2448 );

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " end\n" ));
}

// utility : copy (sync)
#undef D_IM_XCH_TEST_NO
#define D_IM_XCH_TEST_NO "2_21"
static void ptImXchDoTest221(PalladiumTestXch *self)
{
	char testArgv1[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "21", "0", "3264", "2448"};

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_XCH_SRC_TOP_ADDR, 3264*2448 );

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* XCH begin CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));
	ptImXchExecuteCmd(self, (sizeof(testArgv1) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv1 );
	Ddim_Print(( "* XCH end CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_set_out_localstack( D_CT_XCH_DST_TOP_ADDR, 3264*2448 );

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " end\n" ));
}

// utility : copy (async)
#undef D_IM_XCH_TEST_NO
#define D_IM_XCH_TEST_NO "2_22"
static void ptImXchDoTest222(PalladiumTestXch *self)
{
	char testArgv1[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "21", "1", "3264", "2448"};

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_XCH_SRC_TOP_ADDR, 3264*2448 );

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* XCH begin CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));
	ptImXchExecuteCmd(self, (sizeof(testArgv1) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv1 );
	Ddim_Print(( "* XCH end CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_set_out_localstack( D_CT_XCH_DST_TOP_ADDR, 3264*2448 );

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " end\n" ));
}

// utility : copy_ex_sync
#undef D_IM_XCH_TEST_NO
#define D_IM_XCH_TEST_NO "2_23"
static void ptImXchDoTest223(PalladiumTestXch *self)
{
	char testArgv1[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "22", "0", "0", "3264", "3264", "2448", "0"};

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_XCH_SRC_TOP_ADDR, 3264*2448 );

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* XCH begin CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));
	ptImXchExecuteCmd(self, (sizeof(testArgv1) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv1 );
	Ddim_Print(( "* XCH end CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_set_out_localstack( D_CT_XCH_DST_TOP_ADDR, 3264*2448 );

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " end\n" ));
}

// utility : copy_ex_async
#undef D_IM_XCH_TEST_NO
#define D_IM_XCH_TEST_NO "2_24"
static void ptImXchDoTest224(PalladiumTestXch *self)
{
	char testArgv1[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "22", "1", "1", "3264", "3264", "2448", "1"};

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_XCH_SRC_TOP_ADDR, 3264*2448 );

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* XCH begin CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));
	ptImXchExecuteCmd(self, (sizeof(testArgv1) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv1 );
	Ddim_Print(( "* XCH end CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_set_out_localstack( D_CT_XCH_DST_TOP_ADDR, 3264*2448 );

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " end\n" ));
}

// utility : fill
#undef D_IM_XCH_TEST_NO
#define D_IM_XCH_TEST_NO "2_25"
static void ptImXchDoTest225(PalladiumTestXch *self)
{
	char testArgv1[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "23", "0", "3264", "640", "480", "0"};

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_XCH_SRC_TOP_ADDR, 3264*2448 );

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* XCH begin CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));
	ptImXchExecuteCmd(self, (sizeof(testArgv1) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv1 );
	Ddim_Print(( "* XCH end CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_set_out_localstack( D_CT_XCH_DST_TOP_ADDR, 3264*2448 );

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " end\n" ));
}

// utility : fill_ex_sync
#undef D_IM_XCH_TEST_NO
#define D_IM_XCH_TEST_NO "2_26"
static void ptImXchDoTest226(PalladiumTestXch *self)
{
	char testArgv1[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "24", "0", "3264", "640", "480", "128", "0"};

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_XCH_SRC_TOP_ADDR, 3264*2448 );

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* XCH begin CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));
	ptImXchExecuteCmd(self, (sizeof(testArgv1) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv1 );
	Ddim_Print(( "* XCH end CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_set_out_localstack( D_CT_XCH_DST_TOP_ADDR, 3264*2448 );

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " end\n" ));
}

// utility : fill_ex_async
#undef D_IM_XCH_TEST_NO
#define D_IM_XCH_TEST_NO "2_27"
static void ptImXchDoTest227(PalladiumTestXch *self)
{
	char testArgv1[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "24", "1", "3264", "640", "480", "0", "1"};

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_XCH_SRC_TOP_ADDR, 3264*2448 );

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* XCH begin CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));
	ptImXchExecuteCmd(self, (sizeof(testArgv1) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv1 );
	Ddim_Print(( "* XCH end CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_set_out_localstack( D_CT_XCH_DST_TOP_ADDR, 3264*2448 );

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " end\n" ));
}

// utility : convert subsumpling sync (1/1 subsumpling)
#undef D_IM_XCH_TEST_NO
#define D_IM_XCH_TEST_NO "2_28"
static void ptImXchDoTest228( void )
{
	char testArgv1[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "25", "0", "0", "0", "3264", "3264", "2448", "0"};

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_XCH_SRC_TOP_ADDR, 3264*2448 );

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* XCH begin CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));
	ptImXchExecuteCmd( (sizeof(testArgv1) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv1 );
	Ddim_Print(( "* XCH end CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_set_out_localstack( D_CT_XCH_DST_TOP_ADDR, 3264*2448 );

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " end\n" ));
}

// utility : convert subsumpling sync (1/2 subsumpling)
#undef D_IM_XCH_TEST_NO
#define D_IM_XCH_TEST_NO "2_29"
static void ptImXchDoTest229( PalladiumTestXch *self)
{
	char testArgv1[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "25", "0", "1", "1", "1632", "3264", "2448", "0"};

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_XCH_SRC_TOP_ADDR, 3264*2448 );

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* XCH begin CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));
	ptImXchExecuteCmd( (sizeof(testArgv1) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv1 );
	Ddim_Print(( "* XCH end CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_set_out_localstack( D_CT_XCH_DST_TOP_ADDR, (3264*2448)/4 );

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " end\n" ));
}

// utility : convert subsumpling sync (1/4 subsumpling)
#undef D_IM_XCH_TEST_NO
#define D_IM_XCH_TEST_NO "2_30"
static void ptImXchDoTest230( PalladiumTestXch *self)
{
	char testArgv1[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "25", "0", "2", "2", "816", "3264", "2448", "0"};

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_XCH_SRC_TOP_ADDR, 3264*2448 );

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* XCH begin CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));
	ptImXchExecuteCmd( (sizeof(testArgv1) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv1 );
	Ddim_Print(( "* XCH end CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_set_out_localstack( D_CT_XCH_DST_TOP_ADDR, (3264*2448)/16 );

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " end\n" ));
}

// utility : convert subsumpling sync (3/4 subsumpling)
#undef D_IM_XCH_TEST_NO
#define D_IM_XCH_TEST_NO "2_31"
static void ptImXchDoTest231( PalladiumTestXch *self)
{
	char testArgv1[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "25", "0", "3", "3", "2448", "3264", "2448", "0"};

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_XCH_SRC_TOP_ADDR, 3264*2448 );

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* XCH begin CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));
	ptImXchExecuteCmd( (sizeof(testArgv1) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv1 );
	Ddim_Print(( "* XCH end CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_set_out_localstack( D_CT_XCH_DST_TOP_ADDR, 2448*1836 );

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " end\n" ));
}

// utility : convert subsumpling async (1/2 subsumpling)
#undef D_IM_XCH_TEST_NO
#define D_IM_XCH_TEST_NO "2_32"
static void ptImXchDoTest232( PalladiumTestXch *self)
{
	char testArgv1[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "25", "1", "1", "1", "1632", "3264", "2448", "1"};

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_XCH_SRC_TOP_ADDR, 3264*2448 );

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* XCH begin CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));
	ptImXchExecuteCmd( (sizeof(testArgv1) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv1 );
	Ddim_Print(( "* XCH end CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_set_out_localstack( D_CT_XCH_DST_TOP_ADDR, (3264*2448)/4 );

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " end\n" ));
}

// utility : histogram sync
#undef D_IM_XCH_TEST_NO
#define D_IM_XCH_TEST_NO "2_33"
static void ptImXchDoTest233( PalladiumTestXch *self)
{
	char testArgv1[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "26", "3264", "2448", "0"};

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_XCH_SRC_TOP_ADDR, 3264*2448 );

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* XCH begin CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));
	ptImXchExecuteCmd(self, (sizeof(testArgv1) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv1 );
	Ddim_Print(( "* XCH end CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_set_out_localstack( D_CT_XCH_DST_TOP_ADDR, 3264*2448 );

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " end\n" ));
}

// utility : histogram async
#undef D_IM_XCH_TEST_NO
#define D_IM_XCH_TEST_NO "2_34"
static void ptImXchDoTest234( PalladiumTestXch *self)
{
	char testArgv1[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "26", "3264", "2448", "1"};

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_XCH_SRC_TOP_ADDR, 3264*2448 );

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* XCH begin CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));
	ptImXchExecuteCmd(self, (sizeof(testArgv1) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv1 );
	Ddim_Print(( "* XCH end CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_set_out_localstack( D_CT_XCH_DST_TOP_ADDR, 3264*2448 );

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " end\n" ));
}

// utility : copy dual channel
#undef D_IM_XCH_TEST_NO
#define D_IM_XCH_TEST_NO "2_35"
static void ptImXchDoTest235( PalladiumTestXch *self)
{
	char testArgv1[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "27", "65536", "1024"};

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_XCH_SRC_TOP_ADDR, 3264*2448 );

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* XCH begin CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));
	ptImXchExecuteCmd(self, (sizeof(testArgv1) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv1 );
	Ddim_Print(( "* XCH end CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_set_out_localstack( D_CT_XCH_DST_TOP_ADDR, 3264*2448 );

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " end\n" ));
}

// utility : copy dual channel (fill-1)
#undef D_IM_XCH_TEST_NO
#define D_IM_XCH_TEST_NO "2_36"
static void ptImXchDoTest236( PalladiumTestXch *self)
{
	char testArgv1[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "27", "2048", "8"};

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_XCH_SRC_TOP_ADDR, 3264*2448 );

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* XCH begin CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));
	ptImXchExecuteCmd(self, (sizeof(testArgv1) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv1 );
	Ddim_Print(( "* XCH end CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_set_out_localstack( D_CT_XCH_DST_TOP_ADDR, 3264*2448 );

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " end\n" ));
}

// utility : copy dual channel (fill-2)
#undef D_IM_XCH_TEST_NO
#define D_IM_XCH_TEST_NO "2_37"
static void ptImXchDoTest237( PalladiumTestXch *self)
{
	char testArgv1[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "27", "1024", "8"};

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_XCH_SRC_TOP_ADDR, 3264*2448 );

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* XCH begin CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));
	ptImXchExecuteCmd(self, (sizeof(testArgv1) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv1 );
	Ddim_Print(( "* XCH end CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_set_out_localstack( D_CT_XCH_DST_TOP_ADDR, 3264*2448 );

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " end\n" ));
}

// utility : copy dual channel (fill-3)
#undef D_IM_XCH_TEST_NO
#define D_IM_XCH_TEST_NO "2_38"
static void ptImXchDoTest238( PalladiumTestXch *self)
{
	char testArgv1[][PalladiumTestXch_D_PT_XCH_CMD_LEN] = {"imxch", "27", "512", "8"};

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " begin\n" ));

	// 入力データ
	Palladium_Set_In_Localstack( D_CT_XCH_SRC_TOP_ADDR, 3264*2448 );

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// テストコード起動
	Ddim_Print(( "* XCH begin CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));
	ptImXchExecuteCmd(self, (sizeof(testArgv1) / PalladiumTestXch_D_PT_XCH_CMD_LEN), (char*)testArgv1 );
	Ddim_Print(( "* XCH end CT_Im_Xch_" D_IM_XCH_TEST_NO "\n" ));

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	palladium_set_out_localstack( D_CT_XCH_DST_TOP_ADDR, 3264*2448 );

	Ddim_Print(( "*** XCH test " D_IM_XCH_TEST_NO " end\n" ));
}

/*
 * PUBULIC
 */

void palladium_test_xch_im_main( PalladiumTestXch *self)
{
	kuchar			type1;

	// 開始...
	Ddim_Print(( "****** XCH begin palladium_test_xch_im_main\n" ));

	// タイマー初期化
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_INIT );

	// テストパラメータ取得
	type1	= gDdimInfo.com._6a;


	Ddim_Print(( "*** XCH begin Im_XCH_Init\n" ));
	Im_Xch_Init();
	Ddim_Print(( "*** XCH end Im_XCH_Init\n" ));

	ptImXchEnableGic();
	ptImXchStartGic();

	switch( type1 ) {
		case 1:
			ptImXchDoTest21(self);
			Ddim_Print(( "\n" ));
			break;
		case 2:
			ptImXchDoTest22(self);
			Ddim_Print(( "\n" ));
			break;
		case 3:
			ptImXchDoTest23(self);
			Ddim_Print(( "\n" ));
			break;
		case 4:
			ptImXchDoTest24(self);
			Ddim_Print(( "\n" ));
			break;
		case 5:
			ptImXchDoTest25(self);
			Ddim_Print(( "\n" ));
			break;
		case 6:
			ptImXchDoTest26(self);
			Ddim_Print(( "\n" ));
			break;
		case 7:
			ptImXchDoTest27(self);
			Ddim_Print(( "\n" ));
			break;
		case 8:
			ptImXchDoTest28(self);
			Ddim_Print(( "\n" ));
			break;
		case 9:
			ptImXchDoTest29(self);
			Ddim_Print(( "\n" ));
			break;
		case 10:
			ptImXchDoTest210(self);
			Ddim_Print(( "\n" ));
			break;
		case 11:
			ptImXchDoTest211(self);
			Ddim_Print(( "\n" ));
			break;
		case 12:
			ptImXchDoTest212(self);
			Ddim_Print(( "\n" ));
			break;
		case 13:
			ptImXchDoTest213(self);
			Ddim_Print(( "\n" ));
			break;
		case 14:
			ptImXchDoTest214(self);
			Ddim_Print(( "\n" ));
			break;
		case 15:
			ptImXchDoTest215(self);
			Ddim_Print(( "\n" ));
			break;
		case 16:
			ptImXchDoTest216(self);
			Ddim_Print(( "\n" ));
			break;
		case 17:
			ptImXchDoTest217(self);
			Ddim_Print(( "\n" ));
			break;
		case 18:
			ptImXchDoTest218(self);
			Ddim_Print(( "\n" ));
			break;
		case 19:
			ptImXchDoTest219(self);
			Ddim_Print(( "\n" ));
			break;
		case 20:
			ptImXchDoTest220(self);
			Ddim_Print(( "\n" ));
			break;
		case 21:
			ptImXchDoTest221(self);
			Ddim_Print(( "\n" ));
			break;
		case 22:
			ptImXchDoTest222(self);
			Ddim_Print(( "\n" ));
			break;
		case 23:
			ptImXchDoTest223(self);
			Ddim_Print(( "\n" ));
			break;
		case 24:
			ptImXchDoTest224(self);
			Ddim_Print(( "\n" ));
			break;
		case 25:
			ptImXchDoTest225(self);
			Ddim_Print(( "\n" ));
			break;
		case 26:
			ptImXchDoTest226(self);
			Ddim_Print(( "\n" ));
			break;
		case 27:
			ptImXchDoTest227(self);
			Ddim_Print(( "\n" ));
			break;
		case 28:
			ptImXchDoTest228(self);
			Ddim_Print(( "\n" ));
			break;
		case 29:
			ptImXchDoTest229(self);
			Ddim_Print(( "\n" ));
			break;
		case 30:
			ptImXchDoTest230(self);
			Ddim_Print(( "\n" ));
			break;
		case 31:
			ptImXchDoTest231(self);
			Ddim_Print(( "\n" ));
			break;
		case 32:
			ptImXchDoTest232(self);
			Ddim_Print(( "\n" ));
			break;
		case 33:
			ptImXchDoTest233(self);
			Ddim_Print(( "\n" ));
			break;
		case 34:
			ptImXchDoTest234(self);
			Ddim_Print(( "\n" ));
			break;
		case 35:
			ptImXchDoTest235(self);
			Ddim_Print(( "\n" ));
			break;
		case 36:
			ptImXchDoTest236(self);
			Ddim_Print(( "\n" ));
			break;
		case 37:
			ptImXchDoTest237(self);
			Ddim_Print(( "\n" ));
			break;
		case 38:
			ptImXchDoTest238(self);
			Ddim_Print(( "\n" ));
			break;
		default:
			Ddim_Print(("*** XCH test skip\n" ));
			break;
	}

	// タイマーログ出力
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_PRINT );

	// テスト強制終了処理
	palladium_test_force_stop();
}

PalladiumTestXch* palladium_test_xch_new(void)
{
	PalladiumTestXch *self = k_object_new_with_private(PALLADIUM_TYPE_TEST_XCH, sizeof(PalladiumTestXchPrivate));
	return self;
}
