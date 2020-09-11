/***********************************************************************
 * @Copyright(C) 上海网用软件有限公司
 * @file mxicmasterslave.h
 * @date 2020-09-02
 * @author: 吴海辉
 * @brief: 
 * @version: 1.0.0
***********************************************************************/

#ifndef __MXIC_MASTER_SLAVE_H__ 
#define __MXIC_MASTER_SLAVE_H__ 

#include "mxicutlis.h"

#define MXIC_TYPE_MASTER_SLAVE    (mxic_master_slave_get_type())
#define MXIC_MASTER_SLAVE(obj)    (K_TYPE_CHECK_INSTANCE_CAST(obj, MxicMasterSlave))
#define MXIC_IS_MASTER_SLAVE(obj) (K_TYPE_CHECK_INSTANCE_TYPE(obj, MXIC_TYPE_MASTER_SLAVE))


typedef struct _MxicMasterSlave MxicMasterSlave;
typedef struct _MxicMasterSlavePrivate MxicMasterSlavePrivate;

struct _MxicMasterSlave {
    KObject parent;
};

KConstType  mxic_master_slave_get_type(void);
// MxicMasterSlave*     mxic_master_slave_get(void);
MxicMasterSlave*     mxic_master_slave_new(void);

/**
This function set slave area setting of specified slave number.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value.<br>
@param[in]		slaveNumber			Slave area number.<br>
										Please refer to @ref ImMxicSlaveNumber for a set value. <br>
@param[in]		slaveArea				Slave area setting.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32	mxic_master_slave_set_slave_area( MxicMasterSlave *self, ImMxicUnit unit, 
										  ImMxicSlaveNumber slaveNumber, 
										  ImMxicSlaveArea const* const slaveArea );

/**
This function get slave area setting of specified slave number.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value.<br>
@param[in]		slaveNumber			Slave area number.<br>
										Please refer to @ref ImMxicSlaveNumber for a set value. <br>
@param[out]		slaveArea				Slave area setting.<br>
@retval			D_DDIM_OK					Success
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error
*/
INT32	mxic_master_slave_get_slave_area( MxicMasterSlave *self, ImMxicUnit unit, 
										  ImMxicSlaveNumber slaveNumber, ImMxicSlaveArea* const slaveArea );

/**
This function set slave area setting of all slave number.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value.<br>
@param[in]		allSlaveArea			Slave area setting of all slave number.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32	mxic_master_slave_set_slave_area_all( MxicMasterSlave *self, ImMxicUnit unit, 
											  const MxicAllSlaveArea* const allSlaveArea );

/**
This function get slave area setting of all slave number.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value.<br>
@param[out]		allSlaveArea			Slave area setting of all slave number.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32	mxic_master_slave_get_slave_area_all( MxicMasterSlave *self, ImMxicUnit unit, 
											  MxicAllSlaveArea* const allSlaveArea );

/**
This function set interruption setting of salave area decode error.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value.<br>
@param[in]		decErrInt				Setting of decoding error interruption.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
@remarks		Please acquire error status with an mxic_master_slave_get_decode_error function 
				at the time of decode error interruption generating. 
*/
INT32	mxic_master_slave_set_decode_error_int( MxicMasterSlave *self, ImMxicUnit unit, 
												const MxicDecErrInt* const decErrInt );

/**
This function get interruption setting of salave area decode error.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value.<br>
@param[out]		decErrInt				Setting of decoding error interruption.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32	mxic_master_slave_get_decode_error_int( MxicMasterSlave *self, ImMxicUnit unit, 
												MxicDecErrInt* const decErrInt );

/**
This function get decode error status.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value.<br>
@param[out]		status					Decode error status.<br>
@remarks		Decode error will be notifed by the callback function that set up with the mxic_master_slave_set_decode_error_int function.<br>
				Please acquire error status with mxic_master_slave_get_decode_error function at this time.
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32	mxic_master_slave_get_decode_error( MxicMasterSlave *self, ImMxicUnit unit, 
											ImMxicDecErr* const status );

/**
This function set the W master to the W arbiter.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value.<br>
@param[in]		arbiter					Target write arbiter.<br>
										Please refer to @ref ImMxicWArbiter for a set value.<br>
@param[in]		assign					Setting of master assign.
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
@remarks		The setting changed by this function is reflected by the configration start.
@remarks		MxicUtlis_W_RESERVE is set to the part where the channel is not set up without fail.
*/
INT32	mxic_master_slave_set_master_w_arbiter( MxicMasterSlave *self, ImMxicUnit unit, ImMxicWArbiter arbiter, 
												const MxicWarbiterAssignPort* const assign );

/**
This function get the W master from the W arbiter.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value.<br>
@param[in]		arbiter					Target write arbiter.<br>
										Please refer to @ref ImMxicWArbiter for a set value.<br>
@param[out]		assign					Setting of master assign.
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32	mxic_master_slave_get_master_w_arbiter( MxicMasterSlave *self, ImMxicUnit unit, ImMxicWArbiter arbiter, 
												MxicWarbiterAssignPort* const assign );

/**
This function set the R master to the R arbiter.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value.<br>
@param[in]		arbiter					Target read arbiter.<br>
										Please refer to @ref ImMxicRArbiter for a set value.<br>
@param[in]		assign					Setting of master assign.
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
@remarks		The setting changed by this function is reflected by the configration start.
@remarks		MxicUtlis_R_RESERVE is set to the part where the channel is not set up without fail.
*/
INT32	mxic_master_slave_set_master_r_arbiter( MxicMasterSlave *self, ImMxicUnit unit, 
												ImMxicRArbiter arbiter, 
												const MxicRarbiterAssignPort* const assign );

/**
This function get the R master from the R arbiter.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value.<br>
@param[in]		arbiter					Target read arbiter.<br>
										Please refer to @ref ImMxicRArbiter for a set value.<br>
@param[out]		assign					Setting of master assign.
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32	mxic_master_slave_get_master_r_arbiter( MxicMasterSlave *self, ImMxicUnit unit, 
												ImMxicRArbiter arbiter, 
												MxicRarbiterAssignPort* const assign );

/**
This function set the master to the all arbiter.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value.<br>
@param[in]		allAssign		 		Setting of master assign.
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
@remarks		The setting changed by this function is reflected by the configration start.
*/
INT32	mxic_master_slave_set_master_all_arbiter( MxicMasterSlave *self, ImMxicUnit unit, 
												  const MxicAllArbiterAssign* const allAssign );

/**
This function get the master from the all arbiter.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value.<br>
@param[out]		allAssign		 		Setting of master assign.
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32	mxic_master_slave_get_master_all_arbiter( MxicMasterSlave *self, ImMxicUnit unit, 
												  MxicAllArbiterAssign* const allAssign );

void mxic_master_slave_for_dec_err(MxicMasterSlave *self, ImMxicUnit unit, INT32 decErrCh);

#endif	// __MXIC_MASTER_SLAVE_H__