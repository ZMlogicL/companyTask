/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 陈元
*@brief : CtImPro1
*@rely : klib
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_PRO_1_H__
#define __CT_IM_PRO_1_H__


#include <klib.h>
#include "ctimprofile.h"
#include "impro1print.h"


#define CT_TYPE_IM_PRO1                  (ct_im_pro1_get_type())
#define CT_IM_PRO1(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImPro1))
#define CT_IS_IM_PRO1(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_PRO1))


typedef struct _CtImPro1 CtImPro1;
typedef struct _CtImPro1Private CtImPro1Private;


struct _CtImPro1 
{
	KObject parent;
	CtImPro1Private *priv;
};

KConstType 	ct_im_pro1_get_type(void);
CtImPro1* 	ct_im_pro1_new(void);

#ifndef CO_CT_IM_PRO_DISABLE
void 			ct_im_pro1_1(CtImPro1* self, const kuint32 idx);
void 			ct_im_pro1_2(CtImPro1* self, const kuint32 idx);
void 			ct_im_pro1_3(CtImPro1* self, const kuint32 idx);
void 			ct_im_pro1_4(CtImPro1* self, const kuint32 idx);
void 			ct_im_pro1_5(CtImPro1* self, const kuint32 idx);
void 			ct_im_pro1_6(CtImPro1* self, const kuint32 idx);
void 			ct_im_pro1_7(CtImPro1* self, const kuint32 idx);
void 			ct_im_pro1_8(CtImPro1* self, const kuint32 idx);
void 			ct_im_pro1_9(CtImPro1* self, const kuint32 idx);
#endif //CO_CT_IM_PRO_DISABLE


#endif /* __CT_IM_PRO_1_H__ */
