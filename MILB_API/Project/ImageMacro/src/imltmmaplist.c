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
#include "ddarm.h"
#include "jdsltm.h"
#include "imltmmaplist.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImLtmMapList, im_ltm_map_list);
#define IM_LTM_MAP_LIST_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImLtmMapListPrivate, IM_TYPE_LTM_MAP_LIST))

struct _ImLtmMapListPrivate
{
	int a;
};

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
// Nothing Special
#endif	// CO_DDIM_UTILITY_USE

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
// Nothing Special
#endif	// CO_DDIM_UTILITY_USE

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
// Nothing Special
#endif	// CO_DDIM_UTILITY_USE

static volatile struct io_ltm_map_sram* S_GIM_IO_LTM_MAP_TBL_PTR[D_IM_LTM_PIPE_MAX] = { &(IO_LTM_TBL_P1.MAP_SRAM), &(IO_LTM_TBL_P2.MAP_SRAM), &(IO_LTM_TBL_P3.MAP_SRAM) };

static const TImLtmMapIntflgTbl S_GIM_LTM_MAP_INTTBL[ImLtmMapList_D_IM_LTM_PIPE_COUNT][6] = {
	{
		{ 0x00000001, 0x00000001, D_IM_LTM_MAP1_INT_STATE_MAP_END,      D_IM_LTM_MAP1_INT_FLG_MAP_END      },	// FINEN
		{ 0x00001000, 0x00001000, D_IM_LTM_MAP1_INT_STATE_LINE_END,     ImLtmMapList_D_IM_LTM_MAP1_INT_FLG_LINE_END     },	// LCNTEN
		{ 0x00010000, 0x00010000, ImLtmMapList_D_IM_LTM_MAP1_INT_STATE_HISTINI_END,  ImLtmMapList_D_IM_LTM_MAP1_INT_FLG_HISTINI_END  },	// LCNTEN
		{ 0x00100000, 0x00100000, D_IM_LTM_MAP1_INT_STATE_AXR_ERR,      ImLtmMapList_D_IM_LTM_MAP1_INT_FLG_AXR_ERR      },	// AXREEN
		{ 0x00200000, 0x00200000, D_IM_LTM_MAP1_INT_STATE_AXW_ERR,      ImLtmMapList_D_IM_LTM_MAP1_INT_FLG_AXW_ERR      },	// AXWEEN
		{ 0x02000000, 0x02000000, D_IM_LTM_MAP1_INT_STATE_YLOG_ERR,     ImLtmMapList_D_IM_LTM_MAP1_INT_FLG_YLOG_ERR     },	// RAMEEN
	},
	{
		{ 0x00000001, 0x00000001, D_IM_LTM_MAP2_INT_STATE_MAP_END,      D_IM_LTM_MAP2_INT_FLG_MAP_END      },	// FINEN
		{ 0x00001000, 0x00001000, D_IM_LTM_MAP2_INT_STATE_LINE_END,     ImLtmMapList_D_IM_LTM_MAP2_INT_FLG_LINE_END     },	// LCNTEN
		{ 0x00010000, 0x00010000, ImLtmMapList_D_IM_LTM_MAP2_INT_STATE_HISTINI_END,  ImLtmMapList_D_IM_LTM_MAP2_INT_FLG_HISTINI_END  },	// LCNTEN
		{ 0x00100000, 0x00100000, D_IM_LTM_MAP2_INT_STATE_AXR_ERR,      ImLtmMapList_D_IM_LTM_MAP2_INT_FLG_AXR_ERR      },	// AXREEN
		{ 0x00200000, 0x00200000, D_IM_LTM_MAP2_INT_STATE_AXW_ERR,      ImLtmMapList_D_IM_LTM_MAP2_INT_FLG_AXW_ERR      },	// AXWEEN
		{ 0x02000000, 0x02000000, D_IM_LTM_MAP2_INT_STATE_YLOG_ERR,     ImLtmMapList_D_IM_LTM_MAP2_INT_FLG_YLOG_ERR     },	// RAMEEN
	},
};

static void im_ltm_map_list_constructor(ImLtmMapList *self)
{
//	ImLtmMapListPrivate *priv = IM_LTM_MAP_LIST_GET_PRIVATE(self);
}

