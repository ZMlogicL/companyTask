/*
 * imshdr.c
 *
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :卢樊
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、interrupt setting process api
*2、
*@version:        1.0.0
*/

#include "jdsshdr.h"
#include "dd_top.h"
#include "ddim_user_custom.h"

#include "imshdr.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImShdr, im_shdr);
#define IM_SHDR_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImShdrPrivate, IM_TYPE_SHDR))

struct _ImShdrPrivate
{
	int a;
};

static void im_shdr_constructor(ImShdr *self)
{
//	ImShdrPrivate *priv = IM_SHDR_GET_PRIVATE(self);
}

static void im_shdr_destructor(ImShdr *self)
{
//	ImShdrPrivate *priv = IM_SHDR_GET_PRIVATE(self);
}

#ifdef CO_ACT_SHDR_CLOCK
static volatile UCHAR				S_G_IM_SHDR_CLK_COUNTER	= 0;
#endif

#ifdef CO_ACT_SHDR_ICLOCK
static volatile UCHAR				S_G_IM_SHDR_XCLK_COUNTER	= 0;
#endif

#ifdef CO_ACT_SHDR_HCLOCK
static volatile UCHAR				S_G_IM_SHDR_HCLK_COUNTER	= 0;
#endif

#ifdef CO_ACT_SHDR_PCLOCK
static volatile UCHAR				S_G_IM_SHDR_PCLK_COUNTER	= 0;
#endif

static volatile ULONG				S_G_IM_SHDR_SPIN_LOCK __attribute__((section(".LOCK_SECTION"), aligned(64)));

#define im_shdr_lock()				Dd_ARM_Critical_Section_Start( S_G_IM_SHDR_SPIN_LOCK )
#define im_shdr_unlock()			Dd_ARM_Critical_Section_End( S_G_IM_SHDR_SPIN_LOCK )

/*
 DECLS
 */
static VOID imShdrOnClk( VOID );
static VOID imShdrOnXclk( VOID );
static VOID imShdrOnHclk( VOID );
static VOID imShdrOffHclk( VOID );
static VOID imShdrInit( VOID );
/*
 IMPL
 */
static VOID imShdrOnClk( VOID )
{
#ifdef CO_ACT_SHDR_CLOCK
	Dd_Top_Start_Clock( (UCHAR*)&S_G_IM_SHDR_CLK_COUNTER, &Dd_Top_Get_CLKSTOP7(), ~D_DD_TOP_SHDRCK_BIT );
#endif
}
/**
XCLK ON for SHDR.<br>
@param[in]		None.
@retval			None.
*/
static VOID imShdrOnXclk( VOID )
{
#ifdef CO_ACT_SHDR_ICLOCK
	Dd_Top_Start_Clock( (UCHAR*)&S_G_IM_SHDR_XCLK_COUNTER, &Dd_Top_Get_CLKSTOP7(), ~D_DD_TOP_SHDRAX_BIT );
#endif
}
/**
HCLK ON for SHDR.<br>
@param[in]		None.
@retval			None.
*/
static VOID imShdrOnHclk( VOID )
{
#ifdef CO_ACT_SHDR_HCLOCK
	Dd_Top_Start_Clock( (UCHAR*)&S_G_IM_SHDR_HCLK_COUNTER, &Dd_Top_Get_CLKSTOP7(), ~D_DD_TOP_SHDRAH_BIT );
#endif
}
/**
HCLK OFF for SHDR.<br>
@param[in]		None.
@retval			None.
*/
static VOID imShdrOffHclk( VOID )
{
#ifdef CO_ACT_SHDR_HCLOCK
	Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_SHDR_HCLK_COUNTER, &Dd_Top_Get_CLKSTOP7(), D_DD_TOP_SHDRAH_BIT );
#endif
}
/**
SHDR initialize.<br>
@param[in]		None.
@retval			None.
*/
static VOID imShdrInit( VOID )
{
	im_shdr_wait_usec( D_IM_SHDR_SRAM_WAIT_USEC );

	// Software reset.
	IO_SHDR.SHDRACTL0.bit.SR = D_IM_SHDR_SR_RESET;

	im_shdr_dsb();

	// SHDRCLK       = MAX 400MHz	MIN 160MHz.
	// APB clock     = MAX  50MHz	MIN 12.5MHz.
	// -->   ( (1/SHDRCLK) / (1/APB clock) ) * 2 + 1.
	//     = ( (1/160)     / (1/50)        ) * 2 + 1.
	//     = 1.63 => 2 APB cycle.

	// wait 2 APB clock.
	IO_SHDR.SHDRACTL0.word;		/* pgr0695 */

	im_shdr_dsb();

	// Software reset release.
	IO_SHDR.SHDRACTL0.bit.SR = D_IM_SHDR_SR_RELEASE;

	im_shdr_dsb();

	// wait 2 APB clock.
	IO_SHDR.SHDRACTL0.word;		/* pgr0695 */

	im_shdr_dsb();

	// SRAM access enable.
	IO_SHDR.SHDRACTL2.bit.SRAMAEN = D_IM_SHDR_SRAM_ENABLE;

	// Wait 1us,
	im_shdr_wait_usec( D_IM_SHDR_SRAM_WAIT_USEC );

	im_shdr_dsb();
}

/*
PUBLIC
 */
/**
CLK OFF for SHDR.<br>
@param[in]		None.
@retval			None.
*/
 VOID im_shdr_off_clk( VOID )
{
#ifdef CO_ACT_SHDR_CLOCK
	Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_SHDR_CLK_COUNTER, &Dd_Top_Get_CLKSTOP7(), D_DD_TOP_SHDRCK_BIT );
