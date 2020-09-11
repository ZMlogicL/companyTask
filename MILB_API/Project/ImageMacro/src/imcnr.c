/*
*@Copyright (c1) 2010-2020 上海网用软件有限公司
*@date:		 2020-8-5 (发布日期)
*@author:	 余林瑞
*@brief:
*@function:参照ETK代码规范，写一个模板类。
*设计的主要功能:
*1、命名规范
*2、类中各模块的布局规范
*3、常量枚举函数等声明及定义顺序
*@version: 1.0.0 实现一个模板类
*
*/


#include "imcnr.h"
#include "driver_common.h"
// #if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
// #endif
#include "dd_arm.h"
#include "ddim_user_custom.h"
#include "imcnrone.h"
#include "jdscnr.h"
// for memset
#include "imcnrone.h"
#include <string.h>


G_DEFINE_TYPE(ImCnr, im_cnr, G_TYPE_OBJECT);
#define IM_CNR_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IM_TYPE_CNR, ImCnrPrivate));


struct _ImCnrPrivate{

};


#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
// Nothing Special
//---------------------------- colabo section ----------------------------
// Nothing Special
#endif


/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
/* Nothing Special */

#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
// Nothing Special
//---------------------------- colabo section ----------------------------
// Nothing Special
#endif

#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
// Nothing Special
//---------------------------- colabo section ----------------------------
// Nothing Special
#endif

/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------

#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
// Nothing Special
//---------------------------- colabo section ----------------------------
// Nothing Special
#endif

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------


#ifdef CO_ACT_CNRCLOCK
static volatile UCHAR gIM_CNR_Clk_Ctrl_Cnt1 = 0;
static volatile UCHAR gIM_CNR_Clk_Ctrl_Cnt2 = 0;
#endif //CO_ACT_CNRCLOCK
#ifdef CO_ACT_CNR_ICLK
static volatile UCHAR gIM_CNR_Iclk_Ctrl_Cnt1 = 0;
static volatile UCHAR gIM_CNR_Iclk_Ctrl_Cnt2 = 0;
#endif //CO_ACT_CNR_ICLK
#ifdef CO_ACT_CNR_PCLK
static volatile UCHAR gIM_CNR_Pclk_Ctrl_Cnt1 = 0;
static volatile UCHAR gIM_CNR_Pclk_Ctrl_Cnt2 = 0;
#endif //CO_ACT_CNR_PCLK


/*DECLS*/
/*----------------------------------------------------------------------*/
/* Local Method Definition												*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
static void  dispose_od(GObject *object);
static void  finalize_od(GObject *object);
static VOID imCnrOflSetSpde( const UCHAR ch, const UCHAR onoff );
static VOID imCnrOtfSetSpde( const UCHAR ch, const UCHAR onoff );
static VOID imCnrOflClearAxif( UCHAR ch );
static VOID imCnrOtfClearAxif( UCHAR ch );
static VOID imCnrOflClearSpdf( UCHAR ch );
static VOID imCnrOtfClearSpdf( UCHAR ch );
static VOID imCnrOnSprClk( UCHAR ch );
static VOID imCnrOffSprClk( UCHAR ch );

/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
// Interrupt Enable/Disable control
/*IMPL*/
static void im_cnr_class_init(ImCnrClass *klass)
{
	g_type_class_add_private(klass, sizeof(ImCnrPrivate));
}

static void im_cnr_init(ImCnr *self)
{
	ImCnrPrivate *priv = IM_CNR_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
	ImCnrPrivate *self = IM_CNR_GET_PRIVATE(object);
}

static void finalize_od(GObject *object)
{
	ImCnrPrivate *self = IM_CNR_GET_PRIVATE(object);
}

static VOID imCnrOflSetSpde(const UCHAR ch, const UCHAR onoff)
{
	union io_cnr_ofl_reg_rw_sprice spric;

	spric.word = 0;
	spric.bit.SPDE = onoff;
	spric.bit.AXIE = onoff;

	IO_CNR(ch)->OFL_REG_RW.SPRICE.word = spric.word;
#ifdef CO_DEBUG_ON_PC
	if( ch == D_IM_CNR_CH_2 ) {
		IO_CNR(D_IM_CNR_CH_0)->OFL_REG_RW.SPRICE.word = spric.word;
		IO_CNR(D_IM_CNR_CH_1)->OFL_REG_RW.SPRICE.word = spric.word;
	}
#endif	// CO_DEBUG_ON_PC
}

