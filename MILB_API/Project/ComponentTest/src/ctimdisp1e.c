/*
 *ctimdisp1e.c
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-11
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
#include "ctimdisp1e.h"

K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(CtImDisp1e, ct_im_disp1e, IM_TYPE_DISP1_PARENT)
#define CT_IM_DISP1E_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), CtImDisp1ePrivate, CT_TYPE_IM_DISP1E))

struct _CtImDisp1ePrivate
{
	kpointer qwertyu;
};

/*
 * DECLS
 * */
#ifdef CtImDisp_CO_DEBUG_DISP
static kboolean imDisp1eDoPctest_od(ImDisp1Parent *parent, kint32 *pSeqNo);
#endif /*CtImDisp_CO_DEBUG_DISP*/

/*
 * IMPL
 * */
static void ct_im_disp1e_constructor(CtImDisp1e *self)
{
	//CtImDisp1ePrivate *priv = CT_IM_DISP1E_GET_PRIVATE(self);
#ifdef CtImDisp_CO_DEBUG_DISP
	ImDisp1Parent *parent = (ImDisp1Parent *)self;
	parent->pctestFunc = imDisp1eDoPctest_od;
#endif /*CtImDisp_CO_DEBUG_DISP*/
}

static void ct_im_disp1e_destructor(CtImDisp1e *self)
{
}

