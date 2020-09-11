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
#include "exiutest.h"


G_DEFINE_TYPE(ExiuTest, exiu_test, G_TYPE_OBJECT);

#define EXIU_TEST_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o),EXIU_TYPE_TEST, ExiuTestPrivate));


struct _ExiuTestPrivate
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
static void exiu_test_class_init(ExiuTestClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(ExiuTestPrivate));

	AbsHeaderTestClass *absClass =  ABS_HEADER_TEST_CALSS(klass);
	absClass->run = run_od;
}

static void exiu_test_init(ExiuTest *self)
{
	ExiuTestPrivate *priv = EXIU_TEST_GET_PRIVATE(self);

}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(exiu_test_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	ExiuTest *self = EXIU_TEST(object);
	ExiuTestPrivate *priv = EXIU_TEST_GET_PRIVATE(self);
	G_OBJECT_CLASS(exiu_test_parent_class)->finalize(object);

}

static void run_od(AbsHeaderTest *self)
{

}
/**
 * PUBLIC
 */
/*************************************************************************/
void exiu_test()
{
	RS_printf("EXIU\n");
#if 0
	RS_printf("IO_EXIU                      = %p\n", &IO_EXIU );
	RS_printf("IO_EXIU.EIMASK               = %p\n", &IO_EXIU.EIMASK );
	RS_printf("IO_EXIU.EISRCSEL             = %p\n", &IO_EXIU.EISRCSEL );
	RS_printf("IO_EXIU.EIREQSTA             = %p\n", &IO_EXIU.EIREQSTA );
	RS_printf("IO_EXIU.EIRAWREQSTA          = %p\n", &IO_EXIU.EIRAWREQSTA );
	RS_printf("IO_EXIU.EIREQCLR             = %p\n", &IO_EXIU.EIREQCLR );
	RS_printf("IO_EXIU.EILVL                = %p\n", &IO_EXIU.EILVL );
	RS_printf("IO_EXIU.EIEDG                = %p\n", &IO_EXIU.EIEDG );
	RS_printf("IO_EXIU.EISIR                = %p\n", &IO_EXIU.EISIR );
	RS_printf(" \n");
#endif
}

ExiuTest *exiu_test_new()
{
	ExiuTest *self = g_object_new(EXIU_TYPE_TEST, NULL);
	return self;
}
