/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-07
*@author              :刘杰
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年06月开始开发
*/

/**
 * @file    palladium_test_mxic.c
 * @brief   MXIC test code on palladium
 * @note    None
 * @attention None
 *
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */

#include "im_mxic.h"
#include "ct_im_mxic.h"
#include "dd_gic.h"
#include "dd_top.h"
#include "driver_common.h"
#include "palladium_test.h"
#include "palladiumtestmxic.h"

K_TYPE_DEFINE_WITH_PRIVATE(PalladiumTestMxic, palladium_test_mxic);
#define PALLADIUM_TEST_MXIC_GET_PRIVATE(o) \
  (K_OBJECT_GET_PRIVATE ((o), PalladiumTestMxicPrivate,PALLADIUM_TYPE_TEST_MXIC))

/*----------------------------------------------------------------------*/
/* Definition                             */
/*----------------------------------------------------------------------*/
#define PalladiumTestMxic_PT_MXIC_CMD_LEN     (20)

/*----------------------------------------------------------------------*/
/* Global Data                              */
/*----------------------------------------------------------------------*/
static char* S_G_CMD_ARGV[ PalladiumTestMxic_PT_MXIC_CMD_LEN ];

struct _PalladiumTestMxicPrivate
{
};

/*
 * DECLS
 */
static VOID ptImMxicEnableGic( VOID );
static VOID ptImMxicStartClock( VOID );
static void ptImMxicExecuteCmd( int cmdArgc, char* cmdArgv );

static void palladium_test_mxic_constructor(PalladiumTestMxic *self)
{
//	PalladiumTestMxicPrivate *priv = PALLADIUM_TEST_MXIC_GET_PRIVATE(self);
}

static void palladium_test_mxic_destructor(PalladiumTestMxic *self)
{
//  PalladiumTestMxicPrivate *priv = PALLADIUM_TEST_MXIC_GET_PRIVATE(self);
}

/*
 * IMPL
 */
/*----------------------------------------------------------------------*/
/* Local Function                           */
/*----------------------------------------------------------------------*/
static VOID ptImMxicEnableGic( VOID )
{
  Dd_GIC_Ctrl( E_DD_GIC_INTID_TIMER_CH0_INT,  1, D_DD_GIC_PRI30, 1 );   // cpu=0, intid=118, enable, pri=30
  Dd_GIC_Ctrl( E_DD_GIC_INTID_MXIC_UNIT0_INT, 1, D_DD_GIC_PRI30, 1 );   // int enable
  Dd_GIC_Ctrl( E_DD_GIC_INTID_MXIC_UNIT1_INT, 1, D_DD_GIC_PRI30, 1 );   // int enable
  Dd_GIC_Ctrl( E_DD_GIC_INTID_MXIC_UNIT2_INT, 1, D_DD_GIC_PRI30, 1 );   // int enable
  Dd_GIC_Ctrl( E_DD_GIC_INTID_MXIC_UNIT3_INT, 1, D_DD_GIC_PRI30, 1 );   // int enable
  Dd_GIC_Ctrl( E_DD_GIC_INTID_MXIC_UNIT4_INT, 1, D_DD_GIC_PRI30, 1 );   // int enable
  Dd_GIC_Ctrl( E_DD_GIC_INTID_MXIC_UNIT5_INT, 1, D_DD_GIC_PRI30, 1 );   // int enable
  Dd_GIC_Ctrl( E_DD_GIC_INTID_MXIC_UNIT6_INT, 1, D_DD_GIC_PRI30, 1 );   // int enable
}


