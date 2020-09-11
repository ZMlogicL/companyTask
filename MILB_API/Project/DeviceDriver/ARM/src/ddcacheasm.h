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


#ifndef DD_CACHE_ASM_H_
#define DD_CACHE_ASM_H_


#include"ddcache.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
Level 1 D-Cache ALL Flush function
@remarks	This function ALL flush is Level 1 Cache Only.
*/
void				Dd_CACHE_L1_Flush_Dcache_All(void);

/**
Level 1 D-Cache ALL Clean function
@remarks	This function ALL Clean is Level 1 Cache Only.
*/
void				Dd_CACHE_L1_Clean_Dcache_All(void);

/**
Level 1 D-Cache ALL Clean & Flush function
@remarks	This function ALL Clean is Level 1 Cache Only.
*/
void				Dd_CACHE_L1_Clean_Flush_Dcache_All(void);

/**
Level 2 D-Cache ALL Flush function
@remarks	This function ALL flush is Level 2 Cache Only.
*/
void				Dd_CACHE_L2_Flush_Dcache_All(void);

/**
Level 2 D-Cache ALL Clean function
@remarks	This function ALL Clean is Level 2 Cache Only.
*/
void				Dd_CACHE_L2_Clean_Dcache_All(void);

/**
Level 2 D-Cache ALL Clean & Flush function
@remarks	This function ALL Clean is Level 2 Cache Only.
*/
void				Dd_CACHE_L2_Clean_Flush_Dcache_All(void);

#ifdef __cplusplus
}
#endif

#endif /* DD_CACHE_ASM_H_ */
