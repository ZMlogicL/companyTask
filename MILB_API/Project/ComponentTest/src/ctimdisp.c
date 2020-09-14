/*
 *ctimdisp.c
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-11
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

/**
 * @file		ct_im_disp.c
 * @brief		This is ct code for im_disp.c.
 * @note		None
 * @attention	None
 *
 * <B><I>ALL RIGHTS RESERVED, COPYRIGHT&copy; SOCIONEXT INCORPORATED 2015</I></B>
 */
/*
 * 以下开始include语句
 * */
#include <stdlib.h>
#include <string.h>
#include "im_disp.h"
#include "dd_top.h"
#include "ddim_user_custom.h"
#include "jdsdisp3a.h"

#include "ctimdisp3.h"
#include "ctimdisp3a.h"
#include "imdisp1group.h"
#include "imdisp2group.h"
#include "ctimdisp.h"//already define CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING

/*
 * G_DEFINE_语句
 * */
G_DEFINE_TYPE (CtImDisp, ct_im_disp, G_TYPE_OBJECT);

/*
 * 以下开始宏定义
 * */
#define CT_IM_DISP_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), CT_TYPE_IM_DISP, CtImDispPrivate))
#define CtImDisp_IMDISP_MAIN_DO_MAX_CNT  (50)//

//#define CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
//#define CO_DEBUG_ON_PC

/*
 * 内部结构体或类型定义
 * */
struct _CtImDispPrivate
{
	ImDisp1Group *imDisp1Group;
	ImDisp2Group *imDisp2Group;
	GObject *mainObjectList[CtImDisp_IMDISP_MAIN_DO_MAX_CNT];
	// PCLK_Disp setting task counter (0~255)
	volatile guchar gImDispPclkCounter;
	// HCLK_Disp setting task counter (0~255)
	volatile guchar gImDispHclkCounter;

	CtImDisp3 *ctImDisp3;
	CtImDisp3a *ctImDisp3a;
};

/*
 * 文件级全局变量定义
 * */

static ImDisp2GroupDoMainType S_DISP2_MAIN_GROUP_TYPE[] =
{
	ImDisp2Group_DO_IM_DISP_TEST,
	ImDisp2Group_DO_IM_DISP_TEST_A,
//	ImDisp2Group_DO_IM_DISP_TEST_B,//由a来调用
	ImDisp2Group_DO_IM_DISP_TEST_C,
	ImDisp2Group_DO_IM_DISP_TEST_D,
	ImDisp2Group_DO_IM_DISP_TEST_E,
	ImDisp2Group_DO_IM_DISP_TEST_F,
	ImDisp2Group_DO_IM_DISP_TEST_G,
	ImDisp2Group_DO_IM_DISP_TEST_H,
	ImDisp2Group_DO_IM_DISP_TEST_I,
	ImDisp2Group_DO_IM_DISP_TEST_J,
	ImDisp2Group_DO_IM_DISP_TEST_K,
	ImDisp2Group_DO_IM_DISP_TEST_L,
	ImDisp2Group_DO_IM_DISP_TEST_M,
	ImDisp2Group_DO_IM_DISP_TEST_N,
	ImDisp2Group_DO_IM_DISP_TEST_O,
};

/*
 * DECLS
 * */
static void dispose_od(GObject *object);
static void finalize_od(GObject *object);
static gint addMainObjectList(CtImDisp *self, GObject *element);
static void initDispMain(CtImDisp *self);
static void doAllDispMain(CtImDisp *self, gint32 argc, char **argv);

/*
 * IMPL
 * */
static void ct_im_disp_class_init(CtImDispClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtImDispPrivate));
}

static void ct_im_disp_init(CtImDisp *self)
{
	CtImDispPrivate *priv = CT_IM_DISP_GET_PRIVATE(self);
	self->privCtImDisp = priv;
	memset(priv->mainObjectList, 0, sizeof(priv->mainObjectList));//初始化 NULL
	priv->imDisp1Group = NULL;
	priv->imDisp2Group = NULL;

	priv->ctImDisp3 = ct_im_disp3_new((guchar *)&priv->gImDispPclkCounter,
			(guchar *)&priv->gImDispPclkCounter);
	priv->ctImDisp3a = ct_im_disp3a_new((guchar *)&priv->gImDispPclkCounter,
			(guchar *)&priv->gImDispPclkCounter);
}

