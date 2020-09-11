/***********************************************************************
 * @Copyright(C) 上海网用软件有限公司
 * @file mxicutlis.c
 * @date 2020-09-02
 * @author: 吴海辉
 * @brief: 
 * @version: 1.0.0
***********************************************************************/

#include "mxicutlis.h"


K_TYPE_DEFINE_WITH_PRIVATE(MxicUtlis, mxic_utlis)
#define MXIC_UTLIS_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), MxicUtlisPrivate, MXIC_TYPE_UTLIS))


/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
// Spin_lock.
typedef struct {
	ULONG							lock;
	ULONG							dummy[ ( 64 / 4 ) - 1 ];
} ImMxicSpinLockVar;


struct _MxicUtlisPrivate
{
    int a;
	// TAEN setting user counter.
	volatile INT32 gImMxicTaenCounter[MxicUtlis_UNIT_MAX];
#ifdef MxicUtlis_CO_ACT_MXIC_HCLOCK
	volatile UCHAR imMxic1HclkCounter;
	volatile UCHAR imMxic2HclkCounter;
	volatile UCHAR imMxic3HclkCounter;
#endif
#ifdef MxicUtlis_CO_ACT_MXIC_PCLOCK
	volatile UCHAR imMxic0PclkCounter;
	volatile UCHAR imMxic1PclkCounter;
	volatile UCHAR imMxic2PclkCounter;
	volatile UCHAR imMxic3PclkCounter;
	volatile UCHAR imMxic4PclkCounter;
	volatile UCHAR imMxic5PclkCounter;
	volatile UCHAR imMxic6PclkCounter;
#endif
};


// Spin_lock.
static volatile ImMxicSpinLockVar S_G_IM_MXIC_SPIN_LOCK[MxicUtlis_UNIT_MAX] \
										__attribute__((section(".LOCK_SECTION"), aligned(64)));


/*----------------------------------------------------------------------*/
/* DECLS  															    */
/*----------------------------------------------------------------------*/
#ifdef CO_PARAM_CHECK
static INT32 imMxicCheckUnit( ImMxicUnit unit );
#endif // CO_PARAM_CHECK


/*----------------------------------------------------------------------*/
/* IMPL  															    */
/*----------------------------------------------------------------------*/
static void mxic_utlis_constructor(MxicUtlis *self)
{
    MxicUtlisPrivate *priv = MXIC_UTLIS_GET_PRIVATE(self);

	for (int i = 0; i < MxicUtlis_UNIT_MAX; i++)
	{
		priv->gImMxicTaenCounter[i] = 0;
	}
#ifdef MxicUtlis_CO_ACT_MXIC_HCLOCK
	priv->imMxic1HclkCounter = 0;
	priv->imMxic2HclkCounter = 0;
	priv->imMxic3HclkCounter = 0;
#endif
#ifdef MxicUtlis_CO_ACT_MXIC_PCLOCK
	priv->imMxic0PclkCounter = 0;
	priv->imMxic1PclkCounter = 0;
	priv->imMxic2PclkCounter = 0;
	priv->imMxic3PclkCounter = 0;
	priv->imMxic4PclkCounter = 0;
	priv->imMxic5PclkCounter = 0;
	priv->imMxic6PclkCounter = 0;
#endif
}

static void mxic_utlis_destructor(MxicUtlis *self)
{
    
}

#ifdef CO_PARAM_CHECK
/**
Check unit parameter.
@param[in]		unit								MXIC unit number.<br>
@retval			D_DDIM_OK							Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail	Parameter error.
*/
static INT32 imMxicCheckUnit( ImMxicUnit unit )
{
	INT32 result;

	result = D_DDIM_OK;

	if ( unit >= MxicUtlis_UNIT_MAX ) {
		result = MxicUtlis_INPUT_PARAM_ERROR;
		Ddim_Print(("E:imMxicCheckUnit(): Parameter is illegal. unitt=%d\n", unit));
	}

	return result;
}
#endif // CO_PARAM_CHECK


