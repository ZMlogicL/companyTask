/*
 * imltmrbk.c
 *
 *  Created on: 2020年9月3日
 *      Author: sns
 */

#include "imltm.h"
#include "imltm1.h"
//#include "im_ltm.h"
#include <string.h>
#include "dd_arm.h"
#include "jdsltm.h"

typedef struct _ImLtmPrivate ImLtmPrivate;

 struct _ImLtmPrivate
{
	int a;
};

K_TYPE_DEFINE_DERIVED(ImLtm, im_ltm, sizeof(ImLtmPrivate),K_TYPE_OBJECT)
#define IM_LTM_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImLtmPrivate, ImLtm_IM_TYPE_LTM))

//static volatile T_IM_LTM_RBK_MNG gIM_LTM_RBK_Mng[D_IM_LTM_PIPE_COUNT];
//static volatile struct io_ltm_ch_rbk* gIM_Io_Ltm_Rbk_Reg_Ptr[ImLtm_D_IM_LTM_PIPE_MAX] = { &(IO_LTM_P1.RBK), &(IO_LTM_P2.RBK), &(IO_LTM_P3.RBK) };

 static VOID imLtmRbkGetLoopVal( UCHAR pipe_no, UCHAR* loop_sta, UCHAR* loop_end );

static void im_ltm_constructor(ImLtm *self)
{
	//ImLtmPrivate *priv = IM_LTM_GET_PRIVATE(self);
}

static void im_ltm_destructor(ImLtm *self)
{
	//ImLtmPrivate *priv = IM_LTM_GET_PRIVATE(self);
}

#ifdef IM_LTM_RBK_STATUS_PRINT
// Calculate LTM RBK output image width
static UINT32 imLtmRbkCalcOutWidth( UCHAR pipe_no )
{
	UINT32 in_pixs;
	UINT32 out_pixs;
	UINT32 ref_pixs;

	if( pipe_no >= ImLtm_D_IM_LTM_PIPE12 ){
		Ddim_Print(( "imLtmRbkCalcOutWidth:pipe_no err\n" ));
		return 0;
	}

	Im_LTM_On_Pclk(pipe_no);
	if( gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RIOCTL.bit.INSEL == D_IM_LTM_RBK_MODE_SRO_DIRECT ) {
		if( gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RIOCTL.bit.SROMD == D_IM_LTM_RBK_SRO_DIRECT_1 ){
			in_pixs = gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->BTHSIZ0.word;
		}
		else{
			in_pixs = gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->BTHSIZ0.word + gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->BTHSIZ1.word;
		}
	}
	else {
		in_pixs = gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RSDRHSZ.word;
	}

	if( gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->HVEN.bit.HVEN == ImLtm_D_IM_LTM_ENABLE_ON ){
		pixs = pixs >> 1;
	}

	if( gIM_LTM_RBK_Mng[pipe_no].resolution_conversion == ImLtm_D_IM_LTM_ENABLE_ON ){
		pixs = pixs >> 1;
	}

	if( gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RTEN.bit.RTEN == ImLtm_D_IM_LTM_ENABLE_ON ){
		if( gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RTHSIZ.word > pixs ){
			pixs = 0xFFFF;
		}
		else{
			pixs = gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RTHSIZ.word;
		}
	}

	Im_LTM_Off_Pclk(pipe_no);

	return out_pixs;
}

