/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-10
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

#include <glib-object.h>
#include "ddim_typedef.h"


G_BEGIN_DECLS

#define CT_TYPE_DD_CACHE					(ct_dd_cache_get_type())
#define CT_DD_CACHE(obj)						(G_TYPE_CHECK_INSTANCE_CAST (obj, CtDdCache))
#define CT_DD_CACHE_CLASS(klass)		(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_DD_CACHE, CtDdCacheClass))
#define CT_IS_DD_CACHE(obj)					(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_DD_CACHE)) 
#define CT_IS_DD_CACHE_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_DD_CACHE))
#define CT_DD_CACHE_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_DD_CACHE, CtDdCacheClass))


typedef struct 			_CtDdCache CtDdCache;
typedef struct 			_CtDdCacheClass CtDdCacheClass;
typedef struct 			_CtDdCachePrivate CtDdCachePrivate;

struct _CtDdCache
{
	GObject parent;
};

struct _CtDdCacheClass
{
	GObjectClass parentclass;
};


GType 					ct_dd_cache_get_type(void);
CtDdCache *		ct_dd_cache_new(void);

void 					ct_dd_cache_main_main(CtDdCache* self, gint argc, gchar** argv);


G_END_DECLS

#endif /* __CT_DD_CACHE_H_ */
