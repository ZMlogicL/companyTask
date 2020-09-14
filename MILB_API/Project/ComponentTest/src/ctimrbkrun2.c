/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-10
*@author              :jianghaodong
*@brief               :CtImRbkRun2类
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
#include "ctimrbkrun3.h"
#include "ctimrbkrun2.h"


G_DEFINE_TYPE(CtImRbkRun2, ct_im_rbk_run2, G_TYPE_OBJECT);
#define CT_IM_RBK_RUN2_GET_PRIVATE(o)(G_TYPE_INSTANCE_GET_PRIVATE ((o),CT_TYPE_IM_RBK_RUN2, CtImRbkRun2Private))

struct _CtImRbkRun2Private
{
	CtImRbkRun1* ctImRbkRun1;
	CtImRbkRun3* ctImRbkRun3;
	T_IM_LTM_RBK_CTRL_SRO_DIRECT *gctImLtmRbkCtrlSroDirectBase;
};

T_IM_LTM_RBK_CTRL_SRO_DIRECT gctImLtmRbkCtrlSroDirectBase = {
	.top_pixel0 = D_IM_LTM_RBK_TOP_PIXEL_R,
	.top_pixel1 = D_IM_LTM_RBK_TOP_PIXEL_R,
	.sro_mode = D_IM_LTM_RBK_SRO_DIRECT_1,
	.shift_enable0 = D_IM_LTM_ENABLE_ON,
	.shift_enable1 = D_IM_LTM_ENABLE_OFF,
	.half_reduction_enable = D_IM_LTM_ENABLE_OFF,
	.bayer_trim0 = {
		.img_top = 0,
		.img_left = 0,
		.img_width = D_IM_LTM_RBK_SRC_IMG_PIXS_WIDTH,
		.img_lines = D_IM_LTM_RBK_SRC_IMG_PIXS_LINES,
	},
	.bayer_trim1 = {
		.img_top = 0,
		.img_left = 0,
		.img_width = 0,
		.img_lines = 0,
	},
};
/*
*DECLS
*/
static void 	dispose_od(GObject *object);
static void 	finalize_od(GObject *object);
/*
*IMPL
*/

static void ct_im_rbk_run2_class_init(CtImRbkRun2Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtImRbkRun2Private));
}

static void ct_im_rbk_run2_init(CtImRbkRun2 *self)
{
	CtImRbkRun2Private *priv = CT_IM_RBK_RUN2_GET_PRIVATE(self);
	priv->ctImRbkRun1=ct_im_rbk_run1_new();
	priv->ctImRbkRun3=ct_im_rbk_run3_new();
	priv->gctImLtmRbkCtrlSroDirectBase=&gctImLtmRbkCtrlSroDirectBase;
}

