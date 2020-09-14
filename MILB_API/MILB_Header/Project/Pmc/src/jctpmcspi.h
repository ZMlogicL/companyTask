/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-08
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


#ifndef __JCTPMC_SPI_H__
#define __JCTPMC_SPI_H__


#include <stdio.h>
#include <glib-object.h>


typedef union 				_IoPmcSpiDiv IoPmcSpiDiv;
typedef union 				_IoPmcSpiCtrl IoPmcSpiCtrl;
typedef union 				_IoPmcSpiAuxCtrl IoPmcSpiAuxCtrl;
typedef union 				_IoPmcSpiSt IoPmcSpiSt;
typedef union 				_IoPmcSpiSlvSel IoPmcSpiSlvSel;
typedef union 				_IoPmcSpiSlvPol IoPmcSpiSlvPol;
typedef union 				_IoPmcSpiIntEn IoPmcSpiIntEn;
typedef union 				_IoPmcSpiIntSt IoPmcSpiIntSt;
typedef union 				_IoPmcSpiIntClr IoPmcSpiIntClr;
typedef union 				_IoPmcSpiTxfifo IoPmcSpiTxfifo;
typedef union 				_IoPmcSpiRxfifo IoPmcSpiRxfifo;
typedef union 				_IoPmcSpiDmaTo IoPmcSpiDmaTo;
typedef union 				_IoPmcSpiMsDly IoPmcSpiMsDly;
typedef union 				_IoPmcSpiEn IoPmcSpiEn;
typedef union 				_IoPmcSpiFifoDpth IoPmcSpiFifoDpth;
typedef union 				_IoPmcSpiFifoWmk IoPmcSpiFifoWmk;
typedef union 				_IoPmcSpiTxDwr IoPmcSpiTxDwr;
typedef struct 				_IoPmcSpi IoPmcSpi;

/* QSPI */

/* DIV */
union _IoPmcSpiDiv {
	gulong		word;
	struct {
		gulong	divisor			:8;
		gulong					:24;
	}bit;
};

/* CTRL */
union _IoPmcSpiCtrl {
	gulong		word;
	struct {
		gulong	contxfer		:1;
		gulong	divenable		:1;
		gulong	msb1st			:1;
		gulong	cpha			:1;
		gulong	cpol			:1;
		gulong	master			:1;
		gulong					:4;
		gulong	dma				:1;
		gulong	mwaiten			:1;
		gulong					:20;
	}bit;
};

/* AUX_CTRL */
union _IoPmcSpiAuxCtrl {
	gulong		word;
	struct {
		gulong	spimode			:2;
		gulong					:1;
		gulong	inhibitdin		:1;
		gulong	xferformat		:2;
		gulong					:1;
		gulong	contxferextend	:1;
		gulong	bitsize			:5;
		gulong					:19;
	}bit;
};

/* ST */
union _IoPmcSpiSt {
	gulong		word;
	struct {
		gulong	xferip			:1;
		gulong				 	:1;
		gulong	txempty			:1;
		gulong	txwmark			:1;
		gulong	txfull			:1;
		gulong	rxempty			:1;
		gulong	rxwmark			:1;
		gulong	rxfull			:1;
		gulong	rxoverflow		:1;
		gulong	rxtimeout		:1;
		gulong					:22;
	}bit;
};

/* SLV_SEL */
union _IoPmcSpiSlvSel {
	gulong		word;
	struct {
		gulong	ssout			:1;
		gulong					:31;
	}bit;
};

/* SLV_POL */
union _IoPmcSpiSlvPol {
	gulong		word;
	struct {
		gulong	sspol			:1;
		gulong					:31;
	}bit;
};

/* INT_EN */
union _IoPmcSpiIntEn {
	gulong		word;
	struct {
		gulong	txemptypulse	:1;
		gulong	txwmarkpulse	:1;
		gulong	rxwmarkpulse	:1;
		gulong	rxfullpulse		:1;
		gulong	xferdonepulse	:1;
		gulong					:2;
		gulong	rxfifooverflow	:1;
		gulong	rxtimeout		:1;
		gulong					:23;
	}bit;
};

/* INT_ST */
union _IoPmcSpiIntSt {
	gulong		word;
	struct {
		gulong	txemptypulse	:1;
		gulong	txwmarkpulse	:1;
		gulong	rxwmarkpulse	:1;
		gulong	rxfullpulse		:1;
		gulong	xferdonepulse	:1;
		gulong					:2;
		gulong	rxfifooverflow	:1;
		gulong	rxtimeout		:1;
		gulong					:23;
	}bit;
};

