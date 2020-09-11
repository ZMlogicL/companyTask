/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-03
*@author : maoguangkun
*@brief : CtImShdrSet2
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_SHDR_SET2_H__
#define __CT_IM_SHDR_SET2_H__


#include <klib.h>

#include "ctimshdrtools.h"


#define CT_TYPE_IM_SHDR_SET2                  (ct_im_shdr_set2_get_type())
#define CT_IM_SHDR_SET2(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImShdrSet2)) 
#define CT_IS_IM_SHDR_SET2(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_SHDR_SET2)) 


typedef struct _CtImShdrSet2 CtImShdrSet2;
typedef struct _CtImShdrSet2Private CtImShdrSet2Private;


struct _CtImShdrSet2 
{
	KObject parent;
};


KConstType 		ct_im_shdr_set2_get_type(void);
CtImShdrSet2*	ct_im_shdr_set2_get(void);

VOID 					ct_im_shdr_set2_get_ctrl(CtImShdrSet2* self);
VOID					ct_im_shdr_set2_get_pre(CtImShdrSet2* self);
VOID					ct_im_shdr_set2_get_fmd(CtImShdrSet2* self);
VOID					ct_im_shdr_set2_get_pmsk(CtImShdrSet2* self);
VOID					ct_im_shdr_set2_get_spnr(CtImShdrSet2* self);
VOID					ct_im_shdr_set2_get_mask(CtImShdrSet2* self);
VOID					ct_im_shdr_set2_get_bld(CtImShdrSet2* self);
VOID					ct_im_shdr_set2_get_post(CtImShdrSet2* self);
VOID					ct_im_shdr_set2_get_resize(CtImShdrSet2* self);
VOID					ct_im_shdr_set2_get_smc(CtImShdrSet2* self);
VOID					ct_im_shdr_set2_get_dgr(CtImShdrSet2* self);
VOID					ct_im_shdr_set2_get_dgg(CtImShdrSet2* self);
VOID					ct_im_shdr_set2_get_dgb(CtImShdrSet2* self);
VOID					ct_im_shdr_set2_get_dg(CtImShdrSet2* self);
VOID 					ct_im_shdr_set2_get_axires(CtImShdrSet2* self);

#endif /* __CT_IM_SHDR_SET2_H__ */
