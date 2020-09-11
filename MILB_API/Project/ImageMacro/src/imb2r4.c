
/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :唐萍萍
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年09月开始开发
*/

#include <string.h>
//#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
//#endif
#include "dd_arm.h"

#include "jdsb2r.h"
//#include "imrdma.h"
#include"imb2r.h"
#include"imb2r1.h"
#include"imb2r2.h"
#include"imb2r3.h"
#include "imb2r4.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImB2r4, im_b2r4);
#define IM_B2R4_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImB2r4Private, IM_TYPE_B2R4))

struct _ImB2r4Private
{
	int a;
};

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/

/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/

static void im_b2r4_constructor(ImB2r4 *self)
{
	//ImB2r4Private *priv = IM_B2R4_GET_PRIVATE(self);
}

static void im_b2r4_destructor(ImB2r4 *self)
{
	//ImB2r4Private *priv = IM_B2R4_GET_PRIVATE(self);
}

/*----------------------------------------------------------------------*/
/* Grobal Function														*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
/* Bayer left shift control
 */
INT32 Im_B2R_Ctrl_Left_Shift( UCHAR pipe_no, UCHAR bayer_left_shift, UCHAR saturation_mode )
{
	ImB2r2*	imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	if( bayer_left_shift > D_IM_B2R_BLSFT_4BIT ) {
		// Parameter setting error
		Ddim_Assertion(("Im_B2R_Ctrl_Left_Shift error. bayer_left_shift > D_IM_B2R_BLSFT_4BIT\n"));
		return D_IM_B2R_PARAM_ERROR;
	}
	if( pipe_no > D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Ctrl_Left_Shift error. pipe_no>D_IM_B2R_PIPE12\n" ));
		return D_IM_B2R_PARAM_ERROR;
	}
#endif

	Im_B2R_On_Pclk( pipe_no );
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.OFG.BLSFT.bit.BLSFT  = bayer_left_shift;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.OFG.BLSFT.bit.BLSFMD = saturation_mode;
	Im_B2R_Off_Pclk( pipe_no );

	return D_DDIM_OK;
}

/* WB Gain control
 */
INT32 Im_B2R_Set_WB_Gain( UCHAR pipe_no, const T_IM_B2R_BAYER_COLOR* const b2r_bay_color )
{
	ImB2r2*	imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	// check on input pointer
	if(b2r_bay_color == NULL) {
		// Parameter setting error
		Ddim_Assertion(("Im_B2R_Set_WB_Gain error. bay_color = NULL\n"));
		return D_IM_B2R_PARAM_ERROR;
	}
	if( pipe_no > D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Set_WB_Gain error. pipe_no>D_IM_B2R_PIPE12\n" ));
		return D_IM_B2R_PARAM_ERROR;
	}
#endif

	Im_B2R_On_Pclk( pipe_no );
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.OFG.WBGARB.bit.WBGARR = b2r_bay_color->R;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.OFG.WBGARB.bit.WBGABB = b2r_bay_color->B;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.OFG.WBGAGR.bit.WBGAGR = b2r_bay_color->Gr;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.OFG.WBGAGR.bit.WBGAGB = b2r_bay_color->Gb;
	Im_B2R_Off_Pclk( pipe_no );

	return D_DDIM_OK;
}

/* set AXI bus I/F Control
 */
