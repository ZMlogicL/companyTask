/*
 * imr2yproc.c
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

#include "imr2yproc.h"
#include "imr2y2.h"
#include "imr2y3.h"
#include "imr2yctrl.h"
#include "imr2yctrl2.h"
#include "imr2yctrl3.h"
#include "imr2yedge.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImR2yProc, im_r2y_proc);
#define IM_R2Y_PROC_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImR2yProcPrivate, IM_TYPE_R2Y_PROC))

// Driver state of Starting flag
#define D_IM_R2Y_STATE_IDLE				(0x00)
#define D_IM_R2Y_STATE_BUSY_F_R2Y		(0x01)
#define D_IM_R2Y_STATE_BUSY_YYR			(0x02)
#define D_IM_R2Y_STATE_BUSY_YYW0		(0x04)
#define D_IM_R2Y_STATE_BUSY_YYW0A		(0x08)
#define D_IM_R2Y_STATE_BUSY_YYW1		(0x10)
#define D_IM_R2Y_STATE_BUSY_YYW2		(0x20)
#define D_IM_R2Y_STATE_BUSY_ALL			(D_IM_R2Y_STATE_BUSY_F_R2Y | D_IM_R2Y_STATE_BUSY_YYR | D_IM_R2Y_STATE_BUSY_YYW0 | D_IM_R2Y_STATE_BUSY_YYW0A | D_IM_R2Y_STATE_BUSY_YYW1 | D_IM_R2Y_STATE_BUSY_YYW2)


// YYINTE value
#define D_IM_R2Y_YYINTE_YYW0_ENABLE		(0x00337131)	// YYR, YYW0, YYW0a, AXI
#define D_IM_R2Y_YYINTE_YYW1_ENABLE		(0x00337141)	// YYR, YYW1, AXI
#define D_IM_R2Y_YYINTE_YYW2_ENABLE		(0x00337181)	// YYR, YYW1, AXI
#define D_IM_R2Y_YYINTE_DISABLE			(0x00000000)
// YINTF value
#define D_IM_R2Y_YYINTF_ALL_CLR			(0x003371F1)	// YYR, YYW0, YYW0a, YYW1, YYW2, AXI

// R2YINTE value
#define D_IM_R2Y_R2YINTE_ALL_ENABLE		(0x0111)
#define D_IM_R2Y_R2YINTE_DISABLE		(0x0000)


// R2YINTF value
#define D_IM_R2Y_R2YINTF_ALL_CLR		(0x0111)

#define D_IM_R2Y_YYRTRG_OFF				(0)

#define D_IM_R2Y_FR2YTRG_OFF			(0)
#define D_IM_R2Y_FR2YTRG_ON				(1)
#define ImR2y_FR2YTRG_IDLE			(2)
#define D_IM_R2Y_FR2YTRG_BUSY			(3)

#define D_IM_R2Y_YYWTRG_OFF				(0)
#define D_IM_R2Y_YYWTRG_ON				(1)
#define D_IM_R2Y_YYWTRG_BUSY			(3)

#define D_IM_R2Y_YYRTRG_ON				(1)

// wait usec
//TODO 加了一个
#define im_r2y_wait_usec( usec )				Dd_ARM_Wait_ns( (usec) * 1000 )

#ifdef D_IM_R2Y_DEBUG_ON_PC
volatile kuint16 gIM_R2Y_macro_fake_finish[ImR2yUtils_PIPE_COUNT] = {0,0};
#endif


struct _ImR2yProcPrivate
{
	int a;
};

// Interrupt parameter table
typedef struct {
	kulong					flg_bitmask;		// Bitmask of interrupt flag.
	kulong					ena_bitmask;		// Bitmask of inaerrupt enable.
	kulong					waitflg;			// Value of set_flg.
	kulong					intStatus;			// Value of gImR2yState.intStatus.
	kulong					busyState;			// Value of gImR2yState.busyState.
} T_IM_R2Y_INTFLG_TBL;

//
// Interrupt parameter table
//
static const T_IM_R2Y_INTFLG_TBL gim_r2y_inttbl_jdsr2y[ImR2yUtils_PIPE_COUNT][13] = {
	{
		{ 0x00000001, 0x00000001, ImR2yCtrl_INT_FLG_YYR_END1,    ImR2yCtrl_INT_STATE_YYR_END1,    D_IM_R2Y_STATE_BUSY_YYR },		// YYREE
		{ 0x00000010, 0x00000010, ImR2yCtrl_INT_FLG_YYW0_END1,   ImR2yCtrl_INT_STATE_YYW0_END1,   D_IM_R2Y_STATE_BUSY_YYW0 },		// YYW0EE
		{ 0x00000020, 0x00000020, ImR2yCtrl_INT_FLG_YYW0A_END1,  ImR2yCtrl_INT_STATE_YYW0A_END1,  D_IM_R2Y_STATE_BUSY_YYW0A },	// YYWAEE
		{ 0x00000040, 0x00000040, ImR2yCtrl_INT_FLG_YYW1_END1,   ImR2yCtrl_INT_STATE_YYW1_END1,   D_IM_R2Y_STATE_BUSY_YYW1 },		// YYW1EE
		{ 0x00000080, 0x00000080, ImR2yCtrl_INT_FLG_YYW2_END1,   ImR2yCtrl_INT_STATE_YYW2_END1,   D_IM_R2Y_STATE_BUSY_YYW2 },		// YYW2EE
		{ 0x00000100, 0x00000100, ImR2yCtrl_INT_FLG_YYWALL_END1, ImR2yCtrl_INT_STATE_YYWALL_END1, (D_IM_R2Y_STATE_BUSY_YYW0 | D_IM_R2Y_STATE_BUSY_YYW0A | D_IM_R2Y_STATE_BUSY_YYW1 | D_IM_R2Y_STATE_BUSY_YYW2 ) },	// YYWEE
		{ 0x00001000, 0x00001000, ImR2yCtrl_INT_FLG_LINE0_END1,  ImR2yCtrl_INT_STATE_LINE0_END1,  0 },	// LINT0E
		{ 0x00002000, 0x00002000, ImR2yCtrl_INT_FLG_LINE1_END1,  ImR2yCtrl_INT_STATE_LINE1_END1,  0 },	// LINT1E
		{ 0x00004000, 0x00004000, ImR2yCtrl_INT_FLG_LINE2_END1,  ImR2yCtrl_INT_STATE_LINE2_END1,  0 },	// LINT2E
		{ 0x00010000, 0x00010000, ImR2yCtrl_INT_FLG_YYR_ERR1,    ImR2yCtrl_INT_STATE_YYR_ERR1,    D_IM_R2Y_STATE_BUSY_YYR },		// YYRERE
		{ 0x00020000, 0x00020000, ImR2yCtrl_INT_FLG_YYW_ERR1,    ImR2yCtrl_INT_STATE_YYW_ERR1,    (D_IM_R2Y_STATE_BUSY_YYW0 | D_IM_R2Y_STATE_BUSY_YYW0A | D_IM_R2Y_STATE_BUSY_YYW1 | D_IM_R2Y_STATE_BUSY_YYW2) },	// YYWERE
		{ 0x00100000, 0x00100000, ImR2yCtrl_INT_FLG_AXR_ERR1,    ImR2yCtrl_INT_STATE_AXR_ERR1,    0 },	// AXRERE
		{ 0x00200000, 0x00200000, ImR2yCtrl_INT_FLG_AXW_ERR1,    ImR2yCtrl_INT_STATE_AXW_ERR1,    0 },	// AXWERE
	},
	{
		{ 0x00000001, 0x00000001, D_IM_R2Y2_INT_FLG_YYR_END,    ImR2yCtrl_INT_STATE_YYR_END2,    D_IM_R2Y_STATE_BUSY_YYR },		// YYREE
		{ 0x00000010, 0x00000010, D_IM_R2Y2_INT_FLG_YYW0_END,   ImR2yCtrl_INT_STATE_YYW0_END2,   D_IM_R2Y_STATE_BUSY_YYW0 },		// YYW0EE
		{ 0x00000020, 0x00000020, D_IM_R2Y2_INT_FLG_YYW0A_END,  ImR2yCtrl_INT_STATE_YYW0A_END2,  D_IM_R2Y_STATE_BUSY_YYW0A },	// YYWAEE
		{ 0x00000040, 0x00000040, D_IM_R2Y2_INT_FLG_YYW1_END,   ImR2yCtrl_INT_STATE_YYW1_END2,   D_IM_R2Y_STATE_BUSY_YYW1 },		// YYW1EE
		{ 0x00000080, 0x00000080, D_IM_R2Y2_INT_FLG_YYW2_END,   ImR2yCtrl_INT_STATE_YYW2_END2,   D_IM_R2Y_STATE_BUSY_YYW2 },		// YYW2EE
		{ 0x00000100, 0x00000100, D_IM_R2Y2_INT_FLG_YYWALL_END, ImR2yCtrl_INT_STATE_YYWALL_END2, (D_IM_R2Y_STATE_BUSY_YYW0 | D_IM_R2Y_STATE_BUSY_YYW0A | D_IM_R2Y_STATE_BUSY_YYW1 | D_IM_R2Y_STATE_BUSY_YYW2 ) },	// YYWEE
		{ 0x00001000, 0x00001000, D_IM_R2Y2_INT_FLG_LINE0_END,  ImR2yCtrl_INT_STATE_LINE0_END2,  0 },	// LINT0E
		{ 0x00002000, 0x00002000, D_IM_R2Y2_INT_FLG_LINE1_END,  ImR2yCtrl_INT_STATE_LINE1_END2,  0 },	// LINT1E
		{ 0x00004000, 0x00004000, D_IM_R2Y2_INT_FLG_LINE2_END,  ImR2yCtrl_INT_STATE_LINE2_END2,  0 },	// LINT2E
		{ 0x00010000, 0x00010000, D_IM_R2Y2_INT_FLG_YYR_ERR,    ImR2yCtrl_INT_STATE_YYR_ERR2,    D_IM_R2Y_STATE_BUSY_YYR },		// YYRERE
		{ 0x00020000, 0x00020000, D_IM_R2Y2_INT_FLG_YYW_ERR,    ImR2yCtrl_INT_STATE_YYW_ERR2,    (D_IM_R2Y_STATE_BUSY_YYW0 | D_IM_R2Y_STATE_BUSY_YYW0A | D_IM_R2Y_STATE_BUSY_YYW1 | D_IM_R2Y_STATE_BUSY_YYW2) },	// YYWERE
		{ 0x00100000, 0x00100000, D_IM_R2Y2_INT_FLG_AXR_ERR,    ImR2yCtrl_INT_STATE_AXR_ERR2,    0 },	// AXRERE
		{ 0x00200000, 0x00200000, D_IM_R2Y2_INT_FLG_AXW_ERR,    ImR2yCtrl_INT_STATE_AXW_ERR2,    0 },	// AXWERE
	},
};

static const T_IM_R2Y_INTFLG_TBL gim_r2y_inttbl_fr2y[ImR2yUtils_PIPE_COUNT][3] = {
	{
		{ 0x00000001, 0x00000001, ImR2yCtrl_INT_FLG_YCFERR_ERR1, ImR2yCtrl_INT_STATE_YCFERR_ERR1, 0 },	// YCFERE
		{ 0x00000010, 0x00000010, D_IM_R2Y1_INT_FLG_TCT_END,    ImR2yCtrl_INT_STATE_TCT_END1,    0 },	// TCTEE
		{ 0x00000100, 0x00000100, D_IM_R2Y1_INT_FLG_TCHS_END,   ImR2yCtrl_INT_STATE_TCHS_END1,   0 },	// TCHSEE
	},
	{
		{ 0x00000001, 0x00000001, D_IM_R2Y2_INT_FLG_YCFERR_ERR, ImR2yCtrl_INT_STATE_YCFERR_ERR2, 0 },	// YCFERE
		{ 0x00000010, 0x00000010, D_IM_R2Y2_INT_FLG_TCT_END,    ImR2yCtrl_INT_STATE_TCT_END2,    0 },	// TCTEE
		{ 0x00000100, 0x00000100, D_IM_R2Y2_INT_FLG_TCHS_END,   ImR2yCtrl_INT_STATE_TCHS_END2,   0 },	// TCHSEE
	},
};


/*
 * DECLS
 */
