/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :liudong
*@brief               :CtImB2r2类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#include "ct_im_b2r.h"

#include "im_b2r.h"
#include "im_pro.h"
#include "im_pro_common.h"

#include "driver_common.h"
#include "ddim_user_custom.h"
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
#endif

#include "jdsb2r.h"

#include <stdlib.h>
#include <string.h>

#include "ctimb2r.h"

#include "ctimb2r2.h"
#include "ctimb2r1.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtImB2r2, ct_im_b2r2);
#define CT_IM_B2R2_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtImB2r2Private,CT_TYPE_IM_B2R2))


/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
#define ct_im_b2r_check_target_pipe_no_1(a)		(((a)+1) & (D_IM_B2R_PIPE1+1))
#define ct_im_b2r_check_target_pipe_no_2(a)		(((a)+1) & (D_IM_B2R_PIPE2+1))


struct _CtImB2r2Private
{

};


// Max/Min table
static T_IM_B2R_CTRL S_GCT_IM_B2R_CTRL[] = {
	[0] = {	// max
		.bayer_top_pixel = 3,

		.ybw = {
			.axi_write_mode = {
				.out_sel = 1,
				.burst_length = 2,
			},
			.output_dtype = 3,
			.write_request_mask[D_IM_B2R_PORT_0] = 0xFFF,
			.write_request_mask[D_IM_B2R_PORT_1] = 0xFFF,
			.write_request_mask[D_IM_B2R_PORT_2] = 0xFFF,
			.trim_out_enable = 1,
			.knee_enable = 1,
		},

		.line_intr = {
			.count = 0x3FFF,
		},
		.ybw_continue_start_enable = 1,
		.deknee_enable = 1,
		.cia_bypass = 1,
		.cia_padding = 1,
		.ext_out_en = 1,
		.ext_out_alarm = 3,
	},
	[1] = {	// min
		.bayer_top_pixel = 0,

		.ybw = {
			.axi_write_mode = {
				.out_sel = 0,
				.burst_length = 0,
			},
			.output_dtype = 0,
			.write_request_mask[D_IM_B2R_PORT_0] = 0,
			.write_request_mask[D_IM_B2R_PORT_1] = 0,
			.write_request_mask[D_IM_B2R_PORT_2] = 0,
			.trim_out_enable = 0,
			.knee_enable = 0,
		},

		.line_intr = {
			.count = 0,
		},
		.ybw_continue_start_enable = 0,
		.deknee_enable = 0,
		.cia_bypass = 0,
		.cia_padding = 0,
		.ext_out_alarm = 0,
	},
};
// Max/Min table
static T_IM_B2R_CTRL_SDRAM_INPUT S_GCT_IM_B2R_CTRL_SDRAM_IN[] = {

		[0] = {	// max
			.burst_length = 2,
			.read_request_mask = 0xFFF,
			.input_dtype = 3,
			.top_offset = 7,
			.input_global = 0xFFFF,
			.line_space = 0x3FF,
		},
		[1] = {	// min
			.burst_length = 0,
			.read_request_mask = 0,
			.input_dtype = 0,
			.top_offset = 0,
			.input_global = 0,
			.line_space = 0,
		},
	};

/*
DECLS
*/

static void ct_im_b2r2_constructor(CtImB2r2 *self) 
{
//	CtImB2r2Private *priv = CT_IM_B2R2_GET_PRIVATE(self);
}

static void ct_im_b2r2_destructor(CtImB2r2 *self) 
{
//	CtImB2r2Private *priv = CT_IM_B2R2_GET_PRIVATE(self);
	self = NULL;
}

/*
IMPL//todo
*/

