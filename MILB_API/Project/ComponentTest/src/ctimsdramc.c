/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-03
*@author            :吴雨莎
*@brief             :ctimsdramc
*@rely              :klib
*@function
*设计的主要功能:
*1、
*2、
*3、
*4、
*5、
*@version
*
*/

/**
 * @file		ct_im_sdramc.c
 * @brief		This is ct code for im_sdramc.c.
 * @note		None
 * @attention	None
 *
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */


#include <string.h>
#include <stdlib.h>

//#include "ct_im_sdramc.h"
#include "ctimsdramc.h"
#include "sdramc.h"
#include "im_sdramc.h"
#include "ddim_user_custom.h"

#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
#endif //CO_ACT_CLOCK | CO_ACT_HCLOCK | CO_ACT_PCLOCK


K_TYPE_DEFINE_WITH_PRIVATE(CtImSdramc, ct_im_sdramc)
#define CT_IM_SDRAMC_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), CtImSdramcPrivate, CT_TYPE_IM_SDRAMC))


/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
struct  _CtImSdramcPrivate
{

};


/*
 *DECLS
 */
static void ctSdramcCallback_cb( ULONG intCause );


/*
 *IMPL
 */
static void ct_im_sdramc_constructor(CtImSdramc *self)
{
 //CtImSdramcPrivate *priv = CT_IM_SDRAMC_GET_PRIVATE(self);
}

static void ct_im_sdramc_destructor(CtImSdramc *self)
{
}

/*----------------------------------------------------------------------*/
/* Local Method															*/
/*----------------------------------------------------------------------*/
static void ctSdramcCallback_cb( ULONG intCause )
{
	Ddim_Print(("ctSdramcCallback_cb. intCause=%08lx\n", intCause));
}


/*
 * PUBLIC
 */
/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/
void ct_im_sdramc_1_01( CtImSdramc *self, UCHAR ch )
{
	ImSdramcPortEImSdramcPort port;
	SdramcCmdArbRate arbRate;

	Ddim_Print(("ct_im_sdramc_1_01(test ch=%d)\n", ch));

	for ( port = ImSdramc_E_IM_SDRAMC_PORT_MX10; port < ImSdramc_E_IM_SDRAMC_PORT_MAX; port++ ) {
		arbRate.throughput[ port ] = 0xFFF;
		arbRate.latency[ port ] = 0xFFF;
		arbRate.enable[ port ] = ImSdramc_E_IM_SDRAMC_EN_ENABLE;
	}

	(void)im_sdramc1_set_acceptancecapability( (ImSdramcEImSdramcCh)ch, &arbRate );

	memset( &arbRate, 0, sizeof(arbRate) );

	(void)im_sdramc1_get_acceptancecapability( (ImSdramcEImSdramcCh)ch, &arbRate );

	for ( port = ImSdramc_E_IM_SDRAMC_PORT_MX10; port < ImSdramc_E_IM_SDRAMC_PORT_MAX; port++ ) {
		Ddim_Print( ("arbRate.throughput[%d] = %d\n", port, arbRate.throughput[ port ] ) );
		Ddim_Print( ("arbRate.latency[%d] = %d\n", port, arbRate.latency[ port ] ) );
		Ddim_Print( ("arbRate.enable[%d] = %d\n", port, arbRate.enable[ port ] ) );
	}

	Ddim_Print(("\n"));
	Ddim_Print(("ct_im_sdramc_1_01(reset ch=%d)\n", ch));

	for ( port = ImSdramc_E_IM_SDRAMC_PORT_MX10; port < ImSdramc_E_IM_SDRAMC_PORT_MAX; port++ ) {
		arbRate.throughput[ port ] = 0;
		arbRate.latency[ port ] = 0;
		arbRate.enable[ port ] = ImSdramc_E_IM_SDRAMC_EN_DISABLE;
	}

	(void)im_sdramc1_set_acceptancecapability( (ImSdramcEImSdramcCh)ch, &arbRate );

	memset( &arbRate, 0, sizeof(arbRate) );

	(void)im_sdramc1_get_acceptancecapability( (ImSdramcEImSdramcCh)ch, &arbRate );

	for ( port = ImSdramc_E_IM_SDRAMC_PORT_MX10; port < ImSdramc_E_IM_SDRAMC_PORT_MAX; port++ ) {
		Ddim_Print( ("arbRate.throughput[%d] = %d\n", port, arbRate.throughput[ port ] ) );
		Ddim_Print( ("arbRate.latency[%d] = %d\n", port, arbRate.latency[ port ]    ) );
		Ddim_Print( ("arbRate.enable[%d] = %d\n", port, arbRate.enable[ port ]     ) );
	}

	Ddim_Print(("ct_im_sdramc_1_01 end\n"));
	Ddim_Print(("\n"));
}

void ct_im_sdramc_1_02( CtImSdramc *self, UCHAR ch )
{
	ImSdramcPortEImSdramcPort port;
	SdramcCmdArbPri arbPri;

	Ddim_Print(("ct_im_sdramc_1_02(test ch=%d)\n", ch));

	for ( port = ImSdramc_E_IM_SDRAMC_PORT_MX10; port < ImSdramc_E_IM_SDRAMC_PORT_MAX; port++ ) {
		arbPri.priority[ port ] = 0x1F;
		arbPri.enable[ port ] = ImSdramc_E_IM_SDRAMC_EN_ENABLE;
	}

	(void)im_sdramc1_set_cmd_arbitration_priority( (ImSdramcEImSdramcCh)ch, &arbPri );

	memset( &arbPri, 0, sizeof(arbPri) );

	(void)im_sdramc1_get_cmd_arbitration_priority( (ImSdramcEImSdramcCh)ch, &arbPri );

	for ( port = ImSdramc_E_IM_SDRAMC_PORT_MX10; port < ImSdramc_E_IM_SDRAMC_PORT_MAX; port++ ) {
		Ddim_Print( ("arbPri.priority[%d] = %d\n", port, arbPri.priority[ port ] ) );
		Ddim_Print( ("arbPri.enable[%d] = %d\n", port, arbPri.enable[ port ] ) );
	}

	Ddim_Print(("\n"));
	Ddim_Print(("ct_im_sdramc_1_02(reset ch=%d)\n", ch));

	for ( port = ImSdramc_E_IM_SDRAMC_PORT_MX10; port < ImSdramc_E_IM_SDRAMC_PORT_MAX; port++ ) {
		arbPri.priority[ port ] = 0;
		arbPri.enable[ port ] = ImSdramc_E_IM_SDRAMC_EN_DISABLE;
	}

	(void)im_sdramc1_set_cmd_arbitration_priority( (ImSdramcEImSdramcCh)ch, &arbPri );

	memset( &arbPri, 0, sizeof(arbPri) );

	(void)im_sdramc1_get_cmd_arbitration_priority( (ImSdramcEImSdramcCh)ch, &arbPri );

	for ( port = ImSdramc_E_IM_SDRAMC_PORT_MX10; port < ImSdramc_E_IM_SDRAMC_PORT_MAX; port++ ) {
		Ddim_Print( ("arbPri.priority[%d] = %d\n", port, arbPri.priority[ port ] ) );
		Ddim_Print( ("arbPri.enable[%d]   = %d\n", port, arbPri.enable[ port ] ) );
	}

	Ddim_Print(("ct_im_sdramc_1_02 end\n"));
	Ddim_Print(("\n"));
}

void ct_im_sdramc_1_03( CtImSdramc *self, UCHAR ch )
{
	UCHAR data;
	ImSdramcEImSdramcRank	rank	= ImSdram_E_IM_SDRAMC_RANK_0;

	Ddim_Print(("ct_im_sdramc_1_03(ch=%d)\n", ch));

	IO_SDRAMC[ ch ].UMCMRACSST.bit.MRST = 1;

	(void)im_sdramc1_set_mode_register( (ImSdramcEImSdramcCh)ch, rank, 0, 0xFF );

	(void)im_sdeamc1_get_mode_register( (ImSdramcEImSdramcCh)ch, rank, 0, &data );

	Ddim_Print( ("data = %d\n", data  ) );

	Ddim_Print(("ct_im_sdramc_1_03 end\n"));
	Ddim_Print(("\n"));
}

void ct_im_sdramc_1_04( CtImSdramc *self, UCHAR ch )
{
	ImSdramcPortEImSdramcPort port;

	Ddim_Print(("ct_im_sdramc_1_04(ch=%d)\n", ch));

	for ( port = ImSdramc_E_IM_SDRAMC_PORT_MX10; port < ImSdramc_E_IM_SDRAMC_PORT_MAX; port++ ) {

		Ddim_Print( ("Bus IF(read %d) on\n", port) );
		(void)im_sdramc1_set_clock_enable_busIf( (ImSdramcEImSdramcCh)ch, port, ImSdramc_E_IM_SDRAMC_ACCESS_READ,
				ImSdramc_E_IM_SDRAMC_EN_ENABLE );

		Ddim_Print( ("Bus IF(read %d) off\n", port) );
		(void)im_sdramc1_set_clock_enable_busIf( (ImSdramcEImSdramcCh)ch, port, ImSdramc_E_IM_SDRAMC_ACCESS_READ,
				ImSdramc_E_IM_SDRAMC_EN_DISABLE );

		Ddim_Print( ("Bus IF(write %d) on\n", port) );
		(void)im_sdramc1_set_clock_enable_busIf( (ImSdramcEImSdramcCh)ch, port, ImSdram_E_IM_SDRAMC_ACCESS_WRITE,
				ImSdramc_E_IM_SDRAMC_EN_ENABLE );

		Ddim_Print( ("Bus IF(write %d) off\n", port) );
		(void)im_sdramc1_set_clock_enable_busIf( (ImSdramcEImSdramcCh)ch, port, ImSdram_E_IM_SDRAMC_ACCESS_WRITE,
				ImSdramc_E_IM_SDRAMC_EN_DISABLE );

	}

	Ddim_Print(("ct_im_sdramc_1_04 end\n"));
	Ddim_Print(("\n"));
}

