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
#include <string.h>
#include "imbmh.h"
#include "driver_common.h"
// #if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
// #endif
#include "dd_arm.h"
#include "ddim_user_custom.h"

#include "jmlbmh.h"
#include"imbmh1.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImBmh, im_bmh);
#define IM_BMH_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImBmhPrivate, IM_TYPE_BMH))

struct _ImBmhPrivate
{
	int a;
};

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
// #define CO_BMH_DEBUG
// #define CO_BMH_REG_TYPE_CHECK

// Low power consumption option
#ifdef CO_ACT_CLOCK
#define ImBmh_CO_ACT_BMHCLOCK
#endif	// CO_ACT_CLOCK
#ifdef CO_ACT_ICLOCK
#define ImBmh_CO_ACT_BMH_ICLK
#endif	// CO_ACT_ICLOCK

#define ImBmh_D_IM_BMH_SYNC				(0)				// Sync Processing
#define ImBmh_D_IM_BMH_ASYNC				(1)				// Async Processing
#define ImBmh_D_IM_BMH_SRAM_WAIT_USEC		(1)
#define ImBmh_D_IM_BMH_WAIT_FLGPTN		(ImBmh_D_IM_BMH_FLG_BMH_END | ImBmh_D_IM_BMH_FLG_BMH_AXI_ERR)

#define ImBmh_IM_BMH_DSB()				Dd_ARM_Dsb_Pou()
#define ImBmh_IM_BMH_WAIT_USEC( usec )	Dd_ARM_Wait_ns( (usec * 1000) )

#ifdef CO_BMH_REG_TYPE_CHECK
#define ImBmh_IM_BMH_CHECK_REG_TYPE( dst, src )	(dst) = (src);
#else	// CO_BMH_REG_TYPE_CHECK
#define ImBmh_IM_BMH_CHECK_REG_TYPE( dst, src )
#endif	// CO_BMH_REG_TYPE_CHECK

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
typedef struct {
	ULONG lock;
	ULONG dummy[(64 / 4) - 1];
} TImBmhSpinLockVar;

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
static volatile ImBmhCallback S_G_IM_BMH_CALL_BACK_FUNC = NULL;

#if defined(ImBmh_CO_ACT_BMH_ICLK) || defined(ImBmh_CO_ACT_BMHCLOCK)
// Spin_lock.
static TImBmhSpinLockVar S_G_IM_BMH_SPIN_LOCK_TBL[2] __attribute__((section(".LOCK_SECTION"), aligned(64)));
#endif	// ImBmh_CO_ACT_BMH_ICLK || ImBmh_CO_ACT_BMHCLOCK

#ifdef ImBmh_CO_ACT_BMHCLOCK
static volatile UCHAR S_G_IM_BMH_CLK_CTRL_CNT[2] = {0,0};
#endif	// ImBmh_CO_ACT_BMHCLOCK
#ifdef ImBmh_CO_ACT_BMH_ICLK
static volatile UCHAR S_G_IM_BMH_ICLK_CTRL_CNT[2] = {0,0};
#endif	// ImBmh_CO_ACT_BMH_ICLK
/*----------------------------------------------------------------------*/
/* Local Method Definition												*/
/*----------------------------------------------------------------------*/
static VOID imBmhSetBmhinte( BYTE channel_no, const UCHAR onoff );
static INT32 imBmhStartCore( BYTE channel_no, const UCHAR sync, const INT32 wait_time );
static VOID imBmhOnBmhClk( BYTE channel_no );
static UCHAR imBmhIsAct( BYTE channel_no );
static VOID imBmhMhOffBmhClk( BYTE channel_no );
static VOID imBmhClearAxif( BYTE channel_no );
static VOID imBmhClearBmhf( BYTE channel_no );
/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
static void im_bmh_constructor(ImBmh *self)
{
	//ImBmhPrivate *priv = IM_BMH_GET_PRIVATE(self);
}

static void im_bmh_destructor(ImBmh *self)
{
	//ImBmhPrivate *priv = IM_BMH_GET_PRIVATE(self);
}

// Interrupt Enable/Disable control
static VOID imBmhSetBmhinte( BYTE channel_no, const UCHAR onoff )
{
	union io_bmh_bmhinte bmhinte;

	bmhinte.word = 0;
	bmhinte.bit.BMHE = onoff;
	bmhinte.bit.AXIE = onoff;

	IO_BMH[channel_no].BMHINTE.word = bmhinte.word;
}