static void imR2yLatestAddrUpdate( kuint16 pipeNo, const UINT32 yywNo );
static kuint16 imR2yIsActFr2y( kuint16 pipeNo );

/*
 * IMPL
 */
static void im_r2y_proc_constructor(ImR2yProc *self)
{
	ImR2yProcPrivate *priv = IM_R2Y_PROC_GET_PRIVATE(self);
}

static void im_r2y_proc_destructor(ImR2yProc *self)
{
	ImR2yProcPrivate *priv = IM_R2Y_PROC_GET_PRIVATE(self);
}

static void imR2yLatestAddrUpdate( kuint16 pipeNo, const UINT32 yywNo )
{
#ifdef CO_PARAM_CHECK
	if( pipeNo >= ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "imR2yLatestAddrUpdate error. pipeNo>=ImR2yCtrl_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	//TODO 抽出
	im_r2y_update_latest_address(im_r2y_new(), pipeNo, yywNo);
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
}

/* Is F_R2Y active
 */
static kuint16 imR2yIsActFr2y( kuint16 pipeNo )
{
	kuint16 t_r2y_enable;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

	if( pipeNo >= ImR2yCtrl_PIPE12 ){
		Ddim_Print(( "imR2yIsActFr2y:pipeNo err\n" ));
		return 0;
	}

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	t_r2y_enable = (gImIoR2yRegPtr[pipeNo]->F_R2Y.CNTL.CNTL.bit.TRG != ImR2y_FR2YTRG_IDLE)?(ImR2yCtrl_ENABLE_ON):(ImR2yCtrl_ENABLE_OFF);
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );

	return t_r2y_enable;
}


/*
 * PUBLIC
 */
/* Restart R2Y process when yywContinueStartEnable equal ImR2yCtrl_ENABLE_OFF.
 */