/* INT_CLR */
union _IoPmcSpiIntClr {
	gulong		word;
	struct {
		gulong	txemptypulseTemp2		:1;
		gulong	txwmarkpulseTemp2		:1;
		gulong	rxwmarkpulseTemp2		:1;
		gulong	rxfullpulseTemp2		:1;
		gulong	xferdonepulseTemp2		:1;
		gulong						:2;
		gulong	rxfifooverflowTemp2	:1;
		gulong	rxtimeoutTemp2			:1;
		gulong						:23;
	}bit;
};

/* TXFIFO */
union _IoPmcSpiTxfifo {
	gulong		word;
	struct {
		gulong	txFifoLevel	:7;
		gulong					:25;
	}bit;
};

/* RXFIFO */
union _IoPmcSpiRxfifo {
	gulong		word;
	struct {
		gulong	rxFifoLevel	:7;
		gulong					:25;
	}bit;
};

/* DMA_TO */
union _IoPmcSpiDmaTo {
	gulong		word;
	struct {
		gulong	timeout			:24;
		gulong					:8;
	}bit;
};

/* MS_DLY */
union _IoPmcSpiMsDly {
	gulong		word;
	struct {
		gulong	mwait			:8;
		gulong					:24;
	}bit;
};

/* EN */
union _IoPmcSpiEn {
	gulong		word;
	struct {
		gulong	enablereqTemp2		:1;
		gulong	extenselTemp2		:3;
		gulong					:28;
	}bit;
};

/* FIFO_DPTH */
union _IoPmcSpiFifoDpth {
	gulong		word;
	struct {
		gulong	fifodepth		:9;
		gulong					:23;
	}bit;
};

/* FIFO_WMK */
union _IoPmcSpiFifoWmk {
	gulong		word;
	struct {
		gulong	rxwmarkset		:8;
		gulong	txwmarkset		:8;
		gulong					:16;
	}bit;
};

/* TX_DWR */
union _IoPmcSpiTxDwr {
	gulong		word;
	struct {
		gulong	txdummywr		:8;
		gulong					:24;
	}bit;
};

/* QSPI */
struct _IoPmcSpi {
	/* 1DD0_(0000 - 0003h)	*/
	gulong					txdata;
	/* 1DD0_(0004 - 0007h)	*/
	gulong					rxdata;
	/* 1DD0_(0008 - 000Bh)	*/
	IoPmcSpiDiv			div;
	/* 1DD0_(000C - 000Fh)	*/
	IoPmcSpiCtrl			ctrl;
	/* 1DD0_(0010 - 0013h)	*/
	IoPmcSpiAuxCtrl		auxCtrl;
	/* 1DD0_(0014 - 0017h)	*/
	IoPmcSpiSt			st;
	/* 1DD0_(0018 - 001Bh)	*/
	IoPmcSpiSlvSel		slvSel;
	/* 1DD0_(001C - 001Fh)	*/
	IoPmcSpiSlvPol		slvPol;
	/* 1DD0_(0020 - 0023h)	*/
	IoPmcSpiIntEn		intEn;
	/* 1DD0_(0024 - 0027h)	*/
	IoPmcSpiIntSt		intSt;
	/* 1DD0_(0028 - 002Bh)	*/
	IoPmcSpiIntClr		intClr;
	/* 1DD0_(002C - 002Fh)	*/
	IoPmcSpiTxfifo		txfifo;
	/* 1DD0_(0030 - 0033h)	*/
	IoPmcSpiRxfifo		rxfifo;
	/* 1DD0_(0034 - 0037h)	*/
	IoPmcSpiDmaTo		dmaTo;
	/* 1DD0_(0038 - 003Bh)	*/
	IoPmcSpiMsDly		msDly;
	/* 1DD0_(003C - 003Fh)	*/
	IoPmcSpiEn			en;
	/* 1DD0_(0040 - 0047h)	*/
	guchar					dmyPmcSpi040047[0x048 - 0x040];
	/* 1DD0_(0048 - 004Bh)	*/
	IoPmcSpiFifoDpth	fifoDpth;
	/* 1DD0_(004C - 004Fh)	*/
	IoPmcSpiFifoWmk		fifoWmk;
	/* 1DD0_(0050 - 0053h)	*/
	IoPmcSpiTxDwr		txDwr;
	/* 1DD0_0054 - 1DDF_FFFFh)	*/
	guchar					dmyPmcSpi00054Fffff[0x100000 - 0x054];
};


#endif /* __JCTPMC_SPI_H__ */
