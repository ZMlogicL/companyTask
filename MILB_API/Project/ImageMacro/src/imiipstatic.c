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
static volatile UINT32 S_GIM_IIP_CRETSEQ_RECURSIVE_COUNT[ ImIipDefine_D_IM_IIP_NUM_CPU_CORES ] = { 0, 0, 0, 0 };

static const TImIipDumpUnitName S_GIM_IIP_DUMP_UNIT_NAME[] = {
	{ .unitId = ImIipStruct_E_IM_IIP_UNIT_ID_LD0,		.unitName = "ld0", },
	{ .unitId = ImIipStruct_E_IM_IIP_UNIT_ID_LD1,		.unitName = "ld1", },
	{ .unitId = ImIipStruct_E_IM_IIP_UNIT_ID_LD2,		.unitName = "ld2", },
	{ .unitId = ImIipStruct_E_IM_IIP_UNIT_ID_LD3,		.unitName = "ld3", },
	{ .unitId = ImIipStruct_E_IM_IIP_UNIT_ID_FLT,		.unitName = "flt", },
	{ .unitId = ImIipStruct_E_IM_IIP_UNIT_ID_AFN0,		.unitName = "afn0", },
	{ .unitId = ImIipStruct_E_IM_IIP_UNIT_ID_AFN1,		.unitName = "afn1", },
	{ .unitId = ImIipStruct_E_IM_IIP_UNIT_ID_AFN2,		.unitName = "afn2", },
	{ .unitId = ImIipStruct_E_IM_IIP_UNIT_ID_FRECT0,	.unitName = "frect0", },
	{ .unitId = ImIipStruct_E_IM_IIP_UNIT_ID_MON,		.unitName = "mon", },
	{ .unitId = ImIipStruct_E_IM_IIP_UNIT_ID_SL0,		.unitName = "sl0", },
	{ .unitId = ImIipStruct_E_IM_IIP_UNIT_ID_SL1,		.unitName = "sl1", },
	{ .unitId = ImIipStruct_E_IM_IIP_UNIT_ID_SL2,		.unitName = "sl2", },
	{ .unitId = ImIipStruct_E_IM_IIP_UNIT_ID_SL3,		.unitName = "sl3", },
	{ .unitId = ImIipStruct_E_IM_IIP_UNIT_ID_SL4,		.unitName = "sl4", },
	{ .unitId = ImIipStruct_E_IM_IIP_UNIT_ID_SL5,		.unitName = "sl5", },
	{ .unitId = ImIipStruct_E_IM_IIP_UNIT_ID_CSC0,		.unitName = "csc0", },
	{ .unitId = ImIipStruct_E_IM_IIP_UNIT_ID_CSC1,		.unitName = "csc1", },
	{ .unitId = ImIipStruct_E_IM_IIP_UNIT_ID_LUT,		.unitName = "lut", },
	{ .unitId = ImIipStruct_E_IM_IIP_UNIT_ID_GPC,		.unitName = "gpc", },
	{ .unitId = ImIipStruct_E_IM_IIP_UNIT_ID_BLEND0,	.unitName = "blend0", },
	{ .unitId = ImIipStruct_E_IM_IIP_UNIT_ID_BLEND1,	.unitName = "blend1", },
	{ .unitId = ImIipStruct_E_IM_IIP_UNIT_ID_FRECT1,	.unitName = "frect1", },
	{ .unitId = ImIipStruct_E_IM_IIP_UNIT_ID_CFL0,		.unitName = "cfl0", },
	{ .unitId = ImIipStruct_E_IM_IIP_UNIT_ID_CSC2,		.unitName = "csc2", },
	{ .unitId = ImIipStruct_E_IM_IIP_UNIT_ID_CSC3,		.unitName = "csc3", },
	{ .unitId = ImIipStruct_E_IM_IIP_UNIT_ID_SL6,		.unitName = "sl6", },
	{ .unitId = ImIipStruct_E_IM_IIP_UNIT_ID_SL7,		.unitName = "sl7", },
	{ .unitId = ImIipStruct_E_IM_IIP_UNIT_ID_SL8,		.unitName = "sl8", },
	{ .unitId = ImIipStruct_E_IM_IIP_UNIT_ID_LD4,		.unitName = "ld4", },
	{ .unitId = ImIipStruct_E_IM_IIP_UNIT_ID_LD5,		.unitName = "ld5", },
	{ .unitId = ImIipStruct_E_IM_IIP_UNIT_ID_LD6,		.unitName = "ld6", },
	{ .unitId = ImIipStruct_E_IM_IIP_UNIT_ID_LD7,		.unitName = "ld7", },
	{ .unitId = ImIipStruct_E_IM_IIP_UNIT_ID_AFN3,		.unitName = "afn3", },
	{ .unitId = ImIipStruct_E_IM_IIP_UNIT_ID_MFT,		.unitName = "mft", },
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

INT32 Im_IIP_Ctrl_SWTRG_Unit( const EImIipUnitId unitId, const TImIipUnitCfg* const p_unitcfg )
{
	volatile struct io_iip_uinftbl* p_uinftbl;

#ifdef ImIipStruct_CO_PARAM_CHECK
	if( p_unitcfg == NULL ) {
		Ddim_Assertion(("I:Im_IIP_Ctrl_SWTRG_Unit INVALID_ARG_ERR\n"));
		return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}
#endif	// ImIipStruct_CO_PARAM_CHECK

	p_uinftbl = im_iip_sun_get_unitinftbl_regaddr( unitId );
	if( p_uinftbl == NULL ) {
		return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}

	Im_IIP_On_Pclk();
	ImIipDefine_IM_IIP_DSB();

	switch( unitId ) {
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL0:	// FALLTHROUGH
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL1:	// FALLTHROUGH
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL2:	// FALLTHROUGH
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL3:	// FALLTHROUGH
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL4:	// FALLTHROUGH
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL5:	// FALLTHROUGH
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL6:	// FALLTHROUGH
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL7:	// FALLTHROUGH
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL8:
			im_iip_static_set_unitinftbl_sl( NULL,p_unitcfg, p_uinftbl );
			break;
		default:
			im_iip_couter_set_unitinftbl(NULL, p_unitcfg, p_uinftbl );
			break;
	}

	Im_IIP_Off_Pclk();
	ImIipDefine_IM_IIP_DSB();

	return ImIipDefine_D_IM_IIP_OK;
}

VOID im_iip_static_set_unitinftbl_sl( ImIipDefine* self, const TImIipUnitCfg* const sl_cfg, volatile struct io_iip_uinftbl* const pUNITINFTBL )
{
	union {
		ULLONG					loadUnitParamFlag;
		union io_iip_uinftbl_1	uinftbl_1;
	} u_pldunit = {
		.loadUnitParamFlag = 0ull,
		.uinftbl_1.word = { 0ul, 0ul },
	};

	if( sl_cfg == NULL ) {
		pUNITINFTBL->UNITINFTBL0.bit.HWEN = ImIipDefine_D_IM_IIP_HW_CTRL_SWTRG;
	}
	else {
		pUNITINFTBL->UNITINFTBL0.bit.HWEN = sl_cfg->unitCtrl;
		pUNITINFTBL->UNITINFTBL0.bit.CHAIN = sl_cfg->chainEnable;
		u_pldunit.loadUnitParamFlag = sl_cfg->loadUnitParamFlag;
		pUNITINFTBL->UNITINFTBL1 = u_pldunit.uinftbl_1;		// Force 32bit access
		pUNITINFTBL->UNITINFTBL2.bit.PADRS = sl_cfg->unitParamAddr;
	}
}

void im_iip_static_irq_enable( ImIipDefine* self, UINT32 irq_mask )
{
	UINT32	recursive_count;
	ULONG	cpu_id;

	cpu_id = Dd_ARM_Get_CPU_ID();
	if ( cpu_id >= ImIipDefine_D_IM_IIP_NUM_CPU_CORES ) {
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

UINT32 im_iip_static_irq_disable( void )
{
	UINT32	recursive_count;
	UINT32	lock_id = 0;
	ULONG	cpu_id;

	lock_id = (UINT32)Dd_ARM_DI();
	cpu_id = Dd_ARM_Get_CPU_ID();

	if ( cpu_id >= ImIipDefine_D_IM_IIP_NUM_CPU_CORES ) {
		while ( 1 ) {	// Assersion
			;
		}
	}

	if ( S_GIM_IIP_CRETSEQ_RECURSIVE_COUNT[cpu_id] >= ImIipDefine_D_IM_IIP_RECURSIVE_COUNT_MAX ) {
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

INT32 im_iip_static_get_unit_param( const EImIipUnitId unitId, ULONG* const p_param_buffer, UINT32* const param_size )
{
	UINT32			size;
	INT32			result;
	volatile ULONG* regaddr;

#ifdef ImIipStruct_CO_PARAM_CHECK
	if( (p_param_buffer == NULL) ||
	     (param_size == NULL) ) {
		Ddim_Assertion(("I:im_iip_static_get_unit_param INVALID_ARG_ERR\n"));
		return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}
#endif

	im_iip_sub_get_unit_param_size(NULL, &size, unitId );
	if( size == ImIipDefine_D_IM_IIP_UNITPARAM_SIZE_ERROR ) {
		return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}

	im_iip_counter_on_lipclk(NULL);
	im_iip_struct_on_lclk(NULL);
	Im_IIP_On_Pclk();
	ImIipDefine_IM_IIP_DSB();

	while( 1 ) {
		if( IO_IIP.IZACTL1.bit.TRG != ImIipDefine_D_IM_IIP_STOPPED ) {
			result = ImIipDefine_D_IM_IIP_ERR;
			break;
		}


		regaddr = (volatile ULONG*)(((ULONG)&IO_IIP) + ImIipDefine_D_IM_IIP_UNITPARAM_BASEADDR);

		IO_IIP.IZACTL1.bit.SELRDREG_UNIT = unitId;

		IO_IIP.IZACTL1.bit.DBEN = 1;
		im_iip_sub_get_regword(NULL, p_param_buffer, regaddr, size );
		IO_IIP.IZACTL1.bit.DBEN = 0;

		*param_size = size;

		result = ImIipDefine_D_IM_IIP_OK;
		break;
	}

	Im_IIP_Off_Pclk();
	im_iip_struct_off_iclk(NULL);
	im_iip_counter_off_lipclk(NULL);
	ImIipDefine_IM_IIP_DSB();

	return result;
}

INT32 im_iip_set_static_accessenable( const UINT32 resBitmask, const UCHAR permission_flg )
{
	UINT32 irq_mask;

	irq_mask = im_iip_static_irq_disable();

	Im_IIP_On_Pclk();

	if( (resBitmask & ImIipStruct_E_IM_IIP_OPEN_RES_CACHE1) != 0 ) {
		IO_IIP.ACESEN0.bit.CA1RAC = permission_flg;
	}
	if( (resBitmask & ImIipStruct_E_IM_IIP_OPEN_RES_CACHE2) != 0 ) {
		IO_IIP.ACESEN0.bit.CA2RAC = permission_flg;
	}
	if( (resBitmask & ImIipStruct_E_IM_IIP_OPEN_RES_LUT_A) != 0 ) {
		IO_IIP.ACESEN0.bit.LUARAC = permission_flg;
	}
	if( (resBitmask & ImIipStruct_E_IM_IIP_OPEN_RES_LUT_B) != 0 ) {
		IO_IIP.ACESEN0.bit.LUBRAC = permission_flg;
	}
	if( (resBitmask & ImIipStruct_E_IM_IIP_OPEN_RES_LUT_C) != 0 ) {
		IO_IIP.ACESEN0.bit.LUCRAC = permission_flg;
	}
	if( (resBitmask & ImIipStruct_E_IM_IIP_OPEN_RES_LUT_D) != 0 ) {
		IO_IIP.ACESEN0.bit.LUDRAC = permission_flg;
	}
	if( (resBitmask & ImIipStruct_E_IM_IIP_OPEN_RES_LUT_E) != 0 ) {
		IO_IIP.ACESEN0.bit.LUERAC = permission_flg;
	}
	if( (resBitmask & ImIipStruct_E_IM_IIP_OPEN_RES_LUT_F) != 0 ) {
		IO_IIP.ACESEN0.bit.LUFRAC = permission_flg;
	}
	if( (resBitmask & ImIipStruct_E_IM_IIP_OPEN_RES_HIST_0) != 0 ) {
		IO_IIP.ACESEN0.bit.MO0RAC = permission_flg;
	}
	if( (resBitmask & ImIipStruct_E_IM_IIP_OPEN_RES_HIST_1) != 0 ) {
		IO_IIP.ACESEN0.bit.MO1RAC = permission_flg;
	}
	if( (resBitmask & ImIipStruct_E_IM_IIP_OPEN_RES_HIST_2) != 0 ) {
		IO_IIP.ACESEN0.bit.MO2RAC = permission_flg;
	}
	if( (resBitmask & ImIipStruct_E_IM_IIP_OPEN_RES_HIST_3) != 0 ) {
		IO_IIP.ACESEN0.bit.MO3RAC = permission_flg;
	}

	Im_IIP_Off_Pclk();

	im_iip_static_irq_enable( NULL,irq_mask );

	if( permission_flg != 0 ) {
		ImIipDefine_IM_IIP_DSB();
		ImIipDefine_IM_IIP_WAIT_USEC( ImIipDefine_D_IM_IIP_SRAM_WAIT_USEC );
	}

	return ImIipDefine_D_IM_IIP_OK;
}

#if 0	// B2Y Link not support
/**
   Set Link enable register (LKEN).

   @param[in]	b2yLink			: <ul>
   										<li> @ref ImIipDefine_D_IM_IIP_ENABLE_ON : B2Y Link enable
   										<li> @ref ImIipDefine_D_IM_IIP_ENABLE_OFF : B2Y Linke disable
									  </ul>
   @retval		ImIipDefine_D_IM_IIP_OK				: Normal end.
*/
INT32 Im_IIP_Set_B2YLinkEnable( const UCHAR b2yLink )
{
	Im_IIP_On_Pclk();
	ImIipDefine_IM_IIP_DSB();

	// link control
	IO_IIP.IZACTL1.bit.LKEN = b2yLink;

	Im_IIP_Off_Pclk();
	ImIipDefine_IM_IIP_DSB();

	return ImIipDefine_D_IM_IIP_OK;
}
#endif	// B2Y Link not support

INT32 im_iip_static_get_genline( TImIipGenline* const genline )
{
#ifdef ImIipStruct_CO_PARAM_CHECK
	if( genline == NULL ) {
		Ddim_Assertion(("I:im_iip_static_get_genline INVALID_ARG_ERR\n"));
		return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}
#endif

	Im_IIP_On_Pclk();
	ImIipDefine_IM_IIP_DSB();

	genline->b2yOutlineno = IO_IIP.GENLINE.GENLINE1.bit.B2Y_OUTLINENO;
	genline->afnOutlineno[0] = IO_IIP.GENLINE.GENLINE1.bit.AFN0_OUTLINENO;
	genline->afnOutlineno[1] = IO_IIP.GENLINE.GENLINE1.bit.AFN1_OUTLINENO;
	genline->afnOutlineno[2] = IO_IIP.GENLINE.GENLINE1.bit.AFN2_OUTLINENO;
	genline->afnOutlineno[3] = IO_IIP.GENLINE.GENLINE2.bit.AFN3_OUTLINENO;
	genline->frectOutlineno[0] = IO_IIP.GENLINE.GENLINE2.bit.FR0_OUTLINENO;
	genline->frectOutlineno[1] = IO_IIP.GENLINE.GENLINE2.bit.FR1_OUTLINENO;
	genline->ldOutlineno[0] = IO_IIP.GENLINE.GENLINE2.bit.LD0_OUTLINENO;
	genline->ldOutlineno[1] = IO_IIP.GENLINE.GENLINE3.bit.LD1_OUTLINENO;
	genline->ldOutlineno[2] = IO_IIP.GENLINE.GENLINE3.bit.LD2_OUTLINENO;
	genline->ldOutlineno[3] = IO_IIP.GENLINE.GENLINE3.bit.LD3_OUTLINENO;
	genline->ldOutlineno[4] = IO_IIP.GENLINE.GENLINE3.bit.LD4_OUTLINENO;
	genline->ldOutlineno[5] = IO_IIP.GENLINE.GENLINE4.bit.LD5_OUTLINENO;
	genline->ldOutlineno[6] = IO_IIP.GENLINE.GENLINE4.bit.LD6_OUTLINENO;
	genline->fltOutlineno = IO_IIP.GENLINE.GENLINE4.bit.FLT_OUTLINENO;

	Im_IIP_Off_Pclk();
	ImIipDefine_IM_IIP_DSB();

	return ImIipDefine_D_IM_IIP_OK;
}

INT32 im_iip_static_get_debug_monitor( TImIipDebugMonitor* const monitor_val )
{
	union {
		ULLONG					dataOutPort;
		union io_iip_dtout_mon	dtout_mon;
	} u_dtout_mon = {
		.dataOutPort = 0ULL,
	};
	union {
		ULLONG					waitingPort;
		union io_iip_wait_mon	wait_mon;
	} u_wait_mon = {
		.waitingPort = 0ULL,
	};

#ifdef ImIipStruct_CO_PARAM_CHECK
	if( monitor_val == NULL ) {
		Ddim_Assertion(("I:im_iip_static_get_debug_monitor INVALID_ARG_ERR\n"));
		return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}
#endif

	Im_IIP_On_Pclk();
	ImIipDefine_IM_IIP_DSB();

	u_dtout_mon.dtout_mon = IO_IIP.DTOUT_MON;		// Force 32bit access
	monitor_val->dataOutPort = u_dtout_mon.dataOutPort;
	u_wait_mon.wait_mon = IO_IIP.WAIT_MON;			// Force 32bit access
	monitor_val->waitingPort  = u_wait_mon.waitingPort;
	monitor_val->imgcacheDataOut[0] = IO_IIP.PDC_DTOUT_MON.PDC_DTOUT_MON1.bit.PDC_DTOUT_MON_0;
	monitor_val->imgcacheDataOut[1] = IO_IIP.PDC_DTOUT_MON.PDC_DTOUT_MON1.bit.PDC_DTOUT_MON_1;
	monitor_val->imgcacheDataOut[2] = IO_IIP.PDC_DTOUT_MON.PDC_DTOUT_MON2.bit.PDC_DTOUT_MON_2;
	monitor_val->imgcacheReady[0] = IO_IIP.PDC_RDY_MON.PDC_RDY_MON1.bit.PDC_RDY_MON_0;
	monitor_val->imgcacheReady[1] = IO_IIP.PDC_RDY_MON.PDC_RDY_MON1.bit.PDC_RDY_MON_1;
	monitor_val->imgcacheReady[2] = IO_IIP.PDC_RDY_MON.PDC_RDY_MON2.bit.PDC_RDY_MON_2;

	Im_IIP_Off_Pclk();
	ImIipDefine_IM_IIP_DSB();

	return ImIipDefine_D_IM_IIP_OK;
}

INT32 im_iip_static_start_dumpunitreg( const EImIipUnitId unitId )
{
	Dd_ARM_Critical_Section_Start( S_GIM_IIP_SPIN_LOCK );

	Im_IIP_On_Pclk();
	im_iip_counter_on_lipclk(NULL);

	// IIP Force stop for Dump enabled.
	IO_IIP.IZACTL2.bit.ABORT = 0;

	IO_IIP.IZACTL1.bit.SELRDREG_UNIT = unitId;
	IO_IIP.IZACTL1.bit.DBEN = 1;

	Dd_ARM_Critical_Section_End( S_GIM_IIP_SPIN_LOCK );

	return ImIipDefine_D_IM_IIP_OK;
}

INT32 im_iip_static_stop_dumpunitreg( VOID )
{
	Dd_ARM_Critical_Section_Start( S_GIM_IIP_SPIN_LOCK );

	IO_IIP.IZACTL1.bit.DBEN = 0;

	Im_IIP_Off_Pclk();
	im_iip_counter_off_lipclk(NULL);

	Dd_ARM_Critical_Section_End( S_GIM_IIP_SPIN_LOCK );

	return ImIipDefine_D_IM_IIP_OK;
}

INT32 im_iip_static_dumpunitreg_byname( const CHAR* const unitName )
{
	UINT32 loopcnt;

	for( loopcnt = 0; loopcnt < (sizeof(S_GIM_IIP_DUMP_UNIT_NAME) / sizeof(S_GIM_IIP_DUMP_UNIT_NAME[0])); loopcnt++ ) {
		if( strcmp( unitName, S_GIM_IIP_DUMP_UNIT_NAME[loopcnt].unitName ) == 0 ) {
			return im_iip_static_start_dumpunitreg( S_GIM_IIP_DUMP_UNIT_NAME[loopcnt].unitId );
		}
	}

	return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
}

INT32 im_iip_static_twai_pol_flg( const DDIM_USER_ID flagid, const DDIM_USER_FLGPTN waiptn, const DDIM_USER_MODE wfmode, DDIM_USER_FLGPTN* const p_flgptn, const DDIM_USER_TMO tmout )
{
	DDIM_USER_ER ercd;

	if( tmout == D_DDIM_USER_SEM_WAIT_POL ) {
		ercd = DDIM_User_Pol_Flg( flagid, waiptn, wfmode, p_flgptn );
	}
	else {
		ercd = DDIM_User_Twai_Flg( flagid, waiptn, wfmode, p_flgptn, tmout );
	}

	if( D_DDIM_USER_E_TMOUT == ercd ) {
		return ImIipDefine_D_IM_IIP_TIMEOUT_ERR;
	}
	else
	if( D_DDIM_USER_E_OK != ercd ) {
		ImIipDefine_IM_IIP_PRINT_PCDBG(( "im_iip_static_twai_pol_flg() err%u ercd=%d id=%u wait=0x%lx\n", 1, ercd, flagid, waiptn ));
		return ImIipDefine_D_IM_IIP_SYSTEMCALL_ERR;
	}
	return ImIipDefine_D_IM_IIP_OK;
}

INT32 im_iip_static_calc_timeout( TImIipTimeout* const tmout )
{
	switch( tmout->waitTime ) {
		case D_DDIM_USER_SEM_WAIT_FEVR:		// FALLTHROUGH
		case D_DDIM_USER_SEM_WAIT_POL:
			tmout->lastWaitTime = tmout->waitTime;
			break;
		default:
			if( (tmout->waitTime) < (tmout->curTime - tmout->startTime) ) {
				// Timeout
				return ImIipDefine_D_IM_IIP_TIMEOUT_ERR;
			}

			tmout->lastWaitTime = tmout->waitTime - (DDIM_USER_TMO)(tmout->curTime - tmout->startTime);
			break;
	}

	return ImIipDefine_D_IM_IIP_OK;
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

