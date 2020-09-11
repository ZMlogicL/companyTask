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
#ifndef __ITM_TEST_H__
#define __ITM_TEST_H__


#include <stdio.h>
#include <glib-object.h>
#include "absheadertest.h"


G_BEGIN_DECLS


#define ITM_TYPE_TEST									(itm_test_get_type())
#define ITM_TEST(obj)										(G_TYPE_CHECK_INSTANCE_CAST(obj, ITM_TYPE_TEST, ItmTest))
#define ITM_TEST_CALSS(klass)              			(G_TYPE_CHECK_CLASS_CAST((klass), ITM_TYPE_TEST, ItmTestClass))
#define ITM_IS_TEST(obj)                        		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), ITM_TYPE_TEST))
#define ITM_IS_TEST_CLASS(klass)         			(G_TYPE_CHECK_CLASS_TYPE ((klass), ITM_TYPE_TEST))
#define ITM_TEST_GET_CLASS(obj)         		(G_TYPE_INSTANCE_GET_CLASS ((obj), ITM_TYPE_TEST, ItmTestClass))


typedef struct _ItmTest                       		ItmTest;
typedef struct _ItmTestClass            		ItmTestClass;
typedef struct _ItmTestPrivate           		ItmTestPrivate;


struct _ItmTest
{
	AbsHeaderTest    parent;
};

struct _ItmTestClass
{
	AbsHeaderTestClass    parentclass;
};


GType 						itm_test_get_type(void) G_GNUC_CONST;
ItmTest *         		itm_test_new(void);


G_END_DECLS


#endif /* __ITM_TEST_H__ */
