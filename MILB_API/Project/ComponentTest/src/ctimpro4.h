/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 陈阳
*@brief : CtImPro4
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_PRO4_H__
#define __CT_IM_PRO4_H__


#include <klib.h>
#include "ctimprofile.h"
#include "impro4print.h"

#define CT_TYPE_IM_PRO4                  (ct_im_pro4_get_type())
#define CT_IM_PRO4(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImPro4))
#define CT_IS_IM_PRO4(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_PRO4))


typedef struct _CtImPro4 CtImPro4;
typedef struct _CtImPro4Private CtImPro4Private;


struct _CtImPro4 
{
	KObject parent;
};


KConstType 	ct_im_pro4_get_type(void);
CtImPro4* 	ct_im_pro4_new(void);

#ifndef CO_CT_IM_PRO_DISABLE
void 			ct_im_pro4_1(CtImPro4* self, const kuint32 idx);
void 			ct_im_pro4_2(CtImPro4* self, const kuint32 idx);
void 			ct_im_pro4_3(CtImPro4* self, const kuint32 idx);
void 			ct_im_pro4_4(CtImPro4* self, const kuint32 idx);
void 			ct_im_pro4_5(CtImPro4* self, const kuint32 idx);
void 			ct_im_pro4_6(CtImPro4* self, const kuint32 idx);
void 			ct_im_pro4_7(CtImPro4* self, const kuint32 idx);
void 			ct_im_pro4_8(CtImPro4* self, const kuint32 idx);
void 			ct_im_pro4_9(CtImPro4* self, const kuint32 idx);
void 			ct_im_pro4_10(CtImPro4* self, const kuint32 idx);
void 			ct_im_pro4_11(CtImPro4* self, const kuint32 idx);
void 			ct_im_pro4_12(CtImPro4* self, const kuint32 idx);
void 			ct_im_pro4_13(CtImPro4* self, const kuint32 idx);
void 			ct_im_pro4_14(CtImPro4* self, const kuint32 idx);
void 			ct_im_pro4_15(CtImPro4* self, const kuint32 idx);
void 			ct_im_pro4_16(CtImPro4* self, const kuint32 idx);
void 			ct_im_pro4_17(CtImPro4* self, const kuint32 idx);
void 			ct_im_pro4_18(CtImPro4* self, const kuint32 idx);
void 			ct_im_pro4_19(CtImPro4* self, const kuint32 idx);
void 			ct_im_pro4_20(CtImPro4* self, const kuint32 idx);
void 			ct_im_pro4_21(CtImPro4* self, const kuint32 idx);
void 			ct_im_pro4_22(CtImPro4* self, const kuint32 idx);
void 			ct_im_pro4_23(CtImPro4* self, const kuint32 idx);
void 			ct_im_pro4_24(CtImPro4* self, const kuint32 idx);
void 			ct_im_pro4_25(CtImPro4* self, const kuint32 idx);
void 			ct_im_pro4_26(CtImPro4* self, const kuint32 idx);
void 			ct_im_pro4_27(CtImPro4* self, const kuint32 idx);
void 			ct_im_pro4_28(CtImPro4* self, const kuint32 idx);
#endif //CO_CT_IM_PRO_DISABLE


#endif /* __CT_IM_PRO4_H__ */
