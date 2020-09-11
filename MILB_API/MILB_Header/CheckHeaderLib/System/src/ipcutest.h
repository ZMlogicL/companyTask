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
#ifndef __IPCU_TEST_H__
#define __IPCU_TEST_H__


#include <stdio.h>
#include <glib-object.h>
#include "absheadertest.h"


G_BEGIN_DECLS


#define IPCU_TYPE_TEST									(ipcu_test_get_type())
#define IPCU_TEST(obj)									(G_TYPE_CHECK_INSTANCE_CAST(obj, IPCU_TYPE_TEST, IpcuTest))
#define IPCU_TEST_CALSS(klass)              		(G_TYPE_CHECK_CLASS_CAST((klass), IPCU_TYPE_TEST, IpcuTestClass))
#define IPCU_IS_TEST(obj)                        		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), IPCU_TYPE_TEST))
#define IPCU_IS_TEST_CLASS(klass)         		(G_TYPE_CHECK_CLASS_TYPE ((klass), IPCU_TYPE_TEST))
#define IPCU_TEST_GET_CLASS(obj)         		(G_TYPE_INSTANCE_GET_CLASS ((obj), IPCU_TYPE_TEST, IpcuTestClass))


typedef struct _IpcuTest                       	IpcuTest;
typedef struct _IpcuTestClass            		IpcuTestClass;
typedef struct _IpcuTestPrivate           	IpcuTestPrivate;


struct _IpcuTest
{
	AbsHeaderTest    parent;
};

struct _IpcuTestClass
{
	AbsHeaderTestClass    parentclass;
};


GType 						ipcu_test_get_type(void) G_GNUC_CONST;
IpcuTest *         		ipcu_test_new(void);


G_END_DECLS


#endif /* __IPCU_TEST_H__ */
