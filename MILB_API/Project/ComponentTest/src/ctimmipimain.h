/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-10
*@author              :jianghaodong
*@brief               :CtImMipiMain类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_MIPI_MAIN_H_
#define __CT_IM_MIPI_MAIN_H_

#include "driver_common.h"

#include "./../../../fj/glib/src/gobject.h"


G_BEGIN_DECLS

#define CT_TYPE_IM_MIPI_MAIN					(ct_im_mipi_main_get_type())
#define CT_IM_MIPI_MAIN(obj)					(G_TYPE_CHECK_INSTANCE_CAST (obj, CtImMipiMain)) 
#define CT_IM_MIPI_MAIN_CLASS(klass)					(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_IM_MIPI_MAIN, CtImMipiMainClass)) 
#define CT_IS_IM_MIPI_MAIN(obj)					(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_IM_MIPI_MAIN)) 
#define CT_IS_IM_MIPI_MAIN_CLASS(klass)					(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_MIPI_MAIN)) 
#define CT_IM_MIPI_MAIN_GET_CLASS(obj)					(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_IM_MIPI_MAIN, CtImMipiMainClass)) 


typedef struct 			_CtImMipiMain CtImMipiMain;
typedef struct 			_CtImMipiMainClass CtImMipiMainClass;
typedef struct 			_CtImMipiMainPrivate CtImMipiMainPrivate;

struct _CtImMipiMain
{
	GObject parent;
};

struct _CtImMipiMainClass
{
	GObjectClass parentclass;
};


GType ct_im_mipi_main_get_type(void);
CtImMipiMain *ct_im_mipi_main_new(void);

void 					Ct_Im_Mipi_Main(gint32 argc, gchar** argv);
//void 					ct_im_mipi_main_main(CtImMipiMain* self,gint argc, gchar** argv);

G_END_DECLS

#endif /* __CT_IM_MIPI_MAIN_H_ */
