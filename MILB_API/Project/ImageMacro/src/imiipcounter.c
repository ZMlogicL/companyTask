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
#include "imiipdefine.h"
#include "imiipsub.h"
#include "im_iip_param.h"
#include "driver_common.h"
#include <klib.h>
#include "dd_top.h"
#include "dd_arm.h"
#include "ddim_user_custom.h"
#include "jdsiip.h"
#ifdef CO_PT_ENABLE
#include "palladium_test.h"
#endif //CO_PT_ENABLE
#include <string.h>
#include "imiipcounter.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImIipCounter, im_iip_counter);
#define IM_IIP_COUNTER_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImIipCounterPrivate, IM_TYPE_IIP_COUNTER))

struct _ImIipCounterPrivate
{
	int a;
};

#ifdef CO_ACT_IIPCLK
static volatile UINT32 gIM_IIP_Iipclk_Ctrl_Disable = 0;
#endif // CO_ACT_IIPCLK

#ifdef CO_ACT_IIPCLK
static volatile UCHAR S_GIM_IIP_IIPCLK_COUTER  = 0;
#endif

#if 0	// INTIZ2/INTEN2 delete
/** Interrupt parameter table of INTIZ2/INTEN2 */
static volatile T_IM_IIP_INTFLG_TBL S_GIMIIP_INTTBL_2[] = {
	{ D_IM_IIP_REAF0F_BIT, D_IM_IIP_REAF0E_BIT, D_IM_IIP_INT_FACTOR_RINGFULL_AFN0, D_IM_IIP_PARAM_PLDUNIT_AFN0, NULL },
	{ D_IM_IIP_REAF1F_BIT, D_IM_IIP_REAF1E_BIT, D_IM_IIP_INT_FACTOR_RINGFULL_AFN1, D_IM_IIP_PARAM_PLDUNIT_AFN1, NULL },
	{ D_IM_IIP_REAF2F_BIT, D_IM_IIP_REAF2E_BIT, D_IM_IIP_INT_FACTOR_RINGFULL_AFN2, D_IM_IIP_PARAM_PLDUNIT_AFN2, NULL },
	{ D_IM_IIP_REAF3F_BIT, D_IM_IIP_REAF3E_BIT, D_IM_IIP_INT_FACTOR_RINGFULL_AFN3, D_IM_IIP_PARAM_PLDUNIT_AFN3, NULL },
	{ D_IM_IIP_REFR0F_BIT, D_IM_IIP_REFR0E_BIT, D_IM_IIP_INT_FACTOR_RINGFULL_FRECT0, D_IM_IIP_PARAM_PLDUNIT_FRECT0, NULL },
	{ D_IM_IIP_REFR1F_BIT, D_IM_IIP_REFR1E_BIT, D_IM_IIP_INT_FACTOR_RINGFULL_FRECT1, D_IM_IIP_PARAM_PLDUNIT_FRECT1, NULL },
	{ D_IM_IIP_REFLTF_BIT, D_IM_IIP_REFLTE_BIT, D_IM_IIP_INT_FACTOR_RINGFULL_FLT, D_IM_IIP_PARAM_PLDUNIT_FLT, NULL },
};
#endif	// INTIZ2/INTEN2 delete

static volatile UINT32 S_GIM_IIP_ACCEN0_IZARAC_COUNTER = 0;
static volatile T_IM_IIP_SWTRG_MNG S_GIM_IIP_SWTRG_MNG = {
	.unit_bitmask = 0ULL,
	.pixfmttbl_bitmask = 0,
	.res_bitmask = 0,
	.cache_users = {
		0, 0,
	},
};

static volatile T_IM_IIP_INTFLG_TBL S_GIM_IIP_INTTBL_1[] = {
	{ D_IM_IIP_SL0FF_BIT, D_IM_IIP_SL0FEN_BIT, D_IM_IIP_INT_FACTOR_SL0END, D_IM_IIP_PARAM_PLDUNIT_SL0, NULL },
	{ D_IM_IIP_SL1FF_BIT, D_IM_IIP_SL1FEN_BIT, D_IM_IIP_INT_FACTOR_SL1END, D_IM_IIP_PARAM_PLDUNIT_SL1, NULL },
	{ D_IM_IIP_SL2FF_BIT, D_IM_IIP_SL2FEN_BIT, D_IM_IIP_INT_FACTOR_SL2END, D_IM_IIP_PARAM_PLDUNIT_SL2, NULL },
	{ D_IM_IIP_SL3FF_BIT, D_IM_IIP_SL3FEN_BIT, D_IM_IIP_INT_FACTOR_SL3END, D_IM_IIP_PARAM_PLDUNIT_SL3, NULL },
	{ D_IM_IIP_SL4FF_BIT, D_IM_IIP_SL4FEN_BIT, D_IM_IIP_INT_FACTOR_SL4END, D_IM_IIP_PARAM_PLDUNIT_SL4, NULL },
	{ D_IM_IIP_SL5FF_BIT, D_IM_IIP_SL5FEN_BIT, D_IM_IIP_INT_FACTOR_SL5END, D_IM_IIP_PARAM_PLDUNIT_SL5, NULL },
	{ D_IM_IIP_SL6FF_BIT, D_IM_IIP_SL6FEN_BIT, D_IM_IIP_INT_FACTOR_SL6END, D_IM_IIP_PARAM_PLDUNIT_SL6, NULL },
	{ D_IM_IIP_SL7FF_BIT, D_IM_IIP_SL7FEN_BIT, D_IM_IIP_INT_FACTOR_SL7END, D_IM_IIP_PARAM_PLDUNIT_SL7, NULL },
	{ D_IM_IIP_SL8FF_BIT, D_IM_IIP_SL8FEN_BIT, D_IM_IIP_INT_FACTOR_SL8END, D_IM_IIP_PARAM_PLDUNIT_SL8, NULL },
	{ D_IM_IIP_SL0MF_BIT, D_IM_IIP_SL0MEN_BIT, D_IM_IIP_INT_FACTOR_SL0_LINEEND, D_IM_IIP_PARAM_PLDUNIT_SL0, NULL },
	{ D_IM_IIP_SL1MF_BIT, D_IM_IIP_SL1MEN_BIT, D_IM_IIP_INT_FACTOR_SL1_LINEEND, D_IM_IIP_PARAM_PLDUNIT_SL1, NULL },
	{ D_IM_IIP_SL2MF_BIT, D_IM_IIP_SL2MEN_BIT, D_IM_IIP_INT_FACTOR_SL2_LINEEND, D_IM_IIP_PARAM_PLDUNIT_SL2, NULL },
	{ D_IM_IIP_SL3MF_BIT, D_IM_IIP_SL3MEN_BIT, D_IM_IIP_INT_FACTOR_SL3_LINEEND, D_IM_IIP_PARAM_PLDUNIT_SL3, NULL },
	{ D_IM_IIP_SL4MF_BIT, D_IM_IIP_SL4MEN_BIT, D_IM_IIP_INT_FACTOR_SL4_LINEEND, D_IM_IIP_PARAM_PLDUNIT_SL4, NULL },
	{ D_IM_IIP_SL5MF_BIT, D_IM_IIP_SL5MEN_BIT, D_IM_IIP_INT_FACTOR_SL5_LINEEND, D_IM_IIP_PARAM_PLDUNIT_SL5, NULL },
	{ D_IM_IIP_SL6MF_BIT, D_IM_IIP_SL6MEN_BIT, D_IM_IIP_INT_FACTOR_SL6_LINEEND, D_IM_IIP_PARAM_PLDUNIT_SL6, NULL },
	{ D_IM_IIP_SL7MF_BIT, D_IM_IIP_SL7MEN_BIT, D_IM_IIP_INT_FACTOR_SL7_LINEEND, D_IM_IIP_PARAM_PLDUNIT_SL7, NULL },
	{ D_IM_IIP_SL8MF_BIT, D_IM_IIP_SL8MEN_BIT, D_IM_IIP_INT_FACTOR_SL8_LINEEND, D_IM_IIP_PARAM_PLDUNIT_SL8, NULL },
};

