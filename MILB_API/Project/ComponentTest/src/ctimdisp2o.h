/*
 *ctimdisp2o.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-11
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP2O_H__
#define __CT_IM_DISP2O_H__

#include "imdisp2parent.h"

G_BEGIN_DECLS
/*
 * 以下开始宏声明
 * */
#define CT_TYPE_IM_DISP2O						(ct_im_disp2o_get_type ())
#define CT_IM_DISP2O(widget)					(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
		CT_TYPE_IM_DISP2O, CtImDisp2o))
#define CT_IM_DISP2O_CLASS(klass)			(G_TYPE_CHECK_CLASS_CAST ((klass), \
		CT_TYPE_IM_DISP2O, CtImDisp2oClass))
#define CT_IS_IM_DISP2O(widget)				(G_TYPE_CHECK_INSTANCE_TYPE ((widget), CT_TYPE_IM_DISP2O))
#define CT_IS_IM_DISP2O_CLASS(klass)		(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_DISP2O))
#define CT_IM_DISP2O_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS ((obj), \
		CT_TYPE_IM_DISP2O, CtImDisp2oClass))

/*
 * 以下开始类结构体声明
 * */
typedef struct _CtImDisp2o 						CtImDisp2o;
typedef struct _CtImDisp2oClass 				CtImDisp2oClass;
typedef struct _CtImDisp2oPrivate 				CtImDisp2oPrivate;

struct _CtImDisp2o
{
	ImDisp2Parent parent;
	/*public*/
	gpointer privCtImDisp2o;
};

struct _CtImDisp2oClass
{
	ImDisp2ParentClass parentclass;
};

/*
 * 如下开始public方法声明
 * */
GType 					ct_im_disp2o_get_type(void) G_GNUC_CONST;
CtImDisp2o *		ct_im_disp2o_new(void);


G_END_DECLS

#endif /* __CT_IM_DISP2O_H__ */
