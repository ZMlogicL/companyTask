/***********************************************************************
 * @Copyright(C) 上海网用软件有限公司
 * @file mxiclevelport.c
 * @date 2020-09-02
 * @author: 吴海辉
 * @brief: 
 * @version: 1.0.0
***********************************************************************/

#include "mxiclevelport.h"


K_TYPE_DEFINE_WITH_PRIVATE(MxicLevelPort, mxic_level_port)
#define MXIC_LEVEL_PORT_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), MxicLevelPortPrivate, MXIC_TYPE_LEVEL_PORT))

// TGCKEN.TGCKSEN bit flag
#define MxicLevelPort_TGCKEN_TGCKSEN_GROUP_0	(0x01)			// Group-0 arbiter block
#define MxicLevelPort_TGCKEN_TGCKSEN_GROUP_1	(0x02)			// Group-1 arbiter block
#define MxicLevelPort_TGCKEN_TGCKSEN_GROUP_2	(0x04)			// Group-2 arbiter block
#define MxicLevelPort_TGCKEN_TGCKSEN_GROUP_3	(0x08)			// Group-3 arbiter block
#define MxicLevelPort_TGCKEN_TGCKSEN_GROUP_4	(0x10)			// Group-4 arbiter block
#define MxicLevelPort_TGCKEN_TGCKSEN_GROUP_5	(0x20)			// Group-5 arbiter block
#define MxicLevelPort_TGCKEN_TGCKSEN_GROUP_6	(0x40)			// Group-6 arbiter block
#define MxicLevelPort_TGCKEN_TGCKSEN_GROUP_7	(0x80)			// Group-7 arbiter block

// TCKENP.TCKENP_1/2/3/4 bit flag
#define MxicLevelPort_TCKENP_TCKENP_SLAVE_x_0	(0x01)			// Slave-x port-0 arbiter block
#define MxicLevelPort_TCKENP_TCKENP_SLAVE_x_1	(0x02)			// Slave-x port-1 arbiter block
#define MxicLevelPort_TCKENP_TCKENP_SLAVE_x_2	(0x04)			// Slave-x port-2 arbiter block
#define MxicLevelPort_TCKENP_TCKENP_SLAVE_x_3	(0x08)			// Slave-x port-3 arbiter block


struct _MxicLevelPortPrivate
{
    MxicUtlis* mxicUtlis;
};


/*----------------------------------------------------------------------*/
/* DECLS  															    */
/*----------------------------------------------------------------------*/
#ifdef CO_PARAM_CHECK
static INT32 imMxicCheckLevel( ImMxicWrArbiter wrArbiter, 
								ImMxicSpecArbiter arbiter, ImMxicLevel level );
static INT32 imMxicCheckArbiter( ImMxicWrArbiter wrArbiter, ImMxicSpecArbiter arbiter );
#endif // CO_PARAM_CHECK


/*----------------------------------------------------------------------*/
/* IMPL  															    */
/*----------------------------------------------------------------------*/
static void mxic_level_port_constructor(MxicLevelPort *self)
{
    MxicLevelPortPrivate *priv = MXIC_LEVEL_PORT_GET_PRIVATE(self);

	priv->mxicUtlis = mxic_utlis_new();
}

static void mxic_level_port_destructor(MxicLevelPort *self)
{
	MxicLevelPortPrivate *priv = MXIC_LEVEL_PORT_GET_PRIVATE(self);

	if(priv->mxicUtlis)
	{
		k_object_unref(priv->mxicUtlis);
		priv->mxicUtlis = NULL;
	}
}

#ifdef CO_PARAM_CHECK

