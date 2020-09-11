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
#include "metest.h"


G_DEFINE_TYPE(MeTest, me_test, G_TYPE_OBJECT);

#define ME_TEST_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o),ME_TYPE_TEST, MeTestPrivate));


struct _MeTestPrivate
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
static void me_test_class_init(MeTestClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(MeTestPrivate));

	AbsHeaderTestClass *absClass =  ABS_HEADER_TEST_CALSS(klass);
	absClass->run = run_od;
}

static void me_test_init(MeTest *self)
{
	MeTestPrivate *priv = ME_TEST_GET_PRIVATE(self);

}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(me_test_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	MeTest *self = ME_TEST(object);
	MeTestPrivate *priv = ME_TEST_GET_PRIVATE(self);
	G_OBJECT_CLASS(me_test_parent_class)->finalize(object);

}

static void run_od(AbsHeaderTest *self)
{

}
/**
 * PUBLIC
 */
/*************************************************************************/
void me_test()
{
#if 0
#define IO_ME	(*IO_ME1)
	volatile struct io_jdsme*	IO_ME1	= (void*)0x28870000;
#endif
	RS_printf("ME\n");
#if 0
	RS_printf("APBBRG\n");
	RS_printf("IO_ME.SRESET     = %x\n", (unsigned int)&IO_ME.SRESET );
	RS_printf("IO_ME.INTMODE    = %x\n", (unsigned int)&IO_ME.INTMODE );
	RS_printf("IO_ME.INTSTATE   = %x\n", (unsigned int)&IO_ME.INTSTATE );
	RS_printf("IO_ME.INTCNTR    = %x\n", (unsigned int)&IO_ME.INTCNTR );
	RS_printf(" \n");

	for ( int i = 0; i < 3; i++ ) {
		RS_printf("PTCNT[ %d ]\n", i );
		RS_printf("IO_ME.PME[ %d ].CR             = %x\n", i, (unsigned int)&IO_ME.PME[ i ].CR );
		RS_printf("IO_ME.PME[ %d ].PTCC           = %x\n", i, (unsigned int)&IO_ME.PME[ i ].PTCC );
		RS_printf("IO_ME.PME[ %d ].PACC           = %x\n", i, (unsigned int)&IO_ME.PME[ i ].PACC );
		RS_printf("IO_ME.PME[ %d ].IRQSC          = %x\n", i, (unsigned int)&IO_ME.PME[ i ].IRQSC );
		RS_printf("IO_ME.PME[ %d ].IRQE           = %x\n", i, (unsigned int)&IO_ME.PME[ i ].IRQE );
		RS_printf("IO_ME.PME[ %d ].MIRQS          = %x\n", i, (unsigned int)&IO_ME.PME[ i ].MIRQS );
		RS_printf("IO_ME.PME[ %d ].PABT_PARAM_MPR = %x\n", i, (unsigned int)&IO_ME.PME[ i ].PABT_PARAM_MPR );
		RS_printf("IO_ME.PME[ %d ].PABT_PARAM_MVR = %x\n", i, (unsigned int)&IO_ME.PME[ i ].PABT_PARAM_MVR );
		RS_printf("IO_ME.PME[ %d ].PABT_PARAM_MVW = %x\n", i, (unsigned int)&IO_ME.PME[ i ].PABT_PARAM_MVW );
		RS_printf("IO_ME.PME[ %d ].PABT_PARAM_PPW = %x\n", i, (unsigned int)&IO_ME.PME[ i ].PABT_PARAM_PPW );
		RS_printf("IO_ME.PME[ %d ].PABT_PARAM_PPR = %x\n", i, (unsigned int)&IO_ME.PME[ i ].PABT_PARAM_PPR );
		RS_printf("IO_ME.PME[ %d ].PABT_PARAM_PSW = %x\n", i, (unsigned int)&IO_ME.PME[ i ].PABT_PARAM_PSW );

		RS_printf(" \n");

		RS_printf("PME[ %d ]\n", i );
		RS_printf("IO_ME.PME[ %d ].SRST             = %x\n", i, (unsigned int)&IO_ME.PME[ i ].SRST );
		RS_printf("IO_ME.PME[ %d ].ACTIVE           = %x\n", i, (unsigned int)&IO_ME.PME[ i ].ACTIVE );
		RS_printf("IO_ME.PME[ %d ].STATE            = %x\n", i, (unsigned int)&IO_ME.PME[ i ].STATE );
		RS_printf("IO_ME.PME[ %d ].MBNUM            = %x\n", i, (unsigned int)&IO_ME.PME[ i ].MBNUM );
		RS_printf("IO_ME.PME[ %d ].INPUTMODE        = %x\n", i, (unsigned int)&IO_ME.PME[ i ].INPUTMODE );
		RS_printf("IO_ME.PME[ %d ].OUTLIMIT         = %x\n", i, (unsigned int)&IO_ME.PME[ i ].OUTLIMIT );
		RS_printf("IO_ME.PME[ %d ].QMBADR           = %x\n", i, (unsigned int)&IO_ME.PME[ i ].QMBADR );
		RS_printf("IO_ME.PME[ %d ].M1BANKNUM        = %x\n", i, (unsigned int)&IO_ME.PME[ i ].M1BANKNUM );
		RS_printf("IO_ME.PME[ %d ].M1ORGMODE[ 0 ]   = %x\n", i, (unsigned int)&IO_ME.PME[ i ].M1ORGMODE[ 0 ] );
		RS_printf("IO_ME.PME[ %d ].M1ORGMODE[ 1 ]   = %x\n", i, (unsigned int)&IO_ME.PME[ i ].M1ORGMODE[ 1 ] );
		RS_printf("IO_ME.PME[ %d ].M1ORGMODE[ 2 ]   = %x\n", i, (unsigned int)&IO_ME.PME[ i ].M1ORGMODE[ 2 ] );
		RS_printf("IO_ME.PME[ %d ].M1ORGMODE[ 3 ]   = %x\n", i, (unsigned int)&IO_ME.PME[ i ].M1ORGMODE[ 3 ] );
		RS_printf("IO_ME.PME[ %d ].M1START          = %x\n", i, (unsigned int)&IO_ME.PME[ i ].M1START );
		RS_printf("IO_ME.PME[ %d ].M1CORRECT        = %x\n", i, (unsigned int)&IO_ME.PME[ i ].M1CORRECT );
		RS_printf("IO_ME.PME[ %d ].M1MC             = %x\n", i, (unsigned int)&IO_ME.PME[ i ].M1MC );
		RS_printf("IO_ME.PME[ %d ].M1SPLT           = %x\n", i, (unsigned int)&IO_ME.PME[ i ].M1SPLT );
		RS_printf("IO_ME.PME[ %d ].M1SKIP           = %x\n", i, (unsigned int)&IO_ME.PME[ i ].M1SKIP );
		RS_printf("IO_ME.PME[ %d ].M1SADSUM         = %x\n", i, (unsigned int)&IO_ME.PME[ i ].M1SADSUM );
		RS_printf("IO_ME.PME[ %d ].M1ADJUST         = %x\n", i, (unsigned int)&IO_ME.PME[ i ].M1ADJUST );
		RS_printf("IO_ME.PME[ %d ].M1PAUSE          = %x\n", i, (unsigned int)&IO_ME.PME[ i ].M1PAUSE );
		RS_printf("IO_ME.PME[ %d ].M1LIMITMV[ 0 ]   = %x\n", i, (unsigned int)&IO_ME.PME[ i ].M1LIMITMV[ 0 ] );
		RS_printf("IO_ME.PME[ %d ].M1LIMITMV[ 1 ]   = %x\n", i, (unsigned int)&IO_ME.PME[ i ].M1LIMITMV[ 1 ] );
		RS_printf("IO_ME.PME[ %d ].M1LIMITMV[ 2 ]   = %x\n", i, (unsigned int)&IO_ME.PME[ i ].M1LIMITMV[ 2 ] );
		RS_printf("IO_ME.PME[ %d ].M1LIMITMV[ 3 ]   = %x\n", i, (unsigned int)&IO_ME.PME[ i ].M1LIMITMV[ 3 ] );
		RS_printf("IO_ME.PME[ %d ].M1LIMITMH[ 0 ]   = %x\n", i, (unsigned int)&IO_ME.PME[ i ].M1LIMITMH[ 0 ] );
		RS_printf("IO_ME.PME[ %d ].M1LIMITMH[ 1 ]   = %x\n", i, (unsigned int)&IO_ME.PME[ i ].M1LIMITMH[ 1 ] );
		RS_printf("IO_ME.PME[ %d ].M1LIMITMH[ 2 ]   = %x\n", i, (unsigned int)&IO_ME.PME[ i ].M1LIMITMH[ 2 ] );
		RS_printf("IO_ME.PME[ %d ].M1LIMITMH[ 3 ]   = %x\n", i, (unsigned int)&IO_ME.PME[ i ].M1LIMITMH[ 3 ] );
		RS_printf("IO_ME.PME[ %d ].M1STORGAVRSAD[ 0 ] = %x\n", i, (unsigned int)&IO_ME.PME[ i ].M1STORGAVRSAD[ 0 ] );
		RS_printf("IO_ME.PME[ %d ].M1STORGAVRSAD[ 1 ] = %x\n", i, (unsigned int)&IO_ME.PME[ i ].M1STORGAVRSAD[ 1 ] );
		RS_printf("IO_ME.PME[ %d ].M1STORGAVRSAD[ 2 ] = %x\n", i, (unsigned int)&IO_ME.PME[ i ].M1STORGAVRSAD[ 2 ] );
		RS_printf("IO_ME.PME[ %d ].M1STORGAVRSAD[ 3 ] = %x\n", i, (unsigned int)&IO_ME.PME[ i ].M1STORGAVRSAD[ 3 ] );
		RS_printf("IO_ME.PME[ %d ].M1STMINAVRSAD[ 0 ] = %x\n", i, (unsigned int)&IO_ME.PME[ i ].M1STMINAVRSAD[ 0 ] );
		RS_printf("IO_ME.PME[ %d ].M1STMINAVRSAD[ 1 ] = %x\n", i, (unsigned int)&IO_ME.PME[ i ].M1STMINAVRSAD[ 1 ] );
		RS_printf("IO_ME.PME[ %d ].M1STMINAVRSAD[ 2 ] = %x\n", i, (unsigned int)&IO_ME.PME[ i ].M1STMINAVRSAD[ 2 ] );
		RS_printf("IO_ME.PME[ %d ].M1STMINAVRSAD[ 3 ] = %x\n", i, (unsigned int)&IO_ME.PME[ i ].M1STMINAVRSAD[ 3 ] );
		RS_printf("IO_ME.PME[ %d ].M1ST_ORG_VXVX[ 0 ] = %x\n", i, (unsigned int)&IO_ME.PME[ i ].M1ST_ORG_VXVX[ 0 ] );
		RS_printf("IO_ME.PME[ %d ].M1ST_ORG_VXVX[ 1 ] = %x\n", i, (unsigned int)&IO_ME.PME[ i ].M1ST_ORG_VXVX[ 2 ] );
		RS_printf("IO_ME.PME[ %d ].M1ST_ORG_VXVX[ 2 ] = %x\n", i, (unsigned int)&IO_ME.PME[ i ].M1ST_ORG_VXVX[ 3 ] );
		RS_printf("IO_ME.PME[ %d ].M1ST_ORG_VXVX[ 3 ] = %x\n", i, (unsigned int)&IO_ME.PME[ i ].M1ST_ORG_VXVX[ 4 ] );
		RS_printf("IO_ME.PME[ %d ].PMBUF_CTL        = %x\n", i, (unsigned int)&IO_ME.PME[ i ].PMBUF_CTL );
		RS_printf("IO_ME.PME[ %d ].COREMODE         = %x\n", i, (unsigned int)&IO_ME.PME[ i ].COREMODE );
		RS_printf("IO_ME.PME[ %d ].CNCL             = %x\n", i, (unsigned int)&IO_ME.PME[ i ].CNCL );
		RS_printf("IO_ME.PME[ %d ].VOUT_FMT         = %x\n", i, (unsigned int)&IO_ME.PME[ i ].VOUT_FMT );
		RS_printf("IO_ME.PME[ %d ].ORGAVR[ 0 ]      = %x\n", i, (unsigned int)&IO_ME.PME[ i ].ORGAVR[ 0 ] );
		RS_printf("IO_ME.PME[ %d ].ORGAVR[ 1 ]      = %x\n", i, (unsigned int)&IO_ME.PME[ i ].ORGAVR[ 1 ] );
		RS_printf("IO_ME.PME[ %d ].ORGAVR[ 2 ]      = %x\n", i, (unsigned int)&IO_ME.PME[ i ].ORGAVR[ 2 ] );
		RS_printf("IO_ME.PME[ %d ].ORGAVR[ 3 ]      = %x\n", i, (unsigned int)&IO_ME.PME[ i ].ORGAVR[ 3 ] );
		RS_printf(" \n");
	}

	RS_printf("RMCIF\n");
	RS_printf("IO_ME.CLKENB1          = %x\n", (unsigned int)&IO_ME.CLKENB1 );
	RS_printf("IO_ME.CLKENB4          = %x\n", (unsigned int)&IO_ME.CLKENB4 );
	RS_printf("IO_ME.CLKACT1          = %x\n", (unsigned int)&IO_ME.CLKACT1 );
	RS_printf("IO_ME.CLKACT4          = %x\n", (unsigned int)&IO_ME.CLKACT4 );
	RS_printf("IO_ME.PF_SIZE          = %x\n", (unsigned int)&IO_ME.PF_SIZE );
	RS_printf("IO_ME.WRITE_STATE      = %x\n", (unsigned int)&IO_ME.WRITE_STATE );
	RS_printf("IO_ME.ABT_TYPE         = %x\n", (unsigned int)&IO_ME.ABT_TYPE );
	RS_printf("IO_ME.BANK_TBL_PVEC    = %x\n", (unsigned int)&IO_ME.BANK_TBL_PVEC );
	RS_printf("IO_ME.BANK_TBL_8PELREF = %x\n", (unsigned int)&IO_ME.BANK_TBL_8PELREF );
	RS_printf("IO_ME.BANK_TBL_8PEL    = %x\n", (unsigned int)&IO_ME.BANK_TBL_8PEL );
	RS_printf("IO_ME.PF1_ON           = %x\n", (unsigned int)&IO_ME.PF1_ON );
	RS_printf("IO_ME.PF1_INISIZE      = %x\n", (unsigned int)&IO_ME.PF1_INISIZE );
	RS_printf("IO_ME.PF1_TBSEL        = %x\n", (unsigned int)&IO_ME.PF1_TBSEL );
	RS_printf("IO_ME.PF1_PMENUM       = %x\n", (unsigned int)&IO_ME.PF1_PMENUM );
	RS_printf("IO_ME.PF1_START        = %x\n", (unsigned int)&IO_ME.PF1_START );
	RS_printf("IO_ME.PF1_CLEAR        = %x\n", (unsigned int)&IO_ME.PF1_CLEAR );
	RS_printf("IO_ME.PF1_PB0_STBKNO   = %x\n", (unsigned int)&IO_ME.PF1_PB0_STBKNO );
	RS_printf("IO_ME.PF1_PB0_STBKNO2  = %x\n", (unsigned int)&IO_ME.PF1_PB2_STBKNO );
	RS_printf("IO_ME.PF1_PFB0         = %x\n", (unsigned int)&IO_ME.PF1_PFB0 );
	RS_printf("IO_ME.PF1_PFB2         = %x\n", (unsigned int)&IO_ME.PF1_PFB2 );
	RS_printf("IO_ME.PREVSZ_3DNRME    = %x\n", (unsigned int)&IO_ME.PREVSZ_3DNRME );
	RS_printf("IO_ME.MRGN_3DNRME      = %x\n", (unsigned int)&IO_ME.MRGN_3DNRME );
	RS_printf("IO_ME.SHIFT_3DNRME     = %x\n", (unsigned int)&IO_ME.SHIFT_3DNRME );
	RS_printf("IO_ME.CMD_RST          = %x\n", (unsigned int)&IO_ME.CMD_RST );
	RS_printf("IO_ME.M1_GBO           = %x\n", (unsigned int)&IO_ME.M1_GBO );
	RS_printf("IO_ME.M1_GBS           = %x\n", (unsigned int)&IO_ME.M1_GBS );
	RS_printf("IO_ME.M1_GLSS          = %x\n", (unsigned int)&IO_ME.M1_GLSS );
	RS_printf("IO_ME.PREV_GBO         = %x\n", (unsigned int)&IO_ME.PREV_GBO );
	RS_printf("IO_ME.PREV_GBS         = %x\n", (unsigned int)&IO_ME.PREV_GBS );
	RS_printf("IO_ME.PREV_GLSS        = %x\n", (unsigned int)&IO_ME.PREV_GLSS );
	RS_printf("IO_ME.PVEC_GBO         = %x\n", (unsigned int)&IO_ME.PVEC_GBO );
	RS_printf("IO_ME.PVEC_GBS         = %x\n", (unsigned int)&IO_ME.PVEC_GBS );
	RS_printf("IO_ME.WBUF             = %x\n", (unsigned int)&IO_ME.WBUF );
	RS_printf("IO_ME.RBUF[ 0 ]        = %x\n", (unsigned int)&IO_ME.RBUF[ 0 ] );
	RS_printf("IO_ME.RBUF[ 1 ]        = %x\n", (unsigned int)&IO_ME.RBUF[ 1 ] );
	RS_printf("IO_ME.AXI_CNTL_SET     = %x\n", (unsigned int)&IO_ME.AXI_CNTL_SET );
	RS_printf("IO_ME.AXI_ERR_CLR      = %x\n", (unsigned int)&IO_ME.AXI_ERR_CLR );
	RS_printf("IO_ME.AXI_ERR_STATUS   = %x\n", (unsigned int)&IO_ME.AXI_ERR_STATUS );
	RS_printf("IO_ME.CUR_RDMA_QU_STAT = %x\n", (unsigned int)&IO_ME.CUR_RDMA_QU_STAT );
	RS_printf("IO_ME.PRE_RDMA_QU_STAT = %x\n", (unsigned int)&IO_ME.PRE_RDMA_QU_STAT );
	RS_printf("IO_ME.VEC_WDMA_QU_STAT = %x\n", (unsigned int)&IO_ME.VEC_WDMA_QU_STAT );
	RS_printf(" \n");
#endif
}

MeTest *me_test_new()
{
	MeTest *self = g_object_new(ME_TYPE_TEST, NULL);
	return self;
}
