/*
 * imraw.c
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

#include "jdsraw.h"
#include "dd_top.h"
#include "ddim_user_custom.h"
#include "driver_common.h"

#include "imraw.h"


K_TYPE_DEFINE_WITH_PRIVATE(imRaw, im_raw)
#define IM_RAW_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), imRawPrivate,IM_TYPE_RAW))

#ifdef CO_ACT_CLOCK
#define CO_ACT_RAWCLK
#endif
#ifdef CO_ACT_ICLOCK
#define CO_ACT_RAW_ICLK
#endif
#ifdef CO_ACT_PCLOCK
#define CO_ACT_RAW_PCLK
#endif

#ifdef CO_ACT_RAWCLK
#define D_IM_RAW_RAWCK_BIT		(D_DD_TOP_RAWCK_BIT)
#endif
#ifdef CO_ACT_RAW_PCLK
#define D_IM_RAW_RAWAP_BIT		(D_DD_TOP_RAWAP_BIT)
#endif
#ifdef CO_ACT_RAW_ICLK
#define D_IM_RAW_RAWAX_BIT		(D_DD_TOP_RAWAX_BIT)
#endif


#define	D_IM_RAW_FALSE			(0)
#define	D_IM_RAW_TRUE			(1)

#define	D_IM_RAW_RTRG_STOP		(0)
#define	D_IM_RAW_RTRG_START		(1)
#define	D_IM_RAW_RTRG_STOPPED	(2)
#define	D_IM_RAW_RTRG_RUNNING	(3)

#define	D_IM_RAW_FLG_END		(0x00000001)
#define	D_IM_RAW_FLG_STOP		(0x00000002)
#define	D_IM_RAW_FLG_R_AXI_ERR	(0x00000004)
#define	D_IM_RAW_FLG_W_AXI_ERR	(0x00000008)

#define	D_IM_RAW_INT_R_BIT		(0x00000001)	// RE, RF bit
#define	D_IM_RAW_INT_RAXER_BIT	(0x00000010)	// RAXERE, RAXERF bit
#define	D_IM_RAW_INT_WAXER_BIT	(0x00000020)	// WAXERE, WAXERF bit

#define D_IM_RAW_SRAM_WAIT_USEC	(1)

#ifdef CO_PARAM_CHECK
#define im_raw_check_pointer(ptr)			(( ptr != NULL ) ? D_IM_RAW_TRUE : D_IM_RAW_FALSE)
#define im_raw_check_wait_time(wait_time)	(( wait_time >= D_DDIM_USER_SEM_WAIT_FEVR ) ? D_IM_RAW_TRUE : D_IM_RAW_FALSE)
#endif

#define Im_RAW_Dsb()				Dd_ARM_Dsb_Pou()
#define Im_RAW_Wait_usec( usec )	Dd_ARM_Wait_ns( (usec * 1000) )

struct _imRawPrivate
{
	int a;
};


static void im_raw_constructor(imRaw *self)
{
//	imRawPrivate *priv = IM_RAW_GET_PRIVATE(self);
}

static void im_raw_destructor(imRaw *self)
{
//	imRawPrivate *priv = IM_RAW_GET_PRIVATE(self);
}

#ifdef CO_ACT_RAWCLK
static volatile UCHAR S_G_IM_RAW_RAWCLK_COUNTER = 0;
#endif
#ifdef CO_ACT_RAW_ICLK
static volatile UCHAR S_G_IM_RAW_ICLK_COUNTER = 0;
#endif
#ifdef CO_ACT_RAW_PCLK
static volatile UCHAR S_G_IM_RAW_PCLK_COUNTER = 0;
#endif

static volatile UINT32 S_G_IM_RAW_COND;

static VOID (*S_G_IM_RAW_CALLBACK)(UINT32) = NULL;

/*
 DECLS
 */
static VOID imRawOnRawclk( VOID );
static VOID imRawOffRawclk( VOID );
static VOID imRawOnRawiclk( VOID );
static VOID imRawOffRawiclk( VOID );
static VOID imRawSetupParam( const ImRawCtrlParam* const cfg );
static INT32 imRawWaitEnd( DDIM_USER_FLGPTN* flgptn, INT32 wait_time );

/*
 IMPL
 */

/**
 * @brief			RAWCLK ON
 * @param[in]		None
 * @param[out]		None
 * @retval			None
 * @note			None
 */
