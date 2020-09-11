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

INT32 Im_IIP_Stop( const UINT32 stop_type )
{
	INT32			retval = D_IM_IIP_OK;
	DDIM_USER_ER	ercd;
	UINT32			loopcnt;
	UINT32			irq_mask;

	im_iip_On_Iipclk();
	im_iip_On_Iclk();
	Im_IIP_On_Pclk();
	Im_IIP_Dsb();

	irq_mask = im_iip_irq_disable();

	if( IO_IIP.IZACTL1.bit.TRG == D_IM_IIP_RUNNING ) {
		if( stop_type == D_IM_IIP_STOP ) {
			IO_IIP.IZACTL1.bit.TRG = D_IM_IIP_STOP;

#ifdef CO_DEBUG_ON_PC
			IO_IIP.IZACTL1.bit.TRG = D_IM_IIP_STOPPED;
			IO_IIP.IZACTL2.bit.ABORT = D_IM_IIP_STOPPED;
			Im_IIP_Print_Pcdbg(( "Im_IIP_Stop: IZACTL1.bit.TRG = %u\n", IO_IIP.IZACTL1.bit.TRG ));
#endif //CO_DEBUG_ON_PC

			if( IO_IIP.IZACTL1.bit.TRG == D_IM_IIP_STOPPED ) {
				// off clock on from Im_IIP_Start() or Im_IIP_Start_SWTRG().
				im_iip_Off_izarac_caxrac();
				im_iip_Off_Iclk();
				im_iip_Off_Iipclk();
			}
		}
		else if( stop_type == D_IM_IIP_ABORT ) {
			IO_IIP.IZACTL2.bit.ABORT = 0;

#ifdef CO_DEBUG_ON_PC
			IO_IIP.IZACTL1.bit.TRG = D_IM_IIP_STOPPED;
			IO_IIP.IZACTL2.bit.ABORT = D_IM_IIP_STOPPED;
			Im_IIP_Print_Pcdbg(( "Im_IIP_Stop: IZACTL1.bit.ABORT = %u\n", IO_IIP.IZACTL2.bit.ABORT ));
#endif //CO_DEBUG_ON_PC

			for( loopcnt = 0; loopcnt < D_IM_IIP_TRIG_STOP_CHK_RETRY_COUNT; loopcnt++ ) {
				if( IO_IIP.IZACTL1.bit.TRG == D_IM_IIP_STOPPED ) {
					break;
				}
			}
			if( loopcnt >= D_IM_IIP_TRIG_STOP_CHK_RETRY_COUNT ) {
				retval = D_IM_IIP_ABORT_FAILED_ERR;
				Ddim_Print(("I:Im_IIP_Stop abort Failed.\n"));
//				Ddim_Assertion(("I:Im_IIP_Stop abort Failed.\n"));
			}

			// off clock on from Im_IIP_Start() or Im_IIP_Start_SWTRG().
			im_iip_Off_izarac_caxrac();
			im_iip_Off_Iclk();
			im_iip_Off_Iipclk();
		}
		else {
			retval = D_IM_IIP_INVALID_ARG_ERR;
		}
	}

	if( (stop_type == D_IM_IIP_ABORT) && (retval == D_IM_IIP_OK) ) {
		// Clear all interrupt flag.
		// And **ENABLE** Interrupt in service call.
		ercd = DDIM_User_Clr_Flg( FID_IM_IIP, ~D_IM_IIP_FLG_USED_BIT_PATTERN );
		if( ercd != D_DDIM_USER_E_OK ) {
			retval = D_IM_IIP_SYSTEMCALL_ERR;
		}
		else {
		}
	}

	im_iip_irq_enable( irq_mask );

	Im_IIP_Off_Pclk();
	im_iip_Off_Iclk();
	im_iip_Off_Iipclk();
	Im_IIP_Dsb();

	return retval;
}

