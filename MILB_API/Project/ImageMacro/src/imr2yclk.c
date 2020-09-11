/*
 * imr2yclk.c
 *
 *  Created on: 2020年9月2日
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

#include "imr2yclk.h"
#include "dd_arm.h"
#include "dd_top.h"
#include "imr2yutils.h"
#include "imr2y.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImR2yClk, im_r2y_clk);
#define IM_R2Y_CLK_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImR2yClkPrivate, IM_TYPE_R2Y_CLK))


#if defined(CO_ACT_CLOCK) || defined(CO_ACT_IMAGE_CLOCK)
#define CO_ACT_R2Y_CLOCK
#endif	// CO_ACT_PCLOCK
#if defined(CO_ACT_HCLOCK) || defined(CO_ACT_IMAGE_HCLOCK)
#define CO_ACT_R2Y_HCLOCK
#endif	// CO_ACT_HCLOCK
#if defined(CO_ACT_PCLOCK) || defined(CO_ACT_IMAGE_PCLOCK)
#define CO_ACT_R2Y_PCLOCK
#endif	// CO_ACT_PCLOCK
#if defined(CO_ACT_ICLOCK) || defined(CO_ACT_IMAGE_ICLOCK)
#define CO_ACT_R2Y_ICLOCK
#endif	// CO_ACT_ICLOCK

#define D_IM_R2Y1_CLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP11())
#define D_IM_R2Y1_HCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP11())
#define D_IM_R2Y1_PCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP11())
#define D_IM_R2Y1_ICLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP11())

#define D_IM_R2Y2_CLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP13())
#define D_IM_R2Y2_HCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP13())
#define D_IM_R2Y2_PCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP13())
#define D_IM_R2Y2_ICLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP13())

#define D_IM_R2Y1_CLK_REG_BIT	D_DD_TOP_R2Y1CK_BIT
#define D_IM_R2Y1_HCLK_REG_BIT	D_DD_TOP_R2Y1AH_BIT
#define D_IM_R2Y1_PCLK_REG_BIT	D_DD_TOP_R2Y1AP_BIT
#define D_IM_R2Y1_ICLK_REG_BIT	D_DD_TOP_R2Y1AX_BIT

#define D_IM_R2Y2_CLK_REG_BIT	D_DD_TOP_R2Y2CK_BIT
#define D_IM_R2Y2_HCLK_REG_BIT	D_DD_TOP_R2Y2AH_BIT
#define D_IM_R2Y2_PCLK_REG_BIT	D_DD_TOP_R2Y2AP_BIT
#define D_IM_R2Y2_ICLK_REG_BIT	D_DD_TOP_R2Y2AX_BIT


// Clock control counter
#ifdef CO_ACT_R2Y_CLOCK
static volatile UCHAR gIM_R2Y_Clk_Ctrl_Cnt[D_IM_R2Y_PIPE_COUNT] = {0,0};
#endif	// CO_ACT_R2Y_CLOCK
#ifdef CO_ACT_R2Y_HCLOCK
static volatile UCHAR gIM_R2Y_Hclk_Ctrl_Cnt[D_IM_R2Y_PIPE_COUNT] = {0,0};
#endif	// CO_ACT_R2Y_HCLOCK
#ifdef CO_ACT_R2Y_PCLOCK
static volatile UCHAR gIM_R2Y_Pclk_Ctrl_Cnt[D_IM_R2Y_PIPE_COUNT] = {0,0};
#endif	// CO_ACT_R2Y_PCLOCK
#ifdef CO_ACT_R2Y_ICLOCK
static volatile UCHAR gIM_R2Y_Iclk_Ctrl_Cnt[D_IM_R2Y_PIPE_COUNT] = {0,0};
#endif	// CO_ACT_R2Y_ICLOCK

// clock off control is disabled(for register dump on debugger)
#ifdef CO_ACT_R2Y_CLOCK
static volatile UINT32 gIM_R2Y_Clk_Ctrl_Disable[D_IM_R2Y_PIPE_COUNT] = {0,0};
#endif	// CO_ACT_R2Y_CLOCK
#ifdef CO_ACT_R2Y_HCLOCK
static volatile UINT32 gIM_R2Y_Hclk_Ctrl_Disable[D_IM_R2Y_PIPE_COUNT] = {0,0};
#endif	// CO_ACT_R2Y_HCLOCK
#ifdef CO_ACT_R2Y_PCLOCK
static volatile UINT32 gIM_R2Y_Pclk_Ctrl_Disable[D_IM_R2Y_PIPE_COUNT] = {0,0};
#endif	// CO_ACT_R2Y_PCLOCK
#ifdef CO_ACT_R2Y_ICLOCK
static volatile UINT32 gIM_R2Y_Iclk_Ctrl_Disable[D_IM_R2Y_PIPE_COUNT] = {0,0};
#endif	// CO_ACT_R2Y_ICLOCK

static ULONG gOsUsr_Spin_Lock __attribute__((section(".LOCK_SECTION"), aligned(64)));


struct _ImR2yClkPrivate
{
	int a;
};

/*
 * IMPL
 */
