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
#include "protest5.h"


K_TYPE_DEFINE_WITH_PRIVATE(ProTest5, pro_test5);
#define PRO_TEST5_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ProTest5Private, PRO_TYPE_TEST5))


struct _ProTest5Private
{
	kint a;
};
/*
 * IMPL
 */
static void pro_test5_constructor(ProTest5 *self)
{
	ProTest5Private *priv = PRO_TEST5_GET_PRIVATE(self);

	priv->a = 0;
}

static void pro_test5_destructor(ProTest5 *self)
{
	ProTest5Private *priv = PRO_TEST5_GET_PRIVATE(self);

	priv->a = 0;
}
/*
 * PUBLIC
 */
void pro_test5(ProTest5 *self, EProBlockType type, IoPro ioPro)
{
#if 0
#ifdef D_ENABLE_IO_PRO_SRO_PIPE_3	/** SRO Unit(pipe[3]) **/
	if(type == IntErnals_E_PRO_BLOCK_TYPE_SRO3) {
		// SROTOP
		IntErnals_RS_printf("SR0[3]\n");
		IntErnals_RS_printf("ioPro.sro[3].spotop.sr          = %x\n", (kuint)&ioPro.imgPipe[2].sro.spotop.sr );
		IntErnals_RS_printf("ioPro.sro[3].spotop.clkstp      = %x\n", (kuint)&ioPro.imgPipe[2].sro.spotop.clkstp );
		IntErnals_RS_printf("ioPro.sro[3].spotop.spotopctl1  = %x\n", (kuint)&ioPro.imgPipe[2].sro.spotop.spotopctl1 );
		IntErnals_RS_printf("ioPro.sro[3].spotop.spotopctl2  = %x\n", (kuint)&ioPro.imgPipe[2].sro.spotop.spotopctl2 );
		IntErnals_RS_printf("ioPro.sro[3].spotop.intmon1     = %x\n", (kuint)&ioPro.imgPipe[2].sro.spotop.intmon1 );
		IntErnals_RS_printf("ioPro.sro[3].spotop.intmon2     = %x\n", (kuint)&ioPro.imgPipe[2].sro.spotop.intmon2 );
		IntErnals_RS_printf("ioPro.sro[3].spotop.intctl      = %x\n", (kuint)&ioPro.imgPipe[2].sro.spotop.intctl );
		IntErnals_RS_printf("ioPro.sro[3].spotop.vhdintenb   = %x\n", (kuint)&ioPro.imgPipe[2].sro.spotop.vhdintenb );
		IntErnals_RS_printf("ioPro.sro[3].spotop.vhdintflg   = %x\n", (kuint)&ioPro.imgPipe[2].sro.spotop.vhdintflg );
		IntErnals_RS_printf("ioPro.sro[3].spotop.vhset       = %x\n", (kuint)&ioPro.imgPipe[2].sro.spotop.vhset );
		IntErnals_RS_printf("ioPro.sro[3].spotop.vmivadr     = %x\n", (kuint)&ioPro.imgPipe[2].sro.spotop.vmivadr );
		IntErnals_RS_printf("ioPro.sro[3].spotop.vmihadr     = %x\n", (kuint)&ioPro.imgPipe[2].sro.spotop.vmihadr );
		IntErnals_RS_printf("ioPro.sro[3].spotop.hmihadr     = %x\n", (kuint)&ioPro.imgPipe[2].sro.spotop.hmihadr );
		// PG
		IntErnals_RS_printf("ioPro.sro[3].pg.pgtrg           = %x\n", (kuint)&ioPro.imgPipe[2].sro.pg.pgtrg );
		IntErnals_RS_printf("ioPro.sro[3].pg.pgctl           = %x\n", (kuint)&ioPro.imgPipe[2].sro.pg.pgctl );
		IntErnals_RS_printf("ioPro.sro[3].pg.pgvw            = %x\n", (kuint)&ioPro.imgPipe[2].sro.pg.pgvw );
		IntErnals_RS_printf("ioPro.sro[3].pg.pghw            = %x\n", (kuint)&ioPro.imgPipe[2].sro.pg.pghw );
		IntErnals_RS_printf("ioPro.sro[3].pg.pgvblnk         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pg.pgvblnk );
		IntErnals_RS_printf("ioPro.sro[3].pg.pghblnk         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pg.pghblnk );
		IntErnals_RS_printf("ioPro.sro[3].pg.pgvdhdblnk      = %x\n", (kuint)&ioPro.imgPipe[2].sro.pg.pgvdhdblnk );
		// FFSH-0
		IntErnals_RS_printf("ioPro.sro[3].ffsh0.ffshtrg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[0].ffshtrg );
		IntErnals_RS_printf("ioPro.sro[3].ffsh0.ffshpaen     = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[0].ffshpaen );
		IntErnals_RS_printf("ioPro.sro[3].ffsh0.ffshv        = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[0].ffshv );
		IntErnals_RS_printf("ioPro.sro[3].ffsh0.ffshh        = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[0].ffshh );
		IntErnals_RS_printf("ioPro.sro[3].ffsh0.ffshvw       = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[0].ffshvw );
		IntErnals_RS_printf("ioPro.sro[3].ffsh0.ffshhw       = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[0].ffshhw );
		IntErnals_RS_printf("ioPro.sro[3].ffsh0.ffshbc       = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[0].ffshbc );
		IntErnals_RS_printf("ioPro.sro[3].ffsh0.ffshsubpr    = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[0].ffshsubpr );
		IntErnals_RS_printf("ioPro.sro[3].ffsh0.ffshsubsp    = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[0].ffshsubsp );
		IntErnals_RS_printf("ioPro.sro[3].ffsh0.ffshsubdr    = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[0].ffshsubdr );
		IntErnals_RS_printf("ioPro.sro[3].ffsh0.ffshsubst    = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[0].ffshsubst );
		IntErnals_RS_printf("ioPro.sro[3].ffsh0.ffshwric     = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[0].ffshwric );
		// FFSH-1
		IntErnals_RS_printf("ioPro.sro[3].ffsh1.ffshtrg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[1].ffshtrg );
		IntErnals_RS_printf("ioPro.sro[3].ffsh1.ffshpaen     = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[1].ffshpaen );
		IntErnals_RS_printf("ioPro.sro[3].ffsh1.ffshv        = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[1].ffshv );
		IntErnals_RS_printf("ioPro.sro[3].ffsh1.ffshh        = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[1].ffshh );
		IntErnals_RS_printf("ioPro.sro[3].ffsh1.ffshvw       = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[1].ffshvw );
		IntErnals_RS_printf("ioPro.sro[3].ffsh1.ffshhw       = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[1].ffshhw );
		IntErnals_RS_printf("ioPro.sro[3].ffsh1.ffshbc       = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[1].ffshbc );
		IntErnals_RS_printf("ioPro.sro[3].ffsh1.ffshsubpr    = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[1].ffshsubpr );
		IntErnals_RS_printf("ioPro.sro[3].ffsh1.ffshsubsp    = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[1].ffshsubsp );
		IntErnals_RS_printf("ioPro.sro[3].ffsh1.ffshsubdr    = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[1].ffshsubdr );
		IntErnals_RS_printf("ioPro.sro[3].ffsh1.ffshsubst    = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[1].ffshsubst );
		IntErnals_RS_printf("ioPro.sro[3].ffsh1.ffshwric     = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffsh[1].ffshwric );
		// FF-0
		IntErnals_RS_printf("ioPro.sro[3].ff0.fftrg          = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[0].fftrg );
		IntErnals_RS_printf("ioPro.sro[3].ff0.ffv            = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[0].ffv );
		IntErnals_RS_printf("ioPro.sro[3].ff0.ffh            = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[0].ffh );
		IntErnals_RS_printf("ioPro.sro[3].ff0.ffvw           = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[0].ffvw );
		IntErnals_RS_printf("ioPro.sro[3].ff0.ffhw           = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[0].ffhw );
		IntErnals_RS_printf("ioPro.sro[3].ff0.fflpb0         = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[0].fflpb0 );
		IntErnals_RS_printf("ioPro.sro[3].ff0.fflpb1         = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[0].fflpb1 );
		IntErnals_RS_printf("ioPro.sro[3].ff0.fflpb2         = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[0].fflpb2 );
		IntErnals_RS_printf("ioPro.sro[3].ff0.ffdefts        = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[0].ffdefts );
		IntErnals_RS_printf("ioPro.sro[3].ff0.ffmnwgt        = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[0].ffmnwgt );
		IntErnals_RS_printf("ioPro.sro[3].ff0.ffsbwgt        = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[0].ffsbwgt );
		// FF-1
		IntErnals_RS_printf("ioPro.sro[3].ff1.fftrg          = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[1].fftrg );
		IntErnals_RS_printf("ioPro.sro[3].ff1.ffv            = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[1].ffv );
		IntErnals_RS_printf("ioPro.sro[3].ff1.ffh            = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[1].ffh );
		IntErnals_RS_printf("ioPro.sro[3].ff1.ffvw           = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[1].ffvw );
		IntErnals_RS_printf("ioPro.sro[3].ff1.ffhw           = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[1].ffhw );
		IntErnals_RS_printf("ioPro.sro[3].ff1.fflpb0         = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[1].fflpb0 );
		IntErnals_RS_printf("ioPro.sro[3].ff1.fflpb1         = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[1].fflpb1 );
		IntErnals_RS_printf("ioPro.sro[3].ff1.fflpb2         = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[1].fflpb2 );
		IntErnals_RS_printf("ioPro.sro[3].ff1.ffdefts        = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[1].ffdefts );
		IntErnals_RS_printf("ioPro.sro[3].ff1.ffmnwgt        = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[1].ffmnwgt );
		IntErnals_RS_printf("ioPro.sro[3].ff1.ffsbwgt        = %x\n", (kuint)&ioPro.imgPipe[2].sro.ff[1].ffsbwgt );

		// PGAIN0
		IntErnals_RS_printf("ioPro.sro[3].pgain0.pgaintrg     = %x\n", (kuint)&ioPro.imgPipe[2].sro.pgain0.pgaintrg );
		IntErnals_RS_printf("ioPro.sro[3].pgain0.pgainr       = %x\n", (kuint)&ioPro.imgPipe[2].sro.pgain0.pgainr );
		IntErnals_RS_printf("ioPro.sro[3].pgain0.pgaingr      = %x\n", (kuint)&ioPro.imgPipe[2].sro.pgain0.pgaingr );
		IntErnals_RS_printf("ioPro.sro[3].pgain0.pgaingb      = %x\n", (kuint)&ioPro.imgPipe[2].sro.pgain0.pgaingb );
		IntErnals_RS_printf("ioPro.sro[3].pgain0.pgainb       = %x\n", (kuint)&ioPro.imgPipe[2].sro.pgain0.pgainb );
		IntErnals_RS_printf("ioPro.sro[3].pgain0.pofsr        = %x\n", (kuint)&ioPro.imgPipe[2].sro.pgain0.pofsr );
		IntErnals_RS_printf("ioPro.sro[3].pgain0.pofsgr       = %x\n", (kuint)&ioPro.imgPipe[2].sro.pgain0.pofsgr );
		IntErnals_RS_printf("ioPro.sro[3].pgain0.pofsgb       = %x\n", (kuint)&ioPro.imgPipe[2].sro.pgain0.pofsgb );
		IntErnals_RS_printf("ioPro.sro[3].pgain0.pofsb        = %x\n", (kuint)&ioPro.imgPipe[2].sro.pgain0.pofsb );
		// SDC-0
		IntErnals_RS_printf("ioPro.sro[3].sdc0.sdctrg     = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdctrg );
		IntErnals_RS_printf("ioPro.sro[3].sdc0.sdcpaen    = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcpaen );
		IntErnals_RS_printf("ioPro.sro[3].sdc0.sdcctl     = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcctl );
		IntErnals_RS_printf("ioPro.sro[3].sdc0.sdcintenb  = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcintenb );
		IntErnals_RS_printf("ioPro.sro[3].sdc0.sdcintflg  = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcintflg );
		IntErnals_RS_printf("ioPro.sro[3].sdc0.sdcsgd     = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcsgd );
		IntErnals_RS_printf("ioPro.sro[3].sdc0.sdcph0     = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcph0 );
		IntErnals_RS_printf("ioPro.sro[3].sdc0.sdcph1     = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcph1 );
		IntErnals_RS_printf("ioPro.sro[3].sdc0.sdcphw0    = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcphw0 );
		IntErnals_RS_printf("ioPro.sro[3].sdc0.sdcphw1    = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcphw1 );
		IntErnals_RS_printf("ioPro.sro[3].sdc0.sdcp1hw0   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcp1hw0 );
		IntErnals_RS_printf("ioPro.sro[3].sdc0.sdcp1hw1   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcp1hw1 );
		IntErnals_RS_printf("ioPro.sro[3].sdc0.sdcn1hw0   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcn1hw0 );
		IntErnals_RS_printf("ioPro.sro[3].sdc0.sdcn1hw1   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcn1hw1 );
		IntErnals_RS_printf("ioPro.sro[3].sdc0.sdcp2hw0   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcp2hw0 );
		IntErnals_RS_printf("ioPro.sro[3].sdc0.sdcp2hw1   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcp2hw1 );
		IntErnals_RS_printf("ioPro.sro[3].sdc0.sdcn2hw0   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcn2hw0 );
		IntErnals_RS_printf("ioPro.sro[3].sdc0.sdcn2hw1   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcn2hw1 );
		IntErnals_RS_printf("ioPro.sro[3].sdc0.sdcpc0     = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcpc0 );
		IntErnals_RS_printf("ioPro.sro[3].sdc0.sdcpc1     = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcpc1 );
		IntErnals_RS_printf("ioPro.sro[3].sdc0.sdcpcw0    = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcpcw0 );
		IntErnals_RS_printf("ioPro.sro[3].sdc0.sdcpcw1    = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcpcw1 );
		IntErnals_RS_printf("ioPro.sro[3].sdc0.sdcp1cw0   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcp1cw0 );
		IntErnals_RS_printf("ioPro.sro[3].sdc0.sdcp1cw1   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcp1cw1 );
		IntErnals_RS_printf("ioPro.sro[3].sdc0.sdcn1cw0   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcn1cw0 );
		IntErnals_RS_printf("ioPro.sro[3].sdc0.sdcn1cw1   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcn1cw1 );
		IntErnals_RS_printf("ioPro.sro[3].sdc0.sdcp2cw0   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcp2cw0 );
		IntErnals_RS_printf("ioPro.sro[3].sdc0.sdcp2cw1   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcp2cw1 );
		IntErnals_RS_printf("ioPro.sro[3].sdc0.sdcn2cw0   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcn2cw0 );
		IntErnals_RS_printf("ioPro.sro[3].sdc0.sdcn2cw1   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcn2cw1 );
		IntErnals_RS_printf("ioPro.sro[3].sdc0.sdcgmaxmin = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcgmaxmin );
		IntErnals_RS_printf("ioPro.sro[3].sdc0.sdcnmax    = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[0].sdcnmax );
		// SDC-1
		IntErnals_RS_printf("ioPro.sro[3].sdc1.sdctrg     = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdctrg );
		IntErnals_RS_printf("ioPro.sro[3].sdc1.sdcpaen    = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcpaen );
		IntErnals_RS_printf("ioPro.sro[3].sdc1.sdcctl     = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcctl );
		IntErnals_RS_printf("ioPro.sro[3].sdc1.sdcintenb  = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcintenb );
		IntErnals_RS_printf("ioPro.sro[3].sdc1.sdcintflg  = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcintflg );
		IntErnals_RS_printf("ioPro.sro[3].sdc1.sdcsgd     = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcsgd );
		IntErnals_RS_printf("ioPro.sro[3].sdc1.sdcph0     = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcph0 );
		IntErnals_RS_printf("ioPro.sro[3].sdc1.sdcph1     = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcph1 );
		IntErnals_RS_printf("ioPro.sro[3].sdc1.sdcphw0    = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcphw0 );
		IntErnals_RS_printf("ioPro.sro[3].sdc1.sdcphw1    = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcphw1 );
		IntErnals_RS_printf("ioPro.sro[3].sdc1.sdcp1hw0   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcp1hw0 );
		IntErnals_RS_printf("ioPro.sro[3].sdc1.sdcp1hw1   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcp1hw1 );
		IntErnals_RS_printf("ioPro.sro[3].sdc1.sdcn1hw0   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcn1hw0 );
		IntErnals_RS_printf("ioPro.sro[3].sdc1.sdcn1hw1   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcn1hw1 );
		IntErnals_RS_printf("ioPro.sro[3].sdc1.sdcp2hw0   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcp2hw0 );
		IntErnals_RS_printf("ioPro.sro[3].sdc1.sdcp2hw1   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcp2hw1 );
		IntErnals_RS_printf("ioPro.sro[3].sdc1.sdcn2hw0   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcn2hw0 );
		IntErnals_RS_printf("ioPro.sro[3].sdc1.sdcn2hw1   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcn2hw1 );
		IntErnals_RS_printf("ioPro.sro[3].sdc1.sdcpc0     = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcpc0 );
		IntErnals_RS_printf("ioPro.sro[3].sdc1.sdcpc1     = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcpc1 );
		IntErnals_RS_printf("ioPro.sro[3].sdc1.sdcpcw0    = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcpcw0 );
		IntErnals_RS_printf("ioPro.sro[3].sdc1.sdcpcw1    = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcpcw1 );
		IntErnals_RS_printf("ioPro.sro[3].sdc1.sdcp1cw0   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcp1cw0 );
		IntErnals_RS_printf("ioPro.sro[3].sdc1.sdcp1cw1   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcp1cw1 );
		IntErnals_RS_printf("ioPro.sro[3].sdc1.sdcn1cw0   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcn1cw0 );
		IntErnals_RS_printf("ioPro.sro[3].sdc1.sdcn1cw1   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcn1cw1 );
		IntErnals_RS_printf("ioPro.sro[3].sdc1.sdcp2cw0   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcp2cw0 );
		IntErnals_RS_printf("ioPro.sro[3].sdc1.sdcp2cw1   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcp2cw1 );
		IntErnals_RS_printf("ioPro.sro[3].sdc1.sdcn2cw0   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcn2cw0 );
		IntErnals_RS_printf("ioPro.sro[3].sdc1.sdcn2cw1   = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcn2cw1 );
		IntErnals_RS_printf("ioPro.sro[3].sdc1.sdcgmaxmin = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcgmaxmin );
		IntErnals_RS_printf("ioPro.sro[3].sdc1.sdcnmax    = %x\n", (kuint)&ioPro.imgPipe[2].sro.sdc[1].sdcnmax );
		// PZSFTB1
		IntErnals_RS_printf("ioPro.sro[3].pzsftb1.pzsfttrg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.pzsftb1.pzsfttrg );
		IntErnals_RS_printf("ioPro.sro[3].pzsftb1.pzofst        = %x\n", (kuint)&ioPro.imgPipe[2].sro.pzsftb1.pzofst );
		// DPC
		IntErnals_RS_printf("ioPro.sro[3].dpc.dpctrg            = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dpctrg );
		IntErnals_RS_printf("ioPro.sro[3].dpc.dpcpaen           = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dpcpaen );
		IntErnals_RS_printf("ioPro.sro[3].dpc.dpcgwp            = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dpcgwp );
		IntErnals_RS_printf("ioPro.sro[3].dpc.dpcgws            = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dpcgws );
		IntErnals_RS_printf("ioPro.sro[3].dpc.dpcwp             = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dpcwp );
		IntErnals_RS_printf("ioPro.sro[3].dpc.dpcws             = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dpcws );
		IntErnals_RS_printf("ioPro.sro[3].dpc.dpcmd             = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dpcmd );
		IntErnals_RS_printf("ioPro.sro[3].dpc.dpcblp            = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dpcblp );
		IntErnals_RS_printf("ioPro.sro[3].dpc.dpcblm            = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dpcblm );
		IntErnals_RS_printf("ioPro.sro[3].dpc.dfctl             = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dfctl );
		IntErnals_RS_printf("ioPro.sro[3].dpc.dfs               = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dfs );
		IntErnals_RS_printf("ioPro.sro[3].dpc.dfo               = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dfo );
		IntErnals_RS_printf("ioPro.sro[3].dpc.dfk               = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dfk );
		IntErnals_RS_printf("ioPro.sro[3].dpc.dfh               = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dfh );
		IntErnals_RS_printf("ioPro.sro[3].dpc.dfcsr             = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dfcsr );
		IntErnals_RS_printf("ioPro.sro[3].dpc.dflsth            = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dflsth );
		IntErnals_RS_printf("ioPro.sro[3].dpc.dfagef            = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dfagef );
		IntErnals_RS_printf("ioPro.sro[3].dpc.dfagef2           = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dfagef2 );
		IntErnals_RS_printf("ioPro.sro[3].dpc.dfagth            = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dfagth );
		IntErnals_RS_printf("ioPro.sro[3].dpc.dfagthk           = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dfagthk );
		IntErnals_RS_printf("ioPro.sro[3].dpc.dmctl             = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dmctl );
		IntErnals_RS_printf("ioPro.sro[3].dpc.dmwks             = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dmwks );
		IntErnals_RS_printf("ioPro.sro[3].dpc.dmwkd             = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dmwkd );
		IntErnals_RS_printf("ioPro.sro[3].dpc.dmagk             = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dmagk );
		IntErnals_RS_printf("ioPro.sro[3].dpc.dectl             = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dectl );
		IntErnals_RS_printf("ioPro.sro[3].dpc.denss             = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.denss );
		IntErnals_RS_printf("ioPro.sro[3].dpc.denso             = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.denso );
		IntErnals_RS_printf("ioPro.sro[3].dpc.densk             = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.densk );
		IntErnals_RS_printf("ioPro.sro[3].dpc.densh             = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.densh );
		IntErnals_RS_printf("ioPro.sro[3].dpc.densmgn           = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.densmgn );
		IntErnals_RS_printf("ioPro.sro[3].dpc.dendcth           = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dendcth );
		IntErnals_RS_printf("ioPro.sro[3].dpc.deagk             = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.deagk );
		IntErnals_RS_printf("ioPro.sro[3].dpc.dcagef            = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dcagef );
		IntErnals_RS_printf("ioPro.sro[3].dpc.dcagth            = %x\n", (kuint)&ioPro.imgPipe[2].sro.dpc.dcagth );
		// PZSFTB2
		IntErnals_RS_printf("ioPro.sro[3].pzsftb2.pzsfttrg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.pzsftb2.pzsfttrg );
		IntErnals_RS_printf("ioPro.sro[3].pzsftb2.pzofst        = %x\n", (kuint)&ioPro.imgPipe[2].sro.pzsftb2.pzofst );
		// FSHDL0
		IntErnals_RS_printf("ioPro.sro[3].fshdl0.ffshtrg        = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl0.ffshtrg );
		IntErnals_RS_printf("ioPro.sro[3].fshdl0.ffshpaen       = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl0.ffshpaen );
		IntErnals_RS_printf("ioPro.sro[3].fshdl0.ffshv          = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl0.ffshv );
		IntErnals_RS_printf("ioPro.sro[3].fshdl0.ffshh          = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl0.ffshh );
		IntErnals_RS_printf("ioPro.sro[3].fshdl0.ffshvw         = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl0.ffshvw );
		IntErnals_RS_printf("ioPro.sro[3].fshdl0.ffshhw         = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl0.ffshhw );
		IntErnals_RS_printf("ioPro.sro[3].fshdl0.ffshbc         = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl0.ffshbc );
		IntErnals_RS_printf("ioPro.sro[3].fshdl0.ffshul1        = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl0.ffshul1 );
		IntErnals_RS_printf("ioPro.sro[3].fshdl0.ffshul2        = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl0.ffshul2 );
		IntErnals_RS_printf("ioPro.sro[3].fshdl0.ffshgfmt       = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl0.ffshgfmt );
		IntErnals_RS_printf("ioPro.sro[3].fshdl0.ffshsubpr      = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl0.ffshsubpr );
		IntErnals_RS_printf("ioPro.sro[3].fshdl0.ffshsubsp      = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl0.ffshsubsp );
		IntErnals_RS_printf("ioPro.sro[3].fshdl0.ffshsubdr      = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl0.ffshsubdr );
		IntErnals_RS_printf("ioPro.sro[3].fshdl0.ffshsubst      = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl0.ffshsubst );
		IntErnals_RS_printf("ioPro.sro[3].fshdl0.ffshctl        = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl0.ffshctl );
		IntErnals_RS_printf("ioPro.sro[3].fshdl0.ffshhwph       = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl0.ffshhwph );
		IntErnals_RS_printf("ioPro.sro[3].fshdl0.ffshwric       = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl0.ffshwric );
		// AFPBA
		IntErnals_RS_printf("ioPro.sro[3].afpbA.afpbtrg         = %x\n", (kuint)&ioPro.imgPipe[2].sro.afpb[0].afpbtrg );
		IntErnals_RS_printf("ioPro.sro[3].afpbA.afpbv           = %x\n", (kuint)&ioPro.imgPipe[2].sro.afpb[0].afpbv );
		IntErnals_RS_printf("ioPro.sro[3].afpbA.afpbh           = %x\n", (kuint)&ioPro.imgPipe[2].sro.afpb[0].afpbh );
		IntErnals_RS_printf("ioPro.sro[3].afpbA.afpbvw          = %x\n", (kuint)&ioPro.imgPipe[2].sro.afpb[0].afpbvw );
		IntErnals_RS_printf("ioPro.sro[3].afpbA.afpbhw          = %x\n", (kuint)&ioPro.imgPipe[2].sro.afpb[0].afpbhw );
		// AFPBB
		IntErnals_RS_printf("ioPro.sro[3].afpbG.afpbtrg         = %x\n", (kuint)&ioPro.imgPipe[2].sro.afpb[1].afpbtrg );
		IntErnals_RS_printf("ioPro.sro[3].afpbG.afpbv           = %x\n", (kuint)&ioPro.imgPipe[2].sro.afpb[1].afpbv );
		IntErnals_RS_printf("ioPro.sro[3].afpbG.afpbh           = %x\n", (kuint)&ioPro.imgPipe[2].sro.afpb[1].afpbh );
		IntErnals_RS_printf("ioPro.sro[3].afpbG.afpbvw          = %x\n", (kuint)&ioPro.imgPipe[2].sro.afpb[1].afpbvw );
		IntErnals_RS_printf("ioPro.sro[3].afpbG.afpbhw          = %x\n", (kuint)&ioPro.imgPipe[2].sro.afpb[1].afpbhw );
		// PZSFTC1
		IntErnals_RS_printf("ioPro.sro[3].pzsftc1.pzsfttrg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.pzsftc1.pzsfttrg );
		IntErnals_RS_printf("ioPro.sro[3].pzsftc1.pzofst        = %x\n", (kuint)&ioPro.imgPipe[2].sro.pzsftc1.pzofst );
		// FFC
		IntErnals_RS_printf("ioPro.sro[3].ffc.fctrg             = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffc.fctrg );
		IntErnals_RS_printf("ioPro.sro[3].ffc.fcpaen            = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffc.fcpaen );
		IntErnals_RS_printf("ioPro.sro[3].ffc.fcv               = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffc.fcv );
		IntErnals_RS_printf("ioPro.sro[3].ffc.fch               = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffc.fch );
		IntErnals_RS_printf("ioPro.sro[3].ffc.fcvw              = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffc.fcvw );
		IntErnals_RS_printf("ioPro.sro[3].ffc.fchw              = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffc.fchw );
		IntErnals_RS_printf("ioPro.sro[3].ffc.fcbc              = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffc.fcbc );
		IntErnals_RS_printf("ioPro.sro[3].ffc.fcsubpr           = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffc.fcsubpr );
		IntErnals_RS_printf("ioPro.sro[3].ffc.fcsubsp           = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffc.fcsubsp );
		IntErnals_RS_printf("ioPro.sro[3].ffc.fcsubdr           = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffc.fcsubdr );
		IntErnals_RS_printf("ioPro.sro[3].ffc.fcsubst           = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffc.fcsubst );
		IntErnals_RS_printf("ioPro.sro[3].ffc.fcwric            = %x\n", (kuint)&ioPro.imgPipe[2].sro.ffc.fcwric );
		// CAG
		IntErnals_RS_printf("ioPro.sro[3].cag.cagtrg            = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.cagtrg );
		IntErnals_RS_printf("ioPro.sro[3].cag.cagpaen           = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.cagpaen );
		IntErnals_RS_printf("ioPro.sro[3].cag.caggwp            = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.caggwp );
		IntErnals_RS_printf("ioPro.sro[3].cag.caggws            = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.caggws );
		IntErnals_RS_printf("ioPro.sro[3].cag.cagwp             = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.cagwp );
		IntErnals_RS_printf("ioPro.sro[3].cag.cagws             = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.cagws );
		IntErnals_RS_printf("ioPro.sro[3].cag.cagmd             = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.cagmd );
		IntErnals_RS_printf("ioPro.sro[3].cag.rbr               = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.rbr );
		IntErnals_RS_printf("ioPro.sro[3].cag.aboarv            = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.aboarv );
		IntErnals_RS_printf("ioPro.sro[3].cag.aboarh            = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.aboarh );
		IntErnals_RS_printf("ioPro.sro[3].cag.aboagv            = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.aboagv );
		IntErnals_RS_printf("ioPro.sro[3].cag.aboagh            = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.aboagh );
		IntErnals_RS_printf("ioPro.sro[3].cag.aboabv            = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.aboabv );
		IntErnals_RS_printf("ioPro.sro[3].cag.aboabh            = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.aboabh );
		IntErnals_RS_printf("ioPro.sro[3].cag.abgar             = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abgar );
		IntErnals_RS_printf("ioPro.sro[3].cag.abgag             = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abgag );
		IntErnals_RS_printf("ioPro.sro[3].cag.abgab             = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abgab );
		IntErnals_RS_printf("ioPro.sro[3].cag.ablrv             = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.ablrv );
		IntErnals_RS_printf("ioPro.sro[3].cag.ablrh             = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.ablrh );
		IntErnals_RS_printf("ioPro.sro[3].cag.ablgv             = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.ablgv );
		IntErnals_RS_printf("ioPro.sro[3].cag.ablgh             = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.ablgh );
		IntErnals_RS_printf("ioPro.sro[3].cag.ablbv             = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.ablbv );
		IntErnals_RS_printf("ioPro.sro[3].cag.ablbh             = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.ablbh );
		IntErnals_RS_printf("ioPro.sro[3].cag.abofsrv           = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abofsrv );
		IntErnals_RS_printf("ioPro.sro[3].cag.abofsrh           = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abofsrh );
		IntErnals_RS_printf("ioPro.sro[3].cag.abofsgv           = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abofsgv );
		IntErnals_RS_printf("ioPro.sro[3].cag.abofsgh           = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abofsgh );
		IntErnals_RS_printf("ioPro.sro[3].cag.abofsbv           = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abofsbv );
		IntErnals_RS_printf("ioPro.sro[3].cag.abofsbh           = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abofsbh );
		IntErnals_RS_printf("ioPro.sro[3].cag.abnlthr1          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlthr1 );
		IntErnals_RS_printf("ioPro.sro[3].cag.abnlthg1          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlthg1 );
		IntErnals_RS_printf("ioPro.sro[3].cag.abnlthb1          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlthb1 );
		IntErnals_RS_printf("ioPro.sro[3].cag.abnlgar1          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlgar1 );
		IntErnals_RS_printf("ioPro.sro[3].cag.abnlgag1          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlgag1 );
		IntErnals_RS_printf("ioPro.sro[3].cag.abnlgab1          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlgab1 );
		IntErnals_RS_printf("ioPro.sro[3].cag.abnlthr2          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlthr2 );
		IntErnals_RS_printf("ioPro.sro[3].cag.abnlthg2          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlthg2 );
		IntErnals_RS_printf("ioPro.sro[3].cag.abnlthb2          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlthb2 );
		IntErnals_RS_printf("ioPro.sro[3].cag.abnlgar2          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlgar2 );
		IntErnals_RS_printf("ioPro.sro[3].cag.abnlgag2          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlgag2 );
		IntErnals_RS_printf("ioPro.sro[3].cag.abnlgab2          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlgab2 );
		IntErnals_RS_printf("ioPro.sro[3].cag.abnlthr3          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlthr3 );
		IntErnals_RS_printf("ioPro.sro[3].cag.abnlthg3          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlthg3 );
		IntErnals_RS_printf("ioPro.sro[3].cag.abnlthb3          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlthb3 );
		IntErnals_RS_printf("ioPro.sro[3].cag.abnlgar3          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlgar3 );
		IntErnals_RS_printf("ioPro.sro[3].cag.abnlgag3          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlgag3 );
		IntErnals_RS_printf("ioPro.sro[3].cag.abnlgab3          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlgab3 );
		IntErnals_RS_printf("ioPro.sro[3].cag.abnlthr4          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlthr4 );
		IntErnals_RS_printf("ioPro.sro[3].cag.abnlthg4          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlthg4 );
		IntErnals_RS_printf("ioPro.sro[3].cag.abnlthb4          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlthb4 );
		IntErnals_RS_printf("ioPro.sro[3].cag.abnlgar4          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlgar4 );
		IntErnals_RS_printf("ioPro.sro[3].cag.abnlgag4          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlgag4 );
		IntErnals_RS_printf("ioPro.sro[3].cag.abnlgab4          = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.abnlgab4 );
		IntErnals_RS_printf("ioPro.sro[3].cag.bfglmt            = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.bfglmt );
		IntErnals_RS_printf("ioPro.sro[3].cag.bfgth             = %x\n", (kuint)&ioPro.imgPipe[2].sro.cag.bfgth );
		// PZSFTC2
		IntErnals_RS_printf("ioPro.sro[3].pzsftc2.pzsfttrg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.pzsftc2.pzsfttrg );
		IntErnals_RS_printf("ioPro.sro[3].pzsftc2.pzofst        = %x\n", (kuint)&ioPro.imgPipe[2].sro.pzsftc2.pzofst );
		// FSHDL1
		IntErnals_RS_printf("ioPro.sro[3].fshdl1.ffshtrg        = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl1.ffshtrg );
		IntErnals_RS_printf("ioPro.sro[3].fshdl1.ffshpaen       = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl1.ffshpaen );
		IntErnals_RS_printf("ioPro.sro[3].fshdl1.ffshv          = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl1.ffshv );
		IntErnals_RS_printf("ioPro.sro[3].fshdl1.ffshh          = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl1.ffshh );
		IntErnals_RS_printf("ioPro.sro[3].fshdl1.ffshvw         = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl1.ffshvw );
		IntErnals_RS_printf("ioPro.sro[3].fshdl1.ffshhw         = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl1.ffshhw );
		IntErnals_RS_printf("ioPro.sro[3].fshdl1.ffshbc         = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl1.ffshbc );
		IntErnals_RS_printf("ioPro.sro[3].fshdl1.ffshul1        = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl1.ffshul1 );
		IntErnals_RS_printf("ioPro.sro[3].fshdl1.ffshul2        = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl1.ffshul2 );
		IntErnals_RS_printf("ioPro.sro[3].fshdl1.ffshgfmt       = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl1.ffshgfmt );
		IntErnals_RS_printf("ioPro.sro[3].fshdl1.ffshsubpr      = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl1.ffshsubpr );
		IntErnals_RS_printf("ioPro.sro[3].fshdl1.ffshsubsp      = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl1.ffshsubsp );
		IntErnals_RS_printf("ioPro.sro[3].fshdl1.ffshsubdr      = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl1.ffshsubdr );
		IntErnals_RS_printf("ioPro.sro[3].fshdl1.ffshsubst      = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl1.ffshsubst );
		IntErnals_RS_printf("ioPro.sro[3].fshdl1.ffshctl        = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl1.ffshctl );
		IntErnals_RS_printf("ioPro.sro[3].fshdl1.ffshhwph       = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl1.ffshhwph );
		IntErnals_RS_printf("ioPro.sro[3].fshdl1.ffshwric       = %x\n", (kuint)&ioPro.imgPipe[2].sro.fshdl1.ffshwric );
		// VRB
		IntErnals_RS_printf("ioPro.sro[3].vrb.vrbtrg            = %x\n", (kuint)&ioPro.imgPipe[2].sro.vrb.vrbtrg );
		IntErnals_RS_printf("ioPro.sro[3].vrb.vrbv              = %x\n", (kuint)&ioPro.imgPipe[2].sro.vrb.vrbv );
		IntErnals_RS_printf("ioPro.sro[3].vrb.vrbh              = %x\n", (kuint)&ioPro.imgPipe[2].sro.vrb.vrbh );
		IntErnals_RS_printf("ioPro.sro[3].vrb.vrbvw             = %x\n", (kuint)&ioPro.imgPipe[2].sro.vrb.vrbvw );
		IntErnals_RS_printf("ioPro.sro[3].vrb.vrbhw             = %x\n", (kuint)&ioPro.imgPipe[2].sro.vrb.vrbhw );
		IntErnals_RS_printf("ioPro.sro[3].vrb.vrbscyc           = %x\n", (kuint)&ioPro.imgPipe[2].sro.vrb.vrbscyc );
		IntErnals_RS_printf("ioPro.sro[3].vrb.vrbpaen           = %x\n", (kuint)&ioPro.imgPipe[2].sro.vrb.vrbpaen );
		IntErnals_RS_printf("ioPro.sro[3].vrb.vrb0k             = %x\n", (kuint)&ioPro.imgPipe[2].sro.vrb.vrb0k );
		IntErnals_RS_printf("ioPro.sro[3].vrb.vrb1k             = %x\n", (kuint)&ioPro.imgPipe[2].sro.vrb.vrb1k );
		// HRB
		IntErnals_RS_printf("ioPro.sro[3].hrb.hrbtrg            = %x\n", (kuint)&ioPro.imgPipe[2].sro.hrb.hrbtrg );
		IntErnals_RS_printf("ioPro.sro[3].hrb.hrbv              = %x\n", (kuint)&ioPro.imgPipe[2].sro.hrb.hrbv );
		IntErnals_RS_printf("ioPro.sro[3].hrb.hrbh              = %x\n", (kuint)&ioPro.imgPipe[2].sro.hrb.hrbh );
		IntErnals_RS_printf("ioPro.sro[3].hrb.hrbvw             = %x\n", (kuint)&ioPro.imgPipe[2].sro.hrb.hrbvw );
		IntErnals_RS_printf("ioPro.sro[3].hrb.hrbhw             = %x\n", (kuint)&ioPro.imgPipe[2].sro.hrb.hrbhw );
		IntErnals_RS_printf("ioPro.sro[3].hrb.hrbohw            = %x\n", (kuint)&ioPro.imgPipe[2].sro.hrb.hrbohw );
		IntErnals_RS_printf("ioPro.sro[3].hrb.hrbscyc           = %x\n", (kuint)&ioPro.imgPipe[2].sro.hrb.hrbscyc );
		IntErnals_RS_printf("ioPro.sro[3].hrb.hrbosm            = %x\n", (kuint)&ioPro.imgPipe[2].sro.hrb.hrbosm );
		IntErnals_RS_printf("ioPro.sro[3].hrb.hrbpaen           = %x\n", (kuint)&ioPro.imgPipe[2].sro.hrb.hrbpaen );
		IntErnals_RS_printf("ioPro.sro[3].hrb.hrbk              = %x\n", (kuint)&ioPro.imgPipe[2].sro.hrb.hrbk );
		// P2M-0
		IntErnals_RS_printf("ioPro.sro[3].p2m0.p2mtrg           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[0].p2mtrg );
		IntErnals_RS_printf("ioPro.sro[3].p2m0.p2mpaen          = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[0].p2mpaen );
		IntErnals_RS_printf("ioPro.sro[3].p2m0.p2mctl           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[0].p2mctl );
		IntErnals_RS_printf("ioPro.sro[3].p2m0.p2mofs           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[0].p2mofs );
		IntErnals_RS_printf("ioPro.sro[3].p2m0.pbsft            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[0].pbsft );
		IntErnals_RS_printf("ioPro.sro[3].p2m0.pclph            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[0].pclph );
		IntErnals_RS_printf("ioPro.sro[3].p2m0.ptrmv            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[0].ptrmv );
		IntErnals_RS_printf("ioPro.sro[3].p2m0.ptrmh            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[0].ptrmh );
		IntErnals_RS_printf("ioPro.sro[3].p2m0.ptrmvw           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[0].ptrmvw );
		IntErnals_RS_printf("ioPro.sro[3].p2m0.ptrmhw           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[0].ptrmhw );
		IntErnals_RS_printf("ioPro.sro[3].p2m0.ptrmxvcyc        = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[0].ptrmxvcyc );
		IntErnals_RS_printf("ioPro.sro[3].p2m0.ptrmxhcyc        = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[0].ptrmxhcyc );
		IntErnals_RS_printf("ioPro.sro[3].p2m0.ptrmxven         = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[0].ptrmxven );
		IntErnals_RS_printf("ioPro.sro[3].p2m0.ptrmxhen         = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[0].ptrmxhen );
		IntErnals_RS_printf("ioPro.sro[3].p2m0.p2mmir           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[0].p2mmir );
		// P2M-1
		IntErnals_RS_printf("ioPro.sro[3].p2m1.p2mtrg           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[1].p2mtrg );
		IntErnals_RS_printf("ioPro.sro[3].p2m1.p2mpaen          = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[1].p2mpaen );
		IntErnals_RS_printf("ioPro.sro[3].p2m1.p2mctl           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[1].p2mctl );
		IntErnals_RS_printf("ioPro.sro[3].p2m1.p2mofs           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[1].p2mofs );
		IntErnals_RS_printf("ioPro.sro[3].p2m1.pbsft            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[1].pbsft );
		IntErnals_RS_printf("ioPro.sro[3].p2m1.pclph            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[1].pclph );
		IntErnals_RS_printf("ioPro.sro[3].p2m1.ptrmv            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[1].ptrmv );
		IntErnals_RS_printf("ioPro.sro[3].p2m1.ptrmh            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[1].ptrmh );
		IntErnals_RS_printf("ioPro.sro[3].p2m1.ptrmvw           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[1].ptrmvw );
		IntErnals_RS_printf("ioPro.sro[3].p2m1.ptrmhw           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[1].ptrmhw );
		IntErnals_RS_printf("ioPro.sro[3].p2m1.ptrmxvcyc        = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[1].ptrmxvcyc );
		IntErnals_RS_printf("ioPro.sro[3].p2m1.ptrmxhcyc        = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[1].ptrmxhcyc );
		IntErnals_RS_printf("ioPro.sro[3].p2m1.ptrmxven         = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[1].ptrmxven );
		IntErnals_RS_printf("ioPro.sro[3].p2m1.ptrmxhen         = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[1].ptrmxhen );
		IntErnals_RS_printf("ioPro.sro[3].p2m1.p2mmir           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[1].p2mmir );
		// P2M-2
		IntErnals_RS_printf("ioPro.sro[3].p2m2.p2mtrg           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[2].p2mtrg );
		IntErnals_RS_printf("ioPro.sro[3].p2m2.p2mpaen          = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[2].p2mpaen );
		IntErnals_RS_printf("ioPro.sro[3].p2m2.p2mctl           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[2].p2mctl );
		IntErnals_RS_printf("ioPro.sro[3].p2m2.p2mofs           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[2].p2mofs );
		IntErnals_RS_printf("ioPro.sro[3].p2m2.pbsft            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[2].pbsft );
		IntErnals_RS_printf("ioPro.sro[3].p2m2.pclph            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[2].pclph );
		IntErnals_RS_printf("ioPro.sro[3].p2m2.ptrmv            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[2].ptrmv );
		IntErnals_RS_printf("ioPro.sro[3].p2m2.ptrmh            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[2].ptrmh );
		IntErnals_RS_printf("ioPro.sro[3].p2m2.ptrmvw           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[2].ptrmvw );
		IntErnals_RS_printf("ioPro.sro[3].p2m2.ptrmhw           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[2].ptrmhw );
		IntErnals_RS_printf("ioPro.sro[3].p2m2.ptrmxvcyc        = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[2].ptrmxvcyc );
		IntErnals_RS_printf("ioPro.sro[3].p2m2.ptrmxhcyc        = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[2].ptrmxhcyc );
		IntErnals_RS_printf("ioPro.sro[3].p2m2.ptrmxven         = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[2].ptrmxven );
		IntErnals_RS_printf("ioPro.sro[3].p2m2.ptrmxhen         = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[2].ptrmxhen );
		IntErnals_RS_printf("ioPro.sro[3].p2m2.p2mmir           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[2].p2mmir );
		// P2M-3
		IntErnals_RS_printf("ioPro.sro[3].p2m3.p2mtrg           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[3].p2mtrg );
		IntErnals_RS_printf("ioPro.sro[3].p2m3.p2mpaen          = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[3].p2mpaen );
		IntErnals_RS_printf("ioPro.sro[3].p2m3.p2mctl           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[3].p2mctl );
		IntErnals_RS_printf("ioPro.sro[3].p2m3.p2mofs           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[3].p2mofs );
		IntErnals_RS_printf("ioPro.sro[3].p2m3.pbsft            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[3].pbsft );
		IntErnals_RS_printf("ioPro.sro[3].p2m3.pclph            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[3].pclph );
		IntErnals_RS_printf("ioPro.sro[3].p2m3.ptrmv            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[3].ptrmv );
		IntErnals_RS_printf("ioPro.sro[3].p2m3.ptrmh            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[3].ptrmh );
		IntErnals_RS_printf("ioPro.sro[3].p2m3.ptrmvw           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[3].ptrmvw );
		IntErnals_RS_printf("ioPro.sro[3].p2m3.ptrmhw           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[3].ptrmhw );
		IntErnals_RS_printf("ioPro.sro[3].p2m3.ptrmxvcyc        = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[3].ptrmxvcyc );
		IntErnals_RS_printf("ioPro.sro[3].p2m3.ptrmxhcyc        = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[3].ptrmxhcyc );
		IntErnals_RS_printf("ioPro.sro[3].p2m3.ptrmxven         = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[3].ptrmxven );
		IntErnals_RS_printf("ioPro.sro[3].p2m3.ptrmxhen         = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[3].ptrmxhen );
		IntErnals_RS_printf("ioPro.sro[3].p2m3.p2mmir           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[3].p2mmir );
		// P2M-4
		IntErnals_RS_printf("ioPro.sro[3].p2m4.p2mtrg           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[4].p2mtrg );
		IntErnals_RS_printf("ioPro.sro[3].p2m4.p2mpaen          = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[4].p2mpaen );
		IntErnals_RS_printf("ioPro.sro[3].p2m4.p2mctl           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[4].p2mctl );
		IntErnals_RS_printf("ioPro.sro[3].p2m4.p2mofs           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[4].p2mofs );
		IntErnals_RS_printf("ioPro.sro[3].p2m4.pbsft            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[4].pbsft );
		IntErnals_RS_printf("ioPro.sro[3].p2m4.pclph            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[4].pclph );
		IntErnals_RS_printf("ioPro.sro[3].p2m4.ptrmv            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[4].ptrmv );
		IntErnals_RS_printf("ioPro.sro[3].p2m4.ptrmh            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[4].ptrmh );
		IntErnals_RS_printf("ioPro.sro[3].p2m4.ptrmvw           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[4].ptrmvw );
		IntErnals_RS_printf("ioPro.sro[3].p2m4.ptrmhw           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[4].ptrmhw );
		IntErnals_RS_printf("ioPro.sro[3].p2m4.ptrmxvcyc        = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[4].ptrmxvcyc );
		IntErnals_RS_printf("ioPro.sro[3].p2m4.ptrmxhcyc        = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[4].ptrmxhcyc );
		IntErnals_RS_printf("ioPro.sro[3].p2m4.ptrmxven         = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[4].ptrmxven );
		IntErnals_RS_printf("ioPro.sro[3].p2m4.ptrmxhen         = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[4].ptrmxhen );
		IntErnals_RS_printf("ioPro.sro[3].p2m4.p2mmir           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[4].p2mmir );
		// P2M-5
		IntErnals_RS_printf("ioPro.sro[3].p2m5.p2mtrg           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[5].p2mtrg );
		IntErnals_RS_printf("ioPro.sro[3].p2m5.p2mpaen          = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[5].p2mpaen );
		IntErnals_RS_printf("ioPro.sro[3].p2m5.p2mctl           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[5].p2mctl );
		IntErnals_RS_printf("ioPro.sro[3].p2m5.p2mofs           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[5].p2mofs );
		IntErnals_RS_printf("ioPro.sro[3].p2m5.pbsft            = %x\n", (kuint)&ioPro.imgPipe[2].sro.P2M[5].pbsft );
		IntErnals_RS_printf("ioPro.sro[3].p2m5.pclph            = %x\n", (kuint)&ioPro.imgPipe[2].sro.P2M[5].pclph );
		IntErnals_RS_printf("ioPro.sro[3].p2m5.ptrmv            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[5].ptrmv );
		IntErnals_RS_printf("ioPro.sro[3].p2m5.ptrmh            = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[5].ptrmh );
		IntErnals_RS_printf("ioPro.sro[3].p2m5.ptrmvw           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[5].ptrmvw );
		IntErnals_RS_printf("ioPro.sro[3].p2m5.ptrmhw           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[5].ptrmhw );
		IntErnals_RS_printf("ioPro.sro[3].p2m5.ptrmxvcyc        = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[5].ptrmxvcyc );
		IntErnals_RS_printf("ioPro.sro[3].p2m5.ptrmxhcyc        = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[5].ptrmxhcyc );
		IntErnals_RS_printf("ioPro.sro[3].p2m5.ptrmxven         = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[5].ptrmxven );
		IntErnals_RS_printf("ioPro.sro[3].p2m5.ptrmxhen         = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[5].ptrmxhen );
		IntErnals_RS_printf("ioPro.sro[3].p2m5.p2mmir           = %x\n", (kuint)&ioPro.imgPipe[2].sro.p2m[5].p2mmir );
		// PWCH-0
		IntErnals_RS_printf("ioPro.sro[3].pwch0.pwchtrg         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[0].pwchtrg );
		IntErnals_RS_printf("ioPro.sro[3].pwch0.pws             = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[0].pws );
		IntErnals_RS_printf("ioPro.sro[3].pwch0.pwaxctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[0].pwaxctl );
		IntErnals_RS_printf("ioPro.sro[3].pwch0.pwchctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[0].pwchctl );
		IntErnals_RS_printf("ioPro.sro[3].pwch0.pwchintenb      = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[0].pwchintenb );
		IntErnals_RS_printf("ioPro.sro[3].pwch0.pwchintflg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[0].pwchintflg );
		IntErnals_RS_printf("ioPro.sro[3].pwch0.pwchbresp       = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[0].pwchbresp );
		IntErnals_RS_printf("ioPro.sro[3].pwch0.pwsa            = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[0].pwsa );
		IntErnals_RS_printf("ioPro.sro[3].pwch0.pwlsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[0].pwlsize );
		// PWCH-1
		IntErnals_RS_printf("ioPro.sro[3].pwch1.pwchtrg         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[1].pwchtrg );
		IntErnals_RS_printf("ioPro.sro[3].pwch1.pws             = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[1].pws );
		IntErnals_RS_printf("ioPro.sro[3].pwch1.pwaxctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[1].pwaxctl );
		IntErnals_RS_printf("ioPro.sro[3].pwch1.pwchctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[1].pwchctl );
		IntErnals_RS_printf("ioPro.sro[3].pwch1.pwchintenb      = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[1].pwchintenb );
		IntErnals_RS_printf("ioPro.sro[3].pwch1.pwchintflg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[1].pwchintflg );
		IntErnals_RS_printf("ioPro.sro[3].pwch1.pwchbresp       = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[1].pwchbresp );
		IntErnals_RS_printf("ioPro.sro[3].pwch1.pwsa            = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[1].pwsa );
		IntErnals_RS_printf("ioPro.sro[3].pwch1.pwlsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[1].pwlsize );
		// PWCH-2
		IntErnals_RS_printf("ioPro.sro[3].pwch2.pwchtrg         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[2].pwchtrg );
		IntErnals_RS_printf("ioPro.sro[3].pwch2.pws             = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[2].pws );
		IntErnals_RS_printf("ioPro.sro[3].pwch2.pwaxctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[2].pwaxctl );
		IntErnals_RS_printf("ioPro.sro[3].pwch2.pwchctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[2].pwchctl );
		IntErnals_RS_printf("ioPro.sro[3].pwch2.pwchintenb      = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[2].pwchintenb );
		IntErnals_RS_printf("ioPro.sro[3].pwch2.pwchintflg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[2].pwchintflg );
		IntErnals_RS_printf("ioPro.sro[3].pwch2.pwchbresp       = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[2].pwchbresp );
		IntErnals_RS_printf("ioPro.sro[3].pwch2.pwsa            = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[2].pwsa );
		IntErnals_RS_printf("ioPro.sro[3].pwch2.pwlsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[2].pwlsize );
		// PWCH-3
		IntErnals_RS_printf("ioPro.sro[3].pwch3.pwchtrg         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[3].pwchtrg );
		IntErnals_RS_printf("ioPro.sro[3].pwch3.pws             = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[3].pws );
		IntErnals_RS_printf("ioPro.sro[3].pwch3.pwaxctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[3].pwaxctl );
		IntErnals_RS_printf("ioPro.sro[3].pwch3.pwchctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[3].pwchctl );
		IntErnals_RS_printf("ioPro.sro[3].pwch3.pwchintenb      = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[3].pwchintenb );
		IntErnals_RS_printf("ioPro.sro[3].pwch3.pwchintflg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[3].pwchintflg );
		IntErnals_RS_printf("ioPro.sro[3].pwch3.pwchbresp       = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[3].pwchbresp );
		IntErnals_RS_printf("ioPro.sro[3].pwch3.pwsa            = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[3].pwsa );
		IntErnals_RS_printf("ioPro.sro[3].pwch3.pwlsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[3].pwlsize );
		// PWCH-4
		IntErnals_RS_printf("ioPro.sro[3].pwch4.pwchtrg         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[4].pwchtrg );
		IntErnals_RS_printf("ioPro.sro[3].pwch4.pws             = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[4].pws );
		IntErnals_RS_printf("ioPro.sro[3].pwch4.pwaxctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[4].pwaxctl );
		IntErnals_RS_printf("ioPro.sro[3].pwch4.pwchctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[4].pwchctl );
		IntErnals_RS_printf("ioPro.sro[3].pwch4.pwchintenb      = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[4].pwchintenb );
		IntErnals_RS_printf("ioPro.sro[3].pwch4.pwchintflg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[4].pwchintflg );
		IntErnals_RS_printf("ioPro.sro[3].pwch4.pwchbresp       = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[4].pwchbresp );
		IntErnals_RS_printf("ioPro.sro[3].pwch4.pwsa            = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[4].pwsa );
		IntErnals_RS_printf("ioPro.sro[3].pwch4.pwlsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[4].pwlsize );
		// PWCH-5
		IntErnals_RS_printf("ioPro.sro[3].pwch5.pwchtrg         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[5].pwchtrg );
		IntErnals_RS_printf("ioPro.sro[3].pwch5.pws             = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[5].pws );
		IntErnals_RS_printf("ioPro.sro[3].pwch5.pwaxctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[5].pwaxctl );
		IntErnals_RS_printf("ioPro.sro[3].pwch5.pwchctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[5].pwchctl );
		IntErnals_RS_printf("ioPro.sro[3].pwch5.pwchintenb      = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[5].pwchintenb );
		IntErnals_RS_printf("ioPro.sro[3].pwch5.pwchintflg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[5].pwchintflg );
		IntErnals_RS_printf("ioPro.sro[3].pwch5.pwchbresp       = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[5].pwchbresp );
		IntErnals_RS_printf("ioPro.sro[3].pwch5.pwsa            = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[5].pwsa );
		IntErnals_RS_printf("ioPro.sro[3].pwch5.pwlsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.pwch[5].pwlsize );
		// M2P-0
		IntErnals_RS_printf("ioPro.sro[3].m2p0.m2ptrg           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[0].m2ptrg );
		IntErnals_RS_printf("ioPro.sro[3].m2p0.m2ppaen          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[0].m2ppaen );
		IntErnals_RS_printf("ioPro.sro[3].m2p0.m2pctl           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[0].m2pctl );
		IntErnals_RS_printf("ioPro.sro[3].m2p0.m2pbsft          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[0].m2pbsft );
		IntErnals_RS_printf("ioPro.sro[3].m2p0.m2pofs           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[0].m2pofs );
		IntErnals_RS_printf("ioPro.sro[3].m2p0.m2pclip          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[0].m2pclip );
		// M2P-1
		IntErnals_RS_printf("ioPro.sro[3].m2p1.m2ptrg           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[1].m2ptrg );
		IntErnals_RS_printf("ioPro.sro[3].m2p1.m2ppaen          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[1].m2ppaen );
		IntErnals_RS_printf("ioPro.sro[3].m2p1.m2pctl           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[1].m2pctl );
		IntErnals_RS_printf("ioPro.sro[3].m2p1.m2pbsft          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[1].m2pbsft );
		IntErnals_RS_printf("ioPro.sro[3].m2p1.m2pofs           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[1].m2pofs );
		IntErnals_RS_printf("ioPro.sro[3].m2p1.m2pclip          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[1].m2pclip );
		// M2P-2
		IntErnals_RS_printf("ioPro.sro[3].m2p2.m2ptrg           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[2].m2ptrg );
		IntErnals_RS_printf("ioPro.sro[3].m2p2.m2ppaen          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[2].m2ppaen );
		IntErnals_RS_printf("ioPro.sro[3].m2p2.m2pctl           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[2].m2pctl );
		IntErnals_RS_printf("ioPro.sro[3].m2p2.m2pbsft          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[2].m2pbsft );
		IntErnals_RS_printf("ioPro.sro[3].m2p2.m2pofs           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[2].m2pofs );
		IntErnals_RS_printf("ioPro.sro[3].m2p2.m2pclip          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[2].m2pclip );
		// M2P-3
		IntErnals_RS_printf("ioPro.sro[3].m2p3.m2ptrg           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[3].m2ptrg );
		IntErnals_RS_printf("ioPro.sro[3].m2p3.m2ppaen          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[3].m2ppaen );
		IntErnals_RS_printf("ioPro.sro[3].m2p3.m2pctl           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[3].m2pctl );
		IntErnals_RS_printf("ioPro.sro[3].m2p3.m2pbsft          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[3].m2pbsft );
		IntErnals_RS_printf("ioPro.sro[3].m2p3.m2pofs           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[3].m2pofs );
		IntErnals_RS_printf("ioPro.sro[3].m2p3.m2pclip          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[3].m2pclip );
		// M2P-6
		IntErnals_RS_printf("ioPro.sro[3].m2p6.m2ptrg           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[4].m2ptrg );
		IntErnals_RS_printf("ioPro.sro[3].m2p6.m2ppaen          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[4].m2ppaen );
		IntErnals_RS_printf("ioPro.sro[3].m2p6.m2pctl           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[4].m2pctl );
		IntErnals_RS_printf("ioPro.sro[3].m2p6.m2pbsft          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[4].m2pbsft );
		IntErnals_RS_printf("ioPro.sro[3].m2p6.m2pofs           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[4].m2pofs );
		IntErnals_RS_printf("ioPro.sro[3].m2p6.m2pclip          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[4].m2pclip );
		// M2P-7
		IntErnals_RS_printf("ioPro.sro[3].m2p7.m2ptrg           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[5].m2ptrg );
		IntErnals_RS_printf("ioPro.sro[3].m2p7.m2ppaen          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[5].m2ppaen );
		IntErnals_RS_printf("ioPro.sro[3].m2p7.m2pctl           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[5].m2pctl );
		IntErnals_RS_printf("ioPro.sro[3].m2p7.m2pbsft          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[5].m2pbsft );
		IntErnals_RS_printf("ioPro.sro[3].m2p7.m2pofs           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[5].m2pofs );
		IntErnals_RS_printf("ioPro.sro[3].m2p7.m2pclip          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[5].m2pclip );
		// M2P-8
		IntErnals_RS_printf("ioPro.sro[3].m2p8.m2ptrg           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[6].m2ptrg );
		IntErnals_RS_printf("ioPro.sro[3].m2p8.m2ppaen          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[6].m2ppaen );
		IntErnals_RS_printf("ioPro.sro[3].m2p8.m2pctl           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[6].m2pctl );
		IntErnals_RS_printf("ioPro.sro[3].m2p8.m2pbsft          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[6].m2pbsft );
		IntErnals_RS_printf("ioPro.sro[3].m2p8.m2pofs           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[6].m2pofs );
		IntErnals_RS_printf("ioPro.sro[3].m2p8.m2pclip          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[6].m2pclip );
		// M2P-0
		IntErnals_RS_printf("ioPro.sro[3].m2p9.m2ptrg           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[7].m2ptrg );
		IntErnals_RS_printf("ioPro.sro[3].m2p9.m2ppaen          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[7].m2ppaen );
		IntErnals_RS_printf("ioPro.sro[3].m2p9.m2pctl           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[7].m2pctl );
		IntErnals_RS_printf("ioPro.sro[3].m2p9.m2pbsft          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[7].m2pbsft );
		IntErnals_RS_printf("ioPro.sro[3].m2p9.m2pofs           = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[7].m2pofs );
		IntErnals_RS_printf("ioPro.sro[3].m2p9.m2pclip          = %x\n", (kuint)&ioPro.imgPipe[2].sro.m2p[7].m2pclip );
		// PRCH-0
		IntErnals_RS_printf("ioPro.sro[3].prch0.prchtrg         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[0].prchtrg );
		IntErnals_RS_printf("ioPro.sro[3].prch0.prchctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[0].prchctl );
		IntErnals_RS_printf("ioPro.sro[3].prch0.prchrs          = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[0].prchrs );
		IntErnals_RS_printf("ioPro.sro[3].prch0.praxctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[0].praxctl );
		IntErnals_RS_printf("ioPro.sro[3].prch0.prchintenb      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[0].prchintenb );
		IntErnals_RS_printf("ioPro.sro[3].prch0.prchintflg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[0].prchintflg );
		IntErnals_RS_printf("ioPro.sro[3].prch0.prchbresp       = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[0].prchbresp );
		IntErnals_RS_printf("ioPro.sro[3].prch0.prsa            = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[0].prsa );
		IntErnals_RS_printf("ioPro.sro[3].prch0.prlsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[0].prlsize );
		IntErnals_RS_printf("ioPro.sro[3].prch0.prvsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[0].prvsize );
		IntErnals_RS_printf("ioPro.sro[3].prch0.prhsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[0].prhsize );
		// PRCH-1
		IntErnals_RS_printf("ioPro.sro[3].prch1.prchtrg         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[1].prchtrg );
		IntErnals_RS_printf("ioPro.sro[3].prch1.prchctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[1].prchctl );
		IntErnals_RS_printf("ioPro.sro[3].prch1.prchrs          = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[1].prchrs );
		IntErnals_RS_printf("ioPro.sro[3].prch1.praxctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[1].praxctl );
		IntErnals_RS_printf("ioPro.sro[3].prch1.prchintenb      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[1].prchintenb );
		IntErnals_RS_printf("ioPro.sro[3].prch1.prchintflg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[1].prchintflg );
		IntErnals_RS_printf("ioPro.sro[3].prch1.prchbresp       = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[1].prchbresp );
		IntErnals_RS_printf("ioPro.sro[3].prch1.prsa            = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[1].prsa );
		IntErnals_RS_printf("ioPro.sro[3].prch1.prlsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[1].prlsize );
		IntErnals_RS_printf("ioPro.sro[3].prch1.prvsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[1].prvsize );
		IntErnals_RS_printf("ioPro.sro[3].prch1.prhsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[1].prhsize );
		// PRCH-2
		IntErnals_RS_printf("ioPro.sro[3].prch2.prchtrg         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[2].prchtrg );
		IntErnals_RS_printf("ioPro.sro[3].prch2.prchctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[2].prchctl );
		IntErnals_RS_printf("ioPro.sro[3].prch2.prchrs          = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[2].prchrs );
		IntErnals_RS_printf("ioPro.sro[3].prch2.praxctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[2].praxctl );
		IntErnals_RS_printf("ioPro.sro[3].prch2.prchintenb      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[2].prchintenb );
		IntErnals_RS_printf("ioPro.sro[3].prch2.prchintflg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[2].prchintflg );
		IntErnals_RS_printf("ioPro.sro[3].prch2.prchbresp       = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[2].prchbresp );
		IntErnals_RS_printf("ioPro.sro[3].prch2.prsa            = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[2].prsa );
		IntErnals_RS_printf("ioPro.sro[3].prch2.prlsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[2].prlsize );
		IntErnals_RS_printf("ioPro.sro[3].prch2.prvsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[2].prvsize );
		IntErnals_RS_printf("ioPro.sro[3].prch2.prhsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[2].prhsize );
		// PRCH-3
		IntErnals_RS_printf("ioPro.sro[3].prch3.prchtrg         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[3].prchtrg );
		IntErnals_RS_printf("ioPro.sro[3].prch3.prchctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[3].prchctl );
		IntErnals_RS_printf("ioPro.sro[3].prch3.prchrs          = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[3].prchrs );
		IntErnals_RS_printf("ioPro.sro[3].prch3.praxctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[3].praxctl );
		IntErnals_RS_printf("ioPro.sro[3].prch3.prchintenb      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[3].prchintenb );
		IntErnals_RS_printf("ioPro.sro[3].prch3.prchintflg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[3].prchintflg );
		IntErnals_RS_printf("ioPro.sro[3].prch3.prchbresp       = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[3].prchbresp );
		IntErnals_RS_printf("ioPro.sro[3].prch3.prsa            = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[3].prsa );
		IntErnals_RS_printf("ioPro.sro[3].prch3.prlsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[3].prlsize );
		IntErnals_RS_printf("ioPro.sro[3].prch3.prvsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[3].prvsize );
		IntErnals_RS_printf("ioPro.sro[3].prch3.prhsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[3].prhsize );
		// PRCH-4
		IntErnals_RS_printf("ioPro.sro[3].prch4.prchtrg         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[4].prchtrg );
		IntErnals_RS_printf("ioPro.sro[3].prch4.prchctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[4].prchctl );
		IntErnals_RS_printf("ioPro.sro[3].prch4.prchrs          = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[4].prchrs );
		IntErnals_RS_printf("ioPro.sro[3].prch4.praxctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[4].praxctl );
		IntErnals_RS_printf("ioPro.sro[3].prch4.prchintenb      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[4].prchintenb );
		IntErnals_RS_printf("ioPro.sro[3].prch4.prchintflg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[4].prchintflg );
		IntErnals_RS_printf("ioPro.sro[3].prch4.prchbresp       = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[4].prchbresp );
		IntErnals_RS_printf("ioPro.sro[3].prch4.prsa            = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[4].prsa );
		IntErnals_RS_printf("ioPro.sro[3].prch4.prlsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[4].prlsize );
		IntErnals_RS_printf("ioPro.sro[3].prch4.prvsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[4].prvsize );
		IntErnals_RS_printf("ioPro.sro[3].prch4.prhsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[4].prhsize );
		// PRCH-5
		IntErnals_RS_printf("ioPro.sro[3].prch5.prchtrg         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[5].prchtrg );
		IntErnals_RS_printf("ioPro.sro[3].prch5.prchctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[5].prchctl );
		IntErnals_RS_printf("ioPro.sro[3].prch5.prchrs          = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[5].prchrs );
		IntErnals_RS_printf("ioPro.sro[3].prch5.praxctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[5].praxctl );
		IntErnals_RS_printf("ioPro.sro[3].prch5.prchintenb      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[5].prchintenb );
		IntErnals_RS_printf("ioPro.sro[3].prch5.prchintflg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[5].prchintflg );
		IntErnals_RS_printf("ioPro.sro[3].prch5.prchbresp       = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[5].prchbresp );
		IntErnals_RS_printf("ioPro.sro[3].prch5.prsa            = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[5].prsa );
		IntErnals_RS_printf("ioPro.sro[3].prch5.prlsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[5].prlsize );
		IntErnals_RS_printf("ioPro.sro[3].prch5.prvsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[5].prvsize );
		IntErnals_RS_printf("ioPro.sro[3].prch5.prhsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[5].prhsize );
		// PRCH-6
		IntErnals_RS_printf("ioPro.sro[3].prch6.prchtrg         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[6].prchtrg );
		IntErnals_RS_printf("ioPro.sro[3].prch6.prchctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[6].prchctl );
		IntErnals_RS_printf("ioPro.sro[3].prch6.prchrs          = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[6].prchrs );
		IntErnals_RS_printf("ioPro.sro[3].prch6.praxctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[6].praxctl );
		IntErnals_RS_printf("ioPro.sro[3].prch6.prchintenb      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[6].prchintenb );
		IntErnals_RS_printf("ioPro.sro[3].prch6.prchintflg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[6].prchintflg );
		IntErnals_RS_printf("ioPro.sro[3].prch6.prchbresp       = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[6].prchbresp );
		IntErnals_RS_printf("ioPro.sro[3].prch6.prsa            = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[6].prsa );
		IntErnals_RS_printf("ioPro.sro[3].prch6.prlsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[6].prlsize );
		IntErnals_RS_printf("ioPro.sro[3].prch6.prvsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[6].prvsize );
		IntErnals_RS_printf("ioPro.sro[3].prch6.prhsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[6].prhsize );
		// PRCH-7
		IntErnals_RS_printf("ioPro.sro[3].prch7.prchtrg         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[7].prchtrg );
		IntErnals_RS_printf("ioPro.sro[3].prch7.prchctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[7].prchctl );
		IntErnals_RS_printf("ioPro.sro[3].prch7.prchrs          = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[7].prchrs );
		IntErnals_RS_printf("ioPro.sro[3].prch7.praxctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[7].praxctl );
		IntErnals_RS_printf("ioPro.sro[3].prch7.prchintenb      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[7].prchintenb );
		IntErnals_RS_printf("ioPro.sro[3].prch7.prchintflg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[7].prchintflg );
		IntErnals_RS_printf("ioPro.sro[3].prch7.prchbresp       = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[7].prchbresp );
		IntErnals_RS_printf("ioPro.sro[3].prch7.prsa            = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[7].prsa );
		IntErnals_RS_printf("ioPro.sro[3].prch7.prlsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[7].prlsize );
		IntErnals_RS_printf("ioPro.sro[3].prch7.prvsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[7].prvsize );
		IntErnals_RS_printf("ioPro.sro[3].prch7.prhsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[7].prhsize );
		// PRCH-8
		IntErnals_RS_printf("ioPro.sro[3].prch8.prchtrg         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[8].prchtrg );
		IntErnals_RS_printf("ioPro.sro[3].prch8.prchctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[8].prchctl );
		IntErnals_RS_printf("ioPro.sro[3].prch8.prchrs          = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[8].prchrs );
		IntErnals_RS_printf("ioPro.sro[3].prch8.praxctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[8].praxctl );
		IntErnals_RS_printf("ioPro.sro[3].prch8.prchintenb      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[8].prchintenb );
		IntErnals_RS_printf("ioPro.sro[3].prch8.prchintflg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[8].prchintflg );
		IntErnals_RS_printf("ioPro.sro[3].prch8.prchbresp       = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[8].prchbresp );
		IntErnals_RS_printf("ioPro.sro[3].prch8.prsa            = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[8].prsa );
		IntErnals_RS_printf("ioPro.sro[3].prch8.prlsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[8].prlsize );
		IntErnals_RS_printf("ioPro.sro[3].prch8.prvsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[8].prvsize );
		IntErnals_RS_printf("ioPro.sro[3].prch8.prhsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[8].prhsize );
		// PRCH-9
		IntErnals_RS_printf("ioPro.sro[3].prch9.prchtrg         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[9].prchtrg );
		IntErnals_RS_printf("ioPro.sro[3].prch9.prchctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[9].prchctl );
		IntErnals_RS_printf("ioPro.sro[3].prch9.prchrs          = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[9].prchrs );
		IntErnals_RS_printf("ioPro.sro[3].prch9.praxctl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[9].praxctl );
		IntErnals_RS_printf("ioPro.sro[3].prch9.prchintenb      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[9].prchintenb );
		IntErnals_RS_printf("ioPro.sro[3].prch9.prchintflg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[9].prchintflg );
		IntErnals_RS_printf("ioPro.sro[3].prch9.prchbresp       = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[9].prchbresp );
		IntErnals_RS_printf("ioPro.sro[3].prch9.prsa            = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[9].prsa );
		IntErnals_RS_printf("ioPro.sro[3].prch9.prlsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[9].prlsize );
		IntErnals_RS_printf("ioPro.sro[3].prch9.prvsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[9].prvsize );
		IntErnals_RS_printf("ioPro.sro[3].prch9.prhsize         = %x\n", (kuint)&ioPro.imgPipe[2].sro.prch[9].prhsize );
		// MONI-0
		IntErnals_RS_printf("ioPro.sro[3].moni0.monitrg         = %x\n", (kuint)&ioPro.imgPipe[2].sro.moni0.monitrg );
		IntErnals_RS_printf("ioPro.sro[3].moni0.monictl         = %x\n", (kuint)&ioPro.imgPipe[2].sro.moni0.monictl );
		IntErnals_RS_printf("ioPro.sro[3].moni0.moniintflg      = %x\n", (kuint)&ioPro.imgPipe[2].sro.moni0.moniintflg );
		IntErnals_RS_printf("ioPro.sro[3].moni0.moniintenb      = %x\n", (kuint)&ioPro.imgPipe[2].sro.moni0.moniintenb );
		IntErnals_RS_printf("ioPro.sro[3].moni0.monivd          = %x\n", (kuint)&ioPro.imgPipe[2].sro.moni0.monivd );
		IntErnals_RS_printf("ioPro.sro[3].moni0.monihd          = %x\n", (kuint)&ioPro.imgPipe[2].sro.moni0.monihd );
		IntErnals_RS_printf("ioPro.sro[3].moni0.moniepf         = %x\n", (kuint)&ioPro.imgPipe[2].sro.moni0.moniepf );
		IntErnals_RS_printf("ioPro.sro[3].moni0.monieplmin      = %x\n", (kuint)&ioPro.imgPipe[2].sro.moni0.monieplmin );
		IntErnals_RS_printf("ioPro.sro[3].moni0.monieplmax      = %x\n", (kuint)&ioPro.imgPipe[2].sro.moni0.monieplmax );
		IntErnals_RS_printf("ioPro.sro[3].moni0.moniblf         = %x\n", (kuint)&ioPro.imgPipe[2].sro.moni0.moniblf );
		IntErnals_RS_printf("ioPro.sro[3].moni0.monibllmin      = %x\n", (kuint)&ioPro.imgPipe[2].sro.moni0.monibllmin );
		IntErnals_RS_printf("ioPro.sro[3].moni0.monibllmax      = %x\n", (kuint)&ioPro.imgPipe[2].sro.moni0.monibllmax );
		IntErnals_RS_printf("ioPro.sro[3].moni0.monihdexp       = %x\n", (kuint)&ioPro.imgPipe[2].sro.moni0.monihdexp );
		IntErnals_RS_printf("ioPro.sro[3].moni0.moniepfexp      = %x\n", (kuint)&ioPro.imgPipe[2].sro.moni0.moniepfexp );
		IntErnals_RS_printf("ioPro.sro[3].moni0.monibllminexp   = %x\n", (kuint)&ioPro.imgPipe[2].sro.moni0.monibllminexp );
		IntErnals_RS_printf("ioPro.sro[3].moni0.monibllmaxexp   = %x\n", (kuint)&ioPro.imgPipe[2].sro.moni0.monibllmaxexp );
	}
#endif	/** SRO Unit(pipe[3]) **/
#endif
}

ProTest5 *pro_test5_new(void)
{
	ProTest5* self = k_object_new_with_private(PRO_TYPE_TEST5,sizeof(ProTest5Private));

	return self;
}