INT32 im_r2y_proc_constart(ImR2yProc *self,  kuint16 pipeNo )
{
	kuint16 loop_cnt, loop_sta, loop_end;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile R2yStateMng* gImR2yState = im_r2y_utils_get_state_mng(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_proc_constart error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_utils_get_loop_val(imR2yUtils, pipeNo, &loop_sta, &loop_end );

#ifdef CO_DEBUG_PRINT_IM_R2Y
	Ddim_Print(( "im_r2y_proc_constart on pclk\n" ));
#endif
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		if( gImR2yState[loop_cnt].wasStarted == D_IM_R2Y_FALSE ) {
			continue;
		}
		// P-clock control

		gImIoR2yRegPtr[pipeNo]->YYW.YYWTRG.bit.YYWTRG = D_IM_R2Y_YYWTRG_ON;

	}
#ifdef CO_DEBUG_PRINT_IM_R2Y
	Ddim_Print(( "im_r2y_proc_constart off pclk\n" ));
#endif
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
	Im_R2Y_Dsb();

	return D_DDIM_OK;
}

/* Start R2Y process.
 */
INT32 im_r2y_proc_start(ImR2yProc *self,  kuint16 pipeNo )
{
	DDIM_USER_ER		ercd;
	INT32				retcd;
	DDIM_USER_FLGPTN	flgptn = 0;
	kuint16 loop_cnt, loop_sta, loop_end;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile R2yStateMng* gImR2yState = im_r2y_utils_get_state_mng(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_proc_start error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_DEBUG_PRINT_IM_R2Y
	Ddim_Print(( "im_r2y_proc_start begin\n" ));
#endif

	// P-clock control
#ifdef CO_DEBUG_PRINT_IM_R2Y
	Ddim_Print(( "im_r2y_proc_start on pclk\n" ));
#endif
	im_r2y_utils_get_loop_val(imR2yUtils, pipeNo, &loop_sta, &loop_end );

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		if( ImR2yCtrl_YYR_IS_ACTIVATED(loop_cnt) ){
			Ddim_Print(( "im_r2y_proc_start error. YYR busy\n" ));
			return ImR2yUtils_MACRO_BUSY;
		}
		if( im_r2y_yyw_is_activated(loop_cnt) ){
			Ddim_Print(( "im_r2y_proc_start error. YYW busy\n" ));
			return ImR2yUtils_MACRO_BUSY;
		}
		if( imR2yIsActFr2y(loop_cnt) != ImR2yCtrl_ENABLE_OFF ){
			Ddim_Print(( "im_r2y_proc_start error. F_R2Y busy\n" ));
			return ImR2yUtils_MACRO_BUSY;
		}
	}

	while( 1 ) {	// Pclk enable section
		// Clear of All Interrupt enable & Interrupt status
#ifdef CO_DEBUG_PRINT_IM_R2Y
		Ddim_Print(( "im_r2y_proc_start begin initialize\n" ));
#endif

#ifdef CO_DEBUG_PRINT_IM_R2Y
		Ddim_Print(( "im_r2y_proc_start initialize interrupt\n" ));
#endif
		// Initialized Interrupt
		gImIoR2yRegPtr[pipeNo]->R2Y_CMN.YYINTE.word = D_IM_R2Y_YYINTE_DISABLE;
		gImIoR2yRegPtr[pipeNo]->R2Y_CMN.YYINTF.word = D_IM_R2Y_YYINTF_ALL_CLR;

		gImIoR2yRegPtr[pipeNo]->F_R2Y.CNTL.R2YINTE.word = D_IM_R2Y_R2YINTE_DISABLE;
		gImIoR2yRegPtr[pipeNo]->F_R2Y.CNTL.R2YINTF.word = D_IM_R2Y_R2YINTF_ALL_CLR;

#ifdef CO_DEBUG_PRINT_IM_R2Y
		Ddim_Print(( "im_r2y_proc_start enable interrupt\n" ));
#endif
		for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
			gImR2yState[loop_cnt].intStatus = 0;

			// Set of All Interrupt enable
			if( gImR2yState[loop_cnt].yywEnable[ImR2yCtrl_YYW_CH_0] == ImR2yCtrl_ENABLE_ON ) {
				gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.YYINTE.word |= D_IM_R2Y_YYINTE_YYW0_ENABLE;
			}
			if( gImR2yState[loop_cnt].yywEnable[ImR2yCtrl_YYW_CH_1] == ImR2yCtrl_ENABLE_ON ) {
				gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.YYINTE.word |= D_IM_R2Y_YYINTE_YYW1_ENABLE;
			}
			if( gImR2yState[loop_cnt].yywEnable[ImR2yCtrl_YYW_CH_2] == ImR2yCtrl_ENABLE_ON ) {
				gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.YYINTE.word |= D_IM_R2Y_YYINTE_YYW2_ENABLE;
			}
		}

		gImIoR2yRegPtr[pipeNo]->F_R2Y.CNTL.R2YINTE.word = D_IM_R2Y_R2YINTE_ALL_ENABLE;


#ifdef CO_DEBUG_PRINT_IM_R2Y
		Ddim_Print(( "im_r2y_proc_start on clk\n" ));
#endif
		im_r2y_clk_on_iclk(im_r2y_clk_new(),  pipeNo );
		im_r2y_clk_on_clk(im_r2y_clk_new(),  pipeNo );

		// Set access enable
		for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
			// RGB Deknee
			if( gImIoR2yRegPtr[loop_cnt]->YYR.YYRCTL.bit.DKNEN != 0 ) {
				im_r2y3_set_rgb_deknee_access_enable(im_r2y3_new(),  loop_cnt, ImR2yCtrl_ENABLE_ON, ImR2yCtrl_WAIT_OFF );
			}

			// Tone control
			if(( gImIoR2yRegPtr[loop_cnt]->F_R2Y.TC.TCCTL.bit.TCEN != 0 )
			|| ( gImIoR2yRegPtr[loop_cnt]->F_R2Y.TC.TCCTL.bit.TCYBEN != 0 )) {
				im_r2y_set_tone_control_tbl_access_enable(im_r2y_ctrl_new(), loop_cnt, ImR2yCtrl_ENABLE_ON, ImR2yCtrl_WAIT_OFF );
			}

			// BTC Luminance evaluation
			if( gImIoR2yRegPtr[loop_cnt]->F_R2Y.BTC.TCTCTL.bit.TCTEN != 0 ) {
				im_r2y_ctrl2_set_luminance_evaluation_tbl_access_enable(im_r2y_ctrl2_new(), loop_cnt, ImR2yCtrl_ENABLE_ON, ImR2yCtrl_WAIT_OFF );
			}

			// BTC histogram
			if( gImIoR2yRegPtr[loop_cnt]->F_R2Y.BTC.TCHSCTL.bit.TCHSEN != 0 ) {
				im_r2y_ctrl2_set_btc_histogram_tbl_access_enable(im_r2y_ctrl2_new(), loop_cnt, ImR2yCtrl_ENABLE_ON, ImR2yCtrl_WAIT_OFF );
			}

			// Gamma
			if( gImIoR2yRegPtr[loop_cnt]->F_R2Y.GAM.GMCTL.bit.GMEN != 0 ) {
				im_r2y_ctrl2_set_gamma_tbl_access_enable(im_r2y_ctrl2_new(),  loop_cnt, ImR2yCtrl_ENABLE_ON, ImR2yCtrl_WAIT_OFF );
				im_r2y_ctrl2_set_gamma_yb_tbl_access_enable(im_r2y_ctrl2_new(),  loop_cnt, ImR2yCtrl_ENABLE_ON, ImR2yCtrl_WAIT_OFF );
			}

			// High frequency EdgeEnhance
			if( gImIoR2yRegPtr[loop_cnt]->F_R2Y.EGHW.EGHWCTL.bit.EGHWEN != 0 ) {
				im_r2y_edge_set_high_edge_scl_tbl_access_enable(im_r2y_edge_new(),  loop_cnt, ImR2yCtrl_ENABLE_ON, ImR2yCtrl_WAIT_OFF );
				if( gImIoR2yRegPtr[loop_cnt]->F_R2Y.EGHW.EGHWCTL.bit.EGHWTC != 0 ) {
					im_r2y_edge_set_high_edge_step_tbl_access_enable(im_r2y_edge_new(),  loop_cnt, ImR2yCtrl_ENABLE_ON, ImR2yCtrl_WAIT_OFF );
				}
			}

			// Medium frequency EdgeEnhance
			if( gImIoR2yRegPtr[loop_cnt]->F_R2Y.EGMW.EGMWCTL.bit.EGMWEN != 0 ) {
				im_r2y_edge_set_medium_edge_scl_tbl_access_enable(im_r2y_edge_new(),  loop_cnt, ImR2yCtrl_ENABLE_ON, ImR2yCtrl_WAIT_OFF );
				if( gImIoR2yRegPtr[loop_cnt]->F_R2Y.EGMW.EGMWCTL.bit.EGMWTC != 0 ) {
					im_r2y_edge_set_medium_edge_step_tbl_access_enable(im_r2y_edge_new(),  loop_cnt, ImR2yCtrl_ENABLE_ON, ImR2yCtrl_WAIT_OFF );
				}
			}

			// Low frequency EdgeEnhance
			if( gImIoR2yRegPtr[loop_cnt]->F_R2Y.EGLW.EGLWCTL.bit.EGLWEN != 0 ) {
				im_r2y_edge_set_low_edge_scl_tbl_access_enable(im_r2y_edge_new(),  loop_cnt, ImR2yCtrl_ENABLE_ON, ImR2yCtrl_WAIT_OFF );
				if( gImIoR2yRegPtr[loop_cnt]->F_R2Y.EGLW.EGLWCTL.bit.EGLWTC != 0 ) {
					im_r2y_edge_set_low_edge_step_tbl_access_enable(im_r2y_edge_new(),  loop_cnt, ImR2yCtrl_ENABLE_ON, ImR2yCtrl_WAIT_OFF );
				}
			}

			// Map scale
			if((( gImIoR2yRegPtr[loop_cnt]->F_R2Y.EGHW.EGHWCTL.bit.EGHWEN != 0 )
			 && ( gImIoR2yRegPtr[loop_cnt]->F_R2Y.EGHW.EGHWCTL.bit.EGHWMP != 0 ))
			|| (( gImIoR2yRegPtr[loop_cnt]->F_R2Y.EGMW.EGMWCTL.bit.EGMWEN != 0 )
			 && ( gImIoR2yRegPtr[loop_cnt]->F_R2Y.EGMW.EGMWCTL.bit.EGMWMP != 0 ))
			|| (( gImIoR2yRegPtr[loop_cnt]->F_R2Y.EGLW.EGLWCTL.bit.EGLWEN != 0 )
			 && ( gImIoR2yRegPtr[loop_cnt]->F_R2Y.EGLW.EGLWCTL.bit.EGLWMP != 0 ))) {
				im_r2y_ctrl3_set_map_scl_tbl_access_enable(im_r2y_ctrl3_new(),  loop_cnt, ImR2yCtrl_ENABLE_ON, ImR2yCtrl_WAIT_OFF );
			}
		}

		// YYR Histogram
		im_r2y3_set_histogram_access_enable(im_r2y3_new(),  pipeNo, ImR2yCtrl_ENABLE_ON, ImR2yCtrl_WAIT_OFF );

		gImIoR2yRegPtr[pipeNo]->R2Y_CMN.RAMAEN.bit.YYRAEN_YYR = 1;
		for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
			if( gImR2yState[loop_cnt].yywEnable[ImR2yCtrl_YYW_CH_0] != 0 ){
				gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.RAMAEN.bit.YW0AEN_YYW0 = 1;
				if( gImIoR2yRegPtr[loop_cnt]->YYW.YYW0MD.bit.RSZ0MD == ImR2yCtrl_RSZ_BICUBIC ){
					gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.RAMAEN.bit.YW0AEN_YYW0_BICUBIC = 1;
				}
				if( gImIoR2yRegPtr[loop_cnt]->YYW.EE0CTL.bit.EE0EN != 0 ){
					gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.RAMAEN.bit.YW0AEN_YYW0_EDGE = 1;
				}
				if( gImR2yState[loop_cnt].outputMode0a != ImR2yCtrl_YYW0A_OUTPUT_MODE_STOP ){
					gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.RAMAEN.bit.YW0AEN_YYW0A = 1;
				}
			}
			if( gImR2yState[loop_cnt].yywEnable[ImR2yCtrl_YYW_CH_1] != 0 ){
				gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.RAMAEN.bit.YW1AEN_YYW1 = 1;
				if( gImIoR2yRegPtr[loop_cnt]->YYW.YYW1MD.bit.RSZ1MD == ImR2yCtrl_RSZ_BICUBIC ){
					gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.RAMAEN.bit.YW1AEN_YYW1_BICUBIC = 1;
				}
				if( gImIoR2yRegPtr[loop_cnt]->YYW.EE1CTL.bit.EE1EN != 0 ){
					gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.RAMAEN.bit.YW1AEN_YYW1_EDGE = 1;
				}
			}
			gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.RAMAEN.bit.YW2AEN = (gImR2yState[loop_cnt].yywEnable[ImR2yCtrl_YYW_CH_2] != 0)?(1):(0);
		}

		gImIoR2yRegPtr[pipeNo]->F_R2Y.CNTL.FLTAEN.bit.YCFAEN = 1;

		im_r2y_wait_usec( ImR2yUtils_SRAM_WAIT_USEC );

