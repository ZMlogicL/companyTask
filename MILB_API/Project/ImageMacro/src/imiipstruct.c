/*
*@Copyright (C) 2020-2020 上海网用软件有限公司
*@date                :2020-08-04
*@author              :刘应春
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*2、
*2、
*@version
*2.0.0 2020年06月开始开发
*/

#include "driver_common.h"

//#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"

#include "dd_arm.h"

#include "ddim_user_custom.h"
#include <klib.h>
#include "jdsiip.h"

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
#include "palladium_test.h"
#endif //CO_PT_ENABLE
// ### REMOVE_RELEASE END
#include <string.h>
#include "imiipdefine.h"
#include "imiipcounter.h"
#include"imiipstruct.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImIipStruct, im_iip_struct);
#define IM_IIP_STRUCT_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImIipStructPrivate, IM_TYPE_IIP_STRUCT))

struct _ImIipStructPrivate
{
	int a;
};

#ifdef ImIipStruct_CO_ACT_IIP_ICLK
static volatile UCHAR S_GIM_IIP_ICLK_COUNTER    = 0;
#endif
#ifdef ImIipStruct_CO_ACT_IIP_PCLK
static volatile UCHAR S_GIM_IIP_PCLK_COUNTER    = 0;
#endif

const volatile U_IM_IIP_PARAM_UNITDEBUG* const S_GIM_IIP_UNITDEBUGREG = (U_IM_IIP_PARAM_UNITDEBUG*)IO_IIP.UNITDEBUG;

// clock off control is disabled(for register dump on debugger)

#ifdef ImIipStruct_CO_ACT_IIP_ICLK
static volatile UINT32 S_GIM_IIP_LCLK_CTRL_DISABLE = 0;
#endif // ImIipStruct_CO_ACT_IIP_ICLK
#ifdef ImIipStruct_CO_ACT_IIP_PCLK
static volatile UINT32 S_GIM_IIP_PCLK_CTRL_DISABLE = 0;
#endif // ImIipStruct_CO_ACT_IIP_PCLK

static void im_iip_struct_constructor(ImIipStruct *self)
{
//	ImIipStructPrivate *priv = IM_IIP_STRUCT_GET_PRIVATE(self);
//	priv-> a =  0;
}

static void im_iip_struct_destructor(ImIipStruct *self)
{
//	ImIipStructPrivate *priv = IM_IIP_STRUCT_GET_PRIVATE(self);
//	priv-> a =  0;
}

#ifdef ImIipStruct_CO_ACT_IIP_HCLK
static volatile UINT32 S_GIM_IIP_HCLK_CTRL_DISABLE = 0;
#endif // ImIipStruct_CO_ACT_IIP_HCLK

#ifdef ImIipStruct_CO_ACT_IIP_HCLK
static volatile UCHAR S_GIM_IIP_HCLK_COUNTER    = 0;
#endif

#ifdef ImIipStruct_CO_PARAM_CHECK
static INT32 imIipUtilCheckMasterIf( const INT32 master_IF )
{
	switch( master_IF ) {
		case ImIipDefine_D_IM_IIP_MASTER_IF0:	// FALLTHROUGH
		case ImIipDefine_D_IM_IIP_MASTER_IF1:	// FALLTHROUGH
#if D_IM_IIP_MASTER_IF1 != ImIipDefine_D_IM_IIP_MASTER_IF2
		case ImIipDefine_D_IM_IIP_MASTER_IF2:
#endif
			return ImIipDefine_D_IM_IIP_TRUE;
		default:
			return ImIipDefine_D_IM_IIP_FALSE;
	}
}
#endif

static INT32 imIipUtilWaitAndClose( TImIipUtilParamOpen* const openParam, TImIipUtilParamWait* const waitParam, const EImIipUnitId cubeic_free_unitid )
{
	UINT32	wait_factor;
	INT32	retval;
	INT32	ercd;

	retval = Im_IIP_Wait_End( &wait_factor,
							  waitParam->intFact,
							  ImIipDefine_D_IM_IIP_OR_WAIT,
							  waitParam->waitTime );
	if( retval == ImIipDefine_D_IM_IIP_OK ) {
		if( wait_factor & ImIipDefine_D_IM_IIP_INT_FACTOR_AXIERR ) {
			retval = ImIipDefine_D_IM_IIP_ERR;
		}
	}
	ercd = Im_IIP_Close_SWTRG( openParam->unitidBitmask, openParam->pixidBitmask, openParam->openResBitmask );
	if( retval == ImIipDefine_D_IM_IIP_OK ) {
		return ercd;
	}

	return retval;
}

