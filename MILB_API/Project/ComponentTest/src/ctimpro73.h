/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : CtImpro73
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IMPRO_7_3_H__
#define __CT_IMPRO_7_3_H__


#include <klib.h>
#include "ctimprofile.h"


#define CT_TYPE_IMPRO_7_3                  (ct_impro_7_3_get_type())
#define CT_IMPRO_7_3(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImpro73)) 
#define CT_IS_IMPRO_7_3(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IMPRO_7_3)) 


typedef struct _CtImpro73 CtImpro73;
typedef struct _CtImpro73Private CtImpro73Private;

struct _CtImpro73 
{
	KObject parent;
};


KConstType ct_impro_7_3_get_type(void);
CtImpro73* ct_impro_7_3_new(void);
CtImpro73* ct_impro_7_3_get(void);

#ifndef CO_CT_IM_PRO_DISABL
void ct_im_pro_7_30( const kuint32 idx );
void ct_im_pro_7_31( const kuint32 idx );
void ct_im_pro_7_32( const kuint32 idx );
void ct_im_pro_7_33( const kuint32 idx );
void ct_im_pro_7_34( const kuint32 idx );
void ct_im_pro_7_35( const kuint32 idx );
void ct_im_pro_7_36( const kuint32 idx );
void ct_im_pro_7_37( const kuint32 idx );
void ct_im_pro_7_38( const kuint32 idx );
void ct_im_pro_7_39( const kuint32 idx );
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __CT_IMPRO_7_3_H__ */
