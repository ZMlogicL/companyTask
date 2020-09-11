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

#ifndef __IM_LTM_LTM_UTLIS_H__
#define __IM_LTM_LTM_UTLIS_H__

#include <klib.h>

#define IM_TYPE_LTM_LTM_UTLIS							(im_ltm_ltm_utlis_get_type())
#define IM_LTM_LTM_UTLIS(obj)								(K_TYPE_CHECK_INSTANCE_CAST(obj, ImLtmLtmUtlis))
#define IM_IS_LTM_LTM_UTLIS(obj)						(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_LTM_LTM_UTLIS))

#define ImLtmLtmUtlis_IM_LTM_DSB()  Dd_ARM_Dsb_Pou()

// SW reset
#define	ImLtmLtmUtlis_D_IM_LTM_SR_RELEASE				(0)						/**< SW reset release				*/
#define	ImLtmLtmUtlis_D_IM_LTM_SR_RESET				(1)						/**< SW reset state					*/

// LSRAMEN value
#define ImLtmLtmUtlis_D_IM_LTM_LTM_LSRAMEN_ENABLE		(0x00000031)
#define ImLtmLtmUtlis_D_IM_LTM_LTM_LSRAMEN_DISABLE	(0x00000000)

// PIPE count
#define ImLtmLtmUtlis_D_IM_LTM_PIPE_COUNT				(2)

// LINT0 value
#define ImLtmLtmUtlis_D_IM_LTM_LTM_LINT0_ENABLE		(0x02301011)
#define ImLtmLtmUtlis_D_IM_LTM_LTM_LINT0_DISABLE		(0x00000000)
// LINT1 value
#define ImLtmLtmUtlis_D_IM_LTM_LTM_LINT1_ALL_CLR		(0x02301011)

// register bit pattern
#define ImLtmLtmUtlis_D_IM_LTM_LTM_TRG_OFF			(0)
#define ImLtmLtmUtlis_D_IM_LTM_LTM_TRG_ON				(1)
#define ImLtmLtmUtlis_D_IM_LTM_LTM_TRG_IDLE			(2)
#define ImLtmLtmUtlis_D_IM_LTM_LTM_TRG_BUSY			(3)

// Input mode
#define ImLtmLtmUtlis_D_IM_LTM_LTM_MODE_B2R_DIRECT	(0)
#define ImLtmLtmUtlis_D_IM_LTM_LTM_MODE_SDRAM_INPUT	(1)

#define ImLtmLtmUtlis_D_IM_LTM_LTM_SRAM_WAIT_USEC		(1)

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
// Nothing Special
#endif	// CO_DDIM_UTILITY_USE

/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
#define ImLtmLtmUtlis_IM_LTM_LTM_MAX( a, b )						(((a) > (b)) ? (a):(b))
#define ImLtmLtmUtlis_IM_LTM_LTM_MIN( a, b )						(((a) < (b)) ? (a):(b))

#define ImLtmLtmUtlis_IM_LTM_LTM_CHECK_TARGET_PIPE_NO_1(a)		(((a) + 1) & (D_IM_LTM_PIPE1 + 1))
#define ImLtmLtmUtlis_IM_LTM_LTM_CHECK_TARGET_PIPE_NO_2(a)		(((a) + 1) & (D_IM_LTM_PIPE2 + 1))


// The structure type matching check.
#ifdef IM_LTM_LTM_REG_TYPE_CHECK
#define ImLtmLtmUtlis_IM_LTM_LTM_CHECK_REG_TYPE( dst, src )	(dst) = (src);
#else
#define ImLtmLtmUtlis_IM_LTM_LTM_CHEECK_REG_TYPE( dst, src )
#endif

// Signed register access macros.
#define ImLtmLtmUtlis_IM_LTM_LTM_SET_REG_SIGNED( reg, type, member, val )		\
		{ \
			type work = { .word = 0UL }; \
			work.bit.member = (val); \
			(reg).bit.member = work.bit.member; \
			ImLtmLtmUtlis_IM_LTM_LTM_CHEECK_REG_TYPE( work, (reg) );	/* The structure type matching check. */ \
		}

#define ImLtmLtmUtlis_IM_LTM_LTM_SET_REG_SIGNED_A( reg, type, member, val )		\
		{ \
			type work = { .word[0] = 0xFFFFFFFFUL }; \
			work.bit.member = (val); \
			(reg).bit.member = work.bit.member; \
			ImLtmLtmUtlis_IM_LTM_LTM_CHEECK_REG_TYPE( work, (reg) );	/* The structure type matching check. */ \
		}

// wait usec
#define ImLtmLtmUtlis_IM_LTM_LTM_WAIT_USEC( usec )			Dd_ARM_Wait_ns( (usec) * 1000 )

#ifdef CO_ASSERT_ON
#define ImLtmLtmUtlis_M_IM_LTM_LTM_ASSETION_MSG( msg )		(msg)
#else
#define ImLtmLtmUtlis_M_IM_LTM_LTM_ASSETION_MSG( msg )		(NULL)
#endif

