/*
 *ctimdisp2o.c
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-09
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
#include "ct_im_disp_define.h"//CO_IO_DISP_DEFINE

#include "ctimdisp4.h"//variable
#include "ctimdisp3.h"//static func
#include "ctimdisp3a.h"

#include "imdisp2group.h"
#include "ctimdisp2o.h"

K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(CtImDisp2o, ct_im_disp2o, IM_TYPE_DISP2_PARENT)
#define CT_IM_DISP2O_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), CtImDisp2oPrivate, CT_TYPE_IM_DISP2O))

typedef enum {
	CtImDisp2o_LCD_OSD_0 = 0,			/**< OSD-0.		*/
	CtImDisp2o_LCD_OSD_1,				/**< OSD-1.		*/
	CtImDisp2o_LCD_OSD_END
} CtImDisp2oELcdOsdSel;

struct _CtImDisp2oPrivate
{
	kpointer qwertyu;
	T_IM_DISP_CTRL_OSD_LAYER gLcdDispTblOsdCtrl[CtImDisp4_LCD_DISP_SEL_END][CtImDisp2o_LCD_OSD_END];
};

/*
 * DECLS
 * */
#ifdef CtImDisp_CO_DEBUG_DISP
static void disp2oDoMain_od(ImDisp2Parent *parent, kint32 argc, char **argv);
#endif /*CtImDisp_CO_DEBUG_DISP*/
static void initTblOsdCtrl(CtImDisp2o *self);

/*
 * IMPL
 * */
static void ct_im_disp2o_constructor(CtImDisp2o *self)
{
	CtImDisp2oPrivate *priv = CT_IM_DISP2O_GET_PRIVATE(self);
#ifdef CtImDisp_CO_DEBUG_DISP
	ImDisp2Parent *parent = (ImDisp2Parent *)self;
	parent->doMainFunc = disp2oDoMain_od;
#endif /*CtImDisp_CO_DEBUG_DISP*/
	self->privCtImDisp2o =priv;
	initTblOsdCtrl(self);
}

static void ct_im_disp2o_destructor(CtImDisp2o *self)
{
}