void ct_im_sdramc_1_05( CtImSdramc *self, UCHAR ch )
{
	ImSdramcEImSdramcDatabuf dbno;

	Ddim_Print(("ct_im_sdramc_1_05(ch=%d)\n", ch));

	for ( dbno = ImSdram_E_IM_SDRAMC_DATABUF_0; dbno < ImSdram_E_IM_SDRAMC_DATABUF_MAX; dbno++ ) {

		Ddim_Print( ("Data buf(%d) on\n", dbno) );
		(void)im_sdramc_set_clock_enable_databuf( (ImSdramcEImSdramcCh)ch, dbno, ImSdramc_E_IM_SDRAMC_EN_ENABLE );

		Ddim_Print( ("Data buf(%d) off\n", dbno) );
		(void)im_sdramc_set_clock_enable_databuf( (ImSdramcEImSdramcCh)ch, dbno, ImSdramc_E_IM_SDRAMC_EN_DISABLE );
	}

	Ddim_Print(("ct_im_sdramc_1_05 end\n"));
	Ddim_Print(("\n"));
}

void ct_im_sdramc_1_06( CtImSdramc *self, UCHAR ch )
{
	Ddim_Print(("ct_im_sdramc_1_06(ch=%d)\n", ch));

//	IO_SDRAMC[ ch ].UMCSPCSTAT.bit.SLFRST = 1;

	Ddim_Print( ("refresh start ch = %d\n", ch) );
	Ddim_Print(("\n"));
	(void)im_sdramc_strat_selfrefresh( (ImSdramcEImSdramcCh)ch );

//	IO_SDRAMC[ ch ].UMCSPCSTAT.bit.SLFRST = 0;

	Ddim_Print( ("refresh stop ch = %d\n", ch) );
	Ddim_Print(("\n"));
	(void)im_sdramc_stop_selfrefresh( (ImSdramcEImSdramcCh)ch );

	Ddim_Print(("ct_im_sdramc_1_06 end\n"));
	Ddim_Print(("\n"));
}

void ct_im_sdramc_1_07( CtImSdramc *self, UCHAR ch )
{
	ImSdramcAccessDetection acsDet;
	ImSdramcEImSdramcArea area = ImSdram_E_IM_SDRAMC_AREA_A;
	ImSdramcPortEImSdramcPort port;
	ULONG addr;

	Ddim_Print(("ct_im_sdramc_1_07(ch=%d)\n", ch));

	Ddim_Print( ("ch   = %d\n", ch  ) );
	Ddim_Print( ("area = %d\n", area) );
	Ddim_Print( ("Access detection start\n") );
	Ddim_Print(("\n"));

	acsDet.sAddr = 0x48000000;
	acsDet.eAddr = 0x49000000;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	acsDet.wPort = 1;
	acsDet.rPort = 2;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	acsDet.wPortL	= 1;
	acsDet.rPortL	= 2;
	acsDet.wPortU	= 1;
	acsDet.rPortU	= 2;
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif	// CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	acsDet.pCallBack	= (TImSdramcCallback)ctSdramcCallback_cb;

	(void)im_sdramc_start_access_detection( (ImSdramcEImSdramcCh)ch, area, &acsDet );

	Ddim_Print( ("Access detection stop\n") );
	Ddim_Print(("\n"));

	(void)im_sdramc_stop_access_detection( (ImSdramcEImSdramcCh)ch, area );

	(void)im_sdramc_get_access_detection( (ImSdramcEImSdramcCh)ch, &area, &port, &addr );

	Ddim_Print( ("Access detection get\n") );
	Ddim_Print( ("area = %d\n", area) );
	Ddim_Print( ("port = %d\n", port) );
	Ddim_Print( ("addr = 0x%08lx\n", addr) );
	Ddim_Print(("\n"));

	Ddim_Print(("ct_im_sdramc_1_07 end\n"));
	Ddim_Print(("\n"));
}

void ct_im_sdramc_1_08( CtImSdramc *self, UCHAR ch )
{
	ImSdramcEImSdramcMonmode mode = ImSdram_E_IM_SDRAMC_MONMODE_SIZE;
	ImSdramcPortEImSdramcPort port;
	TImSdramcMonitor mon;

	Ddim_Print(("ct_im_sdramc_1_08(ch=%d)\n", ch));

	Ddim_Print( ("ch = %d\n", ch  ) );
	Ddim_Print( ("mode = %d\n", mode) );
	Ddim_Print( ("Monitor start\n") );
	Ddim_Print(("\n"));

	(void)im_sdramc_start_monitor( (ImSdramcEImSdramcCh)ch, mode, TRUE, TRUE, TRUE );

	Ddim_Print( ("ch = %d\n", ch  ) );
	Ddim_Print( ("Monitor stop\n") );
	Ddim_Print(("\n"));

	(void)im_sdramc_stop_monitor( (ImSdramcEImSdramcCh)ch );

	Ddim_Print( ("Monitor get\n") );
	Ddim_Print( ("ch = %d\n", ch  ) );

	memset( &mon, 0, sizeof(mon) );

	(void)im_sdramc_get_monitor( (ImSdramcEImSdramcCh)ch, &mon );

	for ( port = ImSdramc_E_IM_SDRAMC_PORT_MX10; port < ImSdramc_E_IM_SDRAMC_PORT_MAX; port++ ) {
		Ddim_Print( ("mon.data[%d] = %lu\n", port, mon.data[ port ] ) );
	}

	Ddim_Print(("ct_im_sdramc_1_08 end\n"));
	Ddim_Print(("\n"));
}

void ct_im_sdramc_1_09( CtImSdramc *self, UCHAR ch )
{
	ImSdramcEImSdramcMonmode mode = ImSdram_E_IM_SDRAMC_MONMODE_SIZE;
	UCHAR subId;
	ImSdramcMonitorMxic monmxic;

	Ddim_Print(("ct_im_sdramc_1_09(ch=%d)\n", ch));

	Ddim_Print( ("ch = %d\n", ch ) );
	Ddim_Print( ("mode = %d\n", mode) );
	Ddim_Print( ("Monitor for MXIC start\n") );
	Ddim_Print(("\n"));

	(void)im_sdramc_start_monitor_mxic( (ImSdramcEImSdramcCh)ch, mode, TRUE, TRUE, TRUE );

	Ddim_Print( ("ch = %d\n", ch  ) );
	Ddim_Print( ("Monitor for MXIC stop\n") );
	Ddim_Print(("\n"));

	(void)im_sdramc_stop_monitor_mxic( (ImSdramcEImSdramcCh)ch );

	Ddim_Print( ("Monitor for MXIC get\n") );
	Ddim_Print( ("ch = %d\n", ch  ) );

	memset( &monmxic, 0, sizeof(monmxic) );

	(void)im_sdramc_get_monitor_mxic( (ImSdramcEImSdramcCh)ch, &monmxic );

	for ( subId = 0; subId < ImSdram_E_IM_SDRAMC_SUBID_MAX; subId++ ) {
		Ddim_Print( ("monmxic.data[%d] = %lu\n", subId, monmxic.data[ subId ] ) );
	}

	Ddim_Print(("ct_im_sdramc_1_09 end\n"));
	Ddim_Print(("\n"));
}

void ct_im_sdramc_1_10( CtImSdramc *self, UCHAR ch )
{
	Ddim_Print(("ct_im_sdramc_1_10(ch=%d)\n", ch));

	Ddim_Print( (" manual mode start\n") );
	Ddim_Print(("\n"));
	(void)im_sdramc_start_manualmode( (ImSdramcEImSdramcCh)ch );

	Ddim_Print( ("manual mode stop\n") );
	Ddim_Print(("\n"));
	(void)im_sdramc_stop_manualmode( (ImSdramcEImSdramcCh)ch );

	Ddim_Print(("ct_im_sdramc_1_10 end\n"));
	Ddim_Print(("\n"));
}

void ct_im_sdramc_1_11( CtImSdramc *self, UCHAR ch )
{
	Ddim_Print(("ct_im_sdramc_1_11(ch=%d)\n", ch));

	Ddim_Print( (" ReLock_DLL start\n") );
	Ddim_Print(("\n"));
	(void)im_sdramc_relock_dll( (ImSdramcEImSdramcCh)ch );

	Ddim_Print(("ct_im_sdramc_1_11 end\n"));
	Ddim_Print(("\n"));
}

