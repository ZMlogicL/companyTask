/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-07
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


#ifndef __K_CHIPTOP3_H__
#define __K_CHIPTOP3_H__


#include <klib.h>
#include "kchiptop2.h"
#include "kchiptop1.h"


#define K_TYPE_CHIPTOP3			(k_chiptop3_get_type())
#define K_CHIPTOP3(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, KChiptop3))
#define K_IS_CHIPTOP3(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, K_TYPE_CHIPTOP3))


typedef union 				_IoChiptopPuder IoChiptopPuder;
typedef union 				_IoChiptopPudcr IoChiptopPudcr;
typedef union 				_IoChiptopPersel1 IoChiptopPersel1;
typedef union 				_IoChiptopPersel2 IoChiptopPersel2;
typedef union 				_IoChiptopPersel3 IoChiptopPersel3;
typedef union			 	_IoChiptopPersel4 IoChiptopPersel4;
typedef union 				_IoChiptopMselc IoChiptopMselc;
typedef union 				_IoChiptopDbcnt1 IoChiptopDbcnt1;
typedef union 				_IoChiptopDbcnt2 IoChiptopDbcnt2;
typedef union 				_IoChiptopDbcnt3 IoChiptopDbcnt3;
typedef union 				_IoChiptopDbcnt4 IoChiptopDbcnt4;
typedef union 				_IoChiptopDbcnt5 IoChiptopDbcnt5;
typedef union 				_IoChiptopPudcnt IoChiptopPudcnt;
typedef union 				_IoChiptopPllfreq1 IoChiptopPllfreq1;
typedef union 				_IoChiptopOdivch0 IoChiptopOdivch0;
typedef union 				_IoChiptopCmden IoChiptopCmden;
typedef struct 				_IoChiptop IoChiptop;
typedef struct 				_KChiptop3 KChiptop3;
typedef struct 				_KChiptop3Private KChiptop3Private;

/*	structure of PUDER	(0x1D02_230C) */
union _IoChiptopPuder {
	kulong		word[10];
	struct {
	/* PUDER76 (1D02_230Ch) */
		kulong				:32;
	/* PUDER98 (1D02_2310h) */
		kulong	p80			:1;
		kulong	p81			:1;
		kulong	p82			:1;
		kulong	p83			:1;
		kulong				:2;
		kulong	p86			:1;
		kulong	p87			:1;
		kulong	p90			:1;
		kulong	p91			:1;
		kulong	p92			:1;
		kulong	p93			:1;
		kulong				:20;
	/* PUDERBA (1D02_2314h) */
		kulong	pa0			:1;
		kulong	pa1			:1;
		kulong	pa2			:1;
		kulong	pa3			:1;
		kulong	pa4			:1;
		kulong	pa5			:1;
		kulong	pa6			:1;
		kulong	pa7			:1;
		kulong	pb0			:1;
		kulong	pb1			:1;
		kulong	pb2			:1;
		kulong	pb3			:1;
		kulong	pb4			:1;
		kulong				:19;
	/* PUDERDC (1D02_2318h) */
		kulong				:8;
		kulong	pd0			:1;
		kulong	pd1			:1;
		kulong	pd2			:1;
		kulong	pd3			:1;
		kulong	pd4			:1;
		kulong	pd5			:1;
		kulong	pd6			:1;
		kulong				:17;
	/* PUDERFE (1D02_231Ch) */
		kulong	pe0			:1;
		kulong	pe1			:1;
		kulong				:8;
		kulong	pf2			:1;
		kulong	pf3			:1;
		kulong	pf4			:1;
		kulong				:19;
	/* PUDERHG (1D02_2320h) */
		kulong	pg0			:1;
		kulong	pg1			:1;
		kulong	pg2			:1;
		kulong	pg3			:1;
		kulong	pg4			:1;
		kulong	pg5			:1;
		kulong	pg6			:1;
		kulong	pg7			:1;
		kulong	ph0			:1;
		kulong	ph1			:1;
		kulong	ph2			:1;
		kulong	ph3			:1;
		kulong				:20;
	/* PUDERJW (1D02_2324h) */
		kulong	pw0			:1;
		kulong	pw1			:1;
		kulong	pw2			:1;
		kulong	pw3			:1;
		kulong	pw4			:1;
		kulong	pw5			:1;
		kulong	pw6			:1;
		kulong	pw7			:1;
		kulong	pj0			:1;
		kulong	pj1			:1;
		kulong	pj2			:1;
		kulong	pj3			:1;
		kulong	pj4			:1;
		kulong	pj5			:1;
		kulong	pj6			:1;
		kulong	pj7			:1;
		kulong				:16;
	/* PUDERLK (1D02_2328h) */
		kulong	pk0			:1;
		kulong	pk1			:1;
		kulong	pk2			:1;
		kulong	pk3			:1;
		kulong	pk4			:1;
		kulong	pk5			:1;
		kulong	pk6			:1;
		kulong	pk7			:1;
		kulong	pl0			:1;
		kulong	pl1			:1;
		kulong	pl2			:1;
		kulong	pl3			:1;
		kulong	pl4			:1;
		kulong	pl5			:1;
		kulong				:18;
	/* PUDERNM (1D02_232Ch) */
		kulong	pm0			:1;
		kulong	pm1			:1;
		kulong				:1;
		kulong	pm3			:1;
		kulong	pm4			:1;
		kulong				:3;
		kulong	pn0			:1;
		kulong	pn1			:1;
		kulong				:1;
		kulong	pn3			:1;
		kulong	pn4			:1;
		kulong				:19;
	/* PUDERPY (1D02_2330h) */
		kulong	py0			:1;
		kulong	py1			:1;
		kulong	py2			:1;
		kulong	py3			:1;
		kulong	py4			:1;
		kulong	py5			:1;
		kulong	py6			:1;
		kulong	py7			:1;
		kulong	pp0			:1;
		kulong	pp1			:1;
		kulong	pp2			:1;
		kulong	pp3			:1;
		kulong				:20;
	}bit;
};

