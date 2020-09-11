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


#ifndef __JCTPMC_SENSOR_IF_H__
#define __JCTPMC_SENSOR_IF_H__


#include <klib.h>


#define JCTPMC_TYPE_SENSOR_IF			(jctpmc_sensor_if_get_type())
#define JCTPMC_SENSOR_IF(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, JctpmcSensorIf))
#define JCTPMC_IS_SENSOR_IF(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, JCTPMC_TYPE_SENSOR_IF))


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
typedef struct 				_JctpmcSensorIf JctpmcSensorIf;
typedef struct 				_JctpmcSensorIfPrivate JctpmcSensorIfPrivate;

/* Temperature Sensor I/F */

/* MACROINFO */
union _IoPmcSensorIfMacroinfo {
	kulong		word;
	struct {
		kulong	tsNum				:4;
		kulong						:4;
		kulong	macroRev			:8;
		kulong	macroId			:16;
	}bit;
};

/* ALLCONFIG */
union _IoPmcSensorIfAllconfig {
	kulong		word;
	struct {
		kulong	configEn			:1;
		kulong						:31;
	}bit;
};

/* TS_RESET */
union _IoPmcSensorIfTsReset {
	kulong		word;
	struct {
		kulong	reset				:1;
		kulong						:31;
	}bit;
};

/* TS_EN */
union _IoPmcSensorIfTsEn {
	kulong		word;
	struct {
		kulong	en					:1;
		kulong						:31;
	}bit;
};

/* TS_CT */
union _IoPmcSensorIfTsCt {
	kulong		word;
	struct {
		kulong	ct					:2;
		kulong						:30;
	}bit;
};

/* IRQOUT */
union _IoPmcSensorIfIrqout {
	kulong		word;
	struct {
		kulong	ts0Irqout			:1;
		kulong	tsIrqout			:15;
		kulong	allLfIrqout		:1;
		kulong	allLnIrqout		:1;
		kulong	allHnIrqout		:1;
		kulong	allHfIrqout		:1;
		kulong						:4;
		kulong	anyLfIrqout		:1;
		kulong	anyLnIrqout		:1;
		kulong	anyHnIrqout		:1;
		kulong	anyHfIrqout		:1;
		kulong						:4;
	}bit;
};

/* IRQCLR */
union _IoPmcSensorIfIrqclr {
	kulong		word;
	struct {
		kulong						:16;
		kulong	allLfIrqclr		:1;
		kulong	allLnIrqclr		:1;
		kulong	allHnIrqclr		:1;
		kulong	allHfIrqclr		:1;
		kulong						:4;
		kulong	anyLfIrqclr		:1;
		kulong	anyLnIrqclr		:1;
		kulong	anyHnIrqclr		:1;
		kulong	anyHfIrqclr		:1;
		kulong						:4;
	}bit;
};

/* IRQMASK */
union _IoPmcSensorIfIrqmask {
	kulong		word;
	struct {
		kulong	ts0Irqmask			:1;
		kulong	tsIrqmask			:15;
		kulong	allLfIrqmask		:1;
		kulong	allLnIrqmask		:1;
		kulong	allHnIrqmask		:1;
		kulong	allHfIrqmask		:1;
		kulong						:4;
		kulong	anyLfIrqmask		:1;
		kulong	anyLnIrqmask		:1;
		kulong	anyHnIrqmask		:1;
		kulong	anyHfIrqmask		:1;
		kulong						:4;
	}bit;
};

/* IRQSTATUS */
union _IoPmcSensorIfIrqstatus {
	kulong		word;
	struct {
		kulong	ts0Irqstatus		:1;
		kulong	tsIrqstatus		:15;
		kulong	allLfIrqstatus	:1;
		kulong	allLnIrqstatus	:1;
		kulong	allHnIrqstatus	:1;
		kulong	allHfIrqstatus	:1;
		kulong						:4;
		kulong	anyLfIrqstatus	:1;
		kulong	anyLnIrqstatus	:1;
		kulong	anyHnIrqstatus	:1;
		kulong	anyHfIrqstatus	:1;
		kulong						:4;
	}bit;
};

/* IRQOUT#x (x=0-4) */
union	_IoPmcSensorIfSensorIrqout {
	kulong		word;
	struct {
		kulong	lfIrqout			:1;
		kulong	lnIrqout			:1;
		kulong	hnIrqout			:1;
		kulong	hfIrqout			:1;
		kulong						:28;
	}bit;
};

/* IRQCLR#x (x=0-4) */
union	_IoPmcSensorIfSensorIrqclr {
	kulong		word;
	struct {
		kulong	lfIrqclr			:1;
		kulong	lnIrqclr			:1;
		kulong	hnIrqclr			:1;
		kulong	hfIrqclr			:1;
		kulong						:28;
	}bit;
};

