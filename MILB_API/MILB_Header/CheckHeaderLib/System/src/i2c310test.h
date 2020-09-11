/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020年9月3日
*@author              :陈柱
*@brief               :
*@rely                :glib
*@function
*设计的主要功能:
*1、
*@version
*
*/
#ifndef __I2C310_TEST_H__
#define __I2C310_TEST_H__


#include <stdio.h>
#include <glib-object.h>
#include "absheadertest.h"


G_BEGIN_DECLS


#define I2C310_TYPE_TEST									(i2c310_test_get_type())
#define I2C310_TEST(obj)									(G_TYPE_CHECK_INSTANCE_CAST(obj, I2C310_TYPE_TEST, I2c310Test))
#define I2C310_TEST_CALSS(klass)              		(G_TYPE_CHECK_CLASS_CAST((klass), I2C310_TYPE_TEST, I2c310TestClass))
#define I2C310_IS_TEST(obj)                        		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), I2C310_TYPE_TEST))
#define I2C310_IS_TEST_CLASS(klass)         		(G_TYPE_CHECK_CLASS_TYPE ((klass), I2C310_TYPE_TEST))
#define I2C310_TEST_GET_CLASS(obj)         		(G_TYPE_INSTANCE_GET_CLASS ((obj), I2C310_TYPE_TEST, I2c310TestClass))


typedef struct _I2c310Test                       	I2c310Test;
typedef struct _I2c310TestClass            		I2c310TestClass;
typedef struct _I2c310TestPrivate           	I2c310TestPrivate;


struct _I2c310Test
{
	AbsHeaderTest    parent;
};

struct _I2c310TestClass
{
	AbsHeaderTestClass    parentclass;
};


GType 							i2c310_test_get_type(void) G_GNUC_CONST;
I2c310Test *         		i2c310_test_new(void);


G_END_DECLS


#endif /* __I2C310_TEST_H__ */
