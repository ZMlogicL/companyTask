/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-07
*@author              :李昕
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

#include "imcnrinit.h"
#include "imcnr.h"
#include "imcnrset.h"
#include "imcnrget.h"
#include "imcnrcspr.h"
#include "imcnraxi.h"
#include "driver_common.h"
// #if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
// #endif
#include "dd_arm.h"
#include "ddim_user_custom.h"
#include "jdscnr.h"
// for memset
#include <string.h>

K_TYPE_DEFINE_WITH_PRIVATE(ImCnrInit, im_cnr_init);
#define IM_CNR_INIT_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImCnrInitPrivate, IM_TYPE_CNR_INIT))

struct _ImCnrInitPrivate
{
	int a;
};

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
static volatile TImCnrCallback	S_G_IM_CNR_OFL_CALLBACK_FUNC[ImCnr_D_IM_CNR_CH_READ_NUM_MAX] = {NULL, NULL};
static volatile TImCnrCallback	S_G_IM_CNR_OTF_CALLBACK_FUNC[ImCnr_D_IM_CNR_CH_READ_NUM_MAX] = {NULL, NULL};
static volatile UINT32 S_G_IM_CNR_OFL_USERPARAM[ImCnr_D_IM_CNR_CH_READ_NUM_MAX] = {0, 0};
static volatile UINT32 S_G_IM_CNR_OTF_USERPARAM[ImCnr_D_IM_CNR_CH_READ_NUM_MAX] = {0, 0};
// Output address parameter
static volatile TImCnrOutputMng S_G_IM_CNR_OUTPUT_MNG[ImCnr_D_IM_CNR_CH_READ_NUM_MAX];
// Output address parameter
static volatile TImCnrLatestMng S_G_IM_CNR_LATEST_MNG[ImCnr_D_IM_CNR_CH_READ_NUM_MAX];

