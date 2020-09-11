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
static volatile T_IM_CNR_CALLBACK	S_G_IM_CNR_OFL_CALLBACK_FUNC[D_IM_CNR_CH_READ_NUM_MAX] = {NULL, NULL};
static volatile T_IM_CNR_CALLBACK	S_G_IM_CNR_OTF_CALLBACK_FUNC[D_IM_CNR_CH_READ_NUM_MAX] = {NULL, NULL};
static volatile UINT32 S_G_IM_CNR_OFL_USERPARAM[D_IM_CNR_CH_READ_NUM_MAX] = {0, 0};
static volatile UINT32 S_G_IM_CNR_OTF_USERPARAM[D_IM_CNR_CH_READ_NUM_MAX] = {0, 0};
// Output address parameter
static volatile T_IM_CNR_OUTPUT_MNG S_G_IM_CNR_OUTPUT_MNG[D_IM_CNR_CH_READ_NUM_MAX];
// Output address parameter
static volatile T_IM_CNR_LATEST_MNG S_G_IM_CNR_LATEST_MNG[D_IM_CNR_CH_READ_NUM_MAX];

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

	IO_CNR(ch)->OFL_REG_RW.SPRICE.word = spric.word;
#ifdef CO_DEBUG_ON_PC
	if( ch == D_IM_CNR_CH_2 ){
		IO_CNR(D_IM_CNR_CH_0)->OFL_REG_RW.SPRICE.word = spric.word;
		IO_CNR(D_IM_CNR_CH_1)->OFL_REG_RW.SPRICE.word = spric.word;
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

	IO_CNR(ch)->OTF_REG_RW.SPRICE.word = spric.word;
#ifdef CO_DEBUG_ON_PC
	if( ch == D_IM_CNR_CH_2 ){
		IO_CNR(D_IM_CNR_CH_0)->OTF_REG_RW.SPRICE.word = spric.word;
		IO_CNR(D_IM_CNR_CH_1)->OTF_REG_RW.SPRICE.word = spric.word;
	}
#endif	// CO_DEBUG_ON_PC
}

// AXIF Interrupt flag clear
static VOID imCnrOflClearAxif( UCHAR ch )
{
#ifdef CO_DEBUG_ON_PC
	IO_CNR(ch)->OFL_REG_RW.SPRICF.bit.__AXIF = 0;
	if( ch == D_IM_CNR_CH_2 ){
		IO_CNR(D_IM_CNR_CH_0)->OFL_REG_RW.SPRICF.bit.__AXIF = 0;
		IO_CNR(D_IM_CNR_CH_1)->OFL_REG_RW.SPRICF.bit.__AXIF = 0;
	}
#else //!CO_DEBUG_ON_PC
	union io_cnr_ofl_reg_rw_spricf spricf;

	spricf.word = 0;
	spricf.bit.__AXIF = 1;

	IO_CNR(ch)->OFL_REG_RW.SPRICF.word = spricf.word;
#endif //!CO_DEBUG_ON_PC
}

// AXIF Interrupt flag clear
static VOID imCnrOtfClearAxif( UCHAR ch )
{
#ifdef CO_DEBUG_ON_PC
	IO_CNR(ch)->OTF_REG_RW.SPRICF.bit.__AXIF = 0;
	if( ch == D_IM_CNR_CH_2 ){
		IO_CNR(D_IM_CNR_CH_0)->OTF_REG_RW.SPRICF.bit.__AXIF = 0;
		IO_CNR(D_IM_CNR_CH_1)->OTF_REG_RW.SPRICF.bit.__AXIF = 0;
	}
#else //!CO_DEBUG_ON_PC
	union io_cnr_otf_reg_rw_spricf spricf;

	spricf.word = 0;
	spricf.bit.__AXIF = 1;

	IO_CNR(ch)->OTF_REG_RW.SPRICF.word = spricf.word;
#endif //!CO_DEBUG_ON_PC
}

