/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-05
 *@author            :陈倩
 *@brief             :kjdscnr1a
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


#ifndef __K_JDSCNR1A_H__
#define __K_JDSCNR1A_H__


#include <klib.h>
//#include "_jdscnr_otf_reg_rw.h"
//#include "_jdscnr_cspr_reg.h"
//#include "_jdscnr_ofl_reg_rw.h"
//#include "_jdscnr_ofl_reg_yspr.h"
#include "kjdscnr1a1.h"
#include "kjdscnr1a2.h"


#define K_TYPE_JDSCNR1A				(k_jdscnr1a_get_type())
#define K_JDSCNR1A(obj)				(K_TYPE_CHECK_INSTANCE_CAST((obj), KJdscnr1a))
#define K_IS_JDSCNR1A(obj)			(K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_JDSCNR1A))


typedef struct _KJdscnr1a 				KJdscnr1a;
typedef struct _KJdscnr1aPrivate 	KJdscnr1aPrivate;


struct _KJdscnr1a
{
	KObject parent;
};


typedef union _IoCnrCsprRegSprscrof2
{
	kulong word;
	struct
	{
		klong sprscrof4 :8;
		klong sprscrof5 :8;
		kulong :16;
	} bit;
} IoCnrCsprRegSprscrof2;

typedef struct _IoCnrCsprRegSprscrof
{
	IoCnrCsprRegSprscrof1 sprscrof1;
	IoCnrCsprRegSprscrof2 sprscrof2;
} IoCnrCsprRegSprscrof;

/*	structure of sprscrga	(2842_1230h)	*/
typedef union _IoCnrCsprRegSprscrga1
{
	kulong word;
	struct
	{
		klong sprscrga0 :12;
		kulong :4;
		klong sprscrga1 :12;
		kulong :4;
	} bit;
} IoCnrCsprRegSprscrga1;

typedef union _IoCnrCsprRegSprscrga2
{
	kulong word;
	struct
	{
		klong sprscrga2 :12;
		kulong :4;
		klong sprscrga3 :12;
		kulong :4;
	} bit;
} IoCnrCsprRegSprscrga2;

typedef union _IoCnrCsprRegSprscrga3
{
	kulong word;
	struct
	{
		klong sprscrga4 :12;
		kulong :4;
		klong sprscrga5 :12;
		kulong :4;
	} bit;
} IoCnrCsprRegSprscrga3;

typedef struct _IoCnrCsprRegSprscrga
{
	IoCnrCsprRegSprscrga1 sprscrga1;
	IoCnrCsprRegSprscrga2 sprscrga2;
	IoCnrCsprRegSprscrga3 sprscrga3;
} IoCnrCsprRegSprscrga;

/*	structure of sprscrbd	(2842_1240h)	*/
typedef union _IoCnrCsprRegSprscrbd1
{
	kulong word;
	struct
	{
		klong sprscrbd1 :8;
		klong sprscrbd2 :8;
		klong sprscrbd3 :8;
		klong sprscrbd4 :8;
	} bit;
} IoCnrCsprRegSprscrbd1;

typedef union _IoCnrCsprRegSprscrbd2
{
	kulong word;
	struct
	{
		klong sprscrbd5 :8;
		kulong :24;
	} bit;
} IoCnrCsprRegSprscrbd2;

typedef struct _IoCnrCsprRegSprscrbd
{
	IoCnrCsprRegSprscrbd1 sprscrbd1;
	IoCnrCsprRegSprscrbd2 sprscrbd2;
} IoCnrCsprRegSprscrbd;

/*	structure of sprd	(2842_1280h)	*/
typedef union _IoCnrCsprRegSprd
{
	kulong word;
	struct
	{
		kulong sprd :1;
		kulong :31;
	} bit;
} IoCnrCsprRegSprd;

/*	structure of sprdcbof	(2842_1288h)	*/
typedef union _IoCnrCsprRegSprdcbof1
{
	kulong word;
	struct
	{
		klong sprdcbof0 :8;
		klong sprdcbof1 :8;
		klong sprdcbof2 :8;
		klong sprdcbof3 :8;
	} bit;
} IoCnrCsprRegSprdcbof1;

typedef union _IoCnrCsprRegSprdcbof2
{
	kulong word;
	struct
	{
		klong sprdcbof4 :8;
		klong sprdcbof5 :8;
		kulong :16;
	} bit;
} IoCnrCsprRegSprdcbof2;

