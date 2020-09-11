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
#ifndef __DDR_TEST_H__
#define __DDR_TEST_H__


#include <stdio.h>
#include <glib-object.h>
#include "absheadertest.h"


G_BEGIN_DECLS


#define DDR_TYPE_TEST									(ddr_test_get_type())
#define DDR_TEST(obj)									(G_TYPE_CHECK_INSTANCE_CAST(obj, DDR_TYPE_TEST, DdrTest))
#define DDR_TEST_CALSS(klass)              		(G_TYPE_CHECK_CLASS_CAST((klass), DDR_TYPE_TEST, DdrTestClass))
#define DDR_IS_TEST(obj)                        		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), DDR_TYPE_TEST))
#define DDR_IS_TEST_CLASS(klass)         		(G_TYPE_CHECK_CLASS_TYPE ((klass), DDR_TYPE_TEST))
#define DDR_TEST_GET_CLASS(obj)         		(G_TYPE_INSTANCE_GET_CLASS ((obj), DDR_TYPE_TEST, DdrTestClass))


typedef struct _DdrTest                       	DdrTest;
typedef struct _DdrTestClass            		DdrTestClass;
typedef struct _DdrTestPrivate           		DdrTestPrivate;


struct _DdrTest
{
	AbsHeaderTest    parent;
};

struct _DdrTestClass
{
	AbsHeaderTestClass    parentclass;
};


GType 						ddr_test_get_type(void) G_GNUC_CONST;
DdrTest *         		ddr_test_new(void);


G_END_DECLS


#endif /* __DDR_TEST_H__ */
