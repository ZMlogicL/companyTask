/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro21Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IMPRO_2_1_PRINT_H__
#define __IMPRO_2_1_PRINT_H__


#include <klib.h>
#include "absimproprint.h"


#define IMPRO_TYPE_2_1_PRINT                  (impro_2_1_print_get_type())
#define IMPRO_2_1_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, Impro21Print)) 
#define IMPRO_IS_2_1_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_2_1_PRINT)) 


typedef struct _Impro21Print Impro21Print;
typedef struct _Impro21PrintPrivate Impro21PrintPrivate;

struct _Impro21Print 
{
	AbsImProPrint parent;
};


KConstType impro_2_1_print_get_type(void);
Impro21Print* impro_2_1_print_new(void);
Impro21Print* impro_2_1_print_get(void);

#ifndef CO_CT_IM_PRO_DISABL

void 			im_pro_2_1_print_0(Impro21Print *self,E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_FSHDL_CH ch);
void 			im_pro_2_1_print_1(Impro21Print *self,E_IM_PRO_UNIT_NUM unitNo, 
									E_IM_PRO_FSHDL_CH ch, kuchar force);
void 			im_pro_2_1_print_2(Impro21Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, 
									E_IM_PRO_FSHDL_CH ch, kint32 ercd, T_IM_PRO_FSHDL_COMMON_CTRL* fshdlCtrl);
void 			im_pro_2_1_print_3(Impro21Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, 
									E_IM_PRO_FSHDL_CH ch, kint32 ercd, T_IM_PRO_FSHDL_BLEND_CTRL* fshdlCtrl);
void 			im_pro_2_1_print_4(Impro21Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, 
									E_IM_PRO_FSHDL_CH ch, kint32 ercd, kuchar fshdlCtrl);
void 			im_pro_2_1_print_5(Impro21Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, 
									E_IM_PRO_FSHDL_CH ch, kint32 ercd, T_IM_PRO_AREA_INFO* fshdlCtrl);
void 			im_pro_2_1_print_6(Impro21Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, 
									E_IM_PRO_FSHDL_CH ch, kint32 ercd, T_IM_PRO_FSHDL_FRAME_CTRL* fshdlCtrl);
void 			im_pro_2_1_print_7(Impro21Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, 
									E_IM_PRO_FSHDL_CH ch, kint32 ercd, USHORT fshdlCtrl);
void 			im_pro_2_1_print_8(Impro21Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, 
									E_IM_PRO_FSHDL_CH ch, kint32 ercd,  const T_IM_PRO_RDMA_FSHDL_ADDR** fshdlCtrl);
void 			im_pro_2_1_print_9(Impro21Print *self,E_IM_PRO_UNIT_NUM unitNo);
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __IMPRO_2_1_PRINT_H__ */
