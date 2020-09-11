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


#ifndef __F_HDMITX2P0_LP1_H__
#define __F_HDMITX2P0_LP1_H__


#include <klib.h>


#define F_TYPE_HDMITX2P0_LP1			(f_hdmitx2p0_lp1_get_type())
#define F_HDMITX2P0_LP1(obj)				(K_TYPE_CHECK_INSTANCE_CAST((obj), FHdmitx2p0Lp1))
#define F_IS_HDMITX2P0_LP1(obj)			(K_TYPE_CHECK_INSTANCE_TYPE((obj), F_TYPE_HDMITX2P0_LP1))


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
typedef struct 				_FHdmitx2p0Lp1 FHdmitx2p0Lp1;
typedef struct 				_FHdmitx2p0Lp1Private	FHdmitx2p0Lp1Private;

/* Interrupt Registers */

/* structure of PWRCTRL (2892_0000h) */
union  _IoFHdmitxPwrctrl{
	kushort		hword;
	struct {
		kushort	ckPoweron					:1;
		kushort	txPoweron2					:1;
		kushort	txPoweron1					:1;
		kushort	txPoweron0					:1;
		kushort	txPwron					:1;
		kushort	biasDataOn				:1;
		kushort	biasClkOn					:1;
		kushort								:8;
		kushort	override					:1;
	}bit;
};

/* structure of OPMODE_PLLCFG (2892_0006h) */
union  _IoFHdmitxCpmodePllcfg{
	kushort		hword;
	struct {
		kushort	nCntrl						:2;
		kushort	refCntrl					:2;
		kushort	fbdiv1Cntrl				:2;
		kushort	fbdiv2Cntrl				:3;
		kushort	opmode						:2;
		kushort	tmdsmhlCntrl				:2;
		kushort	prePdiv					:2;
		kushort								:1;
	}bit;
};

/* structure of CKSYMTXCTRL (2892_0009h) */
union  _IoFHdmitxCksymtxctrl{
	kushort		hword;
	struct {
		kushort	ckSymon					:1;
		kushort	TxTrbon					:1;
		kushort	TxTraon					:1;
		kushort	TxSymon					:1;
		kushort	slopeboost					:2;
		kushort								:9;
		kushort	override					:1;
	}bit;
};

/* structure of VLEVCTRL (2892_000Eh) */
union  _IoFHdmitxVlevctrl{
	kushort		hword;
	struct {
		kushort	supCkLvl					:5;
		kushort	supTxLvl					:5;
		kushort								:5;
		kushort	override					:1;
	}bit;
};

/* structure of PLLCURRCTRL (2892_0010h) */
union  _IoFHdmitxPllcurrctrl{
	kushort		hword;
	struct {
		kushort	mpllIntCntrl				:3;
		kushort	mpllPropCntrl				:3;
		kushort								:10;
	}bit;
};

/* structure of PLLCTRL (2892_0014h) */
union  _IoFHdmitxPllctrl{
	kushort		hword;
	struct {
		kushort								:2;
		kushort	mpllRst					:1;
		kushort	mpllPwrOn					:1;
		kushort								:11;
		kushort	override					:1;
	}bit;
};

/* structure of PLLGMPCTRL (2892_0015h) */
union  _IoFHdmitxPllgmpctrl{
	kushort		hword;
	struct {
		kushort	mpllGmpCntrl				:2;
		kushort								:14;
	}bit;
};

/* structure of TXTERM (2892_0019h) */
union  _IoFHdmitxTxterm{
	kushort		hword;
	struct {
		kushort	dTxTerm					:3;
		kushort								:13;
	}bit;
};

