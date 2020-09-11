/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 陈元
*@brief : CtImPro21
*@rely : klib
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_PRO2_1_H__
#define __CT_IM_PRO2_1_H__


#include <klib.h>
#include "ctimprofile.h"
#include "impro2print.h"


#define CT_TYPE_IM_PRO2_1                  (ct_im_pro2_1_get_type())
#define CT_IM_PRO2_1(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImPro21)) 
#define CT_IS_IM_PRO2_1(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_PRO2_1)) 


typedef struct _CtImPro21 CtImPro21;
typedef struct _CtImPro21Private CtImPro21Private;


struct _CtImPro21 
{
	KObject parent;
	CtImPro21Private *priv;
};


KConstType 	ct_im_pro2_1_get_type(void);
CtImPro21* 	ct_im_pro2_1_new(void);

#ifndef CO_CT_IM_PRO_DISABLE
void 			ct_im_pro2_1_0(CtImPro21* self, const kuint32 idx);
void 			ct_im_pro2_1_1(CtImPro21* self, const kuint32 idx);
void 			ct_im_pro2_1_2(CtImPro21* self, const kuint32 idx);
void 			ct_im_pro2_1_3(CtImPro21* self, const kuint32 idx);
void 			ct_im_pro2_1_4(CtImPro21* self, const kuint32 idx);
void 			ct_im_pro2_1_5(CtImPro21* self, const kuint32 idx);
void 			ct_im_pro2_1_6(CtImPro21* self, const kuint32 idx);
void 			ct_im_pro2_1_7(CtImPro21* self, const kuint32 idx);
void 			ct_im_pro2_1_8(CtImPro21* self, const kuint32 idx);
void 			ct_im_pro2_1_9(CtImPro21* self, const kuint32 idx);
#endif  //CO_CT_IM_PRO_DISABLE


#endif /* __CT_IM_PRO2_1_H__ */
