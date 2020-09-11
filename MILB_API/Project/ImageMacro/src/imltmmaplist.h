/*
*@Copyright (C) 2010-2020贵阳高新网用软件有限公司
*@date                :2020-9-2
*@author           :sunhongyu
*@brief                :imltmmaplist类
*@rely                  :
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __IM_LTM_MAP_LIST_H__
#define __IM_LTM_MAP_LIST_H__

#include <klib.h>

#define IM_TYPE_LTM_MAP_LIST				(im_ltm_map_list_get_type())
#define IM_LTM_MAP_LIST(obj)				(K_TYPE_CHECK_INSTANCE_CAST(obj, ImLtmMapList))
#define IM_IS_LTM_MAP_LIST(obj)			(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_LTM_MAP_LIST))

#define	ImLtmMapList_D_IM_LTM_MAP1_INT_FLG_ALL			(0x0000003F)			/**< All flags(PIPE1)				*/
#define	ImLtmMapList_D_IM_LTM_MAP2_INT_FLG_ALL			(0x00003F00)			/**< All flags(PIPE2)				*/
#define	ImLtmMapList_D_IM_LTM_MAP_INT_FLG_ALL			(0x00003F3F)			/**< All flags						*/

#define ImLtmMapList_Im_LTM_Dsb()	Dd_ARM_Dsb_Pou()

// SW reset
#define	ImLtmMapList_D_IM_LTM_SR_RELEASE				(0)						/**< SW reset release				*/
#define	ImLtmMapList_D_IM_LTM_SR_RESET				(1)						/**< SW reset state					*/

// MSRAMEN value
#define ImLtmMapList_D_IM_LTM_MAP_MSRAMEN_ENABLE		(0x000000B1)
#define ImLtmMapList_D_IM_LTM_MAP_MSRAMEN_DISABLE	(0x00000000)

// PIPE count
#define ImLtmMapList_D_IM_LTM_PIPE_COUNT				(2)

// MINT0 value
#define ImLtmMapList_D_IM_LTM_MAP_MINT0_ENABLE		(0x02311001)
#define ImLtmMapList_D_IM_LTM_MAP_MINT0_DISABLE		(0x00000000)
// MINT1 value
#define ImLtmMapList_D_IM_LTM_MAP_MINT1_ALL_CLR		(0x02301001)

// register bit pattern
#define ImLtmMapList_D_IM_LTM_MAP_TRG_OFF			(0)
#define ImLtmMapList_D_IM_LTM_MAP_TRG_ON				(1)
#define ImLtmMapList_D_IM_LTM_MAP_TRG_IDLE			(2)
#define ImLtmMapList_D_IM_LTM_MAP_TRG_BUSY			(3)

// Input mode
#define ImLtmMapList_D_IM_LTM_MAP_MODE_RBK_DIRECT	(0)
#define ImLtmMapList_D_IM_LTM_MAP_MODE_SDRAM_INPUT	(1)

#define ImLtmMapList_D_IM_LTM_MAP_SRAM_WAIT_USEC		(1)

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
// Nothing Special
#endif	// CO_DDIM_UTILITY_USE

#define ImLtmMapList_IM_LTM_MAP_CHECK_TARGET_PIPE_NO_1(a)		(((a) + 1) & (D_IM_LTM_PIPE1 + 1))
#define ImLtmMapList_IM_LTM_MAP_CHECK_TARGET_PIPE_NO_2(a)		(((a) + 1) & (D_IM_LTM_PIPE2 + 1))

// wait usec
#define ImLtmMapList_IM_LTM_MAP_WAIT_USEC( usec )			Dd_ARM_Wait_ns( (usec) * 1000 )

#ifdef CO_ASSERT_ON
#define ImLtmMapList_IM_IM_LTM_MAP_ASSETION_MSG( msg )		(msg)
#else
#define ImLtmMapList_M_IM_LTM_MAP_ASSETION_MSG( msg )		(NULL)
#endif

