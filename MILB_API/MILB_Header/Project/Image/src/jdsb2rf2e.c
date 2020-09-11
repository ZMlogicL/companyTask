/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-05
*@author            :陈倩
*@brief             :jdsb2rf2e
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


//#include "jdsb2r.h"
#include "jdsb2rf2e.h"


K_TYPE_DEFINE_WITH_PRIVATE(Jdsb2rF2e, jdsb2r_f2e);
#define JDSB2R_F2E_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), Jdsb2rF2ePrivate, JDSB2R_TYPE_F2E))


struct  _Jdsb2rF2ePrivate
{

};


volatile struct io_b2r		IO_B2R_P1		__attribute__((section(".B2R_P1")));
volatile struct io_b2r		IO_B2R_P2		__attribute__((section(".B2R_P2")));
volatile struct io_b2r		IO_B2R_P3		__attribute__((section(".B2R_P3")));
volatile struct io_b2r_sram	IO_B2R_TBL_P1	__attribute__((section(".B2R_TBL_P1")));
volatile struct io_b2r_sram	IO_B2R_TBL_P2	__attribute__((section(".B2R_TBL_P2")));
volatile struct io_b2r_sram	IO_B2R_TBL_P3	__attribute__((section(".B2R_TBL_P3")));
/**
 IMPL
*/
static void jdsb2r_f2e_constructor(Jdsb2rF2e *self)
{
//	Jdsb2rF2ePrivate *priv = JDSB2R_F2E_GET_PRIVATE(self);
}

static void jdsb2r_f2e_destructor(Jdsb2rF2e *self)
{
//	Jdsb2rF2ePrivate *priv = JDSB2R_F2E_GET_PRIVATE(self);
}
/**
 PUBLIC
*/
Jdsb2rF2e* jdsb2r_f2e_new(void)
{
	Jdsb2rF2e* self = k_object_new_with_private(JDSB2R_TYPE_F2E, sizeof(Jdsb2rF2ePrivate));
	return self;
}

