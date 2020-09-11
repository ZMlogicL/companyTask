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

#ifdef CO_ACT_IIP_ICLK
static volatile UCHAR S_GIM_IIP_ICLK_COUNTER    = 0;
#endif
#ifdef CO_ACT_IIP_PCLK
static volatile UCHAR S_GIM_IIP_PCLK_COUNTER    = 0;
#endif

const volatile U_IM_IIP_PARAM_UNITDEBUG* const S_GIM_IIP_UNITDEBUGREG = (U_IM_IIP_PARAM_UNITDEBUG*)IO_IIP.UNITDEBUG;

// clock off control is disabled(for register dump on debugger)

#ifdef CO_ACT_IIP_ICLK
static volatile UINT32 S_GIM_IIP_LCLK_CTRL_DISABLE = 0;
#endif // CO_ACT_IIP_ICLK
#ifdef CO_ACT_IIP_PCLK
static volatile UINT32 S_GIM_IIP_PCLK_CTRL_DISABLE = 0;
#endif // CO_ACT_IIP_PCLK

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

#ifdef CO_ACT_IIP_HCLK
static volatile UINT32 S_GIM_IIP_HCLK_CTRL_DISABLE = 0;
#endif // CO_ACT_IIP_HCLK

#ifdef CO_ACT_IIP_HCLK
static volatile UCHAR S_GIM_IIP_HCLK_COUNTER    = 0;
#endif

#ifdef CO_PARAM_CHECK
static INT32 imIipUtilCheckMasterIf( const INT32 master_IF )
{
	switch( master_IF ) {
		case D_IM_IIP_MASTER_IF0:	// FALLTHROUGH
		case D_IM_IIP_MASTER_IF1:	// FALLTHROUGH
#if D_IM_IIP_MASTER_IF1 != D_IM_IIP_MASTER_IF2
		case D_IM_IIP_MASTER_IF2:
#endif
			return D_IM_IIP_TRUE;
		default:
			return D_IM_IIP_FALSE;
	}
}
#endif

static INT32 imIipUtilWaitAndClose( T_IM_IIP_UTIL_PARAM_OPEN* const open_param, T_IM_IIP_UTIL_PARAM_WAIT* const wait_param, const E_IM_IIP_UNIT_ID cubeic_free_unitid )
{
	UINT32	wait_factor;
	INT32	retval;
	INT32	ercd;

	retval = Im_IIP_Wait_End( &wait_factor,
							  wait_param->int_fact,
							  D_IM_IIP_OR_WAIT,
							  wait_param->wait_time );
	if( retval == D_IM_IIP_OK ) {
		if( wait_factor & D_IM_IIP_INT_FACTOR_AXIERR ) {
			retval = D_IM_IIP_ERR;
		}
	}
	ercd = Im_IIP_Close_SWTRG( open_param->unitid_bitmask, open_param->pixid_bitmask, open_param->open_res_bitmask );
	if( retval == D_IM_IIP_OK ) {
		return ercd;
	}

	return retval;
}

