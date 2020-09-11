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


#include "dd_arm.h"
#include "driver_common.h"
#include "ddim_user_custom.h"
#if 1    // special key control
#include "pmc.h"
#include <string.h>
#endif
#include <stdio.h>
#include "ddtoptwo.h"


G_DEFINE_TYPE(DdToptwo, dd_toptwo, G_TYPE_OBJECT);
#define DD_TOPTWO_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), DD_TYPE_TOPTWO, DdToptwoPrivate));


struct _DdToptwoPrivate{

};


/*DECLS*/
static void 					dispose_od(GObject  *object);
static void 					finalize_od(GObject  *object);


/*IMPL*/
static void dd_toptwo_class_init(DdToptwoClass *klass)
{
	g_type_class_add_private(klass, sizeof(DdToptwoPrivate));
}

static void dd_toptwo_init(DdToptwo *self)
{
	DdToptwoPrivate *priv = DD_TOPTWO_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
	DdToptwoPrivate *self = DD_TOPTWO_GET_PRIVATE(object);
}

static void finalize_od(GObject *object)
{
	DdToptwoPrivate *self = DD_TOPTWO_GET_PRIVATE(object);
}

#if 1    // special key control
INT32 dd_toptwo_set_gpio_cm0_function(DdToptwo *self, DdTop_GPIO_CM0_PORT port, UCHAR function )
{
#ifdef DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL
		INT32 s;
#endif // DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL

#ifdef CO_PARAM_CHECK
		if( port >= DdTop_GPIO_CM0_PORT_MAX ) {
			Ddim_Assertion(("Dd_TOP_GPIO_Set_Gpio_CM0_Function() error. port parameters is abnormal.\n"));
			return DdTopone_INPUT_PARAM_ERROR;
		}
		if( function > DdToptwo_GPIO_FUNC_HWMODE ) {
			Ddim_Assertion(("Dd_TOP_GPIO_Set_Gpio_CM0_Function() error. function parameters is abnormal.\n"));
			return DdTopone_INPUT_PARAM_ERROR;
		}
#endif

		DdToptwo_START_GPIO_CLK_WITH_CS();

		switch( port ) {
			case DdTop_GPIO_CM0_P22: IO_PMC.GPIO.EPCR.bit.P22 = function; break;
			case DdTop_GPIO_CM0_P23: IO_PMC.GPIO.EPCR.bit.P23 = function; break;
			case DdTop_GPIO_CM0_P31: IO_PMC.GPIO.EPCR.bit.P31 = function; break;
			case DdTop_GPIO_CM0_P33: IO_PMC.GPIO.EPCR.bit.P33 = function; break;
			case DdTop_GPIO_CM0_P35: IO_PMC.GPIO.EPCR.bit.P35 = function; break;
			case DdTop_GPIO_CM0_P37: IO_PMC.GPIO.EPCR.bit.P37 = function; break;
			case DdTop_GPIO_CM0_P45: IO_PMC.GPIO.EPCR.bit.P45 = function; break;
			default:
				DdToptwo_STOP_GPIO_CLK_WITH_CS();
				Ddim_Print(("Dd_PMC_GPIO_Set_Gpio_Function() error. port not exist.\n"));
				return DdTopone_INPUT_PARAM_ERROR;
		}

		Dd_ARM_Dsb_Pou();
		DdToptwo_STOP_GPIO_CLK_WITH_CS();

		return D_DDIM_OK;
}

INT32 dd_toptwo_get_gpio_cm0_function(DdToptwo *self, DdTop_GPIO_CM0_PORT port, UCHAR* function )
{
#ifdef DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL
	INT32 s;
#endif // DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL

#ifdef CO_PARAM_CHECK
	if( port >= DdTop_GPIO_CM0_PORT_MAX ) {
		Ddim_Assertion(("DdTopone_GPIO_Get_Gpio_CM0_Function() error. port parameters is abnormal.\n"));
		return DdTopone_INPUT_PARAM_ERROR;
	}
	if( function == NULL ) {
		Ddim_Assertion(("DdTopone_GPIO_Get_Gpio_CM0_Function() error. function parameters is abnormal.\n"));
		return DdTopone_INPUT_PARAM_ERROR;
	}
#endif

	DdToptwo_START_GPIO_CLK_WITH_CS();

	switch( port ) {
		case DdTop_GPIO_CM0_P22: *function = IO_PMC.GPIO.EPCR.bit.P22; break;
		case DdTop_GPIO_CM0_P23: *function = IO_PMC.GPIO.EPCR.bit.P23; break;
		case DdTop_GPIO_CM0_P31: *function = IO_PMC.GPIO.EPCR.bit.P31; break;
		case DdTop_GPIO_CM0_P33: *function = IO_PMC.GPIO.EPCR.bit.P33; break;
		case DdTop_GPIO_CM0_P35: *function = IO_PMC.GPIO.EPCR.bit.P35; break;
		case DdTop_GPIO_CM0_P37: *function = IO_PMC.GPIO.EPCR.bit.P37; break;
		case DdTop_GPIO_CM0_P45: *function = IO_PMC.GPIO.EPCR.bit.P45; break;
		default:
			DdToptwo_STOP_GPIO_CLK_WITH_CS();
			Ddim_Print(("DdTopone_GPIO_Get_Gpio_CM0_Function() error. port not exist.\n"));
			return DdTopone_INPUT_PARAM_ERROR;
	}

	DdToptwo_STOP_GPIO_CLK_WITH_CS();

	return D_DDIM_OK;
}

