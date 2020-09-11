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
#include "gtimertest.h"


G_DEFINE_TYPE(GtimerTest, gtimer_test, G_TYPE_OBJECT);

#define GTIMER_TEST_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o),GTIMER_TYPE_TEST, GtimerTestPrivate));


struct _GtimerTestPrivate
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
static void gtimer_test_class_init(GtimerTestClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(GtimerTestPrivate));

	AbsHeaderTestClass *absClass =  ABS_HEADER_TEST_CALSS(klass);
	absClass->run = run_od;
}

static void gtimer_test_init(GtimerTest *self)
{
	GtimerTestPrivate *priv = GTIMER_TEST_GET_PRIVATE(self);

}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(gtimer_test_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	GtimerTest *self = GTIMER_TEST(object);
	GtimerTestPrivate *priv = GTIMER_TEST_GET_PRIVATE(self);
	G_OBJECT_CLASS(gtimer_test_parent_class)->finalize(object);

}

static void run_od(AbsHeaderTest *self)
{

}
/**
 * PUBLIC
 */
/*************************************************************************/
void gtimer_test()
{
	RS_printf("GlobalTimer\n");
#if 0
	RS_printf("IO_GTIMER                  = %p\n", &IO_GTIMER );
	RS_printf("IO_GTIMER.GTIMER_COUNTER   = %p\n", &IO_GTIMER.GTIMER_COUNTER );
	RS_printf("IO_GTIMER.GTIMER_CONTROL   = %p\n", &IO_GTIMER.GTIMER_CONTROL );
	RS_printf("IO_GTIMER.GTIMER_INTERRUPT = %p\n", &IO_GTIMER.GTIMER_INTERRUPT );
	RS_printf("IO_GTIMER.GTIMER_COMPA     = %p\n", &IO_GTIMER.GTIMER_COMPA );
	RS_printf("IO_GTIMER.GTIMER_AUTOINC   = %p\n", &IO_GTIMER.GTIMER_AUTOINC );
	RS_printf(" \n");
#endif
}

GtimerTest *gtimer_test_new()
{
	GtimerTest *self = g_object_new(GTIMER_TYPE_TEST, NULL);
	return self;
}
