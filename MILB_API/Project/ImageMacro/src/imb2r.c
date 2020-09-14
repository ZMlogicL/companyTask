/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :唐萍萍
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年09月开始开发
*/

#include <string.h>
//#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
//#endif
#include "dd_arm.h"

#include "jdsb2r.h"
//#include "imrdma.h"
#include"imb2r.h"
#include"imb2r1.h"
#include"imb2r2.h"
#include"imb2r3.h"
#include "imb2r4.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImB2r, im_b2r);
#define IM_B2R_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImB2rPrivate, IM_TYPE_B2R))

struct _ImB2rPrivate
{
	int a;
};


static void im_b2r_constructor(ImB2r *self)
{
	//ImB2rPrivate *priv = IM_B2R_GET_PRIVATE(self);
}

static void im_b2r_destructor(ImB2r *self)
{
	//ImB2rPrivate *priv = IM_B2R_GET_PRIVATE(self);
}

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_IMAGE_CLOCK)
#define ImB2r_CO_ACT_B2R_CLOCK
#endif	// CO_ACT_PCLOCK
#if defined(CO_ACT_HCLOCK) || defined(CO_ACT_IMAGE_HCLOCK)
#define ImB2r_CO_ACT_B2R_HCLOCK
#endif	// CO_ACT_HCLOCK
#if defined(CO_ACT_PCLOCK) || defined(CO_ACT_IMAGE_PCLOCK)
#define ImB2r_CO_ACT_B2R_PCLOCK
#endif	// CO_ACT_PCLOCK
#if defined(CO_ACT_ICLOCK) || defined(CO_ACT_IMAGE_ICLOCK)
#define ImB2r_CO_ACT_B2R_ICLOCK
#endif	// CO_ACT_ICLOCK