static void dispose_od(GObject *object)
{
	CtImRbkRun2 *self = (CtImRbkRun2*)object;
	CtImRbkRun2Private *priv = CT_IM_RBK_RUN2_GET_PRIVATE(self);

	if(priv->ctImRbkRun1)
		{
			g_object_unref(priv->ctImRbkRun1);
			priv->ctImRbkRun1 = NULL;
		}
	if(priv->ctImRbkRun3)
		{
			g_object_unref(priv->ctImRbkRun3);
			priv->ctImRbkRun3 = NULL;
		}
	G_OBJECT_CLASS(ct_im_rbk_run2_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	CtImRbkRun2 *self = (CtImRbkRun2*)object;
	CtImRbkRun2Private *priv = CT_IM_RBK_RUN2_GET_PRIVATE(self);
	G_OBJECT_CLASS(ct_im_rbk_run2_parent_class)->finalize(object);
}


/*
*PUBLIC
*/
#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run2_rbk_2_1: "
gint32 ct_im_rbk_run2_rbk_2_1(CtImRbkRun2* self)
{
	CtImRbkRun2Private *priv = CT_IM_RBK_RUN2_GET_PRIVATE(self);
	gint32 ercd = DriverCommon_D_DDIM_OK;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	ercd = Im_LTM_RBK_Ctrl_Axi( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), NULL );
	if( ercd != DriverCommon_D_DDIM_OK ){
		Ddim_Print(( D_IM_LTM_FUNC_NAME "RBK ctrl axi error = 0x%x\n", ercd ));
	}

	return ercd;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run2_rbk_2_2: "
gint32 ct_im_rbk_run2_rbk_2_2(CtImRbkRun2* self)
{
	CtImRbkRun2Private *priv = CT_IM_RBK_RUN2_GET_PRIVATE(self);
	gint32 ercd = DriverCommon_D_DDIM_OK;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	ercd = Im_LTM_RBK_Get_AxiReadStat( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), NULL );
	if( ercd != DriverCommon_D_DDIM_OK ){
		Ddim_Print(( D_IM_LTM_FUNC_NAME "RBK get axi read stat error = 0x%x\n", ercd ));
	}

	return ercd;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run2_rbk_2_3: "
gint32 ct_im_rbk_run2_rbk_2_3(CtImRbkRun2* self)
{
	CtImRbkRun2Private *priv = CT_IM_RBK_RUN2_GET_PRIVATE(self);
	gint32 ercd = DriverCommon_D_DDIM_OK;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	ercd = Im_LTM_RBK_Get_AxiWriteStat( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), NULL );
	if( ercd != DriverCommon_D_DDIM_OK ){
		Ddim_Print(( D_IM_LTM_FUNC_NAME "RBK get axi write stat error = 0x%x\n", ercd ));
	}

	return ercd;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run2_rbk_2_4: "
gint32 ct_im_rbk_run2_rbk_2_4(CtImRbkRun2* self)
{
	CtImRbkRun2Private *priv = CT_IM_RBK_RUN2_GET_PRIVATE(self);
	gint32 ercd = DriverCommon_D_DDIM_OK;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	ercd = Im_LTM_RBK_Get_AxiCtrlParam( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), NULL );
	if( ercd != DriverCommon_D_DDIM_OK ){
		Ddim_Print(( D_IM_LTM_FUNC_NAME "RBK get axi ctrl param error = 0x%x\n", ercd ));
	}

	return ercd;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run2_rbk_2_5: "
gint32 ct_im_rbk_run2_rbk_2_5(CtImRbkRun2* self)
{
	CtImRbkRun2Private *priv = CT_IM_RBK_RUN2_GET_PRIVATE(self);
	gint32 ercd = DriverCommon_D_DDIM_OK;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	ercd = Im_LTM_RBK_Set_AxiCtrlParam( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), NULL );
	if( ercd != DriverCommon_D_DDIM_OK ){
		Ddim_Print(( D_IM_LTM_FUNC_NAME "RBK set axi ctrl param error = 0x%x\n", ercd ));
	}

	return ercd;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run2_rbk_2_6: "
gint32 ct_im_rbk_run2_rbk_2_6(CtImRbkRun2* self)
{
	CtImRbkRun2Private *priv = CT_IM_RBK_RUN2_GET_PRIVATE(self);
	gint32 ercd = DriverCommon_D_DDIM_OK;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	ercd = Im_LTM_RBK_Ctrl_Common( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), NULL );
	if( ercd != DriverCommon_D_DDIM_OK ){
		Ddim_Print(( D_IM_LTM_FUNC_NAME "RBK set ctrl common error = 0x%x\n", ercd ));
	}

	return ercd;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run2_rbk_2_7: "
gint32 ct_im_rbk_run2_rbk_2_7(CtImRbkRun2* self)
{
	CtImRbkRun2Private *priv = CT_IM_RBK_RUN2_GET_PRIVATE(self);
	gint32 ercd = DriverCommon_D_DDIM_OK;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	ercd = Im_LTM_RBK_Ctrl_ModeSDRAMInput( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), NULL );
	if( ercd != DriverCommon_D_DDIM_OK ){
		Ddim_Print(( D_IM_LTM_FUNC_NAME "RBK set ctrl sdram input error = 0x%x\n", ercd ));
	}

	return ercd;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run2_rbk_2_8: "
gint32 ct_im_rbk_run2_rbk_2_8(CtImRbkRun2* self)
{
	CtImRbkRun2Private *priv = CT_IM_RBK_RUN2_GET_PRIVATE(self);
	gint32 ercd = DriverCommon_D_DDIM_OK;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	ercd = Im_LTM_RBK_Set_InAddr_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), NULL );
	if( ercd != DriverCommon_D_DDIM_OK ){
		Ddim_Print(( D_IM_LTM_FUNC_NAME "RBK set inaddr error = 0x%x\n", ercd ));
	}

	return ercd;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run2_rbk_2_9: "
