/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-14
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
 * @file        jdsprolnr.h
 * @brief       Definition JDSPRO Macro I/O register
 * @note        None
 * @attention   None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */


#ifndef __JDSPRO_LNR_H__
#define __JDSPRO_LNR_H__


typedef union _IoLnrtrg  			IoLnrtrg;
typedef union _IoLnrbr1			IoLnrbr1;
typedef union _IoLnrbr2			IoLnrbr2;
typedef union _IoLnrbr3			IoLnrbr3;
typedef union _IoLnrbr4			IoLnrbr4;
typedef struct _IoLnrbr			IoLnrbr;
typedef union _IoLnrincr1		IoLnrincr1;
typedef union _IoLnrincr2		IoLnrincr2;
typedef union _IoLnrincr3		IoLnrincr3;
typedef union _IoLnrincr4		IoLnrincr4;
typedef struct _IoLnrincr			IoLnrincr;
typedef union _IoLnrofsr1		IoLnrofsr1;
typedef union _IoLnrofsr2		IoLnrofsr2;
typedef union _IoLnrofsr3		IoLnrofsr3;
typedef union _IoLnrofsr4		IoLnrofsr4;
typedef struct _IoLnrofsr			IoLnrofsr;
typedef union _IoLnrbgr1		IoLnrbgr1;
typedef union _IoLnrbgr2		IoLnrbgr2;
typedef union _IoLnrbgr3		IoLnrbgr3;
typedef union _IoLnrbgr4		IoLnrbgr4;
typedef struct _IoLnrbgr			IoLnrbgr;
typedef union _IoLnrincgr1		IoLnrincgr1;
typedef union _IoLnrincgr2		IoLnrincgr2;
typedef union _IoLnrincgr3		IoLnrincgr3;
typedef union _IoLnrincgr4  	IoLnrincgr4;
typedef struct _IoLnrincgr		IoLnrincgr;
typedef union _IoLnrofsgr1		IoLnrofsgr1;
typedef union _IoLnrofsgr2		IoLnrofsgr2;
typedef union _IoLnrofsgr3		IoLnrofsgr3;
typedef union _IoLnrofsgr4		IoLnrofsgr4;
typedef struct _IoLnrofsgr		IoLnrofsgr;
typedef union _IoLnrbgb1		IoLnrbgb1;
typedef union _IoLnrbgb2		IoLnrbgb2;
typedef union _IoLnrbgb3		IoLnrbgb3;
typedef union _IoLnrbgb4		IoLnrbgb4;
typedef struct _IoLnrbgb			IoLnrbgb;
typedef union _IoLnrincgb1	IoLnrincgb1;
typedef union _IoLnrincgb2	IoLnrincgb2;
typedef union _IoLnrincgb3	IoLnrincgb3;
typedef union _IoLnrincgb4	IoLnrincgb4;
typedef struct _IoLnrincgb		IoLnrincgb;
typedef union _IoLnrofsgb1	IoLnrofsgb1;
typedef union _IoLnrofsgb2	IoLnrofsgb2;
typedef union _IoLnrofsgb3	IoLnrofsgb3;
typedef union _IoLnrofsgb4	IoLnrofsgb4;
typedef struct _IoLnrofsgb		IoLnrofsgb;
typedef union _IoLnrbb1			IoLnrbb1;
typedef union _IoLnrbb2			IoLnrbb2;
typedef union _IoLnrbb3			IoLnrbb3;
typedef union _IoLnrbb4			IoLnrbb4;
typedef struct _IoLnrbb			IoLnrbb;
typedef union _IoLnrincb1		IoLnrincb1;
typedef union _IoLnrincb2		IoLnrincb2;
typedef union _IoLnrincb3		IoLnrincb3;
typedef union _IoLnrincb4		IoLnrincb4;
typedef struct _IoLnrincb		IoLnrincb;
typedef union _IoLnrofsb1		IoLnrofsb1;
typedef union _IoLnrofsb2		IoLnrofsb2;
typedef union _IoLnrofsb3		IoLnrofsb3;
typedef union _IoLnrofsb4		IoLnrofsb4;
typedef struct _IoLnrofsb		IoLnrofsb;
typedef struct _IoLnr				IoLnr;


