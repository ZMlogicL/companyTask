/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-11
*@author              :于孟孟
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年06月开始开发
*/
/**
 * @file		jdsltm1altm.h
 * @brief		Definition JDSLTM1A Macro I/O register
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2016 Socionext Inc.</I></B>
 */


#ifndef __JDSLTM1A_LTM_H__
#define __JDSLTM1A_LTM_H__


typedef union _IoLtmChLtmLtmsr  				IoLtmChLtmLtmsr;
typedef union _IoLtmChLtmLsramen   			IoLtmChLtmLsramen;
typedef union _IoLtmChLtmLtrg  					IoLtmChLtmLtrg;
typedef union _IoLtmChLtmLfrstp  				IoLtmChLtmLfrstp;
typedef union _IoLtmChLtmLparmsk  			IoLtmChLtmLparmsk;
typedef union _IoLtmChLtmLint0  					IoLtmChLtmLint0;
typedef union _IoLtmChLtmLint1  					IoLtmChLtmLint1;
typedef union _IoLtmChLtmLlintlv  				IoLtmChLtmLlintlv;
typedef union _IoLtmChLtmLaxictlr1  			IoLtmChLtmLaxictlr1;
typedef union _IoLtmChLtmLaxictlr2 			IoLtmChLtmLaxictlr2;
typedef union _IoLtmChLtmLaxirerr  				IoLtmChLtmLaxirerr;
typedef union _IoLtmChLtmLaxictlw  			IoLtmChLtmLaxictlw;
typedef union _IoLtmChLtmLaxiwerr  			IoLtmChLtmLaxiwerr;
typedef union _IoLtmChLtmLaxibsiz  			IoLtmChLtmLaxibsiz;
typedef union _IoLtmChLtmAxirsel 				IoLtmChLtmAxirsel;
typedef union _IoLtmChLtmLsdrhszr2 			IoLtmChLtmLsdrhszr2;
typedef union _IoLtmChLtmLsdrdefr2  			IoLtmChLtmLsdrdefr2;
typedef union _IoLtmChLtmLsdrvszr2  			IoLtmChLtmLsdrvszr2;
typedef union _IoLtmChLtmLsdradr2r  			IoLtmChLtmLsdradr2r;
typedef union _IoLtmChLtmLsdradr2g 			IoLtmChLtmLsdradr2g;
typedef union _IoLtmChLtmLsdradr2b  			IoLtmChLtmLsdradr2b;
typedef union _IoLtmChLtmLsdrhszr3  			IoLtmChLtmLsdrhszr3;
typedef union _IoLtmChLtmLsdrdefr3  			IoLtmChLtmLsdrdefr3;
typedef union _IoLtmChLtmLsdrvszr3  			IoLtmChLtmLsdrvszr3;
typedef union _IoLtmChLtmLsdradr3  			IoLtmChLtmLsdradr3;
typedef union _IoLtmChLtmLsdrdefr4  			IoLtmChLtmLsdrdefr4;
typedef union _IoLtmChLtmLsdradr4 			IoLtmChLtmLsdradr4;
typedef union _IoLtmChLtmLsdrofs  				IoLtmChLtmLsdrofs;
typedef union _IoLtmChLtmLsdwadr  			IoLtmChLtmLsdwadr;
typedef union _IoLtmChLtmLsdwdefr  			IoLtmChLtmLsdwdefr;
typedef union _IoLtmChLtmLsdwadg  			IoLtmChLtmLsdwadg;
typedef union _IoLtmChLtmLsdwdefg  			IoLtmChLtmLsdwdefg;
typedef union _IoLtmChLtmLsdwadb  			IoLtmChLtmLsdwadb;
typedef union _IoLtmChLtmLsdwdefb  			IoLtmChLtmLsdwdefb;
typedef union _IoLtmChLtmLioctl  				IoLtmChLtmLioctl;
typedef union _IoLtmChLtmLhsta  					IoLtmChLtmLhsta;
typedef union _IoLtmChLtmLhpit  					IoLtmChLtmLhpit;
typedef union _IoLtmChLtmLvsta  					IoLtmChLtmLvsta;
typedef union _IoLtmChLtmLvpit  					IoLtmChLtmLvpit;
typedef union _IoLtmChLtmNlvthof  				IoLtmChLtmNlvthof;
typedef union _IoLtmChLtmPlvthof  				IoLtmChLtmPlvthof;
typedef union _IoLtmChLtmLyshadow  			IoLtmChLtmLyshadow;
typedef union _IoLtmChLtmLyhighlight 		IoLtmChLtmLyhighlight;
typedef union _IoLtmChLtmRcgmd  				IoLtmChLtmRcgmd;
typedef union _IoLtmChLtmRcgtbl  				IoLtmChLtmRcgtbl;
typedef union _IoLtmChLtmBldyrt  				IoLtmChLtmBldyrt;
typedef union _IoLtmChLtmBldof1  				IoLtmChLtmBldof1;
typedef union _IoLtmChLtmBldof2  				IoLtmChLtmBldof2;
typedef union _IoLtmChLtmBldof3  				IoLtmChLtmBldof3;
typedef union _IoLtmChLtmBldof4  				IoLtmChLtmBldof4;
typedef struct _IoLtmChLtmBldof  					IoLtmChLtmBldof;
typedef union _IoLtmChLtmBldga1  				IoLtmChLtmBldga1;
typedef union _IoLtmChLtmBldga2 				IoLtmChLtmBldga2;
typedef union _IoLtmChLtmBldga3  				IoLtmChLtmBldga3;
typedef union _IoLtmChLtmBldga4  				IoLtmChLtmBldga4;
typedef struct _IoLtmChLtmBldga  				IoLtmChLtmBldga;
typedef union _IoLtmChLtmBldbd1   			IoLtmChLtmBldbd1;
typedef union _IoLtmChLtmBldbd2  				IoLtmChLtmBldbd2;
typedef union _IoLtmChLtmBldbd3  				IoLtmChLtmBldbd3;
typedef union _IoLtmChLtmBldbd4  				IoLtmChLtmBldbd4;
typedef struct _IoLtmChLtmBldbd  				IoLtmChLtmBldbd;
typedef union _IoLtmChLtmLtmmd  				IoLtmChLtmLtmmd;
typedef union _IoLtmChLtmCgof1  				IoLtmChLtmCgof1;
typedef union _IoLtmChLtmCgof2  				IoLtmChLtmCgof2;
typedef union _IoLtmChLtmCgof3  				IoLtmChLtmCgof3;
typedef union _IoLtmChLtmCgof4  				IoLtmChLtmCgof4;
typedef struct _IoLtmChLtmCgof  					IoLtmChLtmCgof;
typedef union _IoLtmChLtmCgga1  				IoLtmChLtmCgga1;
typedef union _IoLtmChLtmCgga2 				IoLtmChLtmCgga2;
typedef union _IoLtmChLtmCgga3  				IoLtmChLtmCgga3;
typedef union _IoLtmChLtmCgga4  				IoLtmChLtmCgga4;
typedef struct _IoLtmChLtmCgga  					IoLtmChLtmCgga;
typedef union _IoLtmChLtmCgbd1  				IoLtmChLtmCgbd1;
typedef union _IoLtmChLtmCgbd2  				IoLtmChLtmCgbd2;
typedef union _IoLtmChLtmCgbd3 				IoLtmChLtmCgbd3;
typedef union _IoLtmChLtmCgbd4  				IoLtmChLtmCgbd4;
typedef struct _IoLtmChLtmCgbd  					IoLtmChLtmCgbd;
typedef union _IoLtmChLtmLylctl  					IoLtmChLtmLylctl;
typedef union _IoLtmChLtmLylog0ep0  		IoLtmChLtmLylog0ep0;
typedef union _IoLtmChLtmLylog0ep1  		IoLtmChLtmLylog0ep1;
typedef union _IoLtmChLtmLylog1ep0  		IoLtmChLtmLylog1ep0;
typedef union _IoLtmChLtmLylog1ep1  		IoLtmChLtmLylog1ep1;
typedef struct _IoLtmChLtm  							IoLtmChLtm;


