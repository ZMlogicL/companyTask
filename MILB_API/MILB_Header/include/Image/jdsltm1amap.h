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
 * @file		jdsltm1amap.h
 * @brief		Definition JDSLTM1A Macro I/O register
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2016 Socionext Inc.</I></B>
 */


#ifndef __JDSLTM1A_MAP_H__
#define __JDSLTM1A_MAP_H__


typedef union _IoLtmChMapMapsr   				IoLtmChMapMapsr;
typedef union _IoLtmChMapMsramen  			IoLtmChMapMsramen;
typedef union _IoLtmChMapMtrg 					IoLtmChMapMtrg;
typedef union _IoLtmChMapMfrstp  				IoLtmChMapMfrstp;
typedef union _IoLtmChMapMparmsk  			IoLtmChMapMparmsk;
typedef union _IoLtmChMapMhstini  			IoLtmChMapMhstini;
typedef union _IoLtmChMapMhcprd  			IoLtmChMapMhcprd;
typedef union _IoLtmChMapMint0   				IoLtmChMapMint0;
typedef union _IoLtmChMapMint1   				IoLtmChMapMint1;
typedef union _IoLtmChMapMlintlv  				IoLtmChMapMlintlv;
typedef union _IoLtmChMapAxichsel  			IoLtmChMapAxichsel;
typedef union _IoLtmChMapMaxictlr  			IoLtmChMapMaxictlr;
typedef union _IoLtmChMapMaxirerr  			IoLtmChMapMaxirerr;
typedef union _IoLtmChMapMaxictlw  			IoLtmChMapMaxictlw;
typedef union _IoLtmChMapMaxiwerr  			IoLtmChMapMaxiwerr;
typedef union _IoLtmChMapMaxibsiz  			IoLtmChMapMaxibsiz;
typedef union _IoLtmChMapMsdrhsz  			IoLtmChMapMsdrhsz;
typedef union _IoLtmChMapMsdrdef  			IoLtmChMapMsdrdef;
typedef union _IoLtmChMapMsdrvsz  			IoLtmChMapMsdrvsz;
typedef union _IoLtmChMapMsdrad  			IoLtmChMapMsdrad;
typedef union _IoLtmChMapMsdrofs  			IoLtmChMapMsdrofs;
typedef union _IoLtmChMapMsdwadw0  		IoLtmChMapMsdwadw0;
typedef union _IoLtmChMapMsdwdefw0  	IoLtmChMapMsdwdefw0;
typedef union _IoLtmChMapMsdwadw1 		IoLtmChMapMsdwadw1;
typedef union _IoLtmChMapMsdwdefw1 		IoLtmChMapMsdwdefw1;
typedef union _IoLtmChMapMioctl  				IoLtmChMapMioctl;
typedef union _IoLtmChMapGainr  				IoLtmChMapGainr;
typedef union _IoLtmChMapGaing  				IoLtmChMapGaing;
typedef union _IoLtmChMapGainb  				IoLtmChMapGainb;
typedef union _IoLtmChMapGaincpr  			IoLtmChMapGaincpr;
typedef union _IoLtmChMapGaincpg  			IoLtmChMapGaincpg;
typedef union _IoLtmChMapGaincpb  			IoLtmChMapGaincpb;
typedef union _IoLtmChMapPeps0m  			IoLtmChMapPeps0m;
typedef union _IoLtmChMapPeps0of  			IoLtmChMapPeps0of;
typedef union _IoLtmChMapPeps1m  			IoLtmChMapPeps1m;
typedef union _IoLtmChMapPeps1of 			IoLtmChMapPeps1of;
typedef union _IoLtmChMapPeps2m  			IoLtmChMapPeps2m;
typedef union _IoLtmChMapPeps2of  			IoLtmChMapPeps2of;
typedef union _IoLtmChMapNeps0m  			IoLtmChMapNeps0m;
typedef union _IoLtmChMapNeps0of   			IoLtmChMapNeps0of;
typedef union _IoLtmChMapNeps1m  			IoLtmChMapNeps1m;
typedef union _IoLtmChMapNeps1of  			IoLtmChMapNeps1of;
typedef union _IoLtmChMapNeps2m  			IoLtmChMapNeps2m;
typedef union _IoLtmChMapNeps2of  			IoLtmChMapNeps2of;
typedef union _IoLtmChMapYshadow  			IoLtmChMapYshadow;
typedef union _IoLtmChMapYhighlight  		IoLtmChMapYhighlight;
typedef union _IoLtmChMapMylctl 				IoLtmChMapMylctl;
typedef union _IoLtmChMapMylog0ep0  		IoLtmChMapMylog0ep0;
typedef union _IoLtmChMapMylog0ep1  		IoLtmChMapMylog0ep1;
typedef union _IoLtmChMapMylog1ep0  		IoLtmChMapMylog1ep0;
typedef union _IoLtmChMapMylog1ep1  		IoLtmChMapMylog1ep1;
typedef struct _IoLtmChMap							IoLtmChMap;

