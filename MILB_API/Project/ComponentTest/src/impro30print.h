/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro30Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IMPRO_3_0_PRINT_H__
#define __IMPRO_3_0_PRINT_H__


#include <klib.h>
#include "absimproprint.h"


#define IMPRO_TYPE_3_0_PRINT                  (impro_3_0_print_get_type())
#define IMPRO_3_0_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, Impro30Print)) 
#define IMPRO_IS_3_0_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_3_0_PRINT)) 


typedef struct _Impro30Print Impro30Print;
typedef struct _Impro30PrintPrivate Impro30PrintPrivate;

struct _Impro30Print 
{
	AbsImProPrint parent;
};


KConstType impro_3_0_print_get_type(void);
Impro30Print* impro_3_0_print_new(void);
Impro30Print* impro_3_0_print_get(void);
#ifndef CO_CT_IM_PRO_DISABL
void 			im_pro_3_0_print_4(Impro30Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo,
						 			kint32 ercd, T_IM_PRO_B2BTOP_CTRL* b2btopCtrl );
void 			im_pro_3_0_print_5(Impro30Print *self, E_IM_PRO_UNIT_NUM unitNo );
void 			im_pro_3_0_print_6(Impro30Print *self, E_IM_PRO_UNIT_NUM unitNo, kuchar force );
void 			im_pro_3_0_print_7(Impro30Print *self, E_IM_PRO_UNIT_NUM unitNo, kuchar paenTrg );
void 			im_pro_3_0_print_8(Impro30Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo,
						 			kint32 ercd, T_IM_PRO_ELF_COMMON_CTRL* elfCtrl );
void 			im_pro_3_0_print_9(Impro30Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo,
						 			kint32 ercd, T_IM_PRO_ELF_CTRL* elfCtrl );
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __IMPRO_3_0_PRINT_H__ */
