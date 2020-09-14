/*
 * imsdramc1.c
 *
 *  Created on: 2020年9月3日
 *      Author: sns
 */

#include "imsdramc1.h"
#include "imsdramc.h"
#include "sdramc.h"

typedef struct _ImSdramc1Private ImSdramc1Private;
 struct _ImSdramc1Private
{
	int a;
};

K_TYPE_DEFINE_DERIVED(ImSdramc1, im_sdramc1, sizeof(ImSdramc1Private),K_TYPE_OBJECT)
#define IM_SDRAMC1_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImSdramc1Private, IM_TYPE_SDRAMC1))

static void im_sdramc1_constructor(ImSdramc1 *self)
{
	//ImSdramcPrivate1 *priv = IM_SDRAMC1_GET_PRIVATE(self);
}

static void im_sdramc1_destructor(ImSdramc1 *self)
{
	//ImSdramcPrivate1 *priv = IM_SDRAMC1_GET_PRIVATE(self);
}

 VOID im_sdramc_on_pclk( E_IM_SDRAMC_CH ch )
{
#ifdef CO_ACT_SDRAMC_PCLOCK
	if ( ch == E_IM_SDRAMC_CH_0 ) {
		Dd_Top_Start_Clock( (UCHAR*)&gIM_SDRAMC_PCLK_Counter[ ch ], &Dd_Top_Get_CLKSTOP9(), ~D_DD_TOP_UMC0AP_BIT );
	}
	else  {
		Dd_Top_Start_Clock( (UCHAR*)&gIM_SDRAMC_PCLK_Counter[ ch ], &Dd_Top_Get_CLKSTOP9(), ~D_DD_TOP_UMC1AP_BIT );
	}
#endif
}

 VOID im_sdramc_off_pclk( E_IM_SDRAMC_CH ch )
{
#ifdef CO_ACT_SDRAMC_PCLOCK
	if ( ch == E_IM_SDRAMC_CH_0 ) {
		Dd_Top_Stop_Clock( (UCHAR*)&gIM_SDRAMC_PCLK_Counter[ ch ], &Dd_Top_Get_CLKSTOP9(), D_DD_TOP_UMC0AP_BIT );
	}
	else {
		Dd_Top_Stop_Clock( (UCHAR*)&gIM_SDRAMC_PCLK_Counter[ ch ], &Dd_Top_Get_CLKSTOP9(), D_DD_TOP_UMC1AP_BIT );
	}
#endif
}

