/*
*@Copyright (c1) 2010-2020 上海网用软件有限公司
*@date:		 2020-9-7 (发布日期)
*@author:	 余林瑞
*@brief:
*@function:参照ETK代码规范，写一个模板类。
*设计的主要功能:
*1、命名规范
*2、类中各模块的布局规范
*3、常量枚举函数等声明及定义顺序
*@version: 1.0.0 实现一个模板类
*
*/


#include <stdio.h>
#include "dd_arm.h"
#include "driver_common.h"
#include "ddim_user_custom.h"
#if 1    // special key control
#include "pmc.h"
#include <string.h>
#endif
#include "ddtop.h"


G_DEFINE_TYPE(DdTop, dd_top, G_TYPE_OBJECT);
#define DD_TOP_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), DD_TYPE_TOP, DdTopPrivate));


struct _DdTopPrivate{

};


/*DECLS*/
static void 					dispose_od(GObject  *object);
static void 					finalize_od(GObject  *object);


/*IMPL*/
static void dd_top_class_init(DdTopClass *klass)
{
	g_type_class_add_private(klass, sizeof(DdTopPrivate));
}

static void dd_top_init(DdTop *self)
{
	DdTopPrivate *priv = DD_TOP_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
	DdTopPrivate *self = DD_TOP_GET_PRIVATE(object);
}

static void finalize_od(GObject *object)
{
	DdTopPrivate *self = DD_TOP_GET_PRIVATE(object);
}

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/


/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
ULONG gDD_Top_Spin_Lock __attribute__((section(".LOCK_SECTION"), aligned(64)));

/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/


/*----------------------------------------------------------------------*/
/* Local Method Definition												*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Global Function														*/
/*----------------------------------------------------------------------*/


/*PUBLIC*/

