/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro60Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IMPRO_6_0_PRINT_H__
#define __IMPRO_6_0_PRINT_H__


#include <klib.h>
#include "absimproprint.h"


#define IMPRO_TYPE_6_0_PRINT                  (impro_6_0_print_get_type())
#define IMPRO_6_0_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, Impro60Print)) 
#define IMPRO_IS_6_0_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_6_0_PRINT)) 


typedef struct _Impro60Print Impro60Print;
typedef struct _Impro60PrintPrivate Impro60PrintPrivate;

struct _Impro60Print 
{
	AbsImProPrint parent;
};


KConstType impro_6_0_print_get_type(void);
Impro60Print* impro_6_0_print_new(void);
Impro60Print* impro_6_0_print_get(void);

#ifndef CO_CT_IM_PRO_DISABL
void im_pro_6_0_print_1(Impro60Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, kint32 ercd );
void im_pro_6_0_print_2(Impro60Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, kint32 ercd, kuchar force );
void im_pro_6_0_print_3(Impro60Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, 
							kuchar ch, kint32 ercd, T_IM_PRO_P2M_CTRL* p2m_ctrl );
void im_pro_6_0_print_4(Impro60Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, kint32 ercd, kuchar paenTrg );
void im_pro_6_0_print_5(Impro60Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, 
							kint32 ercd, kint32 cmpErcd );
void im_pro_6_0_print_6(Impro60Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, kint32 ercd, 
							const T_IM_PRO_RDMA_P2M_KNEE_TBL_ADDR** addr );
void im_pro_6_0_print_7(Impro60Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, kint32 ercd );
void im_pro_6_0_print_8(Impro60Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, kint32 ercd, kuchar force );
void im_pro_6_0_print_9(Impro60Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, 
							kuchar ch, kint32 ercd, T_IM_PRO_PWCH_CTRL* pwchCtrl );
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __IMPRO_6_0_PRINT_H__ */
