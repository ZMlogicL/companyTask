/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-07
*@author              :李昕
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年06月开始开发
*/

#ifndef _IM_CNR_INIT_H_
#define _IM_CNR_INIT_H_

#include <klib.h>
#include "imcnr.h"
#include "driver_common.h"
#include "ddim_typedef.h"
// get register value for RDMA
#include "_jdscnr_cspr_reg.h"
#include "_jdscnr_ofl_reg_rw.h"
#include "_jdscnr_ofl_reg_yspr.h"
#include "_jdscnr_otf_reg_rw.h"

#define IM_TYPE_CNR_INIT		(im_cnr_init_get_type())
#define IM_CNR_INIT(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImCnrInit))
#define IM_IS_CNR_INIT(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_CNR_INIT))

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
#define D_IM_CNR_ADDR_BANK_MAX			(4)				/**< Maximum output bank index number of WCTA */
#define ADDR_BNK_LIMIT(pos, total) ((pos < total) ? pos : 0)

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
/** Im_CNR_OTF_Set_OutAddr_Info() parameter structure */
typedef struct {
	UCHAR				use_bank_num;						/**< CbCr address bank number @@WCTA
																	Use only one bank in the setting of 1 (d),
																	and use of the four banks in the setting of 4 (d).	*/
	ULONG				w_c_addr[D_IM_CNR_ADDR_BANK_MAX];	/**< CbCr address for write (aligned on 2bytes)		@@WCTA	*/
} T_IM_CNR_OTF_OUTADDR_INFO;

// Output address management information
typedef struct {
	UCHAR	use_bank_num;							// Output bank number
	UCHAR	bank_area;								// Target bank number
	ULONG	output_addr[D_IM_CNR_ADDR_BANK_MAX];	// Output bank address information.
} T_IM_CNR_OUTPUT_MNG;

// Output latest management information
typedef struct {
	UCHAR	bank_area;								// Latest bank number
	ULONG	addr;									// Latest Output address.
} T_IM_CNR_LATEST_MNG;

typedef struct 				_ImCnrInit ImCnrInit;
typedef struct 				_ImCnrInitPrivate ImCnrInitPrivate;

struct _ImCnrInit {
	KObject parent;
};

KConstType 		    im_cnr_init_get_type(void);
ImCnrInit*		        im_cnr_init_new(void);

/*----------------------------------------------------------------------*/
/* Function Prototype Definition										*/
/*----------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif
//---------------------------- driver section ----------------------------
VOID im_cnr_otf_int_handler( UCHAR ch );
VOID im_cnr_ofl_int_handler( UCHAR ch );

/**
Set software reset and operating mode for Off Line
@param [in]	ch				channel[0 - 2]
@retval		D_DDIM_OK						Success
*/
INT32 Im_CNR_OFL_Init( UCHAR ch );

/**
Suppre Control for Off Line
@param [in]	ch				channel[0 - 2]
@param[in]	cnr_ctrl
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	The calcurate mode of the Suppre is set.
			Please call Y, C or both setting after this function if necessary.
*/
INT32 Im_CNR_OFL_Ctrl( UCHAR ch, const T_IM_CNR_OFL_CTRL* const cnr_ctrl );

/**
Set software reset and operating mode for On The Fly
@param [in]	ch				channel[0 - 2]
@retval		D_DDIM_OK						Success
*/
INT32 Im_CNR_OTF_Init( UCHAR ch );

/**
Suppre Control for On The Fly
@param [in]	ch				channel[0 - 2]
@param[in]	cnr_ctrl
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	The calcurate mode of the Suppre is set.
			Please call Y, C or both setting after this function if necessary.
*/
INT32 Im_CNR_OTF_Ctrl( UCHAR ch, const T_IM_CNR_OTF_CTRL* const cnr_ctrl );

/**
Set Suppre output address information for On The Fly
@param [in]	ch				channel[0 - 2]
@param[in]	addr_info
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 Im_CNR_OTF_Set_OutAddr_Info( UCHAR ch, const T_IM_CNR_OTF_OUTADDR_INFO* const addr_info );

/**
Increment Suppre output address index for On The Fly
@param [in]	ch				channel[0 - 1]
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 Im_CNR_OTF_Increment_OutAddr_Index( UCHAR ch );

/**
SPR Get Latest Address information for On The Fly
@param [in]		ch				channel[0 - 1]
@param [out]	latest_addr		latest CbCr image address
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 Im_CNR_OTF_Get_Latest_OutAddr( UCHAR ch, ULONG* const latest_addr );

#endif// _IM_CNR_INIT_H_
