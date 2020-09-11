/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-03
*@author : 王顺
*@brief : DdCache
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/
/**
 * @file		dd_cache.c
 * @brief		Cache Operation driver
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */


#include "ddcache.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdCache, dd_cache);

#define DD_CACHE_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), DdCachePrivate, DD_TYPE_CACHE))


struct _DdCachePrivate
{

};


extern void Dd_CACHE_L1_Flush_Dcache_Addr_Asm(kuint32 address, kuint32 size);
extern void Dd_CACHE_L1_Clean_Dcache_Addr_Asm(kuint32 address, kuint32 size);
extern void Dd_CACHE_L1_Clean_Flush_Dcache_Addr_Asm(kuint32 address, kuint32 size);
extern void Dd_CACHE_L2_Flush_Dcache_Addr_Asm(kuint32 address, kuint32 size);
extern void Dd_CACHE_L2_Clean_Dcache_Addr_Asm(kuint32 address, kuint32 size);
extern void Dd_CACHE_L2_Clean_Flush_Dcache_Addr_Asm(kuint32 address, kuint32 size);

/**
DECLS
*/
/**
IMPL
*/
static void dd_cache_constructor(DdCache *self)
{
//	DdCachePrivate *priv = DD_CACHE_GET_PRIVATE(self);
}

static void dd_cache_destructor(DdCache *self)
{
//	DdCachePrivate *priv = DD_CACHE_GET_PRIVATE(self);
}
/**
PUBLIC
*/
/**
Level 1 D-Cache Flush by Addressing & size function
@param[in]		address		: target start address
@param[in]		size		: target size
@remarks	This function flush is Level 1 Cache Only.
*/
void dd_cache_l1_flush_dcache_addr_align(DdCache *self, kuint32 address, kuint32 size)
{
	if( 0 == size ) {
#ifdef CO_PARAM_CHECK
		Ddim_Print(("dd_cache_l1_flush_dcache_addr_align : input size 0 error.\n"));
#endif
		return;
	}
	Dd_CACHE_L1_Flush_Dcache_Addr_Asm(address, size);
}

/**
Level 1 D-Cache Clean by Addressing & size function
@param[in]		address		: target start address
@param[in]		size		: target size
@remarks	This function clean is Level 1 Cache Only.
*/
void dd_cache_l1_clean_dcache_addr_align(DdCache *self, kuint32 address, kuint32 size)
{
	if( 0 == size ) {
#ifdef CO_PARAM_CHECK
		Ddim_Print(("dd_cache_l1_clean_dcache_addr_align : input size 0 error.\n"));
#endif
		return;
	}
	Dd_CACHE_L1_Clean_Dcache_Addr_Asm(address, size);
}

/**
Level 1 D-Cache Clean & Flush by Addressing & size function
@param[in]		address		: target start address
@param[in]		size		: target size
@remarks	This function clean & flush is Level 1 Cache Only.
*/
void dd_cache_l1_clean_flush_dcache_addr_align(DdCache *self, kuint32 address, kuint32 size)
{
	if (0 == size) {
#ifdef CO_PARAM_CHECK
		Ddim_Print(("dd_cache_l1_clean_flush_dcache_addr_align : input size 0 error.\n"));
#endif
		return;
	}
	Dd_CACHE_L1_Clean_Flush_Dcache_Addr_Asm(address, size);
}

/**
Level 2 D-Cache Flush by Addressing & size function
@param[in]		address		: target start address
@param[in]		size		: target size
@remarks	This function's flush is Level 2 Cache Only.
*/
void dd_cache_l2_flush_dcache_addr_align(DdCache *self, kuint32 address, kuint32 size)
{
	if (0 == size) {
#ifdef CO_PARAM_CHECK
		Ddim_Print(("dd_cache_l2_flush_dcache_addr_align : input size 0 error.\n"));
#endif
		return;
	}
	Dd_CACHE_L2_Flush_Dcache_Addr_Asm(address, size);
}

/**
Level 2 D-Cache Clean by Addressing & size function
@param[in]		address		: target start address
@param[in]		size		: target size
@remarks	This function's clean is Level 2 Cache Only.
*/
void dd_cache_l2_clean_dcache_addr_align(DdCache *self, kuint32 address, kuint32 size)
{
	if (0 == size) {
#ifdef CO_PARAM_CHECK
		Ddim_Print(("dd_cache_l2_clean_dcache_addr_align : input size 0 error.\n"));
#endif
		return;
	}
	Dd_CACHE_L2_Clean_Dcache_Addr_Asm(address, size);
}

/**
Level 2 D-Cache Clean & Flush by Addressing & size function
@param[in]		address		: target start address
@param[in]		size		: target size
@remarks	This function's clean & flush is Level 2 Cache Only.
*/
void dd_cache_l2_clean_flush_dcache_addr_align(DdCache *self, kuint32 address, kuint32 size)
{
	if (0 == size) {
#ifdef CO_PARAM_CHECK
		Ddim_Print(("dd_cache_l2_clean_flush_dcache_addr_align : input size 0 error.\n"));
#endif
		return;
	}
	Dd_CACHE_L2_Clean_Flush_Dcache_Addr_Asm(address, size);
}

DdCache* dd_cache_new(void)
{
	DdCache* self = k_object_new_with_private(DD_TYPE_CACHE, sizeof(DdCachePrivate));

	return self;
}
