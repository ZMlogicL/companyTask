/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-05
 *@author            :陈倩
 *@brief             :kspi
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *3、
 *4、
 *5、
 *@version
 *
 */

#ifndef __K_SPI_H__
#define __K_SPI_H__

#include <klib.h>

#define K_TYPE_SPI					(k_spi_get_type())
#define K_SPI(obj)					(K_TYPE_CHECK_INSTANCE_CAST((obj), KSpi))
#define K_IS_SPI(obj)				(K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_SPI))

typedef struct _KSpi 				KSpi;
typedef struct _KSpiPrivate 	KSpiPrivate;

struct _KSpi
{
	KObject parent;
};

/*	structure of div	*/
typedef union _IoSpiDiv
{
	kulong word;
	struct
	{
		kulong divisor :8;
		kulong :24;
	} bit;
} IoSpiDiv;

/*	structure of ctrl	*/
typedef union _IoSpiCtrl
{
	kulong word;
	struct
	{
		kulong contxfer :1;
		kulong divenable :1;
		kulong msb1st :1;
		kulong cpha :1;
		kulong cpol :1;
		kulong master :1;
		kulong :4;
		kulong dma :1;
		kulong mwaiten :1;
		kulong :20;
	} bit;
} IoSpiCtrl;

/*	structure of auxCtrl	*/
typedef union _IoSpiAuxctrl
{
	kulong word;
	struct
	{
		kulong spimode :2;
		kulong :1;
		kulong inhibitdin :1;
		kulong xferformat :2;
		kulong :1;
		kulong contxferextend :1;
		kulong bitsize :5;
		kulong :19;
	} bit;
} IoSpiAuxctrl;

/*	structure of st	*/
typedef union _IoSpiSt
{
	kulong word;
	struct
	{
		kulong xferip :1;
		kulong :1;
		kulong txempty :1;
		kulong txwmark :1;
		kulong txfull :1;
		kulong rxempty :1;
		kulong rxwmark :1;
		kulong rxfull :1;
		kulong rxoverflow :1;
		kulong rxtimeout :1;
		kulong :22;
	} bit;
} IoSpiSt;

/*	structure of slvSel	*/
typedef union _IoSpiSlvsel
{
	kulong word;
	struct
	{
		kulong ssout0 :1;
		kulong ssout1 :1;
		kulong ssout2 :1;
		kulong ssout3 :1;
		kulong :28;
	} bit;
} IoSpiSlvsel;

/*	structure of slvPol	*/
typedef union _IoSpiSlvpol
{
	kulong word;
	struct
	{
		kulong sspol0 :1;
		kulong sspol1 :1;
		kulong sspol2 :1;
		kulong sspol3 :1;
		kulong :28;
	} bit;
} IoSpiSlvpol;

/*	structure of intEn	*/
typedef union _IoSpiInten
{
	kulong word;
	struct
	{
		kulong txemptypulse :1;
		kulong txwmarkpulse :1;
		kulong rxwmarkpulse :1;
		kulong rxfullpulse :1;
		kulong xferdonepulse :1;
		kulong :2;
		kulong rxfifooverflow :1;
		kulong rxtimeout :1;
		kulong :23;
	} bit;
} IoSpiInten;

/*	structure of intSt	*/
typedef union _IoSpiIntst
{
	kulong word;
	struct
	{
		kulong txemptypulse :1;
		kulong txwmarkpulse :1;
		kulong rxwmarkpulse :1;
		kulong rxfullpulse :1;
		kulong xferdonepulse :1;
		kulong :2;
		kulong rxfifooverflow :1;
		kulong rxtimeout :1;
		kulong :23;
	} bit;
} IoSpiIntst;

/*	structure of intClr	*/
typedef union _IoSpiIntclr
{
	kulong word;
	struct
	{
		kulong __txemptypulse :1;
		kulong __txwmarkpulse :1;
		kulong __rxwmarkpulse :1;
		kulong __rxfullpulse :1;
		kulong __xferdonepulse :1;
		kulong :2;
		kulong __rxfifooverflow :1;
		kulong __rxtimeout :1;
		kulong :23;
	} bit;
} IoSpiIntclr;

