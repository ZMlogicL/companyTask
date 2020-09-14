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
#ifndef __PRO_TEST1_H__
#define __PRO_TEST1_H__

#include <klib.h>
#include "checkheadermaindefs.h"

#define PRO_TYPE_TEST1                  (pro_test1_get_type())
#define PRO_TEST1(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, ProTest1)) 
#define PRO_IS_TEST1(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, PRO_TYPE_TEST1)) 


typedef struct _ProTest1 ProTest1;
typedef struct _ProTest1Private ProTest1Private;

struct _ProTest1
{
	KObject parent;
};


KConstType 	pro_test1_get_type(void);
ProTest1* 		pro_test1_new(void);
void 				pro_test1(ProTest1 *self, EProBlockType type, IoPro ioPro);

#endif /* __PRO_TEST1_H__ */