static VOID imRawOnRawclk( VOID )
{
#ifdef CO_ACT_RAWCLK
	Dd_Top_Start_Clock( (UCHAR*)&S_G_IM_RAW_RAWCLK_COUNTER, &Dd_Top_Get_CLKSTOP7(), ~((ULONG)D_IM_RAW_RAWCK_BIT) );
#endif
}

/**
 * @brief			RAWCLK OFF
 * @param[in]		None
 * @param[out]		None
 * @retval			None
 * @note			None
 */
static VOID imRawOffRawclk( VOID )
{
#ifdef CO_ACT_RAWCLK
	Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_RAW_RAWCLK_COUNTER, &Dd_Top_Get_CLKSTOP7(), ((ULONG)D_IM_RAW_RAWCK_BIT) );
#endif
}

/**
 * @brief			RAWICLK ON
 * @param[in]		None
 * @param[out]		None
 * @retval			None
 * @note			None
 */
static VOID imRawOnRawiclk( VOID )
{
#ifdef CO_ACT_RAW_ICLK
	Dd_Top_Start_Clock( (UCHAR*)&S_G_IM_RAW_ICLK_COUNTER, &Dd_Top_Get_CLKSTOP7(), ~((ULONG)D_IM_RAW_RAWAX_BIT) );
#endif
}

/**
 * @brief			RAWICLK OFF
 * @param[in]		None
 * @param[out]		None
 * @retval			None
 * @note			None
 */
static VOID imRawOffRawiclk( VOID )
{
#ifdef CO_ACT_RAW_ICLK
	Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_RAW_ICLK_COUNTER, &Dd_Top_Get_CLKSTOP7(), ((ULONG)D_IM_RAW_RAWAX_BIT) );
#endif
}

/**
 * @brief			Setup parameters
 * @param[in]   	ImRawCtrlParam* const cfg	: control data
 * @param[out]		None
 * @retval			None
 * @note			None
 */
static VOID imRawSetupParam( const ImRawCtrlParam* const cfg )
{
	INT32 i;
	volatile UINT32 *pLUT;

	// Common
	IO_RAW.RINTE.bit.RE		= 1;
	IO_RAW.RINTE.bit.RAXERE	= 1;
	IO_RAW.RINTE.bit.WAXERE	= 1;

	IO_RAW.MSA.bit.MSA			= cfg->srcAddr;
	IO_RAW.MDA.bit.MDA			= cfg->dstAddr;
	IO_RAW.RCTL1.bit.RFMT		= cfg->dataFormat;
	IO_RAW.RCTL1.bit.BYTS		= cfg->byteStuffing;
	IO_RAW.DEFINIT.bit.DEFINIT	= cfg->diffFixedValue;

	IO_RAW.MRAXCTL.bit.MRCACHE	= cfg->axiParam.rCacheType;
	IO_RAW.MRAXCTL.bit.MRPROT	= cfg->axiParam.rProtectionType;
	IO_RAW.MWAXCTL.bit.MWCACHE	= cfg->axiParam.wCacheType;
	IO_RAW.MWAXCTL.bit.MWPROT	= cfg->axiParam.wProtectionType;

	S_G_IM_RAW_CALLBACK = cfg->callback;

	// Only 12/14/16 bit
	if( (cfg->dataFormat == D_IM_RAW_RFMT_14_OR_16_BIT)||(cfg->dataFormat == D_IM_RAW_RFMT_12_BIT_PACK) ){
		IO_RAW.HSIZE.bit.HSIZE	= cfg->width;
		IO_RAW.VSIZE.bit.VSIZE	= cfg->lines;
		IO_RAW.RCTL1.bit.DEFFC	= cfg->mcuSize;
		if( cfg->dataFormat == D_IM_RAW_RFMT_12_BIT_PACK ){
			IO_RAW.RCTL1.bit.BITSEL = D_IM_RAW_BITSEL_EXCEPT_16_BIT;
		}
		else{
			IO_RAW.RCTL1.bit.BITSEL = cfg->bitSelect;
		}
		IO_RAW.RCTL1.bit.LUTEN		= D_IM_RAW_OFF;
		IO_RAW.RCTL1.bit.DEFOP		= D_IM_RAW_DEFOP_DIFF_PREV_VALUE;
	}
	else{	// D_IM_RAW_RFMT_8_BIT
		IO_RAW.DSIZE.bit.DSIZE	= cfg->dataSize;
		IO_RAW.RCTL1.bit.DEFOP	= cfg->diffMode;
		IO_RAW.RCTL1.bit.BITSEL	= D_IM_RAW_BITSEL_EXCEPT_16_BIT;

		if( cfg->lut == NULL ){
			IO_RAW.RCTL1.bit.LUTEN		= D_IM_RAW_OFF;
		}
		else{
			// set RAW macro enable (active mode)
			IO_RAW.TBLAEN.bit.TBLAEN	= D_IM_RAW_TBLAEN_ON;
			// wait 1us
			Im_RAW_Wait_usec( D_IM_RAW_SRAM_WAIT_USEC );

			IO_RAW.RCTL1.bit.LUTEN		= D_IM_RAW_ON;
			pLUT = (volatile UINT32*)&IO_RAW.LUT.LUT1.word;
			for( i = 0; i < 256; i+=4 ){
				*pLUT++ = (  (cfg->lut[i+3] << 24)
						   | (cfg->lut[i+2] << 16)
						   | (cfg->lut[i+1] <<  8)
						   | (cfg->lut[i+0] <<  0) );
			}

			// RAW macro disable (power save mode)
			IO_RAW.TBLAEN.bit.TBLAEN	= D_IM_RAW_TBLAEN_OFF;
		}
	}
}