/*	structure of PUDCR	(0x1D02_2400) */
union _IoChiptopPudcr {
	kulong		word[10];
	struct {
	/* PUDCR76 (1D02_240Ch) */
		kulong				:32;
	/* PUDCR98 (1D02_2410h) */
		kulong	p80			:1;
		kulong	p81			:1;
		kulong	p82			:1;
		kulong	p83			:1;
		kulong				:2;
		kulong	p86			:1;
		kulong	p87			:1;
		kulong	p90			:1;
		kulong	p91			:1;
		kulong	p92			:1;
		kulong	p93			:1;
		kulong				:20;
	/* PUDCRBA (1D02_2414h) */
		kulong	pa0			:1;
		kulong	pa1			:1;
		kulong	pa2			:1;
		kulong	pa3			:1;
		kulong	pa4			:1;
		kulong	pa5			:1;
		kulong	pa6			:1;
		kulong	pa7			:1;
		kulong	pb0			:1;
		kulong	pb1			:1;
		kulong	pb2			:1;
		kulong	pb3			:1;
		kulong	pb4			:1;
		kulong				:19;
	/* PUDCRDC (1D02_2418h) */
		kulong				:8;
		kulong	pd0			:1;
		kulong	pd1			:1;
		kulong	pd2			:1;
		kulong	pd3			:1;
		kulong	pd4			:1;
		kulong	pd5			:1;
		kulong	pd6			:1;
		kulong				:17;
	/* PUDCRFE (1D02_241Ch) */
		kulong	pe0			:1;
		kulong	pe1			:1;
		kulong				:8;
		kulong	pf2			:1;
		kulong	pf3			:1;
		kulong	pf4			:1;
		kulong				:19;
	/* PUDCRHG (1D02_2420h) */
		kulong	pg0			:1;
		kulong	pg1			:1;
		kulong	pg2			:1;
		kulong	pg3			:1;
		kulong	pg4			:1;
		kulong	pg5			:1;
		kulong	pg6			:1;
		kulong	pg7			:1;
		kulong	ph0			:1;
		kulong	ph1			:1;
		kulong	ph2			:1;
		kulong	ph3			:1;
		kulong				:20;
	/* PUDCRJW (1D02_2424h) */
		kulong	pw0			:1;
		kulong	pw1			:1;
		kulong	pw2			:1;
		kulong	pw3			:1;
		kulong	pw4			:1;
		kulong	pw5			:1;
		kulong	pw6			:1;
		kulong	pw7			:1;
		kulong	pj0			:1;
		kulong	pj1			:1;
		kulong	pj2			:1;
		kulong	pj3			:1;
		kulong	pj4			:1;
		kulong	pj5			:1;
		kulong	pj6			:1;
		kulong	pj7			:1;
		kulong				:16;
	/* PUDCRLK (1D02_2428h) */
		kulong	pk0			:1;
		kulong	pk1			:1;
		kulong	pk2			:1;
		kulong	pk3			:1;
		kulong	pk4			:1;
		kulong	pk5			:1;
		kulong	pk6			:1;
		kulong	pk7			:1;
		kulong	pl0			:1;
		kulong	pl1			:1;
		kulong	pl2			:1;
		kulong	pl3			:1;
		kulong	pl4			:1;
		kulong	pl5			:1;
		kulong				:18;
	/* PUDCRNM (1D02_242Ch) */
		kulong	pm0			:1;
		kulong	pm1			:1;
		kulong				:1;
		kulong	pm3			:1;
		kulong	pm4			:1;
		kulong				:3;
		kulong	pn0			:1;
		kulong	pn1			:1;
		kulong				:1;
		kulong	pn3			:1;
		kulong	pn4			:1;
		kulong				:19;
	/* PUDCRPY (1D02_2430h) */
		kulong	py0			:1;
		kulong	py1			:1;
		kulong	py2			:1;
		kulong	py3			:1;
		kulong	py4			:1;
		kulong	py5			:1;
		kulong	py6			:1;
		kulong	py7			:1;
		kulong	pp0			:1;
		kulong	pp1			:1;
		kulong	pp2			:1;
		kulong	pp3			:1;
		kulong				:20;
	}bit;
};

