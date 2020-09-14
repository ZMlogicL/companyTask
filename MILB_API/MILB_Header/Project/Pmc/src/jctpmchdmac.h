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


#ifndef __JCTPMC_HDMAC_H__
#define __JCTPMC_HDMAC_H__


#include <stdio.h>
#include <glib-object.h>


typedef union 				_IoPmcHdmacDmacr IoPmcHdmacDmacr;
typedef union 				_IoPmcHdmacDmaca IoPmcHdmacDmaca;
typedef union 				_IoPmcHdmacDmacb IoPmcHdmacDmacb;
typedef struct 				_IoPmcHdmacElement IoPmcHdmacElement;
typedef struct 				_IoPmcHdmac IoPmcHdmac;

/* HDMAC */

/* DMACR */
union _IoPmcHdmacDmacr {
	gulong		word;
	struct {
		gulong					:24;
		gulong	dh				:4;
		gulong	pr				:1;
		gulong					:1;
		gulong	ds				:1;
		gulong	de				:1;
	}bit;
};

/* DMACA */
union _IoPmcHdmacDmaca {
	gulong		word;
	struct {
		gulong	tc				:16;
		gulong	bc				:4;
		gulong	bt				:4;
		gulong	is				:5;
		gulong	st				:1;
		gulong	pb				:1;
		gulong	eb				:1;
	}bit;
};

/* DMACB */
union _IoPmcHdmacDmacb {
	gulong		word;
	struct {
		gulong					:8;
		gulong	dp				:4;
		gulong	sp				:4;
		gulong	ss				:3;
		gulong	ci				:1;
		gulong	ei				:1;
		gulong	rd				:1;
		gulong	rs				:1;
		gulong	rc				:1;
		gulong	fd				:1;
		gulong	fs				:1;
		gulong	tw				:2;
		gulong	ms				:2;
		gulong	tt				:2;
	}bit;
};

/* DMACA/DMACB/DMACSA/DMACDA (0-7ch)  */
struct _IoPmcHdmacElement {
	IoPmcHdmacDmaca	dmaca;
	IoPmcHdmacDmacb	dmacb;
	gulong				dmacsa;
	gulong				dmacda;
};

/* HDMAC */
struct _IoPmcHdmac {
	/* 1DC0_(0000 - 0003h) */
	IoPmcHdmacDmacr		dmacr;
	/* 1DC0_(0004 - 000Fh) */
	guchar					dmyPmcHdmac0004000f[0x0010 - 0x0004];
	/* 1DC0_(0010 - 008Fh) */
	IoPmcHdmacElement	dmac[8];
	/* 1DC0_0090 - 1DCF_FFFFh */
	guchar					dmyPmcHdmac00090Fffff[0x1DD00000 - 0x1DC00090];
};


#endif /* __JCTPMC_HDMAC_H__ */
