/*
 *ctimdisp2g.c
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

#include "ctimdisp3.h"//static func ct_im_disp3_int_00_cb

#include "imdisp2group.h"
#include "ctimdisp2g.h"

K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(CtImDisp2g, ct_im_disp2g, IM_TYPE_DISP2_PARENT)
#define CT_IM_DISP2G_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), CtImDisp2gPrivate, CT_TYPE_IM_DISP2G))

struct _CtImDisp2gPrivate
{
	kpointer qwertyu;
};

/*
 * DECLS
 * */
#ifdef CtImDisp_CO_DEBUG_DISP
static void disp2gDoMain_od(ImDisp2Parent *parent, kint32 argc, char **argv);
#endif /*CtImDisp_CO_DEBUG_DISP*/

/*
 * IMPL
 * */
static void ct_im_disp2g_constructor(CtImDisp2g *self)
{
	//CtImDisp2gPrivate *priv = CT_IM_DISP2G_GET_PRIVATE(self);
#ifdef CtImDisp_CO_DEBUG_DISP
	ImDisp2Parent *parent = (ImDisp2Parent *)self;
	parent->doMainFunc = disp2gDoMain_od;
#endif /*CtImDisp_CO_DEBUG_DISP*/
}

static void ct_im_disp2g_destructor(CtImDisp2g *self)
{
}

