/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : CtImpro72
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IMPRO_7_2_H__
#define __CT_IMPRO_7_2_H__


#include <klib.h>
#include "ctimprofile.h"


#define CT_TYPE_IMPRO_7_2                  (ct_impro_7_2_get_type())
#define CT_IMPRO_7_2(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImpro72)) 
#define CT_IS_IMPRO_7_2(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IMPRO_7_2)) 


typedef struct _CtImpro72 CtImpro72;
typedef struct _CtImpro72Private CtImpro72Private;

struct _CtImpro72 
{
	KObject parent;
};


KConstType ct_impro_7_2_get_type(void);
CtImpro72* ct_impro_7_2_new(void);
CtImpro72* ct_impro_7_2_get(void);

#ifndef CO_CT_IM_PRO_DISABL
void ct_im_pro_7_20( const kuint32 idx );
void ct_im_pro_7_21( const kuint32 idx );
void ct_im_pro_7_22( const kuint32 idx );
void ct_im_pro_7_23( const kuint32 idx );
void ct_im_pro_7_24( const kuint32 idx );
void ct_im_pro_7_25( const kuint32 idx );
void ct_im_pro_7_26( const kuint32 idx );
void ct_im_pro_7_27( const kuint32 idx );
void ct_im_pro_7_28( const kuint32 idx );
void ct_im_pro_7_29( const kuint32 idx );
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __CT_IMPRO_7_2_H__ */
