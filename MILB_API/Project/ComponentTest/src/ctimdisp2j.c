/*
 *ctimdisp2j.c
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
#include "ctimdisp2j.h"

K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(CtImDisp2j, ct_im_disp2j, IM_TYPE_DISP2_PARENT)
#define CT_IM_DISP2J_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), CtImDisp2jPrivate, CT_TYPE_IM_DISP2J))

struct _CtImDisp2jPrivate
{
	kpointer qwertyu;
};

/*
 * DECLS
 * */
#ifdef CtImDisp_CO_DEBUG_DISP
static void disp2jDoMain_od(ImDisp2Parent *parent, kint32 argc, char **argv);
#endif /*CtImDisp_CO_DEBUG_DISP*/

/*
 * IMPL
 * */
static void ct_im_disp2j_constructor(CtImDisp2j *self)
{
	//CtImDisp2jPrivate *priv = CT_IM_DISP2J_GET_PRIVATE(self);
#ifdef CtImDisp_CO_DEBUG_DISP
	ImDisp2Parent *parent = (ImDisp2Parent *)self;
	parent->doMainFunc = disp2jDoMain_od;
#endif /*CtImDisp_CO_DEBUG_DISP*/
}

static void ct_im_disp2j_destructor(CtImDisp2j *self)
{
}

#ifdef CtImDisp_CO_DEBUG_DISP
static void disp2jDoMain_od(ImDisp2Parent *parent, kint32 argc, char **argv)
{
	kint i = 0;
	kint32 error = D_DDIM_OK;
	ImDisp2Group *imDisp2Group = (ImDisp2Group *)im_disp2_parent_get_group(parent);
	kuchar *pImDispPclkCounter = im_disp2_group_get_pclk_counter(imDisp2Group);
	CtImDisp3 *disp3 = (CtImDisp3 *)im_disp2_group_get_disp3(imDisp2Group);
	CtImDisp3a *disp3a = (CtImDisp3a *)im_disp2_group_get_disp3a(imDisp2Group);

	if (strcmp((kchar*) argv[1], "SetBarSz") == 0)
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
	else if (strcmp((kchar*) argv[1], "SetOutMax") == 0)
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
//			clipCal = ((T_IM_DISP_CTRL_OUTPUT *)(pOutputCtl + block))->clip_cal;
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

}
#endif /*CtImDisp_CO_DEBUG_DISP*/

/*
 * PUBLIC
 * */

CtImDisp2j *ct_im_disp2j_new(void)
{
	CtImDisp2j *self = (CtImDisp2j *) k_object_new_with_private(CT_TYPE_IM_DISP2J,sizeof(CtImDisp2jPrivate));
	return self;
}

