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
 * @file    palladium_test_shdr.c
 * @brief   SHDR test code on palladium
 * @note    None
 * @attention None
 *
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */

#include "im_shdr.h"
#include "ct_im_shdr.h"
#include "ddgic.h"
#include "ddtop.h"
#include "driver_common.h"
#include "palladium_test.h"
#include "palladiumtestshdr.h"

K_TYPE_DEFINE_WITH_PRIVATE(PalladiumTestShdr, palladium_test_shdr);
#define PALLADIUM_TEST_SHDR_GET_PRIVATE(o) \
  (K_OBJECT_GET_PRIVATE ((o), PalladiumTestShdrPrivate,PALLADIUM_TYPE_TEST_SHDR))

/*----------------------------------------------------------------------*/
/* Definition                             */
/*----------------------------------------------------------------------*/
#define PalladiumTestShdr_PT_SHDR_CMD_LEN     (20)

/*----------------------------------------------------------------------*/
/* Global Data                              */
/*----------------------------------------------------------------------*/
static kchar* S_G_CMD_ARGV[ PalladiumTestShdr_PT_SHDR_CMD_LEN ];

struct _PalladiumTestShdrPrivate
{
};

/*
 * DECLS
 */
static void ptImShdrEnableGic(void);
static void ptImShdrStartClock(void);
static void ptImShdrExecuteCmd(kint cmdArgc, kchar* cmdArgv);
static void ptImShdrRegisterDumpCmd();

static void palladium_test_shdr_constructor(PalladiumTestShdr *self)
{
//	PalladiumTestShdrPrivate *priv = PALLADIUM_TEST_SHDR_GET_PRIVATE(self);
}

static void palladium_test_shdr_destructor(PalladiumTestShdr *self)
{
//  PalladiumTestShdrPrivate *priv = PALLADIUM_TEST_SHDR_GET_PRIVATE(self);
}

/*
 * IMPL
 */
/*----------------------------------------------------------------------*/
/* Local Function                           */
/*----------------------------------------------------------------------*/
static void ptImShdrEnableGic(void)
{
  Dd_GIC_Ctrl(E_DD_GIC_INTID_TIMER_CH0_INT, 1, C_PRI30, 1);    // cpu=0, intid=118, enable, pri=30
  Dd_GIC_Ctrl(E_DD_GIC_INTID_SHDR_INT, 1, C_PRI30, 1);    // kint enable
  Dd_GIC_Ctrl(E_DD_GIC_INTID_SHDR_LINE_INT, 1, C_PRI30, 1);    // kint enable
}


static void ptImShdrStartClock(void)
{
  kuchar imShdrPclkCtrlCnt = 0;
  kuchar imShdrClkCtrlCnt = 0;
  kuchar imShdrIlkCtrlCnt = 0;
  kuchar imShdrHclkCtrlCnt = 0;

  Dd_Top_Start_Clock((kuchar*)&imShdrPclkCtrlCnt, &DdToptwo_GET_CLKSTOP7(), ~DdTopone_SHDRAP_BIT);

  Dd_Top_Start_Clock((kuchar*)&imShdrIlkCtrlCnt, &DdToptwo_GET_CLKSTOP7(), ~DdTopone_SHDRAX_BIT);

  Dd_Top_Start_Clock((kuchar*)&imShdrClkCtrlCnt, &DdToptwo_GET_CLKSTOP7(), ~DdTopone_SHDRCK_BIT);

  Dd_Top_Start_Clock((kuchar*)&imShdrHclkCtrlCnt, &DdToptwo_GET_CLKSTOP7(), ~DdTopone_SHDRAH_BIT);
}

static void ptImShdrExecuteCmd(kint cmdArgc, kchar* cmdArgv)
{
  kint32 j;
  kint32 cmdPos = 0;

  for(j = 0; j < cmdArgc; j++) {
    S_G_CMD_ARGV[ j ] = (cmdArgv + (cmdPos * PalladiumTestShdr_PT_SHDR_CMD_LEN));
    cmdPos++;
  }

  Ct_Im_SHDR_Main(cmdArgc, S_G_CMD_ARGV);
}

