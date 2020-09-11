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
#ifndef __PTIMER_TEST_H__
#define __PTIMER_TEST_H__


#include <klib.h>


#define PTIMER_TYPE_TEST                  (ptimer_test_get_type())
#define PTIMER_TEST(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, PtimerTest)) 
#define PTIMER_IS_TEST(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, PTIMER_TYPE_TEST)) 


typedef struct _PtimerTest PtimerTest;
typedef struct _PtimerTestPrivate PtimerTestPrivate;

struct _PtimerTest 
{
	KObject parent;
};


KConstType 	ptimer_test_get_type(void);
PtimerTest* 	ptimer_test_new(void);
void 				ptimer_test(PtimerTest *self);

#endif /* __PTIMER_TEST_H__ */
