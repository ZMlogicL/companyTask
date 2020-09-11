/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro42Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IMPRO_4_2_PRINT_H__
#define __IMPRO_4_2_PRINT_H__


#include <klib.h>
#include "absimproprint.h"


#define IMPRO_TYPE_4_2_PRINT                  (impro_4_2_print_get_type())
#define IMPRO_4_2_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, Impro42Print)) 
#define IMPRO_IS_4_2_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_4_2_PRINT)) 


typedef struct _Impro42Print Impro42Print;
typedef struct _Impro42PrintPrivate Impro42PrintPrivate;

struct _Impro42Print 
{
	AbsImProPrint parent;
};


KConstType impro_4_2_print_get_type(void);
Impro42Print* impro_4_2_print_new(void);
Impro42Print* impro_4_2_print_get(void);

#ifndef CO_CT_IM_PRO_DISABL
void im_pro_4_2_print_0(Impro42Print *self, const char* string, E_IM_PRO_AEAWB_CH ch, kulong* lineData );
void im_pro_4_2_print_1(Impro42Print *self, const char* string, E_IM_PRO_AEAWB_CH ch, kulong* dataAddress );
void im_pro_4_2_print_2(Impro42Print *self, const char* string, E_IM_PRO_AEAWB_CH ch, kulong* dataAddress );
void im_pro_4_2_print_3(Impro42Print *self, const char* string, E_IM_PRO_AEAWB_CH ch, T_IM_PRO_AEAWB_WD_INFO* wdInfo );
void im_pro_4_2_print_4(Impro42Print *self, E_IM_PRO_AF_CH ch );
void im_pro_4_2_print_5(Impro42Print *self, E_IM_PRO_AF_CH ch, kuchar force );
void im_pro_4_2_print_6(Impro42Print *self, const char* string, E_IM_PRO_AF_CH ch, T_IM_PRO_AF_CTRL* afCtrl );
void im_pro_4_2_print_7(Impro42Print *self, E_IM_PRO_AF_CH ch, kuchar paenTrg );
void im_pro_4_2_print_8(Impro42Print *self, const char* string, E_IM_PRO_AF_CH ch, T_IM_PRO_AREA_INFO* globalWin );
void im_pro_4_2_print_9(Impro42Print *self, const char* string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_EVAL_CALC_UNIT unitNo, T_IM_PRO_AF_EVAL_CALC_CTRL* afEvalCalcCtrl );
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __IMPRO_4_2_PRINT_H__ */
