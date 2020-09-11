/*
 *ctimdisp1b.c
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

#include "ctimdisp3.h"
#include "ctimdisp3a.h"

#include "imdisp1group.h"
#include "ctimdisp1b.h"

K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(CtImDisp1b, ct_im_disp1b, IM_TYPE_DISP1_PARENT)
#define CT_IM_DISP1B_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), CtImDisp1bPrivate, CT_TYPE_IM_DISP1B))

struct _CtImDisp1bPrivate
{
	kpointer qwertyu;
};

/*
 * DECLS
 * */
#ifdef CtImDisp_CO_DEBUG_DISP
static kboolean imDisp1bDoPctest_od(ImDisp1Parent *parent, kint32 *pSeqNo);
#endif /*CtImDisp_CO_DEBUG_DISP*/

/*
 * IMPL
 * */
static void ct_im_disp1b_constructor(CtImDisp1b *self)
{
	//CtImDisp1bPrivate *priv = CT_IM_DISP1B_GET_PRIVATE(self);
#ifdef CtImDisp_CO_DEBUG_DISP
	ImDisp1Parent *parent = (ImDisp1Parent *)self;
	parent->pctestFunc = imDisp1bDoPctest_od;
#endif /*CtImDisp_CO_DEBUG_DISP*/
}

static void ct_im_disp1b_destructor(CtImDisp1b *self)
{
}

/*
 * PUBLIC
 * */

