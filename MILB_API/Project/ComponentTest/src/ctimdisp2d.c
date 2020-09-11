/*
 *ctimdisp2d.c
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-04
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

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
#include "ctimdisp2d.h"

K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(CtImDisp2d, ct_im_disp2d, IM_TYPE_DISP2_PARENT)
#define CT_IM_DISP2D_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), CtImDisp2dPrivate, CT_TYPE_IM_DISP2D))

struct _CtImDisp2dPrivate
{
	kpointer qwertyu;
};

/*
 * DECLS
 * */
static void outputDispAntiGamma(CtImDisp3a *disp3a,
		volatile struct io_jdslch_igtbl_rgb* igtblA, volatile struct io_jdslch_igtbl_rgb* igtblB,
		volatile struct io_jdslch_gtbl_rgb* gtblA, volatile struct io_jdslch_gtbl_rgb* gtblB);
static void printDispAntiGamma(CtImDisp3a *disp3a,
		T_IM_DISP_ANTI_GAMMA_TBL* antiA, T_IM_DISP_ANTI_GAMMA_TBL* antiB,
		T_IM_DISP_GAMMA_TBL_IN* gammaA, T_IM_DISP_GAMMA_TBL_IN* gammaB);
#ifdef CtImDisp_CO_DEBUG_DISP
static void disp2dDoMain_od(ImDisp2Parent *parent, kint32 argc, char **argv);
#endif /*CtImDisp_CO_DEBUG_DISP*/

/*
 * IMPL
 * */
static void ct_im_disp2d_constructor(CtImDisp2d *self)
{
	CtImDisp2dPrivate *priv = CT_IM_DISP2D_GET_PRIVATE(self);
#ifdef CtImDisp_CO_DEBUG_DISP
	ImDisp2Parent *parent = (ImDisp2Parent *)self;
	parent->doMainFunc = disp2dDoMain_od;
#endif /*CtImDisp_CO_DEBUG_DISP*/
	self->ctImDisp2dPrivate = priv;
}

static void ct_im_disp2d_destructor(CtImDisp2d *self)
{
}

//Output IO_DISP_TBL's table data
static void outputDispAntiGamma(CtImDisp3a *disp3a,
		volatile struct io_jdslch_igtbl_rgb* igtblA, volatile struct io_jdslch_igtbl_rgb* igtblB,
		volatile struct io_jdslch_gtbl_rgb* gtblA, volatile struct io_jdslch_gtbl_rgb* gtblB)
{
	Ddim_Print(("--- r_anti_a ---\n"));
	ct_im_disp3a_output_ushort_32_table(igtblA->IGTBLR.hword);
	Ddim_Print(("--- g_anti_a ---\n"));
	ct_im_disp3a_output_ushort_32_table(igtblA->IGTBLG.hword);
	Ddim_Print(("--- b_anti_a ---\n"));
	ct_im_disp3a_output_ushort_32_table(igtblA->IGTBLB.hword);

	Ddim_Print(("--- r_anti_b ---\n"));
	ct_im_disp3a_output_ushort_32_table(igtblB->IGTBLR.hword);
	Ddim_Print(("--- g_anti_b ---\n"));
	ct_im_disp3a_output_ushort_32_table(igtblB->IGTBLG.hword);
	Ddim_Print(("--- b_anti_b ---\n"));
	ct_im_disp3a_output_ushort_32_table(igtblB->IGTBLB.hword);

	Ddim_Print(("--- r_gamma_a ---\n"));
	ct_im_disp3a_output_ushort_32_table(gtblA->GTBLR.hword);
	Ddim_Print(("--- g_gamma_a ---\n"));
	ct_im_disp3a_output_ushort_32_table(gtblA->GTBLG.hword);
	Ddim_Print(("--- b_gamma_a ---\n"));
	ct_im_disp3a_output_ushort_32_table(gtblA->GTBLB.hword);

	Ddim_Print(("--- r_gamma_b ---\n"));
	ct_im_disp3a_output_ushort_32_table(gtblB->GTBLR.hword);
	Ddim_Print(("--- g_gamma_b ---\n"));
	ct_im_disp3a_output_ushort_32_table(gtblB->GTBLG.hword);
	Ddim_Print(("--- b_gamma_b ---\n"));
	ct_im_disp3a_output_ushort_32_table(gtblB->GTBLB.hword);
}

