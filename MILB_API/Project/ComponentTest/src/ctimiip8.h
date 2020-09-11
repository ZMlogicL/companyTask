/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : maoguangkun
*@brief : CtImIip8
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_IIP_8_H__
#define __CT_IM_IIP_8_H__


#include <klib.h>

#include "ctimiip9.h"


#define CT_TYPE_IM_IIP_8                  (ct_im_iip_8_get_type())
#define CT_IM_IIP_8(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImIip8)) 
#define CT_IS_IM_IIP_8(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_IIP_8)) 


typedef struct _CtImIip8 CtImIip8;
typedef struct _CtImIip8Private CtImIip8Private;


struct _CtImIip8 
{
	KObject parent;
};


KConstType 		ct_im_iip_8_get_type(void);
CtImIip8* 			ct_im_iip_8_get(void);

#ifndef CO_CT_IM_IIP_DISABLE
INT32 					CT_Im_IIP_2_4_1( VOID);
INT32 					CT_Im_IIP_2_6_1( VOID);
INT32 					CT_Im_IIP_2_7_1( VOID);
VOID 					CT_Im_IIP_Main(INT32 argc, CHAR** argv);

#else //CO_CT_IM_IIP_DISABLE
VOID 					CT_Im_IIP_Main( INT32 argc, CHAR** argv )
#endif //CO_CT_IM_IIP_DISABLE

#endif /* __CT_IM_IIP_8_H__ */
