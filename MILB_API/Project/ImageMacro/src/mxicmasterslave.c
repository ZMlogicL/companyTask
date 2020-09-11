/***********************************************************************
 * @Copyright(C) 上海网用软件有限公司
 * @file mxicmasterslave.c
 * @date 2020-09-02
 * @author: 吴海辉
 * @brief: 
 * @version: 1.0.0
***********************************************************************/

#include "mxicmasterslave.h"


K_TYPE_DEFINE_WITH_PRIVATE(MxicMasterSlave, mxic_master_slave)
#define MXIC_MASTER_SLAVE_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), MxicMasterSlavePrivate, MXIC_TYPE_MASTER_SLAVE))


typedef struct{
	ImMxicUnit unit;
	ImMxicWArbiter arbiter;
}WArbiter;

typedef struct{
	ImMxicUnit unit;
	ImMxicRArbiter arbiter;
}RArbiter;

struct _MxicMasterSlavePrivate
{
    MxicUtlis* mxicUtlis;
	// Callback function pointer for decode error.
	volatile ImMxicDecErrFunc gImMxicDecErrCallback[MxicUtlis_UNIT_MAX];
};


/*----------------------------------------------------------------------*/
/* DECLS  															    */
/*----------------------------------------------------------------------*/
#ifdef CO_PARAM_CHECK
static INT32 imMxicCheckRwMasterNumber( UCHAR masterType, UCHAR master );
static INT32 imMxicCheckSetMasterWArbiterParam( ImMxicWArbiter arbiter, 
												const MxicWarbiterAssignPort* const assign );
static INT32 imMxicCheckGetMasterWArbiterParam(ImMxicWArbiter arbiter, 
												MxicWarbiterAssignPort* const assign);
static INT32 imMxicCheckSetMasterRArbiterParam( ImMxicRArbiter arbiter, 
												const MxicRarbiterAssignPort* const assign );
static INT32 imMxicCheckGetMasterRArbiterParam( ImMxicRArbiter arbiter, 
												MxicRarbiterAssignPort* const assign );
#endif // CO_PARAM_CHECK
static INT32 imMxicSetMasterWArbiterReg( MxicMasterSlave *self, WArbiter arg, volatile struct io_jdsmxic* ioMxic, 
										 volatile struct io_jdsmxic_tbl* ioMxicTbl, 
										 const MxicWarbiterAssignPort* const assign );
static INT32 imMxicSetMasterRArbiterReg( MxicMasterSlave *self, RArbiter arg, volatile struct io_jdsmxic* ioMxic, 
										 volatile struct io_jdsmxic_tbl* ioMxicTbl,  
										 const MxicRarbiterAssignPort* const assign );
static INT32 imMxicSetSlaveAreaReg( MxicMasterSlave *self, ImMxicUnit unit, volatile struct io_jdsmxic* ioMxic, 
									ImMxicSlaveNumber slaveNumber, ImMxicSlaveArea const* const slaveArea );
static INT32 imMxicGetSlaveAreaReg( MxicMasterSlave *self, ImMxicUnit unit, volatile struct io_jdsmxic* ioMxic, 
									ImMxicSlaveNumber slaveNumber, ImMxicSlaveArea* const slaveArea );


/*----------------------------------------------------------------------*/
/* IMPL  															    */
/*----------------------------------------------------------------------*/
static void mxic_master_slave_constructor(MxicMasterSlave *self)
{
    MxicMasterSlavePrivate *priv = MXIC_MASTER_SLAVE_GET_PRIVATE(self);

	priv->mxicUtlis = mxic_utlis_new();
	for (int i = 0; i < MxicUtlis_UNIT_MAX; i++)
	{
		priv->gImMxicDecErrCallback[i] = NULL;
	}
}

static void mxic_master_slave_destructor(MxicMasterSlave *self)
{
    MxicMasterSlavePrivate *priv = MXIC_MASTER_SLAVE_GET_PRIVATE(self);

	if(priv->mxicUtlis)
	{
		k_object_unref(priv->mxicUtlis);
		priv->mxicUtlis = NULL;
	}
}

