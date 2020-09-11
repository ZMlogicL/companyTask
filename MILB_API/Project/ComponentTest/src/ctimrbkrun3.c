/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :jianghaodong
*@brief               :CtImRbkRun3类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#include "ct_im_ltm.h"

#include "im_ltm.h"
#include "im_pro.h"
#include "im_pro_common.h"

#include "driver_common.h"
#include "ddim_user_custom.h"
//#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
//#endif

#include "jdsltm.h"

#include <stdlib.h>
#include <string.h>

#include "ctimltmrbk.h"
#include "ctimrbkrun2.h"
#include "ctimrbkrun3.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtImRbkRun3, ct_im_rbk_run3);
#define CT_IM_RBK_RUN3_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtImRbkRun3Private,CT_TYPE_IM_RBK_RUN3))

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
#define IM_LTM_RBK_ROUNDUP_N( val, align_val )	( ( ( (val) + (align_val - 1) ) / align_val ) * align_val )

struct _CtImRbkRun3Private
{
	CtImRbkRun1* ctImRbkRun1;
	CtImRbkRun2* ctImRbkRun2;
	T_IM_LTM_RBK_CTRL_SDRAM_INPUT *gctImLtmRbkCtrlSdramInBase;
	T_IM_LTM_RBK_OUTDATA_INFO *gctImLtmRbkOutdataBase;
};

static T_IM_LTM_INADDR_INFO S_GCT_IM_LTM_RBK_IN_ADDR_BASE = {
	.addr_r = (void*)D_IM_LTM_RBK_IMG_MEM_IN_R_ADDR_TOP,
	.addr_g = (void*)D_IM_LTM_RBK_IMG_MEM_IN_G_ADDR_TOP,
	.addr_b = (void*)D_IM_LTM_RBK_IMG_MEM_IN_B_ADDR_TOP,
};

T_IM_LTM_RBK_OUTDATA_INFO gctImLtmRbkOutdataBase = {
	.addr = (void*)D_IM_LTM_RBK_IMG_MEM_OUT_RGB_ADDR_TOP,
	.global_width = IM_LTM_RBK_ROUNDUP_N( D_IM_LTM_RBK_DST_IMG_GLOBAL_WIDTH_UP, 512 ),
};

T_IM_LTM_RBK_CTRL_SDRAM_INPUT gctImLtmRbkCtrlSdramInBase = {
	.burst_length_r = D_IM_LTM_BRST_512,
	.burst_length_g = D_IM_LTM_BRST_512,
	.burst_length_b = D_IM_LTM_BRST_512,
	.input_global = D_IM_LTM_RBK_SRC_IMG_RGB_GLOBAL_WIDTH,
	.input_rect = {
		.img_top = 0,
		.img_left = 0,
		.img_width = D_IM_LTM_RBK_SRC_IMG_PIXS_WIDTH,
		.img_lines = D_IM_LTM_RBK_SRC_IMG_PIXS_LINES,
	},
	.shift_enable = D_IM_LTM_ENABLE_ON,
};

/*
*IMPL
*/
static void ct_im_rbk_run3_constructor(CtImRbkRun3 *self) 
{
	CtImRbkRun3Private *priv = CT_IM_RBK_RUN3_GET_PRIVATE(self);
	priv->ctImRbkRun1=NULL;
	priv->ctImRbkRun2=NULL;
	priv->gctImLtmRbkCtrlSdramInBase=&gctImLtmRbkCtrlSdramInBase;
	priv->gctImLtmRbkOutdataBase=&gctImLtmRbkOutdataBase;
}

static void ct_im_rbk_run3_destructor(CtImRbkRun3 *self) 
{
}