// BMH Start CORE
static INT32 imBmhStartCore( BYTE channel_no, const UCHAR sync, const INT32 wait_time )
{
	INT32 ercd;
	UINT32 flg_ptn;
	union io_bmh_bmhtrg bmhtrg;
	ImBmhBmhre sram;

	// BMH End Flag disable
	DDIM_User_Clr_Flg( FID_IM_BMH, ~ImBmh_D_IM_BMH_WAIT_FLGPTN );

	imBmhOnBmhClk( channel_no );
	ImBmh_IM_BMH_DSB();

	sram.bmhre = 1;
	Im_BMH_Set_Bmhre( channel_no, &sram );

	bmhtrg.word = 0;
	bmhtrg.bit.BMHTRG = 1;
	IO_BMH[channel_no].BMHTRG.word = bmhtrg.word;

	ImBmh_IM_BMH_DSB();
	if( sync == ImBmh_D_IM_BMH_ASYNC ){
		return D_DDIM_OK;
	}

#ifdef CO_DEBUG_ON_PC
	if(( IO_BMH[channel_no].BMHINTFS.bit.__BMHF != 0 )
	|| ( IO_BMH[channel_no].BMHINTFS.bit.__AXIF != 0 )){
		Im_BMH_Int_Handler( channel_no );
	}
#endif	// CO_DEBUG_ON_PC

	// Wait for Process end with Sync
	ercd = Im_BMH_Wait_End( channel_no, &flg_ptn, wait_time );
	if( ercd != D_DDIM_OK ){
		return ercd;
	}
	if(( flg_ptn & ImBmh_D_IM_BMH_FLG_BMH_AXI_ERR ) != 0 ){
		return ImBmh_D_IM_BMH_AXI_ERR;
	}

	return D_DDIM_OK;
}

// Start BMH ICLK, BMHCLK
static VOID imBmhOnBmhClk( BYTE channel_no )
{
#if defined(ImBmh_CO_ACT_BMH_ICLK) || defined(ImBmh_CO_ACT_BMHCLOCK)
	Dd_ARM_Critical_Section_Start( S_G_IM_BMH_SPIN_LOCK_TBL[channel_no] );
#endif	// ImBmh_CO_ACT_BMH_ICLK || ImBmh_CO_ACT_BMHCLOCK

	if( channel_no == ImBmh1_E_IM_BMH_CHANNEL_00 ){
#ifdef ImBmh_CO_ACT_BMHCLOCK
		Dd_Top_Start_Clock( (UCHAR*)&S_G_IM_BMH_CLK_CTRL_CNT[0], &Dd_Top_Get_CLKSTOP14(), ~D_DD_TOP_BMH0CK_BIT );
#endif	// ImBmh_CO_ACT_BMHCLOCK
#ifdef ImBmh_CO_ACT_BMH_ICLK
		Dd_Top_Start_Clock( (UCHAR*)&S_G_IM_BMH_ICLK_CTRL_CNT[0], &Dd_Top_Get_CLKSTOP14(), ~D_DD_TOP_BMH0AX_BIT );
#endif	// ImBmh_CO_ACT_BMH_ICLK
	}

	if( channel_no == ImBmh1_E_IM_BMH_CHANNEL_01 ){
#ifdef ImBmh_CO_ACT_BMHCLOCK
		Dd_Top_Start_Clock( (UCHAR*)&S_G_IM_BMH_CLK_CTRL_CNT[1], &Dd_Top_Get_CLKSTOP13(), ~D_DD_TOP_BMH1CK_BIT );
#endif	// ImBmh_CO_ACT_BMHCLOCK
#ifdef ImBmh_CO_ACT_BMH_ICLK
		Dd_Top_Start_Clock( (UCHAR*)&S_G_IM_BMH_ICLK_CTRL_CNT[1], &Dd_Top_Get_CLKSTOP14(), ~D_DD_TOP_BMH1AX_BIT );
#endif	// ImBmh_CO_ACT_BMH_ICLK
	}

#if defined(ImBmh_CO_ACT_BMH_ICLK) || defined(ImBmh_CO_ACT_BMHCLOCK)
	Dd_ARM_Critical_Section_End( S_G_IM_BMH_SPIN_LOCK_TBL[channel_no] );
#endif	// ImBmh_CO_ACT_BMH_ICLK || ImBmh_CO_ACT_BMHCLOCK
}

/* Is Macro active
 */
static UCHAR imBmhIsAct( BYTE channel_no )
{
	union io_bmh_bmhtrg bmhtrg;

	bmhtrg.word = IO_BMH[channel_no].BMHTRG.word;

	if( bmhtrg.bit.BMHTRG == 3 ){			/* pgr0872 */
		return 1;
	}
	else{
		return 0;
	}
}