/**
Set the Pull-up/down enable state of a selectable GPIO port.<br>
It is set to the PUDER(Pull-up/down Enable Register) value.
@param [in]  port		Port name. See @ref DdTop_GPIO_PORT
@param [in]  enable		Pull-up/down enable state.
						  <ul>
							  <li>0:@ref DdToptwo_GPIO_PUD_OFF
							  <li>1:@ref DdToptwo_GPIO_PUD_ON
						  </ul>
@retval D_DDIM_OK					Success.
@retval DdTopone_INPUT_PARAM_ERROR	Error occurred.
*/
INT32 dd_top_set_gpio_pull_up_down_enable(DdTop *self, DdTop_GPIO_PORT port, UCHAR enable)
{
#ifdef DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL
	INT32 s;
#endif // DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL

#ifdef CO_PARAM_CHECK
	if (port >= DdTop_GPIO_PORT_MAX) {
		Ddim_Assertion(("dd_top_set_gpio_pull_up_down_enable() error. port parameters is abnormal.\n"));
		return DdTopone_INPUT_PARAM_ERROR;
	}
	if (enable > DdToptwo_GPIO_PUD_ON) {
		Ddim_Assertion(("dd_top_set_gpio_pull_up_down_enable() error. enable parameters is abnormal.\n"));
		return DdTopone_INPUT_PARAM_ERROR;
	}
#endif

	DdToptwo_START_GPIO_CLK_WITH_CS();

	switch( port ) {
		case DdTop_GPIO_P80: IO_CHIPTOP.PUDER.bit.P80 = enable; break;
		case DdTop_GPIO_P81: IO_CHIPTOP.PUDER.bit.P81 = enable; break;
		case DdTop_GPIO_P82: IO_CHIPTOP.PUDER.bit.P82 = enable; break;
		case DdTop_GPIO_P83: IO_CHIPTOP.PUDER.bit.P83 = enable; break;
		case DdTop_GPIO_P86: IO_CHIPTOP.PUDER.bit.P86 = enable; break;
		case DdTop_GPIO_P87: IO_CHIPTOP.PUDER.bit.P87 = enable; break;
		case DdTop_GPIO_P90: IO_CHIPTOP.PUDER.bit.P90 = enable; break;
		case DdTop_GPIO_P91: IO_CHIPTOP.PUDER.bit.P91 = enable; break;
		case DdTop_GPIO_P92: IO_CHIPTOP.PUDER.bit.P92 = enable; break;
		case DdTop_GPIO_P93: IO_CHIPTOP.PUDER.bit.P93 = enable; break;
		case DdTop_GPIO_PA0: IO_CHIPTOP.PUDER.bit.PA0 = enable; break;
		case DdTop_GPIO_PA1: IO_CHIPTOP.PUDER.bit.PA1 = enable; break;
		case DdTop_GPIO_PA2: IO_CHIPTOP.PUDER.bit.PA2 = enable; break;
		case DdTop_GPIO_PA3: IO_CHIPTOP.PUDER.bit.PA3 = enable; break;
		case DdTop_GPIO_PA4: IO_CHIPTOP.PUDER.bit.PA4 = enable; break;
		case DdTop_GPIO_PA5: IO_CHIPTOP.PUDER.bit.PA5 = enable; break;
		case DdTop_GPIO_PA6: IO_CHIPTOP.PUDER.bit.PA6 = enable; break;
		case DdTop_GPIO_PA7: IO_CHIPTOP.PUDER.bit.PA7 = enable; break;
		case DdTop_GPIO_PB0: IO_CHIPTOP.PUDER.bit.PB0 = enable; break;
		case DdTop_GPIO_PB1: IO_CHIPTOP.PUDER.bit.PB1 = enable; break;
		case DdTop_GPIO_PB2: IO_CHIPTOP.PUDER.bit.PB2 = enable; break;
		case DdTop_GPIO_PB3: IO_CHIPTOP.PUDER.bit.PB3 = enable; break;
		case DdTop_GPIO_PB4: IO_CHIPTOP.PUDER.bit.PB4 = enable; break;
		case DdTop_GPIO_PD0: IO_CHIPTOP.PUDER.bit.PD0 = enable; break;
		case DdTop_GPIO_PD1: IO_CHIPTOP.PUDER.bit.PD1 = enable; break;
		case DdTop_GPIO_PD2: IO_CHIPTOP.PUDER.bit.PD2 = enable; break;
		case DdTop_GPIO_PD3: IO_CHIPTOP.PUDER.bit.PD3 = enable; break;
		case DdTop_GPIO_PD4: IO_CHIPTOP.PUDER.bit.PD4 = enable; break;
		case DdTop_GPIO_PD5: IO_CHIPTOP.PUDER.bit.PD5 = enable; break;
		case DdTop_GPIO_PD6: IO_CHIPTOP.PUDER.bit.PD6 = enable; break;
		case DdTop_GPIO_PE0: IO_CHIPTOP.PUDER.bit.PE0 = enable; break;
		case DdTop_GPIO_PE1: IO_CHIPTOP.PUDER.bit.PE1 = enable; break;
		case DdTop_GPIO_PF2: IO_CHIPTOP.PUDER.bit.PF2 = enable; break;
		case DdTop_GPIO_PF3: IO_CHIPTOP.PUDER.bit.PF3 = enable; break;
		case DdTop_GPIO_PF4: IO_CHIPTOP.PUDER.bit.PF4 = enable; break;
		case DdTop_GPIO_PG0: IO_CHIPTOP.PUDER.bit.PG0 = enable; break;
		case DdTop_GPIO_PG1: IO_CHIPTOP.PUDER.bit.PG1 = enable; break;
		case DdTop_GPIO_PG2: IO_CHIPTOP.PUDER.bit.PG2 = enable; break;
		case DdTop_GPIO_PG3: IO_CHIPTOP.PUDER.bit.PG3 = enable; break;
		case DdTop_GPIO_PG4: IO_CHIPTOP.PUDER.bit.PG4 = enable; break;
		case DdTop_GPIO_PG5: IO_CHIPTOP.PUDER.bit.PG5 = enable; break;
		case DdTop_GPIO_PG6: IO_CHIPTOP.PUDER.bit.PG6 = enable; break;
		case DdTop_GPIO_PG7: IO_CHIPTOP.PUDER.bit.PG7 = enable; break;
		case DdTop_GPIO_PH0: IO_CHIPTOP.PUDER.bit.PH0 = enable; break;
		case DdTop_GPIO_PH1: IO_CHIPTOP.PUDER.bit.PH1 = enable; break;
		case DdTop_GPIO_PH2: IO_CHIPTOP.PUDER.bit.PH2 = enable; break;
		case DdTop_GPIO_PH3: IO_CHIPTOP.PUDER.bit.PH3 = enable; break;
		case DdTop_GPIO_PW0: IO_CHIPTOP.PUDER.bit.PW0 = enable; break;
		case DdTop_GPIO_PW1: IO_CHIPTOP.PUDER.bit.PW1 = enable; break;
		case DdTop_GPIO_PW2: IO_CHIPTOP.PUDER.bit.PW2 = enable; break;
		case DdTop_GPIO_PW3: IO_CHIPTOP.PUDER.bit.PW3 = enable; break;
		case DdTop_GPIO_PW4: IO_CHIPTOP.PUDER.bit.PW4 = enable; break;
		case DdTop_GPIO_PW5: IO_CHIPTOP.PUDER.bit.PW5 = enable; break;
		case DdTop_GPIO_PW6: IO_CHIPTOP.PUDER.bit.PW6 = enable; break;
		case DdTop_GPIO_PW7: IO_CHIPTOP.PUDER.bit.PW7 = enable; break;
		case DdTop_GPIO_PJ0: IO_CHIPTOP.PUDER.bit.PJ0 = enable; break;
		case DdTop_GPIO_PJ1: IO_CHIPTOP.PUDER.bit.PJ1 = enable; break;
		case DdTop_GPIO_PJ2: IO_CHIPTOP.PUDER.bit.PJ2 = enable; break;
		case DdTop_GPIO_PJ3: IO_CHIPTOP.PUDER.bit.PJ3 = enable; break;
		case DdTop_GPIO_PJ4: IO_CHIPTOP.PUDER.bit.PJ4 = enable; break;
		case DdTop_GPIO_PJ5: IO_CHIPTOP.PUDER.bit.PJ5 = enable; break;
		case DdTop_GPIO_PJ6: IO_CHIPTOP.PUDER.bit.PJ6 = enable; break;
		case DdTop_GPIO_PJ7: IO_CHIPTOP.PUDER.bit.PJ7 = enable; break;
		case DdTop_GPIO_PK0: IO_CHIPTOP.PUDER.bit.PK0 = enable; break;
		case DdTop_GPIO_PK1: IO_CHIPTOP.PUDER.bit.PK1 = enable; break;
		case DdTop_GPIO_PK2: IO_CHIPTOP.PUDER.bit.PK2 = enable; break;
		case DdTop_GPIO_PK3: IO_CHIPTOP.PUDER.bit.PK3 = enable; break;
		case DdTop_GPIO_PK4: IO_CHIPTOP.PUDER.bit.PK4 = enable; break;
		case DdTop_GPIO_PK5: IO_CHIPTOP.PUDER.bit.PK5 = enable; break;
		case DdTop_GPIO_PK6: IO_CHIPTOP.PUDER.bit.PK6 = enable; break;
		case DdTop_GPIO_PK7: IO_CHIPTOP.PUDER.bit.PK7 = enable; break;
		case DdTop_GPIO_PL0: IO_CHIPTOP.PUDER.bit.PL0 = enable; break;
		case DdTop_GPIO_PL1: IO_CHIPTOP.PUDER.bit.PL1 = enable; break;
		case DdTop_GPIO_PL2: IO_CHIPTOP.PUDER.bit.PL2 = enable; break;
		case DdTop_GPIO_PL3: IO_CHIPTOP.PUDER.bit.PL3 = enable; break;
		case DdTop_GPIO_PL4: IO_CHIPTOP.PUDER.bit.PL4 = enable; break;
		case DdTop_GPIO_PL5: IO_CHIPTOP.PUDER.bit.PL5 = enable; break;
		case DdTop_GPIO_PM0: IO_CHIPTOP.PUDER.bit.PM0 = enable; break;
		case DdTop_GPIO_PM1: IO_CHIPTOP.PUDER.bit.PM1 = enable; break;
		case DdTop_GPIO_PM3: IO_CHIPTOP.PUDER.bit.PM3 = enable; break;
		case DdTop_GPIO_PM4: IO_CHIPTOP.PUDER.bit.PM4 = enable; break;
		case DdTop_GPIO_PN0: IO_CHIPTOP.PUDER.bit.PN0 = enable; break;
		case DdTop_GPIO_PN1: IO_CHIPTOP.PUDER.bit.PN1 = enable; break;
		case DdTop_GPIO_PN3: IO_CHIPTOP.PUDER.bit.PN3 = enable; break;
		case DdTop_GPIO_PN4: IO_CHIPTOP.PUDER.bit.PN4 = enable; break;
		case DdTop_GPIO_PY0: IO_CHIPTOP.PUDER.bit.PY0 = enable; break;
		case DdTop_GPIO_PY1: IO_CHIPTOP.PUDER.bit.PY1 = enable; break;
		case DdTop_GPIO_PY2: IO_CHIPTOP.PUDER.bit.PY2 = enable; break;
		case DdTop_GPIO_PY3: IO_CHIPTOP.PUDER.bit.PY3 = enable; break;
		case DdTop_GPIO_PY4: IO_CHIPTOP.PUDER.bit.PY4 = enable; break;
		case DdTop_GPIO_PY5: IO_CHIPTOP.PUDER.bit.PY5 = enable; break;
		case DdTop_GPIO_PY6: IO_CHIPTOP.PUDER.bit.PY6 = enable; break;
		case DdTop_GPIO_PY7: IO_CHIPTOP.PUDER.bit.PY7 = enable; break;
		case DdTop_GPIO_PP0: IO_CHIPTOP.PUDER.bit.PP0 = enable; break;
		case DdTop_GPIO_PP1: IO_CHIPTOP.PUDER.bit.PP1 = enable; break;
		case DdTop_GPIO_PP2: IO_CHIPTOP.PUDER.bit.PP2 = enable; break;
		case DdTop_GPIO_PP3: IO_CHIPTOP.PUDER.bit.PP3 = enable; break;
		default:
			DdToptwo_STOP_GPIO_CLK_WITH_CS();
			Ddim_Print(("dd_top_set_gpio_pull_up_down_enable() error. port not exist.\n"));
			return DdTopone_INPUT_PARAM_ERROR;
	}

	Dd_ARM_Dsb_Pou();
	DdToptwo_STOP_GPIO_CLK_WITH_CS();

	return D_DDIM_OK;
}