// DRTF Interrupt flag clear
static VOID im_cnr_otf_clear_drtf( UCHAR ch )
{
#ifdef CO_DEBUG_ON_PC
	IO_CNR(ch)->OTF_REG_RW.SPRICF.bit.__DRTF = 0;
	if( ch == D_IM_CNR_CH_2 ){
		IO_CNR(D_IM_CNR_CH_0)->OTF_REG_RW.SPRICF.bit.__DRTF = 0;
		IO_CNR(D_IM_CNR_CH_1)->OTF_REG_RW.SPRICF.bit.__DRTF = 0;
	}
#else //!CO_DEBUG_ON_PC
	union io_cnr_otf_reg_rw_spricf spricf;

	spricf.word = 0;
	spricf.bit.__DRTF = 1;

	IO_CNR(ch)->OTF_REG_RW.SPRICF.word = spricf.word;
#endif //!CO_DEBUG_ON_PC
}

// SPDF Interrupt flag clear
static VOID imCnrOflClearSpdf( UCHAR ch )
{
#ifdef CO_DEBUG_ON_PC
	IO_CNR(ch)->OFL_REG_RW.SPRICF.bit.__SPDF = 0;
	if( ch == D_IM_CNR_CH_2 ){
		IO_CNR(D_IM_CNR_CH_0)->OFL_REG_RW.SPRICF.bit.__SPDF = 0;
		IO_CNR(D_IM_CNR_CH_1)->OFL_REG_RW.SPRICF.bit.__SPDF = 0;
	}
#else //!CO_DEBUG_ON_PC
	union io_cnr_ofl_reg_rw_spricf spricf;

	spricf.word = 0;
	spricf.bit.__SPDF = 1;

	IO_CNR(ch)->OFL_REG_RW.SPRICF.word = spricf.word;
#endif //!CO_DEBUG_ON_PC
}

// SPDF Interrupt flag clear
static VOID imCnrOtfClearSpdf( UCHAR ch )
{
#ifdef CO_DEBUG_ON_PC
	IO_CNR(ch)->OTF_REG_RW.SPRICF.bit.__SPDF = 0;
	if( ch == D_IM_CNR_CH_2 ){
		IO_CNR(D_IM_CNR_CH_0)->OTF_REG_RW.SPRICF.bit.__SPDF = 0;
		IO_CNR(D_IM_CNR_CH_1)->OTF_REG_RW.SPRICF.bit.__SPDF = 0;
	}
#else //!CO_DEBUG_ON_PC
	union io_cnr_otf_reg_rw_spricf spricf;

	spricf.word = 0;
	spricf.bit.__SPDF = 1;

	IO_CNR(ch)->OTF_REG_RW.SPRICF.word = spricf.word;
#endif //!CO_DEBUG_ON_PC
}

