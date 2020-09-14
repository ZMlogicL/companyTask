/*
*@Copyright (C) 2070-2020 上海网用软件有限公司

*@date                :2020-08-04
*@author              :刘应春
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*7、
*2、
*@version
*7.0.0 2020年06月开始开发
*/


#include <string.h>
//#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
//#endif
#include "dd_arm.h"

#include "jdsltm.h"
#include "imltmcommon.h"

typedef struct _ImLtmCommonPrivate ImLtmCommonPrivate;
 struct _ImLtmCommonPrivate
{
	int a;
};

K_TYPE_DEFINE_DERIVED(ImLtmCommonPrivate, im_ltm_common, sizeof(ImLtmCommonPrivate),K_TYPE_OBJECT)
#define IM_LTM_COMMON_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImLtmCommonPrivate, IM_TYPE_LTM_COMMON))

#if defined(CO_ACT_CLOCK) || defined(CO_ACT_IMAGE_CLOCK)
#define ImLtmCommon_CO_ACT_LTM_CLOCK
#define ImLtmCommon_CO_ACT_LTMRBK_CLOCK
#endif	// CO_ACT_CLOCK
#if defined(CO_ACT_HCLOCK) || defined(CO_ACT_IMAGE_HCLOCK)
#define ImLtmCommon_CO_ACT_LTM_HCLOCK
#endif	// CO_ACT_HCLOCK
#if defined(CO_ACT_PCLOCK) || defined(CO_ACT_IMAGE_PCLOCK)
#define ImLtmCommon_CO_ACT_LTM_PCLOCK
#endif	// CO_ACT_PCLOCK
#if defined(CO_ACT_ICLOCK) || defined(CO_ACT_IMAGE_ICLOCK)
#define ImLtmCommon_CO_ACT_LTM_ACLOCK
#endif	// CO_ACT_ICLOCK

#define ImLtmCommon_IM_LTM_DSB()	Dd_ARM_Dsb_Pou()

#define ImLtmCommon_D_IM_LTM1_RBKCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP10())
#define ImLtmCommon_D_IM_LTM1_CLK_REG_ADDR		(&Dd_Top_Get_CLKSTOP11())
#define ImLtmCommon_D_IM_LTM1_HCLK_REG_ADDR		(&Dd_Top_Get_CLKSTOP11())
#define ImLtmCommon_D_IM_LTM1_PCLK_REG_ADDR		(&Dd_Top_Get_CLKSTOP11())
#define ImLtmCommon_D_IM_LTM1_ACLK_REG_ADDR		(&Dd_Top_Get_CLKSTOP11())

#define ImLtmCommon_D_IM_LTM2_RBKCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP12())
#define ImLtmCommon_D_IM_LTM2_CLK_REG_ADDR		(&Dd_Top_Get_CLKSTOP13())
#define ImLtmCommon_D_IM_LTM2_HCLK_REG_ADDR		(&Dd_Top_Get_CLKSTOP13())
#define ImLtmCommon_D_IM_LTM2_PCLK_REG_ADDR		(&Dd_Top_Get_CLKSTOP13())
#define ImLtmCommon_D_IM_LTM2_ACLK_REG_ADDR		(&Dd_Top_Get_CLKSTOP13())

#define ImLtmCommon_D_IM_LTM1_RBKCLK_REG_BIT	D_DD_TOP_LTMRBK1CK_BIT
#define ImLtmCommon_D_IM_LTM1_CLK_REG_BIT		D_DD_TOP_LTM1CK_BIT
#define ImLtmCommon_D_IM_LTM1_HCLK_REG_BIT		D_DD_TOP_LTM1AH_BIT
#define ImLtmCommon_D_IM_LTM1_PCLK_REG_BIT		D_DD_TOP_LTM1AP_BIT
#define ImLtmCommon_D_IM_LTM1_ACLK_REG_BIT		D_DD_TOP_LTM1AX_BIT

#define ImLtmCommon_D_IM_LTM2_RBKCLK_REG_BIT	D_DD_TOP_LTMRBK2CK_BIT
#define ImLtmCommon_D_IM_LTM2_CLK_REG_BIT		D_DD_TOP_LTM2CK_BIT
#define ImLtmCommon_D_IM_LTM2_HCLK_REG_BIT		D_DD_TOP_LTM2AH_BIT
#define ImLtmCommon_D_IM_LTM2_PCLK_REG_BIT		D_DD_TOP_LTM2AP_BIT
#define ImLtmCommon_D_IM_LTM2_ACLK_REG_BIT		D_DD_TOP_LTM2AX_BIT

// PIPE count
#define ImLtmCommon_D_IM_LTM_PIPE_COUNT				(2)

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
// Nothing Special
#endif	// CO_DDIM_UTILITY_USE

/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
#define ImLtmCommon_CHECK_TARGET_PIPR_NO_1(a)		(((a) + 1) & (D_IM_LTM_PIPE1 + 1))
#define ImLtmCommon_CHECK_TARGET_PIPR_NO_2(a)		(((a) + 1) & (D_IM_LTM_PIPE2 + 1))

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
// Nothing Special
#endif	// CO_DDIM_UTILITY_USE

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
// Nothing Special

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
// Nothing Special
#endif	// CO_DDIM_UTILITY_USE