/* IRQMASK#x (x=0-4) */
union	_IoPmcSensorIfSensorIrqmask {
	kulong		word;
	struct {
		kulong	lfIrqmask			:1;
		kulong	lnIrqmask			:1;
		kulong	hnIrqmask			:1;
		kulong	hfIrqmask			:1;
		kulong						:28;
	}bit;
};

/* IRQSTATUS#x (x=0-4) */
union	_IoPmcSensorIfSensorIrqstatus {
	kulong		word;
	struct {
		kulong	lfIrqstatus		:1;
		kulong	lnIrqstatus		:1;
		kulong	hnIrqstatus		:1;
		kulong	hfIrqstatus		:1;
		kulong						:28;
	}bit;
};

/* TSDATA_VALID#x (x=0-4) */
union	_IoPmcSensorIfSensorTsdataValid {
	kulong		word;
	struct {
		kulong	dataValid			:1;
		kulong						:31;
	}bit;
};

/* HYS_TEMP */
union _IoPmcSensorIfHysTemp {
	kulong		word;
	struct {
		kulong	hysTemp			:8;
		kulong						:24;
	}bit;
};

/* Register for temperature sensor #0 */
struct _IoPmcSensorIfSensor {
	kuchar									dmyPmcSensorIfSensor00000f[0x010];
	IoPmcSensorIfTsReset				tsReset;
	IoPmcSensorIfTsEn					tsEn;
	IoPmcSensorIfTsCt					tsCt;
	kuchar									dmyPmcSensorIfSensor01c01f[0x020 - 0x01C];
	IoPmcSensorIfSensorIrqout			irqout;
	IoPmcSensorIfSensorIrqclr			irqclr;
	IoPmcSensorIfSensorIrqmask			irqmask;
	IoPmcSensorIfSensorIrqstatus		irqstatus;
	IoPmcSensorIfSensorTsdataValid	tsdataValid;
	kulong									tsdata;
	kuchar									dmyPmcSensorIfSensor03803f[0x040 - 0x038];
	kulong									hiFullTemp;
	kulong									hiNearTemp;
	kulong									loNearTemp;
	kulong									loFullTemp;
	IoPmcSensorIfHysTemp				hysTemp;
	kuchar									dmyPmcSensorIfSensor05407f[0x080 - 0x054];
};

/* Temperature Sensor I/F */
struct _IoPmcSensorIf {
	/* 1DFF_(A000 - A003h)	*/
	IoPmcSensorIfMacroinfo				macroinfo;
	/* 1DFF_(A004 - A00Bh)	*/
	kuchar									dmyPmcSensorIf00400b[0x00C - 0x004];
	/* 1DFF_(A00C - A00Fh)	*/
	IoPmcSensorIfAllconfig				allconfig;
	/* 1DFF_(A010 - A013h)	*/
	IoPmcSensorIfTsReset				tsReset;
	/* 1DFF_(A014 - A017h)	*/
	IoPmcSensorIfTsEn					tsEn;
	/* 1DFF_(A018 - A01Bh)	*/
	IoPmcSensorIfTsCt					tsCt;
	/* 1DFF_(A01C - A01Fh)	*/
	kuchar									dmyPmcSensorIf01c01f[0x020 - 0x01C];
	/* 1DFF_(A020 - A023h)	*/
	IoPmcSensorIfIrqout					irqout;
	/* 1DFF_(A024 - A027h)	*/
	IoPmcSensorIfIrqclr					irqclr;
	/* 1DFF_(A028 - A02Bh)	*/
	IoPmcSensorIfIrqmask				irqmask;
	/* 1DFF_(A02C - A02Fh)	*/
	IoPmcSensorIfIrqstatus				irqstatus;
	/* 1DFF_(A030 - A03Fh)	*/
	kuchar									dmyPmcSensorIf03003f[0x040 - 0x030];
	/* 1DFF_(A040 - A043h)	*/
	kulong									hiFullTemp;
	/* 1DFF_(A044 - A047h)	*/
	kulong									hiNearTemp;
	/* 1DFF_(A048 - A04Bh)	*/
	kulong									loNearTemp;
	/* 1DFF_(A04C - A04Fh)	*/
	kulong									loFullTemp;
	/* 1DFF_(A050 - A053h)	*/
	IoPmcSensorIfHysTemp				hysTemp;
	/* 1DFF_(A054 - A7FFh)	*/
	kuchar									dmyPmcSensorIf0547ff[0x800 - 0x054];
	/* 1DFF_(A800 - A87Fh)	*/
	IoPmcSensorIfSensor					sensor;
	/* 1DFF_(A880 - AFFFh)	*/
	kuchar									dmyPmcSensorIf880Fff[0x1000 - 0x880];
};

struct _JctpmcSensorIf {
	KObject parent;
};


KConstType 					jctpmc_sensor_if_get_type(void);
JctpmcSensorIf*		        jctpmc_sensor_if_new(void);


#endif /* __JCTPMC_SENSOR_IF_H__ */
