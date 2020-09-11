/*
 *ctimdisp1c.c
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
#include "ctimdisp1c.h"

K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(CtImDisp1c, ct_im_disp1c, IM_TYPE_DISP1_PARENT)
#define CT_IM_DISP1C_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), CtImDisp1cPrivate, CT_TYPE_IM_DISP1C))

struct _CtImDisp1cPrivate
{
	kpointer qwertyu;
};

/*
 * DECLS
 * */
#ifdef CtImDisp_CO_DEBUG_DISP
static kboolean imDisp1cDoPctest_od(ImDisp1Parent *parent, kint32 *pSeqNo);
#endif /*CtImDisp_CO_DEBUG_DISP*/

/*
 * IMPL
 * */
static void ct_im_disp1c_constructor(CtImDisp1c *self)
{
	//CtImDisp1cPrivate *priv = CT_IM_DISP1C_GET_PRIVATE(self);
#ifdef CtImDisp_CO_DEBUG_DISP
	ImDisp1Parent *parent = (ImDisp1Parent *)self;
	parent->pctestFunc = imDisp1cDoPctest_od;
#endif /*CtImDisp_CO_DEBUG_DISP*/
}

static void ct_im_disp1c_destructor(CtImDisp1c *self)
{
}

/*
 * PUBLIC
 * */

