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


#ifndef __K_CHIPTOP2_H__
#define __K_CHIPTOP2_H__


//#include <klib.h>
#include <stdio.h>
#include <glib-object.h>


//#define K_TYPE_CHIPTOP2			(k_chiptop2_get_type())
//#define K_CHIPTOP2(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, KChiptop2))
//#define K_IS_CHIPTOP2(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, K_TYPE_CHIPTOP2))


typedef union 				_IoChiprstCrswr IoChiprstCrswr;
typedef union 				_IoChiprstCrrrs IoChiprstCrrrs;
typedef union 				_IoChiprstCrrsm IoChiprstCrrsm;
typedef union 				_IoChiptopPdr IoChiptopPdr;
typedef union 				_IoChiptopDdr IoChiptopDdr;
typedef union 				_IoChiptopEpcr IoChiptopEpcr;
//typedef struct 				_KChiptop2 KChiptop2;
//typedef struct 				_KChiptop2Private KChiptop2Private;

/*	structure of CRSWR	(1D02_108Ch)	*/
union _IoChiprstCrswr {
	gulong		word;
	struct {
		gulong	srreq		:1;
		gulong				:31;
	}bit;
};

/*	structure of CRRRS	(1D02_1090h)	*/
union _IoChiprstCrrrs {
	gulong		word;
	struct {
		gulong	ribsr		:1;
		gulong	heippasyncsr:1;
		gulong	heippsyncsr	:1;
		gulong	hevdfsr		:1;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
		gulong	hepxfsr		:1;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE

#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
		gulong	hevencsr	:1;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE

// --- REMOVE_ES_COMPILE_OPT END ---
		gulong	dspsr		:1;
		gulong				:2;
		gulong	cpu0Sr		:1;
		gulong	cpu1Sr		:1;
		gulong	cpu2Sr		:1;
		gulong	cpu3Sr		:1;
		gulong				:20;
	}bit;
};

/*	structure of CRRSM	(1D02_1094h)	*/
union _IoChiprstCrrsm {
	gulong		word;
	struct {
		gulong	wdrstTemp2			:1;
		gulong	swrstTemp2			:1;
		gulong	srstTemp2			:1;
		gulong	porstTemp2			:1;
		gulong					:28;
	}bit;
};

