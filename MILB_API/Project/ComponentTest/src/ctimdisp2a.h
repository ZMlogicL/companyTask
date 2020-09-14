/*
 *ctimdisp2a.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-11
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP2A_H__
#define __CT_IM_DISP2A_H__

#include "imdisp2parent.h"

G_BEGIN_DECLS
/*
 * 以下开始宏声明
 * */
#define CT_TYPE_IM_DISP2A						(ct_im_disp2a_get_type ())
#define CT_IM_DISP2A(widget)					(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
		CT_TYPE_IM_DISP2A, CtImDisp2a))
#define CT_IM_DISP2A_CLASS(klass)			(G_TYPE_CHECK_CLASS_CAST ((klass), \
		CT_TYPE_IM_DISP2A, CtImDisp2aClass))
#define CT_IS_IM_DISP2A(widget)				(G_TYPE_CHECK_INSTANCE_TYPE ((widget), CT_TYPE_IM_DISP2A))
#define CT_IS_IM_DISP2A_CLASS(klass)		(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_DISP2A))
#define CT_IM_DISP2A_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS ((obj), \
		CT_TYPE_IM_DISP2A, CtImDisp2aClass))

/*
 * 以下开始类结构体声明
 * */
typedef struct _CtImDisp2a 						CtImDisp2a;
typedef struct _CtImDisp2aClass 				CtImDisp2aClass;
typedef struct _CtImDisp2aPrivate 				CtImDisp2aPrivate;

struct _CtImDisp2a
{
	ImDisp2Parent parent;
	/*public*/
	CtImDisp2aPrivate *privCtImDisp2a;
};

struct _CtImDisp2aClass
{
	ImDisp2ParentClass parentclass;
};

/*
 * 如下开始public方法声明
 * */
GType 					ct_im_disp2a_get_type(void) G_GNUC_CONST;
CtImDisp2a *		ct_im_disp2a_new(void);


G_END_DECLS

#endif /* __CT_IM_DISP2A_H__ */
