/*
 * imr2y.c
 *
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
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

#include "imr2y.h"
#include "imr2y3.h"
#include "imr2yutils.h"
#include "imr2yproc.h"
#include "dd_arm.h"
#include "imr2ystat.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImR2y, im_r2y);
#define IM_R2Y_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImR2yPrivate, IM_TYPE_R2Y))

/* debug print switch  for im_r2y.c developping/debugging person.
 * (not im_r2y user)
 */
//#define IM_R2Y_DEBUG_PRINT
//#define IM_R2Y_STATUS_PRINT

#define D_IM_R2Y_FR2YTRG_IDLE			(2)

struct _ImR2yPrivate
{
	int a;
};

typedef struct {
	T_IM_R2Y_OUTBANK_INFO	bank_info;		// Output bank information
	UCHAR					latest_idx;		// Latest Output bank index.
	T_IM_R2Y_OUTADDR_INFO	latest_addr;	// Latest Output address.
} T_IM_R2Y_OUTPUT_MNG;



// Output parameter
static volatile T_IM_R2Y_OUTPUT_MNG gIM_R2Y_Out_Mng[D_IM_R2Y_PIPE_COUNT][D_IM_R2Y_YYW_CH_MAX];


/*
 * DECLS
 */
static VOID imR2yReset( UCHAR pipe_no );
static VOID imR2ySetYyrAddressSdramInput( UCHAR pipe_no );
static VOID imR2yManagerInit( UCHAR pipe_no );
static VOID imR2yCalcRingPixs( UCHAR pipe_no );


/*
 * IMPL
 */
static void im_r2y_constructor(ImR2y *self)
{
	ImR2yPrivate *priv = IM_R2Y_GET_PRIVATE(self);
}

static void im_r2y_destructor(ImR2y *self)
{
	ImR2yPrivate *priv = IM_R2Y_GET_PRIVATE(self);
}

/* R2Y reset sequence
 */
static VOID imR2yReset( UCHAR pipe_no )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "imR2yReset error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	im_r2y_clk_on_hclk(im_r2y_clk_new(),  pipe_no );
	im_r2y_clk_on_iclk(im_r2y_clk_new(),  pipe_no );
	im_r2y_clk_on_clk(im_r2y_clk_new(),  pipe_no );	// TRG off control accompanies the R2Y reset
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CNTL.CNTL.word = 0x0000;
	im_r2y_clk_off_clk(im_r2y_clk_new(),  pipe_no );
	im_r2y_clk_off_iclk(im_r2y_clk_new(),  pipe_no );
	im_r2y_clk_off_hclk(im_r2y_clk_new(),  pipe_no );
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
}

/* Calculate YYRA address after trimming.
 */
static VOID imR2ySetYyrAddressSdramInput( UCHAR pipe_no )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile T_IM_R2Y_STATE_MNG* gIM_R2Y_State = im_r2y_utils_get_state_mng(imR2yUtils);
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile T_IM_R2Y_YYRA_OFS_INFO* gIM_R2Y_yyra_ofs_info = im_r2y_utils_get_yyra_ofs_info(imR2yUtils);

	#ifdef CO_PARAM_CHECK
	if( pipe_no >= D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "imR2ySetYyrAddressSdramInput error. pipe_no>=D_IM_R2Y_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );

	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYR.YYRA.bit.YYRA_0 = (gIM_R2Y_State[pipe_no].in_addr[D_IM_R2Y_PORT_0] + gIM_R2Y_yyra_ofs_info[pipe_no].ofs_bytes);
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYR.YYRA.bit.YYRA_1 = (gIM_R2Y_State[pipe_no].in_addr[D_IM_R2Y_PORT_1] + gIM_R2Y_yyra_ofs_info[pipe_no].ofs_bytes);
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYR.YYRA.bit.YYRA_2 = (gIM_R2Y_State[pipe_no].in_addr[D_IM_R2Y_PORT_2] + gIM_R2Y_yyra_ofs_info[pipe_no].ofs_bytes);

	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
}

/* Reset internal value
 */
static VOID imR2yManagerInit( UCHAR pipe_no )
{
	UCHAR size_coef = 1;

#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "imR2yManagerInit error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

	if( pipe_no == D_IM_R2Y_PIPE12 ){
		size_coef = 2;
		pipe_no = 0;
	}

	im_r2y_stat_init(im_r2y_stat_new(), pipe_no, size_coef);

	// Initialize of Address management information
	memset( (USHORT*)&gIM_R2Y_Out_Mng[pipe_no], 0, sizeof(T_IM_R2Y_OUTPUT_MNG) * D_IM_R2Y_YYW_CH_MAX * size_coef );

	// Initialize of PCLK/HCLK/CLK control information
	//TODO imr2yclk.c
	im_r2y_clk_manager_init(im_r2y_clk_new(), pipe_no, size_coef);

	return;
}

/* Calculate padding pixs and referenced pixs with filter mode
 */
static VOID imR2yCalcRingPixs( UCHAR pipe_no )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile T_IM_R2Y_STATE_MNG* gIM_R2Y_State = im_r2y_utils_get_state_mng(imR2yUtils);
	static const T_IM_R2Y_RING_PIXS ring_pixs_info_tbl[2][2] = {	// YCFBYP, YCFPDD
		{	// YCFBYP=0
			{ D_IM_R2Y_ENABLE_OFF, 3, 0, 6 },	// YCFBYP=0, YCFPDD=0
			{ D_IM_R2Y_ENABLE_ON,  3, 6, 0 },	// YCFBYP=0, YCFPDD=1
		},
		{	// YCFBYP=1
			{ D_IM_R2Y_ENABLE_OFF, 0, 0, 0 },	// YCFBYP=1, YCFPDD=0
			{ D_IM_R2Y_ENABLE_ON,  0, 0, 0 },	// YCFBYP=1, YCFPDD=1	NG Setting
		}
	};

	UCHAR loop_cnt, loop_sta, loop_end;

#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "imR2yCalcRingPixs error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_utils_get_loop_val(imR2yUtils, pipe_no, &loop_sta, &loop_end );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		// Get current ring pixel information
		gIM_R2Y_State[loop_cnt].ring_pixs_info = ring_pixs_info_tbl[gIM_R2Y_State[loop_cnt].ycf_bypass][gIM_R2Y_State[loop_cnt].ycf_padding];

#ifdef IM_R2Y_DEBUG_PRINT
		Ddim_Print(( "imR2yCalcRingPixs(): en=%u ring=%u pad=%u ref=%u\n",
					 gIM_R2Y_State[loop_cnt].ring_pixs_info.pad_enable,
					 gIM_R2Y_State[loop_cnt].ring_pixs_info.ring_pixs,
					 gIM_R2Y_State[loop_cnt].ring_pixs_info.pad_pixs,
					 gIM_R2Y_State[loop_cnt].ring_pixs_info.ref_pixs ));
#endif
	}
}


/*
 * PUBLIC
 */