/*----------------------------------------------------------------------*/
/* Structure  															*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
// Nothing Special

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
// Nothing Special
#endif	// CO_DDIM_UTILITY_USE

 /*----------------------------------------------------------------------*/
 /* Global Data															*/
 /*----------------------------------------------------------------------*/
 //---------------------- driver  section -------------------------------
 // Clock control counter
 #ifdef ImLtmCommon_CO_ACT_LTM_CLOCK
 static volatile UCHAR S_GIM_LTM_CLK_CTRL_CNT[ImLtmCommon_D_IM_LTM_PIPE_COUNT] = {0,0};
 static volatile UCHAR S_GIM_LTM_RBKCLK_CTRL_CNT[ImLtmCommon_D_IM_LTM_PIPE_COUNT] = {0,0};
 #endif	// ImLtmCommon_CO_ACT_LTM_CLOCK
 #ifdef ImLtmCommon_CO_ACT_LTM_HCLOCK
 static volatile UCHAR S_GIM_LTM_HCLK_CTRL_CNT[ImLtmCommon_D_IM_LTM_PIPE_COUNT] = {0,0};
 #endif	// ImLtmCommon_CO_ACT_LTM_HCLOCK
 #ifdef ImLtmCommon_CO_ACT_LTM_PCLOCK
 static volatile UCHAR S_GIM_LTM_PCLK_CTRL_CNT[ImLtmCommon_D_IM_LTM_PIPE_COUNT] = {0,0};
 #endif	// ImLtmCommon_CO_ACT_LTM_PCLOCK
 #ifdef ImLtmCommon_CO_ACT_LTM_ACLOCK
 static volatile UCHAR S_GIM_LTM_ACLK_CTRL_CNT[ImLtmCommon_D_IM_LTM_PIPE_COUNT] = {0,0};
 #endif	// ImLtmCommon_CO_ACT_LTM_ACLOCK

 // clock off control is disabled(for register dump on debugger)
 #ifdef ImLtmCommon_CO_ACT_LTM_CLOCK
 static volatile UINT32 S_GIM_LTM_CLK_CTRL_DISABLE[ImLtmCommon_D_IM_LTM_PIPE_COUNT] = {0,0};
 static volatile UINT32 S_GIM_LTM_RBKCLK_CTRL_DISABLE[ImLtmCommon_D_IM_LTM_PIPE_COUNT] = {0,0};
 #endif	// ImLtmCommon_CO_ACT_LTM_CLOCK
 #ifdef ImLtmCommon_CO_ACT_LTM_HCLOCK
 static volatile UINT32 S_GIM_LTM_HCLK_CTRL_DISABLE[ImLtmCommon_D_IM_LTM_PIPE_COUNT] = {0,0};
 #endif	// ImLtmCommon_CO_ACT_LTM_HCLOCK
 #ifdef ImLtmCommon_CO_ACT_LTM_PCLOCK
 static volatile UINT32 S_GIM_LTM_PCLK_CTRL_DISABLE[ImLtmCommon_D_IM_LTM_PIPE_COUNT] = {0,0};
 #endif	// ImLtmCommon_CO_ACT_LTM_PCLOCK
 #ifdef ImLtmCommon_CO_ACT_LTM_ACLOCK
 static volatile UINT32 S_GIM_LTM_ACLK_CTRL_DISABLE[ImLtmCommon_D_IM_LTM_PIPE_COUNT] = {0,0};
 #endif	// ImLtmCommon_CO_ACT_LTM_ACLOCK

 #if defined(ImLtmCommon_CO_ACT_LTM_CLOCK) || defined(ImLtmCommon_CO_ACT_LTM_ACLOCK) || defined(ImLtmCommon_CO_ACT_LTM_HCLOCK) || defined(ImLtmCommon_CO_ACT_LTM_PCLOCK)
 static ULONG S_GOSUSR_SPIN_LOCK __attribute__((section(".LOCK_SECTION"), aligned(64)));
 #endif	// defined(ImLtmCommon_CO_ACT_LTM_CLOCK) || defined(ImLtmCommon_CO_ACT_LTM_ACLOCK) || defined(ImLtmCommon_CO_ACT_LTM_HCLOCK) || defined(ImLtmCommon_CO_ACT_LTM_PCLOCK)

 #ifdef CO_DDIM_UTILITY_USE
 //---------------------- utility section -------------------------------
 // Nothing Special
 //---------------------- colabo  section -------------------------------
 // Nothing Special
 #endif	// CO_DDIM_UTILITY_USE

 /*----------------------------------------------------------------------*/
 /* Macro																*/
 /*----------------------------------------------------------------------*/
 //---------------------- driver  section -------------------------------
 #ifdef CO_DDIM_UTILITY_USE
 //---------------------- utility section -------------------------------
 // Nothing Special
 //---------------------- colabo  section -------------------------------
 // Nothing Special
 #endif	// CO_DDIM_UTILITY_USE

 /*----------------------------------------------------------------------*/
 /* Function																*/
 /*----------------------------------------------------------------------*/
 //---------------------- driver  section -------------------------------
 #ifdef CO_DDIM_UTILITY_USE
 //---------------------- utility section -------------------------------
 // Nothing Special
 //---------------------- colabo  section -------------------------------
 // Nothing Special
 #endif	// CO_DDIM_UTILITY_USE

 /*----------------------------------------------------------------------*/
 /* Local Function														*/
 /*----------------------------------------------------------------------*/
 //---------------------- driver  section -------------------------------
 // Nothing Special
 #ifdef CO_DDIM_UTILITY_USE
 //---------------------- utility section -------------------------------
 // Nothing Special
 //---------------------- colabo  section -------------------------------
 // Nothing Special
 #endif	// CO_DDIM_UTILITY_USE

 #ifdef CO_DDIM_UTILITY_USE
 //---------------------- utility section -------------------------------
 // Nothing Special
 //---------------------- colabo  section -------------------------------
 // Nothing Special
 #endif	// CO_DDIM_UTILITY_USE

 /*----------------------------------------------------------------------*/
 /* Grobal Function														*/
 /*----------------------------------------------------------------------*/
 //---------------------- driver  section -------------------------------

static void im_ltm_common_constructor(ImLtmCommonPrivate *self)
{
	ImLtmCommonPrivate *priv = IM_LTM_COMMON_GET_PRIVATE(self);
	priv-> a =  0;
}

