/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-07
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


#ifndef __K_CHIPTOP3_H__
#define __K_CHIPTOP3_H__


#include <stdio.h>
#include <glib-object.h>
#include "kchiptop2.h"
#include "kchiptop1.h"


G_BEGIN_DECLS


#define K_TYPE_CHIPTOP3									(k_chiptop3_get_type())
#define K_CHIPTOP3(obj)									(G_TYPE_CHECK_INSTANCE_CAST(obj, K_TYPE_CHIPTOP3, KChiptop3))
#define K_CHIPTOP3_CALSS(klass)              		(G_TYPE_CHECK_CLASS_CAST((klass), K_TYPE_CHIPTOP3, KChiptop3Class))
#define K_IS_CHIPTOP3(obj)                        		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), K_TYPE_CHIPTOP3))
#define K_IS_CHIPTOP3_CLASS(klass)         		(G_TYPE_CHECK_CLASS_TYPE ((klass), K_TYPE_CHIPTOP3))
#define K_CHIPTOP3_GET_CLASS(obj)         		(G_TYPE_INSTANCE_GET_CLASS ((obj), K_TYPE_CHIPTOP3, KChiptop3Class))


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
typedef struct 				_KChiptop3  KChiptop3;
typedef struct 				_KChiptop3Class  KChiptop3Class;
typedef struct 				_KChiptop3Private  KChiptop3Private;

/*	structure of PUDER	(0x1D02_230C) */
union _IoChiptopPuder {
	gulong		word[10];
	struct {
	/* PUDER76 (1D02_230Ch) */
		gulong				:32;
	/* PUDER98 (1D02_2310h) */
		gulong	p80			:1;
		gulong	p81			:1;
		gulong	p82			:1;
		gulong	p83			:1;
		gulong				:2;
		gulong	p86			:1;
		gulong	p87			:1;
		gulong	p90			:1;
		gulong	p91			:1;
		gulong	p92			:1;
		gulong	p93			:1;
		gulong				:20;
	/* PUDERBA (1D02_2314h) */
		gulong	pa0			:1;
		gulong	pa1			:1;
		gulong	pa2			:1;
		gulong	pa3			:1;
		gulong	pa4			:1;
		gulong	pa5			:1;
		gulong	pa6			:1;
		gulong	pa7			:1;
		gulong	pb0			:1;
		gulong	pb1			:1;
		gulong	pb2			:1;
		gulong	pb3			:1;
		gulong	pb4			:1;
		gulong				:19;
	/* PUDERDC (1D02_2318h) */
		gulong				:8;
		gulong	pd0			:1;
		gulong	pd1			:1;
		gulong	pd2			:1;
		gulong	pd3			:1;
		gulong	pd4			:1;
		gulong	pd5			:1;
		gulong	pd6			:1;
		gulong				:17;
	/* PUDERFE (1D02_231Ch) */
		gulong	pe0			:1;
		gulong	pe1			:1;
		gulong				:8;
		gulong	pf2			:1;
		gulong	pf3			:1;
		gulong	pf4			:1;
		gulong				:19;
	/* PUDERHG (1D02_2320h) */
		gulong	pg0			:1;
		gulong	pg1			:1;
		gulong	pg2			:1;
		gulong	pg3			:1;
		gulong	pg4			:1;
		gulong	pg5			:1;
		gulong	pg6			:1;
		gulong	pg7			:1;
		gulong	ph0			:1;
		gulong	ph1			:1;
		gulong	ph2			:1;
		gulong	ph3			:1;
		gulong				:20;
	/* PUDERJW (1D02_2324h) */
		gulong	pw0			:1;
		gulong	pw1			:1;
		gulong	pw2			:1;
		gulong	pw3			:1;
		gulong	pw4			:1;
		gulong	pw5			:1;
		gulong	pw6			:1;
		gulong	pw7			:1;
		gulong	pj0			:1;
		gulong	pj1			:1;
		gulong	pj2			:1;
		gulong	pj3			:1;
		gulong	pj4			:1;
		gulong	pj5			:1;
		gulong	pj6			:1;
		gulong	pj7			:1;
		gulong				:16;
	/* PUDERLK (1D02_2328h) */
		gulong	pk0			:1;
		gulong	pk1			:1;
		gulong	pk2			:1;
		gulong	pk3			:1;
		gulong	pk4			:1;
		gulong	pk5			:1;
		gulong	pk6			:1;
		gulong	pk7			:1;
		gulong	pl0			:1;
		gulong	pl1			:1;
		gulong	pl2			:1;
		gulong	pl3			:1;
		gulong	pl4			:1;
		gulong	pl5			:1;
		gulong				:18;
	/* PUDERNM (1D02_232Ch) */
		gulong	pm0			:1;
		gulong	pm1			:1;
		gulong				:1;
		gulong	pm3			:1;
		gulong	pm4			:1;
		gulong				:3;
		gulong	pn0			:1;
		gulong	pn1			:1;
		gulong				:1;
		gulong	pn3			:1;
		gulong	pn4			:1;
		gulong				:19;
	/* PUDERPY (1D02_2330h) */
		gulong	py0			:1;
		gulong	py1			:1;
		gulong	py2			:1;
		gulong	py3			:1;
		gulong	py4			:1;
		gulong	py5			:1;
		gulong	py6			:1;
		gulong	py7			:1;
		gulong	pp0			:1;
		gulong	pp1			:1;
		gulong	pp2			:1;
		gulong	pp3			:1;
		gulong				:20;
	}bit;
};

