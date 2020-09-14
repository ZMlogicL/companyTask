/***********************************************************************
 * @Copyright(C) 上海网用软件有限公司
 * @file immxic.h
 * @date 2020-09-02
 * @author: 吴海辉
 * @brief: 
 * @version: 1.0.0
***********************************************************************/

/** 
@addtogroup im_mxic
@{
	- @ref im_mxic_sample_section1
	- @ref im_mxic_sample_section2
	- @ref im_mxic_sample_section3
	- @ref im_mxic_sample_section4
*/

#ifndef __IM_MXIC_H__
#define __IM_MXIC_H__

#include "mxicutlis.h"

#define IM_TYPE_MXIC    (im_mxic_get_type())
#define IM_MXIC(obj)    (K_TYPE_CHECK_INSTANCE_CAST(obj, ImMxic))
#define IM_IS_MXIC(obj) (K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_MXIC))


typedef struct _ImMxic ImMxic;
typedef struct _ImMxicPrivate ImMxicPrivate;

struct _ImMxic {
	KObject parent;
};

KConstType  im_mxic_get_type(void);
ImMxic*     im_mxic_new(void);


/**
This function set initial value to register.But this function is not set software reset.<br>
@retval			D_DDIM_OK					Success.
*/
kint32	im_mxic_init( ImMxic *self, ImMxicUnit unit );

/**
This function does software reset.<br>
@param [in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
kint32	im_mxic_reset( ImMxic *self, ImMxicUnit unit );

/**
This function select arbiters of executed "configration start" and start configuration.<br>
@param [in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value.<br>
@param [in]		targetArbiter			Target arbiter of configration start.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
@remarks		Duplication setup of the master number to another port of the same slave including a read channel / write channel is prohibition.<br>
				In this case, this function returns the @ref MxicUtlis_INPUT_PARAM_ERROR error.<br>
				And, the allocation setting of the master is returned to the setting operating now.
*/
kint32	im_mxic_start_config( ImMxic *self, ImMxicUnit unit, const ImMxicConfigArbiter* const targetArbiter );

/**
Detection of Memory Access Area" are started with this function.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		param					Setting of detection parameters of slave each memory access.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
kint32	im_mxic_start_memory_access_detect( ImMxic *self, ImMxicUnit unit, 
											const MxicMemoryAccessSlave* const param );

/**
Detection of Memory Access Area" are stoped with this function.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
kint32	im_mxic_stop_memory_access_detect( ImMxic *self, ImMxicUnit unit );

/**
This function set the parameter of Detection parameters of slave each memory access.<br>
@param[in]		unit					Target unit number.<br>
@param[in]		param					Setting of detection parameters of slave each memory access.<br>
@retval			D_DDIM_OK					Success
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error
@remarks		Change of a parameter is reflected at the time of the detection start by @ref im_mxic_start_memory_access_detect function. 
*/
kint32	im_mxic_set_memory_access_detect( ImMxic *self, ImMxicUnit unit, 
											const MxicMemoryAccessSlave* const param );

/**
This function get the parameter of Detection parameters of slave each memory access.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		param					Setting of detection parameters of slave each memory access.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
@remarks		Change of a parameter is reflected at the time of the detection start by @ref im_mxic_start_memory_access_detect function. 
*/
kint32	im_mxic_get_memory_access_detect( ImMxic *self, ImMxicUnit unit, 
											MxicMemoryAccessSlave* const param );

/**
Set switch of register read value.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		sw						Switching of the register to be read.<br>
										<ul><li>@ref MxicUtlis_ON
											<li>@ref MxicUtlis_OFF</ul>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
@remarks		When set to ON, the read value of the register the following switches to the value of the internal circuit.<br>
					<ul><li>TREGION
						<li>TLVLW, TLVLR
						<li>TPORTMW, TPORTMR
						<li>TACPTCW, TACPTCR
						<li>TGACPTCW, TGACPTCR
						<li>TSLSW, TSLSR
						<li>TGSLSW, TGSLSR</ul>
*/
kint32	im_mxic_set_reg_read_switch( ImMxic *self, ImMxicUnit unit, kuchar sw );

