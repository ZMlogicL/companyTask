/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 陈元
*@brief : CtImPro23
*@rely : klib
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_PRO2_3_H__
#define __CT_IM_PRO2_3_H__


#include <klib.h>
#include "ctimprofile.h"
#include "impro2print.h"


#define CT_TYPE_IM_PRO2_3                  (ct_im_pro2_3_get_type())
#define CT_IM_PRO2_3(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImPro23)) 
#define CT_IS_IM_PRO2_3(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_PRO2_3)) 


typedef struct _CtImPro23 CtImPro23;
typedef struct _CtImPro23Private CtImPro23Private;


struct _CtImPro23 
{
	KObject parent;
	CtImPro23Private *priv;
};


KConstType 	ct_im_pro2_3_get_type(void);
CtImPro23* 	ct_im_pro2_3_new(void);

#ifndef CO_CT_IM_PRO_DISABLE
void 			ct_im_pro2_3_0(CtImPro23* self, const kuint32 idx);
void 			ct_im_pro2_3_1(CtImPro23* self, const kuint32 idx);
void 			ct_im_pro2_3_2(CtImPro23* self, const kuint32 idx);
void 			ct_im_pro2_3_3(CtImPro23* self, const kuint32 idx);
void 			ct_im_pro2_3_4(CtImPro23* self, const kuint32 idx);
void 			ct_im_pro2_3_5(CtImPro23* self, const kuint32 idx);
void 			ct_im_pro2_3_6(CtImPro23* self, const kuint32 idx);
void 			ct_im_pro2_3_7(CtImPro23* self, const kuint32 idx);
void 			ct_im_pro2_3_8(CtImPro23* self, const kuint32 idx);
void 			ct_im_pro2_3_9(CtImPro23* self, const kuint32 idx);
#endif  //CO_CT_IM_PRO_DISABLE


#endif /* __CT_IM_PRO2_3_H__ */
