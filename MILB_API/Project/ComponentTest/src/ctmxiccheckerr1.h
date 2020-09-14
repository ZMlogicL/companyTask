/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-10
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

#include "./../../../fj/glib/src/gobject.h"


G_BEGIN_DECLS

#define CT_TYPE_MXIC_CHECK_ERR1						(ct_mxic_check_err1_get_type())
#define CT_MXIC_CHECK_ERR1(obj)						(G_TYPE_CHECK_INSTANCE_CAST (obj, CtMxicCheckErr1))
#define CT_MXIC_CHECK_ERR1_CLASS(klass)			(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_MXIC_CHECK_ERR1, CtMxicCheckErr1Class))
#define CT_IS_MXIC_CHECK_ERR1(obj)					(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_MXIC_CHECK_ERR1)) 
#define CT_IS_MXIC_CHECK_ERR1_CLASS(klass)		(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_MXIC_CHECK_ERR1))
#define CT_MXIC_CHECK_ERR1_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_MXIC_CHECK_ERR1, CtMxicCheckErr1Class))


typedef struct 			_CtMxicCheckErr1 CtMxicCheckErr1;
typedef struct 			_CtMxicCheckErr1Class CtMxicCheckErr1Class;
typedef struct 			_CtMxicCheckErr1Private CtMxicCheckErr1Private;

struct _CtMxicCheckErr1
{
	GObject parent;
};

struct _CtMxicCheckErr1Class
{
	GObjectClass parentclass;
};


GType 						ct_mxic_check_err1_get_type(void);
CtMxicCheckErr1 *	ct_mxic_check_err1_new(void);

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

G_END_DECLS

#endif /* __CT_MXIC_CHECK_ERR1_H_ */
