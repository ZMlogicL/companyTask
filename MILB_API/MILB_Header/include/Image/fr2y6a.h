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
 * @file		__fr2y6a.h
 * @brief		Definition FR2Y6A Macro I/O register
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */
#ifndef __FR2Y6A_H__
#define __FR2Y6A_H__


typedef union _IoR2yCntl   						 IoR2yCntl;
typedef union _IoR2yR2yflag  				 IoR2yR2yflag;
typedef union _IoR2yR2yinte  				 IoR2yR2yinte;
typedef union _IoR2yR2yintf  					 IoR2yR2yintf;
typedef union _IoR2yFltaen  					 IoR2yFltaen;
typedef union _IoR2yOfst   						 IoR2yOfst;
typedef union _IoR2yWbgar  					 IoR2yWbgar;
typedef union _IoR2yWblv   					 IoR2yWblv;
typedef union _IoR2yCc0ctl  					 IoR2yCc0ctl;
typedef union _IoR2yCc0k  						 IoR2yCc0k;
typedef union _IoR2yCc0ybof  				 IoR2yCc0ybof;
typedef union _IoR2yCc0ybga 				 IoR2yCc0ybga;
typedef union _IoR2yCc0ybbd 				 IoR2yCc0ybbd;
typedef union _IoR2yCcyc  						 IoR2yCcyc;
typedef union _IoR2yMcyc  					 IoR2yMcyc;
typedef union _IoR2yMcb1ab  				 IoR2yMcb1ab;
typedef union _IoR2yMcb1cd  				 IoR2yMcb1cd;
typedef union _IoR2yMcb2ab  				 IoR2yMcb2ab;
typedef union _IoR2yMcb2cd  				 IoR2yMcb2cd;
typedef union _IoR2yMcb3ab  				 IoR2yMcb3ab;
typedef union _IoR2yMcb3cd  				 IoR2yMcb3cd;
typedef union _IoR2yMcb4ab  				 IoR2yMcb4ab;
typedef union _IoR2yMcb4cd  				 IoR2yMcb4cd;
typedef union _IoR2yMcid1 					 IoR2yMcid1;
typedef union _IoR2yMcid2  					 IoR2yMcid2;
typedef union _IoR2yMcid3  					 IoR2yMcid3;
typedef union _IoR2yMcid4  					 IoR2yMcid4;
typedef union _IoR2yMckX  					 IoR2yMckX;
typedef struct _IoR2yMck  						 IoR2yMck;
typedef union _IoR2yMclX  						 IoR2yMclX;
typedef struct _IoR2yMcl  						 IoR2yMcl;
typedef union _IoR2yMcycbalp  				 IoR2yMcycbalp;
typedef union _IoR2yMcycbga  				 IoR2yMcycbga;
typedef union _IoR2yMcycbbd  				 IoR2yMcycbbd;
typedef union _IoR2yMcbabalp  			 IoR2yMcbabalp;
typedef union _IoR2yMcbabof  				 IoR2yMcbabof;
typedef union _IoR2yMcbabga  				 IoR2yMcbabga;
typedef union _IoR2yMcbabbd  				 IoR2yMcbabbd;
typedef union _IoR2yTcof  						 IoR2yTcof;
typedef union _IoR2yTctctl  					 IoR2yTctctl;
typedef union _IoR2yTctsta  					 IoR2yTctsta;
typedef union _IoR2yTctb  						 IoR2yTctb;
typedef union _IoR2yTchsctl  					 IoR2yTchsctl;
typedef union _IoR2yTchssta  				 IoR2yTchssta;
typedef union _IoR2yTchssiz 					 IoR2yTchssiz;
typedef union _IoR2yTchov  					 IoR2yTchov;
typedef union _IoR2yTcctl  						 IoR2yTcctl;
typedef union _IoR2yTcyc  						 IoR2yTcyc;
typedef union _IoR2yTcep  						 IoR2yTcep;
typedef union _IoR2yTcclpr  					 IoR2yTcclpr;
typedef union _IoR2yTcclpg  					 IoR2yTcclpg;
typedef union _IoR2yTcclpb  					 IoR2yTcclpb;
typedef union _IoR2yGmctl 					 IoR2yGmctl;
typedef union _IoR2yCc1ctl	 					 IoR2yCc1ctl;
typedef union _IoR2yCc1k  						 IoR2yCc1k;
typedef union _IoR2yCc1clpr  				 IoR2yCc1clpr;
typedef union _IoR2yCc1clpg  				 IoR2yCc1clpg;
typedef union _IoR2yCc1clpb  				 IoR2yCc1clpb;
typedef union _IoR2yYc  							 IoR2yYc;
typedef union _IoR2yYblend 					 IoR2yYblend;
typedef union _IoR2yNrctl  					 IoR2yNrctl;
typedef union _IoR2yNrof  						 IoR2yNrof;
typedef union _IoR2yNrga  					 IoR2yNrga;
typedef union _IoR2yNrbd  					 IoR2yNrbd;
typedef union _IoR2yEgsmctl  				 IoR2yEgsmctl;
typedef union _IoR2yEgsmtt  					 IoR2yEgsmtt;
typedef union _IoR2yEghwctl  				 IoR2yEghwctl;
typedef union _IoR2yEghwhpfk				 IoR2yEghwhpfk;
typedef union _IoR2yEghwcorpof  			 IoR2yEghwcorpof;
typedef union _IoR2yEghwcorpga  		 IoR2yEghwcorpga;
typedef union _IoR2yEghwcorpbd  		 IoR2yEghwcorpbd;
typedef union _IoR2yEghwcormof  		 IoR2yEghwcormof;
typedef union _IoR2yEghwcormga  		 IoR2yEghwcormga;
typedef union _IoR2yEghwcormbd  		 IoR2yEghwcormbd;
typedef union _IoR2yEghwsclsup  			 IoR2yEghwsclsup;
typedef union _IoR2yEghwclppof  			 IoR2yEghwclppof;
typedef union _IoR2yEghwclppga  		 IoR2yEghwclppga;
typedef union _IoR2yEghwclppbd			 IoR2yEghwclppbd;
typedef union _IoR2yEghwclpmof			 IoR2yEghwclpmof;
typedef union _IoR2yEghwclpmga			 IoR2yEghwclpmga;
typedef union _IoR2yEghwclpmbd			 IoR2yEghwclpmbd;
typedef union _IoR2yEgmwctl				 IoR2yEgmwctl;
typedef union _IoR2yEgmwhpfk				 IoR2yEgmwhpfk;
typedef union _IoR2yEgmwcorpof			 IoR2yEgmwcorpof;
typedef union _IoR2yEgmwcorpga			 IoR2yEgmwcorpga;
typedef union _IoR2yEgmwcorpbd		 IoR2yEgmwcorpbd;
typedef union _IoR2yEgmwcormof		 IoR2yEgmwcormof;
typedef union _IoR2yEgmwcormga		 IoR2yEgmwcormga;
typedef union _IoR2yEgmwcormbd		 IoR2yEgmwcormbd;
typedef union _IoR2yEgmwsclsup			 IoR2yEgmwsclsup;
typedef union _IoR2yEgmwclppof			 IoR2yEgmwclppof;
typedef union _IoR2yEgmwclppga			 IoR2yEgmwclppga;
typedef union _IoR2yEgmwclppbd			 IoR2yEgmwclppbd;
typedef union _IoR2yEgmwclpmof			 IoR2yEgmwclpmof;
typedef union _IoR2yEgmwclpmga		 IoR2yEgmwclpmga;
typedef union _IoR2yEgmwclpmbd 		 IoR2yEgmwclpmbd;
typedef union _IoR2yEglwctl					 IoR2yEglwctl;
typedef union _IoR2yEglwhpfk				 IoR2yEglwhpfk;
typedef union _IoR2yEglwcorpof			 IoR2yEglwcorpof;
typedef union _IoR2yEglwcorpga			 IoR2yEglwcorpga;
typedef union _IoR2yEglwcorpbd			 IoR2yEglwcorpbd;
typedef union _IoR2yEglwcormof			 IoR2yEglwcormof;
typedef union _IoR2yEglwcormga 			 IoR2yEglwcormga;
typedef union _IoR2yEglwcormbd			 IoR2yEglwcormbd;
typedef union _IoR2yEglwsclsup			 IoR2yEglwsclsup;
typedef union _IoR2yEglwclppof			 IoR2yEglwclppof;
typedef union _IoR2yEglwclppga			 IoR2yEglwclppga;
typedef union _IoR2yEglwclppbd 			 IoR2yEglwclppbd;
typedef union _IoR2yEglwclpmof			 IoR2yEglwclpmof;
typedef union _IoR2yEglwclpmga			 IoR2yEglwclpmga;
typedef union _IoR2yEglwclpmbd			 IoR2yEglwclpmbd;
typedef union _IoR2yEgdtctl					 IoR2yEgdtctl;
typedef union _IoR2yEgdthwth				 IoR2yEgdthwth;
typedef union _IoR2yEgdthwk				 IoR2yEgdthwk;
typedef union _IoR2yEgdtmwth				 IoR2yEgdtmwth;
typedef union _IoR2yEgdtmwk				 IoR2yEgdtmwk;
typedef union _IoR2yEgmpctl 				 IoR2yEgmpctl	;
typedef union _IoR2yEgmpsiz					 IoR2yEgmpsiz;
typedef union _IoR2yEgmpsizhinv			 IoR2yEgmpsizhinv;
typedef union _IoR2yEgmpsizvinv			 IoR2yEgmpsizvinv;
typedef union _IoR2yEgmpstaph			 IoR2yEgmpstaph;
typedef union _IoR2yEgmpstapv			 IoR2yEgmpstapv;
typedef union _IoR2yEgcmpctl				 IoR2yEgcmpctl;
typedef union _IoR2yEgcmpbd				 IoR2yEgcmpbd;
typedef union _IoR2yEgcmpalpof			 IoR2yEgcmpalpof;
typedef union _IoR2yEgcmpalpga			 IoR2yEgcmpalpga;
typedef union _IoR2yEgcmpbtaof			 IoR2yEgcmpbtaof;
typedef union _IoR2yEgcmpbtaga			 IoR2yEgcmpbtaga;
typedef union _IoR2yEgcmpclp				 IoR2yEgcmpclp;
typedef	union _IoR2yCrvaf 					 IoR2yCrvaf;
typedef union _IoR2yCrvbf						 IoR2yCrvbf;
typedef union _IoR2yEgcrvctl					 IoR2yEgcrvctl;
typedef union _IoR2yEgcrvasclof			 IoR2yEgcrvasclof;
typedef union _IoR2yEgcrvasclga			 IoR2yEgcrvasclga;
typedef union _IoR2yEgcrvasclbd			 IoR2yEgcrvasclbd;
typedef union _IoR2yEgcrvasclcp			 IoR2yEgcrvasclcp;
typedef union _IoR2yEgyasclga				 IoR2yEgyasclga;
typedef union _IoR2yEgyasclbd				 IoR2yEgyasclbd;
typedef union _IoR2yEgyasclclp				 IoR2yEgyasclclp;
typedef union _IoR2yEgcrvbsclof			 IoR2yEgcrvbsclof;
typedef union _IoR2yEgcrvbsclga			 IoR2yEgcrvbsclga;
typedef union _IoR2yEgcrvbsclbd			 IoR2yEgcrvbsclbd;
typedef union _IoR2yEgcrvbsclcp			 IoR2yEgcrvbsclcp;
typedef union _IoR2yEgybsclga				 IoR2yEgybsclga;
typedef union _IoR2yEgybsclbd				 IoR2yEgybsclbd;
typedef union _IoR2yEgybsclclp				 IoR2yEgybsclclp;
typedef union _IoR2yEgcrvclp					 IoR2yEgcrvclp;
typedef union _IoR2yYbcrvctl					 IoR2yYbcrvctl;
typedef union _IoR2yYbcrvaalpof			 IoR2yYbcrvaalpof;
typedef union _IoR2yYbcrvaalpga			 IoR2yYbcrvaalpga;
typedef union _IoR2yYbcrvaalpbd			 IoR2yYbcrvaalpbd;
typedef union _IoR2yYbcrvaalpcp			 IoR2yYbcrvaalpcp;
typedef union _IoR2yYbyaalpga				 IoR2yYbyaalpga;
typedef union _IoR2yYbyaalpbd	 			 IoR2yYbyaalpbd;
typedef	union _IoR2yYbyaalpclp			 IoR2yYbyaalpclp;
typedef union _IoR2yYbcrvbalpof			 IoR2yYbcrvbalpof;
typedef union _IoR2yYbcrvbalpga			 IoR2yYbcrvbalpga;
typedef union _IoR2yYbcrvbalpbd			 IoR2yYbcrvbalpbd;
typedef union _IoR2yYbcrvbalpcp			 IoR2yYbcrvbalpcp;
typedef union _IoR2yYbybalpga				 IoR2yYbybalpga;
typedef union _IoR2yYbybalpbd				 IoR2yYbybalpbd;
typedef union _IoR2yYbybalpclp			 IoR2yYbybalpclp;
typedef union _IoR2yClpfctl					 IoR2yClpfctl;
typedef union _IoR2yClpfk						 IoR2yClpfk;
typedef union _IoR2yClpfof	 					 IoR2yClpfof;
typedef union _IoR2yClpfga					 IoR2yClpfga;
typedef union _IoR2yClpfbd					 IoR2yClpfbd;
typedef union _IoR2yCsyctl						 IoR2yCsyctl;
typedef union _IoR2yCsyof						 IoR2yCsyof;
typedef union _IoR2yCsyga						 IoR2yCsyga;
typedef union _IoR2yCsybd						 IoR2yCsybd;
typedef union _IoR2yYcrvfx						 IoR2yYcrvfx;
typedef union _IoR2yCfix						 IoR2yCfix;
typedef union _IoR2yYcof						 IoR2yYcof;
typedef struct _IoR2yFr2yCntl					 IoR2yFr2yCntl;
typedef struct _IoR2yOfg							 IoR2yOfg;
typedef struct _IoR2yCca0						 IoR2yCca0;
typedef struct _IoR2yMcc						 IoR2yMcc;
typedef struct _IoR2yBtc							 IoR2yBtc;
typedef struct _IoR2yTcArea					 IoR2yTcArea;
typedef struct _IoR2yGam						 IoR2yGam;
typedef struct _IoR2yCca1						 IoR2yCca1;
typedef struct _IoR2yYcArea					 IoR2yYcArea;
typedef struct _IoR2yYnr							 IoR2yYnr;
typedef struct _IoR2yEgsm						 IoR2yEgsm;
typedef struct _IoR2yEghw						 IoR2yEghw;
typedef struct _IoR2yEgmw						 IoR2yEgmw;
typedef struct _IoR2yEglw						 IoR2yEglw;
typedef struct _IoR2yEgdt					 	 IoR2yEgdt;
typedef struct _IoR2yMapscl  					 IoR2yMapscl;
typedef struct _IoR2yEgcmp   				 IoR2yEgcmp;
typedef struct _IoR2yCrv  						 IoR2yCrv;
typedef struct _IoR2yEgcrv  					 IoR2yEgcrv;
typedef struct _IoR2yYbcrv  				 	 IoR2yYbcrv;
typedef struct _IoR2yClpf    					 IoR2yClpf;
typedef struct _IoR2yCsp  						 IoR2yCsp;
typedef struct _IoR2yFr2y  						 IoR2yFr2y;