static void im_r2y_clk_constructor(ImR2yClk *self)
{
//	ImR2yClkPrivate *priv = IM_R2Y_CLK_GET_PRIVATE(self);
}

static void im_r2y_clk_destructor(ImR2yClk *self)
{
//	ImR2yClkPrivate *priv = IM_R2Y_CLK_GET_PRIVATE(self);
}


/*
 * PUBLIC
 */
// Initialize of PCLK/HCLK/CLK control information
void im_r2y_clk_manager_init(ImR2yClk *self,UCHAR pipe_no, UCHAR size_coef)
{
#ifdef CO_ACT_R2Y_CLOCK
	memset( (USHORT*)&gIM_R2Y_Clk_Ctrl_Cnt[pipe_no], 0, sizeof(gIM_R2Y_Clk_Ctrl_Cnt) * size_coef );
	memset( (USHORT*)&gIM_R2Y_Clk_Ctrl_Disable[pipe_no], 0, sizeof(gIM_R2Y_Clk_Ctrl_Disable) * size_coef );
#endif	// CO_ACT_R2Y_CLOCK
	#ifdef CO_ACT_R2Y_PCLOCK
		memset( (USHORT*)&gIM_R2Y_Pclk_Ctrl_Cnt[pipe_no], 0, sizeof(gIM_R2Y_Pclk_Ctrl_Cnt) * size_coef );
		memset( (USHORT*)&gIM_R2Y_Pclk_Ctrl_Disable[pipe_no], 0, sizeof(gIM_R2Y_Pclk_Ctrl_Disable) * size_coef );
	#endif	// CO_ACT_R2Y_PCLOCK
#ifdef CO_ACT_R2Y_HCLOCK
	memset( (USHORT*)&gIM_R2Y_Hclk_Ctrl_Cnt[pipe_no], 0, sizeof(gIM_R2Y_Hclk_Ctrl_Cnt) * size_coef );
	memset( (USHORT*)&gIM_R2Y_Hclk_Ctrl_Disable[pipe_no], 0, sizeof(gIM_R2Y_Hclk_Ctrl_Disable) * size_coef );
#endif	// CO_ACT_R2Y_HCLOCK
#ifdef CO_ACT_R2Y_ICLOCK
	memset( (USHORT*)&gIM_R2Y_Iclk_Ctrl_Cnt[pipe_no], 0, sizeof(gIM_R2Y_Iclk_Ctrl_Cnt) * size_coef );
	memset( (USHORT*)&gIM_R2Y_Iclk_Ctrl_Disable[pipe_no], 0, sizeof(gIM_R2Y_Iclk_Ctrl_Disable) * size_coef );
#endif	// CO_ACT_R2Y_ICLOCK

}

