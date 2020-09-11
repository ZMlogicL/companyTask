/*
 *imdisp2parent.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-07
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __IM_DISP2_PARENT_H__
#define __IM_DISP2_PARENT_H__

#include <klib.h>

#define IM_TYPE_DISP2_PARENT	(im_disp2_parent_get_type())
#define IM_DISP2_PARENT(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImDisp2Parent))
#define IM_IS_DISP2_PARENT(obj)			K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_DISP2_PARENT)

typedef struct _ImDisp2Parent ImDisp2Parent;
typedef struct _ImDisp2ParentPrivate		ImDisp2ParentPrivate;

typedef void (*ImDisp2xMainDoFunc)(ImDisp2Parent *self, kint32 argc, char **argv);

struct _ImDisp2Parent{
	KObject parent;
	ImDisp2ParentPrivate *privImDisp2Parent;
	ImDisp2xMainDoFunc doMainFunc;
};

KConstType 		im_disp2_parent_get_type(void);

void 				im_disp2_parent_do_main(ImDisp2Parent *self, kint32 argc, char **argv);
void 				im_disp2_parent_set_group(ImDisp2Parent *self, KObject *group);
KObject *			im_disp2_parent_get_group(ImDisp2Parent *self);

#endif /* __IM_DISP2_PARENT_H__ */
