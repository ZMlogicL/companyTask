/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro63Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IMPRO_6_3_PRINT_H__
#define __IMPRO_6_3_PRINT_H__


#include <klib.h>
#include "absimproprint.h"


#define IMPRO_TYPE_6_3_PRINT                  (impro_6_3_print_get_type())
#define IMPRO_6_3_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, Impro63Print)) 
#define IMPRO_IS_6_3_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_6_3_PRINT)) 


typedef struct _Impro63Print Impro63Print;
typedef struct _Impro63PrintPrivate Impro63PrintPrivate;

struct _Impro63Print 
{
	AbsImProPrint parent;
};


KConstType impro_6_3_print_get_type(void);
Impro63Print* impro_6_3_print_new(void);
Impro63Print* impro_6_3_print_get(void);

#ifndef CO_CT_IM_PRO_DISABL

void im_pro_6_3_print_0(Impro63Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kint32 ercd, T_IM_PRO_PG_CTRL* pg_ctrl );
void im_pro_6_3_print_1(Impro63Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, kint32 ercd );
void im_pro_6_3_print_2(Impro63Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, kint32 ercd, kuchar force );
void im_pro_6_3_print_3(Impro63Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, kint32 ercd, T_IM_PRO_MONI_CTRL* moni_ctrl );
void im_pro_6_3_print_4(Impro63Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, kint32 ercd, T_IM_PRO_MONI_RESULT* moniResult );
void im_pro_6_3_print_5(Impro63Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar           ch, kint32 ercd );
void im_pro_6_3_print_6(Impro63Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar           ch, kint32 ercd, kuchar force );
void im_pro_6_3_print_7(Impro63Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar           ch, kint32 ercd, T_IM_PRO_M2P_CTRL* m2p_ctrl );
void im_pro_6_3_print_8(Impro63Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar           ch, kint32 ercd, kuchar paenTrg );
void im_pro_6_3_print_9(Impro63Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar           ch, kint32 ercd, kint32 cmpErcd );
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __IMPRO_6_3_PRINT_H__ */
