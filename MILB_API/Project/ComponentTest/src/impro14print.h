/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-04
*@author : 陈阳
*@brief : ImPro14Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IM_PRO_1_4_PRINT_H__
#define __IM_PRO_1_4_PRINT_H__


#include <klib.h>
#include "absimproprint.h"


#define IM_TYPE_PRO_1_4_PRINT                  (im_pro_1_4_print_get_type())
#define IM_PRO_1_4_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, ImPro14Print)) 
#define IM_IS_PRO_1_4_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IM_TYPE_PRO_1_4_PRINT)) 


typedef struct _ImPro14Print ImPro14Print;
typedef struct _ImPro14PrintPrivate ImPro14PrintPrivate;

struct _ImPro14Print 
{
	AbsImProPrint parent;
};


KConstType im_pro_1_4_print_get_type(void);
ImPro14Print* im_pro_1_4_print_new(void);
ImPro14Print* im_pro_1_4_print_get(void);

#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_1_4_print_0(ImPro14Print *self, const char* string, kuchar ch, T_IM_PRO_RGB4* status );
void im_pro_1_4_print_1(ImPro14Print *self, const char* string, kuchar ch );
void im_pro_1_4_print_2(ImPro14Print *self, const char* string, kuchar ch, kuchar force );
void im_pro_1_4_print_3(ImPro14Print *self, const char* string, kuchar ch, T_IM_PRO_OBT_CTRL* obCtrl );
void im_pro_1_4_print_4(ImPro14Print *self, const char* string, kuchar ch, T_IM_PRO_AREA_INFO* obArea );
void im_pro_1_4_print_5(ImPro14Print *self, const char* string, kuchar ch, T_IM_PRO_RGB2* offset );
void im_pro_1_4_print_6(ImPro14Print *self, const char* string, kuchar ch, T_IM_PRO_RGB2* status );
void im_pro_1_4_print_7(ImPro14Print *self, const char* string, kuchar ch, const T_IM_PRO_RDMA_OBT_ADDR** addr );
void im_pro_1_4_print_8(ImPro14Print *self, const char* string, kuchar ch );
void im_pro_1_4_print_9(ImPro14Print *self, const char* string, kuchar ch );
#endif
#endif /* __IM_PRO_1_4_PRINT_H__ */
