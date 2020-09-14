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


//#include <klib.h>
#include <stdio.h>
#include <glib-object.h>


//#define K_TYPE_CHIPTOP1			(k_chiptop1_get_type())
//#define K_CHIPTOP1(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, KChiptop1))
//#define K_IS_CHIPTOP1(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, K_TYPE_CHIPTOP1))


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
//typedef struct 				_KChiptop1 KChiptop1;
//typedef struct 				_KChiptop1Private KChiptop1Private;

/*	structure of CLKSEL1  (1D02_1000h)    */
union _IoChiptopClksel1 {
	gulong		word;
	struct {
		gulong	rclk		:3;
		gulong	uhs1clk0	:5;
		gulong	uhs1clk1	:5;
		gulong	uhs1clk2	:5;
		gulong	uhs2clk		:4;
		gulong	nfclk		:6;
		gulong	emmcclk		:3;
		gulong				:1;
	} bit;
};

/*	structure of CLKSEL2  (1D02_1004h)    */
union _IoChiptopClksel2 {
	gulong		word;
	struct {
		gulong	elaclk		:4;
		gulong	jpgclk		:4;
		gulong	gpuclk		:4;
		gulong	iputmeclk	:4;
		gulong	ipuclk		:4;
		gulong	mifclk		:4;
		gulong	hifclk		:4;
		gulong	rawclk		:3;
		gulong				:1;
	} bit;
};

/*	structure of CLKSEL3  (1D02_1008h)    */
union _IoChiptopClksel3 {
	gulong		word;
	struct {
		gulong	vdfclk		:4;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
		gulong	pxfclk		:4;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE

#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
		gulong	hevencclk	:4;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE

// --- REMOVE_ES_COMPILE_OPT END ---
		gulong	ippclk		:5;
		gulong	pasclk		:4;
		gulong	iipclk		:4;
		gulong	senmskclk	:2;
		gulong	senclk		:4;
		gulong	pipesel		:2;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
		gulong				:3;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE

#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
		gulong	hevencsel	:2;
		gulong				:1;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	} bit;
};

/*	structure of CLKSEL4  (1D02_100Ch)    */
union _IoChiptopClksel4 {
	gulong		word;
	struct {
		gulong	cnr1clk		:7;
		gulong	b2r1clk		:7;
		gulong	ltm1clk		:7;
		gulong	r2y1clk		:7;
		gulong	sro1clk2	:4;
	} bit;
};

/*	structure of CLKSEL5  (1D02_1010h)    */
union _IoChiptopClksel5 {
	gulong		word;
	struct {
		gulong	ltmrbk1clk	:6;
		gulong	b2b1clk		:6;
		gulong	sro1clk		:5;
		gulong				:15;
	} bit;
};

/*	structure of CLKSEL6	(1D02_1014h)	*/
union _IoChiptopClksel6 {
	gulong word;
	struct {
		gulong	cnr2clk		:7;
		gulong	b2r2clk		:7;
		gulong	ltm2clk		:7;
		gulong	r2y2clk		:7;
		gulong	sro2clk2	:4;
	} bit;
};

/*	structure of CLKSEL7	(1D02_1018h)	*/
union _IoChiptopClksel7 {
	gulong word;
	struct {
		gulong	ltmrbk2clk	:6;
		gulong	b2b2clk		:6;
		gulong	sro2clk		:5;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
		gulong				:15;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE

#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
		gulong	mipisel		:2;
		gulong	pdm0sel		:3;
		gulong	pdm1sel		:3;
		gulong				:7;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	} bit;
};

/*	structure of CLKSEL8  (1D02_101Ch)    */
union _IoChiptopClksel8 {
	gulong		word;
	struct {
		gulong	dspclk		:3;
		gulong	spiclk		:3;
		gulong	auclk		:3;
		gulong	au0sel		:2;
		gulong	au2sel		:2;
		gulong	au3sel		:2;
		gulong	netausel	:2;
		gulong	apclk		:6;
		gulong	ap0sel		:2;
		gulong	ap1sel		:2;
		gulong	ap2sel		:2;
		gulong	ap3sel		:2;
		gulong				:1;
	} bit;
};

