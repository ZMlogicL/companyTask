/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-10
*@author              :jianghaodong
*@brief               :CtImMxicFunc1类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_MXIC_FUNC1_H_
#define __CT_IM_MXIC_FUNC1_H_

#include "driver_common.h"

#include "./../../../fj/glib/src/gobject.h"


G_BEGIN_DECLS

#define CT_TYPE_IM_MXIC_FUNC1						(ct_im_mxic_func1_get_type())
#define CT_IM_MXIC_FUNC1(obj)						(G_TYPE_CHECK_INSTANCE_CAST (obj, CtImMxicFunc1))
#define CT_IM_MXIC_FUNC1_CLASS(klass)			(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_IM_MXIC_FUNC1, CtImMxicFunc1Class))
#define CT_IS_IM_MXIC_FUNC1(obj)					(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_IM_MXIC_FUNC1)) 
#define CT_IS_IM_MXIC_FUNC1_CLASS(klass)		(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_MXIC_FUNC1))
#define CT_IM_MXIC_FUNC1_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_IM_MXIC_FUNC1, CtImMxicFunc1Class))


typedef struct 			_CtImMxicFunc1 CtImMxicFunc1;
typedef struct 			_CtImMxicFunc1Class CtImMxicFunc1Class;
typedef struct 			_CtImMxicFunc1Private CtImMxicFunc1Private;

struct _CtImMxicFunc1
{
	GObject parent;
	guchar unit;

};

struct _CtImMxicFunc1Class
{
	GObjectClass parentclass;
};


GType 						ct_im_mxic_func1_get_type(void);
CtImMxicFunc1 *	ct_im_mxic_func1_new(void);

void 						ct_im_mxic_func1_01(CtImMxicFunc1* self);
void 						ct_im_mxic_func1_02(CtImMxicFunc1* self);
void 						ct_im_mxic_func1_03(CtImMxicFunc1* self);
void 						ct_im_mxic_func1_04(CtImMxicFunc1* self);
void 						ct_im_mxic_func1_05(CtImMxicFunc1* self);
void 						ct_im_mxic_func1_06(CtImMxicFunc1* self);
void 						ct_im_mxic_func1_07(CtImMxicFunc1* self);
void 						ct_im_mxic_func1_08(CtImMxicFunc1* self);
void 						ct_im_mxic_func1_09(CtImMxicFunc1* self);
void 						ct_im_mxic_func1_10(CtImMxicFunc1* self);
void 						ct_im_mxic_func1_11(CtImMxicFunc1* self);


G_END_DECLS

#endif /* __CT_IM_MXIC_FUNC1_H_ */
