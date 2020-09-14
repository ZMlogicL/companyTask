/*
 *ctimdisp2g.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-11
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP2G_H__
#define __CT_IM_DISP2G_H__

#include "imdisp2parent.h"

G_BEGIN_DECLS
/*
 * 以下开始宏声明
 * */
#define CT_TYPE_IM_DISP2G					(ct_im_disp2g_get_type ())
#define CT_IM_DISP2G(widget)				(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
		CT_TYPE_IM_DISP2G, CtImDisp2g))
#define CT_IM_DISP2G_CLASS(klass)		(G_TYPE_CHECK_CLASS_CAST ((klass), \
		CT_TYPE_IM_DISP2G, CtImDisp2gClass))
#define CT_IS_IM_DISP2G(widget)			(G_TYPE_CHECK_INSTANCE_TYPE ((widget), CT_TYPE_IM_DISP2G))
#define CT_IS_IM_DISP2G_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_DISP2G))
#define CT_IM_DISP2G_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS ((obj), \
		CT_TYPE_IM_DISP2G, CtImDisp2gClass))

/*
 * 以下开始类结构体声明
 * */
typedef struct _CtImDisp2g 					CtImDisp2g;
typedef struct _CtImDisp2gClass 			CtImDisp2gClass;
typedef struct _CtImDisp2gPrivate 			CtImDisp2gPrivate;

struct _CtImDisp2g
{
	ImDisp2Parent parent;
	/*public*/
};

struct _CtImDisp2gClass
{
	ImDisp2ParentClass parentclass;
};

/*
 * 如下开始public方法声明
 * */
GType 					ct_im_disp2g_get_type(void) G_GNUC_CONST;
CtImDisp2g *		ct_im_disp2g_new(void);

G_END_DECLS

#endif /* __CT_IM_DISP2G_H__ */
