/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-03
*@author : 陈阳
*@brief : ImProDebug
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "improdebug.h"



K_TYPE_DEFINE_WITH_PRIVATE(ImProDebug, im_pro_debug)
#define IM_PRO_DEBUG_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), ImProDebugPrivate, IM_TYPE_PRO_DEBUG))


struct _ImProDebugPrivate
{
    volatile struct IoPro		ioPro;
};


static void im_pro_debug_constructor(ImProDebug *self)
{
	ImProDebugPrivate *priv = IM_PRO_DEBUG_GET_PRIVATE(self);
    priv->ioPro = ioPro;
}

static void im_pro_debug_destructor(ImProDebug *self)
{
	ImProDebugPrivate *priv = IM_PRO_DEBUG_GET_PRIVATE(self);
}

#ifndef CO_CT_IM_PRO_DISABLE
#ifdef CO_DEBUG_ON_PC
void im_pro_debug_pwch_intflg_fill(ImProDebug *self, kuint32 unitNo, kuint32 blockNum, kuint32 ch, kuint32 inte, kuint32 intf )
{
    const T_IM_PRO_COMMON_PWCH_INFO* pwchInfo;
    im_pro_comm_get_pwch_reg_info( unitNo, blockNum, ch, &pwchInfo );

    if( pwchInfo->regPtr == NULL ) {
        DriverCommon_DDIM_PRINT(( "im_pro_debug_pwch_intflg_fill(ImProDebug *self, %u %u %u ) not exist.\n", unitNo, blockNum, ch ));
        return;
    }
    pwchInfo->regPtr->pwchintenb.word = inte;
    pwchInfo->regPtr->pwchintflg.word = intf;

    im_pro_comm_set_pwch_axi_response( unitNo, blockNum, ch, 0xFF );
}

void im_pro_debug_prch_intflg_fill(ImProDebug *self, kuint32 unitNo, kuint32 blockNum, kuint32 ch, kuint32 inte, kuint32 intf )
{
    const T_IM_PRO_COMMON_PRCH_INFO* prchInfo;
    im_pro_comm_get_prch_reg_info( unitNo, blockNum, ch, &prchInfo );

    if( prchInfo->regPtr == NULL ) {
        DriverCommon_DDIM_PRINT(( "im_pro_debug_prch_intflg_fill(ImProDebug *self, %u %u %u ) not exist.\n", unitNo, blockNum, ch ));
        return;
    }
    prchInfo->regPtr->prchintenb.word = inte;
    prchInfo->regPtr->prchintflg.word = intf;

    im_pro_comm_set_prch_axi_response( unitNo, blockNum, ch, 0xFF );
}

void im_pro_debug_ldiv_intflg_fill(ImProDebug *self, kuint32 ch, kuint32 inte, kuint32 intf )
{
    priv->ioPro.sen.ldiv[ch].ldivintenb.word = inte;
    priv->ioPro.sen.ldiv[ch].ldivintflg.word = intf;
}

void im_pro_debug_obd_intflg_fill(ImProDebug *self, kuint32 blockNum, kuint32 ch, kuint32 inte, kuint32 intf )
{
    priv->ioPro.sen.obd[blockNum][ch].obdintenb.word = inte;
    priv->ioPro.sen.obd[blockNum][ch].obdintflg.word = intf;
}

void im_pro_debug_obt_intflg_fill(ImProDebug *self, kuint32 blockNum, kuint32 ch, kuint32 inte, kuint32 intf )
{
    priv->ioPro.sen.obt[blockNum][ch].obtintenb.word = inte;
    priv->ioPro.sen.obt[blockNum][ch].obtintflg.word = intf;
}