void im_r2y_clk_ddim_print(ImR2yClk *self)
{
#ifdef CO_ACT_R2Y_CLOCK
	Ddim_Print(( "R2Y1CK=%u\n", IO_CHIPTOP.CLKSTOP11.bit.R2Y1CK ));
	Ddim_Print(( "\tgIM_R2Y_Clk_Ctrl_Cnt[0]      = %u\n", gIM_R2Y_Clk_Ctrl_Cnt[0] ));
	Ddim_Print(( "\tgIM_R2Y_Clk_Ctrl_Disable[0]  = %u\n", gIM_R2Y_Clk_Ctrl_Disable[0] ));
	Ddim_Print(( "R2Y2CK=%u\n", IO_CHIPTOP.CLKSTOP13.bit.R2Y2CK ));
	Ddim_Print(( "\tgIM_R2Y_Clk_Ctrl_Cnt[1]      = %u\n", gIM_R2Y_Clk_Ctrl_Cnt[1] ));
	Ddim_Print(( "\tgIM_R2Y_Clk_Ctrl_Disable[1]  = %u\n", gIM_R2Y_Clk_Ctrl_Disable[1] ));
#endif	// CO_ACT_R2Y_CLOCK
#ifdef CO_ACT_R2Y_HCLOCK
	Ddim_Print(( "R2Y1HCLK=%u\n", IO_CHIPTOP.CLKSTOP11.bit.R2Y1AH ));
	Ddim_Print(( "\tgIM_R2Y_Hclk_Ctrl_Cnt[0]     = %u\n", gIM_R2Y_Hclk_Ctrl_Cnt[0] ));
	Ddim_Print(( "\tgIM_R2Y_Hclk_Ctrl_Disable[0] = %u\n", gIM_R2Y_Hclk_Ctrl_Disable[0] ));
	Ddim_Print(( "R2Y2HCLK=%u\n", IO_CHIPTOP.CLKSTOP13.bit.R2Y2AH ));
	Ddim_Print(( "\tgIM_R2Y_Hclk_Ctrl_Cnt[1]     = %u\n", gIM_R2Y_Hclk_Ctrl_Cnt[1] ));
	Ddim_Print(( "\tgIM_R2Y_Hclk_Ctrl_Disable[1] = %u\n", gIM_R2Y_Hclk_Ctrl_Disable[1] ));
#endif	// CO_ACT_R2Y_HCLOCK


	#ifdef CO_ACT_R2Y_PCLOCK
		Ddim_Print(( "R2Y1PCLK=%u\n", IO_CHIPTOP.CLKSTOP11.bit.R2Y1AP ));
		Ddim_Print(( "\tgIM_R2Y_Pclk_Ctrl_Cnt[0]     = %u\n", gIM_R2Y_Pclk_Ctrl_Cnt[0] ));
		Ddim_Print(( "\tgIM_R2Y_Pclk_Ctrl_Disable[0] = %u\n", gIM_R2Y_Pclk_Ctrl_Disable[0] ));
		Ddim_Print(( "R2Y2PCLK=%u\n", IO_CHIPTOP.CLKSTOP13.bit.R2Y2AP ));
		Ddim_Print(( "\tgIM_R2Y_Pclk_Ctrl_Cnt[1]     = %u\n", gIM_R2Y_Pclk_Ctrl_Cnt[1] ));
		Ddim_Print(( "\tgIM_R2Y_Pclk_Ctrl_Disable[1] = %u\n", gIM_R2Y_Pclk_Ctrl_Disable[1] ));
	#endif	// CO_ACT_R2Y_PCLOCK

#ifdef CO_ACT_R2Y_ICLOCK
	Ddim_Print(( "R2Y1ICLK=%u\n", IO_CHIPTOP.CLKSTOP11.bit.R2Y1AX ));
	Ddim_Print(( "\tgIM_R2Y_Iclk_Ctrl_Cnt[0]     = %u\n", gIM_R2Y_Iclk_Ctrl_Cnt[0] ));
	Ddim_Print(( "\tgIM_R2Y_Iclk_Ctrl_Disable[0] = %u\n", gIM_R2Y_Iclk_Ctrl_Disable[0] ));
	Ddim_Print(( "R2Y2ICLK=%u\n", IO_CHIPTOP.CLKSTOP13.bit.R2Y2AX ));
	Ddim_Print(( "\tgIM_R2Y_Iclk_Ctrl_Cnt[1]     = %u\n", gIM_R2Y_Iclk_Ctrl_Cnt[1] ));
	Ddim_Print(( "\tgIM_R2Y_Iclk_Ctrl_Disable[1] = %u\n", gIM_R2Y_Iclk_Ctrl_Disable[1] ));
#endif	// CO_ACT_R2Y_ICLOCK
	Ddim_Print(( "\n" ));

}