static volatile T_IM_IIP_INTFLG_TBL S_GIM_IIP_INTTBL_0[] = {
	{ D_IM_IIP_IZAFLG_BIT, D_IM_IIP_IZAEN_BIT, D_IM_IIP_INT_FACTOR_IZAEND, 0, NULL },
	{ D_IM_IIP_AXEFLG_BIT, D_IM_IIP_AXEEN_BIT, D_IM_IIP_INT_FACTOR_AXIERR, 0, NULL },
};

static void im_iip_counter_constructor(ImIipCounter *self)
{
	ImIipCounterPrivate *priv = IM_IIP_COUNTER_GET_PRIVATE(self);
	priv-> a =  0;
}

static void im_iip_counter_destructor(ImIipCounter *self)
{
	ImIipCounterPrivate *priv = IM_IIP_COUNTER_GET_PRIVATE(self);
	priv-> a =  0;
}

#ifdef CO_DEBUG_ON_PC
static VOID imIipPseudoInterrupt( UINT32 wait_factor )
{
	UINT32			loopcnt;
	ULONG			intiz0 = 0ul;
	ULONG			intiz1 = 0ul;
//	ULONG			intiz2 = 0ul;

	Dd_ARM_Critical_Section_Start( S_GIM_IIP_SPIN_LOCK );

	wait_factor &= ~D_IM_IIP_INT_FACTOR_AXIERR;
	IO_IIP.INTIZ0.word &= ~D_IM_IIP_AXEFLG_BIT;

#if 0	// INTIZ2/INTEN2 delete
	for( loopcnt = 0; loopcnt < (sizeof(S_GIMIIP_INTTBL_2) / sizeof(S_GIMIIP_INTTBL_2[0])); loopcnt++ ) {
		if( (wait_factor & S_GIMIIP_INTTBL_2[loopcnt].int_fact) != 0 ) {
			intiz2 |= S_GIMIIP_INTTBL_2[loopcnt].flg_bitmask;
		}
	}
#endif	// INTIZ2/INTEN2 delete

	for( loopcnt = 0; loopcnt < (sizeof(S_GIM_IIP_INTTBL_1) / sizeof(S_GIM_IIP_INTTBL_1[0])); loopcnt++ ) {
		if( (wait_factor & S_GIM_IIP_INTTBL_1[loopcnt].int_fact) != 0 ) {
			intiz1 |= S_GIM_IIP_INTTBL_1[loopcnt].flg_bitmask;
		}
	}

	for( loopcnt = 0; loopcnt < (sizeof(S_GIM_IIP_INTTBL_0) / sizeof(S_GIM_IIP_INTTBL_0[0])); loopcnt++ ) {
		if( (wait_factor & S_GIM_IIP_INTTBL_0[loopcnt].int_fact) != 0 ) {
			intiz0 |= S_GIM_IIP_INTTBL_0[loopcnt].flg_bitmask;
		}
	}

	IO_IIP.INTIZ0.word |= intiz0;
	IO_IIP.INTIZ1.word |= intiz1;
#if 0	// INTIZ2/INTEN2 delete
	IO_IIP.INTIZ2.word |= intiz2;
#endif	// INTIZ2/INTEN2 delete

	Im_IIP_Int_Handler();

	Dd_ARM_Critical_Section_End( S_GIM_IIP_SPIN_LOCK );
}
#endif

#ifdef CO_PARAM_CHECK
INT32 im_iip_check_wait_time( const INT32 wait_time )
{
	if( wait_time >= D_DDIM_USER_SEM_WAIT_FEVR ) {
		return D_IM_IIP_TRUE;
	}
	else {
		return D_IM_IIP_FALSE;
	}
}
#endif	// CO_PARAM_CHECK

VOID im_iip_On_izarac_caxrac( VOID )
{
	UINT32 irq_mask;

	irq_mask = im_iip_irq_disable();

	if( S_GIM_IIP_ACCEN0_IZARAC_COUNTER < 0xFFFFFFFF ) {
		IO_IIP.ACESEN0.bit.IZARAC = 1;
		IO_IIP.ACESEN0.bit.CA1RAC = 1;
		IO_IIP.ACESEN0.bit.CA2RAC = 1;

		S_GIM_IIP_ACCEN0_IZARAC_COUNTER++;
	}

	im_iip_irq_enable( irq_mask );
}

VOID im_iip_Off_izarac_caxrac( VOID )
{
#ifdef CO_ACT_IIPCLK
	UINT32 irq_mask;

	irq_mask = im_iip_irq_disable();

	if( S_GIM_IIP_ACCEN0_IZARAC_COUNTER > 0 ) {
		S_GIM_IIP_ACCEN0_IZARAC_COUNTER--;

		if( S_GIM_IIP_ACCEN0_IZARAC_COUNTER == 0 ) {
			IO_IIP.ACESEN0.bit.CA2RAC = 0;
			IO_IIP.ACESEN0.bit.CA1RAC = 0;
			IO_IIP.ACESEN0.bit.IZARAC = 0;
		}
	}

	im_iip_irq_enable( irq_mask );
#endif
}

INT32 im_iip_twai_pol_sem( const DDIM_USER_ID semid, const DDIM_USER_TMO tmout )
{
	DDIM_USER_ER ercd;

	if( tmout == D_DDIM_USER_SEM_WAIT_POL ) {
		ercd = DDIM_User_Pol_Sem( semid );
	}
	else {
		ercd = DDIM_User_Twai_Sem( semid, tmout );
	}
	if( D_DDIM_USER_E_TMOUT == ercd ) {
		return D_IM_IIP_TIMEOUT_ERR;
	}
	else
	if( D_DDIM_USER_E_OK != ercd ) {
		return D_IM_IIP_SYSTEMCALL_ERR;
	}
	return D_IM_IIP_OK;
}

