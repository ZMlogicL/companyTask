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

#define K_TYPE_SLIMBUS				(k_slimbus_get_type())
#define K_SLIMBUS(obj)					(K_TYPE_CHECK_INSTANCE_CAST((obj), KSlimbus))
#define K_IS_SLIMBUS(obj)				(K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_SLIMBUS))

typedef struct _KSlimbus 				KSlimbus;
typedef struct _KSlimbusPrivate 	KSlimbusPrivate;

struct _KSlimbus
{
	KObject parent;
};

/* structure of configMode				(Base_0000h) */
typedef union _IoSlimbusMode
{
	kulong word;
	struct
	{
		kulong enable :1;
		kulong managerMode :1;
		kulong snifferMode :1;
		kulong frEn :1;
		kulong devEn :1;
		kulong goAbsent :1;
		kulong :2;
		kulong retryLmt :4;
		kulong reportAtEvent :1;
		kulong crcCalcDisable :1;
		kulong lmtdReport :1;
		kulong reconfTxDis :1;
		kulong :16;
	} bit;
} IoSlimbusMode;

/* structure of configEa				(Base_0004h) */
typedef union _IoSlimbusEa
{
	kulong word;
	struct
	{
		kulong productId :16;
		kulong instanceVal :8;
		kulong :8;
	} bit;
} IoSlimbusEa;

/* structure of configPrTp			(Base_0008h) */
typedef union _IoSlimbusPrtp
{
	kulong word;
	struct
	{
		kulong prSupp :24;
		kulong tpSupp :3;
		kulong :5;
	} bit;
} IoSlimbusPrtp;

/* structure of configFr				(Base_000Ch) */
typedef union _IoSlimbusFr
{
	kulong word;
	struct
	{
		kulong rfSupp :16;
		kulong quality :2;
		kulong pauseAtRfchng :1;
		kulong :13;
	} bit;
} IoSlimbusFr;

/* structure of configDport			(Base_0010h) */
typedef union _IoSlimbusDport
{
	kulong word;
	struct
	{
		kulong sinkStartLvl :8;
		kulong dportClkPresc :4;
		kulong refclkSel :2;
		kulong :18;
	} bit;
} IoSlimbusDport;

/* structure of configEa2				(Base_0018h) */
typedef union _IoSlimbusEa2
{
	kulong word;
	struct
	{
		kulong deviceId1 :8;
		kulong deviceId2 :8;
		kulong deviceId3 :8;
		kulong :8;
	} bit;
} IoSlimbusEa2;

/* structure of configThr				(Base_001Ch) */
typedef union _IoSlimbusThr
{
	kulong word;
	struct
	{
		kulong srcThr :6;
		kulong :10;
		kulong sinkThr :6;
		kulong :10;
	} bit;
} IoSlimbusThr;

/* structure of command					(Base_0020h) */
typedef union _IoSlimbusCommand
{
	kulong word;
	struct
	{
		kulong txPush :1;
		kulong rxPull :1;
		kulong txClr :1;
		kulong unfreeze :1;
		kulong cfgStrobe :1;
		kulong cfgStrobeClr :1;
		kulong :26;
	} bit;
} IoSlimbusCommand;

/* structure of state					(Base_0024h) */
typedef union _IoSlimbusState
{
	kulong word;
	struct
	{
		kulong txFull :1;
		kulong txNotempty :1;
		kulong rxNotempty :1;
		kulong :1;
		kulong txPush :1;
		kulong rxPull :1;
		kulong :2;
		kulong fSync :1;
		kulong sfSync :1;
		kulong mSync :1;
		kulong sfbSync :1;
		kulong phSync :1;
		kulong :2;
		kulong detached :1;
		kulong subframeMode :5;
		kulong :3;
		kulong clockGear :4;
		kulong rootFr :4;
	} bit;
} IoSlimbusState;

/* structure of ieState				(Base_0028h) */
typedef union _IoSlimbusIestate
{
	kulong word;
	struct
	{
		kulong exErrorIf :1;
		kulong :1;
		kulong unsprtdMsgIf :1;
		kulong mcTxCol :1;
		kulong lostFs :1;
		kulong lostSfs :1;
		kulong lostMs :1;
		kulong dataSlotOverlap :1;
		kulong exErrorFr :1;
		kulong rcfgObjection :1;
		kulong unsprtdMsgFr :1;
		kulong activeFramer :1;
		kulong fsTxCol :1;
		kulong fiTxCol :1;
		kulong gcTxCol :1;
		kulong :1;
		kulong exErrorDev :1;
		kulong dataTxCol :1;
		kulong unsprtdMsgDev :1;
		kulong :13;
	} bit;
} IoSlimbusIestate;

/* structure of mchusage				(Base_002Ch) */
typedef union _IoSlimbusMchusage
{
	kulong word;
	struct
	{
		kulong mchusage :11;
		kulong :5;
		kulong mchCapacity :11;
		kulong mchLapse :5;
	} bit;
} IoSlimbusMchusage;

