/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈元
*@brief : CtImPro31
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_PRO3_1_H__
#define __CT_IM_PRO3_1_H__


#include <klib.h>
#include "ctimprofile.h"
#include "impro3print.h"


#define CT_TYPE_IM_PRO3_1                  (ct_im_pro3_1_get_type())
#define CT_IM_PRO3_1(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImPro31)) 
#define CT_IS_IM_PRO3_1(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_PRO3_1)) 


typedef struct _CtImPro31 CtImPro31;
typedef struct _CtImPro31Private CtImPro31Private;


struct _CtImPro31 
{
	KObject parent;
};


KConstType 	ct_im_pro3_1_get_type(void);
CtImPro31* 	ct_im_pro3_1_new(void);

#ifndef CO_CT_IM_PRO_DISABLE
void 			ct_im_pro3_1_0(CtImPro31* self, const UINT32 idx);
void 			ct_im_pro3_1_1(CtImPro31* self, const UINT32 idx);
void 			ct_im_pro3_1_2(CtImPro31* self, const UINT32 idx);
void 			ct_im_pro3_1_3(CtImPro31* self, const UINT32 idx);
void 			ct_im_pro3_1_4(CtImPro31* self, const UINT32 idx);
void 			ct_im_pro3_1_5(CtImPro31* self, const UINT32 idx);
void 			ct_im_pro3_1_6(CtImPro31* self, const UINT32 idx);
void 			ct_im_pro3_1_7(CtImPro31* self, const UINT32 idx);
void 			ct_im_pro3_1_8(CtImPro31* self, const UINT32 idx);
void 			ct_im_pro3_1_9(CtImPro31* self, const UINT32 idx);
#endif   //CO_CT_IM_PRO_DISABLE


#endif /* __CT_IM_PRO3_1_H__ */
