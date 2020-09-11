/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-03
*@author            :吴雨莎
*@brief             :ctimxch
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


#ifndef __CT_IM_XCH_H__
#define __CT_IM_XCH_H__


#include <klib.h>

#include "driver_common.h"


#define CT_TYPE_IM_XCH			(ct_im_xch_get_type())
#define CT_IM_XCH(obj)			K_TYPE_CHECK_INSTANCE_CAST(obj, CtImXch)
#define CT_IS_IM_XCH(obj)    	K_TYPE_CHECK_INSTANCE_TYPE(obj, CT_TYPE_IM_XCH)

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
#define CtImXch_D_CT_XCH_SRC_TOP_ADDR				(0x60000000)	// Source address
#define CtImXch_D_CT_XCH_DST_TOP_ADDR				(0x70000000)	// Destination address

#define CtImXch_D_CT_XCH_SRC_TOP_ADDR2			(0x68000000)	// Source address 2
#define CtImXch_D_CT_XCH_DST_TOP_ADDR2			(0x78000000)	// Destination address 2


typedef struct _CtImXch		 CtImXch;
typedef struct _CtImXchPrivate		 CtImXchPrivate;

struct _CtImXch
{
	KObject parent;
};


KConstType 	ct_im_xch_get_type(void);
CtImXch *		ct_im_xch_get(void);

void 				ct_im_xch_callback_0_cb( void );
void 				ct_im_xch_callback_1_cb( void );

void 				ct_im_xch_main( CtImXch *self, kint32 argc, CHAR** argv );


#endif/*__CT_IM_XCH_H__*/
