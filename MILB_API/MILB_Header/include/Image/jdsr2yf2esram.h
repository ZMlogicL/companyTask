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
 * @file		_jdsr2y_f2e_sram.h
 * @brief		Definition JDSR2Y_F2E Macro I/O register
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */
#ifndef __JDSR2Y_F2E_SRAM_H__
#define __JDSR2Y_F2E_SRAM_H__


typedef union _IoR2ySramTc  					IoR2ySramTc;
typedef union _IoR2ySramTctdata 				IoR2ySramTctdata ;
typedef union _IoR2ySramTchsydata  		IoR2ySramTchsydata;
typedef union _IoR2ySramTchsrdata  		IoR2ySramTchsrdata;
typedef union _IoR2ySramTchsgdata  		IoR2ySramTchsgdata;
typedef union _IoR2ySramTchsbdata  		IoR2ySramTchsbdata;
typedef union _IoR2ySramGmrgbdf  			IoR2ySramGmrgbdf;
typedef union _IoR2ySramGmrdf  				IoR2ySramGmrdf;
typedef union _IoR2ySramGmgdf  			IoR2ySramGmgdf;
typedef union _IoR2ySramGmbdf  			IoR2ySramGmbdf;
typedef union _IoR2ySramGmybdf  			IoR2ySramGmybdf;
typedef union _IoR2ySramGmrgbfl  			IoR2ySramGmrgbfl;
typedef union _IoR2ySramGmrfl  				IoR2ySramGmrfl;
typedef union _IoR2ySramGmgfl  				IoR2ySramGmgfl;
typedef union _IoR2ySramGmbfl  				IoR2ySramGmbfl;
typedef union _IoR2ySramGmybfl 				IoR2ySramGmybfl;
typedef union _IoR2ySramEghwscl  			IoR2ySramEghwscl;
typedef union _IoR2ySramEghwton  			IoR2ySramEghwton;
typedef union _IoR2ySramEgmwscl  			IoR2ySramEgmwscl;
typedef union _IoR2ySramEgmwton  		IoR2ySramEgmwton;
typedef union _IoR2ySramEglwscl 				IoR2ySramEglwscl;
typedef union _IoR2ySramEglwton  			IoR2ySramEglwton;
typedef union _IoR2ySramEgmpscl  			IoR2ySramEgmpscl;
typedef union _IoR2ySramDkntbl  				IoR2ySramDkntbl;
typedef union _IoR2ySramHsty  					IoR2ySramHsty;
typedef struct _IoR2ySram  						IoR2ySram;


/*	structure of TC	(294A_0000h)	*/
union _IoR2ySramTc {
	unsigned short			hword[1024];
	struct {
		unsigned short		tc		:15;
		unsigned short				:1;
	}bit[1024];
};

/*	structure of tctdata	(294A_2000h)	*/
union _IoR2ySramTctdata {
	unsigned long		word[1200];
	struct {
		unsigned long	tctdata		:24;
		unsigned long					:8;
	}bit[1200];
};

/*	structure of tchsydata	(294A_4000h)	*/
union _IoR2ySramTchsydata {
	unsigned short			hword[4096];
	struct {
		unsigned short		tchsydata	:16;
	}bit[4096];
};

/*	structure of tchsrdata	(294A_6000h)	*/
union _IoR2ySramTchsrdata {
	unsigned short			hword[256];
	struct {
		unsigned short		tchsrdata	:16;
	}bit[256];
};

/*	structure of tchsgdata	(294A_6200h)	*/
union _IoR2ySramTchsgdata {
	unsigned short			hword[256];
	struct {
		unsigned short		tchsgdata	:16;
	}bit[256];
};

/*	structure of tchsbdata	(294A_6400h)	*/
union _IoR2ySramTchsbdata {
	unsigned short			hword[256];
	struct {
		unsigned short		tchsbdata	:16;
	}bit[256];
};

/*	structure of gmrgbdf	(294A_8000h)	*/
union _IoR2ySramGmrgbdf {
	unsigned long long			dword[256];
	struct {
		unsigned long long		gmrgbdf		:64;
	}bit[256];
};