// Calculate LTM RBK output image lines
static UINT32 imLtmRbkCalcOutLines( UCHAR pipe_no )
{
	UINT32 pixs;

	if( pipe_no >= ImLtm_D_IM_LTM_PIPE12 ){
		Ddim_Print(( "imLtmRbkCalcOutLines:pipe_no err\n" ));
		return 0;
	}

	Im_LTM_On_Pclk(pipe_no);
	if( gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RIOCTL.bit.INSEL == D_IM_LTM_RBK_MODE_SRO_DIRECT ) {
		if( gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RIOCTL.bit.SROMD == D_IM_LTM_RBK_SRO_DIRECT_1 ){
			in_pixs = gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->BTVSIZ0.word;
		}
		else{
			in_pixs = gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->BTVSIZ0.word;	//  = gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->BTVSIZ1.word
		}
	}
	else {
		in_pixs = gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RSDRVSZ.word;
	}

	if( gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->HVEN.bit.HVEN == ImLtm_D_IM_LTM_ENABLE_ON ){
		pixs = pixs >> 1;
	}

	if( gIM_LTM_RBK_Mng[pipe_no].resolution_conversion == ImLtm_D_IM_LTM_ENABLE_ON ){
		pixs = pixs >> 1;
	}

	if( gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RDCMD.bit.RDCEN == ImLtm_D_IM_LTM_ENABLE_ON ){
		pixs = pixs >> ( gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RDCMD.bit.RDCMD + 1 );
	}

	if( gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RTEN.bit.RTEN == ImLtm_D_IM_LTM_ENABLE_ON ){
		if( gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RTVSIZ.word > pixs ){
			pixs = 0xFFFF;
		}
		else{
			pixs = gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RTVSIZ.word;
		}
	}

	Im_LTM_Off_Pclk(pipe_no);

	return pixs;
}

#endif

static VOID imLtmRbkGetLoopVal( UCHAR pipe_no, UCHAR* loop_sta, UCHAR* loop_end )
{
	switch( pipe_no ){
		case ImLtm_D_IM_LTM_PIPE1:
			*loop_sta = 0;
			*loop_end = 0;
			break;
		case D_IM_LTM_PIPE2:
			*loop_sta = 1;
			*loop_end = 1;
			break;
//		case ImLtm_D_IM_LTM_PIPE12:
		default:
			*loop_sta = 0;
			*loop_end = 1;
			break;
	}
}

INT32 im_ltm_rbk_sw_reset( UCHAR pipe_no )
{
	UCHAR	loop_cnt, loop_sta, loop_end;

#ifdef CO_PARAM_CHECK
	if( pipe_no > ImLtm_D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_rbk_sw_reset error. pipe_no>ImLtm_D_IM_LTM_PIPE12\n" ));
		return ImLtm_D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	imLtmRbkGetLoopVal( pipe_no, &loop_sta, &loop_end );

	Im_LTM_On_Pclk( pipe_no );
	Im_LTM_On_RBKClk( pipe_no );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		if( gIM_Io_Ltm_Rbk_Reg_Ptr[loop_cnt]->RTRG.bit.TRG == D_IM_LTM_RBK_TRG_BUSY ){
			return ImLtm_D_IM_LTM_MACRO_BUSY;
		}
	}
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RBKSR.bit.SR = D_IM_LTM_SR_RESET;

	Im_LTM_Off_RBKClk( pipe_no );
	Im_LTM_Off_Pclk( pipe_no );

	return D_DDIM_OK;
}

INT32 im_ltm_rbk_ctrl_axi( UCHAR pipe_no, const T_IM_LTM_RBK_CTRL_AXI* const ctrl_axi )
{
#ifdef CO_PARAM_CHECK
	// check on input pointer
	if( ctrl_axi == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("im_ltm_rbk_ctrl_axi error. ctrl_axi = NULL\n"));
		return ImLtm_D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no > ImLtm_D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_rbk_ctrl_axi error. pipe_no>ImLtm_D_IM_LTM_PIPE12\n" ));
		return ImLtm_D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RAXICTLR1.bit.ARCACHE_R = ctrl_axi->rch[ImLtm_D_IM_LTM_PORT_R].cache_type;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RAXICTLR1.bit.ARPROT_R  = ctrl_axi->rch[ImLtm_D_IM_LTM_PORT_R].protect_type;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RAXICTLR1.bit.ARCACHE_G = ctrl_axi->rch[ImLtm_D_IM_LTM_PORT_G].cache_type;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RAXICTLR1.bit.ARPROT_G  = ctrl_axi->rch[ImLtm_D_IM_LTM_PORT_G].protect_type;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RAXICTLR1.bit.ARCACHE_B = ctrl_axi->rch[D_IM_LTM_PORT_B].cache_type;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RAXICTLR1.bit.ARPROT_B  = ctrl_axi->rch[D_IM_LTM_PORT_B].protect_type;

	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RAXICTLW1.bit.AWCACHE = ctrl_axi->wch.cache_type;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RAXICTLW1.bit.AWPROT  = ctrl_axi->wch.protect_type;
	Im_LTM_Off_Pclk( pipe_no );

	Im_LTM_Dsb();

	return D_DDIM_OK;
}

