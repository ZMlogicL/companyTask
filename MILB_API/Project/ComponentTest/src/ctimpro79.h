/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : CtImpro79
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IMPRO_7_9_H__
#define __CT_IMPRO_7_9_H__


#include <klib.h>
#include "ctimprofile.h"


#define CT_TYPE_IMPRO_7_9                  (ct_impro_7_9_get_type())
#define CT_IMPRO_7_9(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImpro79)) 
#define CT_IS_IMPRO_7_9(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IMPRO_7_9)) 


typedef struct _CtImpro79 CtImpro79;
typedef struct _CtImpro79Private CtImpro79Private;

struct _CtImpro79 
{
	KObject parent;
};


KConstType ct_impro_7_9_get_type(void);
CtImpro79* ct_impro_7_9_new(void);
CtImpro79* ct_impro_7_9_get(void);

#ifndef CO_CT_IM_PRO_DISABL
void ct_im_pro_7_90( const kuint32 idx );
void ct_im_pro_7_91( const kuint32 idx );
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __CT_IMPRO_7_9_H__ */
