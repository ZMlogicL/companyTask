/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-10
*@author              :jianghaodong
*@brief               :CtDdArm类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_ARM_H_
#define __CT_DD_ARM_H_

#include <glib-object.h>
#include "ddim_typedef.h"

G_BEGIN_DECLS

#define CT_TYPE_DD_ARM					(ct_dd_arm_get_type())
#define CT_DD_ARM(obj)						(G_TYPE_CHECK_INSTANCE_CAST (obj, CtDdArm))
#define CT_DD_ARM_CLASS(klass)		(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_DD_ARM, CtDdArmClass))
#define CT_IS_DD_ARM(obj)				(G_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_ARM))
#define CT_IS_DD_ARM_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_DD_ARM))
#define CT_DD_ARM_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_DD_ARM, CtDdArmClass))


typedef struct 			_CtDdArm CtDdArm;
typedef struct 			_CtDdArmClass CtDdArmClass;
typedef struct 			_CtDdArmPrivate CtDdArmPrivate;

struct _CtDdArm
{
	GObject parent;
};

struct _CtDdArmClass
{
	GObjectClass parentclass;
};


GType ct_dd_arm_get_type(void);
CtDdArm *ct_dd_arm_new(void);

void 					ct_dd_arm_main_main(CtDdArm* self, gint argc, gchar** argv);

G_END_DECLS

#endif /* __CT_DD_ARM_H_ */