typedef struct _IoCnrCsprRegSprdcbof
{
	IoCnrCsprRegSprdcbof1 sprdcbof1;
	IoCnrCsprRegSprdcbof2 sprdcbof2;
} IoCnrCsprRegSprdcbof;

/*	structure of sprdcbga	(2842_1290h)	*/
typedef union _IoSnrSsprRegSprdcbga1
{
	kulong word;
	struct
	{
		klong sprdcbga0 :12;
		kulong :4;
		klong sprdcbga1 :12;
		kulong :4;
	} bit;
} IoSnrSsprRegSprdcbga1;

typedef union _IoSnrSsprRegSprdcbga2
{
	kulong word;
	struct
	{
		klong sprdcbga2 :12;
		kulong :4;
		klong sprdcbga3 :12;
		kulong :4;
	} bit;
} IoSnrSsprRegSprdcbga2;

typedef union _IoSnrSsprRegSprdcbga3
{
	kulong word;
	struct
	{
		klong sprdcbga4 :12;
		kulong :4;
		klong sprdcbga5 :12;
		kulong :4;
	} bit;
} IoSnrSsprRegSprdcbga3;

typedef struct _IoCnrCsprRegSprdcbga
{
	IoSnrSsprRegSprdcbga1 sprdcbga1;
	IoSnrSsprRegSprdcbga2 sprdcbga2;
	IoSnrSsprRegSprdcbga3 sprdcbga3;
} IoCnrCsprRegSprdcbga;

/*	structure of sprdcbbd	(2842_12A0h)	*/
typedef union _IoSnrSsprRegSprdcbbd1
{
	kulong word;
	struct
	{
		klong sprdcbbd1 :8;
		klong sprdcbbd2 :8;
		klong sprdcbbd3 :8;
		klong sprdcbbd4 :8;
	} bit;
} IoSnrSsprRegSprdcbbd1;

typedef union _IoSnrSsprRegSprdcbbd2
{
	kulong word;
	struct
	{
		klong sprdcbbd5 :8;
		kulong :24;
	} bit;
} IoSnrSsprRegSprdcbbd2;

typedef struct _IoCnrCsprRegSprdcbbd
{
	IoSnrSsprRegSprdcbbd1 sprdcbbd1;
	IoSnrSsprRegSprdcbbd2 sprdcbbd2;
} IoCnrCsprRegSprdcbbd;

/*	structure of sprdcrof	(2842_12A8h)	*/
typedef union _IoSnrSsprRegSprdcrof1
{
	kulong word;
	struct
	{
		klong sprdcrof0 :8;
		klong sprdcrof1 :8;
		klong sprdcrof2 :8;
		klong sprdcrof3 :8;
	} bit;
} IoSnrSsprRegSprdcrof1;

typedef union _IoSnrSsprRegSprdcrof2
{
	kulong word;
	struct
	{
		klong sprdcrof4 :8;
		klong sprdcrof5 :8;
		kulong :16;
	} bit;
} IoSnrSsprRegSprdcrof2;

typedef struct _IoSnrSsprRegSprdcrof
{
	IoSnrSsprRegSprdcrof1 sprdcrof1;
	IoSnrSsprRegSprdcrof2 sprdcrof2;
} IoSnrSsprRegSprdcrof;

/*	structure of sprdcrga	(2842_12B0h)	*/
typedef union _IoSnrSsprRegSprdcrga1
{
	kulong word;
	struct
	{
		klong sprdcrga0 :12;
		kulong :4;
		klong sprdcrga1 :12;
		kulong :4;
	} bit;
} IoSnrSsprRegSprdcrga1;

typedef union _IoSnrSsprRegSprdcrga2
{
	kulong word;
	struct
	{
		klong sprdcrga2 :12;
		kulong :4;
		klong sprdcrga3 :12;
		kulong :4;
	} bit;
} IoSnrSsprRegSprdcrga2;

typedef union _IoSnrSsprRegSprdcrga3
{
	kulong word;
	struct
	{
		klong sprdcrga4 :12;
		kulong :4;
		klong sprdcrga5 :12;
		kulong :4;
	} bit;
} IoSnrSsprRegSprdcrga3;

typedef struct _IoSnrSsprRegSprdcrga
{
	IoSnrSsprRegSprdcrga1 sprdcrga1;
	IoSnrSsprRegSprdcrga2 sprdcrga2;
	IoSnrSsprRegSprdcrga3 sprdcrga3;
} IoSnrSsprRegSprdcrga;

