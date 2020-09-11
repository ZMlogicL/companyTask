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


#ifndef __XDMAC_TEST_H__
#define __XDMAC_TEST_H__


#include <stdio.h>
#include <glib-object.h>
#include "internals.h"
#include "absheadertest.h"


G_BEGIN_DECLS


#define XDMAC_TYPE_TEST									(xdmac_test_get_type())
#define XDMAC_TEST(obj)									(G_TYPE_CHECK_INSTANCE_CAST(obj, XDMAC_TYPE_TEST, XdmacTest))
#define XDMAC_TEST_CALSS(klass)              		(G_TYPE_CHECK_CLASS_CAST((klass), XDMAC_TYPE_TEST, XdmacTestClass))
#define XDMAC_IS_TEST(obj)                        		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), XDMAC_TYPE_TEST))
#define XDMAC_IS_TEST_CLASS(klass)         		(G_TYPE_CHECK_CLASS_TYPE ((klass), XDMAC_TYPE_TEST))
#define XDMAC_TEST_GET_CLASS(obj)         		(G_TYPE_INSTANCE_GET_CLASS ((obj), XDMAC_TYPE_TEST, XdmacTestClass))


typedef struct _XdmacTest                       	XdmacTest;
typedef struct _XdmacTestClass            		XdmacTestClass;
typedef struct _XdmacTestPrivate           	XdmacTestPrivate;

struct _XdmacTest
{
	AbsHeaderTest    parent;
};

struct _XdmacTestClass
{
	AbsHeaderTestClass    parentclass;
};


GType 							xdmac_test_get_type(void) G_GNUC_CONST;
XdmacTest *         		xdmac_test_new(void);
void 							xdmac_test();


G_END_DECLS


#endif /* __XDMAC_TEST_H__ */
