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
#include "scutest.h"


K_TYPE_DEFINE_WITH_PRIVATE(ScuTest, scu_test)
#define SCU_TEST_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), ScuTestPrivate, SCU_TYPE_TEST))


struct _ScuTestPrivate
{
	int a;
};


static void scu_test_constructor(ScuTest *self)
{
	ScuTestPrivate *priv = SCU_TEST_GET_PRIVATE(self);
}

static void scu_test_destructor(ScuTest *self)
{
	ScuTestPrivate *priv = SCU_TEST_GET_PRIVATE(self);
}

void scu_test(ScuTest *self)
{
#if 0	// for PC debug
#define ScuTest_IO_SCU		(*ioScu2)
	volatile struct io_scu*		ioScu2		= (void*)0xF8100000;
#endif
	RS_printf("SCU\n");
#if 0
	RS_printf("IO_SCU\n");
	RS_printf("IO_SCU.control                 = %p\n", &ScuTest_IO_SCU.control );
	RS_printf("IO_SCU.configuration           = %p\n", &ScuTest_IO_SCU.configuration );
	RS_printf("IO_SCU.power_status            = %p\n", &ScuTest_IO_SCU.power_status );
	RS_printf("IO_SCU.invalidate_all          = %p\n", &ScuTest_IO_SCU.invalidate_all );
	RS_printf("Reserved                       = %p\n", &ScuTest_IO_SCU.dmy_10_3F );
	RS_printf("IO_SCU.filtering_start_address = %p\n", &ScuTest_IO_SCU.filtering_start_address );
	RS_printf("IO_SCU.filtering_end_address   = %p\n", &ScuTest_IO_SCU.filtering_end_address );
	RS_printf("Reserved                       = %p\n", &ScuTest_IO_SCU.dmy_48_4F );
	RS_printf("IO_SCU.sac                     = %p\n", &ScuTest_IO_SCU.sac );
	RS_printf("IO_SCU.ssac                    = %p\n", &ScuTest_IO_SCU.ssac );
	RS_printf(" \n");
#endif
}

ScuTest* scu_test_new(void)
{
	ScuTest* self = k_object_new_with_private(SCU_TYPE_TEST, sizeof(ScuTestPrivate));

	return self;
}
