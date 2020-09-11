/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : CtImpro70
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IMPRO_7_0_H__
#define __CT_IMPRO_7_0_H__


#include <klib.h>
#include "ctimprofile.h"


#define CT_TYPE_IMPRO_7_0                  (ct_impro_7_0_get_type())
#define CT_IMPRO_7_0(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImpro70)) 
#define CT_IS_IMPRO_7_0(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IMPRO_7_0)) 


typedef struct _CtImpro70 CtImpro70;
typedef struct _CtImpro70Private CtImpro70Private;


struct _CtImpro70 
{
	KObject parent;
};


KConstType ct_impro_7_0_get_type(void);
CtImpro70* ct_impro_7_0_new(void);
CtImpro70* ct_impro_7_0_get(void);

#ifndef CO_CT_IM_PRO_DISABL
void ct_im_pro_7_1( const kuint32 idx );
void ct_im_pro_7_2( const kuint32 idx );
void ct_im_pro_7_3( const kuint32 idx );
void ct_im_pro_7_4( const kuint32 idx );
void ct_im_pro_7_5( const kuint32 idx );
void ct_im_pro_7_6( const kuint32 idx );
void ct_im_pro_7_7( const kuint32 idx );
void ct_im_pro_7_8( const kuint32 idx );
void ct_im_pro_7_9( const kuint32 idx );
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __CT_IMPRO_7_0_H__ */