gint32 ct_im_rbk_run2_rbk_2_9(CtImRbkRun2* self)
{
	CtImRbkRun2Private *priv = CT_IM_RBK_RUN2_GET_PRIVATE(self);
	gint32 ercd = DriverCommon_D_DDIM_OK;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	ercd = Im_LTM_RBK_Set_OutData_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), NULL );
	if( ercd != DriverCommon_D_DDIM_OK ){
		Ddim_Print(( D_IM_LTM_FUNC_NAME "RBK set outdata error = 0x%x\n", ercd ));
	}

	return ercd;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run2_rbk_2_10: "
gint32 ct_im_rbk_run2_rbk_2_10(CtImRbkRun2* self)
{
	CtImRbkRun2Private *priv = CT_IM_RBK_RUN2_GET_PRIVATE(self);
	gint32 ercd = DriverCommon_D_DDIM_OK;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	ercd = Im_LTM_RBK_Ctrl_ModeSRODirect( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), NULL );
	if( ercd != DriverCommon_D_DDIM_OK ){
		Ddim_Print(( D_IM_LTM_FUNC_NAME "RBK ctrl sro direct error = 0x%x\n", ercd ));
	}

	return ercd;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run2_rbk_2_11: "
gint32 ct_im_rbk_run2_rbk_2_11(CtImRbkRun2* self)
{
	CtImRbkRun2Private *priv = CT_IM_RBK_RUN2_GET_PRIVATE(self);
	gint32 ercd = DriverCommon_D_DDIM_OK;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	ercd = Im_LTM_RBK_Get_RbkBusy( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), NULL );
	if( ercd != DriverCommon_D_DDIM_OK ){
		Ddim_Print(( D_IM_LTM_FUNC_NAME "RBK get rbk busy error = 0x%x\n", ercd ));
	}

	return ercd;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run2_rbk_2_12: "
gint32 ct_im_rbk_run2_rbk_2_12(CtImRbkRun2* self)
{
	CtImRbkRun2Private *priv = CT_IM_RBK_RUN2_GET_PRIVATE(self);
	gint32 ercd = DriverCommon_D_DDIM_OK;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	ercd = Im_LTM_RBK_Ctrl_RGBTrimming( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), NULL );
	if( ercd != DriverCommon_D_DDIM_OK ){
		Ddim_Print(( D_IM_LTM_FUNC_NAME "RBK ctrl rgb trimming error = 0x%x\n", ercd ));
	}

	return ercd;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run2_rbk_2_13: "
