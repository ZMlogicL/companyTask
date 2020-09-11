/*
*@Copyright (C) 2030-2020 上海网用软件有限公司

*@date                :2020-08-04
*@author              :刘应春
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*3、
*2、
*@version
*3.0.0 2020年06月开始开发
*/

#include "imiipdefine.h"

#include "imiipstatic.h"
#include "jdsiip.h"
#include "dd_arm.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImIipStatic, im_iip_static);
#define IM_IIP_STATIC_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImIipStaticPrivate, IM_TYPE_IIP_STATIC))

struct _ImIipStaticPrivate
{
	int a;
};

static ULONG  S_GIM_IIP_SPIN_LOCK __attribute__((section(".LOCK_SECTION"), aligned(64)));
static volatile UINT32 S_GIM_IIP_CRETSEQ_RECURSIVE_COUNT[ D_IM_IIP_NUM_CPU_CORES ] = { 0, 0, 0, 0 };

static const T_IM_IIP_DUMP_UNIT_NAME S_GIM_IIP_DUMP_UNIT_NAME[] = {
	{ .unit_id = E_IM_IIP_UNIT_ID_LD0,		.unit_name = "ld0", },
	{ .unit_id = E_IM_IIP_UNIT_ID_LD1,		.unit_name = "ld1", },
	{ .unit_id = E_IM_IIP_UNIT_ID_LD2,		.unit_name = "ld2", },
	{ .unit_id = E_IM_IIP_UNIT_ID_LD3,		.unit_name = "ld3", },
	{ .unit_id = E_IM_IIP_UNIT_ID_FLT,		.unit_name = "flt", },
	{ .unit_id = E_IM_IIP_UNIT_ID_AFN0,		.unit_name = "afn0", },
	{ .unit_id = E_IM_IIP_UNIT_ID_AFN1,		.unit_name = "afn1", },
	{ .unit_id = E_IM_IIP_UNIT_ID_AFN2,		.unit_name = "afn2", },
	{ .unit_id = E_IM_IIP_UNIT_ID_FRECT0,	.unit_name = "frect0", },
	{ .unit_id = E_IM_IIP_UNIT_ID_MON,		.unit_name = "mon", },
	{ .unit_id = E_IM_IIP_UNIT_ID_SL0,		.unit_name = "sl0", },
	{ .unit_id = E_IM_IIP_UNIT_ID_SL1,		.unit_name = "sl1", },
	{ .unit_id = E_IM_IIP_UNIT_ID_SL2,		.unit_name = "sl2", },
	{ .unit_id = E_IM_IIP_UNIT_ID_SL3,		.unit_name = "sl3", },
	{ .unit_id = E_IM_IIP_UNIT_ID_SL4,		.unit_name = "sl4", },
	{ .unit_id = E_IM_IIP_UNIT_ID_SL5,		.unit_name = "sl5", },
	{ .unit_id = E_IM_IIP_UNIT_ID_CSC0,		.unit_name = "csc0", },
	{ .unit_id = E_IM_IIP_UNIT_ID_CSC1,		.unit_name = "csc1", },
	{ .unit_id = E_IM_IIP_UNIT_ID_LUT,		.unit_name = "lut", },
	{ .unit_id = E_IM_IIP_UNIT_ID_GPC,		.unit_name = "gpc", },
	{ .unit_id = E_IM_IIP_UNIT_ID_BLEND0,	.unit_name = "blend0", },
	{ .unit_id = E_IM_IIP_UNIT_ID_BLEND1,	.unit_name = "blend1", },
	{ .unit_id = E_IM_IIP_UNIT_ID_FRECT1,	.unit_name = "frect1", },
	{ .unit_id = E_IM_IIP_UNIT_ID_CFL0,		.unit_name = "cfl0", },
	{ .unit_id = E_IM_IIP_UNIT_ID_CSC2,		.unit_name = "csc2", },
	{ .unit_id = E_IM_IIP_UNIT_ID_CSC3,		.unit_name = "csc3", },
	{ .unit_id = E_IM_IIP_UNIT_ID_SL6,		.unit_name = "sl6", },
	{ .unit_id = E_IM_IIP_UNIT_ID_SL7,		.unit_name = "sl7", },
	{ .unit_id = E_IM_IIP_UNIT_ID_SL8,		.unit_name = "sl8", },
	{ .unit_id = E_IM_IIP_UNIT_ID_LD4,		.unit_name = "ld4", },
	{ .unit_id = E_IM_IIP_UNIT_ID_LD5,		.unit_name = "ld5", },
	{ .unit_id = E_IM_IIP_UNIT_ID_LD6,		.unit_name = "ld6", },
	{ .unit_id = E_IM_IIP_UNIT_ID_LD7,		.unit_name = "ld7", },
	{ .unit_id = E_IM_IIP_UNIT_ID_AFN3,		.unit_name = "afn3", },
	{ .unit_id = E_IM_IIP_UNIT_ID_MFT,		.unit_name = "mft", },
};