/*	structure of sprdcrbd	(2842_12C0h)	*/
typedef union _IoCnrCsprRegSprdcrbd1
{
	kulong word;
	struct
	{
		klong sprdcrbd1 :8;
		klong sprdcrbd2 :8;
		klong sprdcrbd3 :8;
		klong sprdcrbd4 :8;
	} bit;
} IoCnrCsprRegSprdcrbd1;

typedef union _IoCnrCsprRegSprdcrbd2
{
	kulong word;
	struct
	{
		klong sprdcrbd5 :8;
		kulong :24;
	} bit;
} IoCnrCsprRegSprdcrbd2;

typedef struct _IoCnrCsprRegSprdcrbd
{
	IoCnrCsprRegSprdcrbd1 sprdcrbd1;
	IoCnrCsprRegSprdcrbd2 sprdcrbd2;
} IoCnrCsprRegSprdcrbd;

/* Define i/o mapping */
typedef struct _IoCnrCsprReg
{
	/* JDSIMG */
	IoCnrCsprRegCspren cspren; /* 2842_(1000 - 1003h) */

	kuchar dmy10041007[0x1008 - 0x1004]; /* 2842_(1004 - 1007h) */

	IoCnrCsprRegCgdken cgdken; /* 2842_(1008 - 100Bh) */

	kuchar dmy100c101f[0x1020 - 0x100C]; /* 2842_(100C - 101Fh) */

	IoCnrCsprRegMcen mcen; /* 2842_(1020 - 1023h) */
	IoCnrCsprRegMcythh mcythh; /* 2842_(1024 - 1027h) */
	IoCnrCsprRegMcythv mcythv; /* 2842_(1028 - 102Bh) */
	IoCnrCsprRegMccthh mccthh; /* 2842_(102C - 102Fh) */
	IoCnrCsprRegMccthv mccthv; /* 2842_(1030 - 1033h) */
	IoCnrCsprRegMcydym mcydym; /* 2842_(1034 - 1037h) */
	IoCnrCsprRegMcydymdt mcydymdt; /* 2842_(1038 - 103Bh) */

	kuchar dmy103c103f[0x1040 - 0x103C]; /* 2842_(103C - 103Fh) */

	IoCnrCsprRegMcyscl mcyscl; /* 2842_(1040 - 1043h) */

	kuchar dmy10441047[0x1048 - 0x1044]; /* 2842_(1044 - 1047h) */

	IoCnrCsprRegMcysclof mcysclof; /* 2842_(1048 - 104Fh) */
	IoCnrCsprRegMcysclga mcysclga; /* 2842_(1050 - 1057h) */
	IoCnrCsprRegMcysclbd mcysclbd; /* 2842_(1058 - 105Fh) */
	IoCnrCsprRegMccscl mccscl; /* 2842_(1060 - 1063h) */

	kuchar dmy10641067[0x1068 - 0x1064]; /* 2842_(1064 - 1067h) */

	IoCnrCsprRegMccsclof mccsclof; /* 2842_(1068 - 106Fh) */
	IoCnrCsprRegMccsclga mccsclga; /* 2842_(1070 - 1077h) */
	IoCnrCsprRegMccsclbd mccsclbd; /* 2842_(1078 - 107Fh) */
	IoCnrCsprRegMcsscl mcsscl; /* 2842_(1080 - 1083h) */

	kuchar dmy10841087[0x1088 - 0x1084]; /* 2842_(1084 - 1087h) */

	IoCnrCsprRegMcssclof mcssclof; /* 2842_(1088 - 108Fh) */
	IoCnrCsprRegMcssclga mcssclga; /* 2842_(1090 - 1097h) */
	IoCnrCsprRegMcssclbd mcssclbd; /* 2842_(1098 - 109Fh) */

	kuchar dmy10a010bf[0x10C0 - 0x10A0]; /* 2842_(10A0 - 10BFh) */

	IoCnrCsprRegLcen lcen; /* 2842_(10C0 - 10C3h) */
	IoCnrCsprRegLcythh lcythh; /* 2842_(10C4 - 10C7h) */
	IoCnrCsprRegLcythv lcythv; /* 2842_(10C8 - 10CBh) */
	IoCnrCsprRegLccthh lccthh; /* 2842_(10CC - 10CFh) */
	IoCnrCsprRegLccthv lccthv; /* 2842_(10D0 - 10D3h) */
	IoCnrCsprRegLcydym lcydym; /* 2842_(10D4 - 10D7h) */
	IoCnrCsprRegLcydymdt lcydymdt; /* 2842_(10D8 - 10DBh) */

	kuchar dmy10dc10df[0x10E0 - 0x10DC]; /* 2842_(10DC - 10DFh) */

	IoCnrCsprRegLcyscl lcyscl; /* 2842_(10E0 - 10E3h) */

	kuchar dmy10e410e7[0x10E8 - 0x10E4]; /* 2842_(10E4 - 10E7h) */

	IoCnrCsprRegLcysclof lcysclof; /* 2842_(10E8 - 10EFh) */
	IoCnrCsprRegLcysclga lcysclga; /* 2842_(10F0 - 10F7h) */
	IoCnrCsprRegLcysclbd lcysclbd; /* 2842_(10F8 - 10FFh) */
	IoCnrCsprRegLccscl lccscl; /* 2842_(1100 - 1103h) */

	kuchar dmy11041107[0x1108 - 0x1104]; /* 2842_(1104 - 1107h) */

	IoCnrCsprRegLccsclof lccsclof; /* 2842_(1108 - 110Fh) */
	IoCnrCsprRegLccsclga lccsclga; /* 2842_(1110 - 1117h) */
	IoCnrCsprRegLccsclbd lccsclbd; /* 2842_(1118 - 111Fh) */
	IoCnrCsprRegLcsscl lcsscl; /* 2842_(1120 - 1123h) */

	kuchar dmy11241127[0x1128 - 0x1124]; /* 2842_(1124 - 1127h) */

	IoCnrCsprRegLcssclof lcssclof; /* 2842_(1128 - 112Fh) */
	IoCnrCsprRegLcssclga lcssclga; /* 2842_(1130 - 1137h) */
	IoCnrCsprRegLcssclbd lcssclbd; /* 2842_(1138 - 113Fh) */

	kuchar dmy1140115f[0x1160 - 0x1140]; /* 2842_(1140 - 115Fh) */

	IoCnrCsprRegBlend blend; /* 2842_(1160 - 1163h) */

	kuchar dmy11641167[0x1168 - 0x1164]; /* 2842_(1164 - 1167h) */

	IoCnrCsprRegCesclof cesclof; /* 2842_(1168 - 116Fh) */
	IoCnrCsprRegCesclga cesclga; /* 2842_(1170 - 1177h) */
	IoCnrCsprRegCesclbd cesclbd; /* 2842_(1178 - 117Fh) */

	kuchar dmy1180118f[0x11A0 - 0x1190]; /* 2842_(1180 - 118Fh) */

	IoCnrCsprRegCphpt cphpt; /* 2842_(1190 - 1193h) */
	IoCnrCsprRegCphptk cphptk; /* 2842_(1194 - 1197h) */

	kuchar dmy1198119f[0x11A0 - 0x1198]; /* 2842_(1198 - 119Fh) */

	IoCnrCsprRegCdsclof cdsclof; /* 2842_(11A0 - 11ABh) */

	kuchar dmy11ac11af[0x11B0 - 0x11AC]; /* 2842_(11AC - 11AFh) */

	IoCnrCsprRegCdsclga cdsclga; /* 2842_(11B0 - 11BBh) */

	kuchar dmy11bc11bf[0x11C0 - 0x11BC]; /* 2842_(11BC - 11BFh) */

	IoCnrCsprRegCdsclbd cdsclbd; /* 2842_(11C0 - 11CBh) */

	kuchar dmy11cc11cf[0x11D0 - 0x11CC]; /* 2842_(11CC - 11CFh) */

	IoCnrCsprRegWhtmd whtmd; /* 2842_(11D0 - 11D3h) */

	kuchar dmy11d411ff[0x1200 - 0x11D4]; /* 2842_(11D4 - 11FFh) */

	IoCnrCsprRegSprs sprs; /* 2842_(1200 - 1203h) */

	kuchar dmy12041207[0x1208 - 0x1204]; /* 2842_(1204 - 1207h) */

	IoCnrCsprRegSprscbof sprscbof; /* 2842_(1208 - 120Fh) */
	IoCnrCsprRegSprscbga sprscbga; /* 2842_(1210 - 121Bh) */

	kuchar dmy121c121f[0x1220 - 0x121C]; /* 2842_(121C - 121Fh) */

	IoCnrCsprRegSprscbbd sprscbbd; /* 2842_(1220 - 1227h) */
	IoCnrCsprRegSprscrof sprscrof; /* 2842_(1228 - 122Fh) */
	IoCnrCsprRegSprscrga sprscrga; /* 2842_(1230 - 123Bh) */

	kuchar dmy123c123f[0x1240 - 0x123C]; /* 2842_(123C - 123Fh) */

	IoCnrCsprRegSprscrbd sprscrbd; /* 2842_(1240 - 1247h) */

	kuchar dmy1248127f[0x1280 - 0x1248]; /* 2842_(1248 - 127Fh) */

	IoCnrCsprRegSprd sprd; /* 2842_(1280 - 1283h) */

	kuchar dmy12841287[0x1288 - 0x1284]; /* 2842_(1284 - 1287h) */

	IoCnrCsprRegSprdcbof sprdcbof; /* 2842_(1288 - 128Fh) */
	IoCnrCsprRegSprdcbga sprdcbga; /* 2842_(1290 - 129Bh) */

	kuchar dmy129c129f[0x12A0 - 0x129C]; /* 2842_(129C - 129Fh) */

	IoCnrCsprRegSprdcbbd sprdcbbd; /* 2842_(12A0 - 12A7h) */
	IoSnrSsprRegSprdcrof sprdcrof; /* 2842_(12A8 - 12AFh) */
	IoSnrSsprRegSprdcrga sprdcrga; /* 2842_(12B0 - 12BBh) */

	kuchar dmy12bc12bf[0x12C0 - 0x12BC]; /* 2842_(12BC - 12BFh) */

	IoCnrCsprRegSprdcrbd sprdcrbd; /* 2842_(12C0 - 12C7h) */

	kuchar dmy12c81fff[0x2000 - 0x12C8]; /* 2842_(12C8 - 1FFFh) */

} IoCnrCsprReg;