/*	structure of mapsr	(2841_3400h)	*/
union _IoLtmChMapMapsr{
	unsigned long		word;
	struct {
		unsigned long	sr	:1;
		unsigned long		:31;
	}bit;
};

/*	structure of msramen	(2841_3404h)	*/
union _IoLtmChMapMsramen{
	unsigned long		word;
	struct {
		unsigned long	sramaen		:1;
		unsigned long						:3;
		unsigned long	rmaenhst	:1;
		unsigned long	rmaenyn		:1;
		unsigned long	rmaendb		:1;
		unsigned long	rmaenrch	:1;
		unsigned long						:24;
	}bit;
};

/*	structure of mtrg	(2841_3408h)	*/
union _IoLtmChMapMtrg{
	unsigned long		word;
	struct {
		unsigned long	trg	:2;
		unsigned long			:30;
	}bit;
};

/*	structure of mfrstp	(2841_340Ch)	*/
union _IoLtmChMapMfrstp{
	unsigned long		word;
	struct {
		unsigned long	frstp	:1;
		unsigned long			:31;
	}bit;
};

/*	structure of mparmsk	(2841_3410h)	*/
union _IoLtmChMapMparmsk{
	unsigned long		word;
	struct {
		unsigned long	parmsk	:1;
		unsigned long					:31;
	}bit;
};

/*	structure of mhstini	(2841_3418h)	*/
union _IoLtmChMapMhstini{
	unsigned long		word;
	struct {
		unsigned long	hstini	:1;
		unsigned long				:31;
	}bit;
};

/*	structure of mhcprd	(2841_341Ch)	*/
union _IoLtmChMapMhcprd{
	unsigned long		word;
	struct {
		unsigned long	hcprd	:1;
		unsigned long				:31;
	}bit;
};

/*	structure of mint0	(2841_3424h)	*/
union _IoLtmChMapMint0{
	unsigned long		word;
	struct {
		unsigned long	finen		:1;
		unsigned long					:11;
		unsigned long	lcnten		:1;
		unsigned long					:3;
		unsigned long	hinien		:1;
		unsigned long					:3;
		unsigned long	axreen		:1;
		unsigned long	axween	:1;
		unsigned long					:2;
		unsigned long	hsteen		:1;
		unsigned long	rameen	:1;
		unsigned long					:6;
	}bit;
};

/*	structure of mint1	(2841_3428h)	*/
union _IoLtmChMapMint1{
	unsigned long		word;
	struct {
		unsigned long	__finfl		:1;
		unsigned long					:11;
		unsigned long	__lcntfl		:1;
		unsigned long					:3;
		unsigned long	__hinifl		:1;
		unsigned long					:3;
		unsigned long	__axrefl	:1;
		unsigned long	__axwefl	:1;
		unsigned long					:2;
		unsigned long	__hstefl	:1;
		unsigned long	__ramefl	:1;
		unsigned long					:6;
	}bit;
};

/*	structure of mlintlv	(2841_342Ch)	*/
union _IoLtmChMapMlintlv{
	unsigned long		word;
	struct {
		unsigned long	lintlv	:10;
		unsigned long				:22;
	}bit;
};

/*	structure of axichsel	(2841_3430h)	*/
union _IoLtmChMapAxichsel{
	unsigned long		word;
	struct {
		unsigned long	axiwsel1	:1;
		unsigned long	axiwsel2	:1;
		unsigned long					:30;
	}bit;
};

/*	structure of maxictlr	(2841_3434h)	*/
union _IoLtmChMapMaxictlr{
	unsigned long		word;
	struct {
		unsigned long	arcache	:4;
		unsigned long	arprot		:3;
		unsigned long					:25;
	}bit;
};

/*	structure of maxirerr	(2841_3438h)	*/
union _IoLtmChMapMaxirerr{
	unsigned long		word;
	struct {
		unsigned long	rresp	:2;
		unsigned long				:30;
	}bit;
};

