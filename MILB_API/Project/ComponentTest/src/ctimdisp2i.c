/*
 *ctimdisp2i.c
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
#include "ctimdisp2i.h"

K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(CtImDisp2i, ct_im_disp2i, IM_TYPE_DISP2_PARENT)
#define CT_IM_DISP2I_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), CtImDisp2iPrivate, CT_TYPE_IM_DISP2I))

struct _CtImDisp2iPrivate
{
	kpointer qwertyu;
};

/*
 * DECLS
 * */
#ifdef CtImDisp_CO_DEBUG_DISP
static void disp2iDoMain_od(ImDisp2Parent *parent, kint32 argc, char **argv);
#endif /*CtImDisp_CO_DEBUG_DISP*/

/*
 * IMPL
 * */
static void ct_im_disp2i_constructor(CtImDisp2i *self)
{
	//CtImDisp2iPrivate *priv = CT_IM_DISP2I_GET_PRIVATE(self);
#ifdef CtImDisp_CO_DEBUG_DISP
	ImDisp2Parent *parent = (ImDisp2Parent *)self;
	parent->doMainFunc = disp2iDoMain_od;
#endif /*CtImDisp_CO_DEBUG_DISP*/
}

static void ct_im_disp2i_destructor(CtImDisp2i *self)
{
}

