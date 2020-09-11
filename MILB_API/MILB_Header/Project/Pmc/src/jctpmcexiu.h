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


#ifndef __JCTPMC_EXIU_H__
#define __JCTPMC_EXIU_H__


#include <klib.h>


#define JCTPMC_TYPE_EXIU			(jctpmc_exiu_get_type())
#define JCTPMC_EXIU(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, JctpmcExiu))
#define JCTPMC_IS_EXIU(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, JCTPMC_TYPE_EXIU))


typedef union 				_IoPmcExiuEimask IoPmcExiuEimask;
typedef union 				_IoPmcExiuEisrcsel IoPmcExiuEisrcsel;
typedef union 				_IoPmcExiuEireqsta IoPmcExiuEireqsta;
typedef union 				_IoPmcExiuEirawreqsta IoPmcExiuEirawreqsta;
typedef union 				_IoPmcExiuEireqclr IoPmcExiuEireqclr;
typedef union 				_IoPmcExiuEilvl IoPmcExiuEilvl;
typedef union 				_IoPmcExiuEiedg IoPmcExiuEiedg;
typedef union 				_IoPmcExiuEisir IoPmcExiuEisir;
typedef struct 				_IoPmcExiu IoPmcExiu;
typedef struct 				_JctpmcExiu JctpmcExiu;
typedef struct 				_JctpmcExiuPrivate JctpmcExiuPrivate;

/* structure of EIMASK			(1DFF_3000h) */
union _IoPmcExiuEimask {
	kulong		word;
	struct {
		kulong	eimask0 		:1;
		kulong	eimask1 		:1;
		kulong	eimask2 		:1;
		kulong	eimask3 		:1;
		kulong	eimask4 		:1;
		kulong	eimask5 		:1;
		kulong	eimask6 		:1;
		kulong	eimask7 		:1;
		kulong	eimask8 		:1;
		kulong	eimask9 		:1;
		kulong	eimask10		:1;
		kulong	eimask11		:1;
		kulong	eimask12		:1;
		kulong	eimask13		:1;
		kulong	eimask14		:1;
		kulong	eimask15		:1;
		kulong	eimask16		:1;
		kulong					:15;
	}bit;
};

/* structure of EISRCSEL		(1DFF_3004h) */
union _IoPmcExiuEisrcsel {
	kulong		word;
	struct {
		kulong	eisrcsel0		:1;
		kulong	eisrcsel1		:1;
		kulong	eisrcsel2		:1;
		kulong	eisrcsel3		:1;
		kulong	eisrcsel4		:1;
		kulong	eisrcsel5		:1;
		kulong	eisrcsel6		:1;
		kulong	eisrcsel7		:1;
		kulong	eisrcsel8		:1;
		kulong	eisrcsel9		:1;
		kulong	eisrcsel10		:1;
		kulong	eisrcsel11		:1;
		kulong	eisrcsel12		:1;
		kulong	eisrcsel13		:1;
		kulong	eisrcsel14		:1;
		kulong	eisrcsel15		:1;
		kulong	eisrcsel16		:1;
		kulong					:15;
	}bit;
};

/* structure of EIREQSTA		(1DFF_3008h) */
union _IoPmcExiuEireqsta {
	kulong		word;
	struct {
		kulong	eireqsta0		:1;
		kulong	eireqsta1		:1;
		kulong	eireqsta2		:1;
		kulong	eireqsta3		:1;
		kulong	eireqsta4		:1;
		kulong	eireqsta5		:1;
		kulong	eireqsta6		:1;
		kulong	eireqsta7		:1;
		kulong	eireqsta8		:1;
		kulong	eireqsta9		:1;
		kulong	eireqsta10		:1;
		kulong	eireqsta11		:1;
		kulong	eireqsta12		:1;
		kulong	eireqsta13		:1;
		kulong	eireqsta14		:1;
		kulong	eireqsta15		:1;
		kulong	eireqsta16		:1;
		kulong					:15;
	}bit;
};

