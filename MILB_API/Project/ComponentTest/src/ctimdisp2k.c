/*
 *ctimdisp2k.c
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
#include "ctimdisp2k.h"

K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(CtImDisp2k, ct_im_disp2k, IM_TYPE_DISP2_PARENT)
#define CT_IM_DISP2K_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), CtImDisp2kPrivate, CT_TYPE_IM_DISP2K))

struct _CtImDisp2kPrivate
{
	kpointer qwertyu;
};

/*
 * DECLS
 * */
#ifdef CtImDisp_CO_DEBUG_DISP
static void disp2kDoMain_od(ImDisp2Parent *parent, kint32 argc, char **argv);
#endif /*CtImDisp_CO_DEBUG_DISP*/

/*
 * IMPL
 * */
static void ct_im_disp2k_constructor(CtImDisp2k *self)
{
	//CtImDisp2kPrivate *priv = CT_IM_DISP2K_GET_PRIVATE(self);
#ifdef CtImDisp_CO_DEBUG_DISP
	ImDisp2Parent *parent = (ImDisp2Parent *)self;
	parent->doMainFunc = disp2kDoMain_od;
#endif /*CtImDisp_CO_DEBUG_DISP*/
}

static void ct_im_disp2k_destructor(CtImDisp2k *self)
{
}