/*----------------------------------------------------------------------*/
/* Local Method Definition												*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
static VOID imCnrOflSetSpde( const UCHAR ch, const UCHAR onoff );
static VOID imCnrOtfSetSpde( const UCHAR ch, const UCHAR onoff );
static VOID imCnrOflClearAxif( UCHAR ch );
static VOID imCnrOtfClearAxif( UCHAR ch );
static VOID imCnrOflClearSpdf( UCHAR ch );
static VOID imCnrOtfClearSpdf( UCHAR ch );

static void im_cnr_init_constructor(ImCnrInit *self)
{
}

static void im_cnr_init_destructor(ImCnrInit *self)
{
}

/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/
// Interrupt Enable/Disable control
static VOID imCnrOflSetSpde( const UCHAR ch, const UCHAR onoff )
{
	union io_cnr_ofl_reg_rw_sprice spric;

	spric.word = 0;
	spric.bit.SPDE = onoff;
	spric.bit.AXIE = onoff;

	ImCnr_IO_CNR(ch)->OFL_REG_RW.SPRICE.word = spric.word;
#ifdef CO_DEBUG_ON_PC
	if( ch == ImCnr_D_IM_CNR_CH_2 ){
		ImCnr_IO_CNR(ImCnr_D_IM_CNR_CH_0)->OFL_REG_RW.SPRICE.word = spric.word;
		ImCnr_IO_CNR(ImCnr_D_IM_CNR_CH_1)->OFL_REG_RW.SPRICE.word = spric.word;
	}
#endif	// CO_DEBUG_ON_PC
}

static VOID imCnrOtfSetSpde( const UCHAR ch, const UCHAR onoff )
{
	union io_cnr_otf_reg_rw_sprice spric;

	spric.word = 0;
	spric.bit.SPDE = onoff;
	spric.bit.AXIE = onoff;
	spric.bit.DRTE = onoff;

	ImCnr_IO_CNR(ch)->OTF_REG_RW.SPRICE.word = spric.word;
#ifdef CO_DEBUG_ON_PC
	if( ch == ImCnr_D_IM_CNR_CH_2 ){
		ImCnr_IO_CNR(ImCnr_D_IM_CNR_CH_0)->OTF_REG_RW.SPRICE.word = spric.word;
		ImCnr_IO_CNR(ImCnr_D_IM_CNR_CH_1)->OTF_REG_RW.SPRICE.word = spric.word;
	}
#endif	// CO_DEBUG_ON_PC
}

// AXIF Interrupt flag clear
static VOID imCnrOflClearAxif( UCHAR ch )
{
#ifdef CO_DEBUG_ON_PC
	ImCnr_IO_CNR(ch)->OFL_REG_RW.SPRICF.bit.__AXIF = 0;
	if( ch == ImCnr_D_IM_CNR_CH_2 ){
		ImCnr_IO_CNR(ImCnr_D_IM_CNR_CH_0)->OFL_REG_RW.SPRICF.bit.__AXIF = 0;
		ImCnr_IO_CNR(ImCnr_D_IM_CNR_CH_1)->OFL_REG_RW.SPRICF.bit.__AXIF = 0;
	}
#else //!CO_DEBUG_ON_PC
	union io_cnr_ofl_reg_rw_spricf spricf;

	spricf.word = 0;
	spricf.bit.__AXIF = 1;

	ImCnr_IO_CNR(ch)->OFL_REG_RW.SPRICF.word = spricf.word;
#endif //!CO_DEBUG_ON_PC
}

// AXIF Interrupt flag clear
static VOID imCnrOtfClearAxif( UCHAR ch )
{
#ifdef CO_DEBUG_ON_PC
	ImCnr_IO_CNR(ch)->OTF_REG_RW.SPRICF.bit.__AXIF = 0;
	if( ch == ImCnr_D_IM_CNR_CH_2 ){
		ImCnr_IO_CNR(ImCnr_D_IM_CNR_CH_0)->OTF_REG_RW.SPRICF.bit.__AXIF = 0;
		ImCnr_IO_CNR(ImCnr_D_IM_CNR_CH_1)->OTF_REG_RW.SPRICF.bit.__AXIF = 0;
	}
#else //!CO_DEBUG_ON_PC
	union io_cnr_otf_reg_rw_spricf spricf;

	spricf.word = 0;
	spricf.bit.__AXIF = 1;

	ImCnr_IO_CNR(ch)->OTF_REG_RW.SPRICF.word = spricf.word;
#endif //!CO_DEBUG_ON_PC
}

// DRTF Interrupt flag clear
static VOID im_cnr_otf_clear_drtf( UCHAR ch )
{
#ifdef CO_DEBUG_ON_PC
	ImCnr_IO_CNR(ch)->OTF_REG_RW.SPRICF.bit.__DRTF = 0;
	if( ch == ImCnr_D_IM_CNR_CH_2 ){
		ImCnr_IO_CNR(ImCnr_D_IM_CNR_CH_0)->OTF_REG_RW.SPRICF.bit.__DRTF = 0;
		ImCnr_IO_CNR(ImCnr_D_IM_CNR_CH_1)->OTF_REG_RW.SPRICF.bit.__DRTF = 0;
	}
#else //!CO_DEBUG_ON_PC
	union io_cnr_otf_reg_rw_spricf spricf;

	spricf.word = 0;
	spricf.bit.__DRTF = 1;

	ImCnr_IO_CNR(ch)->OTF_REG_RW.SPRICF.word = spricf.word;
#endif //!CO_DEBUG_ON_PC
}

// SPDF Interrupt flag clear
static VOID imCnrOflClearSpdf( UCHAR ch )
{
#ifdef CO_DEBUG_ON_PC
	ImCnr_IO_CNR(ch)->OFL_REG_RW.SPRICF.bit.__SPDF = 0;
	if( ch == ImCnr_D_IM_CNR_CH_2 ){
		ImCnr_IO_CNR(ImCnr_D_IM_CNR_CH_0)->OFL_REG_RW.SPRICF.bit.__SPDF = 0;
		ImCnr_IO_CNR(ImCnr_D_IM_CNR_CH_1)->OFL_REG_RW.SPRICF.bit.__SPDF = 0;
	}
#else //!CO_DEBUG_ON_PC
	union io_cnr_ofl_reg_rw_spricf spricf;

	spricf.word = 0;
	spricf.bit.__SPDF = 1;

	ImCnr_IO_CNR(ch)->OFL_REG_RW.SPRICF.word = spricf.word;
#endif //!CO_DEBUG_ON_PC
}

// SPDF Interrupt flag clear
static VOID imCnrOtfClearSpdf( UCHAR ch )
{
#ifdef CO_DEBUG_ON_PC
	ImCnr_IO_CNR(ch)->OTF_REG_RW.SPRICF.bit.__SPDF = 0;
	if( ch == ImCnr_D_IM_CNR_CH_2 ){
		ImCnr_IO_CNR(ImCnr_D_IM_CNR_CH_0)->OTF_REG_RW.SPRICF.bit.__SPDF = 0;
		ImCnr_IO_CNR(ImCnr_D_IM_CNR_CH_1)->OTF_REG_RW.SPRICF.bit.__SPDF = 0;
	}
#else //!CO_DEBUG_ON_PC
	union io_cnr_otf_reg_rw_spricf spricf;

	spricf.word = 0;
	spricf.bit.__SPDF = 1;

	ImCnr_IO_CNR(ch)->OTF_REG_RW.SPRICF.word = spricf.word;
#endif //!CO_DEBUG_ON_PC
}

/*----------------------------------------------------------------------*/
/* Global Function														*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
/*
CNR(OTF) Macro handler
*/
VOID im_cnr_init_otf_int_handler(ImCnrInit*self, UCHAR ch )
{
	DDIM_USER_FLGPTN flg;
	union io_cnr_otf_reg_rw_sprice sprice;
	union io_cnr_otf_reg_rw_spricf spricf;

	im_cnr_on_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	sprice.word = ImCnr_IO_CNR(ch)->OTF_REG_RW.SPRICE.word;
	spricf.word = ImCnr_IO_CNR(ch)->OTF_REG_RW.SPRICF.word;

	if( (sprice.bit.AXIE != 0) && (spricf.bit.__AXIF != 0) ) {		/* pgr0872 */
		// clear interrupt end register
		imCnrOtfClearAxif(ch);

		// Set End Flag
		if (ch == ImCnr_D_IM_CNR_CH_0) {
			flg = ImCnr_D_IM_CNR_FLG_0_OTF_SPR_AXI_ERR;

			DDIM_User_Set_Flg( FID_IM_CNR, ImCnr_D_IM_CNR_FLG_0_OTF_SPR_AXI_ERR );
		}
		else {
			flg = ImCnr_D_IM_CNR_FLG_1_OTF_SPR_AXI_ERR;

			DDIM_User_Set_Flg( FID_IM_CNR, ImCnr_D_IM_CNR_FLG_1_OTF_SPR_AXI_ERR );
		}

		// User Function Check
		if( S_G_IM_CNR_OTF_CALLBACK_FUNC[ch] != NULL ) {
			S_G_IM_CNR_OTF_CALLBACK_FUNC[ch]( ch, flg, S_G_IM_CNR_OTF_USERPARAM[ch] );
		}
	}

	if( (sprice.bit.DRTE != 0) && (spricf.bit.__DRTF != 0) ) {		/* pgr0872 */
		// clear interrupt end register
		im_cnr_otf_clear_drtf(ch);

		// Set End Flag
		if (ch == ImCnr_D_IM_CNR_CH_0) {
			flg = ImCnr_D_IM_CNR_FLG_0_OTF_SPR_DRT_ERR;

			DDIM_User_Set_Flg( FID_IM_CNR, ImCnr_D_IM_CNR_FLG_0_OTF_SPR_DRT_ERR );
		}
		else {
			flg = ImCnr_D_IM_CNR_FLG_1_OTF_SPR_DRT_ERR;

			DDIM_User_Set_Flg( FID_IM_CNR, ImCnr_D_IM_CNR_FLG_1_OTF_SPR_DRT_ERR );
		}

		// User Function Check
		if( S_G_IM_CNR_OTF_CALLBACK_FUNC[ch] != NULL ) {
			S_G_IM_CNR_OTF_CALLBACK_FUNC[ch]( ch, flg, S_G_IM_CNR_OTF_USERPARAM[ch] );
		}
	}

	if( (sprice.bit.SPDE != 0) && (spricf.bit.__SPDF != 0) ) {		/* pgr0872 */
		// clear interrupt end register
		imCnrOtfClearSpdf(ch);

//		im_cnr_off_spr_clk(im_cnr_new(),ch);

		// Update latest address
		S_G_IM_CNR_LATEST_MNG[ch].addr	= S_G_IM_CNR_OUTPUT_MNG[ch].outputAddr[S_G_IM_CNR_LATEST_MNG[ch].bankArea];
		// Update output address
		++S_G_IM_CNR_LATEST_MNG[ch].bankArea;
		S_G_IM_CNR_LATEST_MNG[ch].bankArea	= ImCnrInit_ADDR_BNK_LIMIT( S_G_IM_CNR_LATEST_MNG[ch].bankArea, S_G_IM_CNR_OUTPUT_MNG[ch].useBankNum );

		if (ch == ImCnr_D_IM_CNR_CH_0) {
			flg = ImCnr_D_IM_CNR_FLG_0_OTF_SPR_END;
		}
		else{	// ImCnr_D_IM_CNR_CH_1
			flg = ImCnr_D_IM_CNR_FLG_1_OTF_SPR_END;
		}

		// Set End Flag
		(VOID)DDIM_User_Set_Flg( FID_IM_CNR, flg );

		// User Function Check
		if( S_G_IM_CNR_OTF_CALLBACK_FUNC[ch] != NULL ) {
			S_G_IM_CNR_OTF_CALLBACK_FUNC[ch]( ch, flg, S_G_IM_CNR_OTF_USERPARAM[ch] );
		}
	}

	im_cnr_off_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();
}

