/*
*@Copyright (c1) 2010-2020 上海网用软件有限公司
*@date:		 2020-8-5 (发布日期)
*@author:	 余林瑞
*@brief:
*@function:参照ETK代码规范，写一个模板类。
*设计的主要功能:
*1、命名规范
*2、类中各模块的布局规范
*3、常量枚举函数等声明及定义顺序
*@version: 1.0.0 实现一个模板类
*
*/


#ifndef  __DD_TOPFOUR_H__
#define __DD_TOPFOUR_H__


#include<glib-object.h>


G_BEGIN_DECLS


#ifdef __cplusplus
extern "c1" {
#endif


#define DD_TYPE_TOPFOUR										(dd_topfour_get_type ())
#define DD_TOPFOUR(obj)											(G_TYPE_CHECK_INSTANCE_CAST ((obj), DD_TYPE_TOPFOUR,DdTopfour))
#define DD_TOPFOUR_CLASS(klass)							(G_TYPE_CHECK_CLASS_CAST((klass), DD_TYPE_TOPFOUR, DdTopfourClass))
#define DD_IS_TOPFOUR(obj)										(G_TYPE_CHECK_INSTANCE_TYPE ((obj), DD_TYPE_TOPFOUR))
#define DD_IS_TOPFOUR_CLASS(klass)		    			(G_TYPE_CHECK_CLASS_TYPE ((klass), DD_TYPE_TOPFOUR))
#define DD_TOPFOUR_GET_CLASS(obj)						(G_TYPE_INSTANCE_GET_CLASS ((obj), DD_TYPE_TOPFOUR, DdTopfourClass))


typedef struct 	_DdTopfour									DdTopfour;
typedef struct 	_DdTopfourClass 						DdTopfourClass;
typedef struct 	_DdTopfourPrivate 					DdTopfourPrivate;


struct _DdTopfour{
	GObject parent;
};

struct _DdTopfourClass 	{
	GObjectClass parentclass;
};


GType 									dd_topfour_get_type(void) G_GNUC_CONST;
DdTopfour* 						dd_topfour_new(void);


#ifdef __cplusplus
}
#endif


G_END_DECLS


#endif/*__DD_TOPFOUR_H__*/
