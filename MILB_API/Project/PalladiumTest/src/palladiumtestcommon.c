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
#include "palladium_test.h"
#include "palladium_test_common.h"
#include "palladium_test_interrupt.h"

#include "palladiumtestcommon.h"

K_TYPE_DEFINE_WITH_PRIVATE(PalladiumTestCommon, palladium_test_common)
#define PALLADIUM_TEST_COMMON_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), PalladiumTestCommonPrivate,PALLADIUM_TYPE_TEST_COMMON))

T_DDIM_INFO gDDIM_Info;

struct _PalladiumTestCommonPrivate
{
	int a;
};

static void palladium_test_common_constructor(PalladiumTestCommon *self)
{
	PalladiumTestCommonPrivate *priv = PALLADIUM_TEST_COMMON_GET_PRIVATE(self);
	priv-> a = 0;
}

static void palladium_test_common_destructor(PalladiumTestCommon *self)
{
	PalladiumTestCommonPrivate *priv = PALLADIUM_TEST_COMMON_GET_PRIVATE(self);
	priv-> a = 0;
}

/*
 * PUBLIC
 */

extern int palladium_test_common_cmd_call_main(INT32 argc, CHAR argv[][PalladiumTestCommon_D_PALLADIUM_TEST_CMD_CHAR_NUM], ct_Main ctCommandMain )
{
	int ret = 0;
	if(argc <= PalladiumTestCommon_D_PALLADIUM_TEST_CMD_PARA_NUM){
		CHAR* p_rgv[PalladiumTestCommon_D_PALLADIUM_TEST_CMD_PARA_NUM];
		int i;
		for(i = 0; i< argc; i++)
		{
			if((argv[i])[0] == 0){
				break;
			}
			p_rgv[i] = argv[i];
		}

	    ctCommandMain(i, p_rgv);
    }
    else{
		ret = -1;
	}
	return ret;
}

extern int palladium_test_common_cmd_dump_reg(ULONG regAddress, ULONG size )
{
	UINT32* outputAddressTemp = (UINT32*)((0x8FFFFFFF- size) & 0xffffff00);
	UINT32* outputAddressTempSave = outputAddressTemp;
	UINT32* intputAddressTemp =(UINT32*)regAddress;
	for(int i = 0; i< size/4; i++){
		*outputAddressTemp = *intputAddressTemp;
		outputAddressTemp++;
		intputAddressTemp++;
	}
	Palladium_Set_Out_Localstack((ULONG)outputAddressTempSave , size);

	return 0;
}


PalladiumTestCommon* palladium_test_common_new(void)
{
	PalladiumTestCommon *self = k_object_new_with_private(PALLADIUM_TYPE_TEST_COMMON, sizeof(PalladiumTestCommonPrivate));
	return self;
}
