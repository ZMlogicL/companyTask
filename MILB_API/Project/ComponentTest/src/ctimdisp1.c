/*
 *ctimdisp1.c
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

#include "ctimdisp3.h"
#include "ctimdisp3a.h"

#include "imdisp1group.h"
#include "ctimdisp1.h"

/*
 * G_DEFINE_语句
 * */
G_DEFINE_TYPE (CtImDisp1, ct_im_disp1, IM_TYPE_DISP1_PARENT);

/*
 * 以下开始宏定义
 * */
#define CT_IM_DISP1_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), CT_TYPE_IM_DISP1, CtImDisp1Private))

/*
 * 内部结构体或类型定义
 * */
struct _CtImDisp1Private
{
	gpointer qwertyu;
};

/*
 * 文件级全局变量定义
 * */

/*
 * DECLS
 * */
static void dispose_od(GObject *object);
static void finalize_od(GObject *object);
#ifdef CtImDisp_CO_DEBUG_DISP
static gboolean imDisp1DoPctest_od(ImDisp1Parent *parent, gint32 *pSeqNo);
#endif /*CtImDisp_CO_DEBUG_DISP*/

/*
 * IMPL
 * */
static void ct_im_disp1_class_init(CtImDisp1Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtImDisp1Private));
}

static void ct_im_disp1_init(CtImDisp1 *self)
{
	//CtImDisp1Private *priv = CT_IM_DISP1_GET_PRIVATE(self);
#ifdef CtImDisp_CO_DEBUG_DISP
	ImDisp1Parent *parent = (ImDisp1Parent *)self;
	parent->pctestFunc = imDisp1DoPctest_od;
#endif /*CtImDisp_CO_DEBUG_DISP*/
}

