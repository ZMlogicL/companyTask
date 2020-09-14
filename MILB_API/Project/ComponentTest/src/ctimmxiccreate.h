/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-10
*@author              :jianghaodong
*@brief               :CtImMxicCreate类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_MXIC_CREATE_H_
#define __CT_IM_MXIC_CREATE_H_

#include "im_mxic.h"

#include "./../../../fj/glib/src/gobject.h"


G_BEGIN_DECLS

#define CT_TYPE_IM_MXIC_CREATE						(ct_im_mxic_create_get_type())
#define CT_IM_MXIC_CREATE(obj)						(G_TYPE_CHECK_INSTANCE_CAST (obj, CtImMxicCreate))
#define CT_IM_MXIC_CREATE_CLASS(klass)		(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_IM_MXIC_CREATE, CtImMxicCreateClass))
#define CT_IS_IM_MXIC_CREATE(obj)					(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_IM_MXIC_CREATE)) 
#define CT_IS_IM_MXIC_CREATE_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_MXIC_CREATE))
#define CT_IM_MXIC_CREATE_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_IM_MXIC_CREATE, CtImMxicCreateClass))


typedef struct 			_CtImMxicCreate CtImMxicCreate;
typedef struct 			_CtImMxicCreateClass CtImMxicCreateClass;
typedef struct 			_CtImMxicCreatePrivate CtImMxicCreatePrivate;

struct _CtImMxicCreate
{
	GObject parent;
};

struct _CtImMxicCreateClass
{
	GObjectClass parentclass;
};


GType 							ct_im_mxic_create_get_type(void);
CtImMxicCreate *		ct_im_mxic_create_new(void);

void 							ct_im_mxic_create_dec_err_cb(guchar chType);

gint32 							ct_im_mxic_create_slot_priority_all_arbiter_param(
									T_IM_MXIC_ALL_SLOT_PRIORITY_LEVEL* const allLevelCtrl);
gint32 							ct_im_mxic_create_all_levelport_param(
									T_IM_MXIC_ALL_LEVELPORT* const allLevelport);
gint32 							ct_im_mxic_create_access_or_trans_monitor_param(guchar paramKind,
									T_IM_MXIC_MONITOR_PARAMETER* const monParam);
gint32 							ct_im_mxic_create_master_w_arbiter_param(E_IM_MXIC_UNIT unit,
									T_IM_MXIC_W_ARBITER_ASSIGN_PORT* const wArbiterAssign );
gint32 							ct_im_mxic_create_master_r_arbiter_param(E_IM_MXIC_UNIT unit,
									T_IM_MXIC_R_ARBITER_ASSIGN_PORT* const rArbiterAssign );
gint32 							ct_im_mxic_create_master_all_arbiter_param(E_IM_MXIC_UNIT unit,
									T_IM_MXIC_ALL_ARBITER_ASSIGN* const allArbiterAssign );
gint32 							ct_im_mxic_create_memory_access_start_trigger(guint32 startParam,
									T_IM_MXIC_MEMORY_ACCESS_SLAVE* const memacc_start);
gint32 							ct_im_mxic_create_memory_access_param(guint32 startParam,
									guint32 paramPattern, T_IM_MXIC_MEMORY_ACCESS_SLAVE* const memaccParam);
gint32 							ct_im_mxic_create_all_port_set(guint32 set_ptn,
									T_IM_MXIC_OUTPUT_PORT* const allPortAssign);

G_END_DECLS

#endif /* __CT_IM_MXIC_CREATE_H_ */