// Stop BMH ICLK, BMHCLK
static VOID imBmhMhOffBmhClk( BYTE channel_no )
{
#if defined(ImBmh_CO_ACT_BMH_ICLK) || defined(ImBmh_CO_ACT_BMHCLOCK)
	Dd_ARM_Critical_Section_Start( S_G_IM_BMH_SPIN_LOCK_TBL[channel_no] );
#endif	// ImBmh_CO_ACT_BMH_ICLK || ImBmh_CO_ACT_BMHCLOCK

	if( channel_no == ImBmh1_E_IM_BMH_CHANNEL_00 ){
#ifdef ImBmh_CO_ACT_BMH_ICLK
		Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_BMH_ICLK_CTRL_CNT[0], &Dd_Top_Get_CLKSTOP14(), D_DD_TOP_BMH0AX_BIT );
#endif	// ImBmh_CO_ACT_BMH_ICLK
#ifdef ImBmh_CO_ACT_BMHCLOCK
		Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_BMH_CLK_CTRL_CNT[0], &Dd_Top_Get_CLKSTOP14(), D_DD_TOP_BMH0CK_BIT );
#endif	// ImBmh_CO_ACT_BMHCLOCK
	}

	if( channel_no == ImBmh1_E_IM_BMH_CHANNEL_01 ){
#ifdef ImBmh_CO_ACT_BMH_ICLK
		Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_BMH_ICLK_CTRL_CNT[1], &Dd_Top_Get_CLKSTOP14(), D_DD_TOP_BMH1AX_BIT );
#endif	// ImBmh_CO_ACT_BMH_ICLK
#ifdef ImBmh_CO_ACT_BMHCLOCK
		Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_BMH_CLK_CTRL_CNT[1], &Dd_Top_Get_CLKSTOP13(), D_DD_TOP_BMH1CK_BIT );
#endif	// ImBmh_CO_ACT_BMHCLOCK
	}

#if defined(ImBmh_CO_ACT_BMH_ICLK) || defined(ImBmh_CO_ACT_BMHCLOCK)
	Dd_ARM_Critical_Section_End( S_G_IM_BMH_SPIN_LOCK_TBL[channel_no] );
#endif	// ImBmh_CO_ACT_BMH_ICLK || ImBmh_CO_ACT_BMHCLOCK
}

// AXIF Interrupt flag clear
static VOID imBmhClearAxif( BYTE channel_no )
{
#ifndef CO_DEBUG_ON_PC
	union io_bmh_bmhintfs bmhintfs;
#endif	// CO_DEBUG_ON_PC


#ifdef CO_DEBUG_ON_PC
	IO_BMH[channel_no].BMHINTFS.bit.__AXIF = 0;
#else	// !CO_DEBUG_ON_PC
	bmhintfs.word = 0;
	bmhintfs.bit.__AXIF = 1;

	IO_BMH[channel_no].BMHINTFS.word = bmhintfs.word;
#endif	// !CO_DEBUG_ON_PC
}

