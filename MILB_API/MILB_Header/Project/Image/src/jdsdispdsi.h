/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-09
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


#ifndef __JDSDISP_DSI_H__
#define __JDSDISP_DSI_H__


#include <stdio.h>
#include <glib-object.h>


typedef union 				_IoJdsdispDsiMdsic0 IoJdsdispDsiMdsic0;
typedef union 				_IoJdsdispDsiMdsic1 IoJdsdispDsiMdsic1;
typedef union 				_IoJdsdispDsiMdssr IoJdsdispDsiMdssr;
typedef struct 				_IoJdsdispDsi IoJdsdispDsi;

union _IoJdsdispDsiMdsic0{
    gulong       word;
    struct {
        gulong   mdssd   :1;
        gulong           :7;
        gulong   mdscm   :1;
        gulong           :23;
    }bit;
};

/*  structure of MDSIC1 (2890_D004h)    */
union _IoJdsdispDsiMdsic1{
    gulong       word;
    struct {
        gulong   mdsudc  :2;
        gulong           :30;
    }bit;
};

/*  structure of MDSSR  (2890_D100h)    */
union _IoJdsdispDsiMdssr{
    gulong       word;
    struct {
        gulong   sr  :1;
        gulong       :31;
    }bit;
};

/* Define i/o mapping */
struct _IoJdsdispDsi{
    /* JDSIMG */
	/* 2890_(D000 - D003h) */
	IoJdsdispDsiMdsic0    mdsic0;
	/* 2890_(D004 - D007h) */
	IoJdsdispDsiMdsic1    mdsic1;
	/* 2890_(D008 - D0FFh) */
    guchar dmyD008D0ff[0xD100-0xD008];
    /* 2890_(D100 - D103h) */
    IoJdsdispDsiMdssr     mdssr;
    /* 2890_(D104 - DFFFh) */
    guchar dmyD104Dfff[0xE000-0xD104];
};


#endif/*__JDSDISP_DSI_H__*/
