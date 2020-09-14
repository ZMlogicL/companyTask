/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-10
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


#ifndef __F_HDMITX2P0_LP2_H__
#define __F_HDMITX2P0_LP2_H__


#include <stdio.h>
#include <glib-object.h>


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

/*  structure of fc_audschnl4 (2892_106Bh)    */
union _IoFHdmitxFcAudschnl4{
	guchar		byte[4];
	struct {
		guchar	oiecChannelnumcr2			:4;
		guchar	oiecChannelnumcr3			:4;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_audschnl5 (2892_106Ch)    */
union _IoFHdmitxFcAudschnl5{
	guchar		byte[4];
	struct {
		guchar	oiecChannelnumcl0			:4;
		guchar	oiecChannelnumcl1			:4;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_audschnl6 (2892_106Dh)    */
union _IoFHdmitxFcAudschnl6{
	guchar		byte[4];
	struct {
		guchar	oiecChannelnumcl2			:4;
		guchar	oiecChannelnumcl3			:4;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_audschnl7 (2892_106Eh)    */
union _IoFHdmitxFcAudschnl7{
	guchar		byte[4];
	struct {
		guchar	oiecSampfreq				:4;
		guchar	oiecClkaccuracy			:2;
		guchar	oiecSampfreqExt			:2;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_audschnl8 (2892_106Fh)    */
union _IoFHdmitxFcAudschnl8{
	guchar		byte[4];
	struct {
		guchar	oiecWordlength				:4;
		guchar	oiecOrigsampfreq			:4;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_ctrlqhigh (2892_1073h)    */
union _IoFHdmitxFcCtrlqhigh{
	guchar		byte[4];
	struct {
		guchar	onhighattended				:5;
		guchar								:3;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_ctrlqlow (2892_1074h)    */
union _IoFHdmitxFcCtrlqlow{
	guchar		byte[4];
	struct {
		guchar	onlowattended				:5;
		guchar								:3;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_iscr1_0 (2892_1092h)    */
union _IoFHdmitxFcIscr10{
	guchar		byte[4];
	struct {
		guchar	isrcCont					:1;
		guchar	isrcValid					:1;
		guchar	isrcStatus					:3;
		guchar								:3;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_datauto0 (2892_10B3h)    */
union _IoFHdmitxFcDatauto0{
	guchar		byte[4];
	struct {
		guchar	acpAuto					:1;
		guchar	iscr1Auto					:1;
		guchar	iscr2Auto					:1;
		guchar	vsdAuto					:1;
		guchar	spdAuto					:1;
		guchar								:3;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_datauto1 (2892_10B4h)    */
union _IoFHdmitxFcDatauto1{
	guchar		byte[4];
	struct {
		guchar	autoFrameInterpolation	:4;
		guchar								:4;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_datauto2 (2892_10B5h)    */
union _IoFHdmitxFcDatauto2{
	guchar		byte[4];
	struct {
		guchar	autoLineSpacing			:4;
		guchar	autoFramePackets			:4;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_datman (2892_10B6h)    */
union _IoFHdmitxFcDatman{
	guchar		byte[4];
	struct {
		guchar	acpTx						:1;
		guchar	iscr1Tx					:1;
		guchar	iscr2Tx					:1;
		guchar	vsdTx						:1;
		guchar	spdTx						:1;
		guchar	nullTx						:1;
		guchar								:2;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_datauto3 (2892_10B7h)    */
union _IoFHdmitxFcDatauto3{
	guchar		byte[4];
	struct {
		guchar	acrAuto					:1;
		guchar	audiAuto					:1;
		guchar	gcpAuto					:1;
		guchar	aviAuto					:1;
		guchar	ampAuto					:1;
		guchar	nvbiAuto					:1;
		guchar								:2;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_rdrb0 (2892_10B8h)    */
union _IoFHdmitxFcRdrb0{
	guchar		byte[4];
	struct {
		guchar	acrframeinterpolation		:4;
		guchar								:4;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_rdrb1 (2892_10B9h)    */
union _IoFHdmitxFcRdrb1{
	guchar		byte[4];
	struct {
		guchar	acrpacketlinespacing		:4;
		guchar	acrpacketsinframe			:4;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_rdrb2 (2892_10BAh)    */
union _IoFHdmitxFcRdrb2{
	guchar		byte[4];
	struct {
		guchar	audiframeinterpolation		:4;
		guchar								:4;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_rdrb3 (2892_10BBh)    */
union _IoFHdmitxFcRdrb3{
	guchar		byte[4];
	struct {
		guchar	audipacketlinespacing		:4;
		guchar	audipacketsinframe			:4;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_rdrb4 (2892_10BCh)    */
union _IoFHdmitxFcRdrb4{
	guchar		byte[4];
	struct {
		guchar	gcpframeinterpolation		:4;
		guchar								:4;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_rdrb5 (2892_10BDh)    */
union _IoFHdmitxFcRdrb5{
	guchar		byte[4];
	struct {
		guchar	gcppacketlinespacing		:4;
		guchar	gcppacketsinframe			:4;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_rdrb6 (2892_10BEh)    */
union _IoFHdmitxFcRdrb6{
	guchar		byte[4];
	struct {
		guchar	aviframeinterpolation		:4;
		guchar								:4;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_rdrb7 (2892_10BFh)    */
union _IoFHdmitxFcRdrb7{
	guchar		byte[4];
	struct {
		guchar	avipacketlinespacing		:4;
		guchar	avipacketsinframe			:4;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_rdrb8 (2892_10C0h)    */
union _IoFHdmitxFcRdrb8{
	guchar		byte[4];
	struct {
		guchar	ampframeinterpolation		:4;
		guchar								:4;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_rdrb9 (2892_10C1h)    */
union _IoFHdmitxFcRdrb9{
	guchar		byte[4];
	struct {
		guchar	amppacketlinespacing		:4;
		guchar	amppacketsinframe			:4;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_rdrb10 (2892_10C2h)    */
union _IoFHdmitxFcRdrb10{
	guchar		byte[4];
	struct {
		guchar	nvbiframeinterpolation		:4;
		guchar								:4;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_rdrb11 (2892_10C3h)    */
union _IoFHdmitxFcRdrb11{
	guchar		byte[4];
	struct {
		guchar	nvbipacketlinespacing		:4;
		guchar	nvbipacketsinframe			:4;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_prconf (2892_10E0h)    */
union _IoFHdmitxFcPrconf{
	guchar		byte[4];
	struct {
		guchar	outputPrFactor			:4;
		guchar	incomingPrFactor			:4;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_scrambler_ctrl (2892_10E1h)    */
union _IoFHdmitxFcScramblerCtrl{
	guchar		byte[4];
	struct {
		guchar	scramblerOn				:1;
		guchar								:3;
		guchar	scramblerUcpLine			:1;
		guchar								:3;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_multistream_ctrl (2892_10E2h)    */
union _IoFHdmitxFcMultistreamCtrl{
	guchar		byte[4];
	struct {
		guchar	fcMasPacketEn			:1;
		guchar								:7;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_packet_tx_en (2892_10E3h)    */
union _IoFHdmitxFcPacketTxEn{
	guchar		byte[4];
	struct {
		guchar	acrTxEn					:1;
		guchar	gcpTxEn					:1;
		guchar	aviTxEn					:1;
		guchar	audiTxEn					:1;
		guchar	autTxEn					:1;
		guchar	ampTxEn					:1;
		guchar	nvbiTxEn					:1;
		guchar								:1;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_actspc_hdlr_cfg (2892_10E8h)    */
union _IoFHdmitxFcActspcHdlrCfg{
	guchar		byte[4];
	struct {
		guchar	actspcHdlrEn				:1;
		guchar	actspcHdlrTgl				:1;
		guchar								:6;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_invact_2d_0 (2892_10E9h)    */
union _IoFHdmitxFcInvact2d0{
	guchar		byte[4];
	struct {
		guchar	fcInvact2d0				:8;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_invact_2d_1 (2892_10EAh)    */
union _IoFHdmitxFcInvact2d1{
	guchar		byte[4];
	struct {
		guchar	fcInvact2d1				:4;
		guchar								:4;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_gmd_stat (2892_1100h)    */
union _IoFHdmitxFcGmdStat{
	guchar		byte[4];
	struct {
		guchar	igmdcurrentGamutSeqNum	:4;
		guchar	igmdpacketSeq				:2;
		guchar	igmddnextField				:1;
		guchar	igmdnoCrntGbd				:1;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_gmd_en (2892_1101h)    */
union _IoFHdmitxFcGmdEn{
	guchar		byte[4];
	struct {
		guchar	gmdenabletx					:1;
		guchar								:7;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_gmd_up (2892_1102h)    */
union _IoFHdmitxFcGmdUp{
	guchar		byte[4];
	struct {
		guchar	gmdupdatepacket				:1;
		guchar								:7;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_gmd_conf (2892_1103h)    */
union _IoFHdmitxFcGmdConf{
	guchar		byte[4];
	struct {
		guchar	gmdpacketlinespacing		:4;
		guchar	gmdpacketsinframe			:4;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_gmd_hb (2892_1104h)    */
union _IoFHdmitxFcGmdHb{
	guchar		byte[4];
	struct {
		guchar	gmdaffectedGamutSeqNum	:4;
		guchar	gmdgbdProfile				:3;
		guchar								:1;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_gmd_pb (2892_1105 - 2892_1120h)    */
union _IoFHdmitxFcGmdPb{
	guchar		byte[4];
	struct {
		guchar	fcGmdPb					:8;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_amp_pb (2892_112A - 2892_1145h)    */
union _IoFHdmitxFcAmpPb{
	guchar		byte[4];
	struct {
		guchar	fcAmpPb					:8;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_nvbi_pb (2892_114A - 2892_1164h)    */
union _IoFHdmitxFcNvbiPb{
	guchar		byte[4];
	struct {
		guchar	fcNvbiPb					:8;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/* PHYConfiguration Registers */

/*  structure of phy_conf0 (2892_3000h)    */
union _IoFHdmitxPhyConf0{
	guchar		byte[4];
	struct {
		guchar								:2;
		guchar	enhpdrxsense				:1;
		guchar	txpwron						:1;
		guchar	pddq						:1;
		guchar	svsret						:1;
		guchar								:2;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of phy_stat0 (2892_3004h) / phy_int0 (2892_3005h) / phy_mask0 (2892_3006h) / phy_pol0 (2892_3007h) */
union _IoFHdmitxPhyStat0{
	guchar		byte[4];
	struct {
		guchar	txPhyLock					:1;
		guchar	hpd							:1;
		guchar								:2;
		guchar	rxSense0					:1;
		guchar	rxSense1					:1;
		guchar	rxSense2					:1;
		guchar	rxSense3					:1;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of phy_i2cm_slave (2892_3020h)    */
union _IoFHdmitxPhyI2cmSlave{
	guchar		byte[4];
	struct {
		guchar	slaveaddr					:7;
		guchar								:1;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of phy_i2cm_operation (2892_3026h)    */
union _IoFHdmitxPhyI2cmOperation{
	guchar		byte[4];
	struct {
		guchar	rd							:1;
		guchar								:3;
		guchar	wr							:1;
		guchar								:3;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of phy_i2cm_int (2892_3027h)    */
union _IoFHdmitxPhyI2cmInt{
	guchar		byte[4];
	struct {
		guchar	doneStatus					:1;
		guchar	doneInterrupt				:1;
		guchar	doneMask					:1;
		guchar	donePol					:1;
		guchar								:4;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of phy_i2cm_ctlint (2892_3028h)    */
union _IoFHdmitxPhyI2cmCtlint{
	guchar		byte[4];
	struct {
		guchar	arbitrationStatus			:1;
		guchar	arbitrationInterrupt		:1;
		guchar	arbitrationMask			:1;
		guchar	arbitrationPol				:1;
		guchar	nackStatus					:1;
		guchar	nackInterrupt				:1;
		guchar	nackMask					:1;
		guchar	nackPol					:1;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of phy_i2cm_div (2892_3029h)    */
union _IoFHdmitxPhyI2cmDiv{
	guchar		byte[4];
	struct {
		guchar								:3;
		guchar	fastStdMode				:1;
		guchar								:4;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of phy_i2cm_softrstz (2892_302Ah)    */
union _IoFHdmitxPhyI2cmSoftrstz{
	guchar		byte[4];
	struct {
		guchar	i2cSoftrstz				:1;
		guchar								:7;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/* AudioSample Registers */

/*  structure of aud_conf0 (2892_3100h)    */
union _IoFHdmitxAudConf0{
	guchar		byte[4];
	struct {
		guchar	i2sInEn					:4;
		guchar								:1;
		guchar	i2sSelect					:1;
		guchar								:1;
		guchar	swAudioFifoRst			:1;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of aud_conf1 (2892_3101h)    */
union _IoFHdmitxAudConf1{
	guchar		byte[4];
	struct {
		guchar	i2sWidth					:5;
		guchar	i2sMode					:3;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of aud_int (2892_3102h)    */
union _IoFHdmitxAudInt{
	guchar		byte[4];
	struct {
		guchar								:2;
		guchar	fifoFullMask				:1;
		guchar	fifoEmptyMask				:1;
		guchar								:4;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of aud_conf2 (2892_3103h)    */
union _IoFHdmitxAudConf2{
	guchar		byte[4];
	struct {
		guchar	hbr							:1;
		guchar	nlpcm						:1;
		guchar								:6;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of aud_int1 (2892_3104h)    */
union _IoFHdmitxAudInt1{
	guchar		byte[4];
	struct {
		guchar								:4;
		guchar	fifoOverrunMask			:1;
		guchar								:3;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/* AudioPacketizer Registers */

/*  structure of aud_n3 (2892_3202h)    */
union _IoFHdmitxAudN3{
	guchar		byte[4];
	struct {
		guchar	audn						:4;
		guchar								:3;
		guchar	nctsAtomicWrite			:1;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of aud_cts3 (2892_3205h)    */
union _IoFHdmitxAudCts3{
	guchar		byte[4];
	struct {
		guchar	audcts						:4;
		guchar	ctsManual					:1;
		guchar	nShift						:3;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of aud_inputclkfs (2892_3206h)    */
union _IoFHdmitxAudInputclkfs{
	guchar		byte[4];
	struct {
		guchar	ifsfactor					:3;
		guchar								:5;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/* AudioSampleSPDIF Registers */

/*  structure of aud_spdif0 (2892_3300h)    */
union _IoFHdmitxAudSpdif0{
	guchar		byte[4];
	struct {
		guchar								:7;
		guchar	swAudioFifoRst			:1;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of aud_spdif1 (2892_3301h)    */
union _IoFHdmitxAudSpdif1{
	guchar		byte[4];
	struct {
		guchar	spdifWidth					:5;
		guchar								:1;
		guchar	spdifHbrMode				:1;
		guchar	setnlpcm					:1;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of aud_spdifint (2892_3302h)    */
union _IoFHdmitxAudSpdifint{
	guchar		byte[4];
	struct {
		guchar								:2;
		guchar	spdifFifoFullMask		:1;
		guchar	spdifFifoEmptyMask		:1;
		guchar								:4;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of aud_spdifint1 (2892_3303h)    */
union _IoFHdmitxAudSpdifint1{
	guchar		byte[4];
	struct {
		guchar								:4;
		guchar	fifoOverrunMask			:1;
		guchar								:3;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/* MainController Registers */

/*  structure of mc_clkdis (2892_4001h)    */
union _IoFHdmitxMcClkdis{
	guchar		byte[4];
	struct {
		guchar	pixelclkDisable			:1;
		guchar	tmdsclkDisable				:1;
		guchar	prepclkDisable				:1;
		guchar	audclkDisable				:1;
		guchar	cscclkDisable				:1;
		guchar	cecclkDisable				:1;
		guchar								:2;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of mc_swrstzreq (2892_4002h)    */
union _IoFHdmitxMcSwrstzreq{
	guchar		byte[4];
	struct {
		guchar	pixelswrstReq				:1;
		guchar	tmdsswrstReq				:1;
		guchar	prepswrstReq				:1;
		guchar	ii2sswrstReq				:1;
		guchar	ispdifswrstReq				:1;
		guchar								:1;
		guchar	cecswrstReq				:1;
		guchar								:1;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of mc_flowctrl (2892_4004h)    */
union _IoFHdmitxMcFlowctrl{
	guchar		byte[4];
	struct {
		guchar	feedThroughOff			:1;
		guchar								:7;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of mc_phyrstz (2892_4005h)    */
union _IoFHdmitxMcPhyrstz{
	guchar		byte[4];
	struct {
		guchar	phyrstz						:1;
		guchar								:7;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/* ColorSpaceConverter Registers */

/*  structure of csc_cfg (2892_4100h)    */
union _IoFHdmitxCscCfg{
	guchar		byte[4];
	struct {
		guchar	decmode						:2;
		guchar								:2;
		guchar	intmode						:2;
		guchar								:1;
		guchar	cscLimit					:1;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of csc_scale (2892_4101h)    */
union _IoFHdmitxCscScale{
	guchar		byte[4];
	struct {
		guchar	cscscale					:2;
		guchar								:2;
		guchar	cscColorDepth				:4;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};


#endif/*__F_HDMITX2P0_LP2_H__*/
