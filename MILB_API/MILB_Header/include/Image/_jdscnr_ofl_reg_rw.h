#ifndef __JDSCNR_OFL_REG_RW_H__
#define __JDSCNR_OFL_REG_RW_H__


#include "../Project/Image/src/kjdscnr1a.h"
///*	structure of sprsr	(2842_2000h)	*/
//union IoCnrOflRegRwSprsr{
//	unsigned long		word;
//	struct {
//		unsigned long	sr	:1;
//		unsigned long		:31;
//	}bit;
//};
//
///*	structure of acesen (2842_2004h)	*/
//union IoCnrOflRegRwAcesen{
//	unsigned long		word;
//	struct {
//		unsigned long	spracs	:1;
//		unsigned long			:31;
//	}bit;
//};
//
///*	structure of sprtrg (2842_2008h)	*/
//union IoCnrOflRegRwSprtrg{
//	unsigned long		word;
//	struct {
//		unsigned long	sprtrg	:2;
//		unsigned long			:30;
//	}bit;
//};
//
///*	structure of sprice (2842_200Ch)	*/
//union IoCnrOflRegRwSprice{
//	unsigned long		word;
//	struct {
//		unsigned long	spde	:1;
//		unsigned long			:3;
//		unsigned long	axie	:1;
//		unsigned long			:27;
//	}bit;
//};
//
///*	structure of spricf (2842_2010h)	*/
//union IoCnrOflRegRwSpricf{
//	unsigned long		word;
//	struct {
//		unsigned long	__spdf	:1;
//		unsigned long			:3;
//		unsigned long	__axif	:1;
//		unsigned long			:27;
//	}bit;
//};
//
///*	structure of VDIV	(2842_2014h)	*/
//union IoCnrOflRegRwVdiv{
//	unsigned long		word;
//	struct {
//		unsigned long	vdivt	:1;
//		unsigned long			:3;
//		unsigned long	vdivb	:1;
//		unsigned long			:27;
//	}bit;
//};
//
///*	structure of spraxiset	(2842_2020h)	*/
//union IoCnrOflRegRwSpraxiset{
//	unsigned long		word;
//	struct {
//		unsigned long	arcache	:4;
//		unsigned long	awcache	:4;
//		unsigned long	arprot	:3;
//		unsigned long			:1;
//		unsigned long	awprot	:3;
//		unsigned long			:1;
//		unsigned long	rresp	:2;
//		unsigned long			:2;
//		unsigned long	wresp	:2;
//		unsigned long			:10;
//	}bit;
//};
//
///*	structure of sprmod (2842_2080h)	*/
//union IoCnrOflRegRwSprmod{
//	unsigned long		word;
//	struct {
//		unsigned long	yuvMode	:3;
//		unsigned long				:29;
//	}bit;
//};
//
///*	structure of hsize	(2842_2084h)	*/
//union IoCnrOflRegRwHsize{
//	unsigned long		word;
//	struct {
//		unsigned long	hsize	:15;
//		unsigned long			:17;
//	}bit;
//};
//
///*	structure of vsize	(2842_2088h)	*/
//union IoCnrOflRegRwVsize{
//	unsigned long		word;
//	struct {
//		unsigned long	vsize	:15;
//		unsigned long			:17;
//	}bit;
//};
//
///*	structure of ryta	(2842_20A0h)	*/
//union IoCnrOflRegRwRyta{
//	unsigned long		word;
//	struct {
//		unsigned long	ryta	:32;
//	}bit;
//};
//
///*	structure of rydef	(2842_20A4h)	*/
//union IoCnrOflRegRwRydef{
//	unsigned long		word;
//	struct {
//		unsigned long	rydef	:18;
//		unsigned long			:14;
//	}bit;
//};
//
///*	structure of rcbta	(2842_20A8h)	*/
//union IoCnrOflRegRwRcbta{
//	unsigned long		word;
//	struct {
//		unsigned long	rcbta	:32;
//	}bit;
//};
//
///*	structure of rcrta	(2842_20ACh)	*/
//union IoCnrOflRegRwRcrta{
//	unsigned long		word;
//	struct {
//		unsigned long	rcrta	:32;
//	}bit;
//};
//
///*	structure of rcdef	(2842_20B0h)	*/
//union IoCnrOflRegRwRcdef{
//	unsigned long		word;
//	struct {
//		unsigned long	rcdef	:18;
//		unsigned long			:14;
//	}bit;
//};
//
///*	structure of wyta	(2842_20C0h)	*/
//union IoCnrOflRegRwWyta{
//	unsigned long		word;
//	struct {
//		unsigned long	wyta	:32;
//	}bit;
//};
//
///*	structure of wydef	(2842_20C4h)	*/
//union IoCnrOflRegRwWydef{
//	unsigned long		word;
//	struct {
//		unsigned long	wydef	:18;
//		unsigned long			:14;
//	}bit;
//};
//
///*	structure of wcbta	(2842_20C8h)	*/
//union IoCnrOflRegRwWcbta{
//	unsigned long		word;
//	struct {
//		unsigned long	wcbta	:32;
//	}bit;
//};
//
///*	structure of wcrta	(2842_20CCh)	*/
//union IoCnrOflRegRwWcrta{
//	unsigned long		word;
//	struct {
//		unsigned long	wcrta	:32;
//	}bit;
//};
//
///*	structure of wcdef	(2842_20D0h)	*/
//union IoCnrOflRegRwWcdef{
//	unsigned long		word;
//	struct {
//		unsigned long	wcdef	:18;
//		unsigned long			:14;
//	}bit;
//};
//
///*	structure of tmpta	(2842_20E0h)	*/
//union IoCnrOflRegRwTmpta{
//	unsigned long		word;
//	struct {
//		unsigned long	tmpta	:32;
//	}bit;
//};
//
///* Define i/o mapping */
//struct IoCnrOflRegRw{
//	/* JDSIMG */
//	union  IoCnrOflRegRwSprsr		sprsr;		/* 2842_(2000 - 2003h) */
//	union  IoCnrOflRegRwAcesen		acesen;		/* 2842_(2004 - 2007h) */
//	union  IoCnrOflRegRwSprtrg		sprtrg;		/* 2842_(2008 - 200Bh) */
//	union  IoCnrOflRegRwSprice		sprice;		/* 2842_(200C - 200Fh) */
//	union  IoCnrOflRegRwSpricf		spricf;		/* 2842_(2010 - 2013h) */
//	union  IoCnrOflRegRwVdiv		VDIV;		/* 2842_(2014 - 2017h) */
//
//	unsigned char dmy_2018_201F[0x2020-0x2018];		/* 2842_(2018 - 201Fh) */
//
//	union  IoCnrOflRegRwSpraxiset	spraxiset;	/* 2842_(2020 - 2023h) */
//
//	unsigned char dmy_2024_207F[0x2080-0x2024];		/* 2842_(2024 - 207Fh) */
//
//	union  IoCnrOflRegRwSprmod		sprmod;		/* 2842_(2080 - 2083h) */
//	union  IoCnrOflRegRwHsize		hsize;		/* 2842_(2084 - 2087h) */
//	union  IoCnrOflRegRwVsize		vsize;		/* 2842_(2088 - 208Bh) */
//
//	unsigned char dmy_208C_209F[0x20A0-0x208C];		/* 2842_(208C - 209Fh) */
//
//	union  IoCnrOflRegRwRyta		ryta;		/* 2842_(20A0 - 20A3h) */
//	union  IoCnrOflRegRwRydef		rydef;		/* 2842_(20A4 - 20A7h) */
//	union  IoCnrOflRegRwRcbta		rcbta;		/* 2842_(20A8 - 20ABh) */
//	union  IoCnrOflRegRwRcrta		rcrta;		/* 2842_(20AC - 20AFh) */
//	union  IoCnrOflRegRwRcdef		rcdef;		/* 2842_(20B0 - 20B3h) */
//
//	unsigned char dmy_20B4_20BF[0x20C0-0x20B4];		/* 2842_(20B4 - 20BFh) */
//
//	union  IoCnrOflRegRwWyta		wyta;		/* 2842_(20C0 - 20C3h) */
//	union  IoCnrOflRegRwWydef		wydef;		/* 2842_(20C4 - 20C7h) */
//	union  IoCnrOflRegRwWcbta		wcbta;		/* 2842_(20C8 - 20CBh) */
//	union  IoCnrOflRegRwWcrta		wcrta;		/* 2842_(20CC - 20CFh) */
//	union  IoCnrOflRegRwWcdef		wcdef;		/* 2842_(20D0 - 20D3h) */
//
//	unsigned char dmy_20D4_20DF[0x20E0-0x20D4];		/* 2842_(20D4 - 20DFh) */
//
//	union  IoCnrOflRegRwTmpta		tmpta;		/* 2842_(20E0 - 20E3h) */
//
//	unsigned char dmy_20E4_2FFF[0x3000-0x20E4];		/* 2842_(20E4 - 2FFFh) */
//
//};

#endif	// #define __JDSCNR_OFL_REG_RW_H__
