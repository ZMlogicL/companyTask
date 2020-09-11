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
#include "dd_gic.h"
#include "dd_top.h"
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
static char* S_G_CMD_ARGV[ PalladiumTestShdr_PT_SHDR_CMD_LEN ];

struct _PalladiumTestShdrPrivate
{
};

/*
 * DECLS
 */
static VOID ptImShdrEnableGic( VOID );
static VOID ptImShdrStartClock( VOID );
static void ptImShdrExecuteCmd( int cmdArgc, char* cmdArgv );
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
static VOID ptImShdrEnableGic( VOID )
{
  Dd_GIC_Ctrl( E_DD_GIC_INTID_TIMER_CH0_INT, 1, D_DD_GIC_PRI30, 1 );    // cpu=0, intid=118, enable, pri=30
  Dd_GIC_Ctrl( E_DD_GIC_INTID_SHDR_INT, 1, D_DD_GIC_PRI30, 1 );    // int enable
  Dd_GIC_Ctrl( E_DD_GIC_INTID_SHDR_LINE_INT, 1, D_DD_GIC_PRI30, 1 );    // int enable
}


static VOID ptImShdrStartClock( VOID )
{
  UCHAR imShdrPclkCtrlCnt = 0;
  UCHAR imShdrClkCtrlCnt = 0;
  UCHAR imShdrIlkCtrlCnt = 0;
  UCHAR imShdrHclkCtrlCnt = 0;

  Dd_Top_Start_Clock( (UCHAR*)&imShdrPclkCtrlCnt, &Dd_Top_Get_CLKSTOP7(), ~D_DD_TOP_SHDRAP_BIT );

  Dd_Top_Start_Clock( (UCHAR*)&imShdrIlkCtrlCnt, &Dd_Top_Get_CLKSTOP7(), ~D_DD_TOP_SHDRAX_BIT );

  Dd_Top_Start_Clock( (UCHAR*)&imShdrClkCtrlCnt, &Dd_Top_Get_CLKSTOP7(), ~D_DD_TOP_SHDRCK_BIT );

  Dd_Top_Start_Clock( (UCHAR*)&imShdrHclkCtrlCnt, &Dd_Top_Get_CLKSTOP7(), ~D_DD_TOP_SHDRAH_BIT );
}

static void ptImShdrExecuteCmd( int cmdArgc, char* cmdArgv )
{
  INT32 j;
  INT32 cmdPos = 0;

  for( j = 0; j < cmdArgc; j++ ) {
    S_G_CMD_ARGV[ j ] = ( cmdArgv + ( cmdPos * PalladiumTestShdr_PT_SHDR_CMD_LEN ) );
    cmdPos++;
  }

  Ct_Im_SHDR_Main( cmdArgc, S_G_CMD_ARGV );
}

