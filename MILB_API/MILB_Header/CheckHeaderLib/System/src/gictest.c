/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020年9月3日
*@author              :陈柱
*@brief               :
*@rely                :glib
*@function
*设计的主要功能:
*1、
*@version
*
*/
#include "defs.h"
#include "gictest.h"


G_DEFINE_TYPE(GicTest, gic_test, G_TYPE_OBJECT);

#define GIC_TEST_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o),GIC_TYPE_TEST, GicTestPrivate));


struct _GicTestPrivate
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
static void gic_test_class_init(GicTestClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(GicTestPrivate));

	AbsHeaderTestClass *absClass =  ABS_HEADER_TEST_CALSS(klass);
	absClass->run = run_od;
}

static void gic_test_init(GicTest *self)
{
	GicTestPrivate *priv = GIC_TEST_GET_PRIVATE(self);

}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(gic_test_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	GicTest *self = GIC_TEST(object);
	GicTestPrivate *priv = GIC_TEST_GET_PRIVATE(self);
	G_OBJECT_CLASS(gic_test_parent_class)->finalize(object);

}

static void run_od(AbsHeaderTest *self)
{

}
/**
 * PUBLIC
 */
/*************************************************************************/
void gic_test()
{
	RS_printf("GIC\n");
#if 0
	RS_printf("IO_GIC_DIST                 = %p\n", &IO_GIC_DIST );
	RS_printf("IO_GIC_DIST.GICD_CTLR       = %p\n", &IO_GIC_DIST.GICD_CTLR );
	RS_printf("IO_GIC_DIST.GICD_TYPER      = %p\n", &IO_GIC_DIST.GICD_TYPER );
	RS_printf("IO_GIC_DIST.GICD_IIDR       = %p\n", &IO_GIC_DIST.GICD_IIDR );
	RS_printf("Reserved                    = %p\n", &IO_GIC_DIST.dmy_100C_107F );
	RS_printf("IO_GIC_DIST.GICD_IGROUPR    = %p\n", &IO_GIC_DIST.GICD_IGROUPR );
	RS_printf("IO_GIC_DIST.GICD_ISENABLER  = %p\n", &IO_GIC_DIST.GICD_ISENABLER );
	RS_printf("IO_GIC_DIST.GICD_ICENABLER  = %p\n", &IO_GIC_DIST.GICD_ICENABLER );
	RS_printf("IO_GIC_DIST.GICD_ISPENDR    = %p\n", &IO_GIC_DIST.GICD_ISPENDR );
	RS_printf("IO_GIC_DIST.GICD_ICPENDR    = %p\n", &IO_GIC_DIST.GICD_ICPENDR );
	RS_printf("IO_GIC_DIST.GICD_ISACTIVER  = %p\n", &IO_GIC_DIST.GICD_ISACTIVER );
	RS_printf("IO_GIC_DIST.GICD_ICACTIVER  = %p\n", &IO_GIC_DIST.GICD_ICACTIVER );
	RS_printf("IO_GIC_DIST.GICD_IPRIORITYR = %p\n", &IO_GIC_DIST.GICD_IPRIORITYR );
	RS_printf("Reserved                    = %p\n", &IO_GIC_DIST.dmy_1600_17FF );
	RS_printf("IO_GIC_DIST.GICD_ITARGETSR  = %p\n", &IO_GIC_DIST.GICD_ITARGETSR );
	RS_printf("Reserved                    = %p\n", &IO_GIC_DIST.dmy_1A00_1BFF );
	RS_printf("IO_GIC_DIST.GICD_ICFGR      = %p\n", &IO_GIC_DIST.GICD_ICFGR );
	RS_printf("Reserved                    = %p\n", &IO_GIC_DIST.dmy_1C80_1CFF );
	RS_printf("IO_GIC_DIST.GICD_PPISR      = %p\n", &IO_GIC_DIST.GICD_PPISR );
	RS_printf("IO_GIC_DIST.GICD_SPISR      = %p\n", &IO_GIC_DIST.GICD_SPISR );
	RS_printf("Reserved                    = %p\n", &IO_GIC_DIST.dmy_1D40_1DFF );
	RS_printf("IO_GIC_DIST.GICD_SGIR       = %p\n", &IO_GIC_DIST.GICD_SGIR );
	RS_printf("Reserved                    = %p\n", &IO_GIC_DIST.dmy_1F04_1F0F );
	RS_printf("IO_GIC_DIST.GICD_CPENDSGIR  = %p\n", &IO_GIC_DIST.GICD_CPENDSGIR );
	RS_printf("IO_GIC_DIST.GICD_SPENDSGIR  = %p\n", &IO_GIC_DIST.GICD_SPENDSGIR );
	RS_printf("Reserved                    = %p\n", &IO_GIC_DIST.dmy_1F30_1FFF );
	RS_printf(" \n");

	RS_printf("IO_GIC_CPU                  = %p\n", &IO_GIC_CPU );
	RS_printf("IO_GIC_CPU.GICC_CTLR        = %p\n", &IO_GIC_CPU.GICC_CTLR );
	RS_printf("IO_GIC_CPU.GICC_PMR         = %p\n", &IO_GIC_CPU.GICC_PMR );
	RS_printf("IO_GIC_CPU.GICC_BPR         = %p\n", &IO_GIC_CPU.GICC_BPR );
	RS_printf("IO_GIC_CPU.GICC_IAR         = %p\n", &IO_GIC_CPU.GICC_IAR );
	RS_printf("IO_GIC_CPU.GICC_EOIR        = %p\n", &IO_GIC_CPU.GICC_EOIR );
	RS_printf("IO_GIC_CPU.GICC_RPR         = %p\n", &IO_GIC_CPU.GICC_RPR );
	RS_printf("IO_GIC_CPU.GICC_HPPIR       = %p\n", &IO_GIC_CPU.GICC_HPPIR );
	RS_printf("IO_GIC_CPU.GICC_ABPR        = %p\n", &IO_GIC_CPU.GICC_ABPR );
	RS_printf("IO_GIC_CPU.GICC_AIAR        = %p\n", &IO_GIC_CPU.GICC_AIAR );
	RS_printf("IO_GIC_CPU.GICC_AEOIR       = %p\n", &IO_GIC_CPU.GICC_AEOIR );
	RS_printf("IO_GIC_CPU.GICC_AHPPIR      = %p\n", &IO_GIC_CPU.GICC_AHPPIR );
	RS_printf("Reserved                    = %p\n", &IO_GIC_CPU.dmy_202C_20CF );
	RS_printf("IO_GIC_CPU.GICC_APR0        = %p\n", &IO_GIC_CPU.GICC_APR0 );
	RS_printf("Reserved                    = %p\n", &IO_GIC_CPU.dmy_20D4_20DF );
	RS_printf("IO_GIC_CPU.GICC_NSAPR0      = %p\n", &IO_GIC_CPU.GICC_NSAPR0 );
	RS_printf("Reserved                    = %p\n", &IO_GIC_CPU.dmy_20E4_20FB );
	RS_printf("IO_GIC_CPU.GICC_IIDR        = %p\n", &IO_GIC_CPU.GICC_IIDR );
	RS_printf("Reserved                    = %p\n", &IO_GIC_CPU.dmy_2100_2FFF );
	RS_printf("IO_GIC_CPU.GICC_DIR         = %p\n", &IO_GIC_CPU.GICC_DIR );
	RS_printf(" \n");
#endif
}

GicTest *gic_test_new()
{
	GicTest *self = g_object_new(GIC_TYPE_TEST, NULL);
	return self;
}
