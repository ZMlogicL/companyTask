/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : maoguangkun
*@brief : CtImIip7
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_IIP_7_H__
#define __CT_IM_IIP_7_H__


#include <klib.h>

#include "ctimiiprun.h"


#define CT_TYPE_IM_IIP_7                  (ct_im_iip_7_get_type())
#define CT_IM_IIP_7(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImIip7)) 
#define CT_IS_IM_IIP_7(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_IIP_7)) 


typedef struct _CtImIip7 CtImIip7;
typedef struct _CtImIip7Private CtImIip7Private;


struct _CtImIip7 
{
	KObject parent;
};


KConstType 		ct_im_iip_7_get_type(void);
CtImIip7*			ct_im_iip_7_get(void);

#ifndef CO_CT_IM_IIP_DISABLE
INT32 					CT_Im_IIP_2_1_1( VOID);
INT32 					CT_Im_IIP_2_1_2( VOID);
INT32 					CT_Im_IIP_2_1_3( VOID);
INT32 					CT_Im_IIP_2_2_1( VOID);
INT32 					CT_Im_IIP_2_2_2( VOID);
#endif //CO_CT_IM_IIP_DISABLE

#endif /* __CT_IM_IIP_7_H__ */
