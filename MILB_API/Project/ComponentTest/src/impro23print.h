/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro23Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IMPRO_2_3_PRINT_H__
#define __IMPRO_2_3_PRINT_H__


#include <klib.h>
#include "absimproprint.h"


#define IMPRO_TYPE_2_3_PRINT                  (impro_2_3_print_get_type())
#define IMPRO_2_3_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, Impro23Print)) 
#define IMPRO_IS_2_3_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_2_3_PRINT)) 


typedef struct _Impro23Print Impro23Print;
typedef struct _Impro23PrintPrivate Impro23PrintPrivate;

struct _Impro23Print 
{
	AbsImProPrint parent;
};


KConstType impro_2_3_print_get_type(void);
Impro23Print* impro_2_3_print_new(void);
Impro23Print* impro_2_3_print_get(void);

#ifndef CO_CT_IM_PRO_DISABL
void 			im_pro_2_3_print_0(Impro23Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, T_IM_PRO_DPC_AREA* dpcCtrl);
void 			im_pro_2_3_print_1(Impro23Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, 
									T_IM_PRO_DPC_AB_CTRL* dpcCtrl);
void 			im_pro_2_3_print_2(Impro23Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, 
									T_IM_PRO_DPC_DDD_CTRL* dpcCtrl);
void 			im_pro_2_3_print_3(Impro23Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, 
									T_IM_PRO_DPC_MDD_CTRL* dpcCtrl);
void 			im_pro_2_3_print_4(Impro23Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, 
									T_IM_PRO_DPC_MDC_CTRL* dpcCtrl);
void 			im_pro_2_3_print_5(Impro23Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, 
									T_IM_PRO_DPC_ESDC_CTRL* dpcCtrl);
void 			im_pro_2_3_print_6(Impro23Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, 
									T_IM_PRO_DPC_OCD_CTRL* dpcCtrl);
void 			im_pro_2_3_print_7(Impro23Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, 
									const T_IM_PRO_RDMA_DPC_ADDR** dpcCtrl);
void 			im_pro_2_3_print_8(Impro23Print *self,E_IM_PRO_UNIT_NUM unitNo);
void 			im_pro_2_3_print_9(Impro23Print *self,E_IM_PRO_UNIT_NUM unitNo, kuchar force);
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __IMPRO_2_3_PRINT_H__ */