#ifdef CO_PARAM_CHECK
/**
Check master number and type.
@param[in]		masterType				Write master: MxicUtlis_MASTER_TYPE_WRITE
										Read master : MxicUtlis_MASTER_TYPE_READ 
@param[in]		master					Master number.
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
static INT32 imMxicCheckRwMasterNumber( UCHAR masterType, UCHAR master )
{
	INT32 result;

	// Check master type
	if ( ( master & MxicUtlis_MASTER_TYPE_CHECK_MASK ) == masterType ) {
		// Check-OK
		result = D_DDIM_OK;
	}
	else {
		// Master type is illegal.
		result = MxicUtlis_INPUT_PARAM_ERROR;
		Ddim_Print(("E:imMxicCheckRwMasterNumber(): masterType is illegal.\n"));
	}

	return result;
}

/**
Check parameter of mxic_master_slave_set_master_w_arbiter function.
@param[in]		arbiter					Target write arbiter.<br>
										Please refer to @ref ImMxicWArbiter for a set value.<br>
@param[in]		assign					Setting of master assign.
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
static INT32 imMxicCheckSetMasterWArbiterParam( ImMxicWArbiter arbiter, 
												const MxicWarbiterAssignPort* const assign )
{
	INT32 portPos;
	INT32 portPos2;
	INT32 slotPos;
	INT32 slotPos2;

	if ( arbiter >= MxicUtlis_W_ARBITER_MAX ) {
		// arbiter parameter value is illegal.
		Ddim_Print(("E:imMxicCheckSetMasterWArbiterParam(): arbiter is illegal.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}

	if ( assign == NULL ) {
		// assign parameter is NULL.
		Ddim_Print(("E:imMxicCheckSetMasterWArbiterParam(): assign is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}

	for ( portPos = MxicUtlis_PORT_0; portPos < MxicUtlis_PORT_MAX; portPos++ ) {

		for ( slotPos = 0; slotPos < MxicUtlis_SLOT_SIZE_8; slotPos++ ) {

			if ( (imMxicCheckRwMasterNumber( MxicUtlis_MASTER_TYPE_WRITE, 
											assign->port[portPos].slot0[slotPos] ) != D_DDIM_OK ) ||
				 (imMxicCheckRwMasterNumber( MxicUtlis_MASTER_TYPE_WRITE, 
				 							assign->port[portPos].slot1[slotPos] ) != D_DDIM_OK ) ||
				 (imMxicCheckRwMasterNumber( MxicUtlis_MASTER_TYPE_WRITE, 
				 							assign->port[portPos].slot2[slotPos] ) != D_DDIM_OK ) ||
				 (imMxicCheckRwMasterNumber( MxicUtlis_MASTER_TYPE_WRITE, 
				 							assign->port[portPos].slot3[slotPos] ) != D_DDIM_OK ) ) {
				// Master number is illegal.
				Ddim_Print(("E:imMxicCheckSetMasterWArbiterParam(): Write master number is illegal. "
							"arbiter=%u port=%u slot=%u\n", arbiter, portPos, slotPos));
				return MxicUtlis_INPUT_PARAM_ERROR;
			}

			if ( assign->port[portPos].slot0[slotPos] != MxicUtlis_W_RESERVE ) {

				for ( portPos2 = MxicUtlis_PORT_0; portPos2 < MxicUtlis_PORT_MAX; portPos2++ ) {

					for ( slotPos2 = 0; slotPos2 < MxicUtlis_SLOT_SIZE_8; slotPos2++ ) {

						if ( ( ( portPos != portPos2 ) 
							&& ( assign->port[portPos].slot0[slotPos] == assign->port[portPos2].slot0[slotPos2] ) ) ||
							 ( assign->port[portPos].slot0[slotPos] == assign->port[portPos2].slot1[slotPos2] ) ||
							 ( assign->port[portPos].slot0[slotPos] == assign->port[portPos2].slot2[slotPos2] ) ||
							 ( assign->port[portPos].slot0[slotPos] == assign->port[portPos2].slot3[slotPos2] ) ) {
							// Master number is illegal.
							Ddim_Print(("E:imMxicCheckSetMasterWArbiterParam(): Write master number is overlap. "
							   "port[%d].slot0[%d]=0x%02x\n", portPos, slotPos, assign->port[portPos].slot0[slotPos]));
							return MxicUtlis_INPUT_PARAM_ERROR;
						}
					}
				}
			}

			if ( assign->port[portPos].slot1[slotPos] != MxicUtlis_W_RESERVE ) {

				for ( portPos2 = MxicUtlis_PORT_0; portPos2 < MxicUtlis_PORT_MAX; portPos2++ ) {

					for ( slotPos2 = 0; slotPos2 < MxicUtlis_SLOT_SIZE_8; slotPos2++ ) {

						if ( ( ( portPos != portPos2 ) && ( assign->port[portPos].slot1[slotPos] == assign->port[portPos2].slot1[slotPos2] ) ) ||
							 ( assign->port[portPos].slot1[slotPos] == assign->port[portPos].slot2[slotPos2] ) ||
							 ( assign->port[portPos].slot1[slotPos] == assign->port[portPos].slot3[slotPos2] ) ) {
							// Master number is illegal.
							Ddim_Print(("E:imMxicCheckSetMasterWArbiterParam(): Write master number is overlap. port[%d].slot1[%d]=0x%02x\n",
										portPos, slotPos,  assign->port[portPos].slot1[slotPos]));
							return MxicUtlis_INPUT_PARAM_ERROR;
						}
					}
				}
			}

			if ( assign->port[portPos].slot2[slotPos] != MxicUtlis_W_RESERVE ) {

				for ( portPos2 = MxicUtlis_PORT_0; portPos2 < MxicUtlis_PORT_MAX; portPos2++ ) {

					for ( slotPos2 = 0; slotPos2 < MxicUtlis_SLOT_SIZE_8; slotPos2++ ) {

						if ( ( ( portPos != portPos2 ) 
							&& ( assign->port[portPos].slot2[slotPos] == assign->port[portPos2].slot2[slotPos2] ) ) ||
							 ( assign->port[portPos].slot2[slotPos] == assign->port[portPos].slot3[slotPos2] ) ) {
							// Master number is illegal.
							Ddim_Print(("E:imMxicCheckSetMasterWArbiterParam(): Write master number is overlap. "
							  "port[%d].slot2[%d]=0x%02x\n", portPos, slotPos,  assign->port[portPos].slot2[slotPos]));
							return MxicUtlis_INPUT_PARAM_ERROR;
						}
					}
				}
			}
		}
	}

	return D_DDIM_OK;
}

/**
Check parameter of mxic_master_slave_get_master_w_arbiter function.
@param[in]		arbiter					Target write arbiter.<br>
										Please refer to @ref ImMxicWArbiter for a set value.<br>
@param[in]		assign					Setting of master assign.
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
static INT32 imMxicCheckGetMasterWArbiterParam(ImMxicWArbiter arbiter, 
												MxicWarbiterAssignPort* const assign)
{
	if ( arbiter >= MxicUtlis_W_ARBITER_MAX ) {
		// arbiter parameter value is illegal.
		Ddim_Print(("E:imMxicCheckGetMasterWArbiterParam(): arbiter is illegal.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
	if ( assign == NULL ) {
		// assign parameter is NULL.
		Ddim_Print(("E:imMxicCheckGetMasterWArbiterParam(): assign is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}

	return D_DDIM_OK;
}

/**
Check parameter of mxic_master_slave_set_master_r_arbiter function.
@param[in]		arbiter					Target read arbiter.<br>
										Please refer to @ref ImMxicRArbiter for a set value.<br>
@param[in]		assign					Setting of master assign.
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
static INT32 imMxicCheckSetMasterRArbiterParam( ImMxicRArbiter arbiter, 
												const MxicRarbiterAssignPort* const assign )
{
	INT32 portPos;
	INT32 portPos2;
	INT32 slotPos;
	INT32 slotPos2;

	if ( arbiter >= MxicUtlis_R_ARBITER_MAX ) {
		// arbiter parameter value is illegal.
		Ddim_Print(("E:imMxicCheckSetMasterRArbiterParam(): arbiter is illegal.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}

	if ( assign == NULL ) {
		// assign parameter is NULL.
		Ddim_Print(("E:imMxicCheckSetMasterRArbiterParam(): assign is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}

	for ( portPos = MxicUtlis_PORT_0; portPos < MxicUtlis_PORT_MAX; portPos++ ) {

		for ( slotPos = 0; slotPos < MxicUtlis_SLOT_SIZE_8; slotPos++ ) {

			if ( ( imMxicCheckRwMasterNumber( MxicUtlis_MASTER_TYPE_READ, 
											assign->port[portPos].slot0[slotPos] ) != D_DDIM_OK ) ||
				 ( imMxicCheckRwMasterNumber( MxicUtlis_MASTER_TYPE_READ, 
				 							assign->port[portPos].slot1[slotPos] ) != D_DDIM_OK ) ||
				 ( imMxicCheckRwMasterNumber( MxicUtlis_MASTER_TYPE_READ, 
				 							assign->port[portPos].slot2[slotPos] ) != D_DDIM_OK ) ||
				 ( imMxicCheckRwMasterNumber( MxicUtlis_MASTER_TYPE_READ, 
				 							assign->port[portPos].slot3[slotPos] ) != D_DDIM_OK ) ) {
				// Master number is illegal.
				Ddim_Print(("E:imMxicCheckSetMasterRArbiterParam(): Read master number is illegal. "
							"arbiter=%u port=%u slot=%u\n", arbiter, portPos, slotPos));
				return MxicUtlis_INPUT_PARAM_ERROR;
			}

			if ( assign->port[portPos].slot0[slotPos] != MxicUtlis_R_RESERVE ) {

				for ( portPos2 = MxicUtlis_PORT_0; portPos2 < MxicUtlis_PORT_MAX; portPos2++ ) {

					for ( slotPos2 = 0; slotPos2 < MxicUtlis_SLOT_SIZE_8; slotPos2++ ) {

						if ( ( ( portPos != portPos2 ) 
							&& ( assign->port[portPos].slot0[slotPos] == assign->port[portPos2].slot0[slotPos2] ) ) ||
							 ( assign->port[portPos].slot0[slotPos] == assign->port[portPos].slot1[slotPos2] ) ||
							 ( assign->port[portPos].slot0[slotPos] == assign->port[portPos].slot2[slotPos2] ) ||
							 ( assign->port[portPos].slot0[slotPos] == assign->port[portPos].slot3[slotPos2] ) ) {
							// Master number is illegal.
							Ddim_Print(("E:imMxicCheckSetMasterRArbiterParam(): Read master number is overlap. "
										"port[%d].slot0[%d] = 0x%02x\n", 
										portPos, slotPos, assign->port[portPos].slot0[slotPos]));
							return MxicUtlis_INPUT_PARAM_ERROR;
						}
					}
				}
			}

			if ( assign->port[portPos].slot1[slotPos] != MxicUtlis_R_RESERVE ) {

				for ( portPos2 = MxicUtlis_PORT_0; portPos2 < MxicUtlis_PORT_MAX; portPos2++ ) {

					for ( slotPos2 = 0; slotPos2 < MxicUtlis_SLOT_SIZE_8; slotPos2++ ) {

						if ( ( ( portPos != portPos2 ) 
							&& ( assign->port[portPos].slot1[slotPos] == assign->port[portPos2].slot1[slotPos2] ) ) ||
							 ( assign->port[portPos].slot1[slotPos] == assign->port[portPos].slot2[slotPos2] ) ||
							 ( assign->port[portPos].slot1[slotPos] == assign->port[portPos].slot3[slotPos2] ) ) {
							// Master number is illegal.
							Ddim_Print(("E:imMxicCheckSetMasterRArbiterParam(): Read master number is overlap. "
										"port[%d].slot1[%d] = 0x%02x\n",
										portPos, slotPos, assign->port[portPos].slot1[slotPos]));
							return MxicUtlis_INPUT_PARAM_ERROR;
						}
					}
				}
			}

			if ( assign->port[portPos].slot2[slotPos] != MxicUtlis_R_RESERVE ) {

				for ( portPos2 = MxicUtlis_PORT_0; portPos2 < MxicUtlis_PORT_MAX; portPos2++ ) {

					for ( slotPos2 = 0; slotPos2 < MxicUtlis_SLOT_SIZE_8; slotPos2++ ) {

						if ( ( ( portPos != portPos2 ) 
							&& ( assign->port[portPos].slot2[slotPos] == assign->port[portPos2].slot2[slotPos2] ) ) ||
							 ( assign->port[portPos].slot2[slotPos] == assign->port[portPos].slot3[slotPos2] ) ) {
							// Master number is illegal.
							Ddim_Print(("E:imMxicCheckSetMasterRArbiterParam(): Read master number is overlap. "
										"port[%d].slot2[%d] = 0x%02x\n",
										portPos, slotPos, assign->port[portPos].slot2[slotPos]));
							return MxicUtlis_INPUT_PARAM_ERROR;
						}
					}
				}
			}
		}
	}

	return D_DDIM_OK;
}

/**
Check parameter of mxic_master_slave_get_master_r_arbiter function.
@param[in]		arbiter					Target read arbiter.<br>
										Please refer to @ref ImMxicRArbiter for a set value.<br>
@param[in]		assign					Setting of master assign.
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
static INT32 imMxicCheckGetMasterRArbiterParam( ImMxicRArbiter arbiter, 
												MxicRarbiterAssignPort* const assign )
{
	if ( arbiter >= MxicUtlis_R_ARBITER_MAX ) {
		// arbiter parameter value is illegal.
		Ddim_Print(("E:imMxicCheckGetMasterRArbiterParam(): arbiter is illegal.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
	if ( assign == NULL ) {
		// assign parameter is NULL.
		Ddim_Print(("E:imMxicCheckGetMasterRArbiterParam(): assign is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}

	return D_DDIM_OK;
}
#endif // CO_PARAM_CHECK

/**
This local function set the W master to the W arbiter.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		ioMxic					MXIC address.<br>
@param[in]		ioMxicTbl				MXIC table address.<br>
@param[in]		arbiter					Target write arbiter.<br>
										Please refer to @ref ImMxicWArbiter for a set value.<br>
@param[in]		assign					Setting of master assign.
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
@remarks		The setting changed by this function is reflected by the configration start.
@remarks		MxicUtlis_W_RESERVE is set to the part where the channel is not set up without fail.
*/
static INT32 imMxicSetMasterWArbiterReg( MxicMasterSlave *self, WArbiter args, volatile struct io_jdsmxic* ioMxic, 
										 volatile struct io_jdsmxic_tbl* ioMxicTbl,  
										 const MxicWarbiterAssignPort* const assign )
{
	INT32 i, j;
	INT32 result;
    MxicMasterSlavePrivate *priv = MXIC_MASTER_SLAVE_GET_PRIVATE(self);

	result = D_DDIM_OK;

	if ( ( args.unit == MxicUtlis_UNIT_1 ) || ( args.unit == MxicUtlis_UNIT_2 ) || ( args.unit == MxicUtlis_UNIT_3 ) ){

		if ( args.unit == MxicUtlis_UNIT_3 ) {
			DDIM_User_AhbReg_SpinLock();	// JPEG issue work around.
		}

		mxic_utlis_on_hclk( priv->mxicUtlis, args.unit );

		for ( i = MxicUtlis_PORT_0; i < MxicUtlis_PORT_MAX; i++ ) {

			for ( j = 0; j < MxicUtlis_SLOT_SIZE_8; j++ ) {

				switch ( args.arbiter ) {
					case MxicUtlis_W_ARBITER_W1:
						ioMxicTbl->TSLW_1[i].byte[MxicUtlis_SLOT_0][j] = assign->port[i].slot0[j];
						ioMxicTbl->TSLW_1[i].byte[MxicUtlis_SLOT_1][j] = assign->port[i].slot1[j];
						ioMxicTbl->TSLW_1[i].byte[MxicUtlis_SLOT_2][j] = assign->port[i].slot2[j];
						ioMxicTbl->TSLW_1[i].byte[MxicUtlis_SLOT_3][j] = assign->port[i].slot3[j];
						break;
					case MxicUtlis_W_ARBITER_W2:
						ioMxicTbl->TSLW_2[i].byte[MxicUtlis_SLOT_0][j] = assign->port[i].slot0[j];
						ioMxicTbl->TSLW_2[i].byte[MxicUtlis_SLOT_1][j] = assign->port[i].slot1[j];
						ioMxicTbl->TSLW_2[i].byte[MxicUtlis_SLOT_2][j] = assign->port[i].slot2[j];
						ioMxicTbl->TSLW_2[i].byte[MxicUtlis_SLOT_3][j] = assign->port[i].slot3[j];
						break;
					case MxicUtlis_W_ARBITER_W3:
						ioMxicTbl->TSLW_3[i].byte[MxicUtlis_SLOT_0][j] = assign->port[i].slot0[j];
						ioMxicTbl->TSLW_3[i].byte[MxicUtlis_SLOT_1][j] = assign->port[i].slot1[j];
						ioMxicTbl->TSLW_3[i].byte[MxicUtlis_SLOT_2][j] = assign->port[i].slot2[j];
						ioMxicTbl->TSLW_3[i].byte[MxicUtlis_SLOT_3][j] = assign->port[i].slot3[j];
						break;
					case MxicUtlis_W_ARBITER_W4:
						ioMxicTbl->TSLW_4[i].byte[MxicUtlis_SLOT_0][j] = assign->port[i].slot0[j];
						ioMxicTbl->TSLW_4[i].byte[MxicUtlis_SLOT_1][j] = assign->port[i].slot1[j];
						ioMxicTbl->TSLW_4[i].byte[MxicUtlis_SLOT_2][j] = assign->port[i].slot2[j];
						ioMxicTbl->TSLW_4[i].byte[MxicUtlis_SLOT_3][j] = assign->port[i].slot3[j];
						break;
					default:
						// arbiter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:imMxicSetMasterWArbiterReg(): arbiter is illegal. arbiter=%d\n", args.arbiter));
						break;
				}
			}
		}

		mxic_utlis_off_hclk( priv->mxicUtlis, args.unit );

		if ( args.unit == MxicUtlis_UNIT_3 ) {
			DDIM_User_AhbReg_SpinUnLock();	// JPEG issue work around.
		}
	}
	else {
		// Unit number is invalid.
		//Ddim_Print(("imMxicSetMasterWArbiterReg(): unit number is invalid. unit=%d\n", unit));
	}

	return result;
}