#ifdef CtImDisp_CO_DEBUG_DISP
static void disp2kDoMain_od(ImDisp2Parent *parent, kint32 argc, char **argv)
{
	kint32 error = D_DDIM_OK;
	kuint32 layer = 0;
	ImDisp2Group *imDisp2Group = (ImDisp2Group *)im_disp2_parent_get_group(parent);
	kuchar *pImDispPclkCounter = im_disp2_group_get_pclk_counter(imDisp2Group);
	CtImDisp3 *disp3 = (CtImDisp3 *)im_disp2_group_get_disp3(imDisp2Group);

	if (strcmp((kchar*) argv[1], "SetFace") == 0)
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
	else if(strcmp((kchar*) argv[1], "SetOSDRefTiming") == 0)
	{
		//Im_DISP_Set_OSD_Parameter_Reflect_Timing

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "SetOSDRefTiming"
		// argv[2] block(0/1)
		// argv[3] layer
		// argv[4] timing

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			layer = strtoul(argv[3], NULL, 0);
			E_IM_DISP_RPGTMG timing = (E_IM_DISP_RPGTMG) strtoul(argv[4], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].GRCH[0].GRRPGCTL = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].GRCH[0].GRRPGCTL.word)); /* pgr0539 */
			Ddim_Print(("IO_DISP.MAIN[%d].GRCH[1].GRRPGCTL = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].GRCH[1].GRRPGCTL.word));
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Set_OSD_Parameter_Reflect_Timing(block,
					(E_IM_DISP_SEL_LAYER) layer, timing); /* pgr0539 */
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_OSD_Parameter_Reflect_Timing error=%08X\n", error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[0].GRRPGCTL = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].GRCH[0].GRRPGCTL.word));
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[1].GRRPGCTL = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].GRCH[1].GRRPGCTL.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetOSDRefTiming") == 0)
	{
		//Im_DISP_Get_OSD_Parameter_Reflect_Timing

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "GetOSDRefTiming"
		// argv[2] Command select(0:Normal/1:timing NULL)
		// argv[3] block(0/1)
		// argv[4] layer

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			layer = strtoul(argv[4], NULL, 0);
			E_IM_DISP_RPGTMG timing = E_IM_DISP_RPGTMG_VSYNC_FRAME_TOP;

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_OSD_Parameter_Reflect_Timing(block,
						(E_IM_DISP_SEL_LAYER) layer, NULL); /* pgr0539 */
			}
			else
			{
				error = Im_DISP_Get_OSD_Parameter_Reflect_Timing(block,
						(E_IM_DISP_SEL_LAYER) layer, &timing); /* pgr0539 */
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_OSD_Parameter_Reflect_Timing error=%08X\n", error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[0].GRRPGCTL = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].GRCH[0].GRRPGCTL.word));
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[1].GRRPGCTL = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].GRCH[1].GRRPGCTL.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("Layer = %02X\n", layer));
				Ddim_Print(("timing = %d\n", timing));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "SetOSDITrans") == 0)
	{
		//Im_DISP_Set_OSD_Input_Data_Transfer

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "SetOSDITrans"
		// argv[2] block(0/1)
		// argv[3] layer
		// argv[4] gridt

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			layer = strtoul(argv[3], NULL, 0);
			U_IM_DISP_GRIDT gridt;
			gridt.word = strtoul(argv[4], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].GRCH[0].GRIDT = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].GRCH[0].GRIDT.word)); /* pgr0539 */
			Ddim_Print(("IO_DISP.MAIN[%d].GRCH[1].GRIDT = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].GRCH[1].GRIDT.word));
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Set_OSD_Input_Data_Transfer(block, (E_IM_DISP_SEL_LAYER) layer, gridt); /* pgr0539 */
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_OSD_Input_Data_Transfer error=%08X\n", error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[0].GRIDT = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].GRCH[0].GRIDT.word));
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[1].GRIDT = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].GRCH[1].GRIDT.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 3\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetOSDITrans") == 0)
	{
		//Im_DISP_Get_OSD_Input_Data_Transfer

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "GetOSDITrans"
		// argv[2] Command select(0:Normal/1:timing NULL)
		// argv[3] block(0/1)
		// argv[4] layer

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			layer = strtoul(argv[4], NULL, 0);
			U_IM_DISP_GRIDT gridt;
			memset(&gridt, 0, sizeof(U_IM_DISP_GRIDT));

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_OSD_Input_Data_Transfer(block,
						(E_IM_DISP_SEL_LAYER) layer, NULL); /* pgr0539 */
			}
			else
			{
				error = Im_DISP_Get_OSD_Input_Data_Transfer(block,
						(E_IM_DISP_SEL_LAYER) layer, &gridt); /* pgr0539 */
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_OSD_Input_Data_Transfer error=%08X\n", error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[0].GRIDT = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].GRCH[0].GRIDT.word));
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[1].GRIDT = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].GRCH[1].GRIDT.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("Layer = %02X\n", layer));
				Ddim_Print(("[U_IM_DISP_GRIDT]\n"));
				Ddim_Print(("IFMT   = %d\n", gridt.bit.IFMT));
				Ddim_Print(("NBT    = %d\n", gridt.bit.NBT));
				Ddim_Print(("CACHE  = %d\n", gridt.bit.CACHE));
				Ddim_Print(("PROT   = %d\n", gridt.bit.PROT));
				Ddim_Print(("SLVSL  = %d\n", gridt.bit.SLVSL));
				Ddim_Print(("ASLVSL = %d\n", gridt.bit.ASLVSL));
				Ddim_Print(("IFBTMU = %d\n", gridt.bit.IFBTMU));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 3\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "SetOSDTrSize") == 0)
	{
		//Im_DISP_Set_OSD_Territory_Size

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "SetOSDTrSize"
		// argv[2] block(0/1)
		// argv[3] layer
		// argv[4] territorySize

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			layer = strtoul(argv[3], NULL, 0);
			U_IM_DISP_SIZE territorySize;
			territorySize.word = strtoul(argv[4], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].GRCH[0].GRTISIZE = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].GRCH[0].GRTISIZE.word)); /* pgr0539 */
			Ddim_Print(("IO_DISP.MAIN[%d].GRCH[1].GRTISIZE = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].GRCH[1].GRTISIZE.word));
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Set_OSD_Territory_Size(block,
					(E_IM_DISP_SEL_LAYER) layer, territorySize); /* pgr0539 */
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_OSD_Territory_Size error=%08X\n", error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[0].GRTISIZE = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].GRCH[0].GRTISIZE.word));
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[1].GRTISIZE = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].GRCH[1].GRTISIZE.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetOSDTrSize") == 0)
	{
		//Im_DISP_Get_OSD_Territory_Size

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "GetOSDTrSize"
		// argv[2] Command select(0:timing NULL/1:Normal)
		// argv[3] block(0/1)
		// argv[4] layer

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			layer = strtoul(argv[4], NULL, 0);
			U_IM_DISP_SIZE territorySize;
			memset(&territorySize, 0, sizeof(U_IM_DISP_SIZE));

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_OSD_Territory_Size(block, (E_IM_DISP_SEL_LAYER) layer, NULL); /* pgr0539 */
			}
			else
			{
				error = Im_DISP_Get_OSD_Territory_Size(block,
						(E_IM_DISP_SEL_LAYER) layer, &territorySize); /* pgr0539 */
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_OSD_Territory_Size error=%08X\n", error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[0].GRTISIZE = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].GRCH[0].GRTISIZE.word));
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[1].GRTISIZE = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].GRCH[1].GRTISIZE.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("Layer = %02X\n", layer));
				Ddim_Print(("[U_IM_DISP_SIZE]\n"));
				Ddim_Print(("width = 0x%04X, lines = 0x%04X\n",
						territorySize.size.width, territorySize.size.lines));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "SetOSDTrPos") == 0)
	{
		//Im_DISP_Set_OSD_Territory_Position

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "SetOSDTrSize"
		// argv[2] block(0/1)
		// argv[3] layer
		// argv[4] position

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			layer = strtoul(argv[3], NULL, 0);
			U_IM_DISP_DSTA position;
			position.word = strtoul(argv[4], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].GRCH[0].GRTDSTA = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].GRCH[0].GRTDSTA.word)); /* pgr0539 */
			Ddim_Print(("IO_DISP.MAIN[%d].GRCH[1].GRTDSTA = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].GRCH[1].GRTDSTA.word));
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Set_OSD_Territory_Position(block,
					(E_IM_DISP_SEL_LAYER) layer, position); /* pgr0539 */
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_OSD_Territory_Position error=%08X\n", error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[0].GRTDSTA = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].GRCH[0].GRTDSTA.word));
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[1].GRTDSTA = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].GRCH[1].GRTDSTA.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetOSDTrPos") == 0)
	{
		//Im_DISP_Get_OSD_Territory_Position

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "GetOSDTrPos"
		// argv[2] Command select(0:position NULL/1:Normal)
		// argv[3] block(0/1)
		// argv[4] layer

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			layer = strtoul(argv[4], NULL, 0);
			U_IM_DISP_DSTA position;
			memset(&position, 0, sizeof(U_IM_DISP_DSTA));

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_OSD_Territory_Position(block,
						(E_IM_DISP_SEL_LAYER) layer, NULL); /* pgr0539 */
			}
			else
			{
				error = Im_DISP_Get_OSD_Territory_Position(block,
						(E_IM_DISP_SEL_LAYER) layer, &position); /* pgr0539 */
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_OSD_Territory_Position error=%08X\n", error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[0].GRTDSTA = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].GRCH[0].GRTDSTA.word));
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[1].GRTDSTA = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].GRCH[1].GRTDSTA.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("[U_IM_DISP_DSTA]\n"));
				Ddim_Print(("DSH:0x%04X, DSV:0x%04X\n", position.bit.DSH, position.bit.DSV));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "SetOSDAreaSw") == 0)
	{
		//Im_DISP_Set_OSD_Area0_Switch

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "SetOSDAreaSw"
		// argv[2] block(0/1)
		// argv[3] layer
		// argv[4] area

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			layer = strtoul(argv[3], NULL, 0);
			E_IM_DISP_INPUT_DATA_AREA area = (E_IM_DISP_INPUT_DATA_AREA) strtoul(argv[4], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].GRCH[0].GRSCCTL = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].GRCH[0].GRSCCTL.word)); /* pgr0539 */
			Ddim_Print(("IO_DISP.MAIN[%d].GRCH[1].GRSCCTL = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].GRCH[1].GRSCCTL.word));
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Set_OSD_Area0_Switch(block, (E_IM_DISP_SEL_LAYER) layer, area); /* pgr0539 */
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_OSD_Area0_Switch error=%08X\n", error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[0].GRSCCTL = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].GRCH[0].GRSCCTL.word));
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[1].GRSCCTL = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].GRCH[1].GRSCCTL.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetOSDAreaSw") == 0)
	{
		//Im_DISP_Get_OSD_Area0_Switch

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "GetOSDAreaSw"
		// argv[2] Command select(0:area NULL/1:Normal)
		// argv[3] block(0/1)
		// argv[4] layer

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			layer = strtoul(argv[4], NULL, 0);
			E_IM_DISP_INPUT_DATA_AREA area = E_IM_DISP_INPUT_DATA_AREA_0;

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_OSD_Area0_Switch(block, (E_IM_DISP_SEL_LAYER) layer, NULL); /* pgr0539 */
			}
			else
			{
				error = Im_DISP_Get_OSD_Area0_Switch(block, (E_IM_DISP_SEL_LAYER) layer, &area); /* pgr0539 */
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_OSD_Area0_Switch error=%08X\n", error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[0].GRSCCTL = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].GRCH[0].GRSCCTL.word));
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[1].GRSCCTL = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].GRCH[1].GRSCCTL.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("area = %d\n", area));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((kchar*) argv[1], "GetOSDAreaMon") == 0)
	{
		//Im_DISP_Get_OSD_Area0_Monitor

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "GetOSDAreaMon"
		// argv[2] Command select(0:Normal/1:area NULL)
		// argv[3] block(0/1)
		// argv[4] layer

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			layer = strtoul(argv[4], NULL, 0);
			E_IM_DISP_INPUT_DATA_AREA area = E_IM_DISP_INPUT_DATA_AREA_0;

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_OSD_Area0_Monitor(block, (E_IM_DISP_SEL_LAYER) layer, NULL); /* pgr0539 */
			}
			else
			{
				error = Im_DISP_Get_OSD_Area0_Monitor(block, (E_IM_DISP_SEL_LAYER) layer, &area); /* pgr0539 */
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_OSD_Area0_Monitor error=%08X\n", error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[0].GRSCCTL = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].GRCH[0].GRSCCTL.word));
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[1].GRSCCTL = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].GRCH[1].GRSCCTL.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("Layer = %02X\n", layer));
				Ddim_Print(("area monitor:%d\n", area));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
