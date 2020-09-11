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
/*************************************************************************/
void netsec_test()
{
	RS_printf("NETSEC\n");
#if 0
	RS_printf("IO_NETSEC.CNT90K_32    = 0x%p\n", &IO_NETSEC.CNT90K_32 );
	RS_printf("IO_NETSEC.CNT_EN       = 0x%p\n", &IO_NETSEC.CNT_EN );
	RS_printf("IO_NETSEC.CNT_ADO_32   = 0x%p\n", &IO_NETSEC.CNT_ADO_32 );
	RS_printf("IO_NETSEC.CNT27M_U32   = 0x%p\n", &IO_NETSEC.CNT27M_U32 );
	RS_printf("IO_NETSEC.CNT27M_L32   = 0x%p\n", &IO_NETSEC.CNT27M_L32 );
	RS_printf(" \n");
#endif
}

NetsecTest *netsec_test_new()
{
	NetsecTest *self = g_object_new(NETSEC_TYPE_TEST, NULL);
	return self;
}
