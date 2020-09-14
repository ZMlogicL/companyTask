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


#ifndef __JCTPMC_GPIO_H__
#define __JCTPMC_GPIO_H__


#include <stdio.h>
#include <glib-object.h>


typedef union 				_IoPmcGpioPdr IoPmcGpioPdr;
typedef union 				_IoPmcGpioDdr IoPmcGpioDdr;
typedef union 				_IoPmcGpioEpcr IoPmcGpioEpcr;
typedef union 				_IoPmcGpioPuder IoPmcGpioPuder;
typedef union 				_IoPmcGpioPudcr IoPmcGpioPudcr;
typedef struct 				_IoPmcGpio IoPmcGpio;

/* GPIO */

/* PDR */
union _IoPmcGpioPdr {
	gulong		word[3];
	struct {
		/* PDR10  */
		gulong	p00				:1;
		gulong	p01				:1;
		gulong	p02				:1;
		gulong	p03				:1;
		gulong	p04				:1;
		gulong	p05				:1;
		gulong	p06				:1;
		gulong	p07				:1;
		gulong	p10				:1;
		gulong	p11				:1;
		gulong	p12				:1;
		gulong	p13				:1;
		gulong	p14				:1;
		gulong	p15				:1;
		gulong	p16				:1;
		gulong	p17				:1;
		gulong	pwe00			:1;
		gulong	pwe01			:1;
		gulong	pwe02			:1;
		gulong	pwe03			:1;
		gulong	pwe04			:1;
		gulong	pwe05			:1;
		gulong	pwe06			:1;
		gulong	pwe07			:1;
		gulong	pwe10			:1;
		gulong	pwe11			:1;
		gulong	pwe12			:1;
		gulong	pwe13			:1;
		gulong	pwe14			:1;
		gulong	pwe15			:1;
		gulong	pwe16			:1;
		gulong	pwe17			:1;
		/* PDR32  */
		gulong	p20				:1;
		gulong	p21				:1;
		gulong	p22				:1;
		gulong	p23				:1;
		gulong	p24				:1;
		gulong	p25				:1;
		gulong	p26				:1;
		gulong	p27				:1;
		gulong	p30				:1;
		gulong	p31				:1;
		gulong	p32				:1;
		gulong	p33				:1;
		gulong	p34				:1;
		gulong	p35				:1;
		gulong	p36				:1;
		gulong	p37				:1;
		gulong	pwe20			:1;
		gulong	pwe21			:1;
		gulong	pwe22			:1;
		gulong	pwe23			:1;
		gulong	pwe24			:1;
		gulong	pwe25			:1;
		gulong	pwe26			:1;
		gulong	pwe27			:1;
		gulong	pwe30			:1;
		gulong	pwe31			:1;
		gulong	pwe32			:1;
		gulong	pwe33			:1;
		gulong	pwe34			:1;
		gulong	pwe35			:1;
		gulong	pwe36			:1;
		gulong	pwe37			:1;
		/* PDR54  */
		gulong					:4;
		gulong	p44				:1;
		gulong	p45				:1;
		gulong	p46				:1;
		gulong					:13;
		gulong	pwe44			:1;
		gulong	pwe45			:1;
		gulong	pwe46			:1;
		gulong					:9;
	}bit;
};

/* DDR */
union _IoPmcGpioDdr {
	gulong		word[3];
	struct {
		/* DDR10 */
		gulong	p00				:1;
		gulong	p01				:1;
		gulong	p02				:1;
		gulong	p03				:1;
		gulong	p04				:1;
		gulong	p05				:1;
		gulong	p06				:1;
		gulong	p07				:1;
		gulong	p10				:1;
		gulong	p11				:1;
		gulong	p12				:1;
		gulong	p13				:1;
		gulong	p14				:1;
		gulong	p15				:1;
		gulong	p16				:1;
		gulong	p17				:1;
		gulong					:16;
		/* DDR32 */
		gulong	p20				:1;
		gulong	p21				:1;
		gulong	p22				:1;
		gulong	p23				:1;
		gulong	p24				:1;
		gulong	p25				:1;
		gulong	p26				:1;
		gulong	p27				:1;
		gulong	p30				:1;
		gulong	p31				:1;
		gulong	p32				:1;
		gulong	p33				:1;
		gulong	p34				:1;
		gulong	p35				:1;
		gulong	p36				:1;
		gulong	p37				:1;
		gulong					:16;
		/* DDR54 */
		gulong					:4;
		gulong	p44				:1;
		gulong	p45				:1;
		gulong	p46				:1;
		gulong					:25;
	}bit;
};

