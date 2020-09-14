/*
 *ctimdisp1d.c
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
#include "ctimdisp1d.h"

/*
 * G_DEFINE_语句
 * */
G_DEFINE_TYPE (CtImDisp1d, ct_im_disp1d, IM_TYPE_DISP1_PARENT);

/*
 * 以下开始宏定义
 * */
#define CT_IM_DISP1D_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), CT_TYPE_IM_DISP1D, CtImDisp1dPrivate))

/*
 * 内部结构体或类型定义
 * */
struct _CtImDisp1dPrivate
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
static gboolean imDisp1dDoPctest_od(ImDisp1Parent *parent, gint32 *pSeqNo);
#endif /*CtImDisp_CO_DEBUG_DISP*/

/*
 * IMPL
 * */
static void ct_im_disp1d_class_init(CtImDisp1dClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtImDisp1dPrivate));
}

static void ct_im_disp1d_init(CtImDisp1d *self)
{
	//CtImDisp1dPrivate *priv = CT_IM_DISP1D_GET_PRIVATE(self);
#ifdef CtImDisp_CO_DEBUG_DISP
	ImDisp1Parent *parent = (ImDisp1Parent *)self;
	parent->pctestFunc = imDisp1dDoPctest_od;
#endif /*CtImDisp_CO_DEBUG_DISP*/
}

