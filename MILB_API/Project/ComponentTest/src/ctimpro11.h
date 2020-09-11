/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 陈元
*@brief : CtImPro11
*@rely : klib
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_PRO1_1_H__
#define __CT_IM_PRO1_1_H__


#include <klib.h>
#include "ctimprofile.h"
#include "impro1print.h"


#define CT_TYPE_IM_PRO1_1                  (ct_im_pro1_1_get_type())
#define CT_IM_PRO1_1(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImPro11)) 
#define CT_IS_IM_PRO1_1(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_PRO1_1)) 


typedef struct _CtImPro11 CtImPro11;
typedef struct _CtImPro11Private CtImPro11Private;


struct _CtImPro11 
{
	KObject parent;
	CtImPro11Private *priv;
};


KConstType 	ct_im_pro1_1_get_type(void);
CtImPro11* 	ct_im_pro1_1_new(void);

#ifndef CO_CT_IM_PRO_DISABLE
void 			ct_im_pro1_1_0(CtImPro11* self, const kuint32 idx);
void 			ct_im_pro1_1_1(CtImPro11* self, const kuint32 idx);
void 			ct_im_pro1_1_2(CtImPro11* self, const kuint32 idx);
void 			ct_im_pro1_1_3(CtImPro11* self, const kuint32 idx);
void 			ct_im_pro1_1_4(CtImPro11* self, const kuint32 idx);
void 			ct_im_pro1_1_5(CtImPro11* self, const kuint32 idx);
void 			ct_im_pro1_1_6(CtImPro11* self, const kuint32 idx);
void 			ct_im_pro1_1_7(CtImPro11* self, const kuint32 idx);
void 			ct_im_pro1_1_8(CtImPro11* self, const kuint32 idx);
void 			ct_im_pro1_1_9(CtImPro11* self, const kuint32 idx);
#endif //CO_CT_IM_PRO_DISABLE


#endif /* __CT_IM_PRO1_1_H__ */
