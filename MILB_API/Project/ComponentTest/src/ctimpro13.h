/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 陈元
*@brief : CtImPro13
*@rely : klib
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_PRO1_3_H__
#define __CT_IM_PRO1_3_H__


#include <klib.h>
#include "ctimprofile.h"
#include "impro1print.h"


#define CT_TYPE_IM_PRO1_3                  (ct_im_pro1_3_get_type())
#define CT_IM_PRO1_3(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImPro13)) 
#define CT_IS_IM_PRO1_3(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_PRO1_3)) 


typedef struct _CtImPro13 CtImPro13;
typedef struct _CtImPro13Private CtImPro13Private;


struct _CtImPro13 
{
	KObject parent;
	CtImPro13Private *priv;
};


KConstType 	ct_im_pro1_3_get_type(void);
CtImPro13* 	ct_im_pro1_3_new(void);

#ifndef CO_CT_IM_PRO_DISABLE
void 			ct_im_pro1_3_0(CtImPro13* self, const kuint32 idx);
void 			ct_im_pro1_3_1(CtImPro13* self, const kuint32 idx);
void 			ct_im_pro1_3_2(CtImPro13* self, const kuint32 idx);
void 			ct_im_pro1_3_3(CtImPro13* self, const kuint32 idx);
void 			ct_im_pro1_3_4(CtImPro13* self, const kuint32 idx);
void 			ct_im_pro1_3_5(CtImPro13* self, const kuint32 idx);
void 			ct_im_pro1_3_6(CtImPro13* self, const kuint32 idx);
void 			ct_im_pro1_3_7(CtImPro13* self, const kuint32 idx);
void 			ct_im_pro1_3_8(CtImPro13* self, const kuint32 idx);
void 			ct_im_pro1_3_9(CtImPro13* self, const kuint32 idx);
#endif //CO_CT_IM_PRO_DISABLE


#endif /* __CT_IM_PRO1_3_H__ */
