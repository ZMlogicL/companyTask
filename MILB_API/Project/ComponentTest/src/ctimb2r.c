/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :liduong
*@brief               :CtImB2r类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#include "ctimb2r.h"

// #include "im_b2r.h"
#include "../../ImageMacro/src/imb2r.h"
#include "im_pro.h"
// #include "im_pro_common.h"
#include "../../ImageMacro/src/improcommon.h"

#include "driver_common.h"
// #include "ddim_user_custom.h"
#include "../../../../milb_api_usercustom/src/ddimusercustom.h"
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
// #include "dd_top.h"
#include "../../DeviceDriver/LSITop/src/ddtop.h"
#endif

#include "jdsb2r.h"

#include <stdlib.h>
#include <string.h>

#include "ctimb2r.h"
#include "ctimb2r1.h"
#include "ctimb2r2.h"
#include "ctimb2r3.h"
#include "ctimb2r4.h"
#include "ctimb2r5.h"
#include "ctimb2r6.h"
#include "ctimb2r7.h"
#include "ctimb2r8.h"
#include "ctimb2r9.h"
#include "ctimb2r10.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImB2r, ct_im_b2r);
#define CT_IM_B2R_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtImB2rPrivate,CT_TYPE_IM_B2R))

#ifdef CO_MSG_PRINT_ON
#define D_IM_B2R_RESULT(statement) result = statement
#else
#define D_IM_B2R_RESULT
#endif


/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
#define ct_im_b2r_check_target_pipe_no_1(a)		(((a)+1) & (ImB2r_D_IM_B2R_PIPE1+1))
#define ct_im_b2r_check_target_pipe_no_2(a)		(((a)+1) & (ImB2r_D_IM_B2R_PIPE2+1))


struct _CtImB2rPrivate
{
	kuint32 ctIdx1st;
	kuint32 ctIdx2nd;
	kuint32 ctIdx3rd;
};


ULONG gct_im_b2r_in_addr = 0x54000000;
ULONG gct_im_b2r_out_addr[2] = {
	0x55000000,
	0x56000000,
};

/*
DECLS
*/
static kint32 ctImB2rRun_1( CtImB2r *self, const kuint32 ctNo3rd );
static kint32 ctImB2rRun_2( CtImB2r *self, const kuint32 ctNo3rd );
static kint32 ctImB2rRun_2( CtImB2r *self, const kuint32 ctNo3rd );

static void ct_im_b2r_constructor(CtImB2r *self) 
{
//	CtImB2rPrivate *priv = CT_IM_B2R_GET_PRIVATE(self);
}

static void ct_im_b2r_destructor(CtImB2r *self) 
{
//	CtImB2rPrivate *priv = CT_IM_B2R_GET_PRIVATE(self);
	self = NULL;
}

/*
IMPL//todo
*/