/*----------------------------------------------------------------------*/
/* Structure  															*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
// Access enable register management
typedef struct {
	UCHAR	ctrlCnt[ImB2r1_D_IM_B2R_PIPE_COUNT];
	VOID	(*regSetFunc)( UCHAR pipe_no, UCHAR enable );
} TImB2rAccessEnableManage;

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
// Clock control counter
#ifdef ImB2r_CO_ACT_B2R_CLOCK
static volatile UCHAR S_G_IM_B2R_CLK_CTRL_CNT[ImB2r1_D_IM_B2R_PIPE_COUNT] = {0,0};
#endif	// ImB2r_CO_ACT_B2R_CLOCK
#ifdef ImB2r_CO_ACT_B2R_HCLOCK
static volatile UCHAR S_G_IM_B2R_HCLK_CTRL_CNT[ImB2r1_D_IM_B2R_PIPE_COUNT] = {0,0};
#endif	// ImB2r_CO_ACT_B2R_HCLOCK
#ifdef ImB2r_CO_ACT_B2R_PCLOCK
static volatile UCHAR S_G_IM_B2R_PCLK_CTRL_CNT[ImB2r1_D_IM_B2R_PIPE_COUNT] = {0,0};
#endif	// ImB2r_CO_ACT_B2R_PCLOCK
#ifdef ImB2r_CO_ACT_B2R_ICLOCK
static volatile UCHAR S_G_IM_B2R_ICLK_CTRL_CNT[ImB2r1_D_IM_B2R_PIPE_COUNT] = {0,0};
#endif	// ImB2r_CO_ACT_B2R_ICLOCK


// clock off control is disabled(for register dump on debugger)
#ifdef ImB2r_CO_ACT_B2R_CLOCK
static volatile UINT32 S_G_IM_B2R_CLK_CTRL_DISABLE[ImB2r1_D_IM_B2R_PIPE_COUNT] = {0,0};
#endif	// ImB2r_CO_ACT_B2R_CLOCK
#ifdef ImB2r_CO_ACT_B2R_HCLOCK
static volatile UINT32 S_G_IM_B2R_HCLK_CTRL_DISABLE[ImB2r1_D_IM_B2R_PIPE_COUNT] = {0,0};
#endif	// ImB2r_CO_ACT_B2R_HCLOCK
#ifdef ImB2r_CO_ACT_B2R_PCLOCK
static volatile UINT32 S_G_IM_B2R_PCLK_CTRL_DISABLE[ImB2r1_D_IM_B2R_PIPE_COUNT] = {0,0};
#endif	// ImB2r_CO_ACT_B2R_PCLOCK
#ifdef ImB2r_CO_ACT_B2R_ICLOCK
static volatile UINT32 S_G_IM_B2R_ICLK_CTRL_DISABLE[ImB2r1_D_IM_B2R_PIPE_COUNT] = {0,0};
#endif	// ImB2r_CO_ACT_B2R_ICLOCK


#ifdef ImB2r_CO_ACT_B2R_PCLOCK
	memset( (USHORT*)&S_G_IM_B2R_PCLK_CTRL_CNT[pipe_no], 0, sizeof(UCHAR) * size_coef );
	memset( (USHORT*)&S_G_IM_B2R_PCLK_CTRL_DISABLE[pipe_no], 0, sizeof(UINT32) * size_coef );
#endif	// ImB2r_CO_ACT_B2R_PCLOCK

static ULONG S_G_OS_USR_SPIN_LOCK __attribute__((section(".LOCK_SECTION"), aligned(64)));

/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/
static INT32 imB2rSetAccessEnable( UCHAR pipe_no, volatile TImB2rAccessEnableManage* const acc_en_mng, const UCHAR acc_enable, const UCHAR wait_enable, const CHAR errmsg[] );
//
// Access enable register manager
//
static VOID imB2rSetDekneeAccessEnable( UCHAR pipe_no, const UCHAR enable );
static VOID imB2rSetRgbKneeAccessEnable( UCHAR pipe_no, const UCHAR enable );

//
// Access enable register manager
//
static volatile TImB2rAccessEnableManage S_G_IM_B2R_DEKNEE_ACCEN_CTRL = {
	.ctrlCnt = { 0, 0 },
	.regSetFunc = imB2rSetDekneeAccessEnable,
};
static volatile TImB2rAccessEnableManage S_G_IM_B2R_RGB_KNEE_ACCEN_CTRL = {
	.ctrlCnt = { 0, 0 },
	.regSetFunc = imB2rSetRgbKneeAccessEnable,
};

/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/
// Control access enable register.
static INT32 imB2rSetAccessEnable( UCHAR pipe_no, volatile TImB2rAccessEnableManage* const acc_en_mng, const UCHAR acc_enable, const UCHAR wait_enable, const CHAR errmsg[] )
{
	INT32 ret = D_DDIM_OK;
	UCHAR cnt;
	UCHAR loop_cnt, loop_sta, loop_end;

	ImB2r2*	imB2r2=im_b2r2_get();

	im_b2r_get_loop_val( pipe_no, &loop_sta, &loop_end );

	Im_B2R_On_Pclk( pipe_no );
	Dd_ARM_Critical_Section_Start(S_G_OS_USR_SPIN_LOCK);

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		cnt = acc_en_mng->ctrlCnt[loop_cnt];
		if( acc_enable == 0 ){
			if( cnt != 0 ){
				cnt--;
				if( cnt == 0 ){
					if(  im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->YBW.YBWTRG.bit.YBWTRG != ImB2r1_D_IM_B2R_YBWTRG_IDLE ){
						// Macro busy error
						Ddim_Assertion(( errmsg ));
						ret = ImB2r_D_IM_B2R_MACRO_BUSY;
					}
					else{
						acc_en_mng->regSetFunc( loop_cnt, 0 );
					}
				}
			}
		}
		else{
			if( cnt == 0 ){
				if(  im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->YBW.YBWTRG.bit.YBWTRG != ImB2r1_D_IM_B2R_YBWTRG_IDLE ){
					// Macro busy error
					Ddim_Assertion(( errmsg ));
					ret = ImB2r_D_IM_B2R_MACRO_BUSY;
				}
				else{
					cnt++;
					acc_en_mng->regSetFunc( loop_cnt, 1 );

					if( wait_enable != ImB2r_D_IM_B2R_WAIT_OFF ){
						ImB2r1_IM_B2R_WAIT_USEC( ImB2r1_D_IM_B2R_SRAM_WAIT_USEC );
					}
				}
			}
			else if((0 < cnt) && (cnt < 255)){
				cnt++;
			}
		}
		acc_en_mng->ctrlCnt[loop_cnt] = cnt;
	}

	Dd_ARM_Critical_Section_End(S_G_OS_USR_SPIN_LOCK);
	Im_B2R_Off_Pclk( pipe_no );

	return ret;
}

static VOID imB2rSetDekneeAccessEnable( UCHAR pipe_no, const UCHAR enable )
{
	ImB2r2*	imB2r2=im_b2r2_get();

	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->B2R_CMN.RAMAEN.bit.RAMAEN_BAY_DEKNEE = enable;
}

static VOID imB2rSetRgbKneeAccessEnable( UCHAR pipe_no, const UCHAR enable )
{
	ImB2r2*	imB2r2=im_b2r2_get();

	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->B2R_CMN.RAMAEN.bit.RAMAEN_RGB_KNEE = enable;
}

/*----------------------------------------------------------------------*/
/* Grobal Function														*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
/* B2R PCLK change to ON
 */
