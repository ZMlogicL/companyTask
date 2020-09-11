/*
 *imdisp2parent.c
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-07
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#include "imdisp2parent.h"

K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(ImDisp2Parent, im_disp2_parent, K_TYPE_OBJECT)
#define IM_DISP2_PARENT_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), ImDisp2ParentPrivate, IM_TYPE_DISP2_PARENT))

struct _ImDisp2ParentPrivate
{
//	kpointer qwertyu;
	KObject *imDisp2Group;
};

/*
 * DECLS
 * */


/*
 * IMPL
 * */
static void im_disp2_parent_constructor(ImDisp2Parent *self)
{
	ImDisp2ParentPrivate *priv = IM_DISP2_PARENT_GET_PRIVATE(self);
	self->privImDisp2Parent = priv;
	self->doMainFunc = NULL;
	priv->imDisp2Group = NULL;
}

static void im_disp2_parent_destructor(ImDisp2Parent *self)
{
	ImDisp2ParentPrivate *priv = self->privImDisp2Parent;
	if (priv->imDisp2Group)
	{
		k_object_unref(priv->imDisp2Group);
		priv->imDisp2Group = NULL;
	}
}

/*
 * PUBLIC
 * */
void im_disp2_parent_do_main(ImDisp2Parent *self, kint32 argc, char **argv)
{
	if(self->doMainFunc){
		self->doMainFunc(self, argc, argv);
	}
}

void im_disp2_parent_set_group(ImDisp2Parent *self, KObject *group)
{
	if (self && group && IM_IS_DISP2_PARENT(self))
	{
		ImDisp2ParentPrivate *priv = self->privImDisp2Parent;
		priv->imDisp2Group = k_object_ref(group);
	}
}

KObject *im_disp2_parent_get_group(ImDisp2Parent *self)
{
	if (self && IM_IS_DISP2_PARENT(self))
	{
		ImDisp2ParentPrivate *priv = self->privImDisp2Parent;
		return priv->imDisp2Group;
	}else{
//		Ddim_Print(("!! ImDisp2Parent:%p  group NULL: %s (%d)", self->parent.string, __FILE__, __LINE__));
		return NULL;
	}
}