#ifdef CtImDisp_CO_DEBUG_DISP
static kboolean imDisp1eDoPctest_od(ImDisp1Parent *parent, kint32 *pSeqNo)
{
//	CtImDisp1d *self = (CtImDisp1d *)parent;
	kint32 seqNo = *pSeqNo;
	ImDisp1Group *imDisp1Group = (ImDisp1Group *)im_disp1_parent_get_group(parent);
	// kuchar *pImDispHclkCounter = im_disp1_group_get_hclk_counter(imDisp1Group);

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_OSD_Blink_Timer() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDBTim 0 1 0x0008");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0/1(error)
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDBTim 1 1 0x000C");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, other(error)
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDBTim 1 1 0xFFF3");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_OSD_Resize() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, rsz0~rsz3
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDRes 1 0 0x0004 "
			"0x00000000 0x0000050a 0x0000050a 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0/1, rsz0~rsz3
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDRes 1 0 0x000C "
			"0x00000001 0x0800050a 0x06000514 0x00003214");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, rsz0~rsz3
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDRes 1 0 0x0008 "
			"0x00000000 0x0000050a 0x0000050a 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, rsz0~rsz3
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDRes 1 1 0x0004 "
			"0x00000001 0x0800050a 0x06000514 0x00003214");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0/1, rsz0~rsz3
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDRes 1 1 0x000C "
			"0x00000000 0x0000050a 0x0000050a 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, rsz0~rsz3
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDRes 1 1 0x0008 "
			"0x00000001 0x0800050a 0x06000514 0x00003214");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_OSD_Resize() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, rsz0~rsz3
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDRes 0 1 0x0008 "
			"0x00000001 0x0800050a 0x06000514 0x00003214");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, other, rsz0~rsz3(error)
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDRes 1 0 0xFFF3 "
			"0x00000000 0x0100320a 0x0100050a 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, rsz0~rsz3
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDRes 1 0 0x0004 "
			"0x00000000 0x00001f0a 0x0000050a 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, rsz0~rsz3
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDRes 1 0 0x0004 "
			"0x00000000 0x0000201F 0x0000050a 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, rsz0~rsz3
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDRes 1 0 0x0004 "
			"0x00000000 0x0800050a 0x0000050a 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, rsz0~rsz3
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDRes 1 0 0x0004 "
			"0x00000001 0x08000a0a 0x0000050a 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, rsz0~rsz3
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDRes 1 0 0x0004 "
			"0x00000001 0x0a00050a 0x0000050a 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, rsz0~rsz3
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDRes 1 0 0x0004 "
			"0x00000001 0x0c00050a 0x0000050a 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, rsz0~rsz3
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDRes 1 0 0x0004 "
			"0x00000000 0x0000050a 0x00001f0a 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, rsz0~rsz3
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDRes 1 0 0x0004 "
			"0x00000000 0x0000050a 0x0000201F 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, rsz0~rsz3
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDRes 1 0 0x0004 "
			"0x00000000 0x0000050a 0x0200050a 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, rsz0~rsz3
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDRes 1 0 0x0004 "
			"0x00000001 0x0000050a 0x02000a0a 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, rsz0~rsz3
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDRes 1 0 0x0004 "
			"0x00000001 0x0000050a 0x0a00050a 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, rsz0~rsz3
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDRes 1 0 0x0004 "
			"0x00000001 0x0000050a 0x0b00050a 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, rsz0~rsz3
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDRes 1 0 0x0004 "
			"0x00000000 0x0000050a 0x0000050a 0x0000003f");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, rsz0~rsz3
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDRes 1 0 0x0004 "
			"0x00000000 0x0000050a 0x0000050a 0x00000100");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_OSD_Resize() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDRes 1 0 0x0004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDRes 1 0 0x0008");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDRes 1 1 0x0004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDRes 1 1 0x0008");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_OSD_Resize() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDRes 0 1 0x0008");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0/1(error)
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDRes 1 0 0x000C");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, other(error)
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDRes 1 0 0xFFF3");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_OSD_Matrix() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, gry2r0~2
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDMax 1 0 0x0004 0x00000000 0x00000000 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0/1, gry2r0~2
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDMax 1 0 0x000C 0x00FFFFFF 0x00FFFFFF 0x00FFFFFF");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, gry2r0~2
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDMax 1 0 0x0004 0x005A0040 0x00D3EA40 0x00FF7140");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0/1, gry2r0~2
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDMax 1 0 0x000C 0x00042D0D 0x0020E8F9 0x00FEE320");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, gry2r0~2
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDMax 1 0 0x0008 0x00650040 0x00E2F440 0x00007740");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, gry2r0~2
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDMax 1 1 0x0004 0x00000000 0x00000000 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0/1, gry2r0~2
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDMax 1 1 0x000C 0x00FFFFFF 0x00FFFFFF 0x00FFFFFF");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, gry2r0~2
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDMax 1 1 0x0004 0x005A0040 0x00D3EA40 0x00FF7140");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0/1, gry2r0~2
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDMax 1 1 0x000C 0x00042D0D 0x0020E8F9 0x00FEE320");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, gry2r0~2
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDMax 1 1 0x0008 0x00650040 0x00E2F440 0x00007740");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_OSD_Matrix() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, gry2r0~2
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDMax 0 0 0x0004 0x00000000 0x00000000 0x00000000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_MAIN(error), gry2r0~2
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDMax 1 0 0x0001 0x000000FF 0x0000FF00 0x00FF0000");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, other(error), gry2r0~2
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDMax 1 0 0xFFF3 0x000000FF 0x0000FF00 0x00FF0000");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_OSD_Matrix() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDMax 1 0 0x0004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDMax 1 0 0x0008");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDMax 1 1 0x0004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDMax 1 1 0x0008");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_OSD_Matrix() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDMax 0 1 0x0004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0/1
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDMax 1 0 0x000C");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_OSD_Alpha() normal\n", seqNo++));
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0, alpha
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAph 0 0x0004 0x000000FF");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0/1, alpha
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAph 0 0x000C 0x00000000");
	// HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1, alpha
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAph 0 0x0008 0x00000001");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0, alpha
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAph 1 0x0004 0x00000001");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_0/1, alpha
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAph 1 0x000C 0x00000000");
	// LCD setting, E_IM_DISP_SEL_LAYER_OSD_1, alpha
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAph 1 0x0008 0x000000FF");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_OSD_Alpha() error\n", seqNo++));
	// HDMI setting, E_IM_DISP_SEL_LAYER_MAIN(error), alpha
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAph 0 0x0001 0x000000FF");
	// LCD setting, E_IM_DISP_SEL_LAYER_MAIN(error), alpha
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAph 1 0x0001 0x00000000");
	// HDMI setting, other(error), alpha
	im_disp1_parent_pctest_wrap(parent, "imdisp SetOSDAph 0 0xFFF3 0x000000FF");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_OSD_Alpha() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAph 1 0 0x00000004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAph 1 0 0x00000008");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAph 1 1 0x00000004");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAph 1 1 0x00000008");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_OSD_Alpha() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting, E_IM_DISP_SEL_LAYER_OSD_1
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAph 0 0 0x0008");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, E_IM_DISP_SEL_LAYER_OSD_0/1(error)
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAph 1 1 0x000C");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, other(error)
	im_disp1_parent_pctest_wrap(parent, "imdisp GetOSDAph 1 1 0xFFF3");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Anti_Gamma_Table() normal\n", seqNo++));

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LTRG.word = 2;
	IO_DISP.MAIN[0].GRCH[0].GRTRG.word = 2;
	IO_DISP.MAIN[0].GRCH[1].GRTRG.word = 2;
	IO_DISP.MAIN[1].LCH.LTRG.word = 2;
	IO_DISP.MAIN[1].GRCH[0].GRTRG.word = 2;
	IO_DISP.MAIN[1].GRCH[1].GRTRG.word = 2;

	IO_DISP.MAIN[0].LCH.LTBLASET.bit.IGTAEN = 1;