INT32 dd_toptwo_set_gpio_cm0_direction(DdToptwo *self, DdTop_GPIO_CM0_PORT port, UCHAR direction )
{
#ifdef DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL
	INT32 s;
#endif // DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL

#ifdef CO_PARAM_CHECK
	if( port >= DdTop_GPIO_CM0_PORT_MAX ) {
		Ddim_Assertion(("dd_toptwo_set_gpio_cm0_direction() error. port parameters is abnormal.\n"));
		return DdTopone_INPUT_PARAM_ERROR;
	}
	if( direction > DdToptwo_GPIO_DIR_OUT ) {
		Ddim_Assertion(("dd_toptwo_set_gpio_cm0_direction() error. direction parameters is abnormal.\n"));
		return DdTopone_INPUT_PARAM_ERROR;
	}
#endif

	DdToptwo_START_GPIO_CLK_WITH_CS();

	switch( port ) {
		case DdTop_GPIO_CM0_P00: IO_PMC.GPIO.DDR.bit.P00 = direction; break;
		case DdTop_GPIO_CM0_P01: IO_PMC.GPIO.DDR.bit.P01 = direction; break;
		case DdTop_GPIO_CM0_P02: IO_PMC.GPIO.DDR.bit.P02 = direction; break;
		case DdTop_GPIO_CM0_P03: IO_PMC.GPIO.DDR.bit.P03 = direction; break;
		case DdTop_GPIO_CM0_P04: IO_PMC.GPIO.DDR.bit.P04 = direction; break;
		case DdTop_GPIO_CM0_P05: IO_PMC.GPIO.DDR.bit.P05 = direction; break;
		case DdTop_GPIO_CM0_P06: IO_PMC.GPIO.DDR.bit.P06 = direction; break;
		case DdTop_GPIO_CM0_P07: IO_PMC.GPIO.DDR.bit.P07 = direction; break;
		case DdTop_GPIO_CM0_P10: IO_PMC.GPIO.DDR.bit.P10 = direction; break;
		case DdTop_GPIO_CM0_P11: IO_PMC.GPIO.DDR.bit.P11 = direction; break;
		case DdTop_GPIO_CM0_P12: IO_PMC.GPIO.DDR.bit.P12 = direction; break;
		case DdTop_GPIO_CM0_P13: IO_PMC.GPIO.DDR.bit.P13 = direction; break;
		case DdTop_GPIO_CM0_P14: IO_PMC.GPIO.DDR.bit.P14 = direction; break;
		case DdTop_GPIO_CM0_P15: IO_PMC.GPIO.DDR.bit.P15 = direction; break;
		case DdTop_GPIO_CM0_P16: IO_PMC.GPIO.DDR.bit.P16 = direction; break;
		case DdTop_GPIO_CM0_P17: IO_PMC.GPIO.DDR.bit.P17 = direction; break;
		case DdTop_GPIO_CM0_P20: IO_PMC.GPIO.DDR.bit.P20 = direction; break;
		case DdTop_GPIO_CM0_P21: IO_PMC.GPIO.DDR.bit.P21 = direction; break;
		case DdTop_GPIO_CM0_P22: IO_PMC.GPIO.DDR.bit.P22 = direction; break;
		case DdTop_GPIO_CM0_P23: IO_PMC.GPIO.DDR.bit.P23 = direction; break;
		case DdTop_GPIO_CM0_P24: IO_PMC.GPIO.DDR.bit.P24 = direction; break;
		case DdTop_GPIO_CM0_P25: IO_PMC.GPIO.DDR.bit.P25 = direction; break;
		case DdTop_GPIO_CM0_P26: IO_PMC.GPIO.DDR.bit.P26 = direction; break;
		case DdTop_GPIO_CM0_P27: IO_PMC.GPIO.DDR.bit.P27 = direction; break;
		case DdTop_GPIO_CM0_P30: IO_PMC.GPIO.DDR.bit.P30 = direction; break;
		case DdTop_GPIO_CM0_P31: IO_PMC.GPIO.DDR.bit.P31 = direction; break;
		case DdTop_GPIO_CM0_P32: IO_PMC.GPIO.DDR.bit.P32 = direction; break;
		case DdTop_GPIO_CM0_P33: IO_PMC.GPIO.DDR.bit.P33 = direction; break;
		case DdTop_GPIO_CM0_P34: IO_PMC.GPIO.DDR.bit.P34 = direction; break;
		case DdTop_GPIO_CM0_P35: IO_PMC.GPIO.DDR.bit.P35 = direction; break;
		case DdTop_GPIO_CM0_P36: IO_PMC.GPIO.DDR.bit.P36 = direction; break;
		case DdTop_GPIO_CM0_P37: IO_PMC.GPIO.DDR.bit.P37 = direction; break;
		case DdTop_GPIO_CM0_P44: IO_PMC.GPIO.DDR.bit.P44 = direction; break;
		case DdTop_GPIO_CM0_P45: IO_PMC.GPIO.DDR.bit.P45 = direction; break;
		case DdTop_GPIO_CM0_P46: IO_PMC.GPIO.DDR.bit.P46 = direction; break;
		default:
			DdToptwo_STOP_GPIO_CLK_WITH_CS();
			Ddim_Print(("dd_toptwo_set_gpio_cm0_direction() error. port not exist.\n"));
			return DdTopone_INPUT_PARAM_ERROR;
	}

	Dd_ARM_Dsb_Pou();
	DdToptwo_STOP_GPIO_CLK_WITH_CS();

	return D_DDIM_OK;
}

INT32 dd_toptwo_get_gpio_cm0_direction(DdToptwo *self, DdTop_GPIO_CM0_PORT port, UCHAR* direction )
{
#ifdef DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL
	INT32 s;
#endif // DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL

#ifdef CO_PARAM_CHECK
	if( port >= DdTop_GPIO_CM0_PORT_MAX ) {
		Ddim_Assertion(("dd_toptwo_get_gpio_cm0_direction() error. port parameters is abnormal.\n"));
		return DdTopone_INPUT_PARAM_ERROR;
	}
	if( direction == NULL ) {
		Ddim_Assertion(("dd_toptwo_get_gpio_cm0_direction() error. direction parameters is abnormal.\n"));
		return DdTopone_INPUT_PARAM_ERROR;
	}
#endif

	DdToptwo_START_GPIO_CLK_WITH_CS();

	switch( port ) {
		case DdTop_GPIO_CM0_P00: *direction = IO_PMC.GPIO.DDR.bit.P00; break;
		case DdTop_GPIO_CM0_P01: *direction = IO_PMC.GPIO.DDR.bit.P01; break;
		case DdTop_GPIO_CM0_P02: *direction = IO_PMC.GPIO.DDR.bit.P02; break;
		case DdTop_GPIO_CM0_P03: *direction = IO_PMC.GPIO.DDR.bit.P03; break;
		case DdTop_GPIO_CM0_P04: *direction = IO_PMC.GPIO.DDR.bit.P04; break;
		case DdTop_GPIO_CM0_P05: *direction = IO_PMC.GPIO.DDR.bit.P05; break;
		case DdTop_GPIO_CM0_P06: *direction = IO_PMC.GPIO.DDR.bit.P06; break;
		case DdTop_GPIO_CM0_P07: *direction = IO_PMC.GPIO.DDR.bit.P07; break;
		case DdTop_GPIO_CM0_P10: *direction = IO_PMC.GPIO.DDR.bit.P10; break;
		case DdTop_GPIO_CM0_P11: *direction = IO_PMC.GPIO.DDR.bit.P11; break;
		case DdTop_GPIO_CM0_P12: *direction = IO_PMC.GPIO.DDR.bit.P12; break;
		case DdTop_GPIO_CM0_P13: *direction = IO_PMC.GPIO.DDR.bit.P13; break;
		case DdTop_GPIO_CM0_P14: *direction = IO_PMC.GPIO.DDR.bit.P14; break;
		case DdTop_GPIO_CM0_P15: *direction = IO_PMC.GPIO.DDR.bit.P15; break;
		case DdTop_GPIO_CM0_P16: *direction = IO_PMC.GPIO.DDR.bit.P16; break;
		case DdTop_GPIO_CM0_P17: *direction = IO_PMC.GPIO.DDR.bit.P17; break;
		case DdTop_GPIO_CM0_P20: *direction = IO_PMC.GPIO.DDR.bit.P20; break;
		case DdTop_GPIO_CM0_P21: *direction = IO_PMC.GPIO.DDR.bit.P21; break;
		case DdTop_GPIO_CM0_P22: *direction = IO_PMC.GPIO.DDR.bit.P22; break;
		case DdTop_GPIO_CM0_P23: *direction = IO_PMC.GPIO.DDR.bit.P23; break;
		case DdTop_GPIO_CM0_P24: *direction = IO_PMC.GPIO.DDR.bit.P24; break;
		case DdTop_GPIO_CM0_P25: *direction = IO_PMC.GPIO.DDR.bit.P25; break;
		case DdTop_GPIO_CM0_P26: *direction = IO_PMC.GPIO.DDR.bit.P26; break;
		case DdTop_GPIO_CM0_P27: *direction = IO_PMC.GPIO.DDR.bit.P27; break;
		case DdTop_GPIO_CM0_P30: *direction = IO_PMC.GPIO.DDR.bit.P30; break;
		case DdTop_GPIO_CM0_P31: *direction = IO_PMC.GPIO.DDR.bit.P31; break;
		case DdTop_GPIO_CM0_P32: *direction = IO_PMC.GPIO.DDR.bit.P32; break;
		case DdTop_GPIO_CM0_P33: *direction = IO_PMC.GPIO.DDR.bit.P33; break;
		case DdTop_GPIO_CM0_P34: *direction = IO_PMC.GPIO.DDR.bit.P34; break;
		case DdTop_GPIO_CM0_P35: *direction = IO_PMC.GPIO.DDR.bit.P35; break;
		case DdTop_GPIO_CM0_P36: *direction = IO_PMC.GPIO.DDR.bit.P36; break;
		case DdTop_GPIO_CM0_P37: *direction = IO_PMC.GPIO.DDR.bit.P37; break;
		case DdTop_GPIO_CM0_P44: *direction = IO_PMC.GPIO.DDR.bit.P44; break;
		case DdTop_GPIO_CM0_P45: *direction = IO_PMC.GPIO.DDR.bit.P45; break;
		case DdTop_GPIO_CM0_P46: *direction = IO_PMC.GPIO.DDR.bit.P46; break;
		default:
			DdToptwo_STOP_GPIO_CLK_WITH_CS();
			Ddim_Print(("dd_toptwo_get_gpio_cm0_direction() error. port not exist.\n"));
			return DdTopone_INPUT_PARAM_ERROR;
	}

	DdToptwo_STOP_GPIO_CLK_WITH_CS();

	return D_DDIM_OK;
}

