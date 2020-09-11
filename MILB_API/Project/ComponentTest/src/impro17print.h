/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-04
*@author : 陈阳
*@brief : ImPro17Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IM_PRO_1_7_PRINT_H__
#define __IM_PRO_1_7_PRINT_H__


#include <klib.h>
#include "absimproprint.h"


#define IM_TYPE_PRO_1_7_PRINT                  (im_pro_1_7_print_get_type())
#define IM_PRO_1_7_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, ImPro17Print)) 
#define IM_IS_PRO_1_7_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IM_TYPE_PRO_1_7_PRINT)) 


typedef struct _ImPro17Print ImPro17Print;
typedef struct _ImPro17PrintPrivate ImPro17PrintPrivate;

struct _ImPro17Print 
{
	AbsImProPrint parent;
};


KConstType im_pro_1_7_print_get_type(void);
ImPro17Print* im_pro_1_7_print_new(void);
ImPro17Print* im_pro_1_7_print_get(void);

#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_1_7_print_0(ImPro17Print *self, const char* string, kuchar ch, kuchar paenTrg );
void im_pro_1_7_print_1(ImPro17Print *self, const char* string, T_IM_PRO_SENTOP_CPHY_DELAYLINE_MONITOR* status );
void im_pro_1_7_print_2(ImPro17Print *self, const char* string, T_IM_PRO_SENTOP_CPHY_COMMON_IF_MONITOR* status );
#endif //CO_CT_IM_PRO_DISABLE


#endif /* __IM_PRO_1_7_PRINT_H__ */
