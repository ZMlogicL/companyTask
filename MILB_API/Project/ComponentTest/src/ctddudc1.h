/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :李清
*@brief               :CtDdUdc1类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年06月开始开发
*/
/**
 * @file		ct_dd_udc.h
 * @brief		This is ct header for dd_udc.c.
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */
#ifndef __CT_DD_UDC1_H__
#define __CT_DD_UDC1_H__

#include <klib.h>
#include "driver_common.h"

#define CT_TYPE_DD_UDC1                 (ct_dd_udc1_get_type())
#define CT_DD_UDC1(obj)                 (K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdUdc1)) 
#define CT_IS_DD_UDC1(obj)              (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_UDC1)) 

typedef struct                          _CtDdUdc1 CtDdUdc1;
typedef struct                          _CtDdUdc1Private CtDdUdc1Private;

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
#define CtDdUdc1_D_CT_DD_UDC_TMR_OBS_CH	(2)	// Timer32 ch for UDCR observer
#define CtDdUdc1_D_CT_DD_UDC_TMR_AIN_CH	(3)	// Timer32 ch for virtual AIN
#define CtDdUdc1_D_CT_DD_UDC_TMR_BIN_CH	(4)	// Timer32 ch for virtual BIN

struct _CtDdUdc1 {
    KObject 			parent;
	kint32				ercd;
	T_DD_UDC_CTRL_CMN	udcCrl;
	DD_UDC_CALLBACK		callback;
	kuchar				tmrAinCh;
	kuchar				tmrBinCh;
	kuchar				prescaler;
	kuchar				edge;
	kulong				usec;
	kuchar				periClock;
	// Control data of UDCR observer
    kuchar				gctDdUdcObsCh;		// Target UDC channel number
    //Save system time for UDC utility function
    kulonglong			gctDdUdcTimUtilSta;
};

KConstType 		ct_dd_udc1_get_type(void);

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
void			ct_dd_udc1_main(CtDdUdc1 *self, kint argc, KType* argv);
kuchar 			ct_dd_udc1_get_obs_ch(CtDdUdc1 *self);
kulonglong 		ct_dd_udc1_get_tim_util_sta(CtDdUdc1 *self);

CtDdUdc1* 		ct_dd_udc1_new(void);

#endif /* __CT_DD_UDC1_H__ */
