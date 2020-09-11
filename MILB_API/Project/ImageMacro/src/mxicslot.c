/***********************************************************************
 * @Copyright(C) 上海网用软件有限公司
 * @file mxicslot.c
 * @date 2020-09-02
 * @author: 吴海辉
 * @brief: 
 * @version: 1.0.0
***********************************************************************/

#include "mxicslot.h"


K_TYPE_DEFINE_WITH_PRIVATE(MxicSlot, mxic_slot)
#define MXIC_SLOT_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), MxicSlotPrivate, MXIC_TYPE_SLOT))

// TLVL*.LML* bit flag
#define MxicSlot_TLVL_LML_SLOT0			(0x00000001)	// Slot0 mask bit
#define MxicSlot_TLVL_LML_SLOT1			(0x00000002)	// Slot1 mask bit
#define MxicSlot_TLVL_LML_SLOT2			(0x00000004)	// Slot2 mask bit
#define MxicSlot_TLVL_LML_SLOT3			(0x00000008)	// Slot3 mask bit


struct _MxicSlotPrivate
{
    MxicUtlis* mxicUtlis;
};


/*----------------------------------------------------------------------*/
/* DECLS  															    */
/*----------------------------------------------------------------------*/
#ifdef CO_PARAM_CHECK
static INT32 imMxicCheckLevelCtrlBlock( ImMxicWrArbiter wrArbiter, ImMxicSpecArbiter arbiter, 
										ImMxicPort port, MxicSlotLevelCtrl levelNumber );
static INT32 imMxicCheckSlot( ImMxicWrArbiter wrArbiter, ImMxicSpecArbiter arbiter, 
								ImMxicPort port, ImMxicSlot slot );
#endif // CO_PARAM_CHECK


/*----------------------------------------------------------------------*/
/* IMPL  															    */
/*----------------------------------------------------------------------*/
static void mxic_slot_constructor(MxicSlot *self)
{
    MxicSlotPrivate *priv = MXIC_SLOT_GET_PRIVATE(self);

	priv->mxicUtlis = mxic_utlis_new();
}

static void mxic_slot_destructor(MxicSlot *self)
{
    MxicSlotPrivate *priv = MXIC_SLOT_GET_PRIVATE(self);

	if(priv->mxicUtlis)
	{
		k_object_unref(priv->mxicUtlis);
		priv->mxicUtlis = NULL;
	}
}

