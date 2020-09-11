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
#include "spitest.h"


G_DEFINE_TYPE(SpiTest, spi_test, G_TYPE_OBJECT);

#define SPI_TEST_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o), SPI_TYPE_TEST, SpiTestPrivate));


struct _SpiTestPrivate
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
static void spi_test_class_init(SpiTestClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);

	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(SpiTestPrivate));
	AbsHeaderTestClass *absClass =  ABS_HEADER_TEST_CALSS(klass);

	absClass->run = run_od;
}

static void spi_test_init(SpiTest *self)
{
	SpiTestPrivate *priv = SPI_TEST_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(spi_test_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	SpiTest *self = SPI_TEST(object);
	SpiTestPrivate *priv = SPI_TEST_GET_PRIVATE(self);

	G_OBJECT_CLASS(spi_test_parent_class)->finalize(object);
}

static void run_od(AbsHeaderTest *self)
{

}
/**
 * PUBLIC
 */
void spi_test()
{
#if 0
	volatile IoSpi*	ioSpi;
	ioSpi = (gpointer)0x1E800000;
#endif

	IntErnals_RS_printf("SPI\n");
#if 0
	int loop;

	for (loop = 0; loop < 3; loop++) {
		IntErnals_RS_printf("ioSpi[%d].txdata       = %lx\n", loop, (gulong)&ioSpi[loop].txdata );
		IntErnals_RS_printf("ioSpi[%d].rxdata       = %lx\n", loop, (gulong)&ioSpi[loop].rxdata );
		IntErnals_RS_printf("ioSpi[%d].div          = %lx\n", loop, (gulong)&ioSpi[loop].div );
		IntErnals_RS_printf("ioSpi[%d].ctrl         = %lx\n", loop, (gulong)&ioSpi[loop].ctrl );
		IntErnals_RS_printf("ioSpi[%d].aucxCtrl    = %lx\n", loop, (gulong)&ioSpi[loop].aucxCtrl );
		IntErnals_RS_printf("ioSpi[%d].st           = %lx\n", loop, (gulong)&ioSpi[loop].st );
		IntErnals_RS_printf("ioSpi[%d].slvSel      = %lx\n", loop, (gulong)&ioSpi[loop].slvSel );
		IntErnals_RS_printf("ioSpi[%d].slvPol      = %lx\n", loop, (gulong)&ioSpi[loop].slvPol );
		IntErnals_RS_printf("ioSpi[%d].intEn       = %lx\n", loop, (gulong)&ioSpi[loop].intEn );
		IntErnals_RS_printf("ioSpi[%d].intSt       = %lx\n", loop, (gulong)&ioSpi[loop].intSt );
		IntErnals_RS_printf("ioSpi[%d].intClr      = %lx\n", loop, (gulong)&ioSpi[loop].intClr );
		IntErnals_RS_printf("ioSpi[%d].txfifo       = %lx\n", loop, (gulong)&ioSpi[loop].txfifo );
		IntErnals_RS_printf("ioSpi[%d].rxfifo       = %lx\n", loop, (gulong)&ioSpi[loop].rxfifo );
		IntErnals_RS_printf("ioSpi[%d].dmaTo       = %lx\n", loop, (gulong)&ioSpi[loop].dmaTo );
		IntErnals_RS_printf("ioSpi[%d].msDly       = %lx\n", loop, (gulong)&ioSpi[loop].msDly );
		IntErnals_RS_printf("ioSpi[%d].en           = %lx\n", loop, (gulong)&ioSpi[loop].en );
		IntErnals_RS_printf("ioSpi[%d].fifoDpth    = %lx\n", loop, (gulong)&ioSpi[loop].fifoDpth );
		IntErnals_RS_printf("ioSpi[%d].fifoWmk     = %lx\n", loop, (gulong)&ioSpi[loop].fifoWmk );
		IntErnals_RS_printf("ioSpi[%d].txDwr       = %lx\n", loop, (gulong)&ioSpi[loop].txDwr );
		IntErnals_RS_printf(" \n");
	}
#endif
}

SpiTest *spi_test_new()
{
	SpiTest *self = g_object_new(SPI_TYPE_TEST, NULL);

	return self;
}