/*	structure of cntl	(2841_8000h)	*/
union _IoR2yCntl {
	unsigned long		word;
	struct {
		unsigned long				:8;
		unsigned long	trg		:2;
		unsigned long				:22;
	}bit;
};

/*	structure of r2yflag	(2841_8004h)	*/
union _IoR2yR2yflag {
	unsigned long		word;
	struct {
		unsigned long	tcact		:1;
		unsigned long	gamact	:1;
		unsigned long	ycfact		:1;
		unsigned long					:5;
		unsigned long	tchact		:1;
		unsigned long	tctact		:1;
		unsigned long					:22;
	}bit;
};

/*	structure of r2yinte	(2841_8008h)	*/
union _IoR2yR2yinte {
	unsigned long		word;
	struct {
		unsigned long	ycfere		:1;
		unsigned long					:3;
		unsigned long	tctee		:1;
		unsigned long					:3;
		unsigned long	tchsee		:1;
		unsigned long					:23;
	}bit;
};

/*	structure of r2yintf	(2841_800Ch)	*/
union _IoR2yR2yintf {
	unsigned long		word;
	struct {
		unsigned long	__ycferf	:1;
		unsigned long					:3;
		unsigned long	__tctef		:1;
		unsigned long					:3;
		unsigned long	__tchsef	:1;
		unsigned long					:23;
	}bit;
};

/*	structure of fltaen	(2841_8010h)	*/
union _IoR2yFltaen {
	unsigned long		word;
	struct {
		unsigned long	ycfaen		:1;
		unsigned long					:31;
	}bit;
};

/*	structure of ofst	(2841_8020h)	*/
union _IoR2yOfst {
	unsigned long		word[2];
	struct {
		long					ofstr			:10;
		unsigned long					:6;
		long					ofstg		:10;
		unsigned long					:6;
		long					ofstb		:10;
		unsigned long					:22;
	}bit;
};

/*	structure of wbgar	(2841_8028h)	*/
union _IoR2yWbgar {
	unsigned long		word[2];
	struct {
		unsigned long	wbgar	:11;
		unsigned long				:5;
		unsigned long	wbgag	:11;
		unsigned long				:5;
		unsigned long	wbgab	:11;
		unsigned long				:21;
	}bit;
};

/*	structure of wblv	(2841_8030h)	*/
union _IoR2yWblv {
	unsigned long		word[2];
	struct {
		unsigned long	wblvr	:12;
		unsigned long				:4;
		unsigned long	wblvg	:12;
		unsigned long				:4;
		unsigned long	wblvb	:12;
		unsigned long				:20;
	}bit;
};

/*	structure of cc0ctl	(2841_8080h)	*/
union _IoR2yCc0ctl{
	unsigned long		word;
	struct {
		unsigned long	cc0dp	:2;
		unsigned long				:30;
	}bit;
};

/*	structure of cc0k	(2841_80A0h)	*/
union _IoR2yCc0k{
	unsigned long		word[5];
	struct {
		long					cc0k00			:12;
		unsigned long						:4;
		long					cc0k01			:12;
		unsigned long						:4;
		long					cc0k02			:12;
		unsigned long						:4;
		long					cc0k10			:12;
		unsigned long						:4;
		long					cc0k11			:12;
		unsigned long						:4;
		long					cc0k12			:12;
		unsigned long						:4;
		long					cc0k20			:12;
		unsigned long						:4;
		long					cc0k21			:12;
		unsigned long						:4;
		long					cc0k22			:12;
		unsigned long						:20;
	}bit;
};

/*	structure of cc0ybof	(2841_80C0h)	*/
union _IoR2yCc0ybof{
	unsigned long		word[2];
	struct {
		unsigned long	cc0ybof0	:11;
		unsigned long					:5;
		unsigned long	cc0ybof1	:11;
		unsigned long					:5;
		unsigned long	cc0ybof2	:11;
		unsigned long					:21;
	}bit;
};

/*	structure of cc0ybga	(2841_80C8h)	*/
union _IoR2yCc0ybga{
	unsigned long		word[2];
	struct {
		long					cc0ybga0		:9;
		unsigned long						:7;
		long					cc0ybga1		:9;
		unsigned long						:7;
		long					cc0ybga2		:9;
		unsigned long						:23;
	}bit;
};

/*	structure of cc0ybbd	(2841_80D0h)	*/
union _IoR2yCc0ybbd {
	unsigned long		word;
	struct {
		unsigned long	cc0ybbd1	:12;
		unsigned long						:4;
		unsigned long	cc0ybbd2	:12;
		unsigned long						:4;
	}bit;
};

/*	structure of ccyc	(2841_80D4h)	*/
union _IoR2yCcyc{
	unsigned long		word;
	struct {
		unsigned long	ccyc00	:8;
		unsigned long	ccyc01	:8;
		unsigned long	ccyc02	:8;
		unsigned long				:8;
	}bit;
};

/*	structure of mcyc	(2841_9000h)	*/
union _IoR2yMcyc{
	unsigned long		word[5];
	struct {
		long					mcyc00	:9;
		unsigned long					:7;
		long					mcyc01	:9;
		unsigned long					:7;
		long					mcyc02	:9;
		unsigned long					:7;
		long					mcyc10	:9;
		unsigned long					:7;
		long					mcyc11	:9;
		unsigned long					:7;
		long					mcyc12	:9;
		unsigned long					:7;
		long					mcyc20	:9;
		unsigned long					:7;
		long					mcyc21	:9;
		unsigned long					:7;
		long					mcyc22	:9;
		unsigned long					:23;
	}bit;
};

/*	structure of mcb1ab	(2841_9020h)	*/
union _IoR2yMcb1ab{
	unsigned long		word;
	struct {
		unsigned long	mcb1a	:12;
		unsigned long				:4;
		unsigned long	mcb1b	:12;
		unsigned long				:4;
	}bit;
};

/*	structure of mcb1cd	(2841_9024h)	*/
union _IoR2yMcb1cd{
	unsigned long		word;
	struct {
		unsigned long	mcb1c	:12;
		unsigned long				:4;
		unsigned long	mcb1d	:12;
		unsigned long				:4;
	}bit;
};

/*	structure of mcb2ab	(2841_9028h)	*/
union _IoR2yMcb2ab{
	unsigned long		word;
	struct {
		unsigned long	mcb2a	:12;
		unsigned long				:4;
		unsigned long	mcb2b	:12;
		unsigned long				:4;
	}bit;
};

/*	structure of mcb2cd	(2841_902Ch)	*/
union _IoR2yMcb2cd{
	unsigned long		word;
	struct {
		unsigned long	mcb2c	:12;
		unsigned long				:4;
		unsigned long	mcb2d	:12;
		unsigned long				:4;
	}bit;
};

/*	structure of mcb3ab	(2841_9030h)	*/
union _IoR2yMcb3ab{
	unsigned long		word;
	struct {
		unsigned long	mcb3a	:12;
		unsigned long				:4;
		unsigned long	mcb3b	:12;
		unsigned long				:4;
	}bit;
};

/*	structure of mcb3cd	(2841_9034h)	*/
union _IoR2yMcb3cd{
	unsigned long		word;
	struct {
		unsigned long	mcb3c	:12;
		unsigned long				:4;
		unsigned long	mcb3d	:12;
		unsigned long				:4;
	}bit;
};

/*	structure of mcb4ab	(2841_9038h)	*/
union _IoR2yMcb4ab{
	unsigned long		word;
	struct {
		unsigned long	mcb4a	:12;
		unsigned long				:4;
		unsigned long	mcb4b	:12;
		unsigned long				:4;
	}bit;
};

/*	structure of mcb4cd	(2841_903Ch)	*/
union _IoR2yMcb4cd{
	unsigned long		word;
	struct {
		unsigned long	mcb4c	:12;
		unsigned long				:4;
		unsigned long	mcb4d	:12;
		unsigned long				:4;
	}bit;
};

/*	structure of mcid1	(2841_9040h)	*/
union _IoR2yMcid1{
	unsigned long		word;
	struct {
		unsigned long	mcid1a	:4;
		unsigned long	mcid1b	:4;
		unsigned long	mcid1c	:4;
		unsigned long	mcid1d	:4;
		unsigned long	mcid1e	:4;
		unsigned long					:12;
	}bit;
};

/*	structure of mcid2	(2841_9044h)	*/
union _IoR2yMcid2{
	unsigned long		word;
	struct {
		unsigned long	mcid2a	:4;
		unsigned long	mcid2b	:4;
		unsigned long	mcid2c	:4;
		unsigned long	mcid2d	:4;
		unsigned long	mcid2e	:4;
		unsigned long					:12;
	}bit;
};

/*	structure of mcid3	(2841_9048h)	*/
union _IoR2yMcid3{
	unsigned long		word;
	struct {
		unsigned long	mcid3a	:4;
		unsigned long	mcid3b	:4;
		unsigned long	mcid3c	:4;
		unsigned long	mcid3d	:4;
		unsigned long	mcid3e	:4;
		unsigned long					:12;
	}bit;
};

/*	structure of mcid4	(2841_904Ch)	*/
union _IoR2yMcid4{
	unsigned long		word;
	struct {
		unsigned long	mcid4a	:4;
		unsigned long	mcid4b	:4;
		unsigned long	mcid4c	:4;
		unsigned long	mcid4d	:4;
		unsigned long	mcid4e	:4;
		unsigned long					:12;
	}bit;
};

/*	structure of mcka	(2841_9080h)	*/
/*	structure of mckb	(2841_9100h)	*/
/*	structure of mckc	(2841_9180h)	*/
/*	structure of mckd	(2841_9200h)	*/
/*	structure of mcke	(2841_9280h)	*/
/*	structure of mckf	(2841_9300h)	*/
/*	structure of mckg	(2841_9380h)	*/
/*	structure of mckh	(2841_9400h)	*/
/*	structure of mcki	(2841_9480h)	*/
/*	structure of mckj	(2841_9500h)	*/
/*	structure of mckk	(2841_9580h)	*/
/*	structure of mckl	(2841_9600h)	*/
union _IoR2yMckX{
	unsigned long		word[5];
	struct {
		long					mck00			:12;
		unsigned long						:4;
		long					mck01			:12;
		unsigned long						:4;
		long					mck02			:12;
		unsigned long						:4;
		long					mck10			:12;
		unsigned long						:4;
		long					mck11			:12;
		unsigned long						:4;
		long					mck12			:12;
		unsigned long						:4;
		long					mck20			:12;
		unsigned long						:4;
		long					mck21			:12;
		unsigned long						:4;
		long					mck22			:12;
		unsigned long						:20;
	}bit;
};

struct _IoR2yMck{
	IoR2yMckX	mck0;
	IoR2yMckX	mck1;
	IoR2yMckX	mck2;
	IoR2yMckX	mck3;
	IoR2yMckX	mck4;
};

/*	structure of mcla	(2841_9680h)	*/
/*	structure of mclb	(2841_96C0h)	*/
/*	structure of mclc	(2841_9700h)	*/
/*	structure of mcld	(2841_9740h)	*/
/*	structure of mcle	(2841_9780h)	*/
/*	structure of mclf	(2841_97C0h)	*/
/*	structure of mclg	(2841_9800h)	*/
/*	structure of mclh	(2841_9840h)	*/
/*	structure of mcli	(2841_9880h)	*/
/*	structure of mclj	(2841_98C0h)	*/
/*	structure of mclk	(2841_9900h)	*/
/*	structure of mcll	(2841_9940h)	*/
union _IoR2yMclX{
	unsigned long		word[3];
	struct {
		long					mcl00			:10;
		unsigned long						:6;
		long					mcl01			:10;
		unsigned long						:6;
		long					mcl10			:10;
		unsigned long						:6;
		long					mcl11			:10;
		unsigned long						:6;
		long					mcl20			:10;
		unsigned long						:6;
		long					mcl21			:10;
		unsigned long						:6;
	}bit;
};
struct _IoR2yMcl{
	IoR2yMclX	mcl0;
	IoR2yMclX	mcl1;
	IoR2yMclX	mcl2;
	IoR2yMclX	mcl3;
	IoR2yMclX	mcl4;
};

