#ifndef __JDSCNR_OFL_REG_YSPR_H__
#define __JDSCNR_OFL_REG_YSPR_H__


#include "../Project/Image/src/kjdscnr1a.h"
///*	structure of yspren (2842_4000h)	*/
//union IoCnrOflRegYsprYspren{
//	unsigned long		word;
//	struct {
//		unsigned long	yspren	:1;
//		unsigned long			:31;
//	}bit;
//};
//
///*	structure of ysprmode	(2842_4004h)	*/
//union IoCnrOflRegYsprYsprmode{
//	unsigned long		word;
//	struct {
//		unsigned long	ysprmd	:1;
//		unsigned long			:3;
//		unsigned long	ysprfe	:2;
//		unsigned long			:26;
//	}bit;
//};
//
///*	structure of ysprfxey	(2842_4020h)	*/
//union IoCnrOflRegYsprYsprfxey{
//	unsigned long		word;
//	struct {
//		unsigned long	ysprfxeyh	:8;
//		unsigned long				:8;
//		unsigned long	ysprfxeyv	:8;
//		unsigned long				:8;
//	}bit;
//};
//
///*	structure of ysprfxec	(2842_4024h)	*/
//union IoCnrOflRegYsprYsprfxec{
//	unsigned long		word;
//	struct {
//		unsigned long	ysprfxech	:8;
//		unsigned long				:8;
//		unsigned long	ysprfxecv	:8;
//		unsigned long				:8;
//	}bit;
//};
//
///*	structure of yspralpbd	(2842_4028h)	*/
//union IoCnrOflRegYsprYspralpbd{
//	unsigned long		word;
//	struct {
//		unsigned long	yspralpbd	:5;
//		unsigned long				:27;
//	}bit;
//};
//
///*	structure of ysprdyeyof (2842_4030h)	*/
//union IoCnrOflRegYsprYsprdyeyof1{
//	unsigned long		word;
//	struct {
//		unsigned long	ysprdyeyof0	:8;
//		unsigned long	ysprdyeyof1	:8;
//		unsigned long	ysprdyeyof2	:8;
//		unsigned long	ysprdyeyof3	:8;
//	}bit;
//};
//union IoCnrOflRegYsprYsprdyeyof2{
//	unsigned long		word;
//	struct {
//		unsigned long	YSPRDYEYOF_4	:8;
//		unsigned long	YSPRDYEYOF_5	:8;
//		unsigned long					:16;
//	}bit;
//};
//struct IoCnrOflRegYsprYsprdyeyof{
//	union IoCnrOflRegYsprYsprdyeyof1	ysprdyeyof1;
//	union IoCnrOflRegYsprYsprdyeyof2	ysprdyeyof2;
//};
//
///*	structure of ysprdyeyga (2842_4038h)	*/
//union IoCnrOflRegYsprYsprdyeyga1{
//	unsigned long		word;
//	struct {
//		long			ysprdyeyga0	:8;
//		long			ysprdyeyga1	:8;
//		long			ysprdyeyga2	:8;
//		long			ysprdyeyga3	:8;
//	}bit;
//};
//union IoCnrOflRegYsprYsprdyeyga2{
//	unsigned long		word;
//	struct {
//		long			ysprdyeyga4	:8;
//		long			ysprdyeyga5	:8;
//		unsigned long					:16;
//	}bit;
//};
//struct IoCnrOflRegYsprYsprdyeyga{
//	union IoCnrOflRegYsprYsprdyeyga1	ysprdyeyga1;
//	union IoCnrOflRegYsprYsprdyeyga2	ysprdyeyga2;
//};
//
///*	structure of ysprdyeybd (2842_4040h)	*/
//union IoCnrOflRegYsprYsprdyeybd1{
//	unsigned long		word;
//	struct {
//		unsigned long	ysprdyeybd1	:8;
//		unsigned long	ysprdyeybd2	:8;
//		unsigned long	ysprdyeybd3	:8;
//		unsigned long	ysprdyeybd4	:8;
//	}bit;
//};
//union IoCnrOflRegYsprYsprdyeybd2{
//	unsigned long		word;
//	struct {
//		unsigned long	ysprdyeybd5	:8;
//		unsigned long					:24;
//	}bit;
//};
//struct IoCnrOflRegYsprYsprdyeybd{
//	union IoCnrOflRegYsprYsprdyeybd1	ysprdyeybd1;
//	union IoCnrOflRegYsprYsprdyeybd2	ysprdyeybd2;
//};
//
///* Define i/o mapping */
//struct IoCnrOflRegYspr{
//	/* JDSIMG */
//	union  IoCnrOflRegYsprYspren		yspren;		/* 2842_(4000 - 4003h) */
//	union  IoCnrOflRegYsprYsprmode		ysprmode;	/* 2842_(4004 - 4007h) */
//
//	unsigned char dmy_4008_401F[0x4020-0x4008];			/* 2842_(4008 - 401Fh) */
//
//	union  IoCnrOflRegYsprYsprfxey		ysprfxey;	/* 2842_(4020 - 4023h) */
//	union  IoCnrOflRegYsprYsprfxec		ysprfxec;	/* 2842_(4024 - 4027h) */
//	union  IoCnrOflRegYsprYspralpbd	yspralpbd;	/* 2842_(4028 - 402Bh) */
//
//	unsigned char dmy_402C_402F[0x4030-0x402C];			/* 2842_(402C - 402Fh) */
//
//	struct IoCnrOflRegYsprYsprdyeyof	ysprdyeyof;	/* 2842_(4030 - 4037h) */
//	struct IoCnrOflRegYsprYsprdyeyga	ysprdyeyga;	/* 2842_(4038 - 403Fh) */
//	struct IoCnrOflRegYsprYsprdyeybd	ysprdyeybd;	/* 2842_(4040 - 4047h) */
//
//	unsigned char dmy_4048_4FFF[0x5000-0x4048];			/* 2842_(4048 - 4FFFh) */
//
//};

#endif	// #define __JDSCNR_OFL_REG_YSPR_H__
