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


#ifndef __JCTPMC_SENSOR_IF_H__
#define __JCTPMC_SENSOR_IF_H__


#include <stdio.h>
#include <glib-object.h>


typedef union 				_IoPmcSensorIfMacroinfo IoPmcSensorIfMacroinfo;
typedef union 				_IoPmcSensorIfAllconfig IoPmcSensorIfAllconfig;
typedef union 				_IoPmcSensorIfTsReset IoPmcSensorIfTsReset;
typedef union 				_IoPmcSensorIfTsEn IoPmcSensorIfTsEn;
typedef union 				_IoPmcSensorIfTsCt IoPmcSensorIfTsCt;
typedef union 				_IoPmcSensorIfIrqout IoPmcSensorIfIrqout;
typedef union 				_IoPmcSensorIfIrqclr IoPmcSensorIfIrqclr;
typedef union 				_IoPmcSensorIfIrqmask IoPmcSensorIfIrqmask;
typedef union 				_IoPmcSensorIfIrqstatus IoPmcSensorIfIrqstatus;
typedef union 				_IoPmcSensorIfSensorIrqout IoPmcSensorIfSensorIrqout;
typedef union 				_IoPmcSensorIfSensorIrqclr IoPmcSensorIfSensorIrqclr;
typedef union 				_IoPmcSensorIfSensorIrqmask IoPmcSensorIfSensorIrqmask;
typedef union 				_IoPmcSensorIfSensorIrqstatus IoPmcSensorIfSensorIrqstatus;
typedef union 				_IoPmcSensorIfSensorTsdataValid IoPmcSensorIfSensorTsdataValid;
typedef union 				_IoPmcSensorIfHysTemp IoPmcSensorIfHysTemp;
typedef struct 				_IoPmcSensorIfSensor IoPmcSensorIfSensor;
typedef struct 				_IoPmcSensorIf IoPmcSensorIf;

/* Temperature Sensor I/F */

/* MACROINFO */
union _IoPmcSensorIfMacroinfo {
	gulong		word;
	struct {
		gulong	tsNum				:4;
		gulong						:4;
		gulong	macroRev			:8;
		gulong	macroId			:16;
	}bit;
};

/* ALLCONFIG */
union _IoPmcSensorIfAllconfig {
	gulong		word;
	struct {
		gulong	configEn			:1;
		gulong						:31;
	}bit;
};

/* TS_RESET */
union _IoPmcSensorIfTsReset {
	gulong		word;
	struct {
		gulong	reset				:1;
		gulong						:31;
	}bit;
};

/* TS_EN */
union _IoPmcSensorIfTsEn {
	gulong		word;
	struct {
		gulong	en					:1;
		gulong						:31;
	}bit;
};

/* TS_CT */
union _IoPmcSensorIfTsCt {
	gulong		word;
	struct {
		gulong	ct					:2;
		gulong						:30;
	}bit;
};

/* IRQOUT */
union _IoPmcSensorIfIrqout {
	gulong		word;
	struct {
		gulong	ts0Irqout			:1;
		gulong	tsIrqout			:15;
		gulong	allLfIrqout		:1;
		gulong	allLnIrqout		:1;
		gulong	allHnIrqout		:1;
		gulong	allHfIrqout		:1;
		gulong						:4;
		gulong	anyLfIrqout		:1;
		gulong	anyLnIrqout		:1;
		gulong	anyHnIrqout		:1;
		gulong	anyHfIrqout		:1;
		gulong						:4;
	}bit;
};

/* IRQCLR */
union _IoPmcSensorIfIrqclr {
	gulong		word;
	struct {
		gulong						:16;
		gulong	allLfIrqclr		:1;
		gulong	allLnIrqclr		:1;
		gulong	allHnIrqclr		:1;
		gulong	allHfIrqclr		:1;
		gulong						:4;
		gulong	anyLfIrqclr		:1;
		gulong	anyLnIrqclr		:1;
		gulong	anyHnIrqclr		:1;
		gulong	anyHfIrqclr		:1;
		gulong						:4;
	}bit;
};

/* IRQMASK */
union _IoPmcSensorIfIrqmask {
	gulong		word;
	struct {
		gulong	ts0Irqmask			:1;
		gulong	tsIrqmask			:15;
		gulong	allLfIrqmask		:1;
		gulong	allLnIrqmask		:1;
		gulong	allHnIrqmask		:1;
		gulong	allHfIrqmask		:1;
		gulong						:4;
		gulong	anyLfIrqmask		:1;
		gulong	anyLnIrqmask		:1;
		gulong	anyHnIrqmask		:1;
		gulong	anyHfIrqmask		:1;
		gulong						:4;
	}bit;
};

/* IRQSTATUS */
union _IoPmcSensorIfIrqstatus {
	gulong		word;
	struct {
		gulong	ts0Irqstatus		:1;
		gulong	tsIrqstatus		:15;
		gulong	allLfIrqstatus	:1;
		gulong	allLnIrqstatus	:1;
		gulong	allHnIrqstatus	:1;
		gulong	allHfIrqstatus	:1;
		gulong						:4;
		gulong	anyLfIrqstatus	:1;
		gulong	anyLnIrqstatus	:1;
		gulong	anyHnIrqstatus	:1;
		gulong	anyHfIrqstatus	:1;
		gulong						:4;
	}bit;
};

