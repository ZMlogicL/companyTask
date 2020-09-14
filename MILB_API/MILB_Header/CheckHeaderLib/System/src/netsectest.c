/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020年9月3日
*@author              :郑蛘钊
*@brief               :
*@rely                :glib
*@function
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/


#include <stdio.h>
#include <stdlib.h>
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
#include "defs.h"
#include "netsectest.h"


G_DEFINE_TYPE(NetsecTest, netsec_test, G_TYPE_OBJECT);

#define NETSEC_TEST_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o),NETSEC_TYPE_TEST, NetsecTestPrivate));


struct _NetsecTestPrivate
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
static void netsec_test_class_init(NetsecTestClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(NetsecTestPrivate));

	AbsHeaderTestClass *absClass =  ABS_HEADER_TEST_CALSS(klass);
	absClass->run = run_od;
}

static void netsec_test_init(NetsecTest *self)
{
	NetsecTestPrivate *priv = NETSEC_TEST_GET_PRIVATE(self);

}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(netsec_test_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	NetsecTest *self = NETSEC_TEST(object);
	NetsecTestPrivate *priv = NETSEC_TEST_GET_PRIVATE(self);
	G_OBJECT_CLASS(netsec_test_parent_class)->finalize(object);

}

static void run_od(AbsHeaderTest *self)
{

}
/**
 * PUBLIC
 */
void netsec_test(NetsecTest* self)
{
	RS_printf("NETSEC\n");
#if 0
	RS_printf("ioNetsec.cnt90k32    = 0x%p\n", &ioNetsec.cnt90k32 );
	RS_printf("ioNetsec.cntEn       = 0x%p\n", &ioNetsec.cntEn );
	RS_printf("ioNetsec.cntAdo32    = 0x%p\n", &ioNetsec.cntAdo32 );
	RS_printf("ioNetsec.cnt27mU32   = 0x%p\n", &ioNetsec.cnt27mU32 );
	RS_printf("ioNetsec.cnt27mL32   = 0x%p\n", &ioNetsec.cnt27mL32 );
	RS_printf(" \n");
#endif
}

NetsecTest *netsec_test_new(void)
{
	NetsecTest *self = g_object_new(NETSEC_TYPE_TEST, NULL);
	return self;
}
