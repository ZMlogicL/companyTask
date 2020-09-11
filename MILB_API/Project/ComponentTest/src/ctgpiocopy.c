/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
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
#include "ctgpiocopy.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtGpioCopy, ct_gpio_copy);
#define CT_GPIO_COPY_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtGpioCopyPrivate,CT_TYPE_GPIO_COPY))

struct _CtGpioCopyPrivate
{
	kint a;
};
/****************
* DECLS
*/
static void 			ct_gpio_copy_constructor(CtGpioCopy *self);
static void 			ct_gpio_copy_destructor(CtGpioCopy *self);
/****************
* IMPL
*/
static void ct_gpio_copy_constructor(CtGpioCopy *self) 
{
//	CtGpioCopyPrivate *priv = CT_GPIO_COPY_GET_PRIVATE(self);
}

static void ct_gpio_copy_destructor(CtGpioCopy *self) 
{
//	CtGpioCopyPrivate *priv = CT_GPIO_COPY_GET_PRIVATE(self);
}
/****************
* PUBLIC
*/
#ifdef CtGpio_D_DD_TOP_PC_DEBUG
kint32 ct_gpio_copy_pdr_pc(CtGpioCopy *self,E_DD_TOP_GPIO_PORT port, kuchar status)
{
	switch (port)
	{
	case E_DD_TOP_GPIO_P60:
		IO_CHIPTOP.PDR.bit.P60 = status;
		IO_CHIPTOP.PDR.bit.PWE60 = 1;
		break;
	case E_DD_TOP_GPIO_P61:
		IO_CHIPTOP.PDR.bit.P61 = status;
		IO_CHIPTOP.PDR.bit.PWE61 = 1;
		break;
	case E_DD_TOP_GPIO_P62:
		IO_CHIPTOP.PDR.bit.P62 = status;
		IO_CHIPTOP.PDR.bit.PWE62 = 1;
		break;
	case E_DD_TOP_GPIO_P63:
		IO_CHIPTOP.PDR.bit.P63 = status;
		IO_CHIPTOP.PDR.bit.PWE63 = 1;
		break;
	case E_DD_TOP_GPIO_P64:
		IO_CHIPTOP.PDR.bit.P64 = status;
		IO_CHIPTOP.PDR.bit.PWE64 = 1;
		break;
	case E_DD_TOP_GPIO_P65:
		IO_CHIPTOP.PDR.bit.P65 = status;
		IO_CHIPTOP.PDR.bit.PWE65 = 1;
		break;
	case E_DD_TOP_GPIO_P66:
		IO_CHIPTOP.PDR.bit.P66 = status;
		IO_CHIPTOP.PDR.bit.PWE66 = 1;
		break;
	case E_DD_TOP_GPIO_P67:
		IO_CHIPTOP.PDR.bit.P67 = status;
		IO_CHIPTOP.PDR.bit.PWE67 = 1;
		break;
	case E_DD_TOP_GPIO_P70:
		IO_CHIPTOP.PDR.bit.P70 = status;
		IO_CHIPTOP.PDR.bit.PWE70 = 1;
		break;
	case E_DD_TOP_GPIO_P71:
		IO_CHIPTOP.PDR.bit.P71 = status;
		IO_CHIPTOP.PDR.bit.PWE71 = 1;
		break;
	case E_DD_TOP_GPIO_P72:
		IO_CHIPTOP.PDR.bit.P72 = status;
		IO_CHIPTOP.PDR.bit.PWE72 = 1;
		break;
	case E_DD_TOP_GPIO_P73:
		IO_CHIPTOP.PDR.bit.P73 = status;
		IO_CHIPTOP.PDR.bit.PWE73 = 1;
		break;
	case E_DD_TOP_GPIO_P74:
		IO_CHIPTOP.PDR.bit.P74 = status;
		IO_CHIPTOP.PDR.bit.PWE74 = 1;
		break;
	case E_DD_TOP_GPIO_P75:
		IO_CHIPTOP.PDR.bit.P75 = status;
		IO_CHIPTOP.PDR.bit.PWE75 = 1;
		break;
	case E_DD_TOP_GPIO_P76:
		IO_CHIPTOP.PDR.bit.P76 = status;
		IO_CHIPTOP.PDR.bit.PWE76 = 1;
		break;
	case E_DD_TOP_GPIO_P77:
		IO_CHIPTOP.PDR.bit.P77 = status;
		IO_CHIPTOP.PDR.bit.PWE77 = 1;
		break;
	case E_DD_TOP_GPIO_P80:
		IO_CHIPTOP.PDR.bit.P80 = status;
		IO_CHIPTOP.PDR.bit.PWE80 = 1;
		break;
	case E_DD_TOP_GPIO_P81:
		IO_CHIPTOP.PDR.bit.P81 = status;
		IO_CHIPTOP.PDR.bit.PWE81 = 1;
		break;
	case E_DD_TOP_GPIO_P82:
		IO_CHIPTOP.PDR.bit.P82 = status;
		IO_CHIPTOP.PDR.bit.PWE82 = 1;
		break;
	case E_DD_TOP_GPIO_P83:
		IO_CHIPTOP.PDR.bit.P83 = status;
		IO_CHIPTOP.PDR.bit.PWE83 = 1;
		break;
	case E_DD_TOP_GPIO_P84:
		IO_CHIPTOP.PDR.bit.P84 = status;
		IO_CHIPTOP.PDR.bit.PWE84 = 1;
		break;
	case E_DD_TOP_GPIO_P85:
		IO_CHIPTOP.PDR.bit.P85 = status;
		IO_CHIPTOP.PDR.bit.PWE85 = 1;
		break;
	case E_DD_TOP_GPIO_P86:
		IO_CHIPTOP.PDR.bit.P86 = status;
		IO_CHIPTOP.PDR.bit.PWE86 = 1;
		break;
	case E_DD_TOP_GPIO_P87:
		IO_CHIPTOP.PDR.bit.P87 = status;
		IO_CHIPTOP.PDR.bit.PWE87 = 1;
		break;
	case E_DD_TOP_GPIO_P90:
		IO_CHIPTOP.PDR.bit.P90 = status;
		IO_CHIPTOP.PDR.bit.PWE90 = 1;
		break;
	case E_DD_TOP_GPIO_P91:
		IO_CHIPTOP.PDR.bit.P91 = status;
		IO_CHIPTOP.PDR.bit.PWE91 = 1;
		break;
	case E_DD_TOP_GPIO_P92:
		IO_CHIPTOP.PDR.bit.P92 = status;
		IO_CHIPTOP.PDR.bit.PWE92 = 1;
		break;
	case E_DD_TOP_GPIO_P93:
		IO_CHIPTOP.PDR.bit.P93 = status;
		IO_CHIPTOP.PDR.bit.PWE93 = 1;
		break;
	case E_DD_TOP_GPIO_PA0:
		IO_CHIPTOP.PDR.bit.PA0 = status;
		IO_CHIPTOP.PDR.bit.PWEA0 = 1;
		break;
	case E_DD_TOP_GPIO_PA1:
		IO_CHIPTOP.PDR.bit.PA1 = status;
		IO_CHIPTOP.PDR.bit.PWEA1 = 1;
		break;
	case E_DD_TOP_GPIO_PA2:
		IO_CHIPTOP.PDR.bit.PA2 = status;
		IO_CHIPTOP.PDR.bit.PWEA2 = 1;
		break;
	case E_DD_TOP_GPIO_PA3:
		IO_CHIPTOP.PDR.bit.PA3 = status;
		IO_CHIPTOP.PDR.bit.PWEA3 = 1;
		break;
	case E_DD_TOP_GPIO_PA4:
		IO_CHIPTOP.PDR.bit.PA4 = status;
		IO_CHIPTOP.PDR.bit.PWEA4 = 1;
		break;
	case E_DD_TOP_GPIO_PA5:
		IO_CHIPTOP.PDR.bit.PA5 = status;
		IO_CHIPTOP.PDR.bit.PWEA5 = 1;
		break;
	case E_DD_TOP_GPIO_PA6:
		IO_CHIPTOP.PDR.bit.PA6 = status;
		IO_CHIPTOP.PDR.bit.PWEA6 = 1;
		break;
	case E_DD_TOP_GPIO_PA7:
		IO_CHIPTOP.PDR.bit.PA7 = status;
		IO_CHIPTOP.PDR.bit.PWEA7 = 1;
		break;
	case E_DD_TOP_GPIO_PB0:
		IO_CHIPTOP.PDR.bit.PB0 = status;
		IO_CHIPTOP.PDR.bit.PWEB0 = 1;
		break;
	case E_DD_TOP_GPIO_PB1:
		IO_CHIPTOP.PDR.bit.PB1 = status;
		IO_CHIPTOP.PDR.bit.PWEB1 = 1;
		break;
	case E_DD_TOP_GPIO_PB2:
		IO_CHIPTOP.PDR.bit.PB2 = status;
		IO_CHIPTOP.PDR.bit.PWEB2 = 1;
		break;
	case E_DD_TOP_GPIO_PB3:
		IO_CHIPTOP.PDR.bit.PB3 = status;
		IO_CHIPTOP.PDR.bit.PWEB3 = 1;
		break;
	case E_DD_TOP_GPIO_PB4:
		IO_CHIPTOP.PDR.bit.PB4 = status;
		IO_CHIPTOP.PDR.bit.PWEB4 = 1;
		break;
	case E_DD_TOP_GPIO_PC0L:
		IO_CHIPTOP.PDR.bit.PC0 = status;
		IO_CHIPTOP.PDR.bit.PWEC0 = 1;
		break;
	case E_DD_TOP_GPIO_PC1L:
		IO_CHIPTOP.PDR.bit.PC1 = status;
		IO_CHIPTOP.PDR.bit.PWEC1 = 1;
		break;
	case E_DD_TOP_GPIO_PC2L:
		IO_CHIPTOP.PDR.bit.PC2 = status;
		IO_CHIPTOP.PDR.bit.PWEC2 = 1;
		break;
	case E_DD_TOP_GPIO_PC3L:
		IO_CHIPTOP.PDR.bit.PC3 = status;
		IO_CHIPTOP.PDR.bit.PWEC3 = 1;
		break;
	case E_DD_TOP_GPIO_PC4L:
		IO_CHIPTOP.PDR.bit.PC4 = status;
		IO_CHIPTOP.PDR.bit.PWEC4 = 1;
		break;
	case E_DD_TOP_GPIO_PC5L:
		IO_CHIPTOP.PDR.bit.PC5 = status;
		IO_CHIPTOP.PDR.bit.PWEC5 = 1;
		break;
	case E_DD_TOP_GPIO_PD0:
		IO_CHIPTOP.PDR.bit.PD0 = status;
		IO_CHIPTOP.PDR.bit.PWED0 = 1;
		break;
	case E_DD_TOP_GPIO_PD1:
		IO_CHIPTOP.PDR.bit.PD1 = status;
		IO_CHIPTOP.PDR.bit.PWED1 = 1;
		break;
	case E_DD_TOP_GPIO_PD2:
		IO_CHIPTOP.PDR.bit.PD2 = status;
		IO_CHIPTOP.PDR.bit.PWED2 = 1;
		break;
	case E_DD_TOP_GPIO_PD3:
		IO_CHIPTOP.PDR.bit.PD3 = status;
		IO_CHIPTOP.PDR.bit.PWED3 = 1;
		break;
	case E_DD_TOP_GPIO_PD4:
		IO_CHIPTOP.PDR.bit.PD4 = status;
		IO_CHIPTOP.PDR.bit.PWED4 = 1;
		break;
	case E_DD_TOP_GPIO_PD5:
		IO_CHIPTOP.PDR.bit.PD5 = status;
		IO_CHIPTOP.PDR.bit.PWED5 = 1;
		break;
	case E_DD_TOP_GPIO_PD6:
		IO_CHIPTOP.PDR.bit.PD6 = status;
		IO_CHIPTOP.PDR.bit.PWED6 = 1;
		break;
	case E_DD_TOP_GPIO_PE0:
		IO_CHIPTOP.PDR.bit.PE0 = status;
		IO_CHIPTOP.PDR.bit.PWEE0 = 1;
		break;
	case E_DD_TOP_GPIO_PE1:
		IO_CHIPTOP.PDR.bit.PE1 = status;
		IO_CHIPTOP.PDR.bit.PWEE1 = 1;
		break;
	case E_DD_TOP_GPIO_PE2:
		IO_CHIPTOP.PDR.bit.PE2 = status;
		IO_CHIPTOP.PDR.bit.PWEE2 = 1;
		break;
	case E_DD_TOP_GPIO_PE3:
		IO_CHIPTOP.PDR.bit.PE3 = status;
		IO_CHIPTOP.PDR.bit.PWEE3 = 1;
		break;
	case E_DD_TOP_GPIO_PE4:
		IO_CHIPTOP.PDR.bit.PE4 = status;
		IO_CHIPTOP.PDR.bit.PWEE4 = 1;
		break;
	case E_DD_TOP_GPIO_PE5:
		IO_CHIPTOP.PDR.bit.PE5 = status;
		IO_CHIPTOP.PDR.bit.PWEE5 = 1;
		break;
	case E_DD_TOP_GPIO_PF0:
		IO_CHIPTOP.PDR.bit.PF0 = status;
		IO_CHIPTOP.PDR.bit.PWEF0 = 1;
		break;
	case E_DD_TOP_GPIO_PF1:
		IO_CHIPTOP.PDR.bit.PF1 = status;
		IO_CHIPTOP.PDR.bit.PWEF1 = 1;
		break;
	case E_DD_TOP_GPIO_PF2:
		IO_CHIPTOP.PDR.bit.PF2 = status;
		IO_CHIPTOP.PDR.bit.PWEF2 = 1;
		break;
	case E_DD_TOP_GPIO_PF3:
		IO_CHIPTOP.PDR.bit.PF3 = status;
		IO_CHIPTOP.PDR.bit.PWEF3 = 1;
		break;
	case E_DD_TOP_GPIO_PF4:
		IO_CHIPTOP.PDR.bit.PF4 = status;
		IO_CHIPTOP.PDR.bit.PWEF4 = 1;
		break;
	case E_DD_TOP_GPIO_PG0:
		IO_CHIPTOP.PDR.bit.PG0 = status;
		IO_CHIPTOP.PDR.bit.PWEG0 = 1;
		break;
	case E_DD_TOP_GPIO_PG1:
		IO_CHIPTOP.PDR.bit.PG1 = status;
		IO_CHIPTOP.PDR.bit.PWEG1 = 1;
		break;
	case E_DD_TOP_GPIO_PG2:
		IO_CHIPTOP.PDR.bit.PG2 = status;
		IO_CHIPTOP.PDR.bit.PWEG2 = 1;
		break;
	case E_DD_TOP_GPIO_PG3:
		IO_CHIPTOP.PDR.bit.PG3 = status;
		IO_CHIPTOP.PDR.bit.PWEG3 = 1;
		break;
	case E_DD_TOP_GPIO_PG4:
		IO_CHIPTOP.PDR.bit.PG4 = status;
		IO_CHIPTOP.PDR.bit.PWEG4 = 1;
		break;
	case E_DD_TOP_GPIO_PG5:
		IO_CHIPTOP.PDR.bit.PG5 = status;
		IO_CHIPTOP.PDR.bit.PWEG5 = 1;
		break;
	case E_DD_TOP_GPIO_PG6:
		IO_CHIPTOP.PDR.bit.PG6 = status;
		IO_CHIPTOP.PDR.bit.PWEG6 = 1;
		break;
	case E_DD_TOP_GPIO_PG7:
		IO_CHIPTOP.PDR.bit.PG7 = status;
		IO_CHIPTOP.PDR.bit.PWEG7 = 1;
		break;
	case E_DD_TOP_GPIO_PH0:
		IO_CHIPTOP.PDR.bit.PH0 = status;
		IO_CHIPTOP.PDR.bit.PWEH0 = 1;
		break;
	case E_DD_TOP_GPIO_PH1:
		IO_CHIPTOP.PDR.bit.PH1 = status;
		IO_CHIPTOP.PDR.bit.PWEH1 = 1;
		break;
	case E_DD_TOP_GPIO_PH2:
		IO_CHIPTOP.PDR.bit.PH2 = status;
		IO_CHIPTOP.PDR.bit.PWEH2 = 1;
		break;
	case E_DD_TOP_GPIO_PH3:
		IO_CHIPTOP.PDR.bit.PH3 = status;
		IO_CHIPTOP.PDR.bit.PWEH3 = 1;
		break;
	case E_DD_TOP_GPIO_PW0:
		IO_CHIPTOP.PDR.bit.PW0 = status;
		IO_CHIPTOP.PDR.bit.PWEW0 = 1;
		break;
	case E_DD_TOP_GPIO_PW1:
		IO_CHIPTOP.PDR.bit.PW1 = status;
		IO_CHIPTOP.PDR.bit.PWEW1 = 1;
		break;
	case E_DD_TOP_GPIO_PW2:
		IO_CHIPTOP.PDR.bit.PW2 = status;
		IO_CHIPTOP.PDR.bit.PWEW2 = 1;
		break;
	case E_DD_TOP_GPIO_PW3:
		IO_CHIPTOP.PDR.bit.PW3 = status;
		IO_CHIPTOP.PDR.bit.PWEW3 = 1;
		break;
	case E_DD_TOP_GPIO_PW4:
		IO_CHIPTOP.PDR.bit.PW4 = status;
		IO_CHIPTOP.PDR.bit.PWEW4 = 1;
		break;
	case E_DD_TOP_GPIO_PW5:
		IO_CHIPTOP.PDR.bit.PW5 = status;
		IO_CHIPTOP.PDR.bit.PWEW5 = 1;
		break;
	case E_DD_TOP_GPIO_PW6:
		IO_CHIPTOP.PDR.bit.PW6 = status;
		IO_CHIPTOP.PDR.bit.PWEW6 = 1;
		break;
	case E_DD_TOP_GPIO_PW7:
		IO_CHIPTOP.PDR.bit.PW7 = status;
		IO_CHIPTOP.PDR.bit.PWEW7 = 1;
		break;
	case E_DD_TOP_GPIO_PJ0:
		IO_CHIPTOP.PDR.bit.PJ0 = status;
		IO_CHIPTOP.PDR.bit.PWEJ0 = 1;
		break;
	case E_DD_TOP_GPIO_PJ1:
		IO_CHIPTOP.PDR.bit.PJ1 = status;
		IO_CHIPTOP.PDR.bit.PWEJ1 = 1;
		break;
	case E_DD_TOP_GPIO_PJ2:
		IO_CHIPTOP.PDR.bit.PJ2 = status;
		IO_CHIPTOP.PDR.bit.PWEJ2 = 1;
		break;
	case E_DD_TOP_GPIO_PJ3:
		IO_CHIPTOP.PDR.bit.PJ3 = status;
		IO_CHIPTOP.PDR.bit.PWEJ3 = 1;
		break;
	case E_DD_TOP_GPIO_PJ4:
		IO_CHIPTOP.PDR.bit.PJ4 = status;
		IO_CHIPTOP.PDR.bit.PWEJ4 = 1;
		break;
	case E_DD_TOP_GPIO_PJ5:
		IO_CHIPTOP.PDR.bit.PJ5 = status;
		IO_CHIPTOP.PDR.bit.PWEJ5 = 1;
		break;
	case E_DD_TOP_GPIO_PJ6:
		IO_CHIPTOP.PDR.bit.PJ6 = status;
		IO_CHIPTOP.PDR.bit.PWEJ6 = 1;
		break;
	case E_DD_TOP_GPIO_PJ7:
		IO_CHIPTOP.PDR.bit.PJ7 = status;
		IO_CHIPTOP.PDR.bit.PWEJ7 = 1;
		break;
	case E_DD_TOP_GPIO_PK0:
		IO_CHIPTOP.PDR.bit.PK0 = status;
		IO_CHIPTOP.PDR.bit.PWEK0 = 1;
		break;
	case E_DD_TOP_GPIO_PK1:
		IO_CHIPTOP.PDR.bit.PK1 = status;
		IO_CHIPTOP.PDR.bit.PWEK1 = 1;
		break;
	case E_DD_TOP_GPIO_PK2:
		IO_CHIPTOP.PDR.bit.PK2 = status;
		IO_CHIPTOP.PDR.bit.PWEK2 = 1;
		break;
	case E_DD_TOP_GPIO_PK3:
		IO_CHIPTOP.PDR.bit.PK3 = status;
		IO_CHIPTOP.PDR.bit.PWEK3 = 1;
		break;
	case E_DD_TOP_GPIO_PK4:
		IO_CHIPTOP.PDR.bit.PK4 = status;
		IO_CHIPTOP.PDR.bit.PWEK4 = 1;
		break;
	case E_DD_TOP_GPIO_PK5:
		IO_CHIPTOP.PDR.bit.PK5 = status;
		IO_CHIPTOP.PDR.bit.PWEK5 = 1;
		break;
	case E_DD_TOP_GPIO_PK6:
		IO_CHIPTOP.PDR.bit.PK6 = status;
		IO_CHIPTOP.PDR.bit.PWEK6 = 1;
		break;
	case E_DD_TOP_GPIO_PK7:
		IO_CHIPTOP.PDR.bit.PK7 = status;
		IO_CHIPTOP.PDR.bit.PWEK7 = 1;
		break;
	case E_DD_TOP_GPIO_PL0:
		IO_CHIPTOP.PDR.bit.PL0 = status;
		IO_CHIPTOP.PDR.bit.PWEL0 = 1;
		break;
	case E_DD_TOP_GPIO_PL1:
		IO_CHIPTOP.PDR.bit.PL1 = status;
		IO_CHIPTOP.PDR.bit.PWEL1 = 1;
		break;
	case E_DD_TOP_GPIO_PL2:
		IO_CHIPTOP.PDR.bit.PL2 = status;
		IO_CHIPTOP.PDR.bit.PWEL2 = 1;
		break;
	case E_DD_TOP_GPIO_PL3:
		IO_CHIPTOP.PDR.bit.PL3 = status;
		IO_CHIPTOP.PDR.bit.PWEL3 = 1;
		break;
	case E_DD_TOP_GPIO_PL4:
		IO_CHIPTOP.PDR.bit.PL4 = status;
		IO_CHIPTOP.PDR.bit.PWEL4 = 1;
		break;
	case E_DD_TOP_GPIO_PL5:
		IO_CHIPTOP.PDR.bit.PL5 = status;
		IO_CHIPTOP.PDR.bit.PWEL5 = 1;
		break;
	case E_DD_TOP_GPIO_PM0:
		IO_CHIPTOP.PDR.bit.PM0 = status;
		IO_CHIPTOP.PDR.bit.PWEM0 = 1;
		break;
	case E_DD_TOP_GPIO_PM1:
		IO_CHIPTOP.PDR.bit.PM1 = status;
		IO_CHIPTOP.PDR.bit.PWEM1 = 1;
		break;
	case E_DD_TOP_GPIO_PM2:
		IO_CHIPTOP.PDR.bit.PM2 = status;
		IO_CHIPTOP.PDR.bit.PWEM2 = 1;
		break;
	case E_DD_TOP_GPIO_PM3:
		IO_CHIPTOP.PDR.bit.PM3 = status;
		IO_CHIPTOP.PDR.bit.PWEM3 = 1;
		break;
	case E_DD_TOP_GPIO_PM4:
		IO_CHIPTOP.PDR.bit.PM4 = status;
		IO_CHIPTOP.PDR.bit.PWEM4 = 1;
		break;
	case E_DD_TOP_GPIO_PN0:
		IO_CHIPTOP.PDR.bit.PN0 = status;
		IO_CHIPTOP.PDR.bit.PWEN0 = 1;
		break;
	case E_DD_TOP_GPIO_PN1:
		IO_CHIPTOP.PDR.bit.PN1 = status;
		IO_CHIPTOP.PDR.bit.PWEN1 = 1;
		break;
	case E_DD_TOP_GPIO_PN2:
		IO_CHIPTOP.PDR.bit.PN2 = status;
		IO_CHIPTOP.PDR.bit.PWEN2 = 1;
		break;
	case E_DD_TOP_GPIO_PN3:
		IO_CHIPTOP.PDR.bit.PN3 = status;
		IO_CHIPTOP.PDR.bit.PWEN3 = 1;
		break;
	case E_DD_TOP_GPIO_PN4:
		IO_CHIPTOP.PDR.bit.PN4 = status;
		IO_CHIPTOP.PDR.bit.PWEN4 = 1;
		break;
	case E_DD_TOP_GPIO_PY0:
		IO_CHIPTOP.PDR.bit.PY0 = status;
		IO_CHIPTOP.PDR.bit.PWEY0 = 1;
		break;
	case E_DD_TOP_GPIO_PY1:
		IO_CHIPTOP.PDR.bit.PY1 = status;
		IO_CHIPTOP.PDR.bit.PWEY1 = 1;
		break;
	case E_DD_TOP_GPIO_PY2:
		IO_CHIPTOP.PDR.bit.PY2 = status;
		IO_CHIPTOP.PDR.bit.PWEY2 = 1;
		break;
	case E_DD_TOP_GPIO_PY3:
		IO_CHIPTOP.PDR.bit.PY3 = status;
		IO_CHIPTOP.PDR.bit.PWEY3 = 1;
		break;
	case E_DD_TOP_GPIO_PY4:
		IO_CHIPTOP.PDR.bit.PY4 = status;
		IO_CHIPTOP.PDR.bit.PWEY4 = 1;
		break;
	case E_DD_TOP_GPIO_PY5:
		IO_CHIPTOP.PDR.bit.PY5 = status;
		IO_CHIPTOP.PDR.bit.PWEY5 = 1;
		break;
	case E_DD_TOP_GPIO_PY6:
		IO_CHIPTOP.PDR.bit.PY6 = status;
		IO_CHIPTOP.PDR.bit.PWEY6 = 1;
		break;
	case E_DD_TOP_GPIO_PY7:
		IO_CHIPTOP.PDR.bit.PY7 = status;
		IO_CHIPTOP.PDR.bit.PWEY7 = 1;
		break;
	case E_DD_TOP_GPIO_PP0:
		IO_CHIPTOP.PDR.bit.PP0 = status;
		IO_CHIPTOP.PDR.bit.PWEP0 = 1;
		break;
	case E_DD_TOP_GPIO_PP1:
		IO_CHIPTOP.PDR.bit.PP1 = status;
		IO_CHIPTOP.PDR.bit.PWEP1 = 1;
		break;
	case E_DD_TOP_GPIO_PP2:
		IO_CHIPTOP.PDR.bit.PP2 = status;
		IO_CHIPTOP.PDR.bit.PWEP2 = 1;
		break;
	case E_DD_TOP_GPIO_PP3:
		IO_CHIPTOP.PDR.bit.PP3 = status;
		IO_CHIPTOP.PDR.bit.PWEP3 = 1;
		break;
	default:
		break;
		;
	}

	return D_DDIM_OK;
}
#endif

CtGpioCopy* ct_gpio_copy_new(void) 
{
    CtGpioCopy *self = k_object_new_with_private(CT_TYPE_GPIO_COPY, sizeof(CtGpioCopyPrivate));
    return self;
}