//Output IO_DISP_TBL's table data
static void printDispAntiGamma(CtImDisp3a *disp3a,
		T_IM_DISP_ANTI_GAMMA_TBL* antiA, T_IM_DISP_ANTI_GAMMA_TBL* antiB,
		T_IM_DISP_GAMMA_TBL_IN* gammaA, T_IM_DISP_GAMMA_TBL_IN* gammaB)
{
	Ddim_Print(("[output gamma table]\n"));
	Ddim_Print(("--- r_anti_a ---\n"));
	ct_im_disp3a_output_ushort_32_table(antiA->r_anti);
	Ddim_Print(("--- g_anti_a ---\n"));
	ct_im_disp3a_output_ushort_32_table(antiA->g_anti);
	Ddim_Print(("--- b_anti_a ---\n"));
	ct_im_disp3a_output_ushort_32_table(antiA->r_anti);

	Ddim_Print(("--- r_anti_b ---\n"));
	ct_im_disp3a_output_ushort_32_table(antiB->r_anti);
	Ddim_Print(("--- g_anti_b ---\n"));
	ct_im_disp3a_output_ushort_32_table(antiB->g_anti);
	Ddim_Print(("--- b_anti_b ---\n"));
	ct_im_disp3a_output_ushort_32_table(antiB->b_anti);

	Ddim_Print(("--- r_gamma_a ---\n"));
	ct_im_disp3a_output_ushort_32_table(gammaA->r_data);
	Ddim_Print(("--- g_gamma_a ---\n"));
	ct_im_disp3a_output_ushort_32_table(gammaA->g_data);
	Ddim_Print(("--- b_gamma_a ---\n"));
	ct_im_disp3a_output_ushort_32_table(gammaA->b_data);

	Ddim_Print(("--- r_gamma_b ---\n"));
	ct_im_disp3a_output_ushort_32_table(gammaB->r_data);
	Ddim_Print(("--- g_gamma_b ---\n"));
	ct_im_disp3a_output_ushort_32_table(gammaB->g_data);
	Ddim_Print(("--- b_gamma_b ---\n"));
	ct_im_disp3a_output_ushort_32_table(gammaB->b_data);
}