/*	structure of ltmsr	(2841_3800h)	*/
union _IoLtmChLtmLtmsr{
	unsigned long		word;
	struct {
		unsigned long	sr		:1;
		unsigned long			:31;
	}bit;
};

/*	structure of lsramen	(2841_3804h)	*/
union _IoLtmChLtmLsramen{
	unsigned long		word;
	struct {
		unsigned long	sramaen		:1;
		unsigned long						:3;
		unsigned long	rmaenrgb	:1;
		unsigned long	rmaenyn		:1;
		unsigned long						:26;
	}bit;
};

/*	structure of ltrg	(2841_3808h)	*/
union _IoLtmChLtmLtrg{
	unsigned long		word;
	struct {
		unsigned long	trg	:2;
		unsigned long			:30;
	}bit;
};

/*	structure of lfrstp (2841_380Ch)	*/
union _IoLtmChLtmLfrstp{
	unsigned long		word;
	struct {
		unsigned long	frstp	:1;
		unsigned long			:31;
	}bit;
};

/*	structure of lparmsk	(2841_3810h)	*/
union _IoLtmChLtmLparmsk{
	unsigned long		word;
	struct {
		unsigned long	parmsk	:1;
		unsigned long					:31;
	}bit;
};

/*	structure of lint0	(2841_3818h)	*/
union _IoLtmChLtmLint0{
	unsigned long		word;
	struct {
		unsigned long	finen		:1;
		unsigned long					:3;
		unsigned long	exipen		:1;
		unsigned long					:7;
		unsigned long	lcnten		:1;
		unsigned long					:7;
		unsigned long	axreen		:1;
		unsigned long	axween	:1;
		unsigned long					:3;
		unsigned long	rameen	:1;
		unsigned long					:6;
	}bit;
};