/*	structure of gmrdf	(294A_8800h)	*/
union _IoR2ySramGmrdf{
	unsigned long long			dword[256];
	struct {
		unsigned long long		gmrdf		:64;
	}bit[256];
};

/*	structure of gmgdf	(294A_9000h)	*/
union _IoR2ySramGmgdf {
	unsigned long long			dword[256];
	struct {
		unsigned long long		gmgdf		:64;
	}bit[256];
};

/*	structure of gmbdf	(294A_9800h)	*/
union _IoR2ySramGmbdf {
	unsigned long long			dword[256];
	struct {
		unsigned long long		gmbdf		:64;
	}bit[256];
};

/*	structure of gmybdf	(294A_A000h)	*/
union _IoR2ySramGmybdf {
	unsigned long long			dword[256];
	struct {
		unsigned long long		gmybdf	:64;
	}bit[256];
};

/*	structure of gmrgbfl	(294A_A800h)	*/
union _IoR2ySramGmrgbfl {
	unsigned short					hword[256];
	struct {
		unsigned short				gmrgbfl	:10;
		unsigned short								:6;
	}bit[256];
};

/*	structure of gmrfl	(294A_AA00h)	*/
union _IoR2ySramGmrfl{
	unsigned short				hword[256];
	struct {
		unsigned short			gmrfl	:10;
		unsigned short						:6;
	}bit[256];
};

/*	structure of gmgfl	(294A_AC00h)	*/
union _IoR2ySramGmgfl {
	unsigned short				hword[256];
	struct {
		unsigned short			gmgfl		:10;
		unsigned short							:6;
	}bit[256];
};

/*	structure of gmbfl	(294A_AE00h)	*/
union _IoR2ySramGmbfl {
	unsigned short				hword[256];
	struct {
		unsigned short			gmbfl		:10;
		unsigned short							:6;
	}bit[256];
};

/*	structure of gmybfl	(294A_B000h)	*/
union _IoR2ySramGmybfl {
	unsigned short				hword[256];
	struct {
		unsigned short			gmybfl		:10;
		unsigned short							:6;
	}bit[256];
};

/*	structure of eghwscl	(294A_C000h)	*/
union _IoR2ySramEghwscl {
	unsigned char				byte[512];
	struct {
		unsigned char			eghwscl	:8;
	}bit[512];
};

/*	structure of eghwton	(294A_C200h)	*/
union _IoR2ySramEghwton{
	unsigned short				hword[256];
	struct {
		unsigned short			eghwton		:9;
		unsigned short								:7;
	}bit[256];
};

/*	structure of egmwscl	(294A_C400h)	*/
union _IoR2ySramEgmwscl{
	unsigned char				byte[512];
	struct {
		unsigned char			egmwscl	:8;
	}bit[512];
};

/*	structure of egmwton	(294A_C600h)	*/
union _IoR2ySramEgmwton {
	unsigned short				hword[256];
	struct {
		unsigned short			egmwton		:9;
		unsigned short								:7;
	}bit[256];
};

/*	structure of eglwscl	(294A_C800h)	*/
union _IoR2ySramEglwscl {
	unsigned char				byte[512];
	struct {
		unsigned char			eglwscl	:8;
	}bit[512];
};

/*	structure of eglwton	(294A_CA00h)	*/
union _IoR2ySramEglwton{
	unsigned short				hword[256];
	struct {
		unsigned short			eglwton	:9;
		unsigned short								:7;
	}bit[256];
};

/*	structure of egmpscl	(294A_CC00h)	*/
union _IoR2ySramEgmpscl {
	unsigned short				hword[13][17];
	struct {
		unsigned short			egmpscl		:10;
		unsigned short								:6;
	}bit[13][17];
};

/*	structure of dkntblr	(294A_E000h)	*/
/*	structure of dkntblg	(294A_E200h)	*/
/*	structure of dkntblb	(294A_E400h)	*/
union _IoR2ySramDkntbl {
	unsigned short				hword[256];
	struct {
		unsigned short			dkntbl		:12;
		unsigned short							:4;
	}bit[256];
};

