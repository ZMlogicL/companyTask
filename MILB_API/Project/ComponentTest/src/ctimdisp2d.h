/*
 *ctimdisp2d.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-11
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP2D_H__
#define __CT_IM_DISP2D_H__

#include "imdisp2parent.h"

G_BEGIN_DECLS
/*
 * 以下开始宏声明
 * */
#define CT_TYPE_IM_DISP2D						(ct_im_disp2d_get_type ())
#define CT_IM_DISP2D(widget)					(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
		CT_TYPE_IM_DISP2D, CtImDisp2d))
#define CT_IM_DISP2D_CLASS(klass)			(G_TYPE_CHECK_CLASS_CAST ((klass), \
		CT_TYPE_IM_DISP2D, CtImDisp2dClass))
#define CT_IS_IM_DISP2D(widget)				(G_TYPE_CHECK_INSTANCE_TYPE ((widget), CT_TYPE_IM_DISP2D))
#define CT_IS_IM_DISP2D_CLASS(klass)		(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_DISP2D))
#define CT_IM_DISP2D_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS ((obj), \
		CT_TYPE_IM_DISP2D, CtImDisp2dClass))

/*
 * 以下开始类结构体声明
 * */
typedef struct _CtImDisp2d 					CtImDisp2d;
typedef struct _CtImDisp2dClass 			CtImDisp2dClass;
typedef struct _CtImDisp2dPrivate 			CtImDisp2dPrivate;

struct _CtImDisp2d
{
	ImDisp2Parent parent;
	/*public*/
	CtImDisp2dPrivate *ctImDisp2dPrivate;
};

struct _CtImDisp2dClass
{
	ImDisp2ParentClass parentclass;
};

/*
 * 如下开始public方法声明
 * */
GType 					ct_im_disp2d_get_type(void) G_GNUC_CONST;
CtImDisp2d *		ct_im_disp2d_new(void);


G_END_DECLS

#endif /* __CT_IM_DISP2D_H__ */
