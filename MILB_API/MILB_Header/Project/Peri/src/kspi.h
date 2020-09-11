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

#define K_TYPE_SPI				(k_spi_get_type())
#define K_SPI(obj)				(K_TYPE_CHECK_INSTANCE_CAST((obj), KSpi))
#define K_IS_SPI(obj)			(K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_SPI))

typedef struct _KSpi KSpi;
typedef struct _KSpiPrivate KSpiPrivate;

struct _KSpi
{
	KObject parent;
};

/*	structure of div	*/
typedef union _IoSpiDiv
{
	unsigned long word;
	struct
	{
		unsigned long divisor :8;
		unsigned long :24;
	} bit;
} IoSpiDiv;

/*	structure of ctrl	*/
typedef union _IoSpiCtrl
{
	unsigned long word;
	struct
	{
		unsigned long contxfer :1;
		unsigned long divenable :1;
		unsigned long msb1st :1;
		unsigned long cpha :1;
		unsigned long cpol :1;
		unsigned long master :1;
		unsigned long :4;
		unsigned long dma :1;
		unsigned long mwaiten :1;
		unsigned long :20;
	} bit;
} IoSpiCtrl;

/*	structure of auxCtrl	*/
typedef union _IoSpiAuxctrl
{
	unsigned long word;
	struct
	{
		unsigned long spimode :2;
		unsigned long :1;
		unsigned long inhibitdin :1;
		unsigned long xferformat :2;
		unsigned long :1;
		unsigned long contxferextend :1;
		unsigned long bitsize :5;
		unsigned long :19;
	} bit;
} IoSpiAuxctrl;

/*	structure of st	*/
typedef union _IoSpiSt
{
	unsigned long word;
	struct
	{
		unsigned long xferip :1;
		unsigned long :1;
		unsigned long txempty :1;
		unsigned long txwmark :1;
		unsigned long txfull :1;
		unsigned long rxempty :1;
		unsigned long rxwmark :1;
		unsigned long rxfull :1;
		unsigned long rxoverflow :1;
		unsigned long rxtimeout :1;
		unsigned long :22;
	} bit;
} IoSpiSt;

/*	structure of slvSel	*/
typedef union _IoSpiSlvsel
{
	unsigned long word;
	struct
	{
		unsigned long ssout0 :1;
		unsigned long ssout1 :1;
		unsigned long ssout2 :1;
		unsigned long ssout3 :1;
		unsigned long :28;
	} bit;
} IoSpiSlvsel;

/*	structure of slvPol	*/
typedef union _IoSpiSlvpol
{
	unsigned long word;
	struct
	{
		unsigned long sspol0 :1;
		unsigned long sspol1 :1;
		unsigned long sspol2 :1;
		unsigned long sspol3 :1;
		unsigned long :28;
	} bit;
} IoSpiSlvpol;

/*	structure of intEn	*/
typedef union _IoSpiInten
{
	unsigned long word;
	struct
	{
		unsigned long txemptypulse :1;
		unsigned long txwmarkpulse :1;
		unsigned long rxwmarkpulse :1;
		unsigned long rxfullpulse :1;
		unsigned long xferdonepulse :1;
		unsigned long :2;
		unsigned long rxfifooverflow :1;
		unsigned long rxtimeout :1;
		unsigned long :23;
	} bit;
} IoSpiInten;

/*	structure of intSt	*/
typedef union _IoSpiIntst
{
	unsigned long word;
	struct
	{
		unsigned long txemptypulse :1;
		unsigned long txwmarkpulse :1;
		unsigned long rxwmarkpulse :1;
		unsigned long rxfullpulse :1;
		unsigned long xferdonepulse :1;
		unsigned long :2;
		unsigned long rxfifooverflow :1;
		unsigned long rxtimeout :1;
		unsigned long :23;
	} bit;
} IoSpiIntst;

/*	structure of intClr	*/
typedef union _IoSpiIntclr
{
	unsigned long word;
	struct
	{
		unsigned long __txemptypulse :1;
		unsigned long __txwmarkpulse :1;
		unsigned long __rxwmarkpulse :1;
		unsigned long __rxfullpulse :1;
		unsigned long __xferdonepulse :1;
		unsigned long :2;
		unsigned long __rxfifooverflow :1;
		unsigned long __rxtimeout :1;
		unsigned long :23;
	} bit;
} IoSpiIntclr;

/*	structure of txfifo	*/
typedef union _IoSpiTxfifo
{
	unsigned long word;
	struct
	{
		unsigned long txFifoLevel :8;
		unsigned long :24;
	} bit;
} IoSpiTxfifo;

/*	structure of rxfifo	*/
typedef union _IoSpiRxfifo
{
	unsigned long word;
	struct
	{
		unsigned long rxFifoLevel :8;
		unsigned long :24;
	} bit;
} IoSpiRxfifo;

/*	structure of dmaTo	*/
typedef union _IoSpiDmato
{
	unsigned long word;
	struct
	{
		unsigned long timeout :24;
		unsigned long :8;
	} bit;
} IoSpiDmato;

/*	structure of msDly	*/
typedef union _IoSpiMsdly
{
	unsigned long word;
	struct
	{
		unsigned long mwait :8;
		unsigned long :24;
	} bit;
} IoSpiMsdly;

/*	structure of en	*/
typedef union _IoSpiEn
{
	unsigned long word;
	struct
	{
		unsigned long __enablereq :1;
		unsigned long __extensel :3;
		unsigned long :28;
	} bit;
} IoSpiEn;

/*	structure of fifoDpth	*/
typedef union _IoSpiFifodpth
{
	unsigned long word;
	struct
	{
		unsigned long fifodepth :9;
		unsigned long :23;
	} bit;
} IoSpiFifodpth;

/*	structure of fifoWmk	*/
typedef union _IoSpiFifowmk
{
	unsigned long word;
	struct
	{
		unsigned long rxwmarkset :8;
		unsigned long txwmarkset :8;
		unsigned long :16;
	} bit;
} IoSpiFifowmk;

/*	structure of txDwr	*/
typedef union _IoSpiTxdwr
{
	unsigned long word;
	struct
	{
		unsigned long txdummywr :8;
		unsigned long :24;
	} bit;
} IoSpiTxdwr;

/* Define I/O Mapping SPI */
/* SPI ch0	(1E80_(0000 - 00FFh)*/
/* SPI ch1	(1E80_(0100 - 01FFh)*/
/* SPI ch2	(1E80_(0200 - 02FFh)*/
typedef struct _IoSpi
{
	unsigned long txdata; /* 1E80_(0000 - 0003h)	*/
	unsigned long rxdata; /* 1E80_(0004 - 0007h)	*/
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
	unsigned char dmy1e8000401e800047[0x1E800048 - 0x1E800040]; /* 1E80_(0040 - 0047h)	*/
	IoSpiFifodpth fifoDpth; /* 1E80_(0048 - 004Bh)	*/
	IoSpiFifowmk fifoWmk; /* 1E80_(004C - 004Fh)	*/
	IoSpiTxdwr txDwr; /* 1E80_(0050 - 0053h)	*/
	unsigned char dmy1e8000541e8000ff[0x1E800100 - 0x1E800054]; /* 1E80_(0054 - 00FFh)	*/
} IoSpi;

extern volatile IoSpi ioSpi[3]; /* addr 1E800000h-	*/

KConstType 		k_spi_get_type(void);
KSpi* 					k_spi_new(void);

#endif/*__K_SPI_H__*/

