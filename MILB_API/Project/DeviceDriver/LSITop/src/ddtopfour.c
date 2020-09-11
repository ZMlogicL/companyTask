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
#include "ddtopfour.h"


/**
Set the direction of a selectable GPIO port.<br>
It is set to the DDR(Data Direction Register) value.
@param [in]  port		Port name. See @ref DdTop_GPIO_PORT
@param [in]  direction	Direction type.
						  <ul>
							  <li>0:@ref DdToptwo_GPIO_DIR_IN
							  <li>1:@ref DdToptwo_GPIO_DIR_OUT
						  </ul>
@retval D_DDIM_OK					Success.
@retval DdTopone_INPUT_PARAM_ERROR	Error occurred.
*/



INT32 dd_topfour_get_gpio_direction(DdTopfour *self, DdTop_GPIO_PORT port, UCHAR* direction )
{
#ifdef DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL
	INT32 s;
#endif // DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL

#ifdef CO_PARAM_CHECK
	if( port >= DdTop_GPIO_PORT_MAX ) {
		Ddim_Assertion(("dd_topfour_get_gpio_direction() error. port parameters is abnormal.\n"));
		return DdTopone_INPUT_PARAM_ERROR;
	}
	if( direction == NULL ) {
		Ddim_Assertion(("dd_topfour_get_gpio_direction() error. direction parameters is abnormal.\n"));
		return DdTopone_INPUT_PARAM_ERROR;
	}
#endif

	DdToptwo_START_GPIO_CLK_WITH_CS();

	switch( port ) {
		case DdTop_GPIO_P60: *direction = IO_CHIPTOP.DDR.bit.P60; break;
		case DdTop_GPIO_P61: *direction = IO_CHIPTOP.DDR.bit.P61; break;
		case DdTop_GPIO_P62: *direction = IO_CHIPTOP.DDR.bit.P62; break;
		case DdTop_GPIO_P63: *direction = IO_CHIPTOP.DDR.bit.P63; break;
		case DdTop_GPIO_P64: *direction = IO_CHIPTOP.DDR.bit.P64; break;
		case DdTop_GPIO_P65: *direction = IO_CHIPTOP.DDR.bit.P65; break;
		case DdTop_GPIO_P66: *direction = IO_CHIPTOP.DDR.bit.P66; break;
		case DdTop_GPIO_P67: *direction = IO_CHIPTOP.DDR.bit.P67; break;
		case DdTop_GPIO_P70: *direction = IO_CHIPTOP.DDR.bit.P70; break;
		case DdTop_GPIO_P71: *direction = IO_CHIPTOP.DDR.bit.P71; break;
		case DdTop_GPIO_P72: *direction = IO_CHIPTOP.DDR.bit.P72; break;
		case DdTop_GPIO_P73: *direction = IO_CHIPTOP.DDR.bit.P73; break;
		case DdTop_GPIO_P74: *direction = IO_CHIPTOP.DDR.bit.P74; break;
		case DdTop_GPIO_P75: *direction = IO_CHIPTOP.DDR.bit.P75; break;
		case DdTop_GPIO_P76: *direction = IO_CHIPTOP.DDR.bit.P76; break;
		case DdTop_GPIO_P77: *direction = IO_CHIPTOP.DDR.bit.P77; break;
		case DdTop_GPIO_P80: *direction = IO_CHIPTOP.DDR.bit.P80; break;
		case DdTop_GPIO_P81: *direction = IO_CHIPTOP.DDR.bit.P81; break;
		case DdTop_GPIO_P82: *direction = IO_CHIPTOP.DDR.bit.P82; break;
		case DdTop_GPIO_P83: *direction = IO_CHIPTOP.DDR.bit.P83; break;
		case DdTop_GPIO_P84: *direction = IO_CHIPTOP.DDR.bit.P84; break;
		case DdTop_GPIO_P85: *direction = IO_CHIPTOP.DDR.bit.P85; break;
		case DdTop_GPIO_P86: *direction = IO_CHIPTOP.DDR.bit.P86; break;
		case DdTop_GPIO_P87: *direction = IO_CHIPTOP.DDR.bit.P87; break;
		case DdTop_GPIO_P90: *direction = IO_CHIPTOP.DDR.bit.P90; break;
		case DdTop_GPIO_P91: *direction = IO_CHIPTOP.DDR.bit.P91; break;
		case DdTop_GPIO_P92: *direction = IO_CHIPTOP.DDR.bit.P92; break;
		case DdTop_GPIO_P93: *direction = IO_CHIPTOP.DDR.bit.P93; break;
		case DdTop_GPIO_PA0: *direction = IO_CHIPTOP.DDR.bit.PA0; break;
		case DdTop_GPIO_PA1: *direction = IO_CHIPTOP.DDR.bit.PA1; break;
		case DdTop_GPIO_PA2: *direction = IO_CHIPTOP.DDR.bit.PA2; break;
		case DdTop_GPIO_PA3: *direction = IO_CHIPTOP.DDR.bit.PA3; break;
		case DdTop_GPIO_PA4: *direction = IO_CHIPTOP.DDR.bit.PA4; break;
		case DdTop_GPIO_PA5: *direction = IO_CHIPTOP.DDR.bit.PA5; break;
		case DdTop_GPIO_PA6: *direction = IO_CHIPTOP.DDR.bit.PA6; break;
		case DdTop_GPIO_PA7: *direction = IO_CHIPTOP.DDR.bit.PA7; break;
		case DdTop_GPIO_PB0: *direction = IO_CHIPTOP.DDR.bit.PB0; break;
		case DdTop_GPIO_PB1: *direction = IO_CHIPTOP.DDR.bit.PB1; break;
		case DdTop_GPIO_PB2: *direction = IO_CHIPTOP.DDR.bit.PB2; break;
		case DdTop_GPIO_PB3: *direction = IO_CHIPTOP.DDR.bit.PB3; break;
		case DdTop_GPIO_PB4: *direction = IO_CHIPTOP.DDR.bit.PB4; break;
		case DdTop_GPIO_PC0L: *direction = IO_CHIPTOP.DDR.bit.PC0; break;
		case DdTop_GPIO_PC1L: *direction = IO_CHIPTOP.DDR.bit.PC1; break;
		case DdTop_GPIO_PC2L: *direction = IO_CHIPTOP.DDR.bit.PC2; break;
		case DdTop_GPIO_PC3L: *direction = IO_CHIPTOP.DDR.bit.PC3; break;
		case DdTop_GPIO_PC4L: *direction = IO_CHIPTOP.DDR.bit.PC4; break;
		case DdTop_GPIO_PC5L: *direction = IO_CHIPTOP.DDR.bit.PC5; break;
		case DdTop_GPIO_PD0: *direction = IO_CHIPTOP.DDR.bit.PD0; break;
		case DdTop_GPIO_PD1: *direction = IO_CHIPTOP.DDR.bit.PD1; break;
		case DdTop_GPIO_PD2: *direction = IO_CHIPTOP.DDR.bit.PD2; break;
		case DdTop_GPIO_PD3: *direction = IO_CHIPTOP.DDR.bit.PD3; break;
		case DdTop_GPIO_PD4: *direction = IO_CHIPTOP.DDR.bit.PD4; break;
		case DdTop_GPIO_PD5: *direction = IO_CHIPTOP.DDR.bit.PD5; break;
		case DdTop_GPIO_PD6: *direction = IO_CHIPTOP.DDR.bit.PD6; break;
		case DdTop_GPIO_PE0: *direction = IO_CHIPTOP.DDR.bit.PE0; break;
		case DdTop_GPIO_PE1: *direction = IO_CHIPTOP.DDR.bit.PE1; break;
		case DdTop_GPIO_PE2: *direction = IO_CHIPTOP.DDR.bit.PE2; break;
		case DdTop_GPIO_PE3: *direction = IO_CHIPTOP.DDR.bit.PE3; break;
		case DdTop_GPIO_PE4: *direction = IO_CHIPTOP.DDR.bit.PE4; break;
		case DdTop_GPIO_PE5: *direction = IO_CHIPTOP.DDR.bit.PE5; break;
		case DdTop_GPIO_PF0: *direction = IO_CHIPTOP.DDR.bit.PF0; break;
		case DdTop_GPIO_PF1: *direction = IO_CHIPTOP.DDR.bit.PF1; break;
		case DdTop_GPIO_PF2: *direction = IO_CHIPTOP.DDR.bit.PF2; break;
		case DdTop_GPIO_PF3: *direction = IO_CHIPTOP.DDR.bit.PF3; break;
		case DdTop_GPIO_PF4: *direction = IO_CHIPTOP.DDR.bit.PF4; break;
		case DdTop_GPIO_PG0: *direction = IO_CHIPTOP.DDR.bit.PG0; break;
		case DdTop_GPIO_PG1: *direction = IO_CHIPTOP.DDR.bit.PG1; break;
		case DdTop_GPIO_PG2: *direction = IO_CHIPTOP.DDR.bit.PG2; break;
		case DdTop_GPIO_PG3: *direction = IO_CHIPTOP.DDR.bit.PG3; break;
		case DdTop_GPIO_PG4: *direction = IO_CHIPTOP.DDR.bit.PG4; break;
		case DdTop_GPIO_PG5: *direction = IO_CHIPTOP.DDR.bit.PG5; break;
		case DdTop_GPIO_PG6: *direction = IO_CHIPTOP.DDR.bit.PG6; break;
		case DdTop_GPIO_PG7: *direction = IO_CHIPTOP.DDR.bit.PG7; break;
		case DdTop_GPIO_PH0: *direction = IO_CHIPTOP.DDR.bit.PH0; break;
		case DdTop_GPIO_PH1: *direction = IO_CHIPTOP.DDR.bit.PH1; break;
		case DdTop_GPIO_PH2: *direction = IO_CHIPTOP.DDR.bit.PH2; break;
		case DdTop_GPIO_PH3: *direction = IO_CHIPTOP.DDR.bit.PH3; break;
		case DdTop_GPIO_PW0: *direction = IO_CHIPTOP.DDR.bit.PW0; break;
		case DdTop_GPIO_PW1: *direction = IO_CHIPTOP.DDR.bit.PW1; break;
		case DdTop_GPIO_PW2: *direction = IO_CHIPTOP.DDR.bit.PW2; break;
		case DdTop_GPIO_PW3: *direction = IO_CHIPTOP.DDR.bit.PW3; break;
		case DdTop_GPIO_PW4: *direction = IO_CHIPTOP.DDR.bit.PW4; break;
		case DdTop_GPIO_PW5: *direction = IO_CHIPTOP.DDR.bit.PW5; break;
		case DdTop_GPIO_PW6: *direction = IO_CHIPTOP.DDR.bit.PW6; break;
		case DdTop_GPIO_PW7: *direction = IO_CHIPTOP.DDR.bit.PW7; break;
		case DdTop_GPIO_PJ0: *direction = IO_CHIPTOP.DDR.bit.PJ0; break;
		case DdTop_GPIO_PJ1: *direction = IO_CHIPTOP.DDR.bit.PJ1; break;
		case DdTop_GPIO_PJ2: *direction = IO_CHIPTOP.DDR.bit.PJ2; break;
		case DdTop_GPIO_PJ3: *direction = IO_CHIPTOP.DDR.bit.PJ3; break;
		case DdTop_GPIO_PJ4: *direction = IO_CHIPTOP.DDR.bit.PJ4; break;
		case DdTop_GPIO_PJ5: *direction = IO_CHIPTOP.DDR.bit.PJ5; break;
		case DdTop_GPIO_PJ6: *direction = IO_CHIPTOP.DDR.bit.PJ6; break;
		case DdTop_GPIO_PJ7: *direction = IO_CHIPTOP.DDR.bit.PJ7; break;
		case DdTop_GPIO_PK0: *direction = IO_CHIPTOP.DDR.bit.PK0; break;
		case DdTop_GPIO_PK1: *direction = IO_CHIPTOP.DDR.bit.PK1; break;
		case DdTop_GPIO_PK2: *direction = IO_CHIPTOP.DDR.bit.PK2; break;
		case DdTop_GPIO_PK3: *direction = IO_CHIPTOP.DDR.bit.PK3; break;
		case DdTop_GPIO_PK4: *direction = IO_CHIPTOP.DDR.bit.PK4; break;
		case DdTop_GPIO_PK5: *direction = IO_CHIPTOP.DDR.bit.PK5; break;
		case DdTop_GPIO_PK6: *direction = IO_CHIPTOP.DDR.bit.PK6; break;
		case DdTop_GPIO_PK7: *direction = IO_CHIPTOP.DDR.bit.PK7; break;
		case DdTop_GPIO_PL0: *direction = IO_CHIPTOP.DDR.bit.PL0; break;
		case DdTop_GPIO_PL1: *direction = IO_CHIPTOP.DDR.bit.PL1; break;
		case DdTop_GPIO_PL2: *direction = IO_CHIPTOP.DDR.bit.PL2; break;
		case DdTop_GPIO_PL3: *direction = IO_CHIPTOP.DDR.bit.PL3; break;
		case DdTop_GPIO_PL4: *direction = IO_CHIPTOP.DDR.bit.PL4; break;
		case DdTop_GPIO_PL5: *direction = IO_CHIPTOP.DDR.bit.PL5; break;
		case DdTop_GPIO_PM0: *direction = IO_CHIPTOP.DDR.bit.PM0; break;
		case DdTop_GPIO_PM1: *direction = IO_CHIPTOP.DDR.bit.PM1; break;
		case DdTop_GPIO_PM2: *direction = IO_CHIPTOP.DDR.bit.PM2; break;
		case DdTop_GPIO_PM3: *direction = IO_CHIPTOP.DDR.bit.PM3; break;
		case DdTop_GPIO_PM4: *direction = IO_CHIPTOP.DDR.bit.PM4; break;
		case DdTop_GPIO_PN0: *direction = IO_CHIPTOP.DDR.bit.PN0; break;
		case DdTop_GPIO_PN1: *direction = IO_CHIPTOP.DDR.bit.PN1; break;
		case DdTop_GPIO_PN2: *direction = IO_CHIPTOP.DDR.bit.PN2; break;
		case DdTop_GPIO_PN3: *direction = IO_CHIPTOP.DDR.bit.PN3; break;
		case DdTop_GPIO_PN4: *direction = IO_CHIPTOP.DDR.bit.PN4; break;
		case DdTop_GPIO_PY0: *direction = IO_CHIPTOP.DDR.bit.PY0; break;
		case DdTop_GPIO_PY1: *direction = IO_CHIPTOP.DDR.bit.PY1; break;
		case DdTop_GPIO_PY2: *direction = IO_CHIPTOP.DDR.bit.PY2; break;
		case DdTop_GPIO_PY3: *direction = IO_CHIPTOP.DDR.bit.PY3; break;
		case DdTop_GPIO_PY4: *direction = IO_CHIPTOP.DDR.bit.PY4; break;
		case DdTop_GPIO_PY5: *direction = IO_CHIPTOP.DDR.bit.PY5; break;
		case DdTop_GPIO_PY6: *direction = IO_CHIPTOP.DDR.bit.PY6; break;
		case DdTop_GPIO_PY7: *direction = IO_CHIPTOP.DDR.bit.PY7; break;
		case DdTop_GPIO_PP0: *direction = IO_CHIPTOP.DDR.bit.PP0; break;
		case DdTop_GPIO_PP1: *direction = IO_CHIPTOP.DDR.bit.PP1; break;
		case DdTop_GPIO_PP2: *direction = IO_CHIPTOP.DDR.bit.PP2; break;
		case DdTop_GPIO_PP3: *direction = IO_CHIPTOP.DDR.bit.PP3; break;
		default:
			DdToptwo_STOP_GPIO_CLK_WITH_CS();
			Ddim_Print(("dd_topfour_get_gpio_direction() error. port not exist.\n"));
			return DdTopone_INPUT_PARAM_ERROR;
	}

	DdToptwo_STOP_GPIO_CLK_WITH_CS();

	return D_DDIM_OK;
}