/**
Get the Pull-up/down enable state of a selectable GPIO port.<br>
It is get from the PUDER(Pull-up/down Enable Register) value.
@param [in]  port		Port name. See @ref DdTop_GPIO_PORT
@param [out] enable		Pull-up/down enable state.
						  <ul>
							  <li>0:@ref DdToptwo_GPIO_PUD_OFF
							  <li>1:@ref DdToptwo_GPIO_PUD_ON
						  </ul>
@retval D_DDIM_OK					Success.
@retval DdTopone_INPUT_PARAM_ERROR	Error occurred.
*/
INT32 dd_top_get_gpio_pull_up_down_enable(DdTop *self, DdTop_GPIO_PORT port, UCHAR* enable )
{
#ifdef DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL
	INT32 s;
#endif // DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL

#ifdef CO_PARAM_CHECK
	if (port >= DdTop_GPIO_PORT_MAX) {
		Ddim_Assertion(("dd_top_get_gpio_pull_up_down_enable() error. port parameters is abnormal.\n"));
		return DdTopone_INPUT_PARAM_ERROR;
	}
	if (enable == NULL) {
		Ddim_Assertion(("dd_top_get_gpio_pull_up_down_enable() error. enable parameters is abnormal.\n"));
		return DdTopone_INPUT_PARAM_ERROR;
	}
#endif

	DdToptwo_START_GPIO_CLK_WITH_CS();

	switch( port ) {
		case DdTop_GPIO_P80: *enable = IO_CHIPTOP.PUDER.bit.P80; break;
		case DdTop_GPIO_P81: *enable = IO_CHIPTOP.PUDER.bit.P81; break;
		case DdTop_GPIO_P82: *enable = IO_CHIPTOP.PUDER.bit.P82; break;
		case DdTop_GPIO_P83: *enable = IO_CHIPTOP.PUDER.bit.P83; break;
		case DdTop_GPIO_P86: *enable = IO_CHIPTOP.PUDER.bit.P86; break;
		case DdTop_GPIO_P87: *enable = IO_CHIPTOP.PUDER.bit.P87; break;
		case DdTop_GPIO_P90: *enable = IO_CHIPTOP.PUDER.bit.P90; break;
		case DdTop_GPIO_P91: *enable = IO_CHIPTOP.PUDER.bit.P91; break;
		case DdTop_GPIO_P92: *enable = IO_CHIPTOP.PUDER.bit.P92; break;
		case DdTop_GPIO_P93: *enable = IO_CHIPTOP.PUDER.bit.P93; break;
		case DdTop_GPIO_PA0: *enable = IO_CHIPTOP.PUDER.bit.PA0; break;
		case DdTop_GPIO_PA1: *enable = IO_CHIPTOP.PUDER.bit.PA1; break;
		case DdTop_GPIO_PA2: *enable = IO_CHIPTOP.PUDER.bit.PA2; break;
		case DdTop_GPIO_PA3: *enable = IO_CHIPTOP.PUDER.bit.PA3; break;
		case DdTop_GPIO_PA4: *enable = IO_CHIPTOP.PUDER.bit.PA4; break;
		case DdTop_GPIO_PA5: *enable = IO_CHIPTOP.PUDER.bit.PA5; break;
		case DdTop_GPIO_PA6: *enable = IO_CHIPTOP.PUDER.bit.PA6; break;
		case DdTop_GPIO_PA7: *enable = IO_CHIPTOP.PUDER.bit.PA7; break;
		case DdTop_GPIO_PB0: *enable = IO_CHIPTOP.PUDER.bit.PB0; break;
		case DdTop_GPIO_PB1: *enable = IO_CHIPTOP.PUDER.bit.PB1; break;
		case DdTop_GPIO_PB2: *enable = IO_CHIPTOP.PUDER.bit.PB2; break;
		case DdTop_GPIO_PB3: *enable = IO_CHIPTOP.PUDER.bit.PB3; break;
		case DdTop_GPIO_PB4: *enable = IO_CHIPTOP.PUDER.bit.PB4; break;
		case DdTop_GPIO_PD0: *enable = IO_CHIPTOP.PUDER.bit.PD0; break;
		case DdTop_GPIO_PD1: *enable = IO_CHIPTOP.PUDER.bit.PD1; break;
		case DdTop_GPIO_PD2: *enable = IO_CHIPTOP.PUDER.bit.PD2; break;
		case DdTop_GPIO_PD3: *enable = IO_CHIPTOP.PUDER.bit.PD3; break;
		case DdTop_GPIO_PD4: *enable = IO_CHIPTOP.PUDER.bit.PD4; break;
		case DdTop_GPIO_PD5: *enable = IO_CHIPTOP.PUDER.bit.PD5; break;
		case DdTop_GPIO_PD6: *enable = IO_CHIPTOP.PUDER.bit.PD6; break;
		case DdTop_GPIO_PE0: *enable = IO_CHIPTOP.PUDER.bit.PE0; break;
		case DdTop_GPIO_PE1: *enable = IO_CHIPTOP.PUDER.bit.PE1; break;
		case DdTop_GPIO_PF2: *enable = IO_CHIPTOP.PUDER.bit.PF2; break;
		case DdTop_GPIO_PF3: *enable = IO_CHIPTOP.PUDER.bit.PF3; break;
		case DdTop_GPIO_PF4: *enable = IO_CHIPTOP.PUDER.bit.PF4; break;
		case DdTop_GPIO_PG0: *enable = IO_CHIPTOP.PUDER.bit.PG0; break;
		case DdTop_GPIO_PG1: *enable = IO_CHIPTOP.PUDER.bit.PG1; break;
		case DdTop_GPIO_PG2: *enable = IO_CHIPTOP.PUDER.bit.PG2; break;
		case DdTop_GPIO_PG3: *enable = IO_CHIPTOP.PUDER.bit.PG3; break;
		case DdTop_GPIO_PG4: *enable = IO_CHIPTOP.PUDER.bit.PG4; break;
		case DdTop_GPIO_PG5: *enable = IO_CHIPTOP.PUDER.bit.PG5; break;
		case DdTop_GPIO_PG6: *enable = IO_CHIPTOP.PUDER.bit.PG6; break;
		case DdTop_GPIO_PG7: *enable = IO_CHIPTOP.PUDER.bit.PG7; break;
		case DdTop_GPIO_PH0: *enable = IO_CHIPTOP.PUDER.bit.PH0; break;
		case DdTop_GPIO_PH1: *enable = IO_CHIPTOP.PUDER.bit.PH1; break;
		case DdTop_GPIO_PH2: *enable = IO_CHIPTOP.PUDER.bit.PH2; break;
		case DdTop_GPIO_PH3: *enable = IO_CHIPTOP.PUDER.bit.PH3; break;
		case DdTop_GPIO_PW0: *enable = IO_CHIPTOP.PUDER.bit.PW0; break;
		case DdTop_GPIO_PW1: *enable = IO_CHIPTOP.PUDER.bit.PW1; break;
		case DdTop_GPIO_PW2: *enable = IO_CHIPTOP.PUDER.bit.PW2; break;
		case DdTop_GPIO_PW3: *enable = IO_CHIPTOP.PUDER.bit.PW3; break;
		case DdTop_GPIO_PW4: *enable = IO_CHIPTOP.PUDER.bit.PW4; break;
		case DdTop_GPIO_PW5: *enable = IO_CHIPTOP.PUDER.bit.PW5; break;
		case DdTop_GPIO_PW6: *enable = IO_CHIPTOP.PUDER.bit.PW6; break;
		case DdTop_GPIO_PW7: *enable = IO_CHIPTOP.PUDER.bit.PW7; break;
		case DdTop_GPIO_PJ0: *enable = IO_CHIPTOP.PUDER.bit.PJ0; break;
		case DdTop_GPIO_PJ1: *enable = IO_CHIPTOP.PUDER.bit.PJ1; break;
		case DdTop_GPIO_PJ2: *enable = IO_CHIPTOP.PUDER.bit.PJ2; break;
		case DdTop_GPIO_PJ3: *enable = IO_CHIPTOP.PUDER.bit.PJ3; break;
		case DdTop_GPIO_PJ4: *enable = IO_CHIPTOP.PUDER.bit.PJ4; break;
		case DdTop_GPIO_PJ5: *enable = IO_CHIPTOP.PUDER.bit.PJ5; break;
		case DdTop_GPIO_PJ6: *enable = IO_CHIPTOP.PUDER.bit.PJ6; break;
		case DdTop_GPIO_PJ7: *enable = IO_CHIPTOP.PUDER.bit.PJ7; break;
		case DdTop_GPIO_PK0: *enable = IO_CHIPTOP.PUDER.bit.PK0; break;
		case DdTop_GPIO_PK1: *enable = IO_CHIPTOP.PUDER.bit.PK1; break;
		case DdTop_GPIO_PK2: *enable = IO_CHIPTOP.PUDER.bit.PK2; break;
		case DdTop_GPIO_PK3: *enable = IO_CHIPTOP.PUDER.bit.PK3; break;
		case DdTop_GPIO_PK4: *enable = IO_CHIPTOP.PUDER.bit.PK4; break;
		case DdTop_GPIO_PK5: *enable = IO_CHIPTOP.PUDER.bit.PK5; break;
		case DdTop_GPIO_PK6: *enable = IO_CHIPTOP.PUDER.bit.PK6; break;
		case DdTop_GPIO_PK7: *enable = IO_CHIPTOP.PUDER.bit.PK7; break;
		case DdTop_GPIO_PL0: *enable = IO_CHIPTOP.PUDER.bit.PL0; break;
		case DdTop_GPIO_PL1: *enable = IO_CHIPTOP.PUDER.bit.PL1; break;
		case DdTop_GPIO_PL2: *enable = IO_CHIPTOP.PUDER.bit.PL2; break;
		case DdTop_GPIO_PL3: *enable = IO_CHIPTOP.PUDER.bit.PL3; break;
		case DdTop_GPIO_PL4: *enable = IO_CHIPTOP.PUDER.bit.PL4; break;
		case DdTop_GPIO_PL5: *enable = IO_CHIPTOP.PUDER.bit.PL5; break;
		case DdTop_GPIO_PM0: *enable = IO_CHIPTOP.PUDER.bit.PM0; break;
		case DdTop_GPIO_PM1: *enable = IO_CHIPTOP.PUDER.bit.PM1; break;
		case DdTop_GPIO_PM3: *enable = IO_CHIPTOP.PUDER.bit.PM3; break;
		case DdTop_GPIO_PM4: *enable = IO_CHIPTOP.PUDER.bit.PM4; break;
		case DdTop_GPIO_PN0: *enable = IO_CHIPTOP.PUDER.bit.PN0; break;
		case DdTop_GPIO_PN1: *enable = IO_CHIPTOP.PUDER.bit.PN1; break;
		case DdTop_GPIO_PN3: *enable = IO_CHIPTOP.PUDER.bit.PN3; break;
		case DdTop_GPIO_PN4: *enable = IO_CHIPTOP.PUDER.bit.PN4; break;
		case DdTop_GPIO_PY0: *enable = IO_CHIPTOP.PUDER.bit.PY0; break;
		case DdTop_GPIO_PY1: *enable = IO_CHIPTOP.PUDER.bit.PY1; break;
		case DdTop_GPIO_PY2: *enable = IO_CHIPTOP.PUDER.bit.PY2; break;
		case DdTop_GPIO_PY3: *enable = IO_CHIPTOP.PUDER.bit.PY3; break;
		case DdTop_GPIO_PY4: *enable = IO_CHIPTOP.PUDER.bit.PY4; break;
		case DdTop_GPIO_PY5: *enable = IO_CHIPTOP.PUDER.bit.PY5; break;
		case DdTop_GPIO_PY6: *enable = IO_CHIPTOP.PUDER.bit.PY6; break;
		case DdTop_GPIO_PY7: *enable = IO_CHIPTOP.PUDER.bit.PY7; break;
		case DdTop_GPIO_PP0: *enable = IO_CHIPTOP.PUDER.bit.PP0; break;
		case DdTop_GPIO_PP1: *enable = IO_CHIPTOP.PUDER.bit.PP1; break;
		case DdTop_GPIO_PP2: *enable = IO_CHIPTOP.PUDER.bit.PP2; break;
		case DdTop_GPIO_PP3: *enable = IO_CHIPTOP.PUDER.bit.PP3; break;
		default:
			DdToptwo_STOP_GPIO_CLK_WITH_CS();
			Ddim_Print(("dd_top_get_gpio_pull_up_down_enable() error. port not exist.\n"));
			return DdTopone_INPUT_PARAM_ERROR;
	}

	DdToptwo_STOP_GPIO_CLK_WITH_CS();

	return D_DDIM_OK;
}

