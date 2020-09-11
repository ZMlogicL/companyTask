/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :liudong
*@brief               :CtDdXdmasnap1类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_XDMASNAP1_H_
#define __CT_DD_XDMASNAP1_H_

#include <klib.h>

#define CT_TYPE_DD_XDMASNAP1					(ct_dd_xdmasnap1_get_type())
#define CT_DD_XDMASNAP1(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdXdmasnap1)) 
#define CT_IS_DD_XDMASNAP1(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_XDMASNAP1)) 


/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
/************************************/
/* Size definition                  */
/************************************/
#define CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_SIZE			(0x96000)

/************************************/
/* Address definition               */
/************************************/
#define CtDdXdmasnap1_D_XDMASNAP_SDRAM_BASE				(0x7B000000)

#define CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_SRC		(CtDdXdmasnap1_D_XDMASNAP_SDRAM_BASE)
#define CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_DST		(CtDdXdmasnap1_D_XDMASNAP_SDRAM_BASE + CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_SIZE)

typedef struct 			_CtDdXdmasnap1 CtDdXdmasnap1;
typedef struct 			_CtDdXdmasnap1Private CtDdXdmasnap1Private;

struct _CtDdXdmasnap1
{
	KObject parent;

};

KConstType 				ct_dd_xdmasnap1_get_type(void);
CtDdXdmasnap1* 			ct_dd_xdmasnap1_new(void);

// kint32 ct_xdmasnap_process(kuchar num);
kint32 					ct_dd_xdmasnap1_process(CtDdXdmasnap1 *self);
void 					ct_dd_xdmasnap1_set_ctddxdmasnap(CtDdXdmasnap1 *self,CtDdXdmasnap *ctDdXdmasnap);

#endif /* __CT_DD_XDMASNAP1_H_ */
