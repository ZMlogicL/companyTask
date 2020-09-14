/*
*@Copyright (C) 2010-2020贵阳高新网用软件有限公司
*@date                :2020-09-02
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
#include "ddarm.h"
#include "jdsltm.h"
#include "imltmmaplist.h"
#include "imltmmapevent.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImLtmMapEvent, im_ltm_map_event);
#define IM_LTM_MAP_EVENT_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImLtmMapEventPrivate, IM_TYPE_LTM_MAP_EVENT))

struct _ImLtmMapEventPrivate
{
	int a;
};

/*----------------------------------------------------------------------*/
/* DECLS  															    */
/*----------------------------------------------------------------------*/
static VOID imLtmMapManagerInit( UCHAR pipe_no );

static void im_ltm_map_event_constructor(ImLtmMapEvent *self)
{
//	ImLtmMapEventPrivate *priv = IM_LTM_MAP_EVENT_GET_PRIVATE(self);
}

static void im_ltm_map_event_destructor(ImLtmMapEvent *self)
{
//	ImLtmMapEventPrivate *priv = IM_LTM_MAP_EVENT_GET_PRIVATE(self);
}

/*----------------------------------------------------------------------*/
/* IMPL  															    */
/*----------------------------------------------------------------------*/
static VOID imLtmMapManagerInit( UCHAR pipe_no )
{
	ImLtmMapList*imLtmMapList=im_ltm_map_list_get( );

	UCHAR size_coef = 1;

#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "imLtmMapManagerInit error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

	if( pipe_no == D_IM_LTM_PIPE12 ){
		size_coef = 2;
		pipe_no = 0;
	}

	// Initialize of State & Handler management information
	memset( (USHORT*)&im_ltm_map_list_get_gIM_LTM_MAP_Mng(imLtmMapList,pipe_no), 0, sizeof(TImLtmMapMng) * size_coef );

	return;
}

/*----------------------------------------------------------------------*/
/* PUBLIC 															    */
/*----------------------------------------------------------------------*/
INT32 Im_LTM_MAP_Init( UCHAR pipe_no )
{
	ImLtmMapList*imLtmMapList=im_ltm_map_list_get( );

	ULONG clksel[2] = { 0, 0 };
	UCHAR clkstop[2][3] = {{ 0, 0, 0 }, { 0, 0, 0 }};	// SROxCLK/SROxCLK_2/LTMRBKxCLK

#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_MAP_Init error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	if( pipe_no == D_IM_LTM_PIPE1 || pipe_no == D_IM_LTM_PIPE12 ){
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
	if( pipe_no == D_IM_LTM_PIPE2 || pipe_no == D_IM_LTM_PIPE12 ){
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

	imLtmMapManagerInit( pipe_no );

	Im_LTM_On_Pclk( pipe_no );
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MAPSR.bit.SR = ImLtmMapList_D_IM_LTM_SR_RELEASE;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MSRAMEN.word = ImLtmMapList_D_IM_LTM_MAP_MSRAMEN_ENABLE;
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

	ImLtmMapList_Im_LTM_Dsb();

	return D_DDIM_OK;
}

/* LTM_MAP SW reset
 */
INT32 Im_LTM_MAP_SW_Reset( UCHAR pipe_no )
{
	ImLtmMapList*imLtmMapList=im_ltm_map_list_get( );

	UCHAR	loop_cnt, loop_sta, loop_end;

#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_MAP_SW_Reset error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_ltm_map_list_im_ltm_map_get_loop_val(NULL,pipe_no, &loop_sta, &loop_end );

	Im_LTM_On_Pclk( pipe_no );
	Im_LTM_On_RBKClk( pipe_no );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		if( im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,loop_cnt)->MTRG.bit.TRG == ImLtmMapList_D_IM_LTM_MAP_TRG_BUSY ){
			return D_IM_LTM_MACRO_BUSY;
		}
	}
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MAPSR.bit.SR = ImLtmMapList_D_IM_LTM_SR_RESET;

	Im_LTM_Off_RBKClk( pipe_no );
	Im_LTM_Off_Pclk( pipe_no );

	ImLtmMapList_Im_LTM_Dsb();

	return D_DDIM_OK;
}

