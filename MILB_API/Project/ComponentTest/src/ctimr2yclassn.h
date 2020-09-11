/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : THH
*@brief : CtImR2yClassn
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_R2Y_CLASSN_H__
#define __CT_IM_R2Y_CLASSN_H__


#include <klib.h>


#define CT_TYPE_IM_R2Y_CLASSN                  (ct_im_r2y_classn_get_type())
#define CT_IM_R2Y_CLASSN(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImR2yClassn)) 
#define CT_IS_IM_R2Y_CLASSN(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_R2Y_CLASSN)) 


typedef struct _CtImR2yClassn CtImR2yClassn;
typedef struct _CtImR2yClassnPrivate CtImR2yClassnPrivate;

struct _CtImR2yClassn 
{
	KObject parent;
};


KConstType ct_im_r2y_classn_get_type(void);
CtImR2yClassn* ct_im_r2y_classn_new(void);
CtImR2yClassn* ct_im_r2y_classn_get(void);

void ct_im_r2y_classn_1_54_temp2();

#endif /* __CT_IM_R2Y_CLASSN_H__ */
