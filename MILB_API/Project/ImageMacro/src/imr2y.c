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
#include "ddarm.h"
#include "imr2ystat.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImR2y, im_r2y);
#define IM_R2Y_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImR2yPrivate, IM_TYPE_R2Y))

/* debug print switch  for im_r2y.c developping/debugging person.
 * (not im_r2y user)
 */
//#define IM_R2Y_DEBUG_PRINT
//#define IM_R2Y_STATUS_PRINT

#define ImR2y_FR2YTRG_IDLE			(2)

struct _ImR2yPrivate
{
	int a;
};

typedef struct {
	R2yOutbankInfo	bank_info;		// Output bank information
	kuint16					latest_idx;		// Latest Output bank index.
	R2yOutaddrInfo	latestAddr;	// Latest Output address.
} T_IM_R2Y_OUTPUT_MNG;



// Output parameter
static volatile T_IM_R2Y_OUTPUT_MNG S_IM_R2Y_OUT_MNG[ImR2yUtils_PIPE_COUNT][ImR2yCtrl_YYW_CH_MAX];


/*
 * DECLS
 */
static void imR2yReset( kuint16 pipeNo );
static void imR2ySetYyrAddressSdramInput( kuint16 pipeNo );
static void imR2yManagerInit( kuint16 pipeNo );
static void imR2yCalcRingPixs( kuint16 pipeNo );


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
static void imR2yReset( kuint16 pipeNo )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);
#ifdef CO_PARAM_CHECK
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "imR2yReset error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	im_r2y_clk_on_hclk(im_r2y_clk_new(),  pipeNo );
	im_r2y_clk_on_iclk(im_r2y_clk_new(),  pipeNo );
	im_r2y_clk_on_clk(im_r2y_clk_new(),  pipeNo );	// TRG off control accompanies the R2Y reset
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CNTL.CNTL.word = 0x0000;
	im_r2y_clk_off_clk(im_r2y_clk_new(),  pipeNo );
	im_r2y_clk_off_iclk(im_r2y_clk_new(),  pipeNo );
	im_r2y_clk_off_hclk(im_r2y_clk_new(),  pipeNo );
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
}

/* Calculate YYRA address after trimming.
 */
static void imR2ySetYyrAddressSdramInput( kuint16 pipeNo )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile R2yStateMng* gImR2yState = im_r2y_utils_get_state_mng(imR2yUtils);
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile R2yYyraOfsInfo* gImR2yYyraOfsInfo = im_r2y_utils_get_yyra_ofs_info(imR2yUtils);

	#ifdef CO_PpipeNoECK
	if( pipeNo >= ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "imR2ySetYyrAddressSdramInput error. pipeNo>=ImR2yCtrl_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );

	gImIoR2yRegPtr[pipeNo]->YYR.YYRA.bit.YYRA_0 = (gImR2yState[pipeNo].inAddr[ImR2yCtrl_PORT_0] + gImR2yYyraOfsInfo[pipeNo].ofsBytes);
	gImIoR2yRegPtr[pipeNo]->YYR.YYRA.bit.YYRA_1 = (gImR2yState[pipeNo].inAddr[ImR2yCtrl_PORT_1] + gImR2yYyraOfsInfo[pipeNo].ofsBytes);
	gImIoR2yRegPtr[pipeNo]->YYR.YYRA.bit.YYRA_2 = (gImR2yState[pipeNo].inAddr[ImR2yCtrl_PORT_2] + gImR2yYyraOfsInfo[pipeNo].ofsBytes);

	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
}

/* Reset internal value
 */
static void imR2yManagerInit( kuint16 pipeNo )
{
	kuint16 size_coef = 1;

#ifdef CO_PARAM_CHECK
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "imR2yManagerInit error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

	if( pipeNo == ImR2yCtrl_PIPE12 ){
		size_coef = 2;
		pipeNo = 0;
	}

	im_r2y_stat_init(im_r2y_stat_new(), pipeNo, size_coef);

	// Initialize of Address management information
	memset( (kuint16*)&S_IM_R2Y_OUT_MNG[pipeNo], 0, sizeof(T_IM_R2Y_OUTPUT_MNG) * ImR2yCtrl_YYW_CH_MAX * size_coef );

	// Initialize of PCLK/HCLK/CLK control information
	//TODO imr2yclk.c
	im_r2y_clk_manager_init(im_r2y_clk_new(), pipeNo, size_coef);

	return;
}

/* Calculate padding pixs and referenced pixs with filter mode
 */
static void imR2yCalcRingPixs( kuint16 pipeNo )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile R2yStateMng* gImR2yState = im_r2y_utils_get_state_mng(imR2yUtils);
	static const R2yRingPixs ring_pixs_info_tbl[2][2] = {	// YCFBYP, YCFPDD
		{	// YCFBYP=0
			{ ImR2yCtrl_ENABLE_OFF, 3, 0, 6 },	// YCFBYP=0, YCFPDD=0
			{ ImR2yCtrl_ENABLE_ON,  3, 6, 0 },	// YCFBYP=0, YCFPDD=1
		},
		{	// YCFBYP=1
			{ ImR2yCtrl_ENABLE_OFF, 0, 0, 0 },	// YCFBYP=1, YCFPDD=0
			{ ImR2yCtrl_ENABLE_ON,  0, 0, 0 },	// YCFBYP=1, YCFPDD=1	NG Setting
		}
	};

	kuint16 loop_cnt, loop_sta, loop_end;

#ifdef CO_PARAM_CHECK
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "imR2yCalcRingPixs error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_utils_get_loop_val(imR2yUtils, pipeNo, &loop_sta, &loop_end );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		// Get current ring pixel information
		gImR2yState[loop_cnt].ringPixsInfo = ring_pixs_info_tbl[gImR2yState[loop_cnt].ycfBypass][gImR2yState[loop_cnt].ycfPadding];

#ifdef IM_R2Y_DEBUG_PRINT
		Ddim_Print(( "imR2yCalcRingPixs(): en=%u ring=%u pad=%u ref=%u\n",
					 gImR2yState[loop_cnt].ringPixsInfo.padEnable,
					 gImR2yState[loop_cnt].ringPixsInfo.ringPixs,
					 gImR2yState[loop_cnt].ringPixsInfo.padPixs,
					 gImR2yState[loop_cnt].ringPixsInfo.refPixs ));
#endif
	}
}


/*
 * PUBLIC
 */
void im_r2y_update_latest_address(ImR2y *self,kuint16 pipeNo, const UINT32 yywNo)
{
		ImR2yUtils* imR2yUtils = im_r2y_utils_get();
		volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

		switch( yywNo ){
		case ImR2yCtrl_YYW_CH_1:
			S_IM_R2Y_OUT_MNG[pipeNo][yywNo].latest_idx = gImIoR2yRegPtr[pipeNo]->YYW.YYWBANK.bit.BANK1STS;
			break;
		case ImR2yCtrl_YYW_CH_2:
			S_IM_R2Y_OUT_MNG[pipeNo][yywNo].latest_idx = gImIoR2yRegPtr[pipeNo]->YYW.YYWBANK.bit.BANK2STS;
			break;
		case ImR2yCtrl_YYW_CH_0A:
			S_IM_R2Y_OUT_MNG[pipeNo][yywNo].latest_idx = gImIoR2yRegPtr[pipeNo]->YYW.YYWBANK.bit.BANKASTS;
			break;
//		case ImR2yCtrl_YYW_CH_0:
		default:
			S_IM_R2Y_OUT_MNG[pipeNo][yywNo].latest_idx = gImIoR2yRegPtr[pipeNo]->YYW.YYWBANK.bit.BANK0STS;
			break;
	}
	S_IM_R2Y_OUT_MNG[pipeNo][yywNo].latestAddr = S_IM_R2Y_OUT_MNG[pipeNo][yywNo].bank_info.outputAddr[ S_IM_R2Y_OUT_MNG[pipeNo][yywNo].latest_idx ];

}