/* R2Y PCLK change to ON
 */
INT32 im_r2y_clk_on_pclk(ImR2yClk *self, UCHAR pipe_no )
{
#ifdef CO_ACT_R2Y_PCLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_clk_on_pclk error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(gOsUsr_Spin_Lock);

	if( im_r2y_check_target_pipe_no_1( pipe_no ) ){
		Dd_Top_Start_Clock( (UCHAR*)&gIM_R2Y_Pclk_Ctrl_Cnt[0], D_IM_R2Y1_PCLK_REG_ADDR, ~D_IM_R2Y1_PCLK_REG_BIT );
	}
	if( im_r2y_check_target_pipe_no_2( pipe_no ) ){
		Dd_Top_Start_Clock( (UCHAR*)&gIM_R2Y_Pclk_Ctrl_Cnt[1], D_IM_R2Y2_PCLK_REG_ADDR, ~D_IM_R2Y2_PCLK_REG_BIT );
	}

	Dd_ARM_Critical_Section_End(gOsUsr_Spin_Lock);
#endif	// CO_ACT_R2Y_PCLOCK

	return D_DDIM_OK;
}

/* R2Y PCLK change to OFF
 */
INT32 im_r2y_clk_off_pclk(ImR2yClk *self, UCHAR pipe_no )
{
#ifdef CO_ACT_R2Y_PCLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_clk_off_pclk error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(gOsUsr_Spin_Lock);

	if( im_r2y_check_target_pipe_no_1( pipe_no ) ){
		if( gIM_R2Y_Pclk_Ctrl_Cnt[0] == 1 ) {
			if( gIM_R2Y_Pclk_Ctrl_Disable[0] == 0 ) {
				Dd_Top_Stop_Clock( (UCHAR*)&gIM_R2Y_Pclk_Ctrl_Cnt[0], D_IM_R2Y1_PCLK_REG_ADDR, D_IM_R2Y1_PCLK_REG_BIT );
			}
		}
		else {
			Dd_Top_Stop_Clock( (UCHAR*)&gIM_R2Y_Pclk_Ctrl_Cnt[0], D_IM_R2Y1_PCLK_REG_ADDR, D_IM_R2Y1_PCLK_REG_BIT );
		}
	}
	if( im_r2y_check_target_pipe_no_2( pipe_no ) ){
		if( gIM_R2Y_Pclk_Ctrl_Cnt[1] == 1 ) {
			if( gIM_R2Y_Pclk_Ctrl_Disable[1] == 0 ) {
				Dd_Top_Stop_Clock( (UCHAR*)&gIM_R2Y_Pclk_Ctrl_Cnt[1], D_IM_R2Y2_PCLK_REG_ADDR, D_IM_R2Y2_PCLK_REG_BIT );
			}
		}
		else {
			Dd_Top_Stop_Clock( (UCHAR*)&gIM_R2Y_Pclk_Ctrl_Cnt[1], D_IM_R2Y2_PCLK_REG_ADDR, D_IM_R2Y2_PCLK_REG_BIT );
		}
	}

	Dd_ARM_Critical_Section_End(gOsUsr_Spin_Lock);
#endif	// CO_ACT_PCLOCK

	return D_DDIM_OK;
}