/*	structure of lint1	(2841_381Ch)	*/
union _IoLtmChLtmLint1{
	unsigned long		word;
	struct {
		unsigned long	__finfl		:1;
		unsigned long					:3;
		unsigned long	__exipfl	:1;
		unsigned long					:7;
		unsigned long	__lcntfl		:1;
		unsigned long					:7;
		unsigned long	__axrefl	:1;
		unsigned long	__axwefl	:1;
		unsigned long					:3;
		unsigned long	__ramefl	:1;
		unsigned long					:6;
	}bit;
};

/*	structure of llintlv	(2841_3820h)	*/
union _IoLtmChLtmLlintlv{
	unsigned long		word;
	struct {
		unsigned long	lintlv	:14;
		unsigned long				:18;
	}bit;
};

/*	structure of laxictlr1	(2841_3824h)	*/
union _IoLtmChLtmLaxictlr1{
	unsigned long		word;
	struct {
		unsigned long	arcacheR	:4;
		unsigned long	arprotR	:3;
		unsigned long					:1;
		unsigned long	arcacheG	:4;
		unsigned long	arprotG	:3;
		unsigned long					:1;
		unsigned long	arcacheB	:4;
		unsigned long	arprotB	:3;
		unsigned long					:9;
	}bit;
};

/*	structure of laxictlr2	(2841_3828h)	*/
union _IoLtmChLtmLaxictlr2{
	unsigned long		word;
	struct {
		unsigned long	arcacheYp	:4;
		unsigned long	arprotYp		:3;
		unsigned long						:1;
		unsigned long	arcacheYn	:4;
		unsigned long	arprotYn		:3;
		unsigned long						:17;
	}bit;
};

/*	structure of laxirerr	(2841_382Ch)	*/
union _IoLtmChLtmLaxirerr{
	unsigned long		word;
	struct {
		unsigned long	rrespR		:2;
		unsigned long	rrespG		:2;
		unsigned long	rrespB		:2;
		unsigned long					:2;
		unsigned long	rrespYp	:2;
		unsigned long	rrespYn	:2;
		unsigned long					:20;
	}bit;
};

/*	structure of laxictlw	(2841_3830h)	*/
union _IoLtmChLtmLaxictlw{
	unsigned long		word;
	struct {
		unsigned long	awcacheR	:4;
		unsigned long	awprotR		:3;
		unsigned long						:1;
		unsigned long	awcacheG	:4;
		unsigned long	awprotG		:3;
		unsigned long						:1;
		unsigned long	awcacheB	:4;
		unsigned long	awprotB		:3;
		unsigned long						:9;
	}bit;
};

/*	structure of laxiwerr	(2841_3834h)	*/
union _IoLtmChLtmLaxiwerr{
	unsigned long		word;
	struct {
		unsigned long	wrespR	:2;
		unsigned long	wrespG	:2;
		unsigned long	wrespB	:2;
		unsigned long					:26;
	}bit;
};

/*	structure of laxibsiz	(2841_3838h)	*/
union _IoLtmChLtmLaxibsiz{
	unsigned long		word;
	struct {
		unsigned long	burstrr			:1;
		unsigned long	burstrg		:1;
		unsigned long	burstrb		:1;
		unsigned long	burstryp		:1;
		unsigned long	burstryn		:1;
		unsigned long						:3;
		unsigned long	burstwr		:1;
		unsigned long	burstwg		:1;
		unsigned long	burstwb		:1;
		unsigned long						:5;
		unsigned long	wstbmskr	:1;
		unsigned long	wstbmskg	:1;
		unsigned long	wstbmskb	:1;
		unsigned long						:13;
	}bit;
};

/*	structure of axirsel	(2841_383Ch)	*/
union _IoLtmChLtmAxirsel{
	unsigned long		word;
	struct {
		unsigned long	axirsel1	:1;
		unsigned long	axirsel2	:1;
		unsigned long					:30;
	}bit;
};

/*	structure of lsdrhszr2	(2841_3880h)	*/
union _IoLtmChLtmLsdrhszr2{
	unsigned long		word;
	struct {
		unsigned long	sdrhszr2	:12;
		unsigned long					:20;
	}bit;
};

/*	structure of lsdrdefr2	(2841_3884h)	*/
union _IoLtmChLtmLsdrdefr2{
	unsigned long		word;
	struct {
		unsigned long	sdrdefr2	:16;
		unsigned long					:16;
	}bit;
};

/*	structure of lsdrvszr2	(2841_3888h)	*/
union _IoLtmChLtmLsdrvszr2{
	unsigned long		word;
	struct {
		unsigned long	sdrvszr2	:14;
		unsigned long					:18;
	}bit;
};