void im_r2y_update_latest_address(ImR2y *self,UCHAR pipe_no, const UINT32 yyw_no)
{
		ImR2yUtils* imR2yUtils = im_r2y_utils_get();
		volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

		switch( yyw_no ){
		case D_IM_R2Y_YYW_CH_1:
			gIM_R2Y_Out_Mng[pipe_no][yyw_no].latest_idx = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYWBANK.bit.BANK1STS;
			break;
		case D_IM_R2Y_YYW_CH_2:
			gIM_R2Y_Out_Mng[pipe_no][yyw_no].latest_idx = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYWBANK.bit.BANK2STS;
			break;
		case D_IM_R2Y_YYW_CH_0A:
			gIM_R2Y_Out_Mng[pipe_no][yyw_no].latest_idx = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYWBANK.bit.BANKASTS;
			break;
//		case D_IM_R2Y_YYW_CH_0:
		default:
			gIM_R2Y_Out_Mng[pipe_no][yyw_no].latest_idx = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYWBANK.bit.BANK0STS;
			break;
	}
	gIM_R2Y_Out_Mng[pipe_no][yyw_no].latest_addr = gIM_R2Y_Out_Mng[pipe_no][yyw_no].bank_info.output_addr[ gIM_R2Y_Out_Mng[pipe_no][yyw_no].latest_idx ];

}

void im_r2y_get_next_r2y_addr(ImR2y *self, UCHAR pipe_no,
 const UINT32 yyw_no, T_IM_R2Y_OUTADDR_INFO* const r2y_addr)
{
	*r2y_addr = gIM_R2Y_Out_Mng[pipe_no][yyw_no].bank_info.output_addr[ (gIM_R2Y_Out_Mng[pipe_no][yyw_no].latest_idx + 2)
	                                                                    % (gIM_R2Y_Out_Mng[pipe_no][yyw_no].bank_info.use_bank_num + 1)];
}

void im_r2y_get_latest_addr(ImR2y *self, UCHAR pipe_no, UINT32 yyw_no,
 UCHAR* const latest_bank_idx, T_IM_R2Y_OUTADDR_INFO* const latest_addr)
{
	*latest_bank_idx = gIM_R2Y_Out_Mng[pipe_no][yyw_no].latest_idx;
	*latest_addr     = gIM_R2Y_Out_Mng[pipe_no][yyw_no].latest_addr;
}

void im_r2y_ddim_print(ImR2y *self,UINT32 loopcnt, UINT32 loopcnt2, UINT32 loopcnt3)
{
		Ddim_Print(( "\t\tlatest_idx = %u\n", gIM_R2Y_Out_Mng[loopcnt3][loopcnt2].latest_idx ));
		Ddim_Print(( "\t\tbank_initial_position = %u\n", gIM_R2Y_Out_Mng[loopcnt3][loopcnt2].bank_info.bank_initial_position ));
		Ddim_Print(( "\t\tuse_bank_num = %u\n", gIM_R2Y_Out_Mng[loopcnt3][loopcnt2].bank_info.use_bank_num ));
		for( loopcnt = 0; loopcnt < D_IM_R2Y_YYW_BANK_MAX; loopcnt++ ) {
			Ddim_Print(( "\t\tBankNum = %u\n", loopcnt ));
			Ddim_Print(( "\t\t\tout_addr[Y]  = 0x%x\n", (UINT32)gIM_R2Y_Out_Mng[loopcnt3][loopcnt2].bank_info.output_addr[loopcnt].ycc.addr_Y ));
			Ddim_Print(( "\t\t\tout_addr[Cb] = 0x%x\n", (UINT32)gIM_R2Y_Out_Mng[loopcnt3][loopcnt2].bank_info.output_addr[loopcnt].ycc.addr_Cb ));
			Ddim_Print(( "\t\t\tout_addr[Cr] = 0x%x\n", (UINT32)gIM_R2Y_Out_Mng[loopcnt3][loopcnt2].bank_info.output_addr[loopcnt].ycc.addr_Cr ));
		}
}

/* R2Y Initialize
 */
INT32 Im_r2y_init(ImR2y *self, UCHAR pipe_no )
{
	UCHAR loop_cnt, loop_sta, loop_end;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile T_IM_R2Y_STATE_MNG* gIM_R2Y_State = im_r2y_utils_get_state_mng(imR2yUtils);
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "Im_r2y_init error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	imR2yReset( pipe_no );
	Im_R2Y_Dsb();

	// Initalize of Managemnet information & Reset of Internal buffer
	imR2yManagerInit( pipe_no );

	imR2yCalcRingPixs( pipe_no );

	im_r2y_utils_get_loop_val(imR2yUtils, pipe_no, &loop_sta, &loop_end );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		gIM_R2Y_State[loop_cnt].top_offset[D_IM_R2Y_PORT_0] = 0;
		gIM_R2Y_State[loop_cnt].top_offset[D_IM_R2Y_PORT_1] = 0;
		gIM_R2Y_State[loop_cnt].top_offset[D_IM_R2Y_PORT_2] = 0;
		gIM_R2Y_State[loop_cnt].was_started = D_IM_R2Y_FALSE;
	}

#ifdef CO_DEBUG_ON_PC
	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		gIM_Io_R2y_Reg_Ptr[loop_cnt]->F_R2Y.CNTL.CNTL.bit.TRG = D_IM_R2Y_FR2YTRG_IDLE;
		gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYR.YYRTRG.bit.YYRTRG   = D_IM_R2Y_YYRTRG_IDLE;
		gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWTRG.bit.YYWTRG   = D_IM_R2Y_YYWTRG_IDLE;
	}
#endif

	return D_DDIM_OK;
}

/* set AXI bus I/F Control
 */