/**
Get switch of register read value.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[out]		sw						Switching of the register to be read.<br>
										<ul><li>@ref MxicUtlis_ON
											<li>@ref MxicUtlis_OFF</ul>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
kint32	im_mxic_get_reg_read_switch( ImMxic *self, ImMxicUnit unit, kuchar *const sw );

/**
This function set output port.<br>
@param[in]		target						Setting target master.<br>
											<ul><li>@ref MxicUtlis_3_W_ELA
												<li>@ref MxicUtlis_3_W_XCH
												<li>@ref MxicUtlis_3_W_FPT_0
												<li>@ref MxicUtlis_3_W_FPT_1
												<li>@ref MxicUtlis_3_R_ELA
												<li>@ref MxicUtlis_3_R_XCH
												<li>@ref MxicUtlis_3_R_FPT_0
												<li>@ref MxicUtlis_3_R_FPT_1
@param[in]		outputPort					Setting of output port.<br>
@retval			D_DDIM_OK					Success.
@retval			D_IM_TMI_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
kint32	im_mxic_set_output_port( ImMxic *self, kuchar target, ImMxicPortGr outputPort );

/**
This function get output port.<br>
@param[in]		target						Setting target master.<br>
											<ul><li>@ref MxicUtlis_3_W_ELA
												<li>@ref MxicUtlis_3_W_XCH
												<li>@ref MxicUtlis_3_W_FPT_0
												<li>@ref MxicUtlis_3_W_FPT_1
												<li>@ref MxicUtlis_3_R_ELA
												<li>@ref MxicUtlis_3_R_XCH
												<li>@ref MxicUtlis_3_R_FPT_0
												<li>@ref MxicUtlis_3_R_FPT_1
@param[out]		outputPort					Setting of output port.<br>
@retval			D_DDIM_OK					Success.
@retval			D_IM_TMI_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
kint32	im_mxic_get_output_port( ImMxic *self, kuchar target, ImMxicPortGr* const outputPort );

/**
This function set output port.<br>
@param[in]		outPort					Setting of output port.<br>
@retval			D_DDIM_OK					Success.
@retval			D_IM_TMI_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
kint32	im_mxic_set_output_port_all( ImMxic *self, const ImMxicOutputPort* const outPort );

/**
This function get output port.<br>
@param[in]		outPort					Setting of output port.<br>
@retval			D_DDIM_OK					Success.
@retval			D_IM_TMI_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
kint32	im_mxic_get_output_port_all( ImMxic *self, ImMxicOutputPort *const outPort );

/**
Interruption handler of MXIC.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
*/
void	im_mxic_int_handler( ImMxicUnit unit );

#endif	// __IM_MXIC_H__

/*@}*/