/*	structure of lsdradr2r	(2841_388Ch)	*/
union _IoLtmChLtmLsdradr2r{
	unsigned long		word;
	struct {
		unsigned long	sdradr2r	:32;
	}bit;
};

/*	structure of lsdradr2g	(2841_3890h)	*/
union _IoLtmChLtmLsdradr2g{
	unsigned long		word;
	struct {
		unsigned long	sdradr2g	:32;
	}bit;
};

/*	structure of lsdradr2b	(2841_3894h)	*/
union _IoLtmChLtmLsdradr2b{
	unsigned long		word;
	struct {
		unsigned long	sdradr2b	:32;
	}bit;
};

/*	structure of lsdrhszr3	(2841_3898h)	*/
union _IoLtmChLtmLsdrhszr3{
	unsigned long		word;
	struct {
		unsigned long	sdrhszr3	:10;
		unsigned long					:22;
	}bit;
};

/*	structure of lsdrdefr3	(2841_389Ch)	*/
union _IoLtmChLtmLsdrdefr3{
	unsigned long		word;
	struct {
		unsigned long	sdrdefr3	:16;
		unsigned long					:16;
	}bit;
};

/*	structure of lsdrvszr3	(2841_38A0h)	*/
union _IoLtmChLtmLsdrvszr3{
	unsigned long		word;
	struct {
		unsigned long	sdrvszr3	:10;
		unsigned long					:22;
	}bit;
};

/*	structure of lsdradr3	(2841_38A4h)	*/
union _IoLtmChLtmLsdradr3{
	unsigned long		word;
	struct {
		unsigned long	sdradr3	:32;
	}bit;
};

/*	structure of lsdrdefr4	(2841_38ACh)	*/
union _IoLtmChLtmLsdrdefr4{
	unsigned long		word;
	struct {
		unsigned long	sdrdefr4	:16;
		unsigned long				:16;
	}bit;
};

/*	structure of lsdradr4	(2841_38B4h)	*/
union _IoLtmChLtmLsdradr4{
	unsigned long		word;
	struct {
		unsigned long	sdradr4	:32;
	}bit;
};

/*	structure of lsdrofs	(2841_38B8h)	*/
union _IoLtmChLtmLsdrofs{
	unsigned long		word;
	struct {
		unsigned long					:2;
		unsigned long	sdrofsr3	:1;
		unsigned long					:3;
		unsigned long	sdrofsr4	:1;
		unsigned long					:25;
	}bit;
};

/*	structure of lsdwadr	(2841_38BCh)	*/
union _IoLtmChLtmLsdwadr{
	unsigned long		word;
	struct {
		unsigned long	sdwadr	:32;
	}bit;
};

/*	structure of lsdwdefr	(2841_38C0h)	*/
union _IoLtmChLtmLsdwdefr{
	unsigned long		word;
	struct {
		unsigned long	sdwdefr	:16;
		unsigned long					:16;
	}bit;
};

/*	structure of lsdwadg	(2841_38C4h)	*/
union _IoLtmChLtmLsdwadg{
	unsigned long		word;
	struct {
		unsigned long	sdwadg	:32;
	}bit;
};

/*	structure of lsdwdefg	(2841_38C8h)	*/
union _IoLtmChLtmLsdwdefg{
	unsigned long		word;
	struct {
		unsigned long	sdwdefg	:16;
		unsigned long					:16;
	}bit;
};

/*	structure of lsdwadb	(2841_38CCh)	*/
union _IoLtmChLtmLsdwadb{
	unsigned long		word;
	struct {
		unsigned long	sdwadb	:32;
	}bit;
};

/*	structure of lsdwdefb	(2841_38D0h)	*/
union _IoLtmChLtmLsdwdefb{
	unsigned long		word;
	struct {
		unsigned long	sdwdefb	:16;
		unsigned long					:16;
	}bit;
};

/*	structure of lioctl (2841_38D4h)	*/
union _IoLtmChLtmLioctl{
	unsigned long		word;
	struct {
		unsigned long	insel			:1;
		unsigned long					:3;
		unsigned long	r3dtyp		:2;
		unsigned long	r4dtyp		:2;
		unsigned long					:7;
		unsigned long	bypass		:1;
		unsigned long	outsel		:1;
		unsigned long					:3;
		unsigned long	w1dtyp	:2;
		unsigned long					:10;
	}bit;
};

/*	structure of lhsta	(2841_39D8h)	*/
union _IoLtmChLtmLhsta{
	unsigned long		word;
	struct {
		long					hsta	:25;
		unsigned long			:7;
	}bit;
};

/*	structure of lhpit	(2841_39DCh)	*/
union _IoLtmChLtmLhpit{
	unsigned long		word;
	struct {
		unsigned long	hpit	:15;
		unsigned long			:17;
	}bit;
};

