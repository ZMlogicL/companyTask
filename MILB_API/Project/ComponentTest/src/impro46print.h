/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro46Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IMPRO_4_6_PRINT_H__
#define __IMPRO_4_6_PRINT_H__


#include <klib.h>
#include "absimproprint.h"


#define IMPRO_TYPE_4_6_PRINT                  (impro_4_6_print_get_type())
#define IMPRO_4_6_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, Impro46Print)) 
#define IMPRO_IS_4_6_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_4_6_PRINT)) 


typedef struct _Impro46Print Impro46Print;
typedef struct _Impro46PrintPrivate Impro46PrintPrivate;

struct _Impro46Print 
{
	AbsImProPrint parent;
};


KConstType impro_4_6_print_get_type(void);
Impro46Print* impro_4_6_print_new(void);
Impro46Print* impro_4_6_print_get(void);

#ifndef CO_CT_IM_PRO_DISABL
void im_pro_4_6_print_0(Impro46Print *self, const char* string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong* calcData );
void im_pro_4_6_print_1(Impro46Print *self, E_IM_PRO_HIST_CH ch );
void im_pro_4_6_print_2(Impro46Print *self, E_IM_PRO_HIST_CH ch, kuchar force );
void im_pro_4_6_print_3(Impro46Print *self, const char* string, E_IM_PRO_HIST_CH ch, T_IM_PRO_HIST_CTRL* histCtrl );
void im_pro_4_6_print_4(Impro46Print *self, E_IM_PRO_AF_CH ch, kuchar paenTrg );
void im_pro_4_6_print_5(Impro46Print *self, const char* string, E_IM_PRO_AF_CH ch, E_IM_PRO_HIST_CYCLE histCycle );
void im_pro_4_6_print_6(Impro46Print *self, const char* string, E_IM_PRO_AF_CH ch, T_IM_PRO_HIST_AREA* histCtrl );
void im_pro_4_6_print_7(Impro46Print *self, const char* string, E_IM_PRO_AF_CH ch, T_IM_PRO_HIST_GAIN* histCtrl );
void im_pro_4_6_print_8(Impro46Print *self, const char* string, E_IM_PRO_AF_CH ch, T_IM_PRO_STAT_YK* histCtrl );
void im_pro_4_6_print_9(Impro46Print *self, const char* string, E_IM_PRO_AF_CH ch, T_IM_PRO_HIST_DATA* histCtrl );
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __IMPRO_4_6_PRINT_H__ */
