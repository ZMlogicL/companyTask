/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-03
*@author              :申雨
*@brief               :sns 索喜rtos
*@rely                :glib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年09月开始开发
*/


#include <stdio.h>
#include <stdlib.h>
#include "CheckHeaderMain.h"
#include "milb.h"
#include "kchiptop3.h"
#if 0
#include "arm.h"
#include "chiptop.h"
#include "exstop.h"
#include "jdsb2r.h"
#include "jdscnr.h"
#include "jdsdisp.h"
#include "jdsela.h"
#include "jdsfpt.h"
#include "jdsiip.h"
#include "jdsimg.h"
#include "jdsjpgdec.h"
#include "jdsjpgenc.h"
#include "jdsltm.h"
#include "jdsmxic.h"
#include "jdspro.h"
#include "jdsr2y.h"
#include "jdsraw.h"
#include "jdsshdr.h"
#include "jdsxch.h"
#include "jmilaum.h"
#include "jmilhdmi.h"
#include "jmlbmh.h"
#include "jsrlot.h"
#include "peripheral.h"
#include "slimbus.h"
#include "sdramc.h"
#include "uart_csio.h"
#include "jdsme.h"
#endif
#include "protest7.h"

G_DEFINE_TYPE(ProTest7, pro_test7, G_TYPE_OBJECT);

#define PRO_TEST7_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o), PRO_TYPE_TEST7, ProTest7Private));


struct _ProTest7Private
{
	 gint preserved;
};
/**
 * DECLS
 */
static void 	dispose_od(GObject *object);
static void 	finalize_od(GObject *object);
/**
 * IMPL
 */
static void pro_test7_class_init(ProTest7Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);

	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(ProTest7Private));
}

static void pro_test7_init(ProTest7 *self)
{
	ProTest7Private *priv = PRO_TEST7_GET_PRIVATE(self);

	priv->preserved = 0;
}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(pro_test7_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	G_OBJECT_CLASS(pro_test7_parent_class)->finalize(object);
}
/*
 * PUBLIC
 */
