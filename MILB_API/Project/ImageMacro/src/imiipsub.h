/*
*@Copyright (C) 2060-2020 上海网用软件有限公司
*@date                :2020-08-04
*@author              :
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*6、
*2、
*@version
*6.0.0 2020年06月开始开发
*/

#ifndef __IM_IIP_SUB_H__
#define __IM_IIP_SUB_H__

#include <klib.h>

#define IM_TYPE_IIP_SUB		(im_iip_sub_get_type())
#define IM_IIP_SUB(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImIipSub))
#define IM_IS_IIP_SUB(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_IIP_SUB))

typedef struct 				_ImIipSub ImIipSub;
typedef struct 				_ImIipSubPrivate ImIipSubPrivate;

struct _ImIipSub {
	KObject parent;
};

KConstType 		    im_iip_sub_get_type(void);
ImIipSub*		        im_iip_sub_new(void);


#endif /* __IM_IIP_SUB_H__ */
