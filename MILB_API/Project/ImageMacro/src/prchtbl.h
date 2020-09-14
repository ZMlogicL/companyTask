/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-08-04
*@author              :刘应春
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年06月开始开发
*/

#ifndef __PRCH_TBL_H__
#define __PRCH_TBL_H__
#include "im_pro.h"
#include <klib.h>

#define PRCH_TYPE_TBL		(prch_tbl_get_type())
#define PRCH_TBL(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, PrchTbl))
#define PRCH_IS_TBL(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, PRCH_TYPE_TBL))

typedef struct 				_PrchTbl PrchTbl;
typedef struct 				_PrchTblPrivate PrchTblPrivate;

struct _PrchTbl {
	KObject parent;
};

KConstType 		    prch_tbl_get_type(void);
PrchTbl*		        prch_tbl_get(void);
PrchTbl*		        prch_tbl_new(void);

INT32 paek_and(PrchTbl* self,E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch,ULONG reg_addr);
INT32 paek_bnd(PrchTbl* self,E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch,ULONG reg_addr);
#endif /* __PRCH_TBL_H__ */
