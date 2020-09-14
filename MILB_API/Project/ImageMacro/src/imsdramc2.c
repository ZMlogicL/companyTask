/*
 * imsdramc2.c
 *
 *  Created on: 2020年9月3日
 *      Author: sns
 */

#include "imsdramc2.h"

typedef struct _ImSdramc2Private ImSdramc2Private;
 struct _ImSdramc2Private
{
	int a;
};

K_TYPE_DEFINE_DERIVED(ImSdramc2, im_sdramc2, sizeof(ImSdramc2Private),K_TYPE_OBJECT)
#define IM_SDRAMC2_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImSdramc2Private, IM_TYPE_SDRAMC2))


static void im_sdramc2_constructor(ImSdramc2 *self)
{
	//ImSdramcPrivate2 *priv = IM_SDRAMC_GET_PRIVATE(self);
}

static void im_sdramc2_destructor(ImSdramc2 *self)
{
	//ImSdramc2Private *priv = IM_SDRAMC2_GET_PRIVATE(self);
}

ImSdramc2 *im_sdramc2_new(void)
{
	ImSdramc2* self = k_object_new(IM_TYPE_SDRAMC2);
	return self;
}