void im_r2y_get_next_r2y_addr(ImR2y *self, kuint16 pipeNo,
 const UINT32 yywNo, R2yOutaddrInfo* const r2yAddr)
{
	*r2yAddr = S_IM_R2Y_OUT_MNG[pipeNo][yywNo].bank_info.outputAddr[ (S_IM_R2Y_OUT_MNG[pipeNo][yywNo].latest_idx + 2)
	                                                                    % (S_IM_R2Y_OUT_MNG[pipeNo][yywNo].bank_info.useBankNum + 1)];
}

void im_r2y_get_latest_addr(ImR2y *self, kuint16 pipeNo, UINT32 yywNo,
 kuint16* const latestBankIdx, R2yOutaddrInfo* const latestAddr)
{
	*latestBankIdx = S_IM_R2Y_OUT_MNG[pipeNo][yywNo].latest_idx;
	*latestAddr     = S_IM_R2Y_OUT_MNG[pipeNo][yywNo].latestAddr;
}

void im_r2y_ddim_print(ImR2y *self,UINT32 loopcnt, UINT32 loopcnt2, UINT32 loopcnt3)
{
		Ddim_Print(( "\t\tlatest_idx = %u\n", S_IM_R2Y_OUT_MNG[loopcnt3][loopcnt2].latest_idx ));
		Ddim_Print(( "\t\tbank_initial_position = %u\n", S_IM_R2Y_OUT_MNG[loopcnt3][loopcnt2].bank_info.bankInitialPosition ));
		Ddim_Print(( "\t\tuse_bank_num = %u\n", S_IM_R2Y_OUT_MNG[loopcnt3][loopcnt2].bank_info.useBankNum ));
		for( loopcnt = 0; loopcnt < ImR2yCtrl_YYW_BANK_MAX; loopcnt++ ) {
			Ddim_Print(( "\t\tBankNum = %u\n", loopcnt ));
			Ddim_Print(( "\t\t\tout_addr[Y]  = 0x%x\n", (UINT32)S_IM_R2Y_OUT_MNG[loopcnt3][loopcnt2].bank_info.outputAddr[loopcnt].ycc.addrY ));
			Ddim_Print(( "\t\t\tout_addr[Cb] = 0x%x\n", (UINT32)S_IM_R2Y_OUT_MNG[loopcnt3][loopcnt2].bank_info.outputAddr[loopcnt].ycc.addrCb ));
			Ddim_Print(( "\t\t\tout_addr[Cr] = 0x%x\n", (UINT32)S_IM_R2Y_OUT_MNG[loopcnt3][loopcnt2].bank_info.outputAddr[loopcnt].ycc.addrCr ));
		}
}

/* R2Y Initialize
 */
INT32 Im_r2y_init(ImR2y *self, kuint16 pipeNo )
{
	kuint16 loop_cnt, loop_sta, loop_end;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile R2yStateMng* gImR2yState = im_r2y_utils_get_state_mng(imR2yUtils);
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "Im_r2y_init error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	imR2yReset( pipeNo );
	Im_R2Y_Dsb();

	// Initalize of Managemnet information & Reset of Internal buffer
	imR2yManagerInit( pipeNo );

	imR2yCalcRingPixs( pipeNo );

	im_r2y_utils_get_loop_val(imR2yUtils, pipeNo, &loop_sta, &loop_end );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		gImR2yState[loop_cnt].topOffset[ImR2yCtrl_PORT_0] = 0;
		gImR2yState[loop_cnt].topOffset[ImR2yCtrl_PORT_1] = 0;
		gImR2yState[loop_cnt].topOffset[ImR2yCtrl_PORT_2] = 0;
		gImR2yState[loop_cnt].wasStarted = D_IM_R2Y_FALSE;
	}

#ifdef CO_DEBUG_ON_PC
	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		gImIoR2yRegPtr[loop_cnt]->F_R2Y.CNTL.CNTL.bit.TRG = ImR2y_FR2YTRG_IDLE;
		gImIoR2yRegPtr[loop_cnt]->YYR.YYRTRG.bit.YYRTRG   = ImR2yCtrl_YYRTRG_IDLE;
		gImIoR2yRegPtr[loop_cnt]->YYW.YYWTRG.bit.YYWTRG   = D_IM_R2Y_YYWTRG_IDLE;
	}
#endif

	return D_DDIM_OK;
}

/* set AXI bus I/F Control
 */
