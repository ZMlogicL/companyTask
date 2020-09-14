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
#include "jdsme.h"
#include "imme.h"
#include "dd_top.h"
#include "ddim_user_custom.h"
#include <string.h>

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
//#define CO_ME_REG_TYPE_CHECK
//#define CO_ME_DEBUG_PRINT		// Debug.

// Data Synchronization Barrier.
#define ImMe_IM_ME_DSB()						Dd_ARM_Dsb_Pou()

// Wait usec.
#define ImMe_IM_ME_WAIT_USEC( usec )			Dd_ARM_Wait_ns( ( usec * 1000 ) )

// The structure type matching check.
#ifdef CO_ME_REG_TYPE_CHECK
#define ImMe_IM_ME_CHECK_REG_TYPE( dst, src )	( dst ) = ( src );
#else
#define ImMe_IM_ME_CHECK_REG_TYPE( dst, src )
#endif

// Set signed register.
#define ImMe_IM_ME_SET_REG_SIGNED( reg, type, member, val )		\
		{ \
			type work = { .word = 0UL }; \
			work.bit.member = (val); \
			(reg).bit.member = work.bit.member; \
			ImMe_IM_ME_CHECK_REG_TYPE( work, (reg) ); \
		}

// Set signed register (multi array).
#define ImMe_IM_ME_SET_REG_SIGNED_A( reg, type, member, val )	\
		{ \
			type work = { .word[0] = 0xFFFFFFFFUL }; \
			work.bit.member = (val); \
			(reg).bit.member = work.bit.member; \
			ImMe_IM_ME_CHECK_REG_TYPE( work, (reg) ); \
		}

// Get signed register.
#define ImMe_IM_ME_GET_REG_SIGNED( val, reg, type, member )		\
		{ \
			type work = { .word = 0UL }; \
			work.bit.member = -1L; \
			if( ((work.bit.member) == 0xFFFFFFFFUL) || ((reg.bit.member) <= ((work.bit.member) /2)) ) { \
				(val) = reg.bit.member; \
			} \
			else { \
				(val) = -(work.bit.member - reg.bit.member +1); \
			} \
			ImMe_IM_ME_CHECK_REG_TYPE( (reg), work );	/* The structure type matching check. */ \
		}

// Get signed register (multi array).
#define ImMe_IM_ME_GET_REG_SIGNED_A( val, reg, type, member )	\
		{ \
			type work = { .word[0] = 0UL }; \
			work.bit.member = -1L; \
			if( ((work.bit.member) == 0xFFFFFFFFUL) || ((reg.bit.member) <= ((work.bit.member) /2)) ) { \
				(val) = reg.bit.member; \
			} \
			else { \
				(val) = -(work.bit.member - reg.bit.member +1); \
			} \
			ImMe_IM_ME_CHECK_REG_TYPE( (reg), work );	/* The structure type matching check. */ \
		}

#ifdef CO_PARAM_CHECK
#define ImMe_IM_ME_CHECK_WAIT_TIME( wait_time )	(( wait_time >= D_DDIM_USER_SEM_WAIT_FEVR ) ? TRUE : FALSE)
#endif	// CO_PARAM_CHECK

#if defined(CO_ACT_CLOCK) || defined(CO_ACT_IMAGE_CLOCK)
#define	ImMe_CO_ACT_ME_CLOCK
#endif

#if defined(CO_ACT_ICLOCK) || defined(CO_ACT_IMAGE_ICLOCK)
#define	ImMe_CO_ACT_ME_ICLOCK
#endif

#if defined(CO_ACT_PCLOCK) || defined(CO_ACT_IMAGE_PCLOCK)
#define	ImMe_CO_ACT_ME_PCLOCK
#endif

// Software reset.
#define	ImMe_D_IM_ME_SR_RELEASE			(0)				// Software reset release.
#define	ImMe_D_IM_ME_SR_RESET			(1)				// Software reset state.

// ME1 state.
#define	ImMe_D_IM_ME_ME1_STATE_STOP		(0)				// Stop  state.
#define	ImMe_D_IM_ME_ME1_STATE_START		(2)				// Start state.
#define	ImMe_D_IM_ME_ME1_STATE_PAUSE		(4)				// Pause state.

// ME1 data prefetch state.
#define	ImMe_D_IM_ME_STR_STOP			(0)				// Stop  state.
#define	ImMe_D_IM_ME_STR_START			(1)				// Start state.

// Wait time.
#define ImMe_D_IM_ME_WAIT_END_TIME		(100)			// ME wait end time.

// Interrupt flag.
#define ImMe_D_IM_ME_FLG_END				(0x00000001)	// End.

// Mutex.
#define ImMe_IM_ME_LOCK()		Dd_ARM_Critical_Section_Start( S_G_IM_ME_SPIN_LOCK )
#define ImMe_IM_ME_UNLOCK()		Dd_ARM_Critical_Section_End( S_G_IM_ME_SPIN_LOCK )

K_TYPE_DEFINE_WITH_PRIVATE(ImMe, im_me);
#define IM_ME_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImMePrivate, IM_TYPE_ME))
/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
struct _ImMePrivate
{
	int a;
};

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
#ifdef ImMe_CO_ACT_ME_CLOCK
static volatile UCHAR				S_G_IM_ME_CLK_COUNTER		= 0;
#endif

#ifdef ImMe_CO_ACT_ME_ICLOCK
static volatile UCHAR				S_G_IM_ME_XCLK_COUNTER		= 0;
#endif

#ifdef ImMe_CO_ACT_ME_PCLOCK
static volatile UCHAR				S_G_IM_ME_PCLK_COUNTER		= 0;
#endif

static volatile ULONG				S_G_IM_ME_AXI_ERR			= ImMe_D_IM_ME_AXI_NORMAL_END;
static volatile ImMeCallback	S_G_IM_ME_CALL_BACK_FUNC	= NULL;
static volatile ImMeCtrl		S_G_IM_ME_CTRL;
static volatile UCHAR				S_G_IM_ME_INT_CNT			= 0;
static volatile ULONG				S_G_IM_ME_SPIN_LOCK __attribute__((section(".LOCK_SECTION"), aligned(64)));

/*----------------------------------------------------------------------*/
/* Local Method Definition												*/
/*----------------------------------------------------------------------*/
static VOID imMeOnClk( VOID );
static VOID imMeOffClk( VOID );
static VOID imMeOnXclk( VOID );
static  VOID imMeOffXclk( VOID );
static VOID imMeOnPclk( VOID );
static VOID imMeOffPclk( VOID );
/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/
void im_me_constructor(ImMe *self)
{
	//ImMePrivate *priv = IM_ME_GET_PRIVATE(self);
}

void im_me_destructor(ImMe *self)
{
	//ImMePrivate *priv = IM_ME_GET_PRIVATE(self);
}

