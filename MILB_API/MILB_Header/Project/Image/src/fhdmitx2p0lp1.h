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


#ifndef __F_HDMITX2P0_LP1_H__
#define __F_HDMITX2P0_LP1_H__


#include <stdio.h>
#include <glib-object.h>


typedef union 				_IoFHdmitxPwrctrl IoFHdmitxPwrctrl;
typedef union 				_IoFHdmitxCpmodePllcfg IoFHdmitxCpmodePllcfg;
typedef union 				_IoFHdmitxCksymtxctrl IoFHdmitxCksymtxctrl;
typedef union 				_IoFHdmitxVlevctrl IoFHdmitxVlevctrl;
typedef union 				_IoFHdmitxPllcurrctrl IoFHdmitxPllcurrctrl;
typedef union 				_IoFHdmitxPllctrl IoFHdmitxPllctrl;
typedef union 				_IoFHdmitxPllgmpctrl IoFHdmitxPllgmpctrl;
typedef union 				_IoFHdmitxTxterm IoFHdmitxTxterm;
typedef union 				_IoFHdmitxIhFcStat0 IoFHdmitxIhFcStat0;
typedef union 				_IoFHdmitxIhFcStat1 IoFHdmitxIhFcStat1;
typedef union 				_IoFHdmitxIhFcStat2 IoFHdmitxIhFcStat2;
typedef union 				_IoFHdmitxIhAsStat0 IoFHdmitxIhAsStat0;
typedef union 				_IoFHdmitxIhPhyStat0 IoFHdmitxIhPhyStat0;
typedef union 				_IoFHdmitxIhI2cmStat0 IoFHdmitxIhI2cmStat0;
typedef union 				_IoFHdmitxIhCecStat0 IoFHdmitxIhCecStat0;
typedef union 				_IoFHdmitxIhVpStat0 IoFHdmitxIhVpStat0;
typedef union 				_IoFHdmitxIhI2cmphyStat0 IoFHdmitxIhI2cmphyStat0;
typedef union 				_IoFHdmitxIhDecode IoFHdmitxIhDecode;
typedef union 				_IoFHdmitxIhMute IoFHdmitxIhMute;
typedef union 				_IoFHdmitxTxInvid0 IoFHdmitxTxInvid0;
typedef union 				_IoFHdmitxTxInstuffing IoFHdmitxTxInstuffing;
typedef union 				_IoFHdmitxVpStatus IoFHdmitxVpStatus;
typedef union 				_IoFHdmitxVpPrCd IoFHdmitxVpPrCd;
typedef union 				_IoFHdmitxVpStuff IoFHdmitxVpStuff;
typedef union 				_IoFHdmitxVpRemap IoFHdmitxVpRemap;
typedef union 				_IoFHdmitxVpConf IoFHdmitxVpConf;
typedef union 				_IoFHdmitxVpMask IoFHdmitxVpMask;
typedef union 				_IoFHdmitxFcInvidconf IoFHdmitxFcInvidconf;
typedef union 				_IoFHdmitxFcInhactiv0 IoFHdmitxFcInhactiv0;
typedef union 				_IoFHdmitxFcInhactiv1 IoFHdmitxFcInhactiv1;
typedef union 				_IoFHdmitxFcInhblank0 IoFHdmitxFcInhblank0;
typedef union 				_IoFHdmitxFcInhblank1 IoFHdmitxFcInhblank1;
typedef union 				_IoFHdmitxFcInvactiv0 IoFHdmitxFcInvactiv0;
typedef union 				_IoFHdmitxFcInvactiv1 IoFHdmitxFcInvactiv1;
typedef union 				_IoFHdmitxFcHsyncindelay0 IoFHdmitxFcHsyncindelay0;
typedef union 				_IoFHdmitxFcHsyncindelay1 IoFHdmitxFcHsyncindelay1;
typedef union 				_IoFHdmitxFcHsyncinwidth0 IoFHdmitxFcHsyncinwidth0;
typedef union 				_IoFHdmitxFcHsyncinwidth1 IoFHdmitxFcHsyncinwidth1;
typedef union 				_IoFHdmitxFcVsyncinwidth IoFHdmitxFcVsyncinwidth;
typedef union 				_IoFHdmitxFcInfreq2 IoFHdmitxFcInfreq2;
typedef union 				_IoFHdmitxFcCh1pream IoFHdmitxFcCh1pream;
typedef union 				_IoFHdmitxFcCh2pream IoFHdmitxFcCh2pream;
typedef union 				_IoFHdmitxFcAviconf3 IoFHdmitxFcAviconf3;
typedef union 				_IoFHdmitxFcGcp IoFHdmitxFcGcp;
typedef union 				_IoFHdmitxFcAviconf0 IoFHdmitxFcAviconf0;
typedef union 				_IoFHdmitxFcAviconf1 IoFHdmitxFcAviconf1;
typedef union 				_IoFHdmitxFcAviconf2 IoFHdmitxFcAviconf2;
typedef union 				_IoFHdmitxFcAvivid IoFHdmitxFcAvivid;
typedef union 				_IoFHdmitxFcAudiconf0 IoFHdmitxFcAudiconf0;
typedef union 				_IoFHdmitxFcAudiconf1 IoFHdmitxFcAudiconf1;
typedef union 				_IoFHdmitxFcAudiconf3 IoFHdmitxFcAudiconf3;
typedef union 				_IoFHdmitxFcVsdsize IoFHdmitxFcVsdsize;
typedef union 				_IoFHdmitxFcVsdpayload IoFHdmitxFcVsdpayload;
typedef union 				_IoFHdmitxFcSpdvendorname IoFHdmitxFcSpdvendorname;
typedef union 				_IoFHdmitxFcSpdproductname IoFHdmitxFcSpdproductname;
typedef union 				_IoFHdmitxFcAcp IoFHdmitxFcAcp;
typedef union 				_IoFHdmitxFcIscr1 IoFHdmitxFcIscr1;
typedef union 				_IoFHdmitxFcIscr2 IoFHdmitxFcIscr2;
typedef union 				_IoFHdmitxFcAudsconf IoFHdmitxFcAudsconf;
typedef union 				_IoFHdmitxFcAudsstat IoFHdmitxFcAudsstat;
typedef union 				_IoFHdmitxFcAudsv IoFHdmitxFcAudsv;
typedef union 				_IoFHdmitxFcAudsu IoFHdmitxFcAudsu;
typedef union 				_IoFHdmitxFcAudschnl0 IoFHdmitxFcAudschnl0;
typedef union 				_IoFHdmitxFcAudschnl2 IoFHdmitxFcAudschnl2;
typedef union 				_IoFHdmitxFcAudschnl3 IoFHdmitxFcAudschnl3;

