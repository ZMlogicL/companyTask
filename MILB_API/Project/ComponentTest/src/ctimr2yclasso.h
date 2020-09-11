/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : THH
*@brief : CtImR2yClasso
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_R2Y_CLASSO_H__
#define __CT_IM_R2Y_CLASSO_H__


#include <klib.h>


#define CT_TYPE_IM_R2Y_CLASSO                  (ct_im_r2y_classo_get_type())
#define CT_IM_R2Y_CLASSO(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImR2yClasso)) 
#define CT_IS_IM_R2Y_CLASSO(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_R2Y_CLASSO)) 


typedef struct _CtImR2yClasso CtImR2yClasso;
typedef struct _CtImR2yClassoPrivate CtImR2yClassoPrivate;

struct _CtImR2yClasso 
{
	KObject parent;
};


KConstType ct_im_r2y_classo_get_type(void);
CtImR2yClasso* ct_im_r2y_classo_new(void);
CtImR2yClasso* ct_im_r2y_classo_get(void);

void ct_im_r2y_classo_1_54_temp3();

#endif /* __CT_IM_R2Y_CLASSO_H__ */