INT32 dd_toptwo_set_gpio_cm0_pull_up_down_enable(DdToptwo *self, DdTop_GPIO_CM0_PORT port, UCHAR enable )
{
#ifdef DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL
	INT32 s;
#endif // DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL

#ifdef CO_PARAM_CHECK
	if( port >= DdTop_GPIO_CM0_PORT_MAX ) {
		Ddim_Assertion(("dd_toptwo_set_gpio_cm0_pull_up_down_enable() error. port parameters is abnormal.\n"));
		return DdTopone_INPUT_PARAM_ERROR;
	}
	if( enable > DdToptwo_GPIO_PUD_ON ) {
		Ddim_Assertion(("dd_toptwo_set_gpio_cm0_pull_up_down_enable() error. enable parameters is abnormal.\n"));
		return DdTopone_INPUT_PARAM_ERROR;
	}
#endif

	DdToptwo_START_GPIO_CLK_WITH_CS();

	switch( port ) {
		case DdTop_GPIO_CM0_P00: IO_PMC.GPIO.PUDER.bit.P00 = enable; break;
		case DdTop_GPIO_CM0_P01: IO_PMC.GPIO.PUDER.bit.P01 = enable; break;
		case DdTop_GPIO_CM0_P02: IO_PMC.GPIO.PUDER.bit.P02 = enable; break;
		case DdTop_GPIO_CM0_P03: IO_PMC.GPIO.PUDER.bit.P03 = enable; break;
		case DdTop_GPIO_CM0_P04: IO_PMC.GPIO.PUDER.bit.P04 = enable; break;
		case DdTop_GPIO_CM0_P05: IO_PMC.GPIO.PUDER.bit.P05 = enable; break;
		case DdTop_GPIO_CM0_P06: IO_PMC.GPIO.PUDER.bit.P06 = enable; break;
		case DdTop_GPIO_CM0_P07: IO_PMC.GPIO.PUDER.bit.P07 = enable; break;
		case DdTop_GPIO_CM0_P10: IO_PMC.GPIO.PUDER.bit.P10 = enable; break;
		case DdTop_GPIO_CM0_P11: IO_PMC.GPIO.PUDER.bit.P11 = enable; break;
		case DdTop_GPIO_CM0_P12: IO_PMC.GPIO.PUDER.bit.P12 = enable; break;
		case DdTop_GPIO_CM0_P13: IO_PMC.GPIO.PUDER.bit.P13 = enable; break;
		case DdTop_GPIO_CM0_P14: IO_PMC.GPIO.PUDER.bit.P14 = enable; break;
		case DdTop_GPIO_CM0_P15: IO_PMC.GPIO.PUDER.bit.P15 = enable; break;
		case DdTop_GPIO_CM0_P16: IO_PMC.GPIO.PUDER.bit.P16 = enable; break;
		case DdTop_GPIO_CM0_P17: IO_PMC.GPIO.PUDER.bit.P17 = enable; break;
		case DdTop_GPIO_CM0_P20: IO_PMC.GPIO.PUDER.bit.P20 = enable; break;
		case DdTop_GPIO_CM0_P21: IO_PMC.GPIO.PUDER.bit.P21 = enable; break;
		case DdTop_GPIO_CM0_P22: IO_PMC.GPIO.PUDER.bit.P22 = enable; break;
		case DdTop_GPIO_CM0_P23: IO_PMC.GPIO.PUDER.bit.P23 = enable; break;
		case DdTop_GPIO_CM0_P24: IO_PMC.GPIO.PUDER.bit.P24 = enable; break;
		case DdTop_GPIO_CM0_P25: IO_PMC.GPIO.PUDER.bit.P25 = enable; break;
		case DdTop_GPIO_CM0_P26: IO_PMC.GPIO.PUDER.bit.P26 = enable; break;
		case DdTop_GPIO_CM0_P27: IO_PMC.GPIO.PUDER.bit.P27 = enable; break;
		case DdTop_GPIO_CM0_P30: IO_PMC.GPIO.PUDER.bit.P30 = enable; break;
		case DdTop_GPIO_CM0_P31: IO_PMC.GPIO.PUDER.bit.P31 = enable; break;
		case DdTop_GPIO_CM0_P32: IO_PMC.GPIO.PUDER.bit.P32 = enable; break;
		case DdTop_GPIO_CM0_P33: IO_PMC.GPIO.PUDER.bit.P33 = enable; break;
		case DdTop_GPIO_CM0_P34: IO_PMC.GPIO.PUDER.bit.P34 = enable; break;
		case DdTop_GPIO_CM0_P35: IO_PMC.GPIO.PUDER.bit.P35 = enable; break;
		case DdTop_GPIO_CM0_P36: IO_PMC.GPIO.PUDER.bit.P36 = enable; break;
		case DdTop_GPIO_CM0_P37: IO_PMC.GPIO.PUDER.bit.P37 = enable; break;
		case DdTop_GPIO_CM0_P44: IO_PMC.GPIO.PUDER.bit.P44 = enable; break;
		case DdTop_GPIO_CM0_P45: IO_PMC.GPIO.PUDER.bit.P45 = enable; break;
		case DdTop_GPIO_CM0_P46: IO_PMC.GPIO.PUDER.bit.P46 = enable; break;
		default:
			DdToptwo_STOP_GPIO_CLK_WITH_CS();
			Ddim_Print(("dd_toptwo_set_gpio_cm0_pull_up_down_enable() error. port not exist.\n"));
			return DdTopone_INPUT_PARAM_ERROR;
	}

	Dd_ARM_Dsb_Pou();
	DdToptwo_STOP_GPIO_CLK_WITH_CS();

	return D_DDIM_OK;
}