static VOID imMeOnClk( VOID )
{
#ifdef ImMe_CO_ACT_ME_CLOCK
	Dd_Top_Start_Clock( (UCHAR*)&S_G_IM_ME_CLK_COUNTER, &Dd_Top_Get_CLKSTOP7(), ~D_DD_TOP_MECK_BIT );
#endif
}

static VOID imMeOffClk( VOID )
{
#ifdef ImMe_CO_ACT_ME_CLOCK
	Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_ME_CLK_COUNTER, &Dd_Top_Get_CLKSTOP7(), D_DD_TOP_MECK_BIT );
#endif
}

static VOID imMeOnXclk( VOID )
{
#ifdef ImMe_CO_ACT_ME_ICLOCK
	Dd_Top_Start_Clock( (UCHAR*)&S_G_IM_ME_XCLK_COUNTER, &Dd_Top_Get_CLKSTOP7(), ~D_DD_TOP_MEAX_BIT );
#endif
}

static  VOID imMeOffXclk( VOID )
{
#ifdef ImMe_CO_ACT_ME_ICLOCK
	Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_ME_XCLK_COUNTER, &Dd_Top_Get_CLKSTOP7(), D_DD_TOP_MEAX_BIT );
#endif
}

/**
PCLK ON for ME.<br>
@param[in]		None.
@retval			None.
*/
static VOID imMeOnPclk( VOID )
{
#ifdef ImMe_CO_ACT_ME_PCLOCK
	Dd_Top_Start_Clock( (UCHAR*)&S_G_IM_ME_PCLK_COUNTER, &Dd_Top_Get_CLKSTOP7(), ~D_DD_TOP_MEAP_BIT );
#endif
}

/**
PCLK OFF for ME.<br>
@param[in]		None.
@retval			None.
*/
static VOID imMeOffPclk( VOID )
{
#ifdef ImMe_CO_ACT_ME_PCLOCK
	Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_ME_PCLK_COUNTER, &Dd_Top_Get_CLKSTOP7(), D_DD_TOP_MEAP_BIT );
#endif
}
/*----------------------------------------------------------------------*/
/* Global Function														*/
/*----------------------------------------------------------------------*/
/**
ME initialize.<br>
@retval			D_DDIM_OK					Success.
*/
INT32 Im_ME_Init( VOID )
{
	imMeOnPclk();
	imMeOnXclk();
	imMeOnClk();
	ImMe_IM_ME_DSB();

	S_G_IM_ME_INT_CNT = 0;

	memset( (VOID*)&S_G_IM_ME_CTRL, 0, sizeof(ImMeCtrl) );

	// Software reset (APBBRG).
	IO_ME.SRESET.bit.CMDR	= ImMe_D_IM_ME_SR_RESET;

	// Software reset release.
	IO_ME.SRESET.bit.CMDR	= ImMe_D_IM_ME_SR_RELEASE;

	ImMe_IM_ME_DSB();

	for ( int i = 0; i < ImMe_E_IM_ME_PPNUM_MAX; i++ ) {

		// Software reset (PTCONT/PABT).
		IO_ME.PME[ i ].CR.bit.CMDR				= ImMe_D_IM_ME_SR_RESET;

		// Software reset release.
		IO_ME.PME[ i ].CR.bit.CMDR				= ImMe_D_IM_ME_SR_RELEASE;

		ImMe_IM_ME_DSB();

		// Clock enable.
		IO_ME.PME[ i ].PTCC.bit.CKA				= ImMe_D_IM_ME_ENABLE;		// PTCONT (Clock on).
		IO_ME.PME[ i ].PACC.bit.PABT_CKA		= ImMe_D_IM_ME_ENABLE;		// PABT   (Clock on).
		IO_ME.PME[ i ].PACC.bit.CKM				= ImMe_D_IM_ME_DISABLE;		// PABT   (Normal mode).

		// Interrupt enable.
		IO_ME.PME[ i ].IRQE.bit.IRQE0			= ImMe_D_IM_ME_DISABLE;
		IO_ME.PME[ i ].IRQE.bit.IRQE1			= ImMe_D_IM_ME_DISABLE;
		IO_ME.PME[ i ].IRQE.bit.IRQE2			= ImMe_D_IM_ME_DISABLE;
		IO_ME.PME[ i ].IRQE.bit.IRQE3			= ImMe_D_IM_ME_DISABLE;
		IO_ME.PME[ i ].IRQE.bit.IRQE4			= ImMe_D_IM_ME_DISABLE;
		IO_ME.PME[ i ].IRQE.bit.IRQE5			= ImMe_D_IM_ME_DISABLE;
		IO_ME.PME[ i ].IRQE.bit.IRQE6			= ImMe_D_IM_ME_ENABLE;
		IO_ME.PME[ i ].IRQE.bit.IRQE7			= ImMe_D_IM_ME_DISABLE;
		IO_ME.PME[ i ].IRQE.bit.IRQE8			= ImMe_D_IM_ME_DISABLE;

		// Software reset (PME/SRST).
		IO_ME.PME[ i ].SRST.bit.SRST			= ImMe_D_IM_ME_SR_RESET;

		// Software reset release.
		IO_ME.PME[ i ].SRST.bit.SRST			= ImMe_D_IM_ME_SR_RELEASE;

		// Software reset (PME/CMDRST).
		IO_ME.PME[ i ].PMBUF_CTL.bit.CMDRST		= ImMe_D_IM_ME_SR_RESET;

		// Software reset release.
		IO_ME.PME[ i ].PMBUF_CTL.bit.CMDRST		= ImMe_D_IM_ME_SR_RELEASE;

		// PMBUF through.
		IO_ME.PME[ i ].PMBUF_CTL.bit.THRU		= ImMe_D_IM_ME_OFF;

		ImMe_IM_ME_DSB();

		// Clock enable.
		IO_ME.PME[ i ].ACTIVE.bit.CLKACT		= ImMe_D_IM_ME_ENABLE;		// PME (Clock on).
		IO_ME.PME[ i ].ACTIVE.bit.CKEN_MODE0	= ImMe_D_IM_ME_DISABLE;		// M6CLK_PM0 (Normal mode).
		IO_ME.PME[ i ].ACTIVE.bit.CKEN_MODE1	= ImMe_D_IM_ME_DISABLE;		// M6CLK_PM0 (Normal mode).

		ImMe_IM_ME_DSB();
	}

	// Software reset (RMCIF).
	IO_ME.CMD_RST.bit.CMD_RST		= ImMe_D_IM_ME_SR_RESET;

	// Software reset release.
	IO_ME.CMD_RST.bit.CMD_RST		= ImMe_D_IM_ME_SR_RELEASE;

	ImMe_IM_ME_DSB();

	// Clock enable.
	IO_ME.CLKENB1.bit.M6_PFM_EN		= ImMe_D_IM_ME_DISABLE;					// M6CLK_PFM (Normal mode).
	IO_ME.CLKENB4.bit.M6_P4M_EN		= ImMe_D_IM_ME_DISABLE;					// M6CLK_P4M (Normal mode).
	IO_ME.CLKACT1.bit.M6_PFM_ACT	= ImMe_D_IM_ME_ENABLE;					// M6CLK_PFM (Clock on : hard autonomous control).
	IO_ME.CLKACT4.bit.M6_P4M_ACT	= ImMe_D_IM_ME_ENABLE;					// M6CLK_P4M (Clock on : hard autonomous control).

	imMeOffClk();
	imMeOffXclk();
	imMeOffPclk();
	ImMe_IM_ME_DSB();

	return D_DDIM_OK;
}

