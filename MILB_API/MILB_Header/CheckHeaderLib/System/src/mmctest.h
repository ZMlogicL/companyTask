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
#ifndef __MMC_TEST_H__
#define __MMC_TEST_H__


#include <stdio.h>
#include <glib-object.h>
#include "absheadertest.h"


G_BEGIN_DECLS


#define MMC_TYPE_TEST									(mmc_test_get_type())
#define MMC_TEST(obj)									(G_TYPE_CHECK_INSTANCE_CAST(obj, MMC_TYPE_TEST, MmcTest))
#define MMC_TEST_CALSS(klass)              		(G_TYPE_CHECK_CLASS_CAST((klass), MMC_TYPE_TEST, MmcTestClass))
#define MMC_IS_TEST(obj)                        		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), MMC_TYPE_TEST))
#define MMC_IS_TEST_CLASS(klass)         		(G_TYPE_CHECK_CLASS_TYPE ((klass), MMC_TYPE_TEST))
#define MMC_TEST_GET_CLASS(obj)         		(G_TYPE_INSTANCE_GET_CLASS ((obj), MMC_TYPE_TEST, MmcTestClass))


typedef struct _MmcTest                       	MmcTest;
typedef struct _MmcTestClass            		MmcTestClass;
typedef struct _MmcTestPrivate           	MmcTestPrivate;


struct _MmcTest
{
	AbsHeaderTest    parent;
};

struct _MmcTestClass
{
	AbsHeaderTestClass    parentclass;
};


GType 						mmc_test_get_type(void) G_GNUC_CONST;
MmcTest *         		mmc_test_new(void);


G_END_DECLS


#endif /* __MMC_TEST_H__ */
