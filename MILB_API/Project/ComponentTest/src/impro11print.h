/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-04
*@author : 陈阳
*@brief : ImPro11Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IM_PRO_1_1_PRINT_H__
#define __IM_PRO_1_1_PRINT_H__


#include <klib.h>
#include "absimproprint.h"


#define IM_TYPE_PRO_1_1_PRINT                  (im_pro_1_1_print_getType())
#define IM_PRO_1_1_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, ImPro11Print)) 
#define IM_IS_PRO_1_1_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IM_TYPE_PRO_1_1_PRINT)) 


typedef struct _ImPro11Print ImPro11Print;
typedef struct _ImPro11PrintPrivate ImPro11PrintPrivate;

struct _ImPro11Print 
{
	AbsImProPrint parent;
};


KConstType 		im_pro_1_1_print_getType(void);
ImPro11Print* 	im_pro_1_1_print_new(void);
ImPro11Print* 	im_pro_1_1_print_get(void);

#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_1_1_print_0(ImPro11Print *self, const char* string, T_IM_PRO_SENTOP_SG_CTRL* sentopCtrl );
void im_pro_1_1_print_1(ImPro11Print *self, const char* string, T_IM_PRO_SENTOP_CPHY_CTRL* cphyCtrl );
void im_pro_1_1_print_2(ImPro11Print *self, const char* string, T_IM_PRO_SENTOP_CPHY_DESKNEW_MONITOR* cphyMoni );
void im_pro_1_1_print_3(ImPro11Print *self, const char* string );
void im_pro_1_1_print_4(ImPro11Print *self, const char* string, kuchar force );
void im_pro_1_1_print_5(ImPro11Print *self, const char* string, E_IM_PRO_SG_CH ch, TImProSgCtrl* sgCtrl );
void im_pro_1_1_print_6(ImPro11Print *self, const char* string, E_IM_PRO_SG_CH ch, TImProSgCtrl* sgCtrl );
void im_pro_1_1_print_7(ImPro11Print *self, const char* string, E_IM_PRO_SG_CH ch, T_IM_PRO_SG_MONI_INFO* sgMoniInfo );
void im_pro_1_1_print_8(ImPro11Print *self, const char* string, E_IM_PRO_SLVS_STREAM_TYPE streamType );
void im_pro_1_1_print_9(ImPro11Print *self, const char* string, E_IM_PRO_SLVS_STREAM_TYPE streamType );
#endif

#endif /* __IM_PRO_1_1_PRINT_H__ */