/*	structure of maxictlw	(2841_343Ch)	*/
union _IoLtmChMapMaxictlw{
	unsigned long		word;
	struct {
		unsigned long	awcacheYp	:4;
		unsigned long	awprotYp		:3;
		unsigned long						:1;
		unsigned long	awcacheYn	:4;
		unsigned long	awprotYn		:3;
		unsigned long						:1;
		unsigned long	awcacheDb	:4;
		unsigned long	awprotDb	:3;
		unsigned long						:9;
	}bit;
};

/*	structure of maxiwerr	(2841_3440h)	*/
union _IoLtmChMapMaxiwerr{
	unsigned long		word;
	struct {
		unsigned long	wrespYp	:2;
		unsigned long	wrespYn	:2;
		unsigned long	wrespDb	:2;
		unsigned long					:26;
	}bit;
};

/*	structure of maxibsiz	(2841_3444h)	*/
union _IoLtmChMapMaxibsiz{
	unsigned long		word;
	struct {
		unsigned long	burstr			:1;
		unsigned long						:7;
		unsigned long	burstwyp		:1;
		unsigned long	burstwyn		:1;
		unsigned long	burstwdb		:1;
		unsigned long						:5;
		unsigned long	wstbmskyp	:1;
		unsigned long	wstbmskyn	:1;
		unsigned long	wstbmskdb	:1;
		unsigned long						:13;
	}bit;
};

/*	structure of msdrhsz	(2841_3480h)	*/
union _IoLtmChMapMsdrhsz{
	unsigned long		word;
	struct {
		unsigned long	sdrhsz		:10;
		unsigned long					:22;
	}bit;
};

/*	structure of msdrdef	(2841_3484h)	*/
union _IoLtmChMapMsdrdef{
	unsigned long		word;
	struct {
		unsigned long	sdrdef	:16;
		unsigned long				:16;
	}bit;
};

/*	structure of msdrvsz	(2841_3488h)	*/
union _IoLtmChMapMsdrvsz{
	unsigned long		word;
	struct {
		unsigned long	sdrvsz	:10;
		unsigned long				:22;
	}bit;
};

/*	structure of msdrad	(2841_348Ch)	*/
union _IoLtmChMapMsdrad{
	unsigned long		word;
	struct {
		unsigned long	sdrad	:32;
	}bit;
};

/*	structure of msdrofs	(2841_3490h)	*/
union _IoLtmChMapMsdrofs{
	unsigned long		word;
	struct {
		unsigned long				:2;
		unsigned long	sdrofs	:1;
		unsigned long				:29;
	}bit;
};

/*	structure of msdwadw0	(2841_3494h)	*/
union _IoLtmChMapMsdwadw0{
	unsigned long		word;
	struct {
		unsigned long	sdwadw0	:32;
	}bit;
};

/*	structure of msdwdefw0	(2841_3498h)	*/
union _IoLtmChMapMsdwdefw0{
	unsigned long		word;
	struct {
		unsigned long	sdwdefw0	:16;
		unsigned long						:16;
	}bit;
};

/*	structure of msdwadw1	(2841_349Ch)	*/
union _IoLtmChMapMsdwadw1{
	unsigned long		word;
	struct {
		unsigned long	sdwadw1		:32;
	}bit;
};

/*	structure of msdwdefw1	(2841_34A0h)	*/
union _IoLtmChMapMsdwdefw1{
	unsigned long		word;
	struct {
		unsigned long	sdwdefw1	:16;
		unsigned long						:16;
	}bit;
};

/*	structure of mioctl	(2841_34ACh)	*/
union _IoLtmChMapMioctl{
	unsigned long		word;
	struct {
		unsigned long	insel			:1;
		unsigned long					:3;
		unsigned long	r1dtyp		:2;
		unsigned long					:10;
		unsigned long	outen1		:1;
		unsigned long					:1;
		unsigned long	outen3		:1;
		unsigned long					:1;
		unsigned long	w0dtyp	:2;
		unsigned long	w1dtyp	:2;
		unsigned long					:2;
		unsigned long	w3dtyp	:2;
		unsigned long					:4;
	}bit;
};

/*	structure of gainr	(2841_34BCh)	*/
union _IoLtmChMapGainr{
	unsigned long		word;
	struct {
		unsigned long	gainr	:11;
		unsigned long				:21;
	}bit;
};

/*	structure of gaing	(2841_34C0h)	*/
union _IoLtmChMapGaing{
	unsigned long		word;
	struct {
		unsigned long	gaing	:11;
		unsigned long				:21;
	}bit;
};