VOID im_iip_set_acesen0_reg( volatile T_IM_IIP_SWTRG_MNG* const swtrg_mng )
{
	BOOL is_enabled = FALSE;

	Im_IIP_On_Pclk();

	if( (swtrg_mng->res_bitmask & E_IM_IIP_OPEN_RES_LUT_A) != 0 ) {
		IO_IIP.ACESEN0.bit.LUARAC = 1;
		is_enabled = TRUE;
	}
	else {
		IO_IIP.ACESEN0.bit.LUARAC = 0;
	}
	if( (swtrg_mng->res_bitmask & E_IM_IIP_OPEN_RES_LUT_B) != 0 ) {
		IO_IIP.ACESEN0.bit.LUBRAC = 1;
		is_enabled = TRUE;
	}
	else {
		IO_IIP.ACESEN0.bit.LUBRAC = 0;
	}
	if( (swtrg_mng->res_bitmask & E_IM_IIP_OPEN_RES_LUT_C) != 0 ) {
		IO_IIP.ACESEN0.bit.LUCRAC = 1;
	}
	else {
		IO_IIP.ACESEN0.bit.LUCRAC = 0;
	}
	if( (swtrg_mng->res_bitmask & E_IM_IIP_OPEN_RES_LUT_D) != 0 ) {
		IO_IIP.ACESEN0.bit.LUDRAC = 1;
		is_enabled = TRUE;
	}
	else {
		IO_IIP.ACESEN0.bit.LUDRAC = 0;
	}
	if( (swtrg_mng->res_bitmask & E_IM_IIP_OPEN_RES_LUT_E) != 0 ) {
		IO_IIP.ACESEN0.bit.LUERAC = 1;
		is_enabled = TRUE;
	}
	else {
		IO_IIP.ACESEN0.bit.LUERAC = 0;
	}
	if( (swtrg_mng->res_bitmask & E_IM_IIP_OPEN_RES_LUT_F) != 0 ) {
		IO_IIP.ACESEN0.bit.LUFRAC = 1;
		is_enabled = TRUE;
	}
	else {
		IO_IIP.ACESEN0.bit.LUFRAC = 0;
	}
	if( (swtrg_mng->res_bitmask & E_IM_IIP_OPEN_RES_HIST_0) != 0 ) {
		IO_IIP.ACESEN0.bit.MO0RAC = 1;
		is_enabled = TRUE;
	}
	else {
		IO_IIP.ACESEN0.bit.MO0RAC = 0;
	}
	if( (swtrg_mng->res_bitmask & E_IM_IIP_OPEN_RES_HIST_1) != 0 ) {
		IO_IIP.ACESEN0.bit.MO1RAC = 1;
		is_enabled = TRUE;
	}
	else {
		IO_IIP.ACESEN0.bit.MO1RAC = 0;
	}
	if( (swtrg_mng->res_bitmask & E_IM_IIP_OPEN_RES_HIST_2) != 0 ) {
		IO_IIP.ACESEN0.bit.MO2RAC = 1;
		is_enabled = TRUE;
	}
	else {
		IO_IIP.ACESEN0.bit.MO2RAC = 0;
	}
	if( (swtrg_mng->res_bitmask & E_IM_IIP_OPEN_RES_HIST_3) != 0 ) {
		IO_IIP.ACESEN0.bit.MO3RAC = 1;
		is_enabled = TRUE;
	}
	else {
		IO_IIP.ACESEN0.bit.MO3RAC = 0;
	}

	Im_IIP_Off_Pclk();

	if( is_enabled != FALSE ) {
		im_iip_wait_usec( D_IM_IIP_SRAM_WAIT_USEC );
	}
}

INT32 im_iip_hunt_unit_and_pix( const U_IM_IIP_64BIT_MASK unitid_bitmask, const UINT32 pixid_bitmask, const UINT32 other_bitmask, const UINT32 cache_bitmask )
{
	DDIM_USER_ER		ercd;
	DDIM_USER_FLGPTN	unit_huntedptn;
	DDIM_USER_FLGPTN	pix_huntedptn;
	DDIM_USER_FLGPTN	other_huntedptn;
	static const char	errmsg1[] = "Im_IIP_Open_SWTRG: warning: cache %u open count is full.\n";
	UINT32				irq_mask;
#if defined(CO_IIP_DEBUG_PRINT_FUNC)
	static const char	errmsg2[] = "im_iip_hunt_unit_and_pix() err%u ercd=%d\n";
#endif

	if( unitid_bitmask.flgptn.lower != 0 ) {
		ercd = DDIM_User_Pol_Flg( FID_IM_IIP_UNIT_LO, unitid_bitmask.flgptn.lower, D_DDIM_USER_TWF_ANDW, &unit_huntedptn );
		if( ercd != D_DDIM_USER_E_OK ) {
			Im_IIP_Print_Pcdbg(( errmsg2, 1, ercd ));
			return ercd;
		}
	}

	if( unitid_bitmask.flgptn.upper != 0 ) {
		ercd = DDIM_User_Pol_Flg( FID_IM_IIP_UNIT_HI, unitid_bitmask.flgptn.upper, D_DDIM_USER_TWF_ANDW, &unit_huntedptn );
		if( ercd != D_DDIM_USER_E_OK ) {
			Im_IIP_Print_Pcdbg(( errmsg2, 2, ercd ));
			return ercd;
		}
	}

	if( pixid_bitmask != 0 ) {
		ercd = DDIM_User_Pol_Flg( FID_IM_IIP_PIX, (DDIM_USER_FLGPTN)pixid_bitmask, D_DDIM_USER_TWF_ANDW, &pix_huntedptn );
		if( ercd != D_DDIM_USER_E_OK ) {
			Im_IIP_Print_Pcdbg(( errmsg2, 3, ercd ));
			return ercd;
		}
	}

	if( other_bitmask != 0 ) {
		ercd = DDIM_User_Pol_Flg( FID_IM_IIP_RES, (DDIM_USER_FLGPTN)other_bitmask, D_DDIM_USER_TWF_ANDW, &other_huntedptn );
		if( ercd != D_DDIM_USER_E_OK ) {
			Im_IIP_Print_Pcdbg(( errmsg2, 4, ercd ));
			return ercd;
		}
	}
	// Do resources hunt.
	ercd = DDIM_User_Clr_Flg( FID_IM_IIP_UNIT_LO, ~unitid_bitmask.flgptn.lower );
	if( ercd != D_DDIM_USER_E_OK ) {
		Im_IIP_Print_Pcdbg(( errmsg2, 5, ercd ));
		return ercd;
	}

	ercd = DDIM_User_Clr_Flg( FID_IM_IIP_UNIT_HI, ~unitid_bitmask.flgptn.upper );
	if( ercd != D_DDIM_USER_E_OK ) {
		Im_IIP_Print_Pcdbg(( errmsg2, 6, ercd ));
		return ercd;
	}

	ercd = DDIM_User_Clr_Flg( FID_IM_IIP_PIX, ~(DDIM_USER_FLGPTN)pixid_bitmask );
	if( ercd != D_DDIM_USER_E_OK ) {
		Im_IIP_Print_Pcdbg(( errmsg2, 7, ercd ));
		return ercd;
	}

	if( other_bitmask != 0 ) {
		ercd = DDIM_User_Clr_Flg( FID_IM_IIP_RES, ~(DDIM_USER_FLGPTN)other_bitmask );
		if( ercd != D_DDIM_USER_E_OK ) {
			Im_IIP_Print_Pcdbg(( errmsg2, 8, ercd ));
			return ercd;
		}
	}

	irq_mask = im_iip_irq_disable();

	S_GIM_IIP_SWTRG_MNG.unit_bitmask |= unitid_bitmask.bit64;
	S_GIM_IIP_SWTRG_MNG.pixfmttbl_bitmask |= pixid_bitmask;
	S_GIM_IIP_SWTRG_MNG.res_bitmask |= other_bitmask;
	if( (cache_bitmask & E_IM_IIP_OPEN_RES_CACHE0) != 0 ) {
		if( S_GIM_IIP_SWTRG_MNG.cache_users[0] != 0xFFFFFFFF ) {

			S_GIM_IIP_SWTRG_MNG.cache_users[0]++;
		}
		else {
			Ddim_Print(( errmsg1, 0 ));
		}
	}
	if( (cache_bitmask & E_IM_IIP_OPEN_RES_CACHE1) != 0 ) {
		if( S_GIM_IIP_SWTRG_MNG.cache_users[1] != 0xFFFFFFFF ) {
			S_GIM_IIP_SWTRG_MNG.cache_users[1]++;
		}
		else {
			Ddim_Print(( errmsg1, 1 ));
		}
	}
	if( (cache_bitmask & E_IM_IIP_OPEN_RES_CACHE2) != 0 ) {
		if( S_GIM_IIP_SWTRG_MNG.cache_users[2] != 0xFFFFFFFF ) {
			S_GIM_IIP_SWTRG_MNG.cache_users[2]++;
		}
		else {
			Ddim_Print(( errmsg1, 2 ));
		}
	}
	im_iip_set_acesen0_reg( &S_GIM_IIP_SWTRG_MNG );

	im_iip_irq_enable( irq_mask );

	return D_DDIM_USER_E_OK;
}

