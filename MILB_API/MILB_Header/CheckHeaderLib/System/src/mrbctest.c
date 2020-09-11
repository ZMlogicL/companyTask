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
#include "mrbctest.h"


G_DEFINE_TYPE(MrbcTest, mrbc_test, G_TYPE_OBJECT);

#define MRBC_TEST_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o),MRBC_TYPE_TEST, MrbcTestPrivate));


struct _MrbcTestPrivate
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
static void mrbc_test_class_init(MrbcTestClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(MrbcTestPrivate));

	AbsHeaderTestClass *absClass =  ABS_HEADER_TEST_CALSS(klass);
	absClass->run = run_od;
}

static void mrbc_test_init(MrbcTest *self)
{
	MrbcTestPrivate *priv = MRBC_TEST_GET_PRIVATE(self);

}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(mrbc_test_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	MrbcTest *self = MRBC_TEST(object);
	MrbcTestPrivate *priv = MRBC_TEST_GET_PRIVATE(self);
	G_OBJECT_CLASS(mrbc_test_parent_class)->finalize(object);

}

static void run_od(AbsHeaderTest *self)
{

}
/**
 * PUBLIC
 */
/*************************************************************************/
void mrbc_test()
{
#if 0	// for PC debug
#define IO_MRBC	(*IO_MRBC2)
	volatile struct io_mrbc*		IO_MRBC2		= (void*)0xFFF68000;
#endif
	RS_printf("MRBC\n");
#if 0
	RS_printf("Reserved       = %p\n", &IO_MRBC.dmy_8000_800F );
	RS_printf("IO_MRBC.VIHSTA = %p\n", &IO_MRBC.VIHSTA );
	RS_printf("IO_MRBC.VIHSET = %p\n", &IO_MRBC.VIHSET );
	RS_printf("IO_MRBC.VIHCLR = %p\n", &IO_MRBC.VIHCLR );
	RS_printf("Reserved       = %p\n", &IO_MRBC.dmy_801C_8FFF );
	RS_printf(" \n");
#endif
}

MrbcTest *mrbc_test_new()
{
	MrbcTest *self = g_object_new(MRBC_TYPE_TEST, NULL);
	return self;
}