/*
PUBLIC//todo
*/

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r2_1_1: "
kint32 ct_im_b2r2_1_1( CtImB2r2 *self )
{
	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

	return Im_B2R_Init( self->pipeNo );
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r2_1_2: "
kint32 ct_im_b2r2_1_2( CtImB2r2 *self )
{
	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

#ifdef IM_B2R_STATUS_PRINT
	Im_B2R_Print_ClockStatus();
#endif

	Im_B2R_On_Pclk( self->pipeNo );
#ifdef IM_B2R_STATUS_PRINT
	Im_B2R_Print_ClockStatus();
#endif

	Im_B2R_Off_Pclk( self->pipeNo );

	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r2_1_3: "
kint32 ct_im_b2r2_1_3( CtImB2r2 *self )
{
	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

	Im_B2R_On_Pclk( self->pipeNo );

#ifdef IM_B2R_STATUS_PRINT
	Im_B2R_Print_ClockStatus();
#endif

	Im_B2R_Off_Pclk( self->pipeNo );
#ifdef IM_B2R_STATUS_PRINT
	Im_B2R_Print_ClockStatus();
#endif

	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r2_1_4: "
kint32 ct_im_b2r2_1_4( CtImB2r2 *self )
{
	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

#ifdef IM_B2R_STATUS_PRINT
	Im_B2R_Print_ClockStatus();
#endif

	Im_B2R_On_Pclk( self->pipeNo );
#ifdef IM_B2R_STATUS_PRINT
	Im_B2R_Print_ClockStatus();
#endif

	Im_B2R_On_Pclk( self->pipeNo );
#ifdef IM_B2R_STATUS_PRINT
	Im_B2R_Print_ClockStatus();
#endif

	Im_B2R_On_Pclk( self->pipeNo );
#ifdef IM_B2R_STATUS_PRINT
	Im_B2R_Print_ClockStatus();
#endif

	Im_B2R_Force_Off_Pclk( self->pipeNo );
#ifdef IM_B2R_STATUS_PRINT
	Im_B2R_Print_ClockStatus();
#endif

	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r2_1_5: "
kint32 ct_im_b2r2_1_5( CtImB2r2 *self )
{
	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

#ifdef IM_B2R_STATUS_PRINT
	Im_B2R_Print_ClockStatus();
#endif

	Im_B2R_On_Hclk( self->pipeNo );
#ifdef IM_B2R_STATUS_PRINT
	Im_B2R_Print_ClockStatus();
#endif

	Im_B2R_Off_Hclk( self->pipeNo );

	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r2_1_6: "
kint32 ct_im_b2r2_1_6( CtImB2r2 *self )
{
	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

	Im_B2R_On_Hclk( self->pipeNo );
#ifdef IM_B2R_STATUS_PRINT
	Im_B2R_Print_ClockStatus();
#endif

	Im_B2R_Off_Hclk( self->pipeNo );
#ifdef IM_B2R_STATUS_PRINT
	Im_B2R_Print_ClockStatus();
#endif

	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r2_1_7: "
kint32 ct_im_b2r2_1_7( CtImB2r2 *self )
{
	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

#ifdef IM_B2R_STATUS_PRINT
	Im_B2R_Print_ClockStatus();
#endif

	Im_B2R_On_Hclk( self->pipeNo );
#ifdef IM_B2R_STATUS_PRINT
	Im_B2R_Print_ClockStatus();
#endif

	Im_B2R_On_Hclk( self->pipeNo );
#ifdef IM_B2R_STATUS_PRINT
	Im_B2R_Print_ClockStatus();
#endif

	Im_B2R_On_Hclk( self->pipeNo );
#ifdef IM_B2R_STATUS_PRINT
	Im_B2R_Print_ClockStatus();
#endif

	Im_B2R_Force_Off_Hclk( self->pipeNo );
#ifdef IM_B2R_STATUS_PRINT
	Im_B2R_Print_ClockStatus();
#endif

	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r2_1_8: "
kint32 ct_im_b2r2_1_8( CtImB2r2 *self )
{
	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

#ifdef IM_B2R_STATUS_PRINT
	Im_B2R_Print_ClockStatus();
#endif

	Im_B2R_On_Iclk( self->pipeNo );
#ifdef IM_B2R_STATUS_PRINT
	Im_B2R_Print_ClockStatus();
#endif

	Im_B2R_Off_Iclk( self->pipeNo );

	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r2_1_9: "
kint32 ct_im_b2r2_1_9( CtImB2r2 *self )
{
	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

	Im_B2R_On_Iclk( self->pipeNo );
#ifdef IM_B2R_STATUS_PRINT
	Im_B2R_Print_ClockStatus();
#endif


	Im_B2R_Off_Iclk( self->pipeNo );
#ifdef IM_B2R_STATUS_PRINT
	Im_B2R_Print_ClockStatus();
#endif

	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r2_1_10: "
kint32 ct_im_b2r2_1_10( CtImB2r2 *self )
{
	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

#ifdef IM_B2R_STATUS_PRINT
	Im_B2R_Print_ClockStatus();
#endif

	Im_B2R_On_Iclk( self->pipeNo );
#ifdef IM_B2R_STATUS_PRINT
	Im_B2R_Print_ClockStatus();
#endif

	Im_B2R_On_Iclk( self->pipeNo );
#ifdef IM_B2R_STATUS_PRINT
	Im_B2R_Print_ClockStatus();
#endif

	Im_B2R_On_Iclk( self->pipeNo );
#ifdef IM_B2R_STATUS_PRINT
	Im_B2R_Print_ClockStatus();
#endif

	Im_B2R_Force_Off_Iclk( self->pipeNo );
#ifdef IM_B2R_STATUS_PRINT
	Im_B2R_Print_ClockStatus();
#endif

	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r2_1_11: "
kint32 ct_im_b2r2_1_11( CtImB2r2 *self )
{
	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

#ifdef IM_B2R_STATUS_PRINT
	Im_B2R_Print_ClockStatus();
#endif

	Im_B2R_On_Clk( self->pipeNo );
#ifdef IM_B2R_STATUS_PRINT
	Im_B2R_Print_ClockStatus();
#endif

	Im_B2R_Off_Clk( self->pipeNo );

	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r2_1_12: "
kint32 ct_im_b2r2_1_12( CtImB2r2 *self )
{
	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

	Im_B2R_On_Clk( self->pipeNo );
#ifdef IM_B2R_STATUS_PRINT
	Im_B2R_Print_ClockStatus();
#endif

	Im_B2R_Off_Clk( self->pipeNo );
#ifdef IM_B2R_STATUS_PRINT
	Im_B2R_Print_ClockStatus();
#endif

	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r2_1_13: "
kint32 ct_im_b2r2_1_13( CtImB2r2 *self )
{
	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

#ifdef IM_B2R_STATUS_PRINT
	Im_B2R_Print_ClockStatus();
#endif

	Im_B2R_On_Clk( self->pipeNo );
#ifdef IM_B2R_STATUS_PRINT
	Im_B2R_Print_ClockStatus();
#endif

	Im_B2R_On_Clk( self->pipeNo );
#ifdef IM_B2R_STATUS_PRINT
	Im_B2R_Print_ClockStatus();
#endif

	Im_B2R_On_Clk( self->pipeNo );
#ifdef IM_B2R_STATUS_PRINT
	Im_B2R_Print_ClockStatus();
#endif

	Im_B2R_Force_Off_Clk( self->pipeNo );
#ifdef IM_B2R_STATUS_PRINT
	Im_B2R_Print_ClockStatus();
#endif

	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r2_1_14: "
kint32 ct_im_b2r2_1_14( CtImB2r2 *self )
{
	kuint32				loopcnt;
	T_IM_B2R_CTRL_AXI	b2r_ctrl_axi[] = {
		[0] = {	// max
			.ybr.cache_type = 0xF,
			.ybr.protect_type = 7,
			.ybw[0].cache_type = 0xF,
			.ybw[0].protect_type = 7,
			.ybw[1].cache_type = 0xF,
			.ybw[1].protect_type = 7,
			.ybw[2].cache_type = 0xF,
			.ybw[2].protect_type = 7,
		},
		[1] = {	// min
			.ybr.cache_type = 0,
			.ybr.protect_type = 0,
			.ybw[0].cache_type = 0,
			.ybw[0].protect_type = 0,
			.ybw[1].cache_type = 0,
			.ybw[1].protect_type = 0,
			.ybw[2].cache_type = 0,
			.ybw[2].protect_type = 0,
		},
	};
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

	for( loopcnt = 0; loopcnt < (sizeof(b2r_ctrl_axi) / sizeof(b2r_ctrl_axi[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = Im_B2R_Ctrl_Axi( self->pipeNo, &b2r_ctrl_axi[loopcnt] );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "%d\n", ercd ));
#else
		Im_B2R_Ctrl_Axi( self->pipeNo, &b2r_ctrl_axi[loopcnt] );
#endif

		Im_B2R_On_Pclk( D_IM_B2R_PIPE12 );
		Ddim_Print(( "IO_B2R_P1.YBCH.YBRAXCTL.bit.YBRCACHE   = %u\n", IO_B2R_P1.YBCH.YBRAXCTL.bit.YBRCACHE ));
		Ddim_Print(( "IO_B2R_P1.YBCH.YBRAXCTL.bit.YBRPROT    = %u\n", IO_B2R_P1.YBCH.YBRAXCTL.bit.YBRPROT ));

		Ddim_Print(( "IO_B2R_P1.YBCH.YBWAXCTL.bit.YBWCACHE_0 = %u\n", IO_B2R_P1.YBCH.YBWAXCTL.bit.YBWCACHE_0 ));
		Ddim_Print(( "IO_B2R_P1.YBCH.YBWAXCTL.bit.YBWPROT_0  = %u\n", IO_B2R_P1.YBCH.YBWAXCTL.bit.YBWPROT_0 ));
		Ddim_Print(( "IO_B2R_P1.YBCH.YBWAXCTL.bit.YBWCACHE_1 = %u\n", IO_B2R_P1.YBCH.YBWAXCTL.bit.YBWCACHE_1 ));
		Ddim_Print(( "IO_B2R_P1.YBCH.YBWAXCTL.bit.YBWPROT_1  = %u\n", IO_B2R_P1.YBCH.YBWAXCTL.bit.YBWPROT_1 ));
		Ddim_Print(( "IO_B2R_P1.YBCH.YBWAXCTL.bit.YBWCACHE_2 = %u\n", IO_B2R_P1.YBCH.YBWAXCTL.bit.YBWCACHE_2 ));
		Ddim_Print(( "IO_B2R_P1.YBCH.YBWAXCTL.bit.YBWPROT_2  = %u\n", IO_B2R_P1.YBCH.YBWAXCTL.bit.YBWPROT_2 ));

		Ddim_Print(( "IO_B2R_P2.YBCH.YBRAXCTL.bit.YBRCACHE   = %u\n", IO_B2R_P2.YBCH.YBRAXCTL.bit.YBRCACHE ));
		Ddim_Print(( "IO_B2R_P2.YBCH.YBRAXCTL.bit.YBRPROT    = %u\n", IO_B2R_P2.YBCH.YBRAXCTL.bit.YBRPROT ));

		Ddim_Print(( "IO_B2R_P2.YBCH.YBWAXCTL.bit.YBWCACHE_0 = %u\n", IO_B2R_P2.YBCH.YBWAXCTL.bit.YBWCACHE_0 ));
		Ddim_Print(( "IO_B2R_P2.YBCH.YBWAXCTL.bit.YBWPROT_0  = %u\n", IO_B2R_P2.YBCH.YBWAXCTL.bit.YBWPROT_0 ));
		Ddim_Print(( "IO_B2R_P2.YBCH.YBWAXCTL.bit.YBWCACHE_1 = %u\n", IO_B2R_P2.YBCH.YBWAXCTL.bit.YBWCACHE_1 ));
		Ddim_Print(( "IO_B2R_P2.YBCH.YBWAXCTL.bit.YBWPROT_1  = %u\n", IO_B2R_P2.YBCH.YBWAXCTL.bit.YBWPROT_1 ));
		Ddim_Print(( "IO_B2R_P2.YBCH.YBWAXCTL.bit.YBWCACHE_2 = %u\n", IO_B2R_P2.YBCH.YBWAXCTL.bit.YBWCACHE_2 ));
		Ddim_Print(( "IO_B2R_P2.YBCH.YBWAXCTL.bit.YBWPROT_2  = %u\n", IO_B2R_P2.YBCH.YBWAXCTL.bit.YBWPROT_2 ));
		Im_B2R_Off_Pclk( D_IM_B2R_PIPE12 );
	}

	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r2_1_15: "
kint32 ct_im_b2r2_1_15( CtImB2r2 *self )
{
	T_IM_B2R_AXI_YBR_STAT b2r_axi_read_stat;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));


#ifdef CO_DEBUG_ON_PC
	if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
		IO_B2R_P1.YBCH.YBRAXSTS.bit.YBRRESP = 3;
	}
	if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
		IO_B2R_P2.YBCH.YBRAXSTS.bit.YBRRESP = 3;
	}
#endif // CO_DEBUG_ON_PC
	memset( &b2r_axi_read_stat, '\0', sizeof(b2r_axi_read_stat) );
#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_Get_AxiReadStat( self->pipeNo, &b2r_axi_read_stat );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "%d\n", ercd ));
#else
	Im_B2R_Get_AxiReadStat( self->pipeNo, &b2r_axi_read_stat );
#endif
	Ddim_Print(( "ybr_axi_stat = %u\n", b2r_axi_read_stat.ybr_axi_stat ));

#ifdef CO_DEBUG_ON_PC
	if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
		IO_B2R_P1.YBCH.YBRAXSTS.bit.YBRRESP = 0;
	}
	if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
		IO_B2R_P2.YBCH.YBRAXSTS.bit.YBRRESP = 0;
	}
#endif // CO_DEBUG_ON_PC
	memset( &b2r_axi_read_stat, '\0', sizeof(b2r_axi_read_stat) );
#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_Get_AxiReadStat( self->pipeNo, &b2r_axi_read_stat );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "%d\n", ercd ));
#else
	Im_B2R_Get_AxiReadStat( self->pipeNo, &b2r_axi_read_stat );
#endif
	Ddim_Print(( "ybr_axi_stat = %u\n", b2r_axi_read_stat.ybr_axi_stat ));

	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r2_1_16: "
kint32 ct_im_b2r2_1_16( CtImB2r2 *self )
{
	T_IM_B2R_AXI_YBW_STAT b2r_axi_write_stat;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

#ifdef CO_DEBUG_ON_PC
	if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
		IO_B2R_P1.YBCH.YBWAXSTS.bit.YBBRESP_0 = 3;
		IO_B2R_P1.YBCH.YBWAXSTS.bit.YBBRESP_1 = 3;
		IO_B2R_P1.YBCH.YBWAXSTS.bit.YBBRESP_2 = 3;
	}
	if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
		IO_B2R_P2.YBCH.YBWAXSTS.bit.YBBRESP_0 = 3;
		IO_B2R_P2.YBCH.YBWAXSTS.bit.YBBRESP_1 = 3;
		IO_B2R_P2.YBCH.YBWAXSTS.bit.YBBRESP_2 = 3;
	}
#endif //CO_DEBUG_ON_PC

	memset( &b2r_axi_write_stat, '\0', sizeof(b2r_axi_write_stat) );
#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_Get_AxiWriteStat( self->pipeNo, &b2r_axi_write_stat );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "%d\n", ercd ));
#else
	Im_B2R_Get_AxiWriteStat( self->pipeNo, &b2r_axi_write_stat );
#endif

	Ddim_Print(( "ybw_axi_stat[0] = %u\n", b2r_axi_write_stat.ybw_axi_stat[D_IM_B2R_PORT_0] ));
	Ddim_Print(( "ybw_axi_stat[1] = %u\n", b2r_axi_write_stat.ybw_axi_stat[D_IM_B2R_PORT_1] ));
	Ddim_Print(( "ybw_axi_stat[2] = %u\n", b2r_axi_write_stat.ybw_axi_stat[D_IM_B2R_PORT_2] ));




#ifdef CO_DEBUG_ON_PC
	if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
		IO_B2R_P1.YBCH.YBWAXSTS.bit.YBBRESP_0 = 0;
		IO_B2R_P1.YBCH.YBWAXSTS.bit.YBBRESP_1 = 0;
		IO_B2R_P1.YBCH.YBWAXSTS.bit.YBBRESP_2 = 0;
	}
	if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
		IO_B2R_P2.YBCH.YBWAXSTS.bit.YBBRESP_0 = 0;
		IO_B2R_P2.YBCH.YBWAXSTS.bit.YBBRESP_1 = 0;
		IO_B2R_P2.YBCH.YBWAXSTS.bit.YBBRESP_2 = 0;
	}
#endif //CO_DEBUG_ON_PC

	memset( &b2r_axi_write_stat, '\0', sizeof(b2r_axi_write_stat) );
#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_Get_AxiWriteStat( self->pipeNo, &b2r_axi_write_stat );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "%d\n", ercd ));
#else
	Im_B2R_Get_AxiWriteStat( self->pipeNo, &b2r_axi_write_stat );
#endif

	Ddim_Print(( "ybw_axi_stat[0] = %u\n", b2r_axi_write_stat.ybw_axi_stat[D_IM_B2R_PORT_0] ));
	Ddim_Print(( "ybw_axi_stat[1] = %u\n", b2r_axi_write_stat.ybw_axi_stat[D_IM_B2R_PORT_1] ));
	Ddim_Print(( "ybw_axi_stat[2] = %u\n", b2r_axi_write_stat.ybw_axi_stat[D_IM_B2R_PORT_2] ));

	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r2_1_17: "
kint32 ct_im_b2r2_1_17( CtImB2r2 *self )
{
	T_IM_B2R_AXI_YBW_MODE	b2r_axi_write_mode;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	if( self->pipeNo == D_IM_B2R_PIPE12 ){
		return D_DDIM_OK;
	}

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

	if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
		IO_B2R_P1.YBCH.YBWAXMD.bit.YBWDOS = 1;
		IO_B2R_P1.YBCH.YBWAXMD.bit.YBWBL = 2;
	}
	if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
		IO_B2R_P2.YBCH.YBWAXMD.bit.YBWDOS = 1;
		IO_B2R_P2.YBCH.YBWAXMD.bit.YBWBL = 2;
	}

	memset( &b2r_axi_write_mode, '\0', sizeof(b2r_axi_write_mode) );
#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_Get_AxiWriteMode( self->pipeNo, &b2r_axi_write_mode );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "%d\n", ercd ));
#else
	Im_B2R_Get_AxiWriteMode( self->pipeNo, &b2r_axi_write_mode );
#endif

	Ddim_Print(( "out_sel      = %u\n", b2r_axi_write_mode.out_sel ));
	Ddim_Print(( "burst_length = %u\n", b2r_axi_write_mode.burst_length ));


	if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
		IO_B2R_P1.YBCH.YBWAXMD.bit.YBWDOS = 0;
		IO_B2R_P1.YBCH.YBWAXMD.bit.YBWBL = 0;
	}
	if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
		IO_B2R_P2.YBCH.YBWAXMD.bit.YBWDOS = 0;
		IO_B2R_P2.YBCH.YBWAXMD.bit.YBWBL = 0;
	}

	memset( &b2r_axi_write_mode, '\0', sizeof(b2r_axi_write_mode) );
#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_Get_AxiWriteMode( self->pipeNo, &b2r_axi_write_mode );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "%d\n", ercd ));
#else
	Im_B2R_Get_AxiWriteMode( self->pipeNo, &b2r_axi_write_mode );
#endif

	Ddim_Print(( "out_sel      = %u\n", b2r_axi_write_mode.out_sel ));
	Ddim_Print(( "burst_length = %u\n", b2r_axi_write_mode.burst_length ));

	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r2_1_18: "
kint32 ct_im_b2r2_1_18( CtImB2r2 *self )
{
	kuint32					loopcnt;
	T_IM_B2R_AXI_YBW_MODE	b2r_axi_write_mode[] = {
		[0] = { // max
			.out_sel = 1,
			.burst_length = 2,
		},
		[1] = { // min
			.out_sel = 0,
			.burst_length = 0,
		},
	};
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

	for( loopcnt = 0; loopcnt < (sizeof(b2r_axi_write_mode) / sizeof(b2r_axi_write_mode[0])); loopcnt++ ) {
#ifdef CO_MSG_PRINT_ON
		ercd = Im_B2R_Set_AxiWriteMode( self->pipeNo, &b2r_axi_write_mode[loopcnt] );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "%d\n", ercd ));
#else
		Im_B2R_Set_AxiWriteMode( self->pipeNo, b2r_axi_write_mode[loopcnt] );
#endif

		Im_B2R_On_Pclk( D_IM_B2R_PIPE12 );
		Ddim_Print(( "IO_B2R_P1.YBCH.YBWAXMD.bit.YBWDOS = 0x%x\n", IO_B2R_P1.YBCH.YBWAXMD.bit.YBWDOS ));
		Ddim_Print(( "IO_B2R_P1.YBCH.YBWAXMD.bit.YBWBL  = 0x%x\n", IO_B2R_P1.YBCH.YBWAXMD.bit.YBWBL ));
		Ddim_Print(( "IO_B2R_P2.YBCH.YBWAXMD.bit.YBWDOS = 0x%x\n", IO_B2R_P2.YBCH.YBWAXMD.bit.YBWDOS ));
		Ddim_Print(( "IO_B2R_P2.YBCH.YBWAXMD.bit.YBWBL  = 0x%x\n", IO_B2R_P2.YBCH.YBWAXMD.bit.YBWBL ));
		Im_B2R_Off_Pclk( D_IM_B2R_PIPE12 );
	}

	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r2_1_19: "
kint32 ct_im_b2r2_1_19( CtImB2r2 *self )
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

	for( loopcnt = 0; loopcnt < (sizeof(S_GCT_IM_B2R_CTRL) / sizeof(S_GCT_IM_B2R_CTRL[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = Im_B2R_Ctrl( self->pipeNo, &S_GCT_IM_B2R_CTRL[loopcnt] );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "%d\n", ercd ));
#else
		Im_B2R_Ctrl( self->pipeNo, &S_GCT_IM_B2R_CTRL[loopcnt] );
#endif

		ct_im_b2r1_print_b2r_ctrl_reg();

#ifdef IM_B2R_STATUS_PRINT
		Im_B2R_Print_Status();
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r2_1_20: "
kint32 ct_im_b2r2_1_20( CtImB2r2 *self )
{
	kuint32 loopcnt;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));


	for( loopcnt = 0; loopcnt < (sizeof(S_GCT_IM_B2R_CTRL_SDRAM_IN) / sizeof(S_GCT_IM_B2R_CTRL_SDRAM_IN[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = Im_B2R_Ctrl( self->pipeNo, &gctImB2rCtrlBase );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "%d\n", ercd ));

		ercd = Im_B2R_Ctrl_ModeSDRAMInput( self->pipeNo, &S_GCT_IM_B2R_CTRL_SDRAM_IN[loopcnt] );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "%d\n", ercd ));
#else
		Im_B2R_Ctrl( self->pipeNo, &gctImB2rCtrlBase );
		Im_B2R_Ctrl_ModeSDRAMInput( self->pipeNo, &S_GCT_IM_B2R_CTRL_SDRAM_IN[loopcnt] );
#endif

		ct_im_b2r1_print_b2r_ctrl_modesdraminput_reg();

#ifdef IM_B2R_STATUS_PRINT
		Im_B2R_Print_Status();
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r2_1_21: "
kint32 ct_im_b2r2_1_21( CtImB2r2 *self )
{
	kuint32 loopcnt;
	T_IM_B2R_CTRL_B2B_DIRECT b2r_ctrl_b2b_direct[] = {
		[0] = {	// max
			.even_line_start_timming = 0x1FFF,
			.frame_stop = 1,
		},
		[1] = {	// min
			.even_line_start_timming = 0,
			.frame_stop = 0,
		},
	};
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

	for( loopcnt = 0; loopcnt < (sizeof(b2r_ctrl_b2b_direct) / sizeof(b2r_ctrl_b2b_direct[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = Im_B2R_Ctrl( self->pipeNo, &gctImB2rCtrlBase );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "%d\n", ercd ));

		ercd = Im_B2R_Ctrl_ModeB2BDirect( self->pipeNo, &b2r_ctrl_b2b_direct[loopcnt] );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "%d\n", ercd ));
#else
		Im_B2R_Ctrl( self->pipeNo, &gctImB2rCtrlBase );
		Im_B2R_Ctrl_ModeB2BDirect( self->pipeNo, &b2r_ctrl_b2b_direct[loopcnt] );
#endif

		ct_im_b2r1_print_b2r_ctrl_modeb2bdirect_reg();

#ifdef IM_B2R_STATUS_PRINT
		Im_B2R_Print_Status();
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r2_1_22: "
kint32 ct_im_b2r2_1_22( CtImB2r2 *self )
{
	kuint32 loopcnt;
	T_IM_B2R_INADDR_INFO b2r_in_addr[] = {
		[0] = { // max
			.raw.addr = (void*)0xFFFFFFFF,
		},
		[1] = { // min
			.raw.addr = (void*)0,
		},
		[2] = { // indvisual
			.raw.addr = (void*)D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP,
		},
	};
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));


	for( loopcnt = 0; loopcnt < (sizeof(b2r_in_addr) / sizeof(b2r_in_addr[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = Im_B2R_Ctrl( self->pipeNo, &gctImB2rCtrlBase );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "%d\n", ercd ));

		ercd = Im_B2R_Ctrl_ModeSDRAMInput( self->pipeNo, &gctImB2rCtrlSdramInBase );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "%d\n", ercd ));

		ercd = Im_B2R_Set_InAddr_Info( self->pipeNo, &b2r_in_addr[loopcnt] );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "%d\n", ercd ));
#else
		Im_B2R_Ctrl( self->pipeNo, &gctImB2rCtrlBase );
		Im_B2R_Ctrl_ModeSDRAMInput( self->pipeNo, &gctImB2rCtrlSdramInBase );
		Im_B2R_Set_InAddr_Info( self->pipeNo, &b2r_in_addr[loopcnt] );
#endif

		ct_im_b2r1_print_b2r_ctrl_modesdraminput_reg();

		// im_b2r_calc_ybr_address_sdram_input(), im_b2r_set_ybr_address_sdram_input(), Im_B2R_Set_InAddr_Info()
		Im_B2R_On_Pclk( D_IM_B2R_PIPE12 );
		Ddim_Print(( "IO_B2R_P1.YBR.YBRA = %lx\n", IO_B2R_P1.YBR.YBRA.bit.YBRA ));
		Ddim_Print(( "IO_B2R_P2.YBR.YBRA = %lx\n", IO_B2R_P2.YBR.YBRA.bit.YBRA ));
		Im_B2R_Off_Pclk( D_IM_B2R_PIPE12 );

#ifdef IM_B2R_STATUS_PRINT
		Im_B2R_Print_Status();
#endif
	}

	return D_DDIM_OK;
}


CtImB2r2* ct_im_b2r2_new(void) 
{
    CtImB2r2 *self = k_object_new_with_private(CT_TYPE_IM_B2R2, sizeof(CtImB2r2Private));
    return self;
}