/* IRQOUT#x (x=0-4) */
union	_IoPmcSensorIfSensorIrqout {
	gulong		word;
	struct {
		gulong	lfIrqout			:1;
		gulong	lnIrqout			:1;
		gulong	hnIrqout			:1;
		gulong	hfIrqout			:1;
		gulong						:28;
	}bit;
};

/* IRQCLR#x (x=0-4) */
union	_IoPmcSensorIfSensorIrqclr {
	gulong		word;
	struct {
		gulong	lfIrqclr			:1;
		gulong	lnIrqclr			:1;
		gulong	hnIrqclr			:1;
		gulong	hfIrqclr			:1;
		gulong						:28;
	}bit;
};

/* IRQMASK#x (x=0-4) */
union	_IoPmcSensorIfSensorIrqmask {
	gulong		word;
	struct {
		gulong	lfIrqmask			:1;
		gulong	lnIrqmask			:1;
		gulong	hnIrqmask			:1;
		gulong	hfIrqmask			:1;
		gulong						:28;
	}bit;
};

/* IRQSTATUS#x (x=0-4) */
union	_IoPmcSensorIfSensorIrqstatus {
	gulong		word;
	struct {
		gulong	lfIrqstatus		:1;
		gulong	lnIrqstatus		:1;
		gulong	hnIrqstatus		:1;
		gulong	hfIrqstatus		:1;
		gulong						:28;
	}bit;
};

/* TSDATA_VALID#x (x=0-4) */
union	_IoPmcSensorIfSensorTsdataValid {
	gulong		word;
	struct {
		gulong	dataValid			:1;
		gulong						:31;
	}bit;
};

/* HYS_TEMP */
union _IoPmcSensorIfHysTemp {
	gulong		word;
	struct {
		gulong	hysTemp			:8;
		gulong						:24;
	}bit;
};

/* Register for temperature sensor #0 */
struct _IoPmcSensorIfSensor {
	guchar									dmyPmcSensorIfSensor00000f[0x010];
	IoPmcSensorIfTsReset				tsReset;
	IoPmcSensorIfTsEn					tsEn;
	IoPmcSensorIfTsCt					tsCt;
	guchar									dmyPmcSensorIfSensor01c01f[0x020 - 0x01C];
	IoPmcSensorIfSensorIrqout			irqout;
	IoPmcSensorIfSensorIrqclr			irqclr;
	IoPmcSensorIfSensorIrqmask			irqmask;
	IoPmcSensorIfSensorIrqstatus		irqstatus;
	IoPmcSensorIfSensorTsdataValid	tsdataValid;
	gulong									tsdata;
	guchar									dmyPmcSensorIfSensor03803f[0x040 - 0x038];
	gulong									hiFullTemp;
	gulong									hiNearTemp;
	gulong									loNearTemp;
	gulong									loFullTemp;
	IoPmcSensorIfHysTemp				hysTemp;
	guchar									dmyPmcSensorIfSensor05407f[0x080 - 0x054];
};

/* Temperature Sensor I/F */
struct _IoPmcSensorIf {
	/* 1DFF_(A000 - A003h)	*/
	IoPmcSensorIfMacroinfo				macroinfo;
	/* 1DFF_(A004 - A00Bh)	*/
	guchar									dmyPmcSensorIf00400b[0x00C - 0x004];
	/* 1DFF_(A00C - A00Fh)	*/
	IoPmcSensorIfAllconfig				allconfig;
	/* 1DFF_(A010 - A013h)	*/
	IoPmcSensorIfTsReset				tsReset;
	/* 1DFF_(A014 - A017h)	*/
	IoPmcSensorIfTsEn					tsEn;
	/* 1DFF_(A018 - A01Bh)	*/
	IoPmcSensorIfTsCt					tsCt;
	/* 1DFF_(A01C - A01Fh)	*/
	guchar									dmyPmcSensorIf01c01f[0x020 - 0x01C];
	/* 1DFF_(A020 - A023h)	*/
	IoPmcSensorIfIrqout					irqout;
	/* 1DFF_(A024 - A027h)	*/
	IoPmcSensorIfIrqclr					irqclr;
	/* 1DFF_(A028 - A02Bh)	*/
	IoPmcSensorIfIrqmask				irqmask;
	/* 1DFF_(A02C - A02Fh)	*/
	IoPmcSensorIfIrqstatus				irqstatus;
	/* 1DFF_(A030 - A03Fh)	*/
	guchar									dmyPmcSensorIf03003f[0x040 - 0x030];
	/* 1DFF_(A040 - A043h)	*/
	gulong									hiFullTemp;
	/* 1DFF_(A044 - A047h)	*/
	gulong									hiNearTemp;
	/* 1DFF_(A048 - A04Bh)	*/
	gulong									loNearTemp;
	/* 1DFF_(A04C - A04Fh)	*/
	gulong									loFullTemp;
	/* 1DFF_(A050 - A053h)	*/
	IoPmcSensorIfHysTemp				hysTemp;
	/* 1DFF_(A054 - A7FFh)	*/
	guchar									dmyPmcSensorIf0547ff[0x800 - 0x054];
	/* 1DFF_(A800 - A87Fh)	*/
	IoPmcSensorIfSensor					sensor;
	/* 1DFF_(A880 - AFFFh)	*/
	guchar									dmyPmcSensorIf880Fff[0x1000 - 0x880];
};


#endif /* __JCTPMC_SENSOR_IF_H__ */