/*
CNR(OFL) Macro handler
*/
VOID im_cnr_init_ofl_int_handler(ImCnrInit*self, UCHAR ch )
{
	DDIM_USER_FLGPTN flg;
	union io_cnr_ofl_reg_rw_sprice sprice;
	union io_cnr_ofl_reg_rw_spricf spricf;

	im_cnr_on_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	sprice.word = ImCnr_IO_CNR(ch)->OFL_REG_RW.SPRICE.word;
	spricf.word = ImCnr_IO_CNR(ch)->OFL_REG_RW.SPRICF.word;

	if( (sprice.bit.AXIE != 0) && (spricf.bit.__AXIF != 0) ) {		/* pgr0872 */
		// clear interrupt end register
		imCnrOflClearAxif(ch);

		// Set End Flag
		if (ch == ImCnr_D_IM_CNR_CH_0) {
			flg = ImCnr_D_IM_CNR_FLG_0_OFL_SPR_AXI_ERR;

			DDIM_User_Set_Flg( FID_IM_CNR, ImCnr_D_IM_CNR_FLG_0_OFL_SPR_AXI_ERR );
		}
		else {
			flg = ImCnr_D_IM_CNR_FLG_1_OFL_SPR_AXI_ERR;

			DDIM_User_Set_Flg( FID_IM_CNR, ImCnr_D_IM_CNR_FLG_1_OFL_SPR_AXI_ERR );
		}

		// User Function Check
		if( S_G_IM_CNR_OFL_CALLBACK_FUNC[ch] != NULL ) {
			S_G_IM_CNR_OFL_CALLBACK_FUNC[ch]( ch, flg, S_G_IM_CNR_OFL_USERPARAM[ch] );
		}
	}

	if( (sprice.bit.SPDE != 0) && (spricf.bit.__SPDF != 0) ) {		/* pgr0872 */
		// clear interrupt end register
		imCnrOflClearSpdf(ch);

		im_cnr_off_spr_clk(im_cnr_new(),ch);

		if (ch == ImCnr_D_IM_CNR_CH_0) {
			flg = ImCnr_D_IM_CNR_FLG_0_OFL_SPR_END;
		}
		else {	// ImCnr_D_IM_CNR_CH_1
			flg = ImCnr_D_IM_CNR_FLG_1_OFL_SPR_END;
		}

		// Set End Flag
		(VOID)DDIM_User_Set_Flg( FID_IM_CNR, flg );

		// User Function Check
		if( S_G_IM_CNR_OFL_CALLBACK_FUNC[ch] != NULL ) {
			S_G_IM_CNR_OFL_CALLBACK_FUNC[ch]( ch, flg, S_G_IM_CNR_OFL_USERPARAM[ch] );
		}
	}

	im_cnr_off_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();
}

