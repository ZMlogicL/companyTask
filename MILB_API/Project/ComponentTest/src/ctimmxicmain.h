/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-10
*@author              :jianghaodong
*@brief               :CtImMxicMain类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_MXIC_MAIN_H_
#define __CT_IM_MXIC_MAIN_H_

#include "driver_common.h"

#include "./../../../fj/glib/src/gobject.h"


G_BEGIN_DECLS

#define CT_TYPE_IM_MXIC_MAIN					(ct_im_mxic_main_get_type())
#define CT_IM_MXIC_MAIN(obj)						(G_TYPE_CHECK_INSTANCE_CAST (obj, CtImMxicMain))
#define CT_IM_MXIC_MAIN_CLASS(klass)		(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_IM_MXIC_MAIN, CtImMxicMainClass))
#define CT_IS_IM_MXIC_MAIN(obj)					(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_IM_MXIC_MAIN)) 
#define CT_IS_IM_MXIC_MAIN_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_MXIC_MAIN))
#define CT_IM_MXIC_MAIN_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_IM_MXIC_MAIN, CtImMxicMainClass))


typedef struct 			_CtImMxicMain CtImMxicMain;
typedef struct 			_CtImMxicMainClass CtImMxicMainClass;
typedef struct 			_CtImMxicMainPrivate CtImMxicMainPrivate;

struct _CtImMxicMain
{
	GObject parent;
};

struct _CtImMxicMainClass
{
	GObjectClass parentclass;
};


GType ct_im_mxic_main_get_type(void);
CtImMxicMain *ct_im_mxic_main_new(void);

void Ct_Im_MXIC_Main(gint32 argc, gchar** argv);
//void ct_im_mxic_main_main(gint32 argc, gchar** argv);

G_END_DECLS

#endif /* __CT_IM_MXIC_MAIN_H_ */
