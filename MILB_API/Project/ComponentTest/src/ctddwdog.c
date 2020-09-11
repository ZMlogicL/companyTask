/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :李清
*@brief               :CtDdWdog类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年06月开始开发
*/
/**
 * @file		ct_dd_wdog.c
 * @brief		dd_wdog Component Test
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */

#include <stdlib.h>
#include <string.h>
#include "driver_common.h"
#include "ddgic.h"
#include "ddwdog.h"
#include "ctddwdog.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdWdog, ct_dd_wdog);
#define CT_DD_WDOG_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdWdogPrivate,CT_TYPE_DD_WDOG))

struct _CtDdWdogPrivate {
    kint i;
};

/*DECLS*/

static void testCallback(void);

static void ct_dd_wdog_constructor(CtDdWdog *self) 
{
// CtDdWdogPrivate *priv = CT_DD_WDOG_GET_PRIVATE(self);
}

static void ct_dd_wdog_destructor(CtDdWdog *self)
{
// CtDdWdogPrivate *priv = CT_DD_WDOG_GET_PRIVATE(self);
}

/*IMPL*/

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
//Nothing Special

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
//Nothing Special

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
//Nothing Special

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
//Nothing Special

/*----------------------------------------------------------------------*/
/* Local Method Definition												*/
/*----------------------------------------------------------------------*/
//Nothing Special

/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/
static void testCallback(void)
{
	kuchar	rawWdogInt;
	kuchar	wdogInt;
	DdWdog 	*dWdog = dd_wdog_new();
	
	Ddim_Print(("Watchdog Timer Interrupt\n"));
	dd_wdog_get_status(dWdog, &rawWdogInt, &wdogInt);
	Ddim_Print(("WDOGRIS.STATUS = 0x%08x\n", rawWdogInt));
	Ddim_Print(("WDOGMIS.STATUS = 0x%08x\n", wdogInt));

	k_object_unref(dWdog);
	dWdog = NULL;
}

/*PUBLIC*/

/*----------------------------------------------------------------------*/
/* Global Function														*/
/*----------------------------------------------------------------------*/
/**
 * @brief  Command main function for watchdog timer test.
 * @param  kint32 argc	:The number of parameters
 *		   kuchar** argv	:The value of parameters
 *
 *			The meaning of parameters
 *			+------+------------+-------------+---------------+----------------------------------------------------+
 *			| P1   | P2         | P3          | P4            |Meaning                                             |
 *			+------+------------+-------------+---------------+----------------------------------------------------+
 *			| 1    |            |             |               |Initialize Watchdog timer Register.                 |
 *			+------+------------+-------------+---------------+----------------------------------------------------+
 *			| 2    |            |             |               |Exclusively controll of Watchdog timer Open/Close.  |
 *			+------+------------+-------------+---------------+----------------------------------------------------+
 *			| 3    |wdogLoad    |resetEnable  |intEnable      |Watchdog timer Controller.                          |
 *			+------+------------+-------------+---------------+----------------------------------------------------+
 *			| 4    |wdogWdmode  |msec         |               |Watchdog timer Timer Set.                           |
 *			+------+------------+-------------+---------------+----------------------------------------------------+
 *			| 5    |            |             |               |Watchdog timer Get API.                             |
 *			+------+------------+-------------+---------------+----------------------------------------------------+
 *			| 6    |            |             |               |Watchdog timer Error Test.                          |
 *			+------+------------+-------------+---------------+----------------------------------------------------+
 *			| 7    |            |             |               |Watchdog timer Interrupt Handler                    |
 *			+------+------------+-------------+---------------+----------------------------------------------------+
 *			| 8    |            |             |               |Watchdog timer API Sequence1.                       |
 *			+------+------------+-------------+---------------+----------------------------------------------------+
 *			| 9    |            |             |               |Watchdog timer API Sequence2.                       |
 *			+------+------------+-------------+---------------+----------------------------------------------------+
 *
 * @return void
 */

