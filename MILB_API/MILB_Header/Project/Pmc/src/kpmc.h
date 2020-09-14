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


#ifndef __K_PMC_H__
#define __K_PMC_H__


#include <stdio.h>
#include <glib-object.h>
#include "jctpmcadc.h"
#include "jctpmccrg11.h"
#include "jctpmccalendar.h"
#include "jctpmcexiu.h"
#include "jctpmcgpio.h"
#include "jctpmchdmac.h"
#include "jctpmci2c.h"
#include "jctpmcpmu.h"
#include "jctpmcspi.h"
#include "jctpmcsensorif.h"
#include "jctpmcuart.h"
#include "jctpmcwatchdog.h"


G_BEGIN_DECLS


#define K_TYPE_PMC								(k_pmc_get_type())
#define K_PMC(obj)									(G_TYPE_CHECK_INSTANCE_CAST(obj, K_TYPE_PMC, KPmc))
#define K_PMC_CALSS(klass)              		(G_TYPE_CHECK_CLASS_CAST((klass), K_TYPE_PMC, KPmcClass))
#define K_IS_PMC(obj)                        		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), K_TYPE_PMC))
#define K_IS_PMC_CLASS(klass)         		(G_TYPE_CHECK_CLASS_TYPE ((klass), K_TYPE_PMC))
#define K_PMC_GET_CLASS(obj)         		(G_TYPE_INSTANCE_GET_CLASS ((obj), K_TYPE_PMC, KPmcClass))


typedef union 				_IoPmcMdr IoPmcMdr;
typedef union 				_IoPmcPerselm1 IoPmcPerselm1;
typedef union 				_IoPmcDbcntm1 IoPmcDbcntm1;
typedef union				 _IoPmcAsv IoPmcAsv;
typedef union				_IoPmcGpioIicr IoPmcGpioIicr;
typedef union 				_IoPmcIrsir IoPmcIrsir;
typedef union 				_IoPmcCtcCtl IoPmcCtcCtl;
typedef union 				_IoPmcCtcIntctl IoPmcCtcIntctl;
typedef union 				_IoPmcCtcIntstat IoPmcCtcIntstat;
typedef union 				_IoPmcCtcObclen IoPmcCtcObclen;
typedef union 				_IoPmcTmrTmcsr	 IoPmcTmrTmcsr;
typedef struct 				_IoPmcCtc	IoPmcCtc;
typedef struct 				_IoPmcTmr	IoPmcTmr;
typedef struct 				_IoPmc	IoPmc;
typedef struct 				_KPmc  KPmc;
typedef struct 				_KPmcClass  KPmcClass;
typedef struct 				_KPmcPrivate  KPmcPrivate;

/* PMC */

/* MDR (Mode indication register) */
union _IoPmcMdr {
	gulong		word;
	struct {
		gulong	md				:6;
		gulong					:22;
		gulong	ver				:4;
	}bit;
};

/* PERSELM1 (Peripheral blcok function select 1) register */
union _IoPmcPerselm1 {
	gulong		word;
	struct {
		gulong	i2chcnt			:2;
		gulong	sdanch			:1;
		gulong	sclnch			:1;
		gulong					:4;
		gulong	sp0misope		:1;
		gulong	sp0mosipe		:1;
		gulong	sp0sckpe		:1;
		gulong	sp0cspe			:1;
		gulong	sp0misoudc		:1;
		gulong	sp0mosiudc		:1;
		gulong	sp0sckudc		:1;
		gulong	sp0csudc		:1;
		gulong					:16;
	}bit;
};

/* DBCNTM1 (Drivability Control M1) register */
union _IoPmcDbcntm1 {
	gulong		word;
	struct {
		gulong	t00dcm			:2;
		gulong	t01dcm			:2;
		gulong	t02dcm			:2;
		gulong	t03dcm			:2;
		gulong	t04dcm			:2;
		gulong	t05dcm			:2;
		gulong	t06dcm			:2;
		gulong					:18;
	}bit;
};

/* ASV(Adaptive Supply Voltage) code register */
union _IoPmcAsv {
	gulong		word;
	struct {
		gulong	asv				:5;
		gulong					:27;
	}bit;
};

/* GPIO initial inputs code register */
union _IoPmcGpioIicr {
	gulong		word;
	struct {
		gulong	p0700			:8;
		gulong	p1710			:8;
		gulong					:16;
	}bit;
};

/* Internal reset signal indication register */
union _IoPmcIrsir {
	gulong		word;
	struct {
		gulong	hrrstx			:1;
		gulong					:31;
	}bit;
};


/* Cycle Time Counter CTL register */
union _IoPmcCtcCtl {
	gulong		word;
	struct {
		gulong	trg				:1;
		gulong					:31;
	}bit;
};

/* Cycle Time Counter INTCTL register */
union _IoPmcCtcIntctl {
	gulong		word;
	struct {
		gulong	meie			:1;
		gulong					:3;
		gulong	swfi			:1;
		gulong					:27;
	}bit;
};

/* Cycle Time Counter INTSTAT register */
union _IoPmcCtcIntstat {
	gulong		word;
	struct {
		gulong	mest			:1;
		gulong					:31;
	}bit;
};