#endif
}
 /**
 XCLK OFF for SHDR.<br>
 @param[in]		None.
 @retval			None.
 */
  VOID im_shdr_off_xclk( VOID )
 {
 #ifdef CO_ACT_SHDR_ICLOCK
 	Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_SHDR_XCLK_COUNTER, &Dd_Top_Get_CLKSTOP7(), D_DD_TOP_SHDRAX_BIT );
 #endif
 }
  /**
  PCLK ON for SHDR.<br>
  @param[in]		None.
  @retval			None.
  */
   VOID im_shdr_on_pclk( VOID )
  {
  #ifdef CO_ACT_SHDR_PCLOCK
  	Dd_Top_Start_Clock( (UCHAR*)&S_G_IM_SHDR_PCLK_COUNTER, &Dd_Top_Get_CLKSTOP7(), ~D_DD_TOP_SHDRAP_BIT );
  #endif
  }
  /**
  PCLK OFF for SHDR.<br>
  @param[in]		None.
  @retval			None.
  */
   VOID im_shdr_off_pclk( VOID )
  {
  #ifdef CO_ACT_SHDR_PCLOCK
  	Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_SHDR_PCLK_COUNTER, &Dd_Top_Get_CLKSTOP7(), D_DD_TOP_SHDRAP_BIT );
  #endif
  }