static VOID ptImMxicStartClock( VOID )
{
  UCHAR imMxicPclkCtrlCnt[ 7 ] = { 0, 0, 0, 0, 0, 0, 0 };
  UCHAR imMxicHclkCtrlCnt[ 3 ] = { 0, 0, 0 };

  Dd_Top_Start_Clock( (UCHAR*)&imMxicPclkCtrlCnt[ 0 ], &Dd_Top_Get_CLKSTOP5(), ~D_DD_TOP_MICAP0_BIT );
  Dd_Top_Start_Clock( (UCHAR*)&imMxicPclkCtrlCnt[ 1 ], &Dd_Top_Get_CLKSTOP5(), ~D_DD_TOP_MICAP1_BIT );
  Dd_Top_Start_Clock( (UCHAR*)&imMxicPclkCtrlCnt[ 2 ], &Dd_Top_Get_CLKSTOP5(), ~D_DD_TOP_MICAP2_BIT );
  Dd_Top_Start_Clock( (UCHAR*)&imMxicPclkCtrlCnt[ 3 ], &Dd_Top_Get_CLKSTOP5(), ~D_DD_TOP_MICAP3_BIT );
  Dd_Top_Start_Clock( (UCHAR*)&imMxicPclkCtrlCnt[ 4 ], &Dd_Top_Get_CLKSTOP5(), ~D_DD_TOP_MICAP4_BIT );
  Dd_Top_Start_Clock( (UCHAR*)&imMxicPclkCtrlCnt[ 5 ], &Dd_Top_Get_CLKSTOP5(), ~D_DD_TOP_MICAP5_BIT );
  Dd_Top_Start_Clock( (UCHAR*)&imMxicPclkCtrlCnt[ 6 ], &Dd_Top_Get_CLKSTOP5(), ~D_DD_TOP_MICAP6_BIT );

  Dd_Top_Start_Clock( (UCHAR*)&imMxicHclkCtrlCnt[ 0 ], &Dd_Top_Get_CLKSTOP6(), ~D_DD_TOP_MICAH1_BIT );
  Dd_Top_Start_Clock( (UCHAR*)&imMxicHclkCtrlCnt[ 1 ], &Dd_Top_Get_CLKSTOP6(), ~D_DD_TOP_MICAH2_BIT );
  Dd_Top_Start_Clock( (UCHAR*)&imMxicHclkCtrlCnt[ 2 ], &Dd_Top_Get_CLKSTOP6(), ~D_DD_TOP_MICAH3_BIT );
}

static void ptImMxicExecuteCmd( int cmdArgc, char* cmdArgv )
{
  INT32 j;
  INT32 cmdPos = 0;

  if( cmdArgc > PalladiumTestMxic_PT_MXIC_CMD_LEN ) {
    cmdArgc = PalladiumTestMxic_PT_MXIC_CMD_LEN;
  }
  for( j = 0; j < cmdArgc; j++ ) {
    S_G_CMD_ARGV[ j ] = ( cmdArgv + ( cmdPos * PalladiumTestMxic_PT_MXIC_CMD_LEN ) );
    cmdPos++;
  }

  Ct_Im_MXIC_Main( cmdArgc, S_G_CMD_ARGV );
}

/*----------------------------------------------------------------------*/
/* Global Function                            */
/*----------------------------------------------------------------------*/
/**
 * @brief   MXIC main code
 * @param   void
 * @return    void
 * @note    None
 * @attention None
 */
