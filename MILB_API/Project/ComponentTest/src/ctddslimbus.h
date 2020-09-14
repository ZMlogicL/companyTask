/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :李清
*@brief               :CtDdSlimbus类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年06月开始开发
*/

#ifndef __CT_DD_SLIMBUS_H__
#define __CT_DD_SLIMBUS_H__

#include <klib.h>
#include "ddimtypedef.h"

#define CT_TYPE_DD_SLIMBUS                  (ct_dd_slimbus_get_type())
#define CT_DD_SLIMBUS(obj)                  (K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdSlimbus)) 
#define CT_IS_DD_SLIMBUS(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_SLIMBUS)) 

typedef struct                              _CtDdSlimbus CtDdSlimbus;
typedef struct                              _CtDdSlimbusPrivate CtDdSlimbusPrivate;
typedef struct 								_TMcFifoMsg TMcFifoMsg;

struct _CtDdSlimbus {
    KObject 		parent;
    EDdSlimbusCh	ch;
	TDdSlimbusCtrl	slimbusCtrl;
	kushort			offset;
	kuint32			data;
	kuint32			index;
	kuchar			dmaCh;
	kuint32			count;
};

KConstType          ct_dd_slimbus_get_type(void);

VOID                ct_dd_slimbus_main(CtDdSlimbus *self, kint argc, KType* argv);

CtDdSlimbus*        ct_dd_slimbus_new(void);

#endif /* __CT_DD_SLIMBUS_H__ */