static void im_ltm_common_destructor(ImLtmCommonPrivate *self)
{
	ImLtmCommonPrivate *priv = IM_LTM_COMMON_GET_PRIVATE(self);
	priv-> a =  0;
}

/* LTM PCLK change to ON
 */
INT32 im_ltm_common_on_pclk( UCHAR pipe_no )
{
#ifdef ImLtmCommon_CO_ACT_LTM_PCLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_common_on_pclk error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(S_GOSUSR_SPIN_LOCK);

	if( ImLtmCommon_CHECK_TARGET_PIPR_NO_1( pipe_no ) ){
		Dd_Top_Start_Clock( (UCHAR*)&S_GIM_LTM_PCLK_CTRL_CNT[0], ImLtmCommon_D_IM_LTM1_PCLK_REG_ADDR, ~ImLtmCommon_D_IM_LTM1_PCLK_REG_BIT );
	}
	if( ImLtmCommon_CHECK_TARGET_PIPR_NO_2( pipe_no ) ){
		Dd_Top_Start_Clock( (UCHAR*)&S_GIM_LTM_PCLK_CTRL_CNT[1], ImLtmCommon_D_IM_LTM2_PCLK_REG_ADDR, ~ImLtmCommon_D_IM_LTM2_PCLK_REG_BIT );
	}

	Dd_ARM_Critical_Section_End(S_GOSUSR_SPIN_LOCK);
#endif	// ImLtmCommon_CO_ACT_LTM_PCLOCK

	return D_DDIM_OK;
}

/* LTM PCLK change to OFF
 */
INT32 im_ltm_common_off_pclk( UCHAR pipe_no )
{
#ifdef ImLtmCommon_CO_ACT_LTM_PCLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_common_off_pclk error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(S_GOSUSR_SPIN_LOCK);

	if( ImLtmCommon_CHECK_TARGET_PIPR_NO_1( pipe_no ) ){
		if( S_GIM_LTM_PCLK_CTRL_CNT[0] == 1 ) {
			if( S_GIM_LTM_PCLK_CTRL_DISABLE[0] == 0 ) {
				Dd_Top_Stop_Clock( (UCHAR*)&S_GIM_LTM_PCLK_CTRL_CNT[0], ImLtmCommon_D_IM_LTM1_PCLK_REG_ADDR, ImLtmCommon_D_IM_LTM1_PCLK_REG_BIT );
			}
		}
		else {
			Dd_Top_Stop_Clock( (UCHAR*)&S_GIM_LTM_PCLK_CTRL_CNT[0], ImLtmCommon_D_IM_LTM1_PCLK_REG_ADDR, ImLtmCommon_D_IM_LTM1_PCLK_REG_BIT );
		}
	}
	if( ImLtmCommon_CHECK_TARGET_PIPR_NO_2( pipe_no ) ){
		if( S_GIM_LTM_PCLK_CTRL_CNT[1] == 1 ) {
			if( S_GIM_LTM_PCLK_CTRL_DISABLE[1] == 0 ) {
				Dd_Top_Stop_Clock( (UCHAR*)&S_GIM_LTM_PCLK_CTRL_CNT[1], ImLtmCommon_D_IM_LTM2_PCLK_REG_ADDR, ImLtmCommon_D_IM_LTM2_PCLK_REG_BIT );
			}
		}
		else {
			Dd_Top_Stop_Clock( (UCHAR*)&S_GIM_LTM_PCLK_CTRL_CNT[1], ImLtmCommon_D_IM_LTM2_PCLK_REG_ADDR, ImLtmCommon_D_IM_LTM2_PCLK_REG_BIT );
		}
	}

	Dd_ARM_Critical_Section_End(S_GOSUSR_SPIN_LOCK);
#endif	// ImLtmCommon_CO_ACT_LTM_PCLOCK

	return D_DDIM_OK;
}

/* LTM PCLK change to OFF force
 */
INT32 im_ltm_common_force_off_pclk( UCHAR pipe_no )
{
#ifdef ImLtmCommon_CO_ACT_LTM_PCLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_common_force_off_pclk error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(S_GOSUSR_SPIN_LOCK);

	if( ImLtmCommon_CHECK_TARGET_PIPR_NO_1( pipe_no ) ){
		S_GIM_LTM_PCLK_CTRL_CNT[0] = 1;
		if( S_GIM_LTM_PCLK_CTRL_DISABLE[0] == 0 ) {
			Dd_Top_Stop_Clock( (UCHAR*)&S_GIM_LTM_PCLK_CTRL_CNT[0], ImLtmCommon_D_IM_LTM1_PCLK_REG_ADDR, ImLtmCommon_D_IM_LTM1_PCLK_REG_BIT );
		}
	}
	if( ImLtmCommon_CHECK_TARGET_PIPR_NO_2( pipe_no ) ){
		S_GIM_LTM_PCLK_CTRL_CNT[1] = 1;
		if( S_GIM_LTM_PCLK_CTRL_DISABLE[1] == 0 ) {
			Dd_Top_Stop_Clock( (UCHAR*)&S_GIM_LTM_PCLK_CTRL_CNT[1], ImLtmCommon_D_IM_LTM2_PCLK_REG_ADDR, ImLtmCommon_D_IM_LTM2_PCLK_REG_BIT );
		}
	}

	Dd_ARM_Critical_Section_End(S_GOSUSR_SPIN_LOCK);
#endif	// ImLtmCommon_CO_ACT_LTM_PCLOCK

	return D_DDIM_OK;
}

/* LTM HCLK change to ON
 */
