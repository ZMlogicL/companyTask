/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-04
*@author : 陈阳
*@brief : ImPro16Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IM_PRO_1_6_PRINT_H__
#define __IM_PRO_1_6_PRINT_H__


#include <klib.h>
#include "absimproprint.h"


#define IM_TYPE_PRO_1_6_PRINT                  (im_pro_1_6_print_get_type())
#define IM_PRO_1_6_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, ImPro16Print)) 
#define IM_IS_PRO_1_6_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IM_TYPE_PRO_1_6_PRINT)) 


typedef struct _ImPro16Print ImPro16Print;
typedef struct _ImPro16PrintPrivate ImPro16PrintPrivate;

struct _ImPro16Print 
{
	AbsImProPrint parent;
};


KConstType im_pro_1_6_print_get_type(void);
ImPro16Print* im_pro_1_6_print_new(void);
ImPro16Print* im_pro_1_6_print_get(void);

#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_1_6_print_0(ImPro16Print *self, const char* string, kuchar ch, kuchar paen_trg0, kuchar paen_trg1 );
void im_pro_1_6_print_1(ImPro16Print *self, const char* string, kuchar ch, T_IM_PRO_CMIPI_STATUS* status );
void im_pro_1_6_print_2(ImPro16Print *self, const char* string, kuchar ch );
void im_pro_1_6_print_3(ImPro16Print *self, const char* string, kuchar ch );
void im_pro_1_6_print_4(ImPro16Print *self, const char* string, kuchar ch, T_IM_PRO_LVDS_CTRL* lvds_ctrl );
void im_pro_1_6_print_5(ImPro16Print *self, const char* string, kuchar ch, USHORT input_pos, USHORT input_size );
void im_pro_1_6_print_6(ImPro16Print *self, const char* string, kuchar ch, T_IM_PRO_LVDS_PIXEL_ORDER* lvds_order );
void im_pro_1_6_print_7(ImPro16Print *self, const char* string, kuchar ch, T_IM_PRO_LVDS_SYNC_CODE_CTRL* syncCode );
void im_pro_1_6_print_8(ImPro16Print *self, const char* string, kuchar ch, T_IM_PRO_LVDS_SYNC_MASK_CTRL* syncMask );
void im_pro_1_6_print_9(ImPro16Print *self, const char* string, kuchar ch, T_IM_PRO_LVDS_INT_ADDR_CTRL* intAddr );
#endif //CO_CT_IM_PRO_DISABLE

#endif /* __IM_PRO_1_6_PRINT_H__ */
