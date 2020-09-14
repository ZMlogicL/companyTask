/*
 *imdisp2parent.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-11
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __IM_DISP2_PARENT_H__
#define __IM_DISP2_PARENT_H__

#include <glib-object.h>

G_BEGIN_DECLS
/*
 * 以下开始宏声明
 * */
#define IM_TYPE_DISP2_PARENT					(im_disp2_parent_get_type())
#define IM_DISP2_PARENT(widget)				(G_TYPE_CHECK_INSTANCE_CAST((widget), \
							IM_TYPE_DISP2_PARENT, ImDisp2Parent))
#define IM_DISP2_PARENT_CLASS(klass)		(G_TYPE_CHECK_CLASS_CAST((klass), \
							IM_TYPE_DISP2_PARENT, ImDisp2ParentClass))
#define IM_IS_DISP2_PARENT(widget)			(G_TYPE_CHECK_INSTANCE_TYPE((widget), IM_TYPE_DISP2_PARENT))
#define IM_IS_DISP2_PARENT_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE((klass), IM_TYPE_DISP2_PARENT))
#define IM_DISP2_PARENT_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS((obj), \
							IM_TYPE_DISP2_PARENT, ImDisp2ParentClass))

/*
 * 以下开始类结构体声明
 * */
typedef struct _ImDisp2Parent 					ImDisp2Parent;
typedef struct _ImDisp2ParentClass 			ImDisp2ParentClass;
typedef struct _ImDisp2ParentPrivate 		ImDisp2ParentPrivate;

typedef void (*ImDisp2xMainDoFunc)(ImDisp2Parent *self, gint32 argc, char **argv);

struct _ImDisp2Parent
{
	GObject parent;
	/*public*/
	ImDisp2ParentPrivate *privImDisp2Parent;
	ImDisp2xMainDoFunc doMainFunc;
};

struct _ImDisp2ParentClass
{
	GObjectClass parentclass;
};

/*
 * 如下开始public方法声明
 * */
GType 				im_disp2_parent_get_type(void) G_GNUC_CONST;

void 				im_disp2_parent_do_main(ImDisp2Parent *self, gint32 argc, char **argv);
void 				im_disp2_parent_set_group(ImDisp2Parent *self, GObject *group);
GObject *			im_disp2_parent_get_group(ImDisp2Parent *self);

G_END_DECLS

#endif /* __IM_DISP2_PARENT_H__ */