INT32 dd_toptwo_get_gpio_cm0_pull_up_down_enable(DdToptwo *self, DdTop_GPIO_CM0_PORT port, UCHAR *enable )
{
#ifdef DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL
	INT32 s;
#endif // DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL

#ifdef CO_PARAM_CHECK
	if( port >= DdTop_GPIO_CM0_PORT_MAX ) {
		Ddim_Assertion(("dd_toptwo_get_gpio_cm0_pull_up_down_enable() error. port parameters is abnormal.\n"));
		return DdTopone_INPUT_PARAM_ERROR;
	}
	if( enable == NULL ) {
		Ddim_Assertion(("dd_toptwo_get_gpio_cm0_pull_up_down_enable() error. enable parameters is abnormal.\n"));
		return DdTopone_INPUT_PARAM_ERROR;
	}
#endif

	DdToptwo_START_GPIO_CLK_WITH_CS();

	switch( port ) {
		case DdTop_GPIO_CM0_P00: *enable = IO_PMC.GPIO.PUDER.bit.P00; break;
		case DdTop_GPIO_CM0_P01: *enable = IO_PMC.GPIO.PUDER.bit.P01; break;
		case DdTop_GPIO_CM0_P02: *enable = IO_PMC.GPIO.PUDER.bit.P02; break;
		case DdTop_GPIO_CM0_P03: *enable = IO_PMC.GPIO.PUDER.bit.P03; break;
		case DdTop_GPIO_CM0_P04: *enable = IO_PMC.GPIO.PUDER.bit.P04; break;
		case DdTop_GPIO_CM0_P05: *enable = IO_PMC.GPIO.PUDER.bit.P05; break;
		case DdTop_GPIO_CM0_P06: *enable = IO_PMC.GPIO.PUDER.bit.P06; break;
		case DdTop_GPIO_CM0_P07: *enable = IO_PMC.GPIO.PUDER.bit.P07; break;
		case DdTop_GPIO_CM0_P10: *enable = IO_PMC.GPIO.PUDER.bit.P10; break;
		case DdTop_GPIO_CM0_P11: *enable = IO_PMC.GPIO.PUDER.bit.P11; break;
		case DdTop_GPIO_CM0_P12: *enable = IO_PMC.GPIO.PUDER.bit.P12; break;
		case DdTop_GPIO_CM0_P13: *enable = IO_PMC.GPIO.PUDER.bit.P13; break;
		case DdTop_GPIO_CM0_P14: *enable = IO_PMC.GPIO.PUDER.bit.P14; break;
		case DdTop_GPIO_CM0_P15: *enable = IO_PMC.GPIO.PUDER.bit.P15; break;
		case DdTop_GPIO_CM0_P16: *enable = IO_PMC.GPIO.PUDER.bit.P16; break;
		case DdTop_GPIO_CM0_P17: *enable = IO_PMC.GPIO.PUDER.bit.P17; break;
		case DdTop_GPIO_CM0_P20: *enable = IO_PMC.GPIO.PUDER.bit.P20; break;
		case DdTop_GPIO_CM0_P21: *enable = IO_PMC.GPIO.PUDER.bit.P21; break;
		case DdTop_GPIO_CM0_P22: *enable = IO_PMC.GPIO.PUDER.bit.P22; break;
		case DdTop_GPIO_CM0_P23: *enable = IO_PMC.GPIO.PUDER.bit.P23; break;
		case DdTop_GPIO_CM0_P24: *enable = IO_PMC.GPIO.PUDER.bit.P24; break;
		case DdTop_GPIO_CM0_P25: *enable = IO_PMC.GPIO.PUDER.bit.P25; break;
		case DdTop_GPIO_CM0_P26: *enable = IO_PMC.GPIO.PUDER.bit.P26; break;
		case DdTop_GPIO_CM0_P27: *enable = IO_PMC.GPIO.PUDER.bit.P27; break;
		case DdTop_GPIO_CM0_P30: *enable = IO_PMC.GPIO.PUDER.bit.P30; break;
		case DdTop_GPIO_CM0_P31: *enable = IO_PMC.GPIO.PUDER.bit.P31; break;
		case DdTop_GPIO_CM0_P32: *enable = IO_PMC.GPIO.PUDER.bit.P32; break;
		case DdTop_GPIO_CM0_P33: *enable = IO_PMC.GPIO.PUDER.bit.P33; break;
		case DdTop_GPIO_CM0_P34: *enable = IO_PMC.GPIO.PUDER.bit.P34; break;
		case DdTop_GPIO_CM0_P35: *enable = IO_PMC.GPIO.PUDER.bit.P35; break;
		case DdTop_GPIO_CM0_P36: *enable = IO_PMC.GPIO.PUDER.bit.P36; break;
		case DdTop_GPIO_CM0_P37: *enable = IO_PMC.GPIO.PUDER.bit.P37; break;
		case DdTop_GPIO_CM0_P44: *enable = IO_PMC.GPIO.PUDER.bit.P44; break;
		case DdTop_GPIO_CM0_P45: *enable = IO_PMC.GPIO.PUDER.bit.P45; break;
		case DdTop_GPIO_CM0_P46: *enable = IO_PMC.GPIO.PUDER.bit.P46; break;
		default:
			DdToptwo_STOP_GPIO_CLK_WITH_CS();
			Ddim_Print(("Dd_PMC_GPIO_Get_Gpio_Pull_Up_Down_Enable() error. port not exist.\n"));
			return DdTopone_INPUT_PARAM_ERROR;
	}

	DdToptwo_STOP_GPIO_CLK_WITH_CS();

	return D_DDIM_OK;
}