INT32 dd_toptwo_set_gpio_status(DdTopfour *self, DdTop_GPIO_PORT port, UCHAR status )
{
#ifdef DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL
	INT32 s;
#endif // DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL

#ifdef CO_PARAM_CHECK
	if( port >= DdTop_GPIO_PORT_MAX ) {
		Ddim_Assertion(("dd_toptwo_set_gpio_status() error. port parameters is abnormal.\n"));
		return DdTopone_INPUT_PARAM_ERROR;
	}
	if( status > DdToptwo_GPIO_STATUS_HIGH ) {
		Ddim_Assertion(("dd_toptwo_set_gpio_status() error. status parameters is abnormal.\n"));
		return DdTopone_INPUT_PARAM_ERROR;
	}
#endif

	DdToptwo_START_GPIO_CLK_WITH_CS();

	switch( port ) {
		case DdTop_GPIO_P60: IO_CHIPTOP.PDR.word[0] = ( DdToptwo_PDR_WR_EN_B16 | status ); break;
		case DdTop_GPIO_P61: IO_CHIPTOP.PDR.word[0] = ( DdToptwo_PDR_WR_EN_B17 | ( status << 1 )); break;
		case DdTop_GPIO_P62: IO_CHIPTOP.PDR.word[0] = ( DdToptwo_PDR_WR_EN_B18 | ( status << 2 )); break;
		case DdTop_GPIO_P63: IO_CHIPTOP.PDR.word[0] = ( DdToptwo_PDR_WR_EN_B19 | ( status << 3 )); break;
		case DdTop_GPIO_P64: IO_CHIPTOP.PDR.word[0] = ( DdToptwo_PDR_WR_EN_B20 | ( status << 4 )); break;
		case DdTop_GPIO_P65: IO_CHIPTOP.PDR.word[0] = ( DdToptwo_PDR_WR_EN_B21 | ( status << 5 )); break;
		case DdTop_GPIO_P66: IO_CHIPTOP.PDR.word[0] = ( DdToptwo_PDR_WR_EN_B22 | ( status << 6 )); break;
		case DdTop_GPIO_P67: IO_CHIPTOP.PDR.word[0] = ( DdToptwo_PDR_WR_EN_B23 | ( status << 7 )); break;
		case DdTop_GPIO_P70: IO_CHIPTOP.PDR.word[0] = ( DdToptwo_PDR_WR_EN_B24 | ( status << 8 )); break;
		case DdTop_GPIO_P71: IO_CHIPTOP.PDR.word[0] = ( DdToptwo_PDR_WR_EN_B25 | ( status << 9 )); break;
		case DdTop_GPIO_P72: IO_CHIPTOP.PDR.word[0] = ( DdToptwo_PDR_WR_EN_B26 | ( status << 10 )); break;
		case DdTop_GPIO_P73: IO_CHIPTOP.PDR.word[0] = ( DdToptwo_PDR_WR_EN_B27 | ( status << 11 )); break;
		case DdTop_GPIO_P74: IO_CHIPTOP.PDR.word[0] = ( DdToptwo_PDR_WR_EN_B28 | ( status << 12 )); break;
		case DdTop_GPIO_P75: IO_CHIPTOP.PDR.word[0] = ( DdToptwo_PDR_WR_EN_B29 | ( status << 13 )); break;
		case DdTop_GPIO_P76: IO_CHIPTOP.PDR.word[0] = ( DdToptwo_PDR_WR_EN_B30 | ( status << 14 )); break;
		case DdTop_GPIO_P77: IO_CHIPTOP.PDR.word[0] = ( DdToptwo_PDR_WR_EN_B31 | ( status << 15 )); break;

		case DdTop_GPIO_P80: IO_CHIPTOP.PDR.word[1] = ( DdToptwo_PDR_WR_EN_B16 | status ); break;
		case DdTop_GPIO_P81: IO_CHIPTOP.PDR.word[1] = ( DdToptwo_PDR_WR_EN_B17 | ( status << 1 )); break;
		case DdTop_GPIO_P82: IO_CHIPTOP.PDR.word[1] = ( DdToptwo_PDR_WR_EN_B18 | ( status << 2 )); break;
		case DdTop_GPIO_P83: IO_CHIPTOP.PDR.word[1] = ( DdToptwo_PDR_WR_EN_B19 | ( status << 3 )); break;
		case DdTop_GPIO_P84: IO_CHIPTOP.PDR.word[1] = ( DdToptwo_PDR_WR_EN_B20 | ( status << 4 )); break;
		case DdTop_GPIO_P85: IO_CHIPTOP.PDR.word[1] = ( DdToptwo_PDR_WR_EN_B21 | ( status << 5 )); break;
		case DdTop_GPIO_P86: IO_CHIPTOP.PDR.word[1] = ( DdToptwo_PDR_WR_EN_B22 | ( status << 6 )); break;
		case DdTop_GPIO_P87: IO_CHIPTOP.PDR.word[1] = ( DdToptwo_PDR_WR_EN_B23 | ( status << 7 )); break;
		case DdTop_GPIO_P90: IO_CHIPTOP.PDR.word[1] = ( DdToptwo_PDR_WR_EN_B24 | ( status << 8 )); break;
		case DdTop_GPIO_P91: IO_CHIPTOP.PDR.word[1] = ( DdToptwo_PDR_WR_EN_B25 | ( status << 9 )); break;
		case DdTop_GPIO_P92: IO_CHIPTOP.PDR.word[1] = ( DdToptwo_PDR_WR_EN_B26 | ( status << 10 )); break;
		case DdTop_GPIO_P93: IO_CHIPTOP.PDR.word[1] = ( DdToptwo_PDR_WR_EN_B27 | ( status << 11 )); break;

		case DdTop_GPIO_PA0: IO_CHIPTOP.PDR.word[2] = ( DdToptwo_PDR_WR_EN_B16 | status ); break;
		case DdTop_GPIO_PA1: IO_CHIPTOP.PDR.word[2] = ( DdToptwo_PDR_WR_EN_B17 | ( status << 1 )); break;
		case DdTop_GPIO_PA2: IO_CHIPTOP.PDR.word[2] = ( DdToptwo_PDR_WR_EN_B18 | ( status << 2 )); break;
		case DdTop_GPIO_PA3: IO_CHIPTOP.PDR.word[2] = ( DdToptwo_PDR_WR_EN_B19 | ( status << 3 )); break;
		case DdTop_GPIO_PA4: IO_CHIPTOP.PDR.word[2] = ( DdToptwo_PDR_WR_EN_B20 | ( status << 4 )); break;
		case DdTop_GPIO_PA5: IO_CHIPTOP.PDR.word[2] = ( DdToptwo_PDR_WR_EN_B21 | ( status << 5 )); break;
		case DdTop_GPIO_PA6: IO_CHIPTOP.PDR.word[2] = ( DdToptwo_PDR_WR_EN_B22 | ( status << 6 )); break;
		case DdTop_GPIO_PA7: IO_CHIPTOP.PDR.word[2] = ( DdToptwo_PDR_WR_EN_B23 | ( status << 7 )); break;
		case DdTop_GPIO_PB0: IO_CHIPTOP.PDR.word[2] = ( DdToptwo_PDR_WR_EN_B24 | ( status << 8 )); break;
		case DdTop_GPIO_PB1: IO_CHIPTOP.PDR.word[2] = ( DdToptwo_PDR_WR_EN_B25 | ( status << 9 )); break;
		case DdTop_GPIO_PB2: IO_CHIPTOP.PDR.word[2] = ( DdToptwo_PDR_WR_EN_B26 | ( status << 10 )); break;
		case DdTop_GPIO_PB3: IO_CHIPTOP.PDR.word[2] = ( DdToptwo_PDR_WR_EN_B27 | ( status << 11 )); break;
		case DdTop_GPIO_PB4: IO_CHIPTOP.PDR.word[2] = ( DdToptwo_PDR_WR_EN_B28 | ( status << 12 )); break;

		case DdTop_GPIO_PC0L: IO_CHIPTOP.PDR.word[3] = ( DdToptwo_PDR_WR_EN_B16 | status ); break;
		case DdTop_GPIO_PC1L: IO_CHIPTOP.PDR.word[3] = ( DdToptwo_PDR_WR_EN_B17 | ( status << 1 )); break;
		case DdTop_GPIO_PC2L: IO_CHIPTOP.PDR.word[3] = ( DdToptwo_PDR_WR_EN_B18 | ( status << 2 )); break;
		case DdTop_GPIO_PC3L: IO_CHIPTOP.PDR.word[3] = ( DdToptwo_PDR_WR_EN_B19 | ( status << 3 )); break;
		case DdTop_GPIO_PC4L: IO_CHIPTOP.PDR.word[3] = ( DdToptwo_PDR_WR_EN_B20 | ( status << 4 )); break;
		case DdTop_GPIO_PC5L: IO_CHIPTOP.PDR.word[3] = ( DdToptwo_PDR_WR_EN_B21 | ( status << 5 )); break;
		case DdTop_GPIO_PD0: IO_CHIPTOP.PDR.word[3] = ( DdToptwo_PDR_WR_EN_B24 | ( status << 8 )); break;
		case DdTop_GPIO_PD1: IO_CHIPTOP.PDR.word[3] = ( DdToptwo_PDR_WR_EN_B25 | ( status << 9 )); break;
		case DdTop_GPIO_PD2: IO_CHIPTOP.PDR.word[3] = ( DdToptwo_PDR_WR_EN_B26 | ( status << 10 )); break;
		case DdTop_GPIO_PD3: IO_CHIPTOP.PDR.word[3] = ( DdToptwo_PDR_WR_EN_B27 | ( status << 11 )); break;
		case DdTop_GPIO_PD4: IO_CHIPTOP.PDR.word[3] = ( DdToptwo_PDR_WR_EN_B28 | ( status << 12 )); break;
		case DdTop_GPIO_PD5: IO_CHIPTOP.PDR.word[3] = ( DdToptwo_PDR_WR_EN_B29 | ( status << 13 )); break;
		case DdTop_GPIO_PD6: IO_CHIPTOP.PDR.word[3] = ( DdToptwo_PDR_WR_EN_B30 | ( status << 14 )); break;

		case DdTop_GPIO_PE0: IO_CHIPTOP.PDR.word[4] = ( DdToptwo_PDR_WR_EN_B16 | status ); break;
		case DdTop_GPIO_PE1: IO_CHIPTOP.PDR.word[4] = ( DdToptwo_PDR_WR_EN_B17 | ( status << 1 )); break;
		case DdTop_GPIO_PE2: IO_CHIPTOP.PDR.word[4] = ( DdToptwo_PDR_WR_EN_B18 | ( status << 2 )); break;
		case DdTop_GPIO_PE3: IO_CHIPTOP.PDR.word[4] = ( DdToptwo_PDR_WR_EN_B19 | ( status << 3 )); break;
		case DdTop_GPIO_PE4: IO_CHIPTOP.PDR.word[4] = ( DdToptwo_PDR_WR_EN_B20 | ( status << 4 )); break;
		case DdTop_GPIO_PE5: IO_CHIPTOP.PDR.word[4] = ( DdToptwo_PDR_WR_EN_B21 | ( status << 5 )); break;
		case DdTop_GPIO_PF0: IO_CHIPTOP.PDR.word[4] = ( DdToptwo_PDR_WR_EN_B24 | ( status << 8 )); break;
		case DdTop_GPIO_PF1: IO_CHIPTOP.PDR.word[4] = ( DdToptwo_PDR_WR_EN_B25 | ( status << 9 )); break;
		case DdTop_GPIO_PF2: IO_CHIPTOP.PDR.word[4] = ( DdToptwo_PDR_WR_EN_B26 | ( status << 10 )); break;
		case DdTop_GPIO_PF3: IO_CHIPTOP.PDR.word[4] = ( DdToptwo_PDR_WR_EN_B27 | ( status << 11 )); break;
		case DdTop_GPIO_PF4: IO_CHIPTOP.PDR.word[4] = ( DdToptwo_PDR_WR_EN_B28 | ( status << 12 )); break;

		case DdTop_GPIO_PG0: IO_CHIPTOP.PDR.word[5] = ( DdToptwo_PDR_WR_EN_B16 | status ); break;
		case DdTop_GPIO_PG1: IO_CHIPTOP.PDR.word[5] = ( DdToptwo_PDR_WR_EN_B17 | ( status << 1 )); break;
		case DdTop_GPIO_PG2: IO_CHIPTOP.PDR.word[5] = ( DdToptwo_PDR_WR_EN_B18 | ( status << 2 )); break;
		case DdTop_GPIO_PG3: IO_CHIPTOP.PDR.word[5] = ( DdToptwo_PDR_WR_EN_B19 | ( status << 3 )); break;
		case DdTop_GPIO_PG4: IO_CHIPTOP.PDR.word[5] = ( DdToptwo_PDR_WR_EN_B20 | ( status << 4 )); break;
		case DdTop_GPIO_PG5: IO_CHIPTOP.PDR.word[5] = ( DdToptwo_PDR_WR_EN_B21 | ( status << 5 )); break;
		case DdTop_GPIO_PG6: IO_CHIPTOP.PDR.word[5] = ( DdToptwo_PDR_WR_EN_B22 | ( status << 6 )); break;
		case DdTop_GPIO_PG7: IO_CHIPTOP.PDR.word[5] = ( DdToptwo_PDR_WR_EN_B23 | ( status << 7 )); break;
		case DdTop_GPIO_PH0: IO_CHIPTOP.PDR.word[5] = ( DdToptwo_PDR_WR_EN_B24 | ( status << 8 )); break;
		case DdTop_GPIO_PH1: IO_CHIPTOP.PDR.word[5] = ( DdToptwo_PDR_WR_EN_B25 | ( status << 9 )); break;
		case DdTop_GPIO_PH2: IO_CHIPTOP.PDR.word[5] = ( DdToptwo_PDR_WR_EN_B26 | ( status << 10 )); break;
		case DdTop_GPIO_PH3: IO_CHIPTOP.PDR.word[5] = ( DdToptwo_PDR_WR_EN_B27 | ( status << 11 )); break;

		case DdTop_GPIO_PW0: IO_CHIPTOP.PDR.word[6] = ( DdToptwo_PDR_WR_EN_B16 | status ); break;
		case DdTop_GPIO_PW1: IO_CHIPTOP.PDR.word[6] = ( DdToptwo_PDR_WR_EN_B17 | ( status << 1 )); break;
		case DdTop_GPIO_PW2: IO_CHIPTOP.PDR.word[6] = ( DdToptwo_PDR_WR_EN_B18 | ( status << 2 )); break;
		case DdTop_GPIO_PW3: IO_CHIPTOP.PDR.word[6] = ( DdToptwo_PDR_WR_EN_B19 | ( status << 3 )); break;
		case DdTop_GPIO_PW4: IO_CHIPTOP.PDR.word[6] = ( DdToptwo_PDR_WR_EN_B20 | ( status << 4 )); break;
		case DdTop_GPIO_PW5: IO_CHIPTOP.PDR.word[6] = ( DdToptwo_PDR_WR_EN_B21 | ( status << 5 )); break;
		case DdTop_GPIO_PW6: IO_CHIPTOP.PDR.word[6] = ( DdToptwo_PDR_WR_EN_B22 | ( status << 6 )); break;
		case DdTop_GPIO_PW7: IO_CHIPTOP.PDR.word[6] = ( DdToptwo_PDR_WR_EN_B23 | ( status << 7 )); break;
		case DdTop_GPIO_PJ0: IO_CHIPTOP.PDR.word[6] = ( DdToptwo_PDR_WR_EN_B24 | ( status << 8 )); break;
		case DdTop_GPIO_PJ1: IO_CHIPTOP.PDR.word[6] = ( DdToptwo_PDR_WR_EN_B25 | ( status << 9 )); break;
		case DdTop_GPIO_PJ2: IO_CHIPTOP.PDR.word[6] = ( DdToptwo_PDR_WR_EN_B26 | ( status << 10 )); break;
		case DdTop_GPIO_PJ3: IO_CHIPTOP.PDR.word[6] = ( DdToptwo_PDR_WR_EN_B27 | ( status << 11 )); break;
		case DdTop_GPIO_PJ4: IO_CHIPTOP.PDR.word[6] = ( DdToptwo_PDR_WR_EN_B28 | ( status << 12 )); break;
		case DdTop_GPIO_PJ5: IO_CHIPTOP.PDR.word[6] = ( DdToptwo_PDR_WR_EN_B29 | ( status << 13 )); break;
		case DdTop_GPIO_PJ6: IO_CHIPTOP.PDR.word[6] = ( DdToptwo_PDR_WR_EN_B30 | ( status << 14 )); break;
		case DdTop_GPIO_PJ7: IO_CHIPTOP.PDR.word[6] = ( DdToptwo_PDR_WR_EN_B31 | ( status << 15 )); break;

		case DdTop_GPIO_PK0: IO_CHIPTOP.PDR.word[7] = ( DdToptwo_PDR_WR_EN_B16 | status ); break;
		case DdTop_GPIO_PK1: IO_CHIPTOP.PDR.word[7] = ( DdToptwo_PDR_WR_EN_B17 | ( status << 1 )); break;
		case DdTop_GPIO_PK2: IO_CHIPTOP.PDR.word[7] = ( DdToptwo_PDR_WR_EN_B18 | ( status << 2 )); break;
		case DdTop_GPIO_PK3: IO_CHIPTOP.PDR.word[7] = ( DdToptwo_PDR_WR_EN_B19 | ( status << 3 )); break;
		case DdTop_GPIO_PK4: IO_CHIPTOP.PDR.word[7] = ( DdToptwo_PDR_WR_EN_B20 | ( status << 4 )); break;
		case DdTop_GPIO_PK5: IO_CHIPTOP.PDR.word[7] = ( DdToptwo_PDR_WR_EN_B21 | ( status << 5 )); break;
		case DdTop_GPIO_PK6: IO_CHIPTOP.PDR.word[7] = ( DdToptwo_PDR_WR_EN_B22 | ( status << 6 )); break;
		case DdTop_GPIO_PK7: IO_CHIPTOP.PDR.word[7] = ( DdToptwo_PDR_WR_EN_B23 | ( status << 7 )); break;
		case DdTop_GPIO_PL0: IO_CHIPTOP.PDR.word[7] = ( DdToptwo_PDR_WR_EN_B24 | ( status << 8 )); break;
		case DdTop_GPIO_PL1: IO_CHIPTOP.PDR.word[7] = ( DdToptwo_PDR_WR_EN_B25 | ( status << 9 )); break;
		case DdTop_GPIO_PL2: IO_CHIPTOP.PDR.word[7] = ( DdToptwo_PDR_WR_EN_B26 | ( status << 10 )); break;
		case DdTop_GPIO_PL3: IO_CHIPTOP.PDR.word[7] = ( DdToptwo_PDR_WR_EN_B27 | ( status << 11 )); break;
		case DdTop_GPIO_PL4: IO_CHIPTOP.PDR.word[7] = ( DdToptwo_PDR_WR_EN_B28 | ( status << 12 )); break;
		case DdTop_GPIO_PL5: IO_CHIPTOP.PDR.word[7] = ( DdToptwo_PDR_WR_EN_B29 | ( status << 13 )); break;

		case DdTop_GPIO_PM0: IO_CHIPTOP.PDR.word[8] = ( DdToptwo_PDR_WR_EN_B16 | status ); break;
		case DdTop_GPIO_PM1: IO_CHIPTOP.PDR.word[8] = ( DdToptwo_PDR_WR_EN_B17 | ( status << 1 )); break;
		case DdTop_GPIO_PM2: IO_CHIPTOP.PDR.word[8] = ( DdToptwo_PDR_WR_EN_B18 | ( status << 2 )); break;
		case DdTop_GPIO_PM3: IO_CHIPTOP.PDR.word[8] = ( DdToptwo_PDR_WR_EN_B19 | ( status << 3 )); break;
		case DdTop_GPIO_PM4: IO_CHIPTOP.PDR.word[8] = ( DdToptwo_PDR_WR_EN_B20 | ( status << 4 )); break;
		case DdTop_GPIO_PN0: IO_CHIPTOP.PDR.word[8] = ( DdToptwo_PDR_WR_EN_B24 | ( status << 8 )); break;
		case DdTop_GPIO_PN1: IO_CHIPTOP.PDR.word[8] = ( DdToptwo_PDR_WR_EN_B25 | ( status << 9 )); break;
		case DdTop_GPIO_PN2: IO_CHIPTOP.PDR.word[8] = ( DdToptwo_PDR_WR_EN_B26 | ( status << 10 )); break;
		case DdTop_GPIO_PN3: IO_CHIPTOP.PDR.word[8] = ( DdToptwo_PDR_WR_EN_B27 | ( status << 11 )); break;
		case DdTop_GPIO_PN4: IO_CHIPTOP.PDR.word[8] = ( DdToptwo_PDR_WR_EN_B28 | ( status << 12 )); break;

		case DdTop_GPIO_PY0: IO_CHIPTOP.PDR.word[9] = ( DdToptwo_PDR_WR_EN_B16 | status ); break;
		case DdTop_GPIO_PY1: IO_CHIPTOP.PDR.word[9] = ( DdToptwo_PDR_WR_EN_B17 | ( status << 1 )); break;
		case DdTop_GPIO_PY2: IO_CHIPTOP.PDR.word[9] = ( DdToptwo_PDR_WR_EN_B18 | ( status << 2 )); break;
		case DdTop_GPIO_PY3: IO_CHIPTOP.PDR.word[9] = ( DdToptwo_PDR_WR_EN_B19 | ( status << 3 )); break;
		case DdTop_GPIO_PY4: IO_CHIPTOP.PDR.word[9] = ( DdToptwo_PDR_WR_EN_B20 | ( status << 4 )); break;
		case DdTop_GPIO_PY5: IO_CHIPTOP.PDR.word[9] = ( DdToptwo_PDR_WR_EN_B21 | ( status << 5 )); break;
		case DdTop_GPIO_PY6: IO_CHIPTOP.PDR.word[9] = ( DdToptwo_PDR_WR_EN_B22 | ( status << 6 )); break;
		case DdTop_GPIO_PY7: IO_CHIPTOP.PDR.word[9] = ( DdToptwo_PDR_WR_EN_B23 | ( status << 7 )); break;
		case DdTop_GPIO_PP0: IO_CHIPTOP.PDR.word[9] = ( DdToptwo_PDR_WR_EN_B24 | ( status << 8 )); break;
		case DdTop_GPIO_PP1: IO_CHIPTOP.PDR.word[9] = ( DdToptwo_PDR_WR_EN_B25 | ( status << 9 )); break;
		case DdTop_GPIO_PP2: IO_CHIPTOP.PDR.word[9] = ( DdToptwo_PDR_WR_EN_B26 | ( status << 10 )); break;
		case DdTop_GPIO_PP3: IO_CHIPTOP.PDR.word[9] = ( DdToptwo_PDR_WR_EN_B27 | ( status << 11 )); break;

		default:
			DdToptwo_STOP_GPIO_CLK_WITH_CS();
			Ddim_Print(("dd_toptwo_set_gpio_status() error. port not exist.\n"));
			return DdTopone_INPUT_PARAM_ERROR;
	}

	Dd_ARM_Dsb_Pou();
	DdToptwo_STOP_GPIO_CLK_WITH_CS();

	return D_DDIM_OK;
}



