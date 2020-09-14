/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-07
 *@author            :陈倩
 *@brief             :kjdsltm1a
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


#ifndef __K_JDSLTM1A_H__
#define __K_JDSLTM1A_H__


#include <klib.h>
#include "__jdsltm1a_rbk.h"
#include "__jdsltm1a_map.h"
#include "__jdsltm1a_ltm.h"
//#include "__jdsltm1a_sram_top.h"
//#include "__jdsltm1a_sram_map.h"
//#include "__jdsltm1a_sram_ltm.h"


#define K_TYPE_JDSLTM1A				(k_jdsltm1a_get_type())
#define K_JDSLTM1A(obj)					(K_TYPE_CHECK_INSTANCE_CAST((obj), KJdsltm1a))
#define K_IS_JDSLTM1A(obj)			(K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_JDSLTM1A))


typedef struct _KJdsltm1a 				KJdsltm1a;
typedef struct _KJdsltm1aPrivate 	KJdsltm1aPrivate;


struct _KJdsltm1a
{
	KObject parent;
};

/* Define i/o mapping */
typedef struct _IoLtmTop
{
	/* JDSLTM */
	/* 2841_(3000 - 31FFh) */
	ioltmchrbk rbk;
	/* 2841_(3200 - 33FFh) */
	kuchar dmy320033ff[0x0400 - 0x0200];
	/* 2841_(3400 - 37FFh) */
	IoLtmChMap map;
	/* 2841_(3800 - 3BFFh) */
	IoLtmChLtm ltm;
	/* 2841_(3C00 - 3FFFh) */
	kuchar dmy3c003fff[0x1000 - 0x0C00];
} IoLtmTop;

/*	structure of mylog0tbl0 (2949_0000h)	*/
typedef union _MapSramMylog0tbl0
{
	kushort hword[512];
	struct
	{
		kushort ylog0tbl0 :13;
		kushort :3;
	} bit[512];
} MapSramMylog0tbl0;

/*	structure of mylog1tbl0 (2949_0400h)	*/
typedef union _MapSramMylog1tbl0
{
	kushort hword[512];
	struct
	{
		kushort ylog1tbl0 :13;
		kushort :3;
	} bit[512];
} MapSramMylog1tbl0;

/*	structure of mylog0tbl1 (2949_0800h)	*/
typedef union _MapSramMylog0tbl1
{
	kushort hword[512];
	struct
	{
		kushort ylog0tbl1 :13;
		kushort :3;
	} bit[512];
} MapSramMylog0tbl1;

/*	structure of mylog1tbl1 (2949_0C00h)	*/
typedef union _MapSramMylog1tbl1
{
	kushort hword[512];
	struct
	{
		kushort ylog0tbl1 :13;
		kushort :3;
	} bit[512];
} MapSramMylog1tbl1;

/* Define i/o mapping */
typedef struct _IoLtmMapSram
{
	/* JDSLTM */
	MapSramMylog0tbl0 mylog0tbl0; /* 2949_(0000 - 03FFh) */
	MapSramMylog1tbl0 mylog1tbl0; /* 2949_(0400 - 07FFh) */
	MapSramMylog0tbl1 mylog0tbl1; /* 2949_(0800 - 0BFFh) */
	MapSramMylog1tbl1 mylog1tbl1; /* 2949_(0C00 - 0FFFh) */
} IoLtmMapSram;

/*	structure of lylog0tbl0 (2949_1000h)	*/
typedef union _ItmSramLylog0tbl0
{
	kushort hword[512];
	struct
	{
		kushort ylog0tbl0 :13;
		kushort :3;
	} bit[512];
} ItmSramLylog0tbl0;

/*	structure of lylog1tbl0 (2949_1400h)	*/
typedef union _ItmSramLylog1tbl0
{
	kushort hword[512];
	struct
	{
		kushort ylog1tbl0 :13;
		kushort :3;
	} bit[512];
} ItmSramLylog1tbl0;

/*	structure of lylog0tbl1 (2949_1800h)	*/
typedef union _ItmSramLylog0tbl1
{
	kushort hword[512];
	struct
	{
		kushort ylog0tbl1 :13;
		kushort :3;
	} bit[512];
} ItmSramLylog0tbl1;

/*	structure of lylog1tbl1 (2949_1C00h)	*/
typedef union _ItmSramLylog1tbl1
{
	kushort hword[512];
	struct
	{
		kushort ylog1tbl1 :13;
		kushort :3;
	} bit[512];
} ItmSramLylog1tbl1;

/* Define i/o mapping */
typedef struct _IoLtmLtmSram
{
	/* JDSLTM */
	ItmSramLylog0tbl0 lylog0tbl0; /* 2949_(1000 - 13FFh) */
	ItmSramLylog1tbl0 lylog1tbl0; /* 2949_(1400 - 17FFh) */
	ItmSramLylog0tbl1 lylog0tbl1; /* 2949_(1800 - 1BFFh) */
	ItmSramLylog1tbl1 lylog1tbl1; /* 2949_(1C00 - 1FFFh) */
} IoLtmLtmSram;

/* Define i/o mapping */
typedef struct _LoLtmSram
{
	/* JDSLTM */
	/* 2949_(0000 - 0FFFh) */
	IoLtmMapSram mapSram;
	/* 2949_(1000 - 1FFFh) */
	IoLtmLtmSram ltmSram;
	/* 2949_2000 - 2949_FFFFh */
	kuchar dmy294920002949ffff[0x294A0000 - 0x29492000];
} LoLtmSram;


extern volatile LoLtmSram ioLtmTblP1;
extern volatile LoLtmSram ioLtmTblP2;
extern volatile LoLtmSram ioLtmTblP3;
extern volatile IoLtmTop ioLtmP1;
extern volatile IoLtmTop ioLtmP2;
extern volatile IoLtmTop ioLtmP3;


KConstType k_jdsltm1a_get_type(void);
KJdsltm1a* k_jdsltm1a_new(void);


#endif/*__K_JDSLTM1A_H__*/

