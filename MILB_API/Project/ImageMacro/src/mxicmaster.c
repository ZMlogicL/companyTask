/***********************************************************************
 * @Copyright(C) 上海网用软件有限公司
 * @file mxicmaster.c
 * @date 2020-09-02
 * @author: 吴海辉
 * @brief: 
 * @version: 1.0.0
***********************************************************************/

#include "mxicmaster.h"


K_TYPE_DEFINE_WITH_PRIVATE(MxicMaster, mxic_master)
#define MXIC_MASTER_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), MxicMasterPrivate, MXIC_TYPE_MASTER))

// TRMC*.TRMFT* bit flag
#define MxicMaster_TRMC_TRMFT_A_FACTOR		(0x00000001)	// Mask factor A group
#define MxicMaster_TRMC_TRMFT_A_TARGET		(0x00000002)	// Mask target A group
#define MxicMaster_TRMC_TRMFT_B_FACTOR		(0x00000004)	// Mask factor B group
#define MxicMaster_TRMC_TRMFT_B_TARGET		(0x00000008)	// Mask target B group
#define MxicMaster_TRMC_TRMFT_SELECT		(0x00000010)	// Mask state select

// TRMC*.TISULIM* bit value
#define MxicMaster_TRMC_TISULIM_MIN_VAL		(0)				// Minimum value of transaction
#define MxicMaster_TRMC_TISULIM_MAX_VAL		(63)			// Mzximum value of transaction


/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
// Operation type (Set/Get)
typedef enum {
	MxicMaster_OPERATION_TYPE_SET,			// Set operation
	MxicMaster_OPERATION_TYPE_GET			// Get operation
} MxicMasterOperationType;

// Master mask operation type (Factor/Target)
typedef enum {
	MxicMaster_MASK_OPERATION_FACTOR,	// Factor
	MxicMaster_MASK_OPERATION_TARGET	// Target
} MxicMasterMaskOperation;


// Master mask factor and target configration
typedef struct {
	MxicMasterOperationType		kindSetGet;			// Operation type (Set/Get)
	MxicMasterMaskOperation		kindFactorTarget;	// Master mask operation type (Factor/Target)
	UCHAR						master;				// Master number.
	ImMxicMaskGroup			group;				// Mask group.
	UCHAR						enable;				// Setting of whether to make a master into a mask factor(target).
} MxicMasterMaskFactorTarget;

struct _MxicMasterPrivate
{
    MxicUtlis* mxicUtlis;
};


/*----------------------------------------------------------------------*/
/* DECLS  															    */
/*----------------------------------------------------------------------*/
static INT32 imMxicRwMasterMaskFactorOrTarget( MxicMaster *self, ImMxicUnit unit, 
												MxicMasterMaskFactorTarget* const config );
#ifdef CO_PARAM_CHECK
static INT32 imMxicCheckMasterMaskFactorTargetParam( MxicMasterOperationType operation, 
													UCHAR master, ImMxicMaskGroup group, UCHAR* const enable );
#endif // CO_PARAM_CHECK


/*----------------------------------------------------------------------*/
/* IMPL  															    */
/*----------------------------------------------------------------------*/
static void mxic_master_constructor(MxicMaster *self)
{
    MxicMasterPrivate *priv = MXIC_MASTER_GET_PRIVATE(self);

	priv->mxicUtlis = mxic_utlis_new();
}

static void mxic_master_destructor(MxicMaster *self)
{
    MxicMasterPrivate *priv = MXIC_MASTER_GET_PRIVATE(self);

	if(priv->mxicUtlis)
	{
		k_object_unref(priv->mxicUtlis);
		priv->mxicUtlis = NULL;
	}
}

