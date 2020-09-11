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
#define D_IM_R2Y_FR2YTRG_IDLE			(2)
#define D_IM_R2Y_FR2YTRG_BUSY			(3)

#define D_IM_R2Y_YYWTRG_OFF				(0)
#define D_IM_R2Y_YYWTRG_ON				(1)
#define D_IM_R2Y_YYWTRG_BUSY			(3)

#define D_IM_R2Y_YYRTRG_ON				(1)

// wait usec
//TODO 加了一个
#define im_r2y_wait_usec( usec )				Dd_ARM_Wait_ns( (usec) * 1000 )

#ifdef D_IM_R2Y_DEBUG_ON_PC
volatile UCHAR gIM_R2Y_macro_fake_finish[D_IM_R2Y_PIPE_COUNT] = {0,0};
#endif


struct _ImR2yProcPrivate
{
	int a;
};

// Interrupt parameter table
typedef struct {
	ULONG					flg_bitmask;		// Bitmask of interrupt flag.
	ULONG					ena_bitmask;		// Bitmask of inaerrupt enable.
	ULONG					waitflg;			// Value of set_flg.
	ULONG					int_status;			// Value of gIM_R2Y_State.int_status.
	ULONG					busy_state;			// Value of gIM_R2Y_State.busy_state.
} T_IM_R2Y_INTFLG_TBL;

//
// Interrupt parameter table
//
static const T_IM_R2Y_INTFLG_TBL gim_r2y_inttbl_jdsr2y[D_IM_R2Y_PIPE_COUNT][13] = {
	{
		{ 0x00000001, 0x00000001, D_IM_R2Y1_INT_FLG_YYR_END,    D_IM_R2Y1_INT_STATE_YYR_END,    D_IM_R2Y_STATE_BUSY_YYR },		// YYREE
		{ 0x00000010, 0x00000010, D_IM_R2Y1_INT_FLG_YYW0_END,   D_IM_R2Y1_INT_STATE_YYW0_END,   D_IM_R2Y_STATE_BUSY_YYW0 },		// YYW0EE
		{ 0x00000020, 0x00000020, D_IM_R2Y1_INT_FLG_YYW0A_END,  D_IM_R2Y1_INT_STATE_YYW0A_END,  D_IM_R2Y_STATE_BUSY_YYW0A },	// YYWAEE
		{ 0x00000040, 0x00000040, D_IM_R2Y1_INT_FLG_YYW1_END,   D_IM_R2Y1_INT_STATE_YYW1_END,   D_IM_R2Y_STATE_BUSY_YYW1 },		// YYW1EE
		{ 0x00000080, 0x00000080, D_IM_R2Y1_INT_FLG_YYW2_END,   D_IM_R2Y1_INT_STATE_YYW2_END,   D_IM_R2Y_STATE_BUSY_YYW2 },		// YYW2EE
		{ 0x00000100, 0x00000100, D_IM_R2Y1_INT_FLG_YYWALL_END, D_IM_R2Y1_INT_STATE_YYWALL_END, (D_IM_R2Y_STATE_BUSY_YYW0 | D_IM_R2Y_STATE_BUSY_YYW0A | D_IM_R2Y_STATE_BUSY_YYW1 | D_IM_R2Y_STATE_BUSY_YYW2 ) },	// YYWEE
		{ 0x00001000, 0x00001000, D_IM_R2Y1_INT_FLG_LINE0_END,  D_IM_R2Y1_INT_STATE_LINE0_END,  0 },	// LINT0E
		{ 0x00002000, 0x00002000, D_IM_R2Y1_INT_FLG_LINE1_END,  D_IM_R2Y1_INT_STATE_LINE1_END,  0 },	// LINT1E
		{ 0x00004000, 0x00004000, D_IM_R2Y1_INT_FLG_LINE2_END,  D_IM_R2Y1_INT_STATE_LINE2_END,  0 },	// LINT2E
		{ 0x00010000, 0x00010000, D_IM_R2Y1_INT_FLG_YYR_ERR,    D_IM_R2Y1_INT_STATE_YYR_ERR,    D_IM_R2Y_STATE_BUSY_YYR },		// YYRERE
		{ 0x00020000, 0x00020000, D_IM_R2Y1_INT_FLG_YYW_ERR,    D_IM_R2Y1_INT_STATE_YYW_ERR,    (D_IM_R2Y_STATE_BUSY_YYW0 | D_IM_R2Y_STATE_BUSY_YYW0A | D_IM_R2Y_STATE_BUSY_YYW1 | D_IM_R2Y_STATE_BUSY_YYW2) },	// YYWERE
		{ 0x00100000, 0x00100000, D_IM_R2Y1_INT_FLG_AXR_ERR,    D_IM_R2Y1_INT_STATE_AXR_ERR,    0 },	// AXRERE
		{ 0x00200000, 0x00200000, D_IM_R2Y1_INT_FLG_AXW_ERR,    D_IM_R2Y1_INT_STATE_AXW_ERR,    0 },	// AXWERE
	},
	{
		{ 0x00000001, 0x00000001, D_IM_R2Y2_INT_FLG_YYR_END,    D_IM_R2Y2_INT_STATE_YYR_END,    D_IM_R2Y_STATE_BUSY_YYR },		// YYREE
		{ 0x00000010, 0x00000010, D_IM_R2Y2_INT_FLG_YYW0_END,   D_IM_R2Y2_INT_STATE_YYW0_END,   D_IM_R2Y_STATE_BUSY_YYW0 },		// YYW0EE
		{ 0x00000020, 0x00000020, D_IM_R2Y2_INT_FLG_YYW0A_END,  D_IM_R2Y2_INT_STATE_YYW0A_END,  D_IM_R2Y_STATE_BUSY_YYW0A },	// YYWAEE
		{ 0x00000040, 0x00000040, D_IM_R2Y2_INT_FLG_YYW1_END,   D_IM_R2Y2_INT_STATE_YYW1_END,   D_IM_R2Y_STATE_BUSY_YYW1 },		// YYW1EE
		{ 0x00000080, 0x00000080, D_IM_R2Y2_INT_FLG_YYW2_END,   D_IM_R2Y2_INT_STATE_YYW2_END,   D_IM_R2Y_STATE_BUSY_YYW2 },		// YYW2EE
		{ 0x00000100, 0x00000100, D_IM_R2Y2_INT_FLG_YYWALL_END, D_IM_R2Y2_INT_STATE_YYWALL_END, (D_IM_R2Y_STATE_BUSY_YYW0 | D_IM_R2Y_STATE_BUSY_YYW0A | D_IM_R2Y_STATE_BUSY_YYW1 | D_IM_R2Y_STATE_BUSY_YYW2 ) },	// YYWEE
		{ 0x00001000, 0x00001000, D_IM_R2Y2_INT_FLG_LINE0_END,  D_IM_R2Y2_INT_STATE_LINE0_END,  0 },	// LINT0E
		{ 0x00002000, 0x00002000, D_IM_R2Y2_INT_FLG_LINE1_END,  D_IM_R2Y2_INT_STATE_LINE1_END,  0 },	// LINT1E
		{ 0x00004000, 0x00004000, D_IM_R2Y2_INT_FLG_LINE2_END,  D_IM_R2Y2_INT_STATE_LINE2_END,  0 },	// LINT2E
		{ 0x00010000, 0x00010000, D_IM_R2Y2_INT_FLG_YYR_ERR,    D_IM_R2Y2_INT_STATE_YYR_ERR,    D_IM_R2Y_STATE_BUSY_YYR },		// YYRERE
		{ 0x00020000, 0x00020000, D_IM_R2Y2_INT_FLG_YYW_ERR,    D_IM_R2Y2_INT_STATE_YYW_ERR,    (D_IM_R2Y_STATE_BUSY_YYW0 | D_IM_R2Y_STATE_BUSY_YYW0A | D_IM_R2Y_STATE_BUSY_YYW1 | D_IM_R2Y_STATE_BUSY_YYW2) },	// YYWERE
		{ 0x00100000, 0x00100000, D_IM_R2Y2_INT_FLG_AXR_ERR,    D_IM_R2Y2_INT_STATE_AXR_ERR,    0 },	// AXRERE
		{ 0x00200000, 0x00200000, D_IM_R2Y2_INT_FLG_AXW_ERR,    D_IM_R2Y2_INT_STATE_AXW_ERR,    0 },	// AXWERE
	},
};

