/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-11
*@author            :陈倩
*@brief             :kjdsmxic1
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


#ifndef __K_JDSMXIC1_H__
#define __K_JDSMXIC1_H__


#include <klib.h>


#define K_TYPE_JDSMXIC1				(k_jdsmxic1_get_type())
#define K_JDSMXIC1(obj)					(K_TYPE_CHECK_INSTANCE_CAST((obj), KJdsmxic1))
#define K_IS_JDSMXIC1(obj)			(K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_JDSMXIC1))


typedef struct _KJdsmxic1				KJdsmxic1;
typedef struct _KJdsmxic1Private	KJdsmxic1Private;


struct  _KJdsmxic1
{
	KObject parent;
};


/*  structure of TSLW		*/
typedef union _IoMxicTslw
{
	unsigned char byte[4][16];
	struct
	{
		unsigned char slotw :7;
		unsigned char :1;
	} bit[4][16];
} IoMxicTslw;

/*  structure of TSLR		*/
typedef union _IoMxicTslr
{
	unsigned char byte[4][16];
	struct
	{
		unsigned char slotr :7;
		unsigned char :1;
	} bit[4][16];
} IoMxicTslr;

/* Define i/o mapping */
typedef struct _IoJdsmxicTbl
{
	/* JDSIMG */
	IoMxicTslw tslw1[4]; /* 29x0_(0000 - 00FFh) */
	IoMxicTslw tslw2[4]; /* 29x0_(0100 - 01FFh) */
	IoMxicTslw tslw3[4]; /* 29x0_(0200 - 02FFh) */
	IoMxicTslw tslw4[4]; /* 29x0_(0300 - 03FFh) */
	IoMxicTslr tslr1[4]; /* 29x0_(0400 - 04FFh) */
	IoMxicTslr tslr2[4]; /* 29x0_(0500 - 05FFh) */
	IoMxicTslr tslr3[4]; /* 29x0_(0600 - 06FFh) */
	IoMxicTslr tslr4[4]; /* 29x0_(0700 - 07FFh) */

	unsigned char dmy29x0080029x0ffff[0x10000 - 0x0800]; /* 29x0_(0800 - FFFFh) */
} IoJdsmxicTbl;

/*	structure of tmirst		*/
typedef union _IoMxicTmirst
{
	unsigned long word;
	struct
	{
		unsigned long sr :1;
		unsigned long :31;
	} bit;
} IoMxicTmirst;

/*	structure of tcken		*/
typedef union _IoMxicTcken
{
	unsigned long word;
	struct
	{
		unsigned long tcksen :1;
		unsigned long :7;
		unsigned long tckmen :1;
		unsigned long :23;
	} bit;
} IoMxicTcken;


KConstType	k_jdsmxic1_get_type(void);
KJdsmxic1*	k_jdsmxic1_new(void);


#endif/*__K_JDSMXIC1_H__*/

