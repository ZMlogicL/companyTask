/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 陈元
*@brief : CtImPro14
*@rely : klib
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_PRO1_4_H__
#define __CT_IM_PRO1_4_H__


#include <klib.h>
#include "ctimprofile.h"
#include "impro1print.h"


#define CT_TYPE_IM_PRO1_4                  (ct_im_pro1_4_get_type())
#define CT_IM_PRO1_4(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImPro14)) 
#define CT_IS_IM_PRO1_4(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_PRO1_4)) 


typedef struct _CtImPro14 CtImPro14;
typedef struct _CtImPro14Private CtImPro14Private;

struct _CtImPro14 
{
	KObject parent;
	CtImPro14Private *priv;
};


KConstType 	ct_im_pro1_4_get_type(void);
CtImPro14* 	ct_im_pro1_4_new(void);

#ifndef CO_CT_IM_PRO_DISABLE
void 			ct_im_pro1_4_0(CtImPro14* self, const kuint32 idx);
void 			ct_im_pro1_4_1(CtImPro14* self, const kuint32 idx);
void 			ct_im_pro1_4_2(CtImPro14* self, const kuint32 idx);
void 			ct_im_pro1_4_3(CtImPro14* self, const kuint32 idx);
void 			ct_im_pro1_4_4(CtImPro14* self, const kuint32 idx);
void 			ct_im_pro1_4_5(CtImPro14* self, const kuint32 idx);
void 			ct_im_pro1_4_6(CtImPro14* self, const kuint32 idx);
void 			ct_im_pro1_4_7(CtImPro14* self, const kuint32 idx);
void 			ct_im_pro1_4_8(CtImPro14* self, const kuint32 idx);
void 			ct_im_pro1_4_9(CtImPro14* self, const kuint32 idx);
#endif //CO_CT_IM_PRO_DISABLE


#endif /* __CT_IM_PRO1_4_H__ */
