/*
*
*@Copyright (C) 2010-2020 贵阳高新网用软件有限公司
*@date : 2020-09-03
*@author : 杨文
*@brief : CtImFpt
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimfpt.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImFpt, ct_im_fpt)
#define CT_IM_FPT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImFptPrivate, CT_TYPE_IM_FPT))


struct _CtImFptPrivate
{
	int a;
};


/**
 * IMPL
 */
static void ct_im_fpt_constructor(CtImFpt *self)
{
	CtImFptPrivate *priv = CT_IM_FPT_GET_PRIVATE(self);

	priv->a = 0;
}

static void ct_im_fpt_destructor(CtImFpt *self)
{
	CtImFptPrivate *priv = CT_IM_FPT_GET_PRIVATE(self);

	priv->a = 0;
}


/**
 * PUBLIC
 */
VOID ct_im_fpt_handler( UINT32 result, UCHAR ch )
{
	if( ((result) & ImFptCommon_D_IM_FPT_INTERRUPT_COMPLETE) != 0 ) {
		Ddim_Print(( "FPT%d end.\n", ch ));
	}
	if( ((result) & ImFptCommon_D_IM_FPT_INTERRUPT_AXI_ERR) != 0 ) {
		Ddim_Print(( "FPT%d AXI error.\n", ch ));
	}
	if( ((result) & ImFptCommon_D_IM_FPT_INTERRUPT_PARAM_ERR) != 0 ) {
		Ddim_Print(( "FPT%d param setting error.\n", ch ));
	}
}

VOID ct_im_fpt_on_pclk( UCHAR ch )
{
#ifdef CO_ACT_PCLOCK
	if( ch == 0 ) {
		Dd_Top_Set_CLKSTOP4_FPT0AP( 0 );
	}
	else{
		Dd_Top_Set_CLKSTOP4_FPT1AP( 0 );
	}
#endif
}

VOID ct_im_fpt_off_pclk( UCHAR ch )
{
#ifdef CO_ACT_PCLOCK
	if( ch == 0 ) {
		Dd_Top_Set_CLKSTOP4_FPT0AP( 1 );
	}
	else{
		Dd_Top_Set_CLKSTOP4_FPT1AP( 1 );
	}
#endif
}

VOID ct_im_fpt_on_hclk( UCHAR ch )
{
#ifdef CO_ACT_HCLOCK
	if( ch == 0 ) {
		Dd_Top_Set_CLKSTOP4_FPT0AH( 0 );
	}
	else{
		Dd_Top_Set_CLKSTOP4_FPT1AH( 0 );
	}
#endif
}

VOID ct_im_fpt_off_hclk( UCHAR ch )
{
#ifdef CO_ACT_HCLOCK
	if( ch == 0 ) {
		Dd_Top_Set_CLKSTOP4_FPT0AH( 1 );
	}
	else{
		Dd_Top_Set_CLKSTOP4_FPT1AH( 1 );
	}
#endif
}

VOID ct_im_fpt_print_mode0_reg( UCHAR ch )
{
	ct_im_fpt_on_pclk( ch );
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_FPT[%d].FPTCTL2   = 0x%lx\n", ch, IO_FPT[ch].FPTCTL2.word   ));
	Ddim_Print(( "IO_FPT[%d].FPTCTL3   = 0x%lx\n", ch, IO_FPT[ch].FPTCTL3.word   ));
	Ddim_Print(( "IO_FPT[%d].FPTFQCTL0 = 0x%lx\n", ch, IO_FPT[ch].FPTFQCTL0.word ));
	Ddim_Print(( "IO_FPT[%d].FPTFQCTL1 = 0x%lx\n", ch, IO_FPT[ch].FPTFQCTL1.word ));
	Ddim_Print(( "IO_FPT[%d].FPTFQCTL2 = 0x%lx\n", ch, IO_FPT[ch].FPTFQCTL2.word ));
	Ddim_Print(( "IO_FPT[%d].FPTFQCTL3 = 0x%lx\n", ch, IO_FPT[ch].FPTFQCTL3.word ));
	Ddim_Print(( "IO_FPT[%d].FPTFQCTL4 = 0x%lx\n", ch, IO_FPT[ch].FPTFQCTL4.word ));
	Ddim_Print(( "IO_FPT[%d].FPTFQCTL5 = 0x%lx\n", ch, IO_FPT[ch].FPTFQCTL5.word ));
	Ddim_Print(( "IO_FPT[%d].FPTFQCTL8 = 0x%lx\n", ch, IO_FPT[ch].FPTFQCTL8.word ));
	Ddim_Print(( "IO_FPT[%d].FPTFQCTL9 = 0x%lx\n", ch, IO_FPT[ch].FPTFQCTL9.word ));
	ct_im_fpt_off_pclk( ch );
}