void im_pro_debug_sentop_vd_intflg_fill(ImProDebug *self, kuint32 vdInte, kuint32 vdIntf, kuint32 sgVdInte, 
kuint32 sgVdIntf, kuint32 gyroVdInte, kuint32 gyroVdIntf )
{
    priv->ioPro.sen.sentop.vhdintenb.vhdintenb1.word = vdInte;
    priv->ioPro.sen.sentop.vhdintflg.vhdintflg1.word = vdIntf;

    priv->ioPro.sen.sentop.sgvhdintenb.word          = sgVdInte;
    priv->ioPro.sen.sentop.sgvhdintflg.word          = sgVdIntf;

    priv->ioPro.sen.sentop.gintenb.word              = gyroVdInte;
    priv->ioPro.sen.sentop.gintflg.word              = gyroVdIntf;
}

void im_pro_debug_sentop_hd_intflg_fill(ImProDebug *self, kuint32 hdInte, kuint32 hdIntf, kuint32 sgHdInte, kuint32 sgHdIntf )
{
    priv->ioPro.sen.sentop.vhdintenb.vhdintenb2.word = hdInte;
    priv->ioPro.sen.sentop.vhdintflg.vhdintflg2.word = hdIntf;

    priv->ioPro.sen.sentop.sgvhdintenb.word          = sgHdInte;
    priv->ioPro.sen.sentop.sgvhdintflg.word          = sgHdIntf;
}

void im_pro_debug_slvs_comm_intflg_fill(ImProDebug *self, kuint32 inte, kuint32 intf )
{
    priv->ioPro.sen.slvsec.common.peintst.word   = inte;
    priv->ioPro.sen.slvsec.common.peinten.word   = intf;
}

void im_pro_debug_slvs_strm_intflg_fill(ImProDebug *self, kuint32 ch, kuint32 inte, kuint32 intf, kuint32 leinte, 
kuint32 leintf, kuint32 meinte0, kuint32 meintf0, kuint32 meinte1, kuint32 meintf1 )
{
    priv->ioPro.sen.slvsec.stream[ch].inten.word     = inte;
    priv->ioPro.sen.slvsec.stream[ch].intst.word     = intf;
    priv->ioPro.sen.slvsec.stream[ch].leinten.word   = leinte;
    priv->ioPro.sen.slvsec.stream[ch].leintst.word   = leintf;
    priv->ioPro.sen.slvsec.stream[ch].meinten0.word  = meinte0;
    priv->ioPro.sen.slvsec.stream[ch].meintst0.word  = meintf0;
    priv->ioPro.sen.slvsec.stream[ch].meinten1.word  = meinte1;
    priv->ioPro.sen.slvsec.stream[ch].meintst1.word  = meintf1;
}

void im_pro_debug_lvds_intflg_fill(ImProDebug *self, kuint32 ch, kuint32 inte1, kuint32 intf1, kuint32 inte2, kuint32 intf2, 
kuint32 inte3, kuint32 intf3 )
{
    priv->ioPro.sen.lvds[ch].lvdsintenb0.word    = inte1;
    priv->ioPro.sen.lvds[ch].lvdsintflg0.word    = intf1;
    priv->ioPro.sen.lvds[ch].lvdsintenb1.word    = inte2;
    priv->ioPro.sen.lvds[ch].lvdsintflg1.word    = intf2;
    priv->ioPro.sen.lvds[ch].lvdsintenb2.word    = inte3;
    priv->ioPro.sen.lvds[ch].lvdsintflg2.word    = intf3;
}

void im_pro_debug_dmipi_intflg_fill(ImProDebug *self, kuint32 ch, kuint32 inte, kuint32 intf )
{
    priv->ioPro.sen.mipid[ch].mpiinte.word   = inte;
    priv->ioPro.sen.mipid[ch].mpiintf.word   = intf;
}

void im_pro_debug_cmipi_intflg_fill(ImProDebug *self, kuint32 ch, kuint32 inte1, kuint32 intf1, kuint32 inte2, kuint32 intf2 )
{
    priv->ioPro.sen.mipic[ch].mpicinte1.word = inte1;
    priv->ioPro.sen.mipic[ch].mpicintf1.word = intf1;
    priv->ioPro.sen.mipic[ch].mpicinte2.word = inte2;
    priv->ioPro.sen.mipic[ch].mpicintf2.word = intf2;
}