#ifdef CO_DEBUG_PRINT_IM_R2Y
		Ddim_Print(( "im_r2y_proc_start clear event flag\n" ));
#endif

		if( im_r2y_check_target_pipe_no_1( pipeNo ) ){
			flgptn |= D_IM_R2Y1_INT_FLG_ALL;
		}
		if( im_r2y_check_target_pipe_no_2( pipeNo ) ){
			flgptn |= D_IM_R2Y2_INT_FLG_ALL;
		}

		// Clear of Event Flag
		ercd = DDIM_User_Clr_Flg( FID_IM_R2Y, ~flgptn );
		if( ercd != D_DDIM_USER_E_OK ) {
			Ddim_Print(( "im_r2y_proc_start: invalid FID\n" ));
			retcd = D_IM_R2Y_SYSTEM_ERROR;
			break;
		}

		for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
			gImR2yState[loop_cnt].wasStarted = D_IM_R2Y_TRUE;
		}

#ifdef CO_DEBUG_PRINT_IM_R2Y
		Ddim_Print(( "im_r2y_proc_start check macro busy state\n" ));
#endif
#ifndef D_IM_R2Y_DEBUG_ON_PC
		Im_R2Y_Dsb();
		for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
			while( ImR2yCtrl_YYR_IS_ACTIVATED(loop_cnt) ) {
				;	// DO NOTHING
			}

			while( im_r2y_yyw_is_activated(loop_cnt) ) {
				;	// DO NOTHING
			}
		}
#endif

