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
#include "protest2.h"


K_TYPE_DEFINE_WITH_PRIVATE(ProTest2, pro_test2)
#define PRO_TEST2_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), ProTest2Private, PRO_TYPE_TEST2))


struct _ProTest2Private
{
	int a;
};


/*DECLS*/


/*IMPL*/
static void pro_test2_constructor(ProTest2 *self)
{
	ProTest2Private *priv = PRO_TEST2_GET_PRIVATE(self);
}

static void pro_test2_destructor(ProTest2 *self)
{
	ProTest2Private *priv = PRO_TEST2_GET_PRIVATE(self);
}


/*PUBLIC*/
void pro_test2(ProTest2 *self, EProBlockType type, IoPro ioPro)
{

#if 0
#ifdef D_ENABLE_IO_PRO_SEN	/** SEN Unit **/

	if(type == E_PRO_BLOCK_TYPE_SEN) {

		// OBD-00
		RS_printf("IO_PRO.SEN.OBD00.OBDTRG            = %x\n", (unsigned int)&ioPro.sen.obd[0][0].obdtrg);
		RS_printf("IO_PRO.SEN.OBD00.OBDINTENB         = %x\n", (unsigned int)&ioPro.sen.obd[0][0].obdintenb);
		RS_printf("IO_PRO.SEN.OBD00.OBDINTFLG         = %x\n", (unsigned int)&ioPro.sen.obd[0][0].obdintflg);
		RS_printf("IO_PRO.SEN.OBD00.OBDCORE.OBDV      = %x\n", (unsigned int)&ioPro.sen.obd[0][0].obdcore.obdv);
		RS_printf("IO_PRO.SEN.OBD00.OBDCORE.OBDH      = %x\n", (unsigned int)&ioPro.sen.obd[0][0].obdcore.obdh);
		RS_printf("IO_PRO.SEN.OBD00.OBDCORE.OBDVW     = %x\n", (unsigned int)&ioPro.sen.obd[0][0].obdcore.obdvw);
		RS_printf("IO_PRO.SEN.OBD00.OBDCORE.OBDHW     = %x\n", (unsigned int)&ioPro.sen.obd[0][0].obdcore.obdhw);
		RS_printf("IO_PRO.SEN.OBD00.OBDCORE.OBDTHBIT  = %x\n", (unsigned int)&ioPro.sen.obd[0][0].obdcore.obdthbit);
		RS_printf("IO_PRO.SEN.OBD00.OBDCORE.OBDDATAR  = %x\n", (unsigned int)&ioPro.sen.obd[0][0].obdcore.obddatar);
		RS_printf("IO_PRO.SEN.OBD00.OBDCORE.OBDDATAGR = %x\n", (unsigned int)&ioPro.sen.obd[0][0].obdcore.obddatagr);
		RS_printf("IO_PRO.SEN.OBD00.OBDCORE.OBDDATAGB = %x\n", (unsigned int)&ioPro.sen.obd[0][0].obdcore.obddatagb);
		RS_printf("IO_PRO.SEN.OBD00.OBDCORE.OBDDATAB  = %x\n", (unsigned int)&ioPro.sen.obd[0][0].obdcore.obddatab);
		RS_printf("IO_PRO.SEN.OBD00.OBDCORE.OBDCNTR   = %x\n", (unsigned int)&ioPro.sen.obd[0][0].obdcore.obdcntr);
		RS_printf("IO_PRO.SEN.OBD00.OBDCORE.OBDCNTGR  = %x\n", (unsigned int)&ioPro.sen.obd[0][0].obdcore.obdcntgr);
		RS_printf("IO_PRO.SEN.OBD00.OBDCORE.OBDCNTGR  = %x\n", (unsigned int)&ioPro.sen.obd[0][0].obdcore.obdcntgr);
		RS_printf("IO_PRO.SEN.OBD00.OBDCORE.OBDCNTB   = %x\n", (unsigned int)&ioPro.sen.obd[0][0].obdcore.obdcntb);

		// OBD-01
		RS_printf("IO_PRO.SEN.OBD01.OBDTRG            = %x\n", (unsigned int)&ioPro.sen.obd[0][1].obdtrg);
		RS_printf("IO_PRO.SEN.OBD01.OBDINTENB         = %x\n", (unsigned int)&ioPro.sen.obd[0][1].obdintenb);
		RS_printf("IO_PRO.SEN.OBD01.OBDINTFLG         = %x\n", (unsigned int)&ioPro.sen.obd[0][1].obdintflg);
		RS_printf("IO_PRO.SEN.OBD01.OBDCORE.OBDV      = %x\n", (unsigned int)&ioPro.sen.obd[0][1].obdcore.obdv);
		RS_printf("IO_PRO.SEN.OBD01.OBDCORE.OBDH      = %x\n", (unsigned int)&ioPro.sen.obd[0][1].obdcore.obdh);
		RS_printf("IO_PRO.SEN.OBD01.OBDCORE.OBDVW     = %x\n", (unsigned int)&ioPro.sen.obd[0][1].obdcore.obdvw);
		RS_printf("IO_PRO.SEN.OBD01.OBDCORE.OBDHW     = %x\n", (unsigned int)&ioPro.sen.obd[0][1].obdcore.obdhw);
		RS_printf("IO_PRO.SEN.OBD01.OBDCORE.OBDTHBIT  = %x\n", (unsigned int)&ioPro.sen.obd[0][1].obdcore.obdthbit);
		RS_printf("IO_PRO.SEN.OBD01.OBDCORE.OBDDATAR  = %x\n", (unsigned int)&ioPro.sen.obd[0][1].obdcore.obddatar);
		RS_printf("IO_PRO.SEN.OBD01.OBDCORE.OBDDATAGR = %x\n", (unsigned int)&ioPro.sen.obd[0][1].obdcore.obddatagr);
		RS_printf("IO_PRO.SEN.OBD01.OBDCORE.OBDDATAGB = %x\n", (unsigned int)&ioPro.sen.obd[0][1].obdcore.obddatagb);
		RS_printf("IO_PRO.SEN.OBD01.OBDCORE.OBDDATAB  = %x\n", (unsigned int)&ioPro.sen.obd[0][1].obdcore.obddatab);
		RS_printf("IO_PRO.SEN.OBD01.OBDCORE.OBDCNTR   = %x\n", (unsigned int)&ioPro.sen.obd[0][1].obdcore.obdcntr);
		RS_printf("IO_PRO.SEN.OBD01.OBDCORE.OBDCNTGR  = %x\n", (unsigned int)&ioPro.sen.obd[0][1].obdcore.obdcntgr);
		RS_printf("IO_PRO.SEN.OBD01.OBDCORE.OBDCNTGR  = %x\n", (unsigned int)&ioPro.sen.obd[0][1].obdcore.obdcntgr);
		RS_printf("IO_PRO.SEN.OBD01.OBDCORE.OBDCNTB   = %x\n", (unsigned int)&ioPro.sen.obd[0][1].obdcore.obdcntb);

		// OBD-10
		RS_printf("IO_PRO.SEN.OBD10.OBDTRG            = %x\n", (unsigned int)&ioPro.sen.obd[1][0].obdtrg);
		RS_printf("IO_PRO.SEN.OBD10.OBDINTENB         = %x\n", (unsigned int)&ioPro.sen.obd[1][0].obdintenb);
		RS_printf("IO_PRO.SEN.OBD10.OBDINTFLG         = %x\n", (unsigned int)&ioPro.sen.obd[1][0].obdintflg);
		RS_printf("IO_PRO.SEN.OBD10.OBDCORE.OBDV      = %x\n", (unsigned int)&ioPro.sen.obd[1][0].obdcore.obdv);
		RS_printf("IO_PRO.SEN.OBD10.OBDCORE.OBDH      = %x\n", (unsigned int)&ioPro.sen.obd[1][0].obdcore.obdh);
		RS_printf("IO_PRO.SEN.OBD10.OBDCORE.OBDVW     = %x\n", (unsigned int)&ioPro.sen.obd[1][0].obdcore.obdvw);
		RS_printf("IO_PRO.SEN.OBD10.OBDCORE.OBDHW     = %x\n", (unsigned int)&ioPro.sen.obd[1][0].obdcore.obdhw);
		RS_printf("IO_PRO.SEN.OBD10.OBDCORE.OBDTHBIT  = %x\n", (unsigned int)&ioPro.sen.obd[1][0].obdcore.obdthbit);
		RS_printf("IO_PRO.SEN.OBD10.OBDCORE.OBDDATAR  = %x\n", (unsigned int)&ioPro.sen.obd[1][0].obdcore.obddatar);
		RS_printf("IO_PRO.SEN.OBD10.OBDCORE.OBDDATAGR = %x\n", (unsigned int)&ioPro.sen.obd[1][0].obdcore.obddatagr);
		RS_printf("IO_PRO.SEN.OBD10.OBDCORE.OBDDATAGB = %x\n", (unsigned int)&ioPro.sen.obd[1][0].obdcore.obddatagb);
		RS_printf("IO_PRO.SEN.OBD10.OBDCORE.OBDDATAB  = %x\n", (unsigned int)&ioPro.sen.obd[1][0].obdcore.obddatab);
		RS_printf("IO_PRO.SEN.OBD10.OBDCORE.OBDCNTR   = %x\n", (unsigned int)&ioPro.sen.obd[1][0].obdcore.obdcntr);
		RS_printf("IO_PRO.SEN.OBD10.OBDCORE.OBDCNTGR  = %x\n", (unsigned int)&ioPro.sen.obd[1][0].obdcore.obdcntgr);
		RS_printf("IO_PRO.SEN.OBD10.OBDCORE.OBDCNTGR  = %x\n", (unsigned int)&ioPro.sen.obd[1][0].obdcore.obdcntgr);
		RS_printf("IO_PRO.SEN.OBD10.OBDCORE.OBDCNTB   = %x\n", (unsigned int)&ioPro.sen.obd[1][0].obdcore.obdcntb);

		// OBD-11
		RS_printf("IO_PRO.SEN.OBD11.OBDTRG            = %x\n", (unsigned int)&ioPro.sen.obd[1][1].obdtrg);
		RS_printf("IO_PRO.SEN.OBD11.OBDINTENB         = %x\n", (unsigned int)&ioPro.sen.obd[1][1].obdintenb);
		RS_printf("IO_PRO.SEN.OBD11.OBDINTFLG         = %x\n", (unsigned int)&ioPro.sen.obd[1][1].obdintflg);
		RS_printf("IO_PRO.SEN.OBD11.OBDCORE.OBDV      = %x\n", (unsigned int)&ioPro.sen.obd[1][1].obdcore.obdv);
		RS_printf("IO_PRO.SEN.OBD11.OBDCORE.OBDH      = %x\n", (unsigned int)&ioPro.sen.obd[1][1].obdcore.obdh);
		RS_printf("IO_PRO.SEN.OBD11.OBDCORE.OBDVW     = %x\n", (unsigned int)&ioPro.sen.obd[1][1].obdcore.obdvw);
		RS_printf("IO_PRO.SEN.OBD11.OBDCORE.OBDHW     = %x\n", (unsigned int)&ioPro.sen.obd[1][1].obdcore.obdhw);
		RS_printf("IO_PRO.SEN.OBD11.OBDCORE.OBDTHBIT  = %x\n", (unsigned int)&ioPro.sen.obd[1][1].obdcore.obdthbit);
		RS_printf("IO_PRO.SEN.OBD11.OBDCORE.OBDDATAR  = %x\n", (unsigned int)&ioPro.sen.obd[1][1].obdcore.obddatar);
		RS_printf("IO_PRO.SEN.OBD11.OBDCORE.OBDDATAGR = %x\n", (unsigned int)&ioPro.sen.obd[1][1].obdcore.obddatagr);
		RS_printf("IO_PRO.SEN.OBD11.OBDCORE.OBDDATAGB = %x\n", (unsigned int)&ioPro.sen.obd[1][1].obdcore.obddatagb);
		RS_printf("IO_PRO.SEN.OBD11.OBDCORE.OBDDATAB  = %x\n", (unsigned int)&ioPro.sen.obd[1][1].obdcore.obddatab);
		RS_printf("IO_PRO.SEN.OBD11.OBDCORE.OBDCNTR   = %x\n", (unsigned int)&ioPro.sen.obd[1][1].obdcore.obdcntr);
		RS_printf("IO_PRO.SEN.OBD11.OBDCORE.OBDCNTGR  = %x\n", (unsigned int)&ioPro.sen.obd[1][1].obdcore.obdcntgr);
		RS_printf("IO_PRO.SEN.OBD11.OBDCORE.OBDCNTGR  = %x\n", (unsigned int)&ioPro.sen.obd[1][1].obdcore.obdcntgr);
		RS_printf("IO_PRO.SEN.OBD11.OBDCORE.OBDCNTB   = %x\n", (unsigned int)&ioPro.sen.obd[1][1].obdcore.obdcntb);

		// OBD-20
		RS_printf("IO_PRO.SEN.OBD20.OBDTRG            = %x\n", (unsigned int)&ioPro.sen.obd[2][0].obdtrg);
		RS_printf("IO_PRO.SEN.OBD20.OBDINTENB         = %x\n", (unsigned int)&ioPro.sen.obd[2][0].obdintenb);
		RS_printf("IO_PRO.SEN.OBD20.OBDINTFLG         = %x\n", (unsigned int)&ioPro.sen.obd[2][0].obdintflg);
		RS_printf("IO_PRO.SEN.OBD20.OBDCORE.OBDV      = %x\n", (unsigned int)&ioPro.sen.obd[2][0].obdcore.obdv);
		RS_printf("IO_PRO.SEN.OBD20.OBDCORE.OBDH      = %x\n", (unsigned int)&ioPro.sen.obd[2][0].obdcore.obdh);
		RS_printf("IO_PRO.SEN.OBD20.OBDCORE.OBDVW     = %x\n", (unsigned int)&ioPro.sen.obd[2][0].obdcore.obdvw);
		RS_printf("IO_PRO.SEN.OBD20.OBDCORE.OBDHW     = %x\n", (unsigned int)&ioPro.sen.obd[2][0].obdcore.obdhw);
		RS_printf("IO_PRO.SEN.OBD20.OBDCORE.OBDTHBIT  = %x\n", (unsigned int)&ioPro.sen.obd[2][0].obdcore.obdthbit);
		RS_printf("IO_PRO.SEN.OBD20.OBDCORE.OBDDATAR  = %x\n", (unsigned int)&ioPro.sen.obd[2][0].obdcore.obddatar);
		RS_printf("IO_PRO.SEN.OBD20.OBDCORE.OBDDATAGR = %x\n", (unsigned int)&ioPro.sen.obd[2][0].obdcore.obddatagr);
		RS_printf("IO_PRO.SEN.OBD20.OBDCORE.OBDDATAGB = %x\n", (unsigned int)&ioPro.sen.obd[2][0].obdcore.obddatagb);
		RS_printf("IO_PRO.SEN.OBD20.OBDCORE.OBDDATAB  = %x\n", (unsigned int)&ioPro.sen.obd[2][0].obdcore.obddatab);
		RS_printf("IO_PRO.SEN.OBD20.OBDCORE.OBDCNTR   = %x\n", (unsigned int)&ioPro.sen.obd[2][0].obdcore.obdcntr);
		RS_printf("IO_PRO.SEN.OBD20.OBDCORE.OBDCNTGR  = %x\n", (unsigned int)&ioPro.sen.obd[2][0].obdcore.obdcntgr);
		RS_printf("IO_PRO.SEN.OBD20.OBDCORE.OBDCNTGR  = %x\n", (unsigned int)&ioPro.sen.obd[2][0].obdcore.obdcntgr);
		RS_printf("IO_PRO.SEN.OBD20.OBDCORE.OBDCNTB   = %x\n", (unsigned int)&ioPro.sen.obd[2][0].obdcore.obdcntb);

		// OBD-21
		RS_printf("IO_PRO.SEN.OBD21.OBDTRG            = %x\n", (unsigned int)&ioPro.sen.obd[2][1].obdtrg);
		RS_printf("IO_PRO.SEN.OBD21.OBDINTENB         = %x\n", (unsigned int)&ioPro.sen.obd[2][1].obdintenb);
		RS_printf("IO_PRO.SEN.OBD21.OBDINTFLG         = %x\n", (unsigned int)&ioPro.sen.obd[2][1].obdintflg);
		RS_printf("IO_PRO.SEN.OBD21.OBDCORE.OBDV      = %x\n", (unsigned int)&ioPro.sen.obd[2][1].obdcore.obdv);
		RS_printf("IO_PRO.SEN.OBD21.OBDCORE.OBDH      = %x\n", (unsigned int)&ioPro.sen.obd[2][1].obdcore.obdh);
		RS_printf("IO_PRO.SEN.OBD21.OBDCORE.OBDVW     = %x\n", (unsigned int)&ioPro.sen.obd[2][1].obdcore.obdvw);
		RS_printf("IO_PRO.SEN.OBD21.OBDCORE.OBDHW     = %x\n", (unsigned int)&ioPro.sen.obd[2][1].obdcore.obdhw);
		RS_printf("IO_PRO.SEN.OBD21.OBDCORE.OBDTHBIT  = %x\n", (unsigned int)&ioPro.sen.obd[2][1].obdcore.obdthbit);
		RS_printf("IO_PRO.SEN.OBD21.OBDCORE.OBDDATAR  = %x\n", (unsigned int)&ioPro.sen.obd[2][1].obdcore.obddatar);
		RS_printf("IO_PRO.SEN.OBD21.OBDCORE.OBDDATAGR = %x\n", (unsigned int)&ioPro.sen.obd[2][1].obdcore.obddatagr);
		RS_printf("IO_PRO.SEN.OBD21.OBDCORE.OBDDATAGB = %x\n", (unsigned int)&ioPro.sen.obd[2][1].obdcore.obddatagb);
		RS_printf("IO_PRO.SEN.OBD21.OBDCORE.OBDDATAB  = %x\n", (unsigned int)&ioPro.sen.obd[2][1].obdcore.obddatab);
		RS_printf("IO_PRO.SEN.OBD21.OBDCORE.OBDCNTR   = %x\n", (unsigned int)&ioPro.sen.obd[2][1].obdcore.obdcntr);
		RS_printf("IO_PRO.SEN.OBD21.OBDCORE.OBDCNTGR  = %x\n", (unsigned int)&ioPro.sen.obd[2][1].obdcore.obdcntgr);
		RS_printf("IO_PRO.SEN.OBD21.OBDCORE.OBDCNTGR  = %x\n", (unsigned int)&ioPro.sen.obd[2][1].obdcore.obdcntgr);
		RS_printf("IO_PRO.SEN.OBD21.OBDCORE.OBDCNTB   = %x\n", (unsigned int)&ioPro.sen.obd[2][1].obdcore.obdcntb);

		// OBD-30
		RS_printf("IO_PRO.SEN.OBD30.OBDTRG            = %x\n", (unsigned int)&ioPro.sen.obd[3][0].obdtrg);
		RS_printf("IO_PRO.SEN.OBD30.OBDINTENB         = %x\n", (unsigned int)&ioPro.sen.obd[3][0].obdintenb);
		RS_printf("IO_PRO.SEN.OBD30.OBDINTFLG         = %x\n", (unsigned int)&ioPro.sen.obd[3][0].obdintflg);
		RS_printf("IO_PRO.SEN.OBD30.OBDCORE.OBDV      = %x\n", (unsigned int)&ioPro.sen.obd[3][0].obdcore.obdv);
		RS_printf("IO_PRO.SEN.OBD30.OBDCORE.OBDH      = %x\n", (unsigned int)&ioPro.sen.obd[3][0].obdcore.obdh);
		RS_printf("IO_PRO.SEN.OBD30.OBDCORE.OBDVW     = %x\n", (unsigned int)&ioPro.sen.obd[3][0].obdcore.obdvw);
		RS_printf("IO_PRO.SEN.OBD30.OBDCORE.OBDHW     = %x\n", (unsigned int)&ioPro.sen.obd[3][0].obdcore.obdhw);
		RS_printf("IO_PRO.SEN.OBD30.OBDCORE.OBDTHBIT  = %x\n", (unsigned int)&ioPro.sen.obd[3][0].obdcore.obdthbit);
		RS_printf("IO_PRO.SEN.OBD30.OBDCORE.OBDDATAR  = %x\n", (unsigned int)&ioPro.sen.obd[3][0].obdcore.obddatar);
		RS_printf("IO_PRO.SEN.OBD30.OBDCORE.OBDDATAGR = %x\n", (unsigned int)&ioPro.sen.obd[3][0].obdcore.obddatagr);
		RS_printf("IO_PRO.SEN.OBD30.OBDCORE.OBDDATAGB = %x\n", (unsigned int)&ioPro.sen.obd[3][0].obdcore.obddatagb);
		RS_printf("IO_PRO.SEN.OBD30.OBDCORE.OBDDATAB  = %x\n", (unsigned int)&ioPro.sen.obd[3][0].obdcore.obddatab);
		RS_printf("IO_PRO.SEN.OBD30.OBDCORE.OBDCNTR   = %x\n", (unsigned int)&ioPro.sen.obd[3][0].obdcore.obdcntr);
		RS_printf("IO_PRO.SEN.OBD30.OBDCORE.OBDCNTGR  = %x\n", (unsigned int)&ioPro.sen.obd[3][0].obdcore.obdcntgr);
		RS_printf("IO_PRO.SEN.OBD30.OBDCORE.OBDCNTGR  = %x\n", (unsigned int)&ioPro.sen.obd[3][0].obdcore.obdcntgr);
		RS_printf("IO_PRO.SEN.OBD30.OBDCORE.OBDCNTB   = %x\n", (unsigned int)&ioPro.sen.obd[3][0].obdcore.obdcntb);

		// OBD-31
		RS_printf("IO_PRO.SEN.OBD31.OBDTRG            = %x\n", (unsigned int)&ioPro.sen.obd[3][1].obdtrg);
		RS_printf("IO_PRO.SEN.OBD31.OBDINTENB         = %x\n", (unsigned int)&ioPro.sen.obd[3][1].obdintenb);
		RS_printf("IO_PRO.SEN.OBD31.OBDINTFLG         = %x\n", (unsigned int)&ioPro.sen.obd[3][1].obdintflg);
		RS_printf("IO_PRO.SEN.OBD31.OBDCORE.OBDV      = %x\n", (unsigned int)&ioPro.sen.obd[3][1].obdcore.obdv);
		RS_printf("IO_PRO.SEN.OBD31.OBDCORE.OBDH      = %x\n", (unsigned int)&ioPro.sen.obd[3][1].obdcore.obdh);
		RS_printf("IO_PRO.SEN.OBD31.OBDCORE.OBDVW     = %x\n", (unsigned int)&ioPro.sen.obd[3][1].obdcore.obdvw);
		RS_printf("IO_PRO.SEN.OBD31.OBDCORE.OBDHW     = %x\n", (unsigned int)&ioPro.sen.obd[3][1].obdcore.obdhw);
		RS_printf("IO_PRO.SEN.OBD31.OBDCORE.OBDTHBIT  = %x\n", (unsigned int)&ioPro.sen.obd[3][1].obdcore.obdthbit);
		RS_printf("IO_PRO.SEN.OBD31.OBDCORE.OBDDATAR  = %x\n", (unsigned int)&ioPro.sen.obd[3][1].obdcore.obddatar);
		RS_printf("IO_PRO.SEN.OBD31.OBDCORE.OBDDATAGR = %x\n", (unsigned int)&ioPro.sen.obd[3][1].obdcore.obddatagr);
		RS_printf("IO_PRO.SEN.OBD31.OBDCORE.OBDDATAGB = %x\n", (unsigned int)&ioPro.sen.obd[3][1].obdcore.obddatagb);
		RS_printf("IO_PRO.SEN.OBD31.OBDCORE.OBDDATAB  = %x\n", (unsigned int)&ioPro.sen.obd[3][1].obdcore.obddatab);
		RS_printf("IO_PRO.SEN.OBD31.OBDCORE.OBDCNTR   = %x\n", (unsigned int)&ioPro.sen.obd[3][1].obdcore.obdcntr);
		RS_printf("IO_PRO.SEN.OBD31.OBDCORE.OBDCNTGR  = %x\n", (unsigned int)&ioPro.sen.obd[3][1].obdcore.obdcntgr);
		RS_printf("IO_PRO.SEN.OBD31.OBDCORE.OBDCNTGR  = %x\n", (unsigned int)&ioPro.sen.obd[3][1].obdcore.obdcntgr);
		RS_printf("IO_PRO.SEN.OBD31.OBDCORE.OBDCNTB   = %x\n", (unsigned int)&ioPro.sen.obd[3][1].obdcore.obdcntb);

		// OBT-00
		RS_printf("IO_PRO.SEN.OBT00.OBTTRG            = %x\n", (unsigned int)&ioPro.sen.obt[0][0].obttrg);
		RS_printf("IO_PRO.SEN.OBT00.OBTINTENB         = %x\n", (unsigned int)&ioPro.sen.obt[0][0].obtintenb);
		RS_printf("IO_PRO.SEN.OBT00.OBTINTFLG         = %x\n", (unsigned int)&ioPro.sen.obt[0][0].obtintflg);
		RS_printf("IO_PRO.SEN.OBT00.OBTCORE.OBTCTL    = %x\n", (unsigned int)&ioPro.sen.obt[0][0].obtcore.obtctl);
		RS_printf("IO_PRO.SEN.OBT00.OBTCORE.OBTV      = %x\n", (unsigned int)&ioPro.sen.obt[0][0].obtcore.obtv);
		RS_printf("IO_PRO.SEN.OBT00.OBTCORE.OBTH      = %x\n", (unsigned int)&ioPro.sen.obt[0][0].obtcore.obth);
		RS_printf("IO_PRO.SEN.OBT00.OBTCORE.OBTVW     = %x\n", (unsigned int)&ioPro.sen.obt[0][0].obtcore.obtvw);
		RS_printf("IO_PRO.SEN.OBT00.OBTCORE.OBTHW     = %x\n", (unsigned int)&ioPro.sen.obt[0][0].obtcore.obthw);
		RS_printf("IO_PRO.SEN.OBT00.OBTCORE.OBTTHBIT  = %x\n", (unsigned int)&ioPro.sen.obt[0][0].obtcore.obtthbit);
		RS_printf("IO_PRO.SEN.OBT00.OBTCORE.OBTDATAR  = %x\n", (unsigned int)&ioPro.sen.obt[0][0].obtcore.obtdatar);
		RS_printf("IO_PRO.SEN.OBT00.OBTCORE.OBTDATAGR = %x\n", (unsigned int)&ioPro.sen.obt[0][0].obtcore.obtdatagr);
		RS_printf("IO_PRO.SEN.OBT00.OBTCORE.OBTDATAGB = %x\n", (unsigned int)&ioPro.sen.obt[0][0].obtcore.obtdatagb);
		RS_printf("IO_PRO.SEN.OBT00.OBTCORE.OBTDATAB  = %x\n", (unsigned int)&ioPro.sen.obt[0][0].obtcore.obtdatab);
		RS_printf("IO_PRO.SEN.OBT00.OBTCORE.OBTOFSR   = %x\n", (unsigned int)&ioPro.sen.obt[0][0].obtcore.obtofsr);
		RS_printf("IO_PRO.SEN.OBT00.OBTCORE.OBTOFSGR  = %x\n", (unsigned int)&ioPro.sen.obt[0][0].obtcore.obtofsgr);
		RS_printf("IO_PRO.SEN.OBT00.OBTCORE.OBTOFSGB  = %x\n", (unsigned int)&ioPro.sen.obt[0][0].obtcore.obtofsgb);
		RS_printf("IO_PRO.SEN.OBT00.OBTCORE.OBTOFSB   = %x\n", (unsigned int)&ioPro.sen.obt[0][0].obtcore.obtofsb);

		// OBT-01
		RS_printf("IO_PRO.SEN.OBT01.OBTTRG            = %x\n", (unsigned int)&ioPro.sen.obt[0][1].obttrg);
		RS_printf("IO_PRO.SEN.OBT01.OBTINTENB         = %x\n", (unsigned int)&ioPro.sen.obt[0][1].obtintenb);
		RS_printf("IO_PRO.SEN.OBT01.OBTINTFLG         = %x\n", (unsigned int)&ioPro.sen.obt[0][1].obtintflg);
		RS_printf("IO_PRO.SEN.OBT01.OBTCORE.OBTCTL    = %x\n", (unsigned int)&ioPro.sen.obt[0][1].obtcore.obtctl);
		RS_printf("IO_PRO.SEN.OBT01.OBTCORE.OBTV      = %x\n", (unsigned int)&ioPro.sen.obt[0][1].obtcore.obtv);
		RS_printf("IO_PRO.SEN.OBT01.OBTCORE.OBTH      = %x\n", (unsigned int)&ioPro.sen.obt[0][1].obtcore.obth);
		RS_printf("IO_PRO.SEN.OBT01.OBTCORE.OBTVW     = %x\n", (unsigned int)&ioPro.sen.obt[0][1].obtcore.obtvw);
		RS_printf("IO_PRO.SEN.OBT01.OBTCORE.OBTHW     = %x\n", (unsigned int)&ioPro.sen.obt[0][1].obtcore.obthw);
		RS_printf("IO_PRO.SEN.OBT01.OBTCORE.OBTTHBIT  = %x\n", (unsigned int)&ioPro.sen.obt[0][1].obtcore.obtthbit);
		RS_printf("IO_PRO.SEN.OBT01.OBTCORE.OBTDATAR  = %x\n", (unsigned int)&ioPro.sen.obt[0][1].obtcore.obtdatar);
		RS_printf("IO_PRO.SEN.OBT01.OBTCORE.OBTDATAGR = %x\n", (unsigned int)&ioPro.sen.obt[0][1].obtcore.obtdatagr);
		RS_printf("IO_PRO.SEN.OBT01.OBTCORE.OBTDATAGB = %x\n", (unsigned int)&ioPro.sen.obt[0][1].obtcore.obtdatagb);
		RS_printf("IO_PRO.SEN.OBT01.OBTCORE.OBTDATAB  = %x\n", (unsigned int)&ioPro.sen.obt[0][1].obtcore.obtdatab);
		RS_printf("IO_PRO.SEN.OBT01.OBTCORE.OBTOFSR   = %x\n", (unsigned int)&ioPro.sen.obt[0][1].obtcore.obtofsr);
		RS_printf("IO_PRO.SEN.OBT01.OBTCORE.OBTOFSGR  = %x\n", (unsigned int)&ioPro.sen.obt[0][1].obtcore.obtofsgr);
		RS_printf("IO_PRO.SEN.OBT01.OBTCORE.OBTOFSGB  = %x\n", (unsigned int)&ioPro.sen.obt[0][1].obtcore.obtofsgb);
		RS_printf("IO_PRO.SEN.OBT01.OBTCORE.OBTOFSB   = %x\n", (unsigned int)&ioPro.sen.obt[0][1].obtcore.obtofsb);

		// OBT-10
		RS_printf("IO_PRO.SEN.OBT10.OBTTRG            = %x\n", (unsigned int)&ioPro.sen.obt[1][0].obttrg);
		RS_printf("IO_PRO.SEN.OBT10.OBTINTENB         = %x\n", (unsigned int)&ioPro.sen.obt[1][0].obtintenb);
		RS_printf("IO_PRO.SEN.OBT10.OBTINTFLG         = %x\n", (unsigned int)&ioPro.sen.obt[1][0].obtintflg);
		RS_printf("IO_PRO.SEN.OBT10.OBTCORE.OBTCTL    = %x\n", (unsigned int)&ioPro.sen.obt[1][0].obtcore.obtctl);
		RS_printf("IO_PRO.SEN.OBT10.OBTCORE.OBTV      = %x\n", (unsigned int)&ioPro.sen.obt[1][0].obtcore.obtv);
		RS_printf("IO_PRO.SEN.OBT10.OBTCORE.OBTH      = %x\n", (unsigned int)&ioPro.sen.obt[1][0].obtcore.obth);
		RS_printf("IO_PRO.SEN.OBT10.OBTCORE.OBTVW     = %x\n", (unsigned int)&ioPro.sen.obt[1][0].obtcore.obtvw);
		RS_printf("IO_PRO.SEN.OBT10.OBTCORE.OBTHW     = %x\n", (unsigned int)&ioPro.sen.obt[1][0].obtcore.obthw);
		RS_printf("IO_PRO.SEN.OBT10.OBTCORE.OBTTHBIT  = %x\n", (unsigned int)&ioPro.sen.obt[1][0].obtcore.obtthbit);
		RS_printf("IO_PRO.SEN.OBT10.OBTCORE.OBTDATAR  = %x\n", (unsigned int)&ioPro.sen.obt[1][0].obtcore.obtdatar);
		RS_printf("IO_PRO.SEN.OBT10.OBTCORE.OBTDATAGR = %x\n", (unsigned int)&ioPro.sen.obt[1][0].obtcore.obtdatagr);
		RS_printf("IO_PRO.SEN.OBT10.OBTCORE.OBTDATAGB = %x\n", (unsigned int)&ioPro.sen.obt[1][0].obtcore.obtdatagb);
		RS_printf("IO_PRO.SEN.OBT10.OBTCORE.OBTDATAB  = %x\n", (unsigned int)&ioPro.sen.obt[1][0].obtcore.obtdatab);
		RS_printf("IO_PRO.SEN.OBT10.OBTCORE.OBTOFSR   = %x\n", (unsigned int)&ioPro.sen.obt[1][0].obtcore.obtofsr);
		RS_printf("IO_PRO.SEN.OBT10.OBTCORE.OBTOFSGR  = %x\n", (unsigned int)&ioPro.sen.obt[1][0].obtcore.obtofsgr);
		RS_printf("IO_PRO.SEN.OBT10.OBTCORE.OBTOFSGB  = %x\n", (unsigned int)&ioPro.sen.obt[1][0].obtcore.obtofsgb);
		RS_printf("IO_PRO.SEN.OBT10.OBTCORE.OBTOFSB   = %x\n", (unsigned int)&ioPro.sen.obt[1][0].obtcore.obtofsb);

		// OBT-11
		RS_printf("IO_PRO.SEN.OBT11.OBTTRG            = %x\n", (unsigned int)&ioPro.sen.obt[1][1].obttrg);
		RS_printf("IO_PRO.SEN.OBT11.OBTINTENB         = %x\n", (unsigned int)&ioPro.sen.obt[1][1].obtintenb);
		RS_printf("IO_PRO.SEN.OBT11.OBTINTFLG         = %x\n", (unsigned int)&ioPro.sen.obt[1][1].obtintflg);
		RS_printf("IO_PRO.SEN.OBT11.OBTCORE.OBTCTL    = %x\n", (unsigned int)&ioPro.sen.obt[1][1].obtcore.obtctl);
		RS_printf("IO_PRO.SEN.OBT11.OBTCORE.OBTV      = %x\n", (unsigned int)&ioPro.sen.obt[1][1].obtcore.obtv);
		RS_printf("IO_PRO.SEN.OBT11.OBTCORE.OBTH      = %x\n", (unsigned int)&ioPro.sen.obt[1][1].obtcore.obth);
		RS_printf("IO_PRO.SEN.OBT11.OBTCORE.OBTVW     = %x\n", (unsigned int)&ioPro.sen.obt[1][1].obtcore.obtvw);
		RS_printf("IO_PRO.SEN.OBT11.OBTCORE.OBTHW     = %x\n", (unsigned int)&ioPro.sen.obt[1][1].obtcore.obthw);
		RS_printf("IO_PRO.SEN.OBT11.OBTCORE.OBTTHBIT  = %x\n", (unsigned int)&ioPro.sen.obt[1][1].obtcore.obtthbit);
		RS_printf("IO_PRO.SEN.OBT11.OBTCORE.OBTDATAR  = %x\n", (unsigned int)&ioPro.sen.obt[1][1].obtcore.obtdatar);
		RS_printf("IO_PRO.SEN.OBT11.OBTCORE.OBTDATAGR = %x\n", (unsigned int)&ioPro.sen.obt[1][1].obtcore.obtdatagr);
		RS_printf("IO_PRO.SEN.OBT11.OBTCORE.OBTDATAGB = %x\n", (unsigned int)&ioPro.sen.obt[1][1].obtcore.obtdatagb);
		RS_printf("IO_PRO.SEN.OBT11.OBTCORE.OBTDATAB  = %x\n", (unsigned int)&ioPro.sen.obt[1][1].obtcore.obtdatab);
		RS_printf("IO_PRO.SEN.OBT11.OBTCORE.OBTOFSR   = %x\n", (unsigned int)&ioPro.sen.obt[1][1].obtcore.obtofsr);
		RS_printf("IO_PRO.SEN.OBT11.OBTCORE.OBTOFSGR  = %x\n", (unsigned int)&ioPro.sen.obt[1][1].obtcore.obtofsgr);
		RS_printf("IO_PRO.SEN.OBT11.OBTCORE.OBTOFSGB  = %x\n", (unsigned int)&ioPro.sen.obt[1][1].obtcore.obtofsgb);
		RS_printf("IO_PRO.SEN.OBT11.OBTCORE.OBTOFSB   = %x\n", (unsigned int)&ioPro.sen.obt[1][1].obtcore.obtofsb);

		// OBT-20
		RS_printf("IO_PRO.SEN.OBT20.OBTTRG            = %x\n", (unsigned int)&ioPro.sen.obt[2][0].obttrg);
		RS_printf("IO_PRO.SEN.OBT20.OBTINTENB         = %x\n", (unsigned int)&ioPro.sen.obt[2][0].obtintenb);
		RS_printf("IO_PRO.SEN.OBT20.OBTINTFLG         = %x\n", (unsigned int)&ioPro.sen.obt[2][0].obtintflg);
		RS_printf("IO_PRO.SEN.OBT20.OBTCORE.OBTCTL    = %x\n", (unsigned int)&ioPro.sen.obt[2][0].obtcore.obtctl);
		RS_printf("IO_PRO.SEN.OBT20.OBTCORE.OBTV      = %x\n", (unsigned int)&ioPro.sen.obt[2][0].obtcore.obtv);
		RS_printf("IO_PRO.SEN.OBT20.OBTCORE.OBTH      = %x\n", (unsigned int)&ioPro.sen.obt[2][0].obtcore.obth);
		RS_printf("IO_PRO.SEN.OBT20.OBTCORE.OBTVW     = %x\n", (unsigned int)&ioPro.sen.obt[2][0].obtcore.obtvw);
		RS_printf("IO_PRO.SEN.OBT20.OBTCORE.OBTHW     = %x\n", (unsigned int)&ioPro.sen.obt[2][0].obtcore.obthw);
		RS_printf("IO_PRO.SEN.OBT20.OBTCORE.OBTTHBIT  = %x\n", (unsigned int)&ioPro.sen.obt[2][0].obtcore.obtthbit);
		RS_printf("IO_PRO.SEN.OBT20.OBTCORE.OBTDATAR  = %x\n", (unsigned int)&ioPro.sen.obt[2][0].obtcore.obtdatar);
		RS_printf("IO_PRO.SEN.OBT20.OBTCORE.OBTDATAGR = %x\n", (unsigned int)&ioPro.sen.obt[2][0].obtcore.obtdatagr);
		RS_printf("IO_PRO.SEN.OBT20.OBTCORE.OBTDATAGB = %x\n", (unsigned int)&ioPro.sen.obt[2][0].obtcore.obtdatagb);
		RS_printf("IO_PRO.SEN.OBT20.OBTCORE.OBTDATAB  = %x\n", (unsigned int)&ioPro.sen.obt[2][0].obtcore.obtdatab);
		RS_printf("IO_PRO.SEN.OBT20.OBTCORE.OBTOFSR   = %x\n", (unsigned int)&ioPro.sen.obt[2][0].obtcore.obtofsr);
		RS_printf("IO_PRO.SEN.OBT20.OBTCORE.OBTOFSGR  = %x\n", (unsigned int)&ioPro.sen.obt[2][0].obtcore.obtofsgr);
		RS_printf("IO_PRO.SEN.OBT20.OBTCORE.OBTOFSGB  = %x\n", (unsigned int)&ioPro.sen.obt[2][0].obtcore.obtofsgb);
		RS_printf("IO_PRO.SEN.OBT20.OBTCORE.OBTOFSB   = %x\n", (unsigned int)&ioPro.sen.obt[2][0].obtcore.obtofsb);

		// OBT-21
		RS_printf("IO_PRO.SEN.OBT21.OBTTRG            = %x\n", (unsigned int)&ioPro.sen.obt[2][1].obttrg);
		RS_printf("IO_PRO.SEN.OBT21.OBTINTENB         = %x\n", (unsigned int)&ioPro.sen.obt[2][1].obtintenb);
		RS_printf("IO_PRO.SEN.OBT21.OBTINTFLG         = %x\n", (unsigned int)&ioPro.sen.obt[2][1].obtintflg);
		RS_printf("IO_PRO.SEN.OBT21.OBTCORE.OBTCTL    = %x\n", (unsigned int)&ioPro.sen.obt[2][1].obtcore.obtctl);
		RS_printf("IO_PRO.SEN.OBT21.OBTCORE.OBTV      = %x\n", (unsigned int)&ioPro.sen.obt[2][1].obtcore.obtv);
		RS_printf("IO_PRO.SEN.OBT21.OBTCORE.OBTH      = %x\n", (unsigned int)&ioPro.sen.obt[2][1].obtcore.obth);
		RS_printf("IO_PRO.SEN.OBT21.OBTCORE.OBTVW     = %x\n", (unsigned int)&ioPro.sen.obt[2][1].obtcore.obtvw);
		RS_printf("IO_PRO.SEN.OBT21.OBTCORE.OBTHW     = %x\n", (unsigned int)&ioPro.sen.obt[2][1].obtcore.obthw);
		RS_printf("IO_PRO.SEN.OBT21.OBTCORE.OBTTHBIT  = %x\n", (unsigned int)&ioPro.sen.obt[2][1].obtcore.obtthbit);
		RS_printf("IO_PRO.SEN.OBT21.OBTCORE.OBTDATAR  = %x\n", (unsigned int)&ioPro.sen.obt[2][1].obtcore.obtdatar);
		RS_printf("IO_PRO.SEN.OBT21.OBTCORE.OBTDATAGR = %x\n", (unsigned int)&ioPro.sen.obt[2][1].obtcore.obtdatagr);
		RS_printf("IO_PRO.SEN.OBT21.OBTCORE.OBTDATAGB = %x\n", (unsigned int)&ioPro.sen.obt[2][1].obtcore.obtdatagb);
		RS_printf("IO_PRO.SEN.OBT21.OBTCORE.OBTDATAB  = %x\n", (unsigned int)&ioPro.sen.obt[2][1].obtcore.obtdatab);
		RS_printf("IO_PRO.SEN.OBT21.OBTCORE.OBTOFSR   = %x\n", (unsigned int)&ioPro.sen.obt[2][1].obtcore.obtofsr);
		RS_printf("IO_PRO.SEN.OBT21.OBTCORE.OBTOFSGR  = %x\n", (unsigned int)&ioPro.sen.obt[2][1].obtcore.obtofsgr);
		RS_printf("IO_PRO.SEN.OBT21.OBTCORE.OBTOFSGB  = %x\n", (unsigned int)&ioPro.sen.obt[2][1].obtcore.obtofsgb);
		RS_printf("IO_PRO.SEN.OBT21.OBTCORE.OBTOFSB   = %x\n", (unsigned int)&ioPro.sen.obt[2][1].obtcore.obtofsb);

		// OBT-30
		RS_printf("IO_PRO.SEN.OBT30.OBTTRG            = %x\n", (unsigned int)&ioPro.sen.obt[3][0].obttrg);
		RS_printf("IO_PRO.SEN.OBT30.OBTINTENB         = %x\n", (unsigned int)&ioPro.sen.obt[3][0].obtintenb);
		RS_printf("IO_PRO.SEN.OBT30.OBTINTFLG         = %x\n", (unsigned int)&ioPro.sen.obt[3][0].obtintflg);
		RS_printf("IO_PRO.SEN.OBT30.OBTCORE.OBTCTL    = %x\n", (unsigned int)&ioPro.sen.obt[3][0].obtcore.obtctl);
		RS_printf("IO_PRO.SEN.OBT30.OBTCORE.OBTV      = %x\n", (unsigned int)&ioPro.sen.obt[3][0].obtcore.obtv);
		RS_printf("IO_PRO.SEN.OBT30.OBTCORE.OBTH      = %x\n", (unsigned int)&ioPro.sen.obt[3][0].obtcore.obth);
		RS_printf("IO_PRO.SEN.OBT30.OBTCORE.OBTVW     = %x\n", (unsigned int)&ioPro.sen.obt[3][0].obtcore.obtvw);
		RS_printf("IO_PRO.SEN.OBT30.OBTCORE.OBTHW     = %x\n", (unsigned int)&ioPro.sen.obt[3][0].obtcore.obthw);
		RS_printf("IO_PRO.SEN.OBT30.OBTCORE.OBTTHBIT  = %x\n", (unsigned int)&ioPro.sen.obt[3][0].obtcore.obtthbit);
		RS_printf("IO_PRO.SEN.OBT30.OBTCORE.OBTDATAR  = %x\n", (unsigned int)&ioPro.sen.obt[3][0].obtcore.obtdatar);
		RS_printf("IO_PRO.SEN.OBT30.OBTCORE.OBTDATAGR = %x\n", (unsigned int)&ioPro.sen.obt[3][0].obtcore.obtdatagr);
		RS_printf("IO_PRO.SEN.OBT30.OBTCORE.OBTDATAGB = %x\n", (unsigned int)&ioPro.sen.obt[3][0].obtcore.obtdatagb);
		RS_printf("IO_PRO.SEN.OBT30.OBTCORE.OBTDATAB  = %x\n", (unsigned int)&ioPro.sen.obt[3][0].obtcore.obtdatab);
		RS_printf("IO_PRO.SEN.OBT30.OBTCORE.OBTOFSR   = %x\n", (unsigned int)&ioPro.sen.obt[3][0].obtcore.obtofsr);
		RS_printf("IO_PRO.SEN.OBT30.OBTCORE.OBTOFSGR  = %x\n", (unsigned int)&ioPro.sen.obt[3][0].obtcore.obtofsgr);
		RS_printf("IO_PRO.SEN.OBT30.OBTCORE.OBTOFSGB  = %x\n", (unsigned int)&ioPro.sen.obt[3][0].obtcore.obtofsgb);
		RS_printf("IO_PRO.SEN.OBT30.OBTCORE.OBTOFSB   = %x\n", (unsigned int)&ioPro.sen.obt[3][0].obtcore.obtofsb);

		// OBT-31
		RS_printf("IO_PRO.SEN.OBT31.OBTTRG            = %x\n", (unsigned int)&ioPro.sen.obt[3][1].obttrg);
		RS_printf("IO_PRO.SEN.OBT31.OBTINTENB         = %x\n", (unsigned int)&ioPro.sen.obt[3][1].obtintenb);
		RS_printf("IO_PRO.SEN.OBT31.OBTINTFLG         = %x\n", (unsigned int)&ioPro.sen.obt[3][1].obtintflg);
		RS_printf("IO_PRO.SEN.OBT31.OBTCORE.OBTCTL    = %x\n", (unsigned int)&ioPro.sen.obt[3][1].obtcore.obtctl);
		RS_printf("IO_PRO.SEN.OBT31.OBTCORE.OBTV      = %x\n", (unsigned int)&ioPro.sen.obt[3][1].obtcore.obtv);
		RS_printf("IO_PRO.SEN.OBT31.OBTCORE.OBTH      = %x\n", (unsigned int)&ioPro.sen.obt[3][1].obtcore.obth);
		RS_printf("IO_PRO.SEN.OBT31.OBTCORE.OBTVW     = %x\n", (unsigned int)&ioPro.sen.obt[3][1].obtcore.obtvw);
		RS_printf("IO_PRO.SEN.OBT31.OBTCORE.OBTHW     = %x\n", (unsigned int)&ioPro.sen.obt[3][1].obtcore.obthw);
		RS_printf("IO_PRO.SEN.OBT31.OBTCORE.OBTTHBIT  = %x\n", (unsigned int)&ioPro.sen.obt[3][1].obtcore.obtthbit);
		RS_printf("IO_PRO.SEN.OBT31.OBTCORE.OBTDATAR  = %x\n", (unsigned int)&ioPro.sen.obt[3][1].obtcore.obtdatar);
		RS_printf("IO_PRO.SEN.OBT31.OBTCORE.OBTDATAGR = %x\n", (unsigned int)&ioPro.sen.obt[3][1].obtcore.obtdatagr);
		RS_printf("IO_PRO.SEN.OBT31.OBTCORE.OBTDATAGB = %x\n", (unsigned int)&ioPro.sen.obt[3][1].obtcore.obtdatagb);
		RS_printf("IO_PRO.SEN.OBT31.OBTCORE.OBTDATAB  = %x\n", (unsigned int)&ioPro.sen.obt[3][1].obtcore.obtdatab);
		RS_printf("IO_PRO.SEN.OBT31.OBTCORE.OBTOFSR   = %x\n", (unsigned int)&ioPro.sen.obt[3][1].obtcore.obtofsr);
		RS_printf("IO_PRO.SEN.OBT31.OBTCORE.OBTOFSGR  = %x\n", (unsigned int)&ioPro.sen.obt[3][1].obtcore.obtofsgr);
		RS_printf("IO_PRO.SEN.OBT31.OBTCORE.OBTOFSGB  = %x\n", (unsigned int)&ioPro.sen.obt[3][1].obtcore.obtofsgb);
		RS_printf("IO_PRO.SEN.OBT31.OBTCORE.OBTOFSB   = %x\n", (unsigned int)&ioPro.sen.obt[3][1].obtcore.obtofsb);

		// P2M-0
		RS_printf("IO_PRO.SEN.P2M0.P2MTRG        = %x\n", (unsigned int)&ioPro.sen.p2m[0].p2mtrg);
		RS_printf("IO_PRO.SEN.P2M0.P2MPAEN       = %x\n", (unsigned int)&ioPro.sen.p2m[0].p2mpaen);
		RS_printf("IO_PRO.SEN.P2M0.P2MCTL        = %x\n", (unsigned int)&ioPro.sen.p2m[0].p2mctl);
		RS_printf("IO_PRO.SEN.P2M0.P2MOFS        = %x\n", (unsigned int)&ioPro.sen.p2m[0].p2mofs);
		RS_printf("IO_PRO.SEN.P2M0.PBSFT         = %x\n", (unsigned int)&ioPro.sen.p2m[0].pbsft);
		RS_printf("IO_PRO.SEN.P2M0.PCLPH         = %x\n", (unsigned int)&ioPro.sen.p2m[0].pclph);
		RS_printf("IO_PRO.SEN.P2M0.PTRMV         = %x\n", (unsigned int)&ioPro.sen.p2m[0].ptrmv);
		RS_printf("IO_PRO.SEN.P2M0.PTRMH         = %x\n", (unsigned int)&ioPro.sen.p2m[0].ptrmh);
		RS_printf("IO_PRO.SEN.P2M0.PTRMVW        = %x\n", (unsigned int)&ioPro.sen.p2m[0].ptrmvw);
		RS_printf("IO_PRO.SEN.P2M0.PTRMHW        = %x\n", (unsigned int)&ioPro.sen.p2m[0].ptrmhw);
		RS_printf("IO_PRO.SEN.P2M0.PTRMXVCYC     = %x\n", (unsigned int)&ioPro.sen.p2m[0].ptrmxvcyc);
		RS_printf("IO_PRO.SEN.P2M0.PTRMXHCYC     = %x\n", (unsigned int)&ioPro.sen.p2m[0].ptrmxhcyc);
		RS_printf("IO_PRO.SEN.P2M0.PTRMXVEN      = %x\n", (unsigned int)&ioPro.sen.p2m[0].ptrmxven);
		RS_printf("IO_PRO.SEN.P2M0.PTRMXHEN      = %x\n", (unsigned int)&ioPro.sen.p2m[0].ptrmxhen);
		RS_printf("IO_PRO.SEN.P2M0.P2MMIR        = %x\n", (unsigned int)&ioPro.sen.p2m[0].p2mmir);

		// P2M-1
		RS_printf("IO_PRO.SEN.P2M1.P2MTRG        = %x\n", (unsigned int)&ioPro.sen.p2m[1].p2mtrg);
		RS_printf("IO_PRO.SEN.P2M1.P2MPAEN       = %x\n", (unsigned int)&ioPro.sen.p2m[1].p2mpaen);
		RS_printf("IO_PRO.SEN.P2M1.P2MCTL        = %x\n", (unsigned int)&ioPro.sen.p2m[1].p2mctl);
		RS_printf("IO_PRO.SEN.P2M1.P2MOFS        = %x\n", (unsigned int)&ioPro.sen.p2m[1].p2mofs);
		RS_printf("IO_PRO.SEN.P2M1.PBSFT         = %x\n", (unsigned int)&ioPro.sen.p2m[1].pbsft);
		RS_printf("IO_PRO.SEN.P2M1.PCLPH         = %x\n", (unsigned int)&ioPro.sen.p2m[1].pclph);
		RS_printf("IO_PRO.SEN.P2M1.PTRMV         = %x\n", (unsigned int)&ioPro.sen.p2m[1].ptrmv);
		RS_printf("IO_PRO.SEN.P2M1.PTRMH         = %x\n", (unsigned int)&ioPro.sen.p2m[1].ptrmh);
		RS_printf("IO_PRO.SEN.P2M1.PTRMVW        = %x\n", (unsigned int)&ioPro.sen.p2m[1].ptrmvw);
		RS_printf("IO_PRO.SEN.P2M1.PTRMHW        = %x\n", (unsigned int)&ioPro.sen.p2m[1].ptrmhw);
		RS_printf("IO_PRO.SEN.P2M1.PTRMXVCYC     = %x\n", (unsigned int)&ioPro.sen.p2m[1].ptrmxvcyc);
		RS_printf("IO_PRO.SEN.P2M1.PTRMXHCYC     = %x\n", (unsigned int)&ioPro.sen.p2m[1].ptrmxhcyc);
		RS_printf("IO_PRO.SEN.P2M1.PTRMXVEN      = %x\n", (unsigned int)&ioPro.sen.p2m[1].ptrmxven);
		RS_printf("IO_PRO.SEN.P2M1.PTRMXHEN      = %x\n", (unsigned int)&ioPro.sen.p2m[1].ptrmxhen);
		RS_printf("IO_PRO.SEN.P2M1.P2MMIR        = %x\n", (unsigned int)&ioPro.sen.p2m[1].p2mmir);

		// P2M-2
		RS_printf("IO_PRO.SEN.P2M2.P2MTRG        = %x\n", (unsigned int)&ioPro.sen.p2m[2].p2mtrg);
		RS_printf("IO_PRO.SEN.P2M2.P2MPAEN       = %x\n", (unsigned int)&ioPro.sen.p2m[2].p2mpaen);
		RS_printf("IO_PRO.SEN.P2M2.P2MCTL        = %x\n", (unsigned int)&ioPro.sen.p2m[2].p2mctl);
		RS_printf("IO_PRO.SEN.P2M2.P2MOFS        = %x\n", (unsigned int)&ioPro.sen.p2m[2].p2mofs);
		RS_printf("IO_PRO.SEN.P2M2.PBSFT         = %x\n", (unsigned int)&ioPro.sen.p2m[2].pbsft);
		RS_printf("IO_PRO.SEN.P2M2.PCLPH         = %x\n", (unsigned int)&ioPro.sen.p2m[2].pclph);
		RS_printf("IO_PRO.SEN.P2M2.PTRMV         = %x\n", (unsigned int)&ioPro.sen.p2m[2].ptrmv);
		RS_printf("IO_PRO.SEN.P2M2.PTRMH         = %x\n", (unsigned int)&ioPro.sen.p2m[2].ptrmh);
		RS_printf("IO_PRO.SEN.P2M2.PTRMVW        = %x\n", (unsigned int)&ioPro.sen.p2m[2].ptrmvw);
		RS_printf("IO_PRO.SEN.P2M2.PTRMHW        = %x\n", (unsigned int)&ioPro.sen.p2m[2].ptrmhw);
		RS_printf("IO_PRO.SEN.P2M2.PTRMXVCYC     = %x\n", (unsigned int)&ioPro.sen.p2m[2].ptrmxvcyc);
		RS_printf("IO_PRO.SEN.P2M2.PTRMXHCYC     = %x\n", (unsigned int)&ioPro.sen.p2m[2].ptrmxhcyc);
		RS_printf("IO_PRO.SEN.P2M2.PTRMXVEN      = %x\n", (unsigned int)&ioPro.sen.p2m[2].ptrmxven);
		RS_printf("IO_PRO.SEN.P2M2.PTRMXHEN      = %x\n", (unsigned int)&ioPro.sen.p2m[2].ptrmxhen);
		RS_printf("IO_PRO.SEN.P2M2.P2MMIR        = %x\n", (unsigned int)&ioPro.sen.p2m[2].p2mmir);

		// P2M-3
		RS_printf("IO_PRO.SEN.P2M3.P2MTRG        = %x\n", (unsigned int)&ioPro.sen.p2m[3].p2mtrg);
		RS_printf("IO_PRO.SEN.P2M3.P2MPAEN       = %x\n", (unsigned int)&ioPro.sen.p2m[3].p2mpaen);
		RS_printf("IO_PRO.SEN.P2M3.P2MCTL        = %x\n", (unsigned int)&ioPro.sen.p2m[3].p2mctl);
		RS_printf("IO_PRO.SEN.P2M3.P2MOFS        = %x\n", (unsigned int)&ioPro.sen.p2m[3].p2mofs);
		RS_printf("IO_PRO.SEN.P2M3.PBSFT         = %x\n", (unsigned int)&ioPro.sen.p2m[3].pbsft);
		RS_printf("IO_PRO.SEN.P2M3.PCLPH         = %x\n", (unsigned int)&ioPro.sen.p2m[3].pclph);
		RS_printf("IO_PRO.SEN.P2M3.PTRMV         = %x\n", (unsigned int)&ioPro.sen.p2m[3].ptrmv);
		RS_printf("IO_PRO.SEN.P2M3.PTRMH         = %x\n", (unsigned int)&ioPro.sen.p2m[3].ptrmh);
		RS_printf("IO_PRO.SEN.P2M3.PTRMVW        = %x\n", (unsigned int)&ioPro.sen.p2m[3].ptrmvw);
		RS_printf("IO_PRO.SEN.P2M3.PTRMHW        = %x\n", (unsigned int)&ioPro.sen.p2m[3].ptrmhw);
		RS_printf("IO_PRO.SEN.P2M3.PTRMXVCYC     = %x\n", (unsigned int)&ioPro.sen.p2m[3].ptrmxvcyc);
		RS_printf("IO_PRO.SEN.P2M3.PTRMXHCYC     = %x\n", (unsigned int)&ioPro.sen.p2m[3].ptrmxhcyc);
		RS_printf("IO_PRO.SEN.P2M3.PTRMXVEN      = %x\n", (unsigned int)&ioPro.sen.p2m[3].ptrmxven);
		RS_printf("IO_PRO.SEN.P2M3.PTRMXHEN      = %x\n", (unsigned int)&ioPro.sen.p2m[3].ptrmxhen);
		RS_printf("IO_PRO.SEN.P2M3.P2MMIR        = %x\n", (unsigned int)&ioPro.sen.p2m[3].p2mmir);

		// P2M-4
		RS_printf("IO_PRO.SEN.P2M4.P2MTRG        = %x\n", (unsigned int)&ioPro.sen.p2m[4].p2mtrg);
		RS_printf("IO_PRO.SEN.P2M4.P2MPAEN       = %x\n", (unsigned int)&ioPro.sen.p2m[4].p2mpaen);
		RS_printf("IO_PRO.SEN.P2M4.P2MCTL        = %x\n", (unsigned int)&ioPro.sen.p2m[4].p2mctl);
		RS_printf("IO_PRO.SEN.P2M4.P2MOFS        = %x\n", (unsigned int)&ioPro.sen.p2m[4].p2mofs);
		RS_printf("IO_PRO.SEN.P2M4.PBSFT         = %x\n", (unsigned int)&ioPro.sen.p2m[4].pbsft);
		RS_printf("IO_PRO.SEN.P2M4.PCLPH         = %x\n", (unsigned int)&ioPro.sen.p2m[4].pclph);
		RS_printf("IO_PRO.SEN.P2M4.PTRMV         = %x\n", (unsigned int)&ioPro.sen.p2m[4].ptrmv);
		RS_printf("IO_PRO.SEN.P2M4.PTRMH         = %x\n", (unsigned int)&ioPro.sen.p2m[4].ptrmh);
		RS_printf("IO_PRO.SEN.P2M4.PTRMVW        = %x\n", (unsigned int)&ioPro.sen.p2m[4].ptrmvw);
		RS_printf("IO_PRO.SEN.P2M4.PTRMHW        = %x\n", (unsigned int)&ioPro.sen.p2m[4].ptrmhw);
		RS_printf("IO_PRO.SEN.P2M4.PTRMXVCYC     = %x\n", (unsigned int)&ioPro.sen.p2m[4].ptrmxvcyc);
		RS_printf("IO_PRO.SEN.P2M4.PTRMXHCYC     = %x\n", (unsigned int)&ioPro.sen.p2m[4].ptrmxhcyc);
		RS_printf("IO_PRO.SEN.P2M4.PTRMXVEN      = %x\n", (unsigned int)&ioPro.sen.p2m[4].ptrmxven);
		RS_printf("IO_PRO.SEN.P2M4.PTRMXHEN      = %x\n", (unsigned int)&ioPro.sen.p2m[4].ptrmxhen);
		RS_printf("IO_PRO.SEN.P2M4.P2MMIR        = %x\n", (unsigned int)&ioPro.sen.p2m[4].p2mmir);

		// P2M-5
		RS_printf("IO_PRO.SEN.P2M5.P2MTRG        = %x\n", (unsigned int)&ioPro.sen.p2m[5].p2mtrg);
		RS_printf("IO_PRO.SEN.P2M5.P2MPAEN       = %x\n", (unsigned int)&ioPro.sen.p2m[5].p2mpaen);
		RS_printf("IO_PRO.SEN.P2M5.P2MCTL        = %x\n", (unsigned int)&ioPro.sen.p2m[5].p2mctl);
		RS_printf("IO_PRO.SEN.P2M5.P2MOFS        = %x\n", (unsigned int)&ioPro.sen.p2m[5].p2mofs);
		RS_printf("IO_PRO.SEN.P2M5.PBSFT         = %x\n", (unsigned int)&ioPro.sen.p2m[5].pbsft);
		RS_printf("IO_PRO.SEN.P2M5.PCLPH         = %x\n", (unsigned int)&ioPro.sen.p2m[5].pclph);
		RS_printf("IO_PRO.SEN.P2M5.PTRMV         = %x\n", (unsigned int)&ioPro.sen.p2m[5].ptrmv);
		RS_printf("IO_PRO.SEN.P2M5.PTRMH         = %x\n", (unsigned int)&ioPro.sen.p2m[5].ptrmh);
		RS_printf("IO_PRO.SEN.P2M5.PTRMVW        = %x\n", (unsigned int)&ioPro.sen.p2m[5].ptrmvw);
		RS_printf("IO_PRO.SEN.P2M5.PTRMHW        = %x\n", (unsigned int)&ioPro.sen.p2m[5].ptrmhw);
		RS_printf("IO_PRO.SEN.P2M5.PTRMXVCYC     = %x\n", (unsigned int)&ioPro.sen.p2m[5].ptrmxvcyc);
		RS_printf("IO_PRO.SEN.P2M5.PTRMXHCYC     = %x\n", (unsigned int)&ioPro.sen.p2m[5].ptrmxhcyc);
		RS_printf("IO_PRO.SEN.P2M5.PTRMXVEN      = %x\n", (unsigned int)&ioPro.sen.p2m[5].ptrmxven);
		RS_printf("IO_PRO.SEN.P2M5.PTRMXHEN      = %x\n", (unsigned int)&ioPro.sen.p2m[5].ptrmxhen);
		RS_printf("IO_PRO.SEN.P2M5.P2MMIR        = %x\n", (unsigned int)&ioPro.sen.p2m[5].p2mmir);

		// P2M-6
		RS_printf("IO_PRO.SEN.P2M6.P2MTRG        = %x\n", (unsigned int)&ioPro.sen.p2m[6].p2mtrg);
		RS_printf("IO_PRO.SEN.P2M6.P2MPAEN       = %x\n", (unsigned int)&ioPro.sen.p2m[6].p2mpaen);
		RS_printf("IO_PRO.SEN.P2M6.P2MCTL        = %x\n", (unsigned int)&ioPro.sen.p2m[6].p2mctl);
		RS_printf("IO_PRO.SEN.P2M6.P2MOFS        = %x\n", (unsigned int)&ioPro.sen.p2m[6].p2mofs);
		RS_printf("IO_PRO.SEN.P2M6.PBSFT         = %x\n", (unsigned int)&ioPro.sen.p2m[6].pbsft);
		RS_printf("IO_PRO.SEN.P2M6.PCLPH         = %x\n", (unsigned int)&ioPro.sen.p2m[6].pclph);
		RS_printf("IO_PRO.SEN.P2M6.PTRMV         = %x\n", (unsigned int)&ioPro.sen.p2m[6].ptrmv);
		RS_printf("IO_PRO.SEN.P2M6.PTRMH         = %x\n", (unsigned int)&ioPro.sen.p2m[6].ptrmh);
		RS_printf("IO_PRO.SEN.P2M6.PTRMVW        = %x\n", (unsigned int)&ioPro.sen.p2m[6].ptrmvw);
		RS_printf("IO_PRO.SEN.P2M6.PTRMHW        = %x\n", (unsigned int)&ioPro.sen.p2m[6].ptrmhw);
		RS_printf("IO_PRO.SEN.P2M6.PTRMXVCYC     = %x\n", (unsigned int)&ioPro.sen.p2m[6].ptrmxvcyc);
		RS_printf("IO_PRO.SEN.P2M6.PTRMXHCYC     = %x\n", (unsigned int)&ioPro.sen.p2m[6].ptrmxhcyc);
		RS_printf("IO_PRO.SEN.P2M6.PTRMXVEN      = %x\n", (unsigned int)&ioPro.sen.p2m[6].ptrmxven);
		RS_printf("IO_PRO.SEN.P2M6.PTRMXHEN      = %x\n", (unsigned int)&ioPro.sen.p2m[6].ptrmxhen);
		RS_printf("IO_PRO.SEN.P2M6.P2MMIR        = %x\n", (unsigned int)&ioPro.sen.p2m[6].p2mmir);

		// P2M-7
		RS_printf("IO_PRO.SEN.P2M7.P2MTRG        = %x\n", (unsigned int)&ioPro.sen.p2m[7].p2mtrg);
		RS_printf("IO_PRO.SEN.P2M7.P2MPAEN       = %x\n", (unsigned int)&ioPro.sen.p2m[7].p2mpaen);
		RS_printf("IO_PRO.SEN.P2M7.P2MCTL        = %x\n", (unsigned int)&ioPro.sen.p2m[7].p2mctl);
		RS_printf("IO_PRO.SEN.P2M7.P2MOFS        = %x\n", (unsigned int)&ioPro.sen.p2m[7].p2mofs);
		RS_printf("IO_PRO.SEN.P2M7.PBSFT         = %x\n", (unsigned int)&ioPro.sen.p2m[7].pbsft);
		RS_printf("IO_PRO.SEN.P2M7.PCLPH         = %x\n", (unsigned int)&ioPro.sen.p2m[7].pclph);
		RS_printf("IO_PRO.SEN.P2M7.PTRMV         = %x\n", (unsigned int)&ioPro.sen.p2m[7].ptrmv);
		RS_printf("IO_PRO.SEN.P2M7.PTRMH         = %x\n", (unsigned int)&ioPro.sen.p2m[7].ptrmh);
		RS_printf("IO_PRO.SEN.P2M7.PTRMVW        = %x\n", (unsigned int)&ioPro.sen.p2m[7].ptrmvw);
		RS_printf("IO_PRO.SEN.P2M7.PTRMHW        = %x\n", (unsigned int)&ioPro.sen.p2m[7].ptrmhw);
		RS_printf("IO_PRO.SEN.P2M7.PTRMXVCYC     = %x\n", (unsigned int)&ioPro.sen.p2m[7].ptrmxvcyc);
		RS_printf("IO_PRO.SEN.P2M7.PTRMXHCYC     = %x\n", (unsigned int)&ioPro.sen.p2m[7].ptrmxhcyc);
		RS_printf("IO_PRO.SEN.P2M7.PTRMXVEN      = %x\n", (unsigned int)&ioPro.sen.p2m[7].ptrmxven);
		RS_printf("IO_PRO.SEN.P2M7.PTRMXHEN      = %x\n", (unsigned int)&ioPro.sen.p2m[7].ptrmxhen);
		RS_printf("IO_PRO.SEN.P2M7.P2MMIR        = %x\n", (unsigned int)&ioPro.sen.p2m[7].p2mmir);

		// PWCH-0
		RS_printf("IO_PRO.SEN.PWCH0.PWCHTRG      = %x\n", (unsigned int)&ioPro.sen.pwch[0].pwchtrg);
		RS_printf("IO_PRO.SEN.PWCH0.PWS          = %x\n", (unsigned int)&ioPro.sen.pwch[0].pws);
		RS_printf("IO_PRO.SEN.PWCH0.PWAXCTL      = %x\n", (unsigned int)&ioPro.sen.pwch[0].pwaxctl);
		RS_printf("IO_PRO.SEN.PWCH0.PWCHCTL      = %x\n", (unsigned int)&ioPro.sen.pwch[0].pwchctl);
		RS_printf("IO_PRO.SEN.PWCH0.PWCHINTENB   = %x\n", (unsigned int)&ioPro.sen.pwch[0].pwchintenb);
		RS_printf("IO_PRO.SEN.PWCH0.PWCHINTFLG   = %x\n", (unsigned int)&ioPro.sen.pwch[0].pwchintflg);
		RS_printf("IO_PRO.SEN.PWCH0.PWCHBRESP    = %x\n", (unsigned int)&ioPro.sen.pwch[0].pwchbresp);
		RS_printf("IO_PRO.SEN.PWCH0.PWSA         = %x\n", (unsigned int)&ioPro.sen.pwch[0].pwsa);
		RS_printf("IO_PRO.SEN.PWCH0.PWLSIZE      = %x\n", (unsigned int)&ioPro.sen.pwch[0].pwlsize);

		// PWCH-1
		RS_printf("IO_PRO.SEN.PWCH1.PWCHTRG      = %x\n", (unsigned int)&ioPro.sen.pwch[1].pwchtrg);
		RS_printf("IO_PRO.SEN.PWCH1.PWS          = %x\n", (unsigned int)&ioPro.SEN.pwch[1].pws);
		RS_printf("IO_PRO.SEN.PWCH1.PWAXCTL      = %x\n", (unsigned int)&ioPro.sen.pwch[1].pwaxctl);
		RS_printf("IO_PRO.SEN.PWCH1.PWCHCTL      = %x\n", (unsigned int)&ioPro.sen.pwch[1].pwchctl);
		RS_printf("IO_PRO.SEN.PWCH1.PWCHINTENB   = %x\n", (unsigned int)&ioPro.sen.pwch[1].pwchintenb);
		RS_printf("IO_PRO.SEN.PWCH1.PWCHINTFLG   = %x\n", (unsigned int)&ioPro.sen.pwch[1].pwchintflg);
		RS_printf("IO_PRO.SEN.PWCH1.PWCHBRESP    = %x\n", (unsigned int)&ioPro.sen.pwch[1].pwchbresp);
		RS_printf("IO_PRO.SEN.PWCH1.PWSA         = %x\n", (unsigned int)&ioPro.sen.pwch[1].pwsa);
		RS_printf("IO_PRO.SEN.PWCH1.PWLSIZE      = %x\n", (unsigned int)&ioPro.sen.pwch[1].pwlsize);

		// PWCH-2
		RS_printf("IO_PRO.SEN.PWCH2.PWCHTRG      = %x\n", (unsigned int)&ioPro.sen.pwch[2].pwchtrg);
		RS_printf("IO_PRO.SEN.PWCH2.PWS          = %x\n", (unsigned int)&ioPro.sen.pwch[2].pws);
		RS_printf("IO_PRO.SEN.PWCH2.PWAXCTL      = %x\n", (unsigned int)&ioPro.sen.pwch[2].pwaxctl);
		RS_printf("IO_PRO.SEN.PWCH2.PWCHCTL      = %x\n", (unsigned int)&ioPro.sen.pwch[2].pwchctl);
		RS_printf("IO_PRO.SEN.PWCH2.PWCHINTENB   = %x\n", (unsigned int)&ioPro.sen.pwch[2].pwchintenb);
		RS_printf("IO_PRO.SEN.PWCH2.PWCHINTFLG   = %x\n", (unsigned int)&ioPro.sen.pwch[2].pwchintflg);
		RS_printf("IO_PRO.SEN.PWCH2.PWCHBRESP    = %x\n", (unsigned int)&ioPro.sen.pwch[2].pwchbresp);
		RS_printf("IO_PRO.SEN.PWCH2.PWSA         = %x\n", (unsigned int)&ioPro.sen.pwch[2].pwsa);
		RS_printf("IO_PRO.SEN.PWCH2.PWLSIZE      = %x\n", (unsigned int)&ioPro.sen.pwch[2].pwlsize);

		// PWCH-3
		RS_printf("IO_PRO.SEN.PWCH3.PWCHTRG      = %x\n", (unsigned int)&ioPro.sen.pwch[3].pwchtrg);
		RS_printf("IO_PRO.SEN.PWCH3.PWS          = %x\n", (unsigned int)&ioPro.sen.pwch[3].pws);
		RS_printf("IO_PRO.SEN.PWCH3.PWAXCTL      = %x\n", (unsigned int)&ioPro.sen.pwch[3].pwaxctl);
		RS_printf("IO_PRO.SEN.PWCH3.PWCHCTL      = %x\n", (unsigned int)&ioPro.sen.pwch[3].pwchctl);
		RS_printf("IO_PRO.SEN.PWCH3.PWCHINTENB   = %x\n", (unsigned int)&ioPro.sen.pwch[3].pwchintenb);
		RS_printf("IO_PRO.SEN.PWCH3.PWCHINTFLG   = %x\n", (unsigned int)&ioPro.sen.pwch[3].pwchintflg);
		RS_printf("IO_PRO.SEN.PWCH3.PWCHBRESP    = %x\n", (unsigned int)&ioPro.sen.pwch[3].pwchbresp);
		RS_printf("IO_PRO.SEN.PWCH3.PWSA         = %x\n", (unsigned int)&ioPro.sen.pwch[3].pwsa);
		RS_printf("IO_PRO.SEN.PWCH3.PWLSIZE      = %x\n", (unsigned int)&ioPro.sen.pwch[3].pwlsize);

		// PWCH-4
		RS_printf("IO_PRO.SEN.PWCH4.PWCHTRG      = %x\n", (unsigned int)&ioPro.sen.pwch[4].pwchtrg);
		RS_printf("IO_PRO.SEN.PWCH4.PWS          = %x\n", (unsigned int)&ioPro.sen.pwch[4].pws);
		RS_printf("IO_PRO.SEN.PWCH4.PWAXCTL      = %x\n", (unsigned int)&ioPro.sen.pwch[4].pwaxctl);
		RS_printf("IO_PRO.SEN.PWCH4.PWCHCTL      = %x\n", (unsigned int)&ioPro.sen.pwch[4].pwchctl);
		RS_printf("IO_PRO.SEN.PWCH4.PWCHINTENB   = %x\n", (unsigned int)&ioPro.sen.pwch[4].pwchintenb);
		RS_printf("IO_PRO.SEN.PWCH4.PWCHINTFLG   = %x\n", (unsigned int)&ioPro.sen.pwch[4].pwchintflg);
		RS_printf("IO_PRO.SEN.PWCH4.PWCHBRESP    = %x\n", (unsigned int)&ioPro.sen.pwch[4].pwchbresp);
		RS_printf("IO_PRO.SEN.PWCH4.PWSA         = %x\n", (unsigned int)&ioPro.sen.pwch[4].pwsa);
		RS_printf("IO_PRO.SEN.PWCH4.PWLSIZE      = %x\n", (unsigned int)&ioPro.sen.pwch[4].pwlsize);

		// PWCH-5
		RS_printf("IO_PRO.SEN.PWCH5.PWCHTRG      = %x\n", (unsigned int)&ioPro.sen.pwch[5].pwchtrg);
		RS_printf("IO_PRO.SEN.PWCH5.PWS          = %x\n", (unsigned int)&ioPro.sen.pwch[5].pws);
		RS_printf("IO_PRO.SEN.PWCH5.PWAXCTL      = %x\n", (unsigned int)&ioPro.sen.pwch[5].pwaxctl);
		RS_printf("IO_PRO.SEN.PWCH5.PWCHCTL      = %x\n", (unsigned int)&ioPro.sen.pwch[5].pwchctl);
		RS_printf("IO_PRO.SEN.PWCH5.PWCHINTENB   = %x\n", (unsigned int)&ioPro.sen.pwch[5].pwchintenb);
		RS_printf("IO_PRO.SEN.PWCH5.PWCHINTFLG   = %x\n", (unsigned int)&ioPro.sen.pwch[5].pwchintflg);
		RS_printf("IO_PRO.SEN.PWCH5.PWCHBRESP    = %x\n", (unsigned int)&ioPro.sen.pwch[5].pwchbresp);
		RS_printf("IO_PRO.SEN.PWCH5.PWSA         = %x\n", (unsigned int)&ioPro.sen.pwch[5].pwsa);
		RS_printf("IO_PRO.SEN.PWCH5.PWLSIZE      = %x\n", (unsigned int)&ioPro.sen.pwch[5].pwlsize);

		// PWCH-6
		RS_printf("IO_PRO.SEN.PWCH6.PWCHTRG      = %x\n", (unsigned int)&ioPro.sen.pwch[6].pwchtrg);
		RS_printf("IO_PRO.SEN.PWCH6.PWS          = %x\n", (unsigned int)&ioPro.sen.pwch[6].pws);
		RS_printf("IO_PRO.SEN.PWCH6.PWAXCTL      = %x\n", (unsigned int)&ioPro.sen.pwch[6].pwaxctl);
		RS_printf("IO_PRO.SEN.PWCH6.PWCHCTL      = %x\n", (unsigned int)&ioPro.sen.pwch[6].pwchctl);
		RS_printf("IO_PRO.SEN.PWCH6.PWCHINTENB   = %x\n", (unsigned int)&ioPro.sen.pwch[6].pwchintenb);
		RS_printf("IO_PRO.SEN.PWCH6.PWCHINTFLG   = %x\n", (unsigned int)&ioPro.sen.pwch[6].pwchintflg);
		RS_printf("IO_PRO.SEN.PWCH6.PWCHBRESP    = %x\n", (unsigned int)&ioPro.sen.pwch[6].pwchbresp);
		RS_printf("IO_PRO.SEN.PWCH6.PWSA         = %x\n", (unsigned int)&ioPro.sen.pwch[6].pwsa);
		RS_printf("IO_PRO.SEN.PWCH6.PWLSIZE      = %x\n", (unsigned int)&ioPro.sen.pwch[6].pwlsize);

		// PWCH-7
		RS_printf("IO_PRO.SEN.PWCH7.PWCHTRG      = %x\n", (unsigned int)&ioPro.sen.pwch[7].pwchtrg);
		RS_printf("IO_PRO.SEN.PWCH7.PWS          = %x\n", (unsigned int)&ioPro.sen.pwch[7].pws);
		RS_printf("IO_PRO.SEN.PWCH7.PWAXCTL      = %x\n", (unsigned int)&ioPro.sen.pwch[7].pwaxctl);
		RS_printf("IO_PRO.SEN.PWCH7.PWCHCTL      = %x\n", (unsigned int)&ioPro.sen.pwch[7].pwchctl);
		RS_printf("IO_PRO.SEN.PWCH7.PWCHINTENB   = %x\n", (unsigned int)&ioPro.sen.pwch[7].pwchintenb);
		RS_printf("IO_PRO.SEN.PWCH7.PWCHINTFLG   = %x\n", (unsigned int)&ioPro.sen.pwch[7].pwchintflg);
		RS_printf("IO_PRO.SEN.PWCH7.PWCHBRESP    = %x\n", (unsigned int)&ioPro.sen.pwch[7].pwchbresp);
		RS_printf("IO_PRO.SEN.PWCH7.PWSA         = %x\n", (unsigned int)&ioPro.sen.pwch[7].pwsa);
		RS_printf("IO_PRO.SEN.PWCH7.PWLSIZE      = %x\n", (unsigned int)&ioPro.sen.pwch[7].pwlsize);
	}

#endif	/** SEN Unit **/
#endif /* if 0 */

}

ProTest2* pro_test2_new(void)
{
	ProTest2* self = k_object_new_with_private(PRO_TYPE_TEST2, sizeof(ProTest2Private));

	return self;
}
