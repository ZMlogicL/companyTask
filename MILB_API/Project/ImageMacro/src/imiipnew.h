/*
*@Copyright (C) 2040-2020 上海网用软件有限公司
*@date                :2020-08-04
*@author              :刘应春
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*4、
*2、
*@version
*4.0.0 2020年06月开始开发
*/

#ifndef __IM_IIP_NEW_H__
#define __IM_IIP_NEW_H__

#include <klib.h>

#define IM_TYPE_IIP_NEW		(im_iip_new_get_type())
#define IM_IIP_NEW(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImIipNew))
#define IM_IS_IIP_NEW(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_IIP_NEW))

typedef struct 				_ImIipNew ImIipNew;
typedef struct 				_ImIipNewPrivate ImIipNewPrivate;

struct _ImIipNew {
	KObject parent;
};

KConstType 		    im_iip_new_get_type(void);
ImIipNew*		        		im_iip_new_new(void);

#endif /* __IM_IIP_NEW_H__ */
