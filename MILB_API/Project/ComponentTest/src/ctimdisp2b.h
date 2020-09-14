/*
 *ctimdisp2b.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-11
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP2B_H__
#define __CT_IM_DISP2B_H__

#include "imdisp2parent.h"

G_BEGIN_DECLS
/*
 * 以下开始宏声明
 * */
#define CT_TYPE_IM_DISP2B					(ct_im_disp2b_get_type ())
#define CT_IM_DISP2B(widget)				(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
		CT_TYPE_IM_DISP2B, CtImDisp2b))
#define CT_IM_DISP2B_CLASS(klass)		(G_TYPE_CHECK_CLASS_CAST ((klass), \
		CT_TYPE_IM_DISP2B, CtImDisp2bClass))
#define CT_IS_IM_DISP2B(widget)			(G_TYPE_CHECK_INSTANCE_TYPE ((widget), CT_TYPE_IM_DISP2B))
#define CT_IS_IM_DISP2B_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_DISP2B))
#define CT_IM_DISP2B_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS ((obj), \
		CT_TYPE_IM_DISP2B, CtImDisp2bClass))

/*
 * 以下开始类结构体声明
 * */
typedef struct _CtImDisp2b 					CtImDisp2b;
typedef struct _CtImDisp2bClass 			CtImDisp2bClass;
typedef struct _CtImDisp2bPrivate 			CtImDisp2bPrivate;

typedef struct _Disp2bNewParams Disp2bNewParams;

struct _CtImDisp2b
{
	ImDisp2Parent parent;
	/*public*/
	CtImDisp2bPrivate *privCtImDisp2b;
};

struct _CtImDisp2bClass
{
	ImDisp2ParentClass parentclass;
};

/*
 * 如下开始public方法声明
 * */
GType 					ct_im_disp2b_get_type(void) G_GNUC_CONST;
CtImDisp2b *		ct_im_disp2b_new(Disp2bNewParams *disp2NewParams);

G_END_DECLS

#endif /* __CT_IM_DISP2B_H__ */