INT32 im_ltm_rbk_get_axireadstat( UCHAR pipe_no, T_IM_LTM_RBK_AXI_RCH_STAT* const axi_read_stat )
{
#ifdef CO_PARAM_CHECK
	// check on input pointer
	if( axi_read_stat == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("im_ltm_rbk_get_axireadstat error. axi_read_stat = NULL\n"));
		return ImLtm_D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no >= ImLtm_D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_rbk_get_axireadstat error. pipe_no>=ImLtm_D_IM_LTM_PIPE12\n" ));
		return ImLtm_D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );
	axi_read_stat->rch_axi_stat[ImLtm_D_IM_LTM_PORT_1] = gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RAXIRERR.bit.RRESP_R;
	axi_read_stat->rch_axi_stat[ImLtm_D_IM_LTM_PORT_2] = gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RAXIRERR.bit.RRESP_G;
	axi_read_stat->rch_axi_stat[ImLtm_D_IM_LTM_PORT_3] = gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RAXIRERR.bit.RRESP_B;
	Im_LTM_Off_Pclk( pipe_no );

	return D_DDIM_OK;
}

INT32 im_ltm_rbk_get_axiwritestat( UCHAR pipe_no, T_IM_LTM_RBK_AXI_WCH_STAT* const axi_write_stat )
{
#ifdef CO_PARAM_CHECK
	// check on input pointer
	if( axi_write_stat == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("im_ltm_rbk_get_axiwritestat error. axi_write_stat = NULL\n"));
		return ImLtm_D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no >= ImLtm_D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_rbk_get_axiwritestat error. pipe_no>=ImLtm_D_IM_LTM_PIPE12\n" ));
		return ImLtm_D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );
	axi_write_stat->wch_axi_stat = gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RAXIWERR.bit.WRESP;
	Im_LTM_Off_Pclk( pipe_no );

	return D_DDIM_OK;
}

INT32 im_ltm_rbk_get_axictrlparam( UCHAR pipe_no, T_IM_LTM_RBK_AXI_CTRL_PARAM* const axi_ctrl_prm )
{
#ifdef CO_PARAM_CHECK
	// check on input pointer
	if( axi_ctrl_prm == NULL ){
		// Parameter setting error
		Ddim_Assertion(("im_ltm_rbk_get_axictrlparam error. axi_ctrl_prm = NULL\n"));
		return ImLtm_D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no >= ImLtm_D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_rbk_get_axictrlparam error. pipe_no>=ImLtm_D_IM_LTM_PIPE12\n" ));
		return ImLtm_D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );
	axi_ctrl_prm->rch_burst_length_r = gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RAXIBSIZ.bit.BURSTRR;
	axi_ctrl_prm->rch_burst_length_g = gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RAXIBSIZ.bit.BURSTRG;
	axi_ctrl_prm->rch_burst_length_b = gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RAXIBSIZ.bit.BURSTRB;
	axi_ctrl_prm->wch_burst_length   = gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RAXIBSIZ.bit.BURSTW;
	axi_ctrl_prm->mask_write         = gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RAXIBSIZ.bit.WSTBMSK;
	Im_LTM_Off_Pclk( pipe_no );

	return D_DDIM_OK;
}

