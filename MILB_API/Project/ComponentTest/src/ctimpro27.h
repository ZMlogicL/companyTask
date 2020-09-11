/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 陈元
*@brief : CtImPro27
*@rely : klib
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_PRO2_7_H__
#define __CT_IM_PRO2_7_H__


#include <klib.h>
#include "ctimprofile.h"
#include "impro2print.h"


#define CT_TYPE_IM_PRO2_7                  (ct_im_pro2_7_get_type())
#define CT_IM_PRO2_7(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImPro27)) 
#define CT_IS_IM_PRO2_7(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_PRO2_7)) 


typedef struct _CtImPro27 CtImPro27;
typedef struct _CtImPro27Private CtImPro27Private;


struct _CtImPro27 
{
	KObject parent;
	CtImPro27Private *priv;
};


KConstType 	ct_im_pro2_7_get_type(void);
CtImPro27* 	ct_im_pro2_7_new(void);

#ifndef CO_CT_IM_PRO_DISABLE
void 			ct_im_pro2_7_0(CtImPro27* self, const kuint32 idx);
void 			ct_im_pro2_7_1(CtImPro27* self, const kuint32 idx);
void 			ct_im_pro2_7_2(CtImPro27* self, const kuint32 idx);
void 			ct_im_pro2_7_3(CtImPro27* self, const kuint32 idx);
void 			ct_im_pro2_7_4(CtImPro27* self, const kuint32 idx);
void 			ct_im_pro2_7_5(CtImPro27* self, const kuint32 idx);
#endif  //CO_CT_IM_PRO_DISABLE


#endif /* __CT_IM_PRO2_7_H__ */
