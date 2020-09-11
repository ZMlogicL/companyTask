/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-04
*@author : 陈元
*@brief : CtImPro5
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_PRO5_H__
#define __CT_IM_PRO5_H__


#include <klib.h>
#include "ctimprofile.h"
#include "impro5print.h"

#define CT_TYPE_IM_PRO5                  (ct_im_pro5_get_type())
#define CT_IM_PRO5(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImPro5))
#define CT_IS_IM_PRO5(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_PRO5))


typedef struct _CtImPro5 CtImPro5;
typedef struct _CtImPro5Private CtImPro5Private;


struct _CtImPro5 
{
	KObject parent;
};


KConstType 	ct_im_pro5_get_type(void);
CtImPro5* 	ct_im_pro5_new(void);

#ifndef CO_CT_IM_PRO_DISABLE
void 			ct_im_pro5_1(CtImPro5* self, const kuint32 idx);
void 			ct_im_pro5_2(CtImPro5* self, const kuint32 idx);
void 			ct_im_pro5_3(CtImPro5* self, const kuint32 idx);
void 			ct_im_pro5_4(CtImPro5* self, const kuint32 idx);
void 			ct_im_pro5_5(CtImPro5* self, const kuint32 idx);
void 			ct_im_pro5_6(CtImPro5* self, const kuint32 idx);
void 			ct_im_pro5_7(CtImPro5* self, const kuint32 idx);
void 			ct_im_pro5_8(CtImPro5* self, const kuint32 idx);
void 			ct_im_pro5_9(CtImPro5* self, const kuint32 idx);
void 			ct_im_pro5_10(CtImPro5* self, const kuint32 idx);
#endif

#endif /* __CT_IM_PRO5_H__ */
