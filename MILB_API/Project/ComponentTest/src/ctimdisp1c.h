/*
 *ctimdisp1c.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-11
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP1C_H__
#define __CT_IM_DISP1C_H__

#include "imdisp1parent.h"

G_BEGIN_DECLS
/*
 * 以下开始宏声明
 * */
#define CT_TYPE_IM_DISP1C					(ct_im_disp1c_get_type ())
#define CT_IM_DISP1C(widget)					(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
					CT_TYPE_IM_DISP1C, CtImDisp1c))
#define CT_IM_DISP1C_CLASS(klass)			(G_TYPE_CHECK_CLASS_CAST ((klass), \
					CT_TYPE_IM_DISP1C, CtImDisp1cClass))
#define CT_IS_IM_DISP1C(widget)			(G_TYPE_CHECK_INSTANCE_TYPE ((widget), CT_TYPE_IM_DISP1C))
#define CT_IS_IM_DISP1C_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_DISP1C))
#define CT_IM_DISP1C_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS ((obj), \
					CT_TYPE_IM_DISP1C, CtImDisp1cClass))

/*
 * 以下开始类结构体声明
 * */
typedef struct _CtImDisp1c 		CtImDisp1c;
typedef struct _CtImDisp1cClass 	CtImDisp1cClass;
typedef struct _CtImDisp1cPrivate 	CtImDisp1cPrivate;

struct _CtImDisp1c
{
	ImDisp1Parent parent;
	/*public*/
};

struct _CtImDisp1cClass
{
	ImDisp1ParentClass parentclass;
};

/*
 * 如下开始public方法声明
 * */
GType 					ct_im_disp1c_get_type(void) G_GNUC_CONST;
CtImDisp1c *		ct_im_disp1c_new(void);

G_END_DECLS

#endif /* __CT_IM_DISP1C_H__ */
