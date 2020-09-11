/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-08
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


#ifndef __JCTPMC_SPI_H__
#define __JCTPMC_SPI_H__


#include <klib.h>


#define JCTPMC_TYPE_SPI		(jctpmc_spi_get_type())
#define JCTPMC_SPI(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, JctpmcSpi))
#define JCTPMC_IS_SPI(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, JCTPMC_TYPE_SPI))


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
typedef struct 				_JctpmcSpi JctpmcSpi;
typedef struct 				_JctpmcSpiPrivate JctpmcSpiPrivate;

/* QSPI */

/* DIV */
union _IoPmcSpiDiv {
	kulong		word;
	struct {
		kulong	divisor			:8;
		kulong					:24;
	}bit;
};

/* CTRL */
union _IoPmcSpiCtrl {
	kulong		word;
	struct {
		kulong	contxfer		:1;
		kulong	divenable		:1;
		kulong	msb1st			:1;
		kulong	cpha			:1;
		kulong	cpol			:1;
		kulong	master			:1;
		kulong					:4;
		kulong	dma				:1;
		kulong	mwaiten			:1;
		kulong					:20;
	}bit;
};

/* AUX_CTRL */
union _IoPmcSpiAuxCtrl {
	kulong		word;
	struct {
		kulong	spimode			:2;
		kulong					:1;
		kulong	inhibitdin		:1;
		kulong	xferformat		:2;
		kulong					:1;
		kulong	contxferextend	:1;
		kulong	bitsize			:5;
		kulong					:19;
	}bit;
};

/* ST */
union _IoPmcSpiSt {
	kulong		word;
	struct {
		kulong	xferip			:1;
		kulong				 	:1;
		kulong	txempty			:1;
		kulong	txwmark			:1;
		kulong	txfull			:1;
		kulong	rxempty			:1;
		kulong	rxwmark			:1;
		kulong	rxfull			:1;
		kulong	rxoverflow		:1;
		kulong	rxtimeout		:1;
		kulong					:22;
	}bit;
};

/* SLV_SEL */
union _IoPmcSpiSlvSel {
	kulong		word;
	struct {
		kulong	ssout			:1;
		kulong					:31;
	}bit;
};

/* SLV_POL */
union _IoPmcSpiSlvPol {
	kulong		word;
	struct {
		kulong	sspol			:1;
		kulong					:31;
	}bit;
};

/* INT_EN */
union _IoPmcSpiIntEn {
	kulong		word;
	struct {
		kulong	txemptypulse	:1;
		kulong	txwmarkpulse	:1;
		kulong	rxwmarkpulse	:1;
		kulong	rxfullpulse		:1;
		kulong	xferdonepulse	:1;
		kulong					:2;
		kulong	rxfifooverflow	:1;
		kulong	rxtimeout		:1;
		kulong					:23;
	}bit;
};

/* INT_ST */
union _IoPmcSpiIntSt {
	kulong		word;
	struct {
		kulong	txemptypulse	:1;
		kulong	txwmarkpulse	:1;
		kulong	rxwmarkpulse	:1;
		kulong	rxfullpulse		:1;
		kulong	xferdonepulse	:1;
		kulong					:2;
		kulong	rxfifooverflow	:1;
		kulong	rxtimeout		:1;
		kulong					:23;
	}bit;
};

/* INT_CLR */
union _IoPmcSpiIntClr {
	kulong		word;
	struct {
		kulong	txemptypulseTemp2		:1;
		kulong	txwmarkpulseTemp2		:1;
		kulong	rxwmarkpulseTemp2		:1;
		kulong	rxfullpulseTemp2		:1;
		kulong	xferdonepulseTemp2		:1;
		kulong						:2;
		kulong	rxfifooverflowTemp2	:1;
		kulong	rxtimeoutTemp2			:1;
		kulong						:23;
	}bit;
};

/* TXFIFO */
union _IoPmcSpiTxfifo {
	kulong		word;
	struct {
		kulong	txFifoLevel	:7;
		kulong					:25;
	}bit;
};

/* RXFIFO */
union _IoPmcSpiRxfifo {
	kulong		word;
	struct {
		kulong	rxFifoLevel	:7;
		kulong					:25;
	}bit;
};

/* DMA_TO */
union _IoPmcSpiDmaTo {
	kulong		word;
	struct {
		kulong	timeout			:24;
		kulong					:8;
	}bit;
};

/* MS_DLY */
union _IoPmcSpiMsDly {
	kulong		word;
	struct {
		kulong	mwait			:8;
		kulong					:24;
	}bit;
};

/* EN */
union _IoPmcSpiEn {
	kulong		word;
	struct {
		kulong	enablereqTemp2		:1;
		kulong	extenselTemp2		:3;
		kulong					:28;
	}bit;
};

/* FIFO_DPTH */
union _IoPmcSpiFifoDpth {
	kulong		word;
	struct {
		kulong	fifodepth		:9;
		kulong					:23;
	}bit;
};

/* FIFO_WMK */
union _IoPmcSpiFifoWmk {
	kulong		word;
	struct {
		kulong	rxwmarkset		:8;
		kulong	txwmarkset		:8;
		kulong					:16;
	}bit;
};

/* TX_DWR */
union _IoPmcSpiTxDwr {
	kulong		word;
	struct {
		kulong	txdummywr		:8;
		kulong					:24;
	}bit;
};

/* QSPI */
struct _IoPmcSpi {
	/* 1DD0_(0000 - 0003h)	*/
	kulong					txdata;
	/* 1DD0_(0004 - 0007h)	*/
	kulong					rxdata;
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
	kuchar					dmyPmcSpi040047[0x048 - 0x040];
	/* 1DD0_(0048 - 004Bh)	*/
	IoPmcSpiFifoDpth	fifoDpth;
	/* 1DD0_(004C - 004Fh)	*/
	IoPmcSpiFifoWmk		fifoWmk;
	/* 1DD0_(0050 - 0053h)	*/
	IoPmcSpiTxDwr		txDwr;
	/* 1DD0_0054 - 1DDF_FFFFh)	*/
	kuchar					dmyPmcSpi00054Fffff[0x100000 - 0x054];
};

struct _JctpmcSpi {
	KObject parent;
};


KConstType 			jctpmc_spi_get_type(void);
JctpmcSpi*		        jctpmc_spi_new(void);


#endif /* __JCTPMC_SPI_H__ */
