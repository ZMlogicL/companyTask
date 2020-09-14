/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-07
*@author            :陈倩
*@brief             :kjdsimg
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


#ifndef __K_JDSIMG_H__
#define __K_JDSIMG_H__


#include <klib.h>


#define K_TYPE_JDSIMG				(k_jdsimg_get_type())
#define K_JDSIMG(obj)					(K_TYPE_CHECK_INSTANCE_CAST((obj), KJdsimg))
#define K_IS_JDSIMG(obj)			(K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_JDSIMG))


typedef struct _KJdsimg				KJdsimg;
typedef struct _KJdsimgPrivate	KJdsimgPrivate;

struct  _KJdsimg
{
	KObject parent;
};


/*	structure of imgpipepsw	(2880_0000h)	*/
typedef union _IoImgpipepsw
{
	kulong word;
	struct {
		kulong r2ysel :2;
		kulong :2;
		kulong b2rcnc :2;
		kulong :26;
	} bit;
} IoImgpipepsw;

/*	structure of mxicmon	(2880_0004h)	*/
typedef union _IoMxicmon
{
	kulong word;
	struct {
		kulong vden :1;
		kulong hden :1;
		kulong :1;
		kulong senen :1;
		kulong sro1en :1;
		kulong sro2en :1;
		kulong b2b1en :1;
		kulong b2b2en :1;
		kulong yo1en :1;
		kulong yo2en :1;
		kulong staten :1;
		kulong pasen :1;
		kulong den :1;
		kulong :19;
	} bit;
} IoMxicmon;

/*	structure of srampd		(2880_0008h)	*/
typedef union _IoSrampd
{
	kulong word;
	struct {
		kulong jpegpd :4;
		kulong :28;
	} bit;
} IoSrampd;

/* Define i/o mapping */
typedef struct _IoImg
{
	/* JDSIMG */
	/* 2880_(0000 - 0003h) */
	IoImgpipepsw imgpipepsw;
	/* 2880_(0004 - 0007h) */
	IoMxicmon mxicmon;
	/* 2880_(0008 - 000Bh) */
	IoSrampd srampd;
	/* 2880_000C - 2880_FFFFh */
	kuchar dmy2880000c2880ffff[0x28810000 - 0x2880000C];
} IoImg;

extern volatile IoImg		ioImg;


KConstType				k_jdsimg_get_type(void);
KJdsimg*					k_jdsimg_new(void);


#endif/*__K_JDSIMG_H__*/

