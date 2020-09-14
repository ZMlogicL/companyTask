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


#ifndef __JDSDISP_DBG_H__
#define __JDSDISP_DBG_H__


#include <stdio.h>
#include <glib-object.h>


typedef union 				_IoJdsddbgRegDbgsl IoJdsddbgRegDbgsl;
typedef struct 				_IoJdsddbgReg IoJdsddbgReg;

union _IoJdsddbgRegDbgsl{
    gulong       word;
    struct {
        gulong   vdmsl   :1;
        gulong           :3;
        gulong   hdmsl   :1;
        gulong           :3;
        gulong   hdemsl  :1;
        gulong           :23;
    }bit;
};

/* Define i/o mapping */
struct _IoJdsddbgReg{
    /* JDSIMG */
	/* 2890_(B000 - B003h) */
	IoJdsddbgRegDbgsl dbgsl;
	/* 2890_(B004 - BFFFh) */
    guchar dmyB004Bfff[0xC000-0xB004];
};


#endif/*__JDSDISP_DBG_H__*/
