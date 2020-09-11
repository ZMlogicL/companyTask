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
#ifndef __ME_TEST_H__
#define __ME_TEST_H__


#include <stdio.h>
#include <glib-object.h>
#include "absheadertest.h"


G_BEGIN_DECLS


#define ME_TYPE_TEST								(me_test_get_type())
#define ME_TEST(obj)									(G_TYPE_CHECK_INSTANCE_CAST(obj, ME_TYPE_TEST, MeTest))
#define ME_TEST_CALSS(klass)              		(G_TYPE_CHECK_CLASS_CAST((klass), ME_TYPE_TEST, MeTestClass))
#define ME_IS_TEST(obj)                        		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), ME_TYPE_TEST))
#define ME_IS_TEST_CLASS(klass)         		(G_TYPE_CHECK_CLASS_TYPE ((klass), ME_TYPE_TEST))
#define ME_TEST_GET_CLASS(obj)         		(G_TYPE_INSTANCE_GET_CLASS ((obj), ME_TYPE_TEST, MeTestClass))


typedef struct _MeTest                       	MeTest;
typedef struct _MeTestClass            	MeTestClass;
typedef struct _MeTestPrivate           	MeTestPrivate;


struct _MeTest
{
	AbsHeaderTest    parent;
};

struct _MeTestClass
{
	AbsHeaderTestClass    parentclass;
};


GType 						me_test_get_type(void) G_GNUC_CONST;
MeTest *         		me_test_new(void);


G_END_DECLS


#endif /* __ME_TEST_H__ */