static void ptImShdrRegisterDumpCmd()
{
  char testArgv1[][ PalladiumTestShdr_PT_SHDR_CMD_LEN ] = { "imshdr", "get", "ctrl" };
  char testArgv2[][ PalladiumTestShdr_PT_SHDR_CMD_LEN ] = { "imshdr", "get", "pre" };
  char testArgv3[][ PalladiumTestShdr_PT_SHDR_CMD_LEN ] = { "imshdr", "get", "fmd" };
  char testArgv4[][ PalladiumTestShdr_PT_SHDR_CMD_LEN ] = { "imshdr", "get", "pmsk" };
  char testArgv5[][ PalladiumTestShdr_PT_SHDR_CMD_LEN ] = { "imshdr", "get", "spnr" };
  char testArgv6[][ PalladiumTestShdr_PT_SHDR_CMD_LEN ] = { "imshdr", "get", "mask" };
  char testArgv7[][ PalladiumTestShdr_PT_SHDR_CMD_LEN ] = { "imshdr", "get", "blend" };
  char testArgv8[][ PalladiumTestShdr_PT_SHDR_CMD_LEN ] = { "imshdr", "get", "post" };
  char testArgv9[][ PalladiumTestShdr_PT_SHDR_CMD_LEN ] = { "imshdr", "get", "resize" };
  char testArgv10[][ PalladiumTestShdr_PT_SHDR_CMD_LEN ] = { "imshdr", "get", "smc" };
  char testArgv11[][ PalladiumTestShdr_PT_SHDR_CMD_LEN ] = { "imshdr", "get", "dgr" };
  char testArgv12[][ PalladiumTestShdr_PT_SHDR_CMD_LEN ] = { "imshdr", "get", "dgg" };
  char testArgv13[][ PalladiumTestShdr_PT_SHDR_CMD_LEN ] = { "imshdr", "get", "dgb" };
  char testArgv14[][ PalladiumTestShdr_PT_SHDR_CMD_LEN ] = { "imshdr", "get", "axi" };
  char testArgv15[][ PalladiumTestShdr_PT_SHDR_CMD_LEN ] = { "imshdr", "get", "axires" };

  ptImShdrExecuteCmd((sizeof(testArgv1) / PalladiumTestShdr_PT_SHDR_CMD_LEN), (char*)testArgv1);
  ptImShdrExecuteCmd((sizeof(testArgv2) / PalladiumTestShdr_PT_SHDR_CMD_LEN), (char*)testArgv2);
  ptImShdrExecuteCmd((sizeof(testArgv3) / PalladiumTestShdr_PT_SHDR_CMD_LEN), (char*)testArgv3);
  ptImShdrExecuteCmd((sizeof(testArgv4) / PalladiumTestShdr_PT_SHDR_CMD_LEN), (char*)testArgv4);
  ptImShdrExecuteCmd((sizeof(testArgv5) / PalladiumTestShdr_PT_SHDR_CMD_LEN), (char*)testArgv5);
  ptImShdrExecuteCmd((sizeof(testArgv6) / PalladiumTestShdr_PT_SHDR_CMD_LEN), (char*)testArgv6);
  ptImShdrExecuteCmd((sizeof(testArgv7) / PalladiumTestShdr_PT_SHDR_CMD_LEN), (char*)testArgv7);
  ptImShdrExecuteCmd((sizeof(testArgv8) / PalladiumTestShdr_PT_SHDR_CMD_LEN), (char*)testArgv8);
  ptImShdrExecuteCmd((sizeof(testArgv9) / PalladiumTestShdr_PT_SHDR_CMD_LEN), (char*)testArgv9);
  ptImShdrExecuteCmd((sizeof(testArgv10) / PalladiumTestShdr_PT_SHDR_CMD_LEN), (char*)testArgv10);
  ptImShdrExecuteCmd((sizeof(testArgv11) / PalladiumTestShdr_PT_SHDR_CMD_LEN), (char*)testArgv11);
  ptImShdrExecuteCmd((sizeof(testArgv12) / PalladiumTestShdr_PT_SHDR_CMD_LEN), (char*)testArgv12);
  ptImShdrExecuteCmd((sizeof(testArgv13) / PalladiumTestShdr_PT_SHDR_CMD_LEN), (char*)testArgv13);
  ptImShdrExecuteCmd((sizeof(testArgv14) / PalladiumTestShdr_PT_SHDR_CMD_LEN), (char*)testArgv14);
  ptImShdrExecuteCmd((sizeof(testArgv15) / PalladiumTestShdr_PT_SHDR_CMD_LEN), (char*)testArgv15);
}

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
void palladium_test_shdr_im_main( void )
{
  UINT32  testno;

  // 開始...
  Ddim_Print(( "****** SHDR begin palladium_test_shdr_im_main\n" ));

  // タイマー初期化
  Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_INIT );

  // テストパラメータ取得
  testno  = gDDIM_Info.com._6a;

  Ddim_Print(( "****** Palladium Test %d begin\n", testno ));

  ptImShdrEnableGic();
  ptImShdrStartClock();

  while( 1 ) {

    // 3DNR w/o MC.
    if ( testno == 1 ) {
      // 入力データ.
      Palladium_Set_In_Localstack( D_IM_SHDR_IMG_MEM_IN_YCC_REF_ADDR_TOP,
                                   D_IM_SHDR_IMG_MEM_4K2K_YCC_REF_U8_BYTES );
      Palladium_Set_In_Localstack( D_IM_SHDR_IMG_MEM_IN_YCC_STD_ADDR_TOP,
                                   D_IM_SHDR_IMG_MEM_4K2K_YCC_STD_U8_BYTES );

      // タイマー起動.
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

      // テストコード起動.
      char testArgv1[][ PalladiumTestShdr_PT_SHDR_CMD_LEN ] = { "imshdr", "2", "1" };
      ptImShdrExecuteCmd((sizeof(testArgv1) / PalladiumTestShdr_PT_SHDR_CMD_LEN), (char*)testArgv1);

      // レジスタダンプ.
      ptImShdrRegisterDumpCmd();

      // タイマー停止.
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

      // 出力ダンプ
      Palladium_Set_Out_Localstack( D_IM_SHDR_IMG_MEM_OUT_HEVC_ADDR_TOP,
                                    D_IM_SHDR_IMG_MEM_HEVC_U8_BYTES );
//      Palladium_Set_Out_Localstack( D_IM_SHDR_IMG_MEM_OUT_MEIN_ADDR_TOP,
      D_IM_SHDR_IMG_MEM_MEIN_YCC_U8_BYTES );
      Palladium_Set_Out_Localstack( D_IM_SHDR_IMG_MEM_OUT_RIB_FHD_ADDR_TOP,
                                    D_IM_SHDR_IMG_MEM_RIB_FHD_U8_BYTES );
      Palladium_Set_Out_Localstack( D_IM_SHDR_IMG_MEM_OUT_RIB_HD_ADDR_TOP,
                                    D_IM_SHDR_IMG_MEM_RIB_HD_U8_BYTES );
      Palladium_Set_Out_Localstack( D_IM_SHDR_IMG_MEM_OUT_DISP_HDMI_ADDR_TOP,
                                    D_IM_SHDR_IMG_MEM_DISP_HDMI_YCC_U8_BYTES );
      Palladium_Set_Out_Localstack( D_IM_SHDR_IMG_MEM_OUT_DISP_LCD_ADDR_TOP,
                                    D_IM_SHDR_IMG_MEM_DISP_LCD_YCC_U8_BYTES );
    }
    // Video-HDR with MC.
    else if ( testno == 3 ) {
      // 入力データ.
      Palladium_Set_In_Localstack( D_IM_SHDR_IMG_MEM_IN_YCC_REF_ADDR_TOP,
                                   D_IM_SHDR_IMG_MEM_4K2K_YCC_REF_U8_BYTES );
      Palladium_Set_In_Localstack( D_IM_SHDR_IMG_MEM_IN_YCC_STD_ADDR_TOP,
                                   D_IM_SHDR_IMG_MEM_4K2K_YCC_STD_U8_BYTES );

      // タイマー起動.
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

      // テストコード起動.
      char testArgv1[][ PalladiumTestShdr_PT_SHDR_CMD_LEN ] = { "imshdr", "2", "3" };
      ptImShdrExecuteCmd((sizeof(testArgv1) / PalladiumTestShdr_PT_SHDR_CMD_LEN), (char*)testArgv1);

      // レジスタダンプ.
      ptImShdrRegisterDumpCmd();

      // タイマー停止.
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

      // 出力ダンプ
      Palladium_Set_Out_Localstack( D_IM_SHDR_IMG_MEM_OUT_HEVC_ADDR_TOP,
                                    D_IM_SHDR_IMG_MEM_HEVC_U8_BYTES );
//      Palladium_Set_Out_Localstack( D_IM_SHDR_IMG_MEM_OUT_MEIN_ADDR_TOP,
      D_IM_SHDR_IMG_MEM_MEIN_YCC_U8_BYTES );
      Palladium_Set_Out_Localstack( D_IM_SHDR_IMG_MEM_OUT_RIB_FHD_ADDR_TOP,
                                    D_IM_SHDR_IMG_MEM_RIB_FHD_U8_BYTES );
      Palladium_Set_Out_Localstack( D_IM_SHDR_IMG_MEM_OUT_RIB_HD_ADDR_TOP,
                                    D_IM_SHDR_IMG_MEM_RIB_HD_U8_BYTES );
      Palladium_Set_Out_Localstack( D_IM_SHDR_IMG_MEM_OUT_DISP_HDMI_ADDR_TOP,
                                    D_IM_SHDR_IMG_MEM_DISP_HDMI_YCC_U8_BYTES );
      Palladium_Set_Out_Localstack( D_IM_SHDR_IMG_MEM_OUT_DISP_LCD_ADDR_TOP,
                                    D_IM_SHDR_IMG_MEM_DISP_LCD_YCC_U8_BYTES );
    }
    // Bypass-YCC.
    else if ( testno == 5 ) {
      // 入力データ.
      Palladium_Set_In_Localstack( D_IM_SHDR_IMG_MEM_IN_YCC_REF_ADDR_TOP,
                                   D_IM_SHDR_IMG_MEM_4K2K_YCC_REF_U8_BYTES );

      // タイマー起動.
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

      // テストコード起動.
      char testArgv1[][ PalladiumTestShdr_PT_SHDR_CMD_LEN ] = { "imshdr", "2", "5" };
      ptImShdrExecuteCmd((sizeof(testArgv1) / PalladiumTestShdr_PT_SHDR_CMD_LEN), (char*)testArgv1);

      // レジスタダンプ.
      ptImShdrRegisterDumpCmd();

      // タイマー停止.
      Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

      // 出力ダンプ
      Palladium_Set_Out_Localstack( D_IM_SHDR_IMG_MEM_OUT_HEVC_ADDR_TOP,
                                    D_IM_SHDR_IMG_MEM_HEVC_U8_BYTES );
//      Palladium_Set_Out_Localstack( D_IM_SHDR_IMG_MEM_OUT_MEIN_ADDR_TOP,
      D_IM_SHDR_IMG_MEM_MEIN_YCC_U8_BYTES );
      Palladium_Set_Out_Localstack( D_IM_SHDR_IMG_MEM_OUT_RIB_FHD_ADDR_TOP,
                                    D_IM_SHDR_IMG_MEM_RIB_FHD_U8_BYTES );
      Palladium_Set_Out_Localstack( D_IM_SHDR_IMG_MEM_OUT_RIB_HD_ADDR_TOP,
                                    D_IM_SHDR_IMG_MEM_RIB_HD_U8_BYTES );
      Palladium_Set_Out_Localstack( D_IM_SHDR_IMG_MEM_OUT_DISP_HDMI_ADDR_TOP,
                                    D_IM_SHDR_IMG_MEM_DISP_HDMI_YCC_U8_BYTES );
      Palladium_Set_Out_Localstack( D_IM_SHDR_IMG_MEM_OUT_DISP_LCD_ADDR_TOP,
                                    D_IM_SHDR_IMG_MEM_DISP_LCD_YCC_U8_BYTES );
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

PalladiumTestShdr* palladium_test_shdr_new(void)
{
	PalladiumTestShdr *self = k_object_new_with_private(PALLADIUM_TYPE_TEST_SHDR,
	                                                    sizeof(PalladiumTestShdrPrivate));
	return self;
}