/*	structure of PERSEL1 (1D02_0000h) */
union _IoChiptopPersel1 {
	kulong word;
	struct {
		kulong	i2c0cnt		:2;
		kulong	sdanc0		:1;
		kulong	sclnc0		:1;
		kulong	i2c1cnt		:2;
		kulong	sdanc1		:1;
		kulong	sclnc1		:1;
		kulong	i2c2cnt		:2;
		kulong	sdanc2		:1;
		kulong	sclnc2		:1;
		kulong	dvwt2		:1;
		kulong	dhwt3		:1;
		kulong				:2;
		kulong	au0do0c		:1;
		kulong	au0do1c		:1;
		kulong	au1doc		:1;
		kulong	au0mcc		:1;
		kulong	au1mcc		:1;
		kulong	rlsel3		:1;
		kulong	rlsel4		:1;
		kulong	rlsel5		:1;
		kulong	intvdsel	:3;
		kulong				:5;
	} bit;
};

/*	structure of PERSEL2 (1D02_0004h) */
union _IoChiptopPersel2 {
	kulong word;
	struct {
		kulong	udctrg		:1;
		kulong	udc0am		:1;
		kulong	udc0bm		:1;
		kulong	udc1am		:1;
		kulong	udc1bm		:1;
		kulong	udc2am		:1;
		kulong	udc2bm		:1;
		kulong	udc3am		:1;
		kulong	udc3bm		:1;
		kulong	udc4am		:1;
		kulong	udc4bm		:1;
		kulong	udc5am		:1;
		kulong	udc5bm		:1;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
		kulong				:19;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE

#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
		kulong	spimsen0	:1;
		kulong	spimsen1	:1;
		kulong	spimsen2	:1;
		kulong				:16;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	} bit;
};

/*	structure of PERSEL3 (1D02_0008h) */
union _IoChiptopPersel3 {
	kulong word;
	struct {
		kulong	au1wpps		:1;
		kulong	au0wp11		:1;
		kulong	snh2wp04	:1;
		kulong	snv2wp05	:1;
		kulong	sna2wp06	:1;
		kulong	snh3wp07	:1;
		kulong	snv3wp08	:1;
		kulong	sna3wp09	:1;
		kulong	u1vbsou5	:1;
		kulong	u2vbsou6	:1;
		kulong	u2idwp14	:1;
		kulong	prt1sou3	:1;
		kulong	pxw0wp12	:1;
		kulong	pxw1sou7	:1;
		kulong	pxc0sck7	:1;
		kulong	pxc1wp15	:1;
		kulong	sck4wp13	:1;
		kulong	s3lsou5wp14	:2;
		kulong	s3swp15		:1;
		kulong	rts1sck2	:1;
		kulong				:1;
		kulong	u1idwp13	:1;
		kulong	prt0sck3	:1;
		kulong				:8;
	} bit;
};

