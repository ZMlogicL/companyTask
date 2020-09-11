/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-05
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
#include "ctgetctrl.h"
#include "ctsetctrl.h"
#include "ctclockclksel.h"
#include "ctclockpllcnt.h"
#include "ctclockclkstop.h"
#include "ctpll.h"
#include "ctreset.h"
#include "ctgpio.h"
#include "ctclockfrequency.h"
#include "ctddtop.h"
#include "ctddtopfrist.h"
#include "ctddtopsecond.h"
#include "ctddtopthird.h"
#include "ctddtopend.h"

#include "ctddtopmain.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdTopMain, ct_dd_top_main);
#define CT_DD_TOP_MAIN_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdTopMainPrivate,CT_TYPE_DD_TOP_MAIN))

struct _CtDdTopMainPrivate
{
	kint a;
};
/*********
DECLS
*/
static void 		ct_dd_top_main_constructor(CtDdTopMain *self);
static void 		ct_dd_top_main_destructor(CtDdTopMain *self);
static void 		ctStartClock(kint argc, kchar **argv);
static void 		ctStopClock(kint argc, kchar **argv);
/****************
* IMPL
*/
static void ct_dd_top_main_constructor(CtDdTopMain *self) 
{
//	CtDdTopMainPrivate *priv = CT_DD_TOP_MAIN_GET_PRIVATE(self);
}

static void ct_dd_top_main_destructor(CtDdTopMain *self) 
{
//	CtDdTopMainPrivate *priv = CT_DD_TOP_MAIN_GET_PRIVATE(self);
}

