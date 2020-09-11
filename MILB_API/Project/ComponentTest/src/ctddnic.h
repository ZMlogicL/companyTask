/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :李清
*@brief               :CtDdNic类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年06月开始开发
*/
/**
 * @file		ct_dd_nic.h
 * @brief		dd_nic Component Test
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */
#ifndef __CT_DD_NIC_H__
#define __CT_DD_NIC_H__

#include <klib.h>
#include "ddim_typedef.h"

#define CT_TYPE_DD_NIC                  (ct_dd_nic_get_type())
#define CT_DD_NIC(obj)                  (K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdNic)) 
#define CT_IS_DD_NIC(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_NIC)) 

typedef struct                          _CtDdNic CtDdNic;
typedef struct                          _CtDdNicPrivate CtDdNicPrivate;

struct _CtDdNic {
    KObject parent;
    kint32  param1;
	kulong  param2;
    kulong  param3;
};

KConstType      ct_dd_nic_get_type(void);

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
void	        ct_dd_nic_main(CtDdNic *self, kint argc, KType* argv);

CtDdNic*        ct_dd_nic_new(void);

#endif /* __CT_DD_NIC_H__ */