static void im_ltm_map_list_destructor(ImLtmMapList *self)
{
//	ImLtmMapListPrivate *priv = IM_LTM_MAP_LIST_GET_PRIVATE(self);
}

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
// Nothing Special
#endif	// CO_DDIM_UTILITY_USE

/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
// Nothing Special
#endif	// CO_DDIM_UTILITY_USE

//---------------------- driver  section -------------------------------
#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
// Nothing Special
#endif	// CO_DDIM_UTILITY_USE

//---------------------- driver  section -------------------------------
#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
// Nothing Special
#endif	// CO_DDIM_UTILITY_USE

/*----------------------------------------------------------------------*/
/* PUBLIC															    */
/*----------------------------------------------------------------------*/
 VOID im_ltm_map_list_im_ltm_map_get_loop_val(ImLtmMapList*self,UCHAR pipe_no, UCHAR* loop_sta, UCHAR* loop_end )
{
	switch( pipe_no ){
		case D_IM_LTM_PIPE1:
			*loop_sta = 0;
			*loop_end = 0;
			break;
		case D_IM_LTM_PIPE2:
			*loop_sta = 1;
			*loop_end = 1;
			break;
//		case D_IM_LTM_PIPE12:
		default:
			*loop_sta = 0;
			*loop_end = 1;
			break;
	}
}

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
// Nothing Special
#endif	// CO_DDIM_UTILITY_USE

INT32 Im_LTM_MAP_Set_FrameStop( UCHAR pipe_no, UCHAR onoff )
{
	ImLtmMapList*imLtmMapList=im_ltm_map_list_get( );

#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_MAP_Set_FrameStop error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );

	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MFRSTP.bit.FRSTP = onoff;

	Im_LTM_Off_Pclk( pipe_no );
	ImLtmMapList_Im_LTM_Dsb();

	return D_DDIM_OK;
}

/* Set MAP parameter hold
*/
INT32 im_ltm_map_list_im_ltm_map_set_paramhold(ImLtmMapList*self,UCHAR pipe_no, const UCHAR hold_enable )
{
	ImLtmMapList*imLtmMapList=im_ltm_map_list_get( );

#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_map_list_im_ltm_map_set_paramhold error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );

	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MPARMSK.bit.PARMSK = hold_enable;

	Im_LTM_Off_Pclk( pipe_no );
	ImLtmMapList_Im_LTM_Dsb();

	return D_DDIM_OK;
}

/* Get MAP busy status.
 */
INT32 im_ltm_map_list_im_ltm_map_get_mapbusy( UCHAR pipe_no, BOOL* const busy_status )
{
	ImLtmMapList*imLtmMapList=im_ltm_map_list_get( );

	ULONG maptrg;

#ifdef CO_PARAM_CHECK
	if( busy_status == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("im_ltm_map_list_im_ltm_map_get_mapbusy error. busy_status = NULL\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no >= D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_map_list_im_ltm_map_get_mapbusy error. pipe_no>=D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );

	maptrg = im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MTRG.bit.TRG;

	Im_LTM_Off_Pclk( pipe_no );

	if( maptrg == ImLtmMapList_D_IM_LTM_MAP_TRG_BUSY ) {
		*busy_status = TRUE;
	}
	else {
		*busy_status = FALSE;
	}
	return D_DDIM_OK;
}

/* Restart MAP process.
 */
INT32 im_ltm_map_list_im_ltm_map_contstart(ImLtmMapList*self,UCHAR pipe_no )
{
	ImLtmMapList*imLtmMapList=im_ltm_map_list_get( );

	UCHAR	loop_cnt, loop_sta, loop_end;

#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_map_list_im_ltm_map_contstart error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// P-clock control
#ifdef CO_DEBUG_PRINT_IM_LTM_MAP
	Ddim_Print(( "im_ltm_map_list_im_ltm_map_contstart on pclk\n" ));
#endif

	im_ltm_map_list_im_ltm_map_get_loop_val(NULL,pipe_no, &loop_sta, &loop_end );

	Im_LTM_On_Pclk( pipe_no );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,loop_cnt)->MSRAMEN.bit.SRAMAEN = D_IM_LTM_ENABLE_ON;
		im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,loop_cnt)->MSRAMEN.bit.RMAENHST = D_IM_LTM_ENABLE_ON;
		im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,loop_cnt)->MSRAMEN.bit.RMAENYN = D_IM_LTM_ENABLE_ON;
		im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,loop_cnt)->MSRAMEN.bit.RMAENRCH = (im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,loop_cnt)->MIOCTL.bit.INSEL == ImLtmMapList_D_IM_LTM_MAP_MODE_RBK_DIRECT) ? D_IM_LTM_ENABLE_OFF : D_IM_LTM_ENABLE_ON;
	}

	ImLtmMapList_IM_LTM_MAP_WAIT_USEC( ImLtmMapList_D_IM_LTM_MAP_SRAM_WAIT_USEC );

	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MTRG.bit.TRG = ImLtmMapList_D_IM_LTM_MAP_TRG_ON;