static void ptImShdrRegisterDumpCmd()
{
  kchar testArgv1[][ PalladiumTestShdr_PT_SHDR_CMD_LEN ] = { "imshdr", "get", "ctrl" };
  kchar testArgv2[][ PalladiumTestShdr_PT_SHDR_CMD_LEN ] = { "imshdr", "get", "pre" };
  kchar testArgv3[][ PalladiumTestShdr_PT_SHDR_CMD_LEN ] = { "imshdr", "get", "fmd" };
  kchar testArgv4[][ PalladiumTestShdr_PT_SHDR_CMD_LEN ] = { "imshdr", "get", "pmsk" };
  kchar testArgv5[][ PalladiumTestShdr_PT_SHDR_CMD_LEN ] = { "imshdr", "get", "spnr" };
  kchar testArgv6[][ PalladiumTestShdr_PT_SHDR_CMD_LEN ] = { "imshdr", "get", "mask" };
  kchar testArgv7[][ PalladiumTestShdr_PT_SHDR_CMD_LEN ] = { "imshdr", "get", "blend" };
  kchar testArgv8[][ PalladiumTestShdr_PT_SHDR_CMD_LEN ] = { "imshdr", "get", "post" };
  kchar testArgv9[][ PalladiumTestShdr_PT_SHDR_CMD_LEN ] = { "imshdr", "get", "resize" };
  kchar testArgv10[][ PalladiumTestShdr_PT_SHDR_CMD_LEN ] = { "imshdr", "get", "smc" };
  kchar testArgv11[][ PalladiumTestShdr_PT_SHDR_CMD_LEN ] = { "imshdr", "get", "dgr" };
  kchar testArgv12[][ PalladiumTestShdr_PT_SHDR_CMD_LEN ] = { "imshdr", "get", "dgg" };
  kchar testArgv13[][ PalladiumTestShdr_PT_SHDR_CMD_LEN ] = { "imshdr", "get", "dgb" };
  kchar testArgv14[][ PalladiumTestShdr_PT_SHDR_CMD_LEN ] = { "imshdr", "get", "axi" };
  kchar testArgv15[][ PalladiumTestShdr_PT_SHDR_CMD_LEN ] = { "imshdr", "get", "axires" };

  ptImShdrExecuteCmd((sizeof(testArgv1) / PalladiumTestShdr_PT_SHDR_CMD_LEN), (kchar*)testArgv1);
  ptImShdrExecuteCmd((sizeof(testArgv2) / PalladiumTestShdr_PT_SHDR_CMD_LEN), (kchar*)testArgv2);
  ptImShdrExecuteCmd((sizeof(testArgv3) / PalladiumTestShdr_PT_SHDR_CMD_LEN), (kchar*)testArgv3);
  ptImShdrExecuteCmd((sizeof(testArgv4) / PalladiumTestShdr_PT_SHDR_CMD_LEN), (kchar*)testArgv4);
  ptImShdrExecuteCmd((sizeof(testArgv5) / PalladiumTestShdr_PT_SHDR_CMD_LEN), (kchar*)testArgv5);
  ptImShdrExecuteCmd((sizeof(testArgv6) / PalladiumTestShdr_PT_SHDR_CMD_LEN), (kchar*)testArgv6);
  ptImShdrExecuteCmd((sizeof(testArgv7) / PalladiumTestShdr_PT_SHDR_CMD_LEN), (kchar*)testArgv7);
  ptImShdrExecuteCmd((sizeof(testArgv8) / PalladiumTestShdr_PT_SHDR_CMD_LEN), (kchar*)testArgv8);
  ptImShdrExecuteCmd((sizeof(testArgv9) / PalladiumTestShdr_PT_SHDR_CMD_LEN), (kchar*)testArgv9);
  ptImShdrExecuteCmd((sizeof(testArgv10) / PalladiumTestShdr_PT_SHDR_CMD_LEN), (kchar*)testArgv10);
  ptImShdrExecuteCmd((sizeof(testArgv11) / PalladiumTestShdr_PT_SHDR_CMD_LEN), (kchar*)testArgv11);
  ptImShdrExecuteCmd((sizeof(testArgv12) / PalladiumTestShdr_PT_SHDR_CMD_LEN), (kchar*)testArgv12);
  ptImShdrExecuteCmd((sizeof(testArgv13) / PalladiumTestShdr_PT_SHDR_CMD_LEN), (kchar*)testArgv13);
  ptImShdrExecuteCmd((sizeof(testArgv14) / PalladiumTestShdr_PT_SHDR_CMD_LEN), (kchar*)testArgv14);
  ptImShdrExecuteCmd((sizeof(testArgv15) / PalladiumTestShdr_PT_SHDR_CMD_LEN), (kchar*)testArgv15);
}

/*
 * PUBLIC
 */
/*----------------------------------------------------------------------*/
/* Global Function                            */
/*----------------------------------------------------------------------*/
/**
 * @brief   SHDR main code
 * @param   void
 * @return    void
 * @note    None
 * @attention None
 */