INT32 im_r2y_ctrl_axi(ImR2y *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_AXI* const r2y_ctrl_axi )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);
#ifdef CO_PARAM_CHECK
	if( r2y_ctrl_axi == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("im_r2y_ctrl_axi error. r2y_ctrl_axi = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl_axi error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );

	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYRAXCTL.bit.YYRCACHE_0 = r2y_ctrl_axi->yyr[D_IM_R2Y_PORT_0].cache_type;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYRAXCTL.bit.YYRPROT_0  = r2y_ctrl_axi->yyr[D_IM_R2Y_PORT_0].protect_type;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYRAXCTL.bit.YYRCACHE_1 = r2y_ctrl_axi->yyr[D_IM_R2Y_PORT_1].cache_type;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYRAXCTL.bit.YYRPROT_1  = r2y_ctrl_axi->yyr[D_IM_R2Y_PORT_1].protect_type;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYRAXCTL.bit.YYRCACHE_2 = r2y_ctrl_axi->yyr[D_IM_R2Y_PORT_2].cache_type;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYRAXCTL.bit.YYRPROT_2  = r2y_ctrl_axi->yyr[D_IM_R2Y_PORT_2].protect_type;

	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW0AXCTL.bit.YYW0CACHE_0 = r2y_ctrl_axi->yyw[D_IM_R2Y_YYW_CH_0][D_IM_R2Y_PORT_0].cache_type;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW0AXCTL.bit.YYW0PROT_0  = r2y_ctrl_axi->yyw[D_IM_R2Y_YYW_CH_0][D_IM_R2Y_PORT_0].protect_type;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW0AXCTL.bit.YYW0CACHE_1 = r2y_ctrl_axi->yyw[D_IM_R2Y_YYW_CH_0][D_IM_R2Y_PORT_1].cache_type;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW0AXCTL.bit.YYW0PROT_1  = r2y_ctrl_axi->yyw[D_IM_R2Y_YYW_CH_0][D_IM_R2Y_PORT_1].protect_type;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW0AXCTL.bit.YYW0CACHE_2 = r2y_ctrl_axi->yyw[D_IM_R2Y_YYW_CH_0][D_IM_R2Y_PORT_2].cache_type;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW0AXCTL.bit.YYW0PROT_2  = r2y_ctrl_axi->yyw[D_IM_R2Y_YYW_CH_0][D_IM_R2Y_PORT_2].protect_type;

	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYWAAXCTL.bit.YYWACACHE_0 = r2y_ctrl_axi->yyw[D_IM_R2Y_YYW_CH_0A][D_IM_R2Y_PORT_0].cache_type;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYWAAXCTL.bit.YYWAPROT_0  = r2y_ctrl_axi->yyw[D_IM_R2Y_YYW_CH_0A][D_IM_R2Y_PORT_0].protect_type;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYWAAXCTL.bit.YYWACACHE_1 = r2y_ctrl_axi->yyw[D_IM_R2Y_YYW_CH_0A][D_IM_R2Y_PORT_1].cache_type;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYWAAXCTL.bit.YYWAPROT_1  = r2y_ctrl_axi->yyw[D_IM_R2Y_YYW_CH_0A][D_IM_R2Y_PORT_1].protect_type;

	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW1AXCTL.bit.YYW1CACHE_0 = r2y_ctrl_axi->yyw[D_IM_R2Y_YYW_CH_1][D_IM_R2Y_PORT_0].cache_type;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW1AXCTL.bit.YYW1PROT_0  = r2y_ctrl_axi->yyw[D_IM_R2Y_YYW_CH_1][D_IM_R2Y_PORT_0].protect_type;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW1AXCTL.bit.YYW1CACHE_1 = r2y_ctrl_axi->yyw[D_IM_R2Y_YYW_CH_1][D_IM_R2Y_PORT_1].cache_type;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW1AXCTL.bit.YYW1PROT_1  = r2y_ctrl_axi->yyw[D_IM_R2Y_YYW_CH_1][D_IM_R2Y_PORT_1].protect_type;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW1AXCTL.bit.YYW1CACHE_2 = r2y_ctrl_axi->yyw[D_IM_R2Y_YYW_CH_1][D_IM_R2Y_PORT_2].cache_type;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW1AXCTL.bit.YYW1PROT_2  = r2y_ctrl_axi->yyw[D_IM_R2Y_YYW_CH_1][D_IM_R2Y_PORT_2].protect_type;

	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW2AXCTL.bit.YYW2CACHE = r2y_ctrl_axi->yyw[D_IM_R2Y_YYW_CH_2][D_IM_R2Y_PORT_0].cache_type;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW2AXCTL.bit.YYW2PROT  = r2y_ctrl_axi->yyw[D_IM_R2Y_YYW_CH_2][D_IM_R2Y_PORT_0].protect_type;

	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );

	Im_R2Y_Dsb();

	return D_DDIM_OK;
}

/* get AXI bus read channel status
 */
INT32 im_r2y_get_axi_read_stat(ImR2y *self, UCHAR pipe_no, T_IM_R2Y_AXI_YYR_STAT* const r2y_axi_read_stat )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2y_axi_read_stat == NULL ) {
		Ddim_Assertion(("im_r2y_get_axi_read_stat error. r2y_axi_read_stat = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no >= D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_get_axi_read_stat error. pipe_no>=D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	r2y_axi_read_stat->yyr_axi_stat[D_IM_R2Y_PORT_0] = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYRAXSTS.bit.YYRRESP_0;
	r2y_axi_read_stat->yyr_axi_stat[D_IM_R2Y_PORT_1] = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYRAXSTS.bit.YYRRESP_1;
	r2y_axi_read_stat->yyr_axi_stat[D_IM_R2Y_PORT_2] = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYRAXSTS.bit.YYRRESP_2;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );

	return D_DDIM_OK;
}

/* get AXI bus write channel status
 */
INT32 im_r2y_get_axi_write_stat(ImR2y *self, UCHAR pipe_no, T_IM_R2Y_AXI_YYW_STAT* const r2y_axi_write_stat )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2y_axi_write_stat == NULL ) {
		Ddim_Assertion(("im_r2y_get_axi_write_stat error. r2y_axi_write_stat = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no >= D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_get_axi_write_stat error. pipe_no>=D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	r2y_axi_write_stat->yyw0_axi_stat[D_IM_R2Y_PORT_0] = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW0AXSTS.bit.YY0BRESP_0;
	r2y_axi_write_stat->yyw0_axi_stat[D_IM_R2Y_PORT_1] = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW0AXSTS.bit.YY0BRESP_1;
	r2y_axi_write_stat->yyw0_axi_stat[D_IM_R2Y_PORT_2] = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW0AXSTS.bit.YY0BRESP_2;

	r2y_axi_write_stat->yyw0a_axi_stat[D_IM_R2Y_PORT_0] = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYWAAXSTS.bit.YYABRESP_0;
	r2y_axi_write_stat->yyw0a_axi_stat[D_IM_R2Y_PORT_1] = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYWAAXSTS.bit.YYABRESP_1;

	r2y_axi_write_stat->yyw1_axi_stat[D_IM_R2Y_PORT_0] = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW1AXSTS.bit.YY1BRESP_0;
	r2y_axi_write_stat->yyw1_axi_stat[D_IM_R2Y_PORT_1] = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW1AXSTS.bit.YY1BRESP_1;
	r2y_axi_write_stat->yyw1_axi_stat[D_IM_R2Y_PORT_2] = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW1AXSTS.bit.YY1BRESP_2;

	r2y_axi_write_stat->yyw2_axi_stat = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW2AXSTS.bit.YY2BRESP;

	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );

	return D_DDIM_OK;
}

/* get AXI bus write channel Transfer mode
 */
INT32 im_r2y_get_axi_write_mode(ImR2y *self, UCHAR pipe_no, UCHAR yyw_no, T_IM_R2Y_AXI_YYW_MODE* const r2y_axi_write_mode )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2y_axi_write_mode == NULL ){
		Ddim_Assertion(("im_r2y_get_axi_write_mode error. r2y_axi_write_mode = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no >= D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_get_axi_write_mode error. pipe_no>=D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	r2y_axi_write_mode->out_enable[D_IM_R2Y_PORT_0] = D_IM_R2Y_ENABLE_OFF;
	r2y_axi_write_mode->out_enable[D_IM_R2Y_PORT_1] = D_IM_R2Y_ENABLE_OFF;
	r2y_axi_write_mode->out_enable[D_IM_R2Y_PORT_2] = D_IM_R2Y_ENABLE_OFF;

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );

	switch( yyw_no ){
		case D_IM_R2Y_YYW_CH_1:
			r2y_axi_write_mode->master_if_select = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW1AXMD.bit.YYW1MSL;
			if((gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW1AXMD.bit.YYW1DOE & 1) != 0){
				r2y_axi_write_mode->out_enable[D_IM_R2Y_PORT_0] = D_IM_R2Y_ENABLE_ON;
			}
			if((gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW1AXMD.bit.YYW1DOE & 2) != 0){
				r2y_axi_write_mode->out_enable[D_IM_R2Y_PORT_1] = D_IM_R2Y_ENABLE_ON;
			}
			if((gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW1AXMD.bit.YYW1DOE & 4) != 0){
				r2y_axi_write_mode->out_enable[D_IM_R2Y_PORT_2] = D_IM_R2Y_ENABLE_ON;
			}
			r2y_axi_write_mode->burst_length = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW1AXMD.bit.YYW1BL;
			break;
		case D_IM_R2Y_YYW_CH_2:
			r2y_axi_write_mode->master_if_select = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW2AXMD.bit.YYW2MSL;
			r2y_axi_write_mode->burst_length = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW2AXMD.bit.YYW2BL;
			break;
		case D_IM_R2Y_YYW_CH_0A:
			r2y_axi_write_mode->master_if_select = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYWAAXMD.bit.YYWAMSL;
			if((gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYWAAXMD.bit.YYWADOE & 1) != 0){
				r2y_axi_write_mode->out_enable[D_IM_R2Y_PORT_0] = D_IM_R2Y_ENABLE_ON;
			}
			if((gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYWAAXMD.bit.YYWADOE & 2) != 0){
				r2y_axi_write_mode->out_enable[D_IM_R2Y_PORT_1] = D_IM_R2Y_ENABLE_ON;
			}
			r2y_axi_write_mode->burst_length = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYWAAXMD.bit.YYWABL;
			break;
//		case D_IM_R2Y_YYW_CH_0:
		default:
			r2y_axi_write_mode->master_if_select = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW0AXMD.bit.YYW0MSL;
			if((gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW0AXMD.bit.YYW0DOE & 1) != 0){
				r2y_axi_write_mode->out_enable[D_IM_R2Y_PORT_0] = D_IM_R2Y_ENABLE_ON;
			}
			if((gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW0AXMD.bit.YYW0DOE & 2) != 0){
				r2y_axi_write_mode->out_enable[D_IM_R2Y_PORT_1] = D_IM_R2Y_ENABLE_ON;
			}
			if((gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW0AXMD.bit.YYW0DOE & 4) != 0){
				r2y_axi_write_mode->out_enable[D_IM_R2Y_PORT_2] = D_IM_R2Y_ENABLE_ON;
			}
			r2y_axi_write_mode->burst_length = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW0AXMD.bit.YYW0BL;
			break;
	}

	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );

	return D_DDIM_OK;
}

