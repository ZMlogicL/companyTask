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
/*************************************************************************/
void mcc_test()
{
	RS_printf("MCC\n");
#if 0
	RS_printf("IO_MCC        = %p\n", &IO_MCC );
	RS_printf("Reserved      = %p\n", &IO_MCC.dmy_A000_A00F );
	RS_printf("IO_MCC.MCSWFI = %p\n", &IO_MCC.MCSWFI );
	RS_printf("Reserved      = %p\n", &IO_MCC.dmy_A014_AFFF );
	RS_printf(" \n");
#endif
}

MmcTest *mmc_test_new()
{
	MmcTest *self = g_object_new(MMC_TYPE_TEST, NULL);
	return self;
}