#ifdef CO_PARAM_CHECK
/**
Check level control block specifies parameter.
@param[in]		wrArbiter				Write or Read Arbiter.<br>
@param[in]		arbiter					Arbiter.<br>
@param[in]		port					Port.<br>
@param[in]		levelNumber			Level control block.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
static INT32 imMxicCheckLevelCtrlBlock( ImMxicWrArbiter wrArbiter, ImMxicSpecArbiter arbiter, 
										ImMxicPort port, MxicSlotLevelCtrl levelNumber )
{
	INT32 result;

	result = D_DDIM_OK;

	if ( ( wrArbiter >= MxicUtlis_WR_ARBITER_MAX ) || ( arbiter >= MxicUtlis_SPEC_ARBITER_MAX ) 
		|| ( port >= MxicUtlis_PORT_MAX ) || ( levelNumber >= MxicUtlis_SLOT_LEVEL_CTRL_MAX ) ) {
		result = MxicUtlis_INPUT_PARAM_ERROR;
		Ddim_Print(("E:imMxicCheckLevelCtrlBlock(): Parameter is illegal. wrArbiter=%d, arbiter=%d, port=%d, "
					"levelNumber=%d\n", wrArbiter, arbiter, port, levelNumber));
	}

	return result;
}

/**
Check slot parameter.
@param[in]		wrArbiter				Write or Read Arbiter.<br>
@param[in]		arbiter					Arbiter.<br>
@param[in]		port					Port.<br>
@param[in]		slot					Slot.
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
static INT32 imMxicCheckSlot( ImMxicWrArbiter wrArbiter, ImMxicSpecArbiter arbiter, 
							  ImMxicPort port, ImMxicSlot slot )
{
	INT32 result;

	result = D_DDIM_OK;

	if ( ( wrArbiter >= MxicUtlis_WR_ARBITER_MAX ) || ( arbiter >= MxicUtlis_SPEC_ARBITER_MAX ) 
		|| ( port >= MxicUtlis_PORT_MAX ) || ( slot >= MxicUtlis_SLOT_MAX ) ) {
		result = MxicUtlis_INPUT_PARAM_ERROR;
		Ddim_Print(("E:imMxicCheckSlot(): Parameter is illegal. wrArbiter=%d, arbiter=%d, port=%d, slot=%d\n", 
					wrArbiter, arbiter, port, slot));
	}
	return result;
}

#endif // CO_PARAM_CHECK

/**
Get TLVL*.LML* bit flag.
@param[in]		slot			Slot.(Set/Get)<br>
@param[out]		bitFlag		TLVL*.LML* bit flag for specified slot.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
static INT32 im_mxic_get_slot_mask_bit_flag( ImMxicSlot slot, INT32* const bitFlag )
{
	INT32 result;

	result = D_DDIM_OK;

	switch ( slot ) {
		case MxicUtlis_SLOT_0:
			*bitFlag = MxicSlot_TLVL_LML_SLOT0;
			break;
		case MxicUtlis_SLOT_1:
			*bitFlag = MxicSlot_TLVL_LML_SLOT1;
			break;
		case MxicUtlis_SLOT_2:
			*bitFlag = MxicSlot_TLVL_LML_SLOT2;
			break;
		case MxicUtlis_SLOT_3:
			*bitFlag = MxicSlot_TLVL_LML_SLOT3;
			break;
		default:
			result = MxicUtlis_INPUT_PARAM_ERROR;
			Ddim_Print(("E:im_mxic_get_slot_mask_bit_flag(): slot is illegal. slot=%d\n", slot));
			break;
	}

	return result;
}


/*----------------------------------------------------------------------*/
/* PUBLIC  															    */
/*----------------------------------------------------------------------*/
/**
This function set the slot priority level control.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		wrArbiter				Target write or read Arbiter.<br>
										Please refer to @ref ImMxicWrArbiter for a set value.<br>
@param[in]		arbiter					Target arbiter.<br>
										Please refer to @ref ImMxicSpecArbiter for a set value.<br>
@param[in]		port					Target Port.<br>
										Please refer to @ref ImMxicPort for a set value.<br>
@param[in]		levelNumber			Target level.<br>
										Please refer to @ref MxicSlotLevelCtrl for a set value.<br>
@param[in]		priority				Priority level control settings.
										Please refer to @ref MxicSlotPriorityLevel for a set value.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
@remarks		The setting ranges are from 1 to 64.
*/
INT32 mxic_slot_set_slot_priority( MxicSlot *self, SlotArgs priArgs, ImMxicPort port, 
		MxicSlotLevelCtrl levelNumber, const MxicSlotPriorityLevel* const priority )
{
	UCHAR						regReadSw;
	INT32						result;
	volatile struct io_jdsmxic*	ioMxic;
    MxicSlotPrivate *priv = MXIC_SLOT_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( imMxicCheckLevelCtrlBlock( priArgs.wrArbiter, priArgs.arbiter, port, levelNumber ) != D_DDIM_OK ) {
		// Input parameter error.
		Ddim_Assertion(("E:mxic_slot_set_slot_priority(): imMxicCheckLevelCtrlBlock error.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
	if ( priority == NULL ) {
		// priority parameter is NULL.
		Ddim_Assertion(("E:mxic_slot_set_slot_priority(): priority is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, priArgs.unit, &ioMxic );

	if ( result == D_DDIM_OK ) {

		mxic_utlis_on_pclk( priv->mxicUtlis, priArgs.unit );

		regReadSw = ioMxic->TRVSW.bit.TRVSW;

		if ( regReadSw == MxicUtlis_ON ) {
			ioMxic->TRVSW.bit.TRVSW = MxicUtlis_OFF;
		}

		if ( priArgs.wrArbiter == MxicUtlis_WR_ARBITER_W ) {

			if ( priArgs.unit != MxicUtlis_UNIT_4 ) {
				// Write arbiter.
				switch ( priArgs.arbiter ) {
					case MxicUtlis_SPEC_ARBITER_1:
						// arbiter1.
						switch ( levelNumber ) {
							case MxicUtlis_SLOT_LEVEL_CTRL_0:
								// Level0.
								ioMxic->TLVLW1[port].bit.LPCCL0W	= priority->upperPriorityLevel;
								ioMxic->TLVLW1[port].bit.LPCSL0W	= priority->lowerPriorityLevel;
								ioMxic->TLVLW1[port].bit.LPL0W		= priority->priorityLevelType;
								break;
							case MxicUtlis_SLOT_LEVEL_CTRL_1:
								// Level1.
								ioMxic->TLVLW1[port].bit.LPCCL1W	= priority->upperPriorityLevel;
								ioMxic->TLVLW1[port].bit.LPCSL1W	= priority->lowerPriorityLevel;
								ioMxic->TLVLW1[port].bit.LPL1W		= priority->priorityLevelType;
								break;
							case MxicUtlis_SLOT_LEVEL_CTRL_2:
								// Level2.
								ioMxic->TLVLW1[port].bit.LPCCL2W	= priority->upperPriorityLevel;
								ioMxic->TLVLW1[port].bit.LPCSL2W	= priority->lowerPriorityLevel;
								ioMxic->TLVLW1[port].bit.LPL2W		= priority->priorityLevelType;
								break;
							default:
								// levelNumber parameter value is illegal.
								result = MxicUtlis_INPUT_PARAM_ERROR;
								Ddim_Print(("E:mxic_slot_set_slot_priority(): levelNumber is illegal. levelNumber=%d\n",
											 levelNumber));
								break;
						}
						break;
					case MxicUtlis_SPEC_ARBITER_2:
						// arbiter2.
						switch ( levelNumber ) {
							case MxicUtlis_SLOT_LEVEL_CTRL_0:
								// Level0.
								ioMxic->TLVLW2[port].bit.LPCCL0W	= priority->upperPriorityLevel;
								ioMxic->TLVLW2[port].bit.LPCSL0W	= priority->lowerPriorityLevel;
								ioMxic->TLVLW2[port].bit.LPL0W		= priority->priorityLevelType;
								break;
							case MxicUtlis_SLOT_LEVEL_CTRL_1:
								// Level1.
								ioMxic->TLVLW2[port].bit.LPCCL1W	= priority->upperPriorityLevel;
								ioMxic->TLVLW2[port].bit.LPCSL1W	= priority->lowerPriorityLevel;
								ioMxic->TLVLW2[port].bit.LPL1W		= priority->priorityLevelType;
								break;
							case MxicUtlis_SLOT_LEVEL_CTRL_2:
								// Level2.
								ioMxic->TLVLW2[port].bit.LPCCL2W	= priority->upperPriorityLevel;
								ioMxic->TLVLW2[port].bit.LPCSL2W	= priority->lowerPriorityLevel;
								ioMxic->TLVLW2[port].bit.LPL2W		= priority->priorityLevelType;
								break;
							default:
								// levelNumber parameter value is illegal.
								result = MxicUtlis_INPUT_PARAM_ERROR;
								Ddim_Print(("E:mxic_slot_set_slot_priority(): levelNumber is illegal. levelNumber=%d\n", 
											levelNumber));
								break;
						}
						break;
					case MxicUtlis_SPEC_ARBITER_3:
						// arbiter3.
						switch ( levelNumber ) {
							case MxicUtlis_SLOT_LEVEL_CTRL_0:
								// Level0.
								ioMxic->TLVLW3[port].bit.LPCCL0W	= priority->upperPriorityLevel;
								ioMxic->TLVLW3[port].bit.LPCSL0W	= priority->lowerPriorityLevel;
								ioMxic->TLVLW3[port].bit.LPL0W		= priority->priorityLevelType;
								break;
							case MxicUtlis_SLOT_LEVEL_CTRL_1:
								// Level1.
								ioMxic->TLVLW3[port].bit.LPCCL1W	= priority->upperPriorityLevel;
								ioMxic->TLVLW3[port].bit.LPCSL1W	= priority->lowerPriorityLevel;
								ioMxic->TLVLW3[port].bit.LPL1W		= priority->priorityLevelType;
								break;
							case MxicUtlis_SLOT_LEVEL_CTRL_2:
								// Level2.
								ioMxic->TLVLW3[port].bit.LPCCL2W	= priority->upperPriorityLevel;
								ioMxic->TLVLW3[port].bit.LPCSL2W	= priority->lowerPriorityLevel;
								ioMxic->TLVLW3[port].bit.LPL2W		= priority->priorityLevelType;
								break;
							default:
								// levelNumber parameter value is illegal.
								result = MxicUtlis_INPUT_PARAM_ERROR;
								Ddim_Print(("E:mxic_slot_set_slot_priority(): levelNumber is illegal. levelNumber=%d\n", 
											levelNumber));
								break;
						}
						break;
					case MxicUtlis_SPEC_ARBITER_4:
						// arbiter4.
						switch ( levelNumber ) {
							case MxicUtlis_SLOT_LEVEL_CTRL_0:
								// Level0.
								ioMxic->TLVLW4[port].bit.LPCCL0W	= priority->upperPriorityLevel;
								ioMxic->TLVLW4[port].bit.LPCSL0W	= priority->lowerPriorityLevel;
								ioMxic->TLVLW4[port].bit.LPL0W		= priority->priorityLevelType;
								break;
							case MxicUtlis_SLOT_LEVEL_CTRL_1:
								// Level1.
								ioMxic->TLVLW4[port].bit.LPCCL1W	= priority->upperPriorityLevel;
								ioMxic->TLVLW4[port].bit.LPCSL1W	= priority->lowerPriorityLevel;
								ioMxic->TLVLW4[port].bit.LPL1W		= priority->priorityLevelType;
								break;
							case MxicUtlis_SLOT_LEVEL_CTRL_2:
								// Level2.
								ioMxic->TLVLW4[port].bit.LPCCL2W	= priority->upperPriorityLevel;
								ioMxic->TLVLW4[port].bit.LPCSL2W	= priority->lowerPriorityLevel;
								ioMxic->TLVLW4[port].bit.LPL2W		= priority->priorityLevelType;
								break;
							default:
								// levelNumber parameter value is illegal.
								result = MxicUtlis_INPUT_PARAM_ERROR;
								Ddim_Print(("E:mxic_slot_set_slot_priority(): levelNumber is illegal. levelNumber=%d\n", 
											levelNumber));
								break;
						}
						break;
					default:
						// arbiter parameter value is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_slot_set_slot_priority(): arbiter is illegal. arbiter=%d\n", priArgs.arbiter));
						break;
				}
			}
			else {
				// Unit number is invalid.
				//Ddim_Print(("mxic_slot_set_slot_priority(): unit number is invalid. unit=%d\n", unit));
			}
		}
		else {
			if ( priArgs.unit != MxicUtlis_UNIT_0 ) {
				// Read arbiter.
				switch ( priArgs.arbiter ) {
					case MxicUtlis_SPEC_ARBITER_1:
						// arbiter1.
						switch ( levelNumber ) {
							case MxicUtlis_SLOT_LEVEL_CTRL_0:
								// Level0.
								ioMxic->TLVLR1[port].bit.LPCCL0R	= priority->upperPriorityLevel;
								ioMxic->TLVLR1[port].bit.LPCSL0R	= priority->lowerPriorityLevel;
								ioMxic->TLVLR1[port].bit.LPL0R		= priority->priorityLevelType;
								break;
							case MxicUtlis_SLOT_LEVEL_CTRL_1:
								// Level1.
								ioMxic->TLVLR1[port].bit.LPCCL1R	= priority->upperPriorityLevel;
								ioMxic->TLVLR1[port].bit.LPCSL1R	= priority->lowerPriorityLevel;
								ioMxic->TLVLR1[port].bit.LPL1R		= priority->priorityLevelType;
								break;
							case MxicUtlis_SLOT_LEVEL_CTRL_2:
								// Level2.
								ioMxic->TLVLR1[port].bit.LPCCL2R	= priority->upperPriorityLevel;
								ioMxic->TLVLR1[port].bit.LPCSL2R	= priority->lowerPriorityLevel;
								ioMxic->TLVLR1[port].bit.LPL2R		= priority->priorityLevelType;
								break;
							default:
								// levelNumber parameter value is illegal.
								result = MxicUtlis_INPUT_PARAM_ERROR;
								Ddim_Print(("E:mxic_slot_set_slot_priority(): levelNumber is illegal. levelNumber=%d\n", 
											levelNumber));
								break;
						}
						break;
					case MxicUtlis_SPEC_ARBITER_2:
						// arbiter2.
						switch ( levelNumber ) {
							case MxicUtlis_SLOT_LEVEL_CTRL_0:
								// Level0.
								ioMxic->TLVLR2[port].bit.LPCCL0R	= priority->upperPriorityLevel;
								ioMxic->TLVLR2[port].bit.LPCSL0R	= priority->lowerPriorityLevel;
								ioMxic->TLVLR2[port].bit.LPL0R		= priority->priorityLevelType;
								break;
							case MxicUtlis_SLOT_LEVEL_CTRL_1:
								// Level1.
								ioMxic->TLVLR2[port].bit.LPCCL1R	= priority->upperPriorityLevel;
								ioMxic->TLVLR2[port].bit.LPCSL1R	= priority->lowerPriorityLevel;
								ioMxic->TLVLR2[port].bit.LPL1R		= priority->priorityLevelType;
								break;
							case MxicUtlis_SLOT_LEVEL_CTRL_2:
								// Level2.
								ioMxic->TLVLR2[port].bit.LPCCL2R	= priority->upperPriorityLevel;
								ioMxic->TLVLR2[port].bit.LPCSL2R	= priority->lowerPriorityLevel;
								ioMxic->TLVLR2[port].bit.LPL2R		= priority->priorityLevelType;
								break;
							default:
								// levelNumber parameter value is illegal.
								result = MxicUtlis_INPUT_PARAM_ERROR;
								Ddim_Print(("E:mxic_slot_set_slot_priority(): levelNumber is illegal. levelNumber=%d\n", 
											levelNumber));
								break;
						}
						break;
					case MxicUtlis_SPEC_ARBITER_3:
						// arbiter3.
						switch ( levelNumber ) {
							case MxicUtlis_SLOT_LEVEL_CTRL_0:
								// Level0.
								ioMxic->TLVLR3[port].bit.LPCCL0R	= priority->upperPriorityLevel;
								ioMxic->TLVLR3[port].bit.LPCSL0R	= priority->lowerPriorityLevel;
								ioMxic->TLVLR3[port].bit.LPL0R		= priority->priorityLevelType;
								break;
							case MxicUtlis_SLOT_LEVEL_CTRL_1:
								// Level1.
								ioMxic->TLVLR3[port].bit.LPCCL1R	= priority->upperPriorityLevel;
								ioMxic->TLVLR3[port].bit.LPCSL1R	= priority->lowerPriorityLevel;
								ioMxic->TLVLR3[port].bit.LPL1R		= priority->priorityLevelType;
								break;
							case MxicUtlis_SLOT_LEVEL_CTRL_2:
								// Level2.
								ioMxic->TLVLR3[port].bit.LPCCL2R	= priority->upperPriorityLevel;
								ioMxic->TLVLR3[port].bit.LPCSL2R	= priority->lowerPriorityLevel;
								ioMxic->TLVLR3[port].bit.LPL2R		= priority->priorityLevelType;
								break;
							default:
								// levelNumber parameter value is illegal.
								result = MxicUtlis_INPUT_PARAM_ERROR;
								Ddim_Print(("E:mxic_slot_set_slot_priority(): levelNumber is illegal. levelNumber=%d\n", 
											levelNumber));
								break;
						}
						break;
					case MxicUtlis_SPEC_ARBITER_4:
						// arbiter4.
						switch ( levelNumber ) {
							case MxicUtlis_SLOT_LEVEL_CTRL_0:
								// Level0.
								ioMxic->TLVLR4[port].bit.LPCCL0R	= priority->upperPriorityLevel;
								ioMxic->TLVLR4[port].bit.LPCSL0R	= priority->lowerPriorityLevel;
								ioMxic->TLVLR4[port].bit.LPL0R		= priority->priorityLevelType;
								break;
							case MxicUtlis_SLOT_LEVEL_CTRL_1:
								// Level1.
								ioMxic->TLVLR4[port].bit.LPCCL1R	= priority->upperPriorityLevel;
								ioMxic->TLVLR4[port].bit.LPCSL1R	= priority->lowerPriorityLevel;
								ioMxic->TLVLR4[port].bit.LPL1R		= priority->priorityLevelType;
								break;
							case MxicUtlis_SLOT_LEVEL_CTRL_2:
								// Level2.
								ioMxic->TLVLR4[port].bit.LPCCL2R	= priority->upperPriorityLevel;
								ioMxic->TLVLR4[port].bit.LPCSL2R	= priority->lowerPriorityLevel;
								ioMxic->TLVLR4[port].bit.LPL2R		= priority->priorityLevelType;
								break;
							default:
								// levelNumber parameter value is illegal.
								result = MxicUtlis_INPUT_PARAM_ERROR;
								Ddim_Print(("E:mxic_slot_set_slot_priority(): levelNumber is illegal. levelNumber=%d\n", 
											levelNumber));
								break;
						}
						break;
					default:
						// arbiter parameter value is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_slot_set_slot_priority(): arbiter is illegal. arbiter=%d\n", 
									priArgs.arbiter));
						break;
				}
			}
			else {
				// Unit number is invalid.
				//Ddim_Print(("mxic_slot_set_slot_priority(): unit number is invalid. unit=%d\n", unit));
			}
		}

		if ( regReadSw == MxicUtlis_ON ) {
			ioMxic->TRVSW.bit.TRVSW = MxicUtlis_ON;
		}

		mxic_utlis_off_pclk( priv->mxicUtlis, priArgs.unit );

		MxicUtlis_DSB();
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:mxic_slot_set_slot_priority(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

/**
This function get the slot priority level control.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
param[in]		wrArbiter				Target write or read Arbiter.<br>
										Please refer to @ref ImMxicWrArbiter for a set value.<br>
@param[in]		arbiter					Target arbiter.<br>
										Please refer to @ref ImMxicSpecArbiter for a set value.<br>
@param[in]		port					Target Port.<br>
										Please refer to @ref ImMxicPort for a set value.<br>
@param[in]		levelNumber			Target level.<br>
										Please refer to @ref MxicSlotLevelCtrl for a set value.<br>
@param[in]		priority				Priority level control settings.
										Please refer to @ref MxicSlotPriorityLevel for a set value.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32 mxic_slot_get_slot_priority( MxicSlot *self, SlotArgs priArgs, ImMxicPort port, 
		MxicSlotLevelCtrl levelNumber, MxicSlotPriorityLevel* const priority )
{
	UCHAR						regReadSw;
	INT32						result;
	volatile struct io_jdsmxic*	ioMxic;
    MxicSlotPrivate *priv = MXIC_SLOT_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (imMxicCheckLevelCtrlBlock( priArgs.wrArbiter, priArgs.arbiter, port, levelNumber ) != D_DDIM_OK) {
		// Input parameter error.
		Ddim_Assertion(("E:mxic_slot_get_slot_priority(): imMxicCheckLevelCtrlBlock error.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
	if ( priority == NULL ) {
		// priority parameter is NULL.
		Ddim_Assertion(("E:mxic_slot_get_slot_priority(): priority is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, priArgs.unit, &ioMxic );

	if ( result == D_DDIM_OK ) {

		mxic_utlis_on_pclk( priv->mxicUtlis, priArgs.unit );

		regReadSw = ioMxic->TRVSW.bit.TRVSW;

		if ( regReadSw == MxicUtlis_ON ) {
			ioMxic->TRVSW.bit.TRVSW = MxicUtlis_OFF;
		}

		if ( priArgs.wrArbiter == MxicUtlis_WR_ARBITER_W ) {

			if ( priArgs.unit != MxicUtlis_UNIT_4 ) {
				// Write arbiter.
				switch ( priArgs.arbiter ) {
					case MxicUtlis_SPEC_ARBITER_1:
						// arbiter1.
						switch ( levelNumber ) {
							case MxicUtlis_SLOT_LEVEL_CTRL_0:
								// Level0.
								priority->upperPriorityLevel = ioMxic->TLVLW1[port].bit.LPCCL0W;
								priority->lowerPriorityLevel = ioMxic->TLVLW1[port].bit.LPCSL0W;
								priority->priorityLevelType  = ioMxic->TLVLW1[port].bit.LPL0W;
								break;
							case MxicUtlis_SLOT_LEVEL_CTRL_1:
								// Level1.
								priority->upperPriorityLevel = ioMxic->TLVLW1[port].bit.LPCCL1W;
								priority->lowerPriorityLevel = ioMxic->TLVLW1[port].bit.LPCSL1W;
								priority->priorityLevelType  = ioMxic->TLVLW1[port].bit.LPL1W;
								break;
							case MxicUtlis_SLOT_LEVEL_CTRL_2:
								// Level2.
								priority->upperPriorityLevel = ioMxic->TLVLW1[port].bit.LPCCL2W;
								priority->lowerPriorityLevel = ioMxic->TLVLW1[port].bit.LPCSL2W;
								priority->priorityLevelType  = ioMxic->TLVLW1[port].bit.LPL2W;
								break;
							default:
								// levelNumber parameter value is illegal.
								result = MxicUtlis_INPUT_PARAM_ERROR;
								Ddim_Print(("E:mxic_slot_get_slot_priority(): levelNumber is illegal. levelNumber=%d\n", 
											levelNumber));
								break;
						}
						break;
					case MxicUtlis_SPEC_ARBITER_2:
						// arbiter2.
						switch ( levelNumber ) {
							case MxicUtlis_SLOT_LEVEL_CTRL_0:
								// Level0.
								priority->upperPriorityLevel = ioMxic->TLVLW2[port].bit.LPCCL0W;
								priority->lowerPriorityLevel = ioMxic->TLVLW2[port].bit.LPCSL0W;
								priority->priorityLevelType  = ioMxic->TLVLW2[port].bit.LPL0W;
								break;
							case MxicUtlis_SLOT_LEVEL_CTRL_1:
								// Level1.
								priority->upperPriorityLevel = ioMxic->TLVLW2[port].bit.LPCCL1W;
								priority->lowerPriorityLevel = ioMxic->TLVLW2[port].bit.LPCSL1W;
								priority->priorityLevelType  = ioMxic->TLVLW2[port].bit.LPL1W;
								break;
							case MxicUtlis_SLOT_LEVEL_CTRL_2:
								// Level2.
								priority->upperPriorityLevel = ioMxic->TLVLW2[port].bit.LPCCL2W;
								priority->lowerPriorityLevel = ioMxic->TLVLW2[port].bit.LPCSL2W;
								priority->priorityLevelType  = ioMxic->TLVLW2[port].bit.LPL2W;
								break;
							default:
								// levelNumber parameter value is illegal.
								result = MxicUtlis_INPUT_PARAM_ERROR;
								Ddim_Print(("E:mxic_slot_get_slot_priority(): levelNumber is illegal. levelNumber=%d\n", 
											levelNumber));
								break;
						}
						break;
					case MxicUtlis_SPEC_ARBITER_3:
						// arbiter3.
						switch ( levelNumber ) {
							case MxicUtlis_SLOT_LEVEL_CTRL_0:
								// Level0.
								priority->upperPriorityLevel = ioMxic->TLVLW3[port].bit.LPCCL0W;
								priority->lowerPriorityLevel = ioMxic->TLVLW3[port].bit.LPCSL0W;
								priority->priorityLevelType  = ioMxic->TLVLW3[port].bit.LPL0W;
								break;
							case MxicUtlis_SLOT_LEVEL_CTRL_1:
								// Level1.
								priority->upperPriorityLevel = ioMxic->TLVLW3[port].bit.LPCCL1W;
								priority->lowerPriorityLevel = ioMxic->TLVLW3[port].bit.LPCSL1W;
								priority->priorityLevelType  = ioMxic->TLVLW3[port].bit.LPL1W;
								break;
							case MxicUtlis_SLOT_LEVEL_CTRL_2:
								// Level2.
								priority->upperPriorityLevel = ioMxic->TLVLW3[port].bit.LPCCL2W;
								priority->lowerPriorityLevel = ioMxic->TLVLW3[port].bit.LPCSL2W;
								priority->priorityLevelType  = ioMxic->TLVLW3[port].bit.LPL2W;
								break;
							default:
								// levelNumber parameter value is illegal.
								result = MxicUtlis_INPUT_PARAM_ERROR;
								Ddim_Print(("E:mxic_slot_get_slot_priority(): levelNumber is illegal. levelNumber=%d\n", 
											levelNumber));
								break;
						}
						break;
					case MxicUtlis_SPEC_ARBITER_4:
						// arbiter4.
						switch ( levelNumber ) {
							case MxicUtlis_SLOT_LEVEL_CTRL_0:
								// Level0.
								priority->upperPriorityLevel = ioMxic->TLVLW4[port].bit.LPCCL0W;
								priority->lowerPriorityLevel = ioMxic->TLVLW4[port].bit.LPCSL0W;
								priority->priorityLevelType  = ioMxic->TLVLW4[port].bit.LPL0W;
								break;
							case MxicUtlis_SLOT_LEVEL_CTRL_1:
								// Level1.
								priority->upperPriorityLevel = ioMxic->TLVLW4[port].bit.LPCCL1W;
								priority->lowerPriorityLevel = ioMxic->TLVLW4[port].bit.LPCSL1W;
								priority->priorityLevelType  = ioMxic->TLVLW4[port].bit.LPL1W;
								break;
							case MxicUtlis_SLOT_LEVEL_CTRL_2:
								// Level2.
								priority->upperPriorityLevel = ioMxic->TLVLW4[port].bit.LPCCL2W;
								priority->lowerPriorityLevel = ioMxic->TLVLW4[port].bit.LPCSL2W;
								priority->priorityLevelType  = ioMxic->TLVLW4[port].bit.LPL2W;
								break;
							default:
								// levelNumber parameter value is illegal.
								result = MxicUtlis_INPUT_PARAM_ERROR;
								Ddim_Print(("E:mxic_slot_get_slot_priority(): levelNumber is illegal. levelNumber=%d\n", 
											levelNumber));
								break;
						}
						break;
					default:
						// arbiter parameter value is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_slot_get_slot_priority(): arbiter is illegal. arbiter=%d\n", 
									priArgs.arbiter));
						break;
				}
			}
			else {
				priority->upperPriorityLevel	= 0;
				priority->lowerPriorityLevel	= 0;
				priority->priorityLevelType	= 0;

				// Unit number is invalid.
				//Ddim_Print(("mxic_slot_get_slot_priority(): unit number is invalid. unit=%d\n", unit));
			}
		}
		else {
			if ( priArgs.unit != MxicUtlis_UNIT_0 ) {
				// Read arbiter.
				switch ( priArgs.arbiter ) {
					case MxicUtlis_SPEC_ARBITER_1:
						// arbiter1.
						switch ( levelNumber ) {
							case MxicUtlis_SLOT_LEVEL_CTRL_0:
								// Level0.
								priority->upperPriorityLevel = ioMxic->TLVLR1[port].bit.LPCCL0R;
								priority->lowerPriorityLevel = ioMxic->TLVLR1[port].bit.LPCSL0R;
								priority->priorityLevelType  = ioMxic->TLVLR1[port].bit.LPL0R;
								break;
							case MxicUtlis_SLOT_LEVEL_CTRL_1:
								// Level1.
								priority->upperPriorityLevel = ioMxic->TLVLR1[port].bit.LPCCL1R;
								priority->lowerPriorityLevel = ioMxic->TLVLR1[port].bit.LPCSL1R;
								priority->priorityLevelType  = ioMxic->TLVLR1[port].bit.LPL1R;
								break;
							case MxicUtlis_SLOT_LEVEL_CTRL_2:
								// Level2.
								priority->upperPriorityLevel = ioMxic->TLVLR1[port].bit.LPCCL2R;
								priority->lowerPriorityLevel = ioMxic->TLVLR1[port].bit.LPCSL2R;
								priority->priorityLevelType  = ioMxic->TLVLR1[port].bit.LPL2R;
								break;
							default:
								// levelNumber parameter value is illegal.
								result = MxicUtlis_INPUT_PARAM_ERROR;
								Ddim_Print(("E:mxic_slot_get_slot_priority(): levelNumber is illegal. levelNumber=%d\n", 
											levelNumber));
								break;
						}
						break;
					case MxicUtlis_SPEC_ARBITER_2:
						// arbiter2
						switch ( levelNumber ) {
							case MxicUtlis_SLOT_LEVEL_CTRL_0:
								// Level0.
								priority->upperPriorityLevel = ioMxic->TLVLR2[port].bit.LPCCL0R;
								priority->lowerPriorityLevel = ioMxic->TLVLR2[port].bit.LPCSL0R;
								priority->priorityLevelType  = ioMxic->TLVLR2[port].bit.LPL0R;
								break;
							case MxicUtlis_SLOT_LEVEL_CTRL_1:
								// Level1.
								priority->upperPriorityLevel = ioMxic->TLVLR2[port].bit.LPCCL1R;
								priority->lowerPriorityLevel = ioMxic->TLVLR2[port].bit.LPCSL1R;
								priority->priorityLevelType  = ioMxic->TLVLR2[port].bit.LPL1R;
								break;
							case MxicUtlis_SLOT_LEVEL_CTRL_2:
								// Level2.
								priority->upperPriorityLevel = ioMxic->TLVLR2[port].bit.LPCCL2R;
								priority->lowerPriorityLevel = ioMxic->TLVLR2[port].bit.LPCSL2R;
								priority->priorityLevelType  = ioMxic->TLVLR2[port].bit.LPL2R;
								break;
							default:
								// levelNumber parameter value is illegal.
								result = MxicUtlis_INPUT_PARAM_ERROR;
								Ddim_Print(("E:mxic_slot_get_slot_priority(): levelNumber is illegal. levelNumber=%d\n", 
											levelNumber));
								break;
						}
						break;
					case MxicUtlis_SPEC_ARBITER_3:
						// arbiter3.
						switch ( levelNumber ) {
							case MxicUtlis_SLOT_LEVEL_CTRL_0:
								// Level0.
								priority->upperPriorityLevel = ioMxic->TLVLR3[port].bit.LPCCL0R;
								priority->lowerPriorityLevel = ioMxic->TLVLR3[port].bit.LPCSL0R;
								priority->priorityLevelType  = ioMxic->TLVLR3[port].bit.LPL0R;
								break;
							case MxicUtlis_SLOT_LEVEL_CTRL_1:
								// Level1.
								priority->upperPriorityLevel = ioMxic->TLVLR3[port].bit.LPCCL1R;
								priority->lowerPriorityLevel = ioMxic->TLVLR3[port].bit.LPCSL1R;
								priority->priorityLevelType  = ioMxic->TLVLR3[port].bit.LPL1R;
								break;
							case MxicUtlis_SLOT_LEVEL_CTRL_2:
								// Level2.
								priority->upperPriorityLevel = ioMxic->TLVLR3[port].bit.LPCCL2R;
								priority->lowerPriorityLevel = ioMxic->TLVLR3[port].bit.LPCSL2R;
								priority->priorityLevelType  = ioMxic->TLVLR3[port].bit.LPL2R;
								break;
							default:
								// levelNumber parameter value is illegal.
								result = MxicUtlis_INPUT_PARAM_ERROR;
								Ddim_Print(("E:mxic_slot_get_slot_priority(): levelNumber is illegal. levelNumber=%d\n", 
											levelNumber));
								break;
						}
						break;
					case MxicUtlis_SPEC_ARBITER_4:
						// arbiter4.
						switch ( levelNumber ) {
							case MxicUtlis_SLOT_LEVEL_CTRL_0:
								// Level0.
								priority->upperPriorityLevel = ioMxic->TLVLR4[port].bit.LPCCL0R;
								priority->lowerPriorityLevel = ioMxic->TLVLR4[port].bit.LPCSL0R;
								priority->priorityLevelType  = ioMxic->TLVLR4[port].bit.LPL0R;
								break;
							case MxicUtlis_SLOT_LEVEL_CTRL_1:
								// Level1.
								priority->upperPriorityLevel = ioMxic->TLVLR4[port].bit.LPCCL1R;
								priority->lowerPriorityLevel = ioMxic->TLVLR4[port].bit.LPCSL1R;
								priority->priorityLevelType  = ioMxic->TLVLR4[port].bit.LPL1R;
								break;
							case MxicUtlis_SLOT_LEVEL_CTRL_2:
								// Level2.
								priority->upperPriorityLevel = ioMxic->TLVLR4[port].bit.LPCCL2R;
								priority->lowerPriorityLevel = ioMxic->TLVLR4[port].bit.LPCSL2R;
								priority->priorityLevelType  = ioMxic->TLVLR4[port].bit.LPL2R;
								break;
							default:
								// levelNumber parameter value is illegal.
								result = MxicUtlis_INPUT_PARAM_ERROR;
								Ddim_Print(("E:mxic_slot_get_slot_priority(): levelNumber is illegal. levelNumber=%d\n", 
											levelNumber));
								break;
						}
						break;
					default:
						// arbiter parameter value is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_slot_get_slot_priority(): arbiter is illegal. arbiter=%d\n", 
									priArgs.arbiter));
						break;
				}
			}
			else {
				priority->upperPriorityLevel	= 0;
				priority->lowerPriorityLevel	= 0;
				priority->priorityLevelType	= 0;

				// Unit number is invalid.
				//Ddim_Print(("mxic_slot_get_slot_priority(): unit number is invalid. unit=%d\n", unit));
			}
		}

		if ( regReadSw == MxicUtlis_ON ) {
			ioMxic->TRVSW.bit.TRVSW = MxicUtlis_ON;
		}

		mxic_utlis_off_pclk( priv->mxicUtlis, priArgs.unit );
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:mxic_slot_get_slot_priority(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

/**
This function set the slot priority level control to all arbiter.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		allPriority			Slot priority level control setting of all arbiter.
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
@remarks		The setting  ranges are from 1 to 64.
*/
INT32 mxic_slot_set_slot_priority_all_arbiter( MxicSlot *self, ImMxicUnit unit, 
		const MxicAllSlotPriority* const allPriority )
{
	INT32 result;
	INT32 i, j, k;
	SlotArgs priArgs;
	priArgs.unit = unit;

#ifdef CO_PARAM_CHECK
	if ( allPriority == NULL ) {
		// allPriority parameter is NULL.
		Ddim_Assertion(("E:mxic_slot_set_slot_priority_all_arbiter(): allPriority is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = D_DDIM_OK;

	// Set priority level control to all Write arbiter.
	for ( k = MxicUtlis_SLOT_LEVEL_CTRL_0; k < MxicUtlis_SLOT_LEVEL_CTRL_MAX; k++ ) {

	for ( i = MxicUtlis_W_ARBITER_W1; i < MxicUtlis_W_ARBITER_MAX; i++ ) {

		for ( j = MxicUtlis_PORT_0; j < MxicUtlis_PORT_MAX; j++ ) {
				priArgs.wrArbiter = MxicUtlis_WR_ARBITER_W;
				priArgs.arbiter = (ImMxicSpecArbiter)i;

				// Set priority level.
				switch ( k ) {
					case 0:
						result = mxic_slot_set_slot_priority( self, priArgs, (ImMxicPort)j, 
									(MxicSlotLevelCtrl)k, &allPriority->wLevel[i].level0[j] );
						break;
					case 1:
						result = mxic_slot_set_slot_priority( self, priArgs, (ImMxicPort)j, 
									(MxicSlotLevelCtrl)k, &allPriority->wLevel[i].level1[j] );
						break;
					case 2:
						result = mxic_slot_set_slot_priority( self, priArgs, (ImMxicPort)j, 
									(MxicSlotLevelCtrl)k, &allPriority->wLevel[i].level2[j] );
						break;
				}

				if ( result != D_DDIM_OK ) {
					// Priority level setting error.
					Ddim_Print(("E:mxic_slot_set_slot_priority_all_arbiter(): mxic_slot_set_slot_priority error.\n"));
					MxicUtlis_DSB();
					return result;
				}
			}
		}
	}

	// Set priority level control to all Read arbiter.
	for ( i = MxicUtlis_R_ARBITER_R1; i < MxicUtlis_R_ARBITER_MAX; i++ ) {

		for ( j = MxicUtlis_PORT_0; j < MxicUtlis_PORT_MAX; j++ ) {

			for ( k = MxicUtlis_SLOT_LEVEL_CTRL_0; k < MxicUtlis_SLOT_LEVEL_CTRL_MAX; k++ ) {
				priArgs.wrArbiter = MxicUtlis_WR_ARBITER_R;
				priArgs.arbiter = (ImMxicSpecArbiter)i;

				// Set priority level.
				switch ( k ) {
					case 0:
						result = mxic_slot_set_slot_priority( self, priArgs, (ImMxicPort)j, 
									(MxicSlotLevelCtrl)k, &allPriority->rLevel[i].level0[j] );
						break;
					case 1:
						result = mxic_slot_set_slot_priority( self, priArgs, (ImMxicPort)j, 
									(MxicSlotLevelCtrl)k, &allPriority->rLevel[i].level1[j] );
						break;
					case 2:
						result = mxic_slot_set_slot_priority( self, priArgs, (ImMxicPort)j, 
									(MxicSlotLevelCtrl)k, &allPriority->rLevel[i].level2[j] );
						break;
				}

				if ( result != D_DDIM_OK ) {
					// Priority level setting error.
					Ddim_Print(("E:mxic_slot_set_slot_priority_all_arbiter(): mxic_slot_set_slot_priority error.\n"));
					MxicUtlis_DSB();
					return result;
				}
			}
		}
	}

	MxicUtlis_DSB();

	return result;
}

/**
This function get the slot priority level control from all arbiter.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[out]		allPriority			Slot priority level control setting of all arbiter.
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32 mxic_slot_get_slot_priority_all_arbiter( MxicSlot *self, ImMxicUnit unit, 
												MxicAllSlotPriority* const allPriority )
{
	INT32 result;
	INT32 i, j, k;
	SlotArgs priArgs;
	priArgs.unit = unit;

#ifdef CO_PARAM_CHECK
	if ( allPriority == NULL ) {
		// allPriority parameter is NULL.
		Ddim_Assertion(("E:mxic_slot_get_slot_priority_all_arbiter(): allPriority is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = D_DDIM_OK;

	// Get priority level control to all Write arbiter.
	for ( i = MxicUtlis_W_ARBITER_W1; i < MxicUtlis_W_ARBITER_MAX; i++ ) {

		for ( j = MxicUtlis_PORT_0; j < MxicUtlis_PORT_MAX; j++ ) {

			for ( k = MxicUtlis_SLOT_LEVEL_CTRL_0; k < MxicUtlis_SLOT_LEVEL_CTRL_MAX; k++ ) {
				priArgs.wrArbiter = MxicUtlis_WR_ARBITER_W;
				priArgs.arbiter = (ImMxicSpecArbiter)i;
				// Get priority level.
				switch ( k ) {
					case 0:
						result = mxic_slot_get_slot_priority( self, priArgs, (ImMxicPort)j, 
								(MxicSlotLevelCtrl)k, &allPriority->wLevel[i].level0[j] );
						break;
					case 1:
						result = mxic_slot_get_slot_priority( self, priArgs, (ImMxicPort)j, 
								(MxicSlotLevelCtrl)k, &allPriority->wLevel[i].level1[j] );
						break;
					case 2:
						result = mxic_slot_get_slot_priority( self, priArgs, (ImMxicPort)j, 
								(MxicSlotLevelCtrl)k, &allPriority->wLevel[i].level2[j] );
						break;
				}

				if ( result != D_DDIM_OK ) {
					// Priority level setting error.
					Ddim_Print(("E:mxic_slot_get_slot_priority_all_arbiter(): mxic_slot_get_slot_priority error.\n"));
					MxicUtlis_DSB();
					return result;
				}
			}
		}
	}

	// Get priority level control to all Read arbiter.
	for ( k = MxicUtlis_SLOT_LEVEL_CTRL_0; k < MxicUtlis_SLOT_LEVEL_CTRL_MAX; k++ ) {
		
		for ( i = MxicUtlis_R_ARBITER_R1; i < MxicUtlis_R_ARBITER_MAX; i++ ) {

			for ( j = MxicUtlis_PORT_0; j < MxicUtlis_PORT_MAX; j++ ) {

				priArgs.wrArbiter = MxicUtlis_WR_ARBITER_R;
				priArgs.arbiter = (ImMxicSpecArbiter)i;

				// Get priority level.
				switch ( k ) {
					case 0:
						result = mxic_slot_get_slot_priority( self, priArgs, (ImMxicPort)j, 
								(MxicSlotLevelCtrl)k, &allPriority->rLevel[i].level0[j] );
						break;
					case 1:
						result = mxic_slot_get_slot_priority( self, priArgs, (ImMxicPort)j, 
								(MxicSlotLevelCtrl)k, &allPriority->rLevel[i].level1[j] );
						break;
					case 2:
						result = mxic_slot_get_slot_priority( self, priArgs, (ImMxicPort)j, 
								(MxicSlotLevelCtrl)k, &allPriority->rLevel[i].level2[j] );
						break;
				}

				if ( result != D_DDIM_OK ) {
					// Priority level setting error.
					Ddim_Print(("E:mxic_slot_get_slot_priority_all_arbiter(): mxic_slot_get_slot_priority error.\n"));
					MxicUtlis_DSB();
					return result;
				}
			}
		}
	}

	return result;
}

/**
This function set the slot mask.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		wrArbiter				Target write or read Arbiter.<br>
										Please refer to @ref ImMxicWrArbiter for a set value.<br>
@param[in]		arbiter					Target arbiter.<br>
										Please refer to @ref ImMxicSpecArbiter for a set value.<br>
@param[in]		port					Target Port.<br>
										Please refer to @ref ImMxicPort for a set value.<br>
@param[in]		slot					Target slot number.<br>
										Please refer to @ref ImMxicSlot for a set value. <br>
@param[in]		maskEnable				Slot mask enable.<br>
										<ul><li>@ref MxicUtlis_ON
											<li>@ref MxicUtlis_OFF</ul>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32 mxic_slot_set_slot_mask( MxicSlot *self, SlotArgs maskArgs, ImMxicPort port, 
								ImMxicSlot slot, UCHAR maskEnable )
{
	INT32						result;
	INT32						bitFlag;
	volatile struct io_jdsmxic*	ioMxic;
    MxicSlotPrivate *priv = MXIC_SLOT_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( imMxicCheckSlot( maskArgs.wrArbiter, maskArgs.arbiter, port, slot ) != D_DDIM_OK ) {
		// Parameter value is illegal.
		Ddim_Assertion(("E:mxic_slot_set_slot_mask(): imMxicCheckSlot error.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
	if ( ( maskEnable != MxicUtlis_ON ) && ( maskEnable != MxicUtlis_OFF ) ) {
		// maskEnable parameter value is illegal.
		Ddim_Assertion(("E:mxic_slot_set_slot_mask(): maskEnable is illegal. maskEnable=%d\n", maskEnable));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, maskArgs.unit, &ioMxic );

	if ( result == D_DDIM_OK ) {

		// Get bit flag for register access.
		result = im_mxic_get_slot_mask_bit_flag( slot, &bitFlag );

		if ( result != D_DDIM_OK ) {
			// Parameter error.
			Ddim_Print(("E:mxic_slot_set_slot_mask(): im_mxic_get_slot_mask_bit_flag error.\n"));
			return result;
		}

		mxic_utlis_on_pclk( priv->mxicUtlis, maskArgs.unit );

		// Set slot mask.
		if ( maskArgs.wrArbiter == MxicUtlis_WR_ARBITER_W ) {

			if ( maskArgs.unit != MxicUtlis_UNIT_4 ) {
				// Write arbiter.
				switch ( maskArgs.arbiter ) {
					case MxicUtlis_SPEC_ARBITER_1:
						if ( maskEnable == MxicUtlis_ON ) {
							ioMxic->TLVLW1[port].bit.LMLW |= bitFlag;
						}
						else {
							ioMxic->TLVLW1[port].bit.LMLW &= ~bitFlag;
						}
						break;
					case MxicUtlis_SPEC_ARBITER_2:
						if ( maskEnable == MxicUtlis_ON ) {
							ioMxic->TLVLW2[port].bit.LMLW |= bitFlag;
						}
						else {
							ioMxic->TLVLW2[port].bit.LMLW &= ~bitFlag;
						}
						break;
					case MxicUtlis_SPEC_ARBITER_3:
						if ( maskEnable == MxicUtlis_ON ) {
							ioMxic->TLVLW3[port].bit.LMLW |= bitFlag;
						}
						 else {
							ioMxic->TLVLW3[port].bit.LMLW &= ~bitFlag;
						}
						break;
					case MxicUtlis_SPEC_ARBITER_4:
						if ( maskEnable == MxicUtlis_ON ) {
							ioMxic->TLVLW4[port].bit.LMLW |= bitFlag;
						}
						else {
							ioMxic->TLVLW4[port].bit.LMLW &= ~bitFlag;
						}
						break;
					default:
						// arbiter parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_slot_set_slot_mask(): arbiter illegal. arbiter=%d\n", maskArgs.arbiter));
						break;
				}
			}
			else {
				// Unit number is invalid.
				//Ddim_Print(("mxic_slot_set_slot_mask(): unit number is invalid. unit=%d\n", unit));
			}
		}
		else {
			if ( maskArgs.unit != MxicUtlis_UNIT_0 ) {
				// Read arbiter.
				switch ( maskArgs.arbiter ) {
					case MxicUtlis_SPEC_ARBITER_1:
						if ( maskEnable == MxicUtlis_ON ) {
							ioMxic->TLVLR1[port].bit.LMLR |= bitFlag;
						}
						else {
							ioMxic->TLVLR1[port].bit.LMLR &= ~bitFlag;
						}
						break;
					case MxicUtlis_SPEC_ARBITER_2:
						if ( maskEnable == MxicUtlis_ON ) {
							ioMxic->TLVLR2[port].bit.LMLR |= bitFlag;
						}
						else {
							ioMxic->TLVLR2[port].bit.LMLR &= ~bitFlag;
						}
						break;
					case MxicUtlis_SPEC_ARBITER_3:
						if ( maskEnable == MxicUtlis_ON ) {
							ioMxic->TLVLR3[port].bit.LMLR |= bitFlag;
						}
						else {
							ioMxic->TLVLR3[port].bit.LMLR &= ~bitFlag;
						}
						break;
					case MxicUtlis_SPEC_ARBITER_4:
						if ( maskEnable == MxicUtlis_ON ) {
							ioMxic->TLVLR4[port].bit.LMLR |= bitFlag;
						}
						else {
							ioMxic->TLVLR4[port].bit.LMLR &= ~bitFlag;
						}
						break;
					default:
						// arbiter parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_slot_set_slot_mask(): arbiter illegal. arbiter=%d\n", maskArgs.arbiter));
						break;
				}
			}
			else {
				// Unit number is invalid.
				//Ddim_Print(("mxic_slot_set_slot_mask(): unit number is invalid. unit=%d\n", unit));
			}
		}

		mxic_utlis_off_pclk( priv->mxicUtlis, maskArgs.unit );

		MxicUtlis_DSB();
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:mxic_slot_set_slot_mask(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

/**
This function get the slot mask.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		wrArbiter				Target write or read Arbiter.<br>
										Please refer to @ref ImMxicWrArbiter for a set value.<br>
@param[in]		arbiter					Target arbiter.<br>
										Please refer to @ref ImMxicSpecArbiter for a set value.<br>
@param[in]		port					Target Port.<br>
										Please refer to @ref ImMxicPort for a set value.<br>
@param[in]		slot					Target slot number.<br>
										Please refer to @ref ImMxicSlot for a set value. <br>
@param[out]		maskEnable				Slot mask enable.<br>
										<ul><li>@ref MxicUtlis_ON
											<li>@ref MxicUtlis_OFF</ul>
@retval			D_DDIM_OK					Success
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error
*/
INT32 mxic_slot_get_slot_mask( MxicSlot *self, SlotArgs maskArgs, ImMxicPort port, 
								ImMxicSlot slot, UCHAR* const maskEnable )
{
	INT32						result;
	INT32						bitFlag;
	volatile struct io_jdsmxic*	ioMxic;
    MxicSlotPrivate *priv = MXIC_SLOT_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( imMxicCheckSlot( maskArgs.wrArbiter, maskArgs.arbiter, port, slot ) != D_DDIM_OK ) {
		// Parameter value is illegal.
		Ddim_Assertion(("E:mxic_slot_get_slot_mask(): imMxicCheckSlot error.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
	if ( maskEnable == NULL ) {
		// maskEnable parameter is NULL.
		Ddim_Assertion(("E:mxic_slot_get_slot_mask(): maskEnable is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, maskArgs.unit, &ioMxic );

	if ( result == D_DDIM_OK ) {

		// Get bit flag for register access.
		result = im_mxic_get_slot_mask_bit_flag( slot, &bitFlag );

		if ( result != D_DDIM_OK ) {
			// Parameter error.
			Ddim_Print(("E:mxic_slot_set_slot_mask(): im_mxic_get_slot_mask_bit_flag error.\n"));
			return result;
		}

		mxic_utlis_on_pclk( priv->mxicUtlis, maskArgs.unit );

		// Get slot mask.
		if ( maskArgs.wrArbiter == MxicUtlis_WR_ARBITER_W ) {

			if ( maskArgs.unit != MxicUtlis_UNIT_4 ) {
				// Write arbiter.
				switch ( maskArgs.arbiter ) {
					case MxicUtlis_SPEC_ARBITER_1:
						if ( ( ioMxic->TLVLW1[port].bit.LMLW & bitFlag ) != 0 ) {
							*maskEnable = MxicUtlis_ON;
						}
						else {
							*maskEnable = MxicUtlis_OFF;
						}
						break;
					case MxicUtlis_SPEC_ARBITER_2:
						if ( ( ioMxic->TLVLW2[port].bit.LMLW & bitFlag ) != 0 ) {
							*maskEnable = MxicUtlis_ON;
						}
						else {
							*maskEnable = MxicUtlis_OFF;
						}
						break;
					case MxicUtlis_SPEC_ARBITER_3:
						if ( ( ioMxic->TLVLW3[port].bit.LMLW & bitFlag ) != 0 ) {
							*maskEnable = MxicUtlis_ON;
						}
						else {
							*maskEnable = MxicUtlis_OFF;
						}
						break;
					case MxicUtlis_SPEC_ARBITER_4:
						if ( ( ioMxic->TLVLW4[port].bit.LMLW & bitFlag ) != 0 ) {
							*maskEnable = MxicUtlis_ON;
						}
						else {
							*maskEnable = MxicUtlis_OFF;
						}
						break;
					default:
						// arbiter parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_slot_set_slot_mask(): arbiter illegal. arbiter=%d\n", maskArgs.arbiter));
						break;
				}
			}
			else {
				*maskEnable = MxicUtlis_OFF;

				// Unit number is invalid.
//				Ddim_Print(("mxic_slot_set_slot_mask(): unit number is invalid. unit=%d\n", unit));
			}
		}
		else {
			if ( maskArgs.unit != MxicUtlis_UNIT_0 ) {
				// Read arbiter.
				switch ( maskArgs.arbiter ) {
					case MxicUtlis_SPEC_ARBITER_1:
						if ( ( ioMxic->TLVLR1[port].bit.LMLR & bitFlag ) != 0 ) {
							*maskEnable = MxicUtlis_ON;
						}
						else {
							*maskEnable = MxicUtlis_OFF;
						}
						break;
					case MxicUtlis_SPEC_ARBITER_2:
						if ( ( ioMxic->TLVLR2[port].bit.LMLR & bitFlag ) !=  0) {
							*maskEnable = MxicUtlis_ON;
						}
						else {
							*maskEnable = MxicUtlis_OFF;
						}
						break;
					case MxicUtlis_SPEC_ARBITER_3:
						if ( ( ioMxic->TLVLR3[port].bit.LMLR & bitFlag ) != 0 ) {
							*maskEnable = MxicUtlis_ON;
						}
						else {
							*maskEnable = MxicUtlis_OFF;
						}
						break;
					case MxicUtlis_SPEC_ARBITER_4:
						if ( ( ioMxic->TLVLR4[port].bit.LMLR & bitFlag ) != 0 ) {
							*maskEnable = MxicUtlis_ON;
						}
						else {
							*maskEnable = MxicUtlis_OFF;
						}
						break;
					default:
						// arbiter parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_slot_set_slot_mask(): arbiter illegal. arbiter=%d\n", maskArgs.arbiter));
						break;
				}
			}
			else {
				*maskEnable = MxicUtlis_OFF;

				// Unit number is invalid.
				//Ddim_Print(("mxic_slot_set_slot_mask(): unit number is invalid. unit=%d\n", unit));
			}
		}

		mxic_utlis_off_pclk( priv->mxicUtlis, maskArgs.unit );
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:mxic_slot_get_slot_mask(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

MxicSlot* mxic_slot_get(void)
{
	static MxicSlot* self = NULL;
	 if(!self){
		self = k_object_new_with_private(MXIC_TYPE_SLOT, sizeof(MxicSlotPrivate));
	 }
	return self;
}

MxicSlot *mxic_slot_new(void)
{
    MxicSlot* self = k_object_new_with_private(MXIC_TYPE_SLOT, sizeof(MxicSlotPrivate));
    return self;
}
