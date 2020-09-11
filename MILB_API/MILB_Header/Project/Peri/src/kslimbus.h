/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-05
 *@author            :陈倩
 *@brief             :kslimbus
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

#ifndef __K_SLIMBUS_H__
#define __K_SLIMBUS_H__

#include <klib.h>

#define K_TYPE_SLIMBUS			(k_slimbus_get_type())
#define K_SLIMBUS(obj)				(K_TYPE_CHECK_INSTANCE_CAST((obj), KSlimbus))
#define K_IS_SLIMBUS(obj)			(K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_SLIMBUS))

typedef struct _KSlimbus KSlimbus;
typedef struct _KSlimbusPrivate KSlimbusPrivate;

struct _KSlimbus
{
	KObject parent;
};

/* structure of configMode				(Base_0000h) */
typedef union _IoSlimbusMode
{
	unsigned long word;
	struct
	{
		unsigned long enable :1;
		unsigned long managerMode :1;
		unsigned long snifferMode :1;
		unsigned long frEn :1;
		unsigned long devEn :1;
		unsigned long goAbsent :1;
		unsigned long :2;
		unsigned long retryLmt :4;
		unsigned long reportAtEvent :1;
		unsigned long crcCalcDisable :1;
		unsigned long lmtdReport :1;
		unsigned long reconfTxDis :1;
		unsigned long :16;
	} bit;
} IoSlimbusMode;

/* structure of configEa				(Base_0004h) */
typedef union _IoSlimbusEa
{
	unsigned long word;
	struct
	{
		unsigned long productId :16;
		unsigned long instanceVal :8;
		unsigned long :8;
	} bit;
} IoSlimbusEa;

/* structure of configPrTp			(Base_0008h) */
typedef union _IoSlimbusPrtp
{
	unsigned long word;
	struct
	{
		unsigned long prSupp :24;
		unsigned long tpSupp :3;
		unsigned long :5;
	} bit;
} IoSlimbusPrtp;

/* structure of configFr				(Base_000Ch) */
typedef union _IoSlimbusFr
{
	unsigned long word;
	struct
	{
		unsigned long rfSupp :16;
		unsigned long quality :2;
		unsigned long pauseAtRfchng :1;
		unsigned long :13;
	} bit;
} IoSlimbusFr;

/* structure of configDport			(Base_0010h) */
typedef union _IoSlimbusDport
{
	unsigned long word;
	struct
	{
		unsigned long sinkStartLvl :8;
		unsigned long dportClkPresc :4;
		unsigned long refclkSel :2;
		unsigned long :18;
	} bit;
} IoSlimbusDport;

/* structure of configEa2				(Base_0018h) */
typedef union _IoSlimbusEa2
{
	unsigned long word;
	struct
	{
		unsigned long deviceId1 :8;
		unsigned long deviceId2 :8;
		unsigned long deviceId3 :8;
		unsigned long :8;
	} bit;
} IoSlimbusEa2;

/* structure of configThr				(Base_001Ch) */
typedef union _IoSlimbusThr
{
	unsigned long word;
	struct
	{
		unsigned long srcThr :6;
		unsigned long :10;
		unsigned long sinkThr :6;
		unsigned long :10;
	} bit;
} IoSlimbusThr;

/* structure of command					(Base_0020h) */
typedef union _IoSlimbusCommand
{
	unsigned long word;
	struct
	{
		unsigned long txPush :1;
		unsigned long rxPull :1;
		unsigned long txClr :1;
		unsigned long unfreeze :1;
		unsigned long cfgStrobe :1;
		unsigned long cfgStrobeClr :1;
		unsigned long :26;
	} bit;
} IoSlimbusCommand;

