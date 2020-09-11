/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro45Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IMPRO_4_5_PRINT_H__
#define __IMPRO_4_5_PRINT_H__


#include <klib.h>
#include "absimproprint.h"


#define IMPRO_TYPE_4_5_PRINT                  (impro_4_5_print_get_type())
#define IMPRO_4_5_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, Impro45Print)) 
#define IMPRO_IS_4_5_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_4_5_PRINT)) 


typedef struct _Impro45Print Impro45Print;
typedef struct _Impro45PrintPrivate Impro45PrintPrivate;

struct _Impro45Print 
{
	AbsImProPrint parent;
};


KConstType impro_4_5_print_get_type(void);
Impro45Print* impro_4_5_print_new(void);
Impro45Print* impro_4_5_print_get(void);

#ifndef CO_CT_IM_PRO_DISABL
void im_pro_4_5_print_0(Impro45Print *self, const char* string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong* calcData );
void im_pro_4_5_print_1(Impro45Print *self, const char* string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong* calcData );
void im_pro_4_5_print_2(Impro45Print *self, const char* string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong* calcData );
void im_pro_4_5_print_3(Impro45Print *self, const char* string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong* calcData );
void im_pro_4_5_print_4(Impro45Print *self, const char* string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong* calcData );
void im_pro_4_5_print_5(Impro45Print *self, const char* string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong* calcData );
void im_pro_4_5_print_6(Impro45Print *self, const char* string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong* calcData );
void im_pro_4_5_print_7(Impro45Print *self, const char* string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong* calcData );
void im_pro_4_5_print_8(Impro45Print *self, const char* string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong* calcData );
void im_pro_4_5_print_9(Impro45Print *self, const char* string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong* calcData );
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __IMPRO_4_5_PRINT_H__ */
