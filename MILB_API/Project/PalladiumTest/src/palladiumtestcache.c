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


#include "palladiumtestcache.h"
#include "palladium_test.h"
#include "dd_cache.h"

typedef struct _PalladiumTestCachePrivate		PalladiumTestCachePrivate;
struct _PalladiumTestCachePrivate
{
	kuchar	testno;
};

K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(PalladiumTestCache, palladium_test_cache,K_TYPE_OBJECT)
#define PALLADIUM_TEST_CACHE_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), PalladiumTestCachePrivate,PALLADIUM_TYPE_TEST_CACHE))

static void palladium_test_cache_constructor(PalladiumTestCache *self)
{
	PalladiumTestCachePrivate *priv = PALLADIUM_TEST_CACHE_GET_PRIVATE(self);
	priv ->testno =0;
}

static void palladium_test_cache_destructor(PalladiumTestCache *self)
{
}

void pt_dd_cache_main( PalladiumTestCache *self )
{
	PalladiumTestCachePrivate *priv = PALLADIUM_TEST_CACHE_GET_PRIVATE(self);
	// テストパラメータ取得(RSファイルに紐付く)
	priv ->testno	= gDdimInfo.com._6a;

	// レジスタ取得＆設定(#define PC_DEBUG を定義すること)
	/******************************************************************/
	if ( priv ->testno == 1 ) {	// HDMAC Auto Test 1
		Ddim_Print(("CACHE L1 Clean Test 1 start\n"));
		Dd_CACHE_L1_Clean_Dcache_Addr(0x57000000, 0x1000);
		Dd_CACHE_L2_Clean_Dcache_Addr(0x57000000, 0x1000);
		Ddim_Print(("CACHE L1 Clean Test 1 end\n"));
	}
}

PalladiumTestCache* palladium_test_cache_new(void)
{
	PalladiumTestCache *self = k_object_new_with_private(PALLADIUM_TYPE_TEST_CACHE,sizeof(PalladiumTestCachePrivate));
	return self;
}