/* Interrupt Registers */

/* structure of PWRCTRL (2892_0000h) */
union  _IoFHdmitxPwrctrl{
	gushort		hword;
	struct {
		gushort	ckPoweron					:1;
		gushort	txPoweron2					:1;
		gushort	txPoweron1					:1;
		gushort	txPoweron0					:1;
		gushort	txPwron					:1;
		gushort	biasDataOn				:1;
		gushort	biasClkOn					:1;
		gushort								:8;
		gushort	override					:1;
	}bit;
};

/* structure of OPMODE_PLLCFG (2892_0006h) */
union  _IoFHdmitxCpmodePllcfg{
	gushort		hword;
	struct {
		gushort	nCntrl						:2;
		gushort	refCntrl					:2;
		gushort	fbdiv1Cntrl				:2;
		gushort	fbdiv2Cntrl				:3;
		gushort	opmode						:2;
		gushort	tmdsmhlCntrl				:2;
		gushort	prePdiv					:2;
		gushort								:1;
	}bit;
};

/* structure of CKSYMTXCTRL (2892_0009h) */
union  _IoFHdmitxCksymtxctrl{
	gushort		hword;
	struct {
		gushort	ckSymon					:1;
		gushort	TxTrbon					:1;
		gushort	TxTraon					:1;
		gushort	TxSymon					:1;
		gushort	slopeboost					:2;
		gushort								:9;
		gushort	override					:1;
	}bit;
};

/* structure of VLEVCTRL (2892_000Eh) */
union  _IoFHdmitxVlevctrl{
	gushort		hword;
	struct {
		gushort	supCkLvl					:5;
		gushort	supTxLvl					:5;
		gushort								:5;
		gushort	override					:1;
	}bit;
};

