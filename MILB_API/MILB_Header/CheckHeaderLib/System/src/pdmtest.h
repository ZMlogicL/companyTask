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


#ifndef __PDM_TEST_H__
#define __PDM_TEST_H__


#include <klib.h>


#define PDM_TYPE_TEST                  (pdm_test_get_type())
#define PDM_TEST(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, PdmTest)) 
#define PDM_IS_TEST(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, PDM_TYPE_TEST)) 


typedef struct _PdmTest PdmTest;
typedef struct _PdmTestPrivate PdmTestPrivate;

struct _PdmTest 
{
	KObject parent;
};


KConstType 	pdm_test_get_type(void);
PdmTest* 		pdm_test_new(void);
void 				pdm_test(PdmTest *self);

#endif /* __PDM_TEST_H__ */
