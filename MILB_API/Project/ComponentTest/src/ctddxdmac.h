/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :liudong
*@brief               :CtDdXdmac类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_XDMAC_H_
#define __CT_DD_XDMAC_H_

#include "ddim_typedef.h"
#include <klib.h>

#define CT_TYPE_DD_XDMAC					(ct_dd_xdmac_get_type())
#define CT_DD_XDMAC(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdXdmac)) 
#define CT_IS_DD_XDMAC(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_XDMAC)) 


typedef struct 			_CtDdXdmac CtDdXdmac;
typedef struct 			_CtDdXdmacPrivate CtDdXdmacPrivate;

struct _CtDdXdmac
{
	KObject parent;
	

};

KConstType 		ct_dd_xdmac_get_type(void);
CtDdXdmac* 		ct_dd_xdmac_new(void);

 void 			ct_dd_xdmac_callback_cb(void);
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
void 			ct_dd_xdmac_main(int argc, char** argv);
kuchar 			ct_dd_xdmac_get_num(CtDdXdmac *self);

#endif /* __CT_DD_XDMAC_H_ */