VOID im_iip_struct_on_lclk( ImIipDefine* self )
{
#ifdef ImIipStruct_CO_ACT_IIP_ICLK
	if( S_GIM_IIP_ICLK_COUNTER < 255 ) {
		Dd_Top_Start_Clock( (UCHAR*)&S_GIM_IIP_ICLK_COUNTER, &Dd_Top_Get_CLKSTOP3(), ~D_DD_TOP_IIPAX_BIT );
#ifdef CO_DEBUG_ON_PC
		Dd_Top_Get_CLKSTOP3() &= ~D_DD_TOP_IIPAX_BIT;
#endif
	}
#endif
}

/**
@brief		IIPAX OFF
*/
VOID im_iip_struct_off_iclk(  ImIipDefine* self )
{
#ifdef ImIipStruct_CO_ACT_IIP_ICLK
	UINT32 irq_mask;

	irq_mask = im_iip_static_irq_disable();

	if( S_GIM_IIP_ICLK_COUNTER == 1 ) {
		if( S_GIM_IIP_LCLK_CTRL_DISABLE == 0 ) {
			Dd_Top_Stop_Clock( (UCHAR*)&S_GIM_IIP_ICLK_COUNTER, &Dd_Top_Get_CLKSTOP3(), D_DD_TOP_IIPAX_BIT );
#ifdef CO_DEBUG_ON_PC
			Dd_Top_Get_CLKSTOP3() |= D_DD_TOP_IIPAX_BIT;
#endif
		}
	}
	else {
		Dd_Top_Stop_Clock( (UCHAR*)&S_GIM_IIP_ICLK_COUNTER, &Dd_Top_Get_CLKSTOP3(), D_DD_TOP_IIPAX_BIT );
#ifdef CO_DEBUG_ON_PC
		Dd_Top_Get_CLKSTOP3() |= D_DD_TOP_IIPAX_BIT;
#endif
	}

	im_iip_static_irq_enable(NULL, irq_mask );
#endif
}

VOID Im_IIP_On_Hclk( VOID )
{
#ifdef ImIipStruct_CO_ACT_IIP_HCLK
	if( S_GIM_IIP_HCLK_COUNTER < 255 ) {
		Dd_Top_Start_Clock( (UCHAR*)&S_GIM_IIP_HCLK_COUNTER, &Dd_Top_Get_CLKSTOP3(), ~D_DD_TOP_IIPAH_BIT );
#ifdef CO_DEBUG_ON_PC
		Dd_Top_Get_CLKSTOP3() &= ~D_DD_TOP_IIPAH_BIT;
#endif
	}
#endif
}

/**
@brief		HCLK OFF
*/
VOID Im_IIP_Off_Hclk( VOID )
{
#ifdef ImIipStruct_CO_ACT_IIP_HCLK
	UINT32 irq_mask;

	irq_mask = im_iip_static_irq_disable();

	if( S_GIM_IIP_HCLK_COUNTER == 1 ) {
		if( S_GIM_IIP_HCLK_CTRL_DISABLE == 0 ) {
			Dd_Top_Stop_Clock( (UCHAR*)&S_GIM_IIP_HCLK_COUNTER, &Dd_Top_Get_CLKSTOP3(), D_DD_TOP_IIPAH_BIT );
#ifdef CO_DEBUG_ON_PC
			Dd_Top_Get_CLKSTOP3() |= D_DD_TOP_IIPAH_BIT;
#endif
		}
	}
	else {
		Dd_Top_Stop_Clock( (UCHAR*)&S_GIM_IIP_HCLK_COUNTER, &Dd_Top_Get_CLKSTOP3(), D_DD_TOP_IIPAH_BIT );
#ifdef CO_DEBUG_ON_PC
		Dd_Top_Get_CLKSTOP3() |= D_DD_TOP_IIPAH_BIT;
#endif
	}

	im_iip_static_irq_enable( NULL,irq_mask );
#endif
}

/**
@brief		PCLK ON
*/
VOID Im_IIP_On_Pclk( VOID )
{
#ifdef ImIipStruct_CO_ACT_IIP_PCLK
	if( S_GIM_IIP_PCLK_COUNTER < 255 ) {
		Dd_Top_Start_Clock( (UCHAR*)&S_GIM_IIP_PCLK_COUNTER, &Dd_Top_Get_CLKSTOP3(), ~D_DD_TOP_IIPAP_BIT );
#ifdef CO_DEBUG_ON_PC
		Dd_Top_Get_CLKSTOP3() &= ~D_DD_TOP_IIPAP_BIT;
#endif

		// wait
		IO_IIP.AHBSTS.word;	/* pgr0695 */
	}
#endif
}

