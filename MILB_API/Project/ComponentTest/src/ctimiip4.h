/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : maoguangkun
*@brief : CtImIip4
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_IIP_4_H__
#define __CT_IM_IIP_4_H__


#include <klib.h>

#include "ctimiip5.h"


#define CT_TYPE_IM_IIP_4                  (ct_im_iip_4_get_type())
#define CT_IM_IIP_4(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImIip4)) 
#define CT_IS_IM_IIP_4(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_IIP_4)) 


typedef struct _CtImIip4 CtImIip4;
typedef struct _CtImIip4Private CtImIip4Private;


struct _CtImIip4 
{
	KObject parent;
};


KConstType 		ct_im_iip_4_get_type(void);
CtImIip4* 			ct_im_iip_4_get(void);

#ifndef CO_CT_IM_IIP_DISABLE
INT32 					CT_Im_IIP_1_1_23( VOID);
INT32 					CT_Im_IIP_1_1_24( VOID);
INT32 					CT_Im_IIP_1_1_25( VOID);

#ifdef CO_CT_IM_IIP_ENABLE_1_1_26
INT32 					CT_Im_IIP_1_1_26( VOID );
#endif //CO_CT_IM_IIP_ENABLE_1_1_26

#ifdef CO_DEBUG_ON_PC
INT32 					CT_Im_IIP_1_1_27( VOID );
#endif //CO_DEBUG_ON_PC
#endif //CO_CT_IM_IIP_DISABLE

#endif /* __CT_IM_IIP_4_H__ */
