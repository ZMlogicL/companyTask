/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-09
*@author              :申雨
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年09月开始开发
*/


#ifndef __JDSPRO_P2M_H__
#define __JDSPRO_P2M_H__


#include <klib.h>


#define JDSPRO_TYPE_P2M				(jdspro_p2m_get_type())
#define JDSPRO_P2M(obj)				(K_TYPE_CHECK_INSTANCE_CAST((obj), JdsproP2m))
#define JDSPRO_IS_P2M(obj)			(K_TYPE_CHECK_INSTANCE_TYPE((obj), JDSPRO_TYPE_P2M))


typedef union 				_IoP2mtrg IoP2mtrg;
typedef union 				_IoP2mpaen IoP2mpaen;
typedef union 				_IoP2mctl IoP2mctl;
typedef union 				_IoP2mofs IoP2mofs;
typedef union 				_IoPbsft IoPbsft;
typedef union 				_IoPclph IoPclph;
typedef union 				_IoPtrmv IoPtrmv;
typedef union 				_IoPtrmh IoPtrmh;
typedef union 				_IoPtrmvw IoPtrmvw;
typedef union 				_IoPtrmhw IoPtrmhw;
typedef union 				_IoPtrmxvcyc IoPtrmxvcyc;
typedef union 				_IoPtrmxhcyc IoPtrmxhcyc;
typedef union 				_IoPtrmxven IoPtrmxven;
typedef union 				_IoPtrmxhen IoPtrmxhen;
typedef union 				_IoP2mmir IoP2mmir;
typedef union 				_IoP2m2pmd IoP2m2pmd;
typedef struct 				_IoP2m IoP2m;
typedef struct 				_JdsproP2m JdsproP2m;
typedef struct 				_JdsproP2mPrivate	JdsproP2mPrivate;

/*  structure of P2MTRG (2800_C000h)    */
union _IoP2mtrg{
    kulong       word;
    struct {
        kulong   p2mtrg  :2;
        kulong           :30;
    }bit;
};

/*  structure of P2MPAEN    (2800_C004h)    */
union _IoP2mpaen{
    kulong       word;
    struct {
        kulong   paen    :1;
        kulong           :31;
    }bit;
};

/*  structure of P2MCTL (2800_C008h)    */
union _IoP2mctl{
    kulong       word;
    struct {
        kulong   pknemd  :2;
        kulong           :2;
        kulong   plpf    :2;
        kulong           :2;
        kulong   p2mtyp  :2;
        kulong           :22;
    }bit;
};

/*  structure of P2MOFS (2800_C00Ch)    */
union _IoP2mofs{
    kulong       word;
    struct {
        long            p2mofs  :15;
        kulong           :17;
    }bit;
};

/*  structure of PBSFT  (2800_C010h)    */
union _IoPbsft{
    kulong       word;
    struct {
        kulong   pbsft   :4;
        kulong           :28;
    }bit;
};

/*  structure of PCLPH  (2800_C014h)    */
union _IoPclph{
    kulong       word;
    struct {
        kulong   pclph   :16;
        kulong           :16;
    }bit;
};

/*  structure of PTRMV  (2800_C050h)    */
union _IoPtrmv{
    kulong       word;
    struct {
        kulong   ptrmv   :14;
        kulong           :18;
    }bit;
};

/*  structure of PTRMH  (2800_C054h)    */
union _IoPtrmh{
    kulong       word;
    struct {
        kulong   ptrmh   :14;
        kulong           :18;
    }bit;
};

/*  structure of PTRMVW (2800_C058h)    */
union _IoPtrmvw{
    kulong       word;
    struct {
        kulong   ptrmvw  :16;
        kulong           :16;
    }bit;
};

/*  structure of PTRMHW (2800_C05Ch)    */
union _IoPtrmhw{
    kulong       word;
    struct {
        kulong   ptrmhw  :24;
        kulong           :8;
    }bit;
};

/*  structure of PTRMXVCYC  (2800_C060h)    */
union _IoPtrmxvcyc{
    kulong       word;
    struct {
        kulong   ptrmxvcyc   :6;
        kulong               :26;
    }bit;
};

/*  structure of PTRMXHCYC  (2800_C064h)    */
union _IoPtrmxhcyc{
    kulong       word;
    struct {
        kulong   ptrmxhcyc   :6;
        kulong               :26;
    }bit;
};

/*  structure of PTRMXVEN   (2800_C068h)    */
union _IoPtrmxven{
    unsigned long long      dword;
    struct {
        unsigned long long  ptrmxven    :64;
    }bit;
};

/*  structure of PTRMXHEN   (2800_C070h)    */
union _IoPtrmxhen{
    unsigned long long      dword;
    struct {
        unsigned long long  ptrmxhen    :64;
    }bit;
};

/*  structure of P2MMIR (2800_C078h)    */
union _IoP2mmir{
    kulong       word;
    struct {
        kulong   p2mmir  :1;
        kulong           :31;
    }bit;
};

/*  structure of P2M2PMD    (2800_C080h)    */
union _IoP2m2pmd{
    kulong       word;
    struct {
        kulong   p2m2pmd :1;
        kulong           :31;
    }bit;
};

/* Define i/o mapping */
struct _IoP2m{
    /* JDSIMG */
	/* 2800_(C000 - C003h) */
	IoP2mtrg     p2mtrg;
	/* 2800_(C004 - C007h) */
	IoP2mpaen    p2mpaen;
	/* 2800_(C008 - C00Bh) */
	IoP2mctl     p2mctl;
	/* 2800_(C00C - C00Fh) */
	IoP2mofs     p2mofs;
	/* 2800_(C010 - C013h) */
	IoPbsft      pbsft;
	/* 2800_(C014 - C017h) */
	IoPclph      pclph;
	/* 2800_(C018 - C04Fh) */
    kuchar dmyC018C04f[0xC050-0xC018];
    /* 2800_(C050 - C053h) */
    IoPtrmv      ptrmv;
    /* 2800_(C054 - C057h) */
    IoPtrmh      ptrmh;
    /* 2800_(C058 - C05Bh) */
    IoPtrmvw     ptrmvw;
    /* 2800_(C05C - C05Fh) */
    IoPtrmhw     ptrmhw;
    /* 2800_(C060 - C063h) */
    IoPtrmxvcyc  ptrmxvcyc;
    /* 2800_(C064 - C067h) */
    IoPtrmxhcyc  ptrmxhcyc;
    /* 2800_(C068 - C06Fh) */
    IoPtrmxven   ptrmxven;
    /* 2800_(C070 - C077h) */
    IoPtrmxhen   ptrmxhen;
    /* 2800_(C078 - C07Bh) */
    IoP2mmir     p2mmir;
    /* 2800_(C07C - C07Fh) */
    kuchar dmyC07cC07f[0xC080-0xC07C];
    /* 2800_(C080 - C083h) */
    IoP2m2pmd    p2m2pmd;
    /* 2800_(C084 - C0FFh) */
    kuchar dmyC084C0ff[0xC100-0xC084];
};

struct  _JdsproP2m
{
	KObject parent;
};


KConstType				jdspro_p2m_get_type(void);
JdsproP2m*			jdspro_p2m_new(void);


#endif/*__JDSPRO_P2M_H__*/