#ifdef CtImDisp_CO_DEBUG_DISP
static void disp2gDoMain_od(ImDisp2Parent *parent, kint32 argc, char **argv)
{
	kint32 error = D_DDIM_OK;
	ImDisp2Group *imDisp2Group = (ImDisp2Group *)im_disp2_parent_get_group(parent);
	kuchar *pImDispPclkCounter = im_disp2_group_get_pclk_counter(imDisp2Group);

	if (strcmp((kchar*) argv[1], "SetRev") == 0)
	{
		//Im_DISP_Set_Reverse_Display

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "SetRev"
		// argv[2] block(0/1)
		// argv[3] reverse

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			U_IM_DISP_LREVDISP reverse;
			reverse.word = strtoul(argv[3], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].LCH.LREVDISP = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].LCH.LREVDISP.word)); /* pgr0539 */
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Im_DISP_Set_Reverse_Display(block, reverse);

			Ddim_Print(("------- After Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].LCH.LREVDISP = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].LCH.LREVDISP.word));
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetRev") == 0)
	{
		//Im_DISP_Get_Display_Position

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetRev"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			U_IM_DISP_LREVDISP reverse;
			memset(&reverse, 0, sizeof(U_IM_DISP_LREVDISP));
			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Reverse_Display(block, NULL); /* pgr0539 */
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Get_Reverse_Display(block, &reverse); /* pgr0539 */
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Reverse_Display error=%08X\n",error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].LCH.LREVDISP = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].LCH.LREVDISP.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("[U_IM_DISP_LREVDISP]\n"));
				Ddim_Print(("HREV:%d, VREV:%d\n", reverse.bit.HREV, reverse.bit.VREV));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "SetIf") == 0)
	{
		//Im_DISP_Set_Display_Interface

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "SetIf"
		// argv[2] block(0/1)
		// argv[3] ifs

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			BYTE ifs;
			ifs = strtoul(argv[3], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.RESET = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].DCORE.RESET.word)); /* pgr0539 */
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.IFS   = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].DCORE.IFS.word));
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Set_Display_Interface(block, ifs); /* pgr0539 */
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_Display_Interface error=%08X\n", error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.RESET = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].DCORE.RESET.word));
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.IFS   = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].DCORE.IFS.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetIf") == 0)
	{
		//Im_DISP_Get_Display_Interface

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetIf"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			BYTE ifs = 0;
			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Display_Interface(block, NULL); /* pgr0539 */
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Get_Display_Interface(block, &ifs); /* pgr0539 */
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Display_Interface error=%08X\n",error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.RESET = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].DCORE.RESET.word));
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.IFS   = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].DCORE.IFS.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("[BYTE]\n"));
				Ddim_Print(("ifs:%d\n", ifs));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "SetStartMod") == 0)
	{
		//Im_DISP_Set_External_Startup_Mode

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "SetStartMod"
		// argv[2] block(0/1)
		// argv[3] tgkmd(0/1)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			E_IM_DISP_TGKMD tgkmd;
			tgkmd = (kuint32) strtoul(argv[3], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TRG.bit.TGKMD = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].DCORE.TRG.bit.TGKMD)); /* pgr0539 */
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TRG.bit.TRG   = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].DCORE.TRG.bit.TRG));
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Set_External_Startup_Mode(block, tgkmd); /* pgr0539 */
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_External_Startup_Mode error=%08X\n", error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TRG.bit.TGKMD = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].DCORE.TRG.bit.TGKMD));
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TRG.bit.TRG   = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].DCORE.TRG.bit.TRG));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetStartMod") == 0)
	{
		//Im_DISP_Get_External_Startup_Mode

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetStartMod"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			E_IM_DISP_TGKMD tgkmd = 0;
			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_External_Startup_Mode(block, NULL); /* pgr0539 */
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Get_External_Startup_Mode(block, &tgkmd); /* pgr0539 */
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_External_Startup_Mode error=%08X\n",error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TRG.bit.TGKMD = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].DCORE.TRG.bit.TGKMD));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("[E_IM_DISP_TGKMD]\n"));
				Ddim_Print(("tgkmd:%d\n", tgkmd));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "SetStartTmg") == 0)
	{
		//Im_DISP_Set_External_Startup_Timing

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "SetStartTmg"
		// argv[2] block(0/1)
		// argv[3] tgkst(~0x0FFF)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			ULONG tgkst;
			tgkst = (ULONG) strtoul(argv[3], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TRG.bit.TRG = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].DCORE.TRG.bit.TRG)); /* pgr0539 */
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TGKST = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].DCORE.TGKST.word));
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Set_External_Startup_Timing(block, tgkst); /* pgr0539 */
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_External_Startup_Timing error=%08X\n", error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TRG.bit.TRG = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].DCORE.TRG.bit.TRG));
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TGKST = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].DCORE.TGKST.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetStartTmg") == 0)
	{
		//Im_DISP_Get_External_Startup_Timing

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetStartTmg"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			ULONG tgkst = 0;
			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_External_Startup_Timing(block, NULL); /* pgr0539 */
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Get_External_Startup_Timing(block, &tgkst); /* pgr0539 */
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_External_Startup_Timing error=%08X\n",error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TGKST = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].DCORE.TGKST.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("[ULONG]\n"));
				Ddim_Print(("tgkst:%d\n", (kuint32)tgkst));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "SetVSN") == 0)
	{
		//Im_DISP_Set_Vsync_Int_Timing

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "SetVSN"
		// argv[2] block(0/1)
		// argv[3] timing

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			E_IM_DISP_VSYNC_FLAG timing = (E_IM_DISP_VSYNC_FLAG) strtoul(argv[3], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.INTC.word = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].DCORE.INTC.word)); /* pgr0539 */
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Im_DISP_Set_Vsync_Int_Timing(block, timing); /* pgr0539 */

			Ddim_Print(("------- After Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.INTC.word = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].DCORE.INTC.word));
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetVSN") == 0)
	{
		//Im_DISP_Get_Vsync_Int_Timing

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetVSN"
		// argv[2] Command select(0:Normal/1:NULL)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			E_IM_DISP_VSYNC_FLAG timing = E_IM_DISP_VSYNC_FLAG_NONE;

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Vsync_Int_Timing(block, NULL); /* pgr0539 */
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Get_Vsync_Int_Timing(block, &timing); /* pgr0539 */
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Vsync_Int_Timing error=%08X\n",error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.INTC.word = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].DCORE.INTC.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("[E_IM_DISP_VSYNC_FLAG]\n"));
				Ddim_Print(("timing:%d\n", timing));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "SetInt") == 0)
	{
		//Im_DISP_Set_Int

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "SetInt"
		// argv[2] block(0/1)
		// argv[3] interruption_select
		// argv[4] interruption_state(0 or 0x0011F1F1)

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			kuint32 interruptionSelect = (kuint32) strtoul(argv[3], NULL, 0);
			E_IM_DISP_INTERRUPTION_STATE Interruption_State =
					(E_IM_DISP_INTERRUPTION_STATE) strtoul(argv[4], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.INTE = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].DCORE.INTE.word)); /* pgr0539 */
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Set_Int(block, interruptionSelect, Interruption_State); /* pgr0539 */
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_Int error=%08X\n",error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.INTE = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].DCORE.INTE.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetInt") == 0)
	{
		//Im_DISP_Get_Int

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetInt"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			kuint32 Interruption_State = 0;

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Int(block, NULL); /* pgr0539 */
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Get_Int(block, &Interruption_State); /* pgr0539 */
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Int error=%08X\n",error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.INTE = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].DCORE.INTE.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("[kuint32]\n"));
				Ddim_Print(("Interruption_State:0x%08X\n", Interruption_State));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "SetCBK") == 0)
	{
		//Im_DISP_Set_Int_Callback

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "SetCBK"
		// argv[2] block(0/1)
		// argv[3] interruption_select
		// argv[4] CallBack(0~11:Normal / 12~:Illegal)

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			kuint32 interruptionSelect = strtoul(argv[3], NULL, 0);
			if (strcmp((kchar*) argv[4], "0") == 0)
			{
				Ddim_Print(("set callback : ct_im_disp3_int_00_cb\n"));
				error = Im_DISP_Set_Int_Callback(block,
						interruptionSelect, ct_im_disp3_int_00_cb); /* pgr0539 */
			}
			else if (strcmp((kchar*) argv[4], "1") == 0)
			{
				Ddim_Print(("set callback : ct_im_disp3_int_01_cb\n"));
				error = Im_DISP_Set_Int_Callback(block,
						interruptionSelect, ct_im_disp3_int_01_cb); /* pgr0539 */
			}
			else if (strcmp((kchar*) argv[4], "2") == 0)
			{
				Ddim_Print(("set callback : ct_im_disp3_int_02_cb\n"));
				error = Im_DISP_Set_Int_Callback(block,
						interruptionSelect, ct_im_disp3_int_02_cb); /* pgr0539 */
			}
			else if (strcmp((kchar*) argv[4], "3") == 0)
			{
				Ddim_Print(("set callback : ct_im_disp3_int_03_cb\n"));
				error = Im_DISP_Set_Int_Callback(block,
						interruptionSelect, ct_im_disp3_int_03_cb); /* pgr0539 */
			}
			else if (strcmp((kchar*) argv[4], "4") == 0)
			{
				Ddim_Print(("set callback : ct_im_disp3_int_04_cb\n"));
				error = Im_DISP_Set_Int_Callback(block,
						interruptionSelect, ct_im_disp3_int_04_cb); /* pgr0539 */
			}
			else if (strcmp((kchar*) argv[4], "5") == 0)
			{
				Ddim_Print(("set callback : ct_im_disp3_int_05_cb\n"));
				error = Im_DISP_Set_Int_Callback(block,
						interruptionSelect, ct_im_disp3_int_05_cb); /* pgr0539 */
			}
			else if (strcmp((kchar*) argv[4], "6") == 0)
			{
				Ddim_Print(("set callback : ct_im_disp3_int_06_cb\n"));
				error = Im_DISP_Set_Int_Callback(block,
						interruptionSelect, ct_im_disp3_int_06_cb); /* pgr0539 */
			}
			else if (strcmp((kchar*) argv[4], "7") == 0)
			{
				Ddim_Print(("set callback : ct_im_disp3_int_07_cb\n"));
				error = Im_DISP_Set_Int_Callback(block,
						interruptionSelect, ct_im_disp3_int_07_cb); /* pgr0539 */
			}
			else if (strcmp((kchar*) argv[4], "8") == 0)
			{
				Ddim_Print(("set callback : ct_im_disp3_int_08_cb\n"));
				error = Im_DISP_Set_Int_Callback(block,
						interruptionSelect, ct_im_disp3_int_08_cb); /* pgr0539 */
			}
			else if (strcmp((kchar*) argv[4], "9") == 0)
			{
				Ddim_Print(("set callback : ct_im_disp3_int_09_cb\n"));
				error = Im_DISP_Set_Int_Callback(block,
						interruptionSelect, ct_im_disp3_int_09_cb); /* pgr0539 */
			}
			else if (strcmp((kchar*) argv[4], "10") == 0)
			{
				Ddim_Print(("set callback : ct_im_disp3_int_10_cb\n"));
				error = Im_DISP_Set_Int_Callback(block,
						interruptionSelect, ct_im_disp3_int_10_cb); /* pgr0539 */
			}
			else if (strcmp((kchar*) argv[4], "11") == 0)
			{
				Ddim_Print(("set callback : ct_im_disp3_int_11_cb\n"));
				error = Im_DISP_Set_Int_Callback(block,
						interruptionSelect, ct_im_disp3_int_11_cb); /* pgr0539 */
			}
			else
			{
				Ddim_Print(("clear callback setting\n"));
				error = Im_DISP_Set_Int_Callback(block,
						interruptionSelect, NULL); /* pgr0539 */
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_Int_Callback error=%08X\n", error));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetCBK") == 0)
	{
		//Im_DISP_Get_Int_Callback

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "GetCBK"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)
		// argv[4] interruption_select

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			E_IM_DISP_INTERRUPTION_SELECT interruptionSelect =
					(E_IM_DISP_INTERRUPTION_SELECT) strtoul(argv[4], NULL, 0);
			VP_CALLBACK pCallbacl = NULL;

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Int_Callback(block, interruptionSelect, NULL); /* pgr0539 */
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Get_Int_Callback(block, interruptionSelect, &pCallbacl); /* pgr0539 */
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Int_Callback error=%08X\n", error));
			}
			else
			{
				if (pCallbacl == ct_im_disp3_int_00_cb)
				{
					Ddim_Print(("pCallbacl=ct_im_disp3_int_00_cb\n"));
				}
				else if (pCallbacl == ct_im_disp3_int_01_cb)
				{
					Ddim_Print(("pCallbacl=ct_im_disp3_int_01_cb\n"));
				}
				else if (pCallbacl == ct_im_disp3_int_02_cb)
				{
					Ddim_Print(("pCallbacl=ct_im_disp3_int_02_cb\n"));
				}
				else if (pCallbacl == ct_im_disp3_int_03_cb)
				{
					Ddim_Print(("pCallbacl=ct_im_disp3_int_03_cb\n"));
				}
				else if (pCallbacl == ct_im_disp3_int_04_cb)
				{
					Ddim_Print(("pCallbacl=ct_im_disp3_int_04_cb\n"));
				}
				else if (pCallbacl == ct_im_disp3_int_05_cb)
				{
					Ddim_Print(("pCallbacl=ct_im_disp3_int_05_cb\n"));
				}
				else if (pCallbacl == ct_im_disp3_int_06_cb)
				{
					Ddim_Print(("pCallbacl=ct_im_disp3_int_06_cb\n"));
				}
				else if (pCallbacl == ct_im_disp3_int_07_cb)
				{
					Ddim_Print(("pCallbacl=ct_im_disp3_int_07_cb\n"));
				}
				else if (pCallbacl == ct_im_disp3_int_08_cb)
				{
					Ddim_Print(("pCallbacl=ct_im_disp3_int_08_cb\n"));
				}
				else if (pCallbacl == ct_im_disp3_int_09_cb)
				{
					Ddim_Print(("pCallbacl=ct_im_disp3_int_09_cb\n"));
				}
				else if (pCallbacl == ct_im_disp3_int_10_cb)
				{
					Ddim_Print(("pCallbacl=ct_im_disp3_int_10_cb\n"));
				}
				else if (pCallbacl == ct_im_disp3_int_11_cb)
				{
					Ddim_Print(("pCallbacl=ct_im_disp3_int_11_cb\n"));
				}
				else
				{
					Ddim_Print(("pCallbacl=NULL\n"));
				}
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetAxi") == 0)
	{
		//Im_DISP_Get_AXI_Status

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetAxi"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			U_IM_DISP_AXISTS axiState;
			axiState.word = 0;
			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_AXI_Status(block, NULL); /* pgr0539 */
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Get_AXI_Status(block, &axiState); /* pgr0539 */
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_AXI_Status error=%08X\n",error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.AXISTS = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].DCORE.AXISTS.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("[U_IM_DISP_AXISTS]\n"));
				Ddim_Print(("axiState = %08X\n",(kuint32)axiState.word));
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

CtImDisp2g *ct_im_disp2g_new(void)
{
	CtImDisp2g *self = (CtImDisp2g *) k_object_new_with_private(CT_TYPE_IM_DISP2G,sizeof(CtImDisp2gPrivate));
	return self;
}