/*	structure of mcycbalp	(2841_9980h)	*/
union _IoR2yMcycbalp{
	unsigned long		word;
	struct {
		unsigned long	mcycbalp	:6;
		unsigned long						:26;
	}bit;
};

/*	structure of mcycbga	(2841_9988h)	*/
union _IoR2yMcycbga{
	unsigned long		word[2];
	struct {
		unsigned long	mcycbga1	:12;
		unsigned long						:4;
		unsigned long	mcycbga2	:12;
		unsigned long						:4;
		unsigned long	mcycbga3	:12;
		unsigned long						:4;
		unsigned long	mcycbga4	:12;
		unsigned long						:4;
	}bit;
};

/*	structure of mcycbbd	(2841_9990h)	*/
union _IoR2yMcycbbd{
	unsigned long		word[2];
	struct {
		unsigned long	mcycbbd1	:12;
		unsigned long						:4;
		unsigned long	mcycbbd2	:12;
		unsigned long						:4;
		unsigned long	mcycbbd3	:12;
		unsigned long						:4;
		unsigned long	mcycbbd4	:12;
		unsigned long						:4;
	}bit;
};

/*	structure of mcbabalp	(2841_9998h)	*/
union _IoR2yMcbabalp{
	unsigned long		word;
	struct {
		unsigned long	mcbabalp	:6;
		unsigned long						:26;
	}bit;
};

/*	structure of mcbabof	(2841_99A0h)	*/
union _IoR2yMcbabof{
	unsigned long		word[2];
	struct {
		unsigned long	mcbabof0	:11;
		unsigned long						:5;
		unsigned long	mcbabof1	:11;
		unsigned long						:5;
		unsigned long	mcbabof2	:11;
		unsigned long						:5;
		unsigned long	mcbabof3	:11;
		unsigned long						:5;
	}bit;
};

/*	structure of mcbabga	(2841_99A8h)	*/
union _IoR2yMcbabga{
	unsigned long		word[2];
	struct {
		long					mcbabga0	:9;
		unsigned long						:7;
		long					mcbabga1	:9;
		unsigned long						:7;
		long					mcbabga2	:9;
		unsigned long						:7;
		long					mcbabga3	:9;
		unsigned long						:7;
	}bit;
};

/*	structure of mcbabbd	(2841_99B0h)	*/
union _IoR2yMcbabbd{
	unsigned long		word[2];
	struct {
		unsigned long	mcbabbd1	:12;
		unsigned long						:4;
		unsigned long	mcbabbd2	:12;
		unsigned long						:4;
		unsigned long	mcbabbd3	:12;
		unsigned long						:20;
	}bit;
};

/*	structure of tcof	(2841_A000h)	*/
union _IoR2yTcof{
	unsigned long		word[2];
	struct {
		long					tcofr			:10;
		unsigned long					:6;
		long					tcofg		:10;
		unsigned long					:6;
		long					tcofb		:10;
		unsigned long					:6;
		long					tcofyb		:10;
		unsigned long					:6;
	}bit;
};

/*	structure of tctctl	(2841_A008h)	*/
union _IoR2yTctctl{
	unsigned long		word;
	struct {
		unsigned long	tcten	:1;
		unsigned long				:3;
		unsigned long	tctaen	:1;
		unsigned long				:27;
	}bit;
};

/*	structure of tctsta	(2841_A00Ch)	*/
union _IoR2yTctsta{
	unsigned long		word;
	struct {
		unsigned long	tcthsta	:12;
		unsigned long				:4;
		unsigned long	tctvsta	:14;
		unsigned long				:2;
	}bit;
};

/*	structure of tctb	(2841_A010h)	*/
union _IoR2yTctb{
	unsigned long		word;
	struct {
		unsigned long	tctbhsiz		:8;
		unsigned long	tctbvsiz		:8;
		unsigned long	tctbhnum	:6;
		unsigned long						:2;
		unsigned long	tctbvnum	:5;
		unsigned long						:3;
	}bit;
};

/*	structure of tchsctl	(2841_A014h)	*/
union _IoR2yTchsctl{
	unsigned long		word;
	struct {
		unsigned long	tchsen			:1;
		unsigned long						:3;
		unsigned long	tchaen			:1;
		unsigned long						:3;
		unsigned long	tchshcyc		:2;
		unsigned long						:2;
		unsigned long	tchsvcyc		:3;
		unsigned long						:1;
		unsigned long	tchsrgbmd	:3;
		unsigned long						:1;
		unsigned long	tchsmn		:1;
		unsigned long						:11;
	}bit;
};

/*	structure of tchssta	(2841_A018h)	*/
union _IoR2yTchssta{
	unsigned long		word;
	struct {
		unsigned long	tchshsta	:12;
		unsigned long					:4;
		unsigned long	tchsvsta	:14;
		unsigned long					:2;
	}bit;
};

/*	structure of tchssiz	(2841_A01Ch)	*/
union _IoR2yTchssiz{
	unsigned long		word;
	struct {
		unsigned long	tchshsiz	:12;
		unsigned long					:4;
		unsigned long	tchsvsiz	:14;
		unsigned long					:2;
	}bit;
};

/*	structure of tchov	(2841_A020h)	*/
union _IoR2yTchov{
	unsigned long		word;
	struct {
		unsigned long	tchyov	:1;
		unsigned long				:3;
		unsigned long	tchrov	:1;
		unsigned long				:3;
		unsigned long	tchgov	:1;
		unsigned long				:3;
		unsigned long	tchbov	:1;
		unsigned long				:19;
	}bit;
};

/*	structure of tcctl	(2841_A040h)	*/
union _IoR2yTcctl{
	unsigned long		word;
	struct {
		unsigned long	tcen			:1;
		unsigned long	tcyben		:1;
		unsigned long	tcblen		:1;
		unsigned long					:1;
		unsigned long	tcaen		:1;
		unsigned long					:3;
		unsigned long	tcres		:2;
		unsigned long					:2;
		unsigned long	tctbl			:2;
		unsigned long					:2;
		unsigned long	tcyout		:1;
		unsigned long					:3;
		unsigned long	tcintbit		:2;
		unsigned long					:2;
		unsigned long	tcblnd		:5;
		unsigned long					:3;
	}bit;
};

/*	structure of tcyc	(2841_A044h)	*/
union _IoR2yTcyc{
	unsigned long		word;
	struct {
		unsigned long	tcyc00	:8;
		unsigned long	tcyc01	:8;
		unsigned long	tcyc02	:8;
		unsigned long				:8;
	}bit;
};

/*	structure of tcep	(2841_A048h)	*/
union _IoR2yTcep{
	unsigned long		word[2];
	struct {
		unsigned long	tcep0	:15;
		unsigned long				:1;
		unsigned long	tcep1	:15;
		unsigned long				:1;
		unsigned long	tcep2	:15;
		unsigned long				:1;
		unsigned long	tcep3	:15;
		unsigned long				:1;
	}bit;
};

/*	structure of tcclpr	(2841_A050h)	*/
union _IoR2yTcclpr{
	unsigned long		word;
	struct {
		unsigned long	tcclprp		:12;
		unsigned long					:4;
		unsigned long	tcclprm	:12;
		unsigned long					:4;
	}bit;
};

/*	structure of tcclpg	(2841_A054h)	*/
union _IoR2yTcclpg{
	unsigned long		word;
	struct {
		unsigned long	tcclpgp	:12;
		unsigned long					:4;
		unsigned long	tcclpgm	:12;
		unsigned long					:4;
	}bit;
};

/*	structure of tcclpb	(2841_A058h)	*/
union _IoR2yTcclpb{
	unsigned long		word;
	struct {
		unsigned long	tcclpbp	:12;
		unsigned long					:4;
		unsigned long	tcclpbm	:12;
		unsigned long					:4;
	}bit;
};

/*	structure of gmctl	(2841_A060h)	*/
union _IoR2yGmctl{
	unsigned long		word;
	struct {
		unsigned long	gmen		:1;
		unsigned long	gmmd		:1;
		unsigned long					:2;
		unsigned long	gmaen		:1;
		unsigned long	gmyaen	:1;
		unsigned long					:2;
		unsigned long	gamsw		:1;
		unsigned long					:23;
	}bit;
};

/*	structure of cc1ctl	(2841_A080h)	*/
union _IoR2yCc1ctl{
	unsigned long		word;
	struct {
		unsigned long	cc1dp	:2;
		unsigned long				:30;
	}bit;
};

/*	structure of cc1k	(2841_A0A0h)	*/
union _IoR2yCc1k{
	unsigned long		word[5];
	struct {
		long					cc1k00			:12;
		unsigned long						:4;
		long					cc1k01			:12;
		unsigned long						:4;
		long					cc1k02			:12;
		unsigned long						:4;
		long					cc1k10			:12;
		unsigned long						:4;
		long					cc1k11			:12;
		unsigned long						:4;
		long					cc1k12			:12;
		unsigned long						:4;
		long					cc1k20			:12;
		unsigned long						:4;
		long					cc1k21			:12;
		unsigned long						:4;
		long					cc1k22			:12;
		unsigned long						:20;
	}bit;
};

/*	structure of cc1clpr	(2841_A0C0h)	*/
union _IoR2yCc1clpr{
	unsigned long		word;
	struct {
		unsigned long	cc1clprp	:12;
		unsigned long					:4;
		unsigned long	cc1clprm	:12;
		unsigned long					:4;
	}bit;
};

/*	structure of cc1clpg	(2841_A0C4h)	*/
union _IoR2yCc1clpg{
	unsigned long		word;
	struct {
		unsigned long	cc1clpgp		:12;
		unsigned long						:4;
		unsigned long	cc1clpgm	:12;
		unsigned long						:4;
	}bit;
};

/*	structure of cc1clpb	(2841_A0C8h)	*/
union _IoR2yCc1clpb{
	unsigned long		word;
	struct {
		unsigned long	cc1clpbp		:12;
		unsigned long						:4;
		unsigned long	cc1clpbm	:12;
		unsigned long						:4;
	}bit;
};

/*	structure of yc	(2841_A100h)	*/
union _IoR2yYc{
	unsigned long		word[5];
	struct {
		long					yc00			:9;
		unsigned long					:7;
		long					yc01			:9;
		unsigned long					:7;
		long					yc02			:9;
		unsigned long					:7;
		long					yc10			:9;
		unsigned long					:7;
		long					yc11			:9;
		unsigned long					:7;
		long					yc12			:9;
		unsigned long					:7;
		long					yc20			:9;
		unsigned long					:7;
		long					yc21			:9;
		unsigned long					:7;
		long					yc22			:9;
		unsigned long					:23;
	}bit;
};

/*	structure of yblend	(2841_A120h)	*/
union _IoR2yYblend{
	unsigned long		word;
	struct {
		unsigned long	yyblnd	:6;
		unsigned long				:2;
		unsigned long	ybblnd	:6;
		unsigned long				:18;
	}bit;
};

/*	structure of nrctl	(2841_A140h)	*/
union _IoR2yNrctl{
	unsigned long		word;
	struct {
		unsigned long	nrmd		:2;
		unsigned long					:2;
		unsigned long	nrblend	:3;
		unsigned long					:25;
	}bit;
};

/*	structure of nrof	(2841_A148h)	*/
union _IoR2yNrof{
	unsigned long		word[2];
	struct {
		unsigned long	nrof0	:10;
		unsigned long				:6;
		unsigned long	nrof1	:10;
		unsigned long				:6;
		unsigned long	nrof2	:10;
		unsigned long				:6;
		unsigned long	nrof3	:10;
		unsigned long				:6;
	}bit;
};

/*	structure of nrga	(2841_A150h)	*/
union _IoR2yNrga{
	unsigned long		word[2];
	struct {
		long					nrga0		:11;
		unsigned long					:5;
		long					nrga1		:11;
		unsigned long					:5;
		long					nrga2		:11;
		unsigned long					:5;
		long					nrga3		:11;
		unsigned long					:5;
	}bit;
};

/*	structure of nrbd	(2841_A158h)	*/
union _IoR2yNrbd{
	unsigned long		word[2];
	struct {
		unsigned long	nrbd1	:10;
		unsigned long				:6;
		unsigned long	nrbd2	:10;
		unsigned long				:6;
		unsigned long	nrbd3	:10;
		unsigned long				:22;
	}bit;
};

/*	structure of egsmctl	(2841_A180h)	*/
union _IoR2yEgsmctl{
	unsigned long		word;
	struct {
		unsigned long	egsmt	:1;
		unsigned long				:31;
	}bit;
};

/*	structure of egsmtt	(2841_A184h)	*/
union _IoR2yEgsmtt{
	unsigned long		word;
	struct {
		unsigned long	egsmtth			:12;
		unsigned long							:4;
		unsigned long	egsmttxga		:7;
		unsigned long							:9;
	}bit;
};

/*	structure of eghwctl	(2841_A200h)	*/
union _IoR2yEghwctl{
	unsigned long		word;
	struct {
		unsigned long	eghwen		:1;
		unsigned long	eghwmp		:1;
		unsigned long	eghwtc		:1;
		unsigned long						:5;
		unsigned long	ehsaen		:1;
		unsigned long	ehtaen			:1;
		unsigned long						:6;
		unsigned long	eghwsclres	:2;
		unsigned long	eghwscltbl	:2;
		unsigned long	eghwtcres	:2;
		unsigned long	eghwtctbl	:2;
		unsigned long	eghwnrlv		:4;
		unsigned long						:4;
	}bit;
};