/**
 * @brief			Wait that the asynchronization processing ends
 * @param[in]   	DDIM_USER_FLGPTN* flgptn	: wait flag pattern
 * @param[in]   	INT32 wait_time				: wait time
 * @param[out]		None
 * @retval			When the executed asynchronization processing ends, it is a return.
 * @note			None
 */
static INT32 imRawWaitEnd( DDIM_USER_FLGPTN* flgptn, INT32 wait_time )
{
	DDIM_USER_ER		ercd;
	DDIM_USER_FLGPTN	waitptn;

	waitptn = ( D_IM_RAW_FLG_END | D_IM_RAW_FLG_STOP | D_IM_RAW_FLG_R_AXI_ERR | D_IM_RAW_FLG_W_AXI_ERR );
	ercd = DDIM_User_Twai_Flg( FID_IM_RAW, waitptn, D_DDIM_USER_TWF_ORW, flgptn, (DDIM_USER_TMO)wait_time );
	if( ercd == D_DDIM_USER_E_TMOUT ){
		return D_IM_RAW_RETVAL_TIME_OUT;
	}
	if( ercd != D_DDIM_USER_E_OK ){
		return D_IM_RAW_RETVAL_SYSTEM_ERROR;
	}

	ercd = DDIM_User_Clr_Flg( FID_IM_RAW, ~(waitptn & (*flgptn)) );
	if( ercd != D_DDIM_USER_E_OK ){
		return D_IM_RAW_RETVAL_SYSTEM_ERROR;
	}

	// Read AXI Error Check
	if( ((*flgptn) & (DDIM_USER_FLGPTN)D_IM_RAW_FLG_R_AXI_ERR) != 0 ){
		return D_IM_RAW_RETVAL_R_AXI_ERR;
	}
	// Write AXI Error Check
	if( ((*flgptn) & (DDIM_USER_FLGPTN)D_IM_RAW_FLG_W_AXI_ERR) != 0 ){
		return D_IM_RAW_RETVAL_W_AXI_ERR;
	}

	return D_IM_RAW_RETVAL_OK;
}

/*
PUBLIC
 */

/**
 * @brief			APB Bus clock ON for RAW
 * @param[in]   	None
 * @param[out]		None
 * @retval			None
 * @note			None
 */
VOID im_raw_on_pclk( imRaw*self )
{
#ifdef CO_ACT_RAW_PCLK
	Dd_Top_Start_Clock( (UCHAR*)&S_G_IM_RAW_PCLK_COUNTER, &Dd_Top_Get_CLKSTOP7(), ~((ULONG)D_IM_RAW_RAWAP_BIT) );

	// wait
	IO_RAW.CCNT.word;	/* pgr0695 */
#endif
}

/**
 * @brief			APB Bus clock OFF for RAW
 * @param[in]   	None
 * @param[out]		None
 * @retval			None
 * @note			None
 */
VOID im_raw_off_pclk( imRaw*self )
{
#ifdef CO_ACT_RAW_PCLK
	// wait
	IO_RAW.CCNT.word;	/* pgr0695 */

	Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_RAW_PCLK_COUNTER, &Dd_Top_Get_CLKSTOP7(), ((ULONG)D_IM_RAW_RAWAP_BIT) );
