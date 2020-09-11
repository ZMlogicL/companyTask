/**
 * @file		ct_dd_pwm.h
 * @brief		This is ct header for dd_pwm.c
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */

#ifndef _CT_DD_PWM_H_
#define _CT_DD_PWM_H_

#include "../src/ctddpwm.h"
#include "../src/ctddpwmmain.h"

static inline	VOID Ct_Dd_PWM_Main( int argc, char** argv )
{
	CtDdPwmMain* self = ct_dd_pwm_main_new();
	ct_dd_pwm_main_test(self, argc, argv);
	k_object_unref(self);
	self = NULL;
}

/*#include "driver_common.h"

----------------------------------------------------------------------
 Definition
----------------------------------------------------------------------

----------------------------------------------------------------------
 Enumeration
----------------------------------------------------------------------
 Nothing Special

----------------------------------------------------------------------
 Structure
----------------------------------------------------------------------
 Nothing Special

----------------------------------------------------------------------
 Function Prototype Definition
----------------------------------------------------------------------
VOID Ct_Dd_PWM_Main( int argc, char** argv );*/

#endif	// _CT_DD_PWM_H_
