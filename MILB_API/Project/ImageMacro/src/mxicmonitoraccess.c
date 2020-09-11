/***********************************************************************
 * @Copyright(C) 上海网用软件有限公司
 * @file mxicmonitoraccess.c
 * @date 2020-09-02
 * @author: 吴海辉
 * @brief: 
 * @version: 1.0.0
***********************************************************************/

#include "mxicmonitoraccess.h"


K_TYPE_DEFINE_WITH_PRIVATE(MxicMonitorAccess, mxic_monitor_access)
#define MXIC_MONITOR_ACCESS_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), MxicMonitorAccessPrivate, \
											MXIC_TYPE_MONITOR_ACCESS))

// Definition of the monitored range checking.
#define MxicMonitorAccess_CHECK_MASTER_W_MIN		(0x001)
#define MxicMonitorAccess_CHECK_MASTER_W_MAX		(0x043)
#define MxicMonitorAccess_CHECK_MASTER_R_MIN		(0x081)
#define MxicMonitorAccess_CHECK_MASTER_R_MAX		(0x0C3)
#define MxicMonitorAccess_CHECK_SLAVE_W_MIN			(0x104)
#define MxicMonitorAccess_CHECK_SLAVE_W_MAX			(0x10E)
#define MxicMonitorAccess_CHECK_SLAVE_R_MIN			(0x184)
#define MxicMonitorAccess_CHECK_SLAVE_R_MAX			(0x18E)


typedef struct{
	ImMxicWrArbiter wrArbiter; 
	ImMxicSpecArbiter arbiter; 
	ImMxicPort port; 
	ImMxicSlot slot;
}SlotArrayArgs;

struct _MxicMonitorAccessPrivate
{
    MxicUtlis* mxicUtlis;
	// Running state of transfer/access monitor with limit.
	volatile UCHAR gImMxicTransMonLimitEndState;
	// Callback function pointer for transfer/access monitor end by limit.
	volatile VP_CALLBACK gImMxicAcsTransMonLimitEndCallBack;
};


/*----------------------------------------------------------------------*/
/* DECLS  															    */
/*----------------------------------------------------------------------*/
#ifdef CO_PARAM_CHECK
static INT32 imMxicCheckMasterNumberForMonitor( UINT32 master );
#endif // CO_PARAM_CHECK
static INT32 imMxicGetSlotStatusArray( ImMxicUnit unit, volatile struct io_jdsmxic* ioMxic, 
									   SlotArrayArgs args, UCHAR* const slotStatus );


/*----------------------------------------------------------------------*/
/* IMPL  															    */
/*----------------------------------------------------------------------*/
static void mxic_monitor_access_constructor(MxicMonitorAccess *self)
{
    MxicMonitorAccessPrivate *priv = MXIC_MONITOR_ACCESS_GET_PRIVATE(self);

	priv->mxicUtlis = mxic_utlis_new();
	priv->gImMxicTransMonLimitEndState = MxicUtlis_MONITOR_OPERATION_END;
	priv->gImMxicAcsTransMonLimitEndCallBack = NULL;
}

static void mxic_monitor_access_destructor(MxicMonitorAccess *self)
{
	MxicMonitorAccessPrivate *priv = MXIC_MONITOR_ACCESS_GET_PRIVATE(self);
	
	if(priv->mxicUtlis)
	{
		k_object_unref(priv->mxicUtlis);
		priv->mxicUtlis = NULL;
	}
	priv->gImMxicAcsTransMonLimitEndCallBack = NULL;
}

