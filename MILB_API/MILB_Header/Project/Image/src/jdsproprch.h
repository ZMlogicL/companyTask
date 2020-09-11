/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-08
 *@author            :郑蛘钊
 *@brief             :Definition JDSPRO Macro I/O register
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */

#ifndef __JDSPRO_PRCH_H__
#define __JDSPRO_PRCH_H__

#ifndef _IO_PRO_PRCH_H_
#define _IO_PRO_PRCH_H_

#include <klib.h>

#define JDSPRO_TYPE_PRCH	(jdspro_prch_get_type())
#define JDSPRO_PRCH(obj)	(K_TYPE_CHECK_INSTANCE_CAST((obj), JdsproPrch))
#define JDSPRO_IS_PRCH(obj)	(K_TYPE_CHECK_INSTANCE_TYPE((obj), JDSPRO_TYPE_PRCH))

typedef struct _JdsproPrch JdsproPrch;
typedef struct _JdsproPrchPrivate JdsproPrchPrivate;

typedef struct _IoPrch IoPrch;

typedef union _IoPrchtrg IoPrchtrg;
typedef union _IoPrchctl IoPrchctl;
typedef union _IoPrchrs IoPrchrs;
typedef union _IoPraxctl IoPraxctl;
typedef union _IoPrchintenb IoPrchintenb;
typedef union _IoPrchintflg IoPrchintflg;
typedef union _IoPrchbresp IoPrchbresp;
typedef union _IoPrsa IoPrsa;
typedef union _IoPrlsize IoPrlsize;
typedef union _IoPrvsize IoPrvsize;
typedef union _IoPrhsize IoPrhsize;

struct _JdsproPrch
{
    KObject parent;
};

/*  structure of prchtrg    (2840_B200h)    */
union _IoPrchtrg
{
    unsigned long word;
    struct
    {
        unsigned long prchtrg :2;
        unsigned long :30;
    } bit;
};

/*  structure of prchctl    (2840_B204h)    */
union _IoPrchctl
{
    unsigned long word;
    struct
    {
        unsigned long prbmd :2;
        unsigned long :2;
        unsigned long prlv :4;
        unsigned long :24;
    } bit;
};

/*  structure of prchrs (2840_B208h)    */
union _IoPrchrs
{
    unsigned long word;
    struct
    {
        unsigned long prs :1;
        unsigned long :31;
    } bit;
};

/*  structure of praxctl    (2840_B20Ch)    */
union _IoPraxctl
{
    unsigned long word;
    struct
    {
        unsigned long arcache :4;
        unsigned long :4;
        unsigned long arprot :3;
        unsigned long :21;
    } bit;
};

/*  structure of prchintenb (2840_B210h)    */
union _IoPrchintenb
{
    unsigned long word;
    struct
    {
        unsigned long pre :1;
        unsigned long :3;
        unsigned long pree :1;
        unsigned long :3;
        unsigned long prxe :1;
        unsigned long :23;
    } bit;
};

/*  structure of prchintflg (2840_B214h)    */
union _IoPrchintflg
{
    unsigned long word;
    struct
    {
        unsigned long prf :1;
        unsigned long :3;
        unsigned long pref :1;
        unsigned long :3;
        unsigned long prxf :1;
        unsigned long :23;
    } bit;
};

/*  structure of prchbresp  (2840_B218h)    */
union _IoPrchbresp
{
    unsigned long word;
    struct
    {
        unsigned long prchbresp :2;
        unsigned long :30;
    } bit;
};

/*  structure of prsa   (2840_B21Ch)    */
union _IoPrsa
{
    unsigned long word;
    struct
    {
        unsigned long prsa :32;
    } bit;
};

/*  structure of prlsize    (2840_B220h)    */
union _IoPrlsize
{
    unsigned long word;
    struct
    {
        unsigned long prlsize :32;
    } bit;
};

/*  structure of prvsize    (2840_B224h)    */
union _IoPrvsize
{
    unsigned long word;
    struct
    {
        unsigned long prvsize :14;
        unsigned long :18;
    } bit;
};

/*  structure of prhsize    (2840_B228h)    */
union _IoPrhsize
{
    unsigned long word;
    struct
    {
        unsigned long prhsize :24;
        unsigned long :8;
    } bit;
};

/* Define i/o mapping */
struct _IoPrch
{
    /* JDSIMG */
    IoPrchtrg prchtrg; /* 2840_(B200 - B203h) */
    IoPrchctl prchctl; /* 2840_(B204 - B207h) */
    IoPrchrs prchrs; /* 2840_(B208 - B20Bh) */
    IoPraxctl praxctl; /* 2840_(B20C - B20Fh) */
    IoPrchintenb prchintenb; /* 2840_(B210 - B213h) */
    IoPrchintflg prchintflg; /* 2840_(B214 - B217h) */
    IoPrchbresp prchbresp; /* 2840_(B218 - B21Bh) */
    IoPrsa prsa; /* 2840_(B21C - B21Fh) */
    IoPrlsize prlsize; /* 2840_(B220 - B223h) */
    IoPrvsize prvsize; /* 2840_(B224 - B227h) */
    IoPrhsize prhsize; /* 2840_(B228 - B22Bh) */

    unsigned char dmyB22cB2ff[0xB300 - 0xB22C]; /* 2840_(B22C - B2FFh) */
};

KConstType jdspro_prch_get_type(void);
JdsproPrch* jdspro_prch_new(void);

#endif  // _IO_PRO_PRCH_H_
#endif/*__JDSPRO_PRCH_H__*/

