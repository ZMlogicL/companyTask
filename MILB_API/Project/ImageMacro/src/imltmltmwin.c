/*
*@Copyright (C) 2010-2020贵阳高新网用软件有限公司
*@date                :2020-9-2
*@author           :sunhongyu
*@brief                :imltmmapevent类
*@rely                  :
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#include "im_ltm.h"
#include <string.h>
#include "dd_arm.h"
#include "jdsltm.h"
#include "imltmltmutlis.h"
#include "imltmltmwin.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImLtmLtmWin, im_ltm_ltm_win);
#define IM_LTM_LTM_WIN_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImLtmLtmWinPrivate, IM_TYPE_LTM_LTM_WIN))

struct _ImLtmLtmWinPrivate
{
	int a;
};

/*
DECLS
*/
static VOID imLtmLtmManagerInit( UCHAR pipe_no );

static void im_ltm_ltm_win_constructor(ImLtmLtmWin *self)
{
//	ImLtmLtmWinPrivate *priv = IM_LTM_LTM_WIN_GET_PRIVATE(self);
}

static void im_ltm_ltm_win_destructor(ImLtmLtmWin *self)
{
//	ImLtmLtmWinPrivate *priv = IM_LTM_LTM_WIN_GET_PRIVATE(self);
}

/*
IMPL
*/
static VOID imLtmLtmManagerInit( UCHAR pipe_no )
{
	ImLtmLtmUtlis*imLtmLtmUtlis=im_ltm_ltm_utlis_get( );

	UCHAR size_coef = 1;

#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "imLtmLtmManagerInit error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

	if( pipe_no == D_IM_LTM_PIPE12 ){
		size_coef = 2;
		pipe_no = 0;
	}

	// Initialize of State & Handler management information
	memset( (USHORT*)&im_ltm_ltm_utlis_get_gIM_LTM_LTM_Mng(imLtmLtmUtlis,pipe_no), 0, sizeof(TImLtmLtmMng) * size_coef );

	return;
}

