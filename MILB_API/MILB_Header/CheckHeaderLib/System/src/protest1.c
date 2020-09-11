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
#include "protest1.h"


K_TYPE_DEFINE_WITH_PRIVATE(ProTest1, pro_test1)
#define PRO_TEST1_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), ProTest1Private, PRO_TYPE_TEST1))


struct _ProTest1Private
{
	int a;
};


/*DECLS*/


/*IMPL*/
static void pro_test1_constructor(ProTest1 *self)
{
	ProTest1Private *priv = PRO_TEST1_GET_PRIVATE(self);
}

static void pro_test1_destructor(ProTest1 *self)
{
	ProTest1Private *priv = PRO_TEST1_GET_PRIVATE(self);
}


/*PUBLIC*/
void pro_test1(ProTest1 *self, EProBlockType type, IoPro ioPro)
{

#if 0
#ifdef D_ENABLE_IO_PRO_SEN	/** SEN Unit **/

	if(type == E_PRO_BLOCK_TYPE_SEN) {

		// SENTOP
		RS_printf("IO_PRO.SEN.SENTOP.SR          = %x\n", (unsigned int)&ioPro.sen.sentop.sr);
		RS_printf("IO_PRO.SEN.SENTOP.CLKSTP      = %x\n", (unsigned int)&ioPro.sen.sentop.clkstp);
		RS_printf("IO_PRO.SEN.SENTOP.SENTOPCTL1  = %x\n", (unsigned int)&ioPro.sen.sentop.sentopctl1);
		RS_printf("IO_PRO.SEN.SENTOP.SENTOPCTL2  = %x\n", (unsigned int)&ioPro.sen.sentop.sentopctl2);
		RS_printf("IO_PRO.SEN.SENTOP.BSCTL       = %x\n", (unsigned int)&ioPro.sen.sentop.bsctl);
		RS_printf("IO_PRO.SEN.SENTOP.INTMON1     = %x\n", (unsigned int)&ioPro.sen.sentop.intmon1);
		RS_printf("IO_PRO.SEN.SENTOP.INTMON2     = %x\n", (unsigned int)&ioPro.sen.sentop.intmon2);
		RS_printf("IO_PRO.SEN.SENTOP.INTCTL      = %x\n", (unsigned int)&ioPro.sen.sentop.intctl);
		RS_printf("IO_PRO.SEN.SENTOP.VHDINTENB   = %x\n", (unsigned int)&ioPro.sen.sentop.vhdintenb);
		RS_printf("IO_PRO.SEN.SENTOP.VHDINTFLG   = %x\n", (unsigned int)&ioPro.sen.sentop.vhdintflg);
		RS_printf("IO_PRO.SEN.SENTOP.VHSET0      = %x\n", (unsigned int)&ioPro.sen.sentop.vhset0);
		RS_printf("IO_PRO.SEN.SENTOP.VHSET1      = %x\n", (unsigned int)&ioPro.sen.sentop.vhset1);
		RS_printf("IO_PRO.SEN.SENTOP.VHSET2      = %x\n", (unsigned int)&ioPro.sen.sentop.vhset2);
		RS_printf("IO_PRO.SEN.SENTOP.VHSET3      = %x\n", (unsigned int)&ioPro.sen.sentop.vhset3);
		RS_printf("IO_PRO.SEN.SENTOP.VMIVADR     = %x\n", (unsigned int)&ioPro.sen.sentop.vmivadr);
		RS_printf("IO_PRO.SEN.SENTOP.VMIHADR     = %x\n", (unsigned int)&ioPro.sen.sentop.vmihadr);
		RS_printf("IO_PRO.SEN.SENTOP.HMIHADR     = %x\n", (unsigned int)&ioPro.sen.sentop.hmihadr);
		RS_printf("IO_PRO.SEN.SENTOP.SGVHDINTENB = %x\n", (unsigned int)&ioPro.sen.sentop.sgvhdintenb);
		RS_printf("IO_PRO.SEN.SENTOP.SGVHDINTFLG = %x\n", (unsigned int)&ioPro.sen.sentop.sgvhdintflg);
		RS_printf("IO_PRO.SEN.SENTOP.VHDSGCTL    = %x\n", (unsigned int)&ioPro.sen.sentop.vhdsgctl);
		RS_printf("IO_PRO.SEN.SENTOP.OBTCDCSET   = %x\n", (unsigned int)&ioPro.sen.sentop.obtcdcset);
		RS_printf("IO_PRO.SEN.SENTOP.OBTCDCCTL1  = %x\n", (unsigned int)&ioPro.sen.sentop.obtcdcctl1);
		RS_printf("IO_PRO.SEN.SENTOP.OBTCDCCTL2  = %x\n", (unsigned int)&ioPro.sen.sentop.obtcdcctl2);
		RS_printf("IO_PRO.SEN.SENTOP.LVDSCTL     = %x\n", (unsigned int)&ioPro.sen.sentop.lvdsctl);
		RS_printf("IO_PRO.SEN.SENTOP.SLVSECCTL   = %x\n", (unsigned int)&ioPro.sen.sentop.slvsecctl);
		RS_printf("IO_PRO.SEN.SENTOP.SGOUTCTL    = %x\n", (unsigned int)&ioPro.sen.sentop.sgoutctl);
		RS_printf("IO_PRO.SEN.SENTOP.GINTENB     = %x\n", (unsigned int)&ioPro.sen.sentop.gintenb);
		RS_printf("IO_PRO.SEN.SENTOP.GINTFLG     = %x\n", (unsigned int)&ioPro.sen.sentop.gintflg);
		RS_printf("IO_PRO.SEN.SENTOP.GSET0       = %x\n", (unsigned int)&ioPro.sen.sentop.gset0);
		RS_printf("IO_PRO.SEN.SENTOP.GSET1       = %x\n", (unsigned int)&ioPro.sen.sentop.gset1);
		RS_printf("IO_PRO.SEN.SENTOP.GSET2       = %x\n", (unsigned int)&ioPro.sen.sentop.gset2);
		RS_printf("IO_PRO.SEN.SENTOP.GSET3       = %x\n", (unsigned int)&ioPro.sen.sentop.gset3);
		RS_printf("IO_PRO.SEN.SENTOP.GVADR       = %x\n", (unsigned int)&ioPro.sen.sentop.gvadr);
		RS_printf("IO_PRO.SEN.SENTOP.GHADR       = %x\n", (unsigned int)&ioPro.sen.sentop.ghadr);
		RS_printf("IO_PRO.SEN.SENTOP.PHYCIFCTL   = %x\n", (unsigned int)&ioPro.sen.sentop.phycifctl);
		RS_printf("IO_PRO.SEN.SENTOP.PHY0CLKCTL  = %x\n", (unsigned int)&ioPro.sen.sentop.phy0clkctl);
		RS_printf("IO_PRO.SEN.SENTOP.PHY1CLKCTL  = %x\n", (unsigned int)&ioPro.sen.sentop.phy1clkctl);
		RS_printf("IO_PRO.SEN.SENTOP.PHY2CLKCTL  = %x\n", (unsigned int)&ioPro.sen.sentop.phy2clkctl);
		RS_printf("IO_PRO.SEN.SENTOP.PHY3CLKCTL  = %x\n", (unsigned int)&ioPro.sen.sentop.phy3clkctl);
		RS_printf("IO_PRO.SEN.SENTOP.PHY0MDCTL   = %x\n", (unsigned int)&ioPro.sen.sentop.phy0mdctl);
		RS_printf("IO_PRO.SEN.SENTOP.PHY1MDCTL   = %x\n", (unsigned int)&ioPro.sen.sentop.phy1mdctl);
		RS_printf("IO_PRO.SEN.SENTOP.PHY2MDCTL   = %x\n", (unsigned int)&ioPro.sen.sentop.phy2mdctl);
		RS_printf("IO_PRO.SEN.SENTOP.PHY3MDCTL   = %x\n", (unsigned int)&ioPro.sen.sentop.phy3mdctl);
		RS_printf("IO_PRO.SEN.SENTOP.PHY0MDCPCTL = %x\n", (unsigned int)&ioPro.sen.sentop.phy0mdcpctl);
		RS_printf("IO_PRO.SEN.SENTOP.PHY1MDCPCTL = %x\n", (unsigned int)&ioPro.sen.sentop.phy1mdcpctl);
		RS_printf("IO_PRO.SEN.SENTOP.PHY2MDCPCTL = %x\n", (unsigned int)&ioPro.sen.sentop.phy2mdcpctl);
		RS_printf("IO_PRO.SEN.SENTOP.PHY3MDCPCTL = %x\n", (unsigned int)&ioPro.sen.sentop.phy3mdcpctl);
		RS_printf("IO_PRO.SEN.SENTOP.PHY0DLCTL   = %x\n", (unsigned int)&ioPro.sen.sentop.phy0dlctl);
		RS_printf("IO_PRO.SEN.SENTOP.PHY1DLCTL   = %x\n", (unsigned int)&ioPro.sen.sentop.phy1dlctl);
		RS_printf("IO_PRO.SEN.SENTOP.PHY2DLCTL   = %x\n", (unsigned int)&ioPro.sen.sentop.phy2dlctl);
		RS_printf("IO_PRO.SEN.SENTOP.PHY3DLCTL   = %x\n", (unsigned int)&ioPro.sen.sentop.phy3dlctl);
		RS_printf("IO_PRO.SEN.SENTOP.PHY0IFCTL   = %x\n", (unsigned int)&ioPro.sen.sentop.phy0ifctl);
		RS_printf("IO_PRO.SEN.SENTOP.PHY1IFCTL   = %x\n", (unsigned int)&ioPro.sen.sentop.phy1ifctl);
		RS_printf("IO_PRO.SEN.SENTOP.PHY2IFCTL   = %x\n", (unsigned int)&ioPro.sen.sentop.phy2ifctl);
		RS_printf("IO_PRO.SEN.SENTOP.PHY3IFCTL   = %x\n", (unsigned int)&ioPro.sen.sentop.phy3ifctl);
		RS_printf("IO_PRO.SEN.SENTOP.PHY0DSKCTL  = %x\n", (unsigned int)&ioPro.sen.sentop.phy0dskctl);
		RS_printf("IO_PRO.SEN.SENTOP.PHY1DSKCTL  = %x\n", (unsigned int)&ioPro.sen.sentop.phy1dskctl);
		RS_printf("IO_PRO.SEN.SENTOP.PHY2DSKCTL  = %x\n", (unsigned int)&ioPro.sen.sentop.phy2dskctl);
		RS_printf("IO_PRO.SEN.SENTOP.PHY3DSKCTL  = %x\n", (unsigned int)&ioPro.sen.sentop.phy3dskctl);
		RS_printf("IO_PRO.SEN.SENTOP.PLL0CTL     = %x\n", (unsigned int)&ioPro.sen.sentop.pll0ctl);
		RS_printf("IO_PRO.SEN.SENTOP.BIASCTL     = %x\n", (unsigned int)&ioPro.sen.sentop.biasctl);
		RS_printf("IO_PRO.SEN.SENTOP.PHY0DSKMONI = %x\n", (unsigned int)&ioPro.sen.sentop.phy0dskmoni);
		RS_printf("IO_PRO.SEN.SENTOP.PHY1DSKMONI = %x\n", (unsigned int)&ioPro.sen.sentop.phy1dskmoni);
		RS_printf("IO_PRO.SEN.SENTOP.PHY2DSKMONI = %x\n", (unsigned int)&ioPro.sen.sentop.phy2dskmoni);
		RS_printf("IO_PRO.SEN.SENTOP.PHY3DSKMONI = %x\n", (unsigned int)&ioPro.sen.sentop.phy3dskmoni);
		RS_printf("IO_PRO.SEN.SENTOP.PHY0DLMONI  = %x\n", (unsigned int)&ioPro.sen.sentop.phy0dlmoni);
		RS_printf("IO_PRO.SEN.SENTOP.PHY1DLMONI  = %x\n", (unsigned int)&ioPro.sen.sentop.phy1dlmoni);
		RS_printf("IO_PRO.SEN.SENTOP.PHY2DLMONI  = %x\n", (unsigned int)&ioPro.sen.sentop.phy2dlmoni);
		RS_printf("IO_PRO.SEN.SENTOP.PHY3DLMONI  = %x\n", (unsigned int)&ioPro.sen.sentop.phy3dlmoni);
		RS_printf("IO_PRO.SEN.SENTOP.PHYCMONI    = %x\n", (unsigned int)&ioPro.sen.sentop.phycmoni);

		// SG-0
		RS_printf("IO_PRO.SEN.SG0.SGTRG         = %x\n", (unsigned int)&ioPro.sen.sg[0].sgtrg);
		RS_printf("IO_PRO.SEN.SG0.SGCTL1        = %x\n", (unsigned int)&ioPro.sen.sg[0].sgctl1);
		RS_printf("IO_PRO.SEN.SG0.SGCTL2        = %x\n", (unsigned int)&ioPro.sen.sg[0].sgctl2);
		RS_printf("IO_PRO.SEN.SG0.VDOCYC        = %x\n", (unsigned int)&ioPro.sen.sg[0].vdocyc);
		RS_printf("IO_PRO.SEN.SG0.VDOW          = %x\n", (unsigned int)&ioPro.sen.sg[0].vdow);
		RS_printf("IO_PRO.SEN.SG0.HDOCYC        = %x\n", (unsigned int)&ioPro.sen.sg[0].hdocyc);
		RS_printf("IO_PRO.SEN.SG0.HDOW          = %x\n", (unsigned int)&ioPro.sen.sg[0].hdow);
		RS_printf("IO_PRO.SEN.SG0.HDOCYC2       = %x\n", (unsigned int)&ioPro.sen.sg[0].hdocyc2);
		RS_printf("IO_PRO.SEN.SG0.HDOW2         = %x\n", (unsigned int)&ioPro.sen.sg[0].hdow2);
		RS_printf("IO_PRO.SEN.SG0.VDHDMON       = %x\n", (unsigned int)&ioPro.sen.sg[0].vdhdmon);

		// SG-1
		RS_printf("IO_PRO.SEN.SG1.SGTRG         = %x\n", (unsigned int)&ioPro.sen.sg[1].sgtrg);
		RS_printf("IO_PRO.SEN.SG1.SGCTL1        = %x\n", (unsigned int)&ioPro.sen.sg[1].sgctl1);
		RS_printf("IO_PRO.SEN.SG1.SGCTL2        = %x\n", (unsigned int)&ioPro.sen.sg[1].sgctl2);
		RS_printf("IO_PRO.SEN.SG1.VDOCYC        = %x\n", (unsigned int)&ioPro.sen.sg[1].vdocyc);
		RS_printf("IO_PRO.SEN.SG1.VDOW          = %x\n", (unsigned int)&ioPro.sen.sg[1].vdow);
		RS_printf("IO_PRO.SEN.SG1.HDOCYC        = %x\n", (unsigned int)&ioPro.sen.sg[1].hdocyc);
		RS_printf("IO_PRO.SEN.SG1.HDOW          = %x\n", (unsigned int)&ioPro.sen.sg[1].hdow);
		RS_printf("IO_PRO.SEN.SG1.HDOCYC2       = %x\n", (unsigned int)&ioPro.sen.sg[1].hdocyc2);
		RS_printf("IO_PRO.SEN.SG1.HDOW2         = %x\n", (unsigned int)&ioPro.sen.sg[1].hdow2);
		RS_printf("IO_PRO.SEN.SG1.VDHDMON       = %x\n", (unsigned int)&ioPro.sen.sg[1].vdhdmon);

		// SG-2
		RS_printf("IO_PRO.SEN.SG2.SGTRG         = %x\n", (unsigned int)&ioPro.sen.sg[2].sgtrg);
		RS_printf("IO_PRO.SEN.SG2.SGCTL1        = %x\n", (unsigned int)&ioPro.sen.sg[2].sgctl1);
		RS_printf("IO_PRO.SEN.SG2.SGCTL2        = %x\n", (unsigned int)&ioPro.sen.sg[2].sgctl2);
		RS_printf("IO_PRO.SEN.SG2.VDOCYC        = %x\n", (unsigned int)&ioPro.sen.sg[2].vdocyc);
		RS_printf("IO_PRO.SEN.SG2.VDOW          = %x\n", (unsigned int)&ioPro.sen.sg[2].vdow);
		RS_printf("IO_PRO.SEN.SG2.HDOCYC        = %x\n", (unsigned int)&ioPro.sen.sg[2].hdocyc);
		RS_printf("IO_PRO.SEN.SG2.HDOW          = %x\n", (unsigned int)&ioPro.sen.sg[2].hdow);
		RS_printf("IO_PRO.SEN.SG2.HDOCYC2       = %x\n", (unsigned int)&ioPro.sen.sg[2].hdocyc2);
		RS_printf("IO_PRO.SEN.SG2.HDOW2         = %x\n", (unsigned int)&ioPro.sen.sg[2].hdow2);
		RS_printf("IO_PRO.SEN.SG2.VDHDMON       = %x\n", (unsigned int)&ioPro.sen.sg[2].vdhdmon);

		// SG-3
		RS_printf("IO_PRO.SEN.SG3.SGTRG         = %x\n", (unsigned int)&ioPro.sen.sg[3].sgtrg);
		RS_printf("IO_PRO.SEN.SG3.SGCTL1        = %x\n", (unsigned int)&ioPro.sen.sg[3].sgctl1);
		RS_printf("IO_PRO.SEN.SG3.SGCTL2        = %x\n", (unsigned int)&ioPro.sen.sg[3].sgctl2);
		RS_printf("IO_PRO.SEN.SG3.VDOCYC        = %x\n", (unsigned int)&ioPro.sen.sg[3].vdocyc);
		RS_printf("IO_PRO.SEN.SG3.VDOW          = %x\n", (unsigned int)&ioPro.sen.sg[3].vdow);
		RS_printf("IO_PRO.SEN.SG3.HDOCYC        = %x\n", (unsigned int)&ioPro.sen.sg[3].hdocyc);
		RS_printf("IO_PRO.SEN.SG3.HDOW          = %x\n", (unsigned int)&ioPro.sen.sg[3].hdow);
		RS_printf("IO_PRO.SEN.SG3.HDOCYC2       = %x\n", (unsigned int)&ioPro.sen.sg[3].hdocyc2);
		RS_printf("IO_PRO.SEN.SG3.HDOW2         = %x\n", (unsigned int)&ioPro.sen.sg[3].hdow2);
		RS_printf("IO_PRO.SEN.SG3.VDHDMON       = %x\n", (unsigned int)&ioPro.sen.sg[3].vdhdmon);

		// LVDS-0
		RS_printf("IO_PRO.SEN.LVDS0.LVDSTRG      = %x\n", (unsigned int)&ioPro.sen.lvds[0].lvdstrg);
		RS_printf("IO_PRO.SEN.LVDS0.LVDSINTENB0  = %x\n", (unsigned int)&ioPro.sen.lvds[0].lvdsintenb0);
		RS_printf("IO_PRO.SEN.LVDS0.LVDSINTENB1  = %x\n", (unsigned int)&ioPro.sen.lvds[0].lvdsintenb1);
		RS_printf("IO_PRO.SEN.LVDS0.LVDSINTENB2  = %x\n", (unsigned int)&ioPro.sen.lvds[0].lvdsintenb2);
		RS_printf("IO_PRO.SEN.LVDS0.LVDSINTFLG0  = %x\n", (unsigned int)&ioPro.sen.lvds[0].lvdsintflg0);
		RS_printf("IO_PRO.SEN.LVDS0.LVDSINTFLG1  = %x\n", (unsigned int)&ioPro.sen.lvds[0].lvdsintflg1);
		RS_printf("IO_PRO.SEN.LVDS0.LVDSINTFLG2  = %x\n", (unsigned int)&ioPro.sen.lvds[0].lvdsintflg2);
		RS_printf("IO_PRO.SEN.LVDS0.LVDSINTADR0  = %x\n", (unsigned int)&ioPro.sen.lvds[0].lvdsintadr0);
		RS_printf("IO_PRO.SEN.LVDS0.LVDSINTADR1  = %x\n", (unsigned int)&ioPro.sen.lvds[0].lvdsintadr1);
		RS_printf("IO_PRO.SEN.LVDS0.LVDSINTADR2  = %x\n", (unsigned int)&ioPro.sen.lvds[0].lvdsintadr2);
		RS_printf("IO_PRO.SEN.LVDS0.LVDSINTSET0  = %x\n", (unsigned int)&ioPro.sen.lvds[0].lvdsintset0);
		RS_printf("IO_PRO.SEN.LVDS0.LVDSINTSET1  = %x\n", (unsigned int)&ioPro.sen.lvds[0].lvdsintset1);
		RS_printf("IO_PRO.SEN.LVDS0.LVDSINTSET2  = %x\n", (unsigned int)&ioPro.sen.lvds[0].lvdsintset2);
		RS_printf("IO_PRO.SEN.LVDS0.LVDSCTL1     = %x\n", (unsigned int)&ioPro.sen.lvds[0].lvdsctl1);
		RS_printf("IO_PRO.SEN.LVDS0.LVDSCTL2     = %x\n", (unsigned int)&ioPro.sen.lvds[0].lvdsctl2);
		RS_printf("IO_PRO.SEN.LVDS0.LVDSCLKS     = %x\n", (unsigned int)&ioPro.sen.lvds[0].lvdsclks);
		RS_printf("IO_PRO.SEN.LVDS0.LVDSDATS     = %x\n", (unsigned int)&ioPro.sen.lvds[0].lvdsdats);
		RS_printf("IO_PRO.SEN.LVDS0.LHSADD       = %x\n", (unsigned int)&ioPro.sen.lvds[0].lhsadd);
		RS_printf("IO_PRO.SEN.LVDS0.LHSIZE       = %x\n", (unsigned int)&ioPro.sen.lvds[0].lhsize);
		RS_printf("IO_PRO.SEN.LVDS0.SYNCSEL      = %x\n", (unsigned int)&ioPro.sen.lvds[0].syncsel);
		RS_printf("IO_PRO.SEN.LVDS0.LPDCHG       = %x\n", (unsigned int)&ioPro.sen.lvds[0].lpdchg);
		RS_printf("IO_PRO.SEN.LVDS0.SAV0         = %x\n", (unsigned int)&ioPro.sen.lvds[0].sav0);
		RS_printf("IO_PRO.SEN.LVDS0.SAV1         = %x\n", (unsigned int)&ioPro.sen.lvds[0].sav1);
		RS_printf("IO_PRO.SEN.LVDS0.SAV2         = %x\n", (unsigned int)&ioPro.sen.lvds[0].sav2);
		RS_printf("IO_PRO.SEN.LVDS0.EAV0         = %x\n", (unsigned int)&ioPro.sen.lvds[0].eav0);
		RS_printf("IO_PRO.SEN.LVDS0.EAV1         = %x\n", (unsigned int)&ioPro.sen.lvds[0].eav1);
		RS_printf("IO_PRO.SEN.LVDS0.EAV2         = %x\n", (unsigned int)&ioPro.sen.lvds[0].eav2);
		RS_printf("IO_PRO.SEN.LVDS0.SAB0         = %x\n", (unsigned int)&ioPro.sen.lvds[0].sab0);
		RS_printf("IO_PRO.SEN.LVDS0.SAB1         = %x\n", (unsigned int)&ioPro.sen.lvds[0].sab1);
		RS_printf("IO_PRO.SEN.LVDS0.SAB2         = %x\n", (unsigned int)&ioPro.sen.lvds[0].sab2);
		RS_printf("IO_PRO.SEN.LVDS0.EAB0         = %x\n", (unsigned int)&ioPro.sen.lvds[0].eab0);
		RS_printf("IO_PRO.SEN.LVDS0.EAB1         = %x\n", (unsigned int)&ioPro.sen.lvds[0].eab1);
		RS_printf("IO_PRO.SEN.LVDS0.EAB2         = %x\n", (unsigned int)&ioPro.sen.lvds[0].eab2);
		RS_printf("IO_PRO.SEN.LVDS0.MSAV0        = %x\n", (unsigned int)&ioPro.sen.lvds[0].msav0);
		RS_printf("IO_PRO.SEN.LVDS0.MSAV1        = %x\n", (unsigned int)&ioPro.sen.lvds[0].msav1);
		RS_printf("IO_PRO.SEN.LVDS0.MSAV2        = %x\n", (unsigned int)&ioPro.sen.lvds[0].msav2);
		RS_printf("IO_PRO.SEN.LVDS0.MEAV0        = %x\n", (unsigned int)&ioPro.sen.lvds[0].meav0);
		RS_printf("IO_PRO.SEN.LVDS0.MEAV1        = %x\n", (unsigned int)&ioPro.sen.lvds[0].meav1);
		RS_printf("IO_PRO.SEN.LVDS0.MEAV2        = %x\n", (unsigned int)&ioPro.sen.lvds[0].meav2);
		RS_printf("IO_PRO.SEN.LVDS0.MSAB0        = %x\n", (unsigned int)&ioPro.sen.lvds[0].msab0);
		RS_printf("IO_PRO.SEN.LVDS0.MSAB1        = %x\n", (unsigned int)&ioPro.sen.lvds[0].msab1);
		RS_printf("IO_PRO.SEN.LVDS0.MSAB2        = %x\n", (unsigned int)&ioPro.sen.lvds[0].msab2);
		RS_printf("IO_PRO.SEN.LVDS0.MEAB0        = %x\n", (unsigned int)&ioPro.sen.lvds[0].meab0);
		RS_printf("IO_PRO.SEN.LVDS0.MEAB1        = %x\n", (unsigned int)&ioPro.sen.lvds[0].meab1);
		RS_printf("IO_PRO.SEN.LVDS0.MEAB2        = %x\n", (unsigned int)&ioPro.sen.lvds[0].meab2);
		RS_printf("IO_PRO.SEN.LVDS0.LVDSPAEN     = %x\n", (unsigned int)&ioPro.sen.lvds[0].lvdspaen);

		// LVDS-1
		RS_printf("IO_PRO.SEN.LVDS1.LVDSTRG      = %x\n", (unsigned int)&ioPro.sen.lvds[1].lvdstrg);
		RS_printf("IO_PRO.SEN.LVDS1.LVDSINTENB0  = %x\n", (unsigned int)&ioPro.sen.lvds[1].lvdsintenb0);
		RS_printf("IO_PRO.SEN.LVDS1.LVDSINTENB1  = %x\n", (unsigned int)&ioPro.sen.lvds[1].lvdsintenb1);
		RS_printf("IO_PRO.SEN.LVDS1.LVDSINTENB2  = %x\n", (unsigned int)&ioPro.sen.lvds[1].lvdsintenb2);
		RS_printf("IO_PRO.SEN.LVDS1.LVDSINTFLG0  = %x\n", (unsigned int)&ioPro.sen.lvds[1].lvdsintflg0);
		RS_printf("IO_PRO.SEN.LVDS1.LVDSINTFLG1  = %x\n", (unsigned int)&ioPro.sen.lvds[1].lvdsintflg1);
		RS_printf("IO_PRO.SEN.LVDS1.LVDSINTFLG2  = %x\n", (unsigned int)&ioPro.sen.lvds[1].lvdsintflg2);
		RS_printf("IO_PRO.SEN.LVDS1.LVDSINTADR0  = %x\n", (unsigned int)&ioPro.sen.lvds[1].lvdsintadr0);
		RS_printf("IO_PRO.SEN.LVDS1.LVDSINTADR1  = %x\n", (unsigned int)&ioPro.sen.lvds[1].lvdsintadr1);
		RS_printf("IO_PRO.SEN.LVDS1.LVDSINTADR2  = %x\n", (unsigned int)&ioPro.sen.lvds[1].lvdsintadr2);
		RS_printf("IO_PRO.SEN.LVDS1.LVDSINTSET0  = %x\n", (unsigned int)&ioPro.sen.lvds[1].lvdsintset0);
		RS_printf("IO_PRO.SEN.LVDS1.LVDSINTSET1  = %x\n", (unsigned int)&ioPro.sen.lvds[1].lvdsintset1);
		RS_printf("IO_PRO.SEN.LVDS1.LVDSINTSET2  = %x\n", (unsigned int)&ioPro.sen.lvds[1].lvdsintset2);
		RS_printf("IO_PRO.SEN.LVDS1.LVDSCTL1     = %x\n", (unsigned int)&ioPro.sen.lvds[1].lvdsctl1);
		RS_printf("IO_PRO.SEN.LVDS1.LVDSCTL2     = %x\n", (unsigned int)&ioPro.sen.lvds[1].lvdsctl2);
		RS_printf("IO_PRO.SEN.LVDS1.LVDSCLKS     = %x\n", (unsigned int)&ioPro.sen.lvds[1].lvdsclks);
		RS_printf("IO_PRO.SEN.LVDS1.LVDSDATS     = %x\n", (unsigned int)&ioPro.sen.lvds[1].lvdsdats);
		RS_printf("IO_PRO.SEN.LVDS1.LHSADD       = %x\n", (unsigned int)&ioPro.sen.lvds[1].lhsadd);
		RS_printf("IO_PRO.SEN.LVDS1.LHSIZE       = %x\n", (unsigned int)&ioPro.sen.lvds[1].lhsize);
		RS_printf("IO_PRO.SEN.LVDS1.SYNCSEL      = %x\n", (unsigned int)&ioPro.sen.lvds[1].syncsel);
		RS_printf("IO_PRO.SEN.LVDS1.LPDCHG       = %x\n", (unsigned int)&ioPro.sen.lvds[1].lpdchg);
		RS_printf("IO_PRO.SEN.LVDS1.SAV0         = %x\n", (unsigned int)&ioPro.sen.lvds[1].sav0);
		RS_printf("IO_PRO.SEN.LVDS1.SAV1         = %x\n", (unsigned int)&ioPro.sen.lvds[1].sav1);
		RS_printf("IO_PRO.SEN.LVDS1.SAV2         = %x\n", (unsigned int)&ioPro.sen.lvds[1].sav2);
		RS_printf("IO_PRO.SEN.LVDS1.EAV0         = %x\n", (unsigned int)&ioPro.sen.lvds[1].eav0);
		RS_printf("IO_PRO.SEN.LVDS1.EAV1         = %x\n", (unsigned int)&ioPro.sen.lvds[1].eav1);
		RS_printf("IO_PRO.SEN.LVDS1.EAV2         = %x\n", (unsigned int)&ioPro.sen.lvds[1].eav2);
		RS_printf("IO_PRO.SEN.LVDS1.SAB0         = %x\n", (unsigned int)&ioPro.sen.lvds[1].sab0);
		RS_printf("IO_PRO.SEN.LVDS1.SAB1         = %x\n", (unsigned int)&ioPro.sen.lvds[1].sab1);
		RS_printf("IO_PRO.SEN.LVDS1.SAB2         = %x\n", (unsigned int)&ioPro.sen.lvds[1].sab2);
		RS_printf("IO_PRO.SEN.LVDS1.EAB0         = %x\n", (unsigned int)&ioPro.sen.lvds[1].eab0);
		RS_printf("IO_PRO.SEN.LVDS1.EAB1         = %x\n", (unsigned int)&ioPro.sen.lvds[1].eab1);
		RS_printf("IO_PRO.SEN.LVDS1.EAB2         = %x\n", (unsigned int)&ioPro.sen.lvds[1].eab2);
		RS_printf("IO_PRO.SEN.LVDS1.MSAV0        = %x\n", (unsigned int)&ioPro.sen.lvds[1].msav0);
		RS_printf("IO_PRO.SEN.LVDS1.MSAV1        = %x\n", (unsigned int)&ioPro.sen.lvds[1].msav1);
		RS_printf("IO_PRO.SEN.LVDS1.MSAV2        = %x\n", (unsigned int)&ioPro.sen.lvds[1].msav2);
		RS_printf("IO_PRO.SEN.LVDS1.MEAV0        = %x\n", (unsigned int)&ioPro.sen.lvds[1].meav0);
		RS_printf("IO_PRO.SEN.LVDS1.MEAV1        = %x\n", (unsigned int)&ioPro.sen.lvds[1].meav1);
		RS_printf("IO_PRO.SEN.LVDS1.MEAV2        = %x\n", (unsigned int)&ioPro.sen.lvds[1].meav2);
		RS_printf("IO_PRO.SEN.LVDS1.MSAB0        = %x\n", (unsigned int)&ioPro.sen.lvds[1].msab0);
		RS_printf("IO_PRO.SEN.LVDS1.MSAB1        = %x\n", (unsigned int)&ioPro.sen.lvds[1].msab1);
		RS_printf("IO_PRO.SEN.LVDS1.MSAB2        = %x\n", (unsigned int)&ioPro.sen.lvds[1].msab2);
		RS_printf("IO_PRO.SEN.LVDS1.MEAB0        = %x\n", (unsigned int)&ioPro.sen.lvds[1].meab0);
		RS_printf("IO_PRO.SEN.LVDS1.MEAB1        = %x\n", (unsigned int)&ioPro.sen.lvds[1].meab1);
		RS_printf("IO_PRO.SEN.LVDS1.MEAB2        = %x\n", (unsigned int)&ioPro.sen.lvds[1].meab2);
		RS_printf("IO_PRO.SEN.LVDS1.LVDSPAEN     = %x\n", (unsigned int)&ioPro.sen.lvds[1].lvdspaen);

		// LVDS-2
		RS_printf("IO_PRO.SEN.LVDS2.LVDSTRG      = %x\n", (unsigned int)&ioPro.sen.lvds[2].lvdstrg);
		RS_printf("IO_PRO.SEN.LVDS2.LVDSINTENB0  = %x\n", (unsigned int)&ioPro.sen.lvds[2].lvdsintenb0);
		RS_printf("IO_PRO.SEN.LVDS2.LVDSINTENB1  = %x\n", (unsigned int)&ioPro.sen.lvds[2].lvdsintenb1);
		RS_printf("IO_PRO.SEN.LVDS2.LVDSINTENB2  = %x\n", (unsigned int)&ioPro.sen.lvds[2].lvdsintenb2);
		RS_printf("IO_PRO.SEN.LVDS2.LVDSINTFLG0  = %x\n", (unsigned int)&ioPro.sen.lvds[2].lvdsintflg0);
		RS_printf("IO_PRO.SEN.LVDS2.LVDSINTFLG1  = %x\n", (unsigned int)&ioPro.sen.lvds[2].lvdsintflg1);
		RS_printf("IO_PRO.SEN.LVDS2.LVDSINTFLG2  = %x\n", (unsigned int)&ioPro.sen.lvds[2].lvdsintflg2);
		RS_printf("IO_PRO.SEN.LVDS2.LVDSINTADR0  = %x\n", (unsigned int)&ioPro.sen.lvds[2].lvdsintadr0);
		RS_printf("IO_PRO.SEN.LVDS2.LVDSINTADR1  = %x\n", (unsigned int)&ioPro.sen.lvds[2].lvdsintadr1);
		RS_printf("IO_PRO.SEN.LVDS2.LVDSINTADR2  = %x\n", (unsigned int)&ioPro.sen.lvds[2].lvdsintadr2);
		RS_printf("IO_PRO.SEN.LVDS2.LVDSINTSET0  = %x\n", (unsigned int)&ioPro.sen.lvds[2].lvdsintset0);
		RS_printf("IO_PRO.SEN.LVDS2.LVDSINTSET1  = %x\n", (unsigned int)&ioPro.sen.lvds[2].lvdsintset1);
		RS_printf("IO_PRO.SEN.LVDS2.LVDSINTSET2  = %x\n", (unsigned int)&ioPro.sen.lvds[2].lvdsintset2);
		RS_printf("IO_PRO.SEN.LVDS2.LVDSCTL1     = %x\n", (unsigned int)&ioPro.sen.lvds[2].lvdsctl1);
		RS_printf("IO_PRO.SEN.LVDS2.LVDSCTL2     = %x\n", (unsigned int)&ioPro.sen.lvds[2].lvdsctl2);
		RS_printf("IO_PRO.SEN.LVDS2.LVDSCLKS     = %x\n", (unsigned int)&ioPro.sen.lvds[2].lvdsclks);
		RS_printf("IO_PRO.SEN.LVDS2.LVDSDATS     = %x\n", (unsigned int)&ioPro.sen.lvds[2].lvdsdats);
		RS_printf("IO_PRO.SEN.LVDS2.LHSADD       = %x\n", (unsigned int)&ioPro.sen.lvds[2].lhsadd);
		RS_printf("IO_PRO.SEN.LVDS2.LHSIZE       = %x\n", (unsigned int)&ioPro.sen.lvds[2].lhsize);
		RS_printf("IO_PRO.SEN.LVDS2.SYNCSEL      = %x\n", (unsigned int)&ioPro.sen.lvds[2].syncsel);
		RS_printf("IO_PRO.SEN.LVDS2.LPDCHG       = %x\n", (unsigned int)&ioPro.sen.lvds[2].lpdchg);
		RS_printf("IO_PRO.SEN.LVDS2.SAV0         = %x\n", (unsigned int)&ioPro.sen.lvds[2].sav0);
		RS_printf("IO_PRO.SEN.LVDS2.SAV1         = %x\n", (unsigned int)&ioPro.sen.lvds[2].sav1);
		RS_printf("IO_PRO.SEN.LVDS2.SAV2         = %x\n", (unsigned int)&ioPro.sen.lvds[2].sav2);
		RS_printf("IO_PRO.SEN.LVDS2.EAV0         = %x\n", (unsigned int)&ioPro.sen.lvds[2].eav0);
		RS_printf("IO_PRO.SEN.LVDS2.EAV1         = %x\n", (unsigned int)&ioPro.sen.lvds[2].eav1);
		RS_printf("IO_PRO.SEN.LVDS2.EAV2         = %x\n", (unsigned int)&ioPro.sen.lvds[2].eav2);
		RS_printf("IO_PRO.SEN.LVDS2.SAB0         = %x\n", (unsigned int)&ioPro.sen.lvds[2].sab0);
		RS_printf("IO_PRO.SEN.LVDS2.SAB1         = %x\n", (unsigned int)&ioPro.sen.lvds[2].sab1);
		RS_printf("IO_PRO.SEN.LVDS2.SAB2         = %x\n", (unsigned int)&ioPro.sen.lvds[2].sab2);
		RS_printf("IO_PRO.SEN.LVDS2.EAB0         = %x\n", (unsigned int)&ioPro.sen.lvds[2].eab0);
		RS_printf("IO_PRO.SEN.LVDS2.EAB1         = %x\n", (unsigned int)&ioPro.sen.lvds[2].eab1);
		RS_printf("IO_PRO.SEN.LVDS2.EAB2         = %x\n", (unsigned int)&ioPro.sen.lvds[2].eab2);
		RS_printf("IO_PRO.SEN.LVDS2.MSAV0        = %x\n", (unsigned int)&ioPro.sen.lvds[2].msav0);
		RS_printf("IO_PRO.SEN.LVDS2.MSAV1        = %x\n", (unsigned int)&ioPro.sen.lvds[2].msav1);
		RS_printf("IO_PRO.SEN.LVDS2.MSAV2        = %x\n", (unsigned int)&ioPro.sen.lvds[2].msav2);
		RS_printf("IO_PRO.SEN.LVDS2.MEAV0        = %x\n", (unsigned int)&ioPro.sen.lvds[2].meav0);
		RS_printf("IO_PRO.SEN.LVDS2.MEAV1        = %x\n", (unsigned int)&ioPro.sen.lvds[2].meav1);
		RS_printf("IO_PRO.SEN.LVDS2.MEAV2        = %x\n", (unsigned int)&ioPro.sen.lvds[2].meav2);
		RS_printf("IO_PRO.SEN.LVDS2.MSAB0        = %x\n", (unsigned int)&ioPro.sen.lvds[2].msab0);
		RS_printf("IO_PRO.SEN.LVDS2.MSAB1        = %x\n", (unsigned int)&ioPro.sen.lvds[2].msab1);
		RS_printf("IO_PRO.SEN.LVDS2.MSAB2        = %x\n", (unsigned int)&ioPro.sen.lvds[2].msab2);
		RS_printf("IO_PRO.SEN.LVDS2.MEAB0        = %x\n", (unsigned int)&ioPro.sen.lvds[2].meab0);
		RS_printf("IO_PRO.SEN.LVDS2.MEAB1        = %x\n", (unsigned int)&ioPro.sen.lvds[2].meab1);
		RS_printf("IO_PRO.SEN.LVDS2.MEAB2        = %x\n", (unsigned int)&ioPro.sen.lvds[2].meab2);
		RS_printf("IO_PRO.SEN.LVDS2.LVDSPAEN     = %x\n", (unsigned int)&ioPro.sen.lvds[2].lvdspaen);

		// LVDS-3
		RS_printf("IO_PRO.SEN.LVDS3.LVDSTRG      = %x\n", (unsigned int)&ioPro.sen.lvds[3].lvdstrg);
		RS_printf("IO_PRO.SEN.LVDS3.LVDSINTENB0  = %x\n", (unsigned int)&ioPro.sen.lvds[3].lvdsintenb0);
		RS_printf("IO_PRO.SEN.LVDS3.LVDSINTENB1  = %x\n", (unsigned int)&ioPro.sen.lvds[3].lvdsintenb1);
		RS_printf("IO_PRO.SEN.LVDS3.LVDSINTENB2  = %x\n", (unsigned int)&ioPro.sen.lvds[3].lvdsintenb2);
		RS_printf("IO_PRO.SEN.LVDS3.LVDSINTFLG0  = %x\n", (unsigned int)&ioPro.sen.lvds[3].lvdsintflg0);
		RS_printf("IO_PRO.SEN.LVDS3.LVDSINTFLG1  = %x\n", (unsigned int)&ioPro.sen.lvds[3].lvdsintflg1);
		RS_printf("IO_PRO.SEN.LVDS3.LVDSINTFLG2  = %x\n", (unsigned int)&ioPro.sen.lvds[3].lvdsintflg2);
		RS_printf("IO_PRO.SEN.LVDS3.LVDSINTADR0  = %x\n", (unsigned int)&ioPro.sen.lvds[3].lvdsintadr0);
		RS_printf("IO_PRO.SEN.LVDS3.LVDSINTADR1  = %x\n", (unsigned int)&ioPro.sen.lvds[3].lvdsintadr1);
		RS_printf("IO_PRO.SEN.LVDS3.LVDSINTADR2  = %x\n", (unsigned int)&ioPro.sen.lvds[3].lvdsintadr2);
		RS_printf("IO_PRO.SEN.LVDS3.LVDSINTSET0  = %x\n", (unsigned int)&ioPro.sen.lvds[3].lvdsintset0);
		RS_printf("IO_PRO.SEN.LVDS3.LVDSINTSET1  = %x\n", (unsigned int)&ioPro.sen.lvds[3].lvdsintset1);
		RS_printf("IO_PRO.SEN.LVDS3.LVDSINTSET2  = %x\n", (unsigned int)&ioPro.sen.lvds[3].lvdsintset2);
		RS_printf("IO_PRO.SEN.LVDS3.LVDSCTL1     = %x\n", (unsigned int)&ioPro.sen.lvds[3].lvdsctl1);
		RS_printf("IO_PRO.SEN.LVDS3.LVDSCTL2     = %x\n", (unsigned int)&ioPro.sen.lvds[3].lvdsctl2);
		RS_printf("IO_PRO.SEN.LVDS3.LVDSCLKS     = %x\n", (unsigned int)&ioPro.sen.lvds[3].lvdsclks);
		RS_printf("IO_PRO.SEN.LVDS3.LVDSDATS     = %x\n", (unsigned int)&ioPro.sen.lvds[3].lvdsdats);
		RS_printf("IO_PRO.SEN.LVDS3.LHSADD       = %x\n", (unsigned int)&ioPro.sen.lvds[3].lhsadd);
		RS_printf("IO_PRO.SEN.LVDS3.LHSIZE       = %x\n", (unsigned int)&ioPro.sen.lvds[3].lhsize);
		RS_printf("IO_PRO.SEN.LVDS3.SYNCSEL      = %x\n", (unsigned int)&ioPro.sen.lvds[3].syncsel);
		RS_printf("IO_PRO.SEN.LVDS3.LPDCHG       = %x\n", (unsigned int)&ioPro.sen.lvds[3].lpdchg);
		RS_printf("IO_PRO.SEN.LVDS3.SAV0         = %x\n", (unsigned int)&ioPro.sen.lvds[3].sav0);
		RS_printf("IO_PRO.SEN.LVDS3.SAV1         = %x\n", (unsigned int)&ioPro.sen.lvds[3].sav1);
		RS_printf("IO_PRO.SEN.LVDS3.SAV2         = %x\n", (unsigned int)&ioPro.sen.lvds[3].sav2);
		RS_printf("IO_PRO.SEN.LVDS3.EAV0         = %x\n", (unsigned int)&ioPro.sen.lvds[3].eav0);
		RS_printf("IO_PRO.SEN.LVDS3.EAV1         = %x\n", (unsigned int)&ioPro.sen.lvds[3].eav1);
		RS_printf("IO_PRO.SEN.LVDS3.EAV2         = %x\n", (unsigned int)&ioPro.sen.lvds[3].eav2);
		RS_printf("IO_PRO.SEN.LVDS3.SAB0         = %x\n", (unsigned int)&ioPro.sen.lvds[3].sab0);
		RS_printf("IO_PRO.SEN.LVDS3.SAB1         = %x\n", (unsigned int)&ioPro.sen.lvds[3].sab1);
		RS_printf("IO_PRO.SEN.LVDS3.SAB2         = %x\n", (unsigned int)&ioPro.sen.lvds[3].sab2);
		RS_printf("IO_PRO.SEN.LVDS3.EAB0         = %x\n", (unsigned int)&ioPro.sen.lvds[3].eab0);
		RS_printf("IO_PRO.SEN.LVDS3.EAB1         = %x\n", (unsigned int)&ioPro.sen.lvds[3].eab1);
		RS_printf("IO_PRO.SEN.LVDS3.EAB2         = %x\n", (unsigned int)&ioPro.sen.lvds[3].eab2);
		RS_printf("IO_PRO.SEN.LVDS3.MSAV0        = %x\n", (unsigned int)&ioPro.sen.lvds[3].msav0);
		RS_printf("IO_PRO.SEN.LVDS3.MSAV1        = %x\n", (unsigned int)&ioPro.sen.lvds[3].msav1);
		RS_printf("IO_PRO.SEN.LVDS3.MSAV2        = %x\n", (unsigned int)&ioPro.sen.lvds[3].msav2);
		RS_printf("IO_PRO.SEN.LVDS3.MEAV0        = %x\n", (unsigned int)&ioPro.sen.lvds[3].meav0);
		RS_printf("IO_PRO.SEN.LVDS3.MEAV1        = %x\n", (unsigned int)&ioPro.sen.lvds[3].meav1);
		RS_printf("IO_PRO.SEN.LVDS3.MEAV2        = %x\n", (unsigned int)&ioPro.sen.lvds[3].meav2);
		RS_printf("IO_PRO.SEN.LVDS3.MSAB0        = %x\n", (unsigned int)&ioPro.sen.lvds[3].msab0);
		RS_printf("IO_PRO.SEN.LVDS3.MSAB1        = %x\n", (unsigned int)&ioPro.sen.lvds[3].msab1);
		RS_printf("IO_PRO.SEN.LVDS3.MSAB2        = %x\n", (unsigned int)&ioPro.sen.lvds[3].msab2);
		RS_printf("IO_PRO.SEN.LVDS3.MEAB0        = %x\n", (unsigned int)&ioPro.sen.lvds[3].meab0);
		RS_printf("IO_PRO.SEN.LVDS3.MEAB1        = %x\n", (unsigned int)&ioPro.sen.lvds[3].meab1);
		RS_printf("IO_PRO.SEN.LVDS3.MEAB2        = %x\n", (unsigned int)&ioPro.sen.lvds[3].meab2);
		RS_printf("IO_PRO.SEN.LVDS3.LVDSPAEN     = %x\n", (unsigned int)&ioPro.sen.lvds[3].lvdspaen);

		// SLVSEC
		RS_printf("IO_PRO.SEN.SLVSEC0.COMMON.SR         = %x\n", (unsigned int)&ioPro.sen.slvsec.common.sr);
		RS_printf("IO_PRO.SEN.SLVSEC0.COMMON.PHYCR0     = %x\n", (unsigned int)&ioPro.sen.slvsec.common.phycr0);
		RS_printf("IO_PRO.SEN.SLVSEC0.COMMON.PHYCR1     = %x\n", (unsigned int)&ioPro.sen.slvsec.common.phycr1);
		RS_printf("IO_PRO.SEN.SLVSEC0.COMMON.PHYCR2     = %x\n", (unsigned int)&ioPro.sen.slvsec.common.phycr2);
		RS_printf("IO_PRO.SEN.SLVSEC0.COMMON.ATTR1      = %x\n", (unsigned int)&ioPro.sen.slvsec.common.attr1);
		RS_printf("IO_PRO.SEN.SLVSEC0.COMMON.ATTR2      = %x\n", (unsigned int)&ioPro.sen.slvsec.common.attr2);
		RS_printf("IO_PRO.SEN.SLVSEC0.COMMON.ATTR3      = %x\n", (unsigned int)&ioPro.sen.slvsec.common.attr3);
		RS_printf("IO_PRO.SEN.SLVSEC0.COMMON.ATTR4      = %x\n", (unsigned int)&ioPro.sen.slvsec.common.attr4);
		RS_printf("IO_PRO.SEN.SLVSEC0.COMMON.PEINTST    = %x\n", (unsigned int)&ioPro.sen.slvsec.common.peintst);
		RS_printf("IO_PRO.SEN.SLVSEC0.COMMON.PEINTEN    = %x\n", (unsigned int)&ioPro.sen.slvsec.common.peinten);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[0].RAMPD   = %x\n", (unsigned int)&ioPro.sen.slvsec.stream[0].rampd);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[0].TRGR    = %x\n", (unsigned int)&ioPro.sen.slvsec.stream[0].trgr);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[0].INTST   = %x\n", (unsigned int)&ioPro.sen.slvsec.stream[0].intst);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[0].INTEN   = %x\n", (unsigned int)&ioPro.sen.slvsec.stream[0].inten);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[0].LEINTST = %x\n", (unsigned int)&ioPro.sen.slvsec.stream[0].leintst);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[0].LEINTEN = %x\n", (unsigned int)&ioPro.sen.slvsec.stream[0].leinten);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[0].MEINTST0= %x\n", (unsigned int)&ioPro.sen.slvsec.stream[0].meintst0);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[0].MEINTST1= %x\n", (unsigned int)&ioPro.sen.slvsec.stream[0].meintst1);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[0].MEINTEN0= %x\n", (unsigned int)&ioPro.sen.slvsec.stream[0].meinten0);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[0].MEINTEN1= %x\n", (unsigned int)&ioPro.sen.slvsec.stream[0].meinten1);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[0].CFGR0   = %x\n", (unsigned int)&ioPro.sen.slvsec.stream[0].cfgr0);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[0].CFGR1   = %x\n", (unsigned int)&ioPro.sen.slvsec.stream[0].cfgr1);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[0].OUTMD   = %x\n", (unsigned int)&ioPro.sen.slvsec.stream[0].outmd);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[0].LSWAP   = %x\n", (unsigned int)&ioPro.sen.slvsec.stream[0].lswap);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[0].VLANE   = %x\n", (unsigned int)&ioPro.sen.slvsec.stream[0].vlane);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[0].HSADD   = %x\n", (unsigned int)&ioPro.sen.slvsec.stream[0].hsadd);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[0].HSIZE   = %x\n", (unsigned int)&ioPro.sen.slvsec.stream[0].hsize);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[0].EBDST   = %x\n", (unsigned int)&ioPro.sen.slvsec.stream[0].ebdst);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[0].LNEST   = %x\n", (unsigned int)&ioPro.sen.slvsec.stream[0].lnest);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[0].MMODE   = %x\n", (unsigned int)&ioPro.sen.slvsec.stream[0].mmode);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[1].RAMPD   = %x\n", (unsigned int)&ioPro.sen.slvsec.stream[1].rampd);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[1].TRGR    = %x\n", (unsigned int)&ioPro.sen.slvsec.stream[1].trgr);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[1].INTST   = %x\n", (unsigned int)&ioPro.sen.slvsec.stream[1].intst);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[1].INTEN   = %x\n", (unsigned int)&ioPro.sen.slvsec.stream[1].inten);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[1].LEINTST = %x\n", (unsigned int)&ioPro.sen.slvsec.stream[1].leintst);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[1].LEINTEN = %x\n", (unsigned int)&ioPro.sen.slvsec.stream[1].leinten);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[1].MEINTST0= %x\n", (unsigned int)&ioPro.sen.slvsec.stream[1].meintst0);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[1].MEINTST1= %x\n", (unsigned int)&ioPro.sen.slvsec.stream[1].meintst1);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[1].MEINTEN0= %x\n", (unsigned int)&ioPro.sen.slvsec.stream[1].meinten0);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[1].MEINTEN1= %x\n", (unsigned int)&ioPro.sen.slvsec.stream[1].meinten1);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[1].CFGR0   = %x\n", (unsigned int)&ioPro.sen.slvsec.stream[1].cfgr0);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[1].CFGR1   = %x\n", (unsigned int)&ioPro.sen.slvsec.stream[1].cfgr1);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[1].OUTMD   = %x\n", (unsigned int)&ioPro.sen.slvsec.stream[1].outmd);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[1].LSWAP   = %x\n", (unsigned int)&ioPro.sen.slvsec.stream[1].lswap);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[1].VLANE   = %x\n", (unsigned int)&ioPro.sen.slvsec.stream[1].vlane);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[1].HSADD   = %x\n", (unsigned int)&ioPro.sen.slvsec.stream[1].hsadd);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[1].HSIZE   = %x\n", (unsigned int)&ioPro.sen.slvsec.stream[1].hsize);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[1].EBDST   = %x\n", (unsigned int)&ioPro.sen.slvsec.stream[1].ebdst);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[1].LNEST   = %x\n", (unsigned int)&ioPro.sen.slvsec.stream[1].lnest);
		RS_printf("IO_PRO.SEN.SLVSEC0.STREAM[1].MMODE   = %x\n", (unsigned int)&ioPro.sen.slvsec.stream[1].mmode);

		// MIPID0
		RS_printf("IO_PRO.SEN.MIPID0.MPISR       = %x\n", (unsigned int)&ioPro.sen.mipid[0].mpisr);
		RS_printf("IO_PRO.SEN.MIPID0.MPITRG      = %x\n", (unsigned int)&ioPro.sen.mipid[0].mpitrg);
		RS_printf("IO_PRO.SEN.MIPID0.MPIPAEN0    = %x\n", (unsigned int)&ioPro.sen.mipid[0].mpipaen0);
		RS_printf("IO_PRO.SEN.MIPID0.MPIPAEN1    = %x\n", (unsigned int)&ioPro.sen.mipid[0].mpipaen1);
		RS_printf("IO_PRO.SEN.MIPID0.MPIINTE     = %x\n", (unsigned int)&ioPro.sen.mipid[0].mpiinte);
		RS_printf("IO_PRO.SEN.MIPID0.MPIINTF     = %x\n", (unsigned int)&ioPro.sen.mipid[0].mpiintf);
		RS_printf("IO_PRO.SEN.MIPID0.MPILMODE    = %x\n", (unsigned int)&ioPro.sen.mipid[0].mpilmode);
		RS_printf("IO_PRO.SEN.MIPID0.MPIIOMD0    = %x\n", (unsigned int)&ioPro.sen.mipid[0].mpiiomd0);
		RS_printf("IO_PRO.SEN.MIPID0.MPIIOMD1    = %x\n", (unsigned int)&ioPro.sen.mipid[0].mpiiomd1);
		RS_printf("IO_PRO.SEN.MIPID0.MPIDPI      = %x\n", (unsigned int)&ioPro.sen.mipid[0].mpidpi);
		RS_printf("IO_PRO.SEN.MIPID0.MPIDPVR     = %x\n", (unsigned int)&ioPro.sen.mipid[0].mpidpvr);
		RS_printf("IO_PRO.SEN.MIPID0.MPISCS      = %x\n", (unsigned int)&ioPro.sen.mipid[0].mpiscs);
		RS_printf("IO_PRO.SEN.MIPID0.MPIHDPDSEL  = %x\n", (unsigned int)&ioPro.sen.mipid[0].mpihdpdsel);

		// MIPID1
		RS_printf("IO_PRO.SEN.MIPID1.MPISR       = %x\n", (unsigned int)&ioPro.sen.mipid[1].mpisr);
		RS_printf("IO_PRO.SEN.MIPID1.MPITRG      = %x\n", (unsigned int)&ioPro.sen.mipid[1].mpitrg);
		RS_printf("IO_PRO.SEN.MIPID1.MPIPAEN0    = %x\n", (unsigned int)&ioPro.sen.mipid[1].mpipaen0);
		RS_printf("IO_PRO.SEN.MIPID1.MPIPAEN1    = %x\n", (unsigned int)&ioPro.sen.mipid[1].mpipaen1);
		RS_printf("IO_PRO.SEN.MIPID1.MPIINTE     = %x\n", (unsigned int)&ioPro.sen.mipid[1].mpiinte);
		RS_printf("IO_PRO.SEN.MIPID1.MPIINTF     = %x\n", (unsigned int)&ioPro.sen.mipid[1].mpiintf);
		RS_printf("IO_PRO.SEN.MIPID1.MPILMODE    = %x\n", (unsigned int)&ioPro.sen.mipid[1].mpilmode);
		RS_printf("IO_PRO.SEN.MIPID1.MPIIOMD0    = %x\n", (unsigned int)&ioPro.sen.mipid[1].mpiiomd0);
		RS_printf("IO_PRO.SEN.MIPID1.MPIIOMD1    = %x\n", (unsigned int)&ioPro.sen.mipid[1].mpiiomd1);
		RS_printf("IO_PRO.SEN.MIPID1.MPIDPI      = %x\n", (unsigned int)&ioPro.sen.mipid[1].mpidpi);
		RS_printf("IO_PRO.SEN.MIPID1.MPIDPVR     = %x\n", (unsigned int)&ioPro.sen.mipid[1].mpidpvr);
		RS_printf("IO_PRO.SEN.MIPID1.MPISCS      = %x\n", (unsigned int)&ioPro.sen.mipid[1].mpiscs);
		RS_printf("IO_PRO.SEN.MIPID1.MPIHDPDSEL  = %x\n", (unsigned int)&ioPro.sen.mipid[1].mpihdpdsel);

		// MIPID2
		RS_printf("IO_PRO.SEN.MIPID2.MPISR       = %x\n", (unsigned int)&ioPro.sen.mipid[2].mpisr);
		RS_printf("IO_PRO.SEN.MIPID2.MPITRG      = %x\n", (unsigned int)&ioPro.sen.mipid[2].mpitrg);
		RS_printf("IO_PRO.SEN.MIPID2.MPIPAEN0    = %x\n", (unsigned int)&ioPro.sen.mipid[2].mpipaen0);
		RS_printf("IO_PRO.SEN.MIPID2.MPIPAEN1    = %x\n", (unsigned int)&ioPro.sen.mipid[2].mpipaen1);
		RS_printf("IO_PRO.SEN.MIPID2.MPIINTE     = %x\n", (unsigned int)&ioPro.sen.mipid[2].mpiinte);
		RS_printf("IO_PRO.SEN.MIPID2.MPIINTF     = %x\n", (unsigned int)&ioPro.sen.mipid[2].mpiintf);
		RS_printf("IO_PRO.SEN.MIPID2.MPILMODE    = %x\n", (unsigned int)&ioPro.sen.mipid[2].mpilmode);
		RS_printf("IO_PRO.SEN.MIPID2.MPIIOMD0    = %x\n", (unsigned int)&ioPro.sen.mipid[2].mpiiomd0);
		RS_printf("IO_PRO.SEN.MIPID2.MPIIOMD1    = %x\n", (unsigned int)&ioPro.sen.mipid[2].mpiiomd1);
		RS_printf("IO_PRO.SEN.MIPID2.MPIDPI      = %x\n", (unsigned int)&ioPro.sen.mipid[2].mpidpi);
		RS_printf("IO_PRO.SEN.MIPID2.MPIDPVR     = %x\n", (unsigned int)&ioPro.sen.mipid[2].mpidpvr);
		RS_printf("IO_PRO.SEN.MIPID2.MPISCS      = %x\n", (unsigned int)&ioPro.sen.mipid[2].mpiscs);
		RS_printf("IO_PRO.SEN.MIPID2.MPIHDPDSEL  = %x\n", (unsigned int)&ioPro.sen.mipid[2].mpihdpdsel);

		// MIPID3
		RS_printf("IO_PRO.SEN.MIPID3.MPISR       = %x\n", (unsigned int)&ioPro.sen.mipid[3].mpisr);
		RS_printf("IO_PRO.SEN.MIPID3.MPITRG      = %x\n", (unsigned int)&ioPro.sen.mipid[3].mpitrg);
		RS_printf("IO_PRO.SEN.MIPID3.MPIPAEN0    = %x\n", (unsigned int)&ioPro.sen.mipid[3].mpipaen0);
		RS_printf("IO_PRO.SEN.MIPID3.MPIPAEN1    = %x\n", (unsigned int)&ioPro.sen.mipid[3].mpipaen1);
		RS_printf("IO_PRO.SEN.MIPID3.MPIINTE     = %x\n", (unsigned int)&ioPro.sen.mipid[3].mpiinte);
		RS_printf("IO_PRO.SEN.MIPID3.MPIINTF     = %x\n", (unsigned int)&ioPro.sen.mipid[3].mpiintf);
		RS_printf("IO_PRO.SEN.MIPID3.MPILMODE    = %x\n", (unsigned int)&ioPro.sen.mipid[3].mpilmode);
		RS_printf("IO_PRO.SEN.MIPID3.MPIIOMD0    = %x\n", (unsigned int)&ioPro.sen.mipid[3].mpiiomd0);
		RS_printf("IO_PRO.SEN.MIPID3.MPIIOMD1    = %x\n", (unsigned int)&ioPro.sen.mipid[3].mpiiomd1);
		RS_printf("IO_PRO.SEN.MIPID3.MPIDPI      = %x\n", (unsigned int)&ioPro.sen.mipid[3].mpidpi);
		RS_printf("IO_PRO.SEN.MIPID3.MPIDPVR     = %x\n", (unsigned int)&ioPro.sen.mipid[3].mpidpvr);
		RS_printf("IO_PRO.SEN.MIPID3.MPISCS      = %x\n", (unsigned int)&ioPro.sen.mipid[3].mpiscs);
		RS_printf("IO_PRO.SEN.MIPID3.MPIHDPDSEL  = %x\n", (unsigned int)&ioPro.sen.mipid[3].mpihdpdsel);

		// MIPIC0
		RS_printf("IO_PRO.SEN.MIPIC0.MPICSR           = %x\n", (unsigned int)&ioPro.sen.mipic[0].mpicsr);
		RS_printf("IO_PRO.SEN.MIPIC0.MPICTRG          = %x\n", (unsigned int)&ioPro.sen.mipic[0].mpictrg);
		RS_printf("IO_PRO.SEN.MIPIC0.MPICPAEN0        = %x\n", (unsigned int)&ioPro.sen.mipic[0].mpicpaen0);
		RS_printf("IO_PRO.SEN.MIPIC0.MPICPAEN1        = %x\n", (unsigned int)&ioPro.sen.mipic[0].mpicpaen1);
		RS_printf("IO_PRO.SEN.MIPIC0.MPICINTE1        = %x\n", (unsigned int)&ioPro.sen.mipic[0].mpicinte1);
		RS_printf("IO_PRO.SEN.MIPIC0.MPICINTE2        = %x\n", (unsigned int)&ioPro.sen.mipic[0].mpicinte2);
		RS_printf("IO_PRO.SEN.MIPIC0.MPICINTF1        = %x\n", (unsigned int)&ioPro.sen.mipic[0].mpicintf1);
		RS_printf("IO_PRO.SEN.MIPIC0.MPICINTF2        = %x\n", (unsigned int)&ioPro.sen.mipic[0].mpicintf2);
		RS_printf("IO_PRO.SEN.MIPIC0.MPICLMODE        = %x\n", (unsigned int)&ioPro.sen.mipic[0].mpiclmode);
		RS_printf("IO_PRO.SEN.MIPIC0.MPICIOMD0        = %x\n", (unsigned int)&ioPro.sen.mipic[0].mpiciomd0);
		RS_printf("IO_PRO.SEN.MIPIC0.MPICIOMD1        = %x\n", (unsigned int)&ioPro.sen.mipic[0].mpiciomd1);
		RS_printf("IO_PRO.SEN.MIPIC0.MPICPVR          = %x\n", (unsigned int)&ioPro.sen.mipic[0].mpicpvr);
		RS_printf("IO_PRO.SEN.MIPIC0.MPICHDPDSEL      = %x\n", (unsigned int)&ioPro.sen.mipic[0].mpichdpdsel);
		RS_printf("IO_PRO.SEN.MIPIC0.MPICCPI1         = %x\n", (unsigned int)&ioPro.sen.mipic[0].mpiccpi1);
		RS_printf("IO_PRO.SEN.MIPIC0.MPICCPI2         = %x\n", (unsigned int)&ioPro.sen.mipic[0].mpiccpi2);
		RS_printf("IO_PRO.SEN.MIPIC0.MPICPRLRLCONF    = %x\n", (unsigned int)&ioPro.sen.mipic[0].mpicprlrlconf);
		RS_printf("IO_PRO.SEN.MIPIC0.MPICPRLRLTPSEL   = %x\n", (unsigned int)&ioPro.sen.mipic[0].mpicprlrltpsel);
		RS_printf("IO_PRO.SEN.MIPIC0.MPICPRLRPRBS     = %x\n", (unsigned int)&ioPro.sen.mipic[0].mpicprlrprbs);
		RS_printf("IO_PRO.SEN.MIPIC0.MPICPRLRLST      = %x\n", (unsigned int)&ioPro.sen.mipic[0].mpicprlrlst);
		RS_printf("IO_PRO.SEN.MIPIC0.MPICPRLRWECNT0   = %x\n", (unsigned int)&ioPro.sen.mipic[0].mpicprlrwecnt0);
		RS_printf("IO_PRO.SEN.MIPIC0.MPICPRLRWECNT1   = %x\n", (unsigned int)&ioPro.sen.mipic[0].mpicprlrwecnt1);
		RS_printf("IO_PRO.SEN.MIPIC0.MPICPRLRWECNT2   = %x\n", (unsigned int)&ioPro.sen.mipic[0].mpicprlrwecnt2);
		RS_printf("IO_PRO.SEN.MIPIC0.MPICPRLRWCNT0    = %x\n", (unsigned int)&ioPro.sen.mipic[0].mpicprlrwcnt0);
		RS_printf("IO_PRO.SEN.MIPIC0.MPICPRLRWCNT1    = %x\n", (unsigned int)&ioPro.sen.mipic[0].mpicprlrwcnt1);
		RS_printf("IO_PRO.SEN.MIPIC0.MPICPRLRWCNT2    = %x\n", (unsigned int)&ioPro.sen.mipic[0].mpicprlrwcnt2);
		RS_printf("IO_PRO.SEN.MIPIC0.MPICPRLRSERRCNT0 = %x\n", (unsigned int)&ioPro.sen.mipic[0].mpicprlrserrcnt0);
		RS_printf("IO_PRO.SEN.MIPIC0.MPICPRLRSERRCNT1 = %x\n", (unsigned int)&ioPro.sen.mipic[0].mpicprlrserrcnt1);
		RS_printf("IO_PRO.SEN.MIPIC0.MPICPRLRSERRCNT2 = %x\n", (unsigned int)&ioPro.sen.mipic[0].mpicprlrserrcnt2);
		RS_printf("IO_PRO.SEN.MIPIC0.MPICPRLRSERRLOC0 = %x\n", (unsigned int)&ioPro.sen.mipic[0].mpicprlrserrloc0);
		RS_printf("IO_PRO.SEN.MIPIC0.MPICPRLRSERRLOC1 = %x\n", (unsigned int)&ioPro.sen.mipic[0].mpicprlrserrloc1);
		RS_printf("IO_PRO.SEN.MIPIC0.MPICPRLRSERRLOC2 = %x\n", (unsigned int)&ioPro.sen.mipic[0].mpicprlrserrloc2);
		RS_printf("IO_PRO.SEN.MIPIC0.MPICPPROGSEQ     = %x\n", (unsigned int)&ioPro.sen.mipic[0].mpicpprogseq);

		// MIPIC1
		RS_printf("IO_PRO.SEN.MIPIC1.MPICSR           = %x\n", (unsigned int)&ioPro.sen.mipic[1].mpicsr);
		RS_printf("IO_PRO.SEN.MIPIC1.MPICTRG          = %x\n", (unsigned int)&ioPro.sen.mipic[1].mpictrg);
		RS_printf("IO_PRO.SEN.MIPIC1.MPICPAEN0        = %x\n", (unsigned int)&ioPro.sen.mipic[1].mpicpaen0);
		RS_printf("IO_PRO.SEN.MIPIC1.MPICPAEN1        = %x\n", (unsigned int)&ioPro.sen.mipic[1].mpicpaen1);
		RS_printf("IO_PRO.SEN.MIPIC1.MPICINTE1        = %x\n", (unsigned int)&ioPro.sen.mipic[1].mpicinte1);
		RS_printf("IO_PRO.SEN.MIPIC1.MPICINTE2        = %x\n", (unsigned int)&ioPro.sen.mipic[1].mpicinte2);
		RS_printf("IO_PRO.SEN.MIPIC1.MPICINTF1        = %x\n", (unsigned int)&ioPro.sen.mipic[1].mpicintf1);
		RS_printf("IO_PRO.SEN.MIPIC1.MPICINTF2        = %x\n", (unsigned int)&ioPro.sen.mipic[1].mpicintf2);
		RS_printf("IO_PRO.SEN.MIPIC1.MPICLMODE        = %x\n", (unsigned int)&ioPro.sen.mipic[1].mpiclmode);
		RS_printf("IO_PRO.SEN.MIPIC1.MPICIOMD0        = %x\n", (unsigned int)&ioPro.sen.mipic[1].mpiciomd0);
		RS_printf("IO_PRO.SEN.MIPIC1.MPICIOMD1        = %x\n", (unsigned int)&ioPro.sen.mipic[1].mpiciomd1);
		RS_printf("IO_PRO.SEN.MIPIC1.MPICPVR          = %x\n", (unsigned int)&ioPro.sen.mipic[1].mpicpvr);
		RS_printf("IO_PRO.SEN.MIPIC1.MPICHDPDSEL      = %x\n", (unsigned int)&ioPro.sen.mipic[1].mpichdpdsel);
		RS_printf("IO_PRO.SEN.MIPIC1.MPICCPI1         = %x\n", (unsigned int)&ioPro.sen.mipic[1].mpiccpi1);
		RS_printf("IO_PRO.SEN.MIPIC1.MPICCPI2         = %x\n", (unsigned int)&ioPro.sen.mipic[1].mpiccpi2);
		RS_printf("IO_PRO.SEN.MIPIC1.MPICPRLRLCONF    = %x\n", (unsigned int)&ioPro.sen.mipic[1].mpicprlrlconf);
		RS_printf("IO_PRO.SEN.MIPIC1.MPICPRLRLTPSEL   = %x\n", (unsigned int)&ioPro.sen.mipic[1].mpicprlrltpsel);
		RS_printf("IO_PRO.SEN.MIPIC1.MPICPRLRPRBS     = %x\n", (unsigned int)&ioPro.sen.mipic[1].mpicprlrprbs);
		RS_printf("IO_PRO.SEN.MIPIC1.MPICPRLRLST      = %x\n", (unsigned int)&ioPro.sen.mipic[1].mpicprlrlst);
		RS_printf("IO_PRO.SEN.MIPIC1.MPICPRLRWECNT0   = %x\n", (unsigned int)&ioPro.sen.mipic[1].mpicprlrwecnt0);
		RS_printf("IO_PRO.SEN.MIPIC1.MPICPRLRWECNT1   = %x\n", (unsigned int)&ioPro.sen.mipic[1].mpicprlrwecnt1);
		RS_printf("IO_PRO.SEN.MIPIC1.MPICPRLRWECNT2   = %x\n", (unsigned int)&ioPro.sen.mipic[1].mpicprlrwecnt2);
		RS_printf("IO_PRO.SEN.MIPIC1.MPICPRLRWCNT0    = %x\n", (unsigned int)&ioPro.sen.mipic[1].mpicprlrwcnt0);
		RS_printf("IO_PRO.SEN.MIPIC1.MPICPRLRWCNT1    = %x\n", (unsigned int)&ioPro.sen.mipic[1].mpicprlrwcnt1);
		RS_printf("IO_PRO.SEN.MIPIC1.MPICPRLRWCNT2    = %x\n", (unsigned int)&ioPro.sen.mipic[1].mpicprlrwcnt2);
		RS_printf("IO_PRO.SEN.MIPIC1.MPICPRLRSERRCNT0 = %x\n", (unsigned int)&ioPro.sen.mipic[1].mpicprlrserrcnt0);
		RS_printf("IO_PRO.SEN.MIPIC1.MPICPRLRSERRCNT1 = %x\n", (unsigned int)&ioPro.sen.mipic[1].mpicprlrserrcnt1);
		RS_printf("IO_PRO.SEN.MIPIC1.MPICPRLRSERRCNT2 = %x\n", (unsigned int)&ioPro.sen.mipic[1].mpicprlrserrcnt2);
		RS_printf("IO_PRO.SEN.MIPIC1.MPICPRLRSERRLOC0 = %x\n", (unsigned int)&ioPro.sen.mipic[1].mpicprlrserrloc0);
		RS_printf("IO_PRO.SEN.MIPIC1.MPICPRLRSERRLOC1 = %x\n", (unsigned int)&ioPro.sen.mipic[1].mpicprlrserrloc1);
		RS_printf("IO_PRO.SEN.MIPIC1.MPICPRLRSERRLOC2 = %x\n", (unsigned int)&ioPro.sen.mipic[1].mpicprlrserrloc2);
		RS_printf("IO_PRO.SEN.MIPIC1.MPICPPROGSEQ     = %x\n", (unsigned int)&ioPro.sen.mipic[1].mpicpprogseq);

		// MIPIC2
		RS_printf("IO_PRO.SEN.MIPIC2.MPICSR           = %x\n", (unsigned int)&ioPro.sen.mipic[2].mpicsr);
		RS_printf("IO_PRO.SEN.MIPIC2.MPICTRG          = %x\n", (unsigned int)&ioPro.sen.mipic[2].mpictrg);
		RS_printf("IO_PRO.SEN.MIPIC2.MPICPAEN0        = %x\n", (unsigned int)&ioPro.sen.mipic[2].mpicpaen0);
		RS_printf("IO_PRO.SEN.MIPIC2.MPICPAEN1        = %x\n", (unsigned int)&ioPro.sen.mipic[2].mpicpaen1);
		RS_printf("IO_PRO.SEN.MIPIC2.MPICINTE1        = %x\n", (unsigned int)&ioPro.sen.mipic[2].mpicinte1);
		RS_printf("IO_PRO.SEN.MIPIC2.MPICINTE2        = %x\n", (unsigned int)&ioPro.sen.mipic[2].mpicinte2);
		RS_printf("IO_PRO.SEN.MIPIC2.MPICINTF1        = %x\n", (unsigned int)&ioPro.sen.mipic[2].mpicintf1);
		RS_printf("IO_PRO.SEN.MIPIC2.MPICINTF2        = %x\n", (unsigned int)&ioPro.sen.mipic[2].mpicintf2);
		RS_printf("IO_PRO.SEN.MIPIC2.MPICLMODE        = %x\n", (unsigned int)&ioPro.sen.mipic[2].mpiclmode);
		RS_printf("IO_PRO.SEN.MIPIC2.MPICIOMD0        = %x\n", (unsigned int)&ioPro.sen.mipic[2].mpiciomd0);
		RS_printf("IO_PRO.SEN.MIPIC2.MPICIOMD1        = %x\n", (unsigned int)&ioPro.sen.mipic[2].mpiciomd1);
		RS_printf("IO_PRO.SEN.MIPIC2.MPICPVR          = %x\n", (unsigned int)&ioPro.sen.mipic[2].mpicpvr);
		RS_printf("IO_PRO.SEN.MIPIC2.MPICHDPDSEL      = %x\n", (unsigned int)&ioPro.sen.mipic[2].mpichdpdsel);
		RS_printf("IO_PRO.SEN.MIPIC2.MPICCPI1         = %x\n", (unsigned int)&ioPro.sen.mipic[2].mpiccpi1);
		RS_printf("IO_PRO.SEN.MIPIC2.MPICCPI2         = %x\n", (unsigned int)&ioPro.sen.mipic[2].mpiccpi2);
		RS_printf("IO_PRO.SEN.MIPIC2.MPICPRLRLCONF    = %x\n", (unsigned int)&ioPro.sen.mipic[2].mpicprlrlconf);
		RS_printf("IO_PRO.SEN.MIPIC2.MPICPRLRLTPSEL   = %x\n", (unsigned int)&ioPro.sen.mipic[2].mpicprlrltpsel);
		RS_printf("IO_PRO.SEN.MIPIC2.MPICPRLRPRBS     = %x\n", (unsigned int)&ioPro.sen.mipic[2].mpicprlrprbs);
		RS_printf("IO_PRO.SEN.MIPIC2.MPICPRLRLST      = %x\n", (unsigned int)&ioPro.sen.mipic[2].mpicprlrlst);
		RS_printf("IO_PRO.SEN.MIPIC2.MPICPRLRWECNT0   = %x\n", (unsigned int)&ioPro.sen.mipic[2].mpicprlrwecnt0);
		RS_printf("IO_PRO.SEN.MIPIC2.MPICPRLRWECNT1   = %x\n", (unsigned int)&ioPro.sen.mipic[2].mpicprlrwecnt1);
		RS_printf("IO_PRO.SEN.MIPIC2.MPICPRLRWECNT2   = %x\n", (unsigned int)&ioPro.sen.mipic[2].mpicprlrwecnt2);
		RS_printf("IO_PRO.SEN.MIPIC2.MPICPRLRWCNT0    = %x\n", (unsigned int)&ioPro.sen.mipic[2].mpicprlrwcnt0);
		RS_printf("IO_PRO.SEN.MIPIC2.MPICPRLRWCNT1    = %x\n", (unsigned int)&ioPro.sen.mipic[2].mpicprlrwcnt1);
		RS_printf("IO_PRO.SEN.MIPIC2.MPICPRLRWCNT2    = %x\n", (unsigned int)&ioPro.sen.mipic[2].mpicprlrwcnt2);
		RS_printf("IO_PRO.SEN.MIPIC2.MPICPRLRSERRCNT0 = %x\n", (unsigned int)&ioPro.sen.mipic[2].mpicprlrserrcnt0);
		RS_printf("IO_PRO.SEN.MIPIC2.MPICPRLRSERRCNT1 = %x\n", (unsigned int)&ioPro.sen.mipic[2].mpicprlrserrcnt1);
		RS_printf("IO_PRO.SEN.MIPIC2.MPICPRLRSERRCNT2 = %x\n", (unsigned int)&ioPro.sen.mipic[2].mpicprlrserrcnt2);
		RS_printf("IO_PRO.SEN.MIPIC2.MPICPRLRSERRLOC0 = %x\n", (unsigned int)&ioPro.sen.mipic[2].mpicprlrserrloc0);
		RS_printf("IO_PRO.SEN.MIPIC2.MPICPRLRSERRLOC1 = %x\n", (unsigned int)&ioPro.sen.mipic[2].mpicprlrserrloc1);
		RS_printf("IO_PRO.SEN.MIPIC2.MPICPRLRSERRLOC2 = %x\n", (unsigned int)&ioPro.sen.mipic[2].mpicprlrserrloc2);
		RS_printf("IO_PRO.SEN.MIPIC2.MPICPPROGSEQ     = %x\n", (unsigned int)&ioPro.sen.mipic[2].mpicpprogseq);

		// MIPIC3
		RS_printf("IO_PRO.SEN.MIPIC3.MPICSR           = %x\n", (unsigned int)&ioPro.sen.mipic[3].mpicsr);
		RS_printf("IO_PRO.SEN.MIPIC3.MPICTRG          = %x\n", (unsigned int)&ioPro.sen.mipic[3].mpictrg);
		RS_printf("IO_PRO.SEN.MIPIC3.MPICPAEN0        = %x\n", (unsigned int)&ioPro.sen.mipic[3].mpicpaen0);
		RS_printf("IO_PRO.SEN.MIPIC3.MPICPAEN1        = %x\n", (unsigned int)&ioPro.sen.mipic[3].mpicpaen1);
		RS_printf("IO_PRO.SEN.MIPIC3.MPICINTE1        = %x\n", (unsigned int)&ioPro.sen.mipic[3].mpicinte1);
		RS_printf("IO_PRO.SEN.MIPIC3.MPICINTE2        = %x\n", (unsigned int)&ioPro.sen.mipic[3].mpicinte2);
		RS_printf("IO_PRO.SEN.MIPIC3.MPICINTF1        = %x\n", (unsigned int)&ioPro.sen.mipic[3].mpicintf1);
		RS_printf("IO_PRO.SEN.MIPIC3.MPICINTF2        = %x\n", (unsigned int)&ioPro.sen.mipic[3].mpicintf2);
		RS_printf("IO_PRO.SEN.MIPIC3.MPICLMODE        = %x\n", (unsigned int)&ioPro.sen.mipic[3].mpiclmode);
		RS_printf("IO_PRO.SEN.MIPIC3.MPICIOMD0        = %x\n", (unsigned int)&ioPro.sen.mipic[3].mpiciomd0);
		RS_printf("IO_PRO.SEN.MIPIC3.MPICIOMD1        = %x\n", (unsigned int)&ioPro.sen.mipic[3].mpiciomd1);
		RS_printf("IO_PRO.SEN.MIPIC3.MPICPVR          = %x\n", (unsigned int)&ioPro.sen.mipic[3].mpicpvr);
		RS_printf("IO_PRO.SEN.MIPIC3.MPICHDPDSEL      = %x\n", (unsigned int)&ioPro.sen.mipic[3].mpichdpdsel);
		RS_printf("IO_PRO.SEN.MIPIC3.MPICCPI1         = %x\n", (unsigned int)&ioPro.sen.mipic[3].mpiccpi1);
		RS_printf("IO_PRO.SEN.MIPIC3.MPICCPI2         = %x\n", (unsigned int)&ioPro.sen.mipic[3].mpiccpi2);
		RS_printf("IO_PRO.SEN.MIPIC3.MPICPRLRLCONF    = %x\n", (unsigned int)&ioPro.sen.mipic[3].mpicprlrlconf);
		RS_printf("IO_PRO.SEN.MIPIC3.MPICPRLRLTPSEL   = %x\n", (unsigned int)&ioPro.sen.mipic[3].mpicprlrltpsel);
		RS_printf("IO_PRO.SEN.MIPIC3.MPICPRLRPRBS     = %x\n", (unsigned int)&ioPro.sen.mipic[3].mpicprlrprbs);
		RS_printf("IO_PRO.SEN.MIPIC3.MPICPRLRLST      = %x\n", (unsigned int)&ioPro.sen.mipic[3].mpicprlrlst);
		RS_printf("IO_PRO.SEN.MIPIC3.MPICPRLRWECNT0   = %x\n", (unsigned int)&ioPro.sen.mipic[3].mpicprlrwecnt0);
		RS_printf("IO_PRO.SEN.MIPIC3.MPICPRLRWECNT1   = %x\n", (unsigned int)&ioPro.sen.mipic[3].mpicprlrwecnt1);
		RS_printf("IO_PRO.SEN.MIPIC3.MPICPRLRWECNT2   = %x\n", (unsigned int)&ioPro.sen.mipic[3].mpicprlrwecnt2);
		RS_printf("IO_PRO.SEN.MIPIC3.MPICPRLRWCNT0    = %x\n", (unsigned int)&ioPro.sen.mipic[3].mpicprlrwcnt0);
		RS_printf("IO_PRO.SEN.MIPIC3.MPICPRLRWCNT1    = %x\n", (unsigned int)&ioPro.sen.mipic[3].mpicprlrwcnt1);
		RS_printf("IO_PRO.SEN.MIPIC3.MPICPRLRWCNT2    = %x\n", (unsigned int)&ioPro.sen.mipic[3].mpicprlrwcnt2);
		RS_printf("IO_PRO.SEN.MIPIC3.MPICPRLRSERRCNT0 = %x\n", (unsigned int)&ioPro.sen.mipic[3].mpicprlrserrcnt0);
		RS_printf("IO_PRO.SEN.MIPIC3.MPICPRLRSERRCNT1 = %x\n", (unsigned int)&ioPro.sen.mipic[3].mpicprlrserrcnt1);
		RS_printf("IO_PRO.SEN.MIPIC3.MPICPRLRSERRCNT2 = %x\n", (unsigned int)&ioPro.sen.mipic[3].mpicprlrserrcnt2);
		RS_printf("IO_PRO.SEN.MIPIC3.MPICPRLRSERRLOC0 = %x\n", (unsigned int)&ioPro.sen.mipic[3].mpicprlrserrloc0);
		RS_printf("IO_PRO.SEN.MIPIC3.MPICPRLRSERRLOC1 = %x\n", (unsigned int)&ioPro.sen.mipic[3].mpicprlrserrloc1);
		RS_printf("IO_PRO.SEN.MIPIC3.MPICPRLRSERRLOC2 = %x\n", (unsigned int)&ioPro.sen.mipic[3].mpicprlrserrloc2);
		RS_printf("IO_PRO.SEN.MIPIC3.MPICPPROGSEQ     = %x\n", (unsigned int)&ioPro.sen.mipic[3].mpicpprogseq);

		// MONI-0
		RS_printf("IO_PRO.SEN.MONI0.MONITRG       = %x\n", (unsigned int)&ioPro.sen.moni[0].monitrg);
		RS_printf("IO_PRO.SEN.MONI0.MONICTL       = %x\n", (unsigned int)&ioPro.sen.moni[0].monictl);
		RS_printf("IO_PRO.SEN.MONI0.MONIINTFLG    = %x\n", (unsigned int)&ioPro.sen.moni[0].moniintflg);
		RS_printf("IO_PRO.SEN.MONI0.MONIINTENB    = %x\n", (unsigned int)&ioPro.sen.moni[0].moniintenb);
		RS_printf("IO_PRO.SEN.MONI0.MONIVD        = %x\n", (unsigned int)&ioPro.sen.moni[0].monivd);
		RS_printf("IO_PRO.SEN.MONI0.MONIHD        = %x\n", (unsigned int)&ioPro.sen.moni[0].monihd);
		RS_printf("IO_PRO.SEN.MONI0.MONIEPF       = %x\n", (unsigned int)&ioPro.sen.moni[0].moniepf);
		RS_printf("IO_PRO.SEN.MONI0.MONIEPLMIN    = %x\n", (unsigned int)&ioPro.sen.moni[0].monieplmin);
		RS_printf("IO_PRO.SEN.MONI0.MONIEPLMAX    = %x\n", (unsigned int)&ioPro.sen.moni[0].monieplmax);
		RS_printf("IO_PRO.SEN.MONI0.MONIBLF       = %x\n", (unsigned int)&ioPro.sen.moni[0].moniblf);
		RS_printf("IO_PRO.SEN.MONI0.MONIBLLMIN    = %x\n", (unsigned int)&ioPro.sen.moni[0].monibllmin);
		RS_printf("IO_PRO.SEN.MONI0.MONIBLLMAX    = %x\n", (unsigned int)&ioPro.sen.moni[0].monibllmax);
		RS_printf("IO_PRO.SEN.MONI0.MONIHDEXP     = %x\n", (unsigned int)&ioPro.sen.moni[0].monihdexp);
		RS_printf("IO_PRO.SEN.MONI0.MONIEPFEXP    = %x\n", (unsigned int)&ioPro.sen.moni[0].moniepfexp);
		RS_printf("IO_PRO.SEN.MONI0.MONIBLLMINEXP = %x\n", (unsigned int)&ioPro.sen.moni[0].monibllminexp);
		RS_printf("IO_PRO.SEN.MONI0.MONIBLLMAXEXP = %x\n", (unsigned int)&ioPro.sen.moni[0].monibllmaxexp);

		// MONI-1
		RS_printf("IO_PRO.SEN.MONI1.MONITRG       = %x\n", (unsigned int)&ioPro.sen.moni[1].monitrg);
		RS_printf("IO_PRO.SEN.MONI1.MONICTL       = %x\n", (unsigned int)&ioPro.sen.moni[1].monictl);
		RS_printf("IO_PRO.SEN.MONI1.MONIINTFLG    = %x\n", (unsigned int)&ioPro.sen.moni[1].moniintflg);
		RS_printf("IO_PRO.SEN.MONI1.MONIINTENB    = %x\n", (unsigned int)&ioPro.sen.moni[1].moniintenb);
		RS_printf("IO_PRO.SEN.MONI1.MONIVD        = %x\n", (unsigned int)&ioPro.sen.moni[1].monivd);
		RS_printf("IO_PRO.SEN.MONI1.MONIHD        = %x\n", (unsigned int)&ioPro.sen.moni[1].monihd);
		RS_printf("IO_PRO.SEN.MONI1.MONIEPF       = %x\n", (unsigned int)&ioPro.sen.moni[1].moniepf);
		RS_printf("IO_PRO.SEN.MONI1.MONIEPLMIN    = %x\n", (unsigned int)&ioPro.sen.moni[1].monieplmin);
		RS_printf("IO_PRO.SEN.MONI1.MONIEPLMAX    = %x\n", (unsigned int)&ioPro.sen.moni[1].monieplmax);
		RS_printf("IO_PRO.SEN.MONI1.MONIBLF       = %x\n", (unsigned int)&ioPro.sen.moni[1].moniblf);
		RS_printf("IO_PRO.SEN.MONI1.MONIBLLMIN    = %x\n", (unsigned int)&ioPro.sen.moni[1].monibllmin);
		RS_printf("IO_PRO.SEN.MONI1.MONIBLLMAX    = %x\n", (unsigned int)&ioPro.sen.moni[1].monibllmax);
		RS_printf("IO_PRO.SEN.MONI1.MONIHDEXP     = %x\n", (unsigned int)&ioPro.sen.moni[1].monihdexp);
		RS_printf("IO_PRO.SEN.MONI1.MONIEPFEXP    = %x\n", (unsigned int)&ioPro.sen.moni[1].moniepfexp);
		RS_printf("IO_PRO.SEN.MONI1.MONIBLLMINEXP = %x\n", (unsigned int)&ioPro.sen.moni[1].monibllminexp);
		RS_printf("IO_PRO.SEN.MONI1.MONIBLLMAXEXP = %x\n", (unsigned int)&ioPro.sen.moni[1].monibllmaxexp);

		// MONI-2
		RS_printf("IO_PRO.SEN.MONI2.MONITRG       = %x\n", (unsigned int)&ioPro.sen.moni[2].monitrg);
		RS_printf("IO_PRO.SEN.MONI2.MONICTL       = %x\n", (unsigned int)&ioPro.sen.moni[2].monictl);
		RS_printf("IO_PRO.SEN.MONI2.MONIINTFLG    = %x\n", (unsigned int)&ioPro.sen.moni[2].moniintflg);
		RS_printf("IO_PRO.SEN.MONI2.MONIINTENB    = %x\n", (unsigned int)&ioPro.sen.moni[2].moniintenb);
		RS_printf("IO_PRO.SEN.MONI2.MONIVD        = %x\n", (unsigned int)&ioPro.sen.moni[2].monivd);
		RS_printf("IO_PRO.SEN.MONI2.MONIHD        = %x\n", (unsigned int)&ioPro.sen.moni[2].monihd);
		RS_printf("IO_PRO.SEN.MONI2.MONIEPF       = %x\n", (unsigned int)&ioPro.sen.moni[2].moniepf);
		RS_printf("IO_PRO.SEN.MONI2.MONIEPLMIN    = %x\n", (unsigned int)&ioPro.sen.moni[2].monieplmin);
		RS_printf("IO_PRO.SEN.MONI2.MONIEPLMAX    = %x\n", (unsigned int)&ioPro.sen.moni[2].monieplmax);
		RS_printf("IO_PRO.SEN.MONI2.MONIBLF       = %x\n", (unsigned int)&ioPro.sen.moni[2].moniblf);
		RS_printf("IO_PRO.SEN.MONI2.MONIBLLMIN    = %x\n", (unsigned int)&ioPro.sen.moni[2].monibllmin);
		RS_printf("IO_PRO.SEN.MONI2.MONIBLLMAX    = %x\n", (unsigned int)&ioPro.sen.moni[2].monibllmax);
		RS_printf("IO_PRO.SEN.MONI2.MONIHDEXP     = %x\n", (unsigned int)&ioPro.sen.moni[2].monihdexp);
		RS_printf("IO_PRO.SEN.MONI2.MONIEPFEXP    = %x\n", (unsigned int)&ioPro.sen.moni[2].moniepfexp);
		RS_printf("IO_PRO.SEN.MONI2.MONIBLLMINEXP = %x\n", (unsigned int)&ioPro.sen.moni[2].monibllminexp);
		RS_printf("IO_PRO.SEN.MONI2.MONIBLLMAXEXP = %x\n", (unsigned int)&ioPro.sen.moni[2].monibllmaxexp);

		// MONI-3
		RS_printf("IO_PRO.SEN.MONI3.MONITRG       = %x\n", (unsigned int)&ioPro.sen.moni[3].monitrg);
		RS_printf("IO_PRO.SEN.MONI3.MONICTL       = %x\n", (unsigned int)&ioPro.sen.moni[3].monictl);
		RS_printf("IO_PRO.SEN.MONI3.MONIINTFLG    = %x\n", (unsigned int)&ioPro.sen.moni[3].moniintflg);
		RS_printf("IO_PRO.SEN.MONI3.MONIINTENB    = %x\n", (unsigned int)&ioPro.sen.moni[3].moniintenb);
		RS_printf("IO_PRO.SEN.MONI3.MONIVD        = %x\n", (unsigned int)&ioPro.sen.moni[3].monivd);
		RS_printf("IO_PRO.SEN.MONI3.MONIHD        = %x\n", (unsigned int)&ioPro.sen.moni[3].monihd);
		RS_printf("IO_PRO.SEN.MONI3.MONIEPF       = %x\n", (unsigned int)&ioPro.sen.moni[3].moniepf);
		RS_printf("IO_PRO.SEN.MONI3.MONIEPLMIN    = %x\n", (unsigned int)&ioPro.sen.moni[3].monieplmin);
		RS_printf("IO_PRO.SEN.MONI3.MONIEPLMAX    = %x\n", (unsigned int)&ioPro.sen.moni[3].monieplmax);
		RS_printf("IO_PRO.SEN.MONI3.MONIBLF       = %x\n", (unsigned int)&ioPro.sen.moni[3].moniblf);
		RS_printf("IO_PRO.SEN.MONI3.MONIBLLMIN    = %x\n", (unsigned int)&ioPro.sen.moni[3].monibllmin);
		RS_printf("IO_PRO.SEN.MONI3.MONIBLLMAX    = %x\n", (unsigned int)&ioPro.sen.moni[3].monibllmax);
		RS_printf("IO_PRO.SEN.MONI3.MONIHDEXP     = %x\n", (unsigned int)&ioPro.sen.moni[3].monihdexp);
		RS_printf("IO_PRO.SEN.MONI3.MONIEPFEXP    = %x\n", (unsigned int)&ioPro.sen.moni[3].moniepfexp);
		RS_printf("IO_PRO.SEN.MONI3.MONIBLLMINEXP = %x\n", (unsigned int)&ioPro.sen.moni[3].monibllminexp);
		RS_printf("IO_PRO.SEN.MONI3.MONIBLLMAXEXP = %x\n", (unsigned int)&ioPro.sen.moni[3].monibllmaxexp);

		// LDIV-0
		RS_printf("IO_PRO.SEN.LDIV0.LDIVTRG      = %x\n", (unsigned int)&ioPro.sen.ldiv[0].ldivtrg);
		RS_printf("IO_PRO.SEN.LDIV0.LDIVPAEN     = %x\n", (unsigned int)&ioPro.sen.ldiv[0].ldivpaen);
		RS_printf("IO_PRO.SEN.LDIV0.LDIVCTL      = %x\n", (unsigned int)&ioPro.sen.ldiv[0].ldivctl);
		RS_printf("IO_PRO.SEN.LDIV0.LDIVIHW      = %x\n", (unsigned int)&ioPro.sen.ldiv[0].ldivihw);
		RS_printf("IO_PRO.SEN.LDIV0.LDIVOH       = %x\n", (unsigned int)&ioPro.sen.ldiv[0].ldivoh);
		RS_printf("IO_PRO.SEN.LDIV0.LDIVOHW      = %x\n", (unsigned int)&ioPro.sen.ldiv[0].ldivohw);
		RS_printf("IO_PRO.SEN.LDIV0.LDIVINTENB   = %x\n", (unsigned int)&ioPro.sen.ldiv[0].ldivintenb);
		RS_printf("IO_PRO.SEN.LDIV0.LDIVINTFLG   = %x\n", (unsigned int)&ioPro.sen.ldiv[0].ldivintflg);

		// LDIV-1
		RS_printf("IO_PRO.SEN.LDIV1.LDIVTRG      = %x\n", (unsigned int)&ioPro.sen.ldiv[1].ldivtrg);
		RS_printf("IO_PRO.SEN.LDIV1.LDIVPAEN     = %x\n", (unsigned int)&ioPro.sen.ldiv[1].ldivpaen);
		RS_printf("IO_PRO.SEN.LDIV1.LDIVCTL      = %x\n", (unsigned int)&ioPro.sen.ldiv[1].ldivctl);
		RS_printf("IO_PRO.SEN.LDIV1.LDIVIHW      = %x\n", (unsigned int)&ioPro.sen.ldiv[1].ldivihw);
		RS_printf("IO_PRO.SEN.LDIV1.LDIVOH       = %x\n", (unsigned int)&ioPro.sen.ldiv[1].ldivoh);
		RS_printf("IO_PRO.SEN.LDIV1.LDIVOHW      = %x\n", (unsigned int)&ioPro.sen.ldiv[1].ldivohw);
		RS_printf("IO_PRO.SEN.LDIV1.LDIVINTENB   = %x\n", (unsigned int)&ioPro.sen.ldiv[1].ldivintenb);
		RS_printf("IO_PRO.SEN.LDIV1.LDIVINTFLG   = %x\n", (unsigned int)&ioPro.sen.ldiv[1].ldivintflg);

		// LDIV-2
		RS_printf("IO_PRO.SEN.LDIV2.LDIVTRG      = %x\n", (unsigned int)&ioPro.sen.ldiv[2].ldivtrg);
		RS_printf("IO_PRO.SEN.LDIV2.LDIVPAEN     = %x\n", (unsigned int)&ioPro.sen.ldiv[2].ldivpaen);
		RS_printf("IO_PRO.SEN.LDIV2.LDIVCTL      = %x\n", (unsigned int)&ioPro.sen.ldiv[2].ldivctl);
		RS_printf("IO_PRO.SEN.LDIV2.LDIVIHW      = %x\n", (unsigned int)&ioPro.sen.ldiv[2].ldivihw);
		RS_printf("IO_PRO.SEN.LDIV2.LDIVOH       = %x\n", (unsigned int)&ioPro.sen.ldiv[2].ldivoh);
		RS_printf("IO_PRO.SEN.LDIV2.LDIVOHW      = %x\n", (unsigned int)&ioPro.sen.ldiv[2].ldivohw);
		RS_printf("IO_PRO.SEN.LDIV2.LDIVINTENB   = %x\n", (unsigned int)&ioPro.sen.ldiv[2].ldivintenb);
		RS_printf("IO_PRO.SEN.LDIV2.LDIVINTFLG   = %x\n", (unsigned int)&ioPro.sen.ldiv[2].ldivintflg);

		// LDIV-3
		RS_printf("IO_PRO.SEN.LDIV3.LDIVTRG      = %x\n", (unsigned int)&ioPro.sen.ldiv[3].ldivtrg);
		RS_printf("IO_PRO.SEN.LDIV3.LDIVPAEN     = %x\n", (unsigned int)&ioPro.sen.ldiv[3].ldivpaen);
		RS_printf("IO_PRO.SEN.LDIV3.LDIVCTL      = %x\n", (unsigned int)&ioPro.sen.ldiv[3].ldivctl);
		RS_printf("IO_PRO.SEN.LDIV3.LDIVIHW      = %x\n", (unsigned int)&ioPro.sen.ldiv[3].ldivihw);
		RS_printf("IO_PRO.SEN.LDIV3.LDIVOH       = %x\n", (unsigned int)&ioPro.sen.ldiv[3].ldivoh);
		RS_printf("IO_PRO.SEN.LDIV3.LDIVOHW      = %x\n", (unsigned int)&ioPro.sen.ldiv[3].ldivohw);
		RS_printf("IO_PRO.SEN.LDIV3.LDIVINTENB   = %x\n", (unsigned int)&ioPro.sen.ldiv[3].ldivintenb);
		RS_printf("IO_PRO.SEN.LDIV3.LDIVINTFLG   = %x\n", (unsigned int)&ioPro.sen.ldiv[3].ldivintflg);

		// LNR-0
		RS_printf("IO_PRO.SEN.LNR0.LNRTRG        = %x\n", (unsigned int)&ioPro.sen.lnr[0].lnrtrg);
		RS_printf("IO_PRO.SEN.LNR0.LNRBR         = %x\n", (unsigned int)&ioPro.sen.lnr[0].lnrbr);
		RS_printf("IO_PRO.SEN.LNR0.LNRINCR       = %x\n", (unsigned int)&ioPro.sen.lnr[0].lnrincr);
		RS_printf("IO_PRO.SEN.LNR0.LNROFSR       = %x\n", (unsigned int)&ioPro.sen.lnr[0].lnrofsr);
		RS_printf("IO_PRO.SEN.LNR0.LNRBGR        = %x\n", (unsigned int)&ioPro.sen.lnr[0].lnrbgr);
		RS_printf("IO_PRO.SEN.LNR0.LNRINCGR      = %x\n", (unsigned int)&ioPro.sen.lnr[0].lnrincgr);
		RS_printf("IO_PRO.SEN.LNR0.LNROFSGR      = %x\n", (unsigned int)&ioPro.sen.lnr[0].lnrofsgr);
		RS_printf("IO_PRO.SEN.LNR0.LNRBGB        = %x\n", (unsigned int)&ioPro.sen.lnr[0].lnrbgb);
		RS_printf("IO_PRO.SEN.LNR0.LNRINCGB      = %x\n", (unsigned int)&ioPro.sen.lnr[0].lnrincgb);
		RS_printf("IO_PRO.SEN.LNR0.LNROFSGB      = %x\n", (unsigned int)&ioPro.sen.lnr[0].lnrofsgb);
		RS_printf("IO_PRO.SEN.LNR0.LNRBB         = %x\n", (unsigned int)&ioPro.sen.lnr[0].lnrbb);
		RS_printf("IO_PRO.SEN.LNR0.LNRINCB       = %x\n", (unsigned int)&ioPro.sen.lnr[0].lnrincb);
		RS_printf("IO_PRO.SEN.LNR0.LNROFSB       = %x\n", (unsigned int)&ioPro.sen.lnr[0].lnrofsb);

		// LNR-1
		RS_printf("IO_PRO.SEN.LNR1.LNRTRG        = %x\n", (unsigned int)&ioPro.sen.lnr[1].lnrtrg);
		RS_printf("IO_PRO.SEN.LNR1.LNRBR         = %x\n", (unsigned int)&ioPro.sen.lnr[1].lnrbr);
		RS_printf("IO_PRO.SEN.LNR1.LNRINCR       = %x\n", (unsigned int)&ioPro.sen.lnr[1].lnrincr);
		RS_printf("IO_PRO.SEN.LNR1.LNROFSR       = %x\n", (unsigned int)&ioPro.sen.lnr[1].lnrofsr);
		RS_printf("IO_PRO.SEN.LNR1.LNRBGR        = %x\n", (unsigned int)&ioPro.sen.lnr[1].lnrbgr);
		RS_printf("IO_PRO.SEN.LNR1.LNRINCGR      = %x\n", (unsigned int)&ioPro.sen.lnr[1].lnrincgr);
		RS_printf("IO_PRO.SEN.LNR1.LNROFSGR      = %x\n", (unsigned int)&ioPro.sen.lnr[1].lnrofsgr);
		RS_printf("IO_PRO.SEN.LNR1.LNRBGB        = %x\n", (unsigned int)&ioPro.sen.lnr[1].lnrbgb);
		RS_printf("IO_PRO.SEN.LNR1.LNRINCGB      = %x\n", (unsigned int)&ioPro.sen.lnr[1].lnrincgb);
		RS_printf("IO_PRO.SEN.LNR1.LNROFSGB      = %x\n", (unsigned int)&ioPro.sen.lnr[1].lnrofsgb);
		RS_printf("IO_PRO.SEN.LNR1.LNRBB         = %x\n", (unsigned int)&ioPro.sen.lnr[1].lnrbb);
		RS_printf("IO_PRO.SEN.LNR1.LNRINCB       = %x\n", (unsigned int)&ioPro.sen.lnr[1].lnrincb);
		RS_printf("IO_PRO.SEN.LNR1.LNROFSB       = %x\n", (unsigned int)&ioPro.sen.lnr[1].lnrofsb);

		// LNR-2
		RS_printf("IO_PRO.SEN.LNR2.LNRTRG        = %x\n", (unsigned int)&ioPro.sen.lnr[2].lnrtrg);
		RS_printf("IO_PRO.SEN.LNR2.LNRBR         = %x\n", (unsigned int)&ioPro.sen.lnr[2].lnrbr);
		RS_printf("IO_PRO.SEN.LNR2.LNRINCR       = %x\n", (unsigned int)&ioPro.sen.lnr[2].lnrincr);
		RS_printf("IO_PRO.SEN.LNR2.LNROFSR       = %x\n", (unsigned int)&ioPro.sen.lnr[2].lnrofsr);
		RS_printf("IO_PRO.SEN.LNR2.LNRBGR        = %x\n", (unsigned int)&ioPro.sen.lnr[2].lnrbgr);
		RS_printf("IO_PRO.SEN.LNR2.LNRINCGR      = %x\n", (unsigned int)&ioPro.sen.lnr[2].lnrincgr);
		RS_printf("IO_PRO.SEN.LNR2.LNROFSGR      = %x\n", (unsigned int)&ioPro.sen.lnr[2].lnrofsgr);
		RS_printf("IO_PRO.SEN.LNR2.LNRBGB        = %x\n", (unsigned int)&ioPro.sen.lnr[2].lnrbgb);
		RS_printf("IO_PRO.SEN.LNR2.LNRINCGB      = %x\n", (unsigned int)&ioPro.sen.lnr[2].lnrincgb);
		RS_printf("IO_PRO.SEN.LNR2.LNROFSGB      = %x\n", (unsigned int)&ioPro.sen.lnr[2].lnrofsgb);
		RS_printf("IO_PRO.SEN.LNR2.LNRBB         = %x\n", (unsigned int)&ioPro.sen.lnr[2].lnrbb);
		RS_printf("IO_PRO.SEN.LNR2.LNRINCB       = %x\n", (unsigned int)&ioPro.sen.lnr[2].lnrincb);
		RS_printf("IO_PRO.SEN.LNR2.LNROFSB       = %x\n", (unsigned int)&ioPro.sen.lnr[2].lnrofsb);

		// LNR-3
		RS_printf("IO_PRO.SEN.LNR3.LNRTRG        = %x\n", (unsigned int)&ioPro.sen.lnr[3].lnrtrg);
		RS_printf("IO_PRO.SEN.LNR3.LNRBR         = %x\n", (unsigned int)&ioPro.sen.lnr[3].lnrbr);
		RS_printf("IO_PRO.SEN.LNR3.LNRINCR       = %x\n", (unsigned int)&ioPro.sen.lnr[3].lnrincr);
		RS_printf("IO_PRO.SEN.LNR3.LNROFSR       = %x\n", (unsigned int)&ioPro.sen.lnr[3].lnrofsr);
		RS_printf("IO_PRO.SEN.LNR3.LNRBGR        = %x\n", (unsigned int)&ioPro.sen.lnr[3].lnrbgr);
		RS_printf("IO_PRO.SEN.LNR3.LNRINCGR      = %x\n", (unsigned int)&ioPro.sen.lnr[3].lnrincgr);
		RS_printf("IO_PRO.SEN.LNR3.LNROFSGR      = %x\n", (unsigned int)&ioPro.sen.lnr[3].lnrofsgr);
		RS_printf("IO_PRO.SEN.LNR3.LNRBGB        = %x\n", (unsigned int)&ioPro.sen.lnr[3].lnrbgb);
		RS_printf("IO_PRO.SEN.LNR3.LNRINCGB      = %x\n", (unsigned int)&ioPro.sen.lnr[3].lnrincgb);
		RS_printf("IO_PRO.SEN.LNR3.LNROFSGB      = %x\n", (unsigned int)&ioPro.sen.lnr[3].lnrofsgb);
		RS_printf("IO_PRO.SEN.LNR3.LNRBB         = %x\n", (unsigned int)&ioPro.sen.lnr[3].lnrbb);
		RS_printf("IO_PRO.SEN.LNR3.LNRINCB       = %x\n", (unsigned int)&ioPro.sen.lnr[3].lnrincb);
		RS_printf("IO_PRO.SEN.LNR3.LNROFSB       = %x\n", (unsigned int)&ioPro.sen.lnr[3].lnrofsb);

	}

#endif	/** SEN Unit **/
#endif  /* if 0 */

}

ProTest1* pro_test1_new(void)
{
	ProTest1* self = k_object_new_with_private(PRO_TYPE_TEST1, sizeof(ProTest1Private));

	return self;
}

