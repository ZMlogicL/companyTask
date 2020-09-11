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
 * @file		ddcache.h
 * @brief		Cache Operation driver
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */
/**
@addtogroup dd_cache
@{
	- @ref dd_cache_sample_section1
	- @ref dd_cache_sample_section2
*/


#ifndef __DD_CACHE_H__
#define __DD_CACHE_H__


#include <klib.h>
#include "driver_common.h"
#include "ddcacheasm.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DD_TYPE_CACHE                  (dd_cache_get_type())
#define DD_CACHE(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, DdCache))
#define DD_IS_CACHE(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, DD_TYPE_CACHE))

#define C_ALIGN_64BIT_MASK			((1 << 6) - 1)	/**< local mask 64bit for D-cache address */
/** Level 1 Cache Flush D-cache for CPU, by address with align */
#define DdCache_L1_FLUSH_DCACHE_ADDR(adrs,size)		dd_cache_l1_flush_dcache_addr_align(NULL, \
		(adrs)&(~C_ALIGN_64BIT_MASK),((adrs)&C_ALIGN_64BIT_MASK)+(size))
/** Level 1 Cache Clean D-cache for CPU, by address with align */
#define DdCache_L1_CLEAN_DCACHE_ADDR(adrs,size)		dd_cache_l1_clean_dcache_addr_align(NULL,\
		(adrs)&(~C_ALIGN_64BIT_MASK),((adrs)&C_ALIGN_64BIT_MASK)+(size))
/** Level 1 Cache Clean & Flush D-cache for CPU, by address with align */
#define DdCache_L1_CLEAN_FLUSH_DCACHE_ADDR(adrs,size)	dd_cache_l1_clean_flush_dcache_addr_align(NULL,\
		(adrs)&(~C_ALIGN_64BIT_MASK),((adrs)&C_ALIGN_64BIT_MASK)+(size))
/** Level 2 Cache Flush D-cache for CPU, by address with align */
#define DdCache_L2_FLUSH_DCACHE_ADDR(adrs,size)		dd_cache_l2_flush_dcache_addr_align(NULL,\
		(adrs)&(~C_ALIGN_64BIT_MASK),((adrs)&C_ALIGN_64BIT_MASK)+(size))
/** Level 2 Cache Clean D-cache for CPU, by address with align */
#define DdCache_L2_CLEAN_DCACHE_ADDR(adrs,size)		dd_cache_l2_clean_dcache_addr_align(NULL,\
		(adrs)&(~C_ALIGN_64BIT_MASK),((adrs)&C_ALIGN_64BIT_MASK)+(size))
/** Level 2 Cache Clean & Flush D-cache for CPU, by address with align */
#define DdCache_L2_CLEAN_FLUSH_DCACHE_ADDR(adrs,size)	dd_cache_l2_clean_flush_dcache_addr_align(NULL, \
		(adrs)&(~C_ALIGN_64BIT_MASK),((adrs)&C_ALIGN_64BIT_MASK)+(size))


typedef struct _DdCache DdCache;
typedef struct _DdCachePrivate DdCachePrivate;

struct _DdCache
{
	KObject parent;
};


KConstType		dd_cache_get_type(void);
DdCache*		dd_cache_new(void);
/**
Level 1 D-Cache Flush by Addressing & size function
@param[in]		address		: target start address
@param[in]		size		: target size
@remarks	This function flush is Level 1 Cache Only.
*/
void				dd_cache_l1_flush_dcache_addr_align(DdCache *self, kuint32 address, kuint32 size);

/**
Level 1 D-Cache Clean by Addressing & size function
@param[in]		address		: target start address
@param[in]		size		: target size
@remarks	This function clean is Level 1 Cache Only.
*/
void				dd_cache_l1_clean_dcache_addr_align(DdCache *self, kuint32 address, kuint32 size);

/**
Level 1 D-Cache Clean & Flush by Addressing & size function
@param[in]		address		: target start address
@param[in]		size		: target size
@remarks	This function clean & flush is Level 1 Cache Only.
*/
void				dd_cache_l1_clean_flush_dcache_addr_align(DdCache *self, kuint32 address, kuint32 size);

/**
Level 2 D-Cache Flush by Addressing & size function
@param[in]		address		: target start address
@param[in]		size		: target size
@remarks	This function flush is Level 2 Cache Only.
*/
void				dd_cache_l2_flush_dcache_addr_align(DdCache *self, kuint32 address, kuint32 size);

/**
Level 2 D-Cache Clean by Addressing & size function
@param[in]		address		: target start address
@param[in]		size		: target size
@remarks	This function clean is Level 2 Cache Only.
*/
void				dd_cache_l2_clean_dcache_addr_align(DdCache *self, kuint32 address, kuint32 size);

/**
Level 2 D-Cache Clean & Flush by Addressing & size function
@param[in]		address		: target start address
@param[in]		size		: target size
@remarks	This function clean & flush is Level 2 Cache Only.
*/
void				dd_cache_l2_clean_flush_dcache_addr_align(DdCache *self, kuint32 address, kuint32 size);

/*@}*/

/**
@weakgroup dd_arm
@{
	@section dd_cache_sample_section1		Sample of Clean & Flush by Addressing & size
	@code
	//
	// CPU accessing in same memory area.
	//
	DdCache_L1_CLEAN_FLUSH_DCACHE_ADDR( adrs, size );
	DD_ARM_DSB_POU();
	DdCache_L2_CLEAN_FLUSH_DCACHE_ADDR( adrs, size );
	//
	// Macro and/or DMA accessing in same memory area.
	//
	@endcode
	<br>
	@section dd_cache_sample_section2		Sample of Clean & Flush by All Address
	@code
	//
	// CPU accessing in same memory area.
	//
	Dd_CACHE_L1_Clean_Flush_Dcache_All();
	DD_ARM_DSB_POU();
	Dd_CACHE_L2_Clean_Flush_Dcache_All();
	//
	// Macro and/or DMA accessing in same memory area.
	//
	@endcode
@}*/

#ifdef __cplusplus
}
#endif

#endif /* __DD_CACHE_H__ */
