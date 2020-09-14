/*
 * imrdma.h
 *
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-09
*@author              :卢樊
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version:        1.0.0
*/


#ifndef __IM_RDMA_H__
#define __IM_RDMA_H__

#include "driver_common.h"
#include <klib.h>

#define IM_TYPE_RDMA		(im_rdma_get_type())
#define IM_RDMA(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImRdma))
#define IM_IS_RDMA(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_RDMA))


/* Return value of processing result
*/
#define D_IM_RDMA_OK					(D_DDIM_OK)								/**< Normal end						*/
#define D_IM_RDMA_NG					(D_IM_RDMA | D_DDIM_SYSTEM_ERROR)		/**< Processing NG					*/
#define D_IM_RDMA_INPUT_PARAM_ERR		(D_IM_RDMA | D_DDIM_INPUT_PARAM_ERROR)	/**< Input Parameter Error			*/
#define D_IM_RDMA_SEM_TIMEOUT			(D_IM_RDMA | D_DDIM_SEM_TIMEOUT)		/**< Semaphore acquisition Time Out */
#define D_IM_RDMA_SEM_NG				(D_IM_RDMA | D_DDIM_SEM_NG)				/**< Semaphore acquisition NG		*/
#define D_IM_RDMA_MACRO_BUSY_NG			(D_IM_RDMA | D_DDIM_MACRO_BUSY_NG)		/**< Macro busy Error				*/


/* Interrupt flag (INTMON1/INTMON2)
*/
#define D_IM_RDMA_FLG_WAIT_END_RDMAF	(0x00000001)							/**< RDMA flag to wait for async processing end */
#define D_IM_RDMA_FLG_WAIT_END_PRF_0	(0x00000002)							/**< PRch0 flag to wait for async processing end */
#define D_IM_RDMA_FLG_WAIT_END_PRF_1	(0x00000004)							/**< PRch1 flag to wait for async processing end */
#define D_IM_RDMA_FLG_WAIT_END_ALL		(0x00000007)							/**< All flag to wait for async processing end */
#define D_IM_RDMA_FLG_ERR_RDMAXF		(0x00000010)							/**< RDMA error flag */
#define D_IM_RDMA_FLG_ERR_PRXF0			(0x00000020)							/**< PRch0 error flag */
#define D_IM_RDMA_FLG_ERR_PRXF1			(0x00000040)							/**< PRch1 error flag */
#define D_IM_RDMA_FLG_ERR_ALL			(0x00000070)							/**< ALL error flag */

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
// Nothing Special
#endif	// CO_DDIM_UTILITY_USE

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
/** Interrupt Mode
*/
typedef enum {
	ImRdma_INT_MODE_OR 	= 0,		/**< Interrupt mode is "OR" */
	ImRdma_INT_MODE_AND,				/**< Interrupt mode is "AND" */
	ImRdma_INT_MODE_AND_ERR ,			/**< Interrupt mode is "AND" + "Error" */
} ImRdmaIntMode;

/** PRch precedent request threshold
*/
typedef enum {
	ImRdma_PRCH_CNT_NOLIMIT  = 0,		/**< PRch no limit		*/
	ImRdma_PRCH_CNT_MAX1 ,			/**< PRch max 1 time	*/
	ImRdma_PRCH_CNT_MAX2,			/**< PRch max 2 times	*/
	ImRdma_PRCH_CNT_MAX3,			/**< PRch max 3 times	*/
} ImRdmaPrchCnt;

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
// Nothing Special
#endif	// CO_DDIM_UTILITY_USE

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
typedef VOID (*T_IM_RDMA_CALLBACK)( ULONG interrupt_flag_mask, ULONG interrupt_error_flag_mask );	/**< Callback function pointer	*/

/** RDMA driver common control structure
*/
typedef struct {
	UINT32				transferByte;			/**< Transfer size of the input/output area. @@PRHSIZE <br>
													 Set at 4 byte units.
												 */
	ULONG				regAddrTblAddr;		/**< Start address of the register address area for PRch0. @@PRSA <br>
													 Set at 4 byte units.
												 */
	ULONG				regDataTopAddr;		/**< Start address of the register data  area for PRch1. @@PRSA <br>
													 Set at 4 byte units.
												 */
	ImRdmaPrchCnt	reqThreshold;			/**< precedent request threshold<br>
													value range		:See @ref E_IM_RDMA_PRCH_CNT<br>
													target registor	:@@PRLV */
	ImRdmaIntMode intMode;				/**< Interrupt Mode<br>
													value range		:See @ref E_IM_RDMA_INT_MODE<br>
													target registor	:@@RDMAINTENB */
	VP_CALLBACK			pCallBack;				/**< Callback function pointer.
												 */
} ImRdmaCtrl;

/** Im_RDMA_Set_Axi() parameter structure */
typedef struct {
	UINT32	writeCacheType;			/**< Write Cache type. */
	UINT32	writeProtectionType;		/**< Write Protection type. */
} ImRdmaAxi;

/** Im_RDMA_Get_Axi_Status() parameter structure */
typedef struct {
	UCHAR	writeChannelResponse;	/**< WRESP register */
} ImRdmaAxiStatus;

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
// Nothing Special
#endif	// CO_DDIM_UTILITY_USE

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
// Nothing Special

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
// Nothing Special
#endif	// CO_DDIM_UTILITY_USE

/*----------------------------------------------------------------------*/
/* Macro                                                                */
/*----------------------------------------------------------------------*/
// Nothing Special

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
// Nothing Special
#endif	// CO_DDIM_UTILITY_USE

typedef struct 				_ImRdma ImRdma;
typedef struct 				_ImRdmaPrivate ImRdmaPrivate;

struct _ImRdma {
	KObject parent;
};

KConstType 		    im_rdma_get_type(void);
ImRdma*		        im_rdma_new(void);

INT32 im_rdma_open( ImRdma*self,INT32 tmout );
INT32 im_rdma_close( ImRdma*self );
INT32 im_rdma_init( ImRdma*self );
INT32 im_rdma_ctrl( ImRdma*self,ImRdmaCtrl* rdma_ctrl );
INT32 im_rdma_start_sync( ImRdma*self );
INT32 im_rdma_start_async( ImRdma*self );
INT32 im_rdma_wait_end( ImRdma*self );
VOID im_rdma_int_handler( VOID );
INT32 im_rdma_get_ctrl( ImRdma*self,ImRdmaCtrl* rdma_ctrl );
ImRdmaIntMode im_rdma_get_int_mode( ImRdma*self );
BOOL im_rdma_get_prch_error_status( ImRdma*self );
INT32 im_rdma_set_axi( ImRdma*self,const ImRdmaAxi* const axi_ctrl );
INT32 im_rdma_get_axi_status( ImRdma*self,ImRdmaAxiStatus* const sts );
VOID im_rdma_print_clock_status( ImRdma*self );
INT32 im_rdma_ctrl_quick_start_sync( ImRdma*self,INT32 tmout, ImRdmaCtrl* rdma_ctrl );


#endif /* __IM_RDAM_H__ */
