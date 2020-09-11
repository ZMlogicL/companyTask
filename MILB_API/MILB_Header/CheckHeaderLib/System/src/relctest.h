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
#ifndef __RELC_TEST_H__
#define __RELC_TEST_H__


#include <klib.h>


#define RELC_TYPE_TEST                  (relc_test_get_type())
#define RELC_TEST(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, RelcTest)) 
#define RELC_IS_TEST(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, RELC_TYPE_TEST)) 


typedef struct _RelcTest RelcTest;
typedef struct _RelcTestPrivate RelcTestPrivate;

struct _RelcTest 
{
	KObject parent;
};


KConstType 	relc_test_get_type(void);
RelcTest* 		relc_test_new(void);
void 				relc_test(RelcTest *self);


#endif /* __RELC_TEST_H__ */
