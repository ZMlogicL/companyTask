/*
 *ctimdisp2e.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-11
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP2E_H__
#define __CT_IM_DISP2E_H__

#include "imdisp2parent.h"

G_BEGIN_DECLS
/*
 * 以下开始宏声明
 * */
#define CT_TYPE_IM_DISP2E						(ct_im_disp2e_get_type ())
#define CT_IM_DISP2E(widget)						(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
		CT_TYPE_IM_DISP2E, CtImDisp2e))
#define CT_IM_DISP2E_CLASS(klass)				(G_TYPE_CHECK_CLASS_CAST ((klass), \
		CT_TYPE_IM_DISP2E, CtImDisp2eClass))
#define CT_IS_IM_DISP2E(widget)				(G_TYPE_CHECK_INSTANCE_TYPE ((widget), CT_TYPE_IM_DISP2E))
#define CT_IS_IM_DISP2E_CLASS(klass)		(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_DISP2E))
#define CT_IM_DISP2E_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS ((obj), \
		CT_TYPE_IM_DISP2E, CtImDisp2eClass))

/*
 * 以下开始类结构体声明
 * */
typedef struct _CtImDisp2e 						CtImDisp2e;
typedef struct _CtImDisp2eClass 				CtImDisp2eClass;
typedef struct _CtImDisp2ePrivate 				CtImDisp2ePrivate;

struct _CtImDisp2e
{
	ImDisp2Parent parent;
	/*public*/
};

struct _CtImDisp2eClass
{
	ImDisp2ParentClass parentclass;
};

/*
 * 如下开始public方法声明
 * */
GType 					ct_im_disp2e_get_type(void) G_GNUC_CONST;
CtImDisp2e *		ct_im_disp2e_new(void);


G_END_DECLS

#endif /* __CT_IM_DISP2E_H__ */
