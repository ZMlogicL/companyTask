/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-05
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
#include "ctddtopmain.h"
#include "ctddtopwrap.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdTopWrap, ct_dd_top_wrap);
#define CT_DD_TOP_WRAP_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdTopWrapPrivate,CT_TYPE_DD_TOP_WRAP))

struct _CtDdTopWrapPrivate
{
	CtDdTopMain* ctDdTopMain;
};
/****************
* DECLS
*/
static void 		ct_dd_top_wrap_constructor(CtDdTopWrap *self);
static void 		ct_dd_top_wrap_destructor(CtDdTopWrap *self);
/****************
* IMPL
*/
static void ct_dd_top_wrap_constructor(CtDdTopWrap *self) 
{
	CtDdTopWrapPrivate *priv = CT_DD_TOP_WRAP_GET_PRIVATE(self);
    priv->ctDdTopMain = ct_dd_top_main_new();
}

static void ct_dd_top_wrap_destructor(CtDdTopWrap *self) 
{
	CtDdTopWrapPrivate *priv = CT_DD_TOP_WRAP_GET_PRIVATE(self);
    k_object_unref(priv->ctDdTopMain);
}
/****************
* PUBLIC
*/
void ct_dd_top_wrap_pctest(CtDdTopWrap *self,kchar *cmd)
{
	CtDdTopWrapPrivate *priv = CT_DD_TOP_WRAP_GET_PRIVATE(self);
	kint32 argc = 0;
	kchar *argv[32];
	kchar arg[32][32];
	kint32 pos = 0;
	kint32 len = 0;
	kint32 max = strlen(cmd);
	kint32 i;

	printf("CMD> %s\n", cmd);

	// Clear arg buffer
	for (i = 0; i < 32; i++)
	{
		argv[i] = arg[i];
		memset(argv[i], 0, 32);
	}

	// Set arg buffer
	for (i = 0; i < max; i++)
	{
		if (cmd[i] == ' ')
		{
			if (len)
			{
				memcpy(argv[argc], &cmd[pos], len);
				argc++;
				len = 0;
			}
			pos = i + 1;
		}else if ( i == max - 1)
		{
			memcpy(argv[argc], &cmd[pos], len + 1);
			argc++;
			len = 0;
			pos = i + 1;
		}
		else
		{
			len++;
		}
	}

	// Execute command
	ct_dd_top_main(priv->ctDdTopMain,argc, argv);
}

CtDdTopWrap* ct_dd_top_wrap_new(void) 
{
    CtDdTopWrap *self = k_object_new_with_private(CT_TYPE_DD_TOP_WRAP, sizeof(CtDdTopWrapPrivate));
    return self;
}