/*
Set software reset and operating mode for Off Line
*/
INT32 im_cnr_init_ofl_init(ImCnrInit*self, UCHAR ch )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_init_ofl_init() error. input channel error : %d\n", ch));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	im_cnr_on_spr_clk(im_cnr_new(),ch);
	im_cnr_on_pclk(im_cnr_new(),ch);

	if (ch == ImCnr_D_IM_CNR_CH_0) {
		ImCnr_IO_CNR(ch)->OFL_REG_RW.SPRSR.bit.SR = 1;	// Software reset assert

		ImCnr_IM_CNR_DSB();

		// CNRCLK        = MAX 252.0MHz		MIN 31.5MHz
		// APB clock     = MAX  66.7MHz		MIN 20.8MHz
		// -->   ( (1/CNRCLK) / (1/APB clock) ) * 2 + 1
		//     = ( (1/31.5)   / (1/66.7)        ) * 2 + 1
		//     = 5.23 => 6 APB cycle

		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		ImCnr_IM_CNR_DSB();

		ImCnr_IO_CNR(ch)->OFL_REG_RW.SPRSR.bit.SR = 0;	// Software reset de-assert

		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		ImCnr_IM_CNR_DSB();
	}
	else if (ch == ImCnr_D_IM_CNR_CH_1) {
		ImCnr_IO_CNR(ch)->OFL_REG_RW.SPRSR.bit.SR = 1;	// Software reset assert

		ImCnr_IM_CNR_DSB();

		// CNRCLK        = MAX 252.0MHz		MIN 31.5MHz
		// APB clock     = MAX  66.7MHz		MIN 20.8MHz
		// -->   ( (1/CNRCLK) / (1/APB clock) ) * 2 + 1
		//     = ( (1/31.5)   / (1/66.7)        ) * 2 + 1
		//     = 5.23 => 6 APB cycle

		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		ImCnr_IM_CNR_DSB();

		ImCnr_IO_CNR(ch)->OFL_REG_RW.SPRSR.bit.SR = 0;	// Software reset de-assert

		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		ImCnr_IM_CNR_DSB();
	}
	else {
		ImCnr_IO_CNR(ch)->OFL_REG_RW.SPRSR.bit.SR = 1;	// Software reset assert

		ImCnr_IM_CNR_DSB();

		// CNRCLK        = MAX 252.0MHz		MIN 31.5MHz
		// APB clock     = MAX  66.7MHz		MIN 20.8MHz
		// -->   ( (1/CNRCLK) / (1/APB clock) ) * 2 + 1
		//     = ( (1/31.5)   / (1/66.7)        ) * 2 + 1
		//     = 5.23 => 6 APB cycle

		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		ImCnr_IM_CNR_DSB();

		ImCnr_IO_CNR(ch)->OFL_REG_RW.SPRSR.bit.SR = 0;	// Software reset de-assert

		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		ImCnr_IM_CNR_DSB();
	}

	imCnrOflClearSpdf(ch);	// Interrupt clear
	imCnrOflClearAxif(ch);	// Interrupt clear
	imCnrOflSetSpde( ch, 1 );

	im_cnr_off_pclk(im_cnr_new(),ch);
	im_cnr_off_spr_clk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	return D_DDIM_OK;
}

