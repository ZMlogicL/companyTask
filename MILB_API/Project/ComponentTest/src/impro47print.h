/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro47Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IMPRO_4_7_PRINT_H__
#define __IMPRO_4_7_PRINT_H__


#include <klib.h>
#include "absimproprint.h"


#define IMPRO_TYPE_4_7_PRINT                  (impro_4_7_print_get_type())
#define IMPRO_4_7_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, Impro47Print)) 
#define IMPRO_IS_4_7_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_4_7_PRINT)) 


typedef struct _Impro47Print Impro47Print;
typedef struct _Impro47PrintPrivate Impro47PrintPrivate;

struct _Impro47Print 
{
	AbsImProPrint parent;
};


KConstType impro_4_7_print_get_type(void);
Impro47Print* impro_4_7_print_new(void);
Impro47Print* impro_4_7_print_get(void);

#ifndef CO_CT_IM_PRO_DISABL
void im_pro_4_7_print_0(Impro47Print *self, const char* string, E_IM_PRO_AF_CH ch, T_IM_PRO_HIST_RAM_DATA* histCtrl );
void im_pro_4_7_print_1(Impro47Print *self, E_IM_PRO_FLCK_CH ch );
void im_pro_4_7_print_2(Impro47Print *self, E_IM_PRO_FLCK_CH ch, kuchar force );
void im_pro_4_7_print_3(Impro47Print *self, const char* string, E_IM_PRO_FLCK_CH ch, T_IM_PRO_FLCK_CTRL* flckCtrl );
void im_pro_4_7_print_4(Impro47Print *self, const char* string, E_IM_PRO_FLCK_CH ch, E_IM_PRO_FLCK_TYPE flckCtrl );
void im_pro_4_7_print_5(Impro47Print *self, const char* string, E_IM_PRO_FLCK_CH ch, E_IM_PRO_FLCK_TYPE flckCtrl );
void im_pro_4_7_print_6(Impro47Print *self, const char* string, E_IM_PRO_FLCK_CH ch, T_IM_PRO_FLCK_AREA* flckCtrl );
void im_pro_4_7_print_7(Impro47Print *self, const char* string, E_IM_PRO_FLCK_CH ch, USHORT flckCtrl );
void im_pro_4_7_print_8(Impro47Print *self, const char* string, E_IM_PRO_FLCK_CH ch, USHORT flckCtrl );
void im_pro_4_7_print_9(Impro47Print *self, const char* string, E_IM_PRO_FLCK_CH ch, T_IM_PRO_FLCK_LV_GATE* flckCtrl );
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __IMPRO_4_7_PRINT_H__ */
