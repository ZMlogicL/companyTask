/*
 *ctimdisp2f.c
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
#include "ctimdisp2f.h"

/*
 * G_DEFINE_语句
 * */
G_DEFINE_TYPE (CtImDisp2f, ct_im_disp2f, IM_TYPE_DISP2_PARENT);

/*
 * 以下开始宏定义
 * */
#define CT_IM_DISP2F_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), CT_TYPE_IM_DISP2F, CtImDisp2fPrivate))

/*
 * 内部结构体或类型定义
 * */
struct _CtImDisp2fPrivate
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
static void disp2fDoMain_od(ImDisp2Parent *parent, gint32 argc, char **argv);
#endif /*CtImDisp_CO_DEBUG_DISP*/

/*
 * IMPL
 * */
static void ct_im_disp2f_class_init(CtImDisp2fClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtImDisp2fPrivate));
}

static void ct_im_disp2f_init(CtImDisp2f *self)
{
	//CtImDisp2fPrivate *priv = CT_IM_DISP2F_GET_PRIVATE(self);
#ifdef CtImDisp_CO_DEBUG_DISP
	ImDisp2Parent *parent = (ImDisp2Parent *)self;
	parent->doMainFunc = disp2fDoMain_od;
#endif /*CtImDisp_CO_DEBUG_DISP*/
}