#ifdef CO_PARAM_CHECK
/**
Check master number for monitor function.
@param[in]	master					Channel number.
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
static INT32 imMxicCheckMasterNumberForMonitor( UINT32 master )
{
	// Check whether the specified number is a port number or "no use" number.
	if ( master == MxicUtlis_TARGET_NOTHING ) {
		return D_DDIM_OK;
	}
	if ( ( master >= MxicMonitorAccess_CHECK_MASTER_W_MIN ) && ( master <= MxicMonitorAccess_CHECK_MASTER_W_MAX ) ) {
		return D_DDIM_OK;
	}
	if ( ( master >= MxicMonitorAccess_CHECK_MASTER_R_MIN ) && ( master <= MxicMonitorAccess_CHECK_MASTER_R_MAX ) ) {
		return D_DDIM_OK;
	}
	if ( ( master >= MxicMonitorAccess_CHECK_SLAVE_W_MIN ) && ( master <= MxicMonitorAccess_CHECK_SLAVE_W_MAX ) ) {
		return D_DDIM_OK;
	}
	if ( ( master >= MxicMonitorAccess_CHECK_SLAVE_R_MIN ) && ( master <= MxicMonitorAccess_CHECK_SLAVE_R_MAX ) ) {
		return D_DDIM_OK;
	}

	return MxicUtlis_INPUT_PARAM_ERROR;
}
#endif // CO_PARAM_CHECK

/**
Get slot status of specified slot.
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		ioMxic					MXIC address.<br>
@param[in]		wrArbiter				Write or Read Arbiter.<br>
@param[in]		arbiter					Target arbiter.<br>
@param[in]		port					Target port.<br>
@param[in]		slot					Target slot.<br>
@param[out]		slotStatus				Result of slot status monitor.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
static INT32 imMxicGetSlotStatusArray( ImMxicUnit unit, volatile struct io_jdsmxic* ioMxic, 
									   SlotArrayArgs args, UCHAR* const slotStatus )
{
	INT32 result;

	result = D_DDIM_OK;

	if ( args.wrArbiter == MxicUtlis_WR_ARBITER_W ) {
		// W arbiter.
		if ( unit != MxicUtlis_UNIT_4 ) {
			switch ( args.arbiter ) {
				case MxicUtlis_SPEC_ARBITER_1:
					slotStatus[0] = ioMxic->TSLSW_1[args.port][args.slot].bit.SLOTSW_0;
					slotStatus[1] = ioMxic->TSLSW_1[args.port][args.slot].bit.SLOTSW_1;
					slotStatus[2] = ioMxic->TSLSW_1[args.port][args.slot].bit.SLOTSW_2;
					slotStatus[3] = ioMxic->TSLSW_1[args.port][args.slot].bit.SLOTSW_3;
					slotStatus[4] = ioMxic->TSLSW_1[args.port][args.slot].bit.SLOTSW_4;
					slotStatus[5] = ioMxic->TSLSW_1[args.port][args.slot].bit.SLOTSW_5;
					slotStatus[6] = ioMxic->TSLSW_1[args.port][args.slot].bit.SLOTSW_6;
					slotStatus[7] = ioMxic->TSLSW_1[args.port][args.slot].bit.SLOTSW_7;
					break;
				case MxicUtlis_SPEC_ARBITER_2:
					slotStatus[0] = ioMxic->TSLSW_2[args.port][args.slot].bit.SLOTSW_0;
					slotStatus[1] = ioMxic->TSLSW_2[args.port][args.slot].bit.SLOTSW_1;
					slotStatus[2] = ioMxic->TSLSW_2[args.port][args.slot].bit.SLOTSW_2;
					slotStatus[3] = ioMxic->TSLSW_2[args.port][args.slot].bit.SLOTSW_3;
					slotStatus[4] = ioMxic->TSLSW_2[args.port][args.slot].bit.SLOTSW_4;
					slotStatus[5] = ioMxic->TSLSW_2[args.port][args.slot].bit.SLOTSW_5;
					slotStatus[6] = ioMxic->TSLSW_2[args.port][args.slot].bit.SLOTSW_6;
					slotStatus[7] = ioMxic->TSLSW_2[args.port][args.slot].bit.SLOTSW_7;
					break;
				case MxicUtlis_SPEC_ARBITER_3:
					slotStatus[0] = ioMxic->TSLSW_3[args.port][args.slot].bit.SLOTSW_0;
					slotStatus[1] = ioMxic->TSLSW_3[args.port][args.slot].bit.SLOTSW_1;
					slotStatus[2] = ioMxic->TSLSW_3[args.port][args.slot].bit.SLOTSW_2;
					slotStatus[3] = ioMxic->TSLSW_3[args.port][args.slot].bit.SLOTSW_3;
					slotStatus[4] = ioMxic->TSLSW_3[args.port][args.slot].bit.SLOTSW_4;
					slotStatus[5] = ioMxic->TSLSW_3[args.port][args.slot].bit.SLOTSW_5;
					slotStatus[6] = ioMxic->TSLSW_3[args.port][args.slot].bit.SLOTSW_6;
					slotStatus[7] = ioMxic->TSLSW_3[args.port][args.slot].bit.SLOTSW_7;
					break;
				case MxicUtlis_SPEC_ARBITER_4:
					slotStatus[0] = ioMxic->TSLSW_4[args.port][args.slot].bit.SLOTSW_0;
					slotStatus[1] = ioMxic->TSLSW_4[args.port][args.slot].bit.SLOTSW_1;
					slotStatus[2] = ioMxic->TSLSW_4[args.port][args.slot].bit.SLOTSW_2;
					slotStatus[3] = ioMxic->TSLSW_4[args.port][args.slot].bit.SLOTSW_3;
					slotStatus[4] = ioMxic->TSLSW_4[args.port][args.slot].bit.SLOTSW_4;
					slotStatus[5] = ioMxic->TSLSW_4[args.port][args.slot].bit.SLOTSW_5;
					slotStatus[6] = ioMxic->TSLSW_4[args.port][args.slot].bit.SLOTSW_6;
					slotStatus[7] = ioMxic->TSLSW_4[args.port][args.slot].bit.SLOTSW_7;
					break;
				default:
					// arbiter is illegal.
					result = MxicUtlis_INPUT_PARAM_ERROR;
					Ddim_Print(("E:imMxicGetSlotStatusArray(): arbiter is illegal. arbiter=%d\n", args.arbiter));
					break;
			}
		}
		else {
			slotStatus[0] = 0;
			slotStatus[1] = 0;
			slotStatus[2] = 0;
			slotStatus[3] = 0;
			slotStatus[4] = 0;
			slotStatus[5] = 0;
			slotStatus[6] = 0;
			slotStatus[7] = 0;

			// Unit number is invalid.
//			Ddim_Print(("imMxicGetSlotStatusArray(): unit number is invalid. unit=%d\n", unit));
		}
	}
	else {
		// R arbiter.
		if ( unit != MxicUtlis_UNIT_0 ) {
			switch ( args.arbiter ) {
				case MxicUtlis_SPEC_ARBITER_1:
					slotStatus[0] = ioMxic->TSLSR_1[args.port][args.slot].bit.SLOTSR_0;
					slotStatus[1] = ioMxic->TSLSR_1[args.port][args.slot].bit.SLOTSR_1;
					slotStatus[2] = ioMxic->TSLSR_1[args.port][args.slot].bit.SLOTSR_2;
					slotStatus[3] = ioMxic->TSLSR_1[args.port][args.slot].bit.SLOTSR_3;
					slotStatus[4] = ioMxic->TSLSR_1[args.port][args.slot].bit.SLOTSR_4;
					slotStatus[5] = ioMxic->TSLSR_1[args.port][args.slot].bit.SLOTSR_5;
					slotStatus[6] = ioMxic->TSLSR_1[args.port][args.slot].bit.SLOTSR_6;
					slotStatus[7] = ioMxic->TSLSR_1[args.port][args.slot].bit.SLOTSR_7;
					break;
				case MxicUtlis_SPEC_ARBITER_2:
					slotStatus[0] = ioMxic->TSLSR_2[args.port][args.slot].bit.SLOTSR_0;
					slotStatus[1] = ioMxic->TSLSR_2[args.port][args.slot].bit.SLOTSR_1;
					slotStatus[2] = ioMxic->TSLSR_2[args.port][args.slot].bit.SLOTSR_2;
					slotStatus[3] = ioMxic->TSLSR_2[args.port][args.slot].bit.SLOTSR_3;
					slotStatus[4] = ioMxic->TSLSR_2[args.port][args.slot].bit.SLOTSR_4;
					slotStatus[5] = ioMxic->TSLSR_2[args.port][args.slot].bit.SLOTSR_5;
					slotStatus[6] = ioMxic->TSLSR_2[args.port][args.slot].bit.SLOTSR_6;
					slotStatus[7] = ioMxic->TSLSR_2[args.port][args.slot].bit.SLOTSR_7;
					break;
				case MxicUtlis_SPEC_ARBITER_3:
					slotStatus[0] = ioMxic->TSLSR_3[args.port][args.slot].bit.SLOTSR_0;
					slotStatus[1] = ioMxic->TSLSR_3[args.port][args.slot].bit.SLOTSR_1;
					slotStatus[2] = ioMxic->TSLSR_3[args.port][args.slot].bit.SLOTSR_2;
					slotStatus[3] = ioMxic->TSLSR_3[args.port][args.slot].bit.SLOTSR_3;
					slotStatus[4] = ioMxic->TSLSR_3[args.port][args.slot].bit.SLOTSR_4;
					slotStatus[5] = ioMxic->TSLSR_3[args.port][args.slot].bit.SLOTSR_5;
					slotStatus[6] = ioMxic->TSLSR_3[args.port][args.slot].bit.SLOTSR_6;
					slotStatus[7] = ioMxic->TSLSR_3[args.port][args.slot].bit.SLOTSR_7;
					break;
				case MxicUtlis_SPEC_ARBITER_4:
					slotStatus[0] = ioMxic->TSLSR_4[args.port][args.slot].bit.SLOTSR_0;
					slotStatus[1] = ioMxic->TSLSR_4[args.port][args.slot].bit.SLOTSR_1;
					slotStatus[2] = ioMxic->TSLSR_4[args.port][args.slot].bit.SLOTSR_2;
					slotStatus[3] = ioMxic->TSLSR_4[args.port][args.slot].bit.SLOTSR_3;
					slotStatus[4] = ioMxic->TSLSR_4[args.port][args.slot].bit.SLOTSR_4;
					slotStatus[5] = ioMxic->TSLSR_4[args.port][args.slot].bit.SLOTSR_5;
					slotStatus[6] = ioMxic->TSLSR_4[args.port][args.slot].bit.SLOTSR_6;
					slotStatus[7] = ioMxic->TSLSR_4[args.port][args.slot].bit.SLOTSR_7;
					break;
				default:
					// arbiter is illegal.
					result = MxicUtlis_INPUT_PARAM_ERROR;
					Ddim_Print(("E:imMxicGetSlotStatusArray(): arbiter is illegal. arbiter=%d\n", args.arbiter));
					break;
			}
		}
		else {
			slotStatus[0] = 0;
			slotStatus[1] = 0;
			slotStatus[2] = 0;
			slotStatus[3] = 0;
			slotStatus[4] = 0;
			slotStatus[5] = 0;
			slotStatus[6] = 0;
			slotStatus[7] = 0;

			// Unit number is invalid.
//			Ddim_Print(("imMxicGetSlotStatusArray(): unit number is invalid. unit=%d\n", unit));
		}
	}

	return result;
}


/*----------------------------------------------------------------------*/
/* PUBLIC  															    */
/*----------------------------------------------------------------------*/
/**
"Service history monitor" and "Access count or amount of transfer monitor" 
are started with this function.<br>
*/
VOID mxic_monitor_access_start_monitor( MxicMonitorAccess *self )
{
	MxicMonitorAccessPrivate *priv = MXIC_MONITOR_ACCESS_GET_PRIVATE(self);

	// Monitor processing ended flag is cleared.
	priv->gImMxicTransMonLimitEndState = MxicUtlis_MONITOR_OPERATION_PROCESS;

	// Start monitor.
	mxic_utlis_on_pclk( priv->mxicUtlis, MxicUtlis_UNIT_3 );

	IO_MXIC3.TMTRG.bit.TMTRG = 1;

	if ( IO_MXIC3.TMMD.bit.TMON == MxicUtlis_MONITOR_START_TRG ) {
		// When start conditions are TONTRG=1 writing. TONTRG=1 is performed here.
		IO_MXIC3.TMONTRG.bit.TONTRG = 1;
	}

	mxic_utlis_off_pclk( priv->mxicUtlis, MxicUtlis_UNIT_3 );

	MxicUtlis_DSB();

	return;
}