/*	structure of CLKSEL9  (1D02_1020h)    */
union _IoChiptopClksel9 {
	gulong		word;
	struct {
		gulong	pclk		:7;
		gulong	hclk		:5;
		gulong	hclkbmh		:4;
		gulong	aclkexs		:4;
		gulong	aclk		:4;
		gulong				:8;
	} bit;
};

/*	structure of CLKSEL10  (1D02_1024h)    */
union _IoChiptopClksel10 {
	gulong		word;
	struct {
		gulong	aclk400		:3;
		gulong	mclk200		:4;
		gulong	mclk400		:3;
		gulong				:22;
	} bit;
};

/*	structure of CLKSEL11  (1D02_1028h)    */
union _IoChiptopClksel11 {
	gulong		word;
	struct {
		gulong	dchreq		:1;
		gulong				:31;
	} bit;
};

/*	structure of CLKSEL12  (1D02_102Ch)    */
union _IoChiptopClksel12 {
	gulong		word;
	struct {
		gulong	aclk300		:2;
		gulong	gyroclk		:3;
		gulong				:3;
		gulong	fpt0clk		:4;
		gulong	fpt1clk		:4;
		gulong	meclk		:3;
		gulong	nfbchclk	:2;
		gulong	ribclk		:5;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
		gulong	shdrclk		:4;
		gulong				:2;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE

#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
		gulong	shdrclk		:5;
		gulong				:1;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	} bit;
};

/*	structure of PLLCNT1	(1D02_1030h)	*/
union _IoChiptopPllcnt1 {
	gulong word;
	struct {
		gulong	pl00st		:1;
		gulong	pl01st		:1;
		gulong	pl02st		:1;
		gulong	pl03st		:1;
		gulong	pl04st		:1;
		gulong	pl05st		:1;
		gulong	pl05ast		:1;
		gulong	pl06st		:1;
		gulong	pl07st		:1;
		gulong	pl08st		:1;
		gulong	pl10st		:1;
		gulong	pl10ast		:1;
		gulong	pl11st		:1;
		gulong	dpl00st		:1;
		gulong	dpl01st		:1;
		gulong	dpl02st		:1;
		gulong	dpl10st		:1;
		gulong	dpl11st		:1;
		gulong	dpl12st		:1;
		gulong				:13;
	} bit;
};

/*	structure of PLLCNT2	(1D02_1034h)	*/
union _IoChiptopPllcnt2 {
	gulong word;
	struct {
		gulong	pl00sel		:1;
		gulong	pl01sel		:1;
		gulong	pl02sel		:1;
		gulong	pl03sel		:1;
		gulong	pl04sel		:1;
		gulong	pl05sel		:1;
		gulong	pl05asel	:1;
		gulong	pl06sel		:1;
		gulong	pl07sel		:1;
		gulong	pl08sel		:1;
		gulong	pl10sel		:1;
		gulong	pl10asel	:1;
		gulong	pl11sel		:1;
		gulong				:3;
		gulong	pl01ssen	:1;
		gulong	pl02ssen	:1;
		gulong				:14;
	} bit;
};

/*	structure of PLLCNT3	(1D02_1038h)	*/
union _IoChiptopPllcnt3 {
	gulong word;
	struct {
		gulong	p00postdiv	:8;
		gulong	p00prediv	:2;
		gulong				:6;
		gulong	p00plldiv	:8;
		gulong				:8;
	} bit;
};

/*	structure of PLLCNT4	(1D02_103Ch)	*/
union _IoChiptopPllcnt4 {
	gulong word;
	struct {
		gulong	p00fnum		:32;
	} bit;
};

/*	structure of PLLCNT5	(1D02_1040h)	*/
union _IoChiptopPllcnt5 {
	gulong word;
	struct {
		gulong	p00fden		:32;
	} bit;
};

/*	structure of PLLCNT6	(1D02_1044h)	*/
union _IoChiptopPllcnt6 {
	gulong word;
	struct {
		gulong	p01rate		:10;
		gulong	p01freq		:2;
		gulong	p01mode		:1;
		gulong				:3;
		gulong	p02rate		:10;
		gulong	p02freq		:2;
		gulong	p02mode		:1;
		gulong				:3;
	} bit;
};