/**
Check level specifies parameter.
@param[in]		wrArbiter				Write or Read Arbiter.<br>
@param[in]		arbiter					Arbiter.<br>
@param[in]		level					Level.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
static INT32 imMxicCheckLevel( ImMxicWrArbiter wrArbiter, 
								ImMxicSpecArbiter arbiter, ImMxicLevel level )
{
	INT32 result;

	result = D_DDIM_OK;

	if ( ( wrArbiter >= MxicUtlis_WR_ARBITER_MAX ) || ( arbiter >= MxicUtlis_SPEC_ARBITER_MAX ) 
		|| ( level >= MxicUtlis_LEVEL_MAX ) ) {
		result = MxicUtlis_INPUT_PARAM_ERROR;
		Ddim_Print(("E:imMxicCheckLevel(): Parameter is illegal. wrArbiter=%d, arbiter=%d, level=%d\n", 
					wrArbiter, arbiter, level));
	}

	return result;
}

/**
Check arbiter specifies parameter.
@param[in]		wrArbiter				Write or Read Arbiter.<br>
@param[in]		arbiter					Arbiter.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
static INT32 imMxicCheckArbiter( ImMxicWrArbiter wrArbiter, ImMxicSpecArbiter arbiter )
{
	INT32 result;

	result = D_DDIM_OK;

	if ( ( wrArbiter >= MxicUtlis_WR_ARBITER_MAX ) || ( arbiter >= MxicUtlis_SPEC_ARBITER_MAX ) ) {
		result = MxicUtlis_INPUT_PARAM_ERROR;
		Ddim_Print(("E:imMxicCheckArbiter(): Parameter is illegal. wrArbiter=%d, arbiter=%d\n", wrArbiter, arbiter));
	}

	return result;
}

#endif // CO_PARAM_CHECK


/*----------------------------------------------------------------------*/
/* PUBLIC  															    */
/*----------------------------------------------------------------------*/
/**
This function set clock supply to a functional block. 
@param [in]		unit							Target unit number.<br>
												Please refer to @ref ImMxicUnit for a set value. <br>
@param [in]		clock							Clock enable setting.<br>
@retval			D_DDIM_OK						Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR		Fail - Parameter error.
*/
INT32 mxic_level_port_set_clock_enable( MxicLevelPort *self, ImMxicUnit unit, const ImMxicClock* const clock )
{
	UCHAR						tckenp1;	// Write value of IO_MXIC.TCKENP.bit.TCKENP_1.
	UCHAR						tckenp2;	// Write value of IO_MXIC.TCKENP.bit.TCKENP_2.
	UCHAR						tckenp3;	// Write value of IO_MXIC.TCKENP.bit.TCKENP_3.
	UCHAR						tckenp4;	// Write value of IO_MXIC.TCKENP.bit.TCKENP_4.
	UCHAR						tgcksen;	// Write value of IO_MXIC.TGCKEN.bit.TGCKSEN.
	INT32						result;
	volatile struct io_jdsmxic*	ioMxic;
	MxicLevelPortPrivate *priv = MXIC_LEVEL_PORT_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( clock == NULL ) {
		// clock parameter is NULL.
		Ddim_Assertion(("E:mxic_level_port_set_clock_enable(): clock is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {
		// Initialize write value of TCKENP, TGCKSEN.
		tckenp1	= 0;
		tckenp2	= 0;
		tckenp3	= 0;
		tckenp4	= 0;
		tgcksen		= 0;

		mxic_utlis_on_pclk( priv->mxicUtlis, unit );

		// Decode error block.
		if ( clock->clkEnDecErr == MxicUtlis_ON ) {
			ioMxic->TCKEN.bit.TCKSEN = 1;
		}
		else {
			ioMxic->TCKEN.bit.TCKSEN = 0;
		}
		// Monitor block.
		if (clock->clkEnMonitor == MxicUtlis_ON ) {
			ioMxic->TCKEN.bit.TCKMEN = 1;
		}
		else{
			ioMxic->TCKEN.bit.TCKMEN = 0;
		}

		// Slave-1 port-0 arbiter block.
		if ( clock->clkEnSlave10 == MxicUtlis_ON ) {
			tckenp1 |= MxicLevelPort_TCKENP_TCKENP_SLAVE_x_0;
		}
		// Slave-1 port-1 arbiter block.
		if ( clock->clkEnSlave11 == MxicUtlis_ON ) {
			tckenp1 |= MxicLevelPort_TCKENP_TCKENP_SLAVE_x_1;
		}
		// Slave-1 port-2 arbiter block.
		if ( clock->clkEnSlave12 == MxicUtlis_ON ) {
			tckenp1 |= MxicLevelPort_TCKENP_TCKENP_SLAVE_x_2;
		}
		// Slave-1 port-3 arbiter block.
		if ( clock->clkEnSlave13 == MxicUtlis_ON ) {
			tckenp1 |= MxicLevelPort_TCKENP_TCKENP_SLAVE_x_3;
		}
		ioMxic->TCKENP.bit.TCKENP_1 = tckenp1;

		// Slave-2 port-0 arbiter block.
		if ( clock->clkEnSlave20 == MxicUtlis_ON ) {
			tckenp2 |= MxicLevelPort_TCKENP_TCKENP_SLAVE_x_0;
		}
		// Slave-2 port-1 arbiter block.
		if ( clock->clkEnSlave21 == MxicUtlis_ON ) {
			tckenp2 |= MxicLevelPort_TCKENP_TCKENP_SLAVE_x_1;
		}
		// Slave-2 port-2 arbiter block.
		if ( clock->clkEnSlave22 == MxicUtlis_ON ) {
			tckenp2 |= MxicLevelPort_TCKENP_TCKENP_SLAVE_x_2;
		}
		// Slave-2 port-3 arbiter block.
		if ( clock->clkEnSlave23 == MxicUtlis_ON ) {
			tckenp2 |= MxicLevelPort_TCKENP_TCKENP_SLAVE_x_3;
		}
		ioMxic->TCKENP.bit.TCKENP_2 = tckenp2;

		// Slave-3 port-0 arbiter block.
		if ( clock->clkEnSlave30 == MxicUtlis_ON ) {
			tckenp3 |= MxicLevelPort_TCKENP_TCKENP_SLAVE_x_0;
		}
		// Slave-3 port-1 arbiter block.
		if ( clock->clkEnSlave31 == MxicUtlis_ON ) {
			tckenp3 |= MxicLevelPort_TCKENP_TCKENP_SLAVE_x_1;
		}
		// Slave-3 port-2 arbiter block.
		if ( clock->clkEnSlave32 == MxicUtlis_ON ) {
			tckenp3 |= MxicLevelPort_TCKENP_TCKENP_SLAVE_x_2;
		}
		// Slave-3 port-3 arbiter block.
		if ( clock->clkEnSlave33 == MxicUtlis_ON ) {
			tckenp3 |= MxicLevelPort_TCKENP_TCKENP_SLAVE_x_3;
		}
		ioMxic->TCKENP.bit.TCKENP_3 = tckenp3;

		// Slave-4 port-0 arbiter block.
		if ( clock->clkEnSlave40 == MxicUtlis_ON ) {
			tckenp4 |= MxicLevelPort_TCKENP_TCKENP_SLAVE_x_0;
		}
		// Slave-4 port-1 arbiter block.
		if ( clock->clkEnSlave41 == MxicUtlis_ON ) {
			tckenp4 |= MxicLevelPort_TCKENP_TCKENP_SLAVE_x_1;
		}
		// Slave-4 port-2 arbiter block.
		if ( clock->clkEnSlave42 == MxicUtlis_ON ) {
			tckenp4 |= MxicLevelPort_TCKENP_TCKENP_SLAVE_x_2;
		}
		// Slave-4 port-3 arbiter block.
		if ( clock->clkEnSlave43 == MxicUtlis_ON ) {
			tckenp4 |= MxicLevelPort_TCKENP_TCKENP_SLAVE_x_3;
		}
		ioMxic->TCKENP.bit.TCKENP_4 = tckenp4;

		if ( unit == MxicUtlis_UNIT_3 ) {
			// Group-0 arbiter block
			if ( clock->clkEnGroup0 == MxicUtlis_ON ) {
				tgcksen |= MxicLevelPort_TGCKEN_TGCKSEN_GROUP_0;
			}
			// Group-1 arbiter block
			if ( clock->clkEnGroup1 == MxicUtlis_ON ) {
				tgcksen |= MxicLevelPort_TGCKEN_TGCKSEN_GROUP_1;
			}
			// Group-2 arbiter block
			if ( clock->clkEnGroup2 == MxicUtlis_ON ) {
				tgcksen |= MxicLevelPort_TGCKEN_TGCKSEN_GROUP_2;
			}
			// Group-3 arbiter block
			if ( clock->clkEnGroup3 == MxicUtlis_ON ) {
				tgcksen |= MxicLevelPort_TGCKEN_TGCKSEN_GROUP_3;
			}
			// Group-4 arbiter block
			if ( clock->clkEnGroup4 == MxicUtlis_ON ) {
				tgcksen |= MxicLevelPort_TGCKEN_TGCKSEN_GROUP_4;
			}
			// Group-5 arbiter block
			if ( clock->clkEnGroup5 == MxicUtlis_ON ) {
				tgcksen |= MxicLevelPort_TGCKEN_TGCKSEN_GROUP_5;
			}
			// Group-6 arbiter block
			if ( clock->clkEnGroup6 == MxicUtlis_ON ) {
				tgcksen |= MxicLevelPort_TGCKEN_TGCKSEN_GROUP_6;
			}
			// Group-7 arbiter block
			if ( clock->clkEnGroup7 == MxicUtlis_ON ) {
				tgcksen |= MxicLevelPort_TGCKEN_TGCKSEN_GROUP_7;
			}
			ioMxic->TGCKEN.bit.TGCKSEN = tgcksen;
		}

		mxic_utlis_off_pclk( priv->mxicUtlis, unit );

		MxicUtlis_DSB();
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:mxic_level_port_set_clock_enable(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

/**
This function get clock supply to a functional block. 
@param [in]		unit							Target unit number.<br>
												Please refer to @ref ImMxicUnit for a set value. <br>
@param [out]	clock							Clock enable setting.<br>
@retval			D_DDIM_OK						Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR		Fail - Parameter error.
*/
INT32 mxic_level_port_get_clock_enable( MxicLevelPort *self, ImMxicUnit unit, ImMxicClock* const clock )
{
	INT32						result;
	volatile struct io_jdsmxic*	ioMxic;
	MxicLevelPortPrivate *priv = MXIC_LEVEL_PORT_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (clock == NULL ) {
		// clock parameter is NULL.
		Ddim_Assertion(("E:mxic_level_port_get_clock_enable(): clock is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {

		mxic_utlis_on_pclk( priv->mxicUtlis, unit );

		// Decode error block.
		clock->clkEnDecErr = ioMxic->TCKEN.bit.TCKSEN;

		// Monitor block.
		clock->clkEnMonitor = ioMxic->TCKEN.bit.TCKMEN;

		// Slave-1 port-0 arbiter block.
		if ( ( ioMxic->TCKENP.bit.TCKENP_1 & MxicLevelPort_TCKENP_TCKENP_SLAVE_x_0 ) != 0 ) {
			clock->clkEnSlave10 = MxicUtlis_ON;
		}
		else {
			clock->clkEnSlave10 = MxicUtlis_OFF;
		}
		// Slave-1 port-1 arbiter block.
		if ( ( ioMxic->TCKENP.bit.TCKENP_1 & MxicLevelPort_TCKENP_TCKENP_SLAVE_x_1 ) != 0 ) {
			clock->clkEnSlave11 = MxicUtlis_ON;
		}
		else {
			clock->clkEnSlave11 = MxicUtlis_OFF;
		}
		// Slave-1 port-2 arbiter block.
		if ( ( ioMxic->TCKENP.bit.TCKENP_1 & MxicLevelPort_TCKENP_TCKENP_SLAVE_x_2 ) != 0 ) {
			clock->clkEnSlave12 = MxicUtlis_ON;
		}
		else {
			clock->clkEnSlave12 = MxicUtlis_OFF;
		}
		// Slave-1 port-3 arbiter block.
		if ( ( ioMxic->TCKENP.bit.TCKENP_1 & MxicLevelPort_TCKENP_TCKENP_SLAVE_x_3 ) != 0 ) {
			clock->clkEnSlave13 = MxicUtlis_ON;
		}
		else {
			clock->clkEnSlave13 = MxicUtlis_OFF;
		}
		// Slave-2 port-0 arbiter block.
		if ( ( ioMxic->TCKENP.bit.TCKENP_2 & MxicLevelPort_TCKENP_TCKENP_SLAVE_x_0 ) != 0 ) {
			clock->clkEnSlave20 = MxicUtlis_ON;
		}
		else {
			clock->clkEnSlave20 = MxicUtlis_OFF;
		}
		// Slave-2 port-1 arbiter block.
		if ( ( ioMxic->TCKENP.bit.TCKENP_2 & MxicLevelPort_TCKENP_TCKENP_SLAVE_x_1 ) != 0 ) {
			clock->clkEnSlave21 = MxicUtlis_ON;
		}
		else {
			clock->clkEnSlave21 = MxicUtlis_OFF;
		}
		// Slave-2 port-2 arbiter block.
		if ( ( ioMxic->TCKENP.bit.TCKENP_2 & MxicLevelPort_TCKENP_TCKENP_SLAVE_x_2 ) != 0 ) {
			clock->clkEnSlave22 = MxicUtlis_ON;
		}
		else {
			clock->clkEnSlave22 = MxicUtlis_OFF;
		}
		// Slave-2 port-3 arbiter block.
		if ( ( ioMxic->TCKENP.bit.TCKENP_2 & MxicLevelPort_TCKENP_TCKENP_SLAVE_x_3 ) != 0 ) {
			clock->clkEnSlave23 = MxicUtlis_ON;
		}
		else {
			clock->clkEnSlave23 = MxicUtlis_OFF;
		}
		// Slave-3 port-0 arbiter block.
		if ( ( ioMxic->TCKENP.bit.TCKENP_3 & MxicLevelPort_TCKENP_TCKENP_SLAVE_x_0 ) != 0 ) {
			clock->clkEnSlave30 = MxicUtlis_ON;
		}
		else {
			clock->clkEnSlave30 = MxicUtlis_OFF;
		}
		// Slave-3 port-1 arbiter block.
		if ( ( ioMxic->TCKENP.bit.TCKENP_3 & MxicLevelPort_TCKENP_TCKENP_SLAVE_x_1 ) != 0 ) {
			clock->clkEnSlave31 = MxicUtlis_ON;
		}
		else {
			clock->clkEnSlave31 = MxicUtlis_OFF;
		}
		// Slave-3 port-2 arbiter block.
		if ( ( ioMxic->TCKENP.bit.TCKENP_3 & MxicLevelPort_TCKENP_TCKENP_SLAVE_x_2 ) != 0 ) {
			clock->clkEnSlave32 = MxicUtlis_ON;
		}
		else {
			clock->clkEnSlave32 = MxicUtlis_OFF;
		}
		// Slave-3 port-3 arbiter block.
		if ( ( ioMxic->TCKENP.bit.TCKENP_3 & MxicLevelPort_TCKENP_TCKENP_SLAVE_x_3 ) != 0 ) {
			clock->clkEnSlave33 = MxicUtlis_ON;
		}
		else {
			clock->clkEnSlave33 = MxicUtlis_OFF;
		}
		// Slave-4 port-0 arbiter block.
		if ( ( ioMxic->TCKENP.bit.TCKENP_4 & MxicLevelPort_TCKENP_TCKENP_SLAVE_x_0 ) != 0 ) {
			clock->clkEnSlave40 = MxicUtlis_ON;
		}
		else {
			clock->clkEnSlave40 = MxicUtlis_OFF;
		}
		// Slave-4 port-1 arbiter block.
		if ( ( ioMxic->TCKENP.bit.TCKENP_4 & MxicLevelPort_TCKENP_TCKENP_SLAVE_x_1 ) != 0 ) {
			clock->clkEnSlave41 = MxicUtlis_ON;
		}
		else {
			clock->clkEnSlave41 = MxicUtlis_OFF;
		}
		// Slave-4 port-2 arbiter block.
		if ( ( ioMxic->TCKENP.bit.TCKENP_4 & MxicLevelPort_TCKENP_TCKENP_SLAVE_x_2 ) != 0 ) {
			clock->clkEnSlave42 = MxicUtlis_ON;
		}
		else {
			clock->clkEnSlave42 = MxicUtlis_OFF;
		}
		// Slave-4 port-3 arbiter block.
		if ( ( ioMxic->TCKENP.bit.TCKENP_4 & MxicLevelPort_TCKENP_TCKENP_SLAVE_x_3 ) != 0 ) {
			clock->clkEnSlave43 = MxicUtlis_ON;
		}
		else {
			clock->clkEnSlave43 = MxicUtlis_OFF;
		}

		if ( unit == MxicUtlis_UNIT_3 ) {
			// Group-0 arbiter block.
			if ( ( ioMxic->TGCKEN.bit.TGCKSEN & MxicLevelPort_TGCKEN_TGCKSEN_GROUP_0 ) != 0 ) {
				clock->clkEnGroup0 = MxicUtlis_ON;
			}
			else {
				clock->clkEnGroup0 = MxicUtlis_OFF;
			}
			// Group-1 arbiter block.
			if ( ( ioMxic->TGCKEN.bit.TGCKSEN & MxicLevelPort_TGCKEN_TGCKSEN_GROUP_1 ) != 0 ) {
				clock->clkEnGroup1 = MxicUtlis_ON;
			}
			else {
				clock->clkEnGroup1 = MxicUtlis_OFF;
			}
			// Group-2 arbiter block.
			if ( ( ioMxic->TGCKEN.bit.TGCKSEN & MxicLevelPort_TGCKEN_TGCKSEN_GROUP_2 ) != 0 ) {
				clock->clkEnGroup2 = MxicUtlis_ON;
			}
			else {
				clock->clkEnGroup2 = MxicUtlis_OFF;
			}
			// Group-3 arbiter block.
			if ( ( ioMxic->TGCKEN.bit.TGCKSEN & MxicLevelPort_TGCKEN_TGCKSEN_GROUP_3 ) != 0 ) {
				clock->clkEnGroup3 = MxicUtlis_ON;
			}
			else {
				clock->clkEnGroup3 = MxicUtlis_OFF;
			}
			// Group-4 arbiter block.
			if ( ( ioMxic->TGCKEN.bit.TGCKSEN & MxicLevelPort_TGCKEN_TGCKSEN_GROUP_4 ) != 0 ) {
				clock->clkEnGroup4 = MxicUtlis_ON;
			}
			else {
				clock->clkEnGroup4 = MxicUtlis_OFF;
			}
			// Group-5 arbiter block.
			if ( ( ioMxic->TGCKEN.bit.TGCKSEN & MxicLevelPort_TGCKEN_TGCKSEN_GROUP_5 ) != 0 ) {
				clock->clkEnGroup5 = MxicUtlis_ON;
			}
			else {
				clock->clkEnGroup5 = MxicUtlis_OFF;
			}
			// Group-6 arbiter block.
			if ( ( ioMxic->TGCKEN.bit.TGCKSEN & MxicLevelPort_TGCKEN_TGCKSEN_GROUP_6 ) != 0 ) {
				clock->clkEnGroup6 = MxicUtlis_ON;
			}
			else {
				clock->clkEnGroup6 = MxicUtlis_OFF;
			}
			// Group-7 arbiter block.
			if ( ( ioMxic->TGCKEN.bit.TGCKSEN & MxicLevelPort_TGCKEN_TGCKSEN_GROUP_7 ) != 0 ) {
				clock->clkEnGroup7 = MxicUtlis_ON;
			}
			else {
				clock->clkEnGroup7 = MxicUtlis_OFF;
			}
		}
		else {
			clock->clkEnGroup0 = MxicUtlis_OFF;
			clock->clkEnGroup1 = MxicUtlis_OFF;
			clock->clkEnGroup2 = MxicUtlis_OFF;
			clock->clkEnGroup3 = MxicUtlis_OFF;
			clock->clkEnGroup4 = MxicUtlis_OFF;
			clock->clkEnGroup5 = MxicUtlis_OFF;
			clock->clkEnGroup6 = MxicUtlis_OFF;
			clock->clkEnGroup7 = MxicUtlis_OFF;
		}

		mxic_utlis_off_pclk( priv->mxicUtlis, unit );
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:mxic_level_port_get_clock_enable(): mxic_utlis_get_unit_address error.\n"));
	}
	return result;
}

/**
This function set the LevelPort(Port).<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		wrArbiter				Target write or read Arbiter.<br>
										Please refer to @ref ImMxicWrArbiter for a set value.<br>
@param[in]		arbiter					Target arbiter.<br>
										Please refer to @ref ImMxicSpecArbiter for a set value.<br>
@param[in]		master					Master number.<br>
@param[in]		port					Target Port.<br>
										Please refer to @ref ImMxicPort for a set value.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32 mxic_level_port_set_levelport_port( MxicLevelPort *self, LevelPortArgs portArgs, 
											UCHAR master, ImMxicPort port )
{
	UCHAR						regReadSw;
	INT32						result;
	volatile struct io_jdsmxic*	ioMxic;
	MxicLevelPortPrivate *priv = MXIC_LEVEL_PORT_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( mxic_utlis_check_port( priv->mxicUtlis, portArgs.wrArbiter, portArgs.arbiter, port ) != D_DDIM_OK ) {
		// arbiter or port parameter is illegal.
		Ddim_Assertion(("E:mxic_level_port_set_levelport_port(): mxic_utlis_check_port error.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, portArgs.unit, &ioMxic );

	if ( result == D_DDIM_OK ) {

		mxic_utlis_on_pclk( priv->mxicUtlis, portArgs.unit );

		regReadSw = ioMxic->TRVSW.bit.TRVSW;

		if ( regReadSw == MxicUtlis_ON ) {
			ioMxic->TRVSW.bit.TRVSW = MxicUtlis_OFF;
		}

		if ( portArgs.wrArbiter == MxicUtlis_WR_ARBITER_W ) {

			if ( master < MxicUtlis_MASTER_NUMBER_MAX ) {

				if ( portArgs.unit != MxicUtlis_UNIT_4 ) {
					// Write arbiter.
					switch ( portArgs.arbiter ) {
						case MxicUtlis_SPEC_ARBITER_1:
							ioMxic->TMARLP_W_1[(master - 1)].bit.MAS_PORT_W = port;
							break;
						case MxicUtlis_SPEC_ARBITER_2:
							ioMxic->TMARLP_W_2[(master - 1)].bit.MAS_PORT_W = port;
							break;
						case MxicUtlis_SPEC_ARBITER_3:
							ioMxic->TMARLP_W_3[(master - 1)].bit.MAS_PORT_W = port;
							break;
						case MxicUtlis_SPEC_ARBITER_4:
							ioMxic->TMARLP_W_4[(master - 1)].bit.MAS_PORT_W = port;
							break;
						default:
							// arbiter parameter is illegal.
							result = MxicUtlis_INPUT_PARAM_ERROR;
							Ddim_Print(("E:mxic_level_port_set_levelport_port(): arbiter illegal. arbiter=%d\n", 
										portArgs.arbiter));
							break;
					}
				}
				else {
					// Unit number is invalid.
					//Ddim_Print(("mxic_level_port_set_levelport_port(): unit number is invalid. unit=%d\n", unit));
				}
			}
			else {
				// master number is illegal.
				result = MxicUtlis_INPUT_PARAM_ERROR;
				Ddim_Print(("E:mxic_level_port_set_levelport_port(): master number illegal. arbiter=%d\n", 
							portArgs.arbiter));
			}
		}
		else {
			if ( master < MxicUtlis_MASTER_NUMBER_MAX ) {

				if ( portArgs.unit != MxicUtlis_UNIT_0 ) {
					// Read arbiter.
					switch ( portArgs.arbiter ) {
						case MxicUtlis_SPEC_ARBITER_1:
							ioMxic->TMARLP_R_1[(master - 1)].bit.MAS_PORT_R = port;
							break;
						case MxicUtlis_SPEC_ARBITER_2:
							ioMxic->TMARLP_R_2[(master - 1)].bit.MAS_PORT_R = port;
							break;
						case MxicUtlis_SPEC_ARBITER_3:
							ioMxic->TMARLP_R_3[(master - 1)].bit.MAS_PORT_R = port;
							break;
						case MxicUtlis_SPEC_ARBITER_4:
							ioMxic->TMARLP_R_4[(master - 1)].bit.MAS_PORT_R = port;
							break;
						default:
							// arbiter parameter is illegal.
							result = MxicUtlis_INPUT_PARAM_ERROR;
							Ddim_Print(("E:mxic_level_port_set_levelport_port(): arbiter illegal. arbiter=%d\n", 
										portArgs.arbiter));
							break;
					}
				}
				else {
					// Unit number is invalid.
					//Ddim_Print(("mxic_level_port_set_levelport_port(): unit number is invalid. unit=%d\n", unit));
				}
			}
			else {
				// master number is illegal.
				result = MxicUtlis_INPUT_PARAM_ERROR;
				Ddim_Print(("E:mxic_level_port_set_levelport_port(): master number illegal. arbiter=%d\n", 
							portArgs.arbiter));
			}
		}

		if ( regReadSw == MxicUtlis_ON ) {
			ioMxic->TRVSW.bit.TRVSW = MxicUtlis_ON;
		}

		mxic_utlis_off_pclk( priv->mxicUtlis, portArgs.unit );

		MxicUtlis_DSB();
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:mxic_level_port_set_levelport_port(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

/**
This function get the LevelPort(Port).<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		wrArbiter				Target write or read Arbiter.<br>
										Please refer to @ref ImMxicWrArbiter for a set value.<br>
@param[in]		arbiter					Target arbiter.<br>
										Please refer to @ref ImMxicSpecArbiter for a set value.<br>
@param[in]		master					Master number.<br>
@param[out]		port					Target Port.<br>
										Please refer to @ref ImMxicPort for a set value.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32 mxic_level_port_get_levelport_port( MxicLevelPort *self, LevelPortArgs portArgs, 
											UCHAR master, ImMxicPort* const port )
{
	UCHAR						regReadSw;
	INT32						result;
	volatile struct io_jdsmxic*	ioMxic;
	MxicLevelPortPrivate *priv = MXIC_LEVEL_PORT_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( imMxicCheckArbiter( portArgs.wrArbiter, portArgs.arbiter ) != D_DDIM_OK ) {
		// arbiter parameter is illegal.
		Ddim_Assertion(("E:mxic_level_port_get_levelport_port(): imMxicCheckArbiter error.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
	if ( port == NULL ) {
		// port parameter is NULL.
		Ddim_Assertion(("E:mxic_level_port_get_levelport_port(): port is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, portArgs.unit, &ioMxic );

	if ( result == D_DDIM_OK ) {

		mxic_utlis_on_pclk( priv->mxicUtlis, portArgs.unit );

		regReadSw = ioMxic->TRVSW.bit.TRVSW;

		if ( regReadSw == MxicUtlis_ON ) {
			ioMxic->TRVSW.bit.TRVSW = MxicUtlis_OFF;
		}

		if ( portArgs.wrArbiter == MxicUtlis_WR_ARBITER_W ) {

			if ( master < MxicUtlis_MASTER_NUMBER_MAX ) {

				if ( portArgs.unit != MxicUtlis_UNIT_4 ) {
					// Write arbiter.
					switch ( portArgs.arbiter ) {
						case MxicUtlis_SPEC_ARBITER_1:
							*port = (ImMxicPort)ioMxic->TMARLP_W_1[(master - 1)].bit.MAS_PORT_W;
							break;
						case MxicUtlis_SPEC_ARBITER_2:
							*port = (ImMxicPort)ioMxic->TMARLP_W_2[(master - 1)].bit.MAS_PORT_W;
							break;
						case MxicUtlis_SPEC_ARBITER_3:
							*port = (ImMxicPort)ioMxic->TMARLP_W_3[(master - 1)].bit.MAS_PORT_W;
							break;
						case MxicUtlis_SPEC_ARBITER_4:
							*port = (ImMxicPort)ioMxic->TMARLP_W_4[(master - 1)].bit.MAS_PORT_W;
							break;
						default:
							// arbiter parameter is illegal.
							result = MxicUtlis_INPUT_PARAM_ERROR;
							Ddim_Print(("E:mxic_level_port_get_levelport_port(): arbiter illegal. arbiter=%d\n", 
										portArgs.arbiter));
							break;
					}
				}
				else {
					// Unit number is invalid.
					//Ddim_Print(("mxic_level_port_get_levelport_port(): unit number is invalid. unit=%d\n", unit));
				}
			}
			else {
				// master number is illegal.
				result = MxicUtlis_INPUT_PARAM_ERROR;
				Ddim_Print(("E:mxic_level_port_get_levelport_port(): master number illegal. arbiter=%d\n", 
							portArgs.arbiter));
			}
		}
		else {
			if ( master < MxicUtlis_MASTER_NUMBER_MAX ) {

				if ( portArgs.unit != MxicUtlis_UNIT_0 ) {
					// Read arbiter.
					switch ( portArgs.arbiter ) {
						case MxicUtlis_SPEC_ARBITER_1:
							*port = (ImMxicPort)ioMxic->TMARLP_R_1[(master - 1)].bit.MAS_PORT_R;
							break;
						case MxicUtlis_SPEC_ARBITER_2:
							*port = (ImMxicPort)ioMxic->TMARLP_R_2[(master - 1)].bit.MAS_PORT_R;
							break;
						case MxicUtlis_SPEC_ARBITER_3:
							*port = (ImMxicPort)ioMxic->TMARLP_R_3[(master - 1)].bit.MAS_PORT_R;
							break;
						case MxicUtlis_SPEC_ARBITER_4:
							*port = (ImMxicPort)ioMxic->TMARLP_R_4[(master - 1)].bit.MAS_PORT_R;
							break;
						default:
							// arbiter parameter is illegal.
							result = MxicUtlis_INPUT_PARAM_ERROR;
							Ddim_Print(("E:mxic_level_port_get_levelport_port(): arbiter illegal. arbiter=%d\n", 
										portArgs.arbiter));
							break;
					}
				}
				else {
					// Unit number is invalid.
//					Ddim_Print(("mxic_level_port_get_levelport_port(): unit number is invalid. unit=%d\n", unit));
				}
			}
			else {
				// master number is illegal.
				result = MxicUtlis_INPUT_PARAM_ERROR;
				Ddim_Print(("E:mxic_level_port_get_levelport_port(): master number illegal. arbiter=%d\n", 
							portArgs.arbiter));
			}
		}

		if ( regReadSw == MxicUtlis_ON ) {
			ioMxic->TRVSW.bit.TRVSW = MxicUtlis_ON;
		}

		mxic_utlis_off_pclk( priv->mxicUtlis, portArgs.unit );
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:mxic_level_port_get_levelport_port(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

/**
This function set the LevelPort(Level).<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		wrArbiter				Target write or read Arbiter.<br>
										Please refer to @ref ImMxicWrArbiter for a set value.<br>
@param[in]		arbiter					Target arbiter.<br>
										Please refer to @ref ImMxicSpecArbiter for a set value.<br>
@param[in]		master					Master number.<br>
@param[in]		level					Target Level.<br>
										Please refer to @ref ImMxicLevel for a set value.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32 mxic_level_port_set_levelport_level( MxicLevelPort *self, LevelPortArgs levelArgs, 
											UCHAR master, ImMxicLevel level )
{
	UCHAR						regReadSw;
	INT32						result;
	volatile struct io_jdsmxic*	ioMxic;
	MxicLevelPortPrivate *priv = MXIC_LEVEL_PORT_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( imMxicCheckLevel( levelArgs.wrArbiter, levelArgs.arbiter, level ) != D_DDIM_OK ) {
		// arbiter or port parameter is illegal.
		Ddim_Assertion(("E:mxic_level_port_set_levelport_level(): imMxicCheckLevel error.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, levelArgs.unit, &ioMxic );

	if ( result == D_DDIM_OK ) {

		mxic_utlis_on_pclk( priv->mxicUtlis, levelArgs.unit );

		regReadSw = ioMxic->TRVSW.bit.TRVSW;

		if ( regReadSw == MxicUtlis_ON ) {
			ioMxic->TRVSW.bit.TRVSW = MxicUtlis_OFF;
		}

		if ( levelArgs.wrArbiter == MxicUtlis_WR_ARBITER_W ) {

			if ( master < MxicUtlis_MASTER_NUMBER_MAX ) {

				if ( levelArgs.unit != MxicUtlis_UNIT_4 ) {
					// Write arbiter.
					switch ( levelArgs.arbiter ) {
						case MxicUtlis_SPEC_ARBITER_1:
							ioMxic->TMARLP_W_1[(master - 1)].bit.MAS_LEVEL_W = level;
							break;
						case MxicUtlis_SPEC_ARBITER_2:
							ioMxic->TMARLP_W_2[(master - 1)].bit.MAS_LEVEL_W = level;
							break;
						case MxicUtlis_SPEC_ARBITER_3:
							ioMxic->TMARLP_W_3[(master - 1)].bit.MAS_LEVEL_W = level;
							break;
						case MxicUtlis_SPEC_ARBITER_4:
							ioMxic->TMARLP_W_4[(master - 1)].bit.MAS_LEVEL_W = level;
							break;
						default:
							// arbiter parameter is illegal.
							result = MxicUtlis_INPUT_PARAM_ERROR;
							Ddim_Print(("E:mxic_level_port_set_levelport_level(): arbiter illegal. arbiter=%d\n", 
										levelArgs.arbiter));
							break;
					}
				}
				else {
					// Unit number is invalid.
//					Ddim_Print(("mxic_level_port_set_levelport_level(): unit number is invalid. unit=%d\n", unit));
				}
			}
			else {
				// master number is illegal.
				result = MxicUtlis_INPUT_PARAM_ERROR;
				Ddim_Print(("E:mxic_level_port_set_levelport_level(): master number illegal. arbiter=%d\n", 
							levelArgs.arbiter));
			}
		}
		else {
			if ( master < MxicUtlis_MASTER_NUMBER_MAX ) {

				if ( levelArgs.unit != MxicUtlis_UNIT_0 ) {
					// Read arbiter.
					switch ( levelArgs.arbiter ) {
						case MxicUtlis_SPEC_ARBITER_1:
							ioMxic->TMARLP_R_1[(master - 1)].bit.MAS_LEVEL_R = level;
							break;
						case MxicUtlis_SPEC_ARBITER_2:
							ioMxic->TMARLP_R_2[(master - 1)].bit.MAS_LEVEL_R = level;
							break;
						case MxicUtlis_SPEC_ARBITER_3:
							ioMxic->TMARLP_R_3[(master - 1)].bit.MAS_LEVEL_R = level;
							break;
						case MxicUtlis_SPEC_ARBITER_4:
							ioMxic->TMARLP_R_4[(master - 1)].bit.MAS_LEVEL_R = level;
							break;
						default:
							// arbiter parameter is illegal.
							result = MxicUtlis_INPUT_PARAM_ERROR;
							Ddim_Print(("E:mxic_level_port_set_levelport_level(): arbiter illegal. arbiter=%d\n", 
										levelArgs.arbiter));
							break;
					}
				}
				else {
					// Unit number is invalid.
//					Ddim_Print(("mxic_level_port_set_levelport_level(): unit number is invalid. unit=%d\n", unit));
				}
			}
			else {
				// master number is illegal.
				result = MxicUtlis_INPUT_PARAM_ERROR;
				Ddim_Print(("E:mxic_level_port_set_levelport_level(): master number illegal. arbiter=%d\n", 
							levelArgs.arbiter));
			}
		}

		if ( regReadSw == MxicUtlis_ON ) {
			ioMxic->TRVSW.bit.TRVSW = MxicUtlis_ON;
		}

		mxic_utlis_off_pclk( priv->mxicUtlis, levelArgs.unit );

		MxicUtlis_DSB();
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:mxic_level_port_set_levelport_level(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

/**
This function get the LevelPort(Level).<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		wrArbiter				Target write or read Arbiter.<br>
										Please refer to @ref ImMxicWrArbiter for a set value.<br>
@param[in]		arbiter					Target arbiter.<br>
										Please refer to @ref ImMxicSpecArbiter for a set value.<br>
@param[in]		master					Master number.<br>
@param[out]		level					Target Level.<br>
										Please refer to @ref ImMxicLevel for a set value.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32 mxic_level_port_get_levelport_level( MxicLevelPort *self, LevelPortArgs levelArgs, 
											UCHAR master, ImMxicLevel* const level )
{
	UCHAR						regReadSw;
	INT32						result;
	volatile struct io_jdsmxic*	ioMxic;
	MxicLevelPortPrivate *priv = MXIC_LEVEL_PORT_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( imMxicCheckArbiter( levelArgs.wrArbiter, levelArgs.arbiter ) != D_DDIM_OK ) {
		// arbiter parameter is illegal.
		Ddim_Assertion(("E:mxic_level_port_get_levelport_level(): imMxicCheckArbiter error.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
	if ( level == NULL ) {
		// level parameter is NULL.
		Ddim_Assertion(("E:mxic_level_port_get_levelport_level(): level is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, levelArgs.unit, &ioMxic );

	if ( result == D_DDIM_OK ) {

		mxic_utlis_on_pclk( priv->mxicUtlis, levelArgs.unit );

		regReadSw = ioMxic->TRVSW.bit.TRVSW;

		if ( regReadSw == MxicUtlis_ON ) {
			ioMxic->TRVSW.bit.TRVSW = MxicUtlis_OFF;
		}

		if ( levelArgs.wrArbiter == MxicUtlis_WR_ARBITER_W ) {

			if ( master < MxicUtlis_MASTER_NUMBER_MAX ) {

				if ( levelArgs.unit != MxicUtlis_UNIT_4 ) {
					// Write arbiter.
					switch ( levelArgs.arbiter ) {
						case MxicUtlis_SPEC_ARBITER_1:
							*level = (ImMxicLevel)ioMxic->TMARLP_W_1[(master - 1)].bit.MAS_LEVEL_W;
							break;
						case MxicUtlis_SPEC_ARBITER_2:
							*level = (ImMxicLevel)ioMxic->TMARLP_W_2[(master - 1)].bit.MAS_LEVEL_W;
							break;
						case MxicUtlis_SPEC_ARBITER_3:
							*level = (ImMxicLevel)ioMxic->TMARLP_W_3[(master - 1)].bit.MAS_LEVEL_W;
							break;
						case MxicUtlis_SPEC_ARBITER_4:
							*level = (ImMxicLevel)ioMxic->TMARLP_W_4[(master - 1)].bit.MAS_LEVEL_W;
							break;
						default:
							// arbiter parameter is illegal.
							result = MxicUtlis_INPUT_PARAM_ERROR;
							Ddim_Print(("E:mxic_level_port_get_levelport_level(): arbiter illegal. arbiter=%d\n", 
										levelArgs.arbiter));
							break;
					}
				}
				else {
					// Unit number is invalid.
//					Ddim_Print(("mxic_level_port_get_levelport_level(): unit number is invalid. unit=%d\n", unit));
				}
			}
			else {
				// master number is illegal.
				result = MxicUtlis_INPUT_PARAM_ERROR;
				Ddim_Print(("E:mxic_level_port_get_levelport_level(): master number illegal. arbiter=%d\n", 
							levelArgs.arbiter));
			}
		}
		else {
			if ( master < MxicUtlis_MASTER_NUMBER_MAX ) {

				if ( levelArgs.unit != MxicUtlis_UNIT_0 ) {
					// Read arbiter.
					switch ( levelArgs.arbiter ) {
						case MxicUtlis_SPEC_ARBITER_1:
							*level = (ImMxicLevel)ioMxic->TMARLP_R_1[(master - 1)].bit.MAS_LEVEL_R;
							break;
						case MxicUtlis_SPEC_ARBITER_2:
							*level = (ImMxicLevel)ioMxic->TMARLP_R_2[(master - 1)].bit.MAS_LEVEL_R;
							break;
						case MxicUtlis_SPEC_ARBITER_3:
							*level = (ImMxicLevel)ioMxic->TMARLP_R_3[(master - 1)].bit.MAS_LEVEL_R;
							break;
						case MxicUtlis_SPEC_ARBITER_4:
							*level = (ImMxicLevel)ioMxic->TMARLP_R_4[(master - 1)].bit.MAS_LEVEL_R;
							break;
						default:
							// arbiter parameter is illegal.
							result = MxicUtlis_INPUT_PARAM_ERROR;
							Ddim_Print(("E:mxic_level_port_get_levelport_level(): arbiter illegal. arbiter=%d\n", 
										levelArgs.arbiter));
							break;
					}
				}
				else {
					// Unit number is invalid.
//					Ddim_Print(("mxic_level_port_get_levelport_level(): unit number is invalid. unit=%d\n", unit));
				}
			}
			else {
				// master number is illegal.
				result = MxicUtlis_INPUT_PARAM_ERROR;
				Ddim_Print(("E:mxic_level_port_get_levelport_level(): master number illegal. arbiter=%d\n", 
							levelArgs.arbiter));
			}
		}

		if ( regReadSw == MxicUtlis_ON ) {
			ioMxic->TRVSW.bit.TRVSW = MxicUtlis_ON;
		}

		mxic_utlis_off_pclk( priv->mxicUtlis, levelArgs.unit );
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:mxic_level_port_get_levelport_level(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

/**
This function set the LevelPort(All).<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		allLevelport			All LevelPort information.<br>
										Please refer to @ref ImMxicAllLevelport.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32 mxic_level_port_set_levelport_all( MxicLevelPort *self, ImMxicUnit unit, ImMxicAllLevelport* allLevelport )
{
	UCHAR						regReadSw;
	INT32						result;
	INT32						i, j;
	volatile struct io_jdsmxic*	ioMxic;
	MxicLevelPortPrivate *priv = MXIC_LEVEL_PORT_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( allLevelport == NULL ) {
		// allLevelport parameter is NULL.
		Ddim_Assertion(("E:Im_MXIC_Set_LevelPort_All(): allLevelport is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {

		mxic_utlis_on_pclk( priv->mxicUtlis, unit );

		regReadSw = ioMxic->TRVSW.bit.TRVSW;

		if ( regReadSw == MxicUtlis_ON ) {
			ioMxic->TRVSW.bit.TRVSW = MxicUtlis_OFF;
		}

		if ( unit != MxicUtlis_UNIT_4 ) {

			// Write arbiter.
			for ( i = MxicUtlis_W_ARBITER_W1; i < MxicUtlis_W_ARBITER_MAX; i++ ) {

				for ( j = 0; j < MxicUtlis_MASTER_NUMBER_MAX-1; j++ ) {

					switch ( i ) {
						case MxicUtlis_SPEC_ARBITER_1:
							ioMxic->TMARLP_W_1[ j ].bit.MAS_PORT_W		= allLevelport->wArbiter[ i ].port[ j ];
							ioMxic->TMARLP_W_1[ j ].bit.MAS_LEVEL_W	= allLevelport->wArbiter[ i ].level[ j ];
							break;
						case MxicUtlis_SPEC_ARBITER_2:
							ioMxic->TMARLP_W_2[ j ].bit.MAS_PORT_W		= allLevelport->wArbiter[ i ].port[ j ];
							ioMxic->TMARLP_W_2[ j ].bit.MAS_LEVEL_W	= allLevelport->wArbiter[ i ].level[ j ];
							break;
						case MxicUtlis_SPEC_ARBITER_3:
							ioMxic->TMARLP_W_3[ j ].bit.MAS_PORT_W		= allLevelport->wArbiter[ i ].port[ j ];
							ioMxic->TMARLP_W_3[ j ].bit.MAS_LEVEL_W	= allLevelport->wArbiter[ i ].level[ j ];
							break;
						case MxicUtlis_SPEC_ARBITER_4:
							ioMxic->TMARLP_W_4[ j ].bit.MAS_PORT_W		= allLevelport->wArbiter[ i ].port[ j ];
							ioMxic->TMARLP_W_4[ j ].bit.MAS_LEVEL_W	= allLevelport->wArbiter[ i ].level[ j ];
							break;
						default:
							// arbiter parameter is illegal.
							result = MxicUtlis_INPUT_PARAM_ERROR;
							Ddim_Print(("E:Im_MXIC_Set_LevelPort_All(): write arbiter illegal. arbiter=%d\n", i));
							break;
					}
				}
			}
		}
		else {
			// Unit number is invalid.
//			Ddim_Print(("Im_MXIC_Set_LevelPort_All(): unit number is invalid. unit=%d\n", unit));
		}

		if ( unit != MxicUtlis_UNIT_0 ) {

			// Read arbiter.
			for ( i = MxicUtlis_R_ARBITER_R1; i < MxicUtlis_R_ARBITER_MAX; i++ ) {

				for ( j = 0; j < MxicUtlis_MASTER_NUMBER_MAX-1; j++ ) {

					switch ( i ) {
						case MxicUtlis_SPEC_ARBITER_1:
							ioMxic->TMARLP_R_1[ j ].bit.MAS_PORT_R		= allLevelport->rArbiter[ i ].port[ j ];
							ioMxic->TMARLP_R_1[ j ].bit.MAS_LEVEL_R	= allLevelport->rArbiter[ i ].level[ j ];
							break;
						case MxicUtlis_SPEC_ARBITER_2:
							ioMxic->TMARLP_R_2[ j ].bit.MAS_PORT_R		= allLevelport->rArbiter[ i ].port[ j ];
							ioMxic->TMARLP_R_2[ j ].bit.MAS_LEVEL_R	= allLevelport->rArbiter[ i ].level[ j ];
							break;
						case MxicUtlis_SPEC_ARBITER_3:
							ioMxic->TMARLP_R_3[ j ].bit.MAS_PORT_R		= allLevelport->rArbiter[ i ].port[ j ];
							ioMxic->TMARLP_R_3[ j ].bit.MAS_LEVEL_R	= allLevelport->rArbiter[ i ].level[ j ];
							break;
						case MxicUtlis_SPEC_ARBITER_4:
							ioMxic->TMARLP_R_4[ j ].bit.MAS_PORT_R		= allLevelport->rArbiter[ i ].port[ j ];
							ioMxic->TMARLP_R_4[ j ].bit.MAS_LEVEL_R	= allLevelport->rArbiter[ i ].level[ j ];
							break;
						default:
							// arbiter parameter is illegal.
							result = MxicUtlis_INPUT_PARAM_ERROR;
							Ddim_Print(("E:Im_MXIC_Set_LevelPort_All(): read arbiter illegal. arbiter=%d\n", i));
							break;
					}
				}
			}
		}
		else {
			// Unit number is invalid.
//			Ddim_Print(("Im_MXIC_Set_LevelPort_All(): unit number is invalid. unit=%d\n", unit));
		}

		if ( regReadSw == MxicUtlis_ON ) {
			ioMxic->TRVSW.bit.TRVSW = MxicUtlis_ON;
		}

		mxic_utlis_off_pclk( priv->mxicUtlis, unit );

		MxicUtlis_DSB();
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:Im_MXIC_Set_LevelPort_All(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

/**
This function get the LevelPort(All).<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[out]		allLevelport			All LevelPort information.<br>
										Please refer to @ref ImMxicAllLevelport.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32 mxic_level_port_get_levelport_all( MxicLevelPort *self, ImMxicUnit unit, ImMxicAllLevelport* allLevelport )
{
	UCHAR						regReadSw;
	INT32						result;
	INT32						i, j;
	volatile struct io_jdsmxic*	ioMxic;
	MxicLevelPortPrivate *priv = MXIC_LEVEL_PORT_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ( allLevelport == NULL ) {
		// allLevelport parameter is NULL.
		Ddim_Assertion(("E:mxic_level_port_get_levelport_all(): allLevelport is NULL.\n"));
		return MxicUtlis_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	result = mxic_utlis_get_unit_address( priv->mxicUtlis, unit, &ioMxic );

	if ( result == D_DDIM_OK ) {

		mxic_utlis_on_pclk( priv->mxicUtlis, unit );

		regReadSw = ioMxic->TRVSW.bit.TRVSW;

		if ( regReadSw == MxicUtlis_ON ) {
			ioMxic->TRVSW.bit.TRVSW = MxicUtlis_OFF;
		}

		if ( unit != MxicUtlis_UNIT_4 ) {

			// Write arbiter.
			for ( i = MxicUtlis_W_ARBITER_W1; i < MxicUtlis_W_ARBITER_MAX; i++ ) {

				for ( j = 0; j < MxicUtlis_MASTER_NUMBER_MAX-1; j++ ) {

					switch ( i ) {
						case MxicUtlis_SPEC_ARBITER_1:
							allLevelport->wArbiter[ i ].port[ j ]		= (ImMxicPort)ioMxic->TMARLP_W_1[ j ].bit.MAS_PORT_W;
							allLevelport->wArbiter[ i ].level[ j ]	= (ImMxicLevel)ioMxic->TMARLP_W_1[ j ].bit.MAS_LEVEL_W;
							break;
						case MxicUtlis_SPEC_ARBITER_2:
							allLevelport->wArbiter[ i ].port[ j ]		= (ImMxicPort)ioMxic->TMARLP_W_2[ j ].bit.MAS_PORT_W;
							allLevelport->wArbiter[ i ].level[ j ]	= (ImMxicLevel)ioMxic->TMARLP_W_2[ j ].bit.MAS_LEVEL_W;
							break;
						case MxicUtlis_SPEC_ARBITER_3:
							allLevelport->wArbiter[ i ].port[ j ]		= (ImMxicPort)ioMxic->TMARLP_W_3[ j ].bit.MAS_PORT_W;
							allLevelport->wArbiter[ i ].level[ j ]	= (ImMxicLevel)ioMxic->TMARLP_W_3[ j ].bit.MAS_LEVEL_W;
							break;
						case MxicUtlis_SPEC_ARBITER_4:
							allLevelport->wArbiter[ i ].port[ j ]		= (ImMxicPort)ioMxic->TMARLP_W_4[ j ].bit.MAS_PORT_W;
							allLevelport->wArbiter[ i ].level[ j ]	= (ImMxicLevel)ioMxic->TMARLP_W_4[ j ].bit.MAS_LEVEL_W;
							break;
						default:
							// arbiter parameter is illegal.
							result = MxicUtlis_INPUT_PARAM_ERROR;
							Ddim_Print(("E:mxic_level_port_get_levelport_all(): write arbiter illegal. arbiter=%d\n", i));
							break;
					}
				}
			}
		}
		else {
			// Unit number is invalid.
//			Ddim_Print(("mxic_level_port_get_levelport_all(): unit number is invalid. unit=%d\n", unit));
		}

		if ( unit != MxicUtlis_UNIT_0 ) {

			// Read arbiter.
			for ( i = MxicUtlis_R_ARBITER_R1; i < MxicUtlis_R_ARBITER_MAX; i++ ) {

				for ( j = 0; j < MxicUtlis_MASTER_NUMBER_MAX-1; j++ ) {

					switch ( i ) {
						case MxicUtlis_SPEC_ARBITER_1:
							allLevelport->rArbiter[ i ].port[ j ]		= (ImMxicPort)ioMxic->TMARLP_R_1[ j ].bit.MAS_PORT_R;
							allLevelport->rArbiter[ i ].level[ j ]	= (ImMxicLevel)ioMxic->TMARLP_R_1[ j ].bit.MAS_LEVEL_R;
							break;
						case MxicUtlis_SPEC_ARBITER_2:
							allLevelport->rArbiter[ i ].port[ j ]		= (ImMxicPort)ioMxic->TMARLP_R_2[ j ].bit.MAS_PORT_R;
							allLevelport->rArbiter[ i ].level[ j ]	= (ImMxicLevel)ioMxic->TMARLP_R_2[ j ].bit.MAS_LEVEL_R;
							break;
						case MxicUtlis_SPEC_ARBITER_3:
							allLevelport->rArbiter[ i ].port[ j ]		= (ImMxicPort)ioMxic->TMARLP_R_3[ j ].bit.MAS_PORT_R;
							allLevelport->rArbiter[ i ].level[ j ]	= (ImMxicLevel)ioMxic->TMARLP_R_3[ j ].bit.MAS_LEVEL_R;
							break;
						case MxicUtlis_SPEC_ARBITER_4:
							allLevelport->rArbiter[ i ].port[ j ]		= (ImMxicPort)ioMxic->TMARLP_R_4[ j ].bit.MAS_PORT_R;
							allLevelport->rArbiter[ i ].level[ j ]	= (ImMxicLevel)ioMxic->TMARLP_R_4[ j ].bit.MAS_LEVEL_R;
							break;
						default:
							// arbiter parameter is illegal.
							result = MxicUtlis_INPUT_PARAM_ERROR;
							Ddim_Print(("E:mxic_level_port_get_levelport_all(): read arbiter illegal. arbiter=%d\n", i));
							break;
					}
				}
			}
		}
		else {
			// Unit number is invalid.
//			Ddim_Print(("mxic_level_port_get_levelport_all(): unit number is invalid. unit=%d\n", unit));
		}

		if ( regReadSw == MxicUtlis_ON ) {
			ioMxic->TRVSW.bit.TRVSW = MxicUtlis_ON;
		}

		mxic_utlis_off_pclk( priv->mxicUtlis, unit );

		MxicUtlis_DSB();
	}
	else {
		// Input parameter error.
		Ddim_Print(("E:mxic_level_port_get_levelport_all(): mxic_utlis_get_unit_address error.\n"));
	}

	return result;
}

MxicLevelPort *mxic_level_port_new(void)
{
    MxicLevelPort* self = k_object_new_with_private(MXIC_TYPE_LEVEL_PORT, sizeof(MxicLevelPortPrivate));
    return self;
}