/**
@brief		PCLK OFF
*/
VOID Im_IIP_Off_Pclk( VOID )
{
#ifdef ImIipStruct_CO_ACT_IIP_PCLK
	UINT32 irq_mask;

	irq_mask = im_iip_static_irq_disable();

	// wait
	IO_IIP.AHBSTS.word;	/* pgr0695 */

	if( S_GIM_IIP_PCLK_COUNTER == 1 ) {
		if( S_GIM_IIP_PCLK_CTRL_DISABLE == 0 ) {
			Dd_Top_Stop_Clock( (UCHAR*)&S_GIM_IIP_PCLK_COUNTER, &Dd_Top_Get_CLKSTOP3(), D_DD_TOP_IIPAP_BIT );
#ifdef CO_DEBUG_ON_PC
			Dd_Top_Get_CLKSTOP3() |= D_DD_TOP_IIPAP_BIT;
#endif
		}
	}
	else {
		Dd_Top_Stop_Clock( (UCHAR*)&S_GIM_IIP_PCLK_COUNTER, &Dd_Top_Get_CLKSTOP3(), D_DD_TOP_IIPAP_BIT );
#ifdef CO_DEBUG_ON_PC
		Dd_Top_Get_CLKSTOP3() |= D_DD_TOP_IIPAP_BIT;
#endif
	}

	im_iip_static_irq_enable( NULL,irq_mask );
#endif
}

INT32 im_iip_struct_init( VOID )
{
	INT32	retval;

	im_iip_counter_on_lipclk(NULL);
	im_iip_struct_on_lclk(NULL);
	Im_IIP_On_Pclk();

#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
	ImIipDefine_IM_IIP_PRINT_PCDBG(( "PCLK=%u ICLK=%u CLK=%u\n", Dd_Top_Get_CLKSTOP_IIPAP(), Dd_Top_Get_CLKSTOP_IIPAX(), Dd_Top_Get_CLKSTOP_IIPCK() ));
#endif
	if( IO_IIP.IZACTL1.bit.TRG == ImIipDefine_D_IM_IIP_STOPPED ) {
		im_iip_counter_on_izarac_caxrac(NULL);

		ImIipDefine_IM_IIP_DSB();

		ImIipDefine_IM_IIP_WAIT_USEC( ImIipDefine_D_IM_IIP_SRAM_WAIT_USEC );

		// Software-Reset ON
		IO_IIP.IZACTL0.word = 1;

		ImIipDefine_IM_IIP_DSB();

		// IIPCLK        = MAX 252.0MHz		MIN 31.5MHz
		// APB clock     = MAX  66.7MHz		MIN 20.8MHz
		// -->   ( (1/IIPCLK) / (1/APB clock) ) * 2 + 1
		//     = ( (1/31.5)   / (1/66.7)      ) * 2 + 1
		//     = 5.23 => 6 APB cycle

		// wait 6 APB clock
		IO_IIP.IZACTL0.word;	/* pgr0695 */
		IO_IIP.IZACTL0.word;	/* pgr0695 */
		IO_IIP.IZACTL0.word;	/* pgr0695 */

		ImIipDefine_IM_IIP_PRINT_PCDBG(( "IZACTL0 = 0x%lx IZACTL0 = 0x%x\n", IO_IIP.IZACTL0.word, IO_IIP.ACESEN0.bit.IZARAC ));

		ImIipDefine_IM_IIP_DSB();

		// Software-Reset OFF
		IO_IIP.IZACTL0.word = 0;

		ImIipDefine_IM_IIP_DSB();

		// wait 6 APB clock
		IO_IIP.IZACTL0.word;	/* pgr0695 */
		IO_IIP.IZACTL0.word;	/* pgr0695 */
		IO_IIP.IZACTL0.word;	/* pgr0695 */

		ImIipDefine_IM_IIP_DSB();

		im_iip_counter_off_izarac_caxrac(NULL);

		ImIipDefine_IM_IIP_PRINT_PCDBG(( "IZACTL0 = 0x%lx IZACTL0 = 0x%x\n", IO_IIP.IZACTL0.word, IO_IIP.ACESEN0.bit.IZARAC ));

		retval = ImIipDefine_D_IM_IIP_OK;
	}
	else {
		retval = ImIipDefine_D_IM_IIP_ERR;
	}

	Im_IIP_Off_Pclk();
	im_iip_struct_off_iclk(NULL);
	im_iip_counter_off_lipclk(NULL);
	ImIipDefine_IM_IIP_DSB();

	if( retval != ImIipDefine_D_IM_IIP_OK ) {
		return retval;
	}

	retval = DDIM_User_Set_Flg( FID_IM_IIP_UNIT_LO, (DDIM_USER_FLGPTN)0xFFFFFFFF );
	if( retval != D_DDIM_USER_E_OK ) {
		return ImIipDefine_D_IM_IIP_ERR;
	}
	retval = DDIM_User_Set_Flg( FID_IM_IIP_UNIT_HI, (DDIM_USER_FLGPTN)0xFFFFFFFF );
	if( retval != D_DDIM_USER_E_OK ) {
		return ImIipDefine_D_IM_IIP_ERR;
	}
	retval = DDIM_User_Set_Flg( FID_IM_IIP_PIX, (DDIM_USER_FLGPTN)0xFFFFFFFF );
	if( retval != D_DDIM_USER_E_OK ) {
		return ImIipDefine_D_IM_IIP_ERR;
	}
	retval = DDIM_User_Set_Flg( FID_IM_IIP_RES, (DDIM_USER_FLGPTN)0xFFFFFFFF );
	if( retval != D_DDIM_USER_E_OK ) {
		return ImIipDefine_D_IM_IIP_ERR;
	}

	return ImIipDefine_D_IM_IIP_OK;
}

