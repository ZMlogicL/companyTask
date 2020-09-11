/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-03
*@author              :董如利
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/
#include <stdlib.h>
#include <string.h>
#include "../../DeviceDriver/LSITop/src/ddtop.h"
#include "../../DeviceDriver/LSITop/src/ddtopfour.h"
#include "../../DeviceDriver/LSITop/src/ddtopone.h"
#include "../../DeviceDriver/LSITop/src/ddtopthree.h"
#include "../../DeviceDriver/LSITop/src/ddtoptwo.h"
#include "ctgpiomidtest.h"
#include"ctgpio.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtGpioMidTest, ct_gpio_mid_test);
#define CT_GPIO_MID_TEST_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtGpioMidTestPrivate,CT_TYPE_GPIO_MID_TEST))

struct _CtGpioMidTestPrivate
{
	kint a;
};
/****************
* DECLS
*/
static void 			ct_gpio_mid_test_constructor(CtGpioMidTest *self);
static void 			ct_gpio_mid_test_destructor(CtGpioMidTest *self);
/****************
* IMPL
*/
static void ct_gpio_mid_test_constructor(CtGpioMidTest *self) 
{
	// CtGpioMidTestPrivate *priv = CT_GPIO_MID_TEST_GET_PRIVATE(self);
}

static void ct_gpio_mid_test_destructor(CtGpioMidTest *self) 
{
	// CtGpioMidTestPrivate *priv = CT_GPIO_MID_TEST_GET_PRIVATE(self);
}
/****************
* PUBLIC
*/
void ct_gpio_mid_test(CtGpioMidTest *self,CtGpio *ctGpio)
{
 
	/* PUDER */
	ct_gpio_set_ctrl(ctGpio,"PUDER", "P80", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "P80");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "P80", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "P80");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "P81", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "P81");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "P81", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "P81");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "P82", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "P82");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "P82", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "P82");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "P83", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "P83");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "P83", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "P83");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "P86", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "P86");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "P86", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "P86");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "P87", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "P87");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "P87", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "P87");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "P90", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "P90");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "P90", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "P90");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "P91", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "P91");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "P91", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "P91");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "P92", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "P92");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "P92", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "P92");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "P93", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "P93");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "P93", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "P93");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PA0", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PA0");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PA0", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PA0");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PA1", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PA1");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PA1", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PA1");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PA2", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PA2");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PA2", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PA2");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PA3", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PA3");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PA3", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PA3");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PA4", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PA4");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PA4", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PA4");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PA5", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PA5");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PA5", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PA5");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PA6", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PA6");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PA6", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PA6");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PA7", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PA7");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PA7", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PA7");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PB0", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PB0");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PB0", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PB0");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PB1", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PB1");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PB1", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PB1");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PB2", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PB2");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PB2", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PB2");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PB3", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PB3");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PB3", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PB3");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PB4", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PB4");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PB4", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PB4");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PD0", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PD0");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PD0", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PD0");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PD1", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PD1");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PD1", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PD1");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PD2", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PD2");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PD2", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PD2");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PD3", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PD3");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PD3", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PD3");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PD4", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PD4");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PD4", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PD4");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PD5", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PD5");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PD5", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PD5");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PD6", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PD6");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PD6", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PD6");
	//	ct_gpio_set_ctrl(ctGpio, "PUDER", "PE0", 1 );
	//	ct_gpio_get_ctrl(ctGpio, "PUDER", "PE0");
	//	ct_gpio_set_ctrl(ctGpio, "PUDER", "PE0", 0 );
	//	ct_gpio_get_ctrl(ctGpio, "PUDER", "PE0");
	//	ct_gpio_set_ctrl(ctGpio, "PUDER", "PE1", 1 );
	//	ct_gpio_get_ctrl(ctGpio, "PUDER", "PE1");
	//	ct_gpio_set_ctrl(ctGpio, "PUDER", "PE1", 0 );
	//	ct_gpio_get_ctrl(ctGpio, "PUDER", "PE1");
	//	ct_gpio_set_ctrl(ctGpio, "PUDER", "PF2", 1 );
	//	ct_gpio_get_ctrl(ctGpio, "PUDER", "PF2");
	//	ct_gpio_set_ctrl(ctGpio, "PUDER", "PF2", 0 );
	//	ct_gpio_get_ctrl(ctGpio, "PUDER", "PF2");
	//	ct_gpio_set_ctrl(ctGpio, "PUDER", "PF3", 1 );
	//	ct_gpio_get_ctrl(ctGpio, "PUDER", "PF3");
	//	ct_gpio_set_ctrl(ctGpio, "PUDER", "PF3", 0 );
	//	ct_gpio_get_ctrl(ctGpio, "PUDER", "PF3");
	//	ct_gpio_set_ctrl(ctGpio, "PUDER", "PF4", 1 );
	//	ct_gpio_get_ctrl(ctGpio, "PUDER", "PF4");
	//	ct_gpio_set_ctrl(ctGpio, "PUDER", "PF4", 0 );
	//	ct_gpio_get_ctrl(ctGpio, "PUDER", "PF4");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PG0", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PG0");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PG0", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PG0");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PG1", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PG1");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PG1", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PG1");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PG2", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PG2");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PG2", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PG2");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PG3", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PG3");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PG3", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PG3");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PG4", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PG4");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PG4", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PG4");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PG5", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PG5");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PG5", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PG5");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PG6", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PG6");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PG6", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PG6");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PG7", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PG7");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PG7", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PG7");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PH0", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PH0");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PH0", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PH0");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PH1", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PH1");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PH1", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PH1");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PH2", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PH2");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PH2", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PH2");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PH3", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PH3");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PH3", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PH3");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PW0", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PW0");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PW0", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PW0");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PW1", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PW1");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PW1", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PW1");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PW2", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PW2");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PW2", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PW2");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PW3", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PW3");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PW3", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PW3");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PW4", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PW4");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PW4", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PW4");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PW5", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PW5");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PW5", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PW5");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PW6", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PW6");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PW6", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PW6");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PW7", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PW7");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PW7", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PW7");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PJ0", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PJ0");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PJ0", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PJ0");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PJ1", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PJ1");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PJ1", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PJ1");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PJ2", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PJ2");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PJ2", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PJ2");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PJ3", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PJ3");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PJ3", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PJ3");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PJ4", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PJ4");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PJ4", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PJ4");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PJ5", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PJ5");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PJ5", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PJ5");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PJ6", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PJ6");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PJ6", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PJ6");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PJ7", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PJ7");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PJ7", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PJ7");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PK0", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PK0");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PK0", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PK0");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PK1", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PK1");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PK1", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PK1");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PK2", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PK2");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PK2", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PK2");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PK3", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PK3");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PK3", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PK3");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PK4", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PK4");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PK4", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PK4");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PK5", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PK5");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PK5", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PK5");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PK6", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PK6");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PK6", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PK6");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PK7", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PK7");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PK7", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PK7");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PL0", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PL0");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PL0", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PL0");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PL1", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PL1");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PL1", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PL1");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PL2", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PL2");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PL2", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PL2");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PL3", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PL3");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PL3", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PL3");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PL4", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PL4");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PL4", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PL4");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PL5", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PL5");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PL5", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PL5");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PM0", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PM0");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PM0", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PM0");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PM1", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PM1");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PM1", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PM1");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PM3", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PM3");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PM3", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PM3");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PM4", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PM4");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PM4", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PM4");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PN0", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PN0");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PN0", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PN0");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PN1", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PN1");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PN1", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PN1");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PN3", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PN3");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PN3", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PN3");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PN4", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PN4");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PN4", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PN4");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PY0", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PY0");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PY0", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PY0");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PY1", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PY1");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PY1", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PY1");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PY2", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PY2");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PY2", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PY2");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PY3", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PY3");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PY3", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PY3");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PY4", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PY4");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PY4", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PY4");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PY5", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PY5");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PY5", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PY5");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PY6", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PY6");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PY6", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PY6");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PY7", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PY7");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PY7", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PY7");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PP0", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PP0");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PP0", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PP0");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PP1", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PP1");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PP1", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PP1");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PP2", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PP2");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PP2", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PP2");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PP3", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PP3");
	ct_gpio_set_ctrl(ctGpio,"PUDER", "PP3", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDER", "PP3");    

	/* PUDCR */
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "P80", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "P80");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "P80", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "P80");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "P81", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "P81");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "P81", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "P81");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "P82", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "P82");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "P82", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "P82");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "P83", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "P83");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "P83", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "P83");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "P86", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "P86");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "P86", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "P86");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "P87", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "P87");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "P87", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "P87");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "P90", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "P90");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "P90", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "P90");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "P91", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "P91");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "P91", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "P91");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "P92", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "P92");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "P92", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "P92");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "P93", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "P93");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "P93", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "P93");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PA0", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PA0");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PA0", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PA0");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PA1", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PA1");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PA1", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PA1");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PA2", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PA2");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PA2", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PA2");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PA3", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PA3");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PA3", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PA3");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PA4", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PA4");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PA4", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PA4");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PA5", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PA5");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PA5", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PA5");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PA6", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PA6");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PA6", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PA6");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PA7", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PA7");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PA7", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PA7");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PB0", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PB0");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PB0", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PB0");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PB1", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PB1");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PB1", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PB1");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PB2", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PB2");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PB2", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PB2");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PB3", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PB3");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PB3", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PB3");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PB4", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PB4");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PB4", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PB4");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PD0", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PD0");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PD0", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PD0");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PD1", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PD1");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PD1", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PD1");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PD2", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PD2");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PD2", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PD2");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PD3", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PD3");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PD3", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PD3");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PD4", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PD4");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PD4", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PD4");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PD5", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PD5");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PD5", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PD5");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PD6", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PD6");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PD6", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PD6");
	//	ct_gpio_set_ctrl(ctGpio, "PUDCR", "PE0", 1 );
	//	ct_gpio_get_ctrl(ctGpio, "PUDCR", "PE0");
	//	ct_gpio_set_ctrl(ctGpio, "PUDCR", "PE0", 0 );
	//	ct_gpio_get_ctrl(ctGpio, "PUDCR", "PE0");
	//	ct_gpio_set_ctrl(ctGpio, "PUDCR", "PE1", 1 );
	//	ct_gpio_get_ctrl(ctGpio, "PUDCR", "PE1");
	//	ct_gpio_set_ctrl(ctGpio, "PUDCR", "PE1", 0 );
	//	ct_gpio_get_ctrl(ctGpio, "PUDCR", "PE1");
	//	ct_gpio_set_ctrl(ctGpio, "PUDCR", "PF2", 1 );
	//	ct_gpio_get_ctrl(ctGpio, "PUDCR", "PF2");
	//	ct_gpio_set_ctrl(ctGpio, "PUDCR", "PF2", 0 );
	//	ct_gpio_get_ctrl(ctGpio, "PUDCR", "PF2");
	//	ct_gpio_set_ctrl(ctGpio, "PUDCR", "PF3", 1 );
	//	ct_gpio_get_ctrl(ctGpio, "PUDCR", "PF3");
	//	ct_gpio_set_ctrl(ctGpio, "PUDCR", "PF3", 0 );
	//	ct_gpio_get_ctrl(ctGpio, "PUDCR", "PF3");
	//	ct_gpio_set_ctrl(ctGpio, "PUDCR", "PF4", 1 );
	//	ct_gpio_get_ctrl(ctGpio, "PUDCR", "PF4");
	//	ct_gpio_set_ctrl(ctGpio, "PUDCR", "PF4", 0 );
	//	ct_gpio_get_ctrl(ctGpio, "PUDCR", "PF4");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PG0", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PG0");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PG0", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PG0");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PG1", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PG1");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PG1", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PG1");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PG2", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PG2");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PG2", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PG2");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PG3", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PG3");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PG3", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PG3");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PG4", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PG4");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PG4", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PG4");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PG5", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PG5");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PG5", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PG5");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PG6", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PG6");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PG6", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PG6");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PG7", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PG7");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PG7", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PG7");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PH0", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PH0");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PH0", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PH0");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PH1", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PH1");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PH1", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PH1");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PH2", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PH2");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PH2", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PH2");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PH3", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PH3");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PH3", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PH3");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PW0", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PW0");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PW0", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PW0");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PW1", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PW1");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PW1", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PW1");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PW2", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PW2");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PW2", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PW2");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PW3", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PW3");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PW3", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PW3");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PW4", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PW4");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PW4", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PW4");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PW5", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PW5");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PW5", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PW5");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PW6", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PW6");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PW6", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PW6");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PW7", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PW7");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PW7", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PW7");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PJ0", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PJ0");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PJ0", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PJ0");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PJ1", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PJ1");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PJ1", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PJ1");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PJ2", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PJ2");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PJ2", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PJ2");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PJ3", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PJ3");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PJ3", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PJ3");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PJ4", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PJ4");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PJ4", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PJ4");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PJ5", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PJ5");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PJ5", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PJ5");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PJ6", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PJ6");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PJ6", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PJ6");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PJ7", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PJ7");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PJ7", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PJ7");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PK0", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PK0");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PK0", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PK0");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PK1", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PK1");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PK1", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PK1");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PK2", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PK2");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PK2", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PK2");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PK3", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PK3");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PK3", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PK3");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PK4", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PK4");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PK4", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PK4");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PK5", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PK5");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PK5", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PK5");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PK6", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PK6");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PK6", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PK6");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PK7", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PK7");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PK7", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PK7");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PL0", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PL0");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PL0", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PL0");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PL1", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PL1");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PL1", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PL1");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PL2", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PL2");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PL2", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PL2");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PL3", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PL3");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PL3", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PL3");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PL4", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PL4");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PL4", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PL4");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PL5", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PL5");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PL5", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PL5");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PM0", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PM0");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PM0", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PM0");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PM1", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PM1");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PM1", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PM1");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PM3", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PM3");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PM3", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PM3");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PM4", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PM4");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PM4", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PM4");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PN0", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PN0");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PN0", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PN0");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PN1", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PN1");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PN1", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PN1");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PN3", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PN3");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PN3", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PN3");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PN4", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PN4");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PN4", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PN4");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PY0", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PY0");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PY0", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PY0");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PY1", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PY1");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PY1", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PY1");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PY2", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PY2");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PY2", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PY2");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PY3", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PY3");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PY3", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PY3");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PY4", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PY4");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PY4", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PY4");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PY5", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PY5");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PY5", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PY5");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PY6", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PY6");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PY6", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PY6");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PY7", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PY7");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PY7", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PY7");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PP0", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PP0");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PP0", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PP0");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PP1", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PP1");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PP1", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PP1");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PP2", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PP2");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PP2", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PP2");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PP3", 1);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PP3");
	ct_gpio_set_ctrl(ctGpio,"PUDCR", "PP3", 0);
	ct_gpio_get_ctrl(ctGpio,"PUDCR", "PP3");

}

CtGpioMidTest* ct_gpio_mid_test_new(void) 
{
    CtGpioMidTest *self = k_object_new_with_private(CT_TYPE_GPIO_MID_TEST, sizeof(CtGpioMidTestPrivate));
    return self;
}