/*
 *ctimdisp2h.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-11
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP2H_H__
#define __CT_IM_DISP2H_H__

#include "imdisp2parent.h"

G_BEGIN_DECLS
/*
 * 以下开始宏声明
 * */
#define CT_TYPE_IM_DISP2H					(ct_im_disp2h_get_type ())
#define CT_IM_DISP2H(widget)				(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
		T_TYPE_IM_DISP2H, CtImDisp2h))
#define CT_IM_DISP2H_CLASS(klass)		(G_TYPE_CHECK_CLASS_CAST ((klass), \
		CT_TYPE_IM_DISP2H, CtImDisp2hClass))
#define CT_IS_IM_DISP2H(widget)			(G_TYPE_CHECK_INSTANCE_TYPE ((widget), CT_TYPE_IM_DISP2H))
#define CT_IS_IM_DISP2H_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_DISP2H))
#define CT_IM_DISP2H_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS ((obj), \
		CT_TYPE_IM_DISP2H, CtImDisp2hClass))

/*
 * 以下开始类结构体声明
 * */
typedef struct _CtImDisp2h 					CtImDisp2h;
typedef struct _CtImDisp2hClass 			CtImDisp2hClass;
typedef struct _CtImDisp2hPrivate 			CtImDisp2hPrivate;

struct _CtImDisp2h
{
	ImDisp2Parent parent;
	/*public*/
};

struct _CtImDisp2hClass
{
	ImDisp2ParentClass parentclass;
};

/*
 * 如下开始public方法声明
 * */
GType 					ct_im_disp2h_get_type(void) G_GNUC_CONST;
CtImDisp2h *		ct_im_disp2h_new(void);


G_END_DECLS

#endif /* __CT_IM_DISP2H_H__ */
