/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-10
*@author              :jianghaodong
*@brief               :CtImRbkRun1类
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
#include "ctimrbkrun1.h"


G_DEFINE_TYPE(CtImRbkRun1, ct_im_rbk_run1, G_TYPE_OBJECT);
#define CT_IM_RBK_RUN1_GET_PRIVATE(o)(G_TYPE_INSTANCE_GET_PRIVATE ((o),CT_TYPE_IM_RBK_RUN1, CtImRbkRun1Private))

struct _CtImRbkRun1Private
{
	CtImRbkRun3* ctImRbkRun3;
	T_IM_LTM_RBK_CTRL_COMMON *gctImLtmRbkCtrlCommonBase;
};

// Max/Min table
static T_IM_LTM_RBK_CTRL_COMMON S_GCT_IM_LTM_RBK_CTRL_COMMON[] = {
	[0] = {	// max
		.line_intr = 0x3FFF,
		.burst_length = D_IM_LTM_BRST_256,
		.mask_write = D_IM_LTM_MASK_WRITE_DISABLE,
		.out_select = D_IM_LTM_RBK_OUT_MAP_DIRECT,
		.data_type = D_IM_LTM_DTYP_UNPACK12,
		.reduction_enable = D_IM_LTM_ENABLE_ON,
		.reduction_mode = D_IM_LTM_RBK_RDC_MODE_DIV_8,
	},
	[1] = {	// min
		.line_intr = 0,
		.burst_length = D_IM_LTM_BRST_512,
		.mask_write = D_IM_LTM_MASK_WRITE_ENABLE,
		.out_select = D_IM_LTM_RBK_OUT_SDRAM,
		.data_type = D_IM_LTM_DTYP_PACK12,
		.reduction_enable = D_IM_LTM_ENABLE_OFF,
		.reduction_mode = D_IM_LTM_RBK_RDC_MODE_DIV_2,
	},
};

static T_IM_LTM_RBK_CTRL_SDRAM_INPUT S_GCT_IM_LTM_RBK_CTRL_SDRAM_IN[] = {
	[0] = {	// max
		.burst_length_r = D_IM_LTM_BRST_256,
		.burst_length_g = D_IM_LTM_BRST_256,
		.burst_length_b = D_IM_LTM_BRST_256,
		.input_global = 0xFFF0,
		.input_rect = {
			.img_top = 8888,
			.img_left = 2264,
			.img_width = 2360,
			.img_lines = 8960,
		},
		.shift_enable = D_IM_LTM_ENABLE_ON,
	},
	[1] = {	// min
		.burst_length_r = D_IM_LTM_BRST_512,
		.burst_length_g = D_IM_LTM_BRST_512,
		.burst_length_b = D_IM_LTM_BRST_512,
		.input_global = 0,
		.input_rect = {
			.img_top = 0,
			.img_left = 0,
			.img_width = 96,
			.img_lines = 72,
		},
		.shift_enable = D_IM_LTM_ENABLE_OFF,
	},
};

static T_IM_LTM_RBK_CTRL_SRO_DIRECT S_GCT_IM_LTM_RBK_CTRL_SRO_DIRECT[] = {
	[0] = {	// max
		.top_pixel0 = D_IM_LTM_RBK_TOP_PIXEL_B,
		.top_pixel1 = D_IM_LTM_RBK_TOP_PIXEL_B,
		.sro_mode = D_IM_LTM_RBK_SRO_DIRECT_2,
		.shift_enable0 = D_IM_LTM_ENABLE_ON,
		.shift_enable1 = D_IM_LTM_ENABLE_ON,
		.half_reduction_enable = D_IM_LTM_ENABLE_ON,
		.bayer_trim0 = {
			.img_top = 4095,
			.img_left = 1023,
			.img_width = 2360,
			.img_lines = 8960,
		},
		.bayer_trim1 = {
			.img_top = 4095,
			.img_left = 1023,
			.img_width = 2360,
			.img_lines = 8960,
		},
	},
	[1] = {	// min
		.top_pixel0 = D_IM_LTM_RBK_TOP_PIXEL_R,
		.top_pixel1 = D_IM_LTM_RBK_TOP_PIXEL_R,
		.sro_mode = D_IM_LTM_RBK_SRO_DIRECT_1,
		.shift_enable0 = D_IM_LTM_ENABLE_OFF,
		.shift_enable1 = D_IM_LTM_ENABLE_OFF,
		.half_reduction_enable = D_IM_LTM_ENABLE_OFF,
		.bayer_trim0 = {
			.img_top = 0,
			.img_left = 0,
			.img_width = 96,
			.img_lines = 72,
		},
		.bayer_trim1 = {
			.img_top = 0,
			.img_left = 0,
			.img_width = 96,
			.img_lines = 72,
		},
	},
};

/*
*DECLS
*/
static void 	dispose_od(GObject *object);
static void 	finalize_od(GObject *object);
static void 	ctImLtmRbkHandler(guint32* result, guint32 userParam);

// TestBase table
T_IM_LTM_RBK_CTRL_COMMON gctImLtmRbkCtrlCommonBase = {
	.line_intr = 0,
	.burst_length = D_IM_LTM_BRST_512,
	.mask_write = D_IM_LTM_MASK_WRITE_ENABLE,
	.out_select = D_IM_LTM_RBK_OUT_SDRAM,
	.data_type = D_IM_LTM_DTYP_UNPACK12,
	.reduction_enable = D_IM_LTM_ENABLE_ON,
	.reduction_mode = D_IM_LTM_RBK_RDC_MODE_DIV_4,
	.rbk_user_handler = ctImLtmRbkHandler,
	.user_param = 0,
};
/*
*IMPL
*/

static void ct_im_rbk_run1_class_init(CtImRbkRun1Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtImRbkRun1Private));
}

static void ct_im_rbk_run1_init(CtImRbkRun1 *self)
{
	CtImRbkRun1Private *priv = CT_IM_RBK_RUN1_GET_PRIVATE(self);
	priv->ctImRbkRun3=ct_im_rbk_run3_new();;
	priv->gctImLtmRbkCtrlCommonBase=&gctImLtmRbkCtrlCommonBase;
	self->pipeNo=0;
}

