/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-10
*@author              :jianghaodong
*@brief               :CtDdExiu类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_EXIU_H_
#define __CT_DD_EXIU_H_

#include <glib-object.h>

G_BEGIN_DECLS

#define CT_TYPE_DD_EXIU					(ct_dd_exiu_get_type())
#define CT_DD_EXIU(obj)					(G_TYPE_CHECK_INSTANCE_CAST (obj, CtDdExiu)) 
#define CT_DD_EXIU_CLASS(klass)					(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_DD_EXIU, CtDdExiuClass)) 
#define CT_IS_DD_EXIU(obj)					(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_DD_EXIU)) 
#define CT_IS_DD_EXIU_CLASS(klass)					(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_DD_EXIU)) 
#define CT_DD_EXIU_GET_CLASS(obj)					(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_DD_EXIU, CtDdExiuClass)) 


typedef struct 			_CtDdExiu CtDdExiu;
typedef struct 			_CtDdExiuClass CtDdExiuClass;
typedef struct 			_CtDdExiuPrivate CtDdExiuPrivate;

struct _CtDdExiu
{
	GObject parent;
};

struct _CtDdExiuClass
{
	GObjectClass parentclass;
};


GType ct_dd_exiu_get_type(void);
CtDdExiu *ct_dd_exiu_new(void);

void 					ct_dd_exiu_main_main(CtDdExiu *self, gint argc, gchar** argv);

G_END_DECLS

#endif /* __CT_DD_EXIU_H_ */
