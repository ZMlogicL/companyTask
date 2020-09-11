/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-04
*@author            :吴雨莎
*@brief             :ctimiipflt
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


#ifndef __CT_IM_IIP_FLT_H__
#define __CT_IM_IIP_FLT_H__


#include <klib.h>

#include "ddim_typedef.h"


#define CT_TYPE_IM_IIP_FLT		(ct_im_iip_flt_get_type())
#define CT_IM_IIP_FLT(obj)			K_TYPE_CHECK_INSTANCE_CAST(obj, CtImIipFlt)
#define CT_IS_IM_IIP_FLT(obj)    	K_TYPE_CHECK_INSTANCE_TYPE(obj, CT_TYPE_IM_IIP_FLT)


/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */


typedef struct _CtImIipFlt		 CtImIipFlt;
typedef struct _CtImIipFltPrivate		 CtImIipFltPrivate;

struct _CtImIipFlt
{
	KObject parent;
};


KConstType ct_im_iip_flt_get_type(void);
CtImIipFlt *ct_im_iip_flt_new(void);

/*----------------------------------------------------------------------*/
/* Function Prototype Definition										*/
/*----------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus

#ifndef CO_CT_IM_IIP_DISABLE
// FLT Unit
kint32 	ct_im_iip_9_1_1( CtImIipFlt *self );
kint32 	ct_im_iip_9_1_2( CtImIipFlt *self );
kint32 	ct_im_iip_run_9_1( CtImIipFlt *self, const kuint32 ctNo3rd );
kint32 	ct_im_iip_9_2_1( CtImIipFlt *self );
kint32 	ct_im_iip_run_9_2( CtImIipFlt *self, const kuint32 ctNo3rd );
kint32 	ct_im_iip_9_3_1( CtImIipFlt *self );
kint32 	ct_im_iip_run_9_3( CtImIipFlt *self, const kuint32 ctNo3rd );
#endif //CO_CT_IM_IIP_DISABLE

#ifdef __cplusplus
}
#endif	// __cplusplus

#endif/*__CT_IM_IIP_FLT_H__*/
