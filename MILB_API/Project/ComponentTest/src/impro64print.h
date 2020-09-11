/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro64Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IMPRO_6_4_PRINT_H__
#define __IMPRO_6_4_PRINT_H__


#include <klib.h>
#include "absimproprint.h"


#define IMPRO_TYPE_6_4_PRINT                  (impro_6_4_print_get_type())
#define IMPRO_6_4_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, Impro64Print)) 
#define IMPRO_IS_6_4_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_6_4_PRINT)) 


typedef struct _Impro64Print Impro64Print;
typedef struct _Impro64PrintPrivate Impro64PrintPrivate;

struct _Impro64Print 
{
	AbsImProPrint parent;
};


KConstType impro_6_4_print_get_type(void);
Impro64Print* impro_6_4_print_new(void);
Impro64Print* impro_6_4_print_get(void);

#ifndef CO_CT_IM_PRO_DISABL

void im_pro_6_4_print_0(Impro64Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, kint32 ercd, 
							 const T_IM_PRO_RDMA_M2P_DEKNEE_TBL_ADDR** addr );
void im_pro_6_4_print_1(Impro64Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, kint32 ercd );
void im_pro_6_4_print_2(Impro64Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, 
							 kint32 ercd, kuchar force );
void im_pro_6_4_print_3(Impro64Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, 
							 kint32 ercd, T_IM_PRO_PRCH_CTRL* prchCtrl );
void im_pro_6_4_print_4(Impro64Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, 
							 kint32 ercd, T_IM_PRO_AXI_CTRL* axiCtrl );
void im_pro_6_4_print_5(Impro64Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, 
							 kint32 ercd, kulong prAddr );
void im_pro_6_4_print_6(Impro64Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, 
						     kint32 ercd, T_IM_PRO_PRCH_AREA* prArea );
void im_pro_6_4_print_7(Impro64Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, 
							 kint32 ercd, kuchar axiResponse );
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __IMPRO_6_4_PRINT_H__ */