VOID ct_im_fpt_print_mode1_reg( UCHAR ch )
{
	ct_im_fpt_on_pclk( ch );
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_FPT[%d].FPTCTL2   = 0x%lx\n", ch, IO_FPT[ch].FPTCTL2.word   ));
	Ddim_Print(( "IO_FPT[%d].FPTCTL3   = 0x%lx\n", ch, IO_FPT[ch].FPTCTL3.word   ));
	Ddim_Print(( "IO_FPT[%d].FPTFQCTL0 = 0x%lx\n", ch, IO_FPT[ch].FPTFQCTL0.word ));
	Ddim_Print(( "IO_FPT[%d].FPTFQCTL1 = 0x%lx\n", ch, IO_FPT[ch].FPTFQCTL1.word ));
	Ddim_Print(( "IO_FPT[%d].FPTFQCTL2 = 0x%lx\n", ch, IO_FPT[ch].FPTFQCTL2.word ));
	Ddim_Print(( "IO_FPT[%d].FPTFQCTL3 = 0x%lx\n", ch, IO_FPT[ch].FPTFQCTL3.word ));
	Ddim_Print(( "IO_FPT[%d].FPTFQCTL6 = 0x%lx\n", ch, IO_FPT[ch].FPTFQCTL6.word ));
	Ddim_Print(( "IO_FPT[%d].FPTFQCTL7 = 0x%lx\n", ch, IO_FPT[ch].FPTFQCTL7.word ));
	Ddim_Print(( "IO_FPT[%d].FPTFQCTL9 = 0x%lx\n", ch, IO_FPT[ch].FPTFQCTL9.word ));
	ct_im_fpt_off_pclk( ch );
}

VOID ct_im_fpt_print_mode2_reg( UCHAR ch )
{
	ct_im_fpt_on_pclk( ch );
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_FPT[%d].FPTCTL2    = 0x%lx\n", ch, IO_FPT[ch].FPTCTL2.word    ));
	Ddim_Print(( "IO_FPT[%d].FPTCTL3    = 0x%lx\n", ch, IO_FPT[ch].FPTCTL3.word    ));
	Ddim_Print(( "IO_FPT[%d].FPTFTCTL0  = 0x%lx\n", ch, IO_FPT[ch].FPTFTCTL0.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFTCTL1  = 0x%lx\n", ch, IO_FPT[ch].FPTFTCTL1.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFTCTL2  = 0x%lx\n", ch, IO_FPT[ch].FPTFTCTL2.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFTCTL3  = 0x%lx\n", ch, IO_FPT[ch].FPTFTCTL3.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFTCTL4  = 0x%lx\n", ch, IO_FPT[ch].FPTFTCTL4.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFTCTL5  = 0x%lx\n", ch, IO_FPT[ch].FPTFTCTL5.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFTCTL6  = 0x%lx\n", ch, IO_FPT[ch].FPTFTCTL6.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFTCTL7  = 0x%lx\n", ch, IO_FPT[ch].FPTFTCTL7.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFTCTL8  = 0x%lx\n", ch, IO_FPT[ch].FPTFTCTL8.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFTCTL9  = 0x%lx\n", ch, IO_FPT[ch].FPTFTCTL9.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFTCTL10 = 0x%lx\n", ch, IO_FPT[ch].FPTFTCTL10.word ));
	ct_im_fpt_off_pclk( ch );
}

