/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 陈元
*@brief : CtImPro17
*@rely : klib
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_PRO1_7_H__
#define __CT_IM_PRO1_7_H__


#include <klib.h>
#include "ctimprofile.h"
#include "impro1print.h"


#define CT_TYPE_IM_PRO1_7                  (ct_im_pro1_7_get_type())
#define CT_IM_PRO1_7(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImPro17)) 
#define CT_IS_IM_PRO1_7(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_PRO1_7)) 


typedef struct _CtImPro17 CtImPro17;
typedef struct _CtImPro17Private CtImPro17Private;


struct _CtImPro17 
{
	KObject parent;
	CtImPro17Private *priv;
};


KConstType 	ct_im_pro1_7_get_type(void);
CtImPro17* 	ct_im_pro1_7_new(void);

#ifndef CO_CT_IM_PRO_DISABLE
void 			ct_im_pro1_7_0(CtImPro17* self, const kuint32 idx);
void 			ct_im_pro1_7_1(CtImPro17* self, const kuint32 idx);
void 			ct_im_pro1_7_2(CtImPro17* self, const kuint32 idx);
#endif //CO_CT_IM_PRO_DISABLE


#endif /* __CT_IM_PRO1_7_H__ */
