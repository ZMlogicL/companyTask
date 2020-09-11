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

#ifndef __PALLADIUM_TEST_MAIN_EXS_H__
#define __PALLADIUM_TEST_MAIN_EXS_H__

#include <klib.h>
#include "dd_relc.h"

#define PALLADIUM_TYPE_TEST_MAIN_EXS		(palladium_test_main_exs_get_type())
#define PALLADIUM_TEST_MAIN_EXS(obj) 	K_TYPE_CHECK_INSTANCE_CAST(obj, PalladiumTestMainExs)
#define PALLADIUM_IS_TEST_MAIN_EXS(obj) 	K_TYPE_CHECK_INSTANCE_TYPE(obj, PALLADIUM_TYPE_TEST_MAIN_EXS)


typedef struct _PalladiumTestMainExs 				PalladiumTestMainExs;
typedef struct _PalladiumTestMainExsPrivate 	PalladiumTestMainExsPrivate;

struct _PalladiumTestMainExs {
	KObject parent;
};

KConstType 										palladium_test_main_exs_get_type(void);
PalladiumTestMainExs* 					palladium_test_main_exs_new(void);

VOID 													palladium_test_main_exs_testno( UCHAR testno );

#endif /* __PALLADIUM_TEST_MAIN_EXS_H__ */

