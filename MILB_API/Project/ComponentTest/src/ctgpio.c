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
#include "ctgpio.h"
#include "ctgpiotest.h"
#include "ctgpiomidtest.h"
#include "ctgpioendtest.h"
#include "ctgpiocopy.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtGpio, ct_gpio);
#define CT_GPIO_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtGpioPrivate,CT_TYPE_GPIO))

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
//#define CtGpio_D_DD_TOP_PC_DEBUG
// GPIO register definition

//< EPCR  : External Port Control Register 
#define CtGpio_D_DD_TOP_GPIO_EPCR (0)
//< DDR   : Port Direction Register	
#define CtGpio_D_DD_TOP_GPIO_DDR (1)
//< PDR   : Port Data Register
#define CtGpio_D_DD_TOP_GPIO_PDR (2)
//< PUDER : Pull-Up/Down Enable Register
#define CtGpio_D_DD_TOP_GPIO_PUDER (3)
//< PUDCR : Pull-Up/Down Control Register 
#define CtGpio_D_DD_TOP_GPIO_PUDCR (4)

struct _CtGpioPrivate
{
    CtGpioTest* ctGpioTest;
    CtGpioMidTest* ctGpioMidTest;
    CtGpioEndTest* ctGpioEndTest;
};
/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
static kchar S_GDD_TOP_PORT_NAME[E_DD_TOP_GPIO_PORT_MAX][4] = {"P60",
															"P61",
															"P62",
															"P63",
															"P64",
															"P65",
															"P66",
															"P67",
															"P70",
															"P71",
															"P72",
															"P73",
															"P74",
															"P75",
															"P76",
															"P77",
															"P80",
															"P81",
															"P82",
															"P83",
															"P84",
															"P85",
															"P86",
															"P87",
															"P90",
															"P91",
															"P92",
															"P93",
															"PA0",
															"PA1",
															"PA2",
															"PA3",
															"PA4",
															"PA5",
															"PA6",
															"PA7",
															"PB0",
															"PB1",
															"PB2",
															"PB3",
															"PB4",
															"PC0",
															"PC1",
															"PC2",
															"PC3",
															"PC4",
															"PC5",
															"PD0",
															"PD1",
															"PD2",
															"PD3",
															"PD4",
															"PD5",
															"PD6",
															"PE0",
															"PE1",
															"PE2",
															"PE3",
															"PE4",
															"PE5",
															"PF0",
															"PF1",
															"PF2",
															"PF3",
															"PF4",
															"PG0",
															"PG1",
															"PG2",
															"PG3",
															"PG4",
															"PG5",
															"PG6",
															"PG7",
															"PH0",
															"PH1",
															"PH2",
															"PH3",
															"PW0",
															"PW1",
															"PW2",
															"PW3",
															"PW4",
															"PW5",
															"PW6",
															"PW7",
															"PJ0",
															"PJ1",
															"PJ2",
															"PJ3",
															"PJ4",
															"PJ5",
															"PJ6",
															"PJ7",
															"PK0",
															"PK1",
															"PK2",
															"PK3",
															"PK4",
															"PK5",
															"PK6",
															"PK7",
															"PL0",
															"PL1",
															"PL2",
															"PL3",
															"PL4",
															"PL5",
															"PM0",
															"PM1",
															"PM2",
															"PM3",
															"PM4",
															"PN0",
															"PN1",
															"PN2",
															"PN3",
															"PN4",
															"PY0",
															"PY1",
															"PY2",
															"PY3",
															"PY4",
															"PY5",
															"PY6",
															"PY7",
															"PP0",
															"PP1",
															"PP2",
															"PP3"};

/****************
* DECLS
*/
static void 			ct_gpio_constructor(CtGpio *self);
static void 			ct_gpio_destructor(CtGpio *self);
static void 			ctGpioTestPdr(CtGpio*self,kint argc, kchar **argv);
static void 			ctGpioTest(CtGpio *self);
static void 			ctGpioErr(void);
/****************
* IMPL
*/
static void ct_gpio_constructor(CtGpio *self) 
{
	CtGpioPrivate *priv = CT_GPIO_GET_PRIVATE(self);
    ((CtDdParameter *)self)->argv = NULL;
    priv->ctGpioTest = ct_gpio_test_new();
    priv->ctGpioMidTest = ct_gpio_mid_test_new();
    priv->ctGpioEndTest = ct_gpio_end_test_new();
}

static void ct_gpio_destructor(CtGpio *self) 
{
	CtGpioPrivate *priv = CT_GPIO_GET_PRIVATE(self);
    
    ((CtDdParameter *)self)->argv = NULL;
    k_object_unref(priv->ctGpioTest);
    k_object_unref(priv->ctGpioMidTest);
    k_object_unref(priv->ctGpioEndTest);
}