/*
PUBLIC
*/
INT32 Im_LTM_LTM_Init( UCHAR pipe_no )
{
	ImLtmLtmUtlis*imLtmLtmUtlis=im_ltm_ltm_utlis_get( );

	ULONG clksel[2] = { 0, 0 };
	UCHAR clkstop[2][5] = {{ 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }};	// SROxCLK/SROxCLK_2/B2BxCLK/B2RxCLK/LTMRBKxCLK

#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_LTM_Init error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	if( pipe_no == D_IM_LTM_PIPE1 || pipe_no == D_IM_LTM_PIPE12 ){
		clksel[0] = Dd_Top_Get_CLKSEL4_LTM1CLK();
		switch( clksel[0] ){
			case 8:		// SRO1CLK
			case 16:	// SRO1CLK_2
			case 24:	// B2B1CLK
			case 32:	// B2R1CLK
				if( Dd_Top_Get_CLKSTOP10_SRO1CK() == 0 ){
					clkstop[0][0] = 1;
					Dd_Top_Set_CLKSTOP10_SRO1CK( 1 );
				}
				if( Dd_Top_Get_CLKSTOP10_SRO1CK_2() == 0 ){
					clkstop[0][1] = 1;
					Dd_Top_Set_CLKSTOP10_SRO1CK_2( 1 );
				}
				if( Dd_Top_Get_CLKSTOP10_B2B1CK() == 0 ){
					clkstop[0][2] = 1;
					Dd_Top_Set_CLKSTOP10_B2B1CK( 1 );
				}
				if( Dd_Top_Get_CLKSTOP10_B2R1CK() == 0 ){
					clkstop[0][3] = 1;
					Dd_Top_Set_CLKSTOP10_B2R1CK( 1 );
				}
				if( Dd_Top_Get_CLKSTOP11_LTM1CK() == 0 ){
					clkstop[0][4] = 1;
					Dd_Top_Set_CLKSTOP11_LTM1CK( 1 );
				}
				Dd_Top_Set_CLKSEL4_LTM1CLK( 0 );		// 300MHz
				break;
			default:
				if( Dd_Top_Get_CLKSTOP11_LTM1CK() == 0 ){
					clkstop[0][4] = 1;
					Dd_Top_Set_CLKSTOP11_LTM1CK( 1 );
				}
				break;
		}
	}
	if( pipe_no == D_IM_LTM_PIPE2 || pipe_no == D_IM_LTM_PIPE12 ){
		clksel[1] = Dd_Top_Get_CLKSEL6_LTM2CLK();
		switch( clksel[1] ){
			case 8:		// SRO1CLK
			case 16:	// SRO1CLK_2
			case 24:	// B2B1CLK
			case 32:	// B2R1CLK
				if( Dd_Top_Get_CLKSTOP12_SRO2CK() == 0 ){
					clkstop[1][0] = 1;
					Dd_Top_Set_CLKSTOP12_SRO2CK( 1 );
				}
				if( Dd_Top_Get_CLKSTOP12_SRO2CK_2() == 0 ){
					clkstop[1][1] = 1;
					Dd_Top_Set_CLKSTOP12_SRO2CK_2( 1 );
				}
				if( Dd_Top_Get_CLKSTOP12_B2B2CK() == 0 ){
					clkstop[1][2] = 1;
					Dd_Top_Set_CLKSTOP12_B2B2CK( 1 );
				}
				if( Dd_Top_Get_CLKSTOP12_B2R2CK() == 0 ){
					clkstop[1][3] = 1;
					Dd_Top_Set_CLKSTOP12_B2R2CK( 1 );
				}
				if( Dd_Top_Get_CLKSTOP13_LTM2CK() == 0 ){
					clkstop[1][4] = 1;
					Dd_Top_Set_CLKSTOP13_LTM2CK( 1 );
				}
				Dd_Top_Set_CLKSEL6_LTM2CLK( 0 );		// 300MHz
				break;
			default:
				if( Dd_Top_Get_CLKSTOP13_LTM2CK() == 0 ){
					clkstop[1][4] = 1;
					Dd_Top_Set_CLKSTOP13_LTM2CK( 1 );
				}
				break;
		}
	}

	imLtmLtmManagerInit( pipe_no );

	Im_LTM_On_Pclk( pipe_no );
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LTMSR.bit.SR = ImLtmLtmUtlis_D_IM_LTM_SR_RELEASE;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LSRAMEN.word = ImLtmLtmUtlis_D_IM_LTM_LTM_LSRAMEN_ENABLE;
	Im_LTM_Off_Pclk( pipe_no );

	switch( clksel[0] ){
		case 8:		// SRO1CLK
		case 16:	// SRO1CLK_2
		case 24:	// B2B1CLK
		case 32:	// B2R1CLK
			Dd_Top_Set_CLKSEL4_LTM1CLK( clksel[0] );		// original settings
			break;
		default:
			// DO NOTHING.
			break;
	}
	switch( clksel[1] ){
		case 8:		// SRO1CLK
		case 16:	// SRO1CLK_2
		case 24:	// B2B1CLK
		case 32:	// B2R1CLK
			Dd_Top_Set_CLKSEL6_LTM2CLK( clksel[1] );		// original settings
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
		Dd_Top_Set_CLKSTOP10_B2B1CK( 0 );
	}
	if( clkstop[0][3] ){
		Dd_Top_Set_CLKSTOP10_B2R1CK( 0 );
	}
	if( clkstop[0][4] ){
		Dd_Top_Set_CLKSTOP11_LTM1CK( 0 );
	}
	if( clkstop[1][0] ){
		Dd_Top_Set_CLKSTOP12_SRO2CK( 0 );
	}
	if( clkstop[1][1] ){
		Dd_Top_Set_CLKSTOP12_SRO2CK_2( 0 );
	}
	if( clkstop[1][2] ){
		Dd_Top_Set_CLKSTOP12_B2B2CK( 0 );
	}
	if( clkstop[1][3] ){
		Dd_Top_Set_CLKSTOP12_B2R2CK( 0 );
	}
	if( clkstop[1][4] ){
		Dd_Top_Set_CLKSTOP13_LTM2CK( 0 );
	}

	ImLtmLtmUtlis_IM_LTM_DSB();

	return D_DDIM_OK;
}

/* LTM_LTM SW reset
 */
INT32 Im_LTM_LTM_SW_Reset( UCHAR pipe_no )
{
	ImLtmLtmUtlis*imLtmLtmUtlis=im_ltm_ltm_utlis_get( );

	UCHAR	loop_cnt, loop_sta, loop_end;

#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_LTM_SW_Reset error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_ltm_ltm_get_loop_val( pipe_no, &loop_sta, &loop_end );

	Im_LTM_On_Pclk( pipe_no );
	Im_LTM_On_Clk( pipe_no );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		if( im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,loop_cnt) ->LTRG.bit.TRG == ImLtmLtmUtlis_D_IM_LTM_LTM_TRG_BUSY ){
			return D_IM_LTM_MACRO_BUSY;
		}
	}
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LTMSR.bit.SR = ImLtmLtmUtlis_D_IM_LTM_SR_RESET;

	Im_LTM_Off_Clk( pipe_no );
	Im_LTM_Off_Pclk( pipe_no );

	return D_DDIM_OK;
}

