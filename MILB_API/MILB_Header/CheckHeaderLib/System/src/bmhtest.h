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
#ifndef __BMH_TEST_H__
#define __BMH_TEST_H__


#include <stdio.h>
#include <glib-object.h>
#include "absheadertest.h"


G_BEGIN_DECLS


#define BMH_TYPE_TEST									(bmh_test_get_type())
#define BMH_TEST(obj)									(G_TYPE_CHECK_INSTANCE_CAST(obj, BMH_TYPE_TEST, BmhTest))
#define BMH_TEST_CALSS(klass)              		(G_TYPE_CHECK_CLASS_CAST((klass), BMH_TYPE_TEST, BmhTestClass))
#define BMH_IS_TEST(obj)                        		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), BMH_TYPE_TEST))
#define BMH_IS_TEST_CLASS(klass)         		(G_TYPE_CHECK_CLASS_TYPE ((klass), BMH_TYPE_TEST))
#define BMH_TEST_GET_CLASS(obj)         		(G_TYPE_INSTANCE_GET_CLASS ((obj), BMH_TYPE_TEST, BmhTestClass))


typedef struct _BmhTest                       	BmhTest;
typedef struct _BmhTestClass            		BmhTestClass;
typedef struct _BmhTestPrivate           	BmhTestPrivate;


struct _BmhTest
{
	AbsHeaderTest    parent;
};

struct _BmhTestClass
{
	AbsHeaderTestClass    parentclass;
};


GType 						bmh_test_get_type(void) G_GNUC_CONST;
BmhTest *         		bmh_test_new(void);


G_END_DECLS


#endif /* __BMH_TEST_H__ */
