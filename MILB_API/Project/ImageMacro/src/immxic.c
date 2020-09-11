/***********************************************************************
 * @Copyright(C) 上海网用软件有限公司
 * @file immxic.c
 * @date 2020-09-02
 * @author: 吴海辉
 * @brief: 
 * @version: 1.0.0
***********************************************************************/

#include "immxic.h"
#include "mxicmasterslave.h"
#include "mxicmonitoraccess.h"
#include "mxiclevelport.h"
#include "mxicslot.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImMxic, im_mxic)
#define IM_MXIC_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImMxicPrivate, IM_TYPE_MXIC))

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
// TMIF interrupt flag bit
#define ImMxic_TMIF_BIT_TMF				(0x00000002)	// TMIF.TMF bit
#define ImMxic_TMIF_BIT_TDEWF			(0x00000004)	// TMIF.TDEWF bit
#define ImMxic_TMIF_BIT_TDERF			(0x00000008)	// TMIF.TDERF bit
#define ImMxic_TMIF_BIT_TSAWF			(0x00000010)	// TMIF.TSAWF bit

// Separated position of the master output port configuration register.
#define ImMxic_OUT_PORT_SEP_NUM	(64)

// Master LO/HI bit mask
#define ImMxic_MASTER_LO_MASK			(0x00000000FFFFFFFF)		// Master LO bit mask
#define ImMxic_MASTER_HI_MASK			(0xFFFFFFFF00000000)		// Master HI bit mask

// Number of arbiters in MXIC of the full spec composition.
#define ImMxic_FULL_SPEC_ARBITER_NUM		(4)
// Number of slots for each arbiter in MXIC of the full spec composition.
#define ImMxic_FULL_SPEC_SLOT_NUM		(4)
// Number of masters for each slot in MXIC of the full spec composition.
#define ImMxic_FULL_SPEC_MASTER_NUM		(16)
// Number of masters for each port in MXIC of the full spec composition.
#define ImMxic_FULL_SPEC_PORT_NUM		(4)

#define ImMxic_TMIF_BIT_TCF				(0x00000001)	// TMIF.TCF bit


/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
// Shift operation for creating setting TPORTMW, TPORTMR
#define ImMxic_SHIFT_TPORTMX(x, n)	((UINT64)(x & 0x01) << (n & 0x3F))

// Output port of the master setting acquisition from TPORTMW, TPORTMR
#define ImMxic_MASTER_OUT_PORT_TPORTMX(x, n)\
	(((x & ((UINT64)0x01 << (n & 0x3F))) != 0) ? MxicUtlis_PORT_GR_1 : MxicUtlis_PORT_GR_0 )


struct _ImMxicPrivate
{
	MxicUtlis* mxicUtlis;
	MxicLevelPort* mxicLevelPort;
	MxicMasterSlave* mxicMasterSlave;
	MxicMonitorAccess* mxicMonitorAccess;
	MxicSlot* mxicSlot;

	// Callback function pointer for detection of memory access.
	volatile VP_CALLBACK gImMxicMemoryAccessDetectCallback[MxicUtlis_UNIT_MAX];
};


/*----------------------------------------------------------------------*/
/* DECLS  															    */
/*----------------------------------------------------------------------*/
static INT32 imMxicInitAllLevelport( ImMxicUnit unit, ImMxicAllLevelport* allLevelport );


/*----------------------------------------------------------------------*/
/* IMPL  															    */
/*----------------------------------------------------------------------*/
static void im_mxic_constructor(ImMxic *self)
{
	ImMxicPrivate *priv = IM_MXIC_GET_PRIVATE(self);

	priv->mxicUtlis = mxic_utlis_new();
	priv->mxicLevelPort = mxic_level_port_new();
	priv->mxicMasterSlave = mxic_master_slave_new();
	priv->mxicMonitorAccess = mxic_monitor_access_new();
	priv->mxicSlot = mxic_slot_new();
	for (int i = 0; i < MxicUtlis_UNIT_MAX; i++)
	{
		priv->gImMxicMemoryAccessDetectCallback[i] = NULL;
	}
}

static void im_mxic_destructor(ImMxic *self)
{
	ImMxicPrivate *priv = IM_MXIC_GET_PRIVATE(self);

	if(priv->mxicUtlis)
	{
		k_object_unref(priv->mxicUtlis);
		priv->mxicUtlis = NULL;
	}
	if(priv->mxicLevelPort)
	{
		k_object_unref(priv->mxicLevelPort);
		priv->mxicLevelPort = NULL;
	}
	if(priv->mxicMasterSlave)
	{
		k_object_unref(priv->mxicMasterSlave);
		priv->mxicMasterSlave = NULL;
	}
	if(priv->mxicMonitorAccess)
	{
		k_object_unref(priv->mxicMonitorAccess);
		priv->mxicMonitorAccess = NULL;
	}
	if(priv->mxicSlot)
	{
		k_object_unref(priv->mxicSlot);
		priv->mxicSlot = NULL;
	}
}

/**
Init arbiter assign setting.<br>
@param[in]		unit						Target unit number.<br>
											Please refer to @ref ImMxicUnit for a set value. <br>
@param[out]		allLevelport				All LevelPort information.<br>
											Please refer to @ref ImMxicAllLevelport.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR		Fail - Parameter error.
*/
static INT32 imMxicInitAllLevelport( ImMxicUnit unit, ImMxicAllLevelport* allLevelport )
{
	INT32	i, j;
	INT32	result;

	result = D_DDIM_OK;

	for ( i = MxicUtlis_W_ARBITER_W1; i < MxicUtlis_W_ARBITER_MAX; i++ ) {

		for ( j = 0; j < MxicUtlis_MASTER_NUMBER_MAX-1; j++ ) {

			allLevelport->wArbiter[ i ].port[ j ]		= (ImMxicPort)0;
			allLevelport->wArbiter[ i ].level[ j ]	= (ImMxicLevel)0;
		}
	}

	for ( i = MxicUtlis_R_ARBITER_R1; i < MxicUtlis_R_ARBITER_MAX; i++ ) {

		for ( j = 0; j < MxicUtlis_MASTER_NUMBER_MAX-1; j++ ) {

			allLevelport->rArbiter[ i ].port[ j ]		= (ImMxicPort)0;
			allLevelport->rArbiter[ i ].level[ j ]	= (ImMxicLevel)0;
		}
	}

	switch ( unit ) {
		case MxicUtlis_UNIT_0:
			break;
		case MxicUtlis_UNIT_1:
		case MxicUtlis_UNIT_2:
			allLevelport->wArbiter[ MxicUtlis_W_ARBITER_W1 ].port[  9 ]	= MxicUtlis_PORT_1;
			allLevelport->wArbiter[ MxicUtlis_W_ARBITER_W1 ].port[ 10 ]	= MxicUtlis_PORT_1;
			allLevelport->wArbiter[ MxicUtlis_W_ARBITER_W1 ].port[ 11 ]	= MxicUtlis_PORT_1;
			allLevelport->wArbiter[ MxicUtlis_W_ARBITER_W1 ].port[ 12 ]	= MxicUtlis_PORT_1;
			allLevelport->wArbiter[ MxicUtlis_W_ARBITER_W1 ].port[ 13 ]	= MxicUtlis_PORT_1;
			allLevelport->wArbiter[ MxicUtlis_W_ARBITER_W1 ].port[ 14 ]	= MxicUtlis_PORT_1;
			allLevelport->rArbiter[ MxicUtlis_R_ARBITER_R1 ].port[ 13 ]	= MxicUtlis_PORT_1;
			break;
		case MxicUtlis_UNIT_3:
			allLevelport->wArbiter[ MxicUtlis_W_ARBITER_W1 ].port[  4 ]	= MxicUtlis_PORT_1;
			allLevelport->wArbiter[ MxicUtlis_W_ARBITER_W1 ].port[  5 ]	= MxicUtlis_PORT_1;
			allLevelport->wArbiter[ MxicUtlis_W_ARBITER_W1 ].port[  6 ]	= MxicUtlis_PORT_1;
			allLevelport->wArbiter[ MxicUtlis_W_ARBITER_W1 ].port[  8 ]	= MxicUtlis_PORT_2;
			allLevelport->wArbiter[ MxicUtlis_W_ARBITER_W1 ].port[ 16 ]	= MxicUtlis_PORT_2;
			allLevelport->rArbiter[ MxicUtlis_R_ARBITER_R1 ].port[  4 ]	= MxicUtlis_PORT_1;
			allLevelport->rArbiter[ MxicUtlis_R_ARBITER_R1 ].port[  5 ]	= MxicUtlis_PORT_1;
			allLevelport->rArbiter[ MxicUtlis_R_ARBITER_R1 ].port[  6 ]	= MxicUtlis_PORT_1;
			allLevelport->rArbiter[ MxicUtlis_R_ARBITER_R1 ].port[  7 ]	= MxicUtlis_PORT_1;
			allLevelport->rArbiter[ MxicUtlis_R_ARBITER_R1 ].port[  8 ]	= MxicUtlis_PORT_2;
			allLevelport->rArbiter[ MxicUtlis_R_ARBITER_R1 ].port[ 16 ]	= MxicUtlis_PORT_2;
			allLevelport->wArbiter[ MxicUtlis_W_ARBITER_W2 ].port[  9 ]	= MxicUtlis_PORT_1;
			allLevelport->wArbiter[ MxicUtlis_W_ARBITER_W2 ].port[ 11 ]	= MxicUtlis_PORT_1;
			allLevelport->wArbiter[ MxicUtlis_W_ARBITER_W2 ].port[ 12 ]	= MxicUtlis_PORT_1;
			allLevelport->wArbiter[ MxicUtlis_W_ARBITER_W2 ].port[ 13 ]	= MxicUtlis_PORT_1;
			allLevelport->rArbiter[ MxicUtlis_R_ARBITER_R2 ].port[  9 ]	= MxicUtlis_PORT_1;
			allLevelport->rArbiter[ MxicUtlis_R_ARBITER_R2 ].port[ 10 ]	= MxicUtlis_PORT_1;
			allLevelport->rArbiter[ MxicUtlis_R_ARBITER_R2 ].port[ 11 ]	= MxicUtlis_PORT_1;
			allLevelport->rArbiter[ MxicUtlis_R_ARBITER_R2 ].port[ 12 ]	= MxicUtlis_PORT_1;
			break;
		case MxicUtlis_UNIT_4:
		case MxicUtlis_UNIT_5:
		case MxicUtlis_UNIT_6:
			break;
		default :
			result = MxicUtlis_INPUT_PARAM_ERROR;
			Ddim_Print(("E:imMxicInitAllLevelport(): unit number(%d) is illegal.\n", unit));
			break;
	}

	return result;
}


