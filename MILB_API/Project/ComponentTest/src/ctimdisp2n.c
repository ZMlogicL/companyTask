/*
 *ctimdisp2n.c
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

#include "ctimdisp3.h"//static func
#include "ctimdisp3a.h"
#include "ctimdisp4.h"

#include "imdisp2group.h"
#include "ctimdisp2n.h"

K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(CtImDisp2n, ct_im_disp2n, IM_TYPE_DISP2_PARENT)
#define CT_IM_DISP2N_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), CtImDisp2nPrivate, CT_TYPE_IM_DISP2N))

struct _CtImDisp2nPrivate
{
	kpointer qwertyu;
	T_IM_DISP_CTRL_P2M gLcdDispTblCtrlP2m;//const
	T_IM_DISP_CTRL_PWCH gLcdDispTblCtrlPwch;//const
};

/*
 * DECLS
 * */
#ifdef CtImDisp_CO_DEBUG_DISP
static void disp2nDoMain_od(ImDisp2Parent *parent, kint32 argc, char **argv);
#endif /*CtImDisp_CO_DEBUG_DISP*/

/*
 * IMPL
 * */
static void ct_im_disp2n_constructor(CtImDisp2n *self)
{
	CtImDisp2nPrivate *priv = CT_IM_DISP2N_GET_PRIVATE(self);
	T_IM_DISP_CTRL_P2M *pgLcdDispTblCtrlP2m = &(priv->gLcdDispTblCtrlP2m);
#ifdef CtImDisp_CO_DEBUG_DISP
	ImDisp2Parent *parent = (ImDisp2Parent *)self;
	parent->doMainFunc = disp2nDoMain_od;
#endif /*CtImDisp_CO_DEBUG_DISP*/
	self->ctImDisp2nPrivate =priv;

	pgLcdDispTblCtrlP2m->p2mpaen =(ULONG)D_IM_DISP_ENABLE_ON;					// P2MPAEN(ena)
	pgLcdDispTblCtrlP2m->p2mctl_plpf =(E_IM_DISP_PLPF)E_IM_DISP_PLPF_LONG;		// p2mctl_plpf
	pgLcdDispTblCtrlP2m->p2mctl_p2mtyp =(E_IM_DISP_P2MTYP)E_IM_DISP_P2MTYP_16;		// p2mctl_p2mtyp
	pgLcdDispTblCtrlP2m->p2mofs =(kushort)32767;								// p2mofs
	pgLcdDispTblCtrlP2m->pbsft =(BYTE)8;									// pbsft
	pgLcdDispTblCtrlP2m->pclph =(kushort)65535;								// pclph
	pgLcdDispTblCtrlP2m->ptrmv =(kushort)8191;								// ptrmv
	pgLcdDispTblCtrlP2m->ptrmh =(kushort)12287;								// ptrmh
	pgLcdDispTblCtrlP2m->ptrmvw =(kushort)65535;								// ptrmvw
	pgLcdDispTblCtrlP2m->ptrmhw =(ULONG)16777215;							// ptrmhw
	pgLcdDispTblCtrlP2m->ptrmxvcyc =(BYTE)63;									// ptrmxvcyc
	pgLcdDispTblCtrlP2m->ptrmxhcyc =(BYTE)63;									// ptrmxhcyc
	pgLcdDispTblCtrlP2m->ptrmxven =(UINT64)0xFFFFFFFFull;						// ptrmxven
	pgLcdDispTblCtrlP2m->ptrmxhen =(UINT64)0xFFFFFFFFull;						// ptrmxhen
	pgLcdDispTblCtrlP2m->p2mmir =(BYTE)D_IM_DISP_ENABLE_ON;					// p2mmir
	pgLcdDispTblCtrlP2m->p2m2pmd =(E_IM_DISP_P2M2PMD)E_IM_DISP_P2M2PMD_2;		// p2m2pmd

	T_IM_DISP_CTRL_PWCH *pgLcdDispTblCtrlPwch = &(priv->gLcdDispTblCtrlPwch);
	pgLcdDispTblCtrlPwch->pwaxctl.word =	(ULONG)0x0000070F;						// pwaxctl
	pgLcdDispTblCtrlPwch->pwmw = (BYTE)D_IM_DISP_ENABLE_ON;					// pwmw
	pgLcdDispTblCtrlPwch->pwchintenb.word = (ULONG)0x00000111;						// pwchintenb
	pgLcdDispTblCtrlPwch->pwsa = (ULONG)4294967288;							// pwsa
	pgLcdDispTblCtrlPwch->pwlsize = (ULONG)2147483640;							// pwlsize
	pgLcdDispTblCtrlPwch->pwvfm = (BYTE)D_IM_DISP_FORMAT_VIDEO	;			// pwvfm
}

