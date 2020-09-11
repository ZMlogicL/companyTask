/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : CtImpro60
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IMPRO_6_0_H__
#define __CT_IMPRO_6_0_H__


#include <klib.h>
#include "ctimprofile.h"


#define CT_TYPE_IMPRO_6_0                  (ct_impro_6_0_get_type())
#define CT_IMPRO_6_0(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImpro60)) 
#define CT_IS_IMPRO_6_0(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IMPRO_6_0)) 


typedef struct _CtImpro60 CtImpro60;
typedef struct _CtImpro60Private CtImpro60Private;

struct _CtImpro60 
{
	KObject parent;
};


KConstType ct_impro_6_0_get_type(void);
CtImpro60* ct_impro_6_0_new(void);
CtImpro60* ct_impro_6_0_get(void);

#ifndef CO_CT_IM_PRO_DISABL
void ct_im_pro_6_0_1(const kuint32 idx);
void ct_im_pro_6_0_2(const kuint32 idx);
void ct_im_pro_6_0_3(const kuint32 idx);
void ct_im_pro_6_0_4(const kuint32 idx);
void ct_im_pro_6_0_5(const kuint32 idx);
void ct_im_pro_6_0_6(const kuint32 idx);
void ct_im_pro_6_0_7(const kuint32 idx);
void ct_im_pro_6_0_8(const kuint32 idx);
void ct_im_pro_6_0_9(const kuint32 idx);
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __CT_IMPRO_6_0_H__ */