VOID ct_im_fpt_print_mode3_reg( UCHAR ch )
{
	ct_im_fpt_on_pclk( ch );
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_FPT[%d].FPTCTL2    = 0x%lx\n", ch, IO_FPT[ch].FPTCTL2.word    ));
	Ddim_Print(( "IO_FPT[%d].FPTCTL3    = 0x%lx\n", ch, IO_FPT[ch].FPTCTL3.word    ));
	Ddim_Print(( "IO_FPT[%d].FPTFQCTL1  = 0x%lx\n", ch, IO_FPT[ch].FPTFQCTL1.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFQCTL2  = 0x%lx\n", ch, IO_FPT[ch].FPTFQCTL2.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFQCTL7  = 0x%lx\n", ch, IO_FPT[ch].FPTFQCTL7.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFTCTL0  = 0x%lx\n", ch, IO_FPT[ch].FPTFTCTL0.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFTCTL1  = 0x%lx\n", ch, IO_FPT[ch].FPTFTCTL1.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFTCTL2  = 0x%lx\n", ch, IO_FPT[ch].FPTFTCTL2.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFTCTL3  = 0x%lx\n", ch, IO_FPT[ch].FPTFTCTL3.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFTCTL4  = 0x%lx\n", ch, IO_FPT[ch].FPTFTCTL4.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFTCTL5  = 0x%lx\n", ch, IO_FPT[ch].FPTFTCTL5.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFTCTL6  = 0x%lx\n", ch, IO_FPT[ch].FPTFTCTL6.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFTCTL7  = 0x%lx\n", ch, IO_FPT[ch].FPTFTCTL7.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFTCTL8  = 0x%lx\n", ch, IO_FPT[ch].FPTFTCTL8.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFTCTL9  = 0x%lx\n", ch, IO_FPT[ch].FPTFTCTL9.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFTCTL10 = 0x%lx\n", ch, IO_FPT[ch].FPTFTCTL10.word ));
	ct_im_fpt_off_pclk( ch );
}

VOID ct_im_fpt_print_all_reg( UCHAR ch )
{
	USHORT loop;

	ct_im_fpt_on_pclk( ch );
	Ddim_Print(( "APB\n" ));
	Ddim_Print(( "IO_FPT[%d].FPTCTL0    = 0x%lx\n", ch, IO_FPT[ch].FPTCTL0.word    ));
	Ddim_Print(( "IO_FPT[%d].FPTCTL1    = 0x%lx\n", ch, IO_FPT[ch].FPTCTL1.word    ));
	Ddim_Print(( "IO_FPT[%d].FPTCTL2    = 0x%lx\n", ch, IO_FPT[ch].FPTCTL2.word    ));
	Ddim_Print(( "IO_FPT[%d].FPTFQCTL0  = 0x%lx\n", ch, IO_FPT[ch].FPTFQCTL0.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFQCTL1  = 0x%lx\n", ch, IO_FPT[ch].FPTFQCTL1.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFQCTL2  = 0x%lx\n", ch, IO_FPT[ch].FPTFQCTL2.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFQCTL3  = 0x%lx\n", ch, IO_FPT[ch].FPTFQCTL3.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFQCTL4  = 0x%lx\n", ch, IO_FPT[ch].FPTFQCTL4.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFQCTL5  = 0x%lx\n", ch, IO_FPT[ch].FPTFQCTL5.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFQCTL6  = 0x%lx\n", ch, IO_FPT[ch].FPTFQCTL6.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFQCTL7  = 0x%lx\n", ch, IO_FPT[ch].FPTFQCTL7.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFQCTL8  = 0x%lx\n", ch, IO_FPT[ch].FPTFQCTL8.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFQCTL9  = 0x%lx\n", ch, IO_FPT[ch].FPTFQCTL9.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFTCTL0  = 0x%lx\n", ch, IO_FPT[ch].FPTFTCTL0.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFTCTL1  = 0x%lx\n", ch, IO_FPT[ch].FPTFTCTL1.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFTCTL2  = 0x%lx\n", ch, IO_FPT[ch].FPTFTCTL2.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFTCTL3  = 0x%lx\n", ch, IO_FPT[ch].FPTFTCTL3.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFTCTL4  = 0x%lx\n", ch, IO_FPT[ch].FPTFTCTL4.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFTCTL5  = 0x%lx\n", ch, IO_FPT[ch].FPTFTCTL5.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFTCTL6  = 0x%lx\n", ch, IO_FPT[ch].FPTFTCTL6.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFTCTL7  = 0x%lx\n", ch, IO_FPT[ch].FPTFTCTL7.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFTCTL8  = 0x%lx\n", ch, IO_FPT[ch].FPTFTCTL8.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFTCTL9  = 0x%lx\n", ch, IO_FPT[ch].FPTFTCTL9.word  ));
	Ddim_Print(( "IO_FPT[%d].FPTFTCTL10 = 0x%lx\n", ch, IO_FPT[ch].FPTFTCTL10.word ));
	Ddim_Print(( "IO_FPT[%d].FPTINTE0   = 0x%lx\n", ch, IO_FPT[ch].FPTINTE0.word   ));
	Ddim_Print(( "IO_FPT[%d].FPTINTF0   = 0x%lx\n", ch, IO_FPT[ch].FPTINTF0.word   ));
	Ddim_Print(( "IO_FPT[%d].FPTAXICTL0 = 0x%lx\n", ch, IO_FPT[ch].FPTAXICTL0.word ));
	Ddim_Print(( "IO_FPT[%d].FPTAXIERR0 = 0x%lx\n", ch, IO_FPT[ch].FPTAXIERR0.word ));
	Ddim_Print(( "IO_FPT[%d].FPTCTL3    = 0x%lx\n", ch, IO_FPT[ch].FPTCTL3.word    ));
	Ddim_Print(( "IO_FPT[%d].FPTCTL4    = 0x%lx\n", ch, IO_FPT[ch].FPTCTL4.word    ));
	Ddim_Print(( "IO_FPT[%d].FPTCTL5    = 0x%lx\n", ch, IO_FPT[ch].FPTCTL5.word    ));

	ct_im_fpt_on_hclk( ch );
	Im_FPT_Open( ch, 100 );
	Ddim_Print(( "AHB\n" ));
	for( loop = 0; loop < 256 / 4; loop++ ) {
		Ddim_Print(( "IO_FPT_AHB[%d].FPTLUT0[%d] = 0x%lx\n", ch, loop, IO_FPT_AHB[ch].FPTLUT0.word[loop] ));
	}
	for( loop = 0; loop < 256 / 4; loop++ ) {
		Ddim_Print(( "IO_FPT_AHB[%d].FPTLUT1[%d] = 0x%lx\n", ch, loop, IO_FPT_AHB[ch].FPTLUT1.word[loop] ));
	}
	for( loop = 0; loop < 512 / 4; loop++ ) {
		Ddim_Print(( "IO_FPT_AHB[%d].FPTREG0[%d] = 0x%lx\n", ch, loop, IO_FPT_AHB[ch].FPTREG0.word[loop] ));
	}
	for( loop = 0; loop < 512 / 4; loop++ ) {
		Ddim_Print(( "IO_FPT_AHB[%d].FPTREG1[%d] = 0x%lx\n", ch, loop, IO_FPT_AHB[ch].FPTREG1.word[loop] ));
	}
	Im_FPT_Close( ch );
	ct_im_fpt_off_hclk( ch );
	ct_im_fpt_off_pclk( ch );
}

VOID ct_im_fpt_run( const UINT32 ct_idx_1st, const UINT32 ct_idx_2nd, const UINT32 ct_idx_3rd )
{
#ifdef CO_MSG_PRINT_ON
	INT32 result = D_DDIM_INPUT_PARAM_ERROR;
#endif
	static BOOL is_init = 0;
	UCHAR loop_cnt;
	INT32 ercd;

	Ddim_Print(( "ct_im_fpt_run( %u, %u, %u ) Begin\n", ct_idx_1st, ct_idx_2nd, ct_idx_3rd ));

	if( is_init == 0 ) {
#ifdef CO_DEBUG_ON_PC
		memset( (VOID*)&IO_FPT[0], '\0', sizeof(IO_FPT) );
		memset( (VOID*)&IO_FPT_AHB[0], '\0', sizeof(IO_FPT_AHB) );
		IO_FPT[0].FPTCTL1.word = 2;
		IO_FPT[1].FPTCTL1.word = 2;
#endif // CO_DEBUG_ON_PC
		if( !((ct_idx_1st == 1) && (ct_idx_2nd == 1)) ) {
			Ddim_Print(( "Im_FPT_Init() Begin\n" ));
			ercd = Im_FPT_Init( 0 );
			if( ercd != D_IM_FPT_RETVAL_OK ) {
				Ddim_Print(( "Im_FPT_Init(0) error\n" ));
			}
			ercd = Im_FPT_Init( 1 );
			if( ercd != D_IM_FPT_RETVAL_OK ) {
				Ddim_Print(( "Im_FPT_Init(1) error\n" ));
			}
			Ddim_Print(( "Im_FPT_Init() End\n" ));
			is_init = 1;
		}
	}

	if( ct_idx_1st != 4 ) {
		for( loop_cnt = 0; loop_cnt <= 1; loop_cnt++ ) {
			switch( ct_idx_1st ) {
				case 1:
					CtImFpt_D_IM_FPT_RESULT( ct_im_fpt1_run_1( loop_cnt, ct_idx_2nd ) );
					break;

				case 2:
					CtImFpt_D_IM_FPT_RESULT( ct_im_fpt2_run_2( loop_cnt, ct_idx_2nd ) );
					break;

				case 3:
					CtImFpt_D_IM_FPT_RESULT( ct_im_fpt2_run_3( loop_cnt, ct_idx_2nd ) );
					break;

				default:
					Ddim_Print(( "Error: Unknown command.\n" ));
					break;
			}

#ifdef CO_MSG_PRINT_ON
			Ddim_Print(( "result = %d\n", result ));
#endif
			Ddim_Print(( "ct_im_fpt_run( %u, %u, %u) End\n", ct_idx_1st, ct_idx_2nd, loop_cnt ));
		}
	}
	else{
		CtImFpt_D_IM_FPT_RESULT( ct_im_fpt3_run_4( ct_idx_3rd, ct_idx_2nd ) );

#ifdef CO_MSG_PRINT_ON
		Ddim_Print(( "result = %d\n", result ));
#endif
		Ddim_Print(( "ct_im_fpt_run( %u, %u, %u) End\n", ct_idx_1st, ct_idx_2nd, ct_idx_3rd ));
	}

	return;
}

// for Debug console interface
VOID ct_im_fpt_main( INT32 argc, CHAR** argv )
{
	if( argc < 3 ) {
		Ddim_Print(( "ct_im_fpt_main: parameter error.\n" ));
		return;
	}

	ct_im_fpt_run( (UINT32)atoi((const char*)argv[1]),
				   (UINT32)atoi((const char*)argv[2]),
				   (UINT32)atoi((const char*)argv[3]) );
}

CtImFpt* ct_im_fpt_new(void)
{
	CtImFpt* self = k_object_new_with_private(CT_TYPE_IM_FPT, sizeof(CtImFptPrivate));

	return self;
}