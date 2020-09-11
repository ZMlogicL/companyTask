/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :于孟孟
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年06月开始开发
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
#include "protest4.h"


K_TYPE_DEFINE_WITH_PRIVATE(ProTest4, pro_test4)
#define PRO_TEST4_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), ProTest4Private, PRO_TYPE_TEST4))


struct _ProTest4Private
{
	int a;
};


/*DECLS*/


/*MIPL*/
static void pro_test4_constructor(ProTest4 *self)
{
	ProTest4Private *priv = PRO_TEST4_GET_PRIVATE(self);
}

static void pro_test4_destructor(ProTest4 *self)
{
	ProTest4Private *priv = PRO_TEST4_GET_PRIVATE(self);
}


/*PUBLIC*/
void pro_test4(ProTest4 *self, EProBlockType type, IoPro ioPro)
{

#if 0
#ifdef D_ENABLE_IO_PRO_SRO_PIPE_2	/** SRO Unit(pipe[2]) **/

	if(type == E_PRO_BLOCK_TYPE_SRO2) {

		// SROTOP
		RS_printf("SR0[2]\n");
		RS_printf("IO_PRO.SRO[2].SROTOP.SR          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.srotop.sr);
		RS_printf("IO_PRO.SRO[2].SROTOP.CLKSTP      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.srotop.clkstp);
		RS_printf("IO_PRO.SRO[2].SROTOP.SROTOPCTL1  = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.srotop.srotopctl1);
		RS_printf("IO_PRO.SRO[2].SROTOP.SROTOPCTL2  = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.srotop.srotopctl2);
		RS_printf("IO_PRO.SRO[2].SROTOP.INTMON1     = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.srotop.intmon1);
		RS_printf("IO_PRO.SRO[2].SROTOP.INTMON2     = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.srotop.intmon2);
		RS_printf("IO_PRO.SRO[2].SROTOP.INTCTL      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.srotop.intctl);
		RS_printf("IO_PRO.SRO[2].SROTOP.VHDINTENB   = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.srotop.vhdintenb);
		RS_printf("IO_PRO.SRO[2].SROTOP.VHDINTFLG   = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.srotop.vhdintflg);
		RS_printf("IO_PRO.SRO[2].SROTOP.VHSET       = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.srotop.vhset);
		RS_printf("IO_PRO.SRO[2].SROTOP.VMIVADR     = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.srotop.vmivadr);
		RS_printf("IO_PRO.SRO[2].SROTOP.VMIHADR     = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.srotop.vmihadr);
		RS_printf("IO_PRO.SRO[2].SROTOP.HMIHADR     = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.srotop.hmihadr);

		// PG
		RS_printf("IO_PRO.SRO[2].PG.PGTRG           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pg.pgtrg);
		RS_printf("IO_PRO.SRO[2].PG.PGCTL           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pg.pgctl);
		RS_printf("IO_PRO.SRO[2].PG.PGVW            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pg.pgvw);
		RS_printf("IO_PRO.SRO[2].PG.PGHW            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pg.pghw);
		RS_printf("IO_PRO.SRO[2].PG.PGVBLNK         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pg.pgvblnk);
		RS_printf("IO_PRO.SRO[2].PG.PGHBLNK         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pg.pghblnk);
		RS_printf("IO_PRO.SRO[2].PG.PGVDHDBLNK      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pg.pgvdhdblnk);

		// FFSH-0
		RS_printf("IO_PRO.SRO[2].FFSH0.FFSHTRG      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ffsh[0].ffshtrg);
		RS_printf("IO_PRO.SRO[2].FFSH0.FFSHPAEN     = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ffsh[0].ffshpaen);
		RS_printf("IO_PRO.SRO[2].FFSH0.FFSHV        = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ffsh[0].ffshv);
		RS_printf("IO_PRO.SRO[2].FFSH0.FFSHH        = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ffsh[0].ffshh);
		RS_printf("IO_PRO.SRO[2].FFSH0.FFSHVW       = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ffsh[0].ffshvw);
		RS_printf("IO_PRO.SRO[2].FFSH0.FFSHHW       = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ffsh[0].ffshhw);
		RS_printf("IO_PRO.SRO[2].FFSH0.FFSHBC       = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ffsh[0].ffshbc);
		RS_printf("IO_PRO.SRO[2].FFSH0.FFSHSUBPR    = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ffsh[0].ffshsubpr);
		RS_printf("IO_PRO.SRO[2].FFSH0.FFSHSUBSP    = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ffsh[0].ffshsubsp);
		RS_printf("IO_PRO.SRO[2].FFSH0.FFSHSUBDR    = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ffsh[0].ffshsubdr);
		RS_printf("IO_PRO.SRO[2].FFSH0.FFSHSUBST    = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ffsh[0].ffshsubst);
		RS_printf("IO_PRO.SRO[2].FFSH0.FFSHWRIC     = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ffsh[0].ffshwric);

		// FFSH-1
		RS_printf("IO_PRO.SRO[2].FFSH1.FFSHTRG      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ffsh[1].ffshtrg);
		RS_printf("IO_PRO.SRO[2].FFSH1.FFSHPAEN     = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ffsh[1].ffshpaen);
		RS_printf("IO_PRO.SRO[2].FFSH1.FFSHV        = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ffsh[1].ffshv);
		RS_printf("IO_PRO.SRO[2].FFSH1.FFSHH        = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ffsh[1].ffshh);
		RS_printf("IO_PRO.SRO[2].FFSH1.FFSHVW       = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ffsh[1].ffshvw);
		RS_printf("IO_PRO.SRO[2].FFSH1.FFSHHW       = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ffsh[1].ffshhw);
		RS_printf("IO_PRO.SRO[2].FFSH1.FFSHBC       = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ffsh[1].ffshbc);
		RS_printf("IO_PRO.SRO[2].FFSH1.FFSHSUBPR    = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ffsh[1].ffshsubpr);
		RS_printf("IO_PRO.SRO[2].FFSH1.FFSHSUBSP    = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ffsh[1].ffshsubsp);
		RS_printf("IO_PRO.SRO[2].FFSH1.FFSHSUBDR    = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ffsh[1].ffshsubdr);
		RS_printf("IO_PRO.SRO[2].FFSH1.FFSHSUBST    = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ffsh[1].ffshsubst);
		RS_printf("IO_PRO.SRO[2].FFSH1.FFSHWRIC     = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ffsh[1].ffshwric);

		// FF-0
		RS_printf("IO_PRO.SRO[2].FF0.FFTRG          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ff[0].fftrg);
		RS_printf("IO_PRO.SRO[2].FF0.FFV            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ff[0].ffv);
		RS_printf("IO_PRO.SRO[2].FF0.FFH            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ff[0].ffh);
		RS_printf("IO_PRO.SRO[2].FF0.FFVW           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ff[0].ffvw);
		RS_printf("IO_PRO.SRO[2].FF0.FFHW           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ff[0].ffhw);
		RS_printf("IO_PRO.SRO[2].FF0.FFLPB0         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ff[0].fflpb0);
		RS_printf("IO_PRO.SRO[2].FF0.FFLPB1         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ff[0].fflpb1);
		RS_printf("IO_PRO.SRO[2].FF0.FFLPB2         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ff[0].fflpb2);
		RS_printf("IO_PRO.SRO[2].FF0.FFDEFTS        = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ff[0].ffdefts);
		RS_printf("IO_PRO.SRO[2].FF0.FFMNWGT        = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ff[0].ffmnwgt);
		RS_printf("IO_PRO.SRO[2].FF0.FFSBWGT        = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ff[0].ffsbwgt);

		// FF-1
		RS_printf("IO_PRO.SRO[2].FF1.FFTRG          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ff[1].fftrg);
		RS_printf("IO_PRO.SRO[2].FF1.FFV            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ff[1].ffv);
		RS_printf("IO_PRO.SRO[2].FF1.FFH            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ff[1].ffh);
		RS_printf("IO_PRO.SRO[2].FF1.FFVW           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ff[1].ffvw);
		RS_printf("IO_PRO.SRO[2].FF1.FFHW           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ff[1].ffhw);
		RS_printf("IO_PRO.SRO[2].FF1.FFLPB0         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ff[1].fflpb0);
		RS_printf("IO_PRO.SRO[2].FF1.FFLPB1         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ff[1].fflpb1);
		RS_printf("IO_PRO.SRO[2].FF1.FFLPB2         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ff[1].fflpb2);
		RS_printf("IO_PRO.SRO[2].FF1.FFDEFTS        = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ff[1].ffdefts);
		RS_printf("IO_PRO.SRO[2].FF1.FFMNWGT        = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ff[1].ffmnwgt);
		RS_printf("IO_PRO.SRO[2].FF1.FFSBWGT        = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ff[1].ffsbwgt);

		// PGAIN0
		RS_printf("IO_PRO.SRO[2].PGAIN0.PGAINTRG     = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pgain0.pgaintrg);
		RS_printf("IO_PRO.SRO[2].PGAIN0.PGAINR       = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pgain0.pgainr);
		RS_printf("IO_PRO.SRO[2].PGAIN0.PGAINGR      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pgain0.pgaingr);
		RS_printf("IO_PRO.SRO[2].PGAIN0.PGAINGB      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pgain0.pgaingb);
		RS_printf("IO_PRO.SRO[2].PGAIN0.PGAINB       = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pgain0.pgainb);
		RS_printf("IO_PRO.SRO[2].PGAIN0.POFSR        = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pgain0.pofsr);
		RS_printf("IO_PRO.SRO[2].PGAIN0.POFSGR       = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pgain0.pofsgr);
		RS_printf("IO_PRO.SRO[2].PGAIN0.POFSGB       = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pgain0.pofsgb);
		RS_printf("IO_PRO.SRO[2].PGAIN0.POFSB        = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pgain0.pofsb);

		// SDC-0
		RS_printf("IO_PRO.SRO[2].SDC0.SDCTRG     = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[0].sdctrg);
		RS_printf("IO_PRO.SRO[2].SDC0.SDCPAEN    = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[0].sdcpaen);
		RS_printf("IO_PRO.SRO[2].SDC0.SDCCTL     = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[0].sdcctl);
		RS_printf("IO_PRO.SRO[2].SDC0.SDCINTENB  = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[0].sdcintenb);
		RS_printf("IO_PRO.SRO[2].SDC0.SDCINTFLG  = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[0].sdcintflg);
		RS_printf("IO_PRO.SRO[2].SDC0.SDCSGD     = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[0].sdcsgd);
		RS_printf("IO_PRO.SRO[2].SDC0.SDCPH0     = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[0].sdcph0);
		RS_printf("IO_PRO.SRO[2].SDC0.SDCPH1     = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[0].sdcph1);
		RS_printf("IO_PRO.SRO[2].SDC0.SDCPHW0    = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[0].sdcphw0);
		RS_printf("IO_PRO.SRO[2].SDC0.SDCPHW1    = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[0].sdcphw1);
		RS_printf("IO_PRO.SRO[2].SDC0.SDCP1HW0   = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[0].sdcp1hw0);
		RS_printf("IO_PRO.SRO[2].SDC0.SDCP1HW1   = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[0].sdcp1hw1);
		RS_printf("IO_PRO.SRO[2].SDC0.SDCN1HW0   = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[0].sdcn1hw0);
		RS_printf("IO_PRO.SRO[2].SDC0.SDCN1HW1   = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[0].sdcn1hw1);
		RS_printf("IO_PRO.SRO[2].SDC0.SDCP2HW0   = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[0].sdcp2hw0);
		RS_printf("IO_PRO.SRO[2].SDC0.SDCP2HW1   = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[0].sdcp2hw1);
		RS_printf("IO_PRO.SRO[2].SDC0.SDCN2HW0   = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[0].sdcn2hw0);
		RS_printf("IO_PRO.SRO[2].SDC0.SDCN2HW1   = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[0].sdcn2hw1);
		RS_printf("IO_PRO.SRO[2].SDC0.SDCPC0     = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[0].sdcpc0);
		RS_printf("IO_PRO.SRO[2].SDC0.SDCPC1     = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[0].sdcpc1);
		RS_printf("IO_PRO.SRO[2].SDC0.SDCPCW0    = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[0].sdcpcw0);
		RS_printf("IO_PRO.SRO[2].SDC0.SDCPCW1    = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[0].sdcpcw1);
		RS_printf("IO_PRO.SRO[2].SDC0.SDCP1CW0   = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[0].sdcp1cw0);
		RS_printf("IO_PRO.SRO[2].SDC0.SDCP1CW1   = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[0].sdcp1cw1);
		RS_printf("IO_PRO.SRO[2].SDC0.SDCN1CW0   = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[0].sdcn1cw0);
		RS_printf("IO_PRO.SRO[2].SDC0.SDCN1CW1   = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[0].sdcn1cw1);
		RS_printf("IO_PRO.SRO[2].SDC0.SDCP2CW0   = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[0].sdcp2cw0);
		RS_printf("IO_PRO.SRO[2].SDC0.SDCP2CW1   = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[0].sdcp2cw1);
		RS_printf("IO_PRO.SRO[2].SDC0.SDCN2CW0   = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[0].sdcn2cw0);
		RS_printf("IO_PRO.SRO[2].SDC0.SDCN2CW1   = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[0].sdcn2cw1);
		RS_printf("IO_PRO.SRO[2].SDC0.SDCGMAXMIN = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[0].sdcgmaxmin);
		RS_printf("IO_PRO.SRO[2].SDC0.SDCNMAX    = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[0].sdcnmax);

		// SDC-1
		RS_printf("IO_PRO.SRO[2].SDC1.SDCTRG     = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[1].sdctrg);
		RS_printf("IO_PRO.SRO[2].SDC1.SDCPAEN    = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[1].sdcpaen);
		RS_printf("IO_PRO.SRO[2].SDC1.SDCCTL     = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[1].sdcctl);
		RS_printf("IO_PRO.SRO[2].SDC1.SDCINTENB  = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[1].sdcintenb);
		RS_printf("IO_PRO.SRO[2].SDC1.SDCINTFLG  = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[1].sdcintflg);
		RS_printf("IO_PRO.SRO[2].SDC1.SDCSGD     = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[1].sdcsgd);
		RS_printf("IO_PRO.SRO[2].SDC1.SDCPH0     = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[1].sdcph0);
		RS_printf("IO_PRO.SRO[2].SDC1.SDCPH1     = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[1].sdcph1);
		RS_printf("IO_PRO.SRO[2].SDC1.SDCPHW0    = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[1].sdcphw0);
		RS_printf("IO_PRO.SRO[2].SDC1.SDCPHW1    = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[1].sdcphw1);
		RS_printf("IO_PRO.SRO[2].SDC1.SDCP1HW0   = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[1].sdcp1hw0);
		RS_printf("IO_PRO.SRO[2].SDC1.SDCP1HW1   = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[1].sdcp1hw1);
		RS_printf("IO_PRO.SRO[2].SDC1.SDCN1HW0   = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[1].sdcn1hw0);
		RS_printf("IO_PRO.SRO[2].SDC1.SDCN1HW1   = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[1].sdcn1hw1);
		RS_printf("IO_PRO.SRO[2].SDC1.SDCP2HW0   = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[1].sdcp2hw0);
		RS_printf("IO_PRO.SRO[2].SDC1.SDCP2HW1   = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[1].sdcp2hw1);
		RS_printf("IO_PRO.SRO[2].SDC1.SDCN2HW0   = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[1].sdcn2hw0);
		RS_printf("IO_PRO.SRO[2].SDC1.SDCN2HW1   = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[1].sdcn2hw1);
		RS_printf("IO_PRO.SRO[2].SDC1.SDCPC0     = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[1].sdcpc0);
		RS_printf("IO_PRO.SRO[2].SDC1.SDCPC1     = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[1].sdcpc1);
		RS_printf("IO_PRO.SRO[2].SDC1.SDCPCW0    = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[1].sdcpcw0);
		RS_printf("IO_PRO.SRO[2].SDC1.SDCPCW1    = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[1].sdcpcw1);
		RS_printf("IO_PRO.SRO[2].SDC1.SDCP1CW0   = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[1].sdcp1cw0);
		RS_printf("IO_PRO.SRO[2].SDC1.SDCP1CW1   = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[1].sdcp1cw1);
		RS_printf("IO_PRO.SRO[2].SDC1.SDCN1CW0   = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[1].sdcn1cw0);
		RS_printf("IO_PRO.SRO[2].SDC1.SDCN1CW1   = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[1].sdcn1cw1);
		RS_printf("IO_PRO.SRO[2].SDC1.SDCP2CW0   = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[1].sdcp2cw0);
		RS_printf("IO_PRO.SRO[2].SDC1.SDCP2CW1   = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[1].sdcp2cw1);
		RS_printf("IO_PRO.SRO[2].SDC1.SDCN2CW0   = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[1].sdcn2cw0);
		RS_printf("IO_PRO.SRO[2].SDC1.SDCN2CW1   = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[1].sdcn2cw1);
		RS_printf("IO_PRO.SRO[2].SDC1.SDCGMAXMIN = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[1].sdcgmaxmin);
		RS_printf("IO_PRO.SRO[2].SDC1.SDCNMAX    = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.sdc[1].sdcnmax);

		// PZSFTB1
		RS_printf("IO_PRO.SRO[2].PZSFTB1.PZSFTTRG      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pzsftb1.pzsfttrg);
		RS_printf("IO_PRO.SRO[2].PZSFTB1.PZOFST        = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pzsftb1.pzofst);

		// DPC
		RS_printf("IO_PRO.SRO[2].DPC.DPCTRG            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.dpc.dpctrg);
		RS_printf("IO_PRO.SRO[2].DPC.DPCPAEN           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.dpc.dpcpaen);
		RS_printf("IO_PRO.SRO[2].DPC.DPCGWP            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.dpc.dpcgwp);
		RS_printf("IO_PRO.SRO[2].DPC.DPCGWS            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.dpc.dpcgws);
		RS_printf("IO_PRO.SRO[2].DPC.DPCWP             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.dpc.dpcwp);
		RS_printf("IO_PRO.SRO[2].DPC.DPCWS             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.dpc.dpcws);
		RS_printf("IO_PRO.SRO[2].DPC.DPCMD             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.dpc.dpcmd);
		RS_printf("IO_PRO.SRO[2].DPC.DPCBLP            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.dpc.dpcblp);
		RS_printf("IO_PRO.SRO[2].DPC.DPCBLM            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.dpc.dpcblm);
		RS_printf("IO_PRO.SRO[2].DPC.DFCTL             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.dpc.dfctl);
		RS_printf("IO_PRO.SRO[2].DPC.DFS               = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.dpc.dfs);
		RS_printf("IO_PRO.SRO[2].DPC.DFO               = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.dpc.dfo);
		RS_printf("IO_PRO.SRO[2].DPC.DFK               = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.dpc.dfk);
		RS_printf("IO_PRO.SRO[2].DPC.DFH               = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.dpc.dfh);
		RS_printf("IO_PRO.SRO[2].DPC.DFCSR             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.dpc.dfcsr);
		RS_printf("IO_PRO.SRO[2].DPC.DFLSTH            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.dpc.dflsth);
		RS_printf("IO_PRO.SRO[2].DPC.DFAGEF            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.dpc.dfagef);
		RS_printf("IO_PRO.SRO[2].DPC.DFAGEF2           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.dpc.dfagef2);
		RS_printf("IO_PRO.SRO[2].DPC.DFAGTH            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.dpc.dfagth);
		RS_printf("IO_PRO.SRO[2].DPC.DFAGTHK           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.dpc.dfagthk);
		RS_printf("IO_PRO.SRO[2].DPC.DMCTL             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.dpc.dmctl);
		RS_printf("IO_PRO.SRO[2].DPC.DMWKS             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.dpc.dmwks);
		RS_printf("IO_PRO.SRO[2].DPC.DMWKD             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.dpc.dmwkd);
		RS_printf("IO_PRO.SRO[2].DPC.DMAGK             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.dpc.dmagk);
		RS_printf("IO_PRO.SRO[2].DPC.DECTL             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.dpc.dectl);
		RS_printf("IO_PRO.SRO[2].DPC.DENSS             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.dpc.denss);
		RS_printf("IO_PRO.SRO[2].DPC.DENSO             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.dpc.denso);
		RS_printf("IO_PRO.SRO[2].DPC.DENSK             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.dpc.densk);
		RS_printf("IO_PRO.SRO[2].DPC.DENSH             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.dpc.densh);
		RS_printf("IO_PRO.SRO[2].DPC.DENSMGN           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.dpc.densmgn);
		RS_printf("IO_PRO.SRO[2].DPC.DENDCTH           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.dpc.dendcth);
		RS_printf("IO_PRO.SRO[2].DPC.DEAGK             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.dpc.deagk);
		RS_printf("IO_PRO.SRO[2].DPC.DCAGEF            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.dpc.dcagef);
		RS_printf("IO_PRO.SRO[2].DPC.DCAGTH            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.dpc.dcagth);

		// PZSFTB2
		RS_printf("IO_PRO.SRO[2].PZSFTB2.PZSFTTRG      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pzsftb2.pzsfttrg);
		RS_printf("IO_PRO.SRO[2].PZSFTB2.PZOFST        = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pzsftb2.pzofst);

		// FSHDL0
		RS_printf("IO_PRO.SRO[2].FSHDL0.FFSHTRG        = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.fshdl0.ffshtrg);
		RS_printf("IO_PRO.SRO[2].FSHDL0.FFSHPAEN       = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.fshdl0.ffshpaen);
		RS_printf("IO_PRO.SRO[2].FSHDL0.FFSHV          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.fshdl0.ffshv);
		RS_printf("IO_PRO.SRO[2].FSHDL0.FFSHH          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.fshdl0.ffshh);
		RS_printf("IO_PRO.SRO[2].FSHDL0.FFSHVW         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.fshdl0.ffshvw);
		RS_printf("IO_PRO.SRO[2].FSHDL0.FFSHHW         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.fshdl0.ffshhw);
		RS_printf("IO_PRO.SRO[2].FSHDL0.FFSHBC         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.fshdl0.ffshbc);
		RS_printf("IO_PRO.SRO[2].FSHDL0.FFSHUL1        = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.fshdl0.ffshul1);
		RS_printf("IO_PRO.SRO[2].FSHDL0.FFSHUL2        = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.fshdl0.ffshul2);
		RS_printf("IO_PRO.SRO[2].FSHDL0.FFSHGFMT       = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.fshdl0.ffshgfmt);
		RS_printf("IO_PRO.SRO[2].FSHDL0.FFSHSUBPR      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.fshdl0.ffshsubpr);
		RS_printf("IO_PRO.SRO[2].FSHDL0.FFSHSUBSP      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.fshdl0.ffshsubsp);
		RS_printf("IO_PRO.SRO[2].FSHDL0.FFSHSUBDR      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.fshdl0.ffshsubdr);
		RS_printf("IO_PRO.SRO[2].FSHDL0.FFSHSUBST      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.fshdl0.ffshsubst);
		RS_printf("IO_PRO.SRO[2].FSHDL0.FFSHCTL        = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.fshdl0.ffshctl);
		RS_printf("IO_PRO.SRO[2].FSHDL0.FFSHHWPH       = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.fshdl0.ffshhwph);
		RS_printf("IO_PRO.SRO[2].FSHDL0.FFSHWRIC       = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.fshdl0.ffshwric);

		// AFPBA
		RS_printf("IO_PRO.SRO[2].AFPBA.AFPBTRG         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.afpb[0].afpbtrg);
		RS_printf("IO_PRO.SRO[2].AFPBA.AFPBV           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.afpb[0].afpbv);
		RS_printf("IO_PRO.SRO[2].AFPBA.AFPBH           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.afpb[0].afpbh);
		RS_printf("IO_PRO.SRO[2].AFPBA.AFPBVW          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.afpb[0].afpbvw);
		RS_printf("IO_PRO.SRO[2].AFPBA.AFPBHW          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.afpb[0].afpbhw);

		// AFPBB
		RS_printf("IO_PRO.SRO[2].AFPBG.AFPBTRG         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.afpb[1].afpbtrg);
		RS_printf("IO_PRO.SRO[2].AFPBG.AFPBV           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.afpb[1].afpbv);
		RS_printf("IO_PRO.SRO[2].AFPBG.AFPBH           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.afpb[1].afpbh);
		RS_printf("IO_PRO.SRO[2].AFPBG.AFPBVW          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.afpb[1].afpbvw);
		RS_printf("IO_PRO.SRO[2].AFPBG.AFPBHW          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.afpb[1].afpbhw);

		// PZSFTC1
		RS_printf("IO_PRO.SRO[2].PZSFTC1.PZSFTTRG      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pzsftc1.pzsfttrg);
		RS_printf("IO_PRO.SRO[2].PZSFTC1.PZOFST        = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pzsftc1.pzofst);

		// FFC
		RS_printf("IO_PRO.SRO[2].FFC.FCTRG             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ffc.fctrg);
		RS_printf("IO_PRO.SRO[2].FFC.FCPAEN            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ffc.fcpaen);
		RS_printf("IO_PRO.SRO[2].FFC.FCV               = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ffc.fcv);
		RS_printf("IO_PRO.SRO[2].FFC.FCH               = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ffc.fch);
		RS_printf("IO_PRO.SRO[2].FFC.FCVW              = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ffc.fcvw);
		RS_printf("IO_PRO.SRO[2].FFC.FCHW              = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ffc.fchw);
		RS_printf("IO_PRO.SRO[2].FFC.FCBC              = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ffc.fcbc);
		RS_printf("IO_PRO.SRO[2].FFC.FCSUBPR           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ffc.fcsubpr);
		RS_printf("IO_PRO.SRO[2].FFC.FCSUBSP           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ffc.fcsubsp);
		RS_printf("IO_PRO.SRO[2].FFC.FCSUBDR           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ffc.fcsubdr);
		RS_printf("IO_PRO.SRO[2].FFC.FCSUBST           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ffc.fcsubst);
		RS_printf("IO_PRO.SRO[2].FFC.FCWRIC            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.ffc.fcwric);

		// CAG
		RS_printf("IO_PRO.SRO[2].CAG.CAGTRG            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.cagtrg);
		RS_printf("IO_PRO.SRO[2].CAG.CAGPAEN           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.cagpaen);
		RS_printf("IO_PRO.SRO[2].CAG.CAGGWP            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.caggwp);
		RS_printf("IO_PRO.SRO[2].CAG.CAGGWS            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.caggws);
		RS_printf("IO_PRO.SRO[2].CAG.CAGWP             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.cagwp);
		RS_printf("IO_PRO.SRO[2].CAG.CAGWS             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.cagws);
		RS_printf("IO_PRO.SRO[2].CAG.CAGMD             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.cagmd);
		RS_printf("IO_PRO.SRO[2].CAG.RBR               = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.rbr);
		RS_printf("IO_PRO.SRO[2].CAG.ABOARV            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.aboarv);
		RS_printf("IO_PRO.SRO[2].CAG.ABOARH            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.aboarh);
		RS_printf("IO_PRO.SRO[2].CAG.ABOAGV            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.aboagv);
		RS_printf("IO_PRO.SRO[2].CAG.ABOAGH            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.aboagh);
		RS_printf("IO_PRO.SRO[2].CAG.ABOABV            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.aboabv);
		RS_printf("IO_PRO.SRO[2].CAG.ABOABH            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.aboabh);
		RS_printf("IO_PRO.SRO[2].CAG.ABGAR             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.abgar);
		RS_printf("IO_PRO.SRO[2].CAG.ABGAG             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.abgag);
		RS_printf("IO_PRO.SRO[2].CAG.ABGAB             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.abgab);
		RS_printf("IO_PRO.SRO[2].CAG.ABLRV             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.ablrv);
		RS_printf("IO_PRO.SRO[2].CAG.ABLRH             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.ablrh);
		RS_printf("IO_PRO.SRO[2].CAG.ABLGV             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.ablgv);
		RS_printf("IO_PRO.SRO[2].CAG.ABLGH             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.ablgh);
		RS_printf("IO_PRO.SRO[2].CAG.ABLBV             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.ablbv);
		RS_printf("IO_PRO.SRO[2].CAG.ABLBH             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.ablbh);
		RS_printf("IO_PRO.SRO[2].CAG.ABOFSRV           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.abofsrv);
		RS_printf("IO_PRO.SRO[2].CAG.ABOFSRH           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.abofsrh);
		RS_printf("IO_PRO.SRO[2].CAG.ABOFSGV           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.abofsgv);
		RS_printf("IO_PRO.SRO[2].CAG.ABOFSGH           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.abofsgh);
		RS_printf("IO_PRO.SRO[2].CAG.ABOFSBV           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.abofsbv);
		RS_printf("IO_PRO.SRO[2].CAG.ABOFSBH           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.abofsbh);
		RS_printf("IO_PRO.SRO[2].CAG.ABNLTHR1          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.abnlthr1);
		RS_printf("IO_PRO.SRO[2].CAG.ABNLTHG1          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.abnlthg1);
		RS_printf("IO_PRO.SRO[2].CAG.ABNLTHB1          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.abnlthb1);
		RS_printf("IO_PRO.SRO[2].CAG.ABNLGAR1          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.abnlgar1);
		RS_printf("IO_PRO.SRO[2].CAG.ABNLGAG1          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.abnlgag1);
		RS_printf("IO_PRO.SRO[2].CAG.ABNLGAB1          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.abnlgab1);
		RS_printf("IO_PRO.SRO[2].CAG.ABNLTHR2          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.abnlthr2);
		RS_printf("IO_PRO.SRO[2].CAG.ABNLTHG2          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.abnlthg2);
		RS_printf("IO_PRO.SRO[2].CAG.ABNLTHB2          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.abnlthb2);
		RS_printf("IO_PRO.SRO[2].CAG.ABNLGAR2          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.abnlgar2);
		RS_printf("IO_PRO.SRO[2].CAG.ABNLGAG2          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.abnlgag2);
		RS_printf("IO_PRO.SRO[2].CAG.ABNLGAB2          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.abnlgab2);
		RS_printf("IO_PRO.SRO[2].CAG.ABNLTHR3          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.abnlthr3);
		RS_printf("IO_PRO.SRO[2].CAG.ABNLTHG3          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.abnlthg3);
		RS_printf("IO_PRO.SRO[2].CAG.ABNLTHB3          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.abnlthb3);
		RS_printf("IO_PRO.SRO[2].CAG.ABNLGAR3          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.abnlgar3);
		RS_printf("IO_PRO.SRO[2].CAG.ABNLGAG3          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.abnlgag3);
		RS_printf("IO_PRO.SRO[2].CAG.ABNLGAB3          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.abnlgab3);
		RS_printf("IO_PRO.SRO[2].CAG.ABNLTHR4          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.abnlthr4);
		RS_printf("IO_PRO.SRO[2].CAG.ABNLTHG4          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.abnlthg4);
		RS_printf("IO_PRO.SRO[2].CAG.ABNLTHB4          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.abnlthb4);
		RS_printf("IO_PRO.SRO[2].CAG.ABNLGAR4          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.abnlgar4);
		RS_printf("IO_PRO.SRO[2].CAG.ABNLGAG4          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.abnlgag4);
		RS_printf("IO_PRO.SRO[2].CAG.ABNLGAB4          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.abnlgab4);
		RS_printf("IO_PRO.SRO[2].CAG.BFGLMT            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.bfglmt);
		RS_printf("IO_PRO.SRO[2].CAG.BFGTH             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.cag.bfgth);

		// PZSFTC2
		RS_printf("IO_PRO.SRO[2].PZSFTC2.PZSFTTRG      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pzsftc2.pzsfttrg);
		RS_printf("IO_PRO.SRO[2].PZSFTC2.PZOFST        = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pzsftc2.pzofst);

		// FSHDL1
		RS_printf("IO_PRO.SRO[2].FSHDL1.FFSHTRG        = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.fshdl1.ffshtrg);
		RS_printf("IO_PRO.SRO[2].FSHDL1.FFSHPAEN       = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.fshdl1.ffshpaen);
		RS_printf("IO_PRO.SRO[2].FSHDL1.FFSHV          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.fshdl1.ffshv);
		RS_printf("IO_PRO.SRO[2].FSHDL1.FFSHH          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.fshdl1.ffshh);
		RS_printf("IO_PRO.SRO[2].FSHDL1.FFSHVW         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.fshdl1.ffshvw);
		RS_printf("IO_PRO.SRO[2].FSHDL1.FFSHHW         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.fshdl1.ffshhw);
		RS_printf("IO_PRO.SRO[2].FSHDL1.FFSHBC         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.fshdl1.ffshbc);
		RS_printf("IO_PRO.SRO[2].FSHDL1.FFSHUL1        = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.fshdl1.ffshul1);
		RS_printf("IO_PRO.SRO[2].FSHDL1.FFSHUL2        = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.fshdl1.ffshul2);
		RS_printf("IO_PRO.SRO[2].FSHDL1.FFSHGFMT       = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.fshdl1.ffshgfmt);
		RS_printf("IO_PRO.SRO[2].FSHDL1.FFSHSUBPR      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.fshdl1.ffshsubpr);
		RS_printf("IO_PRO.SRO[2].FSHDL1.FFSHSUBSP      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.fshdl1.ffshsubsp);
		RS_printf("IO_PRO.SRO[2].FSHDL1.FFSHSUBDR      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.fshdl1.ffshsubdr);
		RS_printf("IO_PRO.SRO[2].FSHDL1.FFSHSUBST      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.fshdl1.ffshsubst);
		RS_printf("IO_PRO.SRO[2].FSHDL1.FFSHCTL        = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.fshdl1.ffshctl);
		RS_printf("IO_PRO.SRO[2].FSHDL1.FFSHHWPH       = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.fshdl1.ffshhwph);
		RS_printf("IO_PRO.SRO[2].FSHDL1.FFSHWRIC       = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.fshdl1.ffshwric);

		// VRB
		RS_printf("IO_PRO.SRO[2].VRB.VRBTRG            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.vrb.vrbtrg);
		RS_printf("IO_PRO.SRO[2].VRB.VRBV              = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.vrb.vrbv);
		RS_printf("IO_PRO.SRO[2].VRB.VRBH              = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.vrb.vrbh);
		RS_printf("IO_PRO.SRO[2].VRB.VRBVW             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.vrb.vrbvw);
		RS_printf("IO_PRO.SRO[2].VRB.VRBHW             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.vrb.vrbhw);
		RS_printf("IO_PRO.SRO[2].VRB.VRBSCYC           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.vrb.vrbscyc);
		RS_printf("IO_PRO.SRO[2].VRB.VRBPAEN           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.vrb.vrbpaen);
		RS_printf("IO_PRO.SRO[2].VRB.VRB0K             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.vrb.vrb0k);
		RS_printf("IO_PRO.SRO[2].VRB.VRB1K             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.vrb.vrb1k);

		// HRB
		RS_printf("IO_PRO.SRO[2].HRB.HRBTRG            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.hrb.hrbtrg);
		RS_printf("IO_PRO.SRO[2].HRB.HRBV              = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.hrb.hrbv);
		RS_printf("IO_PRO.SRO[2].HRB.HRBH              = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.hrb.hrbh);
		RS_printf("IO_PRO.SRO[2].HRB.HRBVW             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.hrb.hrbvw);
		RS_printf("IO_PRO.SRO[2].HRB.HRBHW             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.hrb.hrbhw);
		RS_printf("IO_PRO.SRO[2].HRB.HRBOHW            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.hrb.hrbohw);
		RS_printf("IO_PRO.SRO[2].HRB.HRBSCYC           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.hrb.hrbscyc);
		RS_printf("IO_PRO.SRO[2].HRB.HRBOSM            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.hrb.hrbosm);
		RS_printf("IO_PRO.SRO[2].HRB.HRBPAEN           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.hrb.hrbpaen);
		RS_printf("IO_PRO.SRO[2].HRB.HRBK              = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.hrb.hrbk);

		// P2M-0
		RS_printf("IO_PRO.SRO[2].P2M0.P2MTRG           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[0].p2mtrg);
		RS_printf("IO_PRO.SRO[2].P2M0.P2MPAEN          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[0].p2mpaen);
		RS_printf("IO_PRO.SRO[2].P2M0.P2MCTL           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[0].p2mctl);
		RS_printf("IO_PRO.SRO[2].P2M0.P2MOFS           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[0].p2mofs);
		RS_printf("IO_PRO.SRO[2].P2M0.PBSFT            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[0].pbsft);
		RS_printf("IO_PRO.SRO[2].P2M0.PCLPH            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[0].pclph);
		RS_printf("IO_PRO.SRO[2].P2M0.PTRMV            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[0].ptrmv);
		RS_printf("IO_PRO.SRO[2].P2M0.PTRMH            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[0].ptrmh);
		RS_printf("IO_PRO.SRO[2].P2M0.PTRMVW           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[0].ptrmvw);
		RS_printf("IO_PRO.SRO[2].P2M0.PTRMHW           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[0].ptrmhw);
		RS_printf("IO_PRO.SRO[2].P2M0.PTRMXVCYC        = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[0].ptrmxvcyc);
		RS_printf("IO_PRO.SRO[2].P2M0.PTRMXHCYC        = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[0].ptrmxhcyc);
		RS_printf("IO_PRO.SRO[2].P2M0.PTRMXVEN         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[0].ptrmxven);
		RS_printf("IO_PRO.SRO[2].P2M0.PTRMXHEN         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[0].ptrmxhen);
		RS_printf("IO_PRO.SRO[2].P2M0.P2MMIR           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[0].p2mmir);

		// P2M-1
		RS_printf("IO_PRO.SRO[2].P2M1.P2MTRG           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[1].p2mtrg);
		RS_printf("IO_PRO.SRO[2].P2M1.P2MPAEN          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[1].p2mpaen);
		RS_printf("IO_PRO.SRO[2].P2M1.P2MCTL           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[1].p2mctl);
		RS_printf("IO_PRO.SRO[2].P2M1.P2MOFS           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[1].p2mofs);
		RS_printf("IO_PRO.SRO[2].P2M1.PBSFT            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[1].pbsft);
		RS_printf("IO_PRO.SRO[2].P2M1.PCLPH            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[1].pclph);
		RS_printf("IO_PRO.SRO[2].P2M1.PTRMV            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[1].ptrmv);
		RS_printf("IO_PRO.SRO[2].P2M1.PTRMH            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[1].ptrmh);
		RS_printf("IO_PRO.SRO[2].P2M1.PTRMVW           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[1].ptrmvw);
		RS_printf("IO_PRO.SRO[2].P2M1.PTRMHW           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[1].ptrmhw);
		RS_printf("IO_PRO.SRO[2].P2M1.PTRMXVCYC        = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[1].ptrmxvcyc);
		RS_printf("IO_PRO.SRO[2].P2M1.PTRMXHCYC        = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[1].ptrmxhcyc);
		RS_printf("IO_PRO.SRO[2].P2M1.PTRMXVEN         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[1].ptrmxven);
		RS_printf("IO_PRO.SRO[2].P2M1.PTRMXHEN         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[1].ptrmxhen);
		RS_printf("IO_PRO.SRO[2].P2M1.P2MMIR           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[1].p2mmir);

		// P2M-2
		RS_printf("IO_PRO.SRO[2].P2M2.P2MTRG           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[2].p2mtrg);
		RS_printf("IO_PRO.SRO[2].P2M2.P2MPAEN          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[2].p2mpaen);
		RS_printf("IO_PRO.SRO[2].P2M2.P2MCTL           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[2].p2mctl);
		RS_printf("IO_PRO.SRO[2].P2M2.P2MOFS           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[2].p2mofs);
		RS_printf("IO_PRO.SRO[2].P2M2.PBSFT            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[2].pbsft);
		RS_printf("IO_PRO.SRO[2].P2M2.PCLPH            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[2].pclph);
		RS_printf("IO_PRO.SRO[2].P2M2.PTRMV            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[2].ptrmv);
		RS_printf("IO_PRO.SRO[2].P2M2.PTRMH            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[2].ptrmh);
		RS_printf("IO_PRO.SRO[2].P2M2.PTRMVW           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[2].ptrmvw);
		RS_printf("IO_PRO.SRO[2].P2M2.PTRMHW           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[2].ptrmhw);
		RS_printf("IO_PRO.SRO[2].P2M2.PTRMXVCYC        = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[2].ptrmxvcyc);
		RS_printf("IO_PRO.SRO[2].P2M2.PTRMXHCYC        = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[2].ptrmxhcyc);
		RS_printf("IO_PRO.SRO[2].P2M2.PTRMXVEN         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[2].ptrmxven);
		RS_printf("IO_PRO.SRO[2].P2M2.PTRMXHEN         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[2].ptrmxhen);
		RS_printf("IO_PRO.SRO[2].P2M2.P2MMIR           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[2].p2mmir);

		// P2M-3
		RS_printf("IO_PRO.SRO[2].P2M3.P2MTRG           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[3].p2mtrg);
		RS_printf("IO_PRO.SRO[2].P2M3.P2MPAEN          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[3].p2mpaen);
		RS_printf("IO_PRO.SRO[2].P2M3.P2MCTL           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[3].p2mctl);
		RS_printf("IO_PRO.SRO[2].P2M3.P2MOFS           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[3].p2mofs);
		RS_printf("IO_PRO.SRO[2].P2M3.PBSFT            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[3].pbsft);
		RS_printf("IO_PRO.SRO[2].P2M3.PCLPH            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[3].pclph);
		RS_printf("IO_PRO.SRO[2].P2M3.PTRMV            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[3].ptrmv);
		RS_printf("IO_PRO.SRO[2].P2M3.PTRMH            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[3].ptrmh);
		RS_printf("IO_PRO.SRO[2].P2M3.PTRMVW           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[3].ptrmvw);
		RS_printf("IO_PRO.SRO[2].P2M3.PTRMHW           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[3].ptrmhw);
		RS_printf("IO_PRO.SRO[2].P2M3.PTRMXVCYC        = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[3].ptrmxvcyc);
		RS_printf("IO_PRO.SRO[2].P2M3.PTRMXHCYC        = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[3].ptrmxhcyc);
		RS_printf("IO_PRO.SRO[2].P2M3.PTRMXVEN         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[3].ptrmxven);
		RS_printf("IO_PRO.SRO[2].P2M3.PTRMXHEN         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[3].ptrmxhen);
		RS_printf("IO_PRO.SRO[2].P2M3.P2MMIR           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[3].p2mmir);

		// P2M-4
		RS_printf("IO_PRO.SRO[2].P2M4.P2MTRG           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[4].p2mtrg);
		RS_printf("IO_PRO.SRO[2].P2M4.P2MPAEN          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[4].p2mpaen);
		RS_printf("IO_PRO.SRO[2].P2M4.P2MCTL           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[4].p2mctl);
		RS_printf("IO_PRO.SRO[2].P2M4.P2MOFS           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[4].p2mofs);
		RS_printf("IO_PRO.SRO[2].P2M4.PBSFT            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[4].pbsft);
		RS_printf("IO_PRO.SRO[2].P2M4.PCLPH            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[4].pclph);
		RS_printf("IO_PRO.SRO[2].P2M4.PTRMV            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[4].ptrmv);
		RS_printf("IO_PRO.SRO[2].P2M4.PTRMH            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[4].ptrmh);
		RS_printf("IO_PRO.SRO[2].P2M4.PTRMVW           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[4].ptrmvw);
		RS_printf("IO_PRO.SRO[2].P2M4.PTRMHW           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[4].ptrmhw);
		RS_printf("IO_PRO.SRO[2].P2M4.PTRMXVCYC        = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[4].ptrmxvcyc);
		RS_printf("IO_PRO.SRO[2].P2M4.PTRMXHCYC        = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[4].ptrmxhcyc);
		RS_printf("IO_PRO.SRO[2].P2M4.PTRMXVEN         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[4].ptrmxven);
		RS_printf("IO_PRO.SRO[2].P2M4.PTRMXHEN         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[4].ptrmxhen);
		RS_printf("IO_PRO.SRO[2].P2M4.P2MMIR           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[4].p2mmir);

		// P2M-5
		RS_printf("IO_PRO.SRO[2].P2M5.P2MTRG           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[5].p2mtrg);
		RS_printf("IO_PRO.SRO[2].P2M5.P2MPAEN          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[5].p2mpaen);
		RS_printf("IO_PRO.SRO[2].P2M5.P2MCTL           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[5].p2mctl);
		RS_printf("IO_PRO.SRO[2].P2M5.P2MOFS           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[5].p2mofs);
		RS_printf("IO_PRO.SRO[2].P2M5.PBSFT            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[5].pbsft);
		RS_printf("IO_PRO.SRO[2].P2M5.PCLPH            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[5].pclph);
		RS_printf("IO_PRO.SRO[2].P2M5.PTRMV            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[5].ptrmv);
		RS_printf("IO_PRO.SRO[2].P2M5.PTRMH            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[5].ptrmh);
		RS_printf("IO_PRO.SRO[2].P2M5.PTRMVW           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[5].ptrmvw);
		RS_printf("IO_PRO.SRO[2].P2M5.PTRMHW           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[5].ptrmhw);
		RS_printf("IO_PRO.SRO[2].P2M5.PTRMXVCYC        = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[5].ptrmxvcyc);
		RS_printf("IO_PRO.SRO[2].P2M5.PTRMXHCYC        = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[5].ptrmxhcyc);
		RS_printf("IO_PRO.SRO[2].P2M5.PTRMXVEN         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[5].ptrmxven);
		RS_printf("IO_PRO.SRO[2].P2M5.PTRMXHEN         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[5].ptrmxhen);
		RS_printf("IO_PRO.SRO[2].P2M5.P2MMIR           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.p2m[5].p2mmir);

		// PWCH-0
		RS_printf("IO_PRO.SRO[2].PWCH0.PWCHTRG         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[0].pwchtrg);
		RS_printf("IO_PRO.SRO[2].PWCH0.PWS             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[0].pws);
		RS_printf("IO_PRO.SRO[2].PWCH0.PWAXCTL         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[0].pwaxctl);
		RS_printf("IO_PRO.SRO[2].PWCH0.PWCHCTL         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[0].pwchctl);
		RS_printf("IO_PRO.SRO[2].PWCH0.PWCHINTENB      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[0].pwchintenb);
		RS_printf("IO_PRO.SRO[2].PWCH0.PWCHINTFLG      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[0].pwchintflg);
		RS_printf("IO_PRO.SRO[2].PWCH0.PWCHBRESP       = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[0].pwchbresp);
		RS_printf("IO_PRO.SRO[2].PWCH0.PWSA            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[0].pwsa);
		RS_printf("IO_PRO.SRO[2].PWCH0.PWLSIZE         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[0].pwlsize);

		// PWCH-1
		RS_printf("IO_PRO.SRO[2].PWCH1.PWCHTRG         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[1].pwchtrg);
		RS_printf("IO_PRO.SRO[2].PWCH1.PWS             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[1].pws);
		RS_printf("IO_PRO.SRO[2].PWCH1.PWAXCTL         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[1].pwaxctl);
		RS_printf("IO_PRO.SRO[2].PWCH1.PWCHCTL         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[1].pwchctl);
		RS_printf("IO_PRO.SRO[2].PWCH1.PWCHINTENB      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[1].pwchintenb);
		RS_printf("IO_PRO.SRO[2].PWCH1.PWCHINTFLG      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[1].pwchintflg);
		RS_printf("IO_PRO.SRO[2].PWCH1.PWCHBRESP       = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[1].pwchbresp);
		RS_printf("IO_PRO.SRO[2].PWCH1.PWSA            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[1].pwsa);
		RS_printf("IO_PRO.SRO[2].PWCH1.PWLSIZE         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[1].pwlsize);

		// PWCH-2
		RS_printf("IO_PRO.SRO[2].PWCH2.PWCHTRG         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[2].pwchtrg);
		RS_printf("IO_PRO.SRO[2].PWCH2.PWS             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[2].pws);
		RS_printf("IO_PRO.SRO[2].PWCH2.PWAXCTL         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[2].pwaxctl);
		RS_printf("IO_PRO.SRO[2].PWCH2.PWCHCTL         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[2].pwchctl);
		RS_printf("IO_PRO.SRO[2].PWCH2.PWCHINTENB      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[2].pwchintenb);
		RS_printf("IO_PRO.SRO[2].PWCH2.PWCHINTFLG      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[2].pwchintflg);
		RS_printf("IO_PRO.SRO[2].PWCH2.PWCHBRESP       = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[2].pwchbresp);
		RS_printf("IO_PRO.SRO[2].PWCH2.PWSA            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[2].pwsa);
		RS_printf("IO_PRO.SRO[2].PWCH2.PWLSIZE         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[2].pwlsize);

		// PWCH-3
		RS_printf("IO_PRO.SRO[2].PWCH3.PWCHTRG         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[3].pwchtrg);
		RS_printf("IO_PRO.SRO[2].PWCH3.PWS             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[3].pws);
		RS_printf("IO_PRO.SRO[2].PWCH3.PWAXCTL         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[3].pwaxctl);
		RS_printf("IO_PRO.SRO[2].PWCH3.PWCHCTL         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[3].pwchctl);
		RS_printf("IO_PRO.SRO[2].PWCH3.PWCHINTENB      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[3].pwchintenb);
		RS_printf("IO_PRO.SRO[2].PWCH3.PWCHINTFLG      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[3].pwchintflg);
		RS_printf("IO_PRO.SRO[2].PWCH3.PWCHBRESP       = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[3].pwchbresp);
		RS_printf("IO_PRO.SRO[2].PWCH3.PWSA            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[3].pwsa);
		RS_printf("IO_PRO.SRO[2].PWCH3.PWLSIZE         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[3].pwlsize);

		// PWCH-4
		RS_printf("IO_PRO.SRO[2].PWCH4.PWCHTRG         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[4].pwchtrg);
		RS_printf("IO_PRO.SRO[2].PWCH4.PWS             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[4].pws);
		RS_printf("IO_PRO.SRO[2].PWCH4.PWAXCTL         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[4].pwaxctl);
		RS_printf("IO_PRO.SRO[2].PWCH4.PWCHCTL         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[4].pwchctl);
		RS_printf("IO_PRO.SRO[2].PWCH4.PWCHINTENB      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[4].pwchintenb);
		RS_printf("IO_PRO.SRO[2].PWCH4.PWCHINTFLG      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[4].pwchintflg);
		RS_printf("IO_PRO.SRO[2].PWCH4.PWCHBRESP       = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[4].pwchbresp);
		RS_printf("IO_PRO.SRO[2].PWCH4.PWSA            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[4].pwsa);
		RS_printf("IO_PRO.SRO[2].PWCH4.PWLSIZE         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[4].pwlsize);

		// PWCH-5
		RS_printf("IO_PRO.SRO[2].PWCH5.PWCHTRG         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[5].pwchtrg);
		RS_printf("IO_PRO.SRO[2].PWCH5.PWS             = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[5].pws);
		RS_printf("IO_PRO.SRO[2].PWCH5.PWAXCTL         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[5].pwaxctl);
		RS_printf("IO_PRO.SRO[2].PWCH5.PWCHCTL         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[5].pwchctl);
		RS_printf("IO_PRO.SRO[2].PWCH5.PWCHINTENB      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[5].pwchintenb);
		RS_printf("IO_PRO.SRO[2].PWCH5.PWCHINTFLG      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[5].pwchintflg);
		RS_printf("IO_PRO.SRO[2].PWCH5.PWCHBRESP       = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[5].pwchbresp);
		RS_printf("IO_PRO.SRO[2].PWCH5.PWSA            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[5].pwsa);
		RS_printf("IO_PRO.SRO[2].PWCH5.PWLSIZE         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.pwch[5].pwlsize);

		// M2P-0
		RS_printf("IO_PRO.SRO[2].M2P0.M2PTRG           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[0].m2ptrg);
		RS_printf("IO_PRO.SRO[2].M2P0.M2PPAEN          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[0].m2ppaen);
		RS_printf("IO_PRO.SRO[2].M2P0.M2PCTL           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[0].m2pctl);
		RS_printf("IO_PRO.SRO[2].M2P0.M2PBSFT          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[0].m2pbsft);
		RS_printf("IO_PRO.SRO[2].M2P0.M2POFS           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[0].m2pofs);
		RS_printf("IO_PRO.SRO[2].M2P0.M2PCLIP          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[0].m2pclip);

		// M2P-1
		RS_printf("IO_PRO.SRO[2].M2P1.M2PTRG           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[1].m2ptrg);
		RS_printf("IO_PRO.SRO[2].M2P1.M2PPAEN          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[1].m2ppaen);
		RS_printf("IO_PRO.SRO[2].M2P1.M2PCTL           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[1].m2pctl);
		RS_printf("IO_PRO.SRO[2].M2P1.M2PBSFT          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[1].m2pbsft);
		RS_printf("IO_PRO.SRO[2].M2P1.M2POFS           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[1].m2pofs);
		RS_printf("IO_PRO.SRO[2].M2P1.M2PCLIP          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[1].m2pclip);

		// M2P-2
		RS_printf("IO_PRO.SRO[2].M2P2.M2PTRG           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[2].m2ptrg);
		RS_printf("IO_PRO.SRO[2].M2P2.M2PPAEN          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[2].m2ppaen);
		RS_printf("IO_PRO.SRO[2].M2P2.M2PCTL           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[2].m2pctl);
		RS_printf("IO_PRO.SRO[2].M2P2.M2PBSFT          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[2].m2pbsft);
		RS_printf("IO_PRO.SRO[2].M2P2.M2POFS           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[2].m2pofs);
		RS_printf("IO_PRO.SRO[2].M2P2.M2PCLIP          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[2].m2pclip);

		// M2P-3
		RS_printf("IO_PRO.SRO[2].M2P3.M2PTRG           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[3].m2ptrg);
		RS_printf("IO_PRO.SRO[2].M2P3.M2PPAEN          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[3].m2ppaen);
		RS_printf("IO_PRO.SRO[2].M2P3.M2PCTL           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[3].m2pctl);
		RS_printf("IO_PRO.SRO[2].M2P3.M2PBSFT          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[3].m2pbsft);
		RS_printf("IO_PRO.SRO[2].M2P3.M2POFS           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[3].m2pofs);
		RS_printf("IO_PRO.SRO[2].M2P3.M2PCLIP          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[3].m2pclip);

		// M2P-6
		RS_printf("IO_PRO.SRO[2].M2P6.M2PTRG           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[4].m2ptrg);
		RS_printf("IO_PRO.SRO[2].M2P6.M2PPAEN          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[4].m2ppaen);
		RS_printf("IO_PRO.SRO[2].M2P6.M2PCTL           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[4].m2pctl);
		RS_printf("IO_PRO.SRO[2].M2P6.M2PBSFT          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[4].m2pbsft);
		RS_printf("IO_PRO.SRO[2].M2P6.M2POFS           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[4].m2pofs);
		RS_printf("IO_PRO.SRO[2].M2P6.M2PCLIP          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[4].m2pclip);

		// M2P-7
		RS_printf("IO_PRO.SRO[2].M2P7.M2PTRG           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[5].m2ptrg);
		RS_printf("IO_PRO.SRO[2].M2P7.M2PPAEN          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[5].m2ppaen);
		RS_printf("IO_PRO.SRO[2].M2P7.M2PCTL           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[5].m2pctl);
		RS_printf("IO_PRO.SRO[2].M2P7.M2PBSFT          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[5].m2pbsft);
		RS_printf("IO_PRO.SRO[2].M2P7.M2POFS           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[5].m2pofs);
		RS_printf("IO_PRO.SRO[2].M2P7.M2PCLIP          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[5].m2pclip);

		// M2P-8
		RS_printf("IO_PRO.SRO[2].M2P8.M2PTRG           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[6].m2ptrg);
		RS_printf("IO_PRO.SRO[2].M2P8.M2PPAEN          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[6].m2ppaen);
		RS_printf("IO_PRO.SRO[2].M2P8.M2PCTL           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[6].m2pctl);
		RS_printf("IO_PRO.SRO[2].M2P8.M2PBSFT          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[6].m2pbsft);
		RS_printf("IO_PRO.SRO[2].M2P8.M2POFS           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[6].m2pofs);
		RS_printf("IO_PRO.SRO[2].M2P8.M2PCLIP          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[6].m2pclip);

		// M2P-0
		RS_printf("IO_PRO.SRO[2].M2P9.M2PTRG           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[7].m2ptrg);
		RS_printf("IO_PRO.SRO[2].M2P9.M2PPAEN          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[7].m2ppaen);
		RS_printf("IO_PRO.SRO[2].M2P9.M2PCTL           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[7].m2pctl);
		RS_printf("IO_PRO.SRO[2].M2P9.M2PBSFT          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[7].m2pbsft);
		RS_printf("IO_PRO.SRO[2].M2P9.M2POFS           = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[7].m2pofs);
		RS_printf("IO_PRO.SRO[2].M2P9.M2PCLIP          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.m2p[7].m2pclip);

		// PRCH-0
		RS_printf("IO_PRO.SRO[2].PRCH0.PRCHTRG         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[0].prchtrg);
		RS_printf("IO_PRO.SRO[2].PRCH0.PRCHCTL         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[0].prchctl);
		RS_printf("IO_PRO.SRO[2].PRCH0.PRCHRS          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[0].prchrs);
		RS_printf("IO_PRO.SRO[2].PRCH0.PRAXCTL         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[0].praxctl);
		RS_printf("IO_PRO.SRO[2].PRCH0.PRCHINTENB      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[0].prchintenb);
		RS_printf("IO_PRO.SRO[2].PRCH0.PRCHINTFLG      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[0].prchintflg);
		RS_printf("IO_PRO.SRO[2].PRCH0.PRCHBRESP       = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[0].prchbresp);
		RS_printf("IO_PRO.SRO[2].PRCH0.PRSA            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[0].prsa);
		RS_printf("IO_PRO.SRO[2].PRCH0.PRLSIZE         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[0].prlsize);
		RS_printf("IO_PRO.SRO[2].PRCH0.PRVSIZE         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[0].prvsize);
		RS_printf("IO_PRO.SRO[2].PRCH0.PRHSIZE         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[0].prhsize);

		// PRCH-1
		RS_printf("IO_PRO.SRO[2].PRCH1.PRCHTRG         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[1].prchtrg);
		RS_printf("IO_PRO.SRO[2].PRCH1.PRCHCTL         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[1].prchctl);
		RS_printf("IO_PRO.SRO[2].PRCH1.PRCHRS          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[1].prchrs);
		RS_printf("IO_PRO.SRO[2].PRCH1.PRAXCTL         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[1].praxctl);
		RS_printf("IO_PRO.SRO[2].PRCH1.PRCHINTENB      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[1].prchintenb);
		RS_printf("IO_PRO.SRO[2].PRCH1.PRCHINTFLG      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[1].prchintflg);
		RS_printf("IO_PRO.SRO[2].PRCH1.PRCHBRESP       = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[1].prchbresp);
		RS_printf("IO_PRO.SRO[2].PRCH1.PRSA            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[1].prsa);
		RS_printf("IO_PRO.SRO[2].PRCH1.PRLSIZE         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[1].prlsize);
		RS_printf("IO_PRO.SRO[2].PRCH1.PRVSIZE         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[1].prvsize);
		RS_printf("IO_PRO.SRO[2].PRCH1.PRHSIZE         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[1].prhsize);

		// PRCH-2
		RS_printf("IO_PRO.SRO[2].PRCH2.PRCHTRG         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[2].prchtrg);
		RS_printf("IO_PRO.SRO[2].PRCH2.PRCHCTL         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[2].prchctl);
		RS_printf("IO_PRO.SRO[2].PRCH2.PRCHRS          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[2].prchrs);
		RS_printf("IO_PRO.SRO[2].PRCH2.PRAXCTL         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[2].praxctl);
		RS_printf("IO_PRO.SRO[2].PRCH2.PRCHINTENB      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[2].prchintenb);
		RS_printf("IO_PRO.SRO[2].PRCH2.PRCHINTFLG      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[2].prchintflg);
		RS_printf("IO_PRO.SRO[2].PRCH2.PRCHBRESP       = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[2].prchbresp);
		RS_printf("IO_PRO.SRO[2].PRCH2.PRSA            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[2].prsa);
		RS_printf("IO_PRO.SRO[2].PRCH2.PRLSIZE         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[2].prlsize);
		RS_printf("IO_PRO.SRO[2].PRCH2.PRVSIZE         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[2].prvsize);
		RS_printf("IO_PRO.SRO[2].PRCH2.PRHSIZE         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[2].prhsize);

		// PRCH-3
		RS_printf("IO_PRO.SRO[2].PRCH3.PRCHTRG         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[3].prchtrg);
		RS_printf("IO_PRO.SRO[2].PRCH3.PRCHCTL         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[3].prchctl);
		RS_printf("IO_PRO.SRO[2].PRCH3.PRCHRS          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[3].prchrs);
		RS_printf("IO_PRO.SRO[2].PRCH3.PRAXCTL         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[3].praxctl);
		RS_printf("IO_PRO.SRO[2].PRCH3.PRCHINTENB      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[3].prchintenb);
		RS_printf("IO_PRO.SRO[2].PRCH3.PRCHINTFLG      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[3].prchintflg);
		RS_printf("IO_PRO.SRO[2].PRCH3.PRCHBRESP       = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[3].prchbresp);
		RS_printf("IO_PRO.SRO[2].PRCH3.PRSA            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[3].prsa);
		RS_printf("IO_PRO.SRO[2].PRCH3.PRLSIZE         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[3].prlsize);
		RS_printf("IO_PRO.SRO[2].PRCH3.PRVSIZE         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[3].prvsize);
		RS_printf("IO_PRO.SRO[2].PRCH3.PRHSIZE         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[3].prhsize);

		// PRCH-4
		RS_printf("IO_PRO.SRO[2].PRCH4.PRCHTRG         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[4].prchtrg);
		RS_printf("IO_PRO.SRO[2].PRCH4.PRCHCTL         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[4].prchctl);
		RS_printf("IO_PRO.SRO[2].PRCH4.PRCHRS          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[4].prchrs);
		RS_printf("IO_PRO.SRO[2].PRCH4.PRAXCTL         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[4].praxctl);
		RS_printf("IO_PRO.SRO[2].PRCH4.PRCHINTENB      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[4].prchintenb);
		RS_printf("IO_PRO.SRO[2].PRCH4.PRCHINTFLG      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[4].prchintflg);
		RS_printf("IO_PRO.SRO[2].PRCH4.PRCHBRESP       = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[4].prchbresp);
		RS_printf("IO_PRO.SRO[2].PRCH4.PRSA            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[4].prsa);
		RS_printf("IO_PRO.SRO[2].PRCH4.PRLSIZE         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[4].prlsize);
		RS_printf("IO_PRO.SRO[2].PRCH4.PRVSIZE         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[4].prvsize);
		RS_printf("IO_PRO.SRO[2].PRCH4.PRHSIZE         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[4].prhsize);

		// PRCH-5
		RS_printf("IO_PRO.SRO[2].PRCH5.PRCHTRG         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[5].prchtrg);
		RS_printf("IO_PRO.SRO[2].PRCH5.PRCHCTL         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[5].prchctl);
		RS_printf("IO_PRO.SRO[2].PRCH5.PRCHRS          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[5].prchrs);
		RS_printf("IO_PRO.SRO[2].PRCH5.PRAXCTL         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[5].praxctl);
		RS_printf("IO_PRO.SRO[2].PRCH5.PRCHINTENB      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[5].prchintenb);
		RS_printf("IO_PRO.SRO[2].PRCH5.PRCHINTFLG      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[5].prchintflg);
		RS_printf("IO_PRO.SRO[2].PRCH5.PRCHBRESP       = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[5].prchbresp);
		RS_printf("IO_PRO.SRO[2].PRCH5.PRSA            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[5].prsa);
		RS_printf("IO_PRO.SRO[2].PRCH5.PRLSIZE         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[5].prlsize);
		RS_printf("IO_PRO.SRO[2].PRCH5.PRVSIZE         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[5].prvsize);
		RS_printf("IO_PRO.SRO[2].PRCH5.PRHSIZE         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[5].prhsize);

		// PRCH-6
		RS_printf("IO_PRO.SRO[2].PRCH6.PRCHTRG         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[6].prchtrg);
		RS_printf("IO_PRO.SRO[2].PRCH6.PRCHCTL         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[6].prchctl);
		RS_printf("IO_PRO.SRO[2].PRCH6.PRCHRS          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[6].prchrs);
		RS_printf("IO_PRO.SRO[2].PRCH6.PRAXCTL         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[6].praxctl);
		RS_printf("IO_PRO.SRO[2].PRCH6.PRCHINTENB      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[6].prchintenb);
		RS_printf("IO_PRO.SRO[2].PRCH6.PRCHINTFLG      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[6].prchintflg);
		RS_printf("IO_PRO.SRO[2].PRCH6.PRCHBRESP       = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[6].prchbresp);
		RS_printf("IO_PRO.SRO[2].PRCH6.PRSA            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[6].prsa);
		RS_printf("IO_PRO.SRO[2].PRCH6.PRLSIZE         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[6].prlsize);
		RS_printf("IO_PRO.SRO[2].PRCH6.PRVSIZE         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[6].prvsize);
		RS_printf("IO_PRO.SRO[2].PRCH6.PRHSIZE         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[6].prhsize);

		// PRCH-7
		RS_printf("IO_PRO.SRO[2].PRCH7.PRCHTRG         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[7].prchtrg);
		RS_printf("IO_PRO.SRO[2].PRCH7.PRCHCTL         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[7].prchctl);
		RS_printf("IO_PRO.SRO[2].PRCH7.PRCHRS          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[7].prchrs);
		RS_printf("IO_PRO.SRO[2].PRCH7.PRAXCTL         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[7].praxctl);
		RS_printf("IO_PRO.SRO[2].PRCH7.PRCHINTENB      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[7].prchintenb);
		RS_printf("IO_PRO.SRO[2].PRCH7.PRCHINTFLG      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[7].prchintflg);
		RS_printf("IO_PRO.SRO[2].PRCH7.PRCHBRESP       = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[7].prchbresp);
		RS_printf("IO_PRO.SRO[2].PRCH7.PRSA            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[7].prsa);
		RS_printf("IO_PRO.SRO[2].PRCH7.PRLSIZE         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[7].prlsize);
		RS_printf("IO_PRO.SRO[2].PRCH7.PRVSIZE         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[7].prvsize);
		RS_printf("IO_PRO.SRO[2].PRCH7.PRHSIZE         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[7].prhsize);

		// PRCH-8
		RS_printf("IO_PRO.SRO[2].PRCH8.PRCHTRG         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[8].prchtrg);
		RS_printf("IO_PRO.SRO[2].PRCH8.PRCHCTL         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[8].prchctl);
		RS_printf("IO_PRO.SRO[2].PRCH8.PRCHRS          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[8].prchrs);
		RS_printf("IO_PRO.SRO[2].PRCH8.PRAXCTL         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[8].praxctl);
		RS_printf("IO_PRO.SRO[2].PRCH8.PRCHINTENB      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[8].prchintenb);
		RS_printf("IO_PRO.SRO[2].PRCH8.PRCHINTFLG      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[8].prchintflg);
		RS_printf("IO_PRO.SRO[2].PRCH8.PRCHBRESP       = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[8].prchbresp);
		RS_printf("IO_PRO.SRO[2].PRCH8.PRSA            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[8].prsa);
		RS_printf("IO_PRO.SRO[2].PRCH8.PRLSIZE         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[8].prlsize);
		RS_printf("IO_PRO.SRO[2].PRCH8.PRVSIZE         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[8].prvsize);
		RS_printf("IO_PRO.SRO[2].PRCH8.PRHSIZE         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[8].prhsize);

		// PRCH-9
		RS_printf("IO_PRO.SRO[2].PRCH9.PRCHTRG         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[9].prchtrg);
		RS_printf("IO_PRO.SRO[2].PRCH9.PRCHCTL         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[9].prchctl);
		RS_printf("IO_PRO.SRO[2].PRCH9.PRCHRS          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[9].prchrs);
		RS_printf("IO_PRO.SRO[2].PRCH9.PRAXCTL         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[9].praxctl);
		RS_printf("IO_PRO.SRO[2].PRCH9.PRCHINTENB      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[9].prchintenb);
		RS_printf("IO_PRO.SRO[2].PRCH9.PRCHINTFLG      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[9].prchintflg);
		RS_printf("IO_PRO.SRO[2].PRCH9.PRCHBRESP       = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[9].prchbresp);
		RS_printf("IO_PRO.SRO[2].PRCH9.PRSA            = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[9].prsa);
		RS_printf("IO_PRO.SRO[2].PRCH9.PRLSIZE         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[9].prlsize);
		RS_printf("IO_PRO.SRO[2].PRCH9.PRVSIZE         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[9].prvsize);
		RS_printf("IO_PRO.SRO[2].PRCH9.PRHSIZE         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.prch[9].prhsize);

		// MONI-0
		RS_printf("IO_PRO.SRO[2].MONI0.MONITRG         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.moni0.monitrg);
		RS_printf("IO_PRO.SRO[2].MONI0.MONICTL         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.moni0.monictl);
		RS_printf("IO_PRO.SRO[2].MONI0.MONIINTFLG      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.moni0.moniintflg);
		RS_printf("IO_PRO.SRO[2].MONI0.MONIINTENB      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.moni0.moniintenb);
		RS_printf("IO_PRO.SRO[2].MONI0.MONIVD          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.moni0.monivd);
		RS_printf("IO_PRO.SRO[2].MONI0.MONIHD          = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.moni0.monihd);
		RS_printf("IO_PRO.SRO[2].MONI0.MONIEPF         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.moni0.moniepf);
		RS_printf("IO_PRO.SRO[2].MONI0.MONIEPLMIN      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.moni0.monieplmin);
		RS_printf("IO_PRO.SRO[2].MONI0.MONIEPLMAX      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.moni0.monieplmax);
		RS_printf("IO_PRO.SRO[2].MONI0.MONIBLF         = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.moni0.moniblf);
		RS_printf("IO_PRO.SRO[2].MONI0.MONIBLLMIN      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.moni0.monibllmin);
		RS_printf("IO_PRO.SRO[2].MONI0.MONIBLLMAX      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.moni0.monibllmax);
		RS_printf("IO_PRO.SRO[2].MONI0.MONIHDEXP       = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.moni0.monihdexp);
		RS_printf("IO_PRO.SRO[2].MONI0.MONIEPFEXP      = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.moni0.moniepfexp);
		RS_printf("IO_PRO.SRO[2].MONI0.MONIBLLMINEXP   = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.moni0.monibllminexp);
		RS_printf("IO_PRO.SRO[2].MONI0.MONIBLLMAXEXP   = %x\n", (unsigned int)&ioPro.imgPipe[1].sro.moni0.monibllmaxexp);

	}

#endif	/** SRO Unit(pipe[2]) **/
#endif /* if 0 */

}

ProTest4* pro_test4_new(void)
{
	ProTest4* self = k_object_new_with_private(PRO_TYPE_TEST4, sizeof(ProTest4Private));

	return self;
}
