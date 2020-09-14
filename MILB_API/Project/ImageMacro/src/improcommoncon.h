/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-08-04
*@author              :刘应春
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

#ifndef __IM_PRO_COMMON_CON_H__
#define __IM_PRO_COMMON_CON_H__

#include <klib.h>

#define IM_TYPE_PRO_COMMON_CON		(im_pro_common_con_get_type())
#define IM_PRO_COMMON_CON(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImProCommonCon))
#define IM_IS_PRO_COMMON_CON(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_PRO_COMMON_CON))

typedef struct 				_ImProCommonCon ImProCommonCon;
typedef struct 				_ImProCommonConPrivate ImProCommonConPrivate;

struct _ImProCommonCon {
	KObject parent;
};

KConstType 		    im_pro_common_con_get_type(void);
ImProCommonCon*		        im_pro_common_con_new(void);

#endif /* __IM_PRO_COMMON_CON_H__ */
