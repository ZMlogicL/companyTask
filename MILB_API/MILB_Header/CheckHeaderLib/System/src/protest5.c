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
#include "protest5.h"

G_DEFINE_TYPE(ProTest5, pro_test5, G_TYPE_OBJECT);

#define PRO_TEST5_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o), PRO_TYPE_TEST5, ProTest5Private));


struct _ProTest5Private
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
static void pro_test5_class_init(ProTest5Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);

	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(ProTest5Private));
}

static void pro_test5_init(ProTest5 *self)
{
	ProTest5Private *priv = PRO_TEST5_GET_PRIVATE(self);

	priv->preserved = 0;
}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(pro_test5_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	G_OBJECT_CLASS(pro_test5_parent_class)->finalize(object);
}
/*
 * PUBLIC
 */
void pro_test5(ProTest5 *self, EProBlockType type, IoPro ioPro)
{
#if 0
#ifdef D_ENABLE_IO_PRO_SRO_PIPE_3	/** SRO Unit(pipe[3]) **/
	if(type == CheckHeaderMain_E_PRO_BLOCK_TYPE_SRO3) {
		// SROTOP
		CheckHeaderMain_RS_PRINTF("SR0[3]\n");
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].spotop.sr          = %x\n", (kuint)&ioPro.imgPipe[2].sro.spotop.sr );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].spotop.clkstp      = %x\n", (kuint)&ioPro.imgPipe[2].sro.spotop.clkstp );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].spotop.spotopctl1  = %x\n", (kuint)&ioPro.imgPipe[2].sro.spotop.spotopctl1 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].spotop.spotopctl2  = %x\n", (kuint)&ioPro.imgPipe[2].sro.spotop.spotopctl2 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].spotop.intmon1     = %x\n", (kuint)&ioPro.imgPipe[2].sro.spotop.intmon1 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].spotop.intmon2     = %x\n", (kuint)&ioPro.imgPipe[2].sro.spotop.intmon2 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].spotop.intctl      = %x\n", (kuint)&ioPro.imgPipe[2].sro.spotop.intctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].spotop.vhdintenb   = %x\n", (kuint)&ioPro.imgPipe[2].sro.spotop.vhdintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].spotop.vhdintflg   = %x\n", (kuint)&ioPro.imgPipe[2].sro.spotop.vhdintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].spotop.vhset       = %x\n", (kuint)&ioPro.imgPipe[2].sro.spotop.vhset );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].spotop.vmivadr     = %x\n", (kuint)&ioPro.imgPipe[2].sro.spotop.vmivadr );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].spotop.vmihadr     = %x\n", (kuint)&ioPro.imgPipe[2].sro.spotop.vmihadr );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].spotop.hmihadr     = %x\n", (kuint)&ioPro.imgPipe[2].sro.spotop.hmihadr );
		// PG
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pg.pgtrg           = %x\n", (kuint)&ioPro.imgPipe[2].sro.pg.pgtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pg.pgctl           = %x\n", (kuint)&ioPro.imgPipe[2].sro.pg.pgctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pg.pgvw            = %x\n", (kuint)&ioPro.imgPipe[2].sro.pg.pgvw );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pg.pghw            = %x\n", (kuint)&ioPro.imgPipe[2].sro.pg.pghw );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pg.pgvblnk         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pg.pgvblnk );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pg.pghblnk         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pg.pghblnk );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pg.pgvdhdblnk      = %x\n", (kuint)&ioPro.imgPipe[2].sro.pg.pgvdhdblnk );
		// FFSH-0
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ffsh0.ffshtrg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[0].ffshtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ffsh0.ffshpaen     = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[0].ffshpaen );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ffsh0.ffshv        = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[0].ffshv );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ffsh0.ffshh        = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[0].ffshh );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ffsh0.ffshvw       = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[0].ffshvw );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ffsh0.ffshhw       = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[0].ffshhw );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ffsh0.ffshbc       = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[0].ffshbc );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ffsh0.ffshsubpr    = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[0].ffshsubpr );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ffsh0.ffshsubsp    = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[0].ffshsubsp );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ffsh0.ffshsubdr    = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[0].ffshsubdr );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ffsh0.ffshsubst    = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[0].ffshsubst );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ffsh0.ffshwric     = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[0].ffshwric );
		// FFSH-1
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ffsh1.ffshtrg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[1].ffshtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ffsh1.ffshpaen     = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[1].ffshpaen );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ffsh1.ffshv        = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[1].ffshv );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ffsh1.ffshh        = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[1].ffshh );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ffsh1.ffshvw       = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[1].ffshvw );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ffsh1.ffshhw       = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[1].ffshhw );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ffsh1.ffshbc       = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[1].ffshbc );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ffsh1.ffshsubpr    = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[1].ffshsubpr );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ffsh1.ffshsubsp    = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[1].ffshsubsp );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ffsh1.ffshsubdr    = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[1].ffshsubdr );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ffsh1.ffshsubst    = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[1].ffshsubst );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ffsh1.ffshwric     = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[1].ffshwric );
		// FF-0
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ff0.fftrg          = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[0].fftrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ff0.ffv            = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[0].ffv );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ff0.ffh            = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[0].ffh );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ff0.ffvw           = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[0].ffvw );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ff0.ffhw           = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[0].ffhw );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ff0.fflpb0         = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[0].fflpb0 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ff0.fflpb1         = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[0].fflpb1 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ff0.fflpb2         = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[0].fflpb2 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ff0.ffdefts        = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[0].ffdefts );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ff0.ffmnwgt        = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[0].ffmnwgt );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ff0.ffsbwgt        = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[0].ffsbwgt );
		// FF-1
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ff1.fftrg          = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[1].fftrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ff1.ffv            = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[1].ffv );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ff1.ffh            = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[1].ffh );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ff1.ffvw           = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[1].ffvw );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ff1.ffhw           = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[1].ffhw );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ff1.fflpb0         = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[1].fflpb0 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ff1.fflpb1         = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[1].fflpb1 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ff1.fflpb2         = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[1].fflpb2 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ff1.ffdefts        = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[1].ffdefts );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ff1.ffmnwgt        = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[1].ffmnwgt );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ff1.ffsbwgt        = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[1].ffsbwgt );

		// PGAIN0
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pgain0.pgaintrg     = %x\n", (kuint)&ioPro.imgPipe[2].sro.pgain0.pgaintrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pgain0.pgainr       = %x\n", (kuint)&ioPro.imgPipe[2].sro.pgain0.pgainr );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pgain0.pgaingr      = %x\n", (kuint)&ioPro.imgPipe[2].sro.pgain0.pgaingr );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pgain0.pgaingb      = %x\n", (kuint)&ioPro.imgPipe[2].sro.pgain0.pgaingb );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pgain0.pgainb       = %x\n", (kuint)&ioPro.imgPipe[2].sro.pgain0.pgainb );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pgain0.pofsr        = %x\n", (kuint)&ioPro.imgPipe[2].sro.pgain0.pofsr );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pgain0.pofsgr       = %x\n", (kuint)&ioPro.imgPipe[2].sro.pgain0.pofsgr );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pgain0.pofsgb       = %x\n", (kuint)&ioPro.imgPipe[2].sro.pgain0.pofsgb );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pgain0.pofsb        = %x\n", (kuint)&ioPro.imgPipe[2].sro.pgain0.pofsb );
		// SDC-0
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc0.sdctrg     = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdctrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc0.sdcpaen    = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcpaen );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc0.sdcctl     = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc0.sdcintenb  = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc0.sdcintflg  = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc0.sdcsgd     = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcsgd );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc0.sdcph0     = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcph0 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc0.sdcph1     = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcph1 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc0.sdcphw0    = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcphw0 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc0.sdcphw1    = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcphw1 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc0.sdcp1hw0   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcp1hw0 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc0.sdcp1hw1   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcp1hw1 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc0.sdcn1hw0   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcn1hw0 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc0.sdcn1hw1   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcn1hw1 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc0.sdcp2hw0   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcp2hw0 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc0.sdcp2hw1   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcp2hw1 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc0.sdcn2hw0   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcn2hw0 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc0.sdcn2hw1   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcn2hw1 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc0.sdcpc0     = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcpc0 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc0.sdcpc1     = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcpc1 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc0.sdcpcw0    = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcpcw0 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc0.sdcpcw1    = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcpcw1 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc0.sdcp1cw0   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcp1cw0 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc0.sdcp1cw1   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcp1cw1 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc0.sdcn1cw0   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcn1cw0 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc0.sdcn1cw1   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcn1cw1 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc0.sdcp2cw0   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcp2cw0 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc0.sdcp2cw1   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcp2cw1 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc0.sdcn2cw0   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcn2cw0 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc0.sdcn2cw1   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcn2cw1 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc0.sdcgmaxmin = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcgmaxmin );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc0.sdcnmax    = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcnmax );
		// SDC-1
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc1.sdctrg     = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdctrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc1.sdcpaen    = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcpaen );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc1.sdcctl     = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc1.sdcintenb  = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc1.sdcintflg  = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc1.sdcsgd     = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcsgd );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc1.sdcph0     = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcph0 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc1.sdcph1     = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcph1 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc1.sdcphw0    = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcphw0 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc1.sdcphw1    = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcphw1 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc1.sdcp1hw0   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcp1hw0 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc1.sdcp1hw1   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcp1hw1 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc1.sdcn1hw0   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcn1hw0 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc1.sdcn1hw1   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcn1hw1 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc1.sdcp2hw0   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcp2hw0 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc1.sdcp2hw1   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcp2hw1 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc1.sdcn2hw0   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcn2hw0 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc1.sdcn2hw1   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcn2hw1 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc1.sdcpc0     = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcpc0 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc1.sdcpc1     = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcpc1 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc1.sdcpcw0    = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcpcw0 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc1.sdcpcw1    = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcpcw1 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc1.sdcp1cw0   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcp1cw0 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc1.sdcp1cw1   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcp1cw1 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc1.sdcn1cw0   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcn1cw0 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc1.sdcn1cw1   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcn1cw1 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc1.sdcp2cw0   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcp2cw0 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc1.sdcp2cw1   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcp2cw1 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc1.sdcn2cw0   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcn2cw0 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc1.sdcn2cw1   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcn2cw1 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc1.sdcgmaxmin = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcgmaxmin );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].sdc1.sdcnmax    = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcnmax );
		// PZSFTB1
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pzsftb1.pzsfttrg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.pzsftb1.pzsfttrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pzsftb1.pzofst        = %x\n", (kuint)&ioPro.imgPipe[2].sro.pzsftb1.pzofst );
		// DPC
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].dpc.dpctrg            = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dpctrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].dpc.dpcpaen           = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dpcpaen );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].dpc.dpcgwp            = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dpcgwp );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].dpc.dpcgws            = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dpcgws );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].dpc.dpcwp             = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dpcwp );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].dpc.dpcws             = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dpcws );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].dpc.dpcmd             = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dpcmd );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].dpc.dpcblp            = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dpcblp );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].dpc.dpcblm            = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dpcblm );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].dpc.dfctl             = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dfctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].dpc.dfs               = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dfs );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].dpc.dfo               = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dfo );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].dpc.dfk               = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dfk );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].dpc.dfh               = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dfh );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].dpc.dfcsr             = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dfcsr );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].dpc.dflsth            = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dflsth );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].dpc.dfagef            = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dfagef );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].dpc.dfagef2           = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dfagef2 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].dpc.dfagth            = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dfagth );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].dpc.dfagthk           = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dfagthk );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].dpc.dmctl             = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dmctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].dpc.dmwks             = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dmwks );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].dpc.dmwkd             = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dmwkd );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].dpc.dmagk             = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dmagk );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].dpc.dectl             = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dectl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].dpc.denss             = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.denss );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].dpc.denso             = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.denso );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].dpc.densk             = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.densk );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].dpc.densh             = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.densh );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].dpc.densmgn           = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.densmgn );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].dpc.dendcth           = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dendcth );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].dpc.deagk             = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.deagk );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].dpc.dcagef            = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dcagef );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].dpc.dcagth            = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dcagth );
		// PZSFTB2
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pzsftb2.pzsfttrg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.pzsftb2.pzsfttrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pzsftb2.pzofst        = %x\n", (kuint)&ioPro.imgPipe[2].sro.pzsftb2.pzofst );
		// FSHDL0
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].fshdl0.ffshtrg        = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl0.ffshtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].fshdl0.ffshpaen       = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl0.ffshpaen );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].fshdl0.ffshv          = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl0.ffshv );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].fshdl0.ffshh          = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl0.ffshh );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].fshdl0.ffshvw         = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl0.ffshvw );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].fshdl0.ffshhw         = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl0.ffshhw );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].fshdl0.ffshbc         = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl0.ffshbc );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].fshdl0.ffshul1        = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl0.ffshul1 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].fshdl0.ffshul2        = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl0.ffshul2 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].fshdl0.ffshgfmt       = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl0.ffshgfmt );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].fshdl0.ffshsubpr      = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl0.ffshsubpr );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].fshdl0.ffshsubsp      = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl0.ffshsubsp );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].fshdl0.ffshsubdr      = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl0.ffshsubdr );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].fshdl0.ffshsubst      = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl0.ffshsubst );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].fshdl0.ffshctl        = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl0.ffshctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].fshdl0.ffshhwph       = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl0.ffshhwph );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].fshdl0.ffshwric       = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl0.ffshwric );
		// AFPBA
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].afpbA.afpbtrg         = %x\n", (kuint)&ioPro.imgPipe[2].sro.afpb[0].afpbtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].afpbA.afpbv           = %x\n", (kuint)&ioPro.imgPipe[2].sro.afpb[0].afpbv );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].afpbA.afpbh           = %x\n", (kuint)&ioPro.imgPipe[2].sro.afpb[0].afpbh );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].afpbA.afpbvw          = %x\n", (kuint)&ioPro.imgPipe[2].sro.afpb[0].afpbvw );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].afpbA.afpbhw          = %x\n", (kuint)&ioPro.imgPipe[2].sro.afpb[0].afpbhw );
		// AFPBB
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].afpbG.afpbtrg         = %x\n", (kuint)&ioPro.imgPipe[2].sro.afpb[1].afpbtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].afpbG.afpbv           = %x\n", (kuint)&ioPro.imgPipe[2].sro.afpb[1].afpbv );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].afpbG.afpbh           = %x\n", (kuint)&ioPro.imgPipe[2].sro.afpb[1].afpbh );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].afpbG.afpbvw          = %x\n", (kuint)&ioPro.imgPipe[2].sro.afpb[1].afpbvw );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].afpbG.afpbhw          = %x\n", (kuint)&ioPro.imgPipe[2].sro.afpb[1].afpbhw );
		// PZSFTC1
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pzsftc1.pzsfttrg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.pzsftc1.pzsfttrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pzsftc1.pzofst        = %x\n", (kuint)&ioPro.imgPipe[2].sro.pzsftc1.pzofst );
		// FFC
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ffc.fctrg             = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffc.fctrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ffc.fcpaen            = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffc.fcpaen );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ffc.fcv               = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffc.fcv );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ffc.fch               = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffc.fch );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ffc.fcvw              = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffc.fcvw );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ffc.fchw              = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffc.fchw );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ffc.fcbc              = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffc.fcbc );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ffc.fcsubpr           = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffc.fcsubpr );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ffc.fcsubsp           = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffc.fcsubsp );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ffc.fcsubdr           = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffc.fcsubdr );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ffc.fcsubst           = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffc.fcsubst );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].ffc.fcwric            = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffc.fcwric );
		// CAG
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.cagtrg            = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.cagtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.cagpaen           = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.cagpaen );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.caggwp            = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.caggwp );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.caggws            = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.caggws );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.cagwp             = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.cagwp );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.cagws             = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.cagws );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.cagmd             = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.cagmd );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.rbr               = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.rbr );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.aboarv            = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.aboarv );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.aboarh            = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.aboarh );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.aboagv            = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.aboagv );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.aboagh            = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.aboagh );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.aboabv            = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.aboabv );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.aboabh            = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.aboabh );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.abgar             = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abgar );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.abgag             = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abgag );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.abgab             = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abgab );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.ablrv             = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.ablrv );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.ablrh             = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.ablrh );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.ablgv             = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.ablgv );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.ablgh             = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.ablgh );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.ablbv             = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.ablbv );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.ablbh             = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.ablbh );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.abofsrv           = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abofsrv );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.abofsrh           = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abofsrh );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.abofsgv           = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abofsgv );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.abofsgh           = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abofsgh );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.abofsbv           = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abofsbv );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.abofsbh           = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abofsbh );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.abnlthr1          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlthr1 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.abnlthg1          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlthg1 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.abnlthb1          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlthb1 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.abnlgar1          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlgar1 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.abnlgag1          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlgag1 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.abnlgab1          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlgab1 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.abnlthr2          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlthr2 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.abnlthg2          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlthg2 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.abnlthb2          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlthb2 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.abnlgar2          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlgar2 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.abnlgag2          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlgag2 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.abnlgab2          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlgab2 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.abnlthr3          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlthr3 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.abnlthg3          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlthg3 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.abnlthb3          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlthb3 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.abnlgar3          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlgar3 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.abnlgag3          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlgag3 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.abnlgab3          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlgab3 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.abnlthr4          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlthr4 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.abnlthg4          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlthg4 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.abnlthb4          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlthb4 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.abnlgar4          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlgar4 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.abnlgag4          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlgag4 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.abnlgab4          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlgab4 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.bfglmt            = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.bfglmt );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].cag.bfgth             = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.bfgth );
		// PZSFTC2
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pzsftc2.pzsfttrg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.pzsftc2.pzsfttrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pzsftc2.pzofst        = %x\n", (kuint)&ioPro.imgPipe[2].sro.pzsftc2.pzofst );
		// FSHDL1
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].fshdl1.ffshtrg        = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl1.ffshtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].fshdl1.ffshpaen       = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl1.ffshpaen );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].fshdl1.ffshv          = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl1.ffshv );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].fshdl1.ffshh          = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl1.ffshh );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].fshdl1.ffshvw         = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl1.ffshvw );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].fshdl1.ffshhw         = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl1.ffshhw );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].fshdl1.ffshbc         = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl1.ffshbc );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].fshdl1.ffshul1        = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl1.ffshul1 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].fshdl1.ffshul2        = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl1.ffshul2 );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].fshdl1.ffshgfmt       = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl1.ffshgfmt );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].fshdl1.ffshsubpr      = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl1.ffshsubpr );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].fshdl1.ffshsubsp      = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl1.ffshsubsp );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].fshdl1.ffshsubdr      = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl1.ffshsubdr );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].fshdl1.ffshsubst      = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl1.ffshsubst );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].fshdl1.ffshctl        = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl1.ffshctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].fshdl1.ffshhwph       = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl1.ffshhwph );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].fshdl1.ffshwric       = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl1.ffshwric );
		// VRB
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].vrb.vrbtrg            = %x\n", (kuint)&ioPro.imgPipe[2].sro.vrb.vrbtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].vrb.vrbv              = %x\n", (kuint)&ioPro.imgPipe[2].sro.vrb.vrbv );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].vrb.vrbh              = %x\n", (kuint)&ioPro.imgPipe[2].sro.vrb.vrbh );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].vrb.vrbvw             = %x\n", (kuint)&ioPro.imgPipe[2].sro.vrb.vrbvw );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].vrb.vrbhw             = %x\n", (kuint)&ioPro.imgPipe[2].sro.vrb.vrbhw );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].vrb.vrbscyc           = %x\n", (kuint)&ioPro.imgPipe[2].sro.vrb.vrbscyc );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].vrb.vrbpaen           = %x\n", (kuint)&ioPro.imgPipe[2].sro.vrb.vrbpaen );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].vrb.vrb0k             = %x\n", (kuint)&ioPro.imgPipe[2].sro.vrb.vrb0k );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].vrb.vrb1k             = %x\n", (kuint)&ioPro.imgPipe[2].sro.vrb.vrb1k );
		// HRB
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].hrb.hrbtrg            = %x\n", (kuint)&ioPro.imgPipe[2].sro.hrb.hrbtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].hrb.hrbv              = %x\n", (kuint)&ioPro.imgPipe[2].sro.hrb.hrbv );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].hrb.hrbh              = %x\n", (kuint)&ioPro.imgPipe[2].sro.hrb.hrbh );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].hrb.hrbvw             = %x\n", (kuint)&ioPro.imgPipe[2].sro.hrb.hrbvw );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].hrb.hrbhw             = %x\n", (kuint)&ioPro.imgPipe[2].sro.hrb.hrbhw );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].hrb.hrbohw            = %x\n", (kuint)&ioPro.imgPipe[2].sro.hrb.hrbohw );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].hrb.hrbscyc           = %x\n", (kuint)&ioPro.imgPipe[2].sro.hrb.hrbscyc );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].hrb.hrbosm            = %x\n", (kuint)&ioPro.imgPipe[2].sro.hrb.hrbosm );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].hrb.hrbpaen           = %x\n", (kuint)&ioPro.imgPipe[2].sro.hrb.hrbpaen );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].hrb.hrbk              = %x\n", (kuint)&ioPro.imgPipe[2].sro.hrb.hrbk );
		// P2M-0
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m0.p2mtrg           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[0].p2mtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m0.p2mpaen          = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[0].p2mpaen );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m0.p2mctl           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[0].p2mctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m0.p2mofs           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[0].p2mofs );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m0.pbsft            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[0].pbsft );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m0.pclph            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[0].pclph );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m0.ptrmv            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[0].ptrmv );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m0.ptrmh            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[0].ptrmh );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m0.ptrmvw           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[0].ptrmvw );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m0.ptrmhw           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[0].ptrmhw );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m0.ptrmxvcyc        = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[0].ptrmxvcyc );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m0.ptrmxhcyc        = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[0].ptrmxhcyc );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m0.ptrmxven         = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[0].ptrmxven );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m0.ptrmxhen         = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[0].ptrmxhen );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m0.p2mmir           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[0].p2mmir );
		// P2M-1
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m1.p2mtrg           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[1].p2mtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m1.p2mpaen          = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[1].p2mpaen );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m1.p2mctl           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[1].p2mctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m1.p2mofs           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[1].p2mofs );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m1.pbsft            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[1].pbsft );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m1.pclph            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[1].pclph );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m1.ptrmv            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[1].ptrmv );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m1.ptrmh            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[1].ptrmh );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m1.ptrmvw           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[1].ptrmvw );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m1.ptrmhw           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[1].ptrmhw );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m1.ptrmxvcyc        = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[1].ptrmxvcyc );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m1.ptrmxhcyc        = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[1].ptrmxhcyc );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m1.ptrmxven         = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[1].ptrmxven );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m1.ptrmxhen         = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[1].ptrmxhen );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m1.p2mmir           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[1].p2mmir );
		// P2M-2
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m2.p2mtrg           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[2].p2mtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m2.p2mpaen          = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[2].p2mpaen );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m2.p2mctl           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[2].p2mctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m2.p2mofs           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[2].p2mofs );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m2.pbsft            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[2].pbsft );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m2.pclph            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[2].pclph );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m2.ptrmv            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[2].ptrmv );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m2.ptrmh            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[2].ptrmh );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m2.ptrmvw           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[2].ptrmvw );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m2.ptrmhw           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[2].ptrmhw );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m2.ptrmxvcyc        = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[2].ptrmxvcyc );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m2.ptrmxhcyc        = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[2].ptrmxhcyc );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m2.ptrmxven         = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[2].ptrmxven );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m2.ptrmxhen         = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[2].ptrmxhen );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m2.p2mmir           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[2].p2mmir );
		// P2M-3
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m3.p2mtrg           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[3].p2mtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m3.p2mpaen          = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[3].p2mpaen );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m3.p2mctl           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[3].p2mctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m3.p2mofs           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[3].p2mofs );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m3.pbsft            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[3].pbsft );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m3.pclph            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[3].pclph );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m3.ptrmv            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[3].ptrmv );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m3.ptrmh            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[3].ptrmh );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m3.ptrmvw           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[3].ptrmvw );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m3.ptrmhw           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[3].ptrmhw );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m3.ptrmxvcyc        = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[3].ptrmxvcyc );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m3.ptrmxhcyc        = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[3].ptrmxhcyc );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m3.ptrmxven         = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[3].ptrmxven );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m3.ptrmxhen         = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[3].ptrmxhen );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m3.p2mmir           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[3].p2mmir );
		// P2M-4
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m4.p2mtrg           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[4].p2mtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m4.p2mpaen          = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[4].p2mpaen );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m4.p2mctl           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[4].p2mctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m4.p2mofs           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[4].p2mofs );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m4.pbsft            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[4].pbsft );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m4.pclph            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[4].pclph );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m4.ptrmv            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[4].ptrmv );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m4.ptrmh            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[4].ptrmh );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m4.ptrmvw           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[4].ptrmvw );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m4.ptrmhw           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[4].ptrmhw );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m4.ptrmxvcyc        = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[4].ptrmxvcyc );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m4.ptrmxhcyc        = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[4].ptrmxhcyc );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m4.ptrmxven         = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[4].ptrmxven );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m4.ptrmxhen         = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[4].ptrmxhen );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m4.p2mmir           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[4].p2mmir );
		// P2M-5
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m5.p2mtrg           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[5].p2mtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m5.p2mpaen          = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[5].p2mpaen );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m5.p2mctl           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[5].p2mctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m5.p2mofs           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[5].p2mofs );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m5.pbsft            = %x\n", (kuint)&ioPro.imgPipe[2].sro.P2M[5].pbsft );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m5.pclph            = %x\n", (kuint)&ioPro.imgPipe[2].sro.P2M[5].pclph );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m5.ptrmv            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[5].ptrmv );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m5.ptrmh            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[5].ptrmh );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m5.ptrmvw           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[5].ptrmvw );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m5.ptrmhw           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[5].ptrmhw );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m5.ptrmxvcyc        = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[5].ptrmxvcyc );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m5.ptrmxhcyc        = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[5].ptrmxhcyc );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m5.ptrmxven         = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[5].ptrmxven );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m5.ptrmxhen         = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[5].ptrmxhen );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].p2m5.p2mmir           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[5].p2mmir );
		// PWCH-0
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch0.pwchtrg         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[0].pwchtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch0.pws             = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[0].pws );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch0.pwaxctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[0].pwaxctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch0.pwchctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[0].pwchctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch0.pwchintenb      = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[0].pwchintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch0.pwchintflg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[0].pwchintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch0.pwchbresp       = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[0].pwchbresp );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch0.pwsa            = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[0].pwsa );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch0.pwlsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[0].pwlsize );
		// PWCH-1
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch1.pwchtrg         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[1].pwchtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch1.pws             = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[1].pws );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch1.pwaxctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[1].pwaxctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch1.pwchctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[1].pwchctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch1.pwchintenb      = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[1].pwchintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch1.pwchintflg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[1].pwchintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch1.pwchbresp       = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[1].pwchbresp );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch1.pwsa            = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[1].pwsa );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch1.pwlsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[1].pwlsize );
		// PWCH-2
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch2.pwchtrg         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[2].pwchtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch2.pws             = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[2].pws );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch2.pwaxctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[2].pwaxctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch2.pwchctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[2].pwchctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch2.pwchintenb      = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[2].pwchintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch2.pwchintflg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[2].pwchintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch2.pwchbresp       = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[2].pwchbresp );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch2.pwsa            = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[2].pwsa );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch2.pwlsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[2].pwlsize );
		// PWCH-3
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch3.pwchtrg         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[3].pwchtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch3.pws             = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[3].pws );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch3.pwaxctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[3].pwaxctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch3.pwchctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[3].pwchctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch3.pwchintenb      = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[3].pwchintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch3.pwchintflg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[3].pwchintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch3.pwchbresp       = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[3].pwchbresp );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch3.pwsa            = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[3].pwsa );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch3.pwlsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[3].pwlsize );
		// PWCH-4
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch4.pwchtrg         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[4].pwchtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch4.pws             = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[4].pws );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch4.pwaxctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[4].pwaxctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch4.pwchctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[4].pwchctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch4.pwchintenb      = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[4].pwchintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch4.pwchintflg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[4].pwchintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch4.pwchbresp       = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[4].pwchbresp );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch4.pwsa            = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[4].pwsa );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch4.pwlsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[4].pwlsize );
		// PWCH-5
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch5.pwchtrg         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[5].pwchtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch5.pws             = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[5].pws );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch5.pwaxctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[5].pwaxctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch5.pwchctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[5].pwchctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch5.pwchintenb      = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[5].pwchintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch5.pwchintflg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[5].pwchintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch5.pwchbresp       = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[5].pwchbresp );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch5.pwsa            = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[5].pwsa );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].pwch5.pwlsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[5].pwlsize );
		// M2P-0
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p0.m2ptrg           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[0].m2ptrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p0.m2ppaen          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[0].m2ppaen );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p0.m2pctl           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[0].m2pctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p0.m2pbsft          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[0].m2pbsft );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p0.m2pofs           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[0].m2pofs );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p0.m2pclip          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[0].m2pclip );
		// M2P-1
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p1.m2ptrg           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[1].m2ptrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p1.m2ppaen          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[1].m2ppaen );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p1.m2pctl           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[1].m2pctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p1.m2pbsft          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[1].m2pbsft );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p1.m2pofs           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[1].m2pofs );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p1.m2pclip          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[1].m2pclip );
		// M2P-2
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p2.m2ptrg           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[2].m2ptrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p2.m2ppaen          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[2].m2ppaen );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p2.m2pctl           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[2].m2pctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p2.m2pbsft          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[2].m2pbsft );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p2.m2pofs           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[2].m2pofs );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p2.m2pclip          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[2].m2pclip );
		// M2P-3
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p3.m2ptrg           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[3].m2ptrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p3.m2ppaen          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[3].m2ppaen );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p3.m2pctl           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[3].m2pctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p3.m2pbsft          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[3].m2pbsft );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p3.m2pofs           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[3].m2pofs );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p3.m2pclip          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[3].m2pclip );
		// M2P-6
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p6.m2ptrg           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[4].m2ptrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p6.m2ppaen          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[4].m2ppaen );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p6.m2pctl           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[4].m2pctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p6.m2pbsft          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[4].m2pbsft );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p6.m2pofs           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[4].m2pofs );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p6.m2pclip          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[4].m2pclip );
		// M2P-7
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p7.m2ptrg           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[5].m2ptrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p7.m2ppaen          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[5].m2ppaen );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p7.m2pctl           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[5].m2pctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p7.m2pbsft          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[5].m2pbsft );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p7.m2pofs           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[5].m2pofs );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p7.m2pclip          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[5].m2pclip );
		// M2P-8
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p8.m2ptrg           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[6].m2ptrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p8.m2ppaen          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[6].m2ppaen );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p8.m2pctl           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[6].m2pctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p8.m2pbsft          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[6].m2pbsft );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p8.m2pofs           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[6].m2pofs );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p8.m2pclip          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[6].m2pclip );
		// M2P-0
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p9.m2ptrg           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[7].m2ptrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p9.m2ppaen          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[7].m2ppaen );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p9.m2pctl           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[7].m2pctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p9.m2pbsft          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[7].m2pbsft );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p9.m2pofs           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[7].m2pofs );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].m2p9.m2pclip          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[7].m2pclip );
		// PRCH-0
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch0.prchtrg         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[0].prchtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch0.prchctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[0].prchctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch0.prchrs          = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[0].prchrs );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch0.praxctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[0].praxctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch0.prchintenb      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[0].prchintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch0.prchintflg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[0].prchintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch0.prchbresp       = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[0].prchbresp );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch0.prsa            = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[0].prsa );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch0.prlsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[0].prlsize );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch0.prvsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[0].prvsize );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch0.prhsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[0].prhsize );
		// PRCH-1
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch1.prchtrg         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[1].prchtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch1.prchctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[1].prchctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch1.prchrs          = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[1].prchrs );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch1.praxctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[1].praxctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch1.prchintenb      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[1].prchintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch1.prchintflg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[1].prchintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch1.prchbresp       = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[1].prchbresp );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch1.prsa            = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[1].prsa );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch1.prlsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[1].prlsize );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch1.prvsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[1].prvsize );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch1.prhsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[1].prhsize );
		// PRCH-2
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch2.prchtrg         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[2].prchtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch2.prchctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[2].prchctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch2.prchrs          = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[2].prchrs );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch2.praxctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[2].praxctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch2.prchintenb      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[2].prchintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch2.prchintflg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[2].prchintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch2.prchbresp       = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[2].prchbresp );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch2.prsa            = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[2].prsa );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch2.prlsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[2].prlsize );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch2.prvsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[2].prvsize );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch2.prhsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[2].prhsize );
		// PRCH-3
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch3.prchtrg         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[3].prchtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch3.prchctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[3].prchctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch3.prchrs          = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[3].prchrs );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch3.praxctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[3].praxctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch3.prchintenb      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[3].prchintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch3.prchintflg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[3].prchintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch3.prchbresp       = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[3].prchbresp );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch3.prsa            = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[3].prsa );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch3.prlsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[3].prlsize );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch3.prvsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[3].prvsize );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch3.prhsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[3].prhsize );
		// PRCH-4
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch4.prchtrg         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[4].prchtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch4.prchctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[4].prchctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch4.prchrs          = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[4].prchrs );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch4.praxctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[4].praxctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch4.prchintenb      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[4].prchintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch4.prchintflg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[4].prchintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch4.prchbresp       = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[4].prchbresp );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch4.prsa            = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[4].prsa );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch4.prlsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[4].prlsize );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch4.prvsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[4].prvsize );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch4.prhsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[4].prhsize );
		// PRCH-5
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch5.prchtrg         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[5].prchtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch5.prchctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[5].prchctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch5.prchrs          = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[5].prchrs );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch5.praxctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[5].praxctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch5.prchintenb      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[5].prchintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch5.prchintflg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[5].prchintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch5.prchbresp       = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[5].prchbresp );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch5.prsa            = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[5].prsa );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch5.prlsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[5].prlsize );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch5.prvsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[5].prvsize );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch5.prhsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[5].prhsize );
		// PRCH-6
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch6.prchtrg         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[6].prchtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch6.prchctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[6].prchctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch6.prchrs          = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[6].prchrs );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch6.praxctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[6].praxctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch6.prchintenb      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[6].prchintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch6.prchintflg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[6].prchintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch6.prchbresp       = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[6].prchbresp );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch6.prsa            = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[6].prsa );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch6.prlsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[6].prlsize );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch6.prvsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[6].prvsize );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch6.prhsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[6].prhsize );
		// PRCH-7
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch7.prchtrg         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[7].prchtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch7.prchctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[7].prchctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch7.prchrs          = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[7].prchrs );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch7.praxctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[7].praxctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch7.prchintenb      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[7].prchintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch7.prchintflg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[7].prchintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch7.prchbresp       = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[7].prchbresp );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch7.prsa            = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[7].prsa );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch7.prlsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[7].prlsize );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch7.prvsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[7].prvsize );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch7.prhsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[7].prhsize );
		// PRCH-8
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch8.prchtrg         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[8].prchtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch8.prchctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[8].prchctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch8.prchrs          = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[8].prchrs );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch8.praxctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[8].praxctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch8.prchintenb      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[8].prchintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch8.prchintflg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[8].prchintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch8.prchbresp       = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[8].prchbresp );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch8.prsa            = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[8].prsa );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch8.prlsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[8].prlsize );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch8.prvsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[8].prvsize );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch8.prhsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[8].prhsize );
		// PRCH-9
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch9.prchtrg         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[9].prchtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch9.prchctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[9].prchctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch9.prchrs          = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[9].prchrs );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch9.praxctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[9].praxctl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch9.prchintenb      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[9].prchintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch9.prchintflg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[9].prchintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch9.prchbresp       = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[9].prchbresp );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch9.prsa            = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[9].prsa );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch9.prlsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[9].prlsize );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch9.prvsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[9].prvsize );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].prch9.prhsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[9].prhsize );
		// MONI-0
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].moni0.monitrg         = %x\n", (kuint)&ioPro.imgPipe[2].sro.moni0.monitrg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].moni0.monictl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.moni0.monictl );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].moni0.moniintflg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.moni0.moniintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].moni0.moniintenb      = %x\n", (kuint)&ioPro.imgPipe[2].sro.moni0.moniintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].moni0.monivd          = %x\n", (kuint)&ioPro.imgPipe[2].sro.moni0.monivd );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].moni0.monihd          = %x\n", (kuint)&ioPro.imgPipe[2].sro.moni0.monihd );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].moni0.moniepf         = %x\n", (kuint)&ioPro.imgPipe[2].sro.moni0.moniepf );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].moni0.monieplmin      = %x\n", (kuint)&ioPro.imgPipe[2].sro.moni0.monieplmin );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].moni0.monieplmax      = %x\n", (kuint)&ioPro.imgPipe[2].sro.moni0.monieplmax );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].moni0.moniblf         = %x\n", (kuint)&ioPro.imgPipe[2].sro.moni0.moniblf );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].moni0.monibllmin      = %x\n", (kuint)&ioPro.imgPipe[2].sro.moni0.monibllmin );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].moni0.monibllmax      = %x\n", (kuint)&ioPro.imgPipe[2].sro.moni0.monibllmax );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].moni0.monihdexp       = %x\n", (kuint)&ioPro.imgPipe[2].sro.moni0.monihdexp );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].moni0.moniepfexp      = %x\n", (kuint)&ioPro.imgPipe[2].sro.moni0.moniepfexp );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].moni0.monibllminexp   = %x\n", (kuint)&ioPro.imgPipe[2].sro.moni0.monibllminexp );
		CheckHeaderMain_RS_PRINTF("ioPro.sro[3].moni0.monibllmaxexp   = %x\n", (kuint)&ioPro.imgPipe[2].sro.moni0.monibllmaxexp );
	}
#endif	/** SRO Unit(pipe[3]) **/
#endif
}

ProTest5 *pro_test5_new()
{
	ProTest5 *self = g_object_new(PRO_TYPE_TEST5, NULL);

	return self;
}
