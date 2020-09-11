/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-11
*@author            :陈倩
*@brief             :kjdsiip4b1
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


#ifndef __K_JDSIIP4B1_H__
#define __K_JDSIIP4B1_H__


#include <klib.h>


#define K_TYPE_JDSIIP4B1				(k_jdsiip4b1_get_type())
#define K_JDSIIP4B1(obj)					(K_TYPE_CHECK_INSTANCE_CAST((obj), KJdsiip4b1))
#define K_IS_JDSIIP4B1(obj)			(K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_JDSIIP4B1))


typedef struct _KJdsiip4b1				KJdsiip4b1;
typedef struct _KJdsiip4b1Private	KJdsiip4b1Private;


struct  _KJdsiip4b1
{
	KObject parent;
};


/*  structure of pixfmttbl0    (2888_0300h)    */
typedef union _IoIipIpxfmttbl0
{
	unsigned long word;
	struct
	{
		unsigned long p :1;
		unsigned long :3;
		unsigned long ftype :3;
		unsigned long :1;
		unsigned long pfmt :4;
		unsigned long alpha :1;
		unsigned long :3;
		unsigned long pdepth :3;
		unsigned long :1;
		unsigned long adepth :3;
		unsigned long :1;
		unsigned long chkyordr :8;
	} bit;
} IoIipIpxfmttbl0;

/*  structure of pixfmttbl1    (2888_0304h)    */
typedef union _IoIipIpxfmttbl1
{
	unsigned long word;
	struct
	{
		unsigned long sgyg :1;
		unsigned long sgb :1;
		unsigned long sgr :1;
		unsigned long sga :1;
		unsigned long asubspl :2;
		unsigned long :2;
		unsigned long mtifyg :2;
		unsigned long mtifb :2;
		unsigned long mtifr :2;
		unsigned long mtifa :2;
		unsigned long oarbhv :1;
		unsigned long :15;
	} bit;
} IoIipIpxfmttbl1;

/*  structure of pixfmttbl2    (2888_0308h)    */
typedef union _IoIipIpxfmttbl2
{
	unsigned long word;
	struct
	{
		unsigned long oarvalyg :16;
		unsigned long oarvalb :16;
	} bit;
} IoIipIpxfmttbl2;

/*  structure of pixfmttbl3    (2888_030Ch)    */
typedef union _IoIipIpxfmttbl3
{
	unsigned long word;
	struct
	{
		unsigned long oarvalr :16;
		unsigned long oarvala :16;
	} bit;
} IoIipIpxfmttbl3;

/*  structure of pixfmttbl4    (2888_0310h)    */
typedef union _IoIipIpxfmttbl4
{
	unsigned long word;
	struct
	{
		long ghszyg :18;
		unsigned long :14;
	} bit;
} IoIipIpxfmttbl4;

/*  structure of pixfmttbl5    (2888_0314h)    */
typedef union _IoIipIpxfmttbl5
{
	unsigned long word;
	struct
	{
		long ghszb :18;
		unsigned long :14;
	} bit;
} IoIipIpxfmttbl5;

/*  structure of pixfmttbl6    (2888_0318h)    */
typedef union _IoIipIpxfmttbl6
{
	unsigned long word;
	struct
	{
		long ghszr :18;
		unsigned long :14;
	} bit;
} IoIipIpxfmttbl6;

/*  structure of pixfmttbl7    (2888_031Ch)    */
typedef union _IoIipIpxfmttbl7
{
	unsigned long word;
	struct
	{
		long ghsza :18;
		unsigned long :14;
	} bit;
} IoIipIpxfmttbl7;

/*  structure of pixfmttbl8    (2888_0320h)    */
typedef union _IoIipIpxfmttbl8
{
	unsigned long word;
	struct
	{
		unsigned long pichsz :15;
		unsigned long :1;
		unsigned long picvsz :14;
		unsigned long :2;
	} bit;
} IoIipIpxfmttbl8;

/*  structure of pixfmttbl9    (2888_0324h)    */
typedef union _IoIipIpxfmttbl9
{
	unsigned long word;
	struct
	{
		unsigned long adrsyg :32;
	} bit;
} IoIipIpxfmttbl9;

/*  structure of pixfmttbl10   (2888_0328h)    */
typedef union _IoIipIpxfmttbl10
{
	unsigned long word;
	struct
	{
		unsigned long adrsb :32;
	} bit;
} IoIipIpxfmttbl10;