VOID im_iip_wait_pftflg( VOID )
{
	if( IO_IIP.IZACTL1.bit.TRG == D_IM_IIP_STOPPED ) {
		return;
	}

	while( IO_IIP.PFTREWTFLG.bit.PFTFLG == 0 ) {
		// do nothing
#ifdef CO_DEBUG_ON_PC
		IO_IIP.PFTREWTFLG.bit.PFTFLG = 1;
#endif //CO_DEBUG_ON_PC
	}

	IO_IIP.PFTREWTFLG.bit.PFTFLG = 1;
}

VOID im_iip_update_pixfmttbl( const UINT32 pixid )
{
	if( IO_IIP.IZACTL1.bit.TRG == D_IM_IIP_STOPPED ) {
		return;
	}

	IO_IIP.PFTREWT.bit.PFTREWT = pixid;

	while( IO_IIP.PFTREWTFLG.bit.PFTFLG == 0 ) {
		// do nothing
#ifdef CO_DEBUG_ON_PC
		IO_IIP.PFTREWTFLG.bit.PFTFLG = 1;
#endif //CO_DEBUG_ON_PC
	}
}

VOID im_iip_set_UNITINFTBL( const T_IM_IIP_UNIT_CFG* const cfg, volatile struct io_iip_uinftbl* const pUNITINFTBL )
{
	if( cfg == NULL ) {
		pUNITINFTBL->UNITINFTBL0.bit.HWEN = D_IM_IIP_HW_CTRL_SWTRG;
	}
	else {
		pUNITINFTBL->UNITINFTBL0.bit.HWEN = cfg->unit_ctrl;
		pUNITINFTBL->UNITINFTBL0.bit.CHAIN = cfg->chain_enable;
		pUNITINFTBL->UNITINFTBL2.bit.PADRS = cfg->unit_param_addr;
	}
}

