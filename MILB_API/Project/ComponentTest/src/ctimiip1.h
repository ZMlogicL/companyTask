/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-03
*@author : maoguangkun
*@brief : CtImIip1
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_IIP_1_H__
#define __CT_IM_IIP_1_H__


#include <klib.h>

#include"ctimiip2.h"


#define CT_TYPE_IM_IIP_1                  (ct_im_iip_1_get_type())
#define CT_IM_IIP_1(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImIip1)) 
#define CT_IS_IM_IIP_1(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_IIP_1)) 


typedef struct _CtImIip1 CtImIip1;
typedef struct _CtImIip1Private CtImIip1Private;


struct _CtImIip1 
{
	KObject parent;
};


KConstType			ct_im_iip_1_get_type(void);
CtImIip1*			ct_im_iip_1_get(void);

#ifndef CO_CT_IM_IIP_DISABLE
INT32 					CT_Im_IIP_1_1_2( VOID );
INT32					CT_Im_IIP_1_1_3( VOID );
INT32 					CT_Im_IIP_1_1_4( VOID );
INT32 					CT_Im_IIP_1_1_5( VOID );
INT32 					CT_Im_IIP_1_1_6( VOID );
INT32 					CT_Im_IIP_1_1_7( VOID );
INT32 					CT_Im_IIP_1_1_8( VOID );
INT32 					CT_Im_IIP_1_1_9( VOID );
#endif //CO_CT_IM_IIP_DISABLE

#ifndef CO_CT_IM_IIP_DISABLE
VOID 					ct_im_iip_print_base( VOID );
#endif //CO_CT_IM_IIP_DISABLE

#endif /* __CT_IM_IIP_1_H__ */