INT32 im_r2y_ctrl_axi(ImR2y *self, kuint16 pipeNo, const TImR2yCtrlAxi* const r2yCtrlAxi )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);
#ifdef CO_PARAM_CHECK
	if( r2yCtrlAxi == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("im_r2y_ctrl_axi error. r2yCtrlAxi = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl_axi error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );

	gImIoR2yRegPtr[pipeNo]->YYCH.YYRAXCTL.bit.YYRCACHE_0 = r2yCtrlAxi->yyr[ImR2yCtrl_PORT_0].cacheType;
	gImIoR2yRegPtr[pipeNo]->YYCH.YYRAXCTL.bit.YYRPROT_0  = r2yCtrlAxi->yyr[ImR2yCtrl_PORT_0].protectType;
	gImIoR2yRegPtr[pipeNo]->YYCH.YYRAXCTL.bit.YYRCACHE_1 = r2yCtrlAxi->yyr[ImR2yCtrl_PORT_1].cacheType;
	gImIoR2yRegPtr[pipeNo]->YYCH.YYRAXCTL.bit.YYRPROT_1  = r2yCtrlAxi->yyr[ImR2yCtrl_PORT_1].protectType;
	gImIoR2yRegPtr[pipeNo]->YYCH.YYRAXCTL.bit.YYRCACHE_2 = r2yCtrlAxi->yyr[ImR2yCtrl_PORT_2].cacheType;
	gImIoR2yRegPtr[pipeNo]->YYCH.YYRAXCTL.bit.YYRPROT_2  = r2yCtrlAxi->yyr[ImR2yCtrl_PORT_2].protectType;

	gImIoR2yRegPtr[pipeNo]->YYCH.YYW0AXCTL.bit.YYW0CACHE_0 = r2yCtrlAxi->yyw[ImR2yCtrl_YYW_CH_0][ImR2yCtrl_PORT_0].cacheType;
	gImIoR2yRegPtr[pipeNo]->YYCH.YYW0AXCTL.bit.YYW0PROT_0  = r2yCtrlAxi->yyw[ImR2yCtrl_YYW_CH_0][ImR2yCtrl_PORT_0].protectType;
	gImIoR2yRegPtr[pipeNo]->YYCH.YYW0AXCTL.bit.YYW0CACHE_1 = r2yCtrlAxi->yyw[ImR2yCtrl_YYW_CH_0][ImR2yCtrl_PORT_1].cacheType;
	gImIoR2yRegPtr[pipeNo]->YYCH.YYW0AXCTL.bit.YYW0PROT_1  = r2yCtrlAxi->yyw[ImR2yCtrl_YYW_CH_0][ImR2yCtrl_PORT_1].protectType;
	gImIoR2yRegPtr[pipeNo]->YYCH.YYW0AXCTL.bit.YYW0CACHE_2 = r2yCtrlAxi->yyw[ImR2yCtrl_YYW_CH_0][ImR2yCtrl_PORT_2].cacheType;
	gImIoR2yRegPtr[pipeNo]->YYCH.YYW0AXCTL.bit.YYW0PROT_2  = r2yCtrlAxi->yyw[ImR2yCtrl_YYW_CH_0][ImR2yCtrl_PORT_2].protectType;

	gImIoR2yRegPtr[pipeNo]->YYCH.YYWAAXCTL.bit.YYWACACHE_0 = r2yCtrlAxi->yyw[ImR2yCtrl_YYW_CH_0A][ImR2yCtrl_PORT_0].cacheType;
	gImIoR2yRegPtr[pipeNo]->YYCH.YYWAAXCTL.bit.YYWAPROT_0  = r2yCtrlAxi->yyw[ImR2yCtrl_YYW_CH_0A][ImR2yCtrl_PORT_0].protectType;
	gImIoR2yRegPtr[pipeNo]->YYCH.YYWAAXCTL.bit.YYWACACHE_1 = r2yCtrlAxi->yyw[ImR2yCtrl_YYW_CH_0A][ImR2yCtrl_PORT_1].cacheType;
	gImIoR2yRegPtr[pipeNo]->YYCH.YYWAAXCTL.bit.YYWAPROT_1  = r2yCtrlAxi->yyw[ImR2yCtrl_YYW_CH_0A][ImR2yCtrl_PORT_1].protectType;

	gImIoR2yRegPtr[pipeNo]->YYCH.YYW1AXCTL.bit.YYW1CACHE_0 = r2yCtrlAxi->yyw[ImR2yCtrl_YYW_CH_1][ImR2yCtrl_PORT_0].cacheType;
	gImIoR2yRegPtr[pipeNo]->YYCH.YYW1AXCTL.bit.YYW1PROT_0  = r2yCtrlAxi->yyw[ImR2yCtrl_YYW_CH_1][ImR2yCtrl_PORT_0].protectType;
	gImIoR2yRegPtr[pipeNo]->YYCH.YYW1AXCTL.bit.YYW1CACHE_1 = r2yCtrlAxi->yyw[ImR2yCtrl_YYW_CH_1][ImR2yCtrl_PORT_1].cacheType;
	gImIoR2yRegPtr[pipeNo]->YYCH.YYW1AXCTL.bit.YYW1PROT_1  = r2yCtrlAxi->yyw[ImR2yCtrl_YYW_CH_1][ImR2yCtrl_PORT_1].protectType;
	gImIoR2yRegPtr[pipeNo]->YYCH.YYW1AXCTL.bit.YYW1CACHE_2 = r2yCtrlAxi->yyw[ImR2yCtrl_YYW_CH_1][ImR2yCtrl_PORT_2].cacheType;
	gImIoR2yRegPtr[pipeNo]->YYCH.YYW1AXCTL.bit.YYW1PROT_2  = r2yCtrlAxi->yyw[ImR2yCtrl_YYW_CH_1][ImR2yCtrl_PORT_2].protectType;

	gImIoR2yRegPtr[pipeNo]->YYCH.YYW2AXCTL.bit.YYW2CACHE = r2yCtrlAxi->yyw[ImR2yCtrl_YYW_CH_2][ImR2yCtrl_PORT_0].cacheType;
	gImIoR2yRegPtr[pipeNo]->YYCH.YYW2AXCTL.bit.YYW2PROT  = r2yCtrlAxi->yyw[ImR2yCtrl_YYW_CH_2][ImR2yCtrl_PORT_0].protectType;

	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );

	Im_R2Y_Dsb();

	return D_DDIM_OK;
}

/* get AXI bus read channel status
 */
INT32 im_r2y_get_axi_read_stat(ImR2y *self, kuint16 pipeNo, AxiYyrStat* const r2yAxiReadStat )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2yAxiReadStat == NULL ) {
		Ddim_Assertion(("im_r2y_get_axi_read_stat error. r2yAxiReadStat = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo >= ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_get_axi_read_stat error. pipeNo>=ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	r2yAxiReadStat->yyrAxiStat[ImR2yCtrl_PORT_0] = gImIoR2yRegPtr[pipeNo]->YYCH.YYRAXSTS.bit.YYRRESP_0;
	r2yAxiReadStat->yyrAxiStat[ImR2yCtrl_PORT_1] = gImIoR2yRegPtr[pipeNo]->YYCH.YYRAXSTS.bit.YYRRESP_1;
	r2yAxiReadStat->yyrAxiStat[ImR2yCtrl_PORT_2] = gImIoR2yRegPtr[pipeNo]->YYCH.YYRAXSTS.bit.YYRRESP_2;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );

	return D_DDIM_OK;
}

/* get AXI bus write channel status
 */
INT32 im_r2y_get_axi_write_stat(ImR2y *self, kuint16 pipeNo, AxiYywStat* const r2yAxiWriteStat )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2yAxiWriteStat == NULL ) {
		Ddim_Assertion(("im_r2y_get_axi_write_stat error. r2yAxiWriteStat = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo >= ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_get_axi_write_stat error. pipeNo>=ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	r2yAxiWriteStat->yyw0AxiStat[ImR2yCtrl_PORT_0] = gImIoR2yRegPtr[pipeNo]->YYCH.YYW0AXSTS.bit.YY0BRESP_0;
	r2yAxiWriteStat->yyw0AxiStat[ImR2yCtrl_PORT_1] = gImIoR2yRegPtr[pipeNo]->YYCH.YYW0AXSTS.bit.YY0BRESP_1;
	r2yAxiWriteStat->yyw0AxiStat[ImR2yCtrl_PORT_2] = gImIoR2yRegPtr[pipeNo]->YYCH.YYW0AXSTS.bit.YY0BRESP_2;

	r2yAxiWriteStat->yyw0aAxiStat[ImR2yCtrl_PORT_0] = gImIoR2yRegPtr[pipeNo]->YYCH.YYWAAXSTS.bit.YYABRESP_0;
	r2yAxiWriteStat->yyw0aAxiStat[ImR2yCtrl_PORT_1] = gImIoR2yRegPtr[pipeNo]->YYCH.YYWAAXSTS.bit.YYABRESP_1;

	r2yAxiWriteStat->yyw1AxiStat[ImR2yCtrl_PORT_0] = gImIoR2yRegPtr[pipeNo]->YYCH.YYW1AXSTS.bit.YY1BRESP_0;
	r2yAxiWriteStat->yyw1AxiStat[ImR2yCtrl_PORT_1] = gImIoR2yRegPtr[pipeNo]->YYCH.YYW1AXSTS.bit.YY1BRESP_1;
	r2yAxiWriteStat->yyw1AxiStat[ImR2yCtrl_PORT_2] = gImIoR2yRegPtr[pipeNo]->YYCH.YYW1AXSTS.bit.YY1BRESP_2;

	r2yAxiWriteStat->yyw2AxiStat = gImIoR2yRegPtr[pipeNo]->YYCH.YYW2AXSTS.bit.YY2BRESP;

	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );

	return D_DDIM_OK;
}

/* get AXI bus write channel Transfer mode
 */
INT32 im_r2y_get_axi_write_mode(ImR2y *self, kuint16 pipeNo, kuint16 yywNo, AxiYywMode* const r2yAxiWriteMode )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2yAxiWriteMode == NULL ){
		Ddim_Assertion(("im_r2y_get_axi_write_mode error. r2yAxiWriteMode = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo >= ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_get_axi_write_mode error. pipeNo>=ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	r2yAxiWriteMode->outEnable[ImR2yCtrl_PORT_0] = ImR2yCtrl_ENABLE_OFF;
	r2yAxiWriteMode->outEnable[ImR2yCtrl_PORT_1] = ImR2yCtrl_ENABLE_OFF;
	r2yAxiWriteMode->outEnable[ImR2yCtrl_PORT_2] = ImR2yCtrl_ENABLE_OFF;

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );

	switch( yywNo ){
		case ImR2yCtrl_YYW_CH_1:
			r2yAxiWriteMode->masterIfSelect = gImIoR2yRegPtr[pipeNo]->YYCH.YYW1AXMD.bit.YYW1MSL;
			if((gImIoR2yRegPtr[pipeNo]->YYCH.YYW1AXMD.bit.YYW1DOE & 1) != 0){
				r2yAxiWriteMode->outEnable[ImR2yCtrl_PORT_0] = ImR2yCtrl_ENABLE_ON;
			}
			if((gImIoR2yRegPtr[pipeNo]->YYCH.YYW1AXMD.bit.YYW1DOE & 2) != 0){
				r2yAxiWriteMode->outEnable[ImR2yCtrl_PORT_1] = ImR2yCtrl_ENABLE_ON;
			}
			if((gImIoR2yRegPtr[pipeNo]->YYCH.YYW1AXMD.bit.YYW1DOE & 4) != 0){
				r2yAxiWriteMode->outEnable[ImR2yCtrl_PORT_2] = ImR2yCtrl_ENABLE_ON;
			}
			r2yAxiWriteMode->burstLength = gImIoR2yRegPtr[pipeNo]->YYCH.YYW1AXMD.bit.YYW1BL;
			break;
		case ImR2yCtrl_YYW_CH_2:
			r2yAxiWriteMode->masterIfSelect = gImIoR2yRegPtr[pipeNo]->YYCH.YYW2AXMD.bit.YYW2MSL;
			r2yAxiWriteMode->burstLength = gImIoR2yRegPtr[pipeNo]->YYCH.YYW2AXMD.bit.YYW2BL;
			break;
		case ImR2yCtrl_YYW_CH_0A:
			r2yAxiWriteMode->masterIfSelect = gImIoR2yRegPtr[pipeNo]->YYCH.YYWAAXMD.bit.YYWAMSL;
			if((gImIoR2yRegPtr[pipeNo]->YYCH.YYWAAXMD.bit.YYWADOE & 1) != 0){
				r2yAxiWriteMode->outEnable[ImR2yCtrl_PORT_0] = ImR2yCtrl_ENABLE_ON;
			}
			if((gImIoR2yRegPtr[pipeNo]->YYCH.YYWAAXMD.bit.YYWADOE & 2) != 0){
				r2yAxiWriteMode->outEnable[ImR2yCtrl_PORT_1] = ImR2yCtrl_ENABLE_ON;
			}
			r2yAxiWriteMode->burstLength = gImIoR2yRegPtr[pipeNo]->YYCH.YYWAAXMD.bit.YYWABL;
			break;
//		case ImR2yCtrl_YYW_CH_0:
		default:
			r2yAxiWriteMode->masterIfSelect = gImIoR2yRegPtr[pipeNo]->YYCH.YYW0AXMD.bit.YYW0MSL;
			if((gImIoR2yRegPtr[pipeNo]->YYCH.YYW0AXMD.bit.YYW0DOE & 1) != 0){
				r2yAxiWriteMode->outEnable[ImR2yCtrl_PORT_0] = ImR2yCtrl_ENABLE_ON;
			}
			if((gImIoR2yRegPtr[pipeNo]->YYCH.YYW0AXMD.bit.YYW0DOE & 2) != 0){
				r2yAxiWriteMode->outEnable[ImR2yCtrl_PORT_1] = ImR2yCtrl_ENABLE_ON;
			}
			if((gImIoR2yRegPtr[pipeNo]->YYCH.YYW0AXMD.bit.YYW0DOE & 4) != 0){
				r2yAxiWriteMode->outEnable[ImR2yCtrl_PORT_2] = ImR2yCtrl_ENABLE_ON;
			}
			r2yAxiWriteMode->burstLength = gImIoR2yRegPtr[pipeNo]->YYCH.YYW0AXMD.bit.YYW0BL;
			break;
	}

	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );

	return D_DDIM_OK;
}