/*
CNR(OFL) Control
*/
INT32 im_cnr_init_ofl_ctrl(ImCnrInit*self, UCHAR ch, const TImCnrOflCtrl* const spr_ctrl )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_init_ofl_ctrl() error. input channel error : %d\n", ch));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_ctrl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_init_ofl_ctrl() Parameter is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnr_on_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	// Read Setting
	//      |---RYDEF---|       |---RCDEF---|       |---RCDEF---|
	//  RYTA|-HSIZE-|   |  RCBTA|-HSIZE-|   |  RCRTA|-HSIZE-|   |
	// -----+-------+---+  -----+-------+---+  -----+-------+---+
	//   |  |       | | |    |  |       | | |    |  |       | | |
	//   V  |       | d |    V  |       | d |    V  |       | d |
	//   S  |Y data | u |    S  |CB data| u |    S  |CR data| u |
	//   I  |valid  | m |    I  |valid  | m |    I  |valid  | m |
	//   Z  |area   | m |    Z  |area   | m |    Z  |area   | m |
	//   E  |       | y |    E  |       | y |    E  |       | y |
	//   |  |       | | |    |  |       | | |    |  |       | | |
	// -----+-------+---+  -----+-------+---+  -----+-------+---+

	// Write Setting
	//      |---WYDEF---|       |---WCDEF---|       |---WCDEF---|
	//  WYTA|-HSIZE-|   |  WCBTA|-HSIZE-|   |  WCRTA|-HSIZE-|   |
	// -----+-------+---+  -----+-------+---+  -----+-------+---+
	//   |  |       | | |    |  |       | | |    |  |       | | |
	//   V  |       | d |    V  |       | d |    V  |       | d |
	//   S  |Y data | u |    S  |CB data| u |    S  |CR data| u |
	//   I  |valid  | m |    I  |valid  | m |    I  |valid  | m |
	//   Z  |area   | m |    Z  |area   | m |    Z  |area   | m |
	//   E  |       | y |    E  |       | y |    E  |       | y |
	//   |  |       | | |    |  |       | | |    |  |       | | |
	// -----+-------+---+  -----+-------+---+  -----+-------+---+

	ImCnr_IO_CNR(ch)->OFL_REG_RW.SPRMOD.bit.YUV_MODE	= spr_ctrl->mode;	// SPR YCC mode		@YUV_MODE

	ImCnr_IO_CNR(ch)->OFL_REG_RW.HSIZE.bit.HSIZE	= spr_ctrl->width;		// SPR valid data width		@HSIZE
	ImCnr_IO_CNR(ch)->OFL_REG_RW.VSIZE.bit.VSIZE	= spr_ctrl->lines;		// SPR valid data lines		@VSIZE

	ImCnr_IO_CNR(ch)->OFL_REG_RW.RYDEF.bit.RYDEF	= spr_ctrl->rYWidth;	// Y width for read			@RYDEF
	ImCnr_IO_CNR(ch)->OFL_REG_RW.RYTA.bit.RYTA	= spr_ctrl->rYAddr;	// Y address for read		@RYTA

	ImCnr_IO_CNR(ch)->OFL_REG_RW.RCDEF.bit.RCDEF	= spr_ctrl->rCWidth;	// CbCr width for read		@RCDEF
	ImCnr_IO_CNR(ch)->OFL_REG_RW.RCBTA.bit.RCBTA	= spr_ctrl->rCbAddr;	// Cb address for read		@RCBTA
	ImCnr_IO_CNR(ch)->OFL_REG_RW.RCRTA.bit.RCRTA	= spr_ctrl->rCrAddr;	// Cr address for read		@RCRTA

	ImCnr_IO_CNR(ch)->OFL_REG_RW.WYDEF.bit.WYDEF	= spr_ctrl->wYWidth;	// Y width for write		@WYDEF
	ImCnr_IO_CNR(ch)->OFL_REG_RW.WYTA.bit.WYTA	= spr_ctrl->wYAddr;	// Y address for write		@WYTA

	ImCnr_IO_CNR(ch)->OFL_REG_RW.WCDEF.bit.WCDEF	= spr_ctrl->wCWidth;	// CbCr width for write		@WCDEF
	ImCnr_IO_CNR(ch)->OFL_REG_RW.WCBTA.bit.WCBTA	= spr_ctrl->wCbAddr;	// Cb address for write		@WCBTA
	ImCnr_IO_CNR(ch)->OFL_REG_RW.WCRTA.bit.WCRTA	= spr_ctrl->wCrAddr;	// Cr address for write		@WCRTA

	ImCnr_IO_CNR(ch)->OFL_REG_RW.TMPTA.bit.TMPTA	= spr_ctrl->workAddr;	// Address fir work area	@TMPTA

	ImCnr_IO_CNR(ch)->OFL_REG_RW.VDIV.bit.VDIVT	= spr_ctrl->divideTop;		// Virtucal process devide	@VDIVT
	ImCnr_IO_CNR(ch)->OFL_REG_RW.VDIV.bit.VDIVB	= spr_ctrl->divideBot;		// Virtucal process devide	@VDIVB

	if( ch == ImCnr_D_IM_CNR_CH_2 ){
		S_G_IM_CNR_OFL_CALLBACK_FUNC[ImCnr_D_IM_CNR_CH_0]	= spr_ctrl->pCallBack;
		S_G_IM_CNR_OFL_CALLBACK_FUNC[ImCnr_D_IM_CNR_CH_1]	= spr_ctrl->pCallBack;
		S_G_IM_CNR_OFL_USERPARAM[ImCnr_D_IM_CNR_CH_0]		= spr_ctrl->userParam;
		S_G_IM_CNR_OFL_USERPARAM[ImCnr_D_IM_CNR_CH_1]		= spr_ctrl->userParam;
	}
	else{
		S_G_IM_CNR_OFL_CALLBACK_FUNC[ch]	= spr_ctrl->pCallBack;
		S_G_IM_CNR_OFL_USERPARAM[ch]		= spr_ctrl->userParam;
	}

	im_cnr_off_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	return D_DDIM_OK;
}

