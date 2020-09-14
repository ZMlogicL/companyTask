/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020年9月3日
*@author              :郑蛘钊
*@brief               :
*@rely                :glib
*@function
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/


#ifndef __NETSEC_TEST_H__
#define __NETSEC_TEST_H__


#include <stdio.h>
#include <glib-object.h>
#include "absheadertest.h"


G_BEGIN_DECLS


#define NETSEC_TYPE_TEST			    (netsec_test_get_type())
#define NETSEC_TEST(obj)			    (G_TYPE_CHECK_INSTANCE_CAST(obj, NETSEC_TYPE_TEST, NetsecTest))
#define NETSEC_TEST_CALSS(klass)        (G_TYPE_CHECK_CLASS_CAST((klass), NETSEC_TYPE_TEST, NetsecTestClass))
#define NETSEC_IS_TEST(obj)             (G_TYPE_CHECK_INSTANCE_TYPE ((obj), NETSEC_TYPE_TEST))
#define NETSEC_IS_TEST_CLASS(klass)     (G_TYPE_CHECK_CLASS_TYPE ((klass), NETSEC_TYPE_TEST))
#define NETSEC_TEST_GET_CLASS(obj)      (G_TYPE_INSTANCE_GET_CLASS ((obj), NETSEC_TYPE_TEST, NetsecTestClass))


typedef struct _NetsecTest             	NetsecTest;
typedef struct _NetsecTestClass         NetsecTestClass;
typedef struct _NetsecTestPrivate      	NetsecTestPrivate;


struct _NetsecTest
{
	AbsHeaderTest    parent;
};

struct _NetsecTestClass
{
	AbsHeaderTestClass    parentclass;
};


GType 			netsec_test_get_type(void) G_GNUC_CONST;
NetsecTest*     netsec_test_new(void);
void            netsec_test(NetsecTest* self);


G_END_DECLS


#endif /* __NETSEC_TEST_H__ */
