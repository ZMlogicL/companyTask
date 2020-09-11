/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : maoguangkun
*@brief : CtImIip9
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_IIP_9_H__
#define __CT_IM_IIP_9_H__


#include <klib.h>

#include "ctimiiptool.h"


#define CT_TYPE_IM_IIP_9                  (ct_im_iip_9_get_type())
#define CT_IM_IIP_9(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImIip9)) 
#define CT_IS_IM_IIP_9(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_IIP_9)) 


typedef struct _CtImIip9 CtImIip9;
typedef struct _CtImIip9Private CtImIip9Private;


struct _CtImIip9 
{
	KObject parent;
};


KConstType				ct_im_iip_9_get_type(void);
CtImIip9*				ct_im_iip_9_get(void);

#ifndef CO_CT_IM_IIP_DISABLE
INT32 						CT_Im_IIP_1_1_4( VOID );
INT32 						CT_Im_IIP_1_1_5( VOID );
INT32 						CT_Im_IIP_1_1_6( VOID );
INT32 						CT_Im_IIP_1_1_7( VOID );
#endif //CO_CT_IM_IIP_DISABLE

#endif /* __CT_IM_IIP_9_H__ */