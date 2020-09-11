/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :liudong
*@brief               :CtDdXdmac1类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_XDMAC1_H_
#define __CT_DD_XDMAC1_H_

#include <klib.h>

#define CT_TYPE_DD_XDMAC1					(ct_dd_xdmac1_get_type())
#define CT_DD_XDMAC1(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdXdmac1)) 
#define CT_IS_DD_XDMAC1(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_XDMAC1)) 


/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
/************************************/
/* Size definition                  */
/************************************/
#define CtDdXdmac1_D_XDMAC_AUTO_TEST_SIZE			(0x96000)

/************************************/
/* Address definition               */
/************************************/
#define CtDdXdmac1_D_XDMAC_SDRAM_BASE				(0x7B000000)

#define CtDdXdmac1_D_XDMAC_AUTO_TEST_ADR_SRC		(CtDdXdmac1_D_XDMAC_SDRAM_BASE)
#define CtDdXdmac1_D_XDMAC_AUTO_TEST_ADR_DST		(CtDdXdmac1_D_XDMAC_SDRAM_BASE + CtDdXdmac1_D_XDMAC_AUTO_TEST_SIZE)

#define CtDdXdmac1_D_XDMAC_AUTO_TEST_INTMEM		(0x18000000)

typedef struct 			_CtDdXdmac1 CtDdXdmac1;
typedef struct 			_CtDdXdmac1Private CtDdXdmac1Private;

struct _CtDdXdmac1
{
	KObject parent;

};

KConstType 			ct_dd_xdmac1_get_type(void);
CtDdXdmac1* 		ct_dd_xdmac1_new(void);

// kint32 ct_xdmac_process(kuchar num);
kint32 				ct_dd_xdmac1_process(CtDdXdmac1 *self);
void 				ct_dd_xdmac1_set_ctddxdmac(CtDdXdmac1 *self,CtDdXdmac *ctDdXdmac);

#endif /* __CT_DD_XDMAC1_H_ */
