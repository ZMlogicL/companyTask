/*
 *ctimdisp1.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-11
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP1_H__
#define __CT_IM_DISP1_H__

#include "imdisp1parent.h"

G_BEGIN_DECLS
/*
 * 以下开始宏声明
 * */
#define CT_TYPE_IM_DISP1						(ct_im_disp1_get_type ())
#define CT_IM_DISP1(widget)					(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
					CT_TYPE_IM_DISP1, CtImDisp1))
#define CT_IM_DISP1_CLASS(klass)			(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_IM_DISP1, CtImDisp1Class))
#define CT_IS_IM_DISP1(widget)				(G_TYPE_CHECK_INSTANCE_TYPE ((widget), CT_TYPE_IM_DISP1))
#define CT_IS_IM_DISP1_CLASS(klass)		(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_DISP1))
#define CT_IM_DISP1_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_IM_DISP1, CtImDisp1Class))

/*
 * 以下开始类结构体声明
 * */
typedef struct _CtImDisp1 		CtImDisp1;
typedef struct _CtImDisp1Class 	CtImDisp1Class;
typedef struct _CtImDisp1Private 	CtImDisp1Private;

struct _CtImDisp1
{
	ImDisp1Parent parent;
	/*public*/
};

struct _CtImDisp1Class
{
	ImDisp1ParentClass parentclass;
};

/*
 * 如下开始public方法声明
 * */
GType 				ct_im_disp1_get_type(void) G_GNUC_CONST;
CtImDisp1 *		ct_im_disp1_new(void);


G_END_DECLS

#endif /* __CT_IM_DISP1_H__ */
