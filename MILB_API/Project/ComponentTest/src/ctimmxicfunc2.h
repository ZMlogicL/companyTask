/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-10
*@author              :jianghaodong
*@brief               :CtImMxicFunc2类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_MXIC_FUNC2_H_
#define __CT_IM_MXIC_FUNC2_H_

#include "driver_common.h"

#include "./../../../fj/glib/src/gobject.h"


G_BEGIN_DECLS

#define CT_TYPE_IM_MXIC_FUNC2					(ct_im_mxic_func2_get_type())
#define CT_IM_MXIC_FUNC2(obj)					(G_TYPE_CHECK_INSTANCE_CAST (obj, CtImMxicFunc2)) 
#define CT_IM_MXIC_FUNC2_CLASS(klass)					(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_IM_MXIC_FUNC2, CtImMxicFunc2Class)) 
#define CT_IS_IM_MXIC_FUNC2(obj)					(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_IM_MXIC_FUNC2)) 
#define CT_IS_IM_MXIC_FUNC2_CLASS(klass)					(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_MXIC_FUNC2)) 
#define CT_IM_MXIC_FUNC2_GET_CLASS(obj)					(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_IM_MXIC_FUNC2, CtImMxicFunc2Class)) 


typedef struct 			_CtImMxicFunc2 CtImMxicFunc2;
typedef struct 			_CtImMxicFunc2Class CtImMxicFunc2Class;
typedef struct 			_CtImMxicFunc2Private CtImMxicFunc2Private;

struct _CtImMxicFunc2
{
	GObject parent;
	guchar unit;

};

struct _CtImMxicFunc2Class
{
	GObjectClass parentclass;
};


GType ct_im_mxic_func2_get_type(void);
CtImMxicFunc2 *ct_im_mxic_func2_new(void);

void 						ct_im_mxic_func2_12(CtImMxicFunc2* self);
void 						ct_im_mxic_func2_13(CtImMxicFunc2* self);
void 						ct_im_mxic_func2_14(CtImMxicFunc2* self);
void 						ct_im_mxic_func2_15(CtImMxicFunc2* self);
void 						ct_im_mxic_func2_16(CtImMxicFunc2* self);
void 						ct_im_mxic_func2_17(CtImMxicFunc2* self);
void 						ct_im_mxic_func2_19(CtImMxicFunc2* self);

G_END_DECLS

#endif /* __CT_IM_MXIC_FUNC2_H_ */