/**
The semaphore of ME is acquired.<br>
@param[in]		wait_time					Time-out period.<br>
@retval			D_DDIM_OK					Success.
@retval			ImMe_D_IM_ME_INPUT_PARAM_ERROR	Parameter error.
@retval			ImMe_D_IM_ME_SEM_NG				Semaphore acquisition NG.
*/
INT32 Im_ME_Open( const INT32 wait_time )
{
	DDIM_USER_ER	ercd;

#ifdef CO_PARAM_CHECK
	if ( ImMe_IM_ME_CHECK_WAIT_TIME( wait_time ) == FALSE ) {
		Ddim_Assertion(("Im_ME_Open parameter error\n"));
		return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
	}
#endif

	if ( D_DDIM_USER_SEM_WAIT_POL == wait_time ) {
		ercd = DDIM_User_Pol_Sem( SID_IM_ME );
	}
	else {
		ercd = DDIM_User_Twai_Sem( SID_IM_ME, (DDIM_USER_TMO)wait_time );
	}

	if ( D_DDIM_USER_E_OK == ercd ) {
		return D_DDIM_OK;
	}
	else {
		return ImMe_D_IM_ME_SEM_NG;
	}
}

/**
The semaphore of ME is returned.<br>
@retval			D_DDIM_OK					Success.
@retval			ImMe_D_IM_ME_SEM_NG				Semaphore acquisition NG.
*/
INT32 Im_ME_Close( VOID )
{
	DDIM_USER_ER	ercd;

	ercd = DDIM_User_Sig_Sem( SID_IM_ME );

	if ( D_DDIM_USER_E_OK == ercd ) {
		return D_DDIM_OK;
	}
	else {
		return ImMe_D_IM_ME_SEM_NG;
	}
}

