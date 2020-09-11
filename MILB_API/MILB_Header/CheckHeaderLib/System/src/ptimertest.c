/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :于孟孟
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年06月开始开发
*/
#include <stdio.h>
#include <stdlib.h>
#include "CheckHeaderMain.h"
#include "milb.h"
#include "chiptop.h"
#if 0
#include "arm.h"
#include "chiptop.h"
#include "exstop.h"
#include "jdsb2r.h"
#include "jdscnr.h"
#include "jdsdisp.h"
#include "jdsela.h"
#include "jdsfpt.h"
#include "jdsiip.h"
#include "jdsimg.h"
#include "jdsjpgdec.h"
#include "jdsjpgenc.h"
#include "jdsltm.h"
#include "jdsmxic.h"
#include "jdspro.h"
#include "jdsr2y.h"
#include "jdsraw.h"
#include "jdsshdr.h"
#include "jdsxch.h"
#include "jmilaum.h"
#include "jmilhdmi.h"
#include "jmlbmh.h"
#include "jsrlot.h"
#include "peripheral.h"
#include "slimbus.h"
#include "sdramc.h"
#include "uart_csio.h"
#include "jdsme.h"
#endif
#include "ptimertest.h"


K_TYPE_DEFINE_WITH_PRIVATE(PtimerTest, ptimer_test)
#define PTIMER_TEST_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), PtimerTestPrivate, PTIMER_TYPE_TEST))


struct _PtimerTestPrivate
{
	int a;
};


/*DECLS*/


/*IMPL*/
static void ptimer_test_constructor(PtimerTest *self)
{
	PtimerTestPrivate *priv = PTIMER_TEST_GET_PRIVATE(self);
}

static void ptimer_test_destructor(PtimerTest *self)
{
	PtimerTestPrivate *priv = PTIMER_TEST_GET_PRIVATE(self);
}


/*PUBLIC*/
void ptimer_test(PtimerTest *self)
{
	RS_printf("Prevate Timer\n");

#if 0

#if 0	// for PC debug
#define PtimerTest_IO_TIMER					(*ioTimer2)
volatile struct io_timer*		ioTimer2		= (void*)0xF8100600;	//！！struct io_timer找不到定义
#endif

	RS_printf("IO_TIMER.TIMER_LOAD       = 0x%lX\n", (unsigned long)&PtimerTest_IO_TIMER.TIMER_LOAD);
	RS_printf("IO_TIMER.TIMER_COUNTER    = 0x%lX\n", (unsigned long)&PtimerTest_IO_TIMER.TIMER_COUNTER);
	RS_printf("IO_TIMER.TIMER_CONTROL    = 0x%lX\n", (unsigned long)&PtimerTest_IO_TIMER.TIMER_CONTROL);
	RS_printf("IO_TIMER.TIMER_INTERRUPT  = 0x%lX\n", (unsigned long)&PtimerTest_IO_TIMER.TIMER_INTERRUPT);

#endif

	RS_printf(" \n");
}

PtimerTest* ptimer_test_new(void)
{
	PtimerTest* self = k_object_new_with_private(PTIMER_TYPE_TEST, sizeof(PtimerTestPrivate));

	return self;
}

