/*
*@Copyright (C) 2040-2020 上海网用软件有限公司
*@date                :2020-08-04
*@author              :
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

#ifndef __IM_IIP_MAIN_H__
#define __IM_IIP_MAIN_H__

#include <klib.h>

#define IM_TYPE_IIP_MAIN		(im_iip_main_get_type())
#define IM_IIP_MAIN(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImIipMain))
#define IM_IS_IIP_MAIN(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_IIP_MAIN))

typedef struct 				_ImIipMain ImIipMain;
typedef struct 				_ImIipMainPrivate ImIipMainPrivate;

struct _ImIipMain {
	KObject parent;
};

KConstType 		    im_iip_main_get_type(void);
ImIipMain*		        		im_iip_main_new(void);

#endif /* __IM_IIP_MAIN_H__ */
