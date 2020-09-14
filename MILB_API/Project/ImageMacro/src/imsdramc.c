/*
 * imsdramc.c
 *
 *  Created on: 2020年9月3日
 *      Author: sns
 */

#include "imsdramc.h"
#include "sdramc.h"
//#include "im_sdramc.h"
#include "dd_top.h"
#include "ddim_user_custom.h"

typedef struct _ImSdramcPrivate ImSdramcPrivate;
 struct _ImSdramcPrivate
{
	int a;
};

K_TYPE_DEFINE_DERIVED(ImSdramc, im_sdramc, sizeof(ImSdramcPrivate),K_TYPE_OBJECT)
#define IM_SDRAMC_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImSdramcPrivate, IM_TYPE_SDRAMC))

 static volatile T_IM_SDRAMC_CALLBACK	gIM_SDRAMC_CallBack_Func[ E_IM_SDRAMC_CH_MAX ] = { NULL, NULL };
 static volatile ULONG	gIM_SDRAMC_Spin_Lock __attribute__((section(".LOCK_SECTION"), aligned(64)));

static void im_sdramc_constructor(ImSdramc *self)
{
	//ImSdramcPrivate *priv = IM_SDRAMC_GET_PRIVATE(self);
}

static void im_sdramc_destructor(ImSdramc *self)
{
	//ImSdramcPrivate *priv = IM_SDRAMC_GET_PRIVATE(self);
}

