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


#ifndef __JDSDISP_HDMI_H__
#define __JDSDISP_HDMI_H__


#include <stdio.h>
#include <glib-object.h>


typedef union 				_IoJddispHdmiHdmisr IoJddispHdmiHdmisr;
typedef struct 				_IoJddispHdmi IoJddispHdmi;

union _IoJddispHdmiHdmisr{
    gulong       word;
    struct {
        gulong   sr  :1;
        gulong       :31;
    }bit;
};

/* Define i/o mapping */
struct _IoJddispHdmi{
    /* JDSIMG */
	/* 2890_(E000 - E003h) */
	IoJddispHdmiHdmisr    hdmisr;
	/* 2890_(E004 - EFFFh) */
    guchar dmyE004Efff[0xF000-0xE004];
};


#endif/*__JDSDISP_HDMI_H__*/
