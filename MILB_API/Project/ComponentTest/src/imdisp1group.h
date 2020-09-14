/*
 *imdisp1group.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-08
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __IM_DISP1_GROUP_H__
#define __IM_DISP1_GROUP_H__

#include "imdisp1parent.h"

G_BEGIN_DECLS
/*
 * 以下开始宏声明
 * */
#define IM_TYPE_DISP1_GROUP						(im_disp1_group_get_type())
#define IM_DISP1_GROUP(widget)					(G_TYPE_CHECK_INSTANCE_CAST((widget), \
		IM_TYPE_DISP1_GROUP, ImDisp1Group))
#define IM_DISP1_GROUP_CLASS(klass)			(G_TYPE_CHECK_CLASS_CAST((klass), \
		IM_TYPE_DISP1_GROUP, ImDisp1GroupClass))
#define IM_IS_DISP1_GROUP(widget)				(G_TYPE_CHECK_INSTANCE_TYPE((widget), IM_TYPE_DISP1_GROUP))
#define IM_IS_DISP1_GROUP_CLASS(klass)		(G_TYPE_CHECK_CLASS_TYPE((klass), IM_TYPE_DISP1_GROUP))
#define IM_DISP1_GROUP_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS((obj), \
		IM_TYPE_DISP1_GROUP, ImDisp1GroupClass))

/*
 * 以下开始类结构体声明
 * */
typedef struct _ImDisp1Group 			ImDisp1Group;
typedef struct _ImDisp1GroupClass 	ImDisp1GroupClass;
typedef struct _ImDisp1GroupPrivate 	ImDisp1GroupPrivate;

struct _ImDisp1Group
{
	GObject parent;
	ImDisp1GroupPrivate *privImDisp1Group;
	/*public*/
};

struct _ImDisp1GroupClass
{
	GObjectClass parentclass;
};

/*
 * 如下开始public方法声明
 * */
GType 					im_disp1_group_get_type(void) G_GNUC_CONST;
ImDisp1Group *	im_disp1_group_new(guchar *pclkCounter, guchar *hclkCounter);

ImDisp1Parent *	im_disp1_group_get_pctest_instance(ImDisp1Group *self);
guchar *				im_disp1_group_get_pclk_counter(ImDisp1Group *self);
guchar *				im_disp1_group_get_hclk_counter(ImDisp1Group *self);
void 					im_disp1_group_ct_im_disp3_pclk_counter_on(ImDisp1Group *self);
void 					im_disp1_group_ct_im_disp3_pclk_counter_off(ImDisp1Group *self);


G_END_DECLS

#endif /* __IM_DISP1_GROUP_H__ */
