/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : maoguangkun
*@brief : CtImIip5
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_IIP_5_H__
#define __CT_IM_IIP_5_H__


#include <klib.h>

#include "ctimiip6.h"


#define CT_TYPE_IM_IIP_5                  (ct_im_iip_5_get_type())
#define CT_IM_IIP_5(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImIip5)) 
#define CT_IS_IM_IIP_5(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_IIP_5)) 


typedef struct _CtImIip5 CtImIip5;
typedef struct _CtImIip5Private CtImIip5Private;


struct _CtImIip5 
{
	KObject parent;
};


KConstType 		ct_im_iip_5_get_type(void);
CtImIip5* 			ct_im_iip_5_get(void);

#ifndef CO_CT_IM_IIP_DISABLE
#ifdef CO_DEBUG_ON_PC
INT32 					CT_Im_IIP_1_1_28( VOID );
#endif //CO_DEBUG_ON_PC

#ifdef CO_DEBUG_ON_PC
INT32 					CT_Im_IIP_1_1_29( VOID );
#endif //CO_DEBUG_ON_PC

#ifdef CO_DEBUG_ON_PC
INT32 					CT_Im_IIP_1_1_30( VOID );
#endif //CO_DEBUG_ON_PC

#ifdef CO_DEBUG_ON_PC
INT32 					CT_Im_IIP_1_1_31( VOID );
#endif //CO_DEBUG_ON_PC

#ifdef CO_DEBUG_ON_PC
INT32 					CT_Im_IIP_1_1_32( VOID );
#endif //CO_DEBUG_ON_PC

#ifdef CO_DEBUG_ON_PC
INT32 					CT_Im_IIP_1_1_33( VOID );
#endif //CO_DEBUG_ON_PC

INT32 					CT_Im_IIP_1_1_35( VOID);
INT32 					CT_Im_IIP_1_1_36( VOID);

#ifdef CO_DEBUG_ON_PC
INT32 					CT_Im_IIP_1_1_37( VOID );
#endif //CO_DEBUG_ON_PC

#ifdef CO_DEBUG_ON_PC
INT32 					CT_Im_IIP_1_1_38( VOID );
#endif //CO_DEBUG_ON_PC
#endif //CO_CT_IM_IIP_DISABLE

#endif /* __CT_IM_IIP_5_H__ */
