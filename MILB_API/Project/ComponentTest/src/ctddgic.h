/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-10
*@author              :jianghaodong
*@brief               :CtDdGic类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_GIC_H_
#define __CT_DD_GIC_H_

#include <glib-object.h>
#include "ddim_typedef.h"



G_BEGIN_DECLS

#define CT_TYPE_DD_GIC						(ct_dd_gic_get_type())
#define CT_DD_GIC(obj)						(G_TYPE_CHECK_INSTANCE_CAST (obj, CtDdGic))
#define CT_DD_GIC_CLASS(klass)		(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_DD_GIC, CtDdGicClass))
#define CT_IS_DD_GIC(obj)					(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_DD_GIC)) 
#define CT_IS_DD_GIC_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_DD_GIC))
#define CT_DD_GIC_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_DD_GIC, CtDdGicClass))


typedef struct 			_CtDdGic CtDdGic;
typedef struct 			_CtDdGicClass CtDdGicClass;
typedef struct 			_CtDdGicPrivate CtDdGicPrivate;

struct _CtDdGic
{
	GObject parent;
};

struct _CtDdGicClass
{
	GObjectClass parentclass;
};


GType ct_dd_gic_get_type(void);
CtDdGic *ct_dd_gic_new(void);

void 					ct_dd_gic_main_main(CtDdGic* self, gint argc, gchar** argv);

G_END_DECLS

#endif /* __CT_DD_GIC_H_ */
