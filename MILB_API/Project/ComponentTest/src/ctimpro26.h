/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 陈元
*@brief : CtImPro26
*@rely : klib
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_PRO2_6_H__
#define __CT_IM_PRO2_6_H__


#include <klib.h>
#include "ctimprofile.h"
#include "impro2print.h"


#define CT_TYPE_IM_PRO2_6                  (ct_im_pro2_6_get_type())
#define CT_IM_PRO2_6(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImPro26)) 
#define CT_IS_IM_PRO2_6(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_PRO2_6)) 


typedef struct _CtImPro26 CtImPro26;
typedef struct _CtImPro26Private CtImPro26Private;


struct _CtImPro26 
{
	KObject parent;
	CtImPro26Private *priv;
};


KConstType 	ct_im_pro2_6_get_type(void);
CtImPro26* 	ct_im_pro2_6_new(void);

#ifndef CO_CT_IM_PRO_DISABLE
void 			ct_im_pro2_6_0(CtImPro26* self, const kuint32 idx);
void 			ct_im_pro2_6_1(CtImPro26* self, const kuint32 idx);
void 			ct_im_pro2_6_2(CtImPro26* self, const kuint32 idx);
void 			ct_im_pro2_6_3(CtImPro26* self, const kuint32 idx);
void 			ct_im_pro2_6_4(CtImPro26* self, const kuint32 idx);
void 			ct_im_pro2_6_5(CtImPro26* self, const kuint32 idx);
void 			ct_im_pro2_6_6(CtImPro26* self, const kuint32 idx);
void 			ct_im_pro2_6_7(CtImPro26* self, const kuint32 idx);
void 			ct_im_pro2_6_8(CtImPro26* self, const kuint32 idx);
void 			ct_im_pro2_6_9(CtImPro26* self, const kuint32 idx);
#endif  //CO_CT_IM_PRO_DISABLE


#endif /* __CT_IM_PRO2_6_H__ */
