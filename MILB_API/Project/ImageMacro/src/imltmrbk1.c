/*
 * imltmrbk1.c
 *
 *  Created on: 2020年9月3日
 *      Author: sns
 */

#include "imltm1.h"

typedef struct _ImLtm1Private ImLtm1Private;
 struct _ImLtm1Private
{
	int a;
};

K_TYPE_DEFINE_DERIVED(ImLtm1, im_ltm1, sizeof(ImLtm1Private),K_TYPE_OBJECT)
#define IM_LTM1_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImLtm1Private, IM_TYPE_LTM1))

static volatile struct io_ltm_ch_rbk* gIM_Io_Ltm_Rbk_Reg_Ptr[ImLtm_D_IM_LTM_PIPE_MAX] = { &(IO_LTM_P1.RBK), &(IO_LTM_P2.RBK), &(IO_LTM_P3.RBK) };

static VOID imLtmRbkManagerInit( UCHAR pipe_no );

static void im_ltm1_constructor(ImLtm1 *self)
{
	//ImLtm1Private *priv = IM_LTM1_GET_PRIVATE(self);
}

static void im_ltm1_destructor(ImLtm1 *self)
{
	//ImLtm1Private *priv = IM_LTM1_GET_PRIVATE(self);
}

static VOID imLtmRbkManagerInit( UCHAR pipe_no )
{
	UCHAR size_coef = 1;

#ifdef CO_PARAM_CHECK
	if( pipe_no > ImLtm_D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "imLtmRbkManagerInit error. pipe_no>ImLtm_D_IM_LTM_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

	if( pipe_no == ImLtm_D_IM_LTM_PIPE12 ){
		size_coef = 2;
		pipe_no = 0;
	}

	// Initialize of State & Handler management information
	memset( (USHORT*)&gIM_LTM_RBK_Mng[pipe_no], 0, sizeof(T_IM_LTM_RBK_MNG) * size_coef );

	return;
}

INT32 im_ltm_rbk_ctrl_rgbtrimming( UCHAR pipe_no, const T_IM_LTM_RBK_RGB_TRIMMING* const rbk_trimming )
{
	USHORT img_top;
	USHORT img_left;
	USHORT img_width;
	USHORT img_lines;

#ifdef CO_PARAM_CHECK
	if( rbk_trimming == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("im_ltm_rbk_ctrl_rgbtrimming error. rbk_trimming = NULL\n"));
		return ImLtm_D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no > ImLtm_D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_rbk_ctrl_rgbtrimming error. pipe_no>ImLtm_D_IM_LTM_PIPE12\n" ));
		return ImLtm_D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RTEN.bit.RTEN = rbk_trimming->trimming_enable;

	// TRMHSTA
	img_left = rbk_trimming->rgb_trim.img_left;
	img_left = im_ltm_rbk_min( img_left, (USHORT)D_IM_LTM_RBK_RTHSTA_MAX );
	img_left = im_ltm_rbk_max( img_left, (USHORT)D_IM_LTM_RBK_RTHSTA_MIN );

	// TRMVSTA
	img_top = rbk_trimming->rgb_trim.img_top;
	img_top = im_ltm_rbk_min( img_top, (USHORT)D_IM_LTM_RBK_RTVSTA_MAX );
	img_top = im_ltm_rbk_max( img_top, (USHORT)D_IM_LTM_RBK_RTVSTA_MIN );

	// TRMHSIZ (2pixels alignment & Advancing)
	img_width = rbk_trimming->rgb_trim.img_width;
	img_width = im_ltm_rbk_min( img_width, (USHORT)D_IM_LTM_RBK_RTHSIZ_MAX );
	img_width = im_ltm_rbk_max( img_width, (USHORT)D_IM_LTM_RBK_RTHSIZ_MIN );

	// TRMVSIZ
	img_lines = rbk_trimming->rgb_trim.img_lines;
	img_lines = im_ltm_rbk_min( img_lines, (USHORT)D_IM_LTM_RBK_RTVSIZ_MAX );
	img_lines = im_ltm_rbk_max( img_lines, (USHORT)D_IM_LTM_RBK_RTVSIZ_MIN );

	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RTHSTA.bit.RTHSTA = img_left;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RTHSIZ.bit.RTHSIZ = img_width;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RTVSTA.bit.RTVSTA = img_top;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RTVSIZ.bit.RTVSIZ = img_lines;
	Im_LTM_Off_Pclk( pipe_no );
	return D_DDIM_OK;
}

VOID im_ltm_rbk_int_handler( UCHAR pipe_no )
{
	UINT32			loopcnt;
	DDIM_USER_ER	ercd;
	ULONG			rint0;
	ULONG			rint1;
	ULONG			rint1_clr;

#ifdef CO_PARAM_CHECK
	if( pipe_no >= ImLtm_D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_rbk_int_handler error. pipe_no>=ImLtm_D_IM_LTM_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_DEBUG_PRINT_IM_LTM_RBK
	Ddim_Print(( "im_ltm_rbk_int_handler begin\n" ));
#endif

#ifdef CO_DEBUG_PRINT_IM_LTM_RBK
	Ddim_Print(( "im_ltm_rbk_int_handler on pclk\n" ));
#endif
	Im_LTM_On_Pclk( pipe_no );

	rint0 = gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RINT0.word;
	rint1 = gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RINT1.word;
	rint1_clr = 0;

#ifdef CO_DEBUG_PRINT_IM_LTM_RBK
	Ddim_Print(( "im_ltm_rbk_int_handler rint0=0x%lx, rint1=0x%lx\n", rint0, rint1 ));
#endif

	// Call of Callback API for interrupt status

	for( loopcnt = 0; loopcnt < (sizeof(gim_ltm_rbk_inttbl[0]) / sizeof(gim_ltm_rbk_inttbl[0][0])); loopcnt++ ) {
		if( ((rint1 & gim_ltm_rbk_inttbl[pipe_no][loopcnt].flg_bitmask) != 0)
		 && ((rint0 & gim_ltm_rbk_inttbl[pipe_no][loopcnt].ena_bitmask) != 0) ) {

#ifdef CO_DEBUG_PRINT_IM_LTM_RBK
			Ddim_Print(( "im_ltm_rbk_int_handler begin 0x%x\n", gim_ltm_rbk_inttbl[pipe_no][loopcnt].flg_bitmask ));
#endif

			gIM_LTM_RBK_Mng[pipe_no].int_status = gim_ltm_rbk_inttbl[pipe_no][loopcnt].int_status;

			rint1_clr |= gim_ltm_rbk_inttbl[pipe_no][loopcnt].flg_bitmask;

			ercd = DDIM_User_Set_Flg( FID_IM_LTM_RBK, gim_ltm_rbk_inttbl[pipe_no][loopcnt].waitflg );
			if( ercd != D_DDIM_USER_E_OK ) {
				Ddim_Print(( "im_ltm_rbk_int_handler: invalid FID. 0x%lx\n", gim_ltm_rbk_inttbl[pipe_no][loopcnt].waitflg ));
			}

			if (gIM_LTM_RBK_Mng[pipe_no].rbk_user_handler) {
				gIM_LTM_RBK_Mng[pipe_no].rbk_user_handler( (UINT32*)&gIM_LTM_RBK_Mng[pipe_no].int_status, gIM_LTM_RBK_Mng[pipe_no].user_param );
			}
		}
	}

	// Clear interrupt
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RINT1.word = rint1_clr;


#ifdef CO_DEBUG_PRINT_IM_LTM_RBK
	Ddim_Print(( "im_ltm_rbk_int_handler rint1=0x%lx\n", gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RINT1.word ));
#endif

#ifdef CO_DEBUG_PRINT_IM_LTM_RBK
	Ddim_Print(( "im_ltm_rbk_int_handler off pclk\n" ));
#endif
	Im_LTM_Off_Pclk( pipe_no );
	Im_LTM_Dsb();

#ifdef CO_DEBUG_PRINT_IM_LTM_RBK
	Ddim_Print(( "im_ltm_rbk_int_handler end\n" ));
#endif
}

INT32 im_ltm_rbk_start( UCHAR pipe_no )
{
	DDIM_USER_ER		ercd;
	INT32				retcd;
	UCHAR				loop_cnt, loop_sta, loop_end;
	DDIM_USER_FLGPTN	flgptn = 0;

#ifdef CO_PARAM_CHECK
	if( pipe_no > ImLtm_D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_rbk_start error. pipe_no>ImLtm_D_IM_LTM_PIPE12\n" ));
		return ImLtm_D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_DEBUG_PRINT_IM_LTM_RBK
	Ddim_Print(( "im_ltm_rbk_start begin\n" ));
#endif

	// P-clock control
#ifdef CO_DEBUG_PRINT_IM_LTM_RBK
	Ddim_Print(( "im_ltm_rbk_start on pclk\n" ));
#endif

	im_ltm_rbk_get_loop_val( pipe_no, &loop_sta, &loop_end );

	Im_LTM_On_Pclk( pipe_no );

	while( 1 ) {	// Pclk enable section
		// Clear of All Interrupt enable & Interrupt status
#ifdef CO_DEBUG_PRINT_IM_LTM_RBK
		Ddim_Print(( "im_ltm_rbk_start begin initialize\n" ));
#endif

#ifdef CO_DEBUG_PRINT_IM_LTM_RBK
		Ddim_Print(( "im_ltm_rbk_start initialize interrupt\n" ));
#endif
		// Initialized Interrupt
		gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RINT1.word = D_IM_LTM_RBK_RINT1_ALL_CLR;

		for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
			gIM_LTM_RBK_Mng[loop_cnt].int_status = 0;
		}

#ifdef CO_DEBUG_PRINT_IM_LTM_RBK
		Ddim_Print(( "im_ltm_rbk_start enable interrupt\n" ));
#endif
		gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RINT0.word = D_IM_LTM_RBK_RINT0_ENABLE;

#ifdef CO_DEBUG_PRINT_IM_LTM_RBK
		Ddim_Print(( "im_ltm_rbk_start on clk\n" ));
#endif
		Im_LTM_On_Aclk( pipe_no );
		Im_LTM_On_RBKClk( pipe_no );

		// Set access enable

		for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
			gIM_Io_Ltm_Rbk_Reg_Ptr[loop_cnt]->RSRAMEN.bit.SRAMAEN = ImLtm_D_IM_LTM_ENABLE_ON;
			gIM_Io_Ltm_Rbk_Reg_Ptr[loop_cnt]->RSRAMEN.bit.RMAENLB1 = (gIM_Io_Ltm_Rbk_Reg_Ptr[loop_cnt]->HVEN.bit.HVEN == ImLtm_D_IM_LTM_ENABLE_OFF) ? ImLtm_D_IM_LTM_ENABLE_OFF : ImLtm_D_IM_LTM_ENABLE_ON;
			if(( gIM_Io_Ltm_Rbk_Reg_Ptr[loop_cnt]->RIOCTL.bit.INSEL == D_IM_LTM_RBK_MODE_SDRAM_INPUT )
			|| ( gIM_Io_Ltm_Rbk_Reg_Ptr[loop_cnt]->RIOCTL.bit.SROMD != D_IM_LTM_RBK_SRO_DIRECT_2 )){
				gIM_Io_Ltm_Rbk_Reg_Ptr[loop_cnt]->RSRAMEN.bit.RMAENLB2 = ImLtm_D_IM_LTM_ENABLE_OFF;
				gIM_Io_Ltm_Rbk_Reg_Ptr[loop_cnt]->RSRAMEN.bit.RMAENSRO = ImLtm_D_IM_LTM_ENABLE_OFF;
			}
			else{
				gIM_Io_Ltm_Rbk_Reg_Ptr[loop_cnt]->RSRAMEN.bit.RMAENLB2 = ImLtm_D_IM_LTM_ENABLE_ON;
				gIM_Io_Ltm_Rbk_Reg_Ptr[loop_cnt]->RSRAMEN.bit.RMAENSRO = ImLtm_D_IM_LTM_ENABLE_ON;
			}
			gIM_Io_Ltm_Rbk_Reg_Ptr[loop_cnt]->RSRAMEN.bit.RMAENWCH = (gIM_Io_Ltm_Rbk_Reg_Ptr[loop_cnt]->RIOCTL.bit.OUTSEL == D_IM_LTM_RBK_OUT_MAP_DIRECT) ? ImLtm_D_IM_LTM_ENABLE_OFF : ImLtm_D_IM_LTM_ENABLE_ON;
			gIM_Io_Ltm_Rbk_Reg_Ptr[loop_cnt]->RSRAMEN.bit.RMAENRCH = (gIM_Io_Ltm_Rbk_Reg_Ptr[loop_cnt]->RIOCTL.bit.INSEL == D_IM_LTM_RBK_MODE_SRO_DIRECT) ? ImLtm_D_IM_LTM_ENABLE_OFF : ImLtm_D_IM_LTM_ENABLE_ON;
		}

		im_ltm_rbk_wait_usec( D_IM_LTM_RBK_SRAM_WAIT_USEC );


#ifdef CO_DEBUG_PRINT_IM_LTM_RBK
		Ddim_Print(( "im_ltm_rbk_start clear event flag\n" ));
#endif

		// Clear of Event Flag
		if( im_ltm_rbk_check_target_pipe_no_1( pipe_no ) ){
			flgptn |= D_IM_LTM_RBK1_INT_FLG_ALL;
		}
		if( im_ltm_rbk_check_target_pipe_no_2( pipe_no ) ){
			flgptn |= D_IM_LTM_RBK2_INT_FLG_ALL;
		}

		ercd = DDIM_User_Clr_Flg( FID_IM_LTM_RBK, ~flgptn );
		if( ercd != D_DDIM_USER_E_OK ) {
			Ddim_Print(( "im_ltm_rbk_start: invalid FID\n" ));
			retcd = ImLtm_D_IM_LTM_SYSTEM_ERROR;
			break;
		}

		gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RTRG.bit.TRG = D_IM_LTM_RBK_TRG_ON;
#ifdef CO_DEBUG_ON_PC
		for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
			gIM_Io_Ltm_Rbk_Reg_Ptr[loop_cnt]->RTRG.bit.TRG = D_IM_LTM_RBK_TRG_BUSY;
		}
#endif
		retcd = D_DDIM_OK;
		break;
	}

#ifdef CO_DEBUG_PRINT_IM_LTM_RBK
	Ddim_Print(( "im_ltm_rbk_start off pclk\n" ));
#endif
	Im_LTM_Off_Pclk( pipe_no );

#ifdef D_IM_LTM_RBK_DEBUG_ON_PC
	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		gIM_Io_Ltm_Rbk_Reg_Ptr[loop_cnt]->RINT1.word = 0;
		gIM_Io_Ltm_Rbk_Reg_Ptr[loop_cnt]->RINT1.bit.__FINFL = 1;
		if( gIM_Io_Ltm_Rbk_Reg_Ptr[loop_cnt]->RLINTLV.bit.LINTLV != 0 ){
			gIM_Io_Ltm_Rbk_Reg_Ptr[loop_cnt]->RINT1.bit.__LCNTFL = 1;
		}
		im_ltm_rbk_int_handler( loop_cnt );
		gIM_Io_Ltm_Rbk_Reg_Ptr[loop_cnt]->RINT1.word = 0;
	}
