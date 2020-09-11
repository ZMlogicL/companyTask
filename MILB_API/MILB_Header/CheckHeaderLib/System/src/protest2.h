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
#ifndef __PRO_TEST2_H__
#define __PRO_TEST2_H__


#include <klib.h>
#include "internals.h"

#define PRO_TYPE_TEST2                  (pro_test2_get_type())
#define PRO_TEST2(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, ProTest2)) 
#define PRO_IS_TEST2(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, PRO_TYPE_TEST2)) 


typedef struct _ProTest2 ProTest2;
typedef struct _ProTest2Private ProTest2Private;

struct _ProTest2 
{
	KObject parent;
};


KConstType 	pro_test2_get_type(void);
ProTest2* 		pro_test2_new(void);
void 				pro_test2(ProTest1 *self, EProBlockType type, IoPro ioPro);

#endif /* __PRO_TEST2_H__ */
