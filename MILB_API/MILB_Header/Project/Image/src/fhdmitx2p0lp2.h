/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-10
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


#ifndef __F_HDMITX2P0_LP2_H__
#define __F_HDMITX2P0_LP2_H__


#include <klib.h>


#define F_TYPE_HDMITX2P0_LP2			(f_hdmitx2p0_lp2_get_type())
#define F_HDMITX2P0_LP2(obj)				(K_TYPE_CHECK_INSTANCE_CAST((obj), FHdmitx2p0Lp2))
#define F_IS_HDMITX2P0_LP2(obj)			(K_TYPE_CHECK_INSTANCE_TYPE((obj), F_TYPE_HDMITX2P0_LP2))


typedef union 				_IoFHdmitxFcAudschnl4 IoFHdmitxFcAudschnl4;
typedef union 				_IoFHdmitxFcAudschnl5 IoFHdmitxFcAudschnl5;
typedef union 				_IoFHdmitxFcAudschnl6 IoFHdmitxFcAudschnl6;
typedef union 				_IoFHdmitxFcAudschnl7 IoFHdmitxFcAudschnl7;
typedef union 				_IoFHdmitxFcAudschnl8 IoFHdmitxFcAudschnl8;
typedef union 				_IoFHdmitxFcCtrlqhigh IoFHdmitxFcCtrlqhigh;
typedef union 				_IoFHdmitxFcCtrlqlow IoFHdmitxFcCtrlqlow;
typedef union 				_IoFHdmitxFcIscr10 IoFHdmitxFcIscr10;
typedef union 				_IoFHdmitxFcDatauto0 IoFHdmitxFcDatauto0;
typedef union 				_IoFHdmitxFcDatauto1 IoFHdmitxFcDatauto1;
typedef union 				_IoFHdmitxFcDatauto2 IoFHdmitxFcDatauto2;
typedef union 				_IoFHdmitxFcDatman IoFHdmitxFcDatman;
typedef union 				_IoFHdmitxFcDatauto3 IoFHdmitxFcDatauto3;
typedef union 				_IoFHdmitxFcRdrb0 IoFHdmitxFcRdrb0;
typedef union 				_IoFHdmitxFcRdrb1 IoFHdmitxFcRdrb1;
typedef union 				_IoFHdmitxFcRdrb2 IoFHdmitxFcRdrb2;
typedef union 				_IoFHdmitxFcRdrb3 IoFHdmitxFcRdrb3;
typedef union 				_IoFHdmitxFcRdrb4 IoFHdmitxFcRdrb4;
typedef union 				_IoFHdmitxFcRdrb5 IoFHdmitxFcRdrb5;
typedef union 				_IoFHdmitxFcRdrb6 IoFHdmitxFcRdrb6;
typedef union 				_IoFHdmitxFcRdrb7 IoFHdmitxFcRdrb7;
typedef union 				_IoFHdmitxFcRdrb8 IoFHdmitxFcRdrb8;
typedef union 				_IoFHdmitxFcRdrb9 IoFHdmitxFcRdrb9;
typedef union 				_IoFHdmitxFcRdrb10 IoFHdmitxFcRdrb10;
typedef union 				_IoFHdmitxFcRdrb11 IoFHdmitxFcRdrb11;
typedef union 				_IoFHdmitxFcPrconf IoFHdmitxFcPrconf;
typedef union 				_IoFHdmitxFcScramblerCtrl IoFHdmitxFcScramblerCtrl;
typedef union 				_IoFHdmitxFcMultistreamCtrl IoFHdmitxFcMultistreamCtrl;
typedef union 				_IoFHdmitxFcPacketTxEn IoFHdmitxFcPacketTxEn;
typedef union 				_IoFHdmitxFcActspcHdlrCfg IoFHdmitxFcActspcHdlrCfg;
typedef union 				_IoFHdmitxFcInvact2d0 IoFHdmitxFcInvact2d0;
typedef union 				_IoFHdmitxFcInvact2d1 IoFHdmitxFcInvact2d1;
typedef union 				_IoFHdmitxFcGmdStat IoFHdmitxFcGmdStat;
typedef union 				_IoFHdmitxFcGmdEn IoFHdmitxFcGmdEn;
typedef union 				_IoFHdmitxFcGmdUp IoFHdmitxFcGmdUp;
typedef union 				_IoFHdmitxFcGmdConf IoFHdmitxFcGmdConf;
typedef union 				_IoFHdmitxFcGmdHb IoFHdmitxFcGmdHb;
typedef union 				_IoFHdmitxFcGmdPb IoFHdmitxFcGmdPb;
typedef union 				_IoFHdmitxFcAmpPb IoFHdmitxFcAmpPb;
typedef union 				_IoFHdmitxFcNvbiPb IoFHdmitxFcNvbiPb;
typedef union 				_IoFHdmitxPhyConf0 IoFHdmitxPhyConf0;
typedef union 				_IoFHdmitxPhyStat0 IoFHdmitxPhyStat0;
typedef union 				_IoFHdmitxPhyI2cmSlave IoFHdmitxPhyI2cmSlave;
typedef union 				_IoFHdmitxPhyI2cmOperation IoFHdmitxPhyI2cmOperation;
typedef union 				_IoFHdmitxPhyI2cmInt IoFHdmitxPhyI2cmInt;
typedef union 				_IoFHdmitxPhyI2cmCtlint IoFHdmitxPhyI2cmCtlint;
typedef union 				_IoFHdmitxPhyI2cmDiv IoFHdmitxPhyI2cmDiv;
typedef union 				_IoFHdmitxPhyI2cmSoftrstz IoFHdmitxPhyI2cmSoftrstz;
typedef union 				_IoFHdmitxAudConf0 IoFHdmitxAudConf0;
typedef union 				_IoFHdmitxAudConf1 IoFHdmitxAudConf1;
typedef union 				_IoFHdmitxAudInt IoFHdmitxAudInt;
typedef union 				_IoFHdmitxAudConf2 IoFHdmitxAudConf2;
typedef union 				_IoFHdmitxAudInt1 IoFHdmitxAudInt1;
typedef union 				_IoFHdmitxAudN3 IoFHdmitxAudN3;
typedef union 				_IoFHdmitxAudCts3 IoFHdmitxAudCts3;
typedef union 				_IoFHdmitxAudInputclkfs IoFHdmitxAudInputclkfs;
typedef union 				_IoFHdmitxAudSpdif0 IoFHdmitxAudSpdif0;
typedef union 				_IoFHdmitxAudSpdif1 IoFHdmitxAudSpdif1;
typedef union 				_IoFHdmitxAudSpdifint IoFHdmitxAudSpdifint;
typedef union 				_IoFHdmitxAudSpdifint1 IoFHdmitxAudSpdifint1;
typedef union 				_IoFHdmitxMcClkdis IoFHdmitxMcClkdis;
typedef union 				_IoFHdmitxMcSwrstzreq IoFHdmitxMcSwrstzreq;
typedef union 				_IoFHdmitxMcFlowctrl IoFHdmitxMcFlowctrl;
typedef union 				_IoFHdmitxMcPhyrstz IoFHdmitxMcPhyrstz;
typedef union 				_IoFHdmitxCscCfg IoFHdmitxCscCfg;
typedef union 				_IoFHdmitxCscScale IoFHdmitxCscScale;
typedef struct 				_FHdmitx2p0Lp2 FHdmitx2p0Lp2;
typedef struct 				_FHdmitx2p0Lp2Private	FHdmitx2p0Lp2Private;

