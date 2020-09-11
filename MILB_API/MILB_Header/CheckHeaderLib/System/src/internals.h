/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :于孟孟
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年06月开始开发
*/


#ifndef __INT_ERNALS_H__
#define __INT_ERNALS_H__


#include <klib.h>
#if 0
#include "jdspro.h"
#endif


#define INT_TYPE_ERNALS		(int_ernals_get_type())
#define INT_ERNALS(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, IntErnals))
#define INT_IS_ERNALS(obj)	(K_TYPE_CHECK_INSTANCE_TYPE(obj, INT_TYPE_ERNALS))

#define IntErnals_RS_printf printf


typedef struct 				_IntErnals IntErnals;
typedef struct 				_IntErnalsPrivate IntErnalsPrivate;


typedef enum _EProBlockType{
	IntErnals_E_PRO_BLOCK_TYPE_SEN	= 0,
	IntErnals_E_PRO_BLOCK_TYPE_SRO1,
	IntErnals_E_PRO_BLOCK_TYPE_SRO2,
	IntErnals_E_PRO_BLOCK_TYPE_SRO3,
	IntErnals_E_PRO_BLOCK_TYPE_B2B1,
	IntErnals_E_PRO_BLOCK_TYPE_B2B2,
	IntErnals_E_PRO_BLOCK_TYPE_B2B3,
	IntErnals_E_PRO_BLOCK_TYPE_STAT,
	IntErnals_E_PRO_BLOCK_TYPE_PAS,
	IntErnals_E_PRO_BLOCK_TYPE_TABLE,
} EProBlockType;


struct _IntErnals {
	KObject parent;
};


KConstType 		    int_ernals_get_type(void);
IntErnals*		        int_ernals_new(void);


#endif /* __INT_ERNALS_H__ */
