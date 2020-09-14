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
#include "ddgic.h"
#include "ddtop.h"
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
static kchar* S_G_CMD_ARGV[ PalladiumTestMxic_PT_MXIC_CMD_LEN ];

struct _PalladiumTestMxicPrivate
{
};

/*
 * DECLS
 */
static void ptImMxicEnableGic(void);
static void ptImMxicStartClock(void);
static void ptImMxicExecuteCmd(kint cmdArgc, kchar* cmdArgv);

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
static void ptImMxicEnableGic(void)
{
  Dd_GIC_Ctrl(E_DD_GIC_INTID_TIMER_CH0_INT,  1, C_PRI30, 1);   // cpu=0, intid=118, enable, pri=30
  Dd_GIC_Ctrl(E_DD_GIC_INTID_MXIC_UNIT0_INT, 1, C_PRI30, 1);   // kint enable
  Dd_GIC_Ctrl(E_DD_GIC_INTID_MXIC_UNIT1_INT, 1, C_PRI30, 1);   // kint enable
  Dd_GIC_Ctrl(E_DD_GIC_INTID_MXIC_UNIT2_INT, 1, C_PRI30, 1);   // kint enable
  Dd_GIC_Ctrl(E_DD_GIC_INTID_MXIC_UNIT3_INT, 1, C_PRI30, 1);   // kint enable
  Dd_GIC_Ctrl(E_DD_GIC_INTID_MXIC_UNIT4_INT, 1, C_PRI30, 1);   // kint enable
  Dd_GIC_Ctrl(E_DD_GIC_INTID_MXIC_UNIT5_INT, 1, C_PRI30, 1);   // kint enable
  Dd_GIC_Ctrl(E_DD_GIC_INTID_MXIC_UNIT6_INT, 1, C_PRI30, 1);   // kint enable
}


static void ptImMxicStartClock(void)
{
  kuchar imMxicPclkCtrlCnt[ 7 ] = { 0, 0, 0, 0, 0, 0, 0 };
  kuchar imMxicHclkCtrlCnt[ 3 ] = { 0, 0, 0 };

  Dd_Top_Start_Clock((kuchar*)&imMxicPclkCtrlCnt[ 0 ], &Dd_Top_Get_CLKSTOP5(), ~DdTopone_MICAP0_BIT);
  Dd_Top_Start_Clock((kuchar*)&imMxicPclkCtrlCnt[ 1 ], &Dd_Top_Get_CLKSTOP5(), ~DdTopone_MICAP1_BIT);
  Dd_Top_Start_Clock((kuchar*)&imMxicPclkCtrlCnt[ 2 ], &Dd_Top_Get_CLKSTOP5(), ~DdTopone_MICAP2_BIT);
  Dd_Top_Start_Clock((kuchar*)&imMxicPclkCtrlCnt[ 3 ], &Dd_Top_Get_CLKSTOP5(), ~DdTopone_MICAP3_BIT);
  Dd_Top_Start_Clock((kuchar*)&imMxicPclkCtrlCnt[ 4 ], &Dd_Top_Get_CLKSTOP5(), ~DdTopone_MICAP4_BIT);
  Dd_Top_Start_Clock((kuchar*)&imMxicPclkCtrlCnt[ 5 ], &Dd_Top_Get_CLKSTOP5(), ~DdTopone_MICAP5_BIT);
  Dd_Top_Start_Clock((kuchar*)&imMxicPclkCtrlCnt[ 6 ], &Dd_Top_Get_CLKSTOP5(), ~DdTopone_MICAP6_BIT);

  Dd_Top_Start_Clock((kuchar*)&imMxicHclkCtrlCnt[ 0 ], &Dd_Top_Get_CLKSTOP6(), ~DdTopone_MICAH1_BIT);
  Dd_Top_Start_Clock((kuchar*)&imMxicHclkCtrlCnt[ 1 ], &Dd_Top_Get_CLKSTOP6(), ~DdTopone_MICAH2_BIT);
  Dd_Top_Start_Clock((kuchar*)&imMxicHclkCtrlCnt[ 2 ], &Dd_Top_Get_CLKSTOP6(), ~DdTopone_MICAH3_BIT);
}