void palladium_test_mxic_im_main( void )
{
  UINT32  testno;

  // 開始...
  Ddim_Print(( "****** MXIC begin palladium_test_mxic_im_main\n" ));

  // タイマー初期化
  Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_INIT );

  // テストパラメータ取得
  testno  = gDDIM_Info.com._6a;

  Ddim_Print(( "****** Palladium Test %d begin\n", testno ));

  ptImMxicEnableGic();
  ptImMxicStartClock();

  while( 1 ) {

    // 初期化.
    if ( testno == 0 ) {
      // タイマー起動
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

      char testArgv1[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "init", "3"};
      char testArgv2[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "master", "all",  "get", "3"};
      char testArgv3[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "pri", "slot", "all", "get", "3" };
      char testArgv4[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "levelport", "all", "get", "3"};

      ptImMxicExecuteCmd((sizeof(testArgv1) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv1);
      ptImMxicExecuteCmd((sizeof(testArgv2) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv2);
      ptImMxicExecuteCmd((sizeof(testArgv3) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv3);
      ptImMxicExecuteCmd((sizeof(testArgv4) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv4);

      // タイマー停止
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
    }
    // コンフィグレーション起動.
    else if ( testno == 1 ) {
      // タイマー起動
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

      char testArgv1[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "start", "3", "1", "1", "1", "1",
          "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1" };
      char testArgv2[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "start", "3", "0", "0", "0", "0",
          "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0" };

      // enable/disable
      ptImMxicExecuteCmd((sizeof(testArgv1) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv1);
      ptImMxicExecuteCmd((sizeof(testArgv2) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv2);

      // タイマー停止
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
    }
    // クロック供給制御.
    else if ( testno == 2 ) {
      // タイマー起動
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

      char testArgv1[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "clock", "set", "3", "1", "1", "1", "1",
          "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1" };
      char testArgv2[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "clock", "set", "3", "0", "0", "0", "0",
          "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0" };
      char testArgv3[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "clock", "get", "3" };

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv1) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv1);
      ptImMxicExecuteCmd((sizeof(testArgv3) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv3);

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv2) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv2);
      ptImMxicExecuteCmd((sizeof(testArgv3) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv3);

      // タイマー停止
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
    }
    // acceptance capability設定.
    else if ( testno == 3 ) {
      // タイマー起動
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

      char testArgv1[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "acc_capa", "all",   "set", "1", "1" };
      char testArgv2[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "acc_capa", "all",   "get", "1"      };
      char testArgv3[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "acc_capa", "slave", "set", "1", "0",
          "3", "3", "8"};
      char testArgv4[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "acc_capa", "slave", "get", "1", "0",
          "3", "3"};
      char testArgv5[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "acc_capa", "group", "set",  "0",
          "7", "1", "1"};
      char testArgv6[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "acc_capa", "group", "get", "0",
          "7", "1"};

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv1) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv1);
      ptImMxicExecuteCmd((sizeof(testArgv2) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv2);

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv3) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv3);
      ptImMxicExecuteCmd((sizeof(testArgv4) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv4);

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv5) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv5);
      ptImMxicExecuteCmd((sizeof(testArgv6) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv6);

      // タイマー停止
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
    }
    // スレーブ領域設定.
    else if ( testno == 4 ) {
      // タイマー起動
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

      char testArgv1[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "slave_area", "all", "set", "3",
          "0x20000000", "0x40000000", "0x20000000", "0x60000000", "0x20000000", "0x80000000", "0x20000000",
          "0xA0000000" };
      char testArgv2[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "slave_area", "all", "get", "3", };
      char testArgv3[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "slave_area", "one", "set", "3", "0",
          "0x40000000", "0x40000000" };
      char testArgv4[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "slave_area", "one", "get", "3", "0" };

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv1) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv1);
      ptImMxicExecuteCmd((sizeof(testArgv2) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv2);

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv3) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv3);
      ptImMxicExecuteCmd((sizeof(testArgv4) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv4);

      // タイマー停止
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
    }
    // マスタ設定.
    else if ( testno == 5 ) {
      // タイマー起動
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

      char testArgv1[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "master", "all", "set", "3"};
      char testArgv2[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "master", "all", "get", "3"};
      char testArgv3[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "master", "w", "set", "3", "0"};
      char testArgv4[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "master", "w", "get", "3"};
      char testArgv5[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "master", "r", "set", "3", "0"};
      char testArgv6[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "master", "r", "get", "3"};

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv1) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv1);
      ptImMxicExecuteCmd((sizeof(testArgv2) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv2);

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv3) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv3);
      ptImMxicExecuteCmd((sizeof(testArgv4) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv4);

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv5) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv5);
      ptImMxicExecuteCmd((sizeof(testArgv6) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv6);

      // タイマー停止
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
    }
    // レベル間優先順位制御.
    else if ( testno == 6 ) {
      // タイマー起動
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

      char testArgv1[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "pri", "slot", "all", "set", "3" };
      char testArgv2[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "pri", "slot", "all", "get", "3" };
      char testArgv3[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "pri", "slot", "one", "set", "3",
          "0", "0", "0", "0", "0", "0", "63" };
      char testArgv4[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "pri", "slot", "one", "get", "3",
          "0", "0", "0", "0"};

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv1) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv1);
      ptImMxicExecuteCmd((sizeof(testArgv2) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv2);

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv3) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv3);
      ptImMxicExecuteCmd((sizeof(testArgv4) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv4);

      // タイマー停止
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
    }
    // レベル内優先順位制御.
    else if ( testno == 7 ) {
      // タイマー起動
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

      char testArgv1[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "pri", "master", "set", "3", "1", "0" };
      char testArgv2[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "pri", "master", "get", "3", "1"};

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv1) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv1);
      ptImMxicExecuteCmd((sizeof(testArgv2) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv2);

      // タイマー停止
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
    }
    // スロットマスク制御.
    else if ( testno == 8 ) {
      // タイマー起動
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

      char testArgv1[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "mask", "slot", "set", "3", "0", "0",
          "0", "0", "1" };
      char testArgv2[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "mask", "slot", "get", "3", "0", "0",
          "0", "0"};

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv1) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv1);
      ptImMxicExecuteCmd((sizeof(testArgv2) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv2);

      // タイマー停止
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
    }
    // マスタ転送要求マスク制御.
    else if ( testno == 9 ) {
      // タイマー起動
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

      char testArgv1[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "mask", "master", "enable", "set", "3", "1",
          "0", "4" };
      char testArgv2[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "mask", "master", "enable", "get", "3", "1"};

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv1) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv1);
      ptImMxicExecuteCmd((sizeof(testArgv2) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv2);

      // タイマー停止
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
    }
    // マスタ転送要求マスク要因・対象・状態選択設定.
    else if ( testno == 10 ) {
      // タイマー起動
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

      char testArgv1[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "mask", "master", "factor", "set", "3",
          "0x1", "0", "1" };
      char testArgv2[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "mask", "master", "factor", "get", "3",
          "0x1", "0"};
      char testArgv3[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "mask", "master", "target", "set", "3",
          "0x2", "0", "1" };
      char testArgv4[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "mask", "master", "target", "get", "3",
          "0x2", "0"};
      char testArgv5[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "mask", "master", "select", "set", "3",
          "0x1", "1"};
      char testArgv6[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "mask", "master", "select", "get", "3",
          "0x1"};

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv1) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv1);
      ptImMxicExecuteCmd((sizeof(testArgv2) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv2);

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv3) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv3);
      ptImMxicExecuteCmd((sizeof(testArgv4) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv4);

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv5) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv5);
      ptImMxicExecuteCmd((sizeof(testArgv6) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv6);

      // タイマー停止
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
    }
    // マスタ転送要求トランザクション数マスク制御.
    else if ( testno == 11 ) {
      // タイマー起動
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

      char testArgv1[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "mask", "master", "trn", "set", "3",
          "0x1", "1" };
      char testArgv2[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "mask", "master", "trn", "get", "3", "0x1"};

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv1) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv1);
      ptImMxicExecuteCmd((sizeof(testArgv2) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv2);

      // タイマー停止
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
    }
    // マスタアクセスレベルポート設定.
    else if ( testno == 12 ) {
      // タイマー起動
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

      char testArgv1[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "levelport", "all",   "set", "3" };
      char testArgv2[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "levelport", "all",   "get", "3" };
      char testArgv3[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "levelport", "port",  "set", "3", "0", "0",
          "0x11", "0" };
      char testArgv4[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "levelport", "port",  "get", "3", "0", "0",
          "0x11"};
      char testArgv5[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "levelport", "level", "set", "3", "0", "0",
          "0x11", "0" };
      char testArgv6[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "levelport", "level", "get", "3", "0", "0",
          "0x11"};

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv1) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv1);
      ptImMxicExecuteCmd((sizeof(testArgv2) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv2);

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv3) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv3);
      ptImMxicExecuteCmd((sizeof(testArgv4) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv4);

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv5) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv5);
      ptImMxicExecuteCmd((sizeof(testArgv6) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv6);

      // タイマー停止
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
    }
    // マスタ出力ポート設定
    else if ( testno == 13 ) {
      // タイマー起動
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

      char testArgv1[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "port", "assign", "all", "set", "1"};
      char testArgv2[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "port", "assign", "all", "get"};
      char testArgv3[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "port", "assign", "one", "set", "0x40",
          "1" };
      char testArgv4[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "port", "assign", "one", "get", "0x40"};

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv1) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv1);
      ptImMxicExecuteCmd((sizeof(testArgv2) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv2);

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv3) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv3);
      ptImMxicExecuteCmd((sizeof(testArgv4) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv4);

      // タイマー停止
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
    }
    // アクセスモニタ
    else if ( testno == 14 ) {
      // タイマー起動
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

      char testArgv1[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ]  = { "immxic", "monitor", "acc", "param", "set", "0"};
      char testArgv2[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ]  = { "immxic", "monitor", "acc", "param",  "get", };
      char testArgv3[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ]  = { "immxic", "monitor", "start"};
      char testArgv4[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ]  = { "immxic", "monitor", "stop"};
      char testArgv5[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ]  = { "immxic", "monitor", "hist", "thstop", "set", "1" };
      char testArgv6[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ]  = { "immxic", "monitor", "hist", "thstop", "get"};
      char testArgv7[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ]  = { "immxic", "monitor", "hist", "all"};
      char testArgv8[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ]  = { "immxic", "monitor", "hist", "one", "0", "0", "0" };
      char testArgv9[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ]  = { "immxic", "monitor", "status", "slot", "all" };
      char testArgv10[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "monitor", "status", "slot", "3", "w", "0"};
      char testArgv11[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "monitor", "status", "slot", "3", "r", "0"};
      char testArgv12[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "monitor", "status", "slot", "wgr", "0"};
      char testArgv13[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "monitor", "status", "slot", "rgr", "0" };
      char testArgv14[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "monitor", "status", "master", "3" };
      char testArgv15[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "monitor", "acc", "result", "all" };
      char testArgv16[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "monitor", "acc", "result", "one", "0"};
      char testArgv17[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "monitor", "acc", "state" };

      ptImMxicExecuteCmd((sizeof(testArgv1)  / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv1);
      ptImMxicExecuteCmd((sizeof(testArgv2)  / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv2);
      ptImMxicExecuteCmd((sizeof(testArgv3)  / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv3);
      ptImMxicExecuteCmd((sizeof(testArgv4)  / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv4);
      ptImMxicExecuteCmd((sizeof(testArgv5)  / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv5);
      ptImMxicExecuteCmd((sizeof(testArgv6)  / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv6);
      ptImMxicExecuteCmd((sizeof(testArgv7)  / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv7);
      ptImMxicExecuteCmd((sizeof(testArgv8)  / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv8);
      ptImMxicExecuteCmd((sizeof(testArgv9)  / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv9);
      ptImMxicExecuteCmd((sizeof(testArgv10) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv10);
      ptImMxicExecuteCmd((sizeof(testArgv11) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv11);
      ptImMxicExecuteCmd((sizeof(testArgv12) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv12);
      ptImMxicExecuteCmd((sizeof(testArgv13) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv13);
      ptImMxicExecuteCmd((sizeof(testArgv14) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv14);
      ptImMxicExecuteCmd((sizeof(testArgv15) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv15);
      ptImMxicExecuteCmd((sizeof(testArgv16) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv16);
      ptImMxicExecuteCmd((sizeof(testArgv17) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv17);

      // タイマー停止
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
    }
    // メモリアクセス検出
    else if ( testno == 15 ) {
      // タイマー起動
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

      char testArgv1[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "memacc", "set", "3", "9", "0" };
      char testArgv2[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "memacc", "start", "3", "9"};
      char testArgv3[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "memacc", "get", "3" };
      char testArgv4[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "memacc", "stop", "3"};

      // set/start/get/stop
      ptImMxicExecuteCmd((sizeof(testArgv1) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv1);
      ptImMxicExecuteCmd((sizeof(testArgv2) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv2);
      ptImMxicExecuteCmd((sizeof(testArgv3) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv3);
      ptImMxicExecuteCmd((sizeof(testArgv4) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv4);

      // タイマー停止
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
    }
    // DecErr
    else if ( testno == 16 ) {
      // タイマー起動
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

      char testArgv1[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "dec_err", "set_int", "3", "1", "1", "1" };
      char testArgv2[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "dec_err", "get_int", "3"};
      char testArgv3[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "dec_err", "get", "3"};

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv1) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv1);
      ptImMxicExecuteCmd((sizeof(testArgv2) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv2);
      ptImMxicExecuteCmd((sizeof(testArgv3) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (char*)testArgv3);

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

PalladiumTestMxic* palladium_test_mxic_new(void)
{
	PalladiumTestMxic *self = k_object_new_with_private(PALLADIUM_TYPE_TEST_MXIC,
	                                                    sizeof(PalladiumTestMxicPrivate));
	return self;
}
