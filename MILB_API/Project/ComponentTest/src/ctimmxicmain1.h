/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-10
*@author              :jianghaodong
*@brief               :CtImMxicMain1类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_MXIC_MAIN1_H_
#define __CT_IM_MXIC_MAIN1_H_

#include "im_mxic.h"

#include "./../../../fj/glib/src/gobject.h"


G_BEGIN_DECLS

#define CT_TYPE_IM_MXIC_MAIN1						(ct_im_mxic_main1_get_type())
#define CT_IM_MXIC_MAIN1(obj)						(G_TYPE_CHECK_INSTANCE_CAST (obj, CtImMxicMain1))
#define CT_IM_MXIC_MAIN1_CLASS(klass)			(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_IM_MXIC_MAIN1, CtImMxicMain1Class))
#define CT_IS_IM_MXIC_MAIN1(obj)					(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_IM_MXIC_MAIN1)) 
#define CT_IS_IM_MXIC_MAIN1_CLASS(klass)		(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_MXIC_MAIN1))
#define CT_IM_MXIC_MAIN1_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_IM_MXIC_MAIN1, CtImMxicMain1Class))


typedef struct 			_CtImMxicMain1 CtImMxicMain1;
typedef struct 			_CtImMxicMain1Class CtImMxicMain1Class;
typedef struct 			_CtImMxicMain1Private CtImMxicMain1Private;

struct _CtImMxicMain1
{
	GObject parent;
	gint32	result;
	E_IM_MXIC_UNIT							unit;
	T_IM_MXIC_W_ARBITER_ASSIGN_PORT			wSlotStatus;
	T_IM_MXIC_R_ARBITER_ASSIGN_PORT			rSlotStatus;
};

struct _CtImMxicMain1Class
{
	GObjectClass parentclass;
};


GType 						ct_im_mxic_main1_get_type(void);
CtImMxicMain1 *	ct_im_mxic_main1_new(void);

void 						ct_im_mxic_main1(CtImMxicMain1 *self, gint32 argc, gchar** argv);

G_END_DECLS

#endif /* __CT_IM_MXIC_MAIN1_H_ */