INT32 im_sdramc_set_clock_enable_databuf( E_IM_SDRAMC_CH ch, E_IM_SDRAMC_DATABUF dbno, E_IM_SDRAMC_EN enable )
{
#ifdef CO_PARAM_CHECK
	if ( ch >= E_IM_SDRAMC_CH_MAX ) {
		Ddim_Assertion(("im_sdramc_set_clock_enable_databuf() error. [ch] = %d\n", ch));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	if ( dbno >= E_IM_SDRAMC_DATABUF_MAX ) {
		Ddim_Assertion(("im_sdramc_set_clock_enable_databuf() error. [dbno] = %d\n", dbno));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	if ( enable > E_IM_SDRAMC_EN_ENABLE ) {
		Ddim_Assertion(("im_sdramc_set_clock_enable_databuf() error. [enable] = %d\n", enable));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
#endif

	im_sdramc_on_pclk( ch );
	im_sdramc_dsb();

	switch ( dbno ) {
		// Data buffer 0 (MX10/MX11).
		case E_IM_SDRAMC_DATABUF_0 :
			IO_SDRAMC[ ch ].CLKENDA.bit.CLKB0DA = enable;
			break;
		// Data buffer 1 (MX12/MX13).
		case E_IM_SDRAMC_DATABUF_1 :
			IO_SDRAMC[ ch ].CLKENDA.bit.CLKB1DA = enable;
			break;
		// Data buffer 2 (MX20/MX21).
		case E_IM_SDRAMC_DATABUF_2 :
			IO_SDRAMC[ ch ].CLKENDA.bit.CLKB2DA = enable;
			break;
		// Data buffer 3 (MX22/MX23).
		case E_IM_SDRAMC_DATABUF_3 :
			IO_SDRAMC[ ch ].CLKENDA.bit.CLKB3DA = enable;
			break;
		// Data buffer 4 (MX30/MX31).
		case E_IM_SDRAMC_DATABUF_4 :
			IO_SDRAMC[ ch ].CLKENDA.bit.CLKB4DA = enable;
			break;
		// Data buffer 5 (MX32/MX33).
		case E_IM_SDRAMC_DATABUF_5 :
			IO_SDRAMC[ ch ].CLKENDA.bit.CLKB5DA = enable;
			break;
		// Data buffer 6 (MX50/MX51).
		case E_IM_SDRAMC_DATABUF_6 :
			IO_SDRAMC[ ch ].CLKENDA.bit.CLKB6DA = enable;
			break;
		// Data buffer 7 (MX40).
		case E_IM_SDRAMC_DATABUF_7 :
			IO_SDRAMC[ ch ].CLKENDA.bit.CLKB7DA = enable;
			break;
		// Data buffer 8 (MX00/MX01).
		case E_IM_SDRAMC_DATABUF_8 :
			IO_SDRAMC[ ch ].CLKENDA.bit.CLKB8DA = enable;
			break;
		// Data buffer 9 (MX60).
		case E_IM_SDRAMC_DATABUF_9 :
			IO_SDRAMC[ ch ].CLKENDA.bit.CLKB9DA = enable;
			break;
		// Data buffer 10 (RB0).
		case E_IM_SDRAMC_DATABUF_10 :
			IO_SDRAMC[ ch ].CLKENDA.bit.CLKBADA = enable;
			break;
		// Data buffer 11 (RB1).
		case E_IM_SDRAMC_DATABUF_11 :
			IO_SDRAMC[ ch ].CLKENDA.bit.CLKBBDA = enable;
			break;
		// Data buffer 12 (RB2).
		case E_IM_SDRAMC_DATABUF_12 :
			IO_SDRAMC[ ch ].CLKENDA.bit.CLKBCDA = enable;
			break;
		// Data buffer 13 (DS0/DS1).
		case E_IM_SDRAMC_DATABUF_13 :
			IO_SDRAMC[ ch ].CLKENDA.bit.CLKBDDA = enable;
			break;
		// Data buffer 14 (SDM).
		case E_IM_SDRAMC_DATABUF_14 :
			IO_SDRAMC[ ch ].CLKENDA.bit.CLKBEDA = enable;
			break;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
		// Data buffer 15 (VE0/VE1/VE2).
		case E_IM_SDRAMC_DATABUF_15 :
			IO_SDRAMC[ ch ].CLKENDA.bit.CLKBFDA = enable;
			break;
		// Data buffer 16 (VD0/VD1).
		case E_IM_SDRAMC_DATABUF_16 :
			IO_SDRAMC[ ch ].CLKENDA.bit.CLKB10DA = enable;
			break;
		// Data buffer 17 (VD2).
		case E_IM_SDRAMC_DATABUF_17:
			IO_SDRAMC[ ch ].CLKENDA.bit.CLKDRBDA = enable;
			break;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
		// Data buffer 16 (VD0/VD1).
		case E_IM_SDRAMC_DATABUF_16 :
			IO_SDRAMC[ ch ].CLKENDA.bit.CLKB10DA = enable;
			break;
		// Data buffer 18 (VCPU).
		case E_IM_SDRAMC_DATABUF_18 :
			IO_SDRAMC[ ch ].CLKENDA.bit.CLKB12DA = enable;
			break;
		// Data buffer 19 (VCOREW/VCORER0).
		case E_IM_SDRAMC_DATABUF_19 :
			IO_SDRAMC[ ch ].CLKENDA.bit.CLKB13DA = enable;
			break;
		// Data buffer 20 (VCORER1).
		case E_IM_SDRAMC_DATABUF_20 :
			IO_SDRAMC[ ch ].CLKENDA.bit.CLKB14DA = enable;
			break;
		// Data buffer 21 (VCOREM).
		case E_IM_SDRAMC_DATABUF_21 :
			IO_SDRAMC[ ch ].CLKENDA.bit.CLKB15DA = enable;
			break;
		// Data buffer 22 (VD2).
		case E_IM_SDRAMC_DATABUF_22 :
			IO_SDRAMC[ ch ].CLKENDA.bit.CLKDRBDA = enable;
			break;
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif	// CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
		default :
			im_sdramc_off_pclk( ch );
			Ddim_Assertion(("im_sdramc_set_clock_enable_databuf() error. [dbno] = %d\n", dbno));
			return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}

	im_sdramc_off_pclk( ch );
	im_sdramc_dsb();

	return D_DDIM_OK;
}

INT32 im_sdramc_strat_selfrefresh( E_IM_SDRAMC_CH ch )
{
#ifdef CO_PARAM_CHECK
	if ( ch >= E_IM_SDRAMC_CH_MAX ) {
		Ddim_Assertion(("im_sdramc_strat_selfrefresh() error. [ch] = %d\n", ch));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
#endif

	im_sdramc_on_pclk( ch );
	im_sdramc_dsb();

	if ( IO_SDRAMC[ ch ].UMCSPCSTAT.bit.SLFRST == 0 ) {
		// Self refresh mode start.
		IO_SDRAMC[ ch ].UMCSPCSETA.bit.SRINEN = E_IM_SDRAMC_EN_ENABLE;

		im_sdramc_dsb();

		while( IO_SDRAMC[ ch ].UMCSPCSTAT.bit.SLFRST == 0 ) {
			;	// Do nothing.
		}
	}

	im_sdramc_off_pclk( ch );
	im_sdramc_dsb();

	return D_DDIM_OK;
}

INT32 im_sdramc_stop_selfrefresh( E_IM_SDRAMC_CH ch )
{
#ifdef CO_PARAM_CHECK
	if ( ch >= E_IM_SDRAMC_CH_MAX ) {
		Ddim_Assertion(("im_sdramc_stop_selfrefresh() error. [ch] = %d\n", ch));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
#endif

	im_sdramc_on_pclk( ch );
	im_sdramc_dsb();

	if ( IO_SDRAMC[ ch ].UMCSPCSTAT.bit.SLFRST == 1 ) {
		// Self refresh mode stop.
		IO_SDRAMC[ ch ].UMCSPCSETA.bit.SROUTEN = E_IM_SDRAMC_EN_ENABLE;

		im_sdramc_dsb();

		while( IO_SDRAMC[ ch ].UMCSPCSTAT.bit.SLFRST == 1 ) {
			;	// Do nothing.
		}
	}

	im_sdramc_off_pclk( ch );
	im_sdramc_dsb();

	return D_DDIM_OK;
}

INT32 im_sdramc_start_manualmode( E_IM_SDRAMC_CH ch )
{
	union io_sdramc_umcdfictla umcdfictla;

#ifdef CO_PARAM_CHECK
	if ( ch >= E_IM_SDRAMC_CH_MAX ) {
		Ddim_Assertion(("im_sdramc_start_manualmode() error. [ch] = %d\n", ch));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
#endif

	im_sdramc_on_pclk( ch );
	im_sdramc_dsb();

	umcdfictla.word				= 0;
	umcdfictla.bit.LPCTLMD		= 1;
	umcdfictla.bit.LPREQ_DQDQS	= 1;
	umcdfictla.bit.LPREQ_CACK	= 1;

	IO_SDRAMC[ ch ].UMCDFICTLA.word				= umcdfictla.word;
	IO_SDRAMC[ ch ].UMCDFICTLA.bit.LPREQ_CACK	= 0;
	IO_SDRAMC[ ch ].UMCDFICTLA.bit.LPREQ_DQDQS	= 0;

	im_sdramc_off_pclk( ch );
	im_sdramc_dsb();

	return D_DDIM_OK;
}

INT32 im_sdramc_stop_manualmode( E_IM_SDRAMC_CH ch )
{
#ifdef CO_PARAM_CHECK
	if ( ch >= E_IM_SDRAMC_CH_MAX ) {
		Ddim_Assertion(("im_sdramc_stop_manualmode() error. [ch] = %d\n", ch));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
#endif

	im_sdramc_on_pclk( ch );
	im_sdramc_dsb();

	IO_SDRAMC[ ch ].UMCDFICTLA.bit.LPREQ_DQDQS	= 1;
	IO_SDRAMC[ ch ].UMCDFICTLA.bit.LPREQ_CACK	= 1;
	IO_SDRAMC[ ch ].UMCDFICTLA.bit.LPCTLMD		= 0;

	im_sdramc_off_pclk( ch );
	im_sdramc_dsb();

	return D_DDIM_OK;
}

INT32 im_sdramc_relock_dll( E_IM_SDRAMC_CH ch )
{
	union io_sdramc_umcphya umcphya;

#ifdef CO_PARAM_CHECK
	if ( ch >= E_IM_SDRAMC_CH_MAX ) {
		Ddim_Assertion(("im_sdramc_relock_dll() error. [ch] = %d\n", ch));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
#endif

	im_sdramc_on_pclk( ch );
	im_sdramc_dsb();

	// DDR-PHY IDLLRSTX/ISOFTRSTX reset.
	umcphya.word					= 0;
	umcphya.bit.DLLRSTX_CACK		= 0x0;
	umcphya.bit.DLLRSTX_DQDQS		= 0x0;
	umcphya.bit.SOFTRSTX_CACK		= 0x0;
	umcphya.bit.SOFTRSTX_DQDQS		= 0x0;
	IO_SDRAMC[ ch ].UMCPHYCTLA.word = umcphya.word;

	// DDR-PHY IDLLRSTX release.
	IO_SDRAMC[ ch ].UMCPHYCTLA.bit.DLLRSTX_CACK			= 0x1;
	IO_SDRAMC[ ch ].UMCPHYCTLA.bit.DLLRSTX_DQDQS		= 0x1;

	// wait(tDLL_lock).
	//  333MHz/ 667Mbps:124us.
	//  400MHz/ 800Mbps: 85us.
	//  533MHz/1066Mbps: 48us.
	//  667MHz/1333Mbps: 30us.
	//  800MHz/1600Mbps: 21us.
	// 1066MHz/2133Mbps: 12us.
	im_sdramc_wait_us( 21 );

	// DLL Lock result update.
	IO_SDRAMC[ ch ].UMCPHYCTLB.bit.DLL_INIT_UPD_CACK	= 0x1;
	IO_SDRAMC[ ch ].UMCPHYCTLB.bit.DLL_INIT_UPD_DQDQS	= 0xF;

	// wait(80ns).
	im_sdramc_wait_ns( 80 );

	// DDR-PHY ISOFTRSTX release.
	IO_SDRAMC[ ch ].UMCPHYCTLA.bit.SOFTRSTX_CACK		= 0x1;
	IO_SDRAMC[ ch ].UMCPHYCTLA.bit.SOFTRSTX_DQDQS		= 0xF;

	im_sdramc_off_pclk( ch );
	im_sdramc_dsb();

	return D_DDIM_OK;
}

INT32 im_sdramc_start_training( E_IM_SDRAMC_CH ch, E_IM_SDRAMC_TRAINING_MODE mode )
{
	INT32 ret;

#ifdef CO_PARAM_CHECK
	if ( ch >= E_IM_SDRAMC_CH_MAX ) {
		Ddim_Assertion(("im_sdramc_start_training() error. [ch] = %d\n", ch));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	if ( mode > E_IM_SDRAMC_TRAINING_MODE_CA ) {
		Ddim_Assertion(("im_sdramc_start_training() error. [mode] = %d\n", mode));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
#endif

	im_sdramc_on_pclk( ch );
	im_sdramc_dsb();

	// training start.
	IO_SDRAMC[ ch ].UMCPHYCTLC.bit.ITR_MODE	= mode;
	IO_SDRAMC[ ch ].UMCPHYCTLC.bit.ITR_REQ	= 0x1;

	im_sdramc_dsb();

	// status check.
	while( IO_SDRAMC[ ch ].UMCPHYCTLC.bit.ITR_REQ == 0x1 ) {
		;	// Do nothing.
	}

	// result check.
	if ( IO_SDRAMC[ ch ].UMCPHYCTLC.bit.OTR_RESP == 0x0 ) {
		ret = D_DDIM_OK;
	}
	else {
		ret = D_IM_SDRAMC_NG;
	}

	im_sdramc_off_pclk( ch );
	im_sdramc_dsb();

	return ret;
}

INT32 im_sdramc_start_access_detection( E_IM_SDRAMC_CH ch, E_IM_SDRAMC_AREA area, const T_IM_SDRAMC_ACCESS_DETECTION* const acs_det )
{
	union io_sdramc_umcaccrsa*	umcaccrsa;
	union io_sdramc_umcaccrea*	umcaccrea;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	union io_sdramc_umcwaccst*	umcwaccst;
	union io_sdramc_umcraccst*	umcraccst;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	union io_sdramc_umcwaccst*	umcwaccstl;
	union io_sdramc_umcraccst*	umcraccstl;
	union io_sdramc_umcwaccst*	umcwaccstu;
	union io_sdramc_umcraccst*	umcraccstu;
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif	// CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	union io_sdramc_umcacchk*	umcacchk;
	ULONG						int_mask;

#ifdef CO_PARAM_CHECK
	if ( ch >= E_IM_SDRAMC_CH_MAX ) {
		Ddim_Assertion(("im_sdramc_start_access_detection() error. [ch] = %d\n", ch));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	if ( area > E_IM_SDRAMC_AREA_B ) {
		Ddim_Assertion(("im_sdramc_start_access_detection() error. [area] = %d\n", area));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	if ( acs_det == NULL ) {
		Ddim_Assertion(("im_sdramc_start_access_detection() error. [acs_det] is NULL\n"));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	if ( ( acs_det->s_addr ) >= ( acs_det->e_addr ) ) {
		Ddim_Assertion(("im_sdramc_start_access_detection() error. [s_addr]=0x%08lx >= [e_addr]=0x%08lx\n", acs_det->s_addr, acs_det->e_addr ));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
#endif

	im_sdramc_on_pclk( ch );
	im_sdramc_dsb();

	if ( area == E_IM_SDRAMC_AREA_A ) {
		umcaccrsa	= (union io_sdramc_umcaccrsa*)&IO_SDRAMC[ ch ].UMCACCARSAA;
		umcaccrea	= (union io_sdramc_umcaccrea*)&IO_SDRAMC[ ch ].UMCACCAREAA;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
		umcwaccst	= (union io_sdramc_umcwaccst*)&IO_SDRAMC[ ch ].UMCWACCMSTA;
		umcraccst	= (union io_sdramc_umcraccst*)&IO_SDRAMC[ ch ].UMCRACCMSTA;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
		umcwaccstl	= (union io_sdramc_umcwaccst*)&IO_SDRAMC[ ch ].UMCWACCMSTAL;
		umcraccstl	= (union io_sdramc_umcraccst*)&IO_SDRAMC[ ch ].UMCRACCMSTAL;
		umcwaccstu	= (union io_sdramc_umcwaccst*)&IO_SDRAMC[ ch ].UMCWACCMSTAU;
		umcraccstu	= (union io_sdramc_umcraccst*)&IO_SDRAMC[ ch ].UMCRACCMSTAU;
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif	// CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
		umcacchk	= (union io_sdramc_umcacchk*)&IO_SDRAMC[ ch ].UMCACCCHKA;
	}
	else {
		umcaccrsa	= (union io_sdramc_umcaccrsa*)&IO_SDRAMC[ ch ].UMCACCARSAB;
		umcaccrea	= (union io_sdramc_umcaccrea*)&IO_SDRAMC[ ch ].UMCACCAREAB;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
		umcwaccst	= (union io_sdramc_umcwaccst*)&IO_SDRAMC[ ch ].UMCWACCMSTB;
		umcraccst	= (union io_sdramc_umcraccst*)&IO_SDRAMC[ ch ].UMCRACCMSTB;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
		umcwaccstl	= (union io_sdramc_umcwaccst*)&IO_SDRAMC[ ch ].UMCWACCMSTBL;
		umcraccstl	= (union io_sdramc_umcraccst*)&IO_SDRAMC[ ch ].UMCRACCMSTBL;
		umcwaccstu	= (union io_sdramc_umcwaccst*)&IO_SDRAMC[ ch ].UMCWACCMSTBU;
		umcraccstu	= (union io_sdramc_umcraccst*)&IO_SDRAMC[ ch ].UMCRACCMSTBU;
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif	// CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
		umcacchk	= (union io_sdramc_umcacchk*)&IO_SDRAMC[ ch ].UMCACCCHKB;
	}

	// Access detection address set (Particular area).
	umcaccrsa->bit.STADDR						= ( acs_det->s_addr >> 12 );
	umcaccrea->bit.ENADDR						= ( ( acs_det->e_addr + 1 ) >> 12 );

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	// Access detection port set (Particular area).
	umcwaccst->bit.WMST							= acs_det->w_port;
	umcraccst->bit.RMST							= acs_det->r_port;

	// INT mask setting (Particular area).
	int_mask = ~( acs_det->w_port | acs_det->r_port );
	IO_SDRAMC[ ch ].UMCINTMASKM0.bit.INTMASK	= int_mask;
	IO_SDRAMC[ ch ].UMCINTMASKM0.bit.RESERVED	= 0x3;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	// Access detection port set (Particular area).
	umcwaccstl->bit.WMST						= acs_det->w_port_l;
	umcraccstl->bit.RMST						= acs_det->r_port_l;
	umcwaccstu->bit.WMST						= acs_det->w_port_u;
	umcraccstu->bit.RMST						= acs_det->r_port_u;

	// INT mask setting (Particular area).
	int_mask = ~( acs_det->w_port_l | acs_det->r_port_l );
	IO_SDRAMC[ ch ].UMCINTMASKM0.bit.INTMASK	= int_mask;
	IO_SDRAMC[ ch ].UMCINTMASKM0.bit.RESERVED	= 0x3;

	int_mask = ~( acs_det->w_port_u | acs_det->r_port_u );
	IO_SDRAMC[ ch ].UMCINTMASKM1.bit.INTMASK	= int_mask;
	IO_SDRAMC[ ch ].UMCINTMASKM1.bit.RESERVED	= 0x3;
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif	// CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

	// Access detection setting (Particular area).
	umcacchk->bit.PRCT							= 1;
	umcacchk->bit.BUSERR						= 1;
	umcacchk->bit.INT							= 1;
	umcacchk->bit.CHKEN							= E_IM_SDRAMC_EN_ENABLE;

	// Access detection setting (Non-implementation area).
	IO_SDRAMC[ ch ].UMCOODCHK.bit.PRCT			= 1;
	IO_SDRAMC[ ch ].UMCOODCHK.bit.BUSERR		= 1;
	IO_SDRAMC[ ch ].UMCOODCHK.bit.INT			= 1;
	IO_SDRAMC[ ch ].UMCOODCHK.bit.CHKEN			= E_IM_SDRAMC_EN_ENABLE;

	// User callback set.
	gIM_SDRAMC_CallBack_Func[ ch ]				= acs_det->pCallBack;

	// Int enable.
	IO_SDRAMC[ ch ].IRQEN.bit.IRQEN				= E_IM_SDRAMC_EN_ENABLE;

	im_sdramc_off_pclk( ch );
	im_sdramc_dsb();

	return D_DDIM_OK;
}

INT32 im_sdramc_stop_access_detection( E_IM_SDRAMC_CH ch, E_IM_SDRAMC_AREA area )
{
	union io_sdramc_umcacchk*	umcacchk;

#ifdef CO_PARAM_CHECK
	if ( ch >= E_IM_SDRAMC_CH_MAX ) {
		Ddim_Assertion(("im_sdramc_stop_access_detection() error. [ch] = %d\n", ch));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	if ( area > E_IM_SDRAMC_AREA_B ) {
		Ddim_Assertion(("im_sdramc_stop_access_detection() error. [area] = %d\n", area));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
#endif

	im_sdramc_on_pclk( ch );
	im_sdramc_dsb();

	if ( area == E_IM_SDRAMC_AREA_A ) {
		umcacchk = (union io_sdramc_umcacchk*)&IO_SDRAMC[ ch ].UMCACCCHKA;
	}
	else {
		umcacchk = (union io_sdramc_umcacchk*)&IO_SDRAMC[ ch ].UMCACCCHKB;
	}

	// Int disable.
	IO_SDRAMC[ ch ].IRQEN.bit.IRQEN		= 0;

	// Access detection setting.
	umcacchk->bit.CHKEN					= 0;

	// Access detection setting (Non-implementation area).
	IO_SDRAMC[ ch ].UMCOODCHK.bit.CHKEN	= 0;

	// User callback clear.
	gIM_SDRAMC_CallBack_Func[ ch ]		= NULL;

	im_sdramc_off_pclk( ch );
	im_sdramc_dsb();

	return D_DDIM_OK;
}

INT32 im_sdramc_get_access_detection( E_IM_SDRAMC_CH ch, E_IM_SDRAMC_AREA *area, E_IM_SDRAMC_PORT* port, ULONG* const addr )
{
#ifdef CO_PARAM_CHECK
	if ( ch >= E_IM_SDRAMC_CH_MAX ) {
		Ddim_Assertion(("im_sdramc_get_access_detection() error. [ch] = %d\n", ch));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	if ( area == NULL ) {
		Ddim_Assertion(("im_sdramc_get_access_detection() error. [area] is NULL\n"));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	if ( port == NULL ) {
		Ddim_Assertion(("im_sdramc_get_access_detection() error. [port] is NULL\n"));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	if ( addr == NULL ) {
		Ddim_Assertion(("im_sdramc_get_access_detection() error. [addr] is NULL\n"));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
#endif

	im_sdramc_on_pclk( ch );
	im_sdramc_dsb();

	if ( IO_SDRAMC[ ch ].ACCCHKFLG.bit.ACCCHKFLGA == 1 ) {
		IO_SDRAMC[ ch ].ACCCHKFLGCLR.bit.ACCCHKFLGCLRA = 1;
		*area = E_IM_SDRAMC_AREA_A;
	}
	else if ( IO_SDRAMC[ ch ].ACCCHKFLG.bit.ACCCHKFLGB == 1 ) {
		IO_SDRAMC[ ch ].ACCCHKFLGCLR.bit.ACCCHKFLGCLRB = 1;
		*area = E_IM_SDRAMC_AREA_B;
	}
	else {
#ifdef CO_SDRAMC_DEBUG_PRINT
		Ddim_Print(( "im_sdramc_get_access_detection() ACCCHKFLGA/B off\n" ));
#endif
	}

	*port	= (E_IM_SDRAMC_PORT)IO_SDRAMC[ ch ].ACCCHKLOGA.bit.PORTID;
	*addr	= IO_SDRAMC[ ch ].ACCCHKLOGB.bit.DRMADR;

	im_sdramc_off_pclk( ch );
	im_sdramc_dsb();

	return D_DDIM_OK;
}

INT32 im_sdramc_start_monitor( E_IM_SDRAMC_CH ch, E_IM_SDRAMC_MONMODE mode, BOOL write_access, BOOL read_access, BOOL auto_clear )
{
	UCHAR clkmon;

#ifdef CO_PARAM_CHECK
	if ( ch >= E_IM_SDRAMC_CH_MAX ) {
		Ddim_Assertion(("im_sdramc_start_monitor() error. [ch] = %d\n", ch));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	if ( mode > E_IM_SDRAMC_MONMODE_COUNT ) {
		Ddim_Assertion(("im_sdramc_start_monitor() error. [mode] = %d\n", mode));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	if ( write_access > TRUE ) {
		Ddim_Assertion(("im_sdramc_start_monitor() error. [write_access] = %d\n", write_access));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	if ( read_access > TRUE ) {
		Ddim_Assertion(("im_sdramc_start_monitor() error. [read_access] = %d\n", read_access));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	if ( auto_clear > TRUE ) {
		Ddim_Assertion(("im_sdramc_start_monitor() error. [auto_clear] = %d\n", auto_clear));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
#endif

	im_sdramc_on_pclk( ch );
	im_sdramc_dsb();

	clkmon = IO_SDRAMC[ ch ].CLKENMON.bit.CLKMON;

	if ( clkmon == E_IM_SDRAMC_EN_DISABLE ) {
		// Access monitor clock enable.
		IO_SDRAMC[ ch ].CLKENMON.bit.CLKMON					= E_IM_SDRAMC_EN_ENABLE;

		// Access monitor mode set.
		IO_SDRAMC[ ch ].UMCPFMCTL.bit.PFM_MON_CMD			= mode;

		// Access monitor kind set (read/write).
		if ( read_access ) {
			IO_SDRAMC[ ch ].UMCPFMCTL.bit.PFM_MON_R_OFF		= 0;
		}
		else {
			IO_SDRAMC[ ch ].UMCPFMCTL.bit.PFM_MON_R_OFF		= 1;
		}

		if ( write_access ) {
			IO_SDRAMC[ ch ].UMCPFMCTL.bit.PFM_MON_W_OFF		= 0;
		}
		else {
			IO_SDRAMC[ ch ].UMCPFMCTL.bit.PFM_MON_W_OFF		= 1;
		}

		// Status register auto clear.
		IO_SDRAMC[ ch ].UMCPFMCTL.bit.PFM_RST_AFTER_READ	= auto_clear;

		// Status register clear (on).
		IO_SDRAMC[ ch ].UMCPFMCTL.bit.PFM_RST				= 1;

		// Access monitor start.
		IO_SDRAMC[ ch ].UMCPFMCTL.bit.PFM_ON				= 1;
	}

	im_sdramc_off_pclk( ch );
	im_sdramc_dsb();

	return D_DDIM_OK;
}

INT32 im_sdramc_stop_monitor( E_IM_SDRAMC_CH ch )
{
	UCHAR clkmon;

#ifdef CO_PARAM_CHECK
	if ( ch >= E_IM_SDRAMC_CH_MAX ) {
		Ddim_Assertion(("im_sdramc_stop_monitor() error. [ch] = %d\n", ch));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
#endif

	im_sdramc_on_pclk( ch );
	im_sdramc_dsb();

	clkmon = IO_SDRAMC[ ch ].CLKENMON.bit.CLKMON;

	if ( clkmon == E_IM_SDRAMC_EN_ENABLE ) {
		// Access monitor stop.
		IO_SDRAMC[ ch ].UMCPFMCTL.bit.PFM_ON	= 0;

		// Access monitor clock disable.
		IO_SDRAMC[ ch ].CLKENMON.bit.CLKMON		= E_IM_SDRAMC_EN_DISABLE;
	}

	im_sdramc_off_pclk( ch );
	im_sdramc_dsb();

	return D_DDIM_OK;
}

INT32 im_sdramc_get_monitor( E_IM_SDRAMC_CH ch, T_IM_SDRAMC_MONITOR* const mon )
{
	UCHAR port;

#ifdef CO_PARAM_CHECK
	if ( ch >= E_IM_SDRAMC_CH_MAX ) {
		Ddim_Assertion(("im_sdramc_get_monitor() error. [ch] = %d\n", ch));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	if ( mon == NULL ) {
		Ddim_Assertion(("im_sdramc_get_monitor() error. [mon] is null\n"));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
#endif

	im_sdramc_on_pclk( ch );
	im_sdramc_dsb();

	for ( port = 0; port < E_IM_SDRAMC_PORT_MAX; port++ ) {
		mon->data[ port ] = IO_SDRAMC[ ch ].UMCPFMST[ port ].bit.VLDDATA;
	}

	im_sdramc_off_pclk( ch );
	im_sdramc_dsb();

	return D_DDIM_OK;
}

INT32 im_sdramc_start_monitor_mxic( E_IM_SDRAMC_CH ch, E_IM_SDRAMC_MONMODE mode, BOOL write_access, BOOL read_access, BOOL auto_clear )
{
	UCHAR clkmon;

#ifdef CO_PARAM_CHECK
	if ( ch >= E_IM_SDRAMC_CH_MAX ) {
		Ddim_Assertion(("im_sdramc_start_monitor_mxic() error. [ch] = %d\n", ch));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	if ( mode > E_IM_SDRAMC_MONMODE_COUNT ) {
		Ddim_Assertion(("im_sdramc_start_monitor_mxic() error. [mode] = %d\n", mode));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	if ( write_access > TRUE ) {
		Ddim_Assertion(("im_sdramc_start_monitor_mxic() error. [write_access] = %d\n", write_access));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	if ( read_access > TRUE ) {
		Ddim_Assertion(("im_sdramc_start_monitor_mxic() error. [read_access] = %d\n", read_access));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	if ( auto_clear > TRUE ) {
		Ddim_Assertion(("im_sdramc_start_monitor_mxic() error. [auto_clear] = %d\n", auto_clear));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
#endif

	im_sdramc_on_pclk( ch );
	im_sdramc_dsb();

	clkmon = IO_SDRAMC[ ch ].CLKENMON.bit.CLKMON;

	if ( clkmon == E_IM_SDRAMC_EN_DISABLE ) {
		// Access monitor clock enable.
		IO_SDRAMC[ ch ].CLKENMON.bit.CLKMON					= E_IM_SDRAMC_EN_ENABLE;

		// Access monitor mode set.
		IO_SDRAMC[ ch ].UMCMIDPFMCTL.bit.PFM_MON_CMD		= mode;

		// Access monitor kind set (read/write).
		if ( read_access ) {
			IO_SDRAMC[ ch ].UMCMIDPFMCTL.bit.PFM_MON_R_OFF	= 0;
		}
		else {
			IO_SDRAMC[ ch ].UMCMIDPFMCTL.bit.PFM_MON_R_OFF	= 1;
		}

		if ( write_access ) {
			IO_SDRAMC[ ch ].UMCMIDPFMCTL.bit.PFM_MON_W_OFF	= 0;
		}
		else {
			IO_SDRAMC[ ch ].UMCMIDPFMCTL.bit.PFM_MON_W_OFF	= 1;
		}

		// Status register auto clear.
		IO_SDRAMC[ ch ].UMCMIDPFMCTL.bit.PFM_RST_AFTER_READ	= auto_clear;

		// Status register clear (on).
		IO_SDRAMC[ ch ].UMCMIDPFMCTL.bit.PFM_RST			= 1;

		// Access monitor start.
		IO_SDRAMC[ ch ].UMCMIDPFMCTL.bit.PFM_ON				= 1;
	}

	im_sdramc_off_pclk( ch );
	im_sdramc_dsb();

	return D_DDIM_OK;
}

INT32 im_sdramc_stop_monitor_mxic( E_IM_SDRAMC_CH ch )
{
	UCHAR clkmon;

#ifdef CO_PARAM_CHECK
	if ( ch >= E_IM_SDRAMC_CH_MAX ) {
		Ddim_Assertion(("im_sdramc_stop_monitor_mxic() error. [ch] = %d\n", ch));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
#endif

	im_sdramc_on_pclk( ch );
	im_sdramc_dsb();

	clkmon = IO_SDRAMC[ ch ].CLKENMON.bit.CLKMON;

	if ( clkmon == E_IM_SDRAMC_EN_ENABLE ) {
		// Access monitor stop.
		IO_SDRAMC[ ch ].UMCMIDPFMCTL.bit.PFM_ON	= 0;

		// Access monitor clock disable.
		IO_SDRAMC[ ch ].CLKENMON.bit.CLKMON		= E_IM_SDRAMC_EN_DISABLE;
	}

	im_sdramc_off_pclk( ch );
	im_sdramc_dsb();

	return D_DDIM_OK;
}

INT32 im_sdramc_get_monitor_mxic( E_IM_SDRAMC_CH ch, T_IM_SDRAMC_MONITOR_MXIC* const mon )
{
	UCHAR sub_id;

#ifdef CO_PARAM_CHECK
	if ( ch >= E_IM_SDRAMC_CH_MAX ) {
		Ddim_Assertion(("im_sdramc_get_monitor_mxic() error. [ch] = %d\n", ch));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
	if ( mon == NULL ) {
		Ddim_Assertion(("im_sdramc_get_monitor_mxic() error. [mon] is null\n"));
		return D_IM_SDRAMC_INPUT_PARAM_ERROR;
	}
#endif

	im_sdramc_on_pclk( ch );
	im_sdramc_dsb();

	for ( sub_id = 0; sub_id < E_IM_SDRAMC_SUBID_MAX; sub_id++ ) {
		mon->data[ sub_id ] = IO_SDRAMC[ ch ].UMCMIDPFMST[ sub_id ].bit.VLDDATA;
	}

	im_sdramc_off_pclk( ch );
	im_sdramc_dsb();

	return D_DDIM_OK;
}

VOID im_sdramc_int_handler( E_IM_SDRAMC_CH ch )
{
	ULONG int_cause;

	im_sdramc_on_pclk( ch );
	im_sdramc_dsb();

	// Int signal clear.
	IO_SDRAMC[ ch ].IRQCLR.bit.IRQCLR = 1;

	// INTCAUSE get.
	int_cause = IO_SDRAMC[ ch ].UMCINTCAUSEM0.bit.INTCAUSE;

	// INTCAUSE clear.
	IO_SDRAMC[ ch ].UMCINTCAUSEM0.bit.INTCAUSE	= 0x3FFFFFFF;
	IO_SDRAMC[ ch ].UMCINTCAUSEM0.bit.RESERVED	= 0x0;

	im_sdramc_off_pclk( ch );
	im_sdramc_dsb();

	// User callback function.
	if ( gIM_SDRAMC_CallBack_Func[ ch ] != NULL ) {
#ifdef CO_SDRAMC_DEBUG_PRINT
		Ddim_Print(( "im_sdramc_int_handler() begin callback\n" ));
#endif

		gIM_SDRAMC_CallBack_Func[ ch ]( int_cause );

#ifdef CO_SDRAMC_DEBUG_PRINT
		Ddim_Print(( "Im_DRAMC_Int_Handler() end callback\n" ));
#endif
	}
}

ImSdramc *im_sdramc_new(void)
{
	ImSdramc* self = k_object_new(IM_TYPE_SDRAMC);
	return self;
}