/*	structure of lvsta	(2841_39E0h)	*/
union _IoLtmChLtmLvsta{
	unsigned long		word;
	struct {
		long					vsta	:25;
		unsigned long			:7;
	}bit;
};

/*	structure of lvpit	(2841_39E4h)	*/
union _IoLtmChLtmLvpit{
	unsigned long		word;
	struct {
		unsigned long	vpit	:15;
		unsigned long			:17;
	}bit;
};

/*	structure of nlvthof7	(2841_39F0h)	*/
union _IoLtmChLtmNlvthof{
	unsigned long		word;
	struct {
		unsigned long					:16;
		unsigned long	nlvthof7	:13;
		unsigned long					:3;
	}bit;
};

/*	structure of plvthof7	(2841_3A30h)	*/
union _IoLtmChLtmPlvthof{
	unsigned long		word;
	struct {
		unsigned long					:16;
		unsigned long	plvthof7	:13;
		unsigned long					:3;
	}bit;
};

/*	structure of lyshadow	(2841_3A88h)	*/
union _IoLtmChLtmLyshadow{
	unsigned long		word;
	struct {
		unsigned long	yshadow	:14;
		unsigned long					:18;
	}bit;
};

/*	structure of lyhighlight	(2841_3A8Ch)	*/
union _IoLtmChLtmLyhighlight{
	unsigned long		word;
	struct {
		unsigned long	yhighlight	:14;
		unsigned long						:18;
	}bit;
};

/*	structure of rcgmd	(2841_3A90h)	*/
union _IoLtmChLtmRcgmd{
	unsigned long		word;
	struct {
		unsigned long	yshmd		:1;
		unsigned long					:3;
		unsigned long	rcgmd		:1;
		unsigned long					:3;
		unsigned long	rcgamd	:1;
		unsigned long					:23;
	}bit;
};

/*	structure of rcgtbl	(2841_3AC0h)	*/
union _IoLtmChLtmRcgtbl{
	unsigned short		hword[32];
	struct {
		unsigned short	rcgtbl	:12;
		unsigned short				:4;
	}bit;
};

/*	structure of bldyrt (2841_3B1Ch)	*/
union _IoLtmChLtmBldyrt{
	unsigned long		word;
	struct {
		unsigned long	bldyrt	:4;
		unsigned long				:28;
	}bit;
};

/*	structure of bldof	(2841_3B20h)	*/
union _IoLtmChLtmBldof1{
	unsigned long		word;
	struct {
		unsigned long	bldof0	:13;
		unsigned long				:3;
		unsigned long	bldof1	:13;
		unsigned long				:3;
	}bit;
};

union _IoLtmChLtmBldof2{
	unsigned long		word;
	struct {
		unsigned long	bldof2	:13;
		unsigned long				:3;
		unsigned long	bldof3	:13;
		unsigned long				:3;
	}bit;
};

union _IoLtmChLtmBldof3{
	unsigned long		word;
	struct {
		unsigned long	bldof4	:13;
		unsigned long				:3;
		unsigned long	bldof5	:13;
		unsigned long				:3;
	}bit;
};

union _IoLtmChLtmBldof4{
	unsigned long		word;
	struct {
		unsigned long	bldof6	:13;
		unsigned long				:3;
		unsigned long	bldof7	:13;
		unsigned long				:3;
	}bit;
};

struct _IoLtmChLtmBldof{
	IoLtmChLtmBldof1		bldof1;
	IoLtmChLtmBldof2		bldof2;
	IoLtmChLtmBldof3		bldof3;
	IoLtmChLtmBldof4		bldof4;
};

/*	structure of bldga	(2841_3B30h)	*/
union _IoLtmChLtmBldga1{
	unsigned long		word;
	struct {
		long			bldga0		:15;
		unsigned long			:1;
		long			bldga1		:15;
		unsigned long			:1;
	}bit;
};

union _IoLtmChLtmBldga2{
	unsigned long		word;
	struct {
		long			bldga2		:15;
		unsigned long			:1;
		long			bldga3		:15;
		unsigned long			:1;
	}bit;
};

union _IoLtmChLtmBldga3{
	unsigned long		word;
	struct {
		long			bldga4		:15;
		unsigned long			:1;
		long			bldga5		:15;
		unsigned long			:1;
	}bit;
};

union _IoLtmChLtmBldga4{
	unsigned long		word;
	struct {
		long			bldga6		:15;
		unsigned long			:1;
		long			bldga7		:15;
		unsigned long			:1;
	}bit;
};

struct _IoLtmChLtmBldga{
	IoLtmChLtmBldga1	bldga1;
	IoLtmChLtmBldga2	bldga2;
	IoLtmChLtmBldga3	bldga3;
	IoLtmChLtmBldga4	bldga4;
};

/*	structure of bldbd	(2841_3B40h)	*/
union _IoLtmChLtmBldbd1{
	unsigned long		word;
	struct {
		unsigned long	bldbd0		:12;
		unsigned long					:4;
		unsigned long	bldbd1		:12;
		unsigned long					:4;
	}bit;
};

