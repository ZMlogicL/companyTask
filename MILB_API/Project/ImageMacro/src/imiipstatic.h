/*
*@Copyright (C) 2030-2020 上海网用软件有限公司
*@date                :2020-08-04
*@author              :
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*3、
*2、
*@version
*3.0.0 2020年06月开始开发
*/

#ifndef __IM_IIP_STATIC_H__
#define __IM_IIP_STATIC_H__

#include <klib.h>

#define IM_TYPE_IIP_STATIC		(im_iip_static_get_type())
#define IM_IIP_STATIC(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImIipStatic))
#define IM_IS_IIP_STATIC(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_IIP_STATIC))

typedef struct 				_ImIipStatic ImIipStatic;
typedef struct 				_ImIipStaticPrivate ImIipStaticPrivate;

struct _ImIipStatic {
	KObject parent;
};

KConstType 		    im_iip_static_get_type(void);
ImIipStatic*		        		im_iip_static_get(void);


#endif /* __IM_IIP_STATIC_H__ */
