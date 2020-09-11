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
#include "xdmactest.h"


G_DEFINE_TYPE(XdmacTest, xdmac_test, G_TYPE_OBJECT);

#define XDMAC_TEST_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o), XDMAC_TYPE_TEST, XdmacTestPrivate));


struct _XdmacTestPrivate
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
static void xdmac_test_class_init(XdmacTestClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);

	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(XdmacTestPrivate));
	AbsHeaderTestClass *absClass =  ABS_HEADER_TEST_CALSS(klass);

	absClass->run = run_od;
}

static void xdmac_test_init(XdmacTest *self)
{
	XdmacTestPrivate *priv = XDMAC_TEST_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(xdmac_test_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	XdmacTest *self = XDMAC_TEST(object);
	XdmacTestPrivate *priv = XDMAC_TEST_GET_PRIVATE(self);

	G_OBJECT_CLASS(xdmac_test_parent_class)->finalize(object);
}

static void run_od(AbsHeaderTest *self)
{

}
/**
 * PUBLIC
 */
void xdmac_test()
{
	IntErnals_RS_printf("Xdmac\n");
#if 0
#if 0	// for PC debug
#define XdmacTest_IO_XDMAC	(*ioXdmac2)
	volatile IoXdmac*		ioXdmac2		= (gpointer)0x19140000;
#define XdmacTest_IO_XDMACS	(*ioXdmacs2)
	volatile IoXdmac*		ioXdmacs2		= (gpointer)0x1C250000;
#endif

	IntErnals_RS_printf("XdmacTest_IO_XDMAC.xdacs            = 0x%lX\n", (gulong)&XdmacTest_IO_XDMAC.xdacs );
	IntErnals_RS_printf("XdmacTest_IO_XDMAC.ch[0].xdtbc      = 0x%lX\n", (gulong)&XdmacTest_IO_XDMAC.ch[0].xdtbc );
	IntErnals_RS_printf("XdmacTest_IO_XDMAC.ch[0].xdssa      = 0x%lX\n", (gulong)&XdmacTest_IO_XDMAC.ch[0].xdssa );
	IntErnals_RS_printf("XdmacTest_IO_XDMAC.ch[0].xddsa      = 0x%lX\n", (gulong)&XdmacTest_IO_XDMAC.ch[0].xddsa );
	IntErnals_RS_printf("XdmacTest_IO_XDMAC.ch[0].xdsac      = 0x%lX\n", (gulong)&XdmacTest_IO_XDMAC.ch[0].xdsac );
	IntErnals_RS_printf("XdmacTest_IO_XDMAC.ch[0].xddac      = 0x%lX\n", (gulong)&XdmacTest_IO_XDMAC.ch[0].xddac );
	IntErnals_RS_printf("XdmacTest_IO_XDMAC.ch[0].xddcc      = 0x%lX\n", (gulong)&XdmacTest_IO_XDMAC.ch[0].xddcc );
	IntErnals_RS_printf("XdmacTest_IO_XDMAC.ch[0].xddes      = 0x%lX\n", (gulong)&XdmacTest_IO_XDMAC.ch[0].xddes );
	IntErnals_RS_printf("XdmacTest_IO_XDMAC.ch[0].xddpc      = 0x%lX\n", (gulong)&XdmacTest_IO_XDMAC.ch[0].xddpc );
	IntErnals_RS_printf("XdmacTest_IO_XDMAC.ch[0].xddsd      = 0x%lX\n", (gulong)&XdmacTest_IO_XDMAC.ch[0].xddsd );
	IntErnals_RS_printf("XdmacTest_IO_XDMAC.ch[7].xdtbc      = 0x%lX\n", (gulong)&XdmacTest_IO_XDMAC.ch[7].xdtbc );
	IntErnals_RS_printf("XdmacTest_IO_XDMAC.ch[7].xdssa      = 0x%lX\n", (gulong)&XdmacTest_IO_XDMAC.ch[7].xdssa );
	IntErnals_RS_printf("XdmacTest_IO_XDMAC.ch[7].xddsa      = 0x%lX\n", (gulong)&XdmacTest_IO_XDMAC.ch[7].xddsa );
	IntErnals_RS_printf("XdmacTest_IO_XDMAC.ch[7].xdsac      = 0x%lX\n", (gulong)&XdmacTest_IO_XDMAC.ch[7].xdsac );
	IntErnals_RS_printf("XdmacTest_IO_XDMAC.ch[7].xddac      = 0x%lX\n", (gulong)&XdmacTest_IO_XDMAC.ch[7].xddac );
	IntErnals_RS_printf("XdmacTest_IO_XDMAC.ch[7].xddcc      = 0x%lX\n", (gulong)&XdmacTest_IO_XDMAC.ch[7].xddcc );
	IntErnals_RS_printf("XdmacTest_IO_XDMAC.ch[7].xddes      = 0x%lX\n", (gulong)&XdmacTest_IO_XDMAC.ch[7].xddes );
	IntErnals_RS_printf("XdmacTest_IO_XDMAC.ch[7].xddpc      = 0x%lX\n", (gulong)&XdmacTest_IO_XDMAC.ch[7].xddpc );
	IntErnals_RS_printf("XdmacTest_IO_XDMAC.ch[7].xddsd      = 0x%lX\n", (gulong)&XdmacTest_IO_XDMAC.ch[7].xddsd );
	IntErnals_RS_printf("XdmacTest_IO_XDMACS.xdacs           = 0x%lX\n", (gulong)&XdmacTest_IO_XDMACS.xdacs );
	IntErnals_RS_printf("XdmacTest_IO_XDMACS.ch[0].xdtbc     = 0x%lX\n", (gulong)&XdmacTest_IO_XDMACS.ch[0].xdtbc );
	IntErnals_RS_printf("XdmacTest_IO_XDMACS.ch[0].xdssa     = 0x%lX\n", (gulong)&XdmacTest_IO_XDMACS.ch[0].xdssa );
	IntErnals_RS_printf("XdmacTest_IO_XDMACS.ch[0].xddsa     = 0x%lX\n", (gulong)&XdmacTest_IO_XDMACS.ch[0].xddsa );
	IntErnals_RS_printf("XdmacTest_IO_XDMACS.ch[0].xdsac     = 0x%lX\n", (gulong)&XdmacTest_IO_XDMACS.ch[0].xdsac );
	IntErnals_RS_printf("XdmacTest_IO_XDMACS.ch[0].xddac     = 0x%lX\n", (gulong)&XdmacTest_IO_XDMACS.ch[0].xddac );
	IntErnals_RS_printf("XdmacTest_IO_XDMACS.ch[0].xddcc     = 0x%lX\n", (gulong)&XdmacTest_IO_XDMACS.ch[0].xddcc );
	IntErnals_RS_printf("XdmacTest_IO_XDMACS.ch[0].xddes     = 0x%lX\n", (gulong)&XdmacTest_IO_XDMACS.ch[0].xddes );
	IntErnals_RS_printf("XdmacTest_IO_XDMACS.ch[0].xddpc     = 0x%lX\n", (gulong)&XdmacTest_IO_XDMACS.ch[0].xddpc );
	IntErnals_RS_printf("XdmacTest_IO_XDMACS.ch[0].xddsd     = 0x%lX\n", (gulong)&XdmacTest_IO_XDMACS.ch[0].xddsd );
	IntErnals_RS_printf("XdmacTest_IO_XDMACS.ch[7].xdtbc     = 0x%lX\n", (gulong)&XdmacTest_IO_XDMACS.ch[7].xdtbc );
	IntErnals_RS_printf("XdmacTest_IO_XDMACS.ch[7].xdssa     = 0x%lX\n", (gulong)&XdmacTest_IO_XDMACS.ch[7].xdssa );
	IntErnals_RS_printf("XdmacTest_IO_XDMACS.ch[7].xddsa     = 0x%lX\n", (gulong)&XdmacTest_IO_XDMACS.ch[7].xddsa );
	IntErnals_RS_printf("XdmacTest_IO_XDMACS.ch[7].xdsac     = 0x%lX\n", (gulong)&XdmacTest_IO_XDMACS.ch[7].xdsac );
	IntErnals_RS_printf("XdmacTest_IO_XDMACS.ch[7].xddac     = 0x%lX\n", (gulong)&XdmacTest_IO_XDMACS.ch[7].xddac );
	IntErnals_RS_printf("XdmacTest_IO_XDMACS.ch[7].xddcc     = 0x%lX\n", (gulong)&XdmacTest_IO_XDMACS.ch[7].xddcc );
	IntErnals_RS_printf("XdmacTest_IO_XDMACS.ch[7].xddes     = 0x%lX\n", (gulong)&XdmacTest_IO_XDMACS.ch[7].xddes );
	IntErnals_RS_printf("XdmacTest_IO_XDMACS.ch[7].xddpc     = 0x%lX\n", (gulong)&XdmacTest_IO_XDMACS.ch[7].xddpc );
	IntErnals_RS_printf("XdmacTest_IO_XDMACS.ch[7].xddsd     = 0x%lX\n", (gulong)&XdmacTest_IO_XDMACS.ch[7].xddsd );
#endif

	IntErnals_RS_printf(" \n");
}

XdmacTest *xdmac_test_new()
{
	XdmacTest *self = g_object_new(XDMAC_TYPE_TEST, NULL);

	return self;
}
