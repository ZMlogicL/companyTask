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
#ifndef __EXIU_TEST_H__
#define __EXIU_TEST_H__


#include <stdio.h>
#include <glib-object.h>
#include "absheadertest.h"


G_BEGIN_DECLS


#define EXIU_TYPE_TEST									(exiu_test_get_type())
#define EXIU_TEST(obj)									(G_TYPE_CHECK_INSTANCE_CAST(obj, EXIU_TYPE_TEST, ExiuTest))
#define EXIU_TEST_CALSS(klass)              		(G_TYPE_CHECK_CLASS_CAST((klass), EXIU_TYPE_TEST, ExiuTestClass))
#define EXIU_IS_TEST(obj)                        		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), EXIU_TYPE_TEST))
#define EXIU_IS_TEST_CLASS(klass)         		(G_TYPE_CHECK_CLASS_TYPE ((klass), EXIU_TYPE_TEST))
#define EXIU_TEST_GET_CLASS(obj)         		(G_TYPE_INSTANCE_GET_CLASS ((obj), EXIU_TYPE_TEST, ExiuTestClass))


typedef struct _ExiuTest                       	ExiuTest;
typedef struct _ExiuTestClass            		ExiuTestClass;
typedef struct _ExiuTestPrivate           	ExiuTestPrivate;


struct _ExiuTest
{
	AbsHeaderTest    parent;
};

struct _ExiuTestClass
{
	AbsHeaderTestClass    parentclass;
};


GType 						exiu_test_get_type(void) G_GNUC_CONST;
ExiuTest *         		exiu_test_new(void);


G_END_DECLS


#endif /* __EXIU_TEST_H__ */
