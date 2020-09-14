/*
 *ctimdisp4.c
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
#include <stdlib.h>
#include <string.h>
#include "im_disp.h"
#include "dd_top.h"
#include "ddim_user_custom.h"
#include "jdsdisp3a.h"

#include "ctimdisp.h"//already define CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
#include "ct_im_disptbl_define.h"
#include "ct_im_disp_define.h"//CO_IO_DISP_DEFINE

#include "ctimdisp3.h"
#include "ctimdisp4.h"

/*
 * G_DEFINE_语句
 * */
G_DEFINE_TYPE (CtImDisp4, ct_im_disp4, G_TYPE_OBJECT);

/*
 * 以下开始宏定义
 * */
#define CT_IM_DISP4_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), CT_TYPE_IM_DISP4, CtImDisp4Private))

/*
 * 内部结构体或类型定义
 * */
struct _CtImDisp4Private
{
	T_IM_DISP_CTRL_OUTPUT gLcdDispTblOutctrl[CtImDisp4_LCD_DISP_SEL_END];
	guint32 rAntiTblA[32/2];//2m
	guint32 gAntiTblA[32/2];//2m
	guint32 bAntiTblA[32/2];//2m
	gushort rGammaOutTblA[33];//2m
	gushort gGammaOutTblA[33];//2m
	gushort bGammaOutTblA[33];//2m
	gushort rGammaOutTblB[33];//2m
	gushort gGammaOutTblB[33];//2m
	gushort bGammaOutTblB[33];//2m
	guint32 rFullTbl[32/2];//2m
	guint32 gFullTbl[32/2];//2m
	guint32 bFullTbl[32/2];//2m
	gushort luminanceTblA[33];//2m
	gushort luminanceTblB[33];//2m
	gushort gainTblA[33];//2n
	gushort gainTblB[33];//2n
};

/*
 * 文件级全局变量定义
 * */

/*
 * DECLS
 * */
static void dispose_od(GObject *object);
static void finalize_od(GObject *object);
static void initAntiTabl(CtImDisp4 *self);
static void initGammaOutTabl(CtImDisp4 *self);
static void initFullTabl(CtImDisp4 *self);
static void initLuminanceTbl(CtImDisp4 *self);
static void initGainTabl(CtImDisp4 *self);

/*
 * IMPL
 * */
static void ct_im_disp4_class_init(CtImDisp4Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtImDisp4Private));
}

static void ct_im_disp4_init(CtImDisp4 *self)
{
	CtImDisp4Private *priv = CT_IM_DISP4_GET_PRIVATE(self);
	self->privCtImDisp4 = priv;

	initAntiTabl(self);
	initGammaOutTabl(self);
	initFullTabl(self);
	initLuminanceTbl(self);
	initGainTabl(self);
}

