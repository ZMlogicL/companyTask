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


#ifndef __JCTPMC_EXIU_H__
#define __JCTPMC_EXIU_H__


#include <stdio.h>
#include <glib-object.h>


typedef union 				_IoPmcExiuEimask IoPmcExiuEimask;
typedef union 				_IoPmcExiuEisrcsel IoPmcExiuEisrcsel;
typedef union 				_IoPmcExiuEireqsta IoPmcExiuEireqsta;
typedef union 				_IoPmcExiuEirawreqsta IoPmcExiuEirawreqsta;
typedef union 				_IoPmcExiuEireqclr IoPmcExiuEireqclr;
typedef union 				_IoPmcExiuEilvl IoPmcExiuEilvl;
typedef union 				_IoPmcExiuEiedg IoPmcExiuEiedg;
typedef union 				_IoPmcExiuEisir IoPmcExiuEisir;
typedef struct 				_IoPmcExiu IoPmcExiu;

/* structure of EIMASK			(1DFF_3000h) */
union _IoPmcExiuEimask {
	gulong		word;
	struct {
		gulong	eimask0 		:1;
		gulong	eimask1 		:1;
		gulong	eimask2 		:1;
		gulong	eimask3 		:1;
		gulong	eimask4 		:1;
		gulong	eimask5 		:1;
		gulong	eimask6 		:1;
		gulong	eimask7 		:1;
		gulong	eimask8 		:1;
		gulong	eimask9 		:1;
		gulong	eimask10		:1;
		gulong	eimask11		:1;
		gulong	eimask12		:1;
		gulong	eimask13		:1;
		gulong	eimask14		:1;
		gulong	eimask15		:1;
		gulong	eimask16		:1;
		gulong					:15;
	}bit;
};

/* structure of EISRCSEL		(1DFF_3004h) */
union _IoPmcExiuEisrcsel {
	gulong		word;
	struct {
		gulong	eisrcsel0		:1;
		gulong	eisrcsel1		:1;
		gulong	eisrcsel2		:1;
		gulong	eisrcsel3		:1;
		gulong	eisrcsel4		:1;
		gulong	eisrcsel5		:1;
		gulong	eisrcsel6		:1;
		gulong	eisrcsel7		:1;
		gulong	eisrcsel8		:1;
		gulong	eisrcsel9		:1;
		gulong	eisrcsel10		:1;
		gulong	eisrcsel11		:1;
		gulong	eisrcsel12		:1;
		gulong	eisrcsel13		:1;
		gulong	eisrcsel14		:1;
		gulong	eisrcsel15		:1;
		gulong	eisrcsel16		:1;
		gulong					:15;
	}bit;
};

/* structure of EIREQSTA		(1DFF_3008h) */
union _IoPmcExiuEireqsta {
	gulong		word;
	struct {
		gulong	eireqsta0		:1;
		gulong	eireqsta1		:1;
		gulong	eireqsta2		:1;
		gulong	eireqsta3		:1;
		gulong	eireqsta4		:1;
		gulong	eireqsta5		:1;
		gulong	eireqsta6		:1;
		gulong	eireqsta7		:1;
		gulong	eireqsta8		:1;
		gulong	eireqsta9		:1;
		gulong	eireqsta10		:1;
		gulong	eireqsta11		:1;
		gulong	eireqsta12		:1;
		gulong	eireqsta13		:1;
		gulong	eireqsta14		:1;
		gulong	eireqsta15		:1;
		gulong	eireqsta16		:1;
		gulong					:15;
	}bit;
};

/* structure of EIRAWREQSTA		(1DFF_300Ch) */
union _IoPmcExiuEirawreqsta {
	gulong		word;
	struct {
		gulong	eirawreqsta0	:1;
		gulong	eirawreqsta1	:1;
		gulong	eirawreqsta2	:1;
		gulong	eirawreqsta3	:1;
		gulong	eirawreqsta4	:1;
		gulong	eirawreqsta5	:1;
		gulong	eirawreqsta6	:1;
		gulong	eirawreqsta7	:1;
		gulong	eirawreqsta8	:1;
		gulong	eirawreqsta9	:1;
		gulong	eirawreqsta10	:1;
		gulong	eirawreqsta11	:1;
		gulong	eirawreqsta12	:1;
		gulong	eirawreqsta13	:1;
		gulong	eirawreqsta14	:1;
		gulong	eirawreqsta15	:1;
		gulong	eirawreqsta16	:1;
		gulong					:15;
	}bit;
};

