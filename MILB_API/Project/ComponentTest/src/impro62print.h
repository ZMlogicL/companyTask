/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro62Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IMPRO_6_2_PRINT_H__
#define __IMPRO_6_2_PRINT_H__


#include <klib.h>
#include "absimproprint.h"


#define IMPRO_TYPE_6_2_PRINT                  (impro_6_2_print_get_type())
#define IMPRO_6_2_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, Impro62Print)) 
#define IMPRO_IS_6_2_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_6_2_PRINT)) 


typedef struct _Impro62Print Impro62Print;
typedef struct _Impro62PrintPrivate Impro62PrintPrivate;

struct _Impro62Print 
{
	AbsImProPrint parent;
};


KConstType impro_6_2_print_get_type(void);
Impro62Print* impro_6_2_print_new(void);
Impro62Print* impro_6_2_print_get(void);

#ifndef CO_CT_IM_PRO_DISABL

void im_pro_6_2_print_0(Impro62Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, kint32 ercd );
void im_pro_6_2_print_1(Impro62Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, 
							 kuchar ch, kint32 ercd, kuchar force );
void im_pro_6_2_print_2(Impro62Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, 
							 kuchar ch, kint32 ercd, T_IM_PRO_PGAIN_CTRL* pgainCtrl );
void im_pro_6_2_print_3(Impro62Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, kint32 ercd, 
						     const T_IM_PRO_RDMA_PGAIN_ADDR** addr );
void im_pro_6_2_print_4(Impro62Print *self, E_IM_PRO_UNIT_NUM unitNo, kuchar ch, kint32 ercd );
void im_pro_6_2_print_5(Impro62Print *self, E_IM_PRO_UNIT_NUM unitNo, kuchar ch, kint32 ercd, kuchar force );
void im_pro_6_2_print_6(Impro62Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kuchar ch, kint32 ercd, 
							 T_IM_PRO_PZSFT_CTRL* pzsftCtrl );
void im_pro_6_2_print_7(Impro62Print *self, E_IM_PRO_UNIT_NUM unitNo, kuchar ch, kint32 ercd, const T_IM_PRO_RDMA_PZSFT_ADDR** addr );
void im_pro_6_2_print_8(Impro62Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kint32 ercd );
void im_pro_6_2_print_9(Impro62Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kint32 ercd );
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __IMPRO_6_2_PRINT_H__ */
