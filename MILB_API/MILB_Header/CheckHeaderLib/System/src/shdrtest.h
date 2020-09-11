/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020年9月3日
*@author              :申雨
*@brief               :
*@rely                :glib
*@function
*设计的主要功能:
*1、
*@version
*
*/


#ifndef __SHDR_TEST_H__
#define __SHDR_TEST_H__


#include <stdio.h>
#include <glib-object.h>
#include "internals.h"
#include "absheadertest.h"


G_BEGIN_DECLS


#define SHDR_TYPE_TEST							(shdr_test_get_type())
#define SHDR_TEST(obj)								(G_TYPE_CHECK_INSTANCE_CAST(obj, SHDR_TYPE_TEST, ShdrTest))
#define SHDR_TEST_CALSS(klass)              	(G_TYPE_CHECK_CLASS_CAST((klass), SHDR_TYPE_TEST, ShdrTestClass))
#define SHDR_IS_TEST(obj)                        	(G_TYPE_CHECK_INSTANCE_TYPE ((obj), SHDR_TYPE_TEST))
#define SHDR_IS_TEST_CLASS(klass)         	(G_TYPE_CHECK_CLASS_TYPE ((klass), SHDR_TYPE_TEST))
#define SHDR_TEST_GET_CLASS(obj)         	(G_TYPE_INSTANCE_GET_CLASS ((obj), SHDR_TYPE_TEST, ShdrTestClass))


typedef struct _ShdrTest                       	ShdrTest;
typedef struct _ShdrTestClass            		ShdrTestClass;
typedef struct _ShdrTestPrivate           	ShdrTestPrivate;


struct _ShdrTest
{
	AbsHeaderTest    parent;
};

struct _ShdrTestClass
{
	AbsHeaderTestClass    parentclass;
};


GType 						shdr_test_get_type(void) G_GNUC_CONST;
ShdrTest *         		shdr_test_new(void);
void 						shdr_test();


G_END_DECLS


#endif /* __SHDR_TEST_H__ */
