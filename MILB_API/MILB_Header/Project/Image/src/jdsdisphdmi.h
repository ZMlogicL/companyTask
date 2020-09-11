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


#ifndef __JDSDISP_HDMI_H__
#define __JDSDISP_HDMI_H__


#include <klib.h>


#define JDSDISP_TYPE_HDMI				(jdsdisp_hdmi_get_type())
#define JDSDISP_HDMI(obj)				(K_TYPE_CHECK_INSTANCE_CAST((obj), JdsdispHdmi))
#define JDSDISP_IS_HDMI(obj)			(K_TYPE_CHECK_INSTANCE_TYPE((obj), JDSDISP_TYPE_HDMI))


typedef union 				_IoJddispHdmiHdmisr IoJddispHdmiHdmisr;
typedef struct 				_IoJddispHdmi IoJddispHdmi;
typedef struct 				_JdsdispHdmi JdsdispHdmi;
typedef struct 				_JdsdispHdmiPrivate	JdsdispHdmiPrivate;

union _IoJddispHdmiHdmisr{
    kulong       word;
    struct {
        kulong   sr  :1;
        kulong       :31;
    }bit;
};

/* Define i/o mapping */
struct _IoJddispHdmi{
    /* JDSIMG */
	/* 2890_(E000 - E003h) */
	IoJddispHdmiHdmisr    hdmisr;
	/* 2890_(E004 - EFFFh) */
    kuchar dmyE004Efff[0xF000-0xE004];
};

struct  _JdsdispHdmi
{
	KObject parent;
};


KConstType				jdsdisp_hdmi_get_type(void);
JdsdispHdmi*			jdsdisp_hdmi_new(void);


#endif/*__JDSDISP_HDMI_H__*/
