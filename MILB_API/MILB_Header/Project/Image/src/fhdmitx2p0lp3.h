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


#ifndef __F_HDMITX2P0_LP3_H__
#define __F_HDMITX2P0_LP3_H__


#include <klib.h>
#include "fhdmitx2p0lp1.h"
#include "fhdmitx2p0lp2.h"


#define F_TYPE_HDMITX2P0_LP3			(f_hdmitx2p0_lp3_get_type())
#define F_HDMITX2P0_LP3(obj)				(K_TYPE_CHECK_INSTANCE_CAST((obj), FHdmitx2p0Lp3))
#define F_IS_HDMITX2P0_LP3(obj)			(K_TYPE_CHECK_INSTANCE_TYPE((obj), F_TYPE_HDMITX2P0_LP3))


typedef union 				_IoFHdmitxCecCtrl IoFHdmitxCecCtrl;
typedef union 				_IoFHdmitxCecMask IoFHdmitxCecMask;
typedef union 				_IoFHdmitxCecAddrL IoFHdmitxCecAddrL;
typedef union 				_IoFHdmitxCecAddrH IoFHdmitxCecAddrH;
typedef union 				_IoFHdmitxCecTxCnt IoFHdmitxCecTxCnt;
typedef union 				_IoFHdmitxCecRxCnt IoFHdmitxCecRxCnt;
typedef union 				_IoFHdmitxCecTxData IoFHdmitxCecTxData;
typedef union 				_IoFHdmitxCecRxData IoFHdmitxCecRxData;
typedef union 				_IoFHdmitxCecLock IoFHdmitxCecLock;
typedef union 				_IoFHdmitxCecWakeupctrl IoFHdmitxCecWakeupctrl;
typedef union 				_IoFHdmitxI2cmSlave IoFHdmitxI2cmSlave;
typedef union 				_IoFHdmitxI2cmOperation IoFHdmitxI2cmOperation;
typedef union 				_IoFHdmitxI2cmInt IoFHdmitxI2cmInt;
typedef union 				_IoFHdmitxI2cmCtlint IoFHdmitxI2cmCtlint;
typedef union 				_IoFHdmitxI2cmDiv IoFHdmitxI2cmDiv;
typedef union 				_IoFHdmitxI2cmSegaddr IoFHdmitxI2cmSegaddr;
typedef union 				_IoFHdmitxI2cmSoftrstz IoFHdmitxI2cmSoftrstz;
typedef union 				_IoFHdmitxI2cmScdcReadUpdate IoFHdmitxI2cmScdcReadUpdate;
typedef union 				_IoFHdmitxI2cmReadBuff IoFHdmitxI2cmReadBuff;
typedef union 				_IoFHdmitxI2cmScdcUpdate IoFHdmitxI2cmScdcUpdate;
typedef struct 				_IoFHdmiCscCoef IoFHdmiCscCoef;
typedef struct 				_IoFHdmitx2p0Lp IoFHdmitx2p0Lp;
typedef struct 				_FHdmitx2p0Lp3 FHdmitx2p0Lp3;
typedef struct 				_FHdmitx2p0Lp3Private	FHdmitx2p0Lp3Private;

/* CEC Registers */

