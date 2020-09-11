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


#ifndef __PRO_TEST6_H__
#define __PRO_TEST6_H__


#include <klib.h>
#include "internals.h"


#define PRO_TYPE_TEST6		(pro_test6_get_type())
#define PRO_TEST6(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, ProTest6))
#define PRO_IS_TEST6(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, PRO_TYPE_TEST6))


typedef struct 				_ProTest6 ProTest6;
typedef struct 				_ProTest6Private ProTest6Private;

struct _ProTest6 {
	KObject parent;
};


KConstType 		    pro_test6_get_type(void);
ProTest6*		        pro_test6_new(void);
void 						pro_test6(ProTest6 *self, EProBlockType type, IoPro ioPro);


#endif /* __PRO_TEST6_H__ */