void ct_im_sdramc_1_12( CtImSdramc *self, UCHAR ch )
{
	kint32 ret;

	Ddim_Print(("ct_im_sdramc_1_12(ch=%d)\n", ch));

	Ddim_Print( ("Training1 start\n") );
	Ddim_Print(("\n"));

	ret = im_sdramc_start_training( (ImSdramcEImSdramcCh)ch, ImSdram_E_IM_SDRAMC_TRAINING_MODE_WRITE );

	Ddim_Print( ("Training1 end(ret=%d)\n", ret) );
	Ddim_Print(("\n"));

	Ddim_Print( ("Training2 start\n") );
	Ddim_Print(("\n"));

	ret = im_sdramc_start_training( (ImSdramcEImSdramcCh)ch, ImSdram_E_IM_SDRAMC_TRAINING_MODE_CA );

	Ddim_Print( ("Training2 end(ret=%d)\n", ret) );
	Ddim_Print(("\n"));

	Ddim_Print(("ct_im_sdramc_1_12 end\n"));
	Ddim_Print(("\n"));
}

void ct_im_sdramc_2_01( CtImSdramc *self )
{
	ImSdramcPortEImSdramcPort port;
	SdramcCmdArbRate arbRate;

	for ( port = ImSdramc_E_IM_SDRAMC_PORT_MX10; port < ImSdramc_E_IM_SDRAMC_PORT_MAX; port++ ) {
		arbRate.enable[ port ] = ImSdramc_E_IM_SDRAMC_EN_ENABLE;
	}

	arbRate.enable[ 10 ] = (ImSdram_E_IM_SDRAMC_EN)2;

	Ddim_Print(("ct_im_sdramc_2_01\n"));

	(void)im_sdramc1_set_acceptancecapability( ImSdram_E_IM_SDRAMC_CH_0, NULL );
	(void)im_sdramc1_set_acceptancecapability( ImSdram_E_IM_SDRAMC_CH_MAX, NULL );
	(void)im_sdramc1_set_acceptancecapability( ImSdram_E_IM_SDRAMC_CH_0, &arbRate );

	Ddim_Print(("\n"));
}

void ct_im_sdramc_2_02( CtImSdramc *self )
{
	Ddim_Print(("ct_im_sdramc_2_02\n"));

	(void)im_sdramc1_get_acceptancecapability( ImSdram_E_IM_SDRAMC_CH_0, NULL );
	(void)im_sdramc1_get_acceptancecapability( ImSdram_E_IM_SDRAMC_CH_MAX, NULL );

	Ddim_Print(("\n"));
}

void ct_im_sdramc_2_03( CtImSdramc *self )
{
	ImSdramcPortEImSdramcPort port;
	SdramcCmdArbPri arbPri;

	for ( port = ImSdramc_E_IM_SDRAMC_PORT_MX10; port < ImSdramc_E_IM_SDRAMC_PORT_MAX; port++ ) {
		arbPri.enable[ port ] = ImSdramc_E_IM_SDRAMC_EN_ENABLE;
	}
	arbPri.enable[ 11 ] = (ImSdram_E_IM_SDRAMC_EN)2;

	Ddim_Print(("ct_im_sdramc_2_03\n"));

	(void)im_sdramc1_set_cmd_arbitration_priority( ImSdram_E_IM_SDRAMC_CH_0, NULL );
	(void)im_sdramc1_set_cmd_arbitration_priority( ImSdram_E_IM_SDRAMC_CH_MAX, NULL );
	(void)im_sdramc1_set_cmd_arbitration_priority( ImSdram_E_IM_SDRAMC_CH_0, &arbPri );

	Ddim_Print(("\n"));
}

void ct_im_sdramc_2_04( CtImSdramc *self )
{
	Ddim_Print(("ct_im_sdramc_2_04\n"));

	(void)im_sdramc1_get_cmd_arbitration_priority( ImSdram_E_IM_SDRAMC_CH_0,   NULL );
	(void)im_sdramc1_get_cmd_arbitration_priority( ImSdram_E_IM_SDRAMC_CH_MAX, NULL );

	Ddim_Print(("\n"));
}

void ct_im_sdramc_2_05( CtImSdramc *self )
{
	Ddim_Print(("ct_im_sdramc_2_05\n"));

	(void)im_sdramc1_set_clock_enable_busIf( ImSdram_E_IM_SDRAMC_CH_MAX, ImSdramc_E_IM_SDRAMC_PORT_MX10,
			ImSdram_E_IM_SDRAMC_ACCESS_WRITE, ImSdramc_E_IM_SDRAMC_EN_ENABLE );
	(void)im_sdramc1_set_clock_enable_busIf( ImSdram_E_IM_SDRAMC_CH_0, ImSdramc_E_IM_SDRAMC_PORT_MAX,
			ImSdram_E_IM_SDRAMC_ACCESS_WRITE, ImSdramc_E_IM_SDRAMC_EN_ENABLE );
	(void)im_sdramc1_set_clock_enable_busIf( ImSdram_E_IM_SDRAMC_CH_0, ImSdramc_E_IM_SDRAMC_PORT_MX10,
			(ImSdramcEImSdramcAccess)2, ImSdramc_E_IM_SDRAMC_EN_ENABLE );
	(void)im_sdramc1_set_clock_enable_busIf( ImSdram_E_IM_SDRAMC_CH_0, ImSdramc_E_IM_SDRAMC_PORT_MX10,
			ImSdram_E_IM_SDRAMC_ACCESS_WRITE, (ImSdram_E_IM_SDRAMC_EN)2 );

	Ddim_Print(("\n"));
}

void ct_im_sdramc_2_06( CtImSdramc *self )
{
	Ddim_Print(("ct_im_sdramc_2_06\n"));

	(void)im_sdramc_set_clock_enable_databuf( ImSdram_E_IM_SDRAMC_CH_MAX, ImSdram_E_IM_SDRAMC_DATABUF_0,
			ImSdramc_E_IM_SDRAMC_EN_ENABLE );
	(void)im_sdramc_set_clock_enable_databuf( ImSdram_E_IM_SDRAMC_CH_0, ImSdram_E_IM_SDRAMC_DATABUF_MAX,
			ImSdramc_E_IM_SDRAMC_EN_ENABLE );
	(void)im_sdramc_set_clock_enable_databuf( ImSdram_E_IM_SDRAMC_CH_0, ImSdram_E_IM_SDRAMC_DATABUF_0,
			(ImSdram_E_IM_SDRAMC_EN)2 );

	Ddim_Print(("\n"));
}

void ct_im_sdramc_2_07( CtImSdramc *self )
{
	Ddim_Print(("ct_im_sdramc_2_07\n"));

	(void)im_sdramc1_set_mode_register( ImSdram_E_IM_SDRAMC_CH_MAX, ImSdram_E_IM_SDRAMC_RANK_0,  0xFF, 0xFF );
	(void)im_sdramc1_set_mode_register( ImSdram_E_IM_SDRAMC_CH_0,   (ImSdramcEImSdramcRank)3, 0xFF, 0xFF );

	Ddim_Print(("\n"));
}

void ct_im_sdramc_2_08( CtImSdramc *self )
{
	UCHAR data;

	Ddim_Print(("ct_im_sdramc_2_08\n"));

	(void)im_sdeamc1_get_mode_register( ImSdram_E_IM_SDRAMC_CH_MAX, ImSdram_E_IM_SDRAMC_RANK_0, 0xFF, &data );
	(void)im_sdeamc1_get_mode_register( ImSdram_E_IM_SDRAMC_CH_0, (ImSdramcEImSdramcRank)3, 0xFF, &data );
	(void)im_sdeamc1_get_mode_register( ImSdram_E_IM_SDRAMC_CH_0, ImSdram_E_IM_SDRAMC_RANK_0, 0xFF, NULL );

	Ddim_Print(("\n"));
}

void ct_im_sdramc_2_09( CtImSdramc *self )
{
	Ddim_Print(("ct_im_sdramc_2_09\n"));

	(void)im_sdramc_strat_selfrefresh( ImSdram_E_IM_SDRAMC_CH_MAX );

	Ddim_Print(("\n"));
}

void ct_im_sdramc_2_10( CtImSdramc *self )
{
	Ddim_Print(("ct_im_sdramc_2_10\n"));

	(void)im_sdramc_stop_selfrefresh( ImSdram_E_IM_SDRAMC_CH_MAX );

	Ddim_Print(("\n"));
}

void ct_im_sdramc_2_11( CtImSdramc *self )
{
	ImSdramcAccessDetection acsDet;

	Ddim_Print(("ct_im_sdramc_2_11\n"));

	acsDet.sAddr = 0x00001000;
	acsDet.eAddr = 0x00002000;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	acsDet.wPort = 1;
	acsDet.rPort	 = 2;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	acsDet.wPortL	= 1;
	acsDet.rPortL = 2;
	acsDet.wPortU = 1;
	acsDet.rPortU	= 2;
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif	// CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	acsDet.pCallBack = ctSdramcCallback_cb;
	(void)im_sdramc_start_access_detection( ImSdram_E_IM_SDRAMC_CH_MAX, ImSdram_E_IM_SDRAMC_AREA_A,  &acsDet );
	(void)im_sdramc_start_access_detection( ImSdram_E_IM_SDRAMC_CH_0, (ImSdramcEImSdramcArea)2, &acsDet );
	(void)im_sdramc_start_access_detection( ImSdram_E_IM_SDRAMC_CH_0, ImSdram_E_IM_SDRAMC_AREA_A, NULL );
	acsDet.eAddr = acsDet.sAddr;
	(void)im_sdramc_start_access_detection( ImSdram_E_IM_SDRAMC_CH_0, ImSdram_E_IM_SDRAMC_AREA_A, &acsDet );

	Ddim_Print(("\n"));
}