#ifdef CtImDisp_CO_DEBUG_DISP
static kboolean imDisp1bDoPctest_od(ImDisp1Parent *parent, kint32 *pSeqNo)
{
//	CtImDisp1b *self = (CtImDisp1b *)parent;
	kint32 seqNo = *pSeqNo;
	ImDisp1Group *imDisp1Group = (ImDisp1Group *)im_disp1_parent_get_group(parent);

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_SR() normal\n", seqNo++));

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LTRG.word = 2;
	IO_DISP.MAIN[0].DCORE.TRG.word = 2;
	IO_DISP.MAIN[0].GRCH[0].GRTRG.word = 2;
	IO_DISP.MAIN[0].GRCH[1].GRTRG.word = 2;
	IO_DISP.MAIN[1].LCH.LTRG.word = 2;
	IO_DISP.MAIN[1].DCORE.TRG.word = 2;
	IO_DISP.MAIN[1].GRCH[0].GRTRG.word = 2;
	IO_DISP.MAIN[1].GRCH[1].GRTRG.word = 2;

	IO_DISP.MAIN[0].LCH.LRST.word = 0;
	IO_DISP.MAIN[0].DCORE.RESET.word = 0;
	IO_DISP.MAIN[0].GRCH[0].GRRST.word = 0;
	IO_DISP.MAIN[0].GRCH[1].GRRST.word = 0;
	IO_DISP.MAIN[1].LCH.LRST.word = 0;
	IO_DISP.MAIN[1].DCORE.RESET.word = 0;
	IO_DISP.MAIN[1].GRCH[0].GRRST.word = 0;
	IO_DISP.MAIN[1].GRCH[1].GRRST.word = 0;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	//E_IM_DISP_SEL_LAYER_MAIN, E_IM_DISP_SEL_LAYER_OSD_1, D_IM_DISP_SR_RESET
	im_disp1_parent_pctest_wrap(parent, "imdisp SetSR 0x0001 0x0008 1");
	//E_IM_DISP_SEL_LAYER_MAIN, E_IM_DISP_SEL_LAYER_OSD_1, D_IM_DISP_SR_RESET
	im_disp1_parent_pctest_wrap(parent, "imdisp SetSR 0x0001 0x0008 0");
	//E_IM_DISP_SEL_LAYER_DCORE, E_IM_DISP_SEL_LAYER_OSD_0, D_IM_DISP_SR_CANCEL
	im_disp1_parent_pctest_wrap(parent, "imdisp SetSR 0x0002 0x0004 1");
	//E_IM_DISP_SEL_LAYER_DCORE, E_IM_DISP_SEL_LAYER_OSD_0, D_IM_DISP_SR_CANCEL
	im_disp1_parent_pctest_wrap(parent, "imdisp SetSR 0x0002 0x0004 0");
	//E_IM_DISP_SEL_LAYER_OSD_0, E_IM_DISP_SEL_LAYER_DCORE, D_IM_DISP_SR_RESET
	im_disp1_parent_pctest_wrap(parent, "imdisp SetSR 0x0004 0x0002 1");
	//E_IM_DISP_SEL_LAYER_OSD_0, E_IM_DISP_SEL_LAYER_DCORE, D_IM_DISP_SR_RESET
	im_disp1_parent_pctest_wrap(parent, "imdisp SetSR 0x0004 0x0002 0");
	//E_IM_DISP_SEL_LAYER_OSD_1, E_IM_DISP_SEL_LAYER_MAIN, D_IM_DISP_SR_CANCEL
	im_disp1_parent_pctest_wrap(parent, "imdisp SetSR 0x0008 0x0001 1");
	//E_IM_DISP_SEL_LAYER_OSD_1, E_IM_DISP_SEL_LAYER_MAIN, D_IM_DISP_SR_CANCEL
	im_disp1_parent_pctest_wrap(parent, "imdisp SetSR 0x0008 0x0001 0");
	//E_IM_DISP_SEL_LAYER_OSD_0, E_IM_DISP_SEL_LAYER_DCORE, D_IM_DISP_SR_RESET
	im_disp1_parent_pctest_wrap(parent, "imdisp SetSR 0x000F 0x000F 1");
	//E_IM_DISP_SEL_LAYER_OSD_0, E_IM_DISP_SEL_LAYER_DCORE, D_IM_DISP_SR_RESET
	im_disp1_parent_pctest_wrap(parent, "imdisp SetSR 0x000F 0x000F 0");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LTRG.word = 3;
	IO_DISP.MAIN[0].DCORE.TRG.word = 3;
	IO_DISP.MAIN[0].GRCH[0].GRTRG.word = 3;
	IO_DISP.MAIN[0].GRCH[1].GRTRG.word = 3;
	IO_DISP.MAIN[1].LCH.LTRG.word = 3;
	IO_DISP.MAIN[1].DCORE.TRG.word = 3;
	IO_DISP.MAIN[1].GRCH[0].GRTRG.word = 3;
	IO_DISP.MAIN[1].GRCH[1].GRTRG.word = 3;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// E_IM_DISP_SEL_LAYER_ALL, E_IM_DISP_SEL_LAYER_ALL, D_IM_DISP_SR_CANCEL
	im_disp1_parent_pctest_wrap(parent, "imdisp SetSR 0x000F 0x000F 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_SR() error\n", seqNo++));
	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LTRG.word = 2;
	IO_DISP.MAIN[0].DCORE.TRG.word = 2;
	IO_DISP.MAIN[0].GRCH[0].GRTRG.word = 2;
	IO_DISP.MAIN[0].GRCH[1].GRTRG.word = 2;
	IO_DISP.MAIN[1].LCH.LTRG.word = 2;
	IO_DISP.MAIN[1].DCORE.TRG.word = 2;
	IO_DISP.MAIN[1].GRCH[0].GRTRG.word = 2;
	IO_DISP.MAIN[1].GRCH[1].GRTRG.word = 2;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	//E_IM_DISP_SEL_LAYER_NONE, E_IM_DISP_SEL_LAYER_NONE, D_IM_DISP_SR_CANCEL
	im_disp1_parent_pctest_wrap(parent, "imdisp SetSR 0x0000 0x0000 0");
	//E_IM_DISP_SEL_LAYER_NONE, E_IM_DISP_SEL_LAYER_NONE, D_IM_DISP_SR_RESET
	im_disp1_parent_pctest_wrap(parent, "imdisp SetSR 0x0000 0x0000 1");
	//E_IM_DISP_SEL_LAYER_ALL, E_IM_DISP_SEL_LAYER_ALL, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetSR 0x000F 0x000F 2");
	//E_IM_DISP_SEL_LAYER_ALL, E_IM_DISP_SEL_LAYER_ALL, Channnel
	im_disp1_parent_pctest_wrap(parent, "imdisp start 0x000F 0x000F 1");
	//E_IM_DISP_SEL_LAYER_ALL, E_IM_DISP_SEL_LAYER_ALL, D_IM_DISP_SR_RESET
	im_disp1_parent_pctest_wrap(parent, "imdisp SetSR 0x000F 0x000F 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_SR() normal\n", seqNo++));
	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LTRG.word = 2;
	IO_DISP.MAIN[0].DCORE.TRG.word = 2;
	IO_DISP.MAIN[0].GRCH[0].GRTRG.word = 2;
	IO_DISP.MAIN[0].GRCH[1].GRTRG.word = 2;
	IO_DISP.MAIN[1].LCH.LTRG.word = 2;
	IO_DISP.MAIN[1].DCORE.TRG.word = 2;
	IO_DISP.MAIN[1].GRCH[0].GRTRG.word = 2;
	IO_DISP.MAIN[1].GRCH[1].GRTRG.word = 2;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	im_disp1_parent_pctest_wrap(parent, "imdisp GetSR 3");	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LRST.word = 1;
	IO_DISP.MAIN[0].DCORE.RESET.word = 0;
	IO_DISP.MAIN[0].GRCH[0].GRRST.word = 1;
	IO_DISP.MAIN[0].GRCH[1].GRRST.word = 0;
	IO_DISP.MAIN[1].LCH.LRST.word = 0;
	IO_DISP.MAIN[1].DCORE.RESET.word = 1;
	IO_DISP.MAIN[1].GRCH[0].GRRST.word = 0;
	IO_DISP.MAIN[1].GRCH[1].GRRST.word = 1;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	im_disp1_parent_pctest_wrap(parent, "imdisp GetSR 3");	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LRST.word = 0;
	IO_DISP.MAIN[0].DCORE.RESET.word = 1;
	IO_DISP.MAIN[0].GRCH[0].GRRST.word = 0;
	IO_DISP.MAIN[0].GRCH[1].GRRST.word = 1;
	IO_DISP.MAIN[1].LCH.LRST.word = 1;
	IO_DISP.MAIN[1].DCORE.RESET.word = 0;
	IO_DISP.MAIN[1].GRCH[0].GRRST.word = 1;
	IO_DISP.MAIN[1].GRCH[1].GRRST.word = 0;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA
	im_disp1_parent_pctest_wrap(parent, "imdisp GetSR 3");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_SR() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA
	im_disp1_parent_pctest_wrap(parent, "imdisp GetSR 0");
	// CtImDisp3_D_CT_IM_DISP_SECOND_PARA_ONLY
	im_disp1_parent_pctest_wrap(parent, "imdisp GetSR 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY
	im_disp1_parent_pctest_wrap(parent, "imdisp GetSR 2");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LRST.word = 0;
	IO_DISP.MAIN[0].DCORE.RESET.word = 0;
	IO_DISP.MAIN[0].GRCH[0].GRRST.word = 0;
	IO_DISP.MAIN[0].GRCH[1].GRRST.word = 0;
	IO_DISP.MAIN[1].LCH.LRST.word = 0;
	IO_DISP.MAIN[1].DCORE.RESET.word = 0;
	IO_DISP.MAIN[1].GRCH[0].GRRST.word = 0;
	IO_DISP.MAIN[1].GRCH[1].GRRST.word = 0;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Parameter_Reflect_Timing() normal\n", seqNo++));

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LTRG.word = 2;
	IO_DISP.MAIN[1].LCH.LTRG.word = 2;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// HDMI setting, E_IM_DISP_RPGTMG_VSYNC_VSYNC
	im_disp1_parent_pctest_wrap(parent, "imdisp SetRefTiming 0 1");
	// LCD setting, E_IM_DISP_RPGTMG_VSYNC_VSYNC
	im_disp1_parent_pctest_wrap(parent, "imdisp SetRefTiming 1 1");
	// HDMI setting, E_IM_DISP_RPGTMG_VSYNC_FRAME_TOP
	im_disp1_parent_pctest_wrap(parent, "imdisp SetRefTiming 0 0");
	// LCD setting, E_IM_DISP_RPGTMG_VSYNC_FRAME_TOP
	im_disp1_parent_pctest_wrap(parent, "imdisp SetRefTiming 1 0");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Parameter_Reflect_Timing() error\n", seqNo++));

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LTRG.word = 3;
	IO_DISP.MAIN[1].LCH.LTRG.word = 3;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// HDMI setting, E_IM_DISP_RPGTMG_VSYNC_VSYNC
	im_disp1_parent_pctest_wrap(parent, "imdisp SetRefTiming 0 1");
	// LCD setting, E_IM_DISP_RPGTMG_VSYNC_VSYNC
	im_disp1_parent_pctest_wrap(parent, "imdisp SetRefTiming 1 1");
	// HDMI setting, E_IM_DISP_RPGTMG_VSYNC_FRAME_TOP
	im_disp1_parent_pctest_wrap(parent, "imdisp SetRefTiming 0 0");
	// LCD setting, E_IM_DISP_RPGTMG_VSYNC_FRAME_TOP
	im_disp1_parent_pctest_wrap(parent, "imdisp SetRefTiming 1 0");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Parameter_Reflect_Timing() normal\n", seqNo++));

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LTRG.word = 2;
	IO_DISP.MAIN[0].LCH.LRPGCTL.bit.RPGTMG = 1;
	IO_DISP.MAIN[1].LCH.LTRG.word = 3;
	IO_DISP.MAIN[1].LCH.LRPGCTL.bit.RPGTMG = 0;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetRefTiming 1 0");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LTRG.word = 3;
	IO_DISP.MAIN[0].LCH.LRPGCTL.bit.RPGTMG = 0;
	IO_DISP.MAIN[1].LCH.LTRG.word = 2;
	IO_DISP.MAIN[1].LCH.LRPGCTL.bit.RPGTMG = 1;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetRefTiming 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Parameter_Reflect_Timing() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetRefTiming 0 0");
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetRefTiming 0 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Input_Data_Transfer() normal\n", seqNo++));
	// HDMI setting, IFMT = D_IM_DISP_LIDT_IFMT_YCC420_RP_8BIT
	im_disp1_parent_pctest_wrap(parent, "imdisp SetITrans 0, 0x00000004, 0x00003721");
	// LCD setting, IFMT = D_IM_DISP_LIDT_IFMT_YCC420_RP_8BIT
	im_disp1_parent_pctest_wrap(parent, "imdisp SetITrans 1, 0x00000004, 0x00003721");
	// HDMI setting, IFMT = D_IM_DISP_LIDT_IFMT_YCC422_RP_8BIT
	im_disp1_parent_pctest_wrap(parent, "imdisp SetITrans 0, 0x00000000, 0x00003721");
	// LCD setting, IFMT = D_IM_DISP_LIDT_IFMT_YCC422_RP_8BIT
	im_disp1_parent_pctest_wrap(parent, "imdisp SetITrans 1, 0x00000000, 0x00003721");
	// HDMI setting, IFMT = D_IM_DISP_LIDT_IFMT_YCC422_RP_12BIT_PACK
	im_disp1_parent_pctest_wrap(parent, "imdisp SetITrans 0, 0x00013201, 0x00003721");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Input_Data_Transfer() error\n", seqNo++));
	//LCD setting, IFMT = D_IM_DISP_LIDT_IFMT_YCC422_RP_12BIT_PACK
	im_disp1_parent_pctest_wrap(parent, "imdisp SetITrans 1, 0x00013201, 0x00003721");
	//HDMI setting, IFMT = D_IM_DISP_LIDT_IFMT_YCC422_RP_16BIT
	im_disp1_parent_pctest_wrap(parent, "imdisp SetITrans 0, 0x00013202, 0x00003721");
	//LCD setting, IFMT = D_IM_DISP_LIDT_IFMT_YCC422_RP_16BIT
	im_disp1_parent_pctest_wrap(parent, "imdisp SetITrans 1, 0x00013202, 0x00003721");
	//HDMI setting, IFMT = D_IM_DISP_LIDT_IFMT_YCC422_RP_10BIT_PACK
	im_disp1_parent_pctest_wrap(parent, "imdisp SetITrans 0, 0x00013203, 0x00003721");
	//LCD setting, IFMT = D_IM_DISP_LIDT_IFMT_YCC422_RP_10BIT_PACK
	im_disp1_parent_pctest_wrap(parent, "imdisp SetITrans 1, 0x00013203, 0x00003721");
	//HDMI setting, IFMT = D_IM_DISP_LIDT_IFMT_YCC420_RP_10BIT_PACK
	im_disp1_parent_pctest_wrap(parent, "imdisp SetITrans 0, 0x00013207, 0x00003721");
	//LCD setting, IFMT = D_IM_DISP_LIDT_IFMT_YCC420_RP_10BIT_PACK
	im_disp1_parent_pctest_wrap(parent, "imdisp SetITrans 1, 0x00013207, 0x00003721");
	//HDMI setting, IFMT = D_IM_DISP_LIDT_IFMT_GENERAL_8BIT
	im_disp1_parent_pctest_wrap(parent, "imdisp SetITrans 0, 0x00013208, 0x00003721");
	//LCD setting, IFMT = D_IM_DISP_LIDT_IFMT_GENERAL_8BIT
	im_disp1_parent_pctest_wrap(parent, "imdisp SetITrans 1, 0x00013208, 0x00003721");
	//HDMI setting, IFMT = D_IM_DISP_LIDT_IFMT_GENERAL_16BIT
	im_disp1_parent_pctest_wrap(parent, "imdisp SetITrans 0, 0x0001320a, 0x00003721");
	//LCD setting, IFMT = D_IM_DISP_LIDT_IFMT_GENERAL_16BIT
	im_disp1_parent_pctest_wrap(parent, "imdisp SetITrans 1, 0x0001320a, 0x00003721");
	//HDMI setting, IFMT = D_IM_DISP_LIDT_IFMT_GENERAL_10BIT
	im_disp1_parent_pctest_wrap(parent, "imdisp SetITrans 0, 0x0001320b, 0x00003721");
	//LCD setting, IFMT = D_IM_DISP_LIDT_IFMT_GENERAL_10BIT
	im_disp1_parent_pctest_wrap(parent, "imdisp SetITrans 1, 0x0001320b, 0x00003721");
	//HDMI setting, IFMT = D_IM_DISP_LIDT_IFMT_GENERAL_10BITx2
	im_disp1_parent_pctest_wrap(parent, "imdisp SetITrans 0, 0x0001321b, 0x00003721");
	//LCD setting, IFMT = D_IM_DISP_LIDT_IFMT_GENERAL_10BITx2
	im_disp1_parent_pctest_wrap(parent, "imdisp SetITrans 1, 0x0001321b, 0x00003721");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Input_Data_Transfer() normal\n", seqNo++));
	// HDMI setting, IFMT = D_IM_DISP_LIDT_IFMT_YCC422_RP_8BIT
	im_disp1_parent_pctest_wrap(parent, "imdisp SetITrans 0, 0x00000000, 0x00003720");
	// LCD setting, IFMT = D_IM_DISP_LIDT_IFMT_YCC420_RP_8BIT
	im_disp1_parent_pctest_wrap(parent, "imdisp SetITrans 1, 0x00000004, 0x00003721");

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetITrans 1 0");
// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetITrans 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Input_Data_Transfer() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetITrans 0 0");
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetITrans 0 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Input_Size() normal\n", seqNo++));
	// HDMI setting, U_IM_DISP_SIZE width=128 lines=16
	im_disp1_parent_pctest_wrap(parent, "imdisp SetISize 0 0x00100080");
	// LCD setting, U_IM_DISP_SIZE width=130 lines=18
	im_disp1_parent_pctest_wrap(parent, "imdisp SetISize 1 0x00120082");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Input_Size() error\n", seqNo++));
	// HDMI setting, U_IM_DISP_SIZE width=128 lines=14
	im_disp1_parent_pctest_wrap(parent, "imdisp SetISize 0 0x000E0080");
	// HDMI setting, U_IM_DISP_SIZE width=128 lines=19
	im_disp1_parent_pctest_wrap(parent, "imdisp SetISize 0 0x00130080");
	// LCD setting, U_IM_DISP_SIZE width=130 lines=18
	im_disp1_parent_pctest_wrap(parent, "imdisp SetISize 1 0x0010007E");
	// LCD setting, U_IM_DISP_SIZE width=130 lines=18
	im_disp1_parent_pctest_wrap(parent, "imdisp SetISize 1 0x00100081");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Input_Size() normal\n", seqNo++));
	// HDMI setting, U_IM_DISP_SIZE width=128 lines=16
	im_disp1_parent_pctest_wrap(parent, "imdisp SetISize 0 0x00100080");
	// LCD setting, U_IM_DISP_SIZE width=130 lines=18
	im_disp1_parent_pctest_wrap(parent, "imdisp SetISize 1 0x00120082");

// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetISize 1 0");
// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetISize 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Input_Size() error\n", seqNo++));
// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetISize 0 0");
// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetISize 0 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Addr() normal\n", seqNo++));
	// E_IM_DISP_BANK_00, y_addr, c_addr
	im_disp1_parent_pctest_wrap(parent, "imdisp SetAdd 1 0 0 0xAFFFFFFF 0xBFFFFFFF");
	// E_IM_DISP_BANK_01, y_addr, c_addr
	im_disp1_parent_pctest_wrap(parent, "imdisp SetAdd 1 0 1 0xCFFFFFFF 0xDFFFFFFF");
	// E_IM_DISP_BANK_10, y_addr, c_addr
	im_disp1_parent_pctest_wrap(parent, "imdisp SetAdd 1 0 2 0xEFFFFFFF 0xFFFFFFFF");
	// E_IM_DISP_BANK_11, y_addr, c_addr
	im_disp1_parent_pctest_wrap(parent, "imdisp SetAdd 1 0 3 0x1FFFFFFF 0x2FFFFFFF");
	// E_IM_DISP_BANK_00, y_addr, c_addr
	im_disp1_parent_pctest_wrap(parent, "imdisp SetAdd 1 1 0 0xAFFFFFFF 0xBFFFFFFF");
	// E_IM_DISP_BANK_01, y_addr, c_addr
	im_disp1_parent_pctest_wrap(parent, "imdisp SetAdd 1 1 1 0xCFFFFFFF 0xDFFFFFFF");
	// E_IM_DISP_BANK_10, y_addr, c_addr
	im_disp1_parent_pctest_wrap(parent, "imdisp SetAdd 1 1 2 0xEFFFFFFF 0xFFFFFFFF");
	// E_IM_DISP_BANK_11, y_addr, c_addr
	im_disp1_parent_pctest_wrap(parent, "imdisp SetAdd 1 1 3 0x1FFFFFFF 0x2FFFFFFF");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Addr() error\n", seqNo++));
// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting, Band = 1, y_addr, c_addr
	im_disp1_parent_pctest_wrap(parent, "imdisp SetAdd 0 0 1 0xCFFFFFFF 0xDFFFFFFF");
// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting, Band = 3, y_addr, c_addr
	im_disp1_parent_pctest_wrap(parent, "imdisp SetAdd 0 1 3 0x1FFFFFFF 0x2FFFFFFF");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Addr() normal\n", seqNo++));
	// E_IM_DISP_BANK_00, y_addr, c_addr
	im_disp1_parent_pctest_wrap(parent, "imdisp SetAdd 1 0 0 0xAFFFFFF0 0xBFFFFFF0");
	// E_IM_DISP_BANK_01, y_addr, c_addr
	im_disp1_parent_pctest_wrap(parent, "imdisp SetAdd 1 0 1 0xCFFFFFF0 0xDFFFFFF0");
	// E_IM_DISP_BANK_10, y_addr, c_addr
	im_disp1_parent_pctest_wrap(parent, "imdisp SetAdd 1 0 2 0xEFFFFFF0 0xFFFFFFF0");
	// E_IM_DISP_BANK_11, y_addr, c_addr
	im_disp1_parent_pctest_wrap(parent, "imdisp SetAdd 1 0 3 0x1FFFFFF0 0x2FFFFFF0");
	// E_IM_DISP_BANK_00, y_addr, c_addr
	im_disp1_parent_pctest_wrap(parent, "imdisp SetAdd 1 1 0 0xAFFFFFF1 0xBFFFFFF1");
	// E_IM_DISP_BANK_01, y_addr, c_addr
	im_disp1_parent_pctest_wrap(parent, "imdisp SetAdd 1 1 1 0xCFFFFFF1 0xDFFFFFF1");
	// E_IM_DISP_BANK_10, y_addr, c_addr
	im_disp1_parent_pctest_wrap(parent, "imdisp SetAdd 1 1 2 0xEFFFFFF1 0xFFFFFFF1");
	// E_IM_DISP_BANK_11, y_addr, c_addr
	im_disp1_parent_pctest_wrap(parent, "imdisp SetAdd 1 1 3 0x1FFFFFF1 0x2FFFFFF1");

// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Band = 0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetAdd 1 0 0");
// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Band = 1
	im_disp1_parent_pctest_wrap(parent, "imdisp GetAdd 1 0 1");
// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Band = 2
	im_disp1_parent_pctest_wrap(parent, "imdisp GetAdd 1 0 2");
// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Band = 3
	im_disp1_parent_pctest_wrap(parent, "imdisp GetAdd 1 0 3");
// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Band = 0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetAdd 1 1 0");
// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Band = 1
	im_disp1_parent_pctest_wrap(parent, "imdisp GetAdd 1 1 1");
// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Band = 2
	im_disp1_parent_pctest_wrap(parent, "imdisp GetAdd 1 1 2");
// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Band = 3
	im_disp1_parent_pctest_wrap(parent, "imdisp GetAdd 1 1 3");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Addr() error\n", seqNo++));
// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting, Band = 0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetAdd 0 0 0");
// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting, Band = 3
	im_disp1_parent_pctest_wrap(parent, "imdisp GetAdd 0 1 3");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Lfd() normal\n", seqNo++));
	// HDMI setting, y_hga = 2(min), c_hga = 2(min)
	im_disp1_parent_pctest_wrap(parent, "imdisp SetLfd 0 2 2");
	// LCD setting, y_hga = 2(min), c_hga = 2(min)
	im_disp1_parent_pctest_wrap(parent, "imdisp SetLfd 1 2 2");
	// HDMI setting, y_hga = 65534(max), c_hga = 65534(max)
	im_disp1_parent_pctest_wrap(parent, "imdisp SetLfd 0 65534 65534");
	// HDMI setting, y_hga = 65534(max), c_hga = 65534(max)
	im_disp1_parent_pctest_wrap(parent, "imdisp SetLfd 1 65534 65534");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Lfd() error\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp SetLfd 0 0 2");	// HDMI setting, y_hga = 0, c_hga = 2(min)
	im_disp1_parent_pctest_wrap(parent, "imdisp SetLfd 1 2 0");	// LCD setting, y_hga = 2(min), c_hga = 0
	// HDMI setting, y_hga = 1200, c_hga = 65535
	im_disp1_parent_pctest_wrap(parent, "imdisp SetLfd 0 1200 65535");
	// LCD setting, y_hga = 65535, c_hga = 3000
	im_disp1_parent_pctest_wrap(parent, "imdisp SetLfd 1 65535 3000");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Lfd() normal\n", seqNo++));
	// HDMI setting, y_hga = 2(min), c_hga = 2(min)
	im_disp1_parent_pctest_wrap(parent, "imdisp SetLfd 0 2 4");
	// HDMI setting, y_hga = 65534(max), c_hga = 65534(max)
	im_disp1_parent_pctest_wrap(parent, "imdisp SetLfd 1 65532 65534");

// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetLfd 3 0");
// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetLfd 3 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Lfd() error\n", seqNo++));
// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetLfd 0 1");
// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetLfd 1 0");
// CtImDisp3_D_CT_IM_DISP_SECOND_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetLfd 2 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Main_Bank()\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp SetMBank 0 1");	// HDMI setting, E_IM_DISP_BANK_01
	im_disp1_parent_pctest_wrap(parent, "imdisp SetMBank 0 2");	// HDMI setting, E_IM_DISP_BANK_10
	im_disp1_parent_pctest_wrap(parent, "imdisp SetMBank 0 3");	// HDMI setting, E_IM_DISP_BANK_11
	im_disp1_parent_pctest_wrap(parent, "imdisp SetMBank 0 0");	// HDMI setting, E_IM_DISP_BANK_00
	im_disp1_parent_pctest_wrap(parent, "imdisp SetMBank 1 1");	// LCD setting, E_IM_DISP_BANK_01
	im_disp1_parent_pctest_wrap(parent, "imdisp SetMBank 1 2");	// LCD setting, E_IM_DISP_BANK_10
	im_disp1_parent_pctest_wrap(parent, "imdisp SetMBank 1 3");	// LCD setting, E_IM_DISP_BANK_11
	im_disp1_parent_pctest_wrap(parent, "imdisp SetMBank 1 0");	// LCD setting, E_IM_DISP_BANK_00

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Main_Bank() normal\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp SetMBank 0 1");	// HDMI setting, E_IM_DISP_BANK_01
	im_disp1_parent_pctest_wrap(parent, "imdisp SetMBank 1 2");	// LCD setting, E_IM_DISP_BANK_10

	im_disp1_parent_pctest_wrap(parent, "imdisp GetMBank 1 0");
// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetMBank 1 1");
// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Main_Bank() error\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp GetMBank 0 0");
// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetMBank 0 1");
// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Main_Bank_Monitor() normal\n", seqNo++));
	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LIBCTL.bit.IBMNT = 1;
	IO_DISP.MAIN[1].LCH.LIBCTL.bit.IBMNT = 3;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	im_disp1_parent_pctest_wrap(parent, "imdisp GetMBkMon 1 0");
// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetMBkMon 1 1");
// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Main_Bank_Monitor() error\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp GetMBkMon 0 0");
// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetMBkMon 0 1");
// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Resize() normal\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp SetRes 1 0 0x00000000 0x0000050a 0x0000050a 0x00000000");
// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, lrsz0, lrsz1, lrsz2, lrsz3
	im_disp1_parent_pctest_wrap(parent, "imdisp SetRes 1 1 0x00000001 0x0800050a 0x06000514 0x00003214");
// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, lrsz0, lrsz1, lrsz2, lrsz3

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Resize() error\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp SetRes 1 0 0x00000000 0x01001e02 0x0100050a 0x00000000");
// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, lrsz0, lrsz1, lrsz2, lrsz3
	im_disp1_parent_pctest_wrap(parent, "imdisp SetRes 1 1 0x00000000 0x0000021e 0x0000050a 0x00000000");
// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, lrsz0, lrsz1, lrsz2, lrsz3
	im_disp1_parent_pctest_wrap(parent, "imdisp SetRes 1 0 0x00000000 0x0100050a 0x0000050a 0x00000000");
// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, lrsz0, lrsz1, lrsz2, lrsz3
	im_disp1_parent_pctest_wrap(parent, "imdisp SetRes 1 1 0x00000001 0x01000a0a 0x0000050a 0x00000000");
// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, lrsz0, lrsz1, lrsz2, lrsz3
	im_disp1_parent_pctest_wrap(parent, "imdisp SetRes 1 0 0x00000001 0x1400050a 0x0100050a 0x00000F14");
// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, lrsz0, lrsz1, lrsz2, lrsz3
	im_disp1_parent_pctest_wrap(parent, "imdisp SetRes 1 1 0x00000000 0x0000050a 0x01001e02 0x00000000");
// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, lrsz0, lrsz1, lrsz2, lrsz3
	im_disp1_parent_pctest_wrap(parent, "imdisp SetRes 1 0 0x00000000 0x0000050a 0x0000021e 0x00000000");
// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, lrsz0, lrsz1, lrsz2, lrsz3
	im_disp1_parent_pctest_wrap(parent, "imdisp SetRes 1 1 0x00000000 0x0000050a 0x0100050a 0x00000000");
// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, lrsz0, lrsz1, lrsz2, lrsz3
	im_disp1_parent_pctest_wrap(parent, "imdisp SetRes 1 0 0x00000001 0x0000050a 0x01000a0a 0x00000000");
// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, lrsz0, lrsz1, lrsz2, lrsz3
	im_disp1_parent_pctest_wrap(parent, "imdisp SetRes 1 1 0x00000001 0x0000050a 0x1400050a 0x00000F00");
// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, lrsz0, lrsz1, lrsz2, lrsz3
	im_disp1_parent_pctest_wrap(parent, "imdisp SetRes 1 0 0x00000000 0x0000050a 0x0000050a 0x0000000F");
// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, lrsz0, lrsz1, lrsz2, lrsz3
	im_disp1_parent_pctest_wrap(parent, "imdisp SetRes 1 0 0x00000000 0x0000050a 0x0000050a 0x00003F00");
// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, lrsz0, lrsz1, lrsz2, lrsz3
	im_disp1_parent_pctest_wrap(parent, "imdisp SetRes 0 1 0x00000001 0x0800050a 0x06000514 0x00003214");
// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting, lrsz0, lrsz1, lrsz2, lrsz3

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Resize() normal\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp SetRes 1 0 0x00000000 0x0000050a 0x00000514 0x00000000");
// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, lrsz0, lrsz1, lrsz2, lrsz3
	im_disp1_parent_pctest_wrap(parent, "imdisp SetRes 1 1 0x00000001 0x0800050a 0x06000514 0x00003214");
// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, lrsz0, lrsz1, lrsz2, lrsz3

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetRes 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetRes 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Resize() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetRes 0 0");
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetRes 0 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Yhlp() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, lyhlpcl, lyhlpk0, lyhlpk1, lyhlpol, lyhlpclr
	im_disp1_parent_pctest_wrap(parent, "imdisp SetYhlp 1 0 0x80c00000 0x01FF0077 "
			"0x02FF0077 0x55556666 0x1111222233334444");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, lyhlpcl, lyhlpk0, lyhlpk1, lyhlpol, lyhlpclr
	im_disp1_parent_pctest_wrap(parent, "imdisp SetYhlp 1 1 0x80c00000 0x01FF0011 "
			"0x02FF0011 0x22223333 0x4444555566667777");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Yhlp() error\n", seqNo++));
// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting, lyhlpcl, lyhlpk0, lyhlpk1, lyhlpol, lyhlpclr
	im_disp1_parent_pctest_wrap(parent, "imdisp SetYhlp 0 0 0x80c00000 0x01FF0011 "
			"0x02FF0077 0x22223333 0x4444555566667777");
// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting, lyhlpcl, lyhlpk0, lyhlpk1, lyhlpol, lyhlpclr
	im_disp1_parent_pctest_wrap(parent, "imdisp SetYhlp 0 1 0x80c00000 0x01FF0077 "
			"0x02FF0011 0x55556666 0x1111222233334444");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Yhlp() normal\n", seqNo++));
// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, lyhlpcl, lyhlpk0, lyhlpk1, lyhlpol, lyhlpclr
	im_disp1_parent_pctest_wrap(parent, "imdisp SetYhlp 1 0 0x80c00000 0x01FF0077 "
			"0x02FF0077 0x55556666 0x1111222233334444");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, lyhlpcl, lyhlpk0, lyhlpk1, lyhlpol, lyhlpclr
	im_disp1_parent_pctest_wrap(parent, "imdisp SetYhlp 1 1 0x80c00000 0x01FF0011 "
			"0x02FF0011 0x22223333 0x4444555566667777");

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetYhlp 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetYhlp 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Yhlp() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetYhlp 0 0");
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetYhlp 0 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Warning() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetWrng 1 0 0x00000301 0x00010002 0xFFF3FFF4 0x00000003 "
			"0xFFF5FFF60000FFF8 0xFFF9FFFA0000FFFC 0x00000003 0xFFFDFFFE0000FFF0 0xEEE1EEE20000EEE3 0x00000001");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetWrng 1 1 0x00000301 0x00010002 0x00030004 0x00000003 "
			"0x0005000600000008 0x0009000A0000000C 0x00000003 0x000D000E00000001 0x0001000200000003 0x00000001");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Warning() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetWrng 0 1 0 0 0 0 0 0 0 0 0 0");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetWrng 1 0 0x00000301 0x00050002 0xFFF3FFF4 0x00000003 "
			"0xFFF5FFF60000FFF8 0xFFF9FFFA0000FFFC 0x00000003 0xFFFDFFFE0000FFF0 0xEEE1EEE20000EEE3 0x00000001");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetWrng 1 1 0x00000301 0x00010002 0xFFF9FFF4 0x00000003 "
			"0xFFF5FFF60000FFF8 0xFFF9FFFA0000FFFC 0x00000003 0xFFFDFFFE0000FFF0 0xEEE1EEE20000EEE3 0x00000001");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetWrng 1 0 0x00000001 0x00010002 0xFFF3FFF4 0x00000002 "
			"0xFFF5FFF60000FFF8 0xFFF9FFFA0000FFFC 0x00000003 0xFFFDFFFE0000FFF0 0xEEE1EEE20000EEE3 0x00000001");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetWrng 1 1 0x00000001 0x00010002 0xFFF3FFF4 0x00000003 "
			"0xFFF5FFF60000FFF8 0xFFF9FFFA0000FFFC 0x00000003 0xFFFDFFFE0000FFF0 0xEEE1EEE20000EEE3 0x00000001");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetWrng 1 0 0x00000101 0x00010002 0xFFF3FFF4 0x00000002 "
			"0xFFF5FFF60000FFF8 0xFFF9FFFA0000FFFC 0x00000003 0xFFFDFFFE0000FFF0 0xEEE1EEE20000EEE3 0x00000001");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetWrng 1 1 0x00000101 0x00010002 0xFFF3FFF4 0x00000003 "
			"0xFFF5FFF60000FFF8 0xFFF9FFFA0000FFFC 0x00000003 0xFFFDFFFE0000FFF0 0xEEE1EEE20000EEE3 0x00000001");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetWrng 1 0 0x00000001 0x00010002 0xFFF3FFF4 0x00000001 "
			"0xFFF5FFF60000FFF8 0xFFF9FFFA0000FFFC 0x00000002 0xFFFDFFFE0000FFF0 0xEEE1EEE20000EEE3 0x00000001");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetWrng 1 1 0x00000001 0x00010002 0xFFF3FFF4 0x00000001 "
			"0xFFF5FFF60000FFF8 0xFFF9FFFA0000FFFC 0x00000003 0xFFFDFFFE0000FFF0 0xEEE1EEE20000EEE3 0x00000001");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetWrng 1 1 0x00000101 0x00010002 0xFFF3FFF4 0x00000001 "
			"0xFFF5FFF60000FFF8 0xFFF9FFFA0000FFFC 0x00000002 0xFFFDFFFE0000FFF0 0xEEE1EEE20000EEE3 0x00000001");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetWrng 1 0 0x00000101 0x00010002 0xFFF3FFF4 0x00000001 "
			"0xFFF5FFF60000FFF8 0xFFF9FFFA0000FFFC 0x00000003 0xFFFDFFFE0000FFF0 0xEEE1EEE20000EEE3 0x00000001");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetWrng 1 1 0x00000301 0x00010002 0xFFF3FFF4 0x00000001 "
			"0xFFF5FFF60000FFF8 0xFFF9FFFA0000FFFC 0x00000001 0xFFFDFFFE0000FFF0 0xEEE1EEE20000EEE3 0x00000002");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetWrng 1 0 0x00000301 0x00010002 0xFFF3FFF4 0x00000001 "
			"0xFFF5FFF60000FFF8 0xFFF9FFFA0000FFFC 0x00000001 0xFFFDFFFE0000FFF0 0xEEE1EEE20000EEE3 0x00000005");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Warning() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetWrng 1 0 0x00000301 0x00010002 0xFFF3FFF4 0x00000003 "
			"0xFFF5FFF60000FFF8 0xFFF9FFFA0000FFFC 0x00000003 0xFFFDFFFE0000FFF0 0xEEE1EEE20000EEE3 0x00000001");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetWrng 1 1 0x00000301 0x00010002 0x00030004 0x00000003 "
			"0x0005000600000008 0x0009000A0000000C 0x00000003 0x000D000E00000001 0x0001000200000003 0x00000001");

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetWrng 1 0");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetWrng 1 1");	

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Warning() error\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp GetWrng 0 0");	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetWrng 0 1");	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Blink_Timer()\n", seqNo++));
	// HDMI setting, Normal(BTIMH/BTIML/BTIMD)
	im_disp1_parent_pctest_wrap(parent, "imdisp SetBTim 0 0x0001F1F2");	
	// LCD setting, Normal(BTIMH/BTIML/BTIMD)
	im_disp1_parent_pctest_wrap(parent, "imdisp SetBTim 1 0x00013F3F");	

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Blink_Timer() normal\n", seqNo++));
	// HDMI setting, Normal(BTIMH/BTIML/BTIMD)
	im_disp1_parent_pctest_wrap(parent, "imdisp SetBTim 0 0x0001F1F2");	
	// LCD setting, Normal(BTIMH/BTIML/BTIMD)
	im_disp1_parent_pctest_wrap(parent, "imdisp SetBTim 1 0x00013F3F");	

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetBTim 1 0");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetBTim 1 1");	

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Blink_Timer() error\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp GetBTim 0 0");	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetBTim 0 1");	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Zebra() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, LZBWID, LZBV, LZBPT
	im_disp1_parent_pctest_wrap(parent, "imdisp SetZebra 1 0 0x00000203 0x00000100 0x00000001");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, LZBWID, LZBV, LZBPT
	im_disp1_parent_pctest_wrap(parent, "imdisp SetZebra 1 1 0x0000F2F3 0x00000001 0x00000000");	

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Zebra() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting, LZBWID, LZBV, LZBPT
	im_disp1_parent_pctest_wrap(parent, "imdisp SetZebra 0 0 0x00000102 0x00000101 0x00000001");	
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting, LZBWID, LZBV, LZBPT
	im_disp1_parent_pctest_wrap(parent, "imdisp SetZebra 0 1 0x00000201 0x00000101 0x00000001");	
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting, LZBWID, LZBV, LZBPT
	im_disp1_parent_pctest_wrap(parent, "imdisp SetZebra 1 0 0x00000102 0x00000101 0x00000001");	
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting, LZBWID, LZBV, LZBPT
	im_disp1_parent_pctest_wrap(parent, "imdisp SetZebra 1 1 0x00000201 0x00000101 0x00000001");	

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Zebra() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, LZBWID, LZBV, LZBPT
	im_disp1_parent_pctest_wrap(parent, "imdisp SetZebra 1 0 0x00000203 0x00000100 0x00000001");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, LZBWID, LZBV, LZBPT
	im_disp1_parent_pctest_wrap(parent, "imdisp SetZebra 1 1 0x0000F2F3 0x00000001 0x00000000");	

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetZebra 1 0");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetZebra 1 1");	

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Zebra() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetZebra 0 0");	
	im_disp1_parent_pctest_wrap(parent, "imdisp GetZebra 0 1");	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Matrix() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetMax 1 0 "
			"0xE001F0000000F002 0xE011F0100000F012 0xE021E0200000E022");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetMax 1 1 "
			"0xE101F1000000F102 0xE111F1100000F112 0xE121E1200000E122");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetMax 1 0 "
			"0x0000000000000000 0x0000000000000000 0x0000000000000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetMax 1 1 "
			"0x0000000000000000 0x0000000000000000 0x0000000000000000");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Matrix() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetMax 0 0 "
			"0xF001F0000000F002 0xF011F0100000F012 0xF021F0200000F022");
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetMax 0 1 "
			"0xF101F1000000F102 0xF111F1100000F112 0xF121F1200000F122");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Matrix() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetMax 1 0 "
			"0xE001F0000000F002 0xE011F0100000F012 0xE021E0200000E022");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetMax 1 1 "
			"0xE101F1000000F102 0xE111F1100000F112 0xE121E1200000E122");

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetMax 1 0");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetMax 1 1");	

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Matrix() error\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp GetMax 0 0");	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetMax 0 1");	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Gamma_Enable() normal\n", seqNo++));

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LTRG.word = 2;
	IO_DISP.MAIN[0].LCH.LTBLASET.word = 0;
	IO_DISP.MAIN[0].DCORE.TRG.word = 2;
	IO_DISP.MAIN[0].DCORE.TBLASET.word = 0;
	IO_DISP.MAIN[1].LCH.LTRG.word = 2;
	IO_DISP.MAIN[1].LCH.LTBLASET.word = 0;
	IO_DISP.MAIN[1].DCORE.TRG.word = 2;
	IO_DISP.MAIN[1].DCORE.TBLASET.word = 0;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 0 0x01 1 0 0");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 0 0x02 1 0 0");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 0 0x04 1 0 0");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 0 0x08 1 0 0");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 0 0x10 1 0 0");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 0 0x01 1 0 1");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 0 0x02 1 0 1");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 0 0x04 1 0 1");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 0 0x08 1 0 1");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 0 0x10 1 0 1");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 0 0x01 1 1 1");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 0 0x02 1 1 1");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 0 0x04 1 1 1");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 0 0x08 1 1 1");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 0 0x10 1 1 1");	

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LTRG.word = 3;
	IO_DISP.MAIN[0].LCH.LTBLASET.word = 0;
	IO_DISP.MAIN[0].DCORE.TRG.word = 3;
	IO_DISP.MAIN[0].DCORE.TBLASET.word = 0;
	IO_DISP.MAIN[1].LCH.LTRG.word = 3;
	IO_DISP.MAIN[1].LCH.LTBLASET.word = 0;
	IO_DISP.MAIN[1].DCORE.TRG.word = 3;
	IO_DISP.MAIN[1].DCORE.TBLASET.word = 0;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 1 0x01 1 0 0");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 1 0x02 1 0 0");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 1 0x04 1 0 0");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 1 0x08 1 0 0");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 1 0x10 1 0 0");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 1 0x01 1 0 1");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 1 0x02 1 0 1");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 1 0x04 1 0 1");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 1 0x08 1 0 1");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 1 0x10 1 0 1");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 1 0x01 1 1 1");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 1 0x02 1 1 1");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 1 0x04 1 1 1");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 1 0x08 1 1 1");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 1 0x10 1 1 1");	

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Gamma_Enable() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 0 0 0x01 1 0 0");	
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 0 1 0x02 1 0 0");	

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LTRG.word = 3;
	IO_DISP.MAIN[0].LCH.LTBLASET.word = 0;
	IO_DISP.MAIN[0].DCORE.TRG.word = 3;
	IO_DISP.MAIN[0].DCORE.TBLASET.word = 0;
	IO_DISP.MAIN[1].LCH.LTRG.word = 3;
	IO_DISP.MAIN[1].LCH.LTBLASET.word = 0;
	IO_DISP.MAIN[1].DCORE.TRG.word = 3;
	IO_DISP.MAIN[1].DCORE.TBLASET.word = 0;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 0 0x01 0 1 1");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 1 0x02 0 1 1");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 0 0x04 0 1 1");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 1 0x08 0 1 1");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 0 0x10 0 1 1");	

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Gamma_Enable() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 0 0x01 1 1 1");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 0 0x08 1 1 1");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 1 0x08 1 1 1");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamEn 1 1 0x10 1 1 1");	

	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetGamEn 3 0");	
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetGamEn 3 1");	

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Gamma_Enable() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetGamEn 0 0");	
	im_disp1_parent_pctest_wrap(parent, "imdisp GetGamEn 0 1");	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetGamEn 1 0");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetGamEn 1 1");	
	// CtImDisp3_D_CT_IM_DISP_SECOND_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetGamEn 2 0");	
	// CtImDisp3_D_CT_IM_DISP_SECOND_PARA_ONLY, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetGamEn 2 1");	

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Gamma_Mode() normal\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamMod 0 1");	// HDMI setting, GMMD
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGamMod 1 1");	// LCD setting, GMMD

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Gamma_Mode() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, GMMD
	im_disp1_parent_pctest_wrap(parent, "imdisp GetGamMod 1 0");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, GMMD
	im_disp1_parent_pctest_wrap(parent, "imdisp GetGamMod 1 1");	

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Gamma_Mode() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting, GMMD
	im_disp1_parent_pctest_wrap(parent, "imdisp GetGamMod 0 0");	
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting, GMMD
	im_disp1_parent_pctest_wrap(parent, "imdisp GetGamMod 0 1");	

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Alpha_Value() normal\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp SetAlpVal 0 0x00000001");	// HDMI setting, lalp
	im_disp1_parent_pctest_wrap(parent, "imdisp SetAlpVal 1 0x00000001");	// LCD setting, lalp

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Alpha_Value() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetAlpVal 1 0");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetAlpVal 1 1");	

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Alpha_Value() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetAlpVal 0 0");	
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetAlpVal 0 1");	

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Display_Position() normal\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp SetPos 0 0x00000000");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetPos 0 0x345689aa");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetPos 1 0x00000000");	// LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetPos 1 0x345899ac");	// LCD setting, Normal

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Display_Position() error\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp SetPos 0 0x345789aa");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetPos 1 0x345699ab");	// LCD setting, Normal

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Display_Position() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetPos 1 0");	
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetPos 1 1");	

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Display_Position() error\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp GetPos 0 0");	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetPos 0 1");	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting

	*pSeqNo = seqNo;
	return ktrue;
}
#endif /*CtImDisp_CO_DEBUG_DISP*/

CtImDisp1b *ct_im_disp1b_new()
{
	CtImDisp1b *self = (CtImDisp1b *) k_object_new_with_private(CT_TYPE_IM_DISP1B,sizeof(CtImDisp1bPrivate));
	if(!self){//Ddim_Assertion(self)
		Ddim_Print(("!! new CtImDisp1b NULL: %s (%d)", __FILE__, __LINE__));
		return NULL;
	}
	return self;
}