INT32 im_ltm_common_on_hclk( UCHAR pipe_no )
{
#ifdef ImLtmCommon_CO_ACT_LTM_HCLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_common_on_hclk error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(S_GOSUSR_SPIN_LOCK);

	if( ImLtmCommon_CHECK_TARGET_PIPR_NO_1( pipe_no ) ){
		Dd_Top_Start_Clock( (UCHAR*)&S_GIM_LTM_HCLK_CTRL_CNT[0], ImLtmCommon_D_IM_LTM1_HCLK_REG_ADDR, ~ImLtmCommon_D_IM_LTM1_HCLK_REG_BIT );
	}
	if( ImLtmCommon_CHECK_TARGET_PIPR_NO_2( pipe_no ) ){
		Dd_Top_Start_Clock( (UCHAR*)&S_GIM_LTM_HCLK_CTRL_CNT[1], ImLtmCommon_D_IM_LTM2_HCLK_REG_ADDR, ~ImLtmCommon_D_IM_LTM2_HCLK_REG_BIT );
	}

	Dd_ARM_Critical_Section_End(S_GOSUSR_SPIN_LOCK);
#endif	// ImLtmCommon_CO_ACT_LTM_HCLOCK

	return D_DDIM_OK;
}

/* LTM HCLK change to OFF
 */
INT32 im_ltm_common_off_hclk( UCHAR pipe_no )
{
#ifdef ImLtmCommon_CO_ACT_LTM_HCLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_common_off_hclk error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(S_GOSUSR_SPIN_LOCK);

	if( ImLtmCommon_CHECK_TARGET_PIPR_NO_1( pipe_no ) ){
		if( S_GIM_LTM_HCLK_CTRL_CNT[0] == 1 ) {
			if( S_GIM_LTM_HCLK_CTRL_DISABLE[0] == 0 ) {
				Dd_Top_Stop_Clock( (UCHAR*)&S_GIM_LTM_HCLK_CTRL_CNT[0], ImLtmCommon_D_IM_LTM1_HCLK_REG_ADDR, ImLtmCommon_D_IM_LTM1_HCLK_REG_BIT );
			}
		}
		else {
			Dd_Top_Stop_Clock( (UCHAR*)&S_GIM_LTM_HCLK_CTRL_CNT[0], ImLtmCommon_D_IM_LTM1_HCLK_REG_ADDR, ImLtmCommon_D_IM_LTM1_HCLK_REG_BIT );
		}
	}
	if( ImLtmCommon_CHECK_TARGET_PIPR_NO_2( pipe_no ) ){
		if( S_GIM_LTM_HCLK_CTRL_CNT[1] == 1 ) {
			if( S_GIM_LTM_HCLK_CTRL_DISABLE[1] == 0 ) {
				Dd_Top_Stop_Clock( (UCHAR*)&S_GIM_LTM_HCLK_CTRL_CNT[1], ImLtmCommon_D_IM_LTM2_HCLK_REG_ADDR, ImLtmCommon_D_IM_LTM2_HCLK_REG_BIT );
			}
		}
		else {
			Dd_Top_Stop_Clock( (UCHAR*)&S_GIM_LTM_HCLK_CTRL_CNT[1], ImLtmCommon_D_IM_LTM2_HCLK_REG_ADDR, ImLtmCommon_D_IM_LTM2_HCLK_REG_BIT );
		}
	}

	Dd_ARM_Critical_Section_End(S_GOSUSR_SPIN_LOCK);
#endif	// ImLtmCommon_CO_ACT_LTM_HCLOCK

	return D_DDIM_OK;
}

/* LTM HCLK change to OFF force
 */
INT32 im_ltm_common_force_off_hclk( UCHAR pipe_no )
{
#ifdef ImLtmCommon_CO_ACT_LTM_HCLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_common_force_off_hclk error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(S_GOSUSR_SPIN_LOCK);

	if( ImLtmCommon_CHECK_TARGET_PIPR_NO_1( pipe_no ) ){
		S_GIM_LTM_HCLK_CTRL_CNT[0] = 1;
		if( S_GIM_LTM_HCLK_CTRL_DISABLE[0] == 0 ) {
			Dd_Top_Stop_Clock( (UCHAR*)&S_GIM_LTM_HCLK_CTRL_CNT[0], ImLtmCommon_D_IM_LTM1_HCLK_REG_ADDR, ImLtmCommon_D_IM_LTM1_HCLK_REG_BIT );
		}
	}
	if( ImLtmCommon_CHECK_TARGET_PIPR_NO_2( pipe_no ) ){
		S_GIM_LTM_HCLK_CTRL_CNT[1] = 1;
		if( S_GIM_LTM_HCLK_CTRL_DISABLE[1] == 0 ) {
			Dd_Top_Stop_Clock( (UCHAR*)&S_GIM_LTM_HCLK_CTRL_CNT[1], ImLtmCommon_D_IM_LTM2_HCLK_REG_ADDR, ImLtmCommon_D_IM_LTM2_HCLK_REG_BIT );
		}
	}

	Dd_ARM_Critical_Section_End(S_GOSUSR_SPIN_LOCK);
#endif	// ImLtmCommon_CO_ACT_LTM_HCLOCK

	return D_DDIM_OK;
}

/* LTM ACLK change to ON
 */
INT32 im_ltm_common_on_aclk( UCHAR pipe_no )
{
#ifdef ImLtmCommon_CO_ACT_LTM_ACLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_common_on_aclk error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(S_GOSUSR_SPIN_LOCK);

	if( ImLtmCommon_CHECK_TARGET_PIPR_NO_1( pipe_no ) ){
		Dd_Top_Start_Clock( (UCHAR*)&S_GIM_LTM_ACLK_CTRL_CNT[0], ImLtmCommon_D_IM_LTM1_ACLK_REG_ADDR, ~ImLtmCommon_D_IM_LTM1_ACLK_REG_BIT );
	}
	if( ImLtmCommon_CHECK_TARGET_PIPR_NO_2( pipe_no ) ){
		Dd_Top_Start_Clock( (UCHAR*)&S_GIM_LTM_ACLK_CTRL_CNT[1], ImLtmCommon_D_IM_LTM2_ACLK_REG_ADDR, ~ImLtmCommon_D_IM_LTM2_ACLK_REG_BIT );
	}

	Dd_ARM_Critical_Section_End(S_GOSUSR_SPIN_LOCK);
#endif	// ImLtmCommon_CO_ACT_LTM_ACLOCK

	return D_DDIM_OK;
}

