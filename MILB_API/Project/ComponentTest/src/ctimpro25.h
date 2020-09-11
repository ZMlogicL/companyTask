/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 陈元
*@brief : CtImPro25
*@rely : klib
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_PRO2_5_H__
#define __CT_IM_PRO2_5_H__


#include <klib.h>
#include "ctimprofile.h"
#include "impro2print.h"


#define CT_TYPE_IM_PRO2_5                  (ct_im_pro2_5_get_type())
#define CT_IM_PRO2_5(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImPro25)) 
#define CT_IS_IM_PRO2_5(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_PRO2_5)) 


typedef struct _CtImPro25 CtImPro25;
typedef struct _CtImPro25Private CtImPro25Private;


struct _CtImPro25 
{
	KObject parent;
	CtImPro25Private *priv;
};


KConstType 	ct_im_pro2_5_get_type(void);
CtImPro25* 	ct_im_pro2_5_new(void);

#ifndef CO_CT_IM_PRO_DISABLE
void 			ct_im_pro2_5_0(CtImPro25* self, const kuint32 idx);
void 			ct_im_pro2_5_1(CtImPro25* self, const kuint32 idx);
void 			ct_im_pro2_5_2(CtImPro25* self, const kuint32 idx);
void 			ct_im_pro2_5_3(CtImPro25* self, const kuint32 idx);
void 			ct_im_pro2_5_4(CtImPro25* self, const kuint32 idx);
void 			ct_im_pro2_5_5(CtImPro25* self, const kuint32 idx);
void 			ct_im_pro2_5_6(CtImPro25* self, const kuint32 idx);
void 			ct_im_pro2_5_7(CtImPro25* self, const kuint32 idx);
void 			ct_im_pro2_5_8(CtImPro25* self, const kuint32 idx);
void 			ct_im_pro2_5_9(CtImPro25* self, const kuint32 idx);
#endif  //CO_CT_IM_PRO_DISABLE


#endif /* __CT_IM_PRO2_5_H__ */