/* structure of intEn					(Base_0038h) */
typedef union _IoSlimbusInten
{
	kulong word;
	struct
	{
		kulong inEn :1;
		kulong rxIntEn :1;
		kulong txIntEn :1;
		kulong txErrEn :1;
		kulong syncLostEn :1;
		kulong rcfgIntEn :1;
		kulong mchIntEn :1;
		kulong :25;
	} bit;
} IoSlimbusInten;

/* structure of ksint						(Base_003Ch) */
typedef union _IoSlimbusInt
{
	kulong word;
	struct
	{
		kulong :1;
		kulong __rxInt :1;
		kulong __txInt :1;
		kulong __txErr :1;
		kulong __syncLost :1;
		kulong __rcfgInt :1;
		kulong __mchInt :1;
		kulong __portInt :1;
		kulong :24;
	} bit;
} IoSlimbusInt;

/* structure of p0IntEn				(Base_0080h) */
typedef union _IoSlimbusP0inten
{
	kulong word;
	struct
	{
		kulong actIntEn :1;
		kulong conIntEn :1;
		kulong chanIntEn :1;
		kulong dmaIntEn :1;
		kulong ovfIntEn :1;
		kulong undIntEn :1;
		kulong fifoClr :1;
		kulong prGenEn :1;
		kulong :24;
	} bit;
} IoSlimbusP0inten;

/* structure of RX_FIFO_FLAG	*/
typedef union _IoSlimbusRxfifoflag
{
	kulong word;
	struct
	{
		kulong msgSize :6;
		kulong :2;
		kulong rxOverflow :1;
		kulong txErr :7;
		kulong lostMsgNum :16;
	} bit;
} IoSlimbusRxfifoflag;

/* structure of p0Int					(Base_00C0h) */
typedef union _IoSlimbusP0int
{
	kulong word;
	struct
	{
		kulong __actInt :1;
		kulong __conInt :1;
		kulong __chanInt :1;
		kulong __dmaInt :1;
		kulong __ovfInt :1;
		kulong __undInt :1;
		kulong :26;
	} bit;
} IoSlimbusP0int;

/* structure of p0State0				(Base_0100h) */
typedef union _IoSlimbusP0state0
{
	kulong word;
	struct
	{
		kulong active :1;
		kulong contentDefined :1;
		kulong channelDefined :1;
		kulong sink :1;
		kulong ovf :1;
		kulong und :1;
		kulong dportReady :1;
		kulong :9;
		kulong sDistr :12;
		kulong trProtocol :4;
	} bit;
} IoSlimbusP0state0;

/* structure of p0State1				(Base_0104h) */
typedef union _IoSlimbusP0state1
{
	kulong word;
	struct
	{
		kulong pRate :7;
		kulong frLock :1;
		kulong dataType :4;
		kulong :4;
		kulong dataLength :6;
		kulong :2;
		kulong portLinked :6;
		kulong :1;
		kulong chLink :1;
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
	kuchar dmy0010017[0x0018 - 0x0014]; /* Base_(0014 - 0017h) */
	IoSlimbusEa2 configEa2; /* Base_(0018 - 001Bh) */
	IoSlimbusThr configThr; /* Base_(001C - 001Fh) */
	IoSlimbusCommand command; /* Base_(0020 - 0023h) */
	IoSlimbusState state; /* Base_(0024 - 0027h) */
	IoSlimbusIestate ieState; /* Base_(0028 - 002Bh) */
	IoSlimbusMchusage mchusage; /* Base_(002C - 002Fh) */
	kuchar dmy00300037[0x0038 - 0x0030]; /* Base_(0030 - 0037h) */
	IoSlimbusInten intEn; /* Base_(0038 - 003Bh) */
	IoSlimbusInt ksint; /* Base_(003C - 003Fh) */
	kulong mcFifo[16]; /* Base_(0040 - 007Fh) */
	IoSlimbusP0inten p0IntEn; /* Base_(0080 - 0083h) */
	kuchar dmy008400bf[0x00C0 - 0x0084]; /* Base_(0084 - 00BFh) */
	IoSlimbusP0int p0Int; /* Base_(00C0 - 00C3h) */
	kuchar dmy00c400ff[0x0100 - 0x00C4]; /* Base_(00C4 - 00FFh) */
	IoSlimbusP0state0 p0State0; /* Base_(0100 - 0103h) */
	IoSlimbusP0state1 p0State1; /* Base_(0104 - 0107h) */
	kuchar dmy01080fff[0x1000 - 0x0108]; /* Base_(0108 - 0FFFh) */
	kulong p0Fifo[64]; /* Base_(1000 - 10FFh) */
} IoSlimbus;

extern volatile IoSlimbus ioSlimbus0;
extern volatile IoSlimbus ioSlimbus1;
extern volatile IoSlimbus ioSlimbus2;
extern volatile IoSlimbus ioSlimbus3;

KConstType k_slimbus_get_type(void);
KSlimbus* 	k_slimbus_new(void);

#endif/*__K_SLIMBUS_H__*/