INT32 Im_IIP_Open_SWTRG( const ULLONG unitid_bitmask64, const UINT32 pixid_bitmask, const UINT32 open_res_bitmask, const INT32 wait_time )
{
	DDIM_USER_ER		ercd;
	DDIM_USER_ER		ercd_crit;
	T_IM_IIP_TIMEOUT	tmout;
	DDIM_USER_FLGPTN	unit_huntedptn;		// for dummy read.
	DDIM_USER_FLGPTN	pix_huntedptn;		// for dummy read.
	DDIM_USER_FLGPTN	other_huntedptn;	// for dummy read.
	U_IM_IIP_64BIT_MASK	unitid_bitmask = {
		.bit64 = unitid_bitmask64,
	};
	UINT32				cache_bitmask;
	UINT32				other_bitmask;

#ifdef CO_PARAM_CHECK
	if( im_iip_check_wait_time(wait_time) == D_IM_IIP_FALSE ) {
		Ddim_Assertion(("I:Im_IIP_Open INVALID_ARG_ERR\n"));
		return D_IM_IIP_INVALID_ARG_ERR;
	}
#endif

	ercd = DDIM_User_Get_Tim( &tmout.start_time );
	if( D_DDIM_USER_E_OK != ercd ) {
		return D_IM_IIP_SYSTEMCALL_ERR;
	}
	tmout.cur_time = tmout.start_time;
	tmout.wait_time = (DDIM_USER_TMO)wait_time;

	unitid_bitmask.bit64 = unitid_bitmask64;
	cache_bitmask = open_res_bitmask & (E_IM_IIP_OPEN_RES_CACHE0 | E_IM_IIP_OPEN_RES_CACHE1 | E_IM_IIP_OPEN_RES_CACHE2);
	other_bitmask = open_res_bitmask & ~(E_IM_IIP_OPEN_RES_CACHE0 | E_IM_IIP_OPEN_RES_CACHE1 | E_IM_IIP_OPEN_RES_CACHE2);

	while( 1 ) {
		// Unit hunt check upper 32bit
		if( unitid_bitmask.flgptn.lower != 0 ) {
			ercd = im_iip_calc_timeout( &tmout );
			if( ercd != D_IM_IIP_OK ) {
				Im_IIP_Print_Pcdbg(( "Im_IIP_Open_SWTRG() err%u ercd=0x%x\n", 1, ercd ));
				return ercd;
			}
			ercd = im_iip_twai_pol_flg( FID_IM_IIP_UNIT_LO, unitid_bitmask.flgptn.lower, D_DDIM_USER_TWF_ANDW, &unit_huntedptn, tmout.last_wait_time );
			if( D_IM_IIP_OK != ercd ) {
				Im_IIP_Print_Pcdbg(( "Im_IIP_Open_SWTRG() err%u ercd=0x%x bitmask=0x%llx\n", 2, ercd, S_GIM_IIP_SWTRG_MNG.unit_bitmask ));
				return ercd;
			}
			ercd = DDIM_User_Set_Flg( FID_IM_IIP_UNIT_LO, unitid_bitmask.flgptn.lower );
			if( D_IM_IIP_OK != ercd ) {
				Im_IIP_Print_Pcdbg(( "Im_IIP_Open_SWTRG() err%u ercd=0x%x\n", 3, ercd ));
				return ercd;
			}
		}

		// Unit hunt check upper 32bit
		if( unitid_bitmask.flgptn.upper != 0 ) {
			ercd = DDIM_User_Get_Tim( &tmout.cur_time );
			if( D_DDIM_USER_E_OK != ercd ) {
				Im_IIP_Print_Pcdbg(( "Im_IIP_Open_SWTRG() err%u ercd=0x%x\n", 4, ercd ));
				return D_IM_IIP_SYSTEMCALL_ERR;
			}
			ercd = im_iip_calc_timeout( &tmout );
			if( ercd != D_IM_IIP_OK ) {
				Im_IIP_Print_Pcdbg(( "Im_IIP_Open_SWTRG() err%u ercd=0x%x\n", 1, ercd ));
				return ercd;
			}
			ercd = im_iip_twai_pol_flg( FID_IM_IIP_UNIT_HI, unitid_bitmask.flgptn.upper, D_DDIM_USER_TWF_ANDW, &unit_huntedptn, tmout.last_wait_time );
			if( D_IM_IIP_OK != ercd ) {
				Im_IIP_Print_Pcdbg(( "Im_IIP_Open_SWTRG() err%u ercd=0x%x bitmask=0x%llx\n", 2, ercd, S_GIM_IIP_SWTRG_MNG.unit_bitmask ));
				return ercd;
			}
			ercd = DDIM_User_Set_Flg( FID_IM_IIP_UNIT_HI, unitid_bitmask.flgptn.upper );
			if( D_IM_IIP_OK != ercd ) {
				Im_IIP_Print_Pcdbg(( "Im_IIP_Open_SWTRG() err%u ercd=0x%x\n", 3, ercd ));
				return ercd;
			}
		}

		// Pixid hunt check
		if( pixid_bitmask != 0 ) {
			ercd = DDIM_User_Get_Tim( &tmout.cur_time );
			if( D_DDIM_USER_E_OK != ercd ) {
				Im_IIP_Print_Pcdbg(( "Im_IIP_Open_SWTRG() err%u ercd=0x%x\n", 4, ercd ));
				return D_IM_IIP_SYSTEMCALL_ERR;
			}
			ercd = im_iip_calc_timeout( &tmout );
			if( ercd != D_IM_IIP_OK ) {
				Im_IIP_Print_Pcdbg(( "Im_IIP_Open_SWTRG() err%u ercd=0x%x\n", 5, ercd ));
				return ercd;
			}
			ercd = im_iip_twai_pol_flg( FID_IM_IIP_PIX, (DDIM_USER_FLGPTN)pixid_bitmask, D_DDIM_USER_TWF_ANDW, &pix_huntedptn, tmout.last_wait_time );
			if( D_IM_IIP_OK != ercd ) {
				Im_IIP_Print_Pcdbg(( "Im_IIP_Open_SWTRG() err%u ercd=0x%x bitmask=0x%lx\n", 6, ercd, S_GIM_IIP_SWTRG_MNG.pixfmttbl_bitmask ));
				return ercd;
			}
			ercd = DDIM_User_Set_Flg( FID_IM_IIP_PIX, (DDIM_USER_FLGPTN)pixid_bitmask );
			if( D_IM_IIP_OK != ercd ) {
				Im_IIP_Print_Pcdbg(( "Im_IIP_Open_SWTRG() err%u ercd=0x%x\n", 7, ercd ));
				return ercd;
			}
		}

		// Other hunt check
		if( other_bitmask != 0 ) {
			ercd = DDIM_User_Get_Tim( &tmout.cur_time );
			if( D_DDIM_USER_E_OK != ercd ) {
				Im_IIP_Print_Pcdbg(( "Im_IIP_Open_SWTRG() err%u ercd=0x%x\n", 8, ercd ));
				return D_IM_IIP_SYSTEMCALL_ERR;
			}
			ercd = im_iip_calc_timeout( &tmout );
			if( ercd != D_IM_IIP_OK ) {
				Im_IIP_Print_Pcdbg(( "Im_IIP_Open_SWTRG() err%u ercd=0x%x\n", 9, ercd ));
				return ercd;
			}
			ercd = im_iip_twai_pol_flg( FID_IM_IIP_RES, (DDIM_USER_FLGPTN)other_bitmask, D_DDIM_USER_TWF_ANDW, &other_huntedptn, tmout.last_wait_time );
			if( D_IM_IIP_OK != ercd ) {
				Im_IIP_Print_Pcdbg(( "Im_IIP_Open_SWTRG() err%u ercd=0x%x bitmask=0x%lx\n", 11, ercd, S_GIM_IIP_SWTRG_MNG.res_bitmask ));
				return ercd;
			}
			ercd = DDIM_User_Set_Flg( FID_IM_IIP_RES, (DDIM_USER_FLGPTN)other_bitmask );
			if( D_IM_IIP_OK != ercd ) {
				Im_IIP_Print_Pcdbg(( "Im_IIP_Open_SWTRG() err%u ercd=0x%x\n", 10, ercd ));
				return ercd;
			}
		}
		// Entry critical section
		ercd = DDIM_User_Get_Tim( &tmout.cur_time );
		if( D_DDIM_USER_E_OK != ercd ) {
			Im_IIP_Print_Pcdbg(( "Im_IIP_Open_SWTRG() err%u ercd=0x%x\n", 12, ercd ));
			return D_IM_IIP_SYSTEMCALL_ERR;
		}
		ercd = im_iip_calc_timeout( &tmout );
		if( ercd != D_IM_IIP_OK ) {
			Im_IIP_Print_Pcdbg(( "Im_IIP_Open_SWTRG() err%u ercd=0x%x\n", 13, ercd ));
			return ercd;
		}
		ercd = im_iip_twai_pol_sem( SID_IM_IIP_SW, tmout.last_wait_time );
		if( ercd != D_IM_IIP_OK ) {
			Im_IIP_Print_Pcdbg(( "Im_IIP_Open_SWTRG() err%u ercd=0x%x\n", 14, ercd ));
			return ercd;
		}

		ercd_crit = im_iip_hunt_unit_and_pix( unitid_bitmask, pixid_bitmask, other_bitmask, cache_bitmask );

		ercd = DDIM_User_Sig_Sem( SID_IM_IIP_SW );
		if( D_DDIM_USER_E_OK != ercd ) {
			Im_IIP_Print_Pcdbg(( "Im_IIP_Open_SWTRG() err%u ercd=0x%x\n", 15, ercd ));
			return D_IM_IIP_SYSTEMCALL_ERR;
		}

		if( ercd_crit == D_DDIM_USER_E_OK ) {
			// Resource hunt successfull. break loop.
			break;
		}
		else
		if( ercd_crit == D_DDIM_USER_E_TMOUT ) {
			// Resource already hunted other one.
			// Goto retry.
		}
		else {
			Im_IIP_Print_Pcdbg(( "Im_IIP_Open_SWTRG() err%u ercd=0x%x\n", 16, ercd ));
			return D_IM_IIP_SYSTEMCALL_ERR;
		}

		if( wait_time == D_DDIM_USER_SEM_WAIT_POL ) {
			Im_IIP_Print_Pcdbg(( "Im_IIP_Open_SWTRG() err%u ercd=0x%x\n", 17, ercd ));
			return D_IM_IIP_TIMEOUT_ERR;
		}

		ercd = DDIM_User_Get_Tim( &tmout.cur_time );
		if( D_DDIM_USER_E_OK != ercd ) {
			Im_IIP_Print_Pcdbg(( "Im_IIP_Open_SWTRG() err%u ercd=0x%x\n", 18, ercd ));
			return D_IM_IIP_SYSTEMCALL_ERR;
		}
	}

	return D_IM_IIP_OK;
}

