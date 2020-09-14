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

#ifndef __PALLADIUM_TEST_CACHE_H__
#define __PALLADIUM_TEST_CACHE_H__

#include <klib.h>

#define PALLADIUM_TYPE_TEST_CACHE			(palladium_test_cache_get_type())
#define PALLADIUM_TEST_CACHE(obj) 			K_TYPE_CHECK_INSTANCE_CAST(obj, PalladiumTestCache)
#define PALLADIUM_IS_TEST_CACHE(obj) 		K_TYPE_CHECK_INSTANCE_TYPE(obj, PALLADIUM_TYPE_TEST_CACHE)

typedef struct _PalladiumTestCache PalladiumTestCache;

struct _PalladiumTestCache{

};

KConstType 					palladium_test_cache_get_type(void);
PalladiumTestCache* 	palladium_test_cache_new(void);

void 								pt_dd_cache_main( PalladiumTestCache *self );

#endif /* __PALLADIUM_TEST_CACHE_H__ */

