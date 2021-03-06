/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-10
*@author              :申雨
*@brief               :sns 索喜rtos
*@rely                :glib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年09月开始开发
*/


#ifndef __JDSDISP_DCORE_TBL_H__
#define __JDSDISP_DCORE_TBL_H__


#include <stdio.h>
#include <glib-object.h>


typedef union 				_IoJdsdcoreGtbl IoJdsdcoreGtbl;
typedef struct 				_IoJdsdcoreGtblRgb IoJdsdcoreGtblRgb;
typedef union 				_IoJdsdcoreYstbl IoJdsdcoreYstbl;
typedef struct 				_IoJdsdcoreTbl IoJdsdcoreTbl;

/*  structure of GTBLxy (298E_5000h) x=A/B, y=R/G/B    */
union _IoJdsdcoreGtbl{
    gushort      hword[33];
    struct {
        gushort  gm      :8;
        gushort          :8;
    }bit[33];
};

/*  structure of GTBLAR ~ GTBLAB / GTBLBR ~ GTBLBB */
struct _IoJdsdcoreGtblRgb{
	/* 000 - 041h */
	IoJdsdcoreGtbl     gtblr;
	/* 042 - 07Fh */
    guchar dmy0042007f[0x0080-0x0042];
    /* 080 - 0C1h */
    IoJdsdcoreGtbl     gtblg;
    /* 0C2 - 0FFh) */
    guchar dmy00c200ff[0x0100-0x00C2];
    /* 100 - 141h */
    IoJdsdcoreGtbl     gtblb;
    /* 142 - 1FFh */
    guchar dmy014201ff[0x0200-0x0142];
};

/*  structure of YSTBLAYT (298E_6000h) / YSTBLACG (298E_6080h) / YSTBLBYT (298E_6100h) / YSTBLBCG (298E_6180h) */
union _IoJdsdcoreYstbl{
    gushort      hword[33];
    struct {
        gushort  ysat    :8;
        gushort          :8;
    }bit[33];
};

/* Define i/o mapping */
struct _IoJdsdcoreTbl{
    /* JDSIMG */
	/* 298E_(4000 - 4FFFh) */
    guchar dmy40004fff[0x5000-0x4000];
    /* 298E_(5000 - 51FFh) */
    IoJdsdcoreGtblRgb     gtbla;
    /* 298E_(5200 - 53FFh) */
    IoJdsdcoreGtblRgb     gtblb;
    /* 298E_(5400 - 5FFFh) */
    guchar dmy53425fff[0x6000-0x5400];
    /* 298E_(6000 - 6041h) */
    IoJdsdcoreYstbl        ystblayt;
    /* 298E_(6042 - 607Fh) */
    guchar dmy6042607f[0x6080-0x6042];
    /* 298E_(6080 - 60C1h) */
    IoJdsdcoreYstbl        ystblacg;
    /* 298E_(60C2 - 60FFh) */
    guchar dmy60c260ff[0x6100-0x60C2];
    /* 298E_(6100 - 6141h) */
    IoJdsdcoreYstbl        ystblbyt;
    /* 298E_(6142 - 617Fh) */
    guchar dmy6142617f[0x6180-0x6142];
    /* 298E_(6180 - 61C1h) */
    IoJdsdcoreYstbl        ystblbcg;
    /* 298E_(61C2 - 7FFFh) */
    guchar dmy61c27fff[0x8000-0x61C2];
};


#endif/*__JDSDISP_DCORE_TBL_H__*/
