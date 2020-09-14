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
 * @file		jdsltm1arbk.h
 * @brief		Definition JDSLTM1A Macro I/O register
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2016 Socionext Inc.</I></B>
 */


#ifndef __JDSLTM1A_RBK_H__
#define __JDSLTM1A_RBK_H__


typedef union _IoLtmChRbkRbksr   				IoLtmChRbkRbksr;
typedef union _IoLtmChRbkRsRamen  			IoLtmChRbkRsRamen;
typedef union _IoLtmChRbkRtrg						IoLtmChRbkRtrg;
typedef union _IoLtmChRbkRfrstp  				IoLtmChRbkRfrstp;
typedef union _IoLtmChRbkRparmsk  			IoLtmChRbkRparmsk;
typedef union _IoLtmChRbkRint0  					IoLtmChRbkRint0;
typedef union _IoLtmChRbkRint1 					IoLtmChRbkRint1;
typedef union _IoLtmChRbkRlintlv  				IoLtmChRbkRlintlv;
typedef union _IoLtmChRbkRaxictlr1  			IoLtmChRbkRaxictlr1;
typedef union _IoLtmChRbkRaxirerr  			IoLtmChRbkRaxirerr;
typedef union _IoLtmChRbkRaxictlw1  			IoLtmChRbkRaxictlw1;
typedef union _IoLtmChRbkRaxiwerr  			IoLtmChRbkRaxiwerr;
typedef union _IoLtmChRbkRaxibsiz  			IoLtmChRbkRaxibsiz;
typedef union _IoLtmChRbkRsdrhsz  				IoLtmChRbkRsdrhsz;
typedef union _IoLtmChRbkRsdrdef  				IoLtmChRbkRsdrdef;
typedef union _IoLtmChRbkRsdrvsz  				IoLtmChRbkRsdrvsz;
typedef union _IoLtmChRbkRsdradr  				IoLtmChRbkRsdradr;
typedef union _IoLtmChRbkRsdradg   			IoLtmChRbkRsdradg;
typedef union _IoLtmChRbkRsdradb  			IoLtmChRbkRsdradb;
typedef union _IoLtmChRbkRsdwad  				IoLtmChRbkRsdwad;
typedef union _IoLtmChRbkRsdwdef  			IoLtmChRbkRsdwdef;
typedef union _IoLtmChRbkRioctl  				IoLtmChRbkRioctl;
typedef union _IoLtmChRbkBthsta0  				IoLtmChRbkBthsta0;
typedef union _IoLtmChRbkBtvsta0  				IoLtmChRbkBtvsta0;
typedef union _IoLtmChRbkBthsiz0  				IoLtmChRbkBthsiz0;
typedef union _IoLtmChRbkBtvsiz0  				IoLtmChRbkBtvsiz0;
typedef union _IoLtmChRbkBthsta1  				IoLtmChRbkBthsta1;
typedef union _IoLtmChRbkBtvsta1  				IoLtmChRbkBtvsta1;
typedef union _IoLtmChRbkBthsiz1  				IoLtmChRbkBthsiz1;
typedef union _IoLtmChRbkBtvsiz1  				IoLtmChRbkBtvsiz1;
typedef union _IoLtmChRbkRsfen  				IoLtmChRbkRsfen;
typedef union _IoLtmChRbkHven 					IoLtmChRbkHven;
typedef union _IoLtmChRbkRhsta  				IoLtmChRbkRhsta;
typedef union _IoLtmChRbkRhpit  					IoLtmChRbkRhpit;
typedef union _IoLtmChRbkRvsta  					IoLtmChRbkRvsta;
typedef union _IoLtmChRbkRvpit  					IoLtmChRbkRvpit;
typedef union _IoLtmChRbkRdcmd  				IoLtmChRbkRdcmd;
typedef union _IoLtmChRbkRten  					IoLtmChRbkRten;
typedef union _IoLtmChRbkRthsta  				IoLtmChRbkRthsta;
typedef union _IoLtmChRbkRtvsta  				IoLtmChRbkRtvsta;
typedef union _IoLtmChRbkRthsiz  				IoLtmChRbkRthsiz;
typedef union _IoLtmChRbkRtvsiz 					IoLtmChRbkRtvsiz;
typedef struct _IoLtmChRbk  							IoLtmChRbk;