static const T_IM_R2Y_INTFLG_TBL gim_r2y_inttbl_fr2y[D_IM_R2Y_PIPE_COUNT][3] = {
	{
		{ 0x00000001, 0x00000001, D_IM_R2Y1_INT_FLG_YCFERR_ERR, D_IM_R2Y1_INT_STATE_YCFERR_ERR, 0 },	// YCFERE
		{ 0x00000010, 0x00000010, D_IM_R2Y1_INT_FLG_TCT_END,    D_IM_R2Y1_INT_STATE_TCT_END,    0 },	// TCTEE
		{ 0x00000100, 0x00000100, D_IM_R2Y1_INT_FLG_TCHS_END,   D_IM_R2Y1_INT_STATE_TCHS_END,   0 },	// TCHSEE
	},
	{
		{ 0x00000001, 0x00000001, D_IM_R2Y2_INT_FLG_YCFERR_ERR, D_IM_R2Y2_INT_STATE_YCFERR_ERR, 0 },	// YCFERE
		{ 0x00000010, 0x00000010, D_IM_R2Y2_INT_FLG_TCT_END,    D_IM_R2Y2_INT_STATE_TCT_END,    0 },	// TCTEE
		{ 0x00000100, 0x00000100, D_IM_R2Y2_INT_FLG_TCHS_END,   D_IM_R2Y2_INT_STATE_TCHS_END,   0 },	// TCHSEE
	},
};


/*
 * DECLS
 */
static VOID imR2yLatestAddrUpdate( UCHAR pipe_no, const UINT32 yyw_no );
static UCHAR imR2yIsActFr2y( UCHAR pipe_no );

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

static VOID imR2yLatestAddrUpdate( UCHAR pipe_no, const UINT32 yyw_no )
{
#ifdef CO_PARAM_CHECK
	if( pipe_no >= D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "imR2yLatestAddrUpdate error. pipe_no>=D_IM_R2Y_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	//TODO 抽出
	im_r2y_update_latest_address(im_r2y_new(), pipe_no, yyw_no);
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
}

/* Is F_R2Y active
 */
static UCHAR imR2yIsActFr2y( UCHAR pipe_no )
{
	UCHAR t_r2y_enable;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

	if( pipe_no >= D_IM_R2Y_PIPE12 ){
		Ddim_Print(( "imR2yIsActFr2y:pipe_no err\n" ));
		return 0;
	}

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	t_r2y_enable = (gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CNTL.CNTL.bit.TRG != D_IM_R2Y_FR2YTRG_IDLE)?(D_IM_R2Y_ENABLE_ON):(D_IM_R2Y_ENABLE_OFF);
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );

	return t_r2y_enable;
}


/*
 * PUBLIC
 */
/* Restart R2Y process when yyw_continue_start_enable equal D_IM_R2Y_ENABLE_OFF.
 */
INT32 im_r2y_proc_constart(ImR2yProc *self,  UCHAR pipe_no )
{
	UCHAR loop_cnt, loop_sta, loop_end;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile T_IM_R2Y_STATE_MNG* gIM_R2Y_State = im_r2y_utils_get_state_mng(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_proc_constart error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_utils_get_loop_val(imR2yUtils, pipe_no, &loop_sta, &loop_end );

#ifdef CO_DEBUG_PRINT_IM_R2Y
	Ddim_Print(( "im_r2y_proc_constart on pclk\n" ));
#endif
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		if( gIM_R2Y_State[loop_cnt].was_started == D_IM_R2Y_FALSE ) {
			continue;
		}
		// P-clock control

		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYWTRG.bit.YYWTRG = D_IM_R2Y_YYWTRG_ON;

	}
#ifdef CO_DEBUG_PRINT_IM_R2Y
	Ddim_Print(( "im_r2y_proc_constart off pclk\n" ));
#endif
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
	Im_R2Y_Dsb();

	return D_DDIM_OK;
}

