/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 陈元
*@brief : CtImPro22
*@rely : klib
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_PRO2_2_H__
#define __CT_IM_PRO2_2_H__


#include <klib.h>
#include "ctimprofile.h"
#include "impro2print.h"


#define CT_TYPE_IM_PRO2_2                  (ct_im_pro2_2_get_type())
#define CT_IM_PRO2_2(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImPro22)) 
#define CT_IS_IM_PRO2_2(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_PRO2_2)) 


typedef struct _CtImPro22 CtImPro22;
typedef struct _CtImPro22Private CtImPro22Private;


struct _CtImPro22 
{
	KObject parent;
	CtImPro22Private* priv;
};


KConstType 	ct_im_pro2_2_get_type(void);
CtImPro22* 	ct_im_pro2_2_new(void);

#ifndef CO_CT_IM_PRO_DISABLE
void 			ct_im_pro2_2_0(CtImPro22* self, const kuint32 idx);
void 			ct_im_pro2_2_1(CtImPro22* self, const kuint32 idx);
void 			ct_im_pro2_2_2(CtImPro22* self, const kuint32 idx);
void 			ct_im_pro2_2_3(CtImPro22* self, const kuint32 idx);
void 			ct_im_pro2_2_4(CtImPro22* self, const kuint32 idx);
void 			ct_im_pro2_2_5(CtImPro22* self, const kuint32 idx);
void 			ct_im_pro2_2_6(CtImPro22* self, const kuint32 idx);
void 			ct_im_pro2_2_7(CtImPro22* self, const kuint32 idx);
void 			ct_im_pro2_2_8(CtImPro22* self, const kuint32 idx);
void 			ct_im_pro2_2_9(CtImPro22* self, const kuint32 idx);
#endif  //CO_CT_IM_PRO_DISABLE


#endif /* __CT_IM_PRO2_2_H__ */
