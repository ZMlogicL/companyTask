/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020年9月3日
*@author              :郑蛘钊
*@brief               :
*@rely                :glib
*@function
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/


#ifndef __MRBC_TEST_H__
#define __MRBC_TEST_H__


#include <stdio.h>
#include <glib-object.h>
#include "absheadertest.h"


G_BEGIN_DECLS


#define MRBC_TYPE_TEST					 (mrbc_test_get_type())
#define MRBC_TEST(obj)				 	 (G_TYPE_CHECK_INSTANCE_CAST(obj, MRBC_TYPE_TEST, MrbcTest))
#define MRBC_TEST_CALSS(klass)           (G_TYPE_CHECK_CLASS_CAST((klass), MRBC_TYPE_TEST, MrbcTestClass))
#define MRBC_IS_TEST(obj)                (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MRBC_TYPE_TEST))
#define MRBC_IS_TEST_CLASS(klass)        (G_TYPE_CHECK_CLASS_TYPE ((klass), MRBC_TYPE_TEST))
#define MRBC_TEST_GET_CLASS(obj)         (G_TYPE_INSTANCE_GET_CLASS ((obj), MRBC_TYPE_TEST, MrbcTestClass))


typedef struct _MrbcTest                 MrbcTest;
typedef struct _MrbcTestClass            MrbcTestClass;
typedef struct _MrbcTestPrivate          MrbcTestPrivate;


struct _MrbcTest
{
	AbsHeaderTest    parent;
};

struct _MrbcTestClass
{
	AbsHeaderTestClass    parentclass;
};


GType 			mrbc_test_get_type(void) G_GNUC_CONST;
MrbcTest*       mrbc_test_new(void);
void            mrbc_test(MrbcTest* self);


G_END_DECLS


#endif /* __MRBC_TEST_H__ */