/*	structure of eghwhpfk	(2841_A208h)	*/
union _IoR2yEghwhpfk{
	unsigned long		word[2];
	struct {
		unsigned long	eghwhpfk0	:10;
		unsigned long						:6;
		long					eghwhpfk1	:8;
		long					eghwhpfk2	:8;
		long					eghwhpfk3	:8;
		long					eghwhpfk4	:8;
		long					eghwhpfk5	:8;
		unsigned long						:8;
	}bit;
};

/*	structure of eghwcorpof	(2841_A210h)	*/
union _IoR2yEghwcorpof{
	unsigned long		word[2];
	struct {
		unsigned long	eghwcorpof0	:10;
		unsigned long							:6;
		unsigned long	eghwcorpof1	:10;
		unsigned long							:6;
		unsigned long	eghwcorpof2	:10;
		unsigned long							:6;
		unsigned long	eghwcorpof3	:10;
		unsigned long							:6;
	}bit;
};

/*	structure of eghwcorpga	(2841_A218h)	*/
union _IoR2yEghwcorpga{
	unsigned long		word;
	struct {
		long					eghwcorpga0	:8;
		long					eghwcorpga1	:8;
		long					eghwcorpga2	:8;
		long					eghwcorpga3	:8;
	}bit;
};

/*	structure of eghwcorpbd	(2841_A220h)	*/
union _IoR2yEghwcorpbd{
	unsigned long		word[2];
	struct {
		unsigned long	eghwcorpbd1	:10;
		unsigned long							:6;
		unsigned long	eghwcorpbd2	:10;
		unsigned long							:6;
		unsigned long	eghwcorpbd3	:10;
		unsigned long							:22;
	}bit;
};

/*	structure of eghwcormof	(2841_A228h)	*/
union _IoR2yEghwcormof{
	unsigned long		word[2];
	struct {
		unsigned long	eghwcormof0	:10;
		unsigned long							:6;
		unsigned long	eghwcormof1	:10;
		unsigned long							:6;
		unsigned long	eghwcormof2	:10;
		unsigned long							:6;
		unsigned long	eghwcormof3	:10;
		unsigned long							:6;
	}bit;
};

/*	structure of eghwcormga	(2841_A230h)	*/
union _IoR2yEghwcormga{
	unsigned long		word;
	struct {
		long			eghwcormga0	:8;
		long			eghwcormga1	:8;
		long			eghwcormga2	:8;
		long			eghwcormga3	:8;
	}bit;
};

/*	structure of eghwcormbd	(2841_A238h)	*/
union _IoR2yEghwcormbd{
	unsigned long		word[2];
	struct {
		unsigned long	eghwcormbd1	:10;
		unsigned long								:6;
		unsigned long	eghwcormbd2	:10;
		unsigned long								:6;
		unsigned long	eghwcormbd3	:10;
		unsigned long								:22;
	}bit;
};

/*	structure of eghwsclsup	(2841_A240h)	*/
union _IoR2yEghwsclsup{
	unsigned long		word;
	struct {
		unsigned long	eghwsclsup	:6;
		unsigned long						:26;
	}bit;
};

/*	structure of eghwclppof	(2841_A248h)	*/
union _IoR2yEghwclppof{
	unsigned long		word[2];
	struct {
		unsigned long	eghwclppof0	:9;
		unsigned long							:7;
		unsigned long	eghwclppof1	:9;
		unsigned long							:7;
		unsigned long	eghwclppof2	:9;
		unsigned long							:23;
	}bit;
};

/*	structure of eghwclppga	(2841_A250h)	*/
union _IoR2yEghwclppga{
	unsigned long		word;
	struct {
		long			eghwclppga0	:8;
		long			eghwclppga1	:8;
		long			eghwclppga2	:8;
		unsigned long					:8;
	}bit;
};

/*	structure of eghwclppbd	(2841_A254h)	*/
union _IoR2yEghwclppbd{
	unsigned long		word;
	struct {
		unsigned long	eghwclppbd1	:10;
		unsigned long							:6;
		unsigned long	eghwclppbd2	:10;
		unsigned long							:6;
	}bit;
};

/*	structure of eghwclpmof	(2841_A258h)	*/
union _IoR2yEghwclpmof{
	unsigned long		word[2];
	struct {
		unsigned long	eghwclpmof0	:9;
		unsigned long							:7;
		unsigned long	eghwclpmof1	:9;
		unsigned long							:7;
		unsigned long	eghwclpmof2	:9;
		unsigned long							:23;
	}bit;
};

/*	structure of eghwclpmga	(2841_A260h)	*/
union _IoR2yEghwclpmga{
	unsigned long		word;
	struct {
		long			eghwclpmga0	:8;
		long			eghwclpmga1	:8;
		long			eghwclpmga2	:8;
		unsigned long					:8;
	}bit;
};

/*	structure of eghwclpmbd	(2841_A264h)	*/
union _IoR2yEghwclpmbd{
	unsigned long		word;
	struct {
		unsigned long	eghwclpmbd1	:10;
		unsigned long							:6;
		unsigned long	eghwclpmbd2	:10;
		unsigned long							:6;
	}bit;
};

/*	structure of egmwctl	(2841_A280h)	*/
union _IoR2yEgmwctl{
	unsigned long		word;
	struct {
		unsigned long	egmwen		:1;
		unsigned long	egmwmp		:1;
		unsigned long	egmwtc		:1;
		unsigned long						:5;
		unsigned long	emsaen		:1;
		unsigned long	emtaen		:1;
		unsigned long						:6;
		unsigned long	egmwsclres	:2;
		unsigned long	egmwscltbl	:2;
		unsigned long	egmwtcres	:2;
		unsigned long	egmwtctbl	:2;
		unsigned long	egmwnrlv	:4;
		unsigned long						:4;
	}bit;
};

/*	structure of egmwhpfk	(2841_A288h)	*/
union _IoR2yEgmwhpfk{
	unsigned long		word[2];
	struct {
		unsigned long	egmwhpfk0	:10;
		unsigned long						:6;
		long					egmwhpfk1	:8;
		long					egmwhpfk2	:8;
		long					egmwhpfk3	:8;
		long					egmwhpfk4	:8;
		long					egmwhpfk5	:8;
		unsigned long						:8;
	}bit;
};

/*	structure of egmwcorpof	(2841_A290h)	*/
union _IoR2yEgmwcorpof{
	unsigned long		word[2];
	struct {
		unsigned long	egmwcorpof0	:10;
		unsigned long							:6;
		unsigned long	egmwcorpof1	:10;
		unsigned long							:6;
		unsigned long	egmwcorpof2	:10;
		unsigned long							:6;
		unsigned long	egmwcorpof3	:10;
		unsigned long							:6;
	}bit;
};

/*	structure of egmwcorpga	(2841_A298h)	*/
union _IoR2yEgmwcorpga{
	unsigned long		word;
	struct {
		long			egmwcorpga0	:8;
		long			egmwcorpga1	:8;
		long			egmwcorpga2	:8;
		long			egmwcorpga3	:8;
	}bit;
};

/*	structure of egmwcorpbd	(2841_A2A0h)	*/
union _IoR2yEgmwcorpbd{
	unsigned long		word[2];
	struct {
		unsigned long	egmwcorpbd1	:10;
		unsigned long								:6;
		unsigned long	egmwcorpbd2	:10;
		unsigned long								:6;
		unsigned long	egmwcorpbd3	:10;
		unsigned long								:22;
	}bit;
};

/*	structure of egmwcormof	(2841_A2A8h)	*/
union _IoR2yEgmwcormof{
	unsigned long		word[2];
	struct {
		unsigned long	egmwcormof0	:10;
		unsigned long								:6;
		unsigned long	egmwcormof1	:10;
		unsigned long								:6;
		unsigned long	egmwcormof2	:10;
		unsigned long								:6;
		unsigned long	egmwcormof3	:10;
		unsigned long								:6;
	}bit;
};

/*	structure of egmwcormga	(2841_A2B0h)	*/
union _IoR2yEgmwcormga{
	unsigned long		word;
	struct {
		long			egmwcormga0	:8;
		long			egmwcormga1	:8;
		long			egmwcormga2	:8;
		long			egmwcormga3	:8;
	}bit;
};

/*	structure of egmwcormbd	(2841_A2B8h)	*/
union _IoR2yEgmwcormbd{
	unsigned long		word[2];
	struct {
		unsigned long	egmwcormbd1	:10;
		unsigned long								:6;
		unsigned long	egmwcormbd2	:10;
		unsigned long								:6;
		unsigned long	egmwcormbd3	:10;
		unsigned long								:22;
	}bit;
};

/*	structure of egmwsclsup	(2841_A2C0h)	*/
union _IoR2yEgmwsclsup{
	unsigned long		word;
	struct {
		unsigned long	egmwsclsup	:6;
		unsigned long							:26;
	}bit;
};

/*	structure of egmwclppof	(2841_A2C8h)	*/
union _IoR2yEgmwclppof{
	unsigned long		word[2];
	struct {
		unsigned long	egmwclppof0		:9;
		unsigned long								:7;
		unsigned long	egmwclppof1		:9;
		unsigned long								:7;
		unsigned long	egmwclppof2		:9;
		unsigned long								:23;
	}bit;
};

/*	structure of egmwclppga	(2841_A2D0h)	*/
union _IoR2yEgmwclppga{
	unsigned long		word;
	struct {
		long			egmwclppga0	:8;
		long			egmwclppga1	:8;
		long			egmwclppga2	:8;
		unsigned long					:8;
	}bit;
};

/*	structure of egmwclppbd	(2841_A2D4h)	*/
union _IoR2yEgmwclppbd{
	unsigned long		word;
	struct {
		unsigned long	egmwclppbd1	:10;
		unsigned long							:6;
		unsigned long	egmwclppbd2	:10;
		unsigned long							:6;
	}bit;
};

/*	structure of egmwclpmof	(2841_A2D8h)	*/
union _IoR2yEgmwclpmof{
	unsigned long		word[2];
	struct {
		unsigned long	egmwclpmof0	:9;
		unsigned long								:7;
		unsigned long	egmwclpmof1	:9;
		unsigned long								:7;
		unsigned long	egmwclpmof2	:9;
		unsigned long								:23;
	}bit;
};

/*	structure of egmwclpmga	(2841_A2E0h)	*/
union _IoR2yEgmwclpmga{
	unsigned long		word;
	struct {
		long			egmwclpmga0	:8;
		long			egmwclpmga1	:8;
		long			egmwclpmga2	:8;
		unsigned long						:8;
	}bit;
};

/*	structure of egmwclpmbd	(2841_A2E4h)	*/
union _IoR2yEgmwclpmbd{
	unsigned long		word;
	struct {
		unsigned long	egmwclpmbd1	:10;
		unsigned long								:6;
		unsigned long	egmwclpmbd2	:10;
		unsigned long								:6;
	}bit;
};

/*	structure of eglwctl	(2841_A300h)	*/
union _IoR2yEglwctl{
	unsigned long		word;
	struct {
		unsigned long	eglwen		:1;
		unsigned long	eglwmp		:1;
		unsigned long	eglwtc			:1;
		unsigned long						:5;
		unsigned long	elsaen			:1;
		unsigned long	eltaen			:1;
		unsigned long						:6;
		unsigned long	eglwsclres	:2;
		unsigned long	eglwscltbl	:2;
		unsigned long	eglwtcres		:2;
		unsigned long	eglwtctbl		:2;
		unsigned long						:8;
	}bit;
};

/*	structure of eglwhpfk	(2841_A310h)	*/
union _IoR2yEglwhpfk{
	unsigned long		word[3];
	struct {
		unsigned long	eglwhpfk0	:10;
		unsigned long				:6;
		long			eglwhpfk1	:8;
		long			eglwhpfk2	:8;
		long			eglwhpfk3	:8;
		long			eglwhpfk4	:8;
		long			eglwhpfk5	:8;
		long			eglwhpfk6	:8;
		long			eglwhpfk7	:8;
		long			eglwhpfk8	:8;
		long			eglwhpfk9	:8;
		unsigned long				:8;
	}bit;
};

/*	structure of eglwcorpof	(2841_A320h)	*/
union _IoR2yEglwcorpof{
	unsigned long		word[2];
	struct {
		unsigned long	eglwcorpof0	:10;
		unsigned long							:6;
		unsigned long	eglwcorpof1	:10;
		unsigned long							:6;
		unsigned long	eglwcorpof2	:10;
		unsigned long							:6;
		unsigned long	eglwcorpof3	:10;
		unsigned long							:6;
	}bit;
};

/*	structure of eglwcorpga	(2841_A328h)	*/
union _IoR2yEglwcorpga{
	unsigned long		word;
	struct {
		long			eglwcorpga0	:8;
		long			eglwcorpga1	:8;
		long			eglwcorpga2	:8;
		long			eglwcorpga3	:8;
	}bit;
};

/*	structure of eglwcorpbd	(2841_A330h)	*/
union _IoR2yEglwcorpbd{
	unsigned long		word[2];
	struct {
		unsigned long	eglwcorpbd1	:10;
		unsigned long							:6;
		unsigned long	eglwcorpbd2	:10;
		unsigned long							:6;
		unsigned long	eglwcorpbd3	:10;
		unsigned long							:22;
	}bit;
};

/*	structure of eglwcormof	(2841_A338h)	*/
union _IoR2yEglwcormof{
	unsigned long		word[2];
	struct {
		unsigned long	eglwcormof0	:10;
		unsigned long							:6;
		unsigned long	eglwcormof1	:10;
		unsigned long							:6;
		unsigned long	eglwcormof2	:10;
		unsigned long							:6;
		unsigned long	eglwcormof3	:10;
		unsigned long							:6;
	}bit;
};

