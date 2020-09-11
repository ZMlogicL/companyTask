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


#include <klib.h>


#define K_TYPE_CHIPTOP2			(k_chiptop2_get_type())
#define K_CHIPTOP2(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, KChiptop2))
#define K_IS_CHIPTOP2(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, K_TYPE_CHIPTOP2))


typedef union 				_IoChiprstCrswr IoChiprstCrswr;
typedef union 				_IoChiprstCrrrs IoChiprstCrrrs;
typedef union 				_IoChiprstCrrsm IoChiprstCrrsm;
typedef union 				_IoChiptopPdr IoChiptopPdr;
typedef union 				_IoChiptopDdr IoChiptopDdr;
typedef union 				_IoChiptopEpcr IoChiptopEpcr;
typedef struct 				_KChiptop2 KChiptop2;
typedef struct 				_KChiptop2Private KChiptop2Private;

/*	structure of CRSWR	(1D02_108Ch)	*/
union _IoChiprstCrswr {
	kulong		word;
	struct {
		kulong	srreq		:1;
		kulong				:31;
	}bit;
};

/*	structure of CRRRS	(1D02_1090h)	*/
union _IoChiprstCrrrs {
	kulong		word;
	struct {
		kulong	ribsr		:1;
		kulong	heippasyncsr:1;
		kulong	heippsyncsr	:1;
		kulong	hevdfsr		:1;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
		kulong	hepxfsr		:1;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE

#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
		kulong	hevencsr	:1;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE

// --- REMOVE_ES_COMPILE_OPT END ---
		kulong	dspsr		:1;
		kulong				:2;
		kulong	cpu0Sr		:1;
		kulong	cpu1Sr		:1;
		kulong	cpu2Sr		:1;
		kulong	cpu3Sr		:1;
		kulong				:20;
	}bit;
};

/*	structure of CRRSM	(1D02_1094h)	*/
union _IoChiprstCrrsm {
	kulong		word;
	struct {
		kulong	wdrstTemp2			:1;
		kulong	swrstTemp2			:1;
		kulong	srstTemp2			:1;
		kulong	porstTemp2			:1;
		kulong					:28;
	}bit;
};