#endif
}

/**
 * @brief			Software-reset and release software reset.
 * @param[in]   	None
 * @param[out]		None
 * @retval			D_IM_RAW_RETVAL_OK, D_IM_RAW_RETVAL_MACRO_BUSY
 * @note			None
 */
INT32 im_raw_init( imRaw*self )
{
	INT32	retval;

	imRawOnRawclk();
	imRawOnRawiclk();
	im_raw_on_pclk(NULL);
	Im_RAW_Dsb();

	if( IO_RAW.RCTL1.bit.RTRG == D_IM_RAW_RTRG_STOPPED ){
		// Software-Reset ON
		IO_RAW.RCTL0.word = 1;

		// RAWCLK        = MAX200MHz	MIN50MHz
		// APB clock     = 50MHz
		// -->   ( (1/RAWCLK) / (1/APB clock) ) * 3 + 1
		//     = ( (1/25)   / (1/50)     ) * 3 + 1
		//     = 7 APB cycle

		IO_RAW.RCTL0.word;	/* pgr0695 */
		IO_RAW.RCTL0.word;	/* pgr0695 */
		IO_RAW.RCTL0.word;	/* pgr0695 */
		IO_RAW.RCTL0.word;	/* pgr0695 */

		// Software-Reset OFF
		IO_RAW.RCTL0.word = 0;

		// RAW macro disable (power save mode)
		IO_RAW.TBLAEN.bit.TBLAEN	= D_IM_RAW_TBLAEN_OFF;

		retval = D_IM_RAW_RETVAL_OK;
	}
	else{
		retval = D_IM_RAW_RETVAL_MACRO_BUSY;
	}

	im_raw_off_pclk(NULL);
	imRawOffRawiclk();
	imRawOffRawclk();
	Im_RAW_Dsb();

	return retval;
}

/**
   Open driver.
   */

/**
 * @brief			The semaphore of RAW is acquired
 * @param[in]		wait_time	: Time-out period
 * @param[out]		None
 * @retval			D_IM_RAW_RETVAL_OK, D_IM_RAW_RETVAL_PARAM_ERROR, D_IM_RAW_RETVAL_SYSTEM_ERROR
 * @note			None
 */
INT32 im_raw_open( imRaw*self,INT32 wait_time )
{
	DDIM_USER_ER	ercd;

#ifdef CO_PARAM_CHECK
	if( im_raw_check_wait_time(wait_time) == D_IM_RAW_FALSE ){
		Ddim_Assertion(("I:im_raw_open INVALID_ARG_ERR\n"));
		return D_IM_RAW_RETVAL_PARAM_ERROR;
	}
#endif

	if( D_DDIM_USER_SEM_WAIT_POL == wait_time ){
		ercd = DDIM_User_Pol_Sem( SID_IM_RAW );
	}
	else{
		ercd = DDIM_User_Twai_Sem( SID_IM_RAW, (DDIM_USER_TMO)wait_time );
	}

	if( D_DDIM_USER_E_OK == ercd ){
		return D_IM_RAW_RETVAL_OK;
	}
	else{
		return D_IM_RAW_RETVAL_SYSTEM_ERROR;
	}
}

/**
 * @brief		The semaphore of RAW is returned
 * @param[in]	None
 * @param[out]	None
 * @return		D_IM_RAW_RETVAL_OK, D_IM_RAW_RETVAL_SYSTEM_ERROR
 * @note		None
 */
INT32 im_raw_close( imRaw*self )
{
	DDIM_USER_ER	ercd;

	ercd = DDIM_User_Sig_Sem( SID_IM_RAW );

	if( D_DDIM_USER_E_OK == ercd ){
		return D_IM_RAW_RETVAL_OK;
	}
	else{
		return D_IM_RAW_RETVAL_SYSTEM_ERROR;
	}
}

/**
 * @brief		Setup CODEx and LENx table registers.
 * @param[in]	ImRawCtrlCodeTbl* tbl	: Pointer of code table
 * @param[in]	UCHAR dataFormat			: D_IM_RAW_RFMT_14_OR_16_BIT, D_IM_RAW_RFMT_12_BIT_PACK, D_IM_RAW_RFMT_8_BIT
 * @param[out]	None
 * @return		D_IM_RAW_RETVAL_OK, D_IM_RAW_RETVAL_PARAM_ERROR
 * @note		None
 */
