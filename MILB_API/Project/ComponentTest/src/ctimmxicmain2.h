/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-10
*@author              :jianghaodong
*@brief               :CtImMxicMain2类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_MXIC_MAIN2_H_
#define __CT_IM_MXIC_MAIN2_H_

#include "ctimmxicmain1.h"

#include "./../../../fj/glib/src/gobject.h"


G_BEGIN_DECLS

#define CT_TYPE_IM_MXIC_MAIN2						(ct_im_mxic_main2_get_type())
#define CT_IM_MXIC_MAIN2(obj)						(G_TYPE_CHECK_INSTANCE_CAST (obj, CtImMxicMain2))
#define CT_IM_MXIC_MAIN2_CLASS(klass)			(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_IM_MXIC_MAIN2, CtImMxicMain2Class))
#define CT_IS_IM_MXIC_MAIN2(obj)					(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_IM_MXIC_MAIN2)) 
#define CT_IS_IM_MXIC_MAIN2_CLASS(klass)		(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_MXIC_MAIN2))
#define CT_IM_MXIC_MAIN2_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_IM_MXIC_MAIN2, CtImMxicMain2Class))


typedef struct 			_CtImMxicMain2 CtImMxicMain2;
typedef struct 			_CtImMxicMain2Class CtImMxicMain2Class;
typedef struct 			_CtImMxicMain2Private CtImMxicMain2Private;

struct _CtImMxicMain2
{
	GObject parent;
	CtImMxicMain1* ctImMxicMain1;
};

struct _CtImMxicMain2Class
{
	GObjectClass parentclass;
};


GType 						ct_im_mxic_main2_get_type(void);
CtImMxicMain2 *	ct_im_mxic_main2_new(void);

void 						ct_im_mxic_main2(CtImMxicMain2 *self, gint32 argc, gchar** argv);

G_END_DECLS

#endif /* __CT_IM_MXIC_MAIN2_H_ */
