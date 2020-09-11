/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro43Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IMPRO_4_3_PRINT_H__
#define __IMPRO_4_3_PRINT_H__


#include <klib.h>
#include "absimproprint.h"


#define IMPRO_TYPE_4_3_PRINT                  (impro_4_3_print_get_type())
#define IMPRO_4_3_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, Impro43Print)) 
#define IMPRO_IS_4_3_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_4_3_PRINT)) 


typedef struct _Impro43Print Impro43Print;
typedef struct _Impro43PrintPrivate Impro43PrintPrivate;

struct _Impro43Print 
{
	AbsImProPrint parent;
};


KConstType impro_4_3_print_get_type(void);
Impro43Print* impro_4_3_print_new(void);
Impro43Print* impro_4_3_print_get(void);

#ifndef CO_CT_IM_PRO_DISABL

void im_pro_4_3_print_0(Impro43Print *self, const char* string, E_IM_PRO_AF_CH ch, T_IM_PRO_AF_VERTICAL_CTRL* afVerticalCtrl );
void im_pro_4_3_print_1(Impro43Print *self, const char* string, E_IM_PRO_AF_CH ch, kuchar           tap_no, 
							T_IM_PRO_AF_HORIZON_CTRL* afCtrl );
void im_pro_4_3_print_2(Impro43Print *self, const char* string, E_IM_PRO_AF_CH ch, 
							E_IM_PRO_AF_WINDOW_NO winNo, T_IM_PRO_AF_WIN_CTRL* afCtrl );
void im_pro_4_3_print_3(Impro43Print *self, const char* string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong* calcData );
void im_pro_4_3_print_4(Impro43Print *self, const char* string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong* calcData );
void im_pro_4_3_print_5(Impro43Print *self, const char* string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong* calcData );
void im_pro_4_3_print_6(Impro43Print *self, const char* string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong* calcData );
void im_pro_4_3_print_7(Impro43Print *self, const char* string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong* calcData );
void im_pro_4_3_print_8(Impro43Print *self, const char* string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong* calcData );
void im_pro_4_3_print_9(Impro43Print *self, const char* string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong* calcData );
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __IMPRO_4_3_PRINT_H__ */