gint32 ct_im_rbk_run2_rbk_2_13(CtImRbkRun2* self)
{
	gint32 ercd = DriverCommon_D_DDIM_OK;
	DDIM_USER_FLGPTN flgptn;
	DDIM_USER_FLGPTN waiptn;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	waiptn = 0x11110000;
	ercd = Im_LTM_RBK_WaitEnd( &flgptn, waiptn, 100 );
	if( ercd != DriverCommon_D_DDIM_OK ){
		Ddim_Print(( D_IM_LTM_FUNC_NAME "RBK wait end error = 0x%x\n", ercd ));
	}

	return ercd;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run2_rbk_3_11: "
gint32 ct_im_rbk_run2_rbk_3_11(CtImRbkRun2* self)
{
	CtImRbkRun2Private *priv = CT_IM_RBK_RUN2_GET_PRIVATE(self);

	T_IM_LTM_RBK_CTRL_COMMON *rbkCtrlCommon =
			ct_im_rbk_run1_get_gct_im_ltm_rbk_ctrl_common_base(priv->ctImRbkRun1);
	T_IM_LTM_RBK_CTRL_SRO_DIRECT rbk_ctrl_sro_direct = gctImLtmRbkCtrlSroDirectBase;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	gint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	// SRO setting
	ct_im_ltm_rbk_set_sro( (E_IM_PRO_UNIT_NUM)ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), 0 );

	rbkCtrlCommon->reduction_enable = D_IM_LTM_ENABLE_OFF;
	rbk_ctrl_sro_direct.top_pixel0 = D_IM_LTM_RBK_TOP_PIXEL_B;
	rbk_ctrl_sro_direct.bayer_trim0.img_top   = 241;
	rbk_ctrl_sro_direct.bayer_trim0.img_left  = 321;
	rbk_ctrl_sro_direct.bayer_trim0.img_width = 640;
	rbk_ctrl_sro_direct.bayer_trim0.img_lines = 480;

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_RBK_Ctrl_Common( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), rbkCtrlCommon );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Ctrl_ModeSRODirect( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), &rbk_ctrl_sro_direct );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Set_OutData_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			ct_im_rbk_run3_get_gct_im_ltm_rbk_outdata_base(priv->ctImRbkRun3) );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Set_FrameStop( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), D_IM_LTM_ENABLE_ON );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Start( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_RBK_Ctrl_Common( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), rbkCtrlCommon );
	Im_LTM_RBK_Ctrl_ModeSRODirect( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), &rbk_ctrl_sro_direct );
	Im_LTM_RBK_Set_OutData_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			ct_im_rbk_run3_get_gct_im_ltm_rbk_outdata_base(priv->ctImRbkRun3) );
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

	return DriverCommon_D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run2_rbk_3_12: "
gint32 ct_im_rbk_run2_rbk_3_12(CtImRbkRun2* self)
{
	CtImRbkRun2Private *priv = CT_IM_RBK_RUN2_GET_PRIVATE(self);

	T_IM_LTM_RBK_CTRL_COMMON *rbkCtrlCommon =
			ct_im_rbk_run1_get_gct_im_ltm_rbk_ctrl_common_base(priv->ctImRbkRun1);
	T_IM_LTM_RBK_CTRL_SRO_DIRECT rbk_ctrl_sro_direct = gctImLtmRbkCtrlSroDirectBase;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	gint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	rbkCtrlCommon->reduction_enable = D_IM_LTM_ENABLE_OFF;
	rbk_ctrl_sro_direct.half_reduction_enable = D_IM_LTM_ENABLE_ON;

	// SRO setting
	ct_im_ltm_rbk_set_sro( (E_IM_PRO_UNIT_NUM)ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), 0 );

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_RBK_Ctrl_Common( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), rbkCtrlCommon );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Ctrl_ModeSRODirect( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), &rbk_ctrl_sro_direct );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Set_OutData_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			ct_im_rbk_run3_get_gct_im_ltm_rbk_outdata_base(priv->ctImRbkRun3) );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Set_FrameStop( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), D_IM_LTM_ENABLE_ON );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Start( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_RBK_Ctrl_Common( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), rbkCtrlCommon );
	Im_LTM_RBK_Ctrl_ModeSRODirect( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), &rbk_ctrl_sro_direct );
	Im_LTM_RBK_Set_OutData_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			ct_im_rbk_run3_get_gct_im_ltm_rbk_outdata_base(priv->ctImRbkRun3) );
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

	return DriverCommon_D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run2_rbk_3_13: "