#ifdef CO_DEBUG_PRINT_IM_R2Y
		Ddim_Print(( "im_r2y_proc_start enable YYW\n" ));
#endif
		for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
			if( gImR2yState[loop_cnt].yywEnable[ImR2yCtrl_YYW_CH_0] == ImR2yCtrl_ENABLE_ON ) {
				gImR2yState[loop_cnt].busyState |= D_IM_R2Y_STATE_BUSY_YYW0;
			}
			if( gImR2yState[loop_cnt].yywEnable[ImR2yCtrl_YYW_CH_1] == ImR2yCtrl_ENABLE_ON ) {
				gImR2yState[loop_cnt].busyState |= D_IM_R2Y_STATE_BUSY_YYW1;
			}
			if( gImR2yState[loop_cnt].yywEnable[ImR2yCtrl_YYW_CH_2] == ImR2yCtrl_ENABLE_ON ) {
				gImR2yState[loop_cnt].busyState |= D_IM_R2Y_STATE_BUSY_YYW2;
			}
		}
		gImIoR2yRegPtr[pipeNo]->YYW.YYWTRG.bit.YYWTRG = D_IM_R2Y_YYWTRG_ON;

#ifdef CO_DEBUG_PRINT_IM_R2Y
		Ddim_Print(( "im_r2y_proc_start enable F_R2Y\n" ));
#endif
		for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
			gImR2yState[loop_cnt].busyState |= D_IM_R2Y_STATE_BUSY_F_R2Y;
		}
		gImIoR2yRegPtr[pipeNo]->F_R2Y.CNTL.CNTL.bit.TRG = D_IM_R2Y_FR2YTRG_ON;
#ifdef CO_DEBUG_ON_PC
		for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
			gImIoR2yRegPtr[pipeNo]->F_R2Y.CNTL.CNTL.bit.TRG = D_IM_R2Y_FR2YTRG_BUSY;
		}
#endif

#ifdef CO_DEBUG_PRINT_IM_R2Y
		Ddim_Print(( "im_r2y_proc_start enable YYR\n" ));
#endif
		for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
			gImR2yState[loop_cnt].busyState |= D_IM_R2Y_STATE_BUSY_YYR;
		}
		gImIoR2yRegPtr[pipeNo]->YYR.YYRTRG.bit.YYRTRG = D_IM_R2Y_YYRTRG_ON;

		retcd = D_DDIM_OK;
		break;
	}

#ifdef CO_DEBUG_PRINT_IM_R2Y
	Ddim_Print(( "im_r2y_proc_start off pclk\n" ));
#endif
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );

#ifdef D_IM_R2Y_DEBUG_ON_PC
	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		if( gIM_R2Y_macro_fake_finish[loop_cnt] != 0 ) {
			gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.YYINTF.word = 0;
			gImIoR2yRegPtr[loop_cnt]->F_R2Y.CNTL.R2YINTF.word = 0;
			gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.YYINTF.bit.__YYREF = 1;
			if( gImR2yState[loop_cnt].yywEnable[ImR2yCtrl_YYW_CH_0] == ImR2yCtrl_ENABLE_ON ) {
				gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.YYINTF.bit.__YYW0EF = 1;
				if( gImR2yState[loop_cnt].outputMode0a != ImR2yCtrl_YYW0A_OUTPUT_MODE_STOP ){
					gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.YYINTF.bit.__YYWAEF = 1;
				}
				if( (gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.LINTLV.bit.LINTLV_0 != 0)
				 && (gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.LINTSEL.bit.LINTS_0 == 0) ) {
					gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.YYINTF.bit.__LINT0F = 1;
				}
				if( (gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.LINTLV.bit.LINTLV_1 != 0)
				 && (gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.LINTSEL.bit.LINTS_1 == 0) ) {
					gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.YYINTF.bit.__LINT1F = 1;
				}
				if( (gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.LINTLV.bit.LINTLV_2 != 0)
				 && (gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.LINTSEL.bit.LINTS_2 == 0) ) {
					gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.YYINTF.bit.__LINT2F = 1;
				}
			}
			if( gImR2yState[loop_cnt].yywEnable[ImR2yCtrl_YYW_CH_1] == ImR2yCtrl_ENABLE_ON ) {
				gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.YYINTF.bit.__YYW1EF = 1;
				if( (gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.LINTLV.bit.LINTLV_0 != 0)
				 && (gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.LINTSEL.bit.LINTS_0 == 1) ) {
					gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.YYINTF.bit.__LINT0F = 1;
				}
				if( (gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.LINTLV.bit.LINTLV_1 != 0)
				 && (gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.LINTSEL.bit.LINTS_1 == 1) ) {
					gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.YYINTF.bit.__LINT1F = 1;
				}
				if( (gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.LINTLV.bit.LINTLV_2 != 0)
				 && (gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.LINTSEL.bit.LINTS_2 == 1) ) {
					gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.YYINTF.bit.__LINT2F = 1;
				}
			}
			if( gImR2yState[loop_cnt].yywEnable[ImR2yCtrl_YYW_CH_2] == ImR2yCtrl_ENABLE_ON ) {
				gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.YYINTF.bit.__YYW2EF = 1;
			}
			gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.YYINTF.bit.__YYWEF = 1;
			if( gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANKST != 0 ) {
				gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANKST = 0;
				gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK0STS = gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK0PS;
				gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANKASTS = gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANKAPS;
				gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK1STS = gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK1PS;
				gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK2STS = gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK2PS;
			}
			im_r2y_proc_int_handler(im_r2y_proc_new(),  loop_cnt );
			gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.YYINTF.word = 0;
			im_r2y2_loop_set(im_r2y2_new(), loop_cnt);
		}
	}
#endif

	Im_R2Y_Dsb();

#ifdef CO_DEBUG_PRINT_IM_R2Y
	Ddim_Print(( "im_r2y_proc_start end\n" ));
#endif

	return retcd;
}

/* Stop R2Y process
 */