INT32 Im_B2R_On_Pclk( UCHAR pipe_no )
{
#ifdef ImB2r_CO_ACT_B2R_PCLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > ImB2r_D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_On_Pclk error. pipe_no>ImB2r_D_IM_B2R_PIPE12\n" ));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(S_G_OS_USR_SPIN_LOCK);

	if( ImB2r1_IM_B2R_CHECK_TARGET_PIPE_NO_1( pipe_no ) ){
		Dd_Top_Start_Clock( (UCHAR*)&S_G_IM_B2R_PCLK_CTRL_CNT[0], ImB2r1_D_IM_B2R1_PCLK_REG_ADDR, ~ImB2r1_D_IM_B2R1_PCLK_REG_BIT );
	}
	if( ImB2r1_IM_B2R_CHECK_TARGET_PIPE_NO_2( pipe_no ) ){
		Dd_Top_Start_Clock( (UCHAR*)&S_G_IM_B2R_PCLK_CTRL_CNT[1], ImB2r1_D_IM_B2R2_PCLK_REG_ADDR, ~ImB2r1_D_IM_B2R2_PCLK_REG_BIT );
	}

	Dd_ARM_Critical_Section_End(S_G_OS_USR_SPIN_LOCK);
#endif	// ImB2r_CO_ACT_B2R_PCLOCK

	return D_DDIM_OK;
}

/* B2R PCLK change to OFF
 */
INT32 Im_B2R_Off_Pclk( UCHAR pipe_no )
{
#ifdef ImB2r_CO_ACT_B2R_PCLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > ImB2r_D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Off_Pclk error. pipe_no>ImB2r_D_IM_B2R_PIPE12\n" ));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(S_G_OS_USR_SPIN_LOCK);

	if( ImB2r1_IM_B2R_CHECK_TARGET_PIPE_NO_1( pipe_no ) ){
		if( S_G_IM_B2R_PCLK_CTRL_CNT[0] == 1 ) {
			if( S_G_IM_B2R_PCLK_CTRL_DISABLE[0] == 0 ) {
				Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_B2R_PCLK_CTRL_CNT[0], ImB2r1_D_IM_B2R1_PCLK_REG_ADDR, ImB2r1_D_IM_B2R1_PCLK_REG_BIT );
			}
		}
		else {
			Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_B2R_PCLK_CTRL_CNT[0], ImB2r1_D_IM_B2R1_PCLK_REG_ADDR, ImB2r1_D_IM_B2R1_PCLK_REG_BIT );
		}
	}
	if( ImB2r1_IM_B2R_CHECK_TARGET_PIPE_NO_2( pipe_no ) ){
		if( S_G_IM_B2R_PCLK_CTRL_CNT[1] == 1 ) {
			if( S_G_IM_B2R_PCLK_CTRL_DISABLE[1] == 0 ) {
				Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_B2R_PCLK_CTRL_CNT[1], ImB2r1_D_IM_B2R2_PCLK_REG_ADDR, ImB2r1_D_IM_B2R2_PCLK_REG_BIT );
			}
		}
		else {
			Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_B2R_PCLK_CTRL_CNT[1], ImB2r1_D_IM_B2R2_PCLK_REG_ADDR, ImB2r1_D_IM_B2R2_PCLK_REG_BIT );
		}
	}

	Dd_ARM_Critical_Section_End(S_G_OS_USR_SPIN_LOCK);
#endif	// CO_ACT_PCLOCK

	return D_DDIM_OK;
}

/* B2R PCLK change to OFF force
 */
INT32 Im_B2R_Force_Off_Pclk( UCHAR pipe_no )
{
#ifdef ImB2r_CO_ACT_B2R_PCLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > ImB2r_D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Force_Off_Pclk error. pipe_no>ImB2r_D_IM_B2R_PIPE12\n" ));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(S_G_OS_USR_SPIN_LOCK);

	if( ImB2r1_IM_B2R_CHECK_TARGET_PIPE_NO_1( pipe_no ) ){
		S_G_IM_B2R_PCLK_CTRL_CNT[0] = 1;
		if( S_G_IM_B2R_PCLK_CTRL_DISABLE[0] == 0 ) {
			Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_B2R_PCLK_CTRL_CNT[0], ImB2r1_D_IM_B2R1_PCLK_REG_ADDR, ImB2r1_D_IM_B2R1_PCLK_REG_BIT );
		}
	}
	if( ImB2r1_IM_B2R_CHECK_TARGET_PIPE_NO_2( pipe_no ) ){
		S_G_IM_B2R_PCLK_CTRL_CNT[1] = 1;
		if( S_G_IM_B2R_PCLK_CTRL_DISABLE[1] == 0 ) {
			Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_B2R_PCLK_CTRL_CNT[1], ImB2r1_D_IM_B2R2_PCLK_REG_ADDR, ImB2r1_D_IM_B2R2_PCLK_REG_BIT );
		}
	}

	Dd_ARM_Critical_Section_End(S_G_OS_USR_SPIN_LOCK);
