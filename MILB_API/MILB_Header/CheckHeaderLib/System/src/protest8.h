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


#ifndef __PRO_TEST8_H__
#define __PRO_TEST8_H__


#include <stdio.h>
#include <glib-object.h>
#include "checkheadermaindefs.h"


G_BEGIN_DECLS


#define PRO_TYPE_TEST8								(pro_test8_get_type())
#define PRO_TEST8(obj)									(G_TYPE_CHECK_INSTANCE_CAST(obj, PRO_TYPE_TEST8, ProTest8))
#define PRO_TEST8_CALSS(klass)              		(G_TYPE_CHECK_CLASS_CAST((klass), PRO_TYPE_TEST8, ProTest8Class))
#define PRO_IS_TEST8(obj)                        		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), PRO_TYPE_TEST8))
#define PRO_IS_TEST8_CLASS(klass)         		(G_TYPE_CHECK_CLASS_TYPE ((klass), PRO_TYPE_TEST8))
#define PRO_TEST8_GET_CLASS(obj)         		(G_TYPE_INSTANCE_GET_CLASS ((obj), PRO_TYPE_TEST8, ProTest8Class))


typedef struct 				_ProTest8  ProTest8;
typedef struct 				_ProTest8Class  ProTest8Class;
typedef struct 				_ProTest8Private  ProTest8Private;

struct _ProTest8
{
	GObject    parent;
};

struct _ProTest8Class
{
	GObject    parentclass;
};


GType 							pro_test8_get_type(void) G_GNUC_CONST;
ProTest8 *         			pro_test8_new(void);
void 							pro_test8(ProTest8 *self, EProBlockType type, IoPro ioPro);


G_END_DECLS


#endif /* __PRO_TEST8_H__ */
