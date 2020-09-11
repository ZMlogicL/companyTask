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
#include "timestamptest.h"


G_DEFINE_TYPE(TimestampTest, timestamp_test, G_TYPE_OBJECT);

#define TIMESTAMP_TEST_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o),TIMESTAMP_TYPE_TEST, TimestampTestPrivate));


struct _TimestampTestPrivate
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
static void timestamp_test_class_init(TimestampTestClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);

	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(TimestampTestPrivate));
	AbsHeaderTestClass *absClass =  ABS_HEADER_TEST_CALSS(klass);

	absClass->run = run_od;
}

static void timestamp_test_init(TimestampTest *self)
{
	TimestampTestPrivate *priv = TIMESTAMP_TEST_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(timestamp_test_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	TimestampTest *self = TIMESTAMP_TEST(object);
	TimestampTestPrivate *priv = TIMESTAMP_TEST_GET_PRIVATE(self);

	G_OBJECT_CLASS(timestamp_test_parent_class)->finalize(object);
}

static void run_od(AbsHeaderTest *self)
{

}
/**
 * PUBLIC
 */
void timestamp_test()
{
	IntErnals_RS_printf("TIMESTAMP\n");
#if 0
	IntErnals_RS_printf("ioTimestamp\n");
	IntErnals_RS_printf("ioTimestamp                  = %p\n", &ioTimestamp );
	IntErnals_RS_printf("ioTimestamp.cntcr            = %p\n", &ioTimestamp.cntcr );
	IntErnals_RS_printf("ioTimestamp.cntsr            = %p\n", &ioTimestamp.cntsr );
	IntErnals_RS_printf("ioTimestamp.cntcvl           = %p\n", &ioTimestamp.cntcvl );
	IntErnals_RS_printf("ioTimestamp.cntcvu           = %p\n", &ioTimestamp.cntcvu );
	IntErnals_RS_printf("Reserved                      = %p\n", &ioTimestamp.dmy0010001f );
	IntErnals_RS_printf("ioTimestamp.cntfid0          = %p\n", &ioTimestamp.cntfid0 );
	IntErnals_RS_printf("Reserved                      = %p\n", &ioTimestamp.dmy00240fcf );
	IntErnals_RS_printf("ioTimestamp.pidr4            = %p\n", &ioTimestamp.pidr4 );
	IntErnals_RS_printf("Reserved                      = %p\n", &ioTimestamp.dmy0fd40fdf );
	IntErnals_RS_printf("ioTimestamp.pidr0            = %p\n", &ioTimestamp.pidr0 );
	IntErnals_RS_printf("ioTimestamp.pidr1            = %p\n", &ioTimestamp.pidr1 );
	IntErnals_RS_printf("ioTimestamp.pidr2            = %p\n", &ioTimestamp.pidr2 );
	IntErnals_RS_printf("ioTimestamp.pidr3            = %p\n", &ioTimestamp.pidr3 );
	IntErnals_RS_printf("ioTimestamp.cidr0            = %p\n", &ioTimestamp.cidr0 );
	IntErnals_RS_printf("ioTimestamp.cidr1            = %p\n", &ioTimestamp.cidr1 );
	IntErnals_RS_printf("ioTimestamp.cidr2            = %p\n", &ioTimestamp.cidr2 );
	IntErnals_RS_printf("ioTimestamp.cidr3            = %p\n", &ioTimestamp.cidr3 );
	IntErnals_RS_printf(" \n");
#endif
}

TimestampTest *timestamp_test_new()
{
	TimestampTest *self = g_object_new(TIMESTAMP_TYPE_TEST, NULL);

	return self;
}