/**
Set the Pull-up/down state of a selectable GPIO port.<br>
It is set to the PUDCR(Pull-up/down Control Register) value.
@param [in]  port		Port name. See @ref DdTop_GPIO_PORT
@param [in]  control	Pull-up/down state.
						  <ul>
							  <li>0:@ref DdToptwo_GPIO_PUD_DOWN
							  <li>1:@ref DdToptwo_GPIO_PUD_UP
						  </ul>
@retval D_DDIM_OK					Success.
@retval DdTopone_INPUT_PARAM_ERROR	Error occurred.
*/
INT32 dd_top_set_gpio_pull_up_down_ctrl(DdTop *self, DdTop_GPIO_PORT port, UCHAR control )
{
#ifdef DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL
	INT32 s;
#endif // DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL

#ifdef CO_PARAM_CHECK
	if( port >= DdTop_GPIO_PORT_MAX ) {
		Ddim_Assertion(("dd_top_set_gpio_pull_up_down_ctrl() error. port parameters is abnormal.\n"));
		return DdTopone_INPUT_PARAM_ERROR;
	}
	if( control > DdToptwo_GPIO_PUD_UP ) {
		Ddim_Assertion(("dd_top_set_gpio_pull_up_down_ctrl() error. control parameters is abnormal.\n"));
		return DdTopone_INPUT_PARAM_ERROR;
	}
#endif

	DdToptwo_START_GPIO_CLK_WITH_CS();

	switch( port ) {
		case DdTop_GPIO_P80: IO_CHIPTOP.PUDCR.bit.P80 = control; break;
		case DdTop_GPIO_P81: IO_CHIPTOP.PUDCR.bit.P81 = control; break;
		case DdTop_GPIO_P82: IO_CHIPTOP.PUDCR.bit.P82 = control; break;
		case DdTop_GPIO_P83: IO_CHIPTOP.PUDCR.bit.P83 = control; break;
		case DdTop_GPIO_P86: IO_CHIPTOP.PUDCR.bit.P86 = control; break;
		case DdTop_GPIO_P87: IO_CHIPTOP.PUDCR.bit.P87 = control; break;
		case DdTop_GPIO_P90: IO_CHIPTOP.PUDCR.bit.P90 = control; break;
		case DdTop_GPIO_P91: IO_CHIPTOP.PUDCR.bit.P91 = control; break;
		case DdTop_GPIO_P92: IO_CHIPTOP.PUDCR.bit.P92 = control; break;
		case DdTop_GPIO_P93: IO_CHIPTOP.PUDCR.bit.P93 = control; break;
		case DdTop_GPIO_PA0: IO_CHIPTOP.PUDCR.bit.PA0 = control; break;
		case DdTop_GPIO_PA1: IO_CHIPTOP.PUDCR.bit.PA1 = control; break;
		case DdTop_GPIO_PA2: IO_CHIPTOP.PUDCR.bit.PA2 = control; break;
		case DdTop_GPIO_PA3: IO_CHIPTOP.PUDCR.bit.PA3 = control; break;
		case DdTop_GPIO_PA4: IO_CHIPTOP.PUDCR.bit.PA4 = control; break;
		case DdTop_GPIO_PA5: IO_CHIPTOP.PUDCR.bit.PA5 = control; break;
		case DdTop_GPIO_PA6: IO_CHIPTOP.PUDCR.bit.PA6 = control; break;
		case DdTop_GPIO_PA7: IO_CHIPTOP.PUDCR.bit.PA7 = control; break;
		case DdTop_GPIO_PB0: IO_CHIPTOP.PUDCR.bit.PB0 = control; break;
		case DdTop_GPIO_PB1: IO_CHIPTOP.PUDCR.bit.PB1 = control; break;
		case DdTop_GPIO_PB2: IO_CHIPTOP.PUDCR.bit.PB2 = control; break;
		case DdTop_GPIO_PB3: IO_CHIPTOP.PUDCR.bit.PB3 = control; break;
		case DdTop_GPIO_PB4: IO_CHIPTOP.PUDCR.bit.PB4 = control; break;
		case DdTop_GPIO_PD0: IO_CHIPTOP.PUDCR.bit.PD0 = control; break;
		case DdTop_GPIO_PD1: IO_CHIPTOP.PUDCR.bit.PD1 = control; break;
		case DdTop_GPIO_PD2: IO_CHIPTOP.PUDCR.bit.PD2 = control; break;
		case DdTop_GPIO_PD3: IO_CHIPTOP.PUDCR.bit.PD3 = control; break;
		case DdTop_GPIO_PD4: IO_CHIPTOP.PUDCR.bit.PD4 = control; break;
		case DdTop_GPIO_PD5: IO_CHIPTOP.PUDCR.bit.PD5 = control; break;
		case DdTop_GPIO_PD6: IO_CHIPTOP.PUDCR.bit.PD6 = control; break;
		case DdTop_GPIO_PE0: IO_CHIPTOP.PUDCR.bit.PE0 = control; break;
		case DdTop_GPIO_PE1: IO_CHIPTOP.PUDCR.bit.PE1 = control; break;
		case DdTop_GPIO_PF2: IO_CHIPTOP.PUDCR.bit.PF2 = control; break;
		case DdTop_GPIO_PF3: IO_CHIPTOP.PUDCR.bit.PF3 = control; break;
		case DdTop_GPIO_PF4: IO_CHIPTOP.PUDCR.bit.PF4 = control; break;
		case DdTop_GPIO_PG0: IO_CHIPTOP.PUDCR.bit.PG0 = control; break;
		case DdTop_GPIO_PG1: IO_CHIPTOP.PUDCR.bit.PG1 = control; break;
		case DdTop_GPIO_PG2: IO_CHIPTOP.PUDCR.bit.PG2 = control; break;
		case DdTop_GPIO_PG3: IO_CHIPTOP.PUDCR.bit.PG3 = control; break;
		case DdTop_GPIO_PG4: IO_CHIPTOP.PUDCR.bit.PG4 = control; break;
		case DdTop_GPIO_PG5: IO_CHIPTOP.PUDCR.bit.PG5 = control; break;
		case DdTop_GPIO_PG6: IO_CHIPTOP.PUDCR.bit.PG6 = control; break;
		case DdTop_GPIO_PG7: IO_CHIPTOP.PUDCR.bit.PG7 = control; break;
		case DdTop_GPIO_PH0: IO_CHIPTOP.PUDCR.bit.PH0 = control; break;
		case DdTop_GPIO_PH1: IO_CHIPTOP.PUDCR.bit.PH1 = control; break;
		case DdTop_GPIO_PH2: IO_CHIPTOP.PUDCR.bit.PH2 = control; break;
		case DdTop_GPIO_PH3: IO_CHIPTOP.PUDCR.bit.PH3 = control; break;
		case DdTop_GPIO_PW0: IO_CHIPTOP.PUDCR.bit.PW0 = control; break;
		case DdTop_GPIO_PW1: IO_CHIPTOP.PUDCR.bit.PW1 = control; break;
		case DdTop_GPIO_PW2: IO_CHIPTOP.PUDCR.bit.PW2 = control; break;
		case DdTop_GPIO_PW3: IO_CHIPTOP.PUDCR.bit.PW3 = control; break;
		case DdTop_GPIO_PW4: IO_CHIPTOP.PUDCR.bit.PW4 = control; break;
		case DdTop_GPIO_PW5: IO_CHIPTOP.PUDCR.bit.PW5 = control; break;
		case DdTop_GPIO_PW6: IO_CHIPTOP.PUDCR.bit.PW6 = control; break;
		case DdTop_GPIO_PW7: IO_CHIPTOP.PUDCR.bit.PW7 = control; break;
		case DdTop_GPIO_PJ0: IO_CHIPTOP.PUDCR.bit.PJ0 = control; break;
		case DdTop_GPIO_PJ1: IO_CHIPTOP.PUDCR.bit.PJ1 = control; break;
		case DdTop_GPIO_PJ2: IO_CHIPTOP.PUDCR.bit.PJ2 = control; break;
		case DdTop_GPIO_PJ3: IO_CHIPTOP.PUDCR.bit.PJ3 = control; break;
		case DdTop_GPIO_PJ4: IO_CHIPTOP.PUDCR.bit.PJ4 = control; break;
		case DdTop_GPIO_PJ5: IO_CHIPTOP.PUDCR.bit.PJ5 = control; break;
		case DdTop_GPIO_PJ6: IO_CHIPTOP.PUDCR.bit.PJ6 = control; break;
		case DdTop_GPIO_PJ7: IO_CHIPTOP.PUDCR.bit.PJ7 = control; break;
		case DdTop_GPIO_PK0: IO_CHIPTOP.PUDCR.bit.PK0 = control; break;
		case DdTop_GPIO_PK1: IO_CHIPTOP.PUDCR.bit.PK1 = control; break;
		case DdTop_GPIO_PK2: IO_CHIPTOP.PUDCR.bit.PK2 = control; break;
		case DdTop_GPIO_PK3: IO_CHIPTOP.PUDCR.bit.PK3 = control; break;
		case DdTop_GPIO_PK4: IO_CHIPTOP.PUDCR.bit.PK4 = control; break;
		case DdTop_GPIO_PK5: IO_CHIPTOP.PUDCR.bit.PK5 = control; break;
		case DdTop_GPIO_PK6: IO_CHIPTOP.PUDCR.bit.PK6 = control; break;
		case DdTop_GPIO_PK7: IO_CHIPTOP.PUDCR.bit.PK7 = control; break;
		case DdTop_GPIO_PL0: IO_CHIPTOP.PUDCR.bit.PL0 = control; break;
		case DdTop_GPIO_PL1: IO_CHIPTOP.PUDCR.bit.PL1 = control; break;
		case DdTop_GPIO_PL2: IO_CHIPTOP.PUDCR.bit.PL2 = control; break;
		case DdTop_GPIO_PL3: IO_CHIPTOP.PUDCR.bit.PL3 = control; break;
		case DdTop_GPIO_PL4: IO_CHIPTOP.PUDCR.bit.PL4 = control; break;
		case DdTop_GPIO_PL5: IO_CHIPTOP.PUDCR.bit.PL5 = control; break;
		case DdTop_GPIO_PM0: IO_CHIPTOP.PUDCR.bit.PM0 = control; break;
		case DdTop_GPIO_PM1: IO_CHIPTOP.PUDCR.bit.PM1 = control; break;
		case DdTop_GPIO_PM3: IO_CHIPTOP.PUDCR.bit.PM3 = control; break;
		case DdTop_GPIO_PM4: IO_CHIPTOP.PUDCR.bit.PM4 = control; break;
		case DdTop_GPIO_PN0: IO_CHIPTOP.PUDCR.bit.PN0 = control; break;
		case DdTop_GPIO_PN1: IO_CHIPTOP.PUDCR.bit.PN1 = control; break;
		case DdTop_GPIO_PN3: IO_CHIPTOP.PUDCR.bit.PN3 = control; break;
		case DdTop_GPIO_PN4: IO_CHIPTOP.PUDCR.bit.PN4 = control; break;
		case DdTop_GPIO_PY0: IO_CHIPTOP.PUDCR.bit.PY0 = control; break;
		case DdTop_GPIO_PY1: IO_CHIPTOP.PUDCR.bit.PY1 = control; break;
		case DdTop_GPIO_PY2: IO_CHIPTOP.PUDCR.bit.PY2 = control; break;
		case DdTop_GPIO_PY3: IO_CHIPTOP.PUDCR.bit.PY3 = control; break;
		case DdTop_GPIO_PY4: IO_CHIPTOP.PUDCR.bit.PY4 = control; break;
		case DdTop_GPIO_PY5: IO_CHIPTOP.PUDCR.bit.PY5 = control; break;
		case DdTop_GPIO_PY6: IO_CHIPTOP.PUDCR.bit.PY6 = control; break;
		case DdTop_GPIO_PY7: IO_CHIPTOP.PUDCR.bit.PY7 = control; break;
		case DdTop_GPIO_PP0: IO_CHIPTOP.PUDCR.bit.PP0 = control; break;
		case DdTop_GPIO_PP1: IO_CHIPTOP.PUDCR.bit.PP1 = control; break;
		case DdTop_GPIO_PP2: IO_CHIPTOP.PUDCR.bit.PP2 = control; break;
		case DdTop_GPIO_PP3: IO_CHIPTOP.PUDCR.bit.PP3 = control; break;
		default:
			DdToptwo_STOP_GPIO_CLK_WITH_CS();
			Ddim_Print(("dd_top_set_gpio_pull_up_down_ctrl() error. port not exist.\n"));
			return DdTopone_INPUT_PARAM_ERROR;
	}

	Dd_ARM_Dsb_Pou();
	DdToptwo_STOP_GPIO_CLK_WITH_CS();

	return D_DDIM_OK;
}

