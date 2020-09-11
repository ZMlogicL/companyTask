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
#include "imgtest.h"


G_DEFINE_TYPE(ImgTest, img_test, G_TYPE_OBJECT);

#define IMG_TEST_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o),IMG_TYPE_TEST, ImgTestPrivate));


struct _ImgTestPrivate
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
static void img_test_class_init(ImgTestClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(ImgTestPrivate));

	AbsHeaderTestClass *absClass =  ABS_HEADER_TEST_CALSS(klass);
	absClass->run = run_od;
}

static void img_test_init(ImgTest *self)
{
	ImgTestPrivate *priv = IMG_TEST_GET_PRIVATE(self);

}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(img_test_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	ImgTest *self = IMG_TEST(object);
	ImgTestPrivate *priv = IMG_TEST_GET_PRIVATE(self);
	G_OBJECT_CLASS(img_test_parent_class)->finalize(object);

}

static void run_od(AbsHeaderTest *self)
{

}
/**
 * PUBLIC
 */
/*************************************************************************/
void img_test()
{
	RS_printf("IMG\n");
#if 0
	RS_printf("IO_IMG.IMGPIPEPSW = 0x%08x\n", (unsigned int)&IO_IMG.IMGPIPEPSW );
	RS_printf("IO_IMG.MXICMON    = 0x%08x\n", (unsigned int)&IO_IMG.MXICMON );
	RS_printf("IO_IMG.SRAMPD     = 0x%08x\n", (unsigned int)&IO_IMG.SRAMPD );
	RS_printf(" \n");
#endif
}

ImgTest *img_test_new()
{
	ImgTest *self = g_object_new(IMG_TYPE_TEST, NULL);
	return self;
}