// static kint32 ct_im_b2r_run_1( UCHAR pipeNo, const kuint32 ctNo3rd )
static kint32 ctImB2rRun_1( CtImB2r *self, const kuint32 ctNo3rd )
{	
	CtImB2r2* ctimb2r2 = ct_im_b2r2_new();
	CtImB2r3* ctImB2r3 = ct_im_b2r3_new();
	CtImB2r4* ctImB2r4 = ct_im_b2r4_new();
	CtImB2r5* ctImB2r5 = ct_im_b2r5_new();

	ctimb2r2->pipeNo = self->pipeNo;
	ctImB2r3->pipeNo = self->pipeNo;
	ctImB2r4->pipeNo = self->pipeNo;
	ctImB2r5->pipeNo = self->pipeNo;

	switch( ctNo3rd ) {
		// Test-1-1-1
		case 1:
			return ct_im_b2r2_1_1( ctimb2r2 );

		// Test-1-1-2
		case 2:
			return ct_im_b2r2_1_2( ctimb2r2 );

		// Test-1-1-3
		case 3:
			return ct_im_b2r2_1_3( ctimb2r2 );

		// Test-1-1-4
		case 4:
			return ct_im_b2r2_1_4( ctimb2r2 );

		// Test-1-1-5
		case 5:
			return ct_im_b2r2_1_5( ctimb2r2 );

		// Test-1-1-6
		case 6:
			return ct_im_b2r2_1_6( ctimb2r2 );

		// Test-1-1-7
		case 7:
			return ct_im_b2r2_1_7( ctimb2r2 );

		// Test-1-1-8
		case 8:
			return ct_im_b2r2_1_8( ctimb2r2 );

		// Test-1-1-9
		case 9:
			return ct_im_b2r2_1_9( ctimb2r2 );

		// Test-1-1-10
		case 10:
			return ct_im_b2r2_1_10( ctimb2r2 );

		// Test-1-1-11
		case 11:
			return ct_im_b2r2_1_11( ctimb2r2 );

		// Test-1-1-12
		case 12:
			return ct_im_b2r2_1_12( ctimb2r2 );

		// Test-1-1-13
		case 13:
			return ct_im_b2r2_1_13( ctimb2r2 );

		// Test-1-1-14
		case 14:
			return ct_im_b2r2_1_14( ctimb2r2 );

		// Test-1-1-15
		case 15:
			return ct_im_b2r2_1_15( ctimb2r2 );

		// Test-1-1-16
		case 16:
			return ct_im_b2r2_1_16( ctimb2r2 );

		// Test-1-1-17
		case 17:
			return ct_im_b2r2_1_17( ctimb2r2 );

		// Test-1-1-18
		case 18:
			return ct_im_b2r2_1_18( ctimb2r2 );

		// Test-1-1-19
		case 19:
			return ct_im_b2r2_1_19( ctimb2r2 );

		// Test-1-1-20
		case 20:
			return ct_im_b2r2_1_20( ctimb2r2 );

		// Test-1-1-21
		case 21:
			return ct_im_b2r2_1_21( ctimb2r2 );

		// Test-1-1-22
		case 22:
			return ct_im_b2r2_1_22( ctimb2r2 );

		// Test-1-1-23
		case 23:
			return ct_im_b2r3_1_23( ctImB2r3 );

		// Test-1-1-24
		case 24:
			return ct_im_b2r3_1_24( ctImB2r3 );

		// Test-1-1-25
		case 25:
			return ct_im_b2r3_1_25( ctImB2r3 );

		// Test-1-1-26
		case 26:
			return ct_im_b2r3_1_26( ctImB2r3 );

		// Test-1-1-27
		case 27:
			return ct_im_b2r3_1_27( ctImB2r3 );

		// Test-1-1-28
		case 28:
			return ct_im_b2r3_1_28( ctImB2r3 );

		// Test-1-1-29
		case 29:
			return ct_im_b2r3_1_29( ctImB2r3 );

		// Test-1-1-30
		case 30:
			return ct_im_b2r3_1_30( ctImB2r3 );

		// Test-1-1-31
		case 31:
			return ct_im_b2r3_1_31( ctImB2r3 );

		// Test-1-1-32
		case 32:
			return ct_im_b2r3_1_32( ctImB2r3 );

		// Test-1-1-33
		case 33:
			return ct_im_b2r3_1_33( ctImB2r3 );

		// Test-1-1-34
		case 34:
			return ct_im_b2r3_1_34( ctImB2r3 );

		// Test-1-1-35
		case 35:
			return ct_im_b2r3_1_35( ctImB2r3 );

		// Test-1-1-36
		case 36:
			return ct_im_b2r3_1_36( ctImB2r3 );

		// Test-1-1-37
		case 37:
			return ct_im_b2r3_1_37( ctImB2r3 );

		// Test-1-1-38
		case 38:
			return ct_im_b2r4_1_38( ctImB2r4 );

		// Test-1-1-39
		case 39:
			return ct_im_b2r4_1_39( ctImB2r4 );

		// Test-1-1-40
		case 40:
			return ct_im_b2r4_1_40( ctImB2r4 );

		// Test-1-1-41
		case 41:
			return ct_im_b2r4_1_41( ctImB2r4 );

		// Test-1-1-42
		case 42:
			return ct_im_b2r4_1_42( ctImB2r4 );

		// Test-1-1-43
		case 43:
			return ct_im_b2r4_1_43( ctImB2r4 );

		// Test-1-1-44
		case 44:
			return ct_im_b2r4_1_44( ctImB2r4 );

		// Test-1-1-45
		case 45:
			return ct_im_b2r4_1_45( ctImB2r4 );

		// Test-1-1-46
		case 46:
			return ct_im_b2r5_1_46( ctImB2r5 );

		// Test-1-1-47
		case 47:
			return ct_im_b2r5_1_47( ctImB2r5 );

		// Test-1-1-48
		case 48:
			return ct_im_b2r5_1_48( ctImB2r5 );

		// Test-1-1-49
		case 49:
			return ct_im_b2r5_1_49( ctImB2r5 );

		// Test-1-1-50
		case 50:
			return ct_im_b2r5_1_50( ctImB2r5 );

		// Test-1-1-51
		case 51:
			return ct_im_b2r5_1_51( ctImB2r5 );

		// Test-1-1-52
		case 52:
			return ct_im_b2r5_1_52( ctImB2r5 );

		// Test-1-1-53
		case 53:
			return ct_im_b2r5_1_53( ctImB2r5 );

		// Test-1-1-54
		case 54:
			return ct_im_b2r5_1_54( ctImB2r5 );

		default:
			Ddim_Print(("Error: Unknown command.\n"));
			break;
	}

	k_object_unref(ctimb2r2);
	k_object_unref(ctImB2r3);
	k_object_unref(ctImB2r4);
	k_object_unref(ctImB2r5);

	return D_DDIM_INPUT_PARAM_ERROR;

}