#endif	// ImB2r_CO_ACT_B2R_PCLOCK

	return D_DDIM_OK;
}

VOID Im_B2R_Print_ClockStatus( VOID )
{
#ifdef ImB2r_CO_ACT_B2R_CLOCK
	Ddim_Print(( "B2R1CK=%u\n", IO_CHIPTOP.CLKSTOP10.bit.B2R1CK ));
	Ddim_Print(( "\tgIM_B2R_Clk_Ctrl_Cnt[0]      = %u\n", S_G_IM_B2R_CLK_CTRL_CNT[0] ));
	Ddim_Print(( "\tgIM_B2R_Clk_Ctrl_Disable[0]  = %u\n", S_G_IM_B2R_CLK_CTRL_DISABLE[0] ));
	Ddim_Print(( "B2R2CK=%u\n", IO_CHIPTOP.CLKSTOP12.bit.B2R2CK ));
	Ddim_Print(( "\tgIM_B2R_Clk_Ctrl_Cnt[1]      = %u\n", S_G_IM_B2R_CLK_CTRL_CNT[1] ));
	Ddim_Print(( "\tgIM_B2R_Clk_Ctrl_Disable[1]  = %u\n", S_G_IM_B2R_CLK_CTRL_DISABLE[1] ));
#endif	// ImB2r_CO_ACT_B2R_CLOCK
#ifdef ImB2r_CO_ACT_B2R_HCLOCK
	Ddim_Print(( "B2R1HCLK=%u\n", IO_CHIPTOP.CLKSTOP10.bit.B2R1AH ));
	Ddim_Print(( "\tgIM_B2R_Hclk_Ctrl_Cnt[0]     = %u\n", S_G_IM_B2R_HCLK_CTRL_CNT[0] ));
	Ddim_Print(( "\tgIM_B2R_Hclk_Ctrl_Disable[0] = %u\n", S_G_IM_B2R_HCLK_CTRL_DISABLE[0] ));
	Ddim_Print(( "B2R2HCLK=%u\n", IO_CHIPTOP.CLKSTOP12.bit.B2R2AH ));
	Ddim_Print(( "\tgIM_B2R_Hclk_Ctrl_Cnt[1]     = %u\n", S_G_IM_B2R_HCLK_CTRL_CNT[1] ));
	Ddim_Print(( "\tgIM_B2R_Hclk_Ctrl_Disable[1] = %u\n", S_G_IM_B2R_HCLK_CTRL_DISABLE[1] ));
#endif	// ImB2r_CO_ACT_B2R_HCLOCK
#ifdef ImB2r_CO_ACT_B2R_PCLOCK
	Ddim_Print(( "B2R1PCLK=%u\n", IO_CHIPTOP.CLKSTOP10.bit.B2R1AP ));
	Ddim_Print(( "\tgIM_B2R_Pclk_Ctrl_Cnt[0]     = %u\n", S_G_IM_B2R_PCLK_CTRL_CNT[0] ));
	Ddim_Print(( "\tgIM_B2R_Pclk_Ctrl_Disable[0] = %u\n", S_G_IM_B2R_PCLK_CTRL_DISABLE[0] ));
	Ddim_Print(( "B2R2PCLK=%u\n", IO_CHIPTOP.CLKSTOP12.bit.B2R2AP ));
	Ddim_Print(( "\tgIM_B2R_Pclk_Ctrl_Cnt[1]     = %u\n", S_G_IM_B2R_PCLK_CTRL_CNT[1] ));
	Ddim_Print(( "\tgIM_B2R_Pclk_Ctrl_Disable[1] = %u\n", S_G_IM_B2R_PCLK_CTRL_DISABLE[1] ));
#endif	// ImB2r_CO_ACT_B2R_PCLOCK
#ifdef ImB2r_CO_ACT_B2R_ICLOCK
	Ddim_Print(( "B2R1ICLK=%u\n", IO_CHIPTOP.CLKSTOP10.bit.B2R1AX ));
	Ddim_Print(( "\tgIM_B2R_Iclk_Ctrl_Cnt[0]     = %u\n", S_G_IM_B2R_ICLK_CTRL_CNT[0] ));
	Ddim_Print(( "\tgIM_B2R_Iclk_Ctrl_Disable[0] = %u\n", S_G_IM_B2R_ICLK_CTRL_DISABLE[0] ));
	Ddim_Print(( "B2R2ICLK=%u\n", IO_CHIPTOP.CLKSTOP12.bit.B2R2AX ));
	Ddim_Print(( "\tgIM_B2R_Iclk_Ctrl_Cnt[1]     = %u\n", S_G_IM_B2R_ICLK_CTRL_CNT[1] ));
	Ddim_Print(( "\tgIM_B2R_Iclk_Ctrl_Disable[1] = %u\n", S_G_IM_B2R_ICLK_CTRL_DISABLE[1] ));
#endif	// ImB2r_CO_ACT_B2R_ICLOCK
	Ddim_Print(( "\n" ));
}

