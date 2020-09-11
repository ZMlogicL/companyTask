/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro26Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IMPRO_2_6_PRINT_H__
#define __IMPRO_2_6_PRINT_H__


#include <klib.h>
#include "absimproprint.h"


#define IMPRO_TYPE_2_6_PRINT                  (impro_2_6_print_get_type())
#define IMPRO_2_6_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, Impro26Print)) 
#define IMPRO_IS_2_6_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_2_6_PRINT)) 


typedef struct _Impro26Print Impro26Print;
typedef struct _Impro26PrintPrivate Impro26PrintPrivate;

struct _Impro26Print 
{
	AbsImProPrint parent;
};


KConstType impro_2_6_print_get_type(void);
Impro26Print* impro_2_6_print_new(void);
Impro26Print* impro_2_6_print_get(void);

#ifndef CO_CT_IM_PRO_DISABL
void 			im_pro_2_6_print_0(Impro26Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_FFSH_CH ch, kint32 ercd, 
									USHORT ffshCtrl);
void 			im_pro_2_6_print_1(Impro26Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_FFSH_CH ch, kint32 ercd, 
									const T_IM_PRO_RDMA_FFSH_ADDR** ffshCtrl);
void 			im_pro_2_6_print_2(Impro26Print *self,E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_FF_CH ch);
void 			im_pro_2_6_print_3(Impro26Print *self,E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_FF_CH ch, kuchar force);
void 			im_pro_2_6_print_4(Impro26Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_FF_CH ch, kint32 ercd, 
									T_IM_PRO_FF_CTRL* ffCtrl);
void 			im_pro_2_6_print_5(Impro26Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_FF_CH ch, kint32 ercd, 
									T_IM_PRO_AREA_INFO* ffCtrl);
void 			im_pro_2_6_print_6(Impro26Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_FF_CH ch, kint32 ercd, 
									T_IM_PRO_FF_LPF_CTRL* ffCtrl);
void 			im_pro_2_6_print_7(Impro26Print *self,E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch);
void 			im_pro_2_6_print_8(Impro26Print *self,E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch, kuchar force);
void 			im_pro_2_6_print_9(Impro26Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch, kint32 ercd, 
									T_IM_PRO_SDC_CTRL* sdcCtrl);
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __IMPRO_2_6_PRINT_H__ */