/*	structure of PDR	(1D02_200Ch)	*/
union _IoChiptopPdr {
	gulong		word[10];
	struct {
	/* PDR76 (1D02_200Ch) */
		gulong	p60			:1;
		gulong	p61			:1;
		gulong	p62			:1;
		gulong	p63			:1;
		gulong	p64			:1;
		gulong	p65			:1;
		gulong	p66			:1;
		gulong	p67			:1;
		gulong	p70			:1;
		gulong	p71			:1;
		gulong	p72			:1;
		gulong	p73			:1;
		gulong	p74			:1;
		gulong	p75			:1;
		gulong	p76			:1;
		gulong	p77			:1;
		gulong	pwe60		:1;
		gulong	pwe61		:1;
		gulong	pwe62		:1;
		gulong	pwe63		:1;
		gulong	pwe64		:1;
		gulong	pwe65		:1;
		gulong	pwe66		:1;
		gulong	pwe67		:1;
		gulong	pwe70		:1;
		gulong	pwe71		:1;
		gulong	pwe72		:1;
		gulong	pwe73		:1;
		gulong	pwe74		:1;
		gulong	pwe75		:1;
		gulong	pwe76		:1;
		gulong	pwe77		:1;
	/* PDR98 (1D02_2010h) */
		gulong	p80			:1;
		gulong	p81			:1;
		gulong	p82			:1;
		gulong	p83			:1;
		gulong	p84			:1;
		gulong	p85			:1;
		gulong	p86			:1;
		gulong	p87			:1;
		gulong	p90			:1;
		gulong	p91			:1;
		gulong	p92			:1;
		gulong	p93			:1;
		gulong				:4;
		gulong	pwe80		:1;
		gulong	pwe81		:1;
		gulong	pwe82		:1;
		gulong	pwe83		:1;
		gulong	pwe84		:1;
		gulong	pwe85		:1;
		gulong	pwe86		:1;
		gulong	pwe87		:1;
		gulong	pwe90		:1;
		gulong	pwe91		:1;
		gulong	pwe92		:1;
		gulong	pwe93		:1;
		gulong				:4;
	/* PDRBA (1D02_2014h) */
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
		gulong				:3;
		gulong	pwea0		:1;
		gulong	pwea1		:1;
		gulong	pwea2		:1;
		gulong	pwea3		:1;
		gulong	pwea4		:1;
		gulong	pwea5		:1;
		gulong	pwea6		:1;
		gulong	pwea7		:1;
		gulong	pweb0		:1;
		gulong	pweb1		:1;
		gulong	pweb2		:1;
		gulong	pweb3		:1;
		gulong	pweb4		:1;
		gulong				:3;
	/* PDRDC (1D02_2018h) */
		gulong	pc0			:1;
		gulong	pc1			:1;
		gulong	pc2			:1;
		gulong	pc3			:1;
		gulong	pc4			:1;
		gulong	pc5			:1;
		gulong				:2;
		gulong	pd0			:1;
		gulong	pd1			:1;
		gulong	pd2			:1;
		gulong	pd3			:1;
		gulong	pd4			:1;
		gulong	pd5			:1;
		gulong	pd6			:1;
		gulong				:1;
		gulong	pwec0		:1;
		gulong	pwec1		:1;
		gulong	pwec2		:1;
		gulong	pwec3		:1;
		gulong	pwec4		:1;
		gulong	pwec5		:1;
		gulong				:2;
		gulong	pwed0		:1;
		gulong	pwed1		:1;
		gulong	pwed2		:1;
		gulong	pwed3		:1;
		gulong	pwed4		:1;
		gulong	pwed5		:1;
		gulong	pwed6		:1;
		gulong				:1;
	/* PDRFE (1D02_201Ch) */
		gulong	pe0			:1;
		gulong	pe1			:1;
		gulong	pe2			:1;
		gulong	pe3			:1;
		gulong	pe4			:1;
		gulong	pe5			:1;
		gulong				:2;
		gulong	pf0			:1;
		gulong	pf1			:1;
		gulong	pf2			:1;
		gulong	pf3			:1;
		gulong	pf4			:1;
		gulong				:3;
		gulong	pwee0		:1;
		gulong	pwee1		:1;
		gulong	pwee2		:1;
		gulong	pwee3		:1;
		gulong	pwee4		:1;
		gulong	pwee5		:1;
		gulong				:2;
		gulong	pwef0		:1;
		gulong	pwef1		:1;
		gulong	pwef2		:1;
		gulong	pwef3		:1;
		gulong	pwef4		:1;
		gulong				:3;
	/* PDRHG (1D02_2020h) */
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
		gulong				:4;
		gulong	pweg0		:1;
		gulong	pweg1		:1;
		gulong	pweg2		:1;
		gulong	pweg3		:1;
		gulong	pweg4		:1;
		gulong	pweg5		:1;
		gulong	pweg6		:1;
		gulong	pweg7		:1;
		gulong	pweh0		:1;
		gulong	pweh1		:1;
		gulong	pweh2		:1;
		gulong	pweh3		:1;
		gulong				:4;
	/* PDRJW (1D02_2024h) */
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
		gulong	pwew0		:1;
		gulong	pwew1		:1;
		gulong	pwew2		:1;
		gulong	pwew3		:1;
		gulong	pwew4		:1;
		gulong	pwew5		:1;
		gulong	pwew6		:1;
		gulong	pwew7		:1;
		gulong	pwej0		:1;
		gulong	pwej1		:1;
		gulong	pwej2		:1;
		gulong	pwej3		:1;
		gulong	pwej4		:1;
		gulong	pwej5		:1;
		gulong	pwej6		:1;
		gulong	pwej7		:1;
	/* PDRLK (1D02_2028h) */
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
		gulong				:2;
		gulong	pwek0		:1;
		gulong	pwek1		:1;
		gulong	pwek2		:1;
		gulong	pwek3		:1;
		gulong	pwek4		:1;
		gulong	pwek5		:1;
		gulong	pwek6		:1;
		gulong	pwek7		:1;
		gulong	pwel0		:1;
		gulong	pwel1		:1;
		gulong	pwel2		:1;
		gulong	pwel3		:1;
		gulong	pwel4		:1;
		gulong	pwel5		:1;
		gulong				:2;
	/* PDRNM (1D02_202Ch) */
		gulong	pm0			:1;
		gulong	pm1			:1;
		gulong	pm2			:1;
		gulong	pm3			:1;
		gulong	pm4			:1;
		gulong				:3;
		gulong	pn0			:1;
		gulong	pn1			:1;
		gulong	pn2			:1;
		gulong	pn3			:1;
		gulong	pn4			:1;
		gulong				:3;
		gulong	pwem0		:1;
		gulong	pwem1		:1;
		gulong	pwem2		:1;
		gulong	pwem3		:1;
		gulong	pwem4		:1;
		gulong				:3;
		gulong	pwen0		:1;
		gulong	pwen1		:1;
		gulong	pwen2		:1;
		gulong	pwen3		:1;
		gulong	pwen4		:1;
		gulong				:3;
	/* PDRPY (1D02_2030h) */
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
		gulong				:4;
		gulong	pwey0		:1;
		gulong	pwey1		:1;
		gulong	pwey2		:1;
		gulong	pwey3		:1;
		gulong	pwey4		:1;
		gulong	pwey5		:1;
		gulong	pwey6		:1;
		gulong	pwey7		:1;
		gulong	pwep0		:1;
		gulong	pwep1		:1;
		gulong	pwep2		:1;
		gulong	pwep3		:1;
		gulong				:4;
	}bit;
};