#ifdef CtImDisp_CO_DEBUG_DISP
static void disp2iDoMain_od(ImDisp2Parent *parent, kint32 argc, char **argv)
{
	kint i = 0;
	kint32 error = D_DDIM_OK;
	ImDisp2Group *imDisp2Group = (ImDisp2Group *)im_disp2_parent_get_group(parent);
	kuchar *pImDispPclkCounter = im_disp2_group_get_pclk_counter(imDisp2Group);
	CtImDisp3 *disp3 = (CtImDisp3 *)im_disp2_group_get_disp3(imDisp2Group);
	CtImDisp3a *disp3a = (CtImDisp3a *)im_disp2_group_get_disp3a(imDisp2Group);

	if (strcmp((kchar*) argv[1], "SetOutMax") == 0)
	{
		//Im_DISP_Set_Output_Matrix

		// argc=8
		// argv[0] "imdisp"
		// argv[1] "SetOutMax"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)
		// argv[4] kind(2:NG/0,1:OK)
		// argv[5] matrix[0](dword)
		// argv[6] matrix[1](dword)
		// argv[7] matrix[2](dword)

		if (argc == 8)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			E_IM_DISP_MATRIX_KIND kind = strtoul(argv[4], NULL, 0);
			U_IM_DISP_YR_MATRIX_COEFFICIENT matrix[D_IM_DISP_MATRIX_SIZE];
			matrix[0].dword = strtoull(argv[5], NULL, 0);
			matrix[1].dword = strtoull(argv[6], NULL, 0);
			matrix[2].dword = strtoull(argv[7], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_dump_reg_out_matrix(disp3, block); /* pgr0539 */
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			if (argv[2][0] == '0')
			{
				error = Im_DISP_Set_Output_Matrix(block, kind, NULL); /* pgr0539 */
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Set_Output_Matrix(block, kind, matrix); /* pgr0539 */
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_Output_Matrix error=%08X\n",error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_dump_reg_out_matrix(disp3, block);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 8\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetOutMax") == 0)
	{
		//Im_DISP_Get_Output_Matrix

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "GetOutMax"
		// argv[2] Command select(0:Normal/1:NULL)
		// argv[3] block(0/1)
		// argv[4] kind(2:NG/0,1:OK)

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			E_IM_DISP_MATRIX_KIND kind = (E_IM_DISP_MATRIX_KIND) strtoul(argv[4], NULL, 0);
			U_IM_DISP_YR_MATRIX_COEFFICIENT matrix[D_IM_DISP_MATRIX_SIZE];
			for (i = 0; i < D_IM_DISP_MATRIX_SIZE; i++)
			{
				matrix[i].dword = 0;
			}

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Output_Matrix(block, kind, NULL); /* pgr0539 */
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Get_Output_Matrix(block, kind, matrix); /* pgr0539 */
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Output_Matrix error=%08X\n",error));
			}
			else
			{
				ct_im_disp3_dump_reg_out_matrix(disp3, block);
				ct_im_disp3_print_param_out_matrix(matrix);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "SetClip") == 0)
	{
		//Im_DISP_Set_Clip

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "SetClip"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)
		// argv[4] clipCal(0:Normal/1~6:NG)

		if (argc == 5)
		{
			ImDisp2Group *disp2Group = (ImDisp2Group *)im_disp2_parent_get_group(parent);
			// CtImDisp4 *ctImDisp4 = (CtImDisp4 *)im_disp2_group_get_disp4(disp2Group);

			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			T_IM_DISP_CLIP_CAL clipCal;
			T_IM_DISP_CTRL_OUTPUT *pOutputCtl = im_disp2_group_get_output_ctl(disp2Group);
			memcpy(&clipCal, &(pOutputCtl[block].clip_cal), sizeof(memcpy));

			if (argv[4][0] == '0')
			{
				// OK root
			}
			else if (argv[4][0] == '1')
			{
				// (clipCal->y_cal.yofs < 0)
				clipCal.y_cal.yofs = -1;
			}
			else if (argv[4][0] == '2')
			{
				// (clipCal->y_cal.yofs > 8191)
				clipCal.y_cal.yofs = 8192;
			}
			else if (argv[4][0] == '3')
			{
				// (clipCal->cb_cal.cofs < -4096)
				clipCal.cb_cal.cofs = -4097;
			}
			else if (argv[4][0] == '4')
			{
				// (clipCal->cb_cal.cofs > 4095)
				clipCal.cb_cal.cofs = 4096;
			}
			else if (argv[4][0] == '5')
			{
				// (clipCal->cr_cal.cofs < -4096)
				clipCal.cr_cal.cofs = 4096;
			}
			else if (argv[4][0] == '6')
			{
				// (clipCal->cr_cal.cofs > 4095)
				clipCal.cr_cal.cofs = 4096;
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_dump_reg_clip(disp3, block);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			if (argv[2][0] == '0')
			{
				error = Im_DISP_Set_Clip(block, NULL);
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Set_Clip(block, &clipCal);
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_Clip error=%08X\n",error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_dump_reg_clip(disp3, block);
			}
		}
		else if (argc == 2)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			error = Im_DISP_Set_Clip(block, NULL); /* pgr0539 */
			Ddim_Print(("Im_DISP_Set_Clip error=%08X\n",error));
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5 or 2\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetClip") == 0)
	{
		//Im_DISP_Get_Clip

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetClip"
		// argv[2] Command select(0:Normal/1:NULL)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			T_IM_DISP_CLIP_CAL clipCal;
			memset(&clipCal, 0, sizeof(T_IM_DISP_CLIP_CAL));

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Clip(block, NULL); /* pgr0539 */
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Get_Clip(block, &clipCal); /* pgr0539 */
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Clip error=%08X\n",error));
			}
			else
			{
				ct_im_disp3_dump_reg_clip(disp3, block);
				ct_im_disp3_print_param_clip(clipCal);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 2\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "SetOutOd") == 0)
	{
		//Im_DISP_Set_Output_Order

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "SetOutOd"
		// argv[2] block(0/1)
		// argv[3] doctl0

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			U_IM_DISP_DOCTL0 doctl0;
			doctl0.word = strtoul(argv[3], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.DOCTL0 = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].DCORE.DOCTL0.word)); /* pgr0539 */
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Im_DISP_Set_Output_Order(block, doctl0);

			Ddim_Print(("------- After Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.DOCTL0 = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].DCORE.DOCTL0.word));
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetOutOd") == 0)
	{
		//Im_DISP_Get_Output_Order

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetOutOd"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			U_IM_DISP_DOCTL0 doctl0;
			memset(&doctl0, 0, sizeof(U_IM_DISP_DOCTL0));
			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Output_Order(block, NULL); /* pgr0539 */
			}
			if (argv[2][0] == '1')
			{
				error = Im_DISP_Get_Output_Order(block, &doctl0); /* pgr0539 */
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Output_Order error=%08X\n",error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.DOCTL0 = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].DCORE.DOCTL0.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("[U_IM_DISP_DOCTL0]\n"));
				Ddim_Print(("DTO1=%d, DTO2=%d, DTO3=%d, DTO4=%d, DTO5=%d, DTO6=%d\n",
						doctl0.bit.DTO1, doctl0.bit.DTO2, doctl0.bit.DTO3,
						doctl0.bit.DTO4, doctl0.bit.DTO5, doctl0.bit.DTO6 ));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 2\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "SetGrid") == 0)
	{
		//Im_DISP_Set_Grid

		// argc=11
		// argv[0] "imdisp"
		// argv[1] "SetGrid"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)
		// argv[4] ghdsta
		// argv[5] gvdsta
		// argv[6] glength
		// argv[7] gwidth
		// argv[8] gitvl
		// argv[9] gnum
		// argv[10] gdctl

		if (argc == 11)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			T_IM_DISP_GRID grid;
			grid.ghdsta.word = strtoul(argv[4], NULL, 0);
			grid.gvdsta.word = strtoul(argv[5], NULL, 0);
			grid.glength.word = strtoul(argv[6], NULL, 0);
			grid.gwidth.word = strtoul(argv[7], NULL, 0);
			grid.gitvl.word = strtoul(argv[8], NULL, 0);
			grid.gnum.word = strtoul(argv[9], NULL, 0);
			grid.gdctl.word = strtoul(argv[10], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3a_dump_reg_grid(disp3a, block); /* pgr0539 */
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			if (argv[2][0] == '0')
			{
				error = Im_DISP_Set_Grid(block, NULL);
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Set_Grid(block, &grid);
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_Grid error=%08X\n", error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3a_dump_reg_grid(disp3a, block);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 11\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetGrid") == 0)
	{
		//Im_DISP_Get_Grid

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetGrid"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			T_IM_DISP_GRID grid;
			memset(&grid, 0, sizeof(T_IM_DISP_GRID));

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Grid(block, NULL); /* pgr0539 */
			}
			if (argv[2][0] == '1')
			{
				error = Im_DISP_Get_Grid(block, &grid); /* pgr0539 */
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Grid error=%08X\n",error));
			}
			else
			{
				ct_im_disp3a_dump_reg_grid(disp3a, block);
				ct_im_disp3a_print_param_grid(grid);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 2\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "SetGridEn") == 0)
	{
		//Im_DISP_Set_Grid_Enable

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "SetGridEn"
		// argv[2] block(0/1)
		// argv[3] gdis

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			E_IM_DISP_GDISPEN gdispen = (E_IM_DISP_GDISPEN) strtoul(argv[3], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.GDISPEN = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].DCORE.GDISPEN.word)); /* pgr0539 */
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Im_DISP_Set_Grid_Enable(block, gdispen); /* pgr0539 */

			Ddim_Print(("------- After Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.GDISPEN = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].DCORE.GDISPEN.word));
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetGridEn") == 0)
	{
		//Im_DISP_Get_Grid_Enable

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetGridEn"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			E_IM_DISP_GDISPEN gdispen = E_IM_DISP_GDISPEN_NOT_DISPLAY;

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Grid_Enable(block, NULL); /* pgr0539 */
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Get_Grid_Enable(block, &gdispen); /* pgr0539 */
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Grid_Enable error=%08X\n", error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.GDISPEN = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].DCORE.GDISPEN.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("Grid enable = %d\n", gdispen));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "SetFace") == 0)
	{
		//Im_DISP_Set_Face_Frame

		// argc=10
		// argv[0] "imdisp"
		// argv[1] "SetFace"
		// argv[2] block(0/1)
		// argv[3] frame_count
		// argv[4] ffdsta
		// argv[5] ffsize
		// argv[6] ffwidth
		// argv[7] ffclr
		// argv[8] ffden(unsigned long long)
		// argv[9] msff

		if (argc == 10)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);

			T_IM_DISP_FACE_FRAME_PARAM ff_data[D_IM_DISP_FACE_FRAME_COUNT] = {
			{ { 0x00000000 }, { 0x00080008 }, { 0x00020002 }, { 0x00000000 } },// [0]
			{ { 0x3FFEFFFE }, { 0x3FFEFFFE }, { 0x003E003E }, { 0x00FFFFFF } },	// [1]
			{ { 0x01000100 }, { 0x00100010 }, { 0x00020002 }, { 0x000000FF } },	// [2]
			{ { 0x02000200 }, { 0x00200020 }, { 0x00040004 }, { 0x0000FF00 } },	// [3]
			{ { 0x03000300 }, { 0x00300030 }, { 0x00060006 }, { 0x00FF0000 } },	// [4]
			{ { 0x04000400 }, { 0x00400040 }, { 0x00080008 }, { 0x00000080 } },	// [5]
			{ { 0x05000500 }, { 0x00500050 }, { 0x000A000A }, { 0x00008000 } },	// [6]
			{ { 0x06000600 }, { 0x00600060 }, { 0x000C000C }, { 0x00800000 } },	// [7]
			{ { 0x07000700 }, { 0x00700070 }, { 0x000E000E }, { 0x00808080 } },	// [8]
			{ { 0x08000800 }, { 0x00800080 }, { 0x00100010 }, { 0x00000040 } },	// [9]
			{ { 0x09000900 }, { 0x00900090 }, { 0x00120012 }, { 0x00004000 } },	// [10]
			{ { 0x0A000A00 }, { 0x00A000A0 }, { 0x00140014 }, { 0x00400000 } },	// [11]
			{ { 0x0B000B00 }, { 0x00B000B0 }, { 0x00160016 }, { 0x00404040 } },	// [12]
			{ { 0x0C000C00 }, { 0x00C000C0 }, { 0x00180018 }, { 0x00000010 } },	// [13]
			{ { 0x0D000D00 }, { 0x00D000D0 }, { 0x001A001A }, { 0x00001000 } },	// [14]
			{ { 0x0E000E00 }, { 0x00E000E0 }, { 0x001C001C }, { 0x00100000 } },	// [15]
			{ { 0x00000000 }, { 0x00080008 }, { 0x00020002 }, { 0x00000000 } },	// [16]
			{ { 0x3FFEFFFE }, { 0x3FFEFFFE }, { 0x003E003E }, { 0x00FFFFFF } },	// [17]
			{ { 0x01000100 }, { 0x00100010 }, { 0x00020002 }, { 0x000000FF } },	// [18]
			{ { 0x02000200 }, { 0x00200020 }, { 0x00040004 }, { 0x0000FF00 } },	// [19]
			{ { 0x03000300 }, { 0x00300030 }, { 0x00060006 }, { 0x00FF0000 } },	// [20]
			{ { 0x04000400 }, { 0x00400040 }, { 0x00080008 }, { 0x00000080 } },	// [21]
			{ { 0x05000500 }, { 0x00500050 }, { 0x000A000A }, { 0x00008000 } },	// [22]
			{ { 0x06000600 }, { 0x00600060 }, { 0x000C000C }, { 0x00800000 } },	// [23]
			{ { 0x07000700 }, { 0x00700070 }, { 0x000E000E }, { 0x00808080 } },	// [24]
			{ { 0x08000800 }, { 0x00800080 }, { 0x00100010 }, { 0x00000040 } },	// [25]
			{ { 0x09000900 }, { 0x00900090 }, { 0x00120012 }, { 0x00004000 } },	// [26]
			{ { 0x0A000A00 }, { 0x00A000A0 }, { 0x00140014 }, { 0x00400000 } },	// [27]
			{ { 0x0B000B00 }, { 0x00B000B0 }, { 0x00160016 }, { 0x00404040 } },	// [28]
			{ { 0x0C000C00 }, { 0x00C000C0 }, { 0x00180018 }, { 0x00000010 } },	// [29]
			{ { 0x0D000D00 }, { 0x00D000D0 }, { 0x001A001A }, { 0x00001000 } },	// [30]
			{ { 0x0E000E00 }, { 0x00E000E0 }, { 0x001C001C }, { 0x00100000 } },	// [31]
			{ { 0x00000000 }, { 0x00080008 }, { 0x00020002 }, { 0x00000000 } },	// [32]
			{ { 0x3FFEFFFE }, { 0x3FFEFFFE }, { 0x003E003E }, { 0x00FFFFFF } },	// [33]
			{ { 0x01000100 }, { 0x00100010 }, { 0x00020002 }, { 0x000000FF } },	// [34]
			{ { 0x02000200 }, { 0x00200020 }, { 0x00040004 }, { 0x0000FF00 } },	// [35]
			{ { 0x03000300 }, { 0x00300030 }, { 0x00060006 }, { 0x00FF0000 } },	// [36]
			{ { 0x04000400 }, { 0x00400040 }, { 0x00080008 }, { 0x00000080 } },	// [37]
			{ { 0x05000500 }, { 0x00500050 }, { 0x000A000A }, { 0x00008000 } },	// [38]
			{ { 0x06000600 }, { 0x00600060 }, { 0x000C000C }, { 0x00800000 } },	// [39]
			{ { 0x07000700 }, { 0x00700070 }, { 0x000E000E }, { 0x00808080 } },	// [40]
			{ { 0x08000800 }, { 0x00800080 }, { 0x00100010 }, { 0x00000040 } } 	// [41]
			};

			T_IM_DISP_FACE_FRAME face;
			memcpy(face.param, ff_data, (sizeof(T_IM_DISP_FACE_FRAME_PARAM) * D_IM_DISP_FACE_FRAME_COUNT));
			face.ffden = strtoull(argv[8], NULL, 0);
			face.msff = strtoul(argv[9], NULL, 0);
			kuint32 frame_count = strtoul(argv[3], NULL, 0);
			face.param[0].ffdsta.word = strtoul(argv[4], NULL, 0);
			face.param[0].ffsize.word = strtoul(argv[5], NULL, 0);
			face.param[0].ffwidth.word = strtoul(argv[6], NULL, 0);
			face.param[0].ffclr.word = strtoul(argv[7], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_dump_reg_face(disp3, block); /* pgr0539 */
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Set_Face_Frame(block, frame_count, &face); /* pgr0539 */
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_Face_Frame error=%08X\n", error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_dump_reg_face(disp3, block);
			}
		}
		else if (argc == 3)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			error = Im_DISP_Set_Face_Frame(block, 16, NULL); /* pgr0539 */
			Ddim_Print(("Im_DISP_Set_Face_Frame error=%08X\n", error));
		}
		else
		{
			Ddim_Print(("Parameter num shold be 10 or 3\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetFace") == 0)
	{
		//Im_DISP_Get_Face_Frame

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetFace"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			T_IM_DISP_FACE_FRAME face;
			memset(&face, 0, sizeof(T_IM_DISP_FACE_FRAME));

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Face_Frame(block, NULL); /* pgr0539 */
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Get_Face_Frame(block, &face); /* pgr0539 */
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Face_Frame error=%08X\n",error));
			}
			else
			{
				ct_im_disp3_dump_reg_face(disp3, block);
				ct_im_disp3_print_param_face(face);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "SetFaceEn") == 0)
	{
		//Im_DISP_Set_Face_Frame_Enable

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "SetFaceEn"
		// argv[2] block(0/1)
		// argv[3] ffden(unsigned long long)
		// argv[4] msff

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			UINT64 ffden = (UINT64) strtoull(argv[3], NULL, 0);
			BYTE msff = strtoul(argv[4], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.FFDISPEN = %llX\n",
					block, (LLONG)IO_DISP.MAIN[block].DCORE.FFDISPEN.dword)); /* pgr0539 */
			Ddim_Print(("IO_DISP.MAIN[%d].DCORE.FFDO     = %llX\n",
					block, (LLONG)IO_DISP.MAIN[block].DCORE.FFDO.word));
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Set_Face_Frame_Enable(block, ffden, msff); /* pgr0539 */
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_Face_Frame_Enable error=%08X\n",error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.FFDISPEN = %llX\n",
						block, (LLONG)IO_DISP.MAIN[block].DCORE.FFDISPEN.dword));
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.FFDO     = %llX\n",
						block, (LLONG)IO_DISP.MAIN[block].DCORE.FFDO.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetFaceEn") == 0)
	{
		//Im_DISP_Get_Face_Frame_Enable

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetFaceEn"
		// argv[2] Command select(0:both NULL/1:msff NULL/2:ffden NULL/3:Normal)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			UINT64 ffden = 0;
			BYTE msff = 0;

			switch (argv[2][0])
			{
			case '0':
				error = Im_DISP_Get_Face_Frame_Enable(block, NULL, NULL); /* pgr0539 */
				break;
			case '1':
				error = Im_DISP_Get_Face_Frame_Enable(block, NULL, &msff); /* pgr0539 */
				break;
			case '2':
				error = Im_DISP_Get_Face_Frame_Enable(block, &ffden, NULL); /* pgr0539 */
				break;
			default:
				error = Im_DISP_Get_Face_Frame_Enable(block, &ffden, &msff); /* pgr0539 */
				break;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Face_Frame_Enable error=%08X\n", error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.FFDISPEN = %llX\n",
						block, (LLONG)IO_DISP.MAIN[block].DCORE.FFDISPEN.dword));
				Ddim_Print(("IO_DISP.MAIN[%d].DCORE.FFDO     = %llX\n",
						block, (LLONG)IO_DISP.MAIN[block].DCORE.FFDO.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("[T_IM_DISP_FACE_FRAME]\n"));
				Ddim_Print(("Face frame ffden = %llX\n", ffden));
				Ddim_Print(("Face frame msff  = %d\n", msff));
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

CtImDisp2i *ct_im_disp2i_new(void)
{
	CtImDisp2i *self = (CtImDisp2i *) k_object_new_with_private(CT_TYPE_IM_DISP2I,sizeof(CtImDisp2iPrivate));
	return self;
}

