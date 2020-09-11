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

#include "ddim_user_custom.h"
#include "palladium_test_common.h"
#include "palladium_test.h"
#include "dd_gic.h"
#include "dd_top.h"
#include "ct_dd_exs.h"
#include "palladiumtestmainexs.h"
#include "palladiumtestexs.h"



K_TYPE_DEFINE_WITH_PRIVATE(PalladiumTestMainExs, palladium_test_main_exs);
#define PALLADIUM_TEST_MAIN_EXS_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), PalladiumTestMainExsPrivate,PALLADIUM_TYPE_TEST_MAIN_EXS))

struct _PalladiumTestMainExsPrivate
{
	int a;
};

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/

static void palladium_test_main_exs_constructor(PalladiumTestMainExs *self)
{
	PalladiumTestMainExsPrivate *priv = PALLADIUM_TEST_MAIN_EXS_GET_PRIVATE(self);
	priv->a = 0;
}

static void palladium_test_main_exs_destructor(PalladiumTestMainExs *self)
{
}

VOID 	palladium_test_main_exs_testno( UCHAR testno )
{

	// レジスタ取得＆設定(#define PC_DEBUG を定義すること)
	/******************************************************************/
	if ( testno == 1 ) {	// "XD_LPC (XDMAC LowPower Control)"レジスタのテスト

		// 1-1-1 , 1-1-2 , 1-1-3
		char testArgv01And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "xd_lpc", "csysreq", "0"};
		char testArgv01And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "xd_lpc", "csysreq"};
		char testArgv01And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "xd_lpc", "csysack"};
		char testArgv01And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "xd_lpc", "cactrive"};
		char testArgv01And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "xd_lpc", "csysreq", "1"};
		char testArgv01And06[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "xd_lpc", "csysreq"};
		char testArgv01And07[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "xd_lpc", "csysack"};
		char testArgv01And08[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "xd_lpc", "cactrive"};
		char testArgv01And09[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "xd_lpc", "csysreq", "0"};
		char testArgv01And10[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "xd_lpc", "csysreq"};
		char testArgv01And11[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "xd_lpc", "csysack"};
		char testArgv01And12[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "xd_lpc", "cactrive"};

		ptDdExsExecuteCmd((sizeof(testArgv01And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And01);
		ptDdExsExecuteCmd((sizeof(testArgv01And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And02);
		ptDdExsExecuteCmd((sizeof(testArgv01And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And03);
		ptDdExsExecuteCmd((sizeof(testArgv01And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And04);
		ptDdExsExecuteCmd((sizeof(testArgv01And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And05);
		ptDdExsExecuteCmd((sizeof(testArgv01And06) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And06);
		ptDdExsExecuteCmd((sizeof(testArgv01And07) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And07);
		ptDdExsExecuteCmd((sizeof(testArgv01And08) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And08);
		ptDdExsExecuteCmd((sizeof(testArgv01And09) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And09);
		ptDdExsExecuteCmd((sizeof(testArgv01And10) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And10);
		ptDdExsExecuteCmd((sizeof(testArgv01And11) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And11);
		ptDdExsExecuteCmd((sizeof(testArgv01And12) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And12);

	/******************************************************************/
	} else if ( testno == 2 ) {		// "SOFTRESET"レジスタのテスト

		char testArgv00And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset", "nfrstn", "0"};
		char testArgv00And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset", "nfrstnbch", "0"};
		char testArgv00And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset", "nfrstnreg", "0"};
		char testArgv00And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset", "netsecrst", "0"};
		char testArgv00And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset", "emcrst", "0"};
		char testArgv00And06[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset", "relcrst", "0"};

		ptDdExsExecuteCmd((sizeof(testArgv00And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And01);
		ptDdExsExecuteCmd((sizeof(testArgv00And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And02);
		ptDdExsExecuteCmd((sizeof(testArgv00And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And03);
		ptDdExsExecuteCmd((sizeof(testArgv00And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And04);
		ptDdExsExecuteCmd((sizeof(testArgv00And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And05);
		ptDdExsExecuteCmd((sizeof(testArgv00And06) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And06);

		// 1-1-4
		char testArgv01And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset", "nfrstn"};
		char testArgv01And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset", "nfrstn", "1"};
		char testArgv01And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset", "nfrstn"};
		char testArgv01And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset", "nfrstn", "0"};
		char testArgv01And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset", "nfrstn"};

		ptDdExsExecuteCmd((sizeof(testArgv01And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And01);
		ptDdExsExecuteCmd((sizeof(testArgv01And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And02);
		ptDdExsExecuteCmd((sizeof(testArgv01And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And03);
		ptDdExsExecuteCmd((sizeof(testArgv01And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And04);
		ptDdExsExecuteCmd((sizeof(testArgv01And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And05);

		// 1-1-5
		char testArgv02And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset", "nfrstnbch"};
		char testArgv02And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset", "nfrstnbch", "1"};
		char testArgv02And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset", "nfrstnbch"};
		char testArgv02And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset", "nfrstnbch", "0"};
		char testArgv02And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset", "nfrstnbch"};

		ptDdExsExecuteCmd((sizeof(testArgv02And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And01);
		ptDdExsExecuteCmd((sizeof(testArgv02And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And02);
		ptDdExsExecuteCmd((sizeof(testArgv02And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And03);
		ptDdExsExecuteCmd((sizeof(testArgv02And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And04);
		ptDdExsExecuteCmd((sizeof(testArgv02And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And05);

		// 1-1-6
		char testArgv03And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset", "nfrstnreg"};
		char testArgv03And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset", "nfrstnreg", "1"};
		char testArgv03And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset", "nfrstnreg"};
		char testArgv03And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset", "nfrstnreg", "0"};
		char testArgv03And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset", "nfrstnreg"};

		ptDdExsExecuteCmd((sizeof(testArgv03And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And01);
		ptDdExsExecuteCmd((sizeof(testArgv03And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And02);
		ptDdExsExecuteCmd((sizeof(testArgv03And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And03);
		ptDdExsExecuteCmd((sizeof(testArgv03And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And04);
		ptDdExsExecuteCmd((sizeof(testArgv03And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And05);

		// 1-1-7
		char testArgv04And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset", "netsecrst"};
		char testArgv04And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset", "netsecrst", "1"};
		char testArgv04And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset", "netsecrst"};
		char testArgv04And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset", "netsecrst", "0"};
		char testArgv04And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset", "netsecrst"};

		ptDdExsExecuteCmd((sizeof(testArgv04And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And01);
		ptDdExsExecuteCmd((sizeof(testArgv04And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And02);
		ptDdExsExecuteCmd((sizeof(testArgv04And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And03);
		ptDdExsExecuteCmd((sizeof(testArgv04And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And04);
		ptDdExsExecuteCmd((sizeof(testArgv04And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And05);

		// 1-1-8
		char testArgv05And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset", "emcrst"};
		char testArgv05And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset", "emcrst", "1"};
		char testArgv05And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset", "emcrst"};
		char testArgv05And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset", "emcrst", "0"};
		char testArgv05And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset", "emcrst"};

		ptDdExsExecuteCmd((sizeof(testArgv05And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv05And01);
		ptDdExsExecuteCmd((sizeof(testArgv05And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv05And02);
		ptDdExsExecuteCmd((sizeof(testArgv05And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv05And03);
		ptDdExsExecuteCmd((sizeof(testArgv05And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv05And04);
		ptDdExsExecuteCmd((sizeof(testArgv05And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv05And05);

		// 1-1-9
		char testArgv06And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset", "relcrst"};
		char testArgv06And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset", "relcrst", "1"};
		char testArgv06And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset", "relcrst"};
		char testArgv06And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset", "relcrst", "0"};
		char testArgv06And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset", "relcrst"};

		ptDdExsExecuteCmd((sizeof(testArgv06And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv06And01);
		ptDdExsExecuteCmd((sizeof(testArgv06And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv06And02);
		ptDdExsExecuteCmd((sizeof(testArgv06And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv06And03);
		ptDdExsExecuteCmd((sizeof(testArgv06And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv06And04);
		ptDdExsExecuteCmd((sizeof(testArgv06And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv06And05);

	/******************************************************************/
	} else if ( testno == 3 ) {		// "SOFTRESET2"レジスタのテスト

		char testArgv00And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "debretx_sd3", "0"};
		char testArgv00And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "debretx_sd4", "0"};
		char testArgv00And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "debretx_pcie0", "0"};
		char testArgv00And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "debretx_pcie1", "0"};
		char testArgv00And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "debretx_usb2vbus", "0"};
		char testArgv00And06[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "debretx_usb2id", "0"};
		char testArgv00And07[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "debretx_usb3vbus", "0"};
		char testArgv00And08[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "debretx_usb3id", "0"};

		ptDdExsExecuteCmd((sizeof(testArgv00And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And01);
		ptDdExsExecuteCmd((sizeof(testArgv00And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And02);
		ptDdExsExecuteCmd((sizeof(testArgv00And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And03);
		ptDdExsExecuteCmd((sizeof(testArgv00And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And04);
		ptDdExsExecuteCmd((sizeof(testArgv00And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And05);
		ptDdExsExecuteCmd((sizeof(testArgv00And06) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And06);
		ptDdExsExecuteCmd((sizeof(testArgv00And07) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And07);
		ptDdExsExecuteCmd((sizeof(testArgv00And08) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And08);

		// 1-1-10
		char testArgv01And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset2", "debretx_sd3"};
		char testArgv01And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "debretx_sd3", "1"};
		char testArgv01And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset2", "debretx_sd3"};
		char testArgv01And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "debretx_sd3", "0"};
		char testArgv01And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset2", "debretx_sd3"};

		ptDdExsExecuteCmd((sizeof(testArgv01And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And01);
		ptDdExsExecuteCmd((sizeof(testArgv01And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And02);
		ptDdExsExecuteCmd((sizeof(testArgv01And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And03);
		ptDdExsExecuteCmd((sizeof(testArgv01And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And04);
		ptDdExsExecuteCmd((sizeof(testArgv01And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And05);

		// 1-1-11
		char testArgv02And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset2", "debretx_sd4"};
		char testArgv02And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "debretx_sd4", "1"};
		char testArgv02And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset2", "debretx_sd3"};
		char testArgv02And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "debretx_sd4", "0"};
		char testArgv02And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset2", "debretx_sd3"};

		ptDdExsExecuteCmd((sizeof(testArgv02And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And01);
		ptDdExsExecuteCmd((sizeof(testArgv02And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And02);
		ptDdExsExecuteCmd((sizeof(testArgv02And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And03);
		ptDdExsExecuteCmd((sizeof(testArgv02And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And04);
		ptDdExsExecuteCmd((sizeof(testArgv02And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And05);

		// 1-1-12
		char testArgv03And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset2", "debretx_pcie0"};
		char testArgv03And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "debretx_pcie0", "1"};
		char testArgv03And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset2", "debretx_pcie0"};
		char testArgv03And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "debretx_pcie0", "0"};
		char testArgv03And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset2", "debretx_pcie0"};

		ptDdExsExecuteCmd((sizeof(testArgv03And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And01);
		ptDdExsExecuteCmd((sizeof(testArgv03And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And02);
		ptDdExsExecuteCmd((sizeof(testArgv03And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And03);
		ptDdExsExecuteCmd((sizeof(testArgv03And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And04);
		ptDdExsExecuteCmd((sizeof(testArgv03And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And05);

		// 1-1-13
		char testArgv04And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset2", "debretx_pcie1"};
		char testArgv04And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "debretx_pcie1", "1"};
		char testArgv04And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset2", "debretx_pcie1"};
		char testArgv04And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "debretx_pcie1", "0"};
		char testArgv04And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset2", "debretx_pcie1"};

		ptDdExsExecuteCmd((sizeof(testArgv04And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And01);
		ptDdExsExecuteCmd((sizeof(testArgv04And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And02);
		ptDdExsExecuteCmd((sizeof(testArgv04And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And03);
		ptDdExsExecuteCmd((sizeof(testArgv04And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And04);
		ptDdExsExecuteCmd((sizeof(testArgv04And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And05);

		// 1-1-14
		char testArgv05And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset2", "debretx_usb2vbus"};
		char testArgv05And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "debretx_usb2vbus", "1"};
		char testArgv05And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset2", "debretx_usb2vbus"};
		char testArgv05And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "debretx_usb2vbus", "0"};
		char testArgv05And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset2", "debretx_usb2vbus"};

		ptDdExsExecuteCmd((sizeof(testArgv05And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv05And01);
		ptDdExsExecuteCmd((sizeof(testArgv05And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv05And02);
		ptDdExsExecuteCmd((sizeof(testArgv05And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv05And03);
		ptDdExsExecuteCmd((sizeof(testArgv05And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv05And04);
		ptDdExsExecuteCmd((sizeof(testArgv05And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv05And05);

		// 1-1-15
		char testArgv06And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset2", "debretx_usb2id"};
		char testArgv06And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "debretx_usb2id", "1"};
		char testArgv06And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset2", "debretx_usb2id"};
		char testArgv06And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "debretx_usb2id", "0"};
		char testArgv06And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset2", "debretx_usb2id"};

		ptDdExsExecuteCmd((sizeof(testArgv06And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv06And01);
		ptDdExsExecuteCmd((sizeof(testArgv06And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv06And02);
		ptDdExsExecuteCmd((sizeof(testArgv06And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv06And03);
		ptDdExsExecuteCmd((sizeof(testArgv06And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv06And04);
		ptDdExsExecuteCmd((sizeof(testArgv06And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv06And05);

		// 1-1-16
		char testArgv07And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset2", "debretx_usb3vbus"};
		char testArgv07And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "debretx_usb3vbus", "1"};
		char testArgv07And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset2", "debretx_usb3vbus"};
		char testArgv07And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "debretx_usb3vbus", "0"};
		char testArgv07And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset2", "debretx_usb3vbus"};

		ptDdExsExecuteCmd((sizeof(testArgv07And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv07And01);
		ptDdExsExecuteCmd((sizeof(testArgv07And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv07And02);
		ptDdExsExecuteCmd((sizeof(testArgv07And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv07And03);
		ptDdExsExecuteCmd((sizeof(testArgv07And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv07And04);
		ptDdExsExecuteCmd((sizeof(testArgv07And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv07And05);

		// 1-1-17
		char testArgv08And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset2", "debretx_usb3id"};
		char testArgv08And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "debretx_usb3id", "1"};
		char testArgv08And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset2", "debretx_usb3id"};
		char testArgv08And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "debretx_usb3id", "0"};
		char testArgv08And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "softreset2", "debretx_usb3id"};

		ptDdExsExecuteCmd((sizeof(testArgv08And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv08And01);
		ptDdExsExecuteCmd((sizeof(testArgv08And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv08And02);
		ptDdExsExecuteCmd((sizeof(testArgv08And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv08And03);
		ptDdExsExecuteCmd((sizeof(testArgv08And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv08And04);
		ptDdExsExecuteCmd((sizeof(testArgv08And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv08And05);

	/******************************************************************/
	} else if ( testno == 4 ) {	 		// "INTMSK"レジスタのテスト

		char testArgv00And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk02", "0"};
		char testArgv00And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk03", "0"};
		char testArgv00And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk04", "0"};
		char testArgv00And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk05", "0"};
		char testArgv00And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk06", "0"};
		char testArgv00And06[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk07", "0"};
		char testArgv00And07[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk08", "0"};
		char testArgv00And08[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk09", "0"};
		char testArgv00And09[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk10", "0"};
		char testArgv00And10[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk11", "0"};
		char testArgv00And11[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk12", "0"};
		char testArgv00And12[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk13", "0"};
		char testArgv00And13[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk14", "0"};
		char testArgv00And14[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk15", "0"};
		char testArgv00And15[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk16", "0"};
		char testArgv00And16[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk17", "0"};

		ptDdExsExecuteCmd((sizeof(testArgv00And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And01);
		ptDdExsExecuteCmd((sizeof(testArgv00And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And02);
		ptDdExsExecuteCmd((sizeof(testArgv00And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And03);
		ptDdExsExecuteCmd((sizeof(testArgv00And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And04);
		ptDdExsExecuteCmd((sizeof(testArgv00And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And05);
		ptDdExsExecuteCmd((sizeof(testArgv00And06) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And06);
		ptDdExsExecuteCmd((sizeof(testArgv00And07) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And07);
		ptDdExsExecuteCmd((sizeof(testArgv00And08) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And08);
		ptDdExsExecuteCmd((sizeof(testArgv00And09) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And09);
		ptDdExsExecuteCmd((sizeof(testArgv00And10) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And10);
		ptDdExsExecuteCmd((sizeof(testArgv00And11) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And11);
		ptDdExsExecuteCmd((sizeof(testArgv00And12) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And12);
		ptDdExsExecuteCmd((sizeof(testArgv00And13) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And13);
		ptDdExsExecuteCmd((sizeof(testArgv00And14) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And14);
		ptDdExsExecuteCmd((sizeof(testArgv00And15) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And15);
		ptDdExsExecuteCmd((sizeof(testArgv00And16) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And16);

		// 1-1-18
		char testArgv01And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk02"};
		char testArgv01And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk02", "1"};
		char testArgv01And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk02"};
		char testArgv01And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk02", "0"};
		char testArgv01And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk02"};

		ptDdExsExecuteCmd((sizeof(testArgv01And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And01);
		ptDdExsExecuteCmd((sizeof(testArgv01And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And02);
		ptDdExsExecuteCmd((sizeof(testArgv01And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And03);
		ptDdExsExecuteCmd((sizeof(testArgv01And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And04);
		ptDdExsExecuteCmd((sizeof(testArgv01And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And05);

		// 1-1-19
		char testArgv02And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk03"};
		char testArgv02And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk03", "1"};
		char testArgv02And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk03"};
		char testArgv02And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk03", "0"};
		char testArgv02And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk03"};

		ptDdExsExecuteCmd((sizeof(testArgv02And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And01);
		ptDdExsExecuteCmd((sizeof(testArgv02And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And02);
		ptDdExsExecuteCmd((sizeof(testArgv02And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And03);
		ptDdExsExecuteCmd((sizeof(testArgv02And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And04);
		ptDdExsExecuteCmd((sizeof(testArgv02And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And05);

		// 1-1-20
		char testArgv03And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk04"};
		char testArgv03And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk04", "1"};
		char testArgv03And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk04"};
		char testArgv03And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk04", "0"};
		char testArgv03And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk04"};

		ptDdExsExecuteCmd((sizeof(testArgv03And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And01);
		ptDdExsExecuteCmd((sizeof(testArgv03And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And02);
		ptDdExsExecuteCmd((sizeof(testArgv03And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And03);
		ptDdExsExecuteCmd((sizeof(testArgv03And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And04);
		ptDdExsExecuteCmd((sizeof(testArgv03And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And05);

		// 1-1-21
		char testArgv04And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk05"};
		char testArgv04And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk05", "1"};
		char testArgv04And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk05"};
		char testArgv04And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk05", "0"};
		char testArgv04And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk05"};

		ptDdExsExecuteCmd((sizeof(testArgv04And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And01);
		ptDdExsExecuteCmd((sizeof(testArgv04And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And02);
		ptDdExsExecuteCmd((sizeof(testArgv04And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And03);
		ptDdExsExecuteCmd((sizeof(testArgv04And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And04);
		ptDdExsExecuteCmd((sizeof(testArgv04And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And05);

		// 1-1-22
		char testArgv05And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk06"};
		char testArgv05And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk06", "1"};
		char testArgv05And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk06"};
		char testArgv05And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk06", "0"};
		char testArgv05And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk06"};

		ptDdExsExecuteCmd((sizeof(testArgv05And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv05And01);
		ptDdExsExecuteCmd((sizeof(testArgv05And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv05And02);
		ptDdExsExecuteCmd((sizeof(testArgv05And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv05And03);
		ptDdExsExecuteCmd((sizeof(testArgv05And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv05And04);
		ptDdExsExecuteCmd((sizeof(testArgv05And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv05And05);

		// 1-1-23
		char testArgv06And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk07"};
		char testArgv06And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk07", "1"};
		char testArgv06And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk07"};
		char testArgv06And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk07", "0"};
		char testArgv06And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk07"};

		ptDdExsExecuteCmd((sizeof(testArgv06And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv06And01);
		ptDdExsExecuteCmd((sizeof(testArgv06And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv06And02);
		ptDdExsExecuteCmd((sizeof(testArgv06And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv06And03);
		ptDdExsExecuteCmd((sizeof(testArgv06And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv06And04);
		ptDdExsExecuteCmd((sizeof(testArgv06And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv06And05);

		// 1-1-24
		char testArgv07And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk08"};
		char testArgv07And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk08", "1"};
		char testArgv07And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk08"};
		char testArgv07And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk08", "0"};
		char testArgv07And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk08"};

		ptDdExsExecuteCmd((sizeof(testArgv07And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv07And01);
		ptDdExsExecuteCmd((sizeof(testArgv07And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv07And02);
		ptDdExsExecuteCmd((sizeof(testArgv07And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv07And03);
		ptDdExsExecuteCmd((sizeof(testArgv07And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv07And04);
		ptDdExsExecuteCmd((sizeof(testArgv07And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv07And05);

		// 1-1-25
		char testArgv08And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk09"};
		char testArgv08And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk09", "1"};
		char testArgv08And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk09"};
		char testArgv08And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk09", "0"};
		char testArgv08And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk09"};

		ptDdExsExecuteCmd((sizeof(testArgv08And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv08And01);
		ptDdExsExecuteCmd((sizeof(testArgv08And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv08And02);
		ptDdExsExecuteCmd((sizeof(testArgv08And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv08And03);
		ptDdExsExecuteCmd((sizeof(testArgv08And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv08And04);
		ptDdExsExecuteCmd((sizeof(testArgv08And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv08And05);

		// 1-1-26
		char testArgv09And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk10"};
		char testArgv09And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk10", "1"};
		char testArgv09And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk10"};
		char testArgv09And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk10", "0"};
		char testArgv09And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk10"};

		ptDdExsExecuteCmd((sizeof(testArgv09And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv09And01);
		ptDdExsExecuteCmd((sizeof(testArgv09And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv09And02);
		ptDdExsExecuteCmd((sizeof(testArgv09And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv09And03);
		ptDdExsExecuteCmd((sizeof(testArgv09And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv09And04);
		ptDdExsExecuteCmd((sizeof(testArgv09And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv09And05);

		// 1-1-27
		char testArgv10And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk11"};
		char testArgv10And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk11", "1"};
		char testArgv10And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk11"};
		char testArgv10And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk11", "0"};
		char testArgv10And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk11"};

		ptDdExsExecuteCmd((sizeof(testArgv10And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv10And01);
		ptDdExsExecuteCmd((sizeof(testArgv10And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv10And02);
		ptDdExsExecuteCmd((sizeof(testArgv10And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv10And03);
		ptDdExsExecuteCmd((sizeof(testArgv10And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv10And04);
		ptDdExsExecuteCmd((sizeof(testArgv10And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv10And05);

		// 1-1-28
		char testArgv11And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk12"};
		char testArgv11And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk12", "1"};
		char testArgv11And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk12"};
		char testArgv11And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk12", "0"};
		char testArgv11And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk12"};

		ptDdExsExecuteCmd((sizeof(testArgv11And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv11And01);
		ptDdExsExecuteCmd((sizeof(testArgv11And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv11And02);
		ptDdExsExecuteCmd((sizeof(testArgv11And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv11And03);
		ptDdExsExecuteCmd((sizeof(testArgv11And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv11And04);
		ptDdExsExecuteCmd((sizeof(testArgv11And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv11And05);

		// 1-1-29
		char testArgv12And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk13"};
		char testArgv12And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk13", "1"};
		char testArgv12And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk13"};
		char testArgv12And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk13", "0"};
		char testArgv12And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk13"};

		ptDdExsExecuteCmd((sizeof(testArgv12And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv12And01);
		ptDdExsExecuteCmd((sizeof(testArgv12And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv12And02);
		ptDdExsExecuteCmd((sizeof(testArgv12And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv12And03);
		ptDdExsExecuteCmd((sizeof(testArgv12And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv12And04);
		ptDdExsExecuteCmd((sizeof(testArgv12And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv12And05);

		// 1-1-30
		char testArgv13And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk14"};
		char testArgv13And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk14", "1"};
		char testArgv13And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk14"};
		char testArgv13And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk14", "0"};
		char testArgv13And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk14"};

		ptDdExsExecuteCmd((sizeof(testArgv13And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv13And01);
		ptDdExsExecuteCmd((sizeof(testArgv13And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv13And02);
		ptDdExsExecuteCmd((sizeof(testArgv13And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv13And03);
		ptDdExsExecuteCmd((sizeof(testArgv13And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv13And04);
		ptDdExsExecuteCmd((sizeof(testArgv13And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv13And05);

		// 1-1-31
		char testArgv14And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk15"};
		char testArgv14And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk15", "1"};
		char testArgv14And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk15"};
		char testArgv14And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk15", "0"};
		char testArgv14And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk15"};

		ptDdExsExecuteCmd((sizeof(testArgv14And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv14And01);
		ptDdExsExecuteCmd((sizeof(testArgv14And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv14And02);
		ptDdExsExecuteCmd((sizeof(testArgv14And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv14And03);
		ptDdExsExecuteCmd((sizeof(testArgv14And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv14And04);
		ptDdExsExecuteCmd((sizeof(testArgv14And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv14And05);

		// 1-1-32
		char testArgv15And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk16"};
		char testArgv15And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk16", "1"};
		char testArgv15And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk16"};
		char testArgv15And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk16", "0"};
		char testArgv15And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk16"};

		ptDdExsExecuteCmd((sizeof(testArgv15And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv15And01);
		ptDdExsExecuteCmd((sizeof(testArgv15And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv15And02);
		ptDdExsExecuteCmd((sizeof(testArgv15And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv15And03);
		ptDdExsExecuteCmd((sizeof(testArgv15And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv15And04);
		ptDdExsExecuteCmd((sizeof(testArgv15And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv15And05);

		// 1-1-33
		char testArgv16And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk17"};
		char testArgv16And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk17", "1"};
		char testArgv16And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk17"};
		char testArgv16And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "intmask", "intmsk17", "0"};
		char testArgv16And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "intmask", "intmsk17"};

		ptDdExsExecuteCmd((sizeof(testArgv16And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv16And01);
		ptDdExsExecuteCmd((sizeof(testArgv16And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv16And02);
		ptDdExsExecuteCmd((sizeof(testArgv16And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv16And03);
		ptDdExsExecuteCmd((sizeof(testArgv16And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv16And04);
		ptDdExsExecuteCmd((sizeof(testArgv16And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv16And05);

	/******************************************************************/
	} else if ( testno == 5 ) {		// "SIGMON"レジスタのテスト
									// 媒体挿抜による動作は実機確認で実施すること

		// 1-1-34
		char testArgv01And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "sigmon", "sigmon_sd3"};

		ptDdExsExecuteCmd((sizeof(testArgv01And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And01);

		// 1-1-35
		char testArgv02And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "sigmon", "sigmon_sd4"};

		ptDdExsExecuteCmd((sizeof(testArgv02And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And01);

		// 1-1-36
		char testArgv03And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "sigmon", "sigmon_pcie0"};

		ptDdExsExecuteCmd((sizeof(testArgv03And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And01);

		// 1-1-37
		char testArgv04And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "sigmon", "sigmon_pcie1"};

		ptDdExsExecuteCmd((sizeof(testArgv04And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And01);

		// 1-1-38
		char testArgv05And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "sigmon", "sigmon_usb2vbus"};

		ptDdExsExecuteCmd((sizeof(testArgv05And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv05And01);

		// 1-1-39
		char testArgv06And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "sigmon", "sigmon_usb2id"};

		ptDdExsExecuteCmd((sizeof(testArgv06And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv06And01);

		// 1-1-40
		char testArgv07And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "sigmon", "sigmon_usb3vbus"};

		ptDdExsExecuteCmd((sizeof(testArgv07And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv07And01);

		// 1-1-41
		char testArgv08And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "sigmon", "sigmon_usb3id"};

		ptDdExsExecuteCmd((sizeof(testArgv08And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv08And01);

		// 1-1-42
		char testArgv09And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "sigmon", "sigmon2_sd3"};

		ptDdExsExecuteCmd((sizeof(testArgv09And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv09And01);

		// 1-1-43
		char testArgv10And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "sigmon", "sigmon2_sd4"};

		ptDdExsExecuteCmd((sizeof(testArgv10And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv10And01);

		// 1-1-44
		char testArgv11And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "sigmon", "sigmon2_pcie0"};

		ptDdExsExecuteCmd((sizeof(testArgv11And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv11And01);

		// 1-1-45
		char testArgv12And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "sigmon", "sigmon2_pcie1"};

		ptDdExsExecuteCmd((sizeof(testArgv12And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv12And01);

		// 1-1-46
		char testArgv13And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "sigmon", "sigmon2_usb2vbus"};

		ptDdExsExecuteCmd((sizeof(testArgv13And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv13And01);

		// 1-1-47
		char testArgv14And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "sigmon", "sigmon2_usb2id"};

		ptDdExsExecuteCmd((sizeof(testArgv14And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv14And01);

		// 1-1-48
		char testArgv15And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "sigmon", "sigmon2_usb3vbus"};

		ptDdExsExecuteCmd((sizeof(testArgv15And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv15And01);

		// 1-1-49
		char testArgv16And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "sigmon", "sigmon2_usb3id"};

		ptDdExsExecuteCmd((sizeof(testArgv16And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv16And01);

	/******************************************************************/
	}//if 1 end
}


PalladiumTestMainExs* palladium_test_main_exs_new(void)
{
	PalladiumTestMainExs *self = k_object_new_with_private(PALLADIUM_TYPE_TEST_MAIN_EXS,sizeof(PalladiumTestMainExsPrivate));
	return self;
}
