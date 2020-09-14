/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : CtImpro63
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IMPRO_6_3_H__
#define __CT_IMPRO_6_3_H__


#include <klib.h>
#include "ctimprofile.h"


#define CT_TYPE_IMPRO_6_3                  (ct_impro_6_3_get_type())
#define CT_IMPRO_6_3(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImpro63)) 
#define CT_IS_IMPRO_6_3(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IMPRO_6_3)) 


typedef struct _CtImpro63 CtImpro63;
typedef struct _CtImpro63Private CtImpro63Private;

struct _CtImpro63 
{
	KObject parent;
};


KConstType ct_impro_6_3_get_type(void);
CtImpro63* ct_impro_6_3_new(void);
CtImpro63* ct_impro_6_3_get(void);

#ifndef CO_CT_IM_PRO_DISABL
void ct_im_pro_6_3_0(CtImpro63* self, const kuint32 idx);
void ct_im_pro_6_3_1(CtImpro63* self, const kuint32 idx);
void ct_im_pro_6_3_2(CtImpro63* self, const kuint32 idx);
void ct_im_pro_6_3_3(CtImpro63* self, const kuint32 idx);
void ct_im_pro_6_3_4(CtImpro63* self, const kuint32 idx);
void ct_im_pro_6_3_5(CtImpro63* self, const kuint32 idx);
void ct_im_pro_6_3_6(CtImpro63* self, const kuint32 idx);
void ct_im_pro_6_3_7(CtImpro63* self, const kuint32 idx);
void ct_im_pro_6_3_8(CtImpro63* self, const kuint32 idx);
void ct_im_pro_6_3_9(CtImpro63* self, const kuint32 idx);
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __CT_IMPRO_6_3_H__ */
