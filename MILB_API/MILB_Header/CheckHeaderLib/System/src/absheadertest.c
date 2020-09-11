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
#include "absheadertest.h"


G_DEFINE_TYPE(AbsHeaderTest, abs_header_test, G_TYPE_OBJECT);

#define ABS_HEADER_TEST_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o),ABS_TYPE_HEADER_TEST, AbsHeaderTestPrivate));


struct _AbsHeaderTestPrivate
{
	 gpointer preserved;
};

/**
 * DECLS
 */
static void 	dispose_od(GObject *object);
static void 	finalize_od(GObject *object);
/**
 * IMPL
 */
static void abs_header_test_class_init(AbsHeaderTestClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(AbsHeaderTestPrivate));
}

static void abs_header_test_init(AbsHeaderTest *self)
{
	AbsHeaderTestPrivate *priv = ABS_HEADER_TEST_GET_PRIVATE(self);

}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(abs_header_test_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	AbsHeaderTest *self = ABS_HEADER_TEST(object);
	AbsHeaderTestPrivate *priv = ABS_HEADER_TEST_GET_PRIVATE(self);
	G_OBJECT_CLASS(abs_header_test_parent_class)->finalize(object);

}
/**
 * PUBLIC
 */
AbsHeaderTest *abs_header_test_new()
{
	AbsHeaderTest *self = g_object_new(ABS_TYPE_HEADER_TEST, NULL);
	return self;
}