/**
This local function get the R master from the R arbiter.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		ioMxic					MXIC address.<br>
@param[in]		ioMxicTbl				MXIC table address.<br>
@param[in]		arbiter					Target read arbiter.<br>
										Please refer to @ref ImMxicRArbiter for a set value.<br>
@param[out]		assign					Setting of master assign.
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
static INT32 imMxicSetMasterRArbiterReg( MxicMasterSlave *self, RArbiter args, volatile struct io_jdsmxic* ioMxic, 
										 volatile struct io_jdsmxic_tbl* ioMxicTbl, 
										 const MxicRarbiterAssignPort* const assign )
{
	INT32 i, j;
	INT32 result;
    MxicMasterSlavePrivate *priv = MXIC_MASTER_SLAVE_GET_PRIVATE(self);

	result = D_DDIM_OK;

	if ( ( args.unit == MxicUtlis_UNIT_1 ) || ( args.unit == MxicUtlis_UNIT_2 ) || ( args.unit == MxicUtlis_UNIT_3 ) ){

		if ( args.unit == MxicUtlis_UNIT_3 ) {
			DDIM_User_AhbReg_SpinLock();	// JPEG issue work around.
		}

		mxic_utlis_on_hclk( priv->mxicUtlis, args.unit );

		for ( i = MxicUtlis_PORT_0; i < MxicUtlis_PORT_MAX; i++ ) {

			for ( j = 0; j < MxicUtlis_SLOT_SIZE_8; j++ ) {

				switch ( args.arbiter ) {
					case MxicUtlis_R_ARBITER_R1:
						ioMxicTbl->TSLR_1[i].byte[MxicUtlis_SLOT_0][j] 
							= (assign->port[i].slot0[j] & MxicUtlis_READ_MASTER_FLG_MASK);
						ioMxicTbl->TSLR_1[i].byte[MxicUtlis_SLOT_1][j] 
							= (assign->port[i].slot1[j] & MxicUtlis_READ_MASTER_FLG_MASK);
						ioMxicTbl->TSLR_1[i].byte[MxicUtlis_SLOT_2][j] 
							= (assign->port[i].slot2[j] & MxicUtlis_READ_MASTER_FLG_MASK);
						ioMxicTbl->TSLR_1[i].byte[MxicUtlis_SLOT_3][j] 
							= (assign->port[i].slot3[j] & MxicUtlis_READ_MASTER_FLG_MASK);
						break;
					case MxicUtlis_R_ARBITER_R2:
						ioMxicTbl->TSLR_2[i].byte[MxicUtlis_SLOT_0][j] 
							= (assign->port[i].slot0[j] & MxicUtlis_READ_MASTER_FLG_MASK);
						ioMxicTbl->TSLR_2[i].byte[MxicUtlis_SLOT_1][j] 
							= (assign->port[i].slot1[j] & MxicUtlis_READ_MASTER_FLG_MASK);
						ioMxicTbl->TSLR_2[i].byte[MxicUtlis_SLOT_2][j] 
							= (assign->port[i].slot2[j] & MxicUtlis_READ_MASTER_FLG_MASK);
						ioMxicTbl->TSLR_2[i].byte[MxicUtlis_SLOT_3][j] 
							= (assign->port[i].slot3[j] & MxicUtlis_READ_MASTER_FLG_MASK);
						break;
					case MxicUtlis_R_ARBITER_R3:
						ioMxicTbl->TSLR_3[i].byte[MxicUtlis_SLOT_0][j] 
							= (assign->port[i].slot0[j] & MxicUtlis_READ_MASTER_FLG_MASK);
						ioMxicTbl->TSLR_3[i].byte[MxicUtlis_SLOT_1][j] 
							= (assign->port[i].slot1[j] & MxicUtlis_READ_MASTER_FLG_MASK);
						ioMxicTbl->TSLR_3[i].byte[MxicUtlis_SLOT_2][j] 
							= (assign->port[i].slot2[j] & MxicUtlis_READ_MASTER_FLG_MASK);
						ioMxicTbl->TSLR_3[i].byte[MxicUtlis_SLOT_3][j] 
							= (assign->port[i].slot3[j] & MxicUtlis_READ_MASTER_FLG_MASK);
						break;
					case MxicUtlis_R_ARBITER_R4:
						ioMxicTbl->TSLR_4[i].byte[MxicUtlis_SLOT_0][j] 
							= (assign->port[i].slot0[j] & MxicUtlis_READ_MASTER_FLG_MASK);
						ioMxicTbl->TSLR_4[i].byte[MxicUtlis_SLOT_1][j] 
							= (assign->port[i].slot1[j] & MxicUtlis_READ_MASTER_FLG_MASK);
						ioMxicTbl->TSLR_4[i].byte[MxicUtlis_SLOT_2][j] 
							= (assign->port[i].slot2[j] & MxicUtlis_READ_MASTER_FLG_MASK);
						ioMxicTbl->TSLR_4[i].byte[MxicUtlis_SLOT_3][j] 
							= (assign->port[i].slot3[j] & MxicUtlis_READ_MASTER_FLG_MASK);
						break;
					default:
						// arbiter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:imMxicSetMasterRArbiterReg(): arbiter is illegal. arbiter=%d\n", args.arbiter));
						break;
				}
			}
		}

		mxic_utlis_off_hclk( priv->mxicUtlis, args.unit );

		MxicUtlis_DSB();

		if ( args.unit == MxicUtlis_UNIT_3 ) {
			DDIM_User_AhbReg_SpinUnLock();	// JPEG issue work around.
		}
	}
	else {
		// Unit number is invalid.
		//Ddim_Print(("imMxicSetMasterRArbiterReg(): unit number is invalid. unit=%d\n", unit));
	}

	return result;
}

/**
Set slave area setting of specified slave number.<br>
However, reflection of change is not carried out.
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		ioMxic					MXIC address.<br>
@param[in]		slaveNumber			Slave area number.<br>
										Please refer to @ref ImMxicSlaveNumber for a set value. <br>
@param[in]		slaveArea				Slave area setting.<br>
@retval			D_DDIM_OK					Success
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error
*/
static INT32 imMxicSetSlaveAreaReg( MxicMasterSlave *self, ImMxicUnit unit, volatile struct io_jdsmxic* ioMxic, 
									ImMxicSlaveNumber slaveNumber,  ImMxicSlaveArea const* const slaveArea )
{
	UCHAR regReadSw;
    MxicMasterSlavePrivate *priv = MXIC_MASTER_SLAVE_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( slaveNumber >= MxicUtlis_SLAVE_NUMBER_MAX ) {
		// slaveNumber parameter value is illegal.
		Ddim_Assertion(("E:imMxicSetSlaveAreaReg(): slaveNumber is illegal. slaveNumber=%d\n", slaveNumber));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
	if ( slaveArea == NULL ) {
		// slaveArea parameter is NULL.
		Ddim_Assertion(("E:imMxicSetSlaveAreaReg(): slaveArea is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	mxic_utlis_on_pclk( priv->mxicUtlis, unit );

	regReadSw = ioMxic->TRVSW.bit.TRVSW;

	if( regReadSw == MxicUtlis_ON ) {
		ioMxic->TRVSW.bit.TRVSW = MxicUtlis_OFF;
	}

	ioMxic->TREGION[slaveNumber].bit.TSIZE = slaveArea->size;
	ioMxic->TREGION[slaveNumber].bit.TSTAD = slaveArea->address;

	if( regReadSw == MxicUtlis_ON ) {
		ioMxic->TRVSW.bit.TRVSW = MxicUtlis_ON;
	}

	mxic_utlis_off_pclk( priv->mxicUtlis, unit );

	return D_DDIM_OK;
}

/**
Get slave area setting of specified slave number.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		ioMxic					MXIC address.<br>
@param[in]		slaveNumber			Slave area number.<br>
										Please refer to @ref ImMxicSlaveNumber for a set value. <br>
@param[in]		slaveArea				Slave area setting.<br>
@retval			D_DDIM_OK					Success
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error
*/
static INT32 imMxicGetSlaveAreaReg( MxicMasterSlave *self, ImMxicUnit unit, volatile struct io_jdsmxic* ioMxic, 
									ImMxicSlaveNumber slaveNumber, ImMxicSlaveArea* const slaveArea )
{
    MxicMasterSlavePrivate *priv = MXIC_MASTER_SLAVE_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( slaveNumber >= MxicUtlis_SLAVE_NUMBER_MAX ) {
		// slaveNumber parameter value is illegal.
		Ddim_Assertion(("E:imMxicGetSlaveAreaReg(): slaveNumber is illegal. slaveNumber=%d\n", slaveNumber));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
	if ( slaveArea == NULL ) {
		// slaveArea parameter is NULL.
		Ddim_Assertion(("E:imMxicGetSlaveAreaReg(): slaveArea is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	mxic_utlis_on_pclk( priv->mxicUtlis, unit );

	slaveArea->size	= ioMxic->TREGION[slaveNumber].bit.TSIZE;
	slaveArea->address	= ioMxic->TREGION[slaveNumber].bit.TSTAD;

	mxic_utlis_off_pclk( priv->mxicUtlis, unit );

	return D_DDIM_OK;
}


/*----------------------------------------------------------------------*/
/* PUBLIC  															    */
/*----------------------------------------------------------------------*/
/**
This function set slave area setting of specified slave number.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		slaveNumber			Slave area number.<br>
										Please refer to @ref ImMxicSlaveNumber for a set value. <br>
@param[in]		slaveArea				Slave area setting.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32 mxic_master_slave_set_slave_area( MxicMasterSlave *self, ImMxicUnit unit, 
										ImMxicSlaveNumber slaveNumber, 
										ImMxicSlaveArea const* const slaveArea )
{
	INT32						result;
	volatile struct io_jdsmxic*	ioMxic;
    MxicMasterSlavePrivate *priv = MXIC_MASTER_SLAVE_GET_PRIVATE(self);

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {

		// Set slave area.
		result = imMxicSetSlaveAreaReg( self, unit, ioMxic, slaveNumber, slaveArea );

		if ( result == D_DDIM_OK ) {
			// Change of a setup is reflected.
			mxic_utlis_on_pclk( priv->mxicUtlis, unit );

			ioMxic->TSMTRG.bit.TSMTRG = 1;

			mxic_utlis_off_pclk( priv->mxicUtlis, unit );
		}
		else {
			// Input parameter error.
			Ddim_Print(("E:mxic_master_slave_set_slave_area(): imMxicSetSlaveAreaReg error.\n"));
		}

		MxicUtlis_DSB();
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:mxic_master_slave_set_slave_area(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

/**
This function get slave area setting of specified slave number.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		slaveNumber			Slave area number.<br>
										Please refer to @ref ImMxicSlaveNumber for a set value. <br>
@param[out]		slaveArea				Slave area setting.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32 mxic_master_slave_get_slave_area( MxicMasterSlave *self, ImMxicUnit unit, 
										ImMxicSlaveNumber slaveNumber, 
										ImMxicSlaveArea* const slaveArea )
{
	INT32						result;
	volatile struct io_jdsmxic*	ioMxic;
    MxicMasterSlavePrivate *priv = MXIC_MASTER_SLAVE_GET_PRIVATE(self);

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {
		// Get slave area setting.
		result = imMxicGetSlaveAreaReg( self, unit, ioMxic, slaveNumber, slaveArea );

		if ( result != D_DDIM_OK ) {
			// Input parameter error
			Ddim_Print(("E:mxic_master_slave_get_slave_area(): imMxicGetSlaveAreaReg error.\n"));
		}
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:mxic_master_slave_get_slave_area(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

/**
This function set slave area setting of all slave number.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		allSlaveArea			Slave area setting of all slave number.<br>
@retval			D_DDIM_OK					Success
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error
*/
INT32 mxic_master_slave_set_slave_area_all( MxicMasterSlave *self, ImMxicUnit unit, 
											const MxicAllSlaveArea* const allSlaveArea )
{
	INT32						result;
	volatile struct io_jdsmxic*	ioMxic;
	INT32						i;
    MxicMasterSlavePrivate *priv = MXIC_MASTER_SLAVE_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( allSlaveArea == NULL ) {
		// allSlaveArea parameter is NULL.
		Ddim_Assertion(("E:mxic_master_slave_set_slave_area_all(): allSlaveArea is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {
		// Set all slave area.
		for ( i = MxicUtlis_SLAVE_NUMBER_1; i < MxicUtlis_SLAVE_NUMBER_MAX; i++ ) {

			result = imMxicSetSlaveAreaReg( self, unit, ioMxic, (ImMxicSlaveNumber)i, 
											&allSlaveArea->slaveArea[i] );

			if ( result != D_DDIM_OK ) {
				// Input parameter error.
				Ddim_Print(("E:mxic_master_slave_set_slave_area_all(): imMxicSetSlaveAreaReg error.\n"));
				return result;
			}
		}
		// Change of a setup is reflected.
		mxic_utlis_on_pclk( priv->mxicUtlis, unit );

		ioMxic->TSMTRG.bit.TSMTRG = 1;

		mxic_utlis_off_pclk( priv->mxicUtlis, unit );

		MxicUtlis_DSB();
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:mxic_master_slave_set_slave_area_all(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

/**
This function get slave area setting of all slave number.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[out]		allSlaveArea			Slave area setting of all slave number.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32 mxic_master_slave_get_slave_area_all( MxicMasterSlave *self, ImMxicUnit unit, 
											MxicAllSlaveArea* const allSlaveArea )
{
	INT32						result;
	volatile struct io_jdsmxic*	ioMxic;
	INT32						i;
    MxicMasterSlavePrivate *priv = MXIC_MASTER_SLAVE_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( allSlaveArea == NULL ) {
		// allSlaveArea parameter is NULL.
		Ddim_Assertion(("E:mxic_master_slave_get_slave_area_all(): allSlaveArea is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {
		// Get all slave area.
		for ( i = MxicUtlis_SLAVE_NUMBER_1; i < MxicUtlis_SLAVE_NUMBER_MAX; i++ ) {
			result = imMxicGetSlaveAreaReg( self, unit, ioMxic, (ImMxicSlaveNumber)i, 
											&allSlaveArea->slaveArea[i] );
			if ( result != D_DDIM_OK ) {
				// Input parameter error.
				Ddim_Print(("E:mxic_master_slave_get_slave_area_all(): imMxicGetSlaveAreaReg error.\n"));
				return result;
			}
		}
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:mxic_master_slave_get_slave_area_all(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

/**
This function set interruption setting of salave area decode error.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		decErrInt				Setting of decoding error interruption.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
@remarks		Please acquire error status with an mxic_master_slave_get_decode_error function 
				at the time of decode error interruption generating. 
*/
INT32 mxic_master_slave_set_decode_error_int( MxicMasterSlave *self, ImMxicUnit unit, 
											  const MxicDecErrInt* const decErrInt )
{
	INT32						result;
	volatile struct io_jdsmxic*	ioMxic;
	MxicMasterSlavePrivate *priv = MXIC_MASTER_SLAVE_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( decErrInt == NULL ) {
		// decErrInt parameter is NULL.
		Ddim_Assertion(("E:mxic_master_slave_set_decode_error_int(): decErrInt is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {
		// Set interrupt enable
		mxic_utlis_on_pclk( priv->mxicUtlis, unit );

		ioMxic->TMIE.bit.TDEWE = decErrInt->wErrIntEn;
		ioMxic->TMIE.bit.TDERE = decErrInt->rErrIntEn;

		mxic_utlis_off_pclk( priv->mxicUtlis, unit );

		// Set callback function
		priv->gImMxicDecErrCallback[unit] = decErrInt->pCallBack;

		MxicUtlis_DSB();
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:mxic_master_slave_set_decode_error_int(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

/**
This function get interruption setting of salave area decode error.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[out]		decErrInt				Setting of decoding error interruption.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32 mxic_master_slave_get_decode_error_int( MxicMasterSlave *self, ImMxicUnit unit, 
											  MxicDecErrInt* const decErrInt )
{
	INT32						result;
	volatile struct io_jdsmxic*	ioMxic;
	MxicMasterSlavePrivate *priv = MXIC_MASTER_SLAVE_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (decErrInt == NULL) {
		// decErrInt parameter is NULL.
		Ddim_Assertion(("E:mxic_master_slave_get_decode_error_int(): decErrInt is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {
		// Get interrupt enable
		mxic_utlis_on_pclk( priv->mxicUtlis, unit );

		decErrInt->wErrIntEn = ioMxic->TMIE.bit.TDEWE;
		decErrInt->rErrIntEn = ioMxic->TMIE.bit.TDERE;

		mxic_utlis_off_pclk( priv->mxicUtlis, unit );

		// Get callback function
		decErrInt->pCallBack = priv->gImMxicDecErrCallback[unit];
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:mxic_master_slave_get_decode_error_int(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

/**
This function get decode error status.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[out]		status					Decode error status.<br>
@remarks		Decode error will be notifed by the callback function that set up with the mxic_master_slave_set_decode_error_int function.<br>
				Please acquire error status with mxic_master_slave_get_decode_error function at this time.
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32 mxic_master_slave_get_decode_error( MxicMasterSlave *self, ImMxicUnit unit, ImMxicDecErr* const status )
{
	INT32						result;
	volatile struct io_jdsmxic*	ioMxic;
    MxicMasterSlavePrivate *priv = MXIC_MASTER_SLAVE_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( status == NULL ) {
		// status parameter is NULL.
		Ddim_Assertion(("E:mxic_master_slave_get_decode_error(): status is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {

		mxic_utlis_on_pclk( priv->mxicUtlis, unit );

		if ( unit != MxicUtlis_UNIT_4 ) {
			// Write channel.
			status->wReqAddr		= ioMxic->TDESTW.bit.TDEADW;
			status->wReqMaster	= ioMxic->TDESTW.bit.TDEMNW;
		}
		else {
			status->wReqAddr		= 0;
			status->wReqMaster	= 0;

			// Unit number is invalid.
			//Ddim_Print(("mxic_master_slave_get_decode_error(): unit number is invalid. unit=%d\n", unit));
		}

		if ( unit != MxicUtlis_UNIT_0 ) {
			// Read channel.
			status->rReqAddr		= ioMxic->TDESTR.bit.TDEADR;
			status->rReqMaster	= ioMxic->TDESTR.bit.TDEMNR;
		}
		else {
			status->rReqAddr		= 0;
			status->rReqMaster	= 0;

			// Unit number is invalid.
			//Ddim_Print(("mxic_master_slave_get_decode_error(): unit number is invalid. unit=%d\n", unit));
		}

		mxic_utlis_off_pclk( priv->mxicUtlis, unit );
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:mxic_master_slave_get_decode_error(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

/**
This function set the W master to the W arbiter.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		arbiter					Target write arbiter.<br>
										Please refer to @ref ImMxicWArbiter for a set value.<br>
@param[in]		assign					Setting of master assign.
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
@remarks		The setting changed by this function is reflected by the configration start.
@remarks		MxicUtlis_W_RESERVE is set to the part where the channel is not set up without fail.
*/
INT32 mxic_master_slave_set_master_w_arbiter( MxicMasterSlave *self, ImMxicUnit unit, 
											  ImMxicWArbiter arbiter, 
											  const MxicWarbiterAssignPort* const assign )
{
	INT32							result;
	volatile struct io_jdsmxic*		ioMxic;
	volatile struct io_jdsmxic_tbl*	ioMxicTbl;
	WArbiter wArgs = {unit, arbiter};
    MxicMasterSlavePrivate *priv = MXIC_MASTER_SLAVE_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (imMxicCheckSetMasterWArbiterParam( arbiter, assign ) != D_DDIM_OK ) {
		// Input parameter error.
		Ddim_Assertion(("E:mxic_master_slave_set_master_w_arbiter(): imMxicCheckSetMasterWArbiterParam error.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {

		result = mxic_utlis_get_unit_tbl_address( priv->mxicUtlis, unit, &ioMxicTbl );

		if ( result == D_DDIM_OK ) {

			mxic_utlis_wait_command_enable( priv->mxicUtlis, unit, ioMxic );	// Wait TCFLG=1.

			mxic_utlis_set_taen( priv->mxicUtlis, unit, ioMxic, TRUE );		// TAEN-ON.

			result = imMxicSetMasterWArbiterReg( self, wArgs, ioMxic, ioMxicTbl, assign );

			if ( result == D_DDIM_OK ) {

				mxic_utlis_process_configuration( priv->mxicUtlis, unit, ioMxic );

			}

			mxic_utlis_set_taen( priv->mxicUtlis, unit, ioMxic, FALSE );	// TAEN-OFF.
		}
		else {
			// Input parameter error.
			//Ddim_Print(("E:mxic_master_slave_set_master_w_arbiter(): mxic_utlis_get_unit_tbl_address error.\n"));
			result = D_DDIM_OK;
		}
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:mxic_master_slave_set_master_w_arbiter(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

/**
This function get the W master from the W arbiter.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		arbiter					Target write arbiter.<br>
										Please refer to @ref ImMxicWArbiter for a set value.<br>
@param[out]		assign					Setting of master assign.
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32 mxic_master_slave_get_master_w_arbiter( MxicMasterSlave *self, ImMxicUnit unit, ImMxicWArbiter arbiter, 
											  MxicWarbiterAssignPort* const assign )
{
	INT32							i, j;
	INT32							result;
	volatile struct io_jdsmxic*		ioMxic;
	volatile struct io_jdsmxic_tbl*	ioMxicTbl;
    MxicMasterSlavePrivate *priv = MXIC_MASTER_SLAVE_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( imMxicCheckGetMasterWArbiterParam( arbiter, assign ) != D_DDIM_OK ) {
		// Input parameter error.
		Ddim_Assertion(("E:mxic_master_slave_get_master_w_arbiter(): imMxicCheckGetMasterWArbiterParam error.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {

		result = mxic_utlis_get_unit_tbl_address( priv->mxicUtlis, unit, &ioMxicTbl );

		if ( result == D_DDIM_OK ) {

			mxic_utlis_wait_command_enable( priv->mxicUtlis, unit, ioMxic );	// Wait TCFLG=1.

			mxic_utlis_set_taen( priv->mxicUtlis, unit, ioMxic, TRUE );		// TAEN-ON

			if ( unit == MxicUtlis_UNIT_3 ) {
				DDIM_User_AhbReg_SpinLock();					// JPEG issue work around.
			}

			mxic_utlis_on_hclk( priv->mxicUtlis, unit );

			for ( i = MxicUtlis_PORT_0; i < MxicUtlis_PORT_MAX; i++ ) {

				for ( j = 0; j < MxicUtlis_SLOT_SIZE_8; j++ ) {

					switch ( arbiter ) {
						case MxicUtlis_W_ARBITER_W1:
							assign->port[i].slot0[j] = ioMxicTbl->TSLW_1[i].byte[MxicUtlis_SLOT_0][j];
							assign->port[i].slot1[j] = ioMxicTbl->TSLW_1[i].byte[MxicUtlis_SLOT_1][j];
							assign->port[i].slot2[j] = ioMxicTbl->TSLW_1[i].byte[MxicUtlis_SLOT_2][j];
							assign->port[i].slot3[j] = ioMxicTbl->TSLW_1[i].byte[MxicUtlis_SLOT_3][j];
							break;
						case MxicUtlis_W_ARBITER_W2:
							assign->port[i].slot0[j] = ioMxicTbl->TSLW_2[i].byte[MxicUtlis_SLOT_0][j];
							assign->port[i].slot1[j] = ioMxicTbl->TSLW_2[i].byte[MxicUtlis_SLOT_1][j];
							assign->port[i].slot2[j] = ioMxicTbl->TSLW_2[i].byte[MxicUtlis_SLOT_2][j];
							assign->port[i].slot3[j] = ioMxicTbl->TSLW_2[i].byte[MxicUtlis_SLOT_3][j];
							break;
						case MxicUtlis_W_ARBITER_W3:
							assign->port[i].slot0[j] = ioMxicTbl->TSLW_3[i].byte[MxicUtlis_SLOT_0][j];
							assign->port[i].slot1[j] = ioMxicTbl->TSLW_3[i].byte[MxicUtlis_SLOT_1][j];
							assign->port[i].slot2[j] = ioMxicTbl->TSLW_3[i].byte[MxicUtlis_SLOT_2][j];
							assign->port[i].slot3[j] = ioMxicTbl->TSLW_3[i].byte[MxicUtlis_SLOT_3][j];
							break;
						case MxicUtlis_W_ARBITER_W4:
							assign->port[i].slot0[j] = ioMxicTbl->TSLW_4[i].byte[MxicUtlis_SLOT_0][j];
							assign->port[i].slot1[j] = ioMxicTbl->TSLW_4[i].byte[MxicUtlis_SLOT_1][j];
							assign->port[i].slot2[j] = ioMxicTbl->TSLW_4[i].byte[MxicUtlis_SLOT_2][j];
							assign->port[i].slot3[j] = ioMxicTbl->TSLW_4[i].byte[MxicUtlis_SLOT_3][j];
							break;
						default:
							// arbiter is illegal.
							result = MxicUtlis_INPUT_PARAM_ERROR;
							Ddim_Print(("E:mxic_master_slave_get_master_w_arbiter(): arbiter is illegal. arbiter=%d\n", 
										arbiter));
							break;
					}
				}
			}

			mxic_utlis_off_hclk( priv->mxicUtlis, unit );

			if ( unit == MxicUtlis_UNIT_3 ) {
				DDIM_User_AhbReg_SpinUnLock();				// JPEG issue work around.
			}

			mxic_utlis_set_taen( priv->mxicUtlis, unit, ioMxic, FALSE );	// TAEN-OFF.
		}
		else {
			// Input parameter error.
			//Ddim_Print(("E:mxic_master_slave_get_master_w_arbiter(): mxic_utlis_get_unit_tbl_address error.\n"));
			result = D_DDIM_OK;
		}
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:mxic_master_slave_get_master_w_arbiter(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

/**
This function set the R master to the R arbiter.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		arbiter					Target read arbiter.<br>
										Please refer to @ref ImMxicRArbiter for a set value.<br>
@param[in]		assign					Setting of master assign.
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
@remarks		The setting changed by this function is reflected by the configration start.
@remarks		MxicUtlis_R_RESERVE is set to the part where the channel is not set up without fail.
*/
INT32 mxic_master_slave_set_master_r_arbiter( MxicMasterSlave *self, ImMxicUnit unit, ImMxicRArbiter arbiter, 
											  const MxicRarbiterAssignPort* const assign )
{
	INT32							result;
	volatile struct io_jdsmxic*		ioMxic;
	volatile struct io_jdsmxic_tbl*	ioMxicTbl;
	RArbiter rArgs = {unit, arbiter};
    MxicMasterSlavePrivate *priv = MXIC_MASTER_SLAVE_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( imMxicCheckSetMasterRArbiterParam( arbiter, assign ) != D_DDIM_OK ) {
		// Input parameter error
		Ddim_Assertion(("E:mxic_master_slave_set_master_r_arbiter(): imMxicCheckSetMasterRArbiterParam error.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {

		result = mxic_utlis_get_unit_tbl_address( priv->mxicUtlis, unit, &ioMxicTbl );

		if ( result == D_DDIM_OK ) {

			mxic_utlis_wait_command_enable( priv->mxicUtlis, unit, ioMxic );	// Wait TCFLG=1.

			mxic_utlis_set_taen( priv->mxicUtlis, unit, ioMxic, TRUE );		// TAEN-ON.

			result = imMxicSetMasterRArbiterReg( self, rArgs, ioMxic, ioMxicTbl, assign );

			if ( result == D_DDIM_OK ) {

				// Configuration start.
				mxic_utlis_process_configuration( priv->mxicUtlis, unit, ioMxic );
			}

			mxic_utlis_set_taen( priv->mxicUtlis, unit, ioMxic, FALSE );	// TAEN-OFF.
		}
		else {
			// Input parameter error.
			//Ddim_Print(("E:mxic_master_slave_set_master_r_arbiter(): mxic_utlis_get_unit_tbl_address error.\n"));
			result = D_DDIM_OK;
		}
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:mxic_master_slave_set_master_r_arbiter(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

/**
This function get the R master from the R arbiter.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		arbiter					Target read arbiter.<br>
										Please refer to @ref ImMxicRArbiter for a set value.<br>
@param[out]		assign					Setting of master assign.
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32 mxic_master_slave_get_master_r_arbiter( MxicMasterSlave *self, ImMxicUnit unit, ImMxicRArbiter arbiter, 
											  MxicRarbiterAssignPort* const assign )
{
	INT32							i, j;
	INT32							result;
	volatile struct io_jdsmxic*		ioMxic;
	volatile struct io_jdsmxic_tbl*	ioMxicTbl;
    MxicMasterSlavePrivate *priv = MXIC_MASTER_SLAVE_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( imMxicCheckGetMasterRArbiterParam( arbiter, assign ) != D_DDIM_OK ) {
		// Input parameter error.
		Ddim_Assertion(("E:mxic_master_slave_get_master_r_arbiter(): imMxicCheckGetMasterRArbiterParam error.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {

		result = mxic_utlis_get_unit_tbl_address( priv->mxicUtlis, unit, &ioMxicTbl );

		if ( result == D_DDIM_OK ) {

			mxic_utlis_wait_command_enable( priv->mxicUtlis, unit, ioMxic );	// Wait TCFLG=1.

			mxic_utlis_set_taen( priv->mxicUtlis, unit, ioMxic, TRUE );		// TAEN-ON.

			if ( unit == MxicUtlis_UNIT_3 ) {
				DDIM_User_AhbReg_SpinLock();					// JPEG issue work around.
			}

			mxic_utlis_on_hclk( priv->mxicUtlis, unit );

			for ( i = MxicUtlis_PORT_0; i < MxicUtlis_PORT_MAX; i++ ) {

				for ( j = 0; j < MxicUtlis_SLOT_SIZE_8; j++ ) {

					switch ( arbiter ) {
						case MxicUtlis_R_ARBITER_R1:
							assign->port[i].slot0[j] = ioMxicTbl->TSLR_1[i].byte[MxicUtlis_SLOT_0][j];
							assign->port[i].slot1[j] = ioMxicTbl->TSLR_1[i].byte[MxicUtlis_SLOT_1][j];
							assign->port[i].slot2[j] = ioMxicTbl->TSLR_1[i].byte[MxicUtlis_SLOT_2][j];
							assign->port[i].slot3[j] = ioMxicTbl->TSLR_1[i].byte[MxicUtlis_SLOT_3][j];
							break;
						case MxicUtlis_R_ARBITER_R2:
							assign->port[i].slot0[j] = ioMxicTbl->TSLR_2[i].byte[MxicUtlis_SLOT_0][j];
							assign->port[i].slot1[j] = ioMxicTbl->TSLR_2[i].byte[MxicUtlis_SLOT_1][j];
							assign->port[i].slot2[j] = ioMxicTbl->TSLR_2[i].byte[MxicUtlis_SLOT_2][j];
							assign->port[i].slot3[j] = ioMxicTbl->TSLR_2[i].byte[MxicUtlis_SLOT_3][j];
							break;
						case MxicUtlis_R_ARBITER_R3:
							assign->port[i].slot0[j] = ioMxicTbl->TSLR_3[i].byte[MxicUtlis_SLOT_0][j];
							assign->port[i].slot1[j] = ioMxicTbl->TSLR_3[i].byte[MxicUtlis_SLOT_1][j];
							assign->port[i].slot2[j] = ioMxicTbl->TSLR_3[i].byte[MxicUtlis_SLOT_2][j];
							assign->port[i].slot3[j] = ioMxicTbl->TSLR_3[i].byte[MxicUtlis_SLOT_3][j];
							break;
						case MxicUtlis_R_ARBITER_R4:
							assign->port[i].slot0[j] = ioMxicTbl->TSLR_4[i].byte[MxicUtlis_SLOT_0][j];
							assign->port[i].slot1[j] = ioMxicTbl->TSLR_4[i].byte[MxicUtlis_SLOT_1][j];
							assign->port[i].slot2[j] = ioMxicTbl->TSLR_4[i].byte[MxicUtlis_SLOT_2][j];
							assign->port[i].slot3[j] = ioMxicTbl->TSLR_4[i].byte[MxicUtlis_SLOT_3][j];
							break;
						default:
							// arbiter is illegal.
							result = MxicUtlis_INPUT_PARAM_ERROR;
							Ddim_Print(("E:mxic_master_slave_get_master_r_arbiter(): arbiter is illegal. arbiter=%d\n", 
									arbiter));
							break;
					}
				}
			}

			mxic_utlis_off_hclk( priv->mxicUtlis, unit );

			if ( unit == MxicUtlis_UNIT_3 ) {
				DDIM_User_AhbReg_SpinUnLock();			// JPEG issue work around.
			}

			mxic_utlis_set_taen( priv->mxicUtlis, unit, ioMxic, FALSE );	// TAEN-OFF.
		}
		else {
			// Input parameter error.
			//Ddim_Print(("E:mxic_master_slave_get_master_r_arbiter(): mxic_utlis_get_unit_tbl_address error.\n"));
			result = D_DDIM_OK;
		}
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:mxic_master_slave_get_master_r_arbiter(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

/**
This function set the master to the all arbiter.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		allAssign		 		Setting of master assign.
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
@remarks		The setting changed by this function is reflected by the configration start.
*/
INT32 mxic_master_slave_set_master_all_arbiter( MxicMasterSlave *self, ImMxicUnit unit, 
												const MxicAllArbiterAssign* const allAssign )
{
	INT32							i;
	INT32							result;
	volatile struct io_jdsmxic*		ioMxic;
	volatile struct io_jdsmxic_tbl*	ioMxicTbl;
	WArbiter wArgs;
	RArbiter rArgs;
    MxicMasterSlavePrivate *priv = MXIC_MASTER_SLAVE_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( allAssign == NULL ) {
		// allAssign parameter is NULL.
		Ddim_Assertion(("E:mxic_master_slave_set_master_all_arbiter(): allAssign is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {

		result = mxic_utlis_get_unit_tbl_address( priv->mxicUtlis, unit, &ioMxicTbl );

		if ( result == D_DDIM_OK ) {

			mxic_utlis_wait_command_enable( priv->mxicUtlis, unit, ioMxic );	// Wait TCFLG=1.

			mxic_utlis_set_taen( priv->mxicUtlis, unit, ioMxic, TRUE );		// TAEN-ON.

			for ( i = MxicUtlis_W_ARBITER_W1; i < MxicUtlis_W_ARBITER_MAX; i++ ) {
				wArgs.unit = unit;
				wArgs.arbiter = (ImMxicWArbiter)i;
				result = imMxicSetMasterWArbiterReg( self, wArgs, ioMxic, ioMxicTbl, (&allAssign->wArbiter[i]) );

				if ( result != D_DDIM_OK ) {
					// Error occurred by the master allocation to W1 arbiter. 
					Ddim_Print(("E:mxic_master_slave_set_master_all_arbiter(): W%d error.\n", i+1));
					return result;
				}
			}

			for ( i = MxicUtlis_R_ARBITER_R1; i < MxicUtlis_R_ARBITER_MAX; i++ ) {
				rArgs.unit = unit;
				rArgs.arbiter = (ImMxicRArbiter)i;
				result = imMxicSetMasterRArbiterReg( self, rArgs, ioMxic, ioMxicTbl, (&allAssign->rArbiter[i]) );

				if ( result != D_DDIM_OK ) {
					// Error occurred by the master allocation to R1 arbiter. 
					Ddim_Print(("E:mxic_master_slave_set_master_all_arbiter(): R%d error.\n", i+1));
					return result;
				}
			}

			mxic_utlis_process_configuration( priv->mxicUtlis, unit, ioMxic );

			mxic_utlis_set_taen( priv->mxicUtlis, unit, ioMxic, FALSE );	// TAEN-OFF.
		}
		else {
			// Input parameter error.
			//Ddim_Print(("E:mxic_master_slave_set_master_all_arbiter(): mxic_utlis_get_unit_tbl_address error.\n"));
			result = D_DDIM_OK;
		}
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:mxic_master_slave_set_master_all_arbiter(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

/**
This function get the master from the all arbiter.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[out]		allAssign		 		Setting of master assign.
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32 mxic_master_slave_get_master_all_arbiter( MxicMasterSlave *self, ImMxicUnit unit, 
												MxicAllArbiterAssign* const allAssign )
{
	INT32 i;
	INT32 result;

#ifdef CO_PARAM_CHECK
	if ( allAssign == NULL ) {
		// allAssign parameter is NULL.
		Ddim_Assertion(("E:mxic_master_slave_get_master_all_arbiter(): allAssign is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	for ( i = MxicUtlis_W_ARBITER_W1; i < MxicUtlis_W_ARBITER_MAX; i++ ) {

		result = mxic_master_slave_get_master_w_arbiter( self, unit, (ImMxicWArbiter)i, 
														 (&allAssign->wArbiter[i]) );

		if ( result != D_DDIM_OK ) {
			// Error occurred by acquiring the master allocation setting of W1 arbiter. 
			Ddim_Print(("E:mxic_master_slave_get_master_all_arbiter(): W%d error.\n", i+1));
			return result;
		}
	}

	for ( i = MxicUtlis_R_ARBITER_R1; i < MxicUtlis_R_ARBITER_MAX; i++ ) {

		result = mxic_master_slave_get_master_r_arbiter( self, unit, (ImMxicRArbiter)i, 
														 (&allAssign->rArbiter[i]) );

		if ( result != D_DDIM_OK ) {
			// Error occurred by acquiring the master allocation setting of R1 arbiter. 
			Ddim_Print(("E:mxic_master_slave_get_master_all_arbiter(): R%d error.\n", i+1));
			return result;
		}
	}

	return D_DDIM_OK;
}

void mxic_master_slave_for_dec_err(MxicMasterSlave *self, ImMxicUnit unit, INT32 decErrCh)
{
	MxicMasterSlavePrivate *priv = MXIC_MASTER_SLAVE_GET_PRIVATE(self);
	if ( priv->gImMxicDecErrCallback[unit] != NULL ) {
		((VOID (*)()) priv->gImMxicDecErrCallback[unit])( decErrCh );
	}
}

MxicMasterSlave *mxic_master_slave_new(void)
{
    MxicMasterSlave* self = k_object_new_with_private(MXIC_TYPE_MASTER_SLAVE, sizeof(MxicMasterSlavePrivate));
    return self;
}
