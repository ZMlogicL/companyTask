/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :jianghaodong
*@brief               :CtMxicCheckErr1类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_MXIC_CHECK_ERR1_H_
#define __CT_MXIC_CHECK_ERR1_H_

#include <klib.h>

#define CT_TYPE_MXIC_CHECK_ERR1					(ct_mxic_check_err1_get_type())
#define CT_MXIC_CHECK_ERR1(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtMxicCheckErr1)) 
#define CT_IS_MXIC_CHECK_ERR1(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_MXIC_CHECK_ERR1)) 

typedef struct 			_CtMxicCheckErr1 CtMxicCheckErr1;
typedef struct 			_CtMxicCheckErr1Private CtMxicCheckErr1Private;

struct _CtMxicCheckErr1
{
	KObject parent;

};

KConstType 			ct_mxic_check_err1_get_type(void);
CtMxicCheckErr1* 	ct_mxic_check_err1_new(void);

void 						ct_mxic_check_err1_start_config(void);
void 						ct_mxic_check_err1_clock_enable(void);
void 						ct_mxic_check_err1_acceptance_capability(void);
void 						ct_mxic_check_err1_acceptance_capability_group(void);
void 						ct_mxic_check_err1_acceptance_capability_all_port(void);
void 						ct_mxic_check_err1_slave_area(void);
void 						ct_mxic_check_err1_slave_area_all(void);
void 						ct_mxic_check_err1_decode_error(void);
void 						ct_mxic_check_err1_levelport_level(void);
void 						ct_mxic_check_err1_levelport_port(void);
void 						ct_mxic_check_err1_levelport_all(void);
void 						ct_mxic_check_err1_port_assign(void);
void 						ct_mxic_check_err1_port_assign_all(void);
void 						ct_mxic_check_err1_master_w_arbiter(void);
void 						ct_mxic_check_err1_master_r_arbiter(void);
void 						ct_mxic_check_err1_master_all_arbiter(void);
void 						ct_mxic_check_err1_master_overlap( void );
void 						ct_mxic_check_err1_slot_priority(void);

#endif /* __CT_MXIC_CHECK_ERR1_H_ */
