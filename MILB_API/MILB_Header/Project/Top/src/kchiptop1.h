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


#ifndef __K_CHIPTOP1_H__
#define __K_CHIPTOP1_H__


#include <klib.h>


#define K_TYPE_CHIPTOP1			(k_chiptop1_get_type())
#define K_CHIPTOP1(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, KChiptop1))
#define K_IS_CHIPTOP1(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, K_TYPE_CHIPTOP1))


typedef union 				_IoChiptopClksel1 IoChiptopClksel1;
typedef union 				_IoChiptopClksel2 IoChiptopClksel2;
typedef union 				_IoChiptopClksel3 IoChiptopClksel3;
typedef union 				_IoChiptopClksel4 IoChiptopClksel4;
typedef union 				_IoChiptopClksel5 IoChiptopClksel5;
typedef union 				_IoChiptopClksel6 IoChiptopClksel6;
typedef union 				_IoChiptopClksel7 IoChiptopClksel7;
typedef union 				_IoChiptopClksel8 IoChiptopClksel8;
typedef union 				_IoChiptopClksel9 IoChiptopClksel9;
typedef union 				_IoChiptopClksel10 IoChiptopClksel10;
typedef union 				_IoChiptopClksel11 IoChiptopClksel11;
typedef union 				_IoChiptopClksel12 IoChiptopClksel12;
typedef union 				_IoChiptopPllcnt1 IoChiptopPllcnt1;
typedef union 				_IoChiptopPllcnt2 IoChiptopPllcnt2;
typedef union 				_IoChiptopPllcnt3 IoChiptopPllcnt3;
typedef union 				_IoChiptopPllcnt4 IoChiptopPllcnt4;
typedef union 				_IoChiptopPllcnt5 IoChiptopPllcnt5;
typedef union 				_IoChiptopPllcnt6 IoChiptopPllcnt6;
typedef union 				_IoChiptopPllcnt7 IoChiptopPllcnt7;
typedef union 				_IoChiptopPllcnt8 IoChiptopPllcnt8;
typedef union 				_IoChiptopPllcnt9 IoChiptopPllcnt9;
typedef union 				_IoChiptopClkstop1 IoChiptopClkstop1;
typedef union 				_IoChiptopClkstop2 IoChiptopClkstop2;
typedef union 				_IoChiptopClkstop3 IoChiptopClkstop3;
typedef union				_IoChiptopClkstop4 IoChiptopClkstop4;
typedef union 				_IoChiptopClkstop5 IoChiptopClkstop5;
typedef union	 			_IoChiptopClkstop6 IoChiptopClkstop6;
typedef union 				_IoChiptopClkstop7 IoChiptopClkstop7;
typedef union 				_IoChiptopClkstop8 IoChiptopClkstop8;
typedef union 				_IoChiptopClkstop9 IoChiptopClkstop9;
typedef union 				_IoChiptopClkstop10 IoChiptopClkstop10;
typedef union 				_IoChiptopClkstop11 IoChiptopClkstop11;
typedef union 				_IoChiptopClkstop12 IoChiptopClkstop12;
typedef union 				_IoChiptopClkstop13 IoChiptopClkstop13;
typedef union 				_IoChiptopClkstop14 IoChiptopClkstop14;
typedef struct 				_KChiptop1 KChiptop1;
typedef struct 				_KChiptop1Private KChiptop1Private;

/*	structure of CLKSEL1  (1D02_1000h)    */
union _IoChiptopClksel1 {
	kulong		word;
	struct {
		kulong	rclk		:3;
		kulong	uhs1clk0	:5;
		kulong	uhs1clk1	:5;
		kulong	uhs1clk2	:5;
		kulong	uhs2clk		:4;
		kulong	nfclk		:6;
		kulong	emmcclk		:3;
		kulong				:1;
	} bit;
};

