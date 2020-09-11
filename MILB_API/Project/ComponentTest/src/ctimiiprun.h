/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : maoguangkun
*@brief : CtImIipRun
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_IIP_RUN_H__
#define __CT_IM_IIP_RUN_H__


#include <klib.h>

#include "ctimiip8.h"


#define CT_TYPE_IM_IIP_RUN                  (ct_im_iip_run_get_type())
#define CT_IM_IIP_RUN(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImIipRun)) 
#define CT_IS_IM_IIP_RUN(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_IIP_RUN)) 


typedef struct _CtImIipRun CtImIipRun;
typedef struct _CtImIipRunPrivate CtImIipRunPrivate;


struct _CtImIipRun 
{
	KObject parent;
};


KConstType			ct_im_iip_run_get_type(void);
CtImIipRun*		ct_im_iip_run_get(void);

#ifndef CO_CT_IM_IIP_DISABLE
VOID 					CT_Im_IIP_Run(const UINT32 ct_idx_1st, const UINT32 ct_idx_2nd, const UINT32 ct_idx_3rd);

#else //CO_CT_IM_IIP_DISABLE
VOID 					CT_Im_IIP_Run( const UINT32 ct_idx_1st, const UINT32 ct_idx_2nd, const UINT32 ct_idx_3rd );
#endif //CO_CT_IM_IIP_DISABLE

#endif /* __CT_IM_IIP_RUN_H__ */
