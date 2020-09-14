/*
 *ctimdisp2n.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-11
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP2N_H__
#define __CT_IM_DISP2N_H__

#include "imdisp2parent.h"

G_BEGIN_DECLS
/*
 * 以下开始宏声明
 * */
#define CT_TYPE_IM_DISP2N						(ct_im_disp2n_get_type ())
#define CT_IM_DISP2N(widget)					(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
		CT_TYPE_IM_DISP2N, CtImDisp2n))
#define CT_IM_DISP2N_CLASS(klass)			(G_TYPE_CHECK_CLASS_CAST ((klass), \
		CT_TYPE_IM_DISP2N, CtImDisp2nClass))
#define CT_IS_IM_DISP2N(widget)				(G_TYPE_CHECK_INSTANCE_TYPE ((widget), CT_TYPE_IM_DISP2N))
#define CT_IS_IM_DISP2N_CLASS(klass)		(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_DISP2N))
#define CT_IM_DISP2N_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS ((obj), \
		CT_TYPE_IM_DISP2N, CtImDisp2nClass))

/*
 * 以下开始类结构体声明
 * */
typedef struct _CtImDisp2n 						CtImDisp2n;
typedef struct _CtImDisp2nClass 				CtImDisp2nClass;
typedef struct _CtImDisp2nPrivate 				CtImDisp2nPrivate;

struct _CtImDisp2n
{
	ImDisp2Parent parent;
	/*public*/
	CtImDisp2nPrivate *ctImDisp2nPrivate;
};

struct _CtImDisp2nClass
{
	ImDisp2ParentClass parentclass;
};

/*
 * 如下开始public方法声明
 * */
GType 					ct_im_disp2n_get_type(void) G_GNUC_CONST;
CtImDisp2n *		ct_im_disp2n_new(void);


G_END_DECLS

#endif /* __CT_IM_DISP2N_H__ */