/*	structure of CLKSEL2  (1D02_1004h)    */
union _IoChiptopClksel2 {
	kulong		word;
	struct {
		kulong	elaclk		:4;
		kulong	jpgclk		:4;
		kulong	gpuclk		:4;
		kulong	iputmeclk	:4;
		kulong	ipuclk		:4;
		kulong	mifclk		:4;
		kulong	hifclk		:4;
		kulong	rawclk		:3;
		kulong				:1;
	} bit;
};

/*	structure of CLKSEL3  (1D02_1008h)    */
union _IoChiptopClksel3 {
	kulong		word;
	struct {
		kulong	vdfclk		:4;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
		kulong	pxfclk		:4;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE

#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
		kulong	hevencclk	:4;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE

// --- REMOVE_ES_COMPILE_OPT END ---
		kulong	ippclk		:5;
		kulong	pasclk		:4;
		kulong	iipclk		:4;
		kulong	senmskclk	:2;
		kulong	senclk		:4;
		kulong	pipesel		:2;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
		kulong				:3;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE

#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
		kulong	hevencsel	:2;
		kulong				:1;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	} bit;
};

/*	structure of CLKSEL4  (1D02_100Ch)    */
union _IoChiptopClksel4 {
	kulong		word;
	struct {
		kulong	cnr1clk		:7;
		kulong	b2r1clk		:7;
		kulong	ltm1clk		:7;
		kulong	r2y1clk		:7;
		kulong	sro1clk2	:4;
	} bit;
};

/*	structure of CLKSEL5  (1D02_1010h)    */
union _IoChiptopClksel5 {
	kulong		word;
	struct {
		kulong	ltmrbk1clk	:6;
		kulong	b2b1clk		:6;
		kulong	sro1clk		:5;
		kulong				:15;
	} bit;
};

/*	structure of CLKSEL6	(1D02_1014h)	*/
union _IoChiptopClksel6 {
	kulong word;
	struct {
		kulong	cnr2clk		:7;
		kulong	b2r2clk		:7;
		kulong	ltm2clk		:7;
		kulong	r2y2clk		:7;
		kulong	sro2clk2	:4;
	} bit;
};

/*	structure of CLKSEL7	(1D02_1018h)	*/
union _IoChiptopClksel7 {
	kulong word;
	struct {
		kulong	ltmrbk2clk	:6;
		kulong	b2b2clk		:6;
		kulong	sro2clk		:5;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
		kulong				:15;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE

#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
		kulong	mipisel		:2;
		kulong	pdm0sel		:3;
		kulong	pdm1sel		:3;
		kulong				:7;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	} bit;
};

/*	structure of CLKSEL8  (1D02_101Ch)    */
union _IoChiptopClksel8 {
	kulong		word;
	struct {
		kulong	dspclk		:3;
		kulong	spiclk		:3;
		kulong	auclk		:3;
		kulong	au0sel		:2;
		kulong	au2sel		:2;
		kulong	au3sel		:2;
		kulong	netausel	:2;
		kulong	apclk		:6;
		kulong	ap0sel		:2;
		kulong	ap1sel		:2;
		kulong	ap2sel		:2;
		kulong	ap3sel		:2;
		kulong				:1;
	} bit;
};

/*	structure of CLKSEL9  (1D02_1020h)    */
union _IoChiptopClksel9 {
	kulong		word;
	struct {
		kulong	pclk		:7;
		kulong	hclk		:5;
		kulong	hclkbmh		:4;
		kulong	aclkexs		:4;
		kulong	aclk		:4;
		kulong				:8;
	} bit;
};

/*	structure of CLKSEL10  (1D02_1024h)    */
union _IoChiptopClksel10 {
	kulong		word;
	struct {
		kulong	aclk400		:3;
		kulong	mclk200		:4;
		kulong	mclk400		:3;
		kulong				:22;
	} bit;
};

/*	structure of CLKSEL11  (1D02_1028h)    */
union _IoChiptopClksel11 {
	kulong		word;
	struct {
		kulong	dchreq		:1;
		kulong				:31;
	} bit;
};