static void dispose_od(GObject *object)
{
	CtImRbkRun1 *self = (CtImRbkRun1*)object;
	CtImRbkRun1Private *priv = CT_IM_RBK_RUN1_GET_PRIVATE(self);
	if(priv->ctImRbkRun3)
		{
			g_object_unref(priv->ctImRbkRun3);
			priv->ctImRbkRun3 = NULL;
		}
	G_OBJECT_CLASS(ct_im_rbk_run1_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
//	CtImRbkRun1 *self = (CtImRbkRun1*)object;
//	CtImRbkRun1Private *priv = CT_IM_RBK_RUN1_GET_PRIVATE(self);
//	G_OBJECT_CLASS(ct_im_rbk_run1_parent_class)->dispose(object);
}

static void ctImLtmRbkHandler(guint32* result, guint32 userParam)
{
	if( ((*result) & D_IM_LTM_RBK1_INT_STATE_RBK_END) != 0 ) {
		Ddim_Print(( "LTM RBK1 end. 0x%x\n", userParam ));
	}
	if( ((*result) & D_IM_LTM_RBK1_INT_STATE_FRAME_END) != 0 ) {
		Ddim_Print(( "LTM RBK1 Receiving the top of the frame. 0x%x\n", userParam ));
	}
	if( ((*result) & D_IM_LTM_RBK1_INT_STATE_LINE_END) != 0 ) {
		Ddim_Print(( "LTM RBK1 line end. 0x%x\n", userParam ));
	}
	if( ((*result) & D_IM_LTM_RBK1_INT_STATE_WAIT_ERR) != 0 ) {
		Ddim_Print(( "LTM RBK1 overrun error! 0x%x\n", userParam ));
	}
	if( ((*result) & D_IM_LTM_RBK1_INT_STATE_AXR_ERR) != 0 ) {
		Ddim_Print(( "LTM RBK1 AXR error! 0x%x\n", userParam ));
	}
	if( ((*result) & D_IM_LTM_RBK1_INT_STATE_AXW_ERR) != 0 ) {
		Ddim_Print(( "LTM RBK1 AXW error! 0x%x\n", userParam ));
	}
	if( ((*result) & D_IM_LTM_RBK2_INT_STATE_RBK_END) != 0 ) {
		Ddim_Print(( "LTM RBK2 end. 0x%x\n", userParam ));
	}
	if( ((*result) & D_IM_LTM_RBK2_INT_STATE_FRAME_END) != 0 ) {
		Ddim_Print(( "LTM RBK2 Receiving the top of the frame. 0x%x\n", userParam ));
	}
	if( ((*result) & D_IM_LTM_RBK2_INT_STATE_LINE_END) != 0 ) {
		Ddim_Print(( "LTM RBK2 line end. 0x%x\n", userParam ));
	}
	if( ((*result) & D_IM_LTM_RBK2_INT_STATE_WAIT_ERR) != 0 ) {
		Ddim_Print(( "LTM RBK2 overrun error! 0x%x\n", userParam ));
	}
	if( ((*result) & D_IM_LTM_RBK2_INT_STATE_AXR_ERR) != 0 ) {
		Ddim_Print(( "LTM RBK2 AXR error! 0x%x\n", userParam ));
	}
	if( ((*result) & D_IM_LTM_RBK2_INT_STATE_AXW_ERR) != 0 ) {
		Ddim_Print(( "LTM RBK2 AXW error! 0x%x\n", userParam ));
	}
}

/*
*PUBLIC
*/
#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run1_rbk_1_1: "
gint32 ct_im_rbk_run1_rbk_1_1(CtImRbkRun1* self)
{
	gint32 ercd;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	ercd = Im_LTM_RBK_Init( self->pipeNo );

	Im_LTM_On_Pclk( D_IM_LTM_PIPE12 );
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_LTM_P1.RBK.RBKSR   = 0x%lx\n", IO_LTM_P1.RBK.RBKSR.word ));
	Ddim_Print(( "IO_LTM_P1.RBK.RSRAMEN = 0x%lx\n", IO_LTM_P1.RBK.RSRAMEN.word ));
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_LTM_P2.RBK.RBKSR   = 0x%lx\n", IO_LTM_P2.RBK.RBKSR.word ));
	Ddim_Print(( "IO_LTM_P2.RBK.RSRAMEN = 0x%lx\n", IO_LTM_P2.RBK.RSRAMEN.word ));
	Im_LTM_Off_Pclk( D_IM_LTM_PIPE12 );

	return ercd;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run1_rbk_1_2: "
gint32 ct_im_rbk_run1_rbk_1_2(CtImRbkRun1* self)
{
	guint32					loopcnt;
	T_IM_LTM_RBK_CTRL_AXI	rbkCtrlAxi[] = {
		[0] = {	// max
			.rch[0].cache_type = 0xF,
			.rch[0].protect_type = 7,
			.rch[1].cache_type = 0xF,
			.rch[1].protect_type = 7,
			.rch[2].cache_type = 0xF,
			.rch[2].protect_type = 7,
			.wch.cache_type = 0xF,
			.wch.protect_type = 7,
		},
		[1] = {	// min
			.rch[0].cache_type = 0,
			.rch[0].protect_type = 0,
			.rch[1].cache_type = 0,
			.rch[1].protect_type = 0,
			.rch[2].cache_type = 0,
			.rch[2].protect_type = 0,
			.wch.cache_type = 0,
			.wch.protect_type = 0,
		},
	};

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	for( loopcnt = 0; loopcnt < (sizeof(rbkCtrlAxi) / sizeof(rbkCtrlAxi[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

		Im_LTM_RBK_Ctrl_Axi( self->pipeNo, &rbkCtrlAxi[loopcnt] );

		Im_LTM_On_Pclk( D_IM_LTM_PIPE12 );
		Ddim_Print(( "IO_LTM_P1.RBK.RAXICTLR1.bit.ARCACHE_R = %u\n", IO_LTM_P1.RBK.RAXICTLR1.bit.ARCACHE_R ));
		Ddim_Print(( "IO_LTM_P1.RBK.RAXICTLR1.bit.ARPROT_R  = %u\n", IO_LTM_P1.RBK.RAXICTLR1.bit.ARPROT_R  ));
		Ddim_Print(( "IO_LTM_P1.RBK.RAXICTLR1.bit.ARCACHE_G = %u\n", IO_LTM_P1.RBK.RAXICTLR1.bit.ARCACHE_G ));
		Ddim_Print(( "IO_LTM_P1.RBK.RAXICTLR1.bit.ARPROT_G  = %u\n", IO_LTM_P1.RBK.RAXICTLR1.bit.ARPROT_G  ));
		Ddim_Print(( "IO_LTM_P1.RBK.RAXICTLR1.bit.ARCACHE_B = %u\n", IO_LTM_P1.RBK.RAXICTLR1.bit.ARCACHE_B ));
		Ddim_Print(( "IO_LTM_P1.RBK.RAXICTLR1.bit.ARPROT_B  = %u\n", IO_LTM_P1.RBK.RAXICTLR1.bit.ARPROT_B  ));
		Ddim_Print(( "IO_LTM_P1.RBK.RAXICTLW1.bit.AWCACHE   = %u\n", IO_LTM_P1.RBK.RAXICTLW1.bit.AWCACHE   ));
		Ddim_Print(( "IO_LTM_P1.RBK.RAXICTLW1.bit.AWPROT    = %u\n", IO_LTM_P1.RBK.RAXICTLW1.bit.AWPROT    ));
		Ddim_Print(( "\n" ));
		Ddim_Print(( "IO_LTM_P2.RBK.RAXICTLR1.bit.ARCACHE_R = %u\n", IO_LTM_P2.RBK.RAXICTLR1.bit.ARCACHE_R ));
		Ddim_Print(( "IO_LTM_P2.RBK.RAXICTLR1.bit.ARPROT_R  = %u\n", IO_LTM_P2.RBK.RAXICTLR1.bit.ARPROT_R  ));
		Ddim_Print(( "IO_LTM_P2.RBK.RAXICTLR1.bit.ARCACHE_G = %u\n", IO_LTM_P2.RBK.RAXICTLR1.bit.ARCACHE_G ));
		Ddim_Print(( "IO_LTM_P2.RBK.RAXICTLR1.bit.ARPROT_G  = %u\n", IO_LTM_P2.RBK.RAXICTLR1.bit.ARPROT_G  ));
		Ddim_Print(( "IO_LTM_P2.RBK.RAXICTLR1.bit.ARCACHE_B = %u\n", IO_LTM_P2.RBK.RAXICTLR1.bit.ARCACHE_B ));
		Ddim_Print(( "IO_LTM_P2.RBK.RAXICTLR1.bit.ARPROT_B  = %u\n", IO_LTM_P2.RBK.RAXICTLR1.bit.ARPROT_B  ));
		Ddim_Print(( "IO_LTM_P2.RBK.RAXICTLW1.bit.AWCACHE   = %u\n", IO_LTM_P2.RBK.RAXICTLW1.bit.AWCACHE   ));
		Ddim_Print(( "IO_LTM_P2.RBK.RAXICTLW1.bit.AWPROT    = %u\n", IO_LTM_P2.RBK.RAXICTLW1.bit.AWPROT    ));
		Im_LTM_Off_Pclk( D_IM_LTM_PIPE12 );
	}

	return DriverCommon_D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run1_rbk_1_3: "
gint32 ct_im_rbk_run1_rbk_1_3(CtImRbkRun1* self)
{
	T_IM_LTM_RBK_AXI_RCH_STAT rbkAxiReadStat;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

#ifdef CO_DEBUG_ON_PC
	if( ct_im_ltm_rbk_check_target_pipe_no_1( self->pipeNo ) ){
		IO_LTM_P1.RBK.RAXIRERR.bit.RRESP_R = 3;
		IO_LTM_P1.RBK.RAXIRERR.bit.RRESP_G = 3;
		IO_LTM_P1.RBK.RAXIRERR.bit.RRESP_B = 3;
	}
	if( ct_im_ltm_rbk_check_target_pipe_no_2( self->pipeNo ) ){
		IO_LTM_P2.RBK.RAXIRERR.bit.RRESP_R = 3;
		IO_LTM_P2.RBK.RAXIRERR.bit.RRESP_G = 3;
		IO_LTM_P2.RBK.RAXIRERR.bit.RRESP_B = 3;
	}
#endif // CO_DEBUG_ON_PC
	memset( &rbkAxiReadStat, '\0', sizeof(rbkAxiReadStat) );
	Im_LTM_RBK_Get_AxiReadStat( self->pipeNo, &rbkAxiReadStat );
	Ddim_Print(( "rch_axi_stat[0] = %u\n", rbkAxiReadStat.rch_axi_stat[0] ));
	Ddim_Print(( "rch_axi_stat[1] = %u\n", rbkAxiReadStat.rch_axi_stat[1] ));
	Ddim_Print(( "rch_axi_stat[2] = %u\n", rbkAxiReadStat.rch_axi_stat[2] ));

#ifdef CO_DEBUG_ON_PC
	if( ct_im_ltm_rbk_check_target_pipe_no_1( self->pipeNo ) ){
		IO_LTM_P1.RBK.RAXIRERR.bit.RRESP_R = 0;
		IO_LTM_P1.RBK.RAXIRERR.bit.RRESP_G = 0;
		IO_LTM_P1.RBK.RAXIRERR.bit.RRESP_B = 0;
	}
	if( ct_im_ltm_rbk_check_target_pipe_no_2( self->pipeNo ) ){
		IO_LTM_P2.RBK.RAXIRERR.bit.RRESP_R = 0;
		IO_LTM_P2.RBK.RAXIRERR.bit.RRESP_G = 0;
		IO_LTM_P2.RBK.RAXIRERR.bit.RRESP_B = 0;
	}
#endif // CO_DEBUG_ON_PC
	memset( &rbkAxiReadStat, '\0', sizeof(rbkAxiReadStat) );
	Im_LTM_RBK_Get_AxiReadStat( self->pipeNo, &rbkAxiReadStat );
	Ddim_Print(( "rch_axi_stat[0] = %u\n", rbkAxiReadStat.rch_axi_stat[0] ));
	Ddim_Print(( "rch_axi_stat[1] = %u\n", rbkAxiReadStat.rch_axi_stat[1] ));
	Ddim_Print(( "rch_axi_stat[2] = %u\n", rbkAxiReadStat.rch_axi_stat[2] ));

	return DriverCommon_D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run1_rbk_1_4: "
gint32 ct_im_rbk_run1_rbk_1_4(CtImRbkRun1* self)
{
	T_IM_LTM_RBK_AXI_WCH_STAT rbkAxiWriteStat;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

#ifdef CO_DEBUG_ON_PC
	if( ct_im_ltm_rbk_check_target_pipe_no_1( self->pipeNo ) ){
		IO_LTM_P1.RBK.RAXIWERR.bit.WRESP = 3;
	}
	if( ct_im_ltm_rbk_check_target_pipe_no_2( self->pipeNo ) ){
		IO_LTM_P2.RBK.RAXIWERR.bit.WRESP = 3;
	}
#endif // CO_DEBUG_ON_PC
	memset( &rbkAxiWriteStat, '\0', sizeof(rbkAxiWriteStat) );
	Im_LTM_RBK_Get_AxiWriteStat( self->pipeNo, &rbkAxiWriteStat );
	Ddim_Print(( "wch_axi_stat = %u\n", rbkAxiWriteStat.wch_axi_stat ));

#ifdef CO_DEBUG_ON_PC
	if( ct_im_ltm_rbk_check_target_pipe_no_1( self->pipeNo ) ){
		IO_LTM_P1.RBK.RAXIWERR.bit.WRESP = 0;
	}
	if( ct_im_ltm_rbk_check_target_pipe_no_2( self->pipeNo ) ){
		IO_LTM_P2.RBK.RAXIWERR.bit.WRESP = 0;
	}
#endif // CO_DEBUG_ON_PC
	memset( &rbkAxiWriteStat, '\0', sizeof(rbkAxiWriteStat) );
	Im_LTM_RBK_Get_AxiWriteStat( self->pipeNo, &rbkAxiWriteStat );
	Ddim_Print(( "wch_axi_stat = %u\n", rbkAxiWriteStat.wch_axi_stat ));

	return DriverCommon_D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run1_rbk_1_5: "
gint32 ct_im_rbk_run1_rbk_1_5(CtImRbkRun1* self)
{
	T_IM_LTM_RBK_AXI_CTRL_PARAM rbkAxiCtrlParam;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	if( ct_im_ltm_rbk_check_target_pipe_no_1( self->pipeNo ) ){
		IO_LTM_P1.RBK.RAXIBSIZ.bit.BURSTRR = 1;
		IO_LTM_P1.RBK.RAXIBSIZ.bit.BURSTRG = 1;
		IO_LTM_P1.RBK.RAXIBSIZ.bit.BURSTRB = 1;
		IO_LTM_P1.RBK.RAXIBSIZ.bit.BURSTW  = 1;
		IO_LTM_P1.RBK.RAXIBSIZ.bit.WSTBMSK = 1;
	}
	if( ct_im_ltm_rbk_check_target_pipe_no_2( self->pipeNo ) ){
		IO_LTM_P2.RBK.RAXIBSIZ.bit.BURSTRR = 1;
		IO_LTM_P2.RBK.RAXIBSIZ.bit.BURSTRG = 1;
		IO_LTM_P2.RBK.RAXIBSIZ.bit.BURSTRB = 1;
		IO_LTM_P2.RBK.RAXIBSIZ.bit.BURSTW  = 1;
		IO_LTM_P2.RBK.RAXIBSIZ.bit.WSTBMSK = 1;
	}
	memset( &rbkAxiCtrlParam, '\0', sizeof(rbkAxiCtrlParam) );
	Im_LTM_RBK_Get_AxiCtrlParam( self->pipeNo, &rbkAxiCtrlParam );
	Ddim_Print(( "rch_burst_length_r = %u\n", rbkAxiCtrlParam.rch_burst_length_r ));
	Ddim_Print(( "rch_burst_length_g = %u\n", rbkAxiCtrlParam.rch_burst_length_g ));
	Ddim_Print(( "rch_burst_length_b = %u\n", rbkAxiCtrlParam.rch_burst_length_b ));
	Ddim_Print(( "wch_burst_length   = %u\n", rbkAxiCtrlParam.wch_burst_length   ));
	Ddim_Print(( "mask_write         = %u\n", rbkAxiCtrlParam.mask_write         ));

	if( ct_im_ltm_rbk_check_target_pipe_no_1( self->pipeNo ) ){
		IO_LTM_P1.RBK.RAXIBSIZ.bit.BURSTRR = 0;
		IO_LTM_P1.RBK.RAXIBSIZ.bit.BURSTRG = 0;
		IO_LTM_P1.RBK.RAXIBSIZ.bit.BURSTRB = 0;
		IO_LTM_P1.RBK.RAXIBSIZ.bit.BURSTW  = 0;
		IO_LTM_P1.RBK.RAXIBSIZ.bit.WSTBMSK = 0;
	}
	if( ct_im_ltm_rbk_check_target_pipe_no_2( self->pipeNo ) ){
		IO_LTM_P2.RBK.RAXIBSIZ.bit.BURSTRR = 0;
		IO_LTM_P2.RBK.RAXIBSIZ.bit.BURSTRG = 0;
		IO_LTM_P2.RBK.RAXIBSIZ.bit.BURSTRB = 0;
		IO_LTM_P2.RBK.RAXIBSIZ.bit.BURSTW  = 0;
		IO_LTM_P2.RBK.RAXIBSIZ.bit.WSTBMSK = 0;
	}
	memset( &rbkAxiCtrlParam, '\0', sizeof(rbkAxiCtrlParam) );
	Im_LTM_RBK_Get_AxiCtrlParam( self->pipeNo, &rbkAxiCtrlParam );
	Ddim_Print(( "rch_burst_length_r = %u\n", rbkAxiCtrlParam.rch_burst_length_r ));
	Ddim_Print(( "rch_burst_length_g = %u\n", rbkAxiCtrlParam.rch_burst_length_g ));
	Ddim_Print(( "rch_burst_length_b = %u\n", rbkAxiCtrlParam.rch_burst_length_b ));
	Ddim_Print(( "wch_burst_length   = %u\n", rbkAxiCtrlParam.wch_burst_length   ));
	Ddim_Print(( "mask_write         = %u\n", rbkAxiCtrlParam.mask_write         ));

	return DriverCommon_D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run1_rbk_1_6: "
gint32 ct_im_rbk_run1_rbk_1_6(CtImRbkRun1* self)
{
	guint32						loopcnt;
	T_IM_LTM_RBK_AXI_CTRL_PARAM	rbkAxiCtrlParam[] = {
		[0] = {	// max
			.rch_burst_length_r = 1,
			.rch_burst_length_g = 1,
			.rch_burst_length_b = 1,
			.wch_burst_length = 1,
			.mask_write = 1,
		},
		[1] = {	// min
			.rch_burst_length_r = 0,
			.rch_burst_length_g = 0,
			.rch_burst_length_b = 0,
			.wch_burst_length = 0,
			.mask_write = 0,
		},
	};

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	for( loopcnt = 0; loopcnt < (sizeof(rbkAxiCtrlParam) / sizeof(rbkAxiCtrlParam[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

		Im_LTM_RBK_Set_AxiCtrlParam( self->pipeNo, &rbkAxiCtrlParam[loopcnt] );

		Im_LTM_On_Pclk( D_IM_LTM_PIPE12 );
		Ddim_Print(( "IO_LTM_P1.RBK.RAXIBSIZ.bit.BURSTRR = %u\n", IO_LTM_P1.RBK.RAXIBSIZ.bit.BURSTRR ));
		Ddim_Print(( "IO_LTM_P1.RBK.RAXIBSIZ.bit.BURSTRG = %u\n", IO_LTM_P1.RBK.RAXIBSIZ.bit.BURSTRG ));
		Ddim_Print(( "IO_LTM_P1.RBK.RAXIBSIZ.bit.BURSTRB = %u\n", IO_LTM_P1.RBK.RAXIBSIZ.bit.BURSTRB ));
		Ddim_Print(( "IO_LTM_P1.RBK.RAXIBSIZ.bit.BURSTW  = %u\n", IO_LTM_P1.RBK.RAXIBSIZ.bit.BURSTW  ));
		Ddim_Print(( "IO_LTM_P1.RBK.RAXIBSIZ.bit.WSTBMSK = %u\n", IO_LTM_P1.RBK.RAXIBSIZ.bit.WSTBMSK ));
		Ddim_Print(( "\n" ));
		Ddim_Print(( "IO_LTM_P2.RBK.RAXIBSIZ.bit.BURSTRR = %u\n", IO_LTM_P2.RBK.RAXIBSIZ.bit.BURSTRR ));
		Ddim_Print(( "IO_LTM_P2.RBK.RAXIBSIZ.bit.BURSTRG = %u\n", IO_LTM_P2.RBK.RAXIBSIZ.bit.BURSTRG ));
		Ddim_Print(( "IO_LTM_P2.RBK.RAXIBSIZ.bit.BURSTRB = %u\n", IO_LTM_P2.RBK.RAXIBSIZ.bit.BURSTRB ));
		Ddim_Print(( "IO_LTM_P2.RBK.RAXIBSIZ.bit.BURSTW  = %u\n", IO_LTM_P2.RBK.RAXIBSIZ.bit.BURSTW  ));
		Ddim_Print(( "IO_LTM_P2.RBK.RAXIBSIZ.bit.WSTBMSK = %u\n", IO_LTM_P2.RBK.RAXIBSIZ.bit.WSTBMSK ));
		Im_LTM_Off_Pclk( D_IM_LTM_PIPE12 );
	}

	return DriverCommon_D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run1_rbk_1_7: "
gint32 ct_im_rbk_run1_rbk_1_7(CtImRbkRun1* self)
{
	guint32	loopcnt;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	for( loopcnt = 0;
			loopcnt < (sizeof(S_GCT_IM_LTM_RBK_CTRL_COMMON) / sizeof(S_GCT_IM_LTM_RBK_CTRL_COMMON[0]));
			loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

		Im_LTM_RBK_Ctrl_Common( self->pipeNo, &S_GCT_IM_LTM_RBK_CTRL_COMMON[loopcnt] );

		ct_im_ltm_rbk_print_ctrl_common_reg();
	}

	return DriverCommon_D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run1_rbk_1_8: "
gint32 ct_im_rbk_run1_rbk_1_8(CtImRbkRun1* self)
{
	guint32	loopcnt;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	for( loopcnt = 0;
			loopcnt < (sizeof(S_GCT_IM_LTM_RBK_CTRL_SDRAM_IN) / sizeof(S_GCT_IM_LTM_RBK_CTRL_SDRAM_IN[0]));
			loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

		Im_LTM_RBK_Ctrl_ModeSDRAMInput( self->pipeNo, &S_GCT_IM_LTM_RBK_CTRL_SDRAM_IN[loopcnt] );

		ct_im_ltm_rbk_print_ctrl_sdram_input_reg();
	}

	return DriverCommon_D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run1_rbk_1_9: "
gint32 ct_im_rbk_run1_rbk_1_9(CtImRbkRun1* self)
{
	CtImRbkRun1Private *priv = CT_IM_RBK_RUN1_GET_PRIVATE(self);

	guint32 loopcnt;
	T_IM_LTM_RBK_CTRL_SDRAM_INPUT *rbkCtrlSdramIn =
			ct_im_rbk_run3_get_gct_im_ltm_rbk_ctrl_sdram_in_base(priv->ctImRbkRun3);
	T_IM_LTM_INADDR_INFO rbkInAddr[] = {
		[0] = { // max
			.addr_r = (void*)0xFFFFFFFE,
			.addr_g = (void*)0xFFFFFFFE,
			.addr_b = (void*)0xFFFFFFFE,
		},
		[1] = { // min
			.addr_r = (void*)0,
			.addr_g = (void*)0,
			.addr_b = (void*)0,
		},
		[2] = { // indvisual
			.addr_r = (void*)D_IM_LTM_RBK_IMG_MEM_IN_R_ADDR_TOP,
			.addr_g = (void*)D_IM_LTM_RBK_IMG_MEM_IN_G_ADDR_TOP,
			.addr_b = (void*)D_IM_LTM_RBK_IMG_MEM_IN_B_ADDR_TOP,
		},
	};

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	Im_LTM_RBK_Ctrl_Common( self->pipeNo, &gctImLtmRbkCtrlCommonBase );
	Im_LTM_RBK_Ctrl_ModeSDRAMInput( self->pipeNo, rbkCtrlSdramIn );

	for( loopcnt = 0; loopcnt < (sizeof(rbkInAddr) / sizeof(rbkInAddr[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

		Im_LTM_RBK_Set_InAddr_Info( self->pipeNo, &rbkInAddr[loopcnt] );

		ct_im_ltm_rbk_print_ctrl_sdram_input_reg();

		Im_LTM_On_Pclk( D_IM_LTM_PIPE12 );
		Ddim_Print(( "IO_LTM_P1.RBK.RSDRADR.bit.SDRADR = 0x%lx\n", IO_LTM_P1.RBK.RSDRADR.bit.SDRADR ));
		Ddim_Print(( "IO_LTM_P1.RBK.RSDRADG.bit.SDRADG = 0x%lx\n", IO_LTM_P1.RBK.RSDRADG.bit.SDRADG ));
		Ddim_Print(( "IO_LTM_P1.RBK.RSDRADB.bit.SDRADB = 0x%lx\n", IO_LTM_P1.RBK.RSDRADB.bit.SDRADB ));
		Ddim_Print(( "\n" ));
		Ddim_Print(( "IO_LTM_P2.RBK.RSDRADR.bit.SDRADR = 0x%lx\n", IO_LTM_P2.RBK.RSDRADR.bit.SDRADR ));
		Ddim_Print(( "IO_LTM_P2.RBK.RSDRADG.bit.SDRADG = 0x%lx\n", IO_LTM_P2.RBK.RSDRADG.bit.SDRADG ));
		Ddim_Print(( "IO_LTM_P2.RBK.RSDRADB.bit.SDRADB = 0x%lx\n", IO_LTM_P2.RBK.RSDRADB.bit.SDRADB ));
		Im_LTM_Off_Pclk( D_IM_LTM_PIPE12 );
	}

	rbkCtrlSdramIn->input_rect.img_top = 100;
	rbkCtrlSdramIn->input_rect.img_left = 200;

	Im_LTM_RBK_Ctrl_ModeSDRAMInput( self->pipeNo, rbkCtrlSdramIn );

	Im_LTM_RBK_Set_InAddr_Info( self->pipeNo, &rbkInAddr[2] );

	ct_im_ltm_rbk_print_ctrl_sdram_input_reg();

	Im_LTM_On_Pclk( D_IM_LTM_PIPE12 );
	Ddim_Print(( "IO_LTM_P1.RBK.RSDRADR.bit.SDRADR = 0x%lx\n", IO_LTM_P1.RBK.RSDRADR.bit.SDRADR ));
	Ddim_Print(( "IO_LTM_P1.RBK.RSDRADG.bit.SDRADG = 0x%lx\n", IO_LTM_P1.RBK.RSDRADG.bit.SDRADG ));
	Ddim_Print(( "IO_LTM_P1.RBK.RSDRADB.bit.SDRADB = 0x%lx\n", IO_LTM_P1.RBK.RSDRADB.bit.SDRADB ));
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_LTM_P2.RBK.RSDRADR.bit.SDRADR = 0x%lx\n", IO_LTM_P2.RBK.RSDRADR.bit.SDRADR ));
	Ddim_Print(( "IO_LTM_P2.RBK.RSDRADG.bit.SDRADG = 0x%lx\n", IO_LTM_P2.RBK.RSDRADG.bit.SDRADG ));
	Ddim_Print(( "IO_LTM_P2.RBK.RSDRADB.bit.SDRADB = 0x%lx\n", IO_LTM_P2.RBK.RSDRADB.bit.SDRADB ));
	Im_LTM_Off_Pclk( D_IM_LTM_PIPE12 );

	return DriverCommon_D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run1_rbk_1_10: "
gint32 ct_im_rbk_run1_rbk_1_10(CtImRbkRun1* self)
{
	guint32						loopcnt;
	T_IM_LTM_RBK_OUTDATA_INFO	rbkOutdataInfo[] = {
		[0] = {	// max
			.addr = (void*)0xFFFFFFFF,
			.global_width = 0xFFF8,
		},
		[1] = {	// min
			.addr = (void*)0,
			.global_width = 0,
		},
	};

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	for( loopcnt = 0; loopcnt < (sizeof(rbkOutdataInfo) / sizeof(rbkOutdataInfo[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

		Im_LTM_RBK_Set_OutData_Info( self->pipeNo, &rbkOutdataInfo[loopcnt] );

		Im_LTM_On_Pclk( D_IM_LTM_PIPE12 );
		Ddim_Print(( "IO_LTM_P1.RBK.RSDWAD.bit.SDWAD   = 0x%lx\n", IO_LTM_P1.RBK.RSDWAD.bit.SDWAD   ));
		Ddim_Print(( "IO_LTM_P1.RBK.RSDWDEF.bit.SDWDEF = 0x%x\n",  IO_LTM_P1.RBK.RSDWDEF.bit.SDWDEF ));
		Ddim_Print(( "\n" ));
		Ddim_Print(( "IO_LTM_P2.RBK.RSDWAD.bit.SDWAD   = 0x%lx\n", IO_LTM_P2.RBK.RSDWAD.bit.SDWAD   ));
		Ddim_Print(( "IO_LTM_P2.RBK.RSDWDEF.bit.SDWDEF = 0x%x\n",  IO_LTM_P2.RBK.RSDWDEF.bit.SDWDEF ));
		Im_LTM_Off_Pclk( D_IM_LTM_PIPE12 );
	}

	return DriverCommon_D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run1_rbk_1_11: "
gint32 ct_im_rbk_run1_rbk_1_11(CtImRbkRun1* self)
{
	guint32	loopcnt;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	for( loopcnt = 0; loopcnt < (sizeof(S_GCT_IM_LTM_RBK_CTRL_SRO_DIRECT) / sizeof(S_GCT_IM_LTM_RBK_CTRL_SRO_DIRECT[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

		Im_LTM_RBK_Ctrl_ModeSRODirect( self->pipeNo, &S_GCT_IM_LTM_RBK_CTRL_SRO_DIRECT[loopcnt] );

		ct_im_ltm_rbk_print_sro_direct_reg();
	}

	return DriverCommon_D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run1_rbk_1_12: "
gint32 ct_im_rbk_run1_rbk_1_12(CtImRbkRun1* self)
{
	guint32	loopcnt;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	for( loopcnt = 0; loopcnt < 2; loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

		Im_LTM_RBK_Ctrl_Resolution_Conversion( self->pipeNo, loopcnt );

		Im_LTM_On_Pclk( D_IM_LTM_PIPE12 );
		Ddim_Print(( "IO_LTM_P1.RBK.RHSTA.bit.HSTA = 0x%x\n", IO_LTM_P1.RBK.RHSTA.bit.HSTA ));
		Ddim_Print(( "IO_LTM_P1.RBK.RHPIT.bit.HPIT = 0x%x\n", IO_LTM_P1.RBK.RHPIT.bit.HPIT ));
		Ddim_Print(( "IO_LTM_P1.RBK.RVSTA.bit.VSTA = 0x%x\n", IO_LTM_P1.RBK.RVSTA.bit.VSTA ));
		Ddim_Print(( "IO_LTM_P1.RBK.RVPIT.bit.VPIT = 0x%x\n", IO_LTM_P1.RBK.RVPIT.bit.VPIT ));
		Ddim_Print(( "\n" ));
		Ddim_Print(( "IO_LTM_P2.RBK.RHSTA.bit.HSTA = 0x%x\n", IO_LTM_P2.RBK.RHSTA.bit.HSTA ));
		Ddim_Print(( "IO_LTM_P2.RBK.RHPIT.bit.HPIT = 0x%x\n", IO_LTM_P2.RBK.RHPIT.bit.HPIT ));
		Ddim_Print(( "IO_LTM_P2.RBK.RVSTA.bit.VSTA = 0x%x\n", IO_LTM_P2.RBK.RVSTA.bit.VSTA ));
		Ddim_Print(( "IO_LTM_P2.RBK.RVPIT.bit.VPIT = 0x%x\n", IO_LTM_P2.RBK.RVPIT.bit.VPIT ));
		Im_LTM_Off_Pclk( D_IM_LTM_PIPE12 );
	}

	return DriverCommon_D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run1_rbk_1_13: "
gint32 ct_im_rbk_run1_rbk_1_13(CtImRbkRun1* self)
{
	guint32	loopcnt;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	for( loopcnt = 0; loopcnt < 2; loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

		Im_LTM_RBK_Set_FrameStop( self->pipeNo, loopcnt );

		Im_LTM_On_Pclk( D_IM_LTM_PIPE12 );
		Ddim_Print(( "IO_LTM_P1.RBK.RFRSTP.bit.FRSTP = %u\n", IO_LTM_P1.RBK.RFRSTP.bit.FRSTP ));
		Ddim_Print(( "\n" ));
		Ddim_Print(( "IO_LTM_P2.RBK.RFRSTP.bit.FRSTP = %u\n", IO_LTM_P2.RBK.RFRSTP.bit.FRSTP ));
		Im_LTM_Off_Pclk( D_IM_LTM_PIPE12 );
	}

	return DriverCommon_D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run1_rbk_1_14: "
gint32 ct_im_rbk_run1_rbk_1_14(CtImRbkRun1* self)
{
	guint32	loopcnt;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	for( loopcnt = 0; loopcnt < 2; loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

		Im_LTM_RBK_Set_ParamHold( self->pipeNo, loopcnt );

		Im_LTM_On_Pclk( D_IM_LTM_PIPE12 );
		Ddim_Print(( "IO_LTM_P1.RBK.RPARMSK.bit.PARMSK = %u\n", IO_LTM_P1.RBK.RPARMSK.bit.PARMSK ));
		Ddim_Print(( "\n" ));
		Ddim_Print(( "IO_LTM_P2.RBK.RPARMSK.bit.PARMSK = %u\n", IO_LTM_P2.RBK.RPARMSK.bit.PARMSK ));
		Im_LTM_Off_Pclk( D_IM_LTM_PIPE12 );
	}

	return DriverCommon_D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run1_rbk_1_15: "
gint32 ct_im_rbk_run1_rbk_1_15(CtImRbkRun1* self)
{
	BOOL busyStat = FALSE;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

#ifdef CO_DEBUG_ON_PC
	if( ct_im_ltm_rbk_check_target_pipe_no_1( self->pipeNo ) ){
		IO_LTM_P1.RBK.RTRG.bit.TRG = 3;
	}
	if( ct_im_ltm_rbk_check_target_pipe_no_2( self->pipeNo ) ){
		IO_LTM_P2.RBK.RTRG.bit.TRG = 3;
	}
#endif // CO_DEBUG_ON_PC
	Im_LTM_RBK_Get_RbkBusy( self->pipeNo, &busyStat );
	Ddim_Print(( "busyStat = %u\n", busyStat ));

#ifdef CO_DEBUG_ON_PC
	if( ct_im_ltm_rbk_check_target_pipe_no_1( self->pipeNo ) ){
		IO_LTM_P1.RBK.RTRG.bit.TRG = 2;
	}
	if( ct_im_ltm_rbk_check_target_pipe_no_2( self->pipeNo ) ){
		IO_LTM_P2.RBK.RTRG.bit.TRG = 2;
	}
#endif // CO_DEBUG_ON_PC

	busyStat = FALSE;

	Im_LTM_RBK_Get_RbkBusy( self->pipeNo, &busyStat );
	Ddim_Print(( "busyStat = %u\n", busyStat ));

	return DriverCommon_D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run1_rbk_1_16: "
gint32 ct_im_rbk_run1_rbk_1_16(CtImRbkRun1* self)
{
	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	Im_LTM_RBK_ContStart( self->pipeNo );

	Im_LTM_On_Pclk( D_IM_LTM_PIPE12 );
	Ddim_Print(( "IO_LTM_P1.RBK.RTRG.bit.TRG = %u\n", IO_LTM_P1.RBK.RTRG.bit.TRG ));
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_LTM_P2.RBK.RTRG.bit.TRG = %u\n", IO_LTM_P2.RBK.RTRG.bit.TRG ));
	Im_LTM_Off_Pclk( D_IM_LTM_PIPE12 );

	return DriverCommon_D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_rbk_run1_rbk_1_17: "
gint32 ct_im_rbk_run1_rbk_1_17(CtImRbkRun1* self)
{
	guint32						loopcnt;
	T_IM_LTM_RBK_RGB_TRIMMING	rbkRgbTrim[] = {
		[0] = {	// max
			.trimming_enable = D_IM_LTM_ENABLE_ON,
			.rgb_trim = {
				.img_top = 1014,
				.img_left = 845,
				.img_width = 854,
				.img_lines = 1022,
			},
		},
		[1] = {	// min
			.trimming_enable = D_IM_LTM_ENABLE_OFF,
			.rgb_trim = {
				.img_top = 0,
				.img_left = 0,
				.img_width = 8,
				.img_lines = 8,
			},
		},
	};

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	for( loopcnt = 0; loopcnt < (sizeof(rbkRgbTrim) / sizeof(rbkRgbTrim[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

		Im_LTM_RBK_Ctrl_RGBTrimming( self->pipeNo, &rbkRgbTrim[loopcnt] );

		Im_LTM_On_Pclk( D_IM_LTM_PIPE12 );
		Ddim_Print(( "IO_LTM_P1.RBK.RTEN.bit.RTEN     = 0x%x\n", IO_LTM_P1.RBK.RTEN.bit.RTEN     ));
		Ddim_Print(( "IO_LTM_P1.RBK.RTHSTA.bit.RTHSTA = 0x%x\n", IO_LTM_P1.RBK.RTHSTA.bit.RTHSTA ));
		Ddim_Print(( "IO_LTM_P1.RBK.RTHSIZ.bit.RTHSIZ = 0x%x\n", IO_LTM_P1.RBK.RTHSIZ.bit.RTHSIZ ));
		Ddim_Print(( "IO_LTM_P1.RBK.RTVSTA.bit.RTVSTA = 0x%x\n", IO_LTM_P1.RBK.RTVSTA.bit.RTVSTA ));
		Ddim_Print(( "IO_LTM_P1.RBK.RTVSIZ.bit.RTVSIZ = 0x%x\n", IO_LTM_P1.RBK.RTVSIZ.bit.RTVSIZ ));
		Ddim_Print(( "\n" ));
		Ddim_Print(( "IO_LTM_P2.RBK.RTEN.bit.RTEN     = 0x%x\n", IO_LTM_P2.RBK.RTEN.bit.RTEN     ));
		Ddim_Print(( "IO_LTM_P2.RBK.RTHSTA.bit.RTHSTA = 0x%x\n", IO_LTM_P2.RBK.RTHSTA.bit.RTHSTA ));
		Ddim_Print(( "IO_LTM_P2.RBK.RTHSIZ.bit.RTHSIZ = 0x%x\n", IO_LTM_P2.RBK.RTHSIZ.bit.RTHSIZ ));
		Ddim_Print(( "IO_LTM_P2.RBK.RTVSTA.bit.RTVSTA = 0x%x\n", IO_LTM_P2.RBK.RTVSTA.bit.RTVSTA ));
		Ddim_Print(( "IO_LTM_P2.RBK.RTVSIZ.bit.RTVSIZ = 0x%x\n", IO_LTM_P2.RBK.RTVSIZ.bit.RTVSIZ ));
		Im_LTM_Off_Pclk( D_IM_LTM_PIPE12 );
	}

	return DriverCommon_D_DDIM_OK;
}

T_IM_LTM_RBK_CTRL_COMMON *ct_im_rbk_run1_get_gct_im_ltm_rbk_ctrl_common_base(CtImRbkRun1* self)
{
	CtImRbkRun1Private *priv = CT_IM_RBK_RUN1_GET_PRIVATE(self);
	return priv->gctImLtmRbkCtrlCommonBase;
}

void ct_im_rbk_run1_set_pipe_no(CtImRbkRun1* self, guchar pipeNo)
{
	self->pipeNo=pipeNo;
}

guchar ct_im_rbk_run1_get_pipe_no(CtImRbkRun1* self)
{
	return self->pipeNo;
}

CtImRbkRun1 *ct_im_rbk_run1_new(void) 
{
    CtImRbkRun1 *self = g_object_new(CT_TYPE_IM_RBK_RUN1, NULL);
    return self;
}
