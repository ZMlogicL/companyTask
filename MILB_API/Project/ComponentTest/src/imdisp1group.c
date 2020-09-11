/*
 *imdisp1group.c
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-08
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#include <stdlib.h>
#include <string.h>
#include "ctimdisp.h"//already define CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
#include "ctimdisp1.h"
#include "ctimdisp1a.h"
#include "ctimdisp1b.h"
#include "ctimdisp1c.h"
#include "ctimdisp1d.h"
#include "ctimdisp1e.h"

#include "imdisp1group.h"

K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(ImDisp1Group, im_disp1_group, K_TYPE_OBJECT)
#define IM_DISP1_GROUP_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), ImDisp1GroupPrivate, IM_TYPE_DISP1_GROUP))

struct _ImDisp1GroupPrivate
{
	kpointer qwertyu;
	ImDisp1Parent *pcTestInstance;
	KObject *wrapObject;
	kuchar *pImDispPclkCounter;
};

/*
 * DECLS
 * */
static void initAllCtImDisp1(ImDisp1Group *self);

/*
 * IMPL
 * */
static void im_disp1_group_constructor(ImDisp1Group *self)
{
	ImDisp1GroupPrivate *priv = IM_DISP1_GROUP_GET_PRIVATE(self);
	self->privImDisp1Group = priv;
	priv->pcTestInstance = NULL;
}

static void im_disp1_group_destructor(ImDisp1Group *self)
{
}

static void initAllCtImDisp1(ImDisp1Group *self)
{
	ImDisp1GroupPrivate *priv = self->privImDisp1Group;
	ImDisp1Parent *ctImDisp1 = (ImDisp1Parent *)ct_im_disp1_new();
	ImDisp1Parent *ctImDisp1a = (ImDisp1Parent *)ct_im_disp1a_new();
	ImDisp1Parent *ctImDisp1b = (ImDisp1Parent *)ct_im_disp1b_new();
	ImDisp1Parent *ctImDisp1c = (ImDisp1Parent *)ct_im_disp1c_new();
	ImDisp1Parent *ctImDisp1d = (ImDisp1Parent *)ct_im_disp1d_new();
	ImDisp1Parent *ctImDisp1e= (ImDisp1Parent *)ct_im_disp1e_new();

	im_disp1_parent_add_next(ctImDisp1, ctImDisp1a);
	im_disp1_parent_add_next(ctImDisp1a, ctImDisp1b);
	im_disp1_parent_add_next(ctImDisp1b, ctImDisp1c);
	im_disp1_parent_add_next(ctImDisp1c, ctImDisp1d);
	im_disp1_parent_add_next(ctImDisp1d, ctImDisp1e);

	im_disp1_parent_set_group(ctImDisp1, (KObject *)self);
	im_disp1_parent_set_group(ctImDisp1a, (KObject *)self);
	im_disp1_parent_set_group(ctImDisp1b, (KObject *)self);
	im_disp1_parent_set_group(ctImDisp1c, (KObject *)self);
	im_disp1_parent_set_group(ctImDisp1d, (KObject *)self);

	k_object_unref(ctImDisp1a);
	k_object_unref(ctImDisp1b);
	k_object_unref(ctImDisp1c);
	k_object_unref(ctImDisp1d);
	k_object_unref(ctImDisp1e);

	priv->pcTestInstance = ctImDisp1;
}

/*
 * PUBLIC
 * */

ImDisp1Parent *	im_disp1_group_get_pctest_instance(ImDisp1Group *self)
{
	if(self && IM_IS_DISP1_GROUP(self))
	{
		ImDisp1GroupPrivate *priv = self->privImDisp1Group;
		return priv->pcTestInstance;
	}
	return NULL;
}

kuchar *im_disp1_group_get_pclk_counter(ImDisp1Group *self)
{
	if (IM_IS_DISP1_GROUP(self))
	{
		ImDisp1GroupPrivate *priv = self->privImDisp1Group;
		return priv->pImDispPclkCounter;
	}
	return NULL;
}

void im_disp1_group_ct_im_disp3_pclk_counter_on(ImDisp1Group *self)
{
#ifdef CO_ACT_PCLOCK
	ImDisp1GroupPrivate *priv = self->privImDisp1Group;
	Dd_Top_Start_Clock(&priv->pImDispPclkCounter,
			&Dd_Top_Get_CLKSTOP3(), D_IM_DISP_CLKSTOP3_DISPAP_ON);
#endif	// CO_ACT_PCLOCK
}

void im_disp1_group_ct_im_disp3_pclk_counter_off(ImDisp1Group *self)
{
#ifdef CO_ACT_PCLOCK
	ImDisp1GroupPrivate *priv = self->privImDisp1Group;
	Dd_Top_Stop_Clock(&priv->pImDispPclkCounter,
			&Dd_Top_Get_CLKSTOP3(), D_IM_DISP_CLKSTOP3_DISPAP_OFF);
#endif	// CO_ACT_PCLOCK
}

ImDisp1Group *im_disp1_group_new(kuchar *pclkCounter, kuchar *hclkCounter)
{
	ImDisp1Group *self = (ImDisp1Group *)
			k_object_new_with_private(IM_TYPE_DISP1_GROUP,sizeof(ImDisp1GroupPrivate));
	ImDisp1GroupPrivate *priv = self->privImDisp1Group;
	priv->pImDispPclkCounter = pclkCounter;

	initAllCtImDisp1(self);
	return self;
}
