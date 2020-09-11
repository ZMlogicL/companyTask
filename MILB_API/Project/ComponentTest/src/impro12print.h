/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-04
*@author : 陈阳
*@brief : ImPro12Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IM_PRO_1_2_PRINT_H__
#define __IM_PRO_1_2_PRINT_H__


#include <klib.h>
#include "absimproprint.h"


#define IM_TYPE_PRO_1_2_PRINT                  (im_pro_1_2_print_get_type())
#define IM_PRO_1_2_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, ImPro12Print)) 
#define IM_IS_PRO_1_2_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IM_TYPE_PRO_1_2_PRINT)) 


typedef struct _ImPro12Print ImPro12Print;
typedef struct _ImPro12PrintPrivate ImPro12PrintPrivate;

struct _ImPro12Print 
{
	AbsImProPrint parent;
};


KConstType im_pro_1_2_print_get_type(void);
ImPro12Print* im_pro_1_2_print_new(void);
ImPro12Print* im_pro_1_2_print_get(void);

#ifndef CO_CT_IM_PRO_DISABL
void im_pro_1_2_print_0(ImPro12Print *self, const char* string, T_IM_PRO_SLVS_PMA_INIT* pma_init );
void im_pro_1_2_print_1(ImPro12Print *self, const char* string, T_IM_PRO_SLVS_PMA_PD* pma_pd );
void im_pro_1_2_print_2(ImPro12Print *self, const char* string, T_IM_PRO_SLVS_COMMON_CFG* common_cfg );
void im_pro_1_2_print_3(ImPro12Print *self, const char* string, E_IM_PRO_SLVS_STREAM_TYPE stream_type, T_IM_PRO_SLVS_CTRL* slvs_ctrl );
void im_pro_1_2_print_4(ImPro12Print *self, const char* string, E_IM_PRO_SLVS_STREAM_TYPE stream_type, T_IM_PRO_SLVS_MODE_CFG* mode_ctrl );
void im_pro_1_2_print_5(ImPro12Print *self, const char* string, E_IM_PRO_SLVS_STREAM_TYPE stream_type, T_IM_PRO_SLVS_TRIM_CFG* trim_ctrl );
void im_pro_1_2_print_6(ImPro12Print *self, const char* string, E_IM_PRO_SLVS_STREAM_TYPE stream_type, T_IM_PRO_SLVS_STATUS* status );
void im_pro_1_2_print_7(ImPro12Print *self, const char* string, E_IM_PRO_SLVS_STREAM_TYPE stream_type );
void im_pro_1_2_print_8(ImPro12Print *self, const char* string, E_IM_PRO_SLVS_STREAM_TYPE stream_type, kuchar force );
#endif

#endif /* __IM_PRO_1_2_PRINT_H__ */