static VOID imCnrOtfSetSpde(const UCHAR ch, const UCHAR onoff)
{
	union io_cnr_otf_reg_rw_sprice spric;

	spric.word = 0;
	spric.bit.SPDE = onoff;
	spric.bit.AXIE = onoff;
	spric.bit.DRTE = onoff;

	IO_CNR(ch)->OTF_REG_RW.SPRICE.word = spric.word;
#ifdef CO_DEBUG_ON_PC
	if( ch == D_IM_CNR_CH_2 ) {
		IO_CNR(D_IM_CNR_CH_0)->OTF_REG_RW.SPRICE.word = spric.word;
		IO_CNR(D_IM_CNR_CH_1)->OTF_REG_RW.SPRICE.word = spric.word;
	}
#endif	// CO_DEBUG_ON_PC
}

// AXIF Interrupt flag clear
static VOID imCnrOflClearAxif( UCHAR ch)
{
#ifdef CO_DEBUG_ON_PC
	IO_CNR(ch)->OFL_REG_RW.SPRICF.bit.__AXIF = 0;
	if( ch == D_IM_CNR_CH_2 ) {
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
static VOID imCnrOtfClearAxif( UCHAR ch)
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
static VOID imCnrOtfClearDrtf( UCHAR ch)
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
static VOID imCnrOflClearSpdf( UCHAR ch)
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
static VOID imCnrOtfClearSpdf( UCHAR ch)
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

// Start CNR ICLK, CNRCLK
static VOID imCnrOnSprClk(const UCHAR ch)
{
#if defined(CO_ACT_CNR_ICLK) || defined(CO_ACT_CNRCLOCK)
	INT32 intkey;

	intkey = Dd_ARM_DI();
#endif // CO_ACT_CNR_ICLK || CO_ACT_CNRCLOCK

	if (ch == D_IM_CNR_CH_0) {
#ifdef CO_ACT_CNRCLOCK
		Dd_Top_Start_Clock( (UCHAR*)&gIM_CNR_Clk_Ctrl_Cnt1, &Dd_Top_Get_CLKSTOP11(), ~D_DD_TOP_CNR1CK_BIT );
#endif //CO_ACT_CNRCLOCK
#ifdef CO_ACT_CNR_ICLK
		Dd_Top_Start_Clock( (UCHAR*)&gIM_CNR_Iclk_Ctrl_Cnt1, &Dd_Top_Get_CLKSTOP11(), ~D_DD_TOP_CNR1AX_BIT );
#endif //CO_ACT_CNR_ICLK
	}
	else if (ch == D_IM_CNR_CH_1) {
#ifdef CO_ACT_CNRCLOCK
		Dd_Top_Start_Clock( (UCHAR*)&gIM_CNR_Clk_Ctrl_Cnt2, &Dd_Top_Get_CLKSTOP13(), ~D_DD_TOP_CNR2CK_BIT );
#endif //CO_ACT_CNRCLOCK
#ifdef CO_ACT_CNR_ICLK
		Dd_Top_Start_Clock( (UCHAR*)&gIM_CNR_Iclk_Ctrl_Cnt2, &Dd_Top_Get_CLKSTOP13(), ~D_DD_TOP_CNR2AX_BIT );
#endif //CO_ACT_CNR_ICLK
	}
	else {
#ifdef CO_ACT_CNRCLOCK
		Dd_Top_Start_Clock( (UCHAR*)&gIM_CNR_Clk_Ctrl_Cnt1, &Dd_Top_Get_CLKSTOP11(), ~D_DD_TOP_CNR1CK_BIT );
		Dd_Top_Start_Clock( (UCHAR*)&gIM_CNR_Clk_Ctrl_Cnt2, &Dd_Top_Get_CLKSTOP13(), ~D_DD_TOP_CNR2CK_BIT );
#endif //CO_ACT_CNRCLOCK
#ifdef CO_ACT_CNR_ICLK
		Dd_Top_Start_Clock( (UCHAR*)&gIM_CNR_Iclk_Ctrl_Cnt1, &Dd_Top_Get_CLKSTOP11(), ~D_DD_TOP_CNR1AX_BIT );
		Dd_Top_Start_Clock( (UCHAR*)&gIM_CNR_Iclk_Ctrl_Cnt2, &Dd_Top_Get_CLKSTOP13(), ~D_DD_TOP_CNR2AX_BIT );
#endif //CO_ACT_CNR_ICLK
	}

#if defined(CO_ACT_CNR_ICLK) || defined(CO_ACT_CNRCLOCK)
	Dd_ARM_EI( intkey );
#endif // CO_ACT_CNR_ICLK || CO_ACT_CNRCLOCK
}

// Stop CNR ICLK, CNRCLK
static VOID imCnrOffSprClk(const UCHAR ch)
{
#if defined(CO_ACT_CNR_ICLK) || defined(CO_ACT_CNRCLOCK)
	INT32 intkey;

	intkey = Dd_ARM_DI();
#endif // CO_ACT_CNR_ICLK || CO_ACT_CNRCLOCK

	if (ch == D_IM_CNR_CH_0) {
#ifdef CO_ACT_CNR_ICLK
		Dd_Top_Stop_Clock( (UCHAR*)&gIM_CNR_Iclk_Ctrl_Cnt1, &Dd_Top_Get_CLKSTOP11(), D_DD_TOP_CNR1AX_BIT );
#endif //CO_ACT_CNR_ICLK

#ifdef CO_ACT_CNRCLOCK
		Dd_Top_Stop_Clock( (UCHAR*)&gIM_CNR_Clk_Ctrl_Cnt1, &Dd_Top_Get_CLKSTOP11(), D_DD_TOP_CNR1CK_BIT );
#endif //CO_ACT_CNRCLOCK
	}
	else if (ch == D_IM_CNR_CH_1) {
#ifdef CO_ACT_CNR_ICLK
		Dd_Top_Stop_Clock( (UCHAR*)&gIM_CNR_Iclk_Ctrl_Cnt2, &Dd_Top_Get_CLKSTOP13(), D_DD_TOP_CNR2AX_BIT );
#endif //CO_ACT_CNR_ICLK

#ifdef CO_ACT_CNRCLOCK
		Dd_Top_Stop_Clock( (UCHAR*)&gIM_CNR_Clk_Ctrl_Cnt2, &Dd_Top_Get_CLKSTOP13(), D_DD_TOP_CNR2CK_BIT );
#endif //CO_ACT_CNRCLOCK
	}
	else {
#ifdef CO_ACT_CNR_ICLK
		Dd_Top_Stop_Clock( (UCHAR*)&gIM_CNR_Iclk_Ctrl_Cnt1, &Dd_Top_Get_CLKSTOP11(), D_DD_TOP_CNR1AX_BIT );
		Dd_Top_Stop_Clock( (UCHAR*)&gIM_CNR_Iclk_Ctrl_Cnt2, &Dd_Top_Get_CLKSTOP13(), D_DD_TOP_CNR2AX_BIT );
#endif //CO_ACT_CNR_ICLK

#ifdef CO_ACT_CNRCLOCK
		Dd_Top_Stop_Clock( (UCHAR*)&gIM_CNR_Clk_Ctrl_Cnt1, &Dd_Top_Get_CLKSTOP11(), D_DD_TOP_CNR1CK_BIT );
		Dd_Top_Stop_Clock( (UCHAR*)&gIM_CNR_Clk_Ctrl_Cnt2, &Dd_Top_Get_CLKSTOP13(), D_DD_TOP_CNR2CK_BIT );
#endif //CO_ACT_CNRCLOCK
	}

#if defined(CO_ACT_CNR_ICLK) || defined(CO_ACT_CNRCLOCK)
	Dd_ARM_EI( intkey );
#endif // CO_ACT_CNR_ICLK || CO_ACT_CNRCLOCK
}

/*
CNR(OFL) Macro handler
*/
static VOID imCnrOflIntHandler( UCHAR ch)
{
	DDIM_USER_FLGPTN flg;
	union io_cnr_ofl_reg_rw_sprice sprice;
	union io_cnr_ofl_reg_rw_spricf spricf;

	im_cnrone_on_pclk(ch);
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
		if( gIM_CNR_OFL_CallBack_Func[ch] != NULL ) {
			gIM_CNR_OFL_CallBack_Func[ch]( ch, flg, gIM_CNR_OFL_UserParam[ch] );
		}
	}

	if( (sprice.bit.SPDE != 0) && (spricf.bit.__SPDF != 0) ) {		/* pgr0872 */
		// clear interrupt end register
		imCnrOflClearSpdf(ch);

		imCnrOffSprClk(ch);

		if (ch == D_IM_CNR_CH_0) {
			flg = D_IM_CNR_FLG_0_OFL_SPR_END;
		}
		else {	// D_IM_CNR_CH_1
			flg = D_IM_CNR_FLG_1_OFL_SPR_END;
		}

		// Set End Flag
		(VOID)DDIM_User_Set_Flg( FID_IM_CNR, flg );

		// User Function Check
		if( gIM_CNR_OFL_CallBack_Func[ch] != NULL ) {
			gIM_CNR_OFL_CallBack_Func[ch]( ch, flg, gIM_CNR_OFL_UserParam[ch] );
		}
	}

	im_cnrone_off_pclk(ch);
	Im_CNR_Dsb();
}

/*
CNR(OTF) Macro handler
*/
static VOID imCnrOtfIntHandler( UCHAR ch)
{
	DDIM_USER_FLGPTN flg;
	union io_cnr_otf_reg_rw_sprice sprice;
	union io_cnr_otf_reg_rw_spricf spricf;

	im_cnrone_on_pclk(ch);
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
		if( gIM_CNR_OTF_CallBack_Func[ch] != NULL ) {
			gIM_CNR_OTF_CallBack_Func[ch]( ch, flg, gIM_CNR_OTF_UserParam[ch] );
		}
	}

	if( (sprice.bit.DRTE != 0) && (spricf.bit.__DRTF != 0) ) {		/* pgr0872 */
		// clear interrupt end register
		imCnrOtfClearDrtf(ch);

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
		if( gIM_CNR_OTF_CallBack_Func[ch] != NULL ) {
			gIM_CNR_OTF_CallBack_Func[ch]( ch, flg, gIM_CNR_OTF_UserParam[ch] );
		}
	}

	if( (sprice.bit.SPDE != 0) && (spricf.bit.__SPDF != 0) ) {		/* pgr0872 */
		// clear interrupt end register
		imCnrOtfClearSpdf(ch);

//		imCnrOffSprClk(ch);

		// Update latest address
		gIM_CNR_Latest_Mng[ch].addr	= gIM_CNR_Output_Mng[ch].output_addr[gIM_CNR_Latest_Mng[ch].bank_area];
		// Update output address
		++gIM_CNR_Latest_Mng[ch].bank_area;
		gIM_CNR_Latest_Mng[ch].bank_area	= ADDR_BNK_LIMIT( gIM_CNR_Latest_Mng[ch].bank_area, gIM_CNR_Output_Mng[ch].use_bank_num );

		if (ch == D_IM_CNR_CH_0) {
			flg = D_IM_CNR_FLG_0_OTF_SPR_END;
		}
		else{	// D_IM_CNR_CH_1
			flg = D_IM_CNR_FLG_1_OTF_SPR_END;
		}

		// Set End Flag
		(VOID)DDIM_User_Set_Flg( FID_IM_CNR, flg );

		// User Function Check
		if( gIM_CNR_OTF_CallBack_Func[ch] != NULL ) {
			gIM_CNR_OTF_CallBack_Func[ch]( ch, flg, gIM_CNR_OTF_UserParam[ch] );
		}
	}

	im_cnrone_off_pclk(ch);
	Im_CNR_Dsb();
}