INT32 im_raw_ctrl_code_tbl(  imRaw*self,const ImRawCtrlCodeTbl* const tbl, UCHAR dataFormat )
{
	INT32			i, num;
	volatile UINT32	*pCODE, *pLEN;

#ifdef CO_PARAM_CHECK
	if( (im_raw_check_pointer(tbl) == D_IM_RAW_FALSE) || ( dataFormat > D_IM_RAW_RFMT_8_BIT ) ){
		Ddim_Assertion(("I:im_raw_ctrl_code_tbl : INVALID_ARG_ERR\n"));
		return D_IM_RAW_RETVAL_PARAM_ERROR;
	}
#endif

	im_raw_on_pclk(NULL);
	Im_RAW_Dsb();

	if( IO_RAW.RCTL1.bit.RTRG == D_IM_RAW_RTRG_RUNNING ){
		im_raw_off_pclk(NULL);
		Im_RAW_Dsb();
		return D_IM_RAW_RETVAL_MACRO_BUSY;
	}

	// CODEx / LENx
	pCODE = (UINT32*)&IO_RAW.CODE.CODE1.word;
	pLEN  = (UINT32*)&IO_RAW.LEN.LEN1.word;
	if( dataFormat == D_IM_RAW_RFMT_14_OR_16_BIT ){
		num = 14;	// CODE0 - CODEE, LEN0 - LENE
	}
	else if( dataFormat == D_IM_RAW_RFMT_12_BIT_PACK ){
		num = 12;	// CODE0 - CODEC, LEN0 - LENC (Can't Set D - E)
	}
	else{			// D_IM_RAW_RFMT_8_BIT
		num = 8;	// CODE0 - CODE8, LEN0 - LEN8 (Can't Set 9 - E)
	}
	for( i = 0; i < num; i+=2 ){
		*pCODE++ = (UINT32)( (tbl->code[i+1] << 16)        | (tbl->code[i] << 0)        );
		*pLEN++  = (UINT32)( (tbl->codeLength[i+1] << 16) | (tbl->codeLength[i] << 0) );
	}
	*pCODE = (UINT32)(tbl->code[i] << 0);
	*pLEN  = (UINT32)(tbl->codeLength[i] << 0);

	im_raw_off_pclk(NULL);
	Im_RAW_Dsb();

	return D_IM_RAW_RETVAL_OK;
}

/**
 * @brief		Setup encoding parameters except for CODEx and LENx.
 * @param[in]	ImRawCtrlParam* cfg	: Pointer of encoding parameter table.
 * @param[in]	UINT32 code_limit			: The limitation of the size of encoded data
 * @param[out]	None
 * @return		D_IM_RAW_RETVAL_OK, D_IM_RAW_RETVAL_PARAM_ERROR, D_IM_RAW_RETVAL_MACRO_BUSY
 * @note		None
 */
INT32 im_raw_ctrl_enc( imRaw*self,const ImRawCtrlParam* const cfg, UINT32 code_limit )
{
#ifdef CO_PARAM_CHECK
	if( im_raw_check_pointer(cfg) == D_IM_RAW_FALSE ){
		Ddim_Assertion(("I:im_raw_ctrl_enc : INVALID_ARG_ERR\n"));
		return D_IM_RAW_RETVAL_PARAM_ERROR;
	}
#endif

	im_raw_on_pclk(NULL);
	Im_RAW_Dsb();

	if( IO_RAW.RCTL1.bit.RTRG == D_IM_RAW_RTRG_RUNNING ){
		im_raw_off_pclk(NULL);
		Im_RAW_Dsb();
		return D_IM_RAW_RETVAL_MACRO_BUSY;
	}

	imRawSetupParam( cfg );

	IO_RAW.RCTL1.bit.OPMD = 0;			// Encode
	IO_RAW.CLMT.bit.CLMT = code_limit;

	im_raw_off_pclk(NULL);
	Im_RAW_Dsb();

	return D_IM_RAW_RETVAL_OK;
}

/**
 * @brief		Setup decoding parameters except for CODEx and LENx.
 * @param[in]	ImRawCtrlParam*  cfg	: Pointer of decoding parameter table.
 * @param[out]	None
 * @return		D_IM_RAW_RETVAL_OK, D_IM_RAW_RETVAL_PARAM_ERROR, D_IM_RAW_RETVAL_MACRO_BUSY
 * @note		None
 */