/* Start R2Y process.
 */
INT32 im_r2y_proc_start(ImR2yProc *self,  UCHAR pipe_no )
{
	DDIM_USER_ER		ercd;
	INT32				retcd;
	DDIM_USER_FLGPTN	flgptn = 0;
	UCHAR loop_cnt, loop_sta, loop_end;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile T_IM_R2Y_STATE_MNG* gIM_R2Y_State = im_r2y_utils_get_state_mng(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_proc_start error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_DEBUG_PRINT_IM_R2Y
	Ddim_Print(( "im_r2y_proc_start begin\n" ));
#endif

	// P-clock control
#ifdef CO_DEBUG_PRINT_IM_R2Y
	Ddim_Print(( "im_r2y_proc_start on pclk\n" ));
#endif
	im_r2y_utils_get_loop_val(imR2yUtils, pipe_no, &loop_sta, &loop_end );

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		if( im_r2y_yyr_is_activated(loop_cnt) ){
			Ddim_Print(( "im_r2y_proc_start error. YYR busy\n" ));
			return D_IM_R2Y_MACRO_BUSY;
		}
		if( im_r2y_yyw_is_activated(loop_cnt) ){
			Ddim_Print(( "im_r2y_proc_start error. YYW busy\n" ));
			return D_IM_R2Y_MACRO_BUSY;
		}
		if( imR2yIsActFr2y(loop_cnt) != D_IM_R2Y_ENABLE_OFF ){
			Ddim_Print(( "im_r2y_proc_start error. F_R2Y busy\n" ));
			return D_IM_R2Y_MACRO_BUSY;
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
		gIM_Io_R2y_Reg_Ptr[pipe_no]->R2Y_CMN.YYINTE.word = D_IM_R2Y_YYINTE_DISABLE;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->R2Y_CMN.YYINTF.word = D_IM_R2Y_YYINTF_ALL_CLR;

		gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CNTL.R2YINTE.word = D_IM_R2Y_R2YINTE_DISABLE;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CNTL.R2YINTF.word = D_IM_R2Y_R2YINTF_ALL_CLR;

#ifdef CO_DEBUG_PRINT_IM_R2Y
		Ddim_Print(( "im_r2y_proc_start enable interrupt\n" ));
#endif
		for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
			gIM_R2Y_State[loop_cnt].int_status = 0;

			// Set of All Interrupt enable
			if( gIM_R2Y_State[loop_cnt].yyw_enable[D_IM_R2Y_YYW_CH_0] == D_IM_R2Y_ENABLE_ON ) {
				gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.YYINTE.word |= D_IM_R2Y_YYINTE_YYW0_ENABLE;
			}
			if( gIM_R2Y_State[loop_cnt].yyw_enable[D_IM_R2Y_YYW_CH_1] == D_IM_R2Y_ENABLE_ON ) {
				gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.YYINTE.word |= D_IM_R2Y_YYINTE_YYW1_ENABLE;
			}
			if( gIM_R2Y_State[loop_cnt].yyw_enable[D_IM_R2Y_YYW_CH_2] == D_IM_R2Y_ENABLE_ON ) {
				gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.YYINTE.word |= D_IM_R2Y_YYINTE_YYW2_ENABLE;
			}
		}

		gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CNTL.R2YINTE.word = D_IM_R2Y_R2YINTE_ALL_ENABLE;


#ifdef CO_DEBUG_PRINT_IM_R2Y
		Ddim_Print(( "im_r2y_proc_start on clk\n" ));
#endif
		im_r2y_clk_on_iclk(im_r2y_clk_new(),  pipe_no );
		im_r2y_clk_on_clk(im_r2y_clk_new(),  pipe_no );

		// Set access enable
		for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
			// RGB Deknee
			if( gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYR.YYRCTL.bit.DKNEN != 0 ) {
				im_r2y3_set_rgb_deknee_access_enable(im_r2y3_new(),  loop_cnt, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_OFF );
			}

			// Tone control
			if(( gIM_Io_R2y_Reg_Ptr[loop_cnt]->F_R2Y.TC.TCCTL.bit.TCEN != 0 )
			|| ( gIM_Io_R2y_Reg_Ptr[loop_cnt]->F_R2Y.TC.TCCTL.bit.TCYBEN != 0 )) {
				im_r2y_set_tone_control_tbl_access_enable(im_r2y_ctrl_new(), loop_cnt, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_OFF );
			}

			// BTC Luminance evaluation
			if( gIM_Io_R2y_Reg_Ptr[loop_cnt]->F_R2Y.BTC.TCTCTL.bit.TCTEN != 0 ) {
				im_r2y_ctrl2_set_luminance_evaluation_tbl_access_enable(im_r2y_ctrl2_new(), loop_cnt, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_OFF );
			}

			// BTC histogram
			if( gIM_Io_R2y_Reg_Ptr[loop_cnt]->F_R2Y.BTC.TCHSCTL.bit.TCHSEN != 0 ) {
				im_r2y_ctrl2_set_btc_histogram_tbl_access_enable(im_r2y_ctrl2_new(), loop_cnt, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_OFF );
			}

			// Gamma
			if( gIM_Io_R2y_Reg_Ptr[loop_cnt]->F_R2Y.GAM.GMCTL.bit.GMEN != 0 ) {
				im_r2y_ctrl2_set_gamma_tbl_access_enable(im_r2y_ctrl2_new(),  loop_cnt, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_OFF );
				im_r2y_ctrl2_set_gamma_yb_tbl_access_enable(im_r2y_ctrl2_new(),  loop_cnt, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_OFF );
			}

			// High frequency EdgeEnhance
			if( gIM_Io_R2y_Reg_Ptr[loop_cnt]->F_R2Y.EGHW.EGHWCTL.bit.EGHWEN != 0 ) {
				im_r2y_edge_set_high_edge_scl_tbl_access_enable(im_r2y_edge_new(),  loop_cnt, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_OFF );
				if( gIM_Io_R2y_Reg_Ptr[loop_cnt]->F_R2Y.EGHW.EGHWCTL.bit.EGHWTC != 0 ) {
					im_r2y_edge_set_high_edge_step_tbl_access_enable(im_r2y_edge_new(),  loop_cnt, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_OFF );
				}
			}

			// Medium frequency EdgeEnhance
			if( gIM_Io_R2y_Reg_Ptr[loop_cnt]->F_R2Y.EGMW.EGMWCTL.bit.EGMWEN != 0 ) {
				im_r2y_edge_set_medium_edge_scl_tbl_access_enable(im_r2y_edge_new(),  loop_cnt, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_OFF );
				if( gIM_Io_R2y_Reg_Ptr[loop_cnt]->F_R2Y.EGMW.EGMWCTL.bit.EGMWTC != 0 ) {
					im_r2y_edge_set_medium_edge_step_tbl_access_enable(im_r2y_edge_new(),  loop_cnt, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_OFF );
				}
			}

			// Low frequency EdgeEnhance
			if( gIM_Io_R2y_Reg_Ptr[loop_cnt]->F_R2Y.EGLW.EGLWCTL.bit.EGLWEN != 0 ) {
				im_r2y_edge_set_low_edge_scl_tbl_access_enable(im_r2y_edge_new(),  loop_cnt, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_OFF );
				if( gIM_Io_R2y_Reg_Ptr[loop_cnt]->F_R2Y.EGLW.EGLWCTL.bit.EGLWTC != 0 ) {
					im_r2y_edge_set_low_edge_step_tbl_access_enable(im_r2y_edge_new(),  loop_cnt, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_OFF );
				}
			}

			// Map scale
			if((( gIM_Io_R2y_Reg_Ptr[loop_cnt]->F_R2Y.EGHW.EGHWCTL.bit.EGHWEN != 0 )
			 && ( gIM_Io_R2y_Reg_Ptr[loop_cnt]->F_R2Y.EGHW.EGHWCTL.bit.EGHWMP != 0 ))
			|| (( gIM_Io_R2y_Reg_Ptr[loop_cnt]->F_R2Y.EGMW.EGMWCTL.bit.EGMWEN != 0 )
			 && ( gIM_Io_R2y_Reg_Ptr[loop_cnt]->F_R2Y.EGMW.EGMWCTL.bit.EGMWMP != 0 ))
			|| (( gIM_Io_R2y_Reg_Ptr[loop_cnt]->F_R2Y.EGLW.EGLWCTL.bit.EGLWEN != 0 )
			 && ( gIM_Io_R2y_Reg_Ptr[loop_cnt]->F_R2Y.EGLW.EGLWCTL.bit.EGLWMP != 0 ))) {
				im_r2y_ctrl3_set_map_scl_tbl_access_enable(im_r2y_ctrl3_new(),  loop_cnt, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_OFF );
			}
		}

		// YYR Histogram
		im_r2y3_set_histogram_access_enable(im_r2y3_new(),  pipe_no, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_OFF );

		gIM_Io_R2y_Reg_Ptr[pipe_no]->R2Y_CMN.RAMAEN.bit.YYRAEN_YYR = 1;
		for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
			if( gIM_R2Y_State[loop_cnt].yyw_enable[D_IM_R2Y_YYW_CH_0] != 0 ){
				gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.RAMAEN.bit.YW0AEN_YYW0 = 1;
				if( gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYW0MD.bit.RSZ0MD == D_IM_R2Y_RSZ_BICUBIC ){
					gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.RAMAEN.bit.YW0AEN_YYW0_BICUBIC = 1;
				}
				if( gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.EE0CTL.bit.EE0EN != 0 ){
					gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.RAMAEN.bit.YW0AEN_YYW0_EDGE = 1;
				}
				if( gIM_R2Y_State[loop_cnt].output_mode_0a != D_IM_R2Y_YYW0A_OUTPUT_MODE_STOP ){
					gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.RAMAEN.bit.YW0AEN_YYW0A = 1;
				}
			}
			if( gIM_R2Y_State[loop_cnt].yyw_enable[D_IM_R2Y_YYW_CH_1] != 0 ){
				gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.RAMAEN.bit.YW1AEN_YYW1 = 1;
				if( gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYW1MD.bit.RSZ1MD == D_IM_R2Y_RSZ_BICUBIC ){
					gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.RAMAEN.bit.YW1AEN_YYW1_BICUBIC = 1;
				}
				if( gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.EE1CTL.bit.EE1EN != 0 ){
					gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.RAMAEN.bit.YW1AEN_YYW1_EDGE = 1;
				}
			}
			gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.RAMAEN.bit.YW2AEN = (gIM_R2Y_State[loop_cnt].yyw_enable[D_IM_R2Y_YYW_CH_2] != 0)?(1):(0);
		}

		gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CNTL.FLTAEN.bit.YCFAEN = 1;

		im_r2y_wait_usec( D_IM_R2Y_SRAM_WAIT_USEC );