#ifdef CtImDisp_CO_DEBUG_DISP
static void disp2oDoMain_od(ImDisp2Parent *parent, kint32 argc, char **argv)
{
	kint32 error = D_DDIM_OK;
	kuint32 layer = 0;
	CtImDisp2o *self = (CtImDisp2o *)parent;
	CtImDisp2oPrivate *priv = self->privCtImDisp2o;
	ImDisp2Group *imDisp2Group = (ImDisp2Group *)im_disp2_parent_get_group(parent);
	CtImDisp3a *disp3a = (CtImDisp3a *)im_disp2_group_get_disp3a(imDisp2Group);

	if (strcmp((kchar*) argv[1], "Ctrl_OSDs") == 0)
	{
		//Im_DISP_Ctrl_OSD_Layer

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "Ctrl_OSDs"
		// argv[2] Command select(0:both NULL, 1:first NULL, 2:second NULL, 3:Normal)
		// argv[3] block
		// argv[4] layer
		// argv[5] grrpgctl(0:FRAME_TOP/1:VSYNC)
		// argv[6] parameter

		if (argc == 7)
		{
			E_IM_DISP_SEL block = strtoul(argv[3], NULL, 0);
			layer = strtoul(argv[4], NULL, 0);
			kuint32 layer_idx = 0;
			if (layer == 8)
			{
				layer_idx = 1;
			}
#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			if ((layer == E_IM_DISP_SEL_LAYER_OSD_0) || (layer == E_IM_DISP_SEL_LAYER_OSD_1))
			{
				Ddim_Print(("------- Before Setting -------\n"));
				ct_im_disp3a_dump_regiser(disp3a, (E_IM_DISP_SEL_LAYER) layer, block); /* pgr0539 */
			}
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			E_IM_DISP_RPGTMG* pGrrpgctl = NULL;
			E_IM_DISP_RPGTMG grrpgctl = (E_IM_DISP_SEL) strtoul(argv[5], NULL, 0);

			T_IM_DISP_CTRL_OSD_LAYER* pOsdCtrl = NULL;
			T_IM_DISP_CTRL_OSD_LAYER osdCtrl;
			memcpy(&osdCtrl, (void *) &priv->gLcdDispTblOsdCtrl[block][layer_idx],
					sizeof(T_IM_DISP_CTRL_OSD_LAYER)); /* pgr0539 */

			// Check in Im_DISP_Ctrl_OSD_Layer
			switch (argv[2][0])
			{
			case CtImDisp3_D_CT_IM_DISP_NO_PARA:			// both NULL
				break;
			case CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY:	// first NULL
				pGrrpgctl = (void *) &grrpgctl;
				break;
			case CtImDisp3_D_CT_IM_DISP_SECOND_PARA_ONLY:	// second NULL
				pOsdCtrl = (void *) &osdCtrl;
				break;
			case CtImDisp3_D_CT_IM_DISP_BOTH_PARA:		// Normal
				pGrrpgctl = (void *) &grrpgctl;
				pOsdCtrl = (void *) &osdCtrl;
				break;
			default:
				Ddim_Print(("Command parameter error\n"));
				break;
			}

			// Check in im_disp_param_check_gridt
			if (strcmp((kchar*) argv[6], "1") == 0)
			{
				osdCtrl.gridt.bit.IFMT = 5;
			}
			// Check in im_disp_param_check_grtisize
			else if (strcmp((kchar*) argv[6], "2") == 0)
			{
				osdCtrl.grtisize.word = 0x00080009;
			}
			else if (strcmp((kchar*) argv[6], "3") == 0)
			{
				osdCtrl.grtisize.word = 0x00080006;
			}
			else if (strcmp((kchar*) argv[6], "4") == 0)
			{
				osdCtrl.grtisize.word = 0x00090008;
			}
			else if (strcmp((kchar*) argv[6], "5") == 0)
			{
				osdCtrl.grtisize.word = 0x00060008;
			}
			// im_disp_param_check_grtdsta
			else if (strcmp((kchar*) argv[6], "6") == 0)
			{
				osdCtrl.grtdsta.word = 0x00000001;
			}
			else if (strcmp((kchar*) argv[6], "7") == 0)
			{
				osdCtrl.grtdsta.word = 0x00010000;
			}
			// im_disp_param_check_gripo
			else if (strcmp((kchar*) argv[6], "8") == 0)
			{
				osdCtrl.gripo.word = 0x03020101;
			}
			else if (strcmp((kchar*) argv[6], "9") == 0)
			{
				osdCtrl.gripo.word = 0x03010201;
			}
			else if (strcmp((kchar*) argv[6], "10") == 0)
			{
				osdCtrl.gripo.word = 0x01030201;
			}
			else if (strcmp((kchar*) argv[6], "11") == 0)
			{
				osdCtrl.gripo.word = 0x03020201;
			}
			else if (strcmp((kchar*) argv[6], "12") == 0)
			{
				osdCtrl.gripo.word = 0x02030201;
			}
			else if (strcmp((kchar*) argv[6], "13") == 0)
			{
				osdCtrl.gripo.word = 0x03030201;
			}
			// im_disp_param_check_grisize
			else if (strcmp((kchar*) argv[6], "14") == 0)
			{
				osdCtrl.grisize[0].word = 0x0008000A;
			}
			else if (strcmp((kchar*) argv[6], "15") == 0)
			{
				osdCtrl.grisize[0].word = 0x0008000B;
			}
			else if (strcmp((kchar*) argv[6], "16") == 0)
			{
				osdCtrl.grisize[1].word = 0x00080000;
			}
			else if (strcmp((kchar*) argv[6], "17") == 0)
			{
				osdCtrl.grisize[8].word = 0x00090008;
			}
			else if (strcmp((kchar*) argv[6], "18") == 0)
			{
				osdCtrl.grisize[9].word = 0x00060008;
			}
			// im_disp_param_check_ctrl_osd_layer
			else if (strcmp((kchar*) argv[6], "19") == 0)
			{
				osdCtrl.grtisize.word = 0x00080008;
				osdCtrl.grisize[0].word = 0x00080008;
				osdCtrl.grdsta[0].word = 0x00000002;
			}
			else if (strcmp((kchar*) argv[6], "20") == 0)
			{
				osdCtrl.grtisize.word = 0x00080008;
				osdCtrl.grisize[9].word = 0x00080008;
				osdCtrl.grdsta[9].word = 0x00020000;
			}
			// im_disp_param_check_grhga
			else if (strcmp((kchar*) argv[6], "21") == 0)
			{
				osdCtrl.grhga[0] = 0;
			}
			else if (strcmp((kchar*) argv[6], "22") == 0)
			{
				osdCtrl.grhga[8] = 0xFFF9;
			}
			else if (strcmp((kchar*) argv[6], "23") == 0)
			{
				osdCtrl.grhga[9] = 0x00000001;
			}
			else if (strcmp((kchar*) argv[6], "24") == 0)
			{
				osdCtrl.grdsta[5].word = 0x00000002;
			}
			else if (strcmp((kchar*) argv[6], "25") == 0)
			{
				osdCtrl.grdsta[0].word = 0x00010000;
			}
			// im_disp_param_check_grdsta
			else if (strcmp((kchar*) argv[6], "26") == 0)
			{
				osdCtrl.grdsta[0].word = 0x00000001;
				osdCtrl.grdsta[1].word = 0x00000000;
				osdCtrl.grdsta[2].word = 0x00000000;
				osdCtrl.grdsta[3].word = 0x00000000;
				osdCtrl.grdsta[4].word = 0x00000000;
				osdCtrl.grdsta[5].word = 0x00000000;
				osdCtrl.grdsta[6].word = 0x00000000;
				osdCtrl.grdsta[7].word = 0x00000000;
				osdCtrl.grdsta[8].word = 0x00000000;
				osdCtrl.grdsta[9].word = 0x00000000;
			}
			else if (strcmp((kchar*) argv[6], "27") == 0)
			{
				osdCtrl.grdsta[0].word = 0x00000000;
				osdCtrl.grdsta[1].word = 0x00000000;
				osdCtrl.grdsta[2].word = 0x00000000;
				osdCtrl.grdsta[3].word = 0x00000000;
				osdCtrl.grdsta[4].word = 0x00000001;
				osdCtrl.grdsta[5].word = 0x00000000;
				osdCtrl.grdsta[6].word = 0x00000000;
				osdCtrl.grdsta[7].word = 0x00000000;
				osdCtrl.grdsta[8].word = 0x00000000;
				osdCtrl.grdsta[9].word = 0x00000000;
			}
			else if (strcmp((kchar*) argv[6], "28") == 0)
			{
				osdCtrl.grdsta[0].word = 0x00000000;
				osdCtrl.grdsta[1].word = 0x00000000;
				osdCtrl.grdsta[2].word = 0x00000000;
				osdCtrl.grdsta[3].word = 0x00000000;
				osdCtrl.grdsta[4].word = 0x00000000;
				osdCtrl.grdsta[5].word = 0x00000000;
				osdCtrl.grdsta[6].word = 0x00000000;
				osdCtrl.grdsta[7].word = 0x00000000;
				osdCtrl.grdsta[8].word = 0x00000000;
				osdCtrl.grdsta[9].word = 0x00000001;
			}
			// im_disp_param_check_grdsta
			else if (strcmp((kchar*) argv[6], "29") == 0)
			{
				osdCtrl.grdsta[0].word = 0x00010000;
				osdCtrl.grdsta[1].word = 0x00000000;
				osdCtrl.grdsta[2].word = 0x00000000;
				osdCtrl.grdsta[3].word = 0x00000000;
				osdCtrl.grdsta[4].word = 0x00000000;
				osdCtrl.grdsta[5].word = 0x00000000;
				osdCtrl.grdsta[6].word = 0x00000000;
				osdCtrl.grdsta[7].word = 0x00000000;
				osdCtrl.grdsta[8].word = 0x00000000;
				osdCtrl.grdsta[9].word = 0x00000000;
			}
			else if (strcmp((kchar*) argv[6], "30") == 0)
			{
				osdCtrl.grdsta[0].word = 0x00000000;
				osdCtrl.grdsta[1].word = 0x00000000;
				osdCtrl.grdsta[2].word = 0x00000000;
				osdCtrl.grdsta[3].word = 0x00000000;
				osdCtrl.grdsta[4].word = 0x00010000;
				osdCtrl.grdsta[5].word = 0x00000000;
				osdCtrl.grdsta[6].word = 0x00000000;
				osdCtrl.grdsta[7].word = 0x00000000;
				osdCtrl.grdsta[8].word = 0x00000000;
				osdCtrl.grdsta[9].word = 0x00000000;
			}
			else if (strcmp((kchar*) argv[6], "31") == 0)
			{
				osdCtrl.grdsta[0].word = 0x00000000;
				osdCtrl.grdsta[1].word = 0x00000000;
				osdCtrl.grdsta[2].word = 0x00000000;
				osdCtrl.grdsta[3].word = 0x00000000;
				osdCtrl.grdsta[4].word = 0x00000000;
				osdCtrl.grdsta[5].word = 0x00000000;
				osdCtrl.grdsta[6].word = 0x00000000;
				osdCtrl.grdsta[7].word = 0x00000000;
				osdCtrl.grdsta[8].word = 0x00000000;
				osdCtrl.grdsta[9].word = 0x00010000;
			}
			else if (strcmp((kchar*) argv[6], "32") == 0)
			{
				osdCtrl.grdsta[0].word = 0x00000000;
				osdCtrl.grdsta[1].word = 0x00000002;
				osdCtrl.grdsta[2].word = 0x00000004;
				osdCtrl.grdsta[3].word = 0x00000006;
				osdCtrl.grdsta[4].word = 0x00000008;
				osdCtrl.grdsta[5].word = 0x00000010;
				osdCtrl.grdsta[6].word = 0x00000012;
				osdCtrl.grdsta[7].word = 0x00000014;
				osdCtrl.grdsta[8].word = 0x00000016;
				osdCtrl.grdsta[9].word = 0x00000010;
			}
			// im_disp_param_check_grsa
			else if (strcmp((kchar*) argv[6], "33") == 0)
			{
				osdCtrl.grsa0[0] = 0xFFFFFFF9;
			}
			else if (strcmp((kchar*) argv[6], "34") == 0)
			{
				osdCtrl.grsa0[3] = 0x00000007;
			}
			// im_disp_param_check_grsa
			else if (strcmp((kchar*) argv[6], "35") == 0)
			{
				osdCtrl.grsa[0] = 0xFFFFFFFF;
			}
			else if (strcmp((kchar*) argv[6], "36") == 0)
			{
				osdCtrl.grsa[8] = 0x00000001;
			}
			// im_disp_param_check_resize
			else if (strcmp((kchar*) argv[6], "37") == 0)
			{
				osdCtrl.grrsz0 = 0;
				osdCtrl.grrsz1.word = 0x00000C04;		// rsz1.bit.HRSZM / rsz1.bit.HRSZN < 0.5
				osdCtrl.grrsz2.word = 0x00000404;
				osdCtrl.grrsz3.word = 0x00000000;
			}
			else if (strcmp((kchar*) argv[6], "38") == 0)
			{
				osdCtrl.grrsz0 = 0;
				osdCtrl.grrsz1.word = 0x00000212;		//rsz1.bit.HRSZM / rsz1.bit.HRSZN > 8.0
				osdCtrl.grrsz2.word = 0x00000404;
				osdCtrl.grrsz3.word = 0x00000000;
			}
			else if (strcmp((kchar*) argv[6], "39") == 0)
			{
				osdCtrl.grrsz0 = 0;
				//(rszsl == E_IM_DISP_RSZSL_PADDING_THINNING) && (rsz1.bit.HRSZOF != 0)
				osdCtrl.grrsz1.word = 0x01000408;
				osdCtrl.grrsz2.word = 0x00000408;
				osdCtrl.grrsz3.word = 0x00000000;
			}
			else if (strcmp((kchar*) argv[6], "40") == 0)
			{
				osdCtrl.grrsz0 = 1;
				//rsz1.bit.HRSZM / rsz1.bit.HRSZN == 1.0) && (rsz1.bit.HRSZOF != 0)
				osdCtrl.grrsz1.word = 0x01000404;
				osdCtrl.grrsz2.word = 0x00000404;
				osdCtrl.grrsz3.word = 0x00000000;
			}
			else if (strcmp((kchar*) argv[6], "41") == 0)
			{
				osdCtrl.grrsz0 = 1;
				osdCtrl.grrsz1.word = 0x0A000408;	//rsz1.bit.HRSZOF >= rsz1.bit.HRSZM
				osdCtrl.grrsz2.word = 0x00000404;
				osdCtrl.grrsz3.word = 0x00000000;
			}
			else if (strcmp((kchar*) argv[6], "42") == 0)
			{
				osdCtrl.grrsz0 = 0;
				osdCtrl.grrsz1.word = 0x00000404;
				osdCtrl.grrsz2.word = 0x00000C04;	// rsz2.bit.VRSZM / rsz2.bit.VRSZN < 0.5
				osdCtrl.grrsz3.word = 0x00000000;
			}
			else if (strcmp((kchar*) argv[6], "43") == 0)
			{
				osdCtrl.grrsz0 = 0;
				osdCtrl.grrsz1.word = 0x00000404;	//
				osdCtrl.grrsz2.word = 0x00000214;	// rsz2.bit.VRSZM / rsz2.bit.VRSZN > 8
				osdCtrl.grrsz3.word = 0x00000000;
			}
			else if (strcmp((kchar*) argv[6], "44") == 0)
			{
				osdCtrl.grrsz0 = 0;
				osdCtrl.grrsz1.word = 0x00000404;
				// (rszsl == E_IM_DISP_RSZSL_PADDING_THINNING) && (rsz2.bit.VRSZOF != 0)
				osdCtrl.grrsz2.word = 0x01000404;
				osdCtrl.grrsz3.word = 0x00000000;
			}
			else if (strcmp((kchar*) argv[6], "45") == 0)
			{
				osdCtrl.grrsz0 = 1;
				osdCtrl.grrsz1.word = 0x00000404;
				// rsz2.bit.VRSZM / rsz2.bit.VRSZN == 1.0) && (rsz2.bit.VRSZOF != 0)
				osdCtrl.grrsz2.word = 0x01000404;
				osdCtrl.grrsz3.word = 0x00000000;
			}
			else if (strcmp((kchar*) argv[6], "46") == 0)
			{
				osdCtrl.grrsz0 = 1;
				osdCtrl.grrsz1.word = 0x00000404;
				osdCtrl.grrsz2.word = 0x0A000408;	// (rsz2.bit.VRSZOF >= rsz2.bit.VRSZM)
				osdCtrl.grrsz3.word = 0x00000000;
			}
			else if (strcmp((kchar*) argv[6], "47") == 0)
			{
				osdCtrl.grrsz0 = 0;
				osdCtrl.grrsz1.word = 0x00000404;
				osdCtrl.grrsz2.word = 0x00000404;
				// (rszsl == E_IM_DISP_RSZSL_PADDING_THINNING) && (rsz3.bit.HCSTA != 0)
				osdCtrl.grrsz3.word = 0x00000001;
			}
			else if (strcmp((kchar*) argv[6], "48") == 0)
			{
				osdCtrl.grrsz0 = 0;
				osdCtrl.grrsz1.word = 0x00000404;
				osdCtrl.grrsz2.word = 0x00000404;
				// (rszsl == E_IM_DISP_RSZSL_PADDING_THINNING) && (rsz3.bit.VCSTA != 0)
				osdCtrl.grrsz3.word = 0x00000100;
			}
			if (pGrrpgctl)
			{
				Ddim_Print(("[E_IM_DISP_RPGTMG]\n"));
				Ddim_Print(("rpgtmg:%d\n", grrpgctl)); /* pgr0539 */
			}
			if (pOsdCtrl)
			{
				ct_im_disp3a_print_param_ctrl_osd_layer(osdCtrl);
			}

			error = Im_DISP_Ctrl_OSD_Layer(block, (E_IM_DISP_SEL_LAYER)
					layer, pGrrpgctl, pOsdCtrl); /* pgr0539 */
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Ctrl_OSD_Layer error=%08X\n",error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3a_dump_regiser(disp3a, (E_IM_DISP_SEL_LAYER) layer, block);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 3\n"));
		}
	}
}
#endif /*CtImDisp_CO_DEBUG_DISP*/

