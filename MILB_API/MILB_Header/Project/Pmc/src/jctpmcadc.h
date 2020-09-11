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


#ifndef __JCTPMC_ADC_H__
#define __JCTPMC_ADC_H__


#include <klib.h>


#define JCTPMC_TYPE_ADC			(jctpmc_adc_get_type())
#define JCTPMC_ADC(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, JctpmcAdc))
#define JCTPMC_IS_ADC(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, JCTPMC_TYPE_ADC))


typedef union 				_IoPmcAdcAdc1 IoPmcAdcAdc1;
typedef union 				_IoPmcAdcAdc2 IoPmcAdcAdc2;
typedef union 				_IoPmcAdcAdmr IoPmcAdcAdmr;
typedef union 				_IoPmcAdcAdst IoPmcAdcAdst;
typedef union 				_IoPmcAdcAdd IoPmcAdcAdd;
typedef union 				_IoPmcAdcAdcrl IoPmcAdcAdcrl;
typedef union 				_IoPmcAdcAdcrh IoPmcAdcAdcrh;
typedef struct 				_IoPmcAdc IoPmcAdc;
typedef struct 				_JctpmcAdc JctpmcAdc;
typedef struct 				_JctpmcAdcPrivate JctpmcAdcPrivate;

/* A/D Convertor */

/* ADC1 */
union _IoPmcAdcAdc1 {
	kulong		word;
	struct {
		kulong	adcs			:8;
		kulong	strg			:1;
		kulong	xpd				:1;
		kulong	tgs				:2;
		kulong	adrst			:1;
		kulong	tsel			:1;
		kulong	xpdctl			:1;
		kulong					:17;
	}bit;
};

/* ADC2 */
union _IoPmcAdcAdc2 {
	kulong		word;
	struct {
		kulong					:12;
		kulong	stg				:3;
		kulong	etedg			:1;
		kulong					:16;
	}bit;
};

/* ADMR */
union _IoPmcAdcAdmr {
	kulong		word;
	struct {
		kulong	sts				:8;
		kulong	md				:2;
		kulong	intel			:1;
		kulong	inteh			:1;
		kulong	inte			:1;
		kulong					:19;
	}bit;
};

/* ADST */
union _IoPmcAdcAdst {
	kulong		word;
	struct {
		kulong	busy			:1;
		kulong	intl			:1;
		kulong	inth			:1;
		kulong	intf			:1;
		kulong	cs				:3;
		kulong					:25;
	}bit;
};

/* ADDx (x=0-6) */
union _IoPmcAdcAdd {
	kulong		word;
	struct {
		kulong	add				:10;
		kulong					:22;
	}bit;
};

/* ADCRL */
union _IoPmcAdcAdcrl {
	kulong		word;
	struct {
		kulong	adcrl			:10;
		kulong					:22;
	}bit;
};

/* ADCRH */
union _IoPmcAdcAdcrh {
	kulong		word;
	struct {
		kulong	adcrh			:10;
		kulong					:22;
	}bit;
};

/* A/D Convertor */
struct _IoPmcAdc {
	/* 1DFF_(5000 - 5003h)	*/
	IoPmcAdcAdc1			adc1;
	/* 1DFF_(5004 - 5007h)	*/
	IoPmcAdcAdc2			adc2;
	/* 1DFF_(5008 - 500Bh)	*/
	IoPmcAdcAdmr			admr;
	/* 1DFF_(500C - 500Fh)	*/
	IoPmcAdcAdst			adst;
	/* 1DFF_(5010 - 502Fh)	*/
	IoPmcAdcAdd			add[8];
	/* 1DFF_(5030 - 5033h)	*/
	IoPmcAdcAdcrl		adcrl;
	/* 1DFF_(5034 - 5037h)	*/
	IoPmcAdcAdcrh		adcrh;
	/* 1DFF_(5038 - 5FFFh)	*/
	kuchar					dmyPmcAdc038Fff[0x1000 - 0x038];
};

struct _JctpmcAdc {
	KObject parent;
};


KConstType 			jctpmc_adc_get_type(void);
JctpmcAdc*		        jctpmc_adc_new(void);


#endif /* __JCTPMC_ADC_H__ */
