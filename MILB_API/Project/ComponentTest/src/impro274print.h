/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro274Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IMPRO_2_7_4_PRINT_H__
#define __IMPRO_2_7_4_PRINT_H__


#include <klib.h>
#include "absimproprint.h"


#define IMPRO_TYPE_2_7_4_PRINT                  (impro_2_7_4_print_get_type())
#define IMPRO_2_7_4_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, Impro274Print)) 
#define IMPRO_IS_2_7_4_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_2_7_4_PRINT)) 


typedef struct _Impro274Print Impro274Print;
typedef struct _Impro274PrintPrivate Impro274PrintPrivate;

struct _Impro274Print 
{
	AbsImProPrint parent;
};


KConstType impro_2_7_4_print_get_type(void);
Impro274Print* impro_2_7_4_print_new(void);
Impro274Print* impro_2_7_4_print_get(void);

#ifndef CO_CT_IM_PRO_DISABL
void im_pro_2_7_4_Print(Impro274Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch, 
kint32 ercd, const T_IM_PRO_RDMA_SDC_ADDR** sdcCtrl);
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __IMPRO_2_7_4_PRINT_H__ */
