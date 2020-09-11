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
#include "protest8.h"


K_TYPE_DEFINE_WITH_PRIVATE(ProTest8, pro_test8);
#define PRO_TEST8_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ProTest8Private, PRO_TYPE_TEST8))


struct _ProTest8Private
{
	kint a;
};
/*
 * IMPL
 */
static void pro_test8_constructor(ProTest8 *self)
{
	ProTest8Private *priv = PRO_TEST8_GET_PRIVATE(self);

	priv->a = 0;
}

static void pro_test8_destructor(ProTest8 *self)
{
	ProTest8Private *priv = PRO_TEST8_GET_PRIVATE(self);

	priv->a = 0;
}
/*
 * PUBLIC
 */
void pro_test8(ProTest8 *self, EProBlockType type, IoPro ioPro)
{
#if 0
#ifdef D_ENABLE_IO_PRO_STAT		/** STAT Unit **/
	if(type == IntErnals_E_PRO_BLOCK_TYPE_STAT) {
		// AF1
		// General control Unit
		IntErnals_RS_printf("ioPro.stat.af1.afgbal.aftrg        = %x\n", (kuint)&ioPro.stat.af[1].afgbal.aftrg );
		IntErnals_RS_printf("ioPro.stat.af1.afgbal.afeben       = %x\n", (kuint)&ioPro.stat.af[1].afgbal.afeben );
		IntErnals_RS_printf("ioPro.stat.af1.afgbal.afintenb     = %x\n", (kuint)&ioPro.stat.af[1].afgbal.afintenb );
		IntErnals_RS_printf("ioPro.stat.af1.afgbal.afintflg     = %x\n", (kuint)&ioPro.stat.af[1].afgbal.afintflg );
		IntErnals_RS_printf("ioPro.stat.af1.afgbal.afgv         = %x\n", (kuint)&ioPro.stat.af[1].afgbal.afgv );
		IntErnals_RS_printf("ioPro.stat.af1.afgbal.afgh         = %x\n", (kuint)&ioPro.stat.af[1].afgbal.afgh );
		IntErnals_RS_printf("ioPro.stat.af1.afgbal.afgvw        = %x\n", (kuint)&ioPro.stat.af[1].afgbal.afgvw );
		IntErnals_RS_printf("ioPro.stat.af1.afgbal.afghw        = %x\n", (kuint)&ioPro.stat.af[1].afgbal.afghw );
		IntErnals_RS_printf("ioPro.stat.af1.afgbal.afpaen       = %x\n", (kuint)&ioPro.stat.af[1].afgbal.afpaen );
		// Evaluted value Calculation Unit(0)
		IntErnals_RS_printf("ioPro.stat.af1.afmain0.afmtrxrr    = %x\n", (kuint)&ioPro.stat.af[1].afmain0.afmtrxrr );
		IntErnals_RS_printf("ioPro.stat.af1.afmain0.afmtrxgr    = %x\n", (kuint)&ioPro.stat.af[1].afmain0.afmtrxgr );
		IntErnals_RS_printf("ioPro.stat.af1.afmain0.afmtrxgb    = %x\n", (kuint)&ioPro.stat.af[1].afmain0.afmtrxgb );
		IntErnals_RS_printf("ioPro.stat.af1.afmain0.afmtrxbb    = %x\n", (kuint)&ioPro.stat.af[1].afmain0.afmtrxbb );
		IntErnals_RS_printf("ioPro.stat.af1.afmain0.afmden      = %x\n", (kuint)&ioPro.stat.af[1].afmain0.afmden );
		IntErnals_RS_printf("ioPro.stat.af1.afmain0.afknen      = %x\n", (kuint)&ioPro.stat.af[1].afmain0.afknen );
		IntErnals_RS_printf("ioPro.stat.af1.afmain0.afknb       = %x\n", (kuint)&ioPro.stat.af[1].afmain0.afknb );
		IntErnals_RS_printf("ioPro.stat.af1.afmain0.afkninc     = %x\n", (kuint)&ioPro.stat.af[1].afmain0.afkninc );
		IntErnals_RS_printf("ioPro.stat.af1.afmain0.afknofs     = %x\n", (kuint)&ioPro.stat.af[1].afmain0.afknofs );
		// Evaluted value Calculation Unit(1)
		IntErnals_RS_printf("ioPro.stat.af1.afmain1.afmtrxrr    = %x\n", (kuint)&ioPro.stat.af[1].afmain1.afmtrxrr );
		IntErnals_RS_printf("ioPro.stat.af1.afmain1.afmtrxgr    = %x\n", (kuint)&ioPro.stat.af[1].afmain1.afmtrxgr );
		IntErnals_RS_printf("ioPro.stat.af1.afmain1.afmtrxgb    = %x\n", (kuint)&ioPro.stat.af[1].afmain1.afmtrxgb );
		IntErnals_RS_printf("ioPro.stat.af1.afmain1.afmtrxbb    = %x\n", (kuint)&ioPro.stat.af[1].afmain1.afmtrxbb );
		IntErnals_RS_printf("ioPro.stat.af1.afmain1.afmden      = %x\n", (kuint)&ioPro.stat.af[1].afmain1.afmden );
		IntErnals_RS_printf("ioPro.stat.af1.afmain1.afknen      = %x\n", (kuint)&ioPro.stat.af[1].afmain1.afknen );
		IntErnals_RS_printf("ioPro.stat.af1.afmain1.afknb       = %x\n", (kuint)&ioPro.stat.af[1].afmain1.afknb );
		IntErnals_RS_printf("ioPro.stat.af1.afmain1.afkninc     = %x\n", (kuint)&ioPro.stat.af[1].afmain1.afkninc );
		IntErnals_RS_printf("ioPro.stat.af1.afmain1.afknofs     = %x\n", (kuint)&ioPro.stat.af[1].afmain1.afknofs );
		// Evaluted value Calculation Unit(2)
		IntErnals_RS_printf("ioPro.stat.af1.afmain2.afmtrxrr    = %x\n", (kuint)&ioPro.stat.af[1].afmain2.afmtrxrr );
		IntErnals_RS_printf("ioPro.stat.af1.afmain2.afmtrxgr    = %x\n", (kuint)&ioPro.stat.af[1].afmain2.afmtrxgr );
		IntErnals_RS_printf("ioPro.stat.af1.afmain2.afmtrxgb    = %x\n", (kuint)&ioPro.stat.af[1].afmain2.afmtrxgb );
		IntErnals_RS_printf("ioPro.stat.af1.afmain2.afmtrxbb    = %x\n", (kuint)&ioPro.stat.af[1].afmain2.afmtrxbb );
		IntErnals_RS_printf("ioPro.stat.af1.afmain2.afmden      = %x\n", (kuint)&ioPro.stat.af[1].afmain2.afmden );
		IntErnals_RS_printf("ioPro.stat.af1.afmain2.afknen      = %x\n", (kuint)&ioPro.stat.af[1].afmain2.afknen );
		IntErnals_RS_printf("ioPro.stat.af1.afmain2.afknb       = %x\n", (kuint)&ioPro.stat.af[1].afmain2.afknb );
		IntErnals_RS_printf("ioPro.stat.af1.afmain2.afkninc     = %x\n", (kuint)&ioPro.stat.af[1].afmain2.afkninc );
		IntErnals_RS_printf("ioPro.stat.af1.afmain2.afknofs     = %x\n", (kuint)&ioPro.stat.af[1].afmain2.afknofs );
		// Vertical Detection Processing Unit Register
		IntErnals_RS_printf("ioPro.stat.af1.afvs.afvsctl        = %x\n", (kuint)&ioPro.stat.af[1].afvs.afvsctl );
		IntErnals_RS_printf("ioPro.stat.af1.afvs.afvsh          = %x\n", (kuint)&ioPro.stat.af[1].afvs.afvsh );
		IntErnals_RS_printf("ioPro.stat.af1.afvs.afvshw         = %x\n", (kuint)&ioPro.stat.af[1].afvs.afvshw );
		IntErnals_RS_printf("ioPro.stat.af1.afvs.afiirvb        = %x\n", (kuint)&ioPro.stat.af[1].afvs.afiirvb );
		IntErnals_RS_printf("ioPro.stat.af1.afvs.afcor2v        = %x\n", (kuint)&ioPro.stat.af[1].afvs.afcor2v );
		IntErnals_RS_printf("ioPro.stat.af1.afvs.affirvb        = %x\n", (kuint)&ioPro.stat.af[1].afvs.affirvb );
		// Horizontal Detection Processing Unit Register(0)
		IntErnals_RS_printf("ioPro.stat.af1.afhs0.afhsctla      = %x\n", (kuint)&ioPro.stat.af[1].afhs0.afhsctla );
		IntErnals_RS_printf("ioPro.stat.af1.afhs0.afhsctlb      = %x\n", (kuint)&ioPro.stat.af[1].afhs0.afhsctlb );
		IntErnals_RS_printf("ioPro.stat.af1.afhs0.affirhba      = %x\n", (kuint)&ioPro.stat.af[1].afhs0.affirhba );
		IntErnals_RS_printf("ioPro.stat.af1.afhs0.affirhbb      = %x\n", (kuint)&ioPro.stat.af[1].afhs0.affirhbb );
		IntErnals_RS_printf("ioPro.stat.af1.afhs0.afcor1ha      = %x\n", (kuint)&ioPro.stat.af[1].afhs0.afcor1ha );
		IntErnals_RS_printf("ioPro.stat.af1.afhs0.afcor1hb      = %x\n", (kuint)&ioPro.stat.af[1].afhs0.afcor1hb );
		IntErnals_RS_printf("ioPro.stat.af1.afhs0.afgainha      = %x\n", (kuint)&ioPro.stat.af[1].afhs0.afgainha );
		IntErnals_RS_printf("ioPro.stat.af1.afhs0.afgainhb      = %x\n", (kuint)&ioPro.stat.af[1].afhs0.afgainhb );
		IntErnals_RS_printf("ioPro.stat.af1.afhs0.afiirhba      = %x\n", (kuint)&ioPro.stat.af[1].afhs0.afiirhba );
		IntErnals_RS_printf("ioPro.stat.af1.afhs0.afiirhbb      = %x\n", (kuint)&ioPro.stat.af[1].afhs0.afiirhbb );
		IntErnals_RS_printf("ioPro.stat.af1.afhs0.afcorbha      = %x\n", (kuint)&ioPro.stat.af[1].afhs0.afcorbha );
		IntErnals_RS_printf("ioPro.stat.af1.afhs0.afcorbhb      = %x\n", (kuint)&ioPro.stat.af[1].afhs0.afcorbhb );
		IntErnals_RS_printf("ioPro.stat.af1.afhs0.afcorofsha    = %x\n", (kuint)&ioPro.stat.af[1].afhs0.afcorofsha );
		IntErnals_RS_printf("ioPro.stat.af1.afhs0.afcorofshb    = %x\n", (kuint)&ioPro.stat.af[1].afhs0.afcorofshb );
		// Horizontal Detection Processing Unit Register(1)
		IntErnals_RS_printf("ioPro.stat.af1.afhs1.afhsctla      = %x\n", (kuint)&ioPro.stat.af[1].afhs1.afhsctla );
		IntErnals_RS_printf("ioPro.stat.af1.afhs1.afhsctlb      = %x\n", (kuint)&ioPro.stat.af[1].afhs1.afhsctlb );
		IntErnals_RS_printf("ioPro.stat.af1.afhs1.affirhba      = %x\n", (kuint)&ioPro.stat.af[1].afhs1.affirhba );
		IntErnals_RS_printf("ioPro.stat.af1.afhs1.affirhbb      = %x\n", (kuint)&ioPro.stat.af[1].afhs1.affirhbb );
		IntErnals_RS_printf("ioPro.stat.af1.afhs1.afcor1ha      = %x\n", (kuint)&ioPro.stat.af[1].afhs1.afcor1ha );
		IntErnals_RS_printf("ioPro.stat.af1.afhs1.afcor1hb      = %x\n", (kuint)&ioPro.stat.af[1].afhs1.afcor1hb );
		IntErnals_RS_printf("ioPro.stat.af1.afhs1.afgainha      = %x\n", (kuint)&ioPro.stat.af[1].afhs1.afgainha );
		IntErnals_RS_printf("ioPro.stat.af1.afhs1.afgainhb      = %x\n", (kuint)&ioPro.stat.af[1].afhs1.afgainhb );
		IntErnals_RS_printf("ioPro.stat.af1.afhs1.afiirhba      = %x\n", (kuint)&ioPro.stat.af[1].afhs1.afiirhba );
		IntErnals_RS_printf("ioPro.stat.af1.afhs1.afiirhbb      = %x\n", (kuint)&ioPro.stat.af[1].afhs1.afiirhbb );
		IntErnals_RS_printf("ioPro.stat.af1.afhs1.afcorbha      = %x\n", (kuint)&ioPro.stat.af[1].afhs1.afcorbha );
		IntErnals_RS_printf("ioPro.stat.af1.afhs1.afcorbhb      = %x\n", (kuint)&ioPro.stat.af[1].afhs1.afcorbhb );
		IntErnals_RS_printf("ioPro.stat.af1.afhs1.afcorofsha    = %x\n", (kuint)&ioPro.stat.af[1].afhs1.afcorofsha );
		IntErnals_RS_printf("ioPro.stat.af1.afhs1.afcorofshb    = %x\n", (kuint)&ioPro.stat.af[1].afhs1.afcorofshb );
		// Horizontal Detection Processing Unit Register(2)
		IntErnals_RS_printf("ioPro.stat.af1.afhs2.afhsctla      = %x\n", (kuint)&ioPro.stat.af[1].afhs2.afhsctla );
		IntErnals_RS_printf("ioPro.stat.af1.afhs2.afhsctlb      = %x\n", (kuint)&ioPro.stat.af[1].afhs2.afhsctlb );
		IntErnals_RS_printf("ioPro.stat.af1.afhs2.affirhba      = %x\n", (kuint)&ioPro.stat.af[1].afhs2.affirhba );
		IntErnals_RS_printf("ioPro.stat.af1.afhs2.affirhbb      = %x\n", (kuint)&ioPro.stat.af[1].afhs2.affirhbb );
		IntErnals_RS_printf("ioPro.stat.af1.afhs2.afcor1ha      = %x\n", (kuint)&ioPro.stat.af[1].afhs2.afcor1ha );
		IntErnals_RS_printf("ioPro.stat.af1.afhs2.afcor1hb      = %x\n", (kuint)&ioPro.stat.af[1].afhs2.afcor1hb );
		IntErnals_RS_printf("ioPro.stat.af1.afhs2.afgainha      = %x\n", (kuint)&ioPro.stat.af[1].afhs2.afgainha );
		IntErnals_RS_printf("ioPro.stat.af1.afhs2.afgainhb      = %x\n", (kuint)&ioPro.stat.af[1].afhs2.afgainhb );
		IntErnals_RS_printf("ioPro.stat.af1.afhs2.afiirhba      = %x\n", (kuint)&ioPro.stat.af[1].afhs2.afiirhba );
		IntErnals_RS_printf("ioPro.stat.af1.afhs2.afiirhbb      = %x\n", (kuint)&ioPro.stat.af[1].afhs2.afiirhbb );
		IntErnals_RS_printf("ioPro.stat.af1.afhs2.afcorbha      = %x\n", (kuint)&ioPro.stat.af[1].afhs2.afcorbha );
		IntErnals_RS_printf("ioPro.stat.af1.afhs2.afcorbhb      = %x\n", (kuint)&ioPro.stat.af[1].afhs2.afcorbhb );
		IntErnals_RS_printf("ioPro.stat.af1.afhs2.afcorofsha    = %x\n", (kuint)&ioPro.stat.af[1].afhs2.afcorofsha );
		IntErnals_RS_printf("ioPro.stat.af1.afhs2.afcorofshb    = %x\n", (kuint)&ioPro.stat.af[1].afhs2.afcorofshb );
		// Detection Window Processing Unit Register(0)
		IntErnals_RS_printf("ioPro.stat.af1.afwin0.afwinctl     = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afwinctl );
		IntErnals_RS_printf("ioPro.stat.af1.afwin0.afclvge      = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afclvge );
		IntErnals_RS_printf("ioPro.stat.af1.afwin0.afclvl       = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afclvl );
		IntErnals_RS_printf("ioPro.stat.af1.afwin0.afv          = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afv );
		IntErnals_RS_printf("ioPro.stat.af1.afwin0.afh          = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afh );
		IntErnals_RS_printf("ioPro.stat.af1.afwin0.afvw         = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afvw );
		IntErnals_RS_printf("ioPro.stat.af1.afwin0.afhw         = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afhw );
		IntErnals_RS_printf("ioPro.stat.af1.afwin0.afdatas      = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afdatas );
		IntErnals_RS_printf("ioPro.stat.af1.afwin0.afdatage     = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afdatage );
		IntErnals_RS_printf("ioPro.stat.af1.afwin0.afdatal      = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afdatal );
		IntErnals_RS_printf("ioPro.stat.af1.afwin0.afdatah0     = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afdatah0 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin0.afdatah1     = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afdatah1 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin0.afdatah2     = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afdatah2 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin0.afdatav      = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afdatav );
		IntErnals_RS_printf("ioPro.stat.af1.afwin0.afslwm       = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afslwm );
		IntErnals_RS_printf("ioPro.stat.af1.afwin0.afdatamax    = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afdatamax );
		IntErnals_RS_printf("ioPro.stat.af1.afwin0.afdatamin    = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afdatamin );
		IntErnals_RS_printf("ioPro.stat.af1.afwin0.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afdatamh0 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin0.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afdatamh1 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin0.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afdatamh2 );
		// Detection Window Processing Unit Register(1)
		IntErnals_RS_printf("ioPro.stat.af1.afwin1.afwinctl     = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afwinctl );
		IntErnals_RS_printf("ioPro.stat.af1.afwin1.afclvge      = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afclvge );
		IntErnals_RS_printf("ioPro.stat.af1.afwin1.afclvl       = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afclvl );
		IntErnals_RS_printf("ioPro.stat.af1.afwin1.afv          = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afv );
		IntErnals_RS_printf("ioPro.stat.af1.afwin1.afh          = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afh );
		IntErnals_RS_printf("ioPro.stat.af1.afwin1.afvw         = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afvw );
		IntErnals_RS_printf("ioPro.stat.af1.afwin1.afhw         = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afhw );
		IntErnals_RS_printf("ioPro.stat.af1.afwin1.afdatas      = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afdatas );
		IntErnals_RS_printf("ioPro.stat.af1.afwin1.afdatage     = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afdatage );
		IntErnals_RS_printf("ioPro.stat.af1.afwin1.afdatal      = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afdatal );
		IntErnals_RS_printf("ioPro.stat.af1.afwin1.afdatah0     = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afdatah0 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin1.afdatah1     = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afdatah1 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin1.afdatah2     = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afdatah2 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin1.afdatav      = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afdatav );
		IntErnals_RS_printf("ioPro.stat.af1.afwin1.afslwm       = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afslwm );
		IntErnals_RS_printf("ioPro.stat.af1.afwin1.afdatamax    = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afdatamax );
		IntErnals_RS_printf("ioPro.stat.af1.afwin1.afdatamin    = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afdatamin );
		IntErnals_RS_printf("ioPro.stat.af1.afwin1.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afdatamh0 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin1.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afdatamh1 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin1.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afdatamh2 );
		// Detection Window Processing Unit Register(2)
		IntErnals_RS_printf("ioPro.stat.af1.afwin2.afwinctl     = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afwinctl );
		IntErnals_RS_printf("ioPro.stat.af1.afwin2.afclvge      = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afclvge );
		IntErnals_RS_printf("ioPro.stat.af1.afwin2.afclvl       = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afclvl );
		IntErnals_RS_printf("ioPro.stat.af1.afwin2.afv          = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afv );
		IntErnals_RS_printf("ioPro.stat.af1.afwin2.afh          = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afh );
		IntErnals_RS_printf("ioPro.stat.af1.afwin2.afvw         = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afvw );
		IntErnals_RS_printf("ioPro.stat.af1.afwin2.afhw         = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afhw );
		IntErnals_RS_printf("ioPro.stat.af1.afwin2.afdatas      = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afdatas );
		IntErnals_RS_printf("ioPro.stat.af1.afwin2.afdatage     = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afdatage );
		IntErnals_RS_printf("ioPro.stat.af1.afwin2.afdatal      = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afdatal );
		IntErnals_RS_printf("ioPro.stat.af1.afwin2.afdatah0     = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afdatah0 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin2.afdatah1     = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afdatah1 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin2.afdatah2     = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afdatah2 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin2.afdatav      = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afdatav );
		IntErnals_RS_printf("ioPro.stat.af1.afwin2.afslwm       = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afslwm );
		IntErnals_RS_printf("ioPro.stat.af1.afwin2.afdatamax    = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afdatamax );
		IntErnals_RS_printf("ioPro.stat.af1.afwin2.afdatamin    = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afdatamin );
		IntErnals_RS_printf("ioPro.stat.af1.afwin2.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afdatamh0 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin2.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afdatamh1 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin2.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afdatamh2 );
		// Detection Window Processing Unit Register(3)
		IntErnals_RS_printf("ioPro.stat.af1.afwin3.afwinctl     = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afwinctl );
		IntErnals_RS_printf("ioPro.stat.af1.afwin3.afclvge      = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afclvge );
		IntErnals_RS_printf("ioPro.stat.af1.afwin3.afclvl       = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afclvl );
		IntErnals_RS_printf("ioPro.stat.af1.afwin3.afv          = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afv );
		IntErnals_RS_printf("ioPro.stat.af1.afwin3.afh          = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afh );
		IntErnals_RS_printf("ioPro.stat.af1.afwin3.afvw         = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afvw );
		IntErnals_RS_printf("ioPro.stat.af1.afwin3.afhw         = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afhw );
		IntErnals_RS_printf("ioPro.stat.af1.afwin3.afdatas      = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afdatas );
		IntErnals_RS_printf("ioPro.stat.af1.afwin3.afdatage     = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afdatage );
		IntErnals_RS_printf("ioPro.stat.af1.afwin3.afdatal      = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afdatal );
		IntErnals_RS_printf("ioPro.stat.af1.afwin3.afdatah0     = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afdatah0 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin3.afdatah1     = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afdatah1 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin3.afdatah2     = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afdatah2 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin3.afdatav      = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afdatav );
		IntErnals_RS_printf("ioPro.stat.af1.afwin3.afslwm       = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afslwm );
		IntErnals_RS_printf("ioPro.stat.af1.afwin3.afdatamax    = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afdatamax );
		IntErnals_RS_printf("ioPro.stat.af1.afwin3.afdatamin    = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afdatamin );
		IntErnals_RS_printf("ioPro.stat.af1.afwin3.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afdatamh0 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin3.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afdatamh1 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin3.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afdatamh2 );
		// Detection Window Processing Unit Register(4)
		IntErnals_RS_printf("ioPro.stat.af1.afwin4.afwinctl     = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afwinctl );
		IntErnals_RS_printf("ioPro.stat.af1.afwin4.afclvge      = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afclvge );
		IntErnals_RS_printf("ioPro.stat.af1.afwin4.afclvl       = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afclvl );
		IntErnals_RS_printf("ioPro.stat.af1.afwin4.afv          = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afv );
		IntErnals_RS_printf("ioPro.stat.af1.afwin4.afh          = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afh );
		IntErnals_RS_printf("ioPro.stat.af1.afwin4.afvw         = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afvw );
		IntErnals_RS_printf("ioPro.stat.af1.afwin4.afhw         = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afhw );
		IntErnals_RS_printf("ioPro.stat.af1.afwin4.afdatas      = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afdatas );
		IntErnals_RS_printf("ioPro.stat.af1.afwin4.afdatage     = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afdatage );
		IntErnals_RS_printf("ioPro.stat.af1.afwin4.afdatal      = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afdatal );
		IntErnals_RS_printf("ioPro.stat.af1.afwin4.afdatah0     = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afdatah0 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin4.afdatah1     = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afdatah1 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin4.afdatah2     = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afdatah2 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin4.afdatav      = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afdatav );
		IntErnals_RS_printf("ioPro.stat.af1.afwin4.afslwm       = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afslwm );
		IntErnals_RS_printf("ioPro.stat.af1.afwin4.afdatamax    = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afdatamax );
		IntErnals_RS_printf("ioPro.stat.af1.afwin4.afdatamin    = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afdatamin );
		IntErnals_RS_printf("ioPro.stat.af1.afwin4.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afdatamh0 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin4.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afdatamh1 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin4.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afdatamh2 );
		// Detection Window Processing Unit Register(5)
		IntErnals_RS_printf("ioPro.stat.af1.afwin5.afwinctl     = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afwinctl );
		IntErnals_RS_printf("ioPro.stat.af1.afwin5.afclvge      = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afclvge );
		IntErnals_RS_printf("ioPro.stat.af1.afwin5.afclvl       = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afclvl );
		IntErnals_RS_printf("ioPro.stat.af1.afwin5.afv          = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afv );
		IntErnals_RS_printf("ioPro.stat.af1.afwin5.afh          = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afh );
		IntErnals_RS_printf("ioPro.stat.af1.afwin5.afvw         = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afvw );
		IntErnals_RS_printf("ioPro.stat.af1.afwin5.afhw         = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afhw );
		IntErnals_RS_printf("ioPro.stat.af1.afwin5.afdatas      = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afdatas );
		IntErnals_RS_printf("ioPro.stat.af1.afwin5.afdatage     = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afdatage );
		IntErnals_RS_printf("ioPro.stat.af1.afwin5.afdatal      = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afdatal );
		IntErnals_RS_printf("ioPro.stat.af1.afwin5.afdatah0     = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afdatah0 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin5.afdatah1     = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afdatah1 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin5.afdatah2     = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afdatah2 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin5.afdatav      = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afdatav );
		IntErnals_RS_printf("ioPro.stat.af1.afwin5.afslwm       = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afslwm );
		IntErnals_RS_printf("ioPro.stat.af1.afwin5.afdatamax    = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afdatamax );
		IntErnals_RS_printf("ioPro.stat.af1.afwin5.afdatamin    = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afdatamin );
		IntErnals_RS_printf("ioPro.stat.af1.afwin5.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afdatamh0 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin5.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afdatamh1 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin5.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afdatamh2 );
		// Detection Window Processing Unit Register(6)
		IntErnals_RS_printf("ioPro.stat.af1.afwin6.afwinctl     = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afwinctl );
		IntErnals_RS_printf("ioPro.stat.af1.afwin6.afclvge      = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afclvge );
		IntErnals_RS_printf("ioPro.stat.af1.afwin6.afclvl       = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afclvl );
		IntErnals_RS_printf("ioPro.stat.af1.afwin6.afv          = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afv );
		IntErnals_RS_printf("ioPro.stat.af1.afwin6.afh          = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afh );
		IntErnals_RS_printf("ioPro.stat.af1.afwin6.afvw         = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afvw );
		IntErnals_RS_printf("ioPro.stat.af1.afwin6.afhw         = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afhw );
		IntErnals_RS_printf("ioPro.stat.af1.afwin6.afdatas      = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afdatas );
		IntErnals_RS_printf("ioPro.stat.af1.afwin6.afdatage     = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afdatage );
		IntErnals_RS_printf("ioPro.stat.af1.afwin6.afdatal      = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afdatal );
		IntErnals_RS_printf("ioPro.stat.af1.afwin6.afdatah0     = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afdatah0 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin6.afdatah1     = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afdatah1 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin6.afdatah2     = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afdatah2 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin6.afdatav      = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afdatav );
		IntErnals_RS_printf("ioPro.stat.af1.afwin6.afslwm       = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afslwm );
		IntErnals_RS_printf("ioPro.stat.af1.afwin6.afdatamax    = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afdatamax );
		IntErnals_RS_printf("ioPro.stat.af1.afwin6.afdatamin    = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afdatamin );
		IntErnals_RS_printf("ioPro.stat.af1.afwin6.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afdatamh0 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin6.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afdatamh1 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin6.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afdatamh2 );
		// Detection Window Processing Unit Register(7)
		IntErnals_RS_printf("ioPro.stat.af1.afwin7.afwinctl     = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afwinctl );
		IntErnals_RS_printf("ioPro.stat.af1.afwin7.afclvge      = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afclvge );
		IntErnals_RS_printf("ioPro.stat.af1.afwin7.afclvl       = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afclvl );
		IntErnals_RS_printf("ioPro.stat.af1.afwin7.afv          = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afv );
		IntErnals_RS_printf("ioPro.stat.af1.afwin7.afh          = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afh );
		IntErnals_RS_printf("ioPro.stat.af1.afwin7.afvw         = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afvw );
		IntErnals_RS_printf("ioPro.stat.af1.afwin7.afhw         = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afhw );
		IntErnals_RS_printf("ioPro.stat.af1.afwin7.afdatas      = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afdatas );
		IntErnals_RS_printf("ioPro.stat.af1.afwin7.afdatage     = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afdatage );
		IntErnals_RS_printf("ioPro.stat.af1.afwin7.afdatal      = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afdatal );
		IntErnals_RS_printf("ioPro.stat.af1.afwin7.afdatah0     = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afdatah0 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin7.afdatah1     = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afdatah1 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin7.afdatah2     = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afdatah2 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin7.afdatav      = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afdatav );
		IntErnals_RS_printf("ioPro.stat.af1.afwin7.afslwm       = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afslwm );
		IntErnals_RS_printf("ioPro.stat.af1.afwin7.afdatamax    = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afdatamax );
		IntErnals_RS_printf("ioPro.stat.af1.afwin7.afdatamin    = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afdatamin );
		IntErnals_RS_printf("ioPro.stat.af1.afwin7.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afdatamh0 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin7.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afdatamh1 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin7.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afdatamh2 );
		// Detection Window Processing Unit Register(8)
		IntErnals_RS_printf("ioPro.stat.af1.afwin8.afwinctl     = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afwinctl );
		IntErnals_RS_printf("ioPro.stat.af1.afwin8.afclvge      = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afclvge );
		IntErnals_RS_printf("ioPro.stat.af1.afwin8.afclvl       = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afclvl );
		IntErnals_RS_printf("ioPro.stat.af1.afwin8.afv          = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afv );
		IntErnals_RS_printf("ioPro.stat.af1.afwin8.afh          = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afh );
		IntErnals_RS_printf("ioPro.stat.af1.afwin8.afvw         = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afvw );
		IntErnals_RS_printf("ioPro.stat.af1.afwin8.afhw         = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afhw );
		IntErnals_RS_printf("ioPro.stat.af1.afwin8.afdatas      = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afdatas );
		IntErnals_RS_printf("ioPro.stat.af1.afwin8.afdatage     = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afdatage );
		IntErnals_RS_printf("ioPro.stat.af1.afwin8.afdatal      = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afdatal );
		IntErnals_RS_printf("ioPro.stat.af1.afwin8.afdatah0     = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afdatah0 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin8.afdatah1     = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afdatah1 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin8.afdatah2     = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afdatah2 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin8.afdatav      = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afdatav );
		IntErnals_RS_printf("ioPro.stat.af1.afwin8.afslwm       = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afslwm );
		IntErnals_RS_printf("ioPro.stat.af1.afwin8.afdatamax    = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afdatamax );
		IntErnals_RS_printf("ioPro.stat.af1.afwin8.afdatamin    = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afdatamin );
		IntErnals_RS_printf("ioPro.stat.af1.afwin8.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afdatamh0 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin8.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afdatamh1 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin8.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afdatamh2 );
		// Detection Window Processing Unit Register(9)
		IntErnals_RS_printf("ioPro.stat.af1.afwin9.afwinctl     = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afwinctl );
		IntErnals_RS_printf("ioPro.stat.af1.afwin9.afclvge      = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afclvge );
		IntErnals_RS_printf("ioPro.stat.af1.afwin9.afclvl       = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afclvl );
		IntErnals_RS_printf("ioPro.stat.af1.afwin9.afv          = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afv );
		IntErnals_RS_printf("ioPro.stat.af1.afwin9.afh          = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afh );
		IntErnals_RS_printf("ioPro.stat.af1.afwin9.afvw         = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afvw );
		IntErnals_RS_printf("ioPro.stat.af1.afwin9.afhw         = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afhw );
		IntErnals_RS_printf("ioPro.stat.af1.afwin9.afdatas      = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afdatas );
		IntErnals_RS_printf("ioPro.stat.af1.afwin9.afdatage     = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afdatage );
		IntErnals_RS_printf("ioPro.stat.af1.afwin9.afdatal      = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afdatal );
		IntErnals_RS_printf("ioPro.stat.af1.afwin9.afdatah0     = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afdatah0 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin9.afdatah1     = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afdatah1 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin9.afdatah2     = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afdatah2 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin9.afdatav      = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afdatav );
		IntErnals_RS_printf("ioPro.stat.af1.afwin9.afslwm       = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afslwm );
		IntErnals_RS_printf("ioPro.stat.af1.afwin9.afdatamax    = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afdatamax );
		IntErnals_RS_printf("ioPro.stat.af1.afwin9.afdatamin    = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afdatamin );
		IntErnals_RS_printf("ioPro.stat.af1.afwin9.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afdatamh0 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin9.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afdatamh1 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin9.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afdatamh2 );
		// Detection Window Processing Unit Register(10)
		IntErnals_RS_printf("ioPro.stat.af1.afwin10.afwinctl     = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afwinctl );
		IntErnals_RS_printf("ioPro.stat.af1.afwin10.afclvge      = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afclvge );
		IntErnals_RS_printf("ioPro.stat.af1.afwin10.afclvl       = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afclvl );
		IntErnals_RS_printf("ioPro.stat.af1.afwin10.afv          = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afv );
		IntErnals_RS_printf("ioPro.stat.af1.afwin10.afh          = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afh );
		IntErnals_RS_printf("ioPro.stat.af1.afwin10.afvw         = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afvw );
		IntErnals_RS_printf("ioPro.stat.af1.afwin10.afhw         = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afhw );
		IntErnals_RS_printf("ioPro.stat.af1.afwin10.afdatas      = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afdatas );
		IntErnals_RS_printf("ioPro.stat.af1.afwin10.afdatage     = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afdatage );
		IntErnals_RS_printf("ioPro.stat.af1.afwin10.afdatal      = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afdatal );
		IntErnals_RS_printf("ioPro.stat.af1.afwin10.afdatah0     = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afdatah0 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin10.afdatah1     = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afdatah1 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin10.afdatah2     = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afdatah2 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin10.afdatav      = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afdatav );
		IntErnals_RS_printf("ioPro.stat.af1.afwin10.afslwm       = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afslwm );
		IntErnals_RS_printf("ioPro.stat.af1.afwin10.afdatamax    = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afdatamax );
		IntErnals_RS_printf("ioPro.stat.af1.afwin10.afdatamin    = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afdatamin );
		IntErnals_RS_printf("ioPro.stat.af1.afwin10.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afdatamh0 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin10.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afdatamh1 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin10.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afdatamh2 );
		// Detection Window Processing Unit Register(11)
		IntErnals_RS_printf("ioPro.stat.af1.afwin11.afwinctl     = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afwinctl );
		IntErnals_RS_printf("ioPro.stat.af1.afwin11.afclvge      = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afclvge );
		IntErnals_RS_printf("ioPro.stat.af1.afwin11.afclvl       = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afclvl );
		IntErnals_RS_printf("ioPro.stat.af1.afwin11.afv          = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afv );
		IntErnals_RS_printf("ioPro.stat.af1.afwin11.afh          = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afh );
		IntErnals_RS_printf("ioPro.stat.af1.afwin11.afvw         = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afvw );
		IntErnals_RS_printf("ioPro.stat.af1.afwin11.afhw         = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afhw );
		IntErnals_RS_printf("ioPro.stat.af1.afwin11.afdatas      = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afdatas );
		IntErnals_RS_printf("ioPro.stat.af1.afwin11.afdatage     = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afdatage );
		IntErnals_RS_printf("ioPro.stat.af1.afwin11.afdatal      = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afdatal );
		IntErnals_RS_printf("ioPro.stat.af1.afwin11.afdatah0     = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afdatah0 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin11.afdatah1     = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afdatah1 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin11.afdatah2     = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afdatah2 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin11.afdatav      = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afdatav );
		IntErnals_RS_printf("ioPro.stat.af1.afwin11.afslwm       = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afslwm );
		IntErnals_RS_printf("ioPro.stat.af1.afwin11.afdatamax    = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afdatamax );
		IntErnals_RS_printf("ioPro.stat.af1.afwin11.afdatamin    = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afdatamin );
		IntErnals_RS_printf("ioPro.stat.af1.afwin11.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afdatamh0 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin11.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afdatamh1 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin11.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afdatamh2 );
		// Detection Window Processing Unit Register(12)
		IntErnals_RS_printf("ioPro.stat.af1.afwin12.afwinctl     = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afwinctl );
		IntErnals_RS_printf("ioPro.stat.af1.afwin12.afclvge      = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afclvge );
		IntErnals_RS_printf("ioPro.stat.af1.afwin12.afclvl       = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afclvl );
		IntErnals_RS_printf("ioPro.stat.af1.afwin12.afv          = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afv );
		IntErnals_RS_printf("ioPro.stat.af1.afwin12.afh          = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afh );
		IntErnals_RS_printf("ioPro.stat.af1.afwin12.afvw         = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afvw );
		IntErnals_RS_printf("ioPro.stat.af1.afwin12.afhw         = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afhw );
		IntErnals_RS_printf("ioPro.stat.af1.afwin12.afdatas      = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afdatas );
		IntErnals_RS_printf("ioPro.stat.af1.afwin12.afdatage     = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afdatage );
		IntErnals_RS_printf("ioPro.stat.af1.afwin12.afdatal      = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afdatal );
		IntErnals_RS_printf("ioPro.stat.af1.afwin12.afdatah0     = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afdatah0 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin12.afdatah1     = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afdatah1 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin12.afdatah2     = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afdatah2 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin12.afdatav      = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afdatav );
		IntErnals_RS_printf("ioPro.stat.af1.afwin12.afslwm       = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afslwm );
		IntErnals_RS_printf("ioPro.stat.af1.afwin12.afdatamax    = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afdatamax );
		IntErnals_RS_printf("ioPro.stat.af1.afwin12.afdatamin    = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afdatamin );
		IntErnals_RS_printf("ioPro.stat.af1.afwin12.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afdatamh0 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin12.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afdatamh1 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin12.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afdatamh2 );
		// Detection Window Processing Unit Register(13)
		IntErnals_RS_printf("ioPro.stat.af1.afwin13.afwinctl     = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afwinctl );
		IntErnals_RS_printf("ioPro.stat.af1.afwin13.afclvge      = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afclvge );
		IntErnals_RS_printf("ioPro.stat.af1.afwin13.afclvl       = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afclvl );
		IntErnals_RS_printf("ioPro.stat.af1.afwin13.afv          = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afv );
		IntErnals_RS_printf("ioPro.stat.af1.afwin13.afh          = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afh );
		IntErnals_RS_printf("ioPro.stat.af1.afwin13.afvw         = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afvw );
		IntErnals_RS_printf("ioPro.stat.af1.afwin13.afhw         = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afhw );
		IntErnals_RS_printf("ioPro.stat.af1.afwin13.afdatas      = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afdatas );
		IntErnals_RS_printf("ioPro.stat.af1.afwin13.afdatage     = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afdatage );
		IntErnals_RS_printf("ioPro.stat.af1.afwin13.afdatal      = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afdatal );
		IntErnals_RS_printf("ioPro.stat.af1.afwin13.afdatah0     = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afdatah0 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin13.afdatah1     = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afdatah1 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin13.afdatah2     = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afdatah2 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin13.afdatav      = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afdatav );
		IntErnals_RS_printf("ioPro.stat.af1.afwin13.afslwm       = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afslwm );
		IntErnals_RS_printf("ioPro.stat.af1.afwin13.afdatamax    = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afdatamax );
		IntErnals_RS_printf("ioPro.stat.af1.afwin13.afdatamin    = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afdatamin );
		IntErnals_RS_printf("ioPro.stat.af1.afwin13.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afdatamh0 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin13.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afdatamh1 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin13.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afdatamh2 );
		// Detection Window Processing Unit Register(14)
		IntErnals_RS_printf("ioPro.stat.af1.afwin14.afwinctl     = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afwinctl );
		IntErnals_RS_printf("ioPro.stat.af1.afwin14.afclvge      = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afclvge );
		IntErnals_RS_printf("ioPro.stat.af1.afwin14.afclvl       = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afclvl );
		IntErnals_RS_printf("ioPro.stat.af1.afwin14.afv          = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afv );
		IntErnals_RS_printf("ioPro.stat.af1.afwin14.afh          = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afh );
		IntErnals_RS_printf("ioPro.stat.af1.afwin14.afvw         = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afvw );
		IntErnals_RS_printf("ioPro.stat.af1.afwin14.afhw         = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afhw );
		IntErnals_RS_printf("ioPro.stat.af1.afwin14.afdatas      = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afdatas );
		IntErnals_RS_printf("ioPro.stat.af1.afwin14.afdatage     = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afdatage );
		IntErnals_RS_printf("ioPro.stat.af1.afwin14.afdatal      = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afdatal );
		IntErnals_RS_printf("ioPro.stat.af1.afwin14.afdatah0     = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afdatah0 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin14.afdatah1     = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afdatah1 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin14.afdatah2     = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afdatah2 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin14.afdatav      = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afdatav );
		IntErnals_RS_printf("ioPro.stat.af1.afwin14.afslwm       = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afslwm );
		IntErnals_RS_printf("ioPro.stat.af1.afwin14.afdatamax    = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afdatamax );
		IntErnals_RS_printf("ioPro.stat.af1.afwin14.afdatamin    = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afdatamin );
		IntErnals_RS_printf("ioPro.stat.af1.afwin14.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afdatamh0 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin14.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afdatamh1 );
		IntErnals_RS_printf("ioPro.stat.af1.afwin14.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afdatamh2 );
		// aeawb-0
		IntErnals_RS_printf("ioPro.stat.aeawb0.aetrg            = %x\n", (kuint)&ioPro.stat.aeawb[0].aetrg );
		IntErnals_RS_printf("ioPro.stat.aeawb0.aeawbctl         = %x\n", (kuint)&ioPro.stat.aeawb[0].aeawbctl );
		IntErnals_RS_printf("ioPro.stat.aeawb0.aev              = %x\n", (kuint)&ioPro.stat.aeawb[0].aev );
		IntErnals_RS_printf("ioPro.stat.aeawb0.aeh              = %x\n", (kuint)&ioPro.stat.aeawb[0].aeh );
		IntErnals_RS_printf("ioPro.stat.aeawb0.aevw             = %x\n", (kuint)&ioPro.stat.aeawb[0].aevw );
		IntErnals_RS_printf("ioPro.stat.aeawb0.aetw             = %x\n", (kuint)&ioPro.stat.aeawb[0].aetw );
		IntErnals_RS_printf("ioPro.stat.aeawb0.aebw             = %x\n", (kuint)&ioPro.stat.aeawb[0].aebw );
		IntErnals_RS_printf("ioPro.stat.aeawb0.aehw             = %x\n", (kuint)&ioPro.stat.aeawb[0].aehw );
		IntErnals_RS_printf("ioPro.stat.aeawb0.aelw             = %x\n", (kuint)&ioPro.stat.aeawb[0].aelw );
		IntErnals_RS_printf("ioPro.stat.aeawb0.aerw             = %x\n", (kuint)&ioPro.stat.aeawb[0].aerw );
		IntErnals_RS_printf("ioPro.stat.aeawb0.aevbc            = %x\n", (kuint)&ioPro.stat.aeawb[0].aevbc );
		IntErnals_RS_printf("ioPro.stat.aeawb0.aehbc            = %x\n", (kuint)&ioPro.stat.aeawb[0].aehbc );
		IntErnals_RS_printf("ioPro.stat.aeawb0.aecw1            = %x\n", (kuint)&ioPro.stat.aeawb[0].aecw1 );
		IntErnals_RS_printf("ioPro.stat.aeawb0.aecw2            = %x\n", (kuint)&ioPro.stat.aeawb[0].aecw2 );
		IntErnals_RS_printf("ioPro.stat.aeawb0.aecw3            = %x\n", (kuint)&ioPro.stat.aeawb[0].aecw3 );
		IntErnals_RS_printf("ioPro.stat.aeawb0.awbcw1           = %x\n", (kuint)&ioPro.stat.aeawb[0].awbcw1 );
		IntErnals_RS_printf("ioPro.stat.aeawb0.awbcw2           = %x\n", (kuint)&ioPro.stat.aeawb[0].awbcw2 );
		IntErnals_RS_printf("ioPro.stat.aeawb0.awbcw3           = %x\n", (kuint)&ioPro.stat.aeawb[0].awbcw3 );
		IntErnals_RS_printf("ioPro.stat.aeawb0.aeykrr           = %x\n", (kuint)&ioPro.stat.aeawb[0].aeykrr );
		IntErnals_RS_printf("ioPro.stat.aeawb0.aeykgr           = %x\n", (kuint)&ioPro.stat.aeawb[0].aeykgr );
		IntErnals_RS_printf("ioPro.stat.aeawb0.aeykgb           = %x\n", (kuint)&ioPro.stat.aeawb[0].aeykgb );
		IntErnals_RS_printf("ioPro.stat.aeawb0.aeykbb           = %x\n", (kuint)&ioPro.stat.aeawb[0].aeykbb );
		IntErnals_RS_printf("ioPro.stat.aeawb0.awtdy            = %x\n", (kuint)&ioPro.stat.aeawb[0].awtdy );
		IntErnals_RS_printf("ioPro.stat.aeawb0.awtdr            = %x\n", (kuint)&ioPro.stat.aeawb[0].awtdr );
		IntErnals_RS_printf("ioPro.stat.aeawb0.awtdg            = %x\n", (kuint)&ioPro.stat.aeawb[0].awtdg );
		IntErnals_RS_printf("ioPro.stat.aeawb0.awtdb            = %x\n", (kuint)&ioPro.stat.aeawb[0].awtdb );
		IntErnals_RS_printf("ioPro.stat.aeawb0.awmlcy           = %x\n", (kuint)&ioPro.stat.aeawb[0].awmlcy );
		IntErnals_RS_printf("ioPro.stat.aeawb0.awmlcb           = %x\n", (kuint)&ioPro.stat.aeawb[0].awmlcb );
		IntErnals_RS_printf("ioPro.stat.aeawb0.awmlcr           = %x\n", (kuint)&ioPro.stat.aeawb[0].awmlcr );
		IntErnals_RS_printf("ioPro.stat.aeawb0.awmc             = %x\n", (kuint)&ioPro.stat.aeawb[0].awmc );
		IntErnals_RS_printf("ioPro.stat.aeawb0.linev            = %x\n", (kuint)&ioPro.stat.aeawb[0].linev );
		IntErnals_RS_printf("ioPro.stat.aeawb0.linedata         = %x\n", (kuint)&ioPro.stat.aeawb[0].linedata );
		IntErnals_RS_printf("ioPro.stat.aeawb0.lineintenb       = %x\n", (kuint)&ioPro.stat.aeawb[0].lineintenb );
		IntErnals_RS_printf("ioPro.stat.aeawb0.lineintflg       = %x\n", (kuint)&ioPro.stat.aeawb[0].lineintflg );
		IntErnals_RS_printf("ioPro.stat.aeawb0.aeawbpaen        = %x\n", (kuint)&ioPro.stat.aeawb[0].aeawbpaen );
		// aeawb-1
		IntErnals_RS_printf("ioPro.stat.aeawb1.aetrg            = %x\n", (kuint)&ioPro.stat.aeawb[1].aetrg );
		IntErnals_RS_printf("ioPro.stat.aeawb1.aeawbctl         = %x\n", (kuint)&ioPro.stat.aeawb[1].aeawbctl );
		IntErnals_RS_printf("ioPro.stat.aeawb1.aev              = %x\n", (kuint)&ioPro.stat.aeawb[1].aev );
		IntErnals_RS_printf("ioPro.stat.aeawb1.aeh              = %x\n", (kuint)&ioPro.stat.aeawb[1].aeh );
		IntErnals_RS_printf("ioPro.stat.aeawb1.aevw             = %x\n", (kuint)&ioPro.stat.aeawb[1].aevw );
		IntErnals_RS_printf("ioPro.stat.aeawb1.aetw             = %x\n", (kuint)&ioPro.stat.aeawb[1].aetw );
		IntErnals_RS_printf("ioPro.stat.aeawb1.aebw             = %x\n", (kuint)&ioPro.stat.aeawb[1].aebw );
		IntErnals_RS_printf("ioPro.stat.aeawb1.aehw             = %x\n", (kuint)&ioPro.stat.aeawb[1].aehw );
		IntErnals_RS_printf("ioPro.stat.aeawb1.aelw             = %x\n", (kuint)&ioPro.stat.aeawb[1].aelw );
		IntErnals_RS_printf("ioPro.stat.aeawb1.aerw             = %x\n", (kuint)&ioPro.stat.aeawb[1].aerw );
		IntErnals_RS_printf("ioPro.stat.aeawb1.aevbc            = %x\n", (kuint)&ioPro.stat.aeawb[1].aevbc );
		IntErnals_RS_printf("ioPro.stat.aeawb1.aehbc            = %x\n", (kuint)&ioPro.stat.aeawb[1].aehbc );
		IntErnals_RS_printf("ioPro.stat.aeawb1.aecw1            = %x\n", (kuint)&ioPro.stat.aeawb[1].aecw1 );
		IntErnals_RS_printf("ioPro.stat.aeawb1.aecw2            = %x\n", (kuint)&ioPro.stat.aeawb[1].aecw2 );
		IntErnals_RS_printf("ioPro.stat.aeawb1.aecw3            = %x\n", (kuint)&ioPro.stat.aeawb[1].aecw3 );
		IntErnals_RS_printf("ioPro.stat.aeawb1.awbcw1           = %x\n", (kuint)&ioPro.stat.aeawb[1].awbcw1 );
		IntErnals_RS_printf("ioPro.stat.aeawb1.awbcw2           = %x\n", (kuint)&ioPro.stat.aeawb[1].awbcw2 );
		IntErnals_RS_printf("ioPro.stat.aeawb1.awbcw3           = %x\n", (kuint)&ioPro.stat.aeawb[1].awbcw3 );
		IntErnals_RS_printf("ioPro.stat.aeawb1.aeykrr           = %x\n", (kuint)&ioPro.stat.aeawb[1].aeykrr );
		IntErnals_RS_printf("ioPro.stat.aeawb1.aeykgr           = %x\n", (kuint)&ioPro.stat.aeawb[1].aeykgr );
		IntErnals_RS_printf("ioPro.stat.aeawb1.aeykgb           = %x\n", (kuint)&ioPro.stat.aeawb[1].aeykgb );
		IntErnals_RS_printf("ioPro.stat.aeawb1.aeykbb           = %x\n", (kuint)&ioPro.stat.aeawb[1].aeykbb );
		IntErnals_RS_printf("ioPro.stat.aeawb1.awtdy            = %x\n", (kuint)&ioPro.stat.aeawb[1].awtdy );
		IntErnals_RS_printf("ioPro.stat.aeawb1.awtdr            = %x\n", (kuint)&ioPro.stat.aeawb[1].awtdr );
		IntErnals_RS_printf("ioPro.stat.aeawb1.awtdg            = %x\n", (kuint)&ioPro.stat.aeawb[1].awtdg );
		IntErnals_RS_printf("ioPro.stat.aeawb1.awtdb            = %x\n", (kuint)&ioPro.stat.aeawb[1].awtdb );
		IntErnals_RS_printf("ioPro.stat.aeawb1.awmlcy           = %x\n", (kuint)&ioPro.stat.aeawb[1].awmlcy );
		IntErnals_RS_printf("ioPro.stat.aeawb1.awmlcb           = %x\n", (kuint)&ioPro.stat.aeawb[1].awmlcb );
		IntErnals_RS_printf("ioPro.stat.aeawb1.awmlcr           = %x\n", (kuint)&ioPro.stat.aeawb[1].awmlcr );
		IntErnals_RS_printf("ioPro.stat.aeawb1.awmc             = %x\n", (kuint)&ioPro.stat.aeawb[1].awmc );
		IntErnals_RS_printf("ioPro.stat.aeawb1.linev            = %x\n", (kuint)&ioPro.stat.aeawb[1].linev );
		IntErnals_RS_printf("ioPro.stat.aeawb1.linedata         = %x\n", (kuint)&ioPro.stat.aeawb[1].linedata );
		IntErnals_RS_printf("ioPro.stat.aeawb1.lineintenb       = %x\n", (kuint)&ioPro.stat.aeawb[1].lineintenb );
		IntErnals_RS_printf("ioPro.stat.aeawb1.lineintflg       = %x\n", (kuint)&ioPro.stat.aeawb[1].lineintflg );
		IntErnals_RS_printf("ioPro.stat.aeawb1.aeawbpaen        = %x\n", (kuint)&ioPro.stat.aeawb[1].aeawbpaen );
		// aeawb-2
		IntErnals_RS_printf("ioPro.stat.aeawb2.aetrg            = %x\n", (kuint)&ioPro.stat.aeawb[2].aetrg );
		IntErnals_RS_printf("ioPro.stat.aeawb2.aeawbctl         = %x\n", (kuint)&ioPro.stat.aeawb[2].aeawbctl );
		IntErnals_RS_printf("ioPro.stat.aeawb2.aev              = %x\n", (kuint)&ioPro.stat.aeawb[2].aev );
		IntErnals_RS_printf("ioPro.stat.aeawb2.aeh              = %x\n", (kuint)&ioPro.stat.aeawb[2].aeh );
		IntErnals_RS_printf("ioPro.stat.aeawb2.aevw             = %x\n", (kuint)&ioPro.stat.aeawb[2].aevw );
		IntErnals_RS_printf("ioPro.stat.aeawb2.aetw             = %x\n", (kuint)&ioPro.stat.aeawb[2].aetw );
		IntErnals_RS_printf("ioPro.stat.aeawb2.aebw             = %x\n", (kuint)&ioPro.stat.aeawb[2].aebw );
		IntErnals_RS_printf("ioPro.stat.aeawb2.aehw             = %x\n", (kuint)&ioPro.stat.aeawb[2].aehw );
		IntErnals_RS_printf("ioPro.stat.aeawb2.aelw             = %x\n", (kuint)&ioPro.stat.aeawb[2].aelw );
		IntErnals_RS_printf("ioPro.stat.aeawb2.aerw             = %x\n", (kuint)&ioPro.stat.aeawb[2].aerw );
		IntErnals_RS_printf("ioPro.stat.aeawb2.aevbc            = %x\n", (kuint)&ioPro.stat.aeawb[2].aevbc );
		IntErnals_RS_printf("ioPro.stat.aeawb2.aehbc            = %x\n", (kuint)&ioPro.stat.aeawb[2].aehbc );
		IntErnals_RS_printf("ioPro.stat.aeawb2.aecw1            = %x\n", (kuint)&ioPro.stat.aeawb[2].aecw1 );
		IntErnals_RS_printf("ioPro.stat.aeawb2.aecw2            = %x\n", (kuint)&ioPro.stat.aeawb[2].aecw2 );
		IntErnals_RS_printf("ioPro.stat.aeawb2.aecw3            = %x\n", (kuint)&ioPro.stat.aeawb[2].aecw3 );
		IntErnals_RS_printf("ioPro.stat.aeawb2.awbcw1           = %x\n", (kuint)&ioPro.stat.aeawb[2].awbcw1 );
		IntErnals_RS_printf("ioPro.stat.aeawb2.awbcw2           = %x\n", (kuint)&ioPro.stat.aeawb[2].awbcw2 );
		IntErnals_RS_printf("ioPro.stat.aeawb2.awbcw3           = %x\n", (kuint)&ioPro.stat.aeawb[2].awbcw3 );
		IntErnals_RS_printf("ioPro.stat.aeawb2.aeykrr           = %x\n", (kuint)&ioPro.stat.aeawb[2].aeykrr );
		IntErnals_RS_printf("ioPro.stat.aeawb2.aeykgr           = %x\n", (kuint)&ioPro.stat.aeawb[2].aeykgr );
		IntErnals_RS_printf("ioPro.stat.aeawb2.aeykgb           = %x\n", (kuint)&ioPro.stat.aeawb[2].aeykgb );
		IntErnals_RS_printf("ioPro.stat.aeawb2.aeykbb           = %x\n", (kuint)&ioPro.stat.aeawb[2].aeykbb );
		IntErnals_RS_printf("ioPro.stat.aeawb2.awtdy            = %x\n", (kuint)&ioPro.stat.aeawb[2].awtdy );
		IntErnals_RS_printf("ioPro.stat.aeawb2.awtdr            = %x\n", (kuint)&ioPro.stat.aeawb[2].awtdr );
		IntErnals_RS_printf("ioPro.stat.aeawb2.awtdg            = %x\n", (kuint)&ioPro.stat.aeawb[2].awtdg );
		IntErnals_RS_printf("ioPro.stat.aeawb2.awtdb            = %x\n", (kuint)&ioPro.stat.aeawb[2].awtdb );
		IntErnals_RS_printf("ioPro.stat.aeawb2.awmlcy           = %x\n", (kuint)&ioPro.stat.aeawb[2].awmlcy );
		IntErnals_RS_printf("ioPro.stat.aeawb2.awmlcb           = %x\n", (kuint)&ioPro.stat.aeawb[2].awmlcb );
		IntErnals_RS_printf("ioPro.stat.aeawb2.awmlcr           = %x\n", (kuint)&ioPro.stat.aeawb[2].awmlcr );
		IntErnals_RS_printf("ioPro.stat.aeawb2.awmc             = %x\n", (kuint)&ioPro.stat.aeawb[2].awmc );
		IntErnals_RS_printf("ioPro.stat.aeawb2.linev            = %x\n", (kuint)&ioPro.stat.aeawb[2].linev );
		IntErnals_RS_printf("ioPro.stat.aeawb2.linedata         = %x\n", (kuint)&ioPro.stat.aeawb[2].linedata );
		IntErnals_RS_printf("ioPro.stat.aeawb2.lineintenb       = %x\n", (kuint)&ioPro.stat.aeawb[2].lineintenb );
		IntErnals_RS_printf("ioPro.stat.aeawb2.lineintflg       = %x\n", (kuint)&ioPro.stat.aeawb[2].lineintflg );
		IntErnals_RS_printf("ioPro.stat.aeawb2.aeawbpaen        = %x\n", (kuint)&ioPro.stat.aeawb[2].aeawbpaen );
		// aeawb-3
		IntErnals_RS_printf("ioPro.stat.aeawb3.aetrg            = %x\n", (kuint)&ioPro.stat.aeawb[3].aetrg );
		IntErnals_RS_printf("ioPro.stat.aeawb3.aeawbctl         = %x\n", (kuint)&ioPro.stat.aeawb[3].aeawbctl );
		IntErnals_RS_printf("ioPro.stat.aeawb3.aev              = %x\n", (kuint)&ioPro.stat.aeawb[3].aev );
		IntErnals_RS_printf("ioPro.stat.aeawb3.aeh              = %x\n", (kuint)&ioPro.stat.aeawb[3].aeh );
		IntErnals_RS_printf("ioPro.stat.aeawb3.aevw             = %x\n", (kuint)&ioPro.stat.aeawb[3].aevw );
		IntErnals_RS_printf("ioPro.stat.aeawb3.aetw             = %x\n", (kuint)&ioPro.stat.aeawb[3].aetw );
		IntErnals_RS_printf("ioPro.stat.aeawb3.aebw             = %x\n", (kuint)&ioPro.stat.aeawb[3].aebw );
		IntErnals_RS_printf("ioPro.stat.aeawb3.aehw             = %x\n", (kuint)&ioPro.stat.aeawb[3].aehw );
		IntErnals_RS_printf("ioPro.stat.aeawb3.aelw             = %x\n", (kuint)&ioPro.stat.aeawb[3].aelw );
		IntErnals_RS_printf("ioPro.stat.aeawb3.aerw             = %x\n", (kuint)&ioPro.stat.aeawb[3].aerw );
		IntErnals_RS_printf("ioPro.stat.aeawb3.aevbc            = %x\n", (kuint)&ioPro.stat.aeawb[3].aevbc );
		IntErnals_RS_printf("ioPro.stat.aeawb3.aehbc            = %x\n", (kuint)&ioPro.stat.aeawb[3].aehbc );
		IntErnals_RS_printf("ioPro.stat.aeawb3.aecw1            = %x\n", (kuint)&ioPro.stat.aeawb[3].aecw1 );
		IntErnals_RS_printf("ioPro.stat.aeawb3.aecw2            = %x\n", (kuint)&ioPro.stat.aeawb[3].aecw2 );
		IntErnals_RS_printf("ioPro.stat.aeawb3.aecw3            = %x\n", (kuint)&ioPro.stat.aeawb[3].aecw3 );
		IntErnals_RS_printf("ioPro.stat.aeawb3.awbcw1           = %x\n", (kuint)&ioPro.stat.aeawb[3].awbcw1 );
		IntErnals_RS_printf("ioPro.stat.aeawb3.awbcw2           = %x\n", (kuint)&ioPro.stat.aeawb[3].awbcw2 );
		IntErnals_RS_printf("ioPro.stat.aeawb3.awbcw3           = %x\n", (kuint)&ioPro.stat.aeawb[3].awbcw3 );
		IntErnals_RS_printf("ioPro.stat.aeawb3.aeykrr           = %x\n", (kuint)&ioPro.stat.aeawb[3].aeykrr );
		IntErnals_RS_printf("ioPro.stat.aeawb3.aeykgr           = %x\n", (kuint)&ioPro.stat.aeawb[3].aeykgr );
		IntErnals_RS_printf("ioPro.stat.aeawb3.aeykgb           = %x\n", (kuint)&ioPro.stat.aeawb[3].aeykgb );
		IntErnals_RS_printf("ioPro.stat.aeawb3.aeykbb           = %x\n", (kuint)&ioPro.stat.aeawb[3].aeykbb );
		IntErnals_RS_printf("ioPro.stat.aeawb3.awtdy            = %x\n", (kuint)&ioPro.stat.aeawb[3].awtdy );
		IntErnals_RS_printf("ioPro.stat.aeawb3.awtdr            = %x\n", (kuint)&ioPro.stat.aeawb[3].awtdr );
		IntErnals_RS_printf("ioPro.stat.aeawb3.awtdg            = %x\n", (kuint)&ioPro.stat.aeawb[3].awtdg );
		IntErnals_RS_printf("ioPro.stat.aeawb3.awtdb            = %x\n", (kuint)&ioPro.stat.aeawb[3].awtdb );
		IntErnals_RS_printf("ioPro.stat.aeawb3.awmlcy           = %x\n", (kuint)&ioPro.stat.aeawb[3].awmlcy );
		IntErnals_RS_printf("ioPro.stat.aeawb3.awmlcb           = %x\n", (kuint)&ioPro.stat.aeawb[3].awmlcb );
		IntErnals_RS_printf("ioPro.stat.aeawb3.awmlcr           = %x\n", (kuint)&ioPro.stat.aeawb[3].awmlcr );
		IntErnals_RS_printf("ioPro.stat.aeawb3.awmc             = %x\n", (kuint)&ioPro.stat.aeawb[3].awmc );
		IntErnals_RS_printf("ioPro.stat.aeawb3.linev            = %x\n", (kuint)&ioPro.stat.aeawb[3].linev );
		IntErnals_RS_printf("ioPro.stat.aeawb3.linedata         = %x\n", (kuint)&ioPro.stat.aeawb[3].linedata );
		IntErnals_RS_printf("ioPro.stat.aeawb3.lineintenb       = %x\n", (kuint)&ioPro.stat.aeawb[3].lineintenb );
		IntErnals_RS_printf("ioPro.stat.aeawb3.lineintflg       = %x\n", (kuint)&ioPro.stat.aeawb[3].lineintflg );
		IntErnals_RS_printf("ioPro.stat.aeawb3.aeawbpaen        = %x\n", (kuint)&ioPro.stat.aeawb[3].aeawbpaen );
		// flck-0
		IntErnals_RS_printf("ioPro.stat.flck0.fltrg             = %x\n", (kuint)&ioPro.stat.flck[0].fltrg );
		IntErnals_RS_printf("ioPro.stat.flck0.flckctl           = %x\n", (kuint)&ioPro.stat.flck[0].flckctl );
		IntErnals_RS_printf("ioPro.stat.flck0.flv               = %x\n", (kuint)&ioPro.stat.flck[0].flv );
		IntErnals_RS_printf("ioPro.stat.flck0.flh               = %x\n", (kuint)&ioPro.stat.flck[0].flh );
		IntErnals_RS_printf("ioPro.stat.flck0.flvw              = %x\n", (kuint)&ioPro.stat.flck[0].flvw );
		IntErnals_RS_printf("ioPro.stat.flck0.flhw              = %x\n", (kuint)&ioPro.stat.flck[0].flhw );
		IntErnals_RS_printf("ioPro.stat.flck0.flbc              = %x\n", (kuint)&ioPro.stat.flck[0].flbc );
		IntErnals_RS_printf("ioPro.stat.flck0.flykrr            = %x\n", (kuint)&ioPro.stat.flck[0].flykrr );
		IntErnals_RS_printf("ioPro.stat.flck0.flykgr            = %x\n", (kuint)&ioPro.stat.flck[0].flykgr );
		IntErnals_RS_printf("ioPro.stat.flck0.flykgb            = %x\n", (kuint)&ioPro.stat.flck[0].flykgb );
		IntErnals_RS_printf("ioPro.stat.flck0.flykbb            = %x\n", (kuint)&ioPro.stat.flck[0].flykbb );
		IntErnals_RS_printf("ioPro.stat.flck0.fltdy             = %x\n", (kuint)&ioPro.stat.flck[0].fltdy );
		IntErnals_RS_printf("ioPro.stat.flck0.fltdr             = %x\n", (kuint)&ioPro.stat.flck[0].fltdr );
		IntErnals_RS_printf("ioPro.stat.flck0.fltdg             = %x\n", (kuint)&ioPro.stat.flck[0].fltdg );
		IntErnals_RS_printf("ioPro.stat.flck0.fltdb             = %x\n", (kuint)&ioPro.stat.flck[0].fltdb );
		IntErnals_RS_printf("ioPro.stat.flck0.flmlcy            = %x\n", (kuint)&ioPro.stat.flck[0].flmlcy );
		IntErnals_RS_printf("ioPro.stat.flck0.flmlcb            = %x\n", (kuint)&ioPro.stat.flck[0].flmlcb );
		IntErnals_RS_printf("ioPro.stat.flck0.flmlcr            = %x\n", (kuint)&ioPro.stat.flck[0].flmlcr );
		IntErnals_RS_printf("ioPro.stat.flck0.flmc              = %x\n", (kuint)&ioPro.stat.flck[0].flmc );
		// flck-1
		IntErnals_RS_printf("ioPro.stat.flck1.fltrg             = %x\n", (kuint)&ioPro.stat.flck[1].fltrg );
		IntErnals_RS_printf("ioPro.stat.flck1.flckctl           = %x\n", (kuint)&ioPro.stat.flck[1].flckctl );
		IntErnals_RS_printf("ioPro.stat.flck1.flv               = %x\n", (kuint)&ioPro.stat.flck[1].flv );
		IntErnals_RS_printf("ioPro.stat.flck1.flh               = %x\n", (kuint)&ioPro.stat.flck[1].flh );
		IntErnals_RS_printf("ioPro.stat.flck1.flvw              = %x\n", (kuint)&ioPro.stat.flck[1].flvw );
		IntErnals_RS_printf("ioPro.stat.flck1.flhw              = %x\n", (kuint)&ioPro.stat.flck[1].flhw );
		IntErnals_RS_printf("ioPro.stat.flck1.flbc              = %x\n", (kuint)&ioPro.stat.flck[1].flbc );
		IntErnals_RS_printf("ioPro.stat.flck1.flykrr            = %x\n", (kuint)&ioPro.stat.flck[1].flykrr );
		IntErnals_RS_printf("ioPro.stat.flck1.flykgr            = %x\n", (kuint)&ioPro.stat.flck[1].flykgr );
		IntErnals_RS_printf("ioPro.stat.flck1.flykgb            = %x\n", (kuint)&ioPro.stat.flck[1].flykgb );
		IntErnals_RS_printf("ioPro.stat.flck1.flykbb            = %x\n", (kuint)&ioPro.stat.flck[1].flykbb );
		IntErnals_RS_printf("ioPro.stat.flck1.fltdy             = %x\n", (kuint)&ioPro.stat.flck[1].fltdy );
		IntErnals_RS_printf("ioPro.stat.flck1.fltdr             = %x\n", (kuint)&ioPro.stat.flck[1].fltdr );
		IntErnals_RS_printf("ioPro.stat.flck1.fltdg             = %x\n", (kuint)&ioPro.stat.flck[1].fltdg );
		IntErnals_RS_printf("ioPro.stat.flck1.fltdb             = %x\n", (kuint)&ioPro.stat.flck[1].fltdb );
		IntErnals_RS_printf("ioPro.stat.flck1.flmlcy            = %x\n", (kuint)&ioPro.stat.flck[1].flmlcy );
		IntErnals_RS_printf("ioPro.stat.flck1.flmlcb            = %x\n", (kuint)&ioPro.stat.flck[1].flmlcb );
		IntErnals_RS_printf("ioPro.stat.flck1.flmlcr            = %x\n", (kuint)&ioPro.stat.flck[1].flmlcr );
		IntErnals_RS_printf("ioPro.stat.flck1.flmc              = %x\n", (kuint)&ioPro.stat.flck[1].flmc );
		// hist-0
		IntErnals_RS_printf("ioPro.stat.hist0.histtrg           = %x\n", (kuint)&ioPro.stat.hist[0].histtrg );
		IntErnals_RS_printf("ioPro.stat.hist0.histintenb        = %x\n", (kuint)&ioPro.stat.hist[0].histintenb );
		IntErnals_RS_printf("ioPro.stat.hist0.histintflg        = %x\n", (kuint)&ioPro.stat.hist[0].histintflg );
		IntErnals_RS_printf("ioPro.stat.hist0.histctl           = %x\n", (kuint)&ioPro.stat.hist[0].histctl );
		IntErnals_RS_printf("ioPro.stat.hist0.histv             = %x\n", (kuint)&ioPro.stat.hist[0].histv );
		IntErnals_RS_printf("ioPro.stat.hist0.histh             = %x\n", (kuint)&ioPro.stat.hist[0].histh );
		IntErnals_RS_printf("ioPro.stat.hist0.histvw            = %x\n", (kuint)&ioPro.stat.hist[0].histvw );
		IntErnals_RS_printf("ioPro.stat.hist0.histhw            = %x\n", (kuint)&ioPro.stat.hist[0].histhw );
		IntErnals_RS_printf("ioPro.stat.hist0.histykrr          = %x\n", (kuint)&ioPro.stat.hist[0].histykrr );
		IntErnals_RS_printf("ioPro.stat.hist0.histykgr          = %x\n", (kuint)&ioPro.stat.hist[0].histykgr );
		IntErnals_RS_printf("ioPro.stat.hist0.histykgb          = %x\n", (kuint)&ioPro.stat.hist[0].histykgb );
		IntErnals_RS_printf("ioPro.stat.hist0.histykbb          = %x\n", (kuint)&ioPro.stat.hist[0].histykbb );
		IntErnals_RS_printf("ioPro.stat.hist0.histrmode         = %x\n", (kuint)&ioPro.stat.hist[0].histrmode );
		IntErnals_RS_printf("ioPro.stat.hist0.histgmode         = %x\n", (kuint)&ioPro.stat.hist[0].histgmode );
		IntErnals_RS_printf("ioPro.stat.hist0.histbmode         = %x\n", (kuint)&ioPro.stat.hist[0].histbmode );
		IntErnals_RS_printf("ioPro.stat.hist0.histymode         = %x\n", (kuint)&ioPro.stat.hist[0].histymode );
		IntErnals_RS_printf("ioPro.stat.hist0.histrsum          = %x\n", (kuint)&ioPro.stat.hist[0].histrsum );
		IntErnals_RS_printf("ioPro.stat.hist0.histgsum          = %x\n", (kuint)&ioPro.stat.hist[0].histgsum );
		IntErnals_RS_printf("ioPro.stat.hist0.histbsum          = %x\n", (kuint)&ioPro.stat.hist[0].histbsum );
		IntErnals_RS_printf("ioPro.stat.hist0.histysum          = %x\n", (kuint)&ioPro.stat.hist[0].histysum );
		IntErnals_RS_printf("ioPro.stat.hist0.histwbgr          = %x\n", (kuint)&ioPro.stat.hist[0].histwbgr );
		IntErnals_RS_printf("ioPro.stat.hist0.histwbgg          = %x\n", (kuint)&ioPro.stat.hist[0].histwbgg );
		IntErnals_RS_printf("ioPro.stat.hist0.histwbgb          = %x\n", (kuint)&ioPro.stat.hist[0].histwbgb );
		IntErnals_RS_printf("ioPro.stat.hist0.histpaen          = %x\n", (kuint)&ioPro.stat.hist[0].histpaen );
		// hist-1
		IntErnals_RS_printf("ioPro.stat.hist1.histtrg           = %x\n", (kuint)&ioPro.stat.hist[1].histtrg );
		IntErnals_RS_printf("ioPro.stat.hist1.histintenb        = %x\n", (kuint)&ioPro.stat.hist[1].histintenb );
		IntErnals_RS_printf("ioPro.stat.hist1.histintflg        = %x\n", (kuint)&ioPro.stat.hist[1].histintflg );
		IntErnals_RS_printf("ioPro.stat.hist1.histctl           = %x\n", (kuint)&ioPro.stat.hist[1].histctl );
		IntErnals_RS_printf("ioPro.stat.hist1.histv             = %x\n", (kuint)&ioPro.stat.hist[1].histv );
		IntErnals_RS_printf("ioPro.stat.hist1.histh             = %x\n", (kuint)&ioPro.stat.hist[1].histh );
		IntErnals_RS_printf("ioPro.stat.hist1.histvw            = %x\n", (kuint)&ioPro.stat.hist[1].histvw );
		IntErnals_RS_printf("ioPro.stat.hist1.histhw            = %x\n", (kuint)&ioPro.stat.hist[1].histhw );
		IntErnals_RS_printf("ioPro.stat.hist1.histykrr          = %x\n", (kuint)&ioPro.stat.hist[1].histykrr );
		IntErnals_RS_printf("ioPro.stat.hist1.histykgr          = %x\n", (kuint)&ioPro.stat.hist[1].histykgr );
		IntErnals_RS_printf("ioPro.stat.hist1.histykgb          = %x\n", (kuint)&ioPro.stat.hist[1].histykgb );
		IntErnals_RS_printf("ioPro.stat.hist1.histykbb          = %x\n", (kuint)&ioPro.stat.hist[1].histykbb );
		IntErnals_RS_printf("ioPro.stat.hist1.histrmode         = %x\n", (kuint)&ioPro.stat.hist[1].histrmode );
		IntErnals_RS_printf("ioPro.stat.hist1.histgmode         = %x\n", (kuint)&ioPro.stat.hist[1].histgmode );
		IntErnals_RS_printf("ioPro.stat.hist1.histbmode         = %x\n", (kuint)&ioPro.stat.hist[1].histbmode );
		IntErnals_RS_printf("ioPro.stat.hist1.histymode         = %x\n", (kuint)&ioPro.stat.hist[1].histymode );
		IntErnals_RS_printf("ioPro.stat.hist1.histrsum          = %x\n", (kuint)&ioPro.stat.hist[1].histrsum );
		IntErnals_RS_printf("ioPro.stat.hist1.histgsum          = %x\n", (kuint)&ioPro.stat.hist[1].histgsum );
		IntErnals_RS_printf("ioPro.stat.hist1.histbsum          = %x\n", (kuint)&ioPro.stat.hist[1].histbsum );
		IntErnals_RS_printf("ioPro.stat.hist1.histysum          = %x\n", (kuint)&ioPro.stat.hist[1].histysum );
		IntErnals_RS_printf("ioPro.stat.hist1.histwbgr          = %x\n", (kuint)&ioPro.stat.hist[1].histwbgr );
		IntErnals_RS_printf("ioPro.stat.hist1.histwbgg          = %x\n", (kuint)&ioPro.stat.hist[1].histwbgg );
		IntErnals_RS_printf("ioPro.stat.hist1.histwbgb          = %x\n", (kuint)&ioPro.stat.hist[1].histwbgb );
		IntErnals_RS_printf("ioPro.stat.hist1.histpaen          = %x\n", (kuint)&ioPro.stat.hist[1].histpaen );
		// hist-2
		IntErnals_RS_printf("ioPro.stat.hist2.histtrg           = %x\n", (kuint)&ioPro.stat.hist[2].histtrg );
		IntErnals_RS_printf("ioPro.stat.hist2.histintenb        = %x\n", (kuint)&ioPro.stat.hist[2].histintenb );
		IntErnals_RS_printf("ioPro.stat.hist2.histintflg        = %x\n", (kuint)&ioPro.stat.hist[2].histintflg );
		IntErnals_RS_printf("ioPro.stat.hist2.histctl           = %x\n", (kuint)&ioPro.stat.hist[2].histctl );
		IntErnals_RS_printf("ioPro.stat.hist2.histv             = %x\n", (kuint)&ioPro.stat.hist[2].histv );
		IntErnals_RS_printf("ioPro.stat.hist2.histh             = %x\n", (kuint)&ioPro.stat.hist[2].histh );
		IntErnals_RS_printf("ioPro.stat.hist2.histvw            = %x\n", (kuint)&ioPro.stat.hist[2].histvw );
		IntErnals_RS_printf("ioPro.stat.hist2.histhw            = %x\n", (kuint)&ioPro.stat.hist[2].histhw );
		IntErnals_RS_printf("ioPro.stat.hist2.histykrr          = %x\n", (kuint)&ioPro.stat.hist[2].histykrr );
		IntErnals_RS_printf("ioPro.stat.hist2.histykgr          = %x\n", (kuint)&ioPro.stat.hist[2].histykgr );
		IntErnals_RS_printf("ioPro.stat.hist2.histykgb          = %x\n", (kuint)&ioPro.stat.hist[2].histykgb );
		IntErnals_RS_printf("ioPro.stat.hist2.histykbb          = %x\n", (kuint)&ioPro.stat.hist[2].histykbb );
		IntErnals_RS_printf("ioPro.stat.hist2.histrmode         = %x\n", (kuint)&ioPro.stat.hist[2].histrmode );
		IntErnals_RS_printf("ioPro.stat.hist2.histgmode         = %x\n", (kuint)&ioPro.stat.hist[2].histgmode );
		IntErnals_RS_printf("ioPro.stat.hist2.histbmode         = %x\n", (kuint)&ioPro.stat.hist[2].histbmode );
		IntErnals_RS_printf("ioPro.stat.hist2.histymode         = %x\n", (kuint)&ioPro.stat.hist[2].histymode );
		IntErnals_RS_printf("ioPro.stat.hist2.histrsum          = %x\n", (kuint)&ioPro.stat.hist[2].histrsum );
		IntErnals_RS_printf("ioPro.stat.hist2.histgsum          = %x\n", (kuint)&ioPro.stat.hist[2].histgsum );
		IntErnals_RS_printf("ioPro.stat.hist2.histbsum          = %x\n", (kuint)&ioPro.stat.hist[2].histbsum );
		IntErnals_RS_printf("ioPro.stat.hist2.histysum          = %x\n", (kuint)&ioPro.stat.hist[2].histysum );
		IntErnals_RS_printf("ioPro.stat.hist2.histwbgr          = %x\n", (kuint)&ioPro.stat.hist[2].histwbgr );
		IntErnals_RS_printf("ioPro.stat.hist2.histwbgg          = %x\n", (kuint)&ioPro.stat.hist[2].histwbgg );
		IntErnals_RS_printf("ioPro.stat.hist2.histwbgb          = %x\n", (kuint)&ioPro.stat.hist[2].histwbgb );
		IntErnals_RS_printf("ioPro.stat.hist2.histpaen          = %x\n", (kuint)&ioPro.stat.hist[2].histpaen );
		// hist-3
		IntErnals_RS_printf("ioPro.stat.hist3.histtrg           = %x\n", (kuint)&ioPro.stat.hist[3].histtrg );
		IntErnals_RS_printf("ioPro.stat.hist3.histintenb        = %x\n", (kuint)&ioPro.stat.hist[3].histintenb );
		IntErnals_RS_printf("ioPro.stat.hist3.histintflg        = %x\n", (kuint)&ioPro.stat.hist[3].histintflg );
		IntErnals_RS_printf("ioPro.stat.hist3.histctl           = %x\n", (kuint)&ioPro.stat.hist[3].histctl );
		IntErnals_RS_printf("ioPro.stat.hist3.histv             = %x\n", (kuint)&ioPro.stat.hist[3].histv );
		IntErnals_RS_printf("ioPro.stat.hist3.histh             = %x\n", (kuint)&ioPro.stat.hist[3].histh );
		IntErnals_RS_printf("ioPro.stat.hist3.histvw            = %x\n", (kuint)&ioPro.stat.hist[3].histvw );
		IntErnals_RS_printf("ioPro.stat.hist3.histhw            = %x\n", (kuint)&ioPro.stat.hist[3].histhw );
		IntErnals_RS_printf("ioPro.stat.hist3.histykrr          = %x\n", (kuint)&ioPro.stat.hist[3].histykrr );
		IntErnals_RS_printf("ioPro.stat.hist3.histykgr          = %x\n", (kuint)&ioPro.stat.hist[3].histykgr );
		IntErnals_RS_printf("ioPro.stat.hist3.histykgb          = %x\n", (kuint)&ioPro.stat.hist[3].histykgb );
		IntErnals_RS_printf("ioPro.stat.hist3.histykbb          = %x\n", (kuint)&ioPro.stat.hist[3].histykbb );
		IntErnals_RS_printf("ioPro.stat.hist3.histrmode         = %x\n", (kuint)&ioPro.stat.hist[3].histrmode );
		IntErnals_RS_printf("ioPro.stat.hist3.histgmode         = %x\n", (kuint)&ioPro.stat.hist[3].histgmode );
		IntErnals_RS_printf("ioPro.stat.hist3.histbmode         = %x\n", (kuint)&ioPro.stat.hist[3].histbmode );
		IntErnals_RS_printf("ioPro.stat.hist3.histymode         = %x\n", (kuint)&ioPro.stat.hist[3].histymode );
		IntErnals_RS_printf("ioPro.stat.hist3.histrsum          = %x\n", (kuint)&ioPro.stat.hist[3].histrsum );
		IntErnals_RS_printf("ioPro.stat.hist3.histgsum          = %x\n", (kuint)&ioPro.stat.hist[3].histgsum );
		IntErnals_RS_printf("ioPro.stat.hist3.histbsum          = %x\n", (kuint)&ioPro.stat.hist[3].histbsum );
		IntErnals_RS_printf("ioPro.stat.hist3.histysum          = %x\n", (kuint)&ioPro.stat.hist[3].histysum );
		IntErnals_RS_printf("ioPro.stat.hist3.histwbgr          = %x\n", (kuint)&ioPro.stat.hist[3].histwbgr );
		IntErnals_RS_printf("ioPro.stat.hist3.histwbgg          = %x\n", (kuint)&ioPro.stat.hist[3].histwbgg );
		IntErnals_RS_printf("ioPro.stat.hist3.histwbgb          = %x\n", (kuint)&ioPro.stat.hist[3].histwbgb );
		IntErnals_RS_printf("ioPro.stat.hist3.histpaen          = %x\n", (kuint)&ioPro.stat.hist[3].histpaen );
		// pwch-0
		IntErnals_RS_printf("ioPro.stat.pwch0.pwchtrg           = %x\n", (kuint)&ioPro.stat.pwch[0].pwchtrg );
		IntErnals_RS_printf("ioPro.stat.pwch0.pws               = %x\n", (kuint)&ioPro.stat.pwch[0].pws );
		IntErnals_RS_printf("ioPro.stat.pwch0.pwaxctl           = %x\n", (kuint)&ioPro.stat.pwch[0].pwaxctl );
		IntErnals_RS_printf("ioPro.stat.pwch0.pwchctl           = %x\n", (kuint)&ioPro.stat.pwch[0].pwchctl );
		IntErnals_RS_printf("ioPro.stat.pwch0.pwchintenb        = %x\n", (kuint)&ioPro.stat.pwch[0].pwchintenb );
		IntErnals_RS_printf("ioPro.stat.pwch0.pwchintflg        = %x\n", (kuint)&ioPro.stat.pwch[0].pwchintflg );
		IntErnals_RS_printf("ioPro.stat.pwch0.pwchbresp         = %x\n", (kuint)&ioPro.stat.pwch[0].pwchbresp );
		IntErnals_RS_printf("ioPro.stat.pwch0.pwsa              = %x\n", (kuint)&ioPro.stat.pwch[0].pwsa );
		IntErnals_RS_printf("ioPro.stat.pwch0.pwlsize           = %x\n", (kuint)&ioPro.stat.pwch[0].pwlsize );
		// pwch-1
		IntErnals_RS_printf("ioPro.stat.pwch1.pwchtrg           = %x\n", (kuint)&ioPro.stat.pwch[1].pwchtrg );
		IntErnals_RS_printf("ioPro.stat.pwch1.pws               = %x\n", (kuint)&ioPro.stat.pwch[1].pws );
		IntErnals_RS_printf("ioPro.stat.pwch1.pwaxctl           = %x\n", (kuint)&ioPro.stat.pwch[1].pwaxctl );
		IntErnals_RS_printf("ioPro.stat.pwch1.pwchctl           = %x\n", (kuint)&ioPro.stat.pwch[1].pwchctl );
		IntErnals_RS_printf("ioPro.stat.pwch1.pwchintenb        = %x\n", (kuint)&ioPro.stat.pwch[1].pwchintenb );
		IntErnals_RS_printf("ioPro.stat.pwch1.pwchintflg        = %x\n", (kuint)&ioPro.stat.pwch[1].pwchintflg );
		IntErnals_RS_printf("ioPro.stat.pwch1.pwchbresp         = %x\n", (kuint)&ioPro.stat.pwch[1].pwchbresp );
		IntErnals_RS_printf("ioPro.stat.pwch1.pwsa              = %x\n", (kuint)&ioPro.stat.pwch[1].pwsa );
		IntErnals_RS_printf("ioPro.stat.pwch1.pwlsize           = %x\n", (kuint)&ioPro.stat.pwch[1].pwlsize );
		// pwch-2
		IntErnals_RS_printf("ioPro.stat.pwch2.pwchtrg           = %x\n", (kuint)&ioPro.stat.pwch[2].pwchtrg );
		IntErnals_RS_printf("ioPro.stat.pwch2.pws               = %x\n", (kuint)&ioPro.stat.pwch[2].pws );
		IntErnals_RS_printf("ioPro.stat.pwch2.pwaxctl           = %x\n", (kuint)&ioPro.stat.pwch[2].pwaxctl );
		IntErnals_RS_printf("ioPro.stat.pwch2.pwchctl           = %x\n", (kuint)&ioPro.stat.pwch[2].pwchctl );
		IntErnals_RS_printf("ioPro.stat.pwch2.pwchintenb        = %x\n", (kuint)&ioPro.stat.pwch[2].pwchintenb );
		IntErnals_RS_printf("ioPro.stat.pwch2.pwchintflg        = %x\n", (kuint)&ioPro.stat.pwch[2].pwchintflg );
		IntErnals_RS_printf("ioPro.stat.pwch2.pwchbresp         = %x\n", (kuint)&ioPro.stat.pwch[2].pwchbresp );
		IntErnals_RS_printf("ioPro.stat.pwch2.pwsa              = %x\n", (kuint)&ioPro.stat.pwch[2].pwsa );
		IntErnals_RS_printf("ioPro.stat.pwch2.pwlsize           = %x\n", (kuint)&ioPro.stat.pwch[2].pwlsize );
		// pwch-3
		IntErnals_RS_printf("ioPro.stat.pwch3.pwchtrg           = %x\n", (kuint)&ioPro.stat.pwch[3].pwchtrg );
		IntErnals_RS_printf("ioPro.stat.pwch3.pws               = %x\n", (kuint)&ioPro.stat.pwch[3].pws );
		IntErnals_RS_printf("ioPro.stat.pwch3.pwaxctl           = %x\n", (kuint)&ioPro.stat.pwch[3].pwaxctl );
		IntErnals_RS_printf("ioPro.stat.pwch3.pwchctl           = %x\n", (kuint)&ioPro.stat.pwch[3].pwchctl );
		IntErnals_RS_printf("ioPro.stat.pwch3.pwchintenb        = %x\n", (kuint)&ioPro.stat.pwch[3].pwchintenb );
		IntErnals_RS_printf("ioPro.stat.pwch3.pwchintflg        = %x\n", (kuint)&ioPro.stat.pwch[3].pwchintflg );
		IntErnals_RS_printf("ioPro.stat.pwch3.pwchbresp         = %x\n", (kuint)&ioPro.stat.pwch[3].pwchbresp );
		IntErnals_RS_printf("ioPro.stat.pwch3.pwsa              = %x\n", (kuint)&ioPro.stat.pwch[3].pwsa );
		IntErnals_RS_printf("ioPro.stat.pwch3.pwlsize           = %x\n", (kuint)&ioPro.stat.pwch[3].pwlsize );
		// pwch-4
		IntErnals_RS_printf("ioPro.stat.pwch4.pwchtrg           = %x\n", (kuint)&ioPro.stat.pwch[4].pwchtrg );
		IntErnals_RS_printf("ioPro.stat.pwch4.pws               = %x\n", (kuint)&ioPro.stat.pwch[4].pws );
		IntErnals_RS_printf("ioPro.stat.pwch4.pwaxctl           = %x\n", (kuint)&ioPro.stat.pwch[4].pwaxctl );
		IntErnals_RS_printf("ioPro.stat.pwch4.pwchctl           = %x\n", (kuint)&ioPro.stat.pwch[4].pwchctl );
		IntErnals_RS_printf("ioPro.stat.pwch4.pwchintenb        = %x\n", (kuint)&ioPro.stat.pwch[4].pwchintenb );
		IntErnals_RS_printf("ioPro.stat.pwch4.pwchintflg        = %x\n", (kuint)&ioPro.stat.pwch[4].pwchintflg );
		IntErnals_RS_printf("ioPro.stat.pwch4.pwchbresp         = %x\n", (kuint)&ioPro.stat.pwch[4].pwchbresp );
		IntErnals_RS_printf("ioPro.stat.pwch4.pwsa              = %x\n", (kuint)&ioPro.stat.pwch[4].pwsa );
		IntErnals_RS_printf("ioPro.stat.pwch4.pwlsize           = %x\n", (kuint)&ioPro.stat.pwch[4].pwlsize );
		// pwch-5
		IntErnals_RS_printf("ioPro.stat.pwch5.pwchtrg           = %x\n", (kuint)&ioPro.stat.pwch[5].pwchtrg );
		IntErnals_RS_printf("ioPro.stat.pwch5.pws               = %x\n", (kuint)&ioPro.stat.pwch[5].pws );
		IntErnals_RS_printf("ioPro.stat.pwch5.pwaxctl           = %x\n", (kuint)&ioPro.stat.pwch[5].pwaxctl );
		IntErnals_RS_printf("ioPro.stat.pwch5.pwchctl           = %x\n", (kuint)&ioPro.stat.pwch[5].pwchctl );
		IntErnals_RS_printf("ioPro.stat.pwch5.pwchintenb        = %x\n", (kuint)&ioPro.stat.pwch[5].pwchintenb );
		IntErnals_RS_printf("ioPro.stat.pwch5.pwchintflg        = %x\n", (kuint)&ioPro.stat.pwch[5].pwchintflg );
		IntErnals_RS_printf("ioPro.stat.pwch5.pwchbresp         = %x\n", (kuint)&ioPro.stat.pwch[5].pwchbresp );
		IntErnals_RS_printf("ioPro.stat.pwch5.pwsa              = %x\n", (kuint)&ioPro.stat.pwch[5].pwsa );
		IntErnals_RS_printf("ioPro.stat.pwch5.pwlsize           = %x\n", (kuint)&ioPro.stat.pwch[5].pwlsize );
	}
#endif	/** STAT Unit **/
#endif
}

ProTest8 *pro_test8_new(void)
{
	ProTest8* self = k_object_new_with_private(PRO_TYPE_TEST8,sizeof(ProTest8Private));

	return self;
}