typedef struct 				_ImLtmMapList ImLtmMapList;
typedef struct 				_ImLtmMapListPrivate ImLtmMapListPrivate;

typedef struct {
	T_IM_LTM_RECT			inputSize;						// input size
	UINT32					intStatus;						// Interrupt status
	VOID					(*mapUserHandler)(UINT32* int_status, UINT32 userParam);	// Interrupt Handler
	UINT32					userParam;						// return to callback argument value when interrupt occurs
} TImLtmMapMng;

struct _ImLtmMapList {
	KObject parent;
 TImLtmMapMng gIMLtmMapMng[ImLtmMapList_D_IM_LTM_PIPE_COUNT];
 volatile struct io_ltm_ch_map* gIMIoLtmMapRegPtr[D_IM_LTM_PIPE_MAX];
};


// Interrupt parameter table
typedef struct {
	ULONG				flgBitmask;		// Bitmask of interrupt flag.
	ULONG				enaBitmask;		// Bitmask of inaerrupt enable.
	ULONG				waitflg;			// Value of set_flg.
	ULONG				intStatus;			// Value of gIM_LTM_MAP_Mng.int_status.
} TImLtmMapIntflgTbl;

KConstType 		    					 im_ltm_map_list_get_type(void);
ImLtmMapList*		       			 im_ltm_map_list_get(void);

VOID 												im_ltm_map_get_loop_val( UCHAR pipe_no, UCHAR* loop_sta, UCHAR* loop_end );
INT32											Im_LTM_MAP_Set_AxiCtrlParam( UCHAR pipe_no, const T_IM_LTM_MAP_AXI_CTRL_PARAM* const axi_ctrl_prm );
INT32 											Im_LTM_MAP_Set_FrameStop( UCHAR pipe_no, UCHAR onoff );
INT32 											Im_LTM_MAP_Set_ParamHold( UCHAR pipe_no, const UCHAR hold_enable );
INT32										    Im_LTM_MAP_Get_MapBusy( UCHAR pipe_no, BOOL* const busy_status );
INT32 											Im_LTM_MAP_ContStart( UCHAR pipe_no );
INT32 											Im_LTM_MAP_Start( UCHAR pipe_no );
INT32 											Im_LTM_MAP_Stop( UCHAR pipe_no );
VOID 												Im_LTM_MAP_Int_Handler( UCHAR pipe_no );
INT32 											Im_LTM_MAP_Set_WB_Gain( UCHAR pipe_no, const T_IM_LTM_MAP_GAIN* const wb_gain );
 INT32 											Im_LTM_MAP_Get_Internal_Param( UCHAR pipe_no, T_IM_LTM_INTERNAL_PARAM* const param );
 INT32					 						Im_LTM_MAP_Ctrl_Generation_Mode( UCHAR pipe_no, const T_IM_LTM_MAP_CTRL_GENERATION_MODE* const mode );
INT32 											Im_LTM_MAP_Ctrl_Ylog_Tbl( UCHAR pipe_no, const T_IM_LTM_CTRL_YLOG* const ylog_ctrl );
INT32 											Im_LTM_MAP_Get_Active_Ylog_Tbl_No( UCHAR pipe_no, UCHAR* const tbl_no );
INT32 											Im_LTM_MAP_Set_YLOG_Table( UCHAR pipe_no, UCHAR tbl_sel, const USHORT* const src_tbl );
VOID 												Im_LTM_MAP_Print_Status( VOID );
VOID 												Im_LTM_MAP_Print_AccEnStatus( VOID );

#define im_ltm_map_list_get_gIM_LTM_MAP_Mng(self,i)          (self->gIMLtmMapMng[i])
#define im_ltm_map_list_get_gIM_Io_Ltm_Map_Reg_Ptr(self,i)          (self->gIMIoLtmMapRegPtr[i])
//ImLtmMapList*imLtmMapList=im_ltm_map_list_get( );

#endif /* __IM_LTM_MAP_LIST_H__ */
