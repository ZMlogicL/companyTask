#ifndef __JDSCNR_OTF_REG_RW_H__
#define __JDSCNR_OTF_REG_RW_H__


#include "../Project/Image/src/kjdscnr1a.h"
///*	structure of sprsr	(2842_0000h)	*/
//union IoCnrOtfRegRwSprsr{
//	unsigned long		word;
//	struct {
//		unsigned long	sr	:1;
//		unsigned long		:31;
//	}bit;
//};
//
///*	structure of acesen (2842_0004h)	*/
//union IoCnrOtfRegRwAcesen{
//	unsigned long		word;
//	struct {
//		unsigned long	spracs	:1;
//		unsigned long			:31;
//	}bit;
//};
//
///*	structure of sprtrg (2842_0008h)	*/
//union IoCnrOtfRegRwSprtrg{
//	unsigned long		word;
//	struct {
//		unsigned long	sprtrg	:2;
//		unsigned long			:2;
//		unsigned long	cnrcse	:1;
//		unsigned long			:27;
//	}bit;
//};
//
///*	structure of sprice (2842_000Ch)	*/
//union IoCnrOtfRegRwSprice{
//	unsigned long		word;
//	struct {
//		unsigned long	spde	:1;
//		unsigned long			:3;
//		unsigned long	axie	:1;
//		unsigned long			:3;
//		unsigned long	drte	:1;
//		unsigned long			:23;
//	}bit;
//};
//
///*	structure of spricf (2842_0010h)	*/
//union IoCnrOtfRegRwSpricf{
//	unsigned long		word;
//	struct {
//		unsigned long	__spdf	:1;
//		unsigned long			:3;
//		unsigned long	__axif	:1;
//		unsigned long			:3;
//		unsigned long	__drtf	:1;
//		unsigned long			:23;
//	}bit;
//};
//
///*	structure of hdiv	(2842_0014h)	*/
//union IoCnrOtfRegRwHdiv{
//	unsigned long		word;
//	struct {
//		unsigned long	hdivl	:1;
//		unsigned long			:3;
//		unsigned long	hdivr	:1;
//		unsigned long			:27;
//	}bit;
//};
//
///*	structure of spraxiset	(2842_0020h)	*/
//union IoCnrOtfRegRwSpraxiset{
//	unsigned long		word;
//	struct {
//		unsigned long			:4;
//		unsigned long	awcache	:4;
//		unsigned long			:3;
//		unsigned long			:1;
//		unsigned long	awprot	:3;
//		unsigned long			:1;
//		unsigned long			:2;
//		unsigned long			:2;
//		unsigned long	wresp	:2;
//		unsigned long			:10;
//	}bit;
//};
//
///*	structure of sprmod (2842_0080h)	*/
//union IoCnrOtfRegRwSprmod{
//	unsigned long		word;
//	struct {
//		unsigned long	yuvMode	:3;
//		unsigned long				:1;
//		unsigned long	exmode		:1;
//		unsigned long				:3;
//		unsigned long	cnrvfm		:1;
//		unsigned long				:23;
//	}bit;
//};
//
///*	structure of hsize	(2842_0084h)	*/
//union IoCnrOtfRegRwHsize{
//	unsigned long		word;
//	struct {
//		unsigned long	hsize	:12;
//		unsigned long			:20;
//	}bit;
//};
//
///*	structure of vsize	(2842_0088h)	*/
//union IoCnrOtfRegRwVsize{
//	unsigned long		word;
//	struct {
//		unsigned long	vsize	:13;
//		unsigned long			:19;
//	}bit;
//};
//
///*	structure of wcta	(2842_00A0h)	*/
//union IoCnrOtfRegRwWcta{
//	unsigned long		word;
//	struct {
//		unsigned long	wcta	:32;
//	}bit;
//};
//
///*	structure of wcdef	(2842_00A4h)	*/
//union IoCnrOtfRegRwWcdef{
//	unsigned long		word;
//	struct {
//		unsigned long	wcdef	:18;
//		unsigned long			:14;
//	}bit;
//};
//
///*	structure of cnrwofsx	(2842_00A8h)	*/
//union IoCnrOtfRegRwCnrwofsx{
//	unsigned long		word;
//	struct {
//		unsigned long	cnrwofsx	:12;
//		unsigned long				:20;
//	}bit;
//};
//
///* Define i/o mapping */
//struct IoCnrOtfRegRw{
//	/* JDSIMG */
//	union  IoCnrOtfRegRwSprsr		sprsr;		/* 2842_(0000 - 0003h) */
//	union  IoCnrOtfRegRwAcesen		acesen;		/* 2842_(0004 - 0007h) */
//	union  IoCnrOtfRegRwSprtrg		sprtrg;		/* 2842_(0008 - 000Bh) */
//	union  IoCnrOtfRegRwSprice		sprice;		/* 2842_(000C - 000Fh) */
//	union  IoCnrOtfRegRwSpricf		spricf;		/* 2842_(0010 - 0013h) */
//	union  IoCnrOtfRegRwHdiv		hdiv;		/* 2842_(0014 - 0017h) */
//
//	unsigned char dmy0018001f[0x0020-0x0018];	/* 2842_(0018 - 001Fh) */
//
//	union  IoCnrOtfRegRwSpraxiset	spraxiset;	/* 2842_(0020 - 0023h) */
//
//	unsigned char dmy_0024_007F[0x0080-0x0024];	/* 2842_(0024 - 007Fh) */
//
//	union  IoCnrOtfRegRwSprmod		sprmod;		/* 2842_(0080 - 0083h) */
//	union  IoCnrOtfRegRwHsize		hsize;		/* 2842_(0084 - 0087h) */
//	union  IoCnrOtfRegRwVsize		vsize;		/* 2842_(0088 - 008Bh) */
//
//	unsigned char dmy_008C_009F[0x00A0-0x008C];	/* 2842_(008C - 009Fh) */
//
//	union  IoCnrOtfRegRwWcta		wcta;		/* 2842_(00A0 - 00A3h) */
//	union  IoCnrOtfRegRwWcdef		wcdef;		/* 2842_(00A4 - 00A7h) */
//	union  IoCnrOtfRegRwCnrwofsx	cnrwofsx;	/* 2842_(00A8 - 00ABh) */
//
//	unsigned char dmy_00AC_0FFF[0x1000-0x00AC];	/* 2842_(00AC - 0FFFh) */
//
//};

#endif	// #define __JDSCNR_OTF_REG_RW_H__