INT32 im_ltm_rbk_set_axictrlparam( UCHAR pipe_no, const T_IM_LTM_RBK_AXI_CTRL_PARAM* const axi_ctrl_prm )
{
#ifdef CO_PARAM_CHECK
	// check on input pointer
	if( axi_ctrl_prm == NULL ){
		// Parameter setting error
		Ddim_Assertion(("im_ltm_rbk_set_axictrlparam error. axi_ctrl_prm = NULL\n"));
		return ImLtm_D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no > ImLtm_D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_rbk_set_axictrlparam error. pipe_no>ImLtm_D_IM_LTM_PIPE12\n" ));
		return ImLtm_D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RAXIBSIZ.bit.BURSTRR = axi_ctrl_prm->rch_burst_length_r;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RAXIBSIZ.bit.BURSTRG = axi_ctrl_prm->rch_burst_length_g;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RAXIBSIZ.bit.BURSTRB = axi_ctrl_prm->rch_burst_length_b;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RAXIBSIZ.bit.BURSTW  = axi_ctrl_prm->wch_burst_length;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RAXIBSIZ.bit.WSTBMSK = axi_ctrl_prm->mask_write;
	Im_LTM_Off_Pclk( pipe_no );

	return D_DDIM_OK;
}

INT32 im_ltm_rbk_ctrl_common( UCHAR pipe_no, const T_IM_LTM_RBK_CTRL_COMMON* const rbk_ctrl )
{
	UCHAR	loop_cnt, loop_sta, loop_end;

#ifdef CO_PARAM_CHECK
	if( rbk_ctrl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("im_ltm_rbk_ctrl_common error. rbk_ctrl = NULL\n"));
		return ImLtm_D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no > ImLtm_D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_rbk_ctrl_common error. pipe_no>ImLtm_D_IM_LTM_PIPE12\n" ));
		return ImLtm_D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	imLtmRbkGetLoopVal( pipe_no, &loop_sta, &loop_end );

	Im_LTM_On_Pclk( pipe_no );

	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RLINTLV.bit.LINTLV   = rbk_ctrl->line_intr;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RAXIBSIZ.bit.BURSTW  = rbk_ctrl->burst_length;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RAXIBSIZ.bit.WSTBMSK = rbk_ctrl->mask_write;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RIOCTL.bit.OUTSEL    = rbk_ctrl->out_select;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RIOCTL.bit.W0DTYP    = rbk_ctrl->data_type;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RDCMD.bit.RDCEN      = rbk_ctrl->reduction_enable;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RDCMD.bit.RDCMD      = rbk_ctrl->reduction_mode;

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		// Set Callback pointer
		gIM_LTM_RBK_Mng[loop_cnt].rbk_user_handler = rbk_ctrl->rbk_user_handler;
		gIM_LTM_RBK_Mng[loop_cnt].user_param = rbk_ctrl->user_param;
	}

	Im_LTM_Off_Pclk( pipe_no );

	Im_LTM_Dsb();

	return D_DDIM_OK;
}

INT32 im_ltm_rbk_ctrl_modesdraminput( UCHAR pipe_no, const T_IM_LTM_RBK_CTRL_SDRAM_INPUT* const rbk_ctrl_sdram_input )
{
	UCHAR	loop_cnt, loop_sta, loop_end;

#ifdef CO_PARAM_CHECK
	if( rbk_ctrl_sdram_input == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("im_ltm_rbk_ctrl_modesdraminput error. rbk_ctrl_sdram_input = NULL\n"));
		return ImLtm_D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no > ImLtm_D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_rbk_ctrl_modesdraminput error. pipe_no>ImLtm_D_IM_LTM_PIPE12\n" ));
		return ImLtm_D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	imLtmRbkGetLoopVal( pipe_no, &loop_sta, &loop_end );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		gIM_LTM_RBK_Mng[loop_cnt].input_size = rbk_ctrl_sdram_input->input_rect;
	}

	Im_LTM_On_Pclk( pipe_no );

	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RAXIBSIZ.bit.BURSTRR = rbk_ctrl_sdram_input->burst_length_r;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RAXIBSIZ.bit.BURSTRG = rbk_ctrl_sdram_input->burst_length_g;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RAXIBSIZ.bit.BURSTRB = rbk_ctrl_sdram_input->burst_length_b;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RSDRDEF.bit.SDRDEF   = rbk_ctrl_sdram_input->input_global;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RSDRHSZ.bit.SDRHSZ   = rbk_ctrl_sdram_input->input_rect.img_width;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RSDRVSZ.bit.SDRVSZ   = rbk_ctrl_sdram_input->input_rect.img_lines;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RIOCTL.bit.INSEL     = D_IM_LTM_RBK_MODE_SDRAM_INPUT;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RSFEN.bit.RSFEN      = rbk_ctrl_sdram_input->shift_enable;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->HVEN.bit.HVEN        = ImLtm_D_IM_LTM_ENABLE_ON;

	Im_LTM_Off_Pclk( pipe_no );
	Im_LTM_Dsb();

	return D_DDIM_OK;
}