// static kint32 ct_im_b2r_run_2( UCHAR pipeNo, const kuint32 ctNo3rd )
static kint32 ctImB2rRun_2( CtImB2r *self, const kuint32 ctNo3rd )
{
	CtImB2r10* ctImB2r10 = ct_im_b2r10_new();

	ctImB2r10->pipeNo = self->pipeNo;

	switch( ctNo3rd ) {
		// Test-1-2-1
		case 1:
			return ct_im_b2r10_2_1( ctImB2r10 );

		case 2:
			return ct_im_b2r10_2_2( ctImB2r10 );

		default:
			Ddim_Print(("Error: Unknown command.\n"));
			break;
	}

	k_object_unref(ctImB2r10);
	return D_DDIM_INPUT_PARAM_ERROR;

}

// static kint32 ct_im_b2r_run_3( UCHAR pipeNo, const kuint32 ctNo3rd )
static kint32 ctImB2rRun_3( CtImB2r *self, const kuint32 ctNo3rd )
{
	CtImB2r6* ctImB2r6 = ct_im_b2r6_new();
	CtImB2r7* ctImB2r7 = ct_im_b2r7_new();
	CtImB2r8* ctImB2r8 = ct_im_b2r8_new();
	CtImB2r9* ctImB2r9 = ct_im_b2r9_new();

	ctImB2r6->pipeNo = self->pipeNo;
	ctImB2r7->pipeNo = self->pipeNo;
	ctImB2r8->pipeNo = self->pipeNo;
	ctImB2r9->pipeNo = self->pipeNo;

	switch( ctNo3rd ) {
		// Test-1-2-1
		case 1:
			return ct_im_b2r6_3_1( ctImB2r6 );

		case 2:
			return ct_im_b2r6_3_2( ctImB2r6 );

		case 3:
			return ct_im_b2r6_3_3( ctImB2r6 );

		case 4:
			return ct_im_b2r6_3_4( ctImB2r6 );

		case 5:
			return ct_im_b2r6_3_5( ctImB2r6 );

		case 6:
			return ct_im_b2r6_3_6( ctImB2r6 );

		case 7:
			return ct_im_b2r7_3_7( ctImB2r7 );

		case 8:
			return ct_im_b2r7_3_8( ctImB2r7 );

		case 9:
			return ct_im_b2r7_3_9( ctImB2r7 );

		case 10:
			return ct_im_b2r7_3_10( ctImB2r7 );

		case 11:
			return ct_im_b2r7_3_11( ctImB2r7 );

		case 17:
			return ct_im_b2r8_3_17( ctImB2r8 );

		case 18:
			return ct_im_b2r8_3_18( ctImB2r8 );

		case 19:
			return ct_im_b2r8_3_19( ctImB2r8 );

		case 20:
			return ct_im_b2r8_3_20( ctImB2r8 );

		case 21:
			return ct_im_b2r8_3_21( ctImB2r8 );

		case 22:
			return ct_im_b2r8_3_22( ctImB2r8 );

		case 23:
			return ct_im_b2r8_3_23( ctImB2r8 );

		case 24:
			return ct_im_b2r8_3_24( ctImB2r8 );

		case 25:
			return ct_im_b2r8_3_25( ctImB2r8 );

		case 26:
			return ct_im_b2r8_3_26( ctImB2r8 );

		case 27:
			return ct_im_b2r8_3_27( ctImB2r8 );

		case 28:
			return ct_im_b2r9_3_28( ctImB2r9 );

		case 29:
			return ct_im_b2r9_3_29( ctImB2r9 );

		case 30:
			return ct_im_b2r9_3_30( ctImB2r9 );

		case 31:
			return ct_im_b2r9_3_31( ctImB2r9 );

		case 32:
			return ct_im_b2r9_3_32( ctImB2r9 );

		case 33:
			return ct_im_b2r9_3_33( ctImB2r9 );

		case 34:
			return ct_im_b2r9_3_34( ctImB2r9 );

		case 35:
			return ct_im_b2r9_3_35( ctImB2r9 );

		default:
			Ddim_Print(("Error: Unknown command.\n"));
			break;
	}

	k_object_unref(ctImB2r6);
	k_object_unref(ctImB2r7);
	k_object_unref(ctImB2r8);
	k_object_unref(ctImB2r9);
	return D_DDIM_INPUT_PARAM_ERROR;

}