/* R2Y PCLK change to OFF force
 */
INT32 im_r2y_clk_force_off_pclk(ImR2yClk *self, UCHAR pipe_no )
{
#ifdef CO_ACT_R2Y_PCLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_clk_force_off_pclk error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(gOsUsr_Spin_Lock);

	if( im_r2y_check_target_pipe_no_1( pipe_no ) ){
		gIM_R2Y_Pclk_Ctrl_Cnt[0] = 1;
		if( gIM_R2Y_Pclk_Ctrl_Disable[0] == 0 ) {
			Dd_Top_Stop_Clock( (UCHAR*)&gIM_R2Y_Pclk_Ctrl_Cnt[0], D_IM_R2Y1_PCLK_REG_ADDR, D_IM_R2Y1_PCLK_REG_BIT );
		}
	}
	if( im_r2y_check_target_pipe_no_2( pipe_no ) ){
		gIM_R2Y_Pclk_Ctrl_Cnt[1] = 1;
		if( gIM_R2Y_Pclk_Ctrl_Disable[1] == 0 ) {
			Dd_Top_Stop_Clock( (UCHAR*)&gIM_R2Y_Pclk_Ctrl_Cnt[1], D_IM_R2Y2_PCLK_REG_ADDR, D_IM_R2Y2_PCLK_REG_BIT );
		}
	}

	Dd_ARM_Critical_Section_End(gOsUsr_Spin_Lock);
#endif	// CO_ACT_R2Y_PCLOCK

	return D_DDIM_OK;
}

/* R2Y HCLK change to ON
 */
INT32 im_r2y_clk_on_hclk(ImR2yClk *self, UCHAR pipe_no )
{
#ifdef CO_ACT_R2Y_HCLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_clk_on_hclk error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(gOsUsr_Spin_Lock);

	if( im_r2y_check_target_pipe_no_1( pipe_no ) ){
		//TODO 查到这
		Dd_Top_Start_Clock( (UCHAR*)&gIM_R2Y_Hclk_Ctrl_Cnt[0], D_IM_R2Y1_HCLK_REG_ADDR, ~D_IM_R2Y1_HCLK_REG_BIT );
	}
	if( im_r2y_check_target_pipe_no_2( pipe_no ) ){
		Dd_Top_Start_Clock( (UCHAR*)&gIM_R2Y_Hclk_Ctrl_Cnt[1], D_IM_R2Y2_HCLK_REG_ADDR, ~D_IM_R2Y2_HCLK_REG_BIT );
	}

	Dd_ARM_Critical_Section_End(gOsUsr_Spin_Lock);
#endif	// CO_ACT_R2Y_HCLOCK

	return D_DDIM_OK;
}

/* R2Y HCLK change to OFF
 */
INT32 im_r2y_clk_off_hclk(ImR2yClk *self, UCHAR pipe_no )
{
#ifdef CO_ACT_R2Y_HCLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_clk_off_hclk error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(gOsUsr_Spin_Lock);

	if( im_r2y_check_target_pipe_no_1( pipe_no ) ){
		if( gIM_R2Y_Hclk_Ctrl_Cnt[0] == 1 ) {
			if( gIM_R2Y_Hclk_Ctrl_Disable[0] == 0 ) {
				Dd_Top_Stop_Clock( (UCHAR*)&gIM_R2Y_Hclk_Ctrl_Cnt[0], D_IM_R2Y1_HCLK_REG_ADDR, D_IM_R2Y1_HCLK_REG_BIT );
			}
		}
		else {
			Dd_Top_Stop_Clock( (UCHAR*)&gIM_R2Y_Hclk_Ctrl_Cnt[0], D_IM_R2Y1_HCLK_REG_ADDR, D_IM_R2Y1_HCLK_REG_BIT );
		}
	}
	if( im_r2y_check_target_pipe_no_2( pipe_no ) ){
		if( gIM_R2Y_Hclk_Ctrl_Cnt[1] == 1 ) {
			if( gIM_R2Y_Hclk_Ctrl_Disable[1] == 0 ) {
				Dd_Top_Stop_Clock( (UCHAR*)&gIM_R2Y_Hclk_Ctrl_Cnt[1], D_IM_R2Y2_HCLK_REG_ADDR, D_IM_R2Y2_HCLK_REG_BIT );
			}
		}
		else {
			Dd_Top_Stop_Clock( (UCHAR*)&gIM_R2Y_Hclk_Ctrl_Cnt[1], D_IM_R2Y2_HCLK_REG_ADDR, D_IM_R2Y2_HCLK_REG_BIT );
		}
	}

	Dd_ARM_Critical_Section_End(gOsUsr_Spin_Lock);
#endif	// CO_ACT_R2Y_HCLOCK

	return D_DDIM_OK;
}

