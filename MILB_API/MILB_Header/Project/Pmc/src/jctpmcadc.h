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


#ifndef __JCTPMC_ADC_H__
#define __JCTPMC_ADC_H__


#include <stdio.h>
#include <glib-object.h>


typedef union 				_IoPmcAdcAdc1 IoPmcAdcAdc1;
typedef union 				_IoPmcAdcAdc2 IoPmcAdcAdc2;
typedef union 				_IoPmcAdcAdmr IoPmcAdcAdmr;
typedef union 				_IoPmcAdcAdst IoPmcAdcAdst;
typedef union 				_IoPmcAdcAdd IoPmcAdcAdd;
typedef union 				_IoPmcAdcAdcrl IoPmcAdcAdcrl;
typedef union 				_IoPmcAdcAdcrh IoPmcAdcAdcrh;
typedef struct 				_IoPmcAdc IoPmcAdc;

/* A/D Convertor */

/* ADC1 */
union _IoPmcAdcAdc1 {
	gulong		word;
	struct {
		gulong	adcs			:8;
		gulong	strg			:1;
		gulong	xpd				:1;
		gulong	tgs				:2;
		gulong	adrst			:1;
		gulong	tsel			:1;
		gulong	xpdctl			:1;
		gulong					:17;
	}bit;
};

/* ADC2 */
union _IoPmcAdcAdc2 {
	gulong		word;
	struct {
		gulong					:12;
		gulong	stg				:3;
		gulong	etedg			:1;
		gulong					:16;
	}bit;
};

/* ADMR */
union _IoPmcAdcAdmr {
	gulong		word;
	struct {
		gulong	sts				:8;
		gulong	md				:2;
		gulong	intel			:1;
		gulong	inteh			:1;
		gulong	inte			:1;
		gulong					:19;
	}bit;
};

/* ADST */
union _IoPmcAdcAdst {
	gulong		word;
	struct {
		gulong	busy			:1;
		gulong	intl			:1;
		gulong	inth			:1;
		gulong	intf			:1;
		gulong	cs				:3;
		gulong					:25;
	}bit;
};

/* ADDx (x=0-6) */
union _IoPmcAdcAdd {
	gulong		word;
	struct {
		gulong	add				:10;
		gulong					:22;
	}bit;
};

/* ADCRL */
union _IoPmcAdcAdcrl {
	gulong		word;
	struct {
		gulong	adcrl			:10;
		gulong					:22;
	}bit;
};

/* ADCRH */
union _IoPmcAdcAdcrh {
	gulong		word;
	struct {
		gulong	adcrh			:10;
		gulong					:22;
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
	guchar					dmyPmcAdc038Fff[0x1000 - 0x038];
};


#endif /* __JCTPMC_ADC_H__ */
