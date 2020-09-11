/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-03
*@author : maoguangkun
*@brief : CtImShdrSet
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_SHDR_SET_H__
#define __CT_IM_SHDR_SET_H__


#include <klib.h>

#include "ctimshdrset1.h"


#define CT_TYPE_IM_SHDR_SET                  (ct_im_shdr_set_get_type())
#define CT_IM_SHDR_SET(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImShdrSet)) 
#define CT_IS_IM_SHDR_SET(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_SHDR_SET)) 


typedef struct _CtImShdrSet CtImShdrSet;
typedef struct _CtImShdrSetPrivate CtImShdrSetPrivate;


struct _CtImShdrSet 
{
	KObject parent;
};


KConstType 		ct_im_shdr_set_get_type(void);
CtImShdrSet* 	ct_im_shdr_set_get(void);

VOID 					ct_im_shdr_set_ctrl(CtImShdrSet* self);
VOID 					ct_im_shdr_set_pre(CtImShdrSet* self);
VOID 					ct_im_shdr_set_fmd(CtImShdrSet* self);
VOID 					ct_im_shdr_set_pmsk(CtImShdrSet* self);
VOID 					ct_im_shdr_set_spnr(CtImShdrSet* self);
VOID 					ct_im_shdr_set_mask(CtImShdrSet* self);
VOID 					ct_im_shdr_set_bld(CtImShdrSet* self);

#endif /* __CT_IM_SHDR_SET_H__ */
