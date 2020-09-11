/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : THH
*@brief : CtImR2yClassl
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_R2Y_CLASSL_H__
#define __CT_IM_R2Y_CLASSL_H__


#include <klib.h>


#define CT_TYPE_IM_R2Y_CLASSL                  (ct_im_r2y_classl_get_type())
#define CT_IM_R2Y_CLASSL(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImR2yClassl)) 
#define CT_IS_IM_R2Y_CLASSL(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_R2Y_CLASSL)) 


typedef struct _CtImR2yClassl CtImR2yClassl;
typedef struct _CtImR2yClasslPrivate CtImR2yClasslPrivate;

struct _CtImR2yClassl 
{
	KObject parent;
};

extern TImR2yCtrlMultiAxis r2yCtrlMultiAxisTemp2[1];
KConstType ct_im_r2y_classl_get_type(void);
CtImR2yClassl* ct_im_r2y_classl_new(void);
CtImR2yClassl* ct_im_r2y_classl_get(void);


#endif /* __CT_IM_R2Y_CLASSL_H__ */