/*	structure of PUDCR	(0x1D02_2400) */
union _IoChiptopPudcr {
	gulong		word[10];
	struct {
	/* PUDCR76 (1D02_240Ch) */
		gulong				:32;
	/* PUDCR98 (1D02_2410h) */
		gulong	p80			:1;
		gulong	p81			:1;
		gulong	p82			:1;
		gulong	p83			:1;
		gulong				:2;
		gulong	p86			:1;
		gulong	p87			:1;
		gulong	p90			:1;
		gulong	p91			:1;
		gulong	p92			:1;
		gulong	p93			:1;
		gulong				:20;
	/* PUDCRBA (1D02_2414h) */
		gulong	pa0			:1;
		gulong	pa1			:1;
		gulong	pa2			:1;
		gulong	pa3			:1;
		gulong	pa4			:1;
		gulong	pa5			:1;
		gulong	pa6			:1;
		gulong	pa7			:1;
		gulong	pb0			:1;
		gulong	pb1			:1;
		gulong	pb2			:1;
		gulong	pb3			:1;
		gulong	pb4			:1;
		gulong				:19;
	/* PUDCRDC (1D02_2418h) */
		gulong				:8;
		gulong	pd0			:1;
		gulong	pd1			:1;
		gulong	pd2			:1;
		gulong	pd3			:1;
		gulong	pd4			:1;
		gulong	pd5			:1;
		gulong	pd6			:1;
		gulong				:17;
	/* PUDCRFE (1D02_241Ch) */
		gulong	pe0			:1;
		gulong	pe1			:1;
		gulong				:8;
		gulong	pf2			:1;
		gulong	pf3			:1;
		gulong	pf4			:1;
		gulong				:19;
	/* PUDCRHG (1D02_2420h) */
		gulong	pg0			:1;
		gulong	pg1			:1;
		gulong	pg2			:1;
		gulong	pg3			:1;
		gulong	pg4			:1;
		gulong	pg5			:1;
		gulong	pg6			:1;
		gulong	pg7			:1;
		gulong	ph0			:1;
		gulong	ph1			:1;
		gulong	ph2			:1;
		gulong	ph3			:1;
		gulong				:20;
	/* PUDCRJW (1D02_2424h) */
		gulong	pw0			:1;
		gulong	pw1			:1;
		gulong	pw2			:1;
		gulong	pw3			:1;
		gulong	pw4			:1;
		gulong	pw5			:1;
		gulong	pw6			:1;
		gulong	pw7			:1;
		gulong	pj0			:1;
		gulong	pj1			:1;
		gulong	pj2			:1;
		gulong	pj3			:1;
		gulong	pj4			:1;
		gulong	pj5			:1;
		gulong	pj6			:1;
		gulong	pj7			:1;
		gulong				:16;
	/* PUDCRLK (1D02_2428h) */
		gulong	pk0			:1;
		gulong	pk1			:1;
		gulong	pk2			:1;
		gulong	pk3			:1;
		gulong	pk4			:1;
		gulong	pk5			:1;
		gulong	pk6			:1;
		gulong	pk7			:1;
		gulong	pl0			:1;
		gulong	pl1			:1;
		gulong	pl2			:1;
		gulong	pl3			:1;
		gulong	pl4			:1;
		gulong	pl5			:1;
		gulong				:18;
	/* PUDCRNM (1D02_242Ch) */
		gulong	pm0			:1;
		gulong	pm1			:1;
		gulong				:1;
		gulong	pm3			:1;
		gulong	pm4			:1;
		gulong				:3;
		gulong	pn0			:1;
		gulong	pn1			:1;
		gulong				:1;
		gulong	pn3			:1;
		gulong	pn4			:1;
		gulong				:19;
	/* PUDCRPY (1D02_2430h) */
		gulong	py0			:1;
		gulong	py1			:1;
		gulong	py2			:1;
		gulong	py3			:1;
		gulong	py4			:1;
		gulong	py5			:1;
		gulong	py6			:1;
		gulong	py7			:1;
		gulong	pp0			:1;
		gulong	pp1			:1;
		gulong	pp2			:1;
		gulong	pp3			:1;
		gulong				:20;
	}bit;
};