/* LTM ACLK change to OFF
 */
INT32 im_ltm_common_off_aclk( UCHAR pipe_no )
{
#ifdef ImLtmCommon_CO_ACT_LTM_ACLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_common_off_aclk error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(S_GOSUSR_SPIN_LOCK);

	if( ImLtmCommon_CHECK_TARGET_PIPR_NO_1( pipe_no ) ){
		if( S_GIM_LTM_ACLK_CTRL_CNT[0] == 1 ) {
			if( S_GIM_LTM_ACLK_CTRL_DISABLE[0] == 0 ) {
				Dd_Top_Stop_Clock( (UCHAR*)&S_GIM_LTM_ACLK_CTRL_CNT[0], ImLtmCommon_D_IM_LTM1_ACLK_REG_ADDR, ImLtmCommon_D_IM_LTM1_ACLK_REG_BIT );
			}
		}
		else {
			Dd_Top_Stop_Clock( (UCHAR*)&S_GIM_LTM_ACLK_CTRL_CNT[0], ImLtmCommon_D_IM_LTM1_ACLK_REG_ADDR, ImLtmCommon_D_IM_LTM1_ACLK_REG_BIT );
		}
	}
	if( ImLtmCommon_CHECK_TARGET_PIPR_NO_2( pipe_no ) ){
		if( S_GIM_LTM_ACLK_CTRL_CNT[1] == 1 ) {
			if( S_GIM_LTM_ACLK_CTRL_DISABLE[1] == 0 ) {
				Dd_Top_Stop_Clock( (UCHAR*)&S_GIM_LTM_ACLK_CTRL_CNT[1], ImLtmCommon_D_IM_LTM2_ACLK_REG_ADDR, ImLtmCommon_D_IM_LTM2_ACLK_REG_BIT );
			}
		}
		else {
			Dd_Top_Stop_Clock( (UCHAR*)&S_GIM_LTM_ACLK_CTRL_CNT[1], ImLtmCommon_D_IM_LTM2_ACLK_REG_ADDR, ImLtmCommon_D_IM_LTM2_ACLK_REG_BIT );
		}
	}

	Dd_ARM_Critical_Section_End(S_GOSUSR_SPIN_LOCK);
#endif	// ImLtmCommon_CO_ACT_LTM_ACLOCK

	return D_DDIM_OK;
}

/* LTM ACLK change to OFF force
 */
INT32 im_ltm_common_force_off_aclk( UCHAR pipe_no )
{
#ifdef ImLtmCommon_CO_ACT_LTM_ACLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_common_force_off_aclk error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(S_GOSUSR_SPIN_LOCK);

	if( ImLtmCommon_CHECK_TARGET_PIPR_NO_1( pipe_no ) ){
		S_GIM_LTM_ACLK_CTRL_CNT[0] = 1;
		if( S_GIM_LTM_ACLK_CTRL_DISABLE[0] == 0 ) {
			Dd_Top_Stop_Clock( (UCHAR*)&S_GIM_LTM_ACLK_CTRL_CNT[0], ImLtmCommon_D_IM_LTM1_ACLK_REG_ADDR, ImLtmCommon_D_IM_LTM1_ACLK_REG_BIT );
		}
	}
	if( ImLtmCommon_CHECK_TARGET_PIPR_NO_2( pipe_no ) ){
		S_GIM_LTM_ACLK_CTRL_CNT[1] = 1;
		if( S_GIM_LTM_ACLK_CTRL_DISABLE[1] == 0 ) {
			Dd_Top_Stop_Clock( (UCHAR*)&S_GIM_LTM_ACLK_CTRL_CNT[1], ImLtmCommon_D_IM_LTM2_ACLK_REG_ADDR, ImLtmCommon_D_IM_LTM2_ACLK_REG_BIT );
		}
	}

	Dd_ARM_Critical_Section_End(S_GOSUSR_SPIN_LOCK);
#endif	// ImLtmCommon_CO_ACT_LTM_ACLOCK

	return D_DDIM_OK;
}

/* LTMCLK change to ON
 */
INT32 im_ltm_common_on_clk( UCHAR pipe_no )
{
#ifdef ImLtmCommon_CO_ACT_LTM_CLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_common_on_clk error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(S_GOSUSR_SPIN_LOCK);

	if( ImLtmCommon_CHECK_TARGET_PIPR_NO_1( pipe_no ) ){
		Dd_Top_Start_Clock( (UCHAR*)&S_GIM_LTM_CLK_CTRL_CNT[0], ImLtmCommon_D_IM_LTM1_CLK_REG_ADDR, ~ImLtmCommon_D_IM_LTM1_CLK_REG_BIT );
	}
	if( ImLtmCommon_CHECK_TARGET_PIPR_NO_2( pipe_no ) ){
		Dd_Top_Start_Clock( (UCHAR*)&S_GIM_LTM_CLK_CTRL_CNT[1], ImLtmCommon_D_IM_LTM2_CLK_REG_ADDR, ~ImLtmCommon_D_IM_LTM2_CLK_REG_BIT );
	}

	Dd_ARM_Critical_Section_End(S_GOSUSR_SPIN_LOCK);
#endif	// ImLtmCommon_CO_ACT_LTM_CLOCK

	return D_DDIM_OK;
}

/* LTMCLK change to OFF
 */
