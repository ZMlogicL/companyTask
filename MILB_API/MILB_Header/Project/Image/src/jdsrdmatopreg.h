/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-08
 *@author            :郑蛘钊
 *@brief             :jdsrdmatopreg
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */


#ifndef __JDSRDMA_TOP_REG_H__
#define __JDSRDMA_TOP_REG_H__


#include <klib.h>


#define JDSRDMA_TYPE_TOP_REG	        (jdsrdma_top_reg_get_type())
#define JDSRDMA_TOP_REG(obj)	        (K_TYPE_CHECK_INSTANCE_CAST((obj), JdsrdmaTopReg))
#define JDSRDMA_IS_TOP_REG(obj)	        (K_TYPE_CHECK_INSTANCE_TYPE((obj), JDSRDMA_TYPE_TOP_REG))


typedef struct _JdsrdmaTopReg           JdsrdmaTopReg;
typedef struct _JdsrdmaTopRegPrivate    JdsrdmaTopRegPrivate;

typedef struct _IoRdmaTop               IoRdmaTop;

typedef union _IoRmdaTopSr              IoRmdaTopSr;
typedef union _IoRmdaTopIntmon1         IoRmdaTopIntmon1;
typedef union _IoRmdaTopIntmon2         IoRmdaTopIntmon2;
typedef union _IoRmdaTopIntctl          IoRmdaTopIntctl;
typedef union _IoRmdaTopVdgen0          IoRmdaTopVdgen0;
typedef union _IoRmdaTopVdgen1          IoRmdaTopVdgen1;


struct _JdsrdmaTopReg
{
    KObject parent;
};


/*  structure of sr (2886_9000h)    */
union _IoRmdaTopSr
{
    kulong word;
    struct
    {
        kulong sr :1;
        kulong :31;
    } bit;
};

/*  structure of intmon1 (2886_9004h)   */
union _IoRmdaTopIntmon1
{
    kulong word;
    struct
    {
        kulong rdmaf :1;
        kulong prf0 :1;
        kulong prf1 :1;
        kulong :29;
    } bit;
};

/*  structure of intmon2 (2886_9008h)   */
union _IoRmdaTopIntmon2
{
    kulong word;
    struct
    {
        kulong rdmaxf :1;
        kulong prxf0 :1;
        kulong prxf1 :1;
        kulong :29;
    } bit;
};

/*  structure of intctl (2886_900Ch)    */
union _IoRmdaTopIntctl
{
    kulong word;
    struct
    {
        kulong intmd :2;
        kulong :30;
    } bit;
};

/*  structure of vdgen0 (2886_9010h)    */
union _IoRmdaTopVdgen0
{
    kulong word;
    struct
    {
        kulong vdgen0 :1;
        kulong :31;
    } bit;
};

/*  structure of vdgen1 (2886_9014h)    */
union _IoRmdaTopVdgen1
{
    kulong word;
    struct
    {
        kulong vdgen1 :1;
        kulong :31;
    } bit;
};

/* Define i/o mapping */
struct _IoRdmaTop
{
    /* JDSIMG */
    IoRmdaTopSr sr; /* 2886_(9000 - 0003h) */
    IoRmdaTopIntmon1 intmon1; /* 2886_(9004 - 0007h) */
    IoRmdaTopIntmon2 intmon2; /* 2886_(9008 - 000Bh) */
    IoRmdaTopIntctl intctl; /* 2886_(900C - 000Fh) */
    IoRmdaTopVdgen0 vdgen0; /* 2886_(9010 - 0013h) */
    IoRmdaTopVdgen1 vdgen1; /* 2886_(9014 - 0017h) */

    kuchar dmy001800ff[0x0100 - 0x0018]; /* 2886_(9018 - 00FFh) */
};


KConstType      jdsrdma_top_reg_get_type(void);
JdsrdmaTopReg*  jdsrdma_top_reg_new(void);


#endif/*__JDSRDMA_TOP_REG_H__*/
