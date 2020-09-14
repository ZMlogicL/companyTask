/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-14
*@author            :陈倩
*@brief             :kjdscnr1a1
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


#ifndef __K_JDSCNR1A1_H__
#define __K_JDSCNR1A1_H__


#include <klib.h>


#define K_TYPE_JDSCNR1A1			(k_jdscnr1a1_get_type())
#define K_JDSCNR1A1(obj)				(K_TYPE_CHECK_INSTANCE_CAST((obj), KJdscnr1a1))
#define K_IS_JDSCNR1A1(obj)			(K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_JDSCNR1A1))


typedef struct _KJdscnr1a1				KJdscnr1a1;
typedef struct _KJdscnr1a1Private	KJdscnr1a1Private;

struct  _KJdscnr1a1
{
	KObject parent;
};


/*	structure of sprsr	(2842_0000h)	*/
typedef union _IoCnrOtfRegRwSprsr
{
	kulong word;
	struct
	{
		kulong sr :1;
		kulong :31;
	} bit;
} IoCnrOtfRegRwSprsr;

/*	structure of acesen (2842_0004h)	*/
typedef union _IoCnrOtfRegRwAcesen
{
	kulong word;
	struct
	{
		kulong spracs :1;
		kulong :31;
	} bit;
} IoCnrOtfRegRwAcesen;

/*	structure of sprtrg (2842_0008h)	*/
typedef union _IoCnrOtfRegRwSprtrg
{
	kulong word;
	struct
	{
		kulong sprtrg :2;
		kulong :2;
		kulong cnrcse :1;
		kulong :27;
	} bit;
} IoCnrOtfRegRwSprtrg;

/*	structure of sprice (2842_000Ch)	*/
typedef union _IoCnrOtfRegRwSprice
{
	kulong word;
	struct
	{
		kulong spde :1;
		kulong :3;
		kulong axie :1;
		kulong :3;
		kulong drte :1;
		kulong :23;
	} bit;
} IoCnrOtfRegRwSprice;

/*	structure of spricf (2842_0010h)	*/
typedef union _IoCnrOtfRegRwSpricf
{
	kulong word;
	struct
	{
		kulong __spdf :1;
		kulong :3;
		kulong __axif :1;
		kulong :3;
		kulong __drtf :1;
		kulong :23;
	} bit;
} IoCnrOtfRegRwSpricf;

/*	structure of hdiv	(2842_0014h)	*/
typedef union _IoCnrOtfRegRwHdiv
{
	kulong word;
	struct
	{
		kulong hdivl :1;
		kulong :3;
		kulong hdivr :1;
		kulong :27;
	} bit;
} IoCnrOtfRegRwHdiv;

/*	structure of spraxiset	(2842_0020h)	*/
typedef union _IoCnrOtfRegRwSpraxiset
{
	kulong word;
	struct
	{
		kulong :4;
		kulong awcache :4;
		kulong :3;
		kulong :1;
		kulong awprot :3;
		kulong :1;
		kulong :2;
		kulong :2;
		kulong wresp :2;
		kulong :10;
	} bit;
} IoCnrOtfRegRwSpraxiset;

/*	structure of sprmod (2842_0080h)	*/
typedef union _IoCnrOtfRegRwSprmod
{
	kulong word;
	struct
	{
		kulong yuvMode :3;
		kulong :1;
		kulong exmode :1;
		kulong :3;
		kulong cnrvfm :1;
		kulong :23;
	} bit;
} IoCnrOtfRegRwSprmod;

/*	structure of hsize	(2842_0084h)	*/
typedef union _IoCnrOtfRegRwHsize
{
	kulong word;
	struct
	{
		kulong hsize :12;
		kulong :20;
	} bit;
} IoCnrOtfRegRwHsize;

/*	structure of vsize	(2842_0088h)	*/
typedef union _IoCnrOtfRegRwVsize
{
	kulong word;
	struct
	{
		kulong vsize :13;
		kulong :19;
	} bit;
} IoCnrOtfRegRwVsize;

/*	structure of wcta	(2842_00A0h)	*/
typedef union _IoCnrOtfRegRwWcta
{
	kulong word;
	struct
	{
		kulong wcta :32;
	} bit;
} IoCnrOtfRegRwWcta;

/*	structure of wcdef	(2842_00A4h)	*/
typedef union _IoCnrOtfRegRwWcdef
{
	kulong word;
	struct
	{
		kulong wcdef :18;
		kulong :14;
	} bit;
} IoCnrOtfRegRwWcdef;

