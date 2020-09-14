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

#ifndef __IM_PRO_COMMON_FIG_H__
#define __IM_PRO_COMMON_FIG_H__

#include <klib.h>

#define IM_TYPE_PRO_COMMON_FIG		(im_pro_common_fig_get_type())
#define IM_PRO_COMMON_FIG(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImProCommonFig))
#define IM_IS_PRO_COMMON_FIG(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_PRO_COMMON_FIG))

typedef struct 				_ImProCommonFig ImProCommonFig;
typedef struct 				_ImProCommonFigPrivate ImProCommonFigPrivate;

struct _ImProCommonFig {
	KObject parent;
};

KConstType 		    im_pro_common_fig_get_type(void);
ImProCommonFig*		        im_pro_common_fig_new(void);

#endif /* __IM_PRO_COMMON_FIG_H__ */