INT32 im_sdramc_set_acceptancecapability( E_IM_SDRAMC_CH ch, E_IM_SDRAMC_PORT port, const UCHAR rnum, const UCHAR wnum )
{
#ifdef CO_PARAM_CHECK
	if ( ch >= E_IM_SDRAMC_CH_MAX ) {
		Ddim_Assertion(("im_sdramc_set_acceptancecapability() error. [ch] = %d\n", ch));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	switch(  port ) {
		case E_IM_SDRAMC_PORT_MX40:	// FALLTHROUGH
		case E_IM_SDRAMC_PORT_MX00:	// FALLTHROUGH
		case E_IM_SDRAMC_PORT_MX01:
			break;
		default:
			Ddim_Assertion(("im_sdramc_set_acceptancecapability() error. [port] = %d\n", port));
			return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
#endif

	im_sdramc_on_pclk( ch );
	im_sdramc_dsb();

	IO_SDRAMC[ ch ].EMBNUM[ port ].bit.WNUM = (ULONG)wnum;
	IO_SDRAMC[ ch ].EMBNUM[ port ].bit.RNUM = (ULONG)rnum;

	im_sdramc_off_pclk( ch );
	im_sdramc_dsb();

	return D_DDIM_OK;
}

INT32 im_sdramc_get_acceptancecapability( E_IM_SDRAMC_CH ch, E_IM_SDRAMC_PORT port, UCHAR* const rnum, UCHAR* const wnum )
{
#ifdef CO_PARAM_CHECK
	if ( ch >= E_IM_SDRAMC_CH_MAX ) {
		Ddim_Assertion(("im_sdramc_get_acceptancecapability() error. [ch] = %d\n", ch));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	switch(  port ) {
		case E_IM_SDRAMC_PORT_MX40:	// FALLTHROUGH
		case E_IM_SDRAMC_PORT_MX00:	// FALLTHROUGH
		case E_IM_SDRAMC_PORT_MX01:
			break;
		default:
			Ddim_Assertion(("im_sdramc_get_acceptancecapability() error. [port] = %d\n", port));
			return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
#endif

	im_sdramc_on_pclk( ch );
	im_sdramc_dsb();

	*wnum = (UCHAR)IO_SDRAMC[ ch ].EMBNUM[ port ].bit.WNUM;
	*rnum = (UCHAR)IO_SDRAMC[ ch ].EMBNUM[ port ].bit.RNUM;

	im_sdramc_off_pclk( ch );
	im_sdramc_dsb();

	return D_DDIM_OK;
}

INT32 im_sdramc_set_burstlimit( E_IM_SDRAMC_CH ch, E_IM_SDRAMC_PORT port, const E_IM_SDRAMC_BURST_LIMIT rsize, const E_IM_SDRAMC_BURST_LIMIT wsize )
{
#ifdef CO_PARAM_CHECK
	if ( ch >= E_IM_SDRAMC_CH_MAX ) {
		Ddim_Assertion(("im_sdramc_set_burstlimit() error. [ch] = %d\n", ch));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	switch(  port ) {
		case E_IM_SDRAMC_PORT_MX40:	// FALLTHROUGH
		case E_IM_SDRAMC_PORT_MX00:	// FALLTHROUGH
		case E_IM_SDRAMC_PORT_MX01:
			break;
		default:
			Ddim_Assertion(("im_sdramc_set_burstlimit() error. [port] = %d\n", port));
			return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
#endif

	im_sdramc_on_pclk( ch );
	im_sdramc_dsb();

	IO_SDRAMC[ ch ].EMBNUM[ port ].bit.RSIZE = (ULONG)rsize;
	IO_SDRAMC[ ch ].EMBNUM[ port ].bit.WSIZE = (ULONG)wsize;

	im_sdramc_off_pclk( ch );
	im_sdramc_dsb();

	return D_DDIM_OK;
}

INT32 im_sdramc_get_burstlimit( E_IM_SDRAMC_CH ch, E_IM_SDRAMC_PORT port, E_IM_SDRAMC_BURST_LIMIT* const rsize, E_IM_SDRAMC_BURST_LIMIT* const wsize )
{
#ifdef CO_PARAM_CHECK
	if ( ch >= E_IM_SDRAMC_CH_MAX ) {
		Ddim_Assertion(("im_sdramc_get_burstlimit() error. [ch] = %d\n", ch));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	switch(  port ) {
		case E_IM_SDRAMC_PORT_MX40:	// FALLTHROUGH
		case E_IM_SDRAMC_PORT_MX00:	// FALLTHROUGH
		case E_IM_SDRAMC_PORT_MX01:
			break;
		default:
			Ddim_Assertion(("im_sdramc_get_burstlimit() error. [port] = %d\n", port));
			return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
#endif

	im_sdramc_on_pclk( ch );
	im_sdramc_dsb();

	*rsize = (E_IM_SDRAMC_BURST_LIMIT)IO_SDRAMC[ ch ].EMBNUM[ port ].bit.RSIZE;
	*wsize = (E_IM_SDRAMC_BURST_LIMIT)IO_SDRAMC[ ch ].EMBNUM[ port ].bit.WSIZE;

	im_sdramc_off_pclk( ch );
	im_sdramc_dsb();

	return D_DDIM_OK;
}

INT32 im_sdramc_set_remapaddr( E_IM_SDRAMC_CH ch, E_IM_SDRAMC_PORT port, const LONG addr )
{
#ifdef CO_PARAM_CHECK
	if ( ch >= E_IM_SDRAMC_CH_MAX ) {
		Ddim_Assertion(("im_sdramc_set_remapaddr() error. [ch] = %d\n", ch));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	if ( ( port < E_IM_SDRAMC_PORT_DS0 ) || ( port >= E_IM_SDRAMC_PORT_MAX ) ) {
		Ddim_Assertion(("im_sdramc_set_remapaddr() error. [port] = %d\n", port));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
#endif

	im_sdramc_on_pclk( ch );
	im_sdramc_dsb();

	im_sdramc_set_reg_signed( IO_SDRAMC[ ch ].REMAPADDR[ port ], union io_sdramc_remapaddr, REMAPADDR, ( addr >> D_IM_SDRAMC_SHIFT_REMAPADDR ) );

	im_sdramc_off_pclk( ch );
	im_sdramc_dsb();

	return D_DDIM_OK;
}

INT32 im_sdramc_get_remapaddr( E_IM_SDRAMC_CH ch, E_IM_SDRAMC_PORT port, LONG* const addr )
{
#ifdef CO_PARAM_CHECK
	if ( ch >= E_IM_SDRAMC_CH_MAX ) {
		Ddim_Assertion(("im_sdramc_get_remapaddr() error. [ch] = %d\n", ch));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	if ( ( port < E_IM_SDRAMC_PORT_DS0 ) || ( port >= E_IM_SDRAMC_PORT_MAX ) ) {
		Ddim_Assertion(("im_sdramc_get_remapaddr() error. [port] = %d\n", port));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	if ( addr == NULL ) {
		Ddim_Assertion(("im_sdramc_get_remapaddr() error. [addr] is NULL\n"));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
#endif

	im_sdramc_on_pclk( ch );
	im_sdramc_dsb();

	// Remap address get.
	im_sdramc_get_reg_signed( *addr, IO_SDRAMC[ ch ].REMAPADDR[ port ], union io_sdramc_remapaddr, REMAPADDR );
	*addr = ( *addr << D_IM_SDRAMC_SHIFT_REMAPADDR );

	im_sdramc_off_pclk( ch );
	im_sdramc_dsb();

	return D_DDIM_OK;
}

INT32 im_sdramc_set_ch_select( E_IM_SDRAMC_CH ch, E_IM_SDRAMC_PORT port)
{
#ifdef CO_PARAM_CHECK
	if ( ch >= E_IM_SDRAMC_CH_MAX ) {
		Ddim_Assertion(("im_sdramc_set_ch_select() error. [ch] = %d\n", ch));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	if ( ( port != E_IM_SDRAMC_PORT_VE0 ) &&
		 ( port != E_IM_SDRAMC_PORT_VE1 ) &&
		 ( port != E_IM_SDRAMC_PORT_VD1 ) ) {
		Ddim_Assertion(("im_sdramc_set_ch_select() error. [port] = %d\n", port));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	if ( port != E_IM_SDRAMC_PORT_VD1 ) {
		Ddim_Assertion(("im_sdramc_set_ch_select() error. [port] = %d\n", port));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif	// CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
#endif

	im_sdramc_on_pclk( ch );
	im_sdramc_dsb();

	IO_SDRAMC[ ch ].CHSEL[ port ].bit.CH = ch;

	im_sdramc_off_pclk( ch );
	im_sdramc_dsb();

	return D_DDIM_OK;
}

INT32 im_sdramc_get_ch_select( E_IM_SDRAMC_CH ch, E_IM_SDRAMC_PORT port, E_IM_SDRAMC_CH* chsel )
{
#ifdef CO_PARAM_CHECK
	if ( ch >= E_IM_SDRAMC_CH_MAX ) {
		Ddim_Assertion(("im_sdramc_get_ch_select() error. [ch] = %d\n", ch));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	if ( ( port != E_IM_SDRAMC_PORT_VE0 ) &&
		 ( port != E_IM_SDRAMC_PORT_VE1 ) &&
		 ( port != E_IM_SDRAMC_PORT_VD1 ) ) {
		Ddim_Assertion(("im_sdramc_get_ch_select() error. [port] = %d\n", port));
	}
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	if ( port != E_IM_SDRAMC_PORT_VD1 ) {
		Ddim_Assertion(("im_sdramc_get_ch_select() error. [port] = %d\n", port));
	}
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif	// CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	if ( chsel == NULL ) {
		Ddim_Assertion(("im_sdramc_get_ch_select() error. [chsel] is NULL\n"));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
#endif

	im_sdramc_on_pclk( ch );
	im_sdramc_dsb();

	// CHSEL get.
	*chsel = IO_SDRAMC[ ch ].CHSEL[ port ].bit.CH;

	im_sdramc_off_pclk( ch );
	im_sdramc_dsb();

	return D_DDIM_OK;
}

INT32 im_sdramc_set_cmd_arbitration_rate( E_IM_SDRAMC_CH ch, const T_IM_SDRAMC_CMD_ARB_RATE* const cmd_arb )
{
	UCHAR port;

#ifdef CO_PARAM_CHECK
	if ( ch >= E_IM_SDRAMC_CH_MAX ) {
		Ddim_Assertion(("im_sdramc_set_cmd_arbitration_rate() error. [ch] = %d\n", ch));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	if ( cmd_arb == NULL ) {
		Ddim_Assertion(("im_sdramc_set_cmd_arbitration_rate() error. [cmd_arb] is NULL\n"));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	for ( port = 0; port < E_IM_SDRAMC_PORT_MAX; port++ ) {
		if ( cmd_arb->enable[ port ] > E_IM_SDRAMC_EN_ENABLE ) {
			Ddim_Assertion(("im_sdramc_set_cmd_arbitration_rate() error. [cmd_arb->enable[%d]] = %d\n", port, cmd_arb->enable[ port ]));
			return D_IM_SDRAMC_INPUT_PARAM_ERROR;
		}
	}
#endif

	im_sdramc_on_pclk( ch );
	im_sdramc_dsb();

	for ( port = 0; port < E_IM_SDRAMC_PORT_MAX; port++ ) {
		// Rate control information set.
		IO_SDRAMC[ ch ].RATECONT[ port ].bit.CYCNUM				= cmd_arb->throughput[ port ];
		IO_SDRAMC[ ch ].RATECONT[ port ].bit.LATNUM				= cmd_arb->latency[ port ];
		// Rate control enable.
		IO_SDRAMC[ ch ].MASTEROPTION[ port ].bit.ENABLE_CAT_R	= cmd_arb->enable[ port ];
	}

	im_sdramc_dsb();

	// Rate control register reflect.
	IO_SDRAMC[ ch ].RATE_CHANGE.bit.RATE_CHG = 1;

	im_sdramc_off_pclk( ch );
	im_sdramc_dsb();

	return D_DDIM_OK;
}

INT32 im_sdramc_get_cmd_arbitration_rate( E_IM_SDRAMC_CH ch, T_IM_SDRAMC_CMD_ARB_RATE* const cmd_arb )
{
	UCHAR port;

#ifdef CO_PARAM_CHECK
	if ( ch >= E_IM_SDRAMC_CH_MAX ) {
		Ddim_Assertion(("im_sdramc_get_cmd_arbitration_rate() error. [ch] = %d\n", ch));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	if ( cmd_arb == NULL ) {
		Ddim_Assertion(("im_sdramc_get_cmd_arbitration_rate() error. [cmd_arb] is NULL\n"));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
#endif

	im_sdramc_on_pclk( ch );
	im_sdramc_dsb();

	for ( port = 0; port < E_IM_SDRAMC_PORT_MAX; port++ ) {
		// Rate control information get.
		cmd_arb->throughput[ port ]	= IO_SDRAMC[ ch ].RATECONT[ port ].bit.CYCNUM;
		cmd_arb->latency[ port ]	= IO_SDRAMC[ ch ].RATECONT[ port ].bit.LATNUM;
		cmd_arb->enable[ port ]		= IO_SDRAMC[ ch ].MASTEROPTION[ port ].bit.ENABLE_CAT_R;
	}

	im_sdramc_off_pclk( ch );
	im_sdramc_dsb();

	return D_DDIM_OK;
}

INT32 im_sdramc_set_cmd_arbitration_priority( E_IM_SDRAMC_CH ch, const T_IM_SDRAMC_CMD_ARB_PRI* const cmd_arb )
{
	UCHAR port;

#ifdef CO_PARAM_CHECK
	if ( ch >= E_IM_SDRAMC_CH_MAX ) {
		Ddim_Assertion(("im_sdramc_set_cmd_arbitration_priority() error. [ch] = %d\n", ch));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	if ( cmd_arb == NULL ) {
		Ddim_Assertion(("im_sdramc_set_cmd_arbitration_priority() error. [cmd_arb] is NULL\n"));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	for ( port = 0; port < E_IM_SDRAMC_PORT_MAX; port++ ) {
		if ( cmd_arb->enable[ port ] > E_IM_SDRAMC_EN_ENABLE ) {
			Ddim_Assertion(("im_sdramc_set_cmd_arbitration_priority() error. [cmd_arb->enable[%d]] = %d\n", port, cmd_arb->enable[ port ]));
			return D_IM_SDRAMC_INPUT_PARAM_ERROR;
		}
	}
#endif

	im_sdramc_on_pclk( ch );
	im_sdramc_dsb();

	for ( port = 0; port < E_IM_SDRAMC_PORT_MAX; port++ ) {
		// Priority contrl infformation set.
		IO_SDRAMC[ ch ].PRIORIT_CAT[ port ].bit.PRIORIT_CAT_B = cmd_arb->priority[ port ];
		// Priority control enable.
		IO_SDRAMC[ ch ].MASTEROPTION[ port ].bit.ENABLE_CAT_B = cmd_arb->enable[ port ];
	}

	im_sdramc_off_pclk( ch );
	im_sdramc_dsb();

	return D_DDIM_OK;
}

INT32 im_sdramc_get_cmd_arbitration_priority( E_IM_SDRAMC_CH ch, T_IM_SDRAMC_CMD_ARB_PRI* const cmd_arb )
{
	UCHAR port;

#ifdef CO_PARAM_CHECK
	if ( ch >= E_IM_SDRAMC_CH_MAX ) {
		Ddim_Assertion(("im_sdramc_get_cmd_arbitration_priority() error. [ch] = %d\n", ch));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	if ( cmd_arb == NULL ) {
		Ddim_Assertion(("im_sdramc_get_cmd_arbitration_priority() error. [cmd_arb] is NULL\n"));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
#endif

	im_sdramc_on_pclk( ch );
	im_sdramc_dsb();

	for ( port = 0; port < E_IM_SDRAMC_PORT_MAX; port++ ) {
		// Priority contrl infformation get.
		cmd_arb->priority[ port ]	= IO_SDRAMC[ ch ].PRIORIT_CAT[ port ].bit.PRIORIT_CAT_B;
		cmd_arb->enable[ port ]		= IO_SDRAMC[ ch ].MASTEROPTION[ port ].bit.ENABLE_CAT_B;
	}

	im_sdramc_off_pclk( ch );
	im_sdramc_dsb();

	return D_DDIM_OK;
}

INT32 im_sdramc_set_mode_register( E_IM_SDRAMC_CH ch, E_IM_SDRAMC_RANK rank, const UCHAR ma, const UCHAR data )
{
	union io_sdramc_umcmracs	umcmracs;

#ifdef CO_PARAM_CHECK
	if ( ch >= E_IM_SDRAMC_CH_MAX ) {
		Ddim_Assertion(("im_sdramc_set_mode_register() error. [ch] = %d\n", ch));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	if ( rank > E_IM_SDRAMC_RANK_1 ) {
		Ddim_Assertion(("im_sdramc_set_mode_register() error. [rank] = %d\n", rank));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
#endif

	im_sdramc_on_pclk( ch );
	im_sdramc_dsb();

	// Write data set.
	IO_SDRAMC[ ch ].UMCMRWDT.bit.WDATA = data;

	// Command setting.
	umcmracs.word			= 0;
	umcmracs.bit.MRMA		= ma;
	umcmracs.bit.RESERVED0	= 0x0000;
	umcmracs.bit.MRMODE		= 0xF;
	umcmracs.bit.MRRANK		= rank;
	umcmracs.bit.RESERVED1	= 0x3;

	IO_SDRAMC[ ch ].UMCMRACS.word = umcmracs.word;

	im_sdramc_dsb();

	// status check.
	while( IO_SDRAMC[ ch ].UMCMRACSST.bit.MRST == 0 ) {
		;	// Do nothing.
	}

	// status clear.
	IO_SDRAMC[ ch ].UMCMRACSST.bit.MRST = 1;

	im_sdramc_off_pclk( ch );
	im_sdramc_dsb();

	return D_DDIM_OK;
}

INT32 im_sdeamc_get_mode_register( E_IM_SDRAMC_CH ch, E_IM_SDRAMC_RANK rank, const UCHAR ma, UCHAR* const data )
{
	union io_sdramc_umcmracs	umcmracs;

#ifdef CO_PARAM_CHECK
	if ( ch >= E_IM_SDRAMC_CH_MAX ) {
		Ddim_Assertion(("im_sdeamc_get_mode_register() error. [ch] = %d\n", ch));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	if ( rank > E_IM_SDRAMC_RANK_1 ) {
		Ddim_Assertion(("im_sdeamc_get_mode_register() error. [rank] = %d\n", rank));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	if ( data == NULL ) {
		Ddim_Assertion(("im_sdeamc_get_mode_register() error. [data] is NULL\n"));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
#endif

	im_sdramc_on_pclk( ch );
	im_sdramc_dsb();

	// Command setting.
	umcmracs.word			= 0;
	umcmracs.bit.MRMA		= ma;
	umcmracs.bit.RESERVED0	= 0x0000;
	umcmracs.bit.MRMODE		= 0x7;
	umcmracs.bit.MRRANK		= rank;
	umcmracs.bit.RESERVED1	= 0x3;

	IO_SDRAMC[ ch ].UMCMRACS.word = umcmracs.word;

	im_sdramc_dsb();

	// status check.
	while( IO_SDRAMC[ ch ].UMCMRACSST.bit.MRST == 0 ) {
		;	// Do nothing.
	}

	// Read data get.
	*data = (UCHAR)IO_SDRAMC[ ch ].UMCMRRDT.bit.RDATA;

	// status clear.
	IO_SDRAMC[ ch ].UMCMRACSST.bit.MRST = 1;

	im_sdramc_off_pclk( ch );
	im_sdramc_dsb();

	return D_DDIM_OK;
}

INT32 im_sdramc_set_clock_enable_busIf( E_IM_SDRAMC_CH ch, E_IM_SDRAMC_PORT port, E_IM_SDRAMC_ACCESS access, E_IM_SDRAMC_EN enable )
{
	ULONG	clkifa;
	ULONG	clkifb;
	ULONG	clkifc;
	UCHAR	clkds0;
	UCHAR	clkds1;

#ifdef CO_PARAM_CHECK
	if ( ch >= E_IM_SDRAMC_CH_MAX ) {
		Ddim_Assertion(("im_sdramc_set_clock_enable_busIf() error. [ch] = %d\n", ch));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	if ( port >= E_IM_SDRAMC_PORT_MAX ) {
		Ddim_Assertion(("im_sdramc_set_clock_enable_busIf() error. [port] = %d\n", port));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	if ( access > E_IM_SDRAMC_ACCESS_WRITE ) {
		Ddim_Assertion(("im_sdramc_set_clock_enable_busIf() error. [access] = %d\n", access));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	if ( enable > E_IM_SDRAMC_EN_ENABLE ) {
		Ddim_Assertion(("im_sdramc_set_clock_enable_busIf() error. [enable] = %d\n", enable));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
#endif

	im_sdramc_on_pclk( ch );
	im_sdramc_dsb();

	if ( enable == E_IM_SDRAMC_EN_ENABLE ) {

		clkifa = IO_SDRAMC[ ch ].CLKENBIFA.word;
		clkifb = IO_SDRAMC[ ch ].CLKENBIFB.word;
		clkifc = IO_SDRAMC[ ch ].CLKENBIFC.word;

		if ( ( clkifa == 0 ) &&
			 ( clkifb == 0 ) &&
			 ( ( clkifc & 0x3FFC0000 ) == 0 ) ) {
			IO_SDRAMC[ ch ].CLKENBIFC.bit.CLKBIF = E_IM_SDRAMC_EN_ENABLE;
		}

		if ( ( port == E_IM_SDRAMC_PORT_DS0 ) ||
			 ( port == E_IM_SDRAMC_PORT_DS1 ) ) {

			clkds0 = IO_SDRAMC[ ch ].CLKENBIFC.bit.CLKDS0;
			clkds1 = IO_SDRAMC[ ch ].CLKENBIFC.bit.CLKDS1;

			if ( ( clkds0 == E_IM_SDRAMC_EN_DISABLE ) &&
				 ( clkds1 == E_IM_SDRAMC_EN_DISABLE ) ) {
				IO_SDRAMC[ ch ].CLKENBIFC.bit.CLKDSP = E_IM_SDRAMC_EN_ENABLE;
			}
		}
	}

	im_sdramc_dsb();

	switch ( port ) {
		case E_IM_SDRAMC_PORT_MX10:
			if ( access == E_IM_SDRAMC_ACCESS_WRITE ) {
				IO_SDRAMC[ ch ].CLKENBIFA.bit.CLKWMX10 = enable;
			}
			else {
				IO_SDRAMC[ ch ].CLKENBIFB.bit.CLKRMX10 = enable;
			}
			break;
		case E_IM_SDRAMC_PORT_MX11:
			if ( access == E_IM_SDRAMC_ACCESS_WRITE ) {
				IO_SDRAMC[ ch ].CLKENBIFA.bit.CLKWMX11 = enable;
			}
			else {
				IO_SDRAMC[ ch ].CLKENBIFB.bit.CLKRMX11 = enable;
			}
			break;
		case E_IM_SDRAMC_PORT_MX12:
			if ( access == E_IM_SDRAMC_ACCESS_WRITE ) {
				IO_SDRAMC[ ch ].CLKENBIFA.bit.CLKWMX12 = enable;
			}
			else {
				IO_SDRAMC[ ch ].CLKENBIFB.bit.CLKRMX12 = enable;
			}
			break;
		case E_IM_SDRAMC_PORT_MX13:
			if ( access == E_IM_SDRAMC_ACCESS_WRITE ) {
				IO_SDRAMC[ ch ].CLKENBIFA.bit.CLKWMX13 = enable;
			}
			else {
				IO_SDRAMC[ ch ].CLKENBIFB.bit.CLKRMX13 = enable;
			}
			break;
		case E_IM_SDRAMC_PORT_MX20:
			if ( access == E_IM_SDRAMC_ACCESS_WRITE ) {
				IO_SDRAMC[ ch ].CLKENBIFA.bit.CLKWMX20 = enable;
			}
			else {
				IO_SDRAMC[ ch ].CLKENBIFB.bit.CLKRMX20 = enable;
			}
			break;
		case E_IM_SDRAMC_PORT_MX21:
			if ( access == E_IM_SDRAMC_ACCESS_WRITE ) {
				IO_SDRAMC[ ch ].CLKENBIFA.bit.CLKWMX21 = enable;
			}
			else {
				IO_SDRAMC[ ch ].CLKENBIFB.bit.CLKRMX21 = enable;
			}
			break;
		case E_IM_SDRAMC_PORT_MX22:
			if ( access == E_IM_SDRAMC_ACCESS_WRITE ) {
				IO_SDRAMC[ ch ].CLKENBIFA.bit.CLKWMX22 = enable;
			}
			else {
				IO_SDRAMC[ ch ].CLKENBIFB.bit.CLKRMX22 = enable;
			}
			break;
		case E_IM_SDRAMC_PORT_MX23:
			if ( access == E_IM_SDRAMC_ACCESS_WRITE ) {
				IO_SDRAMC[ ch ].CLKENBIFA.bit.CLKWMX23 = enable;
			}
			else {
				IO_SDRAMC[ ch ].CLKENBIFB.bit.CLKRMX23 = enable;
			}
			break;
		case E_IM_SDRAMC_PORT_MX30:
			if ( access == E_IM_SDRAMC_ACCESS_WRITE ) {
				IO_SDRAMC[ ch ].CLKENBIFA.bit.CLKWMX30 = enable;
			}
			else {
				IO_SDRAMC[ ch ].CLKENBIFB.bit.CLKRMX30 = enable;
			}
			break;
		case E_IM_SDRAMC_PORT_MX31:
			if ( access == E_IM_SDRAMC_ACCESS_WRITE ) {
				IO_SDRAMC[ ch ].CLKENBIFA.bit.CLKWMX31 = enable;
			}
			else {
				IO_SDRAMC[ ch ].CLKENBIFB.bit.CLKRMX31 = enable;
			}
			break;
		case E_IM_SDRAMC_PORT_MX32:
			if ( access == E_IM_SDRAMC_ACCESS_WRITE ) {
				IO_SDRAMC[ ch ].CLKENBIFA.bit.CLKWMX32 = enable;
			}
			else {
				IO_SDRAMC[ ch ].CLKENBIFB.bit.CLKRMX32 = enable;
			}
			break;
		case E_IM_SDRAMC_PORT_MX33:
			if ( access == E_IM_SDRAMC_ACCESS_WRITE ) {
				IO_SDRAMC[ ch ].CLKENBIFA.bit.CLKWMX33 = enable;
			}
			else {
				IO_SDRAMC[ ch ].CLKENBIFB.bit.CLKRMX33 = enable;
			}
			break;
		case E_IM_SDRAMC_PORT_MX40:	// Read only.
			if ( access == E_IM_SDRAMC_ACCESS_READ ) {
				IO_SDRAMC[ ch ].CLKENBIFB.bit.CLKRMX40 = enable;
			}
			break;
		case E_IM_SDRAMC_PORT_MX50:
			if ( access == E_IM_SDRAMC_ACCESS_WRITE ) {
				IO_SDRAMC[ ch ].CLKENBIFA.bit.CLKWMX50 = enable;
			}
			else {
				IO_SDRAMC[ ch ].CLKENBIFB.bit.CLKRMX50 = enable;
			}
			break;
		case E_IM_SDRAMC_PORT_MX51:
			if ( access == E_IM_SDRAMC_ACCESS_WRITE ) {
				IO_SDRAMC[ ch ].CLKENBIFA.bit.CLKWMX51 = enable;
			}
			else {
				IO_SDRAMC[ ch ].CLKENBIFB.bit.CLKRMX51 = enable;
			}
			break;
		case E_IM_SDRAMC_PORT_MX00:	// Write only port.
			if ( access == E_IM_SDRAMC_ACCESS_WRITE ) {
				IO_SDRAMC[ ch ].CLKENBIFA.bit.CLKWMX00 = enable;
			}
			else {
				IO_SDRAMC[ ch ].CLKENBIFB.bit.CLKRMX00 = E_IM_SDRAMC_EN_DISABLE;
			}
			break;
		case E_IM_SDRAMC_PORT_MX01:	// Write only port.
			if ( access == E_IM_SDRAMC_ACCESS_WRITE ) {
				IO_SDRAMC[ ch ].CLKENBIFA.bit.CLKWMX01 = enable;
			}
			else {
				IO_SDRAMC[ ch ].CLKENBIFB.bit.CLKRMX01 = E_IM_SDRAMC_EN_DISABLE;
			}
			break;
		case E_IM_SDRAMC_PORT_MX60:
			if ( access == E_IM_SDRAMC_ACCESS_WRITE ) {
				IO_SDRAMC[ ch ].CLKENBIFA.bit.CLKWMX60 = enable;
			}
			else {
				IO_SDRAMC[ ch ].CLKENBIFB.bit.CLKRMX60 = enable;
			}
			break;
		case E_IM_SDRAMC_PORT_RB0:
			IO_SDRAMC[ ch ].CLKENBIFC.bit.CLKRB0 = enable;
			break;
		case E_IM_SDRAMC_PORT_RB1:
			IO_SDRAMC[ ch ].CLKENBIFC.bit.CLKRB1 = enable;
			break;
		case E_IM_SDRAMC_PORT_RB2:
			IO_SDRAMC[ ch ].CLKENBIFC.bit.CLKRB2 = enable;
			break;
		case E_IM_SDRAMC_PORT_DS0:
			IO_SDRAMC[ ch ].CLKENBIFC.bit.CLKDS0 = enable;
			break;
		case E_IM_SDRAMC_PORT_DS1:
			IO_SDRAMC[ ch ].CLKENBIFC.bit.CLKDS1 = enable;
			break;
		case E_IM_SDRAMC_PORT_SDM:
			IO_SDRAMC[ ch ].CLKENBIFC.bit.CLKSDM = enable;
			break;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
		case E_IM_SDRAMC_PORT_VE0:
			IO_SDRAMC[ ch ].CLKENBIFC.bit.CLKVE0 = enable;
			break;
		case E_IM_SDRAMC_PORT_VE1:
			IO_SDRAMC[ ch ].CLKENBIFC.bit.CLKVE1 = enable;
			break;
		case E_IM_SDRAMC_PORT_VE2:
			IO_SDRAMC[ ch ].CLKENBIFC.bit.CLKVE2 = enable;
			break;
		case E_IM_SDRAMC_PORT_VD0:
			IO_SDRAMC[ ch ].CLKENBIFC.bit.CLKVD0 = enable;
			break;
		case E_IM_SDRAMC_PORT_VD1:
			IO_SDRAMC[ ch ].CLKENBIFC.bit.CLKVD1 = enable;
			break;
		case E_IM_SDRAMC_PORT_VD2:
			IO_SDRAMC[ ch ].CLKENBIFC.bit.CLKVD2 = enable;
			break;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
		case E_IM_SDRAMC_PORT_VCOREW:	// Write only port.
			if ( access == E_IM_SDRAMC_ACCESS_WRITE ) {
				IO_SDRAMC[ ch ].CLKENBIFA.bit.CLKWVCOREW = enable;
			}
			else {
				IO_SDRAMC[ ch ].CLKENBIFB.bit.CLKRVCOREW = E_IM_SDRAMC_EN_DISABLE;
			}
			break;
		case E_IM_SDRAMC_PORT_VCORER0:
			if ( access == E_IM_SDRAMC_ACCESS_WRITE ) {
				IO_SDRAMC[ ch ].CLKENBIFA.bit.CLKWVCORER0 = enable;
			}
			else {
				IO_SDRAMC[ ch ].CLKENBIFB.bit.CLKRVCORER0 = enable;
			}
			break;
		case E_IM_SDRAMC_PORT_VCORER1:
			if ( access == E_IM_SDRAMC_ACCESS_WRITE ) {
				IO_SDRAMC[ ch ].CLKENBIFA.bit.CLKWVCORER1 = enable;
			}
			else {
				IO_SDRAMC[ ch ].CLKENBIFB.bit.CLKRVCORER1 = enable;
			}
			break;
		case E_IM_SDRAMC_PORT_VD0:
			IO_SDRAMC[ ch ].CLKENBIFC.bit.CLKVD0 = enable;
			break;
		case E_IM_SDRAMC_PORT_VD1:
			IO_SDRAMC[ ch ].CLKENBIFC.bit.CLKVD1 = enable;
			break;
		case E_IM_SDRAMC_PORT_VD2:
			IO_SDRAMC[ ch ].CLKENBIFC.bit.CLKVD2 = enable;
			break;
		case E_IM_SDRAMC_PORT_VCPU:
			if ( access == E_IM_SDRAMC_ACCESS_WRITE ) {
				IO_SDRAMC[ ch ].CLKENBIFA.bit.CLKWVCPU = enable;
			}
			else {
				IO_SDRAMC[ ch ].CLKENBIFB.bit.CLKRVCPU = enable;
			}
			break;
		case E_IM_SDRAMC_PORT_VCOREM:
			IO_SDRAMC[ ch ].CLKENBIFC.bit.CLKVOREM = enable;
			break;
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif	// CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
		default :
			im_sdramc_off_pclk( ch );
			Ddim_Assertion(("im_sdramc_set_clock_enable_busIf() error. [port] = %d\n", port));
			return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}

	im_sdramc_dsb();

	if ( enable == E_IM_SDRAMC_EN_DISABLE ) {

		clkifa = IO_SDRAMC[ ch ].CLKENBIFA.word;
		clkifb = IO_SDRAMC[ ch ].CLKENBIFB.word;
		clkifc = IO_SDRAMC[ ch ].CLKENBIFC.word;

		if ( ( clkifa == 0 ) &&
			 ( clkifb == 0 ) &&
			 ( ( clkifc & 0x3FFC0000 ) == 0 ) ) {
			IO_SDRAMC[ ch ].CLKENBIFC.bit.CLKBIF = E_IM_SDRAMC_EN_DISABLE;
		}

		if ( ( port == E_IM_SDRAMC_PORT_DS0 ) ||
			 ( port == E_IM_SDRAMC_PORT_DS1 ) ) {

			clkds0 = IO_SDRAMC[ ch ].CLKENBIFC.bit.CLKDS0;
			clkds1 = IO_SDRAMC[ ch ].CLKENBIFC.bit.CLKDS1;

			if ( ( clkds0 == E_IM_SDRAMC_EN_DISABLE ) &&
				 ( clkds1 == E_IM_SDRAMC_EN_DISABLE ) ) {
				IO_SDRAMC[ ch ].CLKENBIFC.bit.CLKDSP = E_IM_SDRAMC_EN_DISABLE;
			}
		}
	}

	im_sdramc_off_pclk( ch );
	im_sdramc_dsb();

	return D_DDIM_OK;
}

ImSdramc1 *im_sdramc1_new(void)
{
	ImSdramc1* self = k_object_new(IM_TYPE_SDRAMC1);
	return self;
}