/*	structure of cnrwofsx	(2842_00A8h)	*/
typedef union _IoCnrOtfRegRwCnrwofsx
{
	kulong word;
	struct
	{
		kulong cnrwofsx :12;
		kulong :20;
	} bit;
} IoCnrOtfRegRwCnrwofsx;

/* Define i/o mapping */
typedef struct _IoCnrOtfRegRw
{
	/* JDSIMG */
	IoCnrOtfRegRwSprsr sprsr; /* 2842_(0000 - 0003h) */
	IoCnrOtfRegRwAcesen acesen; /* 2842_(0004 - 0007h) */
	IoCnrOtfRegRwSprtrg sprtrg; /* 2842_(0008 - 000Bh) */
	IoCnrOtfRegRwSprice sprice; /* 2842_(000C - 000Fh) */
	IoCnrOtfRegRwSpricf spricf; /* 2842_(0010 - 0013h) */
	IoCnrOtfRegRwHdiv hdiv; /* 2842_(0014 - 0017h) */

	kuchar dmy0018001f[0x0020 - 0x0018]; /* 2842_(0018 - 001Fh) */

	IoCnrOtfRegRwSpraxiset spraxiset; /* 2842_(0020 - 0023h) */

	kuchar dmy0024007f[0x0080 - 0x0024]; /* 2842_(0024 - 007Fh) */

	IoCnrOtfRegRwSprmod sprmod; /* 2842_(0080 - 0083h) */
	IoCnrOtfRegRwHsize hsize; /* 2842_(0084 - 0087h) */
	IoCnrOtfRegRwVsize vsize; /* 2842_(0088 - 008Bh) */

	kuchar dmy008c009f[0x00A0 - 0x008C]; /* 2842_(008C - 009Fh) */

	IoCnrOtfRegRwWcta wcta; /* 2842_(00A0 - 00A3h) */
	IoCnrOtfRegRwWcdef wcdef; /* 2842_(00A4 - 00A7h) */
	IoCnrOtfRegRwCnrwofsx cnrwofsx; /* 2842_(00A8 - 00ABh) */

	kuchar dmy00ac0fff[0x1000 - 0x00AC]; /* 2842_(00AC - 0FFFh) */

} IoCnrOtfRegRw;

/*	structure of cspren (2842_1000h)	*/
typedef union _IoCnrCsprRegCspren
{
	kulong word;
	struct
	{
		kulong cspren :1;
		kulong :31;
	} bit;
} IoCnrCsprRegCspren;

/*	structure of cgdken (2842_1008h)	*/
typedef union _IoCnrCsprRegCgdken
{
	kulong word;
	struct
	{
		kulong cgdken :1;
		kulong :31;
	} bit;
} IoCnrCsprRegCgdken;

/*	structure of mcen	(2842_1020h)	*/
typedef union _IoCnrCsprRegMcen
{
	kulong word;
	struct
	{
		kulong mcen :1;
		kulong :31;
	} bit;
} IoCnrCsprRegMcen;

/*	structure of mcythh (2842_1024h)	*/
typedef union _IoCnrCsprRegMcythh
{
	kulong word;
	struct
	{
		kulong mcythh0 :8;
		kulong mcythh1 :8;
		kulong mcythh2 :8;
		kulong mcythh3 :8;
	} bit;
} IoCnrCsprRegMcythh;

/*	structure of mcythv (2842_1028h)	*/
typedef union _IoCnrCsprRegMcythv
{
	kulong word;
	struct
	{
		kulong mcythv0 :8;
		kulong mcythv1 :8;
		kulong mcythv2 :8;
		kulong mcythv3 :8;
	} bit;
} IoCnrCsprRegMcythv;

/*	structure of mccthh (2842_102Ch)	*/
typedef union _IoCnrCsprRegMccthh
{
	kulong word;
	struct
	{
		kulong mccthh0 :8;
		kulong mccthh1 :8;
		kulong mccthh2 :8;
		kulong mccthh3 :8;
	} bit;
} IoCnrCsprRegMccthh;

/*	structure of mccthv (2842_1030h)	*/
typedef union _IoCnrCsprRegMccthv
{
	kulong word;
	struct
	{
		kulong mccthv0 :8;
		kulong mccthv1 :8;
		kulong mccthv2 :8;
		kulong mccthv3 :8;
	} bit;
} IoCnrCsprRegMccthv;