/**
 * Initialize IIP Unit. This API executes software-reset [UNITSR.UNITSR = 1b] and releases software-reset [UNITSR.UNITSR = 0b].
 */
INT32 im_iip_struct_init_unit( const EImIipUnitId unitId )
{
	volatile struct io_iip_uinftbl* p_uinftbl;
	INT32	retval;

	p_uinftbl = im_iip_sun_get_unitinftbl_regaddr( unitId );
	if( p_uinftbl == NULL ) {
		return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}


	im_iip_counter_on_lipclk(NULL);
	im_iip_struct_on_lclk(NULL);
	Im_IIP_On_Pclk();
	ImIipDefine_IM_IIP_DSB();

	im_iip_counter_on_izarac_caxrac(NULL);

	if( p_uinftbl->UNITINFTBL0.bit.SWTRG == ImIipDefine_D_IM_IIP_SWTRG_STOPPED ) {
		// Software-Reset ON
		p_uinftbl->UNITSR.word = 1;

		ImIipDefine_IM_IIP_DSB();

		// IIPCLK        = MAX 252.0MHz		MIN 31.5MHz
		// APB clock     = MAX  66.7MHz		MIN 20.8MHz
		// -->   ( (1/IIPCLK) / (1/APB clock) ) * 2 + 1
		//     = ( (1/31.5)   / (1/66.7)      ) * 2 + 1
		//     = 5.23 => 6 APB cycle

		// wait 6 APB clock
		IO_IIP.IZACTL0.word;	/* pgr0695 */
		IO_IIP.IZACTL0.word;	/* pgr0695 */
		IO_IIP.IZACTL0.word;	/* pgr0695 */

		ImIipDefine_IM_IIP_DSB();

		// Software-Reset OFF
		p_uinftbl->UNITSR.word = 0;

		ImIipDefine_IM_IIP_DSB();

		// wait 6 APB clock
		IO_IIP.IZACTL0.word;	/* pgr0695 */
		IO_IIP.IZACTL0.word;	/* pgr0695 */
		IO_IIP.IZACTL0.word;	/* pgr0695 */

		ImIipDefine_IM_IIP_DSB();

		retval = ImIipDefine_D_IM_IIP_OK;
	}
	else {
		retval = ImIipDefine_D_IM_IIP_ERR;
	}

	im_iip_counter_off_izarac_caxrac(NULL);

	Im_IIP_Off_Pclk();
	im_iip_struct_off_iclk(NULL);
	im_iip_counter_off_lipclk(NULL);
	ImIipDefine_IM_IIP_DSB();

	return retval;
}

/**
*	Open Driver for hardware trigger.
*/
INT32 im_iip_struct_open( const INT32 waitTime )
{
#ifdef ImIipStruct_CO_PARAM_CHECK
	if( im_iip_counter_check_wait_time(NULL,waitTime) == ImIipDefine_D_IM_IIP_FALSE ) {
		Ddim_Assertion(("I:im_iip_struct_open INVALID_ARG_ERR\n"));
		return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}
#endif

	return im_iip_counter_twai_pol_sem( SID_IM_IIP, (DDIM_USER_TMO)waitTime );
}

/**
*	Close Driver for hardware trigger.
*/
INT32 im_iip_struct_close( VOID )
{
	ImIipDefine *imIipDefine        = im_iip_define_get();
	T_IM_IIP_CALLBACK gimIipCallback     = im_iip_get_gim_iip(imIipDefine);

	DDIM_USER_ER	ercd;
	UINT32			irq_mask;

	gimIipCallback = NULL;

	irq_mask = im_iip_static_irq_disable();

	IO_IIP.INTEN0.bit.IZAEN = 0;

	im_iip_static_irq_enable(NULL, irq_mask );

	im_iip_sub_clear_hwen_all(NULL);

	ercd = DDIM_User_Clr_Flg( FID_IM_IIP, ~ImIipDefine_D_IM_IIP_FLG_USED_BIT_PATTERN );
	if( D_DDIM_USER_E_OK != ercd ) {
		return ImIipDefine_D_IM_IIP_SYSTEMCALL_ERR;
	}

	ercd = DDIM_User_Sig_Sem( SID_IM_IIP );
	if( D_DDIM_USER_E_OK != ercd ) {
		return ImIipDefine_D_IM_IIP_SYSTEMCALL_ERR;
	}

	return ImIipDefine_D_IM_IIP_OK;
}