static void dispose_od(GObject *object)
{
//	CtImDisp4 *self = CT_IM_DISP4(object);
//	CtImDisp4Private *priv = CT_IM_DISP4_GET_PRIVATE(self);
	/*释放创建的对象1*/
//	if (priv->objectMine) {
//		g_object_unref(priv->objectMine);
//		priv->objectMine = NULL;
//	}
	G_OBJECT_CLASS (ct_im_disp4_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
//	CtImDisp4 *self = CT_IM_DISP4(object);
//	CtImDisp4Private *priv = CT_IM_DISP4_GET_PRIVATE(self);
	/*释放创建的内存2*/
//	if(self->name)
//	{
//		free(self->name);
//		self->name =NULL;
//	}
	G_OBJECT_CLASS (ct_im_disp4_parent_class)->finalize(object);
}

static void initAntiTabl(CtImDisp4 *self)
{
	CtImDisp4Private *priv = self->privCtImDisp4;

	// Pointer of R data anti gamma table A.<br>
	//	Please specify the address of the array of gushort[32].<br>
	//	If NULL is specified, this setting is skipped.<br>
	guint32 rAntiTblA[32/2] = {
		DISP_TBL_REVERSE_IGTBLR0	,
		DISP_TBL_REVERSE_IGTBLR1	,
		DISP_TBL_REVERSE_IGTBLR2	,
		DISP_TBL_REVERSE_IGTBLR3	,
		DISP_TBL_REVERSE_IGTBLR4	,
		DISP_TBL_REVERSE_IGTBLR5	,
		DISP_TBL_REVERSE_IGTBLR6	,
		DISP_TBL_REVERSE_IGTBLR7	,
		DISP_TBL_REVERSE_IGTBLR8	,
		DISP_TBL_REVERSE_IGTBLR9	,
		DISP_TBL_REVERSE_IGTBLR10	,
		DISP_TBL_REVERSE_IGTBLR11	,
		DISP_TBL_REVERSE_IGTBLR12	,
		DISP_TBL_REVERSE_IGTBLR13	,
		DISP_TBL_REVERSE_IGTBLR14	,
		DISP_TBL_REVERSE_IGTBLR15
	};

	// Pointer of G data anti gamma table A.<br>
	//	Please specify the address of the array of gushort[32].<br>
	//	If NULL is specified, this setting is skipped.<br>
	guint32 gAntiTblA[32/2] = {
		DISP_TBL_REVERSE_IGTBLG0	,
		DISP_TBL_REVERSE_IGTBLG1	,
		DISP_TBL_REVERSE_IGTBLG2	,
		DISP_TBL_REVERSE_IGTBLG3	,
		DISP_TBL_REVERSE_IGTBLG4	,
		DISP_TBL_REVERSE_IGTBLG5	,
		DISP_TBL_REVERSE_IGTBLG6	,
		DISP_TBL_REVERSE_IGTBLG7	,
		DISP_TBL_REVERSE_IGTBLG8	,
		DISP_TBL_REVERSE_IGTBLG9	,
		DISP_TBL_REVERSE_IGTBLG10	,
		DISP_TBL_REVERSE_IGTBLG11	,
		DISP_TBL_REVERSE_IGTBLG12	,
		DISP_TBL_REVERSE_IGTBLG13	,
		DISP_TBL_REVERSE_IGTBLG14	,
		DISP_TBL_REVERSE_IGTBLG15
	};

	// Pointer of B data anti gamma table A.<br>
	//	Please specify the address of the array of gushort[32].<br>
	//	If NULL is specified, this setting is skipped.<br>
	guint32 bAntiTblA[32/2] = {
		DISP_TBL_REVERSE_IGTBLB0	,
		DISP_TBL_REVERSE_IGTBLB1	,
		DISP_TBL_REVERSE_IGTBLB2	,
		DISP_TBL_REVERSE_IGTBLB3	,
		DISP_TBL_REVERSE_IGTBLB4	,
		DISP_TBL_REVERSE_IGTBLB5	,
		DISP_TBL_REVERSE_IGTBLB6	,
		DISP_TBL_REVERSE_IGTBLB7	,
		DISP_TBL_REVERSE_IGTBLB8	,
		DISP_TBL_REVERSE_IGTBLB9	,
		DISP_TBL_REVERSE_IGTBLB10	,
		DISP_TBL_REVERSE_IGTBLB11	,
		DISP_TBL_REVERSE_IGTBLB12	,
		DISP_TBL_REVERSE_IGTBLB13	,
		DISP_TBL_REVERSE_IGTBLB14	,
		DISP_TBL_REVERSE_IGTBLB15
	};

	memcpy(priv->rAntiTblA, rAntiTblA, sizeof(rAntiTblA));
	memcpy(priv->gAntiTblA, gAntiTblA, sizeof(gAntiTblA));
	memcpy(priv->bAntiTblA, bAntiTblA, sizeof(bAntiTblA));
}

static void initGammaOutTabl(CtImDisp4 *self)
{
	CtImDisp4Private *priv = self->privCtImDisp4;

	// Pointer of R data gamma out table A.<br>
	//	Please specify the address of the array of gushort[33].<br>
	//	If NULL is specified, this setting is skipped.<br>
	gushort rGammaOutTblA[33] = {
		DISP_TBL_REVERSE_GTBLAR0,
		DISP_TBL_REVERSE_GTBLAR1,
		DISP_TBL_REVERSE_GTBLAR2,
		DISP_TBL_REVERSE_GTBLAR3,
		DISP_TBL_REVERSE_GTBLAR4,
		DISP_TBL_REVERSE_GTBLAR5,
		DISP_TBL_REVERSE_GTBLAR6,
		DISP_TBL_REVERSE_GTBLAR7,
		DISP_TBL_REVERSE_GTBLAR8,
		DISP_TBL_REVERSE_GTBLAR9,
		DISP_TBL_REVERSE_GTBLAR10,
		DISP_TBL_REVERSE_GTBLAR11,
		DISP_TBL_REVERSE_GTBLAR12,
		DISP_TBL_REVERSE_GTBLAR13,
		DISP_TBL_REVERSE_GTBLAR14,
		DISP_TBL_REVERSE_GTBLAR15,
		DISP_TBL_REVERSE_GTBLAR16,
		DISP_TBL_REVERSE_GTBLAR17,
		DISP_TBL_REVERSE_GTBLAR18,
		DISP_TBL_REVERSE_GTBLAR19,
		DISP_TBL_REVERSE_GTBLAR10,
		DISP_TBL_REVERSE_GTBLAR21,
		DISP_TBL_REVERSE_GTBLAR22,
		DISP_TBL_REVERSE_GTBLAR23,
		DISP_TBL_REVERSE_GTBLAR24,
		DISP_TBL_REVERSE_GTBLAR25,
		DISP_TBL_REVERSE_GTBLAR26,
		DISP_TBL_REVERSE_GTBLAR27,
		DISP_TBL_REVERSE_GTBLAR28,
		DISP_TBL_REVERSE_GTBLAR29,
		DISP_TBL_REVERSE_GTBLAR30,
		DISP_TBL_REVERSE_GTBLAR31,
		DISP_TBL_REVERSE_GTBLAR32
	};

	// Pointer of G data gamma out table A.<br>
	//	Please specify the address of the array of gushort[33].<br>
	//	If NULL is specified, this setting is skipped.<br>
	gushort gGammaOutTblA[33] = {
		DISP_TBL_REVERSE_GTBLAG0	,
		DISP_TBL_REVERSE_GTBLAG1	,
		DISP_TBL_REVERSE_GTBLAG2	,
		DISP_TBL_REVERSE_GTBLAG3	,
		DISP_TBL_REVERSE_GTBLAG4	,
		DISP_TBL_REVERSE_GTBLAG5	,
		DISP_TBL_REVERSE_GTBLAG6	,
		DISP_TBL_REVERSE_GTBLAG7	,
		DISP_TBL_REVERSE_GTBLAG8	,
		DISP_TBL_REVERSE_GTBLAG9	,
		DISP_TBL_REVERSE_GTBLAG10	,
		DISP_TBL_REVERSE_GTBLAG11	,
		DISP_TBL_REVERSE_GTBLAG12	,
		DISP_TBL_REVERSE_GTBLAG13	,
		DISP_TBL_REVERSE_GTBLAG14	,
		DISP_TBL_REVERSE_GTBLAG15	,
		DISP_TBL_REVERSE_GTBLAG16	,
		DISP_TBL_REVERSE_GTBLAG17	,
		DISP_TBL_REVERSE_GTBLAG18	,
		DISP_TBL_REVERSE_GTBLAG19	,
		DISP_TBL_REVERSE_GTBLAG20	,
		DISP_TBL_REVERSE_GTBLAG21	,
		DISP_TBL_REVERSE_GTBLAG22	,
		DISP_TBL_REVERSE_GTBLAG23	,
		DISP_TBL_REVERSE_GTBLAG24	,
		DISP_TBL_REVERSE_GTBLAG25	,
		DISP_TBL_REVERSE_GTBLAG26	,
		DISP_TBL_REVERSE_GTBLAG27	,
		DISP_TBL_REVERSE_GTBLAG28	,
		DISP_TBL_REVERSE_GTBLAG29	,
		DISP_TBL_REVERSE_GTBLAG30	,
		DISP_TBL_REVERSE_GTBLAG31	,
		DISP_TBL_REVERSE_GTBLAG32
	};

	// Pointer of B data gamma out table A.<br>
	//	Please specify the address of the array of gushort[33].<br>
	//	If NULL is specified, this setting is skipped.<br>
	gushort bGammaOutTblA[33] = {
		DISP_TBL_REVERSE_GTBLAB0	,
		DISP_TBL_REVERSE_GTBLAB1	,
		DISP_TBL_REVERSE_GTBLAB2	,
		DISP_TBL_REVERSE_GTBLAB3	,
		DISP_TBL_REVERSE_GTBLAB4	,
		DISP_TBL_REVERSE_GTBLAB5	,
		DISP_TBL_REVERSE_GTBLAB6	,
		DISP_TBL_REVERSE_GTBLAB7	,
		DISP_TBL_REVERSE_GTBLAB8	,
		DISP_TBL_REVERSE_GTBLAB9	,
		DISP_TBL_REVERSE_GTBLAB10	,
		DISP_TBL_REVERSE_GTBLAB11	,
		DISP_TBL_REVERSE_GTBLAB12	,
		DISP_TBL_REVERSE_GTBLAB13	,
		DISP_TBL_REVERSE_GTBLAB14	,
		DISP_TBL_REVERSE_GTBLAB15	,
		DISP_TBL_REVERSE_GTBLAB16	,
		DISP_TBL_REVERSE_GTBLAB17	,
		DISP_TBL_REVERSE_GTBLAB18	,
		DISP_TBL_REVERSE_GTBLAB19	,
		DISP_TBL_REVERSE_GTBLAB20	,
		DISP_TBL_REVERSE_GTBLAB21	,
		DISP_TBL_REVERSE_GTBLAB22	,
		DISP_TBL_REVERSE_GTBLAB23	,
		DISP_TBL_REVERSE_GTBLAB24	,
		DISP_TBL_REVERSE_GTBLAB25	,
		DISP_TBL_REVERSE_GTBLAB26	,
		DISP_TBL_REVERSE_GTBLAB27	,
		DISP_TBL_REVERSE_GTBLAB28	,
		DISP_TBL_REVERSE_GTBLAB29	,
		DISP_TBL_REVERSE_GTBLAB30	,
		DISP_TBL_REVERSE_GTBLAB31	,
		DISP_TBL_REVERSE_GTBLAB32
	};


	// Pointer of R data gamma out table B.<br>
	//	Please specify the address of the array of gushort[33].<br>
	//	If NULL is specified, this setting is skipped.<br>
	gushort rGammaOutTblB[33] = {
		DISP_TBL_REVERSE_GTBLBR0	,
		DISP_TBL_REVERSE_GTBLBR1	,
		DISP_TBL_REVERSE_GTBLBR2	,
		DISP_TBL_REVERSE_GTBLBR3	,
		DISP_TBL_REVERSE_GTBLBR4	,
		DISP_TBL_REVERSE_GTBLBR5	,
		DISP_TBL_REVERSE_GTBLBR6	,
		DISP_TBL_REVERSE_GTBLBR7	,
		DISP_TBL_REVERSE_GTBLBR8	,
		DISP_TBL_REVERSE_GTBLBR9	,
		DISP_TBL_REVERSE_GTBLBR10	,
		DISP_TBL_REVERSE_GTBLBR11	,
		DISP_TBL_REVERSE_GTBLBR12	,
		DISP_TBL_REVERSE_GTBLBR13	,
		DISP_TBL_REVERSE_GTBLBR14	,
		DISP_TBL_REVERSE_GTBLBR15	,
		DISP_TBL_REVERSE_GTBLBR16	,
		DISP_TBL_REVERSE_GTBLBR17	,
		DISP_TBL_REVERSE_GTBLBR18	,
		DISP_TBL_REVERSE_GTBLBR19	,
		DISP_TBL_REVERSE_GTBLBR10	,
		DISP_TBL_REVERSE_GTBLBR21	,
		DISP_TBL_REVERSE_GTBLBR22	,
		DISP_TBL_REVERSE_GTBLBR23	,
		DISP_TBL_REVERSE_GTBLBR24	,
		DISP_TBL_REVERSE_GTBLBR25	,
		DISP_TBL_REVERSE_GTBLBR26	,
		DISP_TBL_REVERSE_GTBLBR27	,
		DISP_TBL_REVERSE_GTBLBR28	,
		DISP_TBL_REVERSE_GTBLBR29	,
		DISP_TBL_REVERSE_GTBLBR30	,
		DISP_TBL_REVERSE_GTBLBR31	,
		DISP_TBL_REVERSE_GTBLBR32
	};

	// Pointer of G data gamma out table B.<br>
	//	Please specify the address of the array of gushort[33].<br>
	//	If NULL is specified, this setting is skipped.<br>
	gushort gGammaOutTblB[33] = {
		DISP_TBL_REVERSE_GTBLBG0	,
		DISP_TBL_REVERSE_GTBLBG1	,
		DISP_TBL_REVERSE_GTBLBG2	,
		DISP_TBL_REVERSE_GTBLBG3	,
		DISP_TBL_REVERSE_GTBLBG4	,
		DISP_TBL_REVERSE_GTBLBG5	,
		DISP_TBL_REVERSE_GTBLBG6	,
		DISP_TBL_REVERSE_GTBLBG7	,
		DISP_TBL_REVERSE_GTBLBG8	,
		DISP_TBL_REVERSE_GTBLBG9	,
		DISP_TBL_REVERSE_GTBLBG10	,
		DISP_TBL_REVERSE_GTBLBG11	,
		DISP_TBL_REVERSE_GTBLBG12	,
		DISP_TBL_REVERSE_GTBLBG13	,
		DISP_TBL_REVERSE_GTBLBG14	,
		DISP_TBL_REVERSE_GTBLBG15	,
		DISP_TBL_REVERSE_GTBLBG16	,
		DISP_TBL_REVERSE_GTBLBG17	,
		DISP_TBL_REVERSE_GTBLBG18	,
		DISP_TBL_REVERSE_GTBLBG19	,
		DISP_TBL_REVERSE_GTBLBG20	,
		DISP_TBL_REVERSE_GTBLBG21	,
		DISP_TBL_REVERSE_GTBLBG22	,
		DISP_TBL_REVERSE_GTBLBG23	,
		DISP_TBL_REVERSE_GTBLBG24	,
		DISP_TBL_REVERSE_GTBLBG25	,
		DISP_TBL_REVERSE_GTBLBG26	,
		DISP_TBL_REVERSE_GTBLBG27	,
		DISP_TBL_REVERSE_GTBLBG28	,
		DISP_TBL_REVERSE_GTBLBG29	,
		DISP_TBL_REVERSE_GTBLBG30	,
		DISP_TBL_REVERSE_GTBLBG31	,
		DISP_TBL_REVERSE_GTBLBG32
	};

	// Pointer of B data gamma out table B.<br>
	//	Please specify the address of the array of gushort[33].<br>
	//	If NULL is specified, this setting is skipped.<br>
	gushort bGammaOutTblB[33] = {
		DISP_TBL_REVERSE_GTBLBB0	,
		DISP_TBL_REVERSE_GTBLBB1	,
		DISP_TBL_REVERSE_GTBLBB2	,
		DISP_TBL_REVERSE_GTBLBB3	,
		DISP_TBL_REVERSE_GTBLBB4	,
		DISP_TBL_REVERSE_GTBLBB5	,
		DISP_TBL_REVERSE_GTBLBB6	,
		DISP_TBL_REVERSE_GTBLBB7	,
		DISP_TBL_REVERSE_GTBLBB8	,
		DISP_TBL_REVERSE_GTBLBB9	,
		DISP_TBL_REVERSE_GTBLBB10	,
		DISP_TBL_REVERSE_GTBLBB11	,
		DISP_TBL_REVERSE_GTBLBB12	,
		DISP_TBL_REVERSE_GTBLBB13	,
		DISP_TBL_REVERSE_GTBLBB14	,
		DISP_TBL_REVERSE_GTBLBB15	,
		DISP_TBL_REVERSE_GTBLBB16	,
		DISP_TBL_REVERSE_GTBLBB17	,
		DISP_TBL_REVERSE_GTBLBB18	,
		DISP_TBL_REVERSE_GTBLBB19	,
		DISP_TBL_REVERSE_GTBLBB20	,
		DISP_TBL_REVERSE_GTBLBB21	,
		DISP_TBL_REVERSE_GTBLBB22	,
		DISP_TBL_REVERSE_GTBLBB23	,
		DISP_TBL_REVERSE_GTBLBB24	,
		DISP_TBL_REVERSE_GTBLBB25	,
		DISP_TBL_REVERSE_GTBLBB26	,
		DISP_TBL_REVERSE_GTBLBB27	,
		DISP_TBL_REVERSE_GTBLBB28	,
		DISP_TBL_REVERSE_GTBLBB29	,
		DISP_TBL_REVERSE_GTBLBB30	,
		DISP_TBL_REVERSE_GTBLBB31	,
		DISP_TBL_REVERSE_GTBLBB32
	};

	memcpy(priv->rGammaOutTblA, rGammaOutTblA, sizeof(rGammaOutTblA));
	memcpy(priv->gGammaOutTblA, gGammaOutTblA, sizeof(gGammaOutTblA));
	memcpy(priv->bGammaOutTblA, bGammaOutTblA, sizeof(bGammaOutTblA));

	memcpy(priv->rGammaOutTblB, rGammaOutTblB, sizeof(rGammaOutTblB));
	memcpy(priv->gGammaOutTblB, gGammaOutTblB, sizeof(gGammaOutTblB));
	memcpy(priv->bGammaOutTblB, bGammaOutTblB, sizeof(bGammaOutTblB));
}

static void initFullTabl(CtImDisp4 *self)
{
	CtImDisp4Private *priv = self->privCtImDisp4;

	// Pointer of R data gamma table (Full bit)<br>
	//	Please specify the address of the array of USHORT[32].<br>
	//	If NULL is specified, this setting is skipped.<br>
	guint32 rFullTbl[32 / 2] = {
		DISP_TBL_DGTBLFR0,
		DISP_TBL_DGTBLFR1,
		DISP_TBL_DGTBLFR2,
		DISP_TBL_DGTBLFR3,
		DISP_TBL_DGTBLFR4,
		DISP_TBL_DGTBLFR5,
		DISP_TBL_DGTBLFR6,
		DISP_TBL_DGTBLFR7,
		DISP_TBL_DGTBLFR8,
		DISP_TBL_DGTBLFR9,
		DISP_TBL_DGTBLFR10,
		DISP_TBL_DGTBLFR11,
		DISP_TBL_DGTBLFR12,
		DISP_TBL_DGTBLFR13,
		DISP_TBL_DGTBLFR14,
		DISP_TBL_DGTBLFR15
	};

	// Pointer of G data gamma table (Full bit)<br>
	//	Please specify the address of the array of USHORT[32].<br>
	//	If NULL is specified, this setting is skipped.<br>
	guint32 gFullTbl[32 / 2] = {
		DISP_TBL_DGTBLFG0,
		DISP_TBL_DGTBLFG1,
		DISP_TBL_DGTBLFG2,
		DISP_TBL_DGTBLFG3,
		DISP_TBL_DGTBLFG4,
		DISP_TBL_DGTBLFG5,
		DISP_TBL_DGTBLFG6,
		DISP_TBL_DGTBLFG7,
		DISP_TBL_DGTBLFG8,
		DISP_TBL_DGTBLFG9,
		DISP_TBL_DGTBLFG10,
		DISP_TBL_DGTBLFG11,
		DISP_TBL_DGTBLFG12,
		DISP_TBL_DGTBLFG13,
		DISP_TBL_DGTBLFG14,
		DISP_TBL_DGTBLFG15
	};

	// Pointer of B data gamma table (Full bit)<br>
	//	Please specify the address of the array of USHORT[32].<br>
	//	If NULL is specified, this setting is skipped.<br>
	guint32 bFullTbl[32 / 2] = {
		DISP_TBL_DGTBLFB0,
		DISP_TBL_DGTBLFB1,
		DISP_TBL_DGTBLFB2,
		DISP_TBL_DGTBLFB3,
		DISP_TBL_DGTBLFB4,
		DISP_TBL_DGTBLFB5,
		DISP_TBL_DGTBLFB6,
		DISP_TBL_DGTBLFB7,
		DISP_TBL_DGTBLFB8,
		DISP_TBL_DGTBLFB9,
		DISP_TBL_DGTBLFB10,
		DISP_TBL_DGTBLFB11,
		DISP_TBL_DGTBLFB12,
		DISP_TBL_DGTBLFB13,
		DISP_TBL_DGTBLFB14,
		DISP_TBL_DGTBLFB15
	};

	memcpy(priv->rFullTbl, rFullTbl, sizeof(rFullTbl));
	memcpy(priv->gFullTbl, gFullTbl, sizeof(gFullTbl));
	memcpy(priv->bFullTbl, bFullTbl, sizeof(bFullTbl));
}

static void initLuminanceTbl(CtImDisp4 *self)
{
	CtImDisp4Private *priv = self->privCtImDisp4;

	// Pointer of Luminance correction data table A (Full bit)<br>
	//	Please specify the address of the array of gushort[33].<br>
	//	If NULL is specified, this setting is skipped.<br>
	gushort luminanceTblA[33] = {
		DISP_TBL_REVERSE_YSTBLA0		,
		DISP_TBL_REVERSE_YSTBLA1		,
		DISP_TBL_REVERSE_YSTBLA2		,
		DISP_TBL_REVERSE_YSTBLA3		,
		DISP_TBL_REVERSE_YSTBLA4		,
		DISP_TBL_REVERSE_YSTBLA5		,
		DISP_TBL_REVERSE_YSTBLA6		,
		DISP_TBL_REVERSE_YSTBLA7		,
		DISP_TBL_REVERSE_YSTBLA8		,
		DISP_TBL_REVERSE_YSTBLA9		,
		DISP_TBL_REVERSE_YSTBLA10	,
		DISP_TBL_REVERSE_YSTBLA11	,
		DISP_TBL_REVERSE_YSTBLA12	,
		DISP_TBL_REVERSE_YSTBLA13	,
		DISP_TBL_REVERSE_YSTBLA14	,
		DISP_TBL_REVERSE_YSTBLA15	,
		DISP_TBL_REVERSE_YSTBLA16	,
		DISP_TBL_REVERSE_YSTBLA17	,
		DISP_TBL_REVERSE_YSTBLA18	,
		DISP_TBL_REVERSE_YSTBLA19	,
		DISP_TBL_REVERSE_YSTBLA20	,
		DISP_TBL_REVERSE_YSTBLA21	,
		DISP_TBL_REVERSE_YSTBLA22	,
		DISP_TBL_REVERSE_YSTBLA23	,
		DISP_TBL_REVERSE_YSTBLA24	,
		DISP_TBL_REVERSE_YSTBLA25	,
		DISP_TBL_REVERSE_YSTBLA26	,
		DISP_TBL_REVERSE_YSTBLA27	,
		DISP_TBL_REVERSE_YSTBLA28	,
		DISP_TBL_REVERSE_YSTBLA29	,
		DISP_TBL_REVERSE_YSTBLA30	,
		DISP_TBL_REVERSE_YSTBLA31	,
		DISP_TBL_REVERSE_YSTBLA32
	};

	// Pointer of Luminance correction data table B (Full bit)<br>
	//	Please specify the address of the array of gushort[33].<br>
	//	If NULL is specified, this setting is skipped.<br>
	gushort luminanceTblB[33] = {
		DISP_TBL_REVERSE_YSTBLB0		,
		DISP_TBL_REVERSE_YSTBLB1		,
		DISP_TBL_REVERSE_YSTBLB2		,
		DISP_TBL_REVERSE_YSTBLB3		,
		DISP_TBL_REVERSE_YSTBLB4		,
		DISP_TBL_REVERSE_YSTBLB5		,
		DISP_TBL_REVERSE_YSTBLB6		,
		DISP_TBL_REVERSE_YSTBLB7		,
		DISP_TBL_REVERSE_YSTBLB8		,
		DISP_TBL_REVERSE_YSTBLB9		,
		DISP_TBL_REVERSE_YSTBLB10	,
		DISP_TBL_REVERSE_YSTBLB11	,
		DISP_TBL_REVERSE_YSTBLB12	,
		DISP_TBL_REVERSE_YSTBLB13	,
		DISP_TBL_REVERSE_YSTBLB14	,
		DISP_TBL_REVERSE_YSTBLB15	,
		DISP_TBL_REVERSE_YSTBLB16	,
		DISP_TBL_REVERSE_YSTBLB17	,
		DISP_TBL_REVERSE_YSTBLB18	,
		DISP_TBL_REVERSE_YSTBLB19	,
		DISP_TBL_REVERSE_YSTBLB20	,
		DISP_TBL_REVERSE_YSTBLB21	,
		DISP_TBL_REVERSE_YSTBLB22	,
		DISP_TBL_REVERSE_YSTBLB23	,
		DISP_TBL_REVERSE_YSTBLB24	,
		DISP_TBL_REVERSE_YSTBLB25	,
		DISP_TBL_REVERSE_YSTBLB26	,
		DISP_TBL_REVERSE_YSTBLB27	,
		DISP_TBL_REVERSE_YSTBLB28	,
		DISP_TBL_REVERSE_YSTBLB29	,
		DISP_TBL_REVERSE_YSTBLB30	,
		DISP_TBL_REVERSE_YSTBLB31	,
		DISP_TBL_REVERSE_YSTBLB32
	};

	memcpy(priv->luminanceTblA, luminanceTblA, sizeof(luminanceTblA));
	memcpy(priv->luminanceTblB, luminanceTblB, sizeof(luminanceTblB));
}

static void initGainTabl(CtImDisp4 *self)
{
	CtImDisp4Private *priv = self->privCtImDisp4;

	gushort gainTblA[33] = {
		DISP_TBL_REVERSE_YSTBLACG0	,
		DISP_TBL_REVERSE_YSTBLACG1	,
		DISP_TBL_REVERSE_YSTBLACG2	,
		DISP_TBL_REVERSE_YSTBLACG3	,
		DISP_TBL_REVERSE_YSTBLACG4	,
		DISP_TBL_REVERSE_YSTBLACG5	,
		DISP_TBL_REVERSE_YSTBLACG6	,
		DISP_TBL_REVERSE_YSTBLACG7	,
		DISP_TBL_REVERSE_YSTBLACG8	,
		DISP_TBL_REVERSE_YSTBLACG9	,
		DISP_TBL_REVERSE_YSTBLACG10	,
		DISP_TBL_REVERSE_YSTBLACG11	,
		DISP_TBL_REVERSE_YSTBLACG12	,
		DISP_TBL_REVERSE_YSTBLACG13	,
		DISP_TBL_REVERSE_YSTBLACG14	,
		DISP_TBL_REVERSE_YSTBLACG15	,
		DISP_TBL_REVERSE_YSTBLACG16	,
		DISP_TBL_REVERSE_YSTBLACG17	,
		DISP_TBL_REVERSE_YSTBLACG18	,
		DISP_TBL_REVERSE_YSTBLACG19	,
		DISP_TBL_REVERSE_YSTBLACG20	,
		DISP_TBL_REVERSE_YSTBLACG21	,
		DISP_TBL_REVERSE_YSTBLACG22	,
		DISP_TBL_REVERSE_YSTBLACG23	,
		DISP_TBL_REVERSE_YSTBLACG24	,
		DISP_TBL_REVERSE_YSTBLACG25	,
		DISP_TBL_REVERSE_YSTBLACG26	,
		DISP_TBL_REVERSE_YSTBLACG27	,
		DISP_TBL_REVERSE_YSTBLACG28	,
		DISP_TBL_REVERSE_YSTBLACG29	,
		DISP_TBL_REVERSE_YSTBLACG30	,
		DISP_TBL_REVERSE_YSTBLACG31	,
		DISP_TBL_REVERSE_YSTBLACG32
	};

	gushort gainTblB[33] = {
		DISP_TBL_REVERSE_YSTBLBCG0	,
		DISP_TBL_REVERSE_YSTBLBCG1	,
		DISP_TBL_REVERSE_YSTBLBCG2	,
		DISP_TBL_REVERSE_YSTBLBCG3	,
		DISP_TBL_REVERSE_YSTBLBCG4	,
		DISP_TBL_REVERSE_YSTBLBCG5	,
		DISP_TBL_REVERSE_YSTBLBCG6	,
		DISP_TBL_REVERSE_YSTBLBCG7	,
		DISP_TBL_REVERSE_YSTBLBCG8	,
		DISP_TBL_REVERSE_YSTBLBCG9	,
		DISP_TBL_REVERSE_YSTBLBCG10	,
		DISP_TBL_REVERSE_YSTBLBCG11	,
		DISP_TBL_REVERSE_YSTBLBCG12	,
		DISP_TBL_REVERSE_YSTBLBCG13	,
		DISP_TBL_REVERSE_YSTBLBCG14	,
		DISP_TBL_REVERSE_YSTBLBCG15	,
		DISP_TBL_REVERSE_YSTBLBCG16	,
		DISP_TBL_REVERSE_YSTBLBCG17	,
		DISP_TBL_REVERSE_YSTBLBCG18	,
		DISP_TBL_REVERSE_YSTBLBCG19	,
		DISP_TBL_REVERSE_YSTBLBCG20	,
		DISP_TBL_REVERSE_YSTBLBCG21	,
		DISP_TBL_REVERSE_YSTBLBCG22	,
		DISP_TBL_REVERSE_YSTBLBCG23	,
		DISP_TBL_REVERSE_YSTBLBCG24	,
		DISP_TBL_REVERSE_YSTBLBCG25	,
		DISP_TBL_REVERSE_YSTBLBCG26	,
		DISP_TBL_REVERSE_YSTBLBCG27	,
		DISP_TBL_REVERSE_YSTBLBCG28	,
		DISP_TBL_REVERSE_YSTBLBCG29	,
		DISP_TBL_REVERSE_YSTBLBCG30	,
		DISP_TBL_REVERSE_YSTBLBCG31	,
		DISP_TBL_REVERSE_YSTBLBCG32
	};

	memcpy(priv->gainTblA, gainTblA, sizeof(gainTblA));
	memcpy(priv->gainTblB, gainTblB, sizeof(gainTblB));
}

/*
 * PUBLIC
 * */

guint32 *ct_im_disp4_get_r_anti_tbla(CtImDisp4 *self)
{
	CtImDisp4Private *priv = self->privCtImDisp4;
	return priv->rAntiTblA;
}

guint32 *ct_im_disp4_get_g_anti_tbla(CtImDisp4 *self)
{
	CtImDisp4Private *priv = self->privCtImDisp4;
	return priv->gAntiTblA;
}

guint32 *ct_im_disp4_get_b_anti_tbla(CtImDisp4 *self)
{
	CtImDisp4Private *priv = self->privCtImDisp4;
	return priv->bAntiTblA;
}

gushort *ct_im_disp4_get_r_gamma_out_tbla(CtImDisp4 *self)
{
	CtImDisp4Private *priv = self->privCtImDisp4;
	return priv->rGammaOutTblA;
}

gushort *ct_im_disp4_get_g_gamma_out_tbla(CtImDisp4 *self)
{
	CtImDisp4Private *priv = self->privCtImDisp4;
	return priv->gGammaOutTblA;
}

gushort *ct_im_disp4_get_b_gamma_out_tbla(CtImDisp4 *self)
{
	CtImDisp4Private *priv = self->privCtImDisp4;
	return priv->bGammaOutTblA;
}

gushort *ct_im_disp4_get_r_gamma_out_tblb(CtImDisp4 *self)
{
	CtImDisp4Private *priv = self->privCtImDisp4;
	return priv->rGammaOutTblB;
}

gushort *ct_im_disp4_get_g_gamma_out_tblb(CtImDisp4 *self)
{
	CtImDisp4Private *priv = self->privCtImDisp4;
	return priv->gGammaOutTblB;
}

gushort *ct_im_disp4_get_b_gamma_out_tblb(CtImDisp4 *self)
{
	CtImDisp4Private *priv = self->privCtImDisp4;
	return priv->bGammaOutTblB;
}

guint32 *ct_im_disp4_get_r_full_tbl(CtImDisp4 *self)
{
	CtImDisp4Private *priv = self->privCtImDisp4;
	return priv->rFullTbl;
}

guint32 *ct_im_disp4_get_g_full_tbl(CtImDisp4 *self)
{
	CtImDisp4Private *priv = self->privCtImDisp4;
	return priv->gFullTbl;
}

guint32 *ct_im_disp4_get_b_full_tbl(CtImDisp4 *self)
{
	CtImDisp4Private *priv = self->privCtImDisp4;
	return priv->bFullTbl;
}

gushort *ct_im_disp4_get_luminance_tbla(CtImDisp4 *self)
{
	CtImDisp4Private *priv = self->privCtImDisp4;
	return priv->luminanceTblA;
}

gushort *ct_im_disp4_get_luminance_tblb(CtImDisp4 *self)
{
	CtImDisp4Private *priv = self->privCtImDisp4;
	return priv->luminanceTblB;
}

gushort *ct_im_disp4_get_gain_tbla(CtImDisp4 *self)
{
	CtImDisp4Private *priv = self->privCtImDisp4;
	return priv->gainTblA;
}

gushort *ct_im_disp4_get_gain_tblb(CtImDisp4 *self)
{
	CtImDisp4Private *priv = self->privCtImDisp4;
	return priv->gainTblB;
}

CtImDisp4 *ct_im_disp4_new(void)
{
	CtImDisp4 *self = (CtImDisp4 *) g_object_new(CT_TYPE_IM_DISP4, NULL);
	return self;
}
