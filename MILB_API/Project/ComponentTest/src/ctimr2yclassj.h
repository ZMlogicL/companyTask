/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : THH
*@brief : CtImR2yClassj
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_R2Y_CLASSJ_H__
#define __CT_IM_R2Y_CLASSJ_H__


#include <klib.h>


#define CT_TYPE_IM_R2Y_CLASSJ                  (ct_im_r2y_classj_get_type())
#define CT_IM_R2Y_CLASSJ(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImR2yClassj)) 
#define CT_IS_IM_R2Y_CLASSJ(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_R2Y_CLASSJ)) 


typedef struct _CtImR2yClassj CtImR2yClassj;
typedef struct _CtImR2yClassjPrivate CtImR2yClassjPrivate;

struct _CtImR2yClassj 
{
	KObject parent;
};

extern TImR2yCtrlMultiAxis r2yCtrlMultiAxisTemp[];
KConstType ct_im_r2y_classj_get_type(void);
CtImR2yClassj* ct_im_r2y_classj_new(void);
CtImR2yClassj* ct_im_r2y_classj_get(void);


#endif /* __CT_IM_R2Y_CLASSJ_H__ */
