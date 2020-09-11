/*
 *
 *@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
 *@date : 2020-09-02
 *@author : THH
 *@brief : CtImR2yClassh
 *@rely : klib.h
 *@function : 按ETK规范抄写索喜源代码
 *@version : 1.0.0 能正常上屏显示图像
 *
 */

#ifndef __CT_IM_R2Y_CLASSH_H__
#define __CT_IM_R2Y_CLASSH_H__

#include <klib.h>

#define CT_TYPE_IM_R2Y_CLASSH                  (ct_im_r2y_classh_get_type())
#define CT_IM_R2Y_CLASSH(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImR2yClassh)) 
#define CT_IS_IM_R2Y_CLASSH(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_R2Y_CLASSH)) 

typedef struct _CtImR2yClassh CtImR2yClassh;
typedef struct _CtImR2yClasshPrivate CtImR2yClasshPrivate;

struct _CtImR2yClassh
{
	KObject parent;
};

KConstType ct_im_r2y_classh_get_type(void);
CtImR2yClassh* ct_im_r2y_classh_new(void);
CtImR2yClassh* ct_im_r2y_classh_get(void);

INT32 ct_im_r2y_classh_1_55(UCHAR pipeNo);
INT32 ct_im_r2y_classh_1_56(UCHAR pipeNo);
INT32 ct_im_r2y_classh_1_57(UCHAR pipeNo);
INT32 ct_im_r2y_classh_1_58(UCHAR pipeNo);
INT32 ct_im_r2y_classh_1_59(UCHAR pipeNo);
INT32 ct_im_r2y_classh_1_60(UCHAR pipeNo);
INT32 ct_im_r2y_classh_1_61(UCHAR pipeNo);
INT32 ct_im_r2y_classh_1_62(UCHAR pipeNo);
INT32 ct_im_r2y_classh_1_63(UCHAR pipeNo);
INT32 ct_im_r2y_classh_1_64(UCHAR pipeNo);
INT32 ct_im_r2y_classh_1_65(UCHAR pipeNo);
INT32 ct_im_r2y_classh_1_66(UCHAR pipeNo);
INT32 ct_im_r2y_classh_1_67(UCHAR pipeNo);
INT32 ct_im_r2y_classh_1_68(UCHAR pipeNo);
INT32 ct_im_r2y_classh_1_69(UCHAR pipeNo);

#endif /* __CT_IM_R2Y_CLASSH_H__ */