INT32 im_ltm_rbk_set_inaddr_info( UCHAR pipe_no, const T_IM_LTM_INADDR_INFO* const in_addr )
{
	UINT32 offset;

#ifdef CO_PARAM_CHECK
	if( in_addr == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("im_ltm_rbk_set_inaddr_info error. in_addr = NULL\n"));
		return ImLtm_D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no >= ImLtm_D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_rbk_set_inaddr_info error. pipe_no>=ImLtm_D_IM_LTM_PIPE12\n" ));
		return ImLtm_D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );

	offset = ( gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RSDRDEF.bit.SDRDEF * gIM_LTM_RBK_Mng[pipe_no].input_size.img_top ) + ( gIM_LTM_RBK_Mng[pipe_no].input_size.img_left * 2 );

	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RSDRADR.bit.SDRADR = (UINT32)in_addr->addr_r + offset;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RSDRADG.bit.SDRADG = (UINT32)in_addr->addr_g + offset;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RSDRADB.bit.SDRADB = (UINT32)in_addr->addr_b + offset;

	Im_LTM_Off_Pclk( pipe_no );
	Im_LTM_Dsb();

	return D_DDIM_OK;
}

INT32 im_ltm_rbk_set_outdata_info( UCHAR pipe_no, const T_IM_LTM_RBK_OUTDATA_INFO* const out_data_info )
{
#ifdef CO_PARAM_CHECK
	if( out_data_info == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("im_ltm_rbk_set_outdata_info error. out_data_info = NULL\n"));
		return ImLtm_D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no >= ImLtm_D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_rbk_set_outdata_info error. pipe_no>=ImLtm_D_IM_LTM_PIPE12\n" ));
		return ImLtm_D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );

	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RSDWAD.bit.SDWAD   = (UINT32)out_data_info->addr;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RSDWDEF.bit.SDWDEF = out_data_info->global_width;

	Im_LTM_Off_Pclk( pipe_no );
	Im_LTM_Dsb();

	return D_DDIM_OK;
}

INT32 im_ltm_rbk_ctrl_modesrodirect( UCHAR pipe_no, const T_IM_LTM_RBK_CTRL_SRO_DIRECT* const rbk_ctrl_sro_direct )
{
#ifdef CO_PARAM_CHECK
	if( rbk_ctrl_sro_direct == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("im_ltm_rbk_ctrl_modesrodirect error. rbk_ctrl_sro_direct = NULL\n"));
		return ImLtm_D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no > ImLtm_D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_rbk_ctrl_modesrodirect error. pipe_no>ImLtm_D_IM_LTM_PIPE12\n" ));
		return ImLtm_D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );

	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RIOCTL.bit.INSEL    = D_IM_LTM_RBK_MODE_SRO_DIRECT;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RIOCTL.bit.BAYER0   = rbk_ctrl_sro_direct->top_pixel0;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RIOCTL.bit.BAYER1   = rbk_ctrl_sro_direct->top_pixel1;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RIOCTL.bit.SROMD    = rbk_ctrl_sro_direct->sro_mode;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RSFEN.bit.RSFEN0    = rbk_ctrl_sro_direct->shift_enable0;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RSFEN.bit.RSFEN1    = rbk_ctrl_sro_direct->shift_enable1;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->HVEN.bit.HVEN       = rbk_ctrl_sro_direct->half_reduction_enable;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->BTHSTA0.bit.BTHSTA0 = rbk_ctrl_sro_direct->bayer_trim0.img_left;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->BTVSTA0.bit.BTVSTA0 = rbk_ctrl_sro_direct->bayer_trim0.img_top;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->BTHSIZ0.bit.BTHSIZ0 = rbk_ctrl_sro_direct->bayer_trim0.img_width;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->BTVSIZ0.bit.BTVSIZ0 = rbk_ctrl_sro_direct->bayer_trim0.img_lines;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->BTHSTA1.bit.BTHSTA1 = rbk_ctrl_sro_direct->bayer_trim1.img_left;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->BTVSTA1.bit.BTVSTA1 = rbk_ctrl_sro_direct->bayer_trim1.img_top;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->BTHSIZ1.bit.BTHSIZ1 = rbk_ctrl_sro_direct->bayer_trim1.img_width;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->BTVSIZ1.bit.BTVSIZ1 = rbk_ctrl_sro_direct->bayer_trim1.img_lines;

	Im_LTM_Off_Pclk( pipe_no );
	Im_LTM_Dsb();

	return D_DDIM_OK;
}