INT32 dd_toptwo_set_gpio_cm0_pull_up_down_ctrl(DdToptwo *self, DdTop_GPIO_CM0_PORT port, UCHAR control )
{
#ifdef DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL
	INT32 s;
#endif // DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL

#ifdef CO_PARAM_CHECK
	if( port >= DdTop_GPIO_CM0_PORT_MAX ) {
		Ddim_Assertion(("dd_toptwo_set_gpio_cm0_pull_up_down_ctrl() error. port parameters is abnormal.\n"));
		return DdTopone_INPUT_PARAM_ERROR;
	}
	if( control > DdToptwo_GPIO_PUD_UP ) {
		Ddim_Assertion(("dd_toptwo_set_gpio_cm0_pull_up_down_ctrl() error. enable parameters is abnormal.\n"));
		return DdTopone_INPUT_PARAM_ERROR;
	}
#endif

	DdToptwo_START_GPIO_CLK_WITH_CS();

	switch( port ) {
		case DdTop_GPIO_CM0_P00: IO_PMC.GPIO.PUDCR.bit.P00 = control; break;
		case DdTop_GPIO_CM0_P01: IO_PMC.GPIO.PUDCR.bit.P01 = control; break;
		case DdTop_GPIO_CM0_P02: IO_PMC.GPIO.PUDCR.bit.P02 = control; break;
		case DdTop_GPIO_CM0_P03: IO_PMC.GPIO.PUDCR.bit.P03 = control; break;
		case DdTop_GPIO_CM0_P04: IO_PMC.GPIO.PUDCR.bit.P04 = control; break;
		case DdTop_GPIO_CM0_P05: IO_PMC.GPIO.PUDCR.bit.P05 = control; break;
		case DdTop_GPIO_CM0_P06: IO_PMC.GPIO.PUDCR.bit.P06 = control; break;
		case DdTop_GPIO_CM0_P07: IO_PMC.GPIO.PUDCR.bit.P07 = control; break;
		case DdTop_GPIO_CM0_P10: IO_PMC.GPIO.PUDCR.bit.P10 = control; break;
		case DdTop_GPIO_CM0_P11: IO_PMC.GPIO.PUDCR.bit.P11 = control; break;
		case DdTop_GPIO_CM0_P12: IO_PMC.GPIO.PUDCR.bit.P12 = control; break;
		case DdTop_GPIO_CM0_P13: IO_PMC.GPIO.PUDCR.bit.P13 = control; break;
		case DdTop_GPIO_CM0_P14: IO_PMC.GPIO.PUDCR.bit.P14 = control; break;
		case DdTop_GPIO_CM0_P15: IO_PMC.GPIO.PUDCR.bit.P15 = control; break;
		case DdTop_GPIO_CM0_P16: IO_PMC.GPIO.PUDCR.bit.P16 = control; break;
		case DdTop_GPIO_CM0_P17: IO_PMC.GPIO.PUDCR.bit.P17 = control; break;
		case DdTop_GPIO_CM0_P20: IO_PMC.GPIO.PUDCR.bit.P20 = control; break;
		case DdTop_GPIO_CM0_P21: IO_PMC.GPIO.PUDCR.bit.P21 = control; break;
		case DdTop_GPIO_CM0_P22: IO_PMC.GPIO.PUDCR.bit.P22 = control; break;
		case DdTop_GPIO_CM0_P23: IO_PMC.GPIO.PUDCR.bit.P23 = control; break;
		case DdTop_GPIO_CM0_P24: IO_PMC.GPIO.PUDCR.bit.P24 = control; break;
		case DdTop_GPIO_CM0_P25: IO_PMC.GPIO.PUDCR.bit.P25 = control; break;
		case DdTop_GPIO_CM0_P26: IO_PMC.GPIO.PUDCR.bit.P26 = control; break;
		case DdTop_GPIO_CM0_P27: IO_PMC.GPIO.PUDCR.bit.P27 = control; break;
		case DdTop_GPIO_CM0_P30: IO_PMC.GPIO.PUDCR.bit.P30 = control; break;
		case DdTop_GPIO_CM0_P31: IO_PMC.GPIO.PUDCR.bit.P31 = control; break;
		case DdTop_GPIO_CM0_P32: IO_PMC.GPIO.PUDCR.bit.P32 = control; break;
		case DdTop_GPIO_CM0_P33: IO_PMC.GPIO.PUDCR.bit.P33 = control; break;
		case DdTop_GPIO_CM0_P34: IO_PMC.GPIO.PUDCR.bit.P34 = control; break;
		case DdTop_GPIO_CM0_P35: IO_PMC.GPIO.PUDCR.bit.P35 = control; break;
		case DdTop_GPIO_CM0_P36: IO_PMC.GPIO.PUDCR.bit.P36 = control; break;
		case DdTop_GPIO_CM0_P37: IO_PMC.GPIO.PUDCR.bit.P37 = control; break;
		case DdTop_GPIO_CM0_P44: IO_PMC.GPIO.PUDCR.bit.P44 = control; break;
		case DdTop_GPIO_CM0_P45: IO_PMC.GPIO.PUDCR.bit.P45 = control; break;
		case DdTop_GPIO_CM0_P46: IO_PMC.GPIO.PUDCR.bit.P46 = control; break;
		default:
			DdToptwo_STOP_GPIO_CLK_WITH_CS();
			Ddim_Print(("dd_toptwo_set_gpio_cm0_pull_up_down_ctrl() error. port not exist.\n"));
			return DdTopone_INPUT_PARAM_ERROR;
	}

	Dd_ARM_Dsb_Pou();
	DdToptwo_STOP_GPIO_CLK_WITH_CS();

	return D_DDIM_OK;
}

INT32 dd_toptwo_get_gpio_cm0_pull_up_down_ctrl(DdToptwo *self, DdTop_GPIO_CM0_PORT port, UCHAR* control )
{
#ifdef DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL
	INT32 s;
#endif // DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL

#ifdef CO_PARAM_CHECK
	if( port >= DdTop_GPIO_CM0_PORT_MAX ) {
		Ddim_Assertion(("dd_toptwo_get_gpio_cm0_pull_up_down_ctrl() error. port parameters is abnormal.\n"));
		return DdTopone_INPUT_PARAM_ERROR;
	}
	if( control == NULL ) {
		Ddim_Assertion(("dd_toptwo_get_gpio_cm0_pull_up_down_ctrl() error. enable parameters is abnormal.\n"));
		return DdTopone_INPUT_PARAM_ERROR;
	}
#endif

	DdToptwo_START_GPIO_CLK_WITH_CS();

	switch( port ) {
		case DdTop_GPIO_CM0_P00: *control = IO_PMC.GPIO.PUDCR.bit.P00; break;
		case DdTop_GPIO_CM0_P01: *control = IO_PMC.GPIO.PUDCR.bit.P01; break;
		case DdTop_GPIO_CM0_P02: *control = IO_PMC.GPIO.PUDCR.bit.P02; break;
		case DdTop_GPIO_CM0_P03: *control = IO_PMC.GPIO.PUDCR.bit.P03; break;
		case DdTop_GPIO_CM0_P04: *control = IO_PMC.GPIO.PUDCR.bit.P04; break;
		case DdTop_GPIO_CM0_P05: *control = IO_PMC.GPIO.PUDCR.bit.P05; break;
		case DdTop_GPIO_CM0_P06: *control = IO_PMC.GPIO.PUDCR.bit.P06; break;
		case DdTop_GPIO_CM0_P07: *control = IO_PMC.GPIO.PUDCR.bit.P07; break;
		case DdTop_GPIO_CM0_P10: *control = IO_PMC.GPIO.PUDCR.bit.P10; break;
		case DdTop_GPIO_CM0_P11: *control = IO_PMC.GPIO.PUDCR.bit.P11; break;
		case DdTop_GPIO_CM0_P12: *control = IO_PMC.GPIO.PUDCR.bit.P12; break;
		case DdTop_GPIO_CM0_P13: *control = IO_PMC.GPIO.PUDCR.bit.P13; break;
		case DdTop_GPIO_CM0_P14: *control = IO_PMC.GPIO.PUDCR.bit.P14; break;
		case DdTop_GPIO_CM0_P15: *control = IO_PMC.GPIO.PUDCR.bit.P15; break;
		case DdTop_GPIO_CM0_P16: *control = IO_PMC.GPIO.PUDCR.bit.P16; break;
		case DdTop_GPIO_CM0_P17: *control = IO_PMC.GPIO.PUDCR.bit.P17; break;
		case DdTop_GPIO_CM0_P20: *control = IO_PMC.GPIO.PUDCR.bit.P20; break;
		case DdTop_GPIO_CM0_P21: *control = IO_PMC.GPIO.PUDCR.bit.P21; break;
		case DdTop_GPIO_CM0_P22: *control = IO_PMC.GPIO.PUDCR.bit.P22; break;
		case DdTop_GPIO_CM0_P23: *control = IO_PMC.GPIO.PUDCR.bit.P23; break;
		case DdTop_GPIO_CM0_P24: *control = IO_PMC.GPIO.PUDCR.bit.P24; break;
		case DdTop_GPIO_CM0_P25: *control = IO_PMC.GPIO.PUDCR.bit.P25; break;
		case DdTop_GPIO_CM0_P26: *control = IO_PMC.GPIO.PUDCR.bit.P26; break;
		case DdTop_GPIO_CM0_P27: *control = IO_PMC.GPIO.PUDCR.bit.P27; break;
		case DdTop_GPIO_CM0_P30: *control = IO_PMC.GPIO.PUDCR.bit.P30; break;
		case DdTop_GPIO_CM0_P31: *control = IO_PMC.GPIO.PUDCR.bit.P31; break;
		case DdTop_GPIO_CM0_P32: *control = IO_PMC.GPIO.PUDCR.bit.P32; break;
		case DdTop_GPIO_CM0_P33: *control = IO_PMC.GPIO.PUDCR.bit.P33; break;
		case DdTop_GPIO_CM0_P34: *control = IO_PMC.GPIO.PUDCR.bit.P34; break;
		case DdTop_GPIO_CM0_P35: *control = IO_PMC.GPIO.PUDCR.bit.P35; break;
		case DdTop_GPIO_CM0_P36: *control = IO_PMC.GPIO.PUDCR.bit.P36; break;
		case DdTop_GPIO_CM0_P37: *control = IO_PMC.GPIO.PUDCR.bit.P37; break;
		case DdTop_GPIO_CM0_P44: *control = IO_PMC.GPIO.PUDCR.bit.P44; break;
		case DdTop_GPIO_CM0_P45: *control = IO_PMC.GPIO.PUDCR.bit.P45; break;
		case DdTop_GPIO_CM0_P46: *control = IO_PMC.GPIO.PUDCR.bit.P46; break;
		default:
			DdToptwo_STOP_GPIO_CLK_WITH_CS();
			Ddim_Print(("dd_toptwo_get_gpio_cm0_pull_up_down_ctrl() error. port not exist.\n"));
			return DdTopone_INPUT_PARAM_ERROR;
	}

	DdToptwo_STOP_GPIO_CLK_WITH_CS();

	return D_DDIM_OK;
}

