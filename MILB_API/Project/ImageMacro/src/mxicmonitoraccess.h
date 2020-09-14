/***********************************************************************
 * @Copyright(C) 上海网用软件有限公司
 * @file mxicmonitoraccess.h
 * @date 2020-09-02
 * @author: 吴海辉
 * @brief: 
 * @version: 1.0.0
***********************************************************************/

#ifndef __MXIC_MONITOR_ACCESS_H__ 
#define __MXIC_MONITOR_ACCESS_H__ 

#include "mxicutlis.h"


#define MXIC_TYPE_MONITOR_ACCESS    (mxic_monitor_access_get_type())
#define MXIC_MONITOR_ACCESS(obj)    (K_TYPE_CHECK_INSTANCE_CAST(obj, MxicMonitorAccess))
#define MXIC_IS_MONITOR_ACCESS(obj) (K_TYPE_CHECK_INSTANCE_TYPE(obj, MXIC_TYPE_MONITOR_ACCESS))


typedef struct _MxicMonitorAccess MxicMonitorAccess;
typedef struct _MxicMonitorAccessPrivate MxicMonitorAccessPrivate;

struct _MxicMonitorAccess {
    KObject parent;
};

KConstType             mxic_monitor_access_get_type(void);
// MxicMonitorAccess*     mxic_monitor_access_get(void);
MxicMonitorAccess*     mxic_monitor_access_new(void);

/**
"Service history monitor" and "Access count or amount of transfer monitor" are started with this function.<br>
*/
void	mxic_monitor_access_start_monitor( MxicMonitorAccess *self );

/**
"Service history monitor" and "Access count or amount of transfer monitor" are stoped with this function.<br>
*/
void	mxic_monitor_access_stop_monitor( MxicMonitorAccess *self );

/**
Set whether to stop service history monitor operation in a THSTOP terminal input.<br>
@param[in]		enable					Setting of whether to stop service history monitor operation in a THSTOP terminal input.<br>
										<ul><li>@ref MxicUtlis_ON
											<li>@ref MxicUtlis_OFF</ul>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
kint32	mxic_monitor_access_set_history_monitor_stop_enable( MxicMonitorAccess *self, kuchar enable );

/**
Get whether to stop service history monitor operation in a THSTOP terminal input.<br>
@param[out]		enable					Setting of whether to stop service history monitor operation in a THSTOP terminal input.<br>
										<ul><li>@ref MxicUtlis_ON
											<li>@ref MxicUtlis_OFF</ul>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
kint32	mxic_monitor_access_get_history_monitor_stop_enable( MxicMonitorAccess *self, kuchar* const enable );

/**
The service history monitor result of the specified port is acquired. <br>
@param[in]		wrArbiter				Target write or read Arbiter.<br>
										Please refer to @ref ImMxicWrArbiter for a set value.<br>
@param[in]		arbiter					Target arbiter.<br>
										Please refer to @ref ImMxicSpecArbiter for a set value. <br>
@param[in]		port					Target port.<br>
										Please refer to @ref ImMxicPort for a set value. <br>
@param[out]		history					Result of service history monitor.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
@remarks		Please use this function on condition of following either.<br>
				<ul><li>Under a monitor operation stop.
					<li>The state which the transmission demand has not generated in the master currently assigned to the port for a monitor.</ul>
*/
kint32	mxic_monitor_access_get_history_monitor( MxicMonitorAccess *self, ImMxicWrArbiter wrArbiter, 
												 ImMxicSpecArbiter arbiter, ImMxicPort port, 
												 ImMxicHistoryMonitor* const history );

/**
The service history monitor result of the all ports is acquired. <br>
@param[out]		allHistory				Result of service history monitor.<br>
@retval			D_DDIM_OK					Success
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error
@remarks		Please use this function on condition of following either.<br>
				<ul><li>Under a monitor operation stop.
					<li>The state which the transmission demand has not generated in the master currently assigned to the port for a monitor.</ul>
*/
kint32	mxic_monitor_access_get_history_monitor_all_port(MxicMonitorAccess *self, 
														 MxicAllHistoryMonitor* const allHistory);

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
kint32	mxic_monitor_access_get_slot_status_monitor_w_arbiter( MxicMonitorAccess *self, ImMxicUnit unit, 
															   ImMxicWArbiter arbiter, 
															   MxicWarbiterAssignPort* const status );

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
kint32	mxic_monitor_access_get_slot_status_monitor_r_arbiter( MxicMonitorAccess *self, ImMxicUnit unit, 
															   ImMxicRArbiter arbiter, 
															   MxicRarbiterAssignPort* const status );

