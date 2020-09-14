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

#ifndef __PKCH_TBL_H__
#define __PKCH_TBL_H__
#include "im_pro.h"
#include <klib.h>

#define PKCH_TYPE_TBL		(pkch_tbl_get_type())
#define PKCH_TBL(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, PkchTbl))
#define PKCH_IS_TBL(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, PKCH_TYPE_TBL))

typedef struct 				_PkchTbl PkchTbl;
typedef struct 				_PkchTblPrivate PkchTblPrivate;

struct _PkchTbl {
	KObject parent;
};

KConstType 		    pkch_tbl_get_type(void);
PkchTbl*		        pkch_tbl_new(void);
PkchTbl*		        pkch_tbl_get(void);

INT32 paek_cnd(PkchTbl* self,E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch,ULONG reg_addr);
INT32 paek_dnd(PkchTbl* self,E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch,ULONG reg_addr);
INT32 paek_end(PkchTbl* self,E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch,ULONG reg_addr);
INT32 paek_fnd(PkchTbl* self,E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch,ULONG reg_addr);
#endif /* __PKCH_TBL_H__ */