INT32 im_r2y_proc_stop(ImR2yProc *self,  kuint16 pipeNo )
{
	kuint16 loop_cnt, loop_sta, loop_end;
	kuint16 byp_bak[2], pad_bak[2], ext_b_bak[2], ext_c_bak[2];
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile R2yStateMng* gImR2yState = im_r2y_utils_get_state_mng(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_proc_stop error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_utils_get_loop_val(imR2yUtils, pipeNo, &loop_sta, &loop_end );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		gImR2yState[loop_cnt].wasStarted = D_IM_R2Y_FALSE;
	}

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	im_r2y_clk_on_iclk(im_r2y_clk_new(),  pipeNo );
	im_r2y_clk_on_clk(im_r2y_clk_new(),  pipeNo );	// D_IM_R2Y_FR2YTRG_OFF control accompanies the R2Y reset.

	for( loop_cnt = 0; loop_cnt <= 1; loop_cnt++ ){
		byp_bak[loop_cnt] = gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.R2YMODE.bit.YCFBYP;
		pad_bak[loop_cnt] = gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.R2YMODE.bit.YCFPDD;
		ext_b_bak[loop_cnt] = gImIoR2yRegPtr[loop_cnt]->YYW.YYW0MD.bit.EXTBEN;
		ext_c_bak[loop_cnt] = gImIoR2yRegPtr[loop_cnt]->YYW.YYW0MD.bit.EXTCEN;
	}

	//
	// Stop YYW
	//
	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		gImR2yState[loop_cnt].busyState &= ~(D_IM_R2Y_STATE_BUSY_YYW0 | D_IM_R2Y_STATE_BUSY_YYW1 | D_IM_R2Y_STATE_BUSY_YYW2);
	}
	gImIoR2yRegPtr[pipeNo]->YYW.YYWTRG.bit.YYWTRG = D_IM_R2Y_YYWTRG_OFF;

	Im_R2Y_Dsb();

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		while( im_r2y_yyw_is_activated(loop_cnt) ){
#ifdef CO_DEBUG_ON_PC
//			Ddim_Print(( "im_r2y_proc_stop YYW wait loop. %u\n", gImIoR2yRegPtr[loop_cnt]->YYW.YYWTRG.bit.YYWTRG ));
			gImIoR2yRegPtr[loop_cnt]->YYW.YYWTRG.bit.YYWTRG = D_IM_R2Y_YYWTRG_IDLE;
#endif
			;	// DO NOTHING
		}
	}

	//
	// Stop F_R2Y
	//
	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		gImR2yState[loop_cnt].busyState &= ~(D_IM_R2Y_STATE_BUSY_F_R2Y);
	}
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CNTL.CNTL.bit.TRG = D_IM_R2Y_FR2YTRG_OFF;
#ifdef CO_DEBUG_ON_PC
	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		gImIoR2yRegPtr[loop_cnt]->F_R2Y.CNTL.CNTL.bit.TRG = ImR2y_FR2YTRG_IDLE;
	}
#endif

	//
	// Stop YYR
	//
	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		gImR2yState[loop_cnt].busyState &= ~(D_IM_R2Y_STATE_BUSY_YYR);
	}
	gImIoR2yRegPtr[pipeNo]->YYR.YYRTRG.bit.YYRTRG = D_IM_R2Y_YYRTRG_OFF;

	Im_R2Y_Dsb();

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		while( ImR2yCtrl_YYR_IS_ACTIVATED(loop_cnt) ) {
#ifdef CO_DEBUG_ON_PC
//			Ddim_Print(( "im_r2y_proc_stop YYR wait loop. %u\n", gImIoR2yRegPtr[loop_cnt]->YYR.YYRTRG.bit.YYRTRG ));
			gImIoR2yRegPtr[loop_cnt]->YYR.YYRTRG.bit.YYRTRG = ImR2yCtrl_YYRTRG_IDLE;
#endif
			;	// DO NOTHING
		}
	}

	gImIoR2yRegPtr[pipeNo]->R2Y_CMN.R2YMODE.bit.YCFBYP  = ImR2yCtrl_ENABLE_OFF;
	gImIoR2yRegPtr[pipeNo]->R2Y_CMN.R2YMODE.bit.YCFPDD  = ImR2yCtrl_ENABLE_OFF;
	gImIoR2yRegPtr[pipeNo]->YYW.YYW0MD.bit.EXTBEN = ImR2yCtrl_ENABLE_OFF;
	gImIoR2yRegPtr[pipeNo]->YYW.YYW0MD.bit.EXTCEN = ImR2yCtrl_ENABLE_OFF;

	im_r2y_wait_usec( 10 );
	Im_R2Y_Dsb();

	gImIoR2yRegPtr[pipeNo]->YYR.YYRTRG.bit.YYRTRG = D_IM_R2Y_YYRTRG_ON;

	im_r2y_wait_usec( 10 );
	Im_R2Y_Dsb();

	gImIoR2yRegPtr[pipeNo]->YYR.YYRTRG.bit.YYRTRG = D_IM_R2Y_YYRTRG_OFF;

	Im_R2Y_Dsb();

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		while( ImR2yCtrl_YYR_IS_ACTIVATED(loop_cnt) ) {
#ifdef CO_DEBUG_ON_PC
//			Ddim_Print(( "im_r2y_proc_stop YYR wait loop. %u\n", gImIoR2yRegPtr[loop_cnt]->YYR.YYRTRG.bit.YYRTRG ));
			gImIoR2yRegPtr[loop_cnt]->YYR.YYRTRG.bit.YYRTRG = ImR2yCtrl_YYRTRG_IDLE;
#endif
			;	// DO NOTHING
		}
	}

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.R2YMODE.bit.YCFBYP = byp_bak[loop_cnt];
		gImIoR2yRegPtr[loop_cnt]->R2Y_CMN.R2YMODE.bit.YCFPDD = pad_bak[loop_cnt];
		gImIoR2yRegPtr[loop_cnt]->YYW.YYW0MD.bit.EXTBEN = ext_b_bak[loop_cnt];
		gImIoR2yRegPtr[loop_cnt]->YYW.YYW0MD.bit.EXTCEN = ext_c_bak[loop_cnt];
	}

	// Clear of All Interrupt disable
	gImIoR2yRegPtr[pipeNo]->R2Y_CMN.YYINTE.word = D_IM_R2Y_YYINTE_DISABLE;
	gImIoR2yRegPtr[pipeNo]->R2Y_CMN.YYINTF.word = D_IM_R2Y_YYINTF_ALL_CLR;

	gImIoR2yRegPtr[pipeNo]->F_R2Y.CNTL.R2YINTE.word = D_IM_R2Y_R2YINTE_DISABLE;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CNTL.R2YINTF.word = D_IM_R2Y_R2YINTF_ALL_CLR;

	// RGB Deknee
	im_r2y3_set_rgb_deknee_access_enable(im_r2y3_new(),  pipeNo, ImR2yCtrl_ENABLE_OFF, ImR2yCtrl_WAIT_OFF );

	// Tone control
	im_r2y_set_tone_control_tbl_access_enable(im_r2y_ctrl_new(), pipeNo, ImR2yCtrl_ENABLE_OFF, ImR2yCtrl_WAIT_OFF );

	// BTC Luminance evaluation
	im_r2y_ctrl2_set_luminance_evaluation_tbl_access_enable(im_r2y_ctrl2_new(), pipeNo, ImR2yCtrl_ENABLE_OFF, ImR2yCtrl_WAIT_OFF );

	// BTC histogram
	im_r2y_ctrl2_set_btc_histogram_tbl_access_enable(im_r2y_ctrl2_new(), pipeNo, ImR2yCtrl_ENABLE_OFF, ImR2yCtrl_WAIT_OFF );

	// Gamma
	im_r2y_ctrl2_set_gamma_tbl_access_enable(im_r2y_ctrl2_new(),  pipeNo, ImR2yCtrl_ENABLE_OFF, ImR2yCtrl_WAIT_OFF );
	im_r2y_ctrl2_set_gamma_yb_tbl_access_enable(im_r2y_ctrl2_new(),  pipeNo, ImR2yCtrl_ENABLE_OFF, ImR2yCtrl_WAIT_OFF );

	// High frequency EdgeEnhance
	im_r2y_edge_set_high_edge_scl_tbl_access_enable(im_r2y_edge_new(),  pipeNo, ImR2yCtrl_ENABLE_OFF, ImR2yCtrl_WAIT_OFF );
	im_r2y_edge_set_high_edge_step_tbl_access_enable(im_r2y_edge_new(),  pipeNo, ImR2yCtrl_ENABLE_OFF, ImR2yCtrl_WAIT_OFF );

	// Medium frequency EdgeEnhance
	im_r2y_edge_set_medium_edge_scl_tbl_access_enable(im_r2y_edge_new(),  pipeNo, ImR2yCtrl_ENABLE_OFF, ImR2yCtrl_WAIT_OFF );
	im_r2y_edge_set_medium_edge_step_tbl_access_enable(im_r2y_edge_new(),  pipeNo, ImR2yCtrl_ENABLE_OFF, ImR2yCtrl_WAIT_OFF );

	// Low frequency EdgeEnhance
	im_r2y_edge_set_low_edge_scl_tbl_access_enable(im_r2y_edge_new(),  pipeNo, ImR2yCtrl_ENABLE_OFF, ImR2yCtrl_WAIT_OFF );
	im_r2y_edge_set_low_edge_step_tbl_access_enable(im_r2y_edge_new(),  pipeNo, ImR2yCtrl_ENABLE_OFF, ImR2yCtrl_WAIT_OFF );

	// Map scale
	im_r2y_ctrl3_set_map_scl_tbl_access_enable(im_r2y_ctrl3_new(),  pipeNo, ImR2yCtrl_ENABLE_OFF, ImR2yCtrl_WAIT_OFF );

	// YYR Histogram
	im_r2y3_set_histogram_access_enable(im_r2y3_new(),  pipeNo, ImR2yCtrl_ENABLE_OFF, ImR2yCtrl_WAIT_OFF );

	gImIoR2yRegPtr[pipeNo]->R2Y_CMN.RAMAEN.bit.YYRAEN_YYR          = 0;
	gImIoR2yRegPtr[pipeNo]->R2Y_CMN.RAMAEN.bit.YW0AEN_YYW0         = 0;
	gImIoR2yRegPtr[pipeNo]->R2Y_CMN.RAMAEN.bit.YW0AEN_YYW0_BICUBIC = 0;
	gImIoR2yRegPtr[pipeNo]->R2Y_CMN.RAMAEN.bit.YW0AEN_YYW0_EDGE    = 0;
	gImIoR2yRegPtr[pipeNo]->R2Y_CMN.RAMAEN.bit.YW0AEN_YYW0A        = 0;
	gImIoR2yRegPtr[pipeNo]->R2Y_CMN.RAMAEN.bit.YW1AEN_YYW1         = 0;
	gImIoR2yRegPtr[pipeNo]->R2Y_CMN.RAMAEN.bit.YW1AEN_YYW1_BICUBIC = 0;
	gImIoR2yRegPtr[pipeNo]->R2Y_CMN.RAMAEN.bit.YW1AEN_YYW1_EDGE    = 0;
	gImIoR2yRegPtr[pipeNo]->R2Y_CMN.RAMAEN.bit.YW2AEN              = 0;

	gImIoR2yRegPtr[pipeNo]->F_R2Y.CNTL.FLTAEN.bit.YCFAEN = 0;

	im_r2y_clk_force_off_clk(im_r2y_clk_new(), pipeNo );
	im_r2y_clk_force_off_iclk(im_r2y_clk_new(),  pipeNo );
	im_r2y_clk_force_off_pclk(im_r2y_clk_new(),  pipeNo );

	Im_R2Y_Dsb();

	return D_DDIM_OK;
}