static void im_iip_static_constructor(ImIipStatic *self)
{
	ImIipStaticPrivate *priv = IM_IIP_STATIC_GET_PRIVATE(self);
	priv-> a =  0;
}

static void im_iip_static_destructor(ImIipStatic *self)
{
	ImIipStaticPrivate *priv = IM_IIP_STATIC_GET_PRIVATE(self);
	priv-> a =  0;
}

INT32 Im_IIP_Ctrl_SWTRG_Unit( const E_IM_IIP_UNIT_ID unit_id, const T_IM_IIP_UNIT_CFG* const p_unitcfg )
{
	volatile struct io_iip_uinftbl* p_uinftbl;

#ifdef CO_PARAM_CHECK
	if( p_unitcfg == NULL ) {
		Ddim_Assertion(("I:Im_IIP_Ctrl_SWTRG_Unit INVALID_ARG_ERR\n"));
		return D_IM_IIP_INVALID_ARG_ERR;
	}
#endif	// CO_PARAM_CHECK

	p_uinftbl = im_iip_get_unitinftbl_regaddr( unit_id );
	if( p_uinftbl == NULL ) {
		return D_IM_IIP_INVALID_ARG_ERR;
	}

	Im_IIP_On_Pclk();
	Im_IIP_Dsb();

	switch( unit_id ) {
		case E_IM_IIP_UNIT_ID_SL0:	// FALLTHROUGH
		case E_IM_IIP_UNIT_ID_SL1:	// FALLTHROUGH
		case E_IM_IIP_UNIT_ID_SL2:	// FALLTHROUGH
		case E_IM_IIP_UNIT_ID_SL3:	// FALLTHROUGH
		case E_IM_IIP_UNIT_ID_SL4:	// FALLTHROUGH
		case E_IM_IIP_UNIT_ID_SL5:	// FALLTHROUGH
		case E_IM_IIP_UNIT_ID_SL6:	// FALLTHROUGH
		case E_IM_IIP_UNIT_ID_SL7:	// FALLTHROUGH
		case E_IM_IIP_UNIT_ID_SL8:
			im_iip_set_UNITINFTBL_SL( p_unitcfg, p_uinftbl );
			break;
		default:
			im_iip_set_UNITINFTBL( p_unitcfg, p_uinftbl );
			break;
	}

	Im_IIP_Off_Pclk();
	Im_IIP_Dsb();

	return D_IM_IIP_OK;
}

VOID im_iip_set_UNITINFTBL_SL( const T_IM_IIP_UNIT_CFG* const sl_cfg, volatile struct io_iip_uinftbl* const pUNITINFTBL )
{
	union {
		ULLONG					load_unit_param_flag;
		union io_iip_uinftbl_1	uinftbl_1;
	} u_pldunit = {
		.load_unit_param_flag = 0ull,
		.uinftbl_1.word = { 0ul, 0ul },
	};

	if( sl_cfg == NULL ) {
		pUNITINFTBL->UNITINFTBL0.bit.HWEN = D_IM_IIP_HW_CTRL_SWTRG;
	}
	else {
		pUNITINFTBL->UNITINFTBL0.bit.HWEN = sl_cfg->unit_ctrl;
		pUNITINFTBL->UNITINFTBL0.bit.CHAIN = sl_cfg->chain_enable;
		u_pldunit.load_unit_param_flag = sl_cfg->load_unit_param_flag;
		pUNITINFTBL->UNITINFTBL1 = u_pldunit.uinftbl_1;		// Force 32bit access
		pUNITINFTBL->UNITINFTBL2.bit.PADRS = sl_cfg->unit_param_addr;
	}
}

