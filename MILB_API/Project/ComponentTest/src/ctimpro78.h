/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : CtImpro78
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IMPRO_7_8_H__
#define __CT_IMPRO_7_8_H__


#include <klib.h>
#include "ctimprofile.h"


#define CT_TYPE_IMPRO_7_8                  (ct_impro_7_8_get_type())
#define CT_IMPRO_7_8(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImpro78)) 
#define CT_IS_IMPRO_7_8(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IMPRO_7_8)) 


typedef struct _CtImpro78 CtImpro78;
typedef struct _CtImpro78Private CtImpro78Private;

struct _CtImpro78 
{
	KObject parent;
};


KConstType ct_impro_7_8_get_type(void);
CtImpro78* ct_impro_7_8_new(void);
CtImpro78* ct_impro_7_8_get(void);

#ifndef CO_CT_IM_PRO_DISABL
void ct_im_pro_7_80( const kuint32 idx );
void ct_im_pro_7_81( const kuint32 idx );
void ct_im_pro_7_82( const kuint32 idx );
void ct_im_pro_7_83( const kuint32 idx );
void ct_im_pro_7_84( const kuint32 idx );
void ct_im_pro_7_85( const kuint32 idx );
void ct_im_pro_7_86( const kuint32 idx );
void ct_im_pro_7_87( const kuint32 idx );
void ct_im_pro_7_88( const kuint32 idx );
void ct_im_pro_7_89( const kuint32 idx );
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __CT_IMPRO_7_8_H__ */