/*
 * imr2y3.c
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-05
*@author              :gonghaotian
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年06月开始开发
*/

#include "imr2y3.h"
#include "imr2y2.h"
#include "imr2yctrl3.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImR2y3, im_r2y3);
#define IM_R2Y3_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImR2y3Private, IM_TYPE_R2Y3))

#define D_IM_R2Y_YYRTRG_ON				(1)
#define D_IM_R2Y_YYRTRG_BUSY			(3)
#define im_r2y_inc_bank_index(bank_index, max)	(((bank_index) + 1) % (max))
// TRMxHSTA register value
#define D_IM_R2Y_TRMHSTA_MIN			(0)
#define D_IM_R2Y_TRMHSTA_MAX			(2262)
// TRMxVSTA register value
#define D_IM_R2Y_TRMVSTA_MIN			(0)
#define D_IM_R2Y_TRMVSTA_MAX			(8886)
// TRMxHSIZ register value
#define D_IM_R2Y_TRMHSIZ_MIN			(96)
#define D_IM_R2Y_TRMHSIZ_MAX			(2360)
// TRMxVSIZ register value
#define D_IM_R2Y_TRMVSIZ_MIN			(72)
#define D_IM_R2Y_TRMVSIZ_MAX			(8960)
// HSTHSTA register value
#define D_IM_R2Y_HSTHSTA_MIN			(0)
#define D_IM_R2Y_HSTHSTA_MAX			(2262)
// HSTHSIZ register value
#define D_IM_R2Y_HSTHSIZ_MIN			(96)
#define D_IM_R2Y_HSTHSIZ_MAX			(2360)
// HSTVSTA register value
#define D_IM_R2Y_HSTVSTA_MIN			(0)
#define D_IM_R2Y_HSTVSTA_MAX			(8886)
// HSTVSIZ register value
#define D_IM_R2Y_HSTVSIZ_MIN			(72)
#define D_IM_R2Y_HSTVSIZ_MAX			(8960)


struct _ImR2y3Private
{
	int a;
};

/*
 * DECLS
 */
static VOID imR2ySetHistogramAccessEnable( UCHAR pipe_no, const UCHAR enable );
static volatile T_IM_R2Y_ACCESS_ENABLE_MANAGE gim_r2y_histogram_accen_ctrl = {
	.ctrl_cnt = { 0, 0 },
	.reg_set_func = imR2ySetHistogramAccessEnable,
};

static VOID imR2ySetRgbDekneeAccessEnable( UCHAR pipe_no, const UCHAR enable );
static volatile T_IM_R2Y_ACCESS_ENABLE_MANAGE gim_r2y_rgb_deknee_accen_ctrl = {
	.ctrl_cnt = { 0, 0 },
	.reg_set_func = imR2ySetRgbDekneeAccessEnable,
};

#ifdef CO_DDIM_UTILITY_USE
#ifdef CO_R2Y_RDMA_ON
static VOID imR2ySetRdmaValDekneeTable( UCHAR pipe_no, E_R2Y_DKN_RGBTBL tbl_type, const USHORT* const src_tbl );
#endif	// CO_R2Y_RDMA_ON
#endif	// CO_DDIM_UTILITY_USE


/*
 * IMPL
 */
static void im_r2y3_constructor(ImR2y3 *self)
{
	ImR2y3Private *priv = IM_R2Y3_GET_PRIVATE(self);
}

static void im_r2y3_destructor(ImR2y3 *self)
{
	ImR2y3Private *priv = IM_R2Y3_GET_PRIVATE(self);
}

static VOID imR2ySetHistogramAccessEnable( UCHAR pipe_no, const UCHAR enable )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

	gIM_Io_R2y_Reg_Ptr[pipe_no]->R2Y_CMN.RAMAEN.bit.HSTAEN = enable;
}

