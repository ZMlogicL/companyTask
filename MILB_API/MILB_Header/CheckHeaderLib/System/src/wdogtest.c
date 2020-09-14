/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020年9月3日
*@author              :申雨
*@brief               :
*@rely                :glib
*@function
*设计的主要功能:
*1、
*@version
*
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
#include "wdogtest.h"


G_DEFINE_TYPE(WdogTest, wdog_test, G_TYPE_OBJECT);

#define WDOG_TEST_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o), WDOG_TYPE_TEST, WdogTestPrivate));


struct _WdogTestPrivate
{
	 gint preserved;
};
/**
 * DECLS
 */
static void 	dispose_od(GObject *object);
static void 	finalize_od(GObject *object);
static void 	run_od(AbsHeaderTest *self);
/**
 * IMPL
 */
static void wdog_test_class_init(WdogTestClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);

	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(WdogTestPrivate));
	AbsHeaderTestClass *absClass =  ABS_HEADER_TEST_CALSS(klass);

	absClass->run = run_od;
}

static void wdog_test_init(WdogTest *self)
{
	WdogTestPrivate *priv = WDOG_TEST_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(wdog_test_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	WdogTest *self = WDOG_TEST(object);
	WdogTestPrivate *priv = WDOG_TEST_GET_PRIVATE(self);

	G_OBJECT_CLASS(wdog_test_parent_class)->finalize(object);
}

static void run_od(AbsHeaderTest *self)
{

}
/**
 * PUBLIC
 */
void wdog_test()
{
	CheckHeaderMain_RS_PRINTF("Watchdog Timer\n");
#if 0
	CheckHeaderMain_RS_PRINTF("ioWdog                   = %p\n", &ioWdog );
	CheckHeaderMain_RS_PRINTF("ioWdog.wdogload          = %p\n", &ioWdog.wdogload );
	CheckHeaderMain_RS_PRINTF("ioWdog.wdogvalue         = %p\n", &ioWdog.wdogvalue );
	CheckHeaderMain_RS_PRINTF("ioWdog.wdogcontrol       = %p\n", &ioWdog.wdogcontrol );
	CheckHeaderMain_RS_PRINTF("ioWdog.wdogintclr        = %p\n", &ioWdog.wdogintclr );
	CheckHeaderMain_RS_PRINTF("ioWdog.wdogris           = %p\n", &ioWdog.wdogris );
	CheckHeaderMain_RS_PRINTF("ioWdog.wdogmis           = %p\n", &ioWdog.wdogmis );
	CheckHeaderMain_RS_PRINTF("Reserved                  = %p\n", &ioWdog.dmy018Bff );
	CheckHeaderMain_RS_PRINTF("ioWdog.wdoglock          = %p\n", &ioWdog.wdoglock );
	CheckHeaderMain_RS_PRINTF("Reserved                  = %p\n", &ioWdog.dmyC04Eff );
	CheckHeaderMain_RS_PRINTF("ioWdog.wdogitcr          = %p\n", &ioWdog.wdogitcr );
	CheckHeaderMain_RS_PRINTF("ioWdog.wdogitop          = %p\n", &ioWdog.wdogitop );
	CheckHeaderMain_RS_PRINTF("Reserved                  = %p\n", &ioWdog.dmyF08Fdf );
	CheckHeaderMain_RS_PRINTF("ioWdog.wdogperiphid0     = %p\n", &ioWdog.wdogperiphid0 );
	CheckHeaderMain_RS_PRINTF("ioWdog.wdogperiphid1     = %p\n", &ioWdog.wdogperiphid1 );
	CheckHeaderMain_RS_PRINTF("ioWdog.wdogperiphid2     = %p\n", &ioWdog.wdogperiphid2 );
	CheckHeaderMain_RS_PRINTF("ioWdog.wdogperiphid3     = %p\n", &ioWdog.wdogperiphid3 );
	CheckHeaderMain_RS_PRINTF("ioWdog.wdogpcellid[0]    = %p\n", &ioWdog.wdogpcellid[0] );
	CheckHeaderMain_RS_PRINTF("ioWdog.wdogpcellid[1]    = %p\n", &ioWdog.wdogpcellid[1] );
	CheckHeaderMain_RS_PRINTF("ioWdog.wdogpcellid[2]    = %p\n", &ioWdog.wdogpcellid[2] );
	CheckHeaderMain_RS_PRINTF("ioWdog.wdogpcellid[3]    = %p\n", &ioWdog.wdogpcellid[3] );
#endif

	CheckHeaderMain_RS_PRINTF(" \n");
}

WdogTest *wdog_test_new()
{
	WdogTest *self = g_object_new(WDOG_TYPE_TEST, NULL);

	return self;
}
