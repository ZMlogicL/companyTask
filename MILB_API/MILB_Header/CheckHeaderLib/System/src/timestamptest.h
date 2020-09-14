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


#ifndef __TIMESTAMP_TEST_H__
#define __TIMESTAMP_TEST_H__


#include <stdio.h>
#include <glib-object.h>
#include "checkheadermaindefs.h"
#include "absheadertest.h"


G_BEGIN_DECLS


#define TIMESTAMP_TYPE_TEST									(timestamp_test_get_type())
#define TIMESTAMP_TEST(obj)									(G_TYPE_CHECK_INSTANCE_CAST(obj, TIMESTAMP_TYPE_TEST, TimestampTest))
#define TIMESTAMP_TEST_CALSS(klass)              		(G_TYPE_CHECK_CLASS_CAST((klass), TIMESTAMP_TYPE_TEST, TimestampTestClass))
#define TIMESTAMP_IS_TEST(obj)                        		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), TIMESTAMP_TYPE_TEST))
#define TIMESTAMP_IS_TEST_CLASS(klass)         		(G_TYPE_CHECK_CLASS_TYPE ((klass), TIMESTAMP_TYPE_TEST))
#define TIMESTAMP_TEST_GET_CLASS(obj)         		(G_TYPE_INSTANCE_GET_CLASS ((obj), TIMESTAMP_TYPE_TEST, TimestampTestClass))


typedef struct _TimestampTest                       	TimestampTest;
typedef struct _TimestampTestClass            		TimestampTestClass;
typedef struct _TimestampTestPrivate           	TimestampTestPrivate;

struct _TimestampTest
{
	AbsHeaderTest    parent;
};

struct _TimestampTestClass
{
	AbsHeaderTestClass    parentclass;
};


GType 									timestamp_test_get_type(void) G_GNUC_CONST;
TimestampTest *         		timestamp_test_new(void);
void 									timestamp_test();


G_END_DECLS


#endif /* __TIMESTAMP_TEST_H__ */
