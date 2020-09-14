/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-10
*@author              :jianghaodong
*@brief               :CtDdI2c类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_I2C_H_
#define __CT_DD_I2C_H_

#include <glib-object.h>
#include "driver_common.h"


G_BEGIN_DECLS

#define CT_TYPE_DD_I2C						(ct_dd_i2c_get_type())
#define CT_DD_I2C(obj)						(G_TYPE_CHECK_INSTANCE_CAST (obj, CtDdI2c))
#define CT_DD_I2C_CLASS(klass)			(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_DD_I2C, CtDdI2cClass))
#define CT_IS_DD_I2C(obj)					(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_DD_I2C)) 
#define CT_IS_DD_I2C_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_DD_I2C))
#define CT_DD_I2C_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_DD_I2C, CtDdI2cClass))


typedef struct 			_CtDdI2c CtDdI2c;
typedef struct 			_CtDdI2cClass CtDdI2cClass;
typedef struct 			_CtDdI2cPrivate CtDdI2cPrivate;

struct _CtDdI2c
{
	GObject parent;
};

struct _CtDdI2cClass
{
	GObjectClass parentclass;
};


GType ct_dd_i2c_get_type(void);
CtDdI2c *ct_dd_i2c_new(void);

void 				ct_dd_i2c_main_main(CtDdI2c* self, gint argc, gchar** argv);


G_END_DECLS

#endif /* __CT_DD_I2C_H_ */