static void ptImMxicExecuteCmd(kint cmdArgc, kchar* cmdArgv)
{
  kint32 j;
  kint32 cmdPos = 0;

  if(cmdArgc > PalladiumTestMxic_PT_MXIC_CMD_LEN) {
    cmdArgc = PalladiumTestMxic_PT_MXIC_CMD_LEN;
  }
  for(j = 0; j < cmdArgc; j++) {
    S_G_CMD_ARGV[ j ] = (cmdArgv + (cmdPos * PalladiumTestMxic_PT_MXIC_CMD_LEN));
    cmdPos++;
  }

  Ct_Im_MXIC_Main(cmdArgc, S_G_CMD_ARGV);
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
void palladium_test_mxic_im_main(PalladiumTestMxic *self)
{
  kuint32  testno;

  // 開始...
  Ddim_Print(("****** MXIC begin palladium_test_mxic_im_main\n"));

  // タイマー初期化
  Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_INIT);

  // テストパラメータ取得
  testno  = gDDIM_Info.com._6a;

  Ddim_Print(("****** Palladium Test %d begin\n", testno));

  ptImMxicEnableGic();
  ptImMxicStartClock();

  while(1) {

    // 初期化.
    if (testno == 0) {
      // タイマー起動
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_START);

      kchar testArgv1[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "init", "3"};
      kchar testArgv2[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "master", "all",  "get", "3"};
      kchar testArgv3[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "pri", "slot", "all", "get", "3" };
      kchar testArgv4[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "levelport", "all", "get", "3"};

      ptImMxicExecuteCmd((sizeof(testArgv1) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv1);
      ptImMxicExecuteCmd((sizeof(testArgv2) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv2);
      ptImMxicExecuteCmd((sizeof(testArgv3) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv3);
      ptImMxicExecuteCmd((sizeof(testArgv4) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv4);

      // タイマー停止
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_END);
    }
    // コンフィグレーション起動.
    else if (testno == 1) {
      // タイマー起動
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_START);

      kchar testArgv1[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "start", "3", "1", "1", "1", "1",
          "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1" };
      kchar testArgv2[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "start", "3", "0", "0", "0", "0",
          "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0" };

      // enable/disable
      ptImMxicExecuteCmd((sizeof(testArgv1) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv1);
      ptImMxicExecuteCmd((sizeof(testArgv2) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv2);

      // タイマー停止
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_END);
    }
    // クロック供給制御.
    else if (testno == 2) {
      // タイマー起動
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_START);

      kchar testArgv1[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "clock", "set", "3", "1", "1", "1", "1",
          "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1" };
      kchar testArgv2[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "clock", "set", "3", "0", "0", "0", "0",
          "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0" };
      kchar testArgv3[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "clock", "get", "3" };

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv1) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv1);
      ptImMxicExecuteCmd((sizeof(testArgv3) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv3);

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv2) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv2);
      ptImMxicExecuteCmd((sizeof(testArgv3) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv3);

      // タイマー停止
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_END);
    }
    // acceptance capability設定.
    else if (testno == 3) {
      // タイマー起動
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_START);

      kchar testArgv1[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "acc_capa", "all",   "set", "1", "1" };
      kchar testArgv2[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "acc_capa", "all",   "get", "1"      };
      kchar testArgv3[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "acc_capa", "slave", "set", "1", "0",
          "3", "3", "8"};
      kchar testArgv4[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "acc_capa", "slave", "get", "1", "0",
          "3", "3"};
      kchar testArgv5[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "acc_capa", "group", "set",  "0",
          "7", "1", "1"};
      kchar testArgv6[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "acc_capa", "group", "get", "0",
          "7", "1"};

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv1) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv1);
      ptImMxicExecuteCmd((sizeof(testArgv2) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv2);

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv3) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv3);
      ptImMxicExecuteCmd((sizeof(testArgv4) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv4);

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv5) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv5);
      ptImMxicExecuteCmd((sizeof(testArgv6) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv6);

      // タイマー停止
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_END);
    }
    // スレーブ領域設定.
    else if (testno == 4) {
      // タイマー起動
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_START);

      kchar testArgv1[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "slave_area", "all", "set", "3",
          "0x20000000", "0x40000000", "0x20000000", "0x60000000", "0x20000000", "0x80000000", "0x20000000",
          "0xA0000000" };
      kchar testArgv2[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "slave_area", "all", "get", "3", };
      kchar testArgv3[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "slave_area", "one", "set", "3", "0",
          "0x40000000", "0x40000000" };
      kchar testArgv4[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "slave_area", "one", "get", "3", "0" };

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv1) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv1);
      ptImMxicExecuteCmd((sizeof(testArgv2) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv2);

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv3) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv3);
      ptImMxicExecuteCmd((sizeof(testArgv4) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv4);

      // タイマー停止
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_END);
    }
    // マスタ設定.
    else if (testno == 5) {
      // タイマー起動
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_START);

      kchar testArgv1[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "master", "all", "set", "3"};
      kchar testArgv2[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "master", "all", "get", "3"};
      kchar testArgv3[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "master", "w", "set", "3", "0"};
      kchar testArgv4[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "master", "w", "get", "3"};
      kchar testArgv5[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "master", "r", "set", "3", "0"};
      kchar testArgv6[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "master", "r", "get", "3"};

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv1) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv1);
      ptImMxicExecuteCmd((sizeof(testArgv2) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv2);

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv3) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv3);
      ptImMxicExecuteCmd((sizeof(testArgv4) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv4);

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv5) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv5);
      ptImMxicExecuteCmd((sizeof(testArgv6) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv6);

      // タイマー停止
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_END);
    }
    // レベル間優先順位制御.
    else if (testno == 6) {
      // タイマー起動
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_START);

      kchar testArgv1[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "pri", "slot", "all", "set", "3" };
      kchar testArgv2[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "pri", "slot", "all", "get", "3" };
      kchar testArgv3[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "pri", "slot", "one", "set", "3",
          "0", "0", "0", "0", "0", "0", "63" };
      kchar testArgv4[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "pri", "slot", "one", "get", "3",
          "0", "0", "0", "0"};

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv1) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv1);
      ptImMxicExecuteCmd((sizeof(testArgv2) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv2);

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv3) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv3);
      ptImMxicExecuteCmd((sizeof(testArgv4) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv4);

      // タイマー停止
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_END);
    }
    // レベル内優先順位制御.
    else if (testno == 7) {
      // タイマー起動
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_START);

      kchar testArgv1[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "pri", "master", "set", "3", "1", "0" };
      kchar testArgv2[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "pri", "master", "get", "3", "1"};

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv1) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv1);
      ptImMxicExecuteCmd((sizeof(testArgv2) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv2);

      // タイマー停止
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_END);
    }
    // スロットマスク制御.
    else if (testno == 8) {
      // タイマー起動
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_START);

      kchar testArgv1[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "mask", "slot", "set", "3", "0", "0",
          "0", "0", "1" };
      kchar testArgv2[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "mask", "slot", "get", "3", "0", "0",
          "0", "0"};

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv1) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv1);
      ptImMxicExecuteCmd((sizeof(testArgv2) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv2);

      // タイマー停止
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_END);
    }
    // マスタ転送要求マスク制御.
    else if (testno == 9) {
      // タイマー起動
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_START);

      kchar testArgv1[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "mask", "master", "enable", "set", "3", "1",
          "0", "4" };
      kchar testArgv2[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "mask", "master", "enable", "get", "3", "1"};

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv1) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv1);
      ptImMxicExecuteCmd((sizeof(testArgv2) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv2);

      // タイマー停止
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_END);
    }
    // マスタ転送要求マスク要因・対象・状態選択設定.
    else if (testno == 10) {
      // タイマー起動
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_START);

      kchar testArgv1[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "mask", "master", "factor", "set", "3",
          "0x1", "0", "1" };
      kchar testArgv2[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "mask", "master", "factor", "get", "3",
          "0x1", "0"};
      kchar testArgv3[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "mask", "master", "target", "set", "3",
          "0x2", "0", "1" };
      kchar testArgv4[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "mask", "master", "target", "get", "3",
          "0x2", "0"};
      kchar testArgv5[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "mask", "master", "select", "set", "3",
          "0x1", "1"};
      kchar testArgv6[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "mask", "master", "select", "get", "3",
          "0x1"};

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv1) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv1);
      ptImMxicExecuteCmd((sizeof(testArgv2) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv2);

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv3) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv3);
      ptImMxicExecuteCmd((sizeof(testArgv4) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv4);

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv5) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv5);
      ptImMxicExecuteCmd((sizeof(testArgv6) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv6);

      // タイマー停止
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_END);
    }
    // マスタ転送要求トランザクション数マスク制御.
    else if (testno == 11) {
      // タイマー起動
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_START);

      kchar testArgv1[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "mask", "master", "trn", "set", "3",
          "0x1", "1" };
      kchar testArgv2[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "mask", "master", "trn", "get", "3", "0x1"};

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv1) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv1);
      ptImMxicExecuteCmd((sizeof(testArgv2) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv2);

      // タイマー停止
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_END);
    }
    // マスタアクセスレベルポート設定.
    else if (testno == 12) {
      // タイマー起動
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_START);

      kchar testArgv1[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "levelport", "all",   "set", "3" };
      kchar testArgv2[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "levelport", "all",   "get", "3" };
      kchar testArgv3[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "levelport", "port",  "set", "3", "0", "0",
          "0x11", "0" };
      kchar testArgv4[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "levelport", "port",  "get", "3", "0", "0",
          "0x11"};
      kchar testArgv5[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "levelport", "level", "set", "3", "0", "0",
          "0x11", "0" };
      kchar testArgv6[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "levelport", "level", "get", "3", "0", "0",
          "0x11"};

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv1) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv1);
      ptImMxicExecuteCmd((sizeof(testArgv2) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv2);

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv3) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv3);
      ptImMxicExecuteCmd((sizeof(testArgv4) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv4);

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv5) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv5);
      ptImMxicExecuteCmd((sizeof(testArgv6) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv6);

      // タイマー停止
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_END);
    }
    // マスタ出力ポート設定
    else if (testno == 13) {
      // タイマー起動
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_START);

      kchar testArgv1[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "port", "assign", "all", "set", "1"};
      kchar testArgv2[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "port", "assign", "all", "get"};
      kchar testArgv3[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "port", "assign", "one", "set", "0x40",
          "1" };
      kchar testArgv4[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "port", "assign", "one", "get", "0x40"};

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv1) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv1);
      ptImMxicExecuteCmd((sizeof(testArgv2) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv2);

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv3) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv3);
      ptImMxicExecuteCmd((sizeof(testArgv4) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv4);

      // タイマー停止
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_END);
    }
    // アクセスモニタ
    else if (testno == 14) {
      // タイマー起動
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_START);

      kchar testArgv1[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ]  = { "immxic", "monitor", "acc", "param", "set", "0"};
      kchar testArgv2[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ]  = { "immxic", "monitor", "acc", "param",  "get", };
      kchar testArgv3[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ]  = { "immxic", "monitor", "start"};
      kchar testArgv4[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ]  = { "immxic", "monitor", "stop"};
      kchar testArgv5[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ]  = { "immxic", "monitor", "hist", "thstop", "set", "1" };
      kchar testArgv6[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ]  = { "immxic", "monitor", "hist", "thstop", "get"};
      kchar testArgv7[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ]  = { "immxic", "monitor", "hist", "all"};
      kchar testArgv8[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ]  = { "immxic", "monitor", "hist", "one", "0", "0", "0" };
      kchar testArgv9[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ]  = { "immxic", "monitor", "status", "slot", "all" };
      kchar testArgv10[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "monitor", "status", "slot", "3", "w", "0"};
      kchar testArgv11[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "monitor", "status", "slot", "3", "r", "0"};
      kchar testArgv12[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "monitor", "status", "slot", "wgr", "0"};
      kchar testArgv13[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "monitor", "status", "slot", "rgr", "0" };
      kchar testArgv14[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "monitor", "status", "master", "3" };
      kchar testArgv15[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "monitor", "acc", "result", "all" };
      kchar testArgv16[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "monitor", "acc", "result", "one", "0"};
      kchar testArgv17[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "monitor", "acc", "state" };

      ptImMxicExecuteCmd((sizeof(testArgv1)  / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv1);
      ptImMxicExecuteCmd((sizeof(testArgv2)  / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv2);
      ptImMxicExecuteCmd((sizeof(testArgv3)  / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv3);
      ptImMxicExecuteCmd((sizeof(testArgv4)  / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv4);
      ptImMxicExecuteCmd((sizeof(testArgv5)  / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv5);
      ptImMxicExecuteCmd((sizeof(testArgv6)  / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv6);
      ptImMxicExecuteCmd((sizeof(testArgv7)  / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv7);
      ptImMxicExecuteCmd((sizeof(testArgv8)  / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv8);
      ptImMxicExecuteCmd((sizeof(testArgv9)  / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv9);
      ptImMxicExecuteCmd((sizeof(testArgv10) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv10);
      ptImMxicExecuteCmd((sizeof(testArgv11) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv11);
      ptImMxicExecuteCmd((sizeof(testArgv12) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv12);
      ptImMxicExecuteCmd((sizeof(testArgv13) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv13);
      ptImMxicExecuteCmd((sizeof(testArgv14) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv14);
      ptImMxicExecuteCmd((sizeof(testArgv15) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv15);
      ptImMxicExecuteCmd((sizeof(testArgv16) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv16);
      ptImMxicExecuteCmd((sizeof(testArgv17) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv17);

      // タイマー停止
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_END);
    }
    // メモリアクセス検出
    else if (testno == 15) {
      // タイマー起動
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_START);

      kchar testArgv1[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "memacc", "set", "3", "9", "0" };
      kchar testArgv2[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "memacc", "start", "3", "9"};
      kchar testArgv3[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "memacc", "get", "3" };
      kchar testArgv4[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "memacc", "stop", "3"};

      // set/start/get/stop
      ptImMxicExecuteCmd((sizeof(testArgv1) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv1);
      ptImMxicExecuteCmd((sizeof(testArgv2) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv2);
      ptImMxicExecuteCmd((sizeof(testArgv3) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv3);
      ptImMxicExecuteCmd((sizeof(testArgv4) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv4);

      // タイマー停止
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_END);
    }
    // DecErr
    else if (testno == 16) {
      // タイマー起動
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_START);

      kchar testArgv1[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "dec_err", "set_int", "3", "1", "1", "1" };
      kchar testArgv2[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "dec_err", "get_int", "3"};
      kchar testArgv3[][ PalladiumTestMxic_PT_MXIC_CMD_LEN ] = { "immxic", "dec_err", "get", "3"};

      // set/get
      ptImMxicExecuteCmd((sizeof(testArgv1) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv1);
      ptImMxicExecuteCmd((sizeof(testArgv2) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv2);
      ptImMxicExecuteCmd((sizeof(testArgv3) / PalladiumTestMxic_PT_MXIC_CMD_LEN), (kchar*)testArgv3);

      // タイマー停止
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_END);
    }
    else {
      Ddim_Print(("*** RS Parameter Error\n"));
    }

    break;
  }

  // タイマーログ出力
  Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_PRINT);

  Ddim_Print(("****** Palladium Test %d end\n", testno));

  // Force stop
  Palladium_Force_Stop();
}

PalladiumTestMxic* palladium_test_mxic_new(void)
{
	PalladiumTestMxic *self = k_object_new_with_private(PALLADIUM_TYPE_TEST_MXIC,
	                                                    sizeof(PalladiumTestMxicPrivate));
	return self;
}