static void ct_im_disp2n_destructor(CtImDisp2n *self)
{
}

#ifdef CtImDisp_CO_DEBUG_DISP
static void disp2nDoMain_od(ImDisp2Parent *parent, kint32 argc, char **argv)
{
	CtImDisp2n *self = (CtImDisp2n *)parent;
	kint32 error = D_DDIM_OK;
	kuint32 layer = 0;
	ImDisp2Group *disp2Group = (ImDisp2Group *)im_disp2_parent_get_group(parent);
	CtImDisp4 *ctImDisp4 = (CtImDisp4 *)im_disp2_group_get_disp4(disp2Group);
	ImDisp2Group *imDisp2Group = (ImDisp2Group *)im_disp2_parent_get_group(parent);
	kuchar *pImDispPclkCounter = im_disp2_group_get_pclk_counter(imDisp2Group);
	CtImDisp3 *disp3 = (CtImDisp3 *)im_disp2_group_get_disp3(imDisp2Group);
	CtImDisp3a *disp3a = (CtImDisp3a *)im_disp2_group_get_disp3a(imDisp2Group);

	if (strcmp((kchar*) argv[1], "SetGainTbl") == 0)
	{
		//Im_DISP_Set_Chroma_Gain_Table

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "SetGainTbl"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)
		// argv[4] surface(A:0/B:1)

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			BYTE surface = (BYTE) strtoul(argv[4], NULL, 0);
			kushort setTable[33];
			if (surface == 0)
			{
				memcpy(setTable, ct_im_disp4_get_gain_tbla(ctImDisp4), sizeof(setTable));
			}
			else
			{
				memcpy(setTable, ct_im_disp4_get_gain_tblb(ctImDisp4), sizeof(setTable));
			}
			T_IM_DISP_CTRL_OUTPUT_TBL outputTbl;
			outputTbl.chroma_a = (kushort*) setTable;

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TRG        = 0x%08X\n",
					block, IO_DISP.MAIN[block].DCORE.TRG.bit.TRG)); /* pgr0539 */
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TBLASET.bit.YSATSL = 0x%08X\n",
					block, IO_DISP.MAIN[block].DCORE.TBLASET.bit.YSATSL));
			Ddim_Print(("Surface = %02X\n", surface));
			ct_im_disp3_dump_gain_table(disp3, block);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			if (argv[2][0] == '0')
			{
				error = Im_DISP_Set_Chroma_Gain_Table(block, surface, NULL);
			}
			else
			{
//					error = Im_DISP_Set_Chroma_Gain_Table(block, surface, setTable);
				error = Im_DISP_Set_Chroma_Gain_Table(block, surface, (kushort*) &outputTbl.chroma_a);
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_Chroma_Gain_Table error=%08X\n",error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_dump_gain_table(disp3, block);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetGainTbl") == 0)
	{
		//Im_DISP_Get_Chroma_Gain_Table

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "GetGainTbl"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)
		// argv[4] surface(A:0/B:1)

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			BYTE surface = (BYTE) strtoul(argv[4], NULL, 0);
			kushort getTable[33];
			memset(getTable, 0, sizeof(getTable));
			T_IM_DISP_CTRL_OUTPUT_TBL outputTbl;
			outputTbl.chroma_a = (kushort*) getTable;

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Setting -------\n"));
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TRG        = 0x%08X\n",
					block, IO_DISP.MAIN[block].DCORE.TRG.bit.TRG)); /* pgr0539 */
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TBLASET.bit.YSATSL = 0x%08X\n",
					block, IO_DISP.MAIN[block].DCORE.TBLASET.bit.YSATSL));
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Chroma_Gain_Table(block, surface, NULL); /* pgr0539 */
			}
			else
			{
//					error = Im_DISP_Get_Chroma_Gain_Table(block, surface, getTable);	/* pgr0539 */
				error = Im_DISP_Get_Chroma_Gain_Table(block,
						surface, (kushort*) &outputTbl.chroma_a); /* pgr0539 */
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Chroma_Gain_Table error=%08X\n", error));
			}
			else
			{
				ct_im_disp3_dump_gain_table(disp3, block);

				Ddim_Print(("Surface = %02X\n", surface));
				ct_im_disp3a_output_ushort_33_table(getTable);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "SetMipiCtrl0") == 0)
	{
		//Im_DISP_Set_Mipi_Dsi_Ctrl0

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "SetMipiCtrl0"
		// argv[2] shudown
		// argv[3] color_mode

		if (argc == 4)
		{
			BYTE shudown = (BYTE) strtoul(argv[2], NULL, 0);
			BYTE color_mode = (BYTE) strtoul(argv[3], NULL, 0);
#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MDSCTL.MDSIC0 = 0x%08X\n", (kuint32)IO_DISP.MDSCTL.MDSIC0.word));
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Set_Mipi_Dsi_Ctrl0(shudown, color_mode); /* pgr0539 */
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_Mipi_Dsi_Ctrl0 error=%08X\n", error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("------- After Setting -------\n"));
				Ddim_Print(("IO_DISP.MDSCTL.MDSIC0 = 0x%08X\n", (kuint32)IO_DISP.MDSCTL.MDSIC0.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetMipiCtrl0") == 0)
	{
		//Im_DISP_Get_Mipi_Dsi_Ctrl0

		// argc=3
		// argv[0] "imdisp"
		// argv[1] "GetDbgCtrl"
		// argv[2] Command select(0:both NULL/1:shudown NULL/2:color NULL/3:Normal)

		if (argc == 3)
		{
			BYTE shudown = 0;
			BYTE color_mode = 0;
			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Mipi_Dsi_Ctrl0(NULL, NULL);
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Get_Mipi_Dsi_Ctrl0(NULL, &color_mode);
			}
			else if (argv[2][0] == '2')
			{
				error = Im_DISP_Get_Mipi_Dsi_Ctrl0(&shudown, NULL);
			}
			else
			{
				error = Im_DISP_Get_Mipi_Dsi_Ctrl0(&shudown, &color_mode);
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Mipi_Dsi_Ctrl0 error=%08X\n", error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MDSCTL.MDSIC0 = 0x%08X\n", (kuint32)IO_DISP.MDSCTL.MDSIC0.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("shudown    = 0x%02X\n", shudown));
				Ddim_Print(("color_mode = 0x%02X\n", color_mode));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 3\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "SetMipiCtrl1") == 0)
	{
		//Im_DISP_Set_Mipi_Dsi_Ctrl1

		// argc=2
		// argv[0] "imdisp"
		// argv[1] "SetMipiCtrl1"

		if (argc == 2)
		{
#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MDSCTL.MDSIC1 = 0x%08X\n", (kuint32)IO_DISP.MDSCTL.MDSIC1.word));
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Set_Mipi_Dsi_Ctrl1();
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_Mipi_Dsi_Ctrl1 error=%08X\n", error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("------- After Setting -------\n"));
				Ddim_Print(("IO_DISP.MDSCTL.MDSIC1 = 0x%08X\n", (kuint32)IO_DISP.MDSCTL.MDSIC1.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 2\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetMipiCtrl1") == 0)
	{
		//Im_DISP_Get_Mipi_Dsi_Ctrl1

		// argc=3
		// argv[0] "imdisp"
		// argv[1] "GetMipiCtrl1"
		// argv[2] Command select(0:NULL/1:Normal)

		if (argc == 3)
		{
			BYTE update_config = 0;
			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Mipi_Dsi_Ctrl1(NULL);
			}
			else
			{
				error = Im_DISP_Get_Mipi_Dsi_Ctrl1(&update_config);
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Mipi_Dsi_Ctrl1 error=%08X\n", error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MDSCTL.MDSIC1 = 0x%08X\n", (kuint32)IO_DISP.MDSCTL.MDSIC1.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("MDSIC1 = 0x%08X\n", update_config));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 3\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "ChgCsC") == 0)
	{
		//Im_DISP_Change_CSC_Matrix

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "ChgCsC"
		// argv[2] block(0/1)
		// argv[3] layer
		// argv[4] convert

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			layer = strtoul(argv[3], NULL, 0);
			E_IM_DISP_CC_MATRIX convert = (E_IM_DISP_CC_MATRIX) strtoul(argv[4], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_dump_reg_csc_matrix(disp3, block); /* pgr0539 */
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Change_CSC_Matrix(block, (E_IM_DISP_SEL_LAYER) layer, convert); /* pgr0539 */
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Change_CSC_Matrix error=%08X\n",error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_dump_reg_csc_matrix(disp3, block);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "ChgBBCol") == 0)
	{
		//Im_DISP_Change_BB_Color

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "ChgBBCol"
		// argv[2] block(0/1)
		// argv[3] blackBackColor

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			U_IM_DISP_IMAGE_COLOR blackBackColor;
			blackBackColor.word = strtoul(argv[3], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_dump_reg_bb(disp3);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Im_DISP_Change_BB_Color(block, blackBackColor); /* pgr0539 */

			Ddim_Print(("------- After Setting -------\n"));
			ct_im_disp3_dump_reg_bb(disp3);
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "ChkBBCol") == 0)
	{
		//Im_DISP_Check_BB_Color

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "ChgCsC"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			U_IM_DISP_IMAGE_COLOR blackBackColor;
			memset(&blackBackColor, 0, sizeof(U_IM_DISP_IMAGE_COLOR));
			if (argv[2][0] == '0')
			{
				error = Im_DISP_Check_BB_Color(block, NULL); /* pgr0539 */
			}
			else
			{
				error = Im_DISP_Check_BB_Color(block, &blackBackColor); /* pgr0539 */
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Check_BB_Color error=%08X\n",error));
			}
			else
			{
				ct_im_disp3_dump_reg_bb(disp3);

				Ddim_Print(("[U_IM_DISP_IMAGE_COLOR]\n"));
				Ddim_Print(("RGB r=%d g=%d b=%d\n",
						blackBackColor.rgb.r, blackBackColor.rgb.g, blackBackColor.rgb.b));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 2\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "ChgGrid") == 0)
	{
		//Im_DISP_Change_Grid

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "ChgGrid"
		// argv[2] block(0/1)
		// argv[3] ghnum
		// argv[4] gvnum

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			kuint32 ghnum = strtoul(argv[3], NULL, 0);
			kuint32 gvnum = strtoul(argv[4], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_dump_reg_output_size(disp3, block); /* pgr0539 */
			ct_im_disp3a_dump_reg_grid(disp3a, block);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Change_Grid(block, ghnum, gvnum); /* pgr0539 */
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Change_Grid error=%08X\n",error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_dump_reg_output_size(disp3, block);
				ct_im_disp3a_dump_reg_grid(disp3a, block);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "DrawFF") == 0)
	{
		//Im_DISP_Draw_Face_Frame_Single

		// argc=10
		// argv[0] "imdisp"
		// argv[1] "ChgGrid"
		// argv[2] Command select(0:Normal/1:NULL)
		// argv[3] block(0/1)
		// argv[4] index
		// argv[5] enable
		// argv[6] face.ffdsta
		// argv[7] face.ffsize
		// argv[8] face.ffwidth
		// argv[9] face.ffclr

		if (argc == 10)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			kint32 index = strtoul(argv[4], NULL, 0);
			kint32 enable = strtoul(argv[5], NULL, 0);
			T_IM_DISP_FACE_FRAME_PARAM face;
			face.ffdsta.word = strtoul(argv[6], NULL, 0);
			face.ffsize.word = strtoul(argv[7], NULL, 0);
			face.ffwidth.word = strtoul(argv[8], NULL, 0);
			face.ffclr.word = strtoul(argv[9], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			Ddim_Print(("Index = %d\n", index)); /* pgr0539 */
			ct_im_disp3_dump_reg_face(disp3, block); /* pgr0539 */
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			if (argv[2][0] == '0')
			{
				error = Im_DISP_Draw_Face_Frame_Single(block, index, enable, NULL); /* pgr0539 */
			}
			else
			{
				error = Im_DISP_Draw_Face_Frame_Single(block, index, enable, &face); /* pgr0539 */
			}

			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Draw_Face_Frame_Single error=%08X\n",error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				Ddim_Print(("Index = %d\n", index));
				ct_im_disp3_dump_reg_face(disp3, block);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 10\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "SetSRIP") == 0)
	{
		//Im_DISP_Set_SR_IP

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "SetSRIP"
		// argv[2] ip
		// argv[3] sr

		if (argc == 4)
		{
			BYTE ip = (BYTE) strtoul(argv[2], NULL, 0);
			BYTE sr = (BYTE) strtoul(argv[3], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			Ddim_Print(("ip = %d\n", ip)); /* pgr0539 */
			Ddim_Print(("sr = %d\n", sr)); /* pgr0539 */
			Ddim_Print(("IO_DISP.MAIN[0].DCORE.TRG.bit.TRG = %d\n",
					IO_DISP.MAIN[E_IM_DISP_HDMI].DCORE.TRG.bit.TRG));
			Ddim_Print(("IO_DISP.MAIN[1].DCORE.TRG.bit.TRG = %d\n",
					IO_DISP.MAIN[E_IM_DISP_LCD_MIPI].DCORE.TRG.bit.TRG));
			Ddim_Print(("IO_DISP.JDDISP_HDMI_HDMIC.HDMISR  = 0x%08X\n",
					(kuint32)IO_DISP.JDDISP_HDMI_HDMIC.HDMISR.word));
			Ddim_Print(("IO_DISP.MDSCTL.MDSSR              = 0x%08X\n",
					(kuint32)IO_DISP.MDSCTL.MDSSR.word));
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Set_SR_IP(ip, sr);
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_SR_IP error=%08X\n",error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				Ddim_Print(("IO_DISP.JDDISP_HDMI_HDMIC.HDMISR.word = 0x%08X\n",
						(kuint32)IO_DISP.JDDISP_HDMI_HDMIC.HDMISR.word));
				Ddim_Print(("IO_DISP.MDSCTL.MDSSR.word             = 0x%08X\n",
						(kuint32)IO_DISP.MDSCTL.MDSSR.word));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetSRIP") == 0)
	{
		//Im_DISP_Get_SR_IP

		// argc=3
		// argv[0] "imdisp"
		// argv[1] "GetSRIP"
		// argv[2] Command select(0:NULL/1:Normal)

		if (argc == 3)
		{
			BYTE sr = 0;

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			Ddim_Print(("IO_DISP.JDDISP_HDMI_HDMIC.HDMISR.word = 0x%08X\n",
					(kuint32)IO_DISP.JDDISP_HDMI_HDMIC.HDMISR.word));
			Ddim_Print(("IO_DISP.MDSCTL.MDSSR.word             = 0x%08X\n",
					(kuint32)IO_DISP.MDSCTL.MDSSR.word));
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_SR_IP(NULL);
			}
			else
			{
				error = Im_DISP_Get_SR_IP(&sr);
			}

			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_SR_IP error=%08X\n",error));
			}
			else
			{
				Ddim_Print(("------- Setting Data -------\n"));
				Ddim_Print(("sr = %d\n", sr));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 3\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "SetWrtCH") == 0)
	{
		//Im_DISP_Set_Write_Channel_Ctrl

		// argc=6
		// argv[0] "imdisp"
		// argv[1] "SetWrtCH"
		// argv[2] Command select(0:NO para/1:only first para/2:only second para/3:both para)
		// argv[3] number
		// argv[4] p2m->p2mpaen
		// argv[5] pwch->pwvfm

		if (argc == 6)
		{
			CtImDisp2nPrivate*priv = self->ctImDisp2nPrivate;
			T_IM_DISP_CTRL_P2M p2m = priv->gLcdDispTblCtrlP2m;//有修改的情况
			T_IM_DISP_CTRL_PWCH pwch = priv->gLcdDispTblCtrlPwch;

			E_IM_DISP_WC_NUM number = (E_IM_DISP_WC_NUM) strtoul(argv[3], NULL, 0);
			ULONG p2mpaen = (ULONG) strtoul(argv[4], NULL, 0);
			BYTE pwvfm = (BYTE) strtoul(argv[5], NULL, 0);
			p2m.p2mpaen = p2mpaen; /* pgr0539 */
			pwch.pwvfm = pwvfm; /* pgr0539 */

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			Ddim_Print(("IO_DISP.PWCH[%d].PWCHTRG.bit.PWCHTRG = %d\n",
					number, IO_DISP.PWCH[number].PWCHTRG.bit.PWCHTRG)); /* pgr0539 */
			Ddim_Print(("IO_DISP.P2M[%d].P2MTRG.bit.P2MTRG    = %d\n",
					number, IO_DISP.P2M[number].P2MTRG.bit.P2MTRG));
			ct_im_disp3a_dump_reg_p2m_pwch(disp3a, number);
			ct_im_disp3a_output_p2m_pwch(&p2m, pwch);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			if (argv[2][0] == '0')
			{
				error = Im_DISP_Set_Write_Channel_Ctrl(number, NULL, NULL);
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Set_Write_Channel_Ctrl(number, NULL, &pwch);
			}
			else if (argv[2][0] == '2')
			{
				error = Im_DISP_Set_Write_Channel_Ctrl(number, &p2m, NULL);
			}
			else
			{
				error = Im_DISP_Set_Write_Channel_Ctrl(number, &p2m, &pwch);
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_Write_Channel_Ctrl error=%08X\n",error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3a_dump_reg_p2m_pwch(disp3a, number);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 6\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetWrtCH") == 0)
	{
		//Im_DISP_Get_Write_Channel_Ctrl

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetWrtCH"
		// argv[2] Command select(0:NO para/1:only first para/2:only second para/3:both para)
		// argv[3] number

		if (argc == 4)
		{
			T_IM_DISP_CTRL_P2M p2m;
			memset(&p2m, 0, sizeof(T_IM_DISP_CTRL_P2M));
			T_IM_DISP_CTRL_PWCH pwch;
			memset(&pwch, 0, sizeof(T_IM_DISP_CTRL_PWCH));

			E_IM_DISP_WC_NUM number = (E_IM_DISP_WC_NUM) strtoul(argv[3], NULL, 0);

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Write_Channel_Ctrl(number, NULL, NULL); /* pgr0539 */
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Get_Write_Channel_Ctrl(number, NULL, &pwch); /* pgr0539 */
			}
			else if (argv[2][0] == '2')
			{
				error = Im_DISP_Get_Write_Channel_Ctrl(number, &p2m, NULL); /* pgr0539 */
			}
			else
			{
				error = Im_DISP_Get_Write_Channel_Ctrl(number, &p2m, &pwch); /* pgr0539 */
			}

			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_SR_IP error=%08X\n",error));
			}
			else
			{
				Ddim_Print(("------- Setting Data -------\n"));
				ct_im_disp3a_dump_reg_p2m_pwch(disp3a, number);
				ct_im_disp3a_output_p2m_pwch(&p2m, pwch);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetWrtCHRes") == 0)
	{
		//Im_DISP_Get_Write_Channel_Response

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetWrtCHRes"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] number

		if (argc == 4)
		{
			ULONG response = 0;
			E_IM_DISP_WC_NUM number = (E_IM_DISP_WC_NUM) strtoul(argv[3], NULL, 0);

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Write_Channel_Response(number, NULL); /* pgr0539 */
			}
			else
			{
				error = Im_DISP_Get_Write_Channel_Response(number, &response); /* pgr0539 */
			}

			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Write_Channel_Response error=%08X\n",error));
			}
			else
			{
				Ddim_Print(("------- Setting Data -------\n"));
				Ddim_Print(("IO_DISP.PWCH[%d].PWCHBRESP = 0x%08X\n",
						number, (kuint32)IO_DISP.PWCH[number].PWCHBRESP.word));
				Ddim_Print(("response = 0x%08X\n", (kuint32)response));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "delay") == 0)
	{
		if (argc == 3)
		{
			DDIM_USER_RELTIM delaytime = strtoul(argv[2], NULL, 0);
			Ddim_Print(("wait %dms.\n", delaytime)); /* pgr0539 */
			DDIM_User_Dly_Tsk(delaytime);
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

CtImDisp2n *ct_im_disp2n_new(void)
{
	CtImDisp2n *self = (CtImDisp2n *) k_object_new_with_private(CT_TYPE_IM_DISP2N,sizeof(CtImDisp2nPrivate));
	return self;
}