#ifdef CO_DEBUG_ON_PC
	if( ImLtmMapList_IM_LTM_MAP_CHECK_TARGET_PIPE_NO_1(pipe_no) ){
		gIM_Io_Ltm_Map_Reg_Ptr[D_IM_LTM_PIPE1]->MTRG.bit.TRG = ImLtmMapList_D_IM_LTM_MAP_TRG_BUSY;
	}
	if( ImLtmMapList_IM_LTM_MAP_CHECK_TARGET_PIPE_NO_2(pipe_no) ){
		gIM_Io_Ltm_Map_Reg_Ptr[D_IM_LTM_PIPE2]->MTRG.bit.TRG = ImLtmMapList_D_IM_LTM_MAP_TRG_BUSY;
	}
#endif

#ifdef CO_DEBUG_PRINT_IM_LTM_MAP
	Ddim_Print(( "im_ltm_map_list_im_ltm_map_contstart off pclk\n" ));
#endif
	Im_LTM_Off_Pclk( pipe_no );
	ImLtmMapList_Im_LTM_Dsb();

	return D_DDIM_OK;
}

/* Start MAP process.
 */
INT32 Im_LTM_MAP_Start( UCHAR pipe_no )
{
	ImLtmMapList*imLtmMapList=im_ltm_map_list_get( );

	DDIM_USER_ER		ercd;
	INT32				retcd;
	UCHAR				loop_cnt, loop_sta, loop_end;
	DDIM_USER_FLGPTN	flgptn = 0;

#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_MAP_Start error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_DEBUG_PRINT_IM_LTM_MAP
	Ddim_Print(( "Im_LTM_MAP_Start begin\n" ));
#endif

	// P-clock control
#ifdef CO_DEBUG_PRINT_IM_LTM_MAP
	Ddim_Print(( "Im_LTM_MAP_Start on pclk\n" ));
#endif

	im_ltm_map_list_im_ltm_map_get_loop_val(NULL,pipe_no, &loop_sta, &loop_end );

	Im_LTM_On_Pclk( pipe_no );

	while( 1 ) {	// Pclk enable section
		// Clear of All Interrupt enable & Interrupt status
#ifdef CO_DEBUG_PRINT_IM_LTM_MAP
		Ddim_Print(( "Im_LTM_MAP_Start begin initialize\n" ));
#endif

#ifdef CO_DEBUG_PRINT_IM_LTM_MAP
		Ddim_Print(( "Im_LTM_MAP_Start initialize interrupt\n" ));
#endif
		// Initialized Interrupt
		im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MINT1.word = ImLtmMapList_D_IM_LTM_MAP_MINT1_ALL_CLR;

		for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
			im_ltm_map_list_get_gIM_LTM_MAP_Mng(imLtmMapList,loop_cnt).intStatus = 0;
		}

#ifdef CO_DEBUG_PRINT_IM_LTM_MAP
		Ddim_Print(( "Im_LTM_MAP_Start enable interrupt\n" ));
#endif
		im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MINT0.word = ImLtmMapList_D_IM_LTM_MAP_MINT0_ENABLE;

#ifdef CO_DEBUG_PRINT_IM_LTM_MAP
		Ddim_Print(( "Im_LTM_MAP_Start on clk\n" ));
#endif
		Im_LTM_On_Hclk( pipe_no );
		Im_LTM_On_Aclk( pipe_no );
		Im_LTM_On_RBKClk( pipe_no );

		// Set access enable

		for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
			im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,loop_cnt)->MSRAMEN.bit.SRAMAEN = D_IM_LTM_ENABLE_ON;
			im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,loop_cnt)->MSRAMEN.bit.RMAENHST = D_IM_LTM_ENABLE_ON;
			im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,loop_cnt)->MSRAMEN.bit.RMAENYN = D_IM_LTM_ENABLE_ON;
			im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,loop_cnt)->MSRAMEN.bit.RMAENRCH = (im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,loop_cnt)->MIOCTL.bit.INSEL == ImLtmMapList_D_IM_LTM_MAP_MODE_RBK_DIRECT) ? D_IM_LTM_ENABLE_OFF : D_IM_LTM_ENABLE_ON;
		}

		ImLtmMapList_IM_LTM_MAP_WAIT_USEC( ImLtmMapList_D_IM_LTM_MAP_SRAM_WAIT_USEC );

		for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
			im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,loop_cnt)->MHCPRD.bit.HCPRD = D_IM_LTM_ENABLE_ON;
			im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,loop_cnt)->MHSTINI.bit.HSTINI = D_IM_LTM_ENABLE_ON;
			while( im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,loop_cnt)->MHSTINI.bit.HSTINI == D_IM_LTM_ENABLE_ON
				&& im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,loop_cnt)->MINT1.bit.__HINIFL == 0 ) {
				ImLtmMapList_IM_LTM_MAP_WAIT_USEC( ImLtmMapList_D_IM_LTM_MAP_SRAM_WAIT_USEC );
			}
			im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,loop_cnt)->MHCPRD.bit.HCPRD = D_IM_LTM_ENABLE_OFF;
		}

