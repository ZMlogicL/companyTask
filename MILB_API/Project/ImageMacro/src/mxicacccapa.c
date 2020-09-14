/***********************************************************************
 * @Copyright(C) 上海网用软件有限公司
 * @file mxicacccapa.c
 * @date 2020-09-02
 * @author: 吴海辉
 * @brief: 
 * @version: 1.0.0
***********************************************************************/

#include "mxicacccapa.h"


K_TYPE_DEFINE_WITH_PRIVATE(MxicAccCapa, mxic_acc_capa)
#define MXIC_ACC_CAPA_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), MxicAccCapaPrivate, MXIC_TYPE_ACC_CAPA))

// Definition for acceptance capability
#define MxicAccCapa_MIN_VAL			(1)				// Minimum value of acceptance capability
#define MxicAccCapa_MAX_VAL			(8)				// Maximum value of acceptance capability


struct _MxicAccCapaPrivate
{
    MxicUtlis* mxicUtlis;
};


/*----------------------------------------------------------------------*/
/* DECLS  															    */
/*----------------------------------------------------------------------*/
#ifdef CO_PARAM_CHECK
static kint32 imMxicCheckAcceptanceCapability( kuchar capability );
static kint32 imMxicCheckPortGroup( ImMxicWrArbiter wrArbiter, 
									ImMxicSpecArbiterGr arbiter, ImMxicPortGr port );
#endif // CO_PARAM_CHECK


/*----------------------------------------------------------------------*/
/* IMPL  															    */
/*----------------------------------------------------------------------*/
static void mxic_acc_capa_constructor(MxicAccCapa *self)
{
    MxicAccCapaPrivate *priv = MXIC_ACC_CAPA_GET_PRIVATE(self);

	priv->mxicUtlis = mxic_utlis_new();
}

static void mxic_acc_capa_destructor(MxicAccCapa *self)
{
    MxicAccCapaPrivate *priv = MXIC_ACC_CAPA_GET_PRIVATE(self);

	if(priv->mxicUtlis)
	{
		k_object_unref(priv->mxicUtlis);
		priv->mxicUtlis = NULL;
	}
}