/* set AXI bus I/F Control
 */
INT32 Im_LTM_MAP_Ctrl_Axi( UCHAR pipe_no, const T_IM_LTM_MAP_CTRL_AXI* const ctrl_axi )
{
	ImLtmMapList*imLtmMapList=im_ltm_map_list_get( );

#ifdef CO_PARAM_CHECK
	// check on input pointer
	if( ctrl_axi == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_LTM_MAP_Ctrl_Axi error. ctrl_axi = NULL\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_MAP_Ctrl_Axi error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MAXICTLR.bit.ARCACHE = ctrl_axi->rch.cache_type;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MAXICTLR.bit.ARPROT  = ctrl_axi->rch.protect_type;

	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MAXICTLW.bit.AWCACHE_YP = ctrl_axi->wch[D_IM_LTM_PORT_Y_YP].cache_type;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MAXICTLW.bit.AWPROT_YP  = ctrl_axi->wch[D_IM_LTM_PORT_Y_YP].protect_type;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MAXICTLW.bit.AWCACHE_YN = ctrl_axi->wch[D_IM_LTM_PORT_Y_YN].cache_type;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MAXICTLW.bit.AWPROT_YN  = ctrl_axi->wch[D_IM_LTM_PORT_Y_YN].protect_type;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MAXICTLW.bit.AWCACHE_DB = 0;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MAXICTLW.bit.AWPROT_DB  = 0;
	Im_LTM_Off_Pclk( pipe_no );

	ImLtmMapList_Im_LTM_Dsb();

	return D_DDIM_OK;
}

/* get AXI bus read channel status
 */
INT32 Im_LTM_MAP_Get_AxiReadStat( UCHAR pipe_no, T_IM_LTM_MAP_AXI_RCH_STAT* const axi_read_stat )
{
	ImLtmMapList*imLtmMapList=im_ltm_map_list_get( );

#ifdef CO_PARAM_CHECK
	// check on input pointer
	if( axi_read_stat == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_LTM_MAP_Get_AxiReadStat error. axi_read_stat = NULL\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no >= D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_MAP_Get_AxiReadStat error. pipe_no>=D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );
	axi_read_stat->rch_axi_stat = im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MAXIRERR.bit.RRESP;
	Im_LTM_Off_Pclk( pipe_no );

	return D_DDIM_OK;
}

/* get AXI bus write channel status
 */
INT32 Im_LTM_MAP_Get_AxiWriteStat( UCHAR pipe_no, T_IM_LTM_MAP_AXI_WCH_STAT* const axi_write_stat )
{
	ImLtmMapList*imLtmMapList=im_ltm_map_list_get( );

#ifdef CO_PARAM_CHECK
	// check on input pointer
	if( axi_write_stat == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_LTM_MAP_Get_AxiWriteStat error. axi_write_stat = NULL\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no >= D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_MAP_Get_AxiWriteStat error. pipe_no>=D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );
	axi_write_stat->wch_axi_stat[D_IM_LTM_PORT_1] = im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MAXIWERR.bit.WRESP_YP;
	axi_write_stat->wch_axi_stat[D_IM_LTM_PORT_2] = im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MAXIWERR.bit.WRESP_YN;
	Im_LTM_Off_Pclk( pipe_no );

	return D_DDIM_OK;
}

/* get AXI bus ctrl param
 */
INT32 Im_LTM_MAP_Get_AxiCtrlParam( UCHAR pipe_no, T_IM_LTM_MAP_AXI_CTRL_PARAM* const axi_ctrl_prm )
{
	ImLtmMapList*imLtmMapList=im_ltm_map_list_get( );

#ifdef CO_PARAM_CHECK
	// check on input pointer
	if( axi_ctrl_prm == NULL ){
		// Parameter setting error
		Ddim_Assertion(("Im_LTM_MAP_Get_AxiCtrlParam error. axi_ctrl_prm = NULL\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no >= D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_MAP_Get_AxiCtrlParam error. pipe_no>=D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );
	axi_ctrl_prm->rch_burst_length    = im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MAXIBSIZ.bit.BURSTR;
	axi_ctrl_prm->wch_burst_length_yp = im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MAXIBSIZ.bit.BURSTWYP;
	axi_ctrl_prm->wch_burst_length_yn = im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MAXIBSIZ.bit.BURSTWYN;
	axi_ctrl_prm->mask_write_yp       = im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MAXIBSIZ.bit.WSTBMSKYP;
	axi_ctrl_prm->mask_write_yn       = im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MAXIBSIZ.bit.WSTBMSKYN;
	axi_ctrl_prm->write_select_yp     = im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->AXICHSEL.bit.AXIWSEL1;
	axi_ctrl_prm->write_select_yn     = im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->AXICHSEL.bit.AXIWSEL2;
	Im_LTM_Off_Pclk( pipe_no );

	return D_DDIM_OK;
}

INT32 im_ltm_map_list_im_ltm_map_set_axictrlparam( UCHAR pipe_no, const T_IM_LTM_MAP_AXI_CTRL_PARAM* const axi_ctrl_prm )
{
	ImLtmMapList*imLtmMapList=im_ltm_map_list_get( );

#ifdef CO_PARAM_CHECK
	// check on input pointer
	if( axi_ctrl_prm == NULL ){
		// Parameter setting error
		Ddim_Assertion(("im_ltm_map_list_im_ltm_map_set_axictrlparam error. axi_ctrl_prm = NULL\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_map_list_im_ltm_map_set_axictrlparam error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MAXIBSIZ.bit.BURSTR    = axi_ctrl_prm->rch_burst_length;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MAXIBSIZ.bit.BURSTWYP  = axi_ctrl_prm->wch_burst_length_yp;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MAXIBSIZ.bit.BURSTWYN  = axi_ctrl_prm->wch_burst_length_yn;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MAXIBSIZ.bit.WSTBMSKYP = axi_ctrl_prm->mask_write_yp;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MAXIBSIZ.bit.WSTBMSKYN = axi_ctrl_prm->mask_write_yn;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->AXICHSEL.bit.AXIWSEL1 = axi_ctrl_prm->write_select_yp;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->AXICHSEL.bit.AXIWSEL2 = axi_ctrl_prm->write_select_yn;
	Im_LTM_Off_Pclk( pipe_no );

	return D_DDIM_OK;
}

/* LTM_MAP Control (each mode common control)
 */
INT32 Im_LTM_MAP_Ctrl_Common( UCHAR pipe_no, const T_IM_LTM_MAP_CTRL_COMMON* const map_ctrl )
{
	ImLtmMapList*imLtmMapList=im_ltm_map_list_get( );

	UCHAR	loop_cnt, loop_sta, loop_end;

#ifdef CO_PARAM_CHECK
	if( map_ctrl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_LTM_MAP_Ctrl_Common error. map_ctrl = NULL\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_MAP_Ctrl_Common error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_ltm_map_list_im_ltm_map_get_loop_val(NULL,pipe_no, &loop_sta, &loop_end );

	Im_LTM_On_Pclk( pipe_no );

	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MLINTLV.bit.LINTLV     = map_ctrl->line_intr;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MAXIBSIZ.bit.BURSTWYP  = map_ctrl->wch_burst_length_yp;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MAXIBSIZ.bit.BURSTWYN  = map_ctrl->wch_burst_length_yn;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MAXIBSIZ.bit.WSTBMSKYP = map_ctrl->mask_write_yp;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MAXIBSIZ.bit.WSTBMSKYN = map_ctrl->mask_write_yn;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->AXICHSEL.bit.AXIWSEL1  = map_ctrl->write_select_yp;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->AXICHSEL.bit.AXIWSEL2  = map_ctrl->write_select_yn;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MIOCTL.bit.W0DTYP      = map_ctrl->data_type_yp;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MIOCTL.bit.W1DTYP      = map_ctrl->data_type_yn;

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		// Set Callback pointer
		im_ltm_map_list_get_gIM_LTM_MAP_Mng(imLtmMapList,loop_cnt).mapUserHandler = map_ctrl->map_user_handler;
		im_ltm_map_list_get_gIM_LTM_MAP_Mng(imLtmMapList,loop_cnt).userParam = map_ctrl->user_param;
	}

	Im_LTM_Off_Pclk( pipe_no );

	ImLtmMapList_Im_LTM_Dsb();

	return D_DDIM_OK;
}

/* LTM_MAP Control (SDRAM input mode control)
 */
INT32 Im_LTM_MAP_Ctrl_ModeSDRAMInput( UCHAR pipe_no, const T_IM_LTM_MAP_CTRL_SDRAM_INPUT* const map_ctrl_sdram_input )
{
	ImLtmMapList*imLtmMapList=im_ltm_map_list_get( );

	UCHAR	loop_cnt, loop_sta, loop_end;

#ifdef CO_PARAM_CHECK
	if( map_ctrl_sdram_input == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_LTM_MAP_Ctrl_ModeSDRAMInput error. map_ctrl_sdram_input = NULL\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_MAP_Ctrl_ModeSDRAMInput error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_ltm_map_list_im_ltm_map_get_loop_val(NULL,pipe_no, &loop_sta, &loop_end );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		im_ltm_map_list_get_gIM_LTM_MAP_Mng(imLtmMapList,loop_cnt).inputSize = map_ctrl_sdram_input->input_rect;
	}

	Im_LTM_On_Pclk( pipe_no );

	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MAXIBSIZ.bit.BURSTR = map_ctrl_sdram_input->burst_length;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MSDRDEF.bit.SDRDEF  = map_ctrl_sdram_input->input_global;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MSDRHSZ.bit.SDRHSZ  = map_ctrl_sdram_input->input_rect.img_width;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MSDRVSZ.bit.SDRVSZ  = map_ctrl_sdram_input->input_rect.img_lines;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MIOCTL.bit.INSEL    = ImLtmMapList_D_IM_LTM_MAP_MODE_SDRAM_INPUT;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MIOCTL.bit.R1DTYP   = map_ctrl_sdram_input->data_type;

	Im_LTM_Off_Pclk( pipe_no );
	ImLtmMapList_Im_LTM_Dsb();

	return D_DDIM_OK;
}

/* Set Managed Input Address/Offset information
 */
INT32 Im_LTM_MAP_Set_InData_Info( UCHAR pipe_no, const T_IM_LTM_MAP_INDATA_INFO* const in_data_info )
{
	ImLtmMapList*imLtmMapList=im_ltm_map_list_get( );

	UINT32 offset = 0;
	UCHAR bit_offset = 0;
	double coef;

#ifdef CO_PARAM_CHECK
	if( in_data_info == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_LTM_MAP_Set_InData_Info error. in_data_info = NULL\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no >= D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_MAP_Set_InData_Info error. pipe_no>=D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );

	coef = ( im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MIOCTL.bit.R1DTYP == D_IM_LTM_DTYP_PACK12 ) ? ( 3.0 * 3.0 / 2.0 ) : ( 3.0 * 2.0 );

	offset = ( im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MSDRDEF.bit.SDRDEF *im_ltm_map_list_get_gIM_LTM_MAP_Mng(imLtmMapList,pipe_no).inputSize.img_top );
	offset += (UINT32)( im_ltm_map_list_get_gIM_LTM_MAP_Mng(imLtmMapList,pipe_no).inputSize.img_left * coef );

	if(( im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MIOCTL.bit.R1DTYP == D_IM_LTM_DTYP_PACK12 )
	&& ( im_ltm_map_list_get_gIM_LTM_MAP_Mng(imLtmMapList,pipe_no).inputSize.img_left & 0x1 )){
		bit_offset = ( in_data_info->top_bit_offset == D_IM_LTM_ENABLE_ON ) ? 0 : 1;
	}
	else{
		bit_offset = in_data_info->top_bit_offset;
	}

	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MSDRAD.bit.SDRAD   = (UINT32)in_data_info->addr + offset;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MSDROFS.bit.SDROFS = bit_offset;

	Im_LTM_Off_Pclk( pipe_no );
	ImLtmMapList_Im_LTM_Dsb();

	return D_DDIM_OK;
}

/* Set Managed output Address/Global width information
 */
INT32 Im_LTM_MAP_Set_OutData_Info( UCHAR pipe_no, const T_IM_LTM_MAP_OUTDATA_INFO* const out_data_info )
{
	ImLtmMapList*imLtmMapList=im_ltm_map_list_get( );

#ifdef CO_PARAM_CHECK
	if( out_data_info == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_LTM_MAP_Set_OutData_Info error. out_data_info = NULL\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_MAP_Set_OutData_Info error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );

	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MSDWADW0.bit.SDWADW0   = (UINT32)out_data_info->addr_yp;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MSDWDEFW0.bit.SDWDEFW0 = out_data_info->global_width_yp;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MSDWADW1.bit.SDWADW1   = (UINT32)out_data_info->addr_yn;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MSDWDEFW1.bit.SDWDEFW1 = out_data_info->global_width_yn;

	Im_LTM_Off_Pclk( pipe_no );
	ImLtmMapList_Im_LTM_Dsb();

	return D_DDIM_OK;
}

/* LTM_MAP Control (RBK direct connection mode control)
 */
INT32 Im_LTM_MAP_Ctrl_ModeRBKDirect( UCHAR pipe_no )
{
	ImLtmMapList*imLtmMapList=im_ltm_map_list_get( );

#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_MAP_Ctrl_ModeRBKDirect error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );

	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MIOCTL.bit.INSEL  = ImLtmMapList_D_IM_LTM_MAP_MODE_RBK_DIRECT;

	Im_LTM_Off_Pclk( pipe_no );
	ImLtmMapList_Im_LTM_Dsb();

	return D_DDIM_OK;
}

INT32 Im_LTM_MAP_WaitEnd( DDIM_USER_FLGPTN* const p_flgptn, DDIM_USER_FLGPTN waiptn, DDIM_USER_TMO tmout )
{
	DDIM_USER_FLGPTN	flgptn;
	DDIM_USER_ER		ercd;

#ifdef CO_DEBUG_PRINT_IM_LTM_MAP
	Ddim_Print(( "Im_LTM_MAP_WaitEnd begin\n" ));
#endif

#ifdef CO_PARAM_CHECK
	if( (waiptn & ImLtmMapList_D_IM_LTM_MAP_INT_FLG_ALL) != waiptn ) {
		// Parameter setting error
		Ddim_Assertion(("Im_LTM_MAP_WaitEnd error. waiptn\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif
	ImLtmMapList_Im_LTM_Dsb();

	switch( DDIM_User_Twai_Flg( FID_IM_LTM_MAP, waiptn, D_DDIM_USER_TWF_ORW, &flgptn, tmout ) ) {
		case D_DDIM_USER_E_OK:
#ifdef CO_DEBUG_PRINT_IM_LTM_MAP
		Ddim_Print(( "Im_LTM_MAP_WaitEnd twai_flg OK return\n" ));
#endif
			flgptn = waiptn & flgptn;
			ercd = DDIM_User_Clr_Flg( FID_IM_LTM_MAP, ~flgptn );
			if( ercd != D_DDIM_USER_E_OK ) {
				Ddim_Print(( "Im_LTM_MAP_WaitEnd: invalid FID.\n" ));
				return D_IM_LTM_SYSTEM_ERROR;
			}
			if( p_flgptn != NULL ) {
				*p_flgptn = flgptn;
			}
			return D_DDIM_OK;
		case D_DDIM_USER_E_TMOUT:
#ifdef CO_DEBUG_PRINT_IM_LTM_MAP
		Ddim_Print(( "Im_LTM_MAP_WaitEnd twai_flg TimeOut return\n" ));
#endif
			return D_IM_LTM_TIMEOUT;
		default:
#ifdef CO_DEBUG_PRINT_IM_LTM_MAP
		Ddim_Print(( "Im_LTM_MAP_WaitEnd twai_flg NG return\n" ));
#endif
			return D_IM_LTM_PARAM_ERROR;
	}
}

ImLtmMapEvent*im_ltm_map_event_get(void)
{
	 static ImLtmMapEvent* self = NULL;
	 if(!self){
		 self = k_object_new(IM_TYPE_LTM_MAP_EVENT);
	 }
//	 else{
//		 k_object_ref(self);
//	 }
	return self;
}

