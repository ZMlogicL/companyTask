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
#ifndef __B2R_TEST_H__
#define __B2R_TEST_H__


#include <stdio.h>
#include <glib-object.h>
#include "absheadertest.h"


G_BEGIN_DECLS


#define B2R_TYPE_TEST									(b2r_test_get_type())
#define B2R_TEST(obj)										(G_TYPE_CHECK_INSTANCE_CAST(obj, B2R_TYPE_TEST, B2rTest))
#define B2R_TEST_CALSS(klass)              			(G_TYPE_CHECK_CLASS_CAST((klass), B2R_TYPE_TEST, B2rTestClass))
#define B2R_IS_TEST(obj)                        		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), B2R_TYPE_TEST))
#define B2R_IS_TEST_CLASS(klass)         			(G_TYPE_CHECK_CLASS_TYPE ((klass), B2R_TYPE_TEST))
#define B2R_TEST_GET_CLASS(obj)         		(G_TYPE_INSTANCE_GET_CLASS ((obj), B2R_TYPE_TEST, B2rTestClass))


typedef struct _B2rTest                       		B2rTest;
typedef struct _B2rTestClass            		B2rTestClass;
typedef struct _B2rTestPrivate           		B2rTestPrivate;


struct _B2rTest
{
	AbsHeaderTest    parent;
};

struct _B2rTestClass
{
	AbsHeaderTestClass    parentclass;
};


GType 						b2r_test_get_type(void) G_GNUC_CONST;
B2rTest *         		b2r_test_new(void);


G_END_DECLS


#endif /* __B2R_TEST_H__ */
