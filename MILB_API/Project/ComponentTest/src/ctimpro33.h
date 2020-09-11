/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈元
*@brief : CtImPro33
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_PRO3_3_H__
#define __CT_IM_PRO3_3_H__


#include <klib.h>
#include "ctimprofile.h"
#include "impro3print.h"


#define CT_TYPE_IM_PRO3_3                  (ct_im_pro3_3_get_type())
#define CT_IM_PRO3_3(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImPro33)) 
#define CT_IS_IM_PRO3_3(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_PRO3_3)) 


typedef struct _CtImPro33 CtImPro33;
typedef struct _CtImPro33Private CtImPro33Private;

struct _CtImPro33 
{
	KObject parent;
};


KConstType ct_im_pro3_3_get_type(void);
CtImPro33* ct_im_pro3_3_new(void);

#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro3_3_0(CtImPro33* self, const UINT32 idx);
void ct_im_pro3_3_1(CtImPro33* self, const UINT32 idx);
void ct_im_pro3_3_2(CtImPro33* self, const UINT32 idx);
void ct_im_pro3_3_3(CtImPro33* self, const UINT32 idx);
void ct_im_pro3_3_4(CtImPro33* self, const UINT32 idx);
void ct_im_pro3_3_5(CtImPro33* self, const UINT32 idx);
void ct_im_pro3_3_6(CtImPro33* self, const UINT32 idx);
void ct_im_pro3_3_7(CtImPro33* self, const UINT32 idx);
void ct_im_pro3_3_8(CtImPro33* self, const UINT32 idx);
#endif   //CO_CT_IM_PRO_DISABLE


#endif /* __CT_IM_PRO3_3_H__ */