INT32 im_ltm_rbk_ctrl_resolution_conversion( UCHAR pipe_no, const UCHAR conversion_on_off )
{
#ifdef CO_PARAM_CHECK
	if( pipe_no > ImLtm_D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_rbk_ctrl_resolution_conversion error. pipe_no>ImLtm_D_IM_LTM_PIPE12\n" ));
		return ImLtm_D_IM_LTM_PARAM_ERROR;
	}
#endif

	Im_LTM_On_Pclk( pipe_no );

	if( conversion_on_off == ImLtm_D_IM_LTM_ENABLE_ON ){
		gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RHSTA.bit.HSTA = 0x2000;
		gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RHPIT.bit.HPIT = 0x8000;
		gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RVSTA.bit.VSTA = 0x2000;
		gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RVPIT.bit.VPIT = 0x8000;
	}
	else{
		gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RHSTA.bit.HSTA = 0;
		gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RHPIT.bit.HPIT = 0x4000;
		gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RVSTA.bit.VSTA = 0;
		gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RVPIT.bit.VPIT = 0x4000;
	}

	Im_LTM_Off_Pclk( pipe_no );
	Im_LTM_Dsb();

	return D_DDIM_OK;
}

INT32 im_ltm_rbk_set_framestop( UCHAR pipe_no, UCHAR onoff )
{
#ifdef CO_PARAM_CHECK
	if( pipe_no > ImLtm_D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_rbk_set_framestop error. pipe_no>ImLtm_D_IM_LTM_PIPE12\n" ));
		return ImLtm_D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );

	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RFRSTP.bit.FRSTP = onoff;

	Im_LTM_Off_Pclk( pipe_no );
	Im_LTM_Dsb();

	return D_DDIM_OK;
}

INT32 im_ltm_rbk_set_paramhold( UCHAR pipe_no, const UCHAR hold_enable )
{
#ifdef CO_PARAM_CHECK
	if( pipe_no > ImLtm_D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_rbk_set_paramhold error. pipe_no>ImLtm_D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );

	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RPARMSK.bit.PARMSK = hold_enable;

	Im_LTM_Off_Pclk( pipe_no );
	Im_LTM_Dsb();

	return D_DDIM_OK;
}

INT32 im_ltm_rbk_get_rbkbusy( UCHAR pipe_no, BOOL* const busy_status )
{
	ULONG rbktrg;

#ifdef CO_PARAM_CHECK
	if( busy_status == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("im_ltm_rbk_get_rbkbusy error. busy_status = NULL\n"));
		return ImLtm_D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no >= ImLtm_D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_rbk_get_rbkbusy error. pipe_no>=ImLtm_D_IM_LTM_PIPE12\n" ));
		return ImLtm_D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );

	rbktrg = gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RTRG.bit.TRG;

	Im_LTM_Off_Pclk( pipe_no );

	if( rbktrg == D_IM_LTM_RBK_TRG_BUSY ) {
		*busy_status = TRUE;
	}
	else {
		*busy_status = FALSE;
	}
	return D_DDIM_OK;
}