void ct_im_sdramc_2_12( CtImSdramc *self )
{
	Ddim_Print(("ct_im_sdramc_2_12\n"));

	(void)im_sdramc_stop_access_detection( ImSdram_E_IM_SDRAMC_CH_MAX, ImSdram_E_IM_SDRAMC_AREA_A );
	(void)im_sdramc_stop_access_detection( ImSdram_E_IM_SDRAMC_CH_0, (ImSdramcEImSdramcArea)2 );

	Ddim_Print(("\n"));
}

void ct_im_sdramc_2_13( CtImSdramc *self )
{
	ImSdramcEImSdramcArea area;
	ImSdramcPortEImSdramcPort port;
	ULONG addr;

	Ddim_Print(("ct_im_sdramc_2_13\n"));

	(void)im_sdramc_get_access_detection( ImSdram_E_IM_SDRAMC_CH_MAX, &area, &port, &addr );
	(void)im_sdramc_get_access_detection( ImSdram_E_IM_SDRAMC_CH_0, NULL,  &port, &addr );
	(void)im_sdramc_get_access_detection( ImSdram_E_IM_SDRAMC_CH_0, &area, NULL, &addr );
	(void)im_sdramc_get_access_detection( ImSdram_E_IM_SDRAMC_CH_0, &area, &port, NULL );

	Ddim_Print(("\n"));
}

void ct_im_sdramc_2_14( CtImSdramc *self )
{
	Ddim_Print(("ct_im_sdramc_2_14\n"));

	(void)im_sdramc_start_monitor( ImSdram_E_IM_SDRAMC_CH_MAX, ImSdram_E_IM_SDRAMC_MONMODE_SIZE, TRUE, TRUE, TRUE );
	(void)im_sdramc_start_monitor( ImSdram_E_IM_SDRAMC_CH_0, (ImSdramcEImSdramcMonmode)2, TRUE, TRUE, TRUE );
	(void)im_sdramc_start_monitor( ImSdram_E_IM_SDRAMC_CH_0, ImSdram_E_IM_SDRAMC_MONMODE_SIZE, 2, TRUE, TRUE );
	(void)im_sdramc_start_monitor( ImSdram_E_IM_SDRAMC_CH_0, ImSdram_E_IM_SDRAMC_MONMODE_SIZE, TRUE, 2, TRUE );
	(void)im_sdramc_start_monitor( ImSdram_E_IM_SDRAMC_CH_0, ImSdram_E_IM_SDRAMC_MONMODE_SIZE, TRUE, TRUE, 2 );

	Ddim_Print(("\n"));
}

void ct_im_sdramc_2_15( CtImSdramc *self )
{
	Ddim_Print(("ct_im_sdramc_2_15\n"));

	(void)im_sdramc_stop_monitor( ImSdram_E_IM_SDRAMC_CH_MAX );

	Ddim_Print(("\n"));
}

void ct_im_sdramc_2_16( CtImSdramc *self )
{
	TImSdramcMonitor mon;

	Ddim_Print(("ct_im_sdramc_2_16\n"));

	(void)im_sdramc_get_monitor( ImSdram_E_IM_SDRAMC_CH_MAX, &mon );
	(void)im_sdramc_get_monitor( ImSdram_E_IM_SDRAMC_CH_0, NULL );

	Ddim_Print(("\n"));
}

void ct_im_sdramc_2_17( CtImSdramc *self )
{
	Ddim_Print(("ct_im_sdramc_2_17\n"));

	(void)im_sdramc_start_monitor_mxic(ImSdram_E_IM_SDRAMC_CH_MAX, ImSdram_E_IM_SDRAMC_MONMODE_SIZE, TRUE, TRUE, TRUE);
	(void)im_sdramc_start_monitor_mxic(ImSdram_E_IM_SDRAMC_CH_0, (ImSdramcEImSdramcMonmode)2, TRUE, TRUE, TRUE);
	(void)im_sdramc_start_monitor_mxic(ImSdram_E_IM_SDRAMC_CH_0, ImSdram_E_IM_SDRAMC_MONMODE_SIZE, 2, TRUE, TRUE);
	(void)im_sdramc_start_monitor_mxic(ImSdram_E_IM_SDRAMC_CH_0, ImSdram_E_IM_SDRAMC_MONMODE_SIZE, TRUE, 2, TRUE);
	(void)im_sdramc_start_monitor_mxic(ImSdram_E_IM_SDRAMC_CH_0, ImSdram_E_IM_SDRAMC_MONMODE_SIZE, TRUE, TRUE, 2);

	Ddim_Print(("\n"));
}

void ct_im_sdramc_2_18( CtImSdramc *self )
{
	Ddim_Print(("ct_im_sdramc_2_18\n"));

	(void)im_sdramc_stop_monitor_mxic( ImSdram_E_IM_SDRAMC_CH_MAX );

	Ddim_Print(("\n"));
}

void ct_im_sdramc_2_19( CtImSdramc *self )
{
	ImSdramcMonitorMxic monmxic;

	Ddim_Print(("ct_im_sdramc_2_19\n"));

	(void)im_sdramc_get_monitor_mxic( ImSdram_E_IM_SDRAMC_CH_MAX, &monmxic );
	(void)im_sdramc_get_monitor_mxic( ImSdram_E_IM_SDRAMC_CH_0, NULL );

	Ddim_Print(("\n"));
}