/*	structure of eglwcormga	(2841_A340h)	*/
union _IoR2yEglwcormga{
	unsigned long		word;
	struct {
		long			eglwcormga0	:8;
		long			eglwcormga1	:8;
		long			eglwcormga2	:8;
		long			eglwcormga3	:8;
	}bit;
};

/*	structure of eglwcormbd	(2841_A348h)	*/
union _IoR2yEglwcormbd{
	unsigned long		word[2];
	struct {
		unsigned long	eglwcormbd1	:10;
		unsigned long							:6;
		unsigned long	eglwcormbd2	:10;
		unsigned long							:6;
		unsigned long	eglwcormbd3	:10;
		unsigned long							:22;
	}bit;
};

/*	structure of eglwsclsup	(2841_A350h)	*/
union _IoR2yEglwsclsup{
	unsigned long		word;
	struct {
		unsigned long	eglwsclsup	:6;
		unsigned long						:26;
	}bit;
};

/*	structure of eglwclppof	(2841_A358h)	*/
union _IoR2yEglwclppof{
	unsigned long		word[2];
	struct {
		unsigned long	eglwclppof0	:9;
		unsigned long							:7;
		unsigned long	eglwclppof1	:9;
		unsigned long							:7;
		unsigned long	eglwclppof2	:9;
		unsigned long							:23;
	}bit;
};

/*	structure of eglwclppga	(2841_A360h)	*/
union _IoR2yEglwclppga{
	unsigned long		word;
	struct {
		long			eglwclppga0	:8;
		long			eglwclppga1	:8;
		long			eglwclppga2	:8;
		unsigned long					:8;
	}bit;
};

/*	structure of eglwclppbd	(2841_A364h)	*/
union _IoR2yEglwclppbd{
	unsigned long		word;
	struct {
		unsigned long	eglwclppbd1	:10;
		unsigned long							:6;
		unsigned long	eglwclppbd2	:10;
		unsigned long							:6;
	}bit;
};

/*	structure of eglwclpmof	(2841_A368h)	*/
union _IoR2yEglwclpmof{
	unsigned long		word[2];
	struct {
		unsigned long	eglwclpmof0	:9;
		unsigned long							:7;
		unsigned long	eglwclpmof1	:9;
		unsigned long							:7;
		unsigned long	eglwclpmof2	:9;
		unsigned long							:23;
	}bit;
};

/*	structure of eglwclpmga	(2841_A370h)	*/
union _IoR2yEglwclpmga{
	unsigned long		word;
	struct {
		long			eglwclpmga0	:8;
		long			eglwclpmga1	:8;
		long			eglwclpmga2	:8;
		unsigned long					:8;
	}bit;
};

/*	structure of eglwclpmbd	(2841_A374h)	*/
union _IoR2yEglwclpmbd{
	unsigned long		word;
	struct {
		unsigned long	eglwclpmbd1	:10;
		unsigned long							:6;
		unsigned long	eglwclpmbd2	:10;
		unsigned long							:6;
	}bit;
};

/*	structure of egdtctl	(2841_A380h)	*/
union _IoR2yEgdtctl{
	unsigned long		word;
	struct {
		unsigned long	egdthw	:1;
		unsigned long					:3;
		unsigned long	egdtmw	:1;
		unsigned long					:27;
	}bit;
};

/*	structure of egdthwth	(2841_A384h)	*/
union _IoR2yEgdthwth{
	unsigned long		word;
	struct {
		unsigned long	egdthwthp	:10;
		unsigned long						:6;
		unsigned long	egdthwthm	:10;
		unsigned long						:6;
	}bit;
};

/*	structure of egdthwk	(2841_A388h)	*/
union _IoR2yEgdthwk{
	unsigned long		word;
	struct {
		unsigned long	egdthwkp	:4;
		unsigned long	egdthwkm	:4;
		unsigned long						:24;
	}bit;
};

/*	structure of egdtmwth	(2841_A38Ch)	*/
union _IoR2yEgdtmwth{
	unsigned long		word;
	struct {
		unsigned long	egdtmwthp		:10;
		unsigned long							:6;
		unsigned long	egdtmwthm	:10;
		unsigned long							:6;
	}bit;
};

/*	structure of egdtmwk	(2841_A390h)	*/
union _IoR2yEgdtmwk{
	unsigned long		word;
	struct {
		unsigned long	egdtmwkp	:4;
		unsigned long	egdtmwkm	:4;
		unsigned long						:24;
	}bit;
};

/*	structure of egmpctl	(2841_A3A0h)	*/
union _IoR2yEgmpctl{
	unsigned long		word;
	struct {
		unsigned long	empaen	:1;
		unsigned long					:31;
	}bit;
};

/*	structure of egmpsiz	(2841_A3A4h)	*/
union _IoR2yEgmpsiz{
	unsigned long		word;
	struct {
		unsigned long	egmpsizh	:10;
		unsigned long						:6;
		unsigned long	egmpsizv		:10;
		unsigned long						:6;
	}bit;
};

/*	structure of egmpsizhinv	(2841_A3A8h)	*/
union _IoR2yEgmpsizhinv{
	unsigned long		word;
	struct {
		unsigned long	egmpinvh		:14;
		unsigned long							:2;
		unsigned long	egmpinvsfth	:3;
		unsigned long							:13;
	}bit;
};

/*	structure of egmpsizvinv	(2841_A3ACh)	*/
union _IoR2yEgmpsizvinv{
	unsigned long		word;
	struct {
		unsigned long	egmpinvv		:14;
		unsigned long							:2;
		unsigned long	egmpinvsftv	:3;
		unsigned long							:13;
	}bit;
};

/*	structure of egmpstaph	(2841_A3B0h)	*/
union _IoR2yEgmpstaph{
	unsigned long		word;
	struct {
		unsigned long	egmpstabh	:4;
		unsigned long						:12;
		unsigned long	egmpstach	:10;
		unsigned long						:6;
	}bit;
};

/*	structure of egmpstapv	(2841_A3B4h)	*/
union _IoR2yEgmpstapv{
	unsigned long		word;
	struct {
		unsigned long	egmpstabv	:4;
		unsigned long						:12;
		unsigned long	egmpstacv	:10;
		unsigned long						:6;
	}bit;
};

/*	structure of egcmpctl	(2841_A3C0h)	*/
union _IoR2yEgcmpctl{
	unsigned long		word;
	struct {
		unsigned long	egcmps	:1;
		unsigned long					:31;
	}bit;
};

/*	structure of egcmpbd	(2841_A3C8h)	*/
union _IoR2yEgcmpbd{
	unsigned long		word[2];
	struct {
		unsigned long	egcmpbd1	:10;
		unsigned long						:6;
		unsigned long	egcmpbd2	:10;
		unsigned long						:6;
		unsigned long	egcmpbd3	:10;
		unsigned long						:22;
	}bit;
};

/*	structure of egcmpalpof	(2841_A3D0h)	*/
union _IoR2yEgcmpalpof{
	unsigned long		word;
	struct {
		unsigned long	egcmpalpof0	:8;
		unsigned long	egcmpalpof1	:8;
		unsigned long	egcmpalpof2	:8;
		unsigned long	egcmpalpof3	:8;
	}bit;
};

/*	structure of egcmpalpga	(2841_A3D8h)	*/
union _IoR2yEgcmpalpga{
	unsigned long		word[2];
	struct {
		long			egcmpalpga0	:10;
		unsigned long					:6;
		long			egcmpalpga1	:10;
		unsigned long					:6;
		long			egcmpalpga2	:10;
		unsigned long					:6;
		long			egcmpalpga3	:10;
		unsigned long					:6;
	}bit;
};

/*	structure of egcmpbtaof	(2841_A3E0h)	*/
union _IoR2yEgcmpbtaof{
	unsigned long		word;
	struct {
		unsigned long	egcmpbtaof0	:8;
		unsigned long	egcmpbtaof1	:8;
		unsigned long	egcmpbtaof2	:8;
		unsigned long	egcmpbtaof3	:8;
	}bit;
};

/*	structure of egcmpbtaga	(2841_A3E8h)	*/
union _IoR2yEgcmpbtaga{
	unsigned long		word[2];
	struct {
		long			egcmpbtaga0	:10;
		unsigned long					:6;
		long			egcmpbtaga1	:10;
		unsigned long					:6;
		long			egcmpbtaga2	:10;
		unsigned long					:6;
		long			egcmpbtaga3	:10;
		unsigned long					:6;
	}bit;
};

/*	structure of egcmpclp	(2841_A3F0h)	*/
union _IoR2yEgcmpclp{
	unsigned long		word;
	struct {
		unsigned long	egcmpclpp	:9;
		unsigned long						:7;
		unsigned long	egcmpclpm	:9;
		unsigned long						:7;
	}bit;
};

/*	structure of crvaf	(2841_A400h)	*/
union _IoR2yCrvaf{
	unsigned long		word;
	struct {
		long			crvafx1	:8;
		long			crvafy1	:8;
		long			crvafx2	:8;
		long			crvafy2	:8;
	}bit;
};

/*	structure of crvbf	(2841_A404h)	*/
union _IoR2yCrvbf{
	unsigned long		word;
	struct {
		long			crvbfx1	:8;
		long			crvbfy1	:8;
		long			crvbfx2	:8;
		long			crvbfy2	:8;
	}bit;
};

/*	structure of egcrvctl	(2841_A440h)	*/
union _IoR2yEgcrvctl{
	unsigned long		word;
	struct {
		unsigned long	egcrae		:1;
		unsigned long					:3;
		unsigned long	egcrbe		:1;
		unsigned long					:3;
		unsigned long	egcrvmrg	:2;
		unsigned long					:22;
	}bit;
};

/*	structure of egcrvasclof	(2841_A444h)	*/
union _IoR2yEgcrvasclof{
	unsigned long		word;
	struct {
		unsigned long	egcrvasclof1	:8;
		unsigned long							:24;
	}bit;
};

/*	structure of egcrvasclga	(2841_A448h)	*/
union _IoR2yEgcrvasclga{
	unsigned long		word;
	struct {
		long			egcrvasclga0	:11;
		unsigned long					:5;
		long			egcrvasclga1	:11;
		unsigned long					:5;
	}bit;
};

/*	structure of egcrvasclbd	(2841_A44Ch)	*/
union _IoR2yEgcrvasclbd{
	unsigned long		word;
	struct {
		unsigned long	egcrvasclbd1	:7;
		unsigned long							:25;
	}bit;
};

/*	structure of egcrvasclcp	(2841_A450h)	*/
union _IoR2yEgcrvasclcp{
	unsigned long		word;
	struct {
		unsigned long	egcrvasclcpl	:8;
		unsigned long	egcrvasclcph	:8;
		unsigned long							:16;
	}bit;
};

/*	structure of egyasclga	(2841_A454h)	*/
union _IoR2yEgyasclga{
	unsigned long		word;
	struct {
		unsigned long	egyasclga0	:8;
		unsigned long	egyasclga1	:8;
		unsigned long						:16;
	}bit;
};

/*	structure of egyasclbd	(2841_A458h)	*/
union _IoR2yEgyasclbd{
	unsigned long		word;
	struct {
		unsigned long	egyasclbd0	:8;
		unsigned long	egyasclbd1	:8;
		unsigned long						:16;
	}bit;
};

/*	structure of egyasclclp	(2841_A45Ch)	*/
union _IoR2yEgyasclclp{
	unsigned long		word;
	struct {
		unsigned long	egyasclclpl	:9;
		unsigned long						:7;
		unsigned long	egyasclclph	:9;
		unsigned long						:7;
	}bit;
};

/*	structure of egcrvbsclof	(2841_A460h)	*/
union _IoR2yEgcrvbsclof{
	unsigned long		word;
	struct {
		unsigned long	egcrvbsclof1	:8;
		unsigned long							:24;
	}bit;
};

/*	structure of egcrvbsclga	(2841_A464h)	*/
union _IoR2yEgcrvbsclga{
	unsigned long		word;
	struct {
		long			egcrvbsclga0	:11;
		unsigned long					:5;
		long			egcrvbsclga1	:11;
		unsigned long					:5;
	}bit;
};

/*	structure of egcrvbsclbd	(2841_A468h)	*/
union _IoR2yEgcrvbsclbd{
	unsigned long		word;
	struct {
		unsigned long	egcrvbsclbd1	:7;
		unsigned long							:25;
	}bit;
};

/*	structure of egcrvbsclcp	(2841_A46Ch)	*/
union _IoR2yEgcrvbsclcp{
	unsigned long		word;
	struct {
		unsigned long	egcrvbsclcpl	:8;
		unsigned long	egcrvbsclcph	:8;
		unsigned long							:16;
	}bit;
};

/*	structure of egybsclga	(2841_A470h)	*/
union _IoR2yEgybsclga{
	unsigned long		word;
	struct {
		unsigned long	egybsclga0	:8;
		unsigned long	egybsclga1	:8;
		unsigned long						:16;
	}bit;
};

/*	structure of egybsclbd	(2841_A474h)	*/
union _IoR2yEgybsclbd{
	unsigned long		word;
	struct {
		unsigned long	egybsclbd0	:8;
		unsigned long	egybsclbd1	:8;
		unsigned long						:16;
	}bit;
};

/*	structure of egybsclclp	(2841_A478h)	*/
union _IoR2yEgybsclclp{
	unsigned long		word;
	struct {
		unsigned long	egybsclclpl	:9;
		unsigned long						:7;
		unsigned long	egybsclclph	:9;
		unsigned long						:7;
	}bit;
};

/*	structure of egcrvclp	(2841_A47Ch)	*/
union _IoR2yEgcrvclp{
	unsigned long		word;
	struct {
		unsigned long	egcrvclpp	:9;
		unsigned long						:7;
		unsigned long	egcrvclpm	:9;
		unsigned long						:7;
	}bit;
};