/*	structure of PDR	(1D02_200Ch)	*/
union _IoChiptopPdr {
	kulong		word[10];
	struct {
	/* PDR76 (1D02_200Ch) */
		kulong	p60			:1;
		kulong	p61			:1;
		kulong	p62			:1;
		kulong	p63			:1;
		kulong	p64			:1;
		kulong	p65			:1;
		kulong	p66			:1;
		kulong	p67			:1;
		kulong	p70			:1;
		kulong	p71			:1;
		kulong	p72			:1;
		kulong	p73			:1;
		kulong	p74			:1;
		kulong	p75			:1;
		kulong	p76			:1;
		kulong	p77			:1;
		kulong	pwe60		:1;
		kulong	pwe61		:1;
		kulong	pwe62		:1;
		kulong	pwe63		:1;
		kulong	pwe64		:1;
		kulong	pwe65		:1;
		kulong	pwe66		:1;
		kulong	pwe67		:1;
		kulong	pwe70		:1;
		kulong	pwe71		:1;
		kulong	pwe72		:1;
		kulong	pwe73		:1;
		kulong	pwe74		:1;
		kulong	pwe75		:1;
		kulong	pwe76		:1;
		kulong	pwe77		:1;
	/* PDR98 (1D02_2010h) */
		kulong	p80			:1;
		kulong	p81			:1;
		kulong	p82			:1;
		kulong	p83			:1;
		kulong	p84			:1;
		kulong	p85			:1;
		kulong	p86			:1;
		kulong	p87			:1;
		kulong	p90			:1;
		kulong	p91			:1;
		kulong	p92			:1;
		kulong	p93			:1;
		kulong				:4;
		kulong	pwe80		:1;
		kulong	pwe81		:1;
		kulong	pwe82		:1;
		kulong	pwe83		:1;
		kulong	pwe84		:1;
		kulong	pwe85		:1;
		kulong	pwe86		:1;
		kulong	pwe87		:1;
		kulong	pwe90		:1;
		kulong	pwe91		:1;
		kulong	pwe92		:1;
		kulong	pwe93		:1;
		kulong				:4;
	/* PDRBA (1D02_2014h) */
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
		kulong				:3;
		kulong	pwea0		:1;
		kulong	pwea1		:1;
		kulong	pwea2		:1;
		kulong	pwea3		:1;
		kulong	pwea4		:1;
		kulong	pwea5		:1;
		kulong	pwea6		:1;
		kulong	pwea7		:1;
		kulong	pweb0		:1;
		kulong	pweb1		:1;
		kulong	pweb2		:1;
		kulong	pweb3		:1;
		kulong	pweb4		:1;
		kulong				:3;
	/* PDRDC (1D02_2018h) */
		kulong	pc0			:1;
		kulong	pc1			:1;
		kulong	pc2			:1;
		kulong	pc3			:1;
		kulong	pc4			:1;
		kulong	pc5			:1;
		kulong				:2;
		kulong	pd0			:1;
		kulong	pd1			:1;
		kulong	pd2			:1;
		kulong	pd3			:1;
		kulong	pd4			:1;
		kulong	pd5			:1;
		kulong	pd6			:1;
		kulong				:1;
		kulong	pwec0		:1;
		kulong	pwec1		:1;
		kulong	pwec2		:1;
		kulong	pwec3		:1;
		kulong	pwec4		:1;
		kulong	pwec5		:1;
		kulong				:2;
		kulong	pwed0		:1;
		kulong	pwed1		:1;
		kulong	pwed2		:1;
		kulong	pwed3		:1;
		kulong	pwed4		:1;
		kulong	pwed5		:1;
		kulong	pwed6		:1;
		kulong				:1;
	/* PDRFE (1D02_201Ch) */
		kulong	pe0			:1;
		kulong	pe1			:1;
		kulong	pe2			:1;
		kulong	pe3			:1;
		kulong	pe4			:1;
		kulong	pe5			:1;
		kulong				:2;
		kulong	pf0			:1;
		kulong	pf1			:1;
		kulong	pf2			:1;
		kulong	pf3			:1;
		kulong	pf4			:1;
		kulong				:3;
		kulong	pwee0		:1;
		kulong	pwee1		:1;
		kulong	pwee2		:1;
		kulong	pwee3		:1;
		kulong	pwee4		:1;
		kulong	pwee5		:1;
		kulong				:2;
		kulong	pwef0		:1;
		kulong	pwef1		:1;
		kulong	pwef2		:1;
		kulong	pwef3		:1;
		kulong	pwef4		:1;
		kulong				:3;
	/* PDRHG (1D02_2020h) */
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
		kulong				:4;
		kulong	pweg0		:1;
		kulong	pweg1		:1;
		kulong	pweg2		:1;
		kulong	pweg3		:1;
		kulong	pweg4		:1;
		kulong	pweg5		:1;
		kulong	pweg6		:1;
		kulong	pweg7		:1;
		kulong	pweh0		:1;
		kulong	pweh1		:1;
		kulong	pweh2		:1;
		kulong	pweh3		:1;
		kulong				:4;
	/* PDRJW (1D02_2024h) */
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
		kulong	pwew0		:1;
		kulong	pwew1		:1;
		kulong	pwew2		:1;
		kulong	pwew3		:1;
		kulong	pwew4		:1;
		kulong	pwew5		:1;
		kulong	pwew6		:1;
		kulong	pwew7		:1;
		kulong	pwej0		:1;
		kulong	pwej1		:1;
		kulong	pwej2		:1;
		kulong	pwej3		:1;
		kulong	pwej4		:1;
		kulong	pwej5		:1;
		kulong	pwej6		:1;
		kulong	pwej7		:1;
	/* PDRLK (1D02_2028h) */
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
		kulong				:2;
		kulong	pwek0		:1;
		kulong	pwek1		:1;
		kulong	pwek2		:1;
		kulong	pwek3		:1;
		kulong	pwek4		:1;
		kulong	pwek5		:1;
		kulong	pwek6		:1;
		kulong	pwek7		:1;
		kulong	pwel0		:1;
		kulong	pwel1		:1;
		kulong	pwel2		:1;
		kulong	pwel3		:1;
		kulong	pwel4		:1;
		kulong	pwel5		:1;
		kulong				:2;
	/* PDRNM (1D02_202Ch) */
		kulong	pm0			:1;
		kulong	pm1			:1;
		kulong	pm2			:1;
		kulong	pm3			:1;
		kulong	pm4			:1;
		kulong				:3;
		kulong	pn0			:1;
		kulong	pn1			:1;
		kulong	pn2			:1;
		kulong	pn3			:1;
		kulong	pn4			:1;
		kulong				:3;
		kulong	pwem0		:1;
		kulong	pwem1		:1;
		kulong	pwem2		:1;
		kulong	pwem3		:1;
		kulong	pwem4		:1;
		kulong				:3;
		kulong	pwen0		:1;
		kulong	pwen1		:1;
		kulong	pwen2		:1;
		kulong	pwen3		:1;
		kulong	pwen4		:1;
		kulong				:3;
	/* PDRPY (1D02_2030h) */
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
		kulong				:4;
		kulong	pwey0		:1;
		kulong	pwey1		:1;
		kulong	pwey2		:1;
		kulong	pwey3		:1;
		kulong	pwey4		:1;
		kulong	pwey5		:1;
		kulong	pwey6		:1;
		kulong	pwey7		:1;
		kulong	pwep0		:1;
		kulong	pwep1		:1;
		kulong	pwep2		:1;
		kulong	pwep3		:1;
		kulong				:4;
	}bit;
};