/*  structure of lnrtrg (2800_AC00h)    */
union _IoLnrtrg{
    unsigned long       word;
    struct {
        unsigned long   lnrtrg  	:2;
        unsigned long           		:30;
    }bit;
};

/*  structure of lnrbr  (2800_AC10h)    */
union _IoLnrbr1{
    unsigned long       word;
    struct {
        unsigned long   lnrbr1 	:14;
        unsigned long           		:2;
        unsigned long   lnrbr2 	:14;
        unsigned long           		:2;
    }bit;
};

union _IoLnrbr2{
    unsigned long       word;
    struct {
        unsigned long   lnrbr3 	:14;
        unsigned long           		:2;
        unsigned long   lnrbr4 	:14;
        unsigned long           		:2;
    }bit;
};

union _IoLnrbr3{
    unsigned long       word;
    struct {
        unsigned long   lnrbr5 	:14;
        unsigned long           		:2;
        unsigned long   lnrbr6 	:14;
        unsigned long           		:2;
    }bit;
};

union _IoLnrbr4{
    unsigned long       word;
    struct {
        unsigned long   lnrbr7 	:14;
        unsigned long           		:2;
        unsigned long           		:16;
    }bit;
};

struct _IoLnrbr{
    IoLnrbr1 lnrbr1;
    IoLnrbr2 lnrbr2;
    IoLnrbr3 lnrbr3;
    IoLnrbr4 lnrbr4;
};

/*  structure of lnrincr    (2800_AC20h)    */
union _IoLnrincr1{
    unsigned long       word;
    struct {
        unsigned long   lnrincr0   	:10;
        unsigned long               		:6;
        unsigned long   lnrincr1   	:10;
        unsigned long               		:6;
    }bit;
};

union _IoLnrincr2{
    unsigned long       word;
    struct {
        unsigned long   lnrincr2   	:10;
        unsigned long               		:6;
        unsigned long   lnrincr3   	:10;
        unsigned long               		:6;
    }bit;
};

union _IoLnrincr3{
    unsigned long       word;
    struct {
        unsigned long   lnrincr4   	:10;
        unsigned long               		:6;
        unsigned long   lnrincr5   	:10;
        unsigned long               		:6;
    }bit;
};

union _IoLnrincr4{
    unsigned long       word;
    struct {
        unsigned long   lnrincr6   	:10;
        unsigned long               		:6;
        unsigned long   lnrincr7   	:10;
        unsigned long               		:6;
    }bit;
};

struct _IoLnrincr{
    IoLnrincr1   lnrincr1;
    IoLnrincr2   lnrincr2;
    IoLnrincr3   lnrincr3;
    IoLnrincr4   lnrincr4;
};

/*  structure of lnrofsr    (2800_AC30h)    */
union _IoLnrofsr1{
    unsigned long       word;
    struct {
        unsigned long   lnrofsr0   	:14;
        unsigned long               		:2;
        unsigned long   lnrofsr1   	:14;
        unsigned long               		:2;
    }bit;
};

union _IoLnrofsr2{
    unsigned long       word;
    struct {
        unsigned long   lnrofsr2   	:14;
        unsigned long               		:2;
        unsigned long   lnrofsr3   	:14;
        unsigned long               		:2;
    }bit;
};

union _IoLnrofsr3{
    unsigned long       word;
    struct {
        unsigned long   lnrofsr4   	:14;
        unsigned long               		:2;
        unsigned long   lnrofsr5   	:14;
        unsigned long               		:2;
    }bit;
};

union _IoLnrofsr4{
    unsigned long       word;
    struct {
        unsigned long   lnrofsr6   	:14;
        unsigned long               		:2;
        unsigned long   lnrofsr7   	:14;
        unsigned long               		:2;
    }bit;
};

struct _IoLnrofsr{
    IoLnrofsr1   lnrofsr1;
    IoLnrofsr2   lnrofsr2;
    IoLnrofsr3   lnrofsr3;
    IoLnrofsr4   lnrofsr4;
};

/*  structure of lnrbgr (2800_AC40h)    */
union _IoLnrbgr1{
    unsigned long       word;
    struct {
        unsigned long   lnrbgr1    	:14;
        unsigned long               		:2;
        unsigned long   lnrbgr2    	:14;
        unsigned long               		:2;
    }bit;
};