/**
This function operates the factor of a master mask, and the target.
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in/out]	config					Master mask factor and target configration.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
static INT32 imMxicRwMasterMaskFactorOrTarget( MxicMaster *self, ImMxicUnit unit, 
												MxicMasterMaskFactorTarget* const config )
{
	INT32						result;
	INT32						operate_bit;
	INT32						compare_bit;
	UCHAR						readMaster;
	volatile struct io_jdsmxic*	ioMxic;
    MxicMasterPrivate *priv = MXIC_MASTER_GET_PRIVATE(self);

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {
		// Decide operation target bit.
		if ( config->kindFactorTarget == MxicMaster_MASK_OPERATION_FACTOR ) {
			// Mask factor operation.
			if ( config->group == MxicUtlis_MASK_GROUP_A ) {
				// Group-A.
				operate_bit = MxicMaster_TRMC_TRMFT_A_FACTOR;
				compare_bit = MxicMaster_TRMC_TRMFT_A_TARGET;
			}
			else {
				// Group-B.
				operate_bit = MxicMaster_TRMC_TRMFT_B_FACTOR;
				compare_bit = MxicMaster_TRMC_TRMFT_B_TARGET;
			}
		}
		else {
			// Mask target operation.
			if (config->group == MxicUtlis_MASK_GROUP_A) {
				// Group-A.
				operate_bit = MxicMaster_TRMC_TRMFT_A_TARGET;
				compare_bit = MxicMaster_TRMC_TRMFT_A_FACTOR;
			}
			else {
				// Group-B.
				operate_bit = MxicMaster_TRMC_TRMFT_B_TARGET;
				compare_bit = MxicMaster_TRMC_TRMFT_B_FACTOR;
			}
		}

		if ( ( config->master & MxicUtlis_MASTER_TYPE_CHECK_MASK ) == MxicUtlis_MASTER_TYPE_WRITE ) {
			// Write master.
			if ( config->master < MxicUtlis_MASTER_NUMBER_MAX ) {

				if ( unit != MxicUtlis_UNIT_4 ) {

					mxic_utlis_on_pclk( priv->mxicUtlis, unit );

					if ( config->kindSetGet == MxicMaster_OPERATION_TYPE_SET ) {
						// Set operation.
						if ( ( config->enable == MxicUtlis_ON ) && ( ( ioMxic->TRMCW[(config->master - 1)].bit.TRMFTW & compare_bit ) == 0 ) ) {
							// Set mask factor(target) ON. **The same channel can't be set to the factor and the target.
							ioMxic->TRMCW[(config->master - 1)].bit.TRMFTW |= operate_bit;				// W1-63.
						}
						else if ( config->enable == MxicUtlis_OFF ) {
							// Set mask factor(target) OFF.
							ioMxic->TRMCW[(config->master - 1)].bit.TRMFTW &= (~operate_bit);			// W1-63.
						}
						else {
							// Error.
							Ddim_Print(("E:imMxicRwMasterMaskFactorOrTarget(): Write master mask setting is illegal.\n"));
							result = MxicUtlis_INPUT_PARAM_ERROR;
						}
					}
					else {
						// Get operation.
						if ( ( ioMxic->TRMCW[(config->master - 1)].bit.TRMFTW & operate_bit ) != 0 ) {	// W1-63.
							config->enable = MxicUtlis_ON;
						}
						else {
							config->enable = MxicUtlis_OFF;
						}
					}

					mxic_utlis_off_pclk( priv->mxicUtlis, unit );
				}
				else {
					// Unit number is invalid.
//					Ddim_Print(("imMxicRwMasterMaskFactorOrTarget(): unit number is invalid. unit=%d\n", unit));
				}
			}
			else {
				if ( unit == MxicUtlis_UNIT_3 ) {

					config->master = config->master - MxicUtlis_MASTER_NUMBER_MAX;

					mxic_utlis_on_pclk( priv->mxicUtlis, unit );

					if ( config->kindSetGet == MxicMaster_OPERATION_TYPE_SET ) {
						// Set operation.
						if ( ( config->enable == MxicUtlis_ON ) && ( ( ioMxic->TRMCW_GR[config->master].bit.TRMFTW & compare_bit ) == 0 ) ) {
							// Set mask factor(target) ON. **The same channel can't be set to the factor and the target.
							ioMxic->TRMCW_GR[config->master].bit.TRMFTW |= operate_bit;				// W64-127.
						}
						else if ( config->enable == MxicUtlis_OFF ) {
							// Set mask factor(target) OFF.
							ioMxic->TRMCW_GR[config->master].bit.TRMFTW &= (~operate_bit);				// W64-127.
						}
						else {
							// Error.
							Ddim_Print(("E:imMxicRwMasterMaskFactorOrTarget(): Write master mask setting is illegal.\n"));
							result = MxicUtlis_INPUT_PARAM_ERROR;
						}
					}
					else {
						// Get operation.
						if ( ( ioMxic->TRMCW_GR[config->master].bit.TRMFTW & operate_bit ) != 0 ) {	// W64-127.
							config->enable = MxicUtlis_ON;
						}
						else {
							config->enable = MxicUtlis_OFF;
						}
					}

					mxic_utlis_off_pclk( priv->mxicUtlis, unit );
				}
				else {
					// Unit number is invalid.
//					Ddim_Print(("imMxicRwMasterMaskFactorOrTarget(): unit number is invalid. unit=%d\n", unit));
				}
			}
		}
		else if ( ( config->master & MxicUtlis_MASTER_TYPE_CHECK_MASK ) == MxicUtlis_MASTER_TYPE_READ ) {
			// Read master.
			readMaster = ( config->master & MxicUtlis_READ_MASTER_FLG_MASK );

			if ( readMaster < MxicUtlis_MASTER_NUMBER_MAX ) {

				if ( unit != MxicUtlis_UNIT_0 ) {

					mxic_utlis_on_pclk( priv->mxicUtlis, unit );

					if ( config->kindSetGet == MxicMaster_OPERATION_TYPE_SET ) {
						// Set operation.
						if ( ( config->enable == MxicUtlis_ON ) && ( ( ioMxic->TRMCR[(readMaster - 1)].bit.TRMFTR & compare_bit ) == 0 ) ) {
							// Set mask factor(target) ON. **The same channel can't be set to the factor and the target.
							ioMxic->TRMCR[(readMaster - 1)].bit.TRMFTR |= operate_bit;				// R1-63.
						}
						else if ( config->enable == MxicUtlis_OFF ) {
							// Set mask factor(target) OFF.
							ioMxic->TRMCR[(readMaster - 1)].bit.TRMFTR &= (~operate_bit);				// R1-63.
						}
						else {
							// Error.
							Ddim_Print(("E:imMxicRwMasterMaskFactorOrTarget(): Read master mask setting is illegal.\n"));
							result = MxicUtlis_INPUT_PARAM_ERROR;
						}
					}
					else {
						// Get operation.
						if ( ( ioMxic->TRMCR[(readMaster - 1)].bit.TRMFTR & operate_bit ) != 0 ) {	// R1-63.
							config->enable = MxicUtlis_ON;
						}
						else {
							config->enable = MxicUtlis_OFF;
						}
					}

					mxic_utlis_off_pclk( priv->mxicUtlis, unit );
				}
				else {
					// Unit number is invalid.
//					Ddim_Print(("imMxicRwMasterMaskFactorOrTarget(): unit number is invalid. unit=%d\n", unit));
				}
			}
			else {
				if ( unit == MxicUtlis_UNIT_3 ) {

					readMaster = readMaster - MxicUtlis_MASTER_NUMBER_MAX;

					mxic_utlis_on_pclk( priv->mxicUtlis, unit );

					if ( config->kindSetGet == MxicMaster_OPERATION_TYPE_SET ) {
						// Set operation.
						if ( ( config->enable == MxicUtlis_ON ) && ( ( ioMxic->TRMCR_GR[readMaster].bit.TRMFTR & compare_bit ) == 0 ) ) {
							// Set mask factor(target) ON. **The same channel can't be set to the factor and the target.
							ioMxic->TRMCR_GR[readMaster].bit.TRMFTR |= operate_bit;				// R64-127.
						}
						else if ( config->enable == MxicUtlis_OFF ) {
							// Set mask factor(target) OFF.
							ioMxic->TRMCR_GR[readMaster].bit.TRMFTR &= (~operate_bit);			// R64-127.
						}
						else {
							// Error.
							Ddim_Print(("E:imMxicRwMasterMaskFactorOrTarget(): Read master mask setting is illegal.\n"));
							result = MxicUtlis_INPUT_PARAM_ERROR;
						}
					}
					else {
						// Get operation.
						if ( ( ioMxic->TRMCR_GR[readMaster].bit.TRMFTR & operate_bit ) != 0 ) {	// R64-127.
							config->enable = MxicUtlis_ON;
						}
						else {
							config->enable = MxicUtlis_OFF;
						}
						
					}

					mxic_utlis_off_pclk( priv->mxicUtlis, unit );
				}
				else {
					// Unit number is invalid.
//					Ddim_Print(("imMxicRwMasterMaskFactorOrTarget(): unit number is invalid. unit=%d\n", unit));
				}
			}
		}
		else {
			// Master number is illegal.
			Ddim_Print(("E:imMxicRwMasterMaskFactorOrTarget(): Master number is illegal. master=%d\n", config->master));
			result = MxicUtlis_INPUT_PARAM_ERROR;
		}
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:imMxicRwMasterMaskFactorOrTarget(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

#ifdef CO_PARAM_CHECK
/**
Check parameter of function that operates master mask factor and target.<br>
@param[in]		operation				Operation type.(Set/Get)<br>
@param[in]		master					Master number.<br>
@param[in]		group					Mask group.<br>
@param[in]		enable					Setting of whether to make a master into a mask factor.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
static INT32 imMxicCheckMasterMaskFactorTargetParam( MxicMasterOperationType operation, 
													UCHAR master, ImMxicMaskGroup group, UCHAR* const enable )
{
	if ( group >= MxicUtlis_MASK_GROUP_MAX ) {
		// Group is illegal.
		Ddim_Print(("E:imMxicCheckMasterMaskFactorTargetParam(): group is illegal. group=%d\n", group));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
	if ( enable == NULL ) {
		// enable is NULL.
		Ddim_Print(("E:imMxicCheckMasterMaskFactorTargetParam(): enable is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
	if ( operation == MxicMaster_OPERATION_TYPE_SET ) {
		if ( ( *enable != MxicUtlis_ON ) && ( *enable != MxicUtlis_OFF ) ) {
			// enable parameter value is illegal.
			Ddim_Print(("E:imMxicCheckMasterMaskFactorTargetParam(): enable is illegal. enable=%d\n", *enable));
			return MxicUtlis_INPUT_PARAM_ERROR;
		}
	}

	return D_DDIM_OK;
}
#endif // CO_PARAM_CHECK


/*----------------------------------------------------------------------*/
/* PUBLIC  															    */
/*----------------------------------------------------------------------*/
/**
This function set the movement position after the master process.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		master					Master number.<br>
@param[in]		priority				Master priority level.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32 mxic_master_set_master_priority( MxicMaster *self, ImMxicUnit unit, UCHAR master, UCHAR priority )
{
	INT32						result;
	volatile struct io_jdsmxic*	ioMxic;
    MxicMasterPrivate *priv = MXIC_MASTER_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( priority > MxicUtlis_MASTER_MOVE_15 ) {
		// priority parameter value is illegal.
		Ddim_Assertion(("E:mxic_master_set_master_priority(): priority is illegal. priority=%d\n", priority));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {

		if ( ( master & MxicUtlis_MASTER_TYPE_CHECK_MASK ) == MxicUtlis_MASTER_TYPE_WRITE ) {

			if ( master < MxicUtlis_MASTER_NUMBER_MAX ) {

				if ( unit != MxicUtlis_UNIT_4 ) {
					// Set master priority level of write master.
					mxic_utlis_on_pclk( priv->mxicUtlis, unit );

					ioMxic->TRMCW[(master - 1)].bit.TRPW	= priority;		// W1-63.

					mxic_utlis_off_pclk( priv->mxicUtlis, unit );
				}
				else {
					// Unit number is invalid.
					//Ddim_Print(("mxic_master_set_master_priority(): unit number is invalid. unit=%d\n", unit));
				}
			}
			else {
				if ( unit == MxicUtlis_UNIT_3 ) {
					// Set master priority level of write master.
					master = master - MxicUtlis_MASTER_NUMBER_MAX;

					mxic_utlis_on_pclk( priv->mxicUtlis, unit );

					ioMxic->TRMCW_GR[master].bit.TRPW		= priority;		// W64-127.

					mxic_utlis_off_pclk( priv->mxicUtlis, unit );
				}
				else {
					// Unit number is invalid.
					//Ddim_Print(("mxic_master_set_master_priority(): unit number is invalid. unit=%d\n", unit));
				}
			}
		}
		else if ( (master & MxicUtlis_MASTER_TYPE_CHECK_MASK ) == MxicUtlis_MASTER_TYPE_READ ) {

			master &= MxicUtlis_READ_MASTER_FLG_MASK;

			if ( master < MxicUtlis_MASTER_NUMBER_MAX ) {

				if ( unit != MxicUtlis_UNIT_0 ) {
					// Set master priority level of read master.
					mxic_utlis_on_pclk( priv->mxicUtlis, unit );

					ioMxic->TRMCR[(master - 1)].bit.TRPR	= priority;		// R1-63.

					mxic_utlis_off_pclk( priv->mxicUtlis, unit );
				}
				else {
					// Unit number is invalid.
//					Ddim_Print(("mxic_master_set_master_priority(): unit number is invalid. unit=%d\n", unit));
				}
			}
			else {
				if ( unit == MxicUtlis_UNIT_3 ) {
					// Set master priority level of read master.
					master = master - MxicUtlis_MASTER_NUMBER_MAX;

					mxic_utlis_on_pclk( priv->mxicUtlis, unit );

					ioMxic->TRMCR_GR[master].bit.TRPR		= priority;		// R64-127.

					mxic_utlis_off_pclk( priv->mxicUtlis, unit );
				}
				else {
					// Unit number is invalid.
					//Ddim_Print(("mxic_master_set_master_priority(): unit number is invalid. unit=%d\n", unit));
				}
			}
		}
		else {
			// Master number is illegal.
			Ddim_Print(("E:mxic_master_set_master_priority(): master is illegal. master=%d\n", master));
			result = MxicUtlis_INPUT_PARAM_ERROR;
		}

		MxicUtlis_DSB();
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:mxic_master_set_master_priority(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

/**
This function get the movement position after the master process.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		master					Master number.<br>
@param[out]		priority				Master priority level.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32 mxic_master_get_master_priority( MxicMaster *self, ImMxicUnit unit, UCHAR master, UCHAR* const priority )
{
	INT32						result;
	volatile struct io_jdsmxic*	ioMxic;
    MxicMasterPrivate *priv = MXIC_MASTER_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( priority == NULL ) {
		// priority parameter is NULL.
		Ddim_Assertion(("E:mxic_master_get_master_priority(): priority is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {

		if ( ( master & MxicUtlis_MASTER_TYPE_CHECK_MASK ) == MxicUtlis_MASTER_TYPE_WRITE ) {

			if ( master < MxicUtlis_MASTER_NUMBER_MAX ) {

				if ( unit != MxicUtlis_UNIT_4 ) {
					// Get master priority level of write master.
					mxic_utlis_on_pclk( priv->mxicUtlis, unit );

					*priority = ioMxic->TRMCW[(master - 1)].bit.TRPW;	// W1-63.

					mxic_utlis_off_pclk( priv->mxicUtlis, unit );
				}
				else {
					*priority = 0;

					// Unit number is invalid.
					//Ddim_Print(("mxic_master_get_master_priority(): unit number is invalid. unit=%d\n", unit));
				}
			}
			else {
				if ( unit == MxicUtlis_UNIT_3 ) {
					// Get master priority level of write master.
					master = master - MxicUtlis_MASTER_NUMBER_MAX;

					mxic_utlis_on_pclk( priv->mxicUtlis, unit );

					*priority = ioMxic->TRMCW_GR[master].bit.TRPW;		// W64-127.

					mxic_utlis_off_pclk( priv->mxicUtlis, unit );
				}
				else {
					*priority = 0;

					// Unit number is invalid.
					//Ddim_Print(("mxic_master_get_master_priority(): unit number is invalid. unit=%d\n", unit));
				}
			}
		}
		else if( ( master & MxicUtlis_MASTER_TYPE_CHECK_MASK ) == MxicUtlis_MASTER_TYPE_READ ) {

			master &= MxicUtlis_READ_MASTER_FLG_MASK;

			if ( master < MxicUtlis_MASTER_NUMBER_MAX ) {

				if ( unit != MxicUtlis_UNIT_0 ) {
					// Get master priority level of read master.
					mxic_utlis_on_pclk( priv->mxicUtlis, unit );

					*priority = ioMxic->TRMCR[(master - 1)].bit.TRPR;	// R1-63.

					mxic_utlis_off_pclk( priv->mxicUtlis, unit );
				}
				else {
					*priority = 0;

					// Unit number is invalid.
					//Ddim_Print(("mxic_master_get_master_priority(): unit number is invalid. unit=%d\n", unit));
				}
			}
			else {
				if ( unit == MxicUtlis_UNIT_3 ) {
					// Get master priority level of read master.
					master = master - MxicUtlis_MASTER_NUMBER_MAX;

					mxic_utlis_on_pclk( priv->mxicUtlis, unit );

					*priority = ioMxic->TRMCR_GR[master].bit.TRPR;		// R64-127.

					mxic_utlis_off_pclk( priv->mxicUtlis, unit );
				}
				else {
					*priority = 0;

					// Unit number is invalid.
					//Ddim_Print(("mxic_master_get_master_priority(): unit number is invalid. unit=%d\n", unit));
				}
			}
		}
		else {
			// Master number is illegal.
			Ddim_Print(("E:mxic_master_get_master_priority(): master is illegal. master=%d\n", master));
			result = MxicUtlis_INPUT_PARAM_ERROR;
		}
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:mxic_master_get_master_priority(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

/**
This function set the master transfer mask and mask period.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		master					Master number.<br>
@param[in]		mask					Setting of mask.
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
@remarks		The setting mask ranges are from 4 to 4096.
*/
INT32 mxic_master_set_master_mask( MxicMaster *self, ImMxicUnit unit, UCHAR master, 
									const ImMxicMasterMask* const mask )
{
	UCHAR						masterTypeRead;
	INT32						result;
	volatile struct io_jdsmxic*	ioMxic;
    MxicMasterPrivate *priv = MXIC_MASTER_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( mask == NULL ) {
		// mask parameter is NULL.
		Ddim_Assertion(("E:mxic_master_set_master_mask(): mask is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {

		// Set mask period.
		if ( mask->maskType == MxicUtlis_MASTER_MASK_PERIOD_ON ) {

			if ( ( master & MxicUtlis_MASTER_TYPE_CHECK_MASK ) == MxicUtlis_MASTER_TYPE_WRITE ) {

				if ( master < MxicUtlis_MASTER_NUMBER_MAX ) {

					if ( unit != MxicUtlis_UNIT_4 ) {
						// Set mask period of write master.
						mxic_utlis_on_pclk( priv->mxicUtlis, unit );

						ioMxic->TRMCW[(master - 1)].bit.TRMCVPW = mask->maskPeriod;	// W1-63.

						mxic_utlis_off_pclk( priv->mxicUtlis, unit );
					}
					else {
						// Unit number is invalid.
						//Ddim_Print(("mxic_master_set_master_mask(): unit number is invalid. unit=%d\n", unit));
					}
				}
				else {
					if ( unit == MxicUtlis_UNIT_3 ) {
						// Set mask period of write master.
						master = master - MxicUtlis_MASTER_NUMBER_MAX;

						mxic_utlis_on_pclk( priv->mxicUtlis, unit );

						ioMxic->TRMCW_GR[master].bit.TRMCVPW = mask->maskPeriod;		// W64-127.

						mxic_utlis_off_pclk( priv->mxicUtlis, unit );
					}
					else {
						// Unit number is invalid.
						//Ddim_Print(("mxic_master_set_master_mask(): unit number is invalid. unit=%d\n", unit));
					}
				}
			}
			else if ( ( master & MxicUtlis_MASTER_TYPE_CHECK_MASK ) == MxicUtlis_MASTER_TYPE_READ ) {

				masterTypeRead = master;
				masterTypeRead &= MxicUtlis_READ_MASTER_FLG_MASK;

				if ( masterTypeRead < MxicUtlis_MASTER_NUMBER_MAX ) {

					if ( unit != MxicUtlis_UNIT_0 ) {
						// Set mask period of read master.
						mxic_utlis_on_pclk( priv->mxicUtlis, unit );

						ioMxic->TRMCR[(masterTypeRead - 1)].bit.TRMCVPR = mask->maskPeriod;		// R1-63.

						mxic_utlis_off_pclk( priv->mxicUtlis, unit );
					}
					else {
						// Unit number is invalid.
						//Ddim_Print(("mxic_master_set_master_mask(): unit number is invalid. unit=%d\n", unit));
					}
				}
				else {
					if ( unit == MxicUtlis_UNIT_3 ) {
						// Set mask period of write master.
						masterTypeRead = masterTypeRead - MxicUtlis_MASTER_NUMBER_MAX;

						mxic_utlis_on_pclk( priv->mxicUtlis, unit );

						ioMxic->TRMCR_GR[masterTypeRead].bit.TRMCVPR = mask->maskPeriod;		// R64-127.

						mxic_utlis_off_pclk( priv->mxicUtlis, unit );
					}
					else {
						// Unit number is invalid.
						//Ddim_Print(("mxic_master_set_master_mask(): unit number is invalid. unit=%d\n", unit));
					}
				}
			}
			else {
				// Master number is illegal.
				Ddim_Print(("E:mxic_master_set_master_mask(): master is illegal. master=%d\n", master));
				return MxicUtlis_INPUT_PARAM_ERROR;
			}
		}

		// Set mask type.
		if ( ( master & MxicUtlis_MASTER_TYPE_CHECK_MASK ) == MxicUtlis_MASTER_TYPE_WRITE ) {

			if ( master < MxicUtlis_MASTER_NUMBER_MAX ) {

				if ( unit != MxicUtlis_UNIT_4 ) {
					// Set mask type of write master.
					mxic_utlis_on_pclk( priv->mxicUtlis, unit );

					ioMxic->TRMCW[(master - 1)].bit.TRMW = mask->maskType;	// W1-63.

					mxic_utlis_off_pclk( priv->mxicUtlis, unit );
				}
				else {
					// Unit number is invalid.
					//Ddim_Print(("mxic_master_set_master_mask(): unit number is invalid. unit=%d\n", unit));
				}
			}
			else {
				if ( unit == MxicUtlis_UNIT_3 ) {
					// Set mask type of write master.
					master = master - MxicUtlis_MASTER_NUMBER_MAX;

					mxic_utlis_on_pclk( priv->mxicUtlis, unit );

					ioMxic->TRMCW_GR[master].bit.TRMW = mask->maskType;		// W64-127.

					mxic_utlis_off_pclk( priv->mxicUtlis, unit );
				}
				else {
					// Unit number is invalid.
					//Ddim_Print(("mxic_master_set_master_mask(): unit number is invalid. unit=%d\n", unit));
				}
			}
		}
		else if ( ( master & MxicUtlis_MASTER_TYPE_CHECK_MASK ) == MxicUtlis_MASTER_TYPE_READ ) {

			masterTypeRead = master;
			masterTypeRead &= MxicUtlis_READ_MASTER_FLG_MASK;

			if ( masterTypeRead < MxicUtlis_MASTER_NUMBER_MAX ) {

				if ( unit != MxicUtlis_UNIT_0 ) {
					// Set mask type of read master.
					mxic_utlis_on_pclk( priv->mxicUtlis, unit );

					ioMxic->TRMCR[(masterTypeRead - 1)].bit.TRMR = mask->maskType;	// R1-63.

					mxic_utlis_off_pclk( priv->mxicUtlis, unit );
				}
				else {
					// Unit number is invalid.
					//Ddim_Print(("mxic_master_set_master_mask(): unit number is invalid. unit=%d\n", unit));
				}
			}
			else {
				if ( unit == MxicUtlis_UNIT_3 ) {
					// Set mask type of read master.
					masterTypeRead = masterTypeRead - MxicUtlis_MASTER_NUMBER_MAX;
					mxic_utlis_on_pclk( priv->mxicUtlis, unit );

					ioMxic->TRMCR_GR[masterTypeRead].bit.TRMR = mask->maskType;		// R64-127.

					mxic_utlis_off_pclk( priv->mxicUtlis, unit );
				}
				else {
					// Unit number is invalid.
					//Ddim_Print(("mxic_master_set_master_mask(): unit number is invalid. unit=%d\n", unit));
				}
			}
		}
		else {
			// Master number is illegal.
			Ddim_Print(("E:mxic_master_set_master_mask(): master is illegal. master=%d\n", master));
			return MxicUtlis_INPUT_PARAM_ERROR;
		}

		MxicUtlis_DSB();
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:mxic_master_set_master_mask(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

/**
This function get the master transfer mask and mask period.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		master					Master number.<br>
@param[out]		mask					Setting of mask.
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32 mxic_master_get_master_mask( MxicMaster *self, ImMxicUnit unit, UCHAR master, 
									ImMxicMasterMask* const mask )
{
	INT32						result;
	volatile struct io_jdsmxic*	ioMxic;
    MxicMasterPrivate *priv = MXIC_MASTER_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( mask == NULL ) {
		// mask parameter is NULL.
		Ddim_Assertion(("E:mxic_master_get_master_mask(): mask is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {

		if ( ( master & MxicUtlis_MASTER_TYPE_CHECK_MASK ) == MxicUtlis_MASTER_TYPE_WRITE ) {

			if ( master < MxicUtlis_MASTER_NUMBER_MAX ) {

				if ( unit != MxicUtlis_UNIT_4 ) {
					// Get mask setting of write master.
					mxic_utlis_on_pclk( priv->mxicUtlis, unit );

					mask->maskType		= ioMxic->TRMCW[(master - 1)].bit.TRMW;	// W1-63.
					mask->maskPeriod	= ioMxic->TRMCW[(master - 1)].bit.TRMCVPW;	// W1-63.

					mxic_utlis_off_pclk( priv->mxicUtlis, unit );
				}
				else {
					mask->maskType		= 0;
					mask->maskPeriod	= 0;

					// Unit number is invalid.
					//Ddim_Print(("mxic_master_get_master_mask(): unit number is invalid. unit=%d\n", unit));
				}
			}
			else {
				if ( unit == MxicUtlis_UNIT_3 ) {
					// Get mask setting of write master.
					master = master - MxicUtlis_MASTER_NUMBER_MAX;

					mxic_utlis_on_pclk( priv->mxicUtlis, unit );

					mask->maskType		= ioMxic->TRMCW_GR[master].bit.TRMW;		// W64-127.
					mask->maskPeriod	= ioMxic->TRMCW_GR[master].bit.TRMCVPW;	// W64-127.

					mxic_utlis_off_pclk( priv->mxicUtlis, unit );
				}
				else {
					mask->maskType		= 0;
					mask->maskPeriod	= 0;

					// Unit number is invalid.
					//Ddim_Print(("mxic_master_get_master_mask(): unit number is invalid. unit=%d\n", unit));
				}
			}
		}
		else if ( ( master & MxicUtlis_MASTER_TYPE_CHECK_MASK ) == MxicUtlis_MASTER_TYPE_READ ) {

			master &= MxicUtlis_READ_MASTER_FLG_MASK;

			if ( master < MxicUtlis_MASTER_NUMBER_MAX ) {

				if ( unit != MxicUtlis_UNIT_0 ) {
					// Get mask setting of read master.
					mxic_utlis_on_pclk( priv->mxicUtlis, unit );

					mask->maskType   = ioMxic->TRMCR[(master - 1)].bit.TRMR;		// R1-63.
					mask->maskPeriod = ioMxic->TRMCR[(master - 1)].bit.TRMCVPR;	// R1-63.

					mxic_utlis_off_pclk( priv->mxicUtlis, unit );
				}
				else {
					mask->maskType		= 0;
					mask->maskPeriod	= 0;

					// Unit number is invalid.
					//Ddim_Print(("mxic_master_get_master_mask(): unit number is invalid. unit=%d\n", unit));
				}
			}
			else {
				if ( unit == MxicUtlis_UNIT_3 ) {
					// Get mask setting of read master.
					master = master - MxicUtlis_MASTER_NUMBER_MAX;

					mxic_utlis_on_pclk( priv->mxicUtlis, unit );

					mask->maskType   = ioMxic->TRMCR_GR[master].bit.TRMR;			// R64-127.
					mask->maskPeriod = ioMxic->TRMCR_GR[master].bit.TRMCVPR;		// R64-127.

					mxic_utlis_off_pclk( priv->mxicUtlis, unit );
				}
				else {
					mask->maskType		= 0;
					mask->maskPeriod	= 0;

					// Unit number is invalid.
					//Ddim_Print(("mxic_master_get_master_mask(): unit number is invalid. unit=%d\n", unit));
				}
			}
		}
		else {
			// Master number is illegal.
			Ddim_Print(("E:mxic_master_get_master_mask(): master is illegal. master=%d\n", master));
			result = MxicUtlis_INPUT_PARAM_ERROR;
		}
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:mxic_master_get_master_mask(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

/**
This function set factor of transfer demand mask.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		master					Master number.<br>
@param[in]		group					Mask group.<br>
										Please refer to @ref ImMxicMaskGroup for a set value.<br>
@param[in]		enable					Setting of whether to make a master into a mask factor.<br>
										<ul><li>@ref MxicUtlis_ON
											<li>@ref MxicUtlis_OFF</ul>
@retval			D_DDIM_OK					Success
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error
*/
INT32 mxic_master_set_master_mask_factor( MxicMaster *self, ImMxicUnit unit, UCHAR master, 
											ImMxicMaskGroup group, UCHAR enable )
{
	INT32						result;
	MxicMasterMaskFactorTarget	config;

#ifdef CO_PARAM_CHECK
	if ( imMxicCheckMasterMaskFactorTargetParam( MxicMaster_OPERATION_TYPE_SET, master, group, &enable ) 
		!= D_DDIM_OK ) {
		// Parameter error.
		Ddim_Assertion(("E:mxic_master_set_master_mask_factor(): imMxicCheckMasterMaskFactorTargetParam error.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	config.kindSetGet			= MxicMaster_OPERATION_TYPE_SET;
	config.kindFactorTarget	= MxicMaster_MASK_OPERATION_FACTOR;
	config.master				= master;
	config.group				= group;
	config.enable				= enable;

	// Set master mask factor.
	result = imMxicRwMasterMaskFactorOrTarget( self, unit, &config );

	if ( result != D_DDIM_OK ) {
		// Error.
		Ddim_Print(("E:mxic_master_set_master_mask_factor(): imMxicRwMasterMaskFactorOrTarget error.\n"));
	}

	MxicUtlis_DSB();

	return result;
}

/**
This function get factor of transfer demand mask.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		master					Master number.<br>
@param[in]		group					Mask group.<br>
										Please refer to @ref ImMxicMaskGroup for a set value.<br>
@param[out]		enable					Setting of whether to make a master into a mask factor.<br>
										<ul><li>@ref MxicUtlis_ON
											<li>@ref MxicUtlis_OFF</ul>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32 mxic_master_get_master_mask_factor( MxicMaster *self, ImMxicUnit unit, UCHAR master, 
											ImMxicMaskGroup group, UCHAR* const enable )
{
	INT32						result;
	MxicMasterMaskFactorTarget	config;

#ifdef CO_PARAM_CHECK
	if ( imMxicCheckMasterMaskFactorTargetParam( MxicMaster_OPERATION_TYPE_GET, master, group, enable ) 
		!= D_DDIM_OK ) {
		// Parameter error.
		Ddim_Assertion(("E:mxic_master_get_master_mask_factor(): imMxicCheckMasterMaskFactorTargetParam error.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	config.kindSetGet			= MxicMaster_OPERATION_TYPE_GET;
	config.kindFactorTarget	= MxicMaster_MASK_OPERATION_FACTOR;
	config.master				= master;
	config.group				= group;
	config.enable				= MxicUtlis_OFF;

	// Get master mask factor.
	result = imMxicRwMasterMaskFactorOrTarget( self, unit, &config );

	if ( result == D_DDIM_OK ) {
		// Get return value.
		*enable = config.enable;
	}
	else {
		// Error.
		Ddim_Print(("E:mxic_master_set_master_mask_factor(): imMxicRwMasterMaskFactorOrTarget error.\n"));
	}

	return result;
}

/**
This function set target of transfer demand mask.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		master					Master number.<br>
@param[in]		group					Mask group.<br>
										Please refer to @ref ImMxicMaskGroup for a set value.<br>
@param[in]		enable					Setting of whether to make a master into a mask target.<br>
										<ul><li>@ref MxicUtlis_ON
											<li>@ref MxicUtlis_OFF</ul>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32 mxic_master_set_master_mask_target( MxicMaster *self, ImMxicUnit unit, UCHAR master, 
											ImMxicMaskGroup group, UCHAR enable )
{
	INT32						result;
	MxicMasterMaskFactorTarget	config;

#ifdef CO_PARAM_CHECK
	if ( imMxicCheckMasterMaskFactorTargetParam( MxicMaster_OPERATION_TYPE_SET, master, group, &enable ) 
		!= D_DDIM_OK ) {
		// Parameter error.
		Ddim_Assertion(("E:mxic_master_set_master_mask_target(): imMxicCheckMasterMaskFactorTargetParam error.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	config.kindSetGet			= MxicMaster_OPERATION_TYPE_SET;
	config.kindFactorTarget	= MxicMaster_MASK_OPERATION_TARGET;
	config.master				= master;
	config.group				= group;
	config.enable				= enable;

	// Set master mask target.
	result = imMxicRwMasterMaskFactorOrTarget( self, unit, &config );

	if ( result != D_DDIM_OK ) {
		// Error.
		Ddim_Print(("E:mxic_master_set_master_mask_target(): imMxicRwMasterMaskFactorOrTarget error.\n"));
	}

	MxicUtlis_DSB();

	return result;
}

/**
This function get target of transfer demand mask.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		master					Master number.<br>
@param[in]		group					Mask group.<br>
										Please refer to @ref ImMxicMaskGroup for a set value.<br>
@param[out]		enable					Setting of whether to make a master into a mask target.<br>
										<ul><li>@ref MxicUtlis_ON
											<li>@ref MxicUtlis_OFF</ul>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32 mxic_master_get_master_mask_target( MxicMaster *self, ImMxicUnit unit, UCHAR master, 
											ImMxicMaskGroup group, UCHAR* const enable )
{
	INT32						result;
	MxicMasterMaskFactorTarget	config;

#ifdef CO_PARAM_CHECK
	if ( imMxicCheckMasterMaskFactorTargetParam( MxicMaster_OPERATION_TYPE_GET, master, group, enable ) 
		!= D_DDIM_OK ) {
		// Parameter error.
		Ddim_Assertion(("E:mxic_master_get_master_mask_target(): imMxicCheckMasterMaskFactorTargetParam error.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	config.kindSetGet			= MxicMaster_OPERATION_TYPE_GET;
	config.kindFactorTarget	= MxicMaster_MASK_OPERATION_TARGET;
	config.master				= master;
	config.group				= group;
	config.enable				= MxicUtlis_OFF;

	// Get master mask target.
	
	result = imMxicRwMasterMaskFactorOrTarget( self, unit, &config );

	if ( result == D_DDIM_OK ) {
		// Get return value.
		*enable = config.enable;
	}
	else {
		// Error.
		Ddim_Print(("E:mxic_master_get_master_mask_target(): imMxicRwMasterMaskFactorOrTarget error.\n"));
	}

	return result;
}

/**
This function set the mask factor master state.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		master					Master number.<br>
@param[in]		select					Master state select.(0:master address ch demand period ,1:master address ch demand to data transfer complete)<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32 mxic_master_set_master_mask_select( MxicMaster *self, ImMxicUnit unit, UCHAR master, UCHAR select )
{
	INT32						result;
	volatile struct io_jdsmxic*	ioMxic;
    MxicMasterPrivate *priv = MXIC_MASTER_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( ( select != MxicUtlis_ON ) && ( select != MxicUtlis_OFF ) ) {
		// select parameter value is illegal.
		Ddim_Assertion(("E:mxic_master_set_master_mask_select(): select is illegal. select=%d\n", select));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {

		if ( (master & MxicUtlis_MASTER_TYPE_CHECK_MASK) == MxicUtlis_MASTER_TYPE_WRITE ) {
			// Set master mask state select of write master.
			if ( master < MxicUtlis_MASTER_NUMBER_MAX ) {

				if ( unit != MxicUtlis_UNIT_4 ) {

					mxic_utlis_on_pclk( priv->mxicUtlis, unit );

					if ( select == MxicUtlis_ON ) {
						ioMxic->TRMCW[(master - 1)].bit.TRMFTW |= MxicMaster_TRMC_TRMFT_SELECT;		// W1-63.
					} else {
						ioMxic->TRMCW[(master - 1)].bit.TRMFTW &= ~MxicMaster_TRMC_TRMFT_SELECT;	// W1-63.
					}

					mxic_utlis_off_pclk( priv->mxicUtlis, unit );
				}
				else {
					// Unit number is invalid.
					//Ddim_Print(("mxic_master_set_master_mask_select(): unit number is invalid. unit=%d\n", unit));
				}
			}
			else {
				if ( unit == MxicUtlis_UNIT_3 ) {

					master = master - MxicUtlis_MASTER_NUMBER_MAX;

					mxic_utlis_on_pclk( priv->mxicUtlis, unit );

					if ( select == MxicUtlis_ON ) {
						ioMxic->TRMCW_GR[master].bit.TRMFTW |= MxicMaster_TRMC_TRMFT_SELECT;		// W64-127.
					} else {
						ioMxic->TRMCW_GR[master].bit.TRMFTW &= ~MxicMaster_TRMC_TRMFT_SELECT;		// W64-127.
					}

					mxic_utlis_off_pclk( priv->mxicUtlis, unit );
				}
				else {
					// Unit number is invalid.
					//Ddim_Print(("mxic_master_set_master_mask_select(): unit number is invalid. unit=%d\n", unit));
				}
			}
		}
		else if ( (master & MxicUtlis_MASTER_TYPE_CHECK_MASK ) == MxicUtlis_MASTER_TYPE_READ ) {
			// Set master mask state select of read master.
			master &= MxicUtlis_READ_MASTER_FLG_MASK;

			if ( master < MxicUtlis_MASTER_NUMBER_MAX ) {

				if ( unit != MxicUtlis_UNIT_0 ) {

					mxic_utlis_on_pclk( priv->mxicUtlis, unit );

					if ( select == MxicUtlis_ON ) {
						ioMxic->TRMCR[(master - 1)].bit.TRMFTR |= MxicMaster_TRMC_TRMFT_SELECT;		// R1-63.
					} else {
						ioMxic->TRMCR[(master - 1)].bit.TRMFTR &= ~MxicMaster_TRMC_TRMFT_SELECT;	// R1-63.
					}

					mxic_utlis_off_pclk( priv->mxicUtlis, unit );
				}
				else {
					// Unit number is invalid.
					//Ddim_Print(("mxic_master_set_master_mask_select(): unit number is invalid. unit=%d\n", unit));
				}
			}
			else {
				if ( unit == MxicUtlis_UNIT_3 ) {

					master = master - MxicUtlis_MASTER_NUMBER_MAX;

					mxic_utlis_on_pclk( priv->mxicUtlis, unit );

					if ( select == MxicUtlis_ON ) {
						ioMxic->TRMCR_GR[master].bit.TRMFTR |= MxicMaster_TRMC_TRMFT_SELECT;		// R64-127.
					} else {
						ioMxic->TRMCR_GR[master].bit.TRMFTR &= ~MxicMaster_TRMC_TRMFT_SELECT;		// R64-127.
					}

					mxic_utlis_off_pclk( priv->mxicUtlis, unit );
				}
				else {
					// Unit number is invalid.
					//Ddim_Print(("mxic_master_set_master_mask_select(): unit number is invalid. unit=%d\n", unit));
				}
			}
		}
		else {
			// Master number is illegal.
			Ddim_Print(("E:mxic_master_set_master_mask_select(): master is illegal. master=%d\n", master));
			result = MxicUtlis_INPUT_PARAM_ERROR;
		}
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:mxic_master_set_master_mask_select(): mxic_utlis_get_unit_address error.\n"));
	}

	MxicUtlis_DSB();

	return result;
}

/**
This function get the mask factor master state.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		master					Master number.<br>
@param[in]		select					Master state select.(0:master address ch demand period ,1:master address ch demand to data transfer complete)<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32 mxic_master_get_master_mask_select( MxicMaster *self, ImMxicUnit unit, UCHAR master, UCHAR* const select )
{
	INT32						result;
	volatile struct io_jdsmxic*	ioMxic;
    MxicMasterPrivate *priv = MXIC_MASTER_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( select == NULL ) {
		// priority parameter is NULL.
		Ddim_Assertion(("E:mxic_master_get_master_mask_select(): select is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {

		if ( ( master & MxicUtlis_MASTER_TYPE_CHECK_MASK ) == MxicUtlis_MASTER_TYPE_WRITE ) {
			// Set master mask state select of write master.
			if ( master < MxicUtlis_MASTER_NUMBER_MAX ) {

				if ( unit != MxicUtlis_UNIT_4 ) {

					mxic_utlis_on_pclk( priv->mxicUtlis, unit );

					if ( ( ioMxic->TRMCW[(master - 1)].bit.TRMFTW & MxicMaster_TRMC_TRMFT_SELECT ) != 0 ) {		// W1-63.
						*select = MxicUtlis_ON;
					}
					else {
						*select = MxicUtlis_OFF;
					}

					mxic_utlis_off_pclk( priv->mxicUtlis, unit );
				}
				else {
					*select = MxicUtlis_OFF;

					// Unit number is invalid.
					//Ddim_Print(("mxic_master_get_master_mask_select(): unit number is invalid. unit=%d\n", unit));
				}
			}
			else {
				if ( unit == MxicUtlis_UNIT_3 ) {

					master = master - MxicUtlis_MASTER_NUMBER_MAX;

					mxic_utlis_on_pclk( priv->mxicUtlis, unit );

					if ( ( ioMxic->TRMCW_GR[master].bit.TRMFTW & MxicMaster_TRMC_TRMFT_SELECT ) != 0 ) {	// W64-127.
						*select = MxicUtlis_ON;
					}
					else {
						*select = MxicUtlis_OFF;
					}

					mxic_utlis_off_pclk( priv->mxicUtlis, unit );
				}
				else {
					*select = MxicUtlis_OFF;

					// Unit number is invalid.
					//Ddim_Print(("mxic_master_get_master_mask_select(): unit number is invalid. unit=%d\n", unit));
				}
			}
		}
		else if ( ( master & MxicUtlis_MASTER_TYPE_CHECK_MASK ) == MxicUtlis_MASTER_TYPE_READ ) {
			// Set master mask state select of read master.
			master &= MxicUtlis_READ_MASTER_FLG_MASK;

			if ( master < MxicUtlis_MASTER_NUMBER_MAX ) {

				if ( unit != MxicUtlis_UNIT_0 ) {

					mxic_utlis_on_pclk( priv->mxicUtlis, unit );

					if ( ( ioMxic->TRMCR[(master - 1)].bit.TRMFTR & MxicMaster_TRMC_TRMFT_SELECT ) != 0 ) {	// R1-63.
						*select = MxicUtlis_ON;
					}
					else {
						*select = MxicUtlis_OFF;
					}

					mxic_utlis_off_pclk( priv->mxicUtlis, unit );
				}
				else {
					*select = MxicUtlis_OFF;

					// Unit number is invalid.
					//Ddim_Print(("mxic_master_get_master_mask_select(): unit number is invalid. unit=%d\n", unit));
				}
			}
			else {
				if ( unit == MxicUtlis_UNIT_3 ) {

					master = master - MxicUtlis_MASTER_NUMBER_MAX;

					mxic_utlis_on_pclk( priv->mxicUtlis, unit );

					if ( ( ioMxic->TRMCR_GR[master].bit.TRMFTR & MxicMaster_TRMC_TRMFT_SELECT ) != 0 ) {	// R64-127.
						*select = MxicUtlis_ON;
					}
					else {
						*select = MxicUtlis_OFF;
					}

					mxic_utlis_off_pclk( priv->mxicUtlis, unit );
				}
				else {
					*select = MxicUtlis_OFF;

					// Unit number is invalid.
					//Ddim_Print(("mxic_master_get_master_mask_select(): unit number is invalid. unit=%d\n", unit));
				}
			}
		}
		else {
			// Master number is illegal.
			Ddim_Print(("E:mxic_master_get_master_mask_select(): master is illegal. master=%d\n", master));
			result = MxicUtlis_INPUT_PARAM_ERROR;
		}
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:mxic_master_get_master_mask_select(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

/**
This function set the max number of master transaction.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		master					Master number.<br>
@param[in]		select					Master transaction.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32 mxic_master_set_master_transaction( MxicMaster *self, ImMxicUnit unit, UCHAR master, UCHAR transaction )
{
	INT32						result;
	volatile struct io_jdsmxic*	ioMxic;
    MxicMasterPrivate *priv = MXIC_MASTER_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( transaction > MxicMaster_TRMC_TISULIM_MAX_VAL ) {
		// select parameter value is illegal.
		Ddim_Assertion(("E:mxic_master_set_master_transaction(): transaction is illegal. transaction=%d\n", 
						transaction));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {

		if ( ( master & MxicUtlis_MASTER_TYPE_CHECK_MASK ) == MxicUtlis_MASTER_TYPE_WRITE ) {
			// Set master mask state select of write master.
			if ( master < MxicUtlis_MASTER_NUMBER_MAX ) {

				if ( unit != MxicUtlis_UNIT_4 ) {

					mxic_utlis_on_pclk( priv->mxicUtlis, unit );

					ioMxic->TRMCW[(master - 1)].bit.TISULIMW = transaction;		// W1-63.

					mxic_utlis_off_pclk( priv->mxicUtlis, unit );
				}
				else {
					// Unit number is invalid.
					//Ddim_Print(("mxic_master_set_master_transaction(): unit number is invalid. unit=%d\n", unit));
				}
			}
			else {
				if ( unit == MxicUtlis_UNIT_3 ) {

					master = master - MxicUtlis_MASTER_NUMBER_MAX;

					mxic_utlis_on_pclk( priv->mxicUtlis, unit );

					ioMxic->TRMCW_GR[master].bit.TISULIMW = transaction;			// W1-63.

					mxic_utlis_off_pclk( priv->mxicUtlis, unit );
				}
				else {
					// Unit number is invalid.
					//Ddim_Print(("mxic_master_set_master_transaction(): unit number is invalid. unit=%d\n", unit));
				}
			}
		}
		else if ( ( master & MxicUtlis_MASTER_TYPE_CHECK_MASK ) == MxicUtlis_MASTER_TYPE_READ ) {
			// Set master mask state select of read master.
			master &= MxicUtlis_READ_MASTER_FLG_MASK;

			if ( master < MxicUtlis_MASTER_NUMBER_MAX ) {

				if ( unit != MxicUtlis_UNIT_0 ) {

					mxic_utlis_on_pclk( priv->mxicUtlis, unit );

					ioMxic->TRMCR[(master - 1)].bit.TISULIMR = transaction;		// R1-63.

					mxic_utlis_off_pclk( priv->mxicUtlis, unit );
				}
				else {
					// Unit number is invalid.
					//Ddim_Print(("mxic_master_set_master_transaction(): unit number is invalid. unit=%d\n", unit));
				}
			}
			else {
				if ( unit == MxicUtlis_UNIT_3 ) {

					master = master - MxicUtlis_MASTER_NUMBER_MAX;

					mxic_utlis_on_pclk( priv->mxicUtlis, unit );

					ioMxic->TRMCR_GR[master].bit.TISULIMR = transaction;			// R64-127.

					mxic_utlis_off_pclk( priv->mxicUtlis, unit );
				}
				else {
					// Unit number is invalid.
					//Ddim_Print(("mxic_master_set_master_transaction(): unit number is invalid. unit=%d\n", unit));
				}
			}
		}
		else {
			// Master number is illegal.
			Ddim_Print(("E:mxic_master_set_master_transaction(): master is illegal. master=%d\n", master));
			result = MxicUtlis_INPUT_PARAM_ERROR;
		}

		MxicUtlis_DSB();
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:mxic_master_set_master_transaction(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

/**
This function get the max number of master transaction.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		master					Master number.<br>
@param[in]		transaction				Master transaction.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32 mxic_master_get_master_transaction( MxicMaster *self, ImMxicUnit unit, UCHAR master, UCHAR* const transaction )
{
	INT32						result;
	volatile struct io_jdsmxic*	ioMxic;
    MxicMasterPrivate *priv = MXIC_MASTER_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( transaction == NULL ) {
		// priority parameter is NULL.
		Ddim_Assertion(("E:mxic_master_get_master_transaction(): select is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {

		if ( ( master & MxicUtlis_MASTER_TYPE_CHECK_MASK ) == MxicUtlis_MASTER_TYPE_WRITE ) {
			// Set master mask state select of write master.
			if ( master < MxicUtlis_MASTER_NUMBER_MAX ) {

				if ( unit != MxicUtlis_UNIT_4 ) {

					mxic_utlis_on_pclk( priv->mxicUtlis, unit );

					*transaction = ioMxic->TRMCW[(master - 1)].bit.TISULIMW;		// W1-63.

					mxic_utlis_off_pclk( priv->mxicUtlis, unit );
				}
				else {
					*transaction = 0;

					// Unit number is invalid.
					//Ddim_Print(("mxic_master_get_master_transaction(): unit number is invalid. unit=%d\n", unit));
				}
			}
			else {
				if ( unit == MxicUtlis_UNIT_3 ) {

					master = master - MxicUtlis_MASTER_NUMBER_MAX;

					mxic_utlis_on_pclk( priv->mxicUtlis, unit );

					*transaction = ioMxic->TRMCW_GR[master].bit.TISULIMW;			// W64-127.

					mxic_utlis_off_pclk( priv->mxicUtlis, unit );
				}
				else {
					*transaction = 0;

					// Unit number is invalid.
					//Ddim_Print(("mxic_master_get_master_transaction(): unit number is invalid. unit=%d\n", unit));
				}
			}
		}
		else if ( ( master & MxicUtlis_MASTER_TYPE_CHECK_MASK ) == MxicUtlis_MASTER_TYPE_READ ) {
			// Set master mask state select of read master.
			master &= MxicUtlis_READ_MASTER_FLG_MASK;

			if ( master < MxicUtlis_MASTER_NUMBER_MAX ) {

				if ( unit != MxicUtlis_UNIT_0 ) {

					mxic_utlis_on_pclk( priv->mxicUtlis, unit );

					*transaction = ioMxic->TRMCR[(master - 1)].bit.TISULIMR;		// R1-63.

					mxic_utlis_off_pclk( priv->mxicUtlis, unit );
				}
				else {
					*transaction = 0;

					// Unit number is invalid.
					//Ddim_Print(("mxic_master_get_master_transaction(): unit number is invalid. unit=%d\n", unit));
				}
			}
			else {
				if ( unit == MxicUtlis_UNIT_3 ) {

					master = master - MxicUtlis_MASTER_NUMBER_MAX;

					mxic_utlis_on_pclk( priv->mxicUtlis, unit );

					*transaction = ioMxic->TRMCR_GR[master].bit.TISULIMR;			// R64-127.

					mxic_utlis_off_pclk( priv->mxicUtlis, unit );
				}
				else {
					*transaction = 0;

					// Unit number is invalid.
					//Ddim_Print(("mxic_master_get_master_transaction(): unit number is invalid. unit=%d\n", unit));
				}
			}
		}
		else {
			// Master number is illegal.
			Ddim_Print(("E:mxic_master_get_master_transaction(): master is illegal. master=%d\n", master));
			result = MxicUtlis_INPUT_PARAM_ERROR;
		}
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:mxic_master_get_master_transaction(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

MxicMaster *mxic_master_new(void)
{
    MxicMaster* self = k_object_new_with_private(MXIC_TYPE_MASTER, sizeof(MxicMasterPrivate));
    return self;
}