/*	structure of sprsr	(2842_2000h)	*/
typedef union _IoCnrOflRegRwSprsr
{
	kulong word;
	struct
	{
		kulong sr :1;
		kulong :31;
	} bit;
} IoCnrOflRegRwSprsr;

/*	structure of acesen (2842_2004h)	*/
typedef union _IoCnrOflRegRwAcesen
{
	kulong word;
	struct
	{
		kulong spracs :1;
		kulong :31;
	} bit;
} IoCnrOflRegRwAcesen;

/*	structure of sprtrg (2842_2008h)	*/
typedef union _IoCnrOflRegRwSprtrg
{
	kulong word;
	struct
	{
		kulong sprtrg :2;
		kulong :30;
	} bit;
} IoCnrOflRegRwSprtrg;

/*	structure of sprice (2842_200Ch)	*/
typedef union _IoCnrOflRegRwSprice
{
	kulong word;
	struct
	{
		kulong spde :1;
		kulong :3;
		kulong axie :1;
		kulong :27;
	} bit;
} IoCnrOflRegRwSprice;

/*	structure of spricf (2842_2010h)	*/
typedef union _IoCnrOflRegRwSpricf
{
	kulong word;
	struct
	{
		kulong __spdf :1;
		kulong :3;
		kulong __axif :1;
		kulong :27;
	} bit;
} IoCnrOflRegRwSpricf;

