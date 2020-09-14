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
 * @file    palladium_test_hdmac.c
 * @brief   palladium test code for HDMAC
 * @note    None
 * @attention None
 *
 * <B><I>Copyright 2016 Socionext Inc.</I></B>
 */

#include "palladium_test.h"
#include "ct_dd_hdmac.h"
#include "ddgic.h"
#include "palladiumtesthdmac.h"

K_TYPE_DEFINE_WITH_PRIVATE(PalladiumTestHdmac, palladium_test_hdmac);
#define PALLADIUM_TEST_HDMAC_GET_PRIVATE(o) \
  (K_OBJECT_GET_PRIVATE ((o), PalladiumTestHdmacPrivate,PALLADIUM_TYPE_TEST_HDMAC))

/*----------------------------------------------------------------------*/
/* Definition                             */
/*----------------------------------------------------------------------*/
#define PalladiumTestHdmac_CMD_PRM_LEN (15)
#define PalladiumTestHdmac_CMD_PRM_NUM (12)

/*----------------------------------------------------------------------*/
/* Global Data                              */
/*----------------------------------------------------------------------*/
static kchar* S_G_ARGV[PalladiumTestHdmac_CMD_PRM_NUM];

struct _PalladiumTestHdmacPrivate
{
};

/*
 * DECLS
 */
static void ptDdHdmacExecuteCmd(kint cmdArgc, kchar* cmdArgv);

static void palladium_test_hdmac_constructor(PalladiumTestHdmac *self)
{
//	PalladiumTestHdmacPrivate *priv = PALLADIUM_TEST_HDMAC_GET_PRIVATE(self);
}

static void palladium_test_hdmac_destructor(PalladiumTestHdmac *self)
{
//  PalladiumTestHdmacPrivate *priv = PALLADIUM_TEST_HDMAC_GET_PRIVATE(self);
}

/*
 * IMPL
 */