/*	structure of hsty	(294A_F000h)	*/
union _IoR2ySramHsty {
	unsigned short				hword[128];
	struct {
		unsigned short			hsty		:15;
		unsigned short						:1;
	}bit[128];
};

/* Define i/o mapping */
struct _IoR2ySram {
	/* JDSR2Y */
	IoR2ySramTc					tc;			/* 294A_(0000 - 07FFh) */
	unsigned char 				dmy08001fff[0x2000-0x0800];	/* 294A_(0800 - 1FFFh) */
	IoR2ySramTctdata			tctdata;	/* 294A_(2000 - 32BFh) */
	unsigned char 				dmy32c03fff[0x4000-0x32C0];	/* 294A_(32C0 - 3FFFh) */
	IoR2ySramTchsydata		tchsydata;	/* 294A_(4000 - 5FFFh) */
	IoR2ySramTchsrdata		tchsrdata;	/* 294A_(6000 - 61FFh) */
	IoR2ySramTchsgdata		tchsgdata;	/* 294A_(6200 - 63FFh) */
	IoR2ySramTchsbdata		tchsbdata;	/* 294A_(6400 - 65FFh) */
	unsigned char 				dmy66007fff[0x8000-0x6600];	/* 294A_(6600 - 7FFFh) */
	IoR2ySramGmrgbdf		gmrgbdf;	/* 294A_(8000 - 87FFh) */
	IoR2ySramGmrdf			gmrdf;		/* 294A_(8800 - 8FFFh) */
	IoR2ySramGmgdf			gmgdf;		/* 294A_(9000 - 97FFh) */
	IoR2ySramGmbdf			gmbdf;		/* 294A_(9800 - 9FFFh) */
	IoR2ySramGmybdf			gmybdf;		/* 294A_(A000 - A7FFh) */
	IoR2ySramGmrgbfl		gmrgbfl;	/* 294A_(A800 - A9FFh) */
	IoR2ySramGmrfl				gmrfl;		/* 294A_(AA00 - ABFFh) */
	IoR2ySramGmgfl			gmgfl;		/* 294A_(AC00 - ADFFh) */
	IoR2ySramGmbfl			gmbfl;		/* 294A_(AE00 - AFFFh) */
	IoR2ySramGmybfl			gmybfl;		/* 294A_(B000 - B1FFh) */
	unsigned char 				dmyB200Bfff[0xC000-0xB200];	/* 294A_(B200 - BFFFh) */
	IoR2ySramEghwscl			eghwscl;	/* 294A_(C000 - C1FFh) */
	IoR2ySramEghwton		eghwton;	/* 294A_(C200 - C3FFh) */
	IoR2ySramEgmwscl		egmwscl;	/* 294A_(C400 - C5FFh) */
	IoR2ySramEgmwton		egmwton;	/* 294A_(C600 - C7FFh) */
	IoR2ySramEglwscl			eglwscl;	/* 294A_(C800 - C9FFh) */
	IoR2ySramEglwton			eglwton;	/* 294A_(CA00 - CBFFh) */
	IoR2ySramEgmpscl		egmpscl;	/* 294A_(CC00 - CDB9h) */
	unsigned char 				dmyCdbcDfff[0xE000-0xCDBA];	/* 294A_(CDBA - DFFFh) */
	IoR2ySramDkntbl			dkntblr;	/* 294A_(E000 - E1FFh) */
	IoR2ySramDkntbl			dkntblg;	/* 294A_(E200 - E3FFh) */
	IoR2ySramDkntbl			dkntblb;	/* 294A_(E400 - E5FFh) */
	unsigned char 				dmyE600Efff[0xF000-0xE600];	/* 294A_(E600 - EFFFh) */
	IoR2ySramHsty				hsty;		/* 294A_(F000 - F0FFh) */
	unsigned char 				dmy294af100294affff[0x294B0000-0x294AF100];	/* 294A_F100 - 294A_FFFFh */

};

extern volatile IoR2ySram		ioR2yTblP1;
extern volatile IoR2ySram		ioR2yTblP2;
extern volatile IoR2ySram		ioR2yTblP3;

#endif /* __JDSR2Y_F2E_SRAM_H__ */
