/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-04
*@author : 陈阳
*@brief : ImPro15Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IM_PRO_1_5_PRINT_H__
#define __IM_PRO_1_5_PRINT_H__


#include <klib.h>
#include "absimproprint.h"


#define IM_TYPE_PRO_1_5_PRINT                  (im_pro_1_5_print_get_type())
#define IM_PRO_1_5_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, ImPro15Print)) 
#define IM_IS_PRO_1_5_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IM_TYPE_PRO_1_5_PRINT)) 


typedef struct _ImPro15Print ImPro15Print;
typedef struct _ImPro15PrintPrivate ImPro15PrintPrivate;

struct _ImPro15Print 
{
	AbsImProPrint parent;
};


KConstType im_pro_1_5_print_get_type(void);
ImPro15Print* im_pro_1_5_print_new(void);
ImPro15Print* im_pro_1_5_print_get(void);

#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_1_5_print_0(ImPro15Print *self, const char* string, kuchar ch );
void im_pro_1_5_print_1(ImPro15Print *self, const char* string, kuchar ch, kuchar force );
void im_pro_1_5_print_2(ImPro15Print *self, const char* string, kuchar ch, T_IM_PRO_DMIPI_CTRL* dmipiCtrl );
void im_pro_1_5_print_3(ImPro15Print *self, const char* string, kuchar ch, kuchar paenTrg0, kuchar paenTrg1 );
void im_pro_1_5_print_4(ImPro15Print *self, const char* string, kuchar ch, T_IM_PRO_DMIPI_STATUS* status );
void im_pro_1_5_print_5(ImPro15Print *self, const char* string, kuchar ch );
void im_pro_1_5_print_6(ImPro15Print *self, const char* string, kuchar ch );
void im_pro_1_5_print_7(ImPro15Print *self, const char* string, kuchar ch );
void im_pro_1_5_print_8(ImPro15Print *self, const char* string, kuchar ch, kuchar force );
void im_pro_1_5_print_9(ImPro15Print *self, const char* string, kuchar ch, T_IM_PRO_CMIPI_CTRL* cmipiCtrl );
#endif
#endif /* __IM_PRO_1_5_PRINT_H__ */
