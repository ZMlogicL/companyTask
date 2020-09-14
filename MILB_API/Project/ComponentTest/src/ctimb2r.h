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
// #include "ddim_typedef.h"
#include "../../DeviceDriver/ARM/src/ddimtypedef.h"

#include <klib.h>

#define CT_TYPE_IM_B2R					(ct_im_b2r_get_type())
#define CT_IM_B2R(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImB2r)) 
#define CT_IS_IM_B2R(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_B2R)) 

#define CtImB2r_D_IM_B2R_SRC_IMG_PIXS_WIDTH	(640)
#define CtImB2r_D_IM_B2R_SRC_IMG_PIXS_LINES	(480)

#define CtImB2r_D_IM_B2R_SRC_IMG_GLOBAL_WIDTH_BAY_16BIT_NONPACK			(CtImB2r_D_IM_B2R_SRC_IMG_PIXS_WIDTH * 2)
#define CtImB2r_D_IM_B2R_SRC_IMG_GLOBAL_WIDTH_BAY_12BIT_PACK			(CtImB2r_D_IM_B2R_SRC_IMG_PIXS_WIDTH * 3 / 2)
#define CtImB2r_D_IM_B2R_SRC_IMG_GLOBAL_WIDTH_BAY_10BIT_PACK			(CtImB2r_D_IM_B2R_SRC_IMG_PIXS_WIDTH * 5 / 4)
#define CtImB2r_D_IM_B2R_SRC_IMG_GLOBAL_WIDTH_BAY_8BIT_NONPACK			(CtImB2r_D_IM_B2R_SRC_IMG_PIXS_WIDTH)


#define CtImB2r_D_IM_B2R_DST_IMG_PIXS_WIDTH	(640)
#define CtImB2r_D_IM_B2R_DST_IMG_PIXS_LINES	(480)

#define CtImB2r_D_IM_B2R_DST_IMG_GLOBAL_WIDTH_RGB_U8			(CtImB2r_D_IM_B2R_DST_IMG_PIXS_WIDTH)
#define CtImB2r_D_IM_B2R_DST_IMG_GLOBAL_WIDTH_RGB_P12			(CtImB2r_D_IM_B2R_DST_IMG_PIXS_WIDTH * 3 / 2)
#define CtImB2r_D_IM_B2R_DST_IMG_GLOBAL_WIDTH_RGB_U16			(CtImB2r_D_IM_B2R_DST_IMG_PIXS_WIDTH * 2)


#define CtImB2r_D_IM_B2R_IMG_MEM_IN_ADDR_TOP					(gct_im_b2r_in_addr)


#define CtImB2r_D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP				(CtImB2r_D_IM_B2R_IMG_MEM_IN_ADDR_TOP)
#define CtImB2r_D_IM_B2R_IMG_MEM_IN_BAY_BYTES_16BIT				(CtImB2r_D_IM_B2R_SRC_IMG_GLOBAL_WIDTH_BAY_16BIT_NONPACK * CtImB2r_D_IM_B2R_SRC_IMG_PIXS_LINES)
#define CtImB2r_D_IM_B2R_IMG_MEM_IN_BAY_BYTES_12BIT				(CtImB2r_D_IM_B2R_SRC_IMG_GLOBAL_WIDTH_BAY_12BIT_PACK * CtImB2r_D_IM_B2R_SRC_IMG_PIXS_LINES)
#define CtImB2r_D_IM_B2R_IMG_MEM_IN_BAY_BYTES_10BIT				(CtImB2r_D_IM_B2R_SRC_IMG_GLOBAL_WIDTH_BAY_10BIT_PACK * CtImB2r_D_IM_B2R_SRC_IMG_PIXS_LINES)
#define CtImB2r_D_IM_B2R_IMG_MEM_IN_BAY_BYTES_8BIT				(CtImB2r_D_IM_B2R_SRC_IMG_GLOBAL_WIDTH_BAY_8BIT_NONPACK * CtImB2r_D_IM_B2R_SRC_IMG_PIXS_LINES)
#define CtImB2r_D_IM_B2R_IMG_MEM_IN_BAY_BYTES					(CtImB2r_D_IM_B2R_SRC_IMG_GLOBAL_WIDTH_BAY_16BIT_NONPACK * CtImB2r_D_IM_B2R_SRC_IMG_PIXS_LINES)
#define CtImB2r_D_IM_B2R_IMG_MEM_IN_BAY_ADDR_END				(CtImB2r_D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP + CtImB2r_D_IM_B2R_IMG_MEM_IN_BAY_BYTES)


#define CtImB2r_D_IM_B2R_IMG_MEM_OUT_ADDR_TOP					(gct_im_b2r_out_addr[0])

#define CtImB2r_D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP				(CtImB2r_D_IM_B2R_IMG_MEM_OUT_ADDR_TOP)
#define CtImB2r_D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES				(CtImB2r_D_IM_B2R_DST_IMG_PIXS_WIDTH * CtImB2r_D_IM_B2R_DST_IMG_PIXS_LINES *3)
#define CtImB2r_D_IM_B2R_IMG_MEM_OUT_RGB_P12_BYTES				(CtImB2r_D_IM_B2R_DST_IMG_GLOBAL_WIDTH_RGB_P12 * CtImB2r_D_IM_B2R_DST_IMG_PIXS_LINES *3)
#define CtImB2r_D_IM_B2R_IMG_MEM_OUT_RGB_U16_BYTES				(CtImB2r_D_IM_B2R_DST_IMG_GLOBAL_WIDTH_RGB_U16 * CtImB2r_D_IM_B2R_DST_IMG_PIXS_LINES *3)

