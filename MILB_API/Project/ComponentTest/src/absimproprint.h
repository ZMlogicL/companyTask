/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-11
*@author : 陈阳
*@brief : AbsImProPrint
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __ABS_IM_PRO_PRINT_H__
#define __ABS_IM_PRO_PRINT_H__


#include <klib.h>
#include "ctimprofile.h"


#define ABS_TYPE_IM_PRO_PRINT                  (abs_im_pro_print_get_type())
#define ABS_IM_PRO_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, AbsImProPrint)) 
#define ABS_IS_IM_PRO_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, ABS_TYPE_IM_PRO_PRINT)) 


typedef struct _AbsImProPrint AbsImProPrint;
typedef struct _AbsImProPrintPrivate AbsImProPrintPrivate;

struct _AbsImProPrint 
{
	KObject parent;
	volatile struct IoPro*		ioPro;
};


KConstType abs_im_pro_print_get_type(void);
AbsImProPrint* abs_im_pro_print_new(void);
AbsImProPrint* abs_im_pro_print_get(void);

#ifndef CO_CT_IM_PRO_DISABL
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __ABS_IM_PRO_PRINT_H__ */
