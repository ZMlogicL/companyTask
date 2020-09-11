/*
*@Copyright (C) 2010-2015 上海网用软件有限公司
*@date                :2020-04-20
*@author              :
*@brief               :snsnet网络协议栈
*@rely                :klib
*@function
*SNSNET，采用ETK-C语言编写
*设计的主要功能:
*@version
*1.0.0 2020年04月开始开发
*/

#ifndef __PALLADIUM_TEST_COMMON_H__
#define __PALLADIUM_TEST_COMMON_H__

#include <klib.h>
#include "driver_common.h"

#define PALLADIUM_TYPE_TEST_COMMON	(palladium_test_common_get_type())
#define PALLADIUM_TEST_COMMON(obj) 	K_TYPE_CHECK_INSTANCE_CAST(obj, PalladiumTestCommon)
#define PALLADIUM_IS_TEST_COMMON(obj) 	K_TYPE_CHECK_INSTANCE_TYPE(obj, PALLADIUM_TYPE_TEST_COMMON)

#define PalladiumTestCommon_D_PALLADIUM_TEST_CMD_PARA_NUM				(20)
#define PalladiumTestCommon_D_PALLADIUM_TEST_CMD_CHAR_NUM				(20)
#define PalladiumTestCommon_D_PALLADIUM_TEST_CMD_NUM					(20)

typedef struct 				_PalladiumTestCommon PalladiumTestCommon;
typedef struct 				_PalladiumTestCommonPrivate		PalladiumTestCommonPrivate;

struct _PalladiumTestCommon {
	KObject parent;
};
typedef VOID (*ct_Main)(kint32 argc, CHAR** argv);	//CT commande main



KConstType 						palladium_test_common_get_type(void);
PalladiumTestCommon* 	palladium_test_common_new(void);

extern int 							palladium_test_common_cmd_call_main(kint32 argc, CHAR argv[][PalladiumTestCommon_D_PALLADIUM_TEST_CMD_CHAR_NUM], ct_Main ctCommandMain );
extern int 							palladium_test_common_cmd_dump_reg(kulong regAddress, kulong size );

#endif /* __PALLADIUM_TEST_COMMON_H__ */