/*	structure of rbksr	(2841_3000h)	*/
union _IoLtmChRbkRbksr{
	unsigned long		word;
	struct {
		unsigned long	sr	:1;
		unsigned long		:31;
	}bit;
};

/*	structure of rsramen	(2841_3004h)	*/
union _IoLtmChRbkRsRamen{
	unsigned long		word;
	struct {
		unsigned long	sramaen		:1;
		unsigned long						:3;
		unsigned long	rmaenlb1	:1;
		unsigned long	rmaenlb2	:1;
		unsigned long	rmaenhst	:1;
		unsigned long	rmaensro	:1;
		unsigned long	rmaenwch	:1;
		unsigned long	rmaenrch	:1;
		unsigned long						:22;
	}bit;
};

/*	structure of rtrg	(2841_3008h)	*/
union _IoLtmChRbkRtrg{
	unsigned long		word;
	struct {
		unsigned long	trg	:2;
		unsigned long			:30;
	}bit;
};

/*	structure of rfrstp	(2841_300Ch)	*/
union _IoLtmChRbkRfrstp{
	unsigned long		word;
	struct {
		unsigned long	frstp	:1;
		unsigned long			:31;
	}bit;
};

/*	structure of rparmsk	(2841_3010h)	*/
union _IoLtmChRbkRparmsk{
	unsigned long		word;
	struct {
		unsigned long	parmsk	:1;
		unsigned long					:31;
	}bit;
};

/*	structure of rint0	(2841_301Ch)	*/
union _IoLtmChRbkRint0{
	unsigned long		word;
	struct {
		unsigned long	finen		:1;
		unsigned long					:3;
		unsigned long	frmen		:1;
		unsigned long					:3;
		unsigned long	hinien		:1;
		unsigned long					:3;
		unsigned long	lcnten		:1;
		unsigned long					:3;
		unsigned long	waiten		:1;
		unsigned long					:3;
		unsigned long	axreen		:1;
		unsigned long	axween	:1;
		unsigned long					:2;
		unsigned long	hsteen		:1;
		unsigned long					:7;
	}bit;
};

/*	structure of rint1	(2841_3020h)	*/
union _IoLtmChRbkRint1{
	unsigned long		word;
	struct {
		unsigned long	__finfl		:1;
		unsigned long					:3;
		unsigned long	__frmfl		:1;
		unsigned long					:3;
		unsigned long	__hinifl		:1;
		unsigned long					:3;
		unsigned long	__lcntfl		:1;
		unsigned long					:3;
		unsigned long	__waitfl	:1;
		unsigned long					:3;
		unsigned long	__axrefl	:1;
		unsigned long	__axwefl	:1;
		unsigned long					:2;
		unsigned long	__hstefl	:1;
		unsigned long					:7;
	}bit;
};

/*	structure of rlintlv	(2841_3024h)	*/
union _IoLtmChRbkRlintlv{
	unsigned long		word;
	struct {
		unsigned long	lintlv	:14;
		unsigned long				:18;
	}bit;
};