void im_pro_debug_moni_intflg_fill(ImProDebug *self, kuint32 ch, kuint32 inte, kuint32 intf )
{
    priv->ioPro.sen.MONI[ch].moniintenb.word = inte;
    priv->ioPro.sen.MONI[ch].moniintflg.word = intf;
}

void im_pro_debug_sro_moni_intflg_fill(ImProDebug *self, kuint32 unitNo, kuint32 inte, kuint32 intf )
{
    priv->ioPro.imgPipe[unitNo].sro.moni0.moniintenb.word  = inte;
    priv->ioPro.imgPipe[unitNo].sro.moni0.moniintflg.word  = intf;
}

void im_pro_debug_sro_sdc_intflg_fill(ImProDebug *self, kuint32 unitNo, kuint32 ch, kuint32 inte, kuint32 intf )
{
    priv->ioPro.imgPipe[unitNo].sro.sdc[ch].sdcintenb.word = inte;
    priv->ioPro.imgPipe[unitNo].sro.sdc[ch].sdcintflg.word = intf;
}

void im_pro_debug_srotop_vd_intflg_fill(ImProDebug *self, kuint32 unitNo, kuint32 vdInte, kuint32 vdIntf )
{
    priv->ioPro.imgPipe[unitNo].sro.srotop.vhdintenb.word  |= vdInte;
    priv->ioPro.imgPipe[unitNo].sro.srotop.vhdintflg.word  |= vdIntf;
}

void im_pro_debug_srotop_hd_intflg_fill(ImProDebug *self, kuint32 unitNo, kuint32 hdInte, kuint32 hdIntf )
{
    priv->ioPro.imgPipe[unitNo].sro.srotop.vhdintenb.word  |= hdInte;
    priv->ioPro.imgPipe[unitNo].sro.srotop.vhdintflg.word  |= hdIntf;
}

void im_pro_debug_b2btop_vd_intflg_fill(ImProDebug *self, kuint32 unitNo, kuint32 vdInte, kuint32 vdIntf )
{
    priv->ioPro.imgPipe[unitNo].b2b.b2btop.vhdintenb.word  |= vdInte;
    priv->ioPro.imgPipe[unitNo].b2b.b2btop.vhdintflg.word  |= vdIntf;
}

void im_pro_debug_b2btop_hd_intflg_fill(ImProDebug *self, kuint32 unitNo, kuint32 hdInte, kuint32 hdIntf )
{
    priv->ioPro.imgPipe[unitNo].b2b.b2btop.vhdintenb.word  |= hdInte;
    priv->ioPro.imgPipe[unitNo].b2b.b2btop.vhdintflg.word  |= hdIntf;
}

void im_pro_debug_stat_aeawb_intflg_fill(ImProDebug *self, kuint32 ch, kuint32 aeawbInte, kuint32 aeawbIntf )
{
    priv->ioPro.stat.aeawb[ch].lineintenb.word = aeawbInte;
    priv->ioPro.stat.aeawb[ch].lineintflg.word = aeawbIntf;

    priv->ioPro.stat.aeawb[ch].linev.linev1.bit.linev_0 = 32766;
    priv->ioPro.stat.aeawb[ch].linev.linev1.bit.linev_1 = 32766;
    priv->ioPro.stat.aeawb[ch].linev.linev2.bit.linev_2 = 32766;
    priv->ioPro.stat.aeawb[ch].linev.linev2.bit.linev_3 = 32766;
}