/* R2Y HCLK change to OFF force
 */
INT32 im_r2y_clk_force_off_hclk(ImR2yClk *self, UCHAR pipe_no )
{
#ifdef CO_ACT_R2Y_HCLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_clk_force_off_hclk error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(gOsUsr_Spin_Lock);

	if( im_r2y_check_target_pipe_no_1( pipe_no ) ){
		gIM_R2Y_Hclk_Ctrl_Cnt[0] = 1;
		if( gIM_R2Y_Hclk_Ctrl_Disable[0] == 0 ) {
			Dd_Top_Stop_Clock( (UCHAR*)&gIM_R2Y_Hclk_Ctrl_Cnt[0], D_IM_R2Y1_HCLK_REG_ADDR, D_IM_R2Y1_HCLK_REG_BIT );
		}
	}
	if( im_r2y_check_target_pipe_no_2( pipe_no ) ){
		gIM_R2Y_Hclk_Ctrl_Cnt[1] = 1;
		if( gIM_R2Y_Hclk_Ctrl_Disable[1] == 0 ) {
			Dd_Top_Stop_Clock( (UCHAR*)&gIM_R2Y_Hclk_Ctrl_Cnt[1], D_IM_R2Y2_HCLK_REG_ADDR, D_IM_R2Y2_HCLK_REG_BIT );
		}
	}

	Dd_ARM_Critical_Section_End(gOsUsr_Spin_Lock);
#endif	// CO_ACT_R2Y_HCLOCK

	return D_DDIM_OK;
}

/* R2Y ICLK change to ON
 */
INT32 im_r2y_clk_on_iclk(ImR2yClk *self, UCHAR pipe_no )
{
#ifdef CO_ACT_R2Y_ICLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_clk_on_iclk error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(gOsUsr_Spin_Lock);

	if( im_r2y_check_target_pipe_no_1( pipe_no ) ){
		Dd_Top_Start_Clock( (UCHAR*)&gIM_R2Y_Iclk_Ctrl_Cnt[0], D_IM_R2Y1_ICLK_REG_ADDR, ~D_IM_R2Y1_ICLK_REG_BIT );
	}
	if( im_r2y_check_target_pipe_no_2( pipe_no ) ){
		Dd_Top_Start_Clock( (UCHAR*)&gIM_R2Y_Iclk_Ctrl_Cnt[1], D_IM_R2Y2_ICLK_REG_ADDR, ~D_IM_R2Y2_ICLK_REG_BIT );
	}

	Dd_ARM_Critical_Section_End(gOsUsr_Spin_Lock);
#endif	// CO_ACT_R2Y_ICLOCK

	return D_DDIM_OK;
}

/* R2Y ICLK change to OFF
 */