/*----------------------------------------------------------------------*/
/* PUBLIC  															    */
/*----------------------------------------------------------------------*/
/**
This function set initial value to register.<br>
@param[in]		unit							Target unit number.<br>
												Please refer to @ref ImMxicUnit for a set value. <br>
@retval			D_DDIM_OK						Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR		Fail - Parameter error.
*/
INT32 im_mxic_init( ImMxic *self, ImMxicUnit unit )
{
	INT32										i, j, k;
	INT32										result;
	MxicAllArbiterAssign				allAssign;
	MxicAllSlotPriority			slot;
	ImMxicAllLevelport 					allLevelport;
	volatile struct io_jdsmxic*					ioMxic;
	volatile struct io_jdsmxic_tbl*				ioMxicTbl;
	ImMxicPrivate *priv = IM_MXIC_GET_PRIVATE(self);

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {

		mxic_utlis_on_pclk( priv->mxicUtlis, unit );

		// Because TCE/TCF is not used, the interruption is invalidated. 
		ioMxic->TMIE.bit.TCE = 0;
		ioMxic->TMIF.word &= ImMxic_TMIF_BIT_TCF;

		mxic_utlis_off_pclk( priv->mxicUtlis, unit );

		mxic_utlis_wait_command_enable( priv->mxicUtlis, unit, ioMxic );	// Wait TCFLG=1.

		mxic_utlis_set_taen( priv->mxicUtlis, unit, ioMxic, TRUE );		// TAEN-ON.

		// Set Slot priority level.
		// Write Slave.
		for ( i = MxicUtlis_W_ARBITER_W1; i < MxicUtlis_W_ARBITER_MAX; i++ ) {
			for ( j = MxicUtlis_PORT_0; j < MxicUtlis_PORT_MAX; j++ ) {
				// (Slave=1 or 2 or 3) and (port=0).
				if ( ( i == MxicUtlis_SPEC_ARBITER_1 || i == MxicUtlis_SPEC_ARBITER_2 
						|| i == MxicUtlis_SPEC_ARBITER_3 ) && ( j == MxicUtlis_PORT_0 )) {
					slot.wLevel[i].level0[j].priorityLevelType	= MxicUtlis_SLOT_PRIORITY_UPPER_ONLY;
					slot.wLevel[i].level0[j].upperPriorityLevel	= 5;
					slot.wLevel[i].level0[j].lowerPriorityLevel	= 0;
					slot.wLevel[i].level1[j].priorityLevelType	= MxicUtlis_SLOT_PRIORITY_UPPER;
					slot.wLevel[i].level1[j].upperPriorityLevel	= 0;
					slot.wLevel[i].level1[j].lowerPriorityLevel	= 0;
					slot.wLevel[i].level2[j].priorityLevelType	= MxicUtlis_SLOT_PRIORITY_UPPER;
					slot.wLevel[i].level2[j].upperPriorityLevel	= 0;
					slot.wLevel[i].level2[j].lowerPriorityLevel	= 0;
				}

				// (Slave=1 or 2 or 3) and (port=1).
				if ( ( i == MxicUtlis_SPEC_ARBITER_1 || i == MxicUtlis_SPEC_ARBITER_2 
						|| i == MxicUtlis_SPEC_ARBITER_3 ) && ( j == MxicUtlis_PORT_1 )) {
					slot.wLevel[i].level0[j].priorityLevelType	= MxicUtlis_SLOT_PRIORITY_UPPER_ONLY;
					slot.wLevel[i].level0[j].upperPriorityLevel	= 1;
					slot.wLevel[i].level0[j].lowerPriorityLevel	= 7;
					slot.wLevel[i].level1[j].priorityLevelType	= MxicUtlis_SLOT_PRIORITY_UPPER;
					slot.wLevel[i].level1[j].upperPriorityLevel	= 4;
					slot.wLevel[i].level1[j].lowerPriorityLevel	= 3;
					slot.wLevel[i].level2[j].priorityLevelType	= MxicUtlis_SLOT_PRIORITY_UPPER;
					slot.wLevel[i].level2[j].upperPriorityLevel	= 3;
					slot.wLevel[i].level2[j].lowerPriorityLevel	= 0;
				}

				// (Slave=1 or 2 or 3) and (port=2).
				if ( ( i == MxicUtlis_SPEC_ARBITER_1 || i == MxicUtlis_SPEC_ARBITER_2 
						|| i == MxicUtlis_SPEC_ARBITER_3 ) && ( j == MxicUtlis_PORT_2 )) {
					slot.wLevel[i].level0[j].priorityLevelType	= MxicUtlis_SLOT_PRIORITY_UPPER_ONLY;
					slot.wLevel[i].level0[j].upperPriorityLevel	= 3;
					slot.wLevel[i].level0[j].lowerPriorityLevel	= 8;
					slot.wLevel[i].level1[j].priorityLevelType	= MxicUtlis_SLOT_PRIORITY_UPPER;
					slot.wLevel[i].level1[j].upperPriorityLevel	= 5;
					slot.wLevel[i].level1[j].lowerPriorityLevel	= 3;
					slot.wLevel[i].level2[j].priorityLevelType	= MxicUtlis_SLOT_PRIORITY_UPPER;
					slot.wLevel[i].level2[j].upperPriorityLevel	= 3;
					slot.wLevel[i].level2[j].lowerPriorityLevel	= 0;
				}

				// (Slave=4).
				if ( i == MxicUtlis_SPEC_ARBITER_4 ) {

					if ( j == MxicUtlis_PORT_0 ) {
						slot.wLevel[i].level0[j].priorityLevelType	= MxicUtlis_SLOT_PRIORITY_UPPER_ONLY;
						slot.wLevel[i].level0[j].upperPriorityLevel	= 7;
						slot.wLevel[i].level0[j].lowerPriorityLevel	= 17;
					}
					else {
						slot.wLevel[i].level0[j].priorityLevelType	= MxicUtlis_SLOT_PRIORITY_UPPER;
						slot.wLevel[i].level0[j].upperPriorityLevel	= 0;
						slot.wLevel[i].level0[j].lowerPriorityLevel	= 0;
					}

					slot.wLevel[i].level1[j].priorityLevelType		= MxicUtlis_SLOT_PRIORITY_UPPER;

					if ( j == MxicUtlis_PORT_0 ) {
						slot.wLevel[i].level1[j].upperPriorityLevel	= 7;
						slot.wLevel[i].level1[j].lowerPriorityLevel	= 10;
					}
					else {
						slot.wLevel[i].level1[j].upperPriorityLevel	= 0;
						slot.wLevel[i].level1[j].lowerPriorityLevel	= 0;
					}

					slot.wLevel[i].level2[j].priorityLevelType		= MxicUtlis_SLOT_PRIORITY_UPPER;

					if ( j == MxicUtlis_PORT_0 ) {
						slot.wLevel[i].level2[j].upperPriorityLevel	= 4;
						slot.wLevel[i].level2[j].lowerPriorityLevel	= 6;
					}
					else {
						slot.wLevel[i].level2[j].upperPriorityLevel	= 0;
						slot.wLevel[i].level2[j].lowerPriorityLevel	= 0;
					}
				}
			}
		}

		// Read Slave.
		for ( i = MxicUtlis_R_ARBITER_R1; i < MxicUtlis_R_ARBITER_MAX; i++ ) {
			for ( j = MxicUtlis_PORT_0; j < MxicUtlis_PORT_MAX; j++ ) {
				// (Slave=1 or 2 or 3) and (port=0).
				if ( ( i == MxicUtlis_SPEC_ARBITER_1 || i == MxicUtlis_SPEC_ARBITER_2 
						|| i == MxicUtlis_SPEC_ARBITER_3 ) && ( j == MxicUtlis_PORT_0 ) ) {
					slot.rLevel[i].level0[j].priorityLevelType	= MxicUtlis_SLOT_PRIORITY_UPPER_ONLY;
					slot.rLevel[i].level0[j].upperPriorityLevel	= 5;
					slot.rLevel[i].level0[j].lowerPriorityLevel	= 0;
					slot.rLevel[i].level1[j].priorityLevelType	= MxicUtlis_SLOT_PRIORITY_UPPER;
					slot.rLevel[i].level1[j].upperPriorityLevel	= 0;
					slot.rLevel[i].level1[j].lowerPriorityLevel	= 0;
					slot.rLevel[i].level2[j].priorityLevelType	= MxicUtlis_SLOT_PRIORITY_UPPER;
					slot.rLevel[i].level2[j].upperPriorityLevel	= 0;
					slot.rLevel[i].level2[j].lowerPriorityLevel	= 0;
				}

				// (Slave=1 or 2 or 3) and (port=1).
				if ( ( i == MxicUtlis_SPEC_ARBITER_1 || i == MxicUtlis_SPEC_ARBITER_2 
						|| i == MxicUtlis_SPEC_ARBITER_3 ) && ( j == MxicUtlis_PORT_1 ) ) {
					slot.rLevel[i].level0[j].priorityLevelType	= MxicUtlis_SLOT_PRIORITY_UPPER_ONLY;
					slot.rLevel[i].level0[j].upperPriorityLevel	= 2;
					slot.rLevel[i].level0[j].lowerPriorityLevel	= 7;
					slot.rLevel[i].level1[j].priorityLevelType	= MxicUtlis_SLOT_PRIORITY_UPPER;
					slot.rLevel[i].level1[j].upperPriorityLevel	= 4;
					slot.rLevel[i].level1[j].lowerPriorityLevel	= 3;
					slot.rLevel[i].level2[j].priorityLevelType	= MxicUtlis_SLOT_PRIORITY_UPPER;
					slot.rLevel[i].level2[j].upperPriorityLevel	= 3;
					slot.rLevel[i].level2[j].lowerPriorityLevel	= 0;
				}

				// (Slave=1 or 2 or 3) and (port=2).
				if ( ( i == MxicUtlis_SPEC_ARBITER_1 || i == MxicUtlis_SPEC_ARBITER_2 
						|| i == MxicUtlis_SPEC_ARBITER_3 ) && ( j == MxicUtlis_PORT_2 ) ) {
					slot.rLevel[i].level0[j].priorityLevelType	= MxicUtlis_SLOT_PRIORITY_UPPER_ONLY;
					slot.rLevel[i].level0[j].upperPriorityLevel	= 3;
					slot.rLevel[i].level0[j].lowerPriorityLevel	= 8;
					slot.rLevel[i].level1[j].priorityLevelType	= MxicUtlis_SLOT_PRIORITY_UPPER;
					slot.rLevel[i].level1[j].upperPriorityLevel	= 5;
					slot.rLevel[i].level1[j].lowerPriorityLevel	= 3;
					slot.rLevel[i].level2[j].priorityLevelType	= MxicUtlis_SLOT_PRIORITY_UPPER;
					slot.rLevel[i].level2[j].upperPriorityLevel	= 3;
					slot.rLevel[i].level2[j].lowerPriorityLevel	= 0;
				}

				// (Slave=4).
				if ( i == MxicUtlis_SPEC_ARBITER_4 ) {

					if ( j == MxicUtlis_PORT_0 ) {
						slot.rLevel[i].level0[j].priorityLevelType	= MxicUtlis_SLOT_PRIORITY_UPPER_ONLY;
						slot.rLevel[i].level0[j].upperPriorityLevel	= 6;
						slot.rLevel[i].level0[j].lowerPriorityLevel	= 19;
					}
					else {
						slot.rLevel[i].level0[j].priorityLevelType	= MxicUtlis_SLOT_PRIORITY_UPPER;
						slot.rLevel[i].level0[j].upperPriorityLevel	= 0;
						slot.rLevel[i].level0[j].lowerPriorityLevel	= 0;
					}

					slot.rLevel[i].level1[j].priorityLevelType		= MxicUtlis_SLOT_PRIORITY_UPPER;

					if ( j == MxicUtlis_PORT_0 ) {
						slot.rLevel[i].level1[j].upperPriorityLevel	= 7;
						slot.rLevel[i].level1[j].lowerPriorityLevel	= 12;
					}
					else {
						slot.rLevel[i].level1[j].upperPriorityLevel	= 0;
						slot.rLevel[i].level1[j].lowerPriorityLevel	= 0;
					}

					slot.rLevel[i].level2[j].priorityLevelType		= MxicUtlis_SLOT_PRIORITY_UPPER;

					if ( j == MxicUtlis_PORT_0 ) {
						slot.rLevel[i].level2[j].upperPriorityLevel	= 6;
						slot.rLevel[i].level2[j].lowerPriorityLevel	= 6;
					}
					else {
						slot.rLevel[i].level2[j].upperPriorityLevel	= 0;
						slot.rLevel[i].level2[j].lowerPriorityLevel	= 0;
					}
				}
			}
		}

		(VOID)mxic_utlis_init_arbiter_assign( priv->mxicUtlis, unit, &allAssign );

		mxic_utlis_on_pclk( priv->mxicUtlis, unit );

		// Set configuration target arbiter.(All target arbiter initialize).
		// Configuration Start is executed by mxic_master_slave_set_master_all_arbiter() API proccess.
		if ( unit != MxicUtlis_UNIT_4 ) {
			ioMxic->TCFMD.bit.TENW_1	= 1;
			ioMxic->TCFMD.bit.TENW_2	= 1;
			ioMxic->TCFMD.bit.TENW_3	= 1;
			ioMxic->TCFMD.bit.TENW_4	= 1;
		}

		if ( unit != MxicUtlis_UNIT_0 ) {
			ioMxic->TCFMD.bit.TENR_1	= 1;
			ioMxic->TCFMD.bit.TENR_2	= 1;
			ioMxic->TCFMD.bit.TENR_3	= 1;
			ioMxic->TCFMD.bit.TENR_4	= 1;
		}

		if ( unit == MxicUtlis_UNIT_3 ) {
			ioMxic->TGCFMD.bit.TEGW_0	= 1;
			ioMxic->TGCFMD.bit.TEGW_1	= 1;
			ioMxic->TGCFMD.bit.TEGW_2	= 1;
			ioMxic->TGCFMD.bit.TEGW_3	= 0;	// No assign(No target).
			ioMxic->TGCFMD.bit.TEGW_4	= 0;	// No assign(No target).
			ioMxic->TGCFMD.bit.TEGW_5	= 0;	// No assign(No target).
			ioMxic->TGCFMD.bit.TEGW_6	= 0;	// No assign(No target).
			ioMxic->TGCFMD.bit.TEGW_7	= 0;	// No assign(No target).
			ioMxic->TGCFMD.bit.TEGR_0	= 1;
			ioMxic->TGCFMD.bit.TEGR_1	= 1;
			ioMxic->TGCFMD.bit.TEGR_2	= 1;
			ioMxic->TGCFMD.bit.TEGR_3	= 0;	// No assign(No target).
			ioMxic->TGCFMD.bit.TEGR_4	= 0;	// No assign(No target).
			ioMxic->TGCFMD.bit.TEGR_5	= 0;	// No assign(No target).
			ioMxic->TGCFMD.bit.TEGR_6	= 0;	// No assign(No target).
			ioMxic->TGCFMD.bit.TEGR_7	= 0;	// No assign(No target).
		}

		mxic_utlis_off_pclk( priv->mxicUtlis, unit );

		if ( ( unit == MxicUtlis_UNIT_1 ) || ( unit == MxicUtlis_UNIT_2 ) || ( unit == MxicUtlis_UNIT_3 ) ) {
			(VOID)mxic_utlis_get_unit_tbl_address( priv->mxicUtlis, unit, &ioMxicTbl );

			if ( unit == MxicUtlis_UNIT_3 ) {
				DDIM_User_AhbReg_SpinLock();	// JPEG issue work around.
			}

			// Initialize all TSL* register.
			mxic_utlis_on_hclk( priv->mxicUtlis, unit );

			for ( i = 0; i < ImMxic_FULL_SPEC_PORT_NUM; i++ ) {
				for ( j = 0; j < ImMxic_FULL_SPEC_SLOT_NUM; j++ ) {
					for ( k = 0; k < ImMxic_FULL_SPEC_MASTER_NUM; k++ ) {
						ioMxicTbl->TSLW_1[i].byte[j][k] = 0;	// Reserve code.
						ioMxicTbl->TSLW_2[i].byte[j][k] = 0;	// Reserve code.
						ioMxicTbl->TSLW_3[i].byte[j][k] = 0;	// Reserve code.
						ioMxicTbl->TSLW_4[i].byte[j][k] = 0;	// Reserve code.
						ioMxicTbl->TSLR_1[i].byte[j][k] = 0;	// Reserve code.
						ioMxicTbl->TSLR_2[i].byte[j][k] = 0;	// Reserve code.
						ioMxicTbl->TSLR_3[i].byte[j][k] = 0;	// Reserve code.
						ioMxicTbl->TSLR_4[i].byte[j][k] = 0;	// Reserve code.
					}
				}
			}

			mxic_utlis_off_hclk( priv->mxicUtlis, unit );

			if ( unit == MxicUtlis_UNIT_3 ) {
				DDIM_User_AhbReg_SpinUnLock();	// JPEG issue work around.
			}
		}

		mxic_utlis_set_taen( priv->mxicUtlis, unit, ioMxic, FALSE );	// TAEN-OFF.

		// Set all channel allocation.
		result = mxic_master_slave_set_master_all_arbiter( priv->mxicMasterSlave, unit, &allAssign );

		if ( result == D_DDIM_OK ) {

			result = mxic_slot_set_slot_priority_all_arbiter(priv->mxicSlot, unit, &slot );

			if ( result != D_DDIM_OK ) {
				Ddim_Print(("E:im_mxic_init(): mxic_slot_set_slot_priority_all_arbiter error. result=%d\n", result));
			}

			(VOID)imMxicInitAllLevelport( unit, &allLevelport );

			result = mxic_level_port_set_levelport_all( priv->mxicLevelPort, unit, &allLevelport );

			if ( result != D_DDIM_OK ) {
				Ddim_Print(("E:im_mxic_init(): Im_MXIC_Set_LevelPort_All error. result=%d\n", result));
			}
		}
		else {
			Ddim_Print(("E:im_mxic_init(): mxic_master_slave_set_master_all_arbiter error. result=%d\n", result));
		}

		MxicUtlis_DSB();
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:im_mxic_init(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

/**
This function does software reset.<br>
@param[in]		unit							Target unit number.<br>
												Please refer to @ref ImMxicUnit for a set value. <br>
@retval			D_DDIM_OK						Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR		Fail - Parameter error.
*/
INT32 im_mxic_reset( ImMxic *self, ImMxicUnit unit )
{
	INT32						result;
	volatile struct io_jdsmxic*	ioMxic;
	ImMxicPrivate *priv = IM_MXIC_GET_PRIVATE(self);

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {

		mxic_utlis_on_pclk( priv->mxicUtlis, unit );

		// Reset release.
		ioMxic->TMIRST.bit.SR = 0;

		mxic_utlis_off_pclk( priv->mxicUtlis, unit );
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:im_mxic_reset(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

/**
This function select arbiters of executed "configration start" and start configuration.<br>
@param [in]		unit							Target unit number.<br>
												Please refer to @ref ImMxicUnit for a set value. <br>
@param [in]		targetArbiter					Target arbiter of configration start.<br>
@retval			D_DDIM_OK						Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR		Fail - Parameter error.
@remarks		Duplication setup of the master number to another port of the same slave including a read channel / write channel is prohibition.<br>
				In this case, this function returns the error.<br>
				And, the allocation setting of the master is returned to the setting operating now.
*/
INT32 im_mxic_start_config( ImMxic *self, ImMxicUnit unit, const ImMxicConfigArbiter* const targetArbiter )
{
	INT32						result;
	volatile struct io_jdsmxic*	ioMxic;
	ImMxicPrivate *priv = IM_MXIC_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( targetArbiter == NULL ) {
		// targetArbiter parameter is NULL.
		Ddim_Assertion(("E:im_mxic_start_config(): targetArbiter is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {

		mxic_utlis_wait_command_enable( priv->mxicUtlis, unit, ioMxic );		// Wait TCFLG=1.

		mxic_utlis_on_pclk( priv->mxicUtlis, unit );

		// Set configuration target arbiter.
		if ( unit != MxicUtlis_UNIT_4 ) {
			ioMxic->TCFMD.bit.TENW_1 = targetArbiter->slW1ConfigOnFlg;
			ioMxic->TCFMD.bit.TENW_2 = targetArbiter->slW2ConfigOnFlg;
			ioMxic->TCFMD.bit.TENW_3 = targetArbiter->slW3ConfigOnFlg;
			ioMxic->TCFMD.bit.TENW_4 = targetArbiter->slW4ConfigOnFlg;
		}
		if ( unit != MxicUtlis_UNIT_0 ) {
			ioMxic->TCFMD.bit.TENR_1 = targetArbiter->slR1ConfigOnFlg;
			ioMxic->TCFMD.bit.TENR_2 = targetArbiter->slR2ConfigOnFlg;
			ioMxic->TCFMD.bit.TENR_3 = targetArbiter->slR3ConfigOnFlg;
			ioMxic->TCFMD.bit.TENR_4 = targetArbiter->slR4ConfigOnFlg;
		}
		if ( unit == MxicUtlis_UNIT_3 ) {
			ioMxic->TGCFMD.bit.TEGW_0 = targetArbiter->grW0ConfigOnFlg;
			ioMxic->TGCFMD.bit.TEGW_1 = targetArbiter->grW1ConfigOnFlg;
			ioMxic->TGCFMD.bit.TEGW_2 = targetArbiter->grW2ConfigOnFlg;
			ioMxic->TGCFMD.bit.TEGW_3 = targetArbiter->grW3ConfigOnFlg;
			ioMxic->TGCFMD.bit.TEGW_4 = targetArbiter->grW4ConfigOnFlg;
			ioMxic->TGCFMD.bit.TEGW_5 = targetArbiter->grW5ConfigOnFlg;
			ioMxic->TGCFMD.bit.TEGW_6 = targetArbiter->grW6ConfigOnFlg;
			ioMxic->TGCFMD.bit.TEGW_7 = targetArbiter->grW7ConfigOnFlg;
			ioMxic->TGCFMD.bit.TEGR_0 = targetArbiter->grR0ConfigOnFlg;
			ioMxic->TGCFMD.bit.TEGR_1 = targetArbiter->grR1ConfigOnFlg;
			ioMxic->TGCFMD.bit.TEGR_2 = targetArbiter->grR2ConfigOnFlg;
			ioMxic->TGCFMD.bit.TEGR_3 = targetArbiter->grR3ConfigOnFlg;
			ioMxic->TGCFMD.bit.TEGR_4 = targetArbiter->grR4ConfigOnFlg;
			ioMxic->TGCFMD.bit.TEGR_5 = targetArbiter->grR5ConfigOnFlg;
			ioMxic->TGCFMD.bit.TEGR_6 = targetArbiter->grR6ConfigOnFlg;
			ioMxic->TGCFMD.bit.TEGR_7 = targetArbiter->grR7ConfigOnFlg;
		}
		// Configuration start.
		mxic_utlis_process_configuration( priv->mxicUtlis, unit, ioMxic );

		mxic_utlis_off_pclk( priv->mxicUtlis, unit );
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:im_mxic_start_config(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

/**
Detection of Memory Access Area" are started with this function.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		param					Setting of detection parameters of slave each memory access.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32 im_mxic_start_memory_access_detect( ImMxic *self, ImMxicUnit unit, 
											const MxicMemoryAccessSlave* const param )
{
	INT32						i;
	INT32						result;
	volatile struct io_jdsmxic*	ioMxic;
	ImMxicPrivate *priv = IM_MXIC_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( param == NULL ) {
		// param parameter is NULL.
		Ddim_Assertion(("E:im_mxic_start_memory_access_detect(): param is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {

		if ( unit != MxicUtlis_UNIT_4 ) {

			mxic_utlis_on_pclk( priv->mxicUtlis, unit );

			// Start detect memory access.
			for ( i = MxicUtlis_W_ARBITER_W1; i < MxicUtlis_W_ARBITER_MAX; i++ ) {
				ioMxic->TSASETW[i].bit.TSATRGW = param->slave[i].startTrigger;
			}

			mxic_utlis_off_pclk( priv->mxicUtlis, unit );

			MxicUtlis_DSB();
		}
		else {
			// Unit number is invalid.
			//Ddim_Print(("im_mxic_start_memory_access_detect(): unit number is invalid. unit=%d\n", unit));
		}
	}
	else {
		// Error.
		Ddim_Print(("E:im_mxic_start_memory_access_detect(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

/**
Detection of Memory Access Area" are stoped with this function.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32 im_mxic_stop_memory_access_detect( ImMxic *self, ImMxicUnit unit )
{
	INT32						i;
	INT32						result;
	volatile struct io_jdsmxic*	ioMxic;
	ImMxicPrivate *priv = IM_MXIC_GET_PRIVATE(self);

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {

		if ( unit != MxicUtlis_UNIT_4 ) {

			// Stop monitor.
			mxic_utlis_on_pclk( priv->mxicUtlis, unit );

			for ( i = MxicUtlis_W_ARBITER_W1; i < MxicUtlis_W_ARBITER_MAX; i++ ) {
				ioMxic->TSASETW[i].bit.TSATRGW = 0;
			}

			mxic_utlis_off_pclk( priv->mxicUtlis, unit );

			MxicUtlis_DSB();
		}
		else {
			// Unit number is invalid.
			// Ddim_Print(("im_mxic_stop_memory_access_detect(): unit number is invalid. unit=%d\n", unit));
		}
	}
	else {
		// Error.
		Ddim_Print(("E:im_mxic_stop_memory_access_detect(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

/**
This function set the parameter of Detection parameters of slave each memory access.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		param					Setting of detection parameters of slave each memory access.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
@remarks		Change of a parameter is reflected at the time of the detection start by @ref im_mxic_start_memory_access_detect function. 
*/
INT32 im_mxic_set_memory_access_detect( ImMxic *self, ImMxicUnit unit, 
										const MxicMemoryAccessSlave* const param )
{
	INT32						i;
	INT32						result;
	volatile struct io_jdsmxic*	ioMxic;
	ImMxicPrivate *priv = IM_MXIC_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( param == NULL ) {
		// param parameter is NULL.
		Ddim_Assertion(("E:im_mxic_set_memory_access_detect(): param is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {

		if ( unit != MxicUtlis_UNIT_4 ) {

			mxic_utlis_on_pclk( priv->mxicUtlis, unit );

			for ( i = MxicUtlis_W_ARBITER_W1; i < MxicUtlis_W_ARBITER_MAX; i++ ) {
				memset((VOID*)&ioMxic->TSASETW[i], 0, sizeof(ioMxic->TSASETW[i]));
			}

			// Set detection of memory access register. (TSASETW)
			for ( i = MxicUtlis_W_ARBITER_W1; i < MxicUtlis_W_ARBITER_MAX; i++ ) {
				if ( param->slave[i].startTrigger == MxicUtlis_ON ) {
					ioMxic->TSASETW[i].bit.TSAMASW47_1_LO		= (ULONG)((param->slave[i].master47M1   
																& ImMxic_MASTER_LO_MASK));
					ioMxic->TSASETW[i].bit.TSAMASW47_1_HI		= (ULONG)((param->slave[i].master47M1   
																& ImMxic_MASTER_HI_MASK) >> 32);
					ioMxic->TSASETW[i].bit.TSAMASW127_64_LO	= (ULONG)((param->slave[i].master127M64 
																& ImMxic_MASTER_LO_MASK));
					ioMxic->TSASETW[i].bit.TSAMASW127_64_HI	= (ULONG)((param->slave[i].master127M64 
																& ImMxic_MASTER_HI_MASK) >> 32);
					ioMxic->TSASETW[i].bit.TSASADW				= param->slave[i].startAddress;
					ioMxic->TSASETW[i].bit.TSAEADW				= param->slave[i].endAddress;
					ioMxic->TSASETW[i].bit.TSARW				= param->slave[i].mode;
				}
			}

			// The TMF interrupt is enable.
			ioMxic->TMIE.bit.TSAWE = 1;

			mxic_utlis_off_pclk( priv->mxicUtlis, unit );

			MxicUtlis_DSB();

			// Set callback for TMF interrupt.
			priv->gImMxicMemoryAccessDetectCallback[unit] = param->pCallBack;
		}
		else {
			// Unit number is invalid.
			// Ddim_Print(("im_mxic_set_memory_access_detect(): unit number is invalid. unit=%d\n", unit));
		}
	}
	else {
		// Error.
		Ddim_Print(("E:im_mxic_set_memory_access_detect(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

/**
This function get the parameter of Detection parameters of slave each memory access.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		param					Setting of detection parameters of slave each memory access.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
@remarks		Change of a parameter is reflected at the time of the detection start by @ref im_mxic_start_memory_access_detect function. 
*/
INT32 im_mxic_get_memory_access_detect( ImMxic *self, ImMxicUnit unit, MxicMemoryAccessSlave* const param )
{
	INT32						i;
	INT32						result;
	UINT64						w47W1		= 0;
	UINT64						w127W64	= 0;
	volatile struct io_jdsmxic*	ioMxic;
	ImMxicPrivate *priv = IM_MXIC_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( param == NULL ) {
		// param parameter is NULL.
		Ddim_Assertion(("E:im_mxic_get_memory_access_detect(): param is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {

		if ( unit != MxicUtlis_UNIT_4 ) {

			mxic_utlis_on_pclk( priv->mxicUtlis, unit );

			// Set detection of memory access register. (TSASETW)
			for ( i = MxicUtlis_W_ARBITER_W1; i < MxicUtlis_W_ARBITER_MAX; i++ ) {
				param->slave[i].startTrigger	= ioMxic->TSASETW[i].bit.TSATRGW;
				w47W1							= ioMxic->TSASETW[i].bit.TSAMASW47_1_HI;
				w47W1							= (w47W1 << 32) | ioMxic->TSASETW[i].bit.TSAMASW47_1_LO;
				param->slave[i].master47M1		= w47W1;
				w127W64							= ioMxic->TSASETW[i].bit.TSAMASW127_64_HI;
				w127W64							= (w127W64 << 32) | ioMxic->TSASETW[i].bit.TSAMASW127_64_LO;
				param->slave[i].master127M64	= w127W64;
				param->slave[i].startAddress	= ioMxic->TSASETW[i].bit.TSASADW;
				param->slave[i].endAddress		= ioMxic->TSASETW[i].bit.TSAEADW;
				param->slave[i].mode			= ioMxic->TSASETW[i].bit.TSARW;
				param->slave[i].detectMaster	= ioMxic->TSASETW[i].bit.TSAMNSTW;
				param->slave[i].detectAddress	= ioMxic->TSASETW[i].bit.TSAADSTW;
			}

			mxic_utlis_off_pclk( priv->mxicUtlis, unit );

			// Set callback for TMF interrupt.
			param->pCallBack = priv->gImMxicMemoryAccessDetectCallback[unit];
		}
		else {
			// Unit number is invalid.
			//Ddim_Print(("im_mxic_get_memory_access_detect(): unit number is invalid. unit=%d\n", unit));
		}
	}
	else {
		// Error.
		Ddim_Print(("E:im_mxic_get_memory_access_detect(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

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
INT32	im_mxic_set_reg_read_switch( ImMxic *self, ImMxicUnit unit, UCHAR sw )
{
	INT32						result;
	volatile struct io_jdsmxic*	ioMxic;
	ImMxicPrivate *priv = IM_MXIC_GET_PRIVATE(self);

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {
		mxic_utlis_on_pclk( priv->mxicUtlis, unit );
		ioMxic->TRVSW.bit.TRVSW = sw;
		mxic_utlis_off_pclk( priv->mxicUtlis, unit );
		MxicUtlis_DSB();
	}
	else {
		// Error.
		Ddim_Print(("E:im_mxic_set_reg_read_switch(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

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
INT32	im_mxic_get_reg_read_switch( ImMxic *self, ImMxicUnit unit, UCHAR *const sw )
{
	INT32						result;
	volatile struct io_jdsmxic*	ioMxic;
	ImMxicPrivate *priv = IM_MXIC_GET_PRIVATE(self);

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {
		mxic_utlis_on_pclk( priv->mxicUtlis, unit );
		*sw = ioMxic->TRVSW.bit.TRVSW;
		mxic_utlis_off_pclk( priv->mxicUtlis, unit );
	}
	else {
		// Error.
		Ddim_Print(("E:im_mxic_get_reg_read_switch(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

/**
This function set output port.<br>
@param[in]		target					Setting target master.<br>
										<ul><li>@ref MxicUtlis_3_W_ELA
											<li>@ref MxicUtlis_3_W_XCH
											<li>@ref MxicUtlis_3_W_FPT_0
											<li>@ref MxicUtlis_3_W_FPT_1
											<li>@ref MxicUtlis_3_R_ELA
											<li>@ref MxicUtlis_3_R_XCH
											<li>@ref MxicUtlis_3_R_FPT_0
											<li>@ref MxicUtlis_3_R_FPT_1
@param[in]		outPort				Setting of output port.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32	im_mxic_set_output_port( ImMxic *self, UCHAR target, ImMxicPortGr outputPort )
{
	UCHAR				regReadSw;
	UCHAR				writeMaster;
	UCHAR				readMaster;
	UINT32				portSettingWorkLo;
	UINT32				portSettingWorkHi;
	UINT64				portSetMask = 1;
	ImMxicPrivate *priv = IM_MXIC_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( outputPort >= MxicUtlis_PORT_GR_MAX ) {
		// port parameter is illegal.
		Ddim_Assertion(("E:im_mxic_set_output_port(): outputPort=%d.\n", outputPort));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	mxic_utlis_wait_command_enable( priv->mxicUtlis, MxicUtlis_UNIT_3, (struct io_jdsmxic *)&IO_MXIC3 );// Wait TCFLG=1.

	mxic_utlis_on_pclk( priv->mxicUtlis, MxicUtlis_UNIT_3 );

	regReadSw = IO_MXIC3.TRVSW.bit.TRVSW;

	if ( regReadSw == MxicUtlis_ON ) {
		IO_MXIC3.TRVSW.bit.TRVSW = MxicUtlis_OFF;
	}

	if ( target <= MxicUtlis_READ_MASTER_FLG_MASK ) {
		// Write master.
		if ( target >= ImMxic_OUT_PORT_SEP_NUM ) {

			portSettingWorkLo	= IO_MXIC3.TPORTMW.bit.TPORTMW_127_64_LO;
			portSettingWorkHi	= IO_MXIC3.TPORTMW.bit.TPORTMW_127_64_HI;
			writeMaster			= target - ImMxic_OUT_PORT_SEP_NUM;

			if ( writeMaster >= 32 ) {

				portSetMask <<= ( writeMaster - 32 );

				if ( outputPort == MxicUtlis_PORT_GR_0 ) {
					portSettingWorkHi &= ~portSetMask;
				}
				else {
					portSettingWorkHi |= portSetMask;
				}
			}
			else {

				portSetMask <<= writeMaster;

				if ( outputPort == MxicUtlis_PORT_GR_0 ) {
					portSettingWorkLo &= ~portSetMask;
				}
				else {
					portSettingWorkLo |= portSetMask;
				}
			}

			IO_MXIC3.TPORTMW.bit.TPORTMW_127_64_LO = portSettingWorkLo;
			IO_MXIC3.TPORTMW.bit.TPORTMW_127_64_HI = portSettingWorkHi;
		}
		else {
			// target parameter is illegal.
			Ddim_Assertion(("E:im_mxic_set_output_port(): target=%d.\n", target));
			return MxicUtlis_INPUT_PARAM_ERROR;
		}
	}
	else {
		// Read master.
		readMaster = (target & MxicUtlis_READ_MASTER_FLG_MASK);

		if ( readMaster >= ImMxic_OUT_PORT_SEP_NUM ) {

			portSettingWorkLo	= IO_MXIC3.TPORTMR.bit.TPORTMR_127_64_LO;
			portSettingWorkHi	= IO_MXIC3.TPORTMR.bit.TPORTMR_127_64_HI;
			readMaster				-= ImMxic_OUT_PORT_SEP_NUM;

			if ( readMaster >= 32 ) {

				portSetMask <<= ( readMaster - 32 );

				if ( outputPort == MxicUtlis_PORT_GR_0 ) {
					portSettingWorkHi &= ~portSetMask;
				}
				else {
					portSettingWorkHi |= portSetMask;
				}
			}
			else {

				portSetMask <<= readMaster;

				if ( outputPort == MxicUtlis_PORT_GR_0 ) {
					portSettingWorkLo &= ~portSetMask;
				}
				else {
					portSettingWorkLo |= portSetMask;
				}
			}

			IO_MXIC3.TPORTMR.bit.TPORTMR_127_64_LO = portSettingWorkLo;
			IO_MXIC3.TPORTMR.bit.TPORTMR_127_64_HI = portSettingWorkHi;
		}
		else {
			// target parameter is illegal.
			Ddim_Assertion(("E:im_mxic_set_output_port(): target=%d.\n", target));
			return MxicUtlis_INPUT_PARAM_ERROR;
		}
	}

	// Configuration start.
	mxic_utlis_process_configuration( priv->mxicUtlis, MxicUtlis_UNIT_3, &IO_MXIC3 );

	if ( regReadSw == MxicUtlis_ON ) {
		IO_MXIC3.TRVSW.bit.TRVSW = MxicUtlis_ON;
	}

	mxic_utlis_off_pclk( priv->mxicUtlis, MxicUtlis_UNIT_3 );

	MxicUtlis_DSB();

	return D_DDIM_OK;
}

/**
This function get output port.<br>
@param[in]		target					Setting target master.<br>
										<ul><li>@ref MxicUtlis_3_W_ELA
											<li>@ref MxicUtlis_3_W_XCH
											<li>@ref MxicUtlis_3_W_FPT_0
											<li>@ref MxicUtlis_3_W_FPT_1
											<li>@ref MxicUtlis_3_R_ELA
											<li>@ref MxicUtlis_3_R_XCH
											<li>@ref MxicUtlis_3_R_FPT_0
											<li>@ref MxicUtlis_3_R_FPT_1
											<li>@ref MxicUtlis_R_FTP_IF</ul>
@param[out]		outPort				Setting of output port.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32	im_mxic_get_output_port( ImMxic *self, UCHAR target, ImMxicPortGr* const outputPort )
{
	UCHAR	writeMaster;
	UCHAR	readMaster;
	UINT32	portSettingWork;
	UINT64	portMask = 1;
	ImMxicPrivate *priv = IM_MXIC_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( outputPort == NULL ) {
		// mon_state parameter is NULL.
		Ddim_Assertion(("E:im_mxic_get_output_port(): outputPort is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	mxic_utlis_wait_command_enable( priv->mxicUtlis, MxicUtlis_UNIT_3, (struct io_jdsmxic *)&IO_MXIC3 );// Wait TCFLG=1.

	mxic_utlis_on_pclk( priv->mxicUtlis, MxicUtlis_UNIT_3 );

	if ( target <= MxicUtlis_READ_MASTER_FLG_MASK ) {
		// Write master.
		if ( target >= ImMxic_OUT_PORT_SEP_NUM ) {

			writeMaster = target - ImMxic_OUT_PORT_SEP_NUM;

			if ( writeMaster >= 32 ) {
				portMask <<= ( writeMaster - 32 );
				portSettingWork = IO_MXIC3.TPORTMW.bit.TPORTMW_127_64_HI;
			}
			else {
				portMask <<= writeMaster;
				portSettingWork = IO_MXIC3.TPORTMW.bit.TPORTMW_127_64_LO;
			}
		} 
		else {
			// target parameter is NULL.
			Ddim_Assertion(("E:im_mxic_get_output_port(): target=%d.\n\n", target));
			return MxicUtlis_INPUT_PARAM_ERROR;
		}
	}
	else {
		// Read master.
		readMaster = ( target & MxicUtlis_READ_MASTER_FLG_MASK );

		if ( readMaster >= ImMxic_OUT_PORT_SEP_NUM ) {

			readMaster -= ImMxic_OUT_PORT_SEP_NUM;

			if ( readMaster >= 32 ) {
				portMask <<= ( readMaster - 32 );
				portSettingWork = IO_MXIC3.TPORTMR.bit.TPORTMR_127_64_HI;
			} 
			else {
				portMask <<= readMaster;
				portSettingWork = IO_MXIC3.TPORTMR.bit.TPORTMR_127_64_LO;
			}
		}
		else {
			// target parameter is NULL.
			Ddim_Assertion(("E:im_mxic_get_output_port(): target=%d.\n\n", target));
			return MxicUtlis_INPUT_PARAM_ERROR;
		}
	}

	mxic_utlis_off_pclk( priv->mxicUtlis, MxicUtlis_UNIT_3 );

	portSettingWork &= portMask;

	if ( portSettingWork == 0 ) {
		*outputPort = MxicUtlis_PORT_GR_0;
	}
	else {
		*outputPort = MxicUtlis_PORT_GR_1;
	}

	return D_DDIM_OK;
}

/**
This function set output port.<br>
@param[in]		outPort					Setting of output port.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32	im_mxic_set_output_port_all( ImMxic *self, const ImMxicOutputPort* const outPort )
{
	UCHAR	regReadSw;
	UINT64	portSettingW127W64 = 0;
	UINT64	portSettingR127R64 = 0;
	ImMxicPrivate *priv = IM_MXIC_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( outPort == NULL ) {
		// mon_state parameter is NULL.
		Ddim_Assertion(("E:im_mxic_set_output_port(): outPort is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	// TPORTMW_127_64.
	portSettingW127W64 |= ImMxic_SHIFT_TPORTMX( outPort->wOutPort.ela,   MxicUtlis_3_W_ELA   );/* pgr0821 */
	portSettingW127W64 |= ImMxic_SHIFT_TPORTMX( outPort->wOutPort.xch,   MxicUtlis_3_W_XCH   );/* pgr0821 */
	portSettingW127W64 |= ImMxic_SHIFT_TPORTMX( outPort->wOutPort.fpt0, MxicUtlis_3_W_FPT_0 );/* pgr0821 */
	portSettingW127W64 |= ImMxic_SHIFT_TPORTMX( outPort->wOutPort.fpt1, MxicUtlis_3_W_FPT_1 );/* pgr0821 */

	// TPORTMR_127_64.
	portSettingR127R64 |= ImMxic_SHIFT_TPORTMX( outPort->rOutPort.ela,   MxicUtlis_3_R_ELA   );/* pgr0821 */
	portSettingR127R64 |= ImMxic_SHIFT_TPORTMX( outPort->rOutPort.xch,   MxicUtlis_3_R_XCH   );/* pgr0821 */
	portSettingR127R64 |= ImMxic_SHIFT_TPORTMX( outPort->rOutPort.fpt0, MxicUtlis_3_R_FPT_0 );/* pgr0821 */
	portSettingR127R64 |= ImMxic_SHIFT_TPORTMX( outPort->rOutPort.fpt1, MxicUtlis_3_R_FPT_1 );/* pgr0821 */

	mxic_utlis_wait_command_enable( priv->mxicUtlis, MxicUtlis_UNIT_3, (struct io_jdsmxic *)&IO_MXIC3 );// Wait TCFLG=1.

	mxic_utlis_on_pclk( priv->mxicUtlis, MxicUtlis_UNIT_3 );

	regReadSw = IO_MXIC3.TRVSW.bit.TRVSW;

	if ( regReadSw == MxicUtlis_ON ) {
		IO_MXIC3.TRVSW.bit.TRVSW = MxicUtlis_OFF;
	}

	IO_MXIC3.TPORTMW.bit.TPORTMW_127_64_LO = (   portSettingW127W64 & ImMxic_MASTER_LO_MASK );
	IO_MXIC3.TPORTMW.bit.TPORTMW_127_64_HI = ( ( portSettingW127W64 & ImMxic_MASTER_HI_MASK ) >> 32 );
	IO_MXIC3.TPORTMR.bit.TPORTMR_127_64_LO = (   portSettingR127R64 & ImMxic_MASTER_LO_MASK );
	IO_MXIC3.TPORTMR.bit.TPORTMR_127_64_HI = ( ( portSettingR127R64 & ImMxic_MASTER_HI_MASK ) >> 32 );

	// Configuration start.
	mxic_utlis_process_configuration( priv->mxicUtlis, MxicUtlis_UNIT_3, &IO_MXIC3 );

	if ( regReadSw == MxicUtlis_ON ) {
		IO_MXIC3.TRVSW.bit.TRVSW = MxicUtlis_ON;
	}

	mxic_utlis_off_pclk( priv->mxicUtlis, MxicUtlis_UNIT_3 );

	MxicUtlis_DSB();

	return D_DDIM_OK;
}

/**
This function get output port.<br>
@param[out]		outPort					Setting of output port.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32	im_mxic_get_output_port_all( ImMxic *self, ImMxicOutputPort *const outPort )
{
	UINT64	portSettingW127W64 = 0;
	UINT64	portSettingR127R64 = 0;
	ImMxicPrivate *priv = IM_MXIC_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( outPort == NULL ) {
		// mon_state parameter is NULL.
		Ddim_Assertion(("E:im_mxic_get_output_port(): outPort is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	mxic_utlis_wait_command_enable( priv->mxicUtlis, MxicUtlis_UNIT_3, (struct io_jdsmxic *)&IO_MXIC3 );// Wait TCFLG=1.

	mxic_utlis_on_pclk( priv->mxicUtlis, MxicUtlis_UNIT_3 );

	portSettingW127W64 = IO_MXIC3.TPORTMW.bit.TPORTMW_127_64_HI;
	portSettingW127W64 = (portSettingW127W64 << 32) | IO_MXIC3.TPORTMW.bit.TPORTMW_127_64_LO;
	portSettingR127R64 = IO_MXIC3.TPORTMR.bit.TPORTMR_127_64_HI;
	portSettingR127R64 = (portSettingR127R64 << 32) | IO_MXIC3.TPORTMR.bit.TPORTMR_127_64_LO;

	mxic_utlis_off_pclk( priv->mxicUtlis, MxicUtlis_UNIT_3 );

	// TPORTMW_127_64.
	outPort->wOutPort.ela	= ImMxic_MASTER_OUT_PORT_TPORTMX( portSettingW127W64, MxicUtlis_3_W_ELA   );
	outPort->wOutPort.xch	= ImMxic_MASTER_OUT_PORT_TPORTMX( portSettingW127W64, MxicUtlis_3_W_XCH   );
	outPort->wOutPort.fpt0	= ImMxic_MASTER_OUT_PORT_TPORTMX( portSettingW127W64, MxicUtlis_3_W_FPT_0 );
	outPort->wOutPort.fpt1	= ImMxic_MASTER_OUT_PORT_TPORTMX( portSettingW127W64, MxicUtlis_3_W_FPT_1 );

	// TPORTMR_127_64.
	outPort->rOutPort.ela	= ImMxic_MASTER_OUT_PORT_TPORTMX( portSettingR127R64, MxicUtlis_3_R_ELA   );
	outPort->rOutPort.xch	= ImMxic_MASTER_OUT_PORT_TPORTMX( portSettingR127R64, MxicUtlis_3_R_XCH   );
	outPort->rOutPort.fpt0	= ImMxic_MASTER_OUT_PORT_TPORTMX( portSettingR127R64, MxicUtlis_3_R_FPT_0 );
	outPort->rOutPort.fpt1	= ImMxic_MASTER_OUT_PORT_TPORTMX( portSettingR127R64, MxicUtlis_3_R_FPT_1 );

	return D_DDIM_OK;
}

/**
Interruption handler of MXIC.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
*/
VOID im_mxic_int_handler( ImMxicUnit unit )
{
	INT32						decErrCh;
	volatile struct io_jdsmxic*	ioMxic = NULL;
	ImMxic* self = k_object_new_with_private(IM_TYPE_MXIC, sizeof(ImMxicPrivate));
	ImMxicPrivate *priv = IM_MXIC_GET_PRIVATE(self);

	(VOID)mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	decErrCh  = 0;

	mxic_utlis_on_pclk( priv->mxicUtlis, unit );

	MxicUtlis_DSB();

	// Check configuration permission flag.
	if ( ( ioMxic->TMIE.bit.TCE == 1 ) && ( ioMxic->TMIF.bit.__TCF == 1 ) ) {
		// Clear TCF interrupt flag.
		ioMxic->TMIF.word &= ImMxic_TMIF_BIT_TCF;
	}

	// Check amount limit flag of transmission.
	if ( ( ioMxic->TMIE.bit.TME == 1 ) && ( ioMxic->TMIF.bit.__TMF == 1 ) ) {
		// Access count or transfer data monitor processing ended by limt judgment.
		mxic_monitor_access_set_trans_mon_limit_end_state(priv->mxicMonitorAccess, MxicUtlis_MONITOR_OPERATION_END);

		// Callback.
		mxic_monitor_access_set_trans_mon_limit_end_callback(priv->mxicMonitorAccess);
		// Clear TMF interrupt flag.
		ioMxic->TMIF.word &= ImMxic_TMIF_BIT_TMF;
	}

	// Check decode error flag.
	if ( ( ioMxic->TMIE.bit.TDEWE == 1 ) && ( ioMxic->TMIF.bit.__TDEWF == 1 ) ) {
		// Write channel decode error.
		// Workaround of do not clear interrupt flag when set TDECLR = 1.
		ioMxic->TMIF.word &= ImMxic_TMIF_BIT_TDEWF;	
		decErrCh |= MxicUtlis_DEC_ERR_CH_W;
	}
	if ( ( ioMxic->TMIE.bit.TDERE == 1 ) && ( ioMxic->TMIF.bit.__TDERF == 1 ) ) {
		// Read channel decode error.
		// Workaround of do not clear interrupt flag when set TDECLR = 1.
		ioMxic->TMIF.word &= ImMxic_TMIF_BIT_TDERF;	
		decErrCh |= MxicUtlis_DEC_ERR_CH_R;
	}
	if ( decErrCh != 0 ) {
		// Callback.
		mxic_master_slave_for_dec_err(priv->mxicMasterSlave, unit, decErrCh);
		// Clear interrupt flag and decode error information.
		// **Note** TDEWF/TDERF interrupt flag is initialized by this processing. ... TDEWF/TDERF is not initialized. why?
		ioMxic->TDECLR.bit.TDECLR = 1;
	}

	// Check detection of memory access of transmission.
	if ( ( ioMxic->TMIE.bit.TSAWE == 1 ) && ( ioMxic->TMIF.bit.__TSAWF == 1 ) ) {
		// Callback.
		if ( priv->gImMxicMemoryAccessDetectCallback[unit] != NULL ) {
			((VOID (*)()) priv->gImMxicMemoryAccessDetectCallback[unit])();
		}
		// Clear TSAWF interrupt flag.
		ioMxic->TMIF.word &= ImMxic_TMIF_BIT_TSAWF;
	}

	mxic_utlis_off_pclk( priv->mxicUtlis, unit );

	MxicUtlis_DSB();

	return;
}

ImMxic *im_mxic_new(void)
{
	ImMxic* self = k_object_new_with_private(IM_TYPE_MXIC, sizeof(ImMxicPrivate));
	return self;
}
