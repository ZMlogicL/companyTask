/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 陈元
*@brief : CtImPro2
*@rely : klib
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_PRO_2_H__
#define __CT_IM_PRO_2_H__


#include <klib.h>
#include "ctimprofile.h"
#include "impro2print.h"


#define CT_TYPE_IM_PRO2                  (ct_im_pro2_get_type())
#define CT_IM_PRO2(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImPro2))
#define CT_IS_IM_PRO2(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_PRO2))


typedef struct _CtImPro2 CtImPro2;
typedef struct _CtImPro2Private CtImPro2Private;


struct _CtImPro2 
{
	KObject parent;
	CtImPro2Private *priv;
};


KConstType 	ct_im_pro2_get_type(void);
CtImPro2* 	ct_im_pro2_new(void);

#ifndef CO_CT_IM_PRO_DISABLE
void 			ct_im_pro2_1(CtImPro2* self, const kuint32 idx);
void 			ct_im_pro2_2(CtImPro2* self, const kuint32 idx);
void 			ct_im_pro2_3(CtImPro2* self, const kuint32 idx);
void 			ct_im_pro2_4(CtImPro2* self, const kuint32 idx);
void 			ct_im_pro2_5(CtImPro2* self, const kuint32 idx);
void 			ct_im_pro2_6(CtImPro2* self, const kuint32 idx);
void 			ct_im_pro2_7(CtImPro2* self, const kuint32 idx);
void 			ct_im_pro2_8(CtImPro2* self, const kuint32 idx);
void 			ct_im_pro2_9(CtImPro2* self, const kuint32 idx);
#endif  //CO_CT_IM_PRO_DISABLE


#endif /* __CT_IM_PRO_2_H__ */