/*
PUBLIC//todo
*/

// void CT_Im_B2R_Run( const kuint32 ctIdx1st, const kuint32 ctIdx2nd, const kuint32 ctIdx3rd )
void ct_im_b2r_run(  CtImB2r *self )
{
	CtImB2rPrivate *priv = CT_IM_B2R_GET_PRIVATE(self);
#ifdef CO_MSG_PRINT_ON
	kint32 result = D_DDIM_INPUT_PARAM_ERROR;
#endif
	static BOOL is_init = 0;
	UCHAR loop_cnt;

	Ddim_Print(( "ct_im_b2r_run( %u, %u, %u ) Begin\n", priv->ctIdx1st, priv->ctIdx2nd, priv->ctIdx3rd ));

	gctImB2rInAddrRaw.raw.addr = (void*)CtImB2r_D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP;
	gctImB2rOutAddrRgb.output_addr[ImB2r_D_IM_B2R_YBW_BANK_0].rgb.addr_R = (void*)CtImB2r_D_IM_B2R_IMG_MEM_OUT_RGB_U8_R_ADDR_TOP;
	gctImB2rOutAddrRgb.output_addr[ImB2r_D_IM_B2R_YBW_BANK_0].rgb.addr_G = (void*)CtImB2r_D_IM_B2R_IMG_MEM_OUT_RGB_U8_G_ADDR_TOP;
	gctImB2rOutAddrRgb.output_addr[ImB2r_D_IM_B2R_YBW_BANK_0].rgb.addr_B = (void*)CtImB2r_D_IM_B2R_IMG_MEM_OUT_RGB_U8_B_ADDR_TOP;


	if( is_init == 0 ) {
#ifdef CO_DEBUG_ON_PC
		memset( (void*)&IO_B2R_P1, '\0', sizeof(IO_B2R_P1) );
		memset( (void*)&IO_B2R_P2, '\0', sizeof(IO_B2R_P2) );
		memset( (void*)&IO_B2R_P3, '\0', sizeof(IO_B2R_P3) );
		memset( (void*)&IO_B2R_TBL_P1, '\0', sizeof(IO_B2R_TBL_P1) );
		memset( (void*)&IO_B2R_TBL_P2, '\0', sizeof(IO_B2R_TBL_P2) );
		memset( (void*)&IO_B2R_TBL_P3, '\0', sizeof(IO_B2R_TBL_P3) );
#endif // CO_DEBUG_ON_PC
		if( !((priv->ctIdx1st == 1) && (priv->ctIdx2nd == 1)) ) {
			Ddim_Print(( "Im_B2R_Init() Begin\n" ));
			Im_B2R_Init( ImB2r_D_IM_B2R_PIPE12 );
			Ddim_Print(( "Im_B2R_Init() End\n" ));
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#ifdef CO_DEBUG_ON_PC
			IO_CHIPTOP.CLKSTOP10.bit.B2R1CK = 0;
			IO_CHIPTOP.CLKSTOP10.bit.B2R1AP = 0;
			IO_CHIPTOP.CLKSTOP10.bit.B2R1AH = 0;
			IO_CHIPTOP.CLKSTOP10.bit.B2R1AX = 0;
			IO_CHIPTOP.CLKSTOP12.bit.B2R2CK = 0;
			IO_CHIPTOP.CLKSTOP12.bit.B2R2AP = 0;
			IO_CHIPTOP.CLKSTOP12.bit.B2R2AH = 0;
			IO_CHIPTOP.CLKSTOP12.bit.B2R2AX = 0;
#endif // CO_DEBUG_ON_PC
#endif
			is_init = 1;
		}
	}

	if(( priv->ctIdx1st == 1 ) || ( priv->ctIdx1st == 2 )){
#ifdef CO_DEBUG_ON_PC
		for( loop_cnt = ImB2r_D_IM_B2R_PIPE1; loop_cnt <= ImB2r_D_IM_B2R_PIPE2; loop_cnt++ ){
#else // CO_DEBUG_ON_PC
		for( loop_cnt = ImB2r_D_IM_B2R_PIPE1; loop_cnt <= ImB2r_D_IM_B2R_PIPE12; loop_cnt++ ){
#endif // CO_DEBUG_ON_PC
			self->pipeNo = loop_cnt;
			switch( priv->ctIdx1st ) {
				case 1:
					D_IM_B2R_RESULT( ctImB2rRun_1( self, priv->ctIdx2nd ) );
					break;
	
				case 2:
					D_IM_B2R_RESULT( ctImB2rRun_2( self, priv->ctIdx2nd ) );
					break;
	
				default:
					Ddim_Print(( "Error: Unknown command.\n" ));
					break;
			}

#ifdef CO_MSG_PRINT_ON
			Ddim_Print(( "result = 0x%x\n", result ));
#endif
			Ddim_Print(( "ct_im_b2r_run( %u, %u, %u) End\n", priv->ctIdx1st, priv->ctIdx2nd, loop_cnt ));
		}
	}
	else{
		self->pipeNo = priv->ctIdx3rd;
		D_IM_B2R_RESULT( ctImB2rRun_3( self, priv->ctIdx2nd ) );
#ifdef CO_MSG_PRINT_ON
		Ddim_Print(( "result = 0x%x\n", result ));
#endif
		Ddim_Print(( "ct_im_b2r_run( %u, %u, %u) End\n", priv->ctIdx1st, priv->ctIdx2nd, priv->ctIdx3rd ));
	}

	return;
}


// for Debug console interface
void ct_im_b2r_main( kint32 argc, CHAR** argv )
{
	if( argc < 3 ) {
		Ddim_Print(( "Ct_Im_B2R_Main: parameter error.\n" ));
		return;
	}
	CtImB2r* ctImB2r = ct_im_b2r_new();

	ct_im_b2r_set_value(ctImB2r,(kuint32)atoi((const char*)argv[1]),(kuint32)atoi((const char*)argv[2]),(kuint32)atoi((const char*)argv[3]));

	// CT_Im_B2R_Run( (kuint32)atoi((const char*)argv[1]),
	// 			   (kuint32)atoi((const char*)argv[2]),
	// 			   (kuint32)atoi((const char*)argv[3]) );
	ct_im_b2r_run(ctImB2r);
	k_object_unref(ctImB2r);
}

void ct_im_b2r_set_value(CtImB2r *self,kuint32 ctIdx1st,kuint32 ctIdx2nd,kuint32 ctIdx3rd)
{
	CtImB2rPrivate *priv = CT_IM_B2R_GET_PRIVATE(self);
	priv->ctIdx1st = ctIdx1st;
	priv->ctIdx2nd = ctIdx2nd;
	priv->ctIdx3rd = ctIdx3rd;

}

CtImB2r* ct_im_b2r_new(void) 
{
    CtImB2r *self = k_object_new_with_private(CT_TYPE_IM_B2R, sizeof(CtImB2rPrivate));
    return self;
}
