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
#include "protest8.h"

G_DEFINE_TYPE(ProTest8, pro_test8, G_TYPE_OBJECT);

#define PRO_TEST8_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o), PRO_TYPE_TEST8, ProTest8Private));


struct _ProTest8Private
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
static void pro_test8_class_init(ProTest8Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);

	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(ProTest8Private));
}

static void pro_test8_init(ProTest8 *self)
{
	ProTest8Private *priv = PRO_TEST8_GET_PRIVATE(self);

	priv->preserved = 0;
}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(pro_test8_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	G_OBJECT_CLASS(pro_test8_parent_class)->finalize(object);
}
/*
 * PUBLIC
 */
void pro_test8(ProTest8 *self, EProBlockType type, IoPro ioPro)
{
#if 0
#ifdef D_ENABLE_IO_PRO_STAT		/** STAT Unit **/
	if(type == CheckHeaderMain_E_PRO_BLOCK_TYPE_STAT) {
		// AF1
		// General control Unit
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afgbal.aftrg        = %x\n", (kuint)&ioPro.stat.af[1].afgbal.aftrg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afgbal.afeben       = %x\n", (kuint)&ioPro.stat.af[1].afgbal.afeben );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afgbal.afintenb     = %x\n", (kuint)&ioPro.stat.af[1].afgbal.afintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afgbal.afintflg     = %x\n", (kuint)&ioPro.stat.af[1].afgbal.afintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afgbal.afgv         = %x\n", (kuint)&ioPro.stat.af[1].afgbal.afgv );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afgbal.afgh         = %x\n", (kuint)&ioPro.stat.af[1].afgbal.afgh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afgbal.afgvw        = %x\n", (kuint)&ioPro.stat.af[1].afgbal.afgvw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afgbal.afghw        = %x\n", (kuint)&ioPro.stat.af[1].afgbal.afghw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afgbal.afpaen       = %x\n", (kuint)&ioPro.stat.af[1].afgbal.afpaen );
		// Evaluted value Calculation Unit(0)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afmain0.afmtrxrr    = %x\n", (kuint)&ioPro.stat.af[1].afmain0.afmtrxrr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afmain0.afmtrxgr    = %x\n", (kuint)&ioPro.stat.af[1].afmain0.afmtrxgr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afmain0.afmtrxgb    = %x\n", (kuint)&ioPro.stat.af[1].afmain0.afmtrxgb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afmain0.afmtrxbb    = %x\n", (kuint)&ioPro.stat.af[1].afmain0.afmtrxbb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afmain0.afmden      = %x\n", (kuint)&ioPro.stat.af[1].afmain0.afmden );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afmain0.afknen      = %x\n", (kuint)&ioPro.stat.af[1].afmain0.afknen );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afmain0.afknb       = %x\n", (kuint)&ioPro.stat.af[1].afmain0.afknb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afmain0.afkninc     = %x\n", (kuint)&ioPro.stat.af[1].afmain0.afkninc );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afmain0.afknofs     = %x\n", (kuint)&ioPro.stat.af[1].afmain0.afknofs );
		// Evaluted value Calculation Unit(1)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afmain1.afmtrxrr    = %x\n", (kuint)&ioPro.stat.af[1].afmain1.afmtrxrr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afmain1.afmtrxgr    = %x\n", (kuint)&ioPro.stat.af[1].afmain1.afmtrxgr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afmain1.afmtrxgb    = %x\n", (kuint)&ioPro.stat.af[1].afmain1.afmtrxgb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afmain1.afmtrxbb    = %x\n", (kuint)&ioPro.stat.af[1].afmain1.afmtrxbb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afmain1.afmden      = %x\n", (kuint)&ioPro.stat.af[1].afmain1.afmden );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afmain1.afknen      = %x\n", (kuint)&ioPro.stat.af[1].afmain1.afknen );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afmain1.afknb       = %x\n", (kuint)&ioPro.stat.af[1].afmain1.afknb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afmain1.afkninc     = %x\n", (kuint)&ioPro.stat.af[1].afmain1.afkninc );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afmain1.afknofs     = %x\n", (kuint)&ioPro.stat.af[1].afmain1.afknofs );
		// Evaluted value Calculation Unit(2)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afmain2.afmtrxrr    = %x\n", (kuint)&ioPro.stat.af[1].afmain2.afmtrxrr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afmain2.afmtrxgr    = %x\n", (kuint)&ioPro.stat.af[1].afmain2.afmtrxgr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afmain2.afmtrxgb    = %x\n", (kuint)&ioPro.stat.af[1].afmain2.afmtrxgb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afmain2.afmtrxbb    = %x\n", (kuint)&ioPro.stat.af[1].afmain2.afmtrxbb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afmain2.afmden      = %x\n", (kuint)&ioPro.stat.af[1].afmain2.afmden );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afmain2.afknen      = %x\n", (kuint)&ioPro.stat.af[1].afmain2.afknen );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afmain2.afknb       = %x\n", (kuint)&ioPro.stat.af[1].afmain2.afknb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afmain2.afkninc     = %x\n", (kuint)&ioPro.stat.af[1].afmain2.afkninc );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afmain2.afknofs     = %x\n", (kuint)&ioPro.stat.af[1].afmain2.afknofs );
		// Vertical Detection Processing Unit Register
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afvs.afvsctl        = %x\n", (kuint)&ioPro.stat.af[1].afvs.afvsctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afvs.afvsh          = %x\n", (kuint)&ioPro.stat.af[1].afvs.afvsh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afvs.afvshw         = %x\n", (kuint)&ioPro.stat.af[1].afvs.afvshw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afvs.afiirvb        = %x\n", (kuint)&ioPro.stat.af[1].afvs.afiirvb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afvs.afcor2v        = %x\n", (kuint)&ioPro.stat.af[1].afvs.afcor2v );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afvs.affirvb        = %x\n", (kuint)&ioPro.stat.af[1].afvs.affirvb );
		// Horizontal Detection Processing Unit Register(0)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs0.afhsctla      = %x\n", (kuint)&ioPro.stat.af[1].afhs0.afhsctla );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs0.afhsctlb      = %x\n", (kuint)&ioPro.stat.af[1].afhs0.afhsctlb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs0.affirhba      = %x\n", (kuint)&ioPro.stat.af[1].afhs0.affirhba );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs0.affirhbb      = %x\n", (kuint)&ioPro.stat.af[1].afhs0.affirhbb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs0.afcor1ha      = %x\n", (kuint)&ioPro.stat.af[1].afhs0.afcor1ha );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs0.afcor1hb      = %x\n", (kuint)&ioPro.stat.af[1].afhs0.afcor1hb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs0.afgainha      = %x\n", (kuint)&ioPro.stat.af[1].afhs0.afgainha );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs0.afgainhb      = %x\n", (kuint)&ioPro.stat.af[1].afhs0.afgainhb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs0.afiirhba      = %x\n", (kuint)&ioPro.stat.af[1].afhs0.afiirhba );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs0.afiirhbb      = %x\n", (kuint)&ioPro.stat.af[1].afhs0.afiirhbb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs0.afcorbha      = %x\n", (kuint)&ioPro.stat.af[1].afhs0.afcorbha );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs0.afcorbhb      = %x\n", (kuint)&ioPro.stat.af[1].afhs0.afcorbhb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs0.afcorofsha    = %x\n", (kuint)&ioPro.stat.af[1].afhs0.afcorofsha );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs0.afcorofshb    = %x\n", (kuint)&ioPro.stat.af[1].afhs0.afcorofshb );
		// Horizontal Detection Processing Unit Register(1)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs1.afhsctla      = %x\n", (kuint)&ioPro.stat.af[1].afhs1.afhsctla );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs1.afhsctlb      = %x\n", (kuint)&ioPro.stat.af[1].afhs1.afhsctlb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs1.affirhba      = %x\n", (kuint)&ioPro.stat.af[1].afhs1.affirhba );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs1.affirhbb      = %x\n", (kuint)&ioPro.stat.af[1].afhs1.affirhbb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs1.afcor1ha      = %x\n", (kuint)&ioPro.stat.af[1].afhs1.afcor1ha );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs1.afcor1hb      = %x\n", (kuint)&ioPro.stat.af[1].afhs1.afcor1hb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs1.afgainha      = %x\n", (kuint)&ioPro.stat.af[1].afhs1.afgainha );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs1.afgainhb      = %x\n", (kuint)&ioPro.stat.af[1].afhs1.afgainhb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs1.afiirhba      = %x\n", (kuint)&ioPro.stat.af[1].afhs1.afiirhba );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs1.afiirhbb      = %x\n", (kuint)&ioPro.stat.af[1].afhs1.afiirhbb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs1.afcorbha      = %x\n", (kuint)&ioPro.stat.af[1].afhs1.afcorbha );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs1.afcorbhb      = %x\n", (kuint)&ioPro.stat.af[1].afhs1.afcorbhb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs1.afcorofsha    = %x\n", (kuint)&ioPro.stat.af[1].afhs1.afcorofsha );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs1.afcorofshb    = %x\n", (kuint)&ioPro.stat.af[1].afhs1.afcorofshb );
		// Horizontal Detection Processing Unit Register(2)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs2.afhsctla      = %x\n", (kuint)&ioPro.stat.af[1].afhs2.afhsctla );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs2.afhsctlb      = %x\n", (kuint)&ioPro.stat.af[1].afhs2.afhsctlb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs2.affirhba      = %x\n", (kuint)&ioPro.stat.af[1].afhs2.affirhba );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs2.affirhbb      = %x\n", (kuint)&ioPro.stat.af[1].afhs2.affirhbb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs2.afcor1ha      = %x\n", (kuint)&ioPro.stat.af[1].afhs2.afcor1ha );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs2.afcor1hb      = %x\n", (kuint)&ioPro.stat.af[1].afhs2.afcor1hb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs2.afgainha      = %x\n", (kuint)&ioPro.stat.af[1].afhs2.afgainha );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs2.afgainhb      = %x\n", (kuint)&ioPro.stat.af[1].afhs2.afgainhb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs2.afiirhba      = %x\n", (kuint)&ioPro.stat.af[1].afhs2.afiirhba );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs2.afiirhbb      = %x\n", (kuint)&ioPro.stat.af[1].afhs2.afiirhbb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs2.afcorbha      = %x\n", (kuint)&ioPro.stat.af[1].afhs2.afcorbha );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs2.afcorbhb      = %x\n", (kuint)&ioPro.stat.af[1].afhs2.afcorbhb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs2.afcorofsha    = %x\n", (kuint)&ioPro.stat.af[1].afhs2.afcorofsha );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afhs2.afcorofshb    = %x\n", (kuint)&ioPro.stat.af[1].afhs2.afcorofshb );
		// Detection Window Processing Unit Register(0)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin0.afwinctl     = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afwinctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin0.afclvge      = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afclvge );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin0.afclvl       = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afclvl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin0.afv          = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afv );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin0.afh          = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin0.afvw         = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afvw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin0.afhw         = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afhw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin0.afdatas      = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afdatas );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin0.afdatage     = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afdatage );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin0.afdatal      = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afdatal );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin0.afdatah0     = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afdatah0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin0.afdatah1     = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afdatah1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin0.afdatah2     = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afdatah2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin0.afdatav      = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afdatav );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin0.afslwm       = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afslwm );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin0.afdatamax    = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afdatamax );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin0.afdatamin    = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afdatamin );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin0.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afdatamh0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin0.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afdatamh1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin0.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[1].afwin0.afdatamh2 );
		// Detection Window Processing Unit Register(1)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin1.afwinctl     = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afwinctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin1.afclvge      = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afclvge );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin1.afclvl       = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afclvl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin1.afv          = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afv );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin1.afh          = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin1.afvw         = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afvw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin1.afhw         = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afhw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin1.afdatas      = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afdatas );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin1.afdatage     = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afdatage );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin1.afdatal      = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afdatal );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin1.afdatah0     = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afdatah0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin1.afdatah1     = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afdatah1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin1.afdatah2     = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afdatah2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin1.afdatav      = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afdatav );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin1.afslwm       = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afslwm );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin1.afdatamax    = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afdatamax );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin1.afdatamin    = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afdatamin );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin1.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afdatamh0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin1.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afdatamh1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin1.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[1].afwin1.afdatamh2 );
		// Detection Window Processing Unit Register(2)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin2.afwinctl     = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afwinctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin2.afclvge      = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afclvge );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin2.afclvl       = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afclvl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin2.afv          = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afv );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin2.afh          = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin2.afvw         = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afvw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin2.afhw         = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afhw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin2.afdatas      = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afdatas );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin2.afdatage     = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afdatage );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin2.afdatal      = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afdatal );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin2.afdatah0     = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afdatah0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin2.afdatah1     = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afdatah1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin2.afdatah2     = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afdatah2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin2.afdatav      = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afdatav );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin2.afslwm       = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afslwm );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin2.afdatamax    = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afdatamax );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin2.afdatamin    = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afdatamin );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin2.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afdatamh0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin2.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afdatamh1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin2.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[1].afwin2.afdatamh2 );
		// Detection Window Processing Unit Register(3)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin3.afwinctl     = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afwinctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin3.afclvge      = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afclvge );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin3.afclvl       = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afclvl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin3.afv          = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afv );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin3.afh          = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin3.afvw         = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afvw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin3.afhw         = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afhw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin3.afdatas      = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afdatas );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin3.afdatage     = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afdatage );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin3.afdatal      = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afdatal );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin3.afdatah0     = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afdatah0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin3.afdatah1     = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afdatah1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin3.afdatah2     = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afdatah2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin3.afdatav      = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afdatav );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin3.afslwm       = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afslwm );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin3.afdatamax    = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afdatamax );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin3.afdatamin    = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afdatamin );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin3.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afdatamh0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin3.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afdatamh1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin3.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[1].afwin3.afdatamh2 );
		// Detection Window Processing Unit Register(4)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin4.afwinctl     = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afwinctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin4.afclvge      = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afclvge );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin4.afclvl       = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afclvl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin4.afv          = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afv );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin4.afh          = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin4.afvw         = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afvw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin4.afhw         = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afhw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin4.afdatas      = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afdatas );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin4.afdatage     = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afdatage );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin4.afdatal      = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afdatal );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin4.afdatah0     = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afdatah0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin4.afdatah1     = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afdatah1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin4.afdatah2     = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afdatah2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin4.afdatav      = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afdatav );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin4.afslwm       = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afslwm );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin4.afdatamax    = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afdatamax );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin4.afdatamin    = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afdatamin );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin4.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afdatamh0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin4.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afdatamh1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin4.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[1].afwin4.afdatamh2 );
		// Detection Window Processing Unit Register(5)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin5.afwinctl     = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afwinctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin5.afclvge      = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afclvge );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin5.afclvl       = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afclvl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin5.afv          = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afv );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin5.afh          = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin5.afvw         = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afvw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin5.afhw         = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afhw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin5.afdatas      = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afdatas );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin5.afdatage     = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afdatage );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin5.afdatal      = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afdatal );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin5.afdatah0     = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afdatah0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin5.afdatah1     = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afdatah1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin5.afdatah2     = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afdatah2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin5.afdatav      = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afdatav );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin5.afslwm       = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afslwm );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin5.afdatamax    = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afdatamax );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin5.afdatamin    = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afdatamin );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin5.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afdatamh0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin5.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afdatamh1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin5.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[1].afwin5.afdatamh2 );
		// Detection Window Processing Unit Register(6)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin6.afwinctl     = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afwinctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin6.afclvge      = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afclvge );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin6.afclvl       = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afclvl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin6.afv          = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afv );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin6.afh          = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin6.afvw         = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afvw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin6.afhw         = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afhw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin6.afdatas      = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afdatas );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin6.afdatage     = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afdatage );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin6.afdatal      = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afdatal );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin6.afdatah0     = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afdatah0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin6.afdatah1     = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afdatah1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin6.afdatah2     = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afdatah2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin6.afdatav      = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afdatav );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin6.afslwm       = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afslwm );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin6.afdatamax    = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afdatamax );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin6.afdatamin    = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afdatamin );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin6.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afdatamh0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin6.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afdatamh1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin6.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[1].afwin6.afdatamh2 );
		// Detection Window Processing Unit Register(7)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin7.afwinctl     = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afwinctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin7.afclvge      = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afclvge );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin7.afclvl       = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afclvl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin7.afv          = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afv );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin7.afh          = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin7.afvw         = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afvw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin7.afhw         = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afhw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin7.afdatas      = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afdatas );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin7.afdatage     = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afdatage );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin7.afdatal      = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afdatal );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin7.afdatah0     = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afdatah0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin7.afdatah1     = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afdatah1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin7.afdatah2     = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afdatah2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin7.afdatav      = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afdatav );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin7.afslwm       = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afslwm );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin7.afdatamax    = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afdatamax );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin7.afdatamin    = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afdatamin );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin7.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afdatamh0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin7.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afdatamh1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin7.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[1].afwin7.afdatamh2 );
		// Detection Window Processing Unit Register(8)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin8.afwinctl     = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afwinctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin8.afclvge      = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afclvge );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin8.afclvl       = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afclvl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin8.afv          = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afv );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin8.afh          = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin8.afvw         = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afvw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin8.afhw         = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afhw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin8.afdatas      = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afdatas );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin8.afdatage     = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afdatage );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin8.afdatal      = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afdatal );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin8.afdatah0     = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afdatah0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin8.afdatah1     = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afdatah1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin8.afdatah2     = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afdatah2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin8.afdatav      = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afdatav );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin8.afslwm       = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afslwm );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin8.afdatamax    = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afdatamax );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin8.afdatamin    = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afdatamin );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin8.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afdatamh0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin8.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afdatamh1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin8.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[1].afwin8.afdatamh2 );
		// Detection Window Processing Unit Register(9)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin9.afwinctl     = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afwinctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin9.afclvge      = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afclvge );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin9.afclvl       = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afclvl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin9.afv          = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afv );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin9.afh          = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin9.afvw         = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afvw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin9.afhw         = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afhw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin9.afdatas      = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afdatas );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin9.afdatage     = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afdatage );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin9.afdatal      = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afdatal );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin9.afdatah0     = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afdatah0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin9.afdatah1     = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afdatah1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin9.afdatah2     = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afdatah2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin9.afdatav      = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afdatav );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin9.afslwm       = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afslwm );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin9.afdatamax    = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afdatamax );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin9.afdatamin    = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afdatamin );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin9.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afdatamh0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin9.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afdatamh1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin9.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[1].afwin9.afdatamh2 );
		// Detection Window Processing Unit Register(10)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin10.afwinctl     = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afwinctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin10.afclvge      = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afclvge );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin10.afclvl       = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afclvl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin10.afv          = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afv );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin10.afh          = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin10.afvw         = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afvw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin10.afhw         = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afhw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin10.afdatas      = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afdatas );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin10.afdatage     = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afdatage );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin10.afdatal      = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afdatal );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin10.afdatah0     = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afdatah0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin10.afdatah1     = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afdatah1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin10.afdatah2     = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afdatah2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin10.afdatav      = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afdatav );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin10.afslwm       = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afslwm );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin10.afdatamax    = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afdatamax );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin10.afdatamin    = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afdatamin );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin10.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afdatamh0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin10.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afdatamh1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin10.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[1].afwin10.afdatamh2 );
		// Detection Window Processing Unit Register(11)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin11.afwinctl     = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afwinctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin11.afclvge      = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afclvge );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin11.afclvl       = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afclvl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin11.afv          = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afv );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin11.afh          = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin11.afvw         = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afvw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin11.afhw         = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afhw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin11.afdatas      = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afdatas );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin11.afdatage     = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afdatage );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin11.afdatal      = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afdatal );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin11.afdatah0     = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afdatah0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin11.afdatah1     = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afdatah1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin11.afdatah2     = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afdatah2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin11.afdatav      = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afdatav );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin11.afslwm       = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afslwm );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin11.afdatamax    = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afdatamax );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin11.afdatamin    = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afdatamin );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin11.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afdatamh0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin11.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afdatamh1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin11.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[1].afwin11.afdatamh2 );
		// Detection Window Processing Unit Register(12)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin12.afwinctl     = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afwinctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin12.afclvge      = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afclvge );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin12.afclvl       = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afclvl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin12.afv          = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afv );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin12.afh          = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin12.afvw         = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afvw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin12.afhw         = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afhw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin12.afdatas      = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afdatas );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin12.afdatage     = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afdatage );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin12.afdatal      = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afdatal );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin12.afdatah0     = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afdatah0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin12.afdatah1     = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afdatah1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin12.afdatah2     = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afdatah2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin12.afdatav      = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afdatav );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin12.afslwm       = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afslwm );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin12.afdatamax    = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afdatamax );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin12.afdatamin    = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afdatamin );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin12.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afdatamh0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin12.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afdatamh1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin12.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[1].afwin12.afdatamh2 );
		// Detection Window Processing Unit Register(13)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin13.afwinctl     = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afwinctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin13.afclvge      = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afclvge );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin13.afclvl       = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afclvl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin13.afv          = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afv );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin13.afh          = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin13.afvw         = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afvw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin13.afhw         = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afhw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin13.afdatas      = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afdatas );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin13.afdatage     = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afdatage );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin13.afdatal      = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afdatal );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin13.afdatah0     = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afdatah0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin13.afdatah1     = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afdatah1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin13.afdatah2     = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afdatah2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin13.afdatav      = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afdatav );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin13.afslwm       = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afslwm );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin13.afdatamax    = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afdatamax );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin13.afdatamin    = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afdatamin );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin13.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afdatamh0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin13.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afdatamh1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin13.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[1].afwin13.afdatamh2 );
		// Detection Window Processing Unit Register(14)
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin14.afwinctl     = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afwinctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin14.afclvge      = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afclvge );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin14.afclvl       = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afclvl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin14.afv          = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afv );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin14.afh          = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin14.afvw         = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afvw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin14.afhw         = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afhw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin14.afdatas      = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afdatas );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin14.afdatage     = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afdatage );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin14.afdatal      = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afdatal );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin14.afdatah0     = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afdatah0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin14.afdatah1     = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afdatah1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin14.afdatah2     = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afdatah2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin14.afdatav      = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afdatav );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin14.afslwm       = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afslwm );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin14.afdatamax    = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afdatamax );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin14.afdatamin    = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afdatamin );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin14.afdatamh0    = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afdatamh0 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin14.afdatamh1    = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afdatamh1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.af1.afwin14.afdatamh2    = %x\n", (kuint)&ioPro.stat.af[1].afwin14.afdatamh2 );
		// aeawb-0
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb0.aetrg            = %x\n", (kuint)&ioPro.stat.aeawb[0].aetrg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb0.aeawbctl         = %x\n", (kuint)&ioPro.stat.aeawb[0].aeawbctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb0.aev              = %x\n", (kuint)&ioPro.stat.aeawb[0].aev );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb0.aeh              = %x\n", (kuint)&ioPro.stat.aeawb[0].aeh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb0.aevw             = %x\n", (kuint)&ioPro.stat.aeawb[0].aevw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb0.aetw             = %x\n", (kuint)&ioPro.stat.aeawb[0].aetw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb0.aebw             = %x\n", (kuint)&ioPro.stat.aeawb[0].aebw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb0.aehw             = %x\n", (kuint)&ioPro.stat.aeawb[0].aehw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb0.aelw             = %x\n", (kuint)&ioPro.stat.aeawb[0].aelw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb0.aerw             = %x\n", (kuint)&ioPro.stat.aeawb[0].aerw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb0.aevbc            = %x\n", (kuint)&ioPro.stat.aeawb[0].aevbc );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb0.aehbc            = %x\n", (kuint)&ioPro.stat.aeawb[0].aehbc );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb0.aecw1            = %x\n", (kuint)&ioPro.stat.aeawb[0].aecw1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb0.aecw2            = %x\n", (kuint)&ioPro.stat.aeawb[0].aecw2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb0.aecw3            = %x\n", (kuint)&ioPro.stat.aeawb[0].aecw3 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb0.awbcw1           = %x\n", (kuint)&ioPro.stat.aeawb[0].awbcw1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb0.awbcw2           = %x\n", (kuint)&ioPro.stat.aeawb[0].awbcw2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb0.awbcw3           = %x\n", (kuint)&ioPro.stat.aeawb[0].awbcw3 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb0.aeykrr           = %x\n", (kuint)&ioPro.stat.aeawb[0].aeykrr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb0.aeykgr           = %x\n", (kuint)&ioPro.stat.aeawb[0].aeykgr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb0.aeykgb           = %x\n", (kuint)&ioPro.stat.aeawb[0].aeykgb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb0.aeykbb           = %x\n", (kuint)&ioPro.stat.aeawb[0].aeykbb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb0.awtdy            = %x\n", (kuint)&ioPro.stat.aeawb[0].awtdy );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb0.awtdr            = %x\n", (kuint)&ioPro.stat.aeawb[0].awtdr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb0.awtdg            = %x\n", (kuint)&ioPro.stat.aeawb[0].awtdg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb0.awtdb            = %x\n", (kuint)&ioPro.stat.aeawb[0].awtdb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb0.awmlcy           = %x\n", (kuint)&ioPro.stat.aeawb[0].awmlcy );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb0.awmlcb           = %x\n", (kuint)&ioPro.stat.aeawb[0].awmlcb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb0.awmlcr           = %x\n", (kuint)&ioPro.stat.aeawb[0].awmlcr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb0.awmc             = %x\n", (kuint)&ioPro.stat.aeawb[0].awmc );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb0.linev            = %x\n", (kuint)&ioPro.stat.aeawb[0].linev );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb0.linedata         = %x\n", (kuint)&ioPro.stat.aeawb[0].linedata );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb0.lineintenb       = %x\n", (kuint)&ioPro.stat.aeawb[0].lineintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb0.lineintflg       = %x\n", (kuint)&ioPro.stat.aeawb[0].lineintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb0.aeawbpaen        = %x\n", (kuint)&ioPro.stat.aeawb[0].aeawbpaen );
		// aeawb-1
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb1.aetrg            = %x\n", (kuint)&ioPro.stat.aeawb[1].aetrg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb1.aeawbctl         = %x\n", (kuint)&ioPro.stat.aeawb[1].aeawbctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb1.aev              = %x\n", (kuint)&ioPro.stat.aeawb[1].aev );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb1.aeh              = %x\n", (kuint)&ioPro.stat.aeawb[1].aeh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb1.aevw             = %x\n", (kuint)&ioPro.stat.aeawb[1].aevw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb1.aetw             = %x\n", (kuint)&ioPro.stat.aeawb[1].aetw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb1.aebw             = %x\n", (kuint)&ioPro.stat.aeawb[1].aebw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb1.aehw             = %x\n", (kuint)&ioPro.stat.aeawb[1].aehw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb1.aelw             = %x\n", (kuint)&ioPro.stat.aeawb[1].aelw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb1.aerw             = %x\n", (kuint)&ioPro.stat.aeawb[1].aerw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb1.aevbc            = %x\n", (kuint)&ioPro.stat.aeawb[1].aevbc );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb1.aehbc            = %x\n", (kuint)&ioPro.stat.aeawb[1].aehbc );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb1.aecw1            = %x\n", (kuint)&ioPro.stat.aeawb[1].aecw1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb1.aecw2            = %x\n", (kuint)&ioPro.stat.aeawb[1].aecw2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb1.aecw3            = %x\n", (kuint)&ioPro.stat.aeawb[1].aecw3 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb1.awbcw1           = %x\n", (kuint)&ioPro.stat.aeawb[1].awbcw1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb1.awbcw2           = %x\n", (kuint)&ioPro.stat.aeawb[1].awbcw2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb1.awbcw3           = %x\n", (kuint)&ioPro.stat.aeawb[1].awbcw3 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb1.aeykrr           = %x\n", (kuint)&ioPro.stat.aeawb[1].aeykrr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb1.aeykgr           = %x\n", (kuint)&ioPro.stat.aeawb[1].aeykgr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb1.aeykgb           = %x\n", (kuint)&ioPro.stat.aeawb[1].aeykgb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb1.aeykbb           = %x\n", (kuint)&ioPro.stat.aeawb[1].aeykbb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb1.awtdy            = %x\n", (kuint)&ioPro.stat.aeawb[1].awtdy );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb1.awtdr            = %x\n", (kuint)&ioPro.stat.aeawb[1].awtdr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb1.awtdg            = %x\n", (kuint)&ioPro.stat.aeawb[1].awtdg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb1.awtdb            = %x\n", (kuint)&ioPro.stat.aeawb[1].awtdb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb1.awmlcy           = %x\n", (kuint)&ioPro.stat.aeawb[1].awmlcy );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb1.awmlcb           = %x\n", (kuint)&ioPro.stat.aeawb[1].awmlcb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb1.awmlcr           = %x\n", (kuint)&ioPro.stat.aeawb[1].awmlcr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb1.awmc             = %x\n", (kuint)&ioPro.stat.aeawb[1].awmc );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb1.linev            = %x\n", (kuint)&ioPro.stat.aeawb[1].linev );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb1.linedata         = %x\n", (kuint)&ioPro.stat.aeawb[1].linedata );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb1.lineintenb       = %x\n", (kuint)&ioPro.stat.aeawb[1].lineintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb1.lineintflg       = %x\n", (kuint)&ioPro.stat.aeawb[1].lineintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb1.aeawbpaen        = %x\n", (kuint)&ioPro.stat.aeawb[1].aeawbpaen );
		// aeawb-2
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb2.aetrg            = %x\n", (kuint)&ioPro.stat.aeawb[2].aetrg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb2.aeawbctl         = %x\n", (kuint)&ioPro.stat.aeawb[2].aeawbctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb2.aev              = %x\n", (kuint)&ioPro.stat.aeawb[2].aev );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb2.aeh              = %x\n", (kuint)&ioPro.stat.aeawb[2].aeh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb2.aevw             = %x\n", (kuint)&ioPro.stat.aeawb[2].aevw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb2.aetw             = %x\n", (kuint)&ioPro.stat.aeawb[2].aetw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb2.aebw             = %x\n", (kuint)&ioPro.stat.aeawb[2].aebw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb2.aehw             = %x\n", (kuint)&ioPro.stat.aeawb[2].aehw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb2.aelw             = %x\n", (kuint)&ioPro.stat.aeawb[2].aelw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb2.aerw             = %x\n", (kuint)&ioPro.stat.aeawb[2].aerw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb2.aevbc            = %x\n", (kuint)&ioPro.stat.aeawb[2].aevbc );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb2.aehbc            = %x\n", (kuint)&ioPro.stat.aeawb[2].aehbc );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb2.aecw1            = %x\n", (kuint)&ioPro.stat.aeawb[2].aecw1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb2.aecw2            = %x\n", (kuint)&ioPro.stat.aeawb[2].aecw2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb2.aecw3            = %x\n", (kuint)&ioPro.stat.aeawb[2].aecw3 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb2.awbcw1           = %x\n", (kuint)&ioPro.stat.aeawb[2].awbcw1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb2.awbcw2           = %x\n", (kuint)&ioPro.stat.aeawb[2].awbcw2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb2.awbcw3           = %x\n", (kuint)&ioPro.stat.aeawb[2].awbcw3 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb2.aeykrr           = %x\n", (kuint)&ioPro.stat.aeawb[2].aeykrr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb2.aeykgr           = %x\n", (kuint)&ioPro.stat.aeawb[2].aeykgr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb2.aeykgb           = %x\n", (kuint)&ioPro.stat.aeawb[2].aeykgb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb2.aeykbb           = %x\n", (kuint)&ioPro.stat.aeawb[2].aeykbb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb2.awtdy            = %x\n", (kuint)&ioPro.stat.aeawb[2].awtdy );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb2.awtdr            = %x\n", (kuint)&ioPro.stat.aeawb[2].awtdr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb2.awtdg            = %x\n", (kuint)&ioPro.stat.aeawb[2].awtdg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb2.awtdb            = %x\n", (kuint)&ioPro.stat.aeawb[2].awtdb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb2.awmlcy           = %x\n", (kuint)&ioPro.stat.aeawb[2].awmlcy );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb2.awmlcb           = %x\n", (kuint)&ioPro.stat.aeawb[2].awmlcb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb2.awmlcr           = %x\n", (kuint)&ioPro.stat.aeawb[2].awmlcr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb2.awmc             = %x\n", (kuint)&ioPro.stat.aeawb[2].awmc );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb2.linev            = %x\n", (kuint)&ioPro.stat.aeawb[2].linev );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb2.linedata         = %x\n", (kuint)&ioPro.stat.aeawb[2].linedata );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb2.lineintenb       = %x\n", (kuint)&ioPro.stat.aeawb[2].lineintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb2.lineintflg       = %x\n", (kuint)&ioPro.stat.aeawb[2].lineintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb2.aeawbpaen        = %x\n", (kuint)&ioPro.stat.aeawb[2].aeawbpaen );
		// aeawb-3
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb3.aetrg            = %x\n", (kuint)&ioPro.stat.aeawb[3].aetrg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb3.aeawbctl         = %x\n", (kuint)&ioPro.stat.aeawb[3].aeawbctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb3.aev              = %x\n", (kuint)&ioPro.stat.aeawb[3].aev );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb3.aeh              = %x\n", (kuint)&ioPro.stat.aeawb[3].aeh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb3.aevw             = %x\n", (kuint)&ioPro.stat.aeawb[3].aevw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb3.aetw             = %x\n", (kuint)&ioPro.stat.aeawb[3].aetw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb3.aebw             = %x\n", (kuint)&ioPro.stat.aeawb[3].aebw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb3.aehw             = %x\n", (kuint)&ioPro.stat.aeawb[3].aehw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb3.aelw             = %x\n", (kuint)&ioPro.stat.aeawb[3].aelw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb3.aerw             = %x\n", (kuint)&ioPro.stat.aeawb[3].aerw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb3.aevbc            = %x\n", (kuint)&ioPro.stat.aeawb[3].aevbc );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb3.aehbc            = %x\n", (kuint)&ioPro.stat.aeawb[3].aehbc );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb3.aecw1            = %x\n", (kuint)&ioPro.stat.aeawb[3].aecw1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb3.aecw2            = %x\n", (kuint)&ioPro.stat.aeawb[3].aecw2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb3.aecw3            = %x\n", (kuint)&ioPro.stat.aeawb[3].aecw3 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb3.awbcw1           = %x\n", (kuint)&ioPro.stat.aeawb[3].awbcw1 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb3.awbcw2           = %x\n", (kuint)&ioPro.stat.aeawb[3].awbcw2 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb3.awbcw3           = %x\n", (kuint)&ioPro.stat.aeawb[3].awbcw3 );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb3.aeykrr           = %x\n", (kuint)&ioPro.stat.aeawb[3].aeykrr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb3.aeykgr           = %x\n", (kuint)&ioPro.stat.aeawb[3].aeykgr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb3.aeykgb           = %x\n", (kuint)&ioPro.stat.aeawb[3].aeykgb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb3.aeykbb           = %x\n", (kuint)&ioPro.stat.aeawb[3].aeykbb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb3.awtdy            = %x\n", (kuint)&ioPro.stat.aeawb[3].awtdy );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb3.awtdr            = %x\n", (kuint)&ioPro.stat.aeawb[3].awtdr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb3.awtdg            = %x\n", (kuint)&ioPro.stat.aeawb[3].awtdg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb3.awtdb            = %x\n", (kuint)&ioPro.stat.aeawb[3].awtdb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb3.awmlcy           = %x\n", (kuint)&ioPro.stat.aeawb[3].awmlcy );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb3.awmlcb           = %x\n", (kuint)&ioPro.stat.aeawb[3].awmlcb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb3.awmlcr           = %x\n", (kuint)&ioPro.stat.aeawb[3].awmlcr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb3.awmc             = %x\n", (kuint)&ioPro.stat.aeawb[3].awmc );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb3.linev            = %x\n", (kuint)&ioPro.stat.aeawb[3].linev );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb3.linedata         = %x\n", (kuint)&ioPro.stat.aeawb[3].linedata );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb3.lineintenb       = %x\n", (kuint)&ioPro.stat.aeawb[3].lineintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb3.lineintflg       = %x\n", (kuint)&ioPro.stat.aeawb[3].lineintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.aeawb3.aeawbpaen        = %x\n", (kuint)&ioPro.stat.aeawb[3].aeawbpaen );
		// flck-0
		CheckHeaderMain_RS_PRINTF("ioPro.stat.flck0.fltrg             = %x\n", (kuint)&ioPro.stat.flck[0].fltrg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.flck0.flckctl           = %x\n", (kuint)&ioPro.stat.flck[0].flckctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.flck0.flv               = %x\n", (kuint)&ioPro.stat.flck[0].flv );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.flck0.flh               = %x\n", (kuint)&ioPro.stat.flck[0].flh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.flck0.flvw              = %x\n", (kuint)&ioPro.stat.flck[0].flvw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.flck0.flhw              = %x\n", (kuint)&ioPro.stat.flck[0].flhw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.flck0.flbc              = %x\n", (kuint)&ioPro.stat.flck[0].flbc );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.flck0.flykrr            = %x\n", (kuint)&ioPro.stat.flck[0].flykrr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.flck0.flykgr            = %x\n", (kuint)&ioPro.stat.flck[0].flykgr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.flck0.flykgb            = %x\n", (kuint)&ioPro.stat.flck[0].flykgb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.flck0.flykbb            = %x\n", (kuint)&ioPro.stat.flck[0].flykbb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.flck0.fltdy             = %x\n", (kuint)&ioPro.stat.flck[0].fltdy );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.flck0.fltdr             = %x\n", (kuint)&ioPro.stat.flck[0].fltdr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.flck0.fltdg             = %x\n", (kuint)&ioPro.stat.flck[0].fltdg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.flck0.fltdb             = %x\n", (kuint)&ioPro.stat.flck[0].fltdb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.flck0.flmlcy            = %x\n", (kuint)&ioPro.stat.flck[0].flmlcy );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.flck0.flmlcb            = %x\n", (kuint)&ioPro.stat.flck[0].flmlcb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.flck0.flmlcr            = %x\n", (kuint)&ioPro.stat.flck[0].flmlcr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.flck0.flmc              = %x\n", (kuint)&ioPro.stat.flck[0].flmc );
		// flck-1
		CheckHeaderMain_RS_PRINTF("ioPro.stat.flck1.fltrg             = %x\n", (kuint)&ioPro.stat.flck[1].fltrg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.flck1.flckctl           = %x\n", (kuint)&ioPro.stat.flck[1].flckctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.flck1.flv               = %x\n", (kuint)&ioPro.stat.flck[1].flv );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.flck1.flh               = %x\n", (kuint)&ioPro.stat.flck[1].flh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.flck1.flvw              = %x\n", (kuint)&ioPro.stat.flck[1].flvw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.flck1.flhw              = %x\n", (kuint)&ioPro.stat.flck[1].flhw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.flck1.flbc              = %x\n", (kuint)&ioPro.stat.flck[1].flbc );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.flck1.flykrr            = %x\n", (kuint)&ioPro.stat.flck[1].flykrr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.flck1.flykgr            = %x\n", (kuint)&ioPro.stat.flck[1].flykgr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.flck1.flykgb            = %x\n", (kuint)&ioPro.stat.flck[1].flykgb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.flck1.flykbb            = %x\n", (kuint)&ioPro.stat.flck[1].flykbb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.flck1.fltdy             = %x\n", (kuint)&ioPro.stat.flck[1].fltdy );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.flck1.fltdr             = %x\n", (kuint)&ioPro.stat.flck[1].fltdr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.flck1.fltdg             = %x\n", (kuint)&ioPro.stat.flck[1].fltdg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.flck1.fltdb             = %x\n", (kuint)&ioPro.stat.flck[1].fltdb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.flck1.flmlcy            = %x\n", (kuint)&ioPro.stat.flck[1].flmlcy );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.flck1.flmlcb            = %x\n", (kuint)&ioPro.stat.flck[1].flmlcb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.flck1.flmlcr            = %x\n", (kuint)&ioPro.stat.flck[1].flmlcr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.flck1.flmc              = %x\n", (kuint)&ioPro.stat.flck[1].flmc );
		// hist-0
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist0.histtrg           = %x\n", (kuint)&ioPro.stat.hist[0].histtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist0.histintenb        = %x\n", (kuint)&ioPro.stat.hist[0].histintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist0.histintflg        = %x\n", (kuint)&ioPro.stat.hist[0].histintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist0.histctl           = %x\n", (kuint)&ioPro.stat.hist[0].histctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist0.histv             = %x\n", (kuint)&ioPro.stat.hist[0].histv );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist0.histh             = %x\n", (kuint)&ioPro.stat.hist[0].histh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist0.histvw            = %x\n", (kuint)&ioPro.stat.hist[0].histvw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist0.histhw            = %x\n", (kuint)&ioPro.stat.hist[0].histhw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist0.histykrr          = %x\n", (kuint)&ioPro.stat.hist[0].histykrr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist0.histykgr          = %x\n", (kuint)&ioPro.stat.hist[0].histykgr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist0.histykgb          = %x\n", (kuint)&ioPro.stat.hist[0].histykgb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist0.histykbb          = %x\n", (kuint)&ioPro.stat.hist[0].histykbb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist0.histrmode         = %x\n", (kuint)&ioPro.stat.hist[0].histrmode );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist0.histgmode         = %x\n", (kuint)&ioPro.stat.hist[0].histgmode );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist0.histbmode         = %x\n", (kuint)&ioPro.stat.hist[0].histbmode );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist0.histymode         = %x\n", (kuint)&ioPro.stat.hist[0].histymode );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist0.histrsum          = %x\n", (kuint)&ioPro.stat.hist[0].histrsum );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist0.histgsum          = %x\n", (kuint)&ioPro.stat.hist[0].histgsum );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist0.histbsum          = %x\n", (kuint)&ioPro.stat.hist[0].histbsum );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist0.histysum          = %x\n", (kuint)&ioPro.stat.hist[0].histysum );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist0.histwbgr          = %x\n", (kuint)&ioPro.stat.hist[0].histwbgr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist0.histwbgg          = %x\n", (kuint)&ioPro.stat.hist[0].histwbgg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist0.histwbgb          = %x\n", (kuint)&ioPro.stat.hist[0].histwbgb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist0.histpaen          = %x\n", (kuint)&ioPro.stat.hist[0].histpaen );
		// hist-1
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist1.histtrg           = %x\n", (kuint)&ioPro.stat.hist[1].histtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist1.histintenb        = %x\n", (kuint)&ioPro.stat.hist[1].histintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist1.histintflg        = %x\n", (kuint)&ioPro.stat.hist[1].histintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist1.histctl           = %x\n", (kuint)&ioPro.stat.hist[1].histctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist1.histv             = %x\n", (kuint)&ioPro.stat.hist[1].histv );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist1.histh             = %x\n", (kuint)&ioPro.stat.hist[1].histh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist1.histvw            = %x\n", (kuint)&ioPro.stat.hist[1].histvw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist1.histhw            = %x\n", (kuint)&ioPro.stat.hist[1].histhw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist1.histykrr          = %x\n", (kuint)&ioPro.stat.hist[1].histykrr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist1.histykgr          = %x\n", (kuint)&ioPro.stat.hist[1].histykgr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist1.histykgb          = %x\n", (kuint)&ioPro.stat.hist[1].histykgb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist1.histykbb          = %x\n", (kuint)&ioPro.stat.hist[1].histykbb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist1.histrmode         = %x\n", (kuint)&ioPro.stat.hist[1].histrmode );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist1.histgmode         = %x\n", (kuint)&ioPro.stat.hist[1].histgmode );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist1.histbmode         = %x\n", (kuint)&ioPro.stat.hist[1].histbmode );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist1.histymode         = %x\n", (kuint)&ioPro.stat.hist[1].histymode );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist1.histrsum          = %x\n", (kuint)&ioPro.stat.hist[1].histrsum );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist1.histgsum          = %x\n", (kuint)&ioPro.stat.hist[1].histgsum );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist1.histbsum          = %x\n", (kuint)&ioPro.stat.hist[1].histbsum );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist1.histysum          = %x\n", (kuint)&ioPro.stat.hist[1].histysum );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist1.histwbgr          = %x\n", (kuint)&ioPro.stat.hist[1].histwbgr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist1.histwbgg          = %x\n", (kuint)&ioPro.stat.hist[1].histwbgg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist1.histwbgb          = %x\n", (kuint)&ioPro.stat.hist[1].histwbgb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist1.histpaen          = %x\n", (kuint)&ioPro.stat.hist[1].histpaen );
		// hist-2
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist2.histtrg           = %x\n", (kuint)&ioPro.stat.hist[2].histtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist2.histintenb        = %x\n", (kuint)&ioPro.stat.hist[2].histintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist2.histintflg        = %x\n", (kuint)&ioPro.stat.hist[2].histintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist2.histctl           = %x\n", (kuint)&ioPro.stat.hist[2].histctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist2.histv             = %x\n", (kuint)&ioPro.stat.hist[2].histv );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist2.histh             = %x\n", (kuint)&ioPro.stat.hist[2].histh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist2.histvw            = %x\n", (kuint)&ioPro.stat.hist[2].histvw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist2.histhw            = %x\n", (kuint)&ioPro.stat.hist[2].histhw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist2.histykrr          = %x\n", (kuint)&ioPro.stat.hist[2].histykrr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist2.histykgr          = %x\n", (kuint)&ioPro.stat.hist[2].histykgr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist2.histykgb          = %x\n", (kuint)&ioPro.stat.hist[2].histykgb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist2.histykbb          = %x\n", (kuint)&ioPro.stat.hist[2].histykbb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist2.histrmode         = %x\n", (kuint)&ioPro.stat.hist[2].histrmode );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist2.histgmode         = %x\n", (kuint)&ioPro.stat.hist[2].histgmode );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist2.histbmode         = %x\n", (kuint)&ioPro.stat.hist[2].histbmode );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist2.histymode         = %x\n", (kuint)&ioPro.stat.hist[2].histymode );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist2.histrsum          = %x\n", (kuint)&ioPro.stat.hist[2].histrsum );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist2.histgsum          = %x\n", (kuint)&ioPro.stat.hist[2].histgsum );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist2.histbsum          = %x\n", (kuint)&ioPro.stat.hist[2].histbsum );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist2.histysum          = %x\n", (kuint)&ioPro.stat.hist[2].histysum );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist2.histwbgr          = %x\n", (kuint)&ioPro.stat.hist[2].histwbgr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist2.histwbgg          = %x\n", (kuint)&ioPro.stat.hist[2].histwbgg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist2.histwbgb          = %x\n", (kuint)&ioPro.stat.hist[2].histwbgb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist2.histpaen          = %x\n", (kuint)&ioPro.stat.hist[2].histpaen );
		// hist-3
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist3.histtrg           = %x\n", (kuint)&ioPro.stat.hist[3].histtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist3.histintenb        = %x\n", (kuint)&ioPro.stat.hist[3].histintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist3.histintflg        = %x\n", (kuint)&ioPro.stat.hist[3].histintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist3.histctl           = %x\n", (kuint)&ioPro.stat.hist[3].histctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist3.histv             = %x\n", (kuint)&ioPro.stat.hist[3].histv );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist3.histh             = %x\n", (kuint)&ioPro.stat.hist[3].histh );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist3.histvw            = %x\n", (kuint)&ioPro.stat.hist[3].histvw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist3.histhw            = %x\n", (kuint)&ioPro.stat.hist[3].histhw );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist3.histykrr          = %x\n", (kuint)&ioPro.stat.hist[3].histykrr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist3.histykgr          = %x\n", (kuint)&ioPro.stat.hist[3].histykgr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist3.histykgb          = %x\n", (kuint)&ioPro.stat.hist[3].histykgb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist3.histykbb          = %x\n", (kuint)&ioPro.stat.hist[3].histykbb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist3.histrmode         = %x\n", (kuint)&ioPro.stat.hist[3].histrmode );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist3.histgmode         = %x\n", (kuint)&ioPro.stat.hist[3].histgmode );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist3.histbmode         = %x\n", (kuint)&ioPro.stat.hist[3].histbmode );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist3.histymode         = %x\n", (kuint)&ioPro.stat.hist[3].histymode );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist3.histrsum          = %x\n", (kuint)&ioPro.stat.hist[3].histrsum );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist3.histgsum          = %x\n", (kuint)&ioPro.stat.hist[3].histgsum );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist3.histbsum          = %x\n", (kuint)&ioPro.stat.hist[3].histbsum );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist3.histysum          = %x\n", (kuint)&ioPro.stat.hist[3].histysum );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist3.histwbgr          = %x\n", (kuint)&ioPro.stat.hist[3].histwbgr );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist3.histwbgg          = %x\n", (kuint)&ioPro.stat.hist[3].histwbgg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist3.histwbgb          = %x\n", (kuint)&ioPro.stat.hist[3].histwbgb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.hist3.histpaen          = %x\n", (kuint)&ioPro.stat.hist[3].histpaen );
		// pwch-0
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch0.pwchtrg           = %x\n", (kuint)&ioPro.stat.pwch[0].pwchtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch0.pws               = %x\n", (kuint)&ioPro.stat.pwch[0].pws );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch0.pwaxctl           = %x\n", (kuint)&ioPro.stat.pwch[0].pwaxctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch0.pwchctl           = %x\n", (kuint)&ioPro.stat.pwch[0].pwchctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch0.pwchintenb        = %x\n", (kuint)&ioPro.stat.pwch[0].pwchintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch0.pwchintflg        = %x\n", (kuint)&ioPro.stat.pwch[0].pwchintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch0.pwchbresp         = %x\n", (kuint)&ioPro.stat.pwch[0].pwchbresp );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch0.pwsa              = %x\n", (kuint)&ioPro.stat.pwch[0].pwsa );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch0.pwlsize           = %x\n", (kuint)&ioPro.stat.pwch[0].pwlsize );
		// pwch-1
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch1.pwchtrg           = %x\n", (kuint)&ioPro.stat.pwch[1].pwchtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch1.pws               = %x\n", (kuint)&ioPro.stat.pwch[1].pws );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch1.pwaxctl           = %x\n", (kuint)&ioPro.stat.pwch[1].pwaxctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch1.pwchctl           = %x\n", (kuint)&ioPro.stat.pwch[1].pwchctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch1.pwchintenb        = %x\n", (kuint)&ioPro.stat.pwch[1].pwchintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch1.pwchintflg        = %x\n", (kuint)&ioPro.stat.pwch[1].pwchintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch1.pwchbresp         = %x\n", (kuint)&ioPro.stat.pwch[1].pwchbresp );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch1.pwsa              = %x\n", (kuint)&ioPro.stat.pwch[1].pwsa );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch1.pwlsize           = %x\n", (kuint)&ioPro.stat.pwch[1].pwlsize );
		// pwch-2
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch2.pwchtrg           = %x\n", (kuint)&ioPro.stat.pwch[2].pwchtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch2.pws               = %x\n", (kuint)&ioPro.stat.pwch[2].pws );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch2.pwaxctl           = %x\n", (kuint)&ioPro.stat.pwch[2].pwaxctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch2.pwchctl           = %x\n", (kuint)&ioPro.stat.pwch[2].pwchctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch2.pwchintenb        = %x\n", (kuint)&ioPro.stat.pwch[2].pwchintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch2.pwchintflg        = %x\n", (kuint)&ioPro.stat.pwch[2].pwchintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch2.pwchbresp         = %x\n", (kuint)&ioPro.stat.pwch[2].pwchbresp );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch2.pwsa              = %x\n", (kuint)&ioPro.stat.pwch[2].pwsa );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch2.pwlsize           = %x\n", (kuint)&ioPro.stat.pwch[2].pwlsize );
		// pwch-3
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch3.pwchtrg           = %x\n", (kuint)&ioPro.stat.pwch[3].pwchtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch3.pws               = %x\n", (kuint)&ioPro.stat.pwch[3].pws );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch3.pwaxctl           = %x\n", (kuint)&ioPro.stat.pwch[3].pwaxctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch3.pwchctl           = %x\n", (kuint)&ioPro.stat.pwch[3].pwchctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch3.pwchintenb        = %x\n", (kuint)&ioPro.stat.pwch[3].pwchintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch3.pwchintflg        = %x\n", (kuint)&ioPro.stat.pwch[3].pwchintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch3.pwchbresp         = %x\n", (kuint)&ioPro.stat.pwch[3].pwchbresp );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch3.pwsa              = %x\n", (kuint)&ioPro.stat.pwch[3].pwsa );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch3.pwlsize           = %x\n", (kuint)&ioPro.stat.pwch[3].pwlsize );
		// pwch-4
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch4.pwchtrg           = %x\n", (kuint)&ioPro.stat.pwch[4].pwchtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch4.pws               = %x\n", (kuint)&ioPro.stat.pwch[4].pws );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch4.pwaxctl           = %x\n", (kuint)&ioPro.stat.pwch[4].pwaxctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch4.pwchctl           = %x\n", (kuint)&ioPro.stat.pwch[4].pwchctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch4.pwchintenb        = %x\n", (kuint)&ioPro.stat.pwch[4].pwchintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch4.pwchintflg        = %x\n", (kuint)&ioPro.stat.pwch[4].pwchintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch4.pwchbresp         = %x\n", (kuint)&ioPro.stat.pwch[4].pwchbresp );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch4.pwsa              = %x\n", (kuint)&ioPro.stat.pwch[4].pwsa );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch4.pwlsize           = %x\n", (kuint)&ioPro.stat.pwch[4].pwlsize );
		// pwch-5
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch5.pwchtrg           = %x\n", (kuint)&ioPro.stat.pwch[5].pwchtrg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch5.pws               = %x\n", (kuint)&ioPro.stat.pwch[5].pws );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch5.pwaxctl           = %x\n", (kuint)&ioPro.stat.pwch[5].pwaxctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch5.pwchctl           = %x\n", (kuint)&ioPro.stat.pwch[5].pwchctl );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch5.pwchintenb        = %x\n", (kuint)&ioPro.stat.pwch[5].pwchintenb );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch5.pwchintflg        = %x\n", (kuint)&ioPro.stat.pwch[5].pwchintflg );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch5.pwchbresp         = %x\n", (kuint)&ioPro.stat.pwch[5].pwchbresp );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch5.pwsa              = %x\n", (kuint)&ioPro.stat.pwch[5].pwsa );
		CheckHeaderMain_RS_PRINTF("ioPro.stat.pwch5.pwlsize           = %x\n", (kuint)&ioPro.stat.pwch[5].pwlsize );
	}
#endif	/** STAT Unit **/
#endif
}

ProTest8 *pro_test8_new()
{
	ProTest8 *self = g_object_new(PRO_TYPE_TEST8, NULL);

	return self;
}
