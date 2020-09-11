/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-04
*@author : 陈阳
*@brief : ImPro10Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IM_PRO_1_0_PRINT_H__
#define __IM_PRO_1_0_PRINT_H__


#include <klib.h>
#include "absimproprint.h"


#define IM_TYPE_PRO_1_0_PRINT                  (im_pro_1_0_print_get_type())
#define IM_PRO_1_0_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, ImPro10Print)) 
#define IM_IS_PRO_1_0_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IM_TYPE_PRO_1_0_PRINT)) 


typedef struct _ImPro10Print ImPro10Print;
typedef struct _ImPro10PrintPrivate ImPro10PrintPrivate;

struct _ImPro10Print 
{
	AbsImProPrint parent;
};


KConstType im_pro_1_0_print_get_type(void);
ImPro10Print* im_pro_1_0_print_new(void);
ImPro10Print* im_pro_1_0_print_get(void);
#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_1_0_print_4(ImPro10Print *self, const char* string, TImProSentopCtrl* sentopCtrl );
void im_pro_1_0_print_5(ImPro10Print *self, const char* string, TImProSentopBsCtrl* sentopCtrl );
void im_pro_1_0_print_6(ImPro10Print *self, const char* string, TImProSentopObtCtrl* sentopCtrl );
void im_pro_1_0_print_7(ImPro10Print *self, const char* string, TImProSentopObtWeightCoeff* sentopCtrl );
void im_pro_1_0_print_8(ImPro10Print *self, const char* string, T_IM_PRO_SENTOP_LVDS_CTRL* sentopCtrl );
void im_pro_1_0_print_9(ImPro10Print *self, const char* string, T_IM_PRO_SENTOP_SLVS_CTRL* sentopCtrl );
#endif

#endif /* __IM_PRO_1_0_PRINT_H__ */
