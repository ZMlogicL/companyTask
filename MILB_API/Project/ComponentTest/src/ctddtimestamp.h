/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :李清
*@brief               :CtDdTimestamp类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年06月开始开发
*/
/**
 * @file		ct_dd_timestamp.h
 * @brief		dd_timestamp Component Test
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */
#ifndef __CT_DD_TIMESTAMP_H__
#define __CT_DD_TIMESTAMP_H__

#include <klib.h>
#include "ddimtypedef.h"

#define CT_TYPE_DD_TIMESTAMP                  (ct_dd_timestamp_get_type())
#define CT_DD_TIMESTAMP(obj)                  (K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdTimestamp)) 
#define CT_IS_DD_TIMESTAMP(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_TIMESTAMP)) 

typedef struct                                _CtDdTimestamp CtDdTimestamp;
typedef struct                                _CtDdTimestampPrivate CtDdTimestampPrivate;

struct _CtDdTimestamp {
    KObject 		parent;
    kint32 			dat;
	DdTimestamp 	timestampCtrl;
	DdTimestamp 	timestampCtrlGet;
	kulonglong 		timestampCounter;
	kulonglong 		timestampCounterGet;
	kulong 			usec;
	kulong 			frequency;
};

KConstType              ct_dd_timestamp_get_type(void);

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
void	                ct_dd_timestamp_main(CtDdTimestamp *self, kint argc, KType* argv);

CtDdTimestamp*          ct_dd_timestamp_new(void);

#endif /* __CT_DD_TIMESTAMP_H__ */