/* structure of EIREQCLR		(1DFF_3010h) */
union _IoPmcExiuEireqclr {
	gulong		word;
	struct {
		gulong	eireqclr0		:1;
		gulong	eireqclr1		:1;
		gulong	eireqclr2		:1;
		gulong	eireqclr3		:1;
		gulong	eireqclr4		:1;
		gulong	eireqclr5		:1;
		gulong	eireqclr6		:1;
		gulong	eireqclr7		:1;
		gulong	eireqclr8		:1;
		gulong	eireqclr9		:1;
		gulong	eireqclr10		:1;
		gulong	eireqclr11		:1;
		gulong	eireqclr12		:1;
		gulong	eireqclr13		:1;
		gulong	eireqclr14		:1;
		gulong	eireqclr15		:1;
		gulong	eireqclr16		:1;
		gulong					:15;
	}bit;
};

/* structure of EILVL			(1DFF_3014h) */
union _IoPmcExiuEilvl {
	gulong		word;
	struct {
		gulong	eilvl0			:1;
		gulong	eilvl1			:1;
		gulong	eilvl2			:1;
		gulong	eilvl3			:1;
		gulong	eilvl4			:1;
		gulong	eilvl5			:1;
		gulong	eilvl6			:1;
		gulong	eilvl7			:1;
		gulong	eilvl8			:1;
		gulong	eilvl9			:1;
		gulong	eilvl10 		:1;
		gulong	eilvl11 		:1;
		gulong	eilvl12 		:1;
		gulong	eilvl13 		:1;
		gulong	eilvl14 		:1;
		gulong	eilvl15 		:1;
		gulong	eilvl16 		:1;
		gulong			 		:15;
	}bit;
};

/* structure of EIEDG			(1DFF_3018h) */
union _IoPmcExiuEiedg {
	gulong		word;
	struct {
		gulong	eiedg0			:1;
		gulong	eiedg1			:1;
		gulong	eiedg2			:1;
		gulong	eiedg3			:1;
		gulong	eiedg4			:1;
		gulong	eiedg5			:1;
		gulong	eiedg6			:1;
		gulong	eiedg7			:1;
		gulong	eiedg8			:1;
		gulong	eiedg9			:1;
		gulong	eiedg10 		:1;
		gulong	eiedg11 		:1;
		gulong	eiedg12 		:1;
		gulong	eiedg13 		:1;
		gulong	eiedg14 		:1;
		gulong	eiedg15 		:1;
		gulong	eiedg16 		:1;
		gulong			 		:15;
	}bit;
};

/* structure of EISIR			(1DFF_301Ch) */
union _IoPmcExiuEisir {
	gulong		word;
	struct {
		gulong	eisir0			:1;
		gulong	eisir1			:1;
		gulong	eisir2			:1;
		gulong	eisir3			:1;
		gulong	eisir4			:1;
		gulong	eisir5			:1;
		gulong	eisir6			:1;
		gulong	eisir7			:1;
		gulong	eisir8			:1;
		gulong	eisir9			:1;
		gulong	eisir10 		:1;
		gulong	eisir11 		:1;
		gulong	eisir12 		:1;
		gulong	eisir13 		:1;
		gulong	eisir14 		:1;
		gulong	eisir15 		:1;
		gulong	eisir16 		:1;
		gulong			 		:15;
	}bit;
};

/*	EXIU register							*/
struct _IoPmcExiu {
	/* 1DFF_(3000 - 3003h) Interrupt Masking Register */
	IoPmcExiuEimask			eimask;
	/* 1DFF_(3004 - 3007h) Interrupt Source Select Register */
	IoPmcExiuEisrcsel			eisrcsel;
	/* 1DFF_(3008 - 300Bh) Internal Interrupt Request Status Register */
	IoPmcExiuEireqsta			eireqsta;
	/* 1DFF_(300C - 300Fh) Raw Interrupt Request Status Register */
	IoPmcExiuEirawreqsta		eirawreqsta;
	/* 1DFF_(3010 - 3013h) Interrupt Clear Register */
	IoPmcExiuEireqclr			eireqclr;
	/* 1DFF_(3014 - 3017h) External Interrupt Level Setting Register */
	IoPmcExiuEilvl 			eilvl;
	/* 1DFF_(3018 - 301Bh) Interrupt Detection Method Setting Register */
	IoPmcExiuEiedg 			eiedg;
	/* 1DFF_(301C - 301Fh) Software Interrupt Register */
	IoPmcExiuEisir 			eisir;
	/* 1DFF_3020 - 1DFF_3FFFh)	*/
	guchar						dmyPmcExiu30203fff[0x4000 - 0x3020];
};


#endif /* __JCTPMC_EXIU_H__ */