/* B2RCLK change to ON
 */
INT32 Im_B2R_On_Clk( UCHAR pipe_no )
{
#ifdef ImB2r_CO_ACT_B2R_CLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > ImB2r_D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_On_Clk error. pipe_no>ImB2r_D_IM_B2R_PIPE12\n" ));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(S_G_OS_USR_SPIN_LOCK);

	if( ImB2r1_IM_B2R_CHECK_TARGET_PIPE_NO_1( pipe_no ) ){
		Dd_Top_Start_Clock( (UCHAR*)&S_G_IM_B2R_CLK_CTRL_CNT[0], ImB2r1_D_IM_B2R1_CLK_REG_ADDR, ~ImB2r1_D_IM_B2R1_CLK_REG_BIT );
	}
	if( ImB2r1_IM_B2R_CHECK_TARGET_PIPE_NO_2( pipe_no ) ){
		Dd_Top_Start_Clock( (UCHAR*)&S_G_IM_B2R_CLK_CTRL_CNT[1], ImB2r1_D_IM_B2R2_CLK_REG_ADDR, ~ImB2r1_D_IM_B2R2_CLK_REG_BIT );
	}

	Dd_ARM_Critical_Section_End(S_G_OS_USR_SPIN_LOCK);
#endif	// ImB2r_CO_ACT_B2R_CLOCK

	return D_DDIM_OK;
}

/* B2RCLK change to OFF
 */
INT32 Im_B2R_Off_Clk( UCHAR pipe_no )
{
#ifdef ImB2r_CO_ACT_B2R_CLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > ImB2r_D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Off_Clk error. pipe_no>ImB2r_D_IM_B2R_PIPE12\n" ));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(S_G_OS_USR_SPIN_LOCK);

	if( ImB2r1_IM_B2R_CHECK_TARGET_PIPE_NO_1( pipe_no ) ){
		if( S_G_IM_B2R_CLK_CTRL_CNT[0] == 1 ) {
			if( S_G_IM_B2R_CLK_CTRL_DISABLE[0] == 0 ) {
				Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_B2R_CLK_CTRL_CNT[0], ImB2r1_D_IM_B2R1_CLK_REG_ADDR, ImB2r1_D_IM_B2R1_CLK_REG_BIT );
			}
		}
		else {
			Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_B2R_CLK_CTRL_CNT[0], ImB2r1_D_IM_B2R1_CLK_REG_ADDR, ImB2r1_D_IM_B2R1_CLK_REG_BIT );
		}
	}
	if( ImB2r1_IM_B2R_CHECK_TARGET_PIPE_NO_2( pipe_no ) ){
		if( S_G_IM_B2R_CLK_CTRL_CNT[1] == 1 ) {
			if( S_G_IM_B2R_CLK_CTRL_DISABLE[1] == 0 ) {
				Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_B2R_CLK_CTRL_CNT[1], ImB2r1_D_IM_B2R2_CLK_REG_ADDR, ImB2r1_D_IM_B2R2_CLK_REG_BIT );
			}
		}
		else {
			Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_B2R_CLK_CTRL_CNT[1], ImB2r1_D_IM_B2R2_CLK_REG_ADDR, ImB2r1_D_IM_B2R2_CLK_REG_BIT );
		}
	}

	Dd_ARM_Critical_Section_End(S_G_OS_USR_SPIN_LOCK);
#endif	// ImB2r_CO_ACT_B2R_CLOCK

	return D_DDIM_OK;
}

/* B2RCLK change to OFF force
 */
INT32 Im_B2R_Force_Off_Clk( UCHAR pipe_no )
{
#ifdef ImB2r_CO_ACT_B2R_CLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > ImB2r_D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Force_Off_Clk error. pipe_no>ImB2r_D_IM_B2R_PIPE12\n" ));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(S_G_OS_USR_SPIN_LOCK);

	if( ImB2r1_IM_B2R_CHECK_TARGET_PIPE_NO_1( pipe_no ) ){
		S_G_IM_B2R_CLK_CTRL_CNT[0] = 1;
		if( S_G_IM_B2R_CLK_CTRL_DISABLE[0] == 0 ) {
			Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_B2R_CLK_CTRL_CNT[0], ImB2r1_D_IM_B2R1_CLK_REG_ADDR, ImB2r1_D_IM_B2R1_CLK_REG_BIT );
		}
	}
	if( ImB2r1_IM_B2R_CHECK_TARGET_PIPE_NO_2( pipe_no ) ){
		S_G_IM_B2R_CLK_CTRL_CNT[1] = 1;
		if( S_G_IM_B2R_CLK_CTRL_DISABLE[1] == 0 ) {
			Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_B2R_CLK_CTRL_CNT[1], ImB2r1_D_IM_B2R2_CLK_REG_ADDR, ImB2r1_D_IM_B2R2_CLK_REG_BIT );
		}
	}

	Dd_ARM_Critical_Section_End(S_G_OS_USR_SPIN_LOCK);
