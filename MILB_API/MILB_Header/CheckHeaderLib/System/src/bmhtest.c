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
#include "bmhtest.h"


G_DEFINE_TYPE(BmhTest, bmh_test, G_TYPE_OBJECT);

#define BMH_TEST_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o),BMH_TYPE_TEST, BmhTestPrivate));


struct _BmhTestPrivate
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
static void bmh_test_class_init(BmhTestClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(BmhTestPrivate));

	AbsHeaderTestClass *absClass =  ABS_HEADER_TEST_CALSS(klass);
	absClass->run = run_od;
}

static void bmh_test_init(BmhTest *self)
{
	BmhTestPrivate *priv = BMH_TEST_GET_PRIVATE(self);

}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(bmh_test_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	BmhTest *self = BMH_TEST(object);
	BmhTestPrivate *priv = BMH_TEST_GET_PRIVATE(self);
	G_OBJECT_CLASS(bmh_test_parent_class)->finalize(object);

}

static void run_od(AbsHeaderTest *self)
{

}
/**
 * PUBLIC
 */
/*************************************************************************/
void bmh_test()
{
#if 0	// for PC debug
	volatile IoBmh*		IO_BMH;
	IO_BMH = (void*)0x1D400000;
	int loop;
#endif
	RS_printf("BMH\n");
#if 0
	for( loop = 0; loop < 2; loop++ ){
		RS_printf("IO_BMH[%d].BMHSR      = 0x%lX\n", loop, (unsigned long)&IO_BMH[loop].BMHSR );
		RS_printf("IO_BMH[%d].BMHTRG     = 0x%lX\n", loop, (unsigned long)&IO_BMH[loop].BMHTRG );
		RS_printf("IO_BMH[%d].BMHRE      = 0x%lX\n", loop, (unsigned long)&IO_BMH[loop].BMHRE );
		RS_printf("IO_BMH[%d].BMHCONT    = 0x%lX\n", loop, (unsigned long)&IO_BMH[loop].BMHCONT );
		RS_printf("IO_BMH[%d].BMHINTFS   = 0x%lX\n", loop, (unsigned long)&IO_BMH[loop].BMHINTFS );
		RS_printf("IO_BMH[%d].BMHINTE    = 0x%lX\n", loop, (unsigned long)&IO_BMH[loop].BMHINTE );
		RS_printf("IO_BMH[%d].BMHMD      = 0x%lX\n", loop, (unsigned long)&IO_BMH[loop].BMHMD );
		RS_printf("IO_BMH[%d].BMHPRM     = 0x%lX\n", loop, (unsigned long)&IO_BMH[loop].BMHPRM );
		RS_printf("IO_BMH[%d].BMHHCNT    = 0x%lX\n", loop, (unsigned long)&IO_BMH[loop].BMHHCNT );
		RS_printf("IO_BMH[%d].BMHSAD_WR  = 0x%lX\n", loop, (unsigned long)&IO_BMH[loop].BMHSAD_WR );
		RS_printf("IO_BMH[%d].BMHDMA     = 0x%lX\n", loop, (unsigned long)&IO_BMH[loop].BMHDMA );
		RS_printf("IO_BMH[%d].BMHGHSIZE  = 0x%lX\n", loop, (unsigned long)&IO_BMH[loop].BMHGHSIZE );
		RS_printf("IO_BMH[%d].BMHHSIZE   = 0x%lX\n", loop, (unsigned long)&IO_BMH[loop].BMHHSIZE );
		RS_printf("IO_BMH[%d].BMHVSIZE   = 0x%lX\n", loop, (unsigned long)&IO_BMH[loop].BMHVSIZE );
		RS_printf("IO_BMH[%d].BMHCURAD   = 0x%lX\n", loop, (unsigned long)&IO_BMH[loop].BMHCURAD );
		RS_printf("IO_BMH[%d].BMHREFAD   = 0x%lX\n", loop, (unsigned long)&IO_BMH[loop].BMHREFAD );
		RS_printf("IO_BMH[%d].BMHSADAD   = 0x%lX\n", loop, (unsigned long)&IO_BMH[loop].BMHSADAD );
		RS_printf("IO_BMH[%d].BMHSADGH   = 0x%lX\n", loop, (unsigned long)&IO_BMH[loop].BMHSADGH );
		RS_printf("IO_BMH[%d].BMHAXICTRL = 0x%lX\n", loop, (unsigned long)&IO_BMH[loop].BMHAXICTRL );
		RS_printf("IO_BMH[%d].BMHAXIERR  = 0x%lX\n", loop, (unsigned long)&IO_BMH[loop].BMHAXIERR );
		RS_printf("IO_BMH[%d].SADR       = 0x%lX\n", loop, (unsigned long)&IO_BMH[loop].SADR );
		RS_printf("IO_BMH[%d].CUR        = 0x%lX\n", loop, (unsigned long)&IO_BMH[loop].CUR );
		RS_printf("IO_BMH[%d].REF        = 0x%lX\n", loop, (unsigned long)&IO_BMH[loop].REF );
		RS_printf("IO_BMH[%d].LUT        = 0x%lX\n", loop, (unsigned long)&IO_BMH[loop].LUT );
		RS_printf(" \n");
	}
#endif
}

BmhTest *bmh_test_new()
{
	BmhTest *self = g_object_new(BMH_TYPE_TEST, NULL);
	return self;
}