INT32 Im_B2R_Ctrl_Axi( UCHAR pipe_no, const T_IM_B2R_CTRL_AXI* const b2r_ctrl_axi )
{
	ImB2r2*	imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	// check on input pointer
	if( b2r_ctrl_axi == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_B2R_Ctrl_Axi error. b2r_ctrl_axi = NULL\n"));
		return D_IM_B2R_PARAM_ERROR;
	}
	if( pipe_no > D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Ctrl_Axi error. pipe_no>D_IM_B2R_PIPE12\n" ));
		return D_IM_B2R_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_B2R_On_Pclk( pipe_no );
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBCH.YBRAXCTL.bit.YBRCACHE = b2r_ctrl_axi->ybr.cache_type;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBCH.YBRAXCTL.bit.YBRPROT  = b2r_ctrl_axi->ybr.protect_type;

	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBCH.YBWAXCTL.bit.YBWCACHE_0 = b2r_ctrl_axi->ybw[D_IM_B2R_PORT_0].cache_type;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBCH.YBWAXCTL.bit.YBWPROT_0  = b2r_ctrl_axi->ybw[D_IM_B2R_PORT_0].protect_type;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBCH.YBWAXCTL.bit.YBWCACHE_1 = b2r_ctrl_axi->ybw[D_IM_B2R_PORT_1].cache_type;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBCH.YBWAXCTL.bit.YBWPROT_1  = b2r_ctrl_axi->ybw[D_IM_B2R_PORT_1].protect_type;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBCH.YBWAXCTL.bit.YBWCACHE_2 = b2r_ctrl_axi->ybw[D_IM_B2R_PORT_2].cache_type;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBCH.YBWAXCTL.bit.YBWPROT_2  = b2r_ctrl_axi->ybw[D_IM_B2R_PORT_2].protect_type;
	Im_B2R_Off_Pclk( pipe_no );

	ImB2r1_IM_B2R_DSB();

	return D_DDIM_OK;
}

/* get AXI bus read channel status
 */
INT32 Im_B2R_Get_AxiReadStat( UCHAR pipe_no, T_IM_B2R_AXI_YBR_STAT* const b2r_axi_read_stat )
{
	ImB2r2*	imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	// check on input pointer
	if( b2r_axi_read_stat == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_B2R_Get_AxiReadStat error. b2r_axi_read_stat = NULL\n"));
		return D_IM_B2R_PARAM_ERROR;
	}
	if( pipe_no >= D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Get_AxiReadStat error. pipe_no>=D_IM_B2R_PIPE12\n" ));
		return D_IM_B2R_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_B2R_On_Pclk( pipe_no );
	b2r_axi_read_stat->ybr_axi_stat = im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBCH.YBRAXSTS.bit.YBRRESP;
	Im_B2R_Off_Pclk( pipe_no );

	return D_DDIM_OK;
}

/* get AXI bus write channel status
 */
INT32 Im_B2R_Get_AxiWriteStat( UCHAR pipe_no, T_IM_B2R_AXI_YBW_STAT* const b2r_axi_write_stat )
{
	ImB2r2*	imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	// check on input pointer
	if( b2r_axi_write_stat == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_B2R_Get_AxiWriteStat error. b2r_axi_write_stat = NULL\n"));
		return D_IM_B2R_PARAM_ERROR;
	}
	if( pipe_no >= D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Get_AxiWriteStat error. pipe_no>=D_IM_B2R_PIPE12\n" ));
		return D_IM_B2R_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_B2R_On_Pclk( pipe_no );
	b2r_axi_write_stat->ybw_axi_stat[D_IM_B2R_PORT_0] = im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBCH.YBWAXSTS.bit.YBBRESP_0;
	b2r_axi_write_stat->ybw_axi_stat[D_IM_B2R_PORT_1] = im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBCH.YBWAXSTS.bit.YBBRESP_1;
	b2r_axi_write_stat->ybw_axi_stat[D_IM_B2R_PORT_2] = im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBCH.YBWAXSTS.bit.YBBRESP_2;
	Im_B2R_Off_Pclk( pipe_no );

	return D_DDIM_OK;
}


/* get AXI bus write channel Transfer mode
 */
INT32 Im_B2R_Get_AxiWriteMode( UCHAR pipe_no, T_IM_B2R_AXI_YBW_MODE* const b2r_axi_write_mode )
{
	ImB2r2*	imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	// check on input pointer
	if( b2r_axi_write_mode == NULL ){
		// Parameter setting error
		Ddim_Assertion(("Im_B2R_Get_AxiWriteMode error. b2r_axi_write_mode = NULL\n"));
		return D_IM_B2R_PARAM_ERROR;
	}
	if( pipe_no >= D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Get_AxiWriteMode error. pipe_no>=D_IM_B2R_PIPE12\n" ));
		return D_IM_B2R_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_B2R_On_Pclk( pipe_no );
	b2r_axi_write_mode->out_sel      = im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBCH.YBWAXMD.bit.YBWDOS;
	b2r_axi_write_mode->burst_length = im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBCH.YBWAXMD.bit.YBWBL;
	Im_B2R_Off_Pclk( pipe_no );

	return D_DDIM_OK;
}

/* set AXI bus write channel Transfer mode
 */
INT32 Im_B2R_Set_AxiWriteMode( UCHAR pipe_no, const T_IM_B2R_AXI_YBW_MODE* const b2r_axi_write_mode )
{
	ImB2r2*	imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	// check on input pointer
	if( b2r_axi_write_mode == NULL ){
		// Parameter setting error
		Ddim_Assertion(("Im_B2R_Set_AxiWriteMode error. b2r_axi_write_mode = NULL\n"));
		return D_IM_B2R_PARAM_ERROR;
	}
	if( pipe_no > D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Set_AxiWriteMode error. pipe_no>D_IM_B2R_PIPE12\n" ));
		return D_IM_B2R_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_B2R_On_Pclk( pipe_no );
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBCH.YBWAXMD.bit.YBWDOS = b2r_axi_write_mode->out_sel;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBCH.YBWAXMD.bit.YBWBL  = b2r_axi_write_mode->burst_length;
	Im_B2R_Off_Pclk( pipe_no );

	return D_DDIM_OK;
}

/* Set bank index value
 */
INT32 Im_B2R_Set_OutBankIndex( UCHAR pipe_no, UCHAR bank_index )
{
	ImB2r2*	imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Set_OutBankIndex error. pipe_no>D_IM_B2R_PIPE12\n" ));
		return D_IM_B2R_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_B2R_On_Pclk( pipe_no );
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBW.YBWBANK.bit.BANKPS = bank_index;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBW.YBWBANK.bit.BANKST = 1;
	Im_B2R_Off_Pclk( pipe_no );
	ImB2r1_IM_B2R_DSB();

	return D_DDIM_OK;
}

/* Increment bank index value
 */
INT32 Im_B2R_Inc_OutBankIndex( UCHAR pipe_no )
{
	ImB2r2*	imB2r2=im_b2r2_get();

	UCHAR loop_cnt, loop_sta, loop_end;
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Inc_OutBankIndex error. pipe_no>D_IM_B2R_PIPE12\n" ));
		return D_IM_B2R_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_b2r_get_loop_val( pipe_no, &loop_sta, &loop_end );

	Im_B2R_On_Pclk( pipe_no );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->YBW.YBWBANK.bit.BANKPS = ImB2r1_IM_B2R_INC_BANK_INDEX( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->YBW.YBWBANK.bit.BANKSTS, im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->YBW.YBWCTL.bit.USEBANK +1 );
	}
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBW.YBWBANK.bit.BANKST = 1;
	Im_B2R_Off_Pclk( pipe_no );
	ImB2r1_IM_B2R_DSB();

	return D_DDIM_OK;
}

/* Set YBW External I/F output.
*/
INT32 Im_B2R_Set_ExternalIfOutput( UCHAR pipe_no, const UCHAR ext_out_en, const UCHAR ext_out_alarm )
{
	ImB2r2*	imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Set_ExternalIfOutput error. pipe_no>D_IM_B2R_PIPE12\n" ));
		return D_IM_B2R_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_B2R_On_Pclk( pipe_no );
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->B2R_CMN.DINSEL.bit.EXTOEN   = ext_out_en;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->B2R_CMN.EXALMSL.bit.EXALMSL = ext_out_alarm;
	Im_B2R_Off_Pclk( pipe_no );
	ImB2r1_IM_B2R_DSB();

	return D_DDIM_OK;
}

/* Get YBW External I/F output status.
*/
INT32 Im_B2R_Get_ExternalIfOutput( UCHAR pipe_no, UCHAR* const ext_out_en, UCHAR* const ext_out_alarm )
{
	ImB2r2*	imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	if( pipe_no >= D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Get_ExternalIfOutput error. pipe_no>=D_IM_B2R_PIPE12\n" ));
		return D_IM_B2R_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_B2R_On_Pclk( pipe_no );
	*ext_out_en    = im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->B2R_CMN.DINSEL.bit.EXTOEN;
	*ext_out_alarm = im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->B2R_CMN.EXALMSL.bit.EXALMSL;
	Im_B2R_Off_Pclk( pipe_no );

	return D_DDIM_OK;
}

/* Set Frame stop
 */
INT32 Im_B2R_Set_FrameStop( UCHAR pipe_no, UCHAR onoff )
{
	ImB2r2*	imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Set_FrameStop error. pipe_no>D_IM_B2R_PIPE12\n" ));
		return D_IM_B2R_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_B2R_On_Pclk( pipe_no );
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBR.DINCTL.bit.FRMSTP = onoff;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBR.YBRTRG.bit.YBRTRG = ImB2r1_D_IM_B2R_YBRTRG_ON;
	Im_B2R_Off_Pclk( pipe_no );
	ImB2r1_IM_B2R_DSB();

	return D_DDIM_OK;
}

/* Get YBRch busy status.
 */
INT32 Im_B2R_Get_YbrBusy( UCHAR pipe_no, BOOL* const busy_status )
{
	ULONG ybrtrg;
	ImB2r2*	imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	if( busy_status == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_B2R_Get_YbrBusy error. busy_status = NULL\n"));
		return D_IM_B2R_PARAM_ERROR;
	}
	if( pipe_no >= D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Get_YbrBusy error. pipe_no>=D_IM_B2R_PIPE12\n" ));
		return D_IM_B2R_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_B2R_On_Pclk( pipe_no );
	ybrtrg = im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBR.YBRTRG.bit.YBRTRG;
	Im_B2R_Off_Pclk( pipe_no );

	if( ybrtrg == ImB2r1_D_IM_B2R_YBRTRG_BUSY ) {
		*busy_status = TRUE;
	}
	else {
		*busy_status = FALSE;
	}
	return D_DDIM_OK;
}

/* Get YBR error factor
 */
INT32 Im_B2R_Get_YBR_Error_Factor( UCHAR pipe_no, UINT32* const err_factor )
{
	ImB2r2*	imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	if( err_factor == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_B2R_Get_YBR_Error_Factor error. err_factor = NULL\n"));
		return D_IM_B2R_PARAM_ERROR;
	}
	if( pipe_no >= D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Get_YBR_Error_Factor error. pipe_no>=D_IM_B2R_PIPE12\n" ));
		return D_IM_B2R_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_B2R_On_Pclk( pipe_no );
	*err_factor = im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBR.DINERR.word;
	Im_B2R_Off_Pclk( pipe_no );
	return D_DDIM_OK;
}

/* Trimming control
 */
INT32 Im_B2R_Ctrl_Trimming( UCHAR pipe_no, const T_IM_B2R_CTRL_TRIMMING* const b2r_ctrl_trimming )
{
	USHORT img_top;
	USHORT img_left;
	USHORT img_width;
	USHORT img_lines;
	ImB2r2*	imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	if( b2r_ctrl_trimming == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_B2R_Ctrl_Trimming error. b2r_ctrl_trimming = NULL\n"));
		return D_IM_B2R_PARAM_ERROR;
	}
	if( pipe_no > D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Ctrl_Trimming error. pipe_no>D_IM_B2R_PIPE12\n" ));
		return D_IM_B2R_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_B2R_On_Pclk( pipe_no );
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBW.YBWMD.bit.TRMEN = b2r_ctrl_trimming->trimming_enable;

	// TRMHSTA
	img_left = b2r_ctrl_trimming->start_x;
	img_left = ImB2r1_IM_B2R_MIN( img_left, (USHORT)ImB2r1_D_IM_B2R_TRMHSTA_MAX );
	img_left = ImB2r1_IM_B2R_MAX( img_left, (USHORT)ImB2r1_D_IM_B2R_TRMHSTA_MIN );

	// TRMVSTA
	img_top = b2r_ctrl_trimming->start_y;
	img_top = ImB2r1_IM_B2R_MIN( img_top, (USHORT)ImB2r1_D_IM_B2R_TRMVSTA_MAX );
	img_top = ImB2r1_IM_B2R_MAX( img_top, (USHORT)ImB2r1_D_IM_B2R_TRMVSTA_MIN );

	// TRMHSIZ (2pixels alignment & Advancing)
	img_width = b2r_ctrl_trimming->width;
	img_width = ImB2r1_IM_B2R_MIN( img_width, (USHORT)ImB2r1_D_IM_B2R_TRMHSIZ_MAX );
	img_width = ImB2r1_IM_B2R_MAX( img_width, (USHORT)ImB2r1_D_IM_B2R_TRMHSIZ_MIN );

	// TRMVSIZ
	img_lines = b2r_ctrl_trimming->lines;
	img_lines = ImB2r1_IM_B2R_MIN( img_lines, (USHORT)ImB2r1_D_IM_B2R_TRMVSIZ_MAX );
	img_lines = ImB2r1_IM_B2R_MAX( img_lines, (USHORT)ImB2r1_D_IM_B2R_TRMVSIZ_MIN );

	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBW.YBWTRMH.bit.TRMHSTA = img_left;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBW.YBWTRMH.bit.TRMHSIZ = img_width;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBW.YBWTRMV.bit.TRMVSTA = img_top;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBW.YBWTRMV.bit.TRMVSIZ = img_lines;
	Im_B2R_Off_Pclk( pipe_no );
	return D_DDIM_OK;
}

/* Wait end of B2R macro.
 */
INT32 Im_B2R_WaitEnd( DDIM_USER_FLGPTN* const p_flgptn, DDIM_USER_FLGPTN waiptn, DDIM_USER_TMO tmout )
{
	DDIM_USER_FLGPTN	flgptn;
	DDIM_USER_ER		ercd;

#ifdef CO_DEBUG_PRINT_IM_B2R
	Ddim_Print(( "Im_B2R_WaitEnd begin\n" ));
#endif

#ifdef CO_PARAM_CHECK
	if( (waiptn & D_IM_B2R_INT_FLG_ALL) != waiptn ) {
		// Parameter setting error
		Ddim_Assertion(("Im_B2R_WaitEnd error. waiptn\n"));
		return D_IM_B2R_PARAM_ERROR;
	}
#endif
	ImB2r1_IM_B2R_DSB();

	switch( DDIM_User_Twai_Flg( FID_IM_B2R, waiptn, D_DDIM_USER_TWF_ORW, &flgptn, tmout ) ) {
		case D_DDIM_USER_E_OK:
#ifdef CO_DEBUG_PRINT_IM_B2R
		Ddim_Print(( "Im_B2R_WaitEnd twai_flg OK return\n" ));
#endif
			flgptn = waiptn & flgptn;
			ercd = DDIM_User_Clr_Flg( FID_IM_B2R, ~flgptn );
			if( ercd != D_DDIM_USER_E_OK ) {
				Ddim_Print(( "Im_B2R_Start: invalid FID.\n" ));
				return D_IM_B2R_SYSTEM_ERROR;
			}
			if( p_flgptn != NULL ) {
				*p_flgptn = flgptn;
			}
			return D_DDIM_OK;
		case D_DDIM_USER_E_TMOUT:
#ifdef CO_DEBUG_PRINT_IM_B2R
		Ddim_Print(( "Im_B2R_WaitEnd twai_flg TimeOut return\n" ));
#endif
			return D_IM_B2R_TIMEOUT;
		default:
#ifdef CO_DEBUG_PRINT_IM_B2R
		Ddim_Print(( "Im_B2R_WaitEnd twai_flg NG return\n" ));
#endif
			return D_IM_B2R_PARAM_ERROR;
	}
}

/* High pass filter control
 */
INT32 Im_B2R_Ctrl_HighPassFilter( UCHAR pipe_no, const T_IM_B2R_CTRL_HPF* const b2r_ctrl_hpf )
{
	ImB2r2*	imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	// check on input pointer
	if(b2r_ctrl_hpf == NULL) {
		// Parameter setting error
		Ddim_Assertion(("Im_B2R_Ctrl_HighPassFilter error. b2r_ctrl_cc = NULL\n"));
		return D_IM_B2R_PARAM_ERROR;
	}
	if( pipe_no > D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Ctrl_HighPassFilter error. pipe_no>D_IM_B2R_PIPE12\n" ));
		return D_IM_B2R_PARAM_ERROR;
	}
#endif

#ifdef CO_B2R_RDMA_ON
	im_b2r_set_rdma_val_hpf_ctrl( pipe_no, b2r_ctrl_hpf );
#else	// CO_B2R_RDMA_ON
	Im_B2R_On_Pclk( pipe_no );
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFACTL.bit.HFEEN  = b2r_ctrl_hpf->hpf_enable;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFACTL.bit.HFAFEN = b2r_ctrl_hpf->flat_ctrl_enable;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFACTL.bit.HFAYEN = b2r_ctrl_hpf->y_ctrl_enable;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFK.bit.HFK0      = b2r_ctrl_hpf->hpf_k[0];
	ImB2r1_IM_B2R_SET_REG_SIGNED_A( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFK, union io_b2r_hfk, HFK1, b2r_ctrl_hpf->hpf_k[1] );
	ImB2r1_IM_B2R_SET_REG_SIGNED_A( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFK, union io_b2r_hfk, HFK2, b2r_ctrl_hpf->hpf_k[2] );
	ImB2r1_IM_B2R_SET_REG_SIGNED_A( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFK, union io_b2r_hfk, HFK3, b2r_ctrl_hpf->hpf_k[3] );
	ImB2r1_IM_B2R_SET_REG_SIGNED_A( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFK, union io_b2r_hfk, HFK4, b2r_ctrl_hpf->hpf_k[4] );
	ImB2r1_IM_B2R_SET_REG_SIGNED_A( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFK, union io_b2r_hfk, HFK5, b2r_ctrl_hpf->hpf_k[5] );
	ImB2r1_IM_B2R_SET_REG_SIGNED_A( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFK, union io_b2r_hfk, HFK6, b2r_ctrl_hpf->hpf_k[6] );
	ImB2r1_IM_B2R_SET_REG_SIGNED_A( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFK, union io_b2r_hfk, HFK7, b2r_ctrl_hpf->hpf_k[7] );
	ImB2r1_IM_B2R_SET_REG_SIGNED_A( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFK, union io_b2r_hfk, HFK8, b2r_ctrl_hpf->hpf_k[8] );
	ImB2r1_IM_B2R_SET_REG_SIGNED_A( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFK, union io_b2r_hfk, HFK9, b2r_ctrl_hpf->hpf_k[9] );
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFEFCLP.bit.HFEFCLPP = b2r_ctrl_hpf->hpf_level_clip_p;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFEFCLP.bit.HFEFCLPM = b2r_ctrl_hpf->hpf_level_clip_m;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAFST.bit.HFAFSL    = b2r_ctrl_hpf->flat_scale;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAFST.bit.HFAFTH    = b2r_ctrl_hpf->flat_threshold;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAFGU.bit.HFAFGU    = b2r_ctrl_hpf->flat_gain_limit;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAFCLP.bit.HFAFCLPP = b2r_ctrl_hpf->flat_level_clip_p;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAFCLP.bit.HFAFCLPM = b2r_ctrl_hpf->flat_level_clip_m;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAYC.bit.HFAYC00    = b2r_ctrl_hpf->y_convert_coef[0];
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAYC.bit.HFAYC01    = b2r_ctrl_hpf->y_convert_coef[1];
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAYC.bit.HFAYC02    = b2r_ctrl_hpf->y_convert_coef[2];
	ImB2r1_IM_B2R_SET_REG_SIGNED_A( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAYC, union io_b2r_hfayc, HFAYC10, b2r_ctrl_hpf->y_convert_coef[3] );
	ImB2r1_IM_B2R_SET_REG_SIGNED_A( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAYC, union io_b2r_hfayc, HFAYC11, b2r_ctrl_hpf->y_convert_coef[4] );
	ImB2r1_IM_B2R_SET_REG_SIGNED_A( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAYC, union io_b2r_hfayc, HFAYC12, b2r_ctrl_hpf->y_convert_coef[5] );
	ImB2r1_IM_B2R_SET_REG_SIGNED_A( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAYC, union io_b2r_hfayc, HFAYC20, b2r_ctrl_hpf->y_convert_coef[6] );
	ImB2r1_IM_B2R_SET_REG_SIGNED_A( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAYC, union io_b2r_hfayc, HFAYC21, b2r_ctrl_hpf->y_convert_coef[7] );
	ImB2r1_IM_B2R_SET_REG_SIGNED_A( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAYC, union io_b2r_hfayc, HFAYC22, b2r_ctrl_hpf->y_convert_coef[8] );
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAYOF.bit.HFAYOF_0 = b2r_ctrl_hpf->y_ctrl_offset[0];
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAYOF.bit.HFAYOF_1 = b2r_ctrl_hpf->y_ctrl_offset[1];
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAYOF.bit.HFAYOF_2 = b2r_ctrl_hpf->y_ctrl_offset[2];
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAYOF.bit.HFAYOF_3 = b2r_ctrl_hpf->y_ctrl_offset[3];
	ImB2r1_IM_B2R_SET_REG_SIGNED( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAYGA, union io_b2r_hfayga, HFAYGA_0, b2r_ctrl_hpf->y_ctrl_gain[0] );
	ImB2r1_IM_B2R_SET_REG_SIGNED( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAYGA, union io_b2r_hfayga, HFAYGA_1, b2r_ctrl_hpf->y_ctrl_gain[1] );
	ImB2r1_IM_B2R_SET_REG_SIGNED( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAYGA, union io_b2r_hfayga, HFAYGA_2, b2r_ctrl_hpf->y_ctrl_gain[2] );
	ImB2r1_IM_B2R_SET_REG_SIGNED( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAYGA, union io_b2r_hfayga, HFAYGA_3, b2r_ctrl_hpf->y_ctrl_gain[3] );
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAYBD.bit.HFAYBD_0     = b2r_ctrl_hpf->y_ctrl_border[0];
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAYBD.bit.HFAYBD_1     = b2r_ctrl_hpf->y_ctrl_border[1];
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAYBD.bit.HFAYBD_2     = b2r_ctrl_hpf->y_ctrl_border[2];
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAYBD.bit.HFAYBD_3     = b2r_ctrl_hpf->y_ctrl_border[3];
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAYDIV.bit.HFAYDIV1    = b2r_ctrl_hpf->y_ctrl_gain_posi_dec1;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAYDIV.bit.HFAYDIV2    = b2r_ctrl_hpf->y_ctrl_gain_posi_dec2;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAYCLP.bit.HFAYCLPP    = b2r_ctrl_hpf->y_ctrl_level_clip_p;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAYCLP.bit.HFAYCLPM    = b2r_ctrl_hpf->y_ctrl_level_clip_m;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFACOR.bit.HFACORP      = b2r_ctrl_hpf->y_ctrl_cor_p;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFACOR.bit.HFACORM      = b2r_ctrl_hpf->y_ctrl_cor_m;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFACLP.bit.HFACLPR      = b2r_ctrl_hpf->hpf_add_level_clip_r;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFACLP.bit.HFACLPG      = b2r_ctrl_hpf->hpf_add_level_clip_g;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFACLP.bit.HFACLPB      = b2r_ctrl_hpf->hpf_add_level_clip_b;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFACRVCTL.bit.HFACAE    = b2r_ctrl_hpf->area_a_enable;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFACRVCTL.bit.HFACBE    = b2r_ctrl_hpf->area_b_enable;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFACRVCTL.bit.HFACRVMRG = b2r_ctrl_hpf->area_marge_method;
	ImB2r1_IM_B2R_SET_REG_SIGNED( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFACVAFX, union io_b2r_hfacvafx, HFACRVAFX1, b2r_ctrl_hpf->area_a_ctrl.ellipse_area_focus1_x );
	ImB2r1_IM_B2R_SET_REG_SIGNED( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFACVAFX, union io_b2r_hfacvafx, HFACRVAFY1, b2r_ctrl_hpf->area_a_ctrl.ellipse_area_focus1_y );
	ImB2r1_IM_B2R_SET_REG_SIGNED( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFACVAFX, union io_b2r_hfacvafx, HFACRVAFX2, b2r_ctrl_hpf->area_a_ctrl.ellipse_area_focus2_x );
	ImB2r1_IM_B2R_SET_REG_SIGNED( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFACVAFX, union io_b2r_hfacvafx, HFACRVAFY2, b2r_ctrl_hpf->area_a_ctrl.ellipse_area_focus2_y );
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFACRVASCLOF.bit.HFACRVASCLOF1 = b2r_ctrl_hpf->area_a_ctrl.c_area_scale_offset;
	ImB2r1_IM_B2R_SET_REG_SIGNED( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFACRVASCLGA, union io_b2r_hfacrvasclga, HFACRVASCLGA_0, b2r_ctrl_hpf->area_a_ctrl.c_area_scale_gain[0] );
	ImB2r1_IM_B2R_SET_REG_SIGNED( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFACRVASCLGA, union io_b2r_hfacrvasclga, HFACRVASCLGA_1, b2r_ctrl_hpf->area_a_ctrl.c_area_scale_gain[1] );
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFACRVASCLBD.bit.HFACRVASCLBD1 = b2r_ctrl_hpf->area_a_ctrl.c_area_scale_border;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFACRVASCLCP.bit.HFACRVASCLCPL = b2r_ctrl_hpf->area_a_ctrl.c_area_scale_clip_l;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFACRVASCLCP.bit.HFACRVASCLCPH = b2r_ctrl_hpf->area_a_ctrl.c_area_scale_clip_h;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAYASCLGA.bit.HFAYASCLGA_0    = b2r_ctrl_hpf->area_a_ctrl.y_area_scale_gain[0];
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAYASCLGA.bit.HFAYASCLGA_1    = b2r_ctrl_hpf->area_a_ctrl.y_area_scale_gain[1];
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAYASCLBD.bit.HFAYASCLBD_0    = b2r_ctrl_hpf->area_a_ctrl.y_area_scale_border[0];
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAYASCLBD.bit.HFAYASCLBD_1    = b2r_ctrl_hpf->area_a_ctrl.y_area_scale_border[1];
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAYASCLCLP.bit.HFAYASCLCLPL   = b2r_ctrl_hpf->area_a_ctrl.y_area_scale_clip_l;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAYASCLCLP.bit.HFAYASCLCLPH   = b2r_ctrl_hpf->area_a_ctrl.y_area_scale_clip_h;
	ImB2r1_IM_B2R_SET_REG_SIGNED( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFACVBFX, union io_b2r_hfacvbfx, HFACRVBFX1, b2r_ctrl_hpf->area_b_ctrl.ellipse_area_focus1_x );
	ImB2r1_IM_B2R_SET_REG_SIGNED( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFACVBFX, union io_b2r_hfacvbfx, HFACRVBFY1, b2r_ctrl_hpf->area_b_ctrl.ellipse_area_focus1_y );
	ImB2r1_IM_B2R_SET_REG_SIGNED( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFACVBFX, union io_b2r_hfacvbfx, HFACRVBFX2, b2r_ctrl_hpf->area_b_ctrl.ellipse_area_focus2_x );
	ImB2r1_IM_B2R_SET_REG_SIGNED( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFACVBFX, union io_b2r_hfacvbfx, HFACRVBFY2, b2r_ctrl_hpf->area_b_ctrl.ellipse_area_focus2_y );
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFACRVBSCLOF.bit.HFACRVBSCLOF1 = b2r_ctrl_hpf->area_b_ctrl.c_area_scale_offset;
	ImB2r1_IM_B2R_SET_REG_SIGNED( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFACRVBSCLGA, union io_b2r_hfacrvbsclga, HFACRVBSCLGA_0, b2r_ctrl_hpf->area_b_ctrl.c_area_scale_gain[0] );
	ImB2r1_IM_B2R_SET_REG_SIGNED( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFACRVBSCLGA, union io_b2r_hfacrvbsclga, HFACRVBSCLGA_1, b2r_ctrl_hpf->area_b_ctrl.c_area_scale_gain[1] );
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFACRVBSCLBD.bit.HFACRVBSCLBD1 = b2r_ctrl_hpf->area_b_ctrl.c_area_scale_border;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFACRVBSCLCP.bit.HFACRVBSCLCPL = b2r_ctrl_hpf->area_b_ctrl.c_area_scale_clip_l;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFACRVBSCLCP.bit.HFACRVBSCLCPH = b2r_ctrl_hpf->area_b_ctrl.c_area_scale_clip_h;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAYBSCLGA.bit.HFAYBSCLGA_0    = b2r_ctrl_hpf->area_b_ctrl.y_area_scale_gain[0];
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAYBSCLGA.bit.HFAYBSCLGA_1    = b2r_ctrl_hpf->area_b_ctrl.y_area_scale_gain[1];
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAYBSCLBD.bit.HFAYBSCLBD_0    = b2r_ctrl_hpf->area_b_ctrl.y_area_scale_border[0];
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAYBSCLBD.bit.HFAYBSCLBD_1    = b2r_ctrl_hpf->area_b_ctrl.y_area_scale_border[1];
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAYBSCLCLP.bit.HFAYBSCLCLPL   = b2r_ctrl_hpf->area_b_ctrl.y_area_scale_clip_l;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.HFA.HFAYBSCLCLP.bit.HFAYBSCLCLPH   = b2r_ctrl_hpf->area_b_ctrl.y_area_scale_clip_h;
	Im_B2R_Off_Pclk( pipe_no );
#endif	// CO_B2R_RDMA_ON

	return D_DDIM_OK;
}


//私有转公有
VOID im_b2r_get_loop_val( UCHAR pipe_no, UCHAR* loop_sta, UCHAR* loop_end )
{
	switch( pipe_no ){
		case D_IM_B2R_PIPE1:
			*loop_sta = 0;
			*loop_end = 0;
			break;
		case D_IM_B2R_PIPE2:
			*loop_sta = 1;
			*loop_end = 1;
			break;
//		case D_IM_B2R_PIPE12:
		default:
			*loop_sta = 0;
			*loop_end = 1;
			break;
	}
}

ImB2r4 *im_b2r4_get()
{
	static ImB2r4 *imB2r4 = NULL;
	if(!imB2r4)
		imB2r4 = k_object_new_with_private(IM_TYPE_B2R4,sizeof(ImB2r4Private));
	return imB2r4;
}