/*	structure of DDR	(1D02_210Ch)	*/
union _IoChiptopDdr {
	kulong		word[10];
	struct {
	/* DDR76 (1D02_210Ch) */
		kulong	p60			:1;
		kulong	p61			:1;
		kulong	p62			:1;
		kulong	p63			:1;
		kulong	p64			:1;
		kulong	p65			:1;
		kulong	p66			:1;
		kulong	p67			:1;
		kulong	p70			:1;
		kulong	p71			:1;
		kulong	p72			:1;
		kulong	p73			:1;
		kulong	p74			:1;
		kulong	p75			:1;
		kulong	p76			:1;
		kulong	p77			:1;
		kulong				:16;
	/* DDR98 (1D02_2110h) */
		kulong	p80			:1;
		kulong	p81			:1;
		kulong	p82			:1;
		kulong	p83			:1;
		kulong	p84			:1;
		kulong	p85			:1;
		kulong	p86			:1;
		kulong	p87			:1;
		kulong	p90			:1;
		kulong	p91			:1;
		kulong	p92			:1;
		kulong	p93			:1;
		kulong				:20;
	/* DDRBA (1D02_2114h) */
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
	/* DDRDC (1D02_2118h) */
		kulong	pc0			:1;
		kulong	pc1			:1;
		kulong	pc2			:1;
		kulong	pc3			:1;
		kulong	pc4			:1;
		kulong	pc5			:1;
		kulong				:2;
		kulong	pd0			:1;
		kulong	pd1			:1;
		kulong	pd2			:1;
		kulong	pd3			:1;
		kulong	pd4			:1;
		kulong	pd5			:1;
		kulong	pd6			:1;
		kulong				:17;
	/* DDRFE (1D02_211Ch) */
		kulong	pe0			:1;
		kulong	pe1			:1;
		kulong	pe2			:1;
		kulong	pe3			:1;
		kulong	pe4			:1;
		kulong	pe5			:1;
		kulong				:2;
		kulong	pf0			:1;
		kulong	pf1			:1;
		kulong	pf2			:1;
		kulong	pf3			:1;
		kulong	pf4			:1;
		kulong				:19;
	/* DDRHG (1D02_2120h) */
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
	/* DDRJW (1D02_2124h) */
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
	/* DDRLK (1D02_2128h) */
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
	/* DDRNM (1D02_212Ch) */
		kulong	pm0			:1;
		kulong	pm1			:1;
		kulong	pm2			:1;
		kulong	pm3			:1;
		kulong	pm4			:1;
		kulong				:3;
		kulong	pn0			:1;
		kulong	pn1			:1;
		kulong	pn2			:1;
		kulong	pn3			:1;
		kulong	pn4			:1;
		kulong				:19;
	/* DDRPY (1D02_2130h) */
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

/*	structure of EPCR	(0x1D02_220C) */
union _IoChiptopEpcr {
	kulong		word[10];
	struct {
	/* EPCR76 (1D02_220Ch) */
		kulong	p60			:1;
		kulong	p61			:1;
		kulong	p62			:1;
		kulong	p63			:1;
		kulong				:28;
	/* EPCR98 (1D02_2210h) */
		kulong	p80			:1;
		kulong	p81			:1;
		kulong	p82			:1;
		kulong	p83			:1;
		kulong	p84			:1;
		kulong	p85			:1;
		kulong	p86			:1;
		kulong	p87			:1;
		kulong	p90			:1;
		kulong				:1;
		kulong	p92			:1;
		kulong				:21;
	/* EPCRBA (1D02_2214h) */
		kulong	pa0			:1;
		kulong	pa1			:1;
		kulong				:1;
		kulong	pa3			:1;
		kulong	pa4			:1;
		kulong	pa5			:1;
		kulong				:1;
		kulong	pa7			:1;
		kulong	pb0			:1;
		kulong	pb1			:1;
		kulong	pb2			:1;
		kulong	pb3			:1;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
		kulong	pb4			:1;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE

#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
		kulong	trgen		:1;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE

// --- REMOVE_ES_COMPILE_OPT END ---
		kulong				:19;
	/* EPCRDC (1D02_2218h) */
		kulong	pc0			:1;
		kulong	pc1			:1;
		kulong	pc2			:1;
		kulong	pc3			:1;
		kulong	pc4			:1;
		kulong	pc5			:1;
		kulong				:2;
		kulong	pd0			:1;
		kulong	pd1			:1;
		kulong	pd2			:1;
		kulong	pd3			:1;
		kulong	pd4			:1;
		kulong	pd5			:1;
		kulong	pd6			:1;
		kulong				:17;
	/* EPCRFE (1D02_221Ch) */
		kulong				:1;
		kulong	pe1			:1;
		kulong				:1;
		kulong	pe3			:1;
		kulong				:1;
		kulong	pe5			:1;
		kulong				:6;
		kulong	pf4			:1;
		kulong				:19;
	/* EPCRHG (1D02_2220h) */
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
	/* EPCRJW (1D02_2224h) */
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
	/* EPCRLK (1D02_2228h) */
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
	/* EPCRNM (1D02_222Ch) */
		kulong				:1;
		kulong	pm1			:1;
		kulong				:1;
		kulong	pm3			:1;
		kulong	pm4			:1;
		kulong				:4;
		kulong	pn1			:1;
		kulong				:1;
		kulong	pn3			:1;
		kulong	pn4			:1;
		kulong				:19;
	/* EPCRPY (1D02_2230h) */
		kulong	py0			:1;
		kulong	py1			:1;
		kulong				:2;
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

struct _KChiptop2 {
	KObject parent;
};


KConstType 	k_chiptop2_get_type(void);
KChiptop2*		k_chiptop2_new(void);


#endif /* __K_CHIPTOP2_H__ */