union _IoLtmChLtmBldbd2{
	unsigned long		word;
	struct {
		unsigned long	bldbd2		:12;
		unsigned long					:4;
		unsigned long	bldbd3		:12;
		unsigned long					:4;
	}bit;
};

union _IoLtmChLtmBldbd3{
	unsigned long		word;
	struct {
		unsigned long	bldbd4		:12;
		unsigned long					:4;
		unsigned long	bldbd5		:12;
		unsigned long					:4;
	}bit;
};

union _IoLtmChLtmBldbd4{
	unsigned long		word;
	struct {
		unsigned long	bldbd6		:12;
		unsigned long					:4;
		unsigned long	bldbd7		:12;
		unsigned long					:4;
	}bit;
};

struct _IoLtmChLtmBldbd{
	IoLtmChLtmBldbd1	bldbd1;
	IoLtmChLtmBldbd2	bldbd2;
	IoLtmChLtmBldbd3	bldbd3;
	IoLtmChLtmBldbd4	bldbd4;
};

/*	structure of ltmmd	(2841_3B50h)	*/
union _IoLtmChLtmLtmmd{
	unsigned long		word;
	struct {
		unsigned long	ltmmd	:1;
		unsigned long				:31;
	}bit;
};

/*	structure of cgof	(2841_3B60h)	*/
union _IoLtmChLtmCgof1{
	unsigned long		word;
	struct {
		unsigned long	cgof0	:13;
		unsigned long				:3;
		unsigned long	cgof1	:13;
		unsigned long				:3;
	}bit;
};

union _IoLtmChLtmCgof2{
	unsigned long		word;
	struct {
		unsigned long	cgof2	:13;
		unsigned long				:3;
		unsigned long	cgof3	:13;
		unsigned long				:3;
	}bit;
};

union _IoLtmChLtmCgof3{
	unsigned long		word;
	struct {
		unsigned long	cgof4	:13;
		unsigned long				:3;
		unsigned long	cgof5	:13;
		unsigned long				:3;
	}bit;
};

union _IoLtmChLtmCgof4{
	unsigned long		word;
	struct {
		unsigned long	cgof6	:13;
		unsigned long				:3;
		unsigned long	cgof7	:13;
		unsigned long				:3;
	}bit;
};

struct _IoLtmChLtmCgof{
	IoLtmChLtmCgof1 cgof1;
	IoLtmChLtmCgof2 cgof2;
	IoLtmChLtmCgof3 cgof3;
	IoLtmChLtmCgof4 cgof4;
};

/*	structure of cgga	(2841_3B70h)	*/
union _IoLtmChLtmCgga1{
	unsigned long		word;
	struct {
		long			cgga0		:13;
		unsigned long			:3;
		long			cgga1		:13;
		unsigned long			:3;
	}bit;
};

union _IoLtmChLtmCgga2{
	unsigned long		word;
	struct {
		long			cgga2		:13;
		unsigned long			:3;
		long			cgga3		:13;
		unsigned long			:3;
	}bit;
};

union _IoLtmChLtmCgga3{
	unsigned long		word;
	struct {
		long			cgga4		:13;
		unsigned long			:3;
		long			cgga5		:13;
		unsigned long			:3;
	}bit;
};

union _IoLtmChLtmCgga4{
	unsigned long		word;
	struct {
		long			cgga6		:13;
		unsigned long			:3;
		long			cgga7		:13;
		unsigned long			:3;
	}bit;
};

struct _IoLtmChLtmCgga{
	IoLtmChLtmCgga1 cgga1;
	IoLtmChLtmCgga2 cgga2;
	IoLtmChLtmCgga3 cgga3;
	IoLtmChLtmCgga4 cgga4;
};

/*	structure of cgbd	(2841_3B80h)	*/
union _IoLtmChLtmCgbd1{
	unsigned long		word;
	struct {
		unsigned long				:16;
		unsigned long	cgbd1	:12;
		unsigned long				:4;
	}bit;
};

union _IoLtmChLtmCgbd2{
	unsigned long		word;
	struct {
		unsigned long	cgbd2	:12;
		unsigned long				:4;
		unsigned long	cgbd3	:12;
		unsigned long				:4;
	}bit;
};

union _IoLtmChLtmCgbd3{
	unsigned long		word;
	struct {
		unsigned long	cgbd4	:12;
		unsigned long				:4;
		unsigned long	cgbd5	:12;
		unsigned long				:4;
	}bit;
};

union _IoLtmChLtmCgbd4{
	unsigned long		word;
	struct {
		unsigned long	cgbd6	:12;
		unsigned long				:4;
		unsigned long	cgbd7	:12;
		unsigned long				:4;
	}bit;
};