/*	structure of PERSEL4 (1D02_000Ch) */
union _IoChiptopPersel4 {
	kulong word;
	struct {
		kulong	ei22ud0a	:1;
		kulong	ei23ud0b	:1;
		kulong	ei24ud1a	:1;
		kulong	ei25ud1b	:1;
		kulong	ei26ud2a	:1;
		kulong	ei27ud2b	:1;
		kulong	ei28ud3a	:1;
		kulong	ei29ud3b	:1;
		kulong	ei30ud4a	:1;
		kulong	ei31ud4b	:1;
		kulong	sd3cdxs		:1;
		kulong	sd3wps		:1;
		kulong	u1ocdxs		:1;
		kulong	u1iddigs	:1;
		kulong	u2ocdxs		:1;
		kulong	u2iddigs	:1;
		kulong				:16;
	} bit;
};

/*	structure of MSELC (1D02_0010h) */
union _IoChiptopMselc {
	kulong word;
	struct {
		kulong	msel		:4;
		kulong				:28;
	} bit;
};

/*	structure of DBCNT1 (1D02_0014h) */
union _IoChiptopDbcnt1 {
	kulong word;
	struct {
		kulong				:14;
		kulong	t07dc		:2;
		kulong	t08dc		:2;
		kulong	t09dc		:2;
		kulong	t10dc		:2;
		kulong	t11dc		:2;
		kulong	t12dc		:2;
		kulong	t13dc		:2;
		kulong	t14dc		:2;
		kulong	t15dc		:2;
	} bit;
};

/*	structure of DBCNT2 (1D02_0018h) */
union _IoChiptopDbcnt2 {
	kulong word;
	struct {
		kulong	t16dc		:2;
		kulong	t17dc		:2;
		kulong	t18dc		:2;
		kulong	t19dc		:2;
		kulong	t20dc		:2;
		kulong	t21dc		:2;
		kulong	t22dc		:2;
		kulong	t23dc		:2;
		kulong	t24dc		:2;
		kulong	t25dc		:2;
		kulong	t26dc		:2;
		kulong	t27dc		:2;
		kulong	t28dc		:2;
		kulong	t29dc		:2;
		kulong	t30dc		:2;
		kulong	t31dc		:2;
	} bit;
};

/*	structure of DBCNT3 (1D02_001Ch) */
union _IoChiptopDbcnt3 {
	kulong word;
	struct {
		kulong	t32dc		:2;
		kulong	t33dc		:2;
		kulong	t34dc		:2;
		kulong	t35dc		:2;
		kulong	t36dc		:2;
		kulong	t37dc		:2;
		kulong	t38dc		:2;
		kulong	t39dc		:2;
		kulong	t40dc		:2;
		kulong	t41dc		:2;
		kulong	t42dc		:2;
		kulong	t43dc		:2;
		kulong	t44dc		:2;
		kulong	t45dc		:2;
		kulong	t46dc		:2;
		kulong	t47dc		:2;
	} bit;
};

/*	structure of DBCNT4 (1D02_0020h) */
union _IoChiptopDbcnt4 {
	kulong word;
	struct {
		kulong	t48dc		:2;
		kulong	t49dc		:2;
		kulong	t50dc		:2;
		kulong	t51dc		:2;
		kulong	t52dc		:2;
		kulong	t53dc		:2;
		kulong	t54dc		:2;
		kulong	t55dc		:2;
		kulong	t56dc		:2;
		kulong	t57dc		:2;
		kulong	t58dc		:2;
		kulong	t59dc		:2;
		kulong	t60dc		:2;
		kulong	t61dc		:2;
		kulong	t62dc		:2;
		kulong	t63dc		:2;
	} bit;
};

/*	structure of DBCNT5 (1D02_0024h) */
union _IoChiptopDbcnt5 {
	kulong word;
	struct {
		kulong	t64dc		:2;
		kulong	t65dc		:2;
		kulong	t66dc		:2;
		kulong				:26;
	} bit;
};

/*	structure of PUDCNT (1D02_0028h) */
union _IoChiptopPudcnt {
	kulong word;
	struct {
		kulong	emmcnics	:2;
		kulong	emdatpue	:1;
		kulong	emcmdpue	:1;
		kulong	emdspde		:1;
		kulong	nfdatpue	:1;
		kulong	nfrbxpue	:1;
		kulong	nfdqspue	:1;
		kulong	sp1misope	:1;
		kulong	sp1mosipe	:1;
		kulong	sp1sckpe	:1;
		kulong	sp1cs0pe	:1;
		kulong	sp1misoudc	:1;
		kulong	sp1mosiudc	:1;
		kulong	sp1sckudc	:1;
		kulong	sp1cs0udc	:1;
		kulong				:16;
	} bit;
};

