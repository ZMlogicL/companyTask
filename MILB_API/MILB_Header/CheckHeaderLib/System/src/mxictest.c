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
#include "mxictest.h"


G_DEFINE_TYPE(Mxic, mxic_test, G_TYPE_OBJECT);

#define MXIC_TEST_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o),MXIC_TYPE_TEST, MxicPrivate));


struct _MxicPrivate
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
static void mxic_test_class_init(MxicClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(MxicPrivate));

	AbsHeaderTestClass *absClass =  ABS_HEADER_TEST_CALSS(klass);
	absClass->run = run_od;
}

static void mxic_test_init(Mxic *self)
{
	MxicPrivate *priv = MXIC_TEST_GET_PRIVATE(self);

}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(mxic_test_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	Mxic *self = MXIC_TEST(object);
	MxicPrivate *priv = MXIC_TEST_GET_PRIVATE(self);
	G_OBJECT_CLASS(mxic_test_parent_class)->finalize(object);

}

static void run_od(AbsHeaderTest *self)
{

}
/**
 * PUBLIC
 */
/*************************************************************************/
void mxic_test()
{
	RS_printf("MXIC\n");
#if 0
	RS_printf("IO_MXIC0.TMIRST         = %x\n", (unsigned int)&IO_MXIC0.TMIRST );
	RS_printf("IO_MXIC0.TCKEN          = %x\n", (unsigned int)&IO_MXIC0.TCKEN );
	RS_printf("IO_MXIC0.TCKENP         = %x\n", (unsigned int)&IO_MXIC0.TCKENP );
	RS_printf("IO_MXIC0.TMIE           = %x\n", (unsigned int)&IO_MXIC0.TMIE );
	RS_printf("IO_MXIC0.TMIF           = %x\n", (unsigned int)&IO_MXIC0.TMIF );
	RS_printf("IO_MXIC0.TDESTW         = %x\n", (unsigned int)&IO_MXIC0.TDESTW );
	RS_printf("IO_MXIC0.TDESTR         = %x\n", (unsigned int)&IO_MXIC0.TDESTR );
	RS_printf("IO_MXIC0.TCFTRG         = %x\n", (unsigned int)&IO_MXIC0.TCFTRG );
	RS_printf("IO_MXIC0.TCFMD          = %x\n", (unsigned int)&IO_MXIC0.TCFMD );
	RS_printf("IO_MXIC0.TDECLR         = %x\n", (unsigned int)&IO_MXIC0.TDECLR );
	RS_printf("IO_MXIC0.TRVSW          = %x\n", (unsigned int)&IO_MXIC0.TRVSW );

	RS_printf("IO_MXIC0.TAEN           = %x\n", (unsigned int)&IO_MXIC0.TAEN );
	RS_printf("IO_MXIC0.TACPTCW        = %x\n", (unsigned int)&IO_MXIC0.TACPTCW );
	RS_printf("IO_MXIC0.TACPTCR        = %x\n", (unsigned int)&IO_MXIC0.TACPTCR );

	RS_printf("IO_MXIC0.TSMTRG         = %x\n", (unsigned int)&IO_MXIC0.TSMTRG );

	RS_printf("IO_MXIC0.TREGION[0]     = %x\n", (unsigned int)&IO_MXIC0.TREGION[0] );
	RS_printf("IO_MXIC0.TREGION[1]     = %x\n", (unsigned int)&IO_MXIC0.TREGION[1] );
	RS_printf("IO_MXIC0.TREGION[2]     = %x\n", (unsigned int)&IO_MXIC0.TREGION[2] );
	RS_printf("IO_MXIC0.TREGION[3]     = %x\n", (unsigned int)&IO_MXIC0.TREGION[3] );

	RS_printf("IO_MXIC0.TSASETW[0]     = %x\n", (unsigned int)&IO_MXIC0.TSASETW[0] );
	RS_printf("IO_MXIC0.TSASETW[1]     = %x\n", (unsigned int)&IO_MXIC0.TSASETW[1] );
	RS_printf("IO_MXIC0.TSASETW[2]     = %x\n", (unsigned int)&IO_MXIC0.TSASETW[2] );
	RS_printf("IO_MXIC0.TSASETW[3]     = %x\n", (unsigned int)&IO_MXIC0.TSASETW[3] );

	RS_printf("IO_MXIC0.TMTRG          = %x\n", (unsigned int)&IO_MXIC0.TMTRG );
	RS_printf("IO_MXIC0.TMMD           = %x\n", (unsigned int)&IO_MXIC0.TMMD );
	RS_printf("IO_MXIC0.TMONTRG        = %x\n", (unsigned int)&IO_MXIC0.TMONTRG );
	RS_printf("IO_MXIC0.TMUPTRG        = %x\n", (unsigned int)&IO_MXIC0.TMUPTRG );
	RS_printf("IO_MXIC0.TMLIMSEL       = %x\n", (unsigned int)&IO_MXIC0.TMLIMSEL );
	RS_printf("IO_MXIC0.TMLIMIT        = %x\n", (unsigned int)&IO_MXIC0.TMLIMIT );
	RS_printf("IO_MXIC0.TMSEL          = %x\n", (unsigned int)&IO_MXIC0.TMSEL );
	RS_printf("IO_MXIC0.TMCNT[0]       = %x\n", (unsigned int)&IO_MXIC0.TMCNT[0] );
	RS_printf("IO_MXIC0.TMCNT[1]       = %x\n", (unsigned int)&IO_MXIC0.TMCNT[1] );
	RS_printf("IO_MXIC0.TMCNT[2]       = %x\n", (unsigned int)&IO_MXIC0.TMCNT[2] );
	RS_printf("IO_MXIC0.TMCNT[3]       = %x\n", (unsigned int)&IO_MXIC0.TMCNT[3] );

	RS_printf("IO_MXIC0.THSTW[0][0]    = %x\n", (unsigned int)&IO_MXIC0.THSTW[0][0] );
	RS_printf("IO_MXIC0.THSTW[1][0]    = %x\n", (unsigned int)&IO_MXIC0.THSTW[1][0] );
	RS_printf("IO_MXIC0.THSTW[2][0]    = %x\n", (unsigned int)&IO_MXIC0.THSTW[2][0] );
	RS_printf("IO_MXIC0.THSTW[3][0]    = %x\n", (unsigned int)&IO_MXIC0.THSTW[3][0] );

	RS_printf("IO_MXIC0.THSTR[0][0]    = %x\n", (unsigned int)&IO_MXIC0.THSTR[0][0] );
	RS_printf("IO_MXIC0.THSTR[1][0]    = %x\n", (unsigned int)&IO_MXIC0.THSTR[1][0] );
	RS_printf("IO_MXIC0.THSTR[2][0]    = %x\n", (unsigned int)&IO_MXIC0.THSTR[2][0] );
	RS_printf("IO_MXIC0.THSTR[3][0]    = %x\n", (unsigned int)&IO_MXIC0.THSTR[3][0] );

	RS_printf("IO_MXIC0.TMARLP_W_1[0]  = %x\n", (unsigned int)&IO_MXIC0.TMARLP_W_1[0] );
	RS_printf("IO_MXIC0.TMARLP_W_2[0]  = %x\n", (unsigned int)&IO_MXIC0.TMARLP_W_2[0] );
	RS_printf("IO_MXIC0.TMARLP_W_3[0]  = %x\n", (unsigned int)&IO_MXIC0.TMARLP_W_3[0] );
	RS_printf("IO_MXIC0.TMARLP_W_4[0]  = %x\n", (unsigned int)&IO_MXIC0.TMARLP_W_4[0] );

	RS_printf("IO_MXIC0.TMARLP_R_1[0]  = %x\n", (unsigned int)&IO_MXIC0.TMARLP_R_1[0] );
	RS_printf("IO_MXIC0.TMARLP_R_2[0]  = %x\n", (unsigned int)&IO_MXIC0.TMARLP_R_2[0] );
	RS_printf("IO_MXIC0.TMARLP_R_3[0]  = %x\n", (unsigned int)&IO_MXIC0.TMARLP_R_3[0] );
	RS_printf("IO_MXIC0.TMARLP_R_4[0]  = %x\n", (unsigned int)&IO_MXIC0.TMARLP_R_4[0] );

	RS_printf("IO_MXIC0.TRMCW[0]       = %x\n", (unsigned int)&IO_MXIC0.TRMCW[0] );
	RS_printf("IO_MXIC0.TRMCR[0]       = %x\n", (unsigned int)&IO_MXIC0.TRMCR[0] );

	RS_printf("IO_MXIC0.TLVLW1[0]      = %x\n", (unsigned int)&IO_MXIC0.TLVLW1[0] );
	RS_printf("IO_MXIC0.TLVLW1[1]      = %x\n", (unsigned int)&IO_MXIC0.TLVLW1[1] );
	RS_printf("IO_MXIC0.TLVLW1[2]      = %x\n", (unsigned int)&IO_MXIC0.TLVLW1[2] );
	RS_printf("IO_MXIC0.TLVLW1[3]      = %x\n", (unsigned int)&IO_MXIC0.TLVLW1[3] );

	RS_printf("IO_MXIC0.TLVLW2[0]      = %x\n", (unsigned int)&IO_MXIC0.TLVLW2[0] );
	RS_printf("IO_MXIC0.TLVLW2[1]      = %x\n", (unsigned int)&IO_MXIC0.TLVLW2[1] );
	RS_printf("IO_MXIC0.TLVLW2[2]      = %x\n", (unsigned int)&IO_MXIC0.TLVLW2[2] );
	RS_printf("IO_MXIC0.TLVLW2[3]      = %x\n", (unsigned int)&IO_MXIC0.TLVLW2[3] );

	RS_printf("IO_MXIC0.TLVLW3[0]      = %x\n", (unsigned int)&IO_MXIC0.TLVLW3[0] );
	RS_printf("IO_MXIC0.TLVLW3[1]      = %x\n", (unsigned int)&IO_MXIC0.TLVLW3[1] );
	RS_printf("IO_MXIC0.TLVLW3[2]      = %x\n", (unsigned int)&IO_MXIC0.TLVLW3[2] );
	RS_printf("IO_MXIC0.TLVLW3[3]      = %x\n", (unsigned int)&IO_MXIC0.TLVLW3[3] );

	RS_printf("IO_MXIC0.TLVLW4[0]      = %x\n", (unsigned int)&IO_MXIC0.TLVLW4[0] );
	RS_printf("IO_MXIC0.TLVLW4[1]      = %x\n", (unsigned int)&IO_MXIC0.TLVLW4[1] );
	RS_printf("IO_MXIC0.TLVLW4[2]      = %x\n", (unsigned int)&IO_MXIC0.TLVLW4[2] );
	RS_printf("IO_MXIC0.TLVLW4[3]      = %x\n", (unsigned int)&IO_MXIC0.TLVLW4[3] );

	RS_printf("IO_MXIC0.TLVLR1[0]      = %x\n", (unsigned int)&IO_MXIC0.TLVLR1[0] );
	RS_printf("IO_MXIC0.TLVLR1[1]      = %x\n", (unsigned int)&IO_MXIC0.TLVLR1[1] );
	RS_printf("IO_MXIC0.TLVLR1[2]      = %x\n", (unsigned int)&IO_MXIC0.TLVLR1[2] );
	RS_printf("IO_MXIC0.TLVLR1[3]      = %x\n", (unsigned int)&IO_MXIC0.TLVLR1[3] );

	RS_printf("IO_MXIC0.TLVLR2[0]      = %x\n", (unsigned int)&IO_MXIC0.TLVLR2[0] );
	RS_printf("IO_MXIC0.TLVLR2[1]      = %x\n", (unsigned int)&IO_MXIC0.TLVLR2[1] );
	RS_printf("IO_MXIC0.TLVLR2[2]      = %x\n", (unsigned int)&IO_MXIC0.TLVLR2[2] );
	RS_printf("IO_MXIC0.TLVLR2[3]      = %x\n", (unsigned int)&IO_MXIC0.TLVLR2[3] );

	RS_printf("IO_MXIC0.TLVLR3[0]      = %x\n", (unsigned int)&IO_MXIC0.TLVLR3[0] );
	RS_printf("IO_MXIC0.TLVLR3[1]      = %x\n", (unsigned int)&IO_MXIC0.TLVLR3[1] );
	RS_printf("IO_MXIC0.TLVLR3[2]      = %x\n", (unsigned int)&IO_MXIC0.TLVLR3[2] );
	RS_printf("IO_MXIC0.TLVLR3[3]      = %x\n", (unsigned int)&IO_MXIC0.TLVLR3[3] );

	RS_printf("IO_MXIC0.TLVLR4[0]      = %x\n", (unsigned int)&IO_MXIC0.TLVLR4[0] );
	RS_printf("IO_MXIC0.TLVLR4[1]      = %x\n", (unsigned int)&IO_MXIC0.TLVLR4[1] );
	RS_printf("IO_MXIC0.TLVLR4[2]      = %x\n", (unsigned int)&IO_MXIC0.TLVLR4[2] );
	RS_printf("IO_MXIC0.TLVLR4[3]      = %x\n", (unsigned int)&IO_MXIC0.TLVLR4[3] );

	RS_printf("IO_MXIC0.TMSTW[0]       = %x\n", (unsigned int)&IO_MXIC0.TMSTW[0] );
	RS_printf("IO_MXIC0.TMSTR[0]       = %x\n", (unsigned int)&IO_MXIC0.TMSTR[0] );

	RS_printf("IO_MXIC0.TSLSW_1[0][0]  = %x\n", (unsigned int)&IO_MXIC0.TSLSW_1[0][0] );
	RS_printf("IO_MXIC0.TSLSW_1[1][0]  = %x\n", (unsigned int)&IO_MXIC0.TSLSW_1[1][0] );
	RS_printf("IO_MXIC0.TSLSW_1[2][0]  = %x\n", (unsigned int)&IO_MXIC0.TSLSW_1[2][0] );
	RS_printf("IO_MXIC0.TSLSW_1[3][0]  = %x\n", (unsigned int)&IO_MXIC0.TSLSW_1[3][0] );
	RS_printf("IO_MXIC0.TSLSW_2[0][0]  = %x\n", (unsigned int)&IO_MXIC0.TSLSW_2[0][0] );
	RS_printf("IO_MXIC0.TSLSW_2[1][0]  = %x\n", (unsigned int)&IO_MXIC0.TSLSW_2[1][0] );
	RS_printf("IO_MXIC0.TSLSW_2[2][0]  = %x\n", (unsigned int)&IO_MXIC0.TSLSW_2[2][0] );
	RS_printf("IO_MXIC0.TSLSW_2[3][0]  = %x\n", (unsigned int)&IO_MXIC0.TSLSW_2[3][0] );
	RS_printf("IO_MXIC0.TSLSW_3[0][0]  = %x\n", (unsigned int)&IO_MXIC0.TSLSW_3[0][0] );
	RS_printf("IO_MXIC0.TSLSW_3[1][0]  = %x\n", (unsigned int)&IO_MXIC0.TSLSW_3[1][0] );
	RS_printf("IO_MXIC0.TSLSW_3[2][0]  = %x\n", (unsigned int)&IO_MXIC0.TSLSW_3[2][0] );
	RS_printf("IO_MXIC0.TSLSW_3[3][0]  = %x\n", (unsigned int)&IO_MXIC0.TSLSW_3[3][0] );
	RS_printf("IO_MXIC0.TSLSW_4[0][0]  = %x\n", (unsigned int)&IO_MXIC0.TSLSW_4[0][0] );
	RS_printf("IO_MXIC0.TSLSW_4[1][0]  = %x\n", (unsigned int)&IO_MXIC0.TSLSW_4[1][0] );
	RS_printf("IO_MXIC0.TSLSW_4[2][0]  = %x\n", (unsigned int)&IO_MXIC0.TSLSW_4[2][0] );
	RS_printf("IO_MXIC0.TSLSW_4[3][0]  = %x\n", (unsigned int)&IO_MXIC0.TSLSW_4[3][0] );

	RS_printf("IO_MXIC0.TSLSR_1[0][0]  = %x\n", (unsigned int)&IO_MXIC0.TSLSR_1[0][0] );
	RS_printf("IO_MXIC0.TSLSR_1[1][0]  = %x\n", (unsigned int)&IO_MXIC0.TSLSR_1[1][0] );
	RS_printf("IO_MXIC0.TSLSR_1[2][0]  = %x\n", (unsigned int)&IO_MXIC0.TSLSR_1[2][0] );
	RS_printf("IO_MXIC0.TSLSR_1[3][0]  = %x\n", (unsigned int)&IO_MXIC0.TSLSR_1[3][0] );
	RS_printf("IO_MXIC0.TSLSR_2[0][0]  = %x\n", (unsigned int)&IO_MXIC0.TSLSR_2[0][0] );
	RS_printf("IO_MXIC0.TSLSR_2[1][0]  = %x\n", (unsigned int)&IO_MXIC0.TSLSR_2[1][0] );
	RS_printf("IO_MXIC0.TSLSR_2[2][0]  = %x\n", (unsigned int)&IO_MXIC0.TSLSR_2[2][0] );
	RS_printf("IO_MXIC0.TSLSR_2[3][0]  = %x\n", (unsigned int)&IO_MXIC0.TSLSR_2[3][0] );
	RS_printf("IO_MXIC0.TSLSR_3[0][0]  = %x\n", (unsigned int)&IO_MXIC0.TSLSR_3[0][0] );
	RS_printf("IO_MXIC0.TSLSR_3[1][0]  = %x\n", (unsigned int)&IO_MXIC0.TSLSR_3[1][0] );
	RS_printf("IO_MXIC0.TSLSR_3[2][0]  = %x\n", (unsigned int)&IO_MXIC0.TSLSR_3[2][0] );
	RS_printf("IO_MXIC0.TSLSR_3[3][0]  = %x\n", (unsigned int)&IO_MXIC0.TSLSR_3[3][0] );
	RS_printf("IO_MXIC0.TSLSR_4[0][0]  = %x\n", (unsigned int)&IO_MXIC0.TSLSR_4[0][0] );
	RS_printf("IO_MXIC0.TSLSR_4[1][0]  = %x\n", (unsigned int)&IO_MXIC0.TSLSR_4[1][0] );
	RS_printf("IO_MXIC0.TSLSR_4[2][0]  = %x\n", (unsigned int)&IO_MXIC0.TSLSR_4[2][0] );
	RS_printf("IO_MXIC0.TSLSR_4[3][0]  = %x\n", (unsigned int)&IO_MXIC0.TSLSR_4[3][0] );

	RS_printf("IO_MXIC0.TGCKEN         = %x\n", (unsigned int)&IO_MXIC0.TGCKEN );
	RS_printf("IO_MXIC0.TGCFMD         = %x\n", (unsigned int)&IO_MXIC0.TGCFMD );

	RS_printf("IO_MXIC0.TGACPTCW       = %x\n", (unsigned int)&IO_MXIC0.TGACPTCW );
	RS_printf("IO_MXIC0.TGACPTCR       = %x\n", (unsigned int)&IO_MXIC0.TGACPTCR );
	RS_printf("IO_MXIC0.TPORTMW        = %x\n", (unsigned int)&IO_MXIC0.TPORTMW );
	RS_printf("IO_MXIC0.TPORTMR        = %x\n", (unsigned int)&IO_MXIC0.TPORTMR );

	RS_printf("IO_MXIC0.TRMCW_GR[0]    = %x\n", (unsigned int)&IO_MXIC0.TRMCW_GR[0] );
	RS_printf("IO_MXIC0.TRMCR_GR[0]    = %x\n", (unsigned int)&IO_MXIC0.TRMCR_GR[0] );
	RS_printf("IO_MXIC0.TMSTW_GR[0]    = %x\n", (unsigned int)&IO_MXIC0.TMSTW_GR[0] );
	RS_printf("IO_MXIC0.TMSTR_GR[0]    = %x\n", (unsigned int)&IO_MXIC0.TMSTR_GR[0] );

	RS_printf("IO_MXIC0.TGSLSW[0]      = %x\n", (unsigned int)&IO_MXIC0.TGSLSW[0] );
	RS_printf("IO_MXIC0.TGSLSW[1]      = %x\n", (unsigned int)&IO_MXIC0.TGSLSW[1] );
	RS_printf("IO_MXIC0.TGSLSW[2]      = %x\n", (unsigned int)&IO_MXIC0.TGSLSW[2] );
	RS_printf("IO_MXIC0.TGSLSW[3]      = %x\n", (unsigned int)&IO_MXIC0.TGSLSW[3] );
	RS_printf("IO_MXIC0.TGSLSW[4]      = %x\n", (unsigned int)&IO_MXIC0.TGSLSW[4] );
	RS_printf("IO_MXIC0.TGSLSW[5]      = %x\n", (unsigned int)&IO_MXIC0.TGSLSW[5] );
	RS_printf("IO_MXIC0.TGSLSW[6]      = %x\n", (unsigned int)&IO_MXIC0.TGSLSW[6] );
	RS_printf("IO_MXIC0.TGSLSW[7]      = %x\n", (unsigned int)&IO_MXIC0.TGSLSW[7] );
	RS_printf("IO_MXIC0.TGSLSR[0]      = %x\n", (unsigned int)&IO_MXIC0.TGSLSR[0] );
	RS_printf("IO_MXIC0.TGSLSR[1]      = %x\n", (unsigned int)&IO_MXIC0.TGSLSR[1] );
	RS_printf("IO_MXIC0.TGSLSR[2]      = %x\n", (unsigned int)&IO_MXIC0.TGSLSR[2] );
	RS_printf("IO_MXIC0.TGSLSR[3]      = %x\n", (unsigned int)&IO_MXIC0.TGSLSR[3] );
	RS_printf("IO_MXIC0.TGSLSR[4]      = %x\n", (unsigned int)&IO_MXIC0.TGSLSR[4] );
	RS_printf("IO_MXIC0.TGSLSR[5]      = %x\n", (unsigned int)&IO_MXIC0.TGSLSR[5] );
	RS_printf("IO_MXIC0.TGSLSR[6]      = %x\n", (unsigned int)&IO_MXIC0.TGSLSR[6] );
	RS_printf("IO_MXIC0.TGSLSR[7]      = %x\n", (unsigned int)&IO_MXIC0.TGSLSR[7] );

	RS_printf("IO_MXIC1.TMIRST         = %x\n", (unsigned int)&IO_MXIC1.TMIRST );
	RS_printf("IO_MXIC2.TMIRST         = %x\n", (unsigned int)&IO_MXIC2.TMIRST );
	RS_printf("IO_MXIC3.TMIRST         = %x\n", (unsigned int)&IO_MXIC3.TMIRST );
	RS_printf("IO_MXIC4.TMIRST         = %x\n", (unsigned int)&IO_MXIC4.TMIRST );
	RS_printf("IO_MXIC5.TMIRST         = %x\n", (unsigned int)&IO_MXIC5.TMIRST );
	RS_printf("IO_MXIC6.TMIRST         = %x\n", (unsigned int)&IO_MXIC6.TMIRST );

	RS_printf(" \n");

/* io_jdsmxic */
	RS_printf("IO_MXIC1_TBL.TSLW_1[0]  = %x\n", (unsigned int)&IO_MXIC1_TBL.TSLW_1[0] );
	RS_printf("IO_MXIC1_TBL.TSLW_1[1]  = %x\n", (unsigned int)&IO_MXIC1_TBL.TSLW_1[1] );
	RS_printf("IO_MXIC1_TBL.TSLW_1[2]  = %x\n", (unsigned int)&IO_MXIC1_TBL.TSLW_1[2] );
	RS_printf("IO_MXIC1_TBL.TSLW_1[3]  = %x\n", (unsigned int)&IO_MXIC1_TBL.TSLW_1[3] );
	RS_printf("IO_MXIC1_TBL.TSLW_2[0]  = %x\n", (unsigned int)&IO_MXIC1_TBL.TSLW_2[0] );
	RS_printf("IO_MXIC1_TBL.TSLW_2[1]  = %x\n", (unsigned int)&IO_MXIC1_TBL.TSLW_2[1] );
	RS_printf("IO_MXIC1_TBL.TSLW_2[2]  = %x\n", (unsigned int)&IO_MXIC1_TBL.TSLW_2[2] );
	RS_printf("IO_MXIC1_TBL.TSLW_2[3]  = %x\n", (unsigned int)&IO_MXIC1_TBL.TSLW_2[3] );
	RS_printf("IO_MXIC1_TBL.TSLW_3[0]  = %x\n", (unsigned int)&IO_MXIC1_TBL.TSLW_3[0] );
	RS_printf("IO_MXIC1_TBL.TSLW_3[1]  = %x\n", (unsigned int)&IO_MXIC1_TBL.TSLW_3[1] );
	RS_printf("IO_MXIC1_TBL.TSLW_3[2]  = %x\n", (unsigned int)&IO_MXIC1_TBL.TSLW_3[2] );
	RS_printf("IO_MXIC1_TBL.TSLW_3[3]  = %x\n", (unsigned int)&IO_MXIC1_TBL.TSLW_3[3] );
	RS_printf("IO_MXIC1_TBL.TSLW_4[0]  = %x\n", (unsigned int)&IO_MXIC1_TBL.TSLW_4[0] );
	RS_printf("IO_MXIC1_TBL.TSLW_4[1]  = %x\n", (unsigned int)&IO_MXIC1_TBL.TSLW_4[1] );
	RS_printf("IO_MXIC1_TBL.TSLW_4[2]  = %x\n", (unsigned int)&IO_MXIC1_TBL.TSLW_4[2] );
	RS_printf("IO_MXIC1_TBL.TSLW_4[3]  = %x\n", (unsigned int)&IO_MXIC1_TBL.TSLW_4[3] );

	RS_printf("IO_MXIC1_TBL.TSLR_1[0]  = %x\n", (unsigned int)&IO_MXIC1_TBL.TSLR_1[0] );
	RS_printf("IO_MXIC1_TBL.TSLR_1[1]  = %x\n", (unsigned int)&IO_MXIC1_TBL.TSLR_1[1] );
	RS_printf("IO_MXIC1_TBL.TSLR_1[2]  = %x\n", (unsigned int)&IO_MXIC1_TBL.TSLR_1[2] );
	RS_printf("IO_MXIC1_TBL.TSLR_1[3]  = %x\n", (unsigned int)&IO_MXIC1_TBL.TSLR_1[3] );
	RS_printf("IO_MXIC1_TBL.TSLR_2[0]  = %x\n", (unsigned int)&IO_MXIC1_TBL.TSLR_2[0] );
	RS_printf("IO_MXIC1_TBL.TSLR_2[1]  = %x\n", (unsigned int)&IO_MXIC1_TBL.TSLR_2[1] );
	RS_printf("IO_MXIC1_TBL.TSLR_2[2]  = %x\n", (unsigned int)&IO_MXIC1_TBL.TSLR_2[2] );
	RS_printf("IO_MXIC1_TBL.TSLR_2[3]  = %x\n", (unsigned int)&IO_MXIC1_TBL.TSLR_2[3] );
	RS_printf("IO_MXIC1_TBL.TSLR_3[0]  = %x\n", (unsigned int)&IO_MXIC1_TBL.TSLR_3[0] );
	RS_printf("IO_MXIC1_TBL.TSLR_3[1]  = %x\n", (unsigned int)&IO_MXIC1_TBL.TSLR_3[1] );
	RS_printf("IO_MXIC1_TBL.TSLR_3[2]  = %x\n", (unsigned int)&IO_MXIC1_TBL.TSLR_3[2] );
	RS_printf("IO_MXIC1_TBL.TSLR_3[3]  = %x\n", (unsigned int)&IO_MXIC1_TBL.TSLR_3[3] );
	RS_printf("IO_MXIC1_TBL.TSLR_4[0]  = %x\n", (unsigned int)&IO_MXIC1_TBL.TSLR_4[0] );
	RS_printf("IO_MXIC1_TBL.TSLR_4[1]  = %x\n", (unsigned int)&IO_MXIC1_TBL.TSLR_4[1] );
	RS_printf("IO_MXIC1_TBL.TSLR_4[2]  = %x\n", (unsigned int)&IO_MXIC1_TBL.TSLR_4[2] );
	RS_printf("IO_MXIC1_TBL.TSLR_4[3]  = %x\n", (unsigned int)&IO_MXIC1_TBL.TSLR_4[3] );

	RS_printf("IO_MXIC2_TBL.TSLW_1[0]  = %x\n", (unsigned int)&IO_MXIC2_TBL.TSLW_1[0] );

	RS_printf("IO_MXIC3_TBL.TSLW_1[0]  = %x\n", (unsigned int)&IO_MXIC3_TBL.TSLW_1[0] );

	RS_printf(" \n");
#endif
}

Mxic *mxic_test_new()
{
	Mxic *self = g_object_new(MXIC_TYPE_TEST, NULL);
	return self;
}