/*  structure of pixfmttbl11   (2888_032Ch)    */
typedef union _IoIipIpxfmttbl11
{
	unsigned long word;
	struct
	{
		unsigned long adrsr :32;
	} bit;
} IoIipIpxfmttbl11;

/*  structure of pixfmttbl12   (2888_0330h)    */
typedef union _IoIipIpxfmttbl12
{
	unsigned long word;
	struct
	{
		unsigned long adrsa :32;
	} bit;
} IoIipIpxfmttbl12;

/* Define i/o mapping */
typedef struct _IoIipPixfmttbl
{
	/* JDSIMG */
	IoIipIpxfmttbl0 pixfmttbl0; /* 2888_(0300 - 0303h) */
	IoIipIpxfmttbl1 pixfmttbl1; /* 2888_(0304 - 0307h) */
	IoIipIpxfmttbl2 pixfmttbl2; /* 2888_(0308 - 030Bh) */
	IoIipIpxfmttbl3 pixfmttbl3; /* 2888_(030C - 030Fh) */
	IoIipIpxfmttbl4 pixfmttbl4; /* 2888_(0310 - 0313h) */
	IoIipIpxfmttbl5 pixfmttbl5; /* 2888_(0314 - 0317h) */
	IoIipIpxfmttbl6 pixfmttbl6; /* 2888_(0318 - 031Bh) */
	IoIipIpxfmttbl7 pixfmttbl7; /* 2888_(031C - 031Fh) */
	IoIipIpxfmttbl8 pixfmttbl8; /* 2888_(0320 - 0323h) */
	IoIipIpxfmttbl9 pixfmttbl9; /* 2888_(0324 - 0327h) */
	IoIipIpxfmttbl10 pixfmttbl10; /* 2888_(0328 - 032Bh) */
	IoIipIpxfmttbl11 pixfmttbl11; /* 2888_(032C - 032Fh) */
	IoIipIpxfmttbl12 pixfmttbl12; /* 2888_(0330 - 0333h) */

	unsigned char dmy0334033f[0x0340 - 0x0334]; /* 2888_(0334 - 033Fh) */

} IoIipPixfmttbl;

/*  structure of unitinftbl0    (2888_0940h)    */
typedef union _IoIipUinftbl0
{
	unsigned long word;
	struct
	{
		unsigned long swtrg :2;
		unsigned long :2;
		unsigned long hwen :1;
		unsigned long :3;
		unsigned long chain :1;
		unsigned long :23;
	} bit;
} IoIipUinftbl0;

/*  structure of unitinftbl1    (2888_0948h)    */
typedef union _IoIipUinftbl1
{
	unsigned long word[2];
	struct
	{
		unsigned long pldunitLo :32;
		unsigned long pldunitHi :32;
	} bit;
} IoIipUinftbl1;

/*  structure of unitinftbl2    (2888_0950h)    */
typedef union _IoIipUinftbl2
{
	unsigned long word;
	struct
	{
		unsigned long padrs :32;
	} bit;
} IoIipUinftbl2;

/*  structure of unitsr (2888_0954h)    */
typedef union _IoIipUinftblUnitsr
{
	unsigned long word;
	struct
	{
		unsigned long unitsr :1;
		unsigned long :31;
	} bit;
} IoIipUinftblUnitsr;

/* Define i/o mapping */
typedef struct _IoIipUinftbl
{
	/* JDSIMG */
	IoIipUinftbl0 unitinftbl0; /* 2888_(0940 - 0943h) */

	unsigned char dmy09440947[0x0948 - 0x0944]; /* 2888_(0944 - 0947h) */

	IoIipUinftbl1 unitinftbl1; /* 2888_(0948 - 094Fh) */
	IoIipUinftbl2 unitinftbl2; /* 2888_(0950 - 0953h) */
	IoIipUinftblUnitsr unitsr; /* 2888_(0954 - 0957h) */

	unsigned char dmy0958095f[0x0960 - 0x0958]; /* 2888_(0958 - 095Fh) */

} IoIipUinftbl;

/*  structure of lutram (2982_0000h)    */
typedef union _IoIipLutram
{
	unsigned long word[6][1024];
	struct
	{
		unsigned long lut :14;
		unsigned long :18;
	} bit[6][1024];
} IoIipLutram;


KConstType	k_jdsiip4b1_get_type(void);
KJdsiip4b1*	k_jdsiip4b1_new(void);


#endif/*__K_JDSIIP4B1_H__*/

