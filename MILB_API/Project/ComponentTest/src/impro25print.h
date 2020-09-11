/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro25Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IMPRO_2_5_PRINT_H__
#define __IMPRO_2_5_PRINT_H__


#include <klib.h>
#include "absimproprint.h"


#define IMPRO_TYPE_2_5_PRINT                  (impro_2_5_print_get_type())
#define IMPRO_2_5_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, Impro25Print)) 
#define IMPRO_IS_2_5_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_2_5_PRINT)) 


typedef struct _Impro25Print Impro25Print;
typedef struct _Impro25PrintPrivate Impro25PrintPrivate;

struct _Impro25Print 
{
	AbsImProPrint parent;
};


KConstType impro_2_5_print_get_type(void);
Impro25Print* impro_2_5_print_new(void);
Impro25Print* impro_2_5_print_get(void);

#ifndef CO_CT_IM_PRO_DISABL

void 			im_pro_2_5_print_0(Impro25Print *self,E_IM_PRO_UNIT_NUM unitNo);
void 			im_pro_2_5_print_1(Impro25Print *self,E_IM_PRO_UNIT_NUM unitNo, kuchar force);
void 			im_pro_2_5_print_2(Impro25Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, T_IM_PRO_VRB_CTRL* vrbCtrl);
void 			im_pro_2_5_print_3(Impro25Print *self,E_IM_PRO_UNIT_NUM unitNo, kuchar paenTrg);
void 			im_pro_2_5_print_4(Impro25Print *self,E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_FFSH_CH ch);
void 			im_pro_2_5_print_5(Impro25Print *self,E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_FFSH_CH ch, kuchar force);
void 			im_pro_2_5_print_6(Impro25Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_FFSH_CH ch, kint32 ercd, 
									T_IM_PRO_FFSH_CTRL* ffshCtrl);
void 			im_pro_2_5_print_7(Impro25Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_FFSH_CH ch, kint32 ercd, 
									T_IM_PRO_FFSH_BLEND_CTRL* ffshCtrl);
void 			im_pro_2_5_print_8(Impro25Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_FFSH_CH ch, kint32 ercd, 
									T_IM_PRO_FFSH_AREA* ffshCtrl);
void 			im_pro_2_5_print_9(Impro25Print *self,E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_FFSH_CH ch, kint32 ercd, kuchar paenTrg);
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __IMPRO_2_5_PRINT_H__ */
