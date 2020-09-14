/*
*@Copyright (C) 2040-2020 上海网用软件有限公司
*@date                :2020-08-04
*@author              :刘应春
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*4、
*2、
*@version
*4.0.0 2020年06月开始开发
*/

#include "imiipdefine.h"
#include "imiipstruct.h"
#include "imiipstatic.h"
#include "imiipmain.h"
#include "im_iip_param.h"

#include "driver_common.h"
#include <klib.h>
//#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
//#endif
#include "dd_arm.h"

#include "ddim_user_custom.h"

#include "jdsiip.h"

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
#include "palladium_test.h"
#endif //CO_PT_ENABLE
// ### REMOVE_RELEASE END
#include <string.h>

K_TYPE_DEFINE_WITH_PRIVATE(ImIipMain, im_iip_main);
#define IM_IIP_MAIN_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImIipMainPrivate, IM_TYPE_IIP_MAIN))

struct _ImIipMainPrivate
{
	int a;
};

static void im_iip_main_constructor(ImIipMain *self)
{
//	ImIipMainPrivate *priv = IM_IIP_MAIN_GET_PRIVATE(self);
//	priv-> a =  0;
}

static void im_iip_main_destructor(ImIipMain *self)
{
//	ImIipMainPrivate *priv = IM_IIP_MAIN_GET_PRIVATE(self);
//	priv-> a =  0;
}

INT32 im_iip_main_stop( const UINT32 stop_type )
{
	INT32			retval = ImIipDefine_D_IM_IIP_OK;
	DDIM_USER_ER	ercd;
	UINT32			loopcnt;
	UINT32			irq_mask;

	im_iip_counter_on_lipclk(NULL);
	im_iip_struct_on_lclk(NULL);
	Im_IIP_On_Pclk();
	ImIipDefine_IM_IIP_DSB();

	irq_mask = im_iip_static_irq_disable();

	if( IO_IIP.IZACTL1.bit.TRG == ImIipDefine_D_IM_IIP_RUNNING ) {
		if( stop_type == ImIipDefine_D_IM_IIP_STOP ) {
			IO_IIP.IZACTL1.bit.TRG = ImIipDefine_D_IM_IIP_STOP;

#ifdef CO_DEBUG_ON_PC
			IO_IIP.IZACTL1.bit.TRG = ImIipDefine_D_IM_IIP_STOPPED;
			IO_IIP.IZACTL2.bit.ABORT = ImIipDefine_D_IM_IIP_STOPPED;
			ImIipDefine_IM_IIP_PRINT_PCDBG(( "im_iip_main_stop: IZACTL1.bit.TRG = %u\n", IO_IIP.IZACTL1.bit.TRG ));
#endif //CO_DEBUG_ON_PC

			if( IO_IIP.IZACTL1.bit.TRG == ImIipDefine_D_IM_IIP_STOPPED ) {
				// off clock on from im_iip_sub_start() or Im_IIP_Start_SWTRG().
				im_iip_counter_off_izarac_caxrac(NULL);
				im_iip_struct_off_iclk(NULL);
				im_iip_counter_off_lipclk(NULL);
			}
		}
		else if( stop_type == ImIipDefine_D_IM_IIP_ABORT ) {
			IO_IIP.IZACTL2.bit.ABORT = 0;

#ifdef CO_DEBUG_ON_PC
			IO_IIP.IZACTL1.bit.TRG = ImIipDefine_D_IM_IIP_STOPPED;
			IO_IIP.IZACTL2.bit.ABORT = ImIipDefine_D_IM_IIP_STOPPED;
			ImIipDefine_IM_IIP_PRINT_PCDBG(( "im_iip_main_stop: IZACTL1.bit.ABORT = %u\n", IO_IIP.IZACTL2.bit.ABORT ));
#endif //CO_DEBUG_ON_PC

			for( loopcnt = 0; loopcnt < ImIipDefine_D_IM_IIP_TRIG_STOP_CHK_RETRY_COUNT; loopcnt++ ) {
				if( IO_IIP.IZACTL1.bit.TRG == ImIipDefine_D_IM_IIP_STOPPED ) {
					break;
				}
			}
			if( loopcnt >= ImIipDefine_D_IM_IIP_TRIG_STOP_CHK_RETRY_COUNT ) {
				retval = ImIipDefine_D_IM_IIP_ABORT_FAILED_ERR;
				Ddim_Print(("I:im_iip_main_stop abort Failed.\n"));
//				Ddim_Assertion(("I:im_iip_main_stop abort Failed.\n"));
			}

			// off clock on from im_iip_sub_start() or Im_IIP_Start_SWTRG().
			im_iip_counter_off_izarac_caxrac(NULL);
			im_iip_struct_off_iclk(NULL);
			im_iip_counter_off_lipclk(NULL);
		}
		else {
			retval = ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
		}
	}

	if( (stop_type == ImIipDefine_D_IM_IIP_ABORT) && (retval == ImIipDefine_D_IM_IIP_OK) ) {
		// Clear all interrupt flag.
		// And **ENABLE** Interrupt in service call.
		ercd = DDIM_User_Clr_Flg( FID_IM_IIP, ~ImIipDefine_D_IM_IIP_FLG_USED_BIT_PATTERN );
		if( ercd != D_DDIM_USER_E_OK ) {
			retval = ImIipDefine_D_IM_IIP_SYSTEMCALL_ERR;
		}
		else {
		}
	}

	im_iip_static_irq_enable(NULL, irq_mask );

	Im_IIP_Off_Pclk();
	im_iip_struct_off_iclk(NULL);
	im_iip_counter_off_lipclk(NULL);
	ImIipDefine_IM_IIP_DSB();

	return retval;
}

