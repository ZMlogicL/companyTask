/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-07
*@author            :陈倩
*@brief             :kjdsfpt
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


#ifndef __K_JDSFPT_H__
#define __K_JDSFPT_H__


#include <klib.h>


#define K_TYPE_JDSFPT			(k_jdsfpt_get_type())
#define K_JDSFPT(obj)				(K_TYPE_CHECK_INSTANCE_CAST((obj), KJdsfpt))
#define K_IS_JDSFPT(obj)			(K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_JDSFPT))


typedef struct _KJdsfpt				KJdsfpt;
typedef struct _KJdsfptPrivate	KJdsfptPrivate;

struct  _KJdsfpt
{
	KObject parent;
};


/*	structure of fptctl0	(288D_0000h)	*/
typedef union _IoFptFptctl0
{
	unsigned long word;
	struct {
		unsigned long sr :1;
		unsigned long :31;
	} bit;
} IoFptFptctl0;

/*	structure of fptctl1	(288D_0004h)	*/
typedef union _IoFptFptctl1
{
	unsigned long word;
	struct {
		unsigned long trg :2;
		unsigned long :30;
	} bit;
} IoFptFptctl1;

/*	structure of fptctl2	(288D_0008h)	*/
typedef union _IoFptFptctl2
{
	unsigned long word;
	struct {
		unsigned long ramslp :1;
		unsigned long :15;
		unsigned long mode :2;
		unsigned long :2;
		unsigned long ioMode :1;
		unsigned long :3;
		unsigned long pipeEn :1;
		unsigned long :3;
		unsigned long debugMode :1;
		unsigned long :3;
	} bit;
} IoFptFptctl2;

/*	structure of fptfqctl0	(288D_0010h)	*/
typedef union _IoFptFptfqctl0
{
	unsigned long word;
	struct {
		unsigned long ghsize :15;
		unsigned long :17;
	} bit;
} IoFptFptfqctl0;

/*	structure of fptfqctl1	(288D_0014h)	*/
typedef union _IoFptFptfqctl1
{
	unsigned long word;
	struct {
		unsigned long hsize :15;
		unsigned long :1;
		unsigned long vsize :15;
		unsigned long :1;
	} bit;
} IoFptFptfqctl1;

/*	structure of fptfqctl2	(288D_0018h)	*/
typedef union _IoFptFptfqctl2
{
	unsigned long word;
	struct {
		unsigned long fpmax :7;
		unsigned long :1;
		unsigned long sumw :1;
		unsigned long :3;
		unsigned long outen :1;
		unsigned long :19;
	} bit;
} IoFptFptfqctl2;

/*	structure of fptfqctl3	(288D_001Ch)	*/
typedef union _IoFptFptfqctl3
{
	unsigned long word;
	struct {
		unsigned long sdadFqOf :32;
	} bit;
} IoFptFptfqctl3;

/*	structure of fptfqctl4	(288D_0020h)	*/
typedef union _IoFptFptfqctl4
{
	unsigned long word;
	struct {
		unsigned long sdadFqMp :32;
	} bit;
} IoFptFptfqctl4;

/*	structure of fptfqctl5	(288D_0024h)	*/
typedef union _IoFptFptfqctl5
{
	unsigned long word;
	struct {
		unsigned long sdadFqHi :32;
	} bit;
} IoFptFptfqctl5;

/*	structure of fptfqctl6	(288D_0028h)	*/
typedef union _IoFptFptfqctl6
{
	unsigned long word;
	struct {
		unsigned long sdadFqCxy :32;
	} bit;
} IoFptFptfqctl6;

/*	structure of fptfqctl7	(288D_002Ch)	*/
typedef union _IoFptFptfqctl7
{
	unsigned long word;
	struct {
		unsigned long sdadFqRxy :32;
	} bit;
} IoFptFptfqctl7;

/*	structure of fptfqctl8	(288D_0030h)	*/
typedef union _IoFptFptfqctl8
{
	unsigned long word;
	struct {
		unsigned long mapghsize :15;
		unsigned long :17;
	} bit;
} IoFptFptfqctl8;

/*	structure of fptfqctl9	(288D_0034h)	*/
typedef union _IoFptFptfqctl9
{
	unsigned long word;
	struct {
		unsigned long skipxFq :13;
		unsigned long :3;
		unsigned long skipyFq :13;
		unsigned long :3;
	} bit;
} IoFptFptfqctl9;

/*	structure of fptftctl0	(288D_0040h)	*/
typedef union _IoFptFptftctl0
{
	unsigned long word;
	struct {
		unsigned long ghbsize :15;
		unsigned long :1;
		unsigned long ghtsize :15;
		unsigned long :1;
	} bit;
} IoFptFptftctl0;

/*	structure of fptftctl1	(288D_0044h)	*/
typedef union _IoFptFptftctl1
{
	unsigned long word;
	struct {
		unsigned long ftmax :7;
		unsigned long :1;
		unsigned long init0 :1;
		unsigned long :23;
	} bit;
} IoFptFptftctl1;