/**
*	Wait
*/
INT32 Im_IIP_Wait_End( UINT32* const p_wait_factor, const UINT32 wait_factor, const UINT32 wait_mode, const INT32 wait_time )
{
	DDIM_USER_ER		ercd;
	DDIM_USER_FLGPTN	flgptn;

#ifdef CO_PARAM_CHECK
	if( (p_wait_factor == NULL) ||
		 (im_iip_check_wait_time(wait_time) == D_IM_IIP_FALSE) ) {
		Ddim_Assertion(("I:Im_IIP_Wait_End INVALID_ARG_ERR\n"));
		return D_IM_IIP_INVALID_ARG_ERR;
	}
#endif

#ifdef CO_DEBUG_ON_PC
	imIipPseudoInterrupt( wait_factor );
#endif

	ercd = DDIM_User_Twai_Flg( FID_IM_IIP, wait_factor, wait_mode, &flgptn, wait_time );
	switch( ercd ) {
		case D_DDIM_USER_E_OK:
			break;
		case D_DDIM_USER_E_TMOUT:
			return D_IM_IIP_TIMEOUT_ERR;
		default:
			return D_IM_IIP_SYSTEMCALL_ERR;
	}

	ercd = DDIM_User_Clr_Flg( FID_IM_IIP, ~(flgptn & wait_factor) );
	if( ercd != D_DDIM_USER_E_OK ) {
		return D_IM_IIP_SYSTEMCALL_ERR;
	}

	*p_wait_factor = D_IM_IIP_FLG_USED_BIT_PATTERN & (flgptn & wait_factor);

	return D_IM_IIP_OK;
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
	Im_IIP_Dsb();

	hissts = IO_IIP.AHBSTS.bit.HISSTS;
	if( hissts != 0 ) {
		retval = D_IM_IIP_ERR;
	}
	else {
		IO_IIP.MONINIT.bit.INIT = 1;

		im_iip_wait_usec( 1 );

		if( 0 != histgram_a_clr_flag ) {
			im_iip_fill_word( &IO_IIP_TBL.HISTGRAM.HISTGRAM.word[0][0],
							  0,
							  D_IM_IIP_NUM_HISTGRAM,
							  0x0UL );
		}

		if( 0 != histgram_b_clr_flag ) {
			im_iip_fill_word( &IO_IIP_TBL.HISTGRAM.HISTGRAM.word[1][0],
							  0,
							  D_IM_IIP_NUM_HISTGRAM,
							  0x0UL );
		}

		if( 0 != histgram_c_clr_flag ) {
			im_iip_fill_word( &IO_IIP_TBL.HISTGRAM.HISTGRAM.word[2][0],
							  0,
							  D_IM_IIP_NUM_HISTGRAM,
							  0x0UL );
		}

		if( 0 != histgram_d_clr_flag ) {
			im_iip_fill_word( &IO_IIP_TBL.HISTGRAM.HISTGRAM.word[3][0],
							  0,
							  D_IM_IIP_NUM_HISTGRAM,
							  0x0UL );
		}

		retval = D_IM_IIP_OK;
	}

	Im_IIP_Off_Pclk();
	Im_IIP_Off_Hclk();
	Im_IIP_Dsb();

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
	Im_IIP_Dsb();

	hissts = IO_IIP.AHBSTS.bit.HISSTS;
	if( hissts != 0 ) {
		retval = D_IM_IIP_ERR;
	}
	else {
		im_iip_wait_usec( 1 );

		if( buffer_histgram_a != NULL ) {
			im_iip_get_regword( buffer_histgram_a,	// Read access only support Word-width. (Hardware specification.)
								IO_IIP_TBL.HISTGRAM.HISTGRAM.word[0],
								D_IM_IIP_HISTGRAM_BYTES );
		}

		if( buffer_histgram_b != NULL ) {
			im_iip_get_regword( buffer_histgram_b,	// Read access only support Word-width. (Hardware specification.)
								IO_IIP_TBL.HISTGRAM.HISTGRAM.word[1],
								D_IM_IIP_HISTGRAM_BYTES );
		}

		if( buffer_histgram_c != NULL ) {
			im_iip_get_regword( buffer_histgram_c,	// Read access only support Word-width. (Hardware specification.)
								IO_IIP_TBL.HISTGRAM.HISTGRAM.word[2],
								D_IM_IIP_HISTGRAM_BYTES );
		}

		if( buffer_histgram_d != NULL ) {
			im_iip_get_regword( buffer_histgram_d,	// Read access only support Word-width. (Hardware specification.)
								IO_IIP_TBL.HISTGRAM.HISTGRAM.word[3],
								D_IM_IIP_HISTGRAM_BYTES );
		}
		retval = D_IM_IIP_OK;
	}

	Im_IIP_Off_Pclk();
	Im_IIP_Off_Hclk();
	Im_IIP_Dsb();

	DDIM_User_AhbReg_SpinUnLock();	// JPEG issue work around.

	return retval;
}

/**
*	Get HISTMAX info
*/
INT32 Im_IIP_Get_HISTMAX( UCHAR* const histmax_a, UCHAR* const histmax_b, UCHAR* const histmax_c, UCHAR* const histmax_d )
{
	Im_IIP_On_Pclk();
	Im_IIP_Dsb();

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
	Im_IIP_Dsb();

	return D_IM_IIP_OK;
}

