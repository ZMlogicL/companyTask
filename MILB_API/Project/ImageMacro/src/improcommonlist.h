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

#ifndef __IM_PRO_COMMON_LIST_H__
#define __IM_PRO_COMMON_LIST_H__

#include <klib.h>
#include "dd_top.h"
#define IM_TYPE_PRO_COMMON_LIST		(im_pro_pommon_list_get_type())
#define IM_PRO_COMMON_LIST(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImProCommonList))
#define IM_IS_PRO_COMMON_LIST(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_PRO_COMMON_LIST))

#define IM_PRO_COMMON_LIST_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImProCommonListPrivate, IM_TYPE_PRO_COMMON_LIST))
#define im_pro_common_set_start_status(st, ch) 		(imProCommonList->gIM_PRO_COMMON_START_Status[((st) >> 28) & 0xf] |=  (((st) & 0x0fffffff) << (ch)))							/* Macro start status ON	*/
#define im_pro_common_set_stop_status(st, ch)		(imProCommonList->gIM_PRO_COMMON_START_Status[((st) >> 28) & 0xf] &= ~(((st) & 0x0fffffff) << (ch)))							/* Macro start status OFF	*/
#define im_pro_common_get_start_status(st, ch)		(((imProCommonList->gIM_PRO_COMMON_START_Status[((st) >> 28) & 0xf] & (((st) & 0x0fffffff) << (ch))) != 0) ? TRUE : FALSE)	/* started check	*/
#define im_pro_common_get_stop_all()				(((gIM_PRO_COMMON_START_Status[0] | gIM_PRO_COMMON_START_Status[1] | gIM_PRO_COMMON_START_Status[2] | gIM_PRO_COMMON_START_Status[3] | gIM_PRO_COMMON_START_Status[4] | gIM_PRO_COMMON_START_Status[5]) != 0) ? FALSE : TRUE)		/* started check	*/

typedef struct 				_ImProCommonList ImProCommonList;
typedef struct 				_ImProCommonListPrivate ImProCommonListPrivate;

//extern volatile	ULONG	gIM_PRO_COMMON_START_Status[6];

struct _ImProCommonList {
	KObject parent;
	 volatile	ULONG	gIM_PRO_COMMON_START_Status[6];
};
#define im_pro_common_list_get_gIM_PRO_COMMON_START_Status(self,i)           (self->gIM_PRO_COMMON_START_Status[i])

KConstType 		    im_pro_common_list_get_type(void);
ImProCommonList* im_pro_common_list_get(void);
ImProCommonList*		        im_pro_common_list_new(void);

#endif /* __IM_PRO_COMMON_LIST_H__ */