void im_iip_irq_enable( UINT32 irq_mask )
{
	UINT32	recursive_count;
	ULONG	cpu_id;

	cpu_id = Dd_ARM_Get_CPU_ID();
	if ( cpu_id >= D_IM_IIP_NUM_CPU_CORES ) {
		while ( 1 ) {	// Assersion
			;
		}
	}

	if ( S_GIM_IIP_CRETSEQ_RECURSIVE_COUNT[ cpu_id ] == 0 ) {
		while ( 1 ) {	// Assersion
			;
		}
	}

	recursive_count = S_GIM_IIP_CRETSEQ_RECURSIVE_COUNT[ cpu_id ];
	S_GIM_IIP_CRETSEQ_RECURSIVE_COUNT[ cpu_id ]--;

	if ( recursive_count == 1 ) {
		Dd_ARM_Spin_Unlock( &S_GIM_IIP_SPIN_LOCK );
	}
	Dd_ARM_EI( (UINT32)irq_mask );
}

UINT32 im_iip_irq_disable( void )
{
	UINT32	recursive_count;
	UINT32	lock_id = 0;
	ULONG	cpu_id;

	lock_id = (UINT32)Dd_ARM_DI();
	cpu_id = Dd_ARM_Get_CPU_ID();

	if ( cpu_id >= D_IM_IIP_NUM_CPU_CORES ) {
		while ( 1 ) {	// Assersion
			;
		}
	}

	if ( S_GIM_IIP_CRETSEQ_RECURSIVE_COUNT[cpu_id] >= D_IM_IIP_RECURSIVE_COUNT_MAX ) {
		while ( 1 ) {	// Assersion
			;
		}
	}

	recursive_count = S_GIM_IIP_CRETSEQ_RECURSIVE_COUNT[ cpu_id ];
	S_GIM_IIP_CRETSEQ_RECURSIVE_COUNT[ cpu_id ]++;

	if ( recursive_count == 0 ) {
		Dd_ARM_Spin_Lock( &S_GIM_IIP_SPIN_LOCK );
	}

	return lock_id;
}

INT32 Im_IIP_Get_UNIT_PARAM( const E_IM_IIP_UNIT_ID unit_id, ULONG* const p_param_buffer, UINT32* const param_size )
{
	UINT32			size;
	INT32			result;
	volatile ULONG* regaddr;

#ifdef CO_PARAM_CHECK
	if( (p_param_buffer == NULL) ||
	     (param_size == NULL) ) {
		Ddim_Assertion(("I:Im_IIP_Get_UNIT_PARAM INVALID_ARG_ERR\n"));
		return D_IM_IIP_INVALID_ARG_ERR;
	}
#endif

	im_iip_get_unit_param_size( &size, unit_id );
	if( size == D_IM_IIP_UNITPARAM_SIZE_ERROR ) {
		return D_IM_IIP_INVALID_ARG_ERR;
	}

	im_iip_On_Iipclk();
	im_iip_On_Iclk();
	Im_IIP_On_Pclk();
	Im_IIP_Dsb();

	while( 1 ) {
		if( IO_IIP.IZACTL1.bit.TRG != D_IM_IIP_STOPPED ) {
			result = D_IM_IIP_ERR;
			break;
		}


		regaddr = (volatile ULONG*)(((ULONG)&IO_IIP) + D_IM_IIP_UNITPARAM_BASEADDR);

		IO_IIP.IZACTL1.bit.SELRDREG_UNIT = unit_id;

		IO_IIP.IZACTL1.bit.DBEN = 1;
		im_iip_get_regword( p_param_buffer, regaddr, size );
		IO_IIP.IZACTL1.bit.DBEN = 0;

		*param_size = size;

		result = D_IM_IIP_OK;
		break;
	}

	Im_IIP_Off_Pclk();
	im_iip_Off_Iclk();
	im_iip_Off_Iipclk();
	Im_IIP_Dsb();

	return result;
}

