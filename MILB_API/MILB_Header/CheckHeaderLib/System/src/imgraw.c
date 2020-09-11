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
#include "imgraw.h"


G_DEFINE_TYPE(ImgRaw, img_raw, G_TYPE_OBJECT);

#define IMG_RAW_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o),IMG_TYPE_RAW, ImgRawPrivate));


struct _ImgRawPrivate
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
static void img_raw_class_init(ImgRawClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(ImgRawPrivate));

	AbsHeaderTestClass *absClass =  ABS_HEADER_TEST_CALSS(klass);
	absClass->run = run_od;
}

static void img_raw_init(ImgRaw *self)
{
	ImgRawPrivate *priv = IMG_RAW_GET_PRIVATE(self);

}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(img_raw_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	ImgRaw *self = IMG_RAW(object);
	ImgRawPrivate *priv = IMG_RAW_GET_PRIVATE(self);
	G_OBJECT_CLASS(img_raw_parent_class)->finalize(object);

}

static void run_od(AbsHeaderTest *self)
{

}
/**
 * PUBLIC
 */
/*************************************************************************/
void img_raw()
{
	RS_printf("RAW\n");
#if 0
	RS_printf("IO_RAW.RCTL0    = 0x%08x\n", (unsigned int)&IO_RAW.RCTL0   );
	RS_printf("IO_RAW.RCTL1    = 0x%08x\n", (unsigned int)&IO_RAW.RCTL1   );
	RS_printf("IO_RAW.COND     = 0x%08x\n", (unsigned int)&IO_RAW.COND    );
	RS_printf("IO_RAW.RINTF    = 0x%08x\n", (unsigned int)&IO_RAW.RINTF   );
	RS_printf("IO_RAW.RINTE    = 0x%08x\n", (unsigned int)&IO_RAW.RINTE   );
	RS_printf("IO_RAW.HSIZE    = 0x%08x\n", (unsigned int)&IO_RAW.HSIZE   );
	RS_printf("IO_RAW.VSIZE    = 0x%08x\n", (unsigned int)&IO_RAW.VSIZE   );
	RS_printf("IO_RAW.DSIZE    = 0x%08x\n", (unsigned int)&IO_RAW.DSIZE   );
	RS_printf("IO_RAW.MSA      = 0x%08x\n", (unsigned int)&IO_RAW.MSA     );
	RS_printf("IO_RAW.MDA      = 0x%08x\n", (unsigned int)&IO_RAW.MDA     );
	RS_printf("IO_RAW.DEFINIT  = 0x%08x\n", (unsigned int)&IO_RAW.DEFINIT );
	RS_printf("IO_RAW.CLMT     = 0x%08x\n", (unsigned int)&IO_RAW.CLMT    );
	RS_printf("IO_RAW.CCNT     = 0x%08x\n", (unsigned int)&IO_RAW.CCNT    );
	RS_printf("IO_RAW.TBLAEN   = 0x%08x\n", (unsigned int)&IO_RAW.TBLAEN  );
	RS_printf("IO_RAW.MRAXCTL  = 0x%08x\n", (unsigned int)&IO_RAW.MRAXCTL );
	RS_printf("IO_RAW.MWAXCTL  = 0x%08x\n", (unsigned int)&IO_RAW.MWAXCTL );
	RS_printf("IO_RAW.MRAXSTS  = 0x%08x\n", (unsigned int)&IO_RAW.MRAXSTS );
	RS_printf("IO_RAW.MWAXSTS  = 0x%08x\n", (unsigned int)&IO_RAW.MWAXSTS );
	RS_printf("IO_RAW.CODE     = 0x%08x\n", (unsigned int)&IO_RAW.CODE    );
	RS_printf("IO_RAW.LEN      = 0x%08x\n", (unsigned int)&IO_RAW.LEN     );
	RS_printf("IO_RAW.LUT      = 0x%08x\n", (unsigned int)&IO_RAW.LUT     );

	RS_printf(" \n");
#endif
}

ImgRaw *img_raw_new()
{
	ImgRaw *self = g_object_new(IMG_TYPE_RAW, NULL);
	return self;
}