INT32 im_r2y_clk_off_iclk(ImR2yClk *self, UCHAR pipe_no )
{
#ifdef CO_ACT_R2Y_ICLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_clk_off_iclk error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(gOsUsr_Spin_Lock);

	if( im_r2y_check_target_pipe_no_1( pipe_no ) ){
		if( gIM_R2Y_Iclk_Ctrl_Cnt[0] == 1 ) {
			if( gIM_R2Y_Iclk_Ctrl_Disable[0] == 0 ) {
				Dd_Top_Stop_Clock( (UCHAR*)&gIM_R2Y_Iclk_Ctrl_Cnt[0], D_IM_R2Y1_ICLK_REG_ADDR, D_IM_R2Y1_ICLK_REG_BIT );
			}
		}
		else {
			Dd_Top_Stop_Clock( (UCHAR*)&gIM_R2Y_Iclk_Ctrl_Cnt[0], D_IM_R2Y1_ICLK_REG_ADDR, D_IM_R2Y1_ICLK_REG_BIT );
		}
	}
	if( im_r2y_check_target_pipe_no_2( pipe_no ) ){
		if( gIM_R2Y_Iclk_Ctrl_Cnt[1] == 1 ) {
			if( gIM_R2Y_Iclk_Ctrl_Disable[1] == 0 ) {
				Dd_Top_Stop_Clock( (UCHAR*)&gIM_R2Y_Iclk_Ctrl_Cnt[1], D_IM_R2Y2_ICLK_REG_ADDR, D_IM_R2Y2_ICLK_REG_BIT );
			}
		}
		else {
			Dd_Top_Stop_Clock( (UCHAR*)&gIM_R2Y_Iclk_Ctrl_Cnt[1], D_IM_R2Y2_ICLK_REG_ADDR, D_IM_R2Y2_ICLK_REG_BIT );
		}
	}

	Dd_ARM_Critical_Section_End(gOsUsr_Spin_Lock);
#endif	// CO_ACT_R2Y_ICLOCK

	return D_DDIM_OK;
}

/* R2Y ICLK change to OFF force
 */
INT32 im_r2y_clk_force_off_iclk(ImR2yClk *self, UCHAR pipe_no )
{
#ifdef CO_ACT_R2Y_ICLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_clk_force_off_iclk error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(gOsUsr_Spin_Lock);

	if( im_r2y_check_target_pipe_no_1( pipe_no ) ){
		gIM_R2Y_Iclk_Ctrl_Cnt[0] = 1;
		if( gIM_R2Y_Iclk_Ctrl_Disable[0] == 0 ) {
			Dd_Top_Stop_Clock( (UCHAR*)&gIM_R2Y_Iclk_Ctrl_Cnt[0], D_IM_R2Y1_ICLK_REG_ADDR, D_IM_R2Y1_ICLK_REG_BIT );
		}
	}
	if( im_r2y_check_target_pipe_no_2( pipe_no ) ){
		gIM_R2Y_Iclk_Ctrl_Cnt[1] = 1;
		if( gIM_R2Y_Iclk_Ctrl_Disable[1] == 0 ) {
			Dd_Top_Stop_Clock( (UCHAR*)&gIM_R2Y_Iclk_Ctrl_Cnt[1], D_IM_R2Y2_ICLK_REG_ADDR, D_IM_R2Y2_ICLK_REG_BIT );
		}
	}

	Dd_ARM_Critical_Section_End(gOsUsr_Spin_Lock);
#endif	// CO_ACT_R2Y_ICLOCK

	return D_DDIM_OK;
}

/* R2YCLK change to ON
 */
INT32 im_r2y_clk_on_clk(ImR2yClk *self, UCHAR pipe_no )
{
#ifdef CO_ACT_R2Y_CLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_clk_on_clk error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(gOsUsr_Spin_Lock);

	if( im_r2y_check_target_pipe_no_1( pipe_no ) ){
		Dd_Top_Start_Clock( (UCHAR*)&gIM_R2Y_Clk_Ctrl_Cnt[0], D_IM_R2Y1_CLK_REG_ADDR, ~D_IM_R2Y1_CLK_REG_BIT );
	}
	if( im_r2y_check_target_pipe_no_2( pipe_no ) ){
		Dd_Top_Start_Clock( (UCHAR*)&gIM_R2Y_Clk_Ctrl_Cnt[1], D_IM_R2Y2_CLK_REG_ADDR, ~D_IM_R2Y2_CLK_REG_BIT );
	}

	Dd_ARM_Critical_Section_End(gOsUsr_Spin_Lock);
#endif	// CO_ACT_R2Y_CLOCK

	return D_DDIM_OK;
}

