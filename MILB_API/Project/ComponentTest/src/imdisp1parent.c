/*
*imdisp1parent.c
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-08
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#include "driver_common.h"//Ddim_Print
#include "imdisp1parent.h"

K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(ImDisp1Parent, im_disp1_parent, K_TYPE_OBJECT)
#define IM_DISP1_PARENT_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), ImDisp1ParentPrivate, IM_TYPE_DISP1_PARENT))

struct _ImDisp1ParentPrivate
{
	kpointer qwertyu;
	ImDisp1Parent *pNext;
	ImDisp1Parent *pPre;
	PctestWrapFunc wrapFunc;
	CtImDisp *wrapObj;
	KObject *imDisp1Group;
};

/*
 * DECLS
 * */
static void imDisp1ParentAddPre(ImDisp1Parent *self, ImDisp1Parent *pPre);

/*
 * IMPL
 * */
static void im_disp1_parent_constructor(ImDisp1Parent *self)
{
	ImDisp1ParentPrivate *priv = IM_DISP1_PARENT_GET_PRIVATE(self);
	self->privImDisp1Parent = priv;
	self->pctestFunc = NULL;
	priv->pNext = NULL;
	priv->pPre = NULL;
	priv->wrapFunc = NULL;
	priv->wrapObj = NULL;
	priv->imDisp1Group = NULL;
}

static void im_disp1_parent_destructor(ImDisp1Parent *self)
{
	ImDisp1ParentPrivate *priv = self->privImDisp1Parent;
	if (priv->pNext)
	{
		k_object_unref(priv->pNext);
		priv->pNext = NULL;
	}

	if (priv->pPre)
	{
		k_object_unref(priv->pPre);
		priv->pPre = NULL;
	}

	if (priv->wrapObj)
	{
		k_object_unref(priv->wrapObj);
		priv->wrapObj = NULL;
	}

	if (priv->imDisp1Group)
	{
		k_object_unref(priv->imDisp1Group);
		priv->imDisp1Group = NULL;
	}
}

static void imDisp1ParentAddPre(ImDisp1Parent *self, ImDisp1Parent *pPre)
{
	ImDisp1ParentPrivate *priv = self->privImDisp1Parent;
	if(pPre && IM_IS_DISP1_PARENT(pPre))
	{
		priv->pPre = k_object_ref(pPre);
	}
}

/*
 * PUBLIC
 * */
kboolean im_disp1_parent_do_pctest(ImDisp1Parent *self, kint32 *pSeqNo)
{
	if(self->pctestFunc)
	{
		return self->pctestFunc(self, pSeqNo);
	}

	Ddim_Print(("!! ImDisp1Parent:%p  pctestFunc NULL: %s (%d)", self->parent.string, __FILE__, __LINE__));
	return kfalse;
}

void im_disp1_parent_add_next(ImDisp1Parent *self, ImDisp1Parent *pNext)
{
	ImDisp1ParentPrivate *priv = self->privImDisp1Parent;
	if(pNext && IM_IS_DISP1_PARENT(pNext))
	{
		priv->pNext = k_object_ref(pNext);
		imDisp1ParentAddPre(pNext, self);
	}
}

void im_disp1_parent_set_pctest_wrap_func(ImDisp1Parent *self, PctestWrapFunc func, KObject *obj)
{
	ImDisp1ParentPrivate *priv = self->privImDisp1Parent;
	if( IM_IS_DISP1_PARENT(self) && !priv->wrapFunc )
	{
		priv->wrapFunc = func;
		priv->wrapObj = k_object_ref(obj);
		if(priv->pNext)
		{
			im_disp1_parent_set_pctest_wrap_func(priv->pNext, func, obj);
		}
	}
}

void im_disp1_parent_pctest_wrap(ImDisp1Parent *self, char *cmd)
{
	ImDisp1ParentPrivate *priv = self->privImDisp1Parent;
	kint32 argc = 0;
	char *argv[32];
	char arg[32][32];
	kint32 pos = 0;
	kint32 len = 0;
	kint32 max = strlen(cmd);
	kint32 i;

	printf("CMD> %s\n", cmd);

	// Clear arg buffer
	for(i = 0; i < 32; i++){
		argv[i] = arg[i];
		memset(argv[i], 0, 32);
	}

	// Set arg buffer
	for(i = 0; i < max; i++){
		if(cmd[i] == ' '){
			if(len){
				memcpy(argv[argc], &cmd[pos], len);
				argc++;
				len = 0;
			}
			pos = i + 1;
		}
		else if(i == max - 1){
			memcpy(argv[argc], &cmd[pos], len + 1);
			argc++;
			len = 0;
			pos = i + 1;
		}
		else{
			len++;
		}
	}

	// Execute command
//	ct_im_disp_main_cb(NULL, argc, argv);//TODO
	if(IM_IS_DISP1_PARENT(self) && priv->wrapObj)
	{
		priv->wrapFunc(priv->wrapObj, argc, argv);
	}
}

void im_disp1_parent_set_group(ImDisp1Parent *self, KObject *group)
{
	if (self && group && IM_IS_DISP1_PARENT(self))
	{
		ImDisp1ParentPrivate *priv = self->privImDisp1Parent;
		priv->imDisp1Group = group;
	}
}

KObject * im_disp1_parent_get_group(ImDisp1Parent *self)
{
	if (self && IM_IS_DISP1_PARENT(self))
	{
		ImDisp1ParentPrivate *priv = self->privImDisp1Parent;
		return priv->imDisp1Group;
	}else{
//		Ddim_Print(("!! ImDisp2Parent:%p  group NULL: %s (%d)", self->parent.string, __FILE__, __LINE__));
		return NULL;
	}
}