void im_pro_debug_stat_af_intflg_fill(ImProDebug *self, kuint32 ch, kuint32 afInte, kuint32 afIntf )
{
    kuchar   i;

    priv->ioPro.stat.af[ch].afgbal.afintenb.word = afInte;
    priv->ioPro.stat.af[ch].afgbal.afintflg.word = afIntf;

    for (i = E_IM_PRO_AF_WINDOW_MAX; i > 0; i --){
        priv->ioPro.stat.af[ch].afwin[ i - 1 ].afdatas.word              = 0x10000000;
        priv->ioPro.stat.af[ch].afwin[ i - 1 ].afdatage.word             = 0x10000000;
        priv->ioPro.stat.af[ch].afwin[ i - 1 ].afdatal.word              = 0x10000000;
        priv->ioPro.stat.af[ch].afwin[ i - 1 ].afdatah0.word             = 0x10000000;
        priv->ioPro.stat.af[ch].afwin[ i - 1 ].afdatah1.word             = 0x10000000;
        priv->ioPro.stat.af[ch].afwin[ i - 1 ].afdatah2.word             = 0x10000000;
        priv->ioPro.stat.af[ch].afwin[ i - 1 ].AFDATAV.word              = 0x10000000;
        priv->ioPro.stat.af[ch].afwin[ i - 1 ].afdatamax.bit.afdatamax   = 0xFFF;
        priv->ioPro.stat.af[ch].afwin[ i - 1 ].afdatamin.bit.afdatamin   = 0xFFF;
        priv->ioPro.stat.af[ch].afwin[ i - 1 ].afdatamax.bit.afdatamaxe  = 0xFFF;
        priv->ioPro.stat.af[ch].afwin[ i - 1 ].afdatamin.bit.afdatamine  = 0xFFF;
        priv->ioPro.stat.af[ch].afwin[ i - 1 ].afdatamh0.word            = 0x10000000;
        priv->ioPro.stat.af[ch].afwin[ i - 1 ].afdatamh1.word            = 0x10000000;
        priv->ioPro.stat.af[ch].afwin[ i - 1 ].afdatamh2.word            = 0x10000000;
    }
}

void im_pro_debug_stat_hist_intflg_fill(ImProDebug *self, kuint32 ch, kuint32 histInte, kuint32 histIntf )
{
    priv->ioPro.stat.hist[ch].histintenb.word = histInte;
    priv->ioPro.stat.hist[ch].histintflg.word = histIntf;
    memset( (void*)&ioProTbl.statTbl.histdata[ch].histrdata.word[0], 0x1FFFFFF, 
    sizeof(ioProTbl.statTbl.histdata[ch].histrdata.word) );
    memset( (void*)&ioProTbl.statTbl.histdata[ch].histgdata.word[0], 0x1FFFFFF, 
    sizeof(ioProTbl.statTbl.histdata[ch].histgdata.word) );
    memset( (void*)&ioProTbl.statTbl.histdata[ch].histbdata.word[0], 0x1FFFFFF, 
    sizeof(ioProTbl.statTbl.histdata[ch].histbdata.word) );
    memset( (void*)&ioProTbl.statTbl.histdata[ch].histydata.word[0], 0x1FFFFFF, 
    sizeof(ioProTbl.statTbl.histdata[ch].histydata.word) );
}

void im_pro_debug_pastop_vd_intflg_fill(ImProDebug *self, kuint32 unitNo, kuint32 vdInte, kuint32 vdIntf )
{
    priv->ioPro.pas.pastop.vhdintenb.word    |= vdInte;
    priv->ioPro.pas.pastop.vhdintflg.word    |= vdIntf;
}

void im_pro_debug_pastop_hd_intflg_fill(ImProDebug *self, kuint32 unitNo, kuint32 hdInte, kuint32 hdIntf )
{
    priv->ioPro.pas.pastop.vhdintenb.word    |= hdInte;
    priv->ioPro.pas.pastop.vhdintflg.word    |= hdIntf;
}
#endif  // CO_DEBUG_ON_PC
#endif  // CO_CT_IM_PRO_DISABLE

ImProDebug* im_pro_debug_new(void)
{
	ImProDebug* self = k_object_new_with_private(IM_TYPE_PRO_DEBUG, sizeof(ImProDebugPrivate));

	return self;
}

ImProDebug* im_pro_debug_get(void)
{
	static ImProDebug* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IM_TYPE_PRO_DEBUG, sizeof(ImProDebugPrivate));
	}

	return self;
}