/**
ME control parameters set.<br>
@param[in]		me_ctrl							ME control parameters. See @ref ImMeCtrl.<br>
@retval			D_DDIM_OK						Success.
@retval			ImMe_D_IM_ME_INPUT_PARAM_ERROR		Parameter error.
*/
INT32 Im_ME_Ctrl( const ImMeCtrl* const me_ctrl )
{
#ifdef CO_PARAM_CHECK
	if ( me_ctrl == NULL ) {
		Ddim_Assertion(("Im_ME_Ctrl() error. me_ctrl = NULL.\n"));
		return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
	}
	if ( me_ctrl->apbbrg.intMode > ImMe_D_IM_ME_INTMODE_LOGICAL_OR ) {
		Ddim_Assertion(("Im_ME_Ctrl() error. int_mod is invalid.\n"));
		return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
	}
	for ( int i = 0; i < ImMe_E_IM_ME_PPNUM_MAX; i++ ) {
		if ( me_ctrl->apbbrg.ppEnable[ i ] > ImMe_D_IM_ME_ENABLE ) {
			Ddim_Assertion(("Im_ME_Ctrl() error. ppEnable[ %d ] is invalid.\n", i));
			return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
		}
		if ( me_ctrl->pme[ i ].inputMode > ImMe_D_IM_ME_INPUTMODE_PROGRESSIVE ) {
			Ddim_Assertion(("Im_ME_Ctrl() error. inputMode[ %d ] is invalid.\n", i));
			return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
		}
		if ( me_ctrl->pme[ i ].refTxb > ImMe_D_IM_ME_REFTXB_BOTTOM ) {
			Ddim_Assertion(("Im_ME_Ctrl() error. refTxb[ %d ] is invalid.\n", i));
			return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
		}
		if ( me_ctrl->pme[ i ].outLimit > ImMe_D_IM_ME_OUTLIMIT_TOP ) {
			Ddim_Assertion(("Im_ME_Ctrl() error. outLimit[ %d ] is invalid.\n", i));
			return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
		}
		if ( ( me_ctrl->pme[ i ].bankNum == 0 ) ||
			 ( me_ctrl->pme[ i ].bankNum > ImMe_D_IM_ME_BANKNUM_4 ) ) {
			Ddim_Assertion(("Im_ME_Ctrl() error. bankNum[ %d ] is invalid.\n", i));
			return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
		}
		for ( int j = 0; j < ImMe_E_IM_ME_BANKNUM_MAX; j++ ) {
			if ( me_ctrl->pme[ i ].m1orgMode[ j ].direction > ImMe_D_IM_ME_M1ORG_DIR_BWD ) {
				Ddim_Assertion(("Im_ME_Ctrl() error. m1orgMode[ %d ][ %d ].direction is invalid.\n", i, j));
				return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
			}
			if ( me_ctrl->pme[ i ].m1orgMode[ j ].parity > ImMe_D_IM_ME_M1ORG_PARI_BOTTOM ) {
				Ddim_Assertion(("Im_ME_Ctrl() error. m1orgMode[ %d ][ %d ].parity is invalid.\n", i, j));
				return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
			}
			if ( me_ctrl->pme[ i ].m1orgMode[ j ].readMode > ImMe_D_IM_ME_M1ORG_READ_SDRAM ) {
				Ddim_Assertion(("Im_ME_Ctrl() error. m1orgMode[ %d ][ %d ].readMode is invalid.\n", i, j));
				return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
			}
			if ( me_ctrl->pme[ i ].m1orgMode[ j ].sad0Mode > ImMe_D_IM_ME_M1ORG_SAD_MIN1 ) {
				Ddim_Assertion(("Im_ME_Ctrl() error. m1orgMode[ %d ][ %d ].sad0Mode is invalid.\n", i, j));
				return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
			}
			if ( me_ctrl->pme[ i ].m1orgMode[ j ].sad1Mode > ImMe_D_IM_ME_M1ORG_SAD_MIN1 ) {
				Ddim_Assertion(("Im_ME_Ctrl() error. m1orgMode[ %d ][ %d ].sad1Mode is invalid.\n", i, j));
				return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
			}
			if ( me_ctrl->pme[ i ].m1orgMode[ j ].vecMode > ImMe_D_IM_ME_M1ORG_VECM_WRITE1 ) {
				Ddim_Assertion(("Im_ME_Ctrl() error. m1orgMode[ %d ][ %d ].vecMode is invalid.\n", i, j));
				return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
			}
			if ( ( me_ctrl->pme[ i ].m1orgMode[ j ].vecSelect != ImMe_D_IM_ME_M1ORG_VECS_SAVE  ) &&
				 ( me_ctrl->pme[ i ].m1orgMode[ j ].vecSelect != ImMe_D_IM_ME_M1ORG_VECS_COPY0 ) &&
				 ( me_ctrl->pme[ i ].m1orgMode[ j ].vecSelect != ImMe_D_IM_ME_M1ORG_VECS_COPY1 ) ) {
				Ddim_Assertion(("Im_ME_Ctrl() error. m1orgMode[ %d ][ %d ].vecSelect is invalid.\n", i, j));
				return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
			}
			if ( me_ctrl->pme[ i ].m1orgMode[ j ].picType > ImMe_D_IM_ME_M1ORG_PICT_I ) {
				Ddim_Assertion(("Im_ME_Ctrl() error. m1orgMode[ %d ][ %d ].picType is invalid.\n", i, j));
				return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
			}
		}
		if ( me_ctrl->pme[ i ].m1correct.frontKy > ImMe_D_IM_ME_M1CRCT_KY_MAX ) {
			Ddim_Assertion(("Im_ME_Ctrl() error. m1correct.frontKy[ %d ] is invalid.\n", i));
			return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
		}
		if ( me_ctrl->pme[ i ].m1correct.backKy > ImMe_D_IM_ME_M1CRCT_KY_MAX ) {
			Ddim_Assertion(("Im_ME_Ctrl() error. m1correct.backKy[ %d ] is invalid.\n", i));
			return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
		}
		if ( me_ctrl->pme[ i ].m1correct.frontKx > ImMe_D_IM_ME_M1CRCT_KX_MAX ) {
			Ddim_Assertion(("Im_ME_Ctrl() error. m1correct.frontKx[ %d ] is invalid.\n", i));
			return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
		}
		if ( me_ctrl->pme[ i ].m1correct.backKx > ImMe_D_IM_ME_M1CRCT_KX_MAX ) {
			Ddim_Assertion(("Im_ME_Ctrl() error. m1correct.backKx[ %d ] is invalid.\n", i));
			return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
		}
		if ( me_ctrl->pme[ i ].m1splt.mode > ImMe_D_IM_ME_SPLITMODE_VERTICAL ) {
			Ddim_Assertion(("Im_ME_Ctrl() error. m1splt.mode[ %d ] is invalid.\n", i));
			return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
		}
		if ( me_ctrl->pme[ i ].m1skip > ImMe_D_IM_ME_ON ) {
			Ddim_Assertion(("Im_ME_Ctrl() error. m1skip[ %d ] is invalid.\n", i));
			return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
		}
		if ( me_ctrl->pme[ i ].m1adjust.waitOnoff > ImMe_D_IM_ME_ON ) {
			Ddim_Assertion(("Im_ME_Ctrl() error. m1adjust.waitOnoff[ %d ] is invalid.\n", i));
			return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
		}
		if ( me_ctrl->pme[ i ].m1pause.pauseOnoff > ImMe_D_IM_ME_ON ) {
			Ddim_Assertion(("Im_ME_Ctrl() error. m1pause.pauseOnoff[ %d ] is invalid.\n", i));
			return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
		}
		if ( me_ctrl->pme[ i ].m1limit.vPlus > ImMe_D_IM_ME_VEC_LIMITV_MAX ) {
			Ddim_Assertion(("Im_ME_Ctrl() error. m1limit.vPlus[ %d ] is invalid.\n", i));
			return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
		}
		if ( me_ctrl->pme[ i ].m1limit.vMinus > ImMe_D_IM_ME_VEC_LIMITV_MAX ) {
			Ddim_Assertion(("Im_ME_Ctrl() error. m1limit.vMinus[ %d ] is invalid.\n", i));
			return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
		}
		if ( me_ctrl->pme[ i ].m1limit.hPlus > ImMe_D_IM_ME_VEC_LIMITH_MAX ) {
			Ddim_Assertion(("Im_ME_Ctrl() error. m1limit.hPlus[ %d ] is invalid.\n", i));
			return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
		}
		if ( me_ctrl->pme[ i ].m1limit.hMinus > ImMe_D_IM_ME_VEC_LIMITH_MAX ) {
			Ddim_Assertion(("Im_ME_Ctrl() error. m1limit.hMinus[ %d ] is invalid.\n", i));
			return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
		}
		if ( me_ctrl->pme[ i ].coreMode.lineInterval > ImMe_D_IM_ME_LINEINTV_3QMB ) {
			Ddim_Assertion(("Im_ME_Ctrl() error. coreMode.lineInterval[ %d ] is invalid.\n", i));
			return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
		}
	}
	if ( me_ctrl->rmcif.pmeNum > ( ImMe_E_IM_ME_PPNUM_MAX - 1 ) ) {
		Ddim_Assertion(("Im_ME_Ctrl() error. pmeNum is invalid.\n"));
		return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
	}
	if ( me_ctrl->rmcif.abtType > ImMe_D_IM_ME_ABT_ROUND ) {
		Ddim_Assertion(("Im_ME_Ctrl() error. abtType is invalid.\n"));
		return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
	}
#endif

	imMeOnPclk();
	imMeOnXclk();
	imMeOnClk();
	ImMe_IM_ME_DSB();

	// Wait ME Stop.
	while ( ( IO_ME.PME[ ImMe_E_IM_ME_PPNUM_PPA ].STATE.bit.ME1_STATE != ImMe_D_IM_ME_ME1_STATE_STOP ) ||
			( IO_ME.PME[ ImMe_E_IM_ME_PPNUM_PPB ].STATE.bit.ME1_STATE != ImMe_D_IM_ME_ME1_STATE_STOP ) ||
			( IO_ME.PME[ ImMe_E_IM_ME_PPNUM_PPC ].STATE.bit.ME1_STATE != ImMe_D_IM_ME_ME1_STATE_STOP ) ||
			( IO_ME.PF1_START.bit.STR != ImMe_D_IM_ME_STR_STOP ) ) {

		DDIM_User_Dly_Tsk( 1 );

		Ddim_Print(("Im_ME_Ctrl() : ME Processing\n"));
	}

	// User callback function setting.
	S_G_IM_ME_AXI_ERR			= ImMe_D_IM_ME_AXI_NORMAL_END;
	S_G_IM_ME_CALL_BACK_FUNC	= me_ctrl->pCallBack;

	// Parameter saved.
	S_G_IM_ME_CTRL = *me_ctrl;

	// Interrupt enable.
	IO_ME.INTMODE.bit.PPAVALID	= me_ctrl->apbbrg.ppEnable[ ImMe_E_IM_ME_PPNUM_PPA ];	// PPA.
	IO_ME.INTMODE.bit.PPBVALID	= me_ctrl->apbbrg.ppEnable[ ImMe_E_IM_ME_PPNUM_PPB ];	// PPB.
	IO_ME.INTMODE.bit.PPCVALID	= me_ctrl->apbbrg.ppEnable[ ImMe_E_IM_ME_PPNUM_PPC ];	// PPC.
	IO_ME.INTSTATE.bit.PPAINT	= me_ctrl->apbbrg.ppEnable[ ImMe_E_IM_ME_PPNUM_PPA ];	// PPA.
	IO_ME.INTSTATE.bit.PPBINT	= me_ctrl->apbbrg.ppEnable[ ImMe_E_IM_ME_PPNUM_PPB ];	// PPB.
	IO_ME.INTSTATE.bit.PPCINT	= me_ctrl->apbbrg.ppEnable[ ImMe_E_IM_ME_PPNUM_PPC ];	// PPC.
	IO_ME.INTMODE.bit.INTMODE	= me_ctrl->apbbrg.intMode;							// Interrupt mode.
	IO_ME.INTCNTR.bit.INTERVAL	= me_ctrl->apbbrg.interval;							// Interval.

	for ( int i = 0; i < ImMe_E_IM_ME_PPNUM_MAX; i++ ) {

		if ( me_ctrl->apbbrg.ppEnable[ i ] == ImMe_D_IM_ME_ON ) {
			// Input mode.
			IO_ME.PME[ i ].INPUTMODE.bit.INPUTMODE	= me_ctrl->pme[ i ].inputMode;
			IO_ME.PME[ i ].INPUTMODE.bit.REF_TXB	= me_ctrl->pme[ i ].refTxb;

			// The limit of the use of off-screen as a reference pixel.
			IO_ME.PME[ i ].OUTLIMIT.bit.LIMIT		= me_ctrl->pme[ i ].outLimit;

			// PME processing target number of screens.
			IO_ME.PME[ i ].M1BANKNUM.bit.BANKNUM	= me_ctrl->pme[ i ].bankNum;

			// M1 original image mode.
			for ( int j = 0; j < ImMe_E_IM_ME_BANKNUM_MAX; j++ ) {
				IO_ME.PME[ i ].M1ORGMODE[ j ].bit.DIRECTION	= me_ctrl->pme[ i ].m1orgMode[ j ].direction;
				IO_ME.PME[ i ].M1ORGMODE[ j ].bit.PARITY	= me_ctrl->pme[ i ].m1orgMode[ j ].parity;
				IO_ME.PME[ i ].M1ORGMODE[ j ].bit.READMODE	= me_ctrl->pme[ i ].m1orgMode[ j ].readMode;
				IO_ME.PME[ i ].M1ORGMODE[ j ].bit.SAD0MODE	= me_ctrl->pme[ i ].m1orgMode[ j ].sad0Mode;
				IO_ME.PME[ i ].M1ORGMODE[ j ].bit.SAD1MODE	= me_ctrl->pme[ i ].m1orgMode[ j ].sad1Mode;
				IO_ME.PME[ i ].M1ORGMODE[ j ].bit.VECMODE	= me_ctrl->pme[ i ].m1orgMode[ j ].vecMode;
				IO_ME.PME[ i ].M1ORGMODE[ j ].bit.VECSEL	= me_ctrl->pme[ i ].m1orgMode[ j ].vecSelect;
				IO_ME.PME[ i ].M1ORGMODE[ j ].bit.PICTYPE	= me_ctrl->pme[ i ].m1orgMode[ j ].picType;
			}

			// M1 correct.
			IO_ME.PME[ i ].M1CORRECT.bit.FKY		= me_ctrl->pme[ i ].m1correct.frontKy;
			IO_ME.PME[ i ].M1CORRECT.bit.BKY		= me_ctrl->pme[ i ].m1correct.backKy;
			IO_ME.PME[ i ].M1CORRECT.bit.FKX		= me_ctrl->pme[ i ].m1correct.frontKx;
			IO_ME.PME[ i ].M1CORRECT.bit.BKX		= me_ctrl->pme[ i ].m1correct.backKx;
			IO_ME.PME[ i ].M1CORRECT.bit.MODE		= me_ctrl->pme[ i ].m1correct.mode;
			IO_ME.PME[ i ].M1CORRECT.bit.FH			= me_ctrl->pme[ i ].m1correct.frontH;
			IO_ME.PME[ i ].M1CORRECT.bit.FV			= me_ctrl->pme[ i ].m1correct.frontV;
			IO_ME.PME[ i ].M1CORRECT.bit.BH			= me_ctrl->pme[ i ].m1correct.backH;
			IO_ME.PME[ i ].M1CORRECT.bit.BV			= me_ctrl->pme[ i ].m1correct.backV;

			// M1 MC on/off.
			IO_ME.PME[ i ].M1MC.bit.P				= me_ctrl->pme[ i ].m1mc.pPic;
			IO_ME.PME[ i ].M1MC.bit.B				= me_ctrl->pme[ i ].m1mc.bPic;

			// M1 Split.
			IO_ME.PME[ i ].M1SPLT.bit.MODE			= me_ctrl->pme[ i ].m1splt.mode;
			IO_ME.PME[ i ].M1SPLT.bit.TH			= me_ctrl->pme[ i ].m1splt.thH;
			IO_ME.PME[ i ].M1SPLT.bit.TV			= me_ctrl->pme[ i ].m1splt.thV;

			// M1 Skip.
			IO_ME.PME[ i ].M1SKIP.bit.SKIP			= me_ctrl->pme[ i ].m1skip;

			// M1 Sad.
			IO_ME.PME[ i ].M1SADSUM.bit.U			= me_ctrl->pme[ i ].m1sad.upper;
			IO_ME.PME[ i ].M1SADSUM.bit.L			= me_ctrl->pme[ i ].m1sad.lower;

			// M1 Adjust.
			IO_ME.PME[ i ].M1ADJUST.bit.CYCLE		= me_ctrl->pme[ i ].m1adjust.waitCycle;
			IO_ME.PME[ i ].M1ADJUST.bit.ON			= me_ctrl->pme[ i ].m1adjust.waitOnoff;

			// M1 Pause.
			IO_ME.PME[ i ].M1PAUSE.bit.LINE			= me_ctrl->pme[ i ].m1pause.pauseLine;
			IO_ME.PME[ i ].M1PAUSE.bit.ON			= me_ctrl->pme[ i ].m1pause.pauseOnoff;

			// Vector search limit parameter (vertical).
			IO_ME.PME[ i ].M1LIMITMV[ ImMe_E_IM_ME_BANKNUM_0 ].bit.P	= me_ctrl->pme[ i ].m1limit.vPlus;
			IO_ME.PME[ i ].M1LIMITMV[ ImMe_E_IM_ME_BANKNUM_0 ].bit.M	= me_ctrl->pme[ i ].m1limit.vMinus;

			// Vector search limit parameter (horizon).
			IO_ME.PME[ i ].M1LIMITMH[ ImMe_E_IM_ME_BANKNUM_0 ].bit.P	= me_ctrl->pme[ i ].m1limit.hPlus;
			IO_ME.PME[ i ].M1LIMITMH[ ImMe_E_IM_ME_BANKNUM_0 ].bit.M	= me_ctrl->pme[ i ].m1limit.hMinus;

			// PME Core mode.
			IO_ME.PME[ i ].COREMODE.bit.LINEINTV	= me_ctrl->pme[ i ].coreMode.lineInterval;
			IO_ME.PME[ i ].COREMODE.bit.INITPOSY	= me_ctrl->pme[ i ].coreMode.initPosY;
		}
	}

	// PME number.
	IO_ME.PF1_PMENUM.bit.PMENUM			= me_ctrl->rmcif.pmeNum;

	// Request arbitration method selection.
	IO_ME.ABT_TYPE.bit.ABT_TYPE			= me_ctrl->rmcif.abtType;

	// Bank table parameter.
	IO_ME.BANK_TBL_PVEC.bit.FWD_PVEC	= me_ctrl->rmcif.bankTbl.fwdPvec;
	IO_ME.BANK_TBL_8PELREF.bit.TOP		= me_ctrl->rmcif.bankTbl.top;
	IO_ME.BANK_TBL_8PEL.bit.FWD_8PEL	= me_ctrl->rmcif.bankTbl.fwd8pel;

	// AXI setting.
	IO_ME.AXI_CNTL_SET.bit.ARCACHE		= me_ctrl->rmcif.axiIf.rCacheType;
	IO_ME.AXI_CNTL_SET.bit.ARPROT		= me_ctrl->rmcif.axiIf.rProtectType;
	IO_ME.AXI_CNTL_SET.bit.AWCACHE		= me_ctrl->rmcif.axiIf.wCacheType;
	IO_ME.AXI_CNTL_SET.bit.AWPROT		= me_ctrl->rmcif.axiIf.wProtectType;

	// Fidxed value.
	IO_ME.PF1_ON.bit.PF1_ON				= ImMe_D_IM_ME_ON;
	IO_ME.PF1_ON.bit.PFBUF_EN			= ImMe_D_IM_ME_ON;
	IO_ME.PF1_TBSEL.bit.TBSEL			= ImMe_D_IM_ME_OFF;

	imMeOffClk();
	imMeOffXclk();
	imMeOffPclk();
	ImMe_IM_ME_DSB();

	return D_DDIM_OK;
}

/**
ME start.<br>
@param[in]		me_start					ME start parameters. See @ref ImMeStart.<br>
@retval			D_DDIM_OK					Success.
@retval			ImMe_D_IM_ME_INPUT_PARAM_ERROR	Parameter error.
*/
INT32 Im_ME_Start( const ImMeStart* const me_start )
{
	union io_me_irqsc	meint;

#ifdef CO_PARAM_CHECK
	if ( me_start == NULL ) {
		Ddim_Assertion(("Im_ME_Start() error. me_start = NULL.\n"));
		return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
	}
	if ( ( me_start->rmcif.searchWidth < ImMe_D_IM_ME_SRCH_WIDTH_MIN ) ||
		 ( me_start->rmcif.searchWidth > ImMe_D_IM_ME_SRCH_WIDTH_MAX ) ) {
		Ddim_Assertion(("Im_ME_Start() error. searchWidth is invalid.\n"));
		return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
	}
	if ( ( me_start->rmcif.preWidth < ImMe_D_IM_ME_PRE_WIDTH_MIN ) ||
		 ( me_start->rmcif.preWidth > ImMe_D_IM_ME_PRE_WIDTH_MAX ) ) {
		Ddim_Assertion(("Im_ME_Start() error. preWidth is invalid.\n"));
		return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
	}
	if ( ( me_start->rmcif.preHeight < ImMe_D_IM_ME_PRE_HEIGHT_MIN ) ||
		 ( me_start->rmcif.preHeight > ImMe_D_IM_ME_PRE_HEIGHT_MAX ) ) {
		Ddim_Assertion(("Im_ME_Start() error. preHeight is invalid.\n"));
		return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
	}
	if ( ( me_start->rmcif.curMarginWidth != ImMe_D_IM_ME_CUR_MARGIN_0 ) &&
		 ( me_start->rmcif.curMarginWidth != ImMe_D_IM_ME_CUR_MARGIN_4 ) &&
		 ( me_start->rmcif.curMarginWidth != ImMe_D_IM_ME_CUR_MARGIN_8 ) ) {
		Ddim_Assertion(("Im_ME_Start() error. curMarginWidth is invalid.\n"));
		return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
	}
	if ( ( me_start->rmcif.curMarginHeight != ImMe_D_IM_ME_CUR_MARGIN_0 ) &&
		 ( me_start->rmcif.curMarginHeight != ImMe_D_IM_ME_CUR_MARGIN_4 ) &&
		 ( me_start->rmcif.curMarginHeight != ImMe_D_IM_ME_CUR_MARGIN_8 ) ) {
		Ddim_Assertion(("Im_ME_Start() error. curMarginHeight is invalid.\n"));
		return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
	}
	if ( ( me_start->rmcif.prefetchWidth < ImMe_D_IM_ME_PREF_WIDTH_MIN ) ||
		 ( me_start->rmcif.prefetchWidth > ImMe_D_IM_ME_PREF_WIDTH_MAX ) ) {
		Ddim_Assertion(("Im_ME_Start() error. prefetchWidth is invalid.\n"));
		return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
	}
	if ( ( me_start->rmcif.prefetchHeight < ImMe_D_IM_ME_PREF_HEIGHT_MIN ) ||
		 ( me_start->rmcif.prefetchHeight > ImMe_D_IM_ME_PREF_HEIGHT_MAX ) ) {
		Ddim_Assertion(("Im_ME_Start() error. prefetchHeight is invalid.\n"));
		return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
	}
	if ( ( me_start->rmcif.searchHeight < ImMe_D_IM_ME_SRCH_HEIGHT_MIN ) ||
		 ( me_start->rmcif.searchHeight > ImMe_D_IM_ME_SRCH_HEIGHT_MAX ) ) {
		Ddim_Assertion(("Im_ME_Start() error. searchHeight is invalid.\n"));
		return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
	}
	for ( int i = 0; i < ImMe_E_IM_ME_PPNUM_MAX; i++ ) {
		if ( me_start->pme[ i ].mbnumH > ImMe_D_IM_ME_MBNUM_H_MAX ) {
			Ddim_Assertion(("Im_ME_Start() error. mbnumH[ %d ] is invalid.\n", i));
			return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
		}
		if ( me_start->pme[ i ].mbnumV > ImMe_D_IM_ME_MBNUM_V_MAX ) {
			Ddim_Assertion(("Im_ME_Start() error. mbnumV[ %d ] is invalid.\n", i));
			return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
		}
		if ( me_start->pme[ i ].cancelMode > ImMe_D_IM_ME_VEC_CANCEL_MODE_CUR2 ) {
			Ddim_Assertion(("Im_ME_Start() error. pme[ %d ].cancelMode is invalid.\n", i ));
			return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
		}
		if ( ( me_start->pme[ i ].vecHsize != ImMe_D_IM_ME_PRE_VEC_HSIZE_512  ) &&
			 ( me_start->pme[ i ].vecHsize != ImMe_D_IM_ME_PRE_VEC_HSIZE_1024 ) ) {
			Ddim_Assertion(("Im_ME_Start() error. vecHsize[ %d ] is invalid.\n", i));
			return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
		}
	}
#endif

	imMeOnPclk();
	imMeOnXclk();
	imMeOnClk();
	ImMe_IM_ME_DSB();

	ImMe_IM_ME_LOCK();

	// Wait ME Stop.
	while ( ( IO_ME.PME[ ImMe_E_IM_ME_PPNUM_PPA ].STATE.bit.ME1_STATE != ImMe_D_IM_ME_ME1_STATE_STOP ) ||
			( IO_ME.PME[ ImMe_E_IM_ME_PPNUM_PPB ].STATE.bit.ME1_STATE != ImMe_D_IM_ME_ME1_STATE_STOP ) ||
			( IO_ME.PME[ ImMe_E_IM_ME_PPNUM_PPC ].STATE.bit.ME1_STATE != ImMe_D_IM_ME_ME1_STATE_STOP ) ||
			( IO_ME.PF1_START.bit.STR != ImMe_D_IM_ME_STR_STOP ) ) {

		DDIM_User_Dly_Tsk( 1 );

		Ddim_Print(("Im_ME_Start() : ME Processing\n"));
	}

	(VOID)DDIM_User_Clr_Flg( FID_IM_ME, ~ImMe_D_IM_ME_FLG_END );

	// Interrupt flag clear.
	meint.word			= ImMe_D_IM_ME_OFF;
	meint.bit.__IRQ0	= ImMe_D_IM_ME_ON;
	meint.bit.__IRQ1	= ImMe_D_IM_ME_ON;
	meint.bit.__IRQ2	= ImMe_D_IM_ME_ON;
	meint.bit.__IRQ3	= ImMe_D_IM_ME_ON;
	meint.bit.__IRQ4	= ImMe_D_IM_ME_ON;
	meint.bit.__IRQ5	= ImMe_D_IM_ME_ON;
	meint.bit.__IRQ6	= ImMe_D_IM_ME_ON;
	meint.bit.__IRQ7	= ImMe_D_IM_ME_ON;
	meint.bit.__IRQ8	= ImMe_D_IM_ME_ON;
	IO_ME.PME[ ImMe_E_IM_ME_PPNUM_PPA ].IRQSC.word	= meint.word;
	IO_ME.PME[ ImMe_E_IM_ME_PPNUM_PPB ].IRQSC.word	= meint.word;
	IO_ME.PME[ ImMe_E_IM_ME_PPNUM_PPC ].IRQSC.word	= meint.word;

	S_G_IM_ME_INT_CNT = 0;

	// Previous shift.
	ImMe_IM_ME_SET_REG_SIGNED_A( IO_ME.SHIFT_3DNRME, union io_me_shift3dnrme, X, me_start->rmcif.preShiftX );
	ImMe_IM_ME_SET_REG_SIGNED_A( IO_ME.SHIFT_3DNRME, union io_me_shift3dnrme, Y, me_start->rmcif.preShiftY );

	// Previous image read address.
	IO_ME.PREV_GBO.bit.H			= me_start->rmcif.preRAddrHi;
	IO_ME.PREV_GBO.bit.L			= me_start->rmcif.preRAddrLo;

	// Current image read address.
	IO_ME.M1_GBO.bit.H				= me_start->rmcif.curRAddrHi;
	IO_ME.M1_GBO.bit.L				= me_start->rmcif.curRAddrLo;

	// Vector image write address.
	IO_ME.PVEC_GBO.bit.H			= me_start->rmcif.vecWAddrHi;
	IO_ME.PVEC_GBO.bit.L			= me_start->rmcif.vecWAddrLo;

	// Previous image size (1/4 size).
	IO_ME.PREV_GLSS.bit.GLSS		= me_start->rmcif.preGwidth;
	IO_ME.PREVSZ_3DNRME.bit.H		= me_start->rmcif.preWidth;
	IO_ME.PREVSZ_3DNRME.bit.V		= me_start->rmcif.preHeight;

	// Current image size (1/4 size).
	IO_ME.M1_GLSS.bit.GLSS			= me_start->rmcif.curGwidth;

	// Current image margin size.
	IO_ME.MRGN_3DNRME.bit.H			= me_start->rmcif.curMarginWidth;
	IO_ME.MRGN_3DNRME.bit.V			= me_start->rmcif.curMarginHeight;

	// Prefetch size.
	IO_ME.PF_SIZE.bit.H				= me_start->rmcif.prefetchWidth;
	IO_ME.PF_SIZE.bit.V				= me_start->rmcif.prefetchHeight;

	// ME1 initialize search size.
	IO_ME.PF1_INISIZE.bit.SIZE_X	= me_start->rmcif.searchWidth;
	IO_ME.PF1_INISIZE.bit.SIZE_Y	= me_start->rmcif.searchHeight;

	// Prefetch start.
	IO_ME.PF1_START.bit.STR			= ImMe_D_IM_ME_STR_START;

	for ( int i = 0; i < ImMe_E_IM_ME_PPNUM_MAX; i++ ) {

		if ( S_G_IM_ME_CTRL.apbbrg.ppEnable[ i ] == ImMe_D_IM_ME_ON ) {
			// MB number.
			IO_ME.PME[ i ].MBNUM.bit.H				= me_start->pme[ i ].mbnumH;
			IO_ME.PME[ i ].MBNUM.bit.V				= me_start->pme[ i ].mbnumV;

			// Vector cancel function.
			IO_ME.PME[ i ].CNCL.bit.MODE			= me_start->pme[ i ].cancelMode;
			IO_ME.PME[ i ].CNCL.bit.THH				= me_start->pme[ i ].cancelThresholdHi;
			IO_ME.PME[ i ].CNCL.bit.THL				= me_start->pme[ i ].cancelThresholdLo;

			// Vector output.
			IO_ME.PME[ i ].VOUT_FMT.bit.HSIZE		= me_start->pme[ i ].vecHsize;

			// PME start.
			IO_ME.PME[ i ].M1START.bit.M1PIC_STR	= ImMe_D_IM_ME_ON;
		}
	}

	ImMe_IM_ME_UNLOCK();

	imMeOffPclk();
	ImMe_IM_ME_DSB();

	return D_DDIM_OK;
}

