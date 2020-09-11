/*
 *ctimdisp2b.c
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
#include "ctimdisp2b.h"

K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(CtImDisp2b, ct_im_disp2b, IM_TYPE_DISP2_PARENT)
#define CT_IM_DISP2B_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), CtImDisp2bPrivate, CT_TYPE_IM_DISP2B))

struct _CtImDisp2bPrivate
{
	Disp2bNewParams *params;
};

/*
 * DECLS
 * */
#ifdef CtImDisp_CO_DEBUG_DISP
static void disp2bDoMain_od(ImDisp2Parent *parent, kint32 argc, char **argv);
#endif /*CtImDisp_CO_DEBUG_DISP*/

/*
 * IMPL
 * */
static void ct_im_disp2b_constructor(CtImDisp2b *self)
{
	CtImDisp2bPrivate *priv = CT_IM_DISP2B_GET_PRIVATE(self);
#ifdef CtImDisp_CO_DEBUG_DISP
	ImDisp2Parent *parent = (ImDisp2Parent *)self;
	parent->doMainFunc = disp2bDoMain_od;
#endif /*CtImDisp_CO_DEBUG_DISP*/
	self->privCtImDisp2b = priv;
}

static void ct_im_disp2b_destructor(CtImDisp2b *self)
{
}

#ifdef CtImDisp_CO_DEBUG_DISP
static void disp2bDoMain_od(ImDisp2Parent *parent, kint32 argc, char **argv)
{
	CtImDisp2b *self= (CtImDisp2b *)parent;
	CtImDisp2bPrivate *priv = self->privCtImDisp2b;
	E_IM_DISP_SEL block = strtoul(argv[3], NULL, 0);
	kint32 error = D_DDIM_OK;
	ImDisp2Group *imDisp2Group = (ImDisp2Group *)im_disp2_parent_get_group(parent);
	CtImDisp3a *disp3a = (CtImDisp3a *)im_disp2_group_get_disp3a(imDisp2Group);

	T_IM_DISP_CTRL_OUTPUT_TRG_LIMIT *pOutCtrlTrgLimit =
			(T_IM_DISP_CTRL_OUTPUT_TRG_LIMIT *)priv->params->pOutCtrlTrgLimit;
	T_IM_DISP_CTRL_OUTPUT *pOutCtrl = (T_IM_DISP_CTRL_OUTPUT *)priv->params->pOutCtrl;

	// HDMI
	// "CP:im_disp_param_check_ctrl_output() : HDMI 1
	if (strcmp((kchar*) argv[4], "67") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_HDMI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_RGB888_8BIT_1;
	}
	else if (strcmp((kchar*) argv[4], "68") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_HDMI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_RGB888_8BIT_2;
	}
	else if (strcmp((kchar*) argv[4], "69") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_HDMI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_RGB888_8BIT_3;
	}
	else if (strcmp((kchar*) argv[4], "70") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_HDMI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_RGB888_16BIT_1;
	}
	else if (strcmp((kchar*) argv[4], "71") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_HDMI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_RGB888_16BIT_2;
	}
	else if (strcmp((kchar*) argv[4], "72") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_HDMI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_RGB565_8BIT;
	}
	else if (strcmp((kchar*) argv[4], "73") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_HDMI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_RGB565_16BIT;
	}
	else if (strcmp((kchar*) argv[4], "74") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_HDMI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_RGB666_18BIT;
	}
	else if (strcmp((kchar*) argv[4], "75") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_HDMI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_YCC422_8BIT;
	}
	else if (strcmp((kchar*) argv[4], "76") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_HDMI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_DUAL_YCC444_12BIT;
	}
	else if (strcmp((kchar*) argv[4], "77") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_HDMI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_GENERAL_8BIT;
	}
	else if (strcmp((kchar*) argv[4], "78") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_HDMI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_GENERAL_16BIT;
	}
	// "CP:im_disp_param_check_ctrl_output() : HDMI 2
	else if (strcmp((kchar*) argv[4], "79") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_HDMI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		// veps error for HDMI
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_RGB888_24BIT;
		pOutCtrlTrgLimit->polsel.bit.VEPS = D_IM_DISP_POLARITY_NEGATIVE;
	}
	// "CP:im_disp_param_check_ctrl_output() : HDMI 3
	else if (strcmp((kchar*) argv[4], "80") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_HDMI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		// vens error for HDMI
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_RGB888_24BIT;
		pOutCtrlTrgLimit->polsel.bit.VEPS = D_IM_DISP_POLARITY_POSITIVE;
		pOutCtrlTrgLimit->vrfctl = D_IM_DISP_VENS_HSYNC;
	}
	// "CP:im_disp_param_check_ctrl_output() : HDMI 4
	else if (strcmp((kchar*) argv[4], "81") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_HDMI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		// ovsize error for HDMI
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_RGB888_24BIT;
		pOutCtrlTrgLimit->polsel.bit.VEPS = D_IM_DISP_POLARITY_POSITIVE;
		pOutCtrlTrgLimit->vrfctl = D_IM_DISP_VENS_H_ENABLE;
		pOutCtrlTrgLimit->ovsize = 0x2002;
	}
	// "CP:im_disp_param_check_ctrl_output() : HDMI 5
	else if (strcmp((kchar*) argv[4], "82") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_HDMI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		// ohsize error for HDMI
//							if (ctrl->clbhsize * 16 < ohsize) {
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_RGB888_24BIT;
		pOutCtrlTrgLimit->polsel.bit.VEPS = D_IM_DISP_POLARITY_POSITIVE;
		pOutCtrlTrgLimit->vrfctl = D_IM_DISP_VENS_H_ENABLE;
		pOutCtrl->clbhsize = 0x1100;
		pOutCtrlTrgLimit->ohsize = 0x1002;
	}
	// "CP:im_disp_param_check_ctrl_output() : HDMI 6
	else if (strcmp((kchar*) argv[4], "83") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_HDMI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		// con error for HDMI
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_RGB888_24BIT;
		pOutCtrlTrgLimit->polsel.bit.VEPS = D_IM_DISP_POLARITY_POSITIVE;
		pOutCtrlTrgLimit->vrfctl = D_IM_DISP_VENS_H_ENABLE;
		pOutCtrlTrgLimit->toctl.bit.CON = D_IM_DISP_CON_EXTERNAL;
		pOutCtrl->clbhsize = 0x1000;
		pOutCtrlTrgLimit->ohsize = 0x1000;
	}

	// LCD
	// "CP:im_disp_param_check_ctrl_output() : LCD 1
	else if (strcmp((kchar*) argv[4], "84") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_LCD;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_RGB888_30BIT;
	}
	else if (strcmp((kchar*) argv[4], "85") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_LCD;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_RGB888_36BIT;
	}
	else if (strcmp((kchar*) argv[4], "86") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_LCD;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_RGB888_16BIT_1;
	}
	else if (strcmp((kchar*) argv[4], "87") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_LCD;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_RGB888_16BIT_2;
	}
	else if (strcmp((kchar*) argv[4], "88") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_LCD;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_RGB565_8BIT;
	}
	else if (strcmp((kchar*) argv[4], "89") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_LCD;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_RGB565_16BIT;
	}
	else if (strcmp((kchar*) argv[4], "90") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_LCD;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_RGB666_18BIT;
	}
	else if (strcmp((kchar*) argv[4], "91") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_LCD;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_YCC444_24BIT;
	}
	else if (strcmp((kchar*) argv[4], "92") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_LCD;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_YCC422_20BIT;
	}
	else if (strcmp((kchar*) argv[4], "93") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_LCD;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_YCC422_24BIT;
	}
	else if (strcmp((kchar*) argv[4], "94") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_LCD;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_DEEP_YCC444_30BIT;
	}
	else if (strcmp((kchar*) argv[4], "95") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_LCD;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_DEEP_YCC444_36BIT;
	}
	else if (strcmp((kchar*) argv[4], "96") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_LCD;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_DUAL_YCC444_12BIT;
	}
	else if (strcmp((kchar*) argv[4], "97") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_LCD;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_YCC420_24BIT;
	}
	else if (strcmp((kchar*) argv[4], "98") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_LCD;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_YCC420_30BIT;
	}
	else if (strcmp((kchar*) argv[4], "99") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_LCD;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_GENERAL_8BIT;
	}
	else if (strcmp((kchar*) argv[4], "A1") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_LCD;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_GENERAL_16BIT;
	}
	else if (strcmp((kchar*) argv[4], "A2") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_LCD;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_GENERAL_10BIT_1;
	}
	else if (strcmp((kchar*) argv[4], "A3") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_LCD;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_GENERAL_10BIT_2;
	}
	// "CP:im_disp_param_check_ctrl_output() : LCD 2
	else if (strcmp((kchar*) argv[4], "A4") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_LCD;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		// con error for LCD
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_RGB888_24BIT;
		pOutCtrlTrgLimit->toctl.bit.CON = D_IM_DISP_CON_INTERNAL;
	}
	// "CP:im_disp_param_check_ctrl_output() : LCD 3
	else if (strcmp((kchar*) argv[4], "A5") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_LCD;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		// ovsize error for LCD
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_RGB888_24BIT;
		pOutCtrlTrgLimit->toctl.bit.CON = D_IM_DISP_CON_EXTERNAL;
		pOutCtrlTrgLimit->ovsize = 0x2002;
	}
	// "CP:im_disp_param_check_ctrl_output() : LCD 4
	else if (strcmp((kchar*) argv[4], "A6") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_LCD;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		// ovsize error for LCD
		//		if (ctrl->clbhsize * 16 < ohsize) {
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_RGB888_24BIT;
		pOutCtrlTrgLimit->toctl.bit.CON = D_IM_DISP_CON_EXTERNAL;
		pOutCtrl->clbhsize = 0x1100;
		pOutCtrlTrgLimit->ohsize = 0x782;
	}
	// "CP:im_disp_param_check_ctrl_output() : LCD 5
	else if (strcmp((kchar*) argv[4], "A7") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_LCD;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		// ovsize error for LCD
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_RGB888_24BIT;
		pOutCtrlTrgLimit->toctl.bit.CON = D_IM_DISP_CON_EXTERNAL;
		pOutCtrl->doctl2.bit.CTOV = D_IM_DISP_CTOV_AVERAGE;
	}

	// MIPI
	// "CP:im_disp_param_check_ctrl_output() : MIPI 1
	else if (strcmp((kchar*) argv[4], "A8") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_MIPI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		// mode error for MIPI
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_RGB888_30BIT;
	}
	else if (strcmp((kchar*) argv[4], "A9") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_MIPI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		// mode error for MIPI
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_RGB888_36BIT;
	}
	else if (strcmp((kchar*) argv[4], "B1") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_MIPI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		// mode error for MIPI
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_RGB888_8BIT_1;
	}
	else if (strcmp((kchar*) argv[4], "B2") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_MIPI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		// mode error for MIPI
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_RGB888_8BIT_2;
	}
	else if (strcmp((kchar*) argv[4], "B3") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_MIPI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		// mode error for MIPI
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_RGB888_8BIT_3;
	}
	else if (strcmp((kchar*) argv[4], "B4") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_MIPI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		// mode error for MIPI
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_RGB888_16BIT_1;
	}
	else if (strcmp((kchar*) argv[4], "B5") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_MIPI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		// mode error for MIPI
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_RGB888_16BIT_2;
	}
	else if (strcmp((kchar*) argv[4], "B6") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_MIPI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		// mode error for MIPI
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_RGB565_8BIT;
	}
	else if (strcmp((kchar*) argv[4], "B7") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_MIPI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		// mode error for MIPI
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_YCC422_8BIT;
	}
	else if (strcmp((kchar*) argv[4], "B8") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_MIPI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		// mode error for MIPI
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_YCC422_16BIT;
	}
	else if (strcmp((kchar*) argv[4], "B9") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_MIPI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		// mode error for MIPI
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_YCC444_24BIT;
	}
	else if (strcmp((kchar*) argv[4], "C1") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_MIPI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		// mode error for MIPI
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_YCC422_20BIT;
	}
	else if (strcmp((kchar*) argv[4], "C2") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_MIPI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		// mode error for MIPI
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_YCC422_24BIT;
	}
	else if (strcmp((kchar*) argv[4], "C3") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_MIPI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		// mode error for MIPI
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_DEEP_YCC444_30BIT;
	}
	else if (strcmp((kchar*) argv[4], "C4") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_MIPI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		// mode error for MIPI
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_DEEP_YCC444_36BIT;
	}
	else if (strcmp((kchar*) argv[4], "C5") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_MIPI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		// mode error for MIPI
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_DUAL_YCC444_12BIT;
	}
	else if (strcmp((kchar*) argv[4], "C6") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_MIPI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		// mode error for MIPI
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_YCC420_24BIT;
	}
	else if (strcmp((kchar*) argv[4], "C7") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_MIPI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		// mode error for MIPI
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_YCC420_30BIT;
	}
	else if (strcmp((kchar*) argv[4], "C8") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_MIPI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		// mode error for MIPI
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_GENERAL_8BIT;
	}
	else if (strcmp((kchar*) argv[4], "C9") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_MIPI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		// mode error for MIPI
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_GENERAL_16BIT;
	}
	else if (strcmp((kchar*) argv[4], "D1") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_MIPI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		// mode error for MIPI
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_GENERAL_10BIT_1;
	}
	else if (strcmp((kchar*) argv[4], "D2") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_MIPI;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		// mode error for MIPI
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_GENERAL_10BIT_2;
	}
	// "CP:im_disp_param_check_ctrl_output() : MIPI 2
	else if (strcmp((kchar*) argv[4], "D3") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_LCD;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		// con error for LCD
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_RGB888_24BIT;
		pOutCtrlTrgLimit->toctl.bit.CON = D_IM_DISP_CON_EXTERNAL;
	}
	// "CP:im_disp_param_check_ctrl_output() : MIPI 3
	else if (strcmp((kchar*) argv[4], "D4") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_LCD;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		// ovsize error for LCD
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_RGB888_24BIT;
		pOutCtrlTrgLimit->ovsize = 0x2002;
	}
	// "CP:im_disp_param_check_ctrl_output() : MIPI 4
	else if (strcmp((kchar*) argv[4], "D5") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_LCD;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		// ovsize error for LCD
//							if (ctrl->clbhsize * 16 < ohsize) {
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_RGB888_24BIT;
		pOutCtrl->clbhsize = 0x1100;
		pOutCtrlTrgLimit->ohsize = 0x782;
	}
	// "CP:im_disp_param_check_ctrl_output() : MIPI 5
	else if (strcmp((kchar*) argv[4], "D6") == 0)
	{
		// ct_im_disp3_hclk_counter_on(pImDispHclkCounter);
		// IO_DISP.MAIN[block].DCORE.IFS.bit.IFS = D_IM_DISP_IFS_LCD;
		// ct_im_disp3_hclk_counter_off(pImDispHclkCounter);
		// ovsize error for LCD
		pOutCtrlTrgLimit->domd.bit.MODE = D_IM_DISP_MODE_RGB888_24BIT;
		pOutCtrl->doctl2.bit.CTOV = D_IM_DISP_CTOV_AVERAGE;
	}

	switch (argv[2][0])
	{
	case CtImDisp3_D_CT_IM_DISP_NO_PARA:
		error = Im_DISP_Ctrl_Output(block, NULL, NULL);
		break;
	case CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY:
		error = Im_DISP_Ctrl_Output(block, pOutCtrlTrgLimit, NULL);
		break;
	case CtImDisp3_D_CT_IM_DISP_SECOND_PARA_ONLY:
		error = Im_DISP_Ctrl_Output(block, NULL, pOutCtrl);
		break;
	case CtImDisp3_D_CT_IM_DISP_BOTH_PARA:
		error = Im_DISP_Ctrl_Output(block, pOutCtrlTrgLimit, pOutCtrl);
		break;
	default:
		Ddim_Print(("Command parameter error\n"));
		break;
	}
	if (error != D_DDIM_OK)
	{
		Ddim_Print(("Im_DISP_Ctrl_Output error=%08X\n",error));
	}
	else
	{
		Ddim_Print(("------- After Setting -------\n"));
		ct_im_disp3a_dump_regiser(disp3a, E_IM_DISP_SEL_LAYER_DCORE, block);
	}
}
#endif /*CtImDisp_CO_DEBUG_DISP*/

/*
 * PUBLIC
 * */

CtImDisp2b *ct_im_disp2b_new(Disp2bNewParams *disp2NewParams)
{
	CtImDisp2b *self = (CtImDisp2b *) k_object_new_with_private(CT_TYPE_IM_DISP2B,sizeof(CtImDisp2bPrivate));
	CtImDisp2bPrivate *priv = self->privCtImDisp2b;
	priv->params = disp2NewParams;
	return self;
}