INT32 im_ltm_common_off_clk( UCHAR pipe_no )
{
#ifdef ImLtmCommon_CO_ACT_LTM_CLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_common_off_clk error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(S_GOSUSR_SPIN_LOCK);

	if( ImLtmCommon_CHECK_TARGET_PIPR_NO_1( pipe_no ) ){
		if( S_GIM_LTM_CLK_CTRL_CNT[0] == 1 ) {
			if( S_GIM_LTM_CLK_CTRL_DISABLE[0] == 0 ) {
				Dd_Top_Stop_Clock( (UCHAR*)&S_GIM_LTM_CLK_CTRL_CNT[0], ImLtmCommon_D_IM_LTM1_CLK_REG_ADDR, ImLtmCommon_D_IM_LTM1_CLK_REG_BIT );
			}
		}
		else {
			Dd_Top_Stop_Clock( (UCHAR*)&S_GIM_LTM_CLK_CTRL_CNT[0], ImLtmCommon_D_IM_LTM1_CLK_REG_ADDR, ImLtmCommon_D_IM_LTM1_CLK_REG_BIT );
		}
	}
	if( ImLtmCommon_CHECK_TARGET_PIPR_NO_2( pipe_no ) ){
		if( S_GIM_LTM_CLK_CTRL_CNT[1] == 1 ) {
			if( S_GIM_LTM_CLK_CTRL_DISABLE[1] == 0 ) {
				Dd_Top_Stop_Clock( (UCHAR*)&S_GIM_LTM_CLK_CTRL_CNT[1], ImLtmCommon_D_IM_LTM2_CLK_REG_ADDR, ImLtmCommon_D_IM_LTM2_CLK_REG_BIT );
			}
		}
		else {
			Dd_Top_Stop_Clock( (UCHAR*)&S_GIM_LTM_CLK_CTRL_CNT[1], ImLtmCommon_D_IM_LTM2_CLK_REG_ADDR, ImLtmCommon_D_IM_LTM2_CLK_REG_BIT );
		}
	}

	Dd_ARM_Critical_Section_End(S_GOSUSR_SPIN_LOCK);
#endif	// ImLtmCommon_CO_ACT_LTM_CLOCK

	return D_DDIM_OK;
}

/* LTMCLK change to OFF force
 */
INT32 im_ltm_common_force_off_clk( UCHAR pipe_no )
{
#ifdef ImLtmCommon_CO_ACT_LTM_CLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_common_force_off_clk error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(S_GOSUSR_SPIN_LOCK);

	if( ImLtmCommon_CHECK_TARGET_PIPR_NO_1( pipe_no ) ){
		S_GIM_LTM_CLK_CTRL_CNT[0] = 1;
		if( S_GIM_LTM_CLK_CTRL_DISABLE[0] == 0 ) {
			Dd_Top_Stop_Clock( (UCHAR*)&S_GIM_LTM_CLK_CTRL_CNT[0], ImLtmCommon_D_IM_LTM1_CLK_REG_ADDR, ImLtmCommon_D_IM_LTM1_CLK_REG_BIT );
		}
	}
	if( ImLtmCommon_CHECK_TARGET_PIPR_NO_2( pipe_no ) ){
		S_GIM_LTM_CLK_CTRL_CNT[1] = 1;
		if( S_GIM_LTM_CLK_CTRL_DISABLE[1] == 0 ) {
			Dd_Top_Stop_Clock( (UCHAR*)&S_GIM_LTM_CLK_CTRL_CNT[1], ImLtmCommon_D_IM_LTM2_CLK_REG_ADDR, ImLtmCommon_D_IM_LTM2_CLK_REG_BIT );
		}
	}

	Dd_ARM_Critical_Section_End(S_GOSUSR_SPIN_LOCK);
#endif	// ImLtmCommon_CO_ACT_LTM_CLOCK

	return D_DDIM_OK;
}

/* LTMRBKCLK change to ON
 */
INT32 im_ltm_common_on_rbkclk( UCHAR pipe_no )
{
#ifdef ImLtmCommon_CO_ACT_LTM_CLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_common_on_rbkclk error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(S_GOSUSR_SPIN_LOCK);

	if( ImLtmCommon_CHECK_TARGET_PIPR_NO_1( pipe_no ) ){
		Dd_Top_Start_Clock( (UCHAR*)&S_GIM_LTM_RBKCLK_CTRL_CNT[0], ImLtmCommon_D_IM_LTM1_RBKCLK_REG_ADDR, ~ImLtmCommon_D_IM_LTM1_RBKCLK_REG_BIT );
	}
	if( ImLtmCommon_CHECK_TARGET_PIPR_NO_2( pipe_no ) ){
		Dd_Top_Start_Clock( (UCHAR*)&S_GIM_LTM_RBKCLK_CTRL_CNT[1], ImLtmCommon_D_IM_LTM2_RBKCLK_REG_ADDR, ~ImLtmCommon_D_IM_LTM2_RBKCLK_REG_BIT );
	}

	Dd_ARM_Critical_Section_End(S_GOSUSR_SPIN_LOCK);
#endif	// ImLtmCommon_CO_ACT_LTM_CLOCK

	return D_DDIM_OK;
}

/* LTMRBKCLK change to OFF
 */