/*
Set software reset and operating mode for Off Line
*/
INT32 im_cnr_init_otf_init(ImCnrInit*self, UCHAR ch )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_init_otf_init() error. input channel error : %d\n", ch));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	im_cnr_on_spr_clk(im_cnr_new(),ch);
	im_cnr_on_pclk(im_cnr_new(),ch);

	if (ch == ImCnr_D_IM_CNR_CH_0) {
		ImCnr_IO_CNR(ch)->OTF_REG_RW.SPRSR.bit.SR = 1;	// Software reset assert

		ImCnr_IM_CNR_DSB();

		// CNRCLK        = MAX 252.0MHz		MIN 31.5MHz
		// APB clock     = MAX  66.7MHz		MIN 20.8MHz
		// -->   ( (1/CNRCLK) / (1/APB clock) ) * 2 + 1
		//     = ( (1/31.5)   / (1/66.7)        ) * 2 + 1
		//     = 5.23 => 6 APB cycle

		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		ImCnr_IM_CNR_DSB();

		ImCnr_IO_CNR(ch)->OTF_REG_RW.SPRSR.bit.SR = 0;	// Software reset de-assert

		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		ImCnr_IM_CNR_DSB();
	}
	else if (ch == ImCnr_D_IM_CNR_CH_1) {
		ImCnr_IO_CNR(ch)->OTF_REG_RW.SPRSR.bit.SR = 1;	// Software reset assert

		ImCnr_IM_CNR_DSB();

		// CNRCLK        = MAX 252.0MHz		MIN 31.5MHz
		// APB clock     = MAX  66.7MHz		MIN 20.8MHz
		// -->   ( (1/CNRCLK) / (1/APB clock) ) * 2 + 1
		//     = ( (1/31.5)   / (1/66.7)        ) * 2 + 1
		//     = 5.23 => 6 APB cycle

		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		ImCnr_IM_CNR_DSB();

		ImCnr_IO_CNR(ch)->OTF_REG_RW.SPRSR.bit.SR = 0;	// Software reset de-assert

		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		ImCnr_IM_CNR_DSB();
	}
	else {
		ImCnr_IO_CNR(ch)->OTF_REG_RW.SPRSR.bit.SR = 1;	// Software reset assert

		ImCnr_IM_CNR_DSB();

		// CNRCLK        = MAX 252.0MHz		MIN 31.5MHz
		// APB clock     = MAX  66.7MHz		MIN 20.8MHz
		// -->   ( (1/CNRCLK) / (1/APB clock) ) * 2 + 1
		//     = ( (1/31.5)   / (1/66.7)        ) * 2 + 1
		//     = 5.23 => 6 APB cycle

		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		ImCnr_IM_CNR_DSB();

		ImCnr_IO_CNR(ch)->OTF_REG_RW.SPRSR.bit.SR = 0;	// Software reset de-assert

		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		ImCnr_IM_CNR_DSB();
	}

	imCnrOtfClearSpdf(ch);	// Interrupt clear
	imCnrOtfClearAxif(ch);	// Interrupt clear
	im_cnr_otf_clear_drtf(ch);	// Interrupt clear
	imCnrOtfSetSpde( ch, 1 );

	im_cnr_off_pclk(im_cnr_new(),ch);
	im_cnr_off_spr_clk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	// Initialize of Address management information
	if( ch == ImCnr_D_IM_CNR_CH_2 ){
		memset( (VOID*)&S_G_IM_CNR_OUTPUT_MNG[ImCnr_D_IM_CNR_CH_0], 0, sizeof(TImCnrOutputMng) * 2 );
		memset( (VOID*)&S_G_IM_CNR_LATEST_MNG[ImCnr_D_IM_CNR_CH_0], 0, sizeof(TImCnrLatestMng) * 2 );
	}
	else{
		memset( (VOID*)&S_G_IM_CNR_OUTPUT_MNG[ch], 0, sizeof(TImCnrOutputMng) );
		memset( (VOID*)&S_G_IM_CNR_LATEST_MNG[ch], 0, sizeof(TImCnrLatestMng) );
	}

	return D_DDIM_OK;
}