/*	structure of PLLCNT7	(1D02_1048h)	*/
union _IoChiptopPllcnt7 {
	gulong word;
	struct {
		gulong	p03postdiv0	:4;
		gulong	p03postdiv1	:4;
		gulong	p03prediv	:3;
		gulong				:5;
		gulong	p03plldiv	:8;
		gulong	p03oc0		:1;
		gulong	p03oc1		:1;
		gulong	d0xoc		:1;
		gulong	d1xoc		:1;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
		gulong	dplx8		:1;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE

#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
		gulong				:1;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE

// --- REMOVE_ES_COMPILE_OPT END ---
		gulong	dsel		:1;
		gulong				:2;
	} bit;
};

/*	structure of PLLCNT8	(1D02_104Ch)	*/
union _IoChiptopPllcnt8 {
	gulong word;
	struct {
		gulong	p04postdiv	:8;
		gulong	p04prediv	:3;
		gulong				:5;
		gulong	p04plldiv	:8;
		gulong				:8;
	} bit;
};

/*	structure of PLLCNT9	(1D02_1050h)	*/
union _IoChiptopPllcnt9 {
	gulong word;
	struct {
		gulong	p10aplldiv	:2;
		gulong				:6;
		gulong	p08plldiv	:7;
		gulong				:1;
		gulong	p05chg		:1;
		gulong				:15;
	} bit;
};


/*	structure of CLKSTOP1	(1D02_1054h)	*/
union _IoChiptopClkstop1 {
	gulong		word;
	struct {
		gulong	dspck		:2;
		gulong	dspax		:2;
		gulong	senck		:2;
		gulong	senax		:2;
		gulong	senah		:2;
		gulong	senap		:2;
		gulong	gpioap		:2;
		gulong	au0ck		:2;
		gulong	au2ck		:2;
		gulong	au3ck		:2;
		gulong	au4ck		:2;
		gulong	au5ck		:2;
		gulong	netauck		:2;
		gulong				:2;
		gulong	tempck		:2;
		gulong				:2;
	}bit;
};

/*	structure of CLKSTOP2	(1D02_1058h)	*/
union _IoChiptopClkstop2 {
	gulong		word;
	struct {
		gulong	rck			:2;
		gulong	uhs1ck0		:2;
		gulong	uhs1ck1		:2;
		gulong	uhs1ck2		:2;
		gulong	uhs2ck		:2;
		gulong	nfck		:2;
		gulong	emmcck		:2;
		gulong	netsecck	:2;
		gulong	netrck		:2;
		gulong	exsax		:2;
		gulong	spick		:2;
		gulong	slimb00ck	:2;
		gulong	slimb01ck	:2;
		gulong	slimb10ck	:2;
		gulong	slimb11ck	:2;
		gulong	pcisuppck	:2;
	}bit;
};

/*	structure of CLKSTOP3	(1D02_105Ch)	*/
union _IoChiptopClkstop3 {
	gulong		word;
	struct {
		gulong	iipck		:2;
		gulong	iipap		:2;
		gulong	iipah		:2;
		gulong	iipax		:2;
		gulong	lcdck		:2;
		gulong	hifck		:2;
		gulong	mifck		:2;
		gulong	dispap		:2;
		gulong	dispah		:2;
		gulong	dispax		:2;
		gulong	jpgck		:2;
		gulong	jpgax		:2;
		gulong	jpgah		:2;
		gulong	jpgap		:2;
		gulong	pdm0ck		:2;
		gulong	pdm1ck		:2;
	}bit;
};

/*	structure of CLKSTOP4	(1D02_1060h)	*/
union _IoChiptopClkstop4 {
	gulong		word;
	struct {
		gulong	gpuck		:2;
		gulong	gpuap		:2;
		gulong	gpuah		:2;
		gulong	gpuax		:2;
		gulong	fpt0ck		:2;
		gulong	fpt0ax		:2;
		gulong	fpt0ah		:2;
		gulong	fpt0ap		:2;
		gulong	fpt1ck		:2;
		gulong	fpt1ap		:2;
		gulong	fpt1ah		:2;
		gulong	fpt1ax		:2;
		gulong	apck0		:2;
		gulong	apck1		:2;
		gulong	apck2		:2;
		gulong	apck3		:2;
	}bit;
};

