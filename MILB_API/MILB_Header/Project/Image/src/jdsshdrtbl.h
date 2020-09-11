/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-10
 *@author            :郑蛘钊
 *@brief             :Definition SHDR TBL Macro I/O register
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */

#ifndef __JDSSHDR_TBL_H__
#define __JDSSHDR_TBL_H__

#include <klib.h>

#define JDSSHDR_TYPE_TBL	(jdsshdr_tbl_get_type())
#define JDSSHDR_TBL(obj)	(K_TYPE_CHECK_INSTANCE_CAST((obj), JdsshdrTbl))
#define JDSSHDR_IS_TBL(obj)	(K_TYPE_CHECK_INSTANCE_TYPE((obj), JDSSHDR_TYPE_TBL))

typedef struct _JdsshdrTbl JdsshdrTbl;
typedef struct _JdsshdrTblPrivate JdsshdrTblPrivate;

typedef struct _IoJdsshdrTbl IoJdsshdrTbl;

typedef union _IoShdrDgtr IoShdrDgtr;
typedef union _IoShdrDgtg IoShdrDgtg;
typedef union _IoShdrDgtb IoShdrDgtb;

struct _JdsshdrTbl
{
    KObject parent;
};

/*  structure of dgtr       */
union _IoShdrDgtr
{
    unsigned short hword[256];
    struct
    {
        unsigned short dgtr :12;
        unsigned short :4;
    } bit[256];
};

/*  structure of dgtg       */
union _IoShdrDgtg
{
    unsigned short hword[256];
    struct
    {
        unsigned short dgtg :12;
        unsigned short :4;
    } bit[256];
};

/*  structure of dgtb       */
union _IoShdrDgtb
{
    unsigned short hword[256];
    struct
    {
        unsigned short dgtb :12;
        unsigned short :4;
    } bit[256];
};

/* Define i/o mapping */
struct _IoJdsshdrTbl
{
    /* JDSSHDR */
    IoShdrDgtr dgtr; /* (0000 - 01FFh) */
    IoShdrDgtg dgtg; /* (0200 - 03FFh) */
    IoShdrDgtb dgtb; /* (0400 - 05FFh) */

    unsigned char dmy060007ff[0x00800 - 0x0600]; /* (0600 - 07FFh) */
};

extern volatile IoJdsshdrTbl ioShdrTbl;

KConstType jdsshdr_tbl_get_type(void);
JdsshdrTbl* jdsshdr_tbl_new(void);

#endif/*__JDSSHDR_TBL_H__*/

