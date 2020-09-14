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


#ifndef __PRO_TEST7_H__
#define __PRO_TEST7_H__


#include <stdio.h>
#include <glib-object.h>
#include "checkheadermaindefs.h"


G_BEGIN_DECLS


#define PRO_TYPE_TEST7								(pro_test7_get_type())
#define PRO_TEST7(obj)									(G_TYPE_CHECK_INSTANCE_CAST(obj, PRO_TYPE_TEST7, ProTest7))
#define PRO_TEST7_CALSS(klass)              		(G_TYPE_CHECK_CLASS_CAST((klass), PRO_TYPE_TEST7, ProTest7Class))
#define PRO_IS_TEST7(obj)                        		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), PRO_TYPE_TEST7))
#define PRO_IS_TEST7_CLASS(klass)         		(G_TYPE_CHECK_CLASS_TYPE ((klass), PRO_TYPE_TEST7))
#define PRO_TEST7_GET_CLASS(obj)         		(G_TYPE_INSTANCE_GET_CLASS ((obj), PRO_TYPE_TEST7, ProTest7Class))


typedef struct 				_ProTest7  ProTest7;
typedef struct 				_ProTest7Class  ProTest7Class;
typedef struct 				_ProTest7Private  ProTest7Private;

struct _ProTest7
{
	GObject    parent;
};

struct _ProTest7Class
{
	GObject    parentclass;
};


GType 							pro_test7_get_type(void) G_GNUC_CONST;
ProTest7 *         			pro_test7_new(void);
void 							pro_test7(ProTest7 *self, EProBlockType type, IoPro ioPro);


G_END_DECLS


#endif /* __PRO_TEST7_H__ */
