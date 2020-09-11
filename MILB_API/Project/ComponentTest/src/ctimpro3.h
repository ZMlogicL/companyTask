/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈元
*@brief : CtImPro3
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_PRO_3_H__
#define __CT_IM_PRO_3_H__


#include <klib.h>
#include "ctimprofile.h"
#include "impro3print.h"


#define CT_TYPE_IM_PRO3                  (ct_im_pro3_get_type())
#define CT_IM_PRO3(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImPro3))
#define CT_IS_IM_PRO3(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_PRO3))


typedef struct _CtImPro3 CtImPro3;
typedef struct _CtImPro3Private CtImPro3Private;


struct _CtImPro3 
{
	KObject parent;
};


KConstType 	ct_im_pro3_get_type(void);
CtImPro3* 	ct_im_pro3_new(void);

#ifndef CO_CT_IM_PRO_DISABLE
void 			ct_im_pro3_1(CtImPro3* self, const UINT32 idx);
void 			ct_im_pro3_2(CtImPro3* self, const UINT32 idx);
void 			ct_im_pro3_3(CtImPro3* self, const UINT32 idx);
void 			ct_im_pro3_4(CtImPro3* self, const UINT32 idx);
void 			ct_im_pro3_5(CtImPro3* self, const UINT32 idx);
void 			ct_im_pro3_6(CtImPro3* self, const UINT32 idx);
void 			ct_im_pro3_7(CtImPro3* self, const UINT32 idx);
void 			ct_im_pro3_8(CtImPro3* self, const UINT32 idx);
void 			ct_im_pro3_9(CtImPro3* self, const UINT32 idx);
#endif   //CO_CT_IM_PRO_DISABLE

#endif /* __CT_IM_PRO_3_H__ */
