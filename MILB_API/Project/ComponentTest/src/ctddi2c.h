/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-05
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

#include <klib.h>

#define CT_TYPE_DD_I2C					(ct_dd_i2c_get_type())
#define CT_DD_I2C(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdI2c)) 
#define CT_IS_DD_I2C(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_I2C)) 

typedef struct 			_CtDdI2c CtDdI2c;
typedef struct 			_CtDdI2cPrivate CtDdI2cPrivate;

struct _CtDdI2c
{
	KObject parent;

};

KConstType 	ct_dd_i2c_get_type(void);
CtDdI2c* 		ct_dd_i2c_new(void);

void 				ct_dd_i2c_main_main(CtDdI2c* self, kint argc, kchar** argv);



#endif /* __CT_DD_I2C_H_ */