INT32 Im_IIP_Close_SWTRG( const ULLONG unitid_bitmask64, const UINT32 pixid_bitmask, const UINT32 open_res_bitmask )
{
	DDIM_USER_ER		ercd;
	INT32				ercd_im = D_IM_IIP_OK;
	U_IM_IIP_64BIT_MASK	unitid_bitmask = {
		.bit64 = unitid_bitmask64,
	};
	UINT32				cache_bitmask;
	UINT32				other_bitmask;
	UINT32				irq_mask;
	static const char	errmsg1[] = "Im_IIP_Close_SWTRG: warning: cache %u not open.\n";
	unitid_bitmask.bit64 = unitid_bitmask64;
	cache_bitmask = open_res_bitmask & (E_IM_IIP_OPEN_RES_CACHE0 | E_IM_IIP_OPEN_RES_CACHE1 | E_IM_IIP_OPEN_RES_CACHE2);
	other_bitmask = open_res_bitmask & ~(E_IM_IIP_OPEN_RES_CACHE0 | E_IM_IIP_OPEN_RES_CACHE1 | E_IM_IIP_OPEN_RES_CACHE2);

	irq_mask = im_iip_irq_disable();

	S_GIM_IIP_SWTRG_MNG.unit_bitmask &= ~unitid_bitmask.bit64;
	S_GIM_IIP_SWTRG_MNG.pixfmttbl_bitmask &= ~pixid_bitmask;
	S_GIM_IIP_SWTRG_MNG.res_bitmask &= ~other_bitmask;
	if( (cache_bitmask & E_IM_IIP_OPEN_RES_CACHE0) != 0 ) {
		if( S_GIM_IIP_SWTRG_MNG.cache_users[0]!= 0  ) {
			S_GIM_IIP_SWTRG_MNG.cache_users[0]--;
		}
		else {
			Ddim_Print(( errmsg1, 0 ));
		}
	}
	if( (cache_bitmask & E_IM_IIP_OPEN_RES_CACHE1) != 0 ) {
		if( S_GIM_IIP_SWTRG_MNG.cache_users[1] != 0 ) {
			S_GIM_IIP_SWTRG_MNG.cache_users[1]--;
		}
		else {
			Ddim_Print(( errmsg1, 1 ));
		}
	}
	if( (cache_bitmask & E_IM_IIP_OPEN_RES_CACHE2) != 0 ) {
		if( S_GIM_IIP_SWTRG_MNG.cache_users[2] != 0 ) {
			S_GIM_IIP_SWTRG_MNG.cache_users[2]--;
		}
		else {
			Ddim_Print(( errmsg1, 2 ));
		}
	}
	im_iip_set_acesen0_reg( &S_GIM_IIP_SWTRG_MNG );

	if( S_GIM_IIP_SWTRG_MNG.unit_bitmask == 0 ) {
		ercd_im = Im_IIP_Stop( D_IM_IIP_ABORT );
	}
	im_iip_irq_enable( irq_mask );
	ercd = im_iip_unset_interrupt( unitid_bitmask, D_IM_IIP_ENABLE_OFF );
	if( ercd != D_IM_IIP_OK ) {
		return ercd;
	}

	ercd = DDIM_User_Set_Flg( FID_IM_IIP_UNIT_LO, unitid_bitmask.flgptn.lower );
	if( D_DDIM_USER_E_OK != ercd ) {
		if( D_DDIM_USER_E_OK != ercd_im ) {
			return D_IM_IIP_SYSTEMCALL_ERR;
		}
	}

	ercd = DDIM_User_Set_Flg( FID_IM_IIP_UNIT_HI, unitid_bitmask.flgptn.upper );
	if( D_DDIM_USER_E_OK != ercd ) {
		if( D_DDIM_USER_E_OK != ercd_im ) {
			return D_IM_IIP_SYSTEMCALL_ERR;
		}
	}

	ercd = DDIM_User_Set_Flg( FID_IM_IIP_PIX, (DDIM_USER_FLGPTN)pixid_bitmask );
	if( D_DDIM_USER_E_OK != ercd ) {
		if( D_DDIM_USER_E_OK != ercd_im ) {
			return D_IM_IIP_SYSTEMCALL_ERR;
		}
	}
	ercd = DDIM_User_Set_Flg( FID_IM_IIP_RES, (DDIM_USER_FLGPTN)other_bitmask );
	if( D_DDIM_USER_E_OK != ercd ) {
		if( D_DDIM_USER_E_OK != ercd_im ) {
			return D_IM_IIP_SYSTEMCALL_ERR;
		}
	}

	return ercd_im;
}

