/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro311Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IMPRO_3_1_1_PRINT_H__
#define __IMPRO_3_1_1_PRINT_H__


#include <klib.h>
#include "absimproprint.h"


#define IMPRO_TYPE_3_1_1_PRINT                  (impro_3_1_1_print_get_type())
#define IMPRO_3_1_1_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, Impro311Print)) 
#define IMPRO_IS_3_1_1_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_3_1_1_PRINT)) 


typedef struct _Impro311Print Impro311Print;
typedef struct _Impro311PrintPrivate Impro311PrintPrivate;

struct _Impro311Print 
{
	AbsImProPrint parent;
};


KConstType impro_3_1_1_print_get_type(void);
Impro311Print* impro_3_1_1_print_new(void);
Impro311Print* impro_3_1_1_print_get(void);

#ifndef CO_CT_IM_PRO_DISABL
void im_pro_3_1_1_Print(Impro311Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, 
                            T_IM_PRO_ELF_NOISE_FUNC* elfCtrl);
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __IMPRO_3_1_1_PRINT_H__ */
