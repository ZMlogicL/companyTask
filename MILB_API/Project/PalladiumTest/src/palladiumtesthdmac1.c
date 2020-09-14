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


#include "palladiumtesthdmac1.h"
#include "palladium_test.h"
#include "ct_dd_hdmac1.h"
#include "dd_gic.h"

K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(PalladiumTestHdmac1, palladium_test_hdmac1,K_TYPE_OBJECT)
#define PALLADIUM_TEST_HDMAC1_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), PalladiumTestHdmac1Private,PALLADIUM_TYPE_TEST_HDMAC1))

#define PalladiumTestHdmac1_CMD_PRM_LEN (15)
#define PalladiumTestHdmac1_CMD_PRM_NUM (12)

struct _PalladiumTestHdmac1Private
{
	char* gArgv[PalladiumTestHdmac1_CMD_PRM_NUM];
	char* cmdArgv;
};

static void palladium_test_hdmac1_constructor(PalladiumTestHdmac1 *self)
{
	PalladiumTestHdmac1Private *priv = PALLADIUM_TEST_HDMAC_1_GET_PRIVATE(self);
	priv ->cmdArgv =NULL;
	memset(priv ->gArgv, 0,11*(sizeof(char*)));
}

static void palladium_test_hdmac1_destructor(PalladiumTestHdmac1 *self)
{
	PalladiumTestHdmac1Private *priv = PALLADIUM_TEST_HDMAC_1_GET_PRIVATE(self);
	if (priv->gArgv != NULL) {
		k_free(priv->gArgv);
		priv->gArgv = NULL;
	}
	if (priv->cmdArgv != NULL) {
		k_free(priv->cmdArgv);
		priv->cmdArgv = NULL;
	}
}

