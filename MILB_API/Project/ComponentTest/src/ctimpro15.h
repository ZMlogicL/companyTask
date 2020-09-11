/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 陈元
*@brief : CtImPro15
*@rely : klib
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_PRO1_5_H__
#define __CT_IM_PRO1_5_H__


#include <klib.h>
#include "ctimprofile.h"
#include "impro1print.h"


#define CT_TYPE_IM_PRO1_5                  (ct_im_pro1_5_get_type())
#define CT_IM_PRO1_5(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImPro15)) 
#define CT_IS_IM_PRO1_5(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_PRO1_5)) 


typedef struct _CtImPro15 CtImPro15;
typedef struct _CtImPro15Private CtImPro15Private;


struct _CtImPro15 
{
	KObject parent;
	CtImPro15Private *priv;
};


KConstType 	ct_im_pro1_5_get_type(void);
CtImPro15* 	ct_im_pro1_5_new(void);

#ifndef CO_CT_IM_PRO_DISABLE
void 			ct_im_pro1_5_0(CtImPro15* self, const kuint32 idx);
void 			ct_im_pro1_5_1(CtImPro15* self, const kuint32 idx);
void 			ct_im_pro1_5_2(CtImPro15* self, const kuint32 idx);
void 			ct_im_pro1_5_3(CtImPro15* self, const kuint32 idx);
void 			ct_im_pro1_5_4(CtImPro15* self, const kuint32 idx);
void 			ct_im_pro1_5_5(CtImPro15* self, const kuint32 idx);
void 			ct_im_pro1_5_6(CtImPro15* self, const kuint32 idx);
void 			ct_im_pro1_5_7(CtImPro15* self, const kuint32 idx);
void 			ct_im_pro1_5_8(CtImPro15* self, const kuint32 idx);
void 			ct_im_pro1_5_9(CtImPro15* self, const kuint32 idx);
#endif //CO_CT_IM_PRO_DISABLE


#endif /* __CT_IM_PRO1_5_H__ */
