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
 * @file    palladium_test_hdmac0.c
 * @brief   palladium test code for HDMAC0
 * @note    None
 * @attention None
 *
 * <B><I>Copyright 2016 Socionext Inc.</I></B>
 */

#include "palladium_test.h"
#include "ct_dd_hdmac0.h"
#include "dd_gic.h"
#include "palladiumtesthdmac0.h"

K_TYPE_DEFINE_WITH_PRIVATE(PalladiumTestHdmac0, palladium_test_hdmac0);
#define PALLADIUM_TEST_HDMAC0_GET_PRIVATE(o) \
  (K_OBJECT_GET_PRIVATE ((o), PalladiumTestHdmac0Private,PALLADIUM_TYPE_TEST_HDMAC0))

/*----------------------------------------------------------------------*/
/* Definition                             */
/*----------------------------------------------------------------------*/
#define PalladiumTestHdmac0_CMD_PRM_LEN (15)
#define PalladiumTestHdmac0_CMD_PRM_NUM (12)

/*----------------------------------------------------------------------*/
/* Global Data                              */
/*----------------------------------------------------------------------*/
static char* S_G_ARGV[PalladiumTestHdmac0_CMD_PRM_NUM];

struct _PalladiumTestHdmac0Private
{
};

/*
 * DECLS
 */
static VOID ptDdHdmac0ExecuteCmd(int cmdArgc, char* cmdArgv);

static void palladium_test_hdmac0_constructor(PalladiumTestHdmac0 *self)
{
//	PalladiumTestHdmac0Private *priv = PALLADIUM_TEST_HDMAC0_GET_PRIVATE(self);
}

static void palladium_test_hdmac0_destructor(PalladiumTestHdmac0 *self)
{
//  PalladiumTestHdmac0Private *priv = PALLADIUM_TEST_HDMAC0_GET_PRIVATE(self);
}

/*
 * IMPL
 */
/*----------------------------------------------------------------------*/
/* Local Function                           */
/*----------------------------------------------------------------------*/
static VOID ptDdHdmac0ExecuteCmd(int cmdArgc, char* cmdArgv)
{
    INT32   j;
    INT32   cmdPos = 0;

    for (j = 0; j < cmdArgc; j++) {
        S_G_ARGV[j] = (cmdArgv + (cmdPos * PalladiumTestHdmac0_CMD_PRM_LEN));
        cmdPos++;
    }

    Ct_Dd_HDMAC0_Main(cmdArgc, S_G_ARGV);
}

/*----------------------------------------------------------------------*/
/* Global Function                            */
/*----------------------------------------------------------------------*/
/**
 * @brief   sample code
 * @param   void
 * @return    void
 * @note    None
 * @attention None
 */