#endif	// ImB2r_CO_ACT_B2R_CLOCK

	return D_DDIM_OK;
}

/* B2R HCLK change to ON
 */
INT32 Im_B2R_On_Hclk( UCHAR pipe_no )
{
#ifdef ImB2r_CO_ACT_B2R_HCLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > ImB2r_D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_On_Hclk error. pipe_no>ImB2r_D_IM_B2R_PIPE12\n" ));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(S_G_OS_USR_SPIN_LOCK);

	if( ImB2r1_IM_B2R_CHECK_TARGET_PIPE_NO_1( pipe_no ) ){
		Dd_Top_Start_Clock( (UCHAR*)&S_G_IM_B2R_HCLK_CTRL_CNT[0], ImB2r1_D_IM_B2R1_HCLK_REG_ADDR, ~ImB2r1_D_IM_B2R1_HCLK_REG_BIT );
	}
	if( ImB2r1_IM_B2R_CHECK_TARGET_PIPE_NO_2( pipe_no ) ){
		Dd_Top_Start_Clock( (UCHAR*)&S_G_IM_B2R_HCLK_CTRL_CNT[1], ImB2r1_D_IM_B2R2_HCLK_REG_ADDR, ~ImB2r1_D_IM_B2R2_HCLK_REG_BIT );
	}

	Dd_ARM_Critical_Section_End(S_G_OS_USR_SPIN_LOCK);
#endif	// ImB2r_CO_ACT_B2R_HCLOCK

	return D_DDIM_OK;
}

/* B2R HCLK change to OFF
 */
INT32 Im_B2R_Off_Hclk( UCHAR pipe_no )
{
#ifdef ImB2r_CO_ACT_B2R_HCLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > ImB2r_D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Off_Hclk error. pipe_no>ImB2r_D_IM_B2R_PIPE12\n" ));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(S_G_OS_USR_SPIN_LOCK);

	if( ImB2r1_IM_B2R_CHECK_TARGET_PIPE_NO_1( pipe_no ) ){
		if( S_G_IM_B2R_HCLK_CTRL_CNT[0] == 1 ) {
			if( S_G_IM_B2R_HCLK_CTRL_DISABLE[0] == 0 ) {
				Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_B2R_HCLK_CTRL_CNT[0], ImB2r1_D_IM_B2R1_HCLK_REG_ADDR, ImB2r1_D_IM_B2R1_HCLK_REG_BIT );
			}
		}
		else {
			Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_B2R_HCLK_CTRL_CNT[0], ImB2r1_D_IM_B2R1_HCLK_REG_ADDR, ImB2r1_D_IM_B2R1_HCLK_REG_BIT );
		}
	}
	if( ImB2r1_IM_B2R_CHECK_TARGET_PIPE_NO_2( pipe_no ) ){
		if( S_G_IM_B2R_HCLK_CTRL_CNT[1] == 1 ) {
			if( S_G_IM_B2R_HCLK_CTRL_DISABLE[1] == 0 ) {
				Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_B2R_HCLK_CTRL_CNT[1], ImB2r1_D_IM_B2R2_HCLK_REG_ADDR, ImB2r1_D_IM_B2R2_HCLK_REG_BIT );
			}
		}
		else {
			Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_B2R_HCLK_CTRL_CNT[1], ImB2r1_D_IM_B2R2_HCLK_REG_ADDR, ImB2r1_D_IM_B2R2_HCLK_REG_BIT );
		}
	}

	Dd_ARM_Critical_Section_End(S_G_OS_USR_SPIN_LOCK);
#endif	// ImB2r_CO_ACT_B2R_HCLOCK

	return D_DDIM_OK;
}

/* B2R HCLK change to OFF force
 */
