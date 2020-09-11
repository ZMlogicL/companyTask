/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro40Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IMPRO_4_0_PRINT_H__
#define __IMPRO_4_0_PRINT_H__


#include <klib.h>
#include "absimproprint.h"


#define IMPRO_TYPE_4_0_PRINT                  (impro_4_0_print_get_type())
#define IMPRO_4_0_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, Impro40Print)) 
#define IMPRO_IS_4_0_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_4_0_PRINT)) 


typedef struct _Impro40Print Impro40Print;
typedef struct _Impro40PrintPrivate Impro40PrintPrivate;

struct _Impro40Print 
{
	AbsImProPrint parent;
};


KConstType impro_4_0_print_get_type(void);
Impro40Print* impro_4_0_print_new(void);
Impro40Print* impro_4_0_print_get(void);

#ifndef CO_CT_IM_PRO_DISABL
void im_pro_4_0_print_4(Impro40Print *self, const char* string, kint32 ercd, T_IM_PRO_STATTOP_CTRL* ctrl );
void im_pro_4_0_print_5(Impro40Print *self, E_IM_PRO_AEAWB_CH ch );
void im_pro_4_0_print_6(Impro40Print *self, E_IM_PRO_AEAWB_CH ch, kuchar force );
void im_pro_4_0_print_7(Impro40Print *self, const char* string, E_IM_PRO_AEAWB_CH ch, T_IM_PRO_AEAWB_CTRL* aeawbCtrl );
void im_pro_4_0_print_8(Impro40Print *self, E_IM_PRO_AEAWB_CH ch, kuchar paenTrg );
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __IMPRO_4_0_PRINT_H__ */