/*
*PUBLIC
*/
#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run3_3_1: "
kint32 ct_im_rbk_run3_3_1(CtImRbkRun3* self)
{
	CtImRbkRun3Private *priv = CT_IM_RBK_RUN3_GET_PRIVATE(self);

#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_RBK_SW_Reset( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_RBK_SW_Reset( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
#endif

	ct_im_ltm_rbk_print_all_reg();

	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run3_3_2: "
kint32 ct_im_rbk_run3_3_2(CtImRbkRun3* self)
{
	CtImRbkRun3Private *priv = CT_IM_RBK_RUN3_GET_PRIVATE(self);

	T_IM_LTM_RBK_CTRL_COMMON *rbkCtrlCommon =
			ct_im_rbk_run1_get_gct_im_ltm_rbk_ctrl_common_base(priv->ctImRbkRun1);
	T_IM_LTM_RBK_CTRL_SDRAM_INPUT rbk_ctrl_sdram_in = gctImLtmRbkCtrlSdramInBase;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	rbkCtrlCommon->reduction_enable = D_IM_LTM_ENABLE_OFF;
	rbk_ctrl_sdram_in.shift_enable = D_IM_LTM_ENABLE_OFF;

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_RBK_Ctrl_Common( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), rbkCtrlCommon );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Ctrl_ModeSDRAMInput( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), &rbk_ctrl_sdram_in );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Set_InAddr_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			&S_GCT_IM_LTM_RBK_IN_ADDR_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Set_OutData_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), &gctImLtmRbkOutdataBase );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Start( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_RBK_Ctrl_Common( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), rbkCtrlCommon );
	Im_LTM_RBK_Ctrl_ModeSDRAMInput( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), &rbk_ctrl_sdram_in );
	Im_LTM_RBK_Set_InAddr_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), &S_GCT_IM_LTM_RBK_IN_ADDR_BASE );
	Im_LTM_RBK_Set_OutData_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), &gctImLtmRbkOutdataBase );
	Im_LTM_RBK_Start( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
#endif

	if( ct_im_ltm_rbk_check_target_pipe_no_1( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) ) ){
		flgptn |= D_IM_LTM_RBK1_INT_STATE_RBK_END;
	}
	if( ct_im_ltm_rbk_check_target_pipe_no_2( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) ) ){
		flgptn |= D_IM_LTM_RBK2_INT_STATE_RBK_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_RBK_WaitEnd( NULL, flgptn, 60 );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Stop( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_RBK_WaitEnd( NULL, flgptn, 60 );
	Im_LTM_RBK_Stop( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
#endif

	ct_im_ltm_rbk_print_all_reg();

	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run3_3_3: "
kint32 ct_im_rbk_run3_3_3(CtImRbkRun3* self)
{
	CtImRbkRun3Private *priv = CT_IM_RBK_RUN3_GET_PRIVATE(self);

	T_IM_LTM_RBK_CTRL_COMMON *rbkCtrlCommon =
			ct_im_rbk_run1_get_gct_im_ltm_rbk_ctrl_common_base(priv->ctImRbkRun1);
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	rbkCtrlCommon->reduction_enable = D_IM_LTM_ENABLE_OFF;

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_RBK_Ctrl_Common( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), rbkCtrlCommon );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Ctrl_ModeSDRAMInput( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			&gctImLtmRbkCtrlSdramInBase );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Set_InAddr_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			&S_GCT_IM_LTM_RBK_IN_ADDR_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Set_OutData_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), &gctImLtmRbkOutdataBase );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Start( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_RBK_Ctrl_Common( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), rbkCtrlCommon );
	Im_LTM_RBK_Ctrl_ModeSDRAMInput( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), &gctImLtmRbkCtrlSdramInBase );
	Im_LTM_RBK_Set_InAddr_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), &S_GCT_IM_LTM_RBK_IN_ADDR_BASE );
	Im_LTM_RBK_Set_OutData_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), &gctImLtmRbkOutdataBase );
	Im_LTM_RBK_Start( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
#endif

	if( ct_im_ltm_rbk_check_target_pipe_no_1( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) ) ){
		flgptn |= D_IM_LTM_RBK1_INT_STATE_RBK_END;
	}
	if( ct_im_ltm_rbk_check_target_pipe_no_2( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) ) ){
		flgptn |= D_IM_LTM_RBK2_INT_STATE_RBK_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_RBK_WaitEnd( NULL, flgptn, 60 );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Stop( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_RBK_WaitEnd( NULL, flgptn, 60 );
	Im_LTM_RBK_Stop( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
#endif

	ct_im_ltm_rbk_print_all_reg();

	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run3_3_4: "
kint32 ct_im_rbk_run3_3_4(CtImRbkRun3* self)
{
	CtImRbkRun3Private *priv = CT_IM_RBK_RUN3_GET_PRIVATE(self);

	T_IM_LTM_RBK_CTRL_COMMON *rbkCtrlCommon =
			ct_im_rbk_run1_get_gct_im_ltm_rbk_ctrl_common_base(priv->ctImRbkRun1);
	T_IM_LTM_RBK_OUTDATA_INFO rbkOutdata = gctImLtmRbkOutdataBase;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	rbkCtrlCommon->reduction_enable = D_IM_LTM_ENABLE_OFF;
	rbkOutdata.global_width = IM_LTM_RBK_ROUNDUP_N(( D_IM_LTM_RBK_DST_IMG_GLOBAL_WIDTH_UP / 2 ), 512 );

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_RBK_Ctrl_Common( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), rbkCtrlCommon );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Ctrl_ModeSDRAMInput( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			&gctImLtmRbkCtrlSdramInBase );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Set_InAddr_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			&S_GCT_IM_LTM_RBK_IN_ADDR_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Set_OutData_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), &rbkOutdata );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Ctrl_Resolution_Conversion( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			D_IM_LTM_ENABLE_ON );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Start( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_RBK_Ctrl_Common( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), rbkCtrlCommon );
	Im_LTM_RBK_Ctrl_ModeSDRAMInput( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			&gctImLtmRbkCtrlSdramInBase );
	Im_LTM_RBK_Set_InAddr_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			&S_GCT_IM_LTM_RBK_IN_ADDR_BASE );
	Im_LTM_RBK_Set_OutData_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), &rbkOutdata );
	Im_LTM_RBK_Ctrl_Resolution_Conversion( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), D_IM_LTM_ENABLE_ON );
	Im_LTM_RBK_Start( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
#endif

	if( ct_im_ltm_rbk_check_target_pipe_no_1( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) ) ){
		flgptn |= D_IM_LTM_RBK1_INT_STATE_RBK_END;
	}
	if( ct_im_ltm_rbk_check_target_pipe_no_2( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) ) ){
		flgptn |= D_IM_LTM_RBK2_INT_STATE_RBK_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_RBK_WaitEnd( NULL, flgptn, 60 );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Stop( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_RBK_WaitEnd( NULL, flgptn, 60 );
	Im_LTM_RBK_Stop( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
#endif

	ct_im_ltm_rbk_print_all_reg();

	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run3_3_5: "
kint32 ct_im_rbk_run3_3_5(CtImRbkRun3* self)
{
	CtImRbkRun3Private *priv = CT_IM_RBK_RUN3_GET_PRIVATE(self);

	T_IM_LTM_RBK_CTRL_COMMON *rbkCtrlCommon =
			ct_im_rbk_run1_get_gct_im_ltm_rbk_ctrl_common_base(priv->ctImRbkRun1);
	T_IM_LTM_RBK_OUTDATA_INFO rbkOutdata = gctImLtmRbkOutdataBase;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	rbkCtrlCommon->reduction_mode = D_IM_LTM_RBK_RDC_MODE_DIV_2,
	rbkOutdata.global_width = IM_LTM_RBK_ROUNDUP_N(( D_IM_LTM_RBK_DST_IMG_GLOBAL_WIDTH_UP / 2 ), 512 );

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_RBK_Ctrl_Common( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), rbkCtrlCommon );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Ctrl_ModeSDRAMInput( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			&gctImLtmRbkCtrlSdramInBase );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Set_InAddr_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			&S_GCT_IM_LTM_RBK_IN_ADDR_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Set_OutData_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), &rbkOutdata );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Start( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_RBK_Ctrl_Common( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), rbkCtrlCommon );
	Im_LTM_RBK_Ctrl_ModeSDRAMInput( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			&gctImLtmRbkCtrlSdramInBase );
	Im_LTM_RBK_Set_InAddr_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			&S_GCT_IM_LTM_RBK_IN_ADDR_BASE );
	Im_LTM_RBK_Set_OutData_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), &rbkOutdata );
	Im_LTM_RBK_Start( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
#endif

	if( ct_im_ltm_rbk_check_target_pipe_no_1( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) ) ){
		flgptn |= D_IM_LTM_RBK1_INT_STATE_RBK_END;
	}
	if( ct_im_ltm_rbk_check_target_pipe_no_2( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) ) ){
		flgptn |= D_IM_LTM_RBK2_INT_STATE_RBK_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_RBK_WaitEnd( NULL, flgptn, 60 );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Stop( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_RBK_WaitEnd( NULL, flgptn, 60 );
	Im_LTM_RBK_Stop( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
#endif

	ct_im_ltm_rbk_print_all_reg();

	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run3_3_6: "
kint32 ct_im_rbk_run3_3_6(CtImRbkRun3* self)
{
	CtImRbkRun3Private *priv = CT_IM_RBK_RUN3_GET_PRIVATE(self);

	T_IM_LTM_RBK_OUTDATA_INFO rbkOutdata = gctImLtmRbkOutdataBase;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	rbkOutdata.global_width = IM_LTM_RBK_ROUNDUP_N(( D_IM_LTM_RBK_DST_IMG_GLOBAL_WIDTH_UP / 4 ), 512 );

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_RBK_Ctrl_Common( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			ct_im_rbk_run1_get_gct_im_ltm_rbk_ctrl_common_base(priv->ctImRbkRun1) );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Ctrl_ModeSDRAMInput( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			&gctImLtmRbkCtrlSdramInBase );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Set_InAddr_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			&S_GCT_IM_LTM_RBK_IN_ADDR_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Set_OutData_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), &rbkOutdata );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Start( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_RBK_Ctrl_Common( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			ct_im_rbk_run1_get_gct_im_ltm_rbk_ctrl_common_base(priv->ctImRbkRun1) );
	Im_LTM_RBK_Ctrl_ModeSDRAMInput( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			&gctImLtmRbkCtrlSdramInBase );
	Im_LTM_RBK_Set_InAddr_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			&S_GCT_IM_LTM_RBK_IN_ADDR_BASE );
	Im_LTM_RBK_Set_OutData_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), &rbkOutdata );
	Im_LTM_RBK_Start( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
#endif

	if( ct_im_ltm_rbk_check_target_pipe_no_1( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) ) ){
		flgptn |= D_IM_LTM_RBK1_INT_STATE_RBK_END;
	}
	if( ct_im_ltm_rbk_check_target_pipe_no_2( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) ) ){
		flgptn |= D_IM_LTM_RBK2_INT_STATE_RBK_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_RBK_WaitEnd( NULL, flgptn, 60 );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Stop( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_RBK_WaitEnd( NULL, flgptn, 60 );
	Im_LTM_RBK_Stop( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
#endif

	ct_im_ltm_rbk_print_all_reg();

	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run3_3_7: "
kint32 ct_im_rbk_run3_3_7(CtImRbkRun3* self)
{
	CtImRbkRun3Private *priv = CT_IM_RBK_RUN3_GET_PRIVATE(self);

	T_IM_LTM_RBK_CTRL_COMMON *rbkCtrlCommon =
			ct_im_rbk_run1_get_gct_im_ltm_rbk_ctrl_common_base(priv->ctImRbkRun1);
	T_IM_LTM_RBK_OUTDATA_INFO rbkOutdata = gctImLtmRbkOutdataBase;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	rbkCtrlCommon->reduction_mode = D_IM_LTM_RBK_RDC_MODE_DIV_8,
	rbkOutdata.global_width = IM_LTM_RBK_ROUNDUP_N(( D_IM_LTM_RBK_DST_IMG_GLOBAL_WIDTH_UP / 8 ), 512 );

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_RBK_Ctrl_Common( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), rbkCtrlCommon );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Ctrl_ModeSDRAMInput( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			&gctImLtmRbkCtrlSdramInBase );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Set_InAddr_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			&S_GCT_IM_LTM_RBK_IN_ADDR_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Set_OutData_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), &rbkOutdata );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Start( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_RBK_Ctrl_Common( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), rbkCtrlCommon );
	Im_LTM_RBK_Ctrl_ModeSDRAMInput( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			&gctImLtmRbkCtrlSdramInBase );
	Im_LTM_RBK_Set_InAddr_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), &S_GCT_IM_LTM_RBK_IN_ADDR_BASE );
	Im_LTM_RBK_Set_OutData_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), &rbkOutdata );
	Im_LTM_RBK_Start( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
#endif

	if( ct_im_ltm_rbk_check_target_pipe_no_1( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) ) ){
		flgptn |= D_IM_LTM_RBK1_INT_STATE_RBK_END;
	}
	if( ct_im_ltm_rbk_check_target_pipe_no_2( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) ) ){
		flgptn |= D_IM_LTM_RBK2_INT_STATE_RBK_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_RBK_WaitEnd( NULL, flgptn, 60 );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Stop( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_RBK_WaitEnd( NULL, flgptn, 60 );
	Im_LTM_RBK_Stop( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
#endif

	ct_im_ltm_rbk_print_all_reg();

	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run3_3_8: "
kint32 ct_im_rbk_run3_3_8(CtImRbkRun3* self)
{
	CtImRbkRun3Private *priv = CT_IM_RBK_RUN3_GET_PRIVATE(self);

	T_IM_LTM_RBK_CTRL_COMMON *rbkCtrlCommon =
			ct_im_rbk_run1_get_gct_im_ltm_rbk_ctrl_common_base(priv->ctImRbkRun1);
	T_IM_LTM_RBK_OUTDATA_INFO rbkOutdata = gctImLtmRbkOutdataBase;
	T_IM_LTM_RBK_RGB_TRIMMING rbkCtrlRgbTrim;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	rbkCtrlCommon->reduction_enable = D_IM_LTM_ENABLE_OFF;
	rbkOutdata.global_width = IM_LTM_RBK_ROUNDUP_N(( D_IM_LTM_RBK_DST_IMG_GLOBAL_WIDTH_UP / 2 ), 512 );
	rbkCtrlRgbTrim.trimming_enable    = D_IM_LTM_ENABLE_ON;
	rbkCtrlRgbTrim.rgb_trim.img_top   = 120;
	rbkCtrlRgbTrim.rgb_trim.img_left  = 160;
	rbkCtrlRgbTrim.rgb_trim.img_width = 320;
	rbkCtrlRgbTrim.rgb_trim.img_lines = 240;

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_RBK_Ctrl_Common( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), rbkCtrlCommon );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Ctrl_ModeSDRAMInput( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			&gctImLtmRbkCtrlSdramInBase );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Set_InAddr_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			&S_GCT_IM_LTM_RBK_IN_ADDR_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Set_OutData_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), &rbkOutdata );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Ctrl_RGBTrimming( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), &rbkCtrlRgbTrim );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Start( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_RBK_Ctrl_Common( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), rbkCtrlCommon );
	Im_LTM_RBK_Ctrl_ModeSDRAMInput( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			&gctImLtmRbkCtrlSdramInBase );
	Im_LTM_RBK_Set_InAddr_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			&S_GCT_IM_LTM_RBK_IN_ADDR_BASE );
	Im_LTM_RBK_Set_OutData_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), &rbkOutdata );
	Im_LTM_RBK_Ctrl_RGBTrimming( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), &rbkCtrlRgbTrim );
	Im_LTM_RBK_Start( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
#endif

	if( ct_im_ltm_rbk_check_target_pipe_no_1( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) ) ){
		flgptn |= D_IM_LTM_RBK1_INT_STATE_RBK_END;
	}
	if( ct_im_ltm_rbk_check_target_pipe_no_2( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) ) ){
		flgptn |= D_IM_LTM_RBK2_INT_STATE_RBK_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_RBK_WaitEnd( NULL, flgptn, 60 );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Stop( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_RBK_WaitEnd( NULL, flgptn, 60 );
	Im_LTM_RBK_Stop( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
#endif

	ct_im_ltm_rbk_print_all_reg();

	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run3_3_9: "
kint32 ct_im_rbk_run3_3_9(CtImRbkRun3* self)
{
	CtImRbkRun3Private *priv = CT_IM_RBK_RUN3_GET_PRIVATE(self);

	T_IM_LTM_RBK_CTRL_COMMON *rbkCtrlCommon =
			ct_im_rbk_run1_get_gct_im_ltm_rbk_ctrl_common_base(priv->ctImRbkRun1);
	T_IM_LTM_RBK_CTRL_SRO_DIRECT *rbkCtrlSroDirect =
			ct_im_rbk_run2_get_gct_im_ltm_rbk_ctrl_sro_direct_base(priv->ctImRbkRun2);
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	rbkCtrlCommon->reduction_enable = D_IM_LTM_ENABLE_OFF;
	rbkCtrlSroDirect->shift_enable0 = D_IM_LTM_ENABLE_OFF;

	// SRO setting
	ct_im_ltm_rbk_set_sro( (E_IM_PRO_UNIT_NUM)ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), 0 );

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_RBK_Ctrl_Common( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), rbkCtrlCommon );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Ctrl_ModeSRODirect( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), rbkCtrlSroDirect );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Set_OutData_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			&gctImLtmRbkOutdataBase );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Set_FrameStop( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), D_IM_LTM_ENABLE_ON );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Start( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_RBK_Ctrl_Common( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), rbkCtrlCommon );
	Im_LTM_RBK_Ctrl_ModeSRODirect( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), rbkCtrlSroDirect );
	Im_LTM_RBK_Set_OutData_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), &gctImLtmRbkOutdataBase );
	Im_LTM_RBK_Set_FrameStop( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), D_IM_LTM_ENABLE_ON );
	Im_LTM_RBK_Start( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
#endif

	// SRO start
	ct_im_ltm_rbk_start_sro( (E_IM_PRO_UNIT_NUM)ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
	ct_im_ltm_rbk_waitend_stop_sro( (E_IM_PRO_UNIT_NUM)ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );

	if( ct_im_ltm_rbk_check_target_pipe_no_1( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) ) ){
		flgptn |= D_IM_LTM_RBK1_INT_STATE_RBK_END;
	}
	if( ct_im_ltm_rbk_check_target_pipe_no_2( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) ) ){
		flgptn |= D_IM_LTM_RBK2_INT_STATE_RBK_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_RBK_WaitEnd( NULL, flgptn, 60 );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Stop( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_RBK_WaitEnd( NULL, flgptn, 60 );
	Im_LTM_RBK_Stop( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
#endif

	ct_im_ltm_rbk_print_all_reg();

	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run3_3_10: "
kint32 ct_im_rbk_run3_3_10(CtImRbkRun3* self)
{
	CtImRbkRun3Private *priv = CT_IM_RBK_RUN3_GET_PRIVATE(self);

	T_IM_LTM_RBK_CTRL_COMMON *rbkCtrlCommon =
			ct_im_rbk_run1_get_gct_im_ltm_rbk_ctrl_common_base(priv->ctImRbkRun1);
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	rbkCtrlCommon->reduction_enable = D_IM_LTM_ENABLE_OFF;

	// SRO setting
	ct_im_ltm_rbk_set_sro( (E_IM_PRO_UNIT_NUM)ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), 0 );

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_RBK_Ctrl_Common( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), rbkCtrlCommon );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Ctrl_ModeSRODirect( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			ct_im_rbk_run2_get_gct_im_ltm_rbk_ctrl_sro_direct_base(priv->ctImRbkRun2) );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Set_OutData_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			&gctImLtmRbkOutdataBase );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Set_FrameStop( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), D_IM_LTM_ENABLE_ON );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Start( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_RBK_Ctrl_Common( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), rbkCtrlCommon );
	Im_LTM_RBK_Ctrl_ModeSRODirect( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			ct_im_rbk_run2_get_gct_im_ltm_rbk_ctrl_sro_direct_base(priv->ctImRbkRun2) );
	Im_LTM_RBK_Set_OutData_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), &gctImLtmRbkOutdataBase );
	Im_LTM_RBK_Set_FrameStop( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), D_IM_LTM_ENABLE_ON );
	Im_LTM_RBK_Start( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
#endif

	// SRO start
	ct_im_ltm_rbk_start_sro( (E_IM_PRO_UNIT_NUM)ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
	ct_im_ltm_rbk_waitend_stop_sro( (E_IM_PRO_UNIT_NUM)ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );

	if( ct_im_ltm_rbk_check_target_pipe_no_1( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) ) ){
		flgptn |= D_IM_LTM_RBK1_INT_STATE_RBK_END;
	}
	if( ct_im_ltm_rbk_check_target_pipe_no_2( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) ) ){
		flgptn |= D_IM_LTM_RBK2_INT_STATE_RBK_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_RBK_WaitEnd( NULL, flgptn, 60 );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Stop( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_RBK_WaitEnd( NULL, flgptn, 60 );
	Im_LTM_RBK_Stop( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
#endif

	ct_im_ltm_rbk_print_all_reg();

	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run3_3_18: "
kint32 ct_im_rbk_run3_3_18(CtImRbkRun3* self)
{
	CtImRbkRun3Private *priv = CT_IM_RBK_RUN3_GET_PRIVATE(self);

	T_IM_LTM_RBK_CTRL_COMMON *rbkCtrlCommon =
			ct_im_rbk_run1_get_gct_im_ltm_rbk_ctrl_common_base(priv->ctImRbkRun1);
	T_IM_LTM_RBK_OUTDATA_INFO rbkOutdata = gctImLtmRbkOutdataBase;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	rbkCtrlCommon->reduction_enable = D_IM_LTM_ENABLE_OFF;
	rbkCtrlCommon->data_type = D_IM_LTM_DTYP_PACK12,
	rbkOutdata.global_width = IM_LTM_RBK_ROUNDUP_N( D_IM_LTM_RBK_DST_IMG_GLOBAL_WIDTH_P, 512 );

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_RBK_Ctrl_Common( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), rbkCtrlCommon );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Ctrl_ModeSDRAMInput( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			&gctImLtmRbkCtrlSdramInBase );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Set_InAddr_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			&S_GCT_IM_LTM_RBK_IN_ADDR_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Set_OutData_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), &rbkOutdata );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Start( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_RBK_Ctrl_Common( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), rbkCtrlCommon );
	Im_LTM_RBK_Ctrl_ModeSDRAMInput( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			&gctImLtmRbkCtrlSdramInBase );
	Im_LTM_RBK_Set_InAddr_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			&S_GCT_IM_LTM_RBK_IN_ADDR_BASE );
	Im_LTM_RBK_Set_OutData_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), &rbkOutdata );
	Im_LTM_RBK_Start( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
#endif

	if( ct_im_ltm_rbk_check_target_pipe_no_1( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) ) ){
		flgptn |= D_IM_LTM_RBK1_INT_STATE_RBK_END;
	}
	if( ct_im_ltm_rbk_check_target_pipe_no_2( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) ) ){
		flgptn |= D_IM_LTM_RBK2_INT_STATE_RBK_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_RBK_WaitEnd( NULL, flgptn, 60 );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Stop( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_RBK_WaitEnd( NULL, flgptn, 60 );
	Im_LTM_RBK_Stop( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
#endif

	ct_im_ltm_rbk_print_all_reg();

	return D_DDIM_OK;
}

T_IM_LTM_RBK_CTRL_SDRAM_INPUT *ct_im_rbk_run3_get_gct_im_ltm_rbk_ctrl_sdram_in_base(CtImRbkRun3* self)
{
	CtImRbkRun3Private *priv = CT_IM_RBK_RUN3_GET_PRIVATE(self);
	return priv->gctImLtmRbkCtrlSdramInBase;
}

T_IM_LTM_RBK_OUTDATA_INFO *ct_im_rbk_run3_get_gct_im_ltm_rbk_outdata_base(CtImRbkRun3* self)
{
	CtImRbkRun3Private *priv = CT_IM_RBK_RUN3_GET_PRIVATE(self);
	return priv->gctImLtmRbkOutdataBase;
}

void ct_im_rbk_run3_set_var1(CtImRbkRun3* self, CtImRbkRun1* var1)
{
	CtImRbkRun3Private *priv = CT_IM_RBK_RUN3_GET_PRIVATE(self);
	priv->ctImRbkRun1=var1;
}

CtImRbkRun3* ct_im_rbk_run3_new(void) 
{
    CtImRbkRun3 *self = k_object_new_with_private(CT_TYPE_IM_RBK_RUN3, sizeof(CtImRbkRun3Private));
    return self;
}