INT32 im_iip_struct_ctrl_base( const TImIipCtrlBase* const cfg )
{

	ImIipDefine *imIipDefine        = im_iip_define_get();
	T_IM_IIP_CALLBACK gimIipCallback     = im_iip_get_gim_iip(imIipDefine);

	UINT32	loopcnt;

#ifdef ImIipStruct_CO_PARAM_CHECK
	if( cfg == NULL ) {
		Ddim_Assertion(("I:im_iip_struct_ctrl_base INVALID_ARG_ERR\n"));
		return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}
#endif

	Im_IIP_On_Pclk();
	ImIipDefine_IM_IIP_DSB();

#if 0	// B2Y Link not support
	// link control
	IO_IIP.IZACTL1.bit.LKEN = cfg->b2yLink;
#endif	// B2Y Link not support

	// cache control
	for( loopcnt = 0; loopcnt < ImIipStruct_D_IM_IIP_CACHE_MAXNUM; loopcnt++ ) {
		IO_IIP.PDCCTL[loopcnt].bit.FLHALL = cfg->cacheFlushCtrl[loopcnt];
		IO_IIP.PDCCTL[loopcnt].bit.EXTBIT = cfg->extBitCtrlLess8Bits[loopcnt];
	}

	// interrupt control
	gimIipCallback = cfg->intHandler;

	IO_IIP.LINE_VAL_INT_SL0.bit.LINE_VAL_INT_SL = cfg->sl0InterruptLines;
	IO_IIP.LINE_VAL_INT_SL1.bit.LINE_VAL_INT_SL = cfg->sl1InterruptLines;
	IO_IIP.LINE_VAL_INT_SL2.bit.LINE_VAL_INT_SL = cfg->sl2InterruptLines;
	IO_IIP.LINE_VAL_INT_SL3.bit.LINE_VAL_INT_SL = cfg->sl3InterruptLines;
	IO_IIP.LINE_VAL_INT_SL4.bit.LINE_VAL_INT_SL = cfg->sl4InterruptLines;
	IO_IIP.LINE_VAL_INT_SL5.bit.LINE_VAL_INT_SL = cfg->sl5InterruptLines;
	IO_IIP.LINE_VAL_INT_SL6.bit.LINE_VAL_INT_SL = cfg->sl6InterruptLines;
	IO_IIP.LINE_VAL_INT_SL7.bit.LINE_VAL_INT_SL = cfg->sl7InterruptLines;
	IO_IIP.LINE_VAL_INT_SL8.bit.LINE_VAL_INT_SL = cfg->sl8InterruptLines;

	Im_IIP_Off_Pclk();
	ImIipDefine_IM_IIP_DSB();

	return Im_IIP_Set_Interrupt( cfg->enableInterruptFlag, ImIipDefine_D_IM_IIP_ENABLE_ON );
}
/**
*	Color space conversion
*/
INT32 IM_IIP_Utility_CSC( const TImIipUtilCsc* const cfg0,
						  const TImIipUtilCsc* const cfg1,
						  const UCHAR paramMasterIf,
						  const ULONG paramBufferAddr,
						  const INT32 waitTime )
{
	INT32 						retval;
	INT32 						retval2;
	TImIipUtilParamCsc		csc_param[2];

#ifdef ImIipStruct_CO_PARAM_CHECK
	if( (cfg0 == NULL) ||
		 (paramBufferAddr == 0) ||
		 (imIipUtilCheckMasterIf(paramMasterIf) == ImIipDefine_D_IM_IIP_FALSE) ||
		 (im_iip_counter_check_wait_time(NULL,waitTime) == ImIipDefine_D_IM_IIP_FALSE)
	   ) {
		Ddim_Assertion(("I:IM_IIP_Utility_CSC INVALID_ARG_ERR\n"));
		return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}
#endif

	memset( &csc_param[0], '\0', sizeof(csc_param[0]) );	/* pgr0584 */
	csc_param[0].paramBufferAddr = ImIipDefine_IM_IIP_ROUNDUN_8( paramBufferAddr );
	csc_param[0].paramMasterIf = paramMasterIf;
	csc_param[0].waitParam.waitTime = waitTime;
	retval = im_iip_define_util_csc_main( &csc_param[0], cfg0, waitTime );
	if( retval != ImIipDefine_D_IM_IIP_OK ) {
		return retval;
	}

	if( cfg1 != NULL ) {
		memset( &csc_param[1], '\0', sizeof(csc_param[1]) );
		csc_param[1].paramBufferAddr = csc_param[0].paramBufferAddr;
		csc_param[1].paramMasterIf = paramMasterIf;
		csc_param[1].waitParam.waitTime = waitTime;
		retval = im_iip_define_util_csc_main( &csc_param[1], cfg1, waitTime );
		if( retval != ImIipDefine_D_IM_IIP_OK ) {
			return retval;
		}
	}

	retval = imIipUtilWaitAndClose( &csc_param[0].openParam, &csc_param[0].waitParam, ImIipStruct_E_IM_IIP_UNIT_ID_MAX );
								// cubeic_free_unitid value is dummy

	if( cfg1 != NULL ) {
		retval2 = imIipUtilWaitAndClose( &csc_param[1].openParam, &csc_param[1].waitParam, ImIipStruct_E_IM_IIP_UNIT_ID_MAX );
									// cubeic_free_unitid value is dummy
		if( retval == ImIipDefine_D_IM_IIP_OK ) {
			retval = retval2;
		}
	}


	return retval;
}

