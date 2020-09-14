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


#ifndef __JDSDISP_LCH_TBL_H__
#define __JDSDISP_LCH_TBL_H__


#include <stdio.h>
#include <glib-object.h>


typedef union 				_IoJdslchIgtbl IoJdslchIgtbl;
typedef struct 				_IoJdslchIgtblRgb IoJdslchIgtblRgb;
typedef union 				_IoJdslchGtbl IoJdslchGtbl;
typedef struct 				_IoJdslchGtblRgb IoJdslchGtblRgb;
typedef struct 				_IoJdslchTbl IoJdslchTbl;

/*  structure of IGTBLxy (298E_0000h) x=A/B, y=R/G/B */
union _IoJdslchIgtbl{
    gushort      hword[32];
    struct {
        gushort  ig      :12;
        gushort          :4;
    }bit[32];
};

/*  structure of IGTBLAR ~ IGTBLAB / IGTBLBR ~ IGTBLBB */
struct _IoJdslchIgtblRgb{
	IoJdslchIgtbl    igtblr;
	IoJdslchIgtbl    igtblg;
	IoJdslchIgtbl    igtblb;
};

/*  structure of GTBLxy (298E_2000h) x=A/B, y=R/G/B */
union _IoJdslchGtbl{
    gushort      hword[32];
    struct {
        gushort  gm      :12;
        gushort          :4;
    }bit[32];
};

/*  structure of GTBLAR ~ GTBLAB / GTBLBR ~ GTBLBB */
struct _IoJdslchGtblRgb{
	IoJdslchGtbl       gtblr;
	IoJdslchGtbl       gtblg;
	IoJdslchGtbl       gtblb;
};

/* Define i/o mapping */
struct _IoJdslchTbl{
    /* JDSIMG */
	/* 298E_(0000 - 00BFh) */
	IoJdslchIgtblRgb      igtbla;
	/* 298E_(00C0 - 00FFh) */
    guchar dmy00c000ff[0x0100-0x00C0];
    /* 298E_(0100 - 01BFh) */
    IoJdslchIgtblRgb      igtblb;
    /* 298E_(01C0 - 1FFFh) */
    guchar dmy01c01fff[0x2000-0x01C0];
    /* 298E_(2000 - 20BFh) */
    IoJdslchGtblRgb       gtbla;
    /* 298E_(20C0 - 20FFh) */
    guchar dmy20c020ff[0x2100-0x20C0];
    /* 298E_(2100 - 21BFh) */
    IoJdslchGtblRgb       gtblb;
    /* 298E_(21C0 - 3FFFh) */
    guchar dmy21c03fff[0x4000-0x21C0];
};


#endif/*__JDSDISP_LCH_TBL_H__*/