#define CtImB2r_D_IM_B2R_IMG_MEM_OUT_RGB_U8_R_ADDR_TOP			(CtImB2r_D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP)
#define CtImB2r_D_IM_B2R_IMG_MEM_OUT_RGB_U8_G_ADDR_TOP			(CtImB2r_D_IM_B2R_IMG_MEM_OUT_RGB_U8_R_ADDR_TOP + CtImB2r_D_IM_B2R_DST_IMG_GLOBAL_WIDTH_RGB_U8 * CtImB2r_D_IM_B2R_DST_IMG_PIXS_LINES)
#define CtImB2r_D_IM_B2R_IMG_MEM_OUT_RGB_U8_B_ADDR_TOP			(CtImB2r_D_IM_B2R_IMG_MEM_OUT_RGB_U8_G_ADDR_TOP + CtImB2r_D_IM_B2R_DST_IMG_GLOBAL_WIDTH_RGB_U8 * CtImB2r_D_IM_B2R_DST_IMG_PIXS_LINES)

#define CtImB2r_D_IM_B2R_IMG_MEM_OUT_RGB_P12_R_ADDR_TOP			(CtImB2r_D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP)
#define CtImB2r_D_IM_B2R_IMG_MEM_OUT_RGB_P12_G_ADDR_TOP			(CtImB2r_D_IM_B2R_IMG_MEM_OUT_RGB_P12_R_ADDR_TOP + CtImB2r_D_IM_B2R_DST_IMG_GLOBAL_WIDTH_RGB_P12 * CtImB2r_D_IM_B2R_DST_IMG_PIXS_LINES)
#define CtImB2r_D_IM_B2R_IMG_MEM_OUT_RGB_P12_B_ADDR_TOP			(CtImB2r_D_IM_B2R_IMG_MEM_OUT_RGB_P12_G_ADDR_TOP + CtImB2r_D_IM_B2R_DST_IMG_GLOBAL_WIDTH_RGB_P12 * CtImB2r_D_IM_B2R_DST_IMG_PIXS_LINES)

#define CtImB2r_D_IM_B2R_IMG_MEM_OUT_RGB_U16_R_ADDR_TOP			(CtImB2r_D_IM_B2R_IMG_MEM_OUT_RGB_ADDR_TOP)
#define CtImB2r_D_IM_B2R_IMG_MEM_OUT_RGB_U16_G_ADDR_TOP			(CtImB2r_D_IM_B2R_IMG_MEM_OUT_RGB_U16_R_ADDR_TOP + CtImB2r_D_IM_B2R_DST_IMG_GLOBAL_WIDTH_RGB_U16 * CtImB2r_D_IM_B2R_DST_IMG_PIXS_LINES)
#define CtImB2r_D_IM_B2R_IMG_MEM_OUT_RGB_U16_B_ADDR_TOP			(CtImB2r_D_IM_B2R_IMG_MEM_OUT_RGB_U16_G_ADDR_TOP + CtImB2r_D_IM_B2R_DST_IMG_GLOBAL_WIDTH_RGB_U16 * CtImB2r_D_IM_B2R_DST_IMG_PIXS_LINES)

#define CtImB2r_D_IM_B2R_IMG_MEM_OUT2_ADDR_TOP					(gct_im_b2r_out_addr[1])

typedef struct 			_CtImB2r CtImB2r;
typedef struct 			_CtImB2rPrivate CtImB2rPrivate;


struct _CtImB2r
{
	KObject parent;
	UCHAR pipeNo;

};


/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
extern ULONG gct_im_b2r_in_addr;
extern ULONG gct_im_b2r_out_addr[2];

/*----------------------------------------------------------------------*/
/* Local Method															*/
/*----------------------------------------------------------------------*/
#ifdef D_IM_B2R_DEBUG_ON_PC
extern volatile UCHAR gIM_B2R_macro_fake_finish[2];
#endif

/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/
#ifdef ImB2r_IM_B2R_STATUS_PRINT
extern void Im_B2R_Print_Status( void );
extern void Im_B2R_Print_ClockStatus( void );
extern void Im_B2R_Print_AccEnStatus( void );
#endif

extern void ct_im_b2r1_printreg( void );

KConstType 				ct_im_b2r_get_type(void);
CtImB2r* 				ct_im_b2r_new(void);

// extern void CT_Im_B2R_Run( const kuint32 ctIdx1st, const kuint32 ctIdx2nd, const kuint32 ctIdx3rd );
void 					ct_im_b2r_run(  CtImB2r *self );
void 					ct_im_b2r_main( kint32 argc, CHAR** argv );
void 					ct_im_b2r_set_value(CtImB2r *self,kuint32 ctIdx1st,kuint32 ctIdx2nd,kuint32 ctIdx3rd);

#endif /* __CT_IM_B2R_H_ */