/*	structure of raxictlr1	(2841_3028h)	*/
union _IoLtmChRbkRaxictlr1{
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

/*	structure of raxirerr	(2841_302Ch)	*/
union _IoLtmChRbkRaxirerr{
	unsigned long		word;
	struct {
		unsigned long	rrespR	:2;
		unsigned long	rrespG	:2;
		unsigned long	rrespB	:2;
		unsigned long				:26;
	}bit;
};

/*	structure of raxictlw1	(2841_3030h)	*/
union _IoLtmChRbkRaxictlw1{
	unsigned long		word;
	struct {
		unsigned long	awcache	:4;
		unsigned long	awprot		:3;
		unsigned long					:25;
	}bit;
};

/*	structure of raxiwerr	(2841_3034h)	*/
union _IoLtmChRbkRaxiwerr{
	unsigned long		word;
	struct {
		unsigned long	wresp	:2;
		unsigned long				:30;
	}bit;
};

/*	structure of raxibsiz	(2841_3038h)	*/
union _IoLtmChRbkRaxibsiz{
	unsigned long		word;
	struct {
		unsigned long	burstrr		:1;
		unsigned long	burstrg	:1;
		unsigned long	burstrb	:1;
		unsigned long					:5;
		unsigned long	burstw		:1;
		unsigned long					:7;
		unsigned long	wstbmsk	:1;
		unsigned long					:15;
	}bit;
};

/*	structure of rsdrhsz	(2841_3080h)	*/
union _IoLtmChRbkRsdrhsz{
	unsigned long		word;
	struct {
		unsigned long	sdrhsz	:12;
		unsigned long				:20;
	}bit;
};

/*	structure of rsdrdef	(2841_3084h)	*/
union _IoLtmChRbkRsdrdef{
	unsigned long		word;
	struct {
		unsigned long	sdrdef	:16;
		unsigned long				:16;
	}bit;
};

/*	structure of rsdrvsz	(2841_3088h)	*/
union _IoLtmChRbkRsdrvsz{
	unsigned long		word;
	struct {
		unsigned long	sdrvsz	:14;
		unsigned long				:18;
	}bit;
};

/*	structure of rsdradr	(2841_308Ch)	*/
union _IoLtmChRbkRsdradr{
	unsigned long		word;
	struct {
		unsigned long	sdradr	:32;
	}bit;
};

/*	structure of rsdradg	(2841_3090h)	*/
union _IoLtmChRbkRsdradg{
	unsigned long		word;
	struct {
		unsigned long	sdradg	:32;
	}bit;
};

/*	structure of rsdradb	(2841_3094h)	*/
union _IoLtmChRbkRsdradb{
	unsigned long		word;
	struct {
		unsigned long	sdradb	:32;
	}bit;
};

/*	structure of rsdwad	(2841_3098h)	*/
union _IoLtmChRbkRsdwad{
	unsigned long		word;
	struct {
		unsigned long	sdwad	:32;
	}bit;
};

/*	structure of rsdwdef	(2841_309Ch)	*/
union _IoLtmChRbkRsdwdef{
	unsigned long		word;
	struct {
		unsigned long	sdwdef	:16;
		unsigned long					:16;
	}bit;
};

/*	structure of rioctl	(2841_30A0h)	*/
union _IoLtmChRbkRioctl{
	unsigned long		word;
	struct {
		unsigned long	insel			:2;
		unsigned long					:2;
		unsigned long	bayer0		:2;
		unsigned long	bayer1		:2;
		unsigned long					:4;
		unsigned long	sromd		:1;
		unsigned long					:3;
		unsigned long	outsel		:1;
		unsigned long					:3;
		unsigned long	w0dtyp	:2;
		unsigned long					:10;
	}bit;
};

/*	structure of bthsta0	(2841_30A4h)	*/
union _IoLtmChRbkBthsta0{
	unsigned long		word;
	struct {
		unsigned long	bthsta0	:12;
		unsigned long					:20;
	}bit;
};

/*	structure of btvsta0	(2841_30A8h)	*/
union _IoLtmChRbkBtvsta0{
	unsigned long		word;
	struct {
		unsigned long	btvsta0	:12;
		unsigned long					:20;
	}bit;
};

/*	structure of bthsiz0	(2841_30ACh)	*/
union _IoLtmChRbkBthsiz0{
	unsigned long		word;
	struct {
		unsigned long	bthsiz0	:12;
		unsigned long				:20;
	}bit;
};

/*	structure of btvsiz0	(2841_30B0h)	*/
union _IoLtmChRbkBtvsiz0{
	unsigned long		word;
	struct {
		unsigned long	btvsiz0	:14;
		unsigned long				:18;
	}bit;
};

/*	structure of bthsta1	(2841_30B4h)	*/
union _IoLtmChRbkBthsta1{
	unsigned long		word;
	struct {
		unsigned long	bthsta1	:12;
		unsigned long					:20;
	}bit;
};

/*	structure of btvsta1	(2841_30B8h)	*/
union _IoLtmChRbkBtvsta1{
	unsigned long		word;
	struct {
		unsigned long	btvsta1	:12;
		unsigned long					:20;
	}bit;
};

/*	structure of bthsiz1	(2841_30BCh)	*/
union _IoLtmChRbkBthsiz1{
	unsigned long		word;
	struct {
		unsigned long	bthsiz1	:12;
		unsigned long				:20;
	}bit;
};

/*	structure of btvsiz1	(2841_30C0h)	*/
union _IoLtmChRbkBtvsiz1{
	unsigned long		word;
	struct {
		unsigned long	btvsiz1	:14;
		unsigned long				:18;
	}bit;
};

/*	structure of rsfen	(2841_30C4h)	*/
union _IoLtmChRbkRsfen{
	unsigned long		word;
	struct {
		unsigned long	rsfen0	:1;
		unsigned long	rsfen1	:1;
		unsigned long				:2;
		unsigned long	rsfen	:1;
		unsigned long				:27;
	}bit;
};

/*	structure of hven	(2841_30C8h)	*/
union _IoLtmChRbkHven{
	unsigned long		word;
	struct {
		unsigned long	hven	:1;
		unsigned long				:31;
	}bit;
};

/*	structure of rhsta	(2841_30CCh)	*/
union _IoLtmChRbkRhsta{
	unsigned long		word;
	struct {
		unsigned long	hsta	:20;
		unsigned long			:12;
	}bit;
};

/*	structure of rhpit	(2841_30D0h)	*/
union _IoLtmChRbkRhpit{
	unsigned long		word;
	struct {
		unsigned long	hpit	:16;
		unsigned long			:16;
	}bit;
};

/*	structure of rvsta	(2841_30D4h)	*/
union _IoLtmChRbkRvsta{
	unsigned long		word;
	struct {
		unsigned long	vsta	:20;
		unsigned long			:12;
	}bit;
};

/*	structure of rvpit	(2841_30D8h)	*/
union _IoLtmChRbkRvpit{
	unsigned long		word;
	struct {
		unsigned long	vpit	:16;
		unsigned long			:16;
	}bit;
};

/*	structure of rdcmd	(2841_30DCh)	*/
union _IoLtmChRbkRdcmd{
	unsigned long		word;
	struct {
		unsigned long	rdcen	:1;
		unsigned long				:3;
		unsigned long	rdcmd	:2;
		unsigned long				:26;
	}bit;
};

/*	structure of rten	(2841_30E0h)	*/
union _IoLtmChRbkRten{
	unsigned long		word;
	struct {
		unsigned long	rten	:1;
		unsigned long			:31;
	}bit;
};

/*	structure of rthsta	(2841_30E4h)	*/
union _IoLtmChRbkRthsta{
	unsigned long		word;
	struct {
		unsigned long	rthsta	:10;
		unsigned long				:22;
	}bit;
};

/*	structure of rtvsta	(2841_30E8h)	*/
union _IoLtmChRbkRtvsta{
	unsigned long		word;
	struct {
		unsigned long	rtvsta	:10;
		unsigned long				:22;
	}bit;
};

/*	structure of rthsiz	(2841_30ECh)	*/
union _IoLtmChRbkRthsiz{
	unsigned long		word;
	struct {
		unsigned long	rthsiz	:10;
		unsigned long				:22;
	}bit;
};

/*	structure of rtvsiz	(2841_30F0h)	*/
union _IoLtmChRbkRtvsiz{
	unsigned long		word;
	struct {
		unsigned long	rtvsiz	:10;
		unsigned long				:22;
	}bit;
};

/* Define i/o mapping */
struct _IoLtmChRbk{
	/* JDSLTM */
	IoLtmChRbkRbksr				rbksr;			/* 2841_(3000 - 3003h) */
	IoLtmChRbkRsRamen		rsramen;		/* 2841_(3004 - 3007h) */
	IoLtmChRbkRtrg					rtrg;				/* 2841_(3008 - 300Bh) */
	IoLtmChRbkRfrstp				rfrstp;			/* 2841_(300C - 300Fh) */
	IoLtmChRbkRparmsk			rparmsk;		/* 2841_(3010 - 3013h) */
	unsigned char 					dmy3014301b[0x301C-0x3014];		/* 2841_(3014 - 301Bh) */
	IoLtmChRbkRint0				rint0;			/* 2841_(301C - 301Fh) */
	IoLtmChRbkRint1				rint1;			/* 2841_(3020 - 3023h) */
	IoLtmChRbkRlintlv				rlintlv;			/* 2841_(3024 - 3027h) */
	IoLtmChRbkRaxictlr1			raxictlr1;		/* 2841_(3028 - 302Bh) */
	IoLtmChRbkRaxirerr			raxirerr;		/* 2841_(302C - 302Fh) */
	IoLtmChRbkRaxictlw1		raxictlw1;	/* 2841_(3030 - 3033h) */
	IoLtmChRbkRaxiwerr			raxiwerr;		/* 2841_(3034 - 3037h) */
	IoLtmChRbkRaxibsiz			raxibsiz;		/* 2841_(3038 - 303Bh) */
	unsigned char 					dmy303c307f[0x3080-0x303C];		/* 2841_(303C - 307Fh) */
	IoLtmChRbkRsdrhsz			rsdrhsz;		/* 2841_(3080 - 3083h) */
	IoLtmChRbkRsdrdef			rsdrdef;		/* 2841_(3084 - 3087h) */
	IoLtmChRbkRsdrvsz			rsdrvsz;		/* 2841_(3088 - 308Bh) */
	IoLtmChRbkRsdradr			rsdradr;		/* 2841_(308C - 308Fh) */
	IoLtmChRbkRsdradg			rsdradg;		/* 2841_(3090 - 3093h) */
	IoLtmChRbkRsdradb			rsdradb;		/* 2841_(3094 - 3097h) */
	IoLtmChRbkRsdwad			rsdwad;		/* 2841_(3098 - 309Bh) */
	IoLtmChRbkRsdwdef			rsdwdef;		/* 2841_(309C - 309Fh) */
	IoLtmChRbkRioctl				rioctl;			/* 2841_(30A0 - 30A3h) */
	IoLtmChRbkBthsta0			bthsta0;		/* 2841_(30A4 - 30A7h) */
	IoLtmChRbkBtvsta0			btvsta0;		/* 2841_(30A8 - 30ABh) */
	IoLtmChRbkBthsiz0			bthsiz0;		/* 2841_(30AC - 30AFh) */
	IoLtmChRbkBtvsiz0			btvsiz0;		/* 2841_(30B0 - 30B3h) */
	IoLtmChRbkBthsta1			bthsta1;		/* 2841_(30B4 - 30B7h) */
	IoLtmChRbkBtvsta1			btvsta1;		/* 2841_(30B8 - 30BBh) */
	IoLtmChRbkBthsiz1			bthsiz1;		/* 2841_(30BC - 30BFh) */
	IoLtmChRbkBtvsiz1			btvsiz1;		/* 2841_(30C0 - 30C3h) */
	IoLtmChRbkRsfen				rsfen;			/* 2841_(30C4 - 30C7h) */
	IoLtmChRbkHven				hven;			/* 2841_(30C8 - 30CBh) */
	IoLtmChRbkRhsta				rhsta;			/* 2841_(30CC - 30CFh) */
	IoLtmChRbkRhpit				rhpit;			/* 2841_(30D0 - 30D3h) */
	IoLtmChRbkRvsta				rvsta;			/* 2841_(30D4 - 30D7h) */
	IoLtmChRbkRvpit				rvpit;			/* 2841_(30D8 - 30DBh) */
	IoLtmChRbkRdcmd			rdcmd;		/* 2841_(30DC - 30DFh) */
	IoLtmChRbkRten				rten;				/* 2841_(30E0 - 30E3h) */
	IoLtmChRbkRthsta				rthsta;			/* 2841_(30E4 - 30E7h) */
	IoLtmChRbkRtvsta				rtvsta;			/* 2841_(30E8 - 30EBh) */
	IoLtmChRbkRthsiz				rthsiz;			/* 2841_(30EC - 30EFh) */
	IoLtmChRbkRtvsiz				rtvsiz;			/* 2841_(30F0 - 30F3h) */
	unsigned char 					dmy30f431ff[0x3200-0x30F4];		/* 2841_(30F4 - 31FFh) */
};


#endif /* __JDSLTM1A_RBK_H__ */