/*  structure of ih_fc_stat0 (2892_0100h)    */
union _IoFHdmitxIhFcStat0{
	kuchar		byte[4];
	struct {
		kuchar	nullPkt					:1;
		kuchar	acr							:1;
		kuchar	auds						:1;
		kuchar	nvbi						:1;
		kuchar	mas							:1;
		kuchar	hbr							:1;
		kuchar	acp							:1;
		kuchar	audi						:1;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of ih_fc_stat1 (2892_0101h)    */
union _IoFHdmitxIhFcStat1{
	kuchar		byte[4];
	struct {
		kuchar	gcp							:1;
		kuchar	avi							:1;
		kuchar	amp							:1;
		kuchar	spd							:1;
		kuchar	vsd							:1;
		kuchar	iscr2						:1;
		kuchar	iscr1						:1;
		kuchar	gmd							:1;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of ih_fc_stat2 (2892_0102h)    */
union _IoFHdmitxIhFcStat2{
	kuchar		byte[4];
	struct {
		kuchar	highpriorityOverflow		:1;
		kuchar	lowpriorityOverflow		:1;
		kuchar								:6;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of ih_as_stat0 (2892_0103h)    */
union _IoFHdmitxIhAsStat0{
	kuchar		byte[4];
	struct {
		kuchar	audFifoOverflow			:1;
		kuchar	audFifoUnderflow			:1;
		kuchar								:1;
		kuchar	fifoOverrun				:1;
		kuchar								:4;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of ih_phy_stat0 (2892_0104h) / ih_mute_phy_stat0 (2892_0184h)   */
union _IoFHdmitxIhPhyStat0{
	kuchar		byte[4];
	struct {
		kuchar	hdp							:1;
		kuchar	txPhyLock					:1;
		kuchar	rxSense0					:1;
		kuchar	rxSense1					:1;
		kuchar	rxSense2					:1;
		kuchar	rxSense3					:1;
		kuchar								:2;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of ih_i2cm_stat0 (2892_0105h)    */
union _IoFHdmitxIhI2cmStat0{
	kuchar		byte[4];
	struct {
		kuchar	i2cmastererror				:1;
		kuchar	i2cmasterdone				:1;
		kuchar	scdcReadreq				:1;
		kuchar								:5;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of ih_cec_stat0 (2892_0106h)    */
union _IoFHdmitxIhCecStat0{
	kuchar		byte[4];
	struct {
		kuchar	done						:1;
		kuchar	eom							:1;
		kuchar	nack						:1;
		kuchar	arbLost					:1;
		kuchar	errorInitiator				:1;
		kuchar	errorFollow				:1;
		kuchar	wakeup						:1;
		kuchar								:1;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of ih_vp_stat0 (2892_0107h)    */
union _IoFHdmitxIhVpStat0{
	kuchar		byte[4];
	struct {
		kuchar	fifoemptybyp				:1;
		kuchar	fifofullbyp					:1;
		kuchar	fifoemptyremap				:1;
		kuchar	fifofullremap				:1;
		kuchar	fifoemptypp					:1;
		kuchar	fifofullpp					:1;
		kuchar	fifoemptyrepet				:1;
		kuchar	fifofullrepet				:1;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of ih_i2cmphy_stat0 (2892_0108h)    */
union _IoFHdmitxIhI2cmphyStat0{
	kuchar		byte[4];
	struct {
		kuchar	i2cmphyerror				:1;
		kuchar	i2cmphydone					:1;
		kuchar								:6;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of ih_decode (2892_0170h)    */
union _IoFHdmitxIhDecode{
	kuchar		byte[4];
	struct {
		kuchar								:1;
		kuchar	ihCecStat0				:1;
		kuchar	ihI2cmStat0				:1;
		kuchar	ihPhy						:1;
		kuchar	ihAsStat0					:1;
		kuchar	ihFcStat2Vp				:1;
		kuchar	ihFcStat1					:1;
		kuchar	ihFcStat0					:1;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of ih_mute (2892_01FFh)    */
union _IoFHdmitxIhMute{
	kuchar		byte[4];
	struct {
		kuchar	muteAllInterrup			:1;
		kuchar	muteWakeupInterrupt		:1;
		kuchar								:6;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/* VideoSampler Registers */

/*  structure of tx_invid0 (2892_0200h)    */
union _IoFHdmitxTxInvid0{
	kuchar		byte[4];
	struct {
		kuchar	videoMapping				:5;
		kuchar								:2;
		kuchar	internalDeGenerator		:1;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of tx_instuffing (2892_0201h)    */
union _IoFHdmitxTxInstuffing{
	kuchar		byte[4];
	struct {
		kuchar	gydataStuffing				:1;
		kuchar	rcrdataStuffing			:1;
		kuchar	bcbdataStuffing			:1;
		kuchar								:5;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/* VideoPacketizer Registers */

/*  structure of vp_status (2892_0800h)    */
union _IoFHdmitxVpStatus{
	kuchar		byte[4];
	struct {
		kuchar	packingPhase				:4;
		kuchar								:4;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of vp_pr_cd (2892_0801h)    */
union _IoFHdmitxVpPrCd{
	kuchar		byte[4];
	struct {
		kuchar	desiredPrFactor			:4;
		kuchar	colorDepth					:4;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of vp_stuff (2892_0802h)    */
union _IoFHdmitxVpStuff{
	kuchar		byte[4];
	struct {
		kuchar	prStuffing					:1;
		kuchar	ppStuffing					:1;
		kuchar	ycc422Stuffing				:1;
		kuchar	icxGotoP0St				:1;
		kuchar	ifixPpToLast				:1;
		kuchar	idefaultPhase				:1;
		kuchar								:2;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of vp_remap (2892_0803h)    */
union _IoFHdmitxVpRemap{
	kuchar		byte[4];
	struct {
		kuchar	ycc422Size					:2;
		kuchar								:6;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of vp_conf (2892_0804h)    */
union _IoFHdmitxVpConf{
	kuchar		byte[4];
	struct {
		kuchar	outputSelector				:2;
		kuchar	bypassSelect				:1;
		kuchar	ycc422En					:1;
		kuchar	prEn						:1;
		kuchar	ppEn						:1;
		kuchar	bypassEn					:1;
		kuchar								:1;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of vp_mask (2892_0807h)    */
union _IoFHdmitxVpMask{
	kuchar		byte[4];
	struct {
		kuchar	ointemptybyp				:1;
		kuchar	ointfullbyp					:1;
		kuchar	ointemptyremap				:1;
		kuchar	ointfullremap				:1;
		kuchar	ointemptypp					:1;
		kuchar	ointfullpp					:1;
		kuchar	ointemptyrepet				:1;
		kuchar	ointfullrepet				:1;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/* FrameComposer Registers */

/*  structure of fc_invidconf (2892_1000h)    */
union _IoFHdmitxFcInvidconf{
	kuchar		byte[4];
	struct {
		kuchar	inIP						:1;
		kuchar	rVBlankInOsc			:1;
		kuchar								:1;
		kuchar	dviModez					:1;
		kuchar	deInPolarity				:1;
		kuchar	hsyncInPolarity			:1;
		kuchar	vsyncInPolarity			:1;
		kuchar	hdcpKeepout				:1;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_inhactiv0 (2892_1001h)    */
union _IoFHdmitxFcInhactiv0{
	kuchar		byte[4];
	struct {
		kuchar	hInActiv					:8;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_inhactiv1 (2892_1002h)    */
union _IoFHdmitxFcInhactiv1{
	kuchar		byte[4];
	struct {
		kuchar	hInActiv					:4;
		kuchar	hInActiv12				:1;
		kuchar	hInActiv13				:1;
		kuchar								:2;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_inhblank0 (2892_1003h)    */
union _IoFHdmitxFcInhblank0{
	kuchar		byte[4];
	struct {
		kuchar	hInBlank					:8;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_inhblank1 (2892_1004h)    */
union _IoFHdmitxFcInhblank1{
	kuchar		byte[4];
	struct {
		kuchar	hInBlank					:2;
		kuchar	hInBlank12				:3;
		kuchar								:3;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_invactiv0 (2892_1005h)    */
union _IoFHdmitxFcInvactiv0{
	kuchar		byte[4];
	struct {
		kuchar	vInActiv					:8;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_invactiv1 (2892_1006h)    */
union _IoFHdmitxFcInvactiv1{
	kuchar		byte[4];
	struct {
		kuchar	vInActiv					:3;
		kuchar	vInActiv1211			:2;
		kuchar								:3;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_hsyncindelay0 (2892_1008h)    */
union _IoFHdmitxFcHsyncindelay0{
	kuchar		byte[4];
	struct {
		kuchar	hInDelay					:8;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_hsyncindelay1 (2892_1009h)    */
union _IoFHdmitxFcHsyncindelay1{
	kuchar		byte[4];
	struct {
		kuchar	hInDelay					:3;
		kuchar	hInDelay12				:2;
		kuchar								:3;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_hsyncinwidth0 (2892_100Ah)    */
union _IoFHdmitxFcHsyncinwidth0{
	kuchar		byte[4];
	struct {
		kuchar	hInWidth					:8;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_hsyncinwidth1 (2892_100Bh)    */
union _IoFHdmitxFcHsyncinwidth1{
	kuchar		byte[4];
	struct {
		kuchar	hInWidth					:1;
		kuchar	hInWidth9				:1;
		kuchar								:6;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_vsyncinwidth (2892_100Dh)    */
union _IoFHdmitxFcVsyncinwidth{
	kuchar		byte[4];
	struct {
		kuchar	vInWidth					:6;
		kuchar								:2;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_infreq2 (2892_1010h)    */
union _IoFHdmitxFcInfreq2{
	kuchar		byte[4];
	struct {
		kuchar	infreq						:4;
		kuchar								:4;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_ch1pream (2892_1015h)    */
union _IoFHdmitxFcCh1pream{
	kuchar		byte[4];
	struct {
		kuchar	ch1PreambleFilter			:6;
		kuchar								:2;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_ch2pream (2892_1016h)    */
union _IoFHdmitxFcCh2pream{
	kuchar		byte[4];
	struct {
		kuchar	ch2PreambleFilter			:6;
		kuchar								:2;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_aviconf3 (2892_1017h)    */
union _IoFHdmitxFcAviconf3{
	kuchar		byte[4];
	struct {
		kuchar	cn							:2;
		kuchar	yq							:2;
		kuchar								:4;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_gcp (2892_1018h)    */
union _IoFHdmitxFcGcp{
	kuchar		byte[4];
	struct {
		kuchar	clearAvmute				:1;
		kuchar	setAvmute					:1;
		kuchar	defaultPhase				:1;
		kuchar								:5;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_aviconf0 (2892_1019h)    */
union _IoFHdmitxFcAviconf0{
	kuchar		byte[4];
	struct {
		kuchar	rgcYccIndication			:2;
		kuchar	barInformation				:2;
		kuchar	scanInformation			:2;
		kuchar	activeFormatPresen		:1;
		kuchar	rgcYccIndication2		:1;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_aviconf1 (2892_101Ah)    */
union _IoFHdmitxFcAviconf1{
	kuchar		byte[4];
	struct {
		kuchar	activeAspectRatio			:4;
		kuchar	pictureAspectRatio		:2;
		kuchar	colorimetry					:2;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_aviconf2 (2892_101Bh)    */
union _IoFHdmitxFcAviconf2{
	kuchar		byte[4];
	struct {
		kuchar	nonUniformPictureScaling	:2;
		kuchar	quantizationRange			:2;
		kuchar	extendedColorimetry		:3;
		kuchar	itContent					:1;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_avivid (2892_101Ch)    */
union _IoFHdmitxFcAvivid{
	kuchar		byte[4];
	struct {
		kuchar	fcAvivid					:7;
		kuchar	fcAvivid7					:1;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_audiconf0 (2892_1025h)    */
union _IoFHdmitxFcAudiconf0{
	kuchar		byte[4];
	struct {
		kuchar	ct							:4;
		kuchar	cc							:3;
		kuchar								:1;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_audiconf1 (2892_1026h)    */
union _IoFHdmitxFcAudiconf1{
	kuchar		byte[4];
	struct {
		kuchar	sf							:3;
		kuchar								:1;
		kuchar	ss							:2;
		kuchar								:2;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_audiconf3 (2892_1028h)    */
union _IoFHdmitxFcAudiconf3{
	kuchar		byte[4];
	struct {
		kuchar	lsv							:4;
		kuchar	dmInh						:1;
		kuchar	lfepbl						:2;
		kuchar								:1;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_vsdsize (2892_102Ah)    */
union _IoFHdmitxFcVsdsize{
	kuchar		byte[4];
	struct {
		kuchar	vsdsize						:5;
		kuchar								:3;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_vsdpayload (2892_1032 - 2892_1049h)    */
union _IoFHdmitxFcVsdpayload{
	kuchar		byte[4];
	struct {
		kuchar	fcVsdpayload				:8;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_spdvendorname (2892_104A - 2892_1051h)    */
union _IoFHdmitxFcSpdvendorname{
	kuchar		byte[4];
	struct {
		kuchar	fcSpdvendorname			:8;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_spdproductname (2892_1052 - 2892_1061h)    */
union _IoFHdmitxFcSpdproductname{
	kuchar		byte[4];
	struct {
		kuchar	fcSpdproductname			:8;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_acp (2892_1082 - 2892_1091h)    */
union _IoFHdmitxFcAcp{
	kuchar		byte[4];
	struct {
		kuchar	fcAcp						:8;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_iscr1 (2892_1082 - 2892_1091h)    */
union _IoFHdmitxFcIscr1{
	kuchar		byte[4];
	struct {
		kuchar	fcIscr1					:8;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_iscr2 (2892_10A3 - 2892_10B2h)    */
union _IoFHdmitxFcIscr2{
	kuchar		byte[4];
	struct {
		kuchar	fcIscr2					:8;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_audsconf (2892_1063h)    */
union _IoFHdmitxFcAudsconf{
	kuchar		byte[4];
	struct {
		kuchar	audPacketLayout			:1;
		kuchar								:3;
		kuchar	audPacketSampflt			:4;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_audsstat (2892_1064h)    */
union _IoFHdmitxFcAudsstat{
	kuchar		byte[4];
	struct {
		kuchar	packetSampprs				:4;
		kuchar								:4;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_audsv (2892_1065h)    */
union _IoFHdmitxFcAudsv{
	kuchar		byte[4];
	struct {
		kuchar	v0l							:1;
		kuchar	v1l							:1;
		kuchar	v2l							:1;
		kuchar	v3l							:1;
		kuchar	v0r							:1;
		kuchar	v1r							:1;
		kuchar	v2r							:1;
		kuchar	v3r							:1;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_audsu (2892_1066h)    */
union _IoFHdmitxFcAudsu{
	kuchar		byte[4];
	struct {
		kuchar	u0l							:1;
		kuchar	u1l							:1;
		kuchar	u2l							:1;
		kuchar	u3l							:1;
		kuchar	u0r							:1;
		kuchar	u1r							:1;
		kuchar	u2r							:1;
		kuchar	u3r							:1;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_audschnl0 (2892_1067h)    */
union _IoFHdmitxFcAudschnl0{
	kuchar		byte[4];
	struct {
		kuchar	oiecCopyright				:1;
		kuchar								:3;
		kuchar	oiecCgmsa					:2;
		kuchar								:2;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_audschnl2 (2892_1069h)    */
union _IoFHdmitxFcAudschnl2{
	kuchar		byte[4];
	struct {
		kuchar	oiecSourcenumber			:4;
		kuchar	oiecPcmaudiomode			:3;
		kuchar								:1;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of fc_audschnl3 (2892_106Ah)    */
union _IoFHdmitxFcAudschnl3{
	kuchar		byte[4];
	struct {
		kuchar	oiecChannelnumcr0			:4;
		kuchar	oiecChannelnumcr1			:4;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

struct  _FHdmitx2p0Lp1
{
	KObject parent;
};


KConstType					f_hdmitx2p0_lp1_get_type(void);
FHdmitx2p0Lp1*		f_hdmitx2p0_lp1_new(void);


#endif/*__F_HDMITX2P0_LP1_H__*/