/*	structure of VDIV	(2842_2014h)	*/
typedef union _IoCnrOflRegRwVdiv
{
	kulong word;
	struct
	{
		kulong vdivt :1;
		kulong :3;
		kulong vdivb :1;
		kulong :27;
	} bit;
} IoCnrOflRegRwVdiv;

/*	structure of spraxiset	(2842_2020h)	*/
typedef union _IoCnrOflRegRwSpraxiset
{
	kulong word;
	struct
	{
		kulong arcache :4;
		kulong awcache :4;
		kulong arprot :3;
		kulong :1;
		kulong awprot :3;
		kulong :1;
		kulong rresp :2;
		kulong :2;
		kulong wresp :2;
		kulong :10;
	} bit;
} IoCnrOflRegRwSpraxiset;

/*	structure of sprmod (2842_2080h)	*/
typedef union _IoCnrOflRegRwSprmod
{
	kulong word;
	struct
	{
		kulong yuvMode :3;
		kulong :29;
	} bit;
} IoCnrOflRegRwSprmod;

/*	structure of hsize	(2842_2084h)	*/
typedef union _IoCnrOflRegRwHsize
{
	kulong word;
	struct
	{
		kulong hsize :15;
		kulong :17;
	} bit;
} IoCnrOflRegRwHsize;