/* Wait end of R2Y macro.
 */
INT32 im_r2y_proc_waitend(ImR2yProc *self,  DDIM_USER_FLGPTN* const p_flgptn, DDIM_USER_FLGPTN waiptn, DDIM_USER_TMO tmout )
{
	DDIM_USER_FLGPTN	flgptn;
	DDIM_USER_ER		ercd;

#ifdef CO_DEBUG_PRINT_IM_R2Y
	Ddim_Print(( "im_r2y_proc_waitend begin\n" ));
#endif

#ifdef CO_PARAM_CHECK
	if( (waiptn & D_IM_R2Y_INT_FLG_ALL) != waiptn ) {
		Ddim_Assertion(("im_r2y_proc_waitend error. waiptn\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif
	Im_R2Y_Dsb();

	switch( DDIM_User_Twai_Flg( FID_IM_R2Y, waiptn, D_DDIM_USER_TWF_ORW, &flgptn, tmout ) ) {
		case D_DDIM_USER_E_OK:
#ifdef CO_DEBUG_PRINT_IM_R2Y
		Ddim_Print(( "im_r2y_proc_waitend twai_flg OK return\n" ));
#endif
			flgptn = waiptn & flgptn;
			ercd = DDIM_User_Clr_Flg( FID_IM_R2Y, ~flgptn );
			if( ercd != D_DDIM_USER_E_OK ) {
				Ddim_Print(( "im_r2y_proc_start: invalid FID.\n" ));
				return D_IM_R2Y_SYSTEM_ERROR;
			}
			if( p_flgptn != NULL ) {
				*p_flgptn = flgptn;
			}
			return D_DDIM_OK;
		case D_DDIM_USER_E_TMOUT:
#ifdef CO_DEBUG_PRINT_IM_R2Y
		Ddim_Print(( "im_r2y_proc_waitend twai_flg TimeOut return\n" ));
#endif
			return D_IM_R2Y_TIMEOUT;
		default:
#ifdef CO_DEBUG_PRINT_IM_R2Y
		Ddim_Print(( "im_r2y_proc_waitend twai_flg NG return\n" ));
#endif
			return ImR2yUtils_PARAM_ERROR;
	}
}

/* R2Y Interrupt Handler
 */
void im_r2y_proc_int_handler(ImR2yProc *self,  kuint16 pipeNo )
{
	UINT32			loopcnt;
	DDIM_USER_ER	ercd;
	kulong			r2y_inte;
	kulong			r2y_intf;
	kulong			r2y_intf_clr;
	kulong			f_r2y_inte;
	kulong			f_r2y_intf;
	kulong			f_r2y_intf_clr;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile R2yStateMng* gImR2yState = im_r2y_utils_get_state_mng(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( pipeNo >= ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_proc_int_handler error. pipeNo>=ImR2yCtrl_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_DEBUG_PRINT_IM_R2Y
	Ddim_Print(( "im_r2y_proc_int_handler begin\n" ));
#endif

#ifdef CO_DEBUG_PRINT_IM_R2Y
	Ddim_Print(( "im_r2y_proc_int_handler on pclk\n" ));
#endif
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );


	if( gImR2yState[pipeNo].videoPhotoMode == ImR2yUtils_MODE_SDRAM_INPUT ) {
		if( !(ImR2yCtrl_YYR_IS_ACTIVATED(pipeNo) || im_r2y_yyw_is_activated(pipeNo) || (gImIoR2yRegPtr[pipeNo]->YYW.YYWCTL.bit.YYWCSE != 0)) ) {
#ifdef CO_DEBUG_PRINT_IM_R2Y
			Ddim_Print(( "im_r2y_proc_int_handler off clk\n" ));
#endif
			im_r2y_clk_off_clk(im_r2y_clk_new(),  pipeNo );
			im_r2y_clk_off_iclk(im_r2y_clk_new(),  pipeNo );
		}
	}
	Im_R2Y_Dsb();

	r2y_inte = gImIoR2yRegPtr[pipeNo]->R2Y_CMN.YYINTE.word;
	r2y_intf = gImIoR2yRegPtr[pipeNo]->R2Y_CMN.YYINTF.word;
	r2y_intf_clr = 0;
	f_r2y_inte = gImIoR2yRegPtr[pipeNo]->F_R2Y.CNTL.R2YINTE.word;
	f_r2y_intf = gImIoR2yRegPtr[pipeNo]->F_R2Y.CNTL.R2YINTF.word;
	f_r2y_intf_clr = 0;

#ifdef CO_DEBUG_PRINT_IM_R2Y
	Ddim_Print(( "im_r2y_proc_int_handler inte=0x%lx, intf=0x%lx f_inte=0x%lx f_intf=0x%lx\n", r2y_inte, r2y_intf, f_r2y_inte, f_r2y_intf ));
#endif

	// Call of Callback API for interrupt status

	for( loopcnt = 0; loopcnt < (sizeof(gim_r2y_inttbl_jdsr2y[0]) / sizeof(gim_r2y_inttbl_jdsr2y[0][0])); loopcnt++ ) {
		if( ((r2y_intf & gim_r2y_inttbl_jdsr2y[pipeNo][loopcnt].flg_bitmask) != 0)
		 && ((r2y_inte & gim_r2y_inttbl_jdsr2y[pipeNo][loopcnt].ena_bitmask) != 0) ) {

#ifdef CO_DEBUG_PRINT_IM_R2Y
			Ddim_Print(( "im_r2y_proc_int_handler begin JDSR2Y 0x%x\n", gim_r2y_inttbl_jdsr2y[pipeNo][loopcnt].flg_bitmask ));
#endif

			if(( gim_r2y_inttbl_jdsr2y[pipeNo][loopcnt].intStatus == ImR2yCtrl_INT_STATE_YYW0_END1 )
			|| ( gim_r2y_inttbl_jdsr2y[pipeNo][loopcnt].intStatus == ImR2yCtrl_INT_STATE_YYW0_END2 )) {
				imR2yLatestAddrUpdate( pipeNo, ImR2yCtrl_YYW_CH_0 );
			}
			else
			if(( gim_r2y_inttbl_jdsr2y[pipeNo][loopcnt].intStatus == ImR2yCtrl_INT_STATE_YYW1_END1 )
			|| ( gim_r2y_inttbl_jdsr2y[pipeNo][loopcnt].intStatus == ImR2yCtrl_INT_STATE_YYW1_END2 )) {
				imR2yLatestAddrUpdate( pipeNo, ImR2yCtrl_YYW_CH_1 );
			}
			else
			if(( gim_r2y_inttbl_jdsr2y[pipeNo][loopcnt].intStatus == ImR2yCtrl_INT_STATE_YYW2_END1 )
			|| ( gim_r2y_inttbl_jdsr2y[pipeNo][loopcnt].intStatus == ImR2yCtrl_INT_STATE_YYW2_END2 )) {
				imR2yLatestAddrUpdate( pipeNo, ImR2yCtrl_YYW_CH_2 );
			}
			else
			if(( gim_r2y_inttbl_jdsr2y[pipeNo][loopcnt].intStatus == ImR2yCtrl_INT_STATE_YYW0A_END1 )
			|| ( gim_r2y_inttbl_jdsr2y[pipeNo][loopcnt].intStatus == ImR2yCtrl_INT_STATE_YYW0A_END2 )) {
				imR2yLatestAddrUpdate( pipeNo, ImR2yCtrl_YYW_CH_0A );
			}

			gImR2yState[pipeNo].intStatus = gim_r2y_inttbl_jdsr2y[pipeNo][loopcnt].intStatus;
			gImR2yState[pipeNo].busyState &= ~(gim_r2y_inttbl_jdsr2y[pipeNo][loopcnt].busyState);

			r2y_intf_clr |= gim_r2y_inttbl_jdsr2y[pipeNo][loopcnt].flg_bitmask;

			ercd = DDIM_User_Set_Flg( FID_IM_R2Y, gim_r2y_inttbl_jdsr2y[pipeNo][loopcnt].waitflg );
			if( ercd != D_DDIM_USER_E_OK ) {
				Ddim_Print(( "im_r2y_proc_int_handler: invalid FID. 0x%lx\n", gim_r2y_inttbl_jdsr2y[pipeNo][loopcnt].waitflg ));
			}

			if (gImR2yState[pipeNo].r2yUserHandler) {
				gImR2yState[pipeNo].r2yUserHandler( (UINT32*)&gImR2yState[pipeNo].intStatus, gImR2yState[pipeNo].userParam );
			}
		}
	}

	for( loopcnt = 0; loopcnt < (sizeof(gim_r2y_inttbl_fr2y[0]) / sizeof(gim_r2y_inttbl_fr2y[0][0])); loopcnt++ ) {
		if( ((f_r2y_intf & gim_r2y_inttbl_fr2y[pipeNo][loopcnt].flg_bitmask) != 0)
		 && ((f_r2y_inte & gim_r2y_inttbl_fr2y[pipeNo][loopcnt].ena_bitmask) != 0) ) {

#ifdef CO_DEBUG_PRINT_IM_R2Y
			Ddim_Print(( "im_r2y_proc_int_handler begin FR2Y 0x%x\n", gim_r2y_inttbl_fr2y[pipeNo][loopcnt].flg_bitmask ));
#endif

			gImR2yState[pipeNo].intStatus = gim_r2y_inttbl_fr2y[pipeNo][loopcnt].intStatus;
			gImR2yState[pipeNo].busyState &= ~(gim_r2y_inttbl_fr2y[pipeNo][loopcnt].busyState);

			f_r2y_intf_clr |= gim_r2y_inttbl_fr2y[pipeNo][loopcnt].flg_bitmask;

			ercd = DDIM_User_Set_Flg( FID_IM_R2Y, gim_r2y_inttbl_fr2y[pipeNo][loopcnt].waitflg );
			if( ercd != D_DDIM_USER_E_OK ) {
				Ddim_Print(( "im_r2y_proc_int_handler: invalid FID. 0x%lx\n", gim_r2y_inttbl_fr2y[pipeNo][loopcnt].waitflg ));
			}

			if (gImR2yState[pipeNo].r2yUserHandler) {
				gImR2yState[pipeNo].r2yUserHandler( (UINT32*)&gImR2yState[pipeNo].intStatus, gImR2yState[pipeNo].userParam );
			}
		}
	}

	// Clear interrupt
	gImIoR2yRegPtr[pipeNo]->R2Y_CMN.YYINTF.word = r2y_intf_clr;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CNTL.R2YINTF.word = f_r2y_intf_clr;


#ifdef CO_DEBUG_PRINT_IM_R2Y
	Ddim_Print(( "im_r2y_proc_int_handler intf=0x%lx, %0xlx\n", gImIoR2yRegPtr[pipeNo]->R2Y_CMN.YYINTF.word, gImIoR2yRegPtr[pipeNo]->F_R2Y.CNTL.R2YINTF.word ));
#endif

#ifdef CO_DEBUG_PRINT_IM_R2Y
	Ddim_Print(( "im_r2y_proc_int_handler off pclk\n" ));
#endif
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
	Im_R2Y_Dsb();

#ifdef CO_DEBUG_PRINT_IM_R2Y
	Ddim_Print(( "im_r2y_proc_int_handler end\n" ));
#endif
}

ImR2yProc *im_r2y_proc_new(void)
{
	ImR2yProc* self = k_object_new_with_private(IM_TYPE_R2Y_PROC,sizeof(ImR2yProcPrivate));
	return self;
}
