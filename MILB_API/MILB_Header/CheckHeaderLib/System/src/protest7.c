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
#include "protest7.h"


K_TYPE_DEFINE_WITH_PRIVATE(ProTest7, pro_test7);
#define PRO_TEST7_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ProTest7Private, PRO_TYPE_TEST7))


struct _ProTest7Private
{
	kint a;
};
/*
 * IMPL
 */
static void pro_test7_constructor(ProTest7 *self)
{
	ProTest7Private *priv = PRO_TEST7_GET_PRIVATE(self);

	priv->a = 0;
}

static void pro_test7_destructor(ProTest7 *self)
{
	ProTest7Private *priv = PRO_TEST7_GET_PRIVATE(self);

	priv->a = 0;
}
/*
 * PUBLIC
 */
void pro_test7(ProTest7 *self, EProBlockType type, IoPro ioPro)
{
#if 0
#ifdef D_ENABLE_IO_PRO_B2B_PIPE_3	/** B2B Unit(pipe[3]) **/
	if(type == IntErnals_E_PRO_BLOCK_TYPE_B2B3) {
		// B2BTOP
		IntErnals_RS_printf("b2b[3]\n");
		IntErnals_RS_printf("ioPro.b2b[3].b2btop.sr           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.b2btop.sr );
		IntErnals_RS_printf("ioPro.b2b[3].b2btop.clkstp       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.b2btop.clkstp );
		IntErnals_RS_printf("ioPro.b2b[3].b2btop.b2btopctl1   = %x\n", (kuint)&ioPro.imgPipe[2].b2b.b2btop.b2btopctl1 );
		IntErnals_RS_printf("ioPro.b2b[3].b2btop.b2btopctl2   = %x\n", (kuint)&ioPro.imgPipe[2].b2b.b2btop.b2btopctl2 );
		IntErnals_RS_printf("ioPro.b2b[3].b2btop.intmon1      = %x\n", (kuint)&ioPro.imgPipe[2].b2b.b2btop.intmon1 );
		IntErnals_RS_printf("ioPro.b2b[3].b2btop.intmon2      = %x\n", (kuint)&ioPro.imgPipe[2].b2b.b2btop.intmon2 );
		IntErnals_RS_printf("ioPro.b2b[3].b2btop.intctl       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.b2btop.intctl );
		IntErnals_RS_printf("ioPro.b2b[3].b2btop.vhdintenb    = %x\n", (kuint)&ioPro.imgPipe[2].b2b.b2btop.vhdintenb );
		IntErnals_RS_printf("ioPro.b2b[3].b2btop.vhdintflg    = %x\n", (kuint)&ioPro.imgPipe[2].b2b.b2btop.vhdintflg );
		IntErnals_RS_printf("ioPro.b2b[3].b2btop.vhset        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.b2btop.vhset );
		IntErnals_RS_printf("ioPro.b2b[3].b2btop.vmivadr      = %x\n", (kuint)&ioPro.imgPipe[2].b2b.b2btop.vmivadr );
		IntErnals_RS_printf("ioPro.b2b[3].b2btop.vmihadr      = %x\n", (kuint)&ioPro.imgPipe[2].b2b.b2btop.vmihadr );
		IntErnals_RS_printf("ioPro.b2b[3].b2btop.hmihadr      = %x\n", (kuint)&ioPro.imgPipe[2].b2b.b2btop.hmihadr );
		// PG
		IntErnals_RS_printf("ioPro.b2b[3].pg.pgtrg            = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pg.pgtrg );
		IntErnals_RS_printf("ioPro.b2b[3].pg.pgctl            = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pg.pgctl );
		IntErnals_RS_printf("ioPro.b2b[3].pg.pgvw             = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pg.pgvw );
		IntErnals_RS_printf("ioPro.b2b[3].pg.pghw             = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pg.pghw );
		IntErnals_RS_printf("ioPro.b2b[3].pg.pgvblnk          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pg.pgvblnk );
		IntErnals_RS_printf("ioPro.b2b[3].pg.pghblnk          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pg.pghblnk );
		IntErnals_RS_printf("ioPro.b2b[3].pg.pgvdhdblnk       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pg.pgvdhdblnk );
		// PGAIN1
		IntErnals_RS_printf("ioPro.b2b[3].pgain1.pgaintrg     = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pgain1.pgaintrg );
		IntErnals_RS_printf("ioPro.b2b[3].pgain1.pgainr       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pgain1.pgainr );
		IntErnals_RS_printf("ioPro.b2b[3].pgain1.pgaingr      = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pgain1.pgaingr );
		IntErnals_RS_printf("ioPro.b2b[3].pgain1.pgaingb      = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pgain1.pgaingb );
		IntErnals_RS_printf("ioPro.b2b[3].pgain1.pgainb       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pgain1.pgainb );
		IntErnals_RS_printf("ioPro.b2b[3].pgain1.pofsr        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pgain1.pofsr );
		IntErnals_RS_printf("ioPro.b2b[3].pgain1.pofsgr       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pgain1.pofsgr );
		IntErnals_RS_printf("ioPro.b2b[3].pgain1.pofsgb       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pgain1.pofsgb );
		IntErnals_RS_printf("ioPro.b2b[3].pgain1.pofsb        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pgain1.pofsb );
		// PZSFTA1
		IntErnals_RS_printf("ioPro.b2b[3].pzsfta1.pzsfttrg    = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pzsfta1.pzsfttrg );
		IntErnals_RS_printf("ioPro.b2b[3].pzsfta1.pzofst      = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pzsfta1.pzofst );
		// ELF
		IntErnals_RS_printf("ioPro.b2b[3].elf.elftrg          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.elftrg );
		IntErnals_RS_printf("ioPro.b2b[3].elf.nsltrg          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.nsltrg );
		IntErnals_RS_printf("ioPro.b2b[3].elf.elfpaen         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.elfpaen );
		IntErnals_RS_printf("ioPro.b2b[3].elf.elfgwp          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.elfgwp );
		IntErnals_RS_printf("ioPro.b2b[3].elf.elfgws          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.elfgws );
		IntErnals_RS_printf("ioPro.b2b[3].elf.elfwp           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.elfwp );
		IntErnals_RS_printf("ioPro.b2b[3].elf.elfws           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.elfws );
		IntErnals_RS_printf("ioPro.b2b[3].elf.elfctl          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.elfctl );
		IntErnals_RS_printf("ioPro.b2b[3].elf.elfzp           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.elfzp );
		IntErnals_RS_printf("ioPro.b2b[3].elf.elfl            = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.elfl );
		IntErnals_RS_printf("ioPro.b2b[3].elf.anbor           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.anbor );
		IntErnals_RS_printf("ioPro.b2b[3].elf.anbkr           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.anbkr );
		IntErnals_RS_printf("ioPro.b2b[3].elf.anbdr           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.anbdr );
		IntErnals_RS_printf("ioPro.b2b[3].elf.anbog           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.anbog );
		IntErnals_RS_printf("ioPro.b2b[3].elf.anbkg           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.anbkg );
		IntErnals_RS_printf("ioPro.b2b[3].elf.anbdg           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.anbdg );
		IntErnals_RS_printf("ioPro.b2b[3].elf.anbob           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.anbob );
		IntErnals_RS_printf("ioPro.b2b[3].elf.anbkb           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.anbkb );
		IntErnals_RS_printf("ioPro.b2b[3].elf.anbdb           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.anbdb );
		IntErnals_RS_printf("ioPro.b2b[3].elf.lgtw            = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.lgtw );
		IntErnals_RS_printf("ioPro.b2b[3].elf.lgt             = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.lgt );
		IntErnals_RS_printf("ioPro.b2b[3].elf.lgte            = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.lgte );
		IntErnals_RS_printf("ioPro.b2b[3].elf.edg2anba        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.edg2anba );
		IntErnals_RS_printf("ioPro.b2b[3].elf.edgscla         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.edgscla );
		IntErnals_RS_printf("ioPro.b2b[3].elf.edg2anbb        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.edg2anbb );
		IntErnals_RS_printf("ioPro.b2b[3].elf.edgsclb         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.edgsclb );
		IntErnals_RS_printf("ioPro.b2b[3].elf.edg2anbc        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.edg2anbc );
		IntErnals_RS_printf("ioPro.b2b[3].elf.edgsclc         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.edgsclc );
		IntErnals_RS_printf("ioPro.b2b[3].elf.efth            = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.efth );
		IntErnals_RS_printf("ioPro.b2b[3].elf.lfth            = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.lfth );
		IntErnals_RS_printf("ioPro.b2b[3].elf.elcome          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.elcome );
		IntErnals_RS_printf("ioPro.b2b[3].elf.elcomen         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.elcomen );
		IntErnals_RS_printf("ioPro.b2b[3].elf.a1s5e           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.a1s5e );
		IntErnals_RS_printf("ioPro.b2b[3].elf.a1s5l1          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.a1s5l1 );
		IntErnals_RS_printf("ioPro.b2b[3].elf.a1s5l2          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.a1s5l2 );
		IntErnals_RS_printf("ioPro.b2b[3].elf.a1s5l3          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.a1s5l3 );
		IntErnals_RS_printf("ioPro.b2b[3].elf.a1s5l4          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.a1s5l4 );
		IntErnals_RS_printf("ioPro.b2b[3].elf.nr1s5rgb        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.nr1s5rgb );
		IntErnals_RS_printf("ioPro.b2b[3].elf.ns1s5lm         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.ns1s5lm );
		IntErnals_RS_printf("ioPro.b2b[3].elf.a5s9e           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.a5s9e );
		IntErnals_RS_printf("ioPro.b2b[3].elf.a5s9l1          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.a5s9l1 );
		IntErnals_RS_printf("ioPro.b2b[3].elf.a5s9l2          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.a5s9l2 );
		IntErnals_RS_printf("ioPro.b2b[3].elf.a5s9l3          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.a5s9l3 );
		IntErnals_RS_printf("ioPro.b2b[3].elf.a5s9l4          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.a5s9l4 );
		IntErnals_RS_printf("ioPro.b2b[3].elf.nr5s9rgb        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.nr5s9rgb );
		IntErnals_RS_printf("ioPro.b2b[3].elf.ns5s9lm         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.ns5s9lm );
		IntErnals_RS_printf("ioPro.b2b[3].elf.fs9w            = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.fs9w );
		IntErnals_RS_printf("ioPro.b2b[3].elf.fs9yc           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.fs9yc );
		IntErnals_RS_printf("ioPro.b2b[3].elf.fastr           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.fastr );
		IntErnals_RS_printf("ioPro.b2b[3].elf.crvaf           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.crvaf );
		IntErnals_RS_printf("ioPro.b2b[3].elf.fcrvabtof       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.fcrvabtof );
		IntErnals_RS_printf("ioPro.b2b[3].elf.fcrvabtga       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.fcrvabtga );
		IntErnals_RS_printf("ioPro.b2b[3].elf.fcrvabtbd       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.fcrvabtbd );
		IntErnals_RS_printf("ioPro.b2b[3].elf.fcrvabtcp       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.fcrvabtcp );
		IntErnals_RS_printf("ioPro.b2b[3].elf.fyabtga         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.fyabtga );
		IntErnals_RS_printf("ioPro.b2b[3].elf.fyabtga         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.fyabtga );
		IntErnals_RS_printf("ioPro.b2b[3].elf.fyabtclp        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.fyabtclp );
		IntErnals_RS_printf("ioPro.b2b[3].elf.faehh           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.faehh );
		IntErnals_RS_printf("ioPro.b2b[3].elf.fbstr           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.fbstr );
		IntErnals_RS_printf("ioPro.b2b[3].elf.crvbf           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.crvbf );
		IntErnals_RS_printf("ioPro.b2b[3].elf.fcrvbbtof       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.fcrvbbtof );
		IntErnals_RS_printf("ioPro.b2b[3].elf.fcrvbbtga       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.fcrvbbtga );
		IntErnals_RS_printf("ioPro.b2b[3].elf.fcrvbbtbd       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.fcrvbbtbd );
		IntErnals_RS_printf("ioPro.b2b[3].elf.fcrvbbtcp       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.fcrvbbtcp );
		IntErnals_RS_printf("ioPro.b2b[3].elf.fybbtga         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.fybbtga );
		IntErnals_RS_printf("ioPro.b2b[3].elf.fybbtbd         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.fybbtbd );
		IntErnals_RS_printf("ioPro.b2b[3].elf.fybbtclp        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.fybbtclp );
		IntErnals_RS_printf("ioPro.b2b[3].elf.fbehh           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.fbehh );
		IntErnals_RS_printf("ioPro.b2b[3].elf.elfmnnrrl       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.elfmnnrrl );
		IntErnals_RS_printf("ioPro.b2b[3].elf.elfmnnrgl       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.elfmnnrgl );
		IntErnals_RS_printf("ioPro.b2b[3].elf.elfmnnrbl       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.elfmnnrbl );
		IntErnals_RS_printf("ioPro.b2b[3].elf.elfafnr         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.elfafnr );
		IntErnals_RS_printf("ioPro.b2b[3].elf.zeladcmd        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zeladcmd );
		IntErnals_RS_printf("ioPro.b2b[3].elf.zanbor          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zanbor );
		IntErnals_RS_printf("ioPro.b2b[3].elf.zanbkr          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zanbkr );
		IntErnals_RS_printf("ioPro.b2b[3].elf.zanbdr          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zanbdr );
		IntErnals_RS_printf("ioPro.b2b[3].elf.zanbog          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zanbog );
		IntErnals_RS_printf("ioPro.b2b[3].elf.zanbkg          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zanbkg );
		IntErnals_RS_printf("ioPro.b2b[3].elf.zanbdg          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zanbdg );
		IntErnals_RS_printf("ioPro.b2b[3].elf.zanbdb          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zanbdb );
		IntErnals_RS_printf("ioPro.b2b[3].elf.zanbkb          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zanbkb );
		IntErnals_RS_printf("ioPro.b2b[3].elf.zanbkb          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zanbkb );
		IntErnals_RS_printf("ioPro.b2b[3].elf.zanbdb          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zanbdb );
		IntErnals_RS_printf("ioPro.b2b[3].elf.zlgtw           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zlgtw );
		IntErnals_RS_printf("ioPro.b2b[3].elf.zlgt            = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zlgt );
		IntErnals_RS_printf("ioPro.b2b[3].elf.zlgte           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zlgte );
		IntErnals_RS_printf("ioPro.b2b[3].elf.zedg2anba       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zedg2anba );
		IntErnals_RS_printf("ioPro.b2b[3].elf.zedgscla        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zedgscla );
		IntErnals_RS_printf("ioPro.b2b[3].elf.zedg2anbb       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zedg2anbb );
		IntErnals_RS_printf("ioPro.b2b[3].elf.zedgsclb        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zedgsclb );
		IntErnals_RS_printf("ioPro.b2b[3].elf.zalnge          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zalnge );
		IntErnals_RS_printf("ioPro.b2b[3].elf.zalng           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zalng );
		IntErnals_RS_printf("ioPro.b2b[3].elf.zlfth           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zlfth );
		IntErnals_RS_printf("ioPro.b2b[3].elf.zlcome          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zlcome );
		IntErnals_RS_printf("ioPro.b2b[3].elf.zlcomen         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.zlcomen );
		IntErnals_RS_printf("ioPro.b2b[3].elf.znslnglm        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.elf.znslnglm );
		// PZSFTA2
		IntErnals_RS_printf("ioPro.b2b[3].pzsfta2.pzsfttrg    = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pzsfta2.pzsfttrg );
		IntErnals_RS_printf("ioPro.b2b[3].pzsfta2.pzofst      = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pzsfta2.pzofst );
		// PZSFTA2A
		IntErnals_RS_printf("ioPro.b2b[3].pzsfta2a.pzsfttrg   = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pzsfta2a.pzsfttrg );
		IntErnals_RS_printf("ioPro.b2b[3].pzsfta2a.pzofst     = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pzsfta2a.pzofst );
		// FSHD
		IntErnals_RS_printf("ioPro.b2b[3].fshd.fshdtrg        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.fshdtrg );
		IntErnals_RS_printf("ioPro.b2b[3].fshd.fshdpaen       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.fshdpaen );
		IntErnals_RS_printf("ioPro.b2b[3].fshd.fshdctl        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.fshdctl );
		IntErnals_RS_printf("ioPro.b2b[3].fshd.fshdv          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.fshdv );
		IntErnals_RS_printf("ioPro.b2b[3].fshd.fshdh          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.fshdh );
		IntErnals_RS_printf("ioPro.b2b[3].fshd.fshdvw         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.fshdvw );
		IntErnals_RS_printf("ioPro.b2b[3].fshd.fshdhw         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.fshdhw );
		IntErnals_RS_printf("ioPro.b2b[3].fshd.fshdhwph       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.fshdhwph );
		IntErnals_RS_printf("ioPro.b2b[3].fshd.fshdbc         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.fshdbc );
		IntErnals_RS_printf("ioPro.b2b[3].fshd.fsul1          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.fsul1 );
		IntErnals_RS_printf("ioPro.b2b[3].fshd.fsul2          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.fsul2 );
		IntErnals_RS_printf("ioPro.b2b[3].fshd.fsctl          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.fsctl );
		IntErnals_RS_printf("ioPro.b2b[3].fshd.fssubpr        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.fssubpr );
		IntErnals_RS_printf("ioPro.b2b[3].fshd.fssubsp        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.fssubsp );
		IntErnals_RS_printf("ioPro.b2b[3].fshd.fssubdr        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.fssubdr );
		IntErnals_RS_printf("ioPro.b2b[3].fshd.fssubst        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.fssubst );
		IntErnals_RS_printf("ioPro.b2b[3].fshd.fsa1           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.fsa1 );
		IntErnals_RS_printf("ioPro.b2b[3].fshd.fsa2           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.fsa2 );
		IntErnals_RS_printf("ioPro.b2b[3].fshd.csctl1         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.csctl1 );
		IntErnals_RS_printf("ioPro.b2b[3].fshd.csctl2         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.csctl2 );
		IntErnals_RS_printf("ioPro.b2b[3].fshd.cstblst        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.cstblst );
		IntErnals_RS_printf("ioPro.b2b[3].fshd.cstbls1        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.cstbls1 );
		IntErnals_RS_printf("ioPro.b2b[3].fshd.cstbls2        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.cstbls2 );
		IntErnals_RS_printf("ioPro.b2b[3].fshd.cshdd          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.cshdd );
		IntErnals_RS_printf("ioPro.b2b[3].fshd.cshdoa         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.cshdoa );
		IntErnals_RS_printf("ioPro.b2b[3].fshd.csa1           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.csa1 );
		IntErnals_RS_printf("ioPro.b2b[3].fshd.csa2           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.csa2 );
		IntErnals_RS_printf("ioPro.b2b[3].fshd.fswric         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.fshd.fswric );
		// PGAIN2
		IntErnals_RS_printf("ioPro.b2b[3].pgain2.pgaintrg     = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pgain2.pgaintrg );
		IntErnals_RS_printf("ioPro.b2b[3].pgain2.pgainr       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pgain2.pgainr );
		IntErnals_RS_printf("ioPro.b2b[3].pgain2.pgaingr      = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pgain2.pgaingr );
		IntErnals_RS_printf("ioPro.b2b[3].pgain2.pgaingb      = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pgain2.pgaingb );
		IntErnals_RS_printf("ioPro.b2b[3].pgain2.pgainb       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pgain2.pgainb );
		IntErnals_RS_printf("ioPro.b2b[3].pgain2.pofsr        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pgain2.pofsr );
		IntErnals_RS_printf("ioPro.b2b[3].pgain2.pofsgr       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pgain2.pofsgr );
		IntErnals_RS_printf("ioPro.b2b[3].pgain2.pofsgb       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pgain2.pofsgb );
		IntErnals_RS_printf("ioPro.b2b[3].pgain2.pofsb        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pgain2.pofsb );
		// P2M-0
		IntErnals_RS_printf("ioPro.b2b[3].p2m0.p2mtrg         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[0].p2mtrg );
		IntErnals_RS_printf("ioPro.b2b[3].p2m0.p2mpaen        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[0].p2mpaen );
		IntErnals_RS_printf("ioPro.b2b[3].p2m0.p2mctl         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[0].p2mctl );
		IntErnals_RS_printf("ioPro.b2b[3].p2m0.p2mofs         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[0].p2mofs );
		IntErnals_RS_printf("ioPro.b2b[3].p2m0.pbsft          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[0].pbsft );
		IntErnals_RS_printf("ioPro.b2b[3].p2m0.pclph          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[0].pclph );
		IntErnals_RS_printf("ioPro.b2b[3].p2m0.ptrmv          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[0].ptrmv );
		IntErnals_RS_printf("ioPro.b2b[3].p2m0.ptrmh          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[0].ptrmh );
		IntErnals_RS_printf("ioPro.b2b[3].p2m0.ptrmvw         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[0].ptrmvw );
		IntErnals_RS_printf("ioPro.b2b[3].p2m0.ptrmhw         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[0].ptrmhw );
		IntErnals_RS_printf("ioPro.b2b[3].p2m0.ptrmxvcyc      = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[0].ptrmxvcyc );
		IntErnals_RS_printf("ioPro.b2b[3].p2m0.ptrmxhcyc      = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[0].ptrmxhcyc );
		IntErnals_RS_printf("ioPro.b2b[3].p2m0.ptrmxven       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[0].ptrmxven );
		IntErnals_RS_printf("ioPro.b2b[3].p2m0.ptrmxhen       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[0].ptrmxhen );
		IntErnals_RS_printf("ioPro.b2b[3].p2m0.p2mmir         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[0].p2mmir );
		// P2M-1
		IntErnals_RS_printf("ioPro.b2b[3].p2m1.p2mtrg         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[1].p2mtrg );
		IntErnals_RS_printf("ioPro.b2b[3].p2m1.p2mpaen        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[1].p2mpaen );
		IntErnals_RS_printf("ioPro.b2b[3].p2m1.p2mctl         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[1].p2mctl );
		IntErnals_RS_printf("ioPro.b2b[3].p2m1.p2mofs         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[1].p2mofs );
		IntErnals_RS_printf("ioPro.b2b[3].p2m1.pbsft          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[1].pbsft );
		IntErnals_RS_printf("ioPro.b2b[3].p2m1.pclph          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[1].pclph );
		IntErnals_RS_printf("ioPro.b2b[3].p2m1.ptrmv          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[1].ptrmv );
		IntErnals_RS_printf("ioPro.b2b[3].p2m1.ptrmh          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[1].ptrmh );
		IntErnals_RS_printf("ioPro.b2b[3].p2m1.ptrmvw         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[1].ptrmvw );
		IntErnals_RS_printf("ioPro.b2b[3].p2m1.ptrmhw         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[1].ptrmhw );
		IntErnals_RS_printf("ioPro.b2b[3].p2m1.ptrmxvcyc      = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[1].ptrmxvcyc );
		IntErnals_RS_printf("ioPro.b2b[3].p2m1.ptrmxhcyc      = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[1].ptrmxhcyc );
		IntErnals_RS_printf("ioPro.b2b[3].p2m1.ptrmxven       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[1].ptrmxven );
		IntErnals_RS_printf("ioPro.b2b[3].p2m1.ptrmxhen       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[1].ptrmxhen );
		IntErnals_RS_printf("ioPro.b2b[3].p2m1.p2mmir         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.p2m[1].p2mmir );
		// PWCH-0
		IntErnals_RS_printf("ioPro.b2b[3].pwch0.pwchtrg       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pwch[0].pwchtrg );
		IntErnals_RS_printf("ioPro.b2b[3].pwch0.pws           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pwch[0].pws );
		IntErnals_RS_printf("ioPro.b2b[3].pwch0.pwaxctl       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pwch[0].pwaxctl );
		IntErnals_RS_printf("ioPro.b2b[3].pwch0.pwchctl       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pwch[0].pwchctl );
		IntErnals_RS_printf("ioPro.b2b[3].pwch0.pwchintenb    = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pwch[0].pwchintenb );
		IntErnals_RS_printf("ioPro.b2b[3].pwch0.pwchintflg    = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pwch[0].pwchintflg );
		IntErnals_RS_printf("ioPro.b2b[3].pwch0.pwchbresp     = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pwch[0].pwchbresp );
		IntErnals_RS_printf("ioPro.b2b[3].pwch0.pwsa          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pwch[0].pwsa );
		IntErnals_RS_printf("ioPro.b2b[3].pwch0.pwlsize       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pwch[0].pwlsize );
		// PWCH-1
		IntErnals_RS_printf("ioPro.b2b[3].pwch1.pwchtrg       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pwch[1].pwchtrg );
		IntErnals_RS_printf("ioPro.b2b[3].pwch1.pws           = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pwch[1].pws );
		IntErnals_RS_printf("ioPro.b2b[3].pwch1.pwaxctl       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pwch[1].pwaxctl );
		IntErnals_RS_printf("ioPro.b2b[3].pwch1.pwchctl       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pwch[1].pwchctl );
		IntErnals_RS_printf("ioPro.b2b[3].pwch1.pwchintenb    = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pwch[1].pwchintenb );
		IntErnals_RS_printf("ioPro.b2b[3].pwch1.pwchintflg    = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pwch[1].pwchintflg );
		IntErnals_RS_printf("ioPro.b2b[3].pwch1.pwchbresp     = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pwch[1].pwchbresp );
		IntErnals_RS_printf("ioPro.b2b[3].pwch1.pwsa          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pwch[1].pwsa );
		IntErnals_RS_printf("ioPro.b2b[3].pwch1.pwlsize       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.pwch[1].pwlsize );
		// M2P-0
		IntErnals_RS_printf("ioPro.b2b[3].m2p0.m2ptrg         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[0].m2ptrg );
		IntErnals_RS_printf("ioPro.b2b[3].m2p0.m2ppaen        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[0].m2ppaen );
		IntErnals_RS_printf("ioPro.b2b[3].m2p0.m2pctl         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[0].m2pctl );
		IntErnals_RS_printf("ioPro.b2b[3].m2p0.m2pbsft        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[0].m2pbsft );
		IntErnals_RS_printf("ioPro.b2b[3].m2p0.m2pofs         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[0].m2pofs );
		IntErnals_RS_printf("ioPro.b2b[3].m2p0.m2pclip        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[0].m2pclip );
		// M2P-1
		IntErnals_RS_printf("ioPro.b2b[3].m2p1.m2ptrg         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[1].m2ptrg );
		IntErnals_RS_printf("ioPro.b2b[3].m2p1.m2ppaen        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[1].m2ppaen );
		IntErnals_RS_printf("ioPro.b2b[3].m2p1.m2pctl         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[1].m2pctl );
		IntErnals_RS_printf("ioPro.b2b[3].m2p1.m2pbsft        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[1].m2pbsft );
		IntErnals_RS_printf("ioPro.b2b[3].m2p1.m2pofs         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[1].m2pofs );
		IntErnals_RS_printf("ioPro.b2b[3].m2p1.m2pclip        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[1].m2pclip );
		// M2P-2
		IntErnals_RS_printf("ioPro.b2b[3].m2p2.m2ptrg         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[2].m2ptrg );
		IntErnals_RS_printf("ioPro.b2b[3].m2p2.m2ppaen        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[2].m2ppaen );
		IntErnals_RS_printf("ioPro.b2b[3].m2p2.m2pctl         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[2].m2pctl );
		IntErnals_RS_printf("ioPro.b2b[3].m2p2.m2pbsft        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[2].m2pbsft );
		IntErnals_RS_printf("ioPro.b2b[3].m2p2.m2pofs         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[2].m2pofs );
		IntErnals_RS_printf("ioPro.b2b[3].m2p2.m2pclip        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[2].m2pclip );
		// M2P-3
		IntErnals_RS_printf("ioPro.b2b[3].m2p3.m2ptrg         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[3].m2ptrg );
		IntErnals_RS_printf("ioPro.b2b[3].m2p3.m2ppaen        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[3].m2ppaen );
		IntErnals_RS_printf("ioPro.b2b[3].m2p3.m2pctl         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[3].m2pctl );
		IntErnals_RS_printf("ioPro.b2b[3].m2p3.m2pbsft        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[3].m2pbsft );
		IntErnals_RS_printf("ioPro.b2b[3].m2p3.m2pofs         = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[3].m2pofs );
		IntErnals_RS_printf("ioPro.b2b[3].m2p3.m2pclip        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.m2p[3].m2pclip );
		// PRCH-0
		IntErnals_RS_printf("ioPro.b2b[3].prch0.prchtrg       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[0].prchtrg );
		IntErnals_RS_printf("ioPro.b2b[3].prch0.prchctl       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[0].prchctl );
		IntErnals_RS_printf("ioPro.b2b[3].prch0.prchrs        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[0].prchrs );
		IntErnals_RS_printf("ioPro.b2b[3].prch0.praxctl       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[0].praxctl );
		IntErnals_RS_printf("ioPro.b2b[3].prch0.prchintenb    = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[0].prchintenb );
		IntErnals_RS_printf("ioPro.b2b[3].prch0.prchintflg    = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[0].prchintflg );
		IntErnals_RS_printf("ioPro.b2b[3].prch0.prchbresp     = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[0].prchbresp );
		IntErnals_RS_printf("ioPro.b2b[3].prch0.prsa          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[0].prsa );
		IntErnals_RS_printf("ioPro.b2b[3].prch0.prlsize       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[0].prlsize );
		IntErnals_RS_printf("ioPro.b2b[3].prch0.prvsize       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[0].prvsize );
		IntErnals_RS_printf("ioPro.b2b[3].prch0.prhsize       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[0].prhsize );
		// PRCH-1
		IntErnals_RS_printf("ioPro.b2b[3].prch1.prchtrg       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[1].prchtrg );
		IntErnals_RS_printf("ioPro.b2b[3].prch1.prchctl       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[1].prchctl );
		IntErnals_RS_printf("ioPro.b2b[3].prch1.prchrs        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[1].prchrs );
		IntErnals_RS_printf("ioPro.b2b[3].prch1.praxctl       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[1].praxctl );
		IntErnals_RS_printf("ioPro.b2b[3].prch1.prchintenb    = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[1].prchintenb );
		IntErnals_RS_printf("ioPro.b2b[3].prch1.prchintflg    = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[1].prchintflg );
		IntErnals_RS_printf("ioPro.b2b[3].prch1.prchbresp     = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[1].prchbresp );
		IntErnals_RS_printf("ioPro.b2b[3].prch1.prsa          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[1].prsa );
		IntErnals_RS_printf("ioPro.b2b[3].prch1.prlsize       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[1].prlsize );
		IntErnals_RS_printf("ioPro.b2b[3].prch1.prvsize       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[1].prvsize );
		IntErnals_RS_printf("ioPro.b2b[3].prch1.prhsize       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[1].prhsize );
		// PRCH-2
		IntErnals_RS_printf("ioPro.b2b[3].prch2.prchtrg       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[2].prchtrg );
		IntErnals_RS_printf("ioPro.b2b[3].prch2.prchctl       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[2].prchctl );
		IntErnals_RS_printf("ioPro.b2b[3].prch2.prchrs        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[2].prchrs );
		IntErnals_RS_printf("ioPro.b2b[3].prch2.praxctl       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[2].praxctl );
		IntErnals_RS_printf("ioPro.b2b[3].prch2.prchintenb    = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[2].prchintenb );
		IntErnals_RS_printf("ioPro.b2b[3].prch2.prchintflg    = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[2].prchintflg );
		IntErnals_RS_printf("ioPro.b2b[3].prch2.prchbresp     = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[2].prchbresp );
		IntErnals_RS_printf("ioPro.b2b[3].prch2.prsa          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[2].prsa );
		IntErnals_RS_printf("ioPro.b2b[3].prch2.prlsize       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[2].prlsize );
		IntErnals_RS_printf("ioPro.b2b[3].prch2.prvsize       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[2].prvsize );
		IntErnals_RS_printf("ioPro.b2b[3].prch2.prhsize       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[2].prhsize );
		// PRCH-3
		IntErnals_RS_printf("ioPro.b2b[3].prch3.prchtrg       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[3].prchtrg );
		IntErnals_RS_printf("ioPro.b2b[3].prch3.prchctl       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[3].prchctl );
		IntErnals_RS_printf("ioPro.b2b[3].prch3.prchrs        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[3].prchrs );
		IntErnals_RS_printf("ioPro.b2b[3].prch3.praxctl       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[3].praxctl );
		IntErnals_RS_printf("ioPro.b2b[3].prch3.prchintenb    = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[3].prchintenb );
		IntErnals_RS_printf("ioPro.b2b[3].prch3.prchintflg    = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[3].prchintflg );
		IntErnals_RS_printf("ioPro.b2b[3].prch3.prchbresp     = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[3].prchbresp );
		IntErnals_RS_printf("ioPro.b2b[3].prch3.prsa          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[3].prsa );
		IntErnals_RS_printf("ioPro.b2b[3].prch3.prlsize       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[3].prlsize );
		IntErnals_RS_printf("ioPro.b2b[3].prch3.prvsize       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[3].prvsize );
		IntErnals_RS_printf("ioPro.b2b[3].prch3.prhsize       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[3].prhsize );
		// PRCH-4
		IntErnals_RS_printf("ioPro.b2b[3].prch4.prchtrg       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[4].prchtrg );
		IntErnals_RS_printf("ioPro.b2b[3].prch4.prchctl       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[4].prchctl );
		IntErnals_RS_printf("ioPro.b2b[3].prch4.prchrs        = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[4].prchrs );
		IntErnals_RS_printf("ioPro.b2b[3].prch4.praxctl       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[4].praxctl );
		IntErnals_RS_printf("ioPro.b2b[3].prch4.prchintenb    = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[4].prchintenb );
		IntErnals_RS_printf("ioPro.b2b[3].prch4.prchintflg    = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[4].prchintflg );
		IntErnals_RS_printf("ioPro.b2b[3].prch4.prchbresp     = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[4].prchbresp );
		IntErnals_RS_printf("ioPro.b2b[3].prch4.prsa          = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[4].prsa );
		IntErnals_RS_printf("ioPro.b2b[3].prch4.prlsize       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[4].prlsize );
		IntErnals_RS_printf("ioPro.b2b[3].prch4.prvsize       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[4].prvsize );
		IntErnals_RS_printf("ioPro.b2b[3].prch4.prhsize       = %x\n", (kuint)&ioPro.imgPipe[2].b2b.prch[4].prhsize );
		}
	#endif	/** B2B Unit(pipe[3]) **/

	#ifdef D_ENABLE_IO_PRO_STAT		/** STAT Unit **/
		if(type == IntErnals_E_PRO_BLOCK_TYPE_STAT) {
		// STATTOP
		IntErnals_RS_printf("ioPro.stat.stattop.sr                = %x\n", (kuint)&ioPro.stat.stattop.sr );
		IntErnals_RS_printf("ioPro.stat.stattop.clkstp            = %x\n", (kuint)&ioPro.stat.stattop.clkstp );
		IntErnals_RS_printf("ioPro.stat.stattop.stattopctl1       = %x\n", (kuint)&ioPro.stat.stattop.stattopctl1 );
		IntErnals_RS_printf("ioPro.stat.stattop.intmon1           = %x\n", (kuint)&ioPro.stat.stattop.intmon1 );
		IntErnals_RS_printf("ioPro.stat.stattop.intmon2           = %x\n", (kuint)&ioPro.stat.stattop.intmon2 );
		IntErnals_RS_printf("ioPro.stat.stattop.intctl            = %x\n", (kuint)&ioPro.stat.stattop.intctl );
		// af0
		// General control Unit
		IntErnals_RS_printf("ioPro.stat.af0.afgbal.aftrg          = %x\n", (kuint)&ioPro.stat.af[0].afgbal.aftrg );
		IntErnals_RS_printf("ioPro.stat.af0.afgbal.afeben         = %x\n", (kuint)&ioPro.stat.af[0].afgbal.afeben );
		IntErnals_RS_printf("ioPro.stat.af0.afgbal.afintenb       = %x\n", (kuint)&ioPro.stat.af[0].afgbal.afintenb );
		IntErnals_RS_printf("ioPro.stat.af0.afgbal.afintflg       = %x\n", (kuint)&ioPro.stat.af[0].afgbal.afintflg );
		IntErnals_RS_printf("ioPro.stat.af0.afgbal.afgv           = %x\n", (kuint)&ioPro.stat.af[0].afgbal.afgv );
		IntErnals_RS_printf("ioPro.stat.af0.afgbal.afgh           = %x\n", (kuint)&ioPro.stat.af[0].afgbal.afgh );
		IntErnals_RS_printf("ioPro.stat.af0.afgbal.afgvw          = %x\n", (kuint)&ioPro.stat.af[0].afgbal.afgvw );
		IntErnals_RS_printf("ioPro.stat.af0.afgbal.afghw          = %x\n", (kuint)&ioPro.stat.af[0].afgbal.afghw );
		IntErnals_RS_printf("ioPro.stat.af0.afgbal.afpaen         = %x\n", (kuint)&ioPro.stat.af[0].afgbal.afpaen );
		// Evaluted value Calculation Unit(0)
		IntErnals_RS_printf("ioPro.stat.af0.afmain0.afmtrxrr    = %x\n", (kuint)&ioPro.stat.af[0].afmain0.afmtrxrr );
		IntErnals_RS_printf("ioPro.stat.af0.afmain0.afmtrxgr    = %x\n", (kuint)&ioPro.stat.af[0].afmain0.afmtrxgr );
		IntErnals_RS_printf("ioPro.stat.af0.afmain0.afmtrxgb    = %x\n", (kuint)&ioPro.stat.af[0].afmain0.afmtrxgb );
		IntErnals_RS_printf("ioPro.stat.af0.afmain0.afmtrxbb    = %x\n", (kuint)&ioPro.stat.af[0].afmain0.afmtrxbb );
		IntErnals_RS_printf("ioPro.stat.af0.afmain0.afmden      = %x\n", (kuint)&ioPro.stat.af[0].afmain0.afmden );
		IntErnals_RS_printf("ioPro.stat.af0.afmain0.afknen      = %x\n", (kuint)&ioPro.stat.af[0].afmain0.afknen );
		IntErnals_RS_printf("ioPro.stat.af0.afmain0.afknb       = %x\n", (kuint)&ioPro.stat.af[0].afmain0.afknb );
		IntErnals_RS_printf("ioPro.stat.af0.afmain0.afkninc     = %x\n", (kuint)&ioPro.stat.af[0].afmain0.afkninc );
		IntErnals_RS_printf("ioPro.stat.af0.afmain0.afknofs     = %x\n", (kuint)&ioPro.stat.af[0].afmain0.afknofs );
		// Evaluted value Calculation Unit(1)
		IntErnals_RS_printf("ioPro.stat.af0.afmain1.afmtrxrr    = %x\n", (kuint)&ioPro.stat.af[0].afmain1.afmtrxrr );
		IntErnals_RS_printf("ioPro.stat.af0.afmain1.afmtrxgr    = %x\n", (kuint)&ioPro.stat.af[0].afmain1.afmtrxgr );
		IntErnals_RS_printf("ioPro.stat.af0.afmain1.afmtrxgb    = %x\n", (kuint)&ioPro.stat.af[0].afmain1.afmtrxgb );
		IntErnals_RS_printf("ioPro.stat.af0.afmain1.afmtrxbb    = %x\n", (kuint)&ioPro.stat.af[0].afmain1.afmtrxbb );
		IntErnals_RS_printf("ioPro.stat.af0.afmain1.afmden      = %x\n", (kuint)&ioPro.stat.af[0].afmain1.afmden );
		IntErnals_RS_printf("ioPro.stat.af0.afmain1.afknen      = %x\n", (kuint)&ioPro.stat.af[0].afmain1.afknen );
		IntErnals_RS_printf("ioPro.stat.af0.afmain1.afknb       = %x\n", (kuint)&ioPro.stat.af[0].afmain1.afknb );
		IntErnals_RS_printf("ioPro.stat.af0.afmain1.afkninc     = %x\n", (kuint)&ioPro.stat.af[0].afmain1.afkninc );
		IntErnals_RS_printf("ioPro.stat.af0.afmain1.afknofs     = %x\n", (kuint)&ioPro.stat.af[0].afmain1.afknofs );
		// Evaluted value Calculation Unit(2)
		IntErnals_RS_printf("ioPro.stat.af0.afmain2.afmtrxrr    = %x\n", (kuint)&ioPro.stat.af[0].afmain2.afmtrxrr );
		IntErnals_RS_printf("ioPro.stat.af0.afmain2.afmtrxgr    = %x\n", (kuint)&ioPro.stat.af[0].afmain2.afmtrxgr );
		IntErnals_RS_printf("ioPro.stat.af0.afmain2.afmtrxgb    = %x\n", (kuint)&ioPro.stat.af[0].afmain2.afmtrxgb );
		IntErnals_RS_printf("ioPro.stat.af0.afmain2.afmtrxbb    = %x\n", (kuint)&ioPro.stat.af[0].afmain2.afmtrxbb );
		IntErnals_RS_printf("ioPro.stat.af0.afmain2.afmden      = %x\n", (kuint)&ioPro.stat.af[0].afmain2.afmden );
		IntErnals_RS_printf("ioPro.stat.af0.afmain2.afknen      = %x\n", (kuint)&ioPro.stat.af[0].afmain2.afknen );
		IntErnals_RS_printf("ioPro.stat.af0.afmain2.afknb       = %x\n", (kuint)&ioPro.stat.af[0].afmain2.afknb );
		IntErnals_RS_printf("ioPro.stat.af0.afmain2.afkninc     = %x\n", (kuint)&ioPro.stat.af[0].afmain2.afkninc );
		IntErnals_RS_printf("ioPro.stat.af0.afmain2.afknofs     = %x\n", (kuint)&ioPro.stat.af[0].afmain2.afknofs );
		// Vertical Detection Processing Unit Register
		IntErnals_RS_printf("ioPro.stat.af0.afvs.afvsctl        = %x\n", (kuint)&ioPro.stat.af[0].afvs.afvsctl );
		IntErnals_RS_printf("ioPro.stat.af0.afvs.afvsh          = %x\n", (kuint)&ioPro.stat.af[0].afvs.afvsh );
		IntErnals_RS_printf("ioPro.stat.af0.afvs.afvshw         = %x\n", (kuint)&ioPro.stat.af[0].afvs.afvshw );
		IntErnals_RS_printf("ioPro.stat.af0.afvs.afiirvb        = %x\n", (kuint)&ioPro.stat.af[0].afvs.afiirvb );
		IntErnals_RS_printf("ioPro.stat.af0.afvs.afcor2v        = %x\n", (kuint)&ioPro.stat.af[0].afvs.afcor2v );
		IntErnals_RS_printf("ioPro.stat.af0.afvs.affirvb        = %x\n", (kuint)&ioPro.stat.af[0].afvs.affirvb );
		// Horizontal Detection Processing Unit Register(0)
		IntErnals_RS_printf("ioPro.stat.af0.afhs0.afhsctla      = %x\n", (kuint)&ioPro.stat.af[0].afhs0.afhsctla );
		IntErnals_RS_printf("ioPro.stat.af0.afhs0.afhsctlb      = %x\n", (kuint)&ioPro.stat.af[0].afhs0.afhsctlb );
		IntErnals_RS_printf("ioPro.stat.af0.afhs0.affirhba      = %x\n", (kuint)&ioPro.stat.af[0].afhs0.affirhba );
		IntErnals_RS_printf("ioPro.stat.af0.afhs0.affirhbb      = %x\n", (kuint)&ioPro.stat.af[0].afhs0.affirhbb );
		IntErnals_RS_printf("ioPro.stat.af0.afhs0.afcor1ha      = %x\n", (kuint)&ioPro.stat.af[0].afhs0.afcor1ha );
		IntErnals_RS_printf("ioPro.stat.af0.afhs0.afcor1hb      = %x\n", (kuint)&ioPro.stat.af[0].afhs0.afcor1hb );
		IntErnals_RS_printf("ioPro.stat.af0.afhs0.afgainha      = %x\n", (kuint)&ioPro.stat.af[0].afhs0.afgainha );
		IntErnals_RS_printf("ioPro.stat.af0.afhs0.afgainhb      = %x\n", (kuint)&ioPro.stat.af[0].afhs0.afgainhb );
		IntErnals_RS_printf("ioPro.stat.af0.afhs0.afiirhba      = %x\n", (kuint)&ioPro.stat.af[0].afhs0.afiirhba );
		IntErnals_RS_printf("ioPro.stat.af0.afhs0.afiirhbb      = %x\n", (kuint)&ioPro.stat.af[0].afhs0.afiirhbb );
		IntErnals_RS_printf("ioPro.stat.af0.afhs0.afcorbha      = %x\n", (kuint)&ioPro.stat.af[0].afhs0.afcorbha );
		IntErnals_RS_printf("ioPro.stat.af0.afhs0.afcorbhb      = %x\n", (kuint)&ioPro.stat.af[0].afhs0.afcorbhb );
		IntErnals_RS_printf("ioPro.stat.af0.afhs0.afcorofsha    = %x\n", (kuint)&ioPro.stat.af[0].afhs0.afcorofsha );
		IntErnals_RS_printf("ioPro.stat.af0.afhs0.afcorofshb    = %x\n", (kuint)&ioPro.stat.af[0].afhs0.afcorofshb );
		// Horizontal Detection Processing Unit Register(1)
		IntErnals_RS_printf("ioPro.stat.af0.afhs1.afhsctla      = %x\n", (kuint)&ioPro.stat.af[0].afhs1.afhsctla );
		IntErnals_RS_printf("ioPro.stat.af0.afhs1.afhsctlb      = %x\n", (kuint)&ioPro.stat.af[0].afhs1.afhsctlb );
		IntErnals_RS_printf("ioPro.stat.af0.afhs1.affirhba      = %x\n", (kuint)&ioPro.stat.af[0].afhs1.affirhba );
		IntErnals_RS_printf("ioPro.stat.af0.afhs1.affirhbb      = %x\n", (kuint)&ioPro.stat.af[0].afhs1.affirhbb );
		IntErnals_RS_printf("ioPro.stat.af0.afhs1.afcor1ha      = %x\n", (kuint)&ioPro.stat.af[0].afhs1.afcor1ha );
		IntErnals_RS_printf("ioPro.stat.af0.afhs1.afcor1hb      = %x\n", (kuint)&ioPro.stat.af[0].afhs1.afcor1hb );
		IntErnals_RS_printf("ioPro.stat.af0.afhs1.afgainha      = %x\n", (kuint)&ioPro.stat.af[0].afhs1.afgainha );
		IntErnals_RS_printf("ioPro.stat.af0.afhs1.afgainhb      = %x\n", (kuint)&ioPro.stat.af[0].afhs1.afgainhb );
		IntErnals_RS_printf("ioPro.stat.af0.afhs1.afiirhba      = %x\n", (kuint)&ioPro.stat.af[0].afhs1.afiirhba );
		IntErnals_RS_printf("ioPro.stat.af0.afhs1.afiirhbb      = %x\n", (kuint)&ioPro.stat.af[0].afhs1.afiirhbb );
		IntErnals_RS_printf("ioPro.stat.af0.afhs1.afcorbha      = %x\n", (kuint)&ioPro.stat.af[0].afhs1.afcorbha );
		IntErnals_RS_printf("ioPro.stat.af0.afhs1.afcorbhb      = %x\n", (kuint)&ioPro.stat.af[0].afhs1.afcorbhb );
		IntErnals_RS_printf("ioPro.stat.af0.afhs1.afcorofsha    = %x\n", (kuint)&ioPro.stat.af[0].afhs1.afcorofsha );
		IntErnals_RS_printf("ioPro.stat.af0.afhs1.afcorofshb    = %x\n", (kuint)&ioPro.stat.af[0].afhs1.afcorofshb );
		// Horizontal Detection Processing Unit Register(2)
		IntErnals_RS_printf("ioPro.stat.af0.afhs2.afhsctla      = %x\n", (kuint)&ioPro.stat.af[0].afhs2.afhsctla );
		IntErnals_RS_printf("ioPro.stat.af0.afhs2.afhsctlb      = %x\n", (kuint)&ioPro.stat.af[0].afhs2.afhsctlb );
		IntErnals_RS_printf("ioPro.stat.af0.afhs2.affirhba      = %x\n", (kuint)&ioPro.stat.af[0].afhs2.affirhba );
		IntErnals_RS_printf("ioPro.stat.af0.afhs2.affirhbb      = %x\n", (kuint)&ioPro.stat.af[0].afhs2.affirhbb );
		IntErnals_RS_printf("ioPro.stat.af0.afhs2.afcor1ha      = %x\n", (kuint)&ioPro.stat.af[0].afhs2.afcor1ha );
		IntErnals_RS_printf("ioPro.stat.af0.afhs2.afcor1hb      = %x\n", (kuint)&ioPro.stat.af[0].afhs2.afcor1hb );
		IntErnals_RS_printf("ioPro.stat.af0.afhs2.afgainha      = %x\n", (kuint)&ioPro.stat.af[0].afhs2.afgainha );
		IntErnals_RS_printf("ioPro.stat.af0.afhs2.afgainhb      = %x\n", (kuint)&ioPro.stat.af[0].afhs2.afgainhb );
		IntErnals_RS_printf("ioPro.stat.af0.afhs2.afiirhba      = %x\n", (kuint)&ioPro.stat.af[0].afhs2.afiirhba );
		IntErnals_RS_printf("ioPro.stat.af0.afhs2.afiirhbb      = %x\n", (kuint)&ioPro.stat.af[0].afhs2.afiirhbb );
		IntErnals_RS_printf("ioPro.stat.af0.afhs2.afcorbha      = %x\n", (kuint)&ioPro.stat.af[0].afhs2.afcorbha );
		IntErnals_RS_printf("ioPro.stat.af0.afhs2.afcorbhb      = %x\n", (kuint)&ioPro.stat.af[0].afhs2.afcorbhb );
		IntErnals_RS_printf("ioPro.stat.af0.afhs2.afcorofsha    = %x\n", (kuint)&ioPro.stat.af[0].afhs2.afcorofsha );
		IntErnals_RS_printf("ioPro.stat.af0.afhs2.afcorofshb    = %x\n", (kuint)&ioPro.stat.af[0].afhs2.afcorofshb );
		// Detection Window Processing Unit Register(0)
		IntErnals_RS_printf("ioPro.stat.af0.afwin0.afwinctl     = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afwinctl );
		IntErnals_RS_printf("ioPro.stat.af0.afwin0.afclvge      = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afclvge );
		IntErnals_RS_printf("ioPro.stat.af0.afwin0.afclvl       = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afclvl );
		IntErnals_RS_printf("ioPro.stat.af0.afwin0.afv          = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afv );
		IntErnals_RS_printf("ioPro.stat.af0.afwin0.afh          = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afh );
		IntErnals_RS_printf("ioPro.stat.af0.afwin0.afvw         = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afvw );
		IntErnals_RS_printf("ioPro.stat.af0.afwin0.afhw         = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afhw );
		IntErnals_RS_printf("ioPro.stat.af0.afwin0.afdatas      = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afdatas );
		IntErnals_RS_printf("ioPro.stat.af0.afwin0.afdatage     = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afdatage );
		IntErnals_RS_printf("ioPro.stat.af0.afwin0.afdatal      = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afdatal );
		IntErnals_RS_printf("ioPro.stat.af0.afwin0.afdatah0     = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afdatah0 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin0.afdatah1     = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afdatah1 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin0.afdatah2     = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afdatah2 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin0.afdatav      = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afdatav );
		IntErnals_RS_printf("ioPro.stat.af0.afwin0.afslwm       = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afslwm );
		IntErnals_RS_printf("ioPro.stat.af0.afwin0.afdatamax    = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afdatamax );
		IntErnals_RS_printf("ioPro.stat.af0.afwin0.afdatamin    = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afdatamin );
		IntErnals_RS_printf("ioPro.stat.af0.afwin0.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afdatamh0 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin0.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afdatamh1 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin0.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[0].afwin0.afdatamh2 );
		// Detection Window Processing Unit Register(1)
		IntErnals_RS_printf("ioPro.stat.af0.afwin1.afwinctl     = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afwinctl );
		IntErnals_RS_printf("ioPro.stat.af0.afwin1.afclvge      = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afclvge );
		IntErnals_RS_printf("ioPro.stat.af0.afwin1.afclvl       = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afclvl );
		IntErnals_RS_printf("ioPro.stat.af0.afwin1.afv          = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afv );
		IntErnals_RS_printf("ioPro.stat.af0.afwin1.afh          = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afh );
		IntErnals_RS_printf("ioPro.stat.af0.afwin1.afvw         = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afvw );
		IntErnals_RS_printf("ioPro.stat.af0.afwin1.afhw         = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afhw );
		IntErnals_RS_printf("ioPro.stat.af0.afwin1.afdatas      = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afdatas );
		IntErnals_RS_printf("ioPro.stat.af0.afwin1.afdatage     = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afdatage );
		IntErnals_RS_printf("ioPro.stat.af0.afwin1.afdatal      = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afdatal );
		IntErnals_RS_printf("ioPro.stat.af0.afwin1.afdatah0     = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afdatah0 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin1.afdatah1     = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afdatah1 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin1.afdatah2     = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afdatah2 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin1.afdatav      = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afdatav );
		IntErnals_RS_printf("ioPro.stat.af0.afwin1.afslwm       = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afslwm );
		IntErnals_RS_printf("ioPro.stat.af0.afwin1.afdatamax    = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afdatamax );
		IntErnals_RS_printf("ioPro.stat.af0.afwin1.afdatamin    = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afdatamin );
		IntErnals_RS_printf("ioPro.stat.af0.afwin1.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afdatamh0 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin1.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afdatamh1 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin1.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[0].afwin1.afdatamh2 );
		// Detection Window Processing Unit Register(2)
		IntErnals_RS_printf("ioPro.stat.af0.afwin2.afwinctl     = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afwinctl );
		IntErnals_RS_printf("ioPro.stat.af0.afwin2.afclvge      = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afclvge );
		IntErnals_RS_printf("ioPro.stat.af0.afwin2.afclvl       = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afclvl );
		IntErnals_RS_printf("ioPro.stat.af0.afwin2.afv          = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afv );
		IntErnals_RS_printf("ioPro.stat.af0.afwin2.afh          = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afh );
		IntErnals_RS_printf("ioPro.stat.af0.afwin2.afvw         = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afvw );
		IntErnals_RS_printf("ioPro.stat.af0.afwin2.afhw         = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afhw );
		IntErnals_RS_printf("ioPro.stat.af0.afwin2.afdatas      = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afdatas );
		IntErnals_RS_printf("ioPro.stat.af0.afwin2.afdatage     = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afdatage );
		IntErnals_RS_printf("ioPro.stat.af0.afwin2.afdatal      = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afdatal );
		IntErnals_RS_printf("ioPro.stat.af0.afwin2.afdatah0     = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afdatah0 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin2.afdatah1     = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afdatah1 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin2.afdatah2     = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afdatah2 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin2.afdatav      = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afdatav );
		IntErnals_RS_printf("ioPro.stat.af0.afwin2.afslwm       = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afslwm );
		IntErnals_RS_printf("ioPro.stat.af0.afwin2.afdatamax    = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afdatamax );
		IntErnals_RS_printf("ioPro.stat.af0.afwin2.afdatamin    = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afdatamin );
		IntErnals_RS_printf("ioPro.stat.af0.afwin2.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afdatamh0 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin2.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afdatamh1 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin2.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[0].afwin2.afdatamh2 );
		// Detection Window Processing Unit Register(3)
		IntErnals_RS_printf("ioPro.stat.af0.afwin3.afwinctl     = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afwinctl );
		IntErnals_RS_printf("ioPro.stat.af0.afwin3.afclvge      = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afclvge );
		IntErnals_RS_printf("ioPro.stat.af0.afwin3.afclvl       = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afclvl );
		IntErnals_RS_printf("ioPro.stat.af0.afwin3.afv          = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afv );
		IntErnals_RS_printf("ioPro.stat.af0.afwin3.afh          = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afh );
		IntErnals_RS_printf("ioPro.stat.af0.afwin3.afvw         = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afvw );
		IntErnals_RS_printf("ioPro.stat.af0.afwin3.afhw         = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afhw );
		IntErnals_RS_printf("ioPro.stat.af0.afwin3.afdatas      = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afdatas );
		IntErnals_RS_printf("ioPro.stat.af0.afwin3.afdatage     = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afdatage );
		IntErnals_RS_printf("ioPro.stat.af0.afwin3.afdatal      = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afdatal );
		IntErnals_RS_printf("ioPro.stat.af0.afwin3.afdatah0     = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afdatah0 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin3.afdatah1     = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afdatah1 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin3.afdatah2     = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afdatah2 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin3.afdatav      = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afdatav );
		IntErnals_RS_printf("ioPro.stat.af0.afwin3.afslwm       = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afslwm );
		IntErnals_RS_printf("ioPro.stat.af0.afwin3.afdatamax    = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afdatamax );
		IntErnals_RS_printf("ioPro.stat.af0.afwin3.afdatamin    = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afdatamin );
		IntErnals_RS_printf("ioPro.stat.af0.afwin3.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afdatamh0 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin3.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afdatamh1 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin3.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[0].afwin3.afdatamh2 );
		// Detection Window Processing Unit Register(4)
		IntErnals_RS_printf("ioPro.stat.af0.afwin4.afwinctl     = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afwinctl );
		IntErnals_RS_printf("ioPro.stat.af0.afwin4.afclvge      = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afclvge );
		IntErnals_RS_printf("ioPro.stat.af0.afwin4.afclvl       = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afclvl );
		IntErnals_RS_printf("ioPro.stat.af0.afwin4.afv          = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afv );
		IntErnals_RS_printf("ioPro.stat.af0.afwin4.afh          = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afh );
		IntErnals_RS_printf("ioPro.stat.af0.afwin4.afvw         = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afvw );
		IntErnals_RS_printf("ioPro.stat.af0.afwin4.afhw         = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afhw );
		IntErnals_RS_printf("ioPro.stat.af0.afwin4.afdatas      = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afdatas );
		IntErnals_RS_printf("ioPro.stat.af0.afwin4.afdatage     = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afdatage );
		IntErnals_RS_printf("ioPro.stat.af0.afwin4.afdatal      = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afdatal );
		IntErnals_RS_printf("ioPro.stat.af0.afwin4.afdatah0     = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afdatah0 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin4.afdatah1     = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afdatah1 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin4.afdatah2     = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afdatah2 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin4.afdatav      = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afdatav );
		IntErnals_RS_printf("ioPro.stat.af0.afwin4.afslwm       = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afslwm );
		IntErnals_RS_printf("ioPro.stat.af0.afwin4.afdatamax    = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afdatamax );
		IntErnals_RS_printf("ioPro.stat.af0.afwin4.afdatamin    = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afdatamin );
		IntErnals_RS_printf("ioPro.stat.af0.afwin4.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afdatamh0 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin4.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afdatamh1 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin4.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[0].afwin4.afdatamh2 );
		// Detection Window Processing Unit Register(5)
		IntErnals_RS_printf("ioPro.stat.af0.afwin5.afwinctl     = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afwinctl );
		IntErnals_RS_printf("ioPro.stat.af0.afwin5.afclvge      = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afclvge );
		IntErnals_RS_printf("ioPro.stat.af0.afwin5.afclvl       = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afclvl );
		IntErnals_RS_printf("ioPro.stat.af0.afwin5.afv          = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afv );
		IntErnals_RS_printf("ioPro.stat.af0.afwin5.afh          = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afh );
		IntErnals_RS_printf("ioPro.stat.af0.afwin5.afvw         = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afvw );
		IntErnals_RS_printf("ioPro.stat.af0.afwin5.afhw         = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afhw );
		IntErnals_RS_printf("ioPro.stat.af0.afwin5.afdatas      = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afdatas );
		IntErnals_RS_printf("ioPro.stat.af0.afwin5.afdatage     = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afdatage );
		IntErnals_RS_printf("ioPro.stat.af0.afwin5.afdatal      = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afdatal );
		IntErnals_RS_printf("ioPro.stat.af0.afwin5.afdatah0     = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afdatah0 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin5.afdatah1     = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afdatah1 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin5.afdatah2     = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afdatah2 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin5.afdatav      = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afdatav );
		IntErnals_RS_printf("ioPro.stat.af0.afwin5.afslwm       = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afslwm );
		IntErnals_RS_printf("ioPro.stat.af0.afwin5.afdatamax    = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afdatamax );
		IntErnals_RS_printf("ioPro.stat.af0.afwin5.afdatamin    = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afdatamin );
		IntErnals_RS_printf("ioPro.stat.af0.afwin5.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afdatamh0 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin5.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afdatamh1 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin5.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[0].afwin5.afdatamh2 );
		// Detection Window Processing Unit Register(6)
		IntErnals_RS_printf("ioPro.stat.af0.afwin6.afwinctl     = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afwinctl );
		IntErnals_RS_printf("ioPro.stat.af0.afwin6.afclvge      = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afclvge );
		IntErnals_RS_printf("ioPro.stat.af0.afwin6.afclvl       = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afclvl );
		IntErnals_RS_printf("ioPro.stat.af0.afwin6.afv          = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afv );
		IntErnals_RS_printf("ioPro.stat.af0.afwin6.afh          = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afh );
		IntErnals_RS_printf("ioPro.stat.af0.afwin6.afvw         = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afvw );
		IntErnals_RS_printf("ioPro.stat.af0.afwin6.afhw         = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afhw );
		IntErnals_RS_printf("ioPro.stat.af0.afwin6.afdatas      = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afdatas );
		IntErnals_RS_printf("ioPro.stat.af0.afwin6.afdatage     = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afdatage );
		IntErnals_RS_printf("ioPro.stat.af0.afwin6.afdatal      = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afdatal );
		IntErnals_RS_printf("ioPro.stat.af0.afwin6.afdatah0     = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afdatah0 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin6.afdatah1     = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afdatah1 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin6.afdatah2     = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afdatah2 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin6.afdatav      = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afdatav );
		IntErnals_RS_printf("ioPro.stat.af0.afwin6.afslwm       = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afslwm );
		IntErnals_RS_printf("ioPro.stat.af0.afwin6.afdatamax    = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afdatamax );
		IntErnals_RS_printf("ioPro.stat.af0.afwin6.afdatamin    = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afdatamin );
		IntErnals_RS_printf("ioPro.stat.af0.afwin6.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afdatamh0 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin6.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afdatamh1 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin6.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[0].afwin6.afdatamh2 );
		// Detection Window Processing Unit Register(7)
		IntErnals_RS_printf("ioPro.stat.af0.afwin7.afwinctl     = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afwinctl );
		IntErnals_RS_printf("ioPro.stat.af0.afwin7.afclvge      = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afclvge );
		IntErnals_RS_printf("ioPro.stat.af0.afwin7.afclvl       = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afclvl );
		IntErnals_RS_printf("ioPro.stat.af0.afwin7.afv          = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afv );
		IntErnals_RS_printf("ioPro.stat.af0.afwin7.afh          = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afh );
		IntErnals_RS_printf("ioPro.stat.af0.afwin7.afvw         = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afvw );
		IntErnals_RS_printf("ioPro.stat.af0.afwin7.afhw         = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afhw );
		IntErnals_RS_printf("ioPro.stat.af0.afwin7.afdatas      = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afdatas );
		IntErnals_RS_printf("ioPro.stat.af0.afwin7.afdatage     = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afdatage );
		IntErnals_RS_printf("ioPro.stat.af0.afwin7.afdatal      = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afdatal );
		IntErnals_RS_printf("ioPro.stat.af0.afwin7.afdatah0     = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afdatah0 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin7.afdatah1     = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afdatah1 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin7.afdatah2     = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afdatah2 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin7.afdatav      = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afdatav );
		IntErnals_RS_printf("ioPro.stat.af0.afwin7.afslwm       = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afslwm );
		IntErnals_RS_printf("ioPro.stat.af0.afwin7.afdatamax    = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afdatamax );
		IntErnals_RS_printf("ioPro.stat.af0.afwin7.afdatamin    = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afdatamin );
		IntErnals_RS_printf("ioPro.stat.af0.afwin7.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afdatamh0 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin7.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afdatamh1 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin7.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[0].afwin7.afdatamh2 );
		// Detection Window Processing Unit Register(8)
		IntErnals_RS_printf("ioPro.stat.af0.afwin8.afwinctl     = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afwinctl );
		IntErnals_RS_printf("ioPro.stat.af0.afwin8.afclvge      = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afclvge );
		IntErnals_RS_printf("ioPro.stat.af0.afwin8.afclvl       = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afclvl );
		IntErnals_RS_printf("ioPro.stat.af0.afwin8.afv          = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afv );
		IntErnals_RS_printf("ioPro.stat.af0.afwin8.afh          = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afh );
		IntErnals_RS_printf("ioPro.stat.af0.afwin8.afvw         = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afvw );
		IntErnals_RS_printf("ioPro.stat.af0.afwin8.afhw         = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afhw );
		IntErnals_RS_printf("ioPro.stat.af0.afwin8.afdatas      = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afdatas );
		IntErnals_RS_printf("ioPro.stat.af0.afwin8.afdatage     = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afdatage );
		IntErnals_RS_printf("ioPro.stat.af0.afwin8.afdatal      = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afdatal );
		IntErnals_RS_printf("ioPro.stat.af0.afwin8.afdatah0     = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afdatah0 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin8.afdatah1     = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afdatah1 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin8.afdatah2     = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afdatah2 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin8.afdatav      = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afdatav );
		IntErnals_RS_printf("ioPro.stat.af0.afwin8.afslwm       = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afslwm );
		IntErnals_RS_printf("ioPro.stat.af0.afwin8.afdatamax    = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afdatamax );
		IntErnals_RS_printf("ioPro.stat.af0.afwin8.afdatamin    = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afdatamin );
		IntErnals_RS_printf("ioPro.stat.af0.afwin8.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afdatamh0 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin8.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afdatamh1 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin8.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[0].afwin8.afdatamh2 );
		// Detection Window Processing Unit Register(9)
		IntErnals_RS_printf("ioPro.stat.af0.afwin9.afwinctl     = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afwinctl );
		IntErnals_RS_printf("ioPro.stat.af0.afwin9.afclvge      = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afclvge );
		IntErnals_RS_printf("ioPro.stat.af0.afwin9.afclvl       = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afclvl );
		IntErnals_RS_printf("ioPro.stat.af0.afwin9.afv          = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afv );
		IntErnals_RS_printf("ioPro.stat.af0.afwin9.afh          = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afh );
		IntErnals_RS_printf("ioPro.stat.af0.afwin9.afvw         = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afvw );
		IntErnals_RS_printf("ioPro.stat.af0.afwin9.afhw         = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afhw );
		IntErnals_RS_printf("ioPro.stat.af0.afwin9.afdatas      = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afdatas );
		IntErnals_RS_printf("ioPro.stat.af0.afwin9.afdatage     = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afdatage );
		IntErnals_RS_printf("ioPro.stat.af0.afwin9.afdatal      = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afdatal );
		IntErnals_RS_printf("ioPro.stat.af0.afwin9.afdatah0     = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afdatah0 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin9.afdatah1     = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afdatah1 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin9.afdatah2     = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afdatah2 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin9.afdatav      = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afdatav );
		IntErnals_RS_printf("ioPro.stat.af0.afwin9.afslwm       = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afslwm );
		IntErnals_RS_printf("ioPro.stat.af0.afwin9.afdatamax    = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afdatamax );
		IntErnals_RS_printf("ioPro.stat.af0.afwin9.afdatamin    = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afdatamin );
		IntErnals_RS_printf("ioPro.stat.af0.afwin9.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afdatamh0 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin9.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afdatamh1 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin9.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[0].afwin9.afdatamh2 );
		// Detection Window Processing Unit Register(10)
		IntErnals_RS_printf("ioPro.stat.af0.afwin10.afwinctl     = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afwinctl );
		IntErnals_RS_printf("ioPro.stat.af0.afwin10.afclvge      = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afclvge );
		IntErnals_RS_printf("ioPro.stat.af0.afwin10.afclvl       = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afclvl );
		IntErnals_RS_printf("ioPro.stat.af0.afwin10.afv          = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afv );
		IntErnals_RS_printf("ioPro.stat.af0.afwin10.afh          = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afh );
		IntErnals_RS_printf("ioPro.stat.af0.afwin10.afvw         = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afvw );
		IntErnals_RS_printf("ioPro.stat.af0.afwin10.afhw         = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afhw );
		IntErnals_RS_printf("ioPro.stat.af0.afwin10.afdatas      = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afdatas );
		IntErnals_RS_printf("ioPro.stat.af0.afwin10.afdatage     = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afdatage );
		IntErnals_RS_printf("ioPro.stat.af0.afwin10.afdatal      = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afdatal );
		IntErnals_RS_printf("ioPro.stat.af0.afwin10.afdatah0     = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afdatah0 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin10.afdatah1     = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afdatah1 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin10.afdatah2     = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afdatah2 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin10.afdatav      = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afdatav );
		IntErnals_RS_printf("ioPro.stat.af0.afwin10.afslwm       = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afslwm );
		IntErnals_RS_printf("ioPro.stat.af0.afwin10.afdatamax    = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afdatamax );
		IntErnals_RS_printf("ioPro.stat.af0.afwin10.afdatamin    = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afdatamin );
		IntErnals_RS_printf("ioPro.stat.af0.afwin10.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afdatamh0 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin10.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afdatamh1 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin10.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[0].afwin10.afdatamh2 );
		// Detection Window Processing Unit Register(11)
		IntErnals_RS_printf("ioPro.stat.af0.afwin11.afwinctl     = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afwinctl );
		IntErnals_RS_printf("ioPro.stat.af0.afwin11.afclvge      = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afclvge );
		IntErnals_RS_printf("ioPro.stat.af0.afwin11.afclvl       = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afclvl );
		IntErnals_RS_printf("ioPro.stat.af0.afwin11.afv          = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afv );
		IntErnals_RS_printf("ioPro.stat.af0.afwin11.afh          = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afh );
		IntErnals_RS_printf("ioPro.stat.af0.afwin11.afvw         = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afvw );
		IntErnals_RS_printf("ioPro.stat.af0.afwin11.afhw         = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afhw );
		IntErnals_RS_printf("ioPro.stat.af0.afwin11.afdatas      = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afdatas );
		IntErnals_RS_printf("ioPro.stat.af0.afwin11.afdatage     = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afdatage );
		IntErnals_RS_printf("ioPro.stat.af0.afwin11.afdatal      = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afdatal );
		IntErnals_RS_printf("ioPro.stat.af0.afwin11.afdatah0     = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afdatah0 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin11.afdatah1     = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afdatah1 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin11.afdatah2     = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afdatah2 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin11.afdatav      = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afdatav );
		IntErnals_RS_printf("ioPro.stat.af0.afwin11.afslwm       = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afslwm );
		IntErnals_RS_printf("ioPro.stat.af0.afwin11.afdatamax    = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afdatamax );
		IntErnals_RS_printf("ioPro.stat.af0.afwin11.afdatamin    = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afdatamin );
		IntErnals_RS_printf("ioPro.stat.af0.afwin11.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afdatamh0 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin11.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afdatamh1 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin11.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[0].afwin11.afdatamh2 );
		// Detection Window Processing Unit Register(12)
		IntErnals_RS_printf("ioPro.stat.af0.afwin12.afwinctl     = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afwinctl );
		IntErnals_RS_printf("ioPro.stat.af0.afwin12.afclvge      = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afclvge );
		IntErnals_RS_printf("ioPro.stat.af0.afwin12.afclvl       = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afclvl );
		IntErnals_RS_printf("ioPro.stat.af0.afwin12.afv          = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afv );
		IntErnals_RS_printf("ioPro.stat.af0.afwin12.afh          = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afh );
		IntErnals_RS_printf("ioPro.stat.af0.afwin12.afvw         = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afvw );
		IntErnals_RS_printf("ioPro.stat.af0.afwin12.afhw         = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afhw );
		IntErnals_RS_printf("ioPro.stat.af0.afwin12.afdatas      = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afdatas );
		IntErnals_RS_printf("ioPro.stat.af0.afwin12.afdatage     = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afdatage );
		IntErnals_RS_printf("ioPro.stat.af0.afwin12.afdatal      = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afdatal );
		IntErnals_RS_printf("ioPro.stat.af0.afwin12.afdatah0     = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afdatah0 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin12.afdatah1     = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afdatah1 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin12.afdatah2     = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afdatah2 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin12.afdatav      = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afdatav );
		IntErnals_RS_printf("ioPro.stat.af0.afwin12.afslwm       = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afslwm );
		IntErnals_RS_printf("ioPro.stat.af0.afwin12.afdatamax    = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afdatamax );
		IntErnals_RS_printf("ioPro.stat.af0.afwin12.afdatamin    = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afdatamin );
		IntErnals_RS_printf("ioPro.stat.af0.afwin12.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afdatamh0 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin12.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afdatamh1 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin12.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[0].afwin12.afdatamh2 );
		// Detection Window Processing Unit Register(13)
		IntErnals_RS_printf("ioPro.stat.af0.afwin13.afwinctl     = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afwinctl );
		IntErnals_RS_printf("ioPro.stat.af0.afwin13.afclvge      = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afclvge );
		IntErnals_RS_printf("ioPro.stat.af0.afwin13.afclvl       = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afclvl );
		IntErnals_RS_printf("ioPro.stat.af0.afwin13.afv          = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afv );
		IntErnals_RS_printf("ioPro.stat.af0.afwin13.afh          = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afh );
		IntErnals_RS_printf("ioPro.stat.af0.afwin13.afvw         = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afvw );
		IntErnals_RS_printf("ioPro.stat.af0.afwin13.afhw         = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afhw );
		IntErnals_RS_printf("ioPro.stat.af0.afwin13.afdatas      = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afdatas );
		IntErnals_RS_printf("ioPro.stat.af0.afwin13.afdatage     = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afdatage );
		IntErnals_RS_printf("ioPro.stat.af0.afwin13.afdatal      = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afdatal );
		IntErnals_RS_printf("ioPro.stat.af0.afwin13.afdatah0     = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afdatah0 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin13.afdatah1     = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afdatah1 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin13.afdatah2     = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afdatah2 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin13.afdatav      = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afdatav );
		IntErnals_RS_printf("ioPro.stat.af0.afwin13.afslwm       = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afslwm );
		IntErnals_RS_printf("ioPro.stat.af0.afwin13.afdatamax    = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afdatamax );
		IntErnals_RS_printf("ioPro.stat.af0.afwin13.afdatamin    = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afdatamin );
		IntErnals_RS_printf("ioPro.stat.af0.afwin13.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afdatamh0 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin13.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afdatamh1 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin13.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[0].afwin13.afdatamh2 );
		// Detection Window Processing Unit Register(14)
		IntErnals_RS_printf("ioPro.stat.af0.afwin14.afwinctl     = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afwinctl );
		IntErnals_RS_printf("ioPro.stat.af0.afwin14.afclvge      = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afclvge );
		IntErnals_RS_printf("ioPro.stat.af0.afwin14.afclvl       = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afclvl );
		IntErnals_RS_printf("ioPro.stat.af0.afwin14.afv          = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afv );
		IntErnals_RS_printf("ioPro.stat.af0.afwin14.afh          = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afh );
		IntErnals_RS_printf("ioPro.stat.af0.afwin14.afvw         = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afvw );
		IntErnals_RS_printf("ioPro.stat.af0.afwin14.afhw         = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afhw );
		IntErnals_RS_printf("ioPro.stat.af0.afwin14.afdatas      = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afdatas );
		IntErnals_RS_printf("ioPro.stat.af0.afwin14.afdatage     = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afdatage );
		IntErnals_RS_printf("ioPro.stat.af0.afwin14.afdatal      = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afdatal );
		IntErnals_RS_printf("ioPro.stat.af0.afwin14.afdatah0     = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afdatah0 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin14.afdatah1     = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afdatah1 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin14.afdatah2     = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afdatah2 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin14.afdatav      = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afdatav );
		IntErnals_RS_printf("ioPro.stat.af0.afwin14.afslwm       = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afslwm );
		IntErnals_RS_printf("ioPro.stat.af0.afwin14.afdatamax    = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afdatamax );
		IntErnals_RS_printf("ioPro.stat.af0.afwin14.afdatamin    = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afdatamin );
		IntErnals_RS_printf("ioPro.stat.af0.afwin14.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afdatamh0 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin14.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afdatamh1 );
		IntErnals_RS_printf("ioPro.stat.af0.afwin14.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[0].afwin14.afdatamh2 );
	}
#endif	/** STAT Unit **/
#endif
}

ProTest7 *pro_test7_new(void)
{
	ProTest7* self = k_object_new_with_private(PRO_TYPE_TEST7,sizeof(ProTest7Private));

	return self;
}