static void dispose_od(GObject *object)
{
//	CtImDisp2f *self = CT_IM_DISP2F(object);
//	CtImDisp2fPrivate *priv = CT_IM_DISP2F_GET_PRIVATE(self);
	/*释放创建的对象1*/
//	if (priv->objectMine) {
//		g_object_unref(priv->objectMine);
//		priv->objectMine = NULL;
//	}
	G_OBJECT_CLASS (ct_im_disp2f_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
//	CtImDisp2f *self = CT_IM_DISP2F(object);
//	CtImDisp2fPrivate *priv = CT_IM_DISP2F_GET_PRIVATE(self);
	/*释放创建的内存2*/
//	if(self->name)
//	{
//		free(self->name);
//		self->name =NULL;
//	}
	G_OBJECT_CLASS (ct_im_disp2f_parent_class)->finalize(object);
}

#ifdef CtImDisp_CO_DEBUG_DISP
static void disp2fDoMain_od(ImDisp2Parent *parent, gint32 argc, char **argv)
{
	gint32 error = D_DDIM_OK;
	ImDisp2Group *imDisp2Group = (ImDisp2Group *)im_disp2_parent_get_group(parent);
	guchar *pImDispPclkCounter = im_disp2_group_get_pclk_counter(imDisp2Group);
	CtImDisp3 *disp3 = (CtImDisp3 *)im_disp2_group_get_disp3(imDisp2Group);

	if (strcmp((gchar *) argv[1], "SetWrng") == 0)
	{
		//Im_DISP_Set_Brightness_Warning -> Im_DISP_Set_Warning

		// argc=14
		// argv[0] "imdisp"
		// argv[1] "SetWrng"
		// argv[2] Command select(0:Normal/1:NULL)
		// argv[3] block(0/1)
		// argv[4] LYWCTL
		// argv[5] LYW0TH
		// argv[6] LYW1TH
		// argv[7] LYW0ST
		// argv[8] LYW0CA(DWORD)
		// argv[9] LYW0CB(DWORD)
		// argv[10] LYW1ST
		// argv[11] LYW1CA(DWORD)
		// argv[12] LYW1CB(DWORD)
		// argv[13] LBOST

		if (argc == 14)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);

			T_IM_DISP_WARNING warning;
			warning.lywctl.word = strtoul((gchar *) argv[4], NULL, 0);
			warning.lyw0th.word = strtoul((gchar *) argv[5], NULL, 0);
			warning.lyw1th.word = strtoul((gchar *) argv[6], NULL, 0);
			warning.lyw0st = (guint32) strtoul((gchar *) argv[7], NULL, 0);
			warning.lyw0ca.dword = (ULLONG) strtoull(argv[8], NULL, 0);
			warning.lyw0cb.dword = (ULLONG) strtoull(argv[9], NULL, 0);
			warning.lyw1st = (guint32) strtoul((gchar *) argv[10], NULL, 0);
			warning.lyw1ca.dword = (ULLONG) strtoull(argv[11], NULL, 0);
			warning.lyw1cb.dword = (ULLONG) strtoull(argv[12], NULL, 0);
			warning.lbost = (ULONG) strtoul((gchar *) argv[13], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_dump_reg_warning(disp3, block); /* pgr0539 */
			ct_im_disp3_print_param_warning(warning);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			switch (argv[2][0])
			{
			case '0':
				error = Im_DISP_Set_Warning(block, NULL);
				break;
			case '1':
				error = Im_DISP_Set_Warning(block, &warning);
				break;
			default:
				Ddim_Print(("Parameter command error.\n"));
				return;
				break;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_Warning error=%08X\n", error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_dump_reg_warning(disp3, block);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 14\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "GetWrng") == 0)
	{
		//Im_DISP_Get_Brightness_Warning -> Im_DISP_Get_Warning

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetWrng"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);

			T_IM_DISP_WARNING warning;
			memset(&warning, 0, sizeof(T_IM_DISP_WARNING));

			switch (argv[2][0])
			{
			case '0':
				error = Im_DISP_Get_Warning(block, NULL); /* pgr0539 */
				break;
			case '1':
				error = Im_DISP_Get_Warning(block, &warning); /* pgr0539 */
				break;
			default:
				Ddim_Print(("Parameter command error.\n"));
				return;
				break;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Warning error=%08X\n",error));
			}
			else
			{
				ct_im_disp3_dump_reg_warning(disp3, block);
				ct_im_disp3_print_param_warning(warning);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "SetBTim") == 0)
	{
		//Im_DISP_Set_Blink_Timer

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "SetBTim"
		// argv[2] block(0/1)
		// argv[3] lbltmr

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			U_IM_DISP_LBLTMR lbltmr;
			lbltmr.word = strtoul(argv[3], NULL, 0);
#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].LCH.LBLTMR = %08X\n",
					block, (guint32)IO_DISP.MAIN[block].LCH.LBLTMR.word)); /* pgr0539 */
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Im_DISP_Set_Blink_Timer(block, lbltmr);

			Ddim_Print(("------- After Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].LCH.LBLTMR = %08X\n",
					block, (guint32)IO_DISP.MAIN[block].LCH.LBLTMR.word));
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "GetBTim") == 0)
	{
		//Im_DISP_Get_Blink_Timer

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetBTim"
		// argv[2] Command select(0:Normal/1:NULL)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			U_IM_DISP_LBLTMR lbltmr;
			memset(&lbltmr, 0, sizeof(U_IM_DISP_LBLTMR));
			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Blink_Timer(block, NULL); /* pgr0539 */
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Get_Blink_Timer(block, &lbltmr); /* pgr0539 */
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Blink_Timer error = %08X\n",error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].LCH.LBLTMR = %08X\n",
						block, (guint32)IO_DISP.MAIN[block].LCH.LBLTMR.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("[U_IM_DISP_LBLTMR] \n"));
				Ddim_Print(("BTIMH = %08X, BTIML = %08X, BTIMD = %08X\n",
						lbltmr.bit.BTIMH,lbltmr.bit.BTIML,lbltmr.bit.BTIMD));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 2\n"));
		}
	}

	else if (strcmp((gchar *) argv[1], "SetZebra") == 0)
	{
		//Im_DISP_Set_Zebra

		// argc=7
		// argv[0] "imdisp"
		// argv[1] "SetZebra"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)
		// argv[4] LZBWID
		// argv[5] LZBV
		// argv[6] LZBPT

		if (argc == 7)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			T_IM_DISP_ZEBRA zebra;
			zebra.lzbwid.word = strtoul((gchar *) argv[4], NULL, 0);
			zebra.lzbv.word = strtoul((gchar *) argv[5], NULL, 0);
			zebra.lzbpt.word = strtoul((gchar *) argv[6], NULL, 0);
			ct_im_disp3_print_param_zebra(zebra);
#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_dump_reg_zebra(disp3, block); /* pgr0539 */
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			switch (argv[2][0])
			{
			case '0':
				error = Im_DISP_Set_Zebra(block, NULL);
				break;
			case '1':
				error = Im_DISP_Set_Zebra(block, &zebra);
				break;
			default:
				Ddim_Print(("Parameter command error.\n"));
				return;
				break;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_Zebra error=%08X\n", error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_dump_reg_zebra(disp3, block);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 7\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "GetZebra") == 0)
	{
		//Im_DISP_Get_Zebra

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetZebra"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);

			T_IM_DISP_ZEBRA zebra;
			memset(&zebra, 0, sizeof(T_IM_DISP_ZEBRA));

			switch (argv[2][0])
			{
			case '0':
				error = Im_DISP_Get_Zebra(block, NULL); /* pgr0539 */
				break;
			case '1':
				error = Im_DISP_Get_Zebra(block, &zebra); /* pgr0539 */
				break;
			default:
				Ddim_Print(("Parameter command error.\n"));
				return;
				break;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Zebra error=%08X\n",error));
			}
			else
			{
				ct_im_disp3_dump_reg_zebra(disp3, block);
				ct_im_disp3_print_param_zebra(zebra);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 2\n"));
		}
	}

	else if (strcmp((gchar *) argv[1], "SetMax") == 0)
	{
		//Im_DISP_Set_Matrix

		// argc=7
		// argv[0] "imdisp"
		// argv[1] "SetMax"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)
		// argv[4] matrix[0](DWORD)
		// argv[5] matrix[1](DWORD)
		// argv[6] matrix[2](DWORD)

		if (argc == 7)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			U_IM_DISP_YR_MATRIX_COEFFICIENT matrix[D_IM_DISP_MATRIX_SIZE];
			matrix[0].dword = (ULLONG) strtoull(argv[4], NULL, 0);
			matrix[1].dword = (ULLONG) strtoull(argv[5], NULL, 0);
			matrix[2].dword = (ULLONG) strtoull(argv[6], NULL, 0);

			ct_im_disp3_print_param_matrix(matrix);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_dump_reg_matrix(disp3, block); /* pgr0539 */
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			if (argv[2][0] == '0')
			{
				error = Im_DISP_Set_Matrix(block, NULL);
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Set_Matrix(block, matrix);
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}

			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_Matrix error=%08X\n",error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_dump_reg_matrix(disp3, block);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 7\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "GetMax") == 0)
	{
		//Im_DISP_Get_Matrix

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetMax"
		// argv[2] Command select(0:Normal/1:NULL)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			U_IM_DISP_YR_MATRIX_COEFFICIENT matrix[D_IM_DISP_MATRIX_SIZE];
			memset(matrix, 0, (sizeof(U_IM_DISP_YR_MATRIX_COEFFICIENT) * D_IM_DISP_MATRIX_SIZE));

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Matrix(block, NULL); /* pgr0539 */
			}
			if (argv[2][0] == '1')
			{
				error = Im_DISP_Get_Matrix(block, matrix); /* pgr0539 */
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}

			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Matrix error=%08X\n", error));
			}
			else
			{
				ct_im_disp3_dump_reg_matrix(disp3, block);
				ct_im_disp3_print_param_matrix(matrix);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 3\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "SetGamMod") == 0)
	{
		//Im_DISP_Set_Gamma_Mode

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "SetGamMod"
		// argv[2] block(0/1)
		// argv[3] GMMD

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			U_IM_DISP_LGMMD gmmd;
			gmmd.word = (ULONG) strtoul(argv[3], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			Ddim_Print(("IO_DISP.MAIN[%d].LCH.LGMMD.word = 0x%08X\n",
					block, (guint32)IO_DISP.MAIN[block].LCH.LGMMD.word)); /* pgr0539 */
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Im_DISP_Set_Gamma_Mode(block, gmmd);
			Ddim_Print(("------- After Setting -------\n"));
			Ddim_Print(("IO_DISP.MAIN[%d].LCH.LGMMD.word = 0x%08X\n",
					block, (guint32)IO_DISP.MAIN[block].LCH.LGMMD.word));
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "GetGamMod") == 0)
	{
		//Im_DISP_Get_Gamma_Mode

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetGamMod"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			U_IM_DISP_LGMMD gmmd;
			memset(&gmmd, 0, sizeof(U_IM_DISP_LGMMD));

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Gamma_Mode(block, NULL); /* pgr0539 */
			}
			if (argv[2][0] == '1')
			{
				error = Im_DISP_Get_Gamma_Mode(block, &gmmd); /* pgr0539 */
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}

			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Gamma_Mode error=%08X\n", error));
			}
			else
			{
				Ddim_Print(("IO_DISP.MAIN[%d].LCH.LGMMD.word = 0x%08X\n",
						block, (guint32)IO_DISP.MAIN[block].LCH.LGMMD.word));

				Ddim_Print(("[U_IM_DISP_LGMMD]\n"));
				Ddim_Print(("  %08X\n", (guint32)gmmd.word));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "SetGamEn") == 0)
	{
		//Im_DISP_Set_Gamma_Enable

		// argc=8
		// argv[0] "imdisp"
		// argv[1] "SetGamEn"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)
		// argv[4] correct_kind(1,2,4,8,0x10)
		// argv[5] access(0/1)
		// argv[6] proc(0/1)
		// argv[7] surface(0/1)

		if (argc == 8)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			E_IM_DISP_CORRECT_SELECT correct_kind = (E_IM_DISP_CORRECT_SELECT) strtoul(argv[4], NULL, 0);
			T_IM_DISP_TBL_ACCESS_SET correct;
			correct.access = (E_IM_DISP_TABLE_ACCESS) strtoul(argv[5], NULL, 0);
			correct.proc = (E_IM_DISP_CORRECT_PROC) strtoul(argv[6], NULL, 0);
			correct.surface = (BYTE) strtoul(argv[7], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].LCH.LTRG      = %08X\n",
					block, (guint32)IO_DISP.MAIN[block].LCH.LTRG.word)); /* pgr0539 */
			Ddim_Print(("IO_DISP.MAIN[%d].LCH.LTBLASET  = %08X\n",
					block, (guint32)IO_DISP.MAIN[block].LCH.LTBLASET.word));
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TRG.    = %08X\n",
					block, (guint32)IO_DISP.MAIN[block].DCORE.TRG.word));
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TBLASET = %08X\n",
					block, (guint32)IO_DISP.MAIN[block].DCORE.TBLASET.word));
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			if (argv[2][0] == '0')
			{
				error = Im_DISP_Set_Gamma_Enable(block, correct_kind, NULL); /* pgr0539 */
			}
			else
			{
				error = Im_DISP_Set_Gamma_Enable(block, correct_kind, &correct); /* pgr0539 */
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_Gamma_Enable error=%08X\n", error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].LCH.LTRG      = %08X\n",
						block, (guint32)IO_DISP.MAIN[block].LCH.LTRG.word));
				Ddim_Print(("IO_DISP.MAIN[%d].LCH.LTBLASET  = %08X\n",
						block, (guint32)IO_DISP.MAIN[block].LCH.LTBLASET.word));
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TRG.    = %08X\n",
						block, (guint32)IO_DISP.MAIN[block].DCORE.TRG.word));
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TBLASET = %08X\n",
						block, (guint32)IO_DISP.MAIN[block].DCORE.TBLASET.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "GetGamEn") == 0)
	{
		//Im_DISP_Get_Gamma_Enable

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetGamMod"
		// argv[2] Command select(0:Normal/1:NULL)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			U_IM_DISP_LTBLASET lchLtblaset;
			lchLtblaset.word = 0;
			U_IM_DISP_TBLASET dcoreTblaset;
			dcoreTblaset.word = 0;
			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Gamma_Enable(block, NULL, NULL); /* pgr0539 */
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Get_Gamma_Enable(block, NULL, &dcoreTblaset); /* pgr0539 */
			}
			else if (argv[2][0] == '2')
			{
				error = Im_DISP_Get_Gamma_Enable(block, &lchLtblaset, NULL); /* pgr0539 */
			}
			else
			{
				error = Im_DISP_Get_Gamma_Enable(block, &lchLtblaset, &dcoreTblaset); /* pgr0539 */
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Gamma_Enable error=%08X\n",error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].LCH.LTBLASET  = %08X\n",
						block, (guint32)IO_DISP.MAIN[block].LCH.LTBLASET.word));
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TBLASET = %08X\n",
						block, (guint32)IO_DISP.MAIN[block].DCORE.TBLASET.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("[U_IM_DISP_TBLASET]\n"));
				Ddim_Print(("ltblaset      = %08X\n", (guint32)lchLtblaset.word));
				Ddim_Print(("dcoreTblaset = %08X\n", (guint32)dcoreTblaset.word));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "SetAlpVal") == 0)
	{
		//Im_DISP_Set_Alpha_Value

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "SetAlpVal"
		// argv[2] block(0/1)
		// argv[3] lalp

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			U_IM_DISP_LALP lalp;
			lalp.word = (ULONG) strtoul(argv[3], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].LCH.LALP = %08X\n",
					block, (guint32)IO_DISP.MAIN[block].LCH.LALP.word)); /* pgr0539 */
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Im_DISP_Set_Alpha_Value(block, lalp);
			Ddim_Print(("------- After Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].LCH.LALP = %08X\n",
					block, (guint32)IO_DISP.MAIN[block].LCH.LALP.word));
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "GetAlpVal") == 0)
	{
		//Im_DISP_Get_Alpha_Value

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetGamMod"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			U_IM_DISP_LALP lalp;
			memset(&lalp, 0, sizeof(U_IM_DISP_LALP));
			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Alpha_Value(block, NULL); /* pgr0539 */
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Get_Alpha_Value(block, &lalp); /* pgr0539 */
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Alpha_Value error=%08X\n", error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].LCH.LALP = %08X\n",
						block, (guint32)IO_DISP.MAIN[block].LCH.LALP.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("[U_IM_DISP_LALP]\n"));
				Ddim_Print(("  %08X\n", (guint32)lalp.word));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "SetPos") == 0)
	{
		//Im_DISP_Set_Display_Position

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "SetPos"
		// argv[2] block(0/1)
		// argv[3] position

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			U_IM_DISP_DSTA position;
			position.word = strtoul(argv[3], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].LCH.LDSTA = %08X\n",
					block, (guint32)IO_DISP.MAIN[block].LCH.LDSTA.word)); /* pgr0539 */
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Set_Display_Position(block, position);
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_Display_Position error=%08X\n", error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].LCH.LDSTA = %08X\n",
						block, (guint32)IO_DISP.MAIN[block].LCH.LDSTA.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "GetPos") == 0)
	{
		//Im_DISP_Get_Display_Position

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetPos"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			U_IM_DISP_DSTA position;
			memset(&position, 0, sizeof(U_IM_DISP_DSTA));
			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Display_Position(block, NULL); /* pgr0539 */
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Get_Display_Position(block, &position); /* pgr0539 */
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Display_Position error=%08X\n",error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].LCH.LDSTA = %08X\n",
						block, (guint32)IO_DISP.MAIN[block].LCH.LDSTA.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("[U_IM_DISP_DSTA]\n"));
				Ddim_Print(("DSH = %08X, DSV = %08X\n",position.bit.DSH, position.bit.DSV));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
}
#endif /*CtImDisp_CO_DEBUG_DISP*/

/*
 * PUBLIC
 * */

CtImDisp2f *ct_im_disp2f_new(void)
{
	CtImDisp2f *self = (CtImDisp2f *) g_object_new(CT_TYPE_IM_DISP2F, NULL);
	return self;
}