INT32 Im_IIP_Set_AccessEnable( const UINT32 res_bitmask, const UCHAR permission_flg )
{
	UINT32 irq_mask;

	irq_mask = im_iip_irq_disable();

	Im_IIP_On_Pclk();

	if( (res_bitmask & E_IM_IIP_OPEN_RES_CACHE1) != 0 ) {
		IO_IIP.ACESEN0.bit.CA1RAC = permission_flg;
	}
	if( (res_bitmask & E_IM_IIP_OPEN_RES_CACHE2) != 0 ) {
		IO_IIP.ACESEN0.bit.CA2RAC = permission_flg;
	}
	if( (res_bitmask & E_IM_IIP_OPEN_RES_LUT_A) != 0 ) {
		IO_IIP.ACESEN0.bit.LUARAC = permission_flg;
	}
	if( (res_bitmask & E_IM_IIP_OPEN_RES_LUT_B) != 0 ) {
		IO_IIP.ACESEN0.bit.LUBRAC = permission_flg;
	}
	if( (res_bitmask & E_IM_IIP_OPEN_RES_LUT_C) != 0 ) {
		IO_IIP.ACESEN0.bit.LUCRAC = permission_flg;
	}
	if( (res_bitmask & E_IM_IIP_OPEN_RES_LUT_D) != 0 ) {
		IO_IIP.ACESEN0.bit.LUDRAC = permission_flg;
	}
	if( (res_bitmask & E_IM_IIP_OPEN_RES_LUT_E) != 0 ) {
		IO_IIP.ACESEN0.bit.LUERAC = permission_flg;
	}
	if( (res_bitmask & E_IM_IIP_OPEN_RES_LUT_F) != 0 ) {
		IO_IIP.ACESEN0.bit.LUFRAC = permission_flg;
	}
	if( (res_bitmask & E_IM_IIP_OPEN_RES_HIST_0) != 0 ) {
		IO_IIP.ACESEN0.bit.MO0RAC = permission_flg;
	}
	if( (res_bitmask & E_IM_IIP_OPEN_RES_HIST_1) != 0 ) {
		IO_IIP.ACESEN0.bit.MO1RAC = permission_flg;
	}
	if( (res_bitmask & E_IM_IIP_OPEN_RES_HIST_2) != 0 ) {
		IO_IIP.ACESEN0.bit.MO2RAC = permission_flg;
	}
	if( (res_bitmask & E_IM_IIP_OPEN_RES_HIST_3) != 0 ) {
		IO_IIP.ACESEN0.bit.MO3RAC = permission_flg;
	}

	Im_IIP_Off_Pclk();

	im_iip_irq_enable( irq_mask );

	if( permission_flg != 0 ) {
		Im_IIP_Dsb();
		im_iip_wait_usec( D_IM_IIP_SRAM_WAIT_USEC );
	}

	return D_IM_IIP_OK;
}

#if 0	// B2Y Link not support
/**
   Set Link enable register (LKEN).

   @param[in]	b2y_link			: <ul>
   										<li> @ref D_IM_IIP_ENABLE_ON : B2Y Link enable
   										<li> @ref D_IM_IIP_ENABLE_OFF : B2Y Linke disable
									  </ul>
   @retval		D_IM_IIP_OK				: Normal end.
*/
INT32 Im_IIP_Set_B2YLinkEnable( const UCHAR b2y_link )
{
	Im_IIP_On_Pclk();
	Im_IIP_Dsb();

	// link control
	IO_IIP.IZACTL1.bit.LKEN = b2y_link;

	Im_IIP_Off_Pclk();
	Im_IIP_Dsb();

	return D_IM_IIP_OK;
}
#endif	// B2Y Link not support