union _IoLnrbgr2{
    unsigned long       word;
    struct {
        unsigned long   lnrbgr3    	:14;
        unsigned long               		:2;
        unsigned long   lnrbgr4    	:14;
        unsigned long               		:2;
    }bit;
};

union _IoLnrbgr3{
    unsigned long       word;
    struct {
        unsigned long   lnrbgr5    	:14;
        unsigned long               		:2;
        unsigned long   lnrbgr6    	:14;
        unsigned long               		:2;
    }bit;
};

union _IoLnrbgr4{
    unsigned long       word;
    struct {
        unsigned long   lnrbgr7    	:14;
        unsigned long               		:2;
        unsigned long               		:16;
    }bit;
};

struct _IoLnrbgr{
    IoLnrbgr1    lnrbgr1;
    IoLnrbgr2    lnrbgr2;
    IoLnrbgr3    lnrbgr3;
    IoLnrbgr4    lnrbgr4;
};

/*  structure of lnrincgr   (2800_AC50h)    */
union _IoLnrincgr1{
    unsigned long       word;
    struct {
        unsigned long   lnrincgr0  	:10;
        unsigned long               		:6;
        unsigned long   lnrincgr1  	:10;
        unsigned long               		:6;
    }bit;
};

union _IoLnrincgr2{
    unsigned long       word;
    struct {
        unsigned long   lnrincgr2  	:10;
        unsigned long               		:6;
        unsigned long   lnrincgr3  	:10;
        unsigned long               		:6;
    }bit;
};

union _IoLnrincgr3{
    unsigned long       word;
    struct {
        unsigned long   lnrincgr4  	:10;
        unsigned long               		:6;
        unsigned long   lnrincgr5  	:10;
        unsigned long               		:6;
    }bit;
};

union _IoLnrincgr4{
    unsigned long       word;
    struct {
        unsigned long   lnrincgr6  	:10;
        unsigned long               		:6;
        unsigned long   lnrincgr7  	:10;
        unsigned long              		:6;
    }bit;
};

struct _IoLnrincgr{
    IoLnrincgr1  lnrincgr1;
    IoLnrincgr2  lnrincgr2;
    IoLnrincgr3  lnrincgr3;
    IoLnrincgr4  lnrincgr4;
};

/*  structure of lnrofsgr   (2800_AC60h)    */
union _IoLnrofsgr1{
    unsigned long       word;
    struct {
        unsigned long   lnrofsgr0  	:14;
        unsigned long               		:2;
        unsigned long   lnrofsgr1  	:14;
        unsigned long               		:2;
    }bit;
};

union _IoLnrofsgr2{
    unsigned long       word;
    struct {
        unsigned long   lnrofsgr2  	:14;
        unsigned long               		:2;
        unsigned long   lnrofsgr3  	:14;
        unsigned long               		:2;
    }bit;
};

union _IoLnrofsgr3{
    unsigned long       word;
    struct {
        unsigned long   lnrofsgr4  	:14;
        unsigned long               		:2;
        unsigned long   lnrofsgr5  	:14;
        unsigned long               		:2;
    }bit;
};

union _IoLnrofsgr4{
    unsigned long       word;
    struct {
        unsigned long   lnrofsgr6  	:14;
        unsigned long               		:2;
        unsigned long   lnrofsgr7  	:14;
        unsigned long               		:2;
    }bit;
};

struct _IoLnrofsgr{
    IoLnrofsgr1  lnrofsgr1;
    IoLnrofsgr2  lnrofsgr2;
    IoLnrofsgr3  lnrofsgr3;
    IoLnrofsgr4  lnrofsgr4;
};

/*  structure of lnrbgb (2800_AC70h)    */
union _IoLnrbgb1{
    unsigned long       word;
    struct {
        unsigned long   lnrbgb1    	:14;
        unsigned long               		:2;
        unsigned long   lnrbgb2    	:14;
        unsigned long               		:2;
    }bit;
};

union _IoLnrbgb2{
    unsigned long       word;
    struct {
        unsigned long   lnrbgb3    	:14;
        unsigned long               		:2;
        unsigned long   lnrbgb4    	:14;
        unsigned long               		:2;
    }bit;
};

union _IoLnrbgb3{
    unsigned long       word;
    struct {
        unsigned long   lnrbgb5    	:14;
        unsigned long               		:2;
        unsigned long   lnrbgb6    	:14;
        unsigned long               		:2;
    }bit;
};

