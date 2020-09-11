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


#ifndef __JDSDISP_DBG_H__
#define __JDSDISP_DBG_H__


#include <klib.h>


#define JDSDISP_TYPE_DBG			(jdsdisp_dbg_get_type())
#define JDSDISP_DBG(obj)				(K_TYPE_CHECK_INSTANCE_CAST((obj), JdsdispDbg))
#define JDSDISP_IS_DBG(obj)			(K_TYPE_CHECK_INSTANCE_TYPE((obj), JDSDISP_TYPE_DBG))


typedef union 				_IoJdsddbgRegDbgsl IoJdsddbgRegDbgsl;
typedef struct 				_IoJdsddbgReg IoJdsddbgReg;
typedef struct 				_JdsdispDbg JdsdispDbg;
typedef struct 				_JdsdispDbgPrivate	JdsdispDbgPrivate;

union _IoJdsddbgRegDbgsl{
    kulong       word;
    struct {
        kulong   vdmsl   :1;
        kulong           :3;
        kulong   hdmsl   :1;
        kulong           :3;
        kulong   hdemsl  :1;
        kulong           :23;
    }bit;
};

/* Define i/o mapping */
struct _IoJdsddbgReg{
    /* JDSIMG */
	/* 2890_(B000 - B003h) */
	IoJdsddbgRegDbgsl dbgsl;
	/* 2890_(B004 - BFFFh) */
    kuchar dmyB004Bfff[0xC000-0xB004];
};

struct  _JdsdispDbg
{
	KObject parent;
};


KConstType				jdsdisp_dbg_get_type(void);
JdsdispDbg*			jdsdisp_dbg_new(void);


#endif/*__JDSDISP_DBG_H__*/