static void ctStartClock(kint argc, kchar **argv)
{
	kulong val;
	kuchar count;

	if (argc == 6)
	{
		count = atoi(argv[4]);
		val = strtoul(argv[5], NULL, 0);

		if (val == 0)
		{
			Ddim_Print(("please check parameter!!\n"));
		}

		if (0 == strcmp(argv[3], "clkstop1"))
		{
			IO_CHIPTOP.CLKSTOP1.word |= (0x02 | val); // Clock Stop for Test
			dd_topthree_start_clock(&count, &DdToptwo_GET_CLKSTOP1(), ~val);
			Ddim_Print(("Clock Start. Count=%d, CLKSTOP1=0x%08lX\n", count, IO_CHIPTOP.CLKSTOP1.word));
		}else if ( 0 == strcmp(argv[3], "clkstop2"))
		{
			IO_CHIPTOP.CLKSTOP2.word |= (0x02 | val); // Clock Stop for Test
			dd_topthree_start_clock(&count, &DdToptwo_GET_CLKSTOP2(), ~val);
			Ddim_Print(("Clock Start. Count=%d, CLKSTOP2=0x%08lX\n", count, IO_CHIPTOP.CLKSTOP2.word));
		}else if ( 0 == strcmp(argv[3], "clkstop3"))
		{
			IO_CHIPTOP.CLKSTOP3.word |= (0x02 | val); // Clock Stop for Test
			dd_topthree_start_clock(&count, &DdToptwo_GET_CLKSTOP3(), ~val);
			Ddim_Print(("Clock Start. Count=%d, CLKSTOP3=0x%08lX\n", count, IO_CHIPTOP.CLKSTOP3.word));
		}else if ( 0 == strcmp(argv[3], "clkstop4"))
		{
			IO_CHIPTOP.CLKSTOP4.word |= (0x02 | val); // Clock Stop for Test
			dd_topthree_start_clock(&count, &DdToptwo_GET_CLKSTOP4(), ~val);
			Ddim_Print(("Clock Start. Count=%d, CLKSTOP4=0x%08lX\n", count, IO_CHIPTOP.CLKSTOP4.word));
		}else if ( 0 == strcmp(argv[3], "clkstop5"))
		{
			IO_CHIPTOP.CLKSTOP5.word |= (0x02 | val); // Clock Stop for Test
			dd_topthree_start_clock(&count, &DdToptwo_GET_CLKSTOP5(), ~val);
			Ddim_Print(("Clock Start. Count=%d, CLKSTOP5=0x%08lX\n", count, IO_CHIPTOP.CLKSTOP5.word));
		}else if ( 0 == strcmp(argv[3], "clkstop6"))
		{
			IO_CHIPTOP.CLKSTOP6.word |= (0x02 | val); // Clock Stop for Test
			dd_topthree_start_clock(&count, &DdToptwo_GET_CLKSTOP6(), ~val);
			Ddim_Print(("Clock Start. Count=%d, CLKSTOP6=0x%08lX\n", count, IO_CHIPTOP.CLKSTOP6.word));
		}else if ( 0 == strcmp(argv[3], "clkstop7"))
		{
			IO_CHIPTOP.CLKSTOP7.word |= (0x02 | val); // Clock Stop for Test
			dd_topthree_start_clock(&count, &DdToptwo_GET_CLKSTOP7(), ~val);
			Ddim_Print(("Clock Start. Count=%d, CLKSTOP7=0x%08lX\n", count, IO_CHIPTOP.CLKSTOP7.word));
		}else if ( 0 == strcmp(argv[3], "clkstop8"))
		{
			IO_CHIPTOP.CLKSTOP8.word |= (0x02 | val); // Clock Stop for Test
			dd_topthree_start_clock(&count, &DdToptwo_GET_CLKSTOP8(), ~val);
			Ddim_Print(("Clock Start. Count=%d, CLKSTOP8=0x%08lX\n", count, IO_CHIPTOP.CLKSTOP8.word));
		}else if ( 0 == strcmp(argv[3], "clkstop9"))
		{
			IO_CHIPTOP.CLKSTOP9.word |= (0x02 | val); // Clock Stop for Test
			dd_topthree_start_clock(&count, &DdToptwo_GET_CLKSTOP9(), ~val);
			Ddim_Print(("Clock Start. Count=%d, CLKSTOP9=0x%08lX\n", count, IO_CHIPTOP.CLKSTOP9.word));
		}else if ( 0 == strcmp(argv[3], "clkstop10"))
		{
			IO_CHIPTOP.CLKSTOP10.word |= (0x02 | val); // Clock Stop for Test
			dd_topthree_start_clock(&count, &DdToptwo_GET_CLKSTOP10(), ~val);
			Ddim_Print(("Clock Start. Count=%d, CLKSTOP10=0x%08lX\n", count, IO_CHIPTOP.CLKSTOP10.word));
		}else if ( 0 == strcmp(argv[3], "clkstop11"))
		{
			IO_CHIPTOP.CLKSTOP11.word |= (0x02 | val); // Clock Stop for Test
			dd_topthree_start_clock(&count, &DdToptwo_GET_CLKSTOP11(), ~val);
			Ddim_Print(("Clock Start. Count=%d, CLKSTOP11=0x%08lX\n", count, IO_CHIPTOP.CLKSTOP11.word));
		}else if ( 0 == strcmp(argv[3], "clkstop12"))
		{
			IO_CHIPTOP.CLKSTOP12.word |= (0x02 | val); // Clock Stop for Test
			dd_topthree_start_clock(&count, &DdToptwo_GET_CLKSTOP12(), ~val);
			Ddim_Print(("Clock Start. Count=%d, CLKSTOP12=0x%08lX\n", count, IO_CHIPTOP.CLKSTOP12.word));
		}else if ( 0 == strcmp(argv[3], "clkstop13"))
		{
			IO_CHIPTOP.CLKSTOP13.word |= (0x02 | val); // Clock Stop for Test
			dd_topthree_start_clock(&count, &DdToptwo_GET_CLKSTOP13(), ~val);
			Ddim_Print(("Clock Start. Count=%d, CLKSTOP13=0x%08lX\n", count, IO_CHIPTOP.CLKSTOP13.word));
		}else if ( 0 == strcmp(argv[3], "clkstop14"))
		{
			IO_CHIPTOP.CLKSTOP14.word |= (0x02 | val); // Clock Stop for Test
			dd_topthree_start_clock(&count, &DdToptwo_GET_CLKSTOP14(), ~val);
			Ddim_Print(("Clock Start. Count=%d, CLKSTOP14=0x%08lX\n", count, IO_CHIPTOP.CLKSTOP14.word));
		}
		else
		{
			Ddim_Print(("please check 3rd parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}

static void ctStopClock(kint argc, kchar **argv)
{
	kulong val;
	kuchar count;
	if (argc == 6)
	{
		count = atoi(argv[4]);
		val = strtoul(argv[5], NULL, 0);

		if (val == 0)
		{
			Ddim_Print(("please check parameter!!\n"));
		}

		if (0 == strcmp(argv[3], "clkstop1"))
		{
			IO_CHIPTOP.CLKSTOP1.word |= val; // Clock Start for Test
			dd_topthree_stop_clock(&count, &DdToptwo_GET_CLKSTOP1(), val);
			Ddim_Print(("Clock Stop. Count=%d, CLKSTOP1=0x%08lX\n", count, IO_CHIPTOP.CLKSTOP1.word));
		}else if ( 0 == strcmp(argv[3], "clkstop2"))
		{
			IO_CHIPTOP.CLKSTOP2.word |= val; // Clock Start for Test
			dd_topthree_stop_clock(&count, &DdToptwo_GET_CLKSTOP2(), val);
			Ddim_Print(("Clock Stop. Count=%d, CLKSTOP2=0x%08lX\n", count, IO_CHIPTOP.CLKSTOP2.word));
		}else if ( 0 == strcmp(argv[3], "clkstop3"))
		{
			IO_CHIPTOP.CLKSTOP3.word |= val; // Clock Start for Test
			dd_topthree_stop_clock(&count, &DdToptwo_GET_CLKSTOP3(), val);
			Ddim_Print(("Clock Stop. Count=%d, CLKSTOP3=0x%08lX\n", count, IO_CHIPTOP.CLKSTOP3.word));
		}else if ( 0 == strcmp(argv[3], "clkstop4"))
		{
			IO_CHIPTOP.CLKSTOP4.word |= val; // Clock Start for Test
			dd_topthree_stop_clock(&count, &DdToptwo_GET_CLKSTOP4(), val);
			Ddim_Print(("Clock Stop. Count=%d, CLKSTOP4=0x%08lX\n", count, IO_CHIPTOP.CLKSTOP4.word));
		}else if ( 0 == strcmp(argv[3], "clkstop5"))
		{
			IO_CHIPTOP.CLKSTOP5.word |= val; // Clock Start for Test
			dd_topthree_stop_clock(&count, &DdToptwo_GET_CLKSTOP5(), val);
			Ddim_Print(("Clock Stop. Count=%d, CLKSTOP5=0x%08lX\n", count, IO_CHIPTOP.CLKSTOP5.word));
		}else if ( 0 == strcmp(argv[3], "clkstop6"))
		{
			IO_CHIPTOP.CLKSTOP6.word |= val; // Clock Start for Test
			dd_topthree_stop_clock(&count, &DdToptwo_GET_CLKSTOP6(), val);
			Ddim_Print(("Clock Stop. Count=%d, CLKSTOP6=0x%08lX\n", count, IO_CHIPTOP.CLKSTOP6.word));
		}else if ( 0 == strcmp(argv[3], "clkstop7"))
		{
			IO_CHIPTOP.CLKSTOP7.word |= val; // Clock Start for Test
			dd_topthree_stop_clock(&count, &DdToptwo_GET_CLKSTOP7(), val);
			Ddim_Print(("Clock Stop. Count=%d, CLKSTOP7=0x%08lX\n", count, IO_CHIPTOP.CLKSTOP7.word));
		}else if ( 0 == strcmp(argv[3], "clkstop8"))
		{
			IO_CHIPTOP.CLKSTOP8.word |= val; // Clock Start for Test
			dd_topthree_stop_clock(&count, &DdToptwo_GET_CLKSTOP8(), val);
			Ddim_Print(("Clock Stop. Count=%d, CLKSTOP8=0x%08lX\n", count, IO_CHIPTOP.CLKSTOP8.word));
		}else if ( 0 == strcmp(argv[3], "clkstop9"))
		{
			IO_CHIPTOP.CLKSTOP9.word |= val; // Clock Start for Test
			dd_topthree_stop_clock(&count, &DdToptwo_GET_CLKSTOP9(), val);
			Ddim_Print(("Clock Stop. Count=%d, CLKSTOP9=0x%08lX\n", count, IO_CHIPTOP.CLKSTOP9.word));
		}else if ( 0 == strcmp(argv[3], "clkstop10"))
		{
			IO_CHIPTOP.CLKSTOP10.word |= val; // Clock Start for Test
			dd_topthree_stop_clock(&count, &DdToptwo_GET_CLKSTOP10(), val);
			Ddim_Print(("Clock Stop. Count=%d, CLKSTOP10=0x%08lX\n", count, IO_CHIPTOP.CLKSTOP10.word));
		}else if ( 0 == strcmp(argv[3], "clkstop11"))
		{
			IO_CHIPTOP.CLKSTOP11.word |= val; // Clock Start for Test
			dd_topthree_stop_clock(&count, &DdToptwo_GET_CLKSTOP11(), val);
			Ddim_Print(("Clock Stop. Count=%d, CLKSTOP11=0x%08lX\n", count, IO_CHIPTOP.CLKSTOP11.word));
		}else if ( 0 == strcmp(argv[3], "clkstop12"))
		{
			IO_CHIPTOP.CLKSTOP12.word |= val; // Clock Start for Test
			dd_topthree_stop_clock(&count, &DdToptwo_GET_CLKSTOP12(), val);
			Ddim_Print(("Clock Stop. Count=%d, CLKSTOP12=0x%08lX\n", count, IO_CHIPTOP.CLKSTOP12.word));
		}else if ( 0 == strcmp(argv[3], "clkstop13"))
		{
			IO_CHIPTOP.CLKSTOP13.word |= val; // Clock Start for Test
			dd_topthree_stop_clock(&count, &DdToptwo_GET_CLKSTOP13(), val);
			Ddim_Print(("Clock Stop. Count=%d, CLKSTOP13=0x%08lX\n", count, IO_CHIPTOP.CLKSTOP13.word));
		}else if ( 0 == strcmp(argv[3], "clkstop14"))
		{
			IO_CHIPTOP.CLKSTOP14.word |= val; // Clock Start for Test
			dd_topthree_stop_clock(&count, &DdToptwo_GET_CLKSTOP14(), val);
			Ddim_Print(("Clock Stop. Count=%d, CLKSTOP14=0x%08lX\n", count, IO_CHIPTOP.CLKSTOP14.word));
		}
		else
		{
			Ddim_Print(("please check 3rd parameter!!\n"));
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}
}
/****************
* PUBLIC
*/
void ct_dd_top_main(CtDdTopMain* self,kint argc, kchar **argv)
{
	if (0 == strcmp(argv[1], "lsi"))
	{
		if (0 == strcmp(argv[2], "get_ctrl"))
		{
			CtGetCtrl *ctGetCtrl = ct_get_ctrl_new();
			ct_get_ctrl_set_vaule(ctGetCtrl, argv[3]);
			ct_get_ctrl(ctGetCtrl);
		}else if ( 0 == strcmp(argv[2], "set_ctrl"))
		{
			CtSetCtrl *ctSetCtrl = ct_set_ctrl_new();
			ct_dd_parameter_set_parameter((CtDdParameter *)ctSetCtrl, argc, argv);
			ct_set_ctrl(ctSetCtrl);
		}
		else
		{
			Ddim_Print(("please check 2nd parameter!!\n"));
		}
	}
	else if (0 == strcmp(argv[1], "clock"))
	{
		if (0 == strcmp(argv[2], "start"))
		{
			ctStartClock(argc, argv);
		}else if ( 0 == strcmp(argv[2], "stop"))
		{
			ctStopClock(argc, argv);
		}else if ( 0 == strcmp(argv[2], "get_clock"))
		{
			CtClockFrequency*  ctClockFrequency = ct_clock_frequency_new();
			ct_dd_parameter_set_parameter((CtDdParameter *)ctClockFrequency,argc, argv);
			ct_clock_frequency_get_run(ctClockFrequency);
		}else if ( 0 == strcmp(argv[2], "get_reg"))
		{
			CtClockClksel *ctClockClksel = ct_clock_clksel_new();
			ct_dd_parameter_set_parameter((CtDdParameter *)ctClockClksel, argc, argv);
			ct_clock_clksel_get(ctClockClksel);
		}else if ( 0 == strcmp(argv[2], "set_reg"))
		{
			CtClockClksel *ctClockClksel = ct_clock_clksel_new();
			ct_dd_parameter_set_parameter((CtDdParameter *)ctClockClksel, argc, argv);
			ct_clock_clksel_set(ctClockClksel);
		}
		else
		{
			Ddim_Print(("please check 2nd parameter!!\n"));
		}
	}

	else if (0 == strcmp(argv[1], "pll"))
	{

		CtPll *ctPll = ct_pll_new();
		ct_dd_parameter_set_parameter((CtDdParameter *)ctPll, argc,argv);
		ct_pll_control(ctPll);
	}
	else if (0 == strcmp(argv[1], "reset"))
	{
		CtReset *ctReset = ct_reset_new();
		ct_dd_parameter_set_parameter((CtDdParameter *)ctReset, argc, argv);
		ct_reset_control(ctReset);
	}
	else if (0 == strcmp(argv[1], "gpio"))
	{
		CtGpio* ctGpio = ct_gpio_new();
		ct_dd_parameter_set_parameter((CtDdParameter *)ctGpio,argc,argv);
		ct_gpio_control(ctGpio);
	}else {
		Ddim_Print(("please check 1st parameter!!\n"));
	}
}

CtDdTopMain* ct_dd_top_main_new(void) 
{
    CtDdTopMain *self = k_object_new_with_private(CT_TYPE_DD_TOP_MAIN, sizeof(CtDdTopMainPrivate));
    return self;
}
