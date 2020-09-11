/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-03
*@author              :申雨
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年09月开始开发
*/


#ifndef __PRO_TEST5_H__
#define __PRO_TEST5_H__


#include <klib.h>
#include "internals.h"


#define PRO_TYPE_TEST5		(pro_test5_get_type())
#define PRO_TEST5(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, ProTest5))
#define PRO_IS_TEST5(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, PRO_TYPE_TEST5))


typedef struct 				_ProTest5 ProTest5;
typedef struct 				_ProTest5Private ProTest5Private;

struct _ProTest5 {
	KObject parent;
};


KConstType 		    pro_test5_get_type(void);
ProTest5*		        pro_test5_new(void);
void 						pro_test5(ProTest5 *self, EProBlockType type, IoPro ioPro);


#endif /* __PRO_TEST5_H__ */