INT32 dd_toptwo_set_gpio_cm0_status(DdToptwo *self, DdTop_GPIO_CM0_PORT port, UCHAR status )
{
#ifdef DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL
	INT32 s;
#endif // DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL
	int						index = 0;
	union io_pmc_gpio_pdr	pdr;

#ifdef CO_PARAM_CHECK
	if( port >= DdTop_GPIO_CM0_PORT_MAX ) {
		Ddim_Assertion(("dd_toptwo_set_gpio_cm0_status() error. port parameters is abnormal.\n"));
		return DdTopone_INPUT_PARAM_ERROR;
	}
	if( status > DdToptwo_GPIO_STATUS_HIGH ) {
		Ddim_Assertion(("dd_toptwo_set_gpio_cm0_status() error. enable parameters is abnormal.\n"));
		return DdTopone_INPUT_PARAM_ERROR;
	}
#endif
	memset(&pdr, 0, sizeof(pdr));

	DdToptwo_START_GPIO_CLK_WITH_CS();

	switch( port ) {
		case DdTop_GPIO_CM0_P00: pdr.bit.P00 = status; pdr.bit.PWE00 = 1; index = 0; break;
		case DdTop_GPIO_CM0_P01: pdr.bit.P01 = status; pdr.bit.PWE01 = 1; index = 0; break;
		case DdTop_GPIO_CM0_P02: pdr.bit.P02 = status; pdr.bit.PWE02 = 1; index = 0; break;
		case DdTop_GPIO_CM0_P03: pdr.bit.P03 = status; pdr.bit.PWE03 = 1; index = 0; break;
		case DdTop_GPIO_CM0_P04: pdr.bit.P04 = status; pdr.bit.PWE04 = 1; index = 0; break;
		case DdTop_GPIO_CM0_P05: pdr.bit.P05 = status; pdr.bit.PWE05 = 1; index = 0; break;
		case DdTop_GPIO_CM0_P06: pdr.bit.P06 = status; pdr.bit.PWE06 = 1; index = 0; break;
		case DdTop_GPIO_CM0_P07: pdr.bit.P07 = status; pdr.bit.PWE07 = 1; index = 0; break;
		case DdTop_GPIO_CM0_P10: pdr.bit.P10 = status; pdr.bit.PWE10 = 1; index = 0; break;
		case DdTop_GPIO_CM0_P11: pdr.bit.P11 = status; pdr.bit.PWE11 = 1; index = 0; break;
		case DdTop_GPIO_CM0_P12: pdr.bit.P12 = status; pdr.bit.PWE12 = 1; index = 0; break;
		case DdTop_GPIO_CM0_P13: pdr.bit.P13 = status; pdr.bit.PWE13 = 1; index = 0; break;
		case DdTop_GPIO_CM0_P14: pdr.bit.P14 = status; pdr.bit.PWE14 = 1; index = 0; break;
		case DdTop_GPIO_CM0_P15: pdr.bit.P15 = status; pdr.bit.PWE15 = 1; index = 0; break;
		case DdTop_GPIO_CM0_P16: pdr.bit.P16 = status; pdr.bit.PWE16 = 1; index = 0; break;
		case DdTop_GPIO_CM0_P17: pdr.bit.P17 = status; pdr.bit.PWE17 = 1; index = 0; break;
		case DdTop_GPIO_CM0_P20: pdr.bit.P20 = status; pdr.bit.PWE20 = 1; index = 1; break;
		case DdTop_GPIO_CM0_P21: pdr.bit.P21 = status; pdr.bit.PWE21 = 1; index = 1; break;
		case DdTop_GPIO_CM0_P22: pdr.bit.P22 = status; pdr.bit.PWE22 = 1; index = 1; break;
		case DdTop_GPIO_CM0_P23: pdr.bit.P23 = status; pdr.bit.PWE23 = 1; index = 1; break;
		case DdTop_GPIO_CM0_P24: pdr.bit.P24 = status; pdr.bit.PWE24 = 1; index = 1; break;
		case DdTop_GPIO_CM0_P25: pdr.bit.P25 = status; pdr.bit.PWE25 = 1; index = 1; break;
		case DdTop_GPIO_CM0_P26: pdr.bit.P26 = status; pdr.bit.PWE26 = 1; index = 1; break;
		case DdTop_GPIO_CM0_P27: pdr.bit.P27 = status; pdr.bit.PWE27 = 1; index = 1; break;
		case DdTop_GPIO_CM0_P30: pdr.bit.P30 = status; pdr.bit.PWE30 = 1; index = 1; break;
		case DdTop_GPIO_CM0_P31: pdr.bit.P31 = status; pdr.bit.PWE31 = 1; index = 1; break;
		case DdTop_GPIO_CM0_P32: pdr.bit.P32 = status; pdr.bit.PWE32 = 1; index = 1; break;
		case DdTop_GPIO_CM0_P33: pdr.bit.P33 = status; pdr.bit.PWE33 = 1; index = 1; break;
		case DdTop_GPIO_CM0_P34: pdr.bit.P34 = status; pdr.bit.PWE34 = 1; index = 1; break;
		case DdTop_GPIO_CM0_P35: pdr.bit.P35 = status; pdr.bit.PWE35 = 1; index = 1; break;
		case DdTop_GPIO_CM0_P36: pdr.bit.P36 = status; pdr.bit.PWE36 = 1; index = 1; break;
		case DdTop_GPIO_CM0_P37: pdr.bit.P37 = status; pdr.bit.PWE37 = 1; index = 1; break;
		case DdTop_GPIO_CM0_P44: pdr.bit.P44 = status; pdr.bit.PWE44 = 1; index = 2; break;
		case DdTop_GPIO_CM0_P45: pdr.bit.P45 = status; pdr.bit.PWE45 = 1; index = 2; break;
		case DdTop_GPIO_CM0_P46: pdr.bit.P46 = status; pdr.bit.PWE46 = 1; index = 2; break;
		default:
			DdToptwo_STOP_GPIO_CLK_WITH_CS();
			Ddim_Print(("dd_toptwo_set_gpio_cm0_status() error. port not exist.\n"));
			return DdTopone_INPUT_PARAM_ERROR;
	}
	// Set PDR
	IO_PMC.GPIO.PDR.word[index] = pdr.word[index];

	Dd_ARM_Dsb_Pou();
	DdToptwo_STOP_GPIO_CLK_WITH_CS();

	return D_DDIM_OK;
}