/*  structure of fc_audschnl4 (2892_106Bh)    */
union _IoFHdmitxFcAudschnl4{
	kuchar		byte[4];
	struct {
		kuchar	oiecChannelnumcr2			:4;
		kuchar	oiecChannelnumcr3			:4;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_audschnl5 (2892_106Ch)    */
union _IoFHdmitxFcAudschnl5{
	kuchar		byte[4];
	struct {
		kuchar	oiecChannelnumcl0			:4;
		kuchar	oiecChannelnumcl1			:4;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_audschnl6 (2892_106Dh)    */
union _IoFHdmitxFcAudschnl6{
	kuchar		byte[4];
	struct {
		kuchar	oiecChannelnumcl2			:4;
		kuchar	oiecChannelnumcl3			:4;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_audschnl7 (2892_106Eh)    */
union _IoFHdmitxFcAudschnl7{
	kuchar		byte[4];
	struct {
		kuchar	oiecSampfreq				:4;
		kuchar	oiecClkaccuracy			:2;
		kuchar	oiecSampfreqExt			:2;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_audschnl8 (2892_106Fh)    */
union _IoFHdmitxFcAudschnl8{
	kuchar		byte[4];
	struct {
		kuchar	oiecWordlength				:4;
		kuchar	oiecOrigsampfreq			:4;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_ctrlqhigh (2892_1073h)    */
union _IoFHdmitxFcCtrlqhigh{
	kuchar		byte[4];
	struct {
		kuchar	onhighattended				:5;
		kuchar								:3;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_ctrlqlow (2892_1074h)    */
union _IoFHdmitxFcCtrlqlow{
	kuchar		byte[4];
	struct {
		kuchar	onlowattended				:5;
		kuchar								:3;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_iscr1_0 (2892_1092h)    */
union _IoFHdmitxFcIscr10{
	kuchar		byte[4];
	struct {
		kuchar	isrcCont					:1;
		kuchar	isrcValid					:1;
		kuchar	isrcStatus					:3;
		kuchar								:3;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_datauto0 (2892_10B3h)    */
union _IoFHdmitxFcDatauto0{
	kuchar		byte[4];
	struct {
		kuchar	acpAuto					:1;
		kuchar	iscr1Auto					:1;
		kuchar	iscr2Auto					:1;
		kuchar	vsdAuto					:1;
		kuchar	spdAuto					:1;
		kuchar								:3;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_datauto1 (2892_10B4h)    */
union _IoFHdmitxFcDatauto1{
	kuchar		byte[4];
	struct {
		kuchar	autoFrameInterpolation	:4;
		kuchar								:4;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_datauto2 (2892_10B5h)    */
union _IoFHdmitxFcDatauto2{
	kuchar		byte[4];
	struct {
		kuchar	autoLineSpacing			:4;
		kuchar	autoFramePackets			:4;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_datman (2892_10B6h)    */
union _IoFHdmitxFcDatman{
	kuchar		byte[4];
	struct {
		kuchar	acpTx						:1;
		kuchar	iscr1Tx					:1;
		kuchar	iscr2Tx					:1;
		kuchar	vsdTx						:1;
		kuchar	spdTx						:1;
		kuchar	nullTx						:1;
		kuchar								:2;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_datauto3 (2892_10B7h)    */
union _IoFHdmitxFcDatauto3{
	kuchar		byte[4];
	struct {
		kuchar	acrAuto					:1;
		kuchar	audiAuto					:1;
		kuchar	gcpAuto					:1;
		kuchar	aviAuto					:1;
		kuchar	ampAuto					:1;
		kuchar	nvbiAuto					:1;
		kuchar								:2;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_rdrb0 (2892_10B8h)    */
union _IoFHdmitxFcRdrb0{
	kuchar		byte[4];
	struct {
		kuchar	acrframeinterpolation		:4;
		kuchar								:4;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_rdrb1 (2892_10B9h)    */
union _IoFHdmitxFcRdrb1{
	kuchar		byte[4];
	struct {
		kuchar	acrpacketlinespacing		:4;
		kuchar	acrpacketsinframe			:4;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_rdrb2 (2892_10BAh)    */
union _IoFHdmitxFcRdrb2{
	kuchar		byte[4];
	struct {
		kuchar	audiframeinterpolation		:4;
		kuchar								:4;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_rdrb3 (2892_10BBh)    */
union _IoFHdmitxFcRdrb3{
	kuchar		byte[4];
	struct {
		kuchar	audipacketlinespacing		:4;
		kuchar	audipacketsinframe			:4;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_rdrb4 (2892_10BCh)    */
union _IoFHdmitxFcRdrb4{
	kuchar		byte[4];
	struct {
		kuchar	gcpframeinterpolation		:4;
		kuchar								:4;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_rdrb5 (2892_10BDh)    */
union _IoFHdmitxFcRdrb5{
	kuchar		byte[4];
	struct {
		kuchar	gcppacketlinespacing		:4;
		kuchar	gcppacketsinframe			:4;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_rdrb6 (2892_10BEh)    */
union _IoFHdmitxFcRdrb6{
	kuchar		byte[4];
	struct {
		kuchar	aviframeinterpolation		:4;
		kuchar								:4;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_rdrb7 (2892_10BFh)    */
union _IoFHdmitxFcRdrb7{
	kuchar		byte[4];
	struct {
		kuchar	avipacketlinespacing		:4;
		kuchar	avipacketsinframe			:4;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_rdrb8 (2892_10C0h)    */
union _IoFHdmitxFcRdrb8{
	kuchar		byte[4];
	struct {
		kuchar	ampframeinterpolation		:4;
		kuchar								:4;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_rdrb9 (2892_10C1h)    */
union _IoFHdmitxFcRdrb9{
	kuchar		byte[4];
	struct {
		kuchar	amppacketlinespacing		:4;
		kuchar	amppacketsinframe			:4;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_rdrb10 (2892_10C2h)    */
union _IoFHdmitxFcRdrb10{
	kuchar		byte[4];
	struct {
		kuchar	nvbiframeinterpolation		:4;
		kuchar								:4;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_rdrb11 (2892_10C3h)    */
union _IoFHdmitxFcRdrb11{
	kuchar		byte[4];
	struct {
		kuchar	nvbipacketlinespacing		:4;
		kuchar	nvbipacketsinframe			:4;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_prconf (2892_10E0h)    */
union _IoFHdmitxFcPrconf{
	kuchar		byte[4];
	struct {
		kuchar	outputPrFactor			:4;
		kuchar	incomingPrFactor			:4;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_scrambler_ctrl (2892_10E1h)    */
union _IoFHdmitxFcScramblerCtrl{
	kuchar		byte[4];
	struct {
		kuchar	scramblerOn				:1;
		kuchar								:3;
		kuchar	scramblerUcpLine			:1;
		kuchar								:3;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_multistream_ctrl (2892_10E2h)    */
union _IoFHdmitxFcMultistreamCtrl{
	kuchar		byte[4];
	struct {
		kuchar	fcMasPacketEn			:1;
		kuchar								:7;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_packet_tx_en (2892_10E3h)    */
union _IoFHdmitxFcPacketTxEn{
	kuchar		byte[4];
	struct {
		kuchar	acrTxEn					:1;
		kuchar	gcpTxEn					:1;
		kuchar	aviTxEn					:1;
		kuchar	audiTxEn					:1;
		kuchar	autTxEn					:1;
		kuchar	ampTxEn					:1;
		kuchar	nvbiTxEn					:1;
		kuchar								:1;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_actspc_hdlr_cfg (2892_10E8h)    */
union _IoFHdmitxFcActspcHdlrCfg{
	kuchar		byte[4];
	struct {
		kuchar	actspcHdlrEn				:1;
		kuchar	actspcHdlrTgl				:1;
		kuchar								:6;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_invact_2d_0 (2892_10E9h)    */
union _IoFHdmitxFcInvact2d0{
	kuchar		byte[4];
	struct {
		kuchar	fcInvact2d0				:8;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_invact_2d_1 (2892_10EAh)    */
union _IoFHdmitxFcInvact2d1{
	kuchar		byte[4];
	struct {
		kuchar	fcInvact2d1				:4;
		kuchar								:4;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_gmd_stat (2892_1100h)    */
union _IoFHdmitxFcGmdStat{
	kuchar		byte[4];
	struct {
		kuchar	igmdcurrentGamutSeqNum	:4;
		kuchar	igmdpacketSeq				:2;
		kuchar	igmddnextField				:1;
		kuchar	igmdnoCrntGbd				:1;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_gmd_en (2892_1101h)    */
union _IoFHdmitxFcGmdEn{
	kuchar		byte[4];
	struct {
		kuchar	gmdenabletx					:1;
		kuchar								:7;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_gmd_up (2892_1102h)    */
union _IoFHdmitxFcGmdUp{
	kuchar		byte[4];
	struct {
		kuchar	gmdupdatepacket				:1;
		kuchar								:7;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_gmd_conf (2892_1103h)    */
union _IoFHdmitxFcGmdConf{
	kuchar		byte[4];
	struct {
		kuchar	gmdpacketlinespacing		:4;
		kuchar	gmdpacketsinframe			:4;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_gmd_hb (2892_1104h)    */
union _IoFHdmitxFcGmdHb{
	kuchar		byte[4];
	struct {
		kuchar	gmdaffectedGamutSeqNum	:4;
		kuchar	gmdgbdProfile				:3;
		kuchar								:1;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_gmd_pb (2892_1105 - 2892_1120h)    */
union _IoFHdmitxFcGmdPb{
	kuchar		byte[4];
	struct {
		kuchar	fcGmdPb					:8;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_amp_pb (2892_112A - 2892_1145h)    */
union _IoFHdmitxFcAmpPb{
	kuchar		byte[4];
	struct {
		kuchar	fcAmpPb					:8;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_nvbi_pb (2892_114A - 2892_1164h)    */
union _IoFHdmitxFcNvbiPb{
	kuchar		byte[4];
	struct {
		kuchar	fcNvbiPb					:8;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/* PHYConfiguration Registers */

/*  structure of phy_conf0 (2892_3000h)    */
union _IoFHdmitxPhyConf0{
	kuchar		byte[4];
	struct {
		kuchar								:2;
		kuchar	enhpdrxsense				:1;
		kuchar	txpwron						:1;
		kuchar	pddq						:1;
		kuchar	svsret						:1;
		kuchar								:2;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of phy_stat0 (2892_3004h) / phy_int0 (2892_3005h) / phy_mask0 (2892_3006h) / phy_pol0 (2892_3007h) */
union _IoFHdmitxPhyStat0{
	kuchar		byte[4];
	struct {
		kuchar	txPhyLock					:1;
		kuchar	hpd							:1;
		kuchar								:2;
		kuchar	rxSense0					:1;
		kuchar	rxSense1					:1;
		kuchar	rxSense2					:1;
		kuchar	rxSense3					:1;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of phy_i2cm_slave (2892_3020h)    */
union _IoFHdmitxPhyI2cmSlave{
	kuchar		byte[4];
	struct {
		kuchar	slaveaddr					:7;
		kuchar								:1;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of phy_i2cm_operation (2892_3026h)    */
union _IoFHdmitxPhyI2cmOperation{
	kuchar		byte[4];
	struct {
		kuchar	rd							:1;
		kuchar								:3;
		kuchar	wr							:1;
		kuchar								:3;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of phy_i2cm_int (2892_3027h)    */
union _IoFHdmitxPhyI2cmInt{
	kuchar		byte[4];
	struct {
		kuchar	doneStatus					:1;
		kuchar	doneInterrupt				:1;
		kuchar	doneMask					:1;
		kuchar	donePol					:1;
		kuchar								:4;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of phy_i2cm_ctlint (2892_3028h)    */
union _IoFHdmitxPhyI2cmCtlint{
	kuchar		byte[4];
	struct {
		kuchar	arbitrationStatus			:1;
		kuchar	arbitrationInterrupt		:1;
		kuchar	arbitrationMask			:1;
		kuchar	arbitrationPol				:1;
		kuchar	nackStatus					:1;
		kuchar	nackInterrupt				:1;
		kuchar	nackMask					:1;
		kuchar	nackPol					:1;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of phy_i2cm_div (2892_3029h)    */
union _IoFHdmitxPhyI2cmDiv{
	kuchar		byte[4];
	struct {
		kuchar								:3;
		kuchar	fastStdMode				:1;
		kuchar								:4;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of phy_i2cm_softrstz (2892_302Ah)    */
union _IoFHdmitxPhyI2cmSoftrstz{
	kuchar		byte[4];
	struct {
		kuchar	i2cSoftrstz				:1;
		kuchar								:7;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/* AudioSample Registers */

/*  structure of aud_conf0 (2892_3100h)    */
union _IoFHdmitxAudConf0{
	kuchar		byte[4];
	struct {
		kuchar	i2sInEn					:4;
		kuchar								:1;
		kuchar	i2sSelect					:1;
		kuchar								:1;
		kuchar	swAudioFifoRst			:1;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of aud_conf1 (2892_3101h)    */
union _IoFHdmitxAudConf1{
	kuchar		byte[4];
	struct {
		kuchar	i2sWidth					:5;
		kuchar	i2sMode					:3;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of aud_int (2892_3102h)    */
union _IoFHdmitxAudInt{
	kuchar		byte[4];
	struct {
		kuchar								:2;
		kuchar	fifoFullMask				:1;
		kuchar	fifoEmptyMask				:1;
		kuchar								:4;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of aud_conf2 (2892_3103h)    */
union _IoFHdmitxAudConf2{
	kuchar		byte[4];
	struct {
		kuchar	hbr							:1;
		kuchar	nlpcm						:1;
		kuchar								:6;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of aud_int1 (2892_3104h)    */
union _IoFHdmitxAudInt1{
	kuchar		byte[4];
	struct {
		kuchar								:4;
		kuchar	fifoOverrunMask			:1;
		kuchar								:3;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/* AudioPacketizer Registers */

/*  structure of aud_n3 (2892_3202h)    */
union _IoFHdmitxAudN3{
	kuchar		byte[4];
	struct {
		kuchar	audn						:4;
		kuchar								:3;
		kuchar	nctsAtomicWrite			:1;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of aud_cts3 (2892_3205h)    */
union _IoFHdmitxAudCts3{
	kuchar		byte[4];
	struct {
		kuchar	audcts						:4;
		kuchar	ctsManual					:1;
		kuchar	nShift						:3;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of aud_inputclkfs (2892_3206h)    */
union _IoFHdmitxAudInputclkfs{
	kuchar		byte[4];
	struct {
		kuchar	ifsfactor					:3;
		kuchar								:5;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/* AudioSampleSPDIF Registers */

/*  structure of aud_spdif0 (2892_3300h)    */
union _IoFHdmitxAudSpdif0{
	kuchar		byte[4];
	struct {
		kuchar								:7;
		kuchar	swAudioFifoRst			:1;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of aud_spdif1 (2892_3301h)    */
union _IoFHdmitxAudSpdif1{
	kuchar		byte[4];
	struct {
		kuchar	spdifWidth					:5;
		kuchar								:1;
		kuchar	spdifHbrMode				:1;
		kuchar	setnlpcm					:1;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of aud_spdifint (2892_3302h)    */
union _IoFHdmitxAudSpdifint{
	kuchar		byte[4];
	struct {
		kuchar								:2;
		kuchar	spdifFifoFullMask		:1;
		kuchar	spdifFifoEmptyMask		:1;
		kuchar								:4;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of aud_spdifint1 (2892_3303h)    */
union _IoFHdmitxAudSpdifint1{
	kuchar		byte[4];
	struct {
		kuchar								:4;
		kuchar	fifoOverrunMask			:1;
		kuchar								:3;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/* MainController Registers */

/*  structure of mc_clkdis (2892_4001h)    */
union _IoFHdmitxMcClkdis{
	kuchar		byte[4];
	struct {
		kuchar	pixelclkDisable			:1;
		kuchar	tmdsclkDisable				:1;
		kuchar	prepclkDisable				:1;
		kuchar	audclkDisable				:1;
		kuchar	cscclkDisable				:1;
		kuchar	cecclkDisable				:1;
		kuchar								:2;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of mc_swrstzreq (2892_4002h)    */
union _IoFHdmitxMcSwrstzreq{
	kuchar		byte[4];
	struct {
		kuchar	pixelswrstReq				:1;
		kuchar	tmdsswrstReq				:1;
		kuchar	prepswrstReq				:1;
		kuchar	ii2sswrstReq				:1;
		kuchar	ispdifswrstReq				:1;
		kuchar								:1;
		kuchar	cecswrstReq				:1;
		kuchar								:1;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of mc_flowctrl (2892_4004h)    */
union _IoFHdmitxMcFlowctrl{
	kuchar		byte[4];
	struct {
		kuchar	feedThroughOff			:1;
		kuchar								:7;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of mc_phyrstz (2892_4005h)    */
union _IoFHdmitxMcPhyrstz{
	kuchar		byte[4];
	struct {
		kuchar	phyrstz						:1;
		kuchar								:7;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/* ColorSpaceConverter Registers */

/*  structure of csc_cfg (2892_4100h)    */
union _IoFHdmitxCscCfg{
	kuchar		byte[4];
	struct {
		kuchar	decmode						:2;
		kuchar								:2;
		kuchar	intmode						:2;
		kuchar								:1;
		kuchar	cscLimit					:1;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of csc_scale (2892_4101h)    */
union _IoFHdmitxCscScale{
	kuchar		byte[4];
	struct {
		kuchar	cscscale					:2;
		kuchar								:2;
		kuchar	cscColorDepth				:4;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

struct  _FHdmitx2p0Lp2
{
	KObject parent;
};


KConstType					f_hdmitx2p0_lp2_get_type(void);
FHdmitx2p0Lp2*		f_hdmitx2p0_lp2_new(void);


#endif/*__F_HDMITX2P0_LP2_H__*/