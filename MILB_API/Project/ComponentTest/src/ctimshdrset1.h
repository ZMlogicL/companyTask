/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-03
*@author : maoguangkun
*@brief : CtImShdrSet1
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_SHDR_SET1_H__
#define __CT_IM_SHDR_SET1_H__


#include <klib.h>

#include "ctimshdrset2.h"


#define CT_TYPE_IM_SHDR_SET1                  (ct_im_shdr_set1_get_type())
#define CT_IM_SHDR_SET1(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImShdrSet1)) 
#define CT_IS_IM_SHDR_SET1(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_SHDR_SET1)) 


typedef struct _CtImShdrSet1 CtImShdrSet1;
typedef struct _CtImShdrSet1Private CtImShdrSet1Private;


struct _CtImShdrSet1 
{
	KObject parent;
};


KConstType 		ct_im_shdr_set1_get_type(void);
CtImShdrSet1* 	ct_im_shdr_set1_get(void);

VOID 					ct_im_shdr_set1_post(CtImShdrSet1* self);
VOID 					ct_im_shdr_set1_resize(CtImShdrSet1* self);
VOID					ct_im_shdr_set1_smc(CtImShdrSet1* self);
VOID					ct_im_shdr_set1_dgr(CtImShdrSet1* self);
VOID					ct_im_shdr_set1_dgg(CtImShdrSet1* self);
VOID					ct_im_shdr_set1_dgb(CtImShdrSet1* self);
VOID					ct_im_shdr_set1_dg(CtImShdrSet1* self);
VOID					ct_im_shdr_set1_axi(CtImShdrSet1* self);

#endif /* __CT_IM_SHDR_SET1_H__ */
