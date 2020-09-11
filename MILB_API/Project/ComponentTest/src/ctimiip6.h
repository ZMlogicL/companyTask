/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : maoguangkun
*@brief : CtImIip6
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_IIP_6_H__
#define __CT_IM_IIP_6_H__


#include <klib.h>

#include "ctimiip7.h"


#define CT_TYPE_IM_IIP_6                  (ct_im_iip_6_get_type())
#define CT_IM_IIP_6(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImIip6)) 
#define CT_IS_IM_IIP_6(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_IIP_6)) 


typedef struct _CtImIip6 CtImIip6;
typedef struct _CtImIip6Private CtImIip6Private;


struct _CtImIip6 
{
	KObject parent;
};


KConstType 		ct_im_iip_6_get_type(void);
CtImIip6* 			ct_im_iip_6_get(void);

#ifndef CO_CT_IM_IIP_DISABLE
INT32 					CT_Im_IIP_1_1_40( VOID);
INT32 					CT_Im_IIP_1_1_41( VOID);
INT32 					CT_Im_IIP_1_1_42( VOID);
INT32 					CT_Im_IIP_1_1_43( VOID);
INT32 					CT_Im_IIP_1_1_44( VOID);
INT32 					CT_Im_IIP_1_1_45( VOID);
#endif //CO_CT_IM_IIP_DISABLE

#endif /* __CT_IM_IIP_6_H__ */