/**
Get the Pull-up/down state of a selectable GPIO port.<br>
It is get from the PUDCR(Pull-up/down Control Register) value.
@param [in]  port		Port name. See @ref DdTop_GPIO_PORT
@param [out] control	Pull-up/down state.
						  <ul>
							  <li>0:@ref DdToptwo_GPIO_PUD_DOWN
							  <li>1:@ref DdToptwo_GPIO_PUD_UP
						  </ul>
@retval D_DDIM_OK					Success.
@retval DdTopone_INPUT_PARAM_ERROR	Error occurred.
*/
INT32 dd_top_get_gpio_pull_up_down_ctrl(DdTop *self, DdTop_GPIO_PORT port, UCHAR* control )
{
#ifdef DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL
	INT32 s;
#endif // DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL

#ifdef CO_PARAM_CHECK
	if (port >= DdTop_GPIO_PORT_MAX) {
		Ddim_Assertion(("dd_top_get_gpio_pull_up_down_ctrl() error. port parameters is abnormal.\n"));
		return DdTopone_INPUT_PARAM_ERROR;
	}
	if (control == NULL) {
		Ddim_Assertion(("dd_top_get_gpio_pull_up_down_ctrl() error. control parameters is abnormal.\n"));
		return DdTopone_INPUT_PARAM_ERROR;
	}
#endif

	DdToptwo_START_GPIO_CLK_WITH_CS();

	switch( port ) {
		case DdTop_GPIO_P80: *control = IO_CHIPTOP.PUDCR.bit.P80; break;
		case DdTop_GPIO_P81: *control = IO_CHIPTOP.PUDCR.bit.P81; break;
		case DdTop_GPIO_P82: *control = IO_CHIPTOP.PUDCR.bit.P82; break;
		case DdTop_GPIO_P83: *control = IO_CHIPTOP.PUDCR.bit.P83; break;
		case DdTop_GPIO_P86: *control = IO_CHIPTOP.PUDCR.bit.P86; break;
		case DdTop_GPIO_P87: *control = IO_CHIPTOP.PUDCR.bit.P87; break;
		case DdTop_GPIO_P90: *control = IO_CHIPTOP.PUDCR.bit.P90; break;
		case DdTop_GPIO_P91: *control = IO_CHIPTOP.PUDCR.bit.P91; break;
		case DdTop_GPIO_P92: *control = IO_CHIPTOP.PUDCR.bit.P92; break;
		case DdTop_GPIO_P93: *control = IO_CHIPTOP.PUDCR.bit.P93; break;
		case DdTop_GPIO_PA0: *control = IO_CHIPTOP.PUDCR.bit.PA0; break;
		case DdTop_GPIO_PA1: *control = IO_CHIPTOP.PUDCR.bit.PA1; break;
		case DdTop_GPIO_PA2: *control = IO_CHIPTOP.PUDCR.bit.PA2; break;
		case DdTop_GPIO_PA3: *control = IO_CHIPTOP.PUDCR.bit.PA3; break;
		case DdTop_GPIO_PA4: *control = IO_CHIPTOP.PUDCR.bit.PA4; break;
		case DdTop_GPIO_PA5: *control = IO_CHIPTOP.PUDCR.bit.PA5; break;
		case DdTop_GPIO_PA6: *control = IO_CHIPTOP.PUDCR.bit.PA6; break;
		case DdTop_GPIO_PA7: *control = IO_CHIPTOP.PUDCR.bit.PA7; break;
		case DdTop_GPIO_PB0: *control = IO_CHIPTOP.PUDCR.bit.PB0; break;
		case DdTop_GPIO_PB1: *control = IO_CHIPTOP.PUDCR.bit.PB1; break;
		case DdTop_GPIO_PB2: *control = IO_CHIPTOP.PUDCR.bit.PB2; break;
		case DdTop_GPIO_PB3: *control = IO_CHIPTOP.PUDCR.bit.PB3; break;
		case DdTop_GPIO_PB4: *control = IO_CHIPTOP.PUDCR.bit.PB4; break;
		case DdTop_GPIO_PD0: *control = IO_CHIPTOP.PUDCR.bit.PD0; break;
		case DdTop_GPIO_PD1: *control = IO_CHIPTOP.PUDCR.bit.PD1; break;
		case DdTop_GPIO_PD2: *control = IO_CHIPTOP.PUDCR.bit.PD2; break;
		case DdTop_GPIO_PD3: *control = IO_CHIPTOP.PUDCR.bit.PD3; break;
		case DdTop_GPIO_PD4: *control = IO_CHIPTOP.PUDCR.bit.PD4; break;
		case DdTop_GPIO_PD5: *control = IO_CHIPTOP.PUDCR.bit.PD5; break;
		case DdTop_GPIO_PD6: *control = IO_CHIPTOP.PUDCR.bit.PD6; break;
		case DdTop_GPIO_PE0: *control = IO_CHIPTOP.PUDCR.bit.PE0; break;
		case DdTop_GPIO_PE1: *control = IO_CHIPTOP.PUDCR.bit.PE1; break;
		case DdTop_GPIO_PF2: *control = IO_CHIPTOP.PUDCR.bit.PF2; break;
		case DdTop_GPIO_PF3: *control = IO_CHIPTOP.PUDCR.bit.PF3; break;
		case DdTop_GPIO_PF4: *control = IO_CHIPTOP.PUDCR.bit.PF4; break;
		case DdTop_GPIO_PG0: *control = IO_CHIPTOP.PUDCR.bit.PG0; break;
		case DdTop_GPIO_PG1: *control = IO_CHIPTOP.PUDCR.bit.PG1; break;
		case DdTop_GPIO_PG2: *control = IO_CHIPTOP.PUDCR.bit.PG2; break;
		case DdTop_GPIO_PG3: *control = IO_CHIPTOP.PUDCR.bit.PG3; break;
		case DdTop_GPIO_PG4: *control = IO_CHIPTOP.PUDCR.bit.PG4; break;
		case DdTop_GPIO_PG5: *control = IO_CHIPTOP.PUDCR.bit.PG5; break;
		case DdTop_GPIO_PG6: *control = IO_CHIPTOP.PUDCR.bit.PG6; break;
		case DdTop_GPIO_PG7: *control = IO_CHIPTOP.PUDCR.bit.PG7; break;
		case DdTop_GPIO_PH0: *control = IO_CHIPTOP.PUDCR.bit.PH0; break;
		case DdTop_GPIO_PH1: *control = IO_CHIPTOP.PUDCR.bit.PH1; break;
		case DdTop_GPIO_PH2: *control = IO_CHIPTOP.PUDCR.bit.PH2; break;
		case DdTop_GPIO_PH3: *control = IO_CHIPTOP.PUDCR.bit.PH3; break;
		case DdTop_GPIO_PW0: *control = IO_CHIPTOP.PUDCR.bit.PW0; break;
		case DdTop_GPIO_PW1: *control = IO_CHIPTOP.PUDCR.bit.PW1; break;
		case DdTop_GPIO_PW2: *control = IO_CHIPTOP.PUDCR.bit.PW2; break;
		case DdTop_GPIO_PW3: *control = IO_CHIPTOP.PUDCR.bit.PW3; break;
		case DdTop_GPIO_PW4: *control = IO_CHIPTOP.PUDCR.bit.PW4; break;
		case DdTop_GPIO_PW5: *control = IO_CHIPTOP.PUDCR.bit.PW5; break;
		case DdTop_GPIO_PW6: *control = IO_CHIPTOP.PUDCR.bit.PW6; break;
		case DdTop_GPIO_PW7: *control = IO_CHIPTOP.PUDCR.bit.PW7; break;
		case DdTop_GPIO_PJ0: *control = IO_CHIPTOP.PUDCR.bit.PJ0; break;
		case DdTop_GPIO_PJ1: *control = IO_CHIPTOP.PUDCR.bit.PJ1; break;
		case DdTop_GPIO_PJ2: *control = IO_CHIPTOP.PUDCR.bit.PJ2; break;
		case DdTop_GPIO_PJ3: *control = IO_CHIPTOP.PUDCR.bit.PJ3; break;
		case DdTop_GPIO_PJ4: *control = IO_CHIPTOP.PUDCR.bit.PJ4; break;
		case DdTop_GPIO_PJ5: *control = IO_CHIPTOP.PUDCR.bit.PJ5; break;
		case DdTop_GPIO_PJ6: *control = IO_CHIPTOP.PUDCR.bit.PJ6; break;
		case DdTop_GPIO_PJ7: *control = IO_CHIPTOP.PUDCR.bit.PJ7; break;
		case DdTop_GPIO_PK0: *control = IO_CHIPTOP.PUDCR.bit.PK0; break;
		case DdTop_GPIO_PK1: *control = IO_CHIPTOP.PUDCR.bit.PK1; break;
		case DdTop_GPIO_PK2: *control = IO_CHIPTOP.PUDCR.bit.PK2; break;
		case DdTop_GPIO_PK3: *control = IO_CHIPTOP.PUDCR.bit.PK3; break;
		case DdTop_GPIO_PK4: *control = IO_CHIPTOP.PUDCR.bit.PK4; break;
		case DdTop_GPIO_PK5: *control = IO_CHIPTOP.PUDCR.bit.PK5; break;
		case DdTop_GPIO_PK6: *control = IO_CHIPTOP.PUDCR.bit.PK6; break;
		case DdTop_GPIO_PK7: *control = IO_CHIPTOP.PUDCR.bit.PK7; break;
		case DdTop_GPIO_PL0: *control = IO_CHIPTOP.PUDCR.bit.PL0; break;
		case DdTop_GPIO_PL1: *control = IO_CHIPTOP.PUDCR.bit.PL1; break;
		case DdTop_GPIO_PL2: *control = IO_CHIPTOP.PUDCR.bit.PL2; break;
		case DdTop_GPIO_PL3: *control = IO_CHIPTOP.PUDCR.bit.PL3; break;
		case DdTop_GPIO_PL4: *control = IO_CHIPTOP.PUDCR.bit.PL4; break;
		case DdTop_GPIO_PL5: *control = IO_CHIPTOP.PUDCR.bit.PL5; break;
		case DdTop_GPIO_PM0: *control = IO_CHIPTOP.PUDCR.bit.PM0; break;
		case DdTop_GPIO_PM1: *control = IO_CHIPTOP.PUDCR.bit.PM1; break;
		case DdTop_GPIO_PM3: *control = IO_CHIPTOP.PUDCR.bit.PM3; break;
		case DdTop_GPIO_PM4: *control = IO_CHIPTOP.PUDCR.bit.PM4; break;
		case DdTop_GPIO_PN0: *control = IO_CHIPTOP.PUDCR.bit.PN0; break;
		case DdTop_GPIO_PN1: *control = IO_CHIPTOP.PUDCR.bit.PN1; break;
		case DdTop_GPIO_PN3: *control = IO_CHIPTOP.PUDCR.bit.PN3; break;
		case DdTop_GPIO_PN4: *control = IO_CHIPTOP.PUDCR.bit.PN4; break;
		case DdTop_GPIO_PY0: *control = IO_CHIPTOP.PUDCR.bit.PY0; break;
		case DdTop_GPIO_PY1: *control = IO_CHIPTOP.PUDCR.bit.PY1; break;
		case DdTop_GPIO_PY2: *control = IO_CHIPTOP.PUDCR.bit.PY2; break;
		case DdTop_GPIO_PY3: *control = IO_CHIPTOP.PUDCR.bit.PY3; break;
		case DdTop_GPIO_PY4: *control = IO_CHIPTOP.PUDCR.bit.PY4; break;
		case DdTop_GPIO_PY5: *control = IO_CHIPTOP.PUDCR.bit.PY5; break;
		case DdTop_GPIO_PY6: *control = IO_CHIPTOP.PUDCR.bit.PY6; break;
		case DdTop_GPIO_PY7: *control = IO_CHIPTOP.PUDCR.bit.PY7; break;
		case DdTop_GPIO_PP0: *control = IO_CHIPTOP.PUDCR.bit.PP0; break;
		case DdTop_GPIO_PP1: *control = IO_CHIPTOP.PUDCR.bit.PP1; break;
		case DdTop_GPIO_PP2: *control = IO_CHIPTOP.PUDCR.bit.PP2; break;
		case DdTop_GPIO_PP3: *control = IO_CHIPTOP.PUDCR.bit.PP3; break;
		default:
			DdToptwo_STOP_GPIO_CLK_WITH_CS();
			Ddim_Print(("dd_top_get_gpio_pull_up_down_ctrl() error. port not exist.\n"));
			return DdTopone_INPUT_PARAM_ERROR;
	}

	DdToptwo_STOP_GPIO_CLK_WITH_CS();

	return D_DDIM_OK;
}