/**
@weakgroup im_mxic
@{

@section im_mxic_sample_section1	Sample of "Start MXIC macro".
@code
// SAMPLE CODE //
kint32 mxic_start_sample( ImMxicUnit unit )
{
	kint32						result;
	ImMxicConfigArbiter	config_arbiter;			// Setting of configration start enable
	ImMxicClock				clock_enable;			// Setting of clock enable

	// Initialization and a recommendation setup are performed.
	result = Im_MXIC_Init( unit );
	if ( result != D_DDIM_OK ) {
		// Error processing
		return result;
	}

	// Clock setting 
	clock_enable.clkEnSlave10	= MxicUtlis_ON;
	clock_enable.clkEnSlave20	= MxicUtlis_ON;
	clock_enable.clkEnDecErr		= MxicUtlis_OFF;
	clock_enable.clkEnMonitor		= MxicUtlis_OFF;

	result = Im_MXIC_Set_Clock_Enable( unit, &clock_enable );
	if ( result != D_DDIM_OK ) {
		// Error processing
		return result;
	}

	// (*)Please change only a setup to change with an Im_MXIC_Set_XX function here.

	// Configration start
	config_arbiter.slW1ConfigOnFlg = MxicUtlis_ON;
	config_arbiter.slW2ConfigOnFlg = MxicUtlis_ON;
	config_arbiter.slR1ConfigOnFlg = MxicUtlis_OFF;
	config_arbiter.slR2ConfigOnFlg = MxicUtlis_OFF;

	result = Im_MXIC_Start_Config( unit, &config_arbiter );
	if (result != D_DDIM_OK) {
		// Error processing
		return result;
	}

	return result;
}
@endcode


@section im_mxic_sample_section2	Sample of "Service history monitor".
@code
// SAMPLE CODE //
kint32 mxic_service_history_monitor_sample( ImMxicUnit unit )
{
	kint32 result;
	ImMxicConfigArbiter		config_arbiter;		// Setting of configration start enable
	ImMxicClock					clock_enable;		// Setting of clock enable
	MxicAllHistoryMonitor	all_history;		// Monitor result of service history.

	// Initialization and a recommendation setup are performed.
	result = Im_MXIC_Init( unit );
	if ( result != D_DDIM_OK ) {
		// Error processing
		return result;
	}

	// Clock setting 
	clock_enable.clkEnSlave10	= MxicUtlis_ON;
	clock_enable.clkEnSlave20	= MxicUtlis_ON;
	clock_enable.clkEnDecErr		= MxicUtlis_OFF;
	clock_enable.clkEnMonitor		= MxicUtlis_ON;		// Clock is supplied to a monitor block. 

	result = Im_MXIC_Set_Clock_Enable( unit, &clock_enable );
	if ( result != D_DDIM_OK ) {
		// Error processing
		return result;
	}

	// (*)Please change only a setup to change with an Im_MXIC_Set_XX function here.

	// Disable monitor stop by THSTOP assert.
	result = Im_MXIC_Set_History_Monitor_Stop_Enable( MxicUtlis_OFF );
	if ( result != D_DDIM_OK ) {
		// Error processing
		return result;
	}

	// Configration start
	config_arbiter.slW1ConfigOnFlg = MxicUtlis_ON;
	config_arbiter.slW2ConfigOnFlg = MxicUtlis_ON;
	config_arbiter.slR1ConfigOnFlg = MxicUtlis_OFF;
	config_arbiter.slR2ConfigOnFlg = MxicUtlis_OFF;

	result = Im_MXIC_Start_Config( unit, &config_arbiter );
	if ( result != D_DDIM_OK ) {
		// Error processing
		return result;
	}

	.
	.
	.

	// Monitor is started to arbitrary timing.
	Im_MXIC_Start_Monitor();

	.
	.
	.

	// Monitor is stopped to arbitrary timing.
	Im_MXIC_Stop_Monitor();

	// Get monitor result of service history.
	result = MxicUtlis_GET_History_Monitor_All_Port( &all_history );
	if ( result != D_DDIM_OK ) {
		// Error processing
		return result;
	}

	return result;
}
@endcode


@section im_mxic_sample_section3	Sample of "Master status monitor".
@code
// SAMPLE CODE //
kint32 mxic_master_status_monitor_sample( ImMxicUnit unit )
{
	kint32							result;
	ImMxicConfigArbiter		config_arbiter;		// Setting of configration start enable
	ImMxicClock					clock_enable;		// Setting of clock enable
	MxicMasterStatusMonitor	status;				// Monitor result of master status.

	// Initialization and a recommendation setup are performed.
	result = Im_MXIC_Init( unit );
	if ( result != D_DDIM_OK ) {
		// Error processing
		return result;
	}

	// Clock setting 
	clock_enable.clkEnSlave10	= MxicUtlis_ON;
	clock_enable.clkEnSlave20	= MxicUtlis_ON;
	clock_enable.clkEnDecErr		= MxicUtlis_OFF;
	clock_enable.clkEnMonitor		= MxicUtlis_ON;		// Clock is supplied to a monitor block. 

	result = Im_MXIC_Set_Clock_Enable( unit, &clock_enable );
	if ( result != D_DDIM_OK ) {
		// Error processing
		return result;
	}

	// (*)Please change only a setup to change with an Im_MXIC_Set_XX function here.

	// Configration start
	config_arbiter.slW1ConfigOnFlg = MxicUtlis_ON;
	config_arbiter.slW2ConfigOnFlg = MxicUtlis_ON;
	config_arbiter.slR1ConfigOnFlg = MxicUtlis_OFF;
	config_arbiter.slR2ConfigOnFlg = MxicUtlis_OFF;

	result = Im_MXIC_Start_Config( unit, &config_arbiter );
	if ( result != D_DDIM_OK ) {
		// Error processing
		return result;
	}

	.
	.
	.

	return result;
}
@endcode


@section im_mxic_sample_section4	Sample of "Access count monitor".
	The precondition of the this sample is as follows.<br>
	<ul>
	  <li>MXIC macro has already been executed.</li>
	  <li>Clock is supplied to a monitor block by Im_MXIC_Set_Clock_Enable function.</li>
	</ul>
@code
// SAMPLE CODE //
kint32 mxic_access_monitor_sample( void )
{
	kint32						result;
	ImMxicMonitorParameter	monitor_param;

	// Set monitor parameter
	monitor_param.startCondition			= MxicUtlis_MONITOR_START_TRG;
	monitor_param.endCondition				= MxicUtlis_MONITOR_END_LIMIT;
	monitor_param.updateEnable				= MxicUtlis_OFF;
	monitor_param.updateTriggerInterval	= MxicUtlis_MONITOR_UPDATE_1;
	monitor_param.updateClearEn			= MxicUtlis_OFF;
	monitor_param.startClearEn			= MxicUtlis_OFF;
	monitor_param.cntVal					= MxicUtlis_TRANS_COUNT_VALUE;
	monitor_param.limitAccessTrans		= MxicUtlis_MONITOR_ACCESS;
	monitor_param.limitDetectionTarget	= MxicUtlis_3_R_XCH;
	monitor_param.limit						= 0x08000000;
	monitor_param.target[0].monitorSel		= MxicUtlis_MONITOR_ACCESS;
	monitor_param.target[1].monitorSel		= MxicUtlis_MONITOR_TRANSFER;
	monitor_param.target[2].monitorSel		= MxicUtlis_MONITOR_TRANSFER;
	monitor_param.target[3].monitorSel		= MxicUtlis_MONITOR_TRANSFER;
	monitor_param.target[0].monitorTarget	= MxicUtlis_3_R_XCH;
	monitor_param.target[1].monitorTarget	= MxicUtlis_3_W_FPT_0;
	monitor_param.target[2].monitorTarget	= MxicUtlis_3_R_FPT_0;
	monitor_param.target[3].monitorTarget	= MxicUtlis_3_W_XCH;
	monitor_param.pCallBack					= mxic_access_monitor_sample_callback;

	result = Im_MXIC_Set_Access_Or_Trans_Monitor_Parameter( &monitor_param );
	if ( result != D_DDIM_OK ) {
		// Error processing
		return result;
	}

	.
	.
	.

	// Monitor is started to arbitrary timing.
	Im_MXIC_Start_Monitor();

	return result;
}

void mxic_access_monitor_sample_callback( void )
{
	kint32									result;
	AllAccessTransMonitor	monitor_result;

	// Get monitor result.
	result = MxicUtlis_GET_Access_Or_Trans_Monitor_All_Entry( &monitor_result );
	if ( result != D_DDIM_OK ) {
		// Error processing
		return;
	}
	return;
}
@endcode

*/

/*@}*/
