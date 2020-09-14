/*
 *imdisp1parent.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-11
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __IM_DISP1_PARENT_H__
#define __IM_DISP1_PARENT_H__

#include <glib-object.h>

G_BEGIN_DECLS
/*
 * 以下开始宏声明
 * */
#define IM_TYPE_DISP1_PARENT					(im_disp1_parent_get_type())
#define IM_DISP1_PARENT(widget)				(G_TYPE_CHECK_INSTANCE_CAST((widget), \
		IM_TYPE_DISP1_PARENT, ImDisp1Parent))
#define IM_DISP1_PARENT_CLASS(klass)		(G_TYPE_CHECK_CLASS_CAST((klass), \
		IM_TYPE_DISP1_PARENT, ImDisp1ParentClass))
#define IM_IS_DISP1_PARENT(widget)			(G_TYPE_CHECK_INSTANCE_TYPE((widget), IM_TYPE_DISP1_PARENT))
#define IM_IS_DISP1_PARENT_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE((klass), IM_TYPE_DISP1_PARENT))
#define IM_DISP1_PARENT_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS((obj), \
		IM_TYPE_DISP1_PARENT, ImDisp1ParentClass))

/*
 * 以下开始类结构体声明
 * */
typedef struct _ImDisp1Parent 				ImDisp1Parent;
typedef struct _ImDisp1ParentClass 		ImDisp1ParentClass;
typedef struct _ImDisp1ParentPrivate 	ImDisp1ParentPrivate;
typedef struct _CtImDisp 						CtImDisp;

typedef gboolean (*ImDisp1PctestFunc)(ImDisp1Parent *parent, gint32 *pSeqNo);
typedef void (*PctestWrapFunc)(CtImDisp *wrapObject, gint32 argc, char **argv);

struct _ImDisp1Parent
{
	GObject parent;
	/*public*/
	ImDisp1ParentPrivate *privImDisp1Parent;
	ImDisp1PctestFunc pctestFunc;
};

struct _ImDisp1ParentClass
{
	GObjectClass parentclass;
};

/*
 * 如下开始public方法声明
 * */
GType 			im_disp1_parent_get_type(void) G_GNUC_CONST;
gboolean		im_disp1_parent_do_pctest(ImDisp1Parent *self, gint32 *pSeqNo);
void 			im_disp1_parent_add_next(ImDisp1Parent *self, ImDisp1Parent *pNext);
void 			im_disp1_parent_set_pctest_wrap_func(ImDisp1Parent *self,
							PctestWrapFunc func, GObject *obj);
void 			im_disp1_parent_pctest_wrap(ImDisp1Parent *self, char *cmd);
void 			im_disp1_parent_set_group(ImDisp1Parent *self, GObject *group);
GObject *		im_disp1_parent_get_group(ImDisp1Parent *self);


G_END_DECLS

#endif /* __IM_DISP1_PARENT_H__ */