/* structure of state					(Base_0024h) */
typedef union _IoSlimbusState
{
	unsigned long word;
	struct
	{
		unsigned long txFull :1;
		unsigned long txNotempty :1;
		unsigned long rxNotempty :1;
		unsigned long :1;
		unsigned long txPush :1;
		unsigned long rxPull :1;
		unsigned long :2;
		unsigned long fSync :1;
		unsigned long sfSync :1;
		unsigned long mSync :1;
		unsigned long sfbSync :1;
		unsigned long phSync :1;
		unsigned long :2;
		unsigned long detached :1;
		unsigned long subframeMode :5;
		unsigned long :3;
		unsigned long clockGear :4;
		unsigned long rootFr :4;
	} bit;
} IoSlimbusState;

/* structure of ieState				(Base_0028h) */
typedef union _IoSlimbusIestate
{
	unsigned long word;
	struct
	{
		unsigned long exErrorIf :1;
		unsigned long :1;
		unsigned long unsprtdMsgIf :1;
		unsigned long mcTxCol :1;
		unsigned long lostFs :1;
		unsigned long lostSfs :1;
		unsigned long lostMs :1;
		unsigned long dataSlotOverlap :1;
		unsigned long exErrorFr :1;
		unsigned long rcfgObjection :1;
		unsigned long unsprtdMsgFr :1;
		unsigned long activeFramer :1;
		unsigned long fsTxCol :1;
		unsigned long fiTxCol :1;
		unsigned long gcTxCol :1;
		unsigned long :1;
		unsigned long exErrorDev :1;
		unsigned long dataTxCol :1;
		unsigned long unsprtdMsgDev :1;
		unsigned long :13;
	} bit;
} IoSlimbusIestate;

/* structure of mchusage				(Base_002Ch) */
typedef union _IoSlimbusMchusage
{
	unsigned long word;
	struct
	{
		unsigned long mchusage :11;
		unsigned long :5;
		unsigned long mchCapacity :11;
		unsigned long mchLapse :5;
	} bit;
} IoSlimbusMchusage;

/* structure of intEn					(Base_0038h) */
typedef union _IoSlimbusInten
{
	unsigned long word;
	struct
	{
		unsigned long inEn :1;
		unsigned long rxIntEn :1;
		unsigned long txIntEn :1;
		unsigned long txErrEn :1;
		unsigned long syncLostEn :1;
		unsigned long rcfgIntEn :1;
		unsigned long mchIntEn :1;
		unsigned long :25;
	} bit;
} IoSlimbusInten;

/* structure of ksint						(Base_003Ch) */
typedef union _IoSlimbusInt
{
	unsigned long word;
	struct
	{
		unsigned long :1;
		unsigned long __rxInt :1;
		unsigned long __txInt :1;
		unsigned long __txErr :1;
		unsigned long __syncLost :1;
		unsigned long __rcfgInt :1;
		unsigned long __mchInt :1;
		unsigned long __portInt :1;
		unsigned long :24;
	} bit;
} IoSlimbusInt;

/* structure of p0IntEn				(Base_0080h) */
typedef union _IoSlimbusP0inten
{
	unsigned long word;
	struct
	{
		unsigned long actIntEn :1;
		unsigned long conIntEn :1;
		unsigned long chanIntEn :1;
		unsigned long dmaIntEn :1;
		unsigned long ovfIntEn :1;
		unsigned long undIntEn :1;
		unsigned long fifoClr :1;
		unsigned long prGenEn :1;
		unsigned long :24;
	} bit;
} IoSlimbusP0inten;

/* structure of RX_FIFO_FLAG	*/
typedef union _IoSlimbusRxfifoflag
{
	unsigned long word;
	struct
	{
		unsigned long msgSize :6;
		unsigned long :2;
		unsigned long rxOverflow :1;
		unsigned long txErr :7;
		unsigned long lostMsgNum :16;
	} bit;
} IoSlimbusRxfifoflag;

/* structure of p0Int					(Base_00C0h) */
typedef union _IoSlimbusP0int
{
	unsigned long word;
	struct
	{
		unsigned long __actInt :1;
		unsigned long __conInt :1;
		unsigned long __chanInt :1;
		unsigned long __dmaInt :1;
		unsigned long __ovfInt :1;
		unsigned long __undInt :1;
		unsigned long :26;
	} bit;
} IoSlimbusP0int;