/**
The slot status monitor result of the specified write channel arbiter is acquired. (group)<br>
@param[in]		arbiter					Target write channel arbiter.<br>
										Please refer to @ref MxicWArbiterGr for a set value. <br>
@param[out]		status					Result of slot status monitor.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
@remarks		Please use this function on condition of following either.<br>
				<ul><li>Under a monitor operation stop.
					<li>The state which the transmission demand has not generated in the master currently assigned to the arbiter for a monitor.</ul>
*/
kint32	mxic_monitor_access_get_slot_status_monitor_w_arbiter_group( MxicMonitorAccess *self, 
																	 MxicWArbiterGr arbiter, 
																	 MxicWarbiterAssignGr* const status );

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
kint32	mxic_monitor_access_get_slot_status_monitor_r_arbiter_group( MxicMonitorAccess *self, 
																	 MxicRArbiterGr arbiter, 
																	 MxicRarbiterAssignGr* const status );

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
kint32	mxic_monitor_access_get_slot_status_monitor_all_arbiter( MxicMonitorAccess *self, ImMxicUnit unit, 
																 MxicAllSlotMonitor* const allStatus );

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
kint32 mxic_monitor_access_get_master_status_monitor( MxicMonitorAccess *self, ImMxicUnit unit, 
													 MxicMasterStatusMonitor* const status );

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
kint32 mxic_monitor_access_get_master_status_monitor_group( MxicMonitorAccess *self, 
														   MxicMasterStatusMonitor* const status );

/**
This function set the parameter of access count or transfer amount monitor.<br>
@param[in]		param					Setting of monitor operation.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
@remarks		Change of a parameter is reflected at the time of the monitor start by @ref mxic_monitor_access_start_monitor function. 
*/
kint32	mxic_monitor_access_set_access_or_trans_monitor_parameter( MxicMonitorAccess *self, 
																   const ImMxicMonitorParameter* const param );

/**
This function get the parameter of access count or transfer amount monitor.<br>
@param[out]		param					Setting of monitor operation.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
kint32	mxic_monitor_access_get_access_or_trans_monitor_parameter( MxicMonitorAccess *self, 
																   ImMxicMonitorParameter* const param );

/**
This function get access count or transfer amount monitor result of specified entry.<br>
@param[in]		entry					Monitor number. (0~3)
@param[out]		result					Monitor result.
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
@remarks		Please use this function on condition of following either when "cntVal" setting is "MxicUtlis_TRANS_COUNT_VALUE".<br>
				<ul><li>Under a monitor operation stop.
					<li>The state which the transmission demand has not generated in the monitor target master(port).</ul>
				<br>
				And, please use this function in the state of fulfilling all the following conditions when "cntVal" setting is "MxicUtlis_VALUE_WHEN_UPDATE_TRG".<br>
				<ul><li>Under a monitor operation processing.
					<li>Timing which the updating trigger generated.</ul>
*/
kint32	mxic_monitor_access_get_access_or_trans_monitor( MxicMonitorAccess *self, kuchar entry, kuint32* const result );

/**
This function get access count or transfer amount monitor result of all entry.<br>
@param[out]		allResult				Monitor result of all entry.
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
@remarks		Please use this function on condition of following either when "cntVal" setting is "MxicUtlis_TRANS_COUNT_VALUE".<br>
				<ul><li>Under a monitor operation stop.
					<li>The state which the transmission demand has not generated in the monitor target master(port).</ul>
				<br>
				And, please use this function in the state of fulfilling all the following conditions when "cntVal" setting is "MxicUtlis_VALUE_WHEN_UPDATE_TRG".<br>
				<ul><li>Under a monitor operation processing.
					<li>Timing which the updating trigger generated.</ul>
*/
kint32	mxic_monitor_access_get_access_or_trans_monitor_all_entry( MxicMonitorAccess *self, 
															AllAccessTransMonitor* const allResult );

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
kint32	mxic_monitor_access_get_access_or_trans_monitor_limit_end_state( MxicMonitorAccess *self, kuchar* monState );

void mxic_monitor_access_set_trans_mon_limit_end_state(MxicMonitorAccess *self, kuchar state);
void mxic_monitor_access_set_trans_mon_limit_end_callback(MxicMonitorAccess *self);

#endif	// __MXIC_MONITOR_ACCESS_H__