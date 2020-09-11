/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :于孟孟
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年06月开始开发
*/
#ifndef __SDRAMC_TEST_H__
#define __SDRAMC_TEST_H__


#include <klib.h>


#define SDRAMC_TYPE_TEST                  (sdramc_test_get_type())
#define SDRAMC_TEST(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, SdramcTest)) 
#define SDRAMC_IS_TEST(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, SDRAMC_TYPE_TEST)) 


typedef struct _SdramcTest SdramcTest;
typedef struct _SdramcTestPrivate SdramcTestPrivate;

struct _SdramcTest 
{
	KObject parent;
};


KConstType 	sdramc_test_get_type(void);
SdramcTest* 	sdramc_test_new(void);
void 				sdramc_test(SdramcTest *self);

#endif /* __SDRAMC_TEST_H__ */