// BMHF Interrupt flag clear
static VOID imBmhClearBmhf( BYTE channel_no )
{
#ifndef CO_DEBUG_ON_PC
	union io_bmh_bmhintfs bmhintfs;
#endif	// CO_DEBUG_ON_PC

#ifdef CO_DEBUG_ON_PC
	IO_BMH[channel_no].BMHINTFS.bit.__BMHF = 0;
#else	// !CO_DEBUG_ON_PC
	bmhintfs.word = 0;
	bmhintfs.bit.__BMHF = 1;

	IO_BMH[channel_no].BMHINTFS.word = bmhintfs.word;
#endif	// !CO_DEBUG_ON_PC
}
/*----------------------------------------------------------------------*/
/* Global Function														*/
/*----------------------------------------------------------------------*/
/*
Set software reset and operating mode
*/
INT32 Im_BMH_Init( BYTE channel_no )
{
	union io_bmh_bmhsr bmhsr;

#ifdef CO_PARAM_CHECK
	if( channel_no >= ImBmh1_E_IM_BMH_CHANNEL_END ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Init. channel_no is abnormal.\n"));
		return ImBmh_D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
#endif	// CO_PARAM_CHECK
	imBmhOnBmhClk( channel_no );

	bmhsr.word = IO_BMH[channel_no].BMHSR.word;
	bmhsr.bit.SR = 1;
	IO_BMH[channel_no].BMHSR.word = bmhsr.word;

	ImBmh_IM_BMH_DSB();

	bmhsr.word = IO_BMH[channel_no].BMHSR.word;
	bmhsr.bit.SR = 0;
	IO_BMH[channel_no].BMHSR.word = bmhsr.word;

	ImBmh_IM_BMH_DSB();

	imBmhClearBmhf( channel_no );	// Interrupt clear
	imBmhClearAxif( channel_no );	// Interrupt clear
	imBmhSetBmhinte( channel_no, 1 );

	imBmhMhOffBmhClk( channel_no );
	ImBmh_IM_BMH_DSB();

	return D_DDIM_OK;
}

/*
BMH Start Sync
*/
INT32 Im_BMH_Start_Sync( BYTE channel_no, const INT32 wait_time )
{
#ifdef CO_PARAM_CHECK
	if( channel_no >= ImBmh1_E_IM_BMH_CHANNEL_END ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Start_Sync. channel_no is abnormal.\n"));
		return ImBmh_D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
#endif	// CO_PARAM_CHECK

	return imBmhStartCore( channel_no, ImBmh_D_IM_BMH_SYNC, wait_time );
}

/*
BMH Start Async
*/
INT32 Im_BMH_Start_Async( BYTE channel_no )
{
#ifdef CO_PARAM_CHECK
	if( channel_no >= ImBmh1_E_IM_BMH_CHANNEL_END ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Start_Async. channel_no is abnormal.\n"));
		return ImBmh_D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
#endif	// CO_PARAM_CHECK

	return imBmhStartCore( channel_no, ImBmh_D_IM_BMH_ASYNC, 0 );	// wait_time is dummy.
}

/*
BMH Wait End
*/
INT32 Im_BMH_Wait_End( BYTE channel_no, UINT32* const p_wait_factor, const INT32 wait_time )
{
	DDIM_USER_FLGPTN flgptn;
	DDIM_USER_FLGPTN waiptn;
	DDIM_USER_ER ercd;

#ifdef CO_PARAM_CHECK
	if( channel_no >= ImBmh1_E_IM_BMH_CHANNEL_END ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Wait_End. channel_no is abnormal.\n"));
		return ImBmh_D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
	if( p_wait_factor == NULL ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Wait_End. Parameter is NULL.\n"));
		return ImBmh_D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
#endif	// CO_PARAM_CHECK

	waiptn = ImBmh_D_IM_BMH_WAIT_FLGPTN;
	ercd = DDIM_User_Twai_Flg( FID_IM_BMH, waiptn, D_DDIM_USER_TWF_ORW, &flgptn, wait_time );
	if( ercd == D_DDIM_USER_E_TMOUT ){
		// A semaphore acquisition processing time out
		Ddim_Print(("Im_BMH_Wait_End() time out. ercd = %d\n", ercd ));
		return ImBmh_D_IM_BMH_SEM_TIMEOUT_ERR;
	}

	if( ercd != D_DDIM_USER_E_OK ){
		// A semaphore acquisition processing error
		Ddim_Print(("Im_BMH_Wait_End() system error. ercd = %d\n", ercd ));
		return ImBmh_D_IM_BMH_SEM_NG;
	}

	DDIM_User_Clr_Flg( FID_IM_BMH, ~flgptn );

	*p_wait_factor = (UINT32)flgptn;

	if(( flgptn & ImBmh_D_IM_BMH_AXI_ERR ) != 0 ){
		return ImBmh_D_IM_BMH_AXI_ERR;
	}

	return D_DDIM_OK;
}

/*
BMH Stop
*/
INT32 Im_BMH_Stop( BYTE channel_no )
{
	union io_bmh_bmhtrg bmhtrg;
	union io_bmh_bmhre bmhre;

#ifdef CO_PARAM_CHECK
	if( channel_no >= ImBmh1_E_IM_BMH_CHANNEL_END ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Stop. channel_no is abnormal.\n"));
		return ImBmh_D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
#endif	// CO_PARAM_CHECK

	bmhtrg.word = IO_BMH[channel_no].BMHTRG.word;

	if( bmhtrg.bit.BMHTRG == 3 ){			/* pgr0872 */
		bmhtrg.bit.BMHTRG = 0;
		IO_BMH[channel_no].BMHTRG.word = bmhtrg.word;
#ifdef CO_DEBUG_ON_PC
		IO_BMH[channel_no].BMHTRG.bit.BMHTRG = 2;
#endif	// CO_DEBUG_ON_PC
	}

	// Set SRAM Sleep
	bmhre.word = 0;
	bmhre.bit.BMHRE = 0;
	IO_BMH[channel_no].BMHRE.word = bmhre.word;

	// wait 1us
	ImBmh_IM_BMH_WAIT_USEC(ImBmh_D_IM_BMH_SRAM_WAIT_USEC);

	imBmhMhOffBmhClk( channel_no );
	ImBmh_IM_BMH_DSB();
//	Ddim_Print("I: [BMH] func disable.\n");

	return D_DDIM_OK;
}

/*
The semaphore of BMH is returned
*/
INT32 Im_BMH_Close( BYTE channel_no )
{
	DDIM_USER_ER ercd;

#ifdef CO_PARAM_CHECK
	if( channel_no >= ImBmh1_E_IM_BMH_CHANNEL_END ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Close. channel_no is abnormal.\n"));
		return ImBmh_D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
#endif	// CO_PARAM_CHECK

	imBmhMhOffBmhClk( channel_no );
	ImBmh_IM_BMH_DSB();

	ercd = DDIM_User_Sig_Sem( SID_IM_BMH( channel_no ) );				// sig_sem()

	if( ercd != D_DDIM_USER_E_OK ){
		// BMH processing error
		Ddim_Print(("I:Im_BMH_Close() Error.\n"));
		return ImBmh_D_IM_BMH_SEM_NG;
	}
	return D_DDIM_OK;
}

/*
Get BMH Control
*/
INT32 Im_BMH_Get_Ctrl( BYTE channel_no, ImBmhCtrl* const bmh_ctrl )
{
	union io_bmh_bmhmd bmhmd;
	union io_bmh_bmhprm bmhprm;

#ifdef CO_PARAM_CHECK
	if( channel_no >= ImBmh1_E_IM_BMH_CHANNEL_END ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Get_Ctrl. channel_no is abnormal.\n"));
		return ImBmh_D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
	if( bmh_ctrl == NULL ){
		// bmh_ctrl setting error
		Ddim_Assertion(("I:Im_BMH_Get_Ctrl. Parameter is NULL.\n"));
		return ImBmh_D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
#endif	// CO_PARAM_CHECK

	bmhmd.word = IO_BMH[channel_no].BMHMD.word;
	bmhprm.word = IO_BMH[channel_no].BMHPRM.word;

	bmh_ctrl->lselcnt = bmhmd.bit.LSELCNT;			/* pgr0872 */
	bmh_ctrl->rbs     = bmhmd.bit.RBS;				/* pgr0872 */
	bmh_ctrl->pshift  = bmhmd.bit.PSHIFT;			/* pgr0872 */
	bmh_ctrl->outmd   = bmhmd.bit.OUTMD;			/* pgr0872 */
	bmh_ctrl->lutmd   = bmhmd.bit.LUTMD;			/* pgr0872 */
	bmh_ctrl->offmd   = bmhmd.bit.OFFMD;			/* pgr0872 */
	bmh_ctrl->mode    = bmhmd.bit.MODE;				/* pgr0872 */

	bmh_ctrl->poffset = bmhprm.bit.POFFSET;			/* pgr0872 */
	bmh_ctrl->sadlv   = bmhprm.bit.SADLV;			/* pgr0872 */

	return D_DDIM_OK;
}

/*
BMH BMHRE set
*/
INT32 Im_BMH_Set_Bmhre( BYTE channel_no, const ImBmhBmhre* const sram )
{
	union io_bmh_bmhre bmhre;

#ifdef CO_PARAM_CHECK
	if( channel_no >= ImBmh1_E_IM_BMH_CHANNEL_END ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Set_Bmhre. channel_no is abnormal.\n"));
		return ImBmh_D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
	if( sram == NULL ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Set_Bmhre. Parameter is NULL.\n"));
		return ImBmh_D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
#endif	// CO_PARAM_CHECK

	if( imBmhIsAct( channel_no ) ){
		return ImBmh_D_IM_BMH_BUSY_NG;
	}

	bmhre.word = 0;

	bmhre.bit.BMHRE = sram->bmhre;

	IO_BMH[channel_no].BMHRE.word = bmhre.word;

	// wait 1us
	ImBmh_IM_BMH_WAIT_USEC( ImBmh_D_IM_BMH_SRAM_WAIT_USEC );

	return D_DDIM_OK;
}

/*
Get BMH BMHRE
*/
INT32 Im_BMH_Get_Bmhre( BYTE channel_no, ImBmhBmhre* const sram )
{
	union io_bmh_bmhre bmhre;

#ifdef CO_PARAM_CHECK
	if( channel_no >= ImBmh1_E_IM_BMH_CHANNEL_END ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Get_Bmhre. channel_no is abnormal.\n"));
		return ImBmh_D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
	if( sram == NULL ){
		// cnt setting error
		Ddim_Assertion(("I:Im_BMH_Get_Bmhre. Parameter is NULL.\n"));
		return ImBmh_D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
#endif	// CO_PARAM_CHECK

	bmhre.word = IO_BMH[channel_no].BMHRE.word;

	sram->bmhre = bmhre.bit.BMHRE;			/* pgr0872 */

	return D_DDIM_OK;
}

/*
Get BMH BMHINTFS-RSST
*/
INT32 Im_BMH_Get_Rsst( BYTE channel_no, ImBmhRsst* const rsst )
{
	union io_bmh_bmhintfs bmhintfs;

#ifdef CO_PARAM_CHECK
	if( channel_no >= ImBmh1_E_IM_BMH_CHANNEL_END ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Get_Rsst. channel_no is abnormal.\n"));
		return ImBmh_D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
	if( rsst == NULL ){
		// cnt setting error
		Ddim_Assertion(("I:Im_BMH_Get_Rsst. Parameter is NULL.\n"));
		return ImBmh_D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
#endif	// CO_PARAM_CHECK

	bmhintfs.word = IO_BMH[channel_no].BMHINTFS.word;

	rsst->rsst = bmhintfs.bit.__RSST;			/* pgr0872 */

	return D_DDIM_OK;
}

/*
BMH BMHCONT set
*/
INT32 Im_BMH_Set_Bmhcont( BYTE channel_no, const ImBmhBmhcont* const cont )
{
	union io_bmh_bmhcont bmhcont;

#ifdef CO_PARAM_CHECK
	if( channel_no >= ImBmh1_E_IM_BMH_CHANNEL_END ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Set_Bmhcont. channel_no is abnormal.\n"));
		return ImBmh_D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
	if( cont == NULL ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Set_Bmhcont. Parameter is NULL.\n"));
		return ImBmh_D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
#endif	// CO_PARAM_CHECK

	bmhcont.word = 0;

	bmhcont.bit.CONT = cont->cont;

	IO_BMH[channel_no].BMHCONT.word = bmhcont.word;

	return D_DDIM_OK;
}

/*
Get BMH BMHCONT
*/
INT32 Im_BMH_Get_Bmhcont( BYTE channel_no, ImBmhBmhcont* const cont )
{
	union io_bmh_bmhcont bmhcont;

#ifdef CO_PARAM_CHECK
	if( channel_no >= ImBmh1_E_IM_BMH_CHANNEL_END ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Get_Bmhcont. channel_no is abnormal.\n"));
		return ImBmh_D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
	if( cont == NULL ){
		// cnt setting error
		Ddim_Assertion(("I:Im_BMH_Get_Bmhcont. Parameter is NULL.\n"));
		return ImBmh_D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
#endif	// CO_PARAM_CHECK

	bmhcont.word = IO_BMH[channel_no].BMHCONT.word;

	cont->cont = bmhcont.bit.CONT;			/* pgr0872 */

	return D_DDIM_OK;
}

/*
BMH Control set AXI bus I/F Control
*/
INT32 Im_BMH_Set_Bmhaxi( BYTE channel_no, const ImBmhAxi* const axi_ctrl )
{
	union io_bmh_bmhaxictrl bmhaxictrl;

#ifdef CO_PARAM_CHECK
	if( channel_no >= ImBmh1_E_IM_BMH_CHANNEL_END ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Set_Bmhaxi. channel_no is abnormal.\n"));
		return ImBmh_D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
	if( axi_ctrl == NULL ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Set_Bmhaxi. Parameter is NULL.\n"));
		return ImBmh_D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
#endif	// CO_PARAM_CHECK

	bmhaxictrl.word = 0;

	bmhaxictrl.bit.AWPROT  = axi_ctrl->writeProtectionType;
	bmhaxictrl.bit.AWCACHE = axi_ctrl->writeCacheType;
	bmhaxictrl.bit.ARPROT  = axi_ctrl->readProtectionType;
	bmhaxictrl.bit.ARCACHE = axi_ctrl->readCacheType;

	IO_BMH[channel_no].BMHAXICTRL.word = bmhaxictrl.word;

	return D_DDIM_OK;
}

/*
BMH BMHHCNT set
*/
INT32 Im_BMH_Set_Bmhhcnt( BYTE channel_no, const ImBmhBmhhcnt* const cnt )
{
	union io_bmh_bmhhcnt bmhhcnt;

#ifdef CO_PARAM_CHECK
	if( channel_no >= ImBmh1_E_IM_BMH_CHANNEL_END ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Set_Bmhhcnt. channel_no is abnormal.\n"));
		return ImBmh_D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
	if( cnt == NULL ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Set_Bmhhcnt. Parameter is NULL.\n"));
		return ImBmh_D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
#endif	// CO_PARAM_CHECK

	if( imBmhIsAct( channel_no ) ){
		return ImBmh_D_IM_BMH_BUSY_NG;
	}

	bmhhcnt.word = 0;

	bmhhcnt.bit.HCNT = cnt->hcnt;
	bmhhcnt.bit.RCNT = cnt->rcnt;

	IO_BMH[channel_no].BMHHCNT.word = bmhhcnt.word;

	return D_DDIM_OK;
}

/*
BMH BMHSAD_WR set
*/
INT32 Im_BMH_Set_Bmhsad_wr( BYTE channel_no, const ImBmhBmhsadWr* const sadWr )
{
	union io_bmh_bmhsad_wr bmhsad_wr;

#ifdef CO_PARAM_CHECK
	if( channel_no >= ImBmh1_E_IM_BMH_CHANNEL_END ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Set_Bmhsad_wr. channel_no is abnormal.\n"));
		return ImBmh_D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
	if( sadWr == NULL ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Set_Bmhsad_wr. Parameter is NULL.\n"));
		return ImBmh_D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
#endif	// CO_PARAM_CHECK

	if( imBmhIsAct( channel_no ) ){
		return ImBmh_D_IM_BMH_BUSY_NG;
	}

	bmhsad_wr.word = 0;

	bmhsad_wr.bit.SAD_WR = sadWr->sadWr;

	IO_BMH[channel_no].BMHSAD_WR.word = bmhsad_wr.word;

	return D_DDIM_OK;
}

/*
BMH LUT set
*/
INT32 Im_BMH_Set_Lut( BYTE channel_no, const ImBmhLut* const lut_data )
{
	ULONG count;
	typedef union {
		unsigned long word;
		struct {
		unsigned long	LUT_0	:12;
		unsigned long			:4;
		unsigned long	LUT_1	:12;
		unsigned long			:4;
		} bit;
	} u_bmh_lut;

	u_bmh_lut lut;

#ifdef CO_PARAM_CHECK
	if( channel_no >= ImBmh1_E_IM_BMH_CHANNEL_END ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Set_Lut. channel_no is abnormal.\n"));
		return ImBmh_D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
	if( lut_data == NULL ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Set_Lut. Parameter is NULL.\n"));
		return ImBmh_D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
#endif	// CO_PARAM_CHECK

	if( imBmhIsAct( channel_no ) ){
		return ImBmh_D_IM_BMH_BUSY_NG;
	}

	lut.word = 0;

	for( count = 0; count < 1024; count++ ){
		lut.bit.LUT_0 = lut_data->lut[count * 2];
		lut.bit.LUT_1 = lut_data->lut[count * 2 + 1];
		IO_BMH[channel_no].LUT.word[count] = lut.word;
	}

	return D_DDIM_OK;
}

/*
BMH Dma mode control
*/
INT32 Im_BMH_Ctrl_Dma( BYTE channel_no, const ImBmhCtrlDma* const bmh_ctrl_dma )
{
	union io_bmh_bmhdma    bmhdma;
	union io_bmh_bmhghsize bmhghsize;
	union io_bmh_bmhhsize  bmhhsize;
	union io_bmh_bmhvsize  bmhvsize;
	union io_bmh_bmhcurad  bmhcurad;
	union io_bmh_bmhrefad  bmhrefad;
	union io_bmh_bmhsadad  bmhsadad;
	union io_bmh_bmhsadgh  bmhsadgh;

#ifdef CO_PARAM_CHECK
	if( channel_no >= ImBmh1_E_IM_BMH_CHANNEL_END ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Ctrl_Dma. channel_no is abnormal.\n"));
		return ImBmh_D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
	if( bmh_ctrl_dma == NULL ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Ctrl_Dma. Parameter is NULL.\n"));
		return ImBmh_D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
#endif	// CO_PARAM_CHECK

	if( imBmhIsAct( channel_no ) ){
		return ImBmh_D_IM_BMH_BUSY_NG;
	}

	bmhdma.word    = 0;
	bmhghsize.word = 0;
	bmhhsize.word  = 0;
	bmhvsize.word  = 0;
	bmhcurad.word  = 0;
	bmhrefad.word  = 0;
	bmhsadad.word  = 0;
	bmhsadgh.word  = 0;

	bmhdma.bit.DMAMD         = bmh_ctrl_dma->dmamd;
	bmhghsize.bit.GHSIZE_CUR = bmh_ctrl_dma->ghsizeCur;
	bmhghsize.bit.GHSIZE_REF = bmh_ctrl_dma->ghsizeRef;
	bmhhsize.bit.HSIZE_REF   = bmh_ctrl_dma->hsizeRef;
	bmhvsize.bit.VSIZE_REF   = bmh_ctrl_dma->vsizeRef;
	bmhcurad.bit.CURSTAD     = bmh_ctrl_dma->curstad;
	bmhrefad.bit.REFSTAD     = bmh_ctrl_dma->refstad;
	bmhsadad.bit.SADSTAD     = bmh_ctrl_dma->sadstad;
	bmhsadgh.bit.SADGHSIZE   = bmh_ctrl_dma->sadghsize;

	IO_BMH[channel_no].BMHDMA.word    = bmhdma.word;
	IO_BMH[channel_no].BMHGHSIZE.word = bmhghsize.word;
	IO_BMH[channel_no].BMHHSIZE.word  = bmhhsize.word;
	IO_BMH[channel_no].BMHVSIZE.word  = bmhvsize.word;
	IO_BMH[channel_no].BMHCURAD.word  = bmhcurad.word;
	IO_BMH[channel_no].BMHREFAD.word  = bmhrefad.word;
	IO_BMH[channel_no].BMHSADAD.word  = bmhsadad.word;
	IO_BMH[channel_no].BMHSADGH.word  = bmhsadgh.word;

	return D_DDIM_OK;
}

/*
BMH Macro handler
*/
VOID Im_BMH_Int_Handler( BYTE channel_no )
{
	DDIM_USER_FLGPTN flg;
	union io_bmh_bmhintfs bmhintfs;
	union io_bmh_bmhinte bmhinte;

#ifdef CO_PARAM_CHECK
	if( channel_no >= ImBmh1_E_IM_BMH_CHANNEL_END ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Int_Handler. channel_no is abnormal.\n"));
		return;
	}
#endif	// CO_PARAM_CHECK

	bmhinte.word = IO_BMH[channel_no].BMHINTE.word;
	bmhintfs.word = IO_BMH[channel_no].BMHINTFS.word;

	if(( bmhinte.bit.AXIE != 0 ) && ( bmhintfs.bit.__AXIF != 0 )){		/* pgr0872 */
		// clear interrupt end register
		imBmhClearAxif( channel_no );

		flg = ImBmh_D_IM_BMH_FLG_BMH_AXI_ERR;

		// Set End Flag
		DDIM_User_Set_Flg( FID_IM_BMH, ImBmh_D_IM_BMH_FLG_BMH_AXI_ERR );

		// User Function Check
		if( S_G_IM_BMH_CALL_BACK_FUNC != NULL ){
			S_G_IM_BMH_CALL_BACK_FUNC( flg );
		}
	}

	if(( bmhinte.bit.BMHE != 0 ) && ( bmhintfs.bit.__BMHF != 0 )){		/* pgr0872 */
		// clear interrupt end register
		imBmhClearBmhf( channel_no );

		imBmhMhOffBmhClk( channel_no );

		flg = ImBmh_D_IM_BMH_FLG_BMH_END;

		// Set End Flag
		(VOID)DDIM_User_Set_Flg( FID_IM_BMH, flg );

		// User Function Check
		if( S_G_IM_BMH_CALL_BACK_FUNC != NULL ){
			S_G_IM_BMH_CALL_BACK_FUNC( flg );
		}
	}

	ImBmh_IM_BMH_DSB();
}

/*
BMH Control
*/
INT32 Im_BMH_Ctrl( BYTE channel_no, const ImBmhCtrl* const bmh_ctrl )
{
	union io_bmh_bmhmd bmhmd;
	union io_bmh_bmhprm bmhprm;

#ifdef CO_PARAM_CHECK
	if( channel_no >= ImBmh1_E_IM_BMH_CHANNEL_END ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Ctrl. channel_no is abnormal.\n"));
		return ImBmh_D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
	if( bmh_ctrl == NULL ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Ctrl. Parameter is NULL.\n"));
		return ImBmh_D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
#endif	// CO_PARAM_CHECK

	if( imBmhIsAct( channel_no ) ){
		return ImBmh_D_IM_BMH_BUSY_NG;
	}

	bmhmd.word = 0;
	bmhprm.word = 0;

	bmhmd.bit.LSELCNT  = bmh_ctrl->lselcnt;
	bmhmd.bit.RBS      = bmh_ctrl->rbs;
	bmhmd.bit.PSHIFT   = bmh_ctrl->pshift;
	bmhmd.bit.OUTMD    = bmh_ctrl->outmd;
	bmhmd.bit.LUTMD    = bmh_ctrl->lutmd;
	bmhmd.bit.OFFMD    = bmh_ctrl->offmd;
	bmhmd.bit.MODE     = bmh_ctrl->mode;

	bmhprm.bit.POFFSET = bmh_ctrl->poffset;
	bmhprm.bit.SADLV   = bmh_ctrl->sadlv;

	IO_BMH[channel_no].BMHMD.word = bmhmd.word;
	IO_BMH[channel_no].BMHPRM.word = bmhprm.word;

	S_G_IM_BMH_CALL_BACK_FUNC = bmh_ctrl->pCallBack;

	return D_DDIM_OK;
}

#ifdef CO_BMH_DEBUG
VOID Im_BMH_Print_ClockStatus( VOID )
{
#ifdef ImBmh_CO_ACT_BMH_ICLK
	Ddim_Print(( "CLKSTOP: AX=%u\n", Dd_Top_Get_CLKSTOP14_BMHAX() ));
#endif	// ImBmh_CO_ACT_BMH_ICLK
#ifdef CO_ACT_BMHCLK
	Ddim_Print(( "CLKSTOP: CK=%u\n", Dd_Top_Get_CLKSTOP14_BMHCK() ));
#endif	// CO_ACT_BMHCLK
#ifdef ImBmh_CO_ACT_BMH_ICLK
	Ddim_Print(( "CLKCNT: AX=%u\n", S_G_IM_BMH_ICLK_CTRL_CNT ));
#endif	// ImBmh_CO_ACT_BMH_ICLK
#ifdef CO_ACT_BMHCLK
	Ddim_Print(( "CLKCNT: CK=%u\n", S_G_IM_BMH_CLK_CTRL_CNT ));
#endif	// CO_ACT_BMHCLK
}
#endif	// CO_BMH_DEBUG

ImBmh *im_bmh_new(void)
{
	ImBmh* self = k_object_new_with_private(IM_TYPE_BMH,sizeof(ImBmhPrivate));
	return self;
}