/* set AXI bus write channel Transfer mode
 */
INT32 im_r2y_set_axi_write_mode(ImR2y *self, kuint16 pipeNo, kuint16 yywNo, const AxiYywMode* const r2yAxiWriteMode )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2yAxiWriteMode == NULL ){
		Ddim_Assertion(("im_r2y_set_axi_write_mode error. r2yAxiWriteMode = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_set_axi_write_mode error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	switch( yywNo ){
		case ImR2yCtrl_YYW_CH_1:
			gImIoR2yRegPtr[pipeNo]->YYCH.YYW1AXMD.bit.YYW1MSL = r2yAxiWriteMode->masterIfSelect;
			gImIoR2yRegPtr[pipeNo]->YYCH.YYW1AXMD.bit.YYW1DOE = (kulong)(
																	 ((r2yAxiWriteMode->outEnable[ImR2yCtrl_PORT_0] != ImR2yCtrl_ENABLE_ON) ? (0) : (1)) |
																	 ((r2yAxiWriteMode->outEnable[ImR2yCtrl_PORT_1] != ImR2yCtrl_ENABLE_ON) ? (0) : (2)) |
																	 ((r2yAxiWriteMode->outEnable[ImR2yCtrl_PORT_2] != ImR2yCtrl_ENABLE_ON) ? (0) : (4))
																	 );
			gImIoR2yRegPtr[pipeNo]->YYCH.YYW1AXMD.bit.YYW1BL  = r2yAxiWriteMode->burstLength;
			break;
		case ImR2yCtrl_YYW_CH_2:
			gImIoR2yRegPtr[pipeNo]->YYCH.YYW2AXMD.bit.YYW2MSL = r2yAxiWriteMode->masterIfSelect;
			gImIoR2yRegPtr[pipeNo]->YYCH.YYW2AXMD.bit.YYW2BL  = r2yAxiWriteMode->burstLength;
			break;
		case ImR2yCtrl_YYW_CH_0A:
			gImIoR2yRegPtr[pipeNo]->YYCH.YYWAAXMD.bit.YYWAMSL = r2yAxiWriteMode->masterIfSelect;
			gImIoR2yRegPtr[pipeNo]->YYCH.YYWAAXMD.bit.YYWADOE = (kulong)(
																	 ((r2yAxiWriteMode->outEnable[ImR2yCtrl_PORT_0] != ImR2yCtrl_ENABLE_ON) ? (0) : (1)) |
																	 ((r2yAxiWriteMode->outEnable[ImR2yCtrl_PORT_1] != ImR2yCtrl_ENABLE_ON) ? (0) : (2))
																	 );
			gImIoR2yRegPtr[pipeNo]->YYCH.YYWAAXMD.bit.YYWABL  = r2yAxiWriteMode->burstLength;
			break;
//		case ImR2yCtrl_YYW_CH_0:
		default:
			gImIoR2yRegPtr[pipeNo]->YYCH.YYW0AXMD.bit.YYW0MSL = r2yAxiWriteMode->masterIfSelect;
			gImIoR2yRegPtr[pipeNo]->YYCH.YYW0AXMD.bit.YYW0DOE = (kulong)(
																	 ((r2yAxiWriteMode->outEnable[ImR2yCtrl_PORT_0] != ImR2yCtrl_ENABLE_ON) ? (0) : (1)) |
																	 ((r2yAxiWriteMode->outEnable[ImR2yCtrl_PORT_1] != ImR2yCtrl_ENABLE_ON) ? (0) : (2)) |
																	 ((r2yAxiWriteMode->outEnable[ImR2yCtrl_PORT_2] != ImR2yCtrl_ENABLE_ON) ? (0) : (4))
																	 );
			gImIoR2yRegPtr[pipeNo]->YYCH.YYW0AXMD.bit.YYW0BL  = r2yAxiWriteMode->burstLength;
			break;
	}

	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );

	return D_DDIM_OK;
}

