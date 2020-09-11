/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : maoguangkun
*@brief : CtImShdrTools
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_SHDR_TOOLS_H__
#define __CT_IM_SHDR_TOOLS_H__


#include <klib.h>
#include <string.h>
#include <stdlib.h>

#include "ct_im_shdr.h"
#include "jdsshdr.h"
#include "im_shdr.h"

#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
#endif //CO_ACT_CLOCK | CO_ACT_HCLOCK | CO_ACT_PCLOCK

#include "ddim_user_custom.h"


#define CT_TYPE_IM_SHDR_TOOLS                  (ct_im_shdr_tools_get_type())
#define CT_IM_SHDR_TOOLS(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImShdrTools)) 
#define CT_IS_IM_SHDR_TOOLS(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_SHDR_TOOLS)) 

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
#define CtImShdrTools_PC_DEBUG


/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
// nothing special.

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
typedef struct {
	T_IM_SHDR_CTRL		ctrl;
	T_IM_SHDR_PRE		pre;
	T_IM_SHDR_FMD		fmd;
	T_IM_SHDR_PMSK		pmsk;
	T_IM_SHDR_SPNR		spnr;
	T_IM_SHDR_MSK		msk;
	T_IM_SHDR_BLD		bld;
	T_IM_SHDR_POST		post;
	T_IM_SHDR_RESIZE	resize;
	T_IM_SHDR_SMC		smc;
	T_IM_SHDR_AXI		axi;
} TImShdrParam;


typedef struct _CtImShdrTools CtImShdrTools;
typedef struct _CtImShdrToolsPrivate CtImShdrToolsPrivate;


struct _CtImShdrTools 
{
	KObject parent;
};


KConstType 			ct_im_shdr_tools_get_type(void);
CtImShdrTools* 		ct_im_shdr_tools_get(void);

#endif /* __CT_IM_SHDR_TOOLS_H__ */