/**
"Service history monitor" and "Access count or amount of transfer monitor" 
are stoped with this function.<br>
*/
VOID mxic_monitor_access_stop_monitor( MxicMonitorAccess *self )
{
	MxicMonitorAccessPrivate *priv = MXIC_MONITOR_ACCESS_GET_PRIVATE(self);

	// Stop monitor.
	mxic_utlis_on_pclk( priv->mxicUtlis, MxicUtlis_UNIT_3 );

	IO_MXIC3.TMTRG.bit.TMTRG = 0;

	mxic_utlis_off_pclk( priv->mxicUtlis, MxicUtlis_UNIT_3 );

	MxicUtlis_DSB();

	// Monitor processing ended flag is cleared.
	priv->gImMxicTransMonLimitEndState = MxicUtlis_MONITOR_OPERATION_PROCESS;
}

/**
Set whether to stop service history monitor operation in a THSTOP terminal input.<br>
@param[in]		enable					Setting of whether to stop service history monitor operation in a THSTOP terminal input.<br>
										<ul><li>@ref MxicUtlis_ON
											<li>@ref MxicUtlis_OFF</ul>
@retval			D_DDIM_OK					Success
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error
*/
INT32 mxic_monitor_access_set_history_monitor_stop_enable( MxicMonitorAccess *self, UCHAR enable )
{
	MxicMonitorAccessPrivate *priv = MXIC_MONITOR_ACCESS_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( ( enable != MxicUtlis_ON) && (enable != MxicUtlis_OFF ) ) {
		// enable parameter value is illegal.
		Ddim_Assertion(("E:mxic_monitor_access_set_history_monitor_stop_enable(): enable is illegal. enable=%d\n", 
						enable));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	mxic_utlis_on_pclk( priv->mxicUtlis, MxicUtlis_UNIT_3 );

	IO_MXIC3.TMMD.bit.THSEN = enable;

	mxic_utlis_off_pclk( priv->mxicUtlis, MxicUtlis_UNIT_3 );

	MxicUtlis_DSB();

	return D_DDIM_OK;
}

/**
Get whether to stop service history monitor operation in a THSTOP terminal input.<br>
@param[out]		enable					Setting of whether to stop service history monitor operation in a THSTOP terminal input.<br>
										<ul><li>@ref MxicUtlis_ON
											<li>@ref MxicUtlis_OFF</ul>
@retval			D_DDIM_OK					Success
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error
*/
INT32 mxic_monitor_access_get_history_monitor_stop_enable( MxicMonitorAccess *self, UCHAR* const enable )
{
	MxicMonitorAccessPrivate *priv = MXIC_MONITOR_ACCESS_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( enable == NULL ) {
		// enable parameter is NULL.
		Ddim_Assertion(("E:mxic_monitor_access_get_history_monitor_stop_enable(): enable is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	mxic_utlis_on_pclk( priv->mxicUtlis, MxicUtlis_UNIT_3 );

	*enable = IO_MXIC3.TMMD.bit.THSEN;

	mxic_utlis_off_pclk( priv->mxicUtlis, MxicUtlis_UNIT_3 );

	return D_DDIM_OK;
}

/**
The service history monitor result of the specified port is acquired. <br>
param[in]		wrArbiter				Target write or read Arbiter.<br>
										Please refer to @ref ImMxicWrArbiter for a set value.<br>
@param[in]		arbiter					Target arbiter.<br>
										Please refer to @ref ImMxicSpecArbiter for a set value. <br>
@param[in]		port					Target port.<br>
										Please refer to @ref ImMxicPort for a set value. <br>
@param[out]		history					Result of service history monitor.<br>
@retval			D_DDIM_OK					Success
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error
@remarks		Please use this function on condition of following either.<br>
				<ul><li>Under a monitor operation stop.
					<li>The state which the transmission demand has not generated in the master currently assigned to the port for a monitor.</ul>
*/
INT32 mxic_monitor_access_get_history_monitor( MxicMonitorAccess *self, ImMxicWrArbiter wrArbiter, 
											   ImMxicSpecArbiter arbiter, ImMxicPort port, 
											   ImMxicHistoryMonitor* const history )
{
	MxicMonitorAccessPrivate *priv = MXIC_MONITOR_ACCESS_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( mxic_utlis_check_port( priv->mxicUtlis, wrArbiter, arbiter, port ) != D_DDIM_OK ) {
		// Parameter error.
		Ddim_Assertion(("E:mxic_monitor_access_get_history_monitor(): mxic_utlis_check_port error.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}

	if ( history == NULL ) {
		// history parameter is NULL.
		Ddim_Assertion(("E:mxic_monitor_access_get_history_monitor(): history is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	if ( wrArbiter == MxicUtlis_WR_ARBITER_W ) {

		mxic_utlis_on_pclk( priv->mxicUtlis, MxicUtlis_UNIT_3 );

		// Get service history of W port.
		history->history[0]		= IO_MXIC3.THSTW[arbiter][port].bit.THSTW_0;
		history->history[1]		= IO_MXIC3.THSTW[arbiter][port].bit.THSTW_1;
		history->history[2]		= IO_MXIC3.THSTW[arbiter][port].bit.THSTW_2;
		history->history[3]		= IO_MXIC3.THSTW[arbiter][port].bit.THSTW_3;
		history->history[4]		= IO_MXIC3.THSTW[arbiter][port].bit.THSTW_4;
		history->history[5]		= IO_MXIC3.THSTW[arbiter][port].bit.THSTW_5;
		history->history[6]		= IO_MXIC3.THSTW[arbiter][port].bit.THSTW_6;
		history->history[7]		= IO_MXIC3.THSTW[arbiter][port].bit.THSTW_7;
		history->history[8]		= IO_MXIC3.THSTW[arbiter][port].bit.THSTW_8;
		history->history[9]		= IO_MXIC3.THSTW[arbiter][port].bit.THSTW_9;
		history->history[10]	= IO_MXIC3.THSTW[arbiter][port].bit.THSTW_10;
		history->history[11]	= IO_MXIC3.THSTW[arbiter][port].bit.THSTW_11;
		history->history[12]	= IO_MXIC3.THSTW[arbiter][port].bit.THSTW_12;
		history->history[13]	= IO_MXIC3.THSTW[arbiter][port].bit.THSTW_13;
		history->history[14]	= IO_MXIC3.THSTW[arbiter][port].bit.THSTW_14;
		history->history[15]	= IO_MXIC3.THSTW[arbiter][port].bit.THSTW_15;

		mxic_utlis_off_pclk( priv->mxicUtlis, MxicUtlis_UNIT_3 );
	}
	else {
		mxic_utlis_on_pclk( priv->mxicUtlis, MxicUtlis_UNIT_3 );

		// Get service history of R port.
		history->history[0]		= IO_MXIC3.THSTR[arbiter][port].bit.THSTR_0;
		history->history[1]		= IO_MXIC3.THSTR[arbiter][port].bit.THSTR_1;
		history->history[2]		= IO_MXIC3.THSTR[arbiter][port].bit.THSTR_2;
		history->history[3]		= IO_MXIC3.THSTR[arbiter][port].bit.THSTR_3;
		history->history[4]		= IO_MXIC3.THSTR[arbiter][port].bit.THSTR_4;
		history->history[5]		= IO_MXIC3.THSTR[arbiter][port].bit.THSTR_5;
		history->history[6]		= IO_MXIC3.THSTR[arbiter][port].bit.THSTR_6;
		history->history[7]		= IO_MXIC3.THSTR[arbiter][port].bit.THSTR_7;
		history->history[8]		= IO_MXIC3.THSTR[arbiter][port].bit.THSTR_8;
		history->history[9]		= IO_MXIC3.THSTR[arbiter][port].bit.THSTR_9;
		history->history[10]	= IO_MXIC3.THSTR[arbiter][port].bit.THSTR_10;
		history->history[11]	= IO_MXIC3.THSTR[arbiter][port].bit.THSTR_11;
		history->history[12]	= IO_MXIC3.THSTR[arbiter][port].bit.THSTR_12;
		history->history[13]	= IO_MXIC3.THSTR[arbiter][port].bit.THSTR_13;
		history->history[14]	= IO_MXIC3.THSTR[arbiter][port].bit.THSTR_14;
		history->history[15]	= IO_MXIC3.THSTR[arbiter][port].bit.THSTR_15;

		mxic_utlis_off_pclk( priv->mxicUtlis, MxicUtlis_UNIT_3 );
	}

	return D_DDIM_OK;
}

/**
The service history monitor result of the all ports is acquired. <br>
@param[out]		allHistory				Result of service history monitor.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
@remarks		Please use this function on condition of following either.<br>
				<ul><li>Under a monitor operation stop.
					<li>The state which the transmission demand has not generated in the master currently assigned to the port for a monitor.</ul>
*/
INT32 mxic_monitor_access_get_history_monitor_all_port( MxicMonitorAccess *self, 
														MxicAllHistoryMonitor* const allHistory )
{
	INT32 result;
	INT32 i, j;
	
#ifdef CO_PARAM_CHECK
	if ( allHistory == NULL ) {
		// allHistory parameter is NULL.
		Ddim_Assertion(("E:mxic_monitor_access_get_history_monitor_all_port(): allHistory is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	// Get service history monitor result of W ports.
	for ( i = MxicUtlis_W_ARBITER_W1; i < MxicUtlis_W_ARBITER_MAX; i++ ) {

		for ( j = MxicUtlis_PORT_0; j < MxicUtlis_PORT_MAX; j++ ) {

			result = mxic_monitor_access_get_history_monitor( self, MxicUtlis_WR_ARBITER_W, (ImMxicSpecArbiter)i, 
															  (ImMxicPort)j, &allHistory->wArbiter[i][j] );

			if ( result != D_DDIM_OK ) {
				// Error
				Ddim_Print(("E:mxic_monitor_access_get_history_monitor_all_port(): "
							"mxic_monitor_access_get_history_monitor error.(W)\n"));
				return result;
			}
		}
	}

	// Get service history monitor result of R ports.
	for ( i = MxicUtlis_R_ARBITER_R1; i < MxicUtlis_R_ARBITER_MAX; i++ ) {

		for ( j = MxicUtlis_PORT_0; j < MxicUtlis_PORT_MAX; j++ ) {

			result = mxic_monitor_access_get_history_monitor( self, MxicUtlis_WR_ARBITER_R, (ImMxicSpecArbiter)i, 
															  (ImMxicPort)j, &allHistory->rArbiter[i][j] );

			if ( result != D_DDIM_OK ) {
				// Error
				Ddim_Print(("E:mxic_monitor_access_get_history_monitor_all_port(): "
							"mxic_monitor_access_get_history_monitor error.(R)\n"));
				return result;
			}
		}
	}

	return D_DDIM_OK;
}

/**
The slot status monitor result of the specified write channel arbiter is acquired. <br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		arbiter					Target write channel arbiter.<br>
										Please refer to @ref ImMxicWArbiter for a set value. <br>
@param[out]		status					Result of slot status monitor.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
@remarks		Please use this function on condition of following either.<br>
				<ul><li>Under a monitor operation stop.
					<li>The state which the transmission demand has not generated in the master currently assigned to the arbiter for a monitor.</ul>
*/
INT32 mxic_monitor_access_get_slot_status_monitor_w_arbiter( MxicMonitorAccess *self, ImMxicUnit unit, 
															 ImMxicWArbiter arbiter, 
															 MxicWarbiterAssignPort* const status )
{
	INT32						result;
	INT32						i, j, k;
	ImMxicSlot				slot;
	UCHAR						slotStatus[MxicUtlis_SLOT_SIZE_8];
	volatile struct io_jdsmxic*	ioMxic;
	SlotArrayArgs 				arrayArgs;
	MxicMonitorAccessPrivate *priv = MXIC_MONITOR_ACCESS_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( arbiter >= MxicUtlis_W_ARBITER_MAX ) {
		// arbiter parameter value is illegal.
		Ddim_Assertion(("E:mxic_monitor_access_get_slot_status_monitor_w_arbiter(): arbiter is illegal.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
	if ( status == NULL ) {
		// status parameter is NULL.
		Ddim_Assertion(("E:mxic_monitor_access_get_slot_status_monitor_w_arbiter(): status is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {

		mxic_utlis_wait_command_enable( priv->mxicUtlis, unit, ioMxic );		// Wait TCFLG=1.

		mxic_utlis_on_pclk( priv->mxicUtlis, unit );

		for ( i = 0; i < MxicUtlis_PORT_MAX; i++ ) {

			for ( j = 0; j < MxicUtlis_SLOT_MAX; j++ ) {
				// Convert value type. (INT32 to ImMxicSlot)
				slot = (ImMxicSlot)j;
				arrayArgs.wrArbiter =MxicUtlis_WR_ARBITER_W; 
				arrayArgs.arbiter = (ImMxicSpecArbiter)arbiter;
				arrayArgs.port = (ImMxicPort)i;
				arrayArgs.slot = slot;

				// Get status of specified slot.
				result = imMxicGetSlotStatusArray( unit, ioMxic, arrayArgs, slotStatus );

				if ( result == D_DDIM_OK ) {
					switch ( slot ) {
						case MxicUtlis_SLOT_0:
							// Get status of slot-0.
							for ( k = 0; k < MxicUtlis_SLOT_SIZE_8; k++ ) {
								status->port[i].slot0[k] = slotStatus[k];
							}
							break;
						case MxicUtlis_SLOT_1:
							// Get status of slot-1.
							for ( k = 0; k < MxicUtlis_SLOT_SIZE_8; k++ ) {
								status->port[i].slot1[k] = slotStatus[k];
							}
							break;
						case MxicUtlis_SLOT_2:
							// Get status of slot-2.
							for ( k = 0; k < MxicUtlis_SLOT_SIZE_8; k++ ) {
								status->port[i].slot2[k] = slotStatus[k];
							}
							break;
						case MxicUtlis_SLOT_3:
							// Get status of slot-3.
							for ( k = 0; k < MxicUtlis_SLOT_SIZE_8; k++ ) {
								status->port[i].slot3[k] = slotStatus[k];
							}
							break;
						default:
							// slot is illegal.
							Ddim_Print(("E:mxic_monitor_access_get_slot_status_monitor_w_arbiter(): "
										"slot is illegal. slot=%d\n", slot));
							result = MxicUtlis_INPUT_PARAM_ERROR;
					}
				}
			}
		}

		mxic_utlis_off_pclk( priv->mxicUtlis, unit );
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:mxic_monitor_access_get_slot_status_monitor_w_arbiter(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

/**
The slot status monitor result of the specified read channel arbiter is acquired. <br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		arbiter					Target read channel arbiter.<br>
										Please refer to @ref ImMxicRArbiter for a set value. <br>
@param[out]		status					Result of slot status monitor.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
@remarks		Please use this function on condition of following either.<br>
				<ul><li>Under a monitor operation stop.
					<li>The state which the transmission demand has not generated in the master currently assigned to the arbiter for a monitor.</ul>
*/
INT32 mxic_monitor_access_get_slot_status_monitor_r_arbiter( MxicMonitorAccess *self, ImMxicUnit unit, 
															 ImMxicRArbiter arbiter, 
															 MxicRarbiterAssignPort* const status )
{
	INT32						result;
	INT32						i, j, k;
	ImMxicSlot				slot;
	UCHAR						slotStatus[MxicUtlis_SLOT_SIZE_8];
	volatile struct io_jdsmxic*	ioMxic;
	SlotArrayArgs 				arrayArgs;
	MxicMonitorAccessPrivate *priv = MXIC_MONITOR_ACCESS_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( arbiter >= MxicUtlis_R_ARBITER_MAX ) {
		// arbiter parameter value is illegal.
		Ddim_Assertion(("E:mxic_monitor_access_get_slot_status_monitor_r_arbiter(): arbiter is illegal.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
	if ( status == NULL ) {
		// status parameter is NULL.
		Ddim_Assertion(("E:mxic_monitor_access_get_slot_status_monitor_r_arbiter(): status is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {

		mxic_utlis_wait_command_enable( priv->mxicUtlis, unit, ioMxic );		// Wait TCFLG=1.

		mxic_utlis_on_pclk( priv->mxicUtlis, unit );

		for ( i = 0; i < MxicUtlis_PORT_MAX; i++ ) {

			for ( j = 0; j < MxicUtlis_SLOT_MAX; j++ ) {
				// Convert value type. (INT32 to ImMxicSlot)
				slot = (ImMxicSlot)j;
				arrayArgs.wrArbiter =MxicUtlis_WR_ARBITER_R; 
				arrayArgs.arbiter = (ImMxicSpecArbiter)arbiter;
				arrayArgs.port = (ImMxicPort)i;
				arrayArgs.slot = slot;

				// Get status of specified slot.
				result = imMxicGetSlotStatusArray( unit, ioMxic, arrayArgs, slotStatus );

				if ( result == D_DDIM_OK ) {
					switch ( slot ) {
						case MxicUtlis_SLOT_0:
							// Get status of slot-0.
							for ( k = 0; k < MxicUtlis_SLOT_SIZE_8; k++ ) {
								status->port[i].slot0[k] = slotStatus[k];
							}
							break;
						case MxicUtlis_SLOT_1:
							// Get status of slot-1.
							for ( k = 0; k < MxicUtlis_SLOT_SIZE_8; k++ ) {
								status->port[i].slot1[k] = slotStatus[k];
							}
							break;
						case MxicUtlis_SLOT_2:
							// Get status of slot-2.
							for ( k = 0; k < MxicUtlis_SLOT_SIZE_8; k++ ) {
								status->port[i].slot2[k] = slotStatus[k];
							}
							break;
						case MxicUtlis_SLOT_3:
							// Get status of slot-3.
							for ( k = 0; k < MxicUtlis_SLOT_SIZE_8; k++ ) {
								status->port[i].slot3[k] = slotStatus[k];
							}
							break;
						default:
							// slot is illegal.
							Ddim_Print(("E:mxic_monitor_access_get_slot_status_monitor_r_arbiter(): "
										"slot is illegal. slot=%d\n", slot));
							result = MxicUtlis_INPUT_PARAM_ERROR;
					}
				}
			}
		}

		mxic_utlis_off_pclk( priv->mxicUtlis, unit );
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:mxic_monitor_access_get_slot_status_monitor_r_arbiter(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

/**
The slot status monitor result of the specified write channel arbiter is acquired. (group)<br>
@param[in]		arbiter					Target write channel arbiter.<br>
										Please refer to @ref MxicWArbiterGr for a set value. <br>
@param[out]		status					Result of slot status monitor.<br>
@retval			D_DDIM_OK					Success
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error
@remarks		Please use this function on condition of following either.<br>
				<ul><li>Under a monitor operation stop.
					<li>The state which the transmission demand has not generated in the master currently assigned to the arbiter for a monitor.</ul>
*/
INT32	mxic_monitor_access_get_slot_status_monitor_w_arbiter_group( MxicMonitorAccess *self, 
																	 MxicWArbiterGr arbiter, 
																	 MxicWarbiterAssignGr* const status )
{
	MxicMonitorAccessPrivate *priv = MXIC_MONITOR_ACCESS_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( arbiter >= MxicUtlis_W_ARBITER_GR_MAX ) {
		// arbiter parameter value is illegal.
		Ddim_Assertion(("E:mxic_monitor_access_get_slot_status_monitor_w_arbiter_group(): arbiter is illegal.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
	if ( status == NULL ) {
		// status parameter is NULL.
		Ddim_Assertion(("E:mxic_monitor_access_get_slot_status_monitor_w_arbiter_group(): status is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	mxic_utlis_wait_command_enable( priv->mxicUtlis, MxicUtlis_UNIT_3, (struct io_jdsmxic *)&IO_MXIC3 );// Wait TCFLG=1.

	mxic_utlis_on_pclk( priv->mxicUtlis, MxicUtlis_UNIT_3 );

	status->slot[0] = IO_MXIC3.TGSLSW[arbiter].bit.GSLOTSW_0;
	status->slot[1] = IO_MXIC3.TGSLSW[arbiter].bit.GSLOTSW_1;
	status->slot[2] = IO_MXIC3.TGSLSW[arbiter].bit.GSLOTSW_2;
	status->slot[3] = IO_MXIC3.TGSLSW[arbiter].bit.GSLOTSW_3;
	status->slot[4] = IO_MXIC3.TGSLSW[arbiter].bit.GSLOTSW_4;
	status->slot[5] = IO_MXIC3.TGSLSW[arbiter].bit.GSLOTSW_5;
	status->slot[6] = IO_MXIC3.TGSLSW[arbiter].bit.GSLOTSW_6;
	status->slot[7] = IO_MXIC3.TGSLSW[arbiter].bit.GSLOTSW_7;

	mxic_utlis_off_pclk( priv->mxicUtlis, MxicUtlis_UNIT_3 );

	return D_DDIM_OK;
}

/**
The slot status monitor result of the specified read channel arbiter is acquired. (group)<br>
@param[in]		arbiter					Target read channel arbiter.<br>
										Please refer to @ref MxicRArbiterGr for a set value. <br>
@param[out]		status					Result of slot status monitor.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
@remarks		Please use this function on condition of following either.<br>
				<ul><li>Under a monitor operation stop.
					<li>The state which the transmission demand has not generated in the master currently assigned to the arbiter for a monitor.</ul>
*/
INT32	mxic_monitor_access_get_slot_status_monitor_r_arbiter_group( MxicMonitorAccess *self, 
																	 MxicRArbiterGr arbiter, 
																	 MxicRarbiterAssignGr* const status )
{
	MxicMonitorAccessPrivate *priv = MXIC_MONITOR_ACCESS_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (arbiter >= MxicUtlis_R_ARBITER_GR_MAX ) {
		// arbiter parameter value is illegal.
		Ddim_Assertion(("E:mxic_monitor_access_get_slot_status_monitor_r_arbiter_group(): arbiter is illegal.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
	if ( status == NULL ) {
		// status parameter is NULL.
		Ddim_Assertion(("E:mxic_monitor_access_get_slot_status_monitor_r_arbiter_group(): status is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	mxic_utlis_wait_command_enable( priv->mxicUtlis, MxicUtlis_UNIT_3, (struct io_jdsmxic *)&IO_MXIC3 );// Wait TCFLG=1.

	mxic_utlis_on_pclk( priv->mxicUtlis, MxicUtlis_UNIT_3 );

	status->slot[0] = IO_MXIC3.TGSLSR[arbiter].bit.GSLOTSR_0;
	status->slot[1] = IO_MXIC3.TGSLSR[arbiter].bit.GSLOTSR_1;
	status->slot[2] = IO_MXIC3.TGSLSR[arbiter].bit.GSLOTSR_2;
	status->slot[3] = IO_MXIC3.TGSLSR[arbiter].bit.GSLOTSR_3;
	status->slot[4] = IO_MXIC3.TGSLSR[arbiter].bit.GSLOTSR_4;
	status->slot[5] = IO_MXIC3.TGSLSR[arbiter].bit.GSLOTSR_5;
	status->slot[6] = IO_MXIC3.TGSLSR[arbiter].bit.GSLOTSR_6;
	status->slot[7] = IO_MXIC3.TGSLSR[arbiter].bit.GSLOTSR_7;

	mxic_utlis_off_pclk( priv->mxicUtlis, MxicUtlis_UNIT_3 );

	return D_DDIM_OK;
}

/**
The slot status monitor result of all arbiter is acquired. <br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[out]		allStatus				Result of all slot status monitor.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
@remarks		Please use this function on condition of following either.<br>
				<ul><li>Under a monitor operation stop.
					<li>The state which the transmission demand has not generated in the master currently assigned to the arbiter for a monitor.</ul>
*/
INT32 mxic_monitor_access_get_slot_status_monitor_all_arbiter( MxicMonitorAccess *self, ImMxicUnit unit, 
															   MxicAllSlotMonitor* const allStatus )
{
	INT32 result;
	INT32 i;

#ifdef CO_PARAM_CHECK
	if ( allStatus == NULL ) {
		// allStatus parameter is NULL.
		Ddim_Assertion(("E:mxic_monitor_access_get_slot_status_monitor_all_arbiter(): allStatus is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	// Get slot status of all W arbiter.
	for ( i = MxicUtlis_W_ARBITER_W1; i < MxicUtlis_W_ARBITER_MAX; i++ ) {

		result = mxic_monitor_access_get_slot_status_monitor_w_arbiter( self, unit, (ImMxicWArbiter)i, 
																		&(allStatus->wArbiter[i]) );

		if ( result != D_DDIM_OK ) {
			// Error.
			Ddim_Print(("E:mxic_monitor_access_get_slot_status_monitor_all_arbiter(): "
						"mxic_monitor_access_get_slot_status_monitor_w_arbiter error.\n"));
			return MxicUtlis_INPUT_PARAM_ERROR;
		}
	}

	// Get slot status of all R arbiter.
	for ( i = MxicUtlis_R_ARBITER_R1; i < MxicUtlis_R_ARBITER_MAX; i++ ) {

		result = mxic_monitor_access_get_slot_status_monitor_r_arbiter( self, unit, (ImMxicRArbiter)i, 
																		&(allStatus->rArbiter[i]) );

		if ( result != D_DDIM_OK ) {
			// Error.
			Ddim_Print(("E:mxic_monitor_access_get_slot_status_monitor_all_arbiter(): "
						"mxic_monitor_access_get_slot_status_monitor_r_arbiter error.\n"));
			return MxicUtlis_INPUT_PARAM_ERROR;
		}
	}

	// Get slot status of all group-W arbiter.
	for ( i = MxicUtlis_W_ARBITER_GR_W0; i < MxicUtlis_W_ARBITER_GR_MAX; i++ ) {

		result = mxic_monitor_access_get_slot_status_monitor_w_arbiter_group( self, (MxicWArbiterGr)i, 
																			  &(allStatus->wArbiterGr[i]) );

		if ( result != D_DDIM_OK ) {
			// Error.
			Ddim_Print(("E:mxic_monitor_access_get_slot_status_monitor_all_arbiter(): "
						"mxic_monitor_access_get_slot_status_monitor_w_arbiter_group error.\n"));
			return MxicUtlis_INPUT_PARAM_ERROR;
		}
	}

	// Get slot status of all group-R arbiter.
	for ( i = MxicUtlis_R_ARBITER_GR_R0; i < MxicUtlis_R_ARBITER_GR_MAX; i++ ) {

		result = mxic_monitor_access_get_slot_status_monitor_r_arbiter_group( self, (MxicRArbiterGr)i, 
																			  &(allStatus->rArbiterGr[i]) );

		if ( result != D_DDIM_OK ) {
			// Error.
			Ddim_Print(("E:mxic_monitor_access_get_slot_status_monitor_all_arbiter(): "
						"mxic_monitor_access_get_slot_status_monitor_r_arbiter_group error.\n"));
			return MxicUtlis_INPUT_PARAM_ERROR;
		}
	}

	return D_DDIM_OK;
}

/**
The master status monitor result is acquired.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[out]		status					Result of all master status monitor.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
@remarks		The master number corresponds to the index of "status.wMaster" and "status.rMaster" array.<br>
				An example is shown below.<br>
				JDSPRO I/F-0 Write master status = status.wMaster[MxicUtlis_W_PRO_IF_0]<br>
				JDSDISP I/F-0 Read master status = status.rMaster[MxicUtlis_R_DISP_IF_0]<br>
*/
INT32 mxic_monitor_access_get_master_status_monitor( MxicMonitorAccess *self, ImMxicUnit unit, 
													 MxicMasterStatusMonitor* const status )
{
	INT32						masterCounter;
	INT32						regCounter;
	INT32						result;
	volatile struct io_jdsmxic*	ioMxic;
	MxicMonitorAccessPrivate *priv = MXIC_MONITOR_ACCESS_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( status == NULL ) {
		// status parameter is NULL.
		Ddim_Assertion(("E:mxic_monitor_access_get_master_status_monitor(): status is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {

		// Clear reserve area.
		status->wMaster[0] = 0;
		status->rMaster[0] = 0;

		// Initialize counter.
		masterCounter = 1;
		regCounter    = 0;

		mxic_utlis_on_pclk( priv->mxicUtlis, unit );

		// Get W master status.
		if ( unit != MxicUtlis_UNIT_4 ) {

			for (;;) {
				status->wMaster[masterCounter] = ioMxic->TMSTW[regCounter].bit.TMSTW_1;
				masterCounter++;
				if ( masterCounter >= MxicUtlis_MAX_W_MASTER_NUM ) {
					// End of enable master number.
					break;
				}
	
				status->wMaster[masterCounter] = ioMxic->TMSTW[regCounter].bit.TMSTW_2;
				masterCounter++;
				if ( masterCounter >= MxicUtlis_MAX_W_MASTER_NUM ) {
					// End of enable master number.
					break;
				}
	
				status->wMaster[masterCounter] = ioMxic->TMSTW[regCounter].bit.TMSTW_3;
				masterCounter++;
				if ( masterCounter >= MxicUtlis_MAX_W_MASTER_NUM ) {
					// End of enable master number.
					break;
				}
	
				status->wMaster[masterCounter] = ioMxic->TMSTW[regCounter].bit.TMSTW_4;
				masterCounter++;
				if ( masterCounter >= MxicUtlis_MAX_W_MASTER_NUM ) {
					// End of enable master number.
					break;
				}
				regCounter++;
			}
		}
		else {
			// Unit number is invalid.
			//Ddim_Print(("mxic_monitor_access_get_master_status_monitor(): unit number is invalid. unit=%d\n", unit));
		}

		// Initialize counter.
		masterCounter = 1;
		regCounter    = 0;

		// Get R master status.
		if ( unit != MxicUtlis_UNIT_0 ) {

			for (;;) {
				status->rMaster[masterCounter] = ioMxic->TMSTR[regCounter].bit.TMSTR_1;
				masterCounter++;
				if ( masterCounter >= MxicUtlis_MAX_R_MASTER_NUM ) {
					// End of enable master number.
					break;
				}
	
				status->rMaster[masterCounter] = ioMxic->TMSTR[regCounter].bit.TMSTR_2;
				masterCounter++;
				if ( masterCounter >= MxicUtlis_MAX_R_MASTER_NUM ) {
					// End of enable master number.
					break;
				}
	
				status->rMaster[masterCounter] = ioMxic->TMSTR[regCounter].bit.TMSTR_3;
				masterCounter++;
				if ( masterCounter >= MxicUtlis_MAX_R_MASTER_NUM ) {
					// End of enable master number.
					break;
				}
	
				status->rMaster[masterCounter] = ioMxic->TMSTR[regCounter].bit.TMSTR_4;
				masterCounter++;
				if ( masterCounter >= MxicUtlis_MAX_R_MASTER_NUM ) {
					// End of enable master number.
					break;
				}
				regCounter++;
			}
		}
		else {
			// Unit number is invalid.
			//Ddim_Print(("mxic_monitor_access_get_master_status_monitor(): unit number is invalid. unit=%d\n", unit));
		}

		mxic_utlis_off_pclk( priv->mxicUtlis, unit );
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:mxic_monitor_access_get_master_status_monitor(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

/**
The master status monitor result is acquired.(group)<br>
@param[out]		status					Result of all master status monitor.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
@remarks		The master number corresponds to the index of "status.wMaster" and "status.rMaster" array.<br>
				An example is shown below.<br>
				JDSPRO I/F-0 Write master status = status.wMaster[MxicUtlis_W_PRO_IF_0]<br>
				JDSDISP I/F-0 Read master status = status.rMaster[MxicUtlis_R_DISP_IF_0]<br>
*/
INT32 mxic_monitor_access_get_master_status_monitor_group( MxicMonitorAccess *self, 
														   MxicMasterStatusMonitor* const status )
{
	INT32 masterCounter;
	INT32 regCounter;
	MxicMonitorAccessPrivate *priv = MXIC_MONITOR_ACCESS_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( status == NULL ) {
		// status parameter is NULL.
		Ddim_Assertion(("E:mxic_monitor_access_get_master_status_monitor_group(): status is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	// Clear reserve area.
	status->wMaster[0] = 0;
	status->rMaster[0] = 0;

	// Initialize counter.
	masterCounter = 1;
	regCounter    = 0;

	mxic_utlis_on_pclk( priv->mxicUtlis, MxicUtlis_UNIT_3 );

	// Get W master status.
	for (;;) {
		status->wMaster[masterCounter] = IO_MXIC3.TMSTW_GR[regCounter].bit.TMSTW_1;
		masterCounter++;
		if ( masterCounter >= MxicUtlis_MAX_W_MASTER_NUM ) {
			// End of enable master number.
			break;
		}

		status->wMaster[masterCounter] = IO_MXIC3.TMSTW_GR[regCounter].bit.TMSTW_2;
		masterCounter++;
		if ( masterCounter >= MxicUtlis_MAX_W_MASTER_NUM ) {
			// End of enable master number.
			break;
		}

		status->wMaster[masterCounter] = IO_MXIC3.TMSTW_GR[regCounter].bit.TMSTW_3;
		masterCounter++;
		if ( masterCounter >= MxicUtlis_MAX_W_MASTER_NUM ) {
			// End of enable master number.
			break;
		}

		status->wMaster[masterCounter] = IO_MXIC3.TMSTW_GR[regCounter].bit.TMSTW_4;
		masterCounter++;
		if ( masterCounter >= MxicUtlis_MAX_W_MASTER_NUM ) {
			// End of enable master number.
			break;
		}
		regCounter++;
	}

	// Initialize counter.
	masterCounter = 1;
	regCounter    = 0;

	// Get R master status.
	for (;;) {
		status->rMaster[masterCounter] = IO_MXIC3.TMSTR_GR[regCounter].bit.TMSTR_1;
		masterCounter++;
		if ( masterCounter >= MxicUtlis_MAX_R_MASTER_NUM ) {
			// End of enable master number.
			break;
		}

		status->rMaster[masterCounter] = IO_MXIC3.TMSTR_GR[regCounter].bit.TMSTR_2;
		masterCounter++;
		if ( masterCounter >= MxicUtlis_MAX_R_MASTER_NUM ) {
			// End of enable master number.
			break;
		}

		status->rMaster[masterCounter] = IO_MXIC3.TMSTR_GR[regCounter].bit.TMSTR_3;
		masterCounter++;
		if ( masterCounter >= MxicUtlis_MAX_R_MASTER_NUM ) {
			// End of enable master number.
			break;
		}

		status->rMaster[masterCounter] = IO_MXIC3.TMSTR_GR[regCounter].bit.TMSTR_4;
		masterCounter++;
		if ( masterCounter >= MxicUtlis_MAX_R_MASTER_NUM ) {
			// End of enable master number.
			break;
		}
		regCounter++;
	}

	mxic_utlis_off_pclk( priv->mxicUtlis, MxicUtlis_UNIT_3 );

	return D_DDIM_OK;
}

/**
This function set the parameter of access count or transfer amount monitor.<br>
@param[in]		param					Setting of monitor operation.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
@remarks		Change of a parameter is reflected at the time of the monitor start by @ref mxic_monitor_access_start_monitor function. 
*/
INT32 mxic_monitor_access_set_access_or_trans_monitor_parameter( MxicMonitorAccess *self, 
																 const ImMxicMonitorParameter* const param )
{
	MxicMonitorAccessPrivate *priv = MXIC_MONITOR_ACCESS_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	INT32 i;

	if ( param == NULL ) {
		// param parameter is NULL.
		Ddim_Assertion(("E:mxic_monitor_access_set_access_or_trans_monitor_parameter(): param is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
	if ( param->startCondition != MxicUtlis_MONITOR_START_OFF ) {
		for ( i = 0; i < MxicUtlis_MAX_MONITOR_TARGET_NUM; i++ ) {
			if ( imMxicCheckMasterNumberForMonitor( param->target[i].monitorTarget ) != D_DDIM_OK ) {
				// Monitor target master number is illegal.
				Ddim_Assertion(("E:mxic_monitor_access_set_access_or_trans_monitor_parameter(): "
								"monitorTarget is illegal. (%02X)\n", param->target[i].monitorTarget));
				return MxicUtlis_INPUT_PARAM_ERROR;
			}
		}
		if ( param->endCondition == MxicUtlis_MONITOR_END_LIMIT ) {
			if ( imMxicCheckMasterNumberForMonitor( param->limitDetectionTarget ) != D_DDIM_OK ) {
				// Limit judgment target master number is illegal.
				Ddim_Assertion(("E:mxic_monitor_access_set_access_or_trans_monitor_parameter(): "
								"limitDetectionTarget is illegal. (%02X)\n", param->limitDetectionTarget));
				return MxicUtlis_INPUT_PARAM_ERROR;
			}
		}
	}
#endif // CO_PARAM_CHECK

	mxic_utlis_on_pclk( priv->mxicUtlis, MxicUtlis_UNIT_3 );

	// Set monitor mode register. (TMMD)
	IO_MXIC3.TMMD.bit.TMON		= param->startCondition;			// Monitor start conditions.
	IO_MXIC3.TMMD.bit.TMOFF		= param->endCondition;				// Monitor end conditions.

	IO_MXIC3.TMMD.bit.TMUP		= param->updateEnable;				// Update enabling of a monitor.
	IO_MXIC3.TMMD.bit.TMUPC		= param->updateTriggerInterval;	// Update trigger generation interval.

	IO_MXIC3.TMMD.bit.TMCLR		= param->updateClearEn;			// Selection monitor clear by update trigger.
	IO_MXIC3.TMMD.bit.TMCLRC	= param->startClearEn;// Selection monitor clear by asserting of a monitor start terminal.

	IO_MXIC3.TMMD.bit.TMRSEL	= param->cntVal;					// Selection switch of reading value.

	// Detailed setup is performed when using a monitor.
	if ( param->startCondition != MxicUtlis_MONITOR_START_OFF ) {	// TMON="00b"
		// Set monitor target and kind(Access or Transfer).
		IO_MXIC3.TMSEL.bit.TMAS_0	= param->target[0].monitorSel;
		IO_MXIC3.TMSEL.bit.TMSEL_0	= param->target[0].monitorTarget;
		IO_MXIC3.TMSEL.bit.TMAS_1	= param->target[1].monitorSel;
		IO_MXIC3.TMSEL.bit.TMSEL_1	= param->target[1].monitorTarget;
		IO_MXIC3.TMSEL.bit.TMAS_2	= param->target[2].monitorSel;
		IO_MXIC3.TMSEL.bit.TMSEL_2	= param->target[2].monitorTarget;
		IO_MXIC3.TMSEL.bit.TMAS_3	= param->target[3].monitorSel;
		IO_MXIC3.TMSEL.bit.TMSEL_3	= param->target[3].monitorTarget;

		if ( param->endCondition == MxicUtlis_MONITOR_END_LIMIT ) {			// TMOFF="11b"
			// Set limit judgment conditions.
			IO_MXIC3.TMLIMSEL.bit.TMALMS	= param->limitAccessTrans;// Selection limit judgment. (Access or Transfer)
			IO_MXIC3.TMLIMSEL.bit.TLIMSEL	= param->limitDetectionTarget;	// Selection limit judgment target.
			IO_MXIC3.TMLIMIT.bit.TMLIMT		= param->limit;						// Limit value.
		}
	}

	// The TMF interrupt is enable.
	IO_MXIC3.TMIE.bit.TME = 1;

	mxic_utlis_off_pclk( priv->mxicUtlis, MxicUtlis_UNIT_3 );

	MxicUtlis_DSB();

	// Set callback for TMF interrupt.
	priv->gImMxicAcsTransMonLimitEndCallBack = param->pCallBack;

	return D_DDIM_OK;
}

/**
This function get the parameter of access count or transfer amount monitor.<br>
@param[out]		param					Setting of monitor operation.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32 mxic_monitor_access_get_access_or_trans_monitor_parameter( MxicMonitorAccess *self, 
																 ImMxicMonitorParameter* const param )
{
	MxicMonitorAccessPrivate *priv = MXIC_MONITOR_ACCESS_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( param == NULL ) {
		// param parameter is NULL.
		Ddim_Assertion(("E:mxic_monitor_access_get_access_or_trans_monitor_parameter(): param is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	mxic_utlis_on_pclk( priv->mxicUtlis, MxicUtlis_UNIT_3 );

	// Get monitor mode register. (TMMD)
	param->startCondition			= IO_MXIC3.TMMD.bit.TMON;			// Monitor start conditions.
	param->endCondition			= IO_MXIC3.TMMD.bit.TMOFF;			// Monitor end conditions.
	param->updateEnable			= IO_MXIC3.TMMD.bit.TMUP;			// Update enabling of a monitor.
	param->updateTriggerInterval	= IO_MXIC3.TMMD.bit.TMUPC;			// Update trigger generation interval.
	param->updateClearEn			= IO_MXIC3.TMMD.bit.TMCLR;			// Selection monitor clear by update trigger.
	param->startClearEn			= IO_MXIC3.TMMD.bit.TMCLRC;// Selection monitor clear by asserting of a monitor start terminal.
	param->cntVal					= IO_MXIC3.TMMD.bit.TMRSEL;			// Selection switch of reading value.

	// Get monitor target and kind(Access or Transfer).
	param->target[0].monitorSel    = IO_MXIC3.TMSEL.bit.TMAS_0;
	param->target[0].monitorTarget = IO_MXIC3.TMSEL.bit.TMSEL_0;
	param->target[1].monitorSel    = IO_MXIC3.TMSEL.bit.TMAS_1;
	param->target[1].monitorTarget = IO_MXIC3.TMSEL.bit.TMSEL_1;
	param->target[2].monitorSel    = IO_MXIC3.TMSEL.bit.TMAS_2;
	param->target[2].monitorTarget = IO_MXIC3.TMSEL.bit.TMSEL_2;
	param->target[3].monitorSel    = IO_MXIC3.TMSEL.bit.TMAS_3;
	param->target[3].monitorTarget = IO_MXIC3.TMSEL.bit.TMSEL_3;

	// Get limit judgment conditions.
	param->limitAccessTrans		= IO_MXIC3.TMLIMSEL.bit.TMALMS;		// Selection limit judgment. (Access or Transfer)
	param->limitDetectionTarget	= IO_MXIC3.TMLIMSEL.bit.TLIMSEL;	// Selection limit judgment target.
	param->limit					= IO_MXIC3.TMLIMIT.bit.TMLIMT;		// Limit value.

	mxic_utlis_off_pclk( priv->mxicUtlis, MxicUtlis_UNIT_3 );

	// Set callback for TMF interrupt.
	param->pCallBack = priv->gImMxicAcsTransMonLimitEndCallBack;

	return D_DDIM_OK;
}

/**
This function get access count or transfer amount monitor result of specified entry.<br>
@param[in]		entry					Monitor number. (0~3)
@param[out]		result					Monitor result.
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32 mxic_monitor_access_get_access_or_trans_monitor( MxicMonitorAccess *self, UCHAR entry, UINT32* const result )
{
	MxicMonitorAccessPrivate *priv = MXIC_MONITOR_ACCESS_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( entry > 3 ) {
		// entry parameter value is illegal.
		Ddim_Assertion(("E:mxic_monitor_access_get_access_or_trans_monitor(): entry is illegal. entry=%d\n", entry));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
	if ( result == NULL ) {
		// result parameter is NULL.
		Ddim_Assertion(("E:mxic_monitor_access_get_access_or_trans_monitor(): result is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	mxic_utlis_on_pclk( priv->mxicUtlis, MxicUtlis_UNIT_3 );

	if ( IO_MXIC3.TMMD.bit.TMRSEL == MxicUtlis_VALUE_WHEN_UPDATE_TRG ) {
		// Generate update trigger.
		IO_MXIC3.TMUPTRG.bit.TUPTRG = 1;
	}

	// Get monitor result.
	*result = IO_MXIC3.TMCNT[entry].bit.TMCNT;

	mxic_utlis_off_pclk( priv->mxicUtlis, MxicUtlis_UNIT_3 );

	return D_DDIM_OK;
}

/**
This function get access count or transfer amount monitor result of all entry.<br>
@param[out]		allResult				Monitor result of all entry.
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32 mxic_monitor_access_get_access_or_trans_monitor_all_entry( MxicMonitorAccess *self, 
															AllAccessTransMonitor* const allResult )
{
	INT32 i;
	MxicMonitorAccessPrivate *priv = MXIC_MONITOR_ACCESS_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( allResult == NULL ) {
		// allResult parameter is NULL.
		Ddim_Assertion(("E:mxic_monitor_access_get_access_or_trans_monitor_all_entry(): allResult is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	mxic_utlis_on_pclk( priv->mxicUtlis, MxicUtlis_UNIT_3 );

	if ( IO_MXIC3.TMMD.bit.TMRSEL == MxicUtlis_VALUE_WHEN_UPDATE_TRG ) {
		// Generate update trigger.
		IO_MXIC3.TMUPTRG.bit.TUPTRG = 1;
	}

	// Get all monitor result.
	for ( i = 0; i < MxicUtlis_MAX_MONITOR_TARGET_NUM; i++ ) {
		allResult->count[i] = IO_MXIC3.TMCNT[i].bit.TMCNT;
	}

	mxic_utlis_off_pclk( priv->mxicUtlis, MxicUtlis_UNIT_3 );

	return D_DDIM_OK;
}

/**
The state of access count or transfer amount monitor is acquired.<br>
Please use this function in only the following the monitor end condition.<br>
- Monitor is ended by the amount limit judging of transmission. (MxicUtlis_MONITOR_END_LIMIT)<br><br>
@param[out]		monState				Moniter limit end state.<br>
										Please refer to the following for moniter processing state.<br>
										<ul><li>@ref MxicUtlis_MONITOR_OPERATION_PROCESS
											<li>@ref MxicUtlis_MONITOR_OPERATION_END</ul>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32 mxic_monitor_access_get_access_or_trans_monitor_limit_end_state( MxicMonitorAccess *self, UCHAR* monState )
{
	MxicMonitorAccessPrivate *priv = MXIC_MONITOR_ACCESS_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( monState == NULL ) {
		// monState parameter is NULL.
		Ddim_Assertion(("E:mxic_monitor_access_get_access_or_trans_monitor_limit_end_state(): monState is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	*monState = priv->gImMxicTransMonLimitEndState;

	return D_DDIM_OK;
}

void mxic_monitor_access_set_trans_mon_limit_end_state(MxicMonitorAccess *self, UCHAR state)
{
	MxicMonitorAccessPrivate *priv = MXIC_MONITOR_ACCESS_GET_PRIVATE(self);
	priv->gImMxicTransMonLimitEndState = state;
}

void mxic_monitor_access_set_trans_mon_limit_end_callback(MxicMonitorAccess *self)
{
	MxicMonitorAccessPrivate *priv = MXIC_MONITOR_ACCESS_GET_PRIVATE(self);
	if ( priv->gImMxicAcsTransMonLimitEndCallBack != NULL ) {
		((VOID (*)()) priv->gImMxicAcsTransMonLimitEndCallBack)();
	}
}

MxicMonitorAccess *mxic_monitor_access_new(void)
{
    MxicMonitorAccess* self = k_object_new_with_private(MXIC_TYPE_MONITOR_ACCESS, sizeof(MxicMonitorAccessPrivate));
    return self;
}