/*	structure of gainb	(2841_34C4h)	*/
union _IoLtmChMapGainb{
	unsigned long		word;
	struct {
		unsigned long	gainb	:11;
		unsigned long				:21;
	}bit;
};

/*	structure of gaincpr	(2841_34C8h)	*/
union _IoLtmChMapGaincpr{
	unsigned long		word;
	struct {
		unsigned long	gaincpr	:12;
		unsigned long					:20;
	}bit;
};

/*	structure of gaincpg	(2841_34CCh)	*/
union _IoLtmChMapGaincpg{
	unsigned long		word;
	struct {
		unsigned long	gaincpg	:12;
		unsigned long					:20;
	}bit;
};

/*	structure of gaincpb	(2841_34D0h)	*/
union _IoLtmChMapGaincpb{
	unsigned long		word;
	struct {
		unsigned long	gaincpb	:12;
		unsigned long					:20;
	}bit;
};

/*	structure of peps0m	(2841_35CCh)	*/
union _IoLtmChMapPeps0m{
	unsigned long		word;
	struct {
		unsigned long	peps0m	:1;
		unsigned long					:31;
	}bit;
};

/*	structure of peps0of	(2841_35D4h)	*/
union _IoLtmChMapPeps0of{
	unsigned long		word;
	struct {
		unsigned long						:16;
		unsigned long	peps0of3		:12;
		unsigned long						:4;
	}bit;
};

/*	structure of peps1m	(2841_35E8h)	*/
union _IoLtmChMapPeps1m{
	unsigned long		word;
	struct {
		unsigned long	peps1m	:1;
		unsigned long					:31;
	}bit;
};

/*	structure of peps1of	(2841_35F4h)	*/
union _IoLtmChMapPeps1of{
	unsigned long		word;
	struct {
		unsigned long						:16;
		unsigned long	peps1of3		:12;
		unsigned long						:4;
	}bit;
};

/*	structure of peps2m	(2841_3608h)	*/
union _IoLtmChMapPeps2m{
	unsigned long		word;
	struct {
		unsigned long	peps2m	:1;
		unsigned long					:31;
	}bit;
};

/*	structure of peps2of	(2841_3614h)	*/
union _IoLtmChMapPeps2of{
	unsigned long		word;
	struct {
		unsigned long						:16;
		unsigned long	peps2of3		:12;
		unsigned long						:4;
	}bit;
};

/*	structure of neps0m	(2841_3628h)	*/
union _IoLtmChMapNeps0m{
	unsigned long		word;
	struct {
		unsigned long	neps0m	:1;
		unsigned long					:31;
	}bit;
};

/*	structure of neps0of	(2841_3634h)	*/
union _IoLtmChMapNeps0of{
	unsigned long		word;
	struct {
		unsigned long						:16;
		unsigned long	neps0of3		:12;
		unsigned long						:4;
	}bit;
};

/*	structure of neps1m	(2841_3648h)	*/
union _IoLtmChMapNeps1m{
	unsigned long		word;
	struct {
		unsigned long	neps1m	:1;
		unsigned long					:31;
	}bit;
};

/*	structure of neps1of	(2841_3654h)	*/
union _IoLtmChMapNeps1of{
	unsigned long		word;
	struct {
		unsigned long					:16;
		unsigned long	neps1of3	:12;
		unsigned long					:4;
	}bit;
};

/*	structure of neps2m	(2841_3668h)	*/
union _IoLtmChMapNeps2m{
	unsigned long		word;
	struct {
		unsigned long	neps2m	:1;
		unsigned long					:31;
	}bit;
};

/*	structure of neps2of	(2841_3674h)	*/
union _IoLtmChMapNeps2of{
	unsigned long		word;
	struct {
		unsigned long					:16;
		unsigned long	neps2of3	:12;
		unsigned long					:4;
	}bit;
};

/*	structure of yshadow	(2841_36A8h)	*/
union _IoLtmChMapYshadow{
	unsigned long		word;
	struct {
		unsigned long	yshadow	:14;
		unsigned long					:18;
	}bit;
};

/*	structure of yhighlight	(2841_36ACh)	*/
union _IoLtmChMapYhighlight{
	unsigned long		word;
	struct {
		unsigned long	yhighlight	:14;
		unsigned long						:18;
	}bit;
};

