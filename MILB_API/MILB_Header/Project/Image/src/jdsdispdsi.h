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


#ifndef __JDSDISP_DSI_H__
#define __JDSDISP_DSI_H__


#include <klib.h>


#define JDSDISP_TYPE_DSI				(jdsdisp_dsi_get_type())
#define JDSDISP_DSI(obj)				(K_TYPE_CHECK_INSTANCE_CAST((obj), JdsdispDsi))
#define JDSDISP_IS_DSI(obj)			(K_TYPE_CHECK_INSTANCE_TYPE((obj), JDSDISP_TYPE_DSI))


typedef union 				_IoJdsdispDsiMdsic0 IoJdsdispDsiMdsic0;
typedef union 				_IoJdsdispDsiMdsic1 IoJdsdispDsiMdsic1;
typedef union 				_IoJdsdispDsiMdssr IoJdsdispDsiMdssr;
typedef struct 				_IoJdsdispDsi IoJdsdispDsi;
typedef struct 				_JdsdispDsi JdsdispDsi;
typedef struct 				_JdsdispDsiPrivate	JdsdispDsiPrivate;

union _IoJdsdispDsiMdsic0{
    kulong       word;
    struct {
        kulong   mdssd   :1;
        kulong           :7;
        kulong   mdscm   :1;
        kulong           :23;
    }bit;
};

/*  structure of MDSIC1 (2890_D004h)    */
union _IoJdsdispDsiMdsic1{
    kulong       word;
    struct {
        kulong   mdsudc  :2;
        kulong           :30;
    }bit;
};

/*  structure of MDSSR  (2890_D100h)    */
union _IoJdsdispDsiMdssr{
    kulong       word;
    struct {
        kulong   sr  :1;
        kulong       :31;
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
    kuchar dmyD008D0ff[0xD100-0xD008];
    /* 2890_(D100 - D103h) */
    IoJdsdispDsiMdssr     mdssr;
    /* 2890_(D104 - DFFFh) */
    kuchar dmyD104Dfff[0xE000-0xD104];
};

struct  _JdsdispDsi
{
	KObject parent;
};


KConstType			jdsdisp_dsi_get_type(void);
JdsdispDsi*			jdsdisp_dsi_new(void);


#endif/*__JDSDISP_DSI_H__*/