/*	structure of PERSEL1 (1D02_0000h) */
union _IoChiptopPersel1 {
	gulong word;
	struct {
		gulong	i2c0cnt		:2;
		gulong	sdanc0		:1;
		gulong	sclnc0		:1;
		gulong	i2c1cnt		:2;
		gulong	sdanc1		:1;
		gulong	sclnc1		:1;
		gulong	i2c2cnt		:2;
		gulong	sdanc2		:1;
		gulong	sclnc2		:1;
		gulong	dvwt2		:1;
		gulong	dhwt3		:1;
		gulong				:2;
		gulong	au0do0c		:1;
		gulong	au0do1c		:1;
		gulong	au1doc		:1;
		gulong	au0mcc		:1;
		gulong	au1mcc		:1;
		gulong	rlsel3		:1;
		gulong	rlsel4		:1;
		gulong	rlsel5		:1;
		gulong	intvdsel	:3;
		gulong				:5;
	} bit;
};

/*	structure of PERSEL2 (1D02_0004h) */
union _IoChiptopPersel2 {
	gulong word;
	struct {
		gulong	udctrg		:1;
		gulong	udc0am		:1;
		gulong	udc0bm		:1;
		gulong	udc1am		:1;
		gulong	udc1bm		:1;
		gulong	udc2am		:1;
		gulong	udc2bm		:1;
		gulong	udc3am		:1;
		gulong	udc3bm		:1;
		gulong	udc4am		:1;
		gulong	udc4bm		:1;
		gulong	udc5am		:1;
		gulong	udc5bm		:1;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
		gulong				:19;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE

#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
		gulong	spimsen0	:1;
		gulong	spimsen1	:1;
		gulong	spimsen2	:1;
		gulong				:16;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	} bit;
};

/*	structure of PERSEL3 (1D02_0008h) */
union _IoChiptopPersel3 {
	gulong word;
	struct {
		gulong	au1wpps		:1;
		gulong	au0wp11		:1;
		gulong	snh2wp04	:1;
		gulong	snv2wp05	:1;
		gulong	sna2wp06	:1;
		gulong	snh3wp07	:1;
		gulong	snv3wp08	:1;
		gulong	sna3wp09	:1;
		gulong	u1vbsou5	:1;
		gulong	u2vbsou6	:1;
		gulong	u2idwp14	:1;
		gulong	prt1sou3	:1;
		gulong	pxw0wp12	:1;
		gulong	pxw1sou7	:1;
		gulong	pxc0sck7	:1;
		gulong	pxc1wp15	:1;
		gulong	sck4wp13	:1;
		gulong	s3lsou5wp14	:2;
		gulong	s3swp15		:1;
		gulong	rts1sck2	:1;
		gulong				:1;
		gulong	u1idwp13	:1;
		gulong	prt0sck3	:1;
		gulong				:8;
	} bit;
};

