/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : CtImpro61
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IMPRO_6_1_H__
#define __CT_IMPRO_6_1_H__


#include <klib.h>
#include "ctimprofile.h"


#define CT_TYPE_IMPRO_6_1                  (ct_impro_6_1_get_type())
#define CT_IMPRO_6_1(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImpro61)) 
#define CT_IS_IMPRO_6_1(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IMPRO_6_1)) 


typedef struct _CtImpro61 CtImpro61;
typedef struct _CtImpro61Private CtImpro61Private;

struct _CtImpro61 
{
	KObject parent;
};


KConstType ct_impro_6_1_get_type(void);
CtImpro61* ct_impro_6_1_new(void);
CtImpro61* ct_impro_6_1_get(void);

#ifndef CO_CT_IM_PRO_DISABL
void ct_im_pro_6_1_0(CtImpro61* self, const kuint32 idx);
void ct_im_pro_6_1_1(CtImpro61* self, const kuint32 idx);
void ct_im_pro_6_1_2(CtImpro61* self, const kuint32 idx);
void ct_im_pro_6_1_3(CtImpro61* self, const kuint32 idx);
void ct_im_pro_6_1_4(CtImpro61* self, const kuint32 idx);
void ct_im_pro_6_1_5(CtImpro61* self, const kuint32 idx);
void ct_im_pro_6_1_6(CtImpro61* self, const kuint32 idx);
void ct_im_pro_6_1_7(CtImpro61* self, const kuint32 idx);
void ct_im_pro_6_1_8(CtImpro61* self, const kuint32 idx);
void ct_im_pro_6_1_9(CtImpro61* self, const kuint32 idx);
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __CT_IMPRO_6_1_H__ */
