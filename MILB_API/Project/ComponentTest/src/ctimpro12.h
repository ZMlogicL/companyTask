/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 陈元
*@brief : CtImPro12
*@rely : klib
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_PRO1_2_H__
#define __CT_IM_PRO1_2_H__


#include <klib.h>
#include "ctimprofile.h"
#include "impro1print.h"


#define CT_TYPE_IM_PRO1_2                  (ct_im_pro1_2_get_type())
#define CT_IM_PRO1_2(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImPro12)) 
#define CT_IS_IM_PRO1_2(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_PRO1_2)) 


typedef struct _CtImPro12 CtImPro12;
typedef struct _CtImPro12Private CtImPro12Private;


struct _CtImPro12 
{
	KObject parent;
	CtImPro12Private *priv;
};


KConstType 	ct_im_pro1_2_get_type(void);
CtImPro12* 	ct_im_pro1_2_new(void);

#ifndef CO_CT_IM_PRO_DISABLE
void 			ct_im_pro1_2_0(CtImPro12* self, const kuint32 idx);
void 			ct_im_pro1_2_1(CtImPro12* self, const kuint32 idx);
void 			ct_im_pro1_2_2(CtImPro12* self, const kuint32 idx);
void 			ct_im_pro1_2_3(CtImPro12* self, const kuint32 idx);
void 			ct_im_pro1_2_4(CtImPro12* self, const kuint32 idx);
void 			ct_im_pro1_2_5(CtImPro12* self, const kuint32 idx);
void 			ct_im_pro1_2_6(CtImPro12* self, const kuint32 idx);
void 			ct_im_pro1_2_7(CtImPro12* self, const kuint32 idx);
void 			ct_im_pro1_2_8(CtImPro12* self, const kuint32 idx);
void 			ct_im_pro1_2_9(CtImPro12* self, const kuint32 idx);
#endif //CO_CT_IM_PRO_DISABLE


#endif /* __CT_IM_PRO1_2_H__ */