/*	structure of mcydym (2842_1034h)	*/
typedef union _IoCnrCsprRegMcydym
{
	kulong word;
	struct
	{
		kulong mcydym :1;
		kulong :31;
	} bit;
} IoCnrCsprRegMcydym;

/*	structure of mcydymdt	(2842_1038h)	*/
typedef union _IoCnrCsprRegMcydymdt
{
	kulong word;
	struct
	{
		kulong mcydymycr :8;
		kulong :8;
		kulong mcydymyg :9;
		kulong :7;
	} bit;
} IoCnrCsprRegMcydymdt;

/*	structure of mcyscl (2842_1040h)	*/
typedef union _IoCnrCsprRegMcyscl
{
	kulong word;
	struct
	{
		kulong mcyscl :1;
		kulong :31;
	} bit;
} IoCnrCsprRegMcyscl;

/*	structure of mcysclof	(2842_1048h)	*/
typedef union _IoCnrCsprRegMcysclof1
{
	kulong word;
	struct
	{
		kulong mcysclof0 :8;
		kulong mcysclof1 :8;
		kulong mcysclof2 :8;
		kulong mcysclof3 :8;
	} bit;
} IoCnrCsprRegMcysclof1;

typedef union _IoCnrCsprRegMcysclof2
{
	kulong word;
	struct
	{
		kulong mcysclof4 :8;
		kulong mcysclof5 :8;
		kulong :16;
	} bit;
} IoCnrCsprRegMcysclof2;

typedef struct _IoCnrCsprRegMcysclof
{
	IoCnrCsprRegMcysclof1 mcysclof1;
	IoCnrCsprRegMcysclof2 mcysclof2;
} IoCnrCsprRegMcysclof;

/*	structure of mcysclga	(2842_1050h)	*/
typedef union _IoCnrCsprRegMcysclga1
{
	kulong word;
	struct
	{
		klong mcysclga0 :8;
		klong mcysclga1 :8;
		klong mcysclga2 :8;
		klong mcysclga3 :8;
	} bit;
} IoCnrCsprRegMcysclga1;

typedef union _IoCnrCsprRegMcysclga2
{
	kulong word;
	struct
	{
		klong mcysclga4 :8;
		klong mcysclga5 :8;
		kulong :16;
	} bit;
} IoCnrCsprRegMcysclga2;

typedef struct _IoCnrCsprRegMcysclga
{
	IoCnrCsprRegMcysclga1 mcysclga1;
	IoCnrCsprRegMcysclga2 mcysclga2;
} IoCnrCsprRegMcysclga;

/*	structure of mcysclbd	(2842_1058h)	*/
typedef union _IoCnrCsprRegMcysclbd1
{
	kulong word;
	struct
	{
		kulong mcysclbd1 :8;
		kulong mcysclbd2 :8;
		kulong mcysclbd3 :8;
		kulong mcysclbd4 :8;
	} bit;
} IoCnrCsprRegMcysclbd1;

typedef union _IoCnrCsprRegMcysclbd2
{
	kulong word;
	struct
	{
		kulong mcysclbd5 :8;
		kulong :24;
	} bit;
} IoCnrCsprRegMcysclbd2;

typedef struct _IoCnrCsprRegMcysclbd
{
	IoCnrCsprRegMcysclbd1 mcysclbd1;
	IoCnrCsprRegMcysclbd2 mcysclbd2;
} IoCnrCsprRegMcysclbd;

/*	structure of mccscl (2842_1060h)	*/
typedef union _IoCnrCsprRegMccscl
{
	kulong word;
	struct
	{
		kulong mccscl :1;
		kulong :31;
	} bit;
} IoCnrCsprRegMccscl;

/*	structure of mccsclof	(2842_1068h)	*/
typedef union _IoCnrCsprRegMccsclof1
{
	kulong word;
	struct
	{
		kulong mccsclof0 :8;
		kulong mccsclof1 :8;
		kulong mccsclof2 :8;
		kulong mccsclof3 :8;
	} bit;
} IoCnrCsprRegMccsclof1;

typedef union _IoCnrCsprRegMccsclof2
{
	kulong word;
	struct
	{
		kulong mccsclof4 :8;
		kulong mccsclof5 :8;
		kulong :16;
	} bit;
} IoCnrCsprRegMccsclof2;

typedef struct _IoCnrCsprRegMccsclof
{
	IoCnrCsprRegMccsclof1 mccsclof1;
	IoCnrCsprRegMccsclof2 mccsclof2;
} IoCnrCsprRegMccsclof;

