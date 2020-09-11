/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-08
*@author              :申雨
*@brief               :sns 索喜rtos
*@rely                :klib
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


#include <klib.h>


#define JCTPMC_TYPE_CRG11			(jctpmc_crg11_get_type())
#define JCTPMC_CRG11(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, JctpmcCrg11))
#define JCTPMC_IS_CRG11(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, JCTPMC_TYPE_CRG11))


typedef union 				_IoPmcCrg11Crplc IoPmcCrg11Crplc;
typedef union 				_IoPmcCrg11Crstp IoPmcCrg11Crstp;
typedef union 				_IoPmcCrg11Crrsc IoPmcCrg11Crrsc;
typedef union 				_IoPmcCrg11Crswr IoPmcCrg11Crswr;
typedef union 				_IoPmcCrg11Crrsm IoPmcCrg11Crrsm;
typedef union 				_IoPmcCrg11Crcdc IoPmcCrg11Crcdc;
typedef union 				_IoPmcCrg11Crdm IoPmcCrg11Crdm;
typedef union 				_IoPmcCrg11Crlp IoPmcCrg11Crlp;
typedef struct 				_IoPmcCrg11 IoPmcCrg11;
typedef struct 				_JctpmcCrg11 JctpmcCrg11;
typedef struct 				_JctpmcCrg11Private JctpmcCrg11Private;

/* CRG11 */

/* CRPLC */
union _IoPmcCrg11Crplc {
	kulong		word;
	struct {
		kulong					:24;
		kulong	pllbypass		:1;
		kulong					:7;
	}bit;
};

/* CRSTP */
union _IoPmcCrg11Crstp {
	kulong		word;
	struct {
		kulong	stopen			:1;
		kulong	stopmnt			:1;
		kulong					:30;
	} bit;
};

/* CRRSC */
union _IoPmcCrg11Crrsc {
	kulong		word;
	struct {
		kulong	arstmode		:4;
		kulong					:4;
		kulong	swrstm			:1;
		kulong	wdrstm			:1;
		kulong					:22;
	} bit;
};

/* CRSWR */
union _IoPmcCrg11Crswr {
	kulong		word;
	struct {
		kulong	swrstreq		:1;
		kulong					:31;
	} bit;
};

/* CRRSM */
union _IoPmcCrg11Crrsm {
	kulong		word;
	struct {
		kulong	wdrst			:1;
		kulong	swrst			:1;
		kulong	srst			:1;
		kulong	poreset			:1;
		kulong					:28;
	} bit;
};

/* CRCDC */
union _IoPmcCrg11Crcdc {
	kulong		word;
	struct {
		kulong	dchreq			:1;
		kulong					:31;
	} bit;
};

/* CRDMx (x=0-5) */
union _IoPmcCrg11Crdm {
	kulong		word;
	struct {
		kulong	divmode			:8;
		kulong					:24;
	} bit;
};

/* CRLPx (x=0-5) */
union _IoPmcCrg11Crlp {
	kulong		word;
	struct {
		kulong	csysreqR		:8;
		kulong	lpowerhs		:8;
		kulong	cactiveC		:8;
		kulong	cen				:8;
	} bit;
};

/* PMC */
struct _IoPmcCrg11 {
	/* 1DFF_(E000 - E003h)	*/
	IoPmcCrg11Crplc		crplc;
	/* 1DFF_(E004 - E007h)	*/
	kuchar					dmyPmcCrg11004007[0x008 - 0x004];
	/* 1DFF_(E008 - E00Bh)	*/
	IoPmcCrg11Crstp		crstp;
	/* 1DFF_(E00C - E01Fh)	*/
	kuchar					dmyPmcCrg1100c01f[0x020 - 0x00C];
	/* 1DFF_(E020 - E023h)	*/
	IoPmcCrg11Crrsc		crrsc;
	/* 1DFF_(E024 - E027h)	*/
	IoPmcCrg11Crswr		crswr;
	/* 1DFF_(E028 - E02Bh)	*/
	kuchar					dmyPmcCrg1102802b[0x02C - 0x028];
	/* 1DFF_(E02C - E02Fh)	*/
	IoPmcCrg11Crrsm		crrsm;
	/* 1DFF_(E030 - E033h)	*/
	IoPmcCrg11Crcdc		crcdc;
	/* 1DFF_(E034 - E0FFh)	*/
	kuchar					dmyPmcCrg110340ff[0x100 - 0x034];
	/* 1DFF_(E100 - E103h)	*/
	IoPmcCrg11Crdm		crdm0;
	/* 1DFF_(E104 - E107h)	*/
	IoPmcCrg11Crlp		crlp0;
	/* 1DFF_(E108 - E10Fh)	*/
	kuchar					dmyPmcCrg1110810f[0x110 - 0x108];
	/* 1DFF_(E110 - E113h)	*/
	IoPmcCrg11Crdm		crdm1;
	/* 1DFF_(E114 - E117h)	*/
	IoPmcCrg11Crlp		crlp1;
	/* 1DFF_(E118 - E12Fh)	*/
	kuchar					dmyPmcCrg1111812f[0x130 - 0x118];
	/* 1DFF_(E130 - E133h)	*/
	IoPmcCrg11Crdm		crdm3;
	/* 1DFF_(E134 - E137h)	*/
	IoPmcCrg11Crlp		crlp3;
	/* 1DFF_(E138 - E13Fh)	*/
	kuchar					dmyPmcCrg1113813f[0x140 - 0x138];
	/* 1DFF_(E140 - E143h)	*/
	IoPmcCrg11Crdm		crdm4;
	/* 1DFF_(E144 - E147h)	*/
	IoPmcCrg11Crlp		crlp4;
	/* 1DFF_(E148 - E14Fh)	*/
	kuchar					dmyPmcCrg1114814f[0x150 - 0x148];
	/* 1DFF_(E150 - E153h)	*/
	IoPmcCrg11Crdm		crdm5;
	/* 1DFF_(E154 - E157h)	*/
	IoPmcCrg11Crlp		crlp5;
	/* 1DFF_(E158 - EFFFh)	*/
	kuchar					dmyPmcCrg11158Fff[0x1000 - 0x158];
};

struct _JctpmcCrg11 {
	KObject parent;
};


KConstType 				jctpmc_crg11_get_type(void);
JctpmcCrg11*		        jctpmc_crg11_new(void);


#endif /* __JCTPMC_CRG11_H__ */
