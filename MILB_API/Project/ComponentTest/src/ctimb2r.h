/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :liduong
*@brief               :CtImB2r类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_B2R_H_
#define __CT_IM_B2R_H_
#include "driver_common.h"
#include "ddim_typedef.h"

#include <klib.h>

#define CT_TYPE_IM_B2R					(ct_im_b2r_get_type())
#define CT_IM_B2R(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImB2r)) 
#define CT_IS_IM_B2R(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_B2R)) 

typedef struct 			_CtImB2r CtImB2r;
typedef struct 			_CtImB2rPrivate CtImB2rPrivate;


struct _CtImB2r
{
	KObject parent;
	UCHAR pipeNo;

};

/*----------------------------------------------------------------------*/
/* Local Method															*/
/*----------------------------------------------------------------------*/
#ifdef D_IM_B2R_DEBUG_ON_PC
extern volatile UCHAR gIM_B2R_macro_fake_finish[2];
#endif

/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/
#ifdef IM_B2R_STATUS_PRINT
extern void Im_B2R_Print_Status( void );
extern void Im_B2R_Print_ClockStatus( void );
extern void Im_B2R_Print_AccEnStatus( void );
#endif

KConstType 				ct_im_b2r_get_type(void);
CtImB2r* 				ct_im_b2r_new(void);

// extern void CT_Im_B2R_Run( const kuint32 ctIdx1st, const kuint32 ctIdx2nd, const kuint32 ctIdx3rd );
void 					ct_im_b2r_run(  CtImB2r *self );
void 					ct_im_b2r_main( kint32 argc, CHAR** argv );
void 					ct_im_b2r_set_value(CtImB2r *self,kuint32 ctIdx1st,kuint32 ctIdx2nd,kuint32 ctIdx3rd);

#endif /* __CT_IM_B2R_H_ */