#ifdef CtImDisp_CO_DEBUG_DISP
static void disp2dDoMain_od(ImDisp2Parent *parent, kint32 argc, char **argv)
{//callback?
//	CtImDisp2d *self = (CtImDisp2d *)parent;
	ImDisp2Group *disp2Group = (ImDisp2Group *)im_disp2_parent_get_group(parent);
	ImDisp2Group *imDisp2Group = (ImDisp2Group *)im_disp2_parent_get_group(parent);
	kuchar *pImDispHclkCounter = im_disp2_group_get_hclk_counter(imDisp2Group);
	CtImDisp3 *disp3 = (CtImDisp3 *)im_disp2_group_get_disp3(imDisp2Group);
	CtImDisp3a *disp3a = (CtImDisp3a *)im_disp2_group_get_disp3a(imDisp2Group);

	kint32 error = D_DDIM_OK;
	kuint32 layer = 0;
	kuint32 layer1 = 0;

	if (strcmp((kchar*) argv[1], "Ctrl_Main_TBLs") == 0)
	{
		//Im_DISP_Ctrl_Tbl -> Im_DISP_Ctrl_Main_Tbl

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "Ctrl_Main_TBLs"
		// argv[2] Command select(0:Normal, 1:ctrlTbl NULL)
		// argv[3] block
		// argv[4] table (0/1/2/3/4/5/6/7/8/9/10/11/12)

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			kuint32 table_set = (kuint32) strtoul(argv[4], NULL, 0);
			//临时变量 ctrlTbl，可能会被修改，需要一个初始值
			T_IM_DISP_CTRL_MAIN_TBL *pCtrlTbl = im_disp2_group_get_main_tbl(disp2Group); /* pgr0539 */
			T_IM_DISP_CTRL_MAIN_TBL ctrlTbl;			//不用指针
			memcpy(&ctrlTbl, pCtrlTbl + block, sizeof(ctrlTbl));

			switch (table_set)
			{
			case 1:
				ctrlTbl.anti_a.r_anti = NULL;
				break;
			case 2:
				ctrlTbl.anti_a.g_anti = NULL;
				break;
			case 3:
				ctrlTbl.anti_a.b_anti = NULL;
				break;
			case 4:
				ctrlTbl.anti_b.r_anti = NULL;
				break;
			case 5:
				ctrlTbl.anti_b.g_anti = NULL;
				break;
			case 6:
				ctrlTbl.anti_b.b_anti = NULL;
				break;
			case 7:
				ctrlTbl.gamma_a.r_data = NULL;
				break;
			case 8:
				ctrlTbl.gamma_a.g_data = NULL;
				break;
			case 9:
				ctrlTbl.gamma_a.b_data = NULL;
				break;
			case 10:
				ctrlTbl.gamma_b.r_data = NULL;
				break;
			case 11:
				ctrlTbl.gamma_b.g_data = NULL;
				break;
			case 12:
				ctrlTbl.gamma_b.b_data = NULL;
				break;
			default:
				//
				break;
			}

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
			outputDispAntiGamma(disp3a, &IO_DISP_TBL.MAIN[block].LCH.IGTBLA,
					&IO_DISP_TBL.MAIN[block].LCH.IGTBLB, &IO_DISP_TBL.MAIN[block].LCH.GTBLA,
					&IO_DISP_TBL.MAIN[block].LCH.GTBLB);
			ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING

			if (strcmp(argv[2], "0") == 0)
			{
				error = Im_DISP_Ctrl_Main_Tbl(block, NULL);
			}
			else
			{
				error = Im_DISP_Ctrl_Main_Tbl(block, &ctrlTbl);
			}

			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Ctrl_Main_Tbl error=%08X\n",error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
				outputDispAntiGamma(disp3a, &IO_DISP_TBL.MAIN[block].LCH.IGTBLA,
						&IO_DISP_TBL.MAIN[block].LCH.IGTBLB, &IO_DISP_TBL.MAIN[block].LCH.GTBLA,
						&IO_DISP_TBL.MAIN[block].LCH.GTBLB);
				ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 3\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "Get_Main_TBLs") == 0)
	{
		//Im_DISP_Get_Ctrl_Tbl -> Im_DISP_Get_Ctrl_Main_Tbl

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "Get_Main_TBLs"
		// argv[2] Command select(0:Normal, 1:ctrlTbl NULL)
		// argv[3] block
		// argv[4] table (0/1/2/3/4/5/6/7/8/9/10/11/12)

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			T_IM_DISP_CTRL_MAIN_TBL ctrlTbl;			//不用指针
			T_IM_DISP_CTRL_MAIN_TBL *pCtrlTbl = im_disp2_group_get_main_tbl(disp2Group); /* pgr0539 */
			memcpy(&ctrlTbl, pCtrlTbl + block, sizeof(ctrlTbl));

			if (strcmp((kchar*) argv[4], "1") == 0)
			{
				ctrlTbl.anti_a.r_anti = NULL;
			}
			else if (strcmp((kchar*) argv[4], "2") == 0)
			{
				ctrlTbl.anti_a.g_anti = NULL;
			}
			else if (strcmp((kchar*) argv[4], "3") == 0)
			{
				ctrlTbl.anti_a.b_anti = NULL;
			}
			else if (strcmp((kchar*) argv[4], "4") == 0)
			{
				ctrlTbl.anti_b.r_anti = NULL;
			}
			else if (strcmp((kchar*) argv[4], "5") == 0)
			{
				ctrlTbl.anti_b.g_anti = NULL;
			}
			else if (strcmp((kchar*) argv[4], "6") == 0)
			{
				ctrlTbl.anti_b.b_anti = NULL;
			}
			else if (strcmp((kchar*) argv[4], "7") == 0)
			{
				ctrlTbl.gamma_a.r_data = NULL;
			}
			else if (strcmp((kchar*) argv[4], "8") == 0)
			{
				ctrlTbl.gamma_a.g_data = NULL;
			}
			else if (strcmp((kchar*) argv[4], "9") == 0)
			{
				ctrlTbl.gamma_a.b_data = NULL;
			}
			else if (strcmp((kchar*) argv[4], "10") == 0)
			{
				ctrlTbl.gamma_b.r_data = NULL;
			}
			else if (strcmp((kchar*) argv[4], "11") == 0)
			{
				ctrlTbl.gamma_b.g_data = NULL;
			}
			else if (strcmp((kchar*) argv[4], "12") == 0)
			{
				ctrlTbl.gamma_b.b_data = NULL;
			}

			Ddim_Print(("------- Setting -------\n"));
			ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
			outputDispAntiGamma(disp3a, &IO_DISP_TBL.MAIN[block].LCH.IGTBLA,
					&IO_DISP_TBL.MAIN[block].LCH.IGTBLB, &IO_DISP_TBL.MAIN[block].LCH.GTBLA,
					&IO_DISP_TBL.MAIN[block].LCH.GTBLB);
			ct_im_disp3_hclk_counter_off(pImDispHclkCounter);

			if (strcmp((kchar*) argv[2], "0") == 0)
			{
				error = Im_DISP_Get_Ctrl_Main_Tbl(block, NULL);
			}
			else
			{
				error = Im_DISP_Get_Ctrl_Main_Tbl(block, &ctrlTbl);
			}

			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Ctrl_Main_Tbl error=%08X\n",error));
			}
			else
			{
				ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
				printDispAntiGamma(disp3a, &ctrlTbl.anti_a, &ctrlTbl.anti_b, &ctrlTbl.gamma_a, &ctrlTbl.gamma_b);
				ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 3\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "Ctrl_Output_TBLs") == 0)
	{
		// Im_DISP_Ctrl_Output_Tbl

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "Ctrl_Output_TBLs"
		// argv[2] Command select(0:NULL, 1:Normal)
		// argv[3] block
		// argv[4] table (0/1/2/3/4/5/6/7/8/9/10)

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			T_IM_DISP_CTRL_OUTPUT_TBL *pctrlTbl = im_disp2_group_get_output_tbl(disp2Group); /* pgr0539 */
			T_IM_DISP_CTRL_OUTPUT_TBL ctrlTbl;
			memcpy(&ctrlTbl, pctrlTbl + block, sizeof(ctrlTbl));

			if (strcmp((kchar*) argv[4], "1") == 0)
			{
				ctrlTbl.gamma_a.r_data = NULL;
			}
			else if (strcmp((kchar*) argv[4], "2") == 0)
			{
				ctrlTbl.gamma_a.g_data = NULL;
			}
			else if (strcmp((kchar*) argv[4], "3") == 0)
			{
				ctrlTbl.gamma_a.b_data = NULL;
			}
			else if (strcmp((kchar*) argv[4], "4") == 0)
			{
				ctrlTbl.gamma_b.r_data = NULL;
			}
			else if (strcmp((kchar*) argv[4], "5") == 0)
			{
				ctrlTbl.gamma_b.g_data = NULL;
			}
			else if (strcmp((kchar*) argv[4], "6") == 0)
			{
				ctrlTbl.gamma_b.b_data = NULL;
			}
			else if (strcmp((kchar*) argv[4], "7") == 0)
			{
				ctrlTbl.luminance_a = NULL;
			}
			else if (strcmp((kchar*) argv[4], "8") == 0)
			{
				ctrlTbl.chroma_a = NULL;
			}
			else if (strcmp((kchar*) argv[4], "9") == 0)
			{
				ctrlTbl.luminance_b = NULL;
			}
			else if (strcmp((kchar*) argv[4], "10") == 0)
			{
				ctrlTbl.chroma_b = NULL;
			}

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
			Ddim_Print(("IO_DISP.MAIN[0].DCORE.TRG.bit.TRG = %d\n\n",
					IO_DISP.MAIN[0].DCORE.TRG.bit.TRG));
			Ddim_Print(("IO_DISP.MAIN[0].DCORE.TBLASET.bit.GMTAEN = %d\n\n",
					IO_DISP.MAIN[0].DCORE.TBLASET.bit.GMTAEN));
			Ddim_Print(("IO_DISP.MAIN[0].DCORE.TBLASET.bit.GMTSL  = %d\n\n",
					IO_DISP.MAIN[0].DCORE.TBLASET.bit.GMTSL));
			Ddim_Print(("IO_DISP.MAIN[0].DCORE.TBLASET.bit.YSATTA = %d\n\n",
					IO_DISP.MAIN[0].DCORE.TBLASET.bit.YSATTA));
			Ddim_Print(("IO_DISP.MAIN[0].DCORE.TBLASET.bit.YSATSL = %d\n\n",
					IO_DISP.MAIN[0].DCORE.TBLASET.bit.YSATSL));
			Ddim_Print(("IO_DISP.MAIN[1].DCORE.TRG.bit.TRG = %d\n\n",
					IO_DISP.MAIN[1].DCORE.TRG.bit.TRG));
			Ddim_Print(("IO_DISP.MAIN[1].DCORE.TBLASET.bit.GMTAEN = %d\n\n",
					IO_DISP.MAIN[1].DCORE.TBLASET.bit.GMTAEN));
			Ddim_Print(("IO_DISP.MAIN[1].DCORE.TBLASET.bit.GMTSL  = %d\n\n",
					IO_DISP.MAIN[1].DCORE.TBLASET.bit.GMTSL));
			Ddim_Print(("IO_DISP.MAIN[1].DCORE.TBLASET.bit.YSATTA = %d\n\n",
					IO_DISP.MAIN[1].DCORE.TBLASET.bit.YSATTA));
			Ddim_Print(("IO_DISP.MAIN[1].DCORE.TBLASET.bit.YSATSL = %d\n\n",
					IO_DISP.MAIN[1].DCORE.TBLASET.bit.YSATSL));
			ct_im_disp3_hclk_counter_off(pImDispHclkCounter);

			ct_im_disp3_dump_dcore_gamma_table(disp3, block);
			ct_im_disp3_dump_lumi_gamma_table(disp3, block);
			ct_im_disp3_dump_gain_table(disp3, block);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING

			if (strcmp(argv[2], "0") == 0)
			{
				error = Im_DISP_Ctrl_Output_Tbl(block, NULL);
			}
			else
			{
				error = Im_DISP_Ctrl_Output_Tbl(block, &ctrlTbl);
			}

			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Ctrl_Output_Tbl error=%08X\n",error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3a_print_ctrl_output_tbl(ctrlTbl);
				ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
				ct_im_disp3_dump_dcore_gamma_table(disp3, block);
				ct_im_disp3_dump_lumi_gamma_table(disp3, block);
				ct_im_disp3_dump_gain_table(disp3, block);
				ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "Get_Output_TBLs") == 0)
	{
		//Im_DISP_Get_Tbl -> Im_DISP_Get_Ctrl_Output_Tbl

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "Get_Output_TBLs"
		// argv[2] Command select(0:Normal, 1:ctrlTbl NULL)
		// argv[3] block
		// argv[4] table (0/1/2/3/4/5/6/7/8/9/10/11/12)

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			T_IM_DISP_CTRL_OUTPUT_TBL ctrlTbl;
			kushort tbl[33 * 10];
			memset(tbl, 0, sizeof(tbl));
			ctrlTbl.gamma_a.r_data = &tbl[0];
			ctrlTbl.gamma_a.g_data = &tbl[33];
			ctrlTbl.gamma_a.b_data = &tbl[66];
			ctrlTbl.gamma_b.r_data = &tbl[99];
			ctrlTbl.gamma_b.g_data = &tbl[132];
			ctrlTbl.gamma_b.b_data = &tbl[165];
			ctrlTbl.luminance_a = &tbl[198];
			ctrlTbl.chroma_a = &tbl[231];
			ctrlTbl.luminance_b = &tbl[264];
			ctrlTbl.chroma_b = &tbl[297];

			if (strcmp((kchar*) argv[4], "1") == 0)
			{
				ctrlTbl.gamma_a.r_data = NULL;
			}
			else if (strcmp((kchar*) argv[4], "2") == 0)
			{
				ctrlTbl.gamma_a.g_data = NULL;
			}
			else if (strcmp((kchar*) argv[4], "3") == 0)
			{
				ctrlTbl.gamma_a.b_data = NULL;
			}
			else if (strcmp((kchar*) argv[4], "4") == 0)
			{
				ctrlTbl.gamma_b.r_data = NULL;
			}
			else if (strcmp((kchar*) argv[4], "5") == 0)
			{
				ctrlTbl.gamma_b.g_data = NULL;
			}
			else if (strcmp((kchar*) argv[4], "6") == 0)
			{
				ctrlTbl.gamma_b.b_data = NULL;
			}
			else if (strcmp((kchar*) argv[4], "7") == 0)
			{
				ctrlTbl.luminance_a = NULL;
			}
			else if (strcmp((kchar*) argv[4], "8") == 0)
			{
				ctrlTbl.chroma_a = NULL;
			}
			else if (strcmp((kchar*) argv[4], "9") == 0)
			{
				ctrlTbl.luminance_b = NULL;
			}
			else if (strcmp((kchar*) argv[4], "10") == 0)
			{
				ctrlTbl.chroma_b = NULL;
			}

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
			Ddim_Print(("IO_DISP.MAIN[0].DCORE.TRG.bit.TRG = %d\n\n",
					IO_DISP.MAIN[0].DCORE.TRG.bit.TRG));
			Ddim_Print(("IO_DISP.MAIN[0].DCORE.TBLASET.bit.GMTAEN = %d\n\n",
					IO_DISP.MAIN[0].DCORE.TBLASET.bit.GMTAEN));
			Ddim_Print(("IO_DISP.MAIN[0].DCORE.TBLASET.bit.GMTSL  = %d\n\n",
					IO_DISP.MAIN[0].DCORE.TBLASET.bit.GMTSL));
			Ddim_Print(("IO_DISP.MAIN[0].DCORE.TBLASET.bit.YSATTA = %d\n\n",
					IO_DISP.MAIN[0].DCORE.TBLASET.bit.YSATTA));
			Ddim_Print(("IO_DISP.MAIN[0].DCORE.TBLASET.bit.YSATSL = %d\n\n",
					IO_DISP.MAIN[0].DCORE.TBLASET.bit.YSATSL));
			Ddim_Print(("IO_DISP.MAIN[1].DCORE.TRG.bit.TRG = %d\n\n",
					IO_DISP.MAIN[1].DCORE.TRG.bit.TRG));
			Ddim_Print(("IO_DISP.MAIN[1].DCORE.TBLASET.bit.GMTAEN = %d\n\n",
					IO_DISP.MAIN[1].DCORE.TBLASET.bit.GMTAEN));
			Ddim_Print(("IO_DISP.MAIN[1].DCORE.TBLASET.bit.GMTSL  = %d\n\n",
					IO_DISP.MAIN[1].DCORE.TBLASET.bit.GMTSL));
			Ddim_Print(("IO_DISP.MAIN[1].DCORE.TBLASET.bit.YSATTA = %d\n\n",
					IO_DISP.MAIN[1].DCORE.TBLASET.bit.YSATTA));
			Ddim_Print(("IO_DISP.MAIN[1].DCORE.TBLASET.bit.YSATSL = %d\n\n",
					IO_DISP.MAIN[1].DCORE.TBLASET.bit.YSATSL));
			ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING

			if (strcmp((kchar*) argv[2], "0") == 0)
			{
				error = Im_DISP_Get_Ctrl_Output_Tbl(block, NULL); /* pgr0539 */
			}
			else
			{
				error = Im_DISP_Get_Ctrl_Output_Tbl(block, &ctrlTbl); /* pgr0539 */
			}

			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Ctrl_Output_Tbl error=%08X\n",error));
			}
			else
			{
				Ddim_Print(("------- Setting -------\n"));
				ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
				ct_im_disp3_dump_dcore_gamma_table(disp3, block);
				ct_im_disp3_dump_lumi_gamma_table(disp3, block);
				ct_im_disp3_dump_gain_table(disp3, block);
				ct_im_disp3_hclk_counter_off(pImDispHclkCounter);

				ct_im_disp3a_print_ctrl_output_tbl(ctrlTbl);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 3\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "start") == 0)
	{
		//Im_DISP_Start

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "start"
		// argv[2] HDMI layer
		// argv[3] LCD/MIPI layer
		// argv[4] channnel(1/2)

		if (argc == 5)
		{

			// Set layer for HDMI
			layer = strtoul(argv[2], NULL, 0);

			// Set layer for LCD/mipi
			layer1 = strtoul(argv[3], NULL, 0);

			// Set write channel
			BYTE writeChannel;
			writeChannel = strtoul(argv[4], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3a_dump_reg_trg(disp3a);
			Ddim_Print(("IO_CHIPTOP.CLKSTOP3.bit.LCDCK = %d\n", IO_CHIPTOP.CLKSTOP3.bit.LCDCK));
			Ddim_Print(("IO_CHIPTOP.CLKSTOP3.bit.HIFCK = %d\n", IO_CHIPTOP.CLKSTOP3.bit.HIFCK));
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Start(layer, layer1, writeChannel); /* pgr0539 */
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Start error=%08X\n",error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3a_dump_reg_trg(disp3a);
				Ddim_Print(("IO_CHIPTOP.CLKSTOP3.bit.LCDCK = %d\n", IO_CHIPTOP.CLKSTOP3.bit.LCDCK));
				Ddim_Print(("IO_CHIPTOP.CLKSTOP3.bit.HIFCK = %d\n", IO_CHIPTOP.CLKSTOP3.bit.HIFCK));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 2\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "stop") == 0)
	{
		//Im_DISP_Stop

		// argc=6
		// argv[0] "imdisp"
		// argv[1] "stop"
		// argv[2] HDMI layer
		// argv[3] LCD/MIPI layer
		// argv[4] channnel(1/2)
		// argv[5] stop type(0:Forced stop./2:Stop with wait.)

		if (argc == 6)
		{

			// Set layer
			layer = strtoul(argv[2], NULL, 0);

			// Set layer for LCD/mipi
			layer1 = strtoul(argv[3], NULL, 0);

			// Set write channel
			BYTE writeChannel;
			writeChannel = strtoul(argv[4], NULL, 0);

			E_IM_DISP_STOP_TYPE stop_type = E_IM_DISP_STOP_TYPE_WITHOUT_WAIT;

			if (strcmp((kchar*) argv[5], "0") == 0)
			{
				stop_type = E_IM_DISP_STOP_TYPE_WITHOUT_WAIT;
			}
			else if (strcmp((kchar*) argv[5], "1") == 0)
			{
				stop_type = E_IM_DISP_STOP_TYPE_WITH_WAIT;
			}
			else
			{
				Ddim_Print(("Parameter(stop type) error\n"));
			}

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3a_dump_reg_trg(disp3a);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Stop(layer, layer1, writeChannel, stop_type); /* pgr0539 */
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Stop error=%08X\n", error));
			}
			else
			{
				error = Im_DISP_Wait_Stop(layer, layer1);
				if (error != D_DDIM_OK)
				{
					Ddim_Print(("Im_DISP_Wait_Stop error=%08X\n", error));
				}
				else
				{
					Ddim_Print(("------- After Setting -------\n"));
					ct_im_disp3a_dump_reg_trg(disp3a);
				}
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 3\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "status") == 0)
	{
		//Im_DISP_Get_Status

		// argc=3
		// argv[0] "imdisp"
		// argv[1] "status"
		// argv[2] Command select(0:Normal/1:HDMI layer None./2:LCD/mipi layer None./3:both None.)

		if (argc == 3)
		{
			layer = E_IM_DISP_SEL_LAYER_NONE;
			layer1 = E_IM_DISP_SEL_LAYER_NONE;

			switch (argv[2][0])
			{
			case '0':
				error = Im_DISP_Get_Status(NULL, NULL);
				break;
			case '1':
				error = Im_DISP_Get_Status(&layer, NULL);
				break;
			case '2':
				error = Im_DISP_Get_Status(NULL, &layer1);
				break;
			case '3':
				error = Im_DISP_Get_Status(&layer, &layer1);
				break;
			default:
				Ddim_Print(("Command Parameter error.\n"));
				return;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Status error=%08X\n", error));
			}
			else
			{
				ct_im_disp3a_dump_reg_trg(disp3a);
				Ddim_Print(("Block:0 status = %08X\n", layer));
				Ddim_Print(("Block:1 status = %08X\n", layer1));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 3\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "Wait") == 0)
	{
		//Im_DISP_Wait_Vsync

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "Wait"
		// argv[2] block(0/1)
		// argv[3] interruption_select
		// argv[4] wait_time

		if (argc == 5)
		{
			E_IM_DISP_SEL block = strtoul(argv[2], NULL, 0);
			kuint32 interruptionSelect = strtoul(argv[3], NULL, 0);
			E_IM_DISP_WAIT wait_time = (E_IM_DISP_WAIT) strtoul(argv[4], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TRG  = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].DCORE.TRG.word)); /* pgr0539 */
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.INTC = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].DCORE.INTC.word));
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.INTE = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].DCORE.INTE.word));
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.INTF = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].DCORE.INTF.word));
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Wait_Vsync(block,
					(E_IM_DISP_INTERRUPTION_SELECT) interruptionSelect, wait_time); /* pgr0539 */
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Wait_Vsync error=%08X\n",error));
			}
			else
			{
#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
				Ddim_Print(("------- After Setting -------\n"));
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TRG  = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].DCORE.TRG.word));
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.INTC = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].DCORE.INTC.word));
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.INTE = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].DCORE.INTE.word));
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.INTF = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].DCORE.INTF.word));
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "WaitStop") == 0)
	{
		//Im_DISP_Wait_Stop

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "start"
		// argv[2] HDMI layer
		// argv[3] LCD/MIPI layer

		if (argc == 4)
		{
			// Set HDMI layer
			layer = strtoul(argv[2], NULL, 0);

			// Set layer for LCD/mipi
			layer1 = strtoul(argv[3], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3a_dump_reg_trg(disp3a);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Wait_Stop(layer, layer1); /* pgr0539 */
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Wait_Stop error=%08X\n",error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3a_dump_reg_trg(disp3a);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "IntHndl") == 0)
	{
		//Im_DISP_Int_Handler

		// argc=2
		// argv[0] "imdisp"
		// argv[1] "IntHndl"

		if (argc == 2)
		{
			Im_DISP_Int_Handler();
		}
		else
		{
			Ddim_Print(("Parameter num shold be 2\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "SetSR") == 0)
	{
		//Im_DISP_Set_SR

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "SetSR"
		// argv[2] HDMI layer
		// argv[3] LCD/mipi layer
		// argv[4] setting(0:reset cansel/1:reset)

		if (argc == 5)
		{
			layer = strtoul(argv[2], NULL, 0);
			layer1 = strtoul(argv[3], NULL, 0);
			BYTE sr = strtoul(argv[4], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_dump_reg_reset(disp3);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Set_SR(layer, layer1, sr); /* pgr0539 */
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_SR error=%08X\n",error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_dump_reg_reset(disp3);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 3\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetSR") == 0)
	{
		//Im_DISP_Get_SR

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetSR"
		// argv[2] Command select(0:both None./1:HDMI layer None./2:LCD/mipi layer None./3:Normal)

		if (argc == 3)
		{
			layer = 0;
			layer1 = 0;

			switch (argv[2][0])
			{
			case '0':
				error = Im_DISP_Get_SR(NULL, NULL);
				break;
			case '1':
				error = Im_DISP_Get_SR(NULL, &layer1);
				break;
			case '2':
				error = Im_DISP_Get_SR(&layer, NULL);
				break;
			case '3':
				error = Im_DISP_Get_SR(&layer, &layer1);
				break;
			default:
				Ddim_Print(("Parameter command error.\n"));
				return;
				break;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_SR error=%08X\n",error));
			}
			else
			{
				ct_im_disp3_dump_reg_reset(disp3);
				Ddim_Print(("HDMI     layer = %08X\n", layer));
				Ddim_Print(("MIPI/LCD layer = %08X\n", layer1));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 2\n"));
		}
	}

}
#endif /*CtImDisp_CO_DEBUG_DISP*/

/*
 * PUBLIC
 * */

CtImDisp2d *ct_im_disp2d_new(void)
{
	CtImDisp2d *self = (CtImDisp2d *) k_object_new_with_private(CT_TYPE_IM_DISP2D,sizeof(CtImDisp2dPrivate));
	return self;
}