INT32 Im_B2R_Force_Off_Hclk( UCHAR pipe_no )
{
#ifdef ImB2r_CO_ACT_B2R_HCLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > ImB2r_D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Force_Off_Hclk error. pipe_no>ImB2r_D_IM_B2R_PIPE12\n" ));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(S_G_OS_USR_SPIN_LOCK);

	if( ImB2r1_IM_B2R_CHECK_TARGET_PIPE_NO_1( pipe_no ) ){
		S_G_IM_B2R_HCLK_CTRL_CNT[0] = 1;
		if( S_G_IM_B2R_HCLK_CTRL_DISABLE[0] == 0 ) {
			Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_B2R_HCLK_CTRL_CNT[0], ImB2r1_D_IM_B2R1_HCLK_REG_ADDR, ImB2r1_D_IM_B2R1_HCLK_REG_BIT );
		}
	}
	if( ImB2r1_IM_B2R_CHECK_TARGET_PIPE_NO_2( pipe_no ) ){
		S_G_IM_B2R_HCLK_CTRL_CNT[1] = 1;
		if( S_G_IM_B2R_HCLK_CTRL_DISABLE[1] == 0 ) {
			Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_B2R_HCLK_CTRL_CNT[1], ImB2r1_D_IM_B2R2_HCLK_REG_ADDR, ImB2r1_D_IM_B2R2_HCLK_REG_BIT );
		}
	}

	Dd_ARM_Critical_Section_End(S_G_OS_USR_SPIN_LOCK);
#endif	// ImB2r_CO_ACT_B2R_HCLOCK

	return D_DDIM_OK;
}

/* B2R ICLK change to ON
 */
INT32 Im_B2R_On_Iclk( UCHAR pipe_no )
{
#ifdef ImB2r_CO_ACT_B2R_ICLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > ImB2r_D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_On_Iclk error. pipe_no>ImB2r_D_IM_B2R_PIPE12\n" ));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(S_G_OS_USR_SPIN_LOCK);

	if( ImB2r1_IM_B2R_CHECK_TARGET_PIPE_NO_1( pipe_no ) ){
		Dd_Top_Start_Clock( (UCHAR*)&S_G_IM_B2R_ICLK_CTRL_CNT[0], ImB2r1_D_IM_B2R1_ICLK_REG_ADDR, ~ImB2r1_D_IM_B2R1_ICLK_REG_BIT );
	}
	if( ImB2r1_IM_B2R_CHECK_TARGET_PIPE_NO_2( pipe_no ) ){
		Dd_Top_Start_Clock( (UCHAR*)&S_G_IM_B2R_ICLK_CTRL_CNT[1], ImB2r1_D_IM_B2R2_ICLK_REG_ADDR, ~ImB2r1_D_IM_B2R2_ICLK_REG_BIT );
	}

	Dd_ARM_Critical_Section_End(S_G_OS_USR_SPIN_LOCK);
#endif	// ImB2r_CO_ACT_B2R_ICLOCK

	return D_DDIM_OK;
}


/* B2R ICLK change to OFF
 */
INT32 Im_B2R_Off_Iclk( UCHAR pipe_no )
{
#ifdef ImB2r_CO_ACT_B2R_ICLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > ImB2r_D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Off_Iclk error. pipe_no>ImB2r_D_IM_B2R_PIPE12\n" ));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(S_G_OS_USR_SPIN_LOCK);

	if( ImB2r1_IM_B2R_CHECK_TARGET_PIPE_NO_1( pipe_no ) ){
		if( S_G_IM_B2R_ICLK_CTRL_CNT[0] == 1 ) {
			if( S_G_IM_B2R_ICLK_CTRL_DISABLE[0] == 0 ) {
				Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_B2R_ICLK_CTRL_CNT[0], ImB2r1_D_IM_B2R1_ICLK_REG_ADDR, ImB2r1_D_IM_B2R1_ICLK_REG_BIT );
			}
		}
		else {
			Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_B2R_ICLK_CTRL_CNT[0], ImB2r1_D_IM_B2R1_ICLK_REG_ADDR, ImB2r1_D_IM_B2R1_ICLK_REG_BIT );
		}
	}
	if( ImB2r1_IM_B2R_CHECK_TARGET_PIPE_NO_2( pipe_no ) ){
		if( S_G_IM_B2R_ICLK_CTRL_CNT[1] == 1 ) {
			if( S_G_IM_B2R_ICLK_CTRL_DISABLE[1] == 0 ) {
				Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_B2R_ICLK_CTRL_CNT[1], ImB2r1_D_IM_B2R2_ICLK_REG_ADDR, ImB2r1_D_IM_B2R2_ICLK_REG_BIT );
			}
		}
		else {
			Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_B2R_ICLK_CTRL_CNT[1], ImB2r1_D_IM_B2R2_ICLK_REG_ADDR, ImB2r1_D_IM_B2R2_ICLK_REG_BIT );
		}
	}

	Dd_ARM_Critical_Section_End(S_G_OS_USR_SPIN_LOCK);
#endif	// ImB2r_CO_ACT_B2R_ICLOCK

	return D_DDIM_OK;
}

/* B2R ICLK change to OFF force
 */