/**
Set the functionality of a selectable GPIO port.<br>
It is set to the EPCR(External Port Control Register) value.
@param [in]  port		Port name. See @ref DdTop_GPIO_PORT
@param [in]  function	Function type.
						  <ul>
							  <li>0:@ref DdToptwo_GPIO_FUNC_GPIO
							  <li>1:@ref DdToptwo_GPIO_FUNC_HWMODE
						  </ul>
@retval D_DDIM_OK					Success.
@retval DdTopone_INPUT_PARAM_ERROR	Input parameter error.
*/
INT32 dd_topfour_set_gpio_function(DdTopfour *self, DdTop_GPIO_PORT port, UCHAR function )
{
#ifdef DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL
	INT32 s;
#endif // DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL

#ifdef CO_PARAM_CHECK
	if( port >= DdTop_GPIO_PORT_MAX ) {
		Ddim_Assertion(("dd_topfour_set_gpio_function() error. port parameters is abnormal.\n"));
		return DdTopone_INPUT_PARAM_ERROR;
	}
	if( function > DdToptwo_GPIO_FUNC_HWMODE ) {
		Ddim_Assertion(("dd_topfour_set_gpio_function() error. function parameters is abnormal.\n"));
		return DdTopone_INPUT_PARAM_ERROR;
	}
#endif

	DdToptwo_START_GPIO_CLK_WITH_CS();

	switch( port ) {
		case DdTop_GPIO_P60: IO_CHIPTOP.EPCR.bit.P60 = function; break;
		case DdTop_GPIO_P61: IO_CHIPTOP.EPCR.bit.P61 = function; break;
		case DdTop_GPIO_P62: IO_CHIPTOP.EPCR.bit.P62 = function; break;
		case DdTop_GPIO_P63: IO_CHIPTOP.EPCR.bit.P63 = function; break;
		case DdTop_GPIO_P80: IO_CHIPTOP.EPCR.bit.P80 = function; break;
		case DdTop_GPIO_P81: IO_CHIPTOP.EPCR.bit.P81 = function; break;
		case DdTop_GPIO_P82: IO_CHIPTOP.EPCR.bit.P82 = function; break;
		case DdTop_GPIO_P83: IO_CHIPTOP.EPCR.bit.P83 = function; break;
		case DdTop_GPIO_P84: IO_CHIPTOP.EPCR.bit.P84 = function; break;
		case DdTop_GPIO_P85: IO_CHIPTOP.EPCR.bit.P85 = function; break;
		case DdTop_GPIO_P86: IO_CHIPTOP.EPCR.bit.P86 = function; break;
		case DdTop_GPIO_P87: IO_CHIPTOP.EPCR.bit.P87 = function; break;
		case DdTop_GPIO_P90: IO_CHIPTOP.EPCR.bit.P90 = function; break;
		case DdTop_GPIO_P92: IO_CHIPTOP.EPCR.bit.P92 = function; break;
		case DdTop_GPIO_PA0: IO_CHIPTOP.EPCR.bit.PA0 = function; break;
		case DdTop_GPIO_PA1: IO_CHIPTOP.EPCR.bit.PA1 = function; break;
		case DdTop_GPIO_PA3: IO_CHIPTOP.EPCR.bit.PA3 = function; break;
		case DdTop_GPIO_PA4: IO_CHIPTOP.EPCR.bit.PA4 = function; break;
		case DdTop_GPIO_PA5: IO_CHIPTOP.EPCR.bit.PA5 = function; break;
		case DdTop_GPIO_PA7: IO_CHIPTOP.EPCR.bit.PA7 = function; break;
		case DdTop_GPIO_PB0: IO_CHIPTOP.EPCR.bit.PB0 = function; break;
		case DdTop_GPIO_PB1: IO_CHIPTOP.EPCR.bit.PB1 = function; break;
		case DdTop_GPIO_PB2: IO_CHIPTOP.EPCR.bit.PB2 = function; break;
		case DdTop_GPIO_PB3: IO_CHIPTOP.EPCR.bit.PB3 = function; break;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
		case DdTop_GPIO_PB4: IO_CHIPTOP.EPCR.bit.PB4 = function; break;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
		case DdTop_GPIO_PB4: IO_CHIPTOP.EPCR.bit.TRGEN = function; break;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
		case DdTop_GPIO_PC0L: IO_CHIPTOP.EPCR.bit.PC0 = function; break;
		case DdTop_GPIO_PC1L: IO_CHIPTOP.EPCR.bit.PC1 = function; break;
		case DdTop_GPIO_PC2L: IO_CHIPTOP.EPCR.bit.PC2 = function; break;
		case DdTop_GPIO_PC3L: IO_CHIPTOP.EPCR.bit.PC3 = function; break;
		case DdTop_GPIO_PC4L: IO_CHIPTOP.EPCR.bit.PC4 = function; break;
		case DdTop_GPIO_PC5L: IO_CHIPTOP.EPCR.bit.PC5 = function; break;
		case DdTop_GPIO_PD0: IO_CHIPTOP.EPCR.bit.PD0 = function; break;
		case DdTop_GPIO_PD1: IO_CHIPTOP.EPCR.bit.PD1 = function; break;
		case DdTop_GPIO_PD2: IO_CHIPTOP.EPCR.bit.PD2 = function; break;
		case DdTop_GPIO_PD3: IO_CHIPTOP.EPCR.bit.PD3 = function; break;
		case DdTop_GPIO_PD4: IO_CHIPTOP.EPCR.bit.PD4 = function; break;
		case DdTop_GPIO_PD5: IO_CHIPTOP.EPCR.bit.PD5 = function; break;
		case DdTop_GPIO_PD6: IO_CHIPTOP.EPCR.bit.PD6 = function; break;
		case DdTop_GPIO_PE1: IO_CHIPTOP.EPCR.bit.PE1 = function; break;
		case DdTop_GPIO_PE3: IO_CHIPTOP.EPCR.bit.PE3 = function; break;
		case DdTop_GPIO_PE5: IO_CHIPTOP.EPCR.bit.PE5 = function; break;
		case DdTop_GPIO_PF4: IO_CHIPTOP.EPCR.bit.PF4 = function; break;
		case DdTop_GPIO_PG0: IO_CHIPTOP.EPCR.bit.PG0 = function; break;
		case DdTop_GPIO_PG1: IO_CHIPTOP.EPCR.bit.PG1 = function; break;
		case DdTop_GPIO_PG2: IO_CHIPTOP.EPCR.bit.PG2 = function; break;
		case DdTop_GPIO_PG3: IO_CHIPTOP.EPCR.bit.PG3 = function; break;
		case DdTop_GPIO_PG4: IO_CHIPTOP.EPCR.bit.PG4 = function; break;
		case DdTop_GPIO_PG5: IO_CHIPTOP.EPCR.bit.PG5 = function; break;
		case DdTop_GPIO_PG6: IO_CHIPTOP.EPCR.bit.PG6 = function; break;
		case DdTop_GPIO_PG7: IO_CHIPTOP.EPCR.bit.PG7 = function; break;
		case DdTop_GPIO_PH0: IO_CHIPTOP.EPCR.bit.PH0 = function; break;
		case DdTop_GPIO_PH1: IO_CHIPTOP.EPCR.bit.PH1 = function; break;
		case DdTop_GPIO_PH2: IO_CHIPTOP.EPCR.bit.PH2 = function; break;
		case DdTop_GPIO_PH3: IO_CHIPTOP.EPCR.bit.PH3 = function; break;
		case DdTop_GPIO_PW0: IO_CHIPTOP.EPCR.bit.PW0 = function; break;
		case DdTop_GPIO_PW1: IO_CHIPTOP.EPCR.bit.PW1 = function; break;
		case DdTop_GPIO_PW2: IO_CHIPTOP.EPCR.bit.PW2 = function; break;
		case DdTop_GPIO_PW3: IO_CHIPTOP.EPCR.bit.PW3 = function; break;
		case DdTop_GPIO_PW4: IO_CHIPTOP.EPCR.bit.PW4 = function; break;
		case DdTop_GPIO_PW5: IO_CHIPTOP.EPCR.bit.PW5 = function; break;
		case DdTop_GPIO_PW6: IO_CHIPTOP.EPCR.bit.PW6 = function; break;
		case DdTop_GPIO_PW7: IO_CHIPTOP.EPCR.bit.PW7 = function; break;
		case DdTop_GPIO_PJ0: IO_CHIPTOP.EPCR.bit.PJ0 = function; break;
		case DdTop_GPIO_PJ1: IO_CHIPTOP.EPCR.bit.PJ1 = function; break;
		case DdTop_GPIO_PJ2: IO_CHIPTOP.EPCR.bit.PJ2 = function; break;
		case DdTop_GPIO_PJ3: IO_CHIPTOP.EPCR.bit.PJ3 = function; break;
		case DdTop_GPIO_PJ4: IO_CHIPTOP.EPCR.bit.PJ4 = function; break;
		case DdTop_GPIO_PJ5: IO_CHIPTOP.EPCR.bit.PJ5 = function; break;
		case DdTop_GPIO_PJ6: IO_CHIPTOP.EPCR.bit.PJ6 = function; break;
		case DdTop_GPIO_PJ7: IO_CHIPTOP.EPCR.bit.PJ7 = function; break;
		case DdTop_GPIO_PK0: IO_CHIPTOP.EPCR.bit.PK0 = function; break;
		case DdTop_GPIO_PK1: IO_CHIPTOP.EPCR.bit.PK1 = function; break;
		case DdTop_GPIO_PK2: IO_CHIPTOP.EPCR.bit.PK2 = function; break;
		case DdTop_GPIO_PK3: IO_CHIPTOP.EPCR.bit.PK3 = function; break;
		case DdTop_GPIO_PK4: IO_CHIPTOP.EPCR.bit.PK4 = function; break;
		case DdTop_GPIO_PK5: IO_CHIPTOP.EPCR.bit.PK5 = function; break;
		case DdTop_GPIO_PK6: IO_CHIPTOP.EPCR.bit.PK6 = function; break;
		case DdTop_GPIO_PK7: IO_CHIPTOP.EPCR.bit.PK7 = function; break;
		case DdTop_GPIO_PL0: IO_CHIPTOP.EPCR.bit.PL0 = function; break;
		case DdTop_GPIO_PL1: IO_CHIPTOP.EPCR.bit.PL1 = function; break;
		case DdTop_GPIO_PL2: IO_CHIPTOP.EPCR.bit.PL2 = function; break;
		case DdTop_GPIO_PL3: IO_CHIPTOP.EPCR.bit.PL3 = function; break;
		case DdTop_GPIO_PL4: IO_CHIPTOP.EPCR.bit.PL4 = function; break;
		case DdTop_GPIO_PL5: IO_CHIPTOP.EPCR.bit.PL5 = function; break;
		case DdTop_GPIO_PM1: IO_CHIPTOP.EPCR.bit.PM1 = function; break;
		case DdTop_GPIO_PM3: IO_CHIPTOP.EPCR.bit.PM3 = function; break;
		case DdTop_GPIO_PM4: IO_CHIPTOP.EPCR.bit.PM4 = function; break;
		case DdTop_GPIO_PN1: IO_CHIPTOP.EPCR.bit.PN1 = function; break;
		case DdTop_GPIO_PN3: IO_CHIPTOP.EPCR.bit.PN3 = function; break;
		case DdTop_GPIO_PN4: IO_CHIPTOP.EPCR.bit.PN4 = function; break;
		case DdTop_GPIO_PY0: IO_CHIPTOP.EPCR.bit.PY0 = function; break;
		case DdTop_GPIO_PY1: IO_CHIPTOP.EPCR.bit.PY1 = function; break;
		case DdTop_GPIO_PY4: IO_CHIPTOP.EPCR.bit.PY4 = function; break;
		case DdTop_GPIO_PY5: IO_CHIPTOP.EPCR.bit.PY5 = function; break;
		case DdTop_GPIO_PY6: IO_CHIPTOP.EPCR.bit.PY6 = function; break;
		case DdTop_GPIO_PY7: IO_CHIPTOP.EPCR.bit.PY7 = function; break;
		case DdTop_GPIO_PP0: IO_CHIPTOP.EPCR.bit.PP0 = function; break;
		case DdTop_GPIO_PP1: IO_CHIPTOP.EPCR.bit.PP1 = function; break;
		case DdTop_GPIO_PP2: IO_CHIPTOP.EPCR.bit.PP2 = function; break;
		case DdTop_GPIO_PP3: IO_CHIPTOP.EPCR.bit.PP3 = function; break;
		default:
			DdToptwo_STOP_GPIO_CLK_WITH_CS();
			Ddim_Print(("dd_topfour_set_gpio_function() error. port not exist.\n"));
			return DdTopone_INPUT_PARAM_ERROR;
	}

	Dd_ARM_Dsb_Pou();
	DdToptwo_STOP_GPIO_CLK_WITH_CS();

	return D_DDIM_OK;
}

