/*
 *imdisp1parent.c
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-11
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

/*
 * 以下开始include语句
 * */
#include "driver_common.h"
#include "imdisp1parent.h"

/*
 * G_DEFINE_语句
 * */
G_DEFINE_TYPE (ImDisp1Parent, im_disp1_parent, G_TYPE_OBJECT);

/*
 * 以下开始宏定义
 * */
#define IM_DISP1_PARENT_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), \
		IM_TYPE_DISP1_PARENT, ImDisp1ParentPrivate))

/*
 * 内部结构体或类型定义
 * */
struct _ImDisp1ParentPrivate
{
	gpointer qwertyu;
	ImDisp1Parent *pNext;
	ImDisp1Parent *pPre;
	PctestWrapFunc wrapFunc;
	CtImDisp *wrapObj;
	GObject *imDisp1Group;
};

/*
 * 文件级全局变量定义
 * */

/*
 * DECLS
 * */
static void dispose_od(GObject *object);
static void finalize_od(GObject *object);
static void imDisp1ParentAddPre(ImDisp1Parent *self, ImDisp1Parent *pPre);


/*
 * IMPL
 * */
static void im_disp1_parent_class_init(ImDisp1ParentClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(ImDisp1ParentPrivate));
}

static void im_disp1_parent_init(ImDisp1Parent *self)
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

static void dispose_od(GObject *object)
{
	ImDisp1Parent *self = IM_DISP1_PARENT(object);
//	ImDisp1ParentPrivate *priv = IM_DISP1_PARENT_GET_PRIVATE(self);
	ImDisp1ParentPrivate *priv = self->privImDisp1Parent;
	if (priv->pNext)
	{
		g_object_unref(priv->pNext);
		priv->pNext = NULL;
	}

	if (priv->pPre)
	{
		g_object_unref(priv->pPre);
		priv->pPre = NULL;
	}

	if (priv->wrapObj)
	{
		g_object_unref(priv->wrapObj);
		priv->wrapObj = NULL;
	}

	if (priv->imDisp1Group)
	{
		g_object_unref(priv->imDisp1Group);
		priv->imDisp1Group = NULL;
	}

	G_OBJECT_CLASS (im_disp1_parent_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
//	ImDisp1Parent *self = IM_DISP1_PARENT(object);
//	ImDisp1ParentPrivate *priv = IM_DISP1_PARENT_GET_PRIVATE(self);
	/*释放创建的内存2*/
//	if(self->name)
//	{
//		free(self->name);
//		self->name =NULL;
//	}
	G_OBJECT_CLASS (im_disp1_parent_parent_class)->finalize(object);
}

static void imDisp1ParentAddPre(ImDisp1Parent *self, ImDisp1Parent *pPre)
{
	ImDisp1ParentPrivate *priv = self->privImDisp1Parent;
	if(pPre && IM_IS_DISP1_PARENT(pPre))
	{
		priv->pPre = g_object_ref(pPre);
	}
}

/*
 * PUBLIC
 * */

gboolean im_disp1_parent_do_pctest(ImDisp1Parent *self, gint32 *pSeqNo)
{
	if(self->pctestFunc)
	{
		return self->pctestFunc(self, pSeqNo);
	}

	Ddim_Print(("!! ImDisp1Parent:%p  pctestFunc NULL: %s (%d)", self->parent.string, __FILE__, __LINE__));
	return gfalse;
}

void im_disp1_parent_add_next(ImDisp1Parent *self, ImDisp1Parent *pNext)
{
	ImDisp1ParentPrivate *priv = self->privImDisp1Parent;
	if(pNext && IM_IS_DISP1_PARENT(pNext))
	{
		priv->pNext = g_object_ref(pNext);
		imDisp1ParentAddPre(pNext, self);
	}
}

void im_disp1_parent_set_pctest_wrap_func(ImDisp1Parent *self, PctestWrapFunc func, GObject *obj)
{
	ImDisp1ParentPrivate *priv = self->privImDisp1Parent;
	if( IM_IS_DISP1_PARENT(self) && !priv->wrapFunc )
	{
		priv->wrapFunc = func;
		priv->wrapObj = g_object_ref(obj);
		if(priv->pNext)
		{
			im_disp1_parent_set_pctest_wrap_func(priv->pNext, func, obj);
		}
	}
}

void im_disp1_parent_pctest_wrap(ImDisp1Parent *self, char *cmd)
{
	ImDisp1ParentPrivate *priv = self->privImDisp1Parent;
	gint32 argc = 0;
	char *argv[32];
	char arg[32][32];
	gint32 pos = 0;
	gint32 len = 0;
	gint32 max = strlen(cmd);
	gint32 i;

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

void im_disp1_parent_set_group(ImDisp1Parent *self, GObject *group)
{
	if (self && group && IM_IS_DISP1_PARENT(self))
	{
		ImDisp1ParentPrivate *priv = self->privImDisp1Parent;
		priv->imDisp1Group = group;
	}
}

GObject * im_disp1_parent_get_group(ImDisp1Parent *self)
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