/*	structure of CLKSEL12  (1D02_102Ch)    */
union _IoChiptopClksel12 {
	kulong		word;
	struct {
		kulong	aclk300		:2;
		kulong	gyroclk		:3;
		kulong				:3;
		kulong	fpt0clk		:4;
		kulong	fpt1clk		:4;
		kulong	meclk		:3;
		kulong	nfbchclk	:2;
		kulong	ribclk		:5;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
		kulong	shdrclk		:4;
		kulong				:2;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE

#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
		kulong	shdrclk		:5;
		kulong				:1;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	} bit;
};

/*	structure of PLLCNT1	(1D02_1030h)	*/
union _IoChiptopPllcnt1 {
	kulong word;
	struct {
		kulong	pl00st		:1;
		kulong	pl01st		:1;
		kulong	pl02st		:1;
		kulong	pl03st		:1;
		kulong	pl04st		:1;
		kulong	pl05st		:1;
		kulong	pl05ast		:1;
		kulong	pl06st		:1;
		kulong	pl07st		:1;
		kulong	pl08st		:1;
		kulong	pl10st		:1;
		kulong	pl10ast		:1;
		kulong	pl11st		:1;
		kulong	dpl00st		:1;
		kulong	dpl01st		:1;
		kulong	dpl02st		:1;
		kulong	dpl10st		:1;
		kulong	dpl11st		:1;
		kulong	dpl12st		:1;
		kulong				:13;
	} bit;
};

/*	structure of PLLCNT2	(1D02_1034h)	*/
union _IoChiptopPllcnt2 {
	kulong word;
	struct {
		kulong	pl00sel		:1;
		kulong	pl01sel		:1;
		kulong	pl02sel		:1;
		kulong	pl03sel		:1;
		kulong	pl04sel		:1;
		kulong	pl05sel		:1;
		kulong	pl05asel	:1;
		kulong	pl06sel		:1;
		kulong	pl07sel		:1;
		kulong	pl08sel		:1;
		kulong	pl10sel		:1;
		kulong	pl10asel	:1;
		kulong	pl11sel		:1;
		kulong				:3;
		kulong	pl01ssen	:1;
		kulong	pl02ssen	:1;
		kulong				:14;
	} bit;
};

/*	structure of PLLCNT3	(1D02_1038h)	*/
union _IoChiptopPllcnt3 {
	kulong word;
	struct {
		kulong	p00postdiv	:8;
		kulong	p00prediv	:2;
		kulong				:6;
		kulong	p00plldiv	:8;
		kulong				:8;
	} bit;
};

/*	structure of PLLCNT4	(1D02_103Ch)	*/
union _IoChiptopPllcnt4 {
	kulong word;
	struct {
		kulong	p00fnum		:32;
	} bit;
};

/*	structure of PLLCNT5	(1D02_1040h)	*/
union _IoChiptopPllcnt5 {
	kulong word;
	struct {
		kulong	p00fden		:32;
	} bit;
};

/*	structure of PLLCNT6	(1D02_1044h)	*/
union _IoChiptopPllcnt6 {
	kulong word;
	struct {
		kulong	p01rate		:10;
		kulong	p01freq		:2;
		kulong	p01mode		:1;
		kulong				:3;
		kulong	p02rate		:10;
		kulong	p02freq		:2;
		kulong	p02mode		:1;
		kulong				:3;
	} bit;
};

/*	structure of PLLCNT7	(1D02_1048h)	*/
union _IoChiptopPllcnt7 {
	kulong word;
	struct {
		kulong	p03postdiv0	:4;
		kulong	p03postdiv1	:4;
		kulong	p03prediv	:3;
		kulong				:5;
		kulong	p03plldiv	:8;
		kulong	p03oc0		:1;
		kulong	p03oc1		:1;
		kulong	d0xoc		:1;
		kulong	d1xoc		:1;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
		kulong	dplx8		:1;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE

#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
		kulong				:1;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE

// --- REMOVE_ES_COMPILE_OPT END ---
		kulong	dsel		:1;
		kulong				:2;
	} bit;
};

