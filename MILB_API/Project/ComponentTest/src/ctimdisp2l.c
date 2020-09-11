/*
 *ctimdisp2l.c
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
#include "ctimdisp2l.h"

K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(CtImDisp2l, ct_im_disp2l, IM_TYPE_DISP2_PARENT)
#define CT_IM_DISP2L_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), CtImDisp2lPrivate, CT_TYPE_IM_DISP2L))

struct _CtImDisp2lPrivate
{
	kpointer qwertyu;
};

/*
 * DECLS
 * */

#ifdef CtImDisp_CO_DEBUG_DISP
static void disp2lDoMain_od(ImDisp2Parent *parent, kint32 argc, char **argv);
#endif /*CtImDisp_CO_DEBUG_DISP*/

/*
 * IMPL
 * */
static void ct_im_disp2l_constructor(CtImDisp2l *self)
{
	//CtImDisp2lPrivate *priv = CT_IM_DISP2L_GET_PRIVATE(self);
#ifdef CtImDisp_CO_DEBUG_DISP
	ImDisp2Parent *parent = (ImDisp2Parent *)self;
	parent->doMainFunc = disp2lDoMain_od;
#endif /*CtImDisp_CO_DEBUG_DISP*/
}

static void ct_im_disp2l_destructor(CtImDisp2l *self)
{
}

