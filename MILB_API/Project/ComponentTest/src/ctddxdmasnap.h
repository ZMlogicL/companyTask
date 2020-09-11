/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :liudong
*@brief               :CtDdXdmasnap类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_XDMASNAP_H_
#define __CT_DD_XDMASNAP_H_

#include "ddim_typedef.h"
#include <klib.h>

#define CT_TYPE_DD_XDMASNAP					(ct_dd_xdmasnap_get_type())
#define CT_DD_XDMASNAP(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdXdmasnap)) 
#define CT_IS_DD_XDMASNAP(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_XDMASNAP)) 




typedef struct 			_CtDdXdmasnap CtDdXdmasnap;
typedef struct 			_CtDdXdmasnapPrivate CtDdXdmasnapPrivate;

struct _CtDdXdmasnap
{
	KObject parent;

};

KConstType 			ct_dd_xdmasnap_get_type(void);
CtDdXdmasnap* 		ct_dd_xdmasnap_new(void);

void 				ct_dd_xdmasnap_callback_cb(void);
/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Function Prototype Definition										*/
/*----------------------------------------------------------------------*/
void 				ct_dd_xdmasnap_main(int argc, char** argv);
kuchar 				ct_dd_xdmasnap_get_num(CtDdXdmasnap *self);

#endif /* __CT_DD_XDMASNAP_H_ */
