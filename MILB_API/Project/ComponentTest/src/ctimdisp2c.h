/*
 *ctimdisp2c.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-11
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP2C_H__
#define __CT_IM_DISP2C_H__

#include "imdisp2parent.h"

G_BEGIN_DECLS
/*
 * 以下开始宏声明
 * */
#define CT_TYPE_IM_DISP2C						(ct_im_disp2c_get_type ())
#define CT_IM_DISP2C(widget)						(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
		CT_TYPE_IM_DISP2C, CtImDisp2c))
#define CT_IM_DISP2C_CLASS(klass)				(G_TYPE_CHECK_CLASS_CAST ((klass), \
		CT_TYPE_IM_DISP2C, CtImDisp2cClass))
#define CT_IS_IM_DISP2C(widget)				(G_TYPE_CHECK_INSTANCE_TYPE ((widget), CT_TYPE_IM_DISP2C))
#define CT_IS_IM_DISP2C_CLASS(klass)		(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_DISP2C))
#define CT_IM_DISP2C_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS ((obj), \
		CT_TYPE_IM_DISP2C, CtImDisp2cClass))

/*
 * 以下开始类结构体声明
 * */
typedef struct _CtImDisp2c 					CtImDisp2c;
typedef struct _CtImDisp2cClass 				CtImDisp2cClass;
typedef struct _CtImDisp2cPrivate 			CtImDisp2cPrivate;

struct _CtImDisp2c
{
	ImDisp2Parent parent;
	/*public*/
	CtImDisp2cPrivate *privCtImDisp2c;
};

struct _CtImDisp2cClass
{
	ImDisp2ParentClass parentclass;
};

/*
 * 如下开始public方法声明
 * */
GType 					ct_im_disp2c_get_type(void) G_GNUC_CONST;
CtImDisp2c *		ct_im_disp2c_new(void);

G_END_DECLS

#endif /* __CT_IM_DISP2C_H__ */
