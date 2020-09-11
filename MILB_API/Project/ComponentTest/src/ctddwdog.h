/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :李清
*@brief               :CtDdWdog类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年06月开始开发
*/
/**
 * @file		ct_dd_wdog.h
 * @brief		dd_wdog Component Test
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */
#ifndef __CT_DD_WDOG_H__
#define __CT_DD_WDOG_H__

#include <klib.h>
#include "ddim_typedef.h"
#include "ddwdog.h"
#include "ddimusercustom.h"

#define CT_TYPE_DD_WDOG                  (ct_dd_wdog_get_type())
#define CT_DD_WDOG(obj)                  (K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdWdog)) 
#define CT_IS_DD_WDOG(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_WDOG)) 

typedef struct                           _CtDdWdog CtDdWdog;
typedef struct                           _CtDdWdogPrivate CtDdWdogPrivate;

struct _CtDdWdog {
    KObject 					parent;
    kint32  					ercd;
	kuchar						rawWdogInt;
	kuchar						wdogInt;
	kuchar						wdogLock;
	kuchar						testMode;
	kulong						wdogLoad;
	kulong						wdogCounter;
	kulong						wdogWdmode;
	kulong						msec;
	kulong						pcell;
	DdWdogPeriIdentification	identification;
	DdWdogCtrl					wdogCtrl;
};

KConstType      ct_dd_wdog_get_type(void);

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Function Prototype Definition										*/
/*----------------------------------------------------------------------*/
void	        ct_dd_wdog_main(CtDdWdog *self, kint argc, KType* argv);

CtDdWdog*       ct_dd_wdog_new(void);

#endif /* __CT_DD_WDOG_H__ */