/**
*	Look up table
*/
INT32 IM_IIP_Utility_LUT( const TImIipUtilLut* const cfg,
						  const UCHAR paramMasterIf,
						  const ULONG paramBufferAddr,
						  const INT32 waitTime )
{
	INT32 retval;
	TImIipUtilParamLut lut_param;

#ifdef ImIipStruct_CO_PARAM_CHECK
	if( (cfg == NULL) ||
		 (paramBufferAddr == 0) ||
		 (imIipUtilCheckMasterIf(paramMasterIf) == ImIipDefine_D_IM_IIP_FALSE) ||
		 (im_iip_counter_check_wait_time(NULL,waitTime) == ImIipDefine_D_IM_IIP_FALSE)
	   ) {
		Ddim_Assertion(("I:IM_IIP_Utility_LUT INVALID_ARG_ERR\n"));
		return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}
#endif

	memset( &lut_param, '\0', sizeof(lut_param) );
	lut_param.paramBufferAddr = ImIipDefine_IM_IIP_ROUNDUN_8( paramBufferAddr );
	lut_param.paramMasterIf = paramMasterIf;
	lut_param.waitParam.waitTime = waitTime;
	retval = im_iip_new_util_lut_main( &lut_param, cfg );
	if( retval != ImIipDefine_D_IM_IIP_OK ) {
		return retval;
	}

	retval = imIipUtilWaitAndClose( &lut_param.openParam, &lut_param.waitParam, ImIipStruct_E_IM_IIP_UNIT_ID_MAX );
								// cubeic_free_unitid value is dummy

// ### REMOVE_RELEASE BEGIN
#if 0
//#ifdef CO_PT_ENABLE
	{
		static BYTE unitdbg_buf[0x10000];
		extern VOID CT_Im_IIP_Print_Unitcfg_Byid( const EImIipUnitId unitid );
		extern VOID CT_Im_IIP_Print_Pixfmttbl_Detail( const EImIipPixid pixid );
		Palladium_Set_Out_Localstack( (ULONG)lut_param.pParam1D, sizeof(*lut_param.pParam1D) );
		Palladium_Set_Out_Localstack( (ULONG)lut_param.pParamLut, sizeof(*lut_param.pParamLut) );
		Palladium_Set_Out_Localstack( (ULONG)lut_param.pParamSl, sizeof(*lut_param.pParamSl) );

		CT_Im_IIP_Print_Unitcfg_Byid( cfg->ldUnitid );
		CT_Im_IIP_Print_Pixfmttbl_Detail( 1 );
		CT_Im_IIP_Print_Unitcfg_Byid( cfg->lutUnitid );
		CT_Im_IIP_Print_Unitcfg_Byid( cfg->slUnitid );
		CT_Im_IIP_Print_Pixfmttbl_Detail( 2 );

		im_iip_static_start_dumpunitreg( cfg->ldUnitid );
		memcpy( unitdbg_buf, (void*)S_GIM_IIP_UNITDEBUGREG, 0x10000 );
		DDIM_User_L1l2cache_Clean_Addr( (UINT32)unitdbg_buf, 0x10000 );
		Palladium_Set_Out_Localstack( (ULONG)unitdbg_buf, 0x10000 );

		im_iip_static_start_dumpunitreg( cfg->lutUnitid );
		memcpy( unitdbg_buf, (void*)S_GIM_IIP_UNITDEBUGREG, 0x10000 );
		DDIM_User_L1l2cache_Clean_Addr( (UINT32)unitdbg_buf, 0x10000 );
		Palladium_Set_Out_Localstack( (ULONG)unitdbg_buf, 0x10000 );

		im_iip_static_start_dumpunitreg( cfg->slUnitid );
		memcpy( unitdbg_buf, (void*)S_GIM_IIP_UNITDEBUGREG, 0x10000 );
		DDIM_User_L1l2cache_Clean_Addr( (UINT32)unitdbg_buf, 0x10000 );
		Palladium_Set_Out_Localstack( (ULONG)unitdbg_buf, 0x10000 );

		im_iip_static_stop_dumpunitreg();
	}
#endif //CO_PT_ENABLE
// ### REMOVE_RELEASE END

	return retval;
}