#ifdef CO_DEBUG_PRINT_IM_R2Y
		Ddim_Print(( "im_r2y_proc_start clear event flag\n" ));
#endif

		if( im_r2y_check_target_pipe_no_1( pipe_no ) ){
			flgptn |= D_IM_R2Y1_INT_FLG_ALL;
		}
		if( im_r2y_check_target_pipe_no_2( pipe_no ) ){
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
			gIM_R2Y_State[loop_cnt].was_started = D_IM_R2Y_TRUE;
		}

#ifdef CO_DEBUG_PRINT_IM_R2Y
		Ddim_Print(( "im_r2y_proc_start check macro busy state\n" ));
#endif
#ifndef D_IM_R2Y_DEBUG_ON_PC
		Im_R2Y_Dsb();
		for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
			while( im_r2y_yyr_is_activated(loop_cnt) ) {
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
			if( gIM_R2Y_State[loop_cnt].yyw_enable[D_IM_R2Y_YYW_CH_0] == D_IM_R2Y_ENABLE_ON ) {
				gIM_R2Y_State[loop_cnt].busy_state |= D_IM_R2Y_STATE_BUSY_YYW0;
			}
			if( gIM_R2Y_State[loop_cnt].yyw_enable[D_IM_R2Y_YYW_CH_1] == D_IM_R2Y_ENABLE_ON ) {
				gIM_R2Y_State[loop_cnt].busy_state |= D_IM_R2Y_STATE_BUSY_YYW1;
			}
			if( gIM_R2Y_State[loop_cnt].yyw_enable[D_IM_R2Y_YYW_CH_2] == D_IM_R2Y_ENABLE_ON ) {
				gIM_R2Y_State[loop_cnt].busy_state |= D_IM_R2Y_STATE_BUSY_YYW2;
			}
		}
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYWTRG.bit.YYWTRG = D_IM_R2Y_YYWTRG_ON;