struct _IoLtmChLtmCgbd{
	IoLtmChLtmCgbd1 cgbd1;
	IoLtmChLtmCgbd2 cgbd2;
	IoLtmChLtmCgbd3 cgbd3;
	IoLtmChLtmCgbd4 cgbd4;
};

/*	structure of lylctl (2841_3BC4h)	*/
union _IoLtmChLtmLylctl{
	unsigned long		word;
	struct {
		unsigned long	ylogsl	:1;
		unsigned long				:3;
		unsigned long	ylogsta	:1;
		unsigned long				:27;
	}bit;
};

/*	structure of lylog0ep0	(2841_3BC8h)	*/
union _IoLtmChLtmLylog0ep0{
	unsigned long		word;
	struct {
		unsigned long	ylog0ep0	:14;
		unsigned long					:18;
	}bit;
};

/*	structure of lylog0ep1	(2841_3BCCh)	*/
union _IoLtmChLtmLylog0ep1{
	unsigned long		word;
	struct {
		unsigned long	ylog0ep1	:14;
		unsigned long					:18;
	}bit;
};

/*	structure of lylog1ep0	(2841_3BD0h)	*/
union _IoLtmChLtmLylog1ep0{
	unsigned long		word;
	struct {
		unsigned long	ylog1ep0	:14;
		unsigned long					:18;
	}bit;
};

/*	structure of lylog1ep1	(2841_3BD4h)	*/
union _IoLtmChLtmLylog1ep1{
	unsigned long		word;
	struct {
		unsigned long	ylog1ep1	:14;
		unsigned long					:18;
	}bit;
};

/* Define i/o mapping */
struct _IoLtmChLtm{

