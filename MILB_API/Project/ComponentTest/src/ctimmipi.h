/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-10
*@author              :jianghaodong
*@brief               :CtImMipi类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_MIPI_H_
#define __CT_IM_MIPI_H_

#include "driver_common.h"
#include "./../../../fj/glib/src/gobject.h"


G_BEGIN_DECLS

#define CT_TYPE_IM_MIPI					(ct_im_mipi_get_type())
#define CT_IM_MIPI(obj)						(G_TYPE_CHECK_INSTANCE_CAST (obj, CtImMipi))
#define CT_IM_MIPI_CLASS(klass)		(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_IM_MIPI, CtImMipiClass))
#define CT_IS_IM_MIPI(obj)					(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_IM_MIPI)) 
#define CT_IS_IM_MIPI_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_MIPI))
#define CT_IM_MIPI_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_IM_MIPI, CtImMipiClass))


typedef struct 			_CtImMipi CtImMipi;
typedef struct 			_CtImMipiClass CtImMipiClass;
typedef struct 			_CtImMipiPrivate CtImMipiPrivate;

struct _CtImMipi
{
	GObject parent;
};

struct _CtImMipiClass
{
	GObjectClass parentclass;
};


GType 				ct_im_mipi_get_type(void);
CtImMipi *		ct_im_mipi_new(void);

void 				ct_im_mipi_pclk_on(void);
void 				ct_im_mipi_pclk_off(void);
void 				ct_im_mipi_cb(void);

void 				ct_im_mipi_pcsim_test(CtImMipi* self);


G_END_DECLS

#endif /* __CT_IM_MIPI_H_ */