#ifdef CO_DEBUG_PRINT_IM_R2Y
		Ddim_Print(( "im_r2y_proc_start enable F_R2Y\n" ));
#endif
		for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
			gIM_R2Y_State[loop_cnt].busy_state |= D_IM_R2Y_STATE_BUSY_F_R2Y;
		}
		gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CNTL.CNTL.bit.TRG = D_IM_R2Y_FR2YTRG_ON;
#ifdef CO_DEBUG_ON_PC
		for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
			gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CNTL.CNTL.bit.TRG = D_IM_R2Y_FR2YTRG_BUSY;
		}
#endif

#ifdef CO_DEBUG_PRINT_IM_R2Y
		Ddim_Print(( "im_r2y_proc_start enable YYR\n" ));
#endif
		for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
			gIM_R2Y_State[loop_cnt].busy_state |= D_IM_R2Y_STATE_BUSY_YYR;
		}
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYR.YYRTRG.bit.YYRTRG = D_IM_R2Y_YYRTRG_ON;

		retcd = D_DDIM_OK;
		break;
	}

#ifdef CO_DEBUG_PRINT_IM_R2Y
	Ddim_Print(( "im_r2y_proc_start off pclk\n" ));
#endif
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );

#ifdef D_IM_R2Y_DEBUG_ON_PC
	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		if( gIM_R2Y_macro_fake_finish[loop_cnt] != 0 ) {
			gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.YYINTF.word = 0;
			gIM_Io_R2y_Reg_Ptr[loop_cnt]->F_R2Y.CNTL.R2YINTF.word = 0;
			gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.YYINTF.bit.__YYREF = 1;
			if( gIM_R2Y_State[loop_cnt].yyw_enable[D_IM_R2Y_YYW_CH_0] == D_IM_R2Y_ENABLE_ON ) {
				gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.YYINTF.bit.__YYW0EF = 1;
				if( gIM_R2Y_State[loop_cnt].output_mode_0a != D_IM_R2Y_YYW0A_OUTPUT_MODE_STOP ){
					gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.YYINTF.bit.__YYWAEF = 1;
				}
				if( (gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.LINTLV.bit.LINTLV_0 != 0)
				 && (gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.LINTSEL.bit.LINTS_0 == 0) ) {
					gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.YYINTF.bit.__LINT0F = 1;
				}
				if( (gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.LINTLV.bit.LINTLV_1 != 0)
				 && (gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.LINTSEL.bit.LINTS_1 == 0) ) {
					gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.YYINTF.bit.__LINT1F = 1;
				}
				if( (gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.LINTLV.bit.LINTLV_2 != 0)
				 && (gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.LINTSEL.bit.LINTS_2 == 0) ) {
					gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.YYINTF.bit.__LINT2F = 1;
				}
			}
			if( gIM_R2Y_State[loop_cnt].yyw_enable[D_IM_R2Y_YYW_CH_1] == D_IM_R2Y_ENABLE_ON ) {
				gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.YYINTF.bit.__YYW1EF = 1;
				if( (gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.LINTLV.bit.LINTLV_0 != 0)
				 && (gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.LINTSEL.bit.LINTS_0 == 1) ) {
					gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.YYINTF.bit.__LINT0F = 1;
				}
				if( (gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.LINTLV.bit.LINTLV_1 != 0)
				 && (gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.LINTSEL.bit.LINTS_1 == 1) ) {
					gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.YYINTF.bit.__LINT1F = 1;
				}
				if( (gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.LINTLV.bit.LINTLV_2 != 0)
				 && (gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.LINTSEL.bit.LINTS_2 == 1) ) {
					gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.YYINTF.bit.__LINT2F = 1;
				}
			}
			if( gIM_R2Y_State[loop_cnt].yyw_enable[D_IM_R2Y_YYW_CH_2] == D_IM_R2Y_ENABLE_ON ) {
				gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.YYINTF.bit.__YYW2EF = 1;
			}
			gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.YYINTF.bit.__YYWEF = 1;
			if( gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANKST != 0 ) {
				gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANKST = 0;
				gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK0STS = gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK0PS;
				gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANKASTS = gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANKAPS;
				gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK1STS = gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK1PS;
				gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK2STS = gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK2PS;
			}
			im_r2y_proc_int_handler(im_r2y_proc_new(),  loop_cnt );
			gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.YYINTF.word = 0;
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
INT32 im_r2y_proc_stop(ImR2yProc *self,  UCHAR pipe_no )
{
	UCHAR loop_cnt, loop_sta, loop_end;
	UCHAR byp_bak[2], pad_bak[2], ext_b_bak[2], ext_c_bak[2];
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile T_IM_R2Y_STATE_MNG* gIM_R2Y_State = im_r2y_utils_get_state_mng(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_proc_stop error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_utils_get_loop_val(imR2yUtils, pipe_no, &loop_sta, &loop_end );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		gIM_R2Y_State[loop_cnt].was_started = D_IM_R2Y_FALSE;
	}

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	im_r2y_clk_on_iclk(im_r2y_clk_new(),  pipe_no );
	im_r2y_clk_on_clk(im_r2y_clk_new(),  pipe_no );	// D_IM_R2Y_FR2YTRG_OFF control accompanies the R2Y reset.

	for( loop_cnt = 0; loop_cnt <= 1; loop_cnt++ ){
		byp_bak[loop_cnt] = gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.R2YMODE.bit.YCFBYP;
		pad_bak[loop_cnt] = gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.R2YMODE.bit.YCFPDD;
		ext_b_bak[loop_cnt] = gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYW0MD.bit.EXTBEN;
		ext_c_bak[loop_cnt] = gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYW0MD.bit.EXTCEN;
	}

	//
	// Stop YYW
	//
	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		gIM_R2Y_State[loop_cnt].busy_state &= ~(D_IM_R2Y_STATE_BUSY_YYW0 | D_IM_R2Y_STATE_BUSY_YYW1 | D_IM_R2Y_STATE_BUSY_YYW2);
	}
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYWTRG.bit.YYWTRG = D_IM_R2Y_YYWTRG_OFF;

	Im_R2Y_Dsb();

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		while( im_r2y_yyw_is_activated(loop_cnt) ){
#ifdef CO_DEBUG_ON_PC
//			Ddim_Print(( "im_r2y_proc_stop YYW wait loop. %u\n", gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWTRG.bit.YYWTRG ));
			gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWTRG.bit.YYWTRG = D_IM_R2Y_YYWTRG_IDLE;
#endif
			;	// DO NOTHING
		}
	}

	//
	// Stop F_R2Y
	//
	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		gIM_R2Y_State[loop_cnt].busy_state &= ~(D_IM_R2Y_STATE_BUSY_F_R2Y);
	}
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CNTL.CNTL.bit.TRG = D_IM_R2Y_FR2YTRG_OFF;
#ifdef CO_DEBUG_ON_PC
	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		gIM_Io_R2y_Reg_Ptr[loop_cnt]->F_R2Y.CNTL.CNTL.bit.TRG = D_IM_R2Y_FR2YTRG_IDLE;
	}
