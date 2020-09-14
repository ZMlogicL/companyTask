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
#define im_r2y_inc_bank_index(bankIndex, max)	(((bankIndex) + 1) % (max))
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
static void imR2ySetHistogramAccessEnable( kuint16 pipeNo, const kuint16 enable );
static volatile R2yAccessEnableManage gim_r2y_histogram_accen_ctrl = {
	.ctrlCnt = { 0, 0 },
	.reg_set_func = imR2ySetHistogramAccessEnable,
};

static void imR2ySetRgbDekneeAccessEnable( kuint16 pipeNo, const kuint16 enable );
static volatile R2yAccessEnableManage gim_r2y_rgb_deknee_accen_ctrl = {
	.ctrlCnt = { 0, 0 },
	.reg_set_func = imR2ySetRgbDekneeAccessEnable,
};

#ifdef CO_DDIM_UTILITY_USE
#ifdef CO_R2Y_RDMA_ON
static void imR2ySetRdmaValDekneeTable( kuint16 pipeNo, ER2yDknRgbtbl tbl_type, const kuint16* const src_tbl );
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

static void imR2ySetHistogramAccessEnable( kuint16 pipeNo, const kuint16 enable )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

	gImIoR2yRegPtr[pipeNo]->R2Y_CMN.RAMAEN.bit.HSTAEN = enable;
}

static void imR2ySetRgbDekneeAccessEnable( kuint16 pipeNo, const kuint16 enable )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

	gImIoR2yRegPtr[pipeNo]->R2Y_CMN.RAMAEN.bit.YYRAEN_RGB_DEKNEE = enable;
}
#ifdef CO_DDIM_UTILITY_USE
#ifdef CO_R2Y_RDMA_ON
static void imR2ySetRdmaValDekneeTable( kuint16 pipeNo, ER2yDknRgbtbl tbl_type, const kuint16* const src_tbl )
{
	T_IM_RDMA_CTRL rdma_ctrl = {
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	switch( tbl_type ){
		case ImR2y_DKN_RGBTBL_G:
			rdma_ctrl.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_Deknee_Tbl_G_Addr[pipeNo]);
			break;
		case ImR2y_DKN_RGBTBL_B:
			rdma_ctrl.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_Deknee_Tbl_B_Addr[pipeNo]);
			break;
		default:	// ImR2y_DKN_RGBTBL_R
			rdma_ctrl.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_Deknee_Tbl_R_Addr[pipeNo]);
			break;
	}
	rdma_ctrl.transfer_byte = sizeof( RdmaDekneeTblVal );
	rdma_ctrl.reg_data_top_addr = (kulong)src_tbl;
	im_r2y_utils_start_rdma(imR2yUtils, &rdma_ctrl );
}
#endif	// CO_R2Y_RDMA_ON
#endif	// CO_DDIM_UTILITY_USE

/*
 * PUBLIC
 */
/* Set bank index value
 */
INT32 im_r2y3_set_outbank_index(ImR2y3 *self, kuint16 pipeNo, kuint16 yywNo, kuint16 bankIndex )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

	kuint16 loop_cnt, loop_sta, loop_end;