/*	structure of mccsclga	(2842_1070h)	*/
typedef union _IoCnrCsprRegMccsclga1
{
	kulong word;
	struct
	{
		klong mccsclga0 :8;
		klong mccsclga1 :8;
		klong mccsclga2 :8;
		klong mccsclga3 :8;
	} bit;
} IoCnrCsprRegMccsclga1;

typedef union _IoCnrCsprRegMccsclga2
{
	kulong word;
	struct
	{
		klong mccsclga4 :8;
		klong mccsclga5 :8;
		kulong :16;
	} bit;
} IoCnrCsprRegMccsclga2;

typedef struct _IoCnrCsprRegMccsclga
{
	IoCnrCsprRegMccsclga1 mccsclga1;
	IoCnrCsprRegMccsclga2 mccsclga2;
} IoCnrCsprRegMccsclga;

/*	structure of mccsclbd	(2842_1078h)	*/
typedef union _IoCnrCsprRegMccsclbd1
{
	kulong word;
	struct
	{
		kulong mccsclbd1 :8;
		kulong mccsclbd2 :8;
		kulong mccsclbd3 :8;
		kulong mccsclbd4 :8;
	} bit;
} IoCnrCsprRegMccsclbd1;

typedef union _IoCnrCsprRegMccsclbd2
{
	kulong word;
	struct
	{
		kulong mccsclbd5 :8;
		kulong :24;
	} bit;
} IoCnrCsprRegMccsclbd2;

typedef struct _IoCnrCsprRegMccsclbd
{
	IoCnrCsprRegMccsclbd1 mccsclbd1;
	IoCnrCsprRegMccsclbd2 mccsclbd2;
} IoCnrCsprRegMccsclbd;

/*	structure of mcsscl (2842_1080h)	*/
typedef union _IoCnrCsprRegMcsscl
{
	kulong word;
	struct
	{
		kulong mcsscl :1;
		kulong :31;
	} bit;
} IoCnrCsprRegMcsscl;

/*	structure of mcssclof	(2842_1088h)	*/
typedef union _IoCnrCsprRegMcssclof1
{
	kulong word;
	struct
	{
		kulong mcssclof0 :8;
		kulong mcssclof1 :8;
		kulong mcssclof2 :8;
		kulong mcssclof3 :8;
	} bit;
} IoCnrCsprRegMcssclof1;

typedef union _IoCnrCsprRegMcssclof2
{
	kulong word;
	struct
	{
		kulong mcssclof4 :8;
		kulong mcssclof5 :8;
		kulong :16;
	} bit;
} IoCnrCsprRegMcssclof2;

typedef struct _IoCnrCsprRegMcssclof
{
	IoCnrCsprRegMcssclof1 mcssclof1;
	IoCnrCsprRegMcssclof2 mcssclof2;
} IoCnrCsprRegMcssclof;

/*	structure of mcssclga	(2842_1090h)	*/
typedef union _IoCnrCsprRegMcssclga1
{
	kulong word;
	struct
	{
		klong mcssclga0 :8;
		klong mcssclga1 :8;
		klong mcssclga2 :8;
		klong mcssclga3 :8;
	} bit;
} IoCnrCsprRegMcssclga1;

typedef union _IoCnrCsprRegMcssclga2
{
	kulong word;
	struct
	{
		klong mcssclga4 :8;
		klong mcssclga5 :8;
		kulong :16;
	} bit;
} IoCnrCsprRegMcssclga2;

typedef struct _IoCnrCsprRegMcssclga
{
	IoCnrCsprRegMcssclga1 mcssclga1;
	IoCnrCsprRegMcssclga2 mcssclga2;
} IoCnrCsprRegMcssclga;

/*	structure of mcssclbd	(2842_1098h)	*/
typedef union _IoCnrCsprRegMcssclbd1
{
	kulong word;
	struct
	{
		kulong mcssclbd1 :8;
		kulong mcssclbd2 :8;
		kulong mcssclbd3 :8;
		kulong mcssclbd4 :8;
	} bit;
} IoCnrCsprRegMcssclbd1;

typedef union _IoCnrCsprRegMcssclbd2
{
	kulong word;
	struct
	{
		kulong mcssclbd5 :8;
		kulong :24;
	} bit;
} IoCnrCsprRegMcssclbd2;

typedef struct _IoCnrCsprRegMcssclbd
{
	IoCnrCsprRegMcssclbd1 mcssclbd1;
	IoCnrCsprRegMcssclbd2 mcssclbd2;
} IoCnrCsprRegMcssclbd;

