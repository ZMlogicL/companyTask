/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro31Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IMPRO_3_1_PRINT_H__
#define __IMPRO_3_1_PRINT_H__


#include <klib.h>
#include "absimproprint.h"


#define IMPRO_TYPE_3_1_PRINT                  (impro_3_1_print_get_type())
#define IMPRO_3_1_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, Impro31Print)) 
#define IMPRO_IS_3_1_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_3_1_PRINT)) 


typedef struct _Impro31Print Impro31Print;
typedef struct _Impro31PrintPrivate Impro31PrintPrivate;

struct _Impro31Print 
{
	AbsImProPrint parent;
};


KConstType impro_3_1_print_get_type(void);
Impro31Print* impro_3_1_print_new(void);
Impro31Print* impro_3_1_print_get(void);

#ifndef CO_CT_IM_PRO_DISABL

void 			im_pro_3_1_print_0(Impro31Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo,
						 			kint32 ercd, T_IM_PRO_ELF_AREA* elfCtrl );
void 			im_pro_3_1_print_1(Impro31Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo,
						 			kint32 ercd, T_IM_PRO_ELF_NOISE_FUNC* elfCtrl );
void 			im_pro_3_1_print_2(Impro31Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo,
						 			kint32 ercd, T_IM_PRO_ELF_LGT_EDG_FUNC* elfCtrl );
void 			im_pro_3_1_print_3(Impro31Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo,
						 			kint32 ercd, T_IM_PRO_ELF_L_E_FUNC* elfCtrl );
void 			im_pro_3_1_print_4(Impro31Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo,
						 			kint32 ercd, T_IM_PRO_ELF_f9_SAMPLING* elfCtrl );
void 			im_pro_3_1_print_5(Impro31Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo,
						 			kint32 ercd, T_IM_PRO_ELF_1s5_SAMPLING* elfCtrl );
void 			im_pro_3_1_print_6(Impro31Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo,
						 			kint32 ercd, T_IM_PRO_ELF_5s9_SAMPLING* elfCtrl );
void 			im_pro_3_1_print_7(Impro31Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo,
						 			kint32 ercd, T_IM_PRO_ELF_Noise_Adj* elfCtrl );
void 			im_pro_3_1_print_8(Impro31Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo,
						 			kint32 ercd, T_IM_PRO_ELF_a0_FILTER* elfCtrl );
void 			im_pro_3_1_print_9(Impro31Print *self, E_IM_PRO_UNIT_NUM unitNo );
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __IMPRO_3_1_PRINT_H__ */
