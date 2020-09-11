/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro314Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IMPRO_3_1_4_PRINT_H__
#define __IMPRO_3_1_4_PRINT_H__


#include <klib.h>
#include "absimproprint.h"


#define IMPRO_TYPE_3_1_4_PRINT                  (impro_3_1_4_print_get_type())
#define IMPRO_3_1_4_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, Impro314Print)) 
#define IMPRO_IS_3_1_4_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_3_1_4_PRINT)) 


typedef struct _Impro314Print Impro314Print;
typedef struct _Impro314PrintPrivate Impro314PrintPrivate;

struct _Impro314Print 
{
	AbsImProPrint parent;
};


KConstType impro_3_1_4_print_get_type(void);
Impro314Print* impro_3_1_4_print_new(void);
Impro314Print* impro_3_1_4_print_get(void);

#ifndef CO_CT_IM_PRO_DISABL
void im_pro_3_1_4_Print(Impro314Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, 
                        T_IM_PRO_ELF_f9_SAMPLING* elfCtrl);
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __IMPRO_3_1_4_PRINT_H__ */