/* EPCR */
union _IoPmcGpioEpcr {
	gulong		word[3];
	struct {
		/* EPCR10 */
		gulong					:32;
		/* EPCR32 */
		gulong					:2;
		gulong	p22				:1;
		gulong	p23				:1;
		gulong					:5;
		gulong	p31				:1;
		gulong					:1;
		gulong	p33				:1;
		gulong					:1;
		gulong	p35				:1;
		gulong					:1;
		gulong	p37				:1;
		gulong					:16;
		/* EPCR54 */
		gulong					:5;
		gulong	p45				:1;
		gulong					:26;
	}bit;
};

/* PUDER */
union _IoPmcGpioPuder {
	gulong		word[3];
	struct {
		/* PUDER10 */
		gulong	p00				:1;
		gulong	p01				:1;
		gulong	p02				:1;
		gulong	p03				:1;
		gulong	p04				:1;
		gulong	p05				:1;
		gulong	p06				:1;
		gulong	p07				:1;
		gulong	p10				:1;
		gulong	p11				:1;
		gulong	p12				:1;
		gulong	p13				:1;
		gulong	p14				:1;
		gulong	p15				:1;
		gulong	p16				:1;
		gulong	p17				:1;
		gulong					:16;
		/* PUDER32 */
		gulong	p20				:1;
		gulong	p21				:1;
		gulong	p22				:1;
		gulong	p23				:1;
		gulong	p24				:1;
		gulong	p25				:1;
		gulong	p26				:1;
		gulong	p27				:1;
		gulong	p30				:1;
		gulong	p31				:1;
		gulong	p32				:1;
		gulong	p33				:1;
		gulong	p34				:1;
		gulong	p35				:1;
		gulong	p36				:1;
		gulong	p37				:1;
		gulong					:16;
		/* PUDER54 */
		gulong					:4;
		gulong	p44				:1;
		gulong	p45				:1;
		gulong	p46				:1;
		gulong					:25;
	}bit;
};

/* PUDCR */
union _IoPmcGpioPudcr {
	gulong		word[3];
	struct {
		/* PUDCR10 */
		gulong	p00				:1;
		gulong	p01				:1;
		gulong	p02				:1;
		gulong	p03				:1;
		gulong	p04				:1;
		gulong	p05				:1;
		gulong	p06				:1;
		gulong	p07				:1;
		gulong	p10				:1;
		gulong	p11				:1;
		gulong	p12				:1;
		gulong	p13				:1;
		gulong	p14				:1;
		gulong	p15				:1;
		gulong	p16				:1;
		gulong	p17				:1;
		gulong					:16;
		/* PUDCR32 */
		gulong	p20				:1;
		gulong	p21				:1;
		gulong	p22				:1;
		gulong	p23				:1;
		gulong	p24				:1;
		gulong	p25				:1;
		gulong	p26				:1;
		gulong	p27				:1;
		gulong	p30				:1;
		gulong	p31				:1;
		gulong	p32				:1;
		gulong	p33				:1;
		gulong	p34				:1;
		gulong	p35				:1;
		gulong	p36				:1;
		gulong	p37				:1;
		gulong					:16;
		/* PUDCR54 */
		gulong					:4;
		gulong	p44				:1;
		gulong	p45				:1;
		gulong	p46				:1;
		gulong					:25;
	}bit;
};

/* GPIO */
struct _IoPmcGpio {
	/* 1DFF_(B000 - B00Bh) */
	IoPmcGpioPdr		pdr;
	/* 1DFF_(B00C - B0FFh)	*/
	guchar				dmyGpio00c0ff[0x100 - 0x00C];
	/* 1DFF_(B100 - B10Bh) */
	IoPmcGpioDdr		ddr;
	/* 1DFF_(B10C - B1FFh)	*/
	guchar				dmyGpio10c1ff[0x200 - 0x10C];
	/* 1DFF_(B200 - B20Bh) */
	IoPmcGpioEpcr		epcr;
	/* 1DFF_(B20C - B2FFh)	*/
	guchar				dmyGpio20c2ff[0x300 - 0x20C];
	/* 1DFF_(B300 - B30Bh) */
	IoPmcGpioPuder		puder;
	/* 1DFF_(B30C - B3FFh)	*/
	guchar				dmyGpio30c3ff[0x400 - 0x30C];
	/* 1DFF_(B400 - B40Bh) */
	IoPmcGpioPudcr		pudcr;
	/* 1DFF_(B40C - BFFFh)	*/
	guchar				dmyGpio40cFff[0x1000 - 0x40C];
};


#endif /* __JCTPMC_GPIO_H__ */
