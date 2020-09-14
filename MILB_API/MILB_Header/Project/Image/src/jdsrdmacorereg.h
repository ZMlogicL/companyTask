/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-08
 *@author            :郑蛘钊
 *@brief             :jdsrdmacorereg
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */


#ifndef __JDSRDMA_CORE_REG_H__
#define __JDSRDMA_CORE_REG_H__


#include <klib.h>


#define JDSRDMA_TYPE_CORE_REG	        (jdsrdma_core_reg_get_type())
#define JDSRDMA_CORE_REG(obj)	        (K_TYPE_CHECK_INSTANCE_CAST((obj), JdsrdmaCoreReg))
#define JDSRDMA_IS_CORE_REG(obj)	    (K_TYPE_CHECK_INSTANCE_TYPE((obj), JDSRDMA_TYPE_CORE_REG))


typedef struct _JdsrdmaCoreReg          JdsrdmaCoreReg;
typedef struct _JdsrdmaCoreRegPrivate   JdsrdmaCoreRegPrivate;

typedef struct _IoRdmaCore              IoRdmaCore;

typedef union _IoRmdaCoreRdmatrg        IoRmdaCoreRdmatrg;
typedef union _IoRmdaCoreRdmaintenb     IoRmdaCoreRdmaintenb;
typedef union _IoRmdaCoreRdmaintflg     IoRmdaCoreRdmaintflg;
typedef union _IoRmdaCoreRdmaaxctl      IoRmdaCoreRdmaaxctl;
typedef union _IoRmdaCoreRdmabresp      IoRmdaCoreRdmabresp;
typedef union _IoRmdaCoreRdmaprcherr    IoRmdaCoreRdmaprcherr;


struct _JdsrdmaCoreReg
{
    KObject parent;
};


/*  structure of rdmatrg (2886_9100h)   */
union _IoRmdaCoreRdmatrg
{
    kulong word;
    struct
    {
        kulong rdmatrg :2;
        kulong :30;
    } bit;
};

/*  structure of rdmaintenb (2886_9104h)    */
union _IoRmdaCoreRdmaintenb
{
    kulong word;
    struct
    {
        kulong rdmae :1;
        kulong :3;
        kulong rdmaxe :1;
        kulong :27;
    } bit;
};

/*  structure of rdmaintflg (2886_9108h)    */
union _IoRmdaCoreRdmaintflg
{
    kulong word;
    struct
    {
        kulong rdmaf :1;
        kulong :3;
        kulong rdmaxf :1;
        kulong :27;
    } bit;
};

/*  structure of rdmaaxctl (2886_910Ch) */
union _IoRmdaCoreRdmaaxctl
{
    kulong word;
    struct
    {
        kulong awcache :4;
        kulong :4;
        kulong awprot :3;
        kulong :21;
    } bit;
};

/*  structure of rdmabresp (2886_9110h) */
union _IoRmdaCoreRdmabresp
{
    kulong word;
    struct
    {
        kulong rdmabresp :2;
        kulong :30;
    } bit;
};

/*  structure of rdmaprcherr (2886_9114h)   */
union _IoRmdaCoreRdmaprcherr
{
    kulong word;
    struct
    {
        kulong rdmaprcherr :1;
        kulong :31;
    } bit;
};

/* Define i/o mapping */
struct _IoRdmaCore
{
    /* JDSIMG */
    IoRmdaCoreRdmatrg rdmatrg; /* 2886_(9100 - 0103h) */
    IoRmdaCoreRdmaintenb rdmaintenb; /* 2886_(9104 - 0107h) */
    IoRmdaCoreRdmaintflg rdmaintflg; /* 2886_(9108 - 010Bh) */
    IoRmdaCoreRdmaaxctl rdmaaxctl; /* 2886_(910C - 010Fh) */
    IoRmdaCoreRdmabresp rdmabresp; /* 2886_(9110 - 0113h) */
    IoRmdaCoreRdmaprcherr rdmaprcherr; /* 2886_(9114 - 0117h) */

    kuchar dmy001800ff[0x0100 - 0x0018]; /* 2886_(9018 - 00FFh) */
};


KConstType      jdsrdma_core_reg_get_type(void);
JdsrdmaCoreReg* jdsrdma_core_reg_new(void);


#endif/*__JDSRDMA_CORE_REG_H__*/