/**
*	Alpha blend
*/
INT32 IM_IIP_Utility_AlphaBlend( const TImIipUtilAlphablend* const cfg,
								 const UCHAR paramMasterIf,
								 const ULONG paramBufferAddr,
								 const INT32 waitTime )
{
	INT32 						retval;
	TImIipUtilParamAlpha	alp_param;

#ifdef ImIipStruct_CO_PARAM_CHECK
	if( (cfg == NULL) ||
		 (paramBufferAddr == 0) ||
		 (imIipUtilCheckMasterIf(paramMasterIf) == ImIipDefine_D_IM_IIP_FALSE) ||
		 (im_iip_counter_check_wait_time(NULL,waitTime) == ImIipDefine_D_IM_IIP_FALSE)
	   ) {
		Ddim_Assertion(("I:IM_IIP_Utility_AlphaBlend INVALID_ARG_ERR\n"));
		return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}
#endif

	memset( &alp_param, '\0', sizeof(alp_param) );
	alp_param.paramBufferAddr = ImIipDefine_IM_IIP_ROUNDUN_8( paramBufferAddr );
	alp_param.paramMasterIf = paramMasterIf;
	alp_param.waitParam.waitTime = waitTime;
	retval = im_iip_new_util_alpha_main( &alp_param, cfg );
	if( retval != ImIipDefine_D_IM_IIP_OK ) {
		return retval;
	}

	retval = imIipUtilWaitAndClose( &alp_param.openParam, &alp_param.waitParam, ImIipStruct_E_IM_IIP_UNIT_ID_MAX );
								// cubeic_free_unitid value is dummy

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
	{
		static BYTE unitdbg_buf[0x10000];
		extern VOID CT_Im_IIP_Print_Unitcfg_Byid( const EImIipUnitId unitid );
		Palladium_Set_Out_Localstack( (ULONG)alp_param.pParam1D[0], sizeof(*alp_param.pParam1D[0]) );
		Palladium_Set_Out_Localstack( (ULONG)alp_param.pParam1D[1], sizeof(*alp_param.pParam1D[1]) );
		Palladium_Set_Out_Localstack( (ULONG)alp_param.pParamAlp, sizeof(*alp_param.pParamAlp) );
		Palladium_Set_Out_Localstack( (ULONG)alp_param.pParamSl, sizeof(*alp_param.pParamSl) );

		CT_Im_IIP_Print_Unitcfg_Byid( cfg->ldUnitid[0] );
		CT_Im_IIP_Print_Unitcfg_Byid( cfg->ldUnitid[1] );
		CT_Im_IIP_Print_Unitcfg_Byid( cfg->blendUnitid );
		CT_Im_IIP_Print_Unitcfg_Byid( cfg->slUnitid );

		im_iip_static_start_dumpunitreg( cfg->ldUnitid[0] );
		memcpy( unitdbg_buf, (void*)S_GIM_IIP_UNITDEBUGREG, 0x10000 );
		DDIM_User_L1l2cache_Clean_Addr( (UINT32)unitdbg_buf, 0x10000 );
		Palladium_Set_Out_Localstack( (ULONG)unitdbg_buf, 0x10000 );

		im_iip_static_start_dumpunitreg( cfg->ldUnitid[1] );
		memcpy( unitdbg_buf, (void*)S_GIM_IIP_UNITDEBUGREG, 0x10000 );
		DDIM_User_L1l2cache_Clean_Addr( (UINT32)unitdbg_buf, 0x10000 );
		Palladium_Set_Out_Localstack( (ULONG)unitdbg_buf, 0x10000 );

		im_iip_static_start_dumpunitreg( cfg->blendUnitid );
		memcpy( unitdbg_buf, (void*)S_GIM_IIP_UNITDEBUGREG, 0x10000 );
		DDIM_User_L1l2cache_Clean_Addr( (UINT32)unitdbg_buf, 0x10000 );
		Palladium_Set_Out_Localstack( (ULONG)unitdbg_buf, 0x10000 );

		im_iip_static_start_dumpunitreg( cfg->slUnitid );
		memcpy( unitdbg_buf, (void*)S_GIM_IIP_UNITDEBUGREG, 0x10000 );
		DDIM_User_L1l2cache_Clean_Addr( (UINT32)unitdbg_buf, 0x10000 );
		Palladium_Set_Out_Localstack( (ULONG)unitdbg_buf, 0x10000 );

		im_iip_static_stop_dumpunitreg();
	}
#endif //CO_PT_ENABLE
// ### REMOVE_RELEASE END

	return retval;
}