void palladium_test_shdr_im_main(PalladiumTestShdr *self)
{
  kuint32  testno;

  // 開始...
  Ddim_Print(("****** SHDR begin palladium_test_shdr_im_main\n"));

  // タイマー初期化
  Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_INIT);

  // テストパラメータ取得
  testno  = gDDIM_Info.com._6a;

  Ddim_Print(("****** Palladium Test %d begin\n", testno));

  ptImShdrEnableGic();
  ptImShdrStartClock();

  while(1) {

    // 3DNR w/o MC.
    if (testno == 1) {
      // 入力データ.
      Palladium_Set_In_Localstack(CtImShdr_D_IM_SHDR_IMG_MEM_IN_YCC_REF_ADDR_TOP,
                                   CtImShdr_D_IM_SHDR_IMG_MEM_4K2K_YCC_REF_U8_BYTES);
      Palladium_Set_In_Localstack(CtImShdr_D_IM_SHDR_IMG_MEM_IN_YCC_STD_ADDR_TOP,
                                   CtImShdr_D_IM_SHDR_IMG_MEM_4K2K_YCC_STD_U8_BYTES);

      // タイマー起動.
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_START);

      // テストコード起動.
      kchar testArgv1[][ PalladiumTestShdr_PT_SHDR_CMD_LEN ] = { "imshdr", "2", "1" };
      ptImShdrExecuteCmd((sizeof(testArgv1) / PalladiumTestShdr_PT_SHDR_CMD_LEN), (kchar*)testArgv1);

      // レジスタダンプ.
      ptImShdrRegisterDumpCmd();

      // タイマー停止.
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_END);

      // 出力ダンプ
      Palladium_Set_Out_Localstack(CtImShdr_D_IM_SHDR_IMG_MEM_OUT_HEVC_ADDR_TOP,
                                    CtImShdr_D_IM_SHDR_IMG_MEM_HEVC_U8_BYTES);
//      Palladium_Set_Out_Localstack(D_IM_SHDR_IMG_MEM_OUT_MEIN_ADDR_TOP,
      CtImShdr_D_IM_SHDR_IMG_MEM_MEIN_YCC_U8_BYTES);
      Palladium_Set_Out_Localstack(CtImShdr_D_IM_SHDR_IMG_MEM_OUT_RIB_FHD_ADDR_TOP,
                                    CtImShdr_D_IM_SHDR_IMG_MEM_RIB_FHD_U8_BYTES);
      Palladium_Set_Out_Localstack(CtImShdr_D_IM_SHDR_IMG_MEM_OUT_RIB_HD_ADDR_TOP,
                                    CtImShdr_D_IM_SHDR_IMG_MEM_RIB_HD_U8_BYTES);
      Palladium_Set_Out_Localstack(CtImShdr_D_IM_SHDR_IMG_MEM_OUT_DISP_HDMI_ADDR_TOP,
                                    CtImShdr_D_IM_SHDR_IMG_MEM_DISP_HDMI_YCC_U8_BYTES);
      Palladium_Set_Out_Localstack(CtImShdr_D_IM_SHDR_IMG_MEM_OUT_DISP_LCD_ADDR_TOP,
                                    CtImShdr_D_IM_SHDR_IMG_MEM_DISP_LCD_YCC_U8_BYTES);
    }
    // Video-HDR with MC.
    else if (testno == 3) {
      // 入力データ.
      Palladium_Set_In_Localstack(CtImShdr_D_IM_SHDR_IMG_MEM_IN_YCC_REF_ADDR_TOP,
                                   CtImShdr_D_IM_SHDR_IMG_MEM_4K2K_YCC_REF_U8_BYTES);
      Palladium_Set_In_Localstack(CtImShdr_D_IM_SHDR_IMG_MEM_IN_YCC_STD_ADDR_TOP,
                                   CtImShdr_D_IM_SHDR_IMG_MEM_4K2K_YCC_STD_U8_BYTES);

      // タイマー起動.
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_START);

      // テストコード起動.
      kchar testArgv1[][ PalladiumTestShdr_PT_SHDR_CMD_LEN ] = { "imshdr", "2", "3" };
      ptImShdrExecuteCmd((sizeof(testArgv1) / PalladiumTestShdr_PT_SHDR_CMD_LEN), (kchar*)testArgv1);

      // レジスタダンプ.
      ptImShdrRegisterDumpCmd();

      // タイマー停止.
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_END);

      // 出力ダンプ
      Palladium_Set_Out_Localstack(CtImShdr_D_IM_SHDR_IMG_MEM_OUT_HEVC_ADDR_TOP,
                                    CtImShdr_D_IM_SHDR_IMG_MEM_HEVC_U8_BYTES);
