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
#ifndef __GIC_TEST_H__
#define __GIC_TEST_H__


#include <stdio.h>
#include <glib-object.h>
#include "absheadertest.h"


G_BEGIN_DECLS


#define GIC_TYPE_TEST								(gic_test_get_type())
#define GIC_TEST(obj)									(G_TYPE_CHECK_INSTANCE_CAST(obj, GIC_TYPE_TEST, GicTest))
#define GIC_TEST_CALSS(klass)              		(G_TYPE_CHECK_CLASS_CAST((klass), GIC_TYPE_TEST, GicTestClass))
#define GIC_IS_TEST(obj)                        		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIC_TYPE_TEST))
#define GIC_IS_TEST_CLASS(klass)         		(G_TYPE_CHECK_CLASS_TYPE ((klass), GIC_TYPE_TEST))
#define GIC_TEST_GET_CLASS(obj)         		(G_TYPE_INSTANCE_GET_CLASS ((obj), GIC_TYPE_TEST, GicTestClass))


typedef struct _GicTest                       	GicTest;
typedef struct _GicTestClass            	GicTestClass;
typedef struct _GicTestPrivate           	GicTestPrivate;


struct _GicTest
{
	AbsHeaderTest    parent;
};

struct _GicTestClass
{
	AbsHeaderTestClass    parentclass;
};


GType 						gic_test_get_type(void) G_GNUC_CONST;
GicTest *         		gic_test_new(void);


G_END_DECLS


#endif /* __GIC_TEST_H__ */
