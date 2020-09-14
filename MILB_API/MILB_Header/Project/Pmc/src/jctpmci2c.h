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


#ifndef __JCTPMC_I2C_H__
#define __JCTPMC_I2C_H__


#include <stdio.h>
#include <glib-object.h>


typedef union 				_IoPmcI2cSdat IoPmcI2cSdat;
typedef union 				_IoPmcI2cSt IoPmcI2cSt;
typedef union	 			_IoPmcI2cCst IoPmcI2cCst;
typedef union 				_IoPmcI2cCtl1 IoPmcI2cCtl1;
typedef union 				_IoPmcI2cAddr IoPmcI2cAddr;
typedef union 				_IoPmcI2cCtl2 IoPmcI2cCtl2;
typedef union 				_IoPmcI2cTopr IoPmcI2cTopr;
typedef union 				_IoPmcI2cCtl3 IoPmcI2cCtl3;
typedef struct 				_IoPmcI2c IoPmcI2c;

/* I2C */
union _IoPmcI2cSdat {
	gulong		word;
	struct {
		gulong	data		:8;
		gulong				:24;
	}bit;
};

union _IoPmcI2cSt {
	gulong		word;
	struct {
		gulong	mode 		:5;
		gulong				:2;
		unsigned long	int 		:1;
		gulong				:24;
	}bit;
};

union _IoPmcI2cCst {
	gulong		word;
	struct {
		gulong	bb			:1;
		gulong	tocdiv		:2;
		gulong	terr		:1;
		gulong	tsda		:1;
		gulong	tgscl		:1;
		gulong	pecnext		:1;
		gulong	pecfault	:1;
		gulong				:24;
	}bit;
};

union _IoPmcI2cCtl1 {
	gulong		word;
	struct {
		gulong	start		:1;
		gulong	stop		:1;
		gulong	inten		:1;
		gulong				:1;
		gulong	ack			:1;
		gulong	gcmen		:1;
		gulong	smbare		:1;
		gulong	clrst		:1;
		gulong				:24;
	}bit;
};

union _IoPmcI2cAddr {
	gulong		word;
	struct {
		gulong	addr		:7;
		gulong	saen		:1;
		gulong				:24;
	}bit;
};

union _IoPmcI2cCtl2 {
	gulong		word;
	struct {
		gulong	enable		:1;
		gulong	sclfrq		:7;
		gulong				:24;
	}bit;
};

union _IoPmcI2cTopr {
	gulong		word;
	struct {
		gulong	topr 		:8;
		gulong				:24;
	}bit;
};

union _IoPmcI2cCtl3 {
	gulong		word;
	struct {
		gulong	s10adr		:3;
		gulong	s10en		:1;
		gulong	hscdiv 		:4;
		gulong				:24;
	}bit;
};

/* UART */
struct _IoPmcI2c {
	/* 1DFF_(7000 - 7003h) */
	IoPmcI2cSdat		sdat;
	/* 1DFF_(7004 - 7007h) */
	IoPmcI2cSt		st;
	/* 1DFF_(7008 - 700Bh) */
	IoPmcI2cCst		cst;
	/* 1DFF_(700C - 700Fh) */
	IoPmcI2cCtl1		ctl1;
	/* 1DFF_(7010 - 7013h) */
	IoPmcI2cAddr		addr;
	/* 1DFF_(7014 - 7017h) */
	IoPmcI2cCtl2		ctl2;
	/* 1DFF_(7018 - 701Bh) */
	IoPmcI2cTopr		topr;
	/* 1DFF_(701C - 701Fh) */
	IoPmcI2cCtl3		ctl3;
	/* 1DFF_(7020 - 73FFh) */
	guchar		dmyPmcI2c702073ff[0x7400-0x7020];
};


#endif /* __JCTPMC_I2C_H__ */