/**
*	Get MINMON info
*/
INT32 Im_IIP_Get_MINMON( T_IM_IIP_MINMON* const mon )
{
	UINT32 loopcnt;

#ifdef CO_PARAM_CHECK
	if( mon == NULL ) {
		Ddim_Assertion(("I:Im_IIP_Get_MINMON INVALID_ARG_ERR\n"));
		return D_IM_IIP_INVALID_ARG_ERR;
	}
#endif

	Im_IIP_On_Pclk();
	Im_IIP_Dsb();

	for( loopcnt = 0; loopcnt < 4; loopcnt++ ) {
		mon->min[loopcnt].pos_x = IO_IIP.MINMON[loopcnt].bit.HPOINTMIN;
		mon->min[loopcnt].pos_y = IO_IIP.MINMON[loopcnt].bit.VPOINTMIN;
		im_iip_get_reg_signed_a( mon->min[loopcnt].value, IO_IIP.MINMON[loopcnt], union io_iip_minmon, MINVAL );
	}

	Im_IIP_Off_Pclk();
	Im_IIP_Dsb();

	return D_IM_IIP_OK;
}

/**
*	Get ADDMON info
*/
INT32 Im_IIP_Get_ADDMON( T_IM_IIP_ADDMON* const mon )
{
	UINT32 loopcnt;

#ifdef CO_PARAM_CHECK
	if( mon == NULL ) {
		Ddim_Assertion(("I:Im_IIP_Get_ADDMON INVALID_ARG_ERR\n"));
		return D_IM_IIP_INVALID_ARG_ERR;
	}
#endif

	Im_IIP_On_Pclk();
	Im_IIP_Dsb();

	for( loopcnt = 0; loopcnt < 4; loopcnt++ ) {
		mon->add[loopcnt].pos_x = IO_IIP.ADDMON[loopcnt].bit.HPOINTADD;
		mon->add[loopcnt].pos_y = IO_IIP.ADDMON[loopcnt].bit.VPOINTADD;
		mon->add[loopcnt].value = IO_IIP.ADDMON[loopcnt].bit.ADDVAL;
		im_iip_get_reg_signed_a( mon->add[loopcnt].value, IO_IIP.ADDMON[loopcnt], union io_iip_addmon, ADDVAL );
	}

	Im_IIP_Off_Pclk();
	Im_IIP_Dsb();

	return D_IM_IIP_OK;
}

/**
*	Get Image Cache Access info
*/
INT32 Im_IIP_Get_ImgCache_Access_Info( const E_IM_IIP_CACHE_CH cache_ch, T_IM_IIP_ACCESS_INFO* const info )
{
#ifdef CO_PARAM_CHECK
	if( info == NULL ) {
		Ddim_Assertion(("I:Im_IIP_Get_ImgCache_Access_Info INVALID_ARG_ERR\n"));
		return D_IM_IIP_INVALID_ARG_ERR;
	}
	if( cache_ch >= E_IM_IIP_CACHE_CH_MAX ) {
		Ddim_Assertion(("I:Im_IIP_Get_ImgCache_Access_Info INVALID_ARG_ERR\n"));
		return D_IM_IIP_INVALID_ARG_ERR;
	}
#endif

	Im_IIP_On_Pclk();
	Im_IIP_Dsb();

	info->real_access_counter	= IO_IIP.PDCRAC[cache_ch].word;
	info->real_miss_counter		= IO_IIP.PDCRMC[cache_ch].word;

	Im_IIP_Off_Pclk();
	Im_IIP_Dsb();

	return D_IM_IIP_OK;
}

/**
*	Get AXI Status info
*/
INT32 Im_IIP_Get_AXI_Status( T_IM_IIP_AXI_STATUS* const sts )
{
#ifdef CO_PARAM_CHECK
	if( sts == NULL ) {
		Ddim_Assertion(("I:Im_IIP_Get_AXI_Status INVALID_ARG_ERR\n"));
		return D_IM_IIP_INVALID_ARG_ERR;
	}
#endif

	Im_IIP_On_Pclk();
	Im_IIP_Dsb();

	sts->read_channel_status  = IO_IIP.AXRSTS.word;
	sts->write_channel_status = IO_IIP.AXWSTS.word;

	Im_IIP_Off_Pclk();
	Im_IIP_Dsb();

	return D_IM_IIP_OK;
}

/**
*	Get SL UNIT status
*/
INT32 Im_IIP_Get_SL_Status( UINT32* const sl_status )
{
#ifdef CO_PARAM_CHECK
	if( sl_status == NULL ) {
		Ddim_Assertion(("I:Im_IIP_Get_SL_Status INVALID_ARG_ERR\n"));
		return D_IM_IIP_INVALID_ARG_ERR;
	}
#endif

	Im_IIP_On_Pclk();
	Im_IIP_Dsb();

	*sl_status = IO_IIP.IZACTL1.bit.SLALE;

	Im_IIP_Off_Pclk();
	Im_IIP_Dsb();

	return D_IM_IIP_OK;
}

ImIipMain *im_iip_main_new(void)
{
	ImIipMain* self = k_object_new_with_private(IM_TYPE_IIP_MAIN,sizeof(ImIipMainPrivate));
	return self;
}
