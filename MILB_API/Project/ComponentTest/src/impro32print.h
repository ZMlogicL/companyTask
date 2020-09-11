/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro32Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IMPRO_3_2_PRINT_H__
#define __IMPRO_3_2_PRINT_H__


#include <klib.h>
#include "absimproprint.h"


#define IMPRO_TYPE_3_2_PRINT                  (impro_3_2_print_get_type())
#define IMPRO_3_2_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, Impro32Print)) 
#define IMPRO_IS_3_2_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_3_2_PRINT)) 


typedef struct _Impro32Print Impro32Print;
typedef struct _Impro32PrintPrivate Impro32PrintPrivate;

struct _Impro32Print 
{
	AbsImProPrint parent;
};


KConstType impro_3_2_print_get_type(void);
Impro32Print* impro_3_2_print_new(void);
Impro32Print* impro_3_2_print_get(void);

#ifndef CO_CT_IM_PRO_DISABL
void 			im_pro_3_2_print_0(Impro32Print *self, E_IM_PRO_UNIT_NUM unitNo, kuchar force );
void 			im_pro_3_2_print_1(Impro32Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo,
						 			kint32 ercd, T_IM_PRO_NSL_CTRL* elfCtrl );
void 			im_pro_3_2_print_2(Impro32Print *self, E_IM_PRO_UNIT_NUM unitNo, kuchar paenTrg );
void 			im_pro_3_2_print_3(Impro32Print *self, E_IM_PRO_UNIT_NUM unitNo, kuchar paenTrg );
void 			im_pro_3_2_print_4(Impro32Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo,
						 			kint32 ercd, const T_IM_PRO_RDMA_ELF_ADDR** elfCtrl );
void 			im_pro_3_2_print_5(Impro32Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo,
						 			kint32 ercd, T_IM_PRO_ELF_HIGH_FREQ_AREA_EDGE_ADJ* elfCtrl );
void 			im_pro_3_2_print_6(Impro32Print *self, E_IM_PRO_UNIT_NUM unitNo );
void 			im_pro_3_2_print_7(Impro32Print *self, E_IM_PRO_UNIT_NUM unitNo, kuchar force );
void 			im_pro_3_2_print_8(Impro32Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo,
						 			kint32 ercd, T_IM_PRO_FSHD_COMMON_CTRL* fshdCtrl );
void 			im_pro_3_2_print_9(Impro32Print *self, E_IM_PRO_UNIT_NUM unitNo, kuchar paenTrg );
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __IMPRO_3_2_PRINT_H__ */
