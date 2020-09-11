/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-03
*@author : maoguangkun
*@brief : CtImIip3
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_IIP_3_H__
#define __CT_IM_IIP_3_H__


#include <klib.h>

#include "ctimiip4.h"


#define CT_TYPE_IM_IIP_3                  (ct_im_iip_3_get_type())
#define CT_IM_IIP_3(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImIip3)) 
#define CT_IS_IM_IIP_3(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_IIP_3)) 


typedef struct _CtImIip3 CtImIip3;
typedef struct _CtImIip3Private CtImIip3Private;


struct _CtImIip3 
{
	KObject parent;
};


KConstType 		ct_im_iip_3_get_type(void);
CtImIip3* 			ct_im_iip_3_get(void);

#ifndef CO_CT_IM_IIP_DISABLE
INT32 					CT_Im_IIP_1_1_17( VOID);
INT32 					CT_Im_IIP_1_1_19( VOID);
INT32 					CT_Im_IIP_1_1_20( VOID);
INT32 					CT_Im_IIP_1_1_21( VOID);
INT32 					CT_Im_IIP_1_1_22( VOID);
#endif //CO_CT_IM_IIP_DISABLE

#endif /* __CT_IM_IIP_3_H__ */