/* R2Y Control (each mode common control)
 */
INT32 im_r2y_ctrl(ImR2y *self, kuint16 pipeNo, const TImR2yCtrl* const r2yCtrl )
{
	kuint16 yywNo;
	kuint16 loop_cnt, loop_sta, loop_end;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile R2yStateMng* gImR2yState = im_r2y_utils_get_state_mng(imR2yUtils);
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2yCtrl == NULL ) {
		Ddim_Assertion(("im_r2y_ctrl error. r2yCtrl = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_utils_get_loop_val(imR2yUtils, pipeNo, &loop_sta, &loop_end );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		gImR2yState[loop_cnt].yywEnable[ImR2yCtrl_YYW_CH_0]          = r2yCtrl->yywEnable[ImR2yCtrl_YYW_CH_0];
		gImR2yState[loop_cnt].yywEnable[ImR2yCtrl_YYW_CH_1]          = r2yCtrl->yywEnable[ImR2yCtrl_YYW_CH_1];
		gImR2yState[loop_cnt].yywEnable[ImR2yCtrl_YYW_CH_2]          = r2yCtrl->yywEnable[ImR2yCtrl_YYW_CH_2];
		gImR2yState[loop_cnt].ycfBypass                             = r2yCtrl->ycfBypass;
		gImR2yState[loop_cnt].ycfPadding                            = r2yCtrl->ycfPadding;
		gImR2yState[loop_cnt].mccSelect                             = r2yCtrl->mccSelect;
		gImR2yState[loop_cnt].mccBitShift                          = r2yCtrl->mccBitShift;
		gImR2yState[loop_cnt].r2yUserHandler                       = r2yCtrl->r2yUserHandler;
		gImR2yState[loop_cnt].userParam                             = r2yCtrl->userParam;
		gImR2yState[loop_cnt].pixAvgReductMode[ImR2yCtrl_YYW_CH_0] = r2yCtrl->yyw[ImR2yCtrl_YYW_CH_0].pixelAvgReductionMode;
		gImR2yState[loop_cnt].pixAvgReductMode[ImR2yCtrl_YYW_CH_1] = r2yCtrl->yyw[ImR2yCtrl_YYW_CH_1].pixelAvgReductionMode;
		gImR2yState[loop_cnt].pixAvgReductMode[ImR2yCtrl_YYW_CH_2] = r2yCtrl->yyw[ImR2yCtrl_YYW_CH_2].pixelAvgReductionMode;
		gImR2yState[loop_cnt].pixAvgReductEn[ImR2yCtrl_YYW_CH_0]   = r2yCtrl->yyw[ImR2yCtrl_YYW_CH_0].pixelAvgReductionEnable;
		gImR2yState[loop_cnt].pixAvgReductEn[ImR2yCtrl_YYW_CH_1]   = r2yCtrl->yyw[ImR2yCtrl_YYW_CH_1].pixelAvgReductionEnable;
		gImR2yState[loop_cnt].pixAvgReductEn[ImR2yCtrl_YYW_CH_2]   = r2yCtrl->yyw[ImR2yCtrl_YYW_CH_2].pixelAvgReductionEnable;
		gImR2yState[loop_cnt].outputMode0a                         = r2yCtrl->outputMode0a;
		if( r2yCtrl->yywEnable[ImR2yCtrl_YYW_CH_0] == ImR2yCtrl_ENABLE_ON ) {
			gImR2yState[loop_cnt].resizeMode[ImR2yCtrl_YYW_CH_0]     = r2yCtrl->yyw[ImR2yCtrl_YYW_CH_0].resizeMode;
		}
		if( r2yCtrl->yywEnable[ImR2yCtrl_YYW_CH_1] == ImR2yCtrl_ENABLE_ON ) {
			gImR2yState[loop_cnt].resizeMode[ImR2yCtrl_YYW_CH_1]     = r2yCtrl->yyw[ImR2yCtrl_YYW_CH_1].resizeMode;
		}
	}

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );

	// YYCH

	// R2Y_CMN
	gImIoR2yRegPtr[pipeNo]->R2Y_CMN.LINTLV.bit.LINTLV_0 = r2yCtrl->lineIntr[ImR2yCtrl_LINE_INT_0].level;
	gImIoR2yRegPtr[pipeNo]->R2Y_CMN.LINTLV.bit.LINTLV_1 = r2yCtrl->lineIntr[ImR2yCtrl_LINE_INT_1].level;
	gImIoR2yRegPtr[pipeNo]->R2Y_CMN.LINTLV.bit.LINTLV_2 = r2yCtrl->lineIntr[ImR2yCtrl_LINE_INT_2].level;
	gImIoR2yRegPtr[pipeNo]->R2Y_CMN.LINTSEL.bit.LINTS_0 = r2yCtrl->lineIntr[ImR2yCtrl_LINE_INT_0].yywSelect;
	gImIoR2yRegPtr[pipeNo]->R2Y_CMN.LINTSEL.bit.LINTS_1 = r2yCtrl->lineIntr[ImR2yCtrl_LINE_INT_1].yywSelect;
	gImIoR2yRegPtr[pipeNo]->R2Y_CMN.LINTSEL.bit.LINTS_2 = r2yCtrl->lineIntr[ImR2yCtrl_LINE_INT_2].yywSelect;
	gImIoR2yRegPtr[pipeNo]->R2Y_CMN.R2YMODE.bit.YCFBYP  = r2yCtrl->ycfBypass;
	gImIoR2yRegPtr[pipeNo]->R2Y_CMN.R2YMODE.bit.YCFPDD  = r2yCtrl->ycfPadding;
	gImIoR2yRegPtr[pipeNo]->R2Y_CMN.R2YMODE.bit.MCCSL   = r2yCtrl->mccSelect;
	gImIoR2yRegPtr[pipeNo]->R2Y_CMN.R2YMODE.bit.MCC1BM  = r2yCtrl->mccBitShift;

	// YYW
	gImIoR2yRegPtr[pipeNo]->YYW.YYW0LTT.bit.YYW0LTT = r2yCtrl->lineTransferCycle;
	gImIoR2yRegPtr[pipeNo]->YYW.YYWCTL.bit.YYWCSE   = r2yCtrl->yywContinueStartEnable;
	gImIoR2yRegPtr[pipeNo]->YYW.YYWCTL.bit.YYWHRV   = r2yCtrl->yywHorizontalFlip;

	// setting YYW0/1/2 indivisually
	gImIoR2yRegPtr[pipeNo]->YYW.YYWCTL.bit.YYWMODE = (kulong)(
														  ((r2yCtrl->yywEnable[ImR2yCtrl_YYW_CH_0] != ImR2yCtrl_ENABLE_OFF)?(1):(0)) |
														  ((r2yCtrl->yywEnable[ImR2yCtrl_YYW_CH_1] != ImR2yCtrl_ENABLE_OFF)?(2):(0)) |
														  ((r2yCtrl->yywEnable[ImR2yCtrl_YYW_CH_2] != ImR2yCtrl_ENABLE_OFF)?(4):(0))
														  );

	// YYW0/0A
	if( r2yCtrl->yywEnable[ImR2yCtrl_YYW_CH_0] == ImR2yCtrl_ENABLE_ON ) {
		yywNo = ImR2yCtrl_YYW_CH_0;

		gImIoR2yRegPtr[pipeNo]->YYCH.YYW0AXMD.bit.YYW0MSL        = r2yCtrl->yyw[ yywNo ].axiWriteMode.masterIfSelect;
		gImIoR2yRegPtr[pipeNo]->YYCH.YYW0AXMD.bit.YYW0DOE        = (kulong)(
																		((r2yCtrl->yyw[yywNo].axiWriteMode.outEnable[ImR2yCtrl_PORT_0] != ImR2yCtrl_ENABLE_ON)?(0):(1)) |
																		((r2yCtrl->yyw[yywNo].axiWriteMode.outEnable[ImR2yCtrl_PORT_1] != ImR2yCtrl_ENABLE_ON)?(0):(2)) |
																		((r2yCtrl->yyw[yywNo].axiWriteMode.outEnable[ImR2yCtrl_PORT_2] != ImR2yCtrl_ENABLE_ON)?(0):(4))
																		);
		gImIoR2yRegPtr[pipeNo]->YYCH.YYW0AXMD.bit.YYW0BL         = r2yCtrl->yyw[ yywNo ].axiWriteMode.burstLength;
		gImIoR2yRegPtr[pipeNo]->YYCH.YYW0REQMSK.bit.YYW0REQMSK_0 = r2yCtrl->yyw[ yywNo ].writeRequestMask[ImR2yCtrl_PORT_0];
		gImIoR2yRegPtr[pipeNo]->YYCH.YYW0REQMSK.bit.YYW0REQMSK_1 = r2yCtrl->yyw[ yywNo ].writeRequestMask[ImR2yCtrl_PORT_1];
		gImIoR2yRegPtr[pipeNo]->YYCH.YYW0REQMSK.bit.YYW0REQMSK_2 = r2yCtrl->yyw[ yywNo ].writeRequestMask[ImR2yCtrl_PORT_2];
		gImIoR2yRegPtr[pipeNo]->YYW.YYW0MD.bit.RSZ0MD            = r2yCtrl->yyw[ yywNo ].resizeMode;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW0MD.bit.RDC0MD            = r2yCtrl->yyw[ yywNo ].pixelAvgReductionMode;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW0MD.bit.RDC0EN            = r2yCtrl->yyw[ yywNo ].pixelAvgReductionEnable;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW0MD.bit.CSS0SL            = r2yCtrl->yyw[ yywNo ].yccCcThinSelect;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW0MD.bit.TRM0EN            = r2yCtrl->yyw[ yywNo ].trimOutEnable;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW0MD.bit.SPL0EN            = r2yCtrl->yyw[ yywNo ].planarInterleavedMode;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW0MD.bit.CH0VFM            = r2yCtrl->videoFormatOutSelect0;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW0MD.bit.EXTBEN            = r2yCtrl->ipuMacroOutputEnable;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW0MD.bit.TRMBEN            = r2yCtrl->ipuMacroTrimmingEnable;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW0MD.bit.EXTCEN            = r2yCtrl->cnrMacroOutputEnable;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW0MD.bit.TRMCEN            = r2yCtrl->cnrMacroTrimmingEnable;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW0MD.bit.CH0AMD            = r2yCtrl->outputMode0a;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW0MD.bit.CHAVFM            = r2yCtrl->videoFormatOutSelect0a;

		yywNo = ImR2yCtrl_YYW_CH_0A;

		gImIoR2yRegPtr[pipeNo]->YYCH.YYWAAXMD.bit.YYWAMSL        = r2yCtrl->yyw[ yywNo ].axiWriteMode.masterIfSelect;
		gImIoR2yRegPtr[pipeNo]->YYCH.YYWAAXMD.bit.YYWADOE        = (kulong)(
																		((r2yCtrl->yyw[yywNo].axiWriteMode.outEnable[ImR2yCtrl_PORT_0] != ImR2yCtrl_ENABLE_ON)?(0):(1)) |
																		((r2yCtrl->yyw[yywNo].axiWriteMode.outEnable[ImR2yCtrl_PORT_1] != ImR2yCtrl_ENABLE_ON)?(0):(2))
																		);
		gImIoR2yRegPtr[pipeNo]->YYCH.YYWAAXMD.bit.YYWABL         = r2yCtrl->yyw[ yywNo ].axiWriteMode.burstLength;
		gImIoR2yRegPtr[pipeNo]->YYCH.YYWAREQMSK.bit.YYWAREQMSK_0 = r2yCtrl->yyw[ yywNo ].writeRequestMask[ImR2yCtrl_PORT_0];
		gImIoR2yRegPtr[pipeNo]->YYCH.YYWAREQMSK.bit.YYWAREQMSK_1 = r2yCtrl->yyw[ yywNo ].writeRequestMask[ImR2yCtrl_PORT_1];
	}

	// YYW1
	if( r2yCtrl->yywEnable[ImR2yCtrl_YYW_CH_1] == ImR2yCtrl_ENABLE_ON ) {
		yywNo = ImR2yCtrl_YYW_CH_1;

		gImIoR2yRegPtr[pipeNo]->YYCH.YYW1AXMD.bit.YYW1MSL        = r2yCtrl->yyw[ yywNo ].axiWriteMode.masterIfSelect;
		gImIoR2yRegPtr[pipeNo]->YYCH.YYW1AXMD.bit.YYW1DOE        = (kulong)(
																		((r2yCtrl->yyw[yywNo].axiWriteMode.outEnable[ImR2yCtrl_PORT_0] != ImR2yCtrl_ENABLE_ON)?(0):(1)) |
																		((r2yCtrl->yyw[yywNo].axiWriteMode.outEnable[ImR2yCtrl_PORT_1] != ImR2yCtrl_ENABLE_ON)?(0):(2)) |
																		((r2yCtrl->yyw[yywNo].axiWriteMode.outEnable[ImR2yCtrl_PORT_2] != ImR2yCtrl_ENABLE_ON)?(0):(4))
																		);
		gImIoR2yRegPtr[pipeNo]->YYCH.YYW1AXMD.bit.YYW1BL         = r2yCtrl->yyw[ yywNo ].axiWriteMode.burstLength;
		gImIoR2yRegPtr[pipeNo]->YYCH.YYW1REQMSK.bit.YYW1REQMSK_0 = r2yCtrl->yyw[ yywNo ].writeRequestMask[ImR2yCtrl_PORT_0];
		gImIoR2yRegPtr[pipeNo]->YYCH.YYW1REQMSK.bit.YYW1REQMSK_1 = r2yCtrl->yyw[ yywNo ].writeRequestMask[ImR2yCtrl_PORT_1];
		gImIoR2yRegPtr[pipeNo]->YYCH.YYW1REQMSK.bit.YYW1REQMSK_2 = r2yCtrl->yyw[ yywNo ].writeRequestMask[ImR2yCtrl_PORT_2];
		gImIoR2yRegPtr[pipeNo]->YYW.YYW1MD.bit.RSZ1MD            = r2yCtrl->yyw[ yywNo ].resizeMode;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW1MD.bit.RDC1MD            = r2yCtrl->yyw[ yywNo ].pixelAvgReductionMode;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW1MD.bit.RDC1EN            = r2yCtrl->yyw[ yywNo ].pixelAvgReductionEnable;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW1MD.bit.CSS1SL            = r2yCtrl->yyw[ yywNo ].yccCcThinSelect;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW1MD.bit.TRM1EN            = r2yCtrl->yyw[ yywNo ].trimOutEnable;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW1MD.bit.SPL1EN            = r2yCtrl->yyw[ yywNo ].planarInterleavedMode;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW1MD.bit.DFM1SL            = r2yCtrl->outputFormatSel1;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW1MD.bit.DTY1SL            = r2yCtrl->outputTypeSel1;
	}

	// YYW2
	if( r2yCtrl->yywEnable[ImR2yCtrl_YYW_CH_2] == ImR2yCtrl_ENABLE_ON ) {
		yywNo = ImR2yCtrl_YYW_CH_2;

		gImIoR2yRegPtr[pipeNo]->YYCH.YYW2AXMD.bit.YYW2MSL      = r2yCtrl->yyw[ yywNo ].axiWriteMode.masterIfSelect;
		gImIoR2yRegPtr[pipeNo]->YYCH.YYW2AXMD.bit.YYW2BL       = r2yCtrl->yyw[ yywNo ].axiWriteMode.burstLength;
		gImIoR2yRegPtr[pipeNo]->YYCH.YYW2REQMSK.bit.YYW2REQMSK = r2yCtrl->yyw[ yywNo ].writeRequestMask[ImR2yCtrl_PORT_0];
		gImIoR2yRegPtr[pipeNo]->YYW.YYW2MD.bit.RDC2MD          = r2yCtrl->yyw[ yywNo ].pixelAvgReductionMode;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW2MD.bit.RDC2EN          = r2yCtrl->yyw[ yywNo ].pixelAvgReductionEnable;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW2MD.bit.TRM2EN          = r2yCtrl->yyw[ yywNo ].trimOutEnable;
	}

	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );

	imR2yCalcRingPixs( pipeNo );

	Im_R2Y_Dsb();

	return D_DDIM_OK;
}

