/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : THH
*@brief : CtImR2yClassm
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_R2Y_CLASSM_H__
#define __CT_IM_R2Y_CLASSM_H__


#include <klib.h>


#define CT_TYPE_IM_R2Y_CLASSM                  (ct_im_r2y_classm_get_type())
#define CT_IM_R2Y_CLASSM(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImR2yClassm)) 
#define CT_IS_IM_R2Y_CLASSM(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_R2Y_CLASSM)) 


typedef struct _CtImR2yClassm CtImR2yClassm;
typedef struct _CtImR2yClassmPrivate CtImR2yClassmPrivate;

struct _CtImR2yClassm 
{
	KObject parent;
};


KConstType ct_im_r2y_classm_get_type(void);
CtImR2yClassm* ct_im_r2y_classm_new(void);
CtImR2yClassm* ct_im_r2y_classm_get(void);

void ct_im_r2y_classm_1_54_temp1(CtImR2yClassm *self);

#endif /* __CT_IM_R2Y_CLASSM_H__ */
