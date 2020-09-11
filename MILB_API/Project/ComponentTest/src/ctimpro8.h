/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 陈阳
*@brief : CtImPro8
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_PRO_8_H__
#define __CT_IM_PRO_8_H__


#include <klib.h>
#include "ctimprofile.h"
#include "impro81slvs.h"


#define CT_TYPE_IM_PRO_8                  (ct_im_pro_8_get_type())
#define CT_IM_PRO_8(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImPro8)) 
#define CT_IS_IM_PRO_8(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_PRO_8)) 


typedef struct _CtImPro8 CtImPro8;
typedef struct _CtImPro8Private CtImPro8Private;

struct _CtImPro8 
{
	KObject parent;
};


KConstType ct_im_pro_8_get_type(void);
CtImPro8* ct_im_pro_8_new(void);
CtImPro8* ct_im_pro_8_get(void);

#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro_8_1(CtImPro8 *self,const kuint32 idx);
void ct_im_pro_8_2(CtImPro8 *self,const kuint32 idx);
void ct_im_pro_8_3(CtImPro8 *self,const kuint32 idx);
void ct_im_pro_8_4(CtImPro8 *self,const kuint32 idx);
void ct_im_pro_8_5(CtImPro8 *self,const kuint32 idx);
void ct_im_pro_8_6(CtImPro8 *self,const kuint32 idx);
void ct_im_pro_8_7(CtImPro8 *self,const kuint32 idx);
void ct_im_pro_8_8(CtImPro8 *self,const kuint32 idx);
void ct_im_pro_8_9(CtImPro8 *self,const kuint32 idx);
void ct_im_pro_8_10(CtImPro8 *self,const kuint32 idx);
#endif

#endif /* __CT_IM_PRO_8_H__ */