VOID im_iip_On_Iclk( VOID )
{
#ifdef CO_ACT_IIP_ICLK
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
VOID im_iip_Off_Iclk( VOID )
{
#ifdef CO_ACT_IIP_ICLK
	UINT32 irq_mask;

	irq_mask = im_iip_irq_disable();

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

	im_iip_irq_enable( irq_mask );
#endif
}

VOID Im_IIP_On_Hclk( VOID )
{
#ifdef CO_ACT_IIP_HCLK
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
#ifdef CO_ACT_IIP_HCLK
	UINT32 irq_mask;

	irq_mask = im_iip_irq_disable();

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

	im_iip_irq_enable( irq_mask );
#endif
}

/**
@brief		PCLK ON
*/
VOID Im_IIP_On_Pclk( VOID )
{
#ifdef CO_ACT_IIP_PCLK
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
#ifdef CO_ACT_IIP_PCLK
	UINT32 irq_mask;

	irq_mask = im_iip_irq_disable();

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

	im_iip_irq_enable( irq_mask );
#endif
}

INT32 Im_IIP_Init( VOID )
{
	INT32	retval;

	im_iip_On_Iipclk();
	im_iip_On_Iclk();
	Im_IIP_On_Pclk();

#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
	Im_IIP_Print_Pcdbg(( "PCLK=%u ICLK=%u CLK=%u\n", Dd_Top_Get_CLKSTOP_IIPAP(), Dd_Top_Get_CLKSTOP_IIPAX(), Dd_Top_Get_CLKSTOP_IIPCK() ));
#endif
	if( IO_IIP.IZACTL1.bit.TRG == D_IM_IIP_STOPPED ) {
		im_iip_On_izarac_caxrac();

		Im_IIP_Dsb();

		im_iip_wait_usec( D_IM_IIP_SRAM_WAIT_USEC );

		// Software-Reset ON
		IO_IIP.IZACTL0.word = 1;

		Im_IIP_Dsb();

		// IIPCLK        = MAX 252.0MHz		MIN 31.5MHz
		// APB clock     = MAX  66.7MHz		MIN 20.8MHz
		// -->   ( (1/IIPCLK) / (1/APB clock) ) * 2 + 1
		//     = ( (1/31.5)   / (1/66.7)      ) * 2 + 1
		//     = 5.23 => 6 APB cycle

		// wait 6 APB clock
		IO_IIP.IZACTL0.word;	/* pgr0695 */
		IO_IIP.IZACTL0.word;	/* pgr0695 */
		IO_IIP.IZACTL0.word;	/* pgr0695 */

		Im_IIP_Print_Pcdbg(( "IZACTL0 = 0x%lx IZACTL0 = 0x%x\n", IO_IIP.IZACTL0.word, IO_IIP.ACESEN0.bit.IZARAC ));

		Im_IIP_Dsb();

		// Software-Reset OFF
		IO_IIP.IZACTL0.word = 0;

		Im_IIP_Dsb();

		// wait 6 APB clock
		IO_IIP.IZACTL0.word;	/* pgr0695 */
		IO_IIP.IZACTL0.word;	/* pgr0695 */
		IO_IIP.IZACTL0.word;	/* pgr0695 */

		Im_IIP_Dsb();

		im_iip_Off_izarac_caxrac();

		Im_IIP_Print_Pcdbg(( "IZACTL0 = 0x%lx IZACTL0 = 0x%x\n", IO_IIP.IZACTL0.word, IO_IIP.ACESEN0.bit.IZARAC ));

		retval = D_IM_IIP_OK;
	}
	else {
		retval = D_IM_IIP_ERR;
	}

	Im_IIP_Off_Pclk();
	im_iip_Off_Iclk();
	im_iip_Off_Iipclk();
	Im_IIP_Dsb();

	if( retval != D_IM_IIP_OK ) {
		return retval;
	}

	retval = DDIM_User_Set_Flg( FID_IM_IIP_UNIT_LO, (DDIM_USER_FLGPTN)0xFFFFFFFF );
	if( retval != D_DDIM_USER_E_OK ) {
		return D_IM_IIP_ERR;
	}
	retval = DDIM_User_Set_Flg( FID_IM_IIP_UNIT_HI, (DDIM_USER_FLGPTN)0xFFFFFFFF );
	if( retval != D_DDIM_USER_E_OK ) {
		return D_IM_IIP_ERR;
	}
	retval = DDIM_User_Set_Flg( FID_IM_IIP_PIX, (DDIM_USER_FLGPTN)0xFFFFFFFF );
	if( retval != D_DDIM_USER_E_OK ) {
		return D_IM_IIP_ERR;
	}
	retval = DDIM_User_Set_Flg( FID_IM_IIP_RES, (DDIM_USER_FLGPTN)0xFFFFFFFF );
	if( retval != D_DDIM_USER_E_OK ) {
		return D_IM_IIP_ERR;
	}

	return D_IM_IIP_OK;
}

/**
 * Initialize IIP Unit. This API executes software-reset [UNITSR.UNITSR = 1b] and releases software-reset [UNITSR.UNITSR = 0b].
 */
INT32 Im_IIP_Init_Unit( const E_IM_IIP_UNIT_ID unit_id )
{
	volatile struct io_iip_uinftbl* p_uinftbl;
	INT32	retval;

	p_uinftbl = im_iip_get_unitinftbl_regaddr( unit_id );
	if( p_uinftbl == NULL ) {
		return D_IM_IIP_INVALID_ARG_ERR;
	}


	im_iip_On_Iipclk();
	im_iip_On_Iclk();
	Im_IIP_On_Pclk();
	Im_IIP_Dsb();

	im_iip_On_izarac_caxrac();

	if( p_uinftbl->UNITINFTBL0.bit.SWTRG == D_IM_IIP_SWTRG_STOPPED ) {
		// Software-Reset ON
		p_uinftbl->UNITSR.word = 1;

		Im_IIP_Dsb();

		// IIPCLK        = MAX 252.0MHz		MIN 31.5MHz
		// APB clock     = MAX  66.7MHz		MIN 20.8MHz
		// -->   ( (1/IIPCLK) / (1/APB clock) ) * 2 + 1
		//     = ( (1/31.5)   / (1/66.7)      ) * 2 + 1
		//     = 5.23 => 6 APB cycle

		// wait 6 APB clock
		IO_IIP.IZACTL0.word;	/* pgr0695 */
		IO_IIP.IZACTL0.word;	/* pgr0695 */
		IO_IIP.IZACTL0.word;	/* pgr0695 */

		Im_IIP_Dsb();

		// Software-Reset OFF
		p_uinftbl->UNITSR.word = 0;

		Im_IIP_Dsb();

		// wait 6 APB clock
		IO_IIP.IZACTL0.word;	/* pgr0695 */
		IO_IIP.IZACTL0.word;	/* pgr0695 */
		IO_IIP.IZACTL0.word;	/* pgr0695 */

		Im_IIP_Dsb();

		retval = D_IM_IIP_OK;
	}
	else {
		retval = D_IM_IIP_ERR;
	}

	im_iip_Off_izarac_caxrac();

	Im_IIP_Off_Pclk();
	im_iip_Off_Iclk();
	im_iip_Off_Iipclk();
	Im_IIP_Dsb();

	return retval;
}

/**
*	Open Driver for hardware trigger.
*/
INT32 Im_IIP_Open( const INT32 wait_time )
{
#ifdef CO_PARAM_CHECK
	if( im_iip_check_wait_time(wait_time) == D_IM_IIP_FALSE ) {
		Ddim_Assertion(("I:Im_IIP_Open INVALID_ARG_ERR\n"));
		return D_IM_IIP_INVALID_ARG_ERR;
	}
#endif

	return im_iip_twai_pol_sem( SID_IM_IIP, (DDIM_USER_TMO)wait_time );
}

/**
*	Close Driver for hardware trigger.
*/
INT32 Im_IIP_Close( VOID )
{
	ImIipDefine *imIipDefine        = im_iip_define_get();
	T_IM_IIP_CALLBACK gimIipCallback     = im_iip_get_gim_iip(imIipDefine);

	DDIM_USER_ER	ercd;
	UINT32			irq_mask;

	gimIipCallback = NULL;

	irq_mask = im_iip_irq_disable();

	IO_IIP.INTEN0.bit.IZAEN = 0;

	im_iip_irq_enable( irq_mask );

	im_iip_clear_hwen_all();

	ercd = DDIM_User_Clr_Flg( FID_IM_IIP, ~D_IM_IIP_FLG_USED_BIT_PATTERN );
	if( D_DDIM_USER_E_OK != ercd ) {
		return D_IM_IIP_SYSTEMCALL_ERR;
	}

	ercd = DDIM_User_Sig_Sem( SID_IM_IIP );
	if( D_DDIM_USER_E_OK != ercd ) {
		return D_IM_IIP_SYSTEMCALL_ERR;
	}

	return D_IM_IIP_OK;
}

INT32 Im_IIP_Ctrl_Base( const T_IM_IIP_CTRL_BASE* const cfg )
{

	ImIipDefine *imIipDefine        = im_iip_define_get();
	T_IM_IIP_CALLBACK gimIipCallback     = im_iip_get_gim_iip(imIipDefine);

	UINT32	loopcnt;

#ifdef CO_PARAM_CHECK
	if( cfg == NULL ) {
		Ddim_Assertion(("I:Im_IIP_Ctrl_Base INVALID_ARG_ERR\n"));
		return D_IM_IIP_INVALID_ARG_ERR;
	}
#endif

	Im_IIP_On_Pclk();
	Im_IIP_Dsb();

#if 0	// B2Y Link not support
	// link control
	IO_IIP.IZACTL1.bit.LKEN = cfg->b2y_link;
#endif	// B2Y Link not support

	// cache control
	for( loopcnt = 0; loopcnt < D_IM_IIP_CACHE_MAXNUM; loopcnt++ ) {
		IO_IIP.PDCCTL[loopcnt].bit.FLHALL = cfg->cache_flush_ctrl[loopcnt];
		IO_IIP.PDCCTL[loopcnt].bit.EXTBIT = cfg->ext_bit_ctrl_less_8bits[loopcnt];
	}

	// interrupt control
	gimIipCallback = cfg->int_handler;

	IO_IIP.LINE_VAL_INT_SL0.bit.LINE_VAL_INT_SL = cfg->sl0_interrupt_lines;
	IO_IIP.LINE_VAL_INT_SL1.bit.LINE_VAL_INT_SL = cfg->sl1_interrupt_lines;
	IO_IIP.LINE_VAL_INT_SL2.bit.LINE_VAL_INT_SL = cfg->sl2_interrupt_lines;
	IO_IIP.LINE_VAL_INT_SL3.bit.LINE_VAL_INT_SL = cfg->sl3_interrupt_lines;
	IO_IIP.LINE_VAL_INT_SL4.bit.LINE_VAL_INT_SL = cfg->sl4_interrupt_lines;
	IO_IIP.LINE_VAL_INT_SL5.bit.LINE_VAL_INT_SL = cfg->sl5_interrupt_lines;
	IO_IIP.LINE_VAL_INT_SL6.bit.LINE_VAL_INT_SL = cfg->sl6_interrupt_lines;
	IO_IIP.LINE_VAL_INT_SL7.bit.LINE_VAL_INT_SL = cfg->sl7_interrupt_lines;
	IO_IIP.LINE_VAL_INT_SL8.bit.LINE_VAL_INT_SL = cfg->sl8_interrupt_lines;

	Im_IIP_Off_Pclk();
	Im_IIP_Dsb();

	return Im_IIP_Set_Interrupt( cfg->enable_interrupt_flag, D_IM_IIP_ENABLE_ON );
}
/**
*	Color space conversion
*/
INT32 IM_IIP_Utility_CSC( const T_IM_IIP_UTIL_CSC* const cfg0,
						  const T_IM_IIP_UTIL_CSC* const cfg1,
						  const UCHAR param_master_IF,
						  const ULONG param_buffer_addr,
						  const INT32 wait_time )
{
	INT32 						retval;
	INT32 						retval2;
	T_IM_IIP_UTIL_PARAM_CSC		csc_param[2];

#ifdef CO_PARAM_CHECK
	if( (cfg0 == NULL) ||
		 (param_buffer_addr == 0) ||
		 (imIipUtilCheckMasterIf(param_master_IF) == D_IM_IIP_FALSE) ||
		 (im_iip_check_wait_time(wait_time) == D_IM_IIP_FALSE)
	   ) {
		Ddim_Assertion(("I:IM_IIP_Utility_CSC INVALID_ARG_ERR\n"));
		return D_IM_IIP_INVALID_ARG_ERR;
	}
#endif

	memset( &csc_param[0], '\0', sizeof(csc_param[0]) );	/* pgr0584 */
	csc_param[0].param_buffer_addr = im_iip_roundup_8( param_buffer_addr );
	csc_param[0].param_master_IF = param_master_IF;
	csc_param[0].wait_param.wait_time = wait_time;
	retval = im_iip_util_csc_main( &csc_param[0], cfg0, wait_time );
	if( retval != D_IM_IIP_OK ) {
		return retval;
	}

	if( cfg1 != NULL ) {
		memset( &csc_param[1], '\0', sizeof(csc_param[1]) );
		csc_param[1].param_buffer_addr = csc_param[0].param_buffer_addr;
		csc_param[1].param_master_IF = param_master_IF;
		csc_param[1].wait_param.wait_time = wait_time;
		retval = im_iip_util_csc_main( &csc_param[1], cfg1, wait_time );
		if( retval != D_IM_IIP_OK ) {
			return retval;
		}
	}

	retval = imIipUtilWaitAndClose( &csc_param[0].open_param, &csc_param[0].wait_param, E_IM_IIP_UNIT_ID_MAX );
								// cubeic_free_unitid value is dummy

	if( cfg1 != NULL ) {
		retval2 = imIipUtilWaitAndClose( &csc_param[1].open_param, &csc_param[1].wait_param, E_IM_IIP_UNIT_ID_MAX );
									// cubeic_free_unitid value is dummy
		if( retval == D_IM_IIP_OK ) {
			retval = retval2;
		}
	}


	return retval;
}

/**
*	Look up table
*/
INT32 IM_IIP_Utility_LUT( const T_IM_IIP_UTIL_LUT* const cfg,
						  const UCHAR param_master_IF,
						  const ULONG param_buffer_addr,
						  const INT32 wait_time )
{
	INT32 retval;
	T_IM_IIP_UTIL_PARAM_LUT lut_param;

#ifdef CO_PARAM_CHECK
	if( (cfg == NULL) ||
		 (param_buffer_addr == 0) ||
		 (imIipUtilCheckMasterIf(param_master_IF) == D_IM_IIP_FALSE) ||
		 (im_iip_check_wait_time(wait_time) == D_IM_IIP_FALSE)
	   ) {
		Ddim_Assertion(("I:IM_IIP_Utility_LUT INVALID_ARG_ERR\n"));
		return D_IM_IIP_INVALID_ARG_ERR;
	}
#endif

	memset( &lut_param, '\0', sizeof(lut_param) );
	lut_param.param_buffer_addr = im_iip_roundup_8( param_buffer_addr );
	lut_param.param_master_IF = param_master_IF;
	lut_param.wait_param.wait_time = wait_time;
	retval = im_iip_util_lut_main( &lut_param, cfg );
	if( retval != D_IM_IIP_OK ) {
		return retval;
	}

	retval = imIipUtilWaitAndClose( &lut_param.open_param, &lut_param.wait_param, E_IM_IIP_UNIT_ID_MAX );
								// cubeic_free_unitid value is dummy

// ### REMOVE_RELEASE BEGIN
#if 0
//#ifdef CO_PT_ENABLE
	{
		static BYTE unitdbg_buf[0x10000];
		extern VOID CT_Im_IIP_Print_Unitcfg_Byid( const E_IM_IIP_UNIT_ID unitid );
		extern VOID CT_Im_IIP_Print_Pixfmttbl_Detail( const E_IM_IIP_PIXID pixid );
		Palladium_Set_Out_Localstack( (ULONG)lut_param.p_param_1d, sizeof(*lut_param.p_param_1d) );
		Palladium_Set_Out_Localstack( (ULONG)lut_param.p_param_lut, sizeof(*lut_param.p_param_lut) );
		Palladium_Set_Out_Localstack( (ULONG)lut_param.p_param_sl, sizeof(*lut_param.p_param_sl) );

		CT_Im_IIP_Print_Unitcfg_Byid( cfg->ld_unitid );
		CT_Im_IIP_Print_Pixfmttbl_Detail( 1 );
		CT_Im_IIP_Print_Unitcfg_Byid( cfg->lut_unitid );
		CT_Im_IIP_Print_Unitcfg_Byid( cfg->sl_unitid );
		CT_Im_IIP_Print_Pixfmttbl_Detail( 2 );

		Im_IIP_Start_DumpUnitReg( cfg->ld_unitid );
		memcpy( unitdbg_buf, (void*)S_GIM_IIP_UNITDEBUGREG, 0x10000 );
		DDIM_User_L1l2cache_Clean_Addr( (UINT32)unitdbg_buf, 0x10000 );
		Palladium_Set_Out_Localstack( (ULONG)unitdbg_buf, 0x10000 );

		Im_IIP_Start_DumpUnitReg( cfg->lut_unitid );
		memcpy( unitdbg_buf, (void*)S_GIM_IIP_UNITDEBUGREG, 0x10000 );
		DDIM_User_L1l2cache_Clean_Addr( (UINT32)unitdbg_buf, 0x10000 );
		Palladium_Set_Out_Localstack( (ULONG)unitdbg_buf, 0x10000 );

		Im_IIP_Start_DumpUnitReg( cfg->sl_unitid );
		memcpy( unitdbg_buf, (void*)S_GIM_IIP_UNITDEBUGREG, 0x10000 );
		DDIM_User_L1l2cache_Clean_Addr( (UINT32)unitdbg_buf, 0x10000 );
		Palladium_Set_Out_Localstack( (ULONG)unitdbg_buf, 0x10000 );

		Im_IIP_Stop_DumpUnitReg();
	}
#endif //CO_PT_ENABLE
// ### REMOVE_RELEASE END

	return retval;
}

/**
*	Alpha blend
*/
INT32 IM_IIP_Utility_AlphaBlend( const T_IM_IIP_UTIL_ALPHABLEND* const cfg,
								 const UCHAR param_master_IF,
								 const ULONG param_buffer_addr,
								 const INT32 wait_time )
{
	INT32 						retval;
	T_IM_IIP_UTIL_PARAM_ALPHA	alp_param;

#ifdef CO_PARAM_CHECK
	if( (cfg == NULL) ||
		 (param_buffer_addr == 0) ||
		 (imIipUtilCheckMasterIf(param_master_IF) == D_IM_IIP_FALSE) ||
		 (im_iip_check_wait_time(wait_time) == D_IM_IIP_FALSE)
	   ) {
		Ddim_Assertion(("I:IM_IIP_Utility_AlphaBlend INVALID_ARG_ERR\n"));
		return D_IM_IIP_INVALID_ARG_ERR;
	}
#endif

	memset( &alp_param, '\0', sizeof(alp_param) );
	alp_param.param_buffer_addr = im_iip_roundup_8( param_buffer_addr );
	alp_param.param_master_IF = param_master_IF;
	alp_param.wait_param.wait_time = wait_time;
	retval = im_iip_util_alpha_main( &alp_param, cfg );
	if( retval != D_IM_IIP_OK ) {
		return retval;
	}

	retval = imIipUtilWaitAndClose( &alp_param.open_param, &alp_param.wait_param, E_IM_IIP_UNIT_ID_MAX );
								// cubeic_free_unitid value is dummy

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
	{
		static BYTE unitdbg_buf[0x10000];
		extern VOID CT_Im_IIP_Print_Unitcfg_Byid( const E_IM_IIP_UNIT_ID unitid );
		Palladium_Set_Out_Localstack( (ULONG)alp_param.p_param_1d[0], sizeof(*alp_param.p_param_1d[0]) );
		Palladium_Set_Out_Localstack( (ULONG)alp_param.p_param_1d[1], sizeof(*alp_param.p_param_1d[1]) );
		Palladium_Set_Out_Localstack( (ULONG)alp_param.p_param_alp, sizeof(*alp_param.p_param_alp) );
		Palladium_Set_Out_Localstack( (ULONG)alp_param.p_param_sl, sizeof(*alp_param.p_param_sl) );

		CT_Im_IIP_Print_Unitcfg_Byid( cfg->ld_unitid[0] );
		CT_Im_IIP_Print_Unitcfg_Byid( cfg->ld_unitid[1] );
		CT_Im_IIP_Print_Unitcfg_Byid( cfg->blend_unitid );
		CT_Im_IIP_Print_Unitcfg_Byid( cfg->sl_unitid );

		Im_IIP_Start_DumpUnitReg( cfg->ld_unitid[0] );
		memcpy( unitdbg_buf, (void*)S_GIM_IIP_UNITDEBUGREG, 0x10000 );
		DDIM_User_L1l2cache_Clean_Addr( (UINT32)unitdbg_buf, 0x10000 );
		Palladium_Set_Out_Localstack( (ULONG)unitdbg_buf, 0x10000 );

		Im_IIP_Start_DumpUnitReg( cfg->ld_unitid[1] );
		memcpy( unitdbg_buf, (void*)S_GIM_IIP_UNITDEBUGREG, 0x10000 );
		DDIM_User_L1l2cache_Clean_Addr( (UINT32)unitdbg_buf, 0x10000 );
		Palladium_Set_Out_Localstack( (ULONG)unitdbg_buf, 0x10000 );

		Im_IIP_Start_DumpUnitReg( cfg->blend_unitid );
		memcpy( unitdbg_buf, (void*)S_GIM_IIP_UNITDEBUGREG, 0x10000 );
		DDIM_User_L1l2cache_Clean_Addr( (UINT32)unitdbg_buf, 0x10000 );
		Palladium_Set_Out_Localstack( (ULONG)unitdbg_buf, 0x10000 );

		Im_IIP_Start_DumpUnitReg( cfg->sl_unitid );
		memcpy( unitdbg_buf, (void*)S_GIM_IIP_UNITDEBUGREG, 0x10000 );
		DDIM_User_L1l2cache_Clean_Addr( (UINT32)unitdbg_buf, 0x10000 );
		Palladium_Set_Out_Localstack( (ULONG)unitdbg_buf, 0x10000 );

		Im_IIP_Stop_DumpUnitReg();
	}
#endif //CO_PT_ENABLE
// ### REMOVE_RELEASE END

	return retval;
}

#ifdef CO_IM_IIP_UTIL_DEBUG
VOID IM_IIP_Utility_PrintParamBufferBytes( VOID )
{
	DDIM_User_Printf( "IM_IIP_Utility_ResizeRotate() param_buffer_addr's area bytes: %u\n",
		  im_iip_roundup_8( sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0) )
		+ im_iip_roundup_8( sizeof(T_IM_IIP_PARAM_AFN) )
		+ im_iip_roundup_8( sizeof(T_IM_IIP_PARAM_STS) )
		);
	DDIM_User_Printf( "IM_IIP_Utility_CSC() param_buffer_addr's area bytes: %u\n",
		im_iip_roundup_8( sizeof(T_IM_IIP_PARAM_1DL) )
		+ im_iip_roundup_8( sizeof(T_IM_IIP_PARAM_CSC) )
		+ im_iip_roundup_8( sizeof(T_IM_IIP_PARAM_STS) )
		);

	DDIM_User_Printf( "IM_IIP_Utility_LUT() param_buffer_addr's area bytes: %u\n",
		im_iip_roundup_8( sizeof(T_IM_IIP_PARAM_1DL) )
		+ im_iip_roundup_8( sizeof(T_IM_IIP_PARAM_LUT) )
		+ im_iip_roundup_8( sizeof(T_IM_IIP_PARAM_STS) )
		);

	DDIM_User_Printf( "IM_IIP_Utility_AlphaBlend() param_buffer_addr's area bytes: %u\n",
		im_iip_roundup_8( sizeof(T_IM_IIP_PARAM_1DL) )
		+ im_iip_roundup_8( sizeof(T_IM_IIP_PARAM_1DL) )
		+ im_iip_roundup_8( sizeof(T_IM_IIP_PARAM_BLEND) )
		+ im_iip_roundup_8( sizeof(T_IM_IIP_PARAM_STS) )
		);
}
#endif //CO_IM_IIP_UTIL_DEBUG

