/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 陈元
*@brief : CtImPro24
*@rely : klib
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_PRO2_4_H__
#define __CT_IM_PRO2_4_H__


#include <klib.h>
#include "ctimprofile.h"
#include "impro2print.h"


#define CT_TYPE_IM_PRO2_4                  (ct_im_pro2_4_get_type())
#define CT_IM_PRO2_4(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImPro24)) 
#define CT_IS_IM_PRO2_4(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_PRO2_4)) 


typedef struct _CtImPro24 CtImPro24;
typedef struct _CtImPro24Private CtImPro24Private;


struct _CtImPro24 
{
	KObject parent;
	CtImPro24Private *priv;
};


KConstType 	ct_im_pro2_4_get_type(void);
CtImPro24* 	ct_im_pro2_4_new(void);

#ifndef CO_CT_IM_PRO_DISABLE
void 			ct_im_pro2_4_0(CtImPro24* self, const kuint32 idx);
void 			ct_im_pro2_4_1(CtImPro24* self, const kuint32 idx);
void 			ct_im_pro2_4_2(CtImPro24* self, const kuint32 idx);
void 			ct_im_pro2_4_3(CtImPro24* self, const kuint32 idx);
void 			ct_im_pro2_4_4(CtImPro24* self, const kuint32 idx);
void 			ct_im_pro2_4_5(CtImPro24* self, const kuint32 idx);
void 			ct_im_pro2_4_6(CtImPro24* self, const kuint32 idx);
void 			ct_im_pro2_4_7(CtImPro24* self, const kuint32 idx);
void 			ct_im_pro2_4_8(CtImPro24* self, const kuint32 idx);
void 			ct_im_pro2_4_9(CtImPro24* self, const kuint32 idx);
#endif  //CO_CT_IM_PRO_DISABLE


#endif /* __CT_IM_PRO2_4_H__ */
