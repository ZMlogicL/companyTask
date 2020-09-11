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

#ifndef __PALLADIUM_TEST_MAIN2_EXS_H__
#define __PALLADIUM_TEST_MAIN2_EXS_H__

#include <klib.h>
#include "palladiumtestexs.h"

#define PALLADIUM_TYPE_TEST_MAIN2_EXS	(palladium_test_main2_exs_get_type())
#define PALLADIUM_TEST_MAIN2_EXS(obj) 	K_TYPE_CHECK_INSTANCE_CAST(obj, PalladiumTestMain2Exs)
#define PALLADIUM_IS_TEST_MAIN2_EXS(obj) 	K_TYPE_CHECK_INSTANCE_TYPE(obj, PALLADIUM_TYPE_TEST_MAIN2_EXS)

typedef struct _PalladiumTestMain2Exs					PalladiumTestMain2Exs;
typedef struct _PalladiumTestMain2ExsPrivate		PalladiumTestMain2ExsPrivate;

struct _PalladiumTestMain2ExsPrivate
{
};

KConstType 								palladium_test_main2_exs_get_type(void);
PalladiumTestMain2Exs* 		palladium_test_main2_exs_new(void);

VOID 											palladium_test_main2_exs_testno( UCHAR testno );

#endif /* __PALLADIUM_TEST_MAIN2_EXS_H__ */