/* set AXI bus I/F Control
 */
INT32 Im_LTM_LTM_Ctrl_Axi( UCHAR pipe_no, const T_IM_LTM_LTM_CTRL_AXI* const ctrl_axi )
{
	ImLtmLtmUtlis*imLtmLtmUtlis=im_ltm_ltm_utlis_get( );

#ifdef CO_PARAM_CHECK
	// check on input pointer
	if( ctrl_axi == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_LTM_LTM_Ctrl_Axi error. ctrl_axi = NULL\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_LTM_Ctrl_Axi error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );

	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXICTLR1.bit.ARCACHE_R  = ctrl_axi->rch_rgb[D_IM_LTM_PORT_R].cache_type;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXICTLR1.bit.ARPROT_R   = ctrl_axi->rch_rgb[D_IM_LTM_PORT_R].protect_type;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXICTLR1.bit.ARCACHE_G  = ctrl_axi->rch_rgb[D_IM_LTM_PORT_G].cache_type;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXICTLR1.bit.ARPROT_G   = ctrl_axi->rch_rgb[D_IM_LTM_PORT_G].protect_type;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXICTLR1.bit.ARCACHE_B  = ctrl_axi->rch_rgb[D_IM_LTM_PORT_B].cache_type;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXICTLR1.bit.ARPROT_B   = ctrl_axi->rch_rgb[D_IM_LTM_PORT_B].protect_type;

	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXICTLR2.bit.ARCACHE_YP = ctrl_axi->rch_y[D_IM_LTM_PORT_Y_YP].cache_type;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXICTLR2.bit.ARPROT_YP  = ctrl_axi->rch_y[D_IM_LTM_PORT_Y_YP].protect_type;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXICTLR2.bit.ARCACHE_YN = ctrl_axi->rch_y[D_IM_LTM_PORT_Y_YN].cache_type;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXICTLR2.bit.ARPROT_YN  = ctrl_axi->rch_y[D_IM_LTM_PORT_Y_YN].protect_type;

	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXICTLW.bit.AWCACHE_R   = ctrl_axi->wch[D_IM_LTM_PORT_R].cache_type;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXICTLW.bit.AWPROT_R    = ctrl_axi->wch[D_IM_LTM_PORT_R].protect_type;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXICTLW.bit.AWCACHE_G   = ctrl_axi->wch[D_IM_LTM_PORT_G].cache_type;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXICTLW.bit.AWPROT_G    = ctrl_axi->wch[D_IM_LTM_PORT_G].protect_type;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXICTLW.bit.AWCACHE_B   = ctrl_axi->wch[D_IM_LTM_PORT_B].cache_type;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXICTLW.bit.AWPROT_B    = ctrl_axi->wch[D_IM_LTM_PORT_B].protect_type;

	Im_LTM_Off_Pclk( pipe_no );

	ImLtmLtmUtlis_IM_LTM_DSB();

	return D_DDIM_OK;
}

/* get AXI bus read channel status
 */
INT32 Im_LTM_LTM_Get_AxiReadStat( UCHAR pipe_no, T_IM_LTM_LTM_AXI_RCH_STAT* const axi_read_stat )
{
	ImLtmLtmUtlis*imLtmLtmUtlis=im_ltm_ltm_utlis_get( );

#ifdef CO_PARAM_CHECK
	// check on input pointer
	if( axi_read_stat == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_LTM_LTM_Get_AxiReadStat error. axi_read_stat = NULL\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no >= D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_LTM_Get_AxiReadStat error. pipe_no>=D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );

	axi_read_stat->rch_rgb_axi_stat[D_IM_LTM_PORT_1] = im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIRERR.bit.RRESP_R;
	axi_read_stat->rch_rgb_axi_stat[D_IM_LTM_PORT_2] = im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIRERR.bit.RRESP_G;
	axi_read_stat->rch_rgb_axi_stat[D_IM_LTM_PORT_3] = im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIRERR.bit.RRESP_B;

	axi_read_stat->rch_y_axi_stat[D_IM_LTM_PORT_1]   = im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIRERR.bit.RRESP_YP;
	axi_read_stat->rch_y_axi_stat[D_IM_LTM_PORT_2]   = im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIRERR.bit.RRESP_YN;

	Im_LTM_Off_Pclk( pipe_no );

	return D_DDIM_OK;
}