#ifdef CtImDisp_CO_DEBUG_DISP
static kboolean imDisp1cDoPctest_od(ImDisp1Parent *parent, kint32 *pSeqNo)
{
//	CtImDisp1c *self = (CtImDisp1c *)parent;
	kint32 seqNo = *pSeqNo;
	ImDisp1Group *imDisp1Group = (ImDisp1Group *)im_disp1_parent_get_group(parent);

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Reverse_Display()\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp SetRev 0 0x00000000");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetRev 0 0x00000101");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetRev 1 0x00000000");	// LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetRev 1 0x00000101");	// LCD setting, Normal

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Reverse_Display() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetRev 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetRev 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Reverse_Display() error\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp GetRev 0 0");	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetRev 0 1");	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Display_Interface() normal\n", seqNo++));

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.RESET.bit.SR = 1;
	IO_DISP.MAIN[1].DCORE.RESET.bit.SR = 1;
	DDIM_User_Tslp_Tsk( 1 );	// wait 1ms
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	im_disp1_parent_pctest_wrap(parent, "imdisp SetIf 0 0");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIf 0 2");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIf 1 0");	// LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIf 1 1");	// LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIf 1 3");	// LCD setting, Normal

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Display_Interface() error\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIf 0 4");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIf 0 1");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIf 0 3");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetIf 1 2");	// LCD setting, Normal

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.RESET.bit.SR = 0;
	IO_DISP.MAIN[1].DCORE.RESET.bit.SR = 0;
	DDIM_User_Tslp_Tsk( 1 );	// wait 1ms
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	im_disp1_parent_pctest_wrap(parent, "imdisp SetIf 1 1");	// LCD setting, Normal

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Display_Interface() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetIf 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetIf 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Display_Interface() error\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp GetIf 0 0");	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetIf 0 1");	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_External_Startup_Mode() normal\n", seqNo++));

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.word = 2;
	IO_DISP.MAIN[1].DCORE.TRG.word = 2;
	IO_DISP.MAIN[1].DCORE.RESET.bit.SR = 0;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	im_disp1_parent_pctest_wrap(parent, "imdisp SetStartMod 0 0");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetStartMod 0 1");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetStartMod 1 0");	// LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetStartMod 1 1");	// LCD setting, Normal

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_External_Startup_Mode() error\n", seqNo++));

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.bit.TRG = 3;
	IO_DISP.MAIN[1].DCORE.TRG.bit.TRG = 3;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	im_disp1_parent_pctest_wrap(parent, "imdisp SetStartMod 0 0");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetStartMod 1 0");	// LCD setting, Normal

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.bit.TRG = 2;
	IO_DISP.MAIN[1].DCORE.TRG.bit.TRG = 2;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_External_Startup_Mode() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetStartMod 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetStartMod 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_External_Startup_Mode() error\n", seqNo++));

	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetStartMod 0 0");
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetStartMod 0 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_External_Startup_Timing() normal\n", seqNo++));

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.word = 2;
	IO_DISP.MAIN[1].DCORE.TRG.word = 2;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp SetStartTmg 0 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp SetStartTmg 1 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp SetStartTmg 0 0x00000FFF");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp SetStartTmg 1 0x00000FFF");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_External_Startup_Timing() error\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp SetStartTmg 0 0x00001000");	// HDMI setting, Parameter error

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.word = 3;
	IO_DISP.MAIN[1].DCORE.TRG.word = 3;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	im_disp1_parent_pctest_wrap(parent, "imdisp SetStartTmg 0 0x00000001");	// HDMI setting, Status error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetStartTmg 1 0x00000001");	// LCD setting, Status error

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.word = 2;
	IO_DISP.MAIN[1].DCORE.TRG.word = 2;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_External_Startup_Timing() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetStartTmg 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetStartTmg 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_External_Startup_Timing() error\n", seqNo++));

	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetStartTmg 0 0");
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetStartTmg 0 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Vsync_Int_Timing()\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp SetVSN 0 0");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetVSN 0 1");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetVSN 0 2");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetVSN 0 3");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetVSN 1 0");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetVSN 1 1");	// LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetVSN 1 2");	// LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetVSN 1 3");	// LCD setting, Normal

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Vsync_Int_Timing() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetVSN 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetVSN 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Vsync_Int_Timing() error\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp GetVSN 0 0");	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetVSN 0 1");	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Int() normal\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp SetInt 0 0x00100000 0x0011F1F1");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetInt 0 0x00010000 0x0011F1F1");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetInt 0 0x00008000 0x0011F1F1");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetInt 0 0x00004000 0x0011F1F1");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetInt 0 0x00002000 0x0011F1F1");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetInt 0 0x00001000 0x0011F1F1");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetInt 0 0x00000100 0x0011F1F1");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetInt 0 0x00000080 0x0011F1F1");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetInt 0 0x00000040 0x0011F1F1");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetInt 0 0x00000020 0x0011F1F1");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetInt 0 0x00000010 0x0011F1F1");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetInt 0 0x00000001 0x0011F1F1");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetInt 0 0x0011F1F1 0");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetInt 0 0x0011F1F1 0x0011F1F1");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetInt 1 0x00100000 0x0011F1F1");	// LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetInt 1 0x00010000 0x0011F1F1");	// LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetInt 1 0x00008000 0x0011F1F1");	// LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetInt 1 0x00004000 0x0011F1F1");	// LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetInt 1 0x00002000 0x0011F1F1");	// LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetInt 1 0x00001000 0x0011F1F1");	// LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetInt 1 0x00000100 0x0011F1F1");	// LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetInt 1 0x00000080 0x0011F1F1");	// LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetInt 1 0x00000040 0x0011F1F1");	// LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetInt 1 0x00000020 0x0011F1F1");	// LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetInt 1 0x00000010 0x0011F1F1");	// LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetInt 1 0x00000001 0x0011F1F1");	// LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetInt 1 0x0011F1F1 0");	// LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetInt 1 0x0011F1F1 0x0011F1F1");	// LCD setting, Normal

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Int() error\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp SetInt 0 0xFFEE0E0E 0x0011F1F1");	// HDMI setting, error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetInt 1 0xFFEE0E0E 0x0011F1F1");	// LCD setting, error

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Int() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetInt 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetInt 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Int() error\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp GetInt 0 0");	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetInt 0 1");	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Int_Callback() normal\n", seqNo++));
	// HDMI setting, E_IM_DISP_INTERRUPTION_SELECT_VE2
	im_disp1_parent_pctest_wrap(parent, "imdisp SetCBK 0 0x00010000 0");
	// HDMI setting, E_IM_DISP_INTERRUPTION_SELECT_VE
	im_disp1_parent_pctest_wrap(parent, "imdisp SetCBK 0 0x00100000 1");
	// HDMI setting, E_IM_DISP_INTERRUPTION_SELECT_GA1REE
	im_disp1_parent_pctest_wrap(parent, "imdisp SetCBK 0 0x00000010 2");
	// HDMI setting, E_IM_DISP_INTERRUPTION_SELECT_GA0REE
	im_disp1_parent_pctest_wrap(parent, "imdisp SetCBK 0 0x00000020 3");
	// HDMI setting, E_IM_DISP_INTERRUPTION_SELECT_GR1REE
	im_disp1_parent_pctest_wrap(parent, "imdisp SetCBK 0 0x00000040 4");
	// HDMI setting, E_IM_DISP_INTERRUPTION_SELECT_GR0REE
	im_disp1_parent_pctest_wrap(parent, "imdisp SetCBK 0 0x00000080 5");
	// HDMI setting, E_IM_DISP_INTERRUPTION_SELECT_LREE
	im_disp1_parent_pctest_wrap(parent, "imdisp SetCBK 0 0x00000001 6");
	// HDMI setting, E_IM_DISP_INTERRUPTION_SELECT_GA1EE
	im_disp1_parent_pctest_wrap(parent, "imdisp SetCBK 0 0x00001000 7");
	// HDMI setting, E_IM_DISP_INTERRUPTION_SELECT_GA0EE
	im_disp1_parent_pctest_wrap(parent, "imdisp SetCBK 0 0x00002000 8");
	// HDMI setting, E_IM_DISP_INTERRUPTION_SELECT_GR1EE
	im_disp1_parent_pctest_wrap(parent, "imdisp SetCBK 0 0x00004000 9");
	// HDMI setting, E_IM_DISP_INTERRUPTION_SELECT_GR0EE
	im_disp1_parent_pctest_wrap(parent, "imdisp SetCBK 0 0x00008000 10");
	// HDMI setting, E_IM_DISP_INTERRUPTION_SELECT_LEE
	im_disp1_parent_pctest_wrap(parent, "imdisp SetCBK 0 0x00000100 11");
	// LCD setting, E_IM_DISP_INTERRUPTION_SELECT_VE2
	im_disp1_parent_pctest_wrap(parent, "imdisp SetCBK 1 0x00010000 0");
	// LCD setting, E_IM_DISP_INTERRUPTION_SELECT_VE
	im_disp1_parent_pctest_wrap(parent, "imdisp SetCBK 1 0x00100000 1");
	// LCD setting, E_IM_DISP_INTERRUPTION_SELECT_GA1REE
	im_disp1_parent_pctest_wrap(parent, "imdisp SetCBK 1 0x00000010 2");
	// LCD setting, E_IM_DISP_INTERRUPTION_SELECT_GA0REE
	im_disp1_parent_pctest_wrap(parent, "imdisp SetCBK 1 0x00000020 3");
	// LCD setting, E_IM_DISP_INTERRUPTION_SELECT_GR1REE
	im_disp1_parent_pctest_wrap(parent, "imdisp SetCBK 1 0x00000040 4");
	// LCD setting, E_IM_DISP_INTERRUPTION_SELECT_GR0REE
	im_disp1_parent_pctest_wrap(parent, "imdisp SetCBK 1 0x00000080 5");
	// LCD setting, E_IM_DISP_INTERRUPTION_SELECT_LREE
	im_disp1_parent_pctest_wrap(parent, "imdisp SetCBK 1 0x00000001 6");
	// LCD setting, E_IM_DISP_INTERRUPTION_SELECT_GA1EE
	im_disp1_parent_pctest_wrap(parent, "imdisp SetCBK 1 0x00001000 7");
	// LCD setting, E_IM_DISP_INTERRUPTION_SELECT_GA0EE
	im_disp1_parent_pctest_wrap(parent, "imdisp SetCBK 1 0x00002000 8");
	// LCD setting, E_IM_DISP_INTERRUPTION_SELECT_GR1EE
	im_disp1_parent_pctest_wrap(parent, "imdisp SetCBK 1 0x00004000 9");
	// LCD setting, E_IM_DISP_INTERRUPTION_SELECT_GR0EE
	im_disp1_parent_pctest_wrap(parent, "imdisp SetCBK 1 0x00008000 10");
	// LCD setting, E_IM_DISP_INTERRUPTION_SELECT_LEE
	im_disp1_parent_pctest_wrap(parent, "imdisp SetCBK 1 0x00000100 11");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Int_Callback() error\n", seqNo++));
	// HDMI setting, error, E_IM_DISP_INTERRUPTION_SELECT_VE2
	im_disp1_parent_pctest_wrap(parent, "imdisp SetCBK 0 0xFFEE0E0E 0");
	// LCD setting, error, E_IM_DISP_INTERRUPTION_SELECT_VE2
	im_disp1_parent_pctest_wrap(parent, "imdisp SetCBK 1 0x00000000 0");
	im_disp1_parent_pctest_wrap(parent, "imdisp SetCBK 0 0x00010000 12");	// HDMI setting, NULL
	im_disp1_parent_pctest_wrap(parent, "imdisp SetCBK 1 0x00010000 12");	// LCD setting, NULL

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Int_Callback() normal\n", seqNo++));
	// HDMI setting, E_IM_DISP_INTERRUPTION_SELECT_VE2
	im_disp1_parent_pctest_wrap(parent, "imdisp GetCBK 1 0 0x00010000");
	// HDMI setting, E_IM_DISP_INTERRUPTION_SELECT_VE
	im_disp1_parent_pctest_wrap(parent, "imdisp GetCBK 1 0 0x00100000");
	// HDMI setting, E_IM_DISP_INTERRUPTION_SELECT_GA1REE
	im_disp1_parent_pctest_wrap(parent, "imdisp GetCBK 1 0 0x00000010");
	// HDMI setting, E_IM_DISP_INTERRUPTION_SELECT_GA0REE
	im_disp1_parent_pctest_wrap(parent, "imdisp GetCBK 1 0 0x00000020");
	// HDMI setting, E_IM_DISP_INTERRUPTION_SELECT_GR1REE
	im_disp1_parent_pctest_wrap(parent, "imdisp GetCBK 1 0 0x00000040");
	// HDMI setting, E_IM_DISP_INTERRUPTION_SELECT_GR0REE
	im_disp1_parent_pctest_wrap(parent, "imdisp GetCBK 1 0 0x00000080");
	// HDMI setting, E_IM_DISP_INTERRUPTION_SELECT_LREE
	im_disp1_parent_pctest_wrap(parent, "imdisp GetCBK 1 0 0x00000001");
	// HDMI setting, E_IM_DISP_INTERRUPTION_SELECT_GA1EE
	im_disp1_parent_pctest_wrap(parent, "imdisp GetCBK 1 0 0x00001000");
	// HDMI setting, E_IM_DISP_INTERRUPTION_SELECT_GA0EE
	im_disp1_parent_pctest_wrap(parent, "imdisp GetCBK 1 0 0x00002000");
	// HDMI setting, E_IM_DISP_INTERRUPTION_SELECT_GR1EE
	im_disp1_parent_pctest_wrap(parent, "imdisp GetCBK 1 0 0x00004000");
	// HDMI setting, E_IM_DISP_INTERRUPTION_SELECT_GR0EE
	im_disp1_parent_pctest_wrap(parent, "imdisp GetCBK 1 0 0x00008000");
	// HDMI setting, E_IM_DISP_INTERRUPTION_SELECT_LEE
	im_disp1_parent_pctest_wrap(parent, "imdisp GetCBK 1 0 0x00000100");
	// LCD setting, E_IM_DISP_INTERRUPTION_SELECT_VE2
	im_disp1_parent_pctest_wrap(parent, "imdisp GetCBK 1 1 0x00010000");
	// LCD setting, E_IM_DISP_INTERRUPTION_SELECT_VE
	im_disp1_parent_pctest_wrap(parent, "imdisp GetCBK 1 1 0x00100000");
	// LCD setting, E_IM_DISP_INTERRUPTION_SELECT_GA1REE
	im_disp1_parent_pctest_wrap(parent, "imdisp GetCBK 1 1 0x00000010");
	// LCD setting, E_IM_DISP_INTERRUPTION_SELECT_GA0REE
	im_disp1_parent_pctest_wrap(parent, "imdisp GetCBK 1 1 0x00000020");
	// LCD setting, E_IM_DISP_INTERRUPTION_SELECT_GR1REE
	im_disp1_parent_pctest_wrap(parent, "imdisp GetCBK 1 1 0x00000040");
	// LCD setting, E_IM_DISP_INTERRUPTION_SELECT_GR0REE
	im_disp1_parent_pctest_wrap(parent, "imdisp GetCBK 1 1 0x00000080");
	// LCD setting, E_IM_DISP_INTERRUPTION_SELECT_LREE
	im_disp1_parent_pctest_wrap(parent, "imdisp GetCBK 1 1 0x00000001");
	// LCD setting, E_IM_DISP_INTERRUPTION_SELECT_GA1EE
	im_disp1_parent_pctest_wrap(parent, "imdisp GetCBK 1 1 0x00001000");
	// LCD setting, E_IM_DISP_INTERRUPTION_SELECT_GA0EE
	im_disp1_parent_pctest_wrap(parent, "imdisp GetCBK 1 1 0x00002000");
	// LCD setting, E_IM_DISP_INTERRUPTION_SELECT_GR1EE
	im_disp1_parent_pctest_wrap(parent, "imdisp GetCBK 1 1 0x00004000");
	// LCD setting, E_IM_DISP_INTERRUPTION_SELECT_GR0EE
	im_disp1_parent_pctest_wrap(parent, "imdisp GetCBK 1 1 0x00008000");
	// LCD setting, E_IM_DISP_INTERRUPTION_SELECT_LEE
	im_disp1_parent_pctest_wrap(parent, "imdisp GetCBK 1 1 0x00000100");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Int_Callback() error\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp GetCBK 1 0 0xFFEE0E0E");	// HDMI setting, error
	im_disp1_parent_pctest_wrap(parent, "imdisp GetCBK 1 1 0x00000000");	// LCD setting, error
	im_disp1_parent_pctest_wrap(parent, "imdisp GetCBK 1 0 0x0011F1F1");	// HDMI setting, error
	im_disp1_parent_pctest_wrap(parent, "imdisp GetCBK 0 0 0x00010000");	// HDMI setting, NULL

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_AXI_Status() normal\n", seqNo++));
	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.AXISTS.word = 0x32120003;
	IO_DISP.MAIN[1].DCORE.AXISTS.word = 0x13210002;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetAxi 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetAxi 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_AXI_Status() error\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp GetAxi 0 0");	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetAxi 0 1");	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Output_Parameter_Reflect_Timing() normal\n", seqNo++));

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.word = 2;
	IO_DISP.MAIN[1].DCORE.TRG.word = 2;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// HDMI setting, E_IM_DISP_RPGTMG_VSYNC_VSYNC
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOutRefTiming 0 1");
	// HDMI setting, E_IM_DISP_RPGTMG_VSYNC_FRAME_TOP
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOutRefTiming 0 0");
	// LCD setting, E_IM_DISP_RPGTMG_VSYNC_VSYNC
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOutRefTiming 1 1");
	// LCD setting, E_IM_DISP_RPGTMG_VSYNC_FRAME_TOP
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOutRefTiming 1 0");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Output_Parameter_Reflect_Timing() error\n", seqNo++));

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.word = 3;
	IO_DISP.MAIN[1].DCORE.TRG.word = 3;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// HDMI setting, E_IM_DISP_RPGTMG_VSYNC_VSYNC
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOutRefTiming 0 1");
	// LCD setting, E_IM_DISP_RPGTMG_VSYNC_VSYNC
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOutRefTiming 1 1");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.word = 2;
	IO_DISP.MAIN[1].DCORE.TRG.word = 2;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Output_Parameter_Reflect_Timing() normal\n", seqNo++));
	// LCD setting, E_IM_DISP_RPGTMG_VSYNC_VSYNC
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOutRefTiming 1 1");

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOutRefTiming 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOutRefTiming 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Output_Parameter_Reflect_Timing() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOutRefTiming 0 0");
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOutRefTiming 0 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Output_Parameter_Reflect_Enable() normal\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOutRefEn 0 0");	// HDMI setting, D_IM_DISP_ENABLE_ON
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOutRefEn 0 1");	// HDMI setting, D_IM_DISP_ENABLE_OFF
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOutRefEn 1 0");	// LCD setting, D_IM_DISP_ENABLE_ON
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOutRefEn 1 1");	// LCD setting, D_IM_DISP_ENABLE_OFF

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Output_Parameter_Reflect_Enable() error\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOutRefEn 0 2");	// HDMI setting, error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOutRefEn 1 2");	// LCD setting, error

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Output_Parameter_Reflect_Enable() normal\n", seqNo++));

	im_disp1_parent_pctest_wrap(parent, "imdisp SetOutRefEn 1 0");	// LCD setting, D_IM_DISP_ENABLE_OFF

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOutRefEn 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOutRefEn 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Output_Parameter_Reflect_Enable() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOutRefEn 0 0");
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOutRefEn 0 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_TSL() normal\n", seqNo++));

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.word = 2;
	IO_DISP.MAIN[1].DCORE.TRG.word = 2;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	im_disp1_parent_pctest_wrap(parent, "imdisp SetTSL 0 1");	// HDMI setting, D_IM_DISP_TSL_INTERLACE
	im_disp1_parent_pctest_wrap(parent, "imdisp SetTSL 0 0");	// HDMI setting, D_IM_DISP_TSL_PROGRESSIVE
	im_disp1_parent_pctest_wrap(parent, "imdisp SetTSL 1 1");	// LCD setting, D_IM_DISP_TSL_INTERLACE
	im_disp1_parent_pctest_wrap(parent, "imdisp SetTSL 1 0");	// LCD setting, D_IM_DISP_TSL_PROGRESSIVE

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_TSL() error\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp SetTSL 0 2");	// HDMI setting, error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetTSL 1 2");	// LCD setting, error

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.word = 3;
	IO_DISP.MAIN[1].DCORE.TRG.word = 3;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	im_disp1_parent_pctest_wrap(parent, "imdisp SetTSL 0 1");	// HDMI setting, Status error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetTSL 1 1");	// LCD setting, Status error

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_TSL() normal\n", seqNo++));

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.word = 2;
	IO_DISP.MAIN[1].DCORE.TRG.word = 2;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);
	im_disp1_parent_pctest_wrap(parent, "imdisp SetTSL 1 1");	// LCD setting, D_IM_DISP_TSL_INTERLACE

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetTSL 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetTSL 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_TSL() error\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp GetTSL 0 0");	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetTSL 0 1");	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Output_Size() normal\n", seqNo++));

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.OVSIZE.word = 0x00003FF0;
	IO_DISP.MAIN[0].DCORE.OHSIZE.word = 0x0000FFF0;
	IO_DISP.MAIN[1].DCORE.OVSIZE.word = 0x00003FF1;
	IO_DISP.MAIN[1].DCORE.OHSIZE.word = 0x0000FFF1;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOutSize 3 0");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOutSize 3 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Output_Size() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOutSize 0 0");
	// CtImDisp3_D_CT_IM_DISP_SECOND_PARA_ONLY, LDC setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOutSize 1 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOutSize 2 0");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Force_Out_Data_Enable()\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp SetFOE 0 1");	// HDMI setting, E_IM_DISP_FDOEN_FORCE_DATA_OUT
	im_disp1_parent_pctest_wrap(parent, "imdisp SetFOE 0 0");	// HDMI setting, E_IM_DISP_FDOEN_ORDINARY_OUT
	im_disp1_parent_pctest_wrap(parent, "imdisp SetFOE 1 1");	// LCD setting, E_IM_DISP_FDOEN_FORCE_DATA_OUT
	im_disp1_parent_pctest_wrap(parent, "imdisp SetFOE 1 0");	// LCD setting, E_IM_DISP_FDOEN_ORDINARY_OUT

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Force_Out_Data_Enable() normal\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp SetFOE 0 1");	// HDMI setting, E_IM_DISP_FDOEN_FORCE_DATA_OUT

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetFOE 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetFOE 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Force_Out_Data_Enable() error\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp GetFOE 0 0");	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetFOE 0 1");	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Force_Out_Data()\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp SetFOD 0 0x00FFFEFD");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetFOD 0 0x00000000");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetFOD 1 0x00FFFEFD");	// LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetFOD 1 0x00000000");	// LCD setting, Normal

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Force_Out_Data() normal\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp SetFOD 1 0x00FFFEFD");	// LCD setting, Normal

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetFOD 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetFOD 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Force_Out_Data() error\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp GetFOD 0 0");	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetFOD 0 1");	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Color_Bar_Size() normal\n", seqNo++));

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.OHSIZE.word = 1920;
	IO_DISP.MAIN[1].DCORE.OHSIZE.word = 1920;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	im_disp1_parent_pctest_wrap(parent, "imdisp SetBarSz 0 120");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetBarSz 0 65535");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetBarSz 1 120");	// LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetBarSz 1 65535");	// LCD setting, Normal

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Color_Bar_Size() error\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp SetBarSz 1 0");	// LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetBarSz 0 119");	// HDMI setting, Parameter error

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Color_Bar_Size() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetBarSz 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetBarSz 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Color_Bar_Size() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetBarSz 0 0");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Color_Bar() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetBarCr 1 0 16");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetBarCr 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetBarCr 1 1 16");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetBarCr 1 1 0");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Color_Bar() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetBarCr 1 1 17");
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp SetBarCr 0 0 16");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Color_Bar() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetBarCr 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetBarCr 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Color_Bar() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetBarCr 0 0");
	im_disp1_parent_pctest_wrap(parent, "imdisp GetBarCr 0 1");	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Blend() normal\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp SetBlnd 0 0x00000123");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetBlnd 0 0x00003210");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetBlnd 1 0x00000312");	// LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetBlnd 1 0x00003120");	// LCD setting, Normal

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Blend() error\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp SetBlnd 0 0x00003211");	// HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetBlnd 1 0x00003121");	// LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetBlnd 0 0x00001321");	// HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetBlnd 1 0x00003221");	// LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetBlnd 0 0x00002321");	// HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetBlnd 1 0x00003321");	// LCD setting, Parameter error

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Blend() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetBlnd 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetBlnd 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Blend() error\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp GetBlnd 0 0");	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetBlnd 0 1");	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Output_Matrix() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOutMax 1 0 0 "
			"0x00000FFFFFFF863F 0x000015FFBFFF2DCF 0x00008E8FBFFF000F");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOutMax 1 0 1 "
			"0x0000111122220003 0x0000444455550006 0x0000777788880009");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOutMax 1 1 0 "
			"0xFFFF1FFFFFFF863F 0x000015FFBFFF2DCF 0x00008E8FBFFF000F");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOutMax 1 1 1 "
			"0x0000222211110011 0x0000555544440012 0x0000888877770013");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Output_Matrix() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOutMax 1 0 2 "
			"0xFFFFFFFF863FFFFF 0x000015FFBFFF2DCF 0x00008E8FBFFF000F");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOutMax 1 1 2 "
			"0xFFFFFFFF863FFFFF 0x000015FFBFFF2DCF 0x00008E8FBFFF000F");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, NULL
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOutMax 0 0 0 "\
			"0xFFFFFFFF863FFFFF 0x000015FFBFFF2DCF 0x00008E8FBFFF000F");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, NULL
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOutMax 0 1 1 "\
			"0xFFFFFFFF863FFFFF 0x000015FFBFFF2DCF 0x00008E8FBFFF000F");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Output_Matrix() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_MATRIX_KIND_Y2R
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOutMax 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_MATRIX_KIND_R2Y
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOutMax 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_MATRIX_KIND_Y2R
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOutMax 1 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_MATRIX_KIND_R2Y
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOutMax 1 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Output_Matrix() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_MATRIX_KIND_CC
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOutMax 1 0 2");
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting, E_IM_DISP_MATRIX_KIND_Y2R
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOutMax 0 1 0");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Clip() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetClip 1 0 0");
//	im_disp1_parent_pctest_wrap(parent, "imdisp SetClip 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetClip 1 1 0");
//	im_disp1_parent_pctest_wrap(parent, "imdisp SetClip 1 1 0");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Clip() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetClip 0 0 0");
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetClip 0 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetClip 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetClip 1 1 2");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetClip 1 0 3");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetClip 1 1 4");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetClip 1 0 5");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetClip 1 1 6");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Clip() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetClip 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetClip 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Clip() error\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp GetClip 0 0");	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetClip 0 1");	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Output_Order()\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOutOd 0 0x00000000");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOutOd 0 0x00111111");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOutOd 0 0x00222222");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOutOd 0 0x00321321");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOutOd 1 0x00000000");	// LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOutOd 1 0x00111111");	// LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOutOd 1 0x00222222");	// LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOutOd 1 0x00123123");	// LCD setting, Normal

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Output_Order() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOutOd 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOutOd 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Output_Order() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOutOd 0 0");
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOutOd 0 1");	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Grid() normal\n", seqNo++));

	// SetGrid DSTA,      DSTA,      GLENGTH,   GWIDTH,    GITVL,     GNUM,      GDCTL
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGrid 1 0 0x3FFEFFFE 0x3FFEFFFE "
			"0x3FFEFFFE 0x003E003E 0x3FFEFFFE 0x00070007 0x03FFFFFF");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGrid 1 0 0x00000000 0x00000000 "
			"0x00080008 0x00020002 0x00040004 0x00000000 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGrid 1 1 0x3FFEFFFE 0x3FFEFFFE "
			"0x3FFEFFFE 0x003E003E 0x3FFEFFFE 0x00070007 0x03FFFFFF");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGrid 1 1 0x00000000 0x00000000 "
			"0x00080008 0x00020002 0x00040004 0x00000000 0x00000000");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Grid() error\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGrid");				// NULL

	// SetGrid DSTA,    DSTA,      GLENGTH,   GWIDTH,    GITVL,     GNUM,      GDCTL
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGrid 0 0 0x00000001 0x00000000 "
			"0x00080008 0x00020002 0x00040004 0x00000000 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGrid 0 1 0x00000001 0x00000000 "
			"0x00080008 0x00020002 0x00040004 0x00000000 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGrid 1 0 0x00000001 0x00000000 "
			"0x00080008 0x00020002 0x00040004 0x00000000 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGrid 1 1 0x00010000 0x00000000 "
			"0x00080008 0x00020002 0x00040004 0x00000000 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGrid 1 0 0x00000000 0x00000001 "
			"0x00080008 0x00020002 0x00040004 0x00000000 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGrid 1 1 0x00000000 0x00010000 "
			"0x00080008 0x00020002 0x00040004 0x00000000 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGrid 1 0 0x00000000 0x00000000 "
			"0x00080009 0x00020002 0x00040004 0x00000000 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGrid 1 1 0x00000000 0x00000000 "
			"0x00080006 0x00020002 0x00040004 0x00000000 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGrid 1 0 0x00000000 0x00000000 "
			"0x00090008 0x00020002 0x00040004 0x00000000 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGrid 1 1 0x00000000 0x00000000 "
			"0x00060008 0x00020003 0x00040004 0x00000000 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGrid 1 0 0x00000000 0x00000000 "
			"0x00080008 0x00020003 0x00040004 0x00000000 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGrid 1 1 0x00000000 0x00000000 "
			"0x00080008 0x00020000 0x00040004 0x00000000 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGrid 1 0 0x00000000 0x00000000 "
			"0x00080008 0x00030002 0x00040004 0x00000000 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGrid 1 1 0x00000000 0x00000000 "
			"0x00080008 0x00000002 0x00040004 0x00000000 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGrid 1 0 0x00000000 0x00000000 "
			"0x00080008 0x00020002 0x00040005 0x00000000 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGrid 1 1 0x00000000 0x00000000 "
			"0x00080008 0x00020002 0x00040002 0x00000000 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGrid 1 0 0x00000000 0x00000000 "
			"0x00080008 0x00020002 0x00050004 0x00000000 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGrid 1 1 0x00000000 0x00000000 "
			"0x00080008 0x00020002 0x00020004 0x00000000 0x00000000");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Grid() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetGrid 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetGrid 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Grid() error\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp GetGrid 0 0");	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetGrid 0 1");	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Grid_Enable()\n", seqNo++));
	// HDMI setting, E_IM_DISP_GDISPEN_NOT_DISPLAY
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGridEn 0 0");
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGridEn 0 1");	// HDMI setting, E_IM_DISP_GDISPEN_DISPLAY
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGridEn 1 0");	// LCD setting, E_IM_DISP_GDISPEN_NOT_DISPLAY
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGridEn 1 1");	// LCD setting, E_IM_DISP_GDISPEN_DISPLAY

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Grid_Enable() normal\n", seqNo++));
	// HDMI setting, E_IM_DISP_GDISPEN_NOT_DISPLAY
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGridEn 0 0");

	// HDMI setting, E_IM_DISP_GDISPEN_NOT_DISPLAY
	im_disp1_parent_pctest_wrap(parent, "imdisp GetGridEn 1 0");
	im_disp1_parent_pctest_wrap(parent, "imdisp GetGridEn 1 1");	// HDMI setting, E_IM_DISP_GDISPEN_DISPLAY

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Grid_Enable() error\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp GetGridEn 0 0");	// LCD setting, E_IM_DISP_GDISPEN_NOT_DISPLAY
	im_disp1_parent_pctest_wrap(parent, "imdisp GetGridEn 0 1");	// LCD setting, E_IM_DISP_GDISPEN_DISPLAY

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Face_Frame() normal\n", seqNo++));
	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetFace 0 42 0x00000000 "
			"0x00080008 0x00020002 0x00000000 0x000003FFFFFFFFF1 15");
	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetFace 0 1 0x3FFEFFFE "
			"0x3FFEFFFE 0x003E003E 0x00FFFFFF 0x000003FFFFFFFFF2 14");
	// LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetFace 1 42 0x00000000 "
			"0x00080008 0x00020002 0x00000000 0x000003FFFFFFFFF3 13");
	// LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetFace 1 1 0x3FFEFFFE "
			"0x3FFEFFFE 0x003E003E 0x00FFFFFF 0x000003FFFFFFFFF4 12");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Face_Frame() error\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp SetFace 0");	// NULL
	// Frame Count error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetFace 0 43 0x00000000 "
			"0x00080008 0x00020002 0x00000000 0x000003FFFFFFFFFF 15");
	// DSH error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetFace 0 1 0x00000001 "
			"0x00080008 0x00020002 0x00000000 0x000003FFFFFFFFFF 15");
	// DSV error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetFace 0 1 0x00010000 "
			"0x00080008 0x00020002 0x00000000 0x000003FFFFFFFFFF 15");
	// FFHSZ error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetFace 0 1 0x00000000 "
			"0x00080009 0x00020002 0x00000000 0x000003FFFFFFFFFF 15");
	// FFHSZ error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetFace 0 1 0x00000000 "
			"0x00080006 0x00020002 0x00000000 0x000003FFFFFFFFFF 15");
	// FFVSZ error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetFace 0 1 0x00000000 "
			"0x00090008 0x00020002 0x00000000 0x000003FFFFFFFFFF 15");
	// FFVSZ error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetFace 0 1 0x00000000 "
			"0x00060008 0x00020002 0x00000000 0x000003FFFFFFFFFF 15");
	// FFHWID error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetFace 0 1 0x00000000 "
			"0x00080008 0x00020003 0x00000000 0x000003FFFFFFFFFF 15");
	// FFHWID error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetFace 0 1 0x00000000 "
			"0x00080008 0x00020001 0x00000000 0x000003FFFFFFFFFF 15");
	// FFVWID error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetFace 0 1 0x00000000 "
			"0x00080008 0x00030002 0x00000000 0x000003FFFFFFFFFF 15");
	// FFVWID error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetFace 0 1 0x00000000 "
			"0x00080008 0x00010002 0x00000000 0x000003FFFFFFFFFF 15");
	// MSFF error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetFace 0 1 0x00000000 "
			"0x00080008 0x00020002 0x00000000 0x000003FFFFFFFFFF 16");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Face_Frame() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetFace 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetFace 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Face_Frame() error\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp GetFace 0 0");	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetFace 0 1");	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Face_Frame_Enable() normal\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp SetFaceEn 0 0x00000000FFFFFFF1 0");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetFaceEn 0 0x000003F200000000 15");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetFaceEn 1 0x00000000FFFFFFF3 0");	// LCD setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetFaceEn 1 0x000003F400000000 15");	// LCD setting, Normal

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Face_Frame_Enable() error\n", seqNo++));
	im_disp1_parent_pctest_wrap(parent, "imdisp SetFaceEn 0 0x00000000FFFFFFF1 16");	// HDMI setting, Normal
	im_disp1_parent_pctest_wrap(parent, "imdisp SetFaceEn 1 0x000003F500000000 16");	// LCD setting, Normal

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Face_Frame_Enable() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetFaceEn 3 0");
	// CtImDisp3_D_CT_IM_DISP_BOTH_PARA, LCD setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetFaceEn 3 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Face_Frame_Enable() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetFaceEn 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetFaceEn 1 0");
	// CtImDisp3_D_CT_IM_DISP_SECOND_PARA_ONLY, HDMI setting
	im_disp1_parent_pctest_wrap(parent, "imdisp GetFaceEn 2 1");

	*pSeqNo = seqNo;
	return ktrue;
}
#endif /*CtImDisp_CO_DEBUG_DISP*/

CtImDisp1c *ct_im_disp1c_new()
{
	CtImDisp1c *self = (CtImDisp1c *) k_object_new_with_private(CT_TYPE_IM_DISP1C,sizeof(CtImDisp1cPrivate));
	if(!self){//Ddim_Assertion(self)
		Ddim_Print(("!! new CtImDisp1c NULL: %s (%d)", __FILE__, __LINE__));
		return NULL;
	}
	return self;
}