/*----------------------------------------------------------------------*/
/* PUBLIC  															    */
/*----------------------------------------------------------------------*/
#ifdef CO_PARAM_CHECK
/**
Check port specifies parameter.
@param[in]		wrArbiter				Write or Read Arbiter.<br>
@param[in]		arbiter					Arbiter.<br>
@param[in]		port					Port.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32 mxic_utlis_check_port( MxicUtlis *self, ImMxicWrArbiter wrArbiter, 
							ImMxicSpecArbiter arbiter, ImMxicPort port )
{
	INT32 result;

	result = D_DDIM_OK;

	if ( ( wrArbiter >= MxicUtlis_WR_ARBITER_MAX ) || ( arbiter >= MxicUtlis_SPEC_ARBITER_MAX ) 
		|| ( port >= MxicUtlis_PORT_MAX ) ) {
		result = MxicUtlis_INPUT_PARAM_ERROR;
		Ddim_Print(("E:mxic_utlis_check_port(): Parameter is illegal. wrArbiter=%d, arbiter=%d, port=%d\n", 
					wrArbiter, arbiter, port));
	}

	return result;
}
#endif // CO_PARAM_CHECK

/**
Get unit table address.
@param[in]		unit						MXIC unit number.<br>
@param[out]		ioMxicTbl					MXIC table address.<br>
@retval			D_DDIM_OK						Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR		Fail - Parameter error.
*/
INT32 mxic_utlis_get_unit_tbl_address( MxicUtlis *self, ImMxicUnit unit, 
										volatile struct io_jdsmxic_tbl** ioMxicTbl )
{
	INT32 result;

#ifdef CO_PARAM_CHECK
	if ( imMxicCheckUnit( unit ) != D_DDIM_OK ) {
		// Parameter value is illegal.
		Ddim_Assertion(("E:mxic_utlis_get_unit_tbl_address(): im_mxic_check_unit error.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
	if ( ioMxicTbl == NULL ) {
		// Parameter is NULL.
		Ddim_Assertion(("E:mxic_utlis_get_unit_tbl_address(): ioMxicTbl is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = D_DDIM_OK;

	switch ( unit ) {
		case MxicUtlis_UNIT_1:
			*ioMxicTbl = &IO_MXIC1_TBL;
			break;
		case MxicUtlis_UNIT_2:
			*ioMxicTbl = &IO_MXIC2_TBL;
			break;
		case MxicUtlis_UNIT_3:
			*ioMxicTbl = &IO_MXIC3_TBL;
			break;
		default:
			result = MxicUtlis_INPUT_PARAM_ERROR;
			break;
	}

	return result;
}

/**
Set TAEN register for power saving.
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		ioMxic					MXIC address.<br>
@param[in]		enable					TRUE : Enable  TSL* access.<br>
										FALSE: Disable TSL* access.<br>
*/
VOID mxic_utlis_set_taen( MxicUtlis *self, ImMxicUnit unit, volatile struct io_jdsmxic* ioMxic, BOOL enable )
{
	MxicUtlisPrivate *priv = MXIC_UTLIS_GET_PRIVATE(self);

#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
	Dd_ARM_Critical_Section_Start( S_G_IM_MXIC_SPIN_LOCK[ unit ].lock );
#endif

	mxic_utlis_on_pclk( self, unit );

	if ( enable == TRUE ) {
		// Enable TSL* access.
		priv->gImMxicTaenCounter[unit]++;

		if ( priv->gImMxicTaenCounter[unit] == 1 ) {
			ioMxic->TAEN.bit.TAEN = 1;
			MxicUtlis_DSB();
			Dd_ARM_Wait_ns( 1000 );
		}
	}
	else {
		// Disable TSL* access.
		if ( 0 < priv->gImMxicTaenCounter[unit] ) {
			priv->gImMxicTaenCounter[unit]--;
		}
		if ( priv->gImMxicTaenCounter[unit] == 0 ) {
			ioMxic->TAEN.bit.TAEN = 0;
		}
	}

	mxic_utlis_off_pclk( self, unit );

#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
	Dd_ARM_Critical_Section_End( S_G_IM_MXIC_SPIN_LOCK[ unit ].lock );
#endif
}

/**
Init arbiter assign setting.<br>
@param[in]		unit						Target unit number.<br>
											Please refer to @ref ImMxicUnit for a set value. <br>
@param[out]		allAssign					Arbiter assign.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR		Fail - Parameter error.
*/
INT32 mxic_utlis_init_arbiter_assign( MxicUtlis *self, ImMxicUnit unit, MxicAllArbiterAssign* allAssign )
{
	INT32	i, j, k;
	INT32	result;

	result = D_DDIM_OK;

	// (*Note) Recommendation setup is performed here!.
	for ( i = MxicUtlis_W_ARBITER_W1; i < MxicUtlis_W_ARBITER_MAX; i++ ) {

		for ( j = MxicUtlis_PORT_0; j < MxicUtlis_PORT_MAX; j++ ) {

			for ( k = 0; k < MxicUtlis_SLOT_SIZE_8; k++ ) {

				allAssign->wArbiter[ i ].port[ j ].slot0[ k ] = MxicUtlis_W_RESERVE;
				allAssign->wArbiter[ i ].port[ j ].slot1[ k ] = MxicUtlis_W_RESERVE;
				allAssign->wArbiter[ i ].port[ j ].slot2[ k ] = MxicUtlis_W_RESERVE;
				allAssign->wArbiter[ i ].port[ j ].slot3[ k ] = MxicUtlis_W_RESERVE;
			}
		}
	}

	for ( i = MxicUtlis_R_ARBITER_R1; i < MxicUtlis_R_ARBITER_MAX; i++ ) {

		for ( j = MxicUtlis_PORT_0; j < MxicUtlis_PORT_MAX; j++ ) {

			for ( k = 0; k < MxicUtlis_SLOT_SIZE_8; k++ ) {

				allAssign->rArbiter[ i ].port[ j ].slot0[ k ] = MxicUtlis_R_RESERVE;
				allAssign->rArbiter[ i ].port[ j ].slot1[ k ] = MxicUtlis_R_RESERVE;
				allAssign->rArbiter[ i ].port[ j ].slot2[ k ] = MxicUtlis_R_RESERVE;
				allAssign->rArbiter[ i ].port[ j ].slot3[ k ] = MxicUtlis_R_RESERVE;
			}
		}
	}

	switch ( unit ) {
		case MxicUtlis_UNIT_0:
			// Non-implementation.
			break;
		case MxicUtlis_UNIT_1:
			// TSLW_1, PORT0, SLOT0/1/2.
			allAssign->wArbiter[ 0 ].port[ 0 ].slot0[ 0 ] = MxicUtlis_1_W_SRO;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot0[ 1 ] = MxicUtlis_1_W_B2B;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot0[ 2 ] = MxicUtlis_1_W_LTMDT;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot0[ 3 ] = MxicUtlis_1_W_CNR_A;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot0[ 4 ] = MxicUtlis_1_W_CNR_B;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot1[ 0 ] = MxicUtlis_1_W_SRO;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot1[ 1 ] = MxicUtlis_1_W_B2B;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot1[ 2 ] = MxicUtlis_1_W_LTMDT;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot1[ 3 ] = MxicUtlis_1_W_CNR_A;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot1[ 4 ] = MxicUtlis_1_W_CNR_B;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot2[ 0 ] = MxicUtlis_1_W_SRO;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot2[ 1 ] = MxicUtlis_1_W_B2B;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot2[ 2 ] = MxicUtlis_1_W_LTMDT;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot2[ 3 ] = MxicUtlis_1_W_CNR_A;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot2[ 4 ] = MxicUtlis_1_W_CNR_B;

			// TSLW_1, PORT1, SLOT0/1/2.
			allAssign->wArbiter[ 0 ].port[ 1 ].slot0[ 0 ] = MxicUtlis_1_W_R2Y_A;
			allAssign->wArbiter[ 0 ].port[ 1 ].slot0[ 1 ] = MxicUtlis_1_W_R2Y_B;
			allAssign->wArbiter[ 0 ].port[ 1 ].slot0[ 2 ] = MxicUtlis_1_W_R2Y_C;
			allAssign->wArbiter[ 0 ].port[ 1 ].slot0[ 3 ] = MxicUtlis_1_W_R2Y_D;
			allAssign->wArbiter[ 0 ].port[ 1 ].slot1[ 0 ] = MxicUtlis_1_W_R2Y_A;
			allAssign->wArbiter[ 0 ].port[ 1 ].slot1[ 1 ] = MxicUtlis_1_W_R2Y_B;
			allAssign->wArbiter[ 0 ].port[ 1 ].slot1[ 2 ] = MxicUtlis_1_W_R2Y_C;
			allAssign->wArbiter[ 0 ].port[ 1 ].slot1[ 3 ] = MxicUtlis_1_W_R2Y_D;
			allAssign->wArbiter[ 0 ].port[ 1 ].slot2[ 0 ] = MxicUtlis_1_W_R2Y_A;
			allAssign->wArbiter[ 0 ].port[ 1 ].slot2[ 1 ] = MxicUtlis_1_W_R2Y_B;
			allAssign->wArbiter[ 0 ].port[ 1 ].slot2[ 2 ] = MxicUtlis_1_W_R2Y_C;
			allAssign->wArbiter[ 0 ].port[ 1 ].slot2[ 3 ] = MxicUtlis_1_W_R2Y_D;

			// TSLW_2, PORT0, SLOT0/1/2.
			allAssign->wArbiter[ 1 ].port[ 0 ].slot0[ 0 ] = MxicUtlis_1_W_SRO;
			allAssign->wArbiter[ 1 ].port[ 0 ].slot0[ 1 ] = MxicUtlis_1_W_B2B;
			allAssign->wArbiter[ 1 ].port[ 0 ].slot0[ 2 ] = MxicUtlis_1_W_LTMDT;
			allAssign->wArbiter[ 1 ].port[ 0 ].slot0[ 3 ] = MxicUtlis_1_W_CNR_A;
			allAssign->wArbiter[ 1 ].port[ 0 ].slot1[ 0 ] = MxicUtlis_1_W_SRO;
			allAssign->wArbiter[ 1 ].port[ 0 ].slot1[ 1 ] = MxicUtlis_1_W_B2B;
			allAssign->wArbiter[ 1 ].port[ 0 ].slot1[ 2 ] = MxicUtlis_1_W_LTMDT;
			allAssign->wArbiter[ 1 ].port[ 0 ].slot1[ 3 ] = MxicUtlis_1_W_CNR_A;
			allAssign->wArbiter[ 1 ].port[ 0 ].slot2[ 0 ] = MxicUtlis_1_W_SRO;
			allAssign->wArbiter[ 1 ].port[ 0 ].slot2[ 1 ] = MxicUtlis_1_W_B2B;
			allAssign->wArbiter[ 1 ].port[ 0 ].slot2[ 2 ] = MxicUtlis_1_W_LTMDT;
			allAssign->wArbiter[ 1 ].port[ 0 ].slot2[ 3 ] = MxicUtlis_1_W_CNR_A;

			// TSLW_2, PORT1, SLOT0/1/2.
			allAssign->wArbiter[ 1 ].port[ 1 ].slot0[ 0 ] = MxicUtlis_1_W_R2Y_A;
			allAssign->wArbiter[ 1 ].port[ 1 ].slot0[ 1 ] = MxicUtlis_1_W_R2Y_B;
			allAssign->wArbiter[ 1 ].port[ 1 ].slot0[ 2 ] = MxicUtlis_1_W_R2Y_C;
			allAssign->wArbiter[ 1 ].port[ 1 ].slot0[ 3 ] = MxicUtlis_1_W_R2Y_D;
			allAssign->wArbiter[ 1 ].port[ 1 ].slot1[ 0 ] = MxicUtlis_1_W_R2Y_A;
			allAssign->wArbiter[ 1 ].port[ 1 ].slot1[ 1 ] = MxicUtlis_1_W_R2Y_B;
			allAssign->wArbiter[ 1 ].port[ 1 ].slot1[ 2 ] = MxicUtlis_1_W_R2Y_C;
			allAssign->wArbiter[ 1 ].port[ 1 ].slot1[ 3 ] = MxicUtlis_1_W_R2Y_D;
			allAssign->wArbiter[ 1 ].port[ 1 ].slot2[ 0 ] = MxicUtlis_1_W_R2Y_A;
			allAssign->wArbiter[ 1 ].port[ 1 ].slot2[ 1 ] = MxicUtlis_1_W_R2Y_B;
			allAssign->wArbiter[ 1 ].port[ 1 ].slot2[ 2 ] = MxicUtlis_1_W_R2Y_C;
			allAssign->wArbiter[ 1 ].port[ 1 ].slot2[ 3 ] = MxicUtlis_1_W_R2Y_D;

			// TSLR_1, Port0, SLOT0/1/2.
			allAssign->rArbiter[ 0 ].port[ 0 ].slot0[ 0 ] = MxicUtlis_1_R_SRO;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot0[ 1 ] = MxicUtlis_1_R_B2B;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot0[ 2 ] = MxicUtlis_1_R_LTMDT;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot0[ 3 ] = MxicUtlis_1_R_R2Y_A;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot0[ 4 ] = MxicUtlis_1_R_R2Y_B;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot0[ 5 ] = MxicUtlis_1_R_R2Y_C;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot1[ 0 ] = MxicUtlis_1_R_SRO;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot1[ 1 ] = MxicUtlis_1_R_B2B;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot1[ 2 ] = MxicUtlis_1_R_LTMDT;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot1[ 3 ] = MxicUtlis_1_R_R2Y_A;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot1[ 4 ] = MxicUtlis_1_R_R2Y_B;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot1[ 5 ] = MxicUtlis_1_R_R2Y_C;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot2[ 0 ] = MxicUtlis_1_R_SRO;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot2[ 1 ] = MxicUtlis_1_R_B2B;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot2[ 2 ] = MxicUtlis_1_R_LTMDT;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot2[ 3 ] = MxicUtlis_1_R_R2Y_A;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot2[ 4 ] = MxicUtlis_1_R_R2Y_B;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot2[ 5 ] = MxicUtlis_1_R_R2Y_C;

			// TSLR_1, Port1, SLOT0/1/2.
			allAssign->rArbiter[ 0 ].port[ 1 ].slot0[ 1 ] = MxicUtlis_1_R_CNR_B;
			allAssign->rArbiter[ 0 ].port[ 1 ].slot1[ 1 ] = MxicUtlis_1_R_CNR_B;
			allAssign->rArbiter[ 0 ].port[ 1 ].slot2[ 1 ] = MxicUtlis_1_R_CNR_B;

			// TSLR_2, Port0, SLOT0/1/2.
			allAssign->rArbiter[ 1 ].port[ 0 ].slot0[ 0 ] = MxicUtlis_1_R_SRO;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot0[ 1 ] = MxicUtlis_1_R_B2B;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot0[ 2 ] = MxicUtlis_1_R_LTMDT;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot0[ 3 ] = MxicUtlis_1_R_R2Y_A;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot0[ 4 ] = MxicUtlis_1_R_R2Y_B;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot0[ 5 ] = MxicUtlis_1_R_R2Y_C;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot1[ 0 ] = MxicUtlis_1_R_SRO;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot1[ 1 ] = MxicUtlis_1_R_B2B;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot1[ 2 ] = MxicUtlis_1_R_LTMDT;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot1[ 3 ] = MxicUtlis_1_R_R2Y_A;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot1[ 4 ] = MxicUtlis_1_R_R2Y_B;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot1[ 5 ] = MxicUtlis_1_R_R2Y_C;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot2[ 0 ] = MxicUtlis_1_R_SRO;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot2[ 1 ] = MxicUtlis_1_R_B2B;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot2[ 2 ] = MxicUtlis_1_R_LTMDT;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot2[ 3 ] = MxicUtlis_1_R_R2Y_A;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot2[ 4 ] = MxicUtlis_1_R_R2Y_B;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot2[ 5 ] = MxicUtlis_1_R_R2Y_C;

			// TSLR_2, Port1, SLOT0/1/2.
			allAssign->rArbiter[ 1 ].port[ 1 ].slot0[ 1 ] = MxicUtlis_1_R_CNR_B;
			allAssign->rArbiter[ 1 ].port[ 1 ].slot1[ 1 ] = MxicUtlis_1_R_CNR_B;
			allAssign->rArbiter[ 1 ].port[ 1 ].slot2[ 1 ] = MxicUtlis_1_R_CNR_B;
			break;
		case MxicUtlis_UNIT_2:
			// TSLW_1, PORT0, SLOT0/1/2.
			allAssign->wArbiter[ 0 ].port[ 0 ].slot0[ 0 ] = MxicUtlis_2_W_SRO;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot0[ 1 ] = MxicUtlis_2_W_B2B;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot0[ 2 ] = MxicUtlis_2_W_LTMDT;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot0[ 3 ] = MxicUtlis_2_W_CNR_A;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot0[ 4 ] = MxicUtlis_2_W_CNR_B;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot1[ 0 ] = MxicUtlis_2_W_SRO;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot1[ 1 ] = MxicUtlis_2_W_B2B;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot1[ 2 ] = MxicUtlis_2_W_LTMDT;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot1[ 3 ] = MxicUtlis_2_W_CNR_A;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot1[ 4 ] = MxicUtlis_2_W_CNR_B;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot2[ 0 ] = MxicUtlis_2_W_SRO;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot2[ 1 ] = MxicUtlis_2_W_B2B;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot2[ 2 ] = MxicUtlis_2_W_LTMDT;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot2[ 3 ] = MxicUtlis_2_W_CNR_A;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot2[ 4 ] = MxicUtlis_2_W_CNR_B;

			// TSLW_1, PORT1, SLOT0/1/2.
			allAssign->wArbiter[ 0 ].port[ 1 ].slot0[ 0 ] = MxicUtlis_2_W_R2Y_A;
			allAssign->wArbiter[ 0 ].port[ 1 ].slot0[ 1 ] = MxicUtlis_2_W_R2Y_B;
			allAssign->wArbiter[ 0 ].port[ 1 ].slot0[ 2 ] = MxicUtlis_2_W_R2Y_C;
			allAssign->wArbiter[ 0 ].port[ 1 ].slot0[ 3 ] = MxicUtlis_2_W_R2Y_D;
			allAssign->wArbiter[ 0 ].port[ 1 ].slot1[ 0 ] = MxicUtlis_2_W_R2Y_A;
			allAssign->wArbiter[ 0 ].port[ 1 ].slot1[ 1 ] = MxicUtlis_2_W_R2Y_B;
			allAssign->wArbiter[ 0 ].port[ 1 ].slot1[ 2 ] = MxicUtlis_2_W_R2Y_C;
			allAssign->wArbiter[ 0 ].port[ 1 ].slot1[ 3 ] = MxicUtlis_2_W_R2Y_D;
			allAssign->wArbiter[ 0 ].port[ 1 ].slot2[ 0 ] = MxicUtlis_2_W_R2Y_A;
			allAssign->wArbiter[ 0 ].port[ 1 ].slot2[ 1 ] = MxicUtlis_2_W_R2Y_B;
			allAssign->wArbiter[ 0 ].port[ 1 ].slot2[ 2 ] = MxicUtlis_2_W_R2Y_C;
			allAssign->wArbiter[ 0 ].port[ 1 ].slot2[ 3 ] = MxicUtlis_2_W_R2Y_D;

			// TSLW_2, PORT0, SLOT0/1/2.
			allAssign->wArbiter[ 1 ].port[ 0 ].slot0[ 0 ] = MxicUtlis_2_W_SRO;
			allAssign->wArbiter[ 1 ].port[ 0 ].slot0[ 1 ] = MxicUtlis_2_W_B2B;
			allAssign->wArbiter[ 1 ].port[ 0 ].slot0[ 2 ] = MxicUtlis_2_W_LTMDT;
			allAssign->wArbiter[ 1 ].port[ 0 ].slot0[ 3 ] = MxicUtlis_2_W_CNR_B;
			allAssign->wArbiter[ 1 ].port[ 0 ].slot1[ 0 ] = MxicUtlis_2_W_SRO;
			allAssign->wArbiter[ 1 ].port[ 0 ].slot1[ 1 ] = MxicUtlis_2_W_B2B;
			allAssign->wArbiter[ 1 ].port[ 0 ].slot1[ 2 ] = MxicUtlis_2_W_LTMDT;
			allAssign->wArbiter[ 1 ].port[ 0 ].slot1[ 3 ] = MxicUtlis_2_W_CNR_B;
			allAssign->wArbiter[ 1 ].port[ 0 ].slot2[ 0 ] = MxicUtlis_2_W_SRO;
			allAssign->wArbiter[ 1 ].port[ 0 ].slot2[ 1 ] = MxicUtlis_2_W_B2B;
			allAssign->wArbiter[ 1 ].port[ 0 ].slot2[ 2 ] = MxicUtlis_2_W_LTMDT;
			allAssign->wArbiter[ 1 ].port[ 0 ].slot2[ 3 ] = MxicUtlis_2_W_CNR_B;

			// TSLW_2, PORT1, SLOT0/1/2.
			allAssign->wArbiter[ 1 ].port[ 1 ].slot0[ 0 ] = MxicUtlis_2_W_R2Y_A;
			allAssign->wArbiter[ 1 ].port[ 1 ].slot0[ 1 ] = MxicUtlis_2_W_R2Y_B;
			allAssign->wArbiter[ 1 ].port[ 1 ].slot0[ 2 ] = MxicUtlis_2_W_R2Y_C;
			allAssign->wArbiter[ 1 ].port[ 1 ].slot0[ 3 ] = MxicUtlis_2_W_R2Y_D;
			allAssign->wArbiter[ 1 ].port[ 1 ].slot1[ 0 ] = MxicUtlis_2_W_R2Y_A;
			allAssign->wArbiter[ 1 ].port[ 1 ].slot1[ 1 ] = MxicUtlis_2_W_R2Y_B;
			allAssign->wArbiter[ 1 ].port[ 1 ].slot1[ 2 ] = MxicUtlis_2_W_R2Y_C;
			allAssign->wArbiter[ 1 ].port[ 1 ].slot1[ 3 ] = MxicUtlis_2_W_R2Y_D;
			allAssign->wArbiter[ 1 ].port[ 1 ].slot2[ 0 ] = MxicUtlis_2_W_R2Y_A;
			allAssign->wArbiter[ 1 ].port[ 1 ].slot2[ 1 ] = MxicUtlis_2_W_R2Y_B;
			allAssign->wArbiter[ 1 ].port[ 1 ].slot2[ 2 ] = MxicUtlis_2_W_R2Y_C;
			allAssign->wArbiter[ 1 ].port[ 1 ].slot2[ 3 ] = MxicUtlis_2_W_R2Y_D;

			// TSLR_1, PORT0, SLOT0/1/2/.
			allAssign->rArbiter[ 0 ].port[ 0 ].slot0[ 0 ] = MxicUtlis_2_R_SRO;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot0[ 1 ] = MxicUtlis_2_R_B2B;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot0[ 2 ] = MxicUtlis_2_R_LTMDT;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot0[ 3 ] = MxicUtlis_2_R_R2Y_A;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot0[ 4 ] = MxicUtlis_2_R_R2Y_B;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot0[ 5 ] = MxicUtlis_2_R_R2Y_C;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot1[ 0 ] = MxicUtlis_2_R_SRO;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot1[ 1 ] = MxicUtlis_2_R_B2B;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot1[ 2 ] = MxicUtlis_2_R_LTMDT;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot1[ 3 ] = MxicUtlis_2_R_R2Y_A;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot1[ 4 ] = MxicUtlis_2_R_R2Y_B;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot1[ 5 ] = MxicUtlis_2_R_R2Y_C;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot2[ 0 ] = MxicUtlis_2_R_SRO;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot2[ 1 ] = MxicUtlis_2_R_B2B;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot2[ 2 ] = MxicUtlis_2_R_LTMDT;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot2[ 3 ] = MxicUtlis_2_R_R2Y_A;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot2[ 4 ] = MxicUtlis_2_R_R2Y_B;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot2[ 5 ] = MxicUtlis_2_R_R2Y_C;

			// TSLR_1, PORT1, SLOT0/1/2.
			allAssign->rArbiter[ 0 ].port[ 1 ].slot0[ 1 ] = MxicUtlis_2_R_CNR_B;
			allAssign->rArbiter[ 0 ].port[ 1 ].slot1[ 1 ] = MxicUtlis_2_R_CNR_B;
			allAssign->rArbiter[ 0 ].port[ 1 ].slot2[ 1 ] = MxicUtlis_2_R_CNR_B;

			// TSLR_2, PORT0, SLOT0/1/2.
			allAssign->rArbiter[ 1 ].port[ 0 ].slot0[ 0 ] = MxicUtlis_2_R_SRO;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot0[ 1 ] = MxicUtlis_2_R_B2B;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot0[ 2 ] = MxicUtlis_2_R_LTMDT;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot0[ 3 ] = MxicUtlis_2_R_R2Y_A;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot0[ 4 ] = MxicUtlis_2_R_R2Y_B;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot0[ 5 ] = MxicUtlis_2_R_R2Y_C;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot1[ 0 ] = MxicUtlis_2_R_SRO;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot1[ 1 ] = MxicUtlis_2_R_B2B;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot1[ 2 ] = MxicUtlis_2_R_LTMDT;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot1[ 3 ] = MxicUtlis_2_R_R2Y_A;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot1[ 4 ] = MxicUtlis_2_R_R2Y_B;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot1[ 5 ] = MxicUtlis_2_R_R2Y_C;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot2[ 0 ] = MxicUtlis_2_R_SRO;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot2[ 1 ] = MxicUtlis_2_R_B2B;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot2[ 2 ] = MxicUtlis_2_R_LTMDT;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot2[ 3 ] = MxicUtlis_2_R_R2Y_A;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot2[ 4 ] = MxicUtlis_2_R_R2Y_B;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot2[ 5 ] = MxicUtlis_2_R_R2Y_C;

			// TSLR_2, PORT1, SLOT0/1/2.
			allAssign->rArbiter[ 1 ].port[ 1 ].slot0[ 1 ] = MxicUtlis_2_R_CNR_B;
			allAssign->rArbiter[ 1 ].port[ 1 ].slot1[ 1 ] = MxicUtlis_2_R_CNR_B;
			allAssign->rArbiter[ 1 ].port[ 1 ].slot2[ 1 ] = MxicUtlis_2_R_CNR_B;
			break;
		case MxicUtlis_UNIT_3:
			// TSLW_1, PORT0, SLOT0/1/2.
			allAssign->wArbiter[ 0 ].port[ 0 ].slot0[ 0 ] = MxicUtlis_3_W_IPU_A;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot0[ 1 ] = MxicUtlis_3_W_IPU_C;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot0[ 2 ] = MxicUtlis_3_W_IPU_D;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot0[ 3 ] = MxicUtlis_3_W_IPU_E;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot1[ 0 ] = MxicUtlis_3_W_IPU_A;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot1[ 1 ] = MxicUtlis_3_W_IPU_C;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot1[ 2 ] = MxicUtlis_3_W_IPU_D;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot1[ 3 ] = MxicUtlis_3_W_IPU_E;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot2[ 0 ] = MxicUtlis_3_W_IPU_A;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot2[ 1 ] = MxicUtlis_3_W_IPU_C;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot2[ 2 ] = MxicUtlis_3_W_IPU_D;
			allAssign->wArbiter[ 0 ].port[ 0 ].slot2[ 3 ] = MxicUtlis_3_W_IPU_E;

			// TSLW_1, PORT1, SLOT0/1/2.
			allAssign->wArbiter[ 0 ].port[ 1 ].slot0[ 0 ] = MxicUtlis_3_W_SHDR_A;
			allAssign->wArbiter[ 0 ].port[ 1 ].slot0[ 1 ] = MxicUtlis_3_W_SHDR_B;
			allAssign->wArbiter[ 0 ].port[ 1 ].slot0[ 2 ] = MxicUtlis_3_W_SHDR_C;
			allAssign->wArbiter[ 0 ].port[ 1 ].slot1[ 0 ] = MxicUtlis_3_W_SHDR_A;
			allAssign->wArbiter[ 0 ].port[ 1 ].slot1[ 1 ] = MxicUtlis_3_W_SHDR_B;
			allAssign->wArbiter[ 0 ].port[ 1 ].slot1[ 2 ] = MxicUtlis_3_W_SHDR_C;
			allAssign->wArbiter[ 0 ].port[ 1 ].slot2[ 0 ] = MxicUtlis_3_W_SHDR_A;
			allAssign->wArbiter[ 0 ].port[ 1 ].slot2[ 1 ] = MxicUtlis_3_W_SHDR_B;
			allAssign->wArbiter[ 0 ].port[ 1 ].slot2[ 2 ] = MxicUtlis_3_W_SHDR_C;

			// TSLW_1, PORT2, SLOT0/1/2.
			allAssign->wArbiter[ 0 ].port[ 2 ].slot0[ 0 ] = MxicUtlis_3_W_ME;
			allAssign->wArbiter[ 0 ].port[ 2 ].slot0[ 1 ] = MxicUtlis_3_W_GPU;
			allAssign->wArbiter[ 0 ].port[ 2 ].slot1[ 0 ] = MxicUtlis_3_W_ME;
			allAssign->wArbiter[ 0 ].port[ 2 ].slot1[ 1 ] = MxicUtlis_3_W_GPU;
			allAssign->wArbiter[ 0 ].port[ 2 ].slot2[ 0 ] = MxicUtlis_3_W_ME;
			allAssign->wArbiter[ 0 ].port[ 2 ].slot2[ 1 ] = MxicUtlis_3_W_GPU;

			// TSLW_2, PORT0, SLOT0/1/2.
			allAssign->wArbiter[ 1 ].port[ 0 ].slot0[ 0 ] = MxicUtlis_3_W_SHDR_A;
			allAssign->wArbiter[ 1 ].port[ 0 ].slot0[ 1 ] = MxicUtlis_3_W_SHDR_B;
			allAssign->wArbiter[ 1 ].port[ 0 ].slot0[ 2 ] = MxicUtlis_3_W_SHDR_C;
			allAssign->wArbiter[ 1 ].port[ 0 ].slot1[ 0 ] = MxicUtlis_3_W_SHDR_A;
			allAssign->wArbiter[ 1 ].port[ 0 ].slot1[ 1 ] = MxicUtlis_3_W_SHDR_B;
			allAssign->wArbiter[ 1 ].port[ 0 ].slot1[ 2 ] = MxicUtlis_3_W_SHDR_C;
			allAssign->wArbiter[ 1 ].port[ 0 ].slot2[ 0 ] = MxicUtlis_3_W_SHDR_A;
			allAssign->wArbiter[ 1 ].port[ 0 ].slot2[ 1 ] = MxicUtlis_3_W_SHDR_B;
			allAssign->wArbiter[ 1 ].port[ 0 ].slot2[ 2 ] = MxicUtlis_3_W_SHDR_C;

			// TSLW_2, PORT1, SLOT0/1/2.
			allAssign->wArbiter[ 1 ].port[ 1 ].slot0[ 0 ] = MxicUtlis_3_W_IPU_A;
			allAssign->wArbiter[ 1 ].port[ 1 ].slot0[ 1 ] = MxicUtlis_3_W_IPU_C;
			allAssign->wArbiter[ 1 ].port[ 1 ].slot0[ 2 ] = MxicUtlis_3_W_IPU_D;
			allAssign->wArbiter[ 1 ].port[ 1 ].slot0[ 3 ] = MxicUtlis_3_W_IPU_E;
			allAssign->wArbiter[ 1 ].port[ 1 ].slot1[ 0 ] = MxicUtlis_3_W_IPU_A;
			allAssign->wArbiter[ 1 ].port[ 1 ].slot1[ 1 ] = MxicUtlis_3_W_IPU_C;
			allAssign->wArbiter[ 1 ].port[ 1 ].slot1[ 2 ] = MxicUtlis_3_W_IPU_D;
			allAssign->wArbiter[ 1 ].port[ 1 ].slot1[ 3 ] = MxicUtlis_3_W_IPU_E;
			allAssign->wArbiter[ 1 ].port[ 1 ].slot2[ 0 ] = MxicUtlis_3_W_IPU_A;
			allAssign->wArbiter[ 1 ].port[ 1 ].slot2[ 1 ] = MxicUtlis_3_W_IPU_C;
			allAssign->wArbiter[ 1 ].port[ 1 ].slot2[ 2 ] = MxicUtlis_3_W_IPU_D;
			allAssign->wArbiter[ 1 ].port[ 1 ].slot2[ 3 ] = MxicUtlis_3_W_IPU_E;

			// TSLR_1, PORT0, SLOT0/1/2.
			allAssign->rArbiter[ 0 ].port[ 0 ].slot0[ 0 ] = MxicUtlis_3_R_IPU_A;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot0[ 1 ] = MxicUtlis_3_R_IPU_B;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot0[ 2 ] = MxicUtlis_3_R_IPU_C;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot0[ 3 ] = MxicUtlis_3_R_IPU_D;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot1[ 0 ] = MxicUtlis_3_R_IPU_A;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot1[ 1 ] = MxicUtlis_3_R_IPU_B;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot1[ 2 ] = MxicUtlis_3_R_IPU_C;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot1[ 3 ] = MxicUtlis_3_R_IPU_D;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot2[ 0 ] = MxicUtlis_3_R_IPU_A;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot2[ 1 ] = MxicUtlis_3_R_IPU_B;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot2[ 2 ] = MxicUtlis_3_R_IPU_C;
			allAssign->rArbiter[ 0 ].port[ 0 ].slot2[ 3 ] = MxicUtlis_3_R_IPU_D;

			// TSLR_1, PORT1, SLOT0/1/2.
			allAssign->rArbiter[ 0 ].port[ 1 ].slot0[ 0 ] = MxicUtlis_3_R_SHDR_A;
			allAssign->rArbiter[ 0 ].port[ 1 ].slot0[ 1 ] = MxicUtlis_3_R_SHDR_B;
			allAssign->rArbiter[ 0 ].port[ 1 ].slot0[ 2 ] = MxicUtlis_3_R_SHDR_C;
			allAssign->rArbiter[ 0 ].port[ 1 ].slot0[ 3 ] = MxicUtlis_3_R_SHDR_D;
			allAssign->rArbiter[ 0 ].port[ 1 ].slot1[ 0 ] = MxicUtlis_3_R_SHDR_A;
			allAssign->rArbiter[ 0 ].port[ 1 ].slot1[ 1 ] = MxicUtlis_3_R_SHDR_B;
			allAssign->rArbiter[ 0 ].port[ 1 ].slot1[ 2 ] = MxicUtlis_3_R_SHDR_C;
			allAssign->rArbiter[ 0 ].port[ 1 ].slot1[ 3 ] = MxicUtlis_3_R_SHDR_D;
			allAssign->rArbiter[ 0 ].port[ 1 ].slot2[ 0 ] = MxicUtlis_3_R_SHDR_A;
			allAssign->rArbiter[ 0 ].port[ 1 ].slot2[ 1 ] = MxicUtlis_3_R_SHDR_B;
			allAssign->rArbiter[ 0 ].port[ 1 ].slot2[ 2 ] = MxicUtlis_3_R_SHDR_C;
			allAssign->rArbiter[ 0 ].port[ 1 ].slot2[ 3 ] = MxicUtlis_3_R_SHDR_D;

			// TSLR_1, PORT2, SLOT0/1/2.
			allAssign->rArbiter[ 0 ].port[ 2 ].slot0[ 0 ] = MxicUtlis_3_R_ME;
			allAssign->rArbiter[ 0 ].port[ 2 ].slot0[ 1 ] = MxicUtlis_3_R_GPU;
			allAssign->rArbiter[ 0 ].port[ 2 ].slot1[ 0 ] = MxicUtlis_3_R_ME;
			allAssign->rArbiter[ 0 ].port[ 2 ].slot1[ 1 ] = MxicUtlis_3_R_GPU;
			allAssign->rArbiter[ 0 ].port[ 2 ].slot2[ 0 ] = MxicUtlis_3_R_ME;
			allAssign->rArbiter[ 0 ].port[ 2 ].slot2[ 1 ] = MxicUtlis_3_R_GPU;

			// TSLR_2, PORT0, SLOT0/1/2.
			allAssign->rArbiter[ 1 ].port[ 0 ].slot0[ 0 ] = MxicUtlis_3_R_SHDR_A;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot0[ 1 ] = MxicUtlis_3_R_SHDR_B;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot0[ 2 ] = MxicUtlis_3_R_SHDR_C;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot0[ 3 ] = MxicUtlis_3_R_SHDR_D;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot1[ 0 ] = MxicUtlis_3_R_SHDR_A;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot1[ 1 ] = MxicUtlis_3_R_SHDR_B;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot1[ 2 ] = MxicUtlis_3_R_SHDR_C;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot1[ 3 ] = MxicUtlis_3_R_SHDR_D;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot2[ 0 ] = MxicUtlis_3_R_SHDR_A;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot2[ 1 ] = MxicUtlis_3_R_SHDR_B;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot2[ 2 ] = MxicUtlis_3_R_SHDR_C;
			allAssign->rArbiter[ 1 ].port[ 0 ].slot2[ 3 ] = MxicUtlis_3_R_SHDR_D;

			// TSLR_2, PORT1, SLOT0/1/2.
			allAssign->rArbiter[ 1 ].port[ 1 ].slot0[ 0 ] = MxicUtlis_3_R_IPU_A;
			allAssign->rArbiter[ 1 ].port[ 1 ].slot0[ 1 ] = MxicUtlis_3_R_IPU_B;
			allAssign->rArbiter[ 1 ].port[ 1 ].slot0[ 2 ] = MxicUtlis_3_R_IPU_C;
			allAssign->rArbiter[ 1 ].port[ 1 ].slot0[ 3 ] = MxicUtlis_3_R_IPU_D;
			allAssign->rArbiter[ 1 ].port[ 1 ].slot1[ 0 ] = MxicUtlis_3_R_IPU_A;
			allAssign->rArbiter[ 1 ].port[ 1 ].slot1[ 1 ] = MxicUtlis_3_R_IPU_B;
			allAssign->rArbiter[ 1 ].port[ 1 ].slot1[ 2 ] = MxicUtlis_3_R_IPU_C;
			allAssign->rArbiter[ 1 ].port[ 1 ].slot1[ 3 ] = MxicUtlis_3_R_IPU_D;
			allAssign->rArbiter[ 1 ].port[ 1 ].slot2[ 0 ] = MxicUtlis_3_R_IPU_A;
			allAssign->rArbiter[ 1 ].port[ 1 ].slot2[ 1 ] = MxicUtlis_3_R_IPU_B;
			allAssign->rArbiter[ 1 ].port[ 1 ].slot2[ 2 ] = MxicUtlis_3_R_IPU_C;
			allAssign->rArbiter[ 1 ].port[ 1 ].slot2[ 3 ] = MxicUtlis_3_R_IPU_D;
			break;
		case MxicUtlis_UNIT_4:
		case MxicUtlis_UNIT_5:
		case MxicUtlis_UNIT_6:
			// Non-implementation.
			break;
		default :
			result = MxicUtlis_INPUT_PARAM_ERROR;
			Ddim_Print(("E:mxic_utlis_init_arbiter_assign(): unit number(%d) is illegal.\n", unit));
			break;
	}

	return result;
}

/* MXIC PCLK change to ON.
 */
VOID mxic_utlis_on_pclk( MxicUtlis *self, ImMxicUnit unit )
{
#ifdef MxicUtlis_CO_ACT_MXIC_PCLOCK
	MxicUtlisPrivate *priv = MXIC_UTLIS_GET_PRIVATE(self);

	switch ( unit ) {
		case MxicUtlis_UNIT_0:
			Dd_Top_Start_Clock( (UCHAR*)&priv->imMxic0PclkCounter, &Dd_Top_Get_CLKSTOP5(), ~D_DD_TOP_MICAP0_BIT );
			break;
		case MxicUtlis_UNIT_1:
			Dd_Top_Start_Clock( (UCHAR*)&priv->imMxic1PclkCounter, &Dd_Top_Get_CLKSTOP5(), ~D_DD_TOP_MICAP1_BIT );
			break;
		case MxicUtlis_UNIT_2:
			Dd_Top_Start_Clock( (UCHAR*)&priv->imMxic2PclkCounter, &Dd_Top_Get_CLKSTOP5(), ~D_DD_TOP_MICAP2_BIT );
			break;
		case MxicUtlis_UNIT_3:
			Dd_Top_Start_Clock( (UCHAR*)&priv->imMxic3PclkCounter, &Dd_Top_Get_CLKSTOP5(), ~D_DD_TOP_MICAP3_BIT );
			break;
		case MxicUtlis_UNIT_4:
			Dd_Top_Start_Clock( (UCHAR*)&priv->imMxic4PclkCounter, &Dd_Top_Get_CLKSTOP5(), ~D_DD_TOP_MICAP4_BIT );
			break;
		case MxicUtlis_UNIT_5:
			Dd_Top_Start_Clock( (UCHAR*)&priv->imMxic5PclkCounter, &Dd_Top_Get_CLKSTOP5(), ~D_DD_TOP_MICAP5_BIT );
			break;
		case MxicUtlis_UNIT_6:
			Dd_Top_Start_Clock( (UCHAR*)&priv->imMxic6PclkCounter, &Dd_Top_Get_CLKSTOP5(), ~D_DD_TOP_MICAP6_BIT );
			break;
		default:
			break;
	}
#endif	// MxicUtlis_CO_ACT_MXIC_PCLOCK
}

/* MXIC PCLK change to OFF.
 */
VOID mxic_utlis_off_pclk( MxicUtlis *self, ImMxicUnit unit )
{
#ifdef MxicUtlis_CO_ACT_MXIC_PCLOCK
	MxicUtlisPrivate *priv = MXIC_UTLIS_GET_PRIVATE(self);

	switch ( unit ) {
		case MxicUtlis_UNIT_0:
			Dd_Top_Stop_Clock( (UCHAR*)&priv->imMxic0PclkCounter, &Dd_Top_Get_CLKSTOP5(), D_DD_TOP_MICAP0_BIT );
			break;
		case MxicUtlis_UNIT_1:
			Dd_Top_Stop_Clock( (UCHAR*)&priv->imMxic1PclkCounter, &Dd_Top_Get_CLKSTOP5(), D_DD_TOP_MICAP1_BIT );
			break;
		case MxicUtlis_UNIT_2:
			Dd_Top_Stop_Clock( (UCHAR*)&priv->imMxic2PclkCounter, &Dd_Top_Get_CLKSTOP5(), D_DD_TOP_MICAP2_BIT );
			break;
		case MxicUtlis_UNIT_3:
			Dd_Top_Stop_Clock( (UCHAR*)&priv->imMxic3PclkCounter, &Dd_Top_Get_CLKSTOP5(), D_DD_TOP_MICAP3_BIT );
			break;
		case MxicUtlis_UNIT_4:
			Dd_Top_Stop_Clock( (UCHAR*)&priv->imMxic4PclkCounter, &Dd_Top_Get_CLKSTOP5(), D_DD_TOP_MICAP4_BIT );
			break;
		case MxicUtlis_UNIT_5:
			Dd_Top_Stop_Clock( (UCHAR*)&priv->imMxic5PclkCounter, &Dd_Top_Get_CLKSTOP5(), D_DD_TOP_MICAP5_BIT );
			break;
		case MxicUtlis_UNIT_6:
			Dd_Top_Stop_Clock( (UCHAR*)&priv->imMxic6PclkCounter, &Dd_Top_Get_CLKSTOP5(), D_DD_TOP_MICAP6_BIT );
			break;
		default:
			break;
	}
#endif	// MxicUtlis_CO_ACT_MXIC_PCLOCK
}

/* MXIC HCLK change to ON.
 */
VOID mxic_utlis_on_hclk( MxicUtlis *self, ImMxicUnit unit )
{
#ifdef MxicUtlis_CO_ACT_MXIC_HCLOCK
	MxicUtlisPrivate *priv = MXIC_UTLIS_GET_PRIVATE(self);

	switch ( unit ) {
		case MxicUtlis_UNIT_1:
			Dd_Top_Start_Clock( (UCHAR*)&priv->imMxic1HclkCounter, &Dd_Top_Get_CLKSTOP6(), ~D_DD_TOP_MICAH1_BIT );
			break;
		case MxicUtlis_UNIT_2:
			Dd_Top_Start_Clock( (UCHAR*)&priv->imMxic2HclkCounter, &Dd_Top_Get_CLKSTOP6(), ~D_DD_TOP_MICAH2_BIT );
			break;
		case MxicUtlis_UNIT_3:
			Dd_Top_Start_Clock( (UCHAR*)&priv->imMxic3HclkCounter, &Dd_Top_Get_CLKSTOP6(), ~D_DD_TOP_MICAH3_BIT );
			break;
		default:
			break;
	}
#endif	// MxicUtlis_CO_ACT_MXIC_HCLOCK
}

/* MXIC HCLK change to OFF.
 */
VOID mxic_utlis_off_hclk( MxicUtlis *self, ImMxicUnit unit )
{
#ifdef MxicUtlis_CO_ACT_MXIC_HCLOCK
	MxicUtlisPrivate *priv = MXIC_UTLIS_GET_PRIVATE(self);

	switch ( unit ) {
		case MxicUtlis_UNIT_1:
			Dd_Top_Stop_Clock( (UCHAR*)&priv->imMxic1HclkCounter, &Dd_Top_Get_CLKSTOP6(), D_DD_TOP_MICAH1_BIT );
			break;
		case MxicUtlis_UNIT_2:
			Dd_Top_Stop_Clock( (UCHAR*)&priv->imMxic2HclkCounter, &Dd_Top_Get_CLKSTOP6(), D_DD_TOP_MICAH2_BIT );
			break;
		case MxicUtlis_UNIT_3:
			Dd_Top_Stop_Clock( (UCHAR*)&priv->imMxic3HclkCounter, &Dd_Top_Get_CLKSTOP6(), D_DD_TOP_MICAH3_BIT );
			break;
		default:
			break;
	}
#endif	// MxicUtlis_CO_ACT_MXIC_HCLOCK
}

/**
Get unit address.
@param[in]		unit							MXIC unit number.<br>
@param[out]		ioMxic							MXIC address.<br>
@retval			D_DDIM_OK						Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR		Fail - Parameter error.
*/
INT32 mxic_utlis_get_unit_address( MxicUtlis *self, ImMxicUnit unit, volatile struct io_jdsmxic** ioMxic )
{
	INT32 result;

#ifdef CO_PARAM_CHECK
	if ( imMxicCheckUnit( unit ) != D_DDIM_OK ) {
		// Parameter value is illegal.
		Ddim_Assertion(("E:mxic_utlis_get_unit_address(): im_mxic_check_unit error.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
	if ( ioMxic == NULL ) {
		// Parameter is NULL.
		Ddim_Assertion(("E:mxic_utlis_get_unit_address(): ioMxic is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = D_DDIM_OK;

	switch ( unit ) {
		case MxicUtlis_UNIT_0:
			*ioMxic = &IO_MXIC0;
			break;
		case MxicUtlis_UNIT_1:
			*ioMxic = &IO_MXIC1;
			break;
		case MxicUtlis_UNIT_2:
			*ioMxic = &IO_MXIC2;
			break;
		case MxicUtlis_UNIT_3:
			*ioMxic = &IO_MXIC3;
			break;
		case MxicUtlis_UNIT_4:
			*ioMxic = &IO_MXIC4;
			break;
		case MxicUtlis_UNIT_5:
			*ioMxic = &IO_MXIC5;
			break;
		case MxicUtlis_UNIT_6:
			*ioMxic = &IO_MXIC6;
			break;
		default:
			result = MxicUtlis_INPUT_PARAM_ERROR;
			break;
	}

	return result;
}

/**
Waits until the command becomes executable. 
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		ioMxic					MXIC address.<br>
*/
VOID mxic_utlis_wait_command_enable( MxicUtlis *self, ImMxicUnit unit, volatile struct io_jdsmxic* ioMxic )
{
	mxic_utlis_on_pclk( self, unit );

	MxicUtlis_DSB();

	while ( ioMxic->TCFMD.bit.TCFLG != 1 ) {
#ifdef CO_DEBUG_ON_PC
		ioMxic->TCFMD.bit.TCFLG = 1;
#endif
		;	// DO NOTHING.
	}

	mxic_utlis_off_pclk( self, unit );
}

/**
Configuration start and wait complete.
@param[in]		ioMxic					MXIC address.<br>
*/
VOID mxic_utlis_process_configuration( MxicUtlis *self, ImMxicUnit unit, volatile struct io_jdsmxic* ioMxic )
{
	static const union io_mxic_tmif clearTcf = {
		.bit.__TCF = 1,
	};

	mxic_utlis_on_pclk( self, unit );

	// Clear interrupt flag.
	ioMxic->TMIF.word = clearTcf.word;

	// Configuration start.
	ioMxic->TCFTRG.bit.TCFTRG = 1;

	MxicUtlis_DSB();

	// Wait configuration complete.
	while ( ioMxic->TMIF.bit.__TCF == 0 ) {
		;
	}

	mxic_utlis_wait_command_enable( self, unit, ioMxic );	// Wait TCFLG=1.

	mxic_utlis_off_pclk( self, unit );
}

/**
This function get acceptance capability of the specified port.<br> 
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		wrArbiter				Target write or read Arbiter.<br>
										Please refer to @ref ImMxicWrArbiter for a set value.<br>
@param[in]		arbiter					Target arbiter.<br>
										Please refer to @ref ImMxicSpecArbiter for a set value. <br>
@param[in]		port					Target port.<br>
										Please refer to @ref ImMxicPort for a set value. <br>
@param[out]		capability				Acceptance capability. (1~8)<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32 mxic_utlis_get_acceptance_capability( MxicUtlis *self, ImMxicUnit unit, ImMxicWrArbiter wrArbiter, 
		ImMxicSpecArbiter arbiter, ImMxicPort port, UCHAR* capability )
{
	INT32						result;
	volatile struct io_jdsmxic*	ioMxic;

#ifdef CO_PARAM_CHECK
	if ( mxic_utlis_check_port( self, wrArbiter, arbiter, port) != D_DDIM_OK ) {
		// arbiter or port parameter is illegal.
		Ddim_Assertion(("E:mxic_utlis_get_acceptance_capability(): mxic_utlis_check_port error.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
	if ( capability == NULL ) {
		// capability parameter is NULL.
		Ddim_Assertion(("E:mxic_utlis_get_acceptance_capability(): capability is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( self, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {

		mxic_utlis_wait_command_enable( self, unit, ioMxic );		// Wait TCFLG=1.

		if ( wrArbiter == MxicUtlis_WR_ARBITER_W ) {
			// Write arbiter.
			mxic_utlis_on_pclk( self, unit );

			if ( unit != MxicUtlis_UNIT_4 ) {

				switch ( arbiter ) {
					case MxicUtlis_SPEC_ARBITER_1:
						// arbiter1.
						switch ( port ) {
							case MxicUtlis_PORT_0:
								*capability = ioMxic->TACPTCW.bit.TACPTCW_1_0;
								break;
							case MxicUtlis_PORT_1:
								*capability = ioMxic->TACPTCW.bit.TACPTCW_1_1;
								break;
							case MxicUtlis_PORT_2:
								*capability = ioMxic->TACPTCW.bit.TACPTCW_1_2;
								break;
							case MxicUtlis_PORT_3:
								*capability = ioMxic->TACPTCW.bit.TACPTCW_1_3;
								break;
							default:
								// Port parameter is illegal.
								result = MxicUtlis_INPUT_PARAM_ERROR;
								Ddim_Print(("E:mxic_utlis_get_acceptance_capability(): port illegal. port=%d\n", 
											port));
								break;
						}
						break;
					case MxicUtlis_SPEC_ARBITER_2:
						// arbiter2.
						switch ( port ) {
							case MxicUtlis_PORT_0:
								*capability = ioMxic->TACPTCW.bit.TACPTCW_2_0;
								break;
							case MxicUtlis_PORT_1:
								*capability = ioMxic->TACPTCW.bit.TACPTCW_2_1;
								break;
							case MxicUtlis_PORT_2:
								*capability = ioMxic->TACPTCW.bit.TACPTCW_2_2;
								break;
							case MxicUtlis_PORT_3:
								*capability = ioMxic->TACPTCW.bit.TACPTCW_2_3;
								break;
							default:
								// Port parameter is illegal.
								result = MxicUtlis_INPUT_PARAM_ERROR;
								Ddim_Print(("E:mxic_utlis_get_acceptance_capability(): port illegal. port=%d\n", 
											port));
								break;
						}
						break;
					case MxicUtlis_SPEC_ARBITER_3:
						// arbiter3.
						switch ( port ) {
							case MxicUtlis_PORT_0:
								*capability = ioMxic->TACPTCW.bit.TACPTCW_3_0;
								break;
							case MxicUtlis_PORT_1:
								*capability = ioMxic->TACPTCW.bit.TACPTCW_3_1;
								break;
							case MxicUtlis_PORT_2:
								*capability = ioMxic->TACPTCW.bit.TACPTCW_3_2;
								break;
							case MxicUtlis_PORT_3:
								*capability = ioMxic->TACPTCW.bit.TACPTCW_3_3;
								break;
							default:
								// Port parameter is illegal.
								result = MxicUtlis_INPUT_PARAM_ERROR;
								Ddim_Print(("E:mxic_utlis_get_acceptance_capability(): port illegal. port=%d\n", 
											port));
								break;
						}
						break;
					case MxicUtlis_SPEC_ARBITER_4:
						// arbiter4.
						switch ( port ) {
							case MxicUtlis_PORT_0:
								*capability = ioMxic->TACPTCW.bit.TACPTCW_4_0;
								break;
							case MxicUtlis_PORT_1:
								*capability = ioMxic->TACPTCW.bit.TACPTCW_4_1;
								break;
							case MxicUtlis_PORT_2:
								*capability = ioMxic->TACPTCW.bit.TACPTCW_4_2;
								break;
							case MxicUtlis_PORT_3:
								*capability = ioMxic->TACPTCW.bit.TACPTCW_4_3;
								break;
							default:
								// Port parameter is illegal.
								result = MxicUtlis_INPUT_PARAM_ERROR;
								Ddim_Print(("E:mxic_utlis_get_acceptance_capability(): port illegal. port=%d\n", 
											port));
								break;
						}
						break;
					default:
						// Port parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_utlis_get_acceptance_capability(): arbiter illegal. arbiter=%d\n", 
									arbiter));
						break;
				}
			}
			else {
				*capability = 0;

				// Unit number is invalid.
//				Ddim_Print(("mxic_utlis_get_acceptance_capability(): unit number is invalid. unit=%d\n", unit));
			}

			mxic_utlis_off_pclk( self, unit );
		}
		else {
			// Read arbiter.
			mxic_utlis_on_pclk( self, unit );

			if ( unit != MxicUtlis_UNIT_0 ) {

				switch ( arbiter ) {
					case MxicUtlis_SPEC_ARBITER_1:
						// arbiter1.
						switch ( port ) {
							case MxicUtlis_PORT_0:
								*capability = ioMxic->TACPTCR.bit.TACPTCR_1_0;
								break;
							case MxicUtlis_PORT_1:
								*capability = ioMxic->TACPTCR.bit.TACPTCR_1_1;
								break;
							case MxicUtlis_PORT_2:
								*capability = ioMxic->TACPTCR.bit.TACPTCR_1_2;
								break;
							case MxicUtlis_PORT_3:
								*capability = ioMxic->TACPTCR.bit.TACPTCR_1_3;
								break;
							default:
								// Port parameter is illegal.
								result = MxicUtlis_INPUT_PARAM_ERROR;
								Ddim_Print(("E:mxic_utlis_get_acceptance_capability(): port illegal. port=%d\n", 
											port));
								break;
						}
						break;
					case MxicUtlis_SPEC_ARBITER_2:
						// arbiter2.
						switch ( port ) {
							case MxicUtlis_PORT_0:
								*capability = ioMxic->TACPTCR.bit.TACPTCR_2_0;
								break;
							case MxicUtlis_PORT_1:
								*capability = ioMxic->TACPTCR.bit.TACPTCR_2_1;
								break;
							case MxicUtlis_PORT_2:
								*capability = ioMxic->TACPTCR.bit.TACPTCR_2_2;
								break;
							case MxicUtlis_PORT_3:
								*capability = ioMxic->TACPTCR.bit.TACPTCR_2_3;
								break;
							default:
								// Port parameter is illegal.
								result = MxicUtlis_INPUT_PARAM_ERROR;
								Ddim_Print(("E:mxic_utlis_get_acceptance_capability(): port illegal. port=%d\n", 
											port));
								break;
						}
						break;
					case MxicUtlis_SPEC_ARBITER_3:
						// arbiter3.
						switch ( port ) {
							case MxicUtlis_PORT_0:
								*capability = ioMxic->TACPTCR.bit.TACPTCR_3_0;
								break;
							case MxicUtlis_PORT_1:
								*capability = ioMxic->TACPTCR.bit.TACPTCR_3_1;
								break;
							case MxicUtlis_PORT_2:
								*capability = ioMxic->TACPTCR.bit.TACPTCR_3_2;
								break;
							case MxicUtlis_PORT_3:
								*capability = ioMxic->TACPTCR.bit.TACPTCR_3_3;
								break;
							default:
								// Port parameter is illegal.
								result = MxicUtlis_INPUT_PARAM_ERROR;
								Ddim_Print(("E:mxic_utlis_get_acceptance_capability(): port illegal. port=%d\n", 
											port));
								break;
						}
						break;
					case MxicUtlis_SPEC_ARBITER_4:
						// arbiter4.
						switch ( port ) {
							case MxicUtlis_PORT_0:
								*capability = ioMxic->TACPTCR.bit.TACPTCR_4_0;
								break;
							case MxicUtlis_PORT_1:
								*capability = ioMxic->TACPTCR.bit.TACPTCR_4_1;
								break;
							case MxicUtlis_PORT_2:
								*capability = ioMxic->TACPTCR.bit.TACPTCR_4_2;
								break;
							case MxicUtlis_PORT_3:
								*capability = ioMxic->TACPTCR.bit.TACPTCR_4_3;
								break;
							default:
								// Port parameter is illegal.
								result = MxicUtlis_INPUT_PARAM_ERROR;
								Ddim_Print(("E:mxic_utlis_get_acceptance_capability(): port illegal. port=%d\n", 
											port));
								break;
						}
						break;
					default:
						// Port parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_utlis_get_acceptance_capability(): arbiter illegal. arbiter=%d\n", 
									arbiter));
						break;
				}
			}
			else {
				*capability = 0;

				// Unit number is invalid.
//				Ddim_Print(("mxic_utlis_get_acceptance_capability(): unit number is invalid. unit=%d\n", unit));
			}

			mxic_utlis_off_pclk( self, unit );
		}
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:mxic_utlis_get_acceptance_capability(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

// MxicUtlis* mxic_utlis_get(void)
// {
// 	static MxicUtlis* self = NULL;
// 	if(!self){
// 		self = k_object_new_with_private(MXIC_TYPE_UTLIS, sizeof(MxicUtlisPrivate));
// 	}
// 	return self;
// }

MxicUtlis *mxic_utlis_new(void)
{
    MxicUtlis* self = k_object_new_with_private(MXIC_TYPE_UTLIS, sizeof(MxicUtlisPrivate));
    return self;
}