/**
ME wait end.<br>
@param[out]		p_wait_factor				Pointer of factor parameter which release wait process.
@param[in]		wait_time					Wait time [msec]. The valid range is -1, 0, ... .
											If this parameter is set to -1, driver waits permanently unless system-call sets event-flag.
@retval			D_DDIM_OK					Success.
@retval			ImMe_D_IM_ME_INPUT_PARAM_ERROR	Parameter error.
@retval			ImMe_D_IM_ME_TIMEOUT				Time out.
@retval			ImMe_D_IM_ME_AXI_ERROR			AXI BUS error.
@retval			ImMe_D_IM_ME_NG					System NG.
*/
INT32 Im_ME_Wait_End( UINT32* const p_wait_factor, const INT32 wait_time )
{
	DDIM_USER_FLGPTN	waitptn;
	DDIM_USER_FLGPTN	flgptn;
	DDIM_USER_ER		ercd;
	INT32				ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ( ( p_wait_factor == NULL ) ||
		 ( ImMe_IM_ME_CHECK_WAIT_TIME( wait_time ) == FALSE) ) {
		Ddim_Assertion(("Im_ME_Wait_End parameter error\n"));
		return ImMe_D_IM_ME_INPUT_PARAM_ERROR;
	}
#endif

	waitptn = ImMe_D_IM_ME_FLG_END;

	// ME wait end.
	ercd = DDIM_User_Twai_Flg( FID_IM_ME, waitptn, D_DDIM_USER_TWF_ORW, &flgptn, (DDIM_USER_TMO)wait_time );

	if ( ercd == D_DDIM_USER_E_TMOUT ) {

		Ddim_Print(("Im_ME_Wait_End() time out. ercd = %d\n", ercd));

		ret = ImMe_D_IM_ME_TIMEOUT;
	}
	else if ( ercd != D_DDIM_USER_E_OK ) {

		Ddim_Print(("Im_ME_Wait_End() system error. ercd = %d\n", ercd));

		ret = ImMe_D_IM_ME_NG;
	}
	else {
		flgptn = waitptn & flgptn;
		(VOID)DDIM_User_Clr_Flg( FID_IM_ME, ~flgptn );
	}

	*p_wait_factor = (UINT32)flgptn;

	imMeOnPclk();
	ImMe_IM_ME_DSB();

	if ( ret == D_DDIM_OK ) {
		// Check AXI error.
		if ( S_G_IM_ME_AXI_ERR != ImMe_D_IM_ME_AXI_NORMAL_END ) {
			Ddim_Print(("Im_ME_Wait_End() AXI error. ercd = %lu\n", S_G_IM_ME_AXI_ERR));
#ifdef CO_ME_DEBUG_PRINT
			Ddim_Print(("RESP_CIR = %d\n", IO_ME.AXI_ERR_STATUS.bit.RESP_CIR));
			Ddim_Print(("RESP_PRE = %d\n", IO_ME.AXI_ERR_STATUS.bit.RESP_PRE));
			Ddim_Print(("RESP_VEC = %d\n", IO_ME.AXI_ERR_STATUS.bit.RESP_VEC));
#endif
			ret = ImMe_D_IM_ME_AXI_ERROR;
		}
	}

	// AXI error clear.
	IO_ME.AXI_ERR_CLR.bit.CUR_CLR = ImMe_D_IM_ME_ON;
	IO_ME.AXI_ERR_CLR.bit.PRE_CLR = ImMe_D_IM_ME_ON;
	IO_ME.AXI_ERR_CLR.bit.VEC_CLR = ImMe_D_IM_ME_ON;

	imMeOffClk();
	imMeOffXclk();
	imMeOffPclk();
	ImMe_IM_ME_DSB();

	return ret;
}

