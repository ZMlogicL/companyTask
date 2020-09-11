/*
*@Copyright (C) 2050-2020 上海网用软件有限公司
*@date                :2020-08-04
*@author              :
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*5、
*2、
*@version
*5.0.0 2020年06月开始开发
*/

#ifndef __IM_IIP_VOID_H__
#define __IM_IIP_VOID_H__

#include <klib.h>

#define IM_TYPE_IIP_VOID		(im_iip_void_get_type())
#define IM_IIP_VOID(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImIipVoid))
#define IM_IS_IIP_VOID(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_IIP_VOID))

typedef struct 				_ImIipVoid ImIipVoid;
typedef struct 				_ImIipVoidPrivate ImIipVoidPrivate;

struct _ImIipVoid {
	KObject parent;
};

KConstType 		    im_iip_void_get_type(void);
ImIipVoid*		        im_iip_void_new(void);
ImIipVoid*		        im_iip_void_get(void);
#endif /* __IM_IIP_VOID_H__ */