/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/
static void pt_dd_hdmac1_execute_cmd(PalladiumTestHdmac1 *self, PalladiumTestHdmac1 *self,int cmdArgc, char* cmdArgv)
{
	PalladiumTestHdmac1Private *priv = PALLADIUM_TEST_HDMAC_1_GET_PRIVATE(self);
    kint32   j;
    kint32   cmdPos = 0;
    priv ->cmdArgv =cmdArgv;

    for (j = 0; j < cmdArgc; j++) {
        priv->gArgv[j] = (priv ->cmdArgv + (cmdPos * PalladiumTestHdmac1_CMD_PRM_LEN));
        cmdPos++;
    }

    ct_dd_hdmac1_main(cmdArgc, priv->gArgv);
}

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
void palladium_test_hdmac1_main( PalladiumTestHdmac1 *self )
{
	kuchar	testno;

	// Test Code Start
//	Dd_GIC_Init();
	dd_gic_ctrl(EDdGicIntid_HDMAC1_CH0_INT, 1, D_DD_GIC_PRI30, 1);
	dd_gic_ctrl(EDdGicIntid_HDMAC1_CH1_INT, 1, D_DD_GIC_PRI30, 1);
	dd_gic_ctrl(EDdGicIntid_HDMAC1_CH2_INT, 1, D_DD_GIC_PRI30, 1);
	dd_gic_ctrl(EDdGicIntid_HDMAC1_CH3_INT, 1, D_DD_GIC_PRI30, 1);

	// テストパラメータ取得(RSファイルに紐付く)
	testno	= gDdimInfo.com._6a;

	// set HDMAC1 test data
	Palladium_Set_In_Localstack(D_HDMAC1_AUTO_TEST_ADR_SRC, D_HDMAC1_AUTO_TEST_SIZE);

	// レジスタ取得＆設定(#define PC_DEBUG を定義すること)
	/******************************************************************/
	if ( testno == 1 ) {	// HDMAC1 Auto Test 1

		char hdmac1Argv1[][PalladiumTestHdmac1_CMD_PRM_LEN] = {"hdmac1", "auto", "1"};

		Ddim_Print(("HDMAC1 Auto Test 1 start\n"));
		pt_dd_hdmac1_execute_cmd(self, 3, (char*)hdmac1Argv1);
		Ddim_Print(("HDMAC1 Auto Test 1 end\n"));

	/******************************************************************/
	} else if ( testno == 2 ) {		// HDMAC1 Auto Test 2

		char hdmac1Argv1[][PalladiumTestHdmac1_CMD_PRM_LEN] = {"hdmac1", "auto", "2"};

		Ddim_Print(("HDMAC1 Auto Test 2 start\n"));
		pt_dd_hdmac1_execute_cmd(self, 3, (char*)hdmac1Argv1);
		Ddim_Print(("HDMAC1 Auto Test 2 end\n"));

	/******************************************************************/
	} else if ( testno == 3 ) {		// HDMAC1 Auto Test 3

		char hdmac1Argv1[][PalladiumTestHdmac1_CMD_PRM_LEN] = {"hdmac1", "auto", "3"};

		Ddim_Print(("HDMAC1 Auto Test 3 start\n"));
		pt_dd_hdmac1_execute_cmd(self, 3, (char*)hdmac1Argv1);
		Ddim_Print(("HDMAC1 Auto Test 3 end\n"));

	/******************************************************************/
	} else if ( testno == 4 ) {		// HDMAC1 Auto Test 4

		char hdmac1Argv1[][PalladiumTestHdmac1_CMD_PRM_LEN] = {"hdmac1", "auto", "4"};

		Ddim_Print(("HDMAC1 Auto Test 4 start\n"));
		pt_dd_hdmac1_execute_cmd(self, 3, (char*)hdmac1Argv1);
		Ddim_Print(("HDMAC1 Auto Test 4 end\n"));

	/******************************************************************/
	} else if ( testno == 5 ) {		// HDMAC1 Auto Test 5

		char hdmac1Argv1[][PalladiumTestHdmac1_CMD_PRM_LEN] = {"hdmac1", "auto", "5"};

		Ddim_Print(("HDMAC1 Auto Test 5 start\n"));
		pt_dd_hdmac1_execute_cmd(self, 3, (char*)hdmac1Argv1);
		Ddim_Print(("HDMAC1 Auto Test 5 end\n"));

	/******************************************************************/
	} else if ( testno == 6 ) {		// HDMAC1 Auto Test 6

		char hdmac1Argv1[][PalladiumTestHdmac1_CMD_PRM_LEN] = {"hdmac1", "auto", "6"};

		Ddim_Print(("HDMAC1 Auto Test 6 start\n"));
		pt_dd_hdmac1_execute_cmd(self, 3, (char*)hdmac1Argv1);
		Ddim_Print(("HDMAC1 Auto Test 6 end\n"));

	/******************************************************************/
	} else if ( testno == 11 ) {		// Arb Clear/Get

		char hdmac1Argv1[][PalladiumTestHdmac1_CMD_PRM_LEN] = {"hdmac1", "arb_clear"};
		char hdmac1Argv2[][PalladiumTestHdmac1_CMD_PRM_LEN] = {"hdmac1", "arb_get"};

		Ddim_Print(("HDMAC1 Arbitration Clear Test start\n"));
		pt_dd_hdmac1_execute_cmd(self, 2, (char*)hdmac1Argv1);
		pt_dd_hdmac1_execute_cmd(self, 2, (char*)hdmac1Argv2);
		Ddim_Print(("HDMAC1 Arbitration Clear Test end\n"));

	/******************************************************************/
	} else if ( testno == 12 ) {		// Arb Set/Get

		char hdmac1Argv1[][PalladiumTestHdmac1_CMD_PRM_LEN] = {"hdmac1", "arb_set", "rotate"};
		char hdmac1Argv2[][PalladiumTestHdmac1_CMD_PRM_LEN] = {"hdmac1", "arb_get"};

		Ddim_Print(("HDMAC1 Arbitration Set Test start\n"));
		pt_dd_hdmac1_execute_cmd(self, 3, (char*)hdmac1Argv1);
		pt_dd_hdmac1_execute_cmd(self, 2, (char*)hdmac1Argv2);
		Ddim_Print(("HDMAC1 Arbitration Set Test end\n"));

	/******************************************************************/
	} else if ( testno == 21 ) {		// HDMAC1 Transfer Width get 1

		char hdmac1Argv1[][PalladiumTestHdmac1_CMD_PRM_LEN] = {"hdmac1", "get_width", "45000000", "46000000", "256"};

		Ddim_Print(("HDMAC1 Transfer Width get 1 start\n"));
		pt_dd_hdmac1_execute_cmd(self, 5, (char*)hdmac1Argv1);
		Ddim_Print(("HDMAC1 Transfer Width get 1 end\n"));

	/******************************************************************/
	} else if ( testno == 22 ) {		// HDMAC1 Transfer Width get 2

		char hdmac1Argv1[][PalladiumTestHdmac1_CMD_PRM_LEN] = {"hdmac1", "get_width", "45000000", "46000002", "256"};

		Ddim_Print(("HDMAC1 Transfer Width get 2 start\n"));
		pt_dd_hdmac1_execute_cmd(self, 5, (char*)hdmac1Argv1);
		Ddim_Print(("HDMAC1 Transfer Width get 2 end\n"));

	/******************************************************************/
	} else if ( testno == 23 ) {		// HDMAC1 Transfer Width get 3

		char hdmac1Argv1[][PalladiumTestHdmac1_CMD_PRM_LEN] = {"hdmac1", "get_width", "45000000", "46000002", "257"};

		Ddim_Print(("HDMAC1 Transfer Width get 3 start\n"));
		pt_dd_hdmac1_execute_cmd(self, 5, (char*)hdmac1Argv1);
		Ddim_Print(("HDMAC1 Transfer Width get 3 end\n"));

	/******************************************************************/
	} else if ( testno == 31 ) {		// HDMAC1 Pause/Resume GetSize test

		char hdmac1Argv1[][PalladiumTestHdmac1_CMD_PRM_LEN]  = {"hdmac1", "ctrl_trns_md", "0", "soft", "blk", "src_incr", "dst_incr", "normal"};
		char hdmac1Argv2[][PalladiumTestHdmac1_CMD_PRM_LEN]  = {"hdmac1", "ctrl_trns_sz", "0", "1", "0x96000", "0x41000000", "0x41096000"};
		char hdmac1Argv3[][PalladiumTestHdmac1_CMD_PRM_LEN]  = {"hdmac1", "ctrl_trns", "0"};
		char hdmac1Argv4[][PalladiumTestHdmac1_CMD_PRM_LEN]  = {"hdmac1", "start_async", "0"};
		char hdmac1Argv5[][PalladiumTestHdmac1_CMD_PRM_LEN]  = {"hdmac1", "pause", "0"};
		char hdmac1Argv6[][PalladiumTestHdmac1_CMD_PRM_LEN]  = {"hdmac1", "status_read", "0"};
		char hdmac1Argv7[][PalladiumTestHdmac1_CMD_PRM_LEN]  = {"hdmac1", "status_clear", "0"};
		char hdmac1Argv8[][PalladiumTestHdmac1_CMD_PRM_LEN]  = {"hdmac1", "status_read", "0"};
		char hdmac1Argv9[][PalladiumTestHdmac1_CMD_PRM_LEN]  = {"hdmac1", "trns_size_get", "0"};
		char hdmac1Argv10[][PalladiumTestHdmac1_CMD_PRM_LEN] = {"hdmac1", "rmn_size_get", "0"};
		char hdmac1Argv11[][PalladiumTestHdmac1_CMD_PRM_LEN] = {"hdmac1", "total_size_get", "0"};
		char hdmac1Argv12[][PalladiumTestHdmac1_CMD_PRM_LEN] = {"hdmac1", "src_addr_get", "0"};
		char hdmac1Argv13[][PalladiumTestHdmac1_CMD_PRM_LEN] = {"hdmac1", "dst_addr_get", "0"};
		char hdmac1Argv14[][PalladiumTestHdmac1_CMD_PRM_LEN] = {"hdmac1", "resume", "0"};
		char hdmac1Argv15[][PalladiumTestHdmac1_CMD_PRM_LEN] = {"hdmac1", "wait", "0", "event"};

		Ddim_Print(("HDMAC1 Pause/Resume Test start\n"));
		pt_dd_hdmac1_execute_cmd(self, 8, (char*)hdmac1Argv1);		// ctrl_trns_md
		pt_dd_hdmac1_execute_cmd(self, 7, (char*)hdmac1Argv2);		// ctrl_trns_sz
		pt_dd_hdmac1_execute_cmd(self, 3, (char*)hdmac1Argv3);		// ctrl_trns
		pt_dd_hdmac1_execute_cmd(self, 3, (char*)hdmac1Argv4);		// start_async
		pt_dd_hdmac1_execute_cmd(self, 3, (char*)hdmac1Argv5);		// pause
		pt_dd_hdmac1_execute_cmd(self, 3, (char*)hdmac1Argv6);		// status_read
		pt_dd_hdmac1_execute_cmd(self, 3, (char*)hdmac1Argv7);		// status_clear
		pt_dd_hdmac1_execute_cmd(self, 3, (char*)hdmac1Argv8);		// status_read
		pt_dd_hdmac1_execute_cmd(self, 3, (char*)hdmac1Argv9);		// trns_size_get
		pt_dd_hdmac1_execute_cmd(self, 3, (char*)hdmac1Argv10);		// rmn_size_get
		pt_dd_hdmac1_execute_cmd(self, 3, (char*)hdmac1Argv11);		// total_size_get
		pt_dd_hdmac1_execute_cmd(self, 3, (char*)hdmac1Argv12);		// src_addr_get
		pt_dd_hdmac1_execute_cmd(self, 3, (char*)hdmac1Argv13);		// dst_addr_get
		pt_dd_hdmac1_execute_cmd(self, 3, (char*)hdmac1Argv14);		// resume
		pt_dd_hdmac1_execute_cmd(self, 4, (char*)hdmac1Argv15);		// wait
	}

	palladium_set_out_localstack(D_HDMAC1_AUTO_TEST_ADR_DST, D_HDMAC1_AUTO_TEST_SIZE);

//#endif
}

PalladiumTestHdmac1* palladium_test_hdmac1_new(void)
{
	static PalladiumTestHdmac1* singleton = NULL;
	if (!singleton) {
		singleton = k_object_new_with_private(PALLADIUM_TYPE_TEST_HDMAC1,
				sizeof(PalladiumTestHdmac1Private));
	} else {
		k_object_ref(singleton);
	}
	k_assert(singleton);
	return singleton;
}