#endif

	//
	// Stop YYR
	//
	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		gIM_R2Y_State[loop_cnt].busy_state &= ~(D_IM_R2Y_STATE_BUSY_YYR);
	}
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYR.YYRTRG.bit.YYRTRG = D_IM_R2Y_YYRTRG_OFF;

	Im_R2Y_Dsb();

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		while( im_r2y_yyr_is_activated(loop_cnt) ) {
#ifdef CO_DEBUG_ON_PC
//			Ddim_Print(( "im_r2y_proc_stop YYR wait loop. %u\n", gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYR.YYRTRG.bit.YYRTRG ));
			gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYR.YYRTRG.bit.YYRTRG = D_IM_R2Y_YYRTRG_IDLE;
#endif
			;	// DO NOTHING
		}
	}

	gIM_Io_R2y_Reg_Ptr[pipe_no]->R2Y_CMN.R2YMODE.bit.YCFBYP  = D_IM_R2Y_ENABLE_OFF;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->R2Y_CMN.R2YMODE.bit.YCFPDD  = D_IM_R2Y_ENABLE_OFF;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0MD.bit.EXTBEN = D_IM_R2Y_ENABLE_OFF;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0MD.bit.EXTCEN = D_IM_R2Y_ENABLE_OFF;

	im_r2y_wait_usec( 10 );
	Im_R2Y_Dsb();

	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYR.YYRTRG.bit.YYRTRG = D_IM_R2Y_YYRTRG_ON;

	im_r2y_wait_usec( 10 );
	Im_R2Y_Dsb();

	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYR.YYRTRG.bit.YYRTRG = D_IM_R2Y_YYRTRG_OFF;

	Im_R2Y_Dsb();

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		while( im_r2y_yyr_is_activated(loop_cnt) ) {
#ifdef CO_DEBUG_ON_PC
//			Ddim_Print(( "im_r2y_proc_stop YYR wait loop. %u\n", gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYR.YYRTRG.bit.YYRTRG ));
			gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYR.YYRTRG.bit.YYRTRG = D_IM_R2Y_YYRTRG_IDLE;
#endif
			;	// DO NOTHING
		}
	}

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.R2YMODE.bit.YCFBYP = byp_bak[loop_cnt];
		gIM_Io_R2y_Reg_Ptr[loop_cnt]->R2Y_CMN.R2YMODE.bit.YCFPDD = pad_bak[loop_cnt];
		gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYW0MD.bit.EXTBEN = ext_b_bak[loop_cnt];
		gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYW0MD.bit.EXTCEN = ext_c_bak[loop_cnt];
	}

	// Clear of All Interrupt disable
	gIM_Io_R2y_Reg_Ptr[pipe_no]->R2Y_CMN.YYINTE.word = D_IM_R2Y_YYINTE_DISABLE;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->R2Y_CMN.YYINTF.word = D_IM_R2Y_YYINTF_ALL_CLR;

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CNTL.R2YINTE.word = D_IM_R2Y_R2YINTE_DISABLE;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CNTL.R2YINTF.word = D_IM_R2Y_R2YINTF_ALL_CLR;

	// RGB Deknee
	im_r2y3_set_rgb_deknee_access_enable(im_r2y3_new(),  pipe_no, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_OFF );

	// Tone control
	im_r2y_set_tone_control_tbl_access_enable(im_r2y_ctrl_new(), pipe_no, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_OFF );

	// BTC Luminance evaluation
	im_r2y_ctrl2_set_luminance_evaluation_tbl_access_enable(im_r2y_ctrl2_new(), pipe_no, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_OFF );

	// BTC histogram
	im_r2y_ctrl2_set_btc_histogram_tbl_access_enable(im_r2y_ctrl2_new(), pipe_no, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_OFF );

	// Gamma
	im_r2y_ctrl2_set_gamma_tbl_access_enable(im_r2y_ctrl2_new(),  pipe_no, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_OFF );
	im_r2y_ctrl2_set_gamma_yb_tbl_access_enable(im_r2y_ctrl2_new(),  pipe_no, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_OFF );

	// High frequency EdgeEnhance
	im_r2y_edge_set_high_edge_scl_tbl_access_enable(im_r2y_edge_new(),  pipe_no, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_OFF );
	im_r2y_edge_set_high_edge_step_tbl_access_enable(im_r2y_edge_new(),  pipe_no, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_OFF );

	// Medium frequency EdgeEnhance
	im_r2y_edge_set_medium_edge_scl_tbl_access_enable(im_r2y_edge_new(),  pipe_no, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_OFF );
	im_r2y_edge_set_medium_edge_step_tbl_access_enable(im_r2y_edge_new(),  pipe_no, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_OFF );

	// Low frequency EdgeEnhance
	im_r2y_edge_set_low_edge_scl_tbl_access_enable(im_r2y_edge_new(),  pipe_no, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_OFF );
	im_r2y_edge_set_low_edge_step_tbl_access_enable(im_r2y_edge_new(),  pipe_no, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_OFF );

	// Map scale
	im_r2y_ctrl3_set_map_scl_tbl_access_enable(im_r2y_ctrl3_new(),  pipe_no, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_OFF );

	// YYR Histogram
	im_r2y3_set_histogram_access_enable(im_r2y3_new(),  pipe_no, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_OFF );

	gIM_Io_R2y_Reg_Ptr[pipe_no]->R2Y_CMN.RAMAEN.bit.YYRAEN_YYR          = 0;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->R2Y_CMN.RAMAEN.bit.YW0AEN_YYW0         = 0;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->R2Y_CMN.RAMAEN.bit.YW0AEN_YYW0_BICUBIC = 0;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->R2Y_CMN.RAMAEN.bit.YW0AEN_YYW0_EDGE    = 0;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->R2Y_CMN.RAMAEN.bit.YW0AEN_YYW0A        = 0;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->R2Y_CMN.RAMAEN.bit.YW1AEN_YYW1         = 0;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->R2Y_CMN.RAMAEN.bit.YW1AEN_YYW1_BICUBIC = 0;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->R2Y_CMN.RAMAEN.bit.YW1AEN_YYW1_EDGE    = 0;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->R2Y_CMN.RAMAEN.bit.YW2AEN              = 0;

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CNTL.FLTAEN.bit.YCFAEN = 0;

	im_r2y_clk_force_off_clk(im_r2y_clk_new(), pipe_no );
	im_r2y_clk_force_off_iclk(im_r2y_clk_new(),  pipe_no );
	im_r2y_clk_force_off_pclk(im_r2y_clk_new(),  pipe_no );

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
		return D_IM_R2Y_PARAM_ERROR;
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
			return D_IM_R2Y_PARAM_ERROR;
	}
}