/*----------------------------------------------------------------------*/
/* Local Function                           */
/*----------------------------------------------------------------------*/
static void ptDdHdmacExecuteCmd(kint cmdArgc, kchar* cmdArgv)
{
    kint32   j;
    kint32   cmdPos = 0;

    for (j = 0; j < cmdArgc; j++) {
        S_G_ARGV[j] = (cmdArgv + (cmdPos * PalladiumTestHdmac_CMD_PRM_LEN));
        cmdPos++;
    }

    Ct_Dd_HDMAC_Main(cmdArgc, S_G_ARGV);
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
void palladium_test_hdmac_dd_main(PalladiumTestHdmac *self)
{
  kuchar testno;

  // Test Code Start
//  Dd_GIC_Init();
  Dd_GIC_Ctrl(E_DD_GIC_INTID_EXS_HDMAC_CH0_INT, 1, C_PRI30, 1);
  Dd_GIC_Ctrl(E_DD_GIC_INTID_EXS_HDMAC_CH1_INT, 1, C_PRI30, 1);
  Dd_GIC_Ctrl(E_DD_GIC_INTID_EXS_HDMAC_CH2_INT, 1, C_PRI30, 1);
  Dd_GIC_Ctrl(E_DD_GIC_INTID_EXS_HDMAC_CH3_INT, 1, C_PRI30, 1);

  // テストパラメータ取得(RSファイルに紐付く)
  testno  = gDDIM_Info.com._6a;

  // set HDMAC test data
  Palladium_Set_In_Localstack(D_HDMAC_AUTO_TEST_ADR_SRC, D_HDMAC_AUTO_TEST_SIZE);

  // レジスタ取得＆設定(#define PC_DEBUG を定義すること)
  /******************************************************************/
  if (testno == 1) {  // HDMAC Auto Test 1

    kchar hdmacArgv1[][PalladiumTestHdmac_CMD_PRM_LEN] = {"hdmac", "auto", "1"};

    Ddim_Print(("HDMAC Auto Test 1 start\n"));
    ptDdHdmacExecuteCmd(3, (kchar*)hdmacArgv1);
    Ddim_Print(("HDMAC Auto Test 1 end\n"));

  /******************************************************************/
  } else if (testno == 2) {   // HDMAC Auto Test 2

    kchar hdmacArgv1[][PalladiumTestHdmac_CMD_PRM_LEN] = {"hdmac", "auto", "2"};

    Ddim_Print(("HDMAC Auto Test 2 start\n"));
    ptDdHdmacExecuteCmd(3, (kchar*)hdmacArgv1);
    Ddim_Print(("HDMAC Auto Test 2 end\n"));

  /******************************************************************/
  } else if (testno == 3) {   // HDMAC Auto Test 3

    kchar hdmacArgv1[][PalladiumTestHdmac_CMD_PRM_LEN] = {"hdmac", "auto", "3"};

    Ddim_Print(("HDMAC Auto Test 3 start\n"));
    ptDdHdmacExecuteCmd(3, (kchar*)hdmacArgv1);
    Ddim_Print(("HDMAC Auto Test 3 end\n"));

  /******************************************************************/
  } else if (testno == 4) {   // HDMAC Auto Test 4

    kchar hdmacArgv1[][PalladiumTestHdmac_CMD_PRM_LEN] = {"hdmac", "auto", "4"};

    Ddim_Print(("HDMAC Auto Test 4 start\n"));
    ptDdHdmacExecuteCmd(3, (kchar*)hdmacArgv1);
    Ddim_Print(("HDMAC Auto Test 4 end\n"));

  /******************************************************************/
  } else if (testno == 5) {   // HDMAC Auto Test 5

    kchar hdmacArgv1[][PalladiumTestHdmac_CMD_PRM_LEN] = {"hdmac", "auto", "5"};

    Ddim_Print(("HDMAC Auto Test 5 start\n"));
    ptDdHdmacExecuteCmd(3, (kchar*)hdmacArgv1);
    Ddim_Print(("HDMAC Auto Test 5 end\n"));

  /******************************************************************/
  } else if (testno == 6) {   // HDMAC Auto Test 6

    kchar hdmacArgv1[][PalladiumTestHdmac_CMD_PRM_LEN] = {"hdmac", "auto", "6"};

    Ddim_Print(("HDMAC Auto Test 6 start\n"));
    ptDdHdmacExecuteCmd(3, (kchar*)hdmacArgv1);
    Ddim_Print(("HDMAC Auto Test 6 end\n"));

  /******************************************************************/
  } else if (testno == 11) {    // Arb Clear/Get

    kchar hdmacArgv1[][PalladiumTestHdmac_CMD_PRM_LEN] = {"hdmac", "arb_clear"};
    kchar hdmacArgv2[][PalladiumTestHdmac_CMD_PRM_LEN] = {"hdmac", "arb_get"};

    Ddim_Print(("HDMAC Arbitration Clear Test start\n"));
    ptDdHdmacExecuteCmd(2, (kchar*)hdmacArgv1);
    ptDdHdmacExecuteCmd(2, (kchar*)hdmacArgv2);
    Ddim_Print(("HDMAC Arbitration Clear Test end\n"));

  /******************************************************************/
  } else if (testno == 12) {    // Arb Set/Get

    kchar hdmacArgv1[][PalladiumTestHdmac_CMD_PRM_LEN] = {"hdmac", "arb_set", "rotate"};
    kchar hdmacArgv2[][PalladiumTestHdmac_CMD_PRM_LEN] = {"hdmac", "arb_get"};

    Ddim_Print(("HDMAC Arbitration Set Test start\n"));
    ptDdHdmacExecuteCmd(3, (kchar*)hdmacArgv1);
    ptDdHdmacExecuteCmd(2, (kchar*)hdmacArgv2);
    Ddim_Print(("HDMAC Arbitration Set Test end\n"));

  /******************************************************************/
  } else if (testno == 21) {    // HDMAC Transfer Width get 1

    kchar hdmacArgv1[][PalladiumTestHdmac_CMD_PRM_LEN] = {"hdmac", "get_width", "40000000", "41000000", "256"};

    Ddim_Print(("HDMAC Transfer Width get 1 start\n"));
    ptDdHdmacExecuteCmd(5, (kchar*)hdmacArgv1);
    Ddim_Print(("HDMAC Transfer Width get 1 end\n"));

  /******************************************************************/
  } else if (testno == 22) {    // HDMAC Transfer Width get 2

    kchar hdmacArgv1[][PalladiumTestHdmac_CMD_PRM_LEN] = {"hdmac", "get_width", "40000000", "41000002", "256"};

    Ddim_Print(("HDMAC Transfer Width get 2 start\n"));
    ptDdHdmacExecuteCmd(5, (kchar*)hdmacArgv1);
    Ddim_Print(("HDMAC Transfer Width get 2 end\n"));

  /******************************************************************/
  } else if (testno == 23) {    // HDMAC Transfer Width get 3

    kchar hdmacArgv1[][PalladiumTestHdmac_CMD_PRM_LEN] = {"hdmac", "get_width", "40000000", "41000002", "257"};

    Ddim_Print(("HDMAC Transfer Width get 3 start\n"));
    ptDdHdmacExecuteCmd(5, (kchar*)hdmacArgv1);
    Ddim_Print(("HDMAC Transfer Width get 3 end\n"));

  /******************************************************************/
  } else if (testno == 31) {    // HDMAC Pause/Resume GetSize test

    kchar hdmacArgv1[][PalladiumTestHdmac_CMD_PRM_LEN]  = {"hdmac", "ctrl_trns_md", "0", "soft", "blk", "src_incr",
        "dst_incr", "normal"};
    kchar hdmacArgv2[][PalladiumTestHdmac_CMD_PRM_LEN]  = {"hdmac", "ctrl_trns_sz", "0", "1", "0x96000",
        "0x41000000", "0x41096000"};
    kchar hdmacArgv3[][PalladiumTestHdmac_CMD_PRM_LEN]  = {"hdmac", "ctrl_trns", "0"};
    kchar hdmacArgv4[][PalladiumTestHdmac_CMD_PRM_LEN]  = {"hdmac", "start_async", "0"};
    kchar hdmacArgv5[][PalladiumTestHdmac_CMD_PRM_LEN]  = {"hdmac", "pause", "0"};
    kchar hdmacArgv6[][PalladiumTestHdmac_CMD_PRM_LEN]  = {"hdmac", "status_read", "0"};
    kchar hdmacArgv7[][PalladiumTestHdmac_CMD_PRM_LEN]  = {"hdmac", "status_clear", "0"};
    kchar hdmacArgv8[][PalladiumTestHdmac_CMD_PRM_LEN]  = {"hdmac", "status_read", "0"};
    kchar hdmacArgv9[][PalladiumTestHdmac_CMD_PRM_LEN]  = {"hdmac", "trns_size_get", "0"};
    kchar hdmacArgv10[][PalladiumTestHdmac_CMD_PRM_LEN] = {"hdmac", "rmn_size_get", "0"};
    kchar hdmacArgv11[][PalladiumTestHdmac_CMD_PRM_LEN] = {"hdmac", "total_size_get", "0"};
    kchar hdmacArgv12[][PalladiumTestHdmac_CMD_PRM_LEN] = {"hdmac", "src_addr_get", "0"};
    kchar hdmacArgv13[][PalladiumTestHdmac_CMD_PRM_LEN] = {"hdmac", "dst_addr_get", "0"};
    kchar hdmacArgv14[][PalladiumTestHdmac_CMD_PRM_LEN] = {"hdmac", "resume", "0"};
    kchar hdmacArgv15[][PalladiumTestHdmac_CMD_PRM_LEN] = {"hdmac", "wait", "0", "event"};

    Ddim_Print(("HDMAC Pause/Resume Test start\n"));
    ptDdHdmacExecuteCmd(8, (kchar*)hdmacArgv1);    // ctrl_trns_md
    ptDdHdmacExecuteCmd(7, (kchar*)hdmacArgv2);    // ctrl_trns_sz
    ptDdHdmacExecuteCmd(3, (kchar*)hdmacArgv3);    // ctrl_trns
    ptDdHdmacExecuteCmd(3, (kchar*)hdmacArgv4);    // start_async
    ptDdHdmacExecuteCmd(3, (kchar*)hdmacArgv5);    // pause
    ptDdHdmacExecuteCmd(3, (kchar*)hdmacArgv6);    // status_read
    ptDdHdmacExecuteCmd(3, (kchar*)hdmacArgv7);    // status_clear
    ptDdHdmacExecuteCmd(3, (kchar*)hdmacArgv8);    // status_read
    ptDdHdmacExecuteCmd(3, (kchar*)hdmacArgv9);    // trns_size_get
    ptDdHdmacExecuteCmd(3, (kchar*)hdmacArgv10);   // rmn_size_get
    ptDdHdmacExecuteCmd(3, (kchar*)hdmacArgv11);   // total_size_get
    ptDdHdmacExecuteCmd(3, (kchar*)hdmacArgv12);   // src_addr_get
    ptDdHdmacExecuteCmd(3, (kchar*)hdmacArgv13);   // dst_addr_get
    ptDdHdmacExecuteCmd(3, (kchar*)hdmacArgv14);   // resume
    ptDdHdmacExecuteCmd(4, (kchar*)hdmacArgv15);   // wait
  }

  Palladium_Set_Out_Localstack(D_HDMAC_AUTO_TEST_ADR_DST, D_HDMAC_AUTO_TEST_SIZE);

//#endif
}

PalladiumTestHdmac* palladium_test_hdmac_new(void)
{
	PalladiumTestHdmac *self = k_object_new_with_private(PALLADIUM_TYPE_TEST_HDMAC,
	                                                     sizeof(PalladiumTestHdmacPrivate));
	return self;
}