/* set AXI bus write channel Transfer mode
 */
INT32 im_r2y_set_axi_write_mode(ImR2y *self, UCHAR pipe_no, UCHAR yyw_no, const T_IM_R2Y_AXI_YYW_MODE* const r2y_axi_write_mode )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2y_axi_write_mode == NULL ){
		Ddim_Assertion(("im_r2y_set_axi_write_mode error. r2y_axi_write_mode = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_set_axi_write_mode error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	switch( yyw_no ){
		case D_IM_R2Y_YYW_CH_1:
			gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW1AXMD.bit.YYW1MSL = r2y_axi_write_mode->master_if_select;
			gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW1AXMD.bit.YYW1DOE = (ULONG)(
																	 ((r2y_axi_write_mode->out_enable[D_IM_R2Y_PORT_0] != D_IM_R2Y_ENABLE_ON) ? (0) : (1)) |
																	 ((r2y_axi_write_mode->out_enable[D_IM_R2Y_PORT_1] != D_IM_R2Y_ENABLE_ON) ? (0) : (2)) |
																	 ((r2y_axi_write_mode->out_enable[D_IM_R2Y_PORT_2] != D_IM_R2Y_ENABLE_ON) ? (0) : (4))
																	 );
			gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW1AXMD.bit.YYW1BL  = r2y_axi_write_mode->burst_length;
			break;
		case D_IM_R2Y_YYW_CH_2:
			gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW2AXMD.bit.YYW2MSL = r2y_axi_write_mode->master_if_select;
			gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW2AXMD.bit.YYW2BL  = r2y_axi_write_mode->burst_length;
			break;
		case D_IM_R2Y_YYW_CH_0A:
			gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYWAAXMD.bit.YYWAMSL = r2y_axi_write_mode->master_if_select;
			gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYWAAXMD.bit.YYWADOE = (ULONG)(
																	 ((r2y_axi_write_mode->out_enable[D_IM_R2Y_PORT_0] != D_IM_R2Y_ENABLE_ON) ? (0) : (1)) |
																	 ((r2y_axi_write_mode->out_enable[D_IM_R2Y_PORT_1] != D_IM_R2Y_ENABLE_ON) ? (0) : (2))
																	 );
			gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYWAAXMD.bit.YYWABL  = r2y_axi_write_mode->burst_length;
			break;
//		case D_IM_R2Y_YYW_CH_0:
		default:
			gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW0AXMD.bit.YYW0MSL = r2y_axi_write_mode->master_if_select;
			gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW0AXMD.bit.YYW0DOE = (ULONG)(
																	 ((r2y_axi_write_mode->out_enable[D_IM_R2Y_PORT_0] != D_IM_R2Y_ENABLE_ON) ? (0) : (1)) |
																	 ((r2y_axi_write_mode->out_enable[D_IM_R2Y_PORT_1] != D_IM_R2Y_ENABLE_ON) ? (0) : (2)) |
																	 ((r2y_axi_write_mode->out_enable[D_IM_R2Y_PORT_2] != D_IM_R2Y_ENABLE_ON) ? (0) : (4))
																	 );
			gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW0AXMD.bit.YYW0BL  = r2y_axi_write_mode->burst_length;
			break;
	}

	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );

	return D_DDIM_OK;
}

/* R2Y Control (each mode common control)
 */