void palladium_test_hdmac0_dd_main( void )
{
  UCHAR testno;

  // Test Code Start
//  Dd_GIC_Init();
  Dd_GIC_Ctrl(E_DD_GIC_INTID_HDMAC0_CH0_INT, 1, D_DD_GIC_PRI30, 1);
  Dd_GIC_Ctrl(E_DD_GIC_INTID_HDMAC0_CH1_INT, 1, D_DD_GIC_PRI30, 1);
  Dd_GIC_Ctrl(E_DD_GIC_INTID_HDMAC0_CH2_INT, 1, D_DD_GIC_PRI30, 1);
  Dd_GIC_Ctrl(E_DD_GIC_INTID_HDMAC0_CH3_INT, 1, D_DD_GIC_PRI30, 1);

  // テストパラメータ取得(RSファイルに紐付く)
  testno  = gDDIM_Info.com._6a;

  // set HDMAC0 test data
  Palladium_Set_In_Localstack(D_HDMAC0_AUTO_TEST_ADR_SRC, D_HDMAC0_AUTO_TEST_SIZE);

  // レジスタ取得＆設定(#define PC_DEBUG を定義すること)
  /******************************************************************/
  if ( testno == 1 ) {  // HDMAC0 Auto Test 1

    char hdmac0Argv1[][PalladiumTestHdmac0_CMD_PRM_LEN] = {"hdmac0", "auto", "1"};

    Ddim_Print(("HDMAC0 Auto Test 1 start\n"));
    ptDdHdmac0ExecuteCmd(3, (char*)hdmac0Argv1);
    Ddim_Print(("HDMAC0 Auto Test 1 end\n"));

  /******************************************************************/
  } else if ( testno == 2 ) {   // HDMAC0 Auto Test 2

    char hdmac0Argv1[][PalladiumTestHdmac0_CMD_PRM_LEN] = {"hdmac0", "auto", "2"};

    Ddim_Print(("HDMAC0 Auto Test 2 start\n"));
    ptDdHdmac0ExecuteCmd(3, (char*)hdmac0Argv1);
    Ddim_Print(("HDMAC0 Auto Test 2 end\n"));

  /******************************************************************/
  } else if ( testno == 3 ) {   // HDMAC0 Auto Test 3

    char hdmac0Argv1[][PalladiumTestHdmac0_CMD_PRM_LEN] = {"hdmac0", "auto", "3"};

    Ddim_Print(("HDMAC0 Auto Test 3 start\n"));
    ptDdHdmac0ExecuteCmd(3, (char*)hdmac0Argv1);
    Ddim_Print(("HDMAC0 Auto Test 3 end\n"));

  /******************************************************************/
  } else if ( testno == 4 ) {   // HDMAC0 Auto Test 4

    char hdmac0Argv1[][PalladiumTestHdmac0_CMD_PRM_LEN] = {"hdmac0", "auto", "4"};

    Ddim_Print(("HDMAC0 Auto Test 4 start\n"));
    ptDdHdmac0ExecuteCmd(3, (char*)hdmac0Argv1);
    Ddim_Print(("HDMAC0 Auto Test 4 end\n"));

  /******************************************************************/
  } else if ( testno == 5 ) {   // HDMAC0 Auto Test 5

    char hdmac0Argv1[][PalladiumTestHdmac0_CMD_PRM_LEN] = {"hdmac0", "auto", "5"};

    Ddim_Print(("HDMAC0 Auto Test 5 start\n"));
    ptDdHdmac0ExecuteCmd(3, (char*)hdmac0Argv1);
    Ddim_Print(("HDMAC0 Auto Test 5 end\n"));

  /******************************************************************/
  } else if ( testno == 6 ) {   // HDMAC0 Auto Test 6

    char hdmac0Argv1[][PalladiumTestHdmac0_CMD_PRM_LEN] = {"hdmac0", "auto", "6"};

    Ddim_Print(("HDMAC0 Auto Test 6 start\n"));
    ptDdHdmac0ExecuteCmd(3, (char*)hdmac0Argv1);
    Ddim_Print(("HDMAC0 Auto Test 6 end\n"));

  /******************************************************************/
  } else if ( testno == 11 ) {    // Arb Clear/Get

    char hdmac0Argv1[][PalladiumTestHdmac0_CMD_PRM_LEN] = {"hdmac0", "arb_clear"};
    char hdmac0Argv2[][PalladiumTestHdmac0_CMD_PRM_LEN] = {"hdmac0", "arb_get"};

    Ddim_Print(("HDMAC0 Arbitration Clear Test start\n"));
    ptDdHdmac0ExecuteCmd(2, (char*)hdmac0Argv1);
    ptDdHdmac0ExecuteCmd(2, (char*)hdmac0Argv2);
    Ddim_Print(("HDMAC0 Arbitration Clear Test end\n"));

  /******************************************************************/
  } else if ( testno == 12 ) {    // Arb Set/Get

    char hdmac0Argv1[][PalladiumTestHdmac0_CMD_PRM_LEN] = {"hdmac0", "arb_set", "rotate"};
    char hdmac0Argv2[][PalladiumTestHdmac0_CMD_PRM_LEN] = {"hdmac0", "arb_get"};

    Ddim_Print(("HDMAC0 Arbitration Set Test start\n"));
    ptDdHdmac0ExecuteCmd(3, (char*)hdmac0Argv1);
    ptDdHdmac0ExecuteCmd(2, (char*)hdmac0Argv2);
    Ddim_Print(("HDMAC0 Arbitration Set Test end\n"));

  /******************************************************************/
  } else if ( testno == 21 ) {    // HDMAC0 Transfer Width get 1

    char hdmac0Argv1[][PalladiumTestHdmac0_CMD_PRM_LEN] = {"hdmac0", "get_width", "45000000", "46000000", "256"};

    Ddim_Print(("HDMAC0 Transfer Width get 1 start\n"));
    ptDdHdmac0ExecuteCmd(5, (char*)hdmac0Argv1);
    Ddim_Print(("HDMAC0 Transfer Width get 1 end\n"));

  /******************************************************************/
  } else if ( testno == 22 ) {    // HDMAC0 Transfer Width get 2

    char hdmac0Argv1[][PalladiumTestHdmac0_CMD_PRM_LEN] = {"hdmac0", "get_width", "45000000", "46000002", "256"};

    Ddim_Print(("HDMAC0 Transfer Width get 2 start\n"));
    ptDdHdmac0ExecuteCmd(5, (char*)hdmac0Argv1);
    Ddim_Print(("HDMAC0 Transfer Width get 2 end\n"));

  /******************************************************************/
  } else if ( testno == 23 ) {    // HDMAC0 Transfer Width get 3

    char hdmac0Argv1[][PalladiumTestHdmac0_CMD_PRM_LEN] = {"hdmac0", "get_width", "45000000", "46000002", "257"};

    Ddim_Print(("HDMAC0 Transfer Width get 3 start\n"));
    ptDdHdmac0ExecuteCmd(5, (char*)hdmac0Argv1);
    Ddim_Print(("HDMAC0 Transfer Width get 3 end\n"));

  /******************************************************************/
  } else if ( testno == 31 ) {    // HDMAC0 Pause/Resume GetSize test

    char hdmac0Argv1[][PalladiumTestHdmac0_CMD_PRM_LEN]  = {"hdmac0", "ctrl_trns_md", "0", "soft", "blk", "src_incr",
        "dst_incr", "normal"};
    char hdmac0Argv2[][PalladiumTestHdmac0_CMD_PRM_LEN]  = {"hdmac0", "ctrl_trns_sz", "0", "1", "0x96000",
        "0x41000000", "0x41096000"};
    char hdmac0Argv3[][PalladiumTestHdmac0_CMD_PRM_LEN]  = {"hdmac0", "ctrl_trns", "0"};
    char hdmac0Argv4[][PalladiumTestHdmac0_CMD_PRM_LEN]  = {"hdmac0", "start_async", "0"};
    char hdmac0Argv5[][PalladiumTestHdmac0_CMD_PRM_LEN]  = {"hdmac0", "pause", "0"};
    char hdmac0Argv6[][PalladiumTestHdmac0_CMD_PRM_LEN]  = {"hdmac0", "status_read", "0"};
    char hdmac0Argv7[][PalladiumTestHdmac0_CMD_PRM_LEN]  = {"hdmac0", "status_clear", "0"};
    char hdmac0Argv8[][PalladiumTestHdmac0_CMD_PRM_LEN]  = {"hdmac0", "status_read", "0"};
    char hdmac0Argv9[][PalladiumTestHdmac0_CMD_PRM_LEN]  = {"hdmac0", "trns_size_get", "0"};
    char hdmac0Argv10[][PalladiumTestHdmac0_CMD_PRM_LEN] = {"hdmac0", "rmn_size_get", "0"};
    char hdmac0Argv11[][PalladiumTestHdmac0_CMD_PRM_LEN] = {"hdmac0", "total_size_get", "0"};
    char hdmac0Argv12[][PalladiumTestHdmac0_CMD_PRM_LEN] = {"hdmac0", "src_addr_get", "0"};
    char hdmac0Argv13[][PalladiumTestHdmac0_CMD_PRM_LEN] = {"hdmac0", "dst_addr_get", "0"};
    char hdmac0Argv14[][PalladiumTestHdmac0_CMD_PRM_LEN] = {"hdmac0", "resume", "0"};
    char hdmac0Argv15[][PalladiumTestHdmac0_CMD_PRM_LEN] = {"hdmac0", "wait", "0", "event"};

    Ddim_Print(("HDMAC0 Pause/Resume Test start\n"));
    ptDdHdmac0ExecuteCmd(8, (char*)hdmac0Argv1);    // ctrl_trns_md
    ptDdHdmac0ExecuteCmd(7, (char*)hdmac0Argv2);    // ctrl_trns_sz
    ptDdHdmac0ExecuteCmd(3, (char*)hdmac0Argv3);    // ctrl_trns
    ptDdHdmac0ExecuteCmd(3, (char*)hdmac0Argv4);    // start_async
    ptDdHdmac0ExecuteCmd(3, (char*)hdmac0Argv5);    // pause
    ptDdHdmac0ExecuteCmd(3, (char*)hdmac0Argv6);    // status_read
    ptDdHdmac0ExecuteCmd(3, (char*)hdmac0Argv7);    // status_clear
    ptDdHdmac0ExecuteCmd(3, (char*)hdmac0Argv8);    // status_read
    ptDdHdmac0ExecuteCmd(3, (char*)hdmac0Argv9);    // trns_size_get
    ptDdHdmac0ExecuteCmd(3, (char*)hdmac0Argv10);   // rmn_size_get
    ptDdHdmac0ExecuteCmd(3, (char*)hdmac0Argv11);   // total_size_get
    ptDdHdmac0ExecuteCmd(3, (char*)hdmac0Argv12);   // src_addr_get
    ptDdHdmac0ExecuteCmd(3, (char*)hdmac0Argv13);   // dst_addr_get
    ptDdHdmac0ExecuteCmd(3, (char*)hdmac0Argv14);   // resume
    ptDdHdmac0ExecuteCmd(4, (char*)hdmac0Argv15);   // wait
  }

  Palladium_Set_Out_Localstack(D_HDMAC0_AUTO_TEST_ADR_DST, D_HDMAC0_AUTO_TEST_SIZE);

//#endif
}

PalladiumTestHdmac0* palladium_test_hdmac0_new(void)
{
	PalladiumTestHdmac0 *self = k_object_new_with_private(PALLADIUM_TYPE_TEST_HDMAC0,
	                                                      sizeof(PalladiumTestHdmac0Private));
	return self;
}