/*	structure of ybcrvctl	(2841_A480h)	*/
union _IoR2yYbcrvctl{
	unsigned long		word;
	struct {
		unsigned long	ybcrae	:1;
		unsigned long				:3;
		unsigned long	ybcrbe	:1;
		unsigned long				:27;
	}bit;
};

/*	structure of ybcrvaalpof	(2841_A484h)	*/
union _IoR2yYbcrvaalpof{
	unsigned long		word;
	struct {
		unsigned long	ybcrvaalpof1	:8;
		unsigned long							:24;
	}bit;
};

/*	structure of ybcrvaalpga	(2841_A488h)	*/
union _IoR2yYbcrvaalpga{
	unsigned long		word;
	struct {
		long			ybcrvaalpga0	:11;
		unsigned long					:5;
		long			ybcrvaalpga1	:11;
		unsigned long					:5;
	}bit;
};

/*	structure of ybcrvaalpbd	(2841_A48Ch)	*/
union _IoR2yYbcrvaalpbd{
	unsigned long		word;
	struct {
		unsigned long	ybcrvaalpbd1	:7;
		unsigned long							:25;
	}bit;
};

/*	structure of ybcrvaalpcp	(2841_A490h)	*/
union _IoR2yYbcrvaalpcp{
	unsigned long		word;
	struct {
		unsigned long	ybcrvaalpcpl	:8;
		unsigned long	ybcrvaalpcph	:8;
		unsigned long							:16;
	}bit;
};

/*	structure of ybyaalpga	(2841_A494h)	*/
union _IoR2yYbyaalpga{
	unsigned long		word;
	struct {
		unsigned long	ybyaalpga0	:8;
		unsigned long	ybyaalpga1	:8;
		unsigned long						:16;
	}bit;
};

/*	structure of ybyaalpbd	(2841_A498h)	*/
union _IoR2yYbyaalpbd{
	unsigned long		word;
	struct {
		unsigned long	ybyaalpbd0	:8;
		unsigned long	ybyaalpbd1	:8;
		unsigned long						:16;
	}bit;
};

/*	structure of ybyaalpclp	(2841_A49Ch)	*/
union _IoR2yYbyaalpclp{
	unsigned long		word;
	struct {
		unsigned long	ybyaalpclpl		:8;
		unsigned long	ybyaalpclph	:8;
		unsigned long							:16;
	}bit;
};

/*	structure of ybcrvbalpof	(2841_A4A0h)	*/
union _IoR2yYbcrvbalpof{
	unsigned long		word;
	struct {
		unsigned long	ybcrvbalpof1	:8;
		unsigned long							:24;
	}bit;
};

/*	structure of ybcrvbalpga	(2841_A4A4h)	*/
union _IoR2yYbcrvbalpga{
	unsigned long		word;
	struct {
		long			ybcrvbalpga0	:11;
		unsigned long					:5;
		long			ybcrvbalpga1	:11;
		unsigned long					:5;
	}bit;
};

/*	structure of ybcrvbalpbd	(2841_A4A8h)	*/
union _IoR2yYbcrvbalpbd{
	unsigned long		word;
	struct {
		unsigned long	ybcrvbalpbd1	:7;
		unsigned long							:25;
	}bit;
};

/*	structure of ybcrvbalpcp	(2841_A4ACh)	*/
union _IoR2yYbcrvbalpcp{
	unsigned long		word;
	struct {
		unsigned long	ybcrvbalpcpl	:8;
		unsigned long	ybcrvbalpcph	:8;
		unsigned long							:16;
	}bit;
};

/*	structure of ybybalpga	(2841_A4B0h)	*/
union _IoR2yYbybalpga{
	unsigned long		word;
	struct {
		unsigned long	ybybalpga0	:8;
		unsigned long	ybybalpga1	:8;
		unsigned long						:16;
	}bit;
};

/*	structure of ybybalpbd	(2841_A4B4h)	*/
union _IoR2yYbybalpbd{
	unsigned long		word;
	struct {
		unsigned long	ybybalpbd0	:8;
		unsigned long	ybybalpbd1	:8;
		unsigned long						:16;
	}bit;
};

/*	structure of ybybalpclp	(2841_A4B8h)	*/
union _IoR2yYbybalpclp{
	unsigned long		word;
	struct {
		unsigned long	ybybalpclpl		:8;
		unsigned long	ybybalpclph	:8;
		unsigned long							:16;
	}bit;
};

/*	structure of clpfctl	(2841_A500h)	*/
union _IoR2yClpfctl{
	unsigned long		word;
	struct {
		unsigned long	clpfen	:1;
		unsigned long				:3;
		unsigned long	clpfya	:1;
		unsigned long				:27;
	}bit;
};

/*	structure of clpfk	(2841_A520h)	*/
union _IoR2yClpfk{
	unsigned long		word[5];
	struct {
		long			clpfk0		:9;
		unsigned long			:7;
		long			clpfk1		:9;
		unsigned long			:7;
		long			clpfk2		:9;
		unsigned long			:7;
		long			clpfk3		:9;
		unsigned long			:7;
		long			clpfk4		:9;
		unsigned long			:7;
		long			clpfk5		:9;
		unsigned long			:7;
		long			clpfk6		:9;
		unsigned long			:7;
		long			clpfk7		:9;
		unsigned long			:7;
		long			clpfk8		:9;
		unsigned long			:23;
	}bit;
};

/*	structure of clpfof	(2841_A540h)	*/
union _IoR2yClpfof{
	unsigned long		word;
	struct {
		unsigned long	clpfof0	:8;
		unsigned long	clpfof1	:8;
		unsigned long	clpfof2	:8;
		unsigned long	clpfof3	:8;
	}bit;
};

/*	structure of clpfga	(2841_A548h)	*/
union _IoR2yClpfga{
	unsigned long		word[2];
	struct {
		long			clpfga0		:10;
		unsigned long				:6;
		long			clpfga1		:10;
		unsigned long				:6;
		long			clpfga2		:10;
		unsigned long				:6;
		long			clpfga3		:10;
		unsigned long				:6;
	}bit;
};

/*	structure of clpfbd	(2841_A550h)	*/
union _IoR2yClpfbd{
	unsigned long		word[2];
	struct {
		unsigned long	clpfbd1	:10;
		unsigned long					:6;
		unsigned long	clpfbd2	:10;
		unsigned long					:6;
		unsigned long	clpfbd3	:10;
		unsigned long					:22;
	}bit;
};

/*	structure of csyctl	(2841_A580h)	*/
union _IoR2yCsyctl{
	unsigned long		word;
	struct {
		unsigned long	csyen	:1;
		unsigned long				:3;
		unsigned long	csyky	:4;
		unsigned long				:4;
		unsigned long	csytbl	:1;
		unsigned long				:19;
	}bit;
};

/*	structure of csyof	(2841_A588h)	*/
union _IoR2yCsyof{
	unsigned long		word[2];
	struct {
		unsigned long	csyof0	:10;
		unsigned long				:6;
		unsigned long	csyof1	:10;
		unsigned long				:6;
		unsigned long	csyof2	:10;
		unsigned long				:6;
		unsigned long	csyof3	:10;
		unsigned long				:6;
	}bit;
};

/*	structure of csyga	(2841_A590h)	*/
union _IoR2yCsyga{
	unsigned long		word[2];
	struct {
		long			csyga0		:11;
		unsigned long			:5;
		long			csyga1		:11;
		unsigned long			:5;
		long			csyga2		:11;
		unsigned long			:5;
		long			csyga3		:11;
		unsigned long			:5;
	}bit;
};

/*	structure of csybd	(2841_A598h)	*/
union _IoR2yCsybd{
	unsigned long		word[2];
	struct {
		unsigned long	csybd1	:10;
		unsigned long				:6;
		unsigned long	csybd2	:10;
		unsigned long				:6;
		unsigned long	csybd3	:10;
		unsigned long				:22;
	}bit;
};

/*	structure of ycrvfx	(2841_A5A0h)	*/
union _IoR2yYcrvfx{
	unsigned long		word;
	struct {
		unsigned long	yrv		:1;
		unsigned long				:3;
		unsigned long	crv		:1;
		unsigned long				:3;
		unsigned long	cfixen	:1;
		unsigned long				:23;
	}bit;
};

/*	structure of cfix	(2841_A5A4h)	*/
union _IoR2yCfix{
	unsigned long		word;
	struct {
		long					cfixb		:10;
		unsigned long					:6;
		long					cfixr			:10;
		unsigned long					:6;
	}bit;
};

/*	structure of ycof	(2841_A5A8h)	*/
union _IoR2yYcof{
	unsigned long		word[2];
	struct {
		long					yof			:11;
		unsigned long					:21;
		long					cofb			:11;
		unsigned long					:5;
		long					cofr			:11;
		unsigned long					:5;
	}bit;
};

/*	structure of FR2Y control area	2841_(8000 - 801Fh) */
struct _IoR2yFr2yCntl{
	IoR2yCntl			cntl;				/* 2841_(8000 - 8003h) */
	IoR2yR2yflag		r2yflag;		/* 2841_(8004 - 8007h) */
	IoR2yR2yinte		r2yinte;		/* 2841_(8008 - 800Bh) */
	IoR2yR2yintf		r2yintf;			/* 2841_(800C - 800Fh) */
	IoR2yFltaen			fltaen;			/* 2841_(8010 - 8013h) */
	unsigned char 	dmy8014801f[0x8020 - 0x8014];	/* 2841_(8014 - 801Fh) */
};

/*	structure of Offset & WBGain area	2841_(8020 - 807Fh) */
struct _IoR2yOfg{
	IoR2yOfst			ofst;				/* 2841_(8020 - 8027h) */
	IoR2yWbgar		wbgar;			/* 2841_(8028 - 802Fh) */
	IoR2yWblv			wblv;			/* 2841_(8030 - 8037h) */
	unsigned char 	dmy8038807f[0x8080 - 0x8038];	/* 2841_(8038 - 807Fh) */
};

/*	structure of cca0 area	2841_(8080 - 8FFFh) */
struct _IoR2yCca0{
	IoR2yCc0ctl				cc0ctl;			/* 2841_(8080 - 8083h) */
	unsigned char 		dmy8084809f[0x80A0 - 0x8084];		/* 2841_(8084 - 809Fh) */
	IoR2yCc0k				cc0k;			/* 2841_(80A0 - 80B3h) */
	unsigned char 		dmy80b480bf[0x80C0 - 0x80B4];		/* 2841_(80B4 - 80BFh) */
	IoR2yCc0ybof			cc0ybof;		/* 2841_(80C0 - 80C7h) */
	IoR2yCc0ybga			cc0ybga;		/* 2841_(80C8 - 80CFh) */
	IoR2yCc0ybbd			cc0ybbd;		/* 2841_(80D0 - 80D3h) */
	IoR2yCcyc				ccyc;			/* 2841_(80D4 - 80D7h) */
	unsigned char 		dmy80d88fff[0x9000 - 0x80D8];		/* 2841_(80D8 - 8FFFh) */
};