/**
Get Frequency of LTM pipe2 clock
@retval	Hz
*/
ULONG dd_top_get_ltm2clk(VOID)
{
	// 0: 300MHz(=1200MHz/4)
	// 1: 200MHz(=1200MHz/6)
	// 2: 150MHz(=1200MHz/8)
	// 3: 100MHz(=1200MHz/12)
	// 4: 75MHz(=1200MHz/16)
	// 5: 60MHz(=1200MHz/20)
	// 6: 50MHz(=1200MHz/24)
	// 8: SRO2CLK
	// 16:SRO2CLK_2
	// 24:B2B2CLK
	// 32:B2R2CLK
	static const UCHAR S_DIVID[] = { 4, 6, 8, 12, 16, 20, 24 };
	ULONG clock = 0;

	switch (DdTopone_Get_CLKSEL6_LTM2CLK()) {
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		clock = (DdTopone_1200_PLL_OUT / S_DIVID[DdTopone_Get_CLKSEL6_LTM2CLK()]);
		break;
	case 8:
		clock = dd_top_get_sro2clk();
		break;
	case 16:
		clock = dd_topone_get_sro2clk_2();
		break;
	case 24:
		clock = dd_top_get_b2b2clk();
		break;
	case 32:
		clock = dd_top_get_b2r2clk();
		break;
	}

	return clock;
}