//      Palladium_Set_Out_Localstack(D_IM_SHDR_IMG_MEM_OUT_MEIN_ADDR_TOP,
      CtImShdr_D_IM_SHDR_IMG_MEM_MEIN_YCC_U8_BYTES);
      Palladium_Set_Out_Localstack(CtImShdr_D_IM_SHDR_IMG_MEM_OUT_RIB_FHD_ADDR_TOP,
                                    CtImShdr_D_IM_SHDR_IMG_MEM_RIB_FHD_U8_BYTES);
      Palladium_Set_Out_Localstack(CtImShdr_D_IM_SHDR_IMG_MEM_OUT_RIB_HD_ADDR_TOP,
                                    CtImShdr_D_IM_SHDR_IMG_MEM_RIB_HD_U8_BYTES);
      Palladium_Set_Out_Localstack(CtImShdr_D_IM_SHDR_IMG_MEM_OUT_DISP_HDMI_ADDR_TOP,
                                    CtImShdr_D_IM_SHDR_IMG_MEM_DISP_HDMI_YCC_U8_BYTES);
      Palladium_Set_Out_Localstack(CtImShdr_D_IM_SHDR_IMG_MEM_OUT_DISP_LCD_ADDR_TOP,
                                    CtImShdr_D_IM_SHDR_IMG_MEM_DISP_LCD_YCC_U8_BYTES);
    }
    // Bypass-YCC.
    else if (testno == 5) {
      // 入力データ.
      Palladium_Set_In_Localstack(CtImShdr_D_IM_SHDR_IMG_MEM_IN_YCC_REF_ADDR_TOP,
                                   CtImShdr_D_IM_SHDR_IMG_MEM_4K2K_YCC_REF_U8_BYTES);

      // タイマー起動.
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_START);

      // テストコード起動.
      kchar testArgv1[][ PalladiumTestShdr_PT_SHDR_CMD_LEN ] = { "imshdr", "2", "5" };
      ptImShdrExecuteCmd((sizeof(testArgv1) / PalladiumTestShdr_PT_SHDR_CMD_LEN), (kchar*)testArgv1);

      // レジスタダンプ.
      ptImShdrRegisterDumpCmd();

      // タイマー停止.
      Palladium_Timer(P_TIMER_ID_COMMON0, P_TIMER_END);

      // 出力ダンプ
      Palladium_Set_Out_Localstack(CtImShdr_D_IM_SHDR_IMG_MEM_OUT_HEVC_ADDR_TOP,
                                    CtImShdr_D_IM_SHDR_IMG_MEM_HEVC_U8_BYTES);
//      Palladium_Set_Out_Localstack(D_IM_SHDR_IMG_MEM_OUT_MEIN_ADDR_TOP,
      CtImShdr_D_IM_SHDR_IMG_MEM_MEIN_YCC_U8_BYTES);
      Palladium_Set_Out_Localstack(CtImShdr_D_IM_SHDR_IMG_MEM_OUT_RIB_FHD_ADDR_TOP,
                                    CtImShdr_D_IM_SHDR_IMG_MEM_RIB_FHD_U8_BYTES);
      Palladium_Set_Out_Localstack(CtImShdr_D_IM_SHDR_IMG_MEM_OUT_RIB_HD_ADDR_TOP,
                                    CtImShdr_D_IM_SHDR_IMG_MEM_RIB_HD_U8_BYTES);
      Palladium_Set_Out_Localstack(CtImShdr_D_IM_SHDR_IMG_MEM_OUT_DISP_HDMI_ADDR_TOP,
                                    CtImShdr_D_IM_SHDR_IMG_MEM_DISP_HDMI_YCC_U8_BYTES);
      Palladium_Set_Out_Localstack(CtImShdr_D_IM_SHDR_IMG_MEM_OUT_DISP_LCD_ADDR_TOP,
                                    CtImShdr_D_IM_SHDR_IMG_MEM_DISP_LCD_YCC_U8_BYTES);
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

PalladiumTestShdr* palladium_test_shdr_new(void)
{
	PalladiumTestShdr *self = k_object_new_with_private(PALLADIUM_TYPE_TEST_SHDR,
	                                                    sizeof(PalladiumTestShdrPrivate));
	return self;
}