/*
CNR(OTF) Control
*/
INT32 im_cnr_init_otf_ctrl(ImCnrInit*self, UCHAR ch, const TImCnrOtfCtrl* const spr_ctrl )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_init_otf_ctrl() error. input channel error : %d\n", ch));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_ctrl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_init_otf_ctrl() Parameter is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif
	if (spr_ctrl->width < 96 || spr_ctrl->width > 2360) {
		Ddim_Assertion(("im_cnr_init_otf_ctrl() error. input width error : %d\n", spr_ctrl->width));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if (spr_ctrl->lines < 72 || spr_ctrl->lines > 4096) {
		Ddim_Assertion(("im_cnr_init_otf_ctrl() error. input lines error : %d\n", spr_ctrl->lines));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if ( (spr_ctrl->wOffsetX != 0)&&(spr_ctrl->wOffsetX < 96 || spr_ctrl->wOffsetX > 2360)) {
		Ddim_Assertion(("im_cnr_init_otf_ctrl() error. input wOffsetX error : %lu\n", spr_ctrl->wOffsetX));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if (spr_ctrl->videoFormat == 1){
		if (spr_ctrl->wCWidth % 128){
			Ddim_Assertion(("im_cnr_init_otf_ctrl() error. input wCWidth error : %lu\n", spr_ctrl->wCWidth));
			return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
		}
		if( spr_ctrl->mode != ImCnr_E_IM_CNR_OTF_YCC_MODE_YCC420_SIMPLE ){
			Ddim_Assertion(("im_cnr_init_otf_ctrl() error. mode error : %d\n", spr_ctrl->mode));
			return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
		}
	}

	im_cnr_on_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	// Write Setting
	//      |---WCDEF---|
	//  WCTA|-HSIZE-|   |
	// -----+-------+---+
	//   |  |       | | |
	//   V  |       | d |
	//   S  |C data | u |
	//   I  |valid  | m |
	//   Z  |area   | m |
	//   E  |       | y |
	//   |  |       | | |
	// -----+-------+---+

	ImCnr_IO_CNR(ch)->OTF_REG_RW.SPRMOD.bit.YUV_MODE		= spr_ctrl->mode;			// SPR YCC mode				@YUV_MODE
	ImCnr_IO_CNR(ch)->OTF_REG_RW.SPRMOD.bit.EXMODE		= spr_ctrl->extraMode;		// SPR extra mode			@EXMODE
	ImCnr_IO_CNR(ch)->OTF_REG_RW.SPRMOD.bit.CNRVFM		= spr_ctrl->videoFormat;	// SPR video format			@CNRVFM

	ImCnr_IO_CNR(ch)->OTF_REG_RW.HSIZE.bit.HSIZE			= spr_ctrl->width;			// SPR valid data width		@HSIZE
	ImCnr_IO_CNR(ch)->OTF_REG_RW.VSIZE.bit.VSIZE			= spr_ctrl->lines;			// SPR valid data lines		@VSIZE

	ImCnr_IO_CNR(ch)->OTF_REG_RW.WCDEF.bit.WCDEF			= spr_ctrl->wCWidth;		// CbCr width for write		@WCDEF

	ImCnr_IO_CNR(ch)->OTF_REG_RW.CNRWOFSX.bit.CNRWOFSX	= spr_ctrl->wOffsetX;		// write offset X direction	@CNRWOFSX

	ImCnr_IO_CNR(ch)->OTF_REG_RW.HDIV.bit.HDIVL			= spr_ctrl->divideLeft;	// Virtucal process devide	@HDIVL
	ImCnr_IO_CNR(ch)->OTF_REG_RW.HDIV.bit.HDIVR			= spr_ctrl->divideRight;	// Virtucal process devide	@VDIVR

	ImCnr_IO_CNR(ch)->OTF_REG_RW.SPRTRG.bit.CNRCSE		= spr_ctrl->continuous;		// Continuous processing	@CNRCSE

	if( ch == ImCnr_D_IM_CNR_CH_2 ){
		S_G_IM_CNR_OTF_CALLBACK_FUNC[ImCnr_D_IM_CNR_CH_0]	= spr_ctrl->pCallBack;
		S_G_IM_CNR_OTF_CALLBACK_FUNC[ImCnr_D_IM_CNR_CH_1]	= spr_ctrl->pCallBack;
		S_G_IM_CNR_OTF_USERPARAM[ImCnr_D_IM_CNR_CH_0]		= spr_ctrl->userParam;
		S_G_IM_CNR_OTF_USERPARAM[ImCnr_D_IM_CNR_CH_1]		= spr_ctrl->userParam;
	}
	else{
		S_G_IM_CNR_OTF_CALLBACK_FUNC[ch]				= spr_ctrl->pCallBack;
		S_G_IM_CNR_OTF_USERPARAM[ch]					= spr_ctrl->userParam;
	}

	im_cnr_off_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	return D_DDIM_OK;
}

/*
CNR(OTF) Set output address information
*/
INT32 im_cnr_init_otf_set_out_addr_info(ImCnrInit*self, UCHAR ch, const TImCnrOtfOutaddrInfo* const addr_info )
{
	INT32 out_addr_cnt;

#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_init_otf_set_out_addr_info() error. input channel error : %d\n", ch));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( addr_info == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_init_otf_set_out_addr_info() Parameter is NULL.\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( (addr_info->useBankNum == 0)||(addr_info->useBankNum > ImCnrInit_D_IM_CNR_ADDR_BANK_MAX) ){
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_init_otf_set_out_addr_info() useBankNum parameter is error : %d\n", addr_info->useBankNum));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnr_on_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	// Write Setting
	//      |---WCDEF---|
	//  WCTA|-HSIZE-|   |
	// -----+-------+---+
	//   |  |       | | |
	//   V  |       | d |
	//   S  |C data | u |
	//   I  |valid  | m |
	//   Z  |area   | m |
	//   E  |       | y |
	//   |  |       | | |
	// -----+-------+---+

	if( ch == ImCnr_D_IM_CNR_CH_2 ){
		// set output address information	@WCTA
		S_G_IM_CNR_LATEST_MNG[ImCnr_D_IM_CNR_CH_0].bankArea			= 0;	// reset
		S_G_IM_CNR_LATEST_MNG[ImCnr_D_IM_CNR_CH_1].bankArea			= 0;	// reset
		S_G_IM_CNR_LATEST_MNG[ImCnr_D_IM_CNR_CH_0].addr				= 0;	// reset
		S_G_IM_CNR_LATEST_MNG[ImCnr_D_IM_CNR_CH_1].addr				= 0;	// reset
		S_G_IM_CNR_OUTPUT_MNG[ImCnr_D_IM_CNR_CH_0].bankArea			= 0;	// reset
		S_G_IM_CNR_OUTPUT_MNG[ImCnr_D_IM_CNR_CH_1].bankArea			= 0;	// reset
		S_G_IM_CNR_OUTPUT_MNG[ImCnr_D_IM_CNR_CH_0].useBankNum		= addr_info->useBankNum;
		S_G_IM_CNR_OUTPUT_MNG[ImCnr_D_IM_CNR_CH_1].useBankNum		= addr_info->useBankNum;
		for( out_addr_cnt = 0; out_addr_cnt < addr_info->useBankNum; out_addr_cnt++ ){
			S_G_IM_CNR_OUTPUT_MNG[ImCnr_D_IM_CNR_CH_0].outputAddr[out_addr_cnt]	= addr_info->wCAddr[out_addr_cnt];
			S_G_IM_CNR_OUTPUT_MNG[ImCnr_D_IM_CNR_CH_1].outputAddr[out_addr_cnt]	= addr_info->wCAddr[out_addr_cnt];
		}
		ImCnr_IO_CNR(ImCnr_D_IM_CNR_CH_0)->OTF_REG_RW.WCTA.bit.WCTA		= addr_info->wCAddr[0];
		ImCnr_IO_CNR(ImCnr_D_IM_CNR_CH_1)->OTF_REG_RW.WCTA.bit.WCTA		= addr_info->wCAddr[0];
	}
	else{
		// set output address information	@WCTA
		S_G_IM_CNR_LATEST_MNG[ch].bankArea		= 0;	// reset
		S_G_IM_CNR_LATEST_MNG[ch].addr				= 0;	// reset
		S_G_IM_CNR_OUTPUT_MNG[ch].bankArea		= 0;	// reset
		S_G_IM_CNR_OUTPUT_MNG[ch].useBankNum		= addr_info->useBankNum;
		for( out_addr_cnt = 0; out_addr_cnt < addr_info->useBankNum; out_addr_cnt++ ){
			S_G_IM_CNR_OUTPUT_MNG[ch].outputAddr[out_addr_cnt]	= addr_info->wCAddr[out_addr_cnt];
		}
		ImCnr_IO_CNR(ch)->OTF_REG_RW.WCTA.bit.WCTA	= addr_info->wCAddr[0];
	}

	im_cnr_off_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	return D_DDIM_OK;
}

/*
CNR(OTF) increment output address index
*/
INT32 im_cnr_init_otf_increment_out_addr_index(ImCnrInit*self, UCHAR ch )
{
#ifdef CO_PARAM_CHECK
	if (ch > ImCnr_D_IM_CNR_CH_1) {
		Ddim_Assertion(("im_cnr_init_otf_increment_out_addr_index() error. input channel error : %d\n", ch));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnr_on_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	// Update output address
	++S_G_IM_CNR_OUTPUT_MNG[ch].bankArea;
	S_G_IM_CNR_OUTPUT_MNG[ch].bankArea		= ImCnrInit_ADDR_BNK_LIMIT( S_G_IM_CNR_OUTPUT_MNG[ch].bankArea, S_G_IM_CNR_OUTPUT_MNG[ch].useBankNum );
	ImCnr_IO_CNR(ch)->OTF_REG_RW.WCTA.bit.WCTA	= S_G_IM_CNR_OUTPUT_MNG[ch].outputAddr[S_G_IM_CNR_OUTPUT_MNG[ch].bankArea];

	im_cnr_off_pclk(im_cnr_new(),ch);
	ImCnr_IM_CNR_DSB();

	return D_DDIM_OK;
}

/* Get Latest Address information
 */
INT32 im_cnr_init_otf_get_latest_out_addr(ImCnrInit*self, UCHAR ch, ULONG* const latest_addr )
{
#ifdef CO_PARAM_CHECK
	if( latest_addr == NULL ) {
		Ddim_Assertion(("im_cnr_init_otf_get_latest_out_addr() error. latest_addr = NULL\n"));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( ch >= ImCnr_D_IM_CNR_CH_READ_NUM_MAX ){
		Ddim_Assertion(( "im_cnr_init_otf_get_latest_out_addr() error. input channel error : %d\n", ch));
		return ImCnr_D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*latest_addr     = S_G_IM_CNR_LATEST_MNG[ch].addr;

	return D_DDIM_OK;
}

ImCnrInit *im_cnr_init_new(void)
{
	ImCnrInit* self = k_object_new_with_private(IM_TYPE_CNR_INIT,sizeof(ImCnrInitPrivate));
	return self;
}