static void dispose_od(GObject *object)
{
//	CtImDisp1d *self = CT_IM_DISP1D(object);
//	CtImDisp1dPrivate *priv = CT_IM_DISP1D_GET_PRIVATE(self);
	/*释放创建的对象1*/
//	if (priv->objectMine) {
//		g_object_unref(priv->objectMine);
//		priv->objectMine = NULL;
//	}
	G_OBJECT_CLASS (ct_im_disp1d_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
//	CtImDisp1d *self = CT_IM_DISP1D(object);
//	CtImDisp1dPrivate *priv = CT_IM_DISP1D_GET_PRIVATE(self);
	/*释放创建的内存2*/
//	if(self->name)
//	{
//		free(self->name);
//		self->name =NULL;
//	}
	G_OBJECT_CLASS (ct_im_disp1d_parent_class)->finalize(object);
}


#ifdef CtImDisp_CO_DEBUG_DISP
static gboolean imDisp1dDoPctest_od(ImDisp1Parent *parent, gint32 *pSeqNo)
{
//	CtImDisp1d *self = (CtImDisp1d *)parent;
	gint32 seqNo = *pSeqNo;
	gint32 i, j;
	ImDisp1Group *imDisp1Group = (ImDisp1Group *)im_disp1_parent_get_group(parent);

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_OSD_Parameter_Reflect_Timing() normal\n", seqNo++));

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].GRCH[0].GRTRG.word = 2;
	IO_DISP.MAIN[0].GRCH[1].GRTRG.word = 2;
	IO_DISP.MAIN[1].GRCH[0].GRTRG.word = 2;
	IO_DISP.MAIN[1].GRCH[1].GRTRG.word = 2;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, E_IM_DISP_RPGTMG_VSYNC_FRAME_TOP
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDRefTiming 0 0x0004 1");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, E_IM_DISP_RPGTMG_VSYNC_VSYNC
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDRefTiming 0 0x0008 1");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0/1, E_IM_DISP_RPGTMG_VSYNC_FRAME_TOP
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDRefTiming 0 0x000C 0");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, E_IM_DISP_RPGTMG_VSYNC_FRAME_TOP
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDRefTiming 1 0x0004 1");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, E_IM_DISP_RPGTMG_VSYNC_VSYNC
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDRefTiming 1 0x0008 1");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0/1, E_IM_DISP_RPGTMG_VSYNC_FRAME_TOP
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDRefTiming 1 0x000C 0");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_OSD_Parameter_Reflect_Timing() error\n", seqNo++));
	// LCD setting, Parameter error, E_IM_DISP_RPGTMG_VSYNC_VSYNC
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDRefTiming 1 0xFFF3 1");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].GRCH[0].GRTRG.word = 3;
	IO_DISP.MAIN[0].GRCH[1].GRTRG.word = 3;
	IO_DISP.MAIN[1].GRCH[0].GRTRG.word = 3;
	IO_DISP.MAIN[1].GRCH[1].GRTRG.word = 3;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, E_IM_DISP_RPGTMG_VSYNC_FRAME_TOP
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDRefTiming 0 0x0004 1");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, E_IM_DISP_RPGTMG_VSYNC_FRAME_TOP
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDRefTiming 1 0x0008 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_OSD_Parameter_Reflect_Timing() normal\n", seqNo++));

	IO_DISP.MAIN[0].GRCH[0].GRTRG.word = 2;
	IO_DISP.MAIN[0].GRCH[1].GRTRG.word = 2;
	IO_DISP.MAIN[1].GRCH[0].GRTRG.word = 2;
	IO_DISP.MAIN[1].GRCH[1].GRTRG.word = 2;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, E_IM_DISP_RPGTMG_VSYNC_FRAME_TOP
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDRefTiming 0 0x0004 1");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, E_IM_DISP_RPGTMG_VSYNC_VSYNC
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDRefTiming 1 0x0008 1");

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDRefTiming 1 0 0x0004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDRefTiming 1 0 0x0008");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDRefTiming 1 1 0x0004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDRefTiming 1 1 0x0008");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_OSD_Parameter_Reflect_Timing() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDRefTiming 0 0 0x0004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDRefTiming 1 1 0x0002");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDRefTiming 1 0 0x000C");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_OSD_Input_Data_Transfer() normal\n", seqNo++));
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDITrans 0 0x0004 0x107F0014");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDITrans 0 0x0008 0x107F0014");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0/1, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDITrans 0 0x000C 0x00000000");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDITrans 1 0x0004 0x107F0014");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDITrans 1 0x0008 0x107F0014");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0/1, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDITrans 1 0x000C 0x00000000");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_OSD_Input_Data_Transfer() error\n", seqNo++));
	// LCD setting, Paremter error, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDITrans 1 0x0001 0x00000000");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, Paremter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDITrans 0 0x0004 0x107F0015");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, Paremter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDITrans 1 0x0008 0x107F0016");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0/1, Paremter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDITrans 0 0x000C 0x107F0017");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_OSD_Input_Data_Transfer() normal\n", seqNo++));
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDITrans 0 0x0004 0x127F0014");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDITrans 1 0x0008 0x127F0014");

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDITrans 1 0 0x0004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDITrans 1 0 0x0008");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDITrans 1 1 0x0004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDITrans 1 1 0x0008");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_OSD_Input_Data_Transfer() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDITrans 0 0 0x0004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDITrans 1 0 0x0002");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDITrans 1 1 0x000C");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_OSD_Territory_Size() normal\n", seqNo++));
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0/1, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDTrSize 0 0x000C 0x00080008");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDTrSize 0 0x0008 0x3FF2FFF4");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDTrSize 1 0x0004 0x3FF6FFF8");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0/1, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDTrSize 1 0x000C 0x00080008");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDTrSize 1 0x0008 0x3FFAFFFC");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_OSD_Territory_Size() error\n", seqNo++));
	// HDMI setting, Paramter error, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDTrSize 0 0x0002 0x00080008");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, Paramter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDTrSize 1 0x0004 0x00080009");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, Paramter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDTrSize 0 0x0008 0x00080006");
	// LCD setting, Paramter error, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDTrSize 1 0x000C 0x00090008");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, Paramter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDTrSize 0 0x0004 0x00060008");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_OSD_Territory_Size() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDTrSize 1 0 0x0004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDTrSize 1 0 0x0008");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDTrSize 1 1 0x0004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDTrSize 1 1 0x0008");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_OSD_Territory_Size() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDTrSize 0 0 0x0008");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDTrSize 1 1 0x000C");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_OSD_Territory_Position() normal\n", seqNo++));
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDTrPos 0 0x0004 0x3FFEFFFC");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDTrPos 0 0x0008 0x3FFAFFF0");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0/1, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDTrPos 0 0x000C 0x00000000");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDTrPos 1 0x0004 0x3FF0FFFE");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDTrPos 1 0x0008 0x3FFCFFFA");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0/1, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDTrPos 1 0x000C 0x00000000");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_OSD_Territory_Position() error\n", seqNo++));
	// LCD setting, Parameter error, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDTrPos 1 0x0001 0x3FFEFFFE");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDTrPos 0 0x0004 0x00000001");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDTrPos 1 0x0008 0x00010000");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0/1, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDTrPos 0 0x000C 0x00010001");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_OSD_Territory_Position() normal\n", seqNo++));
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDTrPos 0 0x0008 0x3FFAFFF0");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDTrPos 1 0x0004 0x3FF0FFFE");

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDTrPos 1 0 0x0004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDTrPos 1 0 0x0008");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDTrPos 1 1 0x0004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDTrPos 1 1 0x0008");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_OSD_Territory_Position() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDTrPos 0 0 0x0008");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDTrPos 1 1 0x000C");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_OSD_Area0_Switch() normal\n", seqNo++));
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAreaSw 0 0x0004 1");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0/1, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAreaSw 0 0x000C 3");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAreaSw 0 0x0008 2");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAreaSw 1 0x0004 1");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0/1, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAreaSw 1 0x000C 3");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAreaSw 1 0x0008 2");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_OSD_Area0_Switch() error\n", seqNo++));
	// LCD setting, Parameter error, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAreaSw 1 0x0002 2");
	// LCD setting, Parameter error, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAreaSw 1 0xFFF3 2");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_OSD_Area0_Switch() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAreaSw 1 0 0x0004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAreaSw 1 0 0x0008");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAreaSw 1 1 0x0004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAreaSw 1 1 0x0008");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_OSD_Area0_Switch() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAreaSw 0 1 0x0004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAreaSw 1 0 0x000C");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_OSD_Area0_Monitor() normal\n", seqNo++));

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].GRCH[0].GRSCCTL.bit.IDM = 3;
	IO_DISP.MAIN[0].GRCH[1].GRSCCTL.bit.IDM = 2;
	IO_DISP.MAIN[1].GRCH[0].GRSCCTL.bit.IDM = 1;
	IO_DISP.MAIN[1].GRCH[1].GRSCCTL.bit.IDM = 3;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAreaMon 1 0 0x0004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAreaMon 1 0 0x0008");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAreaMon 1 1 0x0004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAreaMon 1 1 0x0008");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_OSD_Area0_Monitor() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAreaMon 0 0 0x0004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAreaMon 1 1 0xFFF3");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAreaMon 1 1 0x000C");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_OSD_Area_Size() normal\n", seqNo++));

	// Clear
	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	for(i = 0; i < 2; i++){
		for(j = 0; j < D_IM_DISP_OSD_DISPLAY_AREA_COUNT; j++){
			IO_DISP.MAIN[0].GRCH[i].GRISIZE[j].word = 0;
			IO_DISP.MAIN[1].GRCH[i].GRISIZE[j].word = 0;
		}
	}
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, Normal, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDASize 0 0x0004 1 0x00080008");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, Normal, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDASize 0 0x0008 10 0x3FFEFFF8");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, Normal, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDASize 1 0x0004 1 0x00080008");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, Normal, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDASize 1 0x0008 10 0x3FFEFFF8");

	// Clear
	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	for(i = 0; i < 2; i++){
		for(j = 0; j < D_IM_DISP_OSD_DISPLAY_AREA_COUNT; j++){
			IO_DISP.MAIN[0].GRCH[i].GRISIZE[j].word = 0;
			IO_DISP.MAIN[1].GRCH[i].GRISIZE[j].word = 0;
		}
	}
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0/1, Normal, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDASize 0 0x000C 10 0x00080008");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0/1, Normal, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDASize 1 0x000C 10 0x00080008");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_OSD_Area_Size() error\n", seqNo++));
	// LCD setting, Parameter error, Normal, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDASize 1 0x0001 10 0x00080008");
	// HDMI setting, Parameter error, Normal, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDASize 0 0x000C 11 0x00080008");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, Normal, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDASize 1 0x0004 1 0x0008000A");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, Normal, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDASize 0 0x0008 10 0x00080000");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, Normal, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDASize 1 0x0004 1 0x00090008");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, Normal, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDASize 0 0x0008 10 0x00060008");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_OSD_Area_Size() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDASize 1 0 0x0004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDASize 1 0 0x0008");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDASize 1 1 0x0004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDASize 1 1 0x0008");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_OSD_Area_Size() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDASize 0 0 0x0004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDASize 1 1 0x000C");

	// Clear
	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	for(i = 0; i < 2; i++){
		for(j = 0; j < D_IM_DISP_OSD_DISPLAY_AREA_COUNT; j++){
			IO_DISP.MAIN[0].GRCH[i].GRISIZE[j].word = 0;
			IO_DISP.MAIN[1].GRCH[i].GRISIZE[j].word = 0;
		}
	}
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_OSD_Area_Addr() normal\n", seqNo++));

	// Clear
	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	for(i = 0; i < 2; i++){
		for(j = 0; j < D_IM_DISP_OSD_ADDR_0_BANK_SIZE; j++){
			IO_DISP.MAIN[0].GRCH[i].GRSA0[j].word = 0;
			IO_DISP.MAIN[1].GRCH[i].GRSA0[j].word = 0;
		}
		for(j = 0; j < D_IM_DISP_OSD_ADDR_BANK_SIZE; j++){
			IO_DISP.MAIN[0].GRCH[i].GRSA[j].word = 0;
			IO_DISP.MAIN[1].GRCH[i].GRSA[j].word = 0;
		}
	}
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, E_IM_DISP_OSD_SA_BANK_NO_0_0, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAAddr 0 0x0004 0 0xFFFFFFF8");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, E_IM_DISP_OSD_SA_BANK_NO_0_2, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAAddr 0 0x0008 2 0xFFFFFFF8");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, E_IM_DISP_OSD_SA_BANK_NO_1, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAAddr 0 0x000C 4 0xFFFFFFF8");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, E_IM_DISP_OSD_SA_BANK_NO_5, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAAddr 0 0x000C 8 0xFFFFFFF8");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, E_IM_DISP_OSD_SA_BANK_NO_7, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAAddr 0 0x0004 10 0xFFFFFFF8");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, E_IM_DISP_OSD_SA_BANK_NO_9, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAAddr 0 0x0008 12 0xFFFFFFF8");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, E_IM_DISP_OSD_SA_BANK_NO_0_1, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAAddr 1 0x0004 1 0xFFFFFFF8");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, E_IM_DISP_OSD_SA_BANK_NO_0_3, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAAddr 1 0x0008 3 0xFFFFFFF8");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, E_IM_DISP_OSD_SA_BANK_NO_2, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAAddr 1 0x000C 5 0xFFFFFFF8");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, E_IM_DISP_OSD_SA_BANK_NO_4, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAAddr 1 0x0008 7 0xFFFFFFF8");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, E_IM_DISP_OSD_SA_BANK_NO_6, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAAddr 1 0x0004 9 0xFFFFFFF8");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, E_IM_DISP_OSD_SA_BANK_NO_8, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAAddr 1 0x000C 11 0xFFFFFFF8");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_OSD_Area_Addr() error\n", seqNo++));
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, E_IM_DISP_OSD_SA_BANK_NO_1, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAAddr 1 0x0002 4 0xFFFFFFF8");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, E_IM_DISP_OSD_SA_BANK_NO_9, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAAddr 0 0x000C 12 0xFFFFFFF9");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_OSD_Area_Addr() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAAddr 1 0 0x0004 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAAddr 1 0 0x0004 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAAddr 1 0 0x0008 4");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAAddr 1 0 0x0008 12");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAAddr 1 1 0x0004 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAAddr 1 1 0x0004 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAAddr 1 1 0x0008 4");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAAddr 1 1 0x0008 12");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_OSD_Area_Addr() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAAddr 0 1 0x0004 12");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0/1, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAAddr 1 0 0x000C 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0/1, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAAddr 1 0 0xFFF3 0");

	// Clear
	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	for(i = 0; i < 2; i++){
		for(j = 0; j < D_IM_DISP_OSD_ADDR_0_BANK_SIZE; j++){
			IO_DISP.MAIN[0].GRCH[i].GRSA0[j].word = 0;
			IO_DISP.MAIN[1].GRCH[i].GRSA0[j].word = 0;
		}
		for(j = 0; j < D_IM_DISP_OSD_ADDR_BANK_SIZE; j++){
			IO_DISP.MAIN[0].GRCH[i].GRSA[j].word = 0;
			IO_DISP.MAIN[1].GRCH[i].GRSA[j].word = 0;
		}
	}
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_OSD_Area_Adata_Addr() normal\n", seqNo++));
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no, adr.
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAAdataAddr 0 0x0004 0 0xFFFFFF18");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, bank_no, adr.
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAAdataAddr 0 0x0008 2 0xFFFFFF28");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0/1, bank_no, adr.
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAAdataAddr 0 0x000C 4 0xFFFFFF38");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0/1, bank_no, adr.
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAAdataAddr 0 0x000C 8 0xFFFFFF48");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no, adr.
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAAdataAddr 1 0x0004 1 0xFFFFFF58");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, bank_no, adr.
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAAdataAddr 1 0x0008 3 0xFFFFFF68");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0/1, bank_no, adr.
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAAdataAddr 1 0x000C 5 0xFFFFFF78");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, bank_no, adr.
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAAdataAddr 1 0x0008 7 0xFFFFFF88");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no, adr.
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAAdataAddr 1 0x0004 9 0xFFFFFF98");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_OSD_Area_Adata_Addr() error\n", seqNo++));
	// LCD setting, E_IM_DISP_SEL_LAYER_DCORE(error), bank_no, adr.
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAAdataAddr 1 0x0002 4 0xFFFFFFF8");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0/1, bank_no(error), adr.
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAAdataAddr 0 0x000C 10 0xFFFFFFF8");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0/1, bank_no, adr.(error)
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAAdataAddr 1 0x000C 9 0xFFFFFFF9");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_OSD_Area_Adata_Addr() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAAdataAddr 1 0 0x0004 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAAdataAddr 1 0 0x0008 2");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAAdataAddr 1 0 0x0004 4");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAAdataAddr 1 0 0x0008 8");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAAdataAddr 1 1 0x0004 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAAdataAddr 1 1 0x0008 3");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAAdataAddr 1 1 0x0004 5");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAAdataAddr 1 1 0x0008 7");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAAdataAddr 1 1 0x0004 9");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_OSD_Area_Adata_Addr() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAAdataAddr 0 0 0x0004 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, bank_no(error)
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAAdataAddr 1 0 0x0008 10");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0/1(error), bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAAdataAddr 1 1 0x000C 8");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0/1(error), bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAAdataAddr 1 1 0xFFF3 8");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_OSD_Lfd() normal\n", seqNo++));
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no, grhga
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDALfd 0 0x0004 1 0xFF18");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, bank_no, grhga
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDALfd 0 0x0008 3 0xFF28");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0/1, bank_no, grhga
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDALfd 0 0x000C 5 0xFF38");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no, grhga
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDALfd 0 0x0004 7 0xFF48");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, bank_no, grhga
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDALfd 0 0x0008 9 0xFF58");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0/1, bank_no, grhga
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDALfd 1 0x000C 0 0xFF68");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no, grhga
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDALfd 1 0x0004 2 0xFF78");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, bank_no, grhga
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDALfd 1 0x0008 4 0xFF88");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0/1, bank_no, grhga
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDALfd 1 0x000C 8 0xFF98");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_OSD_Lfd() error\n", seqNo++));
	// HDMI setting, E_IM_DISP_SEL_LAYER_MAIN(error), bank_no, grhga
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDALfd 0 0x0001 1 0xF000");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0/1, bank_no(error), grhga
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDALfd 1 0x000C 10 0xF000");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0/1, bank_no, grhga(error)
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDALfd 0 0x000C 0 0");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0/1, bank_no, grhga(error)
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDALfd 1 0x000C 1 0x10000");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0/1, bank_no, grhga(error)
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDALfd 0 0x000C 2 0x001F");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_OSD_Lfd() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDALfd 1 0 0x0004 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDALfd 1 0 0x0008 3");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDALfd 1 0 0x0004 5");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDALfd 1 0 0x0008 7");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDALfd 1 1 0x0004 9");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDALfd 1 1 0x0008 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDALfd 1 1 0x0004 2");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDALfd 1 1 0x0008 4");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDALfd 1 1 0x0008 8");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_OSD_Lfd() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDALfd 0 0 0x0004 4");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, bank_no(error)
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDALfd 1 1 0x0008 10");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDI setting, E_IM_DISP_SEL_LAYER_OSD_0/1(error), bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDALfd 1 0 0x000C 2");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDI setting, E_IM_DISP_SEL_LAYER_OSD_0/1(error), bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDALfd 1 0 0xFFF3 2");

	// Clear
	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	for(i = 0; i < 2; i++){
		for(j = 0; j < D_IM_DISP_OSD_DISPLAY_AREA_COUNT; j++){
			IO_DISP.MAIN[0].GRCH[i].GRHGA[j].word = 0;
			IO_DISP.MAIN[1].GRCH[i].GRHGA[j].word = 0;
		}
	}
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_OSD_Adata_Lfd() normal\n", seqNo++));
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no, grhga
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAdataLfd 0 0x0004 1 0xFF18");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, bank_no, grhga
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAdataLfd 0 0x0008 3 0xFF28");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0/1, bank_no, grhga
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAdataLfd 0 0x000C 5 0xFF38");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no, grhga
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAdataLfd 0 0x0004 7 0xFF48");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, bank_no, grhga
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAdataLfd 0 0x0008 9 0xFF58");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0/1, bank_no, grhga
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAdataLfd 1 0x000C 0 0xFF68");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no, grhga
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAdataLfd 1 0x0004 2 0xFF78");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, bank_no, grhga
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAdataLfd 1 0x0008 4 0xFF88");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0/1, bank_no, grhga
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAdataLfd 1 0x000C 8 0xFF98");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_OSD_Adata_Lfd() error\n", seqNo++));
	// HDMI setting, E_IM_DISP_SEL_LAYER_MAIN(error), bank_no, grhga
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAdataLfd 0 0x0001 1 0xF000");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0/1, bank_no(error), grhga
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAdataLfd 1 0x000C 10 0xF000");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0/1, bank_no, grhga(error)
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAdataLfd 0 0x000C 0 0");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0/1, bank_no, grhga(error)
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAdataLfd 1 0x000C 1 0x10000");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0/1, bank_no, grhga(error)
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAdataLfd 0 0x000C 2 0x001F");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_OSD_Adata_Lfd() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAdataLfd 1 0 0x0004 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAdataLfd 1 0 0x0008 3");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAdataLfd 1 0 0x0004 5");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAdataLfd 1 0 0x0008 7");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAdataLfd 1 1 0x0004 9");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAdataLfd 1 1 0x0008 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAdataLfd 1 1 0x0004 2");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAdataLfd 1 1 0x0008 4");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAdataLfd 1 1 0x0008 8");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_OSD_Adata_Lfd() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAdataLfd 0 0 0x0004 4");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, bank_no(error)
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAdataLfd 1 1 0x0008 10");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0/1(error), bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAdataLfd 1 0 0x000C 2");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0/1(error), bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAdataLfd 1 0 0xFFF3 2");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_OSD_Display_Position() normal\n", seqNo++));
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no, grdsta
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDPos 0 0x0004 0 0x01000200");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0/1, bank_no, grdsta
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDPos 0 0x000C 9 0x3FFEFFFE");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, bank_no, grdsta
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDPos 0 0x0008 1 0x03000400");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no, grdsta
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDPos 1 0x0004 0 0x01000200");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0/1, bank_no, grdsta
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDPos 1 0x000C 9 0x3FFEFFFE");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, bank_no, grdsta
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDPos 1 0x0008 1 0x03000400");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_OSD_Display_Position() error\n", seqNo++));
	// HDMI setting, E_IM_DISP_SEL_LAYER_DCORE(error), bank_no, grdsta
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDPos 0 0x0002 8 0x3FFEFFFE");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0/1, bank_no(error), grdsta
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDPos 1 0x000C 10 0x3FFEFFFE");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no, grdsta(DSH error)
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDPos 0 0x0004 0 0x00000001");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, bank_no, grdsta(DSV error)
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDPos 1 0x0008 1 0x00010000");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_OSD_Display_Position() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDPos 1 0 0x0004 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDPos 1 0 0x0008 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDPos 1 0 0x0004 9");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDPos 1 0 0x0008 9");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDPos 1 1 0x0004 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDPos 1 1 0x0008 3");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDPos 1 1 0x0004 5");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDPos 1 1 0x0004 9");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDPos 1 1 0x0008 9");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_OSD_Display_Position() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDPos 0 0 0x0008 3");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0/1(error), bank_no
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDPos 1 1 0x000C 7");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, bank_no(error)
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDPos 1 0 0x0004 10");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_OSD_IPO() normal\n", seqNo++));
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, ipo
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIPO 1 0x0004 0x03000102");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, ipo
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIPO 0 0x0008 0x03000201");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, ipo
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIPO 1 0x0008 0x03010002");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, ipo
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIPO 0 0x0004 0x03010200");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, ipo
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIPO 1 0x0004 0x03020001");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, ipo
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIPO 0 0x0008 0x03020100");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, ipo
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIPO 1 0x0008 0x02000103");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, ipo
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIPO 0 0x0004 0x02000301");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, ipo
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIPO 1 0x0004 0x02010003");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, ipo
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIPO 0 0x0008 0x02010300");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, ipo
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIPO 1 0x0008 0x02030001");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, ipo
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIPO 0 0x0004 0x02030100");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, ipo
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIPO 1 0x0004 0x01000203");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, ipo
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIPO 0 0x0008 0x01000302");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, ipo
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIPO 1 0x0008 0x01020003");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, ipo
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIPO 0 0x0004 0x01020300");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, ipo
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIPO 1 0x0004 0x01030002");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, ipo
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIPO 0 0x0008 0x01030200");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, ipo
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIPO 1 0x0008 0x00010203");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, ipo
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIPO 0 0x0004 0x00010302");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, ipo
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIPO 1 0x0004 0x00020103");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, ipo
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIPO 0 0x0008 0x00020301");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, ipo
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIPO 1 0x0008 0x00030102");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, ipo
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIPO 0 0x0004 0x00030201");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_OSD_IPO() error\n", seqNo++));
	// E_IM_DISP_SEL_LAYER_MAIN, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIPO 0 0x0001 0x03020001");
	// Parameter error, U_IM_DISP_GRIPO
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIPO 1 0x000C 0x02030100");
	// E_IM_DISP_SEL_LAYER_OSD_0, U_IM_DISP_GRIPO
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIPO 0 0x0004 0x03020101");
	// E_IM_DISP_SEL_LAYER_OSD_1, U_IM_DISP_GRIPO
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIPO 1 0x0008 0x03010201");
	// E_IM_DISP_SEL_LAYER_OSD_0, U_IM_DISP_GRIPO
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIPO 0 0x0004 0x01030201");
	// E_IM_DISP_SEL_LAYER_OSD_1, U_IM_DISP_GRIPO
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIPO 1 0x0008 0x03020201");
	// E_IM_DISP_SEL_LAYER_OSD_0, U_IM_DISP_GRIPO
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIPO 0 0x0004 0x02030201");
	// E_IM_DISP_SEL_LAYER_OSD_1, U_IM_DISP_GRIPO
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIPO 1 0x0008 0x03030201");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_OSD_IPO() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetIPO 1 0 0x0004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp GetIPO 1 0 0x0008");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetIPO 1 1 0x0004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp GetIPO 1 1 0x0008");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_OSD_IPO() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetIPO 0 1 0x0004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0/1(error)
	im_disp1_parent_pctest_wrap(parent, "imdisp GetIPO 1 0 0x000C");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0/1(error)
	im_disp1_parent_pctest_wrap(parent, "imdisp GetIPO 1 0 0xFFF3");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_OSD_Area_Enable() normal\n", seqNo++));
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, area_enable
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAreaEn 0 0x0004 0x0000");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0/1, area_enable
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAreaEn 0 0x000C 0x03FF");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, area_enable
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAreaEn 0 0x0008 0x0001");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, area_enable
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAreaEn 1 0x0004 0x0000");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0/1, area_enable
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAreaEn 1 0x000C 0x03FF");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, area_enable
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAreaEn 1 0x0008 0x0001");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_OSD_Area_Enable() error\n", seqNo++));
	// HDMI setting, E_IM_DISP_SEL_LAYER_MAIN(error), area_enable
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAreaEn 0 0x0001 0x03FF");
	// LCD setting, E_IM_DISP_SEL_LAYER_MAIN(error), area_enable
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAreaEn 1 0x0001 0x03FF");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_OSD_Area_Enable() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAreaEn 1 0 0x0004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAreaEn 1 0 0x0008");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAreaEn 1 1 0x0004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAreaEn 1 1 0x0008");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_OSD_Area_Enable() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAreaEn 0 1 0x0004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0/1(error)
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAreaEn 1 0 0x000C");

	// Clear
	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	for(i = 0; i < 2; i++){
		IO_DISP.MAIN[0].GRCH[i].GRAREN.word = 0;
		IO_DISP.MAIN[1].GRCH[i].GRAREN.word = 0;
	}
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_OSD_Blink() normal\n", seqNo++));
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, blink
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDBlnk 0 0x0004 0x0000");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0/1, blink
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDBlnk 0 0x000C 0x03FF");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, blink
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDBlnk 0 0x0008 0x0001");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, blink
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDBlnk 1 0x0004 0x0000");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0/1, blink
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDBlnk 1 0x000C 0x03FF");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, blink
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDBlnk 1 0x0008 0x0001");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_OSD_Blink() error\n", seqNo++));
	// HDMI setting, E_IM_DISP_SEL_LAYER_MAIN/E_IM_DISP_SEL_LAYER_DCORE(error), area_enable
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDBlnk 0 0x0003 0x03FF");
	// HDMI setting, other(error), area_enable
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDBlnk 0 0xFFF3 0x03FF");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_OSD_Blink() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDBlnk 1 0 0x0004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDBlnk 1 0 0x0008");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDBlnk 1 1 0x0004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDBlnk 1 1 0x0008");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_OSD_Blink() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDBlnk 0 0 0x0004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0/1(error)
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDBlnk 1 0 0x000C");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, other(error)
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDBlnk 1 0 0xFFF3");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_OSD_Blink_Timer() normal\n", seqNo++));
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, grblink0~grblink5
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDBTim 0 0x0004 "
			"0x00000000 0x00000000 0x00000000 0x00000000 0x00000000");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0/1, grblink0~grblink5
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDBTim 0 0x000C "
			"0x3F3F3F3F 0x3F3F3F3F 0x3F3F3F3F 0x3F3F3F3F 0x3F3F3F3F");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, grblink0~grblink5
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDBTim 0 0x0008 "
			"0x04030201 0x08070605 0x0C0B0A09 0x100F0E0D 0x14131211");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, grblink0~grblink5
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDBTim 1 0x0004 "
			"0x00000000 0x00000000 0x00000000 0x00000000 0x00000000");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0/1, grblink0~grblink5
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDBTim 1 0x000C "
			"0x3F3F3F3F 0x3F3F3F3F 0x3F3F3F3F 0x3F3F3F3F 0x3F3F3F3F");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, grblink0~grblink5
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDBTim 1 0x0018 "
			"0x14131211 0x18171615 0x1C1B1A19 0x111F1E1D 0x24232221");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_OSD_Blink_Timer() error\n", seqNo++));
	// HDMI setting, E_IM_DISP_SEL_LAYER_MAIN(error), grblink0~grblink5
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDBTim 0 0x0001 "
			"0x3F3F3F3F 0x3F3F3F3F 0x3F3F3F3F 0x3F3F3F3F 0x3F3F3F3F");
	// LCD setting, E_IM_DISP_SEL_LAYER_MAIN(error), grblink0~grblink5
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDBTim 1 0xFFF3 "
			"0x3F3F3F3F 0x3F3F3F3F 0x3F3F3F3F 0x3F3F3F3F 0x3F3F3F3F");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_OSD_Blink_Timer() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDBTim 1 0 0x0004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDBTim 1 0 0x0008");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDBTim 1 1 0x0004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDBTim 1 1 0x0008");

	*pSeqNo = seqNo;
	return gtrue;
}
#endif /*CtImDisp_CO_DEBUG_DISP*/

/*
 * PUBLIC
 * */

CtImDisp1d *ct_im_disp1d_new()
{
	CtImDisp1d *self = (CtImDisp1d *) g_object_new(CT_TYPE_IM_DISP1D, NULL);
	if(!self){//Ddim_Assertion(self)
		Ddim_Print(("!! new CtImDisp1d NULL: %s (%d)", __FILE__, __LINE__));
		return NULL;
	}
	return self;
}
