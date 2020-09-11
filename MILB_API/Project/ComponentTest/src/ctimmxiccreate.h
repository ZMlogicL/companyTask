/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :jianghaodong
*@brief               :CtImMxicCreate类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_MXIC_CREATE_H_
#define __CT_IM_MXIC_CREATE_H_

#include <klib.h>
#include "im_mxic.h"

#define CT_TYPE_IM_MXIC_CREATE					(ct_im_mxic_create_get_type())
#define CT_IM_MXIC_CREATE(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImMxicCreate)) 
#define CT_IS_IM_MXIC_CREATE(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_MXIC_CREATE)) 

typedef struct 			_CtImMxicCreate CtImMxicCreate;
typedef struct 			_CtImMxicCreatePrivate CtImMxicCreatePrivate;

struct _CtImMxicCreate
{
	KObject parent;

};

KConstType 				ct_im_mxic_create_get_type(void);
CtImMxicCreate*		ct_im_mxic_create_new(void);

void 							ct_im_mxic_create_dec_err_cb( kuchar chType);

kint32 							ct_im_mxic_create_slot_priority_all_arbiter_param(
									T_IM_MXIC_ALL_SLOT_PRIORITY_LEVEL* const allLevelCtrl);
kint32 							ct_im_mxic_create_all_levelport_param(
									T_IM_MXIC_ALL_LEVELPORT* const allLevelport);
kint32 							ct_im_mxic_create_access_or_trans_monitor_param(kuchar paramKind,
									T_IM_MXIC_MONITOR_PARAMETER* const monParam);
kint32 							ct_im_mxic_create_master_w_arbiter_param(E_IM_MXIC_UNIT unit,
									T_IM_MXIC_W_ARBITER_ASSIGN_PORT* const wArbiterAssign );
kint32 							ct_im_mxic_create_master_r_arbiter_param(E_IM_MXIC_UNIT unit,
									T_IM_MXIC_R_ARBITER_ASSIGN_PORT* const rArbiterAssign );
kint32 							ct_im_mxic_create_master_all_arbiter_param(E_IM_MXIC_UNIT unit,
									T_IM_MXIC_ALL_ARBITER_ASSIGN* const allArbiterAssign );
kint32 							ct_im_mxic_create_memory_access_start_trigger(kuint32 startParam,
									T_IM_MXIC_MEMORY_ACCESS_SLAVE* const memacc_start);
kint32 							ct_im_mxic_create_memory_access_param(kuint32 startParam,
									kuint32 paramPattern, T_IM_MXIC_MEMORY_ACCESS_SLAVE* const memaccParam);
kint32 							ct_im_mxic_create_all_port_set(kuint32 set_ptn,
									T_IM_MXIC_OUTPUT_PORT* const allPortAssign);

#endif /* __CT_IM_MXIC_CREATE_H_ */