/**
 * @brief       Command processing of SDRAM control.
 * @param[in]   kint32 argc
 * @param[in]   CHAR** argv
 *
 *	The meaning of parameters
 *	+----------+---------+--------+-------+-------+-------+-----------------------------------------------------+
 *	| P1       | P2      | P4     | P5    | P6    | P7    | Meaning                                             |
 *	+----------+---------+--------+-------+-------+-------+-----------------------------------------------------+
 *	| set      | arbrate | ch     | test  |       |       | Set command arbitration (rate control) for test     |
 *	|          |         |        |       |       |       | im_sdramc1_set_acceptancecapability()                |
 *	|          +         +        +-------+-------+-------+-----------------------------------------------------+
 *	|          |         |        | reset |       |       | Reset command arbitration (rate control)            |
 *	|          |         |        |       |       |       | im_sdramc1_set_acceptancecapability()                |
 *	|          +---------+--------+-------+-------+-------+-----------------------------------------------------+
 *	|          | arbpri  | ch     | test  |       |       | Set command arbitration (priority control) for test |
 *	|          |         |        |       |       |       | im_sdramc1_set_cmd_arbitration_priority()            |
 *	|          +         +        +-------+-------+-------+-----------------------------------------------------+
 *	|          |         |        | reset |       |       | Reset command arbitration (priority control)        |
 *	|          |         |        |       |       |       | im_sdramc1_set_cmd_arbitration_priority()            |
 *	|          +---------+--------+-------+-------+-------+-----------------------------------------------------+
 *	|          | mode    | ch     | rank  | ma    |       | Set mode register                                   |
 *	|          |         |        |       |       |       | im_sdramc1_set_mode_register()                       |
 *	|          +---------+--------+-------+-------+-------+-----------------------------------------------------+
 *	|          | clkbus  | ch     | port  | access| on    | BusIF clock enable                                  |
 *	|          |         |        |       |       |       | im_sdramc1_set_clock_enable_busIf()                  |
 *	|          |         +        +       +       +-------+-----------------------------------------------------+
 *	|          |         |        |       |       | off   | BusIF clock disable                                 |
 *	|          |         |        |       |       |       | im_sdramc1_set_clock_enable_busIf()                  |
 *	|          |---------+--------+-------+-------+-------+-----------------------------------------------------+
 *	|          | clkdat  | ch     | dbno  | on    |       | Data buffer clock enable                            |
 *	|          |         |        |       |       |       | im_sdramc_set_clock_enable_databuf()                |
 *	|          |         +        +       +-------+-------+-----------------------------------------------------+
 *	|          |         |        |       | off   |       | Data buffer clock disable                           |
 *	|          |         |        |       |       |       | im_sdramc_set_clock_enable_databuf()                |
 *	|----------+---------+--------+-------+-------+-------+-----------------------------------------------------+
 *	| get      | arbrate | ch     |       |       |       | Get command arbitration (rate control)              |
 *	|          |         |        |       |       |       | im_sdramc1_get_acceptancecapability()                |
 *	|          +---------+--------+-------+-------+-------+-----------------------------------------------------+
 *	|          | arbpri  | ch     |       |       |       | Get command arbitration (priority control)          |
 *	|          |         |        |       |       |       | im_sdramc1_get_cmd_arbitration_priority()            |
 *	|          +---------+--------+-------+-------+-------+-----------------------------------------------------+
 *	|          | mode    | ch     | rank  | ma    |       | Get mode register                                   |
 *	|          |         |        |       |       |       | im_sdeamc1_get_mode_register()                       |
 *	|----------+---------+--------+-------+-------+-------+-----------------------------------------------------+
 *	| refresh  | start   | ch     |       |       |       | Self refresh mode start                             |
 *	|          |         |        |       |       |       | im_sdramc_strat_selfrefresh()                       |
 *	|          +---------+--------+-------+-------+-------+-----------------------------------------------------+
 *	|          | stop    | ch     |       |       |       | Self refresh mode stop                              |
 *	|          |         |        |       |       |       | im_sdramc_stop_selfrefresh()                        |
 *	|----------+---------+--------+-------+-------+-------+-----------------------------------------------------+
 *	| detect   | start   | ch     | area  |       |       | Access detection start                              |
 *	|          |         |        |       |       |       | im_sdramc_start_access_detection()                  |
 *	|          +---------+--------+-------+-------+-------+-----------------------------------------------------+
 *	|          | stop    | ch     | area  |       |       | Access detection stop                               |
 *	|          |         |        |       |       |       | im_sdramc_stop_access_detection()                   |
 *	|          +---------+--------+-------+-------+-------+-----------------------------------------------------+
 *	|          | get     | ch     |       |       |       | Get access detection                                |
 *	|          |         |        |       |       |       | im_sdramc_get_access_detection()                    |
 *	+----------+---------+--------+-------+-------+-------+-----------------------------------------------------+
 *	| mon      | start   | ch     | mode  | write | read  | Monitor start                                       |
 *	|          |         |        |       |       |       | im_sdramc_start_monitor()                           |
 *	|          +---------+--------+-------+-------+-------+-----------------------------------------------------+
 *	|          | stop    | ch     |       |       |       | Monitor stop                                        |
 *	|          |         |        |       |       |       | im_sdramc_stop_monitor()                            |
 *	|          +---------+--------+-------+-------+-------+-----------------------------------------------------+
 *	|          | get     | ch     |       |       |       | Get access monitor                                  |
 *	|          |         |        |       |       |       | im_sdramc_get_monitor()                             |
 *	+----------+---------+--------+-------+-------+-------+-----------------------------------------------------+
 *	| monmxic  | start   | ch     | mode  | write | read  | Monitor for MXIC start                              |
 *	|          |         |        |       |       |       | im_sdramc_start_monitor_mxic()                      |
 *	|          +---------+--------+-------+-------+-------+-----------------------------------------------------+
 *	|          | stop    | ch     |       |       |       | Monitor for MXIC stop                               |
 *	|          |         |        |       |       |       | im_sdramc_stop_monitor_mxic()                       |
 *	|          +---------+--------+-------+-------+-------+-----------------------------------------------------+
 *	|          | get     | ch     |       |       |       | Get access monitor for MXIC                         |
 *	|          |         |        |       |       |       | im_sdramc_get_monitor_mxic()                        |
 *	+----------+---------+--------+-------+-------+-------+-----------------------------------------------------+
 *	| manual   | start   | ch     |       |       |       | manual mode start                                   |
 *	|          |         |        |       |       |       | im_sdramc_start_manualmode()                        |
 *	|          +---------+--------+-------+-------+-------+-----------------------------------------------------+
 *	|          | stop    | ch     |       |       |       | manual mode stop                                    |
 *	|          |         |        |       |       |       | im_sdramc_stop_manualmode()                         |
 *	+----------+---------+--------+-------+-------+-------+-----------------------------------------------------+
 *	| relock   | ch      |        |       |       |       | Relock dll                                          |
 *	|          |         |        |       |       |       | im_sdramc_relock_dll()                              |
 *	+----------+---------+--------+-------+-------+-------+-----------------------------------------------------+
 *	| training | ch      | mode   |       |       |       | Training startt                                     |
 *	|          |         |        |       |       |       | im_sdramc_start_training()                          |
 *	+----------+---------+--------+-------+-------+-------+-----------------------------------------------------+
 *	| err      | arbrate | set    |       |       |       | im_sdramc1_set_acceptancecapability()                |
 *	|          |         +--------+-------+-------+-------+-----------------------------------------------------+
 *	|          |         | get    |       |       |       | im_sdramc1_get_acceptancecapability()                |
 *	|          +---------+--------+-------+-------+-------+-----------------------------------------------------+
 *	|          | arbpri  | set    |       |       |       | im_sdramc1_set_cmd_arbitration_priority()            |
 *	|          |         +--------+-------+-------+-------+-----------------------------------------------------+
 *	|          |         | get    |       |       |       | im_sdramc1_get_cmd_arbitration_priority()            |
 *	|          +---------+--------+-------+-------+-------+-----------------------------------------------------+
 *	|          | clkbus  | set    |       |       |       | im_sdramc1_set_clock_enable_busIf()                  |
 *	|          |---------+--------+-------+-------+-------+-----------------------------------------------------+
 *	|          | clkdat  | set    |       |       |       | im_sdramc_set_clock_enable_databuf()                |
 *	|          +---------+--------+-------+-------+-------+-----------------------------------------------------+
 *	|          | mode    | set    |       |       |       | im_sdramc1_set_mode_register()                       |
 *	|          |         +--------+-------+-------+-------+-----------------------------------------------------+
 *	|          |         | get    |       |       |       | im_sdeamc1_get_mode_register()                       |
 *	|          +---------+--------+-------+-------+-------+-----------------------------------------------------+
 *	|          | refresh | start  |       |       |       | im_sdramc_strat_selfrefresh()                       |
 *	|          |         +--------+-------+-------+-------+-----------------------------------------------------+
 *	|          |         | stop   |       |       |       | im_sdramc_stop_selfrefresh()                        |
 *	|          |---------+--------+-------+-------+-------+-----------------------------------------------------+
 *	|          | detect  | start  |       |       |       | im_sdramc_start_access_detection()                  |
 *	|          |         +--------+-------+-------+-------+-----------------------------------------------------+
 *	|          |         | stop   |       |       |       | im_sdramc_stop_access_detection()                   |
 *	|          |         +--------+-------+-------+-------+-----------------------------------------------------+
 *	|          |         | get    |       |       |       | im_sdramc_get_access_detection()                    |
 *	|          |---------+--------+-------+-------+-------+-----------------------------------------------------+
 *	|          | mon     | start  |       |       |       | im_sdramc_start_monitor()                           |
 *	|          |         +--------+-------+-------+-------+-----------------------------------------------------+
 *	|          |         | stop   |       |       |       | im_sdramc_stop_monitor()                            |
 *	|          |         +--------+-------+-------+-------+-----------------------------------------------------+
 *	|          |         | get    |       |       |       | im_sdramc_get_monitor()                             |
 *	|          |---------+--------+-------+-------+-------+-----------------------------------------------------+
 *	|          | monmxic | start  |       |       |       | im_sdramc_start_monitor_mxic()                      |
 *	|          |         +--------+-------+-------+-------+-----------------------------------------------------+
 *	|          |         | stop   |       |       |       | im_sdramc_stop_monitor_mxic()                       |
 *	|          |         +--------+-------+-------+-------+-----------------------------------------------------+
 *	|          |         | get    |       |       |       | im_sdramc_get_monitor_mxic()                        |
 *	|----------+---------+--------+-------+-------+-------+-----------------------------------------------------+
 *
 * @return      void
 */