INT32 Im_IIP_Get_Genline( T_IM_IIP_GENLINE* const genline )
{
#ifdef CO_PARAM_CHECK
	if( genline == NULL ) {
		Ddim_Assertion(("I:Im_IIP_Get_Genline INVALID_ARG_ERR\n"));
		return D_IM_IIP_INVALID_ARG_ERR;
	}
#endif

	Im_IIP_On_Pclk();
	Im_IIP_Dsb();

	genline->b2y_outlineno = IO_IIP.GENLINE.GENLINE1.bit.B2Y_OUTLINENO;
	genline->afn_outlineno[0] = IO_IIP.GENLINE.GENLINE1.bit.AFN0_OUTLINENO;
	genline->afn_outlineno[1] = IO_IIP.GENLINE.GENLINE1.bit.AFN1_OUTLINENO;
	genline->afn_outlineno[2] = IO_IIP.GENLINE.GENLINE1.bit.AFN2_OUTLINENO;
	genline->afn_outlineno[3] = IO_IIP.GENLINE.GENLINE2.bit.AFN3_OUTLINENO;
	genline->frect_outlineno[0] = IO_IIP.GENLINE.GENLINE2.bit.FR0_OUTLINENO;
	genline->frect_outlineno[1] = IO_IIP.GENLINE.GENLINE2.bit.FR1_OUTLINENO;
	genline->ld_outlineno[0] = IO_IIP.GENLINE.GENLINE2.bit.LD0_OUTLINENO;
	genline->ld_outlineno[1] = IO_IIP.GENLINE.GENLINE3.bit.LD1_OUTLINENO;
	genline->ld_outlineno[2] = IO_IIP.GENLINE.GENLINE3.bit.LD2_OUTLINENO;
	genline->ld_outlineno[3] = IO_IIP.GENLINE.GENLINE3.bit.LD3_OUTLINENO;
	genline->ld_outlineno[4] = IO_IIP.GENLINE.GENLINE3.bit.LD4_OUTLINENO;
	genline->ld_outlineno[5] = IO_IIP.GENLINE.GENLINE4.bit.LD5_OUTLINENO;
	genline->ld_outlineno[6] = IO_IIP.GENLINE.GENLINE4.bit.LD6_OUTLINENO;
	genline->flt_outlineno = IO_IIP.GENLINE.GENLINE4.bit.FLT_OUTLINENO;

	Im_IIP_Off_Pclk();
	Im_IIP_Dsb();

	return D_IM_IIP_OK;
}

INT32 Im_IIP_Get_Debug_Monitor( T_IM_IIP_DEBUG_MONITOR* const monitor_val )
{
	union {
		ULLONG					data_out_port;
		union io_iip_dtout_mon	dtout_mon;
	} u_dtout_mon = {
		.data_out_port = 0ULL,
	};
	union {
		ULLONG					waiting_port;
		union io_iip_wait_mon	wait_mon;
	} u_wait_mon = {
		.waiting_port = 0ULL,
	};

#ifdef CO_PARAM_CHECK
	if( monitor_val == NULL ) {
		Ddim_Assertion(("I:Im_IIP_Get_Debug_Monitor INVALID_ARG_ERR\n"));
		return D_IM_IIP_INVALID_ARG_ERR;
	}
#endif

	Im_IIP_On_Pclk();
	Im_IIP_Dsb();

	u_dtout_mon.dtout_mon = IO_IIP.DTOUT_MON;		// Force 32bit access
	monitor_val->data_out_port = u_dtout_mon.data_out_port;
	u_wait_mon.wait_mon = IO_IIP.WAIT_MON;			// Force 32bit access
	monitor_val->waiting_port  = u_wait_mon.waiting_port;
	monitor_val->imgcache_data_out[0] = IO_IIP.PDC_DTOUT_MON.PDC_DTOUT_MON1.bit.PDC_DTOUT_MON_0;
	monitor_val->imgcache_data_out[1] = IO_IIP.PDC_DTOUT_MON.PDC_DTOUT_MON1.bit.PDC_DTOUT_MON_1;
	monitor_val->imgcache_data_out[2] = IO_IIP.PDC_DTOUT_MON.PDC_DTOUT_MON2.bit.PDC_DTOUT_MON_2;
	monitor_val->imgcache_ready[0] = IO_IIP.PDC_RDY_MON.PDC_RDY_MON1.bit.PDC_RDY_MON_0;
	monitor_val->imgcache_ready[1] = IO_IIP.PDC_RDY_MON.PDC_RDY_MON1.bit.PDC_RDY_MON_1;
	monitor_val->imgcache_ready[2] = IO_IIP.PDC_RDY_MON.PDC_RDY_MON2.bit.PDC_RDY_MON_2;

	Im_IIP_Off_Pclk();
	Im_IIP_Dsb();

	return D_IM_IIP_OK;
}

