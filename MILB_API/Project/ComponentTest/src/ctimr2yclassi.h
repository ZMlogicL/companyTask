/*
 *
 *@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
 *@date : 2020-09-02
 *@author : THH
 *@brief : CtImR2yClassi
 *@rely : klib.h
 *@function : 按ETK规范抄写索喜源代码
 *@version : 1.0.0 能正常上屏显示图像
 *
 */

#ifndef __CT_IM_R2Y_CLASSI_H__
#define __CT_IM_R2Y_CLASSI_H__

#include <klib.h>

#define CT_TYPE_IM_R2Y_CLASSI                  (ct_im_r2y_classi_get_type())
#define CT_IM_R2Y_CLASSI(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImR2yClassi)) 
#define CT_IS_IM_R2Y_CLASSI(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_R2Y_CLASSI)) 

typedef struct _CtImR2yClassi CtImR2yClassi;
typedef struct _CtImR2yClassiPrivate CtImR2yClassiPrivate;

struct _CtImR2yClassi
{
	KObject parent;
};

KConstType ct_im_r2y_classi_get_type(void);
CtImR2yClassi* ct_im_r2y_classi_new(void);
CtImR2yClassi* ct_im_r2y_classi_get(void);

INT32 ct_im_r2y_classi_1_70(UCHAR pipeNo);
INT32 ct_im_r2y_classi_1_71(UCHAR pipeNo);
INT32 ct_im_r2y_classi_1_72(UCHAR pipeNo);
INT32 ct_im_r2y_classi_1_73(UCHAR pipeNo);

#endif /* __CT_IM_R2Y_CLASSI_H__ */
