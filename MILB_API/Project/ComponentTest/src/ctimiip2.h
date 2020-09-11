/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-03
*@author : maoguangkun
*@brief : CtImIip2
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_IIP_2_H__
#define __CT_IM_IIP_2_H__


#include <klib.h>

#include "ctimiip3.h"


#define CT_TYPE_IM_IIP_2                  (ct_im_iip_2_get_type())
#define CT_IM_IIP_2(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImIip2)) 
#define CT_IS_IM_IIP_2(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_IIP_2)) 


typedef struct _CtImIip2 CtImIip2;
typedef struct _CtImIip2Private CtImIip2Private;


struct _CtImIip2 
{
	KObject parent;
};


KConstType 		ct_im_iip_2_get_type(void);
CtImIip2* 			ct_im_iip_2_get(void);

INT32 					CT_Im_IIP_1_1_10( VOID );
INT32 					CT_Im_IIP_1_1_12( VOID );
INT32 					CT_Im_IIP_1_1_13( VOID );
INT32 					CT_Im_IIP_1_1_14( VOID );
INT32 					CT_Im_IIP_1_1_15( VOID );
INT32 					CT_Im_IIP_1_1_16( VOID );

#endif /* __CT_IM_IIP_2_H__ */