void ct_dd_wdog_main(CtDdWdog *self, kint argc, KType* argv)
{
	DdWdog *dWdog = dd_wdog_new();

	switch (strtol(argv[1], NULL, 16)) {
		case 1:		// Init
			Ddim_Print(("dd_wdog_init Test Start\n"));
			dd_wdog_init(dWdog);
			
			// WDOGLOCK
			dd_wdog_get_lock(dWdog, &self->wdogLock);
			Ddim_Print(("WDOGLOCK = 0x%08x (set 0x00000001)\n", self->wdogLock));
			// WDOGITCR
			dd_wdog_get_test_mode(dWdog, &self->testMode);
			Ddim_Print(("WDOGITCR = 0x%08x (set 0x00000000)\n", self->testMode));
			// WDOGCONTROL
			dd_wdog_get_control(dWdog, &self->wdogCtrl);
			Ddim_Print(("WDOGCONTROL.RESEN = 0x%08x (set 0x00000000)\n", self->wdogCtrl.resetEnable));
			Ddim_Print(("WDOGCONTROL.INTEN = 0x%08x (set 0x00000000)\n", self->wdogCtrl.intEnable));
			
			Ddim_Print(("dd_wdog_init Test End\n"));
			break;
			
		case 2:		// Open/Close
			// DdimUserCustom_SEM_WAIT_POL
			Ddim_Print(("dd_wdog_open / dd_wdog_close POL Test Start\n"));
			self->ercd = dd_wdog_open(dWdog, DdimUserCustom_SEM_WAIT_POL);
			Ddim_Print(("dd_wdog_open return = 0x%08x\n", self->ercd));
			if(self->ercd == D_DDIM_OK){
				self->ercd = dd_wdog_close(dWdog);
				Ddim_Print(("dd_wdog_close return = 0x%08x\n", self->ercd));
			}
			Ddim_Print(("dd_wdog_open / dd_wdog_close POL Test End\n"));
			
			// Twai
			Ddim_Print(("dd_wdog_open / dd_wdog_close Twai Test Start\n"));
			self->ercd = dd_wdog_open(dWdog, 200);
			Ddim_Print(("dd_wdog_open return = 0x%08x\n", self->ercd));
			if(self->ercd == D_DDIM_OK){
				self->ercd = dd_wdog_close(dWdog);
				Ddim_Print(("dd_wdog_close return = 0x%08x\n", self->ercd));
			}
			Ddim_Print(("dd_wdog_open / dd_wdog_close Twai Test End\n"));
			
			break;
			
		case 3:		// Ctrl
			Ddim_Print(("dd_wdog_ctrl Test Start\n"));
			self->wdogCtrl.wdogLoad 	= strtoul(argv[2], NULL, 16);
			self->wdogCtrl.resetEnable 	= strtoul(argv[3], NULL, 16);
			self->wdogCtrl.intEnable 	= strtoul(argv[4], NULL, 16);
			self->wdogCtrl.pCallback 	= testCallback;
			
			if(self->wdogCtrl.wdogLoad <= 0){
				self->wdogCtrl.wdogLoad = 0;
			}
			if(self->wdogCtrl.resetEnable <= 0){
				self->wdogCtrl.resetEnable = 0;
			}
			if(self->wdogCtrl.intEnable <= 0){
				self->wdogCtrl.intEnable = 0;
			}
			if(dd_wdog_ctrl(dWdog, &self->wdogCtrl) == D_DDIM_OK){
				// WDOGLOAD
				dd_wdog_get_load(dWdog, &self->wdogLoad);
				Ddim_Print(("WDOGLOAD = 0x%08lx\n", self->wdogLoad));
				// WDOGVALUE
				dd_wdog_get_counter(dWdog, &self->wdogCounter);
				Ddim_Print(("WDOGVALUE = 0x%08lx\n", self->wdogCounter));
				// WDOGCONTROL
				dd_wdog_get_control(dWdog, &self->wdogCtrl);
				Ddim_Print(("WDOGCONTROL.RESEN = 0x%08x\n", self->wdogCtrl.resetEnable));
				Ddim_Print(("WDOGCONTROL.INTEN = 0x%08x\n", self->wdogCtrl.intEnable));
			}
			else{
				Ddim_Print(("please check parameter!!\n"));
			}
			
			Ddim_Print(("dd_wdog_ctrl Test End\n"));
			
			break;
			
		case 4:		// Timer Set
			Ddim_Print(("dd_wdog_set_timer Test Start\n"));
			self->wdogWdmode = strtoul(argv[2], NULL, 16);
			self->msec = strtoul(argv[3], NULL, 16);
			
			if(self->wdogWdmode <= 0){
				self->wdogWdmode = 0;
			}
			if(self->msec <= 0){
				self->msec = 0;
			}
			if(dd_wdog_set_timer(dWdog, self->wdogWdmode, self->msec) == D_DDIM_OK){
				// WDOGLOAD
				dd_wdog_get_load(dWdog, &self->wdogLoad);
				Ddim_Print(("WDOGLOAD = 0x%08lx\n", self->wdogLoad));
				// WDOGVALUE
				dd_wdog_get_counter(dWdog, &self->wdogCounter);
				Ddim_Print(("WDOGVALUE = 0x%08lx\n", self->wdogCounter));
			}
			
			Ddim_Print(("dd_wdog_set_timer Test End\n"));
			
			break;
			
		case 5:		// Get API
			// WDOGPERIPHID0~3
			dd_wdog_get_peri_identification(dWdog, &self->identification);
			Ddim_Print(("WDOGPERIPHID Get partNumber = 0x%08x\n", 
				self->identification.partNumber));
			Ddim_Print(("WDOGPERIPHID Get designer = 0x%08x\n", 
				self->identification.designer));
			Ddim_Print(("WDOGPERIPHID Get revisionNumber = 0x%08x\n", 
				self->identification.revisionNumber));
			Ddim_Print(("WDOGPERIPHID Get configuration = 0x%08x\n", 
				self->identification.configuration));
			// WDOGPCELLID0~3
			dd_wdog_get_pcell_identification(dWdog, &self->pcell);
			Ddim_Print(("WDOGPCELLID Get WDOGPCELLID[3:0] = 0x%08lx\n", self->pcell));
			
			break;
			
		case 6:		// Error Test
			Ddim_Print(("dd_wdog_open Error Test\n"));
			self->ercd = dd_wdog_open(dWdog, DdimUserCustom_SEM_WAIT_FEVR - 1);
			Ddim_Print(("dd_wdog_open Error = 0x%08x\n", self->ercd));
			self->ercd = dd_wdog_open(dWdog, DdimUserCustom_SEM_WAIT_POL);
			self->ercd = dd_wdog_open(dWdog, DdimUserCustom_SEM_WAIT_POL);
			Ddim_Print(("dd_wdog_open Error = 0x%08x\n", self->ercd));
			
			Ddim_Print(("dd_wdog_close Error Test\n"));
			self->ercd = dd_wdog_close(dWdog);
			Ddim_Print(("dd_wdog_close Error = 0x%08x\n", self->ercd));
			
			Ddim_Print(("dd_wdog_ctrl Error Test\n"));
			self->ercd = dd_wdog_ctrl(dWdog, NULL);
			Ddim_Print(("dd_wdog_ctrl Error = 0x%08x\n", self->ercd));
			self->wdogCtrl.wdogLoad = 0;
			self->wdogCtrl.resetEnable = DdWdog_D_DD_WDOG_ENABLE_ON;
			self->wdogCtrl.intEnable = DdWdog_D_DD_WDOG_ENABLE_OFF;
			self->ercd = dd_wdog_ctrl(dWdog, &self->wdogCtrl);
			Ddim_Print(("dd_wdog_ctrl Error = 0x%08x\n", self->ercd));
			self->wdogCtrl.wdogLoad = 0xFFFFFFFF;
			self->wdogCtrl.resetEnable = DdWdog_D_DD_WDOG_ENABLE_ON + 1;
			self->wdogCtrl.intEnable = DdWdog_D_DD_WDOG_ENABLE_ON;
			self->ercd = dd_wdog_ctrl(dWdog, &self->wdogCtrl);
			Ddim_Print(("dd_wdog_ctrl Error = 0x%08x\n", self->ercd));
			self->wdogCtrl.wdogLoad = 0xFFFFFFFF;
			self->wdogCtrl.resetEnable = DdWdog_D_DD_WDOG_ENABLE_OFF;
			self->wdogCtrl.intEnable = DdWdog_D_DD_WDOG_ENABLE_ON + 1;
			self->ercd = dd_wdog_ctrl(dWdog, &self->wdogCtrl);
			Ddim_Print(("dd_wdog_ctrl Error = 0x%08x\n", self->ercd));
			
			Ddim_Print(("dd_wdog_get_load Error Test\n"));
			self->ercd = dd_wdog_get_load(dWdog, NULL);
			Ddim_Print(("dd_wdog_get_load Error = 0x%08x\n", self->ercd));
			
			Ddim_Print(("dd_wdog_get_counter Error Test\n"));
			self->ercd = dd_wdog_get_counter(dWdog, NULL);
			Ddim_Print(("dd_wdog_get_counter Error = 0x%08x\n", self->ercd));
			
			Ddim_Print(("dd_wdog_get_control Error Test\n"));
			self->ercd = dd_wdog_get_control(dWdog, NULL);
			Ddim_Print(("dd_wdog_get_control Error = 0x%08x\n", self->ercd));
			
			Ddim_Print(("dd_wdog_get_status Error Test\n"));
			self->ercd = dd_wdog_get_status(dWdog, NULL, &self->wdogInt);
			Ddim_Print(("dd_wdog_get_status Error = 0x%08x\n", self->ercd));
			self->ercd = dd_wdog_get_status(dWdog, &self->rawWdogInt, NULL);
			Ddim_Print(("dd_wdog_get_status Error = 0x%08x\n", self->ercd));
			self->ercd = dd_wdog_get_status(dWdog, NULL, NULL);
			Ddim_Print(("dd_wdog_get_status Error = 0x%08x\n", self->ercd));
			
			Ddim_Print(("dd_wdog_get_lock Error Test\n"));
			self->ercd = dd_wdog_get_lock(dWdog, NULL);
			Ddim_Print(("dd_wdog_get_lock Error = 0x%08x\n", self->ercd));
			
			Ddim_Print(("dd_wdog_get_test_mode Error Test\n"));
			self->ercd = dd_wdog_get_test_mode(dWdog, NULL);
			Ddim_Print(("dd_wdog_get_test_mode Error = 0x%08x\n", self->ercd));
			
			Ddim_Print(("dd_wdog_get_peri_identification Error Test\n"));
			self->ercd = dd_wdog_get_peri_identification(dWdog, NULL);
			Ddim_Print(("dd_wdog_get_peri_identification Error = 0x%08x\n", self->ercd));
			
			Ddim_Print(("dd_wdog_get_pcell_identification Error Test\n"));
			self->ercd = dd_wdog_get_pcell_identification(dWdog, NULL);
			Ddim_Print(("dd_wdog_get_pcell_identification Error = 0x%08x\n", self->ercd));
			
			Ddim_Print(("dd_wdog_set_load Error Test\n"));
			self->ercd = dd_wdog_set_load(dWdog, 0);
			Ddim_Print(("dd_wdog_set_load Error = 0x%08x\n", self->ercd));
			
			Ddim_Print(("dd_wdog_set_control Error Test\n"));
			self->ercd = dd_wdog_set_control(dWdog, NULL);
			Ddim_Print(("dd_wdog_set_control Error = 0x%08x\n", self->ercd));
			self->wdogCtrl.resetEnable = DdWdog_D_DD_WDOG_ENABLE_ON + 1;
			self->wdogCtrl.intEnable = DdWdog_D_DD_WDOG_ENABLE_ON;
			self->ercd = dd_wdog_set_control(dWdog, &self->wdogCtrl);
			Ddim_Print(("dd_wdog_set_control Error = 0x%08x\n", self->ercd));
			self->wdogCtrl.resetEnable = DdWdog_D_DD_WDOG_ENABLE_OFF;
			self->wdogCtrl.intEnable = DdWdog_D_DD_WDOG_ENABLE_ON + 1;
			self->ercd = dd_wdog_set_control(dWdog, &self->wdogCtrl);
			Ddim_Print(("dd_wdog_set_control Error = 0x%08x\n", self->ercd));
			
			Ddim_Print(("dd_wdog_set_lock Error Test\n"));
			self->ercd = dd_wdog_set_lock(dWdog, DdWdog_D_DD_WDOG_ENABLE_ON + 1);
			Ddim_Print(("dd_wdog_set_lock Error = 0x%08x\n", self->ercd));
			
			Ddim_Print(("dd_wdog_set_test_mode Error Test\n"));
			self->ercd = dd_wdog_set_test_mode(dWdog, DdWdog_D_DD_WDOG_ENABLE_ON + 1, 
				DdWdog_D_DD_WDOG_ENABLE_ON, DdWdog_D_DD_WDOG_ENABLE_OFF);
			Ddim_Print(("dd_wdog_set_test_mode Error = 0x%08x\n", self->ercd));
			self->ercd = dd_wdog_set_test_mode(dWdog, DdWdog_D_DD_WDOG_ENABLE_OFF, 
				DdWdog_D_DD_WDOG_ENABLE_ON + 1, DdWdog_D_DD_WDOG_ENABLE_ON);
			Ddim_Print(("dd_wdog_set_test_mode Error = 0x%08x\n", self->ercd));
			self->ercd = dd_wdog_set_test_mode(dWdog, DdWdog_D_DD_WDOG_ENABLE_ON, 
				DdWdog_D_DD_WDOG_ENABLE_OFF, DdWdog_D_DD_WDOG_ENABLE_ON + 1);
			Ddim_Print(("dd_wdog_set_test_mode Error = 0x%08x\n", self->ercd));
			
			Ddim_Print(("dd_wdog_set_timer Error Test\n"));
			self->ercd = dd_wdog_set_timer(dWdog, 2, 1000);
			Ddim_Print(("dd_wdog_set_timer Error = 0x%08x\n", self->ercd));
			self->ercd = dd_wdog_set_timer(dWdog, 1, 0);
			Ddim_Print(("dd_wdog_set_timer Error = 0x%08x\n", self->ercd));
			
			Ddim_Print(("dd_wdog_calculate Error Test\n"));
			self->ercd = dd_wdog_calculate(dWdog, 1, 1000, NULL);
			Ddim_Print(("dd_wdog_calculate Error = 0x%08x\n", self->ercd));
			
			break;
			
		case 7:		// Int_Handler
			Ddim_Print(("dd_wdog_int_handler Test Start\n"));
			dd_wdog_set_timer(dWdog, 0, 1000);  // (PCLK = 50MHz) -> (gDD_Wdog_Soft_Counter = 0)
			dd_wdog_int_handler(dWdog);
			// WDOGLOAD
			dd_wdog_get_load(dWdog, &self->wdogLoad);
			Ddim_Print(("WDOGLOAD = 0x%08lx\n", self->wdogLoad));
			
			dd_wdog_set_timer(dWdog, 0, 300000);  // (PCLK = 50MHz) -> (gDD_Wdog_Soft_Counter = 3)
			dd_wdog_int_handler(dWdog);
			// WDOGLOAD
			dd_wdog_get_load(dWdog, &self->wdogLoad);
			Ddim_Print(("WDOGLOAD = 0x%08lx\n", self->wdogLoad));
			
			dd_wdog_int_handler(dWdog);
			// WDOGLOAD
			dd_wdog_get_load(dWdog, &self->wdogLoad);
			Ddim_Print(("WDOGLOAD = 0x%08lx\n", self->wdogLoad));
			
			dd_wdog_int_handler(dWdog);
			// WDOGLOAD
			dd_wdog_get_load(dWdog, &self->wdogLoad);
			Ddim_Print(("WDOGLOAD = 0x%08lx\n", self->wdogLoad));
			
			dd_wdog_int_handler(dWdog);
			// WDOGLOAD
			dd_wdog_get_load(dWdog, &self->wdogLoad);
			Ddim_Print(("WDOGLOAD = 0x%08lx\n", self->wdogLoad));
			Ddim_Print(("dd_wdog_int_handler Test End\n"));
			
			break;
			
		case 8:		// Sequence1
			Ddim_Print(("Sequence1 Test Start\n"));
			
			self->wdogCtrl.wdogLoad 	= 1000000000;
			self->wdogCtrl.resetEnable 	= DdWdog_D_DD_WDOG_ENABLE_OFF;
			self->wdogCtrl.intEnable 	= DdWdog_D_DD_WDOG_ENABLE_ON;
			self->wdogCtrl.pCallback 	= testCallback;
			
			dd_wdog_init(dWdog);
			dd_wdog_open(dWdog, DdimUserCustom_SEM_WAIT_POL);
			dd_wdog_ctrl(dWdog, &self->wdogCtrl);
			
			dd_wdog_close(dWdog);
			
			Ddim_Print(("Sequence1 Test End\n"));
			
			break;
			
		case 9:		// Sequence2
			Ddim_Print(("Sequence2 Test Start\n"));
			
			self->wdogCtrl.wdogLoad 	= 1000000;
			self->wdogCtrl.resetEnable 	= DdWdog_D_DD_WDOG_ENABLE_ON;
			self->wdogCtrl.intEnable 	= DdWdog_D_DD_WDOG_ENABLE_OFF;
			self->wdogCtrl.pCallback 	= NULL;
			
			dd_wdog_init(dWdog);
			dd_wdog_open(dWdog, DdimUserCustom_SEM_WAIT_POL);
			dd_wdog_ctrl(dWdog, &self->wdogCtrl);
			
			dd_wdog_get_status(dWdog, &self->rawWdogInt, &self->wdogInt);
			Ddim_Print(("WDOGRIS.STATUS = 0x%08x\n", self->rawWdogInt));
			Ddim_Print(("WDOGMIS.STATUS = 0x%08x\n", self->wdogInt));
			
			dd_wdog_close(dWdog);
			
			Ddim_Print(("Sequence2 Test End\n"));
			
			break;
			
		default :
			Ddim_Print(("please check 1st parameter!!\n"));
	}
	k_object_unref(dWdog);
	dWdog = NULL;
}

CtDdWdog *ct_dd_wdog_new(void)
{
    CtDdWdog *self = k_object_new_with_private(CT_TYPE_DD_WDOG, sizeof(CtDdWdogPrivate));
    return self;
}