/*	structure of CLKSTOP5	(1D02_1064h)	*/
union _IoChiptopClkstop5 {
	gulong		word;
	struct {
		gulong	micax0		:2;
		gulong	micax1		:2;
		gulong	micax2		:2;
		gulong	micax3		:2;
		gulong	micax4		:2;
		gulong	micax5		:2;
		gulong	micax6		:2;
		gulong	micap0		:2;
		gulong	micap1		:2;
		gulong	micap2		:2;
		gulong	micap3		:2;
		gulong	micap4		:2;
		gulong	micap5		:2;
		gulong	micap6		:2;
		gulong				:4;
	}bit;
};

/*	structure of CLKSTOP6	(1D02_1068h)	*/
union _IoChiptopClkstop6 {
	gulong		word;
	struct {
		gulong	micah1		:2;
		gulong	micah2		:2;
		gulong	micah3		:2;
		gulong	imgax		:2;
		gulong	imgah0		:2;
		gulong	imgah1		:2;
		gulong	imgah3		:2;
		gulong	imgap3		:2;
		gulong	regap		:2;
		gulong	xchax		:2;
		gulong	xchap		:2;
		gulong	elack		:2;
		gulong	elaax		:2;
		gulong	elaap		:2;
		gulong				:4;
	}bit;
};

/*	structure of CLKSTOP7	(1D02_106Ch)	*/
union _IoChiptopClkstop7 {
	gulong		word;
	struct {
		gulong	ipufdck		:2;
		gulong	ipuvisck	:2;
		gulong	ipuax		:2;
		gulong	ipuah		:2;
		gulong	rawck		:2;
		gulong	rawax		:2;
		gulong	rawap		:2;
		gulong	shdrck		:2;
		gulong	shdrax		:2;
		gulong	shdrah		:2;
		gulong	shdrap		:2;
		gulong	m0ck		:2;
		gulong	meck		:2;
		gulong	meax		:2;
		gulong	meap		:2;
		gulong				:2;
	}bit;
};

/*	structure of CLKSTOP8	(1D02_1070h)	*/
union _IoChiptopClkstop8 {
	gulong		word;
	struct {
		gulong	ribck		:2;
		gulong	ribah		:2;
		gulong	hevdfck		:2;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
		gulong	hepxfck		:2;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE

#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
		gulong	hevencck	:2;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE

// --- REMOVE_ES_COMPILE_OPT END ---
		gulong	heippck		:2;
		gulong	umc0hevcmx2	:2;
		gulong	umc0hevcmx4	:2;
		gulong	umc0rbrmx4	:2;
		gulong	umc1hevcmx2	:2;
		gulong	umc1hevcmx4	:2;
		gulong	umc1rbrmx4	:2;
		gulong	umc0cmnax	:2;
		gulong	umc0mx1ax	:2;
		gulong	umc0mx2ax	:2;
		gulong	umc0mx3ax	:2;
		gulong	umc0mx4ax	:2;
	}bit;
};

/*	structure of CLKSTOP9	(1D02_1074h)	*/
union _IoChiptopClkstop9 {
	gulong		word;
	struct {
		gulong	umc0mx5ax	:2;
		gulong	umc1cmnax	:2;
		gulong	umc1mx1ax	:2;
		gulong	umc1mx2ax	:2;
		gulong	umc1mx3ax	:2;
		gulong	umc1mx4ax	:2;
		gulong	umc1mx5ax	:2;
		gulong	umc0mx0ax3	:2;
		gulong	umc0mx6ax4	:2;
		gulong	umc0hevcax4	:2;
		gulong	umc1mx0ax3	:2;
		gulong	umc1mx6ax4	:2;
		gulong	umc1hevcax4	:2;
		gulong	umc0ap		:2;
		gulong	umc1ap		:2;
		gulong				:2;
	}bit;
};