static void dispose_od(GObject *object)
{
//	CtImDisp1 *self = CT_IM_DISP1(object);
//	CtImDisp1Private *priv = CT_IM_DISP1_GET_PRIVATE(self);
	/*释放创建的对象1*/
//	if (priv->objectMine) {
//		g_object_unref(priv->objectMine);
//		priv->objectMine = NULL;
//	}
	G_OBJECT_CLASS (ct_im_disp1_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
//	CtImDisp1 *self = CT_IM_DISP1(object);
//	CtImDisp1Private *priv = CT_IM_DISP1_GET_PRIVATE(self);
	/*释放创建的内存2*/
//	if(self->name)
//	{
//		free(self->name);
//		self->name =NULL;
//	}
	G_OBJECT_CLASS (ct_im_disp1_parent_class)->finalize(object);
}


#ifdef CtImDisp_CO_DEBUG_DISP
static gboolean imDisp1DoPctest_od(ImDisp1Parent *parent, gint32 *pSeqNo)
{
//	CtImDisp1 *self = (CtImDisp1 *)parent;
	gint32 seqNo = *pSeqNo;
	ImDisp1Group *imDisp1Group = (ImDisp1Group *)im_disp1_parent_get_group(parent);

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Init()\n", seqNo++));

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LRST.word = 1;
	IO_DISP.MAIN[0].DCORE.RESET.word = 1;
	IO_DISP.MAIN[0].GRCH[0].GRRST.word = 1;
	IO_DISP.MAIN[0].GRCH[1].GRRST.word = 1;
	IO_DISP.MAIN[1].LCH.LRST.word = 1;
	IO_DISP.MAIN[1].DCORE.RESET.word = 1;
	IO_DISP.MAIN[1].GRCH[0].GRRST.word = 1;
	IO_DISP.MAIN[1].GRCH[1].GRRST.word = 1;
	IO_DISP.MDSCTL.MDSSR.word = 1;
	IO_DISP.JDDISP_HDMI_HDMIC.HDMISR.word = 1;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	im_disp1_parent_pctest_wrap(parent, "imdisp Init");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Ctrl_Main_Layer() normal\n", seqNo++));

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LTRG.word = 2;	// E_IM_DISP_TRG_READ_NO_ACT(2)
	IO_DISP.MAIN[1].LCH.LTRG.word = 2;	// E_IM_DISP_TRG_READ_NO_ACT(2)
	IO_DISP.MAIN[0].DCORE.RPGEN.word = 1;
	IO_DISP.MAIN[1].DCORE.RPGEN.word = 1;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_SECOND_PARA_ONLY, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 2 0 0");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 1 1 0");
	// CtImDisp3_D_CT_IM_DISP_SECOND_PARA_ONLY, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 2 1 0");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 0");

	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 1");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 2");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 3");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 4");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 1");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 2");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 3");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 37");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 38");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 39");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 37");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 38");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 39");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Ctrl_Main_Layer() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 0 0 0");
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 0 1 0");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	// imdisp start 0x0001
	IO_DISP.MAIN[0].LCH.LTRG.word = 3;	// E_IM_DISP_TRG_READ_ACT(3)
	IO_DISP.MAIN[1].LCH.LTRG.word = 3;	// E_IM_DISP_TRG_READ_ACT(3)
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 0");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 0");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	// imdisp stop 0x0001 0
	IO_DISP.MAIN[0].LCH.LTRG.word = 2;	// E_IM_DISP_TRG_READ_NO_ACT(2)
	IO_DISP.MAIN[1].LCH.LTRG.word = 2;	// E_IM_DISP_TRG_READ_NO_ACT(2)
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 5");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 6");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 7");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 8");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 9");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 10");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 11");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 12");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 13");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 14");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 15");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 16");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 17");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 18");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 19");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 20");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 21");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 22");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 23");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 24");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 25");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 26");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 27");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 28");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 29");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 30");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 31");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 32");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 33");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 34");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 35");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 36");

	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Pamameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 4");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Pamameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 5");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 6");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 7");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 8");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 9");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 10");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 11");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 12");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 13");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 14");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 15");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 16");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 17");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 18");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 19");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 20");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 21");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 22");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 23");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 24");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 25");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 26");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 27");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 28");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 29");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 30");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 31");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 32");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 33");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 34");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 35");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 36");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Ctrl_Main_Layer() normal\n", seqNo++));

	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 0 0");

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, CtImDisp3_D_CT_IM_DISP_BLOCK_1
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMg 1 0");
	// CtImDisp3_D_CT_IM_DISP_SECOND_PARA_ONLY, CtImDisp3_D_CT_IM_DISP_BLOCK_1
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMg 2 0");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMg 3 0");

	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMs 3 1 0");

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, CtImDisp3_D_CT_IM_DISP_BLOCK_1
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMg 1 1");
	// CtImDisp3_D_CT_IM_DISP_SECOND_PARA_ONLY, CtImDisp3_D_CT_IM_DISP_BLOCK_1
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMg 2 1");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMg 3 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Ctrl_Main_Layer() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_0
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMg 0 0");
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, CtImDisp3_D_CT_IM_DISP_BLOCK_1
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlMg 0 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Ctrl_Output() normal\n", seqNo++));

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.word = 2;	// E_IM_DISP_TRG_READ_NO_ACT(2)
	IO_DISP.MAIN[1].DCORE.TRG.word = 2;	// E_IM_DISP_TRG_READ_NO_ACT(2)
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 1 1 0");
	// CtImDisp3_D_CT_IM_DISP_SECOND_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 2 1 0");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Ctrl_Output() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 0 0 0");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.word = 3;	// E_IM_DISP_TRG_READ_ACT(3)
	IO_DISP.MAIN[1].DCORE.TRG.word = 3;	// E_IM_DISP_TRG_READ_ACT(3)
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.GMTAEN = 0;
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.YSATTA = 0;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 1 1 0");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.word = 2;
	IO_DISP.MAIN[0].DCORE.RESET.word = D_IM_DISP_SR_RESET;
	IO_DISP.MAIN[0].DCORE.IFS.word = D_IM_DISP_IFS_HDMI;
	IO_DISP.MAIN[0].DCORE.RESET.word = D_IM_DISP_SR_CANCEL;
	IO_DISP.MAIN[1].DCORE.TRG.word = 2;
	IO_DISP.MAIN[1].DCORE.RESET.word = D_IM_DISP_SR_RESET;
	IO_DISP.MAIN[1].DCORE.IFS.word = D_IM_DISP_IFS_LCD;
	IO_DISP.MAIN[1].DCORE.RESET.word = D_IM_DISP_SR_CANCEL;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 1");