void pro_test7(ProTest7 *self, EProBlockType type, IoPro ioPro)
{
#if 0
#ifdef D_ENABLE_IO_PRO_B2B_PIPE_3	/** B2B Unit(pipe[3]) **/
	if(type == CheckHeaderMain_E_PRO_BLOCK_TYPE_B2B3) {
		// B2BTOP
		CheckHeaderMain_RS_PRINTF("b2b[3]\n");
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].b2btop.sr           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.b2btop.sr );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].b2btop.clkstp       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.b2btop.clkstp );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].b2btop.b2btopctl1   = %x\n", (kuint)&ioPro.imgPipe[2].b2b.b2btop.b2btopctl1 );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].b2btop.b2btopctl2   = %x\n", (kuint)&ioPro.imgPipe[2].b2b.b2btop.b2btopctl2 );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].b2btop.intmon1      = %x\n", (kuint)&ioPro.imgPipe[2].b2b.b2btop.intmon1 );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].b2btop.intmon2      = %x\n", (kuint)&ioPro.imgPipe[2].b2b.b2btop.intmon2 );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].b2btop.intctl       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.b2btop.intctl );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].b2btop.vhdintenb    = %x\n", (kuint)&ioPro.imgPipe[2].b2b.b2btop.vhdintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].b2btop.vhdintflg    = %x\n", (kuint)&ioPro.imgPipe[2].b2b.b2btop.vhdintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].b2btop.vhset        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.b2btop.vhset );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].b2btop.vmivadr      = %x\n", (kuint)&ioPro.imgPipe[2].b2b.b2btop.vmivadr );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].b2btop.vmihadr      = %x\n", (kuint)&ioPro.imgPipe[2].b2b.b2btop.vmihadr );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].b2btop.hmihadr      = %x\n", (kuint)&ioPro.imgPipe[2].b2b.b2btop.hmihadr );
		// PG
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pg.pgtrg            = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pg.pgtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pg.pgctl            = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pg.pgctl );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pg.pgvw             = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pg.pgvw );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pg.pghw             = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pg.pghw );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pg.pgvblnk          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pg.pgvblnk );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pg.pghblnk          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pg.pghblnk );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pg.pgvdhdblnk       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pg.pgvdhdblnk );
		// PGAIN1
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pgain1.pgaintrg     = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pgain1.pgaintrg );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pgain1.pgainr       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pgain1.pgainr );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pgain1.pgaingr      = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pgain1.pgaingr );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pgain1.pgaingb      = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pgain1.pgaingb );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pgain1.pgainb       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pgain1.pgainb );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pgain1.pofsr        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pgain1.pofsr );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pgain1.pofsgr       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pgain1.pofsgr );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pgain1.pofsgb       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pgain1.pofsgb );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pgain1.pofsb        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pgain1.pofsb );
		// PZSFTA1
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pzsfta1.pzsfttrg    = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pzsfta1.pzsfttrg );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pzsfta1.pzofst      = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pzsfta1.pzofst );
		// ELF
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.elftrg          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.elftrg );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.nsltrg          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.nsltrg );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.elfpaen         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.elfpaen );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.elfgwp          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.elfgwp );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.elfgws          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.elfgws );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.elfwp           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.elfwp );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.elfws           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.elfws );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.elfctl          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.elfctl );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.elfzp           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.elfzp );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.elfl            = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.elfl );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.anbor           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.anbor );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.anbkr           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.anbkr );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.anbdr           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.anbdr );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.anbog           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.anbog );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.anbkg           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.anbkg );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.anbdg           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.anbdg );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.anbob           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.anbob );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.anbkb           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.anbkb );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.anbdb           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.anbdb );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.lgtw            = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.lgtw );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.lgt             = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.lgt );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.lgte            = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.lgte );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.edg2anba        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.edg2anba );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.edgscla         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.edgscla );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.edg2anbb        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.edg2anbb );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.edgsclb         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.edgsclb );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.edg2anbc        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.edg2anbc );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.edgsclc         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.edgsclc );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.efth            = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.efth );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.lfth            = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.lfth );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.elcome          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.elcome );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.elcomen         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.elcomen );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.a1s5e           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.a1s5e );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.a1s5l1          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.a1s5l1 );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.a1s5l2          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.a1s5l2 );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.a1s5l3          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.a1s5l3 );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.a1s5l4          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.a1s5l4 );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.nr1s5rgb        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.nr1s5rgb );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.ns1s5lm         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.ns1s5lm );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.a5s9e           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.a5s9e );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.a5s9l1          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.a5s9l1 );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.a5s9l2          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.a5s9l2 );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.a5s9l3          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.a5s9l3 );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.a5s9l4          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.a5s9l4 );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.nr5s9rgb        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.nr5s9rgb );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.ns5s9lm         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.ns5s9lm );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.fs9w            = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.fs9w );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.fs9yc           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.fs9yc );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.fastr           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.fastr );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.crvaf           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.crvaf );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.fcrvabtof       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.fcrvabtof );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.fcrvabtga       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.fcrvabtga );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.fcrvabtbd       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.fcrvabtbd );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.fcrvabtcp       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.fcrvabtcp );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.fyabtga         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.fyabtga );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.fyabtga         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.fyabtga );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.fyabtclp        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.fyabtclp );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.faehh           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.faehh );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.fbstr           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.fbstr );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.crvbf           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.crvbf );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.fcrvbbtof       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.fcrvbbtof );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.fcrvbbtga       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.fcrvbbtga );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.fcrvbbtbd       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.fcrvbbtbd );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.fcrvbbtcp       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.fcrvbbtcp );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.fybbtga         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.fybbtga );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.fybbtbd         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.fybbtbd );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.fybbtclp        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.fybbtclp );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.fbehh           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.fbehh );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.elfmnnrrl       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.elfmnnrrl );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.elfmnnrgl       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.elfmnnrgl );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.elfmnnrbl       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.elfmnnrbl );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.elfafnr         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.elfafnr );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.zeladcmd        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zeladcmd );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.zanbor          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zanbor );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.zanbkr          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zanbkr );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.zanbdr          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zanbdr );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.zanbog          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zanbog );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.zanbkg          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zanbkg );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.zanbdg          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zanbdg );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.zanbdb          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zanbdb );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.zanbkb          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zanbkb );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.zanbkb          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zanbkb );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.zanbdb          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zanbdb );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.zlgtw           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zlgtw );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.zlgt            = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zlgt );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.zlgte           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zlgte );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.zedg2anba       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zedg2anba );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.zedgscla        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zedgscla );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.zedg2anbb       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zedg2anbb );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.zedgsclb        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zedgsclb );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.zalnge          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zalnge );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.zalng           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zalng );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.zlfth           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zlfth );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.zlcome          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zlcome );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.zlcomen         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zlcomen );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].elf.znslnglm        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.znslnglm );
		// PZSFTA2
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pzsfta2.pzsfttrg    = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pzsfta2.pzsfttrg );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pzsfta2.pzofst      = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pzsfta2.pzofst );
		// PZSFTA2A
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pzsfta2a.pzsfttrg   = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pzsfta2a.pzsfttrg );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pzsfta2a.pzofst     = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pzsfta2a.pzofst );
		// FSHD
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].fshd.fshdtrg        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.fshdtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].fshd.fshdpaen       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.fshdpaen );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].fshd.fshdctl        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.fshdctl );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].fshd.fshdv          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.fshdv );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].fshd.fshdh          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.fshdh );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].fshd.fshdvw         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.fshdvw );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].fshd.fshdhw         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.fshdhw );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].fshd.fshdhwph       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.fshdhwph );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].fshd.fshdbc         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.fshdbc );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].fshd.fsul1          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.fsul1 );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].fshd.fsul2          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.fsul2 );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].fshd.fsctl          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.fsctl );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].fshd.fssubpr        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.fssubpr );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].fshd.fssubsp        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.fssubsp );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].fshd.fssubdr        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.fssubdr );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].fshd.fssubst        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.fssubst );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].fshd.fsa1           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.fsa1 );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].fshd.fsa2           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.fsa2 );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].fshd.csctl1         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.csctl1 );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].fshd.csctl2         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.csctl2 );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].fshd.cstblst        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.cstblst );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].fshd.cstbls1        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.cstbls1 );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].fshd.cstbls2        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.cstbls2 );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].fshd.cshdd          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.cshdd );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].fshd.cshdoa         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.cshdoa );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].fshd.csa1           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.csa1 );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].fshd.csa2           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.csa2 );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].fshd.fswric         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.fswric );
		// PGAIN2
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pgain2.pgaintrg     = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pgain2.pgaintrg );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pgain2.pgainr       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pgain2.pgainr );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pgain2.pgaingr      = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pgain2.pgaingr );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pgain2.pgaingb      = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pgain2.pgaingb );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pgain2.pgainb       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pgain2.pgainb );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pgain2.pofsr        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pgain2.pofsr );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pgain2.pofsgr       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pgain2.pofsgr );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pgain2.pofsgb       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pgain2.pofsgb );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pgain2.pofsb        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pgain2.pofsb );
		// P2M-0
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].p2m0.p2mtrg         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[0].p2mtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].p2m0.p2mpaen        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[0].p2mpaen );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].p2m0.p2mctl         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[0].p2mctl );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].p2m0.p2mofs         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[0].p2mofs );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].p2m0.pbsft          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[0].pbsft );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].p2m0.pclph          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[0].pclph );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].p2m0.ptrmv          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[0].ptrmv );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].p2m0.ptrmh          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[0].ptrmh );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].p2m0.ptrmvw         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[0].ptrmvw );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].p2m0.ptrmhw         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[0].ptrmhw );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].p2m0.ptrmxvcyc      = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[0].ptrmxvcyc );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].p2m0.ptrmxhcyc      = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[0].ptrmxhcyc );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].p2m0.ptrmxven       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[0].ptrmxven );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].p2m0.ptrmxhen       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[0].ptrmxhen );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].p2m0.p2mmir         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[0].p2mmir );
		// P2M-1
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].p2m1.p2mtrg         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[1].p2mtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].p2m1.p2mpaen        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[1].p2mpaen );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].p2m1.p2mctl         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[1].p2mctl );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].p2m1.p2mofs         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[1].p2mofs );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].p2m1.pbsft          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[1].pbsft );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].p2m1.pclph          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[1].pclph );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].p2m1.ptrmv          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[1].ptrmv );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].p2m1.ptrmh          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[1].ptrmh );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].p2m1.ptrmvw         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[1].ptrmvw );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].p2m1.ptrmhw         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[1].ptrmhw );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].p2m1.ptrmxvcyc      = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[1].ptrmxvcyc );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].p2m1.ptrmxhcyc      = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[1].ptrmxhcyc );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].p2m1.ptrmxven       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[1].ptrmxven );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].p2m1.ptrmxhen       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[1].ptrmxhen );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].p2m1.p2mmir         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[1].p2mmir );
		// PWCH-0
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pwch0.pwchtrg       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pwch[0].pwchtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pwch0.pws           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pwch[0].pws );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pwch0.pwaxctl       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pwch[0].pwaxctl );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pwch0.pwchctl       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pwch[0].pwchctl );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pwch0.pwchintenb    = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pwch[0].pwchintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pwch0.pwchintflg    = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pwch[0].pwchintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pwch0.pwchbresp     = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pwch[0].pwchbresp );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pwch0.pwsa          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pwch[0].pwsa );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pwch0.pwlsize       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pwch[0].pwlsize );
		// PWCH-1
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pwch1.pwchtrg       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pwch[1].pwchtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pwch1.pws           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pwch[1].pws );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pwch1.pwaxctl       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pwch[1].pwaxctl );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pwch1.pwchctl       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pwch[1].pwchctl );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pwch1.pwchintenb    = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pwch[1].pwchintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pwch1.pwchintflg    = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pwch[1].pwchintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pwch1.pwchbresp     = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pwch[1].pwchbresp );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pwch1.pwsa          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pwch[1].pwsa );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].pwch1.pwlsize       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pwch[1].pwlsize );
		// M2P-0
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].m2p0.m2ptrg         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[0].m2ptrg );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].m2p0.m2ppaen        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[0].m2ppaen );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].m2p0.m2pctl         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[0].m2pctl );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].m2p0.m2pbsft        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[0].m2pbsft );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].m2p0.m2pofs         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[0].m2pofs );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].m2p0.m2pclip        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[0].m2pclip );
		// M2P-1
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].m2p1.m2ptrg         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[1].m2ptrg );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].m2p1.m2ppaen        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[1].m2ppaen );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].m2p1.m2pctl         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[1].m2pctl );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].m2p1.m2pbsft        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[1].m2pbsft );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].m2p1.m2pofs         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[1].m2pofs );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].m2p1.m2pclip        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[1].m2pclip );
		// M2P-2
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].m2p2.m2ptrg         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[2].m2ptrg );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].m2p2.m2ppaen        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[2].m2ppaen );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].m2p2.m2pctl         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[2].m2pctl );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].m2p2.m2pbsft        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[2].m2pbsft );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].m2p2.m2pofs         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[2].m2pofs );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].m2p2.m2pclip        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[2].m2pclip );
		// M2P-3
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].m2p3.m2ptrg         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[3].m2ptrg );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].m2p3.m2ppaen        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[3].m2ppaen );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].m2p3.m2pctl         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[3].m2pctl );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].m2p3.m2pbsft        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[3].m2pbsft );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].m2p3.m2pofs         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[3].m2pofs );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].m2p3.m2pclip        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[3].m2pclip );
		// PRCH-0
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch0.prchtrg       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[0].prchtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch0.prchctl       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[0].prchctl );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch0.prchrs        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[0].prchrs );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch0.praxctl       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[0].praxctl );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch0.prchintenb    = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[0].prchintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch0.prchintflg    = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[0].prchintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch0.prchbresp     = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[0].prchbresp );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch0.prsa          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[0].prsa );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch0.prlsize       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[0].prlsize );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch0.prvsize       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[0].prvsize );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch0.prhsize       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[0].prhsize );
		// PRCH-1
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch1.prchtrg       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[1].prchtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch1.prchctl       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[1].prchctl );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch1.prchrs        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[1].prchrs );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch1.praxctl       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[1].praxctl );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch1.prchintenb    = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[1].prchintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch1.prchintflg    = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[1].prchintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch1.prchbresp     = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[1].prchbresp );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch1.prsa          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[1].prsa );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch1.prlsize       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[1].prlsize );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch1.prvsize       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[1].prvsize );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch1.prhsize       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[1].prhsize );
		// PRCH-2
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch2.prchtrg       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[2].prchtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch2.prchctl       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[2].prchctl );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch2.prchrs        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[2].prchrs );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch2.praxctl       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[2].praxctl );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch2.prchintenb    = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[2].prchintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch2.prchintflg    = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[2].prchintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch2.prchbresp     = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[2].prchbresp );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch2.prsa          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[2].prsa );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch2.prlsize       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[2].prlsize );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch2.prvsize       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[2].prvsize );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch2.prhsize       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[2].prhsize );
		// PRCH-3
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch3.prchtrg       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[3].prchtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch3.prchctl       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[3].prchctl );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch3.prchrs        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[3].prchrs );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch3.praxctl       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[3].praxctl );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch3.prchintenb    = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[3].prchintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch3.prchintflg    = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[3].prchintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch3.prchbresp     = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[3].prchbresp );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch3.prsa          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[3].prsa );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch3.prlsize       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[3].prlsize );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch3.prvsize       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[3].prvsize );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch3.prhsize       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[3].prhsize );
		// PRCH-4
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch4.prchtrg       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[4].prchtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch4.prchctl       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[4].prchctl );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch4.prchrs        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[4].prchrs );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch4.praxctl       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[4].praxctl );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch4.prchintenb    = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[4].prchintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch4.prchintflg    = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[4].prchintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch4.prchbresp     = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[4].prchbresp );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch4.prsa          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[4].prsa );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch4.prlsize       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[4].prlsize );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch4.prvsize       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[4].prvsize );
		CheckHeaderMain_RS_PRINTF("ioPro.b2b[3].prch4.prhsize       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[4].prhsize );
		}
	#endif	/** B2B Unit(pipe[3]) **/

	#ifdef D_ENABLE_IO_PRO_STAT		/** STAT Unit **/
		if(type == CheckHeaderMain_E_PRO_BLOCK_TYPE_STAT) {
		// STATTOP
		CheckHeaderMain_RS_PRINTF("ioPro.stat.stattop.sr                = %x\n", (kuint)&ioPro.stat.stattop.sr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.stattop.clkstp            = %x\n", (kuint)&ioPro.stat.stattop.clkstp );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.stattop.stattopctl1       = %x\n", (kuint)&ioPro.stat.stattop.stattopctl1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.stattop.intmon1           = %x\n", (kuint)&ioPro.stat.stattop.intmon1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.stattop.intmon2           = %x\n", (kuint)&ioPro.stat.stattop.intmon2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.stattop.intctl            = %x\n", (kuint)&ioPro.stat.stattop.intctl );
		// af0
		// General control Unit
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afgbal.aftrg          = %x\n", (kuint)&ioPro.stat.af[0].afgbal.aftrg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afgbal.afeben         = %x\n", (kuint)&ioPro.stat.af[0].afgbal.afeben );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afgbal.afintenb       = %x\n", (kuint)&ioPro.stat.af[0].afgbal.afintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afgbal.afintflg       = %x\n", (kuint)&ioPro.stat.af[0].afgbal.afintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afgbal.afgv           = %x\n", (kuint)&ioPro.stat.af[0].afgbal.afgv );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afgbal.afgh           = %x\n", (kuint)&ioPro.stat.af[0].afgbal.afgh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afgbal.afgvw          = %x\n", (kuint)&ioPro.stat.af[0].afgbal.afgvw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afgbal.afghw          = %x\n", (kuint)&ioPro.stat.af[0].afgbal.afghw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afgbal.afpaen         = %x\n", (kuint)&ioPro.stat.af[0].afgbal.afpaen );
		// Evaluted value Calculation Unit(0)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afmain0.afmtrxrr    = %x\n", (kuint)&ioPro.stat.af[0].afmain0.afmtrxrr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afmain0.afmtrxgr    = %x\n", (kuint)&ioPro.stat.af[0].afmain0.afmtrxgr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afmain0.afmtrxgb    = %x\n", (kuint)&ioPro.stat.af[0].afmain0.afmtrxgb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afmain0.afmtrxbb    = %x\n", (kuint)&ioPro.stat.af[0].afmain0.afmtrxbb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afmain0.afmden      = %x\n", (kuint)&ioPro.stat.af[0].afmain0.afmden );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afmain0.afknen      = %x\n", (kuint)&ioPro.stat.af[0].afmain0.afknen );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afmain0.afknb       = %x\n", (kuint)&ioPro.stat.af[0].afmain0.afknb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afmain0.afkninc     = %x\n", (kuint)&ioPro.stat.af[0].afmain0.afkninc );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afmain0.afknofs     = %x\n", (kuint)&ioPro.stat.af[0].afmain0.afknofs );
		// Evaluted value Calculation Unit(1)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afmain1.afmtrxrr    = %x\n", (kuint)&ioPro.stat.af[0].afmain1.afmtrxrr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afmain1.afmtrxgr    = %x\n", (kuint)&ioPro.stat.af[0].afmain1.afmtrxgr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afmain1.afmtrxgb    = %x\n", (kuint)&ioPro.stat.af[0].afmain1.afmtrxgb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afmain1.afmtrxbb    = %x\n", (kuint)&ioPro.stat.af[0].afmain1.afmtrxbb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afmain1.afmden      = %x\n", (kuint)&ioPro.stat.af[0].afmain1.afmden );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afmain1.afknen      = %x\n", (kuint)&ioPro.stat.af[0].afmain1.afknen );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afmain1.afknb       = %x\n", (kuint)&ioPro.stat.af[0].afmain1.afknb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afmain1.afkninc     = %x\n", (kuint)&ioPro.stat.af[0].afmain1.afkninc );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afmain1.afknofs     = %x\n", (kuint)&ioPro.stat.af[0].afmain1.afknofs );
		// Evaluted value Calculation Unit(2)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afmain2.afmtrxrr    = %x\n", (kuint)&ioPro.stat.af[0].afmain2.afmtrxrr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afmain2.afmtrxgr    = %x\n", (kuint)&ioPro.stat.af[0].afmain2.afmtrxgr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afmain2.afmtrxgb    = %x\n", (kuint)&ioPro.stat.af[0].afmain2.afmtrxgb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afmain2.afmtrxbb    = %x\n", (kuint)&ioPro.stat.af[0].afmain2.afmtrxbb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afmain2.afmden      = %x\n", (kuint)&ioPro.stat.af[0].afmain2.afmden );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afmain2.afknen      = %x\n", (kuint)&ioPro.stat.af[0].afmain2.afknen );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afmain2.afknb       = %x\n", (kuint)&ioPro.stat.af[0].afmain2.afknb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afmain2.afkninc     = %x\n", (kuint)&ioPro.stat.af[0].afmain2.afkninc );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afmain2.afknofs     = %x\n", (kuint)&ioPro.stat.af[0].afmain2.afknofs );
		// Vertical Detection Processing Unit Register
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afvs.afvsctl        = %x\n", (kuint)&ioPro.stat.af[0].afvs.afvsctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afvs.afvsh          = %x\n", (kuint)&ioPro.stat.af[0].afvs.afvsh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afvs.afvshw         = %x\n", (kuint)&ioPro.stat.af[0].afvs.afvshw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afvs.afiirvb        = %x\n", (kuint)&ioPro.stat.af[0].afvs.afiirvb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afvs.afcor2v        = %x\n", (kuint)&ioPro.stat.af[0].afvs.afcor2v );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afvs.affirvb        = %x\n", (kuint)&ioPro.stat.af[0].afvs.affirvb );
		// Horizontal Detection Processing Unit Register(0)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs0.afhsctla      = %x\n", (kuint)&ioPro.stat.af[0].afhs0.afhsctla );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs0.afhsctlb      = %x\n", (kuint)&ioPro.stat.af[0].afhs0.afhsctlb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs0.affirhba      = %x\n", (kuint)&ioPro.stat.af[0].afhs0.affirhba );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs0.affirhbb      = %x\n", (kuint)&ioPro.stat.af[0].afhs0.affirhbb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs0.afcor1ha      = %x\n", (kuint)&ioPro.stat.af[0].afhs0.afcor1ha );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs0.afcor1hb      = %x\n", (kuint)&ioPro.stat.af[0].afhs0.afcor1hb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs0.afgainha      = %x\n", (kuint)&ioPro.stat.af[0].afhs0.afgainha );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs0.afgainhb      = %x\n", (kuint)&ioPro.stat.af[0].afhs0.afgainhb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs0.afiirhba      = %x\n", (kuint)&ioPro.stat.af[0].afhs0.afiirhba );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs0.afiirhbb      = %x\n", (kuint)&ioPro.stat.af[0].afhs0.afiirhbb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs0.afcorbha      = %x\n", (kuint)&ioPro.stat.af[0].afhs0.afcorbha );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs0.afcorbhb      = %x\n", (kuint)&ioPro.stat.af[0].afhs0.afcorbhb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs0.afcorofsha    = %x\n", (kuint)&ioPro.stat.af[0].afhs0.afcorofsha );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs0.afcorofshb    = %x\n", (kuint)&ioPro.stat.af[0].afhs0.afcorofshb );
		// Horizontal Detection Processing Unit Register(1)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs1.afhsctla      = %x\n", (kuint)&ioPro.stat.af[0].afhs1.afhsctla );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs1.afhsctlb      = %x\n", (kuint)&ioPro.stat.af[0].afhs1.afhsctlb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs1.affirhba      = %x\n", (kuint)&ioPro.stat.af[0].afhs1.affirhba );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs1.affirhbb      = %x\n", (kuint)&ioPro.stat.af[0].afhs1.affirhbb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs1.afcor1ha      = %x\n", (kuint)&ioPro.stat.af[0].afhs1.afcor1ha );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs1.afcor1hb      = %x\n", (kuint)&ioPro.stat.af[0].afhs1.afcor1hb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs1.afgainha      = %x\n", (kuint)&ioPro.stat.af[0].afhs1.afgainha );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs1.afgainhb      = %x\n", (kuint)&ioPro.stat.af[0].afhs1.afgainhb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs1.afiirhba      = %x\n", (kuint)&ioPro.stat.af[0].afhs1.afiirhba );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs1.afiirhbb      = %x\n", (kuint)&ioPro.stat.af[0].afhs1.afiirhbb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs1.afcorbha      = %x\n", (kuint)&ioPro.stat.af[0].afhs1.afcorbha );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs1.afcorbhb      = %x\n", (kuint)&ioPro.stat.af[0].afhs1.afcorbhb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs1.afcorofsha    = %x\n", (kuint)&ioPro.stat.af[0].afhs1.afcorofsha );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs1.afcorofshb    = %x\n", (kuint)&ioPro.stat.af[0].afhs1.afcorofshb );
		// Horizontal Detection Processing Unit Register(2)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs2.afhsctla      = %x\n", (kuint)&ioPro.stat.af[0].afhs2.afhsctla );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs2.afhsctlb      = %x\n", (kuint)&ioPro.stat.af[0].afhs2.afhsctlb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs2.affirhba      = %x\n", (kuint)&ioPro.stat.af[0].afhs2.affirhba );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs2.affirhbb      = %x\n", (kuint)&ioPro.stat.af[0].afhs2.affirhbb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs2.afcor1ha      = %x\n", (kuint)&ioPro.stat.af[0].afhs2.afcor1ha );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs2.afcor1hb      = %x\n", (kuint)&ioPro.stat.af[0].afhs2.afcor1hb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs2.afgainha      = %x\n", (kuint)&ioPro.stat.af[0].afhs2.afgainha );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs2.afgainhb      = %x\n", (kuint)&ioPro.stat.af[0].afhs2.afgainhb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs2.afiirhba      = %x\n", (kuint)&ioPro.stat.af[0].afhs2.afiirhba );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs2.afiirhbb      = %x\n", (kuint)&ioPro.stat.af[0].afhs2.afiirhbb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs2.afcorbha      = %x\n", (kuint)&ioPro.stat.af[0].afhs2.afcorbha );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs2.afcorbhb      = %x\n", (kuint)&ioPro.stat.af[0].afhs2.afcorbhb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs2.afcorofsha    = %x\n", (kuint)&ioPro.stat.af[0].afhs2.afcorofsha );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afhs2.afcorofshb    = %x\n", (kuint)&ioPro.stat.af[0].afhs2.afcorofshb );
		// Detection Window Processing Unit Register(0)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin0.afwinctl     = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afwinctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin0.afclvge      = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afclvge );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin0.afclvl       = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afclvl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin0.afv          = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afv );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin0.afh          = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin0.afvw         = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afvw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin0.afhw         = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afhw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin0.afdatas      = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afdatas );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin0.afdatage     = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afdatage );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin0.afdatal      = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afdatal );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin0.afdatah0     = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afdatah0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin0.afdatah1     = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afdatah1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin0.afdatah2     = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afdatah2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin0.afdatav      = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afdatav );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin0.afslwm       = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afslwm );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin0.afdatamax    = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afdatamax );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin0.afdatamin    = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afdatamin );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin0.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afdatamh0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin0.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afdatamh1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin0.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afdatamh2 );
		// Detection Window Processing Unit Register(1)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin1.afwinctl     = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afwinctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin1.afclvge      = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afclvge );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin1.afclvl       = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afclvl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin1.afv          = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afv );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin1.afh          = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin1.afvw         = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afvw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin1.afhw         = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afhw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin1.afdatas      = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afdatas );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin1.afdatage     = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afdatage );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin1.afdatal      = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afdatal );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin1.afdatah0     = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afdatah0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin1.afdatah1     = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afdatah1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin1.afdatah2     = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afdatah2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin1.afdatav      = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afdatav );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin1.afslwm       = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afslwm );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin1.afdatamax    = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afdatamax );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin1.afdatamin    = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afdatamin );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin1.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afdatamh0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin1.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afdatamh1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin1.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afdatamh2 );
		// Detection Window Processing Unit Register(2)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin2.afwinctl     = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afwinctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin2.afclvge      = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afclvge );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin2.afclvl       = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afclvl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin2.afv          = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afv );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin2.afh          = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin2.afvw         = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afvw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin2.afhw         = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afhw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin2.afdatas      = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afdatas );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin2.afdatage     = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afdatage );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin2.afdatal      = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afdatal );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin2.afdatah0     = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afdatah0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin2.afdatah1     = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afdatah1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin2.afdatah2     = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afdatah2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin2.afdatav      = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afdatav );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin2.afslwm       = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afslwm );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin2.afdatamax    = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afdatamax );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin2.afdatamin    = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afdatamin );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin2.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afdatamh0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin2.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afdatamh1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin2.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afdatamh2 );
		// Detection Window Processing Unit Register(3)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin3.afwinctl     = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afwinctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin3.afclvge      = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afclvge );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin3.afclvl       = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afclvl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin3.afv          = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afv );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin3.afh          = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin3.afvw         = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afvw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin3.afhw         = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afhw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin3.afdatas      = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afdatas );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin3.afdatage     = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afdatage );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin3.afdatal      = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afdatal );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin3.afdatah0     = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afdatah0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin3.afdatah1     = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afdatah1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin3.afdatah2     = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afdatah2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin3.afdatav      = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afdatav );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin3.afslwm       = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afslwm );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin3.afdatamax    = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afdatamax );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin3.afdatamin    = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afdatamin );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin3.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afdatamh0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin3.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afdatamh1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin3.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afdatamh2 );
		// Detection Window Processing Unit Register(4)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin4.afwinctl     = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afwinctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin4.afclvge      = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afclvge );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin4.afclvl       = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afclvl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin4.afv          = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afv );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin4.afh          = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin4.afvw         = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afvw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin4.afhw         = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afhw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin4.afdatas      = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afdatas );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin4.afdatage     = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afdatage );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin4.afdatal      = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afdatal );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin4.afdatah0     = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afdatah0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin4.afdatah1     = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afdatah1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin4.afdatah2     = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afdatah2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin4.afdatav      = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afdatav );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin4.afslwm       = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afslwm );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin4.afdatamax    = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afdatamax );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin4.afdatamin    = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afdatamin );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin4.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afdatamh0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin4.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afdatamh1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin4.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afdatamh2 );
		// Detection Window Processing Unit Register(5)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin5.afwinctl     = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afwinctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin5.afclvge      = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afclvge );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin5.afclvl       = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afclvl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin5.afv          = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afv );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin5.afh          = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin5.afvw         = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afvw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin5.afhw         = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afhw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin5.afdatas      = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afdatas );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin5.afdatage     = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afdatage );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin5.afdatal      = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afdatal );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin5.afdatah0     = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afdatah0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin5.afdatah1     = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afdatah1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin5.afdatah2     = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afdatah2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin5.afdatav      = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afdatav );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin5.afslwm       = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afslwm );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin5.afdatamax    = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afdatamax );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin5.afdatamin    = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afdatamin );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin5.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afdatamh0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin5.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afdatamh1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin5.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afdatamh2 );
		// Detection Window Processing Unit Register(6)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin6.afwinctl     = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afwinctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin6.afclvge      = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afclvge );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin6.afclvl       = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afclvl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin6.afv          = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afv );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin6.afh          = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin6.afvw         = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afvw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin6.afhw         = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afhw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin6.afdatas      = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afdatas );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin6.afdatage     = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afdatage );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin6.afdatal      = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afdatal );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin6.afdatah0     = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afdatah0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin6.afdatah1     = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afdatah1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin6.afdatah2     = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afdatah2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin6.afdatav      = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afdatav );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin6.afslwm       = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afslwm );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin6.afdatamax    = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afdatamax );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin6.afdatamin    = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afdatamin );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin6.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afdatamh0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin6.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afdatamh1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin6.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afdatamh2 );
		// Detection Window Processing Unit Register(7)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin7.afwinctl     = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afwinctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin7.afclvge      = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afclvge );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin7.afclvl       = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afclvl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin7.afv          = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afv );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin7.afh          = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin7.afvw         = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afvw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin7.afhw         = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afhw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin7.afdatas      = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afdatas );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin7.afdatage     = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afdatage );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin7.afdatal      = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afdatal );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin7.afdatah0     = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afdatah0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin7.afdatah1     = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afdatah1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin7.afdatah2     = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afdatah2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin7.afdatav      = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afdatav );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin7.afslwm       = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afslwm );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin7.afdatamax    = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afdatamax );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin7.afdatamin    = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afdatamin );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin7.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afdatamh0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin7.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afdatamh1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin7.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afdatamh2 );
		// Detection Window Processing Unit Register(8)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin8.afwinctl     = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afwinctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin8.afclvge      = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afclvge );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin8.afclvl       = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afclvl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin8.afv          = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afv );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin8.afh          = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin8.afvw         = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afvw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin8.afhw         = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afhw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin8.afdatas      = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afdatas );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin8.afdatage     = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afdatage );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin8.afdatal      = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afdatal );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin8.afdatah0     = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afdatah0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin8.afdatah1     = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afdatah1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin8.afdatah2     = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afdatah2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin8.afdatav      = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afdatav );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin8.afslwm       = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afslwm );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin8.afdatamax    = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afdatamax );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin8.afdatamin    = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afdatamin );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin8.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afdatamh0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin8.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afdatamh1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin8.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afdatamh2 );
		// Detection Window Processing Unit Register(9)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin9.afwinctl     = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afwinctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin9.afclvge      = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afclvge );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin9.afclvl       = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afclvl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin9.afv          = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afv );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin9.afh          = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin9.afvw         = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afvw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin9.afhw         = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afhw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin9.afdatas      = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afdatas );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin9.afdatage     = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afdatage );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin9.afdatal      = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afdatal );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin9.afdatah0     = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afdatah0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin9.afdatah1     = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afdatah1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin9.afdatah2     = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afdatah2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin9.afdatav      = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afdatav );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin9.afslwm       = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afslwm );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin9.afdatamax    = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afdatamax );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin9.afdatamin    = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afdatamin );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin9.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afdatamh0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin9.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afdatamh1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin9.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afdatamh2 );
		// Detection Window Processing Unit Register(10)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin10.afwinctl     = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afwinctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin10.afclvge      = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afclvge );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin10.afclvl       = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afclvl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin10.afv          = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afv );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin10.afh          = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin10.afvw         = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afvw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin10.afhw         = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afhw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin10.afdatas      = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afdatas );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin10.afdatage     = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afdatage );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin10.afdatal      = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afdatal );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin10.afdatah0     = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afdatah0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin10.afdatah1     = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afdatah1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin10.afdatah2     = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afdatah2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin10.afdatav      = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afdatav );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin10.afslwm       = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afslwm );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin10.afdatamax    = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afdatamax );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin10.afdatamin    = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afdatamin );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin10.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afdatamh0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin10.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afdatamh1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin10.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afdatamh2 );
		// Detection Window Processing Unit Register(11)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin11.afwinctl     = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afwinctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin11.afclvge      = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afclvge );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin11.afclvl       = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afclvl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin11.afv          = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afv );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin11.afh          = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin11.afvw         = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afvw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin11.afhw         = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afhw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin11.afdatas      = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afdatas );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin11.afdatage     = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afdatage );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin11.afdatal      = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afdatal );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin11.afdatah0     = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afdatah0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin11.afdatah1     = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afdatah1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin11.afdatah2     = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afdatah2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin11.afdatav      = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afdatav );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin11.afslwm       = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afslwm );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin11.afdatamax    = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afdatamax );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin11.afdatamin    = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afdatamin );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin11.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afdatamh0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin11.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afdatamh1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin11.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afdatamh2 );
		// Detection Window Processing Unit Register(12)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin12.afwinctl     = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afwinctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin12.afclvge      = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afclvge );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin12.afclvl       = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afclvl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin12.afv          = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afv );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin12.afh          = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin12.afvw         = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afvw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin12.afhw         = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afhw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin12.afdatas      = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afdatas );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin12.afdatage     = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afdatage );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin12.afdatal      = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afdatal );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin12.afdatah0     = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afdatah0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin12.afdatah1     = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afdatah1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin12.afdatah2     = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afdatah2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin12.afdatav      = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afdatav );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin12.afslwm       = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afslwm );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin12.afdatamax    = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afdatamax );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin12.afdatamin    = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afdatamin );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin12.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afdatamh0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin12.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afdatamh1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin12.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afdatamh2 );
		// Detection Window Processing Unit Register(13)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin13.afwinctl     = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afwinctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin13.afclvge      = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afclvge );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin13.afclvl       = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afclvl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin13.afv          = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afv );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin13.afh          = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin13.afvw         = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afvw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin13.afhw         = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afhw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin13.afdatas      = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afdatas );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin13.afdatage     = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afdatage );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin13.afdatal      = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afdatal );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin13.afdatah0     = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afdatah0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin13.afdatah1     = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afdatah1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin13.afdatah2     = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afdatah2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin13.afdatav      = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afdatav );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin13.afslwm       = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afslwm );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin13.afdatamax    = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afdatamax );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin13.afdatamin    = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afdatamin );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin13.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afdatamh0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin13.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afdatamh1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin13.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afdatamh2 );
		// Detection Window Processing Unit Register(14)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin14.afwinctl     = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afwinctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin14.afclvge      = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afclvge );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin14.afclvl       = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afclvl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin14.afv          = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afv );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin14.afh          = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin14.afvw         = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afvw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin14.afhw         = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afhw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin14.afdatas      = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afdatas );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin14.afdatage     = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afdatage );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin14.afdatal      = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afdatal );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin14.afdatah0     = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afdatah0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin14.afdatah1     = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afdatah1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin14.afdatah2     = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afdatah2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin14.afdatav      = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afdatav );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin14.afslwm       = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afslwm );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin14.afdatamax    = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afdatamax );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin14.afdatamin    = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afdatamin );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin14.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afdatamh0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin14.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afdatamh1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af0.afwin14.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afdatamh2 );
	}
#endif	/** STAT Unit **/
#endif
}

ProTest7 *pro_test7_new()
{
	ProTest7 *self = g_object_new(PRO_TYPE_TEST7, NULL);

	return self;
}
