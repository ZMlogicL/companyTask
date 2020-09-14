/*
 *ctimdisp2m.c
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

#include "ctimdisp4.h"//variable
#include "ctimdisp3.h"//static func
#include "ctimdisp3a.h"

#include "imdisp2group.h"
#include "ctimdisp2m.h"

/*
 * G_DEFINE_语句
 * */
G_DEFINE_TYPE (CtImDisp2m, ct_im_disp2m, IM_TYPE_DISP2_PARENT);

/*
 * 以下开始宏定义
 * */
#define CT_IM_DISP2M_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), CT_TYPE_IM_DISP2M, CtImDisp2mPrivate))

/*
 * 内部结构体或类型定义
 * */
struct _CtImDisp2mPrivate
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
static void disp2mDoMain_od(ImDisp2Parent *parent, gint32 argc, char **argv);
#endif /*CtImDisp_CO_DEBUG_DISP*/

/*
 * IMPL
 * */
static void ct_im_disp2m_class_init(CtImDisp2mClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtImDisp2mPrivate));
}

static void ct_im_disp2m_init(CtImDisp2m *self)
{
	//CtImDisp2mPrivate *priv = CT_IM_DISP2M_GET_PRIVATE(self);
#ifdef CtImDisp_CO_DEBUG_DISP
	ImDisp2Parent *parent = (ImDisp2Parent *)self;
	parent->doMainFunc = disp2mDoMain_od;
#endif /*CtImDisp_CO_DEBUG_DISP*/
}