#ifdef CO_DEBUG_PRINT_IM_LTM_MAP
		Ddim_Print(( "Im_LTM_MAP_Start clear event flag\n" ));
#endif

		// Clear of Event Flag
		if( ImLtmMapList_IM_LTM_MAP_CHECK_TARGET_PIPE_NO_1( pipe_no ) ){
			flgptn |= ImLtmMapList_D_IM_LTM_MAP1_INT_FLG_ALL;
		}
		if( ImLtmMapList_IM_LTM_MAP_CHECK_TARGET_PIPE_NO_2( pipe_no ) ){
			flgptn |= ImLtmMapList_D_IM_LTM_MAP2_INT_FLG_ALL;
		}

		ercd = DDIM_User_Clr_Flg( FID_IM_LTM_MAP, ~flgptn );
		if( ercd != D_DDIM_USER_E_OK ) {
			Ddim_Print(( "Im_LTM_MAP_Start: invalid FID\n" ));
			retcd = D_IM_LTM_SYSTEM_ERROR;
			break;
		}

		im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MTRG.bit.TRG = ImLtmMapList_D_IM_LTM_MAP_TRG_ON;
#ifdef CO_DEBUG_ON_PC
		for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
			im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,loop_cnt)->MTRG.bit.TRG = ImLtmMapList_D_IM_LTM_MAP_TRG_BUSY;
		}
#endif
		retcd = D_DDIM_OK;
		break;
	}

#ifdef CO_DEBUG_PRINT_IM_LTM_MAP
	Ddim_Print(( "Im_LTM_MAP_Start off pclk\n" ));
#endif
	Im_LTM_Off_Pclk( pipe_no );

#ifdef D_IM_LTM_MAP_DEBUG_ON_PC
	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,loop_cnt)->MINT1.word = 0;
		im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,loop_cnt)->MINT1.bit.__FINFL = 1;
		if( im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,loop_cnt)->MLINTLV.bit.LINTLV != 0 ){
			im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,loop_cnt)->MINT1.bit.__LCNTFL = 1;
		}
		Im_LTM_MAP_Int_Handler( loop_cnt );
		im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,loop_cnt)->MINT1.word = 0;
	}
#endif

	ImLtmMapList_Im_LTM_Dsb();

#ifdef CO_DEBUG_PRINT_IM_LTM_MAP
	Ddim_Print(( "Im_LTM_MAP_Start end\n" ));
#endif

	return retcd;
}

/* Stop LTM MAP process
 */