/* structure of p0State0				(Base_0100h) */
typedef union _IoSlimbusP0state0
{
	unsigned long word;
	struct
	{
		unsigned long active :1;
		unsigned long contentDefined :1;
		unsigned long channelDefined :1;
		unsigned long sink :1;
		unsigned long ovf :1;
		unsigned long und :1;
		unsigned long dportReady :1;
		unsigned long :9;
		unsigned long sDistr :12;
		unsigned long trProtocol :4;
	} bit;
} IoSlimbusP0state0;

/* structure of p0State1				(Base_0104h) */
typedef union _IoSlimbusP0state1
{
	unsigned long word;
	struct
	{
		unsigned long pRate :7;
		unsigned long frLock :1;
		unsigned long dataType :4;
		unsigned long :4;
		unsigned long dataLength :6;
		unsigned long :2;
		unsigned long portLinked :6;
		unsigned long :1;
		unsigned long chLink :1;
	} bit;
} IoSlimbusP0state1;

/* Define I/O mapping		*/
/* Base(SLIMbus ch0) 1E30_(0000 - 103Fh) */
/* Base(SLIMbus ch1) 1E40_(0000 - 103Fh) */
/* Base(SLIMbus ch2) 1E90_(0000 - 103Fh) */
/* Base(SLIMbus ch3) 1EA0_(0000 - 103Fh) */
typedef struct _IoSlimbus
{
	IoSlimbusMode configMode; /* Base_(0000 - 0003h) */
	IoSlimbusEa configEa; /* Base_(0004 - 0007h) */
	IoSlimbusPrtp configPrTp; /* Base_(0008 - 000Bh) */
	IoSlimbusFr configFr; /* Base_(000C - 000Fh) */
	IoSlimbusDport configDport; /* Base_(0010 - 0013h) */
	unsigned char dmy0010017[0x0018 - 0x0014]; /* Base_(0014 - 0017h) */
	IoSlimbusEa2 configEa2; /* Base_(0018 - 001Bh) */
	IoSlimbusThr configThr; /* Base_(001C - 001Fh) */
	IoSlimbusCommand command; /* Base_(0020 - 0023h) */
	IoSlimbusState state; /* Base_(0024 - 0027h) */
	IoSlimbusIestate ieState; /* Base_(0028 - 002Bh) */
	IoSlimbusMchusage mchusage; /* Base_(002C - 002Fh) */
	unsigned char dmy00300037[0x0038 - 0x0030]; /* Base_(0030 - 0037h) */
	IoSlimbusInten intEn; /* Base_(0038 - 003Bh) */
	IoSlimbusInt ksint; /* Base_(003C - 003Fh) */
	unsigned long mcFifo[16]; /* Base_(0040 - 007Fh) */
	IoSlimbusP0inten p0IntEn; /* Base_(0080 - 0083h) */
	unsigned char dmy008400bf[0x00C0 - 0x0084]; /* Base_(0084 - 00BFh) */
	IoSlimbusP0int p0Int; /* Base_(00C0 - 00C3h) */
	unsigned char dmy00c400ff[0x0100 - 0x00C4]; /* Base_(00C4 - 00FFh) */
	IoSlimbusP0state0 p0State0; /* Base_(0100 - 0103h) */
	IoSlimbusP0state1 p0State1; /* Base_(0104 - 0107h) */
	unsigned char dmy01080fff[0x1000 - 0x0108]; /* Base_(0108 - 0FFFh) */
	unsigned long p0Fifo[64]; /* Base_(1000 - 10FFh) */
} IoSlimbus;

extern volatile IoSlimbus ioSlimbus0;
extern volatile IoSlimbus ioSlimbus1;
extern volatile IoSlimbus ioSlimbus2;
extern volatile IoSlimbus ioSlimbus3;

KConstType k_slimbus_get_type(void);
KSlimbus* k_slimbus_new(void);

#endif/*__K_SLIMBUS_H__*/