#ifdef CO_IM_IIP_UTIL_DEBUG
VOID IM_IIP_Utility_PrintParamBufferBytes( VOID )
{
	DDIM_User_Printf( "IM_IIP_Utility_ResizeRotate() paramBufferAddr's area bytes: %u\n",
		  ImIipDefine_IM_IIP_ROUNDUN_8( sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0) )
		+ ImIipDefine_IM_IIP_ROUNDUN_8( sizeof(T_IM_IIP_PARAM_AFN) )
		+ ImIipDefine_IM_IIP_ROUNDUN_8( sizeof(T_IM_IIP_PARAM_STS) )
		);
	DDIM_User_Printf( "IM_IIP_Utility_CSC() paramBufferAddr's area bytes: %u\n",
		ImIipDefine_IM_IIP_ROUNDUN_8( sizeof(T_IM_IIP_PARAM_1DL) )
		+ ImIipDefine_IM_IIP_ROUNDUN_8( sizeof(T_IM_IIP_PARAM_CSC) )
		+ ImIipDefine_IM_IIP_ROUNDUN_8( sizeof(T_IM_IIP_PARAM_STS) )
		);

	DDIM_User_Printf( "IM_IIP_Utility_LUT() paramBufferAddr's area bytes: %u\n",
		ImIipDefine_IM_IIP_ROUNDUN_8( sizeof(T_IM_IIP_PARAM_1DL) )
		+ ImIipDefine_IM_IIP_ROUNDUN_8( sizeof(T_IM_IIP_PARAM_LUT) )
		+ ImIipDefine_IM_IIP_ROUNDUN_8( sizeof(T_IM_IIP_PARAM_STS) )
		);

	DDIM_User_Printf( "IM_IIP_Utility_AlphaBlend() paramBufferAddr's area bytes: %u\n",
		ImIipDefine_IM_IIP_ROUNDUN_8( sizeof(T_IM_IIP_PARAM_1DL) )
		+ ImIipDefine_IM_IIP_ROUNDUN_8( sizeof(T_IM_IIP_PARAM_1DL) )
		+ ImIipDefine_IM_IIP_ROUNDUN_8( sizeof(T_IM_IIP_PARAM_BLEND) )
		+ ImIipDefine_IM_IIP_ROUNDUN_8( sizeof(T_IM_IIP_PARAM_STS) )
		);
}
#endif //CO_IM_IIP_UTIL_DEBUG

INT32 IM_IIP_Utility_ResizeRotate( const TImIipUtilRr* const cfg0,
								   const TImIipUtilRr* const cfg1,
								   const UCHAR paramMasterIf,
								   const ULONG paramBufferAddr,
								   const INT32 waitTime )
{
	INT32 retval;
	INT32 retval2;
	TImIipUtilParamResizeRotate rr_param[2];

#ifdef ImIipStruct_CO_PARAM_CHECK
	if( (cfg0 == NULL) ||
		 (paramBufferAddr == 0) ||
		 (imIipUtilCheckMasterIf(paramMasterIf) == ImIipDefine_D_IM_IIP_FALSE) ||
		 (im_iip_counter_check_wait_time(NULL,waitTime) == ImIipDefine_D_IM_IIP_FALSE) ||
		 ((cfg0->resizeMode == ImIipStruct_E_IM_IIP_UTIL_RESIZE_MODE_BICUBIC) && (cfg0->rotation != ImIipStruct_E_IM_IIP_UTIL_ROTATE_000))
	   ) {
		Ddim_Assertion(("I:IM_IIP_Utility_ResizeRotate INVALID_ARG_ERR\n"));
		return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}
	if( cfg1 != NULL ) {
		if( cfg1->resizeMode == ImIipStruct_E_IM_IIP_UTIL_RESIZE_MODE_BICUBIC ) {
			Ddim_Assertion(("I:IM_IIP_Utility_ResizeRotate INVALID_ARG_ERR\n"));
			return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
		}
	}
#endif

	memset( &rr_param[0], '\0', sizeof(rr_param[0]) );	/* pgr0584 */
	rr_param[0].paramBufferAddr = ImIipDefine_IM_IIP_ROUNDUN_8( paramBufferAddr );
	rr_param[0].paramMasterIf = paramMasterIf;
	rr_param[0].waitParam.waitTime = waitTime;
	retval = im_iip_define_util_resizerotate_main( &rr_param[0], cfg0 );
	if( retval != ImIipDefine_D_IM_IIP_OK ) {
		return retval;
	}

	if( cfg1 != NULL ) {
		memset( &rr_param[1], '\0', sizeof(rr_param[1]) );
		rr_param[1].paramBufferAddr = rr_param[0].paramBufferAddr;
		rr_param[1].paramMasterIf = paramMasterIf;
		rr_param[1].waitParam.waitTime = waitTime;
		retval = im_iip_define_util_resizerotate_main( &rr_param[1], cfg1 );
		if( retval != ImIipDefine_D_IM_IIP_OK ) {
			return retval;
		}
	}

	retval = imIipUtilWaitAndClose( &rr_param[0].openParam, &rr_param[0].waitParam, cfg0->afnUnitid );

	if( cfg1 != NULL ) {
		retval2 = imIipUtilWaitAndClose( &rr_param[1].openParam, &rr_param[1].waitParam, cfg1->afnUnitid );
		if( retval == ImIipDefine_D_IM_IIP_OK ) {
			retval = retval2;
		}
	}

	return retval;
}

ImIipStruct *im_iip_struct_new(void)
{
	ImIipStruct* self = k_object_new_with_private(IM_TYPE_IIP_STRUCT,sizeof(ImIipStructPrivate));
	return self;
}