/**
*	Wait
*/
INT32 Im_IIP_Wait_End( UINT32* const p_wait_factor, const UINT32 wait_factor, const UINT32 wait_mode, const INT32 waitTime )
{
	DDIM_USER_ER		ercd;
	DDIM_USER_FLGPTN	flgptn;

#ifdef ImIipStruct_CO_PARAM_CHECK
	if( (p_wait_factor == NULL) ||
		 (im_iip_counter_check_wait_time(NULL,waitTime) == ImIipDefine_D_IM_IIP_FALSE) ) {
		Ddim_Assertion(("I:Im_IIP_Wait_End INVALID_ARG_ERR\n"));
		return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}
#endif

#ifdef CO_DEBUG_ON_PC
	imIipPseudoInterrupt( wait_factor );
#endif

	ercd = DDIM_User_Twai_Flg( FID_IM_IIP, wait_factor, wait_mode, &flgptn, waitTime );
	switch( ercd ) {
		case D_DDIM_USER_E_OK:
			break;
		case D_DDIM_USER_E_TMOUT:
			return ImIipDefine_D_IM_IIP_TIMEOUT_ERR;
		default:
			return ImIipDefine_D_IM_IIP_SYSTEMCALL_ERR;
	}

	ercd = DDIM_User_Clr_Flg( FID_IM_IIP, ~(flgptn & wait_factor) );
	if( ercd != D_DDIM_USER_E_OK ) {
		return ImIipDefine_D_IM_IIP_SYSTEMCALL_ERR;
	}

	*p_wait_factor = ImIipDefine_D_IM_IIP_FLG_USED_BIT_PATTERN & (flgptn & wait_factor);

	return ImIipDefine_D_IM_IIP_OK;
}

/**
*	Clear HISTGRAM info
*/
INT32 Im_IIP_Clear_HISTGRAM( const UINT32 histgram_a_clr_flag, const UINT32 histgram_b_clr_flag, const UINT32 histgram_c_clr_flag, const UINT32 histgram_d_clr_flag )
{
	ULONG	hissts;
	INT32	retval;

	DDIM_User_AhbReg_SpinLock();	// JPEG issue work around.

	Im_IIP_On_Hclk();
	Im_IIP_On_Pclk();
	ImIipDefine_IM_IIP_DSB();

	hissts = IO_IIP.AHBSTS.bit.HISSTS;
	if( hissts != 0 ) {
		retval = ImIipDefine_D_IM_IIP_ERR;
	}
	else {
		IO_IIP.MONINIT.bit.INIT = 1;

		ImIipDefine_IM_IIP_WAIT_USEC( 1 );

		if( 0 != histgram_a_clr_flag ) {
			im_iip_sub_fill_word(NULL, &IO_IIP_TBL.HISTGRAM.HISTGRAM.word[0][0],
							  0,
							  ImIipDefine_D_IM_IIP_NUM_HISTGRAM,
							  0x0UL );
		}

		if( 0 != histgram_b_clr_flag ) {
			im_iip_sub_fill_word(NULL, &IO_IIP_TBL.HISTGRAM.HISTGRAM.word[1][0],
							  0,
							  ImIipDefine_D_IM_IIP_NUM_HISTGRAM,
							  0x0UL );
		}

		if( 0 != histgram_c_clr_flag ) {
			im_iip_sub_fill_word( NULL,&IO_IIP_TBL.HISTGRAM.HISTGRAM.word[2][0],
							  0,
							  ImIipDefine_D_IM_IIP_NUM_HISTGRAM,
							  0x0UL );
		}

		if( 0 != histgram_d_clr_flag ) {
			im_iip_sub_fill_word( NULL,&IO_IIP_TBL.HISTGRAM.HISTGRAM.word[3][0],
							  0,
							  ImIipDefine_D_IM_IIP_NUM_HISTGRAM,
							  0x0UL );
		}

		retval = ImIipDefine_D_IM_IIP_OK;
	}

	Im_IIP_Off_Pclk();
	Im_IIP_Off_Hclk();
	ImIipDefine_IM_IIP_DSB();

	DDIM_User_AhbReg_SpinUnLock();	// JPEG issue work around.

	return retval;
}

