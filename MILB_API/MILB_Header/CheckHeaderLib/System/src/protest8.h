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


#ifndef __PRO_TEST8_H__
#define __PRO_TEST8_H__


#include <klib.h>
#include "internals.h"


#define PRO_TYPE_TEST8		(pro_test8_get_type())
#define PRO_TEST8(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, ProTest8))
#define PRO_IS_TEST8(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, PRO_TYPE_TEST8))


typedef struct 				_ProTest8 ProTest8;
typedef struct 				_ProTest8Private ProTest8Private;

struct _ProTest8 {
	KObject parent;
};


KConstType 		    pro_test8_get_type(void);
ProTest8*		        pro_test8_new(void);
void 						pro_test8(ProTest8 *self, EProBlockType type, IoPro ioPro);


#endif /* __PRO_TEST8_H__ */
