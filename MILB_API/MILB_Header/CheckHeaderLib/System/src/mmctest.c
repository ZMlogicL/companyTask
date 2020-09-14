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
#include "mmctest.h"


G_DEFINE_TYPE(MmcTest, mmc_test, G_TYPE_OBJECT);

#define MMC_TEST_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o),MMC_TYPE_TEST, MmcTestPrivate));


struct _MmcTestPrivate
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
static void mmc_test_class_init(MmcTestClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(MmcTestPrivate));

	AbsHeaderTestClass *absClass =  ABS_HEADER_TEST_CALSS(klass);
	absClass->run = run_od;
}

static void mmc_test_init(MmcTest *self)
{
	MmcTestPrivate *priv = MMC_TEST_GET_PRIVATE(self);

}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(mmc_test_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	MmcTest *self = MMC_TEST(object);
	MmcTestPrivate *priv = MMC_TEST_GET_PRIVATE(self);
	G_OBJECT_CLASS(mmc_test_parent_class)->finalize(object);

}

static void run_od(AbsHeaderTest *self)
{

}
/**
 * PUBLIC
 */
void mcc_test(MmcTest* self)
{
	RS_printf("MCC\n");
#if 0
	RS_printf("ioMcc         = %p\n", &ioMcc );
	RS_printf("Reserved      = %p\n", &ioMcc.dmyA000A00f );
	RS_printf("ioMcc.mcswfi  = %p\n", &ioMcc.mcswfi );
	RS_printf("Reserved      = %p\n", &ioMcc.dmyA014Afff );
	RS_printf(" \n");
#endif
}

MmcTest *mmc_test_new(void)
{
	MmcTest *self = g_object_new(MMC_TYPE_TEST, NULL);
	return self;
}