static void dispose_od(GObject *object)
{
	CtImDisp *self = CT_IM_DISP(object);
	CtImDispPrivate *priv = self->privCtImDisp;
	gint index = 0;

	if (priv->imDisp1Group)
	{
		g_object_unref(priv->imDisp1Group);
		priv->imDisp1Group = NULL;
	}

	if (priv->imDisp2Group)
	{
		g_object_unref(priv->imDisp2Group);
		priv->imDisp2Group = NULL;
	}

	for(index=0;index <CtImDisp_IMDISP_MAIN_DO_MAX_CNT; index++)
	{
		GObject *element = priv->mainObjectList[index];
		if(element )
		{
			g_object_unref(element);
			priv->mainObjectList[index] = NULL;
		}
	}

	G_OBJECT_CLASS (ct_im_disp_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
//	CtImDisp *self = CT_IM_DISP(object);
//	CtImDispPrivate *priv = CT_IM_DISP_GET_PRIVATE(self);
	/*释放创建的内存2*/
//	if(self->name)
//	{
//		free(self->name);
//		self->name =NULL;
//	}
	G_OBJECT_CLASS (ct_im_disp_parent_class)->finalize(object);
}

static gboolean addMainObjectList(CtImDisp *self, GObject *element)
{
	CtImDispPrivate *priv = self->privCtImDisp;
	gint index = 0;
	for(index=0;index <CtImDisp_IMDISP_MAIN_DO_MAX_CNT; index++)
	{
		if(NULL == priv->mainObjectList[index] )
		{
			priv->mainObjectList[index] = element;
			return gtrue;
		}
	}
	return gfalse;
}

static void initDispMain(CtImDisp *self)
{
	ImDisp2GroupDoMainType loopType = ImDisp2Group_DO_IM_DISP_TEST;
	gint loopIndex = 0;

	CtImDispPrivate *priv = self->privCtImDisp;
	ImDisp2Group *imDisp2Group = im_disp2_group_new(
			(guchar *)&priv->gImDispPclkCounter, (guchar *)&priv->gImDispPclkCounter);

	priv->imDisp2Group = imDisp2Group;
	for (loopIndex = 0; loopIndex < CtImDisp_IMDISP_MAIN_DO_MAX_CNT; loopIndex++)
	{
		loopType = S_DISP2_MAIN_GROUP_TYPE[loopIndex];
		ImDisp2Parent *imDisp2Parent = im_disp2_group_create_im_disp(imDisp2Group, loopType, (GData)self);
		if(imDisp2Parent)
		{
			if(gtrue == addMainObjectList(self, (GObject *)imDisp2Parent))
			{//
				Ddim_Print(("------- Add Element  ok -------\n"));
			}else{
				Ddim_Print(("------- Add Element  failed -------\n"));
			}
		}
		if (loopType < ImDisp2Group_DO_IM_DISP_TEST || loopType >= ImDisp2Group_DO_IM_DISP_TEST_END)
		{
			break;
		}
	}
}

static void doAllDispMain(CtImDisp *self, gint32 argc, char **argv)
{
	CtImDispPrivate *priv = self->privCtImDisp;
	gint index = 0;
	for(index=0;index <CtImDisp_IMDISP_MAIN_DO_MAX_CNT; index++)
	{
		ImDisp2Parent *element = (ImDisp2Parent *)priv->mainObjectList[index] ;
		im_disp2_parent_do_main(element, argc, argv);
		if(NULL == priv->mainObjectList[index] )
		{
			priv->mainObjectList[index] = (GObject *)element;
			return ;
		}
	}
}

/*
 * PUBLIC
 * */
void ct_im_disp_pctest_main(CtImDisp *self)
{
#ifdef CtImDisp_CO_DEBUG_DISP
	CtImDispPrivate *priv = self->privCtImDisp;
	ImDisp1Group *imDisp1Group = im_disp1_group_new(
			(guchar *)&priv->gImDispPclkCounter, (guchar *)&priv->gImDispPclkCounter);
	ImDisp1Parent *fistDisp1ParentInstance = im_disp1_group_get_pctest_instance(imDisp1Group);
	gint32 seqNo = 1;

	im_disp1_parent_set_pctest_wrap_func(fistDisp1ParentInstance, ct_im_disp_main_cb, (GObject *)self);
	priv->imDisp1Group = imDisp1Group;

	if(gfalse == im_disp1_parent_do_pctest(fistDisp1ParentInstance, &seqNo))
	{
		Ddim_Print(("do pctest error\n"));
	}
#endif /*CtImDisp_CO_DEBUG_DISP*/
}

void ct_im_disp_main_cb(CtImDisp *self, gint32 argc, char **argv)
{
#ifdef CtImDisp_CO_DEBUG_DISP
	if (argc > 1)
	{
		initDispMain(self);

		doAllDispMain(self, argc, argv);
		//endfor 	if (argc > 1)
	}
	else
	{
		Ddim_Print(("input parameter error\n"));
	}

	Ddim_Print(("*.. DISP CT command complete!\n"));
	Ddim_Print(("\n"));
	return;
#endif //CtImDisp_CO_DEBUG_DISP
}

guchar *ct_im_disp_get_pclk_counter(CtImDisp *self)
{
	CtImDispPrivate *priv = self->privCtImDisp;
	return (guchar *)&priv->gImDispPclkCounter;
}

guchar *ct_im_disp_get_hclk_counter(CtImDisp *self)
{
	CtImDispPrivate *priv = self->privCtImDisp;
	return (guchar *)&priv->gImDispHclkCounter;
}

CtImDisp *ct_im_disp_new(void)
{
	CtImDisp *self = (CtImDisp *) g_object_new(CT_TYPE_IM_DISP, NULL);
	return self;
}