union _IoLnrbgb4{
    unsigned long       word;
    struct {
        unsigned long   lnrbgb7    	:14;
        unsigned long               		:2;
        unsigned long               		:16;
    }bit;
};

struct _IoLnrbgb{
    IoLnrbgb1    lnrbgb1;
    IoLnrbgb2    lnrbgb2;
    IoLnrbgb3    lnrbgb3;
    IoLnrbgb4    lnrbgb4;
};

/*  structure of lnrincgb   (2800_AC80h)    */
union _IoLnrincgb1{
    unsigned long       word;
    struct {
        unsigned long   lnrincgb0  	:10;
        unsigned long               		:6;
        unsigned long   lnrincgb1  	:10;
        unsigned long               		:6;
    }bit;
};

union _IoLnrincgb2{
    unsigned long       word;
    struct {
        unsigned long   lnrincgb2  	:10;
        unsigned long               		:6;
        unsigned long   lnrincgb3  	:10;
        unsigned long               		:6;
    }bit;
};

union _IoLnrincgb3{
    unsigned long       word;
    struct {
        unsigned long   lnrincgb4  	:10;
        unsigned long               		:6;
        unsigned long   lnrincgb5  	:10;
        unsigned long               		:6;
    }bit;
};

union _IoLnrincgb4{
    unsigned long       word;
    struct {
        unsigned long   lnrincgb6  	:10;
        unsigned long               		:6;
        unsigned long   lnrincgb7  	:10;
        unsigned long               		:6;
    }bit;
};

struct _IoLnrincgb{
    IoLnrincgb1  lnrincgb1;
    IoLnrincgb2  lnrincgb2;
    IoLnrincgb3  lnrincgb3;
    IoLnrincgb4  lnrincgb4;
};

/*  structure of lnrofsgb   (2800_AC90h)    */
union _IoLnrofsgb1{
    unsigned long       word;
    struct {
        unsigned long   lnrofsgb0  	:14;
        unsigned long               		:2;
        unsigned long   lnrofsgb1  	:14;
        unsigned long               		:2;
    }bit;
};

union _IoLnrofsgb2{
    unsigned long       word;
    struct {
        unsigned long   lnrofsgb2  	:14;
        unsigned long               		:2;
        unsigned long   lnrofsgb3  	:14;
        unsigned long               		:2;
    }bit;
};

union _IoLnrofsgb3{
    unsigned long       word;
    struct {
        unsigned long   lnrofsgb4  	:14;
        unsigned long               		:2;
        unsigned long   lnrofsgb5  	:14;
        unsigned long               		:2;
    }bit;
};

union _IoLnrofsgb4{
    unsigned long       word;
    struct {
        unsigned long   lnrofsgb6  	:14;
        unsigned long               		:2;
        unsigned long   lnrofsgb7  	:14;
        unsigned long               		:2;
    }bit;
};

struct _IoLnrofsgb{
    IoLnrofsgb1  lnrofsgb1;
    IoLnrofsgb2  lnrofsgb2;
    IoLnrofsgb3  lnrofsgb3;
    IoLnrofsgb4  lnrofsgb4;
};

/*  structure of lnrbb  (2800_ACA0h)    */
union _IoLnrbb1{
    unsigned long       word;
    struct {
        unsigned long   lnrbb1 	:14;
        unsigned long           		:2;
        unsigned long   lnrbb2 	:14;
        unsigned long           		:2;
    }bit;
};

union _IoLnrbb2{
    unsigned long       word;
    struct {
        unsigned long   lnrbb3 	:14;
        unsigned long           		:2;
        unsigned long   lnrbb4 	:14;
        unsigned long           		:2;
    }bit;
};

union _IoLnrbb3{
    unsigned long       word;
    struct {
        unsigned long   lnrbb5 	:14;
        unsigned long           		:2;
        unsigned long   lnrbb6 	:14;
        unsigned long           		:2;
    }bit;
};

union _IoLnrbb4{
    unsigned long       word;
    struct {
        unsigned long   lnrbb7 	:14;
        unsigned long           		:2;
        unsigned long           		:16;
    }bit;
};

struct _IoLnrbb{
    IoLnrbb1 lnrbb1;
    IoLnrbb2 lnrbb2;
    IoLnrbb3 lnrbb3;
    IoLnrbb4 lnrbb4;
};

