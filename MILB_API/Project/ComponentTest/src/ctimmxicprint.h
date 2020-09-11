/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :jianghaodong
*@brief               :CtImMxicPrint类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_MXIC_PRINT_H_
#define __CT_IM_MXIC_PRINT_H_

#include <klib.h>
#include "im_mxic.h"

#define CT_TYPE_IM_MXIC_PRINT					(ct_im_mxic_print_get_type())
#define CT_IM_MXIC_PRINT(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImMxicPrint)) 
#define CT_IS_IM_MXIC_PRINT(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_MXIC_PRINT)) 

typedef struct 			_CtImMxicPrint CtImMxicPrint;
typedef struct 			_CtImMxicPrintPrivate CtImMxicPrintPrivate;

struct _CtImMxicPrint
{
	KObject parent;

};

KConstType 		ct_im_mxic_print_get_type(void);
CtImMxicPrint* 	ct_im_mxic_print_new(void);

int 						ct_im_mxic_print_atoi_hex(kchar* ch);
void 					ct_im_mxic_print_w_arbiter_assign(T_IM_MXIC_W_ARBITER_ASSIGN_PORT const* const wAssign);
void 					ct_im_mxic_print_w_arbiter_assign_group(T_IM_MXIC_W_ARBITER_ASSIGN_GR const* const wAssign);
void 					ct_im_mxic_print_r_arbiter_assign(T_IM_MXIC_R_ARBITER_ASSIGN_PORT const* const rAssign);
void 					ct_im_mxic_print_r_arbiter_assign_group(T_IM_MXIC_R_ARBITER_ASSIGN_GR const* const wAssign);
void 					ct_im_mxic_print_all_arbiter_assign(T_IM_MXIC_ALL_ARBITER_ASSIGN const* const allAssign);
void 					ct_im_mxic_print_all_slot_priority_level(
							T_IM_MXIC_ALL_SLOT_PRIORITY_LEVEL const* const allArbiterAssign);
void 					ct_im_mxic_print_all_slot_status_monitor(
							T_IM_MXIC_ALL_SLOT_STATUS_MONITOR const* const allSlotStatus);
void 					ct_im_mxic_print_master_status_monitor(
							T_IM_MXIC_MASTER_STATUS_MONITOR const* const masterStatus);
void 					ct_im_mxic_print_monitor_parameter(T_IM_MXIC_MONITOR_PARAMETER const* const monParam);
void 					ct_im_mxic_print_all_access_or_trans_monitor(
							T_IM_MXIC_ALL_ACCESS_OR_TRANS_MONITOR const* const allAccTrans);
void					ct_im_mxic_print_all_port_assign(T_IM_MXIC_OUTPUT_PORT const* const allPortAssign);
void 					ct_im_mxic_print_all_acceptance_capability(
							T_IM_MXIC_ALL_ACCEPTANCE_CAPABILITY const* const allCapability);
void 					ct_im_mxic_print_slave_area(T_IM_MXIC_SLAVE_AREA const* const slaveArea);
void 					ct_im_mxic_print_all_slave_area(T_IM_MXIC_ALL_SLAVE_AREA const* const allSlaveArea);
void 					ct_im_mxic_print_dec_err_int(T_IM_MXIC_DEC_ERR_INT const* const decErrInt);
void 					ct_im_mxic_print_dec_err(T_IM_MXIC_DEC_ERR const* const decErr);
void 					ct_im_mxic_print_history_monitor(T_IM_MXIC_HISTORY_MONITOR const* const history);
void 					ct_im_mxic_print_all_history_monitor(T_IM_MXIC_ALL_HISTORY_MONITOR const* const allHistory);
void 					ct_im_mxic_print_memory_access_param(
							T_IM_MXIC_MEMORY_ACCESS_SLAVE const* const memaccParam);
void 					ct_im_mxic_print_all_levelport(T_IM_MXIC_ALL_LEVELPORT* const allLevelport);


#endif /* __CT_IM_MXIC_PRINT_H_ */