/*	structure of mcc area	2841_(9000 - 9FFFh) */
struct _IoR2yMcc{
	IoR2yMcyc			mcyc;				/* 2841_(9000 - 9013h) */
	unsigned char 	dmy9014901f[0x9020 - 0x9014];	/* 2841_(9014 - 901Fh) */
	IoR2yMcb1ab		mcb1ab;			/* 2841_(9020 - 9023h) */
	IoR2yMcb1cd		mcb1cd;			/* 2841_(9024 - 9027h) */
	IoR2yMcb2ab		mcb2ab;			/* 2841_(9028 - 902Bh) */
	IoR2yMcb2cd		mcb2cd;			/* 2841_(902C - 902Fh) */
	IoR2yMcb3ab		mcb3ab;			/* 2841_(9030 - 9033h) */
	IoR2yMcb3cd		mcb3cd;			/* 2841_(9034 - 9037h) */
	IoR2yMcb4ab		mcb4ab;			/* 2841_(9038 - 903Bh) */
	IoR2yMcb4cd		mcb4cd;			/* 2841_(903C - 903Fh) */
	IoR2yMcid1			mcid1;				/* 2841_(9040 - 9043h) */
	IoR2yMcid2			mcid2;				/* 2841_(9044 - 9047h) */
	IoR2yMcid3			mcid3;				/* 2841_(9048 - 904Bh) */
	IoR2yMcid4			mcid4;				/* 2841_(904C - 904Fh) */
	unsigned char 	dmy9050907f[0x9080 - 0x9050];	/* 2841_(9050 - 907Fh) */
	IoR2yMck			mcka;				/* 2841_(9080 - 90E3h) */
	unsigned char 	dmy90e490ff[0x9100 - 0x90E4];	/* 2841_(90E4 - 90FFh) */
	IoR2yMck			mckb;				/* 2841_(9100 - 9163h) */
	unsigned char 	dmy9164917f[0x9180 - 0x9164];	/* 2841_(9164 - 917Fh) */
	IoR2yMck			mckc;				/* 2841_(9180 - 91E3h) */
	unsigned char 	dmy91e491ff[0x9200 - 0x91E4];	/* 2841_(91E4 - 91FFh) */
	IoR2yMck			mckd;				/* 2841_(9200 - 9263h) */
	unsigned char dmy9264927f[0x9280 - 0x9264];	/* 2841_(9264 - 927Fh) */
	IoR2yMck			mcke;				/* 2841_(9280 - 92E3h) */
	unsigned char 	dmy92e492ff[0x9300 - 0x92E4];	/* 2841_(92E4 - 92FFh) */
	IoR2yMck			mckf;				/* 2841_(9300 - 9363h) */
	unsigned char 	dmy9364937f[0x9380 - 0x9364];	/* 2841_(9364 - 937Fh) */
	IoR2yMck			mckg;				/* 2841_(9380 - 93E3h) */
	unsigned char 	dmy93e493ff[0x9400 - 0x93E4];	/* 2841_(93E4 - 93FFh) */
	IoR2yMck			mckh;				/* 2841_(9400 - 9463h) */
	unsigned char 	dmy9464947f[0x9480 - 0x9464];	/* 2841_(9464 - 947Fh) */
	IoR2yMck			mcki;				/* 2841_(9480 - 94E3h) */
	unsigned char 	dmy94e494ff[0x9500 - 0x94E4];	/* 2841_(94E4 - 94FFh) */
	IoR2yMck			mckj;				/* 2841_(9500 - 9563h) */
	unsigned char 	dmy9564957f[0x9580 - 0x9564];	/* 2841_(9564 - 957Fh) */
	IoR2yMck			mckk;				/* 2841_(9580 - 95E3h) */
	unsigned char 	dmy95e495ff[0x9600 - 0x95E4];	/* 2841_(95E4 - 95FFh) */
	IoR2yMck			mckl;				/* 2841_(9600 - 9663h) */
	unsigned char 	dmy9664967f[0x9680 - 0x9664];	/* 2841_(9664 - 967Fh) */
	IoR2yMcl				mcla;				/* 2841_(9680 - 96BBh) */
	unsigned char 	dmy96bc96bf[0x96C0 - 0x96BC];	/* 2841_(96BC - 96BFh) */
	IoR2yMcl				mclb;				/* 2841_(96C0 - 96FBh) */
	unsigned char 	dmy96fc96ff[0x9700 - 0x96FC];	/* 2841_(96FC - 96FFh) */
	IoR2yMcl				mclc;				/* 2841_(9700 - 973Bh) */
	unsigned char 	dmy973c973f[0x9740 - 0x973C];	/* 2841_(973C - 973Fh) */
	IoR2yMcl				mcld;				/* 2841_(9740 - 977Bh) */
	unsigned char 	dmy977c977f[0x9780 - 0x977C];	/* 2841_(977C - 977Fh) */
	IoR2yMcl				mcle;				/* 2841_(9780 - 97BBh) */
	unsigned char 	dmy97bc97bf[0x97C0 - 0x97BC];	/* 2841_(97BC - 97BFh) */
	IoR2yMcl				mclf;				/* 2841_(97C0 - 97FBh) */
	unsigned char 	dmy97fc97ff[0x9800 - 0x97FC];	/* 2841_(97FC - 97FFh) */
	IoR2yMcl				mclg;				/* 2841_(9800 - 983Bh) */
	unsigned char 	dmy983c983f[0x9840 - 0x983C];	/* 2841_(983C - 983Fh) */
	IoR2yMcl				mclh;				/* 2841_(9840 - 987Bh) */
	unsigned char 	dmy987c987f[0x9880 - 0x987C];	/* 2841_(987C - 987Fh) */
	IoR2yMcl				mcli;				/* 2841_(9880 - 98BBh) */
	unsigned char 	dmy98bc98bf[0x98C0 - 0x98BC];	/* 2841_(98BC - 98BFh) */
	IoR2yMcl				mclj;				/* 2841_(98C0 - 98FBh) */
	unsigned char 	dmy98fc98ff[0x9900 - 0x98FC];	/* 2841_(98FC - 98FFh) */
	IoR2yMcl				mclk;				/* 2841_(9900 - 993Bh) */
	unsigned char 	dmy993c993f[0x9940 - 0x993C];	/* 2841_(993C - 993Fh) */
	IoR2yMcl				mcll;				/* 2841_(9940 - 997Bh) */
	unsigned char 	dmy997c997f[0x9980 - 0x997C];	/* 2841_(997C - 997Fh) */
	IoR2yMcycbalp	mcycbalp;		/* 2841_(9980 - 9983h) */
	unsigned char 	dmy99849987[0x9988 - 0x9984];	/* 2841_(9984 - 9987h) */
	IoR2yMcycbga	mcycbga;		/* 2841_(9988 - 998Fh) */
	IoR2yMcycbbd	mcycbbd;		/* 2841_(9990 - 9997h) */
	IoR2yMcbabalp	mcbabalp;		/* 2841_(9998 - 999Bh) */
	unsigned char 	dmy999c999f[0x99A0 - 0x999C];	/* 2841_(999C - 999Fh) */
	IoR2yMcbabof	mcbabof;		/* 2841_(99A0 - 99A7h) */
	IoR2yMcbabga	mcbabga;		/* 2841_(99A8 - 99AFh) */
	IoR2yMcbabbd	mcbabbd;		/* 2841_(99B0 - 99B7h) */
	unsigned char 	dmy99b89fff[0xA000 - 0x99B8];	/* 2841_(99B8 - 9FFFh) */
};

/*	structure of Offset/Luminance Evaluation/Histogram before TC area	2841_(A000 - A03Fh) */
struct _IoR2yBtc{
	IoR2yTcof			tcof;				/* 2841_(A000 - A007h) */
	IoR2yTctctl			tctctl;			/* 2841_(A008 - A00Bh) */
	IoR2yTctsta			tctsta;			/* 2841_(A00C - A00Fh) */
	IoR2yTctb			tctb;				/* 2841_(A010 - A013h) */
	IoR2yTchsctl		tchsctl;			/* 2841_(A014 - A017h) */
	IoR2yTchssta		tchssta;		/* 2841_(A018 - A01Bh) */
	IoR2yTchssiz		tchssiz;		/* 2841_(A01C - A01Fh) */
	IoR2yTchov			tchov;			/* 2841_(A020 - A023h) */
	unsigned char dmyA024A03f[0xA040 - 0xA024];	/* 2841_(A024 - A03Fh) */
};

/*	structure of Tone area	2841_(A040 - A05Fh) */
struct _IoR2yTcArea{
	IoR2yTcctl			tcctl;			/* 2841_(A040 - A043h) */
	IoR2yTcyc			tcyc;				/* 2841_(A044 - A047h) */
	IoR2yTcep			tcep;			/* 2841_(A048 - A04Fh) */
	IoR2yTcclpr			tcclpr;			/* 2841_(A050 - A053h) */
	IoR2yTcclpg		tcclpg;			/* 2841_(A054 - A057h) */
	IoR2yTcclpb		tcclpb;			/* 2841_(A058 - A05Bh) */
	unsigned char 	dmyA05cA05f[0xA060 - 0xA05C];		/* 2841_(A05C - A05Fh) */
};

/*	structure of Gamma area	2841_(A060 - A07Fh) */
struct _IoR2yGam{
	IoR2yGmctl			gmctl;			/* 2841_(A060 - A063h) */
	unsigned char 	dmyA064A07f[0xA080 - 0xA064];		/* 2841_(A064 - A07Fh) */
};

/*	structure of cca1 area	2841_(A080 - A0FFh) */
struct _IoR2yCca1{
	IoR2yCc1ctl			cc1ctl;			/* 2841_(A080 - A083h) */
	unsigned char 	dmyA084A09f[0xA0A0 - 0xA084];		/* 2841_(A084 - A09Fh) */
	IoR2yCc1k			cc1k;			/* 2841_(A0A0 - A0B3h) */
	unsigned char 	dmyA0b4A0bf[0xA0C0 - 0xA0B4];	/* 2841_(A0B4 - A0BFh) */
	IoR2yCc1clpr		cc1clpr;		/* 2841_(A0C0 - A0C3h) */
	IoR2yCc1clpg		cc1clpg;		/* 2841_(A0C4 - A0C7h) */
	IoR2yCc1clpb		cc1clpb;		/* 2841_(A0C8 - A0CBh) */
	unsigned char dmyA0ccA0ff[0xA100 - 0xA0CC];		/* 2841_(A0CC - A0FFh) */
};

/*	structure of yc area	2841_(A100 - A13Fh) */
struct _IoR2yYcArea{
	IoR2yYc				yc;					/* 2841_(A100 - A113h) */
	unsigned char 	dmyA114A11f[0xA120 - 0xA114];		/* 2841_(A114 - A11Fh) */
	IoR2yYblend		yblend;			/* 2841_(A120 - A123h) */
	unsigned char 	dmyA124A13f[0xA140 - 0xA124];		/* 2841_(A124 - A13Fh) */
};

/*	structure of ynr area	2841_(A140 - A17Fh) */
struct _IoR2yYnr{
	IoR2yNrctl			nrctl;			/* 2841_(A140 - A143h) */
	unsigned char 	dmyA144A147[0xA148 - 0xA144];	/* 2841_(A144 - A147h) */
	IoR2yNrof			nrof;			/* 2841_(A148 - A14Fh) */
	IoR2yNrga			nrga;			/* 2841_(A150 - A157h) */
	IoR2yNrbd			nrbd;			/* 2841_(A158 - A15Fh) */
	unsigned char 	dmyA160A17f[0xA180 - 0xA160];		/* 2841_(A160 - A17Fh) */
};

/*	structure of eghw & egmw common area	2841_(A180 - A1FFh) */
struct _IoR2yEgsm{
	IoR2yEgsmctl		egsmctl;			/* 2841_(A180 - A183h) */
	IoR2yEgsmtt		egsmtt;			/* 2841_(A184 - A187h) */
	unsigned char 	dmyA188A1ff[0xA200 - 0xA188];	/* 2841_(A188 - A1FFh) */
};

/*	structure of eghw area	2841_(A200 - A27Fh) */
struct _IoR2yEghw{
	IoR2yEghwctl			eghwctl;				/* 2841_(A200 - A203h) */
	unsigned char 		dmyA204A207[0xA208 - 0xA204];	/* 2841_(A204 - A207h) */
	IoR2yEghwhpfk		eghwhpfk;			/* 2841_(A208 - A20Fh) */
	IoR2yEghwcorpof	eghwcorpof;		/* 2841_(A210 - A217h) */
	IoR2yEghwcorpga	eghwcorpga;		/* 2841_(A218 - A21Bh) */
	unsigned char 		dmyA21cA21f[0xA220 - 0xA21C];		/* 2841_(A21C - A21Fh) */
	IoR2yEghwcorpbd	eghwcorpbd;		/* 2841_(A220 - A227h) */
	IoR2yEghwcormof	eghwcormof;		/* 2841_(A228 - A22Fh) */
	IoR2yEghwcormga	eghwcormga;		/* 2841_(A230 - A233h) */
	unsigned char 		dmyA234A237[0xA238 - 0xA234];	/* 2841_(A234 - A237h) */
	IoR2yEghwcormbd	eghwcormbd;		/* 2841_(A238 - A23Fh) */
	IoR2yEghwsclsup	eghwsclsup;		/* 2841_(A240 - A243h) */
	unsigned char 		dmyA244A247[0xA248 - 0xA244];	/* 2841_(A244 - A247h) */
	IoR2yEghwclppof	eghwclppof;		/* 2841_(A248 - A24Fh) */
	IoR2yEghwclppga	eghwclppga;		/* 2841_(A250 - A253h) */
	IoR2yEghwclppbd	eghwclppbd;		/* 2841_(A254 - A257h) */
	IoR2yEghwclpmof	eghwclpmof;		/* 2841_(A258 - A25Fh) */
	IoR2yEghwclpmga	eghwclpmga;		/* 2841_(A260 - A263h) */
	IoR2yEghwclpmbd	eghwclpmbd;		/* 2841_(A264 - A267h) */
	unsigned char 		dmyA268A27f[0xA280 - 0xA268];		/* 2841_(A268 - A27Fh) */
};

/*	structure of egmw area	2841_(A280 - A2FFh) */
struct _IoR2yEgmw{
	IoR2yEgmwctl				egmwctl;				/* 2841_(A280 - A283h) */
	unsigned char 			dmyA284A287[0xA288 - 0xA284];	/* 2841_(A284 - A287h) */
	IoR2yEgmwhpfk			egmwhpfk;			/* 2841_(A288 - A28Fh) */
	IoR2yEgmwcorpof		egmwcorpof;		/* 2841_(A290 - A297h) */
	IoR2yEgmwcorpga		egmwcorpga;		/* 2841_(A298 - A29Bh) */
	unsigned char 			dmyA29cA29f[0xA2A0 - 0xA29C];	/* 2841_(A29C - A29Fh) */
	IoR2yEgmwcorpbd		egmwcorpbd;		/* 2841_(A2A0 - A2A7h) */
	IoR2yEgmwcormof		egmwcormof;		/* 2841_(A2A8 - A2AFh) */
	IoR2yEgmwcormga	egmwcormga;	/* 2841_(A2B0 - A2B3h) */
	unsigned char 			dmyA2b4A2b7[0xA2B8 - 0xA2B4];	/* 2841_(A2B4 - A2B7h) */
	IoR2yEgmwcormbd	egmwcormbd;	/* 2841_(A2B8 - A2BFh) */
	IoR2yEgmwsclsup		egmwsclsup;		/* 2841_(A2C0 - A2C3h) */
	unsigned char 			dmyA2c4A2c7[0xA2C8 - 0xA2C4];	/* 2841_(A2C4 - A2C7h) */
	IoR2yEgmwclppof		egmwclppof;		/* 2841_(A2C8 - A2CFh) */
	IoR2yEgmwclppga		egmwclppga;		/* 2841_(A2D0 - A2D3h) */
	IoR2yEgmwclppbd		egmwclppbd;		/* 2841_(A2D4 - A2D7h) */
	IoR2yEgmwclpmof		egmwclpmof;		/* 2841_(A2D8 - A2DFh) */
	IoR2yEgmwclpmga	egmwclpmga;		/* 2841_(A2E0 - A2E3h) */
	IoR2yEgmwclpmbd	egmwclpmbd;	/* 2841_(A2E4 - A2E7h) */
	unsigned char 			dmyA2e8A2ff[0xA300 - 0xA2E8];		/* 2841_(A2E8 - A2FFh) */
};