/* Cycle Time Counter OBCLEN register */
union _IoPmcCtcObclen {
	gulong		word;
	struct {
		gulong	obclen			:16;
		gulong					:16;
	}bit;
};

/* 32-Bit Reload Timer TMCSR register */
union _IoPmcTmrTmcsr {
	gulong		word;
	struct {
		gulong	trg				:1;
		gulong	cnte			:1;
		gulong	uf				:1;
		gulong	inte			:1;
		gulong	reld			:1;
		gulong	outl			:1;
		gulong					:4;
		gulong	csl				:2;
		gulong	rels			:1;
		gulong					:19;
	}bit;
};

/* Cycle Time Counter */
struct _IoPmcCtc {
	/* 1DFF_(1000 - 1003h) */
	IoPmcCtcCtl			ctl;
	/* 1DFF_(1004 - 1007h) */
	IoPmcCtcIntctl		intctl;
	/* 1DFF_(1008 - 100Bh) */
	IoPmcCtcIntstat		intstat;
	/* 1DFF_(100C - 100Fh) */
	IoPmcCtcObclen		obclen;
	/* 1DFF_(1010 - 1013h) */
	gulong				cntval;
	/* 1DFF_(1014 - 1FFFh) */
	guchar				dmyPmcTmr00140FFF[0x1000 - 0x014];
};

/* 32-Bit Reload Timer */
struct _IoPmcTmr {
	/* 1DFF_(6000 - 6003h) */
	IoPmcTmrTmcsr			tmcsr;
	/* 1DFF_(6004 - 6007h) */
	gulong			tmr;
	/* 1DFF_(6008 - 600Bh) */
	gulong			tmrlr0;
	/* 1DFF_(600C - 600Fh) */
	gulong			tmrlr1;
	/* 1DFF_(6010 - 6FFFh) */
	guchar			dmyPmcTmr00100FFF[0x1000 - 0x010];
};

/* PMC */
struct _IoPmc {
	/* 1DC0_0000h	*/
	IoPmcHdmac 		hdmac;
	/* 1DD0_0000h	*/
	IoPmcSpi 			spi;
	/* 1DE0_0000h	*/
	IoPmcUart 		uart;
	/* 1DF0_0000 - 1DFF_0FFFh	*/
	guchar				dmyPmc1df000001dff0fff[0x1DFF1000 - 0x1DF00000];
	/* 1DFF_1000h	*/
	IoPmcCtc 			ctc;
	/* 1DFF_2000 - 1DFF_2FFFh	*/
	guchar				dmyPmc1dff20001dff2fff[0x1DFF3000 - 0x1DFF2000];
	/* 1DFF_3000h	*/
	IoPmcExiu			exiu;
	/* 1DFF_4000h	*/
	IoPmcMdr			mdr;
	/* 1DFF_4004h	*/
	IoPmcPerselm1		perselm1;
	/* 1DFF_4008h	*/
	IoPmcDbcntm1		dbcntm1;
	/* 1DFF_400C - 1DFF_400Fh	*/
	guchar				dmyPmc1dff400c1dff400f[0x1DFF4010 - 0x1DFF400C];
	/* 1DFF_4010h	*/
	IoPmcAsv			asv;
	/* 1DFF_4014 - 1DFF_4FFFh	*/
	guchar				dmyPmc1dff40141dff4fff[0x1DFF5000 - 0x1DFF4014];
	/* 1DFF_5000h	*/
	IoPmcAdc 		adc;
	/* 1DFF_6000h	*/
	IoPmcTmr						tmr;
	/* 1DFF_7000h	*/
	IoPmcI2c 			i2c;
	/* 1DFF_7400 - 1DFF_7FFFh	*/
	guchar				dmyPmc1dff74001dff7fff[0x1DFF8000 - 0x1DFF7400];
	/* 1DFF_8000h	*/
	IoPmcGpioIicr 	gpioIicr;
	/* 1DFF_8004 - 1DFF_800Fh	*/
	guchar				dmyPmc1dff80041dff800f[0x1DFF8010 - 0x1DFF8004];
	/* 1DFF_8010h	*/
	IoPmcIrsir	 	irsir;
	/* 1DFF_8014 - 1DFF_9FFFh	*/
	guchar				dmyPmc1dff80141dff9fff[0x1DFFA000 - 0x1DFF8014];
	/* 1DFF_A000h	*/
	IoPmcSensorIf	tempSensorIf;
	/* 1DFF_B000h	*/
	IoPmcGpio 		gpio;
	/* 1DFF_C000h	*/
	IoPmcCalendar 	calendar;
	/* 1DFF_D000h	*/
	IoPmcWatchdog 	watchdog;
	/* 1DFF_E000h	*/
	IoPmcCrg11 		crg11;
	/* 1DFF_F000h	*/
	IoPmcPmu 			pmu;
};

struct _KPmc
{
	GObject    parent;
};

struct _KPmcClass
{
	GObject    parentclass;
};

/* addr 1DC0_0000h- */
extern volatile IoPmc	ioPmc;


GType 							k_pmc_get_type(void) G_GNUC_CONST;
KPmc *         				k_pmc_new(void);


G_END_DECLS


#endif /* __K_PMC_H__ */