INT32 Im_IIP_Int_Handler( VOID )
{
	ImIipDefine *imIipDefine        = im_iip_define_get();
	T_IM_IIP_CALLBACK gimIipCallback     = im_iip_get_gim_iip(imIipDefine);

	ULONG			intiz0;
	ULONG			intiz1;
//	ULONG			intiz2;
	UINT32			int_factor = 0;
	DDIM_USER_ER	ercd;
	UINT32			loopcnt;

#ifdef CO_DEBUG_PRINT_IM_IIP
		Ddim_Print(( "Im_IIP_Int_Handler begin\n" ));
#endif

	Im_IIP_On_Pclk();
	Im_IIP_Dsb();
	// Get interrupt
	intiz0 = IO_IIP.INTIZ0.word & IO_IIP.INTEN0.word;
	intiz1 = IO_IIP.INTIZ1.word & IO_IIP.INTEN1.word;
//	intiz2 = IO_IIP.INTIZ2.word & IO_IIP.INTEN2.word;
	IO_IIP.INTIZ0.word = intiz0;
	IO_IIP.INTIZ1.word = intiz1;
//	IO_IIP.INTIZ2.word = intiz2;
#ifdef CO_DEBUG_ON_PC
	IO_IIP.INTIZ0.word &= ~intiz0;
	IO_IIP.INTIZ1.word &= ~intiz1;
//	IO_IIP.INTIZ2.word &= ~intiz2;
#endif // CO_DEBUG_ON_PC

	// Process for each interrupt

#if 0	// INTIZ2/INTEN2 delete
	for( loopcnt = 0; loopcnt < (sizeof(S_GIMIIP_INTTBL_2) / sizeof(S_GIMIIP_INTTBL_2[0])); loopcnt++ ) {
		if( (intiz2 & S_GIMIIP_INTTBL_2[loopcnt].flg_bitmask) != 0 ) {
			int_factor |= S_GIMIIP_INTTBL_2[loopcnt].int_fact;
			if( S_GIMIIP_INTTBL_2[loopcnt].callback_func != NULL ) {
				S_GIMIIP_INTTBL_2[loopcnt].callback_func( S_GIMIIP_INTTBL_2[loopcnt].int_fact );
			}
		}
	}
#endif	// INTIZ2/INTEN2 delete

	for( loopcnt = 0; loopcnt < (sizeof(S_GIM_IIP_INTTBL_1) / sizeof(S_GIM_IIP_INTTBL_1[0])); loopcnt++ ) {
		if( (intiz1 & S_GIM_IIP_INTTBL_1[loopcnt].flg_bitmask) != 0 ) {
			int_factor |= S_GIM_IIP_INTTBL_1[loopcnt].int_fact;
			if( S_GIM_IIP_INTTBL_1[loopcnt].callback_func != NULL ) {
				S_GIM_IIP_INTTBL_1[loopcnt].callback_func( S_GIM_IIP_INTTBL_1[loopcnt].int_fact );
			}
		}
	}
	for( loopcnt = 0; loopcnt < (sizeof(S_GIM_IIP_INTTBL_0) / sizeof(S_GIM_IIP_INTTBL_0[0])); loopcnt++ ) {
		if( (intiz0 & S_GIM_IIP_INTTBL_0[loopcnt].flg_bitmask) != 0 ) {
			int_factor |= S_GIM_IIP_INTTBL_0[loopcnt].int_fact;
			if( S_GIM_IIP_INTTBL_0[loopcnt].callback_func != NULL ) {
				S_GIM_IIP_INTTBL_0[loopcnt].callback_func( S_GIM_IIP_INTTBL_0[loopcnt].int_fact );
			}
		}
	}
	Im_IIP_Dsb();

#ifdef CO_DEBUG_PRINT_IM_IIP
	Ddim_Print(( "Im_IIP_Int_Handler IZ0=0x%lx IZ1=0x%lx IZ2=0x%lx EN0=0x%lx EN1=0x%lx EN2=0x%lx factor=0x%x\n", intiz0, intiz1, intiz2, inten0, inten1, inten2, int_factor ));
#endif

	ercd = DDIM_User_Set_Flg( FID_IM_IIP, int_factor );
	if( ercd != D_DDIM_USER_E_OK ) {
		Im_IIP_Off_Pclk();
		Im_IIP_Dsb();
		return D_IM_IIP_SYSTEMCALL_ERR;
	}

	Im_IIP_Off_Pclk();
	Im_IIP_Dsb();

	if( gimIipCallback != NULL ) {
#ifdef CO_DEBUG_PRINT_IM_IIP
		Ddim_Print(( "Im_IIP_Int_Handler begin callback\n" ));
#endif
		gimIipCallback( int_factor );
#ifdef CO_DEBUG_PRINT_IM_IIP
		Ddim_Print(( "Im_IIP_Int_Handler end callback\n" ));
#endif
	}

#ifdef CO_DEBUG_PRINT_IM_IIP
		Ddim_Print(( "Im_IIP_Int_Handler end\n" ));
#endif

	return D_IM_IIP_OK;
}

INT32 Im_IIP_Set_IntHandler( const ULONG interrupt_bitmask, const T_IM_IIP_CALLBACK int_handler )
{
	UINT32 loopcnt;

	for( loopcnt = 0; loopcnt < (sizeof(S_GIM_IIP_INTTBL_0) / sizeof(S_GIM_IIP_INTTBL_0[0])); loopcnt++ ) {
		if( (S_GIM_IIP_INTTBL_0[loopcnt].int_fact & interrupt_bitmask) != 0 ) {
			S_GIM_IIP_INTTBL_0[loopcnt].callback_func = int_handler;
		}
	}
	for( loopcnt = 0; loopcnt < (sizeof(S_GIM_IIP_INTTBL_1) / sizeof(S_GIM_IIP_INTTBL_1[0])); loopcnt++ ) {
		if( (S_GIM_IIP_INTTBL_1[loopcnt].int_fact & interrupt_bitmask) != 0 ) {
			S_GIM_IIP_INTTBL_1[loopcnt].callback_func = int_handler;
		}
	}

#if 0	// INTIZ2/INTEN2 delete
	for( loopcnt = 0; loopcnt < (sizeof(S_GIMIIP_INTTBL_2) / sizeof(S_GIMIIP_INTTBL_2[0])); loopcnt++ ) {
		if( (S_GIMIIP_INTTBL_2[loopcnt].int_fact & interrupt_bitmask) != 0 ) {
			S_GIMIIP_INTTBL_2[loopcnt].callback_func = int_handler;
		}
	}
#endif	// INTIZ2/INTEN2 delete

	return D_IM_IIP_OK;
}

VOID im_iip_On_Iipclk( VOID )
{
#ifdef CO_ACT_IIPCLK
	if( S_GIM_IIP_IIPCLK_COUTER < 255 ) {
		Dd_Top_Start_Clock( (UCHAR*)&S_GIM_IIP_IIPCLK_COUTER, &Dd_Top_Get_CLKSTOP3(), ~D_DD_TOP_IIPCK_BIT );
#ifdef CO_DEBUG_ON_PC
		Dd_Top_Get_CLKSTOP3() &= ~D_DD_TOP_IIPCK_BIT;
#endif
	}
#endif
}

VOID im_iip_Off_Iipclk( VOID )
{
#ifdef CO_ACT_IIPCLK
	UINT32 irq_mask;

	irq_mask = im_iip_irq_disable();

	if( S_GIM_IIP_IIPCLK_COUTER == 1 ) {
		if( gIM_IIP_Iipclk_Ctrl_Disable == 0 ) {
			Dd_Top_Stop_Clock( (UCHAR*)&S_GIM_IIP_IIPCLK_COUTER, &Dd_Top_Get_CLKSTOP3(), D_DD_TOP_IIPCK_BIT );
#ifdef CO_DEBUG_ON_PC
			Dd_Top_Get_CLKSTOP3() |= D_DD_TOP_IIPCK_BIT;
#endif
		}
	}
	else {
		Dd_Top_Stop_Clock( (UCHAR*)&S_GIM_IIP_IIPCLK_COUTER, &Dd_Top_Get_CLKSTOP3(), D_DD_TOP_IIPCK_BIT );
#ifdef CO_DEBUG_ON_PC
		Dd_Top_Get_CLKSTOP3() |= D_DD_TOP_IIPCK_BIT;
#endif
	}

	im_iip_irq_enable( irq_mask );
#endif
}