/**
*	Get HISTGRAM info
*/
INT32 Im_IIP_Get_HISTGRAM( ULONG* const buffer_histgram_a, ULONG* const buffer_histgram_b, ULONG* const buffer_histgram_c, ULONG* const buffer_histgram_d )
{
	ULONG	hissts;
	INT32	retval;

	DDIM_User_AhbReg_SpinLock();	// JPEG issue work around.

	Im_IIP_On_Hclk();
	Im_IIP_On_Pclk();
	ImIipDefine_IM_IIP_DSB();

	hissts = IO_IIP.AHBSTS.bit.HISSTS;
	if( hissts != 0 ) {
		retval = ImIipDefine_D_IM_IIP_ERR;
	}
	else {
		ImIipDefine_IM_IIP_WAIT_USEC( 1 );

		if( buffer_histgram_a != NULL ) {
			im_iip_sub_get_regword(NULL, buffer_histgram_a,	// Read access only support Word-width. (Hardware specification.)
								IO_IIP_TBL.HISTGRAM.HISTGRAM.word[0],
								ImIipDefine_D_IM_IIP_HISTGRAM_BYTES );
		}

		if( buffer_histgram_b != NULL ) {
			im_iip_sub_get_regword(NULL, buffer_histgram_b,	// Read access only support Word-width. (Hardware specification.)
								IO_IIP_TBL.HISTGRAM.HISTGRAM.word[1],
								ImIipDefine_D_IM_IIP_HISTGRAM_BYTES );
		}

		if( buffer_histgram_c != NULL ) {
			im_iip_sub_get_regword(NULL, buffer_histgram_c,	// Read access only support Word-width. (Hardware specification.)
								IO_IIP_TBL.HISTGRAM.HISTGRAM.word[2],
								ImIipDefine_D_IM_IIP_HISTGRAM_BYTES );
		}

		if( buffer_histgram_d != NULL ) {
			im_iip_sub_get_regword(NULL, buffer_histgram_d,	// Read access only support Word-width. (Hardware specification.)
								IO_IIP_TBL.HISTGRAM.HISTGRAM.word[3],
								ImIipDefine_D_IM_IIP_HISTGRAM_BYTES );
		}
		retval = ImIipDefine_D_IM_IIP_OK;
	}

	Im_IIP_Off_Pclk();
	Im_IIP_Off_Hclk();
	ImIipDefine_IM_IIP_DSB();

	DDIM_User_AhbReg_SpinUnLock();	// JPEG issue work around.

	return retval;
}

/**
*	Get HISTMAX info
*/
INT32 Im_IIP_Get_HISTMAX( UCHAR* const histmax_a, UCHAR* const histmax_b, UCHAR* const histmax_c, UCHAR* const histmax_d )
{
	Im_IIP_On_Pclk();
	ImIipDefine_IM_IIP_DSB();

	if( histmax_a != NULL ) {
		*histmax_a = IO_IIP.HISTMAX.HISTMAX1.bit.HISTMAX_0;
	}

	if( histmax_b != NULL ) {
		*histmax_b = IO_IIP.HISTMAX.HISTMAX1.bit.HISTMAX_1;
	}

	if( histmax_c != NULL ) {
		*histmax_c = IO_IIP.HISTMAX.HISTMAX1.bit.HISTMAX_2;
	}

	if( histmax_d != NULL ) {
		*histmax_d = IO_IIP.HISTMAX.HISTMAX1.bit.HISTMAX_3;
	}

	Im_IIP_Off_Pclk();
	ImIipDefine_IM_IIP_DSB();

	return ImIipDefine_D_IM_IIP_OK;
}