INT32 im_raw_ctrl_dec( imRaw*self,const ImRawCtrlParam* const cfg )
{
#ifdef CO_PARAM_CHECK
	if( im_raw_check_pointer(cfg) == D_IM_RAW_FALSE ){
		Ddim_Assertion(("I:im_raw_ctrl_dec : INVALID_ARG_ERR\n"));
		return D_IM_RAW_RETVAL_PARAM_ERROR;
	}
#endif

	im_raw_on_pclk(NULL);
	Im_RAW_Dsb();

	if( IO_RAW.RCTL1.bit.RTRG == D_IM_RAW_RTRG_RUNNING ){
		im_raw_off_pclk(NULL);
		Im_RAW_Dsb();

		return D_IM_RAW_RETVAL_MACRO_BUSY;
	}

	imRawSetupParam( cfg );

	IO_RAW.RCTL1.bit.OPMD = 1;			// Decode

	im_raw_off_pclk(NULL);
	Im_RAW_Dsb();

	return D_IM_RAW_RETVAL_OK;
}

/**
 * @brief		Start JDSRAW3A.
 * @param[in]	None
 * @param[out]	None
 * @return		D_IM_RAW_RETVAL_OK, D_IM_RAW_RETVAL_SYSTEM_ERROR, D_IM_RAW_RETVAL_MACRO_BUSY
 * @note		None
 */
INT32 im_raw_start( imRaw*self )
{
	DDIM_USER_ER	ercd;

	imRawOnRawclk();
	imRawOnRawiclk();
	im_raw_on_pclk(NULL);
	Im_RAW_Dsb();

	if( IO_RAW.RCTL1.bit.RTRG == D_IM_RAW_RTRG_RUNNING ){
		im_raw_off_pclk(NULL);
		imRawOffRawiclk();
		imRawOffRawclk();
		Im_RAW_Dsb();
		return D_IM_RAW_RETVAL_MACRO_BUSY;
	}

	ercd = DDIM_User_Clr_Flg( FID_IM_RAW, (~(D_IM_RAW_FLG_END | D_IM_RAW_FLG_STOP | D_IM_RAW_FLG_R_AXI_ERR | D_IM_RAW_FLG_W_AXI_ERR)) );
	if( D_DDIM_USER_E_OK != ercd ){
		im_raw_off_pclk(NULL);
		imRawOffRawiclk();
		imRawOffRawclk();
		Im_RAW_Dsb();
		return D_IM_RAW_RETVAL_SYSTEM_ERROR;
	}

	// set RAW macro enable (active mode)
	IO_RAW.TBLAEN.bit.TBLAEN	= D_IM_RAW_TBLAEN_ON;
	// wait 1us
	Im_RAW_Wait_usec( D_IM_RAW_SRAM_WAIT_USEC );

	IO_RAW.RCTL1.bit.RTRG = D_IM_RAW_RTRG_START;

	im_raw_off_pclk(NULL);
	Im_RAW_Dsb();

	return D_IM_RAW_RETVAL_OK;
}

/**
 * @brief		Wait end at encoding.
 * @param[out]	UINT32*  condition	: D_IM_RAW_COND_OK, D_IM_RAW_COND_ENC_LIMIT_OVER
 * @param[out]	UINT32* byte		: The size of encoded data
 * @param[in]	INT32 wait_time		: Wait time [msec]. The valid range is -1, 0, ... .
 * @return		D_IM_RAW_RETVAL_OK, D_IM_RAW_RETVAL_PARAM_ERROR, D_IM_RAW_RETVAL_FORCE_STOP, D_IM_RAW_RETVAL_TIME_OUT
 * @note		None
 */
