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
#ifndef __SCU_TEST_H__
#define __SCU_TEST_H__


#include <klib.h>


#define SCU_TYPE_TEST                  (scu_test_get_type())
#define SCU_TEST(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, ScuTest)) 
#define SCU_IS_TEST(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, SCU_TYPE_TEST)) 


typedef struct _ScuTest ScuTest;
typedef struct _ScuTestPrivate ScuTestPrivate;

struct _ScuTest 
{
	KObject parent;
};


KConstType 	scu_test_get_type(void);
ScuTest* 			scu_test_new(void);
void 				scu_test(ScuTest *self);

#endif /* __SCU_TEST_H__ */
