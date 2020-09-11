/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro22Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IMPRO_2_2_PRINT_H__
#define __IMPRO_2_2_PRINT_H__


#include <klib.h>
#include "absimproprint.h"


#define IMPRO_TYPE_2_2_PRINT                  (impro_2_2_print_get_type())
#define IMPRO_2_2_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, Impro22Print)) 
#define IMPRO_IS_2_2_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_2_2_PRINT)) 


typedef struct _Impro22Print Impro22Print;
typedef struct _Impro22PrintPrivate Impro22PrintPrivate;

struct _Impro22Print 
{
	AbsImProPrint parent;
};


KConstType impro_2_2_print_get_type(void);
Impro22Print* impro_2_2_print_new(void);
Impro22Print* impro_2_2_print_get(void);

#ifndef CO_CT_IM_PRO_DISABL
void 			im_pro_2_2_print_0(Impro22Print *self,E_IM_PRO_UNIT_NUM unitNo, kuchar force);
void 			im_pro_2_2_print_1(Impro22Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, 
									T_IM_PRO_CAG_CTRL* cagCtrl);
void 			im_pro_2_2_print_2(Impro22Print *self,E_IM_PRO_UNIT_NUM unitNo, kuchar paenTrg);
void 			im_pro_2_2_print_3(Impro22Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, 
									T_IM_PRO_CAG_AREA* cagCtrl);
void 			im_pro_2_2_print_4(Impro22Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, 
									T_IM_PRO_CAG_CTRL_GLEVEL_DIFF* cagCtrl);
void 			im_pro_2_2_print_5(Impro22Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, 
									const T_IM_PRO_RDMA_CAG_ADDR** cagCtrl);
void 			im_pro_2_2_print_6(Impro22Print *self,E_IM_PRO_UNIT_NUM unitNo);
void 			im_pro_2_2_print_7(Impro22Print *self,E_IM_PRO_UNIT_NUM unitNo, kuchar force);
void 			im_pro_2_2_print_8(Impro22Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, 
									T_IM_PRO_DPC_CTRL* dpcCtrl);
void 			im_pro_2_2_print_9(Impro22Print *self,E_IM_PRO_UNIT_NUM unitNo, kuchar paenTrg);
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __IMPRO_2_2_PRINT_H__ */
