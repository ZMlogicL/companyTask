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

	CheckHeaderMain_RS_PRINTF("SPI\n");
#if 0
	int loop;

	for (loop = 0; loop < 3; loop++) {
		CheckHeaderMain_RS_PRINTF("ioSpi[%d].txdata       = %lx\n", loop, (gulong)&ioSpi[loop].txdata );
		CheckHeaderMain_RS_PRINTF("ioSpi[%d].rxdata       = %lx\n", loop, (gulong)&ioSpi[loop].rxdata );
		CheckHeaderMain_RS_PRINTF("ioSpi[%d].div          = %lx\n", loop, (gulong)&ioSpi[loop].div );
		CheckHeaderMain_RS_PRINTF("ioSpi[%d].ctrl         = %lx\n", loop, (gulong)&ioSpi[loop].ctrl );
		CheckHeaderMain_RS_PRINTF("ioSpi[%d].aucxCtrl    = %lx\n", loop, (gulong)&ioSpi[loop].aucxCtrl );
		CheckHeaderMain_RS_PRINTF("ioSpi[%d].st           = %lx\n", loop, (gulong)&ioSpi[loop].st );
		CheckHeaderMain_RS_PRINTF("ioSpi[%d].slvSel      = %lx\n", loop, (gulong)&ioSpi[loop].slvSel );
		CheckHeaderMain_RS_PRINTF("ioSpi[%d].slvPol      = %lx\n", loop, (gulong)&ioSpi[loop].slvPol );
		CheckHeaderMain_RS_PRINTF("ioSpi[%d].intEn       = %lx\n", loop, (gulong)&ioSpi[loop].intEn );
		CheckHeaderMain_RS_PRINTF("ioSpi[%d].intSt       = %lx\n", loop, (gulong)&ioSpi[loop].intSt );
		CheckHeaderMain_RS_PRINTF("ioSpi[%d].intClr      = %lx\n", loop, (gulong)&ioSpi[loop].intClr );
		CheckHeaderMain_RS_PRINTF("ioSpi[%d].txfifo       = %lx\n", loop, (gulong)&ioSpi[loop].txfifo );
		CheckHeaderMain_RS_PRINTF("ioSpi[%d].rxfifo       = %lx\n", loop, (gulong)&ioSpi[loop].rxfifo );
		CheckHeaderMain_RS_PRINTF("ioSpi[%d].dmaTo       = %lx\n", loop, (gulong)&ioSpi[loop].dmaTo );
		CheckHeaderMain_RS_PRINTF("ioSpi[%d].msDly       = %lx\n", loop, (gulong)&ioSpi[loop].msDly );
		CheckHeaderMain_RS_PRINTF("ioSpi[%d].en           = %lx\n", loop, (gulong)&ioSpi[loop].en );
		CheckHeaderMain_RS_PRINTF("ioSpi[%d].fifoDpth    = %lx\n", loop, (gulong)&ioSpi[loop].fifoDpth );
		CheckHeaderMain_RS_PRINTF("ioSpi[%d].fifoWmk     = %lx\n", loop, (gulong)&ioSpi[loop].fifoWmk );
		CheckHeaderMain_RS_PRINTF("ioSpi[%d].txDwr       = %lx\n", loop, (gulong)&ioSpi[loop].txDwr );
		CheckHeaderMain_RS_PRINTF(" \n");
	}
#endif
}

SpiTest *spi_test_new()
{
	SpiTest *self = g_object_new(SPI_TYPE_TEST, NULL);

	return self;
}
