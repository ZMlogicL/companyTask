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
#ifndef __PRO_TEST3_H__
#define __PRO_TEST3_H__


#include <klib.h>
#include "internals.h"


#define PRO_TYPE_TEST3                  (pro_test3_get_type())
#define PRO_TEST3(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, ProTest3)) 
#define PRO_IS_TEST3(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, PRO_TYPE_TEST3)) 


typedef struct _ProTest3 ProTest3;
typedef struct _ProTest3Private ProTest3Private;

struct _ProTest3 
{
	KObject parent;
};


KConstType 	pro_test3_get_type(void);
ProTest3* 		pro_test3_new(void);
void 				pro_test3(ProTest3 *self, EProBlockType type, IoPro ioPro);

#endif /* __PRO_TEST3_H__ */
