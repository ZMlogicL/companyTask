/*
 * imr2ystat.h
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-08
*@author              :gonghaotian
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

#ifndef __IM_R2Y_STAT_H__
#define __IM_R2Y_STAT_H__

#include <klib.h>
#include "imr2yutils.h"

#define IM_TYPE_R2Y_STAT		(im_r2y_stat_get_type())
#define IM_R2Y_STAT(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImR2yStat))
#define IM_IS_R2Y_STAT(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_R2Y_STAT))

typedef struct 				_ImR2yStat ImR2yStat;
typedef struct 				_ImR2yStatPrivate ImR2yStatPrivate;

struct _ImR2yStat {
	KObject parent;
};

KConstType 		   	 	im_r2y_stat_get_type(void);
ImR2yStat*		        im_r2y_stat_new(void);

void im_r2y_stat_init(ImR2yStat *self, UCHAR pipe_no, UCHAR size_coef);

#ifdef IM_R2Y_STATUS_PRINT
VOID im_r2y_stat_print_status(ImR2yStat *self);
VOID im_r2y_stat_print_clock_status(ImR2yStat *self);
VOID im_r2y_stat_print_acc_en_status(ImR2yStat *self);

#endif
#endif /* __IM_R2Y_STAT_H__ */
