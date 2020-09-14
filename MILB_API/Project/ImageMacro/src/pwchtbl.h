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

#ifndef __PWCH_TBL_H__
#define __PWCH_TBL_H__

#include "improcommonlist.h"
#include "improcommon.h"
#include "im_pro.h"
#include <klib.h>

#define PWCH_TYPE_TBL		(pwch_tbl_get_type())
#define PWCH_TBL(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, PwchTbl))
#define PWCH_IS_TBL(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, PWCH_TYPE_TBL))


typedef struct 				_PwchTbl PwchTbl;
typedef struct 				_PwchTblPrivate PwchTblPrivate;

struct _PwchTbl {
	KObject parent;
	volatile	T_IM_PRO_ADDR_MNG			gIM_PRO_PWchAddrMng[E_IM_PRO_UNIT_NUM_MAX][E_IM_PRO_BLOCK_TYPE_MAX][E_IM_PRO_PWCH_MAX];
};


KConstType 		    pwch_tbl_get_type(void);
PwchTbl*		        pwch_tbl_get(void);
PwchTbl*		        pwch_tbl_new(void);

#define pwch_tbl_get_gIM_PRO_PWchAddrMng(self,i,x,y)           (self->gIM_PRO_PWchAddrMng[i][x][y])
INT32 paok_ind( PwchTbl* self,E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch);
INT32 paok_and(PwchTbl* self,E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch, T_IM_PRO_PWCH_INFO* pwch_info);
INT32 paok_bnd(PwchTbl* self,E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch);
INT32 paok_cnd(PwchTbl* self,E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch);
void paok_dnd(PwchTbl* self,E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch);
INT32 paok_end(PwchTbl* self,E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch, T_IM_PRO_PWCH_CTRL* pw_ctrl );
INT32 paok_fnd(PwchTbl* self,E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch);
INT32 paok_gnd(PwchTbl* self,E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch, T_IM_PRO_AXI_CTRL* axi_ctrl);
INT32 paok_hnd(PwchTbl* self,E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch, ULONG line_feed);
INT32 paok_jnd(PwchTbl* self,E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch, ULONG reg_addr);
INT32 paok_knd(PwchTbl* self,E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch);
INT32 paok_mnd(PwchTbl* self,E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch,UCHAR force);
INT32 paok_nnd(PwchTbl* self,E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch, ULONG reg_addr);
#endif /* __PWCH_TBL_H__ */
