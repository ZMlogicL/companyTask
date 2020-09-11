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


#include "palladiumtestmain2exs.h"


K_TYPE_DEFINE(PalladiumTestMain2Exs, palladium_test_main2_exs,sizeof(PalladiumTestMain2ExsPrivate))
#define PALLADIUM_TEST_MAIN2_EXS_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), PalladiumTestMain2ExsPrivate,PALLADIUM_TYPE_TEST_MAIN2_EXS))

struct _PalladiumTestMain2ExsPrivate
{
	int a;
};

static void palladium_test_main2_exs_constructor(PalladiumTestMain2Exs *self)
{
	PalladiumTestMain2ExsPrivate *priv = PALLADIUM_TEST_MAIN2_EXS_GET_PRIVATE(self);
	priv->a = 0;
}

static void palladium_test_main2_exs_destructor(PalladiumTestMain2Exs *self)
{
}

VOID palladium_test_main2_exs_testno( UCHAR testno )
{
	 if ( testno == 6 ) {		// "DEBEN"レジスタのテスト

				char testArgv00And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "debretx_sd3", "0"};
				char testArgv00And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "debretx_sd4", "0"};
				char testArgv00And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "deben_pcie0", "0"};
				char testArgv00And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "deben_pcie1", "0"};
				char testArgv00And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "deben_usb2vbus", "0"};
				char testArgv00And06[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "deben_usb2id", "0"};
				char testArgv00And07[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "deben_usb3vbus", "0"};
				char testArgv00And08[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "deben_usb3id", "0"};
				char testArgv00And09[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "sd3detim", "0"};
				char testArgv00And10[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "sd4detim", "0"};
				char testArgv00And11[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "pcie0detim", "0"};
				char testArgv00And12[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "pcie1detim", "0"};
				char testArgv00And13[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "usb2vbdetim", "0"};
				char testArgv00And14[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "usb2iddetim", "0"};
				char testArgv00And15[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "usb3vbdetim", "0"};
				char testArgv00And16[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "softreset2", "usb3iddetim", "0"};

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

				char testArgv00And21[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "deben_sd3", "0"};
				char testArgv00And22[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "deben_sd4", "0"};
				char testArgv00And23[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "deben_pcie0", "0"};
				char testArgv00And24[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "deben_pcie1", "0"};
				char testArgv00And25[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "deben_usb2vbus", "0"};
				char testArgv00And26[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "deben_usb2id", "0"};
				char testArgv00And27[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "deben_usb3vbus", "0"};
				char testArgv00And28[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "deben_usb3id", "0"};
				char testArgv00And29[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "sd3detim", "0"};
				char testArgv00And30[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "sd4detim", "0"};
				char testArgv00And31[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "pcie0detim", "0"};
				char testArgv00And32[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "pcie1detim", "0"};
				char testArgv00And33[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "usb2vbdetim", "0"};
				char testArgv00And34[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "usb2iddetim", "0"};
				char testArgv00And35[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "usb3vbdetim", "0"};
				char testArgv00And36[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "usb3iddetim", "0"};

				ptDdExsExecuteCmd((sizeof(testArgv00And21) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And21);
				ptDdExsExecuteCmd((sizeof(testArgv00And22) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And22);
				ptDdExsExecuteCmd((sizeof(testArgv00And23) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And23);
				ptDdExsExecuteCmd((sizeof(testArgv00And24) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And24);
				ptDdExsExecuteCmd((sizeof(testArgv00And25) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And25);
				ptDdExsExecuteCmd((sizeof(testArgv00And26) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And26);
				ptDdExsExecuteCmd((sizeof(testArgv00And27) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And27);
				ptDdExsExecuteCmd((sizeof(testArgv00And28) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And28);
				ptDdExsExecuteCmd((sizeof(testArgv00And29) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And29);
				ptDdExsExecuteCmd((sizeof(testArgv00And30) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And30);
				ptDdExsExecuteCmd((sizeof(testArgv00And31) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And31);
				ptDdExsExecuteCmd((sizeof(testArgv00And32) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And32);
				ptDdExsExecuteCmd((sizeof(testArgv00And33) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And33);
				ptDdExsExecuteCmd((sizeof(testArgv00And34) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And34);
				ptDdExsExecuteCmd((sizeof(testArgv00And35) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And35);
				ptDdExsExecuteCmd((sizeof(testArgv00And36) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And36);

				// 1-1-50
				char testArgv01And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "deben_sd3"};
				char testArgv01And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "deben_sd3", "1"};
				char testArgv01And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "deben_sd3"};
				char testArgv01And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "deben_sd3", "0"};
				char testArgv01And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "deben_sd3"};

				ptDdExsExecuteCmd((sizeof(testArgv01And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And01);
				ptDdExsExecuteCmd((sizeof(testArgv01And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And02);
				ptDdExsExecuteCmd((sizeof(testArgv01And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And03);
				ptDdExsExecuteCmd((sizeof(testArgv01And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And04);
				ptDdExsExecuteCmd((sizeof(testArgv01And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And05);

				// 1-1-51
				char testArgv02And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "deben_sd4"};
				char testArgv02And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "deben_sd4", "1"};
				char testArgv02And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "deben_sd4"};
				char testArgv02And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "deben_sd4", "0"};
				char testArgv02And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "deben_sd4"};

				ptDdExsExecuteCmd((sizeof(testArgv02And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And01);
				ptDdExsExecuteCmd((sizeof(testArgv02And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And02);
				ptDdExsExecuteCmd((sizeof(testArgv02And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And03);
				ptDdExsExecuteCmd((sizeof(testArgv02And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And04);
				ptDdExsExecuteCmd((sizeof(testArgv02And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And05);

				// 1-1-52
				char testArgv03And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "deben_pcie0"};
				char testArgv03And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "deben_pcie0", "1"};
				char testArgv03And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "deben_pcie0"};
				char testArgv03And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "deben_pcie0", "0"};
				char testArgv03And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "deben_pcie0"};

				ptDdExsExecuteCmd((sizeof(testArgv03And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And01);
				ptDdExsExecuteCmd((sizeof(testArgv03And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And02);
				ptDdExsExecuteCmd((sizeof(testArgv03And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And03);
				ptDdExsExecuteCmd((sizeof(testArgv03And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And04);
				ptDdExsExecuteCmd((sizeof(testArgv03And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And05);

				// 1-1-53
				char testArgv04And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "deben_pcie1"};
				char testArgv04And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "deben_pcie1", "3"};
				char testArgv04And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "deben_pcie1"};
				char testArgv04And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "deben_pcie1", "0"};
				char testArgv04And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "deben_pcie1"};

				ptDdExsExecuteCmd((sizeof(testArgv04And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And01);
				ptDdExsExecuteCmd((sizeof(testArgv04And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And02);
				ptDdExsExecuteCmd((sizeof(testArgv04And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And03);
				ptDdExsExecuteCmd((sizeof(testArgv04And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And04);
				ptDdExsExecuteCmd((sizeof(testArgv04And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And05);

				// 1-1-54
				char testArgv05And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "deben_usb2vbus"};
				char testArgv05And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "deben_usb2vbus", "3"};
				char testArgv05And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "deben_usb2vbus"};
				char testArgv05And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "deben_usb2vbus", "0"};
				char testArgv05And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "deben_usb2vbus"};

				ptDdExsExecuteCmd((sizeof(testArgv05And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv05And01);
				ptDdExsExecuteCmd((sizeof(testArgv05And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv05And02);
				ptDdExsExecuteCmd((sizeof(testArgv05And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv05And03);
				ptDdExsExecuteCmd((sizeof(testArgv05And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv05And04);
				ptDdExsExecuteCmd((sizeof(testArgv05And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv05And05);

				// 1-1-55
				char testArgv06And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "deben_usb2id"};
				char testArgv06And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "deben_usb2id", "3"};
				char testArgv06And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "deben_usb2id"};
				char testArgv06And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "deben_usb2id", "0"};
				char testArgv06And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "deben_usb2id"};

				ptDdExsExecuteCmd((sizeof(testArgv06And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv06And01);
				ptDdExsExecuteCmd((sizeof(testArgv06And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv06And02);
				ptDdExsExecuteCmd((sizeof(testArgv06And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv06And03);
				ptDdExsExecuteCmd((sizeof(testArgv06And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv06And04);
				ptDdExsExecuteCmd((sizeof(testArgv06And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv06And05);

				// 1-1-56
				char testArgv07And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "deben_usb3vbus"};
				char testArgv07And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "deben_usb3vbus", "3"};
				char testArgv07And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "deben_usb3vbus"};
				char testArgv07And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "deben_usb3vbus", "0"};
				char testArgv07And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "deben_usb3vbus"};

				ptDdExsExecuteCmd((sizeof(testArgv07And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv07And01);
				ptDdExsExecuteCmd((sizeof(testArgv07And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv07And02);
				ptDdExsExecuteCmd((sizeof(testArgv07And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv07And03);
				ptDdExsExecuteCmd((sizeof(testArgv07And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv07And04);
				ptDdExsExecuteCmd((sizeof(testArgv07And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv07And05);

				// 1-1-57
				char testArgv08And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "deben_usb3id"};
				char testArgv08And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "deben_usb3id", "3"};
				char testArgv08And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "deben_usb3id"};
				char testArgv08And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "deben_usb3id", "0"};
				char testArgv08And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "deben_usb3id"};

				ptDdExsExecuteCmd((sizeof(testArgv08And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv08And01);
				ptDdExsExecuteCmd((sizeof(testArgv08And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv08And02);
				ptDdExsExecuteCmd((sizeof(testArgv08And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv08And03);
				ptDdExsExecuteCmd((sizeof(testArgv08And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv08And04);
				ptDdExsExecuteCmd((sizeof(testArgv08And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv08And05);

				// 1-1-58
				char testArgv09And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "sd3detim"};
				char testArgv09And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "sd3detim", "3"};
				char testArgv09And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "sd3detim"};
				char testArgv09And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "sd3detim", "0"};
				char testArgv09And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "sd3detim"};

				ptDdExsExecuteCmd((sizeof(testArgv09And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv09And01);
				ptDdExsExecuteCmd((sizeof(testArgv09And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv09And02);
				ptDdExsExecuteCmd((sizeof(testArgv09And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv09And03);
				ptDdExsExecuteCmd((sizeof(testArgv09And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv09And04);
				ptDdExsExecuteCmd((sizeof(testArgv09And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv09And05);

				// 1-1-59
				char testArgv10And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "sd4detim"};
				char testArgv10And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "sd4detim", "3"};
				char testArgv10And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "sd4detim"};
				char testArgv10And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "sd4detim", "0"};
				char testArgv10And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "sd4detim"};

				ptDdExsExecuteCmd((sizeof(testArgv10And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv10And01);
				ptDdExsExecuteCmd((sizeof(testArgv10And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv10And02);
				ptDdExsExecuteCmd((sizeof(testArgv10And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv10And03);
				ptDdExsExecuteCmd((sizeof(testArgv10And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv10And04);
				ptDdExsExecuteCmd((sizeof(testArgv10And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv10And05);

				// 1-1-60
				char testArgv11And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "pcie0detim"};
				char testArgv11And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "pcie0detim", "3"};
				char testArgv11And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "pcie0detim"};
				char testArgv11And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "pcie0detim", "0"};
				char testArgv11And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "pcie0detim"};

				ptDdExsExecuteCmd((sizeof(testArgv11And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv11And01);
				ptDdExsExecuteCmd((sizeof(testArgv11And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv11And02);
				ptDdExsExecuteCmd((sizeof(testArgv11And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv11And03);
				ptDdExsExecuteCmd((sizeof(testArgv11And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv11And04);
				ptDdExsExecuteCmd((sizeof(testArgv11And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv11And05);

				// 1-1-61
				char testArgv12And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "pcie1detim"};
				char testArgv12And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "pcie1detim", "3"};
				char testArgv12And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "pcie1detim"};
				char testArgv12And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "pcie1detim", "0"};
				char testArgv12And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "pcie1detim"};

				ptDdExsExecuteCmd((sizeof(testArgv12And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv12And01);
				ptDdExsExecuteCmd((sizeof(testArgv12And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv12And02);
				ptDdExsExecuteCmd((sizeof(testArgv12And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv12And03);
				ptDdExsExecuteCmd((sizeof(testArgv12And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv12And04);
				ptDdExsExecuteCmd((sizeof(testArgv12And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv12And05);

				// 1-1-62
				char testArgv13And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "usb2vbdetim"};
				char testArgv13And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "usb2vbdetim", "3"};
				char testArgv13And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "usb2vbdetim"};
				char testArgv13And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "usb2vbdetim", "0"};
				char testArgv13And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "usb2vbdetim"};

				ptDdExsExecuteCmd((sizeof(testArgv13And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv13And01);
				ptDdExsExecuteCmd((sizeof(testArgv13And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv13And02);
				ptDdExsExecuteCmd((sizeof(testArgv13And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv13And03);
				ptDdExsExecuteCmd((sizeof(testArgv13And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv13And04);
				ptDdExsExecuteCmd((sizeof(testArgv13And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv13And05);

				// 1-1-63
				char testArgv14And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "usb2iddetim"};
				char testArgv14And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "usb2iddetim", "3"};
				char testArgv14And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "usb2iddetim"};
				char testArgv14And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "usb2iddetim", "0"};
				char testArgv14And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "usb2iddetim"};

				ptDdExsExecuteCmd((sizeof(testArgv14And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv14And01);
				ptDdExsExecuteCmd((sizeof(testArgv14And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv14And02);
				ptDdExsExecuteCmd((sizeof(testArgv14And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv14And03);
				ptDdExsExecuteCmd((sizeof(testArgv14And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv14And04);
				ptDdExsExecuteCmd((sizeof(testArgv14And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv14And05);

				// 1-1-64
				char testArgv15And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "usb3vbdetim"};
				char testArgv15And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "usb3vbdetim", "3"};
				char testArgv15And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "usb3vbdetim"};
				char testArgv15And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "usb3vbdetim", "0"};
				char testArgv15And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "usb3vbdetim"};

				ptDdExsExecuteCmd((sizeof(testArgv15And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv15And01);
				ptDdExsExecuteCmd((sizeof(testArgv15And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv15And02);
				ptDdExsExecuteCmd((sizeof(testArgv15And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv15And03);
				ptDdExsExecuteCmd((sizeof(testArgv15And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv15And04);
				ptDdExsExecuteCmd((sizeof(testArgv15And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv15And05);

				// 1-1-65
				char testArgv16And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "usb3iddetim"};
				char testArgv16And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "usb3iddetim", "3"};
				char testArgv16And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "usb3iddetim"};
				char testArgv16And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "deben", "usb3iddetim", "0"};
				char testArgv16And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "deben", "usb3iddetim"};

				ptDdExsExecuteCmd((sizeof(testArgv16And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv16And01);
				ptDdExsExecuteCmd((sizeof(testArgv16And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv16And02);
				ptDdExsExecuteCmd((sizeof(testArgv16And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv16And03);
				ptDdExsExecuteCmd((sizeof(testArgv16And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv16And04);
				ptDdExsExecuteCmd((sizeof(testArgv16And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv16And05);

			/******************************************************************/
			}
		else if ( testno == 7 ) {		// "CDINSMDCTL"レジスタのテスト

			char testArgv00And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "cdinsmdctl", "cdmod_sd3", "0"};
			char testArgv00And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "cdinsmdctl", "cdmod_sd4", "0"};
			char testArgv00And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "cdinsmdctl", "cdmod_pcie0", "0"};
			char testArgv00And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "cdinsmdctl", "cdmod_pcie1", "0"};
			char testArgv00And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "cdinsmdctl", "cdmod_usb2vbus", "0"};
			char testArgv00And06[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "cdinsmdctl", "cdmod_usb2id", "0"};
			char testArgv00And07[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "cdinsmdctl", "cdmod_usb3vbus", "0"};
			char testArgv00And08[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "cdinsmdctl", "cdmod_usb3id", "0"};

			ptDdExsExecuteCmd((sizeof(testArgv00And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And01);
			ptDdExsExecuteCmd((sizeof(testArgv00And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And02);
			ptDdExsExecuteCmd((sizeof(testArgv00And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And03);
			ptDdExsExecuteCmd((sizeof(testArgv00And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And04);
			ptDdExsExecuteCmd((sizeof(testArgv00And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And05);
			ptDdExsExecuteCmd((sizeof(testArgv00And06) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And06);
			ptDdExsExecuteCmd((sizeof(testArgv00And07) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And07);
			ptDdExsExecuteCmd((sizeof(testArgv00And08) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And08);

			// 1-1-66
			char testArgv01And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "cdinsmdctl", "cdmod_sd3"};
			char testArgv01And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "cdinsmdctl", "cdmod_sd3", "1"};
			char testArgv01And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "cdinsmdctl", "cdmod_sd3"};
			char testArgv01And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "cdinsmdctl", "cdmod_sd3", "0"};
			char testArgv01And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "cdinsmdctl", "cdmod_sd3"};

			ptDdExsExecuteCmd((sizeof(testArgv01And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And01);
			ptDdExsExecuteCmd((sizeof(testArgv01And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And02);
			ptDdExsExecuteCmd((sizeof(testArgv01And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And03);
			ptDdExsExecuteCmd((sizeof(testArgv01And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And04);
			ptDdExsExecuteCmd((sizeof(testArgv01And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And05);

			// 1-1-67
			char testArgv02And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "cdinsmdctl", "cdmod_sd4"};
			char testArgv02And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "cdinsmdctl", "cdmod_sd4", "1"};
			char testArgv02And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "cdinsmdctl", "cdmod_sd4"};
			char testArgv02And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "cdinsmdctl", "cdmod_sd4", "0"};
			char testArgv02And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "cdinsmdctl", "cdmod_sd4"};

			ptDdExsExecuteCmd((sizeof(testArgv02And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And01);
			ptDdExsExecuteCmd((sizeof(testArgv02And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And02);
			ptDdExsExecuteCmd((sizeof(testArgv02And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And03);
			ptDdExsExecuteCmd((sizeof(testArgv02And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And04);
			ptDdExsExecuteCmd((sizeof(testArgv02And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And05);

			// 1-1-68
			char testArgv03And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "cdinsmdctl", "cdmod_pcie0"};
			char testArgv03And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "cdinsmdctl", "cdmod_pcie0", "1"};
			char testArgv03And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "cdinsmdctl", "cdmod_pcie0"};
			char testArgv03And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "cdinsmdctl", "cdmod_pcie0", "0"};
			char testArgv03And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "cdinsmdctl", "cdmod_pcie0"};

			ptDdExsExecuteCmd((sizeof(testArgv03And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And01);
			ptDdExsExecuteCmd((sizeof(testArgv03And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And02);
			ptDdExsExecuteCmd((sizeof(testArgv03And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And03);
			ptDdExsExecuteCmd((sizeof(testArgv03And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And04);
			ptDdExsExecuteCmd((sizeof(testArgv03And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And05);

			// 1-1-69
			char testArgv04And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "cdinsmdctl", "cdmod_pcie1"};
			char testArgv04And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "cdinsmdctl", "cdmod_pcie1", "1"};
			char testArgv04And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "cdinsmdctl", "cdmod_pcie1"};
			char testArgv04And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "cdinsmdctl", "cdmod_pcie1", "0"};
			char testArgv04And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "cdinsmdctl", "cdmod_pcie1"};

			ptDdExsExecuteCmd((sizeof(testArgv04And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And01);
			ptDdExsExecuteCmd((sizeof(testArgv04And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And02);
			ptDdExsExecuteCmd((sizeof(testArgv04And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And03);
			ptDdExsExecuteCmd((sizeof(testArgv04And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And04);
			ptDdExsExecuteCmd((sizeof(testArgv04And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And05);

			// 1-1-70
			char testArgv05And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "cdinsmdctl", "cdmod_usb2vbus"};
			char testArgv05And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "cdinsmdctl", "cdmod_usb2vbus", "1"};
			char testArgv05And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "cdinsmdctl", "cdmod_usb2vbus"};
			char testArgv05And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "cdinsmdctl", "cdmod_usb2vbus", "0"};
			char testArgv05And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "cdinsmdctl", "cdmod_usb2vbus"};

			ptDdExsExecuteCmd((sizeof(testArgv05And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv05And01);
			ptDdExsExecuteCmd((sizeof(testArgv05And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv05And02);
			ptDdExsExecuteCmd((sizeof(testArgv05And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv05And03);
			ptDdExsExecuteCmd((sizeof(testArgv05And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv05And04);
			ptDdExsExecuteCmd((sizeof(testArgv05And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv05And05);

			// 1-1-71
			char testArgv06And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "cdinsmdctl", "cdmod_usb2id"};
			char testArgv06And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "cdinsmdctl", "cdmod_usb2id", "1"};
			char testArgv06And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "cdinsmdctl", "cdmod_usb2id"};
			char testArgv06And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "cdinsmdctl", "cdmod_usb2id", "0"};
			char testArgv06And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "cdinsmdctl", "cdmod_usb2id"};

			ptDdExsExecuteCmd((sizeof(testArgv06And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv06And01);
			ptDdExsExecuteCmd((sizeof(testArgv06And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv06And02);
			ptDdExsExecuteCmd((sizeof(testArgv06And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv06And03);
			ptDdExsExecuteCmd((sizeof(testArgv06And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv06And04);
			ptDdExsExecuteCmd((sizeof(testArgv06And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv06And05);

			// 1-1-72
			char testArgv07And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "cdinsmdctl", "cdmod_usb3vbus"};
			char testArgv07And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "cdinsmdctl", "cdmod_usb3vbus", "1"};
			char testArgv07And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "cdinsmdctl", "cdmod_usb3vbus"};
			char testArgv07And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "cdinsmdctl", "cdmod_usb3vbus", "0"};
			char testArgv07And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "cdinsmdctl", "cdmod_usb3vbus"};

			ptDdExsExecuteCmd((sizeof(testArgv07And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv07And01);
			ptDdExsExecuteCmd((sizeof(testArgv07And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv07And02);
			ptDdExsExecuteCmd((sizeof(testArgv07And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv07And03);
			ptDdExsExecuteCmd((sizeof(testArgv07And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv07And04);
			ptDdExsExecuteCmd((sizeof(testArgv07And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv07And05);

			// 1-1-73
			char testArgv08And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "cdinsmdctl", "cdmod_usb3id"};
			char testArgv08And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "cdinsmdctl", "cdmod_usb3id", "1"};
			char testArgv08And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "cdinsmdctl", "cdmod_usb3id"};
			char testArgv08And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "cdinsmdctl", "cdmod_usb3id", "0"};
			char testArgv08And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "cdinsmdctl", "cdmod_usb3id"};

			ptDdExsExecuteCmd((sizeof(testArgv08And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv08And01);
			ptDdExsExecuteCmd((sizeof(testArgv08And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv08And02);
			ptDdExsExecuteCmd((sizeof(testArgv08And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv08And03);
			ptDdExsExecuteCmd((sizeof(testArgv08And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv08And04);
			ptDdExsExecuteCmd((sizeof(testArgv08And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv08And05);

		/******************************************************************/
		} else if ( testno == 8 ) {		// "RLC_HPT_CTL"レジスタのテスト

			char testArgv00And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "rlc_hpt_ctl", "rerhpt", "0"};
			char testArgv00And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "rlc_hpt_ctl", "rewhpt", "0"};

			ptDdExsExecuteCmd((sizeof(testArgv00And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And01);
			ptDdExsExecuteCmd((sizeof(testArgv00And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv00And02);

			// 1-1-74
			char testArgv01And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "rlc_hpt_ctl", "rerhpt"};
			char testArgv01And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "rlc_hpt_ctl", "rerhpt", "15"};
			char testArgv01And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "rlc_hpt_ctl", "rerhpt"};
			char testArgv01And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "rlc_hpt_ctl", "rerhpt", "0"};
			char testArgv01And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "rlc_hpt_ctl", "rerhpt"};

			ptDdExsExecuteCmd((sizeof(testArgv01And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And01);
			ptDdExsExecuteCmd((sizeof(testArgv01And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And02);
			ptDdExsExecuteCmd((sizeof(testArgv01And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And03);
			ptDdExsExecuteCmd((sizeof(testArgv01And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And04);
			ptDdExsExecuteCmd((sizeof(testArgv01And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And05);

			// 1-1-75
			char testArgv02And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "rlc_hpt_ctl", "rewhpt"};
			char testArgv02And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "rlc_hpt_ctl", "rewhpt", "15"};
			char testArgv02And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "rlc_hpt_ctl", "rewhpt"};
			char testArgv02And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "rlc_hpt_ctl", "rewhpt", "0"};
			char testArgv02And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "rlc_hpt_ctl", "rewhpt"};

			ptDdExsExecuteCmd((sizeof(testArgv02And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And01);
			ptDdExsExecuteCmd((sizeof(testArgv02And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And02);
			ptDdExsExecuteCmd((sizeof(testArgv02And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And03);
			ptDdExsExecuteCmd((sizeof(testArgv02And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And04);
			ptDdExsExecuteCmd((sizeof(testArgv02And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And05);

		/******************************************************************/
		} else if ( testno == 9 ) {		// "RAM_PD"レジスタのテスト

			char testArgv00And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "ram_pd", "rampd_sd2", "0"};
			char testArgv00And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "ram_pd", "rampd_sd3", "0"};
			char testArgv00And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "ram_pd", "rampd_sd4", "0"};
			char testArgv00And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "ram_pd", "rampd_nf", "0"};
			char testArgv00And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "ram_pd", "rampd_relc", "0"};
			char testArgv00And06[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "ram_pd", "rampd_netsec", "0"};
			char testArgv00And07[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "ram_pd", "rampd_usb2", "0"};
			char testArgv00And08[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "ram_pd", "rampd_usb3", "0"};
			char testArgv00And09[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "ram_pd", "rampd_pcie0", "0"};
			char testArgv00And10[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "ram_pd", "rampd_pcie1", "0"};
			char testArgv00And11[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "ram_pd", "rampd_emmc", "0"};

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

			// 1-1-76
			char testArgv01And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "ram_pd", "rampd_sd2"};
			char testArgv01And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "ram_pd", "rampd_sd2", "1"};
			char testArgv01And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "ram_pd", "rampd_sd2"};
			char testArgv01And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "ram_pd", "rampd_sd2", "0"};
			char testArgv01And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "ram_pd", "rampd_sd2"};

			ptDdExsExecuteCmd((sizeof(testArgv01And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And01);
			ptDdExsExecuteCmd((sizeof(testArgv01And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And02);
			ptDdExsExecuteCmd((sizeof(testArgv01And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And03);
			ptDdExsExecuteCmd((sizeof(testArgv01And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And04);
			ptDdExsExecuteCmd((sizeof(testArgv01And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv01And05);

			// 1-1-77
			char testArgv02And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "ram_pd", "rampd_sd3"};
			char testArgv02And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "ram_pd", "rampd_sd3", "1"};
			char testArgv02And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "ram_pd", "rampd_sd3"};
			char testArgv02And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "ram_pd", "rampd_sd3", "0"};
			char testArgv02And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "ram_pd", "rampd_sd3"};

			ptDdExsExecuteCmd((sizeof(testArgv02And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And01);
			ptDdExsExecuteCmd((sizeof(testArgv02And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And02);
			ptDdExsExecuteCmd((sizeof(testArgv02And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And03);
			ptDdExsExecuteCmd((sizeof(testArgv02And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And04);
			ptDdExsExecuteCmd((sizeof(testArgv02And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv02And05);

			// 1-1-78
			char testArgv03And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "ram_pd", "rampd_sd4"};
			char testArgv03And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "ram_pd", "rampd_sd4", "1"};
			char testArgv03And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "ram_pd", "rampd_sd4"};
			char testArgv03And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "ram_pd", "rampd_sd4", "0"};
			char testArgv03And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "ram_pd", "rampd_sd4"};

			ptDdExsExecuteCmd((sizeof(testArgv03And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And01);
			ptDdExsExecuteCmd((sizeof(testArgv03And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And02);
			ptDdExsExecuteCmd((sizeof(testArgv03And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And03);
			ptDdExsExecuteCmd((sizeof(testArgv03And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And04);
			ptDdExsExecuteCmd((sizeof(testArgv03And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv03And05);

			// 1-1-79
			char testArgv04And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "ram_pd", "rampd_nf"};
			char testArgv04And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "ram_pd", "rampd_nf", "1"};
			char testArgv04And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "ram_pd", "rampd_nf"};
			char testArgv04And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "ram_pd", "rampd_nf", "0"};
			char testArgv04And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "ram_pd", "rampd_nf"};

			ptDdExsExecuteCmd((sizeof(testArgv04And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And01);
			ptDdExsExecuteCmd((sizeof(testArgv04And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And02);
			ptDdExsExecuteCmd((sizeof(testArgv04And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And03);
			ptDdExsExecuteCmd((sizeof(testArgv04And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And04);
			ptDdExsExecuteCmd((sizeof(testArgv04And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv04And05);

			// 1-1-80
			char testArgv05And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "ram_pd", "rampd_relc"};
			char testArgv05And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "ram_pd", "rampd_relc", "1"};
			char testArgv05And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "ram_pd", "rampd_relc"};
			char testArgv05And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "ram_pd", "rampd_relc", "0"};
			char testArgv05And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "ram_pd", "rampd_relc"};

			ptDdExsExecuteCmd((sizeof(testArgv05And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv05And01);
			ptDdExsExecuteCmd((sizeof(testArgv05And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv05And02);
			ptDdExsExecuteCmd((sizeof(testArgv05And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv05And03);
			ptDdExsExecuteCmd((sizeof(testArgv05And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv05And04);
			ptDdExsExecuteCmd((sizeof(testArgv05And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv05And05);

			// 1-1-81
			char testArgv06And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "ram_pd", "rampd_netsec"};
			char testArgv06And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "ram_pd", "rampd_netsec", "1"};
			char testArgv06And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "ram_pd", "rampd_netsec"};
			char testArgv06And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "ram_pd", "rampd_netsec", "0"};
			char testArgv06And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "ram_pd", "rampd_netsec"};

			ptDdExsExecuteCmd((sizeof(testArgv06And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv06And01);
			ptDdExsExecuteCmd((sizeof(testArgv06And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv06And02);
			ptDdExsExecuteCmd((sizeof(testArgv06And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv06And03);
			ptDdExsExecuteCmd((sizeof(testArgv06And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv06And04);
			ptDdExsExecuteCmd((sizeof(testArgv06And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv06And05);

			// 1-1-82
			char testArgv07And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "ram_pd", "rampd_usb2"};
			char testArgv07And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "ram_pd", "rampd_usb2", "1"};
			char testArgv07And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "ram_pd", "rampd_usb2"};
			char testArgv07And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "ram_pd", "rampd_usb2", "0"};
			char testArgv07And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "ram_pd", "rampd_usb2"};

			ptDdExsExecuteCmd((sizeof(testArgv07And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv07And01);
			ptDdExsExecuteCmd((sizeof(testArgv07And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv07And02);
			ptDdExsExecuteCmd((sizeof(testArgv07And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv07And03);
			ptDdExsExecuteCmd((sizeof(testArgv07And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv07And04);
			ptDdExsExecuteCmd((sizeof(testArgv07And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv07And05);

			// 1-1-83
			char testArgv08And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "ram_pd", "rampd_usb3"};
			char testArgv08And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "ram_pd", "rampd_usb3", "1"};
			char testArgv08And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "ram_pd", "rampd_usb3"};
			char testArgv08And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "ram_pd", "rampd_usb3", "0"};
			char testArgv08And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "ram_pd", "rampd_usb3"};

			ptDdExsExecuteCmd((sizeof(testArgv08And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv08And01);
			ptDdExsExecuteCmd((sizeof(testArgv08And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv08And02);
			ptDdExsExecuteCmd((sizeof(testArgv08And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv08And03);
			ptDdExsExecuteCmd((sizeof(testArgv08And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv08And04);
			ptDdExsExecuteCmd((sizeof(testArgv08And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv08And05);

			// 1-1-84
			char testArgv09And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "ram_pd", "rampd_pcie0"};
			char testArgv09And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "ram_pd", "rampd_pcie0", "1"};
			char testArgv09And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "ram_pd", "rampd_pcie0"};
			char testArgv09And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "ram_pd", "rampd_pcie0", "0"};
			char testArgv09And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "ram_pd", "rampd_pcie0"};

			ptDdExsExecuteCmd((sizeof(testArgv09And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv09And01);
			ptDdExsExecuteCmd((sizeof(testArgv09And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv09And02);
			ptDdExsExecuteCmd((sizeof(testArgv09And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv09And03);
			ptDdExsExecuteCmd((sizeof(testArgv09And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv09And04);
			ptDdExsExecuteCmd((sizeof(testArgv09And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv09And05);

			// 1-1-85
			char testArgv10And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "ram_pd", "rampd_pcie1"};
			char testArgv10And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "ram_pd", "rampd_pcie1", "1"};
			char testArgv10And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "ram_pd", "rampd_pcie1"};
			char testArgv10And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "ram_pd", "rampd_pcie1", "0"};
			char testArgv10And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "ram_pd", "rampd_pcie1"};

			ptDdExsExecuteCmd((sizeof(testArgv10And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv10And01);
			ptDdExsExecuteCmd((sizeof(testArgv10And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv10And02);
			ptDdExsExecuteCmd((sizeof(testArgv10And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv10And03);
			ptDdExsExecuteCmd((sizeof(testArgv10And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv10And04);
			ptDdExsExecuteCmd((sizeof(testArgv10And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv10And05);

			// 1-1-86
			char testArgv11And01[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "ram_pd", "rampd_emmc"};
			char testArgv11And02[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "ram_pd", "rampd_emmc", "1"};
			char testArgv11And03[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "ram_pd", "rampd_emmc"};
			char testArgv11And04[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "set", "ram_pd", "rampd_emmc", "0"};
			char testArgv11And05[][PalladiumTestExs_PT_DD_EXS_CMD_LEN]  = {"ddexstop", "get", "ram_pd", "rampd_emmc"};

			ptDdExsExecuteCmd((sizeof(testArgv11And01) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv11And01);
			ptDdExsExecuteCmd((sizeof(testArgv11And02) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv11And02);
			ptDdExsExecuteCmd((sizeof(testArgv11And03) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv11And03);
			ptDdExsExecuteCmd((sizeof(testArgv11And04) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv11And04);
			ptDdExsExecuteCmd((sizeof(testArgv11And05) / PalladiumTestExs_PT_DD_EXS_CMD_LEN), (char*)testArgv11And05);

		/******************************************************************/
		}

}

PalladiumTestMain2Exs* palladium_test_main2_exs_new(void)
{
	PalladiumTestMain2Exs *self = k_object_new_with_private(PALLADIUM_TYPE_TEST_MAIN2_EXS,sizeof(PalladiumTestMain2ExsPrivate));
	return self;
}