/*	structure of mylctl	(2841_36B0h)	*/
union _IoLtmChMapMylctl{
	unsigned long		word;
	struct {
		unsigned long	ylogsl	:1;
		unsigned long				:3;
		unsigned long	ylogsta	:1;
		unsigned long				:27;
	}bit;
};

/*	structure of mylog0ep0	(2841_36B4h)	*/
union _IoLtmChMapMylog0ep0{
	unsigned long		word;
	struct {
		unsigned long	ylog0ep0	:14;
		unsigned long					:18;
	}bit;
};

/*	structure of mylog0ep1	(2841_36B8h)	*/
union _IoLtmChMapMylog0ep1{
	unsigned long		word;
	struct {
		unsigned long	ylog0ep1	:14;
		unsigned long					:18;
	}bit;
};

/*	structure of mylog1ep0	(2841_36BCh)	*/
union _IoLtmChMapMylog1ep0{
	unsigned long		word;
	struct {
		unsigned long	ylog1ep0	:14;
		unsigned long					:18;
	}bit;
};

/*	structure of mylog1ep1	(2841_36C0h)	*/
union _IoLtmChMapMylog1ep1{
	unsigned long		word;
	struct {
		unsigned long	ylog1ep1	:14;
		unsigned long					:18;
	}bit;
};

