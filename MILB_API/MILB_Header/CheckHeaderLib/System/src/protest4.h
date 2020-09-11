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
#ifndef __PRO_TEST4_H__
#define __PRO_TEST4_H__


#include <klib.h>
#include "internals.h"


#define PRO_TYPE_TEST4                  (pro_test4_get_type())
#define PRO_TEST4(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, ProTest4)) 
#define PRO_IS_TEST4(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, PRO_TYPE_TEST4)) 


typedef struct _ProTest4 ProTest4;
typedef struct _ProTest4Private ProTest4Private;

struct _ProTest4 
{
	KObject parent;
};


KConstType 	pro_test4_get_type(void);
ProTest4* 		pro_test4_new(void);
void 				pro_test4(ProTest4 *self, EProBlockType type, IoPro ioPro);

#endif /* __PRO_TEST4_H__ */