/*	structure of PLLFREQ1	(1D02_3000h)	*/
union _IoChiptopPllfreq1 {
	kulong		word;
	struct {
		kulong	pllidiv			:8;
		kulong					:24;
	}bit;
};

/*	structure of ODIVCH0	(1D02_3040h)	*/
union _IoChiptopOdivch0 {
	kulong		word;
	struct {
		kulong	odivch0num		:8;
		kulong					:24;
	}bit;
};

/*	structure of CMDEN	(1D02_3080h)	*/
union _IoChiptopCmden {
	kulong		word;
	struct {
		kulong	cmden			:3;
		kulong					:29;
	}bit;
};

/* Define i/o mapping */
struct _IoChiptop {
	/* 1D02_(0000 - 0003h) */
	IoChiptopPersel1		persel1;
	/* 1D02_(0004 - 0007h) */
	IoChiptopPersel2		persel2;
	/* 1D02_(0008 - 000Bh) */
	IoChiptopPersel3		persel3;
	/* 1D02_(000C - 000Fh) */
	IoChiptopPersel4		persel4;
	/* 1D02_(0010 - 0013h) */
	IoChiptopMselc			mselc;
	/* 1D02_(0014 - 0017h) */
	IoChiptopDbcnt1			dbcnt1;
	/* 1D02_(0018 - 001Bh) */
	IoChiptopDbcnt2			dbcnt2;
	/* 1D02_(001C - 001Fh) */
	IoChiptopDbcnt3			dbcnt3;
	/* 1D02_(0020 - 0023h) */
	IoChiptopDbcnt4			dbcnt4;
	/* 1D02_(0024 - 0027h) */
	IoChiptopDbcnt5			dbcnt5;
	/* 1D02_(0028 - 002Bh) */
	IoChiptopPudcnt			pudcnt;
	/* 1D02_(002C - 0FFFh) */
	kuchar dmy002c0fff[0x1000-0x002C];
	/* 1D02_(1000 - 1003h) */
	IoChiptopClksel1		clksel1;
	/* 1D02_(1004 - 1007h) */
	IoChiptopClksel2		clksel2;
	/* 1D02_(1008 - 100Bh) */
	IoChiptopClksel3		clksel3;
	/* 1D02_(100C - 100Fh) */
	IoChiptopClksel4		clksel4;
	/* 1D02_(1010 - 1013h) */
	IoChiptopClksel5		clksel5;
	/* 1D02_(1014 - 1017h) */
	IoChiptopClksel6		clksel6;
	/* 1D02_(1018 - 101Bh) */
	IoChiptopClksel7		clksel7;
	/* 1D02_(101C - 101Fh) */
	IoChiptopClksel8		clksel8;
	/* 1D02_(1020 - 1023h) */
	IoChiptopClksel9		clksel9;
	/* 1D02_(1024 - 1027h) */
	IoChiptopClksel10		clksel10;
	/* 1D02_(1028 - 102Bh) */
	IoChiptopClksel11		clksel11;
	/* 1D02_(102C - 102Fh) */
	IoChiptopClksel12		clksel12;
	/* 1D02_(1030 - 1033h) */
	IoChiptopPllcnt1		pllcnt1;
	/* 1D02_(1034 - 1037h) */
	IoChiptopPllcnt2		pllcnt2;
	/* 1D02_(1038 - 103Bh) */
	IoChiptopPllcnt3		pllcnt3;
	/* 1D02_(103C - 103Fh) */
	IoChiptopPllcnt4		pllcnt4;
	/* 1D02_(1040 - 1043h) */
	IoChiptopPllcnt5		pllcnt5;
	/* 1D02_(1044 - 1047h) */
	IoChiptopPllcnt6		pllcnt6;
	/* 1D02_(1048 - 104Bh) */
	IoChiptopPllcnt7		pllcnt7;
	/* 1D02_(104C - 104Fh) */
	IoChiptopPllcnt8		pllcnt8;
	/* 1D02_(1050 - 1053h) */
	IoChiptopPllcnt9		pllcnt9;
	/* 1D02_(1054 - 1057h) */
	IoChiptopClkstop1		clkstop1;
	/* 1D02_(1058 - 105Bh) */
	IoChiptopClkstop2		clkstop2;
	/* 1D02_(105C - 105Fh) */
	IoChiptopClkstop3		clkstop3;
	/* 1D02_(1060 - 1063h) */
	IoChiptopClkstop4		clkstop4;
	/* 1D02_(1064 - 1067h) */
	IoChiptopClkstop5		clkstop5;
	/* 1D02_(1068 - 106Bh) */
	IoChiptopClkstop6		clkstop6;
	/* 1D02_(106C - 106Fh) */
	IoChiptopClkstop7		clkstop7;
	/* 1D02_(1070 - 1073h) */
	IoChiptopClkstop8		clkstop8;
	/* 1D02_(1074 - 1077h) */
	IoChiptopClkstop9		clkstop9;
	/* 1D02_(1078 - 107Bh) */
	IoChiptopClkstop10		clkstop10;
	/* 1D02_(107C - 107Fh) */
	IoChiptopClkstop11		clkstop11;
	/* 1D02_(1080 - 1083h) */
	IoChiptopClkstop12		clkstop12;
	/* 1D02_(1084 - 1087h) */
	IoChiptopClkstop13		clkstop13;
	/* 1D02_(1088 - 108Bh) */
	IoChiptopClkstop14		clkstop14;
	/* 1D02_(108C - 108Fh) */
	IoChiprstCrswr			crswr;
	/* 1D02_(1090 - 1093h) */
	IoChiprstCrrrs			crrrs;
	/* 1D02_(1094 - 1097h) */
	IoChiprstCrrsm			crrsm;
	/* 1D02_(1098 - 1FFFh) */
	kuchar dmy10981fff[0x2000-0x1098];
	/* 1D02_(2000 - 200Bh) */
	kuchar dmy2000200b[0x200C-0x2000];
	/* 1D02_(200C - 2033h) */
	IoChiptopPdr			pdr;
	/* 1D02_(2034 - 20FFh) */
	kuchar dmy203420ff[0x2100-0x2034];
	/* 1D02_(2100 - 210Bh) */
	kuchar dmy2100210b[0x210C-0x2100];
	/* 1D02_(210C - 2133h) */
	IoChiptopDdr			ddr;
	/* 1D02_(2134 - 21FFh) */
	kuchar dmy213421ff[0x2200-0x2134];
	/* 1D02_(2200 - 220Bh) */
	kuchar dmy2200220b[0x220C-0x2200];
	/* 1D02_(220C - 2233h) */
	IoChiptopEpcr			epcr;
	/* 1D02_(2234 - 22FFh) */
	kuchar dmy223422ff[0x2300-0x2234];
	/* 1D02_(2300 - 230Bh) */
	kuchar dmy2300230b[0x230C-0x2300];
	/* 1D02_(230C - 2333h) */
	IoChiptopPuder			puder;
	/* 1D02_(2334 - 23FFh) */
	kuchar dmy233423ff[0x2400-0x2334];
	/* 1D02_(2400 - 240Bh) */
	kuchar dmy2400240b[0x240C-0x2400];
	/* 1D02_(240C - 2433h) */
	IoChiptopPudcr			pudcr;
	/* 1D02_(2434 - 2FFFh) */
	kuchar dmy24342fff[0x3000-0x2434];
	/* 1D02_(3000 - 3003h) */
	IoChiptopPllfreq1		pllfreq1;
	/* 1D02_(3004 - 303Fh) */
	kuchar dmy3004303f[0x3040-0x3004];
	/* 1D02_(3040 - 3043h) */
	IoChiptopOdivch0		odivch0;
	/* 1D02_(3044 - 307Fh) */
	kuchar dmy3044307f[0x3080-0x3044];
	/* 1D02_(3080 - 3083h) */
	IoChiptopCmden			cmden;
	/* 1D02_(3084 - 3FFFh) */
	kuchar dmy3084Ffff[0x4000-0x3084];
};

struct _KChiptop3 {
	KObject parent;
};

extern volatile IoChiptop ioChiptop;


KConstType 	k_chiptop3_get_type(void);
KChiptop3*		k_chiptop3_new(void);


#endif /* __K_CHIPTOP3_H__ */