INT32 Im_IIP_Start_DumpUnitReg( const E_IM_IIP_UNIT_ID unit_id )
{
	Dd_ARM_Critical_Section_Start( S_GIM_IIP_SPIN_LOCK );

	Im_IIP_On_Pclk();
	im_iip_On_Iipclk();

	// IIP Force stop for Dump enabled.
	IO_IIP.IZACTL2.bit.ABORT = 0;

	IO_IIP.IZACTL1.bit.SELRDREG_UNIT = unit_id;
	IO_IIP.IZACTL1.bit.DBEN = 1;

	Dd_ARM_Critical_Section_End( S_GIM_IIP_SPIN_LOCK );

	return D_IM_IIP_OK;
}

INT32 Im_IIP_Stop_DumpUnitReg( VOID )
{
	Dd_ARM_Critical_Section_Start( S_GIM_IIP_SPIN_LOCK );

	IO_IIP.IZACTL1.bit.DBEN = 0;

	Im_IIP_Off_Pclk();
	im_iip_Off_Iipclk();

	Dd_ARM_Critical_Section_End( S_GIM_IIP_SPIN_LOCK );

	return D_IM_IIP_OK;
}

INT32 Im_IIP_Start_DumpUnitReg_ByName( const CHAR* const unit_name )
{
	UINT32 loopcnt;

	for( loopcnt = 0; loopcnt < (sizeof(S_GIM_IIP_DUMP_UNIT_NAME) / sizeof(S_GIM_IIP_DUMP_UNIT_NAME[0])); loopcnt++ ) {
		if( strcmp( unit_name, S_GIM_IIP_DUMP_UNIT_NAME[loopcnt].unit_name ) == 0 ) {
			return Im_IIP_Start_DumpUnitReg( S_GIM_IIP_DUMP_UNIT_NAME[loopcnt].unit_id );
		}
	}

	return D_IM_IIP_INVALID_ARG_ERR;
}

INT32 im_iip_twai_pol_flg( const DDIM_USER_ID flagid, const DDIM_USER_FLGPTN waiptn, const DDIM_USER_MODE wfmode, DDIM_USER_FLGPTN* const p_flgptn, const DDIM_USER_TMO tmout )
{
	DDIM_USER_ER ercd;

	if( tmout == D_DDIM_USER_SEM_WAIT_POL ) {
		ercd = DDIM_User_Pol_Flg( flagid, waiptn, wfmode, p_flgptn );
	}
	else {
		ercd = DDIM_User_Twai_Flg( flagid, waiptn, wfmode, p_flgptn, tmout );
	}

	if( D_DDIM_USER_E_TMOUT == ercd ) {
		return D_IM_IIP_TIMEOUT_ERR;
	}
	else
	if( D_DDIM_USER_E_OK != ercd ) {
		Im_IIP_Print_Pcdbg(( "im_iip_twai_pol_flg() err%u ercd=%d id=%u wait=0x%lx\n", 1, ercd, flagid, waiptn ));
		return D_IM_IIP_SYSTEMCALL_ERR;
	}
	return D_IM_IIP_OK;
}

INT32 im_iip_calc_timeout( T_IM_IIP_TIMEOUT* const tmout )
{
	switch( tmout->wait_time ) {
		case D_DDIM_USER_SEM_WAIT_FEVR:		// FALLTHROUGH
		case D_DDIM_USER_SEM_WAIT_POL:
			tmout->last_wait_time = tmout->wait_time;
			break;
		default:
			if( (tmout->wait_time) < (tmout->cur_time - tmout->start_time) ) {
				// Timeout
				return D_IM_IIP_TIMEOUT_ERR;
			}

			tmout->last_wait_time = tmout->wait_time - (DDIM_USER_TMO)(tmout->cur_time - tmout->start_time);
			break;
	}

	return D_IM_IIP_OK;
}
VOID Im_IIP_Print_DebugStatus( VOID )
{
}

VOID Im_IIP_Print_ClockStatus( VOID )
{
}

ImIipStatic *im_iip_static_new(void)
{
	ImIipStatic* self = k_object_new_with_private(IM_TYPE_IIP_STATIC,sizeof(ImIipStaticPrivate));
	return self;
}