INT32 im_raw_wait_end_enc( imRaw*self,UINT32* const condition, UINT32* const byte, INT32 wait_time )
{
	INT32 				retval;
	DDIM_USER_FLGPTN	waitptn;

#ifdef CO_PARAM_CHECK
	if( (im_raw_check_pointer(condition) == D_IM_RAW_FALSE)
		|| (im_raw_check_pointer(byte) == D_IM_RAW_FALSE)
		|| (im_raw_check_wait_time(wait_time) == D_IM_RAW_FALSE) ){
		Ddim_Assertion(("I:im_raw_wait_end_enc : INVALID_ARG_ERR\n"));
		return D_IM_RAW_RETVAL_PARAM_ERROR;
	}
#endif

	retval = imRawWaitEnd( &waitptn, wait_time );

	imRawOffRawiclk();
	imRawOffRawclk();

	im_raw_on_pclk(NULL);
	Im_RAW_Dsb();

	// RAW macro disable (power save mode)
	IO_RAW.TBLAEN.bit.TBLAEN	= D_IM_RAW_TBLAEN_OFF;

	im_raw_off_pclk(NULL);
	Im_RAW_Dsb();

	if( retval != D_IM_RAW_RETVAL_OK ){
		return retval;
	}

	if( (waitptn & D_IM_RAW_FLG_END) == D_IM_RAW_FLG_END ){
		*condition = S_G_IM_RAW_COND;

		im_raw_on_pclk(NULL);
		Im_RAW_Dsb();

		*byte = IO_RAW.CCNT.word;

		im_raw_off_pclk(NULL);
		Im_RAW_Dsb();

		return D_IM_RAW_RETVAL_OK;
	}

	return D_IM_RAW_RETVAL_FORCE_STOP;
}

/**
 * @brief		Wait end at decoding.
 * @param[out]	UINT32*  condition	: D_IM_RAW_COND_OK, D_IM_RAW_COND_ENC_LIMIT_OVER
 * @param[in]	INT32 wait_time		: Wait time [msec]. The valid range is -1, 0, ... .
 * @return		D_IM_RAW_RETVAL_OK, D_IM_RAW_RETVAL_PARAM_ERROR, D_IM_RAW_RETVAL_FORCE_STOP, D_IM_RAW_RETVAL_TIME_OUT
 * @note		None
 */
INT32 im_raw_wait_end_dec( imRaw*self,UINT32* const condition, INT32 wait_time )
{
	INT32 				retval;
	DDIM_USER_FLGPTN	waitptn;

#ifdef CO_PARAM_CHECK
	if( (im_raw_check_pointer(condition) == D_IM_RAW_FALSE)
		|| (im_raw_check_wait_time(wait_time) == D_IM_RAW_FALSE) ){
		Ddim_Assertion(("I:im_raw_wait_end_dec : INVALID_ARG_ERR\n"));
		return D_IM_RAW_RETVAL_PARAM_ERROR;
	}
#endif

	retval = imRawWaitEnd( &waitptn, wait_time );

	imRawOffRawiclk();
	imRawOffRawclk();

	im_raw_on_pclk(NULL);
	Im_RAW_Dsb();

	// RAW macro disable (power save mode)
	IO_RAW.TBLAEN.bit.TBLAEN	= D_IM_RAW_TBLAEN_OFF;

	im_raw_off_pclk(NULL);
	Im_RAW_Dsb();

	if( retval != D_IM_RAW_RETVAL_OK ){
		return retval;
	}

	if( (waitptn & D_IM_RAW_FLG_END) == D_IM_RAW_FLG_END ){
		*condition = S_G_IM_RAW_COND;
		return D_IM_RAW_RETVAL_OK;
	}

	return D_IM_RAW_RETVAL_FORCE_STOP;
}

/**
 * @brief		Stop JDSRAW3A.
 * @param[in]	None
 * @param[out]	None
 * @return		D_IM_RAW_RETVAL_OK, D_IM_RAW_RTRG_STOP, D_IM_RAW_RETVAL_SYSTEM_ERROR, D_IM_RAW_RETVAL_MACRO_BUSY
 * @note		None
 */
INT32 im_raw_stop( imRaw*self )
{
	INT32 retval = D_IM_RAW_RETVAL_OK;
	DDIM_USER_ER	ercd;

	im_raw_on_pclk(NULL);
	Im_RAW_Dsb();

	if( IO_RAW.RCTL1.bit.RTRG == D_IM_RAW_RTRG_RUNNING ){
		IO_RAW.RCTL1.bit.RTRG = D_IM_RAW_RTRG_STOP;
		Im_RAW_Dsb();

		ercd = DDIM_User_Set_Flg( FID_IM_RAW, D_IM_RAW_FLG_STOP );
		if( ercd != D_DDIM_USER_E_OK ){
			Ddim_Print(("I:im_raw_stop : Error DDIM_User_Set_Flg [%d]\n", ercd));
			retval = D_IM_RAW_RETVAL_SYSTEM_ERROR;
		}

		if( IO_RAW.RCTL1.bit.RTRG == D_IM_RAW_RTRG_RUNNING ){
			Ddim_Print(("I:im_raw_stop : JDSRAW3A is still running.\n"));
			retval = D_IM_RAW_RETVAL_MACRO_BUSY;
		}
	}

	im_raw_off_pclk(NULL);
	Im_RAW_Dsb();

	return retval;
}