/*	structure of vsize	(2842_2088h)	*/
typedef union _IoCnrOflRegRwVsize
{
	kulong word;
	struct
	{
		kulong vsize :15;
		kulong :17;
	} bit;
} IoCnrOflRegRwVsize;

/*	structure of ryta	(2842_20A0h)	*/
typedef union _IoCnrOflRegRwRyta
{
	kulong word;
	struct
	{
		kulong ryta :32;
	} bit;
} IoCnrOflRegRwRyta;

/*	structure of rydef	(2842_20A4h)	*/
typedef union _IoCnrOflRegRwRydef
{
	kulong word;
	struct
	{
		kulong rydef :18;
		kulong :14;
	} bit;
} IoCnrOflRegRwRydef;

/*	structure of rcbta	(2842_20A8h)	*/
typedef union _IoCnrOflRegRwRcbta
{
	kulong word;
	struct
	{
		kulong rcbta :32;
	} bit;
} IoCnrOflRegRwRcbta;

/*	structure of rcrta	(2842_20ACh)	*/
typedef union _IoCnrOflRegRwRcrta
{
	kulong word;
	struct
	{
		kulong rcrta :32;
	} bit;
} IoCnrOflRegRwRcrta;

/*	structure of rcdef	(2842_20B0h)	*/
typedef union _IoCnrOflRegRwRcdef
{
	kulong word;
	struct
	{
		kulong rcdef :18;
		kulong :14;
	} bit;
} IoCnrOflRegRwRcdef;

/*	structure of wyta	(2842_20C0h)	*/
typedef union _IoCnrOflRegRwWyta
{
	kulong word;
	struct
	{
		kulong wyta :32;
	} bit;
} IoCnrOflRegRwWyta;

/*	structure of wydef	(2842_20C4h)	*/
typedef union _IoCnrOflRegRwWydef
{
	kulong word;
	struct
	{
		kulong wydef :18;
		kulong :14;
	} bit;
} IoCnrOflRegRwWydef;

/*	structure of wcbta	(2842_20C8h)	*/
typedef union _IoCnrOflRegRwWcbta
{
	kulong word;
	struct
	{
		kulong wcbta :32;
	} bit;
} IoCnrOflRegRwWcbta;

/*	structure of wcrta	(2842_20CCh)	*/
typedef union _IoCnrOflRegRwWcrta
{
	kulong word;
	struct
	{
		kulong wcrta :32;
	} bit;
} IoCnrOflRegRwWcrta;

/*	structure of wcdef	(2842_20D0h)	*/
typedef union _IoCnrOflRegRwWcdef
{
	kulong word;
	struct
	{
		kulong wcdef :18;
		kulong :14;
	} bit;
} IoCnrOflRegRwWcdef;

/*	structure of tmpta	(2842_20E0h)	*/
typedef union _IoCnrOflRegRwTmpta
{
	kulong word;
	struct
	{
		kulong tmpta :32;
	} bit;
} IoCnrOflRegRwTmpta;

