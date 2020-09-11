/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-04
*@author            :吴雨莎
*@brief             :ctimiipfrect
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

#ifndef __CT_IM_IIP_FRECT_H__
#define __CT_IM_IIP_FRECT_H__


#include <klib.h>

#include "ddim_typedef.h"


#define CT_TYPE_IM_IIP_FRECT			(ct_im_iip_frect_get_type())
#define CT_IM_IIP_FRECT(obj)				K_TYPE_CHECK_INSTANCE_CAST(obj, CtImIipFrect)
#define CT_IS_IM_IIP_FRECT(obj)    	K_TYPE_CHECK_INSTANCE_TYPE(obj, CT_TYPE_IM_IIP_FRECT)


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


typedef struct _CtImIipFrect		 CtImIipFrect;
typedef struct _CtImIipFrectPrivate		 CtImIipFrectPrivate;

struct _CtImIipFrect
{
	KObject parent;
};


KConstType 	ct_im_iip_frect_get_type(void);
CtImIipFrect *ct_im_iip_frect_new(void);

/*----------------------------------------------------------------------*/
/* Function Prototype Definition										*/
/*----------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus

// FRECT Unit
#ifndef CO_CT_IM_IIP_DISABLE
kint32 ct_im_iip_frect_4_1_1( CtImIipFrect *self );
kint32 ct_im_iip_frect_run_4_1( CtImIipFrect *self, const kuint32 ctNo3rd );
#endif //CO_CT_IM_IIP_DISABLE

#ifdef __cplusplus
}
#endif	// __cplusplus

#endif/*__CT_IM_IIP_FRECT_H__*/