#endif

	Im_LTM_Dsb();

#ifdef CO_DEBUG_PRINT_IM_LTM_RBK
	Ddim_Print(( "im_ltm_rbk_start end\n" ));
#endif

	return retcd;
}

INT32 im_ltm_rbk_init( UCHAR pipe_no )
{
	ULONG clksel[2] = { 0, 0 };
	UCHAR clkstop[2][3] = {{ 0, 0, 0 }, { 0, 0, 0 }};	// SROxCLK/SROxCLK_2/LTMRBKxCLK

#ifdef CO_PARAM_CHECK
	if( pipe_no > ImLtm_D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_rbk_init error. pipe_no>ImLtm_D_IM_LTM_PIPE12\n" ));
		return ImLtm_D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	if( pipe_no == ImLtm_D_IM_LTM_PIPE1 || pipe_no == ImLtm_D_IM_LTM_PIPE12 ){
		clksel[0] = Dd_Top_Get_CLKSEL5_LTMRBK1CLK();
		switch( clksel[0] ){
			case 8:		// SRO1CLK
			case 16:	// SRO1CLK_2
				if( Dd_Top_Get_CLKSTOP10_SRO1CK() == 0 ){
					clkstop[0][0] = 1;
					Dd_Top_Set_CLKSTOP10_SRO1CK( 1 );
				}
				if( Dd_Top_Get_CLKSTOP10_SRO1CK_2() == 0 ){
					clkstop[0][1] = 1;
					Dd_Top_Set_CLKSTOP10_SRO1CK_2( 1 );
				}
				if( Dd_Top_Get_CLKSTOP10_LTMRBK1CK() == 0 ){
					clkstop[0][2] = 1;
					Dd_Top_Set_CLKSTOP10_LTMRBK1CK( 1 );
				}
				Dd_Top_Set_CLKSEL5_LTMRBK1CLK( 0 );		// 300MHz
				break;
			default:
				if( Dd_Top_Get_CLKSTOP10_LTMRBK1CK() == 0 ){
					clkstop[0][2] = 1;
					Dd_Top_Set_CLKSTOP10_LTMRBK1CK( 1 );
				}
				break;
		}
	}
	if( pipe_no == ImLtm_D_IM_LTM_PIPE2 || pipe_no == ImLtm_D_IM_LTM_PIPE12 ){
		clksel[1] = Dd_Top_Get_CLKSEL7_LTMRBK2CLK();
		switch( clksel[1] ){
			case 8:		// SRO2CLK
			case 16:	// SRO2CLK_2
				if( Dd_Top_Get_CLKSTOP12_SRO2CK() == 0 ){
					clkstop[1][0] = 1;
					Dd_Top_Set_CLKSTOP12_SRO2CK( 1 );
				}
				if( Dd_Top_Get_CLKSTOP12_SRO2CK_2() == 0 ){
					clkstop[1][1] = 1;
					Dd_Top_Set_CLKSTOP12_SRO2CK_2( 1 );
				}
				if( Dd_Top_Get_CLKSTOP12_LTMRBK2CK() == 0 ){
					clkstop[1][2] = 1;
					Dd_Top_Set_CLKSTOP12_LTMRBK2CK( 1 );
				}
				Dd_Top_Set_CLKSEL7_LTMRBK2CLK( 0 );		// 300MHz
				break;
			default:
				if( Dd_Top_Get_CLKSTOP12_LTMRBK2CK() == 0 ){
					clkstop[1][2] = 1;
					Dd_Top_Set_CLKSTOP12_LTMRBK2CK( 1 );
				}
				break;
		}
	}

	imLtmRbkManagerInit( pipe_no );

	Im_LTM_On_Pclk( pipe_no );
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RBKSR.bit.SR = D_IM_LTM_SR_RELEASE;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RSRAMEN.word = D_IM_LTM_RBK_RSRAMEN_ENABLE;
	Im_LTM_Off_Pclk( pipe_no );

	switch( clksel[0] ){
		case 8:		// SRO1CLK
		case 16:	// SRO1CLK_2
			Dd_Top_Set_CLKSEL5_LTMRBK1CLK( clksel[0] );		// original settings
			break;
		default:
			// DO NOTHING.
			break;
	}
	switch( clksel[1] ){
		case 8:		// SRO2CLK
		case 16:	// SRO2CLK_2
			Dd_Top_Set_CLKSEL7_LTMRBK2CLK( clksel[1] );		// original settings
			break;
		default:
			// DO NOTHING.
			break;
	}

	if( clkstop[0][0] ){
		Dd_Top_Set_CLKSTOP10_SRO1CK( 0 );
	}
	if( clkstop[0][1] ){
		Dd_Top_Set_CLKSTOP10_SRO1CK_2( 0 );
	}
	if( clkstop[0][2] ){
		Dd_Top_Set_CLKSTOP10_LTMRBK1CK( 0 );
	}
	if( clkstop[1][0] ){
		Dd_Top_Set_CLKSTOP12_SRO2CK( 0 );
	}
	if( clkstop[1][1] ){
		Dd_Top_Set_CLKSTOP12_SRO2CK_2( 0 );
	}
	if( clkstop[1][2] ){
		Dd_Top_Set_CLKSTOP12_LTMRBK2CK( 0 );
	}

	Im_LTM_Dsb();

	return D_DDIM_OK;
}

ImLtm1 *im_ltm1_new(void)
{
	ImLtm1* self = k_object_new(IM_TYPE_LTM1);
	return self;
}