void ct_im_sdramc_main( CtImSdramc *self, kint32 argc, kchar** argv )
{
	UCHAR ma;
	UCHAR data;
	ULONG addr;
	UCHAR subId;
	ImSdramcEImSdramcCh ch;
	ImSdramcPortEImSdramcPort port;
	ImSdramcEImSdramcRank rank;
	ImSdramcEImSdramcArea area;
	ImSdramcEImSdramcAccess access;
	ImSdramcEImSdramcDatabuf dbno;
	ImSdramcEImSdramcMonmode mode;
	SdramcCmdArbRate arbRate;
	SdramcCmdArbPri arbPri;
	ImSdramcAccessDetection acsDet;
	TImSdramcMonitor mon;
	ImSdramcMonitorMxic monmxic;
	ImSdramcEImSdramcTrainingMode tMode;

	if( strcmp(argv[1], "set") == 0 ) {
		if( strcmp(argv[2], "arbrate") == 0 ) {
			if( strcmp(argv[4], "test") == 0 ) {

				ch = (ImSdramcEImSdramcCh)atoi(argv[3]);
				Ddim_Print( ("ch = %d\n", ch) );

				for ( port = ImSdramc_E_IM_SDRAMC_PORT_MX10; port < ImSdramc_E_IM_SDRAMC_PORT_MAX; port++ ) {
					arbRate.throughput[ port ] = 0xFFF;
					arbRate.latency[ port ] = 0xFFF;
					arbRate.enable[ port ] = ImSdramc_E_IM_SDRAMC_EN_ENABLE;
					Ddim_Print( ("arbRate.throughput[%d] = %d\n", port, arbRate.throughput[ port ] ) );
					Ddim_Print( ("arbRate.latency[%d] = %d\n", port, arbRate.latency[ port ] ) );
					Ddim_Print( ("arbRate.enable[%d] = %d\n", port, arbRate.enable[ port ] ) );
				}

				(void)im_sdramc1_set_acceptancecapability( ch, &arbRate );
			} else if( strcmp(argv[4], "reset") == 0 ) {
				ch = (ImSdramcEImSdramcCh)atoi(argv[3]);
				Ddim_Print( ("ch = %d\n", ch) );

				for ( port = ImSdramc_E_IM_SDRAMC_PORT_MX10; port < ImSdramc_E_IM_SDRAMC_PORT_MAX; port++ ) {
					arbRate.throughput[ port ] = 0;
					arbRate.latency[ port ]	= 0;
					arbRate.enable[ port ] = ImSdramc_E_IM_SDRAMC_EN_DISABLE;
					Ddim_Print( ("arbRate.throughput[%d] = %d\n", port, arbRate.throughput[ port ] ) );
					Ddim_Print( ("arbRate.latency[%d] = %d\n", port, arbRate.latency[ port ] ) );
					Ddim_Print( ("arbRate.enable[%d] = %d\n", port, arbRate.enable[ port ] ) );
				}

				(void)im_sdramc1_set_acceptancecapability( ch, &arbRate );
			} else {
				Ddim_Print( ("please check 4th parameter!\n") );
				return;
			}
		} else if( strcmp(argv[2], "arbpri") == 0 ) {
			if( strcmp(argv[4], "test") == 0 ) {
				ch = (ImSdramcEImSdramcCh)atoi(argv[3]);
				Ddim_Print( ("ch = %d\n", ch) );

				for ( port = ImSdramc_E_IM_SDRAMC_PORT_MX10; port < ImSdramc_E_IM_SDRAMC_PORT_MAX; port++ ) {
					arbPri.priority[ port ] = 0x1F;
					arbPri.enable[ port ] = ImSdramc_E_IM_SDRAMC_EN_ENABLE;
					Ddim_Print( ("arbPri.priority[%d] = %d\n", port, arbPri.priority[ port ] ) );
					Ddim_Print( ("arbPri.enable[%d] = %d\n", port, arbPri.enable[ port ] ) );
				}

				(void)im_sdramc1_set_cmd_arbitration_priority( ch, &arbPri );
			} else if( strcmp(argv[4], "reset") == 0 ) {
				ch = (ImSdramcEImSdramcCh)atoi(argv[3]);
				Ddim_Print( ("ch = %d\n", ch) );

				for ( port = ImSdramc_E_IM_SDRAMC_PORT_MX10; port < ImSdramc_E_IM_SDRAMC_PORT_MAX; port++ ) {
					arbPri.priority[ port ] = 0;
					arbPri.enable[ port ] = ImSdramc_E_IM_SDRAMC_EN_DISABLE;
					Ddim_Print( ("arbPri.priority[%d] = %d\n", port, arbPri.priority[ port ] ) );
					Ddim_Print( ("arbPri.enable[%d]   = %d\n", port, arbPri.enable[ port ] ) );
				}

				(void)im_sdramc1_set_cmd_arbitration_priority( ch, &arbPri );
			} else {
				Ddim_Print( ("please check 4th parameter!\n") );
				return;
			}
		} else if( strcmp(argv[2], "mode") == 0 ) {

			ch = (ImSdramcEImSdramcCh)atoi(argv[3]);
			rank	= (ImSdramcEImSdramcRank)atoi(argv[4]);
			ma = atoi(argv[5]);

			Ddim_Print( ("ch = %d\n", ch ) );
			Ddim_Print( ("rank = %d\n", rank) );
			Ddim_Print( ("ma = %d\n", ma ) );

			(void)im_sdramc1_set_mode_register( ch, rank, ma, 0xFF );
		} else if( strcmp(argv[2], "clkbus") == 0 ) {
			ch = (ImSdramcEImSdramcCh)atoi(argv[3]);
			port	= (ImSdramcPortEImSdramcPort)atoi(argv[4]);
			access	= (ImSdramcEImSdramcAccess)atoi(argv[5]);

			Ddim_Print( ("ch = %d\n", ch  ) );
			Ddim_Print( ("port = %d\n", port) );

			if( strcmp(argv[6], "on") == 0 ) {
				Ddim_Print( ("Bus IF on\n") );
				(void)im_sdramc1_set_clock_enable_busIf( ch, port, access, ImSdramc_E_IM_SDRAMC_EN_ENABLE );
			} else {
				Ddim_Print( ("Bus IF off\n") );
				(void)im_sdramc1_set_clock_enable_busIf( ch, port, access, ImSdramc_E_IM_SDRAMC_EN_DISABLE );
			}
		} else if( strcmp(argv[2], "clkdat") == 0 ) {

			ch = (ImSdramcEImSdramcCh)atoi(argv[3]);
			dbno	= (ImSdramcEImSdramcDatabuf)atoi(argv[4]);

			Ddim_Print( ("ch = %d\n", ch  ) );
			Ddim_Print( ("dbno = %d\n", dbno) );

			if( strcmp(argv[5], "on") == 0 ) {
				Ddim_Print( ("Data buf on\n") );
				(void)im_sdramc_set_clock_enable_databuf( ch, dbno, ImSdramc_E_IM_SDRAMC_EN_ENABLE );
			} else {
				Ddim_Print( ("Data buf off\n") );
				(void)im_sdramc_set_clock_enable_databuf( ch, dbno, ImSdramc_E_IM_SDRAMC_EN_DISABLE );
			}
		} else {
			Ddim_Print( ("please check 2nd parameter!\n") );
			return;
		}
	} else if( strcmp(argv[1], "get") == 0 ) {
		if( strcmp(argv[2], "arbrate") == 0 ) {

			ch = (ImSdramcEImSdramcCh)atoi(argv[3]);
			Ddim_Print( ("ch = %d\n", ch) );

			memset( &arbRate, 0, sizeof(arbRate) );

			(void)im_sdramc1_get_acceptancecapability( ch, &arbRate );

			for ( port = ImSdramc_E_IM_SDRAMC_PORT_MX10; port < ImSdramc_E_IM_SDRAMC_PORT_MAX; port++ ) {
				Ddim_Print( ("arbRate.throughput[%d] = %d\n", port, arbRate.throughput[ port ] ) );
				Ddim_Print( ("arbRate.latency[%d]    = %d\n", port, arbRate.latency[ port ]    ) );
			}
		} else if( strcmp(argv[2], "arbpri") == 0 ) {

			ch = (ImSdramcEImSdramcCh)atoi(argv[3]);
			Ddim_Print( ("ch = %d\n", ch) );

			memset( &arbPri, 0, sizeof(arbPri) );

			(void)im_sdramc1_get_cmd_arbitration_priority( ch, &arbPri );

			for ( port = ImSdramc_E_IM_SDRAMC_PORT_MX10; port < ImSdramc_E_IM_SDRAMC_PORT_MAX; port++ ) {
				Ddim_Print( ("arbPri.priority[%d] = %d\n", port, arbPri.priority[ port ] ) );
			}
		} else if( strcmp(argv[2], "mode") == 0 ) {

			ch = (ImSdramcEImSdramcCh)atoi(argv[3]);
			rank	= (ImSdramcEImSdramcRank)atoi(argv[4]);
			ma = atoi(argv[5]);

			Ddim_Print( ("ch = %d\n", ch  ) );
			Ddim_Print( ("rank = %d\n", rank) );
			Ddim_Print( ("ma = %d\n", ma  ) );

			(void)im_sdeamc1_get_mode_register( ch, rank, ma, &data );

			Ddim_Print( ("data = %d\n", data  ) );
		} else {
			Ddim_Print( ("please check 2nd parameter!\n") );
			return;
		}
	} else if( strcmp(argv[1], "refresh") == 0 ) {
		if( strcmp(argv[2], "start") == 0 ) {
			ch = (ImSdramcEImSdramcCh)atoi(argv[3]);
			Ddim_Print( ("refresh start ch = %d\n", ch) );

			(void)im_sdramc_strat_selfrefresh( ch );
		} else if( strcmp(argv[2], "stop") == 0 ) {
			ch = (ImSdramcEImSdramcCh)atoi(argv[3]);
			Ddim_Print( ("refresh stop ch = %d\n", ch) );

			(void)im_sdramc_stop_selfrefresh( ch );
		} else {
			Ddim_Print( ("please check 2nd parameter!\n") );
			return;
		}
	} else if( strcmp(argv[1], "detect") == 0 ) {
		if( strcmp(argv[2], "start") == 0 ) {
			ch = (ImSdramcEImSdramcCh)atoi(argv[3]);
			area	= (ImSdramcEImSdramcArea)atoi(argv[4]);
			Ddim_Print( ("ch = %d\n", ch ) );
			Ddim_Print( ("area = %d\n", area) );
			Ddim_Print( ("Access detection start\n") );

			acsDet.sAddr = 0x00001000;
			acsDet.eAddr = 0x00002000;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
			acsDet.wPort = 1;
			acsDet.rPort = 2;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
			acsDet.wPortL	= 1;
			acsDet.rPortL	= 2;
			acsDet.wPortU	= 1;
			acsDet.rPortU	= 2;
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif	// CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
			acsDet.pCallBack	= (TImSdramcCallback)ctSdramcCallback_cb;

			(void)im_sdramc_start_access_detection( ch, area, &acsDet );
		} else if( strcmp(argv[2], "stop") == 0 ) {
			ch = (ImSdramcEImSdramcCh)atoi(argv[3]);
			area	= (ImSdramcEImSdramcArea)atoi(argv[4]);
			Ddim_Print( ("ch   = %d\n", ch  ) );
			Ddim_Print( ("area = %d\n", area) );
			Ddim_Print( ("Access detection stop\n") );

			(void)im_sdramc_stop_access_detection( ch, area );
		} else if( strcmp(argv[2], "get") == 0 ) {
			ch = (ImSdramcEImSdramcCh)atoi(argv[3]);
			Ddim_Print( ("ch   = %d\n", ch  ) );

			(void)im_sdramc_get_access_detection( ch, &area, &port, &addr );

			Ddim_Print( ("area = %d\n",      area) );
			Ddim_Print( ("port = %d\n",      port) );
			Ddim_Print( ("addr = 0x%08lx\n", addr) );
			Ddim_Print( ("Access detection get\n") );
		} else {
			Ddim_Print( ("please check 2nd parameter!\n") );
			return;
		}
	} else if( strcmp(argv[1], "mon") == 0 ) {
		if( strcmp(argv[2], "start") == 0 ) {
			ch = (ImSdramcEImSdramcCh)atoi(argv[3]);
			mode	= (ImSdramcEImSdramcMonmode)atoi(argv[4]);
			Ddim_Print( ("ch   = %d\n", ch  ) );
			Ddim_Print( ("mode = %d\n", mode) );
			Ddim_Print( ("Monitor start\n") );

			(void)im_sdramc_start_monitor( ch, mode, TRUE, TRUE, TRUE );
		} else if( strcmp(argv[2], "stop") == 0 ) {

			ch = (ImSdramcEImSdramcCh)atoi(argv[3]);
			Ddim_Print( ("ch   = %d\n", ch  ) );
			Ddim_Print( ("Monitor stop\n") );

			(void)im_sdramc_stop_monitor( ch );
		} else if( strcmp(argv[2], "get") == 0 ) {

			ch = (ImSdramcEImSdramcCh)atoi(argv[3]);
			Ddim_Print( ("ch   = %d\n", ch  ) );
			Ddim_Print( ("Monitor get\n") );

			(void)im_sdramc_get_monitor( ch, &mon );

			for ( port = ImSdramc_E_IM_SDRAMC_PORT_MX10; port < ImSdramc_E_IM_SDRAMC_PORT_MAX; port++ ) {
				Ddim_Print( ("mon.data[%d] = %lu\n", port, mon.data[ port ] ) );
			}
		} else {
			Ddim_Print( ("please check 2nd parameter!\n") );
			return;
		}
	} else if( strcmp(argv[1], "monmxic") == 0 ) {
		if( strcmp(argv[2], "start") == 0 ) {

			ch = (ImSdramcEImSdramcCh)atoi(argv[3]);
			mode = (ImSdramcEImSdramcMonmode)atoi(argv[4]);
			Ddim_Print( ("ch   = %d\n", ch  ) );
			Ddim_Print( ("mode = %d\n", mode) );
			Ddim_Print( ("Monitor for MXIC start\n") );

			(void)im_sdramc_start_monitor_mxic( ch, mode, TRUE, TRUE, TRUE );
		} else if( strcmp(argv[2], "stop") == 0 ) {

			ch = (ImSdramcEImSdramcCh)atoi(argv[3]);
			Ddim_Print( ("ch   = %d\n", ch  ) );
			Ddim_Print( ("Monitor for MXIC stop\n") );

			(void)im_sdramc_stop_monitor_mxic( ch );
		} else if( strcmp(argv[2], "get") == 0 ) {

			ch = (ImSdramcEImSdramcCh)atoi(argv[3]);
			Ddim_Print( ("ch = %d\n", ch  ) );
			Ddim_Print( ("Monitor for MXIC get\n") );

			(void)im_sdramc_get_monitor_mxic( ch, &monmxic );

			for ( subId = 0; subId < ImSdram_E_IM_SDRAMC_SUBID_MAX; subId++ ) {
				Ddim_Print( ("monmxic.data[%d] = %lu\n", subId, monmxic.data[ subId ] ) );
			}
		} else {
			Ddim_Print( ("please check 2nd parameter!\n") );
			return;
		}
	} else if( strcmp(argv[1], "manual") == 0 ) {
		if( strcmp(argv[2], "start") == 0 ) {
			ch = (ImSdramcEImSdramcCh)atoi(argv[3]);
			Ddim_Print( ("ch   = %d\n", ch  ) );
			Ddim_Print( ("Manual mode start\n") );

			(void)im_sdramc_start_manualmode( ch );
		} else if( strcmp(argv[2], "stop") == 0 ) {

			ch = (ImSdramcEImSdramcCh)atoi(argv[3]);
			Ddim_Print( ("ch   = %d\n", ch  ) );
			Ddim_Print( ("Manual mode stop\n") );

			(void)im_sdramc_stop_manualmode( ch );
		} else {
			Ddim_Print( ("please check 2nd parameter!\n") );
			return;
		}
	} else if( strcmp(argv[1], "relock") == 0 ) {
		ch = (ImSdramcEImSdramcCh)atoi(argv[2]);
		Ddim_Print( ("ch   = %d\n", ch  ) );
		Ddim_Print( ("Relock dll\n") );

		(void)im_sdramc_relock_dll( ch );
	} else if( strcmp(argv[1], "training") == 0 ) {
			ch = (ImSdramcEImSdramcCh)atoi(argv[2]);
			tMode	= (ImSdramcEImSdramcTrainingMode)atoi(argv[3]);
			Ddim_Print( ("ch   = %d\n", ch  ) );
			Ddim_Print( ("mode = %d\n", tMode) );
			Ddim_Print( ("Training start\n") );

			(void)im_sdramc_start_training( ch, tMode );
	} else if ( strcmp(argv[1], "err") == 0 ) {
		if ( strcmp(argv[2], "arbrate") == 0 ) {
			if ( strcmp(argv[3], "set") == 0 ) {
				(void)im_sdramc1_set_acceptancecapability( ImSdram_E_IM_SDRAMC_CH_0,   NULL );
				(void)im_sdramc1_set_acceptancecapability( ImSdram_E_IM_SDRAMC_CH_MAX, NULL );
			} else if ( strcmp(argv[3], "get") == 0 ) {
				(void)im_sdramc1_get_acceptancecapability( ImSdram_E_IM_SDRAMC_CH_0,   NULL );
				(void)im_sdramc1_get_acceptancecapability( ImSdram_E_IM_SDRAMC_CH_MAX, NULL );
			} else {
				Ddim_Print( ("please check 3rd parameter!\n") );
			}
		} else if ( strcmp(argv[2], "arbpri") == 0 ) {
			if ( strcmp(argv[3], "set") == 0 ) {
				(void)im_sdramc1_set_cmd_arbitration_priority( ImSdram_E_IM_SDRAMC_CH_0,   NULL );
				(void)im_sdramc1_set_cmd_arbitration_priority( ImSdram_E_IM_SDRAMC_CH_MAX, NULL );
			} else if ( strcmp(argv[3], "get") == 0 ) {
				(void)im_sdramc1_get_cmd_arbitration_priority( ImSdram_E_IM_SDRAMC_CH_0,   NULL );
				(void)im_sdramc1_get_cmd_arbitration_priority( ImSdram_E_IM_SDRAMC_CH_MAX, NULL );
			} else {
				Ddim_Print( ("please check 3rd parameter!\n") );
			}
		} else if ( strcmp(argv[2], "clkbus") == 0 ) {
			if ( strcmp(argv[3], "set") == 0 ) {
				(void)im_sdramc1_set_clock_enable_busIf( ImSdram_E_IM_SDRAMC_CH_MAX, ImSdramc_E_IM_SDRAMC_PORT_MX10,
						ImSdram_E_IM_SDRAMC_ACCESS_WRITE, ImSdramc_E_IM_SDRAMC_EN_ENABLE );
				(void)im_sdramc1_set_clock_enable_busIf( ImSdram_E_IM_SDRAMC_CH_0, ImSdramc_E_IM_SDRAMC_PORT_MAX,
						ImSdram_E_IM_SDRAMC_ACCESS_WRITE, ImSdramc_E_IM_SDRAMC_EN_ENABLE );
				(void)im_sdramc1_set_clock_enable_busIf( ImSdram_E_IM_SDRAMC_CH_0, ImSdramc_E_IM_SDRAMC_PORT_MX10,
						(ImSdramcEImSdramcAccess)2, ImSdramc_E_IM_SDRAMC_EN_ENABLE );
				(void)im_sdramc1_set_clock_enable_busIf( ImSdram_E_IM_SDRAMC_CH_0, ImSdramc_E_IM_SDRAMC_PORT_MX10,
						ImSdram_E_IM_SDRAMC_ACCESS_WRITE, (ImSdram_E_IM_SDRAMC_EN)2 );
			} else {
				Ddim_Print( ("please check 3rd parameter!\n") );
			}
		} else if ( strcmp(argv[2], "clkdat") == 0 ) {
			if ( strcmp(argv[3], "set") == 0 ) {
				(void)im_sdramc_set_clock_enable_databuf( ImSdram_E_IM_SDRAMC_CH_MAX, ImSdram_E_IM_SDRAMC_DATABUF_0,
						ImSdramc_E_IM_SDRAMC_EN_ENABLE );
				(void)im_sdramc_set_clock_enable_databuf( ImSdram_E_IM_SDRAMC_CH_0,
						ImSdram_E_IM_SDRAMC_DATABUF_MAX, ImSdramc_E_IM_SDRAMC_EN_ENABLE );
				(void)im_sdramc_set_clock_enable_databuf( ImSdram_E_IM_SDRAMC_CH_0, ImSdram_E_IM_SDRAMC_DATABUF_0,
						(ImSdram_E_IM_SDRAMC_EN)2 );
			} else {
				Ddim_Print( ("please check 3rd parameter!\n") );
			}
		} else if ( strcmp(argv[2], "mode") == 0 ) {
			if ( strcmp(argv[3], "set") == 0 ) {
				(void)im_sdramc1_set_mode_register(ImSdram_E_IM_SDRAMC_CH_MAX, ImSdram_E_IM_SDRAMC_RANK_0, 0xFF, 0xFF);
				(void)im_sdramc1_set_mode_register(ImSdram_E_IM_SDRAMC_CH_0, (ImSdramcEImSdramcRank)3, 0xFF, 0xFF);
			} else if ( strcmp(argv[3], "get") == 0 ) {
				(void)im_sdeamc1_get_mode_register(ImSdram_E_IM_SDRAMC_CH_MAX, ImSdram_E_IM_SDRAMC_RANK_0, 0xFF, &data);
				(void)im_sdeamc1_get_mode_register(ImSdram_E_IM_SDRAMC_CH_0, (ImSdramcEImSdramcRank)3, 0xFF, &data);
				(void)im_sdeamc1_get_mode_register(ImSdram_E_IM_SDRAMC_CH_0, ImSdram_E_IM_SDRAMC_RANK_0, 0xFF, NULL);
			} else {
				Ddim_Print( ("please check 3rd parameter!\n") );
			}
		} else if ( strcmp(argv[2], "refresh") == 0 ) {
			if ( strcmp(argv[3], "start") == 0 ) {
				(void)im_sdramc_strat_selfrefresh( ImSdram_E_IM_SDRAMC_CH_MAX );
			} else if ( strcmp(argv[3], "stop") == 0 ) {
				(void)im_sdramc_stop_selfrefresh( ImSdram_E_IM_SDRAMC_CH_MAX );
			} else {
				Ddim_Print( ("please check 3rd parameter!\n") );
			}
		} else if ( strcmp(argv[2], "detect") == 0 ) {
			if ( strcmp(argv[3], "start") == 0 ) {
				acsDet.sAddr = 0x00001000;
				acsDet.eAddr = 0x00002000;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
				acsDet.wPort = 1;
				acsDet.rPort = 2;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
				acsDet.wPortL	= 1;
				acsDet.rPortL	= 2;
				acsDet.wPortU	= 1;
				acsDet.rPortU	= 2;
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif	// CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
				acsDet.pCallBack = ctSdramcCallback_cb;
				(void)im_sdramc_start_access_detection( ImSdram_E_IM_SDRAMC_CH_MAX, ImSdram_E_IM_SDRAMC_AREA_A,
						&acsDet );
				(void)im_sdramc_start_access_detection( ImSdram_E_IM_SDRAMC_CH_0, (ImSdramcEImSdramcArea)2, &acsDet );
				(void)im_sdramc_start_access_detection( ImSdram_E_IM_SDRAMC_CH_0, ImSdram_E_IM_SDRAMC_AREA_A, NULL );
				acsDet.eAddr = acsDet.sAddr;
				(void)im_sdramc_start_access_detection(ImSdram_E_IM_SDRAMC_CH_0, ImSdram_E_IM_SDRAMC_AREA_A, &acsDet);
			} else if ( strcmp(argv[3], "stop") == 0 ) {
				(void)im_sdramc_stop_access_detection( ImSdram_E_IM_SDRAMC_CH_MAX, ImSdram_E_IM_SDRAMC_AREA_A );
				(void)im_sdramc_stop_access_detection( ImSdram_E_IM_SDRAMC_CH_0, (ImSdramcEImSdramcArea)2 );
			} else if ( strcmp(argv[3], "get") == 0 ) {
				(void)im_sdramc_get_access_detection( ImSdram_E_IM_SDRAMC_CH_MAX, &area, &port, &addr );
				(void)im_sdramc_get_access_detection( ImSdram_E_IM_SDRAMC_CH_0, NULL,  &port, &addr );
				(void)im_sdramc_get_access_detection( ImSdram_E_IM_SDRAMC_CH_0, &area, NULL, &addr );
				(void)im_sdramc_get_access_detection( ImSdram_E_IM_SDRAMC_CH_0, &area, &port, NULL );
			} else {
				Ddim_Print( ("please check 3rd parameter!\n") );
			}
		} else if ( strcmp(argv[2], "mon") == 0 ) {
			if ( strcmp(argv[3], "start") == 0 ) {
				(void)im_sdramc_start_monitor( ImSdram_E_IM_SDRAMC_CH_MAX, ImSdram_E_IM_SDRAMC_MONMODE_SIZE,
						TRUE, TRUE, TRUE );
				(void)im_sdramc_start_monitor( ImSdram_E_IM_SDRAMC_CH_0, (ImSdramcEImSdramcMonmode)2, TRUE, TRUE,
						TRUE );
				(void)im_sdramc_start_monitor( ImSdram_E_IM_SDRAMC_CH_0, ImSdram_E_IM_SDRAMC_MONMODE_SIZE, 2, TRUE,
						TRUE );
				(void)im_sdramc_start_monitor( ImSdram_E_IM_SDRAMC_CH_0, ImSdram_E_IM_SDRAMC_MONMODE_SIZE, TRUE, 2,
						TRUE );
				(void)im_sdramc_start_monitor( ImSdram_E_IM_SDRAMC_CH_0, ImSdram_E_IM_SDRAMC_MONMODE_SIZE, TRUE, TRUE,
						2 );
			} else if ( strcmp(argv[3], "stop") == 0 ) {
				(void)im_sdramc_stop_monitor( ImSdram_E_IM_SDRAMC_CH_MAX );
			} else if ( strcmp(argv[3], "get") == 0 ) {
				(void)im_sdramc_get_monitor( ImSdram_E_IM_SDRAMC_CH_MAX, &mon );
				(void)im_sdramc_get_monitor( ImSdram_E_IM_SDRAMC_CH_0, NULL );
			} else {
				Ddim_Print( ("please check 3rd parameter!\n") );
			}
		} else if ( strcmp(argv[2], "monmxic") == 0 ) {
			if ( strcmp(argv[3], "start") == 0 ) {
				(void)im_sdramc_start_monitor_mxic( ImSdram_E_IM_SDRAMC_CH_MAX, ImSdram_E_IM_SDRAMC_MONMODE_SIZE, TRUE,
						TRUE, TRUE );
				(void)im_sdramc_start_monitor_mxic( ImSdram_E_IM_SDRAMC_CH_0, (ImSdramcEImSdramcMonmode)2, TRUE, TRUE,
						TRUE );
				(void)im_sdramc_start_monitor_mxic( ImSdram_E_IM_SDRAMC_CH_0, ImSdram_E_IM_SDRAMC_MONMODE_SIZE, 2,
						TRUE, TRUE );
				(void)im_sdramc_start_monitor_mxic( ImSdram_E_IM_SDRAMC_CH_0, ImSdram_E_IM_SDRAMC_MONMODE_SIZE, TRUE,
						2, TRUE );
				(void)im_sdramc_start_monitor_mxic( ImSdram_E_IM_SDRAMC_CH_0, ImSdram_E_IM_SDRAMC_MONMODE_SIZE, TRUE,
						TRUE, 2 );
			} else if ( strcmp(argv[3], "stop") == 0 ) {
				(void)im_sdramc_stop_monitor_mxic( ImSdram_E_IM_SDRAMC_CH_MAX );
			} else if ( strcmp(argv[3], "get") == 0 ) {
				(void)im_sdramc_get_monitor_mxic( ImSdram_E_IM_SDRAMC_CH_MAX, &monmxic );
				(void)im_sdramc_get_monitor_mxic( ImSdram_E_IM_SDRAMC_CH_0, NULL );
			} else {
				Ddim_Print( ("please check 3rd parameter!\n") );
			}
		} else {
			Ddim_Print( ("please check 2nd parameter!\n") );
		}
	} else {
		Ddim_Print( ("please check 1st parameter!\n") );
	}
	return ;
}

CtImSdramc *ct_im_sdramc_new(void)
{
	CtImSdramc *self = k_object_new_with_private(CT_TYPE_IM_SDRAMC, sizeof( CtImSdramcPrivate));
	return self;
}
