/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-07
*@author            :陈倩
*@brief             :kjdsmxic
*@rely              :klib
*@function
*设计的主要功能:
*1、
*2、
*3、
*4、
*5、
*@version
*
*/


#include "kjdsmxic.h"


K_TYPE_DEFINE_WITH_PRIVATE(KJdsmxic, k_jdsmxic);
#define K_JDSMXIC_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KJdsmxicPrivate, K_TYPE_JDSMXIC))


struct  _KJdsmxicPrivate
{

};


volatile IoJdsmxic			ioMxic0		__attribute__((section(".MXIC0")));
volatile IoJdsmxic			ioMxic1		__attribute__((section(".MXIC1")));
volatile IoJdsmxic			ioMxic2		__attribute__((section(".MXIC2")));
volatile IoJdsmxic			ioMxic3		__attribute__((section(".MXIC3")));
volatile IoJdsmxic			ioMxic4		__attribute__((section(".MXIC4")));
volatile IoJdsmxic			ioMxic5		__attribute__((section(".MXIC5")));
volatile IoJdsmxic			ioMxic6		__attribute__((section(".MXIC6")));
volatile struct IoJdsmxicTbl		IoMxic1Tbl	__attribute__((section(".MXIC1_TBL")));
volatile struct IoJdsmxicTbl		IoMxic2Tbl	__attribute__((section(".MXIC2_TBL")));
volatile struct IoJdsmxicTbl		IoMxic3Tbl	__attribute__((section(".MXIC3_TBL")));
/**
 IMPL
*/
static void k_jdsmxic_constructor(KJdsmxic *self)
{
//	KJdsmxicPrivate *priv = K_JDSMXIC_GET_PRIVATE(self);
}

static void k_jdsmxic_destructor(KJdsmxic *self)
{
//	KJdsmxicPrivate *priv = K_JDSMXIC_GET_PRIVATE(self);
}
/**
 PUBLIC
*/
KJdsmxic* k_jdsmxic_new(void)
{
	KJdsmxic* self = k_object_new_with_private(K_TYPE_JDSMXIC, sizeof(KJdsmxicPrivate));
	return self;
}

