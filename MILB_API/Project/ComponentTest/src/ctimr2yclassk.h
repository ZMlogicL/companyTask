/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : THH
*@brief : CtImR2yClassk
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_R2Y_CLASSK_H__
#define __CT_IM_R2Y_CLASSK_H__


#include <klib.h>


#define CT_TYPE_IM_R2Y_CLASSK                  (ct_im_r2y_classk_get_type())
#define CT_IM_R2Y_CLASSK(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImR2yClassk)) 
#define CT_IS_IM_R2Y_CLASSK(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_R2Y_CLASSK)) 


typedef struct _CtImR2yClassk CtImR2yClassk;
typedef struct _CtImR2yClasskPrivate CtImR2yClasskPrivate;

struct _CtImR2yClassk 
{
	KObject parent;
};

extern TImR2yCtrlMultiAxis r2yCtrlMultiAxisTemp1[1];

KConstType ct_im_r2y_classk_get_type(void);
CtImR2yClassk* ct_im_r2y_classk_new(void);
CtImR2yClassk* ct_im_r2y_classk_get(void);


#endif /* __CT_IM_R2Y_CLASSK_H__ */
