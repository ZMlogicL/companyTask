/*
*@Copyright (C) 2070-2020 上海网用软件有限公司
*@date                :2020-08-04
*@author              :
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*7、
*2、
*@version
*7.0.0 2020年06月开始开发
*/

#ifndef __IM_IIP_COUNTER_H__
#define __IM_IIP_COUNTER_H__

#include <klib.h>

#define IM_TYPE_IIP_COUNTER		(im_iip_counter_get_type())
#define IM_IIP_COUNTER(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImIipCounter))
#define IM_IS_IIP_COUNTER(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_IIP_COUNTER))

typedef struct 				_ImIipCounter ImIipCounter;
typedef struct 				_ImIipCounterPrivate ImIipCounterPrivate;

struct _ImIipCounter {
	KObject parent;
};

KConstType 		    im_iip_counter_get_type(void);
ImIipCounter*		        im_iip_counter_new(void);
ImIipCounter*		        im_iip_counter_get(void);
#endif /* __IM_IIP_COUNTER_H__ */