INT32 im_r2y_ctrl(ImR2y *self, UCHAR pipe_no, const T_IM_R2Y_CTRL* const r2y_ctrl )
{
	UCHAR yyw_no;
	UCHAR loop_cnt, loop_sta, loop_end;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile T_IM_R2Y_STATE_MNG* gIM_R2Y_State = im_r2y_utils_get_state_mng(imR2yUtils);
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2y_ctrl == NULL ) {
		Ddim_Assertion(("im_r2y_ctrl error. r2y_ctrl = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_utils_get_loop_val(imR2yUtils, pipe_no, &loop_sta, &loop_end );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		gIM_R2Y_State[loop_cnt].yyw_enable[D_IM_R2Y_YYW_CH_0]          = r2y_ctrl->yyw_enable[D_IM_R2Y_YYW_CH_0];
		gIM_R2Y_State[loop_cnt].yyw_enable[D_IM_R2Y_YYW_CH_1]          = r2y_ctrl->yyw_enable[D_IM_R2Y_YYW_CH_1];
		gIM_R2Y_State[loop_cnt].yyw_enable[D_IM_R2Y_YYW_CH_2]          = r2y_ctrl->yyw_enable[D_IM_R2Y_YYW_CH_2];
		gIM_R2Y_State[loop_cnt].ycf_bypass                             = r2y_ctrl->ycf_bypass;
		gIM_R2Y_State[loop_cnt].ycf_padding                            = r2y_ctrl->ycf_padding;
		gIM_R2Y_State[loop_cnt].mcc_select                             = r2y_ctrl->mcc_select;
		gIM_R2Y_State[loop_cnt].mcc_bit_shift                          = r2y_ctrl->mcc_bit_shift;
		gIM_R2Y_State[loop_cnt].r2y_user_handler                       = r2y_ctrl->r2y_user_handler;
		gIM_R2Y_State[loop_cnt].user_param                             = r2y_ctrl->user_param;
		gIM_R2Y_State[loop_cnt].pix_avg_reduct_mode[D_IM_R2Y_YYW_CH_0] = r2y_ctrl->yyw[D_IM_R2Y_YYW_CH_0].pixel_avg_reduction_mode;
		gIM_R2Y_State[loop_cnt].pix_avg_reduct_mode[D_IM_R2Y_YYW_CH_1] = r2y_ctrl->yyw[D_IM_R2Y_YYW_CH_1].pixel_avg_reduction_mode;
		gIM_R2Y_State[loop_cnt].pix_avg_reduct_mode[D_IM_R2Y_YYW_CH_2] = r2y_ctrl->yyw[D_IM_R2Y_YYW_CH_2].pixel_avg_reduction_mode;
		gIM_R2Y_State[loop_cnt].pix_avg_reduct_en[D_IM_R2Y_YYW_CH_0]   = r2y_ctrl->yyw[D_IM_R2Y_YYW_CH_0].pixel_avg_reduction_enable;
		gIM_R2Y_State[loop_cnt].pix_avg_reduct_en[D_IM_R2Y_YYW_CH_1]   = r2y_ctrl->yyw[D_IM_R2Y_YYW_CH_1].pixel_avg_reduction_enable;
		gIM_R2Y_State[loop_cnt].pix_avg_reduct_en[D_IM_R2Y_YYW_CH_2]   = r2y_ctrl->yyw[D_IM_R2Y_YYW_CH_2].pixel_avg_reduction_enable;
		gIM_R2Y_State[loop_cnt].output_mode_0a                         = r2y_ctrl->output_mode_0a;
		if( r2y_ctrl->yyw_enable[D_IM_R2Y_YYW_CH_0] == D_IM_R2Y_ENABLE_ON ) {
			gIM_R2Y_State[loop_cnt].resize_mode[D_IM_R2Y_YYW_CH_0]     = r2y_ctrl->yyw[D_IM_R2Y_YYW_CH_0].resize_mode;
		}
		if( r2y_ctrl->yyw_enable[D_IM_R2Y_YYW_CH_1] == D_IM_R2Y_ENABLE_ON ) {
			gIM_R2Y_State[loop_cnt].resize_mode[D_IM_R2Y_YYW_CH_1]     = r2y_ctrl->yyw[D_IM_R2Y_YYW_CH_1].resize_mode;
		}
	}

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );

	// YYCH

	// R2Y_CMN
	gIM_Io_R2y_Reg_Ptr[pipe_no]->R2Y_CMN.LINTLV.bit.LINTLV_0 = r2y_ctrl->line_intr[D_IM_R2Y_LINE_INT_0].level;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->R2Y_CMN.LINTLV.bit.LINTLV_1 = r2y_ctrl->line_intr[D_IM_R2Y_LINE_INT_1].level;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->R2Y_CMN.LINTLV.bit.LINTLV_2 = r2y_ctrl->line_intr[D_IM_R2Y_LINE_INT_2].level;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->R2Y_CMN.LINTSEL.bit.LINTS_0 = r2y_ctrl->line_intr[D_IM_R2Y_LINE_INT_0].yyw_select;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->R2Y_CMN.LINTSEL.bit.LINTS_1 = r2y_ctrl->line_intr[D_IM_R2Y_LINE_INT_1].yyw_select;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->R2Y_CMN.LINTSEL.bit.LINTS_2 = r2y_ctrl->line_intr[D_IM_R2Y_LINE_INT_2].yyw_select;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->R2Y_CMN.R2YMODE.bit.YCFBYP  = r2y_ctrl->ycf_bypass;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->R2Y_CMN.R2YMODE.bit.YCFPDD  = r2y_ctrl->ycf_padding;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->R2Y_CMN.R2YMODE.bit.MCCSL   = r2y_ctrl->mcc_select;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->R2Y_CMN.R2YMODE.bit.MCC1BM  = r2y_ctrl->mcc_bit_shift;

	// YYW
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0LTT.bit.YYW0LTT = r2y_ctrl->line_transfer_cycle;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYWCTL.bit.YYWCSE   = r2y_ctrl->yyw_continue_start_enable;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYWCTL.bit.YYWHRV   = r2y_ctrl->yyw_horizontal_flip;

	// setting YYW0/1/2 indivisually
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYWCTL.bit.YYWMODE = (ULONG)(
														  ((r2y_ctrl->yyw_enable[D_IM_R2Y_YYW_CH_0] != D_IM_R2Y_ENABLE_OFF)?(1):(0)) |
														  ((r2y_ctrl->yyw_enable[D_IM_R2Y_YYW_CH_1] != D_IM_R2Y_ENABLE_OFF)?(2):(0)) |
														  ((r2y_ctrl->yyw_enable[D_IM_R2Y_YYW_CH_2] != D_IM_R2Y_ENABLE_OFF)?(4):(0))
														  );

	// YYW0/0A
	if( r2y_ctrl->yyw_enable[D_IM_R2Y_YYW_CH_0] == D_IM_R2Y_ENABLE_ON ) {
		yyw_no = D_IM_R2Y_YYW_CH_0;

		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW0AXMD.bit.YYW0MSL        = r2y_ctrl->yyw[ yyw_no ].axi_write_mode.master_if_select;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW0AXMD.bit.YYW0DOE        = (ULONG)(
																		((r2y_ctrl->yyw[yyw_no].axi_write_mode.out_enable[D_IM_R2Y_PORT_0] != D_IM_R2Y_ENABLE_ON)?(0):(1)) |
																		((r2y_ctrl->yyw[yyw_no].axi_write_mode.out_enable[D_IM_R2Y_PORT_1] != D_IM_R2Y_ENABLE_ON)?(0):(2)) |
																		((r2y_ctrl->yyw[yyw_no].axi_write_mode.out_enable[D_IM_R2Y_PORT_2] != D_IM_R2Y_ENABLE_ON)?(0):(4))
																		);
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW0AXMD.bit.YYW0BL         = r2y_ctrl->yyw[ yyw_no ].axi_write_mode.burst_length;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW0REQMSK.bit.YYW0REQMSK_0 = r2y_ctrl->yyw[ yyw_no ].write_request_mask[D_IM_R2Y_PORT_0];
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW0REQMSK.bit.YYW0REQMSK_1 = r2y_ctrl->yyw[ yyw_no ].write_request_mask[D_IM_R2Y_PORT_1];
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW0REQMSK.bit.YYW0REQMSK_2 = r2y_ctrl->yyw[ yyw_no ].write_request_mask[D_IM_R2Y_PORT_2];
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0MD.bit.RSZ0MD            = r2y_ctrl->yyw[ yyw_no ].resize_mode;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0MD.bit.RDC0MD            = r2y_ctrl->yyw[ yyw_no ].pixel_avg_reduction_mode;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0MD.bit.RDC0EN            = r2y_ctrl->yyw[ yyw_no ].pixel_avg_reduction_enable;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0MD.bit.CSS0SL            = r2y_ctrl->yyw[ yyw_no ].ycc_cc_thin_select;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0MD.bit.TRM0EN            = r2y_ctrl->yyw[ yyw_no ].trim_out_enable;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0MD.bit.SPL0EN            = r2y_ctrl->yyw[ yyw_no ].planar_interleaved_mode;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0MD.bit.CH0VFM            = r2y_ctrl->video_format_out_select_0;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0MD.bit.EXTBEN            = r2y_ctrl->ipu_macro_output_enable;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0MD.bit.TRMBEN            = r2y_ctrl->ipu_macro_trimming_enable;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0MD.bit.EXTCEN            = r2y_ctrl->cnr_macro_output_enable;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0MD.bit.TRMCEN            = r2y_ctrl->cnr_macro_trimming_enable;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0MD.bit.CH0AMD            = r2y_ctrl->output_mode_0a;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0MD.bit.CHAVFM            = r2y_ctrl->video_format_out_select_0a;

		yyw_no = D_IM_R2Y_YYW_CH_0A;

		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYWAAXMD.bit.YYWAMSL        = r2y_ctrl->yyw[ yyw_no ].axi_write_mode.master_if_select;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYWAAXMD.bit.YYWADOE        = (ULONG)(
																		((r2y_ctrl->yyw[yyw_no].axi_write_mode.out_enable[D_IM_R2Y_PORT_0] != D_IM_R2Y_ENABLE_ON)?(0):(1)) |
																		((r2y_ctrl->yyw[yyw_no].axi_write_mode.out_enable[D_IM_R2Y_PORT_1] != D_IM_R2Y_ENABLE_ON)?(0):(2))
																		);
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYWAAXMD.bit.YYWABL         = r2y_ctrl->yyw[ yyw_no ].axi_write_mode.burst_length;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYWAREQMSK.bit.YYWAREQMSK_0 = r2y_ctrl->yyw[ yyw_no ].write_request_mask[D_IM_R2Y_PORT_0];
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYWAREQMSK.bit.YYWAREQMSK_1 = r2y_ctrl->yyw[ yyw_no ].write_request_mask[D_IM_R2Y_PORT_1];
	}

	// YYW1
	if( r2y_ctrl->yyw_enable[D_IM_R2Y_YYW_CH_1] == D_IM_R2Y_ENABLE_ON ) {
		yyw_no = D_IM_R2Y_YYW_CH_1;

		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW1AXMD.bit.YYW1MSL        = r2y_ctrl->yyw[ yyw_no ].axi_write_mode.master_if_select;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW1AXMD.bit.YYW1DOE        = (ULONG)(
																		((r2y_ctrl->yyw[yyw_no].axi_write_mode.out_enable[D_IM_R2Y_PORT_0] != D_IM_R2Y_ENABLE_ON)?(0):(1)) |
																		((r2y_ctrl->yyw[yyw_no].axi_write_mode.out_enable[D_IM_R2Y_PORT_1] != D_IM_R2Y_ENABLE_ON)?(0):(2)) |
																		((r2y_ctrl->yyw[yyw_no].axi_write_mode.out_enable[D_IM_R2Y_PORT_2] != D_IM_R2Y_ENABLE_ON)?(0):(4))
																		);
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW1AXMD.bit.YYW1BL         = r2y_ctrl->yyw[ yyw_no ].axi_write_mode.burst_length;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW1REQMSK.bit.YYW1REQMSK_0 = r2y_ctrl->yyw[ yyw_no ].write_request_mask[D_IM_R2Y_PORT_0];
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW1REQMSK.bit.YYW1REQMSK_1 = r2y_ctrl->yyw[ yyw_no ].write_request_mask[D_IM_R2Y_PORT_1];
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW1REQMSK.bit.YYW1REQMSK_2 = r2y_ctrl->yyw[ yyw_no ].write_request_mask[D_IM_R2Y_PORT_2];
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW1MD.bit.RSZ1MD            = r2y_ctrl->yyw[ yyw_no ].resize_mode;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW1MD.bit.RDC1MD            = r2y_ctrl->yyw[ yyw_no ].pixel_avg_reduction_mode;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW1MD.bit.RDC1EN            = r2y_ctrl->yyw[ yyw_no ].pixel_avg_reduction_enable;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW1MD.bit.CSS1SL            = r2y_ctrl->yyw[ yyw_no ].ycc_cc_thin_select;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW1MD.bit.TRM1EN            = r2y_ctrl->yyw[ yyw_no ].trim_out_enable;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW1MD.bit.SPL1EN            = r2y_ctrl->yyw[ yyw_no ].planar_interleaved_mode;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW1MD.bit.DFM1SL            = r2y_ctrl->output_format_sel1;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW1MD.bit.DTY1SL            = r2y_ctrl->output_type_sel1;
	}

	// YYW2
	if( r2y_ctrl->yyw_enable[D_IM_R2Y_YYW_CH_2] == D_IM_R2Y_ENABLE_ON ) {
		yyw_no = D_IM_R2Y_YYW_CH_2;

		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW2AXMD.bit.YYW2MSL      = r2y_ctrl->yyw[ yyw_no ].axi_write_mode.master_if_select;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW2AXMD.bit.YYW2BL       = r2y_ctrl->yyw[ yyw_no ].axi_write_mode.burst_length;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYW2REQMSK.bit.YYW2REQMSK = r2y_ctrl->yyw[ yyw_no ].write_request_mask[D_IM_R2Y_PORT_0];
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW2MD.bit.RDC2MD          = r2y_ctrl->yyw[ yyw_no ].pixel_avg_reduction_mode;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW2MD.bit.RDC2EN          = r2y_ctrl->yyw[ yyw_no ].pixel_avg_reduction_enable;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW2MD.bit.TRM2EN          = r2y_ctrl->yyw[ yyw_no ].trim_out_enable;
	}

	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );

	imR2yCalcRingPixs( pipe_no );

	Im_R2Y_Dsb();

	return D_DDIM_OK;
}