/* Define i/o mapping */
struct _IoLtmChMap{
	/* JDSLTM */
	IoLtmChMapMapsr				mapsr;				/* 2841_(3400 - 3403h) */
	IoLtmChMapMsramen			msramen;		/* 2841_(3404 - 3407h) */
	IoLtmChMapMtrg					mtrg;				/* 2841_(3408 - 340Bh) */
	IoLtmChMapMfrstp				mfrstp;			/* 2841_(340C - 340Fh) */
	IoLtmChMapMparmsk			mparmsk;		/* 2841_(3410 - 3413h) */
	unsigned char 						dmy34143417[0x3418 - 0x3414];			/* 2841_(3414 - 3417h) */
	IoLtmChMapMhstini				mhstini;			/* 2841_(3418 - 341Bh) */
	IoLtmChMapMhcprd				mhcprd;			/* 2841_(341C - 341Fh) */
	unsigned char 						dmy34203423[0x3424 - 0x3420];			/* 2841_(3420 - 3423h) */
	IoLtmChMapMint0					mint0;				/* 2841_(3424 - 3427h) */
	IoLtmChMapMint1					mint1;				/* 2841_(3428 - 342Bh) */
	IoLtmChMapMlintlv				mlintlv;			/* 2841_(342C - 342Fh) */
	IoLtmChMapAxichsel				axichsel;			/* 2841_(3430 - 3433h) */
	IoLtmChMapMaxictlr				maxictlr;			/* 2841_(3434 - 3437h) */
	IoLtmChMapMaxirerr				maxirerr;			/* 2841_(3438 - 343Bh) */
	IoLtmChMapMaxictlw			maxictlw;		/* 2841_(343C - 343Fh) */
	IoLtmChMapMaxiwerr			maxiwerr;		/* 2841_(3440 - 3443h) */
	IoLtmChMapMaxibsiz			maxibsiz;			/* 2841_(3444 - 3447h) */
	unsigned char 						dmy3448347f[0x3480 - 0x3448];			/* 2841_(3448 - 347Fh) */
	IoLtmChMapMsdrhsz				msdrhsz;				/* 2841_(3480 - 3483h) */
	IoLtmChMapMsdrdef				msdrdef;				/* 2841_(3484 - 3487h) */
	IoLtmChMapMsdrvsz				msdrvsz;				/* 2841_(3488 - 348Bh) */
	IoLtmChMapMsdrad				msdrad;				/* 2841_(348C - 348Fh) */
	IoLtmChMapMsdrofs				msdrofs;				/* 2841_(3490 - 3493h) */
	IoLtmChMapMsdwadw0		msdwadw0;		/* 2841_(3494 - 3497h) */
	IoLtmChMapMsdwdefw0		msdwdefw0;		/* 2841_(3498 - 349Bh) */
	IoLtmChMapMsdwadw1		msdwadw1;		/* 2841_(349C - 349Fh) */
	IoLtmChMapMsdwdefw1		msdwdefw1;		/* 2841_(34A0 - 34A3h) */
	unsigned char 						dmy34a434ab[0x34AC - 0x34A4];			/* 2841_(34A4 - 34ABh) */
	IoLtmChMapMioctl				mioctl;					/* 2841_(34AC - 34AFh) */
	unsigned char 						dmy34b034bb[0x34BC - 0x34B0];			/* 2841_(34B0 - 34BBh) */
	IoLtmChMapGainr					gainr;					/* 2841_(34BC - 34BFh) */
	IoLtmChMapGaing					gaing;					/* 2841_(34C0 - 34C3h) */
	IoLtmChMapGainb					gainb;					/* 2841_(34C4 - 34C7h) */
	IoLtmChMapGaincpr				gaincpr;				/* 2841_(34C8 - 34CBh) */
	IoLtmChMapGaincpg				gaincpg;				/* 2841_(34CC - 34CFh) */
	IoLtmChMapGaincpb				gaincpb;				/* 2841_(34D0 - 34D3h) */
	unsigned char				 		dmy34d435cb[0x35CC - 0x34D4];			/* 2841_(34D4 - 35CBh) */
	IoLtmChMapPeps0m				peps0m;				/* 2841_(35CC - 35CFh) */
	unsigned char 						dmy35d035d3[0x35D4 - 0x35D0];			/* 2841_(35D0 - 35D3h) */
	IoLtmChMapPeps0of				peps0of;				/* 2841_(35D4 - 35D7h) */
	unsigned char 						dmy35d835e7[0x35E8 - 0x35D8];			/* 2841_(35D8 - 35E7h) */
	IoLtmChMapPeps1m				peps1m;				/* 2841_(35E8 - 35EBh) */
	unsigned char 						dmy35ec35f3[0x35F4 - 0x35EC];			/* 2841_(35EC - 35F3h) */
	IoLtmChMapPeps1of				peps1of;				/* 2841_(35F4 - 35F7h) */
	unsigned char 						dmy35f83607[0x3608 - 0x35F8];			/* 2841_(35F8 - 3607h) */
	IoLtmChMapPeps2m				peps2m;				/* 2841_(3608 - 360Bh) */
	unsigned char 						dmy360c3613[0x3614 - 0x360C];			/* 2841_(360C - 3613h) */
	IoLtmChMapPeps2of				peps2of;				/* 2841_(3614 - 3617h) */
	unsigned char 						dmy36183627[0x3628 - 0x3618];			/* 2841_(3618 - 3627h) */
	IoLtmChMapNeps0m				neps0m;				/* 2841_(3628 - 362Bh) */
	unsigned char					 	dmy362c3633[0x3634 - 0x362C];			/* 2841_(362C - 3633h) */
	IoLtmChMapNeps0of				neps0of;				/* 2841_(3634 - 3637h) */
	unsigned char 						dmy36383647[0x3648 - 0x3638];			/* 2841_(3638 - 3647h) */
	IoLtmChMapNeps1m				neps1m;			/* 2841_(3648 - 364Bh) */
	unsigned char 						dmy364c3653[0x3654 - 0x364C];			/* 2841_(364C - 3653h) */
	IoLtmChMapNeps1of				neps1of;			/* 2841_(3654 - 3657h) */
	unsigned char 						dmy36583667[0x3668 - 0x3658];			/* 2841_(3658 - 3667h) */
	IoLtmChMapNeps2m				neps2m;			/* 2841_(3668 - 366Bh) */
	unsigned char 						dmy366c3673[0x3674 - 0x366C];			/* 2841_(366C - 3673h) */
	IoLtmChMapNeps2of				neps2of;			/* 2841_(3674 - 3677h) */
	unsigned char 						dmy367836a7[0x36A8 - 0x3678];			/* 2841_(3678 - 36A7h) */
	IoLtmChMapYshadow			yshadow;			/* 2841_(36A8 - 36ABh) */
	IoLtmChMapYhighlight			yhighlight;		/* 2841_(36AC - 36AFh) */
	IoLtmChMapMylctl					mylctl;				/* 2841_(36B0 - 36B3h) */
	IoLtmChMapMylog0ep0		mylog0ep0;		/* 2841_(36B4 - 36B7h) */
	IoLtmChMapMylog0ep1		mylog0ep1;		/* 2841_(36B8 - 36BBh) */
	IoLtmChMapMylog1ep0		mylog1ep0;		/* 2841_(36BC - 36BFh) */
	IoLtmChMapMylog1ep1		mylog1ep1;		/* 2841_(36C0 - 36C3h) */
	unsigned char 						dmy36c437ff[0x3800 - 0x36C4];			/* 2841_(36C4 - 37FFh) */

};


#endif /* __JDSLTM1A_MAP_H__ */