static void dispose_od(GObject *object)
{
//	CtImDisp2m *self = CT_IM_DISP2M(object);
//	CtImDisp2mPrivate *priv = CT_IM_DISP2M_GET_PRIVATE(self);
	/*释放创建的对象1*/
//	if (priv->objectMine) {
//		g_object_unref(priv->objectMine);
//		priv->objectMine = NULL;
//	}
	G_OBJECT_CLASS (ct_im_disp2m_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
//	CtImDisp2m *self = CT_IM_DISP2M(object);
//	CtImDisp2mPrivate *priv = CT_IM_DISP2M_GET_PRIVATE(self);
	/*释放创建的内存2*/
//	if(self->name)
//	{
//		free(self->name);
//		self->name =NULL;
//	}
	G_OBJECT_CLASS (ct_im_disp2m_parent_class)->finalize(object);
}

static void outputAntiGamma(const T_IM_DISP_ANTI_GAMMA_TBL* antiTbl)
{
	if(antiTbl->r_anti){
		Ddim_Print(("--- r_anti ---\n"));
		ct_im_disp3a_output_ushort_32_table(antiTbl->r_anti);
	}
	if(antiTbl->g_anti){
		Ddim_Print(("--- g_anti ---\n"));
		ct_im_disp3a_output_ushort_32_table(antiTbl->g_anti);
	}
	if(antiTbl->b_anti){
		Ddim_Print(("--- b_anti ---\n"));
		ct_im_disp3a_output_ushort_32_table(antiTbl->b_anti);
	}
}

static void outputMainGamma(const T_IM_DISP_GAMMA_TBL_IN* gammaTbl)
{
	if(gammaTbl->r_data){
		Ddim_Print(("--- r_data ---\n"));
		ct_im_disp3a_output_ushort_32_table(gammaTbl->r_data);
	}
	if(gammaTbl->g_data){
		Ddim_Print(("--- g_data ---\n"));
		ct_im_disp3a_output_ushort_32_table(gammaTbl->g_data);
	}
	if(gammaTbl->b_data){
		Ddim_Print(("--- b_data ---\n"));
		ct_im_disp3a_output_ushort_32_table(gammaTbl->b_data);
	}
}

#ifdef CtImDisp_CO_DEBUG_DISP
static void disp2mDoMain_od(ImDisp2Parent *parent, gint32 argc, char **argv)
{
	ImDisp2Group *disp2Group = (ImDisp2Group *)im_disp2_parent_get_group(parent);
	CtImDisp4 *ctImDisp4 = (CtImDisp4 *)im_disp2_group_get_disp4(disp2Group);
	gint i = 0;
	gint32 error = D_DDIM_OK;
	guint32 layer = 0;
	ImDisp2Group *imDisp2Group = (ImDisp2Group *)im_disp2_parent_get_group(parent);
	guchar *pImDispPclkCounter = im_disp2_group_get_pclk_counter(imDisp2Group);
	CtImDisp3 *disp3 = (CtImDisp3 *)im_disp2_group_get_disp3(imDisp2Group);
	CtImDisp3a *disp3a = (CtImDisp3a *)im_disp2_group_get_disp3a(imDisp2Group);

	if (strcmp((gchar *) argv[1], "SetOSDBTim") == 0)
	{
		//Im_DISP_Set_OSD_Blink_Timer

		// argc=9
		// argv[0] "imdisp"
		// argv[1] "SetOSDBTim"
		// argv[2] block(0/1)
		// argv[3] layer
		// argv[4] grblink[0]
		// argv[5] grblink[2]
		// argv[6] grblink[3]
		// argv[7] grblink[4]
		// argv[8] grblink[5]

		if (argc == 9)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			layer = strtoul(argv[3], NULL, 0);
			U_IM_DISP_GRBLINK grblink;
			grblink.word[0] = strtoul(argv[4], NULL, 0);
			grblink.word[1] = strtoul(argv[5], NULL, 0);
			grblink.word[2] = strtoul(argv[6], NULL, 0);
			grblink.word[3] = strtoul(argv[7], NULL, 0);
			grblink.word[4] = strtoul(argv[8], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_dump_reg_osd_blink_timer(disp3, block); /* pgr0539 */
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Set_OSD_Blink_Timer(block, (E_IM_DISP_SEL_LAYER) layer, grblink); /* pgr0539 */
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_OSD_Blink_Timer error=%08X\n",error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_dump_reg_osd_blink_timer(disp3, block);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 9\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "GetOSDBTim") == 0)
	{
		//Im_DISP_Get_OSD_Blink_Timer

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "GetOSDBTim"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)
		// argv[4] layer

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			layer = strtoul(argv[4], NULL, 0);
			U_IM_DISP_GRBLINK grblink = { { 0, 0, 0, 0, 0 } };

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_OSD_Blink_Timer(block, (E_IM_DISP_SEL_LAYER) layer, NULL); /* pgr0539 */
			}
			else
			{
				error = Im_DISP_Get_OSD_Blink_Timer(block, (E_IM_DISP_SEL_LAYER) layer, &grblink); /* pgr0539 */
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_OSD_Blink_Timer error=%08X\n",error));
			}
			else
			{
				ct_im_disp3_dump_reg_osd_blink_timer(disp3, block);

				Ddim_Print(("Layer = %02X\n", layer));
				Ddim_Print(("[U_IM_DISP_GRBLINK]\n"));
				Ddim_Print(("BTIMH_0:%08X, BTIML_0:%08X\n", grblink.bit.BTIMH_0, grblink.bit.BTIML_0));
				Ddim_Print(("BTIMH_1:%08X, BTIML_1:%08X\n", grblink.bit.BTIMH_1, grblink.bit.BTIML_1));
				Ddim_Print(("BTIMH_2:%08X, BTIML_2:%08X\n", grblink.bit.BTIMH_2, grblink.bit.BTIML_2));
				Ddim_Print(("BTIMH_3:%08X, BTIML_3:%08X\n", grblink.bit.BTIMH_3, grblink.bit.BTIML_3));
				Ddim_Print(("BTIMH_4:%08X, BTIML_4:%08X\n", grblink.bit.BTIMH_4, grblink.bit.BTIML_4));
				Ddim_Print(("BTIMH_5:%08X, BTIML_5:%08X\n", grblink.bit.BTIMH_5, grblink.bit.BTIML_5));
				Ddim_Print(("BTIMH_6:%08X, BTIML_6:%08X\n", grblink.bit.BTIMH_6, grblink.bit.BTIML_6));
				Ddim_Print(("BTIMH_7:%08X, BTIML_7:%08X\n", grblink.bit.BTIMH_7, grblink.bit.BTIML_7));
				Ddim_Print(("BTIMH_8:%08X, BTIML_8:%08X\n", grblink.bit.BTIMH_8, grblink.bit.BTIML_8));
				Ddim_Print(("BTIMH_9:%08X, BTIML_9:%08X\n", grblink.bit.BTIMH_9, grblink.bit.BTIML_9));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "SetOSDRes") == 0)
	{
		//Im_DISP_Set_OSD_Resize

		// argc=9
		// argv[0] "imdisp"
		// argv[1] "SetOSDRes"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)
		// argv[4] layer
		// argv[5] rsz0
		// argv[6] rsz1
		// argv[7] rsz2
		// argv[8] rsz3

		if (argc == 9)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			layer = strtoul(argv[4], NULL, 0);
			T_IM_DISP_RESIZE resize;
			resize.rsz0 = (E_IM_DISP_RSZSL) strtoul(argv[5], NULL, 0);
			resize.rsz1.word = (ULONG) strtoul(argv[6], NULL, 0);
			resize.rsz2.word = (ULONG) strtoul(argv[7], NULL, 0);
			resize.rsz3.word = (ULONG) strtoul(argv[8], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_dump_reg_osd_resize(disp3, block); /* pgr0539 */
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			if (argv[2][0] == '0')
			{
				error = Im_DISP_Set_OSD_Resize(block, (E_IM_DISP_SEL_LAYER) layer, NULL); /* pgr0539 */
			}
			else
			{
				error = Im_DISP_Set_OSD_Resize(block, (E_IM_DISP_SEL_LAYER) layer, &resize); /* pgr0539 */
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_OSD_Resize error=%08X\n",error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_dump_reg_osd_resize(disp3, block);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 9\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "GetOSDRes") == 0)
	{
		//Im_DISP_Get_OSD_Resize

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "GetOSDRes"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)
		// argv[4] layer

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			layer = strtoul(argv[4], NULL, 0);
			T_IM_DISP_RESIZE resize;
			memset(&resize, 0, sizeof(T_IM_DISP_RESIZE));

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_OSD_Resize(block, (E_IM_DISP_SEL_LAYER) layer, NULL); /* pgr0539 */
			}
			else
			{
				error = Im_DISP_Get_OSD_Resize(block, (E_IM_DISP_SEL_LAYER) layer, &resize); /* pgr0539 */
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_OSD_Resize error=%08X\n",error));
			}
			else
			{
				ct_im_disp3_dump_reg_osd_resize(disp3, block);

				Ddim_Print(("Layer = %02X\n", layer));
				Ddim_Print(("[T_IM_DISP_RESIZE]\n"));
				Ddim_Print(("HRSZSL = %d\n", resize.rsz0));
				Ddim_Print(("HRSZM = 0x%08X, HRSZN = 0x%08X, HRSZOF = 0x%08X\n",
						resize.rsz1.bit.HRSZM, resize.rsz1.bit.HRSZN, resize.rsz1.bit.HRSZOF));
				Ddim_Print(("VRSZM = 0x%08X, VRSZN = 0x%08X, VRSZOF = 0x%08X\n",
						resize.rsz2.bit.VRSZM, resize.rsz2.bit.VRSZN, resize.rsz2.bit.VRSZOF));
				Ddim_Print(("HCSTA = 0x%08X, VCSTA = 0x%08X\n", resize.rsz3.bit.HCSTA, resize.rsz3.bit.VCSTA));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "SetOSDMax") == 0)
	{
		//Im_DISP_Set_OSD_Matrix

		// argc=8
		// argv[0] "imdisp"
		// argv[1] "SetOSDMax"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)
		// argv[4] layer
		// argv[5] gry2r[0]
		// argv[6] gry2r[1]
		// argv[7] gry2r[2]

		if (argc == 8)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			layer = strtoul(argv[4], NULL, 0);
			U_IM_DISP_GRY2R gry2r[D_IM_DISP_MATRIX_SIZE];
			gry2r[0].word = strtoul(argv[5], NULL, 0);
			gry2r[1].word = strtoul(argv[6], NULL, 0);
			gry2r[2].word = strtoul(argv[7], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_dump_reg_osd_matrix(disp3, block); /* pgr0539 */
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Set_OSD_Matrix(block, (E_IM_DISP_SEL_LAYER) layer, NULL); /* pgr0539 */
			}
			else
			{
				error = Im_DISP_Set_OSD_Matrix(block, (E_IM_DISP_SEL_LAYER) layer, gry2r); /* pgr0539 */
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_OSD_Matrix error=%08X\n",error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_dump_reg_osd_matrix(disp3, block);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 8\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "GetOSDMax") == 0)
	{
		//Im_DISP_Get_OSD_Matrix

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "GetOSDMax"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)
		// argv[4] layer

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			layer = strtoul(argv[4], NULL, 0);
			U_IM_DISP_GRY2R gry2r[D_IM_DISP_MATRIX_SIZE];
			for (i = 0; i < D_IM_DISP_MATRIX_SIZE; i++)
			{
				gry2r[i].word = 0;
			}

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_OSD_Matrix(block, (E_IM_DISP_SEL_LAYER) layer, NULL); /* pgr0539 */
			}
			else
			{
				error = Im_DISP_Get_OSD_Matrix(block, (E_IM_DISP_SEL_LAYER) layer, gry2r); /* pgr0539 */
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_OSD_Matrix error=%08X\n",error));
			}
			else
			{
				ct_im_disp3_dump_reg_osd_matrix(disp3, block);

				Ddim_Print(("Layer = %02X\n", layer));
				ct_im_disp3_print_param_osd_matrix(gry2r);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "SetOSDAph") == 0)
	{
		//Im_DISP_Set_OSD_Alpha

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "SetOSDAph"
		// argv[2] block(0/1)
		// argv[3] layer
		// argv[4] alpha

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			layer = strtoul(argv[3], NULL, 0);
			ULONG alpha = strtoul(argv[4], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].GRCH[0].GRALP = %08X\n",
					block, (guint32)IO_DISP.MAIN[block].GRCH[0].GRALP.word)); /* pgr0539 */
			Ddim_Print(("IO_DISP.MAIN[%d].GRCH[1].GRALP = %08X\n",
					block, (guint32)IO_DISP.MAIN[block].GRCH[1].GRALP.word));
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Set_OSD_Alpha(block, (E_IM_DISP_SEL_LAYER) layer, alpha); /* pgr0539 */
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_OSD_Alpha error=%08X\n",error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[0].GRALP = %08X\n",
						block, (guint32)IO_DISP.MAIN[block].GRCH[0].GRALP.word));
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[1].GRALP = %08X\n",
						block, (guint32)IO_DISP.MAIN[block].GRCH[1].GRALP.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "GetOSDAph") == 0)
	{
		//Im_DISP_Get_OSD_Alpha

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "GetOSDAph"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)
		// argv[4] layer

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			layer = strtoul(argv[4], NULL, 0);
			ULONG alpha = 0;

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_OSD_Alpha(block, (E_IM_DISP_SEL_LAYER) layer, NULL); /* pgr0539 */
			}
			else
			{
				error = Im_DISP_Get_OSD_Alpha(block, (E_IM_DISP_SEL_LAYER) layer, &alpha); /* pgr0539 */
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_OSD_Alpha error=%08X\n",error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[0].GRALP = %08X\n",
						block, (guint32)IO_DISP.MAIN[block].GRCH[0].GRALP.word));
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[1].GRALP = %08X\n",
						block, (guint32)IO_DISP.MAIN[block].GRCH[1].GRALP.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("Layer = %02X\n", layer));
				Ddim_Print(("GRALP = 0x%08X\n", (guint32)alpha));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "SetAnTbl") == 0)
	{
		//Im_DISP_Set_Anti_Gamma_Table

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "SetAnTbl"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)
		// argv[4] surface(A:0/B:1)

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			BYTE surface = (BYTE) strtoul(argv[4], NULL, 0);
			T_IM_DISP_ANTI_GAMMA_TBL antiTbl;
			antiTbl.r_anti = (gushort*) ct_im_disp4_get_r_anti_tbla(ctImDisp4);
			antiTbl.g_anti = (gushort*) ct_im_disp4_get_g_anti_tbla(ctImDisp4);
			antiTbl.b_anti = (gushort*) ct_im_disp4_get_b_anti_tbla(ctImDisp4);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			Ddim_Print(("Surface = %02X\n", surface)); /* pgr0539 */
			ct_im_disp3_dump_anti_gamma_table(disp3, block); /* pgr0539 */
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			if (argv[2][0] == '0')
			{
				error = Im_DISP_Set_Anti_Gamma_Table(block, surface, NULL); /* pgr0539 */
			}
			else
			{
				error = Im_DISP_Set_Anti_Gamma_Table(block, surface, &antiTbl); /* pgr0539 */
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_Anti_Gamma_Table error=%08X\n",error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_dump_anti_gamma_table(disp3, block);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "GetAnTbl") == 0)
	{
		//Im_DISP_Get_Anti_Gamma_Table

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "GetAnTbl"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)
		// argv[4] surface(A:0/B:1)

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			BYTE surface = (BYTE) strtoul(argv[4], NULL, 0);
			T_IM_DISP_ANTI_GAMMA_TBL antiTblAa;
			gushort antiRMatrix[256];
			gushort antiGMatrix[256];
			gushort antiBMatrix[256];
			memset(antiRMatrix, 0, (sizeof(gushort) * 256));
			memset(antiGMatrix, 0, (sizeof(gushort) * 256));
			memset(antiBMatrix, 0, (sizeof(gushort) * 256));

			antiTblAa.r_anti = antiRMatrix;
			antiTblAa.g_anti = antiGMatrix;
			antiTblAa.b_anti = antiBMatrix;

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Anti_Gamma_Table(block, surface, NULL); /* pgr0539 */
			}
			else
			{
				error = Im_DISP_Get_Anti_Gamma_Table(block, surface, &antiTblAa); /* pgr0539 */
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Anti_Gamma_Table error=%08X\n", error));
			}
			else
			{
				ct_im_disp3_dump_anti_gamma_table(disp3, block);

				Ddim_Print(("Surface = %02X\n", surface));
				outputAntiGamma(&antiTblAa);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 3\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "SetMainGamTbl") == 0)
	{
		//Im_DISP_Set_Gamma_Table -> Im_DISP_Set_Main_Gamma_Table

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "SetMainGamTbl"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)
		// argv[4] surface(A:0/B:1)

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			BYTE surface = (BYTE) strtoul(argv[4], NULL, 0);
			T_IM_DISP_GAMMA_TBL_IN gammaTable;
			gammaTable.r_data = (gushort*) ct_im_disp4_get_r_full_tbl(ctImDisp4);
			gammaTable.g_data = (gushort*) ct_im_disp4_get_g_full_tbl(ctImDisp4);
			gammaTable.b_data = (gushort*) ct_im_disp4_get_b_full_tbl(ctImDisp4);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			Ddim_Print(("IO_DISP.MAIN[%d].LCH.LTRG               = %08X\n",
					block, (guint32)IO_DISP.MAIN[block].LCH.LTRG.word)); /* pgr0539 */
			Ddim_Print(("IO_DISP.MAIN[%d].LCH.LTBLASET.bit.GMTSL = %08X\n",
					block, (guint32)IO_DISP.MAIN[block].LCH.LTBLASET.bit.GMTSL));
			Ddim_Print(("Surface = %02X\n", surface)); /* pgr0539 */
			ct_im_disp3_dump_main_gamma_table(disp3, block);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			if (argv[2][0] == '0')
			{
				error = Im_DISP_Set_Main_Gamma_Table(block, surface, NULL); /* pgr0539 */
			}
			else
			{
				error = Im_DISP_Set_Main_Gamma_Table(block, surface, &gammaTable); /* pgr0539 */
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_Main_Gamma_Table error=%08X\n",error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_dump_main_gamma_table(disp3, block);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "GetMainGamTbl") == 0)
	{
		//Im_DISP_Get_Gamma_Table -> Im_DISP_Get_Main_Gamma_Table

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "SetMainGamTbl"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)
		// argv[4] surface(A:0/B:1)

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			BYTE surface = (BYTE) strtoul(argv[4], NULL, 0);
			T_IM_DISP_GAMMA_TBL_IN gammaTable;
			gushort gammaRMatrix[32];
			gushort gammaGMatrix[32];
			gushort gammaBMatrix[32];
			memset(gammaRMatrix, 0, (sizeof(gushort) * 32));
			memset(gammaGMatrix, 0, (sizeof(gushort) * 32));
			memset(gammaBMatrix, 0, (sizeof(gushort) * 32));

			gammaTable.r_data = (gushort*) gammaRMatrix;
			gammaTable.g_data = (gushort*) gammaGMatrix;
			gammaTable.b_data = (gushort*) gammaBMatrix;

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Setting -------\n"));
			Ddim_Print(("IO_DISP.MAIN[%d].LCH.LTRG               = %08X\n",
					block, (guint32)IO_DISP.MAIN[block].LCH.LTRG.word)); /* pgr0539 */
			Ddim_Print(("IO_DISP.MAIN[%d].LCH.LTBLASET.bit.GMTSL = %08X\n",
					block, (guint32)IO_DISP.MAIN[block].LCH.LTBLASET.bit.GMTSL));
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Main_Gamma_Table(block, surface, NULL); /* pgr0539 */
			}
			else
			{
				error = Im_DISP_Get_Main_Gamma_Table(block, surface, &gammaTable); /* pgr0539 */
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Main_Gamma_Table error=%08X\n",error));
			}
			else
			{
				ct_im_disp3_dump_main_gamma_table(disp3, block);

				Ddim_Print(("Surface = %02X\n", surface));
				outputMainGamma(&gammaTable);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 3\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "SetDcoreGamTbl") == 0)
	{
		//Im_DISP_Set_Dcore_Gamma_Table

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "SetDcoreGamTbl"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)
		// argv[4] surface(A:0/B:1)

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			BYTE surface = (BYTE) strtoul(argv[4], NULL, 0);
			T_IM_DISP_GAMMA_TBL_OUT gammaTable;
			if (surface == 0)
			{
				gammaTable.r_data = (gushort*) ct_im_disp4_get_r_gamma_out_tbla(ctImDisp4);
				gammaTable.g_data = (gushort*) ct_im_disp4_get_g_gamma_out_tbla(ctImDisp4);
				gammaTable.b_data = (gushort*) ct_im_disp4_get_b_gamma_out_tbla(ctImDisp4);
			}
			else
			{
				gammaTable.r_data = (gushort*) ct_im_disp4_get_r_gamma_out_tblb(ctImDisp4);
				gammaTable.g_data = (gushort*) ct_im_disp4_get_g_gamma_out_tblb(ctImDisp4);
				gammaTable.b_data = (gushort*) ct_im_disp4_get_b_gamma_out_tblb(ctImDisp4);
			}

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TRG               = 0x%08X\n",
					block, IO_DISP.MAIN[block].DCORE.TRG.bit.TRG)); /* pgr0539 */
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TBLASET.bit.GMTSL = 0x%08X\n",
					block, IO_DISP.MAIN[block].DCORE.TBLASET.bit.GMTSL));
			Ddim_Print(("Surface = %02X\n", surface));
			ct_im_disp3_dump_dcore_gamma_table(disp3, block);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			if (argv[2][0] == '0')
			{
				error = Im_DISP_Set_Dcore_Gamma_Table(block, surface, NULL);
			}
			else
			{
				error = Im_DISP_Set_Dcore_Gamma_Table(block, surface, &gammaTable);
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_Dcore_Gamma_Table error=%08X\n",error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_dump_dcore_gamma_table(disp3, block);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "GetDcoreGamTbl") == 0)
	{
		//Im_DISP_Get_Dcore_Gamma_Table

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "SetMainGamTbl"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)
		// argv[4] surface(A:0/B:1)

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			BYTE surface = (BYTE) strtoul(argv[4], NULL, 0);
			T_IM_DISP_GAMMA_TBL_OUT gammaTable;
			gushort gammaRMatrix[33];
			gushort gammaGMatrix[33];
			gushort gammaBMatrix[33];
			memset(gammaRMatrix, 0, (sizeof(gushort) * 33));
			memset(gammaGMatrix, 0, (sizeof(gushort) * 33));
			memset(gammaBMatrix, 0, (sizeof(gushort) * 33));

			gammaTable.r_data = (gushort*) gammaRMatrix;
			gammaTable.g_data = (gushort*) gammaGMatrix;
			gammaTable.b_data = (gushort*) gammaBMatrix;

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Setting -------\n"));
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TRG               = 0x%08X\n",
					block, IO_DISP.MAIN[block].DCORE.TRG.bit.TRG)); /* pgr0539 */
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TBLASET.bit.GMTSL = 0x%08X\n",
					block, IO_DISP.MAIN[block].DCORE.TBLASET.bit.GMTSL));
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Dcore_Gamma_Table(block, surface, NULL); /* pgr0539 */
			}
			else
			{
				error = Im_DISP_Get_Dcore_Gamma_Table(block, surface, &gammaTable); /* pgr0539 */
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Dcore_Gamma_Table error=%08X\n",error));
			}
			else
			{
				ct_im_disp3a_dump_reg_dcore_gamma(disp3a, block);
				ct_im_disp3a_output_dcore_gamma(gammaTable);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "SetLumiTbl") == 0)
	{
		//Im_DISP_Set_Luminance_Table

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "SetLumiTbl"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)
		// argv[4] surface(A:0/B:1)

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			BYTE surface = (BYTE) strtoul(argv[4], NULL, 0);
			gushort setTable[33];
			memcpy(setTable, ct_im_disp4_get_luminance_tbla(ctImDisp4), sizeof(setTable));
			T_IM_DISP_CTRL_OUTPUT_TBL outputTbl;
			outputTbl.luminance_a = (gushort*) setTable;

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TRG.bit.TRG        = 0x%08X\n",
					block, IO_DISP.MAIN[block].DCORE.TRG.bit.TRG)); /* pgr0539 */
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TBLASET.bit.YSATSL = 0x%08X\n",
					block, IO_DISP.MAIN[block].DCORE.TBLASET.bit.YSATSL));

			Ddim_Print(("Surface = %02X\n", surface)); /* pgr0539 */
			ct_im_disp3_dump_lumi_gamma_table(disp3, block);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			if (argv[2][0] == '0')
			{
				error = Im_DISP_Set_Luminance_Table(block, surface, NULL);
			}
			else
			{
//					error = Im_DISP_Set_Luminance_Table(block, surface, setTable);
				error = Im_DISP_Set_Luminance_Table(block, surface, (gushort*) &outputTbl.luminance_a);
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_Luminance_Table error=%08X\n",error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_dump_lumi_gamma_table(disp3, block);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "GetLumiTbl") == 0)
	{
		//Im_DISP_Get_Luminance_Table

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "GetLumiTbl"
		// argv[2] Command select(0:Normal/1:tbl NULL)
		// argv[3] block(0/1)
		// argv[4] surface(A:0/B:1)

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			BYTE surface = (BYTE) strtoul(argv[4], NULL, 0);
			gushort getTable[33];
			memset(getTable, 0, sizeof(getTable));
			T_IM_DISP_CTRL_OUTPUT_TBL outputTbl;
			outputTbl.luminance_a = (gushort*) getTable;

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Setting -------\n"));
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TRG.bit.TRG        = 0x%08X\n",
					block, IO_DISP.MAIN[block].DCORE.TRG.bit.TRG)); /* pgr0539 */
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TBLASET.bit.YSATSL = 0x%08X\n",
					block, IO_DISP.MAIN[block].DCORE.TBLASET.bit.YSATSL));
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Luminance_Table(block, surface, NULL); /* pgr0539 */
			}
			else
			{
//					error = Im_DISP_Get_Luminance_Table(block, surface, getTable);	/* pgr0539 */
				error = Im_DISP_Get_Luminance_Table(block, surface,
						(gushort*) &outputTbl.luminance_a); /* pgr0539 */
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Luminance_Table error=%08X\n",error));
			}
			else
			{
				ct_im_disp3_dump_lumi_gamma_table(disp3, block);

				Ddim_Print(("Surface = %02X\n", surface));
				ct_im_disp3a_output_ushort_33_table(getTable);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 3\n"));
		}
	}

}
#endif /*CtImDisp_CO_DEBUG_DISP*/

/*
 * PUBLIC
 * */

CtImDisp2m *ct_im_disp2m_new(void)
{
	CtImDisp2m *self = (CtImDisp2m *) g_object_new(CT_TYPE_IM_DISP2M, NULL);
	return self;
}
