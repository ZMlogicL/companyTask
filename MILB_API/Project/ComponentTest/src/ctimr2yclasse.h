/*
 *
 *@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
 *@date : 2020-09-02
 *@author : THH
 *@brief : CtImR2yClasse
 *@rely : klib.h
 *@function : 按ETK规范抄写索喜源代码
 *@version : 1.0.0 能正常上屏显示图像
 *
 */

#ifndef __CT_IM_R2Y_CLASSE_H__
#define __CT_IM_R2Y_CLASSE_H__

#include <klib.h>

#define CT_TYPE_IM_R2Y_CLASSE                  (ct_im_r2y_classe_get_type())
#define CT_IM_R2Y_CLASSE(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImR2yClasse)) 
#define CT_IS_IM_R2Y_CLASSE(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_R2Y_CLASSE)) 

typedef struct _CtImR2yClasse CtImR2yClasse;
typedef struct _CtImR2yClassePrivate CtImR2yClassePrivate;

struct _CtImR2yClasse
{
	KObject parent;
	ImR2y3 *imR2y3;
	ImR2yClk*imR2yClk;
	ImR2yProc*imR2yProc;
};

KConstType ct_im_r2y_classe_get_type(void);
CtImR2yClasse* ct_im_r2y_classe_new(void);
CtImR2yClasse* ct_im_r2y_classe_get(void);

INT32 ct_im_r2y_classe_1_37(CtImR2yClasse *self,UCHAR pipeNo);
INT32 ct_im_r2y_classe_1_38(CtImR2yClasse *self,UCHAR pipeNo);
INT32 ct_im_r2y_classe_1_39(CtImR2yClasse *self,UCHAR pipeNo);
INT32 ct_im_r2y_classe_1_40(CtImR2yClasse *self,UCHAR pipeNo);
INT32 ct_im_r2y_classe_1_41(CtImR2yClasse *self,UCHAR pipeNo);
INT32 ct_im_r2y_classe_1_42(CtImR2yClasse *self,UCHAR pipeNo);
INT32 ct_im_r2y_classe_1_43(CtImR2yClasse *self,UCHAR pipeNo);
INT32 ct_im_r2y_classe_1_44(CtImR2yClasse *self,UCHAR pipeNo);
INT32 ct_im_r2y_classe_1_45(CtImR2yClasse *self,UCHAR pipeNo);

#endif /* __CT_IM_R2Y_CLASSE_H__ */