/*  structure of cec_ctrl (2892_7D00h)    */
union _IoFHdmitxCecCtrl{
	kuchar		byte[4];
	struct {
		kuchar	send						:1;
		kuchar	frameTyp					:2;
		kuchar	bcNack						:1;
		kuchar	standby						:1;
		kuchar								:3;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of cec_mask (2892_7D02h)    */
union _IoFHdmitxCecMask{
	kuchar		byte[4];
	struct {
		kuchar	done						:1;
		kuchar	eom							:1;
		kuchar	nack						:1;
		kuchar	arbLost					:1;
		kuchar	errorInitiator				:1;
		kuchar	errorFlow					:1;
		kuchar	wakeup						:1;
		kuchar								:1;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of cec_addr_l (2892_7D05h)    */
union _IoFHdmitxCecAddrL{
	kuchar		byte[4];
	struct {
		kuchar	cecAddrL0				:1;
		kuchar	cecAddrL1				:1;
		kuchar	cecAddrL2				:1;
		kuchar	cecAddrL3				:1;
		kuchar	cecAddrL4				:1;
		kuchar	cecAddrL5				:1;
		kuchar	cecAddrL6				:1;
		kuchar	cecAddrL7				:1;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of cec_addr_h (2892_7D06h)    */
union _IoFHdmitxCecAddrH{
	kuchar		byte[4];
	struct {
		kuchar	cecAddrH0				:1;
		kuchar	cecAddrH1				:1;
		kuchar	cecAddrH2				:1;
		kuchar	cecAddrH3				:1;
		kuchar	cecAddrH4				:1;
		kuchar	cecAddrH5				:1;
		kuchar	cecAddrH6				:1;
		kuchar	cecAddrH7				:1;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of cec_tx_cnt (2892_7D07h)    */
union _IoFHdmitxCecTxCnt{
	kuchar		byte[4];
	struct {
		kuchar	cecTxCnt					:5;
		kuchar								:3;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of cec_rx_cnt (2892_7D08h)    */
union _IoFHdmitxCecRxCnt{
	kuchar		byte[4];
	struct {
		kuchar	cecRxCnt					:5;
		kuchar								:3;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of cec_tx_data (2892_7D10 - 2892_7D1Fh)    */
union _IoFHdmitxCecTxData{
	kuchar		byte[4];
	struct {
		kuchar	cecTxData					:8;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of cec_rx_data (2892_7D20 - 2892_7D2Fh)    */
union _IoFHdmitxCecRxData{
	kuchar		byte[4];
	struct {
		kuchar	cecRxData					:8;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of cec_lock (2892_7D30h)    */
union _IoFHdmitxCecLock{
	kuchar		byte[4];
	struct {
		kuchar	lockedBuffer				:1;
		kuchar								:7;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of cec_wakeupctrl (2892_7D31h)    */
union _IoFHdmitxCecWakeupctrl{
	kuchar		byte[4];
	struct {
		kuchar	opcode0x04en				:1;
		kuchar	opcode0x0Den				:1;
		kuchar	opcode0x41en				:1;
		kuchar	opcode0x42en				:1;
		kuchar	opcode0x44en				:1;
		kuchar	opcode0x70en				:1;
		kuchar	opcode0x82en				:1;
		kuchar	opcode0x86en				:1;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/* EDDC Registers */

/*  structure of i2cm_slave (2892_7E00h)    */
union _IoFHdmitxI2cmSlave{
	kuchar		byte[4];
	struct {
		kuchar	slaveaddr					:7;
		kuchar								:1;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of i2cm_operation (2892_7E04h)    */
union _IoFHdmitxI2cmOperation{
	kuchar		byte[4];
	struct {
		kuchar	rd							:1;
		kuchar	rdExt						:1;
		kuchar	rd8							:1;
		kuchar	rd8Ext						:1;
		kuchar	wr							:1;
		kuchar								:3;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of i2cm_int (2892_7E05h)    */
union _IoFHdmitxI2cmInt{
	kuchar		byte[4];
	struct {
		kuchar								:2;
		kuchar	doneMask					:1;
		kuchar								:3;
		kuchar	readReqMask				:1;
		kuchar								:1;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of i2cm_ctlint (2892_7E06h)    */
union _IoFHdmitxI2cmCtlint{
	kuchar		byte[4];
	struct {
		kuchar								:2;
		kuchar	arbitrationMask			:1;
		kuchar								:3;
		kuchar	nackMask					:1;
		kuchar								:1;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of i2cm_div (2892_7E07h)    */
union _IoFHdmitxI2cmDiv{
	kuchar		byte[4];
	struct {
		kuchar								:3;
		kuchar	fastStdMode				:1;
		kuchar								:3;
		kuchar	busclear					:1;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of i2cm_segaddr (2892_7E08h)    */
union _IoFHdmitxI2cmSegaddr{
	kuchar		byte[4];
	struct {
		kuchar	segAddr					:7;
		kuchar								:1;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of i2cm_softrstz (2892_7E09h)    */
union _IoFHdmitxI2cmSoftrstz{
	kuchar		byte[4];
	struct {
		kuchar	i2cSoftrstz				:1;
		kuchar								:7;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of i2cm_scdc_read_update (2892_7E14h)    */
union _IoFHdmitxI2cmScdcReadUpdate{
	kuchar		byte[4];
	struct {
		kuchar	readUpdate					:1;
		kuchar								:3;
		kuchar	readRequestEn				:1;
		kuchar	updtrdVsyncpollEn			:1;
		kuchar								:2;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of i2cm_read_buff (2892_7E20 - 2892_7E27h)    */
union _IoFHdmitxI2cmReadBuff{
	kuchar		byte[4];
	struct {
		kuchar	i2cmReadBuff				:8;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of i2cm_scdc_update (2892_7E30 - 2892_7E31h)    */
union _IoFHdmitxI2cmScdcUpdate{
	kuchar		byte[4];
	struct {
		kuchar	i2cmScdcUpdate			:8;
		kuchar								:8;
		kuchar								:8;
		kuchar								:8;
	}bit;
};

/*  structure of csc_coef (2892_(4102 - 4119)h) */
struct _IoFHdmiCscCoef{
	/* Color Space Converter Matrix Coefficient Register MSB */
	kuchar	msb;
	kuchar		dmyFHdmitx1[3];
	/* Color Space Converter Matrix Coefficient Register LSB */
	kuchar	lsb;
	kuchar		dmyFHdmitx2[3];
};

/* Define i/o mapping */
struct _IoFHdmitx2p0Lp{
	/* F_HDMITX2p0_LP */
	/* 2892_0000 - 0001h */
	IoFHdmitxPwrctrl						pwrctrl;
	/* 2892_0002 - 0005h */
	kuchar	dmyFHdmitx00020017[0x0018 - 0x0002];
	/* 2892_0006 - 0007h(2892_0018 - 2892_0019h) */
	IoFHdmitxCpmodePllcfg				opmodePllcfg;
	/* 2892_0008h */
	kuchar	dmyFHdmitx001a0023[0x0024 - 0x001A];
	/* 2892_0009 - 000Ah(2892_0024 - 2892_0025h) */
	IoFHdmitxCksymtxctrl					cksymtxctrl;
	/* 2892_000B - 000Dh */
	kuchar	dmyFHdmitx00260037[0x0038 - 0x0026];
	/* 2892_000E - 000Fh(2892_0038 - 2892_0039h) */
	IoFHdmitxVlevctrl						vlevctrl;
	/* 2892_000B - 000Dh */
	kuchar	dmyFHdmitx003a003f[0x0040 - 0x003A];
	/* 2892_0010 - 0011h(2892_0040 - 2892_0041h) */
	IoFHdmitxPllcurrctrl					pllcurrctrl;
	/* 2892_0012 - 0013h */
	kuchar	dmyFHdmitx0042004f[0x0050 - 0x0042];
	/* 2892_0014 - 0015h(2892_0050 - 2892_0051h) */
	IoFHdmitxPllctrl						pllctrl;
	/* 2892_000B - 000Dh */
	kuchar	dmyFHdmitx00520053[0x0054 - 0x0052];
	/* 2892_0015 - 0016h(2892_0054 - 2892_0055h) */
	IoFHdmitxPllgmpctrl					pllgmpctrl;
	/* 2892_0017 - 0018h */
	kuchar	dmyFHdmitx00560063[0x0064 - 0x0056];
	/* 2892_0019 - 001Ah(2892_0064 - 2892_0065h) */
	IoFHdmitxTxterm						txterm;
	/* 2892_001B - 00FFh(2892_006C - 2892_03FCh) */
	kuchar	dmyFHdmitx006603ff[0x0400 - 0x0066];
	/* 2892_0100h(2892_0400h) */
	IoFHdmitxIhFcStat0					ihFcStat0;
	/* 2892_0101h(2892_0404h) */
	IoFHdmitxIhFcStat1					ihFcStat1;
	/* 2892_0102h(2892_0408h) */
	IoFHdmitxIhFcStat2					ihFcStat2;
	/* 2892_0103h(2892_040Ch) */
	IoFHdmitxIhAsStat0					ihAsStat0;
	/* 2892_0104h(2892_0410h) */
	IoFHdmitxIhPhyStat0					ihPhyStat0;
	/* 2892_0105h(2892_0414h) */
	IoFHdmitxIhI2cmStat0				ihI2cmStat0;
	/* 2892_0106h(2892_0418h) */
	IoFHdmitxIhCecStat0					ihCecStat0;
	/* 2892_0107h(2892_041Ch) */
	IoFHdmitxIhVpStat0					ihVpStat0;
	/* 2892_0108h(2892_0420h) */
	IoFHdmitxIhI2cmphyStat0				ihI2cmphyStat0;
	/* 2892_(0109 - 016Fh) */
	kuchar	dmyFHdmitx042405bf[0x05C0 - 0x0424];
	/* 2892_0170h(2892_05C0h) */
	IoFHdmitxIhDecode					ihDecode;
	/* 2892_(0171 - 017Fh) */
	kuchar	dmyFHdmitx05c405ff[0x0600 - 0x05C4];
	/* 2892_0180h(2892_0600h) */
	IoFHdmitxIhFcStat0					ihMuteFcStat0;
	/* 2892_0181h(2892_0604h) */
	IoFHdmitxIhFcStat1					ihMuteFcStat1;
	/* 2892_0182h(2892_0608h) */
	IoFHdmitxIhFcStat2					ihMuteFcStat2;
	/* 2892_0183h(2892_060Ch) */
	IoFHdmitxIhAsStat0					ihMuteAsStat0;
	/* 2892_0184h(2892_0610h) */
	IoFHdmitxIhPhyStat0					ihMutePhyStat0;
	/* 2892_0185h(2892_0614h) */
	IoFHdmitxIhI2cmStat0				ihMuteI2cmStat0;
	/* 2892_0186h(2892_0618h) */
	IoFHdmitxIhCecStat0					ihMuteCecStat0;
	/* 2892_0187h(2892_061Ch) */
	IoFHdmitxIhVpStat0					ihMuteVpStat0;
	/* 2892_0188h(2892_0620h) */
	IoFHdmitxIhI2cmphyStat0				ihMuteI2cmphyStat0;
	/* 2892_(0189 - 01FEh) */
	kuchar	dmyFHdmitx062407fb[0x07FC - 0x0624];
	/* 2892_01FFh(2892_07FCh) */
	IoFHdmitxIhMute						ihMute;
	/* 2892_0200h(2892_0800h) */
	IoFHdmitxTxInvid0					txInvid0;
	/* 2892_0201h(2892_0804h) */
	IoFHdmitxTxInstuffing				txInstuffing;
	/* 2892_0202h(2892_0808h) */
	kuchar									txGydata0;
	kuchar	dmyFHdmitx28920808[3];
	/* 2892_0203h(2892_080Ch) */
	kuchar									txGydata1;
	kuchar	dmyFHdmitx2892080c[3];
	/* 2892_0204h(2892_0810h) */
	kuchar									txRcrdata0;
	kuchar	dmyFHdmitx28920810[3];
	/* 2892_0205h(2892_0814h) */
	kuchar									txRcrdata1;
	kuchar	dmyFHdmitx28920814[3];
	/* 2892_0206h(2892_0818h) */
	kuchar									txBcbdata0;
	kuchar	dmyFHdmitx28920818[3];
	/* 2892_0207h(2892_081Ch) */
	kuchar									txBcbdata1;
	kuchar	dmyFHdmitx2892081c[3];
	/* 2892_(0208 - 07FFh) */
	kuchar	dmyFHdmitx08201fff[0x2000 - 0x0820];
	/* 2892_0800h(2892_2000h) */
	IoFHdmitxVpStatus					vpStatus;
	/* 2892_0801h(2892_2004h) */
	IoFHdmitxVpPrCd						vpPrCd;
	/* 2892_0802h(2892_2008h) */
	IoFHdmitxVpStuff						vpStuff;
	/* 2892_0803h(2892_200Ch) */
	IoFHdmitxVpRemap						vpRemap;
	/* 2892_0804h(2892_2010h) */
	IoFHdmitxVpConf						vpConf;
	/* 2892_(0805 - 0806h) */
	kuchar	dmyFHdmitx2014201b[0x201C - 0x2014];
	/* 2892_0807h(2892_201Ch) */
	IoFHdmitxVpMask						vpMask;
	/* 2892_(0808 - 0FFFh) */
	kuchar	dmyFHdmitx20203fff[0x4000 - 0x2020];
	/* 2892_1000h(2892_4000h) */
	IoFHdmitxFcInvidconf					fcInvidconf;
	/* 2892_1001h(2892_4004h) */
	IoFHdmitxFcInhactiv0					fcInhactiv0;
	/* 2892_1002h(2892_4008h) */
	IoFHdmitxFcInhactiv1					fcInhactiv1;
	/* 2892_1003h(2892_400Ch) */
	IoFHdmitxFcInhblank0					fcInhblank0;
	/* 2892_1004h(2892_4010h) */
	IoFHdmitxFcInhblank1					fcInhblank1;
	/* 2892_1005h(2892_4014h) */
	IoFHdmitxFcInvactiv0					fcInvactiv0;
	/* 2892_1006h(2892_4018h) */
	IoFHdmitxFcInvactiv1					fcInvactiv1;
	/* 2892_1007h(2892_401Ch) */
	kuchar									fcInvblank;
	kuchar	dmyFHdmitx2892401c[3];
	/* 2892_1008h(2892_4020h) */
	IoFHdmitxFcHsyncindelay0				fcHsyncindelay0;
	/* 2892_1009h(2892_4024h) */
	IoFHdmitxFcHsyncindelay1				fcHsyncindelay1;
	/* 2892_100Ah(2892_4028h) */
	IoFHdmitxFcHsyncinwidth0				fcHsyncinwidth0;
	/* 2892_100Bh(2892_402Ch) */
	IoFHdmitxFcHsyncinwidth1				fcHsyncinwidth1;
	/* 2892_100Ch(2892_4030h) */
	kuchar									fcVsyncindelay;
	kuchar	dmyFHdmitx28924030[3];
	/* 2892_100Dh(2892_4034h) */
	IoFHdmitxFcVsyncinwidth				fcVsyncinwidth;
	/* 2892_100Eh(2892_4038h) */
	kuchar									fcInfreq0;
	kuchar	dmyFHdmitx28924038[3];
	/* 2892_100Fh(2892_403Ch) */
	kuchar									fcInfreq1;
	kuchar	dmyFHdmitx2892403c[3];
	/* 2892_1010h(2892_4040h) */
	IoFHdmitxFcInfreq2					fcInfreq2;
	/* 2892_1011h(2892_4044h) */
	kuchar									fcCtrldur;
	kuchar	dmyFHdmitx28924044[3];
	/* 2892_1012h(2892_4048h) */
	kuchar									fcExctrldur;
	kuchar	dmyFHdmitx28924048[3];
	/* 2892_1013h(2892_404Ch) */
	kuchar									fcExctrlspac;
	kuchar	dmyFHdmitx2892404C[3];
	/* 2892_1014h(2892_4050h) */
	kuchar									fcCh0pream;
	kuchar	dmyFHdmitx28924050[3];
	/* 2892_1015h(2892_4054h) */
	IoFHdmitxFcCh1pream					fcCh1pream;
	/* 2892_1016h(2892_4058h) */
	IoFHdmitxFcCh2pream					fcCh2pream;
	/* 2892_1017h(2892_405Ch) */
	IoFHdmitxFcAviconf3					fcAviconf3;
	/* 2892_1018h(2892_4060h) */
	IoFHdmitxFcGcp						fcGcp;
	/* 2892_1019h(2892_4064h) */
	IoFHdmitxFcAviconf0					fcAviconf0;
	/* 2892_101Ah(2892_4068h) */
	IoFHdmitxFcAviconf1					fcAviconf1;
	/* 2892_101Bh(2892_406Ch) */
	IoFHdmitxFcAviconf2					fcAviconf2;
	/* 2892_101Ch(2892_4070h) */
	IoFHdmitxFcAvivid					fcAvivid;
	/* 2892_101Dh(2892_4074h) */
	kuchar									fcAvietb0;
	kuchar	dmyFHdmitx28924074[3];
	/* 2892_101Eh(2892_4078h) */
	kuchar									fcAvietb1;
	kuchar	dmyFHdmitx28924078[3];
	/* 2892_101Fh(2892_407Ch) */
	kuchar									fcAvisbb0;
	kuchar	dmyFHdmitx2892407c[3];
	/* 2892_1020h(2892_4080h) */
	kuchar									fcAvisbb1;
	kuchar	dmyFHdmitx28924080[3];
	/* 2892_1021h(2892_4084h) */
	kuchar									fcAvielb0;
	kuchar	dmyFHdmitx28924084[3];
	/* 2892_1022h(2892_4088h) */
	kuchar									fcAvielb1;
	kuchar	dmyFHdmitx28924088[3];
	/* 2892_1023h(2892_408Ch) */
	kuchar									fcAvisrb0;
	kuchar	dmyFHdmitx2892408c[3];
	/* 2892_1024h(2892_4090h) */
	kuchar									fcAvisrb1;
	kuchar	dmyFHdmitx28924090[3];
	/* 2892_1025h(2892_4094h) */
	IoFHdmitxFcAudiconf0					fcAudiconf0;
	/* 2892_1026h(2892_4098h) */
	IoFHdmitxFcAudiconf1					fcAudiconf1;
	/* 2892_1027h(2892_409Ch) */
	kuchar									fcAudiconf2;
	kuchar	dmyFHdmitx2892409c[3];
	/* 2892_1028h(2892_40A0h) */
	IoFHdmitxFcAudiconf3					fcAudiconf3;
	/* 2892_1029h(2892_40A4h) */
	kuchar									fcVsdieeeid2;
	kuchar	dmyFHdmitx289240a4[3];
	/* 2892_102Ah(2892_40A8h) */
	IoFHdmitxFcVsdsize					fcVsdsize;
	/* 2892_(102B - 102Fh) */
	kuchar	dmyFHdmitx40ac40bf[0x40C0 - 0x40AC];
	/* 2892_1030h(2892_40C0h) */
	kuchar									fcVsdieeeid1;
	kuchar	dmyFHdmitx289240c0[3];
	/* 2892_1031h(2892_40C4h) */
	kuchar									fcVsdieeeid0;
	kuchar	dmyFHdmitx289240c4[3];
	/* 2892_1032 - 1049h(2892_40C8h - 2892_4124h) */
	IoFHdmitxFcVsdpayload					fcVsdpayload[24];
	/* 2892_104A - 1051h(2892_4128h - 2892_4144h) */
	IoFHdmitxFcSpdvendorname				fcSpdvendorname[8];
	/* 2892_1052 - 1061h(2892_4148h - 2892_4184h) */
	IoFHdmitxFcSpdproductname				fcSpdproductname[16];
	/* 2892_1062h(2892_4188h) */
	kuchar									fcSpddeviceinf;
	kuchar	dmyFHdmitx28924188[3];
	/* 2892_1063h(2892_418Ch) */
	IoFHdmitxFcAudsconf					fcAudsconf;
	/* 2892_1064h(2892_4190h) */
	IoFHdmitxFcAudsstat					fcAudsstat;
	/* 2892_1065h(2892_4194h) */
	IoFHdmitxFcAudsv						fcAudsv;
	/* 2892_1066h(2892_4198h) */
	IoFHdmitxFcAudsu						fcAudsu;
	/* 2892_1067h(2892_419Ch) */
	IoFHdmitxFcAudschnl0					fcAudschnl0;
	/* 2892_1068h(2892_41A0h) */
	kuchar									fcAudschnl1;
	kuchar	dmyFHdmitx289241a0[3];
	/* 2892_1069h(2892_41A4h) */
	IoFHdmitxFcAudschnl2					fcAudschnl2;
	/* 2892_106Ah(2892_41A8h) */
	IoFHdmitxFcAudschnl3					fcAudschnl3;
	/* 2892_106Bh(2892_41ACh) */
	IoFHdmitxFcAudschnl4					fcAudschnl4;
	/* 2892_106Ch(2892_41B0h) */
	IoFHdmitxFcAudschnl5					fcAudschnl5;
	/* 2892_106Dh(2892_41B4h) */
	IoFHdmitxFcAudschnl6					fcAudschnl6;
	/* 2892_106Eh(2892_41B8h) */
	IoFHdmitxFcAudschnl7					fcAudschnl7;
	/* 2892_106Fh(2892_41BCh) */
	IoFHdmitxFcAudschnl8					fcAudschnl8;
	/* 2892_(1070 - 1072h) */
	kuchar	dmyFHdmitx41c041cb[0x41CC - 0x41C0];
	/* 2892_1073h(2892_41CCh) */
	IoFHdmitxFcCtrlqhigh					fcCtrlqhigh;
	/* 2892_1074h(2892_41D0h) */
	IoFHdmitxFcCtrlqlow					fcCtrlqlow;
	/* 2892_1075h(2892_41D4h) */
	kuchar									fcAcp0;
	kuchar	dmyFHdmitx289241d4[3];
	/* 2892_(1076 - 1081h) */
	kuchar	dmyFHdmitx41d84207[0x4208 - 0x41D8];
	/* 2892_1082 - 1091h(2892_4208h - 2892_4244h) */
	IoFHdmitxFcAcp						fcAcp[16];
	/* 2892_1092h(2892_4248h) */
	IoFHdmitxFcIscr10					fcIscr10;
	/* 2892_1093 - 10A2h(2892_424Ch - 2892_4288h) */
	IoFHdmitxFcIscr1						fcIscr1[16];
	/* 2892_10A3 - 10B2h(2892_428Ch - 2892_42C8h) */
	IoFHdmitxFcIscr2						fcIscr2[16];
	/* 2892_10B3h(2892_42CCh) */
	IoFHdmitxFcDatauto0					fcDatauto0;
	/* 2892_10B4h(2892_42D0h) */
	IoFHdmitxFcDatauto1					fcDatauto1;
	/* 2892_10B5h(2892_42D4h) */
	IoFHdmitxFcDatauto2					fcDatauto2;
	/* 2892_10B6h(2892_42D8h) */
	IoFHdmitxFcDatman					fcDatman;
	/* 2892_10B7h(2892_42DCh) */
	IoFHdmitxFcDatauto3					fcDatauto3;
	/* 2892_10B8h(2892_42E0h) */
	IoFHdmitxFcRdrb0						fcRdrb0;
	/* 2892_10B9h(2892_42E4h) */
	IoFHdmitxFcRdrb1						fcRdrb1;
	/* 2892_10BAh(2892_42E8h) */
	IoFHdmitxFcRdrb2						fcRdrb2;
	/* 2892_10BBh(2892_42ECh) */
	IoFHdmitxFcRdrb3						fcRdrb3;
	/* 2892_10BCh(2892_42F0h) */
	IoFHdmitxFcRdrb4						fcRdrb4;
	/* 2892_10BDh(2892_42F4h) */
	IoFHdmitxFcRdrb5						fcRdrb5;
	/* 2892_10BEh(2892_42F8h) */
	IoFHdmitxFcRdrb6						fcRdrb6;
	/* 2892_10BFh(2892_42FCh) */
	IoFHdmitxFcRdrb7						fcRdrb7;
	/* 2892_10C0h(2892_4300h) */
	IoFHdmitxFcRdrb8						fcRdrb8;
	/* 2892_10C1h(2892_4304h) */
	IoFHdmitxFcRdrb9						fcRdrb9;
	/* 2892_10C2h(2892_4308h) */
	IoFHdmitxFcRdrb10					fcRdrb10;
	/* 2892_10C3h(2892_430Ch) */
	IoFHdmitxFcRdrb11					fcRdrb11;
	/* 2892_(10C4 - 10D1h) */
	kuchar	dmyFHdmitx43104347[0x4348 - 0x4310];
	/* 2892_10D2h(2892_4348h) */
	IoFHdmitxIhFcStat0					fcMask0;
	/* 2892_(10D3 - 10D5h) */
	kuchar	dmyFHdmitx434c4357[0x4358 - 0x434C];
	/* 2892_10D6h(2892_4358h) */
	IoFHdmitxIhFcStat1					fcMask1;
	/* 2892_(10D7 - 10D9h) */
	kuchar	dmyFHdmitx435c4367[0x4368 - 0x435C];
	/* 2892_10DAh(2892_4368h) */
	IoFHdmitxIhFcStat2					fcMask2;
	/* 2892_(10DB - 10DFh) */
	kuchar	dmyFHdmitx436c437f[0x4380 - 0x436C];
	/* 2892_10E0h(2892_4380h) */
	IoFHdmitxFcPrconf					fcPrconf;
	/* 2892_10E1h(2892_4384h) */
	IoFHdmitxFcScramblerCtrl			fcScramblerCtrl;
	/* 2892_10E2h(2892_4388h) */
	IoFHdmitxFcMultistreamCtrl			fcMultistreamCtrl;
	/* 2892_10E3h(2892_438Ch) */
	IoFHdmitxFcPacketTxEn				fcPacketTxEn;
	/* 2892_(10E4 - 10E7h) */
	kuchar	dmyFHdmitx4390439f[0x43A0 - 0x4390];
	/* 2892_10E8h(2892_43A0h) */
	IoFHdmitxFcActspcHdlrCfg			fcActspcHdlrCfg;
	/* 2892_10E9h(2892_43A4h) */
	IoFHdmitxFcInvact2d0				fcInvact2d0;
	/* 2892_10EAh(2892_43A8h) */
	IoFHdmitxFcInvact2d1				fcInvact2d1;
	/* 2892_(10EB - 10FFh) */
	kuchar	dmyFHdmitx43ac43ff[0x4400 - 0x43AC];
	/* 2892_1100h(2892_4400h) */
	IoFHdmitxFcGmdStat					fcGmdStat;
	/* 2892_1101h(2892_4404h) */
	IoFHdmitxFcGmdEn					fcGmdEn;
	/* 2892_1102h(2892_4408h) */
	IoFHdmitxFcGmdUp					fcGmdUp;
	/* 2892_1103h(2892_440Ch) */
	IoFHdmitxFcGmdConf					fcGmdConf;
	/* 2892_1104h(2892_4410h) */
	IoFHdmitxFcGmdHb					fcGmdHb;
	/* 2892_1105 - 1120h(2892_4414h - 2892_4480h) */
	IoFHdmitxFcGmdPb					fcGmdPb[28];
	/* 2892_(1121 - 1127h) */
	kuchar	dmyFHdmitx4484449f[0x44A0 - 0x4484];
	/* 2892_1128h(2892_44A0h) */
	kuchar									fcAmpHb1;
	kuchar	dmyFHdmitx289244a0[3];
	/* 2892_1129h(2892_44A4h) */
	kuchar									fcAmpHb2;
	kuchar	dmyFHdmitx289244a4[3];
	/* 2892_112A - 1145h(2892_44A8h - 2892_4514h) */
	IoFHdmitxFcAmpPb						fcAmpPb[28];
	/* 2892_(1146 - 1147h) */
	kuchar	dmyFHdmitx4518451f[0x4520 - 0x4518];
	/* 2892_1148h(2892_4520h) */
	kuchar									fcNvbiHb1;
	kuchar	dmyFHdmitx28924520[3];
	/* 2892_1149h(2892_4524h) */
	kuchar									fcNvbiHb2;
	kuchar	dmyFHdmitx28924524[3];
	/* 2892_114A - 1164h(2892_4528h - 2892_4590h) */
	IoFHdmitxFcNvbiPb					fcNvbiPb[27];
	/* 2892_(1165 - 2FFFh) */
	kuchar	dmyFHdmitx4594Bfff[0xC000 - 0x4594];
	/* 2892_3000h(2892_C000h) */
	IoFHdmitxPhyConf0					phyConf0;
	/* 2892_(3001 - 3003h) */
	kuchar	dmyFHdmitxC004C00f[0xC010 - 0xC004];
	/* 2892_3004h(2892_C010h) */
	IoFHdmitxPhyStat0					phyStat0;
	/* 2892_3005h(2892_C014h) */
	IoFHdmitxPhyStat0					phyInt0;
	/* 2892_3006h(2892_C018h) */
	IoFHdmitxPhyStat0					phyMask0;
	/* 2892_3007h(2892_C01Ch) */
	IoFHdmitxPhyStat0					phyPol0;
	/* 2892_(3008 - 301Fh) */
	kuchar	dmyFHdmitxC020C07f[0xC080 - 0xC020];
	/* 2892_3020h(2892_C080h) */
	IoFHdmitxPhyI2cmSlave				phyI2cmSlave;
	/* 2892_3021h(2892_C084h) */
	kuchar									phyI2cmAddress;
	kuchar	dmyFHdmitx2892C084[3];
	/* 2892_3022h(2892_C088h) */
	kuchar									phyI2cmDatao1;
	kuchar	dmyFHdmitx2892C088[3];
	/* 2892_3023h(2892_C08Ch) */
	kuchar									phyI2cmDatao0;
	kuchar	dmyFHdmitx2892C08c[3];
	/* 2892_3024h(2892_C090h) */
	kuchar									phyI2cmDatai1;
	kuchar	dmyFHdmitx2892C090[3];
	/* 2892_3025h(2892_C094h) */
	kuchar									phyI2cmDatai0;
	kuchar	dmyFHdmitx2892C094[3];
	/* 2892_3026h(2892_C098h) */
	IoFHdmitxPhyI2cmOperation			phyI2cmOperation;
	/* 2892_3027h(2892_C09Ch) */
	IoFHdmitxPhyI2cmInt					phyI2cmInt;
	/* 2892_3028h(2892_C0A0h) */
	IoFHdmitxPhyI2cmCtlint				phyI2cmCtlint;
	/* 2892_3029h(2892_C0A4h) */
	IoFHdmitxPhyI2cmDiv					phyI2cmDiv;
	/* 2892_302Ah(2892_C0A8h) */
	IoFHdmitxPhyI2cmSoftrstz			phyI2cmSoftrstz;
	/* 2892_302Bh(2892_C0ACh) */
	kuchar									phyI2cmSsSclHcnt1Addr;
	kuchar	dmyFHdmitx2892C0ac[3];
	/* 2892_302Ch(2892_C0B0h) */
	kuchar									phyI2cmSsSclHcnt0Addr;
	kuchar	dmyFHdmitx2892C0b0[3];
	/* 2892_302Dh(2892_C0B4h) */
	kuchar									phyI2cmSsSclLcnt1Addr;
	kuchar	dmyFHdmitx2892C0b4[3];
	/* 2892_302Eh(2892_C0B8h) */
	kuchar									phyI2cmSsSclLcnt0Addr;
	kuchar	dmyFHdmitx2892C0b8[3];
	/* 2892_302Fh(2892_C0BCh) */
	kuchar									phyI2cmFsSclHcnt1Addr;
	kuchar	dmyFHdmitx2892C0bc[3];
	/* 2892_3030h(2892_C0C0h) */
	kuchar									phyI2cmFsSclHcnt0Addr;
	kuchar	dmyFHdmitx2892C0c0[3];
	/* 2892_3031h(2892_C0C4h) */
	kuchar									phyI2cmFsSclLcnt1Addr;
	kuchar	dmyFHdmitx2892C0c4[3];
	/* 2892_3032h(2892_C0C8h) */
	kuchar									phyI2cmFsSclLcnt0Addr;
	kuchar	dmyFHdmitx2892C0c8[3];
	/* 2892_3033h(2892_C0CCh) */
	kuchar									phyI2cmSdaHold;
	kuchar	dmyFHdmitx2892C0cc[3];
	/* 2892_(3034 - 30FFh) */
	kuchar	dmyFHdmitxC0d0C3ff[0xC400 - 0xC0D0];
	/* 2892_3100h(2892_C400h) */
	IoFHdmitxAudConf0					audConf0;
	/* 2892_3101h(2892_C404h) */
	IoFHdmitxAudConf1					audConf1;
	/* 2892_3102h(2892_C408h) */
	IoFHdmitxAudInt						audInt;
	/* 2892_3103h(2892_C40Ch) */
	IoFHdmitxAudConf2					audConf2;
	/* 2892_3104h(2892_C410h) */
	IoFHdmitxAudInt1						audInt1;
	/* 2892_(3105 - 31FFh) */
	kuchar	dmyFHdmitxC414C7ff[0xC800 - 0xC414];
	/* 2892_3200h(2892_C800h) */
	kuchar									audN1;
	kuchar	dmyFHdmitx2892C800[3];
	/* 2892_3201h(2892_C804h) */
	kuchar									audN2;
	kuchar	dmyFHdmitx2892C804[3];
	/* 2892_3202h(2892_C808h) */
	IoFHdmitxAudN3						audN3;
	/* 2892_3203h(2892_C80Ch) */
	kuchar									audCts1;
	kuchar	dmyFHdmitx2892C80c[3];
	/* 2892_3204h(2892_C810h) */
	kuchar									audCts2;
	kuchar	dmyFHdmitx2892C810[3];
	/* 2892_3205h(2892_C814h) */
	IoFHdmitxAudCts3						audCts3;
	/* 2892_3206h(2892_C818h) */
	IoFHdmitxAudInputclkfs				audInputclkfs;
	/* 2892_(3207 - 32FFh) */
	kuchar	dmyFHdmitxC81cCbff[0xCC00 - 0xC81C];
	/* 2892_3300h(2892_CC00h) */
	IoFHdmitxAudSpdif0					audSpdif0;
	/* 2892_3301h(2892_CC04h) */
	IoFHdmitxAudSpdif1					audSpdif1;
	/* 2892_3302h(2892_CC08h) */
	IoFHdmitxAudSpdifint					audSpdifint;
	/* 2892_3303h(2892_CC0Ch) */
	IoFHdmitxAudSpdifint1				audSpdifint1;
	/* 2892_(3304 - 4000h) */
	kuchar	dmyFHdmitx2cc1030003[0x30004 - 0x2CC10];
	/* 2892_4001h(2893_0004h) */
	IoFHdmitxMcClkdis					mcClkdis;
	/* 2892_4002h(2893_0008h) */
	IoFHdmitxMcSwrstzreq					mcSwrstzreq;
	/* 2892_4003h(2893_000Ch) */
	kuchar	dmyFHdmitx000c000f[0x0010 - 0x000C];
	/* 2892_4004h(2893_0010h) */
	IoFHdmitxMcFlowctrl					mcFlowctrl;
	/* 2892_4005h(2893_0014h) */
	IoFHdmitxMcPhyrstz					mcPhyrstz;
	/* 2892_4006h(2893_0018h) */
	kuchar	dmyFHdmitx28930018h[4];
	/* 2892_(4007h - 40FFh) */
	kuchar	dmyFHdmitx001c03ff[0x0400 - 0x001C];
	/* 2892_4100h(2893_0400h) */
	IoFHdmitxCscCfg						cscCfg;
	/* 2892_4101h(2893_0404h) */
	IoFHdmitxCscScale					cscScale;
	/* 2892_4102h - 4119h(2893_0408h - 2893_0464h) */
	IoFHdmiCscCoef					cscCoef[3][4];
	/* 2892_411Ah(2893_0468h) */
	kuchar									cscLimitUpMsb;
	kuchar	dmyFHdmitx28930468[3];
	/* 2892_411Bh(2893_046Ch) */
	kuchar									cscLimitUpLsb;
	kuchar	dmyFHdmitx2893046c[3];
	/* 2892_411Ch(2893_0470h) */
	kuchar									cscLimitDnMsb;
	kuchar	dmyFHdmitx28930470[3];
	/* 2892_411Dh(2893_0474h) */
	kuchar									cscLimitDnLsb;
	kuchar	dmyFHdmitx28930474[3];
	/* 2892_(411Eh - 7CFFh) */
	kuchar	dmyFHdmitx0478F3ff[0xF400 - 0x0478];
	/* 2892_7D00h(2893_F400h) */
	IoFHdmitxCecCtrl						cecCtrl;
	/* 2892_7D01h(2893_F404h) */
	kuchar	dmyFHdmitx2893F404h[4];
	/* 2892_7D02h(2893_F408h) */
	IoFHdmitxCecMask						cecMask;
	/* 2892_(7D03h - 7D04h) */
	kuchar	dmyFHdmitxF40cF413[0xF414 - 0xF40C];
	/* 2892_7D05h(2893_F414h) */
	IoFHdmitxCecAddrL					cecAddrL;
	/* 2892_7D06h(2893_F418h) */
	IoFHdmitxCecAddrH					cecAddrH;
	/* 2892_7D07h(2893_F41Ch) */
	IoFHdmitxCecTxCnt					cecTxCnt;
	/* 2892_7D08h(2893_F420h) */
	IoFHdmitxCecRxCnt					cecRxCnt;
	/* 2892_(7D09h - 7D0Fh) */
	kuchar	dmyFHdmitxF424F43f[0xF440 - 0xF424];
	/* 2892_7D10h - 7D1Fh(2893_F440h - 2893_F47Ch) */
	IoFHdmitxCecTxData					cecTxData[16];
	/* 2892_7D20h - 7D2Fh(2893_F480h - 2893_F4BCh) */
	IoFHdmitxCecRxData					cecRxData[16];
	/* 2892_7D30h(2893_F4C0h) */
	IoFHdmitxCecLock						cecLock;
	/* 2892_7D31h(2893_F4C4h) */
	IoFHdmitxCecWakeupctrl				cecWakeupctrl;
	/* 2892_(7D32h - 7DFFh) */
	kuchar	dmyFHdmitxF4c8F7ff[0xF800 - 0xF4C8];
	/* 2892_7E00h(2893_F800h) */
	IoFHdmitxI2cmSlave					i2cmSlave;
	/* 2892_7E01h(2893_F804h) */
	kuchar									i2cmAddress;
	kuchar	dmyFHdmitx2893F804[3];
	/* 2892_7E02h(2893_F808h) */
	kuchar									i2cmDatao;
	kuchar	dmyFHdmitx2893F808[3];
	/* 2892_7E03h(2893_F80Ch) */
	kuchar									i2cmDatai;
	kuchar	dmyFHdmitx2893F80c[3];
	/* 2892_7E04h(2893_F810h) */
	IoFHdmitxI2cmOperation				i2cmOperation;
	/* 2892_7E05h(2893_F814h) */
	IoFHdmitxI2cmInt						i2cmInt;
	/* 2892_7E06h(2893_F818h) */
	IoFHdmitxI2cmCtlint					i2cmCtlint;
	/* 2892_7E07h(2893_F81Ch) */
	IoFHdmitxI2cmDiv						i2cmDiv;
	/* 2892_7E08h(2893_F820h) */
	IoFHdmitxI2cmSegaddr					i2cmSegaddr;
	/* 2892_7E09h(2893_F824h) */
	IoFHdmitxI2cmSoftrstz				i2cmSoftrstz;
	/* 2892_7E0Ah(2893_F828h) */
	kuchar									i2cmSegptr;
	kuchar	dmyFHdmitx2893F828[3];
	/* 2892_7E0Bh(2893_F82Ch) */
	kuchar									i2cmSsSclHcnt1Addr;
	kuchar	dmyFHdmitx2893F82c[3];
	/* 2892_7E0Ch(2893_F830h) */
	kuchar									i2cmSsSclHcnt0Addr;
	kuchar	dmyFHdmitx2893F830[3];
	/* 2892_7E0Dh(2893_F834h) */
	kuchar									i2cmSsSclLcnt1Addr;
	kuchar	dmyFHdmitx2893F834[3];
	/* 2892_7E0Eh(2893_F838h) */
	kuchar									i2cmSsSclLcnt0Addr;
	kuchar	dmyFHdmitx2893F838[3];
	/* 2892_7E0Fh(2893_F83Ch) */
	kuchar									i2cmFsSclHcnt1Addr;
	kuchar	dmyFHdmitx2893F83c[3];
	/* 2892_7E10h(2893_F840h) */
	kuchar									i2cmFsSclHcnt0Addr;
	kuchar	dmyFHdmitx2893F840[3];
	/* 2892_7E11h(2893_F844h) */
	kuchar									i2cmFsSclLcnt1Addr;
	kuchar	dmyFHdmitx2893F844[3];
	/* 2892_7E12h(2893_F848h) */
	kuchar									i2cmFsSclLcnt0Addr;
	kuchar	dmyFHdmitx2893F848[3];
	/* 2892_7E13h(2893_F84Ch) */
	kuchar									i2cmSdaHold;
	kuchar	dmyFHdmitx2893F84c[3];
	/* 2892_7E14h(2893_F850h) */
	IoFHdmitxI2cmScdcReadUpdate		i2cmScdcReadUpdate;
	/* 2892_(7E15h - 7E1Fh) */
	kuchar	dmyFHdmitxF854F87f[0xF880 - 0xF854];
	/* 2892_7E20h - 7E27h(2893_F880h - 2893_F89Ch) */
	IoFHdmitxI2cmReadBuff				i2cmReadBuff[8];
	/* 2892_(7E28h - 7E2Fh) */
	kuchar	dmyFHdmitxF8a0F8bf[0xF8C0 - 0xF8A0];
	/* 2892_7E30h - 7E31h(2893_F8C0h - 2893_F8C4h) */
	IoFHdmitxI2cmScdcUpdate				i2cmScdcUpdate[2];
	/* 2892_7E32 - 2893_FFFFh(2893_F8C8h - 2896_FFFCh) */
    kuchar	dmy2893f8c82896fffc[0x28970000-0x2893F8C8];
};

struct  _FHdmitx2p0Lp3
{
	KObject parent;
};


KConstType					f_hdmitx2p0_lp3_get_type(void);
FHdmitx2p0Lp3*		f_hdmitx2p0_lp3_new(void);


#endif/*__F_HDMITX2P0_LP3_H__*/