/*	structure of PLLCNT8	(1D02_104Ch)	*/
union _IoChiptopPllcnt8 {
	kulong word;
	struct {
		kulong	p04postdiv	:8;
		kulong	p04prediv	:3;
		kulong				:5;
		kulong	p04plldiv	:8;
		kulong				:8;
	} bit;
};

/*	structure of PLLCNT9	(1D02_1050h)	*/
union _IoChiptopPllcnt9 {
	kulong word;
	struct {
		kulong	p10aplldiv	:2;
		kulong				:6;
		kulong	p08plldiv	:7;
		kulong				:1;
		kulong	p05chg		:1;
		kulong				:15;
	} bit;
};


/*	structure of CLKSTOP1	(1D02_1054h)	*/
union _IoChiptopClkstop1 {
	kulong		word;
	struct {
		kulong	dspck		:2;
		kulong	dspax		:2;
		kulong	senck		:2;
		kulong	senax		:2;
		kulong	senah		:2;
		kulong	senap		:2;
		kulong	gpioap		:2;
		kulong	au0ck		:2;
		kulong	au2ck		:2;
		kulong	au3ck		:2;
		kulong	au4ck		:2;
		kulong	au5ck		:2;
		kulong	netauck		:2;
		kulong				:2;
		kulong	tempck		:2;
		kulong				:2;
	}bit;
};

/*	structure of CLKSTOP2	(1D02_1058h)	*/
union _IoChiptopClkstop2 {
	kulong		word;
	struct {
		kulong	rck			:2;
		kulong	uhs1ck0		:2;
		kulong	uhs1ck1		:2;
		kulong	uhs1ck2		:2;
		kulong	uhs2ck		:2;
		kulong	nfck		:2;
		kulong	emmcck		:2;
		kulong	netsecck	:2;
		kulong	netrck		:2;
		kulong	exsax		:2;
		kulong	spick		:2;
		kulong	slimb00ck	:2;
		kulong	slimb01ck	:2;
		kulong	slimb10ck	:2;
		kulong	slimb11ck	:2;
		kulong	pcisuppck	:2;
	}bit;
};

/*	structure of CLKSTOP3	(1D02_105Ch)	*/
union _IoChiptopClkstop3 {
	kulong		word;
	struct {
		kulong	iipck		:2;
		kulong	iipap		:2;
		kulong	iipah		:2;
		kulong	iipax		:2;
		kulong	lcdck		:2;
		kulong	hifck		:2;
		kulong	mifck		:2;
		kulong	dispap		:2;
		kulong	dispah		:2;
		kulong	dispax		:2;
		kulong	jpgck		:2;
		kulong	jpgax		:2;
		kulong	jpgah		:2;
		kulong	jpgap		:2;
		kulong	pdm0ck		:2;
		kulong	pdm1ck		:2;
	}bit;
};

/*	structure of CLKSTOP4	(1D02_1060h)	*/
union _IoChiptopClkstop4 {
	kulong		word;
	struct {
		kulong	gpuck		:2;
		kulong	gpuap		:2;
		kulong	gpuah		:2;
		kulong	gpuax		:2;
		kulong	fpt0ck		:2;
		kulong	fpt0ax		:2;
		kulong	fpt0ah		:2;
		kulong	fpt0ap		:2;
		kulong	fpt1ck		:2;
		kulong	fpt1ap		:2;
		kulong	fpt1ah		:2;
		kulong	fpt1ax		:2;
		kulong	apck0		:2;
		kulong	apck1		:2;
		kulong	apck2		:2;
		kulong	apck3		:2;
	}bit;
};

