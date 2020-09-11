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


#ifndef __JCTPMC_I2C_H__
#define __JCTPMC_I2C_H__


#include <klib.h>


#define JCTPMC_TYPE_I2C		(jctpmc_i2c_get_type())
#define JCTPMC_I2C(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, JctpmcI2c))
#define JCTPMC_IS_I2C(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, JCTPMC_TYPE_I2C))


typedef union 				_IoPmcI2cSdat IoPmcI2cSdat;
typedef union 				_IoPmcI2cSt IoPmcI2cSt;
typedef union	 			_IoPmcI2cCst IoPmcI2cCst;
typedef union 				_IoPmcI2cCtl1 IoPmcI2cCtl1;
typedef union 				_IoPmcI2cAddr IoPmcI2cAddr;
typedef union 				_IoPmcI2cCtl2 IoPmcI2cCtl2;
typedef union 				_IoPmcI2cTopr IoPmcI2cTopr;
typedef union 				_IoPmcI2cCtl3 IoPmcI2cCtl3;
typedef struct 				_IoPmcI2c IoPmcI2c;
typedef struct 				_JctpmcI2c JctpmcI2c;
typedef struct 				_JctpmcI2cPrivate JctpmcI2cPrivate;

/* I2C */
union _IoPmcI2cSdat {
	kulong		word;
	struct {
		kulong	data		:8;
		kulong				:24;
	}bit;
};

union _IoPmcI2cSt {
	kulong		word;
	struct {
		kulong	mode 		:5;
		kulong				:2;
		unsigned long	int 		:1;
		kulong				:24;
	}bit;
};

union _IoPmcI2cCst {
	kulong		word;
	struct {
		kulong	bb			:1;
		kulong	tocdiv		:2;
		kulong	terr		:1;
		kulong	tsda		:1;
		kulong	tgscl		:1;
		kulong	pecnext		:1;
		kulong	pecfault	:1;
		kulong				:24;
	}bit;
};

union _IoPmcI2cCtl1 {
	kulong		word;
	struct {
		kulong	start		:1;
		kulong	stop		:1;
		kulong	inten		:1;
		kulong				:1;
		kulong	ack			:1;
		kulong	gcmen		:1;
		kulong	smbare		:1;
		kulong	clrst		:1;
		kulong				:24;
	}bit;
};

union _IoPmcI2cAddr {
	kulong		word;
	struct {
		kulong	addr		:7;
		kulong	saen		:1;
		kulong				:24;
	}bit;
};

union _IoPmcI2cCtl2 {
	kulong		word;
	struct {
		kulong	enable		:1;
		kulong	sclfrq		:7;
		kulong				:24;
	}bit;
};

union _IoPmcI2cTopr {
	kulong		word;
	struct {
		kulong	topr 		:8;
		kulong				:24;
	}bit;
};

union _IoPmcI2cCtl3 {
	kulong		word;
	struct {
		kulong	s10adr		:3;
		kulong	s10en		:1;
		kulong	hscdiv 		:4;
		kulong				:24;
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
	kuchar		dmyPmcI2c702073ff[0x7400-0x7020];
};

struct _JctpmcI2c {
	KObject parent;
};


KConstType 			jctpmc_i2c_get_type(void);
JctpmcI2c*		        jctpmc_i2c_new(void);


#endif /* __JCTPMC_I2C_H__ */