/*	structure of eglw area	2841_(A300 - A37Fh) */
struct _IoR2yEglw{
	IoR2yEglwctl			eglwctl;				/* 2841_(A300 - A303h) */
	unsigned char 		dmyA304A30f[0xA310 - 0xA304];		/* 2841_(A304 - A30Fh) */
	IoR2yEglwhpfk		eglwhpfk;			/* 2841_(A310 - A31Bh) */
	unsigned char 		dmyA31cA31f[0xA320 - 0xA31C];		/* 2841_(A31C - A31Fh) */
	IoR2yEglwcorpof	eglwcorpof;			/* 2841_(A320 - A327h) */
	IoR2yEglwcorpga	eglwcorpga;		/* 2841_(A328 - A32Bh) */
	unsigned char 		dmyA32cA32f[0xA330 - 0xA32C];		/* 2841_(A32C - A32Fh) */
	IoR2yEglwcorpbd	eglwcorpbd;		/* 2841_(A330 - A337h) */
	IoR2yEglwcormof	eglwcormof;		/* 2841_(A338 - A33Fh) */
	IoR2yEglwcormga	eglwcormga;		/* 2841_(A340 - A343h) */
	unsigned char 		dmyA344A347[0xA348 - 0xA344];	/* 2841_(A344 - A347h) */
	IoR2yEglwcormbd	eglwcormbd;		/* 2841_(A348 - A34Fh) */
	IoR2yEglwsclsup		eglwsclsup;			/* 2841_(A350 - A353h) */
	unsigned char 		dmyA354A357[0xA358 - 0xA354];	/* 2841_(A354 - A357h) */
	IoR2yEglwclppof		eglwclppof;			/* 2841_(A358 - A35Fh) */
	IoR2yEglwclppga	eglwclppga;		/* 2841_(A360 - A363h) */
	IoR2yEglwclppbd	eglwclppbd;		/* 2841_(A364 - A367h) */
	IoR2yEglwclpmof	eglwclpmof;		/* 2841_(A368 - A36Fh) */
	IoR2yEglwclpmga	eglwclpmga;		/* 2841_(A370 - A373h) */
	IoR2yEglwclpmbd	eglwclpmbd;		/* 2841_(A374 - A377h) */
	unsigned char 		dmyA378A37f[0xA380 - 0xA378];		/* 2841_(A378 - A37Fh) */
};

/*	structure of egdt area	2841_(A380 - A39Fh) */
struct _IoR2yEgdt{
	IoR2yEgdtctl			egdtctl;		/* 2841_(A380 - A383h) */
	IoR2yEgdthwth		egdthwth;		/* 2841_(A384 - A387h) */
	IoR2yEgdthwk			egdthwk;		/* 2841_(A388 - A38Bh) */
	IoR2yEgdtmwth		egdtmwth;		/* 2841_(A38C - A38Fh) */
	IoR2yEgdtmwk		egdtmwk;		/* 2841_(A390 - A393h) */
	unsigned char 		dmyA394A39f[0xA3A0 - 0xA394];	/* 2841_(A394 - A39Fh) */
};

/*	structure of mapscl area	2841_(A3A0 - A3BFh) */
struct _IoR2yMapscl{
	IoR2yEgmpctl			egmpctl;		/* 2841_(A3A0 - A3A3h) */
	IoR2yEgmpsiz			egmpsiz;		/* 2841_(A3A4 - A3A7h) */
	IoR2yEgmpsizhinv	egmpsizhinv;	/* 2841_(A3A8 - A3ABh) */
	IoR2yEgmpsizvinv	egmpsizvinv;	/* 2841_(A3AC - A3AFh) */
	IoR2yEgmpstaph	egmpstaph;		/* 2841_(A3B0 - A3B3h) */
	IoR2yEgmpstapv		egmpstapv;		/* 2841_(A3B4 - A3B7h) */
	unsigned char 		dmyA3b8A3bf[0xA3C0 - 0xA3B8];	/* 2841_(A3B8 - A3BFh) */
};

/*	structure of egcmp area	2841_(A3C0 - A3FFh) */
struct _IoR2yEgcmp{
	IoR2yEgcmpctl		egcmpctl;			/* 2841_(A3C0 - A3C3h) */
	unsigned char 		dmyA3c4A3c7[0xA3C8 - 0xA3C4];	/* 2841_(A3C4 - A3C7h) */
	IoR2yEgcmpbd		egcmpbd;			/* 2841_(A3C8 - A3CFh) */
	IoR2yEgcmpalpof	egcmpalpof;		/* 2841_(A3D0 - A3D3h) */
	unsigned char 		dmyA3d4A3d7[0xA3D8 - 0xA3D4];	/* 2841_(A3D4 - A3D7h) */
	IoR2yEgcmpalpga	egcmpalpga;		/* 2841_(A3D8 - A3DFh) */
	IoR2yEgcmpbtaof	egcmpbtaof;		/* 2841_(A3E0 - A3E3h) */
	unsigned char 		dmyA3e4A3e7[0xA3E8 - 0xA3E4];	/* 2841_(A3E4 - A3E7h) */
	IoR2yEgcmpbtaga	egcmpbtaga;		/* 2841_(A3E8 - A3EFh) */
	IoR2yEgcmpclp		egcmpclp;			/* 2841_(A3F0 - A3F3h) */
	unsigned char 		dmyA3f4A3ff[0xA400 - 0xA3F4];	/* 2841_(A3F4 - A3FFh) */
};

/*	structure of crv area	2841_(A400 - A43Fh) */
struct _IoR2yCrv{
	IoR2yCrvaf			crvaf;			/* 2841_(A400 - A403h) */
	IoR2yCrvbf			crvbf;			/* 2841_(A404 - A407h) */
	unsigned char 	dmyA408A43f[0xA440 - 0xA408];		/* 2841_(A408 - A43Fh) */
};

/*	structure of egcrv area	2841_(A440 - A47Fh) */
struct _IoR2yEgcrv{
	IoR2yEgcrvctl			egcrvctl;			/* 2841_(A440 - A443h) */
	IoR2yEgcrvasclof	egcrvasclof;		/* 2841_(A444 - A447h) */
	IoR2yEgcrvasclga	egcrvasclga;	/* 2841_(A448 - A44Bh) */
	IoR2yEgcrvasclbd	egcrvasclbd;	/* 2841_(A44C - A44Fh) */
	IoR2yEgcrvasclcp	egcrvasclcp;	/* 2841_(A450 - A453h) */
	IoR2yEgyasclga		egyasclga;		/* 2841_(A454 - A457h) */
	IoR2yEgyasclbd		egyasclbd;		/* 2841_(A458 - A45Bh) */
	IoR2yEgyasclclp		egyasclclp;		/* 2841_(A45C - A45Fh) */
	IoR2yEgcrvbsclof	egcrvbsclof;	/* 2841_(A460 - A463h) */
	IoR2yEgcrvbsclga	egcrvbsclga;	/* 2841_(A464 - A467h) */
	IoR2yEgcrvbsclbd	egcrvbsclbd;	/* 2841_(A468 - A46Bh) */
	IoR2yEgcrvbsclcp	egcrvbsclcp;	/* 2841_(A46C - A46Fh) */
	IoR2yEgybsclga		egybsclga;		/* 2841_(A470 - A473h) */
	IoR2yEgybsclbd		egybsclbd;		/* 2841_(A474 - A477h) */
	IoR2yEgybsclclp		egybsclclp;		/* 2841_(A478 - A47Bh) */
	IoR2yEgcrvclp			egcrvclp;			/* 2841_(A47C - A47Fh) */
};

/*	structure of ybcrv area	2841_(A480 - A4FFh) */
struct _IoR2yYbcrv{
	IoR2yYbcrvctl			ybcrvctl;			/* 2841_(A480 - A483h) */
	IoR2yYbcrvaalpof	ybcrvaalpof;	/* 2841_(A484 - A487h) */
	IoR2yYbcrvaalpga	ybcrvaalpga;	/* 2841_(A488 - A48Bh) */
	IoR2yYbcrvaalpbd	ybcrvaalpbd;	/* 2841_(A48C - A48Fh) */
	IoR2yYbcrvaalpcp	ybcrvaalpcp;	/* 2841_(A490 - A493h) */
	IoR2yYbyaalpga		ybyaalpga;		/* 2841_(A494 - A497h) */
	IoR2yYbyaalpbd		ybyaalpbd;		/* 2841_(A498 - A49Bh) */
	IoR2yYbyaalpclp		ybyaalpclp;		/* 2841_(A49C - A49Fh) */
	IoR2yYbcrvbalpof	ybcrvbalpof;	/* 2841_(A4A0 - A4A3h) */
	IoR2yYbcrvbalpga	ybcrvbalpga;	/* 2841_(A4A4 - A4A7h) */
	IoR2yYbcrvbalpbd	ybcrvbalpbd;	/* 2841_(A4A8 - A4ABh) */
	IoR2yYbcrvbalpcp	ybcrvbalpcp;	/* 2841_(A4AC - A4AFh) */
	IoR2yYbybalpga		ybybalpga;		/* 2841_(A4B0 - A4B3h) */
	IoR2yYbybalpbd		ybybalpbd;		/* 2841_(A4B4 - A4B7h) */
	IoR2yYbybalpclp		ybybalpclp;		/* 2841_(A4B8 - A4BBh) */
	unsigned char 		dmyA4bcA4ff[0xA500 - 0xA4BC];		/* 2841_(A4BC - A4FFh) */
};

/*	structure of clpf area	2841_(A500 - A57Fh) */
struct _IoR2yClpf{
	IoR2yClpfctl		clpfctl;		/* 2841_(A500 - A503h) */
	unsigned char 	dmyA504A51f[0xA520 - 0xA504];	/* 2841_(A504 - A51Fh) */
	IoR2yClpfk			clpfk;			/* 2841_(A520 - A533h) */
	unsigned char 	dmyA534A53f[0xA540 - 0xA534];	/* 2841_(A534 - A53Fh) */
	IoR2yClpfof			clpfof;			/* 2841_(A540 - A543h) */
	unsigned char 	dmyA544A547[0xA548 - 0xA544];	/* 2841_(A544 - A547h) */
	IoR2yClpfga		clpfga;			/* 2841_(A548 - A54Fh) */
	IoR2yClpfbd		clpfbd;			/* 2841_(A550 - A557h) */
	unsigned char 	dmyA558A57f[0xA580 - 0xA558];	/* 2841_(A558 - A57Fh) */
};

/*	structure of csp area	2841_(A580 - BFFFh) */
struct _IoR2yCsp{
	IoR2yCsyctl			csyctl;			/* 2841_(A580 - A583h) */
	unsigned char 	dmyA584A587[0xAD88 - 0xAD84];	/* 2841_(A584 - A587h) */
	IoR2yCsyof			csyof;			/* 2841_(A588 - A58Fh) */
	IoR2yCsyga			csyga;			/* 2841_(A590 - A597h) */
	IoR2yCsybd			csybd;			/* 2841_(A598 - A59Fh) */
	IoR2yYcrvfx			ycrvfx;			/* 2841_(A5A0 - A5A3h) */
	IoR2yCfix				cfix;				/* 2841_(A5A4 - A5A7h) */
	IoR2yYcof			ycof;			/* 2841_(A5A8 - A5AFh) */
	unsigned char 	dmyA5b0Bfff[0xC000 - 0xA5B0];	/* 2841_(A5B0 - BFFFh) */
};

/* Define i/o mapping */
struct _IoR2yFr2y{
	/* JDSR2Y */
	IoR2yFr2yCntl		cntl;				/* 2841_(8000 - 801Fh) */
	IoR2yOfg				ofg;				/* 2841_(8020 - 807Fh) */
	IoR2yCca0			cca0;			/* 2841_(8080 - 8FFFh) */
	IoR2yMcc			mcc;			/* 2841_(9000 - 9FFFh) */
	IoR2yBtc				btc;				/* 2841_(A000 - A03Fh) */
	IoR2yTcArea		tc;				/* 2841_(A040 - A05Fh) */
	IoR2yGam			gam;			/* 2841_(A060 - A07Fh) */
	IoR2yCca1			cca1;			/* 2841_(A080 - A0FFh) */
	IoR2yYcArea		yc;				/* 2841_(A100 - A13Fh) */
	IoR2yYnr				ynr;				/* 2841_(A140 - A17Fh) */
	IoR2yEgsm			egsm;			/* 2841_(A180 - A1FFh) */
	IoR2yEghw			eghw;			/* 2841_(A200 - A27Fh) */
	IoR2yEgmw			egmw;			/* 2841_(A280 - A2FFh) */
	IoR2yEglw			eglw;			/* 2841_(A300 - A37Fh) */
	IoR2yEgdt			egdt;			/* 2841_(A380 - A39Fh) */
	IoR2yMapscl		mapscl;		/* 2841_(A3A0 - A3BFh) */
	IoR2yEgcmp		egcmp;		/* 2841_(A3C0 - A3FFh) */
	IoR2yCrv				crv;				/* 2841_(A400 - A43Fh) */
	IoR2yEgcrv			egcrv;			/* 2841_(A440 - A47Fh) */
	IoR2yYbcrv			ybcrv;			/* 2841_(A480 - A4FFh) */
	IoR2yClpf			clpf;				/* 2841_(A500 - A57Fh) */
	IoR2yCsp				csp;			/* 2841_(A580 - BFFFh) */
};


#endif /* __FR2Y6A_H__ */