typedef struct 																_ImLtmLtmUtlis ImLtmLtmUtlis;
typedef struct 																_ImLtmLtmUtlisPrivate ImLtmLtmUtlisPrivate;

// control information
typedef struct {
	T_IM_LTM_RECT			inputSizeRgb;					// input size(RGB(Main image))
	T_IM_LTM_RECT			inputSizeY;					// input size(Y(Map image))
	UINT32					intStatus;						// Interrupt status
	VOID					(*ltmUserHandler)(UINT32* intStatus, UINT32 userParam);	// Interrupt Handler
	UINT32					userParam;						// return to callback argument value when interrupt occurs
} TImLtmLtmMng;

struct _ImLtmLtmUtlis {
	KObject parent;
	TImLtmLtmMng gIMLtmLtmMng[ImLtmLtmUtlis_D_IM_LTM_PIPE_COUNT];
	volatile struct io_ltm_ch_ltm*gIMIoLtmLtmRegPtr[D_IM_LTM_PIPE_MAX] ;
};

typedef struct {
	ULONG				flgBitmask;		// Bitmask of interrupt flag.
	ULONG				enaBitmask;		// Bitmask of inaerrupt enable.
	ULONG				waitflg;			// Value of set_flg.
	ULONG				intStatus;			// Value of gimLtmLtmMng.intStatus.
} TImLtmLtmIntflgTbl;


KConstType 		    															im_ltm_ltm_utlis_get_type(void);
ImLtmLtmUtlis*		       													im_ltm_ltm_utlis_get(void);

VOID 																						im_ltm_ltm_get_loop_val( UCHAR pipe_no, UCHAR* loop_sta, UCHAR* loop_end );
INT32 																					Im_LTM_LTM_Set_MapImage_Resize_Pitch_Auto( UCHAR pipe_no );
INT32 																					Im_LTM_LTM_Set_MapImage_Resize_Pitch( UCHAR pipe_no, const T_IM_LTM_LTM_MAP_RESIZE_PITCH* const resize_pitch );
INT32 																					Im_LTM_LTM_Set_FrameStop( UCHAR pipe_no, UCHAR onoff );
INT32 																					Im_LTM_LTM_Set_ParamHold( UCHAR pipe_no, const UCHAR hold_enable );
INT32																					Im_LTM_LTM_Get_LtmBusy( UCHAR pipe_no, BOOL* const busy_status );
INT32 																					Im_LTM_LTM_ContStart( UCHAR pipe_no );
INT32 																					Im_LTM_LTM_Start( UCHAR pipe_no );
INT32 																					Im_LTM_LTM_Stop( UCHAR pipe_no );
INT32 																					Im_LTM_LTM_WaitEnd( DDIM_USER_FLGPTN* const p_flgptn, DDIM_USER_FLGPTN waiptn, DDIM_USER_TMO tmout );
VOID 																						Im_LTM_LTM_Int_Handler( UCHAR pipe_no );
INT32 																					Im_LTM_LTM_Set_High_Frequency_Strength( UCHAR pipe_no, const T_IM_LTM_LTM_CTRL_HF_STRENGTH* hf_ctrl );
INT32 																					Im_LTM_LTM_Set_Internal_Param( UCHAR pipe_no, T_IM_LTM_INTERNAL_PARAM* const param );
INT32 																					Im_LTM_LTM_Ctrl_Blend( UCHAR pipe_no, const T_IM_LTM_LTM_CTRL_BLEND* blend_ctrl );
INT32 																					Im_LTM_LTM_Set_RCG_Table( UCHAR pipe_no, const USHORT* const src_tbl );
INT32 																					Im_LTM_LTM_Ctrl_Chroma_Correction_Strength( UCHAR pipe_no, const T_IM_LTM_LTM_CTRL_CHROMA* chroma_ctrl );
INT32 																					Im_LTM_LTM_Ctrl_Ylog_Tbl( UCHAR pipe_no, const T_IM_LTM_CTRL_YLOG* const ylog_ctrl );
INT32 																					Im_LTM_LTM_Get_Active_Ylog_Tbl_No( UCHAR pipe_no, UCHAR* const tbl_no );
INT32 																					Im_LTM_LTM_Set_YLOG_Table( UCHAR pipe_no, UCHAR tbl_sel, const USHORT* const src_tbl );
VOID 																						Im_LTM_LTM_Print_Status( VOID );
VOID 																						Im_LTM_LTM_Print_AccEnStatus( VOID );

#define im_ltm_ltm_utlis_get_gIM_LTM_LTM_Mng(self,i)          (self->gIMLtmLtmMng[i])
#define im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(self,i)          (self->gIMIoLtmLtmRegPtr[i])

#endif /* __IM_LTM_LTM_UTLIS_H__ */
