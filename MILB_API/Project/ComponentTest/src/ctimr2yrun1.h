/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 梁正明
*@brief : CtImR2yRun1
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_R2Y_RUN1_H__
#define __CT_IM_R2Y_RUN1_H__


#include <klib.h>


#define CT_TYPE_IM_R2Y_RUN1                  (ct_im_r2y_run1_get_type())
#define CT_IM_R2Y_RUN1(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImR2yRun1)) 
#define CT_IS_IM_R2Y_RUN1(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_R2Y_RUN1)) 


typedef struct _CtImR2yRun1 CtImR2yRun1;
typedef struct _CtImR2yRun1Private CtImR2yRun1Private;

struct _CtImR2yRun1 
{
	KObject parent;
};


KConstType 			ct_im_r2y_run1_get_type(void);
CtImR2yRun1			*ct_im_r2y_run1_new(void);

kint32 						ct_im_r2y_run_1(CtImR2yRun1 *self, kuchar pipeNo, const kuint32 ctNo3rd);


#endif /* __CT_IM_R2Y_RUN1_H__ */
