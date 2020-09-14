/*
 *
 *@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
 *@date : 2020-09-02
 *@author : THH
 *@brief : CtImR2yClassf
 *@rely : klib.h
 *@function : 按ETK规范抄写索喜源代码
 *@version : 1.0.0 能正常上屏显示图像
 *
 */

#ifndef __CT_IM_R2Y_CLASSF_H__
#define __CT_IM_R2Y_CLASSF_H__

#include <klib.h>

#define CT_TYPE_IM_R2Y_CLASSF                  (ct_im_r2y_classf_get_type())
#define CT_IM_R2Y_CLASSF(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImR2yClassf)) 
#define CT_IS_IM_R2Y_CLASSF(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_R2Y_CLASSF)) 

typedef struct _CtImR2yClassf CtImR2yClassf;
typedef struct _CtImR2yClassfPrivate CtImR2yClassfPrivate;

struct _CtImR2yClassf
{
	KObject parent;
	ImR2yCtrl*imR2yCtrl;
	ImR2yClk*imR2yClk;
	ImR2y3 *imR2y3;
	ImR2yCtrl2*imR2yCtrl2;
};

KConstType ct_im_r2y_classf_get_type(void);
CtImR2yClassf* ct_im_r2y_classf_new(void);
CtImR2yClassf* ct_im_r2y_classf_get(void);

INT32 ct_im_r2y_classf_1_46(CtImR2yClassf *self,UCHAR pipeNo);
INT32 ct_im_r2y_classf_1_47(CtImR2yClassf *self,UCHAR pipeNo);
INT32 ct_im_r2y_classf_1_48(CtImR2yClassf *self,UCHAR pipeNo);
INT32 ct_im_r2y_classf_1_49(CtImR2yClassf *self,UCHAR pipeNo);
INT32 ct_im_r2y_classf_1_50(CtImR2yClassf *self,UCHAR pipeNo);
INT32 ct_im_r2y_classf_1_51(CtImR2yClassf *self,UCHAR pipeNo);
INT32 ct_im_r2y_classf_1_52(CtImR2yClassf *self,UCHAR pipeNo);
INT32 ct_im_r2y_classf_1_53(CtImR2yClassf *self,UCHAR pipeNo);

#endif /* __CT_IM_R2Y_CLASSF_H__ */
