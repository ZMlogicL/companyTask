/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 陈元
*@brief : CtImPro16
*@rely : klib
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_PRO1_6_H__
#define __CT_IM_PRO1_6_H__


#include <klib.h>
#include "ctimprofile.h"
#include "impro1print.h"


#define CT_TYPE_IM_PRO1_6                  (ct_im_pro1_6_get_type())
#define CT_IM_PRO1_6(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImPro16)) 
#define CT_IS_IM_PRO1_6(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_PRO1_6)) 


typedef struct _CtImPro16 CtImPro16;
typedef struct _CtImPro16Private CtImPro16Private;


struct _CtImPro16 
{
	KObject parent;
	CtImPro16Private *priv;
};


KConstType 	ct_im_pro1_6_get_type(void);
CtImPro16* 	ct_im_pro1_6_new(void);

#ifndef CO_CT_IM_PRO_DISABLE
void 			ct_im_pro1_6_0(CtImPro16* self, const kuint32 idx);
void 			ct_im_pro1_6_1(CtImPro16* self, const kuint32 idx);
void 			ct_im_pro1_6_2(CtImPro16* self, const kuint32 idx);
void 			ct_im_pro1_6_3(CtImPro16* self, const kuint32 idx);
void 			ct_im_pro1_6_4(CtImPro16* self, const kuint32 idx);
void 			ct_im_pro1_6_5(CtImPro16* self, const kuint32 idx);
void 			ct_im_pro1_6_6(CtImPro16* self, const kuint32 idx);
void 			ct_im_pro1_6_7(CtImPro16* self, const kuint32 idx);
void 			ct_im_pro1_6_8(CtImPro16* self, const kuint32 idx);
void 			ct_im_pro1_6_9(CtImPro16* self, const kuint32 idx);
#endif //CO_CT_IM_PRO_DISABLE


#endif /* __CT_IM_PRO1_6_H__ */
