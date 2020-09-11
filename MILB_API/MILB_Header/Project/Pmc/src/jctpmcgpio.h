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


#ifndef __JCTPMC_GPIO_H__
#define __JCTPMC_GPIO_H__


#include <klib.h>


#define JCTPMC_TYPE_GPIO		(jctpmc_gpio_get_type())
#define JCTPMC_GPIO(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, JctpmcGpio))
#define JCTPMC_IS_GPIO(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, JCTPMC_TYPE_GPIO))


typedef union 				_IoPmcGpioPdr IoPmcGpioPdr;
typedef union 				_IoPmcGpioDdr IoPmcGpioDdr;
typedef union 				_IoPmcGpioEpcr IoPmcGpioEpcr;
typedef union 				_IoPmcGpioPuder IoPmcGpioPuder;
typedef union 				_IoPmcGpioPudcr IoPmcGpioPudcr;
typedef struct 				_IoPmcGpio IoPmcGpio;
typedef struct 				_JctpmcGpio JctpmcGpio;
typedef struct 				_JctpmcGpioPrivate JctpmcGpioPrivate;

/* GPIO */

/* PDR */
union _IoPmcGpioPdr {
	kulong		word[3];
	struct {
		/* PDR10  */
		kulong	p00				:1;
		kulong	p01				:1;
		kulong	p02				:1;
		kulong	p03				:1;
		kulong	p04				:1;
		kulong	p05				:1;
		kulong	p06				:1;
		kulong	p07				:1;
		kulong	p10				:1;
		kulong	p11				:1;
		kulong	p12				:1;
		kulong	p13				:1;
		kulong	p14				:1;
		kulong	p15				:1;
		kulong	p16				:1;
		kulong	p17				:1;
		kulong	pwe00			:1;
		kulong	pwe01			:1;
		kulong	pwe02			:1;
		kulong	pwe03			:1;
		kulong	pwe04			:1;
		kulong	pwe05			:1;
		kulong	pwe06			:1;
		kulong	pwe07			:1;
		kulong	pwe10			:1;
		kulong	pwe11			:1;
		kulong	pwe12			:1;
		kulong	pwe13			:1;
		kulong	pwe14			:1;
		kulong	pwe15			:1;
		kulong	pwe16			:1;
		kulong	pwe17			:1;
		/* PDR32  */
		kulong	p20				:1;
		kulong	p21				:1;
		kulong	p22				:1;
		kulong	p23				:1;
		kulong	p24				:1;
		kulong	p25				:1;
		kulong	p26				:1;
		kulong	p27				:1;
		kulong	p30				:1;
		kulong	p31				:1;
		kulong	p32				:1;
		kulong	p33				:1;
		kulong	p34				:1;
		kulong	p35				:1;
		kulong	p36				:1;
		kulong	p37				:1;
		kulong	pwe20			:1;
		kulong	pwe21			:1;
		kulong	pwe22			:1;
		kulong	pwe23			:1;
		kulong	pwe24			:1;
		kulong	pwe25			:1;
		kulong	pwe26			:1;
		kulong	pwe27			:1;
		kulong	pwe30			:1;
		kulong	pwe31			:1;
		kulong	pwe32			:1;
		kulong	pwe33			:1;
		kulong	pwe34			:1;
		kulong	pwe35			:1;
		kulong	pwe36			:1;
		kulong	pwe37			:1;
		/* PDR54  */
		kulong					:4;
		kulong	p44				:1;
		kulong	p45				:1;
		kulong	p46				:1;
		kulong					:13;
		kulong	pwe44			:1;
		kulong	pwe45			:1;
		kulong	pwe46			:1;
		kulong					:9;
	}bit;
};

/* DDR */
union _IoPmcGpioDdr {
	kulong		word[3];
	struct {
		/* DDR10 */
		kulong	p00				:1;
		kulong	p01				:1;
		kulong	p02				:1;
		kulong	p03				:1;
		kulong	p04				:1;
		kulong	p05				:1;
		kulong	p06				:1;
		kulong	p07				:1;
		kulong	p10				:1;
		kulong	p11				:1;
		kulong	p12				:1;
		kulong	p13				:1;
		kulong	p14				:1;
		kulong	p15				:1;
		kulong	p16				:1;
		kulong	p17				:1;
		kulong					:16;
		/* DDR32 */
		kulong	p20				:1;
		kulong	p21				:1;
		kulong	p22				:1;
		kulong	p23				:1;
		kulong	p24				:1;
		kulong	p25				:1;
		kulong	p26				:1;
		kulong	p27				:1;
		kulong	p30				:1;
		kulong	p31				:1;
		kulong	p32				:1;
		kulong	p33				:1;
		kulong	p34				:1;
		kulong	p35				:1;
		kulong	p36				:1;
		kulong	p37				:1;
		kulong					:16;
		/* DDR54 */
		kulong					:4;
		kulong	p44				:1;
		kulong	p45				:1;
		kulong	p46				:1;
		kulong					:25;
	}bit;
};