/* R2YCLK change to OFF
 */
INT32 im_r2y_clk_off_clk(ImR2yClk *self, UCHAR pipe_no )
{
#ifdef CO_ACT_R2Y_CLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_clk_off_clk error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(gOsUsr_Spin_Lock);

	if( im_r2y_check_target_pipe_no_1( pipe_no ) ){
		if( gIM_R2Y_Clk_Ctrl_Cnt[0] == 1 ) {
			if( gIM_R2Y_Clk_Ctrl_Disable[0] == 0 ) {
				Dd_Top_Stop_Clock( (UCHAR*)&gIM_R2Y_Clk_Ctrl_Cnt[0], D_IM_R2Y1_CLK_REG_ADDR, D_IM_R2Y1_CLK_REG_BIT );
			}
		}
		else {
			Dd_Top_Stop_Clock( (UCHAR*)&gIM_R2Y_Clk_Ctrl_Cnt[0], D_IM_R2Y1_CLK_REG_ADDR, D_IM_R2Y1_CLK_REG_BIT );
		}
	}
	if( im_r2y_check_target_pipe_no_2( pipe_no ) ){
		if( gIM_R2Y_Clk_Ctrl_Cnt[1] == 1 ) {
			if( gIM_R2Y_Clk_Ctrl_Disable[1] == 0 ) {
				Dd_Top_Stop_Clock( (UCHAR*)&gIM_R2Y_Clk_Ctrl_Cnt[1], D_IM_R2Y2_CLK_REG_ADDR, D_IM_R2Y2_CLK_REG_BIT );
			}
		}
		else {
			Dd_Top_Stop_Clock( (UCHAR*)&gIM_R2Y_Clk_Ctrl_Cnt[1], D_IM_R2Y2_CLK_REG_ADDR, D_IM_R2Y2_CLK_REG_BIT );
		}
	}

	Dd_ARM_Critical_Section_End(gOsUsr_Spin_Lock);
#endif	// CO_ACT_R2Y_CLOCK

	return D_DDIM_OK;
}

/* R2YCLK change to OFF force
 */
INT32 im_r2y_clk_force_off_clk(ImR2yClk *self, UCHAR pipe_no )
{
#ifdef CO_ACT_R2Y_CLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_clk_force_off_clk error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(gOsUsr_Spin_Lock);

	if( im_r2y_check_target_pipe_no_1( pipe_no ) ){
		gIM_R2Y_Clk_Ctrl_Cnt[0] = 1;
		if( gIM_R2Y_Clk_Ctrl_Disable[0] == 0 ) {
			Dd_Top_Stop_Clock( (UCHAR*)&gIM_R2Y_Clk_Ctrl_Cnt[0], D_IM_R2Y1_CLK_REG_ADDR, D_IM_R2Y1_CLK_REG_BIT );
		}
	}
	if( im_r2y_check_target_pipe_no_2( pipe_no ) ){
		gIM_R2Y_Clk_Ctrl_Cnt[1] = 1;
		if( gIM_R2Y_Clk_Ctrl_Disable[1] == 0 ) {
			Dd_Top_Stop_Clock( (UCHAR*)&gIM_R2Y_Clk_Ctrl_Cnt[1], D_IM_R2Y2_CLK_REG_ADDR, D_IM_R2Y2_CLK_REG_BIT );
		}
	}

	Dd_ARM_Critical_Section_End(gOsUsr_Spin_Lock);
#endif	// CO_ACT_R2Y_CLOCK

	return D_DDIM_OK;
}

ImR2yClk *im_r2y_clk_new(void)
{
	ImR2yClk* self = k_object_new_with_private(IM_TYPE_R2Y_CLK,sizeof(ImR2yClkPrivate));
	return self;
}