/**
*	Get MINMON info
*/
INT32 Im_IIP_Get_MINMON( TImIipMinmon* const mon )
{
	UINT32 loopcnt;

#ifdef ImIipStruct_CO_PARAM_CHECK
	if( mon == NULL ) {
		Ddim_Assertion(("I:Im_IIP_Get_MINMON INVALID_ARG_ERR\n"));
		return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}
#endif

	Im_IIP_On_Pclk();
	ImIipDefine_IM_IIP_DSB();

	for( loopcnt = 0; loopcnt < 4; loopcnt++ ) {
		mon->min[loopcnt].posX = IO_IIP.MINMON[loopcnt].bit.HPOINTMIN;
		mon->min[loopcnt].posY = IO_IIP.MINMON[loopcnt].bit.VPOINTMIN;
		ImIipDefine_IM_IIP_GET_REG_SIGNED_A( mon->min[loopcnt].value, IO_IIP.MINMON[loopcnt], union io_iip_minmon, MINVAL );
	}

	Im_IIP_Off_Pclk();
	ImIipDefine_IM_IIP_DSB();

	return ImIipDefine_D_IM_IIP_OK;
}

/**
*	Get ADDMON info
*/
INT32 Im_IIP_Get_ADDMON( TImIipAddmon* const mon )
{
	UINT32 loopcnt;

#ifdef ImIipStruct_CO_PARAM_CHECK
	if( mon == NULL ) {
		Ddim_Assertion(("I:Im_IIP_Get_ADDMON INVALID_ARG_ERR\n"));
		return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}
#endif

	Im_IIP_On_Pclk();
	ImIipDefine_IM_IIP_DSB();

	for( loopcnt = 0; loopcnt < 4; loopcnt++ ) {
		mon->add[loopcnt].posX = IO_IIP.ADDMON[loopcnt].bit.HPOINTADD;
		mon->add[loopcnt].posY = IO_IIP.ADDMON[loopcnt].bit.VPOINTADD;
		mon->add[loopcnt].value = IO_IIP.ADDMON[loopcnt].bit.ADDVAL;
		ImIipDefine_IM_IIP_GET_REG_SIGNED_A( mon->add[loopcnt].value, IO_IIP.ADDMON[loopcnt], union io_iip_addmon, ADDVAL );
	}

	Im_IIP_Off_Pclk();
	ImIipDefine_IM_IIP_DSB();

	return ImIipDefine_D_IM_IIP_OK;
}

/**
*	Get Image Cache Access info
*/
INT32 Im_IIP_Get_ImgCache_Access_Info( const EImIipCacheCh cache_ch, TImIipAccessInfo* const info )
{
#ifdef ImIipStruct_CO_PARAM_CHECK
	if( info == NULL ) {
		Ddim_Assertion(("I:Im_IIP_Get_ImgCache_Access_Info INVALID_ARG_ERR\n"));
		return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}
	if( cache_ch >= E_IM_IIP_CACHE_CH_MAX ) {
		Ddim_Assertion(("I:Im_IIP_Get_ImgCache_Access_Info INVALID_ARG_ERR\n"));
		return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}
#endif

	Im_IIP_On_Pclk();
	ImIipDefine_IM_IIP_DSB();

	info->realAccessCounter	= IO_IIP.PDCRAC[cache_ch].word;
	info->realMissCounter		= IO_IIP.PDCRMC[cache_ch].word;

	Im_IIP_Off_Pclk();
	ImIipDefine_IM_IIP_DSB();

	return ImIipDefine_D_IM_IIP_OK;
}

/**
*	Get AXI Status info
*/
INT32 Im_IIP_Get_AXI_Status( TImIipAxiStatus* const sts )
{
#ifdef ImIipStruct_CO_PARAM_CHECK
	if( sts == NULL ) {
		Ddim_Assertion(("I:Im_IIP_Get_AXI_Status INVALID_ARG_ERR\n"));
		return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}
#endif

	Im_IIP_On_Pclk();
	ImIipDefine_IM_IIP_DSB();

	sts->readChannelStatus  = IO_IIP.AXRSTS.word;
	sts->writeChannelStatus = IO_IIP.AXWSTS.word;

	Im_IIP_Off_Pclk();
	ImIipDefine_IM_IIP_DSB();

	return ImIipDefine_D_IM_IIP_OK;
}

/**
*	Get SL UNIT status
*/
INT32 im_iip_main_get_sl_status( UINT32* const sl_status )
{
#ifdef ImIipStruct_CO_PARAM_CHECK
	if( sl_status == NULL ) {
		Ddim_Assertion(("I:im_iip_main_get_sl_status INVALID_ARG_ERR\n"));
		return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}
#endif

	Im_IIP_On_Pclk();
	ImIipDefine_IM_IIP_DSB();

	*sl_status = IO_IIP.IZACTL1.bit.SLALE;

	Im_IIP_Off_Pclk();
	ImIipDefine_IM_IIP_DSB();

	return ImIipDefine_D_IM_IIP_OK;
}

ImIipMain *im_iip_main_new(void)
{
	ImIipMain* self = k_object_new_with_private(IM_TYPE_IIP_MAIN,sizeof(ImIipMainPrivate));
	return self;
}
