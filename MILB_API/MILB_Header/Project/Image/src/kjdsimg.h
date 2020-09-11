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
	unsigned long word;
	struct {
		unsigned long r2ysel :2;
		unsigned long :2;
		unsigned long b2rcnc :2;
		unsigned long :26;
	} bit;
} IoImgpipepsw;

/*	structure of mxicmon	(2880_0004h)	*/
typedef union _IoMxicmon
{
	unsigned long word;
	struct {
		unsigned long vden :1;
		unsigned long hden :1;
		unsigned long :1;
		unsigned long senen :1;
		unsigned long sro1en :1;
		unsigned long sro2en :1;
		unsigned long b2b1en :1;
		unsigned long b2b2en :1;
		unsigned long yo1en :1;
		unsigned long yo2en :1;
		unsigned long staten :1;
		unsigned long pasen :1;
		unsigned long den :1;
		unsigned long :19;
	} bit;
} IoMxicmon;

/*	structure of srampd		(2880_0008h)	*/
typedef union _IoSrampd
{
	unsigned long word;
	struct {
		unsigned long jpegpd :4;
		unsigned long :28;
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
	unsigned char dmy2880000c2880ffff[0x28810000 - 0x2880000C];
} IoImg;

extern volatile IoImg		ioImg;


KConstType				k_jdsimg_get_type(void);
KJdsimg*					k_jdsimg_new(void);


#endif/*__K_JDSIMG_H__*/