/**
SHDR initialize.<br>
@param[in]		force_flg						Force init flg.<br>
@retval			D_DDIM_OK						Success.
@retval			D_IM_SHDR_MACRO_BUSY			Macro busy.
*/
INT32 Im_SHDR_Init( BOOL force_flg )
{
	INT32 ret = D_DDIM_OK;

	im_shdr_on_pclk();
//	imShdrOnXclk();
//	imShdrOnClk();

	if ( force_flg ) {

		imShdrInit();
	}
	else {
		// Check SHDR macro status.
		if ( IO_SHDR.SHDRACTL1.bit.TRG == D_IM_SHDR_TRG_STATUS_STOP ) {

			imShdrInit();
		}
		else {
			ret = D_IM_SHDR_MACRO_BUSY;
		}
	}

//	im_shdr_off_clk();
//	im_shdr_off_xclk();
	im_shdr_off_pclk();

	return ret;
}
/**
The semaphore of SHDR is acquired.<br>
@param[in]		wait_time						Time-out period.<br>
@retval			D_DDIM_OK						Success.
@retval			D_IM_SHDR_INPUT_PARAM_ERROR		Parameter error.
@retval			D_IM_SHDR_SEM_NG				Semaphore acquisition NG.
*/
INT32 Im_SHDR_Open( const INT32 wait_time )
{
	DDIM_USER_ER	ercd;

#ifdef CO_PARAM_CHECK
	if ( im_shdr_check_wait_time( wait_time ) == FALSE ) {
		Ddim_Assertion(("Im_SHDR_Open parameter error\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
#endif

	if ( D_DDIM_USER_SEM_WAIT_POL == wait_time ) {
		ercd = DDIM_User_Pol_Sem( SID_IM_SHDR );
	}
	else {
		ercd = DDIM_User_Twai_Sem( SID_IM_SHDR, (DDIM_USER_TMO)wait_time );
	}

	if ( D_DDIM_USER_E_OK == ercd ) {
		return D_DDIM_OK;
	}
	else {
		return D_IM_SHDR_SEM_NG;
	}
}
/**
The semaphore of SHDR is returned.<br>
@retval			D_DDIM_OK						Success.
@retval			D_IM_SHDR_SEM_NG				Semaphore acquisition NG.
*/
INT32 Im_SHDR_Close( VOID )
{
	DDIM_USER_ER	ercd;

	ercd = DDIM_User_Sig_Sem( SID_IM_SHDR );

	if ( D_DDIM_USER_E_OK == ercd ) {
		return D_DDIM_OK;
	}
	else {
		return D_IM_SHDR_SEM_NG;
	}
}

INT32 Im_SHDR_Set_Degamma_R( const USHORT* const src_tbl, const USHORT write_ofs_num, const USHORT array_num )
{
	INT32	ret = D_DDIM_OK;
	UINT32	loop_cnt;

#ifdef CO_PARAM_CHECK
	if ( src_tbl == NULL ) {
		Ddim_Assertion(("Im_SHDR_Set_Degamma_R() error. src_tbl = NULL\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( ( write_ofs_num + array_num ) > D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE ) {
		Ddim_Assertion(("Im_SHDR_Set_Degamma_R(). write_ofs_num + array_num > MAX\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
#endif

	DDIM_User_AhbReg_SpinLock();	// JPEG issue work around.

	im_shdr_on_pclk();
	imShdrOnHclk();
	im_shdr_dsb();

	// Check SHDR macro status.
	if ( IO_SHDR.SHDRACTL1.bit.TRG == D_IM_SHDR_TRG_STATUS_STOP ) {
		for ( loop_cnt = 0; loop_cnt < array_num; loop_cnt++ ) {
			IO_SHDR_TBL.DGTR.hword[ write_ofs_num + loop_cnt ] = src_tbl[ loop_cnt ];
		}
	}
	else {
		Ddim_Print(("Im_SHDR_Set_Degamma_R() : Macro busy\n"));
		ret = D_IM_SHDR_MACRO_BUSY;
	}

	imShdrOffHclk();
	im_shdr_off_pclk();
	im_shdr_dsb();

	DDIM_User_AhbReg_SpinUnLock();	// JPEG issue work around.

	return ret;
}

INT32 Im_SHDR_Set_Degamma_G( const USHORT* const src_tbl, const USHORT write_ofs_num, const USHORT array_num )
{
	INT32	ret = D_DDIM_OK;
	UINT32	loop_cnt;

#ifdef CO_PARAM_CHECK
	if ( src_tbl == NULL ) {
		Ddim_Assertion(("Im_SHDR_Set_Degamma_G() error. src_tbl = NULL\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( ( write_ofs_num + array_num ) > D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE ) {
		Ddim_Assertion(("Im_SHDR_Set_Degamma_G(). write_ofs_num + array_num > MAX\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
#endif

	DDIM_User_AhbReg_SpinLock();	// JPEG issue work around.

	im_shdr_on_pclk();
	imShdrOnHclk();
	im_shdr_dsb();
	// Check SHDR macro status.
	if ( IO_SHDR.SHDRACTL1.bit.TRG == D_IM_SHDR_TRG_STATUS_STOP ) {
		for ( loop_cnt = 0; loop_cnt < array_num; loop_cnt++ ) {
			IO_SHDR_TBL.DGTG.hword[ write_ofs_num + loop_cnt ] = src_tbl[ loop_cnt ];
		}
	}
	else {
		Ddim_Print(("Im_SHDR_Set_Degamma_G() : Macro busy\n"));
		ret = D_IM_SHDR_MACRO_BUSY;
	}

	imShdrOffHclk();
	im_shdr_off_pclk();
	im_shdr_dsb();

	DDIM_User_AhbReg_SpinUnLock();	// JPEG issue work around.

	return ret;
}

INT32 Im_SHDR_Set_Degamma_B( const USHORT* const src_tbl, const USHORT write_ofs_num, const USHORT array_num )
{
	INT32	ret = D_DDIM_OK;
	UINT32	loop_cnt;

#ifdef CO_PARAM_CHECK
	if ( src_tbl == NULL ) {
		Ddim_Assertion(("Im_SHDR_Set_Degamma_B() error. src_tbl = NULL\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( ( write_ofs_num + array_num ) > D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE ) {
		Ddim_Assertion(("Im_SHDR_Set_Degamma_B(). write_ofs_num + array_num > MAX\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
#endif

	DDIM_User_AhbReg_SpinLock();	// JPEG issue work around.

	im_shdr_on_pclk();
	imShdrOnHclk();
	im_shdr_dsb();

	// Check SHDR macro status.
	if ( IO_SHDR.SHDRACTL1.bit.TRG == D_IM_SHDR_TRG_STATUS_STOP ) {
		for ( loop_cnt = 0; loop_cnt < array_num; loop_cnt++ ) {
			IO_SHDR_TBL.DGTB.hword[ write_ofs_num + loop_cnt ] = src_tbl[ loop_cnt ];
		}
	}
	else {
		Ddim_Print(("Im_SHDR_Set_Degamma_B() : Macro busy\n"));
		ret = D_IM_SHDR_MACRO_BUSY;
	}

	imShdrOffHclk();
	im_shdr_off_pclk();
	im_shdr_dsb();

	DDIM_User_AhbReg_SpinUnLock();	// JPEG issue work around.

	return ret;
}

INT32 Im_SHDR_Set_Degamma( const USHORT* const src_tbl_r, const USHORT* const src_tbl_g, const USHORT* const src_tbl_b, const USHORT write_ofs_num, const USHORT array_num )
{
	INT32	ret = D_DDIM_OK;
	UINT32	loop_cnt;

#ifdef CO_PARAM_CHECK
	if ( ( src_tbl_r == NULL ) || ( src_tbl_g == NULL ) || ( src_tbl_b == NULL ) ) {
		Ddim_Assertion(("Im_SHDR_Set_Degamma() error. src_tbl_x = NULL\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( ( write_ofs_num + array_num ) > D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE ) {
		Ddim_Assertion(("Im_SHDR_Set_Degamma(). write_ofs_num + array_num > MAX\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
#endif

	DDIM_User_AhbReg_SpinLock();	// JPEG issue work around.

	im_shdr_on_pclk();
	imShdrOnHclk();
	im_shdr_dsb();
	// Check SHDR macro status.
	if ( IO_SHDR.SHDRACTL1.bit.TRG == D_IM_SHDR_TRG_STATUS_STOP ) {

		for ( loop_cnt = 0; loop_cnt < array_num; loop_cnt++ ) {
			IO_SHDR_TBL.DGTR.hword[ write_ofs_num + loop_cnt ] = src_tbl_r[ loop_cnt ];
			IO_SHDR_TBL.DGTG.hword[ write_ofs_num + loop_cnt ] = src_tbl_g[ loop_cnt ];
			IO_SHDR_TBL.DGTB.hword[ write_ofs_num + loop_cnt ] = src_tbl_b[ loop_cnt ];
		}
	}
	else {
		Ddim_Print(("Im_SHDR_Set_Degamma() : Macro busy\n"));
		ret = D_IM_SHDR_MACRO_BUSY;
	}

	imShdrOffHclk();
	im_shdr_off_pclk();
	im_shdr_dsb();

	DDIM_User_AhbReg_SpinUnLock();	// JPEG issue work around.

	return ret;
}

INT32 Im_SHDR_Get_Degamma_R( USHORT* const dst_tbl, const USHORT read_ofs_num, const USHORT array_num, const UCHAR read_sel )
{
	INT32	ret = D_DDIM_OK;
	UINT32	loop_cnt;

#ifdef CO_PARAM_CHECK
	if ( dst_tbl == NULL ) {
		Ddim_Assertion(("Im_SHDR_Get_Degamma_R() error. dst_tbl = NULL\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( ( read_ofs_num + array_num ) > D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE ) {
		Ddim_Assertion(("Im_SHDR_Get_Degamma_R(). read_ofs_num + array_num > MAX\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( read_sel > D_IM_SHDR_DGTRSEL_PREMBS_ODD ) {
		Ddim_Assertion(("Im_SHDR_Get_Degamma_R(). read_sel is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
#endif

	DDIM_User_AhbReg_SpinLock();	// JPEG issue work around.

	im_shdr_on_pclk();
	imShdrOnHclk();
	im_shdr_dsb();
	// Check SHDR macro status.
	if ( IO_SHDR.SHDRACTL1.bit.TRG == D_IM_SHDR_TRG_STATUS_STOP ) {

		// DGT read selector set.
		IO_SHDR.DGT_RSEL.bit.DGT_RSEL = read_sel;

		for ( loop_cnt = 0; loop_cnt < array_num; loop_cnt++ ) {
			 dst_tbl[ loop_cnt ] = IO_SHDR_TBL.DGTR.hword[ read_ofs_num + loop_cnt ];
		}
	}
	else {
		Ddim_Print(("Im_SHDR_Get_Degamma_R() : Macro busy\n"));
		ret = D_IM_SHDR_MACRO_BUSY;
	}

	imShdrOffHclk();
	im_shdr_off_pclk();
	im_shdr_dsb();

	DDIM_User_AhbReg_SpinUnLock();	// JPEG issue work around.

	return ret;
}

INT32 Im_SHDR_Get_Degamma_G( USHORT* const dst_tbl, const USHORT read_ofs_num, const USHORT array_num, const UCHAR read_sel )
{
	INT32	ret = D_DDIM_OK;
	UINT32	loop_cnt;

#ifdef CO_PARAM_CHECK
	if ( dst_tbl == NULL ) {
		Ddim_Assertion(("Im_SHDR_Get_Degamma_G() error. dst_tbl = NULL\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( ( read_ofs_num + array_num ) > D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE ) {
		Ddim_Assertion(("Im_SHDR_Get_Degamma_G(). read_ofs_num + array_num > MAX\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( read_sel > D_IM_SHDR_DGTRSEL_PREMBS_ODD ) {
		Ddim_Assertion(("Im_SHDR_Get_Degamma_G(). read_sel is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
#endif

	DDIM_User_AhbReg_SpinLock();	// JPEG issue work around.

	im_shdr_on_pclk();
	imShdrOnHclk();
	im_shdr_dsb();
	// Check SHDR macro status.
	if ( IO_SHDR.SHDRACTL1.bit.TRG == D_IM_SHDR_TRG_STATUS_STOP ) {

		// DGT read selector set.
		IO_SHDR.DGT_RSEL.bit.DGT_RSEL = read_sel;

		for ( loop_cnt = 0; loop_cnt < array_num; loop_cnt++ ) {
			 dst_tbl[ loop_cnt ] = IO_SHDR_TBL.DGTG.hword[ read_ofs_num + loop_cnt ];
		}
	}
	else {
		Ddim_Print(("Im_SHDR_Get_Degamma_G() : Macro busy\n"));
		ret = D_IM_SHDR_MACRO_BUSY;
	}

	imShdrOffHclk();
	im_shdr_off_pclk();
	im_shdr_dsb();

	DDIM_User_AhbReg_SpinUnLock();	// JPEG issue work around.

	return ret;
}

INT32 Im_SHDR_Get_Degamma_B( USHORT* const dst_tbl, const USHORT read_ofs_num, const USHORT array_num, const UCHAR read_sel )
{
	INT32	ret = D_DDIM_OK;
	UINT32	loop_cnt;

#ifdef CO_PARAM_CHECK
	if ( dst_tbl == NULL ) {
		Ddim_Assertion(("Im_SHDR_Get_Degamma_B() error. dst_tbl = NULL\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( ( read_ofs_num + array_num ) > D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE ) {
		Ddim_Assertion(("Im_SHDR_Get_Degamma_B(). read_ofs_num + array_num > MAX\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( read_sel > D_IM_SHDR_DGTRSEL_PREMBS_ODD ) {
		Ddim_Assertion(("Im_SHDR_Get_Degamma_B(). read_sel is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
#endif

	DDIM_User_AhbReg_SpinLock();	// JPEG issue work around.

	im_shdr_on_pclk();
	imShdrOnHclk();
	im_shdr_dsb();
	// Check SHDR macro status.
	if ( IO_SHDR.SHDRACTL1.bit.TRG == D_IM_SHDR_TRG_STATUS_STOP ) {

		// DGT read selector set.
		IO_SHDR.DGT_RSEL.bit.DGT_RSEL = read_sel;

		for ( loop_cnt = 0; loop_cnt < array_num; loop_cnt++ ) {
			 dst_tbl[ loop_cnt ] = IO_SHDR_TBL.DGTB.hword[ read_ofs_num + loop_cnt ];
		}
	}
	else {
		Ddim_Print(("Im_SHDR_Get_Degamma_B() : Macro busy\n"));
		ret = D_IM_SHDR_MACRO_BUSY;
	}

	imShdrOffHclk();
	im_shdr_off_pclk();
	im_shdr_dsb();

	DDIM_User_AhbReg_SpinUnLock();	// JPEG issue work around.

	return ret;
}

INT32 Im_SHDR_Get_Degamma( USHORT* const dst_tbl_r, USHORT* const dst_tbl_g, USHORT* const dst_tbl_b, const USHORT read_ofs_num, const USHORT array_num, const UCHAR read_sel )
{
	INT32	ret = D_DDIM_OK;
	UINT32	loop_cnt;

#ifdef CO_PARAM_CHECK
	if ( ( dst_tbl_r == NULL ) || ( dst_tbl_g == NULL ) || ( dst_tbl_b == NULL ) ) {
		Ddim_Assertion(("Im_SHDR_Get_Degamma() error. dst_tbl_x = NULL\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( ( read_ofs_num + array_num ) > D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE ) {
		Ddim_Assertion(("Im_SHDR_Get_Degamma(). read_ofs_num + array_num > MAX\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( read_sel > D_IM_SHDR_DGTRSEL_PREMBS_ODD ) {
		Ddim_Assertion(("Im_SHDR_Get_Degamma(). read_sel is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
#endif

	DDIM_User_AhbReg_SpinLock();	// JPEG issue work around.

	im_shdr_on_pclk();
	imShdrOnHclk();
	im_shdr_dsb();
	// Check SHDR macro status.
	if ( IO_SHDR.SHDRACTL1.bit.TRG == D_IM_SHDR_TRG_STATUS_STOP ) {

		// DGT read selector set.
		IO_SHDR.DGT_RSEL.bit.DGT_RSEL = read_sel;

		for ( loop_cnt = 0; loop_cnt < array_num; loop_cnt++ ) {
			 dst_tbl_r[ loop_cnt ] = IO_SHDR_TBL.DGTR.hword[ read_ofs_num + loop_cnt ];
			 dst_tbl_g[ loop_cnt ] = IO_SHDR_TBL.DGTG.hword[ read_ofs_num + loop_cnt ];
			 dst_tbl_b[ loop_cnt ] = IO_SHDR_TBL.DGTB.hword[ read_ofs_num + loop_cnt ];
		}
	}
	else {
		Ddim_Print(("Im_SHDR_Get_Degamma() : Macro busy\n"));
		ret = D_IM_SHDR_MACRO_BUSY;
	}

	imShdrOffHclk();
	im_shdr_off_pclk();
	im_shdr_dsb();

	DDIM_User_AhbReg_SpinUnLock();	// JPEG issue work around.

	return ret;
}

INT32 Im_SHDR_Set_Axi( const T_IM_SHDR_AXI* const shdr_axi )
{
#ifdef CO_PARAM_CHECK
	if ( shdr_axi == NULL ) {
		Ddim_Assertion(("Im_SHDR_Set_Axi() error. shdr_axi = NULL\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( ( shdr_axi->ax_mode.r_burst > D_IM_SHDR_BURSTLEN_256 ) ||
		 ( shdr_axi->ax_mode.w_burst > D_IM_SHDR_BURSTLEN_256 ) ) {
		Ddim_Assertion(("Im_SHDR_Set_Axi() error. r/w_burst is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_axi->ax_mode.w_w_mask > D_IM_SHDR_WWMASK_OFF ) {
		Ddim_Assertion(("Im_SHDR_Set_Axi() error. w_w_mask is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
#endif

	im_shdr_on_pclk();
	im_shdr_dsb();

	// AXMD.
	IO_SHDR.AXMD.bit.BURSTR				= shdr_axi->ax_mode.r_burst;	// RFID = B/C/D.
	IO_SHDR.AXMD.bit.BURSTW				= shdr_axi->ax_mode.w_burst;	// WFID = B/C/D/E/F/G.
	IO_SHDR.AXMD.bit.WSTBMSK			= shdr_axi->ax_mode.w_w_mask;	// WFID = B/C/D/E/F/G.

	// AXICTLAR.
	// A.
	IO_SHDR.AXICTLARA.bit.ARCACHEA_0	= shdr_axi->r_ctl.a_cahche[ 0 ];
	IO_SHDR.AXICTLARA.bit.ARCACHEA_1	= shdr_axi->r_ctl.a_cahche[ 1 ];
	IO_SHDR.AXICTLARA.bit.ARPROTA_0		= shdr_axi->r_ctl.a_protect[ 0 ];
	IO_SHDR.AXICTLARA.bit.ARPROTA_1		= shdr_axi->r_ctl.a_protect[ 1 ];

	// B.
	IO_SHDR.AXICTLARB.bit.ARCACHEB_0	= shdr_axi->r_ctl.b_cahche[ 0 ];
	IO_SHDR.AXICTLARB.bit.ARCACHEB_1	= shdr_axi->r_ctl.b_cahche[ 1 ];
	IO_SHDR.AXICTLARB.bit.ARPROTB_0		= shdr_axi->r_ctl.b_protect[ 0 ];
	IO_SHDR.AXICTLARB.bit.ARPROTB_1		= shdr_axi->r_ctl.b_protect[ 1 ];

	// C.
	IO_SHDR.AXICTLARC.bit.ARCACHEC_0	= shdr_axi->r_ctl.c_cahche[ 0 ];
	IO_SHDR.AXICTLARC.bit.ARCACHEC_1	= shdr_axi->r_ctl.c_cahche[ 1 ];
	IO_SHDR.AXICTLARC.bit.ARCACHEC_2	= shdr_axi->r_ctl.c_cahche[ 2 ];
	IO_SHDR.AXICTLARC.bit.ARCACHEC_3	= shdr_axi->r_ctl.c_cahche[ 3 ];
	IO_SHDR.AXICTLARC.bit.ARPROTC_0		= shdr_axi->r_ctl.c_protect[ 0 ];
	IO_SHDR.AXICTLARC.bit.ARPROTC_1		= shdr_axi->r_ctl.c_protect[ 1 ];
	IO_SHDR.AXICTLARC.bit.ARPROTC_2		= shdr_axi->r_ctl.c_protect[ 2 ];
	IO_SHDR.AXICTLARC.bit.ARPROTC_3		= shdr_axi->r_ctl.c_protect[ 3 ];

	// D.
	IO_SHDR.AXICTLARD.bit.ARCACHED_0	= shdr_axi->r_ctl.d_cahche[ 0 ];
	IO_SHDR.AXICTLARD.bit.ARCACHED_1	= shdr_axi->r_ctl.d_cahche[ 1 ];
	IO_SHDR.AXICTLARD.bit.ARPROTD_0		= shdr_axi->r_ctl.d_protect[ 0 ];
	IO_SHDR.AXICTLARD.bit.ARPROTD_1		= shdr_axi->r_ctl.d_protect[ 1 ];

	// AXICTLAW.
	// A.
	IO_SHDR.AXICTLAWA.bit.AWCACHE_0		= shdr_axi->w_ctl.a_cahche[ 0 ];
	IO_SHDR.AXICTLAWA.bit.AWCACHE_1		= shdr_axi->w_ctl.a_cahche[ 1 ];
	IO_SHDR.AXICTLAWA.bit.AWCACHE_2		= shdr_axi->w_ctl.a_cahche[ 2 ];
	IO_SHDR.AXICTLAWA.bit.AWCACHE_3		= shdr_axi->w_ctl.a_cahche[ 3 ];
	IO_SHDR.AXICTLAWA.bit.AWPROT_0		= shdr_axi->w_ctl.a_protect[ 0 ];
	IO_SHDR.AXICTLAWA.bit.AWPROT_1		= shdr_axi->w_ctl.a_protect[ 1 ];
	IO_SHDR.AXICTLAWA.bit.AWPROT_2		= shdr_axi->w_ctl.a_protect[ 2 ];
	IO_SHDR.AXICTLAWA.bit.AWPROT_3		= shdr_axi->w_ctl.a_protect[ 3 ];

	// B.
	IO_SHDR.AXICTLAWB.bit.AWCACHE_0		= shdr_axi->w_ctl.b_cahche[ 0 ];
	IO_SHDR.AXICTLAWB.bit.AWCACHE_1		= shdr_axi->w_ctl.b_cahche[ 1 ];
	IO_SHDR.AXICTLAWB.bit.AWCACHE_2		= shdr_axi->w_ctl.b_cahche[ 2 ];
	IO_SHDR.AXICTLAWB.bit.AWCACHE_3		= shdr_axi->w_ctl.b_cahche[ 3 ];
	IO_SHDR.AXICTLAWB.bit.AWCACHE_4		= shdr_axi->w_ctl.b_cahche[ 4 ];
	IO_SHDR.AXICTLAWB.bit.AWCACHE_5		= shdr_axi->w_ctl.b_cahche[ 5 ];
	IO_SHDR.AXICTLAWB.bit.AWPROT_0		= shdr_axi->w_ctl.b_protect[ 0 ];
	IO_SHDR.AXICTLAWB.bit.AWPROT_1		= shdr_axi->w_ctl.b_protect[ 1 ];
	IO_SHDR.AXICTLAWB.bit.AWPROT_2		= shdr_axi->w_ctl.b_protect[ 2 ];
	IO_SHDR.AXICTLAWB.bit.AWPROT_3		= shdr_axi->w_ctl.b_protect[ 3 ];
	IO_SHDR.AXICTLAWB.bit.AWPROT_4		= shdr_axi->w_ctl.b_protect[ 4 ];
	IO_SHDR.AXICTLAWB.bit.AWPROT_5		= shdr_axi->w_ctl.b_protect[ 5 ];

	// C.
	IO_SHDR.AXICTLAWC.bit.AWCACHE_0		= shdr_axi->w_ctl.c_cahche[ 0 ];
	IO_SHDR.AXICTLAWC.bit.AWCACHE_1		= shdr_axi->w_ctl.c_cahche[ 1 ];
	IO_SHDR.AXICTLAWC.bit.AWCACHE_2		= shdr_axi->w_ctl.c_cahche[ 2 ];
	IO_SHDR.AXICTLAWC.bit.AWCACHE_3		= shdr_axi->w_ctl.c_cahche[ 3 ];
	IO_SHDR.AXICTLAWC.bit.AWCACHE_4		= shdr_axi->w_ctl.c_cahche[ 4 ];
	IO_SHDR.AXICTLAWC.bit.AWCACHE_5		= shdr_axi->w_ctl.c_cahche[ 5 ];
	IO_SHDR.AXICTLAWC.bit.AWCACHE_6		= shdr_axi->w_ctl.c_cahche[ 6 ];
	IO_SHDR.AXICTLAWC.bit.AWPROT_0		= shdr_axi->w_ctl.c_protect[ 0 ];
	IO_SHDR.AXICTLAWC.bit.AWPROT_1		= shdr_axi->w_ctl.c_protect[ 1 ];
	IO_SHDR.AXICTLAWC.bit.AWPROT_2		= shdr_axi->w_ctl.c_protect[ 2 ];
	IO_SHDR.AXICTLAWC.bit.AWPROT_3		= shdr_axi->w_ctl.c_protect[ 3 ];
	IO_SHDR.AXICTLAWC.bit.AWPROT_4		= shdr_axi->w_ctl.c_protect[ 4 ];
	IO_SHDR.AXICTLAWC.bit.AWPROT_5		= shdr_axi->w_ctl.c_protect[ 5 ];
	IO_SHDR.AXICTLAWC.bit.AWPROT_6		= shdr_axi->w_ctl.c_protect[ 6 ];

	im_shdr_off_pclk();
	im_shdr_dsb();

	return D_DDIM_OK;
}

INT32 Im_SHDR_Get_Axi( T_IM_SHDR_AXI* const shdr_axi )
{
#ifdef CO_PARAM_CHECK
	if ( shdr_axi == NULL ) {
		Ddim_Assertion(("Im_SHDR_Get_Axi() error. shdr_axi = NULL\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
#endif

	im_shdr_on_pclk();
	im_shdr_dsb();

	// AXMD.
	shdr_axi->ax_mode.r_burst		= IO_SHDR.AXMD.bit.BURSTR;
	shdr_axi->ax_mode.w_burst		= IO_SHDR.AXMD.bit.BURSTW;
	shdr_axi->ax_mode.w_w_mask		= IO_SHDR.AXMD.bit.WSTBMSK;

	// AXICTLAR.
	// A.
	shdr_axi->r_ctl.a_cahche[ 0 ]	= IO_SHDR.AXICTLARA.bit.ARCACHEA_0;
	shdr_axi->r_ctl.a_cahche[ 1 ]	= IO_SHDR.AXICTLARA.bit.ARCACHEA_1;
	shdr_axi->r_ctl.a_protect[ 0 ]	= IO_SHDR.AXICTLARA.bit.ARPROTA_0;
	shdr_axi->r_ctl.a_protect[ 1 ]	= IO_SHDR.AXICTLARA.bit.ARPROTA_1;

	// B.
	shdr_axi->r_ctl.b_cahche[ 0 ]	= IO_SHDR.AXICTLARB.bit.ARCACHEB_0;
	shdr_axi->r_ctl.b_cahche[ 1 ]	= IO_SHDR.AXICTLARB.bit.ARCACHEB_1;
	shdr_axi->r_ctl.b_protect[ 0 ]	= IO_SHDR.AXICTLARB.bit.ARPROTB_0;
	shdr_axi->r_ctl.b_protect[ 1 ]	= IO_SHDR.AXICTLARB.bit.ARPROTB_1;

	// C.
	shdr_axi->r_ctl.c_cahche[ 0 ]	= IO_SHDR.AXICTLARC.bit.ARCACHEC_0;
	shdr_axi->r_ctl.c_cahche[ 1 ]	= IO_SHDR.AXICTLARC.bit.ARCACHEC_1;
	shdr_axi->r_ctl.c_cahche[ 2 ]	= IO_SHDR.AXICTLARC.bit.ARCACHEC_2;
	shdr_axi->r_ctl.c_cahche[ 3 ]	= IO_SHDR.AXICTLARC.bit.ARCACHEC_3;
	shdr_axi->r_ctl.c_protect[ 0 ]	= IO_SHDR.AXICTLARC.bit.ARPROTC_0;
	shdr_axi->r_ctl.c_protect[ 1 ]	= IO_SHDR.AXICTLARC.bit.ARPROTC_1;
	shdr_axi->r_ctl.c_protect[ 2 ]	= IO_SHDR.AXICTLARC.bit.ARPROTC_2;
	shdr_axi->r_ctl.c_protect[ 3 ]	= IO_SHDR.AXICTLARC.bit.ARPROTC_3;

	// D.
	shdr_axi->r_ctl.d_cahche[ 0 ]	= IO_SHDR.AXICTLARD.bit.ARCACHED_0;
	shdr_axi->r_ctl.d_cahche[ 1 ]	= IO_SHDR.AXICTLARD.bit.ARCACHED_1;
	shdr_axi->r_ctl.d_protect[ 0 ]	= IO_SHDR.AXICTLARD.bit.ARPROTD_0;
	shdr_axi->r_ctl.d_protect[ 1 ]	= IO_SHDR.AXICTLARD.bit.ARPROTD_1;

	// AXICTLAW.
	// A.
	shdr_axi->w_ctl.a_cahche[ 0 ]	= IO_SHDR.AXICTLAWA.bit.AWCACHE_0;
	shdr_axi->w_ctl.a_cahche[ 1 ]	= IO_SHDR.AXICTLAWA.bit.AWCACHE_1;
	shdr_axi->w_ctl.a_cahche[ 2 ]	= IO_SHDR.AXICTLAWA.bit.AWCACHE_2;
	shdr_axi->w_ctl.a_cahche[ 3 ]	= IO_SHDR.AXICTLAWA.bit.AWCACHE_3;
	shdr_axi->w_ctl.a_protect[ 0 ]	= IO_SHDR.AXICTLAWA.bit.AWPROT_0;
	shdr_axi->w_ctl.a_protect[ 1 ]	= IO_SHDR.AXICTLAWA.bit.AWPROT_1;
	shdr_axi->w_ctl.a_protect[ 2 ]	= IO_SHDR.AXICTLAWA.bit.AWPROT_2;
	shdr_axi->w_ctl.a_protect[ 3 ]	= IO_SHDR.AXICTLAWA.bit.AWPROT_3;

	// B.
	shdr_axi->w_ctl.b_cahche[ 0 ]	= IO_SHDR.AXICTLAWB.bit.AWCACHE_0;
	shdr_axi->w_ctl.b_cahche[ 1 ]	= IO_SHDR.AXICTLAWB.bit.AWCACHE_1;
	shdr_axi->w_ctl.b_cahche[ 2 ]	= IO_SHDR.AXICTLAWB.bit.AWCACHE_2;
	shdr_axi->w_ctl.b_cahche[ 3 ]	= IO_SHDR.AXICTLAWB.bit.AWCACHE_3;
	shdr_axi->w_ctl.b_cahche[ 4 ]	= IO_SHDR.AXICTLAWB.bit.AWCACHE_4;
	shdr_axi->w_ctl.b_cahche[ 5 ]	= IO_SHDR.AXICTLAWB.bit.AWCACHE_5;
	shdr_axi->w_ctl.b_protect[ 0 ]	= IO_SHDR.AXICTLAWB.bit.AWPROT_0;
	shdr_axi->w_ctl.b_protect[ 1 ]	= IO_SHDR.AXICTLAWB.bit.AWPROT_1;
	shdr_axi->w_ctl.b_protect[ 2 ]	= IO_SHDR.AXICTLAWB.bit.AWPROT_2;
	shdr_axi->w_ctl.b_protect[ 3 ]	= IO_SHDR.AXICTLAWB.bit.AWPROT_3;
	shdr_axi->w_ctl.b_protect[ 4 ]	= IO_SHDR.AXICTLAWB.bit.AWPROT_4;
	shdr_axi->w_ctl.b_protect[ 5 ]	= IO_SHDR.AXICTLAWB.bit.AWPROT_5;

	// C.
	shdr_axi->w_ctl.c_cahche[ 0 ]	= IO_SHDR.AXICTLAWC.bit.AWCACHE_0;
	shdr_axi->w_ctl.c_cahche[ 1 ]	= IO_SHDR.AXICTLAWC.bit.AWCACHE_1;
	shdr_axi->w_ctl.c_cahche[ 2 ]	= IO_SHDR.AXICTLAWC.bit.AWCACHE_2;
	shdr_axi->w_ctl.c_cahche[ 3 ]	= IO_SHDR.AXICTLAWC.bit.AWCACHE_3;
	shdr_axi->w_ctl.c_cahche[ 4 ]	= IO_SHDR.AXICTLAWC.bit.AWCACHE_4;
	shdr_axi->w_ctl.c_cahche[ 5 ]	= IO_SHDR.AXICTLAWC.bit.AWCACHE_5;
	shdr_axi->w_ctl.c_cahche[ 6 ]	= IO_SHDR.AXICTLAWC.bit.AWCACHE_6;
	shdr_axi->w_ctl.c_protect[ 0 ]	= IO_SHDR.AXICTLAWC.bit.AWPROT_0;
	shdr_axi->w_ctl.c_protect[ 1 ]	= IO_SHDR.AXICTLAWC.bit.AWPROT_1;
	shdr_axi->w_ctl.c_protect[ 2 ]	= IO_SHDR.AXICTLAWC.bit.AWPROT_2;
	shdr_axi->w_ctl.c_protect[ 3 ]	= IO_SHDR.AXICTLAWC.bit.AWPROT_3;
	shdr_axi->w_ctl.c_protect[ 4 ]	= IO_SHDR.AXICTLAWC.bit.AWPROT_4;
	shdr_axi->w_ctl.c_protect[ 5 ]	= IO_SHDR.AXICTLAWC.bit.AWPROT_5;
	shdr_axi->w_ctl.c_protect[ 6 ]	= IO_SHDR.AXICTLAWC.bit.AWPROT_6;

	im_shdr_off_pclk();
	im_shdr_dsb();

	return D_DDIM_OK;
}

INT32 Im_SHDR_Get_Axi_Response( T_IM_SHDR_AXI_RESP* const axi_resp )
{
#ifdef CO_PARAM_CHECK
	if ( axi_resp == NULL ) {
		Ddim_Assertion(("Im_SHDR_Get_Axi_Response() error. axi_resp = NULL\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
#endif

	im_shdr_on_pclk();
	im_shdr_dsb();

	// Read channel response (A).
	axi_resp->r_resp_a[ 0 ] = IO_SHDR.AXICTLRA.bit.RRESPA_0;
	axi_resp->r_resp_a[ 1 ] = IO_SHDR.AXICTLRA.bit.RRESPA_1;

	// Read channel response (B).
	axi_resp->r_resp_b[ 0 ] = IO_SHDR.AXICTLRB.bit.RRESPB_0;
	axi_resp->r_resp_b[ 1 ] = IO_SHDR.AXICTLRB.bit.RRESPB_1;

	// Read channel response (C).
	axi_resp->r_resp_c[ 0 ] = IO_SHDR.AXICTLRC.bit.RRESPC_0;
	axi_resp->r_resp_c[ 1 ] = IO_SHDR.AXICTLRC.bit.RRESPC_1;
	axi_resp->r_resp_c[ 2 ] = IO_SHDR.AXICTLRC.bit.RRESPC_2;
	axi_resp->r_resp_c[ 3 ] = IO_SHDR.AXICTLRC.bit.RRESPC_3;

	// Read channel response (D).
	axi_resp->r_resp_d[ 0 ] = IO_SHDR.AXICTLRD.bit.RRESPD_0;
	axi_resp->r_resp_d[ 1 ] = IO_SHDR.AXICTLRD.bit.RRESPD_1;

	// Write channel response (A).
	axi_resp->w_resp_a[ 0 ] = IO_SHDR.AXICTLWA.bit.BRESPA_0;
	axi_resp->w_resp_a[ 1 ] = IO_SHDR.AXICTLWA.bit.BRESPA_1;
	axi_resp->w_resp_a[ 2 ] = IO_SHDR.AXICTLWA.bit.BRESPA_2;
	axi_resp->w_resp_a[ 3 ] = IO_SHDR.AXICTLWA.bit.BRESPA_3;

	// Write channel response (B).
	axi_resp->w_resp_b[ 0 ] = IO_SHDR.AXICTLWB.bit.BRESPB_0;
	axi_resp->w_resp_b[ 1 ] = IO_SHDR.AXICTLWB.bit.BRESPB_1;
	axi_resp->w_resp_b[ 2 ] = IO_SHDR.AXICTLWB.bit.BRESPB_2;
	axi_resp->w_resp_b[ 3 ] = IO_SHDR.AXICTLWB.bit.BRESPB_3;
	axi_resp->w_resp_b[ 4 ] = IO_SHDR.AXICTLWB.bit.BRESPB_4;
	axi_resp->w_resp_b[ 5 ] = IO_SHDR.AXICTLWB.bit.BRESPB_5;

	// Write channel response (C).
	axi_resp->w_resp_c[ 0 ] = IO_SHDR.AXICTLWC.bit.BRESPC_0;
	axi_resp->w_resp_c[ 1 ] = IO_SHDR.AXICTLWC.bit.BRESPC_1;
	axi_resp->w_resp_c[ 2 ] = IO_SHDR.AXICTLWC.bit.BRESPC_2;
	axi_resp->w_resp_c[ 3 ] = IO_SHDR.AXICTLWC.bit.BRESPC_3;
	axi_resp->w_resp_c[ 4 ] = IO_SHDR.AXICTLWC.bit.BRESPC_4;
	axi_resp->w_resp_c[ 5 ] = IO_SHDR.AXICTLWC.bit.BRESPC_5;
	axi_resp->w_resp_c[ 6 ] = IO_SHDR.AXICTLWC.bit.BRESPC_6;

	im_shdr_off_pclk();
	im_shdr_dsb();

	return D_DDIM_OK;
}

INT32 Im_SHDR_Start( VOID )
{
	INT32					ret = D_DDIM_OK;
	union io_shdr_shdrint1	shdrint1;

	im_shdr_on_pclk();
	im_shdr_dsb();

	im_shdr_lock();

	// Check SHDR macro status.
	if ( IO_SHDR.SHDRACTL1.bit.TRG == D_IM_SHDR_TRG_STATUS_STOP ) {

		(VOID)DDIM_User_Clr_Flg( FID_IM_SHDR, ~( D_IM_SHDR_FLG_END | D_IM_SHDR_FLG_STOP ) );

		// Interrupt enable.
		IO_SHDR.SHDRINT0.bit.AXWEEN	= 1;
		IO_SHDR.SHDRINT0.bit.AXREEN	= 1;
		IO_SHDR.SHDRINT0.bit.SHDREN	= 1;

		// Interrupt flag clear.
		shdrint1.word				= 0;
		shdrint1.bit.__AXWEFLG		= 1;
		shdrint1.bit.__AXREFLG		= 1;
		shdrint1.bit.__SHDRFLG		= 1;
		IO_SHDR.SHDRINT1.word		= shdrint1.word;

		imShdrOnXclk();
		imShdrOnClk();
		im_shdr_dsb();

		// SHDR macro start.
		IO_SHDR.SHDRACTL1.bit.TRG = D_IM_SHDR_TRG_START;
	}
	else {
		Ddim_Print(("Im_SHDR_Start() : Macro busy\n"));
		ret = D_IM_SHDR_MACRO_BUSY;
	}

	im_shdr_unlock();
	im_shdr_off_pclk();
	im_shdr_dsb();

	return ret;
}

INT32 Im_SHDR_Stop( VOID )
{
	INT32			ret = D_DDIM_OK;
	DDIM_USER_ER	ercd;

	im_shdr_on_pclk();
	imShdrOnXclk();
	imShdrOnClk();
	im_shdr_dsb();

	im_shdr_lock();

	// Check SHDR macro status.
	if ( IO_SHDR.SHDRACTL1.bit.TRG == D_IM_SHDR_TRG_STATUS_START ) {

		// SHDR macro stop.
		IO_SHDR.SHDRACTL1.bit.TRG = D_IM_SHDR_TRG_STOP;
		im_shdr_dsb();

		ercd = DDIM_User_Set_Flg( FID_IM_SHDR, D_IM_SHDR_FLG_STOP );
		if ( ercd != D_DDIM_USER_E_OK ) {
			Ddim_Print(("Im_SHDR_Stop : Error DDIM_User_Set_Flg [%d]\n", ercd));
			ret = D_IM_SHDR_NG;
		}

		// Check SHDR macro status.
		if ( IO_SHDR.SHDRACTL1.bit.TRG == D_IM_SHDR_TRG_STATUS_START ) {
			Ddim_Print(("Im_SHDR_Stop : Macro busy. [%d]\n", ercd));
			ret = D_IM_SHDR_MACRO_BUSY;
		}
	}
	im_shdr_unlock();
	im_shdr_off_clk();
	im_shdr_off_xclk();
	im_shdr_off_pclk();
	im_shdr_dsb();

	return ret;
}

ImShdr *im_shdr_new(void)
{
	ImShdr* self = k_object_new_with_private(IM_TYPE_SHDR,sizeof(ImShdrPrivate));
	return self;
}