/**
 * @brief		Get AXI bus I/F Status
 * @param[out]	T_IM_RAW_AXI_STATUS* sts	: sts	AXI bus I/F status parameter
 * @return		D_IM_RAW_RETVAL_OK, D_IM_RAW_RETVAL_PARAM_ERROR
 * @note		None
 */
INT32 im_raw_get_axi_status( imRaw*self,ImRawAxiStatus* const sts )
{
#ifdef CO_PARAM_CHECK
	if( sts == NULL ){
		// sts setting error
		Ddim_Assertion(("I:im_raw_get_axi_status : INVALID_ARG_ERR\n"));
		return D_IM_RAW_RETVAL_PARAM_ERROR;
	}
#endif

	im_raw_on_pclk(NULL);
	Im_RAW_Dsb();

	sts->rChResp = IO_RAW.MRAXSTS.bit.RRESP;
	sts->wChResp = IO_RAW.MWAXSTS.bit.BRESP;

	im_raw_off_pclk(NULL);
	Im_RAW_Dsb();

	return D_DDIM_OK;
}

/**
 * @brief		Interrupt handler.
 * @param[in]	None
 * @param[out]	None
 * @return		None
 * @note		None
 */
VOID im_raw_int_handler( VOID)
{
	UINT32	rinte_reg, rintf_reg;
	DDIM_USER_ER	ercd;

	im_raw_on_pclk(NULL);
	Im_RAW_Dsb();

	rintf_reg = IO_RAW.RINTF.word;
	IO_RAW.RINTF.word = rintf_reg;		// Clear interrupt
	rinte_reg = IO_RAW.RINTE.word;
	S_G_IM_RAW_COND = IO_RAW.COND.word;	// Get COND register.

	im_raw_off_pclk(NULL);
	Im_RAW_Dsb();

	// Check Read AXI Error interrupt state
	if( ( (rinte_reg & D_IM_RAW_INT_RAXER_BIT) != 0 ) && ( (rintf_reg & D_IM_RAW_INT_RAXER_BIT) != 0 ) ){
		ercd = DDIM_User_Set_Flg( FID_IM_RAW, D_IM_RAW_FLG_R_AXI_ERR );
		if( ercd != D_DDIM_USER_E_OK ){
			Ddim_Print(("I:im_raw_int_handler : Read AXI Error DDIM_User_Set_Flg [%d]\n", ercd));
		}

		if( S_G_IM_RAW_CALLBACK != NULL ){
			S_G_IM_RAW_CALLBACK( (UINT32)D_IM_RAW_R_AXI_ERROR );
		}
	}

	// Check Write AXI Error interrupt state
	if( ( (rinte_reg & D_IM_RAW_INT_WAXER_BIT) != 0 ) && ( (rintf_reg & D_IM_RAW_INT_WAXER_BIT) != 0 ) ){
		ercd = DDIM_User_Set_Flg( FID_IM_RAW, D_IM_RAW_FLG_W_AXI_ERR );
		if( ercd != D_DDIM_USER_E_OK ){
			Ddim_Print(("I:im_raw_int_handler : Write AXI Error DDIM_User_Set_Flg [%d]\n", ercd));
		}

		if( S_G_IM_RAW_CALLBACK != NULL ){
			S_G_IM_RAW_CALLBACK( (UINT32)D_IM_RAW_W_AXI_ERROR );
		}
	}

	// Check Process complete interrupt state
	if( ( (rinte_reg & D_IM_RAW_INT_R_BIT) != 0 ) && ( (rintf_reg & D_IM_RAW_INT_R_BIT) != 0 ) ){
		ercd = DDIM_User_Set_Flg( FID_IM_RAW, D_IM_RAW_FLG_END );
		if( ercd != D_DDIM_USER_E_OK ){
			Ddim_Print(("I:im_raw_int_handler : Error DDIM_User_Set_Flg [%d]\n", ercd));
		}

		if( S_G_IM_RAW_CALLBACK != NULL ){
			S_G_IM_RAW_CALLBACK( S_G_IM_RAW_COND );
		}
	}
}


imRaw *im_raw_new(void)
{
	imRaw* self = k_object_new_with_private(IM_TYPE_RAW,sizeof(imRawPrivate));
	return self;
}