/* R2Y Control (SDRAM input mode control)
 */
INT32 im_r2y_ctrl_mode_sdram_input(ImR2y *self, kuint16 pipeNo, const CtrlSdramInput* const r2yCtrlSdramInput )
{
	kuint16 loop_cnt, loop_sta, loop_end;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile R2yStateMng* gImR2yState = im_r2y_utils_get_state_mng(imR2yUtils);
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2yCtrlSdramInput == NULL ) {
		Ddim_Assertion(("im_r2y_ctrl_mode_sdram_input error. r2yCtrlSdramInput = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl_mode_sdram_input error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_utils_get_loop_val(imR2yUtils, pipeNo, &loop_sta, &loop_end );

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		if(ImR2yCtrl_YYR_IS_ACTIVATED( loop_cnt )){
#ifdef CO_DEBUG_PRINT_IM_R2Y
			Ddim_Print(( "im_r2y_ctrl_mode_sdram_input error. YYR busy\n" ));
#endif
			im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
			return ImR2yUtils_MACRO_BUSY;
		}
	}

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		gImR2yState[loop_cnt].inputDtype                 = r2yCtrlSdramInput->inputDtype;
		gImR2yState[loop_cnt].topOffset[ImR2yCtrl_PORT_0] = r2yCtrlSdramInput->topOffset[ImR2yCtrl_PORT_0];
		gImR2yState[loop_cnt].topOffset[ImR2yCtrl_PORT_1] = r2yCtrlSdramInput->topOffset[ImR2yCtrl_PORT_1];
		gImR2yState[loop_cnt].topOffset[ImR2yCtrl_PORT_2] = r2yCtrlSdramInput->topOffset[ImR2yCtrl_PORT_2];
		gImR2yState[loop_cnt].inputGlobal                = r2yCtrlSdramInput->inputGlobal;
		gImR2yState[loop_cnt].videoPhotoMode            = ImR2yUtils_MODE_SDRAM_INPUT;
	}

	// YYCH
	gImIoR2yRegPtr[pipeNo]->YYCH.YYRAXMD.bit.YYRBL         = r2yCtrlSdramInput->burstLength;
	gImIoR2yRegPtr[pipeNo]->YYCH.YYRREQMSK.bit.YYRREQMSK_0 = r2yCtrlSdramInput->readRequestMask[ImR2yCtrl_PORT_0];
	gImIoR2yRegPtr[pipeNo]->YYCH.YYRREQMSK.bit.YYRREQMSK_1 = r2yCtrlSdramInput->readRequestMask[ImR2yCtrl_PORT_1];
	gImIoR2yRegPtr[pipeNo]->YYCH.YYRREQMSK.bit.YYRREQMSK_2 = r2yCtrlSdramInput->readRequestMask[ImR2yCtrl_PORT_2];

	// YYR
	gImIoR2yRegPtr[pipeNo]->YYR.DINCTL.bit.B2RDIN  = ImR2yUtils_MODE_SDRAM_INPUT;
	gImIoR2yRegPtr[pipeNo]->YYR.YYRCTL.bit.YYRDTYP = r2yCtrlSdramInput->inputDtype;
	gImIoR2yRegPtr[pipeNo]->YYR.YYRCTL.bit.MONOEN  = r2yCtrlSdramInput->monoEbable;
	gImIoR2yRegPtr[pipeNo]->YYR.YYRCTL.bit.DKNEN   = r2yCtrlSdramInput->rgbDekneeEnable;
	gImIoR2yRegPtr[pipeNo]->YYR.YYRCTL.bit.RGBLSFT = r2yCtrlSdramInput->rgbLeftShift;
	gImIoR2yRegPtr[pipeNo]->YYR.YYRCTL.bit.RGBLSM  = r2yCtrlSdramInput->rgbSaturationMode;
	gImIoR2yRegPtr[pipeNo]->YYR.YYRDEF.bit.YYRDEF  = r2yCtrlSdramInput->inputGlobal;

	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
	Im_R2Y_Dsb();

	return D_DDIM_OK;
}

