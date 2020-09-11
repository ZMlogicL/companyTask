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


#ifndef __JCTPMC_HDMAC_H__
#define __JCTPMC_HDMAC_H__


#include <klib.h>


#define JCTPMC_TYPE_HDMAC		(jctpmc_hdmac_get_type())
#define JCTPMC_HDMAC(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, JctpmcHdmac))
#define JCTPMC_IS_HDMAC(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, JCTPMC_TYPE_HDMAC))


typedef union 				_IoPmcHdmacDmacr IoPmcHdmacDmacr;
typedef union 				_IoPmcHdmacDmaca IoPmcHdmacDmaca;
typedef union 				_IoPmcHdmacDmacb IoPmcHdmacDmacb;
typedef struct 				_IoPmcHdmacElement IoPmcHdmacElement;
typedef struct 				_IoPmcHdmac IoPmcHdmac;
typedef struct 				_JctpmcHdmac JctpmcHdmac;
typedef struct 				_JctpmcHdmacPrivate JctpmcHdmacPrivate;

/* HDMAC */

/* DMACR */
union _IoPmcHdmacDmacr {
	kulong		word;
	struct {
		kulong					:24;
		kulong	dh				:4;
		kulong	pr				:1;
		kulong					:1;
		kulong	ds				:1;
		kulong	de				:1;
	}bit;
};

/* DMACA */
union _IoPmcHdmacDmaca {
	kulong		word;
	struct {
		kulong	tc				:16;
		kulong	bc				:4;
		kulong	bt				:4;
		kulong	is				:5;
		kulong	st				:1;
		kulong	pb				:1;
		kulong	eb				:1;
	}bit;
};

/* DMACB */
union _IoPmcHdmacDmacb {
	kulong		word;
	struct {
		kulong					:8;
		kulong	dp				:4;
		kulong	sp				:4;
		kulong	ss				:3;
		kulong	ci				:1;
		kulong	ei				:1;
		kulong	rd				:1;
		kulong	rs				:1;
		kulong	rc				:1;
		kulong	fd				:1;
		kulong	fs				:1;
		kulong	tw				:2;
		kulong	ms				:2;
		kulong	tt				:2;
	}bit;
};

/* DMACA/DMACB/DMACSA/DMACDA (0-7ch)  */
struct _IoPmcHdmacElement {
	IoPmcHdmacDmaca	dmaca;
	IoPmcHdmacDmacb	dmacb;
	kulong				dmacsa;
	kulong				dmacda;
};

/* HDMAC */
struct _IoPmcHdmac {
	/* 1DC0_(0000 - 0003h) */
	IoPmcHdmacDmacr		dmacr;
	/* 1DC0_(0004 - 000Fh) */
	kuchar					dmyPmcHdmac0004000f[0x0010 - 0x0004];
	/* 1DC0_(0010 - 008Fh) */
	IoPmcHdmacElement	dmac[8];
	/* 1DC0_0090 - 1DCF_FFFFh */
	kuchar					dmyPmcHdmac00090Fffff[0x1DD00000 - 0x1DC00090];
};

struct _JctpmcHdmac {
	KObject parent;
};


KConstType 					jctpmc_hdmac_get_type(void);
JctpmcHdmac*		        jctpmc_hdmac_new(void);


#endif /* __JCTPMC_HDMAC_H__ */
