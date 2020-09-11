/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-03
*@author : maoguangkun
*@brief : CtImShdrErr
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_SHDR_ERR_H__
#define __CT_IM_SHDR_ERR_H__


#include <klib.h>

#include "ctimshdrset.h"


#define CT_TYPE_IM_SHDR_ERR                  (ct_im_shdr_err_get_type())
#define CT_IM_SHDR_ERR(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImShdrErr)) 
#define CT_IS_IM_SHDR_ERR(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_SHDR_ERR)) 


typedef struct _CtImShdrErr CtImShdrErr;
typedef struct _CtImShdrErrPrivate CtImShdrErrPrivate;


struct _CtImShdrErr 
{
	KObject parent;
};


KConstType 			ct_im_shdr_err_get_type(void);
CtImShdrErr*			ct_im_shdr_err_get(void);

VOID 						ct_im_shdr_err_main(CtImShdrErr* self, INT32 argc, char** argv);

#endif /* __CT_IM_SHDR_ERR_H__ */
