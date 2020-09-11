/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : CtImpro74
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IMPRO_7_4_H__
#define __CT_IMPRO_7_4_H__


#include <klib.h>
#include "ctimprofile.h"


#define CT_TYPE_IMPRO_7_4                  (ct_impro_7_4_get_type())
#define CT_IMPRO_7_4(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImpro74)) 
#define CT_IS_IMPRO_7_4(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IMPRO_7_4)) 


typedef struct _CtImpro74 CtImpro74;
typedef struct _CtImpro74Private CtImpro74Private;

struct _CtImpro74 
{
	KObject parent;
};


KConstType ct_impro_7_4_get_type(void);
CtImpro74* ct_impro_7_4_new(void);
CtImpro74* ct_impro_7_4_get(void);

#ifndef CO_CT_IM_PRO_DISABL

void ct_im_pro_7_40( const kuint32 idx );
void ct_im_pro_7_41( const kuint32 idx );
void ct_im_pro_7_42( const kuint32 idx );
void ct_im_pro_7_43( const kuint32 idx );
void ct_im_pro_7_44( const kuint32 idx );
void ct_im_pro_7_45( const kuint32 idx );
void ct_im_pro_7_46( const kuint32 idx );
void ct_im_pro_7_47( const kuint32 idx );
void ct_im_pro_7_48( const kuint32 idx );
void ct_im_pro_7_49( const kuint32 idx );
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __CT_IMPRO_7_4_H__ */
