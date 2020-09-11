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
 * @file		palladium_test_exs.c
 * @brief		palladium test code for exs.
 * @note		None
 * @attention	None
 *
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */


#include "palladiumtestexs.h"

//拆分类头文件
#include "palladiumtestmainexs.h"

K_TYPE_DEFINE_WITH_PRIVATE(PalladiumTestExs, palladium_test_exs);
#define PALLADIUM_TEST_EXS_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), PalladiumTestExsPrivate,PALLADIUM_TYPE_TEST_EXS))



struct _PalladiumTestExsPrivate
{
	int a;
};

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
static char* gDdExsCmdArgv[20];


static void palladium_test_exs_constructor(PalladiumTestExs *self)
{
	PalladiumTestExsPrivate *priv = PALLADIUM_TEST_EXS_GET_PRIVATE(self);
	priv->a = 0;
}

static void palladium_test_exs_destructor(PalladiumTestExs *self)
{
}


/*
 * PUBLIC
 */

/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Local Method Definition												*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/

void palladium_test_exs_execute_cmd(int cmdArgc, char* cmdArgv)
{
	INT32 j;
	INT32 cmdPos = 0;

	for (j = 0; j < cmdArgc; j++) {
		gDdExsCmdArgv[j] = (cmdArgv + (cmdPos * PalladiumTestExs_PT_DD_EXS_CMD_LEN));
		cmdPos++;
	}

	Ct_Dd_EXS_Main(cmdArgc, gDdExsCmdArgv);
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
VOID palladium_test_exs_dd_exs_main( VOID )
{
	UCHAR	testno;

	// 開始ログ
	Ddim_Print(( "EXS Palladium test Start\n" ));

	// タイマー初期化(処理時間計測用)
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_INIT );

	// テストパラメータ取得(RSファイルに紐付く)
	testno	= gDDIM_Info.com._6a;

	Ddim_Print(( "EXS Palladium test No %d Start\n", testno ));
	palladium_test_main_exs_testno( testno );
	palladium_test_main2_exs_testno( testno );
	if ( testno == 10 ) {		// "BUSCKSTP"レジスタのテスト

		char testArgv00And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "busckstp", "nf_ckstp", "1"};
		char testArgv00And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "busckstp", "pcie0_ckstp", "1"};
		char testArgv00And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "busckstp", "pcie1_ckstp", "1"};
		char testArgv00And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "busckstp", "xdmac_ckstp", "1"};
		char testArgv00And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "busckstp", "hdmac_ckstp", "1"};
		char testArgv00And06[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "busckstp", "emmc_ckstp", "1"};
		char testArgv00And07[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "busckstp", "sd2_ckstp", "1"};
		char testArgv00And08[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "busckstp", "sd3_ckstp", "1"};
		char testArgv00And09[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "busckstp", "sd4_ckstp", "1"};
		char testArgv00And10[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "busckstp", "netsec_ckstp", "1"};
		char testArgv00And11[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "busckstp", "relc_ckstp", "1"};

		palladium_test_exs_execute_cmd((sizeof(testArgv00And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv00And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And02);
		palladium_test_exs_execute_cmd((sizeof(testArgv00And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And03);
		palladium_test_exs_execute_cmd((sizeof(testArgv00And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And04);
		palladium_test_exs_execute_cmd((sizeof(testArgv00And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And05);
		palladium_test_exs_execute_cmd((sizeof(testArgv00And06) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And06);
		palladium_test_exs_execute_cmd((sizeof(testArgv00And07) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And07);
		palladium_test_exs_execute_cmd((sizeof(testArgv00And08) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And08);
		palladium_test_exs_execute_cmd((sizeof(testArgv00And09) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And09);
		palladium_test_exs_execute_cmd((sizeof(testArgv00And10) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And10);
		palladium_test_exs_execute_cmd((sizeof(testArgv00And11) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And11);

		// 1-1-87
		char testArgv01And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "busckstp", "nf_ckstp"};
		char testArgv01And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "busckstp", "nf_ckstp", "1"};
		char testArgv01And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "busckstp", "nf_ckstp"};
		char testArgv01And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "busckstp", "nf_ckstp", "0"};
		char testArgv01And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "busckstp", "nf_ckstp"};

		palladium_test_exs_execute_cmd((sizeof(testArgv01And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And02);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And03);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And04);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And05);

		// 1-1-88
		char testArgv02And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "busckstp", "pcie0_ckstp"};
		char testArgv02And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "busckstp", "pcie0_ckstp", "1"};
		char testArgv02And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "busckstp", "pcie0_ckstp"};
		char testArgv02And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "busckstp", "pcie0_ckstp", "0"};
		char testArgv02And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "busckstp", "pcie0_ckstp"};

		palladium_test_exs_execute_cmd((sizeof(testArgv02And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv02And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And02);
		palladium_test_exs_execute_cmd((sizeof(testArgv02And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And03);
		palladium_test_exs_execute_cmd((sizeof(testArgv02And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And04);
		palladium_test_exs_execute_cmd((sizeof(testArgv02And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And05);

		// 1-1-89
		char testArgv03And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "busckstp", "pcie1_ckstp"};
		char testArgv03And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "busckstp", "pcie1_ckstp", "1"};
		char testArgv03And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "busckstp", "pcie1_ckstp"};
		char testArgv03And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "busckstp", "pcie1_ckstp", "0"};
		char testArgv03And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "busckstp", "pcie1_ckstp"};

		palladium_test_exs_execute_cmd((sizeof(testArgv03And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv03And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And02);
		palladium_test_exs_execute_cmd((sizeof(testArgv03And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And03);
		palladium_test_exs_execute_cmd((sizeof(testArgv03And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And04);
		palladium_test_exs_execute_cmd((sizeof(testArgv03And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And05);

		// 1-1-90
		char testArgv04And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "busckstp", "xdmac_ckstp"};
		char testArgv04And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "busckstp", "xdmac_ckstp", "1"};
		char testArgv04And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "busckstp", "xdmac_ckstp"};
		char testArgv04And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "busckstp", "xdmac_ckstp", "0"};
		char testArgv04And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "busckstp", "xdmac_ckstp"};

		palladium_test_exs_execute_cmd((sizeof(testArgv04And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv04And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And02);
		palladium_test_exs_execute_cmd((sizeof(testArgv04And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And03);
		palladium_test_exs_execute_cmd((sizeof(testArgv04And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And04);
		palladium_test_exs_execute_cmd((sizeof(testArgv04And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And05);

		// 1-1-91
		char testArgv05And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "busckstp", "hdmac_ckstp"};
		char testArgv05And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "busckstp", "hdmac_ckstp", "1"};
		char testArgv05And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "busckstp", "hdmac_ckstp"};
		char testArgv05And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "busckstp", "hdmac_ckstp", "0"};
		char testArgv05And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "busckstp", "hdmac_ckstp"};

		palladium_test_exs_execute_cmd((sizeof(testArgv05And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv05And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv05And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv05And02);
		palladium_test_exs_execute_cmd((sizeof(testArgv05And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv05And03);
		palladium_test_exs_execute_cmd((sizeof(testArgv05And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv05And04);
		palladium_test_exs_execute_cmd((sizeof(testArgv05And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv05And05);

		// 1-1-92
		char testArgv06And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "busckstp", "emmc_ckstp"};
		char testArgv06And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "busckstp", "emmc_ckstp", "1"};
		char testArgv06And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "busckstp", "emmc_ckstp"};
		char testArgv06And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "busckstp", "emmc_ckstp", "0"};
		char testArgv06And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "busckstp", "emmc_ckstp"};

		palladium_test_exs_execute_cmd((sizeof(testArgv06And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv06And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv06And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv06And02);
		palladium_test_exs_execute_cmd((sizeof(testArgv06And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv06And03);
		palladium_test_exs_execute_cmd((sizeof(testArgv06And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv06And04);
		palladium_test_exs_execute_cmd((sizeof(testArgv06And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv06And05);

		// 1-1-93
		char testArgv07And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "busckstp", "sd2_ckstp"};
		char testArgv07And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "busckstp", "sd2_ckstp", "1"};
		char testArgv07And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "busckstp", "sd2_ckstp"};
		char testArgv07And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "busckstp", "sd2_ckstp", "0"};
		char testArgv07And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "busckstp", "sd2_ckstp"};

		palladium_test_exs_execute_cmd((sizeof(testArgv07And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv07And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv07And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv07And02);
		palladium_test_exs_execute_cmd((sizeof(testArgv07And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv07And03);
		palladium_test_exs_execute_cmd((sizeof(testArgv07And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv07And04);
		palladium_test_exs_execute_cmd((sizeof(testArgv07And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv07And05);

		// 1-1-94
		char testArgv08And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "busckstp", "sd3_ckstp"};
		char testArgv08And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "busckstp", "sd3_ckstp", "1"};
		char testArgv08And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "busckstp", "sd3_ckstp"};
		char testArgv08And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "busckstp", "sd3_ckstp", "0"};
		char testArgv08And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "busckstp", "sd3_ckstp"};

		palladium_test_exs_execute_cmd((sizeof(testArgv08And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv08And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv08And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv08And02);
		palladium_test_exs_execute_cmd((sizeof(testArgv08And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv08And03);
		palladium_test_exs_execute_cmd((sizeof(testArgv08And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv08And04);
		palladium_test_exs_execute_cmd((sizeof(testArgv08And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv08And05);

		// 1-1-95
		char testArgv09And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "busckstp", "sd4_ckstp"};
		char testArgv09And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "busckstp", "sd4_ckstp", "1"};
		char testArgv09And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "busckstp", "sd4_ckstp"};
		char testArgv09And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "busckstp", "sd4_ckstp", "0"};
		char testArgv09And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "busckstp", "sd4_ckstp"};

		palladium_test_exs_execute_cmd((sizeof(testArgv09And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv09And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv09And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv09And02);
		palladium_test_exs_execute_cmd((sizeof(testArgv09And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv09And03);
		palladium_test_exs_execute_cmd((sizeof(testArgv09And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv09And04);
		palladium_test_exs_execute_cmd((sizeof(testArgv09And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv09And05);

		// 1-1-96
		char testArgv10And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "busckstp", "netsec_ckstp"};
		char testArgv10And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "busckstp", "netsec_ckstp", "1"};
		char testArgv10And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "busckstp", "netsec_ckstp"};
		char testArgv10And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "busckstp", "netsec_ckstp", "0"};
		char testArgv10And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "busckstp", "netsec_ckstp"};

		palladium_test_exs_execute_cmd((sizeof(testArgv10And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv10And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv10And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv10And02);
		palladium_test_exs_execute_cmd((sizeof(testArgv10And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv10And03);
		palladium_test_exs_execute_cmd((sizeof(testArgv10And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv10And04);
		palladium_test_exs_execute_cmd((sizeof(testArgv10And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv10And05);

		// 1-1-97
		char testArgv11And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "busckstp", "relc_ckstp"};
		char testArgv11And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "busckstp", "relc_ckstp", "1"};
		char testArgv11And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "busckstp", "relc_ckstp"};
		char testArgv11And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "busckstp", "relc_ckstp", "0"};
		char testArgv11And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "busckstp", "relc_ckstp"};

		palladium_test_exs_execute_cmd((sizeof(testArgv11And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv11And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv11And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv11And02);
		palladium_test_exs_execute_cmd((sizeof(testArgv11And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv11And03);
		palladium_test_exs_execute_cmd((sizeof(testArgv11And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv11And04);
		palladium_test_exs_execute_cmd((sizeof(testArgv11And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv11And05);

	/******************************************************************/
	} else if ( testno == 11 ) {		// "NSEC_CKSTP"レジスタのテスト

		char testArgv00And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nsec_ckstp", "netsec_ptpstp", "0"};

		palladium_test_exs_execute_cmd((sizeof(testArgv00And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And01);

		// 1-1-98
		char testArgv01And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nsec_ckstp", "netsec_ptpstp"};
		char testArgv01And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nsec_ckstp", "netsec_ptpstp", "1"};
		char testArgv01And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nsec_ckstp", "netsec_ptpstp"};
		char testArgv01And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nsec_ckstp", "netsec_ptpstp", "0"};
		char testArgv01And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nsec_ckstp", "netsec_ptpstp"};

		palladium_test_exs_execute_cmd((sizeof(testArgv01And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And02);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And03);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And04);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And05);

	/******************************************************************/
	} else if ( testno == 12 ) {		// "EMMC_CKSTP"レジスタのテスト

		char testArgv00And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "emmc_ckstp", "emclkstp", "0"};

		palladium_test_exs_execute_cmd((sizeof(testArgv00And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And01);

		// 1-1-99
		char testArgv01And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "emmc_ckstp", "emclkstp"};
		char testArgv01And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "emmc_ckstp", "emclkstp", "1"};
		char testArgv01And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "emmc_ckstp", "emclkstp"};
		char testArgv01And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "emmc_ckstp", "emclkstp", "0"};
		char testArgv01And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "emmc_ckstp", "emclkstp"};

		palladium_test_exs_execute_cmd((sizeof(testArgv01And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And02);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And03);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And04);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And05);

	/******************************************************************/
	} else if ( testno == 13 ) {		// "EM_DRVSTR"レジスタのテスト

		// 1-1-100
		char testArgv01And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "em_drvstr", "em_dsel"};

		palladium_test_exs_execute_cmd((sizeof(testArgv01And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And01);

	/******************************************************************/
	} else if ( testno == 14 ) {		// "EM_PV_DTIMEC"レジスタのテスト

		char testArgv00And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset", "emcrst", "0"};
		char testArgv00And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "em_pv_dtimec", "pv_dtimec", "0x000000"};

		palladium_test_exs_execute_cmd((sizeof(testArgv00And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv00And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And02);

		// 1-1-101
		char testArgv01And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "em_pv_dtimec", "pv_dtimec"};
		char testArgv01And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "em_pv_dtimec", "pv_dtimec", "0xFFFFFF"};
		char testArgv01And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "em_pv_dtimec", "pv_dtimec"};
		char testArgv01And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "em_pv_dtimec", "pv_dtimec", "0xAAAAAA"};
		char testArgv01And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "em_pv_dtimec", "pv_dtimec"};
		char testArgv01And06[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "em_pv_dtimec", "pv_dtimec", "0x000000"};
		char testArgv01And07[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "em_pv_dtimec", "pv_dtimec"};

		palladium_test_exs_execute_cmd((sizeof(testArgv01And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And02);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And03);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And04);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And05);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And06) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And06);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And07) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And07);

	/******************************************************************/
	} else if ( testno == 15 ) {		// "EM_PV_AMPBL"レジスタのテスト

		char testArgv00And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "em_pvAmpbl", "pvAmpbl", "0"};

		palladium_test_exs_execute_cmd((sizeof(testArgv00And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And01);

		// 1-1-102
		char testArgv01And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "em_pvAmpbl", "pvAmpbl"};
		char testArgv01And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "em_pvAmpbl", "pvAmpbl", "15"};
		char testArgv01And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "em_pvAmpbl", "pvAmpbl"};
		char testArgv01And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "em_pvAmpbl", "pvAmpbl", "0"};
		char testArgv01And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "em_pvAmpbl", "pvAmpbl"};

		palladium_test_exs_execute_cmd((sizeof(testArgv01And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And02);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And03);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And04);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And05);

	/******************************************************************/
	} else if ( testno == 16 ) {		// "EM_CR_SLOTTYPE"レジスタのテスト

		char testArgv00And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset", "emcrst", "0"};
		char testArgv00And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "em_cr_slottype", "cr_slottype", "0"};

		palladium_test_exs_execute_cmd((sizeof(testArgv00And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv00And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And02);

		// 1-1-103
		char testArgv01And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "em_cr_slottype", "cr_slottype"};
		char testArgv01And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "em_cr_slottype", "cr_slottype", "1"};
		char testArgv01And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "em_cr_slottype", "cr_slottype"};
		char testArgv01And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "em_cr_slottype", "cr_slottype", "0"};
		char testArgv01And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "em_cr_slottype", "cr_slottype"};

		palladium_test_exs_execute_cmd((sizeof(testArgv01And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And02);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And03);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And04);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And05);

	/******************************************************************/
	} else if ( testno == 17 ) {		// "EM_CR_BCLKFREQ"レジスタのテスト

		char testArgv00And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset", "emcrst", "0"};
		char testArgv00And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "em_cr_bclkfreq", "cr_bclkfreq", "0"};

		palladium_test_exs_execute_cmd((sizeof(testArgv00And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv00And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And02);

		// 1-1-104
		char testArgv01And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "em_cr_bclkfreq", "cr_bclkfreq"};
		char testArgv01And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "em_cr_bclkfreq", "cr_bclkfreq", "1"};
		char testArgv01And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "em_cr_bclkfreq", "cr_bclkfreq"};
		char testArgv01And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "em_cr_bclkfreq", "cr_bclkfreq", "0"};
		char testArgv01And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "em_cr_bclkfreq", "cr_bclkfreq"};

		palladium_test_exs_execute_cmd((sizeof(testArgv01And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And02);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And03);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And04);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And05);

	/******************************************************************/
	} else if ( testno == 18 ) {		// "EM_CDDET"レジスタのテスト

		char testArgv00And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset", "emcrst", "0"};
		char testArgv00And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "em_cddet", "emcd", "0"};

		palladium_test_exs_execute_cmd((sizeof(testArgv00And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv00And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And02);

		// 1-1-105
		char testArgv01And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "em_cddet", "emcd"};
		char testArgv01And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "em_cddet", "emcd", "1"};
		char testArgv01And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "em_cddet", "emcd"};
		char testArgv01And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "em_cddet", "emcd", "0"};
		char testArgv01And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "em_cddet", "emcd"};

		palladium_test_exs_execute_cmd((sizeof(testArgv01And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And02);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And03);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And04);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And05);

		// 1-1-106
		char testArgv02And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "em_cddet", "emphylk"};

		palladium_test_exs_execute_cmd((sizeof(testArgv02And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And01);

	/******************************************************************/
	} else if ( testno == 19 ) {		// "NF_IP_CTL"レジスタのテスト

		char testArgv00And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_ip_ctl", "dscv_inhibit", "0"};
		char testArgv00And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_ip_ctl", "dscv_ignr_crc", "0"};
		char testArgv00And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_ip_ctl", "boot_en", "0"};
		char testArgv00And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_ip_ctl", "iddq_en", "0"};

		palladium_test_exs_execute_cmd((sizeof(testArgv00And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv00And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And02);
		palladium_test_exs_execute_cmd((sizeof(testArgv00And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And03);
		palladium_test_exs_execute_cmd((sizeof(testArgv00And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And04);

		// 1-1-107
		char testArgv01And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_ip_ctl", "dscv_inhibit"};
		char testArgv01And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_ip_ctl", "dscv_inhibit", "1"};
		char testArgv01And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_ip_ctl", "dscv_inhibit"};
		char testArgv01And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_ip_ctl", "dscv_inhibit", "0"};
		char testArgv01And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_ip_ctl", "dscv_inhibit"};

		palladium_test_exs_execute_cmd((sizeof(testArgv01And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And02);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And03);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And04);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And05);

		// 1-1-108
		char testArgv02And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_ip_ctl", "dscv_ignr_crc"};
		char testArgv02And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_ip_ctl", "dscv_ignr_crc", "1"};
		char testArgv02And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_ip_ctl", "dscv_ignr_crc"};
		char testArgv02And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_ip_ctl", "dscv_ignr_crc", "0"};
		char testArgv02And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_ip_ctl", "dscv_ignr_crc"};

		palladium_test_exs_execute_cmd((sizeof(testArgv02And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv02And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And02);
		palladium_test_exs_execute_cmd((sizeof(testArgv02And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And03);
		palladium_test_exs_execute_cmd((sizeof(testArgv02And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And04);
		palladium_test_exs_execute_cmd((sizeof(testArgv02And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And05);

		// 1-1-109
		char testArgv03And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_ip_ctl", "boot_en"};
		char testArgv03And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_ip_ctl", "boot_en", "1"};
		char testArgv03And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_ip_ctl", "boot_en"};
		char testArgv03And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_ip_ctl", "boot_en", "0"};
		char testArgv03And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_ip_ctl", "boot_en"};

		palladium_test_exs_execute_cmd((sizeof(testArgv03And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv03And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And02);
		palladium_test_exs_execute_cmd((sizeof(testArgv03And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And03);
		palladium_test_exs_execute_cmd((sizeof(testArgv03And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And04);
		palladium_test_exs_execute_cmd((sizeof(testArgv03And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And05);

		// 1-1-110
		char testArgv04And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_ip_ctl", "iddq_en"};
		char testArgv04And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_ip_ctl", "iddq_en", "1"};
		char testArgv04And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_ip_ctl", "iddq_en"};
		char testArgv04And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_ip_ctl", "iddq_en", "0"};
		char testArgv04And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_ip_ctl", "iddq_en"};

		palladium_test_exs_execute_cmd((sizeof(testArgv04And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv04And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And02);
		palladium_test_exs_execute_cmd((sizeof(testArgv04And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And03);
		palladium_test_exs_execute_cmd((sizeof(testArgv04And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And04);
		palladium_test_exs_execute_cmd((sizeof(testArgv04And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And05);

	/******************************************************************/
	} else if ( testno == 20 ) {		// "NF_BTSQ_STATE"レジスタのテスト

		// 1-1-111
		char testArgv01And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_btsq_state", "init_fail"};

		palladium_test_exs_execute_cmd((sizeof(testArgv01And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And01);

		// 1-1-112
		char testArgv02And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_btsq_state", "boot_comp"};

		palladium_test_exs_execute_cmd((sizeof(testArgv02And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And01);

		// 1-1-113
		char testArgv03And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_btsq_state", "boot_error"};

		palladium_test_exs_execute_cmd((sizeof(testArgv03And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And01);

		// 1-1-114
		char testArgv04And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_btsq_state", "boot_busy"};

		palladium_test_exs_execute_cmd((sizeof(testArgv04And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And01);

	/******************************************************************/
	} else if ( testno == 21 ) {		// "NF_RB_VALID_TM"レジスタのテスト

		char testArgv00And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_rb_valid_tm", "rb_valid_time", "0x0000"};

		palladium_test_exs_execute_cmd((sizeof(testArgv00And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And01);

		// 1-1-115
		char testArgv01And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_rb_valid_tm", "rb_valid_time"};
		char testArgv01And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_rb_valid_tm", "rb_valid_time", "0xFFFF"};
		char testArgv01And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_rb_valid_tm", "rb_valid_time"};
		char testArgv01And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_rb_valid_tm", "rb_valid_time", "0xAAAA"};
		char testArgv01And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_rb_valid_tm", "rb_valid_time"};
		char testArgv01And06[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_rb_valid_tm", "rb_valid_time", "0x0000"};
		char testArgv01And07[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_rb_valid_tm", "rb_valid_time"};

		palladium_test_exs_execute_cmd((sizeof(testArgv01And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And02);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And03);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And04);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And05);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And06) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And06);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And07) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And07);

	/******************************************************************/
	} else if ( testno == 22 ) {		// "NF_PHY_CTRL_REG"レジスタのテスト

		char testArgv00And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_phy_ctrl_reg", "phy_ctrl", "0x00000000"};

		palladium_test_exs_execute_cmd((sizeof(testArgv00And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And01);

		// 1-1-116
		char testArgv01And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_phy_ctrl_reg", "phy_ctrl"};
		char testArgv01And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_phy_ctrl_reg", "phy_ctrl", "0xFFFFFFFF"};
		char testArgv01And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_phy_ctrl_reg", "phy_ctrl"};
		char testArgv01And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_phy_ctrl_reg", "phy_ctrl", "0xAAAAAAAA"};
		char testArgv01And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_phy_ctrl_reg", "phy_ctrl"};
		char testArgv01And06[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_phy_ctrl_reg", "phy_ctrl", "0x00000000"};
		char testArgv01And07[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_phy_ctrl_reg", "phy_ctrl"};

		palladium_test_exs_execute_cmd((sizeof(testArgv01And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And02);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And03);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And04);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And05);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And06) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And06);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And07) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And07);

	/******************************************************************/
	} else if ( testno == 23 ) {		// "NF_PHY_DQ_TIM"レジスタのテスト

		char testArgv00And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_phy_dq_tim", "phy_dq_timing", "0x00000000"};

		palladium_test_exs_execute_cmd((sizeof(testArgv00And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And01);

		// 1-1-117
		char testArgv01And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_phy_dq_tim", "phy_dq_timing"};
		char testArgv01And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_phy_dq_tim", "phy_dq_timing", "0xFFFFFFFF"};
		char testArgv01And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_phy_dq_tim", "phy_dq_timing"};
		char testArgv01And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_phy_dq_tim", "phy_dq_timing", "0xAAAAAAAA"};
		char testArgv01And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_phy_dq_tim", "phy_dq_timing"};
		char testArgv01And06[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_phy_dq_tim", "phy_dq_timing", "0x00000000"};
		char testArgv01And07[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_phy_dq_tim", "phy_dq_timing"};

		palladium_test_exs_execute_cmd((sizeof(testArgv01And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And02);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And03);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And04);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And05);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And06) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And06);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And07) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And07);

	/******************************************************************/
	} else if ( testno == 23 ) {		// "NF_PHY_DQS_TIM"レジスタのテスト

		char testArgv00And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_phy_dqs_tim", "phy_dqs_timing", "0x00000000"};

		palladium_test_exs_execute_cmd((sizeof(testArgv00And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And01);

		// 1-1-118
		char testArgv01And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_phy_dqs_tim", "phy_dqs_timing"};
		char testArgv01And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_phy_dqs_tim", "phy_dqs_timing", "0xFFFFFFFF"};
		char testArgv01And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_phy_dqs_tim", "phy_dqs_timing"};
		char testArgv01And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_phy_dqs_tim", "phy_dqs_timing", "0xAAAAAAAA"};
		char testArgv01And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_phy_dqs_tim", "phy_dqs_timing"};
		char testArgv01And06[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_phy_dqs_tim", "phy_dqs_timing", "0x00000000"};
		char testArgv01And07[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_phy_dqs_tim", "phy_dqs_timing"};

		palladium_test_exs_execute_cmd((sizeof(testArgv01And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And02);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And03);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And04);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And05);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And06) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And06);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And07) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And07);

	/******************************************************************/
	} else if ( testno == 24 ) {		// "NF_PHY_GT_LPBK"レジスタのテスト

		char testArgv00And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_phy_gt_lpbk", "phy_gt_lpbk_ctl", "0x00000000"};

		palladium_test_exs_execute_cmd((sizeof(testArgv00And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And01);

		// 1-1-119
		char testArgv01And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_phy_gt_lpbk", "phy_gt_lpbk_ctl"};
		char testArgv01And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_phy_gt_lpbk", "phy_gt_lpbk_ctl", "0xFFFFFFFF"};
		char testArgv01And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_phy_gt_lpbk", "phy_gt_lpbk_ctl"};
		char testArgv01And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_phy_gt_lpbk", "phy_gt_lpbk_ctl", "0xAAAAAAAA"};
		char testArgv01And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_phy_gt_lpbk", "phy_gt_lpbk_ctl"};
		char testArgv01And06[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_phy_gt_lpbk", "phy_gt_lpbk_ctl", "0x00000000"};
		char testArgv01And07[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_phy_gt_lpbk", "phy_gt_lpbk_ctl"};

		palladium_test_exs_execute_cmd((sizeof(testArgv01And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And02);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And03);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And04);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And05);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And06) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And06);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And07) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And07);

	/******************************************************************/
	} else if ( testno == 25 ) {		// "NF_PHY_DLL_MCTL"レジスタのテスト

		char testArgv00And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_phy_dll_mctl", "phy_dll_mst_ctl", "0x00000000"};

		palladium_test_exs_execute_cmd((sizeof(testArgv00And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And01);

		// 1-1-120
		char testArgv01And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_phy_dll_mctl", "phy_dll_mst_ctl"};
		char testArgv01And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_phy_dll_mctl", "phy_dll_mst_ctl", "0xFFFFFFFF"};
		char testArgv01And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_phy_dll_mctl", "phy_dll_mst_ctl"};
		char testArgv01And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_phy_dll_mctl", "phy_dll_mst_ctl", "0xAAAAAAAA"};
		char testArgv01And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_phy_dll_mctl", "phy_dll_mst_ctl"};
		char testArgv01And06[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_phy_dll_mctl", "phy_dll_mst_ctl", "0x00000000"};
		char testArgv01And07[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_phy_dll_mctl", "phy_dll_mst_ctl"};

		palladium_test_exs_execute_cmd((sizeof(testArgv01And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And02);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And03);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And04);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And05);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And06) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And06);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And07) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And07);

	/******************************************************************/
	} else if ( testno == 26 ) {		// "NF_PHY_DLL_SCTL"レジスタのテスト

		char testArgv00And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_phy_dll_sctl", "phy_dll_slv_ctl", "0x00000000"};

		palladium_test_exs_execute_cmd((sizeof(testArgv00And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And01);

		// 1-1-121
		char testArgv01And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_phy_dll_sctl", "phy_dll_slv_ctl"};
		char testArgv01And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_phy_dll_sctl", "phy_dll_slv_ctl", "0xFFFFFFFF"};
		char testArgv01And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_phy_dll_sctl", "phy_dll_slv_ctl"};
		char testArgv01And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_phy_dll_sctl", "phy_dll_slv_ctl", "0xAAAAAAAA"};
		char testArgv01And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_phy_dll_sctl", "phy_dll_slv_ctl"};
		char testArgv01And06[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_phy_dll_sctl", "phy_dll_slv_ctl", "0x00000000"};
		char testArgv01And07[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_phy_dll_sctl", "phy_dll_slv_ctl"};

		palladium_test_exs_execute_cmd((sizeof(testArgv01And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And02);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And03);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And04);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And05);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And06) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And06);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And07) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And07);

	/******************************************************************/
	} else if ( testno == 27 ) {		// "NF_BOOT_ECC_CTL"レジスタのテスト

		char testArgv00And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_boot_ecc_ctl", "boot_ecc_sec_siz", "0"};
		char testArgv00And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_boot_ecc_ctl", "bt_ecc_corr_str", "0"};
		char testArgv00And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_boot_ecc_ctl", "boot_ecc_en", "0"};

		palladium_test_exs_execute_cmd((sizeof(testArgv00And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv00And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And02);
		palladium_test_exs_execute_cmd((sizeof(testArgv00And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And03);

		// 1-1-122
		char testArgv01And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_boot_ecc_ctl", "boot_ecc_sec_siz"};
		char testArgv01And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_boot_ecc_ctl", "boot_ecc_sec_siz", "1"};
		char testArgv01And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_boot_ecc_ctl", "boot_ecc_sec_siz"};
		char testArgv01And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_boot_ecc_ctl", "boot_ecc_sec_siz", "0"};
		char testArgv01And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_boot_ecc_ctl", "boot_ecc_sec_siz"};

		palladium_test_exs_execute_cmd((sizeof(testArgv01And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And02);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And03);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And04);
		palladium_test_exs_execute_cmd((sizeof(testArgv01And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And05);

		// 1-1-123
		char testArgv02And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_boot_ecc_ctl", "bt_ecc_corr_str"};
		char testArgv02And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_boot_ecc_ctl", "bt_ecc_corr_str", "1"};
		char testArgv02And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_boot_ecc_ctl", "bt_ecc_corr_str"};
		char testArgv02And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_boot_ecc_ctl", "bt_ecc_corr_str", "0"};
		char testArgv02And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_boot_ecc_ctl", "bt_ecc_corr_str"};

		palladium_test_exs_execute_cmd((sizeof(testArgv02And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv02And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And02);
		palladium_test_exs_execute_cmd((sizeof(testArgv02And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And03);
		palladium_test_exs_execute_cmd((sizeof(testArgv02And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And04);
		palladium_test_exs_execute_cmd((sizeof(testArgv02And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And05);

		// 1-1-124
		char testArgv03And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_boot_ecc_ctl", "boot_ecc_en"};
		char testArgv03And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_boot_ecc_ctl", "boot_ecc_en", "1"};
		char testArgv03And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_boot_ecc_ctl", "boot_ecc_en"};
		char testArgv03And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "nf_boot_ecc_ctl", "boot_ecc_en", "0"};
		char testArgv03And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "nf_boot_ecc_ctl", "boot_ecc_en"};

		palladium_test_exs_execute_cmd((sizeof(testArgv03And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And01);
		palladium_test_exs_execute_cmd((sizeof(testArgv03And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And02);
		palladium_test_exs_execute_cmd((sizeof(testArgv03And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And03);
		palladium_test_exs_execute_cmd((sizeof(testArgv03And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And04);
		palladium_test_exs_execute_cmd((sizeof(testArgv03And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And05);

	/******************************************************************/
	} else {
		// 例外パラメータ指定
		Ddim_Print(( "Parameters of the excluded\n" ));
	}
	// タイマーログ出力(処理時間出力)
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_PRINT );

	Ddim_Print(( "EXS Palladium test No %d End\n", testno ));

	// Force stop
	Palladium_Force_Stop();
}






PalladiumTestExs* palladium_test_exs_new(void)
{
	PalladiumTestExs *self = k_object_new_with_private(PALLADIUM_TYPE_TEST_EXS,sizeof(PalladiumTestExsPrivate));
	return self;
}