INT32 Im_B2R_Force_Off_Iclk( UCHAR pipe_no )
{
#ifdef ImB2r_CO_ACT_B2R_ICLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > ImB2r_D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Force_Off_Iclk error. pipe_no>ImB2r_D_IM_B2R_PIPE12\n" ));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(S_G_OS_USR_SPIN_LOCK);

	if( ImB2r1_IM_B2R_CHECK_TARGET_PIPE_NO_1( pipe_no ) ){
		S_G_IM_B2R_ICLK_CTRL_CNT[0] = 1;
		if( S_G_IM_B2R_ICLK_CTRL_DISABLE[0] == 0 ) {
			Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_B2R_ICLK_CTRL_CNT[0], ImB2r1_D_IM_B2R1_ICLK_REG_ADDR, ImB2r1_D_IM_B2R1_ICLK_REG_BIT );
		}
	}
	if( ImB2r1_IM_B2R_CHECK_TARGET_PIPE_NO_2( pipe_no ) ){
		S_G_IM_B2R_ICLK_CTRL_CNT[1] = 1;
		if( S_G_IM_B2R_ICLK_CTRL_DISABLE[1] == 0 ) {
			Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_B2R_ICLK_CTRL_CNT[1], ImB2r1_D_IM_B2R2_ICLK_REG_ADDR, ImB2r1_D_IM_B2R2_ICLK_REG_BIT );
		}
	}

	Dd_ARM_Critical_Section_End(S_G_OS_USR_SPIN_LOCK);
#endif	// ImB2r_CO_ACT_B2R_ICLOCK

	return D_DDIM_OK;
}

/* Set Bayer Deknee access enable
 */
INT32 Im_B2R_Set_DekneeAccessEnable( UCHAR pipe_no, UCHAR access_enable, UCHAR wait_enable )
{
#ifdef CO_PARAM_CHECK
	// check on input pointer
	if( pipe_no > ImB2r_D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Set_DekneeAccessEnable error. pipe_no>ImB2r_D_IM_B2R_PIPE12\n" ));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
#endif

	return imB2rSetAccessEnable( pipe_no,
									 &S_G_IM_B2R_DEKNEE_ACCEN_CTRL,
									 access_enable,
									 wait_enable,
									 ImB2r1_M_IM_B2R_ASSETION_MSG( "Im_B2R_Set_DekneeAccessEnable error. Macro busy\n" )
									);
}

/* Set RGB Knee access enable
 */
INT32 Im_B2R_Set_RGB_KneeAccessEnable( UCHAR pipe_no, UCHAR access_enable, UCHAR wait_enable )
{
#ifdef CO_PARAM_CHECK
	// check on input pointer
	if( pipe_no > ImB2r_D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Set_RGB_KneeAccessEnable error. pipe_no>ImB2r_D_IM_B2R_PIPE12\n" ));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
#endif

	return imB2rSetAccessEnable( pipe_no,
									 &S_G_IM_B2R_RGB_KNEE_ACCEN_CTRL,
									 access_enable,
									 wait_enable,
									 ImB2r1_M_IM_B2R_ASSETION_MSG( "Im_B2R_Set_RGB_KneeAccessEnable error. Macro busy\n" )
									);
}

//因为变量共享，用函数来调用变量
void im_b2r_for_g_im_b2r_clk_ctrl_cnt_disable(UCHAR pipe_no,UCHAR size_coef)
{
	// Initialize of PCLK/HCLK/CLK control information
	#ifdef ImB2r_CO_ACT_B2R_CLOCK
		memset( (USHORT*)&S_G_IM_B2R_CLK_CTRL_CNT[pipe_no], 0, sizeof(UCHAR) * size_coef );
		memset( (USHORT*)&S_G_IM_B2R_CLK_CTRL_DISABLE[pipe_no], 0, sizeof(UINT32) * size_coef );
	#endif	// ImB2r_CO_ACT_B2R_CLOCK

	#ifdef ImB2r_CO_ACT_B2R_HCLOCK
		memset( (USHORT*)&S_G_IM_B2R_HCLK_CTRL_CNT[pipe_no], 0, sizeof(UCHAR) * size_coef );
		memset( (USHORT*)&S_G_IM_B2R_HCLK_CTRL_DISABLE[pipe_no], 0, sizeof(UINT32) * size_coef );
	#endif	// ImB2r_CO_ACT_B2R_HCLOCK
	#ifdef ImB2r_CO_ACT_B2R_ICLOCK
		memset( (USHORT*)&S_G_IM_B2R_ICLK_CTRL_CNT[pipe_no], 0, sizeof(UCHAR) * size_coef );
		memset( (USHORT*)&S_G_IM_B2R_ICLK_CTRL_DISABLE[pipe_no], 0, sizeof(UINT32) * size_coef );
	#endif	// ImB2r_CO_ACT_B2R_ICLOCK
}

ImB2r *im_b2r_new(void)
{
	ImB2r* self = k_object_new_with_private(IM_TYPE_B2R,sizeof(ImB2rPrivate));
		return self;
}