INT32 Im_LTM_MAP_Stop( UCHAR pipe_no )
{
	ImLtmMapList*imLtmMapList=im_ltm_map_list_get( );

	UCHAR loop_cnt, loop_sta, loop_end;

#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_MAP_Stop error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_ltm_map_list_im_ltm_map_get_loop_val(NULL,pipe_no, &loop_sta, &loop_end );

	Im_LTM_On_Pclk( pipe_no );

	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MTRG.bit.TRG = ImLtmMapList_D_IM_LTM_MAP_TRG_OFF;

	ImLtmMapList_Im_LTM_Dsb();
	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		while( im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,loop_cnt)->MTRG.bit.TRG != ImLtmMapList_D_IM_LTM_MAP_TRG_IDLE ) {
#ifdef CO_DEBUG_ON_PC
//			Ddim_Print(( "Im_LTM_MAP_Stop wait loop. %u\n", im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,loop_cnt)->MTRG.bit.TRG ));
			im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,loop_cnt)->MTRG.bit.TRG = ImLtmMapList_D_IM_LTM_MAP_TRG_IDLE;
#endif
			;	// DO NOTHING
		}
	}

	// Clear of All Interrupt disable
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MINT0.word = ImLtmMapList_D_IM_LTM_MAP_MINT0_DISABLE;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MINT1.word = ImLtmMapList_D_IM_LTM_MAP_MINT1_ALL_CLR;

	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MSRAMEN.word = ImLtmMapList_D_IM_LTM_MAP_MSRAMEN_DISABLE;

	Im_LTM_Off_RBKClk( pipe_no );
	Im_LTM_Off_Aclk( pipe_no );
	Im_LTM_Off_Hclk( pipe_no );
	Im_LTM_Off_Pclk( pipe_no );
	ImLtmMapList_Im_LTM_Dsb();

	return D_DDIM_OK;
}