#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
// Nothing Special
//---------------------------- colabo section ----------------------------
#endif


/*----------------------------------------------------------------------*/
/* Global Function														*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------

/*
Set software reset and operating mode for Off Line
*/
INT32 im_cnr_ofl_init(ImCnr *self, UCHAR ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_ofl_init() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	imCnrOnSprClk(ch);
	im_cnrone_on_pclk(ch);

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

	im_cnrone_off_pclk(ch);
	imCnrOffSprClk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
Set software reset and operating mode for Off Line
*/
INT32 im_cnr_otf_init(ImCnr *self, UCHAR ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_otf_init() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	imCnrOnSprClk(ch);
	im_cnrone_on_pclk(ch);

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
	imCnrOtfClearDrtf(ch);	// Interrupt clear
	imCnrOtfSetSpde( ch, 1 );

	im_cnrone_off_pclk(ch);
	imCnrOffSprClk(ch);
	Im_CNR_Dsb();

	// Initialize of Address management information
	if( ch == D_IM_CNR_CH_2 ){
		memset( (VOID*)&gIM_CNR_Output_Mng[D_IM_CNR_CH_0], 0, sizeof(T_IM_CNR_OUTPUT_MNG) * 2 );
		memset( (VOID*)&gIM_CNR_Latest_Mng[D_IM_CNR_CH_0], 0, sizeof(T_IM_CNR_LATEST_MNG) * 2 );
	}
	else{
		memset( (VOID*)&gIM_CNR_Output_Mng[ch], 0, sizeof(T_IM_CNR_OUTPUT_MNG) );
		memset( (VOID*)&gIM_CNR_Latest_Mng[ch], 0, sizeof(T_IM_CNR_LATEST_MNG) );
	}

	return D_DDIM_OK;
}

/*
CNR(OFL) Stop
*/
INT32 im_cnr_ofl_stop(ImCnr *self, UCHAR ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_ofl_stop() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif
	im_cnrone_on_pclk(ch);
	Im_CNR_Dsb();

	if( IO_CNR(ch)->OFL_REG_RW.SPRTRG.bit.SPRTRG == 3 ) {
		Im_CNR_OFL_Disable(ch);
#ifdef CO_DEBUG_ON_PC
		if( ch == D_IM_CNR_CH_0 ){
			IO_CNR(ch)->OFL_REG_RW.SPRTRG.bit.SPRTRG = 2;
		}
		else if( ch == D_IM_CNR_CH_1 ){
			IO_CNR(ch)->OFL_REG_RW.SPRTRG.bit.SPRTRG = 2;
		}
		else{
			IO_CNR(D_IM_CNR_CH_0)->OFL_REG_RW.SPRTRG.bit.SPRTRG = 2;
			IO_CNR(D_IM_CNR_CH_1)->OFL_REG_RW.SPRTRG.bit.SPRTRG = 2;
		}
#endif //CO_DEBUG_ON_PC
	}

	// Set Acess Disable
	IO_CNR(ch)->OFL_REG_RW.ACESEN.bit.SPRACS = 0;

	imCnrOffSprClk(ch);
	im_cnrone_off_pclk(ch);
	Im_CNR_Dsb();
//	Ddim_Print("I: [SPR] func disable.\n");

	return D_DDIM_OK;
}

/*
CNR(OTF) Stop
*/
INT32 im_cnr_otf_stop(ImCnr *self, UCHAR ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_otf_stop() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif
	im_cnrone_on_pclk(ch);
	Im_CNR_Dsb();

	if( IO_CNR(ch)->OTF_REG_RW.SPRTRG.bit.SPRTRG == 3 ) {
		Im_CNR_OTF_Disable(ch);
#ifdef CO_DEBUG_ON_PC
		if( ch == D_IM_CNR_CH_0 ){
			IO_CNR(ch)->OTF_REG_RW.SPRTRG.bit.SPRTRG = 2;
		}
		else if( ch == D_IM_CNR_CH_1 ){
			IO_CNR(ch)->OTF_REG_RW.SPRTRG.bit.SPRTRG = 2;
		}
		else{
			IO_CNR(D_IM_CNR_CH_0)->OTF_REG_RW.SPRTRG.bit.SPRTRG = 2;
			IO_CNR(D_IM_CNR_CH_1)->OTF_REG_RW.SPRTRG.bit.SPRTRG = 2;
		}
#endif //CO_DEBUG_ON_PC
	}

	// Set Acess Disable
	IO_CNR(ch)->OTF_REG_RW.ACESEN.bit.SPRACS = 0;

	imCnrOffSprClk(ch);
	im_cnrone_off_pclk(ch);
	Im_CNR_Dsb();
//	Ddim_Print("I: [SPR] func disable.\n");

	return D_DDIM_OK;
}

/*
The semaphore of CNR(OFL) is returned
*/
INT32 im_cnr_ofl_close(ImCnr *self, UCHAR ch)
{
	DDIM_USER_ER ercd;

#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_ofl_close() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif
	imCnrOffSprClk(ch);
	Im_CNR_Dsb();

	if (ch == D_IM_CNR_CH_2) {
		for( UCHAR loop = D_IM_CNR_CH_0; loop <= D_IM_CNR_CH_1; loop++ ){
			ercd = DDIM_User_Sig_Sem( SID_IM_CNR_OFL(loop) );				// sig_sem()

			if( D_DDIM_USER_E_OK != ercd ) {
				// SPR processing error
				Ddim_Print(("I:im_cnr_ofl_close() Error.\n"));
				return D_IM_CNR_SEM_NG;
			}
		}
	}
	else{
		ercd = DDIM_User_Sig_Sem( SID_IM_CNR_OFL(ch) );				// sig_sem()

		if( D_DDIM_USER_E_OK != ercd ) {
			// SPR processing error
			Ddim_Print(("I:im_cnr_ofl_close() Error.\n"));
			return D_IM_CNR_SEM_NG;
		}
	}
	return D_DDIM_OK;
}

/*
The semaphore of CNR(OTF) is returned
*/
INT32 im_cnr_otf_close(ImCnr *self, UCHAR ch)
{
	DDIM_USER_ER ercd;

#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_otf_close() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif
	imCnrOffSprClk(ch);
	Im_CNR_Dsb();

	if (ch == D_IM_CNR_CH_2) {
		for( UCHAR loop = D_IM_CNR_CH_0; loop <= D_IM_CNR_CH_1; loop++ ){
			ercd = DDIM_User_Sig_Sem( SID_IM_CNR_OTF(loop) );				// sig_sem()

			if( D_DDIM_USER_E_OK != ercd ) {
				// SPR processing error
				Ddim_Print(("I:im_cnr_otf_close() Error.\n"));
				return D_IM_CNR_SEM_NG;
			}
		}
	}
	else{
		ercd = DDIM_User_Sig_Sem( SID_IM_CNR_OTF(ch) );				// sig_sem()

		if( D_DDIM_USER_E_OK != ercd ) {
			// SPR processing error
			Ddim_Print(("I:im_cnr_otf_close() Error.\n"));
			return D_IM_CNR_SEM_NG;
		}
	}
	return D_DDIM_OK;
}

/*
CNR(OFL) Reset
*/
INT32 im_cnr_ofl_reset(ImCnr *self, UCHAR ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_ofl_reset() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif
	im_cnrone_on_pclk(ch);
	imCnrOnSprClk(ch);
	Im_CNR_Dsb();

	Im_CNR_OFL_Softreset(ch);

	imCnrOffSprClk(ch);
	im_cnrone_off_pclk(ch);
	Im_CNR_Dsb();
//	Ddim_Print("I: [SPR] func soft reset.\n");

	return D_DDIM_OK;
}

/*
CNR(OTF) Reset
*/
INT32 im_cnr_otf_reset(ImCnr *self, UCHAR ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_otf_reset() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif
	im_cnrone_on_pclk(ch);
	imCnrOnSprClk(ch);
	Im_CNR_Dsb();

	Im_CNR_OTF_Softreset(ch);

	imCnrOffSprClk(ch);
	im_cnrone_off_pclk(ch);
	Im_CNR_Dsb();
//	Ddim_Print("I: [SPR] func soft reset.\n");

	return D_DDIM_OK;
}

VOID im_cnr_0_int_handler( VOID)
{
	if( gim_cnr_mode[D_IM_CNR_CH_0] == D_IM_CNR_MODE_OFL ){
		imCnrOflIntHandler( D_IM_CNR_CH_0 );
	}
	else{
		imCnrOtfIntHandler( D_IM_CNR_CH_0 );
	}
}

VOID im_cnr_1_int_handler( VOID )
{
	if (gim_cnr_mode[D_IM_CNR_CH_1] == D_IM_CNR_MODE_OFL) {
		imCnrOflIntHandler( D_IM_CNR_CH_1);
	} else {
		imCnrOtfIntHandler( D_IM_CNR_CH_1);
	}
}


/*PUBLIC*/
ImCnr* im_cnr_new(void)
{
	ImCnr *self = g_object_new(IM_TYPE_CNR, NULL);
	return self;
}