INT32 im_ltm_rbk_contstart( UCHAR pipe_no )
{
	UCHAR	loop_cnt, loop_sta, loop_end;

#ifdef CO_PARAM_CHECK
	if( pipe_no > ImLtm_D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_rbk_contstart error. pipe_no>ImLtm_D_IM_LTM_PIPE12\n" ));
		return ImLtm_D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// P-clock control
#ifdef CO_DEBUG_PRINT_IM_LTM_RBK
	Ddim_Print(( "im_ltm_rbk_contstart on pclk\n" ));
#endif

	imLtmRbkGetLoopVal( pipe_no, &loop_sta, &loop_end );

	Im_LTM_On_Pclk( pipe_no );

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

	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RTRG.bit.TRG = D_IM_LTM_RBK_TRG_ON;
#ifdef CO_DEBUG_ON_PC
	if( im_ltm_rbk_check_target_pipe_no_1(pipe_no) ){
		gIM_Io_Ltm_Rbk_Reg_Ptr[ImLtm_D_IM_LTM_PIPE1]->RTRG.bit.TRG = D_IM_LTM_RBK_TRG_BUSY;
	}
	if( im_ltm_rbk_check_target_pipe_no_2(pipe_no) ){
		gIM_Io_Ltm_Rbk_Reg_Ptr[D_IM_LTM_PIPE2]->RTRG.bit.TRG = D_IM_LTM_RBK_TRG_BUSY;
	}
#endif

#ifdef CO_DEBUG_PRINT_IM_LTM_RBK
	Ddim_Print(( "im_ltm_rbk_contstart off pclk\n" ));
#endif
	Im_LTM_Off_Pclk( pipe_no );
	Im_LTM_Dsb();

	return D_DDIM_OK;
}

INT32 im_ltm_rbk_stop( UCHAR pipe_no )
{
	UCHAR loop_cnt, loop_sta, loop_end;

#ifdef CO_PARAM_CHECK
	if( pipe_no > ImLtm_D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_rbk_stop error. pipe_no>ImLtm_D_IM_LTM_PIPE12\n" ));
		return ImLtm_D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	imLtmRbkGetLoopVal( pipe_no, &loop_sta, &loop_end );

	Im_LTM_On_Pclk( pipe_no );

	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RTRG.bit.TRG = D_IM_LTM_RBK_TRG_OFF;

	Im_LTM_Dsb();
	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		while( gIM_Io_Ltm_Rbk_Reg_Ptr[loop_cnt]->RTRG.bit.TRG != D_IM_LTM_RBK_TRG_IDLE ) {
#ifdef CO_DEBUG_ON_PC
//			Ddim_Print(( "im_ltm_rbk_stop wait loop. %u\n", gIM_Io_Ltm_Rbk_Reg_Ptr[loop_cnt]->RTRG.bit.TRG ));
			gIM_Io_Ltm_Rbk_Reg_Ptr[loop_cnt]->RTRG.bit.TRG = D_IM_LTM_RBK_TRG_IDLE;
#endif
			;	// DO NOTHING
		}
	}

	// Clear of All Interrupt disable
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RINT0.word = D_IM_LTM_RBK_RINT0_DISABLE;
	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RINT1.word = D_IM_LTM_RBK_RINT1_ALL_CLR;

	gIM_Io_Ltm_Rbk_Reg_Ptr[pipe_no]->RSRAMEN.word = D_IM_LTM_RBK_RSRAMEN_DISABLE;

	Im_LTM_Off_RBKClk( pipe_no );
	Im_LTM_Off_Aclk( pipe_no );
	Im_LTM_Off_Pclk( pipe_no );
	Im_LTM_Dsb();

	return D_DDIM_OK;
}

INT32 im_ltm_rbk_waitend( DDIM_USER_FLGPTN* const p_flgptn, DDIM_USER_FLGPTN waiptn, DDIM_USER_TMO tmout )
{
	DDIM_USER_FLGPTN	flgptn;
	DDIM_USER_ER		ercd;

#ifdef CO_DEBUG_PRINT_IM_LTM_RBK
	Ddim_Print(( "im_ltm_rbk_waitend begin\n" ));
#endif

#ifdef CO_PARAM_CHECK
	if( (waiptn & D_IM_LTM_RBK_INT_FLG_ALL) != waiptn ) {
		// Parameter setting error
		Ddim_Assertion(("im_ltm_rbk_waitend error. waiptn\n"));
		return ImLtm_D_IM_LTM_PARAM_ERROR;
	}
#endif
	Im_LTM_Dsb();

	switch( DDIM_User_Twai_Flg( FID_IM_LTM_RBK, waiptn, D_DDIM_USER_TWF_ORW, &flgptn, tmout ) ) {
		case D_DDIM_USER_E_OK:
#ifdef CO_DEBUG_PRINT_IM_LTM_RBK
		Ddim_Print(( "im_ltm_rbk_waitend twai_flg OK return\n" ));
#endif
			flgptn = waiptn & flgptn;
			ercd = DDIM_User_Clr_Flg( FID_IM_LTM_RBK, ~flgptn );
			if( ercd != D_DDIM_USER_E_OK ) {
				Ddim_Print(( "im_ltm_rbk_waitend: invalid FID.\n" ));
				return ImLtm_D_IM_LTM_SYSTEM_ERROR;
			}
			if( p_flgptn != NULL ) {
				*p_flgptn = flgptn;
			}
			return D_DDIM_OK;
		case D_DDIM_USER_E_TMOUT:
#ifdef CO_DEBUG_PRINT_IM_LTM_RBK
		Ddim_Print(( "im_ltm_rbk_waitend twai_flg TimeOut return\n" ));
#endif
			return ImLtm_D_IM_LTM_TIMEOUT;
		default:
#ifdef CO_DEBUG_PRINT_IM_LTM_RBK
		Ddim_Print(( "im_ltm_rbk_waitend twai_flg NG return\n" ));
#endif
			return ImLtm_D_IM_LTM_PARAM_ERROR;
	}
}

#ifdef IM_LTM_RBK_STATUS_PRINT
VOID im_ltm_rbk_print_status( VOID )
{
	UINT32 loopcnt;

	for( loopcnt = 0; loopcnt < 2; loopcnt++ ) {
		Ddim_Print(( "PIPE%u:\n", loopcnt ));
		Ddim_Print(( "\tinput_size\n" ));
		Ddim_Print(( "\t\timg_left            = 0x%x\n", gIM_LTM_RBK_Mng[loopcnt].input_size.img_left ));
		Ddim_Print(( "\t\timg_top             = 0x%x\n", gIM_LTM_RBK_Mng[loopcnt].input_size.img_top ));
		Ddim_Print(( "\t\timg_width           = 0x%x\n", gIM_LTM_RBK_Mng[loopcnt].input_size.img_width ));
		Ddim_Print(( "\t\timg_lines           = 0x%x\n", gIM_LTM_RBK_Mng[loopcnt].input_size.img_lines ));
		Ddim_Print(( "\tint_status            = 0x%x\n", gIM_LTM_RBK_Mng[loopcnt].int_status ));
		Ddim_Print(( "\tresolution_conversion = 0x%x\n", gIM_LTM_RBK_Mng[loopcnt].resolution_conversion ));
		Ddim_Print(( "\trbk_user_handler      = 0x%x\n", (UINT32)gIM_LTM_RBK_Mng[loopcnt].rbk_user_handler ));
		Ddim_Print(( "\tuser_param            = 0x%x\n", (UINT32)gIM_LTM_RBK_Mng[loopcnt].user_param ));
	}
}

VOID im_ltm_rbk_print_accenstatus( VOID )
{
	UINT32 loopcnt;

	Im_LTM_On_Pclk( ImLtm_D_IM_LTM_PIPE12 );
	for( loopcnt = 0; loopcnt < 2; loopcnt++ ) {
		Ddim_Print(( "SRAMAEN  = 0x%x\n", gIM_Io_Ltm_Rbk_Reg_Ptr[loopcnt]->RSRAMEN.bit.SRAMAEN ));
		Ddim_Print(( "RMAENLB1 = 0x%x\n", gIM_Io_Ltm_Rbk_Reg_Ptr[loopcnt]->RSRAMEN.bit.RMAENLB1 ));
		Ddim_Print(( "RMAENLB2 = 0x%x\n", gIM_Io_Ltm_Rbk_Reg_Ptr[loopcnt]->RSRAMEN.bit.RMAENLB2 ));
		Ddim_Print(( "RMAENHST = 0x%x\n", gIM_Io_Ltm_Rbk_Reg_Ptr[loopcnt]->RSRAMEN.bit.RMAENHST ));
		Ddim_Print(( "RMAENSRO = 0x%x\n", gIM_Io_Ltm_Rbk_Reg_Ptr[loopcnt]->RSRAMEN.bit.RMAENSRO ));
		Ddim_Print(( "RMAENWCH = 0x%x\n", gIM_Io_Ltm_Rbk_Reg_Ptr[loopcnt]->RSRAMEN.bit.RMAENWCH ));
		Ddim_Print(( "RMAENRCH = 0x%x\n", gIM_Io_Ltm_Rbk_Reg_Ptr[loopcnt]->RSRAMEN.bit.RMAENRCH ));
	}
	Im_LTM_Off_Pclk( ImLtm_D_IM_LTM_PIPE12 );
}
#endif

ImLtm *im_ltm_new(void)
{
	ImLtm* self = k_object_new(ImLtm_IM_TYPE_LTM);
	return self;
}
