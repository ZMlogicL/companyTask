/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : CtImpro75
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IMPRO_7_5_H__
#define __CT_IMPRO_7_5_H__


#include <klib.h>
#include "ctimprofile.h"


#define CT_TYPE_IMPRO_7_5                  (ct_impro_7_5_get_type())
#define CT_IMPRO_7_5(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImpro75)) 
#define CT_IS_IMPRO_7_5(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IMPRO_7_5)) 


typedef struct _CtImpro75 CtImpro75;
typedef struct _CtImpro75Private CtImpro75Private;

struct _CtImpro75 
{
	KObject parent;
};


KConstType ct_impro_7_5_get_type(void);
CtImpro75* ct_impro_7_5_new(void);
CtImpro75* ct_impro_7_5_get(void);

#ifndef CO_CT_IM_PRO_DISABL
void ct_im_pro_7_5_0(CtImpro75* self, const kuint32 idx );
void ct_im_pro_7_5_1(CtImpro75* self, const kuint32 idx );
void ct_im_pro_7_5_2(CtImpro75* self, const kuint32 idx );
void ct_im_pro_7_5_3(CtImpro75* self, const kuint32 idx );
void ct_im_pro_7_5_4(CtImpro75* self, const kuint32 idx );
void ct_im_pro_7_5_5(CtImpro75* self, const kuint32 idx );
void ct_im_pro_7_5_6(CtImpro75* self, const kuint32 idx );
void ct_im_pro_7_5_7(CtImpro75* self, const kuint32 idx );
void ct_im_pro_7_5_8(CtImpro75* self, const kuint32 idx );
void ct_im_pro_7_5_9(CtImpro75* self, const kuint32 idx );
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __CT_IMPRO_7_5_H__ */
