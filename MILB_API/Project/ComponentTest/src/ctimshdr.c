/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : maoguangkun
*@brief : CtImShdr
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include <string.h>
#include <stdlib.h>

#include "ct_im_shdr.h"
#include "jdsshdr.h"
#include "im_shdr.h"

#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
#endif //CO_ACT_CLOCK | CO_ACT_HCLOCK | CO_ACT_PCLOCK

#include "ddim_user_custom.h"
#include "ctimshdr.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImShdr, ct_im_shdr)
#define CT_IM_SHDR_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImShdrPrivate, CT_TYPE_IM_SHDR))


struct _CtImShdrPrivate
{

};


/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
ULONG gctImShdrInAddr[ 5 ] = {
	0x48000000,
	0x49000000,
	0x4A000000,
	0x4B000000,
	0x4C000000,
};

ULONG gctImShdrOutAddr[ 6 ]	= {
	0x4D000000,
	0x4E000000,
	0x4F000000,
	0x50000000,
	0x51000000,
	0x52000000,
};


/********
 * IMPL
 */
static void ct_im_shdr_constructor(CtImShdr *self)
{
//	CtImShdrPrivate *priv = CT_IM_SHDR_GET_PRIVATE(self);
}

static void ct_im_shdr_destructor(CtImShdr *self)
{
//	CtImShdrPrivate *priv = CT_IM_SHDR_GET_PRIVATE(self);
}


/**********
 * PUBLIC
 */
CtImShdr* ct_im_shdr_get(void)
{
	static CtImShdr* self = NULL;

	if (!self) {
		self = k_object_new_with_private(CT_TYPE_IM_SHDR, sizeof(CtImShdrPrivate));
	}

	return self;
}