static void ctGpioTestPdr(CtGpio*self,kint argc, kchar **argv)
{

	/* PDR */
	ct_gpio_set_ctrl(self,"PDR", "P60", 1);
	ct_gpio_get_ctrl(self,"PDR", "P60");
	ct_gpio_set_ctrl(self,"PDR", "P60", 0);
	ct_gpio_get_ctrl(self,"PDR", "P60");
	ct_gpio_set_ctrl(self,"PDR", "P61", 1);
	ct_gpio_get_ctrl(self,"PDR", "P61");
	ct_gpio_set_ctrl(self,"PDR", "P61", 0);
	ct_gpio_get_ctrl(self,"PDR", "P61");
	ct_gpio_set_ctrl(self,"PDR", "P62", 1);
	ct_gpio_get_ctrl(self,"PDR", "P62");
	ct_gpio_set_ctrl(self,"PDR", "P62", 0);
	ct_gpio_get_ctrl(self,"PDR", "P62");
	ct_gpio_set_ctrl(self,"PDR", "P63", 1);
	ct_gpio_get_ctrl(self,"PDR", "P63");
	ct_gpio_set_ctrl(self,"PDR", "P63", 0);
	ct_gpio_get_ctrl(self,"PDR", "P63");
	ct_gpio_set_ctrl(self,"PDR", "P64", 1);
	ct_gpio_get_ctrl(self,"PDR", "P64");
	ct_gpio_set_ctrl(self,"PDR", "P64", 0);
	ct_gpio_get_ctrl(self,"PDR", "P64");
	ct_gpio_set_ctrl(self,"PDR", "P65", 1);
	ct_gpio_get_ctrl(self,"PDR", "P65");
	ct_gpio_set_ctrl(self,"PDR", "P65", 0);
	ct_gpio_get_ctrl(self,"PDR", "P65");
	ct_gpio_set_ctrl(self,"PDR", "P66", 1);
	ct_gpio_get_ctrl(self,"PDR", "P66");
	ct_gpio_set_ctrl(self,"PDR", "P66", 0);
	ct_gpio_get_ctrl(self,"PDR", "P66");
	ct_gpio_set_ctrl(self,"PDR", "P67", 1);
	ct_gpio_get_ctrl(self,"PDR", "P67");
	ct_gpio_set_ctrl(self,"PDR", "P67", 0);
	ct_gpio_get_ctrl(self,"PDR", "P67");
	ct_gpio_set_ctrl(self,"PDR", "P70", 1);
	ct_gpio_get_ctrl(self,"PDR", "P70");
	ct_gpio_set_ctrl(self,"PDR", "P70", 0);
	ct_gpio_get_ctrl(self,"PDR", "P70");
	ct_gpio_set_ctrl(self,"PDR", "P71", 1);
	ct_gpio_get_ctrl(self,"PDR", "P71");
	ct_gpio_set_ctrl(self,"PDR", "P71", 0);
	ct_gpio_get_ctrl(self,"PDR", "P71");
	ct_gpio_set_ctrl(self,"PDR", "P72", 1);
	ct_gpio_get_ctrl(self,"PDR", "P72");
	ct_gpio_set_ctrl(self,"PDR", "P72", 0);
	ct_gpio_get_ctrl(self,"PDR", "P72");
	ct_gpio_set_ctrl(self,"PDR", "P73", 1);
	ct_gpio_get_ctrl(self,"PDR", "P73");
	ct_gpio_set_ctrl(self,"PDR", "P73", 0);
	ct_gpio_get_ctrl(self,"PDR", "P73");
	ct_gpio_set_ctrl(self,"PDR", "P74", 1);
	ct_gpio_get_ctrl(self,"PDR", "P74");
	ct_gpio_set_ctrl(self,"PDR", "P74", 0);
	ct_gpio_get_ctrl(self,"PDR", "P74");
	ct_gpio_set_ctrl(self,"PDR", "P75", 1);
	ct_gpio_get_ctrl(self,"PDR", "P75");
	ct_gpio_set_ctrl(self,"PDR", "P75", 0);
	ct_gpio_get_ctrl(self,"PDR", "P75");
	ct_gpio_set_ctrl(self,"PDR", "P76", 1);
	ct_gpio_get_ctrl(self,"PDR", "P76");
	ct_gpio_set_ctrl(self,"PDR", "P76", 0);
	ct_gpio_get_ctrl(self,"PDR", "P76");
	ct_gpio_set_ctrl(self,"PDR", "P77", 1);
	ct_gpio_get_ctrl(self,"PDR", "P77");
	ct_gpio_set_ctrl(self,"PDR", "P77", 0);
	ct_gpio_get_ctrl(self,"PDR", "P77");
	ct_gpio_set_ctrl(self,"PDR", "P80", 1);
	ct_gpio_get_ctrl(self,"PDR", "P80");
	ct_gpio_set_ctrl(self,"PDR", "P80", 0);
	ct_gpio_get_ctrl(self,"PDR", "P80");
	ct_gpio_set_ctrl(self,"PDR", "P81", 1);
	ct_gpio_get_ctrl(self,"PDR", "P81");
	ct_gpio_set_ctrl(self,"PDR", "P81", 0);
	ct_gpio_get_ctrl(self,"PDR", "P81");
	ct_gpio_set_ctrl(self,"PDR", "P82", 1);
	ct_gpio_get_ctrl(self,"PDR", "P82");
	ct_gpio_set_ctrl(self,"PDR", "P82", 0);
	ct_gpio_get_ctrl(self,"PDR", "P82");
	ct_gpio_set_ctrl(self,"PDR", "P83", 1);
	ct_gpio_get_ctrl(self,"PDR", "P83");
	ct_gpio_set_ctrl(self,"PDR", "P83", 0);
	ct_gpio_get_ctrl(self,"PDR", "P83");
	ct_gpio_set_ctrl(self,"PDR", "P84", 1);
	ct_gpio_get_ctrl(self,"PDR", "P84");
	ct_gpio_set_ctrl(self,"PDR", "P84", 0);
	ct_gpio_get_ctrl(self,"PDR", "P84");
	ct_gpio_set_ctrl(self,"PDR", "P85", 1);
	ct_gpio_get_ctrl(self,"PDR", "P85");
	ct_gpio_set_ctrl(self,"PDR", "P85", 0);
	ct_gpio_get_ctrl(self,"PDR", "P85");
	ct_gpio_set_ctrl(self,"PDR", "P86", 1);
	ct_gpio_get_ctrl(self,"PDR", "P86");
	ct_gpio_set_ctrl(self,"PDR", "P86", 0);
	ct_gpio_get_ctrl(self,"PDR", "P86");
	ct_gpio_set_ctrl(self,"PDR", "P87", 1);
	ct_gpio_get_ctrl(self,"PDR", "P87");
	ct_gpio_set_ctrl(self,"PDR", "P87", 0);
	ct_gpio_get_ctrl(self,"PDR", "P87");
	ct_gpio_set_ctrl(self,"PDR", "P90", 1);
	ct_gpio_get_ctrl(self,"PDR", "P90");
	ct_gpio_set_ctrl(self,"PDR", "P90", 0);
	ct_gpio_get_ctrl(self,"PDR", "P90");
	ct_gpio_set_ctrl(self,"PDR", "P91", 1);
	ct_gpio_get_ctrl(self,"PDR", "P91");
	ct_gpio_set_ctrl(self,"PDR", "P91", 0);
	ct_gpio_get_ctrl(self,"PDR", "P91");
	ct_gpio_set_ctrl(self,"PDR", "P92", 1);
	ct_gpio_get_ctrl(self,"PDR", "P92");
	ct_gpio_set_ctrl(self,"PDR", "P92", 0);
	ct_gpio_get_ctrl(self,"PDR", "P92");
	ct_gpio_set_ctrl(self,"PDR", "P93", 1);
	ct_gpio_get_ctrl(self,"PDR", "P93");
	ct_gpio_set_ctrl(self,"PDR", "P93", 0);
	ct_gpio_get_ctrl(self,"PDR", "P93");
	ct_gpio_set_ctrl(self,"PDR", "PA0", 1);
	ct_gpio_get_ctrl(self,"PDR", "PA0");
	ct_gpio_set_ctrl(self,"PDR", "PA0", 0);
	ct_gpio_get_ctrl(self,"PDR", "PA0");
	ct_gpio_set_ctrl(self,"PDR", "PA1", 1);
	ct_gpio_get_ctrl(self,"PDR", "PA1");
	ct_gpio_set_ctrl(self,"PDR", "PA1", 0);
	ct_gpio_get_ctrl(self,"PDR", "PA1");
	ct_gpio_set_ctrl(self,"PDR", "PA2", 1);
	ct_gpio_get_ctrl(self,"PDR", "PA2");
	ct_gpio_set_ctrl(self,"PDR", "PA2", 0);
	ct_gpio_get_ctrl(self,"PDR", "PA2");
	ct_gpio_set_ctrl(self,"PDR", "PA3", 1);
	ct_gpio_get_ctrl(self,"PDR", "PA3");
	ct_gpio_set_ctrl(self,"PDR", "PA3", 0);
	ct_gpio_get_ctrl(self,"PDR", "PA3");
	ct_gpio_set_ctrl(self,"PDR", "PA4", 1);
	ct_gpio_get_ctrl(self,"PDR", "PA4");
	ct_gpio_set_ctrl(self,"PDR", "PA4", 0);
	ct_gpio_get_ctrl(self,"PDR", "PA4");
	ct_gpio_set_ctrl(self,"PDR", "PA5", 1);
	ct_gpio_get_ctrl(self,"PDR", "PA5");
	ct_gpio_set_ctrl(self,"PDR", "PA5", 0);
	ct_gpio_get_ctrl(self,"PDR", "PA5");
	ct_gpio_set_ctrl(self,"PDR", "PA6", 1);
	ct_gpio_get_ctrl(self,"PDR", "PA6");
	ct_gpio_set_ctrl(self,"PDR", "PA6", 0);
	ct_gpio_get_ctrl(self,"PDR", "PA6");
	ct_gpio_set_ctrl(self,"PDR", "PA7", 1);
	ct_gpio_get_ctrl(self,"PDR", "PA7");
	ct_gpio_set_ctrl(self,"PDR", "PA7", 0);
	ct_gpio_get_ctrl(self,"PDR", "PA7");
	ct_gpio_set_ctrl(self,"PDR", "PB0", 1);
	ct_gpio_get_ctrl(self,"PDR", "PB0");
	ct_gpio_set_ctrl(self,"PDR", "PB0", 0);
	ct_gpio_get_ctrl(self,"PDR", "PB0");
	ct_gpio_set_ctrl(self,"PDR", "PB1", 1);
	ct_gpio_get_ctrl(self,"PDR", "PB1");
	ct_gpio_set_ctrl(self,"PDR", "PB1", 0);
	ct_gpio_get_ctrl(self,"PDR", "PB1");
	ct_gpio_set_ctrl(self,"PDR", "PB2", 1);
	ct_gpio_get_ctrl(self,"PDR", "PB2");
	ct_gpio_set_ctrl(self,"PDR", "PB2", 0);
	ct_gpio_get_ctrl(self,"PDR", "PB2");
	ct_gpio_set_ctrl(self,"PDR", "PB3", 1);
	ct_gpio_get_ctrl(self,"PDR", "PB3");
	ct_gpio_set_ctrl(self,"PDR", "PB3", 0);
	ct_gpio_get_ctrl(self,"PDR", "PB3");
	ct_gpio_set_ctrl(self,"PDR", "PB4", 1);
	ct_gpio_get_ctrl(self,"PDR", "PB4");
	ct_gpio_set_ctrl(self,"PDR", "PB4", 0);
	ct_gpio_get_ctrl(self,"PDR", "PB4");
	ct_gpio_set_ctrl(self,"PDR", "PC0", 1);
	ct_gpio_get_ctrl(self,"PDR", "PC0");
	ct_gpio_set_ctrl(self,"PDR", "PC0", 0);
	ct_gpio_get_ctrl(self,"PDR", "PC0");
	ct_gpio_set_ctrl(self,"PDR", "PC1", 1);
	ct_gpio_get_ctrl(self,"PDR", "PC1");
	ct_gpio_set_ctrl(self,"PDR", "PC1", 0);
	ct_gpio_get_ctrl(self,"PDR", "PC1");
	ct_gpio_set_ctrl(self,"PDR", "PC2", 1);
	ct_gpio_get_ctrl(self,"PDR", "PC2");
	ct_gpio_set_ctrl(self,"PDR", "PC2", 0);
	ct_gpio_get_ctrl(self,"PDR", "PC2");
	ct_gpio_set_ctrl(self,"PDR", "PC3", 1);
	ct_gpio_get_ctrl(self,"PDR", "PC3");
	ct_gpio_set_ctrl(self,"PDR", "PC3", 0);
	ct_gpio_get_ctrl(self,"PDR", "PC3");
	ct_gpio_set_ctrl(self,"PDR", "PC4", 1);
	ct_gpio_get_ctrl(self,"PDR", "PC4");
	ct_gpio_set_ctrl(self,"PDR", "PC4", 0);
	ct_gpio_get_ctrl(self,"PDR", "PC4");
	ct_gpio_set_ctrl(self,"PDR", "PC5", 1);
	ct_gpio_get_ctrl(self,"PDR", "PC5");
	ct_gpio_set_ctrl(self,"PDR", "PC5", 0);
	ct_gpio_get_ctrl(self,"PDR", "PC5");
	ct_gpio_set_ctrl(self,"PDR", "PD0", 1);
	ct_gpio_get_ctrl(self,"PDR", "PD0");
	ct_gpio_set_ctrl(self,"PDR", "PD0", 0);
	ct_gpio_get_ctrl(self,"PDR", "PD0");
	ct_gpio_set_ctrl(self,"PDR", "PD1", 1);
	ct_gpio_get_ctrl(self,"PDR", "PD1");
	ct_gpio_set_ctrl(self,"PDR", "PD1", 0);
	ct_gpio_get_ctrl(self,"PDR", "PD1");
	ct_gpio_set_ctrl(self,"PDR", "PD2", 1);
	ct_gpio_get_ctrl(self,"PDR", "PD2");
	ct_gpio_set_ctrl(self,"PDR", "PD2", 0);
	ct_gpio_get_ctrl(self,"PDR", "PD2");
	ct_gpio_set_ctrl(self,"PDR", "PD3", 1);
	ct_gpio_get_ctrl(self,"PDR", "PD3");
	ct_gpio_set_ctrl(self,"PDR", "PD3", 0);
	ct_gpio_get_ctrl(self,"PDR", "PD3");
	ct_gpio_set_ctrl(self,"PDR", "PD4", 1);
	ct_gpio_get_ctrl(self,"PDR", "PD4");
	ct_gpio_set_ctrl(self,"PDR", "PD4", 0);
	ct_gpio_get_ctrl(self,"PDR", "PD4");
	ct_gpio_set_ctrl(self,"PDR", "PD5", 1);
	ct_gpio_get_ctrl(self,"PDR", "PD5");
	ct_gpio_set_ctrl(self,"PDR", "PD5", 0);
	ct_gpio_get_ctrl(self,"PDR", "PD5");
	ct_gpio_set_ctrl(self,"PDR", "PD6", 1);
	ct_gpio_get_ctrl(self,"PDR", "PD6");
	ct_gpio_set_ctrl(self,"PDR", "PD6", 0);
	ct_gpio_get_ctrl(self,"PDR", "PD6");
	//	ct_gpio_set_ctrl(self, "PDR", "PE0", 1 );
	//	ct_gpio_get_ctrl(self, "PDR", "PE0");
	//	ct_gpio_set_ctrl(self, "PDR", "PE0", 0 );
	//	ct_gpio_get_ctrl(self, "PDR", "PE0");
	//	ct_gpio_set_ctrl(self, "PDR", "PE1", 1 );
	//	ct_gpio_get_ctrl(self, "PDR", "PE1");
	//	ct_gpio_set_ctrl(self, "PDR", "PE1", 0 );
	//	ct_gpio_get_ctrl(self, "PDR", "PE1");
	//	ct_gpio_set_ctrl(self, "PDR", "PE2", 1 );
	//	ct_gpio_get_ctrl(self, "PDR", "PE2");
	//	ct_gpio_set_ctrl(self, "PDR", "PE2", 0 );
	//	ct_gpio_get_ctrl(self, "PDR", "PE2");
	//	ct_gpio_set_ctrl(self, "PDR", "PE3", 1 );
	//	ct_gpio_get_ctrl(self, "PDR", "PE3");
	//	ct_gpio_set_ctrl(self, "PDR", "PE3", 0 );
	//	ct_gpio_get_ctrl(self, "PDR", "PE3");
	//	ct_gpio_set_ctrl(self, "PDR", "PE4", 1 );
	//	ct_gpio_get_ctrl(self, "PDR", "PE4");
	//	ct_gpio_set_ctrl(self, "PDR", "PE4", 0 );
	//	ct_gpio_get_ctrl(self, "PDR", "PE4");
	//	ct_gpio_set_ctrl(self, "PDR", "PE5", 1 );
	//	ct_gpio_get_ctrl(self, "PDR", "PE5");
	//	ct_gpio_set_ctrl(self, "PDR", "PE5", 0 );
	//	ct_gpio_get_ctrl(self, "PDR", "PE5");
	//	ct_gpio_set_ctrl(self, "PDR", "PF0", 1 );
	//	ct_gpio_get_ctrl(self, "PDR", "PF0");
	//	ct_gpio_set_ctrl(self, "PDR", "PF0", 0 );
	//	ct_gpio_get_ctrl(self, "PDR", "PF0");
	//	ct_gpio_set_ctrl(self, "PDR", "PF1", 1 );
	//	ct_gpio_get_ctrl(self, "PDR", "PF1");
	//	ct_gpio_set_ctrl(self, "PDR", "PF1", 0 );
	//	ct_gpio_get_ctrl(self, "PDR", "PF1");
	//	ct_gpio_set_ctrl(self, "PDR", "PF2", 1 );
	//	ct_gpio_get_ctrl(self, "PDR", "PF2");
	//	ct_gpio_set_ctrl(self, "PDR", "PF2", 0 );
	//	ct_gpio_get_ctrl(self, "PDR", "PF2");
	//	ct_gpio_set_ctrl(self, "PDR", "PF3", 1 );
	//	ct_gpio_get_ctrl(self, "PDR", "PF3");
	//	ct_gpio_set_ctrl(self, "PDR", "PF3", 0 );
	//	ct_gpio_get_ctrl(self, "PDR", "PF3");
	//	ct_gpio_set_ctrl(self, "PDR", "PF4", 1 );
	//	ct_gpio_get_ctrl(self, "PDR", "PF4");
	//	ct_gpio_set_ctrl(self, "PDR", "PF4", 0 );
	//	ct_gpio_get_ctrl(self, "PDR", "PF4");
	ct_gpio_set_ctrl(self,"PDR", "PG0", 1);
	ct_gpio_get_ctrl(self,"PDR", "PG0");
	ct_gpio_set_ctrl(self,"PDR", "PG0", 0);
	ct_gpio_get_ctrl(self,"PDR", "PG0");
	ct_gpio_set_ctrl(self,"PDR", "PG1", 1);
	ct_gpio_get_ctrl(self,"PDR", "PG1");
	ct_gpio_set_ctrl(self,"PDR", "PG1", 0);
	ct_gpio_get_ctrl(self,"PDR", "PG1");
	ct_gpio_set_ctrl(self,"PDR", "PG2", 1);
	ct_gpio_get_ctrl(self,"PDR", "PG2");
	ct_gpio_set_ctrl(self,"PDR", "PG2", 0);
	ct_gpio_get_ctrl(self,"PDR", "PG2");
	ct_gpio_set_ctrl(self,"PDR", "PG3", 1);
	ct_gpio_get_ctrl(self,"PDR", "PG3");
	ct_gpio_set_ctrl(self,"PDR", "PG3", 0);
	ct_gpio_get_ctrl(self,"PDR", "PG3");
	ct_gpio_set_ctrl(self,"PDR", "PG4", 1);
	ct_gpio_get_ctrl(self,"PDR", "PG4");
	ct_gpio_set_ctrl(self,"PDR", "PG4", 0);
	ct_gpio_get_ctrl(self,"PDR", "PG4");
	ct_gpio_set_ctrl(self,"PDR", "PG5", 1);
	ct_gpio_get_ctrl(self,"PDR", "PG5");
	ct_gpio_set_ctrl(self,"PDR", "PG5", 0);
	ct_gpio_get_ctrl(self,"PDR", "PG5");
	ct_gpio_set_ctrl(self,"PDR", "PG6", 1);
	ct_gpio_get_ctrl(self,"PDR", "PG6");
	ct_gpio_set_ctrl(self,"PDR", "PG6", 0);
	ct_gpio_get_ctrl(self,"PDR", "PG6");
	ct_gpio_set_ctrl(self,"PDR", "PG7", 1);
	ct_gpio_get_ctrl(self,"PDR", "PG7");
	ct_gpio_set_ctrl(self,"PDR", "PG7", 0);
	ct_gpio_get_ctrl(self,"PDR", "PG7");
	ct_gpio_set_ctrl(self,"PDR", "PH0", 1);
	ct_gpio_get_ctrl(self,"PDR", "PH0");
	ct_gpio_set_ctrl(self,"PDR", "PH0", 0);
	ct_gpio_get_ctrl(self,"PDR", "PH0");
	ct_gpio_set_ctrl(self,"PDR", "PH1", 1);
	ct_gpio_get_ctrl(self,"PDR", "PH1");
	ct_gpio_set_ctrl(self,"PDR", "PH1", 0);
	ct_gpio_get_ctrl(self,"PDR", "PH1");
	ct_gpio_set_ctrl(self,"PDR", "PH2", 1);
	ct_gpio_get_ctrl(self,"PDR", "PH2");
	ct_gpio_set_ctrl(self,"PDR", "PH2", 0);
	ct_gpio_get_ctrl(self,"PDR", "PH2");
	ct_gpio_set_ctrl(self,"PDR", "PH3", 1);
	ct_gpio_get_ctrl(self,"PDR", "PH3");
	ct_gpio_set_ctrl(self,"PDR", "PH3", 0);
	ct_gpio_get_ctrl(self,"PDR", "PH3");
	ct_gpio_set_ctrl(self,"PDR", "PW0", 1);
	ct_gpio_get_ctrl(self,"PDR", "PW0");
	ct_gpio_set_ctrl(self,"PDR", "PW0", 0);
	ct_gpio_get_ctrl(self,"PDR", "PW0");
	ct_gpio_set_ctrl(self,"PDR", "PW1", 1);
	ct_gpio_get_ctrl(self,"PDR", "PW1");
	ct_gpio_set_ctrl(self,"PDR", "PW1", 0);
	ct_gpio_get_ctrl(self,"PDR", "PW1");
	ct_gpio_set_ctrl(self,"PDR", "PW2", 1);
	ct_gpio_get_ctrl(self,"PDR", "PW2");
	ct_gpio_set_ctrl(self,"PDR", "PW2", 0);
	ct_gpio_get_ctrl(self,"PDR", "PW2");
	ct_gpio_set_ctrl(self,"PDR", "PW3", 1);
	ct_gpio_get_ctrl(self,"PDR", "PW3");
	ct_gpio_set_ctrl(self,"PDR", "PW3", 0);
	ct_gpio_get_ctrl(self,"PDR", "PW3");
	ct_gpio_set_ctrl(self,"PDR", "PW4", 1);
	ct_gpio_get_ctrl(self,"PDR", "PW4");
	ct_gpio_set_ctrl(self,"PDR", "PW4", 0);
	ct_gpio_get_ctrl(self,"PDR", "PW4");
	ct_gpio_set_ctrl(self,"PDR", "PW5", 1);
	ct_gpio_get_ctrl(self,"PDR", "PW5");
	ct_gpio_set_ctrl(self,"PDR", "PW5", 0);
	ct_gpio_get_ctrl(self,"PDR", "PW5");
	ct_gpio_set_ctrl(self,"PDR", "PW6", 1);
	ct_gpio_get_ctrl(self,"PDR", "PW6");
	ct_gpio_set_ctrl(self,"PDR", "PW6", 0);
	ct_gpio_get_ctrl(self,"PDR", "PW6");
	ct_gpio_set_ctrl(self,"PDR", "PW7", 1);
	ct_gpio_get_ctrl(self,"PDR", "PW7");
	ct_gpio_set_ctrl(self,"PDR", "PW7", 0);
	ct_gpio_get_ctrl(self,"PDR", "PW7");
	ct_gpio_set_ctrl(self,"PDR", "PJ0", 1);
	ct_gpio_get_ctrl(self,"PDR", "PJ0");
	ct_gpio_set_ctrl(self,"PDR", "PJ0", 0);
	ct_gpio_get_ctrl(self,"PDR", "PJ0");
	ct_gpio_set_ctrl(self,"PDR", "PJ1", 1);
	ct_gpio_get_ctrl(self,"PDR", "PJ1");
	ct_gpio_set_ctrl(self,"PDR", "PJ1", 0);
	ct_gpio_get_ctrl(self,"PDR", "PJ1");
	ct_gpio_set_ctrl(self,"PDR", "PJ2", 1);
	ct_gpio_get_ctrl(self,"PDR", "PJ2");
	ct_gpio_set_ctrl(self,"PDR", "PJ2", 0);
	ct_gpio_get_ctrl(self,"PDR", "PJ2");
	ct_gpio_set_ctrl(self,"PDR", "PJ3", 1);
	ct_gpio_get_ctrl(self,"PDR", "PJ3");
	ct_gpio_set_ctrl(self,"PDR", "PJ3", 0);
	ct_gpio_get_ctrl(self,"PDR", "PJ3");
	ct_gpio_set_ctrl(self,"PDR", "PJ4", 1);
	ct_gpio_get_ctrl(self,"PDR", "PJ4");
	ct_gpio_set_ctrl(self,"PDR", "PJ4", 0);
	ct_gpio_get_ctrl(self,"PDR", "PJ4");
	ct_gpio_set_ctrl(self,"PDR", "PJ5", 1);
	ct_gpio_get_ctrl(self,"PDR", "PJ5");
	ct_gpio_set_ctrl(self,"PDR", "PJ5", 0);
	ct_gpio_get_ctrl(self,"PDR", "PJ5");
	ct_gpio_set_ctrl(self,"PDR", "PJ6", 1);
	ct_gpio_get_ctrl(self,"PDR", "PJ6");
	ct_gpio_set_ctrl(self,"PDR", "PJ6", 0);
	ct_gpio_get_ctrl(self,"PDR", "PJ6");
	ct_gpio_set_ctrl(self,"PDR", "PJ7", 1);
	ct_gpio_get_ctrl(self,"PDR", "PJ7");
	ct_gpio_set_ctrl(self,"PDR", "PJ7", 0);
	ct_gpio_get_ctrl(self,"PDR", "PJ7");
	ct_gpio_set_ctrl(self,"PDR", "PK0", 1);
	ct_gpio_get_ctrl(self,"PDR", "PK0");
	ct_gpio_set_ctrl(self,"PDR", "PK0", 0);
	ct_gpio_get_ctrl(self,"PDR", "PK0");
	ct_gpio_set_ctrl(self,"PDR", "PK1", 1);
	ct_gpio_get_ctrl(self,"PDR", "PK1");
	ct_gpio_set_ctrl(self,"PDR", "PK1", 0);
	ct_gpio_get_ctrl(self,"PDR", "PK1");
	ct_gpio_set_ctrl(self,"PDR", "PK2", 1);
	ct_gpio_get_ctrl(self,"PDR", "PK2");
	ct_gpio_set_ctrl(self,"PDR", "PK2", 0);
	ct_gpio_get_ctrl(self,"PDR", "PK2");
	ct_gpio_set_ctrl(self,"PDR", "PK3", 1);
	ct_gpio_get_ctrl(self,"PDR", "PK3");
	ct_gpio_set_ctrl(self,"PDR", "PK3", 0);
	ct_gpio_get_ctrl(self,"PDR", "PK3");
	ct_gpio_set_ctrl(self,"PDR", "PK4", 1);
	ct_gpio_get_ctrl(self,"PDR", "PK4");
	ct_gpio_set_ctrl(self,"PDR", "PK4", 0);
	ct_gpio_get_ctrl(self,"PDR", "PK4");
	ct_gpio_set_ctrl(self,"PDR", "PK5", 1);
	ct_gpio_get_ctrl(self,"PDR", "PK5");
	ct_gpio_set_ctrl(self,"PDR", "PK5", 0);
	ct_gpio_get_ctrl(self,"PDR", "PK5");
	ct_gpio_set_ctrl(self,"PDR", "PK6", 1);
	ct_gpio_get_ctrl(self,"PDR", "PK6");
	ct_gpio_set_ctrl(self,"PDR", "PK6", 0);
	ct_gpio_get_ctrl(self,"PDR", "PK6");
	ct_gpio_set_ctrl(self,"PDR", "PK7", 1);
	ct_gpio_get_ctrl(self,"PDR", "PK7");
	ct_gpio_set_ctrl(self,"PDR", "PK7", 0);
	ct_gpio_get_ctrl(self,"PDR", "PK7");
	ct_gpio_set_ctrl(self,"PDR", "PL0", 1);
	ct_gpio_get_ctrl(self,"PDR", "PL0");
	ct_gpio_set_ctrl(self,"PDR", "PL0", 0);
	ct_gpio_get_ctrl(self,"PDR", "PL0");
	ct_gpio_set_ctrl(self,"PDR", "PL1", 1);
	ct_gpio_get_ctrl(self,"PDR", "PL1");
	ct_gpio_set_ctrl(self,"PDR", "PL1", 0);
	ct_gpio_get_ctrl(self,"PDR", "PL1");
	ct_gpio_set_ctrl(self,"PDR", "PL2", 1);
	ct_gpio_get_ctrl(self,"PDR", "PL2");
	ct_gpio_set_ctrl(self,"PDR", "PL2", 0);
	ct_gpio_get_ctrl(self,"PDR", "PL2");
	ct_gpio_set_ctrl(self,"PDR", "PL3", 1);
	ct_gpio_get_ctrl(self,"PDR", "PL3");
	ct_gpio_set_ctrl(self,"PDR", "PL3", 0);
	ct_gpio_get_ctrl(self,"PDR", "PL3");
	ct_gpio_set_ctrl(self,"PDR", "PL4", 1);
	ct_gpio_get_ctrl(self,"PDR", "PL4");
	ct_gpio_set_ctrl(self,"PDR", "PL4", 0);
	ct_gpio_get_ctrl(self,"PDR", "PL4");
	ct_gpio_set_ctrl(self,"PDR", "PL5", 1);
	ct_gpio_get_ctrl(self,"PDR", "PL5");
	ct_gpio_set_ctrl(self,"PDR", "PL5", 0);
	ct_gpio_get_ctrl(self,"PDR", "PL5");
	ct_gpio_set_ctrl(self,"PDR", "PM0", 1);
	ct_gpio_get_ctrl(self,"PDR", "PM0");
	ct_gpio_set_ctrl(self,"PDR", "PM0", 0);
	ct_gpio_get_ctrl(self,"PDR", "PM0");
	ct_gpio_set_ctrl(self,"PDR", "PM1", 1);
	ct_gpio_get_ctrl(self,"PDR", "PM1");
	ct_gpio_set_ctrl(self,"PDR", "PM1", 0);
	ct_gpio_get_ctrl(self,"PDR", "PM1");
	ct_gpio_set_ctrl(self,"PDR", "PM2", 1);
	ct_gpio_get_ctrl(self,"PDR", "PM2");
	ct_gpio_set_ctrl(self,"PDR", "PM2", 0);
	ct_gpio_get_ctrl(self,"PDR", "PM2");
	ct_gpio_set_ctrl(self,"PDR", "PM3", 1);
	ct_gpio_get_ctrl(self,"PDR", "PM3");
	ct_gpio_set_ctrl(self,"PDR", "PM3", 0);
	ct_gpio_get_ctrl(self,"PDR", "PM3");
	ct_gpio_set_ctrl(self,"PDR", "PM4", 1);
	ct_gpio_get_ctrl(self,"PDR", "PM4");
	ct_gpio_set_ctrl(self,"PDR", "PM4", 0);
	ct_gpio_get_ctrl(self,"PDR", "PM4");
	ct_gpio_set_ctrl(self,"PDR", "PN0", 1);
	ct_gpio_get_ctrl(self,"PDR", "PN0");
	ct_gpio_set_ctrl(self,"PDR", "PN0", 0);
	ct_gpio_get_ctrl(self,"PDR", "PN0");
	ct_gpio_set_ctrl(self,"PDR", "PN1", 1);
	ct_gpio_get_ctrl(self,"PDR", "PN1");
	ct_gpio_set_ctrl(self,"PDR", "PN1", 0);
	ct_gpio_get_ctrl(self,"PDR", "PN1");
	ct_gpio_set_ctrl(self,"PDR", "PN2", 1);
	ct_gpio_get_ctrl(self,"PDR", "PN2");
	ct_gpio_set_ctrl(self,"PDR", "PN2", 0);
	ct_gpio_get_ctrl(self,"PDR", "PN2");
	ct_gpio_set_ctrl(self,"PDR", "PN3", 1);
	ct_gpio_get_ctrl(self,"PDR", "PN3");
	ct_gpio_set_ctrl(self,"PDR", "PN3", 0);
	ct_gpio_get_ctrl(self,"PDR", "PN3");
	ct_gpio_set_ctrl(self,"PDR", "PN4", 1);
	ct_gpio_get_ctrl(self,"PDR", "PN4");
	ct_gpio_set_ctrl(self,"PDR", "PN4", 0);
	ct_gpio_get_ctrl(self,"PDR", "PN4");
	ct_gpio_set_ctrl(self,"PDR", "PY0", 1);
	ct_gpio_get_ctrl(self,"PDR", "PY0");
	ct_gpio_set_ctrl(self,"PDR", "PY0", 0);
	ct_gpio_get_ctrl(self,"PDR", "PY0");
	ct_gpio_set_ctrl(self,"PDR", "PY1", 1);
	ct_gpio_get_ctrl(self,"PDR", "PY1");
	ct_gpio_set_ctrl(self,"PDR", "PY1", 0);
	ct_gpio_get_ctrl(self,"PDR", "PY1");
	ct_gpio_set_ctrl(self,"PDR", "PY2", 1);
	ct_gpio_get_ctrl(self,"PDR", "PY2");
	ct_gpio_set_ctrl(self,"PDR", "PY2", 0);
	ct_gpio_get_ctrl(self,"PDR", "PY2");
	ct_gpio_set_ctrl(self,"PDR", "PY3", 1);
	ct_gpio_get_ctrl(self,"PDR", "PY3");
	ct_gpio_set_ctrl(self,"PDR", "PY3", 0);
	ct_gpio_get_ctrl(self,"PDR", "PY3");
	ct_gpio_set_ctrl(self,"PDR", "PY4", 1);
	ct_gpio_get_ctrl(self,"PDR", "PY4");
	ct_gpio_set_ctrl(self,"PDR", "PY4", 0);
	ct_gpio_get_ctrl(self,"PDR", "PY4");
	ct_gpio_set_ctrl(self,"PDR", "PY5", 1);
	ct_gpio_get_ctrl(self,"PDR", "PY5");
	ct_gpio_set_ctrl(self,"PDR", "PY5", 0);
	ct_gpio_get_ctrl(self,"PDR", "PY5");
	ct_gpio_set_ctrl(self,"PDR", "PY6", 1);
	ct_gpio_get_ctrl(self,"PDR", "PY6");
	ct_gpio_set_ctrl(self,"PDR", "PY6", 0);
	ct_gpio_get_ctrl(self,"PDR", "PY6");
	ct_gpio_set_ctrl(self,"PDR", "PY7", 1);
	ct_gpio_get_ctrl(self,"PDR", "PY7");
	ct_gpio_set_ctrl(self,"PDR", "PY7", 0);
	ct_gpio_get_ctrl(self,"PDR", "PY7");
	ct_gpio_set_ctrl(self,"PDR", "PP0", 1);
	ct_gpio_get_ctrl(self,"PDR", "PP0");
	ct_gpio_set_ctrl(self,"PDR", "PP0", 0);
	ct_gpio_get_ctrl(self,"PDR", "PP0");
	ct_gpio_set_ctrl(self,"PDR", "PP1", 1);
	ct_gpio_get_ctrl(self,"PDR", "PP1");
	ct_gpio_set_ctrl(self,"PDR", "PP1", 0);
	ct_gpio_get_ctrl(self,"PDR", "PP1");
	ct_gpio_set_ctrl(self,"PDR", "PP2", 1);
	ct_gpio_get_ctrl(self,"PDR", "PP2");
	ct_gpio_set_ctrl(self,"PDR", "PP2", 0);
	ct_gpio_get_ctrl(self,"PDR", "PP2");
	ct_gpio_set_ctrl(self,"PDR", "PP3", 1);
	ct_gpio_get_ctrl(self,"PDR", "PP3");
	ct_gpio_set_ctrl(self,"PDR", "PP3", 0);
	ct_gpio_get_ctrl(self,"PDR", "PP3");
}

