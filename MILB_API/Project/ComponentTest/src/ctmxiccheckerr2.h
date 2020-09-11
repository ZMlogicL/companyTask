/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :jianghaodong
*@brief               :CtMxicCheckErr2类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_MXIC_CHECK_ERR2_H_
#define __CT_MXIC_CHECK_ERR2_H_

#include <klib.h>

#define CT_TYPE_MXIC_CHECK_ERR2					(ct_mxic_check_err2_get_type())
#define CT_MXIC_CHECK_ERR2(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtMxicCheckErr2)) 
#define CT_IS_MXIC_CHECK_ERR2(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_MXIC_CHECK_ERR2)) 

typedef struct 			_CtMxicCheckErr2 CtMxicCheckErr2;
typedef struct 			_CtMxicCheckErr2Private CtMxicCheckErr2Private;

struct _CtMxicCheckErr2
{
	KObject parent;

};

KConstType 			ct_mxic_check_err2_get_type(void);
CtMxicCheckErr2* 	ct_mxic_check_err2_new(void);

void 						ct_mxic_check_err2_slot_priority_all_arbiter(void);
void 						ct_mxic_check_err2_master_priority(void);
void 						ct_mxic_check_err2_slot_mask(void);
void 						ct_mxic_check_err2_master_mask(void);
void 						ct_mxic_check_err2_master_mask_factor(void);
void 						ct_mxic_check_err2_master_mask_target(void);
void 						ct_mxic_check_err2_master_mask_select(void);
void 						ct_mxic_check_err2_master_transaction(void);
void 						ct_mxic_check_err2_history_monitor_stop_enable(void);
void 						ct_mxic_check_err2_history_monitor(void);
void 						ct_mxic_check_err2_history_monitor_all_port(void);
void 						ct_mxic_check_err2_slot_status_monitor_all_arbiter(void);
void 						ct_mxic_check_err2_slot_status_monitor_w_arbiter(void);
void 						ct_mxic_check_err2_slot_status_monitor_r_arbiter(void);
void 						ct_mxic_check_err2_slot_status_monitor_w_arbiter_group(void);
void 						ct_mxic_check_err2_slot_status_monitor_r_arbiter_group(void);
void 						ct_mxic_check_err2_master_status_monitor(void);
void 						ct_mxic_check_err2_set_access_or_trans_monitor_parameter(void);
void 						ct_mxic_check_err2_get_access_or_trans_monitor_parameter(void);
void 						ct_mxic_check_err2_access_or_trans_monitor(void);
void 						ct_mxic_check_err2_access_or_trans_monitor_all_entry(void);
void 						ct_mxic_check_err2_sccess_or_trans_monitor_limit_end_state(void);
void 						ct_mxic_check_err2_memory_access_start(void);
void 						ct_mxic_check_err2_memory_access_set(void);
void 						ct_mxic_check_err2_memory_access_get(void);

#endif /* __CT_MXIC_CHECK_ERR2_H_ */