/*	structure of fptftctl2	(288D_0048h)	*/
typedef union _IoFptFptftctl2
{
	unsigned long word;
	struct {
		unsigned long leftlimit :12;
		unsigned long :4;
		unsigned long rightlimit :12;
		unsigned long :4;
	} bit;
} IoFptFptftctl2;

/*	structure of fptftctl3	(288D_004Ch)	*/
typedef union _IoFptFptftctl3
{
	unsigned long word;
	struct {
		unsigned long toplimit :12;
		unsigned long :4;
		unsigned long bottomlimit :12;
		unsigned long :4;
	} bit;
} IoFptFptftctl3;

/*	structure of fptftctl4	(288D_0050h)	*/
typedef union _IoFptFptftctl4
{
	unsigned long word;
	struct {
		unsigned long maxerr :12;
		unsigned long :4;
		unsigned long maxitr :4;
		unsigned long :12;
	} bit;
} IoFptFptftctl4;

/*	structure of fptftctl5	(288D_0054h)	*/
typedef union _IoFptFptftctl5
{
	unsigned long word;
	struct {
		unsigned long sdadBpOf :32;
	} bit;
} IoFptFptftctl5;

/*	structure of fptftctl6	(288D_0058h)	*/
typedef union _IoFptFptftctl6
{
	unsigned long word;
	struct {
		unsigned long sdadTpOf :32;
	} bit;
} IoFptFptftctl6;

/*	structure of fptftctl7	(288D_005Ch)	*/
typedef union _IoFptFptftctl7
{
	unsigned long word;
	struct {
		unsigned long sdadFtCxy :32;
	} bit;
} IoFptFptftctl7;

/*	structure of fptftctl8	(288D_0060h)	*/
typedef union _IoFptFptftctl8
{
	unsigned long word;
	struct {
		unsigned long sdadFtBxy :32;
	} bit;
} IoFptFptftctl8;

/*	structure of fptftctl9	(288D_0064h)	*/
typedef union _IoFptFptftctl9
{
	unsigned long word;
	struct {
		unsigned long sdadFtTxy :32;
	} bit;
} IoFptFptftctl9;

/*	structure of fptftctl10	(288D_0068h)	*/
typedef union _IoFptFptftctl10
{
	unsigned long word;
	struct {
		unsigned long skipxFt :13;
		unsigned long :3;
		unsigned long skipyFt :13;
		unsigned long :3;
	} bit;
} IoFptFptftctl10;

/*	structure of fptinte0	(288D_0070h)	*/
typedef union _IoFptFptinte0
{
	unsigned long word;
	struct {
		unsigned long fpten :1;
		unsigned long :3;
		unsigned long axeen :1;
		unsigned long :3;
		unsigned long pmeen :1;
		unsigned long :23;
	} bit;
}IoFptFptinte0;

/*	structure of fptintf0	(288D_0074h)	*/
typedef union _IoFptFptintf0
{
	unsigned long word;
	struct {
		unsigned long __fptflg :1;
		unsigned long :3;
		unsigned long __axeflg :1;
		unsigned long :3;
		unsigned long __pmeflg :1;
		unsigned long :23;
	} bit;
} IoFptFptintf0;

/*	structure of fptaxictl0	(288D_0080h)	*/
typedef union _IoFptFptaxictl0
{
	unsigned long word;
	struct {
		unsigned long arcache :4;
		unsigned long arprot :3;
		unsigned long :1;
		unsigned long awcache :4;
		unsigned long awprot :3;
		unsigned long :1;
		unsigned long pkgen :1;
		unsigned long :15;
	} bit;
} IoFptFptaxictl0;

/*	structure of fptaxierr0	(288D_0084h)	*/
typedef union _IoFptFptaxierr0
{
	unsigned long word;
	struct {
		unsigned long rresp :2;
		unsigned long :6;
		unsigned long wresp :2;
		unsigned long :22;
	} bit;
} IoFptFptaxierr0;

/*	structure of fptctl3	(288D_0090h)	*/
typedef union _IoFptFptctl3
{
	unsigned long word;
	struct {
		unsigned long brcEn :1;
		unsigned long :7;
		unsigned long brcMod :2;
		unsigned long :6;
		unsigned long lutSel :1;
		unsigned long :15;
	} bit;
} IoFptFptctl3;

/*	structure of fptctl4	(288D_0094h)	*/
typedef union _IoFptFptctl4
{
	unsigned long word;
	struct {
		unsigned long clpminB :8;
		unsigned long clpmaxB :8;
		long offsetB :9;
		unsigned long :7;
	} bit;
} IoFptFptctl4;

/*	structure of fptctl5	(288D_0098h)	*/
typedef union _IoFptFptctl5
{
	unsigned long word;
	struct {
		unsigned long clpminT :8;
		unsigned long clpmaxT :8;
		long offsetT :9;
		unsigned long :7;
	} bit;
} IoFptFptctl5;

