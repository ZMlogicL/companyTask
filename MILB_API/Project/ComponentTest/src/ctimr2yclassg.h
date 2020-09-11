/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : THH
*@brief : CtImR2yClassg
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_R2Y_CLASSG_H__
#define __CT_IM_R2Y_CLASSG_H__


#include <klib.h>


#define CT_TYPE_IM_R2Y_CLASSG                  (ct_im_r2y_classg_get_type())
#define CT_IM_R2Y_CLASSG(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImR2yClassg)) 
#define CT_IS_IM_R2Y_CLASSG(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_R2Y_CLASSG)) 


typedef struct _CtImR2yClassg CtImR2yClassg;
typedef struct _CtImR2yClassgPrivate CtImR2yClassgPrivate;

struct _CtImR2yClassg 
{
	KObject parent;
};


KConstType ct_im_r2y_classg_get_type(void);
CtImR2yClassg* ct_im_r2y_classg_new(void);
CtImR2yClassg* ct_im_r2y_classg_get(void);

INT32 ct_im_r2y_classg_1_54( UCHAR pipeNo );


#endif /* __CT_IM_R2Y_CLASSG_H__ */
