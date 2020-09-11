/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro44Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IMPRO_4_4_PRINT_H__
#define __IMPRO_4_4_PRINT_H__


#include <klib.h>
#include "absimproprint.h"


#define IMPRO_TYPE_4_4_PRINT                  (impro_4_4_print_get_type())
#define IMPRO_4_4_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, Impro44Print)) 
#define IMPRO_IS_4_4_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_4_4_PRINT)) 


typedef struct _Impro44Print Impro44Print;
typedef struct _Impro44PrintPrivate Impro44PrintPrivate;

struct _Impro44Print 
{
	AbsImProPrint parent;
};


KConstType impro_4_4_print_get_type(void);
Impro44Print* impro_4_4_print_new(void);
Impro44Print* impro_4_4_print_get(void);

#ifndef CO_CT_IM_PRO_DISABL
void im_pro_4_4_print_0(Impro44Print *self, const char* string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong* calcData );
void im_pro_4_4_print_1(Impro44Print *self, const char* string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong* calcData );
void im_pro_4_4_print_2(Impro44Print *self, const char* string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong* calcData );
void im_pro_4_4_print_3(Impro44Print *self, const char* string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong* calcData );
void im_pro_4_4_print_4(Impro44Print *self, const char* string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong* calcData );
void im_pro_4_4_print_5(Impro44Print *self, const char* string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong* calcData );
void im_pro_4_4_print_6(Impro44Print *self, const char* string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong* calcData );
void im_pro_4_4_print_7(Impro44Print *self, const char* string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong* calcData );
void im_pro_4_4_print_8(Impro44Print *self, const char* string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong* calcData );
void im_pro_4_4_print_9(Impro44Print *self, const char* string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong* calcData );
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __IMPRO_4_4_PRINT_H__ */
