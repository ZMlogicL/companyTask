/*
 * imltm1.h
 *
 *  Created on: 2020年9月3日
 *      Author: sns
 */

#ifndef __IM_LTM1_H__
#define __IM_LTM1_H__

#include <klib.h>
#include "ddim_typedef.h"
#include "imltm.h"

#ifdef CO_ASSERT_ON
#define M_IM_LTM_RBK_ASSETION_MSG( msg )		(msg)
#else
#define M_IM_LTM_RBK_ASSETION_MSG( msg )		(NULL)
#endif

#define IM_TYPE_LTM1			(im_ltm1_get_type())
#define IM_LTM1(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, ImLtm1))
#define IM_IS_LTM1(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, ImLtm1))
#define Im_LTM_Dsb()	Dd_ARM_Dsb_Pou()
#define	D_IM_LTM_SR_RELEASE				(0)						/**< SW reset release				*/
#define	D_IM_LTM_SR_RESET					(1)						/**< SW reset state					*/
#define D_IM_LTM_RBK_RSRAMEN_ENABLE		(0x000003B1)
#define D_IM_LTM_RBK_RSRAMEN_DISABLE		(0x00000000)
#define D_IM_LTM_PIPE_COUNT					(2)
#define D_IM_LTM_RBK_RINT0_ENABLE		(0x00311011)
#define D_IM_LTM_RBK_RINT0_DISABLE		(0x00000000)
#define D_IM_LTM_RBK_RINT1_ALL_CLR		(0x00311011)
#define D_IM_LTM_RBK_TRG_OFF				(0)
#define D_IM_LTM_RBK_TRG_ON				(1)
#define D_IM_LTM_RBK_TRG_IDLE				(2)
#define D_IM_LTM_RBK_TRG_BUSY				(3)
#define D_IM_LTM_RBK_RTHSTA_MIN			(0)
#define D_IM_LTM_RBK_RTHSTA_MAX		(845)
#define D_IM_LTM_RBK_RTVSTA_MIN			(0)
#define D_IM_LTM_RBK_RTVSTA_MAX		(1014)
#define D_IM_LTM_RBK_RTHSIZ_MIN			(8)
#define D_IM_LTM_RBK_RTHSIZ_MAX			(854)
#define D_IM_LTM_RBK_RTVSIZ_MIN			(8)
#define D_IM_LTM_RBK_RTVSIZ_MAX			(1022)
#define D_IM_LTM_RBK_MODE_SRO_DIRECT		(0)
#define D_IM_LTM_RBK_MODE_SDRAM_INPUT	(2)
#define D_IM_LTM_RBK_SRAM_WAIT_USEC		(1)
#define im_ltm_rbk_max( a, b )						(((a) > (b)) ? (a):(b))
#define im_ltm_rbk_min( a, b )						(((a) < (b)) ? (a):(b))
#define im_ltm_rbk_check_target_pipe_no_1(a)		(((a) + 1) & (ImLtm_D_IM_LTM_PIPE1 + 1))
#define im_ltm_rbk_check_target_pipe_no_2(a)		(((a) + 1) & (D_IM_LTM_PIPE2 + 1))
#define im_ltm_rbk_wait_usec( usec )			Dd_ARM_Wait_ns( (usec) * 1000 )

typedef struct _ImLtm1 ImLtm1;
typedef struct {
	T_IM_LTM_RECT			input_size;						// input size
	UINT32					int_status;						// Interrupt status
	UCHAR					resolution_conversion;			// 0:off,1:on
	VOID					(*rbk_user_handler)(UINT32* int_status, UINT32 user_param);	// Interrupt Handler
	UINT32					user_param;						// return to callback argument value when interrupt occurs
} T_IM_LTM_RBK_MNG;

typedef struct {
	ULONG				flg_bitmask;		// Bitmask of interrupt flag.
	ULONG				ena_bitmask;		// Bitmask of inaerrupt enable.
	ULONG				waitflg;			// Value of set_flg.
	ULONG				int_status;			// Value of gIM_LTM_RBK_Mng.int_status.
} T_IM_LTM_RBK_INTFLG_TBL;

struct _ImLtm1 {
	KObject parent;
};