//	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 2");
//	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 3");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 4");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 5");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 6");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 7");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 8");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 9");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 10");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 11");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 12");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 13");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 14");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 15");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 16");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 17");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 18");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 19");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 20");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 21");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 22");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 23");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 24");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 25");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 26");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 27");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 28");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 29");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 30");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 31");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 32");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 33");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 34");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 35");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 36");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 37");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 38");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 39");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 40");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 41");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 42");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 43");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 44");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 45");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 46");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 47");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 48");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 49");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 50");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 51");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 52");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 53");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 54");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 55");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 56");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 57");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 58");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 59");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 60");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 61");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 62");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 63");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 64");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 65");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 66");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 67");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 68");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 69");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 70");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 71");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 72");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 73");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 74");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 75");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 76");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 77");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 78");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 79");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 80");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 81");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 82");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 83");

	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 84");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 85");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 86");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 87");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 88");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 89");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 90");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 91");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 92");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 93");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 94");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 95");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 96");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 97");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 98");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 99");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 A1");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 A2");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 A3");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 A4");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 A5");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 A6");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 A7");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[1].DCORE.RESET.word = D_IM_DISP_SR_RESET;
	IO_DISP.MAIN[1].DCORE.IFS.word = D_IM_DISP_IFS_MIPI;
	IO_DISP.MAIN[1].DCORE.RESET.word = D_IM_DISP_SR_CANCEL;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 A8");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 A9");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 B1");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 B2");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 B3");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 B4");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 B5");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 B6");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 B7");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 B8");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 B9");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 C1");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 C2");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 C3");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 C4");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 C5");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 C6");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 C7");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 C8");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 C9");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 D1");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 D2");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 D3");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 D4");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 D5");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 D6");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Ctrl_Output() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 0 0");
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTs 3 1 0");

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTg 1 0");
	// CtImDisp3_D_CT_IM_DISP_SECOND_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTg 2 0");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTg 3 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTg 1 1");
	// CtImDisp3_D_CT_IM_DISP_SECOND_PARA_ONLY, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTg 2 1");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTg 3 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Ctrl_Output() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTg 0 0");
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlOUTg 0 1");	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Ctrl_Grid_Layer() normal\n", seqNo++));
	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.RPGEN.word = D_IM_DISP_ENABLE_ON;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDs 1 0 0");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.RPGEN.word = D_IM_DISP_ENABLE_OFF;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDs 1 1 0");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Ctrl_Grid_Layer() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDs 0 0 0");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[1].DCORE.RPGEN.word = D_IM_DISP_ENABLE_ON;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDs 0 1 0");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[1].DCORE.RPGEN.word = D_IM_DISP_ENABLE_OFF;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDs 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDs 1 1 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDs 1 0 2");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDs 1 1 2");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDs 1 0 3");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDs 1 1 3");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDs 1 0 4");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDs 1 1 4");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDs 1 0 5");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDs 1 1 5");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDs 1 0 6");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDs 1 1 6");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDs 1 0 7");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDs 1 1 7");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDs 1 0 8");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDs 1 1 8");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDs 1 0 9");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDs 1 1 9");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDs 1 0 10");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDs 1 1 10");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDs 1 0 11");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDs 1 1 11");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDs 1 0 12");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDs 1 1 12");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDs 1 0 13");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDs 1 1 13");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDs 1 0 14");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDs 1 1 14");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDs 1 0 15");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDs 1 1 15");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDs 1 0 16");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDs 1 1 16");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Ctrl_Grid_Layer() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDs 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDs 1 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDg 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDg 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Ctrl_Grid_Layer() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDg 0 0");
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp CtrlGRIDg 0 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Ctrl_OSD_Layer() normal\n", seqNo++));

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].GRCH[0].GRTRG.word = 2;
	IO_DISP.MAIN[0].GRCH[1].GRTRG.word = 2;
	IO_DISP.MAIN[1].GRCH[0].GRTRG.word = 2;
	IO_DISP.MAIN[1].GRCH[1].GRTRG.word = 2;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, RPGTMG, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 1 0 0x0004 1 0");
	// CtImDisp3_D_CT_IM_DISP_SECOND_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, RPGTMG, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 2 0 0x0004 0 0");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 0 0x0008 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 1 1 0x0008 1 0");
	// CtImDisp3_D_CT_IM_DISP_SECOND_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 2 1 0x0008 0 0");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, RPGTMG, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 1 0x0004 1 0");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Ctrl_OSD_Layer() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, RPGTMG, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 0 0 0x0004 1 0");
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 0 1 0x0008 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Layer error, RPGTMG, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 1 0 0x000C 1 0");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 0 0x0008 1 1");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 0 0x0008 0 2");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 0 0x0008 0 3");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 0 0x0008 1 4");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 0 0x0008 1 5");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 0 0x0008 0 6");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 0 0x0008 0 7");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 0 0x0008 1 8");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 0 0x0008 1 9");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 0 0x0008 0 10");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 0 0x0008 0 11");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 0 0x0008 1 12");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 0 0x0008 1 13");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 0 0x0008 0 14");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 0 0x0008 0 15");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 0 0x0008 1 16");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 0 0x0008 1 17");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 0 0x0008 0 18");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 0 0x0008 0 19");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 0 0x0008 1 20");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 0 0x0008 1 21");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 0 0x0008 0 22");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 0 0x0008 0 23");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 1 0x0008 1 24");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 1 0x0008 1 25");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 1 0x0008 0 26");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 1 0x0008 0 27");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 1 0x0008 1 28");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 1 0x0008 1 29");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 1 0x0008 0 30");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 1 0x0008 0 31");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 1 0x0008 1 32");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 1 0x0008 1 33");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 1 0x0008 0 34");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 1 0x0008 0 35");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 1 0x0008 1 36");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 1 0x0008 1 37");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 1 0x0008 0 38");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 1 0x0008 0 39");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 1 0x0008 1 40");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 1 0x0008 1 41");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 1 0x0008 0 42");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 1 0x0008 0 43");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 1 0x0008 1 44");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 1 0x0008 1 45");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 1 0x0008 0 46");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 1 0x0008 0 47");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 1 0x0008 1 48");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Ctrl_OSD_Layer() normal\n", seqNo++));
	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].GRCH[0].GRTRG.word = 2;
	IO_DISP.MAIN[0].GRCH[1].GRTRG.word = 2;
	IO_DISP.MAIN[1].GRCH[0].GRTRG.word = 2;
	IO_DISP.MAIN[1].GRCH[1].GRTRG.word = 2;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, RPGTMG, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 0 0x0004 1 0");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 0 0x0008 1 0");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, RPGTMG, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 1 0x0004 1 0");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, RPGTMG, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDs 3 1 0x0008 1 0");

	*pSeqNo = seqNo;
	return gtrue;
}
#endif /*CtImDisp_CO_DEBUG_DISP*/

/*
 * PUBLIC
 * */

CtImDisp1 *ct_im_disp1_new()
{
	CtImDisp1 *self = (CtImDisp1 *) g_object_new(CT_TYPE_IM_DISP1, NULL);
	if(!self){//Ddim_Assertion(self)
		Ddim_Print(("!! new CtImDisp1 NULL: %s (%d)", __FILE__, __LINE__));
		return NULL;
	}
	return self;
}