//	IO_DISP.MAIN[0].GRCH[0].GRTBLASET.bit.IGTAEN = 1;
//	IO_DISP.MAIN[0].GRCH[1].GRTBLASET.bit.IGTAEN = 1;
	IO_DISP.MAIN[1].LCH.LTBLASET.bit.IGTAEN = 1;
//	IO_DISP.MAIN[1].GRCH[0].GRTBLASET.bit.IGTAEN = 1;
//	IO_DISP.MAIN[1].GRCH[1].GRTBLASET.bit.IGTAEN = 1;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp SetAnTbl 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp SetAnTbl 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp SetAnTbl 1 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp SetAnTbl 1 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Anti_Gamma_Table() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetAnTbl 1 0 2");
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp SetAnTbl 0 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetAnTbl 1 1 2");
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp SetAnTbl 0 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Anti_Gamma_Table() normal\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp GetAnTbl 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp GetAnTbl 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp GetAnTbl 1 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp GetAnTbl 1 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Anti_Gamma_Table() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp GetAnTbl 1 0 2");
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp GetAnTbl 0 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp GetAnTbl 1 1 3");
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, HDMI setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp GetAnTbl 0 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Main_Gamma_Table() normal\n", seqNo++));

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LTRG.word = 2;	// NO ACT
	IO_DISP.MAIN[1].LCH.LTRG.word = 2;	// NO ACT
	IO_DISP.MAIN[0].LCH.LTBLASET.bit.GMTSL = 0;	// A
	IO_DISP.MAIN[1].LCH.LTBLASET.bit.GMTSL = 0;	// A
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp SetMainGamTbl 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp SetMainGamTbl 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp SetMainGamTbl 1 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp SetMainGamTbl 1 1 1");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LTBLASET.bit.GMTSL = 1;	// B
	IO_DISP.MAIN[1].LCH.LTBLASET.bit.GMTSL = 1;	// B
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp SetMainGamTbl 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp SetMainGamTbl 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp SetMainGamTbl 1 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp SetMainGamTbl 1 1 1");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LTRG.word = 3;	// ACT
	IO_DISP.MAIN[1].LCH.LTRG.word = 3;	// ACT
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp SetMainGamTbl 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp SetMainGamTbl 1 1 0");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LTBLASET.bit.GMTSL = 0;	// A
	IO_DISP.MAIN[1].LCH.LTBLASET.bit.GMTSL = 0;	// A
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp SetMainGamTbl 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp SetMainGamTbl 1 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Main_Gamma_Table() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetMainGamTbl 1 0 2");
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp SetMainGamTbl 0 1 0");

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp SetMainGamTbl 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp SetMainGamTbl 1 1 0");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LTBLASET.bit.GMTSL = 1;	// B
	IO_DISP.MAIN[1].LCH.LTBLASET.bit.GMTSL = 1;	// B
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp SetMainGamTbl 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp SetMainGamTbl 1 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Main_Gamma_Table() normal\n", seqNo++));

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LTRG.word = 2;	// NO ACT
	IO_DISP.MAIN[1].LCH.LTRG.word = 2;	// NO ACT
	IO_DISP.MAIN[0].LCH.LTBLASET.bit.GMTSL = 0;	// A
	IO_DISP.MAIN[1].LCH.LTBLASET.bit.GMTSL = 0;	// A
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp GetMainGamTbl 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp GetMainGamTbl 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp GetMainGamTbl 1 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp GetMainGamTbl 1 1 1");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LTBLASET.bit.GMTSL = 1;	// B
	IO_DISP.MAIN[1].LCH.LTBLASET.bit.GMTSL = 1;	// B
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp GetMainGamTbl 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp GetMainGamTbl 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp GetMainGamTbl 1 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp GetMainGamTbl 1 1 1");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LTRG.word = 3;	// ACT
	IO_DISP.MAIN[1].LCH.LTRG.word = 3;	// ACT
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp GetMainGamTbl 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp GetMainGamTbl 1 1 0");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LTBLASET.bit.GMTSL = 0;	// A
	IO_DISP.MAIN[1].LCH.LTBLASET.bit.GMTSL = 0;	// A
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp GetMainGamTbl 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp GetMainGamTbl 1 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Main_Gamma_Table() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp GetMainGamTbl 1 0 2");
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp GetMainGamTbl 0 1 0");

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp GetMainGamTbl 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp GetMainGamTbl 1 1 0");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LTBLASET.bit.GMTSL = 1;	// B
	IO_DISP.MAIN[1].LCH.LTBLASET.bit.GMTSL = 1;	// B
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp GetMainGamTbl 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp GetMainGamTbl 1 1 1");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].LCH.LTRG.word = 2;	// NO ACT
	IO_DISP.MAIN[1].LCH.LTRG.word = 2;	// NO ACT
	IO_DISP.MAIN[0].LCH.LTBLASET.bit.GMTSL = 0;	// A
	IO_DISP.MAIN[1].LCH.LTBLASET.bit.GMTSL = 0;	// A
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Dcore_Gamma_Table() normal\n", seqNo++));

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.bit.TRG = 2;	// NO ACT
	IO_DISP.MAIN[1].DCORE.TRG.bit.TRG = 2;	// NO ACT
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.GMTSL = 0;	// A
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.GMTSL = 0;	// A
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp SetDcoreGamTbl 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp SetDcoreGamTbl 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp SetDcoreGamTbl 1 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp SetDcoreGamTbl 1 1 1");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.GMTSL = 1;	// B
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.GMTSL = 1;	// B
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp SetDcoreGamTbl 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp SetDcoreGamTbl 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp SetDcoreGamTbl 1 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp SetDcoreGamTbl 1 1 1");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.bit.TRG = 3;	// ACT
	IO_DISP.MAIN[1].DCORE.TRG.bit.TRG = 3;	// ACT
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.GMTSL = 1;	// B
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.GMTSL = 1;	// B
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp SetDcoreGamTbl 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp SetDcoreGamTbl 1 1 0");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.GMTSL = 0;	// A
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.GMTSL = 0;	// A
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp SetDcoreGamTbl 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp SetDcoreGamTbl 1 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Dcore_Gamma_Table() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetDcoreGamTbl 1 0 2");
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp SetDcoreGamTbl 0 1 0");

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp SetDcoreGamTbl 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp SetDcoreGamTbl 1 1 0");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.GMTSL = 1;	// B
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.GMTSL = 1;	// B
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp SetDcoreGamTbl 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp SetDcoreGamTbl 1 1 1");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.bit.TRG = 2;	// NO ACT
	IO_DISP.MAIN[1].DCORE.TRG.bit.TRG = 2;	// NO ACT
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.GMTSL = 0;	// A
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.GMTSL = 0;	// A
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Dcore_Gamma_Table() normal\n", seqNo++));

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.bit.TRG = 2;	// NO ACT
	IO_DISP.MAIN[1].DCORE.TRG.bit.TRG = 2;	// NO ACT
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.GMTSL = 0;	// A
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.GMTSL = 0;	// A
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp GetDcoreGamTbl 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp GetDcoreGamTbl 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp GetDcoreGamTbl 1 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp GetDcoreGamTbl 1 1 1");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.GMTSL = 1;	// B
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.GMTSL = 1;	// B
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp GetDcoreGamTbl 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp GetDcoreGamTbl 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp GetDcoreGamTbl 1 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp GetDcoreGamTbl 1 1 1");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.bit.TRG = 3;	// ACT
	IO_DISP.MAIN[1].DCORE.TRG.bit.TRG = 3;	// ACT
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp GetDcoreGamTbl 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp GetDcoreGamTbl 1 1 0");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.GMTSL = 0;	// A
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.GMTSL = 0;	// A
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp GetDcoreGamTbl 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp GetDcoreGamTbl 1 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Dcore_Gamma_Table() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp GetDcoreGamTbl 1 0 2");
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp GetDcoreGamTbl 0 1 0");

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp GetDcoreGamTbl 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp GetDcoreGamTbl 1 1 0");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.GMTSL = 1;	// B
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.GMTSL = 1;	// B
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp GetDcoreGamTbl 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp GetDcoreGamTbl 1 1 1");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.bit.TRG = 2;	// NO ACT
	IO_DISP.MAIN[1].DCORE.TRG.bit.TRG = 2;	// NO ACT
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.GMTSL = 0;	// A
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.GMTSL = 0;	// A
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Luminance_Table() normal\n", seqNo++));

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.bit.TRG = 2;	// NO ACT
	IO_DISP.MAIN[1].DCORE.TRG.bit.TRG = 2;	// NO ACT
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.YSATSL = 0;	// A
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.YSATSL = 0;	// A
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp SetLumiTbl 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp SetLumiTbl 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp SetLumiTbl 1 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp SetLumiTbl 1 1 1");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.YSATSL = 1;	// B
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.YSATSL = 1;	// B
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp SetLumiTbl 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp SetLumiTbl 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp SetLumiTbl 1 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp SetLumiTbl 1 1 1");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.bit.TRG = 3;	// ACT
	IO_DISP.MAIN[1].DCORE.TRG.bit.TRG = 3;	// ACT
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp SetLumiTbl 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp SetLumiTbl 1 1 0");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.YSATSL = 0;	// A
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.YSATSL = 0;	// A
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp SetLumiTbl 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp SetLumiTbl 1 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Luminance_Table() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetLumiTbl 1 0 2");
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp SetLumiTbl 0 1 0");

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp SetLumiTbl 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp SetLumiTbl 1 1 0");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.YSATSL = 1;	// B
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.YSATSL = 1;	// B
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp SetLumiTbl 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp SetLumiTbl 1 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Luminance_Table() normal\n", seqNo++));

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.bit.TRG = 2;	// NO ACT
	IO_DISP.MAIN[1].DCORE.TRG.bit.TRG = 2;	// NO ACT
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.YSATSL = 0;	// A
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.YSATSL = 0;	// A
	IO_DISP_TBL.MAIN[0].DCORE.YSTBLAYT.hword[0] = 0x0100;
	IO_DISP_TBL.MAIN[0].DCORE.YSTBLBYT.hword[0] = 0x0101;
	IO_DISP_TBL.MAIN[1].DCORE.YSTBLAYT.hword[0] = 0x0200;
	IO_DISP_TBL.MAIN[1].DCORE.YSTBLBYT.hword[0] = 0x0201;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp GetLumiTbl 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp GetLumiTbl 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp GetLumiTbl 1 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp GetLumiTbl 1 1 1");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.YSATSL = 1;	// B
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.YSATSL = 1;	// B
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp GetLumiTbl 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp GetLumiTbl 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp GetLumiTbl 1 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp GetLumiTbl 1 1 1");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.bit.TRG = 3;	// ACT
	IO_DISP.MAIN[1].DCORE.TRG.bit.TRG = 3;	// ACT
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp GetLumiTbl 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp GetLumiTbl 1 1 0");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.YSATSL = 0;	// A
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.YSATSL = 0;	// A
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp GetLumiTbl 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp GetLumiTbl 1 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Luminance_Table() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp GetLumiTbl 1 0 2");
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp GetLumiTbl 0 1 0");

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp GetLumiTbl 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp GetLumiTbl 1 1 0");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.YSATSL = 1;	// B
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.YSATSL = 1;	// B
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp GetLumiTbl 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp GetLumiTbl 1 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Chroma_Gain_Table() normal\n", seqNo++));

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.bit.TRG = 2;	// NO ACT
	IO_DISP.MAIN[1].DCORE.TRG.bit.TRG = 2;	// NO ACT
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.YSATSL = 0;	// A
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.YSATSL = 0;	// A
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGainTbl 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGainTbl 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGainTbl 1 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGainTbl 1 1 1");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.YSATSL = 1;	// B
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.YSATSL = 1;	// B
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGainTbl 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGainTbl 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGainTbl 1 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGainTbl 1 1 1");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.bit.TRG = 3;	// ACT
	IO_DISP.MAIN[1].DCORE.TRG.bit.TRG = 3;	// ACT
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGainTbl 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGainTbl 1 1 0");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.YSATSL = 0;	// A
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.YSATSL = 0;	// A
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGainTbl 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGainTbl 1 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Set_Chroma_Gain_Table() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGainTbl 1 0 2");
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGainTbl 0 1 0");

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGainTbl 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGainTbl 1 1 0");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.YSATSL = 1;	// B
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.YSATSL = 1;	// B
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGainTbl 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp SetGainTbl 1 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Chroma_Gain_Table() normal\n", seqNo++));

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.bit.TRG = 2;	// NO ACT
	IO_DISP.MAIN[1].DCORE.TRG.bit.TRG = 2;	// NO ACT
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.YSATSL = 0;	// A
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.YSATSL = 0;	// A
	IO_DISP_TBL.MAIN[0].DCORE.YSTBLACG.hword[0] = 0x0100;
	IO_DISP_TBL.MAIN[0].DCORE.YSTBLBCG.hword[0] = 0x0101;
	IO_DISP_TBL.MAIN[1].DCORE.YSTBLACG.hword[0] = 0x0200;
	IO_DISP_TBL.MAIN[1].DCORE.YSTBLBCG.hword[0] = 0x0201;
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp GetGainTbl 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp GetGainTbl 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp GetGainTbl 1 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp GetGainTbl 1 1 1");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.YSATSL = 1;	// B
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.YSATSL = 1;	// B
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp GetGainTbl 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp GetGainTbl 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp GetGainTbl 1 1 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp GetGainTbl 1 1 1");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TRG.bit.TRG = 3;	// ACT
	IO_DISP.MAIN[1].DCORE.TRG.bit.TRG = 3;	// ACT
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp GetGainTbl 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp GetGainTbl 1 1 0");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.YSATSL = 0;	// A
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.YSATSL = 0;	// A
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp GetGainTbl 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp GetGainTbl 1 1 1");

	Ddim_Print(("*** [CT] 01-01-%03d : Im_DISP_Get_Chroma_Gain_Table() error\n", seqNo++));
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, Parameter error
	im_disp1_parent_pctest_wrap(parent, "imdisp GetGainTbl 1 0 2");
	// CtImDisp3_D_CT_IM_DISP_NO_PARA, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp GetGainTbl 0 1 0");

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp GetGainTbl 1 0 0");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_A
	im_disp1_parent_pctest_wrap(parent, "imdisp GetGainTbl 1 1 0");

	im_disp1_group_ct_im_disp3_pclk_counter_on(imDisp1Group);
	IO_DISP.MAIN[0].DCORE.TBLASET.bit.YSATSL = 1;	// B
	IO_DISP.MAIN[1].DCORE.TBLASET.bit.YSATSL = 1;	// B
	im_disp1_group_ct_im_disp3_pclk_counter_off(imDisp1Group);

	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, HDMI setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp GetGainTbl 1 0 1");
	// CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY, LCD setting, D_IM_DISP_TABLE_SURFACE_B
	im_disp1_parent_pctest_wrap(parent, "imdisp GetGainTbl 1 1 1");

	*pSeqNo = seqNo;
	return ktrue;
}
#endif /*CtImDisp_CO_DEBUG_DISP*/

/*
 * PUBLIC
 * */

CtImDisp1e *ct_im_disp1e_new(void)
{
	CtImDisp1e *self = (CtImDisp1e *) k_object_new_with_private(CT_TYPE_IM_DISP1E,sizeof(CtImDisp1ePrivate));
	return self;
}