/* get AXI bus write channel status
 */
INT32 Im_LTM_LTM_Get_AxiWriteStat( UCHAR pipe_no, T_IM_LTM_LTM_AXI_WCH_STAT* const axi_write_stat )
{
	ImLtmLtmUtlis*imLtmLtmUtlis=im_ltm_ltm_utlis_get( );

#ifdef CO_PARAM_CHECK
	// check on input pointer
	if( axi_write_stat == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_LTM_LTM_Get_AxiWriteStat error. axi_write_stat = NULL\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no >= D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_LTM_Get_AxiWriteStat error. pipe_no>=D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );

	axi_write_stat->wch_axi_stat[D_IM_LTM_PORT_1] = im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIWERR.bit.WRESP_R;
	axi_write_stat->wch_axi_stat[D_IM_LTM_PORT_2] = im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIWERR.bit.WRESP_G;
	axi_write_stat->wch_axi_stat[D_IM_LTM_PORT_3] = im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIWERR.bit.WRESP_B;

	Im_LTM_Off_Pclk( pipe_no );

	return D_DDIM_OK;
}

/* get AXI bus ctrl param
 */
INT32 Im_LTM_LTM_Get_AxiCtrlParam( UCHAR pipe_no, T_IM_LTM_LTM_AXI_CTRL_PARAM* const axi_ctrl_prm )
{
	ImLtmLtmUtlis*imLtmLtmUtlis=im_ltm_ltm_utlis_get( );

#ifdef CO_PARAM_CHECK
	// check on input pointer
	if( axi_ctrl_prm == NULL ){
		// Parameter setting error
		Ddim_Assertion(("Im_LTM_LTM_Get_AxiCtrlParam error. axi_ctrl_prm = NULL\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no >= D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_LTM_Get_AxiCtrlParam error. pipe_no>=D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );

	axi_ctrl_prm->rch_burst_length_r  = im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIBSIZ.bit.BURSTRR;
	axi_ctrl_prm->rch_burst_length_g  = im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIBSIZ.bit.BURSTRG;
	axi_ctrl_prm->rch_burst_length_b  = im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIBSIZ.bit.BURSTRB;
	axi_ctrl_prm->rch_burst_length_yp = im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIBSIZ.bit.BURSTRYP;
	axi_ctrl_prm->rch_burst_length_yn = im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIBSIZ.bit.BURSTRYN;
	axi_ctrl_prm->wch_burst_length_r  = im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIBSIZ.bit.BURSTWR;
	axi_ctrl_prm->wch_burst_length_g  = im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIBSIZ.bit.BURSTWG;
	axi_ctrl_prm->wch_burst_length_b  = im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIBSIZ.bit.BURSTWB;
	axi_ctrl_prm->mask_write_r        = im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIBSIZ.bit.WSTBMSKR;
	axi_ctrl_prm->mask_write_g        = im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIBSIZ.bit.WSTBMSKG;
	axi_ctrl_prm->mask_write_b        = im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIBSIZ.bit.WSTBMSKB;
	axi_ctrl_prm->read_select_yp      = im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->AXIRSEL.bit.AXIRSEL1;
	axi_ctrl_prm->read_select_yn      = im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->AXIRSEL.bit.AXIRSEL2;

	Im_LTM_Off_Pclk( pipe_no );

	return D_DDIM_OK;
}

/* set AXI bus ctrl param
 */
INT32 Im_LTM_LTM_Set_AxiCtrlParam( UCHAR pipe_no, const T_IM_LTM_LTM_AXI_CTRL_PARAM* const axi_ctrl_prm )
{
	ImLtmLtmUtlis*imLtmLtmUtlis=im_ltm_ltm_utlis_get( );

#ifdef CO_PARAM_CHECK
	// check on input pointer
	if( axi_ctrl_prm == NULL ){
		// Parameter setting error
		Ddim_Assertion(("Im_LTM_LTM_Set_AxiCtrlParam error. axi_ctrl_prm = NULL\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_LTM_Set_AxiCtrlParam error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );

	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIBSIZ.bit.BURSTRR  = axi_ctrl_prm->rch_burst_length_r;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIBSIZ.bit.BURSTRG  = axi_ctrl_prm->rch_burst_length_g;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIBSIZ.bit.BURSTRB  = axi_ctrl_prm->rch_burst_length_b;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIBSIZ.bit.BURSTRYP = axi_ctrl_prm->rch_burst_length_yp;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIBSIZ.bit.BURSTRYN = axi_ctrl_prm->rch_burst_length_yn;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIBSIZ.bit.BURSTWR  = axi_ctrl_prm->wch_burst_length_r;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIBSIZ.bit.BURSTWG  = axi_ctrl_prm->wch_burst_length_g;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIBSIZ.bit.BURSTWB  = axi_ctrl_prm->wch_burst_length_b;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIBSIZ.bit.WSTBMSKR = axi_ctrl_prm->mask_write_r;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIBSIZ.bit.WSTBMSKG = axi_ctrl_prm->mask_write_g;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIBSIZ.bit.WSTBMSKB = axi_ctrl_prm->mask_write_b;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->AXIRSEL.bit.AXIRSEL1  = axi_ctrl_prm->read_select_yp;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->AXIRSEL.bit.AXIRSEL2  = axi_ctrl_prm->read_select_yn;

	Im_LTM_Off_Pclk( pipe_no );

	return D_DDIM_OK;
}

/* LTM_LTM Control (each mode common control)
 */
INT32 Im_LTM_LTM_Ctrl_Common( UCHAR pipe_no, const T_IM_LTM_LTM_CTRL_COMMON* const ltm_ctrl )
{
	ImLtmLtmUtlis*imLtmLtmUtlis=im_ltm_ltm_utlis_get( );

	UCHAR	loop_cnt, loop_sta, loop_end;

#ifdef CO_PARAM_CHECK
	if( ltm_ctrl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_LTM_LTM_Ctrl_Common error. ltm_ctrl = NULL\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_LTM_Ctrl_Common error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_ltm_ltm_get_loop_val( pipe_no, &loop_sta, &loop_end );

	Im_LTM_On_Pclk( pipe_no );

	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LLINTLV.bit.LINTLV     = ltm_ctrl->line_intr;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIBSIZ.bit.BURSTRYP  = ltm_ctrl->rch_burst_length_yp;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIBSIZ.bit.BURSTRYN  = ltm_ctrl->rch_burst_length_yn;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIBSIZ.bit.BURSTWR   = ltm_ctrl->wch_burst_length_r;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIBSIZ.bit.BURSTWG   = ltm_ctrl->wch_burst_length_g;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIBSIZ.bit.BURSTWB   = ltm_ctrl->wch_burst_length_b;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIBSIZ.bit.WSTBMSKR  = ltm_ctrl->mask_write_r;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIBSIZ.bit.WSTBMSKG  = ltm_ctrl->mask_write_g;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIBSIZ.bit.WSTBMSKB  = ltm_ctrl->mask_write_b;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->AXIRSEL.bit.AXIRSEL1   = ltm_ctrl->read_select_yp;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->AXIRSEL.bit.AXIRSEL2   = ltm_ctrl->read_select_yn;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LIOCTL.bit.R3DTYP      = ltm_ctrl->in_data_type_yp;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LIOCTL.bit.R4DTYP      = ltm_ctrl->in_data_type_yn;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LIOCTL.bit.OUTSEL      = ltm_ctrl->out_select;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LIOCTL.bit.W1DTYP      = ltm_ctrl->out_data_type;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LSDRHSZR3.bit.SDRHSZR3 = ltm_ctrl->input_rect.img_width;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LSDRDEFR3.bit.SDRDEFR3 = ltm_ctrl->global_width_yp;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LSDRVSZR3.bit.SDRVSZR3 = ltm_ctrl->input_rect.img_lines;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LSDRDEFR4.bit.SDRDEFR4 = ltm_ctrl->global_width_yn;

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		im_ltm_ltm_utlis_get_gIM_LTM_LTM_Mng(imLtmLtmUtlis,loop_cnt).inputSizeY = ltm_ctrl->input_rect;
		// Set Callback pointer
		im_ltm_ltm_utlis_get_gIM_LTM_LTM_Mng(imLtmLtmUtlis,loop_cnt).ltmUserHandler = ltm_ctrl->ltm_user_handler;
		im_ltm_ltm_utlis_get_gIM_LTM_LTM_Mng(imLtmLtmUtlis,loop_cnt).userParam = ltm_ctrl->user_param;
	}

	Im_LTM_Off_Pclk( pipe_no );

	ImLtmLtmUtlis_IM_LTM_DSB();

	return D_DDIM_OK;
}
/* LTM_LTM Control (SDRAM input mode control)
 */
INT32 Im_LTM_LTM_Ctrl_ModeSDRAMInput( UCHAR pipe_no, const T_IM_LTM_LTM_CTRL_SDRAM_INPUT* const ltm_ctrl_sdram_input )
{
	ImLtmLtmUtlis*imLtmLtmUtlis=im_ltm_ltm_utlis_get( );

	UCHAR	loop_cnt, loop_sta, loop_end;
#ifdef CO_PARAM_CHECK
	if( ltm_ctrl_sdram_input == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_LTM_LTM_Ctrl_ModeSDRAMInput error. ltm_ctrl_sdram_input = NULL\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_LTM_Ctrl_ModeSDRAMInput error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_ltm_ltm_get_loop_val( pipe_no, &loop_sta, &loop_end );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		im_ltm_ltm_utlis_get_gIM_LTM_LTM_Mng(imLtmLtmUtlis,loop_cnt).inputSizeRgb = ltm_ctrl_sdram_input->input_rect;
	}

	Im_LTM_On_Pclk( pipe_no );

	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIBSIZ.bit.BURSTRR   = ltm_ctrl_sdram_input->rch_burst_length_r;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIBSIZ.bit.BURSTRG   = ltm_ctrl_sdram_input->rch_burst_length_g;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LAXIBSIZ.bit.BURSTRB   = ltm_ctrl_sdram_input->rch_burst_length_b;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LSDRDEFR2.bit.SDRDEFR2 = ltm_ctrl_sdram_input->input_global_rgb;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LSDRHSZR2.bit.SDRHSZR2 = ltm_ctrl_sdram_input->input_rect.img_width;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LSDRVSZR2.bit.SDRVSZR2 = ltm_ctrl_sdram_input->input_rect.img_lines;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LIOCTL.bit.INSEL       = ImLtmLtmUtlis_D_IM_LTM_LTM_MODE_SDRAM_INPUT;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LIOCTL.bit.BYPASS      = D_IM_LTM_ENABLE_OFF;

	Im_LTM_Off_Pclk( pipe_no );
	ImLtmLtmUtlis_IM_LTM_DSB();

	return D_DDIM_OK;
}

/* Set Managed Input Address information(Main RGB images)
 */
INT32 Im_LTM_LTM_Set_InAddr_Info_Rgb( UCHAR pipe_no, const T_IM_LTM_INADDR_INFO* const in_addr )
{
	ImLtmLtmUtlis*imLtmLtmUtlis=im_ltm_ltm_utlis_get( );

	UINT32 offset;

#ifdef CO_PARAM_CHECK
	if( in_addr == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_LTM_LTM_Set_InAddr_Info_Rgb error. in_addr = NULL\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no >= D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_LTM_Set_InAddr_Info_Rgb error. pipe_no>=D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );

	offset = ( im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LSDRDEFR2.bit.SDRDEFR2 * im_ltm_ltm_utlis_get_gIM_LTM_LTM_Mng(imLtmLtmUtlis,pipe_no).inputSizeRgb.img_top ) + ( im_ltm_ltm_utlis_get_gIM_LTM_LTM_Mng(imLtmLtmUtlis,pipe_no).inputSizeRgb.img_left * 2 );

	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LSDRADR2R.bit.SDRADR2R = (UINT32)in_addr->addr_r + offset;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LSDRADR2G.bit.SDRADR2G = (UINT32)in_addr->addr_g + offset;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LSDRADR2B.bit.SDRADR2B = (UINT32)in_addr->addr_b + offset;

	Im_LTM_Off_Pclk( pipe_no );
	ImLtmLtmUtlis_IM_LTM_DSB();

	return D_DDIM_OK;
}

/* Set Managed Input Address/Offset information(Map Y images)
 */
INT32 Im_LTM_LTM_Set_InData_Info( UCHAR pipe_no, const T_IM_LTM_LTM_INDATA_INFO* const in_data_info )
{
	ImLtmLtmUtlis*imLtmLtmUtlis=im_ltm_ltm_utlis_get( );

	UINT32 offset_yp = 0;
	UINT32 offset_yn = 0;
	UCHAR bit_offset_yp = 0;
	UCHAR bit_offset_yn = 0;
	double coef_yp, coef_yn;

#ifdef CO_PARAM_CHECK
	if( in_data_info == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_LTM_LTM_Set_InData_Info error. in_data_info = NULL\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no >= D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_LTM_Set_InData_Info error. pipe_no>=D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );

	coef_yp = ( im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LIOCTL.bit.R3DTYP == D_IM_LTM_DTYP_PACK12 ) ? ( 3.0 / 2.0 ) : ( 2.0 );
	coef_yn = ( im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LIOCTL.bit.R4DTYP == D_IM_LTM_DTYP_PACK12 ) ? ( 3.0 / 2.0 ) : ( 2.0 );

	offset_yp = ( im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LSDRDEFR3.bit.SDRDEFR3 * im_ltm_ltm_utlis_get_gIM_LTM_LTM_Mng(imLtmLtmUtlis,pipe_no).inputSizeY.img_top );
	offset_yp += (UINT32)( im_ltm_ltm_utlis_get_gIM_LTM_LTM_Mng(imLtmLtmUtlis,pipe_no).inputSizeY.img_left * coef_yp );
	if(( im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LIOCTL.bit.R3DTYP == D_IM_LTM_DTYP_PACK12 )
	&& ( im_ltm_ltm_utlis_get_gIM_LTM_LTM_Mng(imLtmLtmUtlis,pipe_no).inputSizeY.img_left & 1 )){
		bit_offset_yp = ( in_data_info->top_bit_offset_yp == D_IM_LTM_ENABLE_ON ) ? 0 : 1;
	}
	else{
		bit_offset_yp = in_data_info->top_bit_offset_yp;
	}

	offset_yn = ( im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LSDRDEFR4.bit.SDRDEFR4 * im_ltm_ltm_utlis_get_gIM_LTM_LTM_Mng(imLtmLtmUtlis,pipe_no).inputSizeY.img_top );
	offset_yn += (UINT32)( im_ltm_ltm_utlis_get_gIM_LTM_LTM_Mng(imLtmLtmUtlis,pipe_no).inputSizeY.img_left * coef_yn );
	if(( im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LIOCTL.bit.R4DTYP == D_IM_LTM_DTYP_PACK12 )
	&& ( im_ltm_ltm_utlis_get_gIM_LTM_LTM_Mng(imLtmLtmUtlis,pipe_no).inputSizeY.img_left & 1 )){
		bit_offset_yn = ( in_data_info->top_bit_offset_yn == D_IM_LTM_ENABLE_ON ) ? 0 : 1;
	}
	else{
		bit_offset_yn = in_data_info->top_bit_offset_yn;
	}

	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LSDRADR3.bit.SDRADR3 = (UINT32)in_data_info->addr_yp + offset_yp;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LSDROFS.bit.SDROFSR3 = bit_offset_yp;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LSDRADR4.bit.SDRADR4 = (UINT32)in_data_info->addr_yn + offset_yn;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LSDROFS.bit.SDROFSR4 = bit_offset_yn;

	Im_LTM_Off_Pclk( pipe_no );
	ImLtmLtmUtlis_IM_LTM_DSB();

	return D_DDIM_OK;
}

/* Set Managed output Address/Global width information
 */
INT32 Im_LTM_LTM_Set_OutData_Info( UCHAR pipe_no, const T_IM_LTM_LTM_OUTDATA_INFO* const out_data_info )
{
	ImLtmLtmUtlis*imLtmLtmUtlis=im_ltm_ltm_utlis_get( );

#ifdef CO_PARAM_CHECK
	if( out_data_info == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_LTM_LTM_Set_OutData_Info error. out_data_info = NULL\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_LTM_Set_OutData_Info error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );

	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LSDWADR.bit.SDWADR   = (UINT32)out_data_info->addr[D_IM_LTM_PORT_R];
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LSDWDEFR.bit.SDWDEFR = out_data_info->global_width[D_IM_LTM_PORT_R];
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LSDWADG.bit.SDWADG   = (UINT32)out_data_info->addr[D_IM_LTM_PORT_G];
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LSDWDEFG.bit.SDWDEFG = out_data_info->global_width[D_IM_LTM_PORT_G];
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LSDWADB.bit.SDWADB   = (UINT32)out_data_info->addr[D_IM_LTM_PORT_B];
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LSDWDEFB.bit.SDWDEFB = out_data_info->global_width[D_IM_LTM_PORT_B];

	Im_LTM_Off_Pclk( pipe_no );
	ImLtmLtmUtlis_IM_LTM_DSB();

	return D_DDIM_OK;
}

/* LTM_LTM Control (B2R direct connection mode control)
 */
INT32 Im_LTM_LTM_Ctrl_ModeB2RDirect( UCHAR pipe_no, const T_IM_LTM_LTM_CTRL_B2R_DIRECT* const ltm_ctrl_b2r_direct )
{
	UCHAR	loop_cnt, loop_sta, loop_end;

	ImLtmLtmUtlis*imLtmLtmUtlis=im_ltm_ltm_utlis_get( );

#ifdef CO_PARAM_CHECK
	if( ltm_ctrl_b2r_direct == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_LTM_LTM_Ctrl_ModeB2RDirect error. ltm_ctrl_b2r_direct = NULL\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_LTM_Ctrl_ModeB2RDirect error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_ltm_ltm_get_loop_val( pipe_no, &loop_sta, &loop_end );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		im_ltm_ltm_utlis_get_gIM_LTM_LTM_Mng(imLtmLtmUtlis,loop_cnt).inputSizeRgb = ltm_ctrl_b2r_direct->input_rect;
	}

	Im_LTM_On_Pclk( pipe_no );

	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LIOCTL.bit.INSEL       = ImLtmLtmUtlis_D_IM_LTM_LTM_MODE_B2R_DIRECT;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LSDRHSZR2.bit.SDRHSZR2 = ltm_ctrl_b2r_direct->input_rect.img_width;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LSDRVSZR2.bit.SDRVSZR2 = ltm_ctrl_b2r_direct->input_rect.img_lines;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LIOCTL.bit.BYPASS      = ltm_ctrl_b2r_direct->bypass;

	Im_LTM_Off_Pclk( pipe_no );
	ImLtmLtmUtlis_IM_LTM_DSB();

	return D_DDIM_OK;
}

INT32 Im_LTM_LTM_Set_MapImage_Resize_Pitch_Auto( UCHAR pipe_no )
{
	ImLtmLtmUtlis*imLtmLtmUtlis=im_ltm_ltm_utlis_get( );

	UCHAR tmp_pipe_no;
	USHORT rgb_width, rgb_lines, map_width, map_lines;
	UINT32 hsta, hpit, vsta, vpit;
	UINT32 tmp_hsz, tmp_vsz;


#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_LTM_Set_MapImage_Resize_Pitch_Auto error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	tmp_pipe_no = ( pipe_no == D_IM_LTM_PIPE12 ) ? D_IM_LTM_PIPE1: pipe_no;

	Im_LTM_On_Pclk( pipe_no );

	rgb_width = im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,tmp_pipe_no)->LSDRHSZR2.bit.SDRHSZR2;
	rgb_lines = im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,tmp_pipe_no)->LSDRVSZR2.bit.SDRVSZR2;
	map_width = im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,tmp_pipe_no)->LSDRHSZR3.bit.SDRHSZR3;
	map_lines = im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,tmp_pipe_no)->LSDRVSZR3.bit.SDRVSZR3;

	hpit = 16384 * map_width / rgb_width;
	vpit = 16384 * map_lines / rgb_lines;

	tmp_hsz = ( map_width - 1 ) * 16384 / hpit + 1;
	tmp_vsz = ( map_lines - 1 ) * 16384 / vpit + 1;

	hsta = hpit * ( tmp_hsz - rgb_width ) / 2;
	vsta = vpit * ( tmp_vsz - rgb_lines ) / 2;

	ImLtmLtmUtlis_IM_LTM_LTM_SET_REG_SIGNED( im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LHSTA, union io_ltm_ch_ltm_lhsta, HSTA, hsta );
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LHPIT.bit.HPIT = hpit;
	ImLtmLtmUtlis_IM_LTM_LTM_SET_REG_SIGNED( im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LVSTA, union io_ltm_ch_ltm_lvsta, VSTA, vsta );
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LVPIT.bit.VPIT = vpit;

	Im_LTM_Off_Pclk( pipe_no );
	ImLtmLtmUtlis_IM_LTM_DSB();

	return D_DDIM_OK;
}

ImLtmLtmWin*im_ltm_ltm_win_get(void)
{
	 static ImLtmLtmWin* self = NULL;
	 if(!self){
		 self = k_object_new(IM_TYPE_LTM_LTM_WIN);
	 }
//	 else{
//		 k_object_ref(self);
//	 }
	return self;
}