/* structure of EIRAWREQSTA		(1DFF_300Ch) */
union _IoPmcExiuEirawreqsta {
	kulong		word;
	struct {
		kulong	eirawreqsta0	:1;
		kulong	eirawreqsta1	:1;
		kulong	eirawreqsta2	:1;
		kulong	eirawreqsta3	:1;
		kulong	eirawreqsta4	:1;
		kulong	eirawreqsta5	:1;
		kulong	eirawreqsta6	:1;
		kulong	eirawreqsta7	:1;
		kulong	eirawreqsta8	:1;
		kulong	eirawreqsta9	:1;
		kulong	eirawreqsta10	:1;
		kulong	eirawreqsta11	:1;
		kulong	eirawreqsta12	:1;
		kulong	eirawreqsta13	:1;
		kulong	eirawreqsta14	:1;
		kulong	eirawreqsta15	:1;
		kulong	eirawreqsta16	:1;
		kulong					:15;
	}bit;
};

/* structure of EIREQCLR		(1DFF_3010h) */
union _IoPmcExiuEireqclr {
	kulong		word;
	struct {
		kulong	eireqclr0		:1;
		kulong	eireqclr1		:1;
		kulong	eireqclr2		:1;
		kulong	eireqclr3		:1;
		kulong	eireqclr4		:1;
		kulong	eireqclr5		:1;
		kulong	eireqclr6		:1;
		kulong	eireqclr7		:1;
		kulong	eireqclr8		:1;
		kulong	eireqclr9		:1;
		kulong	eireqclr10		:1;
		kulong	eireqclr11		:1;
		kulong	eireqclr12		:1;
		kulong	eireqclr13		:1;
		kulong	eireqclr14		:1;
		kulong	eireqclr15		:1;
		kulong	eireqclr16		:1;
		kulong					:15;
	}bit;
};

/* structure of EILVL			(1DFF_3014h) */
union _IoPmcExiuEilvl {
	kulong		word;
	struct {
		kulong	eilvl0			:1;
		kulong	eilvl1			:1;
		kulong	eilvl2			:1;
		kulong	eilvl3			:1;
		kulong	eilvl4			:1;
		kulong	eilvl5			:1;
		kulong	eilvl6			:1;
		kulong	eilvl7			:1;
		kulong	eilvl8			:1;
		kulong	eilvl9			:1;
		kulong	eilvl10 		:1;
		kulong	eilvl11 		:1;
		kulong	eilvl12 		:1;
		kulong	eilvl13 		:1;
		kulong	eilvl14 		:1;
		kulong	eilvl15 		:1;
		kulong	eilvl16 		:1;
		kulong			 		:15;
	}bit;
};

/* structure of EIEDG			(1DFF_3018h) */
union _IoPmcExiuEiedg {
	kulong		word;
	struct {
		kulong	eiedg0			:1;
		kulong	eiedg1			:1;
		kulong	eiedg2			:1;
		kulong	eiedg3			:1;
		kulong	eiedg4			:1;
		kulong	eiedg5			:1;
		kulong	eiedg6			:1;
		kulong	eiedg7			:1;
		kulong	eiedg8			:1;
		kulong	eiedg9			:1;
		kulong	eiedg10 		:1;
		kulong	eiedg11 		:1;
		kulong	eiedg12 		:1;
		kulong	eiedg13 		:1;
		kulong	eiedg14 		:1;
		kulong	eiedg15 		:1;
		kulong	eiedg16 		:1;
		kulong			 		:15;
	}bit;
};

/* structure of EISIR			(1DFF_301Ch) */
union _IoPmcExiuEisir {
	kulong		word;
	struct {
		kulong	eisir0			:1;
		kulong	eisir1			:1;
		kulong	eisir2			:1;
		kulong	eisir3			:1;
		kulong	eisir4			:1;
		kulong	eisir5			:1;
		kulong	eisir6			:1;
		kulong	eisir7			:1;
		kulong	eisir8			:1;
		kulong	eisir9			:1;
		kulong	eisir10 		:1;
		kulong	eisir11 		:1;
		kulong	eisir12 		:1;
		kulong	eisir13 		:1;
		kulong	eisir14 		:1;
		kulong	eisir15 		:1;
		kulong	eisir16 		:1;
		kulong			 		:15;
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
	kuchar						dmyPmcExiu30203fff[0x4000 - 0x3020];
};

struct _JctpmcExiu {
	KObject parent;
};


KConstType 				jctpmc_exiu_get_type(void);
JctpmcExiu*		        jctpmc_exiu_new(void);


#endif /* __JCTPMC_EXIU_H__ */
