/*
 *ctimdisp1a.c
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
#include "ctimdisp1a.h"

K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(CtImDisp1a, ct_im_disp1a, IM_TYPE_DISP1_PARENT)
#define CT_IM_DISP1A_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), CtImDisp1aPrivate, CT_TYPE_IM_DISP1A))

struct _CtImDisp1aPrivate
{
	kpointer qwertyu;
};

/*
 * DECLS
 * */
#ifdef CtImDisp_CO_DEBUG_DISP
static kboolean imDisp1aDoPctest_od(ImDisp1Parent *parent, kint32 *pSeqNo);
#endif /*CtImDisp_CO_DEBUG_DISP*/

/*
 * IMPL
 * */
static void ct_im_disp1a_constructor(CtImDisp1a *self)
{
	//CtImDisp1aPrivate *priv = CT_IM_DISP1A_GET_PRIVATE(self);
#ifdef CtImDisp_CO_DEBUG_DISP
	ImDisp1Parent *parent = (ImDisp1Parent *)self;
	parent->pctestFunc = imDisp1aDoPctest_od;
#endif /*CtImDisp_CO_DEBUG_DISP*/
}

static void ct_im_disp1a_destructor(CtImDisp1a *self)
{
}

/*
 * PUBLIC
 * */

#ifdef CtImDisp_CO_DEBUG_DISP
static kboolean imDisp1aDoPctest_od(ImDisp1Parent *parent, kint32 *pSeqNo)
{
//	CtImDisp1a *self = (CtImDisp1a *)parent;
	kint32 seqNo = *pSeqNo;
	ImDisp1Group *imDisp1Group = (ImDisp1Group *)im_disp1_parent_get_group(parent);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDg 1 0 0x0004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDg 1 0 0x0008");
	// CtImDisp3_D_CT_IM_DISP_SECOND_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDg 2 0 0x0004");
	// CtImDisp3_D_CT_IM_DISP_SECOND_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDg 2 0 0x0008");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDg 3 0 0x0004");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDg 3 0 0x0008");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDg 1 1 0x0004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDg 1 1 0x0008");
	// CtImDisp3_D_CT_IM_DISP_SECOND_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDg 2 1 0x0004");
	// CtImDisp3_D_CT_IM_DISP_SECOND_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDg 2 1 0x0008");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDg 3 1 0x0004");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDg 3 1 0x0008");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Ctrl_OSD_Layer() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting, Layer error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDg 3 0 0x000C");
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_OSDg 0 1 0x0004");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Ctrl_Main_Tbl() normal\n", seqNo++));

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LTRG.word = 2;
	IO_DISP.MAIN[0].LCH.LTBLASET.bit.IGTAEN = 1;
	IO_DISP.MAIN[0].LCH.LTBLASET.bit.GTAEN = 1;
	IO_DISP.MAIN[0].GRCH[0].GRTRG.word = 2;
	IO_DISP.MAIN[0].GRCH[1].GRTRG.word = 2;

	IO_DISP.MAIN[1].LCH.LTRG.word = 2;
	IO_DISP.MAIN[1].LCH.LTBLASET.bit.IGTAEN = 1;
	IO_DISP.MAIN[1].LCH.LTBLASET.bit.GTAEN = 1;
	IO_DISP.MAIN[1].GRCH[0].GRTRG.word = 2;
	IO_DISP.MAIN[1].GRCH[1].GRTRG.word = 2;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Main_TBLs 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Main_TBLs 1 1 0");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Ctrl_Main_Tbl() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Main_TBLs 0 0 0");
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Main_TBLs 0 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Main_TBLs 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Main_TBLs 1 0 2");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Main_TBLs 1 0 3");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Main_TBLs 1 0 4");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Main_TBLs 1 0 5");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Main_TBLs 1 0 6");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Main_TBLs 1 1 7");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Main_TBLs 1 1 8");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Main_TBLs 1 1 9");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Main_TBLs 1 1 10");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Main_TBLs 1 1 11");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Main_TBLs 1 1 12");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Ctrl_Main_Tbl() normal\n", seqNo++));

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LTRG.word = 2;
	IO_DISP.MAIN[0].LCH.LTBLASET.bit.IGTAEN = 1;
	IO_DISP.MAIN[0].LCH.LTBLASET.bit.GTAEN = 1;
	IO_DISP.MAIN[1].LCH.LTRG.word = 2;
	IO_DISP.MAIN[1].LCH.LTBLASET.bit.IGTAEN = 1;
	IO_DISP.MAIN[1].LCH.LTBLASET.bit.GTAEN = 1;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Main_TBLs 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Main_TBLs 1 1 0");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Ctrl_Main_Tbl() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Main_TBLs 0 0 0");
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Main_TBLs 0 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Main_TBLs 1 1 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Main_TBLs 1 1 2");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Main_TBLs 1 1 3");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Main_TBLs 1 1 4");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Main_TBLs 1 1 5");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Main_TBLs 1 1 6");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Main_TBLs 1 0 7");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Main_TBLs 1 0 8");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Main_TBLs 1 0 9");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Main_TBLs 1 0 10");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Main_TBLs 1 0 11");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Main_TBLs 1 0 12");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Ctrl_Output_Tbl() normal\n", seqNo++));

	// enable OFF
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Output_TBLs 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Output_TBLs 1 1 0");

	// SURFACE B
	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.GMTSL = D_IM_DISP_TABLE_SURFACE_B;
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.YSATSL = D_IM_DISP_TABLE_SURFACE_B;
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.GMTSL = D_IM_DISP_TABLE_SURFACE_B;
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.YSATSL = D_IM_DISP_TABLE_SURFACE_B;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Output_TBLs 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Output_TBLs 1 1 0");

	// SURFACE A
	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.GMTSL = D_IM_DISP_TABLE_SURFACE_A;
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.YSATSL = D_IM_DISP_TABLE_SURFACE_A;
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.GMTSL = D_IM_DISP_TABLE_SURFACE_A;
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.YSATSL = D_IM_DISP_TABLE_SURFACE_A;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Output_TBLs 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Output_TBLs 1 1 0");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.bit.TRG = 2;
	IO_DISP.MAIN[1].DCORE.TRG.bit.TRG = 2;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Output_TBLs 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Output_TBLs 1 1 0");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.bit.TRG = 0;
	IO_DISP.MAIN[1].DCORE.TRG.bit.TRG = 0 ;
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.GMTAEN = E_IM_DISP_TABLE_ACCESS_ENABLE;
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.YSATTA = E_IM_DISP_TABLE_ACCESS_ENABLE;
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.GMTAEN = E_IM_DISP_TABLE_ACCESS_ENABLE;
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.YSATTA = E_IM_DISP_TABLE_ACCESS_ENABLE;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Output_TBLs 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Output_TBLs 1 1 0");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.bit.TRG = 2;
	IO_DISP.MAIN[1].DCORE.TRG.bit.TRG = 2;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Output_TBLs 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Output_TBLs 1 1 0");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.bit.TRG = 0;
	IO_DISP.MAIN[1].DCORE.TRG.bit.TRG = 0 ;
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.GMTAEN = E_IM_DISP_TABLE_ACCESS_DISABLE;
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.YSATTA = E_IM_DISP_TABLE_ACCESS_DISABLE;
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.GMTAEN = E_IM_DISP_TABLE_ACCESS_DISABLE;
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.YSATTA = E_IM_DISP_TABLE_ACCESS_DISABLE;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Ctrl_Output_Tbl() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Output_TBLs 0 0 0");
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Output_TBLs 0 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Output_TBLs 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Output_TBLs 1 1 2");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Output_TBLs 1 0 3");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Output_TBLs 1 1 4");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Output_TBLs 1 0 5");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Output_TBLs 1 1 6");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Output_TBLs 1 0 7");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Output_TBLs 1 1 8");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Output_TBLs 1 0 9");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Ctrl_Output_TBLs 1 1 10");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Ctrl_Output_Tbl() normal\n", seqNo++));

	// enable OFF
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Output_TBLs 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Output_TBLs 1 1 0");

	// SURFACE B
	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.GMTSL = D_IM_DISP_TABLE_SURFACE_B;
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.YSATSL = D_IM_DISP_TABLE_SURFACE_B;
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.GMTSL = D_IM_DISP_TABLE_SURFACE_B;
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.YSATSL = D_IM_DISP_TABLE_SURFACE_B;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Output_TBLs 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Output_TBLs 1 1 0");

	// SURFACE A
	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.GMTSL = D_IM_DISP_TABLE_SURFACE_A;
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.YSATSL = D_IM_DISP_TABLE_SURFACE_A;
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.GMTSL = D_IM_DISP_TABLE_SURFACE_A;
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.YSATSL = D_IM_DISP_TABLE_SURFACE_A;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Output_TBLs 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Output_TBLs 1 1 0");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.bit.TRG = 2;
	IO_DISP.MAIN[1].DCORE.TRG.bit.TRG = 2;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Output_TBLs 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Output_TBLs 1 1 0");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.bit.TRG = 0;
	IO_DISP.MAIN[1].DCORE.TRG.bit.TRG = 0 ;
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.GMTAEN = E_IM_DISP_TABLE_ACCESS_ENABLE;
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.YSATTA = E_IM_DISP_TABLE_ACCESS_ENABLE;
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.GMTAEN = E_IM_DISP_TABLE_ACCESS_ENABLE;
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.YSATTA = E_IM_DISP_TABLE_ACCESS_ENABLE;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Output_TBLs 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Output_TBLs 1 1 0");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.bit.TRG = 2;
	IO_DISP.MAIN[1].DCORE.TRG.bit.TRG = 2;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Output_TBLs 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Output_TBLs 1 1 0");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.bit.TRG = 0;
	IO_DISP.MAIN[1].DCORE.TRG.bit.TRG = 0 ;
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.GMTAEN = E_IM_DISP_TABLE_ACCESS_DISABLE;
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.YSATTA = E_IM_DISP_TABLE_ACCESS_DISABLE;
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.GMTAEN = E_IM_DISP_TABLE_ACCESS_DISABLE;
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.YSATTA = E_IM_DISP_TABLE_ACCESS_DISABLE;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Ctrl_Output_Tbl() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Output_TBLs 0 0 0");
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Output_TBLs 0 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Output_TBLs 1 1 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Output_TBLs 1 0 2");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Output_TBLs 1 1 3");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Output_TBLs 1 0 4");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Output_TBLs 1 1 5");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Output_TBLs 1 0 6");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Output_TBLs 1 1 7");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Output_TBLs 1 0 8");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Output_TBLs 1 1 9");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp Get_Output_TBLs 1 0 10");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Start() normal\n", seqNo++));

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

	// E_IM_DISP_SEL_LAYER_MAIN, E_IM_DISP_SEL_LAYER_MAIN, Channnel
	im_disp1_parent_pctest_wrap(parent, "imdisp start 0x0001 0x0001 1");
	// E_IM_DISP_SEL_LAYER_DCORE, E_IM_DISP_SEL_LAYER_DCORE, Channnel
	im_disp1_parent_pctest_wrap(parent, "imdisp start 0x0002 0x0002 2");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.PWCH[0].PWCHTRG.bit.PWCHTRG = 2;
	IO_DISP.P2M[0].P2MTRG.bit.P2MTRG = 2;
	IO_DISP.PWCH[1].PWCHTRG.bit.PWCHTRG = 2;
	IO_DISP.P2M[1].P2MTRG.bit.P2MTRG = 2;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);
	// E_IM_DISP_SEL_LAYER_OSD_0, E_IM_DISP_SEL_LAYER_OSD_0, Channnel
	im_disp1_parent_pctest_wrap(parent, "imdisp start 0x0004 0x0004 1");
	// E_IM_DISP_SEL_LAYER_OSD_1, E_IM_DISP_SEL_LAYER_OSD_1, Channnel
	im_disp1_parent_pctest_wrap(parent, "imdisp start 0x0008 0x0008 2");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LTRG.word = 2;
	IO_DISP.MAIN[0].DCORE.TRG.word = 2;
	IO_DISP.MAIN[0].GRCH[0].GRTRG.word = 2;
	IO_DISP.MAIN[0].GRCH[1].GRTRG.word = 2;
	IO_DISP.MAIN[1].LCH.LTRG.word = 2;
	IO_DISP.MAIN[1].DCORE.TRG.word = 2;
	IO_DISP.MAIN[1].GRCH[0].GRTRG.word = 2;
	IO_DISP.MAIN[1].GRCH[1].GRTRG.word = 2;
	IO_DISP.PWCH[0].PWCHTRG.bit.PWCHTRG = 2;
	IO_DISP.P2M[0].P2MTRG.bit.P2MTRG = 2;
	IO_DISP.PWCH[1].PWCHTRG.bit.PWCHTRG = 2;
	IO_DISP.P2M[1].P2MTRG.bit.P2MTRG = 2;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);
	// E_IM_DISP_SEL_LAYER_OSD_0/1, E_IM_DISP_SEL_LAYER_OSD_0/1, Channnel
	im_disp1_parent_pctest_wrap(parent, "imdisp start 0x000C 0x000C 1");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LTRG.word = 2;
	IO_DISP.MAIN[0].DCORE.TRG.word = 2;
	IO_DISP.MAIN[0].GRCH[0].GRTRG.word = 2;
	IO_DISP.MAIN[0].GRCH[1].GRTRG.word = 2;
	IO_DISP.MAIN[1].LCH.LTRG.word = 2;
	IO_DISP.MAIN[1].DCORE.TRG.word = 2;
	IO_DISP.MAIN[1].GRCH[0].GRTRG.word = 2;
	IO_DISP.MAIN[1].GRCH[1].GRTRG.word = 2;
	IO_DISP.PWCH[0].PWCHTRG.bit.PWCHTRG = 2;
	IO_DISP.P2M[0].P2MTRG.bit.P2MTRG = 2;
	IO_DISP.PWCH[1].PWCHTRG.bit.PWCHTRG = 2;
	IO_DISP.P2M[1].P2MTRG.bit.P2MTRG = 2;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// E_IM_DISP_SEL_LAYER_ALL, E_IM_DISP_SEL_LAYER_ALL, Channnel
	im_disp1_parent_pctest_wrap(parent, "imdisp start 0x000F 0x000F 2");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Start() error\n", seqNo++));

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LTRG.word = 2;
	IO_DISP.MAIN[0].DCORE.TRG.word = 2;
	IO_DISP.MAIN[0].GRCH[0].GRTRG.word = 2;
	IO_DISP.MAIN[0].GRCH[1].GRTRG.word = 2;
	IO_DISP.MAIN[1].LCH.LTRG.word = 2;
	IO_DISP.MAIN[1].DCORE.TRG.word = 2;
	IO_DISP.MAIN[1].GRCH[0].GRTRG.word = 2;
	IO_DISP.MAIN[1].GRCH[1].GRTRG.word = 2;
	IO_DISP.PWCH[0].PWCHTRG.bit.PWCHTRG = 2;
	IO_DISP.P2M[0].P2MTRG.bit.P2MTRG = 2;
	IO_DISP.PWCH[1].PWCHTRG.bit.PWCHTRG = 2;
	IO_DISP.P2M[1].P2MTRG.bit.P2MTRG = 2;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// Layer error, Layer error, Channnel
	im_disp1_parent_pctest_wrap(parent, "imdisp start 0x0000 0x0000 1");
	// Layer error, E_IM_DISP_SEL_LAYER_MAIN, Channnel
	im_disp1_parent_pctest_wrap(parent, "imdisp start 0x0000 0x0001 1");
	// E_IM_DISP_SEL_LAYER_MAIN, Layer error, Channnel
	im_disp1_parent_pctest_wrap(parent, "imdisp start 0x0001 0x0000 2");

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

	// E_IM_DISP_SEL_LAYER_ALL, E_IM_DISP_SEL_LAYER_ALL, Channnel
	im_disp1_parent_pctest_wrap(parent, "imdisp start 0x000F 0x000F 1");

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

	IO_CHIPTOP.CLKSTOP3.bit.LCDCK = 1;
	IO_CHIPTOP.CLKSTOP3.bit.HIFCK = 1;

	// E_IM_DISP_SEL_LAYER_ALL, E_IM_DISP_SEL_LAYER_ALL, Channnel
	im_disp1_parent_pctest_wrap(parent, "imdisp start 0x000F 0x000F 2");

	IO_CHIPTOP.CLKSTOP3.bit.LCDCK = 0;
	IO_CHIPTOP.CLKSTOP3.bit.HIFCK = 0;

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Stop() normal\n", seqNo++));

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LTRG.word = 3;
	IO_DISP.MAIN[0].DCORE.TRG.word = 3;
	IO_DISP.MAIN[0].GRCH[0].GRTRG.word = 3;
	IO_DISP.MAIN[0].GRCH[1].GRTRG.word = 3;
	IO_DISP.MAIN[1].LCH.LTRG.word = 3;
	IO_DISP.MAIN[1].DCORE.TRG.word = 3;
	IO_DISP.MAIN[1].GRCH[0].GRTRG.word = 3;
	IO_DISP.MAIN[1].GRCH[1].GRTRG.word = 3;
	IO_DISP.PWCH[0].PWCHTRG.bit.PWCHTRG = 1;
	IO_DISP.P2M[0].P2MTRG.bit.P2MTRG = 1;
	IO_DISP.PWCH[1].PWCHTRG.bit.PWCHTRG = 1;
	IO_DISP.P2M[1].P2MTRG.bit.P2MTRG = 1;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// E_IM_DISP_SEL_LAYER_MAIN, E_IM_DISP_SEL_LAYER_MAIN, Channnel, E_IM_DISP_STOP_TYPE_WITHOUT_WAIT
	im_disp1_parent_pctest_wrap(parent, "imdisp stop 0x0001 0x0001 1 0");
	// E_IM_DISP_SEL_LAYER_DCORE, E_IM_DISP_SEL_LAYER_DCORE, Channnel, E_IM_DISP_STOP_TYPE_WITH_WAIT
	im_disp1_parent_pctest_wrap(parent, "imdisp stop 0x0002 0x0002 2 2");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.PWCH[0].PWCHTRG.bit.PWCHTRG = 1;
	IO_DISP.P2M[0].P2MTRG.bit.P2MTRG = 1;
	IO_DISP.PWCH[1].PWCHTRG.bit.PWCHTRG = 1;
	IO_DISP.P2M[1].P2MTRG.bit.P2MTRG = 1;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);
	// E_IM_DISP_SEL_LAYER_OSD_0, E_IM_DISP_SEL_LAYER_OSD_0, Channnel, E_IM_DISP_STOP_TYPE_WITHOUT_WAIT
	im_disp1_parent_pctest_wrap(parent, "imdisp stop 0x0004 0x0004 1 0");
	// E_IM_DISP_SEL_LAYER_OSD_1, E_IM_DISP_SEL_LAYER_OSD_1, Channnel, E_IM_DISP_STOP_TYPE_WITH_WAIT
	im_disp1_parent_pctest_wrap(parent, "imdisp stop 0x0008 0x0008 2 2");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LTRG.word = 3;
	IO_DISP.MAIN[0].DCORE.TRG.word = 3;
	IO_DISP.MAIN[0].GRCH[0].GRTRG.word = 3;
	IO_DISP.MAIN[0].GRCH[1].GRTRG.word = 3;
	IO_DISP.MAIN[1].LCH.LTRG.word = 3;
	IO_DISP.MAIN[1].DCORE.TRG.word = 3;
	IO_DISP.MAIN[1].GRCH[0].GRTRG.word = 3;
	IO_DISP.MAIN[1].GRCH[1].GRTRG.word = 3;
	IO_DISP.PWCH[0].PWCHTRG.bit.PWCHTRG = 1;
	IO_DISP.P2M[0].P2MTRG.bit.P2MTRG = 1;
	IO_DISP.PWCH[1].PWCHTRG.bit.PWCHTRG = 1;
	IO_DISP.P2M[1].P2MTRG.bit.P2MTRG = 1;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);
	// E_IM_DISP_SEL_LAYER_OSD_0/1, E_IM_DISP_SEL_LAYER_OSD_0/1, Channnel, E_IM_DISP_STOP_TYPE_WITHOUT_WAIT
	im_disp1_parent_pctest_wrap(parent, "imdisp stop 0x000C 0x000C 1 0");

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

	// E_IM_DISP_SEL_LAYER_ALL, E_IM_DISP_SEL_LAYER_ALL, Channnel, E_IM_DISP_STOP_TYPE_WITHOUT_WAIT
	im_disp1_parent_pctest_wrap(parent, "imdisp stop 0x000F 0x000F 2 0");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LTRG.word = 3;
	IO_DISP.MAIN[0].DCORE.TRG.word = 3;
	IO_DISP.MAIN[0].GRCH[0].GRTRG.word = 3;
	IO_DISP.MAIN[0].GRCH[1].GRTRG.word = 3;
	IO_DISP.MAIN[1].LCH.LTRG.word = 3;
	IO_DISP.MAIN[1].DCORE.TRG.word = 3;
	IO_DISP.MAIN[1].GRCH[0].GRTRG.word = 3;
	IO_DISP.MAIN[1].GRCH[1].GRTRG.word = 3;
	IO_DISP.PWCH[0].PWCHTRG.bit.PWCHTRG = 1;
	IO_DISP.P2M[0].P2MTRG.bit.P2MTRG = 1;
	IO_DISP.PWCH[1].PWCHTRG.bit.PWCHTRG = 1;
	IO_DISP.P2M[1].P2MTRG.bit.P2MTRG = 1;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// E_IM_DISP_SEL_LAYER_ALL, E_IM_DISP_SEL_LAYER_ALL, Channnel, E_IM_DISP_STOP_TYPE_WITH_WAIT
	im_disp1_parent_pctest_wrap(parent, "imdisp stop 0x000F 0x000F 2 2");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Stop() error\n", seqNo++));

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LTRG.word = 3;
	IO_DISP.MAIN[0].DCORE.TRG.word = 3;
	IO_DISP.MAIN[0].GRCH[0].GRTRG.word = 3;
	IO_DISP.MAIN[0].GRCH[1].GRTRG.word = 3;
	IO_DISP.MAIN[1].LCH.LTRG.word = 3;
	IO_DISP.MAIN[1].DCORE.TRG.word = 3;
	IO_DISP.MAIN[1].GRCH[0].GRTRG.word = 3;
	IO_DISP.MAIN[1].GRCH[1].GRTRG.word = 3;
	IO_DISP.PWCH[0].PWCHTRG.bit.PWCHTRG = 1;
	IO_DISP.P2M[0].P2MTRG.bit.P2MTRG = 1;
	IO_DISP.PWCH[1].PWCHTRG.bit.PWCHTRG = 1;
	IO_DISP.P2M[1].P2MTRG.bit.P2MTRG = 1;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// Layer error, Layer error, Channnel, E_IM_DISP_STOP_TYPE_WITH_WAIT
	im_disp1_parent_pctest_wrap(parent, "imdisp stop 0x0000 0x0000 2 2");
	// Layer error, Layer error, Channnel, E_IM_DISP_STOP_TYPE_WITHOUT_WAIT
	im_disp1_parent_pctest_wrap(parent, "imdisp stop 0x0000 0x0000 1 0");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Status() normal\n", seqNo++));

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

	im_disp1_parent_pctest_wrap(parent, "imdisp status 1");	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY
	im_disp1_parent_pctest_wrap(parent, "imdisp status 2");	// CtImDisp3_D_CT_IM_DISP_SECOND_PARA_ONLY
	im_disp1_parent_pctest_wrap(parent, "imdisp status 3");	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LTRG.word = 3;
	IO_DISP.MAIN[0].DCORE.TRG.word = 2;
	IO_DISP.MAIN[0].GRCH[0].GRTRG.word = 2;
	IO_DISP.MAIN[0].GRCH[1].GRTRG.word = 2;
	IO_DISP.MAIN[1].LCH.LTRG.word = 2;
	IO_DISP.MAIN[1].DCORE.TRG.word = 2;
	IO_DISP.MAIN[1].GRCH[0].GRTRG.word = 2;
	IO_DISP.MAIN[1].GRCH[1].GRTRG.word = 3;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	im_disp1_parent_pctest_wrap(parent, "imdisp status 1");	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY
	im_disp1_parent_pctest_wrap(parent, "imdisp status 2");	// CtImDisp3_D_CT_IM_DISP_SECOND_PARA_ONLY
	im_disp1_parent_pctest_wrap(parent, "imdisp status 3");	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LTRG.word = 2;
	IO_DISP.MAIN[0].DCORE.TRG.word = 3;
	IO_DISP.MAIN[0].GRCH[0].GRTRG.word = 2;
	IO_DISP.MAIN[0].GRCH[1].GRTRG.word = 2;
	IO_DISP.MAIN[1].LCH.LTRG.word = 2;
	IO_DISP.MAIN[1].DCORE.TRG.word = 2;
	IO_DISP.MAIN[1].GRCH[0].GRTRG.word = 3;
	IO_DISP.MAIN[1].GRCH[1].GRTRG.word = 2;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	im_disp1_parent_pctest_wrap(parent, "imdisp status 1");	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY
	im_disp1_parent_pctest_wrap(parent, "imdisp status 2");	// CtImDisp3_D_CT_IM_DISP_SECOND_PARA_ONLY
	im_disp1_parent_pctest_wrap(parent, "imdisp status 3");	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LTRG.word = 2;
	IO_DISP.MAIN[0].DCORE.TRG.word = 2;
	IO_DISP.MAIN[0].GRCH[0].GRTRG.word = 3;
	IO_DISP.MAIN[0].GRCH[1].GRTRG.word = 2;
	IO_DISP.MAIN[1].LCH.LTRG.word = 2;
	IO_DISP.MAIN[1].DCORE.TRG.word = 3;
	IO_DISP.MAIN[1].GRCH[0].GRTRG.word = 2;
	IO_DISP.MAIN[1].GRCH[1].GRTRG.word = 2;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	im_disp1_parent_pctest_wrap(parent, "imdisp status 1");	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY
	im_disp1_parent_pctest_wrap(parent, "imdisp status 2");	// CtImDisp3_D_CT_IM_DISP_SECOND_PARA_ONLY
	im_disp1_parent_pctest_wrap(parent, "imdisp status 3");	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LTRG.word = 2;
	IO_DISP.MAIN[0].DCORE.TRG.word = 2;
	IO_DISP.MAIN[0].GRCH[0].GRTRG.word = 2;
	IO_DISP.MAIN[0].GRCH[1].GRTRG.word = 3;
	IO_DISP.MAIN[1].LCH.LTRG.word = 3;
	IO_DISP.MAIN[1].DCORE.TRG.word = 2;
	IO_DISP.MAIN[1].GRCH[0].GRTRG.word = 2;
	IO_DISP.MAIN[1].GRCH[1].GRTRG.word = 2;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	im_disp1_parent_pctest_wrap(parent, "imdisp status 1");	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY
	im_disp1_parent_pctest_wrap(parent, "imdisp status 2");	// CtImDisp3_D_CT_IM_DISP_SECOND_PARA_ONLY
	im_disp1_parent_pctest_wrap(parent, "imdisp status 3");	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA

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

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY
	im_disp1_parent_pctest_wrap(parent, "imdisp status 1");
	// CtImDisp3_D_CT_IM_DISP_SECOND_PARA_ONLY
	im_disp1_parent_pctest_wrap(parent, "imdisp status 2");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA
	im_disp1_parent_pctest_wrap(parent, "imdisp status 3");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Status() error\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp status 0");	// CtImDisp3_D_CT_IM_DISP_NO_PARA

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Wait_Vsync() normal\n", seqNo++));

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.word = 3;
	IO_DISP.MAIN[0].DCORE.INTC.word = 3;
	IO_DISP.MAIN[0].DCORE.INTE.word = 0x00110000;
	IO_DISP.MAIN[1].DCORE.TRG.word = 3;
	IO_DISP.MAIN[1].DCORE.INTC.word = 3;
	IO_DISP.MAIN[1].DCORE.INTE.word = 0x00110000;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	//HDMI setting, E_IM_DISP_INTERRUPTION_SELECT_VE, E_IM_DISP_WAIT_1_TIME
	im_disp1_parent_pctest_wrap(parent, "imdisp Wait 0 0x00010000 1");
	//HDMI setting, E_IM_DISP_INTERRUPTION_SELECT_VE2, E_IM_DISP_WAIT_1_TIME
	im_disp1_parent_pctest_wrap(parent, "imdisp Wait 0 0x00100000 1");
	//HDMI setting, E_IM_DISP_CORRECT_SELECT_ALL_VE, E_IM_DISP_WAIT_1_TIME
	im_disp1_parent_pctest_wrap(parent, "imdisp Wait 0 0x00110000 2");
	//LCD setting, E_IM_DISP_INTERRUPTION_SELECT_VE, E_IM_DISP_WAIT_1_TIME
	im_disp1_parent_pctest_wrap(parent, "imdisp Wait 1 0x00010000 1");
	//LCD setting, E_IM_DISP_INTERRUPTION_SELECT_VE2, E_IM_DISP_WAIT_1_TIME
	im_disp1_parent_pctest_wrap(parent, "imdisp Wait 1 0x00100000 1");
	//LCD setting, E_IM_DISP_CORRECT_SELECT_ALL_VE, E_IM_DISP_WAIT_1_TIME
	im_disp1_parent_pctest_wrap(parent, "imdisp Wait 1 0x00110000 2");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Wait_Vsync() error\n", seqNo++));
	//E_IM_DISP_CORRECT_SELECT_ALL, E_IM_DISP_WAIT_1_TIME
	im_disp1_parent_pctest_wrap(parent, "imdisp Wait 1 0x00113131 1");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.word = 3;
	IO_DISP.MAIN[0].DCORE.INTC.word = 3;
	IO_DISP.MAIN[0].DCORE.INTE.word = 0x00010000;
	IO_DISP.MAIN[1].DCORE.TRG.word = 3;
	IO_DISP.MAIN[1].DCORE.INTC.word = 3;
	IO_DISP.MAIN[1].DCORE.INTE.word = 0x00010000;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// HDMI setting, E_IM_DISP_INTERRUPTION_SELECT_VE2, 0
	im_disp1_parent_pctest_wrap(parent, "imdisp Wait 0 0x00100000 0");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.word = 3;
	IO_DISP.MAIN[0].DCORE.INTC.word = 3;
	IO_DISP.MAIN[0].DCORE.INTE.word = 0x00100000;
	IO_DISP.MAIN[1].DCORE.TRG.word = 3;
	IO_DISP.MAIN[1].DCORE.INTC.word = 3;
	IO_DISP.MAIN[1].DCORE.INTE.word = 0x00100000;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// HDMI setting, E_IM_DISP_INTERRUPTION_SELECT_VE, 0
	im_disp1_parent_pctest_wrap(parent, "imdisp Wait 0 0x00010000 0");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.word = 3;
	IO_DISP.MAIN[0].DCORE.INTC.word = 0;
	IO_DISP.MAIN[0].DCORE.INTE.word = 0x00110000;
	IO_DISP.MAIN[1].DCORE.TRG.word = 3;
	IO_DISP.MAIN[1].DCORE.INTC.word = 0;
	IO_DISP.MAIN[1].DCORE.INTE.word = 0x00110000;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// HDMI setting, E_IM_DISP_INTERRUPTION_SELECT_VE, E_IM_DISP_WAIT_1_TIME
	im_disp1_parent_pctest_wrap(parent, "imdisp Wait 0 0x00010000 1");
	// HDMI setting, E_IM_DISP_INTERRUPTION_SELECT_VE, E_IM_DISP_WAIT_1_TIME
	im_disp1_parent_pctest_wrap(parent, "imdisp Wait 1 0x00010000 1");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.word = 0;
	IO_DISP.MAIN[0].DCORE.INTC.word = 3;
	IO_DISP.MAIN[0].DCORE.INTE.word = 0x00110000;
	IO_DISP.MAIN[1].DCORE.TRG.word = 0;
	IO_DISP.MAIN[1].DCORE.INTC.word = 3;
	IO_DISP.MAIN[1].DCORE.INTE.word = 0x00110000;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// HDMI setting, E_IM_DISP_INTERRUPTION_SELECT_VE, E_IM_DISP_WAIT_2_TIME
	im_disp1_parent_pctest_wrap(parent, "imdisp Wait 0 0x00010000 2");
	// HDMI setting, E_IM_DISP_INTERRUPTION_SELECT_VE, E_IM_DISP_WAIT_2_TIME
	im_disp1_parent_pctest_wrap(parent, "imdisp Wait 1 0x00010000 2");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Wait_Stop() normal\n", seqNo++));

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

	// E_IM_DISP_SEL_LAYER_MAIN, E_IM_DISP_SEL_LAYER_ALL
	im_disp1_parent_pctest_wrap(parent, "imdisp WaitStop 0x0001 0x000F");
	// E_IM_DISP_SEL_LAYER_DCORE, E_IM_DISP_SEL_LAYER_OSD_0/1
	im_disp1_parent_pctest_wrap(parent, "imdisp WaitStop 0x0002 0x000C");
	// E_IM_DISP_SEL_LAYER_OSD_0, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp WaitStop 0x0004 0x0008");
	// E_IM_DISP_SEL_LAYER_OSD_1, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp WaitStop 0x0008 0x0004");
	// E_IM_DISP_SEL_LAYER_OSD_0/1, E_IM_DISP_SEL_LAYER_DCORE
	im_disp1_parent_pctest_wrap(parent, "imdisp WaitStop 0x000C 0x0002");
	// E_IM_DISP_SEL_LAYER_ALL, E_IM_DISP_SEL_LAYER_MAIN
	im_disp1_parent_pctest_wrap(parent, "imdisp WaitStop 0x000F 0x0001");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Wait_Stop() error\n", seqNo++));

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

	// E_IM_DISP_SEL_LAYER_NONE, E_IM_DISP_SEL_LAYER_NONE
	im_disp1_parent_pctest_wrap(parent, "imdisp WaitStop 0x0000 0x0000");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Int_Handler()\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp IntHndl");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.INTF.word = 0x00000001;	// E_IM_DISP_INTERRUPTION_SELECT_LEE
	IO_DISP.MAIN[1].DCORE.INTF.word = 0x00000001;	// E_IM_DISP_INTERRUPTION_SELECT_LEE
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);
	im_disp1_parent_pctest_wrap(parent, "imdisp IntHndl");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.INTF.word = 0x00000010;	// E_IM_DISP_INTERRUPTION_SELECT_GR0EE
	IO_DISP.MAIN[1].DCORE.INTF.word = 0x00000010;	// E_IM_DISP_INTERRUPTION_SELECT_GR0EE
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);
	im_disp1_parent_pctest_wrap(parent, "imdisp IntHndl");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.INTF.word = 0x00000020;	// E_IM_DISP_INTERRUPTION_SELECT_GR1EE
	IO_DISP.MAIN[1].DCORE.INTF.word = 0x00000020;	// E_IM_DISP_INTERRUPTION_SELECT_GR1EE
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);
	im_disp1_parent_pctest_wrap(parent, "imdisp IntHndl");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.INTF.word = 0x00000080;	// E_IM_DISP_INTERRUPTION_SELECT_GA1EE
	IO_DISP.MAIN[1].DCORE.INTF.word = 0x00000080;	// E_IM_DISP_INTERRUPTION_SELECT_GA1EE
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);
	im_disp1_parent_pctest_wrap(parent, "imdisp IntHndl");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.INTF.word = 0x00000040;	// E_IM_DISP_INTERRUPTION_SELECT_GA0EE
	IO_DISP.MAIN[1].DCORE.INTF.word = 0x00000040;	// E_IM_DISP_INTERRUPTION_SELECT_GA0EE
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);
	im_disp1_parent_pctest_wrap(parent, "imdisp IntHndl");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.INTF.word = 0x00000100;	// E_IM_DISP_INTERRUPTION_SELECT_LREE
	IO_DISP.MAIN[1].DCORE.INTF.word = 0x00000100;	// E_IM_DISP_INTERRUPTION_SELECT_LREE
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);
	im_disp1_parent_pctest_wrap(parent, "imdisp IntHndl");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.INTF.word = 0x00001000;	// E_IM_DISP_INTERRUPTION_SELECT_GR0REE
	IO_DISP.MAIN[1].DCORE.INTF.word = 0x00001000;	// E_IM_DISP_INTERRUPTION_SELECT_GR0REE
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);
	im_disp1_parent_pctest_wrap(parent, "imdisp IntHndl");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.INTF.word = 0x00002000;	// E_IM_DISP_INTERRUPTION_SELECT_GR1REE
	IO_DISP.MAIN[1].DCORE.INTF.word = 0x00002000;	// E_IM_DISP_INTERRUPTION_SELECT_GR1REE
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);
	im_disp1_parent_pctest_wrap(parent, "imdisp IntHndl");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.INTF.word = 0x00008000;	// E_IM_DISP_INTERRUPTION_SELECT_GA1REE
	IO_DISP.MAIN[1].DCORE.INTF.word = 0x00008000;	// E_IM_DISP_INTERRUPTION_SELECT_GA1REE
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);
	im_disp1_parent_pctest_wrap(parent, "imdisp IntHndl");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.INTF.word = 0x00004000;	// E_IM_DISP_INTERRUPTION_SELECT_GA0REE
	IO_DISP.MAIN[1].DCORE.INTF.word = 0x00004000;	// E_IM_DISP_INTERRUPTION_SELECT_GA0REE
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);
	im_disp1_parent_pctest_wrap(parent, "imdisp IntHndl");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.INTF.word = 0x00010000;	// E_IM_DISP_INTERRUPTION_SELECT_VE
	IO_DISP.MAIN[1].DCORE.INTF.word = 0x00010000;	// E_IM_DISP_INTERRUPTION_SELECT_VE
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);
	im_disp1_parent_pctest_wrap(parent, "imdisp IntHndl");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.INTF.word = 0x00100000;	// E_IM_DISP_INTERRUPTION_SELECT_VE2
	IO_DISP.MAIN[1].DCORE.INTF.word = 0x00100000;	// E_IM_DISP_INTERRUPTION_SELECT_VE2
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);
	im_disp1_parent_pctest_wrap(parent, "imdisp IntHndl");

	*pSeqNo = seqNo;
	return ktrue;
}
#endif /*CtImDisp_CO_DEBUG_DISP*/

CtImDisp1a *ct_im_disp1a_new()
{
	CtImDisp1a *self = (CtImDisp1a *) k_object_new_with_private(CT_TYPE_IM_DISP1A,sizeof(CtImDisp1aPrivate));
	if(!self){//Ddim_Assertion(self)
		Ddim_Print(("!! new CtImDisp1a NULL: %s (%d)", __FILE__, __LINE__));
		return NULL;
	}
	return self;
}
