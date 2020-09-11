/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro20Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IMPRO_2_0_PRINT_H__
#define __IMPRO_2_0_PRINT_H__


#include <klib.h>
#include "absimproprint.h"


#define IMPRO_TYPE_2_0_PRINT                  (impro_2_0_print_get_type())
#define IMPRO_2_0_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, Impro20Print)) 
#define IMPRO_IS_2_0_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_2_0_PRINT)) 


typedef struct _Impro20Print Impro20Print;
typedef struct _Impro20PrintPrivate Impro20PrintPrivate;

struct _Impro20Print 
{
	AbsImProPrint parent;
};


KConstType 		impro_2_0_print_get_type(void);
Impro20Print* 	impro_2_0_print_new(void);
Impro20Print* 	impro_2_0_print_get(void);

#ifndef CO_CT_IM_PRO_DISABL
void 			im_pro_2_0_print_4(Impro20Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, T_IM_PRO_SROTOP_CTRL* ctrl);
void 			im_pro_2_0_print_5(Impro20Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, kuchar ch, kint32 ercd, 
									T_IM_PRO_SROTOP_WEITGEN_CTRL* ctrl);
void 			im_pro_2_0_print_6(Impro20Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, kuchar ch, 
									kint32 ercd, E_IM_PRO_WEITGEN_ENABLE ctrl);
void 			im_pro_2_0_print_7(Impro20Print *self,E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_AFPB_CH ch);
void 			im_pro_2_0_print_8(Impro20Print *self,E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_AFPB_CH ch, kuchar force);
void 			im_pro_2_0_print_9(Impro20Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_AFPB_CH ch, 
									T_IM_PRO_AFPB_CTRL* afpbCtrl);
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __IMPRO_2_0_PRINT_H__ */
