/*
*
*@Copyright (C) 2010-2020 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 杨文
*@brief : CtImIipAfn1
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_IIP_AFN1_H__
#define __CT_IM_IIP_AFN1_H__


#include <klib.h>


#define CT_TYPE_IM_IIP_AFN1                  (ct_im_iip_afn1_get_type())
#define CT_IM_IIP_AFN1(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImIipAfn1)) 
#define CT_IS_IM_IIP_AFN1(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_IIP_AFN1)) 


typedef struct _CtImIipAfn1 CtImIipAfn1;
typedef struct _CtImIipAfn1Private CtImIipAfn1Private;

struct _CtImIipAfn1 
{
	KObject parent;
};


KConstType ct_im_iip_afn1_get_type(void);
CtImIipAfn1* ct_im_iip_afn1_new(void);
CtImIipAfn1* ct_im_iip_afn1_get(void);


#endif /* __CT_IM_IIP_AFN1_H__ */
