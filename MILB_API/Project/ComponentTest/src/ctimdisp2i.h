/*
 *ctimdisp2i.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-11
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP2I_H__
#define __CT_IM_DISP2I_H__

#include "imdisp2parent.h"

G_BEGIN_DECLS
/*
 * 以下开始宏声明
 * */
#define CT_TYPE_IM_DISP2I						(ct_im_disp2i_get_type ())
#define CT_IM_DISP2I(widget)					(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
		CT_TYPE_IM_DISP2I, CtImDisp2i))
#define CT_IM_DISP2I_CLASS(klass)			(G_TYPE_CHECK_CLASS_CAST ((klass), \
		CT_TYPE_IM_DISP2I, CtImDisp2iClass))
#define CT_IS_IM_DISP2I(widget)				(G_TYPE_CHECK_INSTANCE_TYPE ((widget), CT_TYPE_IM_DISP2I))
#define CT_IS_IM_DISP2I_CLASS(klass)		(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_DISP2I))
#define CT_IM_DISP2I_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS ((obj), \
		CT_TYPE_IM_DISP2I, CtImDisp2iClass))

/*
 * 以下开始类结构体声明
 * */
typedef struct _CtImDisp2i 						CtImDisp2i;
typedef struct _CtImDisp2iClass 				CtImDisp2iClass;
typedef struct _CtImDisp2iPrivate 			CtImDisp2iPrivate;

struct _CtImDisp2i
{
	ImDisp2Parent parent;
	/*public*/
};

struct _CtImDisp2iClass
{
	ImDisp2ParentClass parentclass;
};

/*
 * 如下开始public方法声明
 * */
GType 					ct_im_disp2i_get_type(void) G_GNUC_CONST;
CtImDisp2i *			ct_im_disp2i_new(void);

G_END_DECLS

#endif /* __CT_IM_DISP2I_H__ */