/* Define i/o mapping */
typedef struct _IoJdsfpt
{
	/* JDSFPT */
	/* 288D_(0000 - 0003h) */
	IoFptFptctl0 fptctl0;
	/* 288D_(0004 - 0007h) */
	IoFptFptctl1 fptctl1;
	/* 288D_(0008 - 000Bh) */
	IoFptFptctl2 fptctl2;
	/* 288D_(000C - 000Fh) */
	unsigned char dmy000c000f[0x0010 - 0x000C];
	/* 288D_(0010 - 0013h) */
	IoFptFptfqctl0 fptfqctl0;
	/* 288D_(0014 - 0017h) */
	IoFptFptfqctl1 fptfqctl1;
	/* 288D_(0018 - 001Bh) */
	IoFptFptfqctl2 fptfqctl2;
	/* 288D_(001C - 001Fh) */
	IoFptFptfqctl3 fptfqctl3;
	/* 288D_(0020 - 0023h) */
	IoFptFptfqctl4 fptfqctl4;
	/* 288D_(0024 - 0027h) */
	IoFptFptfqctl5 fptfqctl5;
	/* 288D_(0028 - 002Bh) */
	IoFptFptfqctl6 fptfqctl6;
	/* 288D_(002C - 002Fh) */
	IoFptFptfqctl7 fptfqctl7;
	/* 288D_(0030 - 0033h) */
	IoFptFptfqctl8 fptfqctl8;
	/* 288D_(0034 - 0037h) */
	IoFptFptfqctl9 fptfqctl9;
	/* 288D_(0038 - 003Fh) */
	unsigned char dmy0038003f[0x0040 - 0x0038];
	/* 288D_(0040 - 0043h) */
	IoFptFptftctl0 fptftctl0;
	/* 288D_(0044 - 0047h) */
	IoFptFptftctl1 fptftctl1;
	/* 288D_(0048 - 004Bh) */
	IoFptFptftctl2 fptftctl2;
	/* 288D_(004C - 004Fh) */
	IoFptFptftctl3 fptftctl3;
	/* 288D_(0050 - 0053h) */
	IoFptFptftctl4 fptftctl4;
	/* 288D_(0054 - 0057h) */
	IoFptFptftctl5 fptftctl5;
	/* 288D_(0058 - 005Bh) */
	IoFptFptftctl6 fptftctl6;
	/* 288D_(005C - 005Fh) */
	IoFptFptftctl7 fptftctl7;
	/* 288D_(0060 - 0063h) */
	IoFptFptftctl8 fptftctl8;
	/* 288D_(0064 - 0067h) */
	IoFptFptftctl9 fptftctl9;
	/* 288D_(0068 - 006Bh) */
	IoFptFptftctl10 fptftctl10;
	/* 288D_(006C - 006Fh) */
	unsigned char dmy006c006f[0x0070 - 0x006C];
	/* 288D_(0070 - 0073h) */
	IoFptFptinte0 fptinte0;
	/* 288D_(0074 - 0077h) */
	IoFptFptintf0 fptintf0;
	/* 288D_(0078 - 007Fh) */
	unsigned char dmy0078007f[0x0080 - 0x0078];
	/* 288D_(0080 - 0083h) */
	IoFptFptaxictl0 fptaxictl0;
	/* 288D_(0084 - 0087h) */
	IoFptFptaxierr0 fptaxierr0;
	/* 288D_(0088 - 008Fh) */
	unsigned char dmy0088008f[0x0090 - 0x0088];
	/* 288D_(0090 - 0093h) */
	IoFptFptctl3 fptctl3;
	/* 288D_(0094 - 0097h) */
	IoFptFptctl4 fptctl4;
	/* 288D_(0098 - 009Bh) */
	IoFptFptctl5 fptctl5;
	/* 288D_(009C - 00FFh) */
	unsigned char dmy009c00ff[0x0100 - 0x009C];

} IoJdsfpt;

extern volatile IoJdsfpt		ioFpt[2];

/*	structure of FPTLUT	(298C_1000h)	*/
typedef union _IoFptFptlut
{
	unsigned char byte[256];
	unsigned long word[64];
} IoFptFptlut;

/*	structure of FPTREG	(298C_1400h)	*/
typedef union _IoFptFptreg
{
	unsigned char byte[512];
	unsigned long word[128];
} IoFptFptreg;

/* Define i/o mapping */
typedef struct _IoJdsfptAhb
{
	/* 298C_(1000 - 10FFh) */
	IoFptFptlut fptlut0;
	/* 298C_(1100 - 11FFh) */
	IoFptFptlut fptlut1;
	/* 298C_(1200 - 13FFh) */
	unsigned char dmy020003ff[0x0400 - 0x0200];
	/* 298C_(1400 - 15FFh) */
	IoFptFptreg fptreg0;
	/* 298C_(1600 - 17FFh) */
	IoFptFptreg fptreg1;
} IoJdsfptAhb;

extern volatile IoJdsfptAhb		ioFptAhb[2];


KConstType	k_jdsfpt_get_type(void);
KJdsfpt*	k_jdsfpt_new(void);


#endif/*__K_JDSFPT_H__*/