	/* JDSLTM */
	IoLtmChLtmLtmsr			ltmsr;			/* 2841_(3800 - 3803h) */
	IoLtmChLtmLsramen		lsramen;		/* 2841_(3804 - 3807h) */
	IoLtmChLtmLtrg				ltrg;				/* 2841_(3808 - 380Bh) */
	IoLtmChLtmLfrstp			lfrstp;			/* 2841_(380C - 380Fh) */
	IoLtmChLtmLparmsk		lparmsk;		/* 2841_(3810 - 3813h) */
	unsigned char 				dmy38143817[0x3818-0x3814];			/* 2841_(3814 - 3817h) */
	IoLtmChLtmLint0			lint0;			/* 2841_(3818 - 381Bh) */
	IoLtmChLtmLint1			lint1;			/* 2841_(381C - 381Fh) */
	IoLtmChLtmLlintlv			llintlv;			/* 2841_(3820 - 3823h) */
	IoLtmChLtmLaxictlr1		laxictlr1;		/* 2841_(3824 - 3827h) */
	IoLtmChLtmLaxictlr2		laxictlr2;		/* 2841_(3828 - 382Bh) */
	IoLtmChLtmLaxirerr		laxirerr;		/* 2841_(382C - 382Fh) */
	IoLtmChLtmLaxictlw		laxictlw;		/* 2841_(3830 - 3833h) */
	IoLtmChLtmLaxiwerr		laxiwerr;		/* 2841_(3834 - 3837h) */
	IoLtmChLtmLaxibsiz		laxibsiz;		/* 2841_(3838 - 383Bh) */
	IoLtmChLtmAxirsel			axirsel;			/* 2841_(383C - 383Fh) */
	unsigned char				dmy3840387f[0x3880-0x3840];			/* 2841_(3840 - 387Fh) */
	IoLtmChLtmLsdrhszr2	lsdrhszr2;		/* 2841_(3880 - 3883h) */
	IoLtmChLtmLsdrdefr2	lsdrdefr2;		/* 2841_(3884 - 3887h) */
	IoLtmChLtmLsdrvszr2	lsdrvszr2;			/* 2841_(3888 - 388Bh) */
	IoLtmChLtmLsdradr2r	lsdradr2r;		/* 2841_(388C - 388Fh) */
	IoLtmChLtmLsdradr2g	lsdradr2g;		/* 2841_(3890 - 3893h) */
	IoLtmChLtmLsdradr2b	lsdradr2b;		/* 2841_(3894 - 3897h) */
	IoLtmChLtmLsdrhszr3	lsdrhszr3;		/* 2841_(3898 - 389Bh) */
	IoLtmChLtmLsdrdefr3	lsdrdefr3;		/* 2841_(389C - 389Fh) */
	IoLtmChLtmLsdrvszr3	lsdrvszr3;			/* 2841_(38A0 - 38A3h) */
	IoLtmChLtmLsdradr3		lsdradr3;			/* 2841_(38A4 - 38A7h) */
	unsigned char 				dmy38a838ab[0x38AC-0x38A8];			/* 2841_(38A8 - 38ABh) */
	IoLtmChLtmLsdrdefr4	lsdrdefr4;		/* 2841_(38AC - 38AFh) */
	unsigned char				dmy38b038b3[0x38B4-0x38B0];			/* 2841_(38B0 - 38B3h) */
	IoLtmChLtmLsdradr4		lsdradr4;		/* 2841_(38B4 - 38B7h) */
	IoLtmChLtmLsdrofs		lsdrofs;		/* 2841_(38B8 - 38BBh) */
	IoLtmChLtmLsdwadr		lsdwadr;		/* 2841_(38BC - 38BFh) */
	IoLtmChLtmLsdwdefr		lsdwdefr;		/* 2841_(38C0 - 38C3h) */
	IoLtmChLtmLsdwadg		lsdwadg;		/* 2841_(38C4 - 38C7h) */
	IoLtmChLtmLsdwdefg	lsdwdefg;		/* 2841_(38C8 - 38CBh) */
	IoLtmChLtmLsdwadb		lsdwadb;		/* 2841_(38CC - 38CFh) */
	IoLtmChLtmLsdwdefb	lsdwdefb;		/* 2841_(38D0 - 38D3h) */
	IoLtmChLtmLioctl			lioctl;			/* 2841_(38D4 - 38D7h) */
	unsigned char 				dmy38d839d7[0x39D8-0x38D8];			/* 2841_(38D8 - 39D7h) */
	IoLtmChLtmLhsta			lhsta;			/* 2841_(39D8 - 39DBh) */
	IoLtmChLtmLhpit			lhpit;			/* 2841_(39DC - 39DFh) */
	IoLtmChLtmLvsta			lvsta;			/* 2841_(39E0 - 39E3h) */
	IoLtmChLtmLvpit			lvpit;			/* 2841_(39E4 - 39E7h) */
	unsigned char 				dmy39e839fb[0x39FC-0x39E8];			/* 2841_(39E8 - 39FBh) */
	IoLtmChLtmNlvthof		nlvthof7;		/* 2841_(39FC - 39FFh) */
	unsigned char 				dmy3a003a3b[0x3A3C-0x3A00];			/* 2841_(3A00 - 3A3Bh) */
	IoLtmChLtmPlvthof		plvthof7;		/* 2841_(3A3C - 3A3Fh) */
	unsigned char 				dmy3a403a87[0x3A88-0x3A40];			/* 2841_(3A40 - 3A87h) */
	IoLtmChLtmLyshadow	lyshadow;		/* 2841_(3A88 - 3A8Bh) */
	IoLtmChLtmLyhighlight	lyhighlight;	/* 2841_(3A8C - 3A8Fh) */
	IoLtmChLtmRcgmd		rcgmd;			/* 2841_(3A90 - 3A93h) */
	unsigned char 				dmy3a943abf[0x3AC0-0x3A94];			/* 2841_(3A94 - 3ABFh) */
	IoLtmChLtmRcgtbl			rcgtbl;			/* 2841_(3AC0 - 3AFFh) */
	unsigned char 				dmy3b003b1b[0x3B1C-0x3B00];			/* 2841_(3A90 - 3B1Bh) */
	IoLtmChLtmBldyrt			bldyrt;			/* 2841_(3B1C - 3B1Fh) */
	IoLtmChLtmBldof			bldof;			/* 2841_(3B20 - 3B2Fh) */
	IoLtmChLtmBldga			bldga;			/* 2841_(3B30 - 3B3Fh) */
	IoLtmChLtmBldbd			bldbd;			/* 2841_(3B40 - 3B4Fh) */
	IoLtmChLtmLtmmd		ltmmd;			/* 2841_(3B50 - 3B53h) */
	unsigned char 				dmy3b543b5f[0x3B60-0x3B54];			/* 2841_(3B54 - 3B5Fh) */
	IoLtmChLtmCgof			cgof;			/* 2841_(3B60 - 3B6Fh) */
	IoLtmChLtmCgga			cgga;			/* 2841_(3B70 - 3B7Fh) */
	IoLtmChLtmCgbd			cgbd;			/* 2841_(3B80 - 3B8Fh) */
	unsigned char 				dmy3b903bc3[0x3BC4-0x3B90];			/* 2841_(3B90 - 3BC3h) */
	IoLtmChLtmLylctl			lylctl;			/* 2841_(3BC4 - 3BC7h) */
	IoLtmChLtmLylog0ep0	lylog0ep0;		/* 2841_(3BC8 - 3BCBh) */
	IoLtmChLtmLylog0ep1	lylog0ep1;		/* 2841_(3BCC - 3BCFh) */
	IoLtmChLtmLylog1ep0	lylog1ep0;		/* 2841_(3BD0 - 3BD3h) */
	IoLtmChLtmLylog1ep1	lylog1ep1;		/* 2841_(3BD4 - 3BD7h) */
	unsigned char 				dmy3bd83bff[0x3C00-0x3BD8];			/* 2841_(3BD8 - 3BFFh) */

};


#endif /* __JDSLTM1A_LTM_H__ */