static volatile T_IM_LTM_RBK_MNG gIM_LTM_RBK_Mng[D_IM_LTM_PIPE_COUNT];
//static volatile struct io_ltm_ch_rbk* gIM_Io_Ltm_Rbk_Reg_Ptr[ImLtm_D_IM_LTM_PIPE_MAX] = { &(IO_LTM_P1.RBK), &(IO_LTM_P2.RBK), &(IO_LTM_P3.RBK) };
static const T_IM_LTM_RBK_INTFLG_TBL gim_ltm_rbk_inttbl[D_IM_LTM_PIPE_COUNT][6] = {
	{
		{ 0x00000001, 0x00000001, D_IM_LTM_RBK1_INT_STATE_RBK_END,   D_IM_LTM_RBK1_INT_FLG_RBK_END   },	// FINEN
		{ 0x00000010, 0x00000010, D_IM_LTM_RBK1_INT_STATE_FRAME_END, D_IM_LTM_RBK1_INT_FLG_FRAME_END },	// FRMEN
		{ 0x00001000, 0x00001000, D_IM_LTM_RBK1_INT_STATE_LINE_END,  D_IM_LTM_RBK1_INT_FLG_LINE_END  },	// LCNTEN
		{ 0x00010000, 0x00010000, D_IM_LTM_RBK1_INT_STATE_WAIT_ERR,  D_IM_LTM_RBK1_INT_FLG_WAIT_ERR  },	// WAITEN
		{ 0x00100000, 0x00100000, D_IM_LTM_RBK1_INT_STATE_AXR_ERR,   D_IM_LTM_RBK1_INT_FLG_AXR_ERR   },	// AXREEN
		{ 0x00200000, 0x00200000, D_IM_LTM_RBK1_INT_STATE_AXW_ERR,   D_IM_LTM_RBK1_INT_FLG_AXW_ERR   },	// AXWEEN
	},
	{
		{ 0x00000001, 0x00000001, D_IM_LTM_RBK2_INT_STATE_RBK_END,   D_IM_LTM_RBK2_INT_FLG_RBK_END   },	// FINEN
		{ 0x00000010, 0x00000010, D_IM_LTM_RBK2_INT_STATE_FRAME_END, D_IM_LTM_RBK2_INT_FLG_FRAME_END },	// FRMEN
		{ 0x00001000, 0x00001000, D_IM_LTM_RBK2_INT_STATE_LINE_END,  D_IM_LTM_RBK2_INT_FLG_LINE_END  },	// LCNTEN
		{ 0x00010000, 0x00010000, D_IM_LTM_RBK2_INT_STATE_WAIT_ERR,  D_IM_LTM_RBK2_INT_FLG_WAIT_ERR  },	// WAITEN
		{ 0x00100000, 0x00100000, D_IM_LTM_RBK2_INT_STATE_AXR_ERR,   D_IM_LTM_RBK2_INT_FLG_AXR_ERR   },	// AXREEN
		{ 0x00200000, 0x00200000, D_IM_LTM_RBK2_INT_STATE_AXW_ERR,   D_IM_LTM_RBK2_INT_FLG_AXW_ERR   },	// AXWEEN
	},
};

KConstType 		    im_ltm1_get_type(void);
ImLtm1*		            im_ltm1_new(void);

extern INT32 im_ltm_rbk_init( UCHAR pipe_no );
extern INT32 im_ltm_rbk_sw_reset( UCHAR pipe_no );
extern INT32 im_ltm_rbk_ctrl_axi( UCHAR pipe_no, const T_IM_LTM_RBK_CTRL_AXI* const ctrl_axi );
extern INT32 im_ltm_rbk_get_axireadstat( UCHAR pipe_no, T_IM_LTM_RBK_AXI_RCH_STAT* const axi_read_stat );
extern INT32 Im_LTM_RBK_Get_AxiWriteStat( UCHAR pipe_no, T_IM_LTM_RBK_AXI_WCH_STAT* const axi_write_stat );
extern INT32 im_ltm_rbk_get_axictrlparam( UCHAR pipe_no, T_IM_LTM_RBK_AXI_CTRL_PARAM* const axi_ctrl_prm );
extern INT32 im_ltm_rbk_set_axictrlparam( UCHAR pipe_no, const T_IM_LTM_RBK_AXI_CTRL_PARAM* const axi_ctrl_prm );
extern INT32 im_ltm_rbk_ctrl_common( UCHAR pipe_no, const T_IM_LTM_RBK_CTRL_COMMON* const rbk_ctrl );
extern INT32 im_ltm_rbk_ctrl_modesdraminput( UCHAR pipe_no, const T_IM_LTM_RBK_CTRL_SDRAM_INPUT* const rbk_ctrl_sdram_input );
extern INT32 im_ltm_rbk_set_inaddr_info( UCHAR pipe_no, const T_IM_LTM_INADDR_INFO* const in_addr );
extern INT32 im_ltm_rbk_set_outdata_info( UCHAR pipe_no, const T_IM_LTM_RBK_OUTDATA_INFO* const out_data_info );
extern INT32 im_ltm_rbk_ctrl_modesrodirect( UCHAR pipe_no, const T_IM_LTM_RBK_CTRL_SRO_DIRECT* const rbk_ctrl_sro_direct );
extern INT32 im_ltm_rbk_ctrl_resolution_conversion( UCHAR pipe_no, const UCHAR conversion_on_off );
extern INT32 im_ltm_rbk_set_framestop( UCHAR pipe_no, UCHAR onoff );
extern INT32 im_ltm_rbk_set_paramhold( UCHAR pipe_no, const UCHAR hold_enable );
extern INT32 im_ltm_rbk_get_rbkbusy( UCHAR pipe_no, BOOL* const busy_status );
extern INT32 im_ltm_rbk_contstart( UCHAR pipe_no );
extern INT32 im_ltm_rbk_start( UCHAR pipe_no );
extern INT32 im_ltm_rbk_stop( UCHAR pipe_no );
extern INT32 im_ltm_rbk_waitend( DDIM_USER_FLGPTN* const p_flgptn, DDIM_USER_FLGPTN waiptn, DDIM_USER_TMO tmout );
extern VOID 	im_ltm_rbk_int_handler( UCHAR pipe_no );
extern INT32 im_ltm_rbk_ctrl_rgbtrimming( UCHAR pipe_no, const T_IM_LTM_RBK_RGB_TRIMMING* const rbk_trimming );

#endif /* __IM_LTM1_H__ */