/*	structure of txfifo	*/
typedef union _IoSpiTxfifo
{
	kulong word;
	struct
	{
		kulong txFifoLevel :8;
		kulong :24;
	} bit;
} IoSpiTxfifo;

/*	structure of rxfifo	*/
typedef union _IoSpiRxfifo
{
	kulong word;
	struct
	{
		kulong rxFifoLevel :8;
		kulong :24;
	} bit;
} IoSpiRxfifo;

/*	structure of dmaTo	*/
typedef union _IoSpiDmato
{
	kulong word;
	struct
	{
		kulong timeout :24;
		kulong :8;
	} bit;
} IoSpiDmato;

/*	structure of msDly	*/
typedef union _IoSpiMsdly
{
	kulong word;
	struct
	{
		kulong mwait :8;
		kulong :24;
	} bit;
} IoSpiMsdly;

/*	structure of en	*/
typedef union _IoSpiEn
{
	kulong word;
	struct
	{
		kulong __enablereq :1;
		kulong __extensel :3;
		kulong :28;
	} bit;
} IoSpiEn;

/*	structure of fifoDpth	*/
typedef union _IoSpiFifodpth
{
	kulong word;
	struct
	{
		kulong fifodepth :9;
		kulong :23;
	} bit;
} IoSpiFifodpth;

/*	structure of fifoWmk	*/
typedef union _IoSpiFifowmk
{
	kulong word;
	struct
	{
		kulong rxwmarkset :8;
		kulong txwmarkset :8;
		kulong :16;
	} bit;
} IoSpiFifowmk;

/*	structure of txDwr	*/
typedef union _IoSpiTxdwr
{
	kulong word;
	struct
	{
		kulong txdummywr :8;
		kulong :24;
	} bit;
} IoSpiTxdwr;

/* Define I/O Mapping spi */
/* spi ch0	(1E80_(0000 - 00FFh)*/
/* spi ch1	(1E80_(0100 - 01FFh)*/
/* spi ch2	(1E80_(0200 - 02FFh)*/
typedef struct _IoSpi
{
	kulong txdata; /* 1E80_(0000 - 0003h)	*/
	kulong rxdata; /* 1E80_(0004 - 0007h)	*/
	IoSpiDiv div; /* 1E80_(0008 - 000Bh)	*/
	IoSpiCtrl ctrl; /* 1E80_(000C - 000Fh)	*/
	IoSpiAuxctrl auxCtrl; /* 1E80_(0010 - 0013h)	*/
	IoSpiSt st; /* 1E80_(0014 - 0017h)	*/
	IoSpiSlvsel slvSel; /* 1E80_(0018 - 001Bh)	*/
	IoSpiSlvpol slvPol; /* 1E80_(001C - 001Fh)	*/
	IoSpiInten intEn; /* 1E80_(0020 - 0023h)	*/
	IoSpiIntst intSt; /* 1E80_(0024 - 0027h)	*/
	IoSpiIntclr intClr; /* 1E80_(0028 - 002Bh)	*/
	IoSpiTxfifo txfifo; /* 1E80_(002C - 002Fh)	*/
	IoSpiRxfifo rxfifo; /* 1E80_(0030 - 0033h)	*/
	IoSpiDmato dmaTo; /* 1E80_(0034 - 0037h)	*/
	IoSpiMsdly msDly; /* 1E80_(0038 - 003Bh)	*/
	IoSpiEn en; /* 1E80_(003C - 003Fh)	*/
	kuchar dmy1e8000401e800047[0x1E800048 - 0x1E800040]; /* 1E80_(0040 - 0047h)	*/
	IoSpiFifodpth fifoDpth; /* 1E80_(0048 - 004Bh)	*/
	IoSpiFifowmk fifoWmk; /* 1E80_(004C - 004Fh)	*/
	IoSpiTxdwr txDwr; /* 1E80_(0050 - 0053h)	*/
	kuchar dmy1e8000541e8000ff[0x1E800100 - 0x1E800054]; /* 1E80_(0054 - 00FFh)	*/
} IoSpi;

extern volatile IoSpi ioSpi[3]; /* addr 1E800000h-	*/

KConstType 		k_spi_get_type(void);
KSpi* 					k_spi_new(void);

#endif/*__K_SPI_H__*/

