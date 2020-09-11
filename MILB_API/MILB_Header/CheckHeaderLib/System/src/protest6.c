/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-03
*@author              :申雨
*@brief               :sns 索喜rtos
*@rely                :klib
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
#include "chiptop.h"
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
#include "protest6.h"


K_TYPE_DEFINE_WITH_PRIVATE(ProTest6, pro_test6);
#define PRO_TEST6_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ProTest6Private, PRO_TYPE_TEST6))


struct _ProTest6Private
{
	kint a;
};
/*
 * IMPL
 */
static void pro_test6_constructor(ProTest6 *self)
{
	ProTest6Private *priv = PRO_TEST6_GET_PRIVATE(self);

	priv->a = 0;
}

static void pro_test6_destructor(ProTest6 *self)
{
	ProTest6Private *priv = PRO_TEST6_GET_PRIVATE(self);

	priv->a = 0;
}
/*
 * PUBLIC
 */
void pro_test6(ProTest6 *self, EProBlockType type, IoPro ioPro)
{
#if 0
#ifdef D_ENABLE_IO_PRO_B2B_PIPE_1	/** B2B Unit(pipe[1]) **/
	if(type == IntErnals_E_PRO_BLOCK_TYPE_B2B1) {
		// B2BTOP
		IntErnals_RS_printf("b2b[1]\n");
		IntErnals_RS_printf("ioPro.b2b[1].b2btop.sr           = %x\n", (kuint)&ioPro.imgPipe[0].b2b.b2btop.sr );
		IntErnals_RS_printf("ioPro.b2b[1].b2btop.clkstp       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.b2btop.clkstp );
		IntErnals_RS_printf("ioPro.b2b[1].b2btop.b2btopctl1   = %x\n", (kuint)&ioPro.imgPipe[0].b2b.b2btop.b2btopctl1 );
		IntErnals_RS_printf("ioPro.b2b[1].b2btop.b2btopctl2   = %x\n", (kuint)&ioPro.imgPipe[0].b2b.b2btop.b2btopctl2 );
		IntErnals_RS_printf("ioPro.b2b[1].b2btop.intmon1      = %x\n", (kuint)&ioPro.imgPipe[0].b2b.b2btop.intmon1 );
		IntErnals_RS_printf("ioPro.b2b[1].b2btop.intmon2      = %x\n", (kuint)&ioPro.imgPipe[0].b2b.b2btop.intmon2 );
		IntErnals_RS_printf("ioPro.b2b[1].b2btop.intctl       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.b2btop.intctl );
		IntErnals_RS_printf("ioPro.b2b[1].b2btop.vhdintenb    = %x\n", (kuint)&ioPro.imgPipe[0].b2b.b2btop.vhdintenb );
		IntErnals_RS_printf("ioPro.b2b[1].b2btop.vhdintflg    = %x\n", (kuint)&ioPro.imgPipe[0].b2b.b2btop.vhdintflg );
		IntErnals_RS_printf("ioPro.b2b[1].b2btop.vhset        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.b2btop.vhset );
		IntErnals_RS_printf("ioPro.b2b[1].b2btop.vmivadr      = %x\n", (kuint)&ioPro.imgPipe[0].b2b.b2btop.vmivadr );
		IntErnals_RS_printf("ioPro.b2b[1].b2btop.vmihadr      = %x\n", (kuint)&ioPro.imgPipe[0].b2b.b2btop.vmihadr );
		IntErnals_RS_printf("ioPro.b2b[1].b2btop.hmihadr      = %x\n", (kuint)&ioPro.imgPipe[0].b2b.b2btop.hmihadr );
		// PG
		IntErnals_RS_printf("ioPro.b2b[1].pg.pgtrg            = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pg.pgtrg );
		IntErnals_RS_printf("ioPro.b2b[1].pg.pgctl            = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pg.pgctl );
		IntErnals_RS_printf("ioPro.b2b[1].pg.pgvw             = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pg.pgvw );
		IntErnals_RS_printf("ioPro.b2b[1].pg.pghw             = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pg.pghw );
		IntErnals_RS_printf("ioPro.b2b[1].pg.pgvblnk          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pg.pgvblnk );
		IntErnals_RS_printf("ioPro.b2b[1].pg.pghblnk          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pg.pghblnk );
		IntErnals_RS_printf("ioPro.b2b[1].pg.pgvdhdblnk       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pg.pgvdhdblnk );
		// PGAIN1
		IntErnals_RS_printf("ioPro.b2b[1].pgain1.pgaintrg     = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pgain1.pgaintrg );
		IntErnals_RS_printf("ioPro.b2b[1].pgain1.pgainr       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pgain1.pgainr );
		IntErnals_RS_printf("ioPro.b2b[1].pgain1.pgaingr      = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pgain1.pgaingr );
		IntErnals_RS_printf("ioPro.b2b[1].pgain1.pgaingb      = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pgain1.pgaingb );
		IntErnals_RS_printf("ioPro.b2b[1].pgain1.pgainb       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pgain1.pgainb );
		IntErnals_RS_printf("ioPro.b2b[1].pgain1.pofsr        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pgain1.pofsr );
		IntErnals_RS_printf("ioPro.b2b[1].pgain1.pofsgr       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pgain1.pofsgr );
		IntErnals_RS_printf("ioPro.b2b[1].pgain1.pofsgb       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pgain1.pofsgb );
		IntErnals_RS_printf("ioPro.b2b[1].pgain1.pofsb        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pgain1.pofsb );
		// PZSFTA1
		IntErnals_RS_printf("ioPro.b2b[1].pzsfta1.pzsfttrg    = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pzsfta1.pzsfttrg );
		IntErnals_RS_printf("ioPro.b2b[1].pzsfta1.pzofst      = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pzsfta1.pzofst );
		// ELF
		IntErnals_RS_printf("ioPro.b2b[1].elf.elftrg          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.elftrg );
		IntErnals_RS_printf("ioPro.b2b[1].elf.nsltrg          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.nsltrg );
		IntErnals_RS_printf("ioPro.b2b[1].elf.elfpaen         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.elfpaen );
		IntErnals_RS_printf("ioPro.b2b[1].elf.elfgwp          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.elfgwp );
		IntErnals_RS_printf("ioPro.b2b[1].elf.elfgws          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.elfgws );
		IntErnals_RS_printf("ioPro.b2b[1].elf.elfwp           = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.elfwp );
		IntErnals_RS_printf("ioPro.b2b[1].elf.elfws           = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.elfws );
		IntErnals_RS_printf("ioPro.b2b[1].elf.elfctl          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.elfctl );
		IntErnals_RS_printf("ioPro.b2b[1].elf.elfzp           = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.elfzp );
		IntErnals_RS_printf("ioPro.b2b[1].elf.elfl            = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.elfl );
		IntErnals_RS_printf("ioPro.b2b[1].elf.anbor           = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.anbor );
		IntErnals_RS_printf("ioPro.b2b[1].elf.anbkr           = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.anbkr );
		IntErnals_RS_printf("ioPro.b2b[1].elf.anbdr           = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.anbdr );
		IntErnals_RS_printf("ioPro.b2b[1].elf.anbog           = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.anbog );
		IntErnals_RS_printf("ioPro.b2b[1].elf.anbkg           = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.anbkg );
		IntErnals_RS_printf("ioPro.b2b[1].elf.anbdg           = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.anbdg );
		IntErnals_RS_printf("ioPro.b2b[1].elf.anbob           = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.anbob );
		IntErnals_RS_printf("ioPro.b2b[1].elf.anbkb           = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.anbkb );
		IntErnals_RS_printf("ioPro.b2b[1].elf.anbdb           = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.anbdb );
		IntErnals_RS_printf("ioPro.b2b[1].elf.lgtw            = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.lgtw );
		IntErnals_RS_printf("ioPro.b2b[1].elf.lgt             = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.lgt );
		IntErnals_RS_printf("ioPro.b2b[1].elf.lgte            = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.lgte );
		IntErnals_RS_printf("ioPro.b2b[1].elf.edg2anba        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.edg2anba );
		IntErnals_RS_printf("ioPro.b2b[1].elf.edgscla         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.edgscla );
		IntErnals_RS_printf("ioPro.b2b[1].elf.edg2anbb        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.edg2anbb );
		IntErnals_RS_printf("ioPro.b2b[1].elf.edgsclb         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.edgsclb );
		IntErnals_RS_printf("ioPro.b2b[1].elf.edg2anbc        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.edg2anbc );
		IntErnals_RS_printf("ioPro.b2b[1].elf.edgsclc         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.edgsclc );
		IntErnals_RS_printf("ioPro.b2b[1].elf.efth            = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.efth );
		IntErnals_RS_printf("ioPro.b2b[1].elf.lfth            = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.lfth );
		IntErnals_RS_printf("ioPro.b2b[1].elf.elcome          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.elcome );
		IntErnals_RS_printf("ioPro.b2b[1].elf.elcomen         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.elcomen );
		IntErnals_RS_printf("ioPro.b2b[1].elf.a1s5e           = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.a1s5e );
		IntErnals_RS_printf("ioPro.b2b[1].elf.a1s5l1          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.a1s5l1 );
		IntErnals_RS_printf("ioPro.b2b[1].elf.a1s5l2          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.a1s5l2 );
		IntErnals_RS_printf("ioPro.b2b[1].elf.a1s5l3          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.a1s5l3 );
		IntErnals_RS_printf("ioPro.b2b[1].elf.a1s5l4          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.a1s5l4 );
		IntErnals_RS_printf("ioPro.b2b[1].elf.nr1s5rgb        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.nr1s5rgb );
		IntErnals_RS_printf("ioPro.b2b[1].elf.ns1s5lm         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.ns1s5lm );
		IntErnals_RS_printf("ioPro.b2b[1].elf.a5s9e           = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.a5s9e );
		IntErnals_RS_printf("ioPro.b2b[1].elf.a5s9l1          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.a5s9l1 );
		IntErnals_RS_printf("ioPro.b2b[1].elf.a5s9l2          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.a5s9l2 );
		IntErnals_RS_printf("ioPro.b2b[1].elf.a5s9l3          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.a5s9l3 );
		IntErnals_RS_printf("ioPro.b2b[1].elf.a5s9l4          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.a5s9l4 );
		IntErnals_RS_printf("ioPro.b2b[1].elf.nr5s9rgb        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.nr5s9rgb );
		IntErnals_RS_printf("ioPro.b2b[1].elf.ns5s9lm         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.ns5s9lm );
		IntErnals_RS_printf("ioPro.b2b[1].elf.fs9w            = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.fs9w );
		IntErnals_RS_printf("ioPro.b2b[1].elf.fs9yc           = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.fs9yc );
		IntErnals_RS_printf("ioPro.b2b[1].elf.fastr           = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.fastr );
		IntErnals_RS_printf("ioPro.b2b[1].elf.crvaf           = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.crvaf );
		IntErnals_RS_printf("ioPro.b2b[1].elf.fcrvabtof       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.fcrvabtof );
		IntErnals_RS_printf("ioPro.b2b[1].elf.fcrvabtga       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.fcrvabtga );
		IntErnals_RS_printf("ioPro.b2b[1].elf.fcrvabtbd       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.fcrvabtbd );
		IntErnals_RS_printf("ioPro.b2b[1].elf.fcrvabtcp       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.fcrvabtcp );
		IntErnals_RS_printf("ioPro.b2b[1].elf.fyabtga         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.fyabtga );
		IntErnals_RS_printf("ioPro.b2b[1].elf.fyabtga         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.fyabtga );
		IntErnals_RS_printf("ioPro.b2b[1].elf.fyabtclp        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.fyabtclp );
		IntErnals_RS_printf("ioPro.b2b[1].elf.faehh           = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.faehh );
		IntErnals_RS_printf("ioPro.b2b[1].elf.fbstr           = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.fbstr );
		IntErnals_RS_printf("ioPro.b2b[1].elf.crvbf           = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.crvbf );
		IntErnals_RS_printf("ioPro.b2b[1].elf.fcrvbbtof       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.fcrvbbtof );
		IntErnals_RS_printf("ioPro.b2b[1].elf.fcrvbbtga       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.fcrvbbtga );
		IntErnals_RS_printf("ioPro.b2b[1].elf.fcrvbbtbd       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.fcrvbbtbd );
		IntErnals_RS_printf("ioPro.b2b[1].elf.fcrvbbtcp       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.fcrvbbtcp );
		IntErnals_RS_printf("ioPro.b2b[1].elf.fybbtga         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.fybbtga );
		IntErnals_RS_printf("ioPro.b2b[1].elf.fybbtbd         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.fybbtbd );
		IntErnals_RS_printf("ioPro.b2b[1].elf.fybbtclp        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.fybbtclp );
		IntErnals_RS_printf("ioPro.b2b[1].elf.fbehh           = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.fbehh );
		IntErnals_RS_printf("ioPro.b2b[1].elf.elfmnnrrl       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.elfmnnrrl );
		IntErnals_RS_printf("ioPro.b2b[1].elf.elfmnnrgl       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.elfmnnrgl );
		IntErnals_RS_printf("ioPro.b2b[1].elf.elfmnnrbl       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.elfmnnrbl );
		IntErnals_RS_printf("ioPro.b2b[1].elf.elfafnr         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.elfafnr );
		IntErnals_RS_printf("ioPro.b2b[1].elf.zeladcmd        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.zeladcmd );
		IntErnals_RS_printf("ioPro.b2b[1].elf.zanbor          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.zanbor );
		IntErnals_RS_printf("ioPro.b2b[1].elf.zanbkr          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.zanbkr );
		IntErnals_RS_printf("ioPro.b2b[1].elf.zanbdr          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.zanbdr );
		IntErnals_RS_printf("ioPro.b2b[1].elf.zanbog          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.zanbog );
		IntErnals_RS_printf("ioPro.b2b[1].elf.zanbkg          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.zanbkg );
		IntErnals_RS_printf("ioPro.b2b[1].elf.zanbdg          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.zanbdg );
		IntErnals_RS_printf("ioPro.b2b[1].elf.zanbdb          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.zanbdb );
		IntErnals_RS_printf("ioPro.b2b[1].elf.zanbkb          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.zanbkb );
		IntErnals_RS_printf("ioPro.b2b[1].elf.zanbkb          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.zanbkb );
		IntErnals_RS_printf("ioPro.b2b[1].elf.zanbdb          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.zanbdb );
		IntErnals_RS_printf("ioPro.b2b[1].elf.zlgtw           = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.zlgtw );
		IntErnals_RS_printf("ioPro.b2b[1].elf.zlgt            = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.zlgt );
		IntErnals_RS_printf("ioPro.b2b[1].elf.zlgte           = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.zlgte );
		IntErnals_RS_printf("ioPro.b2b[1].elf.zedg2anba       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.zedg2anba );
		IntErnals_RS_printf("ioPro.b2b[1].elf.zedgscla        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.zedgscla );
		IntErnals_RS_printf("ioPro.b2b[1].elf.zedg2anbb       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.zedg2anbb );
		IntErnals_RS_printf("ioPro.b2b[1].elf.zedgsclb        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.zedgsclb );
		IntErnals_RS_printf("ioPro.b2b[1].elf.zalnge          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.zalnge );
		IntErnals_RS_printf("ioPro.b2b[1].elf.zalng           = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.zalng );
		IntErnals_RS_printf("ioPro.b2b[1].elf.zlfth           = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.zlfth );
		IntErnals_RS_printf("ioPro.b2b[1].elf.zlcome          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.zlcome );
		IntErnals_RS_printf("ioPro.b2b[1].elf.zlcomen         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.zlcomen );
		IntErnals_RS_printf("ioPro.b2b[1].elf.znslnglm        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.elf.znslnglm );
		// PZSFTA2
		IntErnals_RS_printf("ioPro.b2b[1].pzsfta2.pzsfttrg    = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pzsfta2.pzsfttrg );
		IntErnals_RS_printf("ioPro.b2b[1].pzsfta2.pzofst      = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pzsfta2.pzofst );
		// PZSFTA2A
		IntErnals_RS_printf("ioPro.b2b[1].pzsfta2a.pzsfttrg   = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pzsfta2a.pzsfttrg );
		IntErnals_RS_printf("ioPro.b2b[1].pzsfta2a.pzofst     = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pzsfta2a.pzofst );
		// FSHD
		IntErnals_RS_printf("ioPro.b2b[1].fshd.fshdtrg        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.fshd.fshdtrg );
		IntErnals_RS_printf("ioPro.b2b[1].fshd.fshdpaen       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.fshd.fshdpaen );
		IntErnals_RS_printf("ioPro.b2b[1].fshd.fshdctl        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.fshd.fshdctl );
		IntErnals_RS_printf("ioPro.b2b[1].fshd.fshdv          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.fshd.fshdv );
		IntErnals_RS_printf("ioPro.b2b[1].fshd.fshdh          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.fshd.fshdh );
		IntErnals_RS_printf("ioPro.b2b[1].fshd.fshdvw         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.fshd.fshdvw );
		IntErnals_RS_printf("ioPro.b2b[1].fshd.fshdhw         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.fshd.fshdhw );
		IntErnals_RS_printf("ioPro.b2b[1].fshd.fshdhwph       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.fshd.fshdhwph );
		IntErnals_RS_printf("ioPro.b2b[1].fshd.fshdbc         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.fshd.fshdbc );
		IntErnals_RS_printf("ioPro.b2b[1].fshd.fsul1          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.fshd.fsul1 );
		IntErnals_RS_printf("ioPro.b2b[1].fshd.fsul2          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.fshd.fsul2 );
		IntErnals_RS_printf("ioPro.b2b[1].fshd.fsctl          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.fshd.fsctl );
		IntErnals_RS_printf("ioPro.b2b[1].fshd.fssubpr        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.fshd.fssubpr );
		IntErnals_RS_printf("ioPro.b2b[1].fshd.fssubsp        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.fshd.fssubsp );
		IntErnals_RS_printf("ioPro.b2b[1].fshd.fssubdr        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.fshd.fssubdr );
		IntErnals_RS_printf("ioPro.b2b[1].fshd.fssubst        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.fshd.fssubst );
		IntErnals_RS_printf("ioPro.b2b[1].fshd.fsa1           = %x\n", (kuint)&ioPro.imgPipe[0].b2b.fshd.fsa1 );
		IntErnals_RS_printf("ioPro.b2b[1].fshd.fsa2           = %x\n", (kuint)&ioPro.imgPipe[0].b2b.fshd.fsa2 );
		IntErnals_RS_printf("ioPro.b2b[1].fshd.csctl1         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.fshd.csctl1 );
		IntErnals_RS_printf("ioPro.b2b[1].fshd.csctl2         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.fshd.csctl2 );
		IntErnals_RS_printf("ioPro.b2b[1].fshd.cstblst        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.fshd.cstblst );
		IntErnals_RS_printf("ioPro.b2b[1].fshd.cstbls1        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.fshd.cstbls1 );
		IntErnals_RS_printf("ioPro.b2b[1].fshd.cstbls2        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.fshd.cstbls2 );
		IntErnals_RS_printf("ioPro.b2b[1].fshd.cshdd          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.fshd.cshdd );
		IntErnals_RS_printf("ioPro.b2b[1].fshd.cshdoa         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.fshd.cshdoa );
		IntErnals_RS_printf("ioPro.b2b[1].fshd.csa1           = %x\n", (kuint)&ioPro.imgPipe[0].b2b.fshd.csa1 );
		IntErnals_RS_printf("ioPro.b2b[1].fshd.csa2           = %x\n", (kuint)&ioPro.imgPipe[0].b2b.fshd.csa2 );
		IntErnals_RS_printf("ioPro.b2b[1].fshd.fswric         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.fshd.fswric );
		// PGAIN2
		IntErnals_RS_printf("ioPro.b2b[1].pgain2.pgaintrg     = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pgain2.pgaintrg );
		IntErnals_RS_printf("ioPro.b2b[1].pgain2.pgainr       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pgain2.pgainr );
		IntErnals_RS_printf("ioPro.b2b[1].pgain2.pgaingr      = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pgain2.pgaingr );
		IntErnals_RS_printf("ioPro.b2b[1].pgain2.pgaingb      = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pgain2.pgaingb );
		IntErnals_RS_printf("ioPro.b2b[1].pgain2.pgainb       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pgain2.pgainb );
		IntErnals_RS_printf("ioPro.b2b[1].pgain2.pofsr        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pgain2.pofsr );
		IntErnals_RS_printf("ioPro.b2b[1].pgain2.pofsgr       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pgain2.pofsgr );
		IntErnals_RS_printf("ioPro.b2b[1].pgain2.pofsgb       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pgain2.pofsgb );
		IntErnals_RS_printf("ioPro.b2b[1].pgain2.pofsb        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pgain2.pofsb );
		// P2M-0
		IntErnals_RS_printf("ioPro.b2b[1].p2m0.p2mtrg         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.p2m[0].p2mtrg );
		IntErnals_RS_printf("ioPro.b2b[1].p2m0.p2mpaen        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.p2m[0].p2mpaen );
		IntErnals_RS_printf("ioPro.b2b[1].p2m0.p2mctl         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.p2m[0].p2mctl );
		IntErnals_RS_printf("ioPro.b2b[1].p2m0.p2mofs         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.p2m[0].p2mofs );
		IntErnals_RS_printf("ioPro.b2b[1].p2m0.pbsft          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.p2m[0].pbsft );
		IntErnals_RS_printf("ioPro.b2b[1].p2m0.pclph          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.p2m[0].pclph );
		IntErnals_RS_printf("ioPro.b2b[1].p2m0.ptrmv          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.p2m[0].ptrmv );
		IntErnals_RS_printf("ioPro.b2b[1].p2m0.ptrmh          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.p2m[0].ptrmh );
		IntErnals_RS_printf("ioPro.b2b[1].p2m0.ptrmvw         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.p2m[0].ptrmvw );
		IntErnals_RS_printf("ioPro.b2b[1].p2m0.ptrmhw         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.p2m[0].ptrmhw );
		IntErnals_RS_printf("ioPro.b2b[1].p2m0.ptrmxvcyc      = %x\n", (kuint)&ioPro.imgPipe[0].b2b.p2m[0].ptrmxvcyc );
		IntErnals_RS_printf("ioPro.b2b[1].p2m0.ptrmxhcyc      = %x\n", (kuint)&ioPro.imgPipe[0].b2b.p2m[0].ptrmxhcyc );
		IntErnals_RS_printf("ioPro.b2b[1].p2m0.ptrmxven       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.p2m[0].ptrmxven );
		IntErnals_RS_printf("ioPro.b2b[1].p2m0.ptrmxhen       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.p2m[0].ptrmxhen );
		IntErnals_RS_printf("ioPro.b2b[1].p2m0.p2mmir         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.p2m[0].p2mmir );
		// P2M-1
		IntErnals_RS_printf("ioPro.b2b[1].p2m1.p2mtrg         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.p2m[1].p2mtrg );
		IntErnals_RS_printf("ioPro.b2b[1].p2m1.p2mpaen        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.p2m[1].p2mpaen );
		IntErnals_RS_printf("ioPro.b2b[1].p2m1.p2mctl         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.p2m[1].p2mctl );
		IntErnals_RS_printf("ioPro.b2b[1].p2m1.p2mofs         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.p2m[1].p2mofs );
		IntErnals_RS_printf("ioPro.b2b[1].p2m1.pbsft          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.p2m[1].pbsft );
		IntErnals_RS_printf("ioPro.b2b[1].p2m1.pclph          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.p2m[1].pclph );
		IntErnals_RS_printf("ioPro.b2b[1].p2m1.ptrmv          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.p2m[1].ptrmv );
		IntErnals_RS_printf("ioPro.b2b[1].p2m1.ptrmh          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.p2m[1].ptrmh );
		IntErnals_RS_printf("ioPro.b2b[1].p2m1.ptrmvw         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.p2m[1].ptrmvw );
		IntErnals_RS_printf("ioPro.b2b[1].p2m1.ptrmhw         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.p2m[1].ptrmhw );
		IntErnals_RS_printf("ioPro.b2b[1].p2m1.ptrmxvcyc      = %x\n", (kuint)&ioPro.imgPipe[0].b2b.p2m[1].ptrmxvcyc );
		IntErnals_RS_printf("ioPro.b2b[1].p2m1.ptrmxhcyc      = %x\n", (kuint)&ioPro.imgPipe[0].b2b.p2m[1].ptrmxhcyc );
		IntErnals_RS_printf("ioPro.b2b[1].p2m1.ptrmxven       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.p2m[1].ptrmxven );
		IntErnals_RS_printf("ioPro.b2b[1].p2m1.ptrmxhen       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.p2m[1].ptrmxhen );
		IntErnals_RS_printf("ioPro.b2b[1].p2m1.p2mmir         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.p2m[1].p2mmir );
		// PWCH-0
		IntErnals_RS_printf("ioPro.b2b[1].pwch0.pwchtrg       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pwch[0].pwchtrg );
		IntErnals_RS_printf("ioPro.b2b[1].pwch0.pws           = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pwch[0].pws );
		IntErnals_RS_printf("ioPro.b2b[1].pwch0.pwaxctl       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pwch[0].pwaxctl );
		IntErnals_RS_printf("ioPro.b2b[1].pwch0.pwchCTL       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pwch[0].pwchctl );
		IntErnals_RS_printf("ioPro.b2b[1].pwch0.pwchintenb    = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pwch[0].pwchintenb );
		IntErnals_RS_printf("ioPro.b2b[1].pwch0.pwchintflg    = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pwch[0].pwchintflg );
		IntErnals_RS_printf("ioPro.b2b[1].pwch0.pwchbresp     = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pwch[0].pwchbresp );
		IntErnals_RS_printf("ioPro.b2b[1].pwch0.pwsa          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pwch[0].pwsa );
		IntErnals_RS_printf("ioPro.b2b[1].pwch0.pwlsize       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pwch[0].pwlsize );
		// PWCH-1
		IntErnals_RS_printf("ioPro.b2b[1].pwch1.pwchtrg       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pwch[1].pwchtrg );
		IntErnals_RS_printf("ioPro.b2b[1].pwch1.pws           = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pwch[1].pws );
		IntErnals_RS_printf("ioPro.b2b[1].pwch1.pwaxctl       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pwch[1].pwaxctl );
		IntErnals_RS_printf("ioPro.b2b[1].pwch1.pwchctl       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pwch[1].pwchctl );
		IntErnals_RS_printf("ioPro.b2b[1].pwch1.pwchintenb    = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pwch[1].pwchintenb );
		IntErnals_RS_printf("ioPro.b2b[1].pwch1.pwchintflg    = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pwch[1].pwchintflg );
		IntErnals_RS_printf("ioPro.b2b[1].pwch1.pwchbresp     = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pwch[1].pwchbresp );
		IntErnals_RS_printf("ioPro.b2b[1].pwch1.pwsa          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pwch[1].pwsa );
		IntErnals_RS_printf("ioPro.b2b[1].pwch1.pwlsize       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.pwch[1].pwlsize );
		// M2P-0
		IntErnals_RS_printf("ioPro.b2b[1].m2p0.m2ptrg         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.m2p[0].m2ptrg );
		IntErnals_RS_printf("ioPro.b2b[1].m2p0.m2ppaen        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.m2p[0].m2ppaen );
		IntErnals_RS_printf("ioPro.b2b[1].m2p0.m2pctl         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.m2p[0].m2pctl );
		IntErnals_RS_printf("ioPro.b2b[1].m2p0.m2pbsft        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.m2p[0].m2pbsft );
		IntErnals_RS_printf("ioPro.b2b[1].m2p0.m2pofs         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.m2p[0].m2pofs );
		IntErnals_RS_printf("ioPro.b2b[1].m2p0.m2pclip        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.m2p[0].m2pclip );
		// M2P-1
		IntErnals_RS_printf("ioPro.b2b[1].m2p1.m2ptrg         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.m2p[1].m2ptrg );
		IntErnals_RS_printf("ioPro.b2b[1].m2p1.m2ppaen        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.m2p[1].m2ppaen );
		IntErnals_RS_printf("ioPro.b2b[1].m2p1.m2pctl         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.m2p[1].m2pctl );
		IntErnals_RS_printf("ioPro.b2b[1].m2p1.m2pbsft        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.m2p[1].m2pbsft );
		IntErnals_RS_printf("ioPro.b2b[1].m2p1.m2pofs         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.m2p[1].m2pofs );
		IntErnals_RS_printf("ioPro.b2b[1].m2p1.m2pclip        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.m2p[1].m2pclip );
		// M2P-2
		IntErnals_RS_printf("ioPro.b2b[1].m2p2.m2ptrg         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.m2p[2].m2ptrg );
		IntErnals_RS_printf("ioPro.b2b[1].m2p2.m2ppaen        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.m2p[2].m2ppaen );
		IntErnals_RS_printf("ioPro.b2b[1].m2p2.m2pctl         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.m2p[2].m2pctl );
		IntErnals_RS_printf("ioPro.b2b[1].m2p2.m2pbsft        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.m2p[2].m2pbsft );
		IntErnals_RS_printf("ioPro.b2b[1].m2p2.m2pofs         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.m2p[2].m2pofs );
		IntErnals_RS_printf("ioPro.b2b[1].m2p2.m2pclip        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.m2p[2].m2pclip );
		// M2P-3
		IntErnals_RS_printf("ioPro.b2b[1].m2p3.m2ptrg         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.m2p[3].m2ptrg );
		IntErnals_RS_printf("ioPro.b2b[1].m2p3.m2ppaen        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.m2p[3].m2ppaen );
		IntErnals_RS_printf("ioPro.b2b[1].m2p3.m2pctl         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.m2p[3].m2pctl );
		IntErnals_RS_printf("ioPro.b2b[1].m2p3.m2pbsft        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.m2p[3].m2pbsft );
		IntErnals_RS_printf("ioPro.b2b[1].m2p3.m2pofs         = %x\n", (kuint)&ioPro.imgPipe[0].b2b.m2p[3].m2pofs );
		IntErnals_RS_printf("ioPro.b2b[1].m2p3.m2pclip        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.m2p[3].m2pclip );
		// PRCH-0
		IntErnals_RS_printf("ioPro.b2b[1].prch0.prchtrg       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[0].prchtrg );
		IntErnals_RS_printf("ioPro.b2b[1].prch0.prchctl       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[0].prchctl );
		IntErnals_RS_printf("ioPro.b2b[1].prch0.prchrs        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[0].prchrs );
		IntErnals_RS_printf("ioPro.b2b[1].prch0.praxctl       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[0].praxctl );
		IntErnals_RS_printf("ioPro.b2b[1].prch0.prchintenb    = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[0].prchintenb );
		IntErnals_RS_printf("ioPro.b2b[1].prch0.prchintflg    = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[0].prchintflg );
		IntErnals_RS_printf("ioPro.b2b[1].prch0.prchbresp     = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[0].prchbresp );
		IntErnals_RS_printf("ioPro.b2b[1].prch0.prsa          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[0].prsa );
		IntErnals_RS_printf("ioPro.b2b[1].prch0.prlsize       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[0].prlsize );
		IntErnals_RS_printf("ioPro.b2b[1].prch0.prvsize       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[0].prvsize );
		IntErnals_RS_printf("ioPro.b2b[1].prch0.prhsize       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[0].prhsize );
		// PRCH-1
		IntErnals_RS_printf("ioPro.b2b[1].prch1.prchtrg       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[1].prchtrg );
		IntErnals_RS_printf("ioPro.b2b[1].prch1.prchctl       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[1].prchctl );
		IntErnals_RS_printf("ioPro.b2b[1].prch1.prchrs        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[1].prchrs );
		IntErnals_RS_printf("ioPro.b2b[1].prch1.praxctl       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[1].praxctl );
		IntErnals_RS_printf("ioPro.b2b[1].prch1.prchintenb    = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[1].prchintenb );
		IntErnals_RS_printf("ioPro.b2b[1].prch1.prchintflg    = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[1].prchintflg );
		IntErnals_RS_printf("ioPro.b2b[1].prch1.prchbresp     = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[1].prchbresp );
		IntErnals_RS_printf("ioPro.b2b[1].prch1.prsa          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[1].prsa );
		IntErnals_RS_printf("ioPro.b2b[1].prch1.prlsize       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[1].prlsize );
		IntErnals_RS_printf("ioPro.b2b[1].prch1.prvsize       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[1].prvsize );
		IntErnals_RS_printf("ioPro.b2b[1].prch1.prhsize       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[1].prhsize );
		// PRCH-2
		IntErnals_RS_printf("ioPro.b2b[1].prch2.prchtrg       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[2].prchtrg );
		IntErnals_RS_printf("ioPro.b2b[1].prch2.prchctl       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[2].prchctl );
		IntErnals_RS_printf("ioPro.b2b[1].prch2.prchrs        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[2].prchrs );
		IntErnals_RS_printf("ioPro.b2b[1].prch2.praxctl       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[2].praxctl );
		IntErnals_RS_printf("ioPro.b2b[1].prch2.prchintenb    = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[2].prchintenb );
		IntErnals_RS_printf("ioPro.b2b[1].prch2.prchintflg    = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[2].prchintflg );
		IntErnals_RS_printf("ioPro.b2b[1].prch2.prchbresp     = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[2].prchbresp );
		IntErnals_RS_printf("ioPro.b2b[1].prch2.prsa          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[2].prsa );
		IntErnals_RS_printf("ioPro.b2b[1].prch2.prlsize       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[2].prlsize );
		IntErnals_RS_printf("ioPro.b2b[1].prch2.prvsize       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[2].prvsize );
		IntErnals_RS_printf("ioPro.b2b[1].prch2.prhsize       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[2].prhsize );
		// PRCH-3
		IntErnals_RS_printf("ioPro.b2b[1].prch3.prchtrg       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[3].prchtrg );
		IntErnals_RS_printf("ioPro.b2b[1].prch3.prchctl       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[3].prchctl );
		IntErnals_RS_printf("ioPro.b2b[1].prch3.prchrs        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[3].prchrs );
		IntErnals_RS_printf("ioPro.b2b[1].prch3.praxctl       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[3].praxctl );
		IntErnals_RS_printf("ioPro.b2b[1].prch3.prchintenb    = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[3].prchintenb );
		IntErnals_RS_printf("ioPro.b2b[1].prch3.prchintflg    = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[3].prchintflg );
		IntErnals_RS_printf("ioPro.b2b[1].prch3.prchbresp     = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[3].prchbresp );
		IntErnals_RS_printf("ioPro.b2b[1].prch3.prsa          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[3].prsa );
		IntErnals_RS_printf("ioPro.b2b[1].prch3.prlsize       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[3].prlsize );
		IntErnals_RS_printf("ioPro.b2b[1].prch3.prvsize       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[3].prvsize );
		IntErnals_RS_printf("ioPro.b2b[1].prch3.prhsize       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[3].prhsize );
		// PRCH-4
		IntErnals_RS_printf("ioPro.b2b[1].prch4.prchtrg       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[4].prchtrg );
		IntErnals_RS_printf("ioPro.b2b[1].prch4.prchctl       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[4].prchctl );
		IntErnals_RS_printf("ioPro.b2b[1].prch4.prchrs        = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[4].prchrs );
		IntErnals_RS_printf("ioPro.b2b[1].prch4.praxctl       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[4].praxctl );
		IntErnals_RS_printf("ioPro.b2b[1].prch4.prchintenb    = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[4].prchintenb );
		IntErnals_RS_printf("ioPro.b2b[1].prch4.prchintflg    = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[4].prchintflg );
		IntErnals_RS_printf("ioPro.b2b[1].prch4.prchbresp     = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[4].prchbresp );
		IntErnals_RS_printf("ioPro.b2b[1].prch4.prsa          = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[4].prsa );
		IntErnals_RS_printf("ioPro.b2b[1].prch4.prlsize       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[4].prlsize );
		IntErnals_RS_printf("ioPro.b2b[1].prch4.prvsize       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[4].prvsize );
		IntErnals_RS_printf("ioPro.b2b[1].prch4.prhsize       = %x\n", (kuint)&ioPro.imgPipe[0].b2b.prch[4].prhsize );
	}
#endif	/** B2B Unit(pipe[1]) **/

#ifdef D_ENABLE_IO_PRO_B2B_PIPE_2	/** B2B Unit(pipe[2]) **/
	if(type == IntErnals_E_PRO_BLOCK_TYPE_B2B2) {
		// B2BTOP
		IntErnals_RS_printf("b2b[2]\n");
		IntErnals_RS_printf("ioPro.b2b[2].b2btop.sr           = %x\n", (kuint)&ioPro.imgPipe[1].b2b.b2btop.sr );
		IntErnals_RS_printf("ioPro.b2b[2].b2btop.clkstp       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.b2btop.clkstp );
		IntErnals_RS_printf("ioPro.b2b[2].b2btop.b2btopctl1   = %x\n", (kuint)&ioPro.imgPipe[1].b2b.b2btop.b2btopctl1 );
		IntErnals_RS_printf("ioPro.b2b[2].b2btop.b2btopctl2   = %x\n", (kuint)&ioPro.imgPipe[1].b2b.b2btop.b2btopctl2 );
		IntErnals_RS_printf("ioPro.b2b[2].b2btop.intmon1      = %x\n", (kuint)&ioPro.imgPipe[1].b2b.b2btop.intmon1 );
		IntErnals_RS_printf("ioPro.b2b[2].b2btop.intmon2      = %x\n", (kuint)&ioPro.imgPipe[1].b2b.b2btop.intmon2 );
		IntErnals_RS_printf("ioPro.b2b[2].b2btop.intctl       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.b2btop.intctl );
		IntErnals_RS_printf("ioPro.b2b[2].b2btop.vhdintenb    = %x\n", (kuint)&ioPro.imgPipe[1].b2b.b2btop.vhdintenb );
		IntErnals_RS_printf("ioPro.b2b[2].b2btop.vhdintflg    = %x\n", (kuint)&ioPro.imgPipe[1].b2b.b2btop.vhdintflg );
		IntErnals_RS_printf("ioPro.b2b[2].b2btop.vhset        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.b2btop.vhset );
		IntErnals_RS_printf("ioPro.b2b[2].b2btop.vmivadr      = %x\n", (kuint)&ioPro.imgPipe[1].b2b.b2btop.vmivadr );
		IntErnals_RS_printf("ioPro.b2b[2].b2btop.vmihadr      = %x\n", (kuint)&ioPro.imgPipe[1].b2b.b2btop.vmihadr );
		IntErnals_RS_printf("ioPro.b2b[2].b2btop.hmihadr      = %x\n", (kuint)&ioPro.imgPipe[1].b2b.b2btop.hmihadr );
		// PG
		IntErnals_RS_printf("ioPro.b2b[2].pg.pgtrg            = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pg.pgtrg );
		IntErnals_RS_printf("ioPro.b2b[2].pg.pgctl            = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pg.pgctl );
		IntErnals_RS_printf("ioPro.b2b[2].pg.pgvw             = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pg.pgvw );
		IntErnals_RS_printf("ioPro.b2b[2].pg.pghw             = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pg.pghw );
		IntErnals_RS_printf("ioPro.b2b[2].pg.pgvblnk          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pg.pgvblnk );
		IntErnals_RS_printf("ioPro.b2b[2].pg.pghblnk          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pg.pghblnk );
		IntErnals_RS_printf("ioPro.b2b[2].pg.pgvdhdblnk       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pg.pgvdhdblnk );
		// PGAIN1
		IntErnals_RS_printf("ioPro.b2b[2].pgain1.pgaintrg     = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pgain1.pgaintrg );
		IntErnals_RS_printf("ioPro.b2b[2].pgain1.pgainr       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pgain1.pgainr );
		IntErnals_RS_printf("ioPro.b2b[2].pgain1.pgaingr      = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pgain1.pgaingr );
		IntErnals_RS_printf("ioPro.b2b[2].pgain1.pgaingb      = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pgain1.pgaingb );
		IntErnals_RS_printf("ioPro.b2b[2].pgain1.pgainb       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pgain1.pgainb );
		IntErnals_RS_printf("ioPro.b2b[2].pgain1.pofsr        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pgain1.pofsr );
		IntErnals_RS_printf("ioPro.b2b[2].pgain1.pofsgr       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pgain1.pofsgr );
		IntErnals_RS_printf("ioPro.b2b[2].pgain1.pofsgb       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pgain1.pofsgb );
		IntErnals_RS_printf("ioPro.b2b[2].pgain1.pofsb        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pgain1.pofsb );
		// PZSFTA1
		IntErnals_RS_printf("ioPro.b2b[2].pzsfta1.pzsfttrg    = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pzsfta1.pzsfttrg );
		IntErnals_RS_printf("ioPro.b2b[2].pzsfta1.pzofst      = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pzsfta1.pzofst );
		// ELF
		IntErnals_RS_printf("ioPro.b2b[2].elf.elftrg          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.elftrg );
		IntErnals_RS_printf("ioPro.b2b[2].elf.nsltrg          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.nsltrg );
		IntErnals_RS_printf("ioPro.b2b[2].elf.elfpaen         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.elfpaen );
		IntErnals_RS_printf("ioPro.b2b[2].elf.elfgwp          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.elfgwp );
		IntErnals_RS_printf("ioPro.b2b[2].elf.elfgws          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.elfgws );
		IntErnals_RS_printf("ioPro.b2b[2].elf.elfwp           = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.elfwp );
		IntErnals_RS_printf("ioPro.b2b[2].elf.elfws           = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.elfws );
		IntErnals_RS_printf("ioPro.b2b[2].elf.elfctl          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.elfctl );
		IntErnals_RS_printf("ioPro.b2b[2].elf.elfzp           = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.elfzp );
		IntErnals_RS_printf("ioPro.b2b[2].elf.elfl            = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.elfl );
		IntErnals_RS_printf("ioPro.b2b[2].elf.anbor           = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.anbor );
		IntErnals_RS_printf("ioPro.b2b[2].elf.anbkr           = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.anbkr );
		IntErnals_RS_printf("ioPro.b2b[2].elf.anbdr           = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.anbdr );
		IntErnals_RS_printf("ioPro.b2b[2].elf.anbog           = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.anbog );
		IntErnals_RS_printf("ioPro.b2b[2].elf.anbkg           = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.anbkg );
		IntErnals_RS_printf("ioPro.b2b[2].elf.anbdg           = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.anbdg );
		IntErnals_RS_printf("ioPro.b2b[2].elf.anbob           = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.anbob );
		IntErnals_RS_printf("ioPro.b2b[2].elf.anbkb           = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.anbkb );
		IntErnals_RS_printf("ioPro.b2b[2].elf.anbdb           = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.anbdb );
		IntErnals_RS_printf("ioPro.b2b[2].elf.lgtw            = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.lgtw );
		IntErnals_RS_printf("ioPro.b2b[2].elf.lgt             = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.lgt );
		IntErnals_RS_printf("ioPro.b2b[2].elf.lgte            = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.lgte );
		IntErnals_RS_printf("ioPro.b2b[2].elf.edg2anba        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.edg2anba );
		IntErnals_RS_printf("ioPro.b2b[2].elf.edgscla         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.edgscla );
		IntErnals_RS_printf("ioPro.b2b[2].elf.edg2anbb        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.edg2anbb );
		IntErnals_RS_printf("ioPro.b2b[2].elf.edgsclb         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.edgsclb );
		IntErnals_RS_printf("ioPro.b2b[2].elf.edg2anbc        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.edg2anbc );
		IntErnals_RS_printf("ioPro.b2b[2].elf.edgsclc         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.edgsclc );
		IntErnals_RS_printf("ioPro.b2b[2].elf.efth            = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.efth );
		IntErnals_RS_printf("ioPro.b2b[2].elf.lfth            = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.lfth );
		IntErnals_RS_printf("ioPro.b2b[2].elf.elcome          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.elcome );
		IntErnals_RS_printf("ioPro.b2b[2].elf.elcomen         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.elcomen );
		IntErnals_RS_printf("ioPro.b2b[2].elf.a1s5e           = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.a1s5e );
		IntErnals_RS_printf("ioPro.b2b[2].elf.a1s5l1          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.a1s5l1 );
		IntErnals_RS_printf("ioPro.b2b[2].elf.a1s5l2          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.a1s5l2 );
		IntErnals_RS_printf("ioPro.b2b[2].elf.a1s5l3          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.a1s5l3 );
		IntErnals_RS_printf("ioPro.b2b[2].elf.a1s5l4          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.a1s5l4 );
		IntErnals_RS_printf("ioPro.b2b[2].elf.nr1s5rgb        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.nr1s5rgb );
		IntErnals_RS_printf("ioPro.b2b[2].elf.ns1s5lm         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.ns1s5lm );
		IntErnals_RS_printf("ioPro.b2b[2].elf.a5s9e           = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.a5s9e );
		IntErnals_RS_printf("ioPro.b2b[2].elf.a5s9l1          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.a5s9l1 );
		IntErnals_RS_printf("ioPro.b2b[2].elf.a5s9l2          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.a5s9l2 );
		IntErnals_RS_printf("ioPro.b2b[2].elf.a5s9l3          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.a5s9l3 );
		IntErnals_RS_printf("ioPro.b2b[2].elf.a5s9l4          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.a5s9l4 );
		IntErnals_RS_printf("ioPro.b2b[2].elf.nr5s9rgb        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.nr5s9rgb );
		IntErnals_RS_printf("ioPro.b2b[2].elf.ns5s9lm         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.ns5s9lm );
		IntErnals_RS_printf("ioPro.b2b[2].elf.fs9w            = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.fs9w );
		IntErnals_RS_printf("ioPro.b2b[2].elf.fs9yc           = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.fs9yc );
		IntErnals_RS_printf("ioPro.b2b[2].elf.fastr           = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.fastr );
		IntErnals_RS_printf("ioPro.b2b[2].elf.crvaf           = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.crvaf );
		IntErnals_RS_printf("ioPro.b2b[2].elf.fcrvabtof       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.fcrvabtof );
		IntErnals_RS_printf("ioPro.b2b[2].elf.fcrvabtga       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.fcrvabtga );
		IntErnals_RS_printf("ioPro.b2b[2].elf.fcrvabtbd       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.fcrvabtbd );
		IntErnals_RS_printf("ioPro.b2b[2].elf.fcrvabtcp       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.fcrvabtcp );
		IntErnals_RS_printf("ioPro.b2b[2].elf.fyabtga         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.fyabtga );
		IntErnals_RS_printf("ioPro.b2b[2].elf.fyabtga         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.fyabtga );
		IntErnals_RS_printf("ioPro.b2b[2].elf.fyabtclp        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.fyabtclp );
		IntErnals_RS_printf("ioPro.b2b[2].elf.faehh           = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.faehh );
		IntErnals_RS_printf("ioPro.b2b[2].elf.fbstr           = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.fbstr );
		IntErnals_RS_printf("ioPro.b2b[2].elf.crvbf           = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.crvbf );
		IntErnals_RS_printf("ioPro.b2b[2].elf.fcrvbbtof       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.fcrvbbtof );
		IntErnals_RS_printf("ioPro.b2b[2].elf.fcrvbbtga       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.fcrvbbtga );
		IntErnals_RS_printf("ioPro.b2b[2].elf.fcrvbbtbd       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.fcrvbbtbd );
		IntErnals_RS_printf("ioPro.b2b[2].elf.fcrvbbtcp       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.fcrvbbtcp );
		IntErnals_RS_printf("ioPro.b2b[2].elf.fybbtga         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.fybbtga );
		IntErnals_RS_printf("ioPro.b2b[2].elf.fybbtbd         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.fybbtbd );
		IntErnals_RS_printf("ioPro.b2b[2].elf.fybbtclp        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.fybbtclp );
		IntErnals_RS_printf("ioPro.b2b[2].elf.fbehh           = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.fbehh );
		IntErnals_RS_printf("ioPro.b2b[2].elf.elfmnnrrl       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.elfmnnrrl );
		IntErnals_RS_printf("ioPro.b2b[2].elf.elfmnnrgl       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.elfmnnrgl );
		IntErnals_RS_printf("ioPro.b2b[2].elf.elfmnnrbl       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.elfmnnrbl );
		IntErnals_RS_printf("ioPro.b2b[2].elf.elfafnr         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.elfafnr );
		IntErnals_RS_printf("ioPro.b2b[2].elf.zeladcmd        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.zeladcmd );
		IntErnals_RS_printf("ioPro.b2b[2].elf.zanbor          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.zanbor );
		IntErnals_RS_printf("ioPro.b2b[2].elf.zanbkr          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.zanbkr );
		IntErnals_RS_printf("ioPro.b2b[2].elf.zanbdr          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.zanbdr );
		IntErnals_RS_printf("ioPro.b2b[2].elf.zanbog          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.zanbog );
		IntErnals_RS_printf("ioPro.b2b[2].elf.zanbkg          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.zanbkg );
		IntErnals_RS_printf("ioPro.b2b[2].elf.zanbdg          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.zanbdg );
		IntErnals_RS_printf("ioPro.b2b[2].elf.zanbdb          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.zanbdb );
		IntErnals_RS_printf("ioPro.b2b[2].elf.zanbkb          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.zanbkb );
		IntErnals_RS_printf("ioPro.b2b[2].elf.zanbkb          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.zanbkb );
		IntErnals_RS_printf("ioPro.b2b[2].elf.zanbdb          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.zanbdb );
		IntErnals_RS_printf("ioPro.b2b[2].elf.zlgtw           = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.zlgtw );
		IntErnals_RS_printf("ioPro.b2b[2].elf.zlgt            = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.zlgt );
		IntErnals_RS_printf("ioPro.b2b[2].elf.zlgte           = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.zlgte );
		IntErnals_RS_printf("ioPro.b2b[2].elf.zedg2anba       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.zedg2anba );
		IntErnals_RS_printf("ioPro.b2b[2].elf.zedgscla        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.zedgscla );
		IntErnals_RS_printf("ioPro.b2b[2].elf.zedg2anbb       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.zedg2anbb );
		IntErnals_RS_printf("ioPro.b2b[2].elf.zedgsclb        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.zedgsclb );
		IntErnals_RS_printf("ioPro.b2b[2].elf.zalnge          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.zalnge );
		IntErnals_RS_printf("ioPro.b2b[2].elf.zalng           = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.zalng );
		IntErnals_RS_printf("ioPro.b2b[2].elf.zlfth           = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.zlfth );
		IntErnals_RS_printf("ioPro.b2b[2].elf.zlcome          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.zlcome );
		IntErnals_RS_printf("ioPro.b2b[2].elf.zlcomen         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.zlcomen );
		IntErnals_RS_printf("ioPro.b2b[2].elf.znslnglm        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.elf.znslnglm );
		// PZSFTA2
		IntErnals_RS_printf("ioPro.b2b[2].pzsfta2.pzsfttrg    = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pzsfta2.pzsfttrg );
		IntErnals_RS_printf("ioPro.b2b[2].pzsfta2.pzofst      = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pzsfta2.pzofst );
		// PZSFTA2A
		IntErnals_RS_printf("ioPro.b2b[2].pzsfta2a.pzsfttrg   = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pzsfta2a.pzsfttrg );
		IntErnals_RS_printf("ioPro.b2b[2].pzsfta2a.pzofst     = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pzsfta2a.pzofst );
		// FSHD
		IntErnals_RS_printf("ioPro.b2b[2].fshd.fshdtrg        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.fshd.fshdtrg );
		IntErnals_RS_printf("ioPro.b2b[2].fshd.fshdpaen       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.fshd.fshdpaen );
		IntErnals_RS_printf("ioPro.b2b[2].fshd.fshdctl        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.fshd.fshdctl );
		IntErnals_RS_printf("ioPro.b2b[2].fshd.fshdv          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.fshd.fshdv );
		IntErnals_RS_printf("ioPro.b2b[2].fshd.fshdh          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.fshd.fshdh );
		IntErnals_RS_printf("ioPro.b2b[2].fshd.fshdvw         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.fshd.fshdvw );
		IntErnals_RS_printf("ioPro.b2b[2].fshd.fshdhw         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.fshd.fshdhw );
		IntErnals_RS_printf("ioPro.b2b[2].fshd.fshdhwph       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.fshd.fshdhwph );
		IntErnals_RS_printf("ioPro.b2b[2].fshd.fshdbc         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.fshd.fshdbc );
		IntErnals_RS_printf("ioPro.b2b[2].fshd.fsul1          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.fshd.fsul1 );
		IntErnals_RS_printf("ioPro.b2b[2].fshd.fsul2          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.fshd.fsul2 );
		IntErnals_RS_printf("ioPro.b2b[2].fshd.fsctl          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.fshd.fsctl );
		IntErnals_RS_printf("ioPro.b2b[2].fshd.fssubpr        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.fshd.fssubpr );
		IntErnals_RS_printf("ioPro.b2b[2].fshd.fssubsp        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.fshd.fssubsp );
		IntErnals_RS_printf("ioPro.b2b[2].fshd.fssubdr        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.fshd.fssubdr );
		IntErnals_RS_printf("ioPro.b2b[2].fshd.fssubst        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.fshd.fssubst );
		IntErnals_RS_printf("ioPro.b2b[2].fshd.fsa1           = %x\n", (kuint)&ioPro.imgPipe[1].b2b.fshd.fsa1 );
		IntErnals_RS_printf("ioPro.b2b[2].fshd.fsa2           = %x\n", (kuint)&ioPro.imgPipe[1].b2b.fshd.fsa2 );
		IntErnals_RS_printf("ioPro.b2b[2].fshd.csctl1         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.fshd.csctl1 );
		IntErnals_RS_printf("ioPro.b2b[2].fshd.csctl2         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.fshd.csctl2 );
		IntErnals_RS_printf("ioPro.b2b[2].fshd.cstblst        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.fshd.cstblst );
		IntErnals_RS_printf("ioPro.b2b[2].fshd.cstbls1        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.fshd.cstbls1 );
		IntErnals_RS_printf("ioPro.b2b[2].fshd.cstbls2        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.fshd.cstbls2 );
		IntErnals_RS_printf("ioPro.b2b[2].fshd.cshdd          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.fshd.cshdd );
		IntErnals_RS_printf("ioPro.b2b[2].fshd.cshdoa         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.fshd.cshdoa );
		IntErnals_RS_printf("ioPro.b2b[2].fshd.csa1           = %x\n", (kuint)&ioPro.imgPipe[1].b2b.fshd.csa1 );
		IntErnals_RS_printf("ioPro.b2b[2].fshd.csa2           = %x\n", (kuint)&ioPro.imgPipe[1].b2b.fshd.csa2 );
		IntErnals_RS_printf("ioPro.b2b[2].fshd.fswric         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.fshd.fswric );
		// PGAIN2
		IntErnals_RS_printf("ioPro.b2b[2].pgain2.pgaintrg     = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pgain2.pgaintrg );
		IntErnals_RS_printf("ioPro.b2b[2].pgain2.pgainr       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pgain2.pgainr );
		IntErnals_RS_printf("ioPro.b2b[2].pgain2.pgaingr      = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pgain2.pgaingr );
		IntErnals_RS_printf("ioPro.b2b[2].pgain2.pgaingb      = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pgain2.pgaingb );
		IntErnals_RS_printf("ioPro.b2b[2].pgain2.pgainb       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pgain2.pgainb );
		IntErnals_RS_printf("ioPro.b2b[2].pgain2.pofsr        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pgain2.pofsr );
		IntErnals_RS_printf("ioPro.b2b[2].pgain2.pofsgr       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pgain2.pofsgr );
		IntErnals_RS_printf("ioPro.b2b[2].pgain2.pofsgb       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pgain2.pofsgb );
		IntErnals_RS_printf("ioPro.b2b[2].pgain2.pofsb        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pgain2.pofsb );
		// P2M-0
		IntErnals_RS_printf("ioPro.b2b[2].p2m0.p2mtrg         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.p2m[0].p2mtrg );
		IntErnals_RS_printf("ioPro.b2b[2].p2m0.p2mpaen        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.p2m[0].p2mpaen );
		IntErnals_RS_printf("ioPro.b2b[2].p2m0.p2mctl         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.p2m[0].p2mctl );
		IntErnals_RS_printf("ioPro.b2b[2].p2m0.p2mofs         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.p2m[0].p2mofs );
		IntErnals_RS_printf("ioPro.b2b[2].p2m0.pbsft          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.p2m[0].pbsft );
		IntErnals_RS_printf("ioPro.b2b[2].p2m0.pclph          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.p2m[0].pclph );
		IntErnals_RS_printf("ioPro.b2b[2].p2m0.ptrmv          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.p2m[0].ptrmv );
		IntErnals_RS_printf("ioPro.b2b[2].p2m0.ptrmh          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.p2m[0].ptrmh );
		IntErnals_RS_printf("ioPro.b2b[2].p2m0.ptrmvw         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.p2m[0].ptrmvw );
		IntErnals_RS_printf("ioPro.b2b[2].p2m0.ptrmhw         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.p2m[0].ptrmhw );
		IntErnals_RS_printf("ioPro.b2b[2].p2m0.ptrmxvcyc      = %x\n", (kuint)&ioPro.imgPipe[1].b2b.p2m[0].ptrmxvcyc );
		IntErnals_RS_printf("ioPro.b2b[2].p2m0.ptrmxhcyc      = %x\n", (kuint)&ioPro.imgPipe[1].b2b.p2m[0].ptrmxhcyc );
		IntErnals_RS_printf("ioPro.b2b[2].p2m0.ptrmxven       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.p2m[0].ptrmxven );
		IntErnals_RS_printf("ioPro.b2b[2].p2m0.ptrmxhen       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.p2m[0].ptrmxhen );
		IntErnals_RS_printf("ioPro.b2b[2].p2m0.p2mmir         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.p2m[0].p2mmir );
		// P2M-1
		IntErnals_RS_printf("ioPro.b2b[2].p2m1.p2mtrg         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.p2m[1].p2mtrg );
		IntErnals_RS_printf("ioPro.b2b[2].p2m1.p2mpaen        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.p2m[1].p2mpaen );
		IntErnals_RS_printf("ioPro.b2b[2].p2m1.p2mctl         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.p2m[1].p2mctl );
		IntErnals_RS_printf("ioPro.b2b[2].p2m1.p2mofs         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.p2m[1].p2mofs );
		IntErnals_RS_printf("ioPro.b2b[2].p2m1.pbsft          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.p2m[1].pbsft );
		IntErnals_RS_printf("ioPro.b2b[2].p2m1.pclph          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.p2m[1].pclph );
		IntErnals_RS_printf("ioPro.b2b[2].p2m1.ptrmv          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.p2m[1].ptrmv );
		IntErnals_RS_printf("ioPro.b2b[2].p2m1.ptrmh          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.p2m[1].ptrmh );
		IntErnals_RS_printf("ioPro.b2b[2].p2m1.ptrmvw         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.p2m[1].ptrmvw );
		IntErnals_RS_printf("ioPro.b2b[2].p2m1.ptrmhw         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.p2m[1].ptrmhw );
		IntErnals_RS_printf("ioPro.b2b[2].p2m1.ptrmxvcyc      = %x\n", (kuint)&ioPro.imgPipe[1].b2b.p2m[1].ptrmxvcyc );
		IntErnals_RS_printf("ioPro.b2b[2].p2m1.ptrmxhcyc      = %x\n", (kuint)&ioPro.imgPipe[1].b2b.p2m[1].ptrmxhcyc );
		IntErnals_RS_printf("ioPro.b2b[2].p2m1.ptrmxven       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.p2m[1].ptrmxven );
		IntErnals_RS_printf("ioPro.b2b[2].p2m1.ptrmxhen       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.p2m[1].ptrmxhen );
		IntErnals_RS_printf("ioPro.b2b[2].p2m1.p2mmir         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.p2m[1].p2mmir );
		// PWCH-0
		IntErnals_RS_printf("ioPro.b2b[2].pwch0.pwchtrg       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pwch[0].pwchtrg );
		IntErnals_RS_printf("ioPro.b2b[2].pwch0.pws           = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pwch[0].pws );
		IntErnals_RS_printf("ioPro.b2b[2].pwch0.pwaxctl       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pwch[0].pwaxctl );
		IntErnals_RS_printf("ioPro.b2b[2].pwch0.pwchctl       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pwch[0].pwchctl );
		IntErnals_RS_printf("ioPro.b2b[2].pwch0.pwchintenb    = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pwch[0].pwchintenb );
		IntErnals_RS_printf("ioPro.b2b[2].pwch0.pwchintflg    = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pwch[0].pwchintflg );
		IntErnals_RS_printf("ioPro.b2b[2].pwch0.pwchbresp     = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pwch[0].pwchbresp );
		IntErnals_RS_printf("ioPro.b2b[2].pwch0.pwsa          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pwch[0].pwsa );
		IntErnals_RS_printf("ioPro.b2b[2].pwch0.pwlsize       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pwch[0].pwlsize );
		// PWCH-1
		IntErnals_RS_printf("ioPro.b2b[2].pwch1.pwchtrg       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pwch[1].pwchtrg );
		IntErnals_RS_printf("ioPro.b2b[2].pwch1.pws           = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pwch[1].pws );
		IntErnals_RS_printf("ioPro.b2b[2].pwch1.pwaxctl       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pwch[1].pwaxctl );
		IntErnals_RS_printf("ioPro.b2b[2].pwch1.pwchctl       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pwch[1].pwchctl );
		IntErnals_RS_printf("ioPro.b2b[2].pwch1.pwchintenb    = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pwch[1].pwchintenb );
		IntErnals_RS_printf("ioPro.b2b[2].pwch1.pwchintflg    = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pwch[1].pwchintflg );
		IntErnals_RS_printf("ioPro.b2b[2].pwch1.pwchbresp     = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pwch[1].pwchbresp );
		IntErnals_RS_printf("ioPro.b2b[2].pwch1.pwsa          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.pwch[1].pwsa );
		IntErnals_RS_printf("ioPro.b2b[2].pwch1.pwlsize       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.PWCH[1].pwlsize );
		// M2P-0
		IntErnals_RS_printf("ioPro.b2b[2].m2p0.m2ptrg         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.m2p[0].m2ptrg );
		IntErnals_RS_printf("ioPro.b2b[2].m2p0.m2ppaen        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.m2p[0].m2ppaen );
		IntErnals_RS_printf("ioPro.b2b[2].m2p0.m2pctl         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.m2p[0].m2pctl );
		IntErnals_RS_printf("ioPro.b2b[2].m2p0.m2pbsft        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.m2p[0].m2pbsft );
		IntErnals_RS_printf("ioPro.b2b[2].m2p0.m2pofs         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.m2p[0].m2pofs );
		IntErnals_RS_printf("ioPro.b2b[2].m2p0.m2pclip        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.m2p[0].m2pclip );
		// M2P-1
		IntErnals_RS_printf("ioPro.b2b[2].m2p1.m2ptrg         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.m2p[1].m2ptrg );
		IntErnals_RS_printf("ioPro.b2b[2].m2p1.m2ppaen        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.m2p[1].m2ppaen );
		IntErnals_RS_printf("ioPro.b2b[2].m2p1.m2pctl         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.m2p[1].m2pctl );
		IntErnals_RS_printf("ioPro.b2b[2].m2p1.m2pbsft        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.m2p[1].m2pbsft );
		IntErnals_RS_printf("ioPro.b2b[2].m2p1.m2pofs         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.m2p[1].m2pofs );
		IntErnals_RS_printf("ioPro.b2b[2].m2p1.m2pclip        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.m2p[1].m2pclip );
		// M2P-2
		IntErnals_RS_printf("ioPro.b2b[2].m2p2.m2ptrg         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.m2p[2].m2ptrg );
		IntErnals_RS_printf("ioPro.b2b[2].m2p2.m2ppaen        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.m2p[2].m2ppaen );
		IntErnals_RS_printf("ioPro.b2b[2].m2p2.m2pctl         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.m2p[2].m2pctl );
		IntErnals_RS_printf("ioPro.b2b[2].m2p2.m2pbsft        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.m2p[2].m2pbsft );
		IntErnals_RS_printf("ioPro.b2b[2].m2p2.m2pofs         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.m2p[2].m2pofs );
		IntErnals_RS_printf("ioPro.b2b[2].m2p2.m2pclip        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.m2p[2].m2pclip );
		// M2P-3
		IntErnals_RS_printf("ioPro.b2b[2].m2p3.m2ptrg         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.m2p[3].m2ptrg );
		IntErnals_RS_printf("ioPro.b2b[2].m2p3.m2ppaen        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.m2p[3].m2ppaen );
		IntErnals_RS_printf("ioPro.b2b[2].m2p3.m2pctl         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.m2p[3].m2pctl );
		IntErnals_RS_printf("ioPro.b2b[2].m2p3.m2pbsft        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.m2p[3].m2pbsft );
		IntErnals_RS_printf("ioPro.b2b[2].m2p3.m2pofs         = %x\n", (kuint)&ioPro.imgPipe[1].b2b.m2p[3].m2pofs );
		IntErnals_RS_printf("ioPro.b2b[2].m2p3.m2pclip        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.m2p[3].m2pclip );
		// PRCH-0
		IntErnals_RS_printf("ioPro.b2b[2].prch0.prchtrg       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[0].prchtrg );
		IntErnals_RS_printf("ioPro.b2b[2].prch0.prchctl       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[0].prchctl );
		IntErnals_RS_printf("ioPro.b2b[2].prch0.prchrs        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[0].prchrs );
		IntErnals_RS_printf("ioPro.b2b[2].prch0.praxctl       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[0].praxctl );
		IntErnals_RS_printf("ioPro.b2b[2].prch0.prchintenb    = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[0].prchintenb );
		IntErnals_RS_printf("ioPro.b2b[2].prch0.prchintflg    = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[0].prchintflg );
		IntErnals_RS_printf("ioPro.b2b[2].prch0.prchbresp     = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[0].prchbresp );
		IntErnals_RS_printf("ioPro.b2b[2].prch0.prsa          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[0].prsa );
		IntErnals_RS_printf("ioPro.b2b[2].prch0.prlsize       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[0].prlsize );
		IntErnals_RS_printf("ioPro.b2b[2].prch0.prvsize       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[0].prvsize );
		IntErnals_RS_printf("ioPro.b2b[2].prch0.prhsize       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[0].prhsize );
		// PRCH-1
		IntErnals_RS_printf("ioPro.b2b[2].prch1.prchtrg       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[1].prchtrg );
		IntErnals_RS_printf("ioPro.b2b[2].prch1.prchctl       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[1].prchctl );
		IntErnals_RS_printf("ioPro.b2b[2].prch1.prchrs        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[1].prchrs );
		IntErnals_RS_printf("ioPro.b2b[2].prch1.praxctl       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[1].praxctl );
		IntErnals_RS_printf("ioPro.b2b[2].prch1.prchintenb    = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[1].prchintenb );
		IntErnals_RS_printf("ioPro.b2b[2].prch1.prchintflg    = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[1].prchintflg );
		IntErnals_RS_printf("ioPro.b2b[2].prch1.prchbresp     = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[1].prchbresp );
		IntErnals_RS_printf("ioPro.b2b[2].prch1.prsa          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[1].prsa );
		IntErnals_RS_printf("ioPro.b2b[2].prch1.prlsize       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[1].prlsize );
		IntErnals_RS_printf("ioPro.b2b[2].prch1.prvsize       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[1].prvsize );
		IntErnals_RS_printf("ioPro.b2b[2].prch1.prhsize       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[1].prhsize );
		// PRCH-2
		IntErnals_RS_printf("ioPro.b2b[2].prch2.prchtrg       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[2].prchtrg );
		IntErnals_RS_printf("ioPro.b2b[2].prch2.prchctl       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[2].prchctl );
		IntErnals_RS_printf("ioPro.b2b[2].prch2.prchrs        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[2].prchrs );
		IntErnals_RS_printf("ioPro.b2b[2].prch2.praxctl       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[2].praxctl );
		IntErnals_RS_printf("ioPro.b2b[2].prch2.prchintenb    = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[2].prchintenb );
		IntErnals_RS_printf("ioPro.b2b[2].prch2.prchintflg    = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[2].prchintflg );
		IntErnals_RS_printf("ioPro.b2b[2].prch2.prchbresp     = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[2].prchbresp );
		IntErnals_RS_printf("ioPro.b2b[2].prch2.prsa          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[2].prsa );
		IntErnals_RS_printf("ioPro.b2b[2].prch2.prlsize       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[2].prlsize );
		IntErnals_RS_printf("ioPro.b2b[2].prch2.prvsize       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[2].prvsize );
		IntErnals_RS_printf("ioPro.b2b[2].prch2.prhsize       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[2].prhsize );
		// PRCH-3
		IntErnals_RS_printf("ioPro.b2b[2].prch3.prchtrg       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[3].prchtrg );
		IntErnals_RS_printf("ioPro.b2b[2].prch3.prchctl       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[3].prchctl );
		IntErnals_RS_printf("ioPro.b2b[2].prch3.prchrs        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[3].prchrs );
		IntErnals_RS_printf("ioPro.b2b[2].prch3.praxctl       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[3].praxctl );
		IntErnals_RS_printf("ioPro.b2b[2].prch3.prchintenb    = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[3].prchintenb );
		IntErnals_RS_printf("ioPro.b2b[2].prch3.prchintflg    = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[3].prchintflg );
		IntErnals_RS_printf("ioPro.b2b[2].prch3.prchbresp     = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[3].prchbresp );
		IntErnals_RS_printf("ioPro.b2b[2].prch3.prsa          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[3].prsa );
		IntErnals_RS_printf("ioPro.b2b[2].prch3.prlsize       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[3].prlsize );
		IntErnals_RS_printf("ioPro.b2b[2].prch3.prvsize       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[3].prvsize );
		IntErnals_RS_printf("ioPro.b2b[2].prch3.prhsize       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[3].prhsize );
		// PRCH-4
		IntErnals_RS_printf("ioPro.b2b[2].prch4.prchtrg       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[4].prchtrg );
		IntErnals_RS_printf("ioPro.b2b[2].prch4.prchctl       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[4].prchctl );
		IntErnals_RS_printf("ioPro.b2b[2].prch4.prchrs        = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[4].prchrs );
		IntErnals_RS_printf("ioPro.b2b[2].prch4.praxctl       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[4].praxctl );
		IntErnals_RS_printf("ioPro.b2b[2].prch4.prchintenb    = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[4].prchintenb );
		IntErnals_RS_printf("ioPro.b2b[2].prch4.prchintflg    = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[4].prchintflg );
		IntErnals_RS_printf("ioPro.b2b[2].prch4.prchbresp     = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[4].prchbresp );
		IntErnals_RS_printf("ioPro.b2b[2].prch4.prsa          = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[4].prsa );
		IntErnals_RS_printf("ioPro.b2b[2].prch4.prlsize       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[4].prlsize );
		IntErnals_RS_printf("ioPro.b2b[2].prch4.prvsize       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[4].prvsize );
		IntErnals_RS_printf("ioPro.b2b[2].prch4.prhsize       = %x\n", (kuint)&ioPro.imgPipe[1].b2b.prch[4].prhsize );
	}
#endif	/** B2B Unit(pipe[2]) **/
#endif
}

ProTest6 *pro_test6_new(void)
{
	ProTest6* self = k_object_new_with_private(PRO_TYPE_TEST6,sizeof(ProTest6Private));

	return self;
}