/**
Get the state of a selectable GPIO CM0 port.<br>
It is get from the PDR(Port Data Register) value.
@param [in]  port		Port name. See @ref DdTop_GPIO_CM0_PORT
@param [out] status		Port status.
						  <ul>
							  <li>0:@ref DdToptwo_GPIO_STATUS_LOW
							  <li>1:@ref DdToptwo_GPIO_STATUS_HIGH
						  </ul>
@retval D_DDIM_OK					Success.
@retval DdTopone_INPUT_PARAM_ERROR	Error occurred.
*/
INT32 dd_toptwo_get_gpio_cm0_status(DdToptwo *self, DdTop_GPIO_CM0_PORT port, UCHAR* status )
{
#ifdef DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL
	INT32 s;
#endif // DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL

#ifdef CO_PARAM_CHECK
	if( port >= DdTop_GPIO_CM0_PORT_MAX ) {
		Ddim_Assertion(("dd_toptwo_get_gpio_cm0_status() error. port parameters is abnormal.\n"));
		return DdTopone_INPUT_PARAM_ERROR;
	}
	if( status == NULL ) {
		Ddim_Assertion(("dd_toptwo_get_gpio_cm0_status() error. status parameters is abnormal.\n"));
		return DdTopone_INPUT_PARAM_ERROR;
	}
#endif

	DdToptwo_START_GPIO_CLK_WITH_CS();

	switch( port ) {
		case DdTop_GPIO_CM0_P00: *status = IO_PMC.GPIO.PDR.bit.P00; break;
		case DdTop_GPIO_CM0_P01: *status = IO_PMC.GPIO.PDR.bit.P01; break;
		case DdTop_GPIO_CM0_P02: *status = IO_PMC.GPIO.PDR.bit.P02; break;
		case DdTop_GPIO_CM0_P03: *status = IO_PMC.GPIO.PDR.bit.P03; break;
		case DdTop_GPIO_CM0_P04: *status = IO_PMC.GPIO.PDR.bit.P04; break;
		case DdTop_GPIO_CM0_P05: *status = IO_PMC.GPIO.PDR.bit.P05; break;
		case DdTop_GPIO_CM0_P06: *status = IO_PMC.GPIO.PDR.bit.P06; break;
		case DdTop_GPIO_CM0_P07: *status = IO_PMC.GPIO.PDR.bit.P07; break;
		case DdTop_GPIO_CM0_P10: *status = IO_PMC.GPIO.PDR.bit.P10; break;
		case DdTop_GPIO_CM0_P11: *status = IO_PMC.GPIO.PDR.bit.P11; break;
		case DdTop_GPIO_CM0_P12: *status = IO_PMC.GPIO.PDR.bit.P12; break;
		case DdTop_GPIO_CM0_P13: *status = IO_PMC.GPIO.PDR.bit.P13; break;
		case DdTop_GPIO_CM0_P14: *status = IO_PMC.GPIO.PDR.bit.P14; break;
		case DdTop_GPIO_CM0_P15: *status = IO_PMC.GPIO.PDR.bit.P15; break;
		case DdTop_GPIO_CM0_P16: *status = IO_PMC.GPIO.PDR.bit.P16; break;
		case DdTop_GPIO_CM0_P17: *status = IO_PMC.GPIO.PDR.bit.P17; break;
		case DdTop_GPIO_CM0_P20: *status = IO_PMC.GPIO.PDR.bit.P20; break;
		case DdTop_GPIO_CM0_P21: *status = IO_PMC.GPIO.PDR.bit.P21; break;
		case DdTop_GPIO_CM0_P22: *status = IO_PMC.GPIO.PDR.bit.P22; break;
		case DdTop_GPIO_CM0_P23: *status = IO_PMC.GPIO.PDR.bit.P23; break;
		case DdTop_GPIO_CM0_P24: *status = IO_PMC.GPIO.PDR.bit.P24; break;
		case DdTop_GPIO_CM0_P25: *status = IO_PMC.GPIO.PDR.bit.P25; break;
		case DdTop_GPIO_CM0_P26: *status = IO_PMC.GPIO.PDR.bit.P26; break;
		case DdTop_GPIO_CM0_P27: *status = IO_PMC.GPIO.PDR.bit.P27; break;
		case DdTop_GPIO_CM0_P30: *status = IO_PMC.GPIO.PDR.bit.P30; break;
		case DdTop_GPIO_CM0_P31: *status = IO_PMC.GPIO.PDR.bit.P31; break;
		case DdTop_GPIO_CM0_P32: *status = IO_PMC.GPIO.PDR.bit.P32; break;
		case DdTop_GPIO_CM0_P33: *status = IO_PMC.GPIO.PDR.bit.P33; break;
		case DdTop_GPIO_CM0_P34: *status = IO_PMC.GPIO.PDR.bit.P34; break;
		case DdTop_GPIO_CM0_P35: *status = IO_PMC.GPIO.PDR.bit.P35; break;
		case DdTop_GPIO_CM0_P36: *status = IO_PMC.GPIO.PDR.bit.P36; break;
		case DdTop_GPIO_CM0_P37: *status = IO_PMC.GPIO.PDR.bit.P37; break;
		case DdTop_GPIO_CM0_P44: *status = IO_PMC.GPIO.PDR.bit.P44; break;
		case DdTop_GPIO_CM0_P45: *status = IO_PMC.GPIO.PDR.bit.P45; break;
		case DdTop_GPIO_CM0_P46: *status = IO_PMC.GPIO.PDR.bit.P46; break;
		default:
			DdToptwo_STOP_GPIO_CLK_WITH_CS();
			Ddim_Print(("dd_toptwo_get_gpio_cm0_status() error. port not exist.\n"));
			return DdTopone_INPUT_PARAM_ERROR;
	}

	DdToptwo_STOP_GPIO_CLK_WITH_CS();

	return D_DDIM_OK;
}
#endif


/**
Get Frequency of DSP clock
@retval	Hz
*/
ULONG dd_toptwo_get_dspclk(VOID)
{
	// 0:400MHz(=1600MHz/4)
	// 1:266.666MHz(=1600MHz/6)
	// 2:200MHz(=1600MHz/8)
	// 3:100MHz(=1600MHz/16)
	static const UCHAR S_DIVID[] = {4, 6, 8, 16};

	return (DdTopone_1600_PLL_OUT / S_DIVID[DdTopone_Get_CLKSEL8_DSPCLK()]);
}

/**
Get Frequency of AXI bus clock
@retval	Hz
*/
ULONG dd_toptwo_get_aclk(VOID)
{
	// 3:200MHz(=1600MHz/8)
	// 7:100MHz(=1600MHz/16)
	static const UCHAR S_ID[] = {3, 7, 255};
	static const UCHAR S_DIVID[] = {8, 16};

	int i;
	ULONG clock = 0;

	for (i = 0; S_ID[i] != 255; i++) {
		if (DdTopone_Get_CLKSEL9_ACLK() == S_ID[i]) {
			clock = (DdTopone_1600_PLL_OUT / S_DIVID[i]);
			break;
		}
	}

	return clock;
}

