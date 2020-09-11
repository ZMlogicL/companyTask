/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈元
*@brief : CtImPro32
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_PRO3_2_H__
#define __CT_IM_PRO3_2_H__


#include <klib.h>
#include "ctimprofile.h"
#include "impro3print.h"


#define CT_TYPE_IM_PRO3_2                  (ct_im_pro3_2_get_type())
#define CT_IM_PRO3_2(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImPro32)) 
#define CT_IS_IM_PRO3_2(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_PRO3_2)) 


typedef struct _CtImPro32 CtImPro32;
typedef struct _CtImPro32Private CtImPro32Private;


struct _CtImPro32 
{
	KObject parent;
};


KConstType 	ct_im_pro3_2_get_type(void);
CtImPro32* 	ct_im_pro3_2_new(void);

#ifndef CO_CT_IM_PRO_DISABLE
void 			ct_im_pro3_2_0(CtImPro32* self, const UINT32 idx);
void 			ct_im_pro3_2_1(CtImPro32* self, const UINT32 idx);
void 			ct_im_pro3_2_2(CtImPro32* self, const UINT32 idx);
void 			ct_im_pro3_2_3(CtImPro32* self, const UINT32 idx);
void 			ct_im_pro3_2_4(CtImPro32* self, const UINT32 idx);
void 			ct_im_pro3_2_5(CtImPro32* self, const UINT32 idx);
void 			ct_im_pro3_2_6(CtImPro32* self, const UINT32 idx);
void 			ct_im_pro3_2_7(CtImPro32* self, const UINT32 idx);
void 			ct_im_pro3_2_8(CtImPro32* self, const UINT32 idx);
void 			ct_im_pro3_2_9(CtImPro32* self, const UINT32 idx);
#endif   //CO_CT_IM_PRO_DISABLE


#endif /* __CT_IM_PRO3_2_H__ */
