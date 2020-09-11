/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : CtImpro64
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IMPRO_6_4_H__
#define __CT_IMPRO_6_4_H__


#include <klib.h>
#include "ctimprofile.h"


#define CT_TYPE_IMPRO_6_4                  (ct_impro_6_4_get_type())
#define CT_IMPRO_6_4(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImpro64)) 
#define CT_IS_IMPRO_6_4(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IMPRO_6_4)) 


typedef struct _CtImpro64 CtImpro64;
typedef struct _CtImpro64Private CtImpro64Private;

struct _CtImpro64 
{
	KObject parent;
};


KConstType ct_impro_6_4_get_type(void);
CtImpro64* ct_impro_6_4_new(void);
CtImpro64* ct_impro_6_4_get(void);

#ifndef CO_CT_IM_PRO_DISABL
void ct_im_pro_6_0_40(const kuint32 idx);
void ct_im_pro_6_0_41(const kuint32 idx);
void ct_im_pro_6_0_42(const kuint32 idx);
void ct_im_pro_6_0_43(const kuint32 idx);
void ct_im_pro_6_0_44(const kuint32 idx);
void ct_im_pro_6_0_45(const kuint32 idx);
void ct_im_pro_6_0_46(const kuint32 idx);
void ct_im_pro_6_0_47(const kuint32 idx);
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __CT_IMPRO_6_4_H__ */