#ifdef CO_PARAM_CHECK
	if( yywNo >= ImR2yCtrl_YYW_CH_MAX ) {
		Ddim_Assertion(("im_r2y3_set_outbank_index error. yywNo >= MAX\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( bankIndex >= ImR2yCtrl_YYW_BANK_MAX ) {
		Ddim_Assertion(("im_r2y3_set_outbank_index error. bankIndex > MAX\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_set_outbank_index error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_utils_get_loop_val(imR2yUtils, pipeNo, &loop_sta, &loop_end );

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		if( yywNo == ImR2yCtrl_YYW_CH_0 ) {
			gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK0PS = bankIndex;
			if( gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANKST == 0 ) {
				gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK1PS = im_r2y_inc_bank_index( gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK1STS, gImIoR2yRegPtr[loop_cnt]->YYW.YYWCTL.bit.USEBANK1 + 1 );
				gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK2PS = im_r2y_inc_bank_index( gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK2STS, gImIoR2yRegPtr[loop_cnt]->YYW.YYWCTL.bit.USEBANK2 + 1 );
				gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANKAPS = im_r2y_inc_bank_index( gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANKASTS, gImIoR2yRegPtr[loop_cnt]->YYW.YYWCTL.bit.USEBANKA + 1 );
			}
			gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANKST = 1;
		}
		else if( yywNo == ImR2yCtrl_YYW_CH_1 ) {
			gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK1PS = bankIndex;
			if( gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANKST == 0 ) {
				gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK0PS = im_r2y_inc_bank_index( gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK0STS, gImIoR2yRegPtr[loop_cnt]->YYW.YYWCTL.bit.USEBANK0 + 1 );
				gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK2PS = im_r2y_inc_bank_index( gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK2STS, gImIoR2yRegPtr[loop_cnt]->YYW.YYWCTL.bit.USEBANK2 + 1 );
				gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANKAPS = im_r2y_inc_bank_index( gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANKASTS, gImIoR2yRegPtr[loop_cnt]->YYW.YYWCTL.bit.USEBANKA + 1 );
			}
			gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANKST = 1;
		}
		else if( yywNo == ImR2yCtrl_YYW_CH_2 ) {
			gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK2PS = bankIndex;
			if( gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANKST == 0 ) {
				gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK0PS = im_r2y_inc_bank_index( gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK0STS, gImIoR2yRegPtr[loop_cnt]->YYW.YYWCTL.bit.USEBANK0 + 1 );
				gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK1PS = im_r2y_inc_bank_index( gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK1STS, gImIoR2yRegPtr[loop_cnt]->YYW.YYWCTL.bit.USEBANK1 + 1 );
				gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANKAPS = im_r2y_inc_bank_index( gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANKASTS, gImIoR2yRegPtr[loop_cnt]->YYW.YYWCTL.bit.USEBANKA + 1 );
			}
			gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANKST = 1;
		}
		else {
			gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANKAPS = bankIndex;
			if( gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANKST == 0 ) {
				gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK0PS = im_r2y_inc_bank_index( gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK0STS, gImIoR2yRegPtr[loop_cnt]->YYW.YYWCTL.bit.USEBANK0 + 1 );
				gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK1PS = im_r2y_inc_bank_index( gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK1STS, gImIoR2yRegPtr[loop_cnt]->YYW.YYWCTL.bit.USEBANK1 + 1 );
				gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK2PS = im_r2y_inc_bank_index( gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK2STS, gImIoR2yRegPtr[loop_cnt]->YYW.YYWCTL.bit.USEBANK2 + 1 );
			}
			gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANKST = 1;
		}
	}

	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
	Im_R2Y_Dsb();

	return D_DDIM_OK;
}

/* Increment bank index value
 */
INT32 im_r2y3_inc_outbank_index(ImR2y3 *self, kuint16 pipeNo, kuint16 yywNo )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);
	kuint16 loop_cnt, loop_sta, loop_end;

#ifdef CO_PARAM_CHECK
	if( yywNo >= ImR2yCtrl_YYW_CH_MAX ) {
		Ddim_Assertion(("im_r2y3_inc_outbank_index error. yywNo >= MAX\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_inc_outbank_index error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_utils_get_loop_val(imR2yUtils, pipeNo, &loop_sta, &loop_end );

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		if( yywNo == ImR2yCtrl_YYW_CH_0 ) {
			gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK0PS = im_r2y_inc_bank_index( gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK0STS, gImIoR2yRegPtr[loop_cnt]->YYW.YYWCTL.bit.USEBANK0 + 1 );
		}
		else if( yywNo == ImR2yCtrl_YYW_CH_1 ) {
			gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK1PS = im_r2y_inc_bank_index( gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK1STS, gImIoR2yRegPtr[loop_cnt]->YYW.YYWCTL.bit.USEBANK1 +1 );
		}
		else if( yywNo == ImR2yCtrl_YYW_CH_2 ) {
			gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK2PS = im_r2y_inc_bank_index( gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK2STS, gImIoR2yRegPtr[loop_cnt]->YYW.YYWCTL.bit.USEBANK2 +1 );
		}
		else {
			gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANKAPS = im_r2y_inc_bank_index( gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANKASTS, gImIoR2yRegPtr[loop_cnt]->YYW.YYWCTL.bit.USEBANKA +1 );
		}
		gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANKST = 1;
	}
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
	Im_R2Y_Dsb();

	return D_DDIM_OK;
}

/* R2Y Control (B2R/LTM direct connection mode control)
 */
INT32 im_r2y3_ctrl_mode_direct(ImR2y3 *self, kuint16 pipeNo, const R2CtrlDirect* const r2y_ctrl_direct )
{
	kuint16 loop_cnt, loop_sta, loop_end;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile R2yStateMng* gImR2yState = im_r2y_utils_get_state_mng(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2y_ctrl_direct == NULL ) {
		Ddim_Assertion(("im_r2y3_ctrl_mode_direct error. r2y_ctrl_direct = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_ctrl_mode_direct error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_utils_get_loop_val(imR2yUtils, pipeNo, &loop_sta, &loop_end );

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		if(ImR2yCtrl_YYR_IS_ACTIVATED( loop_cnt )){
#ifdef CO_DEBUG_PRINT_IM_R2Y
			Ddim_Print(( "im_r2y3_ctrl_mode_direct error. YYR busy\n" ));
#endif
			im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
			return ImR2yUtils_MACRO_BUSY;
		}
	}

	gImIoR2yRegPtr[pipeNo]->YYR.DINCTL.bit.FRMSTP = r2y_ctrl_direct->frameStop;
	gImIoR2yRegPtr[pipeNo]->YYR.DINCTL.bit.B2RDIN = ImR2yUtils_MODE_DIRECT;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
	Im_R2Y_Dsb();

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		gImR2yState[loop_cnt].videoPhotoMode = ImR2yUtils_MODE_DIRECT;
	}

	return D_DDIM_OK;
}

/* Set Right side offset(for video format)
 */
INT32 im_r2y3_set_right_side_offset(ImR2y3 *self, kuint16 pipeNo, kuint16 yywNo, R2yRightsideOffset* offsetByte )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( offsetByte == NULL ) {
		Ddim_Assertion(("im_r2y3_set_right_side_offset error. offsetByte = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( !(yywNo == ImR2yCtrl_YYW_CH_0 || yywNo == ImR2yCtrl_YYW_CH_0A) ) {
		Ddim_Assertion(("im_r2y3_set_right_side_offset error. yywNo != (0 or 0A)\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo >= ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_set_right_side_offset error. pipeNo>=ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	if( yywNo == ImR2yCtrl_YYW_CH_0 ){
		gImIoR2yRegPtr[pipeNo]->YYW.YYW0OFSX.bit.YYW0OFSX_0 = offsetByte->offsetByte[ImR2yCtrl_YYW_BANK_0];
		gImIoR2yRegPtr[pipeNo]->YYW.YYW0OFSX.bit.YYW0OFSX_1 = offsetByte->offsetByte[ImR2yCtrl_YYW_BANK_1];
		gImIoR2yRegPtr[pipeNo]->YYW.YYW0OFSX.bit.YYW0OFSX_2 = offsetByte->offsetByte[ImR2yCtrl_YYW_BANK_2];
		gImIoR2yRegPtr[pipeNo]->YYW.YYW0OFSX.bit.YYW0OFSX_3 = offsetByte->offsetByte[ImR2yCtrl_YYW_BANK_3];
	}
	else if( yywNo == ImR2yCtrl_YYW_CH_0A ){
		gImIoR2yRegPtr[pipeNo]->YYW.YYWAOFSX.bit.YYWAOFSX_0 = offsetByte->offsetByte[ImR2yCtrl_YYW_BANK_0];
		gImIoR2yRegPtr[pipeNo]->YYW.YYWAOFSX.bit.YYWAOFSX_1 = offsetByte->offsetByte[ImR2yCtrl_YYW_BANK_1];
		gImIoR2yRegPtr[pipeNo]->YYW.YYWAOFSX.bit.YYWAOFSX_2 = offsetByte->offsetByte[ImR2yCtrl_YYW_BANK_2];
		gImIoR2yRegPtr[pipeNo]->YYW.YYWAOFSX.bit.YYWAOFSX_3 = offsetByte->offsetByte[ImR2yCtrl_YYW_BANK_3];
	}
	else{
		// nothing to do.
	}

	return D_DDIM_OK;
}

/* Get Next Address information
 */
INT32 im_r2y3_get_next_outaddr(ImR2y3 *self, kuint16 pipeNo, const UINT32 yywNo, R2yOutaddrInfo* const r2yAddr )
{
#ifdef CO_PARAM_CHECK
	if( r2yAddr == NULL ) {
		Ddim_Assertion(("im_r2y3_get_next_outaddr error. r2yAddr = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( yywNo >= ImR2yCtrl_YYW_CH_MAX ) {
		Ddim_Assertion(("im_r2y3_get_next_outaddr error. yywNo >= MAX\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo >= ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_get_next_outaddr error. pipeNo>=ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_get_next_r2y_addr(im_r2y_new(),  pipeNo, yywNo, r2yAddr);
	return D_DDIM_OK;
}

/* Get Latest Address information
 */
INT32 im_r2y3_get_latest_outaddr(ImR2y3 *self, kuint16 pipeNo, UINT32 yywNo, kuint16* const latestBankIdx, R2yOutaddrInfo* const latestAddr )
{
#ifdef CO_PARAM_CHECK
	if( latestAddr == NULL ) {
		Ddim_Assertion(("im_r2y3_get_latest_outaddr error. latestAddr = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( yywNo >= ImR2yCtrl_YYW_CH_MAX ) {
		Ddim_Assertion(("im_r2y3_get_latest_outaddr error. yywNo >= MAX\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo >= ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_get_latest_outaddr error. pipeNo>=ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_get_latest_addr(im_r2y_new(),  pipeNo, yywNo, latestBankIdx, latestAddr);

	return D_DDIM_OK;
}

/* Set YYW0 External I/F output.
 */
INT32 im_r2y3_set_external_if_output(ImR2y3 *self, kuint16 pipeNo, kuint16 output_onoff_ipu, kuint16 output_onoff_cnr )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_set_external_if_output error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	gImIoR2yRegPtr[pipeNo]->YYW.YYW0MD.bit.EXTBEN = output_onoff_ipu;
	gImIoR2yRegPtr[pipeNo]->YYW.YYW0MD.bit.EXTCEN = output_onoff_cnr;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
	Im_R2Y_Dsb();

	return D_DDIM_OK;
}

/* Get YYW0 External I/F output status.
 */
INT32 im_r2y3_get_external_if_output(ImR2y3 *self, kuint16 pipeNo, kuint16* const output_onoff_ipu, kuint16* const output_onoff_cnr )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( output_onoff_ipu == NULL ) {
		Ddim_Assertion(("im_r2y3_get_external_if_output error. output_onoff_ipu = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( output_onoff_cnr == NULL ) {
		Ddim_Assertion(("im_r2y3_get_external_if_output error. output_onoff_cnr = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo >= ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_get_external_if_output error. pipeNo>=ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	*output_onoff_ipu = gImIoR2yRegPtr[pipeNo]->YYW.YYW0MD.bit.EXTBEN;
	*output_onoff_cnr = gImIoR2yRegPtr[pipeNo]->YYW.YYW0MD.bit.EXTCEN;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );

	return D_DDIM_OK;
}

/* Set Frame stop
 */
INT32 im_r2y3_set_frame_stop(ImR2y3 *self, kuint16 pipeNo, kuint16 onoff )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_set_frame_stop error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	gImIoR2yRegPtr[pipeNo]->YYR.DINCTL.bit.FRMSTP = onoff;
	gImIoR2yRegPtr[pipeNo]->YYR.YYRTRG.bit.YYRTRG = D_IM_R2Y_YYRTRG_ON;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
	Im_R2Y_Dsb();

	return D_DDIM_OK;
}

/* Get YYRch busy status.
 */
INT32 im_r2y3_get_yyr_busy(ImR2y3 *self, kuint16 pipeNo, BOOL* const busy_status )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

	kulong yyrtrg;

#ifdef CO_PARAM_CHECK
	if( busy_status == NULL ) {
		Ddim_Assertion(("im_r2y3_get_yyr_busy error. busy_status = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo >= ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_get_yyr_busy error. pipeNo>=ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	yyrtrg = gImIoR2yRegPtr[pipeNo]->YYR.YYRTRG.bit.YYRTRG;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );

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
INT32 im_r2y3_get_h_ring_pixs(ImR2y3 *self, kuint16 pipeNo, kuint16* const ringPixs )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile R2yStateMng* gImR2yState = im_r2y_utils_get_state_mng(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( ringPixs == NULL ) {
		Ddim_Assertion(("im_r2y3_get_h_ring_pixs error. ringPixs = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo >= ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_get_h_ring_pixs error. pipeNo>=ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*ringPixs = gImR2yState[pipeNo].ringPixsInfo.ringPixs;

	return D_DDIM_OK;
}

/* Trimming control
 */
INT32 im_r2y3_ctrl_trimming(ImR2y3 *self, kuint16 pipeNo, kuint16 yywNo, const R2yCtrlTrimming* const r2y_ctrl_trimming )
{
	kuint16 imgTop;
	kuint16 imgLeft;
	kuint16 imgWidth;
	kuint16 imgLines;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile R2yStateMng* gImR2yState = im_r2y_utils_get_state_mng(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2y_ctrl_trimming == NULL ) {
		Ddim_Assertion(("im_r2y3_ctrl_trimming error. r2y_ctrl_trimming = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( yywNo > ImR2yCtrl_YYW_CH_2 ) {
		Ddim_Assertion(("im_r2y3_ctrl_trimming error. yywNo > ImR2yCtrl_YYW_CH_2\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_ctrl_trimming error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	if( im_r2y_check_target_pipe_no_1( pipeNo ) ){
		gImR2yState[ImR2yCtrl_PIPE1].trim[yywNo] = *r2y_ctrl_trimming;
	}
	if( im_r2y_check_target_pipe_no_2( pipeNo ) ){
		gImR2yState[ImR2yCtrl_PIPE2].trim[yywNo] = *r2y_ctrl_trimming;
	}

	// TRMxHSTA
	imgLeft = r2y_ctrl_trimming->trim_window.imgLeft;
	imgLeft = ImR2yUtils_MIN( imgLeft, (kuint16)D_IM_R2Y_TRMHSTA_MAX );
	imgLeft = ImR2yUtils_MAX( imgLeft, (kuint16)D_IM_R2Y_TRMHSTA_MIN );

	// TRMxVSTA
	imgTop = r2y_ctrl_trimming->trim_window.imgTop;
	imgTop = ImR2yUtils_MIN( imgTop, (kuint16)D_IM_R2Y_TRMVSTA_MAX );
	imgTop = ImR2yUtils_MAX( imgTop, (kuint16)D_IM_R2Y_TRMVSTA_MIN );

	// TRMxHSIZ
	imgWidth = r2y_ctrl_trimming->trim_window.imgWidth;
	imgWidth = ImR2yUtils_MIN( imgWidth, (kuint16)D_IM_R2Y_TRMHSIZ_MAX );
	imgWidth = ImR2yUtils_MAX( imgWidth, (kuint16)D_IM_R2Y_TRMHSIZ_MIN );

	// TRMxVSIZ
	imgLines = r2y_ctrl_trimming->trim_window.imgLines;
	imgLines = ImR2yUtils_MIN( imgLines, (kuint16)D_IM_R2Y_TRMVSIZ_MAX );
	imgLines = ImR2yUtils_MAX( imgLines, (kuint16)D_IM_R2Y_TRMVSIZ_MIN );

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	switch( yywNo ) {
		case ImR2yCtrl_YYW_CH_0:
			gImIoR2yRegPtr[pipeNo]->YYW.YYW0MD.bit.TRM0EN  = r2y_ctrl_trimming->trimming_enable;
			gImIoR2yRegPtr[pipeNo]->YYW.TRM0H.bit.TRM0HSTA = imgLeft;
			gImIoR2yRegPtr[pipeNo]->YYW.TRM0H.bit.TRM0HSIZ = imgWidth;
			gImIoR2yRegPtr[pipeNo]->YYW.TRM0V.bit.TRM0VSTA = imgTop;
			gImIoR2yRegPtr[pipeNo]->YYW.TRM0V.bit.TRM0VSIZ = imgLines;
			break;
		case ImR2yCtrl_YYW_CH_1:
			gImIoR2yRegPtr[pipeNo]->YYW.YYW1MD.bit.TRM1EN  = r2y_ctrl_trimming->trimming_enable;
			gImIoR2yRegPtr[pipeNo]->YYW.TRM1H.bit.TRM1HSTA = imgLeft;
			gImIoR2yRegPtr[pipeNo]->YYW.TRM1H.bit.TRM1HSIZ = imgWidth;
			gImIoR2yRegPtr[pipeNo]->YYW.TRM1V.bit.TRM1VSTA = imgTop;
			gImIoR2yRegPtr[pipeNo]->YYW.TRM1V.bit.TRM1VSIZ = imgLines;
			break;
//		case ImR2yCtrl_YYW_CH_2:
		default:
			gImIoR2yRegPtr[pipeNo]->YYW.YYW2MD.bit.TRM2EN  = r2y_ctrl_trimming->trimming_enable;
			gImIoR2yRegPtr[pipeNo]->YYW.TRM2H.bit.TRM2HSTA = imgLeft;
			gImIoR2yRegPtr[pipeNo]->YYW.TRM2H.bit.TRM2HSIZ = imgWidth;
			gImIoR2yRegPtr[pipeNo]->YYW.TRM2V.bit.TRM2VSTA = imgTop;
			gImIoR2yRegPtr[pipeNo]->YYW.TRM2V.bit.TRM2VSIZ = imgLines;
			break;
	}
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );

	return D_DDIM_OK;
}

/* Trimming control(for external I/F)
 */
INT32 im_r2y3_ctrl_trimming_external(ImR2y3 *self, kuint16 pipeNo, const CtrlTrimmingExt* const r2y_ctrl_trimming )
{
	kuint16 img_top_b;
	kuint16 img_left_b;
	kuint16 img_width_b;
	kuint16 img_lines_b;
	kuint16 img_top_c;
	kuint16 img_left_c;
	kuint16 img_width_c;
	kuint16 img_lines_c;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile R2yStateMng* gImR2yState = im_r2y_utils_get_state_mng(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2y_ctrl_trimming == NULL ) {
		Ddim_Assertion(("im_r2y3_ctrl_trimming_external error. r2y_ctrl_trimming = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_ctrl_trimming_external error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	if( im_r2y_check_target_pipe_no_1( pipeNo ) ){
		gImR2yState[ImR2yCtrl_PIPE1].trimExt = *r2y_ctrl_trimming;
	}
	if( im_r2y_check_target_pipe_no_2( pipeNo ) ){
		gImR2yState[ImR2yCtrl_PIPE2].trimExt = *r2y_ctrl_trimming;
	}

	// TRMBHSTA
	img_left_b = r2y_ctrl_trimming->trim_window_b.imgLeft;
	img_left_b = ImR2yUtils_MIN( img_left_b, (kuint16)D_IM_R2Y_TRMHSTA_MAX );
	img_left_b = ImR2yUtils_MAX( img_left_b, (kuint16)D_IM_R2Y_TRMHSTA_MIN );

	// TRMBVSTA
	img_top_b = r2y_ctrl_trimming->trim_window_b.imgTop;
	img_top_b = ImR2yUtils_MIN( img_top_b, (kuint16)D_IM_R2Y_TRMVSTA_MAX );
	img_top_b = ImR2yUtils_MAX( img_top_b, (kuint16)D_IM_R2Y_TRMVSTA_MIN );

	// TRMBHSIZ
	img_width_b = r2y_ctrl_trimming->trim_window_b.imgWidth;
	img_width_b = ImR2yUtils_MIN( img_width_b, (kuint16)D_IM_R2Y_TRMHSIZ_MAX );
	img_width_b = ImR2yUtils_MAX( img_width_b, (kuint16)D_IM_R2Y_TRMHSIZ_MIN );

	// TRMBVSIZ
	img_lines_b = r2y_ctrl_trimming->trim_window_b.imgLines;
	img_lines_b = ImR2yUtils_MIN( img_lines_b, (kuint16)D_IM_R2Y_TRMVSIZ_MAX );
	img_lines_b = ImR2yUtils_MAX( img_lines_b, (kuint16)D_IM_R2Y_TRMVSIZ_MIN );

	// TRMCHSTA
	img_left_c = r2y_ctrl_trimming->trim_window_c.imgLeft;
	img_left_c = ImR2yUtils_MIN( img_left_c, (kuint16)D_IM_R2Y_TRMHSTA_MAX );
	img_left_c = ImR2yUtils_MAX( img_left_c, (kuint16)D_IM_R2Y_TRMHSTA_MIN );

	// TRMCVSTA
	img_top_c = r2y_ctrl_trimming->trim_window_c.imgTop;
	img_top_c = ImR2yUtils_MIN( img_top_c, (kuint16)D_IM_R2Y_TRMVSTA_MAX );
	img_top_c = ImR2yUtils_MAX( img_top_c, (kuint16)D_IM_R2Y_TRMVSTA_MIN );

	// TRMCHSIZ
	img_width_c = r2y_ctrl_trimming->trim_window_c.imgWidth;
	img_width_c = ImR2yUtils_MIN( img_width_c, (kuint16)D_IM_R2Y_TRMHSIZ_MAX );
	img_width_c = ImR2yUtils_MAX( img_width_c, (kuint16)D_IM_R2Y_TRMHSIZ_MIN );

	// TRMCVSIZ
	img_lines_c = r2y_ctrl_trimming->trim_window_c.imgLines;
	img_lines_c = ImR2yUtils_MIN( img_lines_c, (kuint16)D_IM_R2Y_TRMVSIZ_MAX );
	img_lines_c = ImR2yUtils_MAX( img_lines_c, (kuint16)D_IM_R2Y_TRMVSIZ_MIN );

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	gImIoR2yRegPtr[pipeNo]->YYW.YYW0MD.bit.TRMBEN  = r2y_ctrl_trimming->trimming_enable_b;
	gImIoR2yRegPtr[pipeNo]->YYW.TRMBH.bit.TRMBHSTA = img_left_b;
	gImIoR2yRegPtr[pipeNo]->YYW.TRMBH.bit.TRMBHSIZ = img_width_b;
	gImIoR2yRegPtr[pipeNo]->YYW.TRMBV.bit.TRMBVSTA = img_top_b;
	gImIoR2yRegPtr[pipeNo]->YYW.TRMBV.bit.TRMBVSIZ = img_lines_b;

	gImIoR2yRegPtr[pipeNo]->YYW.YYW0MD.bit.TRMCEN  = r2y_ctrl_trimming->trimming_enable_c;
	gImIoR2yRegPtr[pipeNo]->YYW.TRMCH.bit.TRMCHSTA = img_left_c;
	gImIoR2yRegPtr[pipeNo]->YYW.TRMCH.bit.TRMCHSIZ = img_width_c;
	gImIoR2yRegPtr[pipeNo]->YYW.TRMCV.bit.TRMCVSTA = img_top_c;
	gImIoR2yRegPtr[pipeNo]->YYW.TRMCV.bit.TRMCVSIZ = img_lines_c;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );

	return D_DDIM_OK;
}

/* Set Histogram control register
 */
INT32 im_r2y3_ctrl_histogram(ImR2y3 *self, kuint16 pipeNo, const R2yCtrlHistogram* const r2y_ctrl_hist )
{
	INT32 retcd = D_DDIM_OK;
	kuint16 loop_cnt, loop_sta, loop_end;
	kuint16 imgTop;
	kuint16 imgLeft;
	kuint16 imgWidth;
	kuint16 imgLines;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2y_ctrl_hist == NULL ) {
		Ddim_Assertion(("im_r2y3_ctrl_histogram error. r2y_ctrl_hist = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_ctrl_histogram error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_utils_get_loop_val(imR2yUtils, pipeNo, &loop_sta, &loop_end );

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	while( 1 ) {

		for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
			if( im_r2y_yyw_is_activated(loop_cnt) && (gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.RAMAEN.bit.HSTAEN == 0) ) {
				retcd = ImR2yUtils_MACRO_BUSY;
			}
		}

		gImIoR2yRegPtr[pipeNo]->YYW.HSTMD.bit.HSTSEL = r2y_ctrl_hist->yywNo;
		gImIoR2yRegPtr[pipeNo]->YYW.HSTMD.bit.PIT_M  = r2y_ctrl_hist->samplingPitch;

		// HSTHSTA
		imgLeft = r2y_ctrl_hist->histogramArea.imgLeft;
		imgLeft = ImR2yUtils_MIN( imgLeft, (kuint16)D_IM_R2Y_HSTHSTA_MAX );
		imgLeft = ImR2yUtils_MAX( imgLeft, (kuint16)D_IM_R2Y_HSTHSTA_MIN );

		// HSTVSTA
		imgTop = r2y_ctrl_hist->histogramArea.imgTop;
		imgTop = ImR2yUtils_MIN( imgTop, (kuint16)D_IM_R2Y_HSTVSTA_MAX );
		imgTop = ImR2yUtils_MAX( imgTop, (kuint16)D_IM_R2Y_HSTVSTA_MIN );

		// HSTHSIZ
		imgWidth = r2y_ctrl_hist->histogramArea.imgWidth;
		imgWidth = ImR2yUtils_MIN( imgWidth, (kuint16)D_IM_R2Y_HSTHSIZ_MAX );
		imgWidth = ImR2yUtils_MAX( imgWidth, (kuint16)D_IM_R2Y_HSTHSIZ_MIN );

		// HSTVSIZ
		imgLines = r2y_ctrl_hist->histogramArea.imgLines;
		imgLines = ImR2yUtils_MIN( imgLines, (kuint16)D_IM_R2Y_HSTVSIZ_MAX );
		imgLines = ImR2yUtils_MAX( imgLines, (kuint16)D_IM_R2Y_HSTVSIZ_MIN );

		gImIoR2yRegPtr[pipeNo]->YYW.HSTH.bit.HSTHSTA = imgLeft;
		gImIoR2yRegPtr[pipeNo]->YYW.HSTH.bit.HSTHSIZ = imgWidth;
		gImIoR2yRegPtr[pipeNo]->YYW.HSTV.bit.HSTVSTA = imgTop;
		gImIoR2yRegPtr[pipeNo]->YYW.HSTV.bit.HSTVSIZ = imgLines;
		gImIoR2yRegPtr[pipeNo]->YYW.HSTMD.bit.HSTEN  = r2y_ctrl_hist->enable;

		break;
	}
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
	Im_R2Y_Dsb();

	return retcd;
}

/* Get Histogram value
 */
INT32 im_r2y3_get_histogram(ImR2y3 *self, kuint16 pipeNo, R2yHistogramStat* const status, R2yHistogramAddr* const dst_addr )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile struct io_r2y_sram** gImIoR2yTblPtr = im_r2y_utils_get_io_tbl(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( status == NULL ) {
		Ddim_Assertion(("im_r2y3_get_histogram error. status = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( dst_addr == NULL ) {
		Ddim_Assertion(("im_r2y3_get_histogram error. dst_addr = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo >= ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_get_histogram error. pipeNo>=ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	status->yOverflow = gImIoR2yRegPtr[pipeNo]->YYW.HSTMD.bit.YHSOVF;
	status->runningStatus = gImIoR2yRegPtr[pipeNo]->YYW.HSTMD.bit.HSTSTS;
	if( status->runningStatus == 0 ) {
		im_r2y_clk_on_hclk(im_r2y_clk_new(),  pipeNo );
		im_r2y_ctrl3_copy_reg_to_sdram_ushort(im_r2y_ctrl3_new(),  dst_addr->yBuf,	// Read access only support Word-width. (Hardware specification.)
										 gImIoR2yTblPtr[pipeNo]->HSTY.hword,
										 ImR2yCtrl_TABLE_MAX_HISTOGRAM );
		im_r2y_clk_off_hclk(im_r2y_clk_new(),  pipeNo );
	}
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );

	if( status->runningStatus == 0 ) {
		return D_DDIM_OK;
	}
	else {
		return ImR2yUtils_MACRO_BUSY;
	}
}

/* Set Histogram ram access enable
 */
INT32 im_r2y3_set_histogram_access_enable(ImR2y3 *self, kuint16 pipeNo, kuint16 histEnable, kuint16 wait_enable )
{
#ifdef CO_PARAM_CHECK
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_set_histogram_access_enable error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	return im_r2y_set_access_enable(im_r2y2_new(), pipeNo,
									 &gim_r2y_histogram_accen_ctrl,
									 histEnable,
									 wait_enable,
									 ImR2yUtils_ASSETION_MSG( "im_r2y3_set_histogram_access_enable error. Macro busy\n" )
									 );
}

/* Set a specific color extraction
 */
INT32 im_r2y3_set_color_extract(ImR2y3 *self, kuint16 pipeNo, const R2yColorExtract* const r2y_color_extract )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2y_color_extract == NULL ) {
		Ddim_Assertion(("im_r2y3_set_color_extract error. r2y_color_extract = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_set_color_extract error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	gImIoR2yRegPtr[pipeNo]->YYW.PCEMD.bit.PCEEN = r2y_color_extract->extractEnable;
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->YYW.PCEXY, union io_r2y_pcexy, PCEX, r2y_color_extract->refAxisX );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->YYW.PCEXY, union io_r2y_pcexy, PCEY, r2y_color_extract->refAxisY );
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );

	return D_DDIM_OK;
}

/* Set chroma scale value
 */
INT32 im_r2y3_set_chroma(ImR2y3 *self, kuint16 pipeNo, const R2yChRomaScale* const r2y_chroma_scale )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2y_chroma_scale == NULL ) {
		Ddim_Assertion(("im_r2y3_set_chroma error. r2y_chroma_scale = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_set_chroma error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	gImIoR2yRegPtr[pipeNo]->YYW.PCEC.bit.PCECOF = r2y_chroma_scale->chromaOffset;
	gImIoR2yRegPtr[pipeNo]->YYW.PCEC.bit.PCECGA = r2y_chroma_scale->chromaGain;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );

	return D_DDIM_OK;
}

/* Set hue scale value
 */
INT32 im_r2y3_set_hue(ImR2y3 *self, kuint16 pipeNo, const R2yHueScale* const r2y_hue_scale )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2y_hue_scale == NULL ) {
		Ddim_Assertion(("im_r2y3_set_hue error. r2y_hue_scale = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_set_hue error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	gImIoR2yRegPtr[pipeNo]->YYW.PCEH.bit.PCEHOF = r2y_hue_scale->hueOffset;
	gImIoR2yRegPtr[pipeNo]->YYW.PCEH.bit.PCEHGA = r2y_hue_scale->hueGain;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );

	return D_DDIM_OK;
}

/* Set RGB Deknee table.
 */
INT32 im_r2y3_set_rgb_deknee_table(ImR2y3 *self, kuint16 pipeNo, ER2yDknRgbtbl tbl_type, const kuint16* const src_tbl )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y_sram** gImIoR2yTblPtr = im_r2y_utils_get_io_tbl(imR2yUtils);

#ifndef CO_R2Y_RDMA_ON
	UINT32 loop_cnt;
	volatile kuint16* dst_tbl;
#endif	// CO_R2Y_RDMA_ON
	INT32  ercd;

#ifdef CO_PARAM_CHECK
	if(src_tbl == NULL) {
		Ddim_Assertion(("im_r2y3_set_rgb_deknee_table error. src_tbl = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_set_rgb_deknee_table error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif

	while( 1 ) {
		ercd = im_r2y3_set_rgb_deknee_access_enable(im_r2y3_new(),  pipeNo, ImR2yCtrl_ENABLE_ON, ImR2yCtrl_WAIT_ON );
		if( ercd != D_DDIM_OK ) {
			break;
		}

#ifdef CO_R2Y_RDMA_ON
		imR2ySetRdmaValDekneeTable( pipeNo, tbl_type, src_tbl );
#else	// CO_R2Y_RDMA_ON
		im_r2y_clk_on_hclk(im_r2y_clk_new(),  pipeNo );

		switch( tbl_type ) {
			case ImR2y_DKN_RGBTBL_G:
				dst_tbl = gImIoR2yTblPtr[pipeNo]->DKNTBLG.hword;
				break;
			case ImR2y_DKN_RGBTBL_B:
				dst_tbl = gImIoR2yTblPtr[pipeNo]->DKNTBLB.hword;
				break;
			default:	// ImR2y_DKN_RGBTBL_R
				dst_tbl = gImIoR2yTblPtr[pipeNo]->DKNTBLR.hword;
				break;
		}
		for( loop_cnt = 0; loop_cnt < ImR2yCtrl_TABLE_MAX_RGB_DEKNEE; loop_cnt++ ) {
			dst_tbl[loop_cnt] = src_tbl[loop_cnt];
		}

		im_r2y_clk_off_hclk(im_r2y_clk_new(),  pipeNo );
#endif	// CO_R2Y_RDMA_ON

		ercd = im_r2y3_set_rgb_deknee_access_enable(im_r2y3_new(),  pipeNo, ImR2yCtrl_ENABLE_OFF, ImR2yCtrl_WAIT_OFF );
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
INT32 im_r2y3_set_rgb_deknee_access_enable(ImR2y3 *self, kuint16 pipeNo, kuint16 access_enable, kuint16 wait_enable )
{
#ifdef CO_PARAM_CHECK
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y3_set_rgb_deknee_access_enable error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	return im_r2y_set_access_enable(im_r2y2_new(), pipeNo,
									 &gim_r2y_rgb_deknee_accen_ctrl,
									 access_enable,
									 wait_enable,
									 ImR2yUtils_ASSETION_MSG( "im_r2y3_set_rgb_deknee_access_enable error. Macro busy\n" )
									 );
}

ImR2y3 *im_r2y3_new(void)
{
	ImR2y3* self = k_object_new_with_private(IM_TYPE_R2Y3,sizeof(ImR2y3Private));
	return self;
}