#if 0
	else if(strcmp((kchar*)argv[1],"SetOSDEAR")==0)
	{
		//Im_DISP_Set_OSD_Error_Auto_Recovery
		if(argc == 4)
		{
			layer = strtoul(argv[2], NULL, 0);
			E_IM_DISP_ERCV auto_recovery = (E_IM_DISP_ERCV)strtoul(argv[3], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].GRCH[0].GRERCV = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].GRCH[0].GRERCV.word));
			Ddim_Print(("IO_DISP.MAIN[%d].GRCH[1].GRERCV = %08X\n",
					block, (kuint32)IO_DISP.MAIN[block].GRCH[1].GRERCV.word));
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Set_OSD_Error_Auto_Recovery((E_IM_DISP_SEL_LAYER)layer, auto_recovery); /* pgr0539 */
			if(error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_OSD_Error_Auto_Recovery error=%08X\n", error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[0].GRERCV = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].GRCH[0].GRERCV.word));
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[1].GRERCV = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].GRCH[1].GRERCV.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 3\n"));
		}
	}
#endif
#if 0
	else if(strcmp((kchar*)argv[1],"GetOSDEAR")==0)
	{
		//Im_DISP_Get_OSD_Error_Auto_Recovery
		if(argc == 4)
		{
			layer = strtoul(argv[2], NULL, 0);
			E_IM_DISP_ERCV auto_recovery = E_IM_DISP_ERCV_OFF;

			if(argv[3][0] == '0')
			{
				error = Im_DISP_Get_OSD_Error_Auto_Recovery((E_IM_DISP_SEL_LAYER)layer,
						&auto_recovery); /* pgr0539 */
			}
			else
			{
				error = Im_DISP_Get_OSD_Error_Auto_Recovery((E_IM_DISP_SEL_LAYER)layer, NULL); /* pgr0539 */
			}
			if(error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_OSD_Error_Auto_Recovery error=%08X\n", error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[0].GRERCV = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].GRCH[0].GRERCV.word));
				Ddim_Print(("IO_DISP.MAIN[%d].GRCH[1].GRERCV = %08X\n",
						block, (kuint32)IO_DISP.MAIN[block].GRCH[1].GRERCV.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("Layer = %02X\n", layer));
				Ddim_Print(("auto_recovery:%d\n", auto_recovery));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 3\n"));
		}
	}
#endif

}
#endif /*CtImDisp_CO_DEBUG_DISP*/

/*
 * PUBLIC
 * */

CtImDisp2k *ct_im_disp2k_new(void)
{
	CtImDisp2k *self = (CtImDisp2k *) k_object_new_with_private(CT_TYPE_IM_DISP2K,sizeof(CtImDisp2kPrivate));
	return self;
}