gint32 ct_im_rbk_run2_rbk_3_13(CtImRbkRun2* self)
{
	CtImRbkRun2Private *priv = CT_IM_RBK_RUN2_GET_PRIVATE(self);

	T_IM_LTM_RBK_CTRL_COMMON *rbkCtrlCommon =
			ct_im_rbk_run1_get_gct_im_ltm_rbk_ctrl_common_base(priv->ctImRbkRun1);
	T_IM_LTM_RBK_CTRL_SRO_DIRECT rbk_ctrl_sro_direct = gctImLtmRbkCtrlSroDirectBase;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	gint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	rbkCtrlCommon->reduction_enable = D_IM_LTM_ENABLE_OFF;
	rbk_ctrl_sro_direct.half_reduction_enable = D_IM_LTM_ENABLE_ON;
	rbk_ctrl_sro_direct.sro_mode = D_IM_LTM_RBK_SRO_DIRECT_2,
	rbk_ctrl_sro_direct.shift_enable0 = D_IM_LTM_ENABLE_OFF;
	rbk_ctrl_sro_direct.bayer_trim0.img_width = D_IM_LTM_RBK_SRC_IMG_PIXS_WIDTH / 2;
	rbk_ctrl_sro_direct.bayer_trim1.img_width = D_IM_LTM_RBK_SRC_IMG_PIXS_WIDTH / 2;
	rbk_ctrl_sro_direct.bayer_trim1.img_lines = D_IM_LTM_RBK_SRC_IMG_PIXS_LINES;

	// SRO setting(2pipe)
	ct_im_ltm_rbk_set_sro( E_IM_PRO_BOTH_UNIT, 0 );

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_RBK_Ctrl_Common( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), rbkCtrlCommon );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Ctrl_ModeSRODirect( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			&rbk_ctrl_sro_direct );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Set_OutData_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			ct_im_rbk_run3_get_gct_im_ltm_rbk_outdata_base(priv->ctImRbkRun3) );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Set_FrameStop( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), D_IM_LTM_ENABLE_ON );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Start( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_RBK_Ctrl_Common( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), rbkCtrlCommon );
	Im_LTM_RBK_Ctrl_ModeSRODirect( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), &rbk_ctrl_sro_direct );
	Im_LTM_RBK_Set_OutData_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			ct_im_rbk_run3_get_gct_im_ltm_rbk_outdata_base(priv->ctImRbkRun3) );
	Im_LTM_RBK_Set_FrameStop( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), D_IM_LTM_ENABLE_ON );
	Im_LTM_RBK_Start( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
#endif

	// SRO start(2pipe)
	ct_im_ltm_rbk_start_sro( E_IM_PRO_BOTH_UNIT );
	ct_im_ltm_rbk_waitend_stop_sro( E_IM_PRO_BOTH_UNIT );

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

	return DriverCommon_D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run2_rbk_3_14: "
gint32 ct_im_rbk_run2_rbk_3_14(CtImRbkRun2* self)
{
	CtImRbkRun2Private *priv = CT_IM_RBK_RUN2_GET_PRIVATE(self);

	T_IM_LTM_RBK_CTRL_COMMON *rbkCtrlCommon =
			ct_im_rbk_run1_get_gct_im_ltm_rbk_ctrl_common_base(priv->ctImRbkRun1);
	T_IM_LTM_RBK_CTRL_SRO_DIRECT rbk_ctrl_sro_direct = gctImLtmRbkCtrlSroDirectBase;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	gint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	rbkCtrlCommon->reduction_enable = D_IM_LTM_ENABLE_OFF;
	rbk_ctrl_sro_direct.half_reduction_enable = D_IM_LTM_ENABLE_ON;
	rbk_ctrl_sro_direct.sro_mode = D_IM_LTM_RBK_SRO_DIRECT_2,
	rbk_ctrl_sro_direct.shift_enable1 = D_IM_LTM_ENABLE_ON;
	rbk_ctrl_sro_direct.bayer_trim0.img_width = D_IM_LTM_RBK_SRC_IMG_PIXS_WIDTH / 2;
	rbk_ctrl_sro_direct.bayer_trim1.img_width = D_IM_LTM_RBK_SRC_IMG_PIXS_WIDTH / 2;
	rbk_ctrl_sro_direct.bayer_trim1.img_lines = D_IM_LTM_RBK_SRC_IMG_PIXS_LINES;

	// SRO setting(2pipe)
	ct_im_ltm_rbk_set_sro( E_IM_PRO_BOTH_UNIT, 0 );

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_RBK_Ctrl_Common( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), rbkCtrlCommon );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Ctrl_ModeSRODirect( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			&rbk_ctrl_sro_direct );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Set_OutData_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			ct_im_rbk_run3_get_gct_im_ltm_rbk_outdata_base(priv->ctImRbkRun3) );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Set_FrameStop( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), D_IM_LTM_ENABLE_ON );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Start( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_RBK_Ctrl_Common( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), rbkCtrlCommon );
	Im_LTM_RBK_Ctrl_ModeSRODirect( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), &rbk_ctrl_sro_direct );
	Im_LTM_RBK_Set_OutData_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			ct_im_rbk_run3_get_gct_im_ltm_rbk_outdata_base(priv->ctImRbkRun3) );
	Im_LTM_RBK_Set_FrameStop( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), D_IM_LTM_ENABLE_ON );
	Im_LTM_RBK_Start( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
#endif

	// SRO start(2pipe)
	ct_im_ltm_rbk_start_sro( E_IM_PRO_BOTH_UNIT );
	ct_im_ltm_rbk_waitend_stop_sro( E_IM_PRO_BOTH_UNIT );

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

	return DriverCommon_D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run2_rbk_3_15: "
gint32 ct_im_rbk_run2_rbk_3_15(CtImRbkRun2* self)
{
	CtImRbkRun2Private *priv = CT_IM_RBK_RUN2_GET_PRIVATE(self);

	T_IM_LTM_RBK_CTRL_COMMON *rbkCtrlCommon =
			ct_im_rbk_run1_get_gct_im_ltm_rbk_ctrl_common_base(priv->ctImRbkRun1);
	T_IM_LTM_RBK_CTRL_SRO_DIRECT rbk_ctrl_sro_direct = gctImLtmRbkCtrlSroDirectBase;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	gint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	rbkCtrlCommon->reduction_enable = D_IM_LTM_ENABLE_OFF;
	rbk_ctrl_sro_direct.half_reduction_enable = D_IM_LTM_ENABLE_ON;
	rbk_ctrl_sro_direct.sro_mode = D_IM_LTM_RBK_SRO_DIRECT_2,
	rbk_ctrl_sro_direct.shift_enable1 = D_IM_LTM_ENABLE_ON;
	rbk_ctrl_sro_direct.bayer_trim0.img_top   =
			( D_IM_LTM_RBK_SRC_IMG_PIXS_LINES - ( D_IM_LTM_RBK_SRC_IMG_PIXS_LINES / 2 )) / 2;
	rbk_ctrl_sro_direct.bayer_trim0.img_left  =
			( D_IM_LTM_RBK_SRC_IMG_PIXS_WIDTH - ( D_IM_LTM_RBK_SRC_IMG_PIXS_WIDTH / 2 )) / 2;
	rbk_ctrl_sro_direct.bayer_trim0.img_width =
			( D_IM_LTM_RBK_SRC_IMG_PIXS_WIDTH - ( D_IM_LTM_RBK_SRC_IMG_PIXS_WIDTH / 2 )) / 2;
	rbk_ctrl_sro_direct.bayer_trim0.img_lines =
			( D_IM_LTM_RBK_SRC_IMG_PIXS_LINES - ( D_IM_LTM_RBK_SRC_IMG_PIXS_LINES / 2 ));
	rbk_ctrl_sro_direct.bayer_trim1.img_top   =
			( D_IM_LTM_RBK_SRC_IMG_PIXS_LINES - ( D_IM_LTM_RBK_SRC_IMG_PIXS_LINES / 2 )) / 2;
	rbk_ctrl_sro_direct.bayer_trim1.img_left  = 0;
	rbk_ctrl_sro_direct.bayer_trim1.img_width =
			( D_IM_LTM_RBK_SRC_IMG_PIXS_WIDTH - ( D_IM_LTM_RBK_SRC_IMG_PIXS_WIDTH / 2 )) / 2;
	rbk_ctrl_sro_direct.bayer_trim1.img_lines =
			( D_IM_LTM_RBK_SRC_IMG_PIXS_LINES - ( D_IM_LTM_RBK_SRC_IMG_PIXS_LINES / 2 ));

	// SRO setting(2pipe)
	ct_im_ltm_rbk_set_sro( E_IM_PRO_BOTH_UNIT, 0 );

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_RBK_Ctrl_Common( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), rbkCtrlCommon );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Ctrl_ModeSRODirect( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), &rbk_ctrl_sro_direct );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Set_OutData_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			ct_im_rbk_run3_get_gct_im_ltm_rbk_outdata_base(priv->ctImRbkRun3) );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Set_FrameStop( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), D_IM_LTM_ENABLE_ON );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Start( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_RBK_Ctrl_Common( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), rbkCtrlCommon );
	Im_LTM_RBK_Ctrl_ModeSRODirect( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), &rbk_ctrl_sro_direct );
	Im_LTM_RBK_Set_OutData_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			ct_im_rbk_run3_get_gct_im_ltm_rbk_outdata_base(priv->ctImRbkRun3) );
	Im_LTM_RBK_Set_FrameStop( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), D_IM_LTM_ENABLE_ON );
	Im_LTM_RBK_Start( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
#endif

	// SRO start(2pipe)
	ct_im_ltm_rbk_start_sro( E_IM_PRO_BOTH_UNIT );
	ct_im_ltm_rbk_waitend_stop_sro( E_IM_PRO_BOTH_UNIT );

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

	return DriverCommon_D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run2_rbk_3_16: "
gint32 ct_im_rbk_run2_rbk_3_16(CtImRbkRun2* self)
{
	CtImRbkRun2Private *priv = CT_IM_RBK_RUN2_GET_PRIVATE(self);

	T_IM_LTM_RBK_CTRL_COMMON *rbkCtrlCommon =
			ct_im_rbk_run1_get_gct_im_ltm_rbk_ctrl_common_base(priv->ctImRbkRun1);
	T_IM_LTM_RBK_CTRL_SRO_DIRECT rbk_ctrl_sro_direct = gctImLtmRbkCtrlSroDirectBase;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	gint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	// SRO setting
	ct_im_ltm_rbk_set_sro( E_IM_PRO_BOTH_UNIT, 1 );

	rbkCtrlCommon->reduction_enable = D_IM_LTM_ENABLE_OFF;
	rbk_ctrl_sro_direct.shift_enable0 = D_IM_LTM_ENABLE_OFF;
	rbk_ctrl_sro_direct.bayer_trim0.img_top   = 0;
	rbk_ctrl_sro_direct.bayer_trim0.img_left  = 0;
	rbk_ctrl_sro_direct.bayer_trim0.img_width = 1282;
	rbk_ctrl_sro_direct.bayer_trim0.img_lines = 962;

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_RBK_Ctrl_Common( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), rbkCtrlCommon );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Ctrl_ModeSRODirect( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), &rbk_ctrl_sro_direct );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Set_OutData_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			ct_im_rbk_run3_get_gct_im_ltm_rbk_outdata_base(priv->ctImRbkRun3) );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Set_FrameStop( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), D_IM_LTM_ENABLE_ON );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_LTM_RBK_Start( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_RBK_Ctrl_Common( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), rbkCtrlCommon );
	Im_LTM_RBK_Ctrl_ModeSRODirect( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), &rbk_ctrl_sro_direct );
	Im_LTM_RBK_Set_OutData_Info( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1),
			ct_im_rbk_run3_get_gct_im_ltm_rbk_outdata_base(priv->ctImRbkRun3) );
	Im_LTM_RBK_Set_FrameStop( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1), D_IM_LTM_ENABLE_ON );
	Im_LTM_RBK_Start( ct_im_rbk_run1_get_pipe_no(priv->ctImRbkRun1) );
#endif

	// SRO start
	ct_im_ltm_rbk_start_sro( E_IM_PRO_BOTH_UNIT );
	ct_im_ltm_rbk_waitend_stop_sro( E_IM_PRO_BOTH_UNIT );

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

	return DriverCommon_D_DDIM_OK;
}

T_IM_LTM_RBK_CTRL_SRO_DIRECT *ct_im_rbk_run2_get_gct_im_ltm_rbk_ctrl_sro_direct_base(CtImRbkRun2* self)
{
	CtImRbkRun2Private *priv = CT_IM_RBK_RUN2_GET_PRIVATE(self);
	return priv->gctImLtmRbkCtrlSroDirectBase;
}

void ct_im_rbk_run2_set_var1(CtImRbkRun2* self, CtImRbkRun1* var1)
{
	CtImRbkRun2Private *priv = CT_IM_RBK_RUN2_GET_PRIVATE(self);
	priv->ctImRbkRun1 = g_object_ref(var1);

}

CtImRbkRun2 *ct_im_rbk_run2_new(void) 
{
    CtImRbkRun2 *self = g_object_new(CT_TYPE_IM_RBK_RUN2, NULL);
    return self;
}
