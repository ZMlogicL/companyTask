/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
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


#ifndef __NIC_TEST_H__
#define __NIC_TEST_H__


#include <klib.h>


#define NIC_TYPE_TEST                  (nic_test_get_type())
#define NIC_TEST(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, NicTest)) 
#define NIC_IS_TEST(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, NIC_TYPE_TEST)) 


typedef struct _NicTest NicTest;
typedef struct _NicTestPrivate NicTestPrivate;

struct _NicTest 
{
	KObject parent;
};


KConstType 	nic_test_get_type(void);
NicTest* 			nic_test_new(void);
void 				nic_test(NicTest *self);


#endif /* __NIC_TEST_H__ */
