/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro24Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IMPRO_2_4_PRINT_H__
#define __IMPRO_2_4_PRINT_H__


#include <klib.h>
#include "absimproprint.h"


#define IMPRO_TYPE_2_4_PRINT                  (impro_2_4_print_get_type())
#define IMPRO_2_4_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, Impro24Print)) 
#define IMPRO_IS_2_4_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_2_4_PRINT)) 


typedef struct _Impro24Print Impro24Print;
typedef struct _Impro24PrintPrivate Impro24PrintPrivate;

struct _Impro24Print 
{
	AbsImProPrint parent;
};


KConstType impro_2_4_print_get_type(void);
Impro24Print* impro_2_4_print_new(void);
Impro24Print* impro_2_4_print_get(void);

#ifndef CO_CT_IM_PRO_DISABL
void 			im_pro_2_4_print_0(Impro24Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, T_IM_PRO_FFC_CTRL* ffcCtrl);
void 			im_pro_2_4_print_1(Impro24Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, 
									T_IM_PRO_FFC_BLEND_CTRL* ffcCtrl);
void 			im_pro_2_4_print_2(Impro24Print *self,E_IM_PRO_UNIT_NUM unitNo, kuchar paenTrg);
void 			im_pro_2_4_print_3(Impro24Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, T_IM_PRO_FFC_AREA* ffcCtrl);
void 			im_pro_2_4_print_4(Impro24Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, USHORT ffcCtrl);
void 			im_pro_2_4_print_5(Impro24Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, 
									const T_IM_PRO_RDMA_FFC_ADDR** ffcCtrl);
void 			im_pro_2_4_print_6(Impro24Print *self,E_IM_PRO_UNIT_NUM unitNo);
void 			im_pro_2_4_print_7(Impro24Print *self,E_IM_PRO_UNIT_NUM unitNo, kuchar force);
void 			im_pro_2_4_print_8(Impro24Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, T_IM_PRO_HRB_CTRL* hrbCtrl);
void 			im_pro_2_4_print_9(Impro24Print *self,E_IM_PRO_UNIT_NUM unitNo, kuchar paenTrg);
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __IMPRO_2_4_PRINT_H__ */
