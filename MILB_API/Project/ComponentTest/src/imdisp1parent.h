/*
 *imdisp1parent.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-08
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __IM_DISP1_PARENT_H__
#define __IM_DISP1_PARENT_H__

#include <klib.h>

#define IM_TYPE_DISP1_PARENT				(im_disp1_parent_get_type())
#define IM_DISP1_PARENT(obj)				(K_TYPE_CHECK_INSTANCE_CAST(obj, ImDisp1Parent))
#define IM_IS_DISP1_PARENT(obj)			K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_DISP1_PARENT)

typedef struct _ImDisp1Parent 				ImDisp1Parent;
typedef struct _ImDisp1ParentPrivate		ImDisp1ParentPrivate;
typedef struct _CtImDisp 						CtImDisp;

typedef kboolean (*ImDisp1PctestFunc)(ImDisp1Parent *parent, kint32 *pSeqNo);
typedef void (*PctestWrapFunc)(CtImDisp *wrapObject, kint32 argc, char **argv);
//typedef void (*PctestWrapFunc)(KObject *wrapObject, kint32 argc, char **argv);

struct _ImDisp1Parent{
	KObject parent;
	ImDisp1ParentPrivate *privImDisp1Parent;
	ImDisp1PctestFunc pctestFunc;
};

KConstType 	im_disp1_parent_get_type(void);

kboolean		im_disp1_parent_do_pctest(ImDisp1Parent *self, kint32 *pSeqNo);
void 			im_disp1_parent_add_next(ImDisp1Parent *self, ImDisp1Parent *pNext);
void 			im_disp1_parent_set_pctest_wrap_func(ImDisp1Parent *self,
							PctestWrapFunc func, KObject *obj);
void 			im_disp1_parent_pctest_wrap(ImDisp1Parent *self, char *cmd);
void 			im_disp1_parent_set_group(ImDisp1Parent *self, KObject *group);
KObject *		im_disp1_parent_get_group(ImDisp1Parent *self);

#endif /* __IM_DISP1_PARENT_H__ */
