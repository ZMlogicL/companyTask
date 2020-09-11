/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro33Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IMPRO_3_3_PRINT_H__
#define __IMPRO_3_3_PRINT_H__


#include <klib.h>
#include "absimproprint.h"


#define IMPRO_TYPE_3_3_PRINT                  (impro_3_3_print_get_type())
#define IMPRO_3_3_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, Impro33Print)) 
#define IMPRO_IS_3_3_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_3_3_PRINT)) 


typedef struct _Impro33Print Impro33Print;
typedef struct _Impro33PrintPrivate Impro33PrintPrivate;

struct _Impro33Print 
{
	AbsImProPrint parent;
};


KConstType impro_3_3_print_get_type(void);
Impro33Print* impro_3_3_print_new(void);
Impro33Print* impro_3_3_print_get(void);

#ifndef CO_CT_IM_PRO_DISABL

void 			im_pro_3_3_print_0(Impro33Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo,
						 			kint32 ercd, T_IM_PRO_AREA_INFO* fshdCtrl );
void 			im_pro_3_3_print_1(Impro33Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo,
						 			kint32 ercd, T_IM_PRO_FSHD_BLEND_CTRL* fshdCtrl );
void 			im_pro_3_3_print_2(Impro33Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo,
						 			kint32 ercd, T_IM_PRO_FSHD_FRAME_CTRL* fshdCtrl );
void 			im_pro_3_3_print_3(Impro33Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo,
						 			kint32 ercd, T_IM_PRO_FSHD_CONCENTRIC_CTRL* fshdCtrl );
void 			im_pro_3_3_print_5(Impro33Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kuchar tblSel, 
									kint32 ercd, kint32 cmpErcd );
void 			im_pro_3_3_print_6(Impro33Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo,
						 			kint32 ercd, USHORT fshdCtrl );
void 			im_pro_3_3_print_7(Impro33Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo,
						 			kint32 ercd, const T_IM_PRO_RDMA_FSHD_ADDR** fshdCtrl );
void 			im_pro_3_3_print_8(Impro33Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kuchar tblSel, 
									kint32 ercd, const T_IM_PRO_RDMA_FSHD_CTBL_ADDR** fshdCtrl );
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __IMPRO_3_3_PRINT_H__ */