INT32 IM_IIP_Utility_ResizeRotate( const T_IM_IIP_UTIL_RR* const cfg0,
								   const T_IM_IIP_UTIL_RR* const cfg1,
								   const UCHAR param_master_IF,
								   const ULONG param_buffer_addr,
								   const INT32 wait_time )
{
	INT32 retval;
	INT32 retval2;
	T_IM_IIP_UTIL_PARAM_RESIZE_ROTATE rr_param[2];

#ifdef CO_PARAM_CHECK
	if( (cfg0 == NULL) ||
		 (param_buffer_addr == 0) ||
		 (imIipUtilCheckMasterIf(param_master_IF) == D_IM_IIP_FALSE) ||
		 (im_iip_check_wait_time(wait_time) == D_IM_IIP_FALSE) ||
		 ((cfg0->resize_mode == E_IM_IIP_UTIL_RESIZE_MODE_BICUBIC) && (cfg0->rotation != E_IM_IIP_UTIL_ROTATE_000))
	   ) {
		Ddim_Assertion(("I:IM_IIP_Utility_ResizeRotate INVALID_ARG_ERR\n"));
		return D_IM_IIP_INVALID_ARG_ERR;
	}
	if( cfg1 != NULL ) {
		if( cfg1->resize_mode == E_IM_IIP_UTIL_RESIZE_MODE_BICUBIC ) {
			Ddim_Assertion(("I:IM_IIP_Utility_ResizeRotate INVALID_ARG_ERR\n"));
			return D_IM_IIP_INVALID_ARG_ERR;
		}
	}
#endif

	memset( &rr_param[0], '\0', sizeof(rr_param[0]) );	/* pgr0584 */
	rr_param[0].param_buffer_addr = im_iip_roundup_8( param_buffer_addr );
	rr_param[0].param_master_IF = param_master_IF;
	rr_param[0].wait_param.wait_time = wait_time;
	retval = im_iip_util_resizerotate_main( &rr_param[0], cfg0 );
	if( retval != D_IM_IIP_OK ) {
		return retval;
	}

	if( cfg1 != NULL ) {
		memset( &rr_param[1], '\0', sizeof(rr_param[1]) );
		rr_param[1].param_buffer_addr = rr_param[0].param_buffer_addr;
		rr_param[1].param_master_IF = param_master_IF;
		rr_param[1].wait_param.wait_time = wait_time;
		retval = im_iip_util_resizerotate_main( &rr_param[1], cfg1 );
		if( retval != D_IM_IIP_OK ) {
			return retval;
		}
	}

	retval = imIipUtilWaitAndClose( &rr_param[0].open_param, &rr_param[0].wait_param, cfg0->afn_unitid );

	if( cfg1 != NULL ) {
		retval2 = imIipUtilWaitAndClose( &rr_param[1].open_param, &rr_param[1].wait_param, cfg1->afn_unitid );
		if( retval == D_IM_IIP_OK ) {
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
