/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-03
*@author            :吴雨莎
*@brief             :ctimsdramc
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


#ifndef __CT_IM_SDRAMC_H__
#define __CT_IM_SDRAMC_H__


#include <klib.h>

#include "driver_common.h"


#define CT_TYPE_IM_SDRAMC			(ct_im_sdramc_get_type())
#define CT_IM_SDRAMC(obj)			K_TYPE_CHECK_INSTANCE_CAST(obj, CtImSdramc)
#define CT_IS_IM_SDRAMC(obj)    	K_TYPE_CHECK_INSTANCE_TYPE(obj, CT_TYPE_IM_SDRAMC)

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */
typedef struct _CtImSdramc		 CtImSdramc;
typedef struct _CtImSdramcPrivate		 CtImSdramcPrivate;

struct _CtImSdramc
{
	KObject parent;
};


KConstType 	ct_im_sdramc_get_type(void);
CtImSdramc *ct_im_sdramc_new(void);

void ct_im_sdramc_1_01( CtImSdramc *self, UCHAR ch );
void ct_im_sdramc_1_02( CtImSdramc *self, UCHAR ch );
void ct_im_sdramc_1_03( CtImSdramc *self, UCHAR ch );
void ct_im_sdramc_1_04( CtImSdramc *self, UCHAR ch );
void ct_im_sdramc_1_05( CtImSdramc *self, UCHAR ch );
void ct_im_sdramc_1_06( CtImSdramc *self, UCHAR ch );
void ct_im_sdramc_1_07( CtImSdramc *self, UCHAR ch );
void ct_im_sdramc_1_08( CtImSdramc *self, UCHAR ch );
void ct_im_sdramc_1_09( CtImSdramc *self, UCHAR ch );
void ct_im_sdramc_1_10( CtImSdramc *self, UCHAR ch );
void ct_im_sdramc_1_11( CtImSdramc *self, UCHAR ch );
void ct_im_sdramc_1_12( CtImSdramc *self, UCHAR ch );
void ct_im_sdramc_2_01( CtImSdramc *self );
void ct_im_sdramc_2_02( CtImSdramc *self );
void ct_im_sdramc_2_03( CtImSdramc *self );
void ct_im_sdramc_2_04( CtImSdramc *self );
void ct_im_sdramc_2_05( CtImSdramc *self );
void ct_im_sdramc_2_06( CtImSdramc *self );
void ct_im_sdramc_2_07( CtImSdramc *self );
void ct_im_sdramc_2_08( CtImSdramc *self );
void ct_im_sdramc_2_09( CtImSdramc *self );
void ct_im_sdramc_2_10( CtImSdramc *self );
void ct_im_sdramc_2_11( CtImSdramc *self );
void ct_im_sdramc_2_12( CtImSdramc *self );
void ct_im_sdramc_2_13( CtImSdramc *self );
void ct_im_sdramc_2_14( CtImSdramc *self );
void ct_im_sdramc_2_15( CtImSdramc *self );
void ct_im_sdramc_2_16( CtImSdramc *self );
void ct_im_sdramc_2_17( CtImSdramc *self );
void ct_im_sdramc_2_18( CtImSdramc *self );
void ct_im_sdramc_2_19( CtImSdramc *self );
void ct_im_sdramc_main(CtImSdramc *self, kint argc, kchar** argv);


#endif/*__CT_IM_SDRAMC_H__*/