/*	structure of CLKSTOP10	(1D02_1078h)	*/
union _IoChiptopClkstop10 {
	gulong		word;
	struct {
		gulong	sro1ck		:2;
		gulong	sro1ck2	:2;
		gulong	sro1ax		:2;
		gulong	sro1ah		:2;
		gulong	sro1ap		:2;
		gulong	b2b1ck		:2;
		gulong	b2b1ax		:2;
		gulong	b2b1ah		:2;
		gulong	b2b1ap		:2;
		gulong	ltmrbk1ck	:2;
		gulong	b2r1ck		:2;
		gulong	b2r1ax		:2;
		gulong	b2r1ah		:2;
		gulong	b2r1ap		:2;
		gulong				:4;
	}bit;
};

/*	structure of CLKSTOP11	(1D02_107Ch)	*/
union _IoChiptopClkstop11 {
	gulong		word;
	struct {
		gulong	ltm1ck		:2;
		gulong	ltm1ax		:2;
		gulong	ltm1ah		:2;
		gulong	ltm1ap		:2;
		gulong	r2y1ck		:2;
		gulong	r2y1ax		:2;
		gulong	r2y1ah		:2;
		gulong	r2y1ap		:2;
		gulong	cnr1ck		:2;
		gulong	cnr1ax		:2;
		gulong	cnr1ap		:2;
		gulong	apah		:2;
		gulong	dbgap		:2;
		gulong	nfbchck		:2;
		gulong				:4;
	}bit;
};

/*	structure of CLKSTOP12	(1D02_1080h)	*/
union _IoChiptopClkstop12 {
	gulong		word;
	struct {
		gulong	sro2ck		:2;
		gulong	sro2ck2	:2;
		gulong	sro2ax		:2;
		gulong	sro2ah		:2;
		gulong	sro2ap		:2;
		gulong	b2b2ck		:2;
		gulong	b2b2ax		:2;
		gulong	b2b2ah		:2;
		gulong	b2b2ap		:2;
		gulong	ltmrbk2ck	:2;
		gulong	b2r2ck		:2;
		gulong	b2r2ax		:2;
		gulong	b2r2ah		:2;
		gulong	b2r2ap		:2;
		gulong				:4;
	}bit;
};

/*	structure of CLKSTOP13	(1D02_1084h)	*/
union _IoChiptopClkstop13 {
	gulong		word;
	struct {
		gulong	ltm2ck		:2;
		gulong	ltm2ax		:2;
		gulong	ltm2ah		:2;
		gulong	ltm2ap		:2;
		gulong	r2y2ck		:2;
		gulong	r2y2ax		:2;
		gulong	r2y2ah		:2;
		gulong	r2y2ap		:2;
		gulong	cnr2ck		:2;
		gulong	cnr2ax		:2;
		gulong	cnr2ap		:2;
		gulong	umcvdfmx4	:2;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
		gulong	umcpxfmx4	:2;
		gulong	umcvdfmx2	:2;
		gulong	umcpxfmx2	:2;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE

#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
		gulong	umchevencax4:2;
		gulong	umcvdfmx2	:2;
		gulong	hevencap	:2;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE

// --- REMOVE_ES_COMPILE_OPT END ---
		gulong	bmh1ck		:2;
	}bit;
};

/*	structure of CLKSTOP14	(1D02_1088h)	*/
union _IoChiptopClkstop14 {
	gulong		word;
	struct {
		gulong	statax		:2;
		gulong	statah		:2;
		gulong	statap		:2;
		gulong	periah		:2;
		gulong	periap		:2;
		gulong	senmskck	:2;
		gulong	gyrock		:2;
		gulong	exsah		:2;
		gulong	exsap		:2;
		gulong	pasck		:2;
		gulong	bmh0ck		:2;
		gulong	bmh0ax		:2;
		gulong				:2;
		gulong	rdmaax		:2;
		gulong	rdmaap		:2;
		gulong	bmh1ax		:2;
	}bit;
};

//struct _KChiptop1 {
//	KObject parent;
//};


//KConstType 	k_chiptop1_get_type(void);
//KChiptop1*		k_chiptop1_new(void);


#endif /* __K_CHIPTOP1_H__ */