#ifdef CO_IIP_DEBUG_PRINT_FUNC
VOID Im_IIP_Print_DebugStatus( VOID )
{
	ImIipDefine *imIipDefine        = im_iip_define_get();
	T_IM_IIP_CALLBACK gimIipCallback     = im_iip_get_gim_iip(imIipDefine);

	UINT32 loopcnt;

	Ddim_Print(( "S_GIM_IIP_SWTRG_MNG.unit_bitmask = 0x%llx\n", S_GIM_IIP_SWTRG_MNG.unit_bitmask ));
	Ddim_Print(( "S_GIM_IIP_SWTRG_MNG.pixfmttbl_bitmask = 0x%lx\n", S_GIM_IIP_SWTRG_MNG.pixfmttbl_bitmask ));
	Ddim_Print(( "S_GIM_IIP_SWTRG_MNG.res_bitmask = 0x%lx\n", S_GIM_IIP_SWTRG_MNG.res_bitmask ));
	for( loopcnt = 0; loopcnt < D_IM_IIP_CACHE_MAXNUM; loopcnt++ ) {
		Ddim_Print(( "S_GIM_IIP_SWTRG_MNG.cache_users[%u] = 0x%x\n", loopcnt, S_GIM_IIP_SWTRG_MNG.cache_users[loopcnt] ));
	}
	Ddim_Print(( "gimIipCallback = 0x%lx\n", (ULONG)gimIipCallback ));
	for( loopcnt = 0; loopcnt < (sizeof(S_GIM_IIP_INTTBL_0) / sizeof(S_GIM_IIP_INTTBL_0[0])); loopcnt++ ) {
		Ddim_Print(( "S_GIM_IIP_INTTBL_0[%u].callback_func = 0x%lx\n", loopcnt, (ULONG)S_GIM_IIP_INTTBL_0[loopcnt].callback_func ));
	}
	for( loopcnt = 0; loopcnt < (sizeof(S_GIM_IIP_INTTBL_1) / sizeof(S_GIM_IIP_INTTBL_1[0])); loopcnt++ ) {
		Ddim_Print(( "S_GIM_IIP_INTTBL_1[%u].callback_func = 0x%lx\n", loopcnt, (ULONG)S_GIM_IIP_INTTBL_1[loopcnt].callback_func ));
	}
#if 0 // INTIZ2/INTEN2 delete
	for( loopcnt = 0; loopcnt < (sizeof(S_GIMIIP_INTTBL_2) / sizeof(S_GIMIIP_INTTBL_2[0])); loopcnt++ ) {
		Ddim_Print(( "S_GIMIIP_INTTBL_2[%u].callback_func = 0x%lx\n", loopcnt, (ULONG)S_GIMIIP_INTTBL_2[loopcnt].callback_func ));
	}
#endif // INTIZ2/INTEN2 delete
}

VOID Im_IIP_Print_ClockStatus( VOID )
{
	Ddim_Print(( "CLKSTOP: AP=%u\n", Dd_Top_Get_CLKSTOP_IIPAP() ));
	Ddim_Print(( "CLKSTOP: AH=%u\n", Dd_Top_Get_CLKSTOP_IIPAH() ));
	Ddim_Print(( "CLKSTOP: AX=%u\n", Dd_Top_Get_CLKSTOP_IIPAX() ));
	Ddim_Print(( "CLKSTOP: CK=%u\n", Dd_Top_Get_CLKSTOP_IIPCK() ));
#ifdef CO_ACT_IIP_PCLK
	Ddim_Print(( "CLKCNT: AP=%u\n", S_GIM_IIP_PCLK_COUNTER ));
#endif
#ifdef CO_ACT_IIP_HCLK
	Ddim_Print(( "CLKCNT: AH=%u\n", S_GIM_IIP_HCLK_COUNTER ));
#endif
#ifdef CO_ACT_IIP_ICLK
	Ddim_Print(( "CLKCNT: AX=%u\n", S_GIM_IIP_ICLK_COUNTER ));
#endif
#ifdef CO_ACT_IIPCLK
	Ddim_Print(( "CLKCNT: CK=%u\n", S_GIM_IIP_IIPCLK_COUTER ));
#endif
}

#else

INT32 im_iip_unset_interrupt( const U_IM_IIP_64BIT_MASK unitid_bitmask, const UCHAR cause )
{
	INT32 ercd;
	UINT32 loopcnt;
	ULONG int_fact = 0;

	for( loopcnt = 0; loopcnt < (sizeof(S_GIM_IIP_INTTBL_0) / sizeof(S_GIM_IIP_INTTBL_0[0])); loopcnt++ ) {
		if( (S_GIM_IIP_INTTBL_0[loopcnt].unitid_bitmask & unitid_bitmask.bit64) != 0 ) {
			int_fact |= S_GIM_IIP_INTTBL_0[loopcnt].int_fact;
		}
	}

	for( loopcnt = 0; loopcnt < (sizeof(S_GIM_IIP_INTTBL_1) / sizeof(S_GIM_IIP_INTTBL_1[0])); loopcnt++ ) {
		if( (S_GIM_IIP_INTTBL_1[loopcnt].unitid_bitmask & unitid_bitmask.bit64) != 0 ) {
			int_fact |= S_GIM_IIP_INTTBL_1[loopcnt].int_fact;
		}
	}

#if 0	// INTIZ2/INTEN2 delete
	for( loopcnt = 0; loopcnt < (sizeof(S_GIMIIP_INTTBL_2) / sizeof(S_GIMIIP_INTTBL_2[0])); loopcnt++ ) {
		if( (S_GIMIIP_INTTBL_2[loopcnt].unitid_bitmask & unitid_bitmask.bit64) != 0 ) {
			int_fact |= S_GIMIIP_INTTBL_2[loopcnt].int_fact;
		}
	}
#endif	// INTIZ2/INTEN2 delete

	ercd = Im_IIP_Set_Interrupt( int_fact, cause );
	if( ercd != D_IM_IIP_OK ) {
		return ercd;
	}

	if( cause == D_IM_IIP_ENABLE_OFF ) {
		ercd = Im_IIP_Set_IntHandler( int_fact, NULL );
		if( ercd != D_IM_IIP_OK ) {
			return ercd;
		}
		// Clear Interrupt factor
		ercd = DDIM_User_Clr_Flg( FID_IM_IIP, ~int_fact );
		if( ercd != D_DDIM_USER_E_OK ) {
			return D_IM_IIP_SYSTEMCALL_ERR;
		}
	}
	return ercd;
}

ImIipCounter *im_iip_counter_new(void)
{
	ImIipCounter* self = k_object_new_with_private(IM_TYPE_IIP_COUNTER,sizeof(ImIipCounterPrivate));
	return self;
}
#endif