/* Define i/o mapping */
typedef struct _IoCnrOflRegRw
{
	/* JDSIMG */
	IoCnrOflRegRwSprsr sprsr; /* 2842_(2000 - 2003h) */
	IoCnrOflRegRwAcesen acesen; /* 2842_(2004 - 2007h) */
	IoCnrOflRegRwSprtrg sprtrg; /* 2842_(2008 - 200Bh) */
	IoCnrOflRegRwSprice sprice; /* 2842_(200C - 200Fh) */
	IoCnrOflRegRwSpricf spricf; /* 2842_(2010 - 2013h) */
	IoCnrOflRegRwVdiv VDIV; /* 2842_(2014 - 2017h) */

	kuchar dmy2018201f[0x2020 - 0x2018]; /* 2842_(2018 - 201Fh) */

	IoCnrOflRegRwSpraxiset spraxiset; /* 2842_(2020 - 2023h) */

	kuchar dmy2024207f[0x2080 - 0x2024]; /* 2842_(2024 - 207Fh) */

	IoCnrOflRegRwSprmod sprmod; /* 2842_(2080 - 2083h) */
	IoCnrOflRegRwHsize hsize; /* 2842_(2084 - 2087h) */
	IoCnrOflRegRwVsize vsize; /* 2842_(2088 - 208Bh) */

	kuchar dmy208c209f[0x20A0 - 0x208C]; /* 2842_(208C - 209Fh) */

	IoCnrOflRegRwRyta ryta; /* 2842_(20A0 - 20A3h) */
	IoCnrOflRegRwRydef rydef; /* 2842_(20A4 - 20A7h) */
	IoCnrOflRegRwRcbta rcbta; /* 2842_(20A8 - 20ABh) */
	IoCnrOflRegRwRcrta rcrta; /* 2842_(20AC - 20AFh) */
	IoCnrOflRegRwRcdef rcdef; /* 2842_(20B0 - 20B3h) */

	kuchar dmy20b420bf[0x20C0 - 0x20B4]; /* 2842_(20B4 - 20BFh) */

	IoCnrOflRegRwWyta wyta; /* 2842_(20C0 - 20C3h) */
	IoCnrOflRegRwWydef wydef; /* 2842_(20C4 - 20C7h) */
	IoCnrOflRegRwWcbta wcbta; /* 2842_(20C8 - 20CBh) */
	IoCnrOflRegRwWcrta wcrta; /* 2842_(20CC - 20CFh) */
	IoCnrOflRegRwWcdef wcdef; /* 2842_(20D0 - 20D3h) */

	kuchar dmy20d420df[0x20E0 - 0x20D4]; /* 2842_(20D4 - 20DFh) */

	IoCnrOflRegRwTmpta tmpta; /* 2842_(20E0 - 20E3h) */

	kuchar dmy20e42fff[0x3000 - 0x20E4]; /* 2842_(20E4 - 2FFFh) */

} IoCnrOflRegRw;

/*	structure of yspren (2842_4000h)	*/
typedef union _IoCnrOflRegYsprYspren
{
	kulong word;
	struct
	{
		kulong yspren :1;
		kulong :31;
	} bit;
} IoCnrOflRegYsprYspren;

/*	structure of ysprmode	(2842_4004h)	*/
typedef union _IoCnrOflRegYsprYsprmode
{
	kulong word;
	struct
	{
		kulong ysprmd :1;
		kulong :3;
		kulong ysprfe :2;
		kulong :26;
	} bit;
} IoCnrOflRegYsprYsprmode;

/*	structure of ysprfxey	(2842_4020h)	*/
typedef union _IoCnrOflRegYsprYsprfxey
{
	kulong word;
	struct
	{
		kulong ysprfxeyh :8;
		kulong :8;
		kulong ysprfxeyv :8;
		kulong :8;
	} bit;
} IoCnrOflRegYsprYsprfxey;

/*	structure of ysprfxec	(2842_4024h)	*/
typedef union _IoCnrOflRegYsprYsprfxec
{
	kulong word;
	struct
	{
		kulong ysprfxech :8;
		kulong :8;
		kulong ysprfxecv :8;
		kulong :8;
	} bit;
} IoCnrOflRegYsprYsprfxec;

/*	structure of yspralpbd	(2842_4028h)	*/
typedef union _IoCnrOflRegYsprYspralpbd
{
	kulong word;
	struct
	{
		kulong yspralpbd :5;
		kulong :27;
	} bit;
} IoCnrOflRegYsprYspralpbd;

/*	structure of ysprdyeyof (2842_4030h)	*/
typedef union _IoCnrOflRegYsprYsprdyeyof1
{
	kulong word;
	struct
	{
		kulong ysprdyeyof0 :8;
		kulong ysprdyeyof1 :8;
		kulong ysprdyeyof2 :8;
		kulong ysprdyeyof3 :8;
	} bit;
} IoCnrOflRegYsprYsprdyeyof1;

typedef union _IoCnrOflRegYsprYsprdyeyof2
{
	kulong word;
	struct
	{
		kulong YSPRDYEYOF_4 :8;
		kulong YSPRDYEYOF_5 :8;
		kulong :16;
	} bit;
} IoCnrOflRegYsprYsprdyeyof2;

typedef struct _IoCnrOflRegYsprYsprdyeyof
{
	IoCnrOflRegYsprYsprdyeyof1 ysprdyeyof1;
	IoCnrOflRegYsprYsprdyeyof2 ysprdyeyof2;
} IoCnrOflRegYsprYsprdyeyof;