/*	structure of PERSEL4 (1D02_000Ch) */
union _IoChiptopPersel4 {
	gulong word;
	struct {
		gulong	ei22ud0a	:1;
		gulong	ei23ud0b	:1;
		gulong	ei24ud1a	:1;
		gulong	ei25ud1b	:1;
		gulong	ei26ud2a	:1;
		gulong	ei27ud2b	:1;
		gulong	ei28ud3a	:1;
		gulong	ei29ud3b	:1;
		gulong	ei30ud4a	:1;
		gulong	ei31ud4b	:1;
		gulong	sd3cdxs		:1;
		gulong	sd3wps		:1;
		gulong	u1ocdxs		:1;
		gulong	u1iddigs	:1;
		gulong	u2ocdxs		:1;
		gulong	u2iddigs	:1;
		gulong				:16;
	} bit;
};

/*	structure of MSELC (1D02_0010h) */
union _IoChiptopMselc {
	gulong word;
	struct {
		gulong	msel		:4;
		gulong				:28;
	} bit;
};

/*	structure of DBCNT1 (1D02_0014h) */
union _IoChiptopDbcnt1 {
	gulong word;
	struct {
		gulong				:14;
		gulong	t07dc		:2;
		gulong	t08dc		:2;
		gulong	t09dc		:2;
		gulong	t10dc		:2;
		gulong	t11dc		:2;
		gulong	t12dc		:2;
		gulong	t13dc		:2;
		gulong	t14dc		:2;
		gulong	t15dc		:2;
	} bit;
};

/*	structure of DBCNT2 (1D02_0018h) */
union _IoChiptopDbcnt2 {
	gulong word;
	struct {
		gulong	t16dc		:2;
		gulong	t17dc		:2;
		gulong	t18dc		:2;
		gulong	t19dc		:2;
		gulong	t20dc		:2;
		gulong	t21dc		:2;
		gulong	t22dc		:2;
		gulong	t23dc		:2;
		gulong	t24dc		:2;
		gulong	t25dc		:2;
		gulong	t26dc		:2;
		gulong	t27dc		:2;
		gulong	t28dc		:2;
		gulong	t29dc		:2;
		gulong	t30dc		:2;
		gulong	t31dc		:2;
	} bit;
};

/*	structure of DBCNT3 (1D02_001Ch) */
union _IoChiptopDbcnt3 {
	gulong word;
	struct {
		gulong	t32dc		:2;
		gulong	t33dc		:2;
		gulong	t34dc		:2;
		gulong	t35dc		:2;
		gulong	t36dc		:2;
		gulong	t37dc		:2;
		gulong	t38dc		:2;
		gulong	t39dc		:2;
		gulong	t40dc		:2;
		gulong	t41dc		:2;
		gulong	t42dc		:2;
		gulong	t43dc		:2;
		gulong	t44dc		:2;
		gulong	t45dc		:2;
		gulong	t46dc		:2;
		gulong	t47dc		:2;
	} bit;
};

/*	structure of DBCNT4 (1D02_0020h) */
union _IoChiptopDbcnt4 {
	gulong word;
	struct {
		gulong	t48dc		:2;
		gulong	t49dc		:2;
		gulong	t50dc		:2;
		gulong	t51dc		:2;
		gulong	t52dc		:2;
		gulong	t53dc		:2;
		gulong	t54dc		:2;
		gulong	t55dc		:2;
		gulong	t56dc		:2;
		gulong	t57dc		:2;
		gulong	t58dc		:2;
		gulong	t59dc		:2;
		gulong	t60dc		:2;
		gulong	t61dc		:2;
		gulong	t62dc		:2;
		gulong	t63dc		:2;
	} bit;
};

/*	structure of DBCNT5 (1D02_0024h) */
union _IoChiptopDbcnt5 {
	gulong word;
	struct {
		gulong	t64dc		:2;
		gulong	t65dc		:2;
		gulong	t66dc		:2;
		gulong				:26;
	} bit;
};