INT32 im_ltm_common_off_rbkclk( UCHAR pipe_no )
{
#ifdef ImLtmCommon_CO_ACT_LTM_CLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_common_off_rbkclk error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(S_GOSUSR_SPIN_LOCK);

	if( ImLtmCommon_CHECK_TARGET_PIPR_NO_1( pipe_no ) ){
		if( S_GIM_LTM_RBKCLK_CTRL_CNT[0] == 1 ) {
			if( S_GIM_LTM_RBKCLK_CTRL_DISABLE[0] == 0 ) {
				Dd_Top_Stop_Clock( (UCHAR*)&S_GIM_LTM_RBKCLK_CTRL_CNT[0], ImLtmCommon_D_IM_LTM1_RBKCLK_REG_ADDR, ImLtmCommon_D_IM_LTM1_RBKCLK_REG_BIT );
			}
		}
		else {
			Dd_Top_Stop_Clock( (UCHAR*)&S_GIM_LTM_RBKCLK_CTRL_CNT[0], ImLtmCommon_D_IM_LTM1_RBKCLK_REG_ADDR, ImLtmCommon_D_IM_LTM1_RBKCLK_REG_BIT );
		}
	}
	if( ImLtmCommon_CHECK_TARGET_PIPR_NO_2( pipe_no ) ){
		if( S_GIM_LTM_RBKCLK_CTRL_CNT[1] == 1 ) {
			if( S_GIM_LTM_RBKCLK_CTRL_DISABLE[1] == 0 ) {
				Dd_Top_Stop_Clock( (UCHAR*)&S_GIM_LTM_RBKCLK_CTRL_CNT[1], ImLtmCommon_D_IM_LTM2_RBKCLK_REG_ADDR, ImLtmCommon_D_IM_LTM2_RBKCLK_REG_BIT );
			}
		}
		else {
			Dd_Top_Stop_Clock( (UCHAR*)&S_GIM_LTM_RBKCLK_CTRL_CNT[1], ImLtmCommon_D_IM_LTM2_RBKCLK_REG_ADDR, ImLtmCommon_D_IM_LTM2_RBKCLK_REG_BIT );
		}
	}

	Dd_ARM_Critical_Section_End(S_GOSUSR_SPIN_LOCK);
#endif	// ImLtmCommon_CO_ACT_LTM_CLOCK

	return D_DDIM_OK;
}

/* LTMRBKCLK change to OFF force
 */
INT32 im_ltm_common_force_off_rbkclk( UCHAR pipe_no )
{
#ifdef ImLtmCommon_CO_ACT_LTM_CLOCK
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_common_force_off_rbkclk error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Dd_ARM_Critical_Section_Start(S_GOSUSR_SPIN_LOCK);

	if( ImLtmCommon_CHECK_TARGET_PIPR_NO_1( pipe_no ) ){
		S_GIM_LTM_RBKCLK_CTRL_CNT[0] = 1;
		if( S_GIM_LTM_RBKCLK_CTRL_DISABLE[0] == 0 ) {
			Dd_Top_Stop_Clock( (UCHAR*)&S_GIM_LTM_RBKCLK_CTRL_CNT[0], ImLtmCommon_D_IM_LTM1_RBKCLK_REG_ADDR, ImLtmCommon_D_IM_LTM1_RBKCLK_REG_BIT );
		}
	}
	if( ImLtmCommon_CHECK_TARGET_PIPR_NO_2( pipe_no ) ){
		S_GIM_LTM_RBKCLK_CTRL_CNT[1] = 1;
		if( S_GIM_LTM_RBKCLK_CTRL_DISABLE[1] == 0 ) {
			Dd_Top_Stop_Clock( (UCHAR*)&S_GIM_LTM_RBKCLK_CTRL_CNT[1], ImLtmCommon_D_IM_LTM2_RBKCLK_REG_ADDR, ImLtmCommon_D_IM_LTM2_RBKCLK_REG_BIT );
		}
	}

	Dd_ARM_Critical_Section_End(S_GOSUSR_SPIN_LOCK);
#endif	// ImLtmCommon_CO_ACT_LTM_CLOCK

	return D_DDIM_OK;
}

/* LTM Initialize
 */
INT32 im_ltm_common_init_all_block( UCHAR pipe_no )
{
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_common_init_all_block error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_RBK_Init( pipe_no );
	Im_LTM_MAP_Init( pipe_no );
	Im_LTM_LTM_Init( pipe_no );

	return D_DDIM_OK;
}

/* LTM SW reset
 */
INT32 im_ltm_common_sw_reset_all_block( UCHAR pipe_no )
{
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_common_sw_reset_all_block error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_RBK_SW_Reset( pipe_no );
	Im_LTM_MAP_SW_Reset( pipe_no );
	Im_LTM_LTM_SW_Reset( pipe_no );

	return D_DDIM_OK;
}

/* Stop LTM(All block) process
 */
INT32 im_ltm_common_stop_all_block( UCHAR pipe_no )
{
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_common_stop_all_block error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_MAP_Stop( pipe_no );
	Im_LTM_RBK_Stop( pipe_no );
	Im_LTM_LTM_Stop( pipe_no );

	return D_DDIM_OK;
}

/* LTM Interrupt Handler
 */