#ifdef CtImDisp_CO_DEBUG_DISP
static void disp2lDoMain_od(ImDisp2Parent *parent, kint32 argc, char **argv)
{
	kint i = 0;
	kint32 error = D_DDIM_OK;
	kuint32 layer = 0;
	ImDisp2Group *imDisp2Group = (ImDisp2Group *)im_disp2_parent_get_group(parent);
	kuchar *pImDispPclkCounter = im_disp2_group_get_pclk_counter(imDisp2Group);
	CtImDisp3 *disp3 = (CtImDisp3 *)im_disp2_group_get_disp3(imDisp2Group);

	if (strcmp((kchar*) argv[1], "SetOSDASize") == 0)
	{
		//Im_DISP_Set_OSD_Area_Size

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "SetOSDASize"
		// argv[2] block(0/1)
		// argv[3] layer
		// argv[4] input_size_count
		// argv[5] inputSize

		if (argc == 6)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			layer = strtoul(argv[3], NULL, 0);
			kuint32 input_size_count = strtoul(argv[4], NULL, 0);
			U_IM_DISP_SIZE inputSize[D_IM_DISP_OSD_DISPLAY_AREA_COUNT] = {
					{ 0x007000C8 }, { 0x00E00190 }, { 0x01C00320 }, { 0x03800640 },
					{ 0x07000C80 }, { 0x0E001900 }, { 0x1C003200 }, { 0x38006400 },
					{ 0x3FFEC800 }, { 0x000E0008 } };
			inputSize[input_size_count - 1].word = strtoul(argv[5], NULL, 0); /* pgr0539 */

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_dump_reg_osd_area_size(disp3, block); /* pgr0539 */
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Set_OSD_Area_Size(block,
					(E_IM_DISP_SEL_LAYER) layer, inputSize, input_size_count); /* pgr0539 */
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_OSD_Area_Size error=%08X\n", error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_dump_reg_osd_area_size(disp3, block);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 6\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetOSDASize") == 0)
	{
		//Im_DISP_Get_OSD_Area_Size

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "GetOSDAreaMon"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)
		// argv[4] layer

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			layer = strtoul(argv[4], NULL, 0);
			U_IM_DISP_SIZE inputSize[D_IM_DISP_OSD_DISPLAY_AREA_COUNT];
			for (i = 0; i < D_IM_DISP_OSD_DISPLAY_AREA_COUNT; i++)
			{
				inputSize[i].word = 0;
			}

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_OSD_Area_Size(block, (E_IM_DISP_SEL_LAYER) layer, NULL); /* pgr0539 */
			}
			else
			{
				error = Im_DISP_Get_OSD_Area_Size(block, (E_IM_DISP_SEL_LAYER) layer, inputSize); /* pgr0539 */
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_OSD_Area_Size error=%08X\n", error));
			}
			else
			{
				ct_im_disp3_dump_reg_osd_area_size(disp3, block);
				Ddim_Print(("Layer = %d\n", layer));
				ct_im_disp3_print_param_osd_area_size(inputSize);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "SetOSDAAddr") == 0)
	{
		//Im_DISP_Set_OSD_Area_Addr

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "SetOSDAAddr"
		// argv[2] block(0/1)
		// argv[3] layer
		// argv[4] bank_no
		// argv[5] address

		if (argc == 6)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			layer = strtoul(argv[3], NULL, 0);
			E_IM_DISP_OSD_SA_BANK_NO bank_no = (E_IM_DISP_OSD_SA_BANK_NO) strtoul(argv[4], NULL, 0);
			ULONG address = strtoul((kchar*) argv[5], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_dump_reg_osd_area_addr(disp3, block); /* pgr0539 */
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Set_OSD_Area_Addr(block,
					(E_IM_DISP_SEL_LAYER) layer, bank_no, address); /* pgr0539 */
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_OSD_Area_Addr error=%08X\n", error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_dump_reg_osd_area_addr(disp3, block);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 6\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetOSDAAddr") == 0)
	{
		//Im_DISP_Get_OSD_Area_Addr

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "GetOSDAAddr"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)
		// argv[4] layer
		// argv[5] bank_no(0~12)

		if (argc == 6)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			layer = strtoul(argv[4], NULL, 0);
			E_IM_DISP_OSD_SA_BANK_NO bank_no = (E_IM_DISP_OSD_SA_BANK_NO) strtoul(argv[5], NULL, 0);
			ULONG address = 0;

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_OSD_Area_Addr(block,
						(E_IM_DISP_SEL_LAYER) layer, bank_no, NULL); /* pgr0539 */
			}
			else
			{
				error = Im_DISP_Get_OSD_Area_Addr(block,
						(E_IM_DISP_SEL_LAYER) layer, bank_no, &address); /* pgr0539 */
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_OSD_Area_Addr error=%08X\n", error));
			}
			else
			{
				ct_im_disp3_dump_reg_osd_area_addr(disp3, block);

				Ddim_Print(("Layer = %02X\n", layer));
				if (bank_no < E_IM_DISP_OSD_SA_BANK_NO_1)
				{
					Ddim_Print(("bank0%d input_address:0x%08X\n", bank_no, (kuint32)address));
				}
				else
				{
					Ddim_Print(("bank%d input_address:0x%08X\n",
							(bank_no - E_IM_DISP_OSD_SA_BANK_NO_0_3), (kuint32)address));
				}
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "SetOSDAAdataAddr") == 0)
	{
		//Im_DISP_Set_OSD_Area_Adata_Addr

		// argc=6
		// argv[0] "imdisp"
		// argv[1] "SetOSDAAdataAddr"
		// argv[2] block(0/1)
		// argv[3] layer
		// argv[4] bank_no(0~9)
		// argv[5] address

		if (argc == 6)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			layer = strtoul(argv[3], NULL, 0);
			E_IM_DISP_OSD_SA_BANK_NO bank_no = (E_IM_DISP_OSD_SA_BANK_NO) strtoul(argv[4], NULL, 0);
			ULONG address = strtoul((kchar*) argv[5], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_dump_reg_osd_area_adata_addr(disp3, block); /* pgr0539 */
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Set_OSD_Area_Adata_Addr(block,
					(E_IM_DISP_SEL_LAYER) layer, bank_no, address); /* pgr0539 */
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_OSD_Area_Adata_Addr error=%08X\n", error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_dump_reg_osd_area_adata_addr(disp3, block);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 6\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetOSDAAdataAddr") == 0)
	{
		//Im_DISP_Get_OSD_Area_Adata_Addr

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "GetOSDAAdataAddr"
		// argv[2] Command select(0:Normal/1:area NULL)
		// argv[3] block(0/1)
		// argv[4] layer
		// argv[5] bank_no(0~9)

		if (argc == 6)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			layer = strtoul(argv[4], NULL, 0);
			E_IM_DISP_OSD_SA_BANK_NO bank_no = (E_IM_DISP_OSD_SA_BANK_NO) strtoul(argv[5], NULL, 0);
			ULONG address = 0;

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_OSD_Area_Adata_Addr(block,
						(E_IM_DISP_SEL_LAYER) layer, bank_no, NULL); /* pgr0539 */
			}
			else
			{
				error = Im_DISP_Get_OSD_Area_Adata_Addr(block,
						(E_IM_DISP_SEL_LAYER) layer, bank_no, &address); /* pgr0539 */
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_OSD_Area_Adata_Addr error=%08X\n", error));
			}
			else
			{
				ct_im_disp3_dump_reg_osd_area_adata_addr(disp3, block);

				Ddim_Print(("Layer = %02X\n", layer));
				if (bank_no < E_IM_DISP_OSD_SA_BANK_NO_1)
				{
					Ddim_Print(("bank%d input_address:0x%08X\n", bank_no, (kuint32)address));
				}
				else
				{
					Ddim_Print(("bank%d input_address:0x%08X\n",
							(bank_no - E_IM_DISP_OSD_SA_BANK_NO_0_3), (kuint32)address));
				}
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "SetOSDALfd") == 0)
	{
		//Im_DISP_Set_OSD_Lfd

		// argc=6
		// argv[0] "imdisp"
		// argv[1] "SetOSDALfd"
		// argv[2] block(0/1)
		// argv[3] layer
		// argv[4] bank_no(0~9)
		// argv[5] width

		if (argc == 6)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			layer = strtoul(argv[3], NULL, 0);
			kuint32 bank_no = strtoul(argv[4], NULL, 0);
			ULONG width = strtoul(argv[5], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_dump_reg_osd_lfd(disp3, block); /* pgr0539 */
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Set_OSD_Lfd(block, (E_IM_DISP_SEL_LAYER) layer, bank_no, width); /* pgr0539 */
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_OSD_Lfd error=%08X\n", error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_dump_reg_osd_lfd(disp3, block);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 6\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetOSDALfd") == 0)
	{
		//Im_DISP_Get_OSD_Lfd

		// argc=6
		// argv[0] "imdisp"
		// argv[1] "GetOSDAAdataAddr"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)
		// argv[4] layer
		// argv[5] bank_no(0~9)

		if (argc == 6)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			layer = strtoul(argv[4], NULL, 0);
			kuint32 bank_no = strtoul(argv[5], NULL, 0);
			ULONG width = 0;

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_OSD_Lfd(block, (E_IM_DISP_SEL_LAYER) layer, bank_no, NULL); /* pgr0539 */
			}
			else
			{
				error = Im_DISP_Get_OSD_Lfd(block, (E_IM_DISP_SEL_LAYER) layer, bank_no, &width); /* pgr0539 */
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_OSD_Lfd error=%08X\n", error));
			}
			else
			{
				ct_im_disp3_dump_reg_osd_lfd(disp3, block);

				Ddim_Print(("Layer = %02X\n", layer));
				Ddim_Print(("bank%d global_area_width:0x%08X\n", bank_no, (kuint32)width));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 6\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "SetOSDAdataLfd") == 0)
	{
		//Im_DISP_Set_OSD_Adata_Lfd

		// argc=6
		// argv[0] "imdisp"
		// argv[1] "SetOSDAdataLfd"
		// argv[2] block(0/1)
		// argv[3] layer
		// argv[4] bank_no(0~9)
		// argv[5] width

		if (argc == 6)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			layer = strtoul(argv[3], NULL, 0);
			kuint32 bank_no = strtoul(argv[4], NULL, 0);
			ULONG width = strtoul(argv[5], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_dump_reg_osd_adata_lfd(disp3, block); /* pgr0539 */
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Set_OSD_Adata_Lfd(block,
					(E_IM_DISP_SEL_LAYER) layer, bank_no, width); /* pgr0539 */
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_OSD_Adata_Lfd error=%08X\n", error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_dump_reg_osd_adata_lfd(disp3, block);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 6\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetOSDAdataLfd") == 0)
	{
		//Im_DISP_Get_OSD_Adata_Lfd

		// argc=6
		// argv[0] "imdisp"
		// argv[1] "GetOSDAAdataAddr"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)
		// argv[4] layer
		// argv[5] bank_no(0~9)

		if (argc == 6)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			layer = strtoul(argv[4], NULL, 0);
			kuint32 bank_no = strtoul(argv[5], NULL, 0);
			ULONG width = 0;

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_OSD_Adata_Lfd(block,
						(E_IM_DISP_SEL_LAYER) layer, bank_no, NULL); /* pgr0539 */
			}
			else
			{
				error = Im_DISP_Get_OSD_Adata_Lfd(block,
						(E_IM_DISP_SEL_LAYER) layer, bank_no, &width); /* pgr0539 */
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_OSD_Adata_Lfd error=%08X\n", error));
			}
			else
			{
				ct_im_disp3_dump_reg_osd_adata_lfd(disp3, block);

				Ddim_Print(("Layer = %02X\n", layer));
				Ddim_Print(("bank%d global_area_width:0x%08X\n", bank_no, (kuint32)width));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 6\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "SetOSDPos") == 0)
	{
		//Im_DISP_Set_OSD_Display_Position

		// argc=6
		// argv[0] "imdisp"
		// argv[1] "SetOSDPos"
		// argv[2] block(0/1)
		// argv[3] layer
		// argv[4] bank_no(0~9)
		// argv[5] position

		if (argc == 6)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			layer = strtoul(argv[3], NULL, 0);
			kuint32 bank_no = strtoul(argv[4], NULL, 0);
			U_IM_DISP_DSTA position;
			position.word = strtoul(argv[5], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_dump_reg_osd_pos(disp3, block); /* pgr0539 */
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Set_OSD_Display_Position(block,
					(E_IM_DISP_SEL_LAYER) layer, bank_no, position); /* pgr0539 */
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_OSD_Display_Position error=%08X\n", error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_dump_reg_osd_pos(disp3, block);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 6\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetOSDPos") == 0)
	{
		//Im_DISP_Get_OSD_Display_Position

		// argc=6
		// argv[0] "imdisp"
		// argv[1] "GetOSDPos"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)
		// argv[4] layer
		// argv[5] bank_no(0~9)

		if (argc == 6)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			layer = strtoul(argv[4], NULL, 0);
			kuint32 bank_no = strtoul(argv[5], NULL, 0);
			U_IM_DISP_DSTA position;
			memset(&position, 0, sizeof(U_IM_DISP_DSTA));

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_OSD_Display_Position(block,
						(E_IM_DISP_SEL_LAYER) layer, bank_no, NULL); /* pgr0539 */
			}
			else
			{
				error = Im_DISP_Get_OSD_Display_Position(block,
						(E_IM_DISP_SEL_LAYER) layer, bank_no, &position); /* pgr0539 */
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_OSD_Display_Position error=%08X\n", error));
			}
			else
			{
				ct_im_disp3_dump_reg_osd_pos(disp3, block);

				Ddim_Print(("Layer = %02X\n", layer));
				Ddim_Print(("bank%d DSH:0x%04X, DSV:0x%04X\n", bank_no, position.bit.DSH, position.bit.DSV));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 6\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "SetIPO") == 0)
	{
		//Im_DISP_Set_OSD_IPO

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "SetIPO"
		// argv[2] block(0/1)
		// argv[3] layer
		// argv[4] ipo

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			layer = strtoul(argv[3], NULL, 0);
			U_IM_DISP_GRIPO ipo;
			ipo.word = strtoul(argv[4], NULL, 0);
#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].GRCH[0].GRIPO = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].GRCH[0].GRIPO.word)); /* pgr0539 */
			Ddim_Print(("IO_DISP.MAIN[%d].GRCH[1].GRIPO = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].GRCH[1].GRIPO.word));
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Set_OSD_IPO(block, (E_IM_DISP_SEL_LAYER) layer, ipo); /* pgr0539 */
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_OSD_IPO error=%08X\n", error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[0].GRIPO = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].GRCH[0].GRIPO.word));
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[1].GRIPO = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].GRCH[1].GRIPO.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}

	}
	else if (strcmp((kchar*) argv[1], "GetIPO") == 0)
	{
		//Im_DISP_Get_OSD_IPO

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "GetIPO"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)
		// argv[4] layer

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			layer = strtoul(argv[4], NULL, 0);
			U_IM_DISP_GRIPO ipo;
			memset(&ipo, 0, sizeof(U_IM_DISP_GRIPO));
			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_OSD_IPO(block, (E_IM_DISP_SEL_LAYER) layer, NULL); /* pgr0539 */
			}
			else
			{
				error = Im_DISP_Get_OSD_IPO(block, (E_IM_DISP_SEL_LAYER) layer, &ipo); /* pgr0539 */
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_OSD_IPO error=%08X\n", error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[0].GRIPO = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].GRCH[0].GRIPO.word));
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[1].GRIPO = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].GRCH[1].GRIPO.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("Layer = %02X\n", layer));
				Ddim_Print(("ipo = 0x%08X\n", (kuint32)ipo.word));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "SetOSDAreaEn") == 0)
	{
		//Im_DISP_Set_OSD_Area_Enable

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "SetOSDAreaEn"
		// argv[2] block(0/1)
		// argv[3] layer
		// argv[4] area_enable

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			layer = strtoul(argv[3], NULL, 0);
			ULONG area_enable = strtoul(argv[4], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].GRCH[0].GRAREN = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].GRCH[0].GRAREN.word)); /* pgr0539 */
			Ddim_Print(("IO_DISP.MAIN[%d].GRCH[1].GRAREN = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].GRCH[1].GRAREN.word));
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Set_OSD_Area_Enable(block, (E_IM_DISP_SEL_LAYER) layer, area_enable); /* pgr0539 */
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_OSD_Area_Enable error=%08X\n", error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[0].GRAREN = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].GRCH[0].GRAREN.word));
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[1].GRAREN = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].GRCH[1].GRAREN.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetOSDAreaEn") == 0)
	{
		//Im_DISP_Get_OSD_Area_Enable

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "GetIPO"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)
		// argv[4] layer

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			layer = strtoul(argv[4], NULL, 0);
			ULONG area_enable = 0;

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_OSD_Area_Enable(block, (E_IM_DISP_SEL_LAYER) layer, NULL); /* pgr0539 */
			}
			else
			{
				error = Im_DISP_Get_OSD_Area_Enable(block,
						(E_IM_DISP_SEL_LAYER) layer, &area_enable); /* pgr0539 */
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_OSD_Area_Enable error=%08X\n", error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[0].GRAREN = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].GRCH[0].GRAREN.word));
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[1].GRAREN = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].GRCH[1].GRAREN.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("Layer = %02X\n", layer));
				Ddim_Print(("area_enable = 0x%08X\n", (kuint32)area_enable));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "SetOSDBlnk") == 0)
	{
		//Im_DISP_Set_OSD_Blink

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "SetOSDAreaEn"
		// argv[2] block(0/1)
		// argv[3] layer
		// argv[4] blink

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			layer = strtoul(argv[3], NULL, 0);
			ULONG blink = strtoul(argv[4], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].GRCH[0].GRBSL = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].GRCH[0].GRBSL.word)); /* pgr0539 */
			Ddim_Print(("IO_DISP.MAIN[%d].GRCH[1].GRBSL = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].GRCH[1].GRBSL.word));
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Set_OSD_Blink(block, (E_IM_DISP_SEL_LAYER) layer, blink); /* pgr0539 */
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_OSD_Blink error=%08X\n", error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[0].GRBSL = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].GRCH[0].GRBSL.word));
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[1].GRBSL = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].GRCH[1].GRBSL.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetOSDBlnk") == 0)
	{
		//Im_DISP_Get_OSD_Blink

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "GetOSDBlnk"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)
		// argv[4] layer

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			layer = strtoul(argv[4], NULL, 0);
			ULONG blink = 0;

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_OSD_Blink(block, (E_IM_DISP_SEL_LAYER) layer, NULL); /* pgr0539 */
			}
			else
			{
				error = Im_DISP_Get_OSD_Blink(block, (E_IM_DISP_SEL_LAYER) layer, &blink); /* pgr0539 */
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_OSD_Blink error=%08X\n", error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[0].GRBSL = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].GRCH[0].GRBSL.word));
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[1].GRBSL = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].GRCH[1].GRBSL.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("Layer = %02X\n", layer));
				Ddim_Print(("blink = 0x%08X\n", (kuint32)blink));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}

}
#endif /*CtImDisp_CO_DEBUG_DISP*/

/*
 * PUBLIC
 * */

CtImDisp2l *ct_im_disp2l_new(void)
{
	CtImDisp2l *self = (CtImDisp2l *) k_object_new_with_private(CT_TYPE_IM_DISP2L,sizeof(CtImDisp2lPrivate));
	return self;
}
