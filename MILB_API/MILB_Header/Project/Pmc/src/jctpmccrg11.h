/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-08
*@author              :申雨
*@brief               :sns 索喜rtos
*@rely                :glib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年09月开始开发
*/


#ifndef __JCTPMC_CRG11_H__
#define __JCTPMC_CRG11_H__


#include <stdio.h>
#include <glib-object.h>


typedef union 				_IoPmcCrg11Crplc IoPmcCrg11Crplc;
typedef union 				_IoPmcCrg11Crstp IoPmcCrg11Crstp;
typedef union 				_IoPmcCrg11Crrsc IoPmcCrg11Crrsc;
typedef union 				_IoPmcCrg11Crswr IoPmcCrg11Crswr;
typedef union 				_IoPmcCrg11Crrsm IoPmcCrg11Crrsm;
typedef union 				_IoPmcCrg11Crcdc IoPmcCrg11Crcdc;
typedef union 				_IoPmcCrg11Crdm IoPmcCrg11Crdm;
typedef union 				_IoPmcCrg11Crlp IoPmcCrg11Crlp;
typedef struct 				_IoPmcCrg11 IoPmcCrg11;

/* CRG11 */

/* CRPLC */
union _IoPmcCrg11Crplc {
	gulong		word;
	struct {
		gulong					:24;
		gulong	pllbypass		:1;
		gulong					:7;
	}bit;
};

/* CRSTP */
union _IoPmcCrg11Crstp {
	gulong		word;
	struct {
		gulong	stopen			:1;
		gulong	stopmnt			:1;
		gulong					:30;
	} bit;
};

/* CRRSC */
union _IoPmcCrg11Crrsc {
	gulong		word;
	struct {
		gulong	arstmode		:4;
		gulong					:4;
		gulong	swrstm			:1;
		gulong	wdrstm			:1;
		gulong					:22;
	} bit;
};

/* CRSWR */
union _IoPmcCrg11Crswr {
	gulong		word;
	struct {
		gulong	swrstreq		:1;
		gulong					:31;
	} bit;
};

/* CRRSM */
union _IoPmcCrg11Crrsm {
	gulong		word;
	struct {
		gulong	wdrst			:1;
		gulong	swrst			:1;
		gulong	srst			:1;
		gulong	poreset			:1;
		gulong					:28;
	} bit;
};

/* CRCDC */
union _IoPmcCrg11Crcdc {
	gulong		word;
	struct {
		gulong	dchreq			:1;
		gulong					:31;
	} bit;
};

/* CRDMx (x=0-5) */
union _IoPmcCrg11Crdm {
	gulong		word;
	struct {
		gulong	divmode			:8;
		gulong					:24;
	} bit;
};

/* CRLPx (x=0-5) */
union _IoPmcCrg11Crlp {
	gulong		word;
	struct {
		gulong	csysreqR		:8;
		gulong	lpowerhs		:8;
		gulong	cactiveC		:8;
		gulong	cen				:8;
	} bit;
};

/* PMC */
struct _IoPmcCrg11 {
	/* 1DFF_(E000 - E003h)	*/
	IoPmcCrg11Crplc		crplc;
	/* 1DFF_(E004 - E007h)	*/
	guchar					dmyPmcCrg11004007[0x008 - 0x004];
	/* 1DFF_(E008 - E00Bh)	*/
	IoPmcCrg11Crstp		crstp;
	/* 1DFF_(E00C - E01Fh)	*/
	guchar					dmyPmcCrg1100c01f[0x020 - 0x00C];
	/* 1DFF_(E020 - E023h)	*/
	IoPmcCrg11Crrsc		crrsc;
	/* 1DFF_(E024 - E027h)	*/
	IoPmcCrg11Crswr		crswr;
	/* 1DFF_(E028 - E02Bh)	*/
	guchar					dmyPmcCrg1102802b[0x02C - 0x028];
	/* 1DFF_(E02C - E02Fh)	*/
	IoPmcCrg11Crrsm		crrsm;
	/* 1DFF_(E030 - E033h)	*/
	IoPmcCrg11Crcdc		crcdc;
	/* 1DFF_(E034 - E0FFh)	*/
	guchar					dmyPmcCrg110340ff[0x100 - 0x034];
	/* 1DFF_(E100 - E103h)	*/
	IoPmcCrg11Crdm		crdm0;
	/* 1DFF_(E104 - E107h)	*/
	IoPmcCrg11Crlp		crlp0;
	/* 1DFF_(E108 - E10Fh)	*/
	guchar					dmyPmcCrg1110810f[0x110 - 0x108];
	/* 1DFF_(E110 - E113h)	*/
	IoPmcCrg11Crdm		crdm1;
	/* 1DFF_(E114 - E117h)	*/
	IoPmcCrg11Crlp		crlp1;
	/* 1DFF_(E118 - E12Fh)	*/
	guchar					dmyPmcCrg1111812f[0x130 - 0x118];
	/* 1DFF_(E130 - E133h)	*/
	IoPmcCrg11Crdm		crdm3;
	/* 1DFF_(E134 - E137h)	*/
	IoPmcCrg11Crlp		crlp3;
	/* 1DFF_(E138 - E13Fh)	*/
	guchar					dmyPmcCrg1113813f[0x140 - 0x138];
	/* 1DFF_(E140 - E143h)	*/
	IoPmcCrg11Crdm		crdm4;
	/* 1DFF_(E144 - E147h)	*/
	IoPmcCrg11Crlp		crlp4;
	/* 1DFF_(E148 - E14Fh)	*/
	guchar					dmyPmcCrg1114814f[0x150 - 0x148];
	/* 1DFF_(E150 - E153h)	*/
	IoPmcCrg11Crdm		crdm5;
	/* 1DFF_(E154 - E157h)	*/
	IoPmcCrg11Crlp		crlp5;
	/* 1DFF_(E158 - EFFFh)	*/
	guchar					dmyPmcCrg11158Fff[0x1000 - 0x158];
};


#endif /* __JCTPMC_CRG11_H__ */
