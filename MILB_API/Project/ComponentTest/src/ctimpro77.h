/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : CtImpro77
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IMPRO_7_7_H__
#define __CT_IMPRO_7_7_H__


#include <klib.h>
#include "ctimprofile.h"


#define CT_TYPE_IMPRO_7_7                  (ct_impro_7_7_get_type())
#define CT_IMPRO_7_7(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImpro77)) 
#define CT_IS_IMPRO_7_7(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IMPRO_7_7)) 


typedef struct _CtImpro77 CtImpro77;
typedef struct _CtImpro77Private CtImpro77Private;

struct _CtImpro77 
{
	KObject parent;
};


KConstType ct_impro_7_7_get_type(void);
CtImpro77* ct_impro_7_7_new(void);
CtImpro77* ct_impro_7_7_get(void);

#ifndef CO_CT_IM_PRO_DISABL
void ct_im_pro_7_7_0(CtImpro77* self, const kuint32 idx );
void ct_im_pro_7_7_1(CtImpro77* self, const kuint32 idx );
void ct_im_pro_7_7_2(CtImpro77* self, const kuint32 idx );
void ct_im_pro_7_7_3(CtImpro77* self, const kuint32 idx );
void ct_im_pro_7_7_4(CtImpro77* self, const kuint32 idx );
void ct_im_pro_7_7_5(CtImpro77* self, const kuint32 idx );
void ct_im_pro_7_7_6(CtImpro77* self, const kuint32 idx );
void ct_im_pro_7_7_7(CtImpro77* self, const kuint32 idx );
void ct_im_pro_7_7_8(CtImpro77* self, const kuint32 idx );
void ct_im_pro_7_7_9(CtImpro77* self, const kuint32 idx );
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __CT_IMPRO_7_7_H__ */
