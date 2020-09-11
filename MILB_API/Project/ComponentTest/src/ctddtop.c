/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
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
#include <stdlib.h>
#include <string.h>
#include "../../DeviceDriver/LSITop/src/ddtop.h"
#include "../../DeviceDriver/LSITop/src/ddtopfour.h"
#include "../../DeviceDriver/LSITop/src/ddtopone.h"
#include "../../DeviceDriver/LSITop/src/ddtopthree.h"
#include "../../DeviceDriver/LSITop/src/ddtoptwo.h"

#include "ctgetctrl.h"
#include "ctsetctrl.h"
#include "ctclockclksel.h"
#include "ctclockpllcnt.h"
#include "ctclockclkstop.h"
#include "ctpll.h"
#include "ctreset.h"
#include "ctgpio.h"
#include "ctclockfrequency.h"
#include "ctddtop.h"
#include "ctddtopfrist.h"
#include "ctddtopsecond.h"
#include "ctddtopthird.h"
#include "ctddtopend.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdTop, ct_dd_top);
#define CT_DD_TOP_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdTopPrivate,CT_TYPE_DD_TOP))

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Local Method Definition												*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/

struct _CtDdTopPrivate
{
	CtDdTopFrist* ctDdTopFrist;
    CtDdTopSecond* ctDdTopSecond;
    CtDdTopThird* ctDdTopThird;
    CtDdTopEnd* ctDdTopEnd;
};
/****************
* DECLS
*/
static void 			ct_dd_top_constructor(CtDdTop *self);
static void 			ct_dd_top_destructor(CtDdTop *self);
/****************
* IMPL
*/
static void ct_dd_top_constructor(CtDdTop *self) 
{
	CtDdTopPrivate *priv = CT_DD_TOP_GET_PRIVATE(self);

    priv->ctDdTopFrist = ct_dd_top_frist_new();
    priv->ctDdTopSecond = ct_dd_top_second_new();
    priv->ctDdTopThird = ct_dd_top_third_new();
    priv->ctDdTopEnd = ct_dd_top_end_new();
}

static void ct_dd_top_destructor(CtDdTop *self) 
{
	CtDdTopPrivate *priv = CT_DD_TOP_GET_PRIVATE(self);
	
    k_object_unref(priv->ctDdTopFrist);
    k_object_unref(priv->ctDdTopSecond);
    k_object_unref(priv->ctDdTopThird);
    k_object_unref(priv->ctDdTopEnd);
}
/****************
* PUBLIC
*/
void ct_dd_top_pc_test_main(CtDdTop *self)
{
    CtDdTopPrivate *priv = CT_DD_TOP_GET_PRIVATE(self);
    
	ct_dd_top_frist_pc_test_main(priv->ctDdTopFrist);
	ct_dd_top_second_pc_test_main(priv->ctDdTopSecond);
	ct_dd_top_third_pc_test_main(priv->ctDdTopThird);
	ct_dd_top_end_set_seq_no(priv->ctDdTopEnd,ct_dd_top_third_get_seq_no(priv->ctDdTopThird));
	ct_dd_top_end_pc_test_main(priv->ctDdTopEnd);
}

CtDdTop* ct_dd_top_new(void) 
{
    CtDdTop *self = k_object_new_with_private(CT_TYPE_DD_TOP, sizeof(CtDdTopPrivate));
    return self;
}
