/*
 *ctimdisp2h.c
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
#include "ctimdisp2h.h"

K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(CtImDisp2h, ct_im_disp2h, IM_TYPE_DISP2_PARENT)
#define CT_IM_DISP2H_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), CtImDisp2hPrivate, CT_TYPE_IM_DISP2H))

struct _CtImDisp2hPrivate
{
	kpointer qwertyu;
};

/*
 * DECLS
 * */
#ifdef CtImDisp_CO_DEBUG_DISP
static void disp2hDoMain_od(ImDisp2Parent *parent, kint32 argc, char **argv);
#endif /*CtImDisp_CO_DEBUG_DISP*/

/*
 * IMPL
 * */
static void ct_im_disp2h_constructor(CtImDisp2h *self)
{
	//CtImDisp2hPrivate *priv = CT_IM_DISP2H_GET_PRIVATE(self);
#ifdef CtImDisp_CO_DEBUG_DISP
	ImDisp2Parent *parent = (ImDisp2Parent *)self;
	parent->doMainFunc = disp2hDoMain_od;
#endif /*CtImDisp_CO_DEBUG_DISP*/
}

static void ct_im_disp2h_destructor(CtImDisp2h *self)
{
}

#ifdef CtImDisp_CO_DEBUG_DISP
static void disp2hDoMain_od(ImDisp2Parent *parent, kint32 argc, char **argv)
{
	kint i = 0;
	kint32 error = D_DDIM_OK;
	ImDisp2Group *imDisp2Group = (ImDisp2Group *)im_disp2_parent_get_group(parent);
	kuchar *pImDispPclkCounter = im_disp2_group_get_pclk_counter(imDisp2Group);
	CtImDisp3 *disp3 = (CtImDisp3 *)im_disp2_group_get_disp3(imDisp2Group);

	if (strcmp((kchar*) argv[1], "SetOutRefTiming") == 0)
	{
		//Im_DISP_Set_Output_Parameter_Reflect_Timing

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "SetOutRefTiming"
		// argv[2] block(0/1)
		// argv[3] timing

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			E_IM_DISP_RPGTMG timing = (E_IM_DISP_RPGTMG) strtoul(argv[3], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.RPGCTL = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].DCORE.RPGCTL.word)); /* pgr0539 */
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Set_Output_Parameter_Reflect_Timing(block, timing); /* pgr0539 */
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_Output_Parameter_Reflect_Timing error=%08X\n", error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.RPGCTL = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].DCORE.RPGCTL.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetOutRefTiming") == 0)
	{
		//Im_DISP_Get_Output_Parameter_Reflect_Timing

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetOutRefTiming"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			E_IM_DISP_RPGTMG timing;
			timing = E_IM_DISP_RPGTMG_VSYNC_FRAME_TOP;
			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Output_Parameter_Reflect_Timing(block, NULL); /* pgr0539 */
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Get_Output_Parameter_Reflect_Timing(block, &timing); /* pgr0539 */
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Output_Parameter_Reflect_Timing error=%08X\n", error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.RPGCTL = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].DCORE.RPGCTL.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("[E_IM_DISP_RPGTMG]\n"));
				Ddim_Print(("Reflect timing:%d\n", timing));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "SetOutRefEn") == 0)
	{
		//Im_DISP_Set_Output_Parameter_Reflect_Enable

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "SetOutRefEn"
		// argv[2] block(0/1)
		// argv[3] enable

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			kuint32 enable = strtoul(argv[3], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.RPGEN = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].DCORE.RPGEN.word)); /* pgr0539 */
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Set_Output_Parameter_Reflect_Enable(block, enable); /* pgr0539 */
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_Output_Parameter_Reflect_Enable error=%08X\n", error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.RPGEN = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].DCORE.RPGEN.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetOutRefEn") == 0)
	{
		//Im_DISP_Get_Output_Parameter_Reflect_Enable

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetOutRefEn"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			kuint32 enable = 0;
			enable = D_IM_DISP_ENABLE_OFF;
			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Output_Parameter_Reflect_Enable(block, NULL); /* pgr0539 */
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Get_Output_Parameter_Reflect_Enable(block, &enable); /* pgr0539 */
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Output_Parameter_Reflect_Enable error=%08X\n", error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.RPGEN = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].DCORE.RPGEN.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("[kuint32]\n"));
				Ddim_Print(("Reflect enable:%d\n", enable));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "SetTSL") == 0)
	{
		//Im_DISP_Set_TSL

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "SetTSL"
		// argv[2] block(0/1)
		// argv[3] tsl(0,1:Normal/2~:Illegal)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			BYTE tsl = strtoul(argv[3], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TSL = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].DCORE.TSL.word)); /* pgr0539 */
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Set_TSL(block, tsl); /* pgr0539 */
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_TSL error=%08X\n", error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TSL = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].DCORE.TSL.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetTSL") == 0)
	{
		//Im_DISP_Get_TSL

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetTSL"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			BYTE tsl = 0;
			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_TSL(block, NULL); /* pgr0539 */
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Get_TSL(block, &tsl); /* pgr0539 */
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_TSL error=%08X\n", error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TSL = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].DCORE.TSL.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("[BYTE]\n"));
				Ddim_Print(("TSL:%d\n", tsl));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetOutSize") == 0)
	{
		//Im_DISP_Get_Output_Size

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetTSL"
		// argv[2] Command select(0:both NULL/1:ohsize NULL/2:ovsize NULL/3:Normal)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			ULONG ovsize = 0;
			ULONG ohsize = 0;
			switch (argv[2][0])
			{
			case '0':
				error = Im_DISP_Get_Output_Size(block, NULL, NULL); /* pgr0539 */
				break;
			case '1':
				error = Im_DISP_Get_Output_Size(block, NULL, &ohsize); /* pgr0539 */
				break;
			case '2':
				error = Im_DISP_Get_Output_Size(block, &ovsize, NULL); /* pgr0539 */
				break;
			case '3':
				error = Im_DISP_Get_Output_Size(block, &ovsize, &ohsize); /* pgr0539 */
				break;
			default:
				Ddim_Print(("Parameter command error.\n"));
				return;
				break;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Output_Size error=%08X\n", error));
			}
			else
			{
				ct_im_disp3_dump_reg_output_size(disp3, block);
				Ddim_Print(("OVSIZE = %08X, OHSIZE = %08X\n", (kuint32)ovsize, (kuint32)ohsize));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "SetFOE") == 0)
	{
		//Im_DISP_Set_Force_Out_Data_Enable

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "SetFOE"
		// argv[2] block(0/1)
		// argv[3] is_enable(0,1:Normal)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			E_IM_DISP_FDOEN Is_enable = (E_IM_DISP_FDOEN) strtoul(argv[3], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.FDOEN = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].DCORE.FDOEN.word)); /* pgr0539 */
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Im_DISP_Set_Force_Out_Data_Enable(block, Is_enable); /* pgr0539 */

			Ddim_Print(("------- After Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.FDOEN = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].DCORE.FDOEN.word));
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetFOE") == 0)
	{
		//Im_DISP_Get_Force_Out_Data_Enable

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetFOE"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			E_IM_DISP_FDOEN Is_enable = E_IM_DISP_FDOEN_ORDINARY_OUT;

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Force_Out_Data_Enable(block, NULL); /* pgr0539 */
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Get_Force_Out_Data_Enable(block, &Is_enable); /* pgr0539 */
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Force_Out_Data_Enable error=%08X\n",error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.FDOEN = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].DCORE.FDOEN.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("[E_IM_DISP_FDOEN]\n"));
				Ddim_Print(("Is_enable = %d\n", Is_enable));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "SetFOD") == 0)
	{
		//Im_DISP_Set_Force_Out_Data

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "SetFOD"
		// argv[2] block(0/1)
		// argv[3] colorData(0,1:Normal)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			U_IM_DISP_IMAGE_COLOR colorData;
			colorData.word = strtoul(argv[3], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.FODATA = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].DCORE.FODATA.word)); /* pgr0539 */
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Im_DISP_Set_Force_Out_Data(block, colorData);

			Ddim_Print(("------- After Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.FODATA = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].DCORE.FODATA.word));
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetFOD") == 0)
	{
		//Im_DISP_Get_Force_Out_Data

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetFOD"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			U_IM_DISP_IMAGE_COLOR colorData;
			memset(&colorData, 0, sizeof(U_IM_DISP_IMAGE_COLOR));
			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Force_Out_Data(block, NULL); /* pgr0539 */
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Get_Force_Out_Data(block, &colorData); /* pgr0539 */
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Force_Out_Data error=%08X\n",error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.FODATA = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].DCORE.FODATA.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("[U_IM_DISP_IMAGE_COLOR]\n"));
				Ddim_Print(("colorData(YCC) = 0x%02X, 0x%02X, 0x%02X\n",
						colorData.ycc.y, colorData.ycc.cb, colorData.ycc.cr ));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "SetBarSz") == 0)
	{
		//Im_DISP_Set_Color_Bar_Size

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "SetBarSz"
		// argv[2] block(0/1)
		// argv[3] clbhsize(0,1:Normal)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			ULONG clbhsize = strtoul(argv[3], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.CLBHSIZE = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].DCORE.CLBHSIZE.word)); /* pgr0539 */
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Set_Color_Bar_Size(block, clbhsize); /* pgr0539 */
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_Color_Bar_Size error=%08X\n", error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.CLBHSIZE = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].DCORE.CLBHSIZE.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 2\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetBarSz") == 0)
	{
		//Im_DISP_Get_Color_Bar_Size

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetBarSz"
		// argv[2] Command select(0:Normal/1:NULL)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			ULONG clbhsize = 0;
			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Color_Bar_Size(block, NULL); /* pgr0539 */
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Get_Color_Bar_Size(block, &clbhsize); /* pgr0539 */
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Color_Bar_Size error=%08X\n",error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.CLBHSIZE = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].DCORE.CLBHSIZE.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("clbhsize:%08X\n",(kuint32)clbhsize));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 2\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "SetBarCr") == 0)
	{
		//Im_DISP_Set_Color_Bar

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "SetBarCr"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)
		// argv[4] clbdt_size

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			U_IM_DISP_IMAGE_COLOR clbdt[D_IM_DISP_COLOR_BAR_COUNT] = { { 0x000000FF },			//RGB Red
			{ 0x0000FF00 },			//RGB Green
			{ 0x00FF0000 },			//RGB Blue
			{ 0x0000FFFF },			//RGB Yellow
			{ 0x00FFFF00 }, { 0x00FF00FF }, { 0x00000000 }, { 0x00808080 },
			{ 0x00FFFFFF }, { 0x00800000 }, { 0x00008000 }, { 0x00000080 },
			{ 0x00008080 }, { 0x00808000 }, { 0x00800080 }, { 0x00FF80FF } };

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_dump_reg_clbdt(disp3, block); /* pgr0539 */
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			kuint32 clbdt_size = (kuint32) strtoul(argv[4], NULL, 0);
			if (argv[2][0] == '0')
			{
				error = Im_DISP_Set_Color_Bar(block, NULL, clbdt_size); /* pgr0539 */
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Set_Color_Bar(block, clbdt, clbdt_size); /* pgr0539 */
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_Color_Bar error=%08X\n",error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_dump_reg_clbdt(disp3, block);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetBarCr") == 0)
	{
		//Im_DISP_Get_Color_Bar

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetBarCr"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			U_IM_DISP_IMAGE_COLOR clbdt[D_IM_DISP_COLOR_BAR_COUNT];
			for (i = 0; i < D_IM_DISP_COLOR_BAR_COUNT; i++)
			{
				clbdt[i].word = 0;
			}
			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Color_Bar(block, NULL); /* pgr0539 */
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Get_Color_Bar(block, clbdt); /* pgr0539 */
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Color_Bar error=%08X\n",error));
			}
			else
			{
				ct_im_disp3_dump_reg_clbdt(disp3, block);
				ct_im_disp3_print_param_clbdt(clbdt);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "SetBlnd") == 0)
	{
		//Im_DISP_Set_Blend

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "SetBlnd"
		// argv[2] block(0/1)
		// argv[3] blend

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			U_IM_DISP_BLDCTL blend;
			blend.word = strtoul((kchar*) argv[3], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.BLDCTL = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].DCORE.BLDCTL.word)); /* pgr0539 */
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Set_Blend(block, blend);
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_Blend error=%08X\n", error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.BLDCTL = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].DCORE.BLDCTL.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetBlnd") == 0)
	{
		//Im_DISP_Get_Blend

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetBlnd"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			U_IM_DISP_BLDCTL blend;
			memset(&blend, 0, sizeof(U_IM_DISP_BLDCTL));

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Blend(block, NULL); /* pgr0539 */
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Get_Blend(block, &blend); /* pgr0539 */
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Blend error=%08X\n",error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.BLDCTL = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].DCORE.BLDCTL.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("[U_IM_DISP_BLDCTL]\n"));
				Ddim_Print(("BLD1:%d, BLD2:%d, BLD3:%d, BLD4:%d\n",
						blend.bit.BLD1, blend.bit.BLD2, blend.bit.BLD3, blend.bit.BLD4));
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

CtImDisp2h *ct_im_disp2h_new(void)
{
	CtImDisp2h *self = (CtImDisp2h *) k_object_new_with_private(CT_TYPE_IM_DISP2H,sizeof(CtImDisp2hPrivate));
	return self;
}