/* structure of PLLCURRCTRL (2892_0010h) */
union  _IoFHdmitxPllcurrctrl{
	gushort		hword;
	struct {
		gushort	mpllIntCntrl				:3;
		gushort	mpllPropCntrl				:3;
		gushort								:10;
	}bit;
};

/* structure of PLLCTRL (2892_0014h) */
union  _IoFHdmitxPllctrl{
	gushort		hword;
	struct {
		gushort								:2;
		gushort	mpllRst					:1;
		gushort	mpllPwrOn					:1;
		gushort								:11;
		gushort	override					:1;
	}bit;
};

/* structure of PLLGMPCTRL (2892_0015h) */
union  _IoFHdmitxPllgmpctrl{
	gushort		hword;
	struct {
		gushort	mpllGmpCntrl				:2;
		gushort								:14;
	}bit;
};

/* structure of TXTERM (2892_0019h) */
union  _IoFHdmitxTxterm{
	gushort		hword;
	struct {
		gushort	dTxTerm					:3;
		gushort								:13;
	}bit;
};

/*  structure of ih_fc_stat0 (2892_0100h)    */
union _IoFHdmitxIhFcStat0{
	guchar		byte[4];
	struct {
		guchar	nullPkt					:1;
		guchar	acr							:1;
		guchar	auds						:1;
		guchar	nvbi						:1;
		guchar	mas							:1;
		guchar	hbr							:1;
		guchar	acp							:1;
		guchar	audi						:1;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of ih_fc_stat1 (2892_0101h)    */
union _IoFHdmitxIhFcStat1{
	guchar		byte[4];
	struct {
		guchar	gcp							:1;
		guchar	avi							:1;
		guchar	amp							:1;
		guchar	spd							:1;
		guchar	vsd							:1;
		guchar	iscr2						:1;
		guchar	iscr1						:1;
		guchar	gmd							:1;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of ih_fc_stat2 (2892_0102h)    */
union _IoFHdmitxIhFcStat2{
	guchar		byte[4];
	struct {
		guchar	highpriorityOverflow		:1;
		guchar	lowpriorityOverflow		:1;
		guchar								:6;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of ih_as_stat0 (2892_0103h)    */
union _IoFHdmitxIhAsStat0{
	guchar		byte[4];
	struct {
		guchar	audFifoOverflow			:1;
		guchar	audFifoUnderflow			:1;
		guchar								:1;
		guchar	fifoOverrun				:1;
		guchar								:4;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of ih_phy_stat0 (2892_0104h) / ih_mute_phy_stat0 (2892_0184h)   */
union _IoFHdmitxIhPhyStat0{
	guchar		byte[4];
	struct {
		guchar	hdp							:1;
		guchar	txPhyLock					:1;
		guchar	rxSense0					:1;
		guchar	rxSense1					:1;
		guchar	rxSense2					:1;
		guchar	rxSense3					:1;
		guchar								:2;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of ih_i2cm_stat0 (2892_0105h)    */
union _IoFHdmitxIhI2cmStat0{
	guchar		byte[4];
	struct {
		guchar	i2cmastererror				:1;
		guchar	i2cmasterdone				:1;
		guchar	scdcReadreq				:1;
		guchar								:5;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of ih_cec_stat0 (2892_0106h)    */
union _IoFHdmitxIhCecStat0{
	guchar		byte[4];
	struct {
		guchar	done						:1;
		guchar	eom							:1;
		guchar	nack						:1;
		guchar	arbLost					:1;
		guchar	errorInitiator				:1;
		guchar	errorFollow				:1;
		guchar	wakeup						:1;
		guchar								:1;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of ih_vp_stat0 (2892_0107h)    */
union _IoFHdmitxIhVpStat0{
	guchar		byte[4];
	struct {
		guchar	fifoemptybyp				:1;
		guchar	fifofullbyp					:1;
		guchar	fifoemptyremap				:1;
		guchar	fifofullremap				:1;
		guchar	fifoemptypp					:1;
		guchar	fifofullpp					:1;
		guchar	fifoemptyrepet				:1;
		guchar	fifofullrepet				:1;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of ih_i2cmphy_stat0 (2892_0108h)    */
union _IoFHdmitxIhI2cmphyStat0{
	guchar		byte[4];
	struct {
		guchar	i2cmphyerror				:1;
		guchar	i2cmphydone					:1;
		guchar								:6;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of ih_decode (2892_0170h)    */
union _IoFHdmitxIhDecode{
	guchar		byte[4];
	struct {
		guchar								:1;
		guchar	ihCecStat0				:1;
		guchar	ihI2cmStat0				:1;
		guchar	ihPhy						:1;
		guchar	ihAsStat0					:1;
		guchar	ihFcStat2Vp				:1;
		guchar	ihFcStat1					:1;
		guchar	ihFcStat0					:1;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of ih_mute (2892_01FFh)    */
union _IoFHdmitxIhMute{
	guchar		byte[4];
	struct {
		guchar	muteAllInterrup			:1;
		guchar	muteWakeupInterrupt		:1;
		guchar								:6;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/* VideoSampler Registers */

/*  structure of tx_invid0 (2892_0200h)    */
union _IoFHdmitxTxInvid0{
	guchar		byte[4];
	struct {
		guchar	videoMapping				:5;
		guchar								:2;
		guchar	internalDeGenerator		:1;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of tx_instuffing (2892_0201h)    */
union _IoFHdmitxTxInstuffing{
	guchar		byte[4];
	struct {
		guchar	gydataStuffing				:1;
		guchar	rcrdataStuffing			:1;
		guchar	bcbdataStuffing			:1;
		guchar								:5;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/* VideoPacketizer Registers */

/*  structure of vp_status (2892_0800h)    */
union _IoFHdmitxVpStatus{
	guchar		byte[4];
	struct {
		guchar	packingPhase				:4;
		guchar								:4;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of vp_pr_cd (2892_0801h)    */
union _IoFHdmitxVpPrCd{
	guchar		byte[4];
	struct {
		guchar	desiredPrFactor			:4;
		guchar	colorDepth					:4;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of vp_stuff (2892_0802h)    */
union _IoFHdmitxVpStuff{
	guchar		byte[4];
	struct {
		guchar	prStuffing					:1;
		guchar	ppStuffing					:1;
		guchar	ycc422Stuffing				:1;
		guchar	icxGotoP0St				:1;
		guchar	ifixPpToLast				:1;
		guchar	idefaultPhase				:1;
		guchar								:2;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of vp_remap (2892_0803h)    */
union _IoFHdmitxVpRemap{
	guchar		byte[4];
	struct {
		guchar	ycc422Size					:2;
		guchar								:6;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of vp_conf (2892_0804h)    */
union _IoFHdmitxVpConf{
	guchar		byte[4];
	struct {
		guchar	outputSelector				:2;
		guchar	bypassSelect				:1;
		guchar	ycc422En					:1;
		guchar	prEn						:1;
		guchar	ppEn						:1;
		guchar	bypassEn					:1;
		guchar								:1;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of vp_mask (2892_0807h)    */
union _IoFHdmitxVpMask{
	guchar		byte[4];
	struct {
		guchar	ointemptybyp				:1;
		guchar	ointfullbyp					:1;
		guchar	ointemptyremap				:1;
		guchar	ointfullremap				:1;
		guchar	ointemptypp					:1;
		guchar	ointfullpp					:1;
		guchar	ointemptyrepet				:1;
		guchar	ointfullrepet				:1;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/* FrameComposer Registers */

/*  structure of fc_invidconf (2892_1000h)    */
union _IoFHdmitxFcInvidconf{
	guchar		byte[4];
	struct {
		guchar	inIP						:1;
		guchar	rVBlankInOsc			:1;
		guchar								:1;
		guchar	dviModez					:1;
		guchar	deInPolarity				:1;
		guchar	hsyncInPolarity			:1;
		guchar	vsyncInPolarity			:1;
		guchar	hdcpKeepout				:1;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_inhactiv0 (2892_1001h)    */
union _IoFHdmitxFcInhactiv0{
	guchar		byte[4];
	struct {
		guchar	hInActiv					:8;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_inhactiv1 (2892_1002h)    */
union _IoFHdmitxFcInhactiv1{
	guchar		byte[4];
	struct {
		guchar	hInActiv					:4;
		guchar	hInActiv12				:1;
		guchar	hInActiv13				:1;
		guchar								:2;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_inhblank0 (2892_1003h)    */
union _IoFHdmitxFcInhblank0{
	guchar		byte[4];
	struct {
		guchar	hInBlank					:8;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_inhblank1 (2892_1004h)    */
union _IoFHdmitxFcInhblank1{
	guchar		byte[4];
	struct {
		guchar	hInBlank					:2;
		guchar	hInBlank12				:3;
		guchar								:3;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_invactiv0 (2892_1005h)    */
union _IoFHdmitxFcInvactiv0{
	guchar		byte[4];
	struct {
		guchar	vInActiv					:8;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_invactiv1 (2892_1006h)    */
union _IoFHdmitxFcInvactiv1{
	guchar		byte[4];
	struct {
		guchar	vInActiv					:3;
		guchar	vInActiv1211			:2;
		guchar								:3;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_hsyncindelay0 (2892_1008h)    */
union _IoFHdmitxFcHsyncindelay0{
	guchar		byte[4];
	struct {
		guchar	hInDelay					:8;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_hsyncindelay1 (2892_1009h)    */
union _IoFHdmitxFcHsyncindelay1{
	guchar		byte[4];
	struct {
		guchar	hInDelay					:3;
		guchar	hInDelay12				:2;
		guchar								:3;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_hsyncinwidth0 (2892_100Ah)    */
union _IoFHdmitxFcHsyncinwidth0{
	guchar		byte[4];
	struct {
		guchar	hInWidth					:8;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_hsyncinwidth1 (2892_100Bh)    */
union _IoFHdmitxFcHsyncinwidth1{
	guchar		byte[4];
	struct {
		guchar	hInWidth					:1;
		guchar	hInWidth9				:1;
		guchar								:6;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_vsyncinwidth (2892_100Dh)    */
union _IoFHdmitxFcVsyncinwidth{
	guchar		byte[4];
	struct {
		guchar	vInWidth					:6;
		guchar								:2;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_infreq2 (2892_1010h)    */
union _IoFHdmitxFcInfreq2{
	guchar		byte[4];
	struct {
		guchar	infreq						:4;
		guchar								:4;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_ch1pream (2892_1015h)    */
union _IoFHdmitxFcCh1pream{
	guchar		byte[4];
	struct {
		guchar	ch1PreambleFilter			:6;
		guchar								:2;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_ch2pream (2892_1016h)    */
union _IoFHdmitxFcCh2pream{
	guchar		byte[4];
	struct {
		guchar	ch2PreambleFilter			:6;
		guchar								:2;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_aviconf3 (2892_1017h)    */
union _IoFHdmitxFcAviconf3{
	guchar		byte[4];
	struct {
		guchar	cn							:2;
		guchar	yq							:2;
		guchar								:4;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_gcp (2892_1018h)    */
union _IoFHdmitxFcGcp{
	guchar		byte[4];
	struct {
		guchar	clearAvmute				:1;
		guchar	setAvmute					:1;
		guchar	defaultPhase				:1;
		guchar								:5;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_aviconf0 (2892_1019h)    */
union _IoFHdmitxFcAviconf0{
	guchar		byte[4];
	struct {
		guchar	rgcYccIndication			:2;
		guchar	barInformation				:2;
		guchar	scanInformation			:2;
		guchar	activeFormatPresen		:1;
		guchar	rgcYccIndication2		:1;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_aviconf1 (2892_101Ah)    */
union _IoFHdmitxFcAviconf1{
	guchar		byte[4];
	struct {
		guchar	activeAspectRatio			:4;
		guchar	pictureAspectRatio		:2;
		guchar	colorimetry					:2;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_aviconf2 (2892_101Bh)    */
union _IoFHdmitxFcAviconf2{
	guchar		byte[4];
	struct {
		guchar	nonUniformPictureScaling	:2;
		guchar	quantizationRange			:2;
		guchar	extendedColorimetry		:3;
		guchar	itContent					:1;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_avivid (2892_101Ch)    */
union _IoFHdmitxFcAvivid{
	guchar		byte[4];
	struct {
		guchar	fcAvivid					:7;
		guchar	fcAvivid7					:1;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_audiconf0 (2892_1025h)    */
union _IoFHdmitxFcAudiconf0{
	guchar		byte[4];
	struct {
		guchar	ct							:4;
		guchar	cc							:3;
		guchar								:1;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_audiconf1 (2892_1026h)    */
union _IoFHdmitxFcAudiconf1{
	guchar		byte[4];
	struct {
		guchar	sf							:3;
		guchar								:1;
		guchar	ss							:2;
		guchar								:2;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_audiconf3 (2892_1028h)    */
union _IoFHdmitxFcAudiconf3{
	guchar		byte[4];
	struct {
		guchar	lsv							:4;
		guchar	dmInh						:1;
		guchar	lfepbl						:2;
		guchar								:1;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_vsdsize (2892_102Ah)    */
union _IoFHdmitxFcVsdsize{
	guchar		byte[4];
	struct {
		guchar	vsdsize						:5;
		guchar								:3;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_vsdpayload (2892_1032 - 2892_1049h)    */
union _IoFHdmitxFcVsdpayload{
	guchar		byte[4];
	struct {
		guchar	fcVsdpayload				:8;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_spdvendorname (2892_104A - 2892_1051h)    */
union _IoFHdmitxFcSpdvendorname{
	guchar		byte[4];
	struct {
		guchar	fcSpdvendorname			:8;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_spdproductname (2892_1052 - 2892_1061h)    */
union _IoFHdmitxFcSpdproductname{
	guchar		byte[4];
	struct {
		guchar	fcSpdproductname			:8;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_acp (2892_1082 - 2892_1091h)    */
union _IoFHdmitxFcAcp{
	guchar		byte[4];
	struct {
		guchar	fcAcp						:8;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_iscr1 (2892_1082 - 2892_1091h)    */
union _IoFHdmitxFcIscr1{
	guchar		byte[4];
	struct {
		guchar	fcIscr1					:8;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_iscr2 (2892_10A3 - 2892_10B2h)    */
union _IoFHdmitxFcIscr2{
	guchar		byte[4];
	struct {
		guchar	fcIscr2					:8;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_audsconf (2892_1063h)    */
union _IoFHdmitxFcAudsconf{
	guchar		byte[4];
	struct {
		guchar	audPacketLayout			:1;
		guchar								:3;
		guchar	audPacketSampflt			:4;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_audsstat (2892_1064h)    */
union _IoFHdmitxFcAudsstat{
	guchar		byte[4];
	struct {
		guchar	packetSampprs				:4;
		guchar								:4;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_audsv (2892_1065h)    */
union _IoFHdmitxFcAudsv{
	guchar		byte[4];
	struct {
		guchar	v0l							:1;
		guchar	v1l							:1;
		guchar	v2l							:1;
		guchar	v3l							:1;
		guchar	v0r							:1;
		guchar	v1r							:1;
		guchar	v2r							:1;
		guchar	v3r							:1;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_audsu (2892_1066h)    */
union _IoFHdmitxFcAudsu{
	guchar		byte[4];
	struct {
		guchar	u0l							:1;
		guchar	u1l							:1;
		guchar	u2l							:1;
		guchar	u3l							:1;
		guchar	u0r							:1;
		guchar	u1r							:1;
		guchar	u2r							:1;
		guchar	u3r							:1;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_audschnl0 (2892_1067h)    */
union _IoFHdmitxFcAudschnl0{
	guchar		byte[4];
	struct {
		guchar	oiecCopyright				:1;
		guchar								:3;
		guchar	oiecCgmsa					:2;
		guchar								:2;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_audschnl2 (2892_1069h)    */
union _IoFHdmitxFcAudschnl2{
	guchar		byte[4];
	struct {
		guchar	oiecSourcenumber			:4;
		guchar	oiecPcmaudiomode			:3;
		guchar								:1;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};

/*  structure of fc_audschnl3 (2892_106Ah)    */
union _IoFHdmitxFcAudschnl3{
	guchar		byte[4];
	struct {
		guchar	oiecChannelnumcr0			:4;
		guchar	oiecChannelnumcr1			:4;
		guchar								:8;
		guchar								:8;
		guchar								:8;
	}bit;
};


#endif/*__F_HDMITX2P0_LP1_H__*/