/**
Get the functionality of a selectable GPIO port.<br>
It is get from the EPCR(External Port Control Register) value.
@param [in]  port		Port name. See @ref DdTop_GPIO_PORT
@param [out] function	Function type.
						  <ul>
							  <li>0:@ref DdToptwo_GPIO_FUNC_GPIO
							  <li>1:@ref DdToptwo_GPIO_FUNC_HWMODE
						  </ul>
@retval D_DDIM_OK					Success.
@retval DdTopone_INPUT_PARAM_ERROR	Input parameter error.
*/
INT32 dd_topfour_get_gpio_function(DdTopfour *self, DdTop_GPIO_PORT port, UCHAR* function )
{
#ifdef DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL
	INT32 s;
#endif // DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL

#ifdef CO_PARAM_CHECK
	if( port >= DdTop_GPIO_PORT_MAX ) {
		Ddim_Assertion(("dd_topfour_get_gpio_function() error. port parameters is abnormal.\n"));
		return DdTopone_INPUT_PARAM_ERROR;
	}
	if( function == NULL ) {
		Ddim_Assertion(("dd_topfour_get_gpio_function() error. function parameters is abnormal.\n"));
		return DdTopone_INPUT_PARAM_ERROR;
	}
#endif

	DdToptwo_START_GPIO_CLK_WITH_CS();

	switch( port ) {
		case DdTop_GPIO_P60: *function = IO_CHIPTOP.EPCR.bit.P60; break;
		case DdTop_GPIO_P61: *function = IO_CHIPTOP.EPCR.bit.P61; break;
		case DdTop_GPIO_P62: *function = IO_CHIPTOP.EPCR.bit.P62; break;
		case DdTop_GPIO_P63: *function = IO_CHIPTOP.EPCR.bit.P63; break;
		case DdTop_GPIO_P80: *function = IO_CHIPTOP.EPCR.bit.P80; break;
		case DdTop_GPIO_P81: *function = IO_CHIPTOP.EPCR.bit.P81; break;
		case DdTop_GPIO_P82: *function = IO_CHIPTOP.EPCR.bit.P82; break;
		case DdTop_GPIO_P83: *function = IO_CHIPTOP.EPCR.bit.P83; break;
		case DdTop_GPIO_P84: *function = IO_CHIPTOP.EPCR.bit.P84; break;
		case DdTop_GPIO_P85: *function = IO_CHIPTOP.EPCR.bit.P85; break;
		case DdTop_GPIO_P86: *function = IO_CHIPTOP.EPCR.bit.P86; break;
		case DdTop_GPIO_P87: *function = IO_CHIPTOP.EPCR.bit.P87; break;
		case DdTop_GPIO_P90: *function = IO_CHIPTOP.EPCR.bit.P90; break;
		case DdTop_GPIO_P92: *function = IO_CHIPTOP.EPCR.bit.P92; break;
		case DdTop_GPIO_PA0: *function = IO_CHIPTOP.EPCR.bit.PA0; break;
		case DdTop_GPIO_PA1: *function = IO_CHIPTOP.EPCR.bit.PA1; break;
		case DdTop_GPIO_PA3: *function = IO_CHIPTOP.EPCR.bit.PA3; break;
		case DdTop_GPIO_PA4: *function = IO_CHIPTOP.EPCR.bit.PA4; break;
		case DdTop_GPIO_PA5: *function = IO_CHIPTOP.EPCR.bit.PA5; break;
		case DdTop_GPIO_PA7: *function = IO_CHIPTOP.EPCR.bit.PA7; break;
		case DdTop_GPIO_PB0: *function = IO_CHIPTOP.EPCR.bit.PB0; break;
		case DdTop_GPIO_PB1: *function = IO_CHIPTOP.EPCR.bit.PB1; break;
		case DdTop_GPIO_PB2: *function = IO_CHIPTOP.EPCR.bit.PB2; break;
		case DdTop_GPIO_PB3: *function = IO_CHIPTOP.EPCR.bit.PB3; break;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
		case DdTop_GPIO_PB4: *function = IO_CHIPTOP.EPCR.bit.PB4; break;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
		case DdTop_GPIO_PB4: *function = IO_CHIPTOP.EPCR.bit.TRGEN; break;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
		case DdTop_GPIO_PC0L: *function = IO_CHIPTOP.EPCR.bit.PC0; break;
		case DdTop_GPIO_PC1L: *function = IO_CHIPTOP.EPCR.bit.PC1; break;
		case DdTop_GPIO_PC2L: *function = IO_CHIPTOP.EPCR.bit.PC2; break;
		case DdTop_GPIO_PC3L: *function = IO_CHIPTOP.EPCR.bit.PC3; break;
		case DdTop_GPIO_PC4L: *function = IO_CHIPTOP.EPCR.bit.PC4; break;
		case DdTop_GPIO_PC5L: *function = IO_CHIPTOP.EPCR.bit.PC5; break;
		case DdTop_GPIO_PD0: *function = IO_CHIPTOP.EPCR.bit.PD0; break;
		case DdTop_GPIO_PD1: *function = IO_CHIPTOP.EPCR.bit.PD1; break;
		case DdTop_GPIO_PD2: *function = IO_CHIPTOP.EPCR.bit.PD2; break;
		case DdTop_GPIO_PD3: *function = IO_CHIPTOP.EPCR.bit.PD3; break;
		case DdTop_GPIO_PD4: *function = IO_CHIPTOP.EPCR.bit.PD4; break;
		case DdTop_GPIO_PD5: *function = IO_CHIPTOP.EPCR.bit.PD5; break;
		case DdTop_GPIO_PD6: *function = IO_CHIPTOP.EPCR.bit.PD6; break;
		case DdTop_GPIO_PE1: *function = IO_CHIPTOP.EPCR.bit.PE1; break;
		case DdTop_GPIO_PE3: *function = IO_CHIPTOP.EPCR.bit.PE3; break;
		case DdTop_GPIO_PE5: *function = IO_CHIPTOP.EPCR.bit.PE5; break;
		case DdTop_GPIO_PF4: *function = IO_CHIPTOP.EPCR.bit.PF4; break;
		case DdTop_GPIO_PG0: *function = IO_CHIPTOP.EPCR.bit.PG0; break;
		case DdTop_GPIO_PG1: *function = IO_CHIPTOP.EPCR.bit.PG1; break;
		case DdTop_GPIO_PG2: *function = IO_CHIPTOP.EPCR.bit.PG2; break;
		case DdTop_GPIO_PG3: *function = IO_CHIPTOP.EPCR.bit.PG3; break;
		case DdTop_GPIO_PG4: *function = IO_CHIPTOP.EPCR.bit.PG4; break;
		case DdTop_GPIO_PG5: *function = IO_CHIPTOP.EPCR.bit.PG5; break;
		case DdTop_GPIO_PG6: *function = IO_CHIPTOP.EPCR.bit.PG6; break;
		case DdTop_GPIO_PG7: *function = IO_CHIPTOP.EPCR.bit.PG7; break;
		case DdTop_GPIO_PH0: *function = IO_CHIPTOP.EPCR.bit.PH0; break;
		case DdTop_GPIO_PH1: *function = IO_CHIPTOP.EPCR.bit.PH1; break;
		case DdTop_GPIO_PH2: *function = IO_CHIPTOP.EPCR.bit.PH2; break;
		case DdTop_GPIO_PH3: *function = IO_CHIPTOP.EPCR.bit.PH3; break;
		case DdTop_GPIO_PW0: *function = IO_CHIPTOP.EPCR.bit.PW0; break;
		case DdTop_GPIO_PW1: *function = IO_CHIPTOP.EPCR.bit.PW1; break;
		case DdTop_GPIO_PW2: *function = IO_CHIPTOP.EPCR.bit.PW2; break;
		case DdTop_GPIO_PW3: *function = IO_CHIPTOP.EPCR.bit.PW3; break;
		case DdTop_GPIO_PW4: *function = IO_CHIPTOP.EPCR.bit.PW4; break;
		case DdTop_GPIO_PW5: *function = IO_CHIPTOP.EPCR.bit.PW5; break;
		case DdTop_GPIO_PW6: *function = IO_CHIPTOP.EPCR.bit.PW6; break;
		case DdTop_GPIO_PW7: *function = IO_CHIPTOP.EPCR.bit.PW7; break;
		case DdTop_GPIO_PJ0: *function = IO_CHIPTOP.EPCR.bit.PJ0; break;
		case DdTop_GPIO_PJ1: *function = IO_CHIPTOP.EPCR.bit.PJ1; break;
		case DdTop_GPIO_PJ2: *function = IO_CHIPTOP.EPCR.bit.PJ2; break;
		case DdTop_GPIO_PJ3: *function = IO_CHIPTOP.EPCR.bit.PJ3; break;
		case DdTop_GPIO_PJ4: *function = IO_CHIPTOP.EPCR.bit.PJ4; break;
		case DdTop_GPIO_PJ5: *function = IO_CHIPTOP.EPCR.bit.PJ5; break;
		case DdTop_GPIO_PJ6: *function = IO_CHIPTOP.EPCR.bit.PJ6; break;
		case DdTop_GPIO_PJ7: *function = IO_CHIPTOP.EPCR.bit.PJ7; break;
		case DdTop_GPIO_PK0: *function = IO_CHIPTOP.EPCR.bit.PK0; break;
		case DdTop_GPIO_PK1: *function = IO_CHIPTOP.EPCR.bit.PK1; break;
		case DdTop_GPIO_PK2: *function = IO_CHIPTOP.EPCR.bit.PK2; break;
		case DdTop_GPIO_PK3: *function = IO_CHIPTOP.EPCR.bit.PK3; break;
		case DdTop_GPIO_PK4: *function = IO_CHIPTOP.EPCR.bit.PK4; break;
		case DdTop_GPIO_PK5: *function = IO_CHIPTOP.EPCR.bit.PK5; break;
		case DdTop_GPIO_PK6: *function = IO_CHIPTOP.EPCR.bit.PK6; break;
		case DdTop_GPIO_PK7: *function = IO_CHIPTOP.EPCR.bit.PK7; break;
		case DdTop_GPIO_PL0: *function = IO_CHIPTOP.EPCR.bit.PL0; break;
		case DdTop_GPIO_PL1: *function = IO_CHIPTOP.EPCR.bit.PL1; break;
		case DdTop_GPIO_PL2: *function = IO_CHIPTOP.EPCR.bit.PL2; break;
		case DdTop_GPIO_PL3: *function = IO_CHIPTOP.EPCR.bit.PL3; break;
		case DdTop_GPIO_PL4: *function = IO_CHIPTOP.EPCR.bit.PL4; break;
		case DdTop_GPIO_PL5: *function = IO_CHIPTOP.EPCR.bit.PL5; break;
		case DdTop_GPIO_PM1: *function = IO_CHIPTOP.EPCR.bit.PM1; break;
		case DdTop_GPIO_PM3: *function = IO_CHIPTOP.EPCR.bit.PM3; break;
		case DdTop_GPIO_PM4: *function = IO_CHIPTOP.EPCR.bit.PM4; break;
		case DdTop_GPIO_PN1: *function = IO_CHIPTOP.EPCR.bit.PN1; break;
		case DdTop_GPIO_PN3: *function = IO_CHIPTOP.EPCR.bit.PN3; break;
		case DdTop_GPIO_PN4: *function = IO_CHIPTOP.EPCR.bit.PN4; break;
		case DdTop_GPIO_PY0: *function = IO_CHIPTOP.EPCR.bit.PY0; break;
		case DdTop_GPIO_PY1: *function = IO_CHIPTOP.EPCR.bit.PY1; break;
		case DdTop_GPIO_PY4: *function = IO_CHIPTOP.EPCR.bit.PY4; break;
		case DdTop_GPIO_PY5: *function = IO_CHIPTOP.EPCR.bit.PY5; break;
		case DdTop_GPIO_PY6: *function = IO_CHIPTOP.EPCR.bit.PY6; break;
		case DdTop_GPIO_PY7: *function = IO_CHIPTOP.EPCR.bit.PY7; break;
		case DdTop_GPIO_PP0: *function = IO_CHIPTOP.EPCR.bit.PP0; break;
		case DdTop_GPIO_PP1: *function = IO_CHIPTOP.EPCR.bit.PP1; break;
		case DdTop_GPIO_PP2: *function = IO_CHIPTOP.EPCR.bit.PP2; break;
		case DdTop_GPIO_PP3: *function = IO_CHIPTOP.EPCR.bit.PP3; break;
		default:
			DdToptwo_STOP_GPIO_CLK_WITH_CS();
			Ddim_Print(("dd_topfour_get_gpio_function() error. port not exist.\n"));
			return DdTopone_INPUT_PARAM_ERROR;
	}

	DdToptwo_STOP_GPIO_CLK_WITH_CS();

	return D_DDIM_OK;
}



