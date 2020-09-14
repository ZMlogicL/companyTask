/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-03
*@author              :申雨
*@brief               :sns 索喜rtos
*@rely                :glib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年09月开始开发
*/


#ifndef __PRO_TEST6_H__
#define __PRO_TEST6_H__


#include <stdio.h>
#include <glib-object.h>
#include "checkheadermaindefs.h"


G_BEGIN_DECLS


#define PRO_TYPE_TEST6								(pro_test6_get_type())
#define PRO_TEST6(obj)									(G_TYPE_CHECK_INSTANCE_CAST(obj, PRO_TYPE_TEST6, ProTest6))
#define PRO_TEST6_CALSS(klass)              		(G_TYPE_CHECK_CLASS_CAST((klass), PRO_TYPE_TEST6, ProTest6Class))
#define PRO_IS_TEST6(obj)                        		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), PRO_TYPE_TEST6))
#define PRO_IS_TEST6_CLASS(klass)         		(G_TYPE_CHECK_CLASS_TYPE ((klass), PRO_TYPE_TEST6))
#define PRO_TEST6_GET_CLASS(obj)         		(G_TYPE_INSTANCE_GET_CLASS ((obj), PRO_TYPE_TEST6, ProTest6Class))


typedef struct 				_ProTest6  ProTest6;
typedef struct 				_ProTest6Class  ProTest6Class;
typedef struct 				_ProTest6Private  ProTest6Private;

struct _ProTest6
{
	GObject    parent;
};

struct _ProTest6Class
{
	GObject    parentclass;
};


GType 							pro_test6_get_type(void) G_GNUC_CONST;
ProTest6 *         			pro_test6_new(void);
void 							pro_test6(ProTest6 *self, EProBlockType type, IoPro ioPro);


G_END_DECLS


#endif /* __PRO_TEST6_H__ */