/* R2Y Interrupt Handler
 */
VOID im_r2y_proc_int_handler(ImR2yProc *self,  UCHAR pipe_no )
{
	UINT32			loopcnt;
	DDIM_USER_ER	ercd;
	ULONG			r2y_inte;
	ULONG			r2y_intf;
	ULONG			r2y_intf_clr;
	ULONG			f_r2y_inte;
	ULONG			f_r2y_intf;
	ULONG			f_r2y_intf_clr;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile T_IM_R2Y_STATE_MNG* gIM_R2Y_State = im_r2y_utils_get_state_mng(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( pipe_no >= D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_proc_int_handler error. pipe_no>=D_IM_R2Y_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_DEBUG_PRINT_IM_R2Y
	Ddim_Print(( "im_r2y_proc_int_handler begin\n" ));
#endif

#ifdef CO_DEBUG_PRINT_IM_R2Y
	Ddim_Print(( "im_r2y_proc_int_handler on pclk\n" ));
#endif
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );


	if( gIM_R2Y_State[pipe_no].video_photo_mode == D_IM_R2Y_MODE_SDRAM_INPUT ) {
		if( !(im_r2y_yyr_is_activated(pipe_no) || im_r2y_yyw_is_activated(pipe_no) || (gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYWCTL.bit.YYWCSE != 0)) ) {
#ifdef CO_DEBUG_PRINT_IM_R2Y
			Ddim_Print(( "im_r2y_proc_int_handler off clk\n" ));
#endif
			im_r2y_clk_off_clk(im_r2y_clk_new(),  pipe_no );
			im_r2y_clk_off_iclk(im_r2y_clk_new(),  pipe_no );
		}
	}
	Im_R2Y_Dsb();

	r2y_inte = gIM_Io_R2y_Reg_Ptr[pipe_no]->R2Y_CMN.YYINTE.word;
	r2y_intf = gIM_Io_R2y_Reg_Ptr[pipe_no]->R2Y_CMN.YYINTF.word;
	r2y_intf_clr = 0;
	f_r2y_inte = gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CNTL.R2YINTE.word;
	f_r2y_intf = gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CNTL.R2YINTF.word;
	f_r2y_intf_clr = 0;

#ifdef CO_DEBUG_PRINT_IM_R2Y
	Ddim_Print(( "im_r2y_proc_int_handler inte=0x%lx, intf=0x%lx f_inte=0x%lx f_intf=0x%lx\n", r2y_inte, r2y_intf, f_r2y_inte, f_r2y_intf ));
#endif

	// Call of Callback API for interrupt status

	for( loopcnt = 0; loopcnt < (sizeof(gim_r2y_inttbl_jdsr2y[0]) / sizeof(gim_r2y_inttbl_jdsr2y[0][0])); loopcnt++ ) {
		if( ((r2y_intf & gim_r2y_inttbl_jdsr2y[pipe_no][loopcnt].flg_bitmask) != 0)
		 && ((r2y_inte & gim_r2y_inttbl_jdsr2y[pipe_no][loopcnt].ena_bitmask) != 0) ) {

#ifdef CO_DEBUG_PRINT_IM_R2Y
			Ddim_Print(( "im_r2y_proc_int_handler begin JDSR2Y 0x%x\n", gim_r2y_inttbl_jdsr2y[pipe_no][loopcnt].flg_bitmask ));
#endif

			if(( gim_r2y_inttbl_jdsr2y[pipe_no][loopcnt].int_status == D_IM_R2Y1_INT_STATE_YYW0_END )
			|| ( gim_r2y_inttbl_jdsr2y[pipe_no][loopcnt].int_status == D_IM_R2Y2_INT_STATE_YYW0_END )) {
				imR2yLatestAddrUpdate( pipe_no, D_IM_R2Y_YYW_CH_0 );
			}
			else
			if(( gim_r2y_inttbl_jdsr2y[pipe_no][loopcnt].int_status == D_IM_R2Y1_INT_STATE_YYW1_END )
			|| ( gim_r2y_inttbl_jdsr2y[pipe_no][loopcnt].int_status == D_IM_R2Y2_INT_STATE_YYW1_END )) {
				imR2yLatestAddrUpdate( pipe_no, D_IM_R2Y_YYW_CH_1 );
			}
			else
			if(( gim_r2y_inttbl_jdsr2y[pipe_no][loopcnt].int_status == D_IM_R2Y1_INT_STATE_YYW2_END )
			|| ( gim_r2y_inttbl_jdsr2y[pipe_no][loopcnt].int_status == D_IM_R2Y2_INT_STATE_YYW2_END )) {
				imR2yLatestAddrUpdate( pipe_no, D_IM_R2Y_YYW_CH_2 );
			}
			else
			if(( gim_r2y_inttbl_jdsr2y[pipe_no][loopcnt].int_status == D_IM_R2Y1_INT_STATE_YYW0A_END )
			|| ( gim_r2y_inttbl_jdsr2y[pipe_no][loopcnt].int_status == D_IM_R2Y2_INT_STATE_YYW0A_END )) {
				imR2yLatestAddrUpdate( pipe_no, D_IM_R2Y_YYW_CH_0A );
			}

			gIM_R2Y_State[pipe_no].int_status = gim_r2y_inttbl_jdsr2y[pipe_no][loopcnt].int_status;
			gIM_R2Y_State[pipe_no].busy_state &= ~(gim_r2y_inttbl_jdsr2y[pipe_no][loopcnt].busy_state);

			r2y_intf_clr |= gim_r2y_inttbl_jdsr2y[pipe_no][loopcnt].flg_bitmask;

			ercd = DDIM_User_Set_Flg( FID_IM_R2Y, gim_r2y_inttbl_jdsr2y[pipe_no][loopcnt].waitflg );
			if( ercd != D_DDIM_USER_E_OK ) {
				Ddim_Print(( "im_r2y_proc_int_handler: invalid FID. 0x%lx\n", gim_r2y_inttbl_jdsr2y[pipe_no][loopcnt].waitflg ));
			}

			if (gIM_R2Y_State[pipe_no].r2y_user_handler) {
				gIM_R2Y_State[pipe_no].r2y_user_handler( (UINT32*)&gIM_R2Y_State[pipe_no].int_status, gIM_R2Y_State[pipe_no].user_param );
			}
		}
	}

	for( loopcnt = 0; loopcnt < (sizeof(gim_r2y_inttbl_fr2y[0]) / sizeof(gim_r2y_inttbl_fr2y[0][0])); loopcnt++ ) {
		if( ((f_r2y_intf & gim_r2y_inttbl_fr2y[pipe_no][loopcnt].flg_bitmask) != 0)
		 && ((f_r2y_inte & gim_r2y_inttbl_fr2y[pipe_no][loopcnt].ena_bitmask) != 0) ) {

#ifdef CO_DEBUG_PRINT_IM_R2Y
			Ddim_Print(( "im_r2y_proc_int_handler begin FR2Y 0x%x\n", gim_r2y_inttbl_fr2y[pipe_no][loopcnt].flg_bitmask ));
#endif

			gIM_R2Y_State[pipe_no].int_status = gim_r2y_inttbl_fr2y[pipe_no][loopcnt].int_status;
			gIM_R2Y_State[pipe_no].busy_state &= ~(gim_r2y_inttbl_fr2y[pipe_no][loopcnt].busy_state);

			f_r2y_intf_clr |= gim_r2y_inttbl_fr2y[pipe_no][loopcnt].flg_bitmask;

			ercd = DDIM_User_Set_Flg( FID_IM_R2Y, gim_r2y_inttbl_fr2y[pipe_no][loopcnt].waitflg );
			if( ercd != D_DDIM_USER_E_OK ) {
				Ddim_Print(( "im_r2y_proc_int_handler: invalid FID. 0x%lx\n", gim_r2y_inttbl_fr2y[pipe_no][loopcnt].waitflg ));
			}

			if (gIM_R2Y_State[pipe_no].r2y_user_handler) {
				gIM_R2Y_State[pipe_no].r2y_user_handler( (UINT32*)&gIM_R2Y_State[pipe_no].int_status, gIM_R2Y_State[pipe_no].user_param );
			}
		}
	}

	// Clear interrupt
	gIM_Io_R2y_Reg_Ptr[pipe_no]->R2Y_CMN.YYINTF.word = r2y_intf_clr;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CNTL.R2YINTF.word = f_r2y_intf_clr;


#ifdef CO_DEBUG_PRINT_IM_R2Y
	Ddim_Print(( "im_r2y_proc_int_handler intf=0x%lx, %0xlx\n", gIM_Io_R2y_Reg_Ptr[pipe_no]->R2Y_CMN.YYINTF.word, gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CNTL.R2YINTF.word ));
#endif

#ifdef CO_DEBUG_PRINT_IM_R2Y
	Ddim_Print(( "im_r2y_proc_int_handler off pclk\n" ));
#endif
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
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
