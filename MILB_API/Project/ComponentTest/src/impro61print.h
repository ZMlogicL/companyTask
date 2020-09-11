/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro61Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IMPRO_6_1_PRINT_H__
#define __IMPRO_6_1_PRINT_H__


#include <klib.h>
#include "absimproprint.h"


#define IMPRO_TYPE_6_1_PRINT                  (impro_6_1_print_get_type())
#define IMPRO_6_1_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, Impro61Print)) 
#define IMPRO_IS_6_1_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_6_1_PRINT)) 


typedef struct _Impro61Print Impro61Print;
typedef struct _Impro61PrintPrivate Impro61PrintPrivate;

struct _Impro61Print 
{
	AbsImProPrint parent;
};


KConstType impro_6_1_print_get_type(void);
Impro61Print* impro_6_1_print_new(void);
Impro61Print* impro_6_1_print_get(void);

#ifndef CO_CT_IM_PRO_DISABL

void im_pro_6_1_print_0(Impro61Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, kint32 ercd, T_IM_PRO_AXI_CTRL* axiCtrl );
void im_pro_6_1_print_1(Impro61Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, kint32 ercd );
void im_pro_6_1_print_3(Impro61Print *self, kuint32 buf_idx, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, kint32 ercd );
void im_pro_6_1_print_4(Impro61Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, kint32 ercd, kulong lineFeed );
void im_pro_6_1_print_5(Impro61Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, kint32 ercd, kuchar axiResponse );
void im_pro_6_1_print_6(Impro61Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, kint32 ercd );
void im_pro_6_1_print_7(Impro61Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, kint32 ercd, kuchar force );
void im_pro_6_1_print_8(Impro61Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, kint32 ercd, T_IM_PRO_LNR_CTRL* lnrCtrl );
void im_pro_6_1_print_9(Impro61Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, kint32 ercd, const T_IM_PRO_RDMA_LNR_ADDR** addr );
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __IMPRO_6_1_PRINT_H__ */