/**
ME interupt handler.<br>
@retval			None.
*/
VOID Im_ME_Int_Handler( VOID )
{
	DDIM_USER_ER				ercd;
	union io_me_axierrstatus	axi_err_status;
	union io_me_irqsc			meint;

	S_G_IM_ME_AXI_ERR = ImMe_D_IM_ME_AXI_NORMAL_END;

	axi_err_status.word = IO_ME.AXI_ERR_STATUS.word;

	// AXI error check.
	if ( axi_err_status.bit.CUR_STS != 0 ) {	/* pgr0872 */
		S_G_IM_ME_AXI_ERR |= ImMe_D_IM_ME_AXI_ERR_CH_R_CUR;
	}

	// AXI error check.
	if ( axi_err_status.bit.PRE_STS != 0 ) {	/* pgr0872 */
		S_G_IM_ME_AXI_ERR |= ImMe_D_IM_ME_AXI_ERR_CH_W_PRE;
	}

	// AXI error check.
	if ( axi_err_status.bit.VEC_STS != 0 ) {	/* pgr0872 */
		S_G_IM_ME_AXI_ERR |= ImMe_D_IM_ME_AXI_ERR_CH_W_VEC;
	}

#ifdef CO_ME_DEBUG_PRINT
	Ddim_Print(( "Im_ME_Int_Handler axi_err_status=0x%lx\n", axi_err_status.word ));
#endif

	imMeOnPclk();
	ImMe_IM_ME_DSB();

	meint.word = IO_ME.PME[ ImMe_E_IM_ME_PPNUM_PPA ].IRQSC.word;
	if( meint.bit.__IRQ6 == ImMe_D_IM_ME_ON ) {		/* pgr0872 */
		S_G_IM_ME_INT_CNT++;
		IO_ME.PME[ ImMe_E_IM_ME_PPNUM_PPA ].IRQSC.word = meint.word;
	}

	meint.word = IO_ME.PME[ ImMe_E_IM_ME_PPNUM_PPB ].IRQSC.word;
	if( meint.bit.__IRQ6 == ImMe_D_IM_ME_ON ) {		/* pgr0872 */
		S_G_IM_ME_INT_CNT++;
		IO_ME.PME[ ImMe_E_IM_ME_PPNUM_PPB ].IRQSC.word = meint.word;
	}

	meint.word = IO_ME.PME[ ImMe_E_IM_ME_PPNUM_PPC ].IRQSC.word;
	if( meint.bit.__IRQ6 == ImMe_D_IM_ME_ON ) {		/* pgr0872 */
		S_G_IM_ME_INT_CNT++;
		IO_ME.PME[ ImMe_E_IM_ME_PPNUM_PPC ].IRQSC.word = meint.word;
	}

	if ( S_G_IM_ME_INT_CNT >= 3 ) {
		S_G_IM_ME_INT_CNT = 0;
		ercd = DDIM_User_Set_Flg( FID_IM_ME, ImMe_D_IM_ME_FLG_END );
		if ( ercd != D_DDIM_USER_E_OK ) {
			Ddim_Print(("Im_ME_Int_Handler : Error DDIM_User_Set_Flg [%d]\n", ercd));
		}
	}

	imMeOffPclk();
	ImMe_IM_ME_DSB();

	// User callback function.
	if ( S_G_IM_ME_CALL_BACK_FUNC != NULL ) {
#ifdef CO_ME_DEBUG_PRINT
		Ddim_Print(( "Im_ME_Int_Handler begin callback\n" ));
#endif
		S_G_IM_ME_CALL_BACK_FUNC( S_G_IM_ME_AXI_ERR );

#ifdef CO_ME_DEBUG_PRINT
		Ddim_Print(( "Im_ME_Int_Handler end callback\n" ));
#endif
	}
}

ImMe *im_me_new(void)
{
	ImMe* self = k_object_new_with_private(IM_TYPE_ME,sizeof(ImMePrivate));
	return self;
}
