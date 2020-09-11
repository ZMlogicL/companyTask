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


#ifndef __WDOG_TEST_H__
#define __WDOG_TEST_H__


#include <stdio.h>
#include <glib-object.h>
#include "internals.h"
#include "absheadertest.h"


G_BEGIN_DECLS


#define WDOG_TYPE_TEST									(wdog_test_get_type())
#define WDOG_TEST(obj)									(G_TYPE_CHECK_INSTANCE_CAST(obj, WDOG_TYPE_TEST, WdogTest))
#define WDOG_TEST_CALSS(klass)              		(G_TYPE_CHECK_CLASS_CAST((klass), WDOG_TYPE_TEST, WdogTestClass))
#define WDOG_IS_TEST(obj)                        		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), WDOG_TYPE_TEST))
#define WDOG_IS_TEST_CLASS(klass)         		(G_TYPE_CHECK_CLASS_TYPE ((klass), WDOG_TYPE_TEST))
#define WDOG_TEST_GET_CLASS(obj)         		(G_TYPE_INSTANCE_GET_CLASS ((obj), WDOG_TYPE_TEST, WdogTestClass))


typedef struct _WdogTest                       		WdogTest;
typedef struct _WdogTestClass            		WdogTestClass;
typedef struct _WdogTestPrivate           		WdogTestPrivate;

struct _WdogTest
{
	AbsHeaderTest    parent;
};

struct _WdogTestClass
{
	AbsHeaderTestClass    parentclass;
};


GType 							wdog_test_get_type(void) G_GNUC_CONST;
WdogTest *         		wdog_test_new(void);
void 							wdog_test();


G_END_DECLS


#endif /* __WDOG_TEST_H__ */
