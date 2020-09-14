/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :唐萍萍
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __IM_B2R1_H__
#define __IM_B2R1_H__

#include <klib.h>

#define IM_TYPE_B2R1		(im_b2r1_get_type())
#define IM_B2R1(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImB2r1))
#define IM_IS_B2R1(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_B2R1))

typedef struct 				_ImB2r1 ImB2r1;
typedef struct 				_ImB2r1Private ImB2r1Private;

struct _ImB2r1 {
	KObject parent;
};

KConstType 		    im_b2r1_get_type(void);
ImB2r1*		        im_b2r1_get(void);

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------

//#define CO_B2R_RDMA_ON

#define ImB2r1_IM_B2R_DSB()	Dd_ARM_Dsb_Pou()

#define ImB2r1_D_IM_B2R1_CLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP10())
#define ImB2r1_D_IM_B2R1_HCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP10())
#define ImB2r1_D_IM_B2R1_PCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP10())
#define ImB2r1_D_IM_B2R1_ICLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP10())

#define ImB2r1_D_IM_B2R2_CLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP12())
#define ImB2r1_D_IM_B2R2_HCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP12())
#define ImB2r1_D_IM_B2R2_PCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP12())
#define ImB2r1_D_IM_B2R2_ICLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP12())

#define ImB2r1_D_IM_B2R1_CLK_REG_BIT	D_DD_TOP_B2R1CK_BIT
#define ImB2r1_D_IM_B2R1_HCLK_REG_BIT	D_DD_TOP_B2R1AH_BIT
#define ImB2r1_D_IM_B2R1_PCLK_REG_BIT	D_DD_TOP_B2R1AP_BIT
#define ImB2r1_D_IM_B2R1_ICLK_REG_BIT	D_DD_TOP_B2R1AX_BIT

#define ImB2r1_D_IM_B2R2_CLK_REG_BIT	D_DD_TOP_B2R2CK_BIT
#define ImB2r1_D_IM_B2R2_HCLK_REG_BIT	D_DD_TOP_B2R2AH_BIT
#define ImB2r1_D_IM_B2R2_PCLK_REG_BIT	D_DD_TOP_B2R2AP_BIT
#define ImB2r1_D_IM_B2R2_ICLK_REG_BIT	D_DD_TOP_B2R2AX_BIT


/* debug print switch  for im_b2r.c developping/debugging person.
 * (not im_b2r user)
 */
//#define IM_B2R_DEBUG_PRINT
//#define ImB2r_IM_B2R_STATUS_PRINT
//#define IM_B2R_REG_TYPE_CHECK

// True/False (UCHAR)
#define ImB2r1_D_IM_B2R_TRUE					((UCHAR)1)
#define ImB2r1_D_IM_B2R_FALSE					((UCHAR)0)



// Driver state of Starting flag
#define ImB2r1_D_IM_B2R_STATE_IDLE				(0x00)
#define ImB2r1_D_IM_B2R_STATE_BUSY_F_B2R		(0x01)
#define ImB2r1_D_IM_B2R_STATE_BUSY_YBR			(0x02)
#define ImB2r1_D_IM_B2R_STATE_BUSY_YBW			(0x04)
#define ImB2r1_D_IM_B2R_STATE_BUSY_ALL			(ImB2r1_D_IM_B2R_STATE_BUSY_F_B2R | ImB2r1_D_IM_B2R_STATE_BUSY_YBR | ImB2r1_D_IM_B2R_STATE_BUSY_YBW)

// YBINTE value
#define ImB2r1_D_IM_B2R_YBINTE_ALL_ENABLE		(0x00003333)	// YBR, YBW, AXI
#define ImB2r1_D_IM_B2R_YBINTE_EXT_ONLY_ENABLE	(0x00001111)	// YBR, AXI
#define ImB2r1_D_IM_B2R_YBINTE_DISABLE			(0x00000000)
// YBINTF value
#define ImB2r1_D_IM_B2R_YBINTF_ALL_CLR			(0x00003333)	// YBR, YBW, AXI

