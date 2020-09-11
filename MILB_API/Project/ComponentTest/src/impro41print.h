/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro41Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IMPRO_4_1_PRINT_H__
#define __IMPRO_4_1_PRINT_H__

#include <klib.h>
#include "ctimprofile.h"
#include "absimproprint.h"


#define IMPRO_TYPE_4_1_PRINT                  (impro_4_1_print_get_type())
#define IMPRO_4_1_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, Impro41Print)) 
#define IMPRO_IS_4_1_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_4_1_PRINT)) 


typedef struct _Impro41Print Impro41Print;
typedef struct _Impro41PrintPrivate Impro41PrintPrivate;

struct _Impro41Print 
{
	AbsImProPrint parent;
};


KConstType impro_4_1_print_get_type(void);
Impro41Print* impro_4_1_print_new(void);
Impro41Print* impro_4_1_print_get(void);

#ifndef CO_CT_IM_PRO_DISABL
void im_pro_4_1_print_4(Impro41Print *self, const char* string, E_IM_PRO_AEAWB_CH ch, T_IM_PRO_AEAWB_CW* aeawbCtrl );
void im_pro_4_1_print_5(Impro41Print *self, const char* string, E_IM_PRO_AEAWB_CH ch, T_IM_PRO_AEAWB_LV_GATE* aeawbCtrl );
void im_pro_4_1_print_6(Impro41Print *self, const char* string, E_IM_PRO_AEAWB_CH ch, T_IM_PRO_AEAWB_MATRIX_LV_GATE* aeawbCtrl );
void im_pro_4_1_print_7(Impro41Print *self, const char* string, E_IM_PRO_AEAWB_CH ch, T_IM_PRO_STAT_YK* aeawbCtrl );
void im_pro_4_1_print_8(Impro41Print *self, const char* string, E_IM_PRO_AEAWB_CH ch, T_IM_PRO_STAT_YK* aeyk );
void im_pro_4_1_print_9(Impro41Print *self, const char* string, E_IM_PRO_AEAWB_CH ch, T_IM_PRO_AEAWB_LINE_INFO* aeawbCtrl );
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __IMPRO_4_1_PRINT_H__ */