/**
Get Frequency of B2R pipe2 clock
@retval	Hz
*/
ULONG dd_top_get_b2r2clk(VOID)
{
	// 0: 300MHz(=1200MHz/4)
	// 1: 200MHz(=1200MHz/6)
	// 2: 150MHz(=1200MHz/8)
	// 3: 100MHz(=1200MHz/12)
	// 4: 75MHz(=1200MHz/16)
	// 5: 60MHz(=1200MHz/20)
	// 6: 50MHz(=1200MHz/24)
	// 8: SRO2CLK
	// 16:SRO2CLK_2
	// 24:B2B2CLK
	static const UCHAR S_DIVID[] = { 4, 6, 8, 12, 16, 20, 24 };
	ULONG clock = 0;

	switch (DdTopone_Get_CLKSEL6_B2R2CLK()) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			clock = (DdTopone_1200_PLL_OUT / S_DIVID[DdTopone_Get_CLKSEL6_B2R2CLK()]);
			break;
		case 8:
			clock = dd_top_get_sro2clk();
			break;
		case 16:
			clock = dd_topone_get_sro2clk_2();
			break;
		case 24:
			clock = dd_top_get_b2b2clk();
			break;
	}

	return clock;
}

/**
Get Frequency of CNR pipe2 clock
@retval	Hz
*/
ULONG dd_top_get_cnr2clk(VOID)
{
	// 0: 300MHz(=1200MHz/4)
	// 1: 200MHz(=1200MHz/6)
	// 2: 150MHz(=1200MHz/8)
	// 3: 100MHz(=1200MHz/12)
	// 4: 75MHz(=1200MHz/16)
	// 5: 60MHz(=1200MHz/20)
	// 6: 50MHz(=1200MHz/24)
	// 8: R2Y2CLK
	static const UCHAR S_DIVID[] = { 4, 6, 8, 12, 16, 20, 24 };
	ULONG clock = 0;

	switch (DdTopone_Get_CLKSEL6_CNR2CLK()) {
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		clock = (DdTopone_1200_PLL_OUT / S_DIVID[DdTopone_Get_CLKSEL6_CNR2CLK()]);
		break;
	case 8:
		clock = dd_topone_get_r2y2clk();
		break;
	}

	return clock;
}

