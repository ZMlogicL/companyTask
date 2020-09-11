/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro48Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IMPRO_4_8_PRINT_H__
#define __IMPRO_4_8_PRINT_H__


#include <klib.h>
#include "absimproprint.h"


#define IMPRO_TYPE_4_8_PRINT                  (impro_4_8_print_get_type())
#define IMPRO_4_8_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, Impro48Print)) 
#define IMPRO_IS_4_8_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_4_8_PRINT)) 


typedef struct _Impro48Print Impro48Print;
typedef struct _Impro48PrintPrivate Impro48PrintPrivate;

struct _Impro48Print 
{
	AbsImProPrint parent;
};


KConstType impro_4_8_print_get_type(void);
Impro48Print* impro_4_8_print_new(void);
Impro48Print* impro_4_8_print_get(void);

#ifndef CO_CT_IM_PRO_DISABL
void im_pro_4_8_print_0(Impro48Print *self, const char* string, E_IM_PRO_FLCK_CH ch, T_IM_PRO_FLCK_MATRIX_LV_GATE* flckCtrl );
void im_pro_4_8_print_1(Impro48Print *self, const char* string, E_IM_PRO_AF_CH ch, T_IM_PRO_STAT_YK* histCtrl );
void im_pro_4_8_print_2(Impro48Print *self, E_IM_PRO_FLCK_CH ch, kulong flckCtrl );
void im_pro_4_8_print_3(Impro48Print *self, E_IM_PRO_FLCK_CH ch, kulong flckCtrl );
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __IMPRO_4_8_PRINT_H__ */
