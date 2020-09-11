/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-05
*@author            :陈倩
*@brief             :kpdm
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


#include "kpdm.h"


K_TYPE_DEFINE_WITH_PRIVATE(KPdm, k_pdm);
#define K_PDM_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KPdmPrivate, K_TYPE_PDM))


struct  _KPdmPrivate
{

};


volatile IoPdm		ioPdm[2]	__attribute__((section(".PDM")));
/**
 IMPL
*/
static void k_pdm_constructor(KPdm *self)
{
//	KPdmPrivate *priv = K_PDM_GET_PRIVATE(self);
}

static void k_pdm_destructor(KPdm *self)
{
//	KPdmPrivate *priv = K_PDM_GET_PRIVATE(self);
}
/**
 PUBLIC
*/
KPdm* k_pdm_new(void)
{
	KPdm* self = k_object_new_with_private(K_TYPE_PDM, sizeof(KPdmPrivate));
	return self;
}