/*	structure of ysprdyeyga (2842_4038h)	*/
typedef union _IoCnrOflRegYsprYsprdyeyga1
{
	kulong word;
	struct
	{
		klong ysprdyeyga0 :8;
		klong ysprdyeyga1 :8;
		klong ysprdyeyga2 :8;
		klong ysprdyeyga3 :8;
	} bit;
} IoCnrOflRegYsprYsprdyeyga1;

typedef union _IoCnrOflRegYsprYsprdyeyga2
{
	kulong word;
	struct
	{
		klong ysprdyeyga4 :8;
		klong ysprdyeyga5 :8;
		kulong :16;
	} bit;
} IoCnrOflRegYsprYsprdyeyga2;

typedef struct _IoCnrOflRegYsprYsprdyeyga
{
	IoCnrOflRegYsprYsprdyeyga1 ysprdyeyga1;
	IoCnrOflRegYsprYsprdyeyga2 ysprdyeyga2;
} IoCnrOflRegYsprYsprdyeyga;

/*	structure of ysprdyeybd (2842_4040h)	*/
typedef union _IoCnrOflRegYsprYsprdyeybd1
{
	kulong word;
	struct
	{
		kulong ysprdyeybd1 :8;
		kulong ysprdyeybd2 :8;
		kulong ysprdyeybd3 :8;
		kulong ysprdyeybd4 :8;
	} bit;
} IoCnrOflRegYsprYsprdyeybd1;

typedef union _IoCnrOflRegYsprYsprdyeybd2
{
	kulong word;
	struct
	{
		kulong ysprdyeybd5 :8;
		kulong :24;
	} bit;
} IoCnrOflRegYsprYsprdyeybd2;

typedef struct _IoCnrOflRegYsprYsprdyeybd
{
	IoCnrOflRegYsprYsprdyeybd1 ysprdyeybd1;
	IoCnrOflRegYsprYsprdyeybd2 ysprdyeybd2;
} IoCnrOflRegYsprYsprdyeybd;

/* Define i/o mapping */
typedef struct _IoCnrOflRegYspr
{
	/* JDSIMG */
	IoCnrOflRegYsprYspren yspren; /* 2842_(4000 - 4003h) */
	IoCnrOflRegYsprYsprmode ysprmode; /* 2842_(4004 - 4007h) */

	kuchar dmy4008401f[0x4020 - 0x4008]; /* 2842_(4008 - 401Fh) */

	IoCnrOflRegYsprYsprfxey ysprfxey; /* 2842_(4020 - 4023h) */
	IoCnrOflRegYsprYsprfxec ysprfxec; /* 2842_(4024 - 4027h) */
	IoCnrOflRegYsprYspralpbd yspralpbd; /* 2842_(4028 - 402Bh) */

	kuchar dmy_402C_402F[0x4030 - 0x402C]; /* 2842_(402C - 402Fh) */

	IoCnrOflRegYsprYsprdyeyof ysprdyeyof; /* 2842_(4030 - 4037h) */
	IoCnrOflRegYsprYsprdyeyga ysprdyeyga; /* 2842_(4038 - 403Fh) */
	IoCnrOflRegYsprYsprdyeybd ysprdyeybd; /* 2842_(4040 - 4047h) */

	kuchar dmy40484fff[0x5000 - 0x4048]; /* 2842_(4048 - 4FFFh) */

} IoCnrOflRegYspr;

/* Define i/o mapping */
typedef struct _IoCnrReg
{
	/* JDSIMG */
	/* 2842_(0000 - 0FFFh) */
	IoCnrOtfRegRw otfRegRw;
	/* 2842_(1000 - 1FFFh) */
	IoCnrCsprReg otfCsprReg;
	/* 2842_(2000 - 2FFFh) */
	IoCnrOflRegRw oflRegRw;
	/* 2842_(3000 - 3FFFh) */
	IoCnrCsprReg oflCsprReg;
	/* 2842_(4000 - 4FFFh) */
	IoCnrOflRegYspr oflRegYspr;
	/* 2842_5000 - 2842_FFFFh */
	kuchar dmy284250002842ffff[0x28430000 - 0x28425000];

} IoCnrReg;


extern volatile IoCnrReg ioCnr1;
extern volatile IoCnrReg ioCnr2;
extern volatile IoCnrReg ioCnr3;


KConstType k_jdscnr1a_get_type(void);
KJdscnr1a* k_jdscnr1a_new(void);


#endif/*__K_JDSCNR1A_H__*/

