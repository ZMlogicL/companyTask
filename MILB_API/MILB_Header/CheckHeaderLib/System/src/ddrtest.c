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
#include "ddrtest.h"


G_DEFINE_TYPE(DdrTest, ddr_test, G_TYPE_OBJECT);

#define DDR_TEST_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o),DDR_TYPE_TEST, DdrTestPrivate));


struct _DdrTestPrivate
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
static void ddr_test_class_init(DdrTestClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(DdrTestPrivate));

	AbsHeaderTestClass *absClass =  ABS_HEADER_TEST_CALSS(klass);
	absClass->run = run_od;
}

static void ddr_test_init(DdrTest *self)
{
	DdrTestPrivate *priv = DDR_TEST_GET_PRIVATE(self);

}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(ddr_test_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	DdrTest *self = DDR_TEST(object);
	DdrTestPrivate *priv = DDR_TEST_GET_PRIVATE(self);
	G_OBJECT_CLASS(ddr_test_parent_class)->finalize(object);

}

static void run_od(AbsHeaderTest *self)
{

}
/**
 * PUBLIC
 */
/*************************************************************************/
void ddr_test()
{
	RS_printf("DDR\n");
#if 0
/* IO_DDR-PHY */
	for(int i=0; i<2; i++) {
		RS_printf("IO_SDRAMC[%d].DDR.IO_MRS[0]       = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_MRS[0] );
		RS_printf("IO_SDRAMC[%d].DDR.IO_MRSWT        = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_MRSWT );
		RS_printf("IO_SDRAMC[%d].DDR.IO_ACTWT        = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_ACTWT );
		RS_printf("IO_SDRAMC[%d].DDR.IO_PREWT        = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_PREWT );
		RS_printf("IO_SDRAMC[%d].DDR.IO_WRITEWT      = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_WRITEWT );
		RS_printf("IO_SDRAMC[%d].DDR.IO_READWT       = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_READWT );
		RS_printf("IO_SDRAMC[%d].DDR.IO_PHYMODE      = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_PHYMODE );
		RS_printf("IO_SDRAMC[%d].DDR.IO_DLLMODE1     = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_DLLMODE1 );
		RS_printf("-----------------------------------------\n" );
		RS_printf("IO_SDRAMC[%d].DDR.IO_DDRIS1       = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_DDRIS1 );
		RS_printf("IO_SDRAMC[%d].DDR.IO_PZQCM        = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_PZQCM );
		RS_printf("IO_SDRAMC[%d].DDR.IO_PZQCDM       = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_PZQCDM );
		RS_printf("IO_SDRAMC[%d].DDR.IO_DDRIOCM      = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_DDRIOCM );
		RS_printf("IO_SDRAMC[%d].DDR.IO_CTRLDSPC     = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_CTRLDSPC );
		RS_printf("IO_SDRAMC[%d].DDR.IO_DDRIS2       = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_DDRIS2 );
		RS_printf("IO_SDRAMC[%d].DDR.IO_DDLMODE3     = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_DDLMODE3 );
		RS_printf("-----------------------------------------\n" );
		RS_printf("IO_SDRAMC[%d].DDR.IO_TRMS         = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_TRMS );
		RS_printf("IO_SDRAMC[%d].DDR.IO_PBLCSW[0]    = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_PBLCSW[0] );
		RS_printf("-----------------------------------------\n" );
		RS_printf("IO_SDRAMC[%d].DDR.IO_PBLCSG[0]    = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_PBLCSG[0] );
		RS_printf("-----------------------------------------\n" );
		RS_printf("IO_SDRAMC[%d].DDR.IO_PBLCSR[0]    = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_PBLCSR[0] );
		RS_printf("-----------------------------------------\n" );
		RS_printf("IO_SDRAMC[%d].DDR.IO_SDRAMM       = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_SDRAMM );
		RS_printf("IO_SDRAMC[%d].DDR.IO_RANKSEL      = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_RANKSEL );
		RS_printf("IO_SDRAMC[%d].DDR.IO_NAODTS       = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_NAODTS );
		RS_printf("IO_SDRAMC[%d].DDR.IO_WLOS         = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_WLOS );
		RS_printf("IO_SDRAMC[%d].DDR.IO_WLRS[0]      = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_WLRS[0] );
		RS_printf("-----------------------------------------\n" );
		RS_printf("IO_SDRAMC[%d].DDR.IO_TWDS         = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_TWDS );
		RS_printf("IO_SDRAMC[%d].DDR.IO_TRWDEY       = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_TRWDEY );
		RS_printf("IO_SDRAMC[%d].DDR.IO_TRWLVL[0]    = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_TRWLVL[0] );
		RS_printf("-----------------------------------------\n" );
		RS_printf("IO_SDRAMC[%d].DDR.IO_TRGL[0]      = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_TRGL[0] );
		RS_printf("-----------------------------------------\n" );
		RS_printf("IO_SDRAMC[%d].DDR.IO_TRRDS        = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_TRRDS );
		RS_printf("IO_SDRAMC[%d].DDR.IO_TRRDEY[0]    = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_TRRDEY[0] );
		RS_printf("-----------------------------------------\n" );
		RS_printf("IO_SDRAMC[%d].DDR.IO_TRWDEDQS[0]  = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_TRWDEDQS[0] );
		RS_printf("-----------------------------------------\n" );
		RS_printf("IO_SDRAMC[%d].DDR.IO_TRRWTM       = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_TRRWTM );
		RS_printf("IO_SDRAMC[%d].DDR.IO_SRTE         = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_SRTE );
		RS_printf("IO_SDRAMC[%d].DDR.IO_SRWL[0]      = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_SRWL[0] );
		RS_printf("-----------------------------------------\n" );
		RS_printf("IO_SDRAMC[%d].DDR.IO_SRGT[0]      = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_SRGT[0] );
		RS_printf("-----------------------------------------\n" );
		RS_printf("IO_SDRAMC[%d].DDR.IO_SRRDS0[0]    = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_SRRDS0[0] );
		RS_printf("-----------------------------------------\n" );
		RS_printf("IO_SDRAMC[%d].DDR.IO_SRRDST       = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_SRRDST );
		RS_printf("IO_SDRAMC[%d].DDR.IO_SRWDE0[0]    = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_SRWDE0[0] );
		RS_printf("-----------------------------------------\n" );
		RS_printf("IO_SDRAMC[%d].DDR.IO_SRWDET       = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_SRWDET );
		RS_printf("IO_SDRAMC[%d].DDR.IO_SRRDE0[0]    = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_SRRDE0[0] );
		RS_printf("-----------------------------------------\n" );
		RS_printf("IO_SDRAMC[%d].DDR.IO_SRRDET       = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_SRRDET );
		RS_printf("IO_SDRAMC[%d].DDR.IO_SRWLWDE[0]   = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_SRWLWDE[0] );
		RS_printf("-----------------------------------------\n" );
		RS_printf("IO_SDRAMC[%d].DDR.IO_SRGTRDE[0]   = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_SRGTRDE[0] );
		RS_printf("-----------------------------------------\n" );
		RS_printf("IO_SDRAMC[%d].DDR.IO_SRRDSN[0]    = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_SRRDSN[0] );
		RS_printf("-----------------------------------------\n" );
		RS_printf("IO_SDRAMC[%d].DDR.IO_TMWLVL       = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_TMWLVL );
		RS_printf("-----------------------------------------\n" );
		RS_printf("IO_SDRAMC[%d].DDR.IO_TMGTRNG      = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_TMGTRNG );
		RS_printf("-----------------------------------------\n" );
		RS_printf("IO_SDRAMC[%d].DDR.IO_TMRDS        = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_TMRDS );
		RS_printf("-----------------------------------------\n" );
		RS_printf("IO_SDRAMC[%d].DDR.IO_TMWDE        = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_TMWDE );
		RS_printf("-----------------------------------------\n" );
		RS_printf("IO_SDRAMC[%d].DDR.IO_TMRDE        = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_TMRDE );
		RS_printf("-----------------------------------------\n" );
		RS_printf("IO_SDRAMC[%d].DDR.IO_DIAWDE[0]    = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_DIAWDE[0] );
		RS_printf("-----------------------------------------\n" );
		RS_printf("IO_SDRAMC[%d].DDR.IO_DIARDE[0]    = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_DIARDE[0] );
		RS_printf("-----------------------------------------\n" );
		RS_printf("IO_SDRAMC[%d].DDR.IO_TRWDEPB[0]   = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_TRWDEPB[0] );
		RS_printf("-----------------------------------------\n" );
		RS_printf("IO_SDRAMC[%d].DDR.IO_TRRDEPB[0]   = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_TRRDEPB[0] );
		RS_printf("-----------------------------------------\n" );
		RS_printf("IO_SDRAMC[%d].DDR.IO_SRWDEI0[0]   = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_SRWDEI0[0] );
		RS_printf("-----------------------------------------\n" );
		RS_printf("IO_SDRAMC[%d].DDR.IO_SRWDEI1[0]   = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_SRWDEI1[0] );
		RS_printf("-----------------------------------------\n" );
		RS_printf("IO_SDRAMC[%d].DDR.IO_SRWDEIM[0]   = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_SRWDEIM[0] );
		RS_printf("-----------------------------------------\n" );
		RS_printf("IO_SDRAMC[%d].DDR.IO_SRRDEI0[0]   = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_SRRDEI0[0] );
		RS_printf("-----------------------------------------\n" );
		RS_printf("IO_SDRAMC[%d].DDR.IO_SRRDEI1[0]   = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_SRRDEI1[0] );
		RS_printf("-----------------------------------------\n" );
		RS_printf("IO_SDRAMC[%d].DDR.IO_SRRDEIM[0]   = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_SRRDEIM[0] );
		RS_printf("-----------------------------------------\n" );
		RS_printf("IO_SDRAMC[%d].DDR.IO_SRWDEDQS0[0] = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_SRWDEDQS0[0] );
		RS_printf("-----------------------------------------\n" );
		RS_printf("IO_SDRAMC[%d].DDR.IO_SRRDEDQS0[0] = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_SRRDEDQS0[0] );
		RS_printf("-----------------------------------------\n" );
		RS_printf("IO_SDRAMC[%d].DDR.IO_TTRWDEI      = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_TTRWDEI );
		RS_printf("IO_SDRAMC[%d].DDR.IO_TTDTPS       = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_TTDTPS );
		RS_printf("IO_SDRAMC[%d].DDR.IO_SDRAMSDDRI   = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_SDRAMSDDRI );
		RS_printf("IO_SDRAMC[%d].DDR.IO_NASMR1       = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_NASMR1 );
		RS_printf("IO_SDRAMC[%d].DDR.IO_NASMR2       = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_NASMR2 );
		RS_printf("-----------------------------------------\n" );
		RS_printf("IO_SDRAMC[%d].DDR.IO_DICATC       = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_DICATC );
		RS_printf("IO_SDRAMC[%d].DDR.IO_DICATPI      = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_DICATPI );
		RS_printf("IO_SDRAMC[%d].DDR.IO_TRCATC       = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_TRCATC );
		RS_printf("IO_SDRAMC[%d].DDR.IO_TRCATI       = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_TRCATI );
		RS_printf("IO_SDRAMC[%d].DDR.IO_SRCATCO      = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_SRCATCO );
		RS_printf("IO_SDRAMC[%d].DDR.IO_SRCATI[0]    = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_SRCATI[0] );
		RS_printf("IO_SDRAMC[%d].DDR.IO_SRCATCH      = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_SRCATCH );
		RS_printf("IO_SDRAMC[%d].DDR.IO_SRCATCLK     = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_SRCATCLK );
		RS_printf("IO_SDRAMC[%d].DDR.IO_TMCATS       = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_TMCATS );
		RS_printf("IO_SDRAMC[%d].DDR.IO_TMCATLD[0]   = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_TMCATLD[0] );
		RS_printf("IO_SDRAMC[%d].DDR.IO_TMCATILD     = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_TMCATILD );
		RS_printf("IO_SDRAMC[%d].DDR.IO_CAPCANTD     = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_CAPCANTD );
		RS_printf("IO_SDRAMC[%d].DDR.IO_CAPCAPBTD    = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_CAPCAPBTD );
		RS_printf("IO_SDRAMC[%d].DDR.IO_CAPCATMS     = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_CAPCATMS );
		RS_printf("IO_SDRAMC[%d].DDR.IO_SRRWTTEF     = %x\n", i, (unsigned int)&IO_SDRAMC[i].DDR.IO_SRRWTTEF );
		RS_printf("\n");
	}
#endif
}

DdrTest *ddr_test_new()
{
	DdrTest *self = g_object_new(DDR_TYPE_TEST, NULL);
	return self;
}
