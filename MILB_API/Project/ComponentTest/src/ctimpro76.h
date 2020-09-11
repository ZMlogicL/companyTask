/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : CtImpro76
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IMPRO_7_6_H__
#define __CT_IMPRO_7_6_H__


#include <klib.h>
#include "ctimprofile.h"


#define CT_TYPE_IMPRO_7_6                  (ct_impro_7_6_get_type())
#define CT_IMPRO_7_6(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImpro76)) 
#define CT_IS_IMPRO_7_6(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IMPRO_7_6)) 


typedef struct _CtImpro76 CtImpro76;
typedef struct _CtImpro76Private CtImpro76Private;

struct _CtImpro76 
{
	KObject parent;
};


KConstType ct_impro_7_6_get_type(void);
CtImpro76* ct_impro_7_6_new(void);
CtImpro76* ct_impro_7_6_get(void);

#ifndef CO_CT_IM_PRO_DISABL
void ct_im_pro_7_60( const kuint32 idx );
void ct_im_pro_7_61( const kuint32 idx );
void ct_im_pro_7_62( const kuint32 idx );
void ct_im_pro_7_63( const kuint32 idx );
void ct_im_pro_7_64( const kuint32 idx );
void ct_im_pro_7_65( const kuint32 idx );
void ct_im_pro_7_66( const kuint32 idx );
void ct_im_pro_7_67( const kuint32 idx );
void ct_im_pro_7_68( const kuint32 idx );
void ct_im_pro_7_69( const kuint32 idx );
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __CT_IMPRO_7_6_H__ */
