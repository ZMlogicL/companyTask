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
	ImR2yCtrl2*imR2yCtrl2;
	ImR2yClk*imR2yClk;
	ImR2yCtrl*imR2yCtrl;
	ImR2yStat*imR2yStat;
	ImR2yEdge*imR2yEdge;
};

KConstType ct_im_r2y_classh_get_type(void);
CtImR2yClassh* ct_im_r2y_classh_new(void);
CtImR2yClassh* ct_im_r2y_classh_get(void);

INT32 ct_im_r2y_classh_1_55(CtImR2yClassh *self,UCHAR pipeNo);
INT32 ct_im_r2y_classh_1_56(CtImR2yClassh *self,UCHAR pipeNo);
INT32 ct_im_r2y_classh_1_57(CtImR2yClassh *self,UCHAR pipeNo);
INT32 ct_im_r2y_classh_1_58(CtImR2yClassh *self,UCHAR pipeNo);
INT32 ct_im_r2y_classh_1_59(CtImR2yClassh *self,UCHAR pipeNo);
INT32 ct_im_r2y_classh_1_60(CtImR2yClassh *self,UCHAR pipeNo);
INT32 ct_im_r2y_classh_1_61(CtImR2yClassh *self,UCHAR pipeNo);
INT32 ct_im_r2y_classh_1_62(CtImR2yClassh *self,UCHAR pipeNo);
INT32 ct_im_r2y_classh_1_63(CtImR2yClassh *self,UCHAR pipeNo);
INT32 ct_im_r2y_classh_1_64(CtImR2yClassh *self,UCHAR pipeNo);
INT32 ct_im_r2y_classh_1_65(CtImR2yClassh *self,UCHAR pipeNo);
INT32 ct_im_r2y_classh_1_66(CtImR2yClassh *self,UCHAR pipeNo);
INT32 ct_im_r2y_classh_1_67(CtImR2yClassh *self,UCHAR pipeNo);
INT32 ct_im_r2y_classh_1_68(CtImR2yClassh *self,UCHAR pipeNo);
INT32 ct_im_r2y_classh_1_69(CtImR2yClassh *self,UCHAR pipeNo);

#endif /* __CT_IM_R2Y_CLASSH_H__ */