static VOID imR2ySetRgbDekneeAccessEnable( UCHAR pipe_no, const UCHAR enable )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

	gIM_Io_R2y_Reg_Ptr[pipe_no]->R2Y_CMN.RAMAEN.bit.YYRAEN_RGB_DEKNEE = enable;
}
#ifdef CO_DDIM_UTILITY_USE
#ifdef CO_R2Y_RDMA_ON
static VOID imR2ySetRdmaValDekneeTable( UCHAR pipe_no, E_R2Y_DKN_RGBTBL tbl_type, const USHORT* const src_tbl )
{
	T_IM_RDMA_CTRL rdma_ctrl = {
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	switch( tbl_type ){
		case E_R2Y_DKN_RGBTBL_G:
			rdma_ctrl.reg_addr_tbl_addr = (ULONG)&(gIM_R2Y_Deknee_Tbl_G_Addr[pipe_no]);
			break;
		case E_R2Y_DKN_RGBTBL_B:
			rdma_ctrl.reg_addr_tbl_addr = (ULONG)&(gIM_R2Y_Deknee_Tbl_B_Addr[pipe_no]);
			break;
		default:	// E_R2Y_DKN_RGBTBL_R
			rdma_ctrl.reg_addr_tbl_addr = (ULONG)&(gIM_R2Y_Deknee_Tbl_R_Addr[pipe_no]);
			break;
	}
	rdma_ctrl.transfer_byte = sizeof( U_IM_R2Y_CTRL_RDMA_DEKNEE_TBL_VAL );
	rdma_ctrl.reg_data_top_addr = (ULONG)src_tbl;
	im_r2y_utils_start_rdma(imR2yUtils, &rdma_ctrl );
}
#endif	// CO_R2Y_RDMA_ON
#endif	// CO_DDIM_UTILITY_USE

/*
 * PUBLIC
 */
/* Set bank index value
 */
INT32 im_r2y3_set_outbank_index(ImR2y3 *self, UCHAR pipe_no, UCHAR yyw_no, UCHAR bank_index )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

	UCHAR loop_cnt, loop_sta, loop_end;

#ifdef CO_PARAM_CHECK
	if( yyw_no >= D_IM_R2Y_YYW_CH_MAX ) {
		Ddim_Assertion(("im_r2y3_set_outbank_index error. yyw_no >= MAX\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( bank_index >= D_IM_R2Y_YYW_BANK_MAX ) {
		Ddim_Assertion(("im_r2y3_set_outbank_index error. bank_index > MAX\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_set_outbank_index error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_utils_get_loop_val(imR2yUtils, pipe_no, &loop_sta, &loop_end );

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		if( yyw_no == D_IM_R2Y_YYW_CH_0 ) {
			gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK0PS = bank_index;
			if( gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANKST == 0 ) {
				gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK1PS = im_r2y_inc_bank_index( gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK1STS, gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWCTL.bit.USEBANK1 + 1 );
				gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK2PS = im_r2y_inc_bank_index( gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK2STS, gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWCTL.bit.USEBANK2 + 1 );
				gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANKAPS = im_r2y_inc_bank_index( gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANKASTS, gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWCTL.bit.USEBANKA + 1 );
			}
			gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANKST = 1;
		}
		else if( yyw_no == D_IM_R2Y_YYW_CH_1 ) {
			gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK1PS = bank_index;
			if( gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANKST == 0 ) {
				gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK0PS = im_r2y_inc_bank_index( gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK0STS, gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWCTL.bit.USEBANK0 + 1 );
				gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK2PS = im_r2y_inc_bank_index( gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK2STS, gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWCTL.bit.USEBANK2 + 1 );
				gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANKAPS = im_r2y_inc_bank_index( gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANKASTS, gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWCTL.bit.USEBANKA + 1 );
			}
			gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANKST = 1;
		}
		else if( yyw_no == D_IM_R2Y_YYW_CH_2 ) {
			gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK2PS = bank_index;
			if( gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANKST == 0 ) {
				gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK0PS = im_r2y_inc_bank_index( gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK0STS, gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWCTL.bit.USEBANK0 + 1 );
				gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK1PS = im_r2y_inc_bank_index( gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK1STS, gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWCTL.bit.USEBANK1 + 1 );
				gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANKAPS = im_r2y_inc_bank_index( gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANKASTS, gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWCTL.bit.USEBANKA + 1 );
			}
			gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANKST = 1;
		}
		else {
			gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANKAPS = bank_index;
			if( gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANKST == 0 ) {
				gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK0PS = im_r2y_inc_bank_index( gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK0STS, gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWCTL.bit.USEBANK0 + 1 );
				gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK1PS = im_r2y_inc_bank_index( gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK1STS, gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWCTL.bit.USEBANK1 + 1 );
				gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK2PS = im_r2y_inc_bank_index( gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK2STS, gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWCTL.bit.USEBANK2 + 1 );
			}
			gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANKST = 1;
		}
	}

	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
	Im_R2Y_Dsb();

	return D_DDIM_OK;
}

/* Increment bank index value
 */
INT32 im_r2y3_inc_outbank_index(ImR2y3 *self, UCHAR pipe_no, UCHAR yyw_no )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);
	UCHAR loop_cnt, loop_sta, loop_end;

#ifdef CO_PARAM_CHECK
	if( yyw_no >= D_IM_R2Y_YYW_CH_MAX ) {
		Ddim_Assertion(("im_r2y3_inc_outbank_index error. yyw_no >= MAX\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_inc_outbank_index error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_utils_get_loop_val(imR2yUtils, pipe_no, &loop_sta, &loop_end );

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		if( yyw_no == D_IM_R2Y_YYW_CH_0 ) {
			gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK0PS = im_r2y_inc_bank_index( gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK0STS, gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWCTL.bit.USEBANK0 + 1 );
		}
		else if( yyw_no == D_IM_R2Y_YYW_CH_1 ) {
			gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK1PS = im_r2y_inc_bank_index( gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK1STS, gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWCTL.bit.USEBANK1 +1 );
		}
		else if( yyw_no == D_IM_R2Y_YYW_CH_2 ) {
			gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK2PS = im_r2y_inc_bank_index( gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK2STS, gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWCTL.bit.USEBANK2 +1 );
		}
		else {
			gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANKAPS = im_r2y_inc_bank_index( gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANKASTS, gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWCTL.bit.USEBANKA +1 );
		}
		gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANKST = 1;
	}
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
	Im_R2Y_Dsb();

	return D_DDIM_OK;
}

/* R2Y Control (B2R/LTM direct connection mode control)
 */
INT32 im_r2y3_ctrl_mode_direct(ImR2y3 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_DIRECT* const r2y_ctrl_direct )
{
	UCHAR loop_cnt, loop_sta, loop_end;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile T_IM_R2Y_STATE_MNG* gIM_R2Y_State = im_r2y_utils_get_state_mng(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2y_ctrl_direct == NULL ) {
		Ddim_Assertion(("im_r2y3_ctrl_mode_direct error. r2y_ctrl_direct = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_ctrl_mode_direct error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_utils_get_loop_val(imR2yUtils, pipe_no, &loop_sta, &loop_end );

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		if(im_r2y_yyr_is_activated( loop_cnt )){
#ifdef CO_DEBUG_PRINT_IM_R2Y
			Ddim_Print(( "im_r2y3_ctrl_mode_direct error. YYR busy\n" ));
#endif
			im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
			return D_IM_R2Y_MACRO_BUSY;
		}
	}

	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYR.DINCTL.bit.FRMSTP = r2y_ctrl_direct->frame_stop;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYR.DINCTL.bit.B2RDIN = D_IM_R2Y_MODE_DIRECT;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
	Im_R2Y_Dsb();

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		gIM_R2Y_State[loop_cnt].video_photo_mode = D_IM_R2Y_MODE_DIRECT;
	}

	return D_DDIM_OK;
}

/* Set Right side offset(for video format)
 */
INT32 im_r2y3_set_right_side_offset(ImR2y3 *self, UCHAR pipe_no, UCHAR yyw_no, T_IM_R2Y_RIGHTSIDE_OFFSET* offset_byte )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( offset_byte == NULL ) {
		Ddim_Assertion(("im_r2y3_set_right_side_offset error. offset_byte = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( !(yyw_no == D_IM_R2Y_YYW_CH_0 || yyw_no == D_IM_R2Y_YYW_CH_0A) ) {
		Ddim_Assertion(("im_r2y3_set_right_side_offset error. yyw_no != (0 or 0A)\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no >= D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_set_right_side_offset error. pipe_no>=D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	if( yyw_no == D_IM_R2Y_YYW_CH_0 ){
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0OFSX.bit.YYW0OFSX_0 = offset_byte->offset_byte[D_IM_R2Y_YYW_BANK_0];
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0OFSX.bit.YYW0OFSX_1 = offset_byte->offset_byte[D_IM_R2Y_YYW_BANK_1];
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0OFSX.bit.YYW0OFSX_2 = offset_byte->offset_byte[D_IM_R2Y_YYW_BANK_2];
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0OFSX.bit.YYW0OFSX_3 = offset_byte->offset_byte[D_IM_R2Y_YYW_BANK_3];
	}
	else if( yyw_no == D_IM_R2Y_YYW_CH_0A ){
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYWAOFSX.bit.YYWAOFSX_0 = offset_byte->offset_byte[D_IM_R2Y_YYW_BANK_0];
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYWAOFSX.bit.YYWAOFSX_1 = offset_byte->offset_byte[D_IM_R2Y_YYW_BANK_1];
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYWAOFSX.bit.YYWAOFSX_2 = offset_byte->offset_byte[D_IM_R2Y_YYW_BANK_2];
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYWAOFSX.bit.YYWAOFSX_3 = offset_byte->offset_byte[D_IM_R2Y_YYW_BANK_3];
	}
	else{
		// nothing to do.
	}

	return D_DDIM_OK;
}

/* Get Next Address information
 */
INT32 im_r2y3_get_next_outaddr(ImR2y3 *self, UCHAR pipe_no, const UINT32 yyw_no, T_IM_R2Y_OUTADDR_INFO* const r2y_addr )
{
#ifdef CO_PARAM_CHECK
	if( r2y_addr == NULL ) {
		Ddim_Assertion(("im_r2y3_get_next_outaddr error. r2y_addr = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( yyw_no >= D_IM_R2Y_YYW_CH_MAX ) {
		Ddim_Assertion(("im_r2y3_get_next_outaddr error. yyw_no >= MAX\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no >= D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_get_next_outaddr error. pipe_no>=D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_get_next_r2y_addr(im_r2y_new(),  pipe_no, yyw_no, r2y_addr);
	return D_DDIM_OK;
}

/* Get Latest Address information
 */
INT32 im_r2y3_get_latest_outaddr(ImR2y3 *self, UCHAR pipe_no, UINT32 yyw_no, UCHAR* const latest_bank_idx, T_IM_R2Y_OUTADDR_INFO* const latest_addr )
{
#ifdef CO_PARAM_CHECK
	if( latest_addr == NULL ) {
		Ddim_Assertion(("im_r2y3_get_latest_outaddr error. latest_addr = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( yyw_no >= D_IM_R2Y_YYW_CH_MAX ) {
		Ddim_Assertion(("im_r2y3_get_latest_outaddr error. yyw_no >= MAX\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no >= D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_get_latest_outaddr error. pipe_no>=D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_get_latest_addr(im_r2y_new(),  pipe_no, yyw_no, latest_bank_idx, latest_addr);

	return D_DDIM_OK;
}

/* Set YYW0 External I/F output.
 */
INT32 im_r2y3_set_external_if_output(ImR2y3 *self, UCHAR pipe_no, UCHAR output_onoff_ipu, UCHAR output_onoff_cnr )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_set_external_if_output error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0MD.bit.EXTBEN = output_onoff_ipu;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0MD.bit.EXTCEN = output_onoff_cnr;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
	Im_R2Y_Dsb();

	return D_DDIM_OK;
}

/* Get YYW0 External I/F output status.
 */
INT32 im_r2y3_get_external_if_output(ImR2y3 *self, UCHAR pipe_no, UCHAR* const output_onoff_ipu, UCHAR* const output_onoff_cnr )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( output_onoff_ipu == NULL ) {
		Ddim_Assertion(("im_r2y3_get_external_if_output error. output_onoff_ipu = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( output_onoff_cnr == NULL ) {
		Ddim_Assertion(("im_r2y3_get_external_if_output error. output_onoff_cnr = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no >= D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_get_external_if_output error. pipe_no>=D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	*output_onoff_ipu = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0MD.bit.EXTBEN;
	*output_onoff_cnr = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0MD.bit.EXTCEN;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );

	return D_DDIM_OK;
}

/* Set Frame stop
 */
INT32 im_r2y3_set_frame_stop(ImR2y3 *self, UCHAR pipe_no, UCHAR onoff )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_set_frame_stop error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYR.DINCTL.bit.FRMSTP = onoff;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYR.YYRTRG.bit.YYRTRG = D_IM_R2Y_YYRTRG_ON;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
	Im_R2Y_Dsb();

	return D_DDIM_OK;
}

/* Get YYRch busy status.
 */
INT32 im_r2y3_get_yyr_busy(ImR2y3 *self, UCHAR pipe_no, BOOL* const busy_status )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

	ULONG yyrtrg;

#ifdef CO_PARAM_CHECK
	if( busy_status == NULL ) {
		Ddim_Assertion(("im_r2y3_get_yyr_busy error. busy_status = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no >= D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_get_yyr_busy error. pipe_no>=D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	yyrtrg = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYR.YYRTRG.bit.YYRTRG;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );

	if( yyrtrg == D_IM_R2Y_YYRTRG_BUSY ) {
		*busy_status = TRUE;
	}
	else {
		*busy_status = FALSE;
	}

	return D_DDIM_OK;
}

/* Get Horizontal ring pixel padding number
 */
INT32 im_r2y3_get_h_ring_pixs(ImR2y3 *self, UCHAR pipe_no, USHORT* const ring_pixs )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile T_IM_R2Y_STATE_MNG* gIM_R2Y_State = im_r2y_utils_get_state_mng(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( ring_pixs == NULL ) {
		Ddim_Assertion(("im_r2y3_get_h_ring_pixs error. ring_pixs = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no >= D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_get_h_ring_pixs error. pipe_no>=D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*ring_pixs = gIM_R2Y_State[pipe_no].ring_pixs_info.ring_pixs;

	return D_DDIM_OK;
}

/* Trimming control
 */
INT32 im_r2y3_ctrl_trimming(ImR2y3 *self, UCHAR pipe_no, UCHAR yyw_no, const T_IM_R2Y_CTRL_TRIMMING* const r2y_ctrl_trimming )
{
	USHORT img_top;
	USHORT img_left;
	USHORT img_width;
	USHORT img_lines;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile T_IM_R2Y_STATE_MNG* gIM_R2Y_State = im_r2y_utils_get_state_mng(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2y_ctrl_trimming == NULL ) {
		Ddim_Assertion(("im_r2y3_ctrl_trimming error. r2y_ctrl_trimming = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( yyw_no > D_IM_R2Y_YYW_CH_2 ) {
		Ddim_Assertion(("im_r2y3_ctrl_trimming error. yyw_no > D_IM_R2Y_YYW_CH_2\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_ctrl_trimming error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	if( im_r2y_check_target_pipe_no_1( pipe_no ) ){
		gIM_R2Y_State[D_IM_R2Y_PIPE1].trim[yyw_no] = *r2y_ctrl_trimming;
	}
	if( im_r2y_check_target_pipe_no_2( pipe_no ) ){
		gIM_R2Y_State[D_IM_R2Y_PIPE2].trim[yyw_no] = *r2y_ctrl_trimming;
	}

	// TRMxHSTA
	img_left = r2y_ctrl_trimming->trim_window.img_left;
	img_left = im_r2y_min( img_left, (USHORT)D_IM_R2Y_TRMHSTA_MAX );
	img_left = im_r2y_max( img_left, (USHORT)D_IM_R2Y_TRMHSTA_MIN );

	// TRMxVSTA
	img_top = r2y_ctrl_trimming->trim_window.img_top;
	img_top = im_r2y_min( img_top, (USHORT)D_IM_R2Y_TRMVSTA_MAX );
	img_top = im_r2y_max( img_top, (USHORT)D_IM_R2Y_TRMVSTA_MIN );

	// TRMxHSIZ
	img_width = r2y_ctrl_trimming->trim_window.img_width;
	img_width = im_r2y_min( img_width, (USHORT)D_IM_R2Y_TRMHSIZ_MAX );
	img_width = im_r2y_max( img_width, (USHORT)D_IM_R2Y_TRMHSIZ_MIN );

	// TRMxVSIZ
	img_lines = r2y_ctrl_trimming->trim_window.img_lines;
	img_lines = im_r2y_min( img_lines, (USHORT)D_IM_R2Y_TRMVSIZ_MAX );
	img_lines = im_r2y_max( img_lines, (USHORT)D_IM_R2Y_TRMVSIZ_MIN );

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	switch( yyw_no ) {
		case D_IM_R2Y_YYW_CH_0:
			gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0MD.bit.TRM0EN  = r2y_ctrl_trimming->trimming_enable;
			gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.TRM0H.bit.TRM0HSTA = img_left;
			gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.TRM0H.bit.TRM0HSIZ = img_width;
			gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.TRM0V.bit.TRM0VSTA = img_top;
			gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.TRM0V.bit.TRM0VSIZ = img_lines;
			break;
		case D_IM_R2Y_YYW_CH_1:
			gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW1MD.bit.TRM1EN  = r2y_ctrl_trimming->trimming_enable;
			gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.TRM1H.bit.TRM1HSTA = img_left;
			gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.TRM1H.bit.TRM1HSIZ = img_width;
			gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.TRM1V.bit.TRM1VSTA = img_top;
			gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.TRM1V.bit.TRM1VSIZ = img_lines;
			break;
//		case D_IM_R2Y_YYW_CH_2:
		default:
			gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW2MD.bit.TRM2EN  = r2y_ctrl_trimming->trimming_enable;
			gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.TRM2H.bit.TRM2HSTA = img_left;
			gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.TRM2H.bit.TRM2HSIZ = img_width;
			gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.TRM2V.bit.TRM2VSTA = img_top;
			gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.TRM2V.bit.TRM2VSIZ = img_lines;
			break;
	}
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );

	return D_DDIM_OK;
}

/* Trimming control(for external I/F)
 */
INT32 im_r2y3_ctrl_trimming_external(ImR2y3 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_TRIMMING_EXT* const r2y_ctrl_trimming )
{
	USHORT img_top_b;
	USHORT img_left_b;
	USHORT img_width_b;
	USHORT img_lines_b;
	USHORT img_top_c;
	USHORT img_left_c;
	USHORT img_width_c;
	USHORT img_lines_c;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile T_IM_R2Y_STATE_MNG* gIM_R2Y_State = im_r2y_utils_get_state_mng(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2y_ctrl_trimming == NULL ) {
		Ddim_Assertion(("im_r2y3_ctrl_trimming_external error. r2y_ctrl_trimming = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_ctrl_trimming_external error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	if( im_r2y_check_target_pipe_no_1( pipe_no ) ){
		gIM_R2Y_State[D_IM_R2Y_PIPE1].trim_ext = *r2y_ctrl_trimming;
	}
	if( im_r2y_check_target_pipe_no_2( pipe_no ) ){
		gIM_R2Y_State[D_IM_R2Y_PIPE2].trim_ext = *r2y_ctrl_trimming;
	}

	// TRMBHSTA
	img_left_b = r2y_ctrl_trimming->trim_window_b.img_left;
	img_left_b = im_r2y_min( img_left_b, (USHORT)D_IM_R2Y_TRMHSTA_MAX );
	img_left_b = im_r2y_max( img_left_b, (USHORT)D_IM_R2Y_TRMHSTA_MIN );

	// TRMBVSTA
	img_top_b = r2y_ctrl_trimming->trim_window_b.img_top;
	img_top_b = im_r2y_min( img_top_b, (USHORT)D_IM_R2Y_TRMVSTA_MAX );
	img_top_b = im_r2y_max( img_top_b, (USHORT)D_IM_R2Y_TRMVSTA_MIN );

	// TRMBHSIZ
	img_width_b = r2y_ctrl_trimming->trim_window_b.img_width;
	img_width_b = im_r2y_min( img_width_b, (USHORT)D_IM_R2Y_TRMHSIZ_MAX );
	img_width_b = im_r2y_max( img_width_b, (USHORT)D_IM_R2Y_TRMHSIZ_MIN );

	// TRMBVSIZ
	img_lines_b = r2y_ctrl_trimming->trim_window_b.img_lines;
	img_lines_b = im_r2y_min( img_lines_b, (USHORT)D_IM_R2Y_TRMVSIZ_MAX );
	img_lines_b = im_r2y_max( img_lines_b, (USHORT)D_IM_R2Y_TRMVSIZ_MIN );

	// TRMCHSTA
	img_left_c = r2y_ctrl_trimming->trim_window_c.img_left;
	img_left_c = im_r2y_min( img_left_c, (USHORT)D_IM_R2Y_TRMHSTA_MAX );
	img_left_c = im_r2y_max( img_left_c, (USHORT)D_IM_R2Y_TRMHSTA_MIN );

	// TRMCVSTA
	img_top_c = r2y_ctrl_trimming->trim_window_c.img_top;
	img_top_c = im_r2y_min( img_top_c, (USHORT)D_IM_R2Y_TRMVSTA_MAX );
	img_top_c = im_r2y_max( img_top_c, (USHORT)D_IM_R2Y_TRMVSTA_MIN );

	// TRMCHSIZ
	img_width_c = r2y_ctrl_trimming->trim_window_c.img_width;
	img_width_c = im_r2y_min( img_width_c, (USHORT)D_IM_R2Y_TRMHSIZ_MAX );
	img_width_c = im_r2y_max( img_width_c, (USHORT)D_IM_R2Y_TRMHSIZ_MIN );

	// TRMCVSIZ
	img_lines_c = r2y_ctrl_trimming->trim_window_c.img_lines;
	img_lines_c = im_r2y_min( img_lines_c, (USHORT)D_IM_R2Y_TRMVSIZ_MAX );
	img_lines_c = im_r2y_max( img_lines_c, (USHORT)D_IM_R2Y_TRMVSIZ_MIN );

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0MD.bit.TRMBEN  = r2y_ctrl_trimming->trimming_enable_b;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.TRMBH.bit.TRMBHSTA = img_left_b;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.TRMBH.bit.TRMBHSIZ = img_width_b;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.TRMBV.bit.TRMBVSTA = img_top_b;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.TRMBV.bit.TRMBVSIZ = img_lines_b;

	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0MD.bit.TRMCEN  = r2y_ctrl_trimming->trimming_enable_c;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.TRMCH.bit.TRMCHSTA = img_left_c;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.TRMCH.bit.TRMCHSIZ = img_width_c;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.TRMCV.bit.TRMCVSTA = img_top_c;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.TRMCV.bit.TRMCVSIZ = img_lines_c;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );

	return D_DDIM_OK;
}

/* Set Histogram control register
 */
INT32 im_r2y3_ctrl_histogram(ImR2y3 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_HISTOGRAM* const r2y_ctrl_hist )
{
	INT32 retcd = D_DDIM_OK;
	UCHAR loop_cnt, loop_sta, loop_end;
	USHORT img_top;
	USHORT img_left;
	USHORT img_width;
	USHORT img_lines;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2y_ctrl_hist == NULL ) {
		Ddim_Assertion(("im_r2y3_ctrl_histogram error. r2y_ctrl_hist = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_ctrl_histogram error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_utils_get_loop_val(imR2yUtils, pipe_no, &loop_sta, &loop_end );

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	while( 1 ) {

		for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
			if( im_r2y_yyw_is_activated(loop_cnt) && (gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.RAMAEN.bit.HSTAEN == 0) ) {
				retcd = D_IM_R2Y_MACRO_BUSY;
			}
		}

		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.HSTMD.bit.HSTSEL = r2y_ctrl_hist->yyw_no;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.HSTMD.bit.PIT_M  = r2y_ctrl_hist->sampling_pitch;

		// HSTHSTA
		img_left = r2y_ctrl_hist->histogram_area.img_left;
		img_left = im_r2y_min( img_left, (USHORT)D_IM_R2Y_HSTHSTA_MAX );
		img_left = im_r2y_max( img_left, (USHORT)D_IM_R2Y_HSTHSTA_MIN );

		// HSTVSTA
		img_top = r2y_ctrl_hist->histogram_area.img_top;
		img_top = im_r2y_min( img_top, (USHORT)D_IM_R2Y_HSTVSTA_MAX );
		img_top = im_r2y_max( img_top, (USHORT)D_IM_R2Y_HSTVSTA_MIN );

		// HSTHSIZ
		img_width = r2y_ctrl_hist->histogram_area.img_width;
		img_width = im_r2y_min( img_width, (USHORT)D_IM_R2Y_HSTHSIZ_MAX );
		img_width = im_r2y_max( img_width, (USHORT)D_IM_R2Y_HSTHSIZ_MIN );

		// HSTVSIZ
		img_lines = r2y_ctrl_hist->histogram_area.img_lines;
		img_lines = im_r2y_min( img_lines, (USHORT)D_IM_R2Y_HSTVSIZ_MAX );
		img_lines = im_r2y_max( img_lines, (USHORT)D_IM_R2Y_HSTVSIZ_MIN );

		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.HSTH.bit.HSTHSTA = img_left;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.HSTH.bit.HSTHSIZ = img_width;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.HSTV.bit.HSTVSTA = img_top;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.HSTV.bit.HSTVSIZ = img_lines;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.HSTMD.bit.HSTEN  = r2y_ctrl_hist->enable;

		break;
	}
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
	Im_R2Y_Dsb();

	return retcd;
}

/* Get Histogram value
 */
INT32 im_r2y3_get_histogram(ImR2y3 *self, UCHAR pipe_no, T_IM_R2Y_HISTOGRAM_STAT* const status, T_IM_R2Y_HISTOGRAM_ADDR* const dst_addr )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile struct io_r2y_sram** gIM_Io_R2y_Tbl_Ptr = im_r2y_utils_get_io_tbl(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( status == NULL ) {
		Ddim_Assertion(("im_r2y3_get_histogram error. status = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( dst_addr == NULL ) {
		Ddim_Assertion(("im_r2y3_get_histogram error. dst_addr = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no >= D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_get_histogram error. pipe_no>=D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	status->y_overflow = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.HSTMD.bit.YHSOVF;
	status->running_status = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.HSTMD.bit.HSTSTS;
	if( status->running_status == 0 ) {
		im_r2y_clk_on_hclk(im_r2y_clk_new(),  pipe_no );
		im_r2y_ctrl3_copy_reg_to_sdram_ushort(im_r2y_ctrl3_new(),  dst_addr->y_buf,	// Read access only support Word-width. (Hardware specification.)
										 gIM_Io_R2y_Tbl_Ptr[pipe_no]->HSTY.hword,
										 D_IM_R2Y_TABLE_MAX_HISTOGRAM );
		im_r2y_clk_off_hclk(im_r2y_clk_new(),  pipe_no );
	}
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );

	if( status->running_status == 0 ) {
		return D_DDIM_OK;
	}
	else {
		return D_IM_R2Y_MACRO_BUSY;
	}
}

/* Set Histogram ram access enable
 */
INT32 im_r2y3_set_histogram_access_enable(ImR2y3 *self, UCHAR pipe_no, UCHAR hist_enable, UCHAR wait_enable )
{
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_set_histogram_access_enable error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	return im_r2y_set_access_enable(im_r2y2_new(), pipe_no,
									 &gim_r2y_histogram_accen_ctrl,
									 hist_enable,
									 wait_enable,
									 M_IM_R2Y_ASSETION_MSG( "im_r2y3_set_histogram_access_enable error. Macro busy\n" )
									 );
}

/* Set a specific color extraction
 */
INT32 im_r2y3_set_color_extract(ImR2y3 *self, UCHAR pipe_no, const T_IM_R2Y_COLOR_EXTRACT* const r2y_color_extract )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2y_color_extract == NULL ) {
		Ddim_Assertion(("im_r2y3_set_color_extract error. r2y_color_extract = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_set_color_extract error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.PCEMD.bit.PCEEN = r2y_color_extract->extract_enable;
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.PCEXY, union io_r2y_pcexy, PCEX, r2y_color_extract->ref_axis_x );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.PCEXY, union io_r2y_pcexy, PCEY, r2y_color_extract->ref_axis_y );
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );

	return D_DDIM_OK;
}

/* Set chroma scale value
 */
INT32 im_r2y3_set_chroma(ImR2y3 *self, UCHAR pipe_no, const T_IM_R2Y_CHROMA_SCALE* const r2y_chroma_scale )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2y_chroma_scale == NULL ) {
		Ddim_Assertion(("im_r2y3_set_chroma error. r2y_chroma_scale = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_set_chroma error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.PCEC.bit.PCECOF = r2y_chroma_scale->chroma_offset;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.PCEC.bit.PCECGA = r2y_chroma_scale->chroma_gain;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );

	return D_DDIM_OK;
}

/* Set hue scale value
 */
INT32 im_r2y3_set_hue(ImR2y3 *self, UCHAR pipe_no, const T_IM_R2Y_HUE_SCALE* const r2y_hue_scale )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2y_hue_scale == NULL ) {
		Ddim_Assertion(("im_r2y3_set_hue error. r2y_hue_scale = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_set_hue error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.PCEH.bit.PCEHOF = r2y_hue_scale->hue_offset;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.PCEH.bit.PCEHGA = r2y_hue_scale->hue_gain;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );

	return D_DDIM_OK;
}

/* Set RGB Deknee table.
 */
INT32 im_r2y3_set_rgb_deknee_table(ImR2y3 *self, UCHAR pipe_no, E_R2Y_DKN_RGBTBL tbl_type, const USHORT* const src_tbl )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y_sram** gIM_Io_R2y_Tbl_Ptr = im_r2y_utils_get_io_tbl(imR2yUtils);

#ifndef CO_R2Y_RDMA_ON
	UINT32 loop_cnt;
	volatile USHORT* dst_tbl;
#endif	// CO_R2Y_RDMA_ON
	INT32  ercd;

#ifdef CO_PARAM_CHECK
	if(src_tbl == NULL) {
		Ddim_Assertion(("im_r2y3_set_rgb_deknee_table error. src_tbl = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_set_rgb_deknee_table error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif

	while( 1 ) {
		ercd = im_r2y3_set_rgb_deknee_access_enable(im_r2y3_new(),  pipe_no, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_ON );
		if( ercd != D_DDIM_OK ) {
			break;
		}

#ifdef CO_R2Y_RDMA_ON
		imR2ySetRdmaValDekneeTable( pipe_no, tbl_type, src_tbl );
#else	// CO_R2Y_RDMA_ON
		im_r2y_clk_on_hclk(im_r2y_clk_new(),  pipe_no );

		switch( tbl_type ) {
			case E_R2Y_DKN_RGBTBL_G:
				dst_tbl = gIM_Io_R2y_Tbl_Ptr[pipe_no]->DKNTBLG.hword;
				break;
			case E_R2Y_DKN_RGBTBL_B:
				dst_tbl = gIM_Io_R2y_Tbl_Ptr[pipe_no]->DKNTBLB.hword;
				break;
			default:	// E_R2Y_DKN_RGBTBL_R
				dst_tbl = gIM_Io_R2y_Tbl_Ptr[pipe_no]->DKNTBLR.hword;
				break;
		}
		for( loop_cnt = 0; loop_cnt < D_IM_R2Y_TABLE_MAX_RGB_DEKNEE; loop_cnt++ ) {
			dst_tbl[loop_cnt] = src_tbl[loop_cnt];
		}

		im_r2y_clk_off_hclk(im_r2y_clk_new(),  pipe_no );
#endif	// CO_R2Y_RDMA_ON

		ercd = im_r2y3_set_rgb_deknee_access_enable(im_r2y3_new(),  pipe_no, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_OFF );
		if( ercd != D_DDIM_OK ) {
			break;
		}

		ercd = D_DDIM_OK;
		break;
	}

	return ercd;
}

/* Set RGB Deknee access enable
 */
INT32 im_r2y3_set_rgb_deknee_access_enable(ImR2y3 *self, UCHAR pipe_no, UCHAR access_enable, UCHAR wait_enable )
{
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_set_rgb_deknee_access_enable error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	return im_r2y_set_access_enable(im_r2y2_new(), pipe_no,
									 &gim_r2y_rgb_deknee_accen_ctrl,
									 access_enable,
									 wait_enable,
									 M_IM_R2Y_ASSETION_MSG( "im_r2y3_set_rgb_deknee_access_enable error. Macro busy\n" )
									 );
}

ImR2y3 *im_r2y3_new(void)
{
	ImR2y3* self = k_object_new_with_private(IM_TYPE_R2Y3,sizeof(ImR2y3Private));
	return self;
}