/**
Set the state of a selectable GPIO port.<br>
It is set to the PDR(Port Data Register) value.
@param [in]  port		Port name. See @ref DdTop_GPIO_PORT
@param [in]  status		Port status.
						  <ul>
							  <li>0:@ref DdToptwo_GPIO_STATUS_LOW
							  <li>1:@ref DdToptwo_GPIO_STATUS_HIGH
						  </ul>
@retval D_DDIM_OK					Success.
@retval DdTopone_INPUT_PARAM_ERROR	Error occurred.
*/


/**
Get the state of a selectable GPIO port.<br>
It is get from the PDR(Port Data Register) value.
@param [in]  port		Port name. See @ref DdTop_GPIO_PORT
@param [out] status		Port status.
						  <ul>
							  <li>0:@ref DdToptwo_GPIO_STATUS_LOW
							  <li>1:@ref DdToptwo_GPIO_STATUS_HIGH
						  </ul>
@retval D_DDIM_OK					Success.
@retval DdTopone_INPUT_PARAM_ERROR	Error occurred.
*/
INT32 dd_topfour_get_gpio_status(DdTopfour *self, DdTop_GPIO_PORT port, UCHAR* status )
{
#ifdef DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL
	INT32 s;
#endif // DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL

#ifdef CO_PARAM_CHECK
	if( port >= DdTop_GPIO_PORT_MAX ) {
		Ddim_Assertion(("dd_topfour_get_gpio_status() error. port parameters is abnormal.\n"));
		return DdTopone_INPUT_PARAM_ERROR;
	}
	if( status == NULL ) {
		Ddim_Assertion(("dd_topfour_get_gpio_status() error. status parameters is abnormal.\n"));
		return DdTopone_INPUT_PARAM_ERROR;
	}
#endif

	DdToptwo_START_GPIO_CLK_WITH_CS();

	switch( port ) {
		case DdTop_GPIO_P60: *status = IO_CHIPTOP.PDR.bit.P60; break;
		case DdTop_GPIO_P61: *status = IO_CHIPTOP.PDR.bit.P61; break;
		case DdTop_GPIO_P62: *status = IO_CHIPTOP.PDR.bit.P62; break;
		case DdTop_GPIO_P63: *status = IO_CHIPTOP.PDR.bit.P63; break;
		case DdTop_GPIO_P64: *status = IO_CHIPTOP.PDR.bit.P64; break;
		case DdTop_GPIO_P65: *status = IO_CHIPTOP.PDR.bit.P65; break;
		case DdTop_GPIO_P66: *status = IO_CHIPTOP.PDR.bit.P66; break;
		case DdTop_GPIO_P67: *status = IO_CHIPTOP.PDR.bit.P67; break;
		case DdTop_GPIO_P70: *status = IO_CHIPTOP.PDR.bit.P70; break;
		case DdTop_GPIO_P71: *status = IO_CHIPTOP.PDR.bit.P71; break;
		case DdTop_GPIO_P72: *status = IO_CHIPTOP.PDR.bit.P72; break;
		case DdTop_GPIO_P73: *status = IO_CHIPTOP.PDR.bit.P73; break;
		case DdTop_GPIO_P74: *status = IO_CHIPTOP.PDR.bit.P74; break;
		case DdTop_GPIO_P75: *status = IO_CHIPTOP.PDR.bit.P75; break;
		case DdTop_GPIO_P76: *status = IO_CHIPTOP.PDR.bit.P76; break;
		case DdTop_GPIO_P77: *status = IO_CHIPTOP.PDR.bit.P77; break;
		case DdTop_GPIO_P80: *status = IO_CHIPTOP.PDR.bit.P80; break;
		case DdTop_GPIO_P81: *status = IO_CHIPTOP.PDR.bit.P81; break;
		case DdTop_GPIO_P82: *status = IO_CHIPTOP.PDR.bit.P82; break;
		case DdTop_GPIO_P83: *status = IO_CHIPTOP.PDR.bit.P83; break;
		case DdTop_GPIO_P84: *status = IO_CHIPTOP.PDR.bit.P84; break;
		case DdTop_GPIO_P85: *status = IO_CHIPTOP.PDR.bit.P85; break;
		case DdTop_GPIO_P86: *status = IO_CHIPTOP.PDR.bit.P86; break;
		case DdTop_GPIO_P87: *status = IO_CHIPTOP.PDR.bit.P87; break;
		case DdTop_GPIO_P90: *status = IO_CHIPTOP.PDR.bit.P90; break;
		case DdTop_GPIO_P91: *status = IO_CHIPTOP.PDR.bit.P91; break;
		case DdTop_GPIO_P92: *status = IO_CHIPTOP.PDR.bit.P92; break;
		case DdTop_GPIO_P93: *status = IO_CHIPTOP.PDR.bit.P93; break;
		case DdTop_GPIO_PA0: *status = IO_CHIPTOP.PDR.bit.PA0; break;
		case DdTop_GPIO_PA1: *status = IO_CHIPTOP.PDR.bit.PA1; break;
		case DdTop_GPIO_PA2: *status = IO_CHIPTOP.PDR.bit.PA2; break;
		case DdTop_GPIO_PA3: *status = IO_CHIPTOP.PDR.bit.PA3; break;
		case DdTop_GPIO_PA4: *status = IO_CHIPTOP.PDR.bit.PA4; break;
		case DdTop_GPIO_PA5: *status = IO_CHIPTOP.PDR.bit.PA5; break;
		case DdTop_GPIO_PA6: *status = IO_CHIPTOP.PDR.bit.PA6; break;
		case DdTop_GPIO_PA7: *status = IO_CHIPTOP.PDR.bit.PA7; break;
		case DdTop_GPIO_PB0: *status = IO_CHIPTOP.PDR.bit.PB0; break;
		case DdTop_GPIO_PB1: *status = IO_CHIPTOP.PDR.bit.PB1; break;
		case DdTop_GPIO_PB2: *status = IO_CHIPTOP.PDR.bit.PB2; break;
		case DdTop_GPIO_PB3: *status = IO_CHIPTOP.PDR.bit.PB3; break;
		case DdTop_GPIO_PB4: *status = IO_CHIPTOP.PDR.bit.PB4; break;
		case DdTop_GPIO_PC0L: *status = IO_CHIPTOP.PDR.bit.PC0; break;
		case DdTop_GPIO_PC1L: *status = IO_CHIPTOP.PDR.bit.PC1; break;
		case DdTop_GPIO_PC2L: *status = IO_CHIPTOP.PDR.bit.PC2; break;
		case DdTop_GPIO_PC3L: *status = IO_CHIPTOP.PDR.bit.PC3; break;
		case DdTop_GPIO_PC4L: *status = IO_CHIPTOP.PDR.bit.PC4; break;
		case DdTop_GPIO_PC5L: *status = IO_CHIPTOP.PDR.bit.PC5; break;
		case DdTop_GPIO_PD0: *status = IO_CHIPTOP.PDR.bit.PD0; break;
		case DdTop_GPIO_PD1: *status = IO_CHIPTOP.PDR.bit.PD1; break;
		case DdTop_GPIO_PD2: *status = IO_CHIPTOP.PDR.bit.PD2; break;
		case DdTop_GPIO_PD3: *status = IO_CHIPTOP.PDR.bit.PD3; break;
		case DdTop_GPIO_PD4: *status = IO_CHIPTOP.PDR.bit.PD4; break;
		case DdTop_GPIO_PD5: *status = IO_CHIPTOP.PDR.bit.PD5; break;
		case DdTop_GPIO_PD6: *status = IO_CHIPTOP.PDR.bit.PD6; break;
		case DdTop_GPIO_PE0: *status = IO_CHIPTOP.PDR.bit.PE0; break;
		case DdTop_GPIO_PE1: *status = IO_CHIPTOP.PDR.bit.PE1; break;
		case DdTop_GPIO_PE2: *status = IO_CHIPTOP.PDR.bit.PE2; break;
		case DdTop_GPIO_PE3: *status = IO_CHIPTOP.PDR.bit.PE3; break;
		case DdTop_GPIO_PE4: *status = IO_CHIPTOP.PDR.bit.PE4; break;
		case DdTop_GPIO_PE5: *status = IO_CHIPTOP.PDR.bit.PE5; break;
		case DdTop_GPIO_PF0: *status = IO_CHIPTOP.PDR.bit.PF0; break;
		case DdTop_GPIO_PF1: *status = IO_CHIPTOP.PDR.bit.PF1; break;
		case DdTop_GPIO_PF2: *status = IO_CHIPTOP.PDR.bit.PF2; break;
		case DdTop_GPIO_PF3: *status = IO_CHIPTOP.PDR.bit.PF3; break;
		case DdTop_GPIO_PF4: *status = IO_CHIPTOP.PDR.bit.PF4; break;
		case DdTop_GPIO_PG0: *status = IO_CHIPTOP.PDR.bit.PG0; break;
		case DdTop_GPIO_PG1: *status = IO_CHIPTOP.PDR.bit.PG1; break;
		case DdTop_GPIO_PG2: *status = IO_CHIPTOP.PDR.bit.PG2; break;
		case DdTop_GPIO_PG3: *status = IO_CHIPTOP.PDR.bit.PG3; break;
		case DdTop_GPIO_PG4: *status = IO_CHIPTOP.PDR.bit.PG4; break;
		case DdTop_GPIO_PG5: *status = IO_CHIPTOP.PDR.bit.PG5; break;
		case DdTop_GPIO_PG6: *status = IO_CHIPTOP.PDR.bit.PG6; break;
		case DdTop_GPIO_PG7: *status = IO_CHIPTOP.PDR.bit.PG7; break;
		case DdTop_GPIO_PH0: *status = IO_CHIPTOP.PDR.bit.PH0; break;
		case DdTop_GPIO_PH1: *status = IO_CHIPTOP.PDR.bit.PH1; break;
		case DdTop_GPIO_PH2: *status = IO_CHIPTOP.PDR.bit.PH2; break;
		case DdTop_GPIO_PH3: *status = IO_CHIPTOP.PDR.bit.PH3; break;
		case DdTop_GPIO_PW0: *status = IO_CHIPTOP.PDR.bit.PW0; break;
		case DdTop_GPIO_PW1: *status = IO_CHIPTOP.PDR.bit.PW1; break;
		case DdTop_GPIO_PW2: *status = IO_CHIPTOP.PDR.bit.PW2; break;
		case DdTop_GPIO_PW3: *status = IO_CHIPTOP.PDR.bit.PW3; break;
		case DdTop_GPIO_PW4: *status = IO_CHIPTOP.PDR.bit.PW4; break;
		case DdTop_GPIO_PW5: *status = IO_CHIPTOP.PDR.bit.PW5; break;
		case DdTop_GPIO_PW6: *status = IO_CHIPTOP.PDR.bit.PW6; break;
		case DdTop_GPIO_PW7: *status = IO_CHIPTOP.PDR.bit.PW7; break;
		case DdTop_GPIO_PJ0: *status = IO_CHIPTOP.PDR.bit.PJ0; break;
		case DdTop_GPIO_PJ1: *status = IO_CHIPTOP.PDR.bit.PJ1; break;
		case DdTop_GPIO_PJ2: *status = IO_CHIPTOP.PDR.bit.PJ2; break;
		case DdTop_GPIO_PJ3: *status = IO_CHIPTOP.PDR.bit.PJ3; break;
		case DdTop_GPIO_PJ4: *status = IO_CHIPTOP.PDR.bit.PJ4; break;
		case DdTop_GPIO_PJ5: *status = IO_CHIPTOP.PDR.bit.PJ5; break;
		case DdTop_GPIO_PJ6: *status = IO_CHIPTOP.PDR.bit.PJ6; break;
		case DdTop_GPIO_PJ7: *status = IO_CHIPTOP.PDR.bit.PJ7; break;
		case DdTop_GPIO_PK0: *status = IO_CHIPTOP.PDR.bit.PK0; break;
		case DdTop_GPIO_PK1: *status = IO_CHIPTOP.PDR.bit.PK1; break;
		case DdTop_GPIO_PK2: *status = IO_CHIPTOP.PDR.bit.PK2; break;
		case DdTop_GPIO_PK3: *status = IO_CHIPTOP.PDR.bit.PK3; break;
		case DdTop_GPIO_PK4: *status = IO_CHIPTOP.PDR.bit.PK4; break;
		case DdTop_GPIO_PK5: *status = IO_CHIPTOP.PDR.bit.PK5; break;
		case DdTop_GPIO_PK6: *status = IO_CHIPTOP.PDR.bit.PK6; break;
		case DdTop_GPIO_PK7: *status = IO_CHIPTOP.PDR.bit.PK7; break;
		case DdTop_GPIO_PL0: *status = IO_CHIPTOP.PDR.bit.PL0; break;
		case DdTop_GPIO_PL1: *status = IO_CHIPTOP.PDR.bit.PL1; break;
		case DdTop_GPIO_PL2: *status = IO_CHIPTOP.PDR.bit.PL2; break;
		case DdTop_GPIO_PL3: *status = IO_CHIPTOP.PDR.bit.PL3; break;
		case DdTop_GPIO_PL4: *status = IO_CHIPTOP.PDR.bit.PL4; break;
		case DdTop_GPIO_PL5: *status = IO_CHIPTOP.PDR.bit.PL5; break;
		case DdTop_GPIO_PM0: *status = IO_CHIPTOP.PDR.bit.PM0; break;
		case DdTop_GPIO_PM1: *status = IO_CHIPTOP.PDR.bit.PM1; break;
		case DdTop_GPIO_PM2: *status = IO_CHIPTOP.PDR.bit.PM2; break;
		case DdTop_GPIO_PM3: *status = IO_CHIPTOP.PDR.bit.PM3; break;
		case DdTop_GPIO_PM4: *status = IO_CHIPTOP.PDR.bit.PM4; break;
		case DdTop_GPIO_PN0: *status = IO_CHIPTOP.PDR.bit.PN0; break;
		case DdTop_GPIO_PN1: *status = IO_CHIPTOP.PDR.bit.PN1; break;
		case DdTop_GPIO_PN2: *status = IO_CHIPTOP.PDR.bit.PN2; break;
		case DdTop_GPIO_PN3: *status = IO_CHIPTOP.PDR.bit.PN3; break;
		case DdTop_GPIO_PN4: *status = IO_CHIPTOP.PDR.bit.PN4; break;
		case DdTop_GPIO_PY0: *status = IO_CHIPTOP.PDR.bit.PY0; break;
		case DdTop_GPIO_PY1: *status = IO_CHIPTOP.PDR.bit.PY1; break;
		case DdTop_GPIO_PY2: *status = IO_CHIPTOP.PDR.bit.PY2; break;
		case DdTop_GPIO_PY3: *status = IO_CHIPTOP.PDR.bit.PY3; break;
		case DdTop_GPIO_PY4: *status = IO_CHIPTOP.PDR.bit.PY4; break;
		case DdTop_GPIO_PY5: *status = IO_CHIPTOP.PDR.bit.PY5; break;
		case DdTop_GPIO_PY6: *status = IO_CHIPTOP.PDR.bit.PY6; break;
		case DdTop_GPIO_PY7: *status = IO_CHIPTOP.PDR.bit.PY7; break;
		case DdTop_GPIO_PP0: *status = IO_CHIPTOP.PDR.bit.PP0; break;
		case DdTop_GPIO_PP1: *status = IO_CHIPTOP.PDR.bit.PP1; break;
		case DdTop_GPIO_PP2: *status = IO_CHIPTOP.PDR.bit.PP2; break;
		case DdTop_GPIO_PP3: *status = IO_CHIPTOP.PDR.bit.PP3; break;
		default:
			DdToptwo_STOP_GPIO_CLK_WITH_CS();
			Ddim_Print(("dd_topfour_get_gpio_status() error. port not exist.\n"));
			return DdTopone_INPUT_PARAM_ERROR;
	}

	DdToptwo_STOP_GPIO_CLK_WITH_CS();

	return D_DDIM_OK;
}


DdTopfour* dd_topfour_new(void)
{
	DdTopfour *self = g_object_new(DD_TYPE_TOPFOUR, NULL);
	return self;
}