VOID Im_LTM_MAP_Int_Handler(UCHAR pipe_no )
{
	ImLtmMapList*imLtmMapList=im_ltm_map_list_get( );

	UINT32			loopcnt;
	DDIM_USER_ER	ercd;
	ULONG			mint0;
	ULONG			mint1;
	ULONG			mint1_clr;

#ifdef CO_PARAM_CHECK
	if( pipe_no >= D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_MAP_Int_Handler error. pipe_no>=D_IM_LTM_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_DEBUG_PRINT_IM_LTM_MAP
	Ddim_Print(( "Im_LTM_MAP_Int_Handler begin\n" ));
#endif

#ifdef CO_DEBUG_PRINT_IM_LTM_MAP
	Ddim_Print(( "Im_LTM_MAP_Int_Handler on pclk\n" ));
#endif
	Im_LTM_On_Pclk( pipe_no );

	mint0 = im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MINT0.word;
	mint1 = im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MINT1.word;
	mint1_clr = 0;

#ifdef CO_DEBUG_PRINT_IM_LTM_MAP
	Ddim_Print(( "Im_LTM_MAP_Int_Handler mint0=0x%lx, mint1=0x%lx\n", mint0, mint1 ));
#endif

	// Call of Callback API for interrupt status

	for( loopcnt = 0; loopcnt < (sizeof(S_GIM_LTM_MAP_INTTBL[0]) / sizeof(S_GIM_LTM_MAP_INTTBL[0][0])); loopcnt++ ) {
		if( ((mint1 & S_GIM_LTM_MAP_INTTBL[pipe_no][loopcnt].flgBitmask) != 0)
		 && ((mint0 & S_GIM_LTM_MAP_INTTBL[pipe_no][loopcnt].enaBitmask) != 0) ) {

#ifdef CO_DEBUG_PRINT_IM_LTM_MAP
			Ddim_Print(( "Im_LTM_MAP_Int_Handler begin 0x%x\n", S_GIM_LTM_MAP_INTTBL[pipe_no][loopcnt].flgBitmask ));
#endif

			im_ltm_map_list_get_gIM_LTM_MAP_Mng(imLtmMapList,pipe_no).intStatus = S_GIM_LTM_MAP_INTTBL[pipe_no][loopcnt].intStatus;

			mint1_clr |= S_GIM_LTM_MAP_INTTBL[pipe_no][loopcnt].flgBitmask;

			ercd = DDIM_User_Set_Flg( FID_IM_LTM_MAP, S_GIM_LTM_MAP_INTTBL[pipe_no][loopcnt].waitflg );
			if( ercd != D_DDIM_USER_E_OK ) {
				Ddim_Print(( "Im_LTM_MAP_Int_Handler: invalid FID. 0x%lx\n", S_GIM_LTM_MAP_INTTBL[pipe_no][loopcnt].waitflg ));
			}

			if (im_ltm_map_list_get_gIM_LTM_MAP_Mng(imLtmMapList,pipe_no).mapUserHandler) {
				im_ltm_map_list_get_gIM_LTM_MAP_Mng(imLtmMapList,pipe_no).mapUserHandler( (UINT32*)&im_ltm_map_list_get_gIM_LTM_MAP_Mng(imLtmMapList,pipe_no).intStatus, im_ltm_map_list_get_gIM_LTM_MAP_Mng(imLtmMapList,pipe_no).userParam );
			}
		}
	}

	// Clear interrupt
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MINT1.word = mint1_clr;

#ifdef CO_DEBUG_PRINT_IM_LTM_MAP
	Ddim_Print(( "Im_LTM_MAP_Int_Handler mint1=0x%lx\n", im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MINT1.word ));
#endif

#ifdef CO_DEBUG_PRINT_IM_LTM_MAP
	Ddim_Print(( "Im_LTM_MAP_Int_Handler off pclk\n" ));
#endif
	Im_LTM_Off_Pclk( pipe_no );
	ImLtmMapList_Im_LTM_Dsb();

#ifdef CO_DEBUG_PRINT_IM_LTM_MAP
	Ddim_Print(( "Im_LTM_MAP_Int_Handler end\n" ));
#endif
}

/* WB Gain control
 */
INT32 Im_LTM_MAP_Set_WB_Gain( UCHAR pipe_no, const T_IM_LTM_MAP_GAIN* const wb_gain )
{
	ImLtmMapList*imLtmMapList=im_ltm_map_list_get( );

#ifdef CO_PARAM_CHECK
	if( wb_gain == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_LTM_MAP_Set_WB_Gain error. wb_gain = NULL\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_MAP_Set_WB_Gain error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );

	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->GAINR.bit.GAINR = wb_gain->gain_r;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->GAING.bit.GAING = wb_gain->gain_g;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->GAINB.bit.GAINB = wb_gain->gain_b;

	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->GAINCPR.bit.GAINCPR = wb_gain->clip_r;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->GAINCPG.bit.GAINCPG = wb_gain->clip_g;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->GAINCPB.bit.GAINCPB = wb_gain->clip_b;

	Im_LTM_Off_Pclk( pipe_no );
	return D_DDIM_OK;
}

/* Map image Generation mode control
 */
INT32 Im_LTM_MAP_Ctrl_Generation_Mode( UCHAR pipe_no, const T_IM_LTM_MAP_CTRL_GENERATION_MODE* const mode )
{
	ImLtmMapList*imLtmMapList=im_ltm_map_list_get( );

#ifdef CO_PARAM_CHECK
	if( mode == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_LTM_MAP_Ctrl_Generation_Mode error. mode = NULL\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_MAP_Ctrl_Generation_Mode error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );

	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->PEPS0M.bit.PEPS0M     = mode->mode0;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->PEPS0OF.bit.PEPS0OF_3 = mode->coef0;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->PEPS1M.bit.PEPS1M     = mode->mode1;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->PEPS1OF.bit.PEPS1OF_3 = mode->coef1;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->PEPS2M.bit.PEPS2M     = mode->mode2;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->PEPS2OF.bit.PEPS2OF_3 = mode->coef2;

	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->NEPS0M.bit.NEPS0M     = mode->mode0;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->NEPS0OF.bit.NEPS0OF_3 = mode->coef0;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->NEPS1M.bit.NEPS1M     = mode->mode1;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->NEPS1OF.bit.NEPS1OF_3 = mode->coef1;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->NEPS2M.bit.NEPS2M     = mode->mode2;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->NEPS2OF.bit.NEPS2OF_3 = mode->coef2;

	Im_LTM_Off_Pclk( pipe_no );
	return D_DDIM_OK;
}

/* Get internal parameter
 */
INT32 Im_LTM_MAP_Get_Internal_Param( UCHAR pipe_no, T_IM_LTM_INTERNAL_PARAM* const param )
{
	ImLtmMapList*imLtmMapList=im_ltm_map_list_get( );

#ifdef CO_PARAM_CHECK
	if( param == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_LTM_MAP_Get_Internal_Param error. param = NULL\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no >= D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_MAP_Get_Internal_Param error. pipe_no>=D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );

	param->yshadow    = im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->YSHADOW.bit.YSHADOW;
	param->yhighlight = im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->YHIGHLIGHT.bit.YHIGHLIGHT;

	Im_LTM_Off_Pclk( pipe_no );
	return D_DDIM_OK;
}

/* YLOG table control
 */
INT32 Im_LTM_MAP_Ctrl_Ylog_Tbl( UCHAR pipe_no, const T_IM_LTM_CTRL_YLOG* const ylog_ctrl )
{
	ImLtmMapList*imLtmMapList=im_ltm_map_list_get( );

#ifdef CO_PARAM_CHECK
	if( ylog_ctrl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_LTM_MAP_Ctrl_Ylog_Tbl error. ylog_ctrl = NULL\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_MAP_Ctrl_Ylog_Tbl error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );

	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MYLCTL.bit.YLOGSL      = ylog_ctrl->use_tbl;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MYLOG0EP0.bit.YLOG0EP0 = ylog_ctrl->end_point0_tbl0;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MYLOG0EP1.bit.YLOG0EP1 = ylog_ctrl->end_point1_tbl0;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MYLOG1EP0.bit.YLOG1EP0 = ylog_ctrl->end_point0_tbl1;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MYLOG1EP1.bit.YLOG1EP1 = ylog_ctrl->end_point1_tbl1;

	Im_LTM_Off_Pclk( pipe_no );
	return D_DDIM_OK;
}

/* Get active YLOG table No.
 */
INT32 Im_LTM_MAP_Get_Active_Ylog_Tbl_No( UCHAR pipe_no, UCHAR* const tbl_no )
{
	ImLtmMapList*imLtmMapList=im_ltm_map_list_get( );

#ifdef CO_PARAM_CHECK
	if( tbl_no == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_LTM_MAP_Get_Active_Ylog_Tbl_No error. tbl_no = NULL\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no >= D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_MAP_Get_Active_Ylog_Tbl_No error. pipe_no>=D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );

	*tbl_no = im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MYLCTL.bit.YLOGSTA;

	Im_LTM_Off_Pclk( pipe_no );
	return D_DDIM_OK;
}

/* Set YLOG table.
 */
INT32 Im_LTM_MAP_Set_YLOG_Table( UCHAR pipe_no, UCHAR tbl_sel, const USHORT* const src_tbl )
{
	ImLtmMapList*imLtmMapList=im_ltm_map_list_get( );

	UINT32 sram_en;
#ifndef CO_LTM_RDMA_ON
	UINT32 loop_cnt;
	volatile USHORT* dst_tbl;
#endif	// CO_LTM_RDMA_ON

#ifdef CO_PARAM_CHECK
	// check on input pointer
	if(src_tbl == NULL) {
		// Parameter setting error
		Ddim_Assertion(("Im_LTM_MAP_Set_YLOG_Table error. src_tbl = NULL\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_MAP_Set_YLOG_Table error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif

	Im_LTM_On_Pclk( pipe_no );

	sram_en = im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MSRAMEN.word;
	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MSRAMEN.word = ImLtmMapList_D_IM_LTM_MAP_MSRAMEN_ENABLE;

#ifdef CO_LTM_RDMA_ON
	im_ltm_map_set_rdma_val_ylog_table( pipe_no, src_tbl );
#else	// CO_LTM_RDMA_ON
	Im_LTM_On_Hclk( pipe_no );

	switch( tbl_sel ){
		case D_LTM_YLOG_TBL_00:
			dst_tbl = S_GIM_IO_LTM_MAP_TBL_PTR[pipe_no]->MYLOG0TBL0.hword;
			break;
		case D_LTM_YLOG_TBL_10:
			dst_tbl = S_GIM_IO_LTM_MAP_TBL_PTR[pipe_no]->MYLOG1TBL0.hword;
			break;
		case D_LTM_YLOG_TBL_01:
			dst_tbl = S_GIM_IO_LTM_MAP_TBL_PTR[pipe_no]->MYLOG0TBL1.hword;
			break;
//		case D_LTM_YLOG_TBL_11:
		default:
			dst_tbl = S_GIM_IO_LTM_MAP_TBL_PTR[pipe_no]->MYLOG1TBL1.hword;
			break;
	}

	for( loop_cnt = 0; loop_cnt < D_IM_LTM_TABLE_MAX_YLOG; loop_cnt++ ) {
		dst_tbl[loop_cnt] = src_tbl[loop_cnt];
	}

	Im_LTM_Off_Hclk( pipe_no );
#endif	// CO_LTM_RDMA_ON

	im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(imLtmMapList,pipe_no)->MSRAMEN.word = sram_en;

	Im_LTM_Off_Pclk( pipe_no );

	return D_DDIM_OK;
}

#ifdef IM_LTM_MAP_STATUS_PRINT
VOID im_ltm_map_list_im_ltm_map_print_status(ImLtmMapList*self )
{
	ImLtmMapList*imLtmMapList=im_ltm_map_list_get( );

	UINT32 loopcnt;

	for( loopcnt = 0; loopcnt < 2; loopcnt++ ) {
		Ddim_Print(( "PIPE%u:\n", loopcnt ));
		Ddim_Print(( "\tinput_size\n" ));
		Ddim_Print(( "\t\timg_left            = 0x%x\n", im_ltm_map_list_get_gIM_LTM_MAP_Mng(imLtmMapList,loopcnt).inputSize.img_left ));
		Ddim_Print(( "\t\timg_top             = 0x%x\n", im_ltm_map_list_get_gIM_LTM_MAP_Mng(imLtmMapList,loopcnt).inputSize.img_top ));
		Ddim_Print(( "\t\timg_width           = 0x%x\n", im_ltm_map_list_get_gIM_LTM_MAP_Mng(imLtmMapList,loopcnt).inputSize.img_width ));
		Ddim_Print(( "\t\timg_lines           = 0x%x\n", im_ltm_map_list_get_gIM_LTM_MAP_Mng(imLtmMapList,loopcnt).inputSize.img_lines ));
		Ddim_Print(( "\tint_status            = 0x%x\n", im_ltm_map_list_get_gIM_LTM_MAP_Mng(imLtmMapList,loopcnt).intStatus ));
		Ddim_Print(( "\tmap_user_handler      = 0x%x\n", (UINT32)im_ltm_map_list_get_gIM_LTM_MAP_Mng(imLtmMapList,loopcnt).mapUserHandler ));
		Ddim_Print(( "\tuser_param            = 0x%x\n", (UINT32)im_ltm_map_list_get_gIM_LTM_MAP_Mng(imLtmMapList,loopcnt).userParam ));
	}
}

VOID im_ltm_map_list_im_ltm_map_print_accenstatus(ImLtmMapList*self)
{
	UINT32 loopcnt;

	Im_LTM_On_Pclk( D_IM_LTM_PIPE12 );
	for( loopcnt = 0; loopcnt < 2; loopcnt++ ) {
		Ddim_Print(( "SRAMAEN  = 0x%x\n", gIM_Io_Ltm_Map_Reg_Ptr[loopcnt]->MSRAMEN.bit.SRAMAEN ));
		Ddim_Print(( "RMAENYN  = 0x%x\n", gIM_Io_Ltm_Map_Reg_Ptr[loopcnt]->MSRAMEN.bit.RMAENYN ));
		Ddim_Print(( "RMAENRCH = 0x%x\n", gIM_Io_Ltm_Map_Reg_Ptr[loopcnt]->MSRAMEN.bit.RMAENRCH ));
	}
	Im_LTM_Off_Pclk( D_IM_LTM_PIPE12 );
}
#endif

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
#endif	// CO_DDIM_UTILITY_USE

ImLtmMapList*im_ltm_map_list_get(void)
{
	 static ImLtmMapList* self = NULL;
	 if(!self){
		 self = k_object_new(IM_TYPE_LTM_MAP_LIST);
		 self->gIMIoLtmMapRegPtr[D_IM_LTM_PIPE_MAX-2]= &(IO_LTM_P1.MAP);
		 self->gIMIoLtmMapRegPtr[D_IM_LTM_PIPE_MAX-1]=&(IO_LTM_P2.MAP);
		 self->gIMIoLtmMapRegPtr[D_IM_LTM_PIPE_MAX-D_IM_LTM_PIPE_MAX]=&(IO_LTM_P3.MAP) ;

	 }
//	 else{
//		 k_object_ref(self);
//	 }
	return self;
}