/*  structure of lnrincb    (2800_ACB0h)    */
union _IoLnrincb1{
    unsigned long       word;
    struct {
        unsigned long   lnrincb0   	:10;
        unsigned long               		:6;
        unsigned long   lnrincb1   	:10;
        unsigned long               		:6;
    }bit;
};

union _IoLnrincb2{
    unsigned long       word;
    struct {
        unsigned long   lnrincb2   	:10;
        unsigned long               		:6;
        unsigned long   lnrincb3   	:10;
        unsigned long               		:6;
    }bit;
};

union _IoLnrincb3{
    unsigned long       word;
    struct {
        unsigned long   lnrincb4   	:10;
        unsigned long               		:6;
        unsigned long   lnrincb5   	:10;
        unsigned long               		:6;
    }bit;
};

union _IoLnrincb4{
    unsigned long       word;
    struct {
        unsigned long   lnrincb6   	:10;
        unsigned long               		:6;
        unsigned long   lnrincb7   	:10;
        unsigned long               		:6;
    }bit;
};

struct _IoLnrincb{
    IoLnrincb1   lnrincb1;
    IoLnrincb2   lnrincb2;
    IoLnrincb3   lnrincb3;
    IoLnrincb4   lnrincb4;
};

/*  structure of lnrofsb    (2800_ACC0h)    */
union _IoLnrofsb1{
    unsigned long       word;
    struct {
        unsigned long   lnrofsb0   	:14;
        unsigned long               		:2;
        unsigned long   lnrofsb1   	:14;
        unsigned long               		:2;
    }bit;
};

union _IoLnrofsb2{
    unsigned long       word;
    struct {
        unsigned long   lnrofsb2   	:14;
        unsigned long               		:2;
        unsigned long   lnrofsb3   	:14;
        unsigned long               		:2;
    }bit;
};

union _IoLnrofsb3{
    unsigned long       word;
    struct {
        unsigned long   lnrofsb4   	:14;
        unsigned long               		:2;
        unsigned long   lnrofsb5   	:14;
        unsigned long               		:2;
    }bit;
};

union _IoLnrofsb4{
    unsigned long       word;
    struct {
        unsigned long   lnrofsb6   	:14;
        unsigned long               		:2;
        unsigned long   lnrofsb7   	:14;
        unsigned long               		:2;
    }bit;
};

struct _IoLnrofsb{
    IoLnrofsb1   lnrofsb1;
    IoLnrofsb2   lnrofsb2;
    IoLnrofsb3   lnrofsb3;
    IoLnrofsb4   lnrofsb4;
};

/* Define i/o mapping */
struct _IoLnr{
    /* JDSIMG */
    IoLnrtrg     			lnrtrg;                /* 2800_(AC00 - AC03h) */
    unsigned char 	dmyAc04Ac0f[0xAC10 - 0xAC04]; /* 2800_(AC04 - AC0Fh) */
    IoLnrbr      			lnrbr;                 /* 2800_(AC10 - AC1Fh) */
    IoLnrincr    			lnrincr;               /* 2800_(AC20 - AC2Fh) */
    IoLnrofsr    			lnrofsr;               /* 2800_(AC30 - AC3Fh) */
    IoLnrbgr     			lnrbgr;                /* 2800_(AC40 - AC4Fh) */
    IoLnrincgr   		lnrincgr;              /* 2800_(AC50 - AC5Fh) */
    IoLnrofsgr   		lnrofsgr;              /* 2800_(AC60 - AC6Fh) */
    IoLnrbgb     		lnrbgb;                /* 2800_(AC70 - AC7Fh) */
    IoLnrincgb   		lnrincgb;              /* 2800_(AC80 - AC8Fh) */
    IoLnrofsgb   		lnrofsgb;              /* 2800_(AC90 - AC9Fh) */
    IoLnrbb      			lnrbb;                 /* 2800_(ACA0 - ACAFh) */
    IoLnrincb    		lnrincb;               /* 2800_(ACB0 - ACBFh) */
    IoLnrofsb    		lnrofsb;               /* 2800_(ACC0 - ACCFh) */
    unsigned char 	dmyAcd0Acff[0xAD00 - 0xACD0]; /* 2800_(ACD0 - ACFFh) */
};


#endif /* __JDSPRO_LNR_H__ */