VOID im_ltm_common_int_handler( UCHAR pipe_no )
{
#ifdef CO_PARAM_CHECK
	if( pipe_no >= D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "im_ltm_common_int_handler error. pipe_no>=D_IM_LTM_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_DEBUG_PRINT_IM_LTM
	Ddim_Print(( "im_ltm_common_int_handler begin\n" ));
#endif

#ifdef CO_DEBUG_PRINT_IM_LTM
	Ddim_Print(( "im_ltm_common_int_handler on pclk\n" ));
#endif
	im_ltm_common_on_pclk( pipe_no );

	if( pipe_no == D_IM_LTM_PIPE1 ){
		if( IO_LTM_P1.RBK.RINT1.word & 0xFFFFFFFF ){
			Im_LTM_RBK_Int_Handler( pipe_no );
		}
		if( IO_LTM_P1.MAP.MINT1.word & 0xFFFFFFFF ){
			Im_LTM_MAP_Int_Handler( pipe_no );
		}
		if( IO_LTM_P1.LTM.LINT1.word & 0xFFFFFFFF ){
			Im_LTM_LTM_Int_Handler( pipe_no );
		}
	}
	else{
		if( IO_LTM_P2.RBK.RINT1.word & 0xFFFFFFFF ){
			Im_LTM_RBK_Int_Handler( pipe_no );
		}
		if( IO_LTM_P2.MAP.MINT1.word & 0xFFFFFFFF ){
			Im_LTM_MAP_Int_Handler( pipe_no );
		}
		if( IO_LTM_P2.LTM.LINT1.word & 0xFFFFFFFF ){
			Im_LTM_LTM_Int_Handler( pipe_no );
		}
	}

#ifdef CO_DEBUG_PRINT_IM_LTM
	Ddim_Print(( "im_ltm_common_int_handler off pclk\n" ));
#endif
	im_ltm_common_off_pclk( pipe_no );

#ifdef CO_DEBUG_PRINT_IM_LTM
	Ddim_Print(( "im_ltm_common_int_handler end\n" ));
#endif
}

#ifdef IM_LTM_STATUS_PRINT
VOID im_ltm_common_print_clockstatus( VOID )
{
#ifdef ImLtmCommon_CO_ACT_LTM_CLOCK
	Ddim_Print(( "LTM1CK=%u\n", IO_CHIPTOP.CLKSTOP10.bit.LTM1CK ));
	Ddim_Print(( "\tgIM_LTM_Clk_Ctrl_Cnt[0]      = %u\n", S_GIM_LTM_CLK_CTRL_CNT[0] ));
	Ddim_Print(( "\tgIM_LTM_Clk_Ctrl_Disable[0]  = %u\n", S_GIM_LTM_CLK_CTRL_DISABLE[0] ));
	Ddim_Print(( "LTM2CK=%u\n", IO_CHIPTOP.CLKSTOP12.bit.LTM2CK ));
	Ddim_Print(( "\tgIM_LTM_Clk_Ctrl_Cnt[1]      = %u\n", S_GIM_LTM_CLK_CTRL_CNT[1] ));
	Ddim_Print(( "\tgIM_LTM_Clk_Ctrl_Disable[1]  = %u\n", S_GIM_LTM_CLK_CTRL_DISABLE[1] ));
#endif	// ImLtmCommon_CO_ACT_LTM_CLOCK
#ifdef ImLtmCommon_CO_ACT_LTM_HCLOCK
	Ddim_Print(( "LTM1HCLK=%u\n", IO_CHIPTOP.CLKSTOP10.bit.LTM1AH ));
	Ddim_Print(( "\tgIM_LTM_Hclk_Ctrl_Cnt[0]     = %u\n", S_GIM_LTM_HCLK_CTRL_CNT[0] ));
	Ddim_Print(( "\tgIM_LTM_Hclk_Ctrl_Disable[0] = %u\n", S_GIM_LTM_HCLK_CTRL_DISABLE[0] ));
	Ddim_Print(( "LTM2HCLK=%u\n", IO_CHIPTOP.CLKSTOP12.bit.LTM2AH ));
	Ddim_Print(( "\tgIM_LTM_Hclk_Ctrl_Cnt[1]     = %u\n", S_GIM_LTM_HCLK_CTRL_CNT[1] ));
	Ddim_Print(( "\tgIM_LTM_Hclk_Ctrl_Disable[1] = %u\n", S_GIM_LTM_HCLK_CTRL_DISABLE[1] ));
#endif	// ImLtmCommon_CO_ACT_LTM_HCLOCK
#ifdef ImLtmCommon_CO_ACT_LTM_PCLOCK
	Ddim_Print(( "LTM1PCLK=%u\n", IO_CHIPTOP.CLKSTOP10.bit.LTM1AP ));
	Ddim_Print(( "\tgIM_LTM_Pclk_Ctrl_Cnt[0]     = %u\n", S_GIM_LTM_PCLK_CTRL_CNT[0] ));
	Ddim_Print(( "\tgIM_LTM_Pclk_Ctrl_Disable[0] = %u\n", S_GIM_LTM_PCLK_CTRL_DISABLE[0] ));
	Ddim_Print(( "LTM2PCLK=%u\n", IO_CHIPTOP.CLKSTOP12.bit.LTM2AP ));
	Ddim_Print(( "\tgIM_LTM_Pclk_Ctrl_Cnt[1]     = %u\n", S_GIM_LTM_PCLK_CTRL_CNT[1] ));
	Ddim_Print(( "\tgIM_LTM_Pclk_Ctrl_Disable[1] = %u\n", S_GIM_LTM_PCLK_CTRL_DISABLE[1] ));
#endif	// ImLtmCommon_CO_ACT_LTM_PCLOCK
#ifdef ImLtmCommon_CO_ACT_LTM_ACLOCK
	Ddim_Print(( "LTMLTM1ACLK=%u\n", IO_CHIPTOP.CLKSTOP10.bit.LTM1AX ));
	Ddim_Print(( "\tgIM_LTM_Aclk_Ctrl_Cnt[0]     = %u\n", S_GIM_LTM_ACLK_CTRL_CNT[0] ));
	Ddim_Print(( "\tgIM_LTM_Aclk_Ctrl_Disable[0] = %u\n", S_GIM_LTM_ACLK_CTRL_DISABLE[0] ));
	Ddim_Print(( "LTM2ACLK=%u\n", IO_CHIPTOP.CLKSTOP12.bit.LTM2AX ));
	Ddim_Print(( "\tgIM_LTM_Aclk_Ctrl_Cnt[1]     = %u\n", S_GIM_LTM_ACLK_CTRL_CNT[1] ));
	Ddim_Print(( "\tgIM_LTM_Aclk_Ctrl_Disable[1] = %u\n", S_GIM_LTM_ACLK_CTRL_DISABLE[1] ));
#endif	// ImLtmCommon_CO_ACT_LTM_ACLOCK
	Ddim_Print(( "\n" ));
}

#endif

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
// Nothing Special
#endif	// CO_DDIM_UTILITY_USE

ImLtmCommon *im_ltm_common_new(void)
{
	ImLtmCommon* self = k_object_new(IM_TYPE_LTM_COMMON);
	return self;
}
