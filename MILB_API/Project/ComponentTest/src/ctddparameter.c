/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-08
*@author              :董如利
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#include "ctddparameter.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdParameter, ct_dd_parameter);
#define CT_DD_PARAMETER_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdParameterPrivate,CT_TYPE_DD_PARAMETER))

struct _CtDdParameterPrivate
{
	int a;
};
/****************
* DECLS
*/
static void 			ct_dd_parameter_constructor(CtDdParameter *self);
static void 			ct_dd_parameter_destructor(CtDdParameter *self);
/****************
* IMPL
*/
static void ct_dd_parameter_constructor(CtDdParameter *self) 
{
//	CtDdParameterPrivate *priv = CT_DD_PARAMETER_GET_PRIVATE(self);
    self->argv = NULL;
}

static void ct_dd_parameter_destructor(CtDdParameter *self) 
{
	// CtDdParameterPrivate *priv = CT_DD_PARAMETER_GET_PRIVATE(self);
    if(self->argv != NULL)
    {
        k_free(self->argv);
        self->argv = NULL; 
    }
}
/****************
* PUBLIC
*/
void ct_dd_parameter_set_parameter(CtDdParameter* self,    kint argc,kchar** argv )
{
    self->argc = argc;
    self->argv = argv;
}

CtDdParameter* ct_dd_parameter_new(void) 
{
    CtDdParameter *self = k_object_new_with_private(CT_TYPE_DD_PARAMETER, sizeof(CtDdParameterPrivate));
    return self;
}
