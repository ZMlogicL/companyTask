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
void ct_im_pro_7_8_0(CtImpro78* self, const kuint32 idx );
void ct_im_pro_7_8_1(CtImpro78* self, const kuint32 idx );
void ct_im_pro_7_8_2(CtImpro78* self, const kuint32 idx );
void ct_im_pro_7_8_3(CtImpro78* self, const kuint32 idx );
void ct_im_pro_7_8_4(CtImpro78* self, const kuint32 idx );
void ct_im_pro_7_8_5(CtImpro78* self, const kuint32 idx );
void ct_im_pro_7_8_6(CtImpro78* self, const kuint32 idx );
void ct_im_pro_7_8_7(CtImpro78* self, const kuint32 idx );
void ct_im_pro_7_8_8(CtImpro78* self, const kuint32 idx );
void ct_im_pro_7_8_9(CtImpro78* self, const kuint32 idx );
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __CT_IMPRO_7_8_H__ */