/*----------------------------------------------------------------------*/
/* Global Function														*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
/*
CNR(OTF) Macro handler
*/
VOID im_cnr_otf_int_handler( UCHAR ch )
{
	DDIM_USER_FLGPTN flg;
	union io_cnr_otf_reg_rw_sprice sprice;
	union io_cnr_otf_reg_rw_spricf spricf;

	Im_CNR_On_Pclk(ch);
	Im_CNR_Dsb();

	sprice.word = IO_CNR(ch)->OTF_REG_RW.SPRICE.word;
	spricf.word = IO_CNR(ch)->OTF_REG_RW.SPRICF.word;

	if( (sprice.bit.AXIE != 0) && (spricf.bit.__AXIF != 0) ) {		/* pgr0872 */
		// clear interrupt end register
		imCnrOtfClearAxif(ch);

		// Set End Flag
		if (ch == D_IM_CNR_CH_0) {
			flg = D_IM_CNR_FLG_0_OTF_SPR_AXI_ERR;

			DDIM_User_Set_Flg( FID_IM_CNR, D_IM_CNR_FLG_0_OTF_SPR_AXI_ERR );
		}
		else {
			flg = D_IM_CNR_FLG_1_OTF_SPR_AXI_ERR;

			DDIM_User_Set_Flg( FID_IM_CNR, D_IM_CNR_FLG_1_OTF_SPR_AXI_ERR );
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
		if (ch == D_IM_CNR_CH_0) {
			flg = D_IM_CNR_FLG_0_OTF_SPR_DRT_ERR;

			DDIM_User_Set_Flg( FID_IM_CNR, D_IM_CNR_FLG_0_OTF_SPR_DRT_ERR );
		}
		else {
			flg = D_IM_CNR_FLG_1_OTF_SPR_DRT_ERR;

			DDIM_User_Set_Flg( FID_IM_CNR, D_IM_CNR_FLG_1_OTF_SPR_DRT_ERR );
		}

		// User Function Check
		if( S_G_IM_CNR_OTF_CALLBACK_FUNC[ch] != NULL ) {
			S_G_IM_CNR_OTF_CALLBACK_FUNC[ch]( ch, flg, S_G_IM_CNR_OTF_USERPARAM[ch] );
		}
	}

	if( (sprice.bit.SPDE != 0) && (spricf.bit.__SPDF != 0) ) {		/* pgr0872 */
		// clear interrupt end register
		imCnrOtfClearSpdf(ch);

//		im_CNR_off_spr_clk(ch);

		// Update latest address
		S_G_IM_CNR_LATEST_MNG[ch].addr	= S_G_IM_CNR_OUTPUT_MNG[ch].output_addr[S_G_IM_CNR_LATEST_MNG[ch].bank_area];
		// Update output address
		++S_G_IM_CNR_LATEST_MNG[ch].bank_area;
		S_G_IM_CNR_LATEST_MNG[ch].bank_area	= ADDR_BNK_LIMIT( S_G_IM_CNR_LATEST_MNG[ch].bank_area, S_G_IM_CNR_OUTPUT_MNG[ch].use_bank_num );

		if (ch == D_IM_CNR_CH_0) {
			flg = D_IM_CNR_FLG_0_OTF_SPR_END;
		}
		else{	// D_IM_CNR_CH_1
			flg = D_IM_CNR_FLG_1_OTF_SPR_END;
		}

		// Set End Flag
		(VOID)DDIM_User_Set_Flg( FID_IM_CNR, flg );

		// User Function Check
		if( S_G_IM_CNR_OTF_CALLBACK_FUNC[ch] != NULL ) {
			S_G_IM_CNR_OTF_CALLBACK_FUNC[ch]( ch, flg, S_G_IM_CNR_OTF_USERPARAM[ch] );
		}
	}

	Im_CNR_Off_Pclk(ch);
	Im_CNR_Dsb();
}

/*
CNR(OFL) Macro handler
*/
VOID im_cnr_ofl_int_handler( UCHAR ch )
{
	DDIM_USER_FLGPTN flg;
	union io_cnr_ofl_reg_rw_sprice sprice;
	union io_cnr_ofl_reg_rw_spricf spricf;

	Im_CNR_On_Pclk(ch);
	Im_CNR_Dsb();

	sprice.word = IO_CNR(ch)->OFL_REG_RW.SPRICE.word;
	spricf.word = IO_CNR(ch)->OFL_REG_RW.SPRICF.word;

	if( (sprice.bit.AXIE != 0) && (spricf.bit.__AXIF != 0) ) {		/* pgr0872 */
		// clear interrupt end register
		imCnrOflClearAxif(ch);

		// Set End Flag
		if (ch == D_IM_CNR_CH_0) {
			flg = D_IM_CNR_FLG_0_OFL_SPR_AXI_ERR;

			DDIM_User_Set_Flg( FID_IM_CNR, D_IM_CNR_FLG_0_OFL_SPR_AXI_ERR );
		}
		else {
			flg = D_IM_CNR_FLG_1_OFL_SPR_AXI_ERR;

			DDIM_User_Set_Flg( FID_IM_CNR, D_IM_CNR_FLG_1_OFL_SPR_AXI_ERR );
		}

		// User Function Check
		if( S_G_IM_CNR_OFL_CALLBACK_FUNC[ch] != NULL ) {
			S_G_IM_CNR_OFL_CALLBACK_FUNC[ch]( ch, flg, S_G_IM_CNR_OFL_USERPARAM[ch] );
		}
	}

	if( (sprice.bit.SPDE != 0) && (spricf.bit.__SPDF != 0) ) {		/* pgr0872 */
		// clear interrupt end register
		imCnrOflClearSpdf(ch);

		im_CNR_off_spr_clk(ch);

		if (ch == D_IM_CNR_CH_0) {
			flg = D_IM_CNR_FLG_0_OFL_SPR_END;
		}
		else {	// D_IM_CNR_CH_1
			flg = D_IM_CNR_FLG_1_OFL_SPR_END;
		}

		// Set End Flag
		(VOID)DDIM_User_Set_Flg( FID_IM_CNR, flg );

		// User Function Check
		if( S_G_IM_CNR_OFL_CALLBACK_FUNC[ch] != NULL ) {
			S_G_IM_CNR_OFL_CALLBACK_FUNC[ch]( ch, flg, S_G_IM_CNR_OFL_USERPARAM[ch] );
		}
	}

	Im_CNR_Off_Pclk(ch);
	Im_CNR_Dsb();
}

/*
Set software reset and operating mode for Off Line
*/
INT32 Im_CNR_OFL_Init( UCHAR ch )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("Im_CNR_OFL_Init() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	im_CNR_on_spr_clk(ch);
	Im_CNR_On_Pclk(ch);

	if (ch == D_IM_CNR_CH_0) {
		IO_CNR(ch)->OFL_REG_RW.SPRSR.bit.SR = 1;	// Software reset assert

		Im_CNR_Dsb();

		// CNRCLK        = MAX 252.0MHz		MIN 31.5MHz
		// APB clock     = MAX  66.7MHz		MIN 20.8MHz
		// -->   ( (1/CNRCLK) / (1/APB clock) ) * 2 + 1
		//     = ( (1/31.5)   / (1/66.7)        ) * 2 + 1
		//     = 5.23 => 6 APB cycle

		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		Im_CNR_Dsb();

		IO_CNR(ch)->OFL_REG_RW.SPRSR.bit.SR = 0;	// Software reset de-assert

		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		Im_CNR_Dsb();
	}
	else if (ch == D_IM_CNR_CH_1) {
		IO_CNR(ch)->OFL_REG_RW.SPRSR.bit.SR = 1;	// Software reset assert

		Im_CNR_Dsb();

		// CNRCLK        = MAX 252.0MHz		MIN 31.5MHz
		// APB clock     = MAX  66.7MHz		MIN 20.8MHz
		// -->   ( (1/CNRCLK) / (1/APB clock) ) * 2 + 1
		//     = ( (1/31.5)   / (1/66.7)        ) * 2 + 1
		//     = 5.23 => 6 APB cycle

		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		Im_CNR_Dsb();

		IO_CNR(ch)->OFL_REG_RW.SPRSR.bit.SR = 0;	// Software reset de-assert

		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		Im_CNR_Dsb();
	}
	else {
		IO_CNR(ch)->OFL_REG_RW.SPRSR.bit.SR = 1;	// Software reset assert

		Im_CNR_Dsb();

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
		Im_CNR_Dsb();

		IO_CNR(ch)->OFL_REG_RW.SPRSR.bit.SR = 0;	// Software reset de-assert

		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		Im_CNR_Dsb();
	}

	imCnrOflClearSpdf(ch);	// Interrupt clear
	imCnrOflClearAxif(ch);	// Interrupt clear
	imCnrOflSetSpde( ch, 1 );

	Im_CNR_Off_Pclk(ch);
	im_CNR_off_spr_clk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
CNR(OFL) Control
*/
INT32 Im_CNR_OFL_Ctrl( UCHAR ch, const T_IM_CNR_OFL_CTRL* const spr_ctrl )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("Im_CNR_OFL_Ctrl() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_ctrl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_OFL_Ctrl() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	Im_CNR_On_Pclk(ch);
	Im_CNR_Dsb();

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

	IO_CNR(ch)->OFL_REG_RW.SPRMOD.bit.YUV_MODE	= spr_ctrl->mode;	// SPR YCC mode		@YUV_MODE

	IO_CNR(ch)->OFL_REG_RW.HSIZE.bit.HSIZE	= spr_ctrl->width;		// SPR valid data width		@HSIZE
	IO_CNR(ch)->OFL_REG_RW.VSIZE.bit.VSIZE	= spr_ctrl->lines;		// SPR valid data lines		@VSIZE

	IO_CNR(ch)->OFL_REG_RW.RYDEF.bit.RYDEF	= spr_ctrl->r_y_width;	// Y width for read			@RYDEF
	IO_CNR(ch)->OFL_REG_RW.RYTA.bit.RYTA	= spr_ctrl->r_y_addr;	// Y address for read		@RYTA

	IO_CNR(ch)->OFL_REG_RW.RCDEF.bit.RCDEF	= spr_ctrl->r_c_width;	// CbCr width for read		@RCDEF
	IO_CNR(ch)->OFL_REG_RW.RCBTA.bit.RCBTA	= spr_ctrl->r_cb_addr;	// Cb address for read		@RCBTA
	IO_CNR(ch)->OFL_REG_RW.RCRTA.bit.RCRTA	= spr_ctrl->r_cr_addr;	// Cr address for read		@RCRTA

	IO_CNR(ch)->OFL_REG_RW.WYDEF.bit.WYDEF	= spr_ctrl->w_y_width;	// Y width for write		@WYDEF
	IO_CNR(ch)->OFL_REG_RW.WYTA.bit.WYTA	= spr_ctrl->w_y_addr;	// Y address for write		@WYTA

	IO_CNR(ch)->OFL_REG_RW.WCDEF.bit.WCDEF	= spr_ctrl->w_c_width;	// CbCr width for write		@WCDEF
	IO_CNR(ch)->OFL_REG_RW.WCBTA.bit.WCBTA	= spr_ctrl->w_cb_addr;	// Cb address for write		@WCBTA
	IO_CNR(ch)->OFL_REG_RW.WCRTA.bit.WCRTA	= spr_ctrl->w_cr_addr;	// Cr address for write		@WCRTA

	IO_CNR(ch)->OFL_REG_RW.TMPTA.bit.TMPTA	= spr_ctrl->work_addr;	// Address fir work area	@TMPTA

	IO_CNR(ch)->OFL_REG_RW.VDIV.bit.VDIVT	= spr_ctrl->divide_top;		// Virtucal process devide	@VDIVT
	IO_CNR(ch)->OFL_REG_RW.VDIV.bit.VDIVB	= spr_ctrl->divide_bot;		// Virtucal process devide	@VDIVB

	if( ch == D_IM_CNR_CH_2 ){
		S_G_IM_CNR_OFL_CALLBACK_FUNC[D_IM_CNR_CH_0]	= spr_ctrl->pCallBack;
		S_G_IM_CNR_OFL_CALLBACK_FUNC[D_IM_CNR_CH_1]	= spr_ctrl->pCallBack;
		S_G_IM_CNR_OFL_USERPARAM[D_IM_CNR_CH_0]		= spr_ctrl->user_param;
		S_G_IM_CNR_OFL_USERPARAM[D_IM_CNR_CH_1]		= spr_ctrl->user_param;
	}
	else{
		S_G_IM_CNR_OFL_CALLBACK_FUNC[ch]	= spr_ctrl->pCallBack;
		S_G_IM_CNR_OFL_USERPARAM[ch]		= spr_ctrl->user_param;
	}

	Im_CNR_Off_Pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
Set software reset and operating mode for Off Line
*/
INT32 Im_CNR_OTF_Init( UCHAR ch )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("Im_CNR_OTF_Init() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	im_CNR_on_spr_clk(ch);
	Im_CNR_On_Pclk(ch);

	if (ch == D_IM_CNR_CH_0) {
		IO_CNR(ch)->OTF_REG_RW.SPRSR.bit.SR = 1;	// Software reset assert

		Im_CNR_Dsb();

		// CNRCLK        = MAX 252.0MHz		MIN 31.5MHz
		// APB clock     = MAX  66.7MHz		MIN 20.8MHz
		// -->   ( (1/CNRCLK) / (1/APB clock) ) * 2 + 1
		//     = ( (1/31.5)   / (1/66.7)        ) * 2 + 1
		//     = 5.23 => 6 APB cycle

		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		Im_CNR_Dsb();

		IO_CNR(ch)->OTF_REG_RW.SPRSR.bit.SR = 0;	// Software reset de-assert

		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		Im_CNR_Dsb();
	}
	else if (ch == D_IM_CNR_CH_1) {
		IO_CNR(ch)->OTF_REG_RW.SPRSR.bit.SR = 1;	// Software reset assert

		Im_CNR_Dsb();

		// CNRCLK        = MAX 252.0MHz		MIN 31.5MHz
		// APB clock     = MAX  66.7MHz		MIN 20.8MHz
		// -->   ( (1/CNRCLK) / (1/APB clock) ) * 2 + 1
		//     = ( (1/31.5)   / (1/66.7)        ) * 2 + 1
		//     = 5.23 => 6 APB cycle

		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		Im_CNR_Dsb();

		IO_CNR(ch)->OTF_REG_RW.SPRSR.bit.SR = 0;	// Software reset de-assert

		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		Im_CNR_Dsb();
	}
	else {
		IO_CNR(ch)->OTF_REG_RW.SPRSR.bit.SR = 1;	// Software reset assert

		Im_CNR_Dsb();

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
		Im_CNR_Dsb();

		IO_CNR(ch)->OTF_REG_RW.SPRSR.bit.SR = 0;	// Software reset de-assert

		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP11();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		Dd_Top_Get_CLKSTOP13();	/* pgr0695 */
		Im_CNR_Dsb();
	}

	imCnrOtfClearSpdf(ch);	// Interrupt clear
	imCnrOtfClearAxif(ch);	// Interrupt clear
	im_cnr_otf_clear_drtf(ch);	// Interrupt clear
	imCnrOtfSetSpde( ch, 1 );

	Im_CNR_Off_Pclk(ch);
	im_CNR_off_spr_clk(ch);
	Im_CNR_Dsb();

	// Initialize of Address management information
	if( ch == D_IM_CNR_CH_2 ){
		memset( (VOID*)&S_G_IM_CNR_OUTPUT_MNG[D_IM_CNR_CH_0], 0, sizeof(T_IM_CNR_OUTPUT_MNG) * 2 );
		memset( (VOID*)&S_G_IM_CNR_LATEST_MNG[D_IM_CNR_CH_0], 0, sizeof(T_IM_CNR_LATEST_MNG) * 2 );
	}
	else{
		memset( (VOID*)&S_G_IM_CNR_OUTPUT_MNG[ch], 0, sizeof(T_IM_CNR_OUTPUT_MNG) );
		memset( (VOID*)&S_G_IM_CNR_LATEST_MNG[ch], 0, sizeof(T_IM_CNR_LATEST_MNG) );
	}

	return D_DDIM_OK;
}

/*
CNR(OTF) Control
*/
INT32 Im_CNR_OTF_Ctrl( UCHAR ch, const T_IM_CNR_OTF_CTRL* const spr_ctrl )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("Im_CNR_OTF_Ctrl() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( spr_ctrl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_OTF_Ctrl() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif
	if (spr_ctrl->width < 96 || spr_ctrl->width > 2360) {
		Ddim_Assertion(("Im_CNR_OTF_Ctrl() error. input width error : %d\n", spr_ctrl->width));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if (spr_ctrl->lines < 72 || spr_ctrl->lines > 4096) {
		Ddim_Assertion(("Im_CNR_OTF_Ctrl() error. input lines error : %d\n", spr_ctrl->lines));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if ( (spr_ctrl->w_offset_x != 0)&&(spr_ctrl->w_offset_x < 96 || spr_ctrl->w_offset_x > 2360)) {
		Ddim_Assertion(("Im_CNR_OTF_Ctrl() error. input w_offset_x error : %lu\n", spr_ctrl->w_offset_x));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if (spr_ctrl->video_format == 1){
		if (spr_ctrl->w_c_width % 128){
			Ddim_Assertion(("Im_CNR_OTF_Ctrl() error. input w_c_width error : %lu\n", spr_ctrl->w_c_width));
			return D_IM_CNR_INPUT_PARAM_ERROR;
		}
		if( spr_ctrl->mode != E_IM_CNR_OTF_YCC_MODE_YCC420_SIMPLE ){
			Ddim_Assertion(("Im_CNR_OTF_Ctrl() error. mode error : %d\n", spr_ctrl->mode));
			return D_IM_CNR_INPUT_PARAM_ERROR;
		}
	}

	Im_CNR_On_Pclk(ch);
	Im_CNR_Dsb();

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

	IO_CNR(ch)->OTF_REG_RW.SPRMOD.bit.YUV_MODE		= spr_ctrl->mode;			// SPR YCC mode				@YUV_MODE
	IO_CNR(ch)->OTF_REG_RW.SPRMOD.bit.EXMODE		= spr_ctrl->extra_mode;		// SPR extra mode			@EXMODE
	IO_CNR(ch)->OTF_REG_RW.SPRMOD.bit.CNRVFM		= spr_ctrl->video_format;	// SPR video format			@CNRVFM

	IO_CNR(ch)->OTF_REG_RW.HSIZE.bit.HSIZE			= spr_ctrl->width;			// SPR valid data width		@HSIZE
	IO_CNR(ch)->OTF_REG_RW.VSIZE.bit.VSIZE			= spr_ctrl->lines;			// SPR valid data lines		@VSIZE

	IO_CNR(ch)->OTF_REG_RW.WCDEF.bit.WCDEF			= spr_ctrl->w_c_width;		// CbCr width for write		@WCDEF

	IO_CNR(ch)->OTF_REG_RW.CNRWOFSX.bit.CNRWOFSX	= spr_ctrl->w_offset_x;		// write offset X direction	@CNRWOFSX

	IO_CNR(ch)->OTF_REG_RW.HDIV.bit.HDIVL			= spr_ctrl->divide_left;	// Virtucal process devide	@HDIVL
	IO_CNR(ch)->OTF_REG_RW.HDIV.bit.HDIVR			= spr_ctrl->divide_right;	// Virtucal process devide	@VDIVR

	IO_CNR(ch)->OTF_REG_RW.SPRTRG.bit.CNRCSE		= spr_ctrl->continuous;		// Continuous processing	@CNRCSE

	if( ch == D_IM_CNR_CH_2 ){
		S_G_IM_CNR_OTF_CALLBACK_FUNC[D_IM_CNR_CH_0]	= spr_ctrl->pCallBack;
		S_G_IM_CNR_OTF_CALLBACK_FUNC[D_IM_CNR_CH_1]	= spr_ctrl->pCallBack;
		S_G_IM_CNR_OTF_USERPARAM[D_IM_CNR_CH_0]		= spr_ctrl->user_param;
		S_G_IM_CNR_OTF_USERPARAM[D_IM_CNR_CH_1]		= spr_ctrl->user_param;
	}
	else{
		S_G_IM_CNR_OTF_CALLBACK_FUNC[ch]				= spr_ctrl->pCallBack;
		S_G_IM_CNR_OTF_USERPARAM[ch]					= spr_ctrl->user_param;
	}

	Im_CNR_Off_Pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
CNR(OTF) Set output address information
*/
INT32 Im_CNR_OTF_Set_OutAddr_Info( UCHAR ch, const T_IM_CNR_OTF_OUTADDR_INFO* const addr_info )
{
	INT32 out_addr_cnt;

#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("Im_CNR_OTF_Set_OutAddr_Info() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( addr_info == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_OTF_Set_OutAddr_Info() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( (addr_info->use_bank_num == 0)||(addr_info->use_bank_num > D_IM_CNR_ADDR_BANK_MAX) ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_OTF_Set_OutAddr_Info() use_bank_num parameter is error : %d\n", addr_info->use_bank_num));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	Im_CNR_On_Pclk(ch);
	Im_CNR_Dsb();

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

	if( ch == D_IM_CNR_CH_2 ){
		// set output address information	@WCTA
		S_G_IM_CNR_LATEST_MNG[D_IM_CNR_CH_0].bank_area			= 0;	// reset
		S_G_IM_CNR_LATEST_MNG[D_IM_CNR_CH_1].bank_area			= 0;	// reset
		S_G_IM_CNR_LATEST_MNG[D_IM_CNR_CH_0].addr				= 0;	// reset
		S_G_IM_CNR_LATEST_MNG[D_IM_CNR_CH_1].addr				= 0;	// reset
		S_G_IM_CNR_OUTPUT_MNG[D_IM_CNR_CH_0].bank_area			= 0;	// reset
		S_G_IM_CNR_OUTPUT_MNG[D_IM_CNR_CH_1].bank_area			= 0;	// reset
		S_G_IM_CNR_OUTPUT_MNG[D_IM_CNR_CH_0].use_bank_num		= addr_info->use_bank_num;
		S_G_IM_CNR_OUTPUT_MNG[D_IM_CNR_CH_1].use_bank_num		= addr_info->use_bank_num;
		for( out_addr_cnt = 0; out_addr_cnt < addr_info->use_bank_num; out_addr_cnt++ ){
			S_G_IM_CNR_OUTPUT_MNG[D_IM_CNR_CH_0].output_addr[out_addr_cnt]	= addr_info->w_c_addr[out_addr_cnt];
			S_G_IM_CNR_OUTPUT_MNG[D_IM_CNR_CH_1].output_addr[out_addr_cnt]	= addr_info->w_c_addr[out_addr_cnt];
		}
		IO_CNR(D_IM_CNR_CH_0)->OTF_REG_RW.WCTA.bit.WCTA		= addr_info->w_c_addr[0];
		IO_CNR(D_IM_CNR_CH_1)->OTF_REG_RW.WCTA.bit.WCTA		= addr_info->w_c_addr[0];
	}
	else{
		// set output address information	@WCTA
		S_G_IM_CNR_LATEST_MNG[ch].bank_area		= 0;	// reset
		S_G_IM_CNR_LATEST_MNG[ch].addr				= 0;	// reset
		S_G_IM_CNR_OUTPUT_MNG[ch].bank_area		= 0;	// reset
		S_G_IM_CNR_OUTPUT_MNG[ch].use_bank_num		= addr_info->use_bank_num;
		for( out_addr_cnt = 0; out_addr_cnt < addr_info->use_bank_num; out_addr_cnt++ ){
			S_G_IM_CNR_OUTPUT_MNG[ch].output_addr[out_addr_cnt]	= addr_info->w_c_addr[out_addr_cnt];
		}
		IO_CNR(ch)->OTF_REG_RW.WCTA.bit.WCTA	= addr_info->w_c_addr[0];
	}

	Im_CNR_Off_Pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
CNR(OTF) increment output address index
*/
INT32 Im_CNR_OTF_Increment_OutAddr_Index( UCHAR ch )
{
#ifdef CO_PARAM_CHECK
	if (ch > D_IM_CNR_CH_1) {
		Ddim_Assertion(("Im_CNR_OTF_Increment_OutAddr_Index() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	Im_CNR_On_Pclk(ch);
	Im_CNR_Dsb();

	// Update output address
	++S_G_IM_CNR_OUTPUT_MNG[ch].bank_area;
	S_G_IM_CNR_OUTPUT_MNG[ch].bank_area		= ADDR_BNK_LIMIT( S_G_IM_CNR_OUTPUT_MNG[ch].bank_area, S_G_IM_CNR_OUTPUT_MNG[ch].use_bank_num );
	IO_CNR(ch)->OTF_REG_RW.WCTA.bit.WCTA	= S_G_IM_CNR_OUTPUT_MNG[ch].output_addr[S_G_IM_CNR_OUTPUT_MNG[ch].bank_area];

	Im_CNR_Off_Pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/* Get Latest Address information
 */
INT32 Im_CNR_OTF_Get_Latest_OutAddr( UCHAR ch, ULONG* const latest_addr )
{
#ifdef CO_PARAM_CHECK
	if( latest_addr == NULL ) {
		Ddim_Assertion(("Im_CNR_OTF_Get_Latest_OutAddr() error. latest_addr = NULL\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( ch >= D_IM_CNR_CH_READ_NUM_MAX ){
		Ddim_Assertion(( "Im_CNR_OTF_Get_Latest_OutAddr() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
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