/*	structure of CLKSTOP5	(1D02_1064h)	*/
union _IoChiptopClkstop5 {
	kulong		word;
	struct {
		kulong	micax0		:2;
		kulong	micax1		:2;
		kulong	micax2		:2;
		kulong	micax3		:2;
		kulong	micax4		:2;
		kulong	micax5		:2;
		kulong	micax6		:2;
		kulong	micap0		:2;
		kulong	micap1		:2;
		kulong	micap2		:2;
		kulong	micap3		:2;
		kulong	micap4		:2;
		kulong	micap5		:2;
		kulong	micap6		:2;
		kulong				:4;
	}bit;
};

/*	structure of CLKSTOP6	(1D02_1068h)	*/
union _IoChiptopClkstop6 {
	kulong		word;
	struct {
		kulong	micah1		:2;
		kulong	micah2		:2;
		kulong	micah3		:2;
		kulong	imgax		:2;
		kulong	imgah0		:2;
		kulong	imgah1		:2;
		kulong	imgah3		:2;
		kulong	imgap3		:2;
		kulong	regap		:2;
		kulong	xchax		:2;
		kulong	xchap		:2;
		kulong	elack		:2;
		kulong	elaax		:2;
		kulong	elaap		:2;
		kulong				:4;
	}bit;
};

/*	structure of CLKSTOP7	(1D02_106Ch)	*/
union _IoChiptopClkstop7 {
	kulong		word;
	struct {
		kulong	ipufdck		:2;
		kulong	ipuvisck	:2;
		kulong	ipuax		:2;
		kulong	ipuah		:2;
		kulong	rawck		:2;
		kulong	rawax		:2;
		kulong	rawap		:2;
		kulong	shdrck		:2;
		kulong	shdrax		:2;
		kulong	shdrah		:2;
		kulong	shdrap		:2;
		kulong	m0ck		:2;
		kulong	meck		:2;
		kulong	meax		:2;
		kulong	meap		:2;
		kulong				:2;
	}bit;
};

/*	structure of CLKSTOP8	(1D02_1070h)	*/
union _IoChiptopClkstop8 {
	kulong		word;
	struct {
		kulong	ribck		:2;
		kulong	ribah		:2;
		kulong	hevdfck		:2;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
		kulong	hepxfck		:2;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE

#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
		kulong	hevencck	:2;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE

// --- REMOVE_ES_COMPILE_OPT END ---
		kulong	heippck		:2;
		kulong	umc0hevcmx2	:2;
		kulong	umc0hevcmx4	:2;
		kulong	umc0rbrmx4	:2;
		kulong	umc1hevcmx2	:2;
		kulong	umc1hevcmx4	:2;
		kulong	umc1rbrmx4	:2;
		kulong	umc0cmnax	:2;
		kulong	umc0mx1ax	:2;
		kulong	umc0mx2ax	:2;
		kulong	umc0mx3ax	:2;
		kulong	umc0mx4ax	:2;
	}bit;
};

/*	structure of CLKSTOP9	(1D02_1074h)	*/
union _IoChiptopClkstop9 {
	kulong		word;
	struct {
		kulong	umc0mx5ax	:2;
		kulong	umc1cmnax	:2;
		kulong	umc1mx1ax	:2;
		kulong	umc1mx2ax	:2;
		kulong	umc1mx3ax	:2;
		kulong	umc1mx4ax	:2;
		kulong	umc1mx5ax	:2;
		kulong	umc0mx0ax3	:2;
		kulong	umc0mx6ax4	:2;
		kulong	umc0hevcax4	:2;
		kulong	umc1mx0ax3	:2;
		kulong	umc1mx6ax4	:2;
		kulong	umc1hevcax4	:2;
		kulong	umc0ap		:2;
		kulong	umc1ap		:2;
		kulong				:2;
	}bit;
};