static void ctGpioTest(CtGpio *self)
{
    CtGpioPrivate *priv = CT_GPIO_GET_PRIVATE(self);

    ct_gpio_test_test(priv->ctGpioTest,self);
    ct_gpio_mid_test(priv->ctGpioMidTest,self);
    ct_gpio_end_test(priv->ctGpioEndTest,self);
}

static void ctGpioErr(void)
{
	kint32 ret;
	E_DD_TOP_GPIO_PORT port;
	kuchar val;

	// port error
	port = E_DD_TOP_GPIO_PORT_MAX;
	val = 0;
	ret = dd_topfour_set_gpio_function(port, val);
	Ddim_Print(("dd_topfour_set_gpio_function(): port error. ret=%d, port=%d\n", ret, port));

	ret = dd_topthree_set_gpio_direction(port, val);
	Ddim_Print(("dd_topthree_set_gpio_direction(): port error. ret=%d, port=%d\n", ret, port));

	ret = dd_toptwo_set_gpio_status(port, val);
	Ddim_Print(("dd_toptwo_set_gpio_status(): port error. ret=%d, port=%d\n", ret, port));

	ret = dd_top_set_gpio_pull_up_down_enable(port, val);
	Ddim_Print(("dd_top_set_gpio_pull_up_down_enable(): port error. ret=%d, port=%d\n", ret, port));

	ret = dd_top_set_gpio_pull_up_down_ctrl(port, val);
	Ddim_Print(("dd_top_set_gpio_pull_up_down_ctrl(): port error. ret=%d, port=%d\n", ret, port));

	ret = dd_topfour_get_gpio_function(port, &val);
	Ddim_Print(("dd_topfour_get_gpio_function(): port error. ret=%d, port=%d\n", ret, port));

	ret = dd_topfour_get_gpio_direction(port, &val);
	Ddim_Print(("dd_topfour_get_gpio_direction(): port error. ret=%d, port=%d\n", ret, port));

	ret = dd_topfour_get_gpio_status(port, &val);
	Ddim_Print(("dd_topfour_get_gpio_status(): port error. ret=%d, port=%d\n", ret, port));

	ret = dd_top_get_gpio_pull_up_down_enable(port, &val);
	Ddim_Print(("dd_top_get_gpio_pull_up_down_enable(): port error. ret=%d, port=%d\n", ret, port));

	ret = dd_top_get_gpio_pull_up_down_ctrl(port, &val);
	Ddim_Print(("dd_top_get_gpio_pull_up_down_ctrl(): port error. ret=%d, port=%d\n", ret, port));

	// value error
	port = E_DD_TOP_GPIO_PP3;
	val = 2;
	ret = dd_topfour_set_gpio_function(port, val);
	Ddim_Print(("dd_topfour_set_gpio_function(): value error. ret=%d, val=%d\n", ret, val));

	ret = dd_topthree_set_gpio_direction(port, val);
	Ddim_Print(("dd_topthree_set_gpio_direction(): value error. ret=%d, val=%d\n", ret, val));

	ret = dd_toptwo_set_gpio_status(port, val);
	Ddim_Print(("dd_toptwo_set_gpio_status(): value error. ret=%d, val=%d\n", ret, val));

	ret = dd_top_set_gpio_pull_up_down_enable(port, val);
	Ddim_Print(("dd_top_set_gpio_pull_up_down_enable(): value error. ret=%d, val=%d\n", ret, val));

	ret = dd_top_set_gpio_pull_up_down_ctrl(port, val);
	Ddim_Print(("dd_top_set_gpio_pull_up_down_ctrl(): value error. ret=%d, val=%d\n", ret, val));

	ret = dd_topfour_get_gpio_function(port, NULL);
	Ddim_Print(("dd_topfour_get_gpio_function(): value error. ret=%d, val=NULL\n", ret));

	ret = dd_topfour_get_gpio_direction(port, NULL);
	Ddim_Print(("dd_topfour_get_gpio_direction(): value error. ret=%d, val=NULL\n", ret));

	ret = dd_topfour_get_gpio_status(port, NULL);
	Ddim_Print(("dd_topfour_get_gpio_status(): value error. ret=%d, val=NULL\n", ret));

	ret = dd_top_get_gpio_pull_up_down_enable(port, NULL);
	Ddim_Print(("dd_top_get_gpio_pull_up_down_enable(): value error. ret=%d, val=NULL\n", ret));

	ret = dd_top_get_gpio_pull_up_down_ctrl(port, NULL);
	Ddim_Print(("dd_top_get_gpio_pull_up_down_ctrl(): value error. ret=%d, val=NULL\n", ret));
}
/****************
* PUBLIC
*/
void ct_gpio_get_ctrl(CtGpio*self,kchar *reg, kchar *port)
{
	kuchar val;
	kint32 ret;
	E_DD_TOP_GPIO_PORT port_index;

	for (port_index = (E_DD_TOP_GPIO_PORT)0; port_index < E_DD_TOP_GPIO_PORT_MAX; port_index++)
	{
		if (0 == strcmp(port, S_GDD_TOP_PORT_NAME[port_index]))
		{
			break;
		}
	}
	if (port_index == E_DD_TOP_GPIO_PORT_MAX)
	{
		Ddim_Print(("please check 4th parameter!!\n"));
		return;
	}

	if (0 == strcmp(reg, "EPCR"))
	{
		ret = dd_topfour_get_gpio_function(port_index, &val);
		Ddim_Print(("dd_topfour_get_gpio_function(): ret=%d, %s.%s=%d\n", ret, reg, port, val));
	}
	else if (0 == strcmp(reg, "DDR"))
	{
		ret = dd_topfour_get_gpio_direction(port_index, &val);
		Ddim_Print(("dd_topfour_get_gpio_direction(): ret=%d, %s.%s=%d\n", ret, reg, port, val));
	}
	else if (0 == strcmp(reg, "PDR"))
	{
		ret = dd_topfour_get_gpio_status(port_index, &val);
		Ddim_Print(("dd_topfour_get_gpio_status(): ret=%d, %s.%s=%d\n", ret, reg, port, val));
	}
	else if (0 == strcmp(reg, "PUDER"))
	{
		ret = dd_top_get_gpio_pull_up_down_enable(port_index, &val);
		Ddim_Print(("dd_top_get_gpio_pull_up_down_enable(): ret=%d, %s.%s=%d\n", ret, reg, port, val));
	}
	else if (0 == strcmp(reg, "PUDCR"))
	{
		ret = dd_top_get_gpio_pull_up_down_ctrl(port_index, &val);
		Ddim_Print(("dd_top_get_gpio_pull_up_down_ctrl(): ret=%d, %s.%s=%d\n", ret, reg, port, val));
	}else {
		Ddim_Print(("please check 3rd parameter!!\n"));
	}
}