// B2RINTE value
#define ImB2r1_D_IM_B2R_B2RINTE_ENABLE			(0x01)
#define ImB2r1_D_IM_B2R_B2RINTE_DISABLE		(0x00)

// B2RINTF value
#define ImB2r1_D_IM_B2R_B2RINTF_CLR			(0x01)

// register bit pattern
#define ImB2r1_D_IM_B2R_FB2RTRG_OFF			(0)
#define ImB2r1_D_IM_B2R_FB2RTRG_ON				(1)
#define ImB2r1_D_IM_B2R_FB2RTRG_IDLE			(2)
#define ImB2r1_D_IM_B2R_FB2RTRG_BUSY			(3)

#define ImB2r1_D_IM_B2R_YBRTRG_OFF				(0)
#define ImB2r1_D_IM_B2R_YBRTRG_ON				(1)
#define ImB2r1_D_IM_B2R_YBRTRG_IDLE			(2)
#define ImB2r1_D_IM_B2R_YBRTRG_BUSY			(3)

#define ImB2r1_D_IM_B2R_YBWTRG_OFF				(0)
#define ImB2r1_D_IM_B2R_YBWTRG_ON				(1)
#define ImB2r1_D_IM_B2R_YBWTRG_IDLE			(2)
#define ImB2r1_D_IM_B2R_YBWTRG_BUSY			(3)

#define ImB2r1_D_IM_B2R_PACK10_MSB_CYCLE_PIXS	(4)
#define ImB2r1_D_IM_B2R_PACK12_MSB_CYCLE_PIXS	(2)

// YBRHSIZ register value
#define ImB2r1_D_IM_B2R_YBRHSIZ_MIN			(96)
#define ImB2r1_D_IM_B2R_YBRHSIZ_MAX			(2360)

// YBRVSIZ register value
#define ImB2r1_D_IM_B2R_YBRVSIZ_MIN			(72)
#define ImB2r1_D_IM_B2R_YBRVSIZ_MAX			(8960)

// DINHSTA register value
#define ImB2r1_D_IM_B2R_DINHSTA_MIN			(0)
#define ImB2r1_D_IM_B2R_DINHSTA_MAX			(2262)

// DINVSTA register value
#define ImB2r1_D_IM_B2R_DINVSTA_MIN			(0)
#define ImB2r1_D_IM_B2R_DINVSTA_MAX			(8886)

// DINHSIZ register value
#define ImB2r1_D_IM_B2R_DINHSIZ_MIN			(96)
#define ImB2r1_D_IM_B2R_DINHSIZ_MAX			(2360)

// DINVSIZ register value
#define ImB2r1_D_IM_B2R_DINVSIZ_MIN			(72)
#define ImB2r1_D_IM_B2R_DINVSIZ_MAX			(8960)

// TRMHSTA register value
#define ImB2r1_D_IM_B2R_TRMHSTA_MIN			(0)
#define ImB2r1_D_IM_B2R_TRMHSTA_MAX			(2262)

// TRMVSTA register value
#define ImB2r1_D_IM_B2R_TRMVSTA_MIN			(0)
#define ImB2r1_D_IM_B2R_TRMVSTA_MAX			(8886)

// TRMHSIZ register value
#define ImB2r1_D_IM_B2R_TRMHSIZ_MIN			(96)
#define ImB2r1_D_IM_B2R_TRMHSIZ_MAX			(2360)

// TRMVSIZ register value
#define ImB2r1_D_IM_B2R_TRMVSIZ_MIN			(72)
#define ImB2r1_D_IM_B2R_TRMVSIZ_MAX			(8960)

// B2R Photo/Video mode(DINSEL.B2BDIN)
#define ImB2r1_D_IM_B2R_MODE_SDRAM_INPUT		(0)
#define ImB2r1_D_IM_B2R_MODE_B2B_DIRECT		(1)

#define ImB2r1_D_IM_B2R_SRAM_WAIT_USEC			(1)

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
#define ImB2r1_IM_B2R_INC_BANK_INDEX(bank_index, max)	(((bank_index) + 1) % (max))

#define ImB2r1_IM_B2R_ROUNDDOWN_2(a)					(((a) >> 1) << 1)					// for 2 byte alignment