/* Set Managed Input Address information
 */
INT32 im_r2y_set_inaddr_info(ImR2y *self, kuint16 pipeNo, const R2yInaddrInfo* const inAddr )
{
	kuint16 loop_cnt, loop_sta, loop_end;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile R2yStateMng* gImR2yState = im_r2y_utils_get_state_mng(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( inAddr == NULL ) {
		Ddim_Assertion(("im_r2y_set_inaddr_info error. inAddr = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_set_inaddr_info error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_utils_get_loop_val(imR2yUtils, pipeNo, &loop_sta, &loop_end );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		gImR2yState[loop_cnt].inAddr[ImR2yCtrl_PORT_R] = (kulong)inAddr->rgb.addrR;
		gImR2yState[loop_cnt].inAddr[ImR2yCtrl_PORT_G] = (kulong)inAddr->rgb.addrG;
		gImR2yState[loop_cnt].inAddr[ImR2yCtrl_PORT_B] = (kulong)inAddr->rgb.addrB;
		imR2ySetYyrAddressSdramInput( loop_cnt );
	}

	return D_DDIM_OK;
}

/* Set Managed bank information
 */
INT32 im_r2y_set_out_bank_info(ImR2y *self, kuint16 pipeNo, kuint16 yywNo, const R2yOutbankInfo* const r2yBank )
{
	INT32 ercd;
	kuint16 loop_cnt, loop_sta, loop_end;
	kuint16 index;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2yBank == NULL ) {
		Ddim_Assertion(("im_r2y_set_out_bank_info error. r2yBank = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( yywNo >= ImR2yCtrl_YYW_CH_MAX ) {
		Ddim_Assertion(("im_r2y_set_out_bank_info error. yywNo >= MAX\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_set_out_bank_info error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_utils_get_loop_val(imR2yUtils, pipeNo, &loop_sta, &loop_end );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		S_IM_R2Y_OUT_MNG[loop_cnt][yywNo].bank_info = *r2yBank;
	}

	if( pipeNo == ImR2yCtrl_PIPE12 ){
		index = 0;
	}
	else{
		index = pipeNo;
	}

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	// YYW0A
	if( yywNo == ImR2yCtrl_YYW_CH_0 ) {
		gImIoR2yRegPtr[pipeNo]->YYW.YYWCTL.bit.USEBANK0 = S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.useBankNum;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW0A.bit.YYW0A_0_0 = (kulong)S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.outputAddr[ImR2yCtrl_YYW_BANK_0].ycc.addrY;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW0A.bit.YYW0A_1_0 = (kulong)S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.outputAddr[ImR2yCtrl_YYW_BANK_0].ycc.addrCb;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW0A.bit.YYW0A_2_0 = (kulong)S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.outputAddr[ImR2yCtrl_YYW_BANK_0].ycc.addrCr;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW0A.bit.YYW0A_0_1 = (kulong)S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.outputAddr[ImR2yCtrl_YYW_BANK_1].ycc.addrY;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW0A.bit.YYW0A_1_1 = (kulong)S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.outputAddr[ImR2yCtrl_YYW_BANK_1].ycc.addrCb;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW0A.bit.YYW0A_2_1 = (kulong)S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.outputAddr[ImR2yCtrl_YYW_BANK_1].ycc.addrCr;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW0A.bit.YYW0A_0_2 = (kulong)S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.outputAddr[ImR2yCtrl_YYW_BANK_2].ycc.addrY;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW0A.bit.YYW0A_1_2 = (kulong)S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.outputAddr[ImR2yCtrl_YYW_BANK_2].ycc.addrCb;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW0A.bit.YYW0A_2_2 = (kulong)S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.outputAddr[ImR2yCtrl_YYW_BANK_2].ycc.addrCr;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW0A.bit.YYW0A_0_3 = (kulong)S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.outputAddr[ImR2yCtrl_YYW_BANK_3].ycc.addrY;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW0A.bit.YYW0A_1_3 = (kulong)S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.outputAddr[ImR2yCtrl_YYW_BANK_3].ycc.addrCb;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW0A.bit.YYW0A_2_3 = (kulong)S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.outputAddr[ImR2yCtrl_YYW_BANK_3].ycc.addrCr;
	}
	// YYW1A
	else if( yywNo == ImR2yCtrl_YYW_CH_1 ){
		gImIoR2yRegPtr[pipeNo]->YYW.YYWCTL.bit.USEBANK1 = S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.useBankNum;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW1A.bit.YYW1A_0_0 = (kulong)S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.outputAddr[ImR2yCtrl_YYW_BANK_0].ycc.addrY;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW1A.bit.YYW1A_1_0 = (kulong)S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.outputAddr[ImR2yCtrl_YYW_BANK_0].ycc.addrCb;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW1A.bit.YYW1A_2_0 = (kulong)S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.outputAddr[ImR2yCtrl_YYW_BANK_0].ycc.addrCr;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW1A.bit.YYW1A_0_1 = (kulong)S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.outputAddr[ImR2yCtrl_YYW_BANK_1].ycc.addrY;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW1A.bit.YYW1A_1_1 = (kulong)S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.outputAddr[ImR2yCtrl_YYW_BANK_1].ycc.addrCb;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW1A.bit.YYW1A_2_1 = (kulong)S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.outputAddr[ImR2yCtrl_YYW_BANK_1].ycc.addrCr;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW1A.bit.YYW1A_0_2 = (kulong)S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.outputAddr[ImR2yCtrl_YYW_BANK_2].ycc.addrY;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW1A.bit.YYW1A_1_2 = (kulong)S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.outputAddr[ImR2yCtrl_YYW_BANK_2].ycc.addrCb;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW1A.bit.YYW1A_2_2 = (kulong)S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.outputAddr[ImR2yCtrl_YYW_BANK_2].ycc.addrCr;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW1A.bit.YYW1A_0_3 = (kulong)S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.outputAddr[ImR2yCtrl_YYW_BANK_3].ycc.addrY;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW1A.bit.YYW1A_1_3 = (kulong)S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.outputAddr[ImR2yCtrl_YYW_BANK_3].ycc.addrCb;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW1A.bit.YYW1A_2_3 = (kulong)S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.outputAddr[ImR2yCtrl_YYW_BANK_3].ycc.addrCr;
	}
	// YYW2A
	else if( yywNo == ImR2yCtrl_YYW_CH_2 ){
		gImIoR2yRegPtr[pipeNo]->YYW.YYWCTL.bit.USEBANK2 = S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.useBankNum;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW2A.bit.YYW2A_0 = (kulong)S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.outputAddr[ImR2yCtrl_YYW_BANK_0].ycc.addrY;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW2A.bit.YYW2A_1 = (kulong)S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.outputAddr[ImR2yCtrl_YYW_BANK_1].ycc.addrY;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW2A.bit.YYW2A_2 = (kulong)S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.outputAddr[ImR2yCtrl_YYW_BANK_2].ycc.addrY;
		gImIoR2yRegPtr[pipeNo]->YYW.YYW2A.bit.YYW2A_3 = (kulong)S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.outputAddr[ImR2yCtrl_YYW_BANK_3].ycc.addrY;
	}
	// YYWAA
	else{
		gImIoR2yRegPtr[pipeNo]->YYW.YYWCTL.bit.USEBANKA = S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.useBankNum;
		gImIoR2yRegPtr[pipeNo]->YYW.YYWAA.bit.YYWAA_0_0 = (kulong)S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.outputAddr[ImR2yCtrl_YYW_BANK_0].ycc.addrY;
		gImIoR2yRegPtr[pipeNo]->YYW.YYWAA.bit.YYWAA_1_0 = (kulong)S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.outputAddr[ImR2yCtrl_YYW_BANK_0].ycc.addrCb;
		gImIoR2yRegPtr[pipeNo]->YYW.YYWAA.bit.YYWAA_0_1 = (kulong)S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.outputAddr[ImR2yCtrl_YYW_BANK_1].ycc.addrY;
		gImIoR2yRegPtr[pipeNo]->YYW.YYWAA.bit.YYWAA_1_1 = (kulong)S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.outputAddr[ImR2yCtrl_YYW_BANK_1].ycc.addrCb;
		gImIoR2yRegPtr[pipeNo]->YYW.YYWAA.bit.YYWAA_0_2 = (kulong)S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.outputAddr[ImR2yCtrl_YYW_BANK_2].ycc.addrY;
		gImIoR2yRegPtr[pipeNo]->YYW.YYWAA.bit.YYWAA_1_2 = (kulong)S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.outputAddr[ImR2yCtrl_YYW_BANK_2].ycc.addrCb;
		gImIoR2yRegPtr[pipeNo]->YYW.YYWAA.bit.YYWAA_0_3 = (kulong)S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.outputAddr[ImR2yCtrl_YYW_BANK_3].ycc.addrY;
		gImIoR2yRegPtr[pipeNo]->YYW.YYWAA.bit.YYWAA_1_3 = (kulong)S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.outputAddr[ImR2yCtrl_YYW_BANK_3].ycc.addrCb;
	}
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );

	// Set bank index & top address information
	ercd = im_r2y3_set_outbank_index(im_r2y3_new(), pipeNo, yywNo, S_IM_R2Y_OUT_MNG[index][yywNo].bank_info.bankInitialPosition );
	if( ercd != D_DDIM_OK ) {
		return ercd;
	}

	return D_DDIM_OK;
}

/* Get bank index value
 */
INT32 im_r2y_get_out_bank_index(ImR2y *self, kuint16 pipeNo, kuint16 yywNo, kuint16* const bankIndex )
{
#ifdef CO_PARAM_CHECK
	if( bankIndex == NULL ) {
		Ddim_Assertion(("im_r2y_get_out_bank_index error. bankIndex = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( yywNo >= ImR2yCtrl_YYW_CH_MAX ) {
		Ddim_Assertion(("im_r2y_get_out_bank_index error. yywNo >= MAX\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo >= ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_get_out_bank_index error. pipeNo>=ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*bankIndex = S_IM_R2Y_OUT_MNG[pipeNo][yywNo].latest_idx;

	return D_DDIM_OK;
}

ImR2y *im_r2y_new(void)
{
	ImR2y* self = k_object_new_with_private(IM_TYPE_R2Y,sizeof(ImR2yPrivate));
	return self;
}
