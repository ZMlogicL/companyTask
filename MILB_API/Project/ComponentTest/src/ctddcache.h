/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-05
*@author              :jianghaodong
*@brief               :CtDdCache类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_CACHE_H_
#define __CT_DD_CACHE_H_

#include <klib.h>
#include "ddim_typedef.h"

#define CT_TYPE_DD_CACHE					(ct_dd_cache_get_type())
#define CT_DD_CACHE(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdCache)) 
#define CT_IS_DD_CACHE(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_CACHE)) 

typedef struct 			_CtDdCache CtDdCache;
typedef struct 			_CtDdCachePrivate CtDdCachePrivate;

struct _CtDdCache
{
	KObject parent;

};

KConstType 		ct_dd_cache_get_type(void);
CtDdCache* 		ct_dd_cache_new(void);

void 					ct_dd_cache_main_main(CtDdCache* self, kint argc, kchar** argv);


#endif /* __CT_DD_CACHE_H_ */