static void initTblOsdCtrl(CtImDisp2o *self)
{
	CtImDisp2oPrivate *priv = self->privCtImDisp2o;
	T_IM_DISP_CTRL_OSD_LAYER tblOsdCtrl[CtImDisp4_LCD_DISP_SEL_END][CtImDisp2o_LCD_OSD_END] = {
		{
			{	// [HDMI][OSD0]
				{ (ULONG)DISP_HDMI_OSD0_GRIDT },						// gridt
				{ (ULONG)DISP_HDMI_OSD0_GRTISIZE },						// grtisize
				{ (ULONG)DISP_HDMI_OSD0_GRTDSTA },						// grtdsta
				{ (ULONG)DISP_HDMI_OSD0_GRIPO },						// gripo
				(E_IM_DISP_INPUT_DATA_AREA)( DISP_HDMI_OSD0_GRSCCTL ),	// grscctl_idset
				{														// grisize[10]
					{ (ULONG)DISP_HDMI_OSD0_GRISIZE0 },
					{ (ULONG)DISP_HDMI_OSD0_GRISIZE1 },
					{ (ULONG)DISP_HDMI_OSD0_GRISIZE2 },
					{ (ULONG)DISP_HDMI_OSD0_GRISIZE3 },
					{ (ULONG)DISP_HDMI_OSD0_GRISIZE4 },
					{ (ULONG)DISP_HDMI_OSD0_GRISIZE5 },
					{ (ULONG)DISP_HDMI_OSD0_GRISIZE6 },
					{ (ULONG)DISP_HDMI_OSD0_GRISIZE7 },
					{ (ULONG)DISP_HDMI_OSD0_GRISIZE8 },
					{ (ULONG)DISP_HDMI_OSD0_GRISIZE9 }
				},
				{														// grsa0[4]
					DISP_HDMI_OSD0_GRSA0_0,
					DISP_HDMI_OSD0_GRSA0_1,
					DISP_HDMI_OSD0_GRSA0_2,
					DISP_HDMI_OSD0_GRSA0_3
				},
				{														// grsa[9]
					DISP_HDMI_OSD0_GRSA1,
					DISP_HDMI_OSD0_GRSA2,
					DISP_HDMI_OSD0_GRSA3,
					DISP_HDMI_OSD0_GRSA4,
					DISP_HDMI_OSD0_GRSA5,
					DISP_HDMI_OSD0_GRSA6,
					DISP_HDMI_OSD0_GRSA7,
					DISP_HDMI_OSD0_GRSA8,
					DISP_HDMI_OSD0_GRSA9
				},
				{													// grasa[10]
					DISP_HDMI_OSD0_GRASA0,
					DISP_HDMI_OSD0_GRASA1,
					DISP_HDMI_OSD0_GRASA2,
					DISP_HDMI_OSD0_GRASA3,
					DISP_HDMI_OSD0_GRASA4,
					DISP_HDMI_OSD0_GRASA5,
					DISP_HDMI_OSD0_GRASA6,
					DISP_HDMI_OSD0_GRASA7,
					DISP_HDMI_OSD0_GRASA8,
					DISP_HDMI_OSD0_GRASA9
				},
				{														// grhga[10]
					DISP_HDMI_OSD0_GRHGA0,
					DISP_HDMI_OSD0_GRHGA1,
					DISP_HDMI_OSD0_GRHGA2,
					DISP_HDMI_OSD0_GRHGA3,
					DISP_HDMI_OSD0_GRHGA4,
					DISP_HDMI_OSD0_GRHGA5,
					DISP_HDMI_OSD0_GRHGA6,
					DISP_HDMI_OSD0_GRHGA7,
					DISP_HDMI_OSD0_GRHGA8,
					DISP_HDMI_OSD0_GRHGA9
				},
				{														// grahga[10]
					DISP_HDMI_OSD0_GRAHGA0,
					DISP_HDMI_OSD0_GRAHGA1,
					DISP_HDMI_OSD0_GRAHGA2,
					DISP_HDMI_OSD0_GRAHGA3,
					DISP_HDMI_OSD0_GRAHGA4,
					DISP_HDMI_OSD0_GRAHGA5,
					DISP_HDMI_OSD0_GRAHGA6,
					DISP_HDMI_OSD0_GRAHGA7,
					DISP_HDMI_OSD0_GRAHGA8,
					DISP_HDMI_OSD0_GRAHGA9
				},
				{												// grdsta[10]
					{ (ULONG)DISP_HDMI_OSD0_GRDSTA0 },					// grdsta[0]
					{ (ULONG)DISP_HDMI_OSD0_GRDSTA1 },					// grdsta[1]
					{ (ULONG)DISP_HDMI_OSD0_GRDSTA2 },					// grdsta[2]
					{ (ULONG)DISP_HDMI_OSD0_GRDSTA3 },					// grdsta[3]
					{ (ULONG)DISP_HDMI_OSD0_GRDSTA4 },					// grdsta[4]
					{ (ULONG)DISP_HDMI_OSD0_GRDSTA5 },					// grdsta[5]
					{ (ULONG)DISP_HDMI_OSD0_GRDSTA6 },					// grdsta[6]
					{ (ULONG)DISP_HDMI_OSD0_GRDSTA7 },					// grdsta[7]
					{ (ULONG)DISP_HDMI_OSD0_GRDSTA8 },					// grdsta[8]
					{ (ULONG)DISP_HDMI_OSD0_GRDSTA9 }					// grdsta[9]
				},
				DISP_HDMI_OSD0_GRAREN,									// graren
				(ULONG)DISP_HDMI_OSD0_GRBSL,									// grbsl
				{														// grblink
					{
						(ULONG)DISP_HDMI_OSD0_GRBLINK0,
						(ULONG)DISP_HDMI_OSD0_GRBLINK1,
						(ULONG)DISP_HDMI_OSD0_GRBLINK2,
						(ULONG)DISP_HDMI_OSD0_GRBLINK3,
						(ULONG)DISP_HDMI_OSD0_GRBLINK4
					}
				},
				DISP_HDMI_OSD0_GRBINIT,									// grbinit
				DISP_HDMI_OSD0_GRBITRG,									// grbitrg
				(E_IM_DISP_RSZSL)DISP_HDMI_OSD0_GRRSZ0,					// grrsz0
				{ (ULONG)DISP_HDMI_OSD0_GRRSZ1 },							// grrsz1
				{ (ULONG)DISP_HDMI_OSD0_GRRSZ2 },							// grrsz2
				{ (ULONG)DISP_HDMI_OSD0_GRRSZ3 },							// grrsz3
				{														// gry2r[3]
					{ (ULONG)DISP_HDMI_OSD0_GRY2R0 },
					{ (ULONG)DISP_HDMI_OSD0_GRY2R1 },
					{ (ULONG)DISP_HDMI_OSD0_GRY2R2 }
				},
				(ULONG)DISP_HDMI_OSD0_GRALP							// gralp
			},

			{	// [HDMI][OSD1]
				{ (ULONG)DISP_HDMI_OSD1_GRIDT },						// gridt
				{ (ULONG)DISP_HDMI_OSD1_GRTISIZE },						// grtisize
				{ (ULONG)DISP_HDMI_OSD1_GRTDSTA },						// grtdsta
				{ (ULONG)DISP_HDMI_OSD1_GRIPO },						// gripo
				(E_IM_DISP_INPUT_DATA_AREA)( DISP_HDMI_OSD1_GRSCCTL ),	// grscctl_idset
				{														// grisize[10]
					{ (ULONG)DISP_HDMI_OSD1_GRISIZE0 },
					{ (ULONG)DISP_HDMI_OSD1_GRISIZE1 },
					{ (ULONG)DISP_HDMI_OSD1_GRISIZE2 },
					{ (ULONG)DISP_HDMI_OSD1_GRISIZE3 },
					{ (ULONG)DISP_HDMI_OSD1_GRISIZE4 },
					{ (ULONG)DISP_HDMI_OSD1_GRISIZE5 },
					{ (ULONG)DISP_HDMI_OSD1_GRISIZE6 },
					{ (ULONG)DISP_HDMI_OSD1_GRISIZE7 },
					{ (ULONG)DISP_HDMI_OSD1_GRISIZE8 },
					{ (ULONG)DISP_HDMI_OSD1_GRISIZE9 }
				},
				{													// grsa0[4]
					DISP_HDMI_OSD1_GRSA0_0,
					DISP_HDMI_OSD1_GRSA0_1,
					DISP_HDMI_OSD1_GRSA0_2,
					DISP_HDMI_OSD1_GRSA0_3
				},
				{													// grsa[9]
					DISP_HDMI_OSD1_GRSA1,
					DISP_HDMI_OSD1_GRSA2,
					DISP_HDMI_OSD1_GRSA3,
					DISP_HDMI_OSD1_GRSA4,
					DISP_HDMI_OSD1_GRSA5,
					DISP_HDMI_OSD1_GRSA6,
					DISP_HDMI_OSD1_GRSA7,
					DISP_HDMI_OSD1_GRSA8,
					DISP_HDMI_OSD1_GRSA9
				},
				{													// grasa[10]
					DISP_HDMI_OSD1_GRASA0,
					DISP_HDMI_OSD1_GRASA1,
					DISP_HDMI_OSD1_GRASA2,
					DISP_HDMI_OSD1_GRASA3,
					DISP_HDMI_OSD1_GRASA4,
					DISP_HDMI_OSD1_GRASA5,
					DISP_HDMI_OSD1_GRASA6,
					DISP_HDMI_OSD1_GRASA7,
					DISP_HDMI_OSD1_GRASA8,
					DISP_HDMI_OSD1_GRASA9
				},
				{													// grhga[10]
					DISP_HDMI_OSD1_GRHGA0,
					DISP_HDMI_OSD1_GRHGA1,
					DISP_HDMI_OSD1_GRHGA2,
					DISP_HDMI_OSD1_GRHGA3,
					DISP_HDMI_OSD1_GRHGA4,
					DISP_HDMI_OSD1_GRHGA5,
					DISP_HDMI_OSD1_GRHGA6,
					DISP_HDMI_OSD1_GRHGA7,
					DISP_HDMI_OSD1_GRHGA8,
					DISP_HDMI_OSD1_GRHGA9
				},
				{													// grahga[10]
					DISP_HDMI_OSD1_GRAHGA0,
					DISP_HDMI_OSD1_GRAHGA1,
					DISP_HDMI_OSD1_GRAHGA2,
					DISP_HDMI_OSD1_GRAHGA3,
					DISP_HDMI_OSD1_GRAHGA4,
					DISP_HDMI_OSD1_GRAHGA5,
					DISP_HDMI_OSD1_GRAHGA6,
					DISP_HDMI_OSD1_GRAHGA7,
					DISP_HDMI_OSD1_GRAHGA8,
					DISP_HDMI_OSD1_GRAHGA9
				},
				{													// grdsta[10]
					{ (ULONG)DISP_HDMI_OSD1_GRDSTA0 },
					{ (ULONG)DISP_HDMI_OSD1_GRDSTA1 },
					{ (ULONG)DISP_HDMI_OSD1_GRDSTA2 },
					{ (ULONG)DISP_HDMI_OSD1_GRDSTA3 },
					{ (ULONG)DISP_HDMI_OSD1_GRDSTA4 },
					{ (ULONG)DISP_HDMI_OSD1_GRDSTA5 },
					{ (ULONG)DISP_HDMI_OSD1_GRDSTA6 },
					{ (ULONG)DISP_HDMI_OSD1_GRDSTA7 },
					{ (ULONG)DISP_HDMI_OSD1_GRDSTA8 },
					{ (ULONG)DISP_HDMI_OSD1_GRDSTA9 }
				},
				DISP_HDMI_OSD1_GRAREN,						// graren
				(ULONG)DISP_HDMI_OSD1_GRBSL,						// grbsl
				{													// grblink
					{
						(ULONG)DISP_HDMI_OSD1_GRBLINK0,
						(ULONG)DISP_HDMI_OSD1_GRBLINK1,
						(ULONG)DISP_HDMI_OSD1_GRBLINK2,
						(ULONG)DISP_HDMI_OSD1_GRBLINK3,
						(ULONG)DISP_HDMI_OSD1_GRBLINK4
					}
				},
				DISP_HDMI_OSD1_GRBINIT,								// grbinit
				DISP_HDMI_OSD1_GRBITRG,								// grbitrg
				(E_IM_DISP_RSZSL)DISP_HDMI_OSD1_GRRSZ0,				// grrsz0
				{ (ULONG)DISP_HDMI_OSD1_GRRSZ1 },						// grrsz1
				{ (ULONG)DISP_HDMI_OSD1_GRRSZ2 },						// grrsz2
				{ (ULONG)DISP_HDMI_OSD1_GRRSZ3 },						// grrsz3
				{													// gry2r[3]
					{ (ULONG)DISP_HDMI_OSD1_GRY2R0 },
					{ (ULONG)DISP_HDMI_OSD1_GRY2R1 },
					{ (ULONG)DISP_HDMI_OSD1_GRY2R2 }
				},
				(ULONG)DISP_HDMI_OSD1_GRALP							// gralp
			}
		},

		{
			{	// [LCD][OSD0]
				{ (ULONG)DISP_LCD_OSD0_GRIDT },							// gridt
				{ (ULONG)DISP_LCD_OSD0_GRTISIZE },						// grtisize
				{ (ULONG)DISP_LCD_OSD0_GRTDSTA },						// grtdsta
				{ (ULONG)DISP_LCD_OSD0_GRIPO },							// gripo
				(E_IM_DISP_INPUT_DATA_AREA)( DISP_LCD_OSD0_GRSCCTL ),	// grscctl_idset
				{														// grisize[10]
					{ (ULONG)DISP_LCD_OSD0_GRISIZE0 },
					{ (ULONG)DISP_LCD_OSD0_GRISIZE1 },
					{ (ULONG)DISP_LCD_OSD0_GRISIZE2 },
					{ (ULONG)DISP_LCD_OSD0_GRISIZE3 },
					{ (ULONG)DISP_LCD_OSD0_GRISIZE4 },
					{ (ULONG)DISP_LCD_OSD0_GRISIZE5 },
					{ (ULONG)DISP_LCD_OSD0_GRISIZE6 },
					{ (ULONG)DISP_LCD_OSD0_GRISIZE7 },
					{ (ULONG)DISP_LCD_OSD0_GRISIZE8 },
					{ (ULONG)DISP_LCD_OSD0_GRISIZE9 }
				},
				{														// grsa0[4]
					DISP_LCD_OSD0_GRSA0_0,
					DISP_LCD_OSD0_GRSA0_1,
					DISP_LCD_OSD0_GRSA0_2,
					DISP_LCD_OSD0_GRSA0_3
				},
				{														// grsa[9]
					DISP_LCD_OSD0_GRSA1,
					DISP_LCD_OSD0_GRSA2,
					DISP_LCD_OSD0_GRSA3,
					DISP_LCD_OSD0_GRSA4,
					DISP_LCD_OSD0_GRSA5,
					DISP_LCD_OSD0_GRSA6,
					DISP_LCD_OSD0_GRSA7,
					DISP_LCD_OSD0_GRSA8,
					DISP_LCD_OSD0_GRSA9
				},
				{													// grasa[10]
					DISP_LCD_OSD1_GRASA0,
					DISP_LCD_OSD1_GRASA1,
					DISP_LCD_OSD1_GRASA2,
					DISP_LCD_OSD1_GRASA3,
					DISP_LCD_OSD1_GRASA4,
					DISP_LCD_OSD1_GRASA5,
					DISP_LCD_OSD1_GRASA6,
					DISP_LCD_OSD1_GRASA7,
					DISP_LCD_OSD1_GRASA8,
					DISP_LCD_OSD1_GRASA9
				},
				{														// grhga[10]
					DISP_LCD_OSD1_GRHGA0,
					DISP_LCD_OSD1_GRHGA1,
					DISP_LCD_OSD1_GRHGA2,
					DISP_LCD_OSD1_GRHGA3,
					DISP_LCD_OSD1_GRHGA4,
					DISP_LCD_OSD1_GRHGA5,
					DISP_LCD_OSD1_GRHGA6,
					DISP_LCD_OSD1_GRHGA7,
					DISP_LCD_OSD1_GRHGA8,
					DISP_LCD_OSD1_GRHGA9
				},
				{														// grahga[10]
					DISP_LCD_OSD0_GRAHGA0,
					DISP_LCD_OSD0_GRAHGA1,
					DISP_LCD_OSD0_GRAHGA2,
					DISP_LCD_OSD0_GRAHGA3,
					DISP_LCD_OSD0_GRAHGA4,
					DISP_LCD_OSD0_GRAHGA5,
					DISP_LCD_OSD0_GRAHGA6,
					DISP_LCD_OSD0_GRAHGA7,
					DISP_LCD_OSD0_GRAHGA8,
					DISP_LCD_OSD0_GRAHGA9
				},
				{														// grdsta[10]
					{ (ULONG)DISP_LCD_OSD0_GRDSTA0 },
					{ (ULONG)DISP_LCD_OSD0_GRDSTA1 },
					{ (ULONG)DISP_LCD_OSD0_GRDSTA2 },
					{ (ULONG)DISP_LCD_OSD0_GRDSTA3 },
					{ (ULONG)DISP_LCD_OSD0_GRDSTA4 },
					{ (ULONG)DISP_LCD_OSD0_GRDSTA5 },
					{ (ULONG)DISP_LCD_OSD0_GRDSTA6 },
					{ (ULONG)DISP_LCD_OSD0_GRDSTA7 },
					{ (ULONG)DISP_LCD_OSD0_GRDSTA8 },
					{ (ULONG)DISP_LCD_OSD0_GRDSTA9 }
				},
				DISP_LCD_OSD0_GRAREN,							// graren
				(ULONG)DISP_LCD_OSD0_GRBSL,								// grbsl
				{														// grblink
					{
						(ULONG)DISP_LCD_OSD0_GRBLINK0,
						(ULONG)DISP_LCD_OSD0_GRBLINK1,
						(ULONG)DISP_LCD_OSD0_GRBLINK2,
						(ULONG)DISP_LCD_OSD0_GRBLINK3,
						(ULONG)DISP_LCD_OSD0_GRBLINK4
					}
				},
				DISP_LCD_OSD0_GRBINIT,									// grbinit
				DISP_LCD_OSD0_GRBITRG,									// grbitrg
				(E_IM_DISP_RSZSL)DISP_LCD_OSD0_GRRSZ0,					// grrsz0
				{ (ULONG)DISP_LCD_OSD0_GRRSZ1 },							// grrsz1
				{ (ULONG)DISP_LCD_OSD0_GRRSZ2 },							// grrsz2
				{ (ULONG)DISP_LCD_OSD0_GRRSZ3 },							// grrsz3
				{														// gry2r[3]
					{ (ULONG)DISP_LCD_OSD0_GRY2R0 },
					{ (ULONG)DISP_LCD_OSD0_GRY2R1 },
					{ (ULONG)DISP_LCD_OSD0_GRY2R2 },
				},
				(ULONG)DISP_LCD_OSD0_GRALP								// gralp
			},
			{	// [LCD][OSD1]
				{ (ULONG)DISP_LCD_OSD1_GRIDT },							// gridt
				{ (ULONG)DISP_LCD_OSD1_GRTISIZE },						// grtisize
				{ (ULONG)DISP_LCD_OSD1_GRTDSTA },						// grtdsta
				{ (ULONG)DISP_LCD_OSD1_GRIPO },							// gripo
				(E_IM_DISP_INPUT_DATA_AREA)( DISP_LCD_OSD1_GRSCCTL ),	// grscctl_idset
				{														// grisize[10]
					{ (ULONG)DISP_LCD_OSD1_GRISIZE0 },
					{ (ULONG)DISP_LCD_OSD1_GRISIZE1 },
					{ (ULONG)DISP_LCD_OSD1_GRISIZE2 },
					{ (ULONG)DISP_LCD_OSD1_GRISIZE3 },
					{ (ULONG)DISP_LCD_OSD1_GRISIZE4 },
					{ (ULONG)DISP_LCD_OSD1_GRISIZE5 },
					{ (ULONG)DISP_LCD_OSD1_GRISIZE6 },
					{ (ULONG)DISP_LCD_OSD1_GRISIZE7 },
					{ (ULONG)DISP_LCD_OSD1_GRISIZE8 },
					{ (ULONG)DISP_LCD_OSD1_GRISIZE9 }
				},
				{													// grsa0[4]
					DISP_LCD_OSD1_GRSA0_0,
					DISP_LCD_OSD1_GRSA0_1,
					DISP_LCD_OSD1_GRSA0_2,
					DISP_LCD_OSD1_GRSA0_3
				},
				{													// grsa[9]
					DISP_LCD_OSD1_GRSA1,
					DISP_LCD_OSD1_GRSA2,
					DISP_LCD_OSD1_GRSA3,
					DISP_LCD_OSD1_GRSA4,
					DISP_LCD_OSD1_GRSA5,
					DISP_LCD_OSD1_GRSA6,
					DISP_LCD_OSD1_GRSA7,
					DISP_LCD_OSD1_GRSA8,
					DISP_LCD_OSD1_GRSA9
				},
				{													// grasa[10]
					DISP_LCD_OSD1_GRASA0,
					DISP_LCD_OSD1_GRASA1,
					DISP_LCD_OSD1_GRASA2,
					DISP_LCD_OSD1_GRASA3,
					DISP_LCD_OSD1_GRASA4,
					DISP_LCD_OSD1_GRASA5,
					DISP_LCD_OSD1_GRASA6,
					DISP_LCD_OSD1_GRASA7,
					DISP_LCD_OSD1_GRASA8,
					DISP_LCD_OSD1_GRASA9
				},
				{													// grhga[10]
					DISP_LCD_OSD1_GRHGA0,
					DISP_LCD_OSD1_GRHGA1,
					DISP_LCD_OSD1_GRHGA2,
					DISP_LCD_OSD1_GRHGA3,
					DISP_LCD_OSD1_GRHGA4,
					DISP_LCD_OSD1_GRHGA5,
					DISP_LCD_OSD1_GRHGA6,
					DISP_LCD_OSD1_GRHGA7,
					DISP_LCD_OSD1_GRHGA8,
					DISP_LCD_OSD1_GRHGA9
				},
				{													// grahga[10]
					DISP_LCD_OSD1_GRAHGA0,
					DISP_LCD_OSD1_GRAHGA1,
					DISP_LCD_OSD1_GRAHGA2,
					DISP_LCD_OSD1_GRAHGA3,
					DISP_LCD_OSD1_GRAHGA4,
					DISP_LCD_OSD1_GRAHGA5,
					DISP_LCD_OSD1_GRAHGA6,
					DISP_LCD_OSD1_GRAHGA7,
					DISP_LCD_OSD1_GRAHGA8,
					DISP_LCD_OSD1_GRAHGA9
				},
				{													// grdsta[10]
					{ (ULONG)DISP_LCD_OSD1_GRDSTA0 },
					{ (ULONG)DISP_LCD_OSD1_GRDSTA1 },
					{ (ULONG)DISP_LCD_OSD1_GRDSTA2 },
					{ (ULONG)DISP_LCD_OSD1_GRDSTA3 },
					{ (ULONG)DISP_LCD_OSD1_GRDSTA4 },
					{ (ULONG)DISP_LCD_OSD1_GRDSTA5 },
					{ (ULONG)DISP_LCD_OSD1_GRDSTA6 },
					{ (ULONG)DISP_LCD_OSD1_GRDSTA7 },
					{ (ULONG)DISP_LCD_OSD1_GRDSTA8 },
					{ (ULONG)DISP_LCD_OSD1_GRDSTA9 }
				},
				DISP_LCD_OSD1_GRAREN,						// graren
				(ULONG)DISP_LCD_OSD1_GRBSL,							// grbsl
				{													// grblink
					{
						(ULONG)DISP_LCD_OSD1_GRBLINK0,
						(ULONG)DISP_LCD_OSD1_GRBLINK1,
						(ULONG)DISP_LCD_OSD1_GRBLINK2,
						(ULONG)DISP_LCD_OSD1_GRBLINK3,
						(ULONG)DISP_LCD_OSD1_GRBLINK4
					}
				},
				DISP_LCD_OSD1_GRBINIT,								// grbinit
				DISP_LCD_OSD1_GRBITRG,								// grbitrg
				(E_IM_DISP_RSZSL)DISP_LCD_OSD1_GRRSZ0,				// grrsz0
				{ (ULONG)DISP_LCD_OSD1_GRRSZ1 },						// grrsz1
				{ (ULONG)DISP_LCD_OSD1_GRRSZ2 },						// grrsz2
				{ (ULONG)DISP_LCD_OSD1_GRRSZ3 },						// grrsz3
				{													// gry2r[3]
					{ (ULONG)DISP_LCD_OSD1_GRY2R0 },
					{ (ULONG)DISP_LCD_OSD1_GRY2R1 },
					{ (ULONG)DISP_LCD_OSD1_GRY2R2 },
				},
				(ULONG)DISP_LCD_OSD1_GRALP,							// gralp
			}
		}
	};
	memcpy(priv->gLcdDispTblOsdCtrl, &tblOsdCtrl, sizeof(tblOsdCtrl));
}

/*
 * PUBLIC
 * */
CtImDisp2o *ct_im_disp2o_new(void)
{
	CtImDisp2o *self = (CtImDisp2o *) k_object_new_with_private(CT_TYPE_IM_DISP2O,sizeof(CtImDisp2oPrivate));
	return self;
}
