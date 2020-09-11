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
#ifndef __GTIMER_TEST_H__
#define __GTIMER_TEST_H__


#include <stdio.h>
#include <glib-object.h>
#include "absheadertest.h"


G_BEGIN_DECLS


#define GTIMER_TYPE_TEST								(gtimer_test_get_type())
#define GTIMER_TEST(obj)									(G_TYPE_CHECK_INSTANCE_CAST(obj, GTIMER_TYPE_TEST, GtimerTest))
#define GTIMER_TEST_CALSS(klass)              		(G_TYPE_CHECK_CLASS_CAST((klass), GTIMER_TYPE_TEST, GtimerTestClass))
#define GTIMER_IS_TEST(obj)                        		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTIMER_TYPE_TEST))
#define GTIMER_IS_TEST_CLASS(klass)         		(G_TYPE_CHECK_CLASS_TYPE ((klass), GTIMER_TYPE_TEST))
#define GTIMER_TEST_GET_CLASS(obj)         		(G_TYPE_INSTANCE_GET_CLASS ((obj), GTIMER_TYPE_TEST, GtimerTestClass))


typedef struct _GtimerTest                       	GtimerTest;
typedef struct _GtimerTestClass            		GtimerTestClass;
typedef struct _GtimerTestPrivate           	GtimerTestPrivate;


struct _GtimerTest
{
	AbsHeaderTest    parent;
};

struct _GtimerTestClass
{
	AbsHeaderTestClass    parentclass;
};


GType 							gtimer_test_get_type(void) G_GNUC_CONST;
GtimerTest *         		gtimer_test_new(void);


G_END_DECLS


#endif /* __GTIMER_TEST_H__ */
