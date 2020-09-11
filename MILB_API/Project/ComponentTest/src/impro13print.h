/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-04
*@author : 陈阳
*@brief : ImPro13Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IM_PRO_1_3_PRINT_H__
#define __IM_PRO_1_3_PRINT_H__


#include <klib.h>
#include "absimproprint.h"


#define IM_TYPE_PRO_1_3_PRINT                  (im_pro_1_3_print_get_type())
#define IM_PRO_1_3_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, ImPro13Print)) 
#define IM_IS_PRO_1_3_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IM_TYPE_PRO_1_3_PRINT)) 


typedef struct _ImPro13Print ImPro13Print;
typedef struct _ImPro13PrintPrivate ImPro13PrintPrivate;

struct _ImPro13Print 
{
	AbsImProPrint parent;
};


KConstType 		im_pro_1_3_print_get_type(void);
ImPro13Print* 	im_pro_1_3_print_new(void);
ImPro13Print* 	im_pro_1_3_print_get(void);
#ifndef CO_CT_IM_PRO_DISABLE
void 			im_pro_1_3_print_0(ImPro13Print *self, const char* string, kuchar ch );
void 			im_pro_1_3_print_1(ImPro13Print *self, const char* string, kuchar ch, kuchar force );
void 			im_pro_1_3_print_2(ImPro13Print *self, const char* string, kuchar ch, TImProLdivCtrl* ldivCtrl );
void 			im_pro_1_3_print_3(ImPro13Print *self, const char* string, kuchar ch, TImProLdivArea* ldivArea );
void 			im_pro_1_3_print_4(ImPro13Print *self, const char* string, kuchar ch, kuchar paenTrg );
void 			im_pro_1_3_print_5(ImPro13Print *self, const char* string, kuchar ch );
void 			im_pro_1_3_print_6(ImPro13Print *self, const char* string, kuchar ch, kuchar force );
void 			im_pro_1_3_print_7(ImPro13Print *self, const char* string, kuchar ch, T_IM_PRO_OBD_CTRL* obCtrl );
void 			im_pro_1_3_print_8(ImPro13Print *self, const char* string, kuchar ch, T_IM_PRO_AREA_INFO* obArea );
void 			im_pro_1_3_print_9(ImPro13Print *self, const char* string, kuchar ch, T_IM_PRO_RGB4* status );
#endif
#endif /* __IM_PRO_1_3_PRINT_H__ */