/*	structure of PUDCNT (1D02_0028h) */
union _IoChiptopPudcnt {
	gulong word;
	struct {
		gulong	emmcnics	:2;
		gulong	emdatpue	:1;
		gulong	emcmdpue	:1;
		gulong	emdspde		:1;
		gulong	nfdatpue	:1;
		gulong	nfrbxpue	:1;
		gulong	nfdqspue	:1;
		gulong	sp1misope	:1;
		gulong	sp1mosipe	:1;
		gulong	sp1sckpe	:1;
		gulong	sp1cs0pe	:1;
		gulong	sp1misoudc	:1;
		gulong	sp1mosiudc	:1;
		gulong	sp1sckudc	:1;
		gulong	sp1cs0udc	:1;
		gulong				:16;
	} bit;
};

/*	structure of PLLFREQ1	(1D02_3000h)	*/
union _IoChiptopPllfreq1 {
	gulong		word;
	struct {
		gulong	pllidiv			:8;
		gulong					:24;
	}bit;
};

/*	structure of ODIVCH0	(1D02_3040h)	*/
union _IoChiptopOdivch0 {
	gulong		word;
	struct {
		gulong	odivch0num		:8;
		gulong					:24;
	}bit;
};

/*	structure of CMDEN	(1D02_3080h)	*/
union _IoChiptopCmden {
	gulong		word;
	struct {
		gulong	cmden			:3;
		gulong					:29;
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
	guchar dmy002c0fff[0x1000-0x002C];
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
	guchar dmy10981fff[0x2000-0x1098];
	/* 1D02_(2000 - 200Bh) */
	guchar dmy2000200b[0x200C-0x2000];
	/* 1D02_(200C - 2033h) */
	IoChiptopPdr			pdr;
	/* 1D02_(2034 - 20FFh) */
	guchar dmy203420ff[0x2100-0x2034];
	/* 1D02_(2100 - 210Bh) */
	guchar dmy2100210b[0x210C-0x2100];
	/* 1D02_(210C - 2133h) */
	IoChiptopDdr			ddr;
	/* 1D02_(2134 - 21FFh) */
	guchar dmy213421ff[0x2200-0x2134];
	/* 1D02_(2200 - 220Bh) */
	guchar dmy2200220b[0x220C-0x2200];
	/* 1D02_(220C - 2233h) */
	IoChiptopEpcr			epcr;
	/* 1D02_(2234 - 22FFh) */
	guchar dmy223422ff[0x2300-0x2234];
	/* 1D02_(2300 - 230Bh) */
	guchar dmy2300230b[0x230C-0x2300];
	/* 1D02_(230C - 2333h) */
	IoChiptopPuder			puder;
	/* 1D02_(2334 - 23FFh) */
	guchar dmy233423ff[0x2400-0x2334];
	/* 1D02_(2400 - 240Bh) */
	guchar dmy2400240b[0x240C-0x2400];
	/* 1D02_(240C - 2433h) */
	IoChiptopPudcr			pudcr;
	/* 1D02_(2434 - 2FFFh) */
	guchar dmy24342fff[0x3000-0x2434];
	/* 1D02_(3000 - 3003h) */
	IoChiptopPllfreq1		pllfreq1;
	/* 1D02_(3004 - 303Fh) */
	guchar dmy3004303f[0x3040-0x3004];
	/* 1D02_(3040 - 3043h) */
	IoChiptopOdivch0		odivch0;
	/* 1D02_(3044 - 307Fh) */
	guchar dmy3044307f[0x3080-0x3044];
	/* 1D02_(3080 - 3083h) */
	IoChiptopCmden			cmden;
	/* 1D02_(3084 - 3FFFh) */
	guchar dmy3084Ffff[0x4000-0x3084];
};

struct _KChiptop3
{
	GObject    parent;
};

struct _KChiptop3Class
{
	GObject    parentclass;
};

extern volatile IoChiptop ioChiptop;


GType 							k_chiptop3_get_type(void) G_GNUC_CONST;
KChiptop3 *         		k_chiptop3_new(void);


G_END_DECLS


#endif /* __K_CHIPTOP3_H__ */