void ct_gpio_set_ctrl(CtGpio*self,kchar *reg, kchar *port, kuchar val)
{
	kint32 ret;
	E_DD_TOP_GPIO_PORT port_index;

	for (port_index = (E_DD_TOP_GPIO_PORT)0; port_index < E_DD_TOP_GPIO_PORT_MAX; port_index++)
	{
		if (0 == strcmp(port, S_GDD_TOP_PORT_NAME[port_index]))
		{
			break;
		}
	}
	if (port_index == E_DD_TOP_GPIO_PORT_MAX)
	{
		Ddim_Print(("please check 4th parameter!!\n"));
		return;
	}

	if (0 == strcmp(reg, "EPCR"))
	{
		ret = dd_topfour_set_gpio_function(port_index, val);
		Ddim_Print(("dd_topfour_set_gpio_function(): ret=%d, %s.%s=%d\n", ret, reg, port, val));
	}
	else if (0 == strcmp(reg, "DDR"))
	{
		ret = dd_topthree_set_gpio_direction(port_index, val);
		Ddim_Print(("dd_topthree_set_gpio_direction(): ret=%d, %s.%s=%d\n", ret, reg, port, val));
	}
	else if (0 == strcmp(reg, "PDR"))
	{
		ret = dd_toptwo_set_gpio_status(port_index, val);
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
		CtGpioCopy* ctGpioCopy = ct_gpio_copy_new();
		ct_gpio_copy_pdr_pc(ctGpioCopy,port_index, val);
		k_object_unref(ctGpioCopy);
#endif
		Ddim_Print(("dd_toptwo_set_gpio_status(): ret=%d, %s.%s=%d\n", ret, reg, port, val));
	}
	else if (0 == strcmp(reg, "PUDER"))
	{
		ret = dd_top_set_gpio_pull_up_down_enable(port_index, val);
		Ddim_Print(("dd_top_set_gpio_pull_up_down_enable(): ret=%d, %s.%s=%d\n", ret, reg, port, val));
	}
	else if (0 == strcmp(reg, "PUDCR"))
	{
		ret = dd_top_set_gpio_pull_up_down_ctrl(port_index, val);
		Ddim_Print(("dd_top_set_gpio_pull_up_down_ctrl(): ret=%d, %s.%s=%d\n", ret, reg, port, val));
	}else {
		Ddim_Print(("please check 3rd parameter!!\n"));
	}
}

void ct_gpio_control(CtGpio *self)
{
    if (0 == strcmp(((CtDdParameter *)self)->argv[2], "get"))
    {
        ct_gpio_get_ctrl(self,((CtDdParameter *)self)->argv[3], ((CtDdParameter *)self)->argv[4]);
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[2], "set"))
    {
        ct_gpio_set_ctrl(self,((CtDdParameter *)self)->argv[3], ((CtDdParameter *)self)->argv[4], atoi(((CtDdParameter *)self)->argv[5]));
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[2], "test"))
    {
        ctGpioTest(self);
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[2], "test_pdr"))
    {
        ctGpioTestPdr(self,((CtDdParameter *)self)->argc, ((CtDdParameter *)self)->argv);
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[2], "err"))
    {
        ctGpioErr();
    }
    else
    {
        Ddim_Print(("please check 2nd parameter!!\n"));
    }
}

CtGpio* ct_gpio_new(void) 
{
    CtGpio *self = k_object_new_with_private(CT_TYPE_GPIO, sizeof(CtGpioPrivate));
    return self;
}