/* R2Y Control (SDRAM input mode control)
 */
INT32 im_r2y_ctrl_mode_sdram_input(ImR2y *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_SDRAM_INPUT* const r2y_ctrl_sdram_input )
{
	UCHAR loop_cnt, loop_sta, loop_end;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile T_IM_R2Y_STATE_MNG* gIM_R2Y_State = im_r2y_utils_get_state_mng(imR2yUtils);
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2y_ctrl_sdram_input == NULL ) {
		Ddim_Assertion(("im_r2y_ctrl_mode_sdram_input error. r2y_ctrl_sdram_input = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl_mode_sdram_input error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_utils_get_loop_val(imR2yUtils, pipe_no, &loop_sta, &loop_end );

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		if(im_r2y_yyr_is_activated( loop_cnt )){
#ifdef CO_DEBUG_PRINT_IM_R2Y
			Ddim_Print(( "im_r2y_ctrl_mode_sdram_input error. YYR busy\n" ));
#endif
			im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
			return D_IM_R2Y_MACRO_BUSY;
		}
	}

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		gIM_R2Y_State[loop_cnt].input_dtype                 = r2y_ctrl_sdram_input->input_dtype;
		gIM_R2Y_State[loop_cnt].top_offset[D_IM_R2Y_PORT_0] = r2y_ctrl_sdram_input->top_offset[D_IM_R2Y_PORT_0];
		gIM_R2Y_State[loop_cnt].top_offset[D_IM_R2Y_PORT_1] = r2y_ctrl_sdram_input->top_offset[D_IM_R2Y_PORT_1];
		gIM_R2Y_State[loop_cnt].top_offset[D_IM_R2Y_PORT_2] = r2y_ctrl_sdram_input->top_offset[D_IM_R2Y_PORT_2];
		gIM_R2Y_State[loop_cnt].input_global                = r2y_ctrl_sdram_input->input_global;
		gIM_R2Y_State[loop_cnt].video_photo_mode            = D_IM_R2Y_MODE_SDRAM_INPUT;
	}

	// YYCH
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYRAXMD.bit.YYRBL         = r2y_ctrl_sdram_input->burst_length;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYRREQMSK.bit.YYRREQMSK_0 = r2y_ctrl_sdram_input->read_request_mask[D_IM_R2Y_PORT_0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYRREQMSK.bit.YYRREQMSK_1 = r2y_ctrl_sdram_input->read_request_mask[D_IM_R2Y_PORT_1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYCH.YYRREQMSK.bit.YYRREQMSK_2 = r2y_ctrl_sdram_input->read_request_mask[D_IM_R2Y_PORT_2];

	// YYR
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYR.DINCTL.bit.B2RDIN  = D_IM_R2Y_MODE_SDRAM_INPUT;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYR.YYRCTL.bit.YYRDTYP = r2y_ctrl_sdram_input->input_dtype;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYR.YYRCTL.bit.MONOEN  = r2y_ctrl_sdram_input->mono_ebable;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYR.YYRCTL.bit.DKNEN   = r2y_ctrl_sdram_input->rgb_deknee_enable;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYR.YYRCTL.bit.RGBLSFT = r2y_ctrl_sdram_input->rgb_left_shift;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYR.YYRCTL.bit.RGBLSM  = r2y_ctrl_sdram_input->rgb_saturation_mode;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYR.YYRDEF.bit.YYRDEF  = r2y_ctrl_sdram_input->input_global;

	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
	Im_R2Y_Dsb();

	return D_DDIM_OK;
}

/* Set Managed Input Address information
 */
INT32 im_r2y_set_inaddr_info(ImR2y *self, UCHAR pipe_no, const T_IM_R2Y_INADDR_INFO* const in_addr )
{
	UCHAR loop_cnt, loop_sta, loop_end;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile T_IM_R2Y_STATE_MNG* gIM_R2Y_State = im_r2y_utils_get_state_mng(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( in_addr == NULL ) {
		Ddim_Assertion(("im_r2y_set_inaddr_info error. in_addr = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_set_inaddr_info error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_utils_get_loop_val(imR2yUtils, pipe_no, &loop_sta, &loop_end );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		gIM_R2Y_State[loop_cnt].in_addr[D_IM_R2Y_PORT_R] = (ULONG)in_addr->rgb.addr_R;
		gIM_R2Y_State[loop_cnt].in_addr[D_IM_R2Y_PORT_G] = (ULONG)in_addr->rgb.addr_G;
		gIM_R2Y_State[loop_cnt].in_addr[D_IM_R2Y_PORT_B] = (ULONG)in_addr->rgb.addr_B;
		imR2ySetYyrAddressSdramInput( loop_cnt );
	}

	return D_DDIM_OK;
}

/* Set Managed bank information
 */
INT32 im_r2y_set_out_bank_info(ImR2y *self, UCHAR pipe_no, UCHAR yyw_no, const T_IM_R2Y_OUTBANK_INFO* const r2y_bank )
{
	INT32 ercd;
	UCHAR loop_cnt, loop_sta, loop_end;
	UCHAR index;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2y_bank == NULL ) {
		Ddim_Assertion(("im_r2y_set_out_bank_info error. r2y_bank = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( yyw_no >= D_IM_R2Y_YYW_CH_MAX ) {
		Ddim_Assertion(("im_r2y_set_out_bank_info error. yyw_no >= MAX\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_set_out_bank_info error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_utils_get_loop_val(imR2yUtils, pipe_no, &loop_sta, &loop_end );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		gIM_R2Y_Out_Mng[loop_cnt][yyw_no].bank_info = *r2y_bank;
	}

	if( pipe_no == D_IM_R2Y_PIPE12 ){
		index = 0;
	}
	else{
		index = pipe_no;
	}

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	// YYW0A
	if( yyw_no == D_IM_R2Y_YYW_CH_0 ) {
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYWCTL.bit.USEBANK0 = gIM_R2Y_Out_Mng[index][yyw_no].bank_info.use_bank_num;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0A.bit.YYW0A_0_0 = (ULONG)gIM_R2Y_Out_Mng[index][yyw_no].bank_info.output_addr[D_IM_R2Y_YYW_BANK_0].ycc.addr_Y;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0A.bit.YYW0A_1_0 = (ULONG)gIM_R2Y_Out_Mng[index][yyw_no].bank_info.output_addr[D_IM_R2Y_YYW_BANK_0].ycc.addr_Cb;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0A.bit.YYW0A_2_0 = (ULONG)gIM_R2Y_Out_Mng[index][yyw_no].bank_info.output_addr[D_IM_R2Y_YYW_BANK_0].ycc.addr_Cr;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0A.bit.YYW0A_0_1 = (ULONG)gIM_R2Y_Out_Mng[index][yyw_no].bank_info.output_addr[D_IM_R2Y_YYW_BANK_1].ycc.addr_Y;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0A.bit.YYW0A_1_1 = (ULONG)gIM_R2Y_Out_Mng[index][yyw_no].bank_info.output_addr[D_IM_R2Y_YYW_BANK_1].ycc.addr_Cb;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0A.bit.YYW0A_2_1 = (ULONG)gIM_R2Y_Out_Mng[index][yyw_no].bank_info.output_addr[D_IM_R2Y_YYW_BANK_1].ycc.addr_Cr;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0A.bit.YYW0A_0_2 = (ULONG)gIM_R2Y_Out_Mng[index][yyw_no].bank_info.output_addr[D_IM_R2Y_YYW_BANK_2].ycc.addr_Y;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0A.bit.YYW0A_1_2 = (ULONG)gIM_R2Y_Out_Mng[index][yyw_no].bank_info.output_addr[D_IM_R2Y_YYW_BANK_2].ycc.addr_Cb;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0A.bit.YYW0A_2_2 = (ULONG)gIM_R2Y_Out_Mng[index][yyw_no].bank_info.output_addr[D_IM_R2Y_YYW_BANK_2].ycc.addr_Cr;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0A.bit.YYW0A_0_3 = (ULONG)gIM_R2Y_Out_Mng[index][yyw_no].bank_info.output_addr[D_IM_R2Y_YYW_BANK_3].ycc.addr_Y;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0A.bit.YYW0A_1_3 = (ULONG)gIM_R2Y_Out_Mng[index][yyw_no].bank_info.output_addr[D_IM_R2Y_YYW_BANK_3].ycc.addr_Cb;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0A.bit.YYW0A_2_3 = (ULONG)gIM_R2Y_Out_Mng[index][yyw_no].bank_info.output_addr[D_IM_R2Y_YYW_BANK_3].ycc.addr_Cr;
	}
	// YYW1A
	else if( yyw_no == D_IM_R2Y_YYW_CH_1 ){
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYWCTL.bit.USEBANK1 = gIM_R2Y_Out_Mng[index][yyw_no].bank_info.use_bank_num;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW1A.bit.YYW1A_0_0 = (ULONG)gIM_R2Y_Out_Mng[index][yyw_no].bank_info.output_addr[D_IM_R2Y_YYW_BANK_0].ycc.addr_Y;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW1A.bit.YYW1A_1_0 = (ULONG)gIM_R2Y_Out_Mng[index][yyw_no].bank_info.output_addr[D_IM_R2Y_YYW_BANK_0].ycc.addr_Cb;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW1A.bit.YYW1A_2_0 = (ULONG)gIM_R2Y_Out_Mng[index][yyw_no].bank_info.output_addr[D_IM_R2Y_YYW_BANK_0].ycc.addr_Cr;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW1A.bit.YYW1A_0_1 = (ULONG)gIM_R2Y_Out_Mng[index][yyw_no].bank_info.output_addr[D_IM_R2Y_YYW_BANK_1].ycc.addr_Y;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW1A.bit.YYW1A_1_1 = (ULONG)gIM_R2Y_Out_Mng[index][yyw_no].bank_info.output_addr[D_IM_R2Y_YYW_BANK_1].ycc.addr_Cb;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW1A.bit.YYW1A_2_1 = (ULONG)gIM_R2Y_Out_Mng[index][yyw_no].bank_info.output_addr[D_IM_R2Y_YYW_BANK_1].ycc.addr_Cr;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW1A.bit.YYW1A_0_2 = (ULONG)gIM_R2Y_Out_Mng[index][yyw_no].bank_info.output_addr[D_IM_R2Y_YYW_BANK_2].ycc.addr_Y;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW1A.bit.YYW1A_1_2 = (ULONG)gIM_R2Y_Out_Mng[index][yyw_no].bank_info.output_addr[D_IM_R2Y_YYW_BANK_2].ycc.addr_Cb;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW1A.bit.YYW1A_2_2 = (ULONG)gIM_R2Y_Out_Mng[index][yyw_no].bank_info.output_addr[D_IM_R2Y_YYW_BANK_2].ycc.addr_Cr;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW1A.bit.YYW1A_0_3 = (ULONG)gIM_R2Y_Out_Mng[index][yyw_no].bank_info.output_addr[D_IM_R2Y_YYW_BANK_3].ycc.addr_Y;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW1A.bit.YYW1A_1_3 = (ULONG)gIM_R2Y_Out_Mng[index][yyw_no].bank_info.output_addr[D_IM_R2Y_YYW_BANK_3].ycc.addr_Cb;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW1A.bit.YYW1A_2_3 = (ULONG)gIM_R2Y_Out_Mng[index][yyw_no].bank_info.output_addr[D_IM_R2Y_YYW_BANK_3].ycc.addr_Cr;
	}
	// YYW2A
	else if( yyw_no == D_IM_R2Y_YYW_CH_2 ){
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYWCTL.bit.USEBANK2 = gIM_R2Y_Out_Mng[index][yyw_no].bank_info.use_bank_num;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW2A.bit.YYW2A_0 = (ULONG)gIM_R2Y_Out_Mng[index][yyw_no].bank_info.output_addr[D_IM_R2Y_YYW_BANK_0].ycc.addr_Y;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW2A.bit.YYW2A_1 = (ULONG)gIM_R2Y_Out_Mng[index][yyw_no].bank_info.output_addr[D_IM_R2Y_YYW_BANK_1].ycc.addr_Y;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW2A.bit.YYW2A_2 = (ULONG)gIM_R2Y_Out_Mng[index][yyw_no].bank_info.output_addr[D_IM_R2Y_YYW_BANK_2].ycc.addr_Y;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW2A.bit.YYW2A_3 = (ULONG)gIM_R2Y_Out_Mng[index][yyw_no].bank_info.output_addr[D_IM_R2Y_YYW_BANK_3].ycc.addr_Y;
	}
	// YYWAA
	else{
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYWCTL.bit.USEBANKA = gIM_R2Y_Out_Mng[index][yyw_no].bank_info.use_bank_num;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYWAA.bit.YYWAA_0_0 = (ULONG)gIM_R2Y_Out_Mng[index][yyw_no].bank_info.output_addr[D_IM_R2Y_YYW_BANK_0].ycc.addr_Y;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYWAA.bit.YYWAA_1_0 = (ULONG)gIM_R2Y_Out_Mng[index][yyw_no].bank_info.output_addr[D_IM_R2Y_YYW_BANK_0].ycc.addr_Cb;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYWAA.bit.YYWAA_0_1 = (ULONG)gIM_R2Y_Out_Mng[index][yyw_no].bank_info.output_addr[D_IM_R2Y_YYW_BANK_1].ycc.addr_Y;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYWAA.bit.YYWAA_1_1 = (ULONG)gIM_R2Y_Out_Mng[index][yyw_no].bank_info.output_addr[D_IM_R2Y_YYW_BANK_1].ycc.addr_Cb;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYWAA.bit.YYWAA_0_2 = (ULONG)gIM_R2Y_Out_Mng[index][yyw_no].bank_info.output_addr[D_IM_R2Y_YYW_BANK_2].ycc.addr_Y;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYWAA.bit.YYWAA_1_2 = (ULONG)gIM_R2Y_Out_Mng[index][yyw_no].bank_info.output_addr[D_IM_R2Y_YYW_BANK_2].ycc.addr_Cb;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYWAA.bit.YYWAA_0_3 = (ULONG)gIM_R2Y_Out_Mng[index][yyw_no].bank_info.output_addr[D_IM_R2Y_YYW_BANK_3].ycc.addr_Y;
		gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYWAA.bit.YYWAA_1_3 = (ULONG)gIM_R2Y_Out_Mng[index][yyw_no].bank_info.output_addr[D_IM_R2Y_YYW_BANK_3].ycc.addr_Cb;
	}
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );

	// Set bank index & top address information
	ercd = im_r2y3_set_outbank_index(im_r2y3_new(), pipe_no, yyw_no, gIM_R2Y_Out_Mng[index][yyw_no].bank_info.bank_initial_position );
	if( ercd != D_DDIM_OK ) {
		return ercd;
	}

	return D_DDIM_OK;
}

/* Get bank index value
 */
INT32 im_r2y_get_out_bank_index(ImR2y *self, UCHAR pipe_no, UCHAR yyw_no, UCHAR* const bank_index )
{
#ifdef CO_PARAM_CHECK
	if( bank_index == NULL ) {
		Ddim_Assertion(("im_r2y_get_out_bank_index error. bank_index = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( yyw_no >= D_IM_R2Y_YYW_CH_MAX ) {
		Ddim_Assertion(("im_r2y_get_out_bank_index error. yyw_no >= MAX\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no >= D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_get_out_bank_index error. pipe_no>=D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*bank_index = gIM_R2Y_Out_Mng[pipe_no][yyw_no].latest_idx;

	return D_DDIM_OK;
}

ImR2y *im_r2y_new(void)
{
	ImR2y* self = k_object_new_with_private(IM_TYPE_R2Y,sizeof(ImR2yPrivate));
	return self;
}