/**
Get Frequency of SRO pipe2 clock
@retval	Hz
*/
ULONG dd_top_get_sro2clk(VOID)
{
	// 0: 300MHz(=1200MHz/4)
	// 1: 200MHz(=1200MHz/6)
	// 2: 150MHz(=1200MHz/8)
	// 3: 100MHz(=1200MHz/12)
	// 4: 75MHz(=1200MHz/16)
	// 5: 60MHz(=1200MHz/20)
	// 6: 50MHz(=1200MHz/24)
	static const UCHAR S_DIVID[] = { 4, 6, 8, 12, 16, 20, 24 };

	return (DdTopone_1200_PLL_OUT / S_DIVID[DdTopone_Get_CLKSEL7_SRO2CLK()]);
}

/**
Get Frequency of B2B pipe2 clock
@retval	Hz
*/
ULONG dd_top_get_b2b2clk(VOID)
{
	// 0: 300MHz(=1200MHz/4)
	// 1: 200MHz(=1200MHz/6)
	// 2: 150MHz(=1200MHz/8)
	// 3: 100MHz(=1200MHz/12)
	// 4: 75MHz(=1200MHz/16)
	// 5: 60MHz(=1200MHz/20)
	// 6: 50MHz(=1200MHz/24)
	// 8 :SRO2CLK
	// 16:SRO2CLK_2
	static const UCHAR S_DIVID[] = { 4, 6, 8, 12, 16, 20, 24 };
	ULONG clock = 0;

	switch (DdTopone_Get_CLKSEL7_B2B2CLK()) {
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		clock = (DdTopone_1200_PLL_OUT / S_DIVID[DdTopone_Get_CLKSEL7_B2B2CLK()]);
		break;
	case 8:
		clock = dd_top_get_sro2clk();
		break;
	case 16:
		clock = dd_topone_get_sro2clk_2();
		break;
	}

	return clock;
}

/**
Get Frequency of LTMRBK pipe2 clock
@retval	Hz
*/
ULONG dd_top_get_ltmrbk2clk(VOID)
{
	// 0: 300MHz(=1200MHz/4)
	// 1: 200MHz(=1200MHz/6)
	// 2: 150MHz(=1200MHz/8)
	// 3: 100MHz(=1200MHz/12)
	// 4: 75MHz(=1200MHz/16)
	// 5: 60MHz(=1200MHz/20)
	// 6: 50MHz(=1200MHz/24)
	// 8 :SRO2CLK
	// 16:SRO2CLK_2
	static const UCHAR S_DIVID[] = { 4, 6, 8, 12, 16, 20, 24 };
	ULONG clock = 0;

	switch (DdTopone_Get_CLKSEL7_LTMRBK2CLK()) {
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		clock = (DdTopone_1200_PLL_OUT / S_DIVID[DdTopone_Get_CLKSEL7_LTMRBK2CLK()]);
		break;
	case 8:
		clock = dd_top_get_sro2clk();
		break;
	case 16:
		clock = dd_topone_get_sro2clk_2();
		break;
	}

	return clock;
}

/**
Get Frequency of APCLK clock
@retval	Hz
*/
ULONG dd_top_get_apclk(VOID)
{
	// 0: 74.25MHz(=1188MHz/16)
	// 1: 54MHz(=1188MHz/22)
	// 2: 37.125MHz(=1188MHz/32)
	// 3: 27MHz(=1188MHz/44)
	// 4: 72MHz(=864MHz/12)
	// 5: 48MHz(=864MHz/18)
	// 8: 64MHz(=1600MHz/25)
	// 9: 45.714MHz(=1600MHz/35)
	// 12: 60MHz(=1500MHz/25)
	static const UCHAR S_ID[] = { 0, 1, 2, 3, 4, 5, 8, 9, 12, 255 };
	static const UCHAR S_DIVID[] = { 16, 22, 32, 44, 12, 18, 25, 35, 25 };
	static const ULONG S_PLLID[] ={ DdTopone_1188_PLL_OUT, DdTopone_1188_PLL_OUT,
					DdTopone_1188_PLL_OUT, DdTopone_1188_PLL_OUT, DdTopone_864_PLL_OUT,
					DdTopone_864_PLL_OUT, DdTopone_1600_PLL_OUT, DdTopone_1600_PLL_OUT,
					DdTopone_1500_PLL_OUT };
	int i;
	ULONG clock = 0;

	for (i = 0; S_ID[i] != 255; i++) {
		if (DdTopone_Get_CLKSEL8_APCLK() == S_ID[i]) {
			clock = (S_PLLID[i] / S_DIVID[i]);
			break;
		}
	}

	return clock;
}

/**
Get Frequency of Audio clock
@retval	Hz
*/
ULONG dd_top_get_auclk(VOID) {
	// 0:36.864MHz (set to 96 PL10ADIV)
	// 1:22.5792MHz (set to 98 PL10ADIV)
	// 2:24.576MHz (set to 128 PL10ADIV)
	// 3:8.192MHz (set to 128 PL10ADIV)
	static const UCHAR S_DIVID[] = { 18, 30, 36, 108 };
	static const ULONG S_PLLD[] = { DdTopone_Audio_96_PLL_OUT, DdTopone_Audio_98_PLL_OUT,
										DdTopone_Audio_128_PLL_OUT, DdTopone_Audio_128_PLL_OUT };

	return (S_PLLD[DdTopone_Get_CLKSEL8_AUCLK()] / S_DIVID[DdTopone_Get_CLKSEL8_AUCLK()]);

}

/**
Get Frequency of SPI clock
@retval	Hz
*/
ULONG dd_top_get_spiclk(VOID)
{
	// 0:216MHz(=864MHz/4)
	// 1:108MHz(=864MHz/8)
	// 2:100MHz(=1600MHz/16)
	static const UCHAR S_ID[] = { 0, 1, 2, 255 };
	static const UCHAR S_DIVID[] = { 4, 8, 16 };
	static const ULONG S_PLLID[] = { DdTopone_864_PLL_OUT, DdTopone_864_PLL_OUT,
																DdTopone_1600_PLL_OUT };

	int i;
	ULONG clock = 0;

	for (i = 0; S_ID[i] != 255; i++) {
		if (DdTopone_Get_CLKSEL8_SPICLK() == S_ID[i]) {
			clock = (S_PLLID[i] / S_DIVID[i]);
			break;
		}
	}

	return clock;
}

DdTop* dd_top_new(void)
{
	DdTop *self = g_object_new(DD_TYPE_TOP, NULL);
	return self;
}