/*	structure of CLKSTOP10	(1D02_1078h)	*/
union _IoChiptopClkstop10 {
	kulong		word;
	struct {
		kulong	sro1ck		:2;
		kulong	sro1ck2	:2;
		kulong	sro1ax		:2;
		kulong	sro1ah		:2;
		kulong	sro1ap		:2;
		kulong	b2b1ck		:2;
		kulong	b2b1ax		:2;
		kulong	b2b1ah		:2;
		kulong	b2b1ap		:2;
		kulong	ltmrbk1ck	:2;
		kulong	b2r1ck		:2;
		kulong	b2r1ax		:2;
		kulong	b2r1ah		:2;
		kulong	b2r1ap		:2;
		kulong				:4;
	}bit;
};

/*	structure of CLKSTOP11	(1D02_107Ch)	*/
union _IoChiptopClkstop11 {
	kulong		word;
	struct {
		kulong	ltm1ck		:2;
		kulong	ltm1ax		:2;
		kulong	ltm1ah		:2;
		kulong	ltm1ap		:2;
		kulong	r2y1ck		:2;
		kulong	r2y1ax		:2;
		kulong	r2y1ah		:2;
		kulong	r2y1ap		:2;
		kulong	cnr1ck		:2;
		kulong	cnr1ax		:2;
		kulong	cnr1ap		:2;
		kulong	apah		:2;
		kulong	dbgap		:2;
		kulong	nfbchck		:2;
		kulong				:4;
	}bit;
};

/*	structure of CLKSTOP12	(1D02_1080h)	*/
union _IoChiptopClkstop12 {
	kulong		word;
	struct {
		kulong	sro2ck		:2;
		kulong	sro2ck2	:2;
		kulong	sro2ax		:2;
		kulong	sro2ah		:2;
		kulong	sro2ap		:2;
		kulong	b2b2ck		:2;
		kulong	b2b2ax		:2;
		kulong	b2b2ah		:2;
		kulong	b2b2ap		:2;
		kulong	ltmrbk2ck	:2;
		kulong	b2r2ck		:2;
		kulong	b2r2ax		:2;
		kulong	b2r2ah		:2;
		kulong	b2r2ap		:2;
		kulong				:4;
	}bit;
};

/*	structure of CLKSTOP13	(1D02_1084h)	*/
union _IoChiptopClkstop13 {
	kulong		word;
	struct {
		kulong	ltm2ck		:2;
		kulong	ltm2ax		:2;
		kulong	ltm2ah		:2;
		kulong	ltm2ap		:2;
		kulong	r2y2ck		:2;
		kulong	r2y2ax		:2;
		kulong	r2y2ah		:2;
		kulong	r2y2ap		:2;
		kulong	cnr2ck		:2;
		kulong	cnr2ax		:2;
		kulong	cnr2ap		:2;
		kulong	umcvdfmx4	:2;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
		kulong	umcpxfmx4	:2;
		kulong	umcvdfmx2	:2;
		kulong	umcpxfmx2	:2;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE

#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
		kulong	umchevencax4:2;
		kulong	umcvdfmx2	:2;
		kulong	hevencap	:2;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE

// --- REMOVE_ES_COMPILE_OPT END ---
		kulong	bmh1ck		:2;
	}bit;
};

/*	structure of CLKSTOP14	(1D02_1088h)	*/
union _IoChiptopClkstop14 {
	kulong		word;
	struct {
		kulong	statax		:2;
		kulong	statah		:2;
		kulong	statap		:2;
		kulong	periah		:2;
		kulong	periap		:2;
		kulong	senmskck	:2;
		kulong	gyrock		:2;
		kulong	exsah		:2;
		kulong	exsap		:2;
		kulong	pasck		:2;
		kulong	bmh0ck		:2;
		kulong	bmh0ax		:2;
		kulong				:2;
		kulong	rdmaax		:2;
		kulong	rdmaap		:2;
		kulong	bmh1ax		:2;
	}bit;
};

struct _KChiptop1 {
	KObject parent;
};


KConstType 	k_chiptop1_get_type(void);
KChiptop1*		k_chiptop1_new(void);


#endif /* __K_CHIPTOP1_H__ */