/*	structure of DDR	(1D02_210Ch)	*/
union _IoChiptopDdr {
	gulong		word[10];
	struct {
	/* DDR76 (1D02_210Ch) */
		gulong	p60			:1;
		gulong	p61			:1;
		gulong	p62			:1;
		gulong	p63			:1;
		gulong	p64			:1;
		gulong	p65			:1;
		gulong	p66			:1;
		gulong	p67			:1;
		gulong	p70			:1;
		gulong	p71			:1;
		gulong	p72			:1;
		gulong	p73			:1;
		gulong	p74			:1;
		gulong	p75			:1;
		gulong	p76			:1;
		gulong	p77			:1;
		gulong				:16;
	/* DDR98 (1D02_2110h) */
		gulong	p80			:1;
		gulong	p81			:1;
		gulong	p82			:1;
		gulong	p83			:1;
		gulong	p84			:1;
		gulong	p85			:1;
		gulong	p86			:1;
		gulong	p87			:1;
		gulong	p90			:1;
		gulong	p91			:1;
		gulong	p92			:1;
		gulong	p93			:1;
		gulong				:20;
	/* DDRBA (1D02_2114h) */
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
	/* DDRDC (1D02_2118h) */
		gulong	pc0			:1;
		gulong	pc1			:1;
		gulong	pc2			:1;
		gulong	pc3			:1;
		gulong	pc4			:1;
		gulong	pc5			:1;
		gulong				:2;
		gulong	pd0			:1;
		gulong	pd1			:1;
		gulong	pd2			:1;
		gulong	pd3			:1;
		gulong	pd4			:1;
		gulong	pd5			:1;
		gulong	pd6			:1;
		gulong				:17;
	/* DDRFE (1D02_211Ch) */
		gulong	pe0			:1;
		gulong	pe1			:1;
		gulong	pe2			:1;
		gulong	pe3			:1;
		gulong	pe4			:1;
		gulong	pe5			:1;
		gulong				:2;
		gulong	pf0			:1;
		gulong	pf1			:1;
		gulong	pf2			:1;
		gulong	pf3			:1;
		gulong	pf4			:1;
		gulong				:19;
	/* DDRHG (1D02_2120h) */
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
	/* DDRJW (1D02_2124h) */
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
	/* DDRLK (1D02_2128h) */
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
	/* DDRNM (1D02_212Ch) */
		gulong	pm0			:1;
		gulong	pm1			:1;
		gulong	pm2			:1;
		gulong	pm3			:1;
		gulong	pm4			:1;
		gulong				:3;
		gulong	pn0			:1;
		gulong	pn1			:1;
		gulong	pn2			:1;
		gulong	pn3			:1;
		gulong	pn4			:1;
		gulong				:19;
	/* DDRPY (1D02_2130h) */
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

/*	structure of EPCR	(0x1D02_220C) */
union _IoChiptopEpcr {
	gulong		word[10];
	struct {
	/* EPCR76 (1D02_220Ch) */
		gulong	p60			:1;
		gulong	p61			:1;
		gulong	p62			:1;
		gulong	p63			:1;
		gulong				:28;
	/* EPCR98 (1D02_2210h) */
		gulong	p80			:1;
		gulong	p81			:1;
		gulong	p82			:1;
		gulong	p83			:1;
		gulong	p84			:1;
		gulong	p85			:1;
		gulong	p86			:1;
		gulong	p87			:1;
		gulong	p90			:1;
		gulong				:1;
		gulong	p92			:1;
		gulong				:21;
	/* EPCRBA (1D02_2214h) */
		gulong	pa0			:1;
		gulong	pa1			:1;
		gulong				:1;
		gulong	pa3			:1;
		gulong	pa4			:1;
		gulong	pa5			:1;
		gulong				:1;
		gulong	pa7			:1;
		gulong	pb0			:1;
		gulong	pb1			:1;
		gulong	pb2			:1;
		gulong	pb3			:1;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
		gulong	pb4			:1;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE

#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
		gulong	trgen		:1;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE

// --- REMOVE_ES_COMPILE_OPT END ---
		gulong				:19;
	/* EPCRDC (1D02_2218h) */
		gulong	pc0			:1;
		gulong	pc1			:1;
		gulong	pc2			:1;
		gulong	pc3			:1;
		gulong	pc4			:1;
		gulong	pc5			:1;
		gulong				:2;
		gulong	pd0			:1;
		gulong	pd1			:1;
		gulong	pd2			:1;
		gulong	pd3			:1;
		gulong	pd4			:1;
		gulong	pd5			:1;
		gulong	pd6			:1;
		gulong				:17;
	/* EPCRFE (1D02_221Ch) */
		gulong				:1;
		gulong	pe1			:1;
		gulong				:1;
		gulong	pe3			:1;
		gulong				:1;
		gulong	pe5			:1;
		gulong				:6;
		gulong	pf4			:1;
		gulong				:19;
	/* EPCRHG (1D02_2220h) */
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
	/* EPCRJW (1D02_2224h) */
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
	/* EPCRLK (1D02_2228h) */
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
	/* EPCRNM (1D02_222Ch) */
		gulong				:1;
		gulong	pm1			:1;
		gulong				:1;
		gulong	pm3			:1;
		gulong	pm4			:1;
		gulong				:4;
		gulong	pn1			:1;
		gulong				:1;
		gulong	pn3			:1;
		gulong	pn4			:1;
		gulong				:19;
	/* EPCRPY (1D02_2230h) */
		gulong	py0			:1;
		gulong	py1			:1;
		gulong				:2;
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

//struct _KChiptop2 {
//	KObject parent;
//};
//
//
//KConstType 	k_chiptop2_get_type(void);
//KChiptop2*		k_chiptop2_new(void);


#endif /* __K_CHIPTOP2_H__ */