#define ImB2r1_IM_B2R_MAX( a, b )						(((a) > (b)) ? (a):(b))
#define ImB2r1_IM_B2R_MIN( a, b )						(((a) < (b)) ? (a):(b))

#define ImB2r1_IM_B2R_CHECK_TARGET_PIPE_NO_1(a)		(((a) + 1) & (ImB2r_D_IM_B2R_PIPE1 + 1))
#define ImB2r1_IM_B2R_CHECK_TARGET_PIPE_NO_2(a)		(((a) + 1) & (ImB2r_D_IM_B2R_PIPE2 + 1))


// The structure type matching check.
#ifdef IM_B2R_REG_TYPE_CHECK
#define ImB2r1_IM_B2R_CHECK_REG_TYPE( dst, src )	(dst) = (src);
#else
#define ImB2r1_IM_B2R_CHECK_REG_TYPE( dst, src )
#endif



// Signed register access macros.
#define ImB2r1_IM_B2R_SET_REG_SIGNED( reg, type, member, val )		\
		{ \
			type work = { .word = 0UL }; \
			work.bit.member = (val); \
			(reg).bit.member = work.bit.member; \
			ImB2r1_IM_B2R_CHECK_REG_TYPE( work, (reg) );	/* The structure type matching check. */ \
		}

#define ImB2r1_IM_B2R_SET_REG_SIGNED_A( reg, type, member, val )		\
		{ \
			type work = { .word[0] = 0xFFFFFFFFUL }; \
			work.bit.member = (val); \
			(reg).bit.member = work.bit.member; \
			ImB2r1_IM_B2R_CHECK_REG_TYPE( work, (reg) );	/* The structure type matching check. */ \
		}


// wait usec
#define ImB2r1_IM_B2R_WAIT_USEC( usec )				Dd_ARM_Wait_ns( (usec) * 1000 )


#ifdef CO_ASSERT_ON
#define ImB2r1_M_IM_B2R_ASSETION_MSG( msg )		(msg)
#else
#define ImB2r1_M_IM_B2R_ASSETION_MSG( msg )		(NULL)
#endif


#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
// Nothing Special
#endif	// CO_DDIM_UTILITY_USE

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
// Nothing Special

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
// Nothing Special
#endif	// CO_DDIM_UTILITY_USE

// PIPE count
#define ImB2r1_D_IM_B2R_PIPE_COUNT				(2)

/*----------------------------------------------------------------------*/
/* Grobal Function														*/
/*----------------------------------------------------------------------*/
INT32 Im_B2R_Init( UCHAR pipe_no );
INT32 Im_B2R_Set_InAddr_Info(UCHAR pipe_no, const T_IM_B2R_INADDR_INFO* const in_addr );
VOID Im_B2R_Int_Handler(UCHAR pipe_no );
#ifdef ImB2r_IM_B2R_STATUS_PRINT
VOID Im_B2R_Print_Status( VOID );///////////////////////////////////////////////////////////////////////头文件没有
VOID Im_B2R_Print_AccEnStatus( VOID );///////////////////////////////////////////////////////////////////////头文件没有
#endif
INT32 Im_B2R_Set_OutBankInfo(UCHAR pipe_no, const T_IM_B2R_OUTBANK_INFO* const b2r_bank );
INT32 Im_B2R_Get_Latest_OutAddr( UCHAR pipe_no, UCHAR* const latest_bank_idx, T_IM_B2R_OUTADDR_INFO* const latest_addr );
INT32 Im_B2R_Get_OutBankIndex( UCHAR pipe_no, UCHAR* const bank_index );
INT32 Im_B2R_Get_Rect_Param( UCHAR pipe_no, T_IM_B2R_RECT* const b2r_rect_param );
INT32 Im_B2R_Set_Rect( UCHAR pipe_no, const T_IM_B2R_RECT* const b2r_rect_param );
INT32 Im_B2R_Ctrl(UCHAR pipe_no, const T_IM_B2R_CTRL* const b2r_ctrl );

#endif /* __IM_B2R1_H__ */