/**
Get Frequency of AXI bus EXS clock
@retval	Hz
*/
ULONG dd_toptwo_get_aclkexs(VOID)
{
	// 3:200MHz(=1600MHz/8)
	// 4:160MHz(=1600MHz/10)
	// 5:133.333MHz(=1600MHz/12)
	// 7:100MHz(=1600MHz/16)
	static const UCHAR S_ID[] = {3, 4, 5, 7, 255};
	static const UCHAR S_DIVID[] = {8, 10, 12, 16};

	int i;
	ULONG clock = 0;

	for (i = 0; S_ID[i] != 255; i ++) {
		if (DdTopone_Get_CLKSEL9_ACLKEXS() == S_ID[i]) {
			clock = (DdTopone_1600_PLL_OUT / S_DIVID[i]);
			break;
		}
	}

	return clock;
}

/**
Get Frequency of AHB bus BMH clock
@retval	Hz
*/
ULONG dd_toptwo_get_hclkbmh(VOID)
{
	// 3:200MHz(=1600MHz/8)
	// 7:100MHz(=1600MHz/16)
	static const UCHAR S_ID[] = {3, 7, 255};
	static const UCHAR S_DIVID[] = {8, 16};

	int i;
	ULONG clock = 0;

	for (i = 0; S_ID[i] != 255; i ++) {
		if (DdTopone_Get_CLKSEL9_HCLKBMH() == S_ID[i]) {
			clock = (DdTopone_1600_PLL_OUT / S_DIVID[i]);
			break;
		}
	}

	return clock;
}

/**
Get Frequency of AHB bus clock
@retval	Hz
*/
ULONG dd_toptwo_get_hclk(VOID)
{
	// 7:100MHz(=1600MHz/16)
	// 15:50MHz(=1600MHz/32)
	static const UCHAR S_ID[] = {7, 15, 255};
	static const UCHAR S_DIVID[] = {16, 32};

	int i;
	ULONG clock = 0;

	for (i = 0; S_ID[i] != 255; i ++) {
		if (DdTopone_Get_CLKSEL9_HCLK() == S_ID[i]) {
			clock = (DdTopone_1600_PLL_OUT / S_DIVID[i]);
			break;
		}
	}

	return clock;
}

/**
Get Frequency of APB bus clock
@retval	Hz
*/
ULONG dd_toptwo_get_pclk(VOID)
{
	// 15:50MHz(=1600MHz/32)
	// 31:25MHz(=1600MHz/64)
	static const UCHAR S_ID[] = {15, 31, 255};
	static const UCHAR S_DIVID[] = {32, 64};

	int i;
	ULONG clock = 0;

	for (i = 0; S_ID[i] != 255; i ++) {
		if (DdTopone_Get_CLKSEL9_PCLK() == S_ID[i]) {
			clock = (DdTopone_1600_PLL_OUT / S_DIVID[i]);
			break;
		}
	}

	return clock;
}

/**
Get Frequency of MXI bus 400 clock
@retval	Hz
*/
ULONG dd_toptwo_get_mclk400(VOID)
{
	// 1:400MHz(=1600MHz/4)
	// 3:200MHz(=1600MHz/8)
	static const UCHAR S_ID[] = {1, 3, 255};
	static const UCHAR S_DIVID[] = {4, 8};

	int i;
	ULONG clock = 0;

	for (i = 0; S_ID[i] != 255; i ++) {
		if (DdTopone_Get_CLKSEL10_MCLK400() == S_ID[i]) {
			clock = (DdTopone_1600_PLL_OUT / S_DIVID[i]);
			break;
		}
	}

	return clock;
}

/**
Get Frequency of MXI bus 200 clock
@retval	Hz
*/
ULONG dd_toptwo_get_mclk200(VOID)
{
	// 3:200MHz(=1600MHz/8)
	// 7:100MHz(=1600MHz/16)
	static const UCHAR S_ID[] = {3, 7, 255};
	static const UCHAR S_DIVID[] = {8, 16};

	int i;
	ULONG clock = 0;

	for (i = 0; S_ID[i] != 255; i ++) {
		if (DdTopone_Get_CLKSEL10_MCLK200() == S_ID[i]) {
			clock = (DdTopone_1600_PLL_OUT / S_DIVID[i]);
			break;
		}
	}

	return clock;
}

/**
Get Frequency of AXI bus 400 clock
@retval	Hz
*/
ULONG dd_toptwo_get_aclk400(VOID)
{
	// 1:400MHz(=1600MHz/4)
	// 3:200MHz(=1600MHz/8)
	static const UCHAR S_ID[] = {1, 3, 255};
	static const UCHAR S_DIVID[] = {4, 8};

	int i;
	ULONG clock = 0;

	for (i = 0; S_ID[i] != 255; i ++) {
		if (DdTopone_Get_CLKSEL10_ACLK400() == S_ID[i]) {
			clock = (DdTopone_1600_PLL_OUT / S_DIVID[i]);
			break;
		}
	}

	return clock;
}

/**
Get Frequency of 3DNR clock
@retval	Hz
*/
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
ULONG dd_toptwo_get_shdrclk(VOID)
{
	// 0: 400MHz(=1600MHz/4)
	// 1: 266.666MHz(=1600MHz/6)
	// 2: 200MHz(=1600MHz/8)
	// 3: 160MHz(=1600MHz/10)
	// 4: 133.333MHz(=1600MHz/12)
	// 5: 100MHz(=1600MHz/16)
	// 6: 80MHz(=1600MHz/20)
	// 7: 66.666MHz(=1600MHz/24)
	static const UCHAR S_DIVID[] = {4, 6, 8, 10, 12, 16, 20, 24};

	return (DdTopone_1600_PLL_OUT / S_DIVID[DdTopone_Get_CLKSEL12_SHDRCLK()]);
}
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
ULONG dd_toptwo_get_shdrclk(VOID)
{
	// 0: 432MHz(=864MHz/2)
	// 8: 400MHz(=1600MHz/4)
	// 9: 266.666MHz(=1600MHz/6)
	// 10: 200MHz(=1600MHz/8)
	// 11: 160MHz(=1600MHz/10)
	// 12: 133.333MHz(=1600MHz/12)
	// 13: 100MHz(=1600MHz/16)
	// 14: 80MHz(=1600MHz/20)
	// 15: 66.666MHz(=1600MHz/24)
	static const UCHAR S_ID[] = {0, 8, 9, 10, 11, 12, 13, 14, 15, 255};
	static const UCHAR S_DIVID[] = {2, 4, 6, 8, 10, 12, 16, 20, 24};
	static const ULONG pllid[] = {DdTopone_864_PLL_OUT, DdTopone_1600_PLL_OUT, DdTopone_1600_PLL_OUT, DdTopone_1600_PLL_OUT, DdTopone_1600_PLL_OUT, DdTopone_1600_PLL_OUT, DdTopone_1600_PLL_OUT, DdTopone_1600_PLL_OUT, DdTopone_1600_PLL_OUT};

	int i;
	ULONG clock = 0;

	for (i = 0; S_ID[i] != 255; i ++) {
		if (DdTopone_Get_CLKSEL12_SHDRCLK() == S_ID[i]) {
			clock = (pllid[i] / S_DIVID[i]);
			break;
		}
	}

	return clock;
}
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

DdToptwo* dd_toptwo_new(void)
{
	DdToptwo *self = g_object_new(DD_TYPE_TOPTWO, NULL);
	return self;
}