#ifdef CO_PARAM_CHECK
/**
Check value of acceptance capability.
@param[in]		capability				Acceptance capability.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
static kint32 imMxicCheckAcceptanceCapability( kuchar capability )
{
	kint32 result;

	result = D_DDIM_OK;

	if ( ( capability < MxicAccCapa_MIN_VAL ) || ( capability > MxicAccCapa_MAX_VAL ) ) {
		result = MxicUtlis_INPUT_PARAM_ERROR;
		Ddim_Print(("E:imMxicCheckAcceptanceCapability(): capability is illegal. capability=%d\n", capability));
	}

	return result;
}

/**
Check port specifies parameter. (gropu)
@param[in]		wrArbiter				Write or Read Arbiter.<br>
@param[in]		arbiter					Arbiter.<br>
@param[in]		port					Port.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
static kint32 imMxicCheckPortGroup( ImMxicWrArbiter wrArbiter, ImMxicSpecArbiterGr arbiter, ImMxicPortGr port )
{
	kint32 result;

	result = D_DDIM_OK;

	if ( ( wrArbiter >= MxicUtlis_WR_ARBITER_MAX ) || ( arbiter >= MxicUtlis_SPEC_ARBITER_GR_MAX ) 
		|| ( port >= MxicUtlis_PORT_GR_MAX ) ) {
		result = MxicUtlis_INPUT_PARAM_ERROR;
		Ddim_Print(("E:imMxicCheckPortGroup(): Parameter is illegal. wrArbiter=%d, arbiter=%d, port=%d\n", 
					wrArbiter, arbiter, port));
	}

	return result;
}
#endif // CO_PARAM_CHECK


/*----------------------------------------------------------------------*/
/* PUBLIC  															    */
/*----------------------------------------------------------------------*/
/**
This function set acceptance capability of the specified port.<br> 
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		wrArbiter				Target write or read Arbiter.<br>
										Please refer to @ref ImMxicWrArbiter for a set value.<br>
@param[in]		arbiter					Target arbiter.<br>
										Please refer to @ref ImMxicSpecArbiter for a set value. <br>
@param[in]		port					Target port.<br>
										Please refer to @ref ImMxicPort for a set value. <br>
@param[in]		capability				Acceptance capability. (1~8)<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
kint32 mxic_acc_capa_set_acceptance_capability( MxicAccCapa *self, ImMxicUnit unit, ImMxicWrArbiter wrArbiter, 
		ImMxicSpecArbiter arbiter, ImMxicPort port, kuchar capability )
{
	kuchar						regReadSw;
	kint32						result;
	volatile struct io_jdsmxic*	ioMxic;
	MxicAccCapaPrivate *priv = MXIC_ACC_CAPA_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( mxic_utlis_check_port( priv->mxicUtlis, wrArbiter, arbiter, port ) != D_DDIM_OK ) {
		// arbiter or port parameter is illegal.
		Ddim_Assertion(("E:mxic_acc_capa_set_acceptance_capability(): mxic_utlis_check_port error.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
	if ( imMxicCheckAcceptanceCapability( capability ) != D_DDIM_OK ) {
		// capability parameter is illegal.
		Ddim_Assertion(("E:mxic_acc_capa_set_acceptance_capability(): imMxicCheckAcceptanceCapability error.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {
		// If operation type is "set", wait TCFLG=1.
		mxic_utlis_wait_command_enable( priv->mxicUtlis, unit, ioMxic );

		mxic_utlis_on_pclk( priv->mxicUtlis, unit );

		regReadSw = ioMxic->TRVSW.bit.TRVSW;

		if ( regReadSw == MxicUtlis_ON ) {
			ioMxic->TRVSW.bit.TRVSW = MxicUtlis_OFF;
		}

		if ( wrArbiter == MxicUtlis_WR_ARBITER_W ) {

			if ( unit != MxicUtlis_UNIT_4 ) {
				// Write arbiter.
				switch ( arbiter ) {
					case MxicUtlis_SPEC_ARBITER_1:
						// arbiter1.
						switch ( port ) {
							case MxicUtlis_PORT_0:
								ioMxic->TACPTCW.bit.TACPTCW_1_0 = capability;
								break;
							case MxicUtlis_PORT_1:
								ioMxic->TACPTCW.bit.TACPTCW_1_1 = capability;
								break;
							case MxicUtlis_PORT_2:
								ioMxic->TACPTCW.bit.TACPTCW_1_2 = capability;
								break;
							case MxicUtlis_PORT_3:
								ioMxic->TACPTCW.bit.TACPTCW_1_3 = capability;
								break;
							default:
								// Port parameter is illegal.
								result = MxicUtlis_INPUT_PARAM_ERROR;
								Ddim_Print(("E:mxic_acc_capa_set_acceptance_capability(): port illegal. port=%d\n", 
											port));
								break;
						}
						break;
					case MxicUtlis_SPEC_ARBITER_2:
						// arbiter2.
						switch ( port ) {
							case MxicUtlis_PORT_0:
								ioMxic->TACPTCW.bit.TACPTCW_2_0 = capability;
								break;
							case MxicUtlis_PORT_1:
								ioMxic->TACPTCW.bit.TACPTCW_2_1 = capability;
								break;
							case MxicUtlis_PORT_2:
								ioMxic->TACPTCW.bit.TACPTCW_2_2 = capability;
								break;
							case MxicUtlis_PORT_3:
								ioMxic->TACPTCW.bit.TACPTCW_2_3 = capability;
								break;
							default:
								// Port parameter is illegal.
								result = MxicUtlis_INPUT_PARAM_ERROR;
								Ddim_Print(("E:mxic_acc_capa_set_acceptance_capability(): port illegal. port=%d\n", 
											port));
								break;
						}
						break;
					case MxicUtlis_SPEC_ARBITER_3:
						// arbiter3.
						switch ( port ) {
							case MxicUtlis_PORT_0:
								ioMxic->TACPTCW.bit.TACPTCW_3_0 = capability;
								break;
							case MxicUtlis_PORT_1:
								ioMxic->TACPTCW.bit.TACPTCW_3_1 = capability;
								break;
							case MxicUtlis_PORT_2:
								ioMxic->TACPTCW.bit.TACPTCW_3_2 = capability;
								break;
							case MxicUtlis_PORT_3:
								ioMxic->TACPTCW.bit.TACPTCW_3_3 = capability;
								break;
							default:
								// Port parameter is illegal.
								result = MxicUtlis_INPUT_PARAM_ERROR;
								Ddim_Print(("E:mxic_acc_capa_set_acceptance_capability(): port illegal. port=%d\n", 
											port));
								break;
						}
						break;
					case MxicUtlis_SPEC_ARBITER_4:
						// arbiter4.
						switch ( port ) {
							case MxicUtlis_PORT_0:
								ioMxic->TACPTCW.bit.TACPTCW_4_0 = capability;
								break;
							case MxicUtlis_PORT_1:
								ioMxic->TACPTCW.bit.TACPTCW_4_1 = capability;
								break;
							case MxicUtlis_PORT_2:
								ioMxic->TACPTCW.bit.TACPTCW_4_2 = capability;
								break;
							case MxicUtlis_PORT_3:
								ioMxic->TACPTCW.bit.TACPTCW_4_3 = capability;
								break;
							default:
								// Port parameter is illegal.
								result = MxicUtlis_INPUT_PARAM_ERROR;
								Ddim_Print(("E:mxic_acc_capa_set_acceptance_capability(): port illegal. port=%d\n", 
											port));
								break;
						}
						break;
					default:
						// Port parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_acc_capa_set_acceptance_capability(): arbiter illegal. arbiter=%d\n", 
									arbiter));
						break;
				}
			}
			else {
				// Unit number is invalid.
				//Ddim_Print(("mxic_acc_capa_set_acceptance_capability(): unit number is invalid. unit=%d\n", unit));
			}
		}
		else {
			if ( unit != MxicUtlis_UNIT_0 ) {
				// Read arbiter.
				switch ( arbiter ) {
					case MxicUtlis_SPEC_ARBITER_1:
						// arbiter1.
						switch ( port ) {
							case MxicUtlis_PORT_0:
								ioMxic->TACPTCR.bit.TACPTCR_1_0 = capability;
								break;
							case MxicUtlis_PORT_1:
								ioMxic->TACPTCR.bit.TACPTCR_1_1 = capability;
								break;
							case MxicUtlis_PORT_2:
								ioMxic->TACPTCR.bit.TACPTCR_1_2 = capability;
								break;
							case MxicUtlis_PORT_3:
								ioMxic->TACPTCR.bit.TACPTCR_1_3 = capability;
								break;
							default:
								// Port parameter is illegal.
								result = MxicUtlis_INPUT_PARAM_ERROR;
								Ddim_Print(("E:mxic_acc_capa_set_acceptance_capability(): port illegal. port=%d\n", 
											port));
								break;
						}
						break;
					case MxicUtlis_SPEC_ARBITER_2:
						// arbiter2.
						switch ( port ) {
							case MxicUtlis_PORT_0:
								ioMxic->TACPTCR.bit.TACPTCR_2_0 = capability;
								break;
							case MxicUtlis_PORT_1:
								ioMxic->TACPTCR.bit.TACPTCR_2_1 = capability;
								break;
							case MxicUtlis_PORT_2:
								ioMxic->TACPTCR.bit.TACPTCR_2_2 = capability;
								break;
							case MxicUtlis_PORT_3:
								ioMxic->TACPTCR.bit.TACPTCR_2_3 = capability;
								break;
							default:
								// Port parameter is illegal.
								result = MxicUtlis_INPUT_PARAM_ERROR;
								Ddim_Print(("E:mxic_acc_capa_set_acceptance_capability(): port illegal. port=%d\n", 
											port));
								break;
						}
						break;
					case MxicUtlis_SPEC_ARBITER_3:
						// arbiter3
						switch ( port ) {
							case MxicUtlis_PORT_0:
								ioMxic->TACPTCR.bit.TACPTCR_3_0 = capability;
								break;
							case MxicUtlis_PORT_1:
								ioMxic->TACPTCR.bit.TACPTCR_3_1 = capability;
								break;
							case MxicUtlis_PORT_2:
								ioMxic->TACPTCR.bit.TACPTCR_3_2 = capability;
								break;
							case MxicUtlis_PORT_3:
								ioMxic->TACPTCR.bit.TACPTCR_3_3 = capability;
								break;
							default:
								// Port parameter is illegal.
								result = MxicUtlis_INPUT_PARAM_ERROR;
								Ddim_Print(("E:mxic_acc_capa_set_acceptance_capability(): port illegal. port=%d\n", 
											port));
								break;
						}
						break;
					case MxicUtlis_SPEC_ARBITER_4:
						// arbiter4
						switch (port) {
							case MxicUtlis_PORT_0:
								ioMxic->TACPTCR.bit.TACPTCR_4_0 = capability;
								break;
							case MxicUtlis_PORT_1:
								ioMxic->TACPTCR.bit.TACPTCR_4_1 = capability;
								break;
							case MxicUtlis_PORT_2:
								ioMxic->TACPTCR.bit.TACPTCR_4_2 = capability;
								break;
							case MxicUtlis_PORT_3:
								ioMxic->TACPTCR.bit.TACPTCR_4_3 = capability;
								break;
							default:
								// Port parameter is illegal.
								result = MxicUtlis_INPUT_PARAM_ERROR;
								Ddim_Print(("E:mxic_acc_capa_set_acceptance_capability(): port illegal. port=%d\n", 
											port));
								break;
						}
						break;
					default:
						// Port parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_acc_capa_set_acceptance_capability(): arbiter illegal. arbiter=%d\n", 
									arbiter));
						break;
				}
			}
			else {
				// Unit number is invalid.
				//Ddim_Print(("mxic_acc_capa_set_acceptance_capability(): unit number is invalid. unit=%d\n", unit));
			}
		}

		// Configuration start.
		mxic_utlis_process_configuration( priv->mxicUtlis, unit, ioMxic );

		if ( regReadSw == MxicUtlis_ON ) {
			ioMxic->TRVSW.bit.TRVSW = MxicUtlis_ON;
		}

		mxic_utlis_off_pclk( priv->mxicUtlis, unit );

		MxicUtlis_DSB();
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:mxic_acc_capa_set_acceptance_capability(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

/**
This function set acceptance capability of all ports.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		allCapability			Acceptance capability of all ports.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
kint32 mxic_acc_capa_set_acceptance_capability_all_port( MxicAccCapa *self, ImMxicUnit unit, 
		const MxicAllAcceptanceCapability* const allCapability )
{
	kint32	result;
	kint32	i, j;

#ifdef CO_PARAM_CHECK
	if ( allCapability == NULL ) {
		// allCapability parameter is NULL.
		Ddim_Assertion(("E:mxic_acc_capa_set_acceptance_capability_all_port(): allCapability is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = D_DDIM_OK;

	// Setting of W ports.
	for ( i = MxicUtlis_W_ARBITER_W1; i < MxicUtlis_W_ARBITER_MAX; i++ ) {
		// Set acceptance capability of all W ports.
		for (j = MxicUtlis_PORT_0; j < MxicUtlis_PORT_MAX; j++) {
			result = mxic_acc_capa_set_acceptance_capability( NULL, unit, MxicUtlis_WR_ARBITER_W, 
				(ImMxicSpecArbiter)i, (ImMxicPort)j, allCapability->wCapability[i][j] );
			if (result != D_DDIM_OK) {
				// Parameter error.
				Ddim_Print(("E:mxic_acc_capa_set_acceptance_capability_all_port(): "
							"mxic_acc_capa_set_acceptance_capability error. (Write)\n"));
				return MxicUtlis_INPUT_PARAM_ERROR;
			}
		}
	}

	// Setting of R ports.
	for ( i = MxicUtlis_R_ARBITER_R1; i < MxicUtlis_R_ARBITER_MAX; i++ ) {
		// Set acceptance capability of all R ports.
		for ( j = MxicUtlis_PORT_0; j < MxicUtlis_PORT_MAX; j++ ) {
			result = mxic_acc_capa_set_acceptance_capability( NULL, unit, MxicUtlis_WR_ARBITER_R, 
					(ImMxicSpecArbiter)i, (ImMxicPort)j, allCapability->rCapability[i][j] );
			if (result != D_DDIM_OK) {
				// Parameter error.
				Ddim_Print(("E:mxic_acc_capa_set_acceptance_capability_all_port(): "
							"mxic_acc_capa_set_acceptance_capability error. (Read)\n"));
				return MxicUtlis_INPUT_PARAM_ERROR;
			}
		}
	}

	// Set acceptance capability of all W ports.
	for ( j = MxicUtlis_PORT_GR_0; j < MxicUtlis_PORT_GR_MAX; j++ ) {
		// Setting of Group-W ports.
		for ( i = MxicUtlis_W_ARBITER_GR_W0; i < MxicUtlis_W_ARBITER_GR_MAX; i++ ) {
			result = mxic_acc_capa_set_acceptance_capability_group(self, MxicUtlis_WR_ARBITER_W, 
					(ImMxicSpecArbiterGr)i, (ImMxicPortGr)j, allCapability->wCapabilityGr[i][j] );
			if ( result != D_DDIM_OK ) {
				// Parameter error.
				Ddim_Print(("E:mxic_acc_capa_set_acceptance_capability_all_port(): "
							"mxic_acc_capa_set_acceptance_capability_group error. (Write)\n"));
				return MxicUtlis_INPUT_PARAM_ERROR;
			}
		}
	}

	// Set acceptance capability of all R ports.
	for (j = MxicUtlis_PORT_GR_0; j < MxicUtlis_PORT_GR_MAX; j++) {
		// Setting of Group-R ports.
		for ( i = MxicUtlis_R_ARBITER_GR_R0; i < MxicUtlis_R_ARBITER_GR_MAX; i++ ) {
			result = mxic_acc_capa_set_acceptance_capability_group( self, MxicUtlis_WR_ARBITER_R, 
					(ImMxicSpecArbiterGr)i, (ImMxicPortGr)j, allCapability->rCapabilityGr[i][j] );
			if (result != D_DDIM_OK) {
				// Parameter error.
				Ddim_Print(("E:mxic_acc_capa_set_acceptance_capability_all_port(): "
							"mxic_acc_capa_set_acceptance_capability_group error. (Read)\n"));
				return MxicUtlis_INPUT_PARAM_ERROR;
			}
		}
	}

	MxicUtlis_DSB();

	return D_DDIM_OK;
}

/**
This function get acceptance capability of all ports.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[out]		allCapability			Acceptance capability of all ports.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
kint32 mxic_acc_capa_get_acceptance_capability_all_port( MxicAccCapa *self, ImMxicUnit unit, 
		MxicAllAcceptanceCapability* const allCapability )
{
	kint32	result;
	kint32	i, j;
	MxicAccCapaPrivate *priv = MXIC_ACC_CAPA_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( allCapability == NULL ) {
		// allCapability parameter is NULL.
		Ddim_Assertion(("E:mxic_acc_capa_get_acceptance_capability_all_port(): allCapability is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = D_DDIM_OK;

	// Setting of W ports.
	for ( i = MxicUtlis_W_ARBITER_W1; i < MxicUtlis_W_ARBITER_MAX; i++ ) {
		// Get acceptance capability of all W ports.
		for ( j = MxicUtlis_PORT_0; j < MxicUtlis_PORT_MAX; j++ ) {
			result = mxic_utlis_get_acceptance_capability( priv->mxicUtlis, unit, MxicUtlis_WR_ARBITER_W, 
					(ImMxicSpecArbiter)i, (ImMxicPort)j, &allCapability->wCapability[i][j] );
			if ( result != D_DDIM_OK ) {
				// Parameter error.
				Ddim_Print(("E:mxic_acc_capa_get_acceptance_capability_all_port(): "
							"MxicUtlis_GET_Acceptance_Capability error. (Write)\n"));
				return MxicUtlis_INPUT_PARAM_ERROR;
			}
		}
	}

	// Setting of R ports.
	for ( i = MxicUtlis_R_ARBITER_R1; i < MxicUtlis_R_ARBITER_MAX; i++ ) {
		// Get acceptance capability of all R ports.
		for ( j = MxicUtlis_PORT_0; j < MxicUtlis_PORT_MAX; j++ ) {
			result = mxic_utlis_get_acceptance_capability( priv->mxicUtlis, unit, MxicUtlis_WR_ARBITER_R, 
					(ImMxicSpecArbiter)i, (ImMxicPort)j, &allCapability->rCapability[i][j] );
			if ( result != D_DDIM_OK ) {
				// Parameter error.
				Ddim_Print(("E:mxic_acc_capa_get_acceptance_capability_all_port(): "
							"MxicUtlis_GET_Acceptance_Capability error. (Read)\n"));
				return MxicUtlis_INPUT_PARAM_ERROR;
			}
		}
	}

	// Get acceptance capability of all W ports.
	for ( j = MxicUtlis_PORT_GR_0; j < MxicUtlis_PORT_GR_MAX; j++ ) {
		// Setting of Group-W ports.
		for ( i = MxicUtlis_W_ARBITER_GR_W0; i < MxicUtlis_W_ARBITER_GR_MAX; i++ ) {
			result = mxic_acc_capa_get_acceptance_capability_group( self, MxicUtlis_WR_ARBITER_W, 
					(ImMxicSpecArbiterGr)i, (ImMxicPortGr)j, &allCapability->wCapabilityGr[i][j] );
			if ( result != D_DDIM_OK ) {
				// Parameter error.
				Ddim_Print(("E:mxic_acc_capa_get_acceptance_capability_all_port(): "
							"mxic_acc_capa_get_acceptance_capability_group error. (Write)\n"));
				return MxicUtlis_INPUT_PARAM_ERROR;
			}
		}
	}

	// Get acceptance capability of all R ports.
	for ( j = MxicUtlis_PORT_GR_0; j < MxicUtlis_PORT_GR_MAX; j++ ) {
		// Setting of Group-R ports.
		for ( i = MxicUtlis_R_ARBITER_GR_R0; i < MxicUtlis_R_ARBITER_GR_MAX; i++ ) {
			result = mxic_acc_capa_get_acceptance_capability_group( self, MxicUtlis_WR_ARBITER_R, 
					(ImMxicSpecArbiterGr)i, (ImMxicPortGr)j, &allCapability->rCapabilityGr[i][j] );
			if ( result != D_DDIM_OK ) {
				// Parameter error.
				Ddim_Print(("E:mxic_acc_capa_get_acceptance_capability_all_port(): "
							"mxic_acc_capa_get_acceptance_capability_group error. (Read)\n"));
				return MxicUtlis_INPUT_PARAM_ERROR;
			}
		}
	}

	return D_DDIM_OK;
}

/**
This function set acceptance capability (gropu) of the specified port.<br> 
@param[in]		wrArbiter				Target write or read Arbiter.<br>
										Please refer to @ref ImMxicWrArbiter for a set value.<br>
@param[in]		arbiter					Target arbiter.<br>
										Please refer to @ref ImMxicSpecArbiterGr for a set value. <br>
@param[in]		port					Target port.<br>
										Please refer to @ref ImMxicPortGr for a set value. <br>
@param[in]		capability				Acceptance capability. (1~8)<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
kint32 mxic_acc_capa_set_acceptance_capability_group( MxicAccCapa *self, ImMxicWrArbiter wrArbiter, 
		ImMxicSpecArbiterGr arbiter, ImMxicPortGr port, kuchar capability )
{
	kuchar	regReadSw;
	kint32	result;
	MxicAccCapaPrivate *priv = MXIC_ACC_CAPA_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( imMxicCheckPortGroup( wrArbiter, arbiter, port ) != D_DDIM_OK ) {
		// arbiter or port parameter is illegal.
		Ddim_Assertion(("E:mxic_acc_capa_set_acceptance_capability_group(): mxic_utlis_check_port error.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
	if ( imMxicCheckAcceptanceCapability( capability ) != D_DDIM_OK ) {
		// capability parameter is illegal.
		Ddim_Assertion(("E:mxic_acc_capa_set_acceptance_capability_group(): "
						"imMxicCheckAcceptanceCapability error.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = D_DDIM_OK;

	mxic_utlis_wait_command_enable( priv->mxicUtlis, MxicUtlis_UNIT_3, (struct io_jdsmxic *)&IO_MXIC3 );// Wait TCFLG=1.

	mxic_utlis_on_pclk( priv->mxicUtlis, MxicUtlis_UNIT_3 );

	regReadSw = IO_MXIC3.TRVSW.bit.TRVSW;

	if ( regReadSw == MxicUtlis_ON ) {
		IO_MXIC3.TRVSW.bit.TRVSW = MxicUtlis_OFF;
	}

	if ( wrArbiter == MxicUtlis_WR_ARBITER_W ) {
		// Write arbiter.
		switch ( arbiter ) {
			case MxicUtlis_SPEC_ARBITER_GR_0:
				// arbiter0.
				switch ( port ) {
					case MxicUtlis_PORT_GR_0:
						IO_MXIC3.TGACPTCW.bit.TGACPTCW_0_0 = capability;
						break;
					case MxicUtlis_PORT_GR_1:
						IO_MXIC3.TGACPTCW.bit.TGACPTCW_0_1 = capability;
						break;
					default:
						// Port parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_acc_capa_set_acceptance_capability_group(): "
									"port illegal. port=%d\n", port));
						break;
				}
				break;
			case MxicUtlis_SPEC_ARBITER_GR_1:
				// arbiter1.
				switch ( port ) {
					case MxicUtlis_PORT_GR_0:
						IO_MXIC3.TGACPTCW.bit.TGACPTCW_1_0 = capability;
						break;
					case MxicUtlis_PORT_GR_1:
						IO_MXIC3.TGACPTCW.bit.TGACPTCW_1_1 = capability;
						break;
					default:
						// Port parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_acc_capa_set_acceptance_capability_group(): port illegal. port=%d\n", 
									port));
						break;
				}
				break;
			case MxicUtlis_SPEC_ARBITER_GR_2:
				// arbiter2.
				switch ( port ) {
					case MxicUtlis_PORT_GR_0:
						IO_MXIC3.TGACPTCW.bit.TGACPTCW_2_0 = capability;
						break;
					case MxicUtlis_PORT_GR_1:
						IO_MXIC3.TGACPTCW.bit.TGACPTCW_2_1 = capability;
						break;
					default:
						// Port parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_acc_capa_set_acceptance_capability_group(): port illegal. port=%d\n", 
									port));
						break;
				}
				break;
			case MxicUtlis_SPEC_ARBITER_GR_3:
				// arbiter3.
				switch ( port ) {
					case MxicUtlis_PORT_GR_0:
						IO_MXIC3.TGACPTCW.bit.TGACPTCW_3_0 = capability;
						break;
					case MxicUtlis_PORT_GR_1:
						IO_MXIC3.TGACPTCW.bit.TGACPTCW_3_1 = capability;
						break;
					default:
						// Port parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_acc_capa_set_acceptance_capability_group(): port illegal. port=%d\n", 
									port));
						break;
				}
				break;
			case MxicUtlis_SPEC_ARBITER_GR_4:
				// arbiter4.
				switch ( port ) {
					case MxicUtlis_PORT_GR_0:
						IO_MXIC3.TGACPTCW.bit.TGACPTCW_4_0 = capability;
						break;
					case MxicUtlis_PORT_GR_1:
						IO_MXIC3.TGACPTCW.bit.TGACPTCW_4_1 = capability;
						break;
					default:
						// Port parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_acc_capa_set_acceptance_capability_group(): port illegal. port=%d\n", 
									port));
						break;
				}
				break;
			case MxicUtlis_SPEC_ARBITER_GR_5:
				// arbiter5.
				switch ( port ) {
					case MxicUtlis_PORT_GR_0:
						IO_MXIC3.TGACPTCW.bit.TGACPTCW_5_0 = capability;
						break;
					case MxicUtlis_PORT_GR_1:
						IO_MXIC3.TGACPTCW.bit.TGACPTCW_5_1 = capability;
						break;
					default:
						// Port parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_acc_capa_set_acceptance_capability_group(): port illegal. port=%d\n", 
									port));
						break;
				}
				break;
			case MxicUtlis_SPEC_ARBITER_GR_6:
				// arbiter6.
				switch ( port ) {
					case MxicUtlis_PORT_GR_0:
						IO_MXIC3.TGACPTCW.bit.TGACPTCW_6_0 = capability;
						break;
					case MxicUtlis_PORT_GR_1:
						IO_MXIC3.TGACPTCW.bit.TGACPTCW_6_1 = capability;
						break;
					default:
						// Port parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_acc_capa_set_acceptance_capability_group(): port illegal. port=%d\n", 
									port));
						break;
				}
				break;
			case MxicUtlis_SPEC_ARBITER_GR_7:
				// arbiter7.
				switch ( port ) {
					case MxicUtlis_PORT_GR_0:
						IO_MXIC3.TGACPTCW.bit.TGACPTCW_7_0 = capability;
						break;
					case MxicUtlis_PORT_GR_1:
						IO_MXIC3.TGACPTCW.bit.TGACPTCW_7_1 = capability;
						break;
					default:
						// Port parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_acc_capa_set_acceptance_capability_group(): port illegal. port=%d\n", 
									port));
						break;
				}
				break;
			default:
				// Port parameter is illegal.
				result = MxicUtlis_INPUT_PARAM_ERROR;
				Ddim_Print(("E:mxic_acc_capa_set_acceptance_capability_group(): arbiter illegal. arbiter=%d\n", 
							arbiter));
				break;
		}
	}
	else {
		// Read arbiter.
		switch ( arbiter ) {
			case MxicUtlis_SPEC_ARBITER_GR_0:
				// arbiter0.
				switch ( port ) {
					case MxicUtlis_PORT_GR_0:
						IO_MXIC3.TGACPTCR.bit.TGACPTCR_0_0 = capability;
						break;
					case MxicUtlis_PORT_GR_1:
						IO_MXIC3.TGACPTCR.bit.TGACPTCR_0_1 = capability;
						break;
					default:
						// Port parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_acc_capa_set_acceptance_capability_group(): port illegal. port=%d\n", 
									port));
						break;
				}
				break;
			case MxicUtlis_SPEC_ARBITER_GR_1:
				// arbiter1.
				switch ( port ) {
					case MxicUtlis_PORT_GR_0:
						IO_MXIC3.TGACPTCR.bit.TGACPTCR_1_0 = capability;
						break;
					case MxicUtlis_PORT_GR_1:
						IO_MXIC3.TGACPTCR.bit.TGACPTCR_1_1 = capability;
						break;
					default:
						// Port parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_acc_capa_set_acceptance_capability_group(): port illegal. port=%d\n", 
									port));
						break;
				}
				break;
			case MxicUtlis_SPEC_ARBITER_GR_2:
				// arbiter2.
				switch ( port ) {
					case MxicUtlis_PORT_GR_0:
						IO_MXIC3.TGACPTCR.bit.TGACPTCR_2_0 = capability;
						break;
					case MxicUtlis_PORT_GR_1:
						IO_MXIC3.TGACPTCR.bit.TGACPTCR_2_1 = capability;
						break;
					default:
						// Port parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_acc_capa_set_acceptance_capability_group(): port illegal. port=%d\n", 
									port));
						break;
				}
				break;
			case MxicUtlis_SPEC_ARBITER_GR_3:
				// arbiter3.
				switch ( port ) {
					case MxicUtlis_PORT_GR_0:
						IO_MXIC3.TGACPTCR.bit.TGACPTCR_3_0 = capability;
						break;
					case MxicUtlis_PORT_GR_1:
						IO_MXIC3.TGACPTCR.bit.TGACPTCR_3_1 = capability;
						break;
					default:
						// Port parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_acc_capa_set_acceptance_capability_group(): port illegal. port=%d\n", 
									port));
						break;
				}
				break;
			case MxicUtlis_SPEC_ARBITER_GR_4:
				// arbiter4.
				switch ( port ) {
					case MxicUtlis_PORT_GR_0:
						IO_MXIC3.TGACPTCR.bit.TGACPTCR_4_0 = capability;
						break;
					case MxicUtlis_PORT_GR_1:
						IO_MXIC3.TGACPTCR.bit.TGACPTCR_4_1 = capability;
						break;
					default:
						// Port parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_acc_capa_set_acceptance_capability_group(): port illegal. port=%d\n", 
									port));
						break;
				}
				break;
			case MxicUtlis_SPEC_ARBITER_GR_5:
				// arbiter5.
				switch ( port ) {
					case MxicUtlis_PORT_GR_0:
						IO_MXIC3.TGACPTCR.bit.TGACPTCR_5_0 = capability;
						break;
					case MxicUtlis_PORT_GR_1:
						IO_MXIC3.TGACPTCR.bit.TGACPTCR_5_1 = capability;
						break;
					default:
						// Port parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_acc_capa_set_acceptance_capability_group(): port illegal. port=%d\n", 
									port));
						break;
				}
				break;
			case MxicUtlis_SPEC_ARBITER_GR_6:
				// arbiter6.
				switch ( port ) {
					case MxicUtlis_PORT_GR_0:
						IO_MXIC3.TGACPTCR.bit.TGACPTCR_6_0 = capability;
						break;
					case MxicUtlis_PORT_GR_1:
						IO_MXIC3.TGACPTCR.bit.TGACPTCR_6_1 = capability;
						break;
					default:
						// Port parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_acc_capa_set_acceptance_capability_group(): port illegal. port=%d\n", 
									port));
						break;
				}
				break;
			case MxicUtlis_SPEC_ARBITER_GR_7:
				// arbiter7.
				switch ( port ) {
					case MxicUtlis_PORT_GR_0:
						IO_MXIC3.TGACPTCR.bit.TGACPTCR_7_0 = capability;
						break;
					case MxicUtlis_PORT_GR_1:
						IO_MXIC3.TGACPTCR.bit.TGACPTCR_7_1 = capability;
						break;
					default:
						// Port parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_acc_capa_set_acceptance_capability_group(): port illegal. port=%d\n", 
									port));
						break;
				}
				break;
			default:
				// Port parameter is illegal.
				result = MxicUtlis_INPUT_PARAM_ERROR;
				Ddim_Print(("E:mxic_acc_capa_set_acceptance_capability_group(): arbiter illegal. arbiter=%d\n", 
							arbiter));
				break;
		}
	}

	// Configuration start.
	mxic_utlis_process_configuration( priv->mxicUtlis, MxicUtlis_UNIT_3, &IO_MXIC3 );

	if ( regReadSw == MxicUtlis_ON ) {
		IO_MXIC3.TRVSW.bit.TRVSW = MxicUtlis_ON;
	}

	mxic_utlis_off_pclk( priv->mxicUtlis, MxicUtlis_UNIT_3 );

	MxicUtlis_DSB();

	return result;
}

/**
This function get acceptance capability (gropu) of the specified port.<br> 
@param[in]		wrArbiter				Target write or read Arbiter.<br>
										Please refer to @ref ImMxicWrArbiter for a set value.<br>
@param[in]		arbiter					Target arbiter.<br>
										Please refer to @ref ImMxicSpecArbiterGr for a set value. <br>
@param[in]		port					Target port.<br>
										Please refer to @ref ImMxicPortGr for a set value. <br>
@param[out]		capability				Acceptance capability. (1~8)<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
kint32 mxic_acc_capa_get_acceptance_capability_group( MxicAccCapa *self, ImMxicWrArbiter wrArbiter, 
		ImMxicSpecArbiterGr arbiter, ImMxicPortGr port, kuchar* capability )
{
	kint32	result;
	MxicAccCapaPrivate *priv = MXIC_ACC_CAPA_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( imMxicCheckPortGroup( wrArbiter, arbiter, port ) != D_DDIM_OK ) {
		// arbiter or port parameter is illegal.
		Ddim_Assertion(("E:mxic_acc_capa_get_acceptance_capability_group(): mxic_utlis_check_port error.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
	if ( capability == NULL ) {
		// capability parameter is NULL.
		Ddim_Assertion(("E:mxic_acc_capa_get_acceptance_capability_group(): capability is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = D_DDIM_OK;

	mxic_utlis_wait_command_enable( priv->mxicUtlis, MxicUtlis_UNIT_3, (struct io_jdsmxic *)&IO_MXIC3 );// Wait TCFLG=1.

	mxic_utlis_on_pclk( priv->mxicUtlis, MxicUtlis_UNIT_3 );

	if ( wrArbiter == MxicUtlis_WR_ARBITER_W ) {
		// Write arbiter.
		switch ( arbiter ) {
			case MxicUtlis_SPEC_ARBITER_GR_0:
				// arbiter0.
				switch ( port ) {
					case MxicUtlis_PORT_GR_0:
						*capability = IO_MXIC3.TGACPTCW.bit.TGACPTCW_0_0;
						break;
					case MxicUtlis_PORT_GR_1:
						*capability = IO_MXIC3.TGACPTCW.bit.TGACPTCW_0_1;
						break;
					default:
						// Port parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_acc_capa_get_acceptance_capability_group(): port illegal. port=%d\n", 
									port));
						break;
				}
				break;
			case MxicUtlis_SPEC_ARBITER_GR_1:
				// arbiter1.
				switch ( port ) {
					case MxicUtlis_PORT_GR_0:
						*capability = IO_MXIC3.TGACPTCW.bit.TGACPTCW_1_0;
						break;
					case MxicUtlis_PORT_GR_1:
						*capability = IO_MXIC3.TGACPTCW.bit.TGACPTCW_1_1;
						break;
					default:
						// Port parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_acc_capa_get_acceptance_capability_group(): port illegal. port=%d\n", 
									port));
						break;
				}
				break;
			case MxicUtlis_SPEC_ARBITER_GR_2:
				// arbiter2.
				switch ( port ) {
					case MxicUtlis_PORT_GR_0:
						*capability = IO_MXIC3.TGACPTCW.bit.TGACPTCW_2_0;
						break;
					case MxicUtlis_PORT_GR_1:
						*capability = IO_MXIC3.TGACPTCW.bit.TGACPTCW_2_1;
						break;
					default:
						// Port parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_acc_capa_get_acceptance_capability_group(): port illegal. port=%d\n", 
									port));
						break;
				}
				break;
			case MxicUtlis_SPEC_ARBITER_GR_3:
				// arbiter3.
				switch ( port ) {
					case MxicUtlis_PORT_GR_0:
						*capability = IO_MXIC3.TGACPTCW.bit.TGACPTCW_3_0;
						break;
					case MxicUtlis_PORT_GR_1:
						*capability = IO_MXIC3.TGACPTCW.bit.TGACPTCW_3_1;
						break;
					default:
						// Port parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_acc_capa_get_acceptance_capability_group(): port illegal. port=%d\n", 
									port));
						break;
				}
				break;
			case MxicUtlis_SPEC_ARBITER_GR_4:
				// arbiter4.
				switch ( port ) {
					case MxicUtlis_PORT_GR_0:
						*capability = IO_MXIC3.TGACPTCW.bit.TGACPTCW_4_0;
						break;
					case MxicUtlis_PORT_GR_1:
						*capability = IO_MXIC3.TGACPTCW.bit.TGACPTCW_4_1;
						break;
					default:
						// Port parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_acc_capa_get_acceptance_capability_group(): port illegal. port=%d\n", 
									port));
						break;
				}
				break;
			case MxicUtlis_SPEC_ARBITER_GR_5:
				// arbiter5.
				switch ( port ) {
					case MxicUtlis_PORT_GR_0:
						*capability = IO_MXIC3.TGACPTCW.bit.TGACPTCW_5_0;
						break;
					case MxicUtlis_PORT_GR_1:
						*capability = IO_MXIC3.TGACPTCW.bit.TGACPTCW_5_1;
						break;
					default:
						// Port parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_acc_capa_get_acceptance_capability_group(): port illegal. port=%d\n", 
									port));
						break;
				}
				break;
			case MxicUtlis_SPEC_ARBITER_GR_6:
				// arbiter6.
				switch ( port ) {
					case MxicUtlis_PORT_GR_0:
						*capability = IO_MXIC3.TGACPTCW.bit.TGACPTCW_6_0;
						break;
					case MxicUtlis_PORT_GR_1:
						*capability = IO_MXIC3.TGACPTCW.bit.TGACPTCW_6_1;
						break;
					default:
						// Port parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_acc_capa_get_acceptance_capability_group(): port illegal. port=%d\n", 
									port));
						break;
				}
				break;
			case MxicUtlis_SPEC_ARBITER_GR_7:
				// arbiter7.
				switch ( port ) {
					case MxicUtlis_PORT_GR_0:
						*capability = IO_MXIC3.TGACPTCW.bit.TGACPTCW_7_0;
						break;
					case MxicUtlis_PORT_GR_1:
						*capability = IO_MXIC3.TGACPTCW.bit.TGACPTCW_7_1;
						break;
					default:
						// Port parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_acc_capa_get_acceptance_capability_group(): port illegal. port=%d\n", 
									port));
						break;
				}
				break;
			default:
				// Port parameter is illegal.
				result = MxicUtlis_INPUT_PARAM_ERROR;
				Ddim_Print(("E:mxic_acc_capa_get_acceptance_capability_group(): arbiter illegal. arbiter=%d\n", 
							arbiter));
				break;
		}
	}
	else {
		// Read arbiter.
		switch ( arbiter ) {
			case MxicUtlis_SPEC_ARBITER_GR_0:
				// arbiter0.
				switch ( port ) {
					case MxicUtlis_PORT_GR_0:
						*capability = IO_MXIC3.TGACPTCR.bit.TGACPTCR_0_0;
						break;
					case MxicUtlis_PORT_GR_1:
						*capability = IO_MXIC3.TGACPTCR.bit.TGACPTCR_0_1;
						break;
					default:
						// Port parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_acc_capa_get_acceptance_capability_group(): port illegal. port=%d\n", 
									port));
						break;
				}
				break;
			case MxicUtlis_SPEC_ARBITER_GR_1:
				// arbiter1.
				switch ( port ) {
					case MxicUtlis_PORT_GR_0:
						*capability = IO_MXIC3.TGACPTCR.bit.TGACPTCR_1_0;
						break;
					case MxicUtlis_PORT_GR_1:
						*capability = IO_MXIC3.TGACPTCR.bit.TGACPTCR_1_1;
						break;
					default:
						// Port parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_acc_capa_get_acceptance_capability_group(): port illegal. port=%d\n", 
									port));
						break;
				}
				break;
			case MxicUtlis_SPEC_ARBITER_GR_2:
				// arbiter2.
				switch ( port ) {
					case MxicUtlis_PORT_GR_0:
						*capability = IO_MXIC3.TGACPTCR.bit.TGACPTCR_2_0;
						break;
					case MxicUtlis_PORT_GR_1:
						*capability = IO_MXIC3.TGACPTCR.bit.TGACPTCR_2_1;
						break;
					default:
						// Port parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_acc_capa_get_acceptance_capability_group(): port illegal. port=%d\n", 
									port));
						break;
				}
				break;
			case MxicUtlis_SPEC_ARBITER_GR_3:
				// arbiter3.
				switch ( port ) {
					case MxicUtlis_PORT_GR_0:
						*capability = IO_MXIC3.TGACPTCR.bit.TGACPTCR_3_0;
						break;
					case MxicUtlis_PORT_GR_1:
						*capability = IO_MXIC3.TGACPTCR.bit.TGACPTCR_3_1;
						break;
					default:
						// Port parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_acc_capa_get_acceptance_capability_group(): port illegal. port=%d\n", 
									port));
						break;
				}
				break;
			case MxicUtlis_SPEC_ARBITER_GR_4:
				// arbiter4.
				switch ( port ) {
					case MxicUtlis_PORT_GR_0:
						*capability = IO_MXIC3.TGACPTCR.bit.TGACPTCR_4_0;
						break;
					case MxicUtlis_PORT_GR_1:
						*capability = IO_MXIC3.TGACPTCR.bit.TGACPTCR_4_1;
						break;
					default:
						// Port parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_acc_capa_get_acceptance_capability_group(): port illegal. port=%d\n", 
									port));
						break;
				}
				break;
			case MxicUtlis_SPEC_ARBITER_GR_5:
				// arbiter5.
				switch ( port ) {
					case MxicUtlis_PORT_GR_0:
						*capability = IO_MXIC3.TGACPTCR.bit.TGACPTCR_5_0;
						break;
					case MxicUtlis_PORT_GR_1:
						*capability = IO_MXIC3.TGACPTCR.bit.TGACPTCR_5_1;
						break;
					default:
						// Port parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_acc_capa_get_acceptance_capability_group(): port illegal. port=%d\n", 
									port));
						break;
				}
				break;
			case MxicUtlis_SPEC_ARBITER_GR_6:
				// arbiter6.
				switch ( port ) {
					case MxicUtlis_PORT_GR_0:
						*capability = IO_MXIC3.TGACPTCR.bit.TGACPTCR_6_0;
						break;
					case MxicUtlis_PORT_GR_1:
						*capability = IO_MXIC3.TGACPTCR.bit.TGACPTCR_6_1;
						break;
					default:
						// Port parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_acc_capa_get_acceptance_capability_group(): port illegal. port=%d\n", 
									port));
						break;
				}
				break;
			case MxicUtlis_SPEC_ARBITER_GR_7:
				// arbiter7.
				switch ( port ) {
					case MxicUtlis_PORT_GR_0:
						*capability = IO_MXIC3.TGACPTCR.bit.TGACPTCR_7_0;
						break;
					case MxicUtlis_PORT_GR_1:
						*capability = IO_MXIC3.TGACPTCR.bit.TGACPTCR_7_1;
						break;
					default:
						// Port parameter is illegal.
						result = MxicUtlis_INPUT_PARAM_ERROR;
						Ddim_Print(("E:mxic_acc_capa_get_acceptance_capability_group(): port illegal. port=%d\n", 
									port));
						break;
				}
				break;
			default:
				// Port parameter is illegal.
				result = MxicUtlis_INPUT_PARAM_ERROR;
				Ddim_Print(("E:mxic_acc_capa_get_acceptance_capability_group(): arbiter illegal. arbiter=%d\n", 
							arbiter));
				break;
		}
	}

	mxic_utlis_off_pclk( priv->mxicUtlis, MxicUtlis_UNIT_3 );

	return result;
}

MxicAccCapa *mxic_acc_capa_new(void)
{
    MxicAccCapa* self = k_object_new_with_private(MXIC_TYPE_ACC_CAPA, sizeof(MxicAccCapaPrivate));
    return self;
}