/*	structure of lcen	(2842_10C0h)	*/
typedef union _IoCnrCsprRegLcen
{
	kulong word;
	struct
	{
		kulong lcen :1;
		kulong :31;
	} bit;
} IoCnrCsprRegLcen;

/*	structure of lcythh (2842_10C4h)	*/
typedef union _IoCnrCsprRegLcythh
{
	kulong word;
	struct
	{
		kulong lcythh0 :8;
		kulong lcythh1 :8;
		kulong lcythh2 :8;
		kulong lcythh3 :8;
	} bit;
} IoCnrCsprRegLcythh;

/*	structure of lcythv (2842_10C8h)	*/
typedef union _IoCnrCsprRegLcythv
{
	kulong word;
	struct
	{
		kulong lcythv0 :8;
		kulong lcythv1 :8;
		kulong lcythv2 :8;
		kulong lcythv3 :8;
	} bit;
} IoCnrCsprRegLcythv;

/*	structure of lccthh (2842_10CCh)	*/
typedef union _IoCnrCsprRegLccthh
{
	kulong word;
	struct
	{
		kulong lccthh0 :8;
		kulong lccthh1 :8;
		kulong lccthh2 :8;
		kulong lccthh3 :8;
	} bit;
} IoCnrCsprRegLccthh;

/*	structure of lccthv (2842_10D0h)	*/
typedef union _IoCnrCsprRegLccthv
{
	kulong word;
	struct
	{
		kulong lccthv0 :8;
		kulong lccthv1 :8;
		kulong lccthv2 :8;
		kulong lccthv3 :8;
	} bit;
} IoCnrCsprRegLccthv;

/*	structure of lcydym (2842_10D4h)	*/
typedef union _IoCnrCsprRegLcydym
{
	kulong word;
	struct
	{
		kulong lcydym :1;
		kulong :31;
	} bit;
} IoCnrCsprRegLcydym;

/*	structure of lcydymdt	(2842_10D8h)	*/
typedef union _IoCnrCsprRegLcydymdt
{
	kulong word;
	struct
	{
		kulong lcydymycr :8;
		kulong :8;
		kulong lcydymyg :9;
		kulong :7;
	} bit;
} IoCnrCsprRegLcydymdt;

/*	structure of lcyscl (2842_10E0h)	*/
typedef union _IoCnrCsprRegLcyscl
{
	kulong word;
	struct
	{
		kulong lcyscl :1;
		kulong :31;
	} bit;
} IoCnrCsprRegLcyscl;

/*	structure of lcysclof	(2842_10E8h)	*/
typedef union _IoCnrCsprRegLcysclof1
{
	kulong word;
	struct
	{
		kulong lcysclof0 :8;
		kulong lcysclof1 :8;
		kulong lcysclof2 :8;
		kulong lcysclof3 :8;
	} bit;
} IoCnrCsprRegLcysclof1;

typedef union _IoCnrCsprRegLcysclof2
{
	kulong word;
	struct
	{
		kulong lcysclof4 :8;
		kulong lcysclof5 :8;
		kulong :16;
	} bit;
} IoCnrCsprRegLcysclof2;

typedef struct _IoCnrCsprRegLcysclof
{
	IoCnrCsprRegLcysclof1 lcysclof1;
	IoCnrCsprRegLcysclof2 lcysclof2;
} IoCnrCsprRegLcysclof;

/*	structure of lcysclga	(2842_10F0h)	*/
typedef union _IoCnrCsprRegLcysclga1
{
	kulong word;
	struct
	{
		klong lcysclga0 :8;
		klong lcysclga1 :8;
		klong lcysclga2 :8;
		klong lcysclga3 :8;
	} bit;
} IoCnrCsprRegLcysclga1;

typedef union _IoCnrCsprRegLcysclga2
{
	kulong word;
	struct
	{
		klong lcysclga4 :8;
		klong lcysclga5 :8;
		kulong :16;
	} bit;
} IoCnrCsprRegLcysclga2;

typedef struct _IoCnrCsprRegLcysclga
{
	IoCnrCsprRegLcysclga1 lcysclga1;
	IoCnrCsprRegLcysclga2 lcysclga2;
} IoCnrCsprRegLcysclga;


KConstType	k_jdscnr1a1_get_type(void);
KJdscnr1a1*	k_jdscnr1a1_new(void);


#endif/*__K_JDSCNR1A1_H__*/