/* EPCR */
union _IoPmcGpioEpcr {
	kulong		word[3];
	struct {
		/* EPCR10 */
		kulong					:32;
		/* EPCR32 */
		kulong					:2;
		kulong	p22				:1;
		kulong	p23				:1;
		kulong					:5;
		kulong	p31				:1;
		kulong					:1;
		kulong	p33				:1;
		kulong					:1;
		kulong	p35				:1;
		kulong					:1;
		kulong	p37				:1;
		kulong					:16;
		/* EPCR54 */
		kulong					:5;
		kulong	p45				:1;
		kulong					:26;
	}bit;
};

/* PUDER */
union _IoPmcGpioPuder {
	kulong		word[3];
	struct {
		/* PUDER10 */
		kulong	p00				:1;
		kulong	p01				:1;
		kulong	p02				:1;
		kulong	p03				:1;
		kulong	p04				:1;
		kulong	p05				:1;
		kulong	p06				:1;
		kulong	p07				:1;
		kulong	p10				:1;
		kulong	p11				:1;
		kulong	p12				:1;
		kulong	p13				:1;
		kulong	p14				:1;
		kulong	p15				:1;
		kulong	p16				:1;
		kulong	p17				:1;
		kulong					:16;
		/* PUDER32 */
		kulong	p20				:1;
		kulong	p21				:1;
		kulong	p22				:1;
		kulong	p23				:1;
		kulong	p24				:1;
		kulong	p25				:1;
		kulong	p26				:1;
		kulong	p27				:1;
		kulong	p30				:1;
		kulong	p31				:1;
		kulong	p32				:1;
		kulong	p33				:1;
		kulong	p34				:1;
		kulong	p35				:1;
		kulong	p36				:1;
		kulong	p37				:1;
		kulong					:16;
		/* PUDER54 */
		kulong					:4;
		kulong	p44				:1;
		kulong	p45				:1;
		kulong	p46				:1;
		kulong					:25;
	}bit;
};

/* PUDCR */
union _IoPmcGpioPudcr {
	kulong		word[3];
	struct {
		/* PUDCR10 */
		kulong	p00				:1;
		kulong	p01				:1;
		kulong	p02				:1;
		kulong	p03				:1;
		kulong	p04				:1;
		kulong	p05				:1;
		kulong	p06				:1;
		kulong	p07				:1;
		kulong	p10				:1;
		kulong	p11				:1;
		kulong	p12				:1;
		kulong	p13				:1;
		kulong	p14				:1;
		kulong	p15				:1;
		kulong	p16				:1;
		kulong	p17				:1;
		kulong					:16;
		/* PUDCR32 */
		kulong	p20				:1;
		kulong	p21				:1;
		kulong	p22				:1;
		kulong	p23				:1;
		kulong	p24				:1;
		kulong	p25				:1;
		kulong	p26				:1;
		kulong	p27				:1;
		kulong	p30				:1;
		kulong	p31				:1;
		kulong	p32				:1;
		kulong	p33				:1;
		kulong	p34				:1;
		kulong	p35				:1;
		kulong	p36				:1;
		kulong	p37				:1;
		kulong					:16;
		/* PUDCR54 */
		kulong					:4;
		kulong	p44				:1;
		kulong	p45				:1;
		kulong	p46				:1;
		kulong					:25;
	}bit;
};

/* GPIO */
struct _IoPmcGpio {
	/* 1DFF_(B000 - B00Bh) */
	IoPmcGpioPdr		pdr;
	/* 1DFF_(B00C - B0FFh)	*/
	kuchar				dmyGpio00c0ff[0x100 - 0x00C];
	/* 1DFF_(B100 - B10Bh) */
	IoPmcGpioDdr		ddr;
	/* 1DFF_(B10C - B1FFh)	*/
	kuchar				dmyGpio10c1ff[0x200 - 0x10C];
	/* 1DFF_(B200 - B20Bh) */
	IoPmcGpioEpcr		epcr;
	/* 1DFF_(B20C - B2FFh)	*/
	kuchar				dmyGpio20c2ff[0x300 - 0x20C];
	/* 1DFF_(B300 - B30Bh) */
	IoPmcGpioPuder		puder;
	/* 1DFF_(B30C - B3FFh)	*/
	kuchar				dmyGpio30c3ff[0x400 - 0x30C];
	/* 1DFF_(B400 - B40Bh) */
	IoPmcGpioPudcr		pudcr;
	/* 1DFF_(B40C - BFFFh)	*/
	kuchar				dmyGpio40cFff[0x1000 - 0x40C];
};

struct _JctpmcGpio {
	KObject parent;
};


KConstType 				jctpmc_gpio_get_type(void);
JctpmcGpio*		        jctpmc_gpio_new(void);


#endif /* __JCTPMC_GPIO_H__ */
